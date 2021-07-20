#include <Servo.h> 
#include <SoftwareSerial.h>

Servo Leg_1;
Servo Leg_2;
Servo Leg_3;
SoftwareSerial BT(6, 5);

char cmd;

void setup() { 
  // 40 90 140 leg
  BT.begin(9600);
  Leg_1.attach(10);
  Leg_2.attach(11);
  Leg_3.attach(12);
  Leg_1.write(90); 
  Leg_2.write(90); 
  Leg_3.write(90);
  Serial.begin(9600);  
}

void loop() {
  bt_mode();
}


void bt_mode() {
 /*
 S-стоп
 B-назад
 F-вперёд
 L-влево
 R-вправо
 */
 if (BT.available()) {
  cmd = BT.read();
  if (cmd=='S') {
    Stop();
    //delay(50);
    Serial.println("Stop");
  }
    if (cmd=='F') {
    Forward();
    delay(50);
    Stop();
    Serial.println("Forward");
  }
    if (cmd=='B') {
    Backward();
    delay(50);
    Stop();
  }
    if (cmd=='L') {
    Left();
    delay(50);
    Stop();
  }
    if (cmd=='R') {
    Right();
    delay(50);
    Stop();
  }
 }
 //Serial.println(cmd);
}

void Forward() {
  Leg_3.write(40);
  delay(500);
  Leg_1.write(40);
  delay(500);
  Leg_2.write(120);
  delay(500);
  Leg_3.write(90);
  delay(500);
  Leg_1.write(140);
  Leg_2.write(40);
  Leg_3.write(40);
  delay(500);
}

void Backward() {
  Leg_3.write(120);
  delay(500);
  Leg_1.write(140);
  delay(500);
  Leg_2.write(40);
  delay(500);
  Leg_3.write(90);
  delay(500);
  Leg_1.write(40);
  Leg_2.write(120);
  Leg_3.write(120);
  delay(500);
}

void Left() {
  Leg_3.write(40);
  delay(500);
  Leg_1.write(140);
  delay(500);
  Leg_2.write(120);
  delay(500);
  Leg_3.write(90);
  delay(500);
  Leg_2.write(40);
  Leg_1.write(40);
  Leg_3.write(40);
  delay(500);
}

void Right() {
  Leg_3.write(40);
  delay(500);
  Leg_1.write(40);
  delay(500);
  Leg_2.write(40);
  delay(500);
  Leg_3.write(90);
  delay(500);
  Leg_1.write(140);
  Leg_2.write(120);
  Leg_3.write(40);
  delay(500);
}

void Stop() {
  Leg_1.write(90);
  Leg_2.write(90);
  Leg_3.write(90);
}
