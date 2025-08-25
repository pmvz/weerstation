#include <Arduino.h>
#include <esp_netif_sntp.h>
#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>
#include <SPI.h>
#include <SensirionI2cScd4x.h>
#include <time.h>
#include <WiFi.h>
#include <Wire.h>
#include "settings.h"
#include "graphics.h"
#include "drawing.h"
#include "weather.h"


SensirionI2cScd4x sensorCO2;
static char errorMessage[64];
TimerHandle_t measurementTimer;
TimerHandle_t updateWeatherTimer;


void setup() {
    // Set pins
    pinMode(PIN_EPD_DC, OUTPUT);
    pinMode(PIN_EPD_CS, OUTPUT);
    pinMode(PIN_EPD_RESET, OUTPUT);
    pinMode(PIN_EPD_BUSY, INPUT);

    // Start serial and sensor
    Serial.begin(115200);
    delay(1000);
    setupCo2Sensor();

    // Init wifi
    WiFi.mode(WIFI_MODE_STA);
    WiFi.begin(wifi_ssid, wifi_pass);
    Serial.print("Connecting to network ..");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    }
    Serial.print(" Connected! IP: ");
    Serial.println(WiFi.localIP());
    delay(1000);

    // Set time from NTP server
    setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 1);
    tzset();
    esp_sntp_config_t config = ESP_NETIF_SNTP_DEFAULT_CONFIG("pool.ntp.org");
    esp_netif_sntp_init(&config);
    if (esp_netif_sntp_sync_wait(pdMS_TO_TICKS(60000)) != ESP_OK) {
        Serial.println("Failed to update system time within 10s timeout");
    }

    // Init display and weather
    initDisplay();
    updateWeatherData();
    updateMeasurements();
    
    // Start measurement and display updating tasks and end the app_main task
    updateWeatherTimer = xTimerCreate("Update weather timer",
                                    pdMS_TO_TICKS(INTERVAL_WEATHER),
                                    pdTRUE,
                                    (void*) 1,
                                    updateWeatherDataTimerHandler);
    measurementTimer = xTimerCreate("Measurement timer",
                                    pdMS_TO_TICKS(INTERVAL_MEASUREMENT),
                                    pdTRUE,
                                    (void*) 0,
                                    updateMeasurementsTimerHandler);

    xTimerStart(updateWeatherTimer, 0);
    xTimerStart(measurementTimer, 0);
    return;
}

void setupCo2Sensor() {
    Wire.begin();
    sensorCO2.begin(Wire, I2C_CO2);
    delay(30);

    int error = sensorCO2.stopPeriodicMeasurement();
    if (error != 0) {
        Serial.print("Error trying to execute stopPeriodicMeasurement(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
    }

    error = sensorCO2.reinit();
    if (error != 0) {
        Serial.print("Error trying to execute reinit(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
    }

    error = sensorCO2.startPeriodicMeasurement();
    if (error != 0) {
        Serial.print("Error trying to execute startPeriodicMeasurement(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
        return;
    }
}

void updateMeasurements() {
    bool dataReady = false;
    uint16_t co2Concentration = 0;
    float temperature = 0.0;
    float relativeHumidity = 0.0;

    int error = sensorCO2.getDataReadyStatus(dataReady);
    if (error != 0) {
        Serial.print("Error trying to execute getDataReadyStatus(): ");
        errorToString(error, errorMessage, sizeof(errorMessage));
        Serial.println(errorMessage);
        return;
    }

    if (!dataReady) {
        Serial.println("Error trying to get data: not ready");
        return;
    }

    error = sensorCO2.readMeasurement(co2Concentration, temperature, relativeHumidity);
    if (error != 0) {
        Serial.print("Error trying to execute readMeasurement(): ");
        errorToString(error, errorMessage, sizeof(errorMessage));
        Serial.println(errorMessage);
        return;
    }
    
    // Report results via serial
    Serial.print("CO2 concentration [ppm]: ");
    Serial.print(co2Concentration);
    Serial.println();
    Serial.print("Temperature [deg C]: ");
    Serial.print(temperature);
    Serial.println();
    Serial.print("Relative Humidity [RH]: ");
    Serial.print(relativeHumidity);
    Serial.println();

    // Get current time
    time_t now;
    struct tm timeinfo;    
    time(&now);
    localtime_r(&now, &timeinfo);

    // Display results
    clear();
    drawInfo(co2Concentration, temperature, relativeHumidity, 1000, &timeinfo);
    show();
}

void updateMeasurementsTimerHandler(TimerHandle_t timer) {
    Serial.println("Updating measurements...");
    updateMeasurements();
}

void updateWeatherDataTimerHandler(TimerHandle_t timer) {
    Serial.println("Updating weather data...");
    updateWeatherData();
}

// loop is required to compile, FreeRTOS runs tasks
void loop() { }
