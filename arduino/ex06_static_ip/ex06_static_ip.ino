/*
고정 아이피 만들기 예제
2020.5.5
 */
#include <ESP8266WiFi.h>      //manipula o wifi
#include <ArduinoJson.h>

const int status_led_pin = 2; //d4

void setup()
{
    pinMode(status_led_pin, OUTPUT);
    digitalWrite(status_led_pin, LOW);
    Serial.begin(115200);
    delay(500);

    Serial.printf("start Appp \n");

    Serial.println("load config");
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


    IPAddress ip;
    String strIp = "192.168.4.81";
    // IPAddress ip(192, 168, 4, 81);
    ip.fromString(strIp); //문자열에서 가져오기 

    IPAddress gateway(192, 168, 4, 1);
    IPAddress subnet(255, 255, 255, 0);

    WiFi.config(ip, gateway, subnet);

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

    // char strAddr1[20]; //new string
    // Serial.print("Start value to the string = ");
    // Serial.println(strAddr);
    // Serial.print("Start value to the apIP = ");
    // Serial.println(apIP);
    // StrToIP(strAddr, &apIP); //conversion: String to IP
    // Serial.print("Conversion: string to  apIP = ");
    // Serial.println(apIP);
    // IPtoStr(strAddr1, apIP); //conversion IP to a new string
    // Serial.print("Conversion: apIP to the new string  = ");
    // Serial.println(strAddr1);
}

void loop()
{
}
