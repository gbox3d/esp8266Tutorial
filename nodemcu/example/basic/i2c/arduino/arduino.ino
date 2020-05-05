#include <Wire.h>

const int g_nVersion = 100;
const int g_DeviceID = 0x1b;

const int g_ledPin = 13;

struct _S_Packet {
  byte m_nSkima;
  int m_nNum;
//  char m_szBuf[8];
//  float m_fVal;
  // float m_ffVal;
  // int m_aList[4];
};

int testData[8] = {1,2,3,4,5,6,7,8};

void receiveEvent(int howMany)
{
  int _index = 0;
  byte _opBuf[32];
//  Serial.print(sizeof(_index));
  while (0 < Wire.available())
  {
    int c = Wire.read();
    Serial.println(c);
    
    _opBuf[_index++] = c;
    

    if(_index >= howMany) {
      
      Serial.print("index : ");
      Serial.println(String(_index));
      Serial.print("howmany : ");
      Serial.println(String(howMany));
      
      _S_Packet *pkt = (_S_Packet *)_opBuf;
      Serial.println( String(pkt->m_nSkima) );
      Serial.println( String(pkt->m_nNum) );
//      Serial.println(pkt->m_szBuf);
//      Serial.println( String(pkt->m_fVal) );
    }
  }

  

  //Serial.println(howMany);

}

void requestEvent()
{
//  Serial.println("requestEvent");
  Wire.write( (unsigned char *)testData,8 * sizeof(int));
}



void setup()
{
  Wire.begin(g_DeviceID);       // 자신의 주소를  설정하고 i2c 버스에 참여
  Wire.onReceive(receiveEvent); // 수신 이벤트 함수 등록
  Wire.onRequest(requestEvent);

  Serial.begin(115200);
  Serial.println("ready");
  pinMode(g_ledPin,OUTPUT);
  digitalWrite(g_ledPin,LOW);

  
}

void loop()
{
  
}
