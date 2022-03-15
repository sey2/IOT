int serialNo=13;

void setup()
{
  	/* 시리얼 통신 9600 bps 속도로 시작 */
  	Serial.begin(9600);	
  
	pinMode(serialNo, OUTPUT);
 
}

void loop()
{
 /* Serial Class 안에 avaiable 메소드가 있는데 Serial이 */
 /* 정상적으로 작동하는지 확인함 */
  
  if(Serial.available() > 0){
    
    /* Serial 케이블로 들어오는 시리얼 데이터를 읽음 */
    int input = Serial.read();
    
    /* Serial 모니터에 값을 나타나개 하는 명령어 */
    Serial.println(input);		
    
    if(input == '1')	digitalWrite(serialNo, HIGH);
   	if(input == '0')   	digitalWrite(serialNo,LOW);
  }
}