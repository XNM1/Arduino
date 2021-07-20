#include <NewPing.h>
#include <Servo.h>
#include <SoftwareSerial.h>

#define PIR_sensor 13
#define Botton_Plus 9
#define Botton_Minus 10
#define IN1 4
#define IN2 5
#define IN3 3
#define IN4 8
#define TRIG 12
#define ECHO 11
#define MAX_DISTANSE 200
NewPing sonar(TRIG,ECHO,MAX_DISTANSE);
Servo myservo;
SoftwareSerial mySerial(6,7);
const int angle_array[13]={0,15,30,45,60,75,90,105,120,135,150,165,180};
const int min_distance=30;
int distance_array[13];
int servo_counter;
int maxarrayindex;
int maxarrayvalue;
char cmd;
int mode = 0;
int premode = -1;
void setup() {
   //randomSeed(analogRead(0));
   myservo.attach(2);
   myservo.write(90);
   mySerial.begin(9600);
   //delay(1000);
   Serial.begin(9600);
   pinMode(Botton_Plus,INPUT_PULLUP);
   pinMode(Botton_Minus,INPUT_PULLUP);
   pinMode(PIR_sensor,INPUT);
}
void loop() {
  if (digitalRead(Botton_Plus)==HIGH) {
   mode+=1;
   premode-=1;
      if (mode>3) {
       mode=0;
       premode=3;
      }
      delay(150);
  }
  if (digitalRead(Botton_Minus)==HIGH) {
   mode-=1;
   premode+=1;
       if (mode<0) {
           mode=3;
           premode=0;
       }
       delay(150);
 }
   switch (mode) {
    case 0:
      Stop();
      break;
    case 1:
      ultrasound_mode();
      break;
    case 2:
      bt_mode();
      break;
    case 3:
      hunt_mode();
      break;
   }
  Serial.println(mode);
}
void hunt_mode() {
  if (digitalRead(PIR_sensor)==HIGH) {
    Forward();
      if (getDistanse() !=0 && getDistanse() <= min_distance) {
       Stop(); 
      }
  }
  else {
    Stop();
  } 
}
void bt_mode() {
 /*
 S-стоп
 B-назад
 F-вперёд
 L-влево
 R-вправо
 */
 if (mySerial.available()) {
	cmd = mySerial.read();
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
void ultrasound_mode() {
    Serial.print("Now:");
    Serial.println(getDistanse());
    if (getDistanse() !=0 && getDistanse() <= min_distance) {
      Stop();
      for(servo_counter=0; servo_counter<13; servo_counter+=1) {
        myservo.write(angle_array[servo_counter]);
        delay(50);
        distance_array[servo_counter] = getDistanse();
        Serial.print(servo_counter);
        Serial.print(" ");
        Serial.println(distance_array[servo_counter]);
      }
    myservo.write(90);
    delay(250);
    maxarrayindex=0;
    maxarrayvalue=0;
    for (servo_counter=0; servo_counter<13; servo_counter+=1) {
      if (maxarrayvalue<distance_array[servo_counter]) {
       maxarrayvalue=distance_array[servo_counter];
       maxarrayindex=servo_counter;
      }
    }
    if (distance_array[maxarrayindex]<min_distance) {
    Backward();
    delay(600);
    Serial.println("Going backward!");
    }
    int tmp2 = 0;
    for (int tmp=4; tmp<9; tmp++) {
     if (distance_array[tmp]< min_distance) {
      tmp2++;
       }
    }
    if (tmp2 > 3) {
     Backward();
     delay(500);
     tmp2=0; 
    }
    if (maxarrayindex < 6) {
      Right();
      delay(35);
      Serial.println("Right!");
    }
    else {
     Left();
     delay(35);
     Serial.println("Left!");
    }
    Serial.print("Max array index is: ");
    Serial.println(maxarrayindex);
    Serial.print("Max array value is: ");
    Serial.println(maxarrayvalue);
  }
  else {
   Forward();
   delay(1); 
   Serial.println("Forward!");
  }
}
int getDistanse() {
  int distanse = sonar.convert_cm(sonar.ping_median(4));
  return distanse;
}
 void Right(){ 
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  //delay(duratation);
}
 void Left(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  //delay(duratation);
}
 void Forward(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  //delay(duratation);
}
 void Backward(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  //delay(duratation);
}
 void Stop(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  //delay(duratation);
}
