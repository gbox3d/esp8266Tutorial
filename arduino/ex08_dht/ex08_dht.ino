/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/

#include <Arduino.h>
#include <DHT.h>
#include <ESP8266WiFi.h>

#define DHTTYPE DHT11
#define DHTPIN D4

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(115200);
    Serial.println("DHT11 test!");
    dht.begin();
}

// the loop function runs over and over again forever
void loop()
{
}
