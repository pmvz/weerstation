#pragma once

#include <ArduinoJson.h>
#include <time.h>
#include <WiFiClientSecure.h>


static WiFiClientSecure client;
static char buffer[BUFFER_SIZE];  // "probably large enough"
JsonDocument doc;


bool updateWeatherData()
{
    // Connect
    client.setCACert(api_cert);
    client.setTimeout(10000);
    if (!client.connect(api_domain, 443))
    {
        Serial.println("Failed to connect to weather service!");
        return false;
    }

    // Send HTTP request
    client.println(api_request);
    client.print("Host: ");
    client.println(api_domain);
    client.println("Connection: close");
    if (client.println() == 0)
    {
        Serial.println("Failed to send request");
        client.stop();
        return false;
    }

    // Check HTTP status, should be "HTTP/1.0 200 OK" or "HTTP/1.1 200 OK"
    char status[32] = {0};
    client.readBytesUntil('\r', status, sizeof(status));
    if (strcmp(status + 9, "200 OK") != 0)
    {
        Serial.print("Unexpected response: ");
        Serial.println(status);
        client.stop();
        return false;
    }

    // Skip HTTP headers
    char endOfHeaders[] = "\r\n\r\n";
    if (!client.find(endOfHeaders))
    {
        Serial.println("Invalid response");
        client.stop();
        return false;
    }

    int buffersize_remaining = BUFFER_SIZE;
    memset(buffer, '\0', BUFFER_SIZE);
    
    // Chunked decoder
    int i = 0;
    while (i < MAX_CHUNKS)
    {
        // Read and decode the chunk size
        char chunksize_line[8] = {0};
        client.readBytesUntil('\n', chunksize_line, 7);
        int chunksize = strtol(chunksize_line, nullptr, 16);
        if (chunksize == 0)
            break;  // End of chunks

        if (buffersize_remaining - chunksize <= 1)
        {
            Serial.println("Insufficient buffer space while decoding chunked response");
            break;
        }
        else
        {   
            buffersize_remaining -= chunksize;
        }

        // Read chunk and add to buffer
        char* chunk = (char*)malloc(chunksize);
        client.readBytes(chunk, chunksize);
        strncat(buffer, chunk, chunksize);
        free(chunk);
        chunk = nullptr;

        client.read(); // read \r
        client.read(); // read \n
        i++;
    }

    Serial.print("API response: ");
    for (int i = 0; i < BUFFER_SIZE; i += 128)
    {
        Serial.write(buffer + i, 128);
    }
    Serial.println();

    // Parse JSON object
    doc.clear();
    DeserializationError error = deserializeJson(doc, buffer);
    if (error)
    {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.f_str());
        return false;
    }

    // Disconnect
    client.stop();
    return true;
}

char* getCurrentWeatherIconName()
{
    if (!doc["liveweer"][0]["image"].is<const char*>())
        return "unknown";

    // Poor man's pattern matching
    const char* image = doc["liveweer"][0]["image"].as<const char*>();
    if (strcmp(image, "zonnig") == 0)
        return "sunny";
    else if (strcmp(image, "lightning") == 0)
        return "lightning";  // TODO: sunnylightning, nightlightning
    else if (strcmp(image, "regen") == 0 ||
             strcmp(image, "buien") == 0 ||
             strcmp(image, "hagel") == 0)
        return "rain";
    else if (strcmp(image, "mist") == 0)
        return "sunnyfog";  // TODO: fog?
    else if (strcmp(image, "sneeuw") == 0)
        return "snow";  // TODO: sunnysnow, nightsnow
    else if (strcmp(image, "lightbewolkt") == 0 ||
             strcmp(image, "halfbewolkt") == 0)
        return "sunnyclouded";  // TODO: nightclouded
    else if (strcmp(image, "halfbewolkt_regen") == 0)
        return "sunnyrain";  // TODO: nightrain
    else if (strcmp(image, "bewolkt") == 0 ||
             strcmp(image, "zwaarbewolkt") == 0)
        return "clouded";
    else if (strcmp(image, "nachtmist") == 0)
        return "nightfog";  // TODO: fog?
    else if (strcmp(image, "helderenacht") == 0)
        return "night";
    else if (strcmp(image, "nachtbewolkt") == 0)
        return "nightclouded";
    else
        return "unknown";
}

