#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

unsigned int UDPPort = 2390; // local port to listen on

char packetBuffer[255];              //buffer to hold incoming packet
char ReplyBuffer[] = "acknowledged"; // a string to send back
WiFiUDP Udp;
void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("espap01","123456789");
  Udp.begin(UDPPort);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);

  // Serial.println();
  // Serial.println("Started ap. Local ip: " + WiFi.localIP().toString());
}

void loop()
{
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remoteIp = Udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(", port ");
    Serial.println(Udp.remotePort());
    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0)
    {
      packetBuffer[len] = 0;
    }
    Serial.println("Contents:");
    Serial.println(packetBuffer);
    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }
}

// /* Create a WiFi access point and provide a web server on it. */

// #include <ESP8266WiFi.h>
// #include <WiFiClient.h>
// #include <ESP8266WebServer.h>

// #ifndef APSSID
// #define APSSID "ESPap"
// #define APPSK  "thereisnospoon"
// #endif

// /* Set these to your desired credentials. */
// const char *ssid = APSSID;
// const char *password = APPSK;

// ESP8266WebServer server(80);

// /* Just a little test message.  Go to http://192.168.4.1 in a web browser
//    connected to this access point to see it.
// */
// void handleRoot() {
//   server.send(200, "text/html", "<h1>You are connected</h1>");
// }

// void setup() {
//   delay(1000);
//   Serial.begin(115200);
//   Serial.println();
//   Serial.print("Configuring access point...");
//   /* You can remove the password parameter if you want the AP to be open. */
//   WiFi.softAP(ssid, password);

//   IPAddress myIP = WiFi.softAPIP();
//   Serial.print("AP IP address: ");
//   Serial.println(myIP);
//   server.on("/", handleRoot);
//   server.begin();
//   Serial.println("HTTP server started");
// }

// void loop() {
//   server.handleClient();
// }