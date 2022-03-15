int serialNo=13;
int val = 0;
void setup()
{
  	/* 시리얼 통신 9600 bps 속도로 시작 */
  	Serial.begin(9600);	
  
	pinMode(serialNo, INPUT);
 
}

void loop()
{
  val = digitalRead(serialNo);
  Serial.println(val);
  delay(100);	// 다운싱 현상 방지
 
}