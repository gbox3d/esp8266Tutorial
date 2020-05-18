## WiFiUDP

### 포트 오픈 
WiFiUDP:begin(listenPort)  
: udp소켓을 오픈한다. listenPort가 0일 경우 랜덤하게 포트를 연다.  

### 보내기  

beginPacket(ip주소,원격포트)  
write 와 같은 stream 객체 지원하는 함수 사용 스트림으로 버퍼에 데이터 넣기  
endPacket 으로 버퍼에있는 데이터 원격전송  

```c

....

WiFiUDP Udp;

....


  {
    S_Packet testPacket;
    memset(&testPacket, 0, sizeof(S_Packet));
    testPacket.m_header = 99;
    testPacket.m_code = 81;
    testPacket.m_index = 15001;
    testPacket.m_sensorData = 96.75;

    Serial.printf("udp packet send to %s ... \n", remoteIp.c_str());
    Udp.beginPacket(remoteIp.c_str(), remoteUdpPort);
    Udp.write((const char *)&testPacket, sizeof(S_Packet));
    Udp.endPacket();
  }
```

### 받기  

```c


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


```

