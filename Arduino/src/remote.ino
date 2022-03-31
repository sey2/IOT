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

/* 도(1), 레(2), 미(3), 파(4), 솔(5), 라(6), 시(7), 도(8)*/
int toneArray[] = {262, 294, 330, 349, 392, 440, 494, 523};

/* 1 ~ 8 번 버튼을 눌렀을 때 들어오는 데이터를 담은 배열 */
uint32_t remoteDataArr[] = {4077715200, 3877175040, 2707357440, 4144561920};

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
        else{
              playTone(myRawData);
        }
     
        /*
        else if (myRawData == 4077715200) { 
              playTone(262);
              Serial.println("Pressed 1 Button");
        }
        else if (myRawData == 3877175040) {       
              playTone(294);
              Serial.println("Pressed 2 Button");
        }
        else if (myRawData == 2707357440) {       
              playTone(330);    
              Serial.println("Pressed 3 Button");
        }
        else if (myRawData == 4144561920) {               
              playTone(349);
              Serial.println("Pressed 4 Button"); 
        }
        */

          
        IrReceiver.resume(); // receive the next value
       
    }      delay(30);
}


void ledBrightness(int brightness){
   IrReceiver.stop();
   analogWrite(ledPin, brightness); 
   IrReceiver.start(8000);  
}

/*

void playTone(int toneData){
   IrReceiver.stop();    // 멈추고 다시 시작을 안해주면 처음 누를 땐 정확한 값이 나오는데 그렇지 않으면 계속 쓰레기 값 나옴
   tone(TONE_PIN, toneData, 500);  
   IrReceiver.start(8000);
}
*/


void playTone(int myRawData){
   for(int i=0; i=6; i++){
      if(myRawData == remoteDataArr[i]){
        IrReceiver.stop();    // 멈추고 다시 시작을 안해주면 처음 누를 땐 정확한 값이 나오는데 그렇지 않으면 계속 쓰레기 값 나옴
        tone(TONE_PIN, toneArray[i], 500);
        IrReceiver.start(8000);
        Serial.println((String)"Pressed " + i+1 + (String)" Button");
        return;
      }  
   }
}
