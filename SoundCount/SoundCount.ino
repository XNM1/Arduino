#include <LiquidCrystal.h>
#include <HCSR04.h>

#define Oy A0
#define Ox A1
#define Button 6
#define p 7

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
UltraSonicDistanceSensor distanceSensor1(8, 13);
UltraSonicDistanceSensor distanceSensor2(9, 10);

unsigned int max_count = 10;
unsigned int cur_count = 0;

unsigned short d1_trig = 0;
unsigned short d2_trig = 0;

bool d1_set = false;
bool d2_set = false;

unsigned short i = 0;
unsigned short c = 0;

bool alarm = true;

const unsigned short min_dist = 20;
const unsigned short max_dist = 100;

void setup() {
  lcd.begin(16, 2);
  pinMode(Ox, INPUT);
  pinMode(Oy, INPUT);
  pinMode(Button, INPUT_PULLUP);
  display_count();
}

void loop() {
  check_sensors_state();
  set_cur_count();
  set_max_count();
  display_count();
  check_alarm();
  check_state();
  if(i == 8) {
    i = 0;
    refresh();
  }
  delay(500);
}

void check_sensors_state() {
  double distance1 = distanceSensor1.measureDistanceCm();
  double distance2 = distanceSensor2.measureDistanceCm();
  if (distance1 > min_dist && distance2 > min_dist){
    i++;
  }
  if (distance1 < min_dist && distance2 > min_dist) {
    d1_set = true;
  }
  else if (distance2 < min_dist && distance1 > min_dist) {
    d2_set = true;
  }

  if (d1_set && distance1 > max_dist && d1_trig == 0) {
    c++;
    d1_trig = c;
    d1_set = false;
  }
  else if (d2_set && distance2 > max_dist && d2_trig == 0) {
    c++;
    d2_trig = c;
    d2_set = false;
  }
}

void set_cur_count() {
  if(d1_trig < d2_trig && cur_count < 1000 && c == 2) {
    cur_count++;
    refresh();
  }
  else if(d2_trig < d1_trig && cur_count > 0 && c == 2) {
    cur_count--;
    refresh();
  }
}

void refresh() {
  c = 0;
  d1_trig = 0;
  d2_trig = 0;
  d1_set = false;
  d2_set = false;
}

void check_state() {
  if (alarm && cur_count > max_count) {
    tone(p, 3000, 50);
  }
}

void check_alarm() {
  if (digitalRead(Button) == LOW) {
    alarm = !alarm;
  }
}

void set_max_count() {
   if (analogRead(Ox) > 960 && max_count < 1000) {
    max_count++;
    display_count();
  }
  else if (analogRead(Ox) < 200 && max_count > 1) {
    max_count--;
    display_count();
  }
}

void display_count() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Max Users: ");
  lcd.setCursor(10, 0);
  lcd.print(max_count, DEC);
  lcd.setCursor(0, 1);
  lcd.print("Cur Users: ");
  lcd.setCursor(10, 1);
  lcd.print(cur_count, DEC);
}
