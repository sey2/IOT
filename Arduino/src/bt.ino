#include<SoftwareSerial.h>

SoftwareSerial BTSerial(2,3);

void setup(){
  Serial.begin(9600);
  BTSerial.begin(9600);
  Serial.println("Initialized");
}

void loop()
{

  // 블루투스 모듈 --> 아두이노 --> 시리얼 모니터
  if(BTSerial.available()){
    Serial.write(BTSerial.read());
  }

  // 시리얼 모니터 --> 아두이노 --> 블루투스 모듈
  if(Serial.available()){
    char ch = Serial.read();
    Serial.write(ch);
    BTSerial.write(ch);
  }
}
