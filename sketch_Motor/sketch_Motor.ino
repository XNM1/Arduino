#define IN1 2
#define IN2 4
#define IN3 7
#define IN4 8
void setup() {
   for (int pin=IN1; pin<=IN4; pin++) {
    pinMode(pin,OUTPUT);
   } 
}
void loop() {
  Stop(3000);
  Forward(2000);
  Left(300);
  Forward(1000);
}
 void Left(int duratation){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(duratation);
}
 void Right(int duratation){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(duratation);
}
 void Backward(int duratation){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(duratation);
}
 void Forward(int duratation){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(duratation);
}
 void Stop(int duratation){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  delay(duratation);
}
