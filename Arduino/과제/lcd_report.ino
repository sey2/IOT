#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int delayTime = 100;  // 100ms ~ 500ms
int switchPin = 4;  // 스위치는 디지털 핀 4

boolean leftRight = false;    // 현재 방향이 왼쪽 -> 오른쪽 
boolean rightLeft = true;     // 현재 방향이 오른쪽 -> 왼쪽
boolean changeDir = false;    // 방향 전환 필요 true, 불필요 false

void setup() {
  Serial.begin(9600);
  pinMode(switchPin, INPUT); // 스위치 디지털 핀 4를 입력으로 설정
  lcd.init();   // lcd 패널 초기화
  lcd.clear();    // lcd 화면의 모든 문자를 지움
  lcd.backlight();  // lcd 백 라이트 켬

  lcd.setCursor(0, 0);  // 커서를 0행 0열로 이동 (0,0)
  lcd.print("Hello everyone! My name is Park Se Young");    //(0,0)에 문자열 출력

  lcd.setCursor(0, 1);  // 커서를 1행 0열로 이동 
  lcd.print("Chosun University, ID:20184494");    // (0,1)에 문자열 출력

}

void loop() {
  moveLcd();      // 방향, 속도를 결정해주고 스크롤을 해준다.
  delay(delayTime);
}

void moveLcd() {
  int inputResistor = analogRead(A0) / 2;   // 가변 저항 아날로그 입력 A0에서 데이터를 읽기

  if(digitalRead(switchPin) == HIGH){   // 스위치가 눌렸으면 방향 전환
    changeDir = !changeDir;
  }

  if(changeDir && rightLeft){   // 방향 전환이 필요하고 현재 방향이 오른쪽 -> 왼쪽이면 
    lcd.scrollDisplayRight();
    rightLeft = false;
    leftRight = true;
  }else if(changeDir && leftRight){ // 방향 전환이 필요하고 현재 방향이 왼쪽 -> 오른쪽 이면
    lcd.scrollDisplayLeft();
    rightLeft = true;
    leftRight = false;
  }else if(!changeDir){   // 스위치가 안눌렸으면
    (rightLeft == true) ? lcd.scrollDisplayLeft():lcd.scrollDisplayRight();
  }

  Serial.println(changeDir);  // 값 변화 확인하기 위함
  Serial.println(delayTime);  // 값 변화 확인하기 위함
  
  delayTime = resizeInput(inputResistor);       // 가변 저항에서 읽은 아날로그 값을 이용해 스크롤 속도 제어를 하기 위해 resize
  changeDir = false;
}


// 가변 저항의 값은 10비트 즉 1~1023 값을 읽어온다.
// 0.1초 ~ 0.5초 즉 100ms ~ 500ms의 값을 맞춰 주기 위해 (가변 input / 2)를 한다.
// 2로 나눠서 나온 값이 100보다 작은 경우와 500보다 큰 값이 나올 수 있기 때문에 값을 재 조정해주는 함수
int resizeInput(int input) {
  if (input <= 100)
    return 100;
  else if (input >= 500)
    return 500;
  else
    return input;
}
