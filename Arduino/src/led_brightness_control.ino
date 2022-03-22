int led1= 3;
int led2= 11;
  
void setup()
{ 
	pinMode(led1, OUTPUT);
  	pinMode(led2, OUTPUT);
 
}

void loop()
{
	analogWrite(led1, 50);
  	analogWrite(led2, 255);
}