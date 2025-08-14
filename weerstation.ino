#include <SPI.h>
#include "settings.h"
#include "Adafruit_ThinkInk.h"
//#include "display.h"
#include <SensirionI2cScd4x.h>
#include "graphics.h"

ThinkInk_290_Tricolor_Z94 display(PIN_EPD_DC, PIN_EPD_RESET, PIN_EPD_CS, -1, PIN_EPD_BUSY);
SensirionI2cScd4x sensorCO2;
static char errorMessage[64];
static int16_t error;
unsigned long last_update_time;


void drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t color)
{
    display.drawLine(x1, y1, x2, y2, (uint16_t)color);
}


void PrintUint64(uint64_t& value) {
    Serial.print("0x");
    Serial.print((uint32_t)(value >> 32), HEX);
    Serial.print((uint32_t)(value & 0xFFFFFFFF), HEX);
}

void setup() {
    pinMode(PIN_EPD_DC, OUTPUT);
    pinMode(PIN_EPD_CS, OUTPUT);
    pinMode(PIN_EPD_RESET, OUTPUT);
    pinMode(PIN_EPD_BUSY, INPUT);

    Serial.begin(115200);
    delay(1000);
    Serial.println("Hi!");
    
    //SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    //SPI.begin();
    
    Wire.begin();
    sensorCO2.begin(Wire, I2C_CO2);
    uint64_t serialNumber = 0;
    delay(30);

    error = sensorCO2.stopPeriodicMeasurement();
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

    // Read out information about the sensor
    error = sensorCO2.getSerialNumber(serialNumber);
    if (error != 0) {
        Serial.print("Error trying to execute getSerialNumber(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
        return;
    }
    Serial.print("serial number: ");
    PrintUint64(serialNumber);
    Serial.println();

    error = sensorCO2.startPeriodicMeasurement();
    if (error != 0) {
        Serial.print("Error trying to execute startPeriodicMeasurement(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
        return;
    }

    display.begin(THINKINK_TRICOLOR);
    display.clearBuffer();
    drawInfo(7890, 12.3, 45.6);
    display.display();
    last_update_time = millis();
}


void drawInfo(int co2Concentration, float temperature, float relativeHumidity)
{
    struct Cursor cursor = { 0, 0 };

    // Time
    cursor = { 31, 36 };


    //drawNumberFloat(cursor, temperature);
    //drawNumberInt(cursor, round(relativeHumidity));
    //drawNumberInt(co2Concentration, cursor);
}


void loop()
{
    unsigned long current_time = millis();
    if (current_time - last_update_time < UPDATE_INTERVAL)
    {
        delay(500);
        return;
    }
    last_update_time = current_time;

    bool dataReady = false;
    uint16_t co2Concentration = 0;
    float temperature = 0.0;
    float relativeHumidity = 0.0;

    error = sensorCO2.getDataReadyStatus(dataReady);
    if (error != 0) {
        Serial.print("Error trying to execute getDataReadyStatus(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
        return;
    }
    if (!dataReady)
    {
        Serial.println("Error trying to get data: not ready");
    }

    // If ambient pressure compenstation during measurement
    // is required, you should call the respective functions here.
    // Check out the header file for the function definition.
    error = sensorCO2.readMeasurement(co2Concentration, temperature, relativeHumidity);
    if (error != 0) {
        Serial.print("Error trying to execute readMeasurement(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
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

    // Display results
    display.clearBuffer();
    drawInfo(co2Concentration, temperature, relativeHumidity);
    display.display();
}
