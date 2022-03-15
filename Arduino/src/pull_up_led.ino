int buttonPin=13;
int ledPin=6;
  
void setup()
{
  	/* 시리얼 통신 9600 bps 속도로 시작 */
  	Serial.begin(9600);	
  
	pinMode(buttonPin, INPUT);
  	pinMode(ledPin,OUTPUT);
 
}

int val = 0;

void loop()
{
  val = digitalRead(buttonPin);
  Serial.println(val);
  
  if(val == LOW) digitalWrite(ledPin, HIGH);
  if(val == HIGH) digitalWrite(ledPin,  LOW);
  
  delay(100);	// 다운싱 현상 방지
 
}