#include <ArduinoJson.h>
#include <time.h>
#include <WiFiClientSecure.h>


static WiFiClientSecure client;
static char buffer[BUFFER_SIZE];  // "probably large enough"
JsonDocument doc;


bool retrieveWeatherData()
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


tm getDateTime()
{
    struct tm datetime;
    if (doc["liveweer"][0]["time"].is<const char*>())
    {
        strptime(doc["liveweer"][0]["time"], "%d-%m-%Y %T", &datetime);
    }
    
    return datetime;
}


