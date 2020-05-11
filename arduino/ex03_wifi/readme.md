## wifi object

### 접속모드 설정

접속모드 종류  

```c
typedef enum WiFiMode 
{
    WIFI_OFF = 0, WIFI_STA = 1, WIFI_AP = 2, WIFI_AP_STA = 3,
    /* these two pseudo modes are experimental: */ WIFI_SHUTDOWN = 4, WIFI_RESUME = 8
} WiFiMode_t;
```

일부 공유기에서 AP_STA 모드가 제데로 동작하지않는 경우가 있다.  
에> 공유기 내부 네트워크 안에서 esp가 패킷을 받을수 있지만 패킷을 보내지 못한다.

WiFi.mode() 이용하여 접속모드를 명시해서 지정해야함.  

```c
WiFi.mode(WIFI_STA);
```

### 접속 관리 

WiFi.begin(ssid, passwd) 함수로 접속시작  
WiFi.disconnect() 함수로 이전 연결 끊기 , WiFi.begin 호출전에 딜레필요함.  
WiFi.status() 함수로 접속 여부 판단.

```c
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

  Serial.printf("Connected, IP address: %s \n",WiFi.localIP());
```
