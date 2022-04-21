#include <DHT.h>
#include<Stepper.h>

#define DHTTYPE DHT11
#define DHTPIN 2

const int rotation180 = 1024;   // 180도 회전

Stepper myStepper(rotation180, 8, 10, 11 , 9);

int buttonA = 4;
int buttonB = 5;

boolean autoMode = true; // 초기 설정은 자동모드
boolean blindState = true; //  블라인드 업(true)/다운 (false)

DHT dht(DHTPIN, DHTTYPE);

/* 컴퓨터 공학과 20184494 박세영
 *  스마트폰을 가까이 댈때의 조도 센서 값은 200 이상으로 지정 하였습니다. 
 * 버튼 데이터 값, 온도, 밝기 데이터를 확인하고 싶으면 loop() 메서드의 printDebug() 메서드의 주석을 푸시면 됩니다. 
 * 버튼 A,B를 누를 때 1.5초 정도 눌러 주세요, 바로 눌렀다 때면 버튼 값을 잘 못 읽을 수 있습니다. 
 * 자동 모드일 때 블라인드가 계속 작동하지 않게 하기 위해 반 바퀴 회전을 하고, 감
 * 똑같은 상태에서 블라인드가 작동하게 되면 블라인드가 끝까지 내려감 / 올라감 메시지가 나옵니다. 
 * 밝기 / 온도 상태를 바꾸면 블라인드가 반대로 다시 작동 합니다. 
 * EX) 블라인드가 끝까지 올라감 메시지가 나왔을때 스마트폰 후레시를 조도 센서에 가까이 대면 블라인드가 내려감
 */

void setup() {
  myStepper.setSpeed(14);

  pinMode(buttonA, INPUT);
  pinMode(buttonB, INPUT);

  Serial.begin(9600);
  Serial.println("start");
  dht.begin();

}

int cdsValue;     // 조도센서 값
int buttonA_State;  // 버튼 A 플래그
int buttonB_State;  // 버튼 B 플래그전

float tem;  // 온도를 담기 위한 변수 

boolean upFlag = true;    // 블라인드를 올릴 수 있으면 true (블라인드가 다 올라가지 않았으면), 블라인드를 내릴 수 있으면 false (블라인드가 다 내려가지 않았으면)

void loop() {
  motor();      // 자동 모드/수동 모드 값과 블라인드를 더 이상 올리거나 내릴 수 있는지 없는지 확인 후 블라인드 작동

  readData();

  if (isnan(tem)) {
    Serial.print(F("Failed to read from DHT sensor!"));
    return;
  }


  if (buttonA_State == HIGH) {   // A가 버튼이 눌리면 자동/수동 변환
    autoMode = !autoMode;
    checkMode();
  }


  // printDebug();  // 온도, 버튼 상태, 밝기 값 확인용 메서드 

  delay(1000);

}

boolean printAble = true;   // 블라인드 안내 메시지 한번만 출력되게 하기 위한 flag 변수 

void motor() {
  if (autoMode) { // 자동 모드일 때

    if (cdsValue >= 200 && tem >= 25 && blindState)   // 스마트폰 라이트를 빛추었을 때 && 온도가 25도 이상 && 블라인드가 더 내려 갈 수 있으면 
      blindDown();
      
    else if (cdsValue >= 200 && tem >= 25 && ! blindState && printAble) { // 위 상태에서 블라인드가 더 내려 갈 수 없으면 
      Serial.println("블라인드가 끝까지 내려 갔습니다.");
      printAble = false;
    }
    
    else if (cdsValue >= 200 && tem < 25 && !blindState)  // 스마트폰 라이트를 빛추었을 때 && 온도가 25도 미만 && 블라인드가 더 올라 갈 수 있으면
      blindUp();

    else if (cdsValue >= 200 && tem < 25 && blindState && printAble){   // 위 상태에서 블라인드가 더 올라 갈 수 없으면 
      Serial.println("블라인드가 끝까지 올라 갔습니다.");
      printAble = false;
    }

    else if (cdsValue < 200 && tem >= 25 && !blindState)  // 스마트폰 라이트를 빛추지 않았을 때 && 온도가 25도 이상 && 블라인드가 더 올라 갈 수 있으면
      blindUp();

    else if(cdsValue < 200 && tem >= 25 && blindState && printAble) {   // 위 상태에서 블라인드가 더 올라 갈 수 없으면 
       Serial.println("블라인드가 끝까지 올라 갔습니다.");
       printAble = false;
    }

    else if (cdsValue < 200 && tem < 25 && blindState)    // 스마트폰 라이트를 빛추지 않았을 때 && 온도갖 25도 미만 && 블라인드가 더 내려갈 수 있으면
      blindDown();
      
    else if(cdsValue < 200 && tem < 25 && !blindState && printAble) {   // 위 상태에서 블라인드가 더 내려 갈 수 없으면 
        Serial.println("블라인드가 끝까지 내려 갔습니다.");
        printAble = false;
    }
   
  } else { // 수동 모드 일 떄
    
    if (buttonB_State == HIGH) {
      (blindState == true) ? blindDown() : blindUp();   // B 버튼을 누를때 마다 블라인드를 올리고 내림 
    }
    
  }
}

void blindUp() {
  Serial.println("블라인드 올림");
  myStepper.step(rotation180);    // 반 시계방향으로 180도 회전 (블라인드 올림)
  blindState = true;
  printAble = true;
}
void blindDown() {
  Serial.println("블라인드 내림");
  myStepper.step(-rotation180);   // 시계 방향으로 180도 회전  (블라인드 내림)
  blindState = false;
  printAble = true;
}


void checkMode() {
  if (autoMode == true) {
    Serial.println("수동 모드 -> 자동 모드 변환");
  } else {
    Serial.println("자동 모드 -> 수동 모드 변환");
  }
}

void readData() {
  cdsValue = analogRead(A0);  // 조도 센서 값 읽기 
  buttonA_State = digitalRead(buttonA);   // 눌리면(1) 자동/수동 전환
  buttonB_State = digitalRead(buttonB);   // 눌리면(1) 수동 모드에서 올림/내림 전환

  tem = dht.readTemperature();

}


// 데이터 값 확인용 메서드
void printDebug() {
  Serial.println(" -------- ");
  Serial.print("버튼A 상태: "); Serial.println(buttonA_State);
  Serial.print("버튼B 상태: "); Serial.println(buttonB_State);
  Serial.print("밝기: "); Serial.println(cdsValue);  // 스마트폰 빛 비추었을 때 200이상 안 비추었을때 100 미만
  Serial.print("온도: "); Serial.print(tem);
  Serial.println("C");
}
