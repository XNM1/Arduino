#define sen_x A0
#define sen_y A1
#define sen_butt 3
#define Buzzer 11
void setup() {
  pinMode(sen_x,INPUT);
  pinMode(sen_y,INPUT);
  pinMode(sen_butt,INPUT_PULLUP);
  pinMode(Buzzer,OUTPUT);
  Serial.begin(9600);
}
int gerc = 16;
void loop() {
  int x,y,k;
  k = digitalRead(sen_butt);
  x = analogRead(sen_x);
  y = analogRead(sen_y);
  if (y >= 500) {
    gerc+=y/10;
  }
  else if (y <= 400) {
    gerc-=(y+1)*10;
    gerc = constrain(gerc,1,4000);
  }
  else if (k == 0) {
    noTone(Buzzer);
  }
  tone(Buzzer,gerc);
  delay(500);
  Serial.println(gerc);
}
