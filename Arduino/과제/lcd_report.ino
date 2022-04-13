#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

char arr1[] = "Hello everyone! My name is Park Se Young";
char arr2[] = "Chosun University, ID:20184494";

int delayTime = 100;  // 100ms ~ 500ms
int switchPin = 4;  // 스위치는 디지털 핀 4

boolean right_toLeft = true;  // true = 오른쪽 -> 왼쪽, false = 왼쪽 -> 오른쪽

void setup() {

  pinMode(switchPin, INPUT); // 스위치 디지털 핀 4를 입력으로 설정
  lcd.init();
  lcd.backlight();

}

void loop() {
  int inputResistor = analogRead(A0) / 2;   // 가변 저항 아날로그 입력 A0에서 데이터를 읽기         
  
  right_toLeft = (digitalRead(switchPin) == 0) ? !right_toLeft : right_toLeft;  // 버튼을 누르면 방향을 바꿈 
  
  delayTime = resizeInput(inputResistor);
  
  lcd.setCursor(15,0);

  for(int posCnt=0; posCnt < 26; posCnt++){
    (right_toLeft == true) ? lcd.scrollDisplayLeft() : lcd.scrollDisplayRight(); // 출력되는 문자열을 오른쪽 또는 왼쪽으로 이동 
    lcd.print(arr1[posCnt]);
    delay(delayTime);
  }

  lcd.clear();    // LCD 화면을 지우고 커서를 왼쪽 상단에 위치
  lcd.setCursor(15,1);   // 커서 1번 행, 15번 열로 이동

  for(int posCnt=0; posCnt < 26; posCnt++){
    (right_toLeft == true) ? lcd.scrollDisplayLeft() : lcd.scrollDisplayRight(); // 출력되는 문자열을 오른쪽 또는 왼쪽으로 이동
    lcd.scrollDisplayLeft();  // 출력되는 문자열을 왼쪽으로 한 칸씩 이동
    lcd.print(arr2[posCnt]);
    delay(delayTime);
  }

  lcd.clear();

}

int resizeInput(int input){
  if(input <= 100)
     return 100;
  else if (input >= 500)
     return 500;
  else
     return input;
}
