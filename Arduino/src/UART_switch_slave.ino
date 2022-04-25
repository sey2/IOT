int pin_LED1 = 13;
int pin_LED2 = 12;
int received_data = 5;

void setup() {
  // put your setup code here, to run once: Serial.begin(9600);
  Serial.print("Sketch: ");

  pinMode(pin_LED1, OUTPUT);
  pinMode(pin_LED2, OUTPUT);
}


void loop() {
  if (Serial.available()) {
    received_data = Serial.read();

    if (received_data == 0) {
      digitalWrite(pin_LED1, LOW);
      Serial.println("Received Data 0");
     }
    if(received_data == 1){
      digitalWrite(pin_LED1, HIGH);
      Serial.println("Received Data 1");
    }
    if (received_data == 2) {
      digitalWrite(pin_LED2, LOW);
      Serial.println("Received Data 2");
     }
    if(received_data == 3){
      digitalWrite(pin_LED2, HIGH);
      Serial.println("Received Data 3");
    }
  }
}
