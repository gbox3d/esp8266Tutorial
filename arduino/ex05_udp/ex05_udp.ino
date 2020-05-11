#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const int status_led_pin = 2; //d4

WiFiUDP Udp;
String remoteIp;
unsigned int remoteUdpPort;
unsigned int localUdpPort; // local port to listen on
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
    remoteIp = (const char *)doc["remoteIp"];
    remoteUdpPort = doc["remotePort"];
    _f.close();
  }
//wifi 초기화 
  WiFi.disconnect();
  delay(500);

  //반드시 접속 모드를 명기해주어야한다. 일부 공유기에서는 STA_AP가 동작하지 않는다.
  WiFi.mode(WIFI_STA);
  delay(100);

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

  Serial.printf("Connected, IP address: %s \n", WiFi.localIP().toString().c_str());

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

    // IPAddress remote_ip(192, 168, 4, 2);
    Serial.printf("udp packet send to %s ... \n", remoteIp.c_str());
    Udp.beginPacket(remoteIp.c_str(), remoteUdpPort);
    Udp.write((const char *)&testPacket, sizeof(S_Packet));
    Udp.endPacket();

  }

  delay(100);

  {
    S_RemotePacket receivePacket;
    //응답처리
    int packetSize = Udp.parsePacket();
    if (packetSize)
    {
      // receive incoming UDP packets
      Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
      int len = Udp.read((char *)&receivePacket, sizeof(S_RemotePacket));

      Serial.printf("\n------\n header : %d,code:%d,status:%d,extra:%d \n",
                    receivePacket.m_header,
                    receivePacket.m_code,
                    receivePacket.m_status,
                    receivePacket.m_extra);
      Serial.printf("data : %d \n---------\n", receivePacket.m_data);
    }
  }

  delay(5000);
}