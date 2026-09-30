int speed = 50;

void setup() {   digitalWrite(tx,LOW); //transmit 
  delay(1);
   digitalWrite(tx,HIGH); //transmit 
  delay(1);
   digitalWrite(tx,LOW); //transmit 
  delay(1);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
}

void loop() {
  analogWrite(8, speed);
}