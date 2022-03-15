int led[] = {4, 6, 8};
int size = sizeof(led) / sizeof(int);

void setup()
{
  
  for(int i=0; i<size; i++)
    pinMode(led[i], OUTPUT);

}

void loop()
{
   for(int i=0; i<size; i++)
    digitalWrite(led[i],HIGH);
  
  delay(1000);
  
 for(int i=0; i<size; i++)
    digitalWrite(led[i],LOW);
  
  delay(1000); 
}