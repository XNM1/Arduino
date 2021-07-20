#include <Servo.h>
#include <SoftwareSerial.h>

Servo MyServo[8];
SoftwareSerial BT(12, 13);
const int Angle[8] = {66, 90, 127, 76, 129, 111, 129, 94};
int tmp = 1;

void setup() {
  for (int i = 0; i < 8; i++) {
    MyServo[i].attach(i + 4);
    MyServo[i].write(Angle[i]);
  }
  BT.begin(9600);
}

void loop() {
  bt_mode();
}

void bt_mode(void) {
  if (BT.available()) {
    char c = BT.read();
    if (c == 'S') {
      //Stop();
    }
    if (c == 'F') {
      Forward();
    }
    if (c == 'B') {
      //Backward();
    }
    if (c == 'L') {
      //Left();
    }
    if (c == 'R') {
      //Right();
    }
    if (c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' || c == 'q') {
      UPDOWN(c);
    }
  }
}



void Stop(void) {
  for (int i = 0; i < 8; i++) {
    MyServo[i].detach();
    digitalWrite(i + 4, LOW);
  }
}

void UPDOWN(int j) {
  if (j == 113) {
    j = 10;
  }
  else {
    j-=54;
  }
  if (tmp < j) {
    for (int i = 1; i < 8; i+=2) {
      MyServo[i].write(Angle[i] - (5 * j));
    }
  }
  else {
     for (int i = 1; i < 8; i+=2) {
      MyServo[i].write(Angle[i] + (5 * j));
    }
  }
  tmp = j;
}


void Forward(void) {
 for (int i = 1; i < 3; i+=2) {
    MyServo[i].write(Angle[i] - 30);
 }
 for (int i = 5; i < 7; i+=2) {
    MyServo[i].write(Angle[i] + 30);
 }
 delay(100);
  for (int i = 1; i < 3; i+=2) {
    MyServo[i].write(Angle[i] + 30);
 }
 for (int i = 5; i < 7; i+=2) {
    MyServo[i].write(Angle[i] - 30);
 }
}

