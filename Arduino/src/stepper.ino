#include<Stepper.h>
// 2048: 한바퀴(360 도), 1024: 반바퀴(180도)...
const int stepsPerRevolution = 2048;
// Stapper class의 인스턴스인 myStepper를 생성
// 아두이노 보드의 디지털8,9, 10, 11번 핀을
// 스테퍼 모터 드라이브의 IN1, IN3, IN2, IN4에 연결
// 인스턴스 생성시1-3-2-4 순서로 대응되는핀 번호 입력
Stepper myStepper(stepsPerRevolution,8, 10,9, 11);
void setup() {
  myStepper.setSpeed(14); // 스테퍼 모터의 스피드 설정
}
void loop() {
  // 시계 반대 방향으로  한 바퀴 회전
  myStepper.step(stepsPerRevolution); 
  delay(500);
  // 시계 방향으로 한 바퀴 회전
  myStepper.step(-stepsPerRevolution);
  delay(500);
}