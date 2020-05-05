#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

const char *g_configFileName = "config.json";

struct _S_CONFIG
{
    String m_ssid;
    String m_passwd;
};

_S_CONFIG g_ConfigData;

void setup()
{
    Serial.begin(115200);

    delay(500);

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

    Serial.println("start app");

    if (SPIFFS.exists(g_configFileName))
    {
        Serial.println("file exist now read file...");
        File _f = SPIFFS.open(g_configFileName, "r");
        // size_t size = _f.size();
        
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, _f);
        g_ConfigData.m_ssid = (const char *)doc["ssid"];
        g_ConfigData.m_passwd = (const char *)doc["passwd"];
        _f.close();
    }
    else
    {
        Serial.println("file not exist now create file...");
        File _f = SPIFFS.open(g_configFileName, "w");

        DynamicJsonDocument doc(1024);

        doc["ssid"] = "redstar";
        doc["passwd"] = "0427";

        serializeJson(doc, _f);

        g_ConfigData.m_ssid = (const char *)doc["ssid"];
        g_ConfigData.m_passwd = (const char *)doc["passwd"];

        _f.close();
    }

    //clear buffer
    while (Serial.available() > 0)
    {
        Serial.print(Serial.readString());
        delay(5);
    }
    Serial.println("setup done..");
}

void loop()
{
    while (Serial.available() > 0)
    {
        char _c = Serial.read();
        switch (_c)
        {
        case 'l': //load
            Serial.println("load:");
            {
            }
            break;
        case 'd': //dump
            Serial.println("dump:");
            {
                DynamicJsonDocument doc(1024);

                doc["ssid"] = g_ConfigData.m_ssid;
                doc["passwd"] = g_ConfigData.m_passwd;

                serializeJson(doc, Serial);
            }
            Serial.println();
            break;
        case 'e':
            Serial.println("edit");
            {
                Serial.read();
                g_ConfigData.m_ssid = Serial.readStringUntil(' ');
                g_ConfigData.m_passwd = Serial.readStringUntil('\r');
            }
            break;
        case 's':
            Serial.println("save");
            {
                DynamicJsonDocument doc(1024);
                doc["ssid"] = g_ConfigData.m_ssid;
                doc["passwd"] = g_ConfigData.m_passwd;

                File _f = SPIFFS.open(g_configFileName, "w");
                serializeJson(doc, _f);
                _f.close();
            }
            break;
        case 'f':
            Serial.println("format");
            {
                SPIFFS.format();
            }
            Serial.println("format done");
            break;
        }
    }
}