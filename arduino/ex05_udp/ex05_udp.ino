#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const int status_led_pin = 2; //d4

WiFiUDP Udp;
unsigned int localUdpPort = 4210; // local port to listen on
char incomingPacket[255];         // buffer for incoming packets
//char  replyPacket[] = "Hi there! Got the message :-)";  // a reply string to send back

struct S_Packet
{
  byte m_header;
  byte m_code;
  byte m_param[2];
  int m_index;
  float m_sensorData;
};

struct S_RemotePacket
{
  byte m_header;
  byte m_code;
  byte m_status;
  byte m_extra;

  int m_data;
};

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

  //WiFi.begin("ubiqos office", "28608010");
  WiFi.begin(ssid,passwd);

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

  delay(500);
  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);

  //Serial.print("Connected, IP address: ");
  //Serial.println(WiFi.localIP());
}

void loop()
{

  //요청
  {
    S_Packet testPacket;
    memset(&testPacket, 0, sizeof(S_Packet));
    testPacket.m_header = 99;
    testPacket.m_code = 81;
    testPacket.m_index = 15001;
    testPacket.m_sensorData = 96.75;

    IPAddress remote_ip(192,168,4,2);
    Udp.beginPacket(remote_ip, 2012);
    Udp.write((const char *)&testPacket, sizeof(S_Packet));

    Udp.endPacket();

    Serial.println("send....");
  }

  // delay(100);

  {
    S_RemotePacket receivePacket;
    //응답처리
    int packetSize = Udp.parsePacket();
    if (packetSize)
    {
      // receive incoming UDP packets
      Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
      int len = Udp.read((char *)&receivePacket, sizeof(S_RemotePacket));

      Serial.printf("header : %d,code:%d,status:%d,extra:%d",
                    receivePacket.m_header,
                    receivePacket.m_code,
                    receivePacket.m_status,
                    receivePacket.m_extra);

      Serial.println();
      Serial.printf("data : %d", receivePacket.m_data);


      // if (len > 0)
      // {
      //   incomingPacket[len] = 0;
      // }
      // Serial.printf("UDP packet contents: %s\n", incomingPacket);
    }
  }

  delay(3000);
}