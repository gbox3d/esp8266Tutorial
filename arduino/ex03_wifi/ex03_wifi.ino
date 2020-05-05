#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

const int status_led_pin = 2; //d4

void setup()
{
  pinMode(status_led_pin, OUTPUT);
  digitalWrite(status_led_pin, LOW);
  delay(500);
  Serial.begin(115200);

  Serial.println("ready...");

  SPIFFS.begin();

  String ssid, passwd;
  {
    File _f = SPIFFS.open("config.json", "r");
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, _f);
    ssid = (const char *)doc["ssid"];
    passwd = (const char *)doc["passwd"];
    _f.close();
  }

  WiFi.begin(ssid, passwd);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(status_led_pin, HIGH);
    delay(250);
    Serial.print(".");
    digitalWrite(status_led_pin, LOW);
    delay(250);
  }
  digitalWrite(status_led_pin, LOW);
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {}