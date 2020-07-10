#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <FS.h>
#include <WiFiUdp.h>
#include <Ticker.h>

#include "esfos_drv.hpp"

const char *g_configFileName = "config.json";

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.begin(115200);

    delay(500);
    Serial.println("start app");

    //Initialize File System
    if (SPIFFS.begin())
    {
        Serial.println("SPIFFS Initialize....ok");
    }
    else
    {
        Serial.println("SPIFFS Initialization...failed");
        //Format File System
        if (SPIFFS.format())
        {
            Serial.println("File System Formated");
        }
        else
        {
            Serial.println("File System Formatting Error");
        }
    }
    // SPIFFS.begin();

    if (SPIFFS.exists(g_configFileName))
    {
        Serial.println("file exist now read file...");
        File _f = SPIFFS.open(g_configFileName, "r");

        String line = _f.readString();
        Serial.println(line);
        _f.close();
    }
    else
    {
    }

    
}

void loop()
{
    esfos::run_driver();
}