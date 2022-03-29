#include <IRremote.hpp>
#include <Arduino.h>

/*
 * Define macros for input and output pin etc.
 */
#include "PinDefinitionsAndMore.h"

void setup() {
    Serial.begin(9600);

    // led 핀 출력 설정
    pinMode(9, OUTPUT);
    
    Serial.println("Start");  // Print Start

    IrReceiver.enableIRIn();
    IrReceiver.begin(11, DISABLE_LED_FEEDBACK); // Start receiver
}

void loop() {

    if (IrReceiver.decode()) {

        Serial.println();

        Serial.println(IrReceiver.decodedIRData.decodedRawData,DEC);
        
        if (IrReceiver.decodedIRData.decodedRawData == 3927310080) {  /* + */
             Serial.println("Pressed + Button");
             analogWrite(9, 50);
        }
        else if (IrReceiver.decodedIRData.decodedRawData == 4161273600) { /* - */
              analogWrite(9, 255);  
              Serial.println("Pressed - Button");
        }
        else if (IrReceiver.decodedIRData.decodedRawData == 4077715200) { /*  도 (1) */
              Serial.println("Pressed 1 Button");
              IrReceiver.stop();    // 멈추고 다시 시작을 안해주면 처음 누를 땐 정확한 값이 나오는데 그렇지 않으면 계속 쓰레기 값 나옴
              tone(3,523,1000); 
              delay(8);
              IrReceiver.start(8000);
        }
        else if (IrReceiver.decodedIRData.decodedRawData == 3877175040) { /* 레(2) */
              Serial.println("Pressed 2 Button");
              IrReceiver.stop();
              tone(3,587,1000); 
              delay(8);
              IrReceiver.start(8000);
        }
        else if (IrReceiver.decodedIRData.decodedRawData == 2707357440) { /* 미(3) */
              Serial.println("Pressed 3 Button");
              IrReceiver.stop();
              tone(3,659,1000);
              delay(8);
              IrReceiver.start(8000);      
        }
        else if (IrReceiver.decodedIRData.decodedRawData == 4144561920) { /* 파(4) */
              Serial.println("Pressed 4 Button");
              IrReceiver.stop();
              tone(3,698,1000);  
              delay(8);
              IrReceiver.start(8000);      
        }
        IrReceiver.resume(); // receive the next value
       
    }      delay(30);
}
