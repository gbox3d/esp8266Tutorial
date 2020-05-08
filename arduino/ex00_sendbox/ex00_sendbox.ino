#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

WiFiUDP Udp;
const char *g_configFileName = "config.json";

struct _S_CONFIG
{
    String m_ssid;
    String m_passwd;
    String m_remoteIp;
    int m_remote_port;
    String m_LocalIp;
    int m_Local_port;
};

_S_CONFIG g_ConfigData;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

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
        g_ConfigData.m_remoteIp = (const char *)doc["remoteIp"];
        g_ConfigData.m_remote_port = doc["remotePort"];
        g_ConfigData.m_LocalIp = (const char *)doc["localIp"];
        g_ConfigData.m_Local_port = doc["localPort"];

        _f.close();
    }
    else
    {
        Serial.println("file not exist now create file...");
        File _f = SPIFFS.open(g_configFileName, "w");

        DynamicJsonDocument doc(1024);

        doc["ssid"] = "redstar";
        doc["passwd"] = "0427";
        doc["remoteIp"] = "";
        doc["remotePort"] = 0;
        doc["localIp"] = "";
        doc["localPort"] = 0;

        serializeJson(doc, _f);

        g_ConfigData.m_ssid = (const char *)doc["ssid"];
        g_ConfigData.m_passwd = (const char *)doc["passwd"];
        g_ConfigData.m_remoteIp = (const char *)doc["remoteIp"];
        g_ConfigData.m_remote_port = doc["remotePort"];
        g_ConfigData.m_LocalIp = (const char *)doc["localIp"];
        g_ConfigData.m_Local_port = doc["localPort"];

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
        case 'n':
            Serial.println("connect ap");
            {
                WiFi.disconnect();
                WiFi.begin(g_ConfigData.m_ssid, g_ConfigData.m_passwd);
                while (WiFi.status() != WL_CONNECTED)
                {
                    digitalWrite(LED_BUILTIN, HIGH);
                    delay(250);
                    Serial.print(".");
                    digitalWrite(LED_BUILTIN, LOW);
                    delay(250);
                }
                Serial.println();
                delay(500);
                Udp.begin(g_ConfigData.m_Local_port);
                Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), g_ConfigData.m_Local_port);
                digitalWrite(LED_BUILTIN, LOW);
            }
            break;
        case 'd': //dump
            Serial.println("dump:");
            {
                DynamicJsonDocument doc(1024);

                doc["ssid"] = g_ConfigData.m_ssid;
                doc["passwd"] = g_ConfigData.m_passwd;
                doc["remoteIp"] = g_ConfigData.m_remoteIp;
                doc["remotePort"] = g_ConfigData.m_remote_port;
                doc["localIp"] = g_ConfigData.m_LocalIp;
                doc["localPort"] = g_ConfigData.m_Local_port;

                serializeJson(doc, Serial);
            }
            Serial.println();
            break;
        case 'e':
            Serial.println("edit");
            {
                char _c = Serial.read();
                if (_c == 'w')
                {
                    Serial.println("wifi setup");
                    Serial.readStringUntil('\n');
                    while (Serial.available() == 0)
                        ;
                    g_ConfigData.m_ssid = Serial.readStringUntil(' ');
                    g_ConfigData.m_passwd = Serial.readStringUntil('\r');

                    Serial.printf("ok : %s ,%s \n", g_ConfigData.m_ssid.c_str(), g_ConfigData.m_passwd.c_str());
                }
                else if (_c == 'r')
                {
                    Serial.println("remote setup");
                    Serial.readStringUntil('\n');
                    while (Serial.available() == 0)
                        ;

                    g_ConfigData.m_remoteIp = Serial.readStringUntil(' ');
                    g_ConfigData.m_remote_port = atoi(Serial.readStringUntil('\r').c_str());

                    Serial.printf("ok : %s ,%d \n", g_ConfigData.m_remoteIp.c_str(), g_ConfigData.m_remote_port);
                }
                else if (_c == 'l')
                {
                    Serial.println("local setup");
                    Serial.readStringUntil('\n');
                    while (Serial.available() == 0)
                        ;

                    g_ConfigData.m_LocalIp = Serial.readStringUntil(' ');
                    g_ConfigData.m_Local_port = atoi(Serial.readStringUntil('\r').c_str());

                    Serial.printf("ok : %s ,%d \n", g_ConfigData.m_LocalIp.c_str(), g_ConfigData.m_Local_port);
                }
            }
            break;
        case 's':
            Serial.println("save");
            {
                DynamicJsonDocument doc(1024);
                doc["ssid"] = g_ConfigData.m_ssid;
                doc["passwd"] = g_ConfigData.m_passwd;
                doc["remoteIp"] = g_ConfigData.m_remoteIp;
                doc["remotePort"] = g_ConfigData.m_remote_port;
                doc["localIp"] = g_ConfigData.m_LocalIp;
                doc["localPort"] = g_ConfigData.m_Local_port;

                File _f = SPIFFS.open(g_configFileName, "w");
                serializeJson(doc, _f);
                _f.close();
            }
            break;
        case 'p':
            Serial.println("send packet test");
            {
                char _c = Serial.read();
                if (_c == 'u')
                {
                    Udp.beginPacket(g_ConfigData.m_remoteIp.c_str(), g_ConfigData.m_remote_port);
                    Udp.write("ping", 5);
                    Udp.endPacket();
                }
                else if (_c == 't')
                {
                    WiFiClient client;
                    Serial.printf("\n[Connecting to %s ... ", g_ConfigData.m_remoteIp.c_str());
                    if (client.connect(g_ConfigData.m_remoteIp.c_str(), g_ConfigData.m_remote_port))
                    {
                        Serial.println("connected]");

                        Serial.println("[Sending a request]");
                        client.print(String("GET /") + " HTTP/1.1\r\n" +
                                     "Host: " + g_ConfigData.m_remoteIp.c_str() + "\r\n" +
                                     "Connection: close\r\n" +
                                     "\r\n");

                        Serial.println("[Response:]");
                        while (client.connected() || client.available())
                        {
                            if (client.available())
                            {
                                String line = client.readStringUntil('\n');
                                Serial.println(line);
                            }
                        }
                        client.stop();
                        Serial.println("\n[Disconnected]");
                    }
                    else
                    {
                        Serial.println("connection failed!]");
                        client.stop();
                    }
                }
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