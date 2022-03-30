#include <IRremote.hpp>
#include <Arduino.h>
 
#include "PinDefinitionsAndMore.h"

int ledPin = 9;
void setup() {
    Serial.begin(9600);
    
    Serial.println("Start");  // Print Start

    IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK); // or IrReceiver.enableIRIn();  Start receiver

     // led 핀 출력 설정
    pinMode(ledPin, OUTPUT);
}

int brightness = 0;

int toneArray[] = {523, 587, 659, 698};
void loop() {
    if (IrReceiver.decode()) {
        Serial.println();
        
        uint32_t myRawData = IrReceiver.decodedIRData.decodedRawData;
        Serial.println(myRawData,DEC);

        
        if (myRawData == 3927310080) {  /* + */
             brightness += (brightness + 50 <= 255) ? 50 : 0;
             ledBrightness(brightness);
             Serial.println("Pressed + Button");
        }
        else if (myRawData == 4161273600) { /* - */
              brightness -= (brightness - 50 >= 0) ? 50 : 0;
              ledBrightness(brightness);
              Serial.println("Pressed - Button");
        }
        else if (myRawData == 4077715200) { /*  도 (1) */
              playTone(523);
              Serial.println("Pressed 1 Button");
        }
        else if (myRawData == 3877175040) { /* 레(2) */        
              playTone(587);
              Serial.println("Pressed 2 Button");
        }
        else if (myRawData == 2707357440) { /* 미(3) */        
              playTone(659);    
              Serial.println("Pressed 3 Button");
        }
        else if (myRawData == 4144561920) { /* 파(4) */              
              playTone(698);
              Serial.println("Pressed 4 Button"); 
        }
        IrReceiver.resume(); // receive the next value
       
    }      delay(30);
}

void ledBrightness(int brightness){
   IrReceiver.stop();
   analogWrite(ledPin, brightness); 
   IrReceiver.start(8000);  
}

void playTone(int toneData){
   IrReceiver.stop();    // 멈추고 다시 시작을 안해주면 처음 누를 땐 정확한 값이 나오는데 그렇지 않으면 계속 쓰레기 값 나옴
   tone(TONE_PIN, toneData, 500);  
   IrReceiver.start(8000);
}

