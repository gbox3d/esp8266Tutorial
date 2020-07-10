#include <Arduino.h>
#include <ESP8266WiFi.h>


/*
테스트 기판 제작요령 
D0 : Vcc(3v)와 스위치 연결 , 오픈 -> 0 SIGANL
D5 : Gnd 와 스위치 연결    ,오픈 -> 1 SIGNAL
*/
const int pulldown_pin = D0; 
// const int led_pin = 14; //d5

void setup()
{
    //16 핀은 pulldown 가능하다, 나머지 핀들은 pullup 만 가능함.
    pinMode(pulldown_pin,INPUT_PULLDOWN_16);
    pinMode(D5,INPUT_PULLUP);
    //digitalWrite(led_pin,LOW);
    Serial.begin(115200);
}

void loop()
{
    Serial.printf("D0:%d,D5:%d\n",
    digitalRead(pulldown_pin),
    digitalRead(D5)
    );
    delay(100);
    // if( digitalRead(pulldown_pin)  ) {
    //     digitalWrite(led_pin,HIGH);
    // }
    // else {
    //      digitalWrite(led_pin,LOW);
    // }

}