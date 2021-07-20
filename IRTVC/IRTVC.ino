#include <IRremote.h>
#include <IRremoteInt.h>
IRsend irwrite;

#include <LiquidCrystal.h>
LiquidCrystal lcd(6, 7, 9, 10, 11, 12);

#define Button_mode_pin 0
#define Button_power_pin 1
#define Oy A5
#define Ox A4

unsigned long power[] = {0x20DF10EF, 0xE0E040BF, 0x1000C, 0xa90, 0x02FD48B7};
unsigned long ch_p[] = {0x20DF00FF, 0xE0E048B7, 0x1004C, 0x90, 0x02FDD827};
unsigned long ch_m[] = {0x20DF807F, 0xE0E008F7, 0x1004D, 0x890, 0x02FDF807};
unsigned long vl_p[]= {0x20DF40BF, 0xE0E0E01F, 0x10010, 0x490, 0x02FD58A7};
unsigned long vl_m[] = {0x20DFC03F, 0xE0E0D02F, 0x10011, 0xC90, 0x02FD7887};

int count = 1;
int mode = 1;
unsigned long work_code[4];
int mode_tv = 1;

void setup() {
  lcd.begin(16, 2);
  pinMode(Button_mode_pin, INPUT_PULLUP);
  pinMode(Button_power_pin, INPUT_PULLUP);
  pinMode(Ox, INPUT);
  pinMode(Oy, INPUT);
  lcd.print("LG");
  lcd.setCursor(3, 0);
  lcd.print("SAMSUNG");
  lcd.setCursor(11, 0);
  lcd.print("SONY");
  lcd.setCursor(0, 1);
  lcd.print("PHILIPS");
  lcd.setCursor(8, 1);
  lcd.print("TOSHIBA");
  lcd.cursor();
}

void loop() {
  mode = Button_mode();
  switch (mode) {
    case 1:
      Mode_TV();
      break;
    case 2:
      TV_Control();
      break;
  }
}

int Button_mode() {
  if (digitalRead(Button_mode_pin) == LOW) {
    count++;
    delay(500);
  }
  if (count > 2) {
    count = 1;
  }
  return count;
}

int Mode_TV() {
  if (analogRead(Oy) > 1000) {
    mode_tv++;
    delay(500);
  }
  else if (analogRead(Oy) < 200) {
    mode_tv--;
    delay(500);
  }
  if (mode_tv > 5) {
    mode_tv = 1;
  }
  else if (mode_tv < 1) {
    mode_tv = 5;
  }
  switch (mode_tv) {
    case 1:
     lcd.setCursor(0, 0);
      work_code[0] = power[0];
      work_code[1] = ch_p[0];
      work_code[2] = ch_m[0];
      work_code[3] = vl_p[0];
      work_code[4] = vl_m[0];
      break;
    case 2:
     lcd.setCursor(3, 0);
      work_code[0] = power[1];
      work_code[1] = ch_p[1];
      work_code[2] = ch_m[1];
      work_code[3] = vl_p[1];
      work_code[4] = vl_m[1];
      break;
    case 3:
      lcd.setCursor(0, 1);
      work_code[0] = power[2];
      work_code[1] = ch_p[2];
      work_code[2] = ch_m[2];
      work_code[3] = vl_p[2];
      work_code[4] = vl_m[2];
      break;
    case 4:
      lcd.setCursor(11, 0);
      work_code[0] = power[3];
      work_code[1] = ch_p[3];
      work_code[2] = ch_m[3];
      work_code[3] = vl_p[3];
      work_code[4] = vl_m[3];
      break;
    case 5:
      lcd.setCursor(8, 1);
      work_code[0] = power[4];
      work_code[1] = ch_p[4];
      work_code[2] = ch_m[4];
      work_code[3] = vl_p[4];
      work_code[4] = vl_m[4];
      break;
  }
}

int TV_Control() {
  switch (mode_tv) {
    case 1:
      //LG
        if (digitalRead(Button_power_pin) == LOW) {
          irwrite.sendNEC(work_code[0], 32);
          delay(500);
        }
        if (analogRead(Oy) > 1000) {
          irwrite.sendNEC(work_code[1], 32);
          delay(500);
        }
        if (analogRead(Oy) < 200) {
          irwrite.sendNEC(work_code[2], 32);
          delay(500);
        }
        if (analogRead(Ox) > 1000) {
          irwrite.sendNEC(work_code[3], 32);
          delay(50);
        }
        if (analogRead(Ox) < 200) {
          irwrite.sendNEC(work_code[4], 32);
          delay(50);
        }
      break;
    case 2:
      //Samsung
        if (digitalRead(Button_power_pin) == LOW) {
          irwrite.sendNEC(work_code[0], 32);
          delay(500);
        }
        if (analogRead(Oy) > 1000) {
          irwrite.sendNEC(work_code[1], 32);
          delay(500);
        }
        if (analogRead(Oy) < 200) {
          irwrite.sendNEC(work_code[2], 32);
          delay(500);
        }
        if (analogRead(Ox) > 1000) {
          irwrite.sendNEC(work_code[3], 32);
          delay(50);
        }
        if (analogRead(Ox) < 200) {
          irwrite.sendNEC(work_code[4], 32);
          delay(50);
        }
      break;
    case 3:
      //Philips
        if (digitalRead(Button_power_pin) == LOW) {
          irwrite.sendRC6(work_code[0], 20);
          delay(500);
        }
        if (analogRead(Oy) > 1000) {
          irwrite.sendRC6(work_code[1], 20);
          delay(500);
        }
        if (analogRead(Oy) < 200) {
          irwrite.sendRC6(work_code[2], 20);
          delay(500);
        }
        if (analogRead(Ox) > 1000) {
          irwrite.sendRC6(work_code[3], 20);
          delay(50);
        }
        if (analogRead(Ox) < 200) {
          irwrite.sendRC6(work_code[4], 20);
          delay(50);
        }
      break;
    case 4:
      //Sony
        if (digitalRead(Button_power_pin) == LOW) {
          irwrite.sendSony(work_code[0], 12);
          delay(500);
        }
        if (analogRead(Oy) > 1000) {
          irwrite.sendSony(work_code[1], 12);
          delay(500);
        }
        if (analogRead(Oy) < 200) {
          irwrite.sendSony(work_code[2], 12);
          delay(500);
        }
        if (analogRead(Ox) > 1000) {
          irwrite.sendSony(work_code[3], 12);
          delay(50);
        }
        if (analogRead(Ox) < 200) {
          irwrite.sendSony(work_code[4], 12);
          delay(50);
        }
      break;
    case 5:
      //Toshiba
        if (digitalRead(Button_power_pin) == LOW) {
          irwrite.sendNEC(work_code[0], 32);
          delay(500);
        }
        if (analogRead(Oy) > 1000) {
          irwrite.sendNEC(work_code[1], 32);
          delay(500);
        }
        if (analogRead(Oy) < 200) {
          irwrite.sendNEC(work_code[2], 32);
          delay(500);
        }
        if (analogRead(Ox) > 1000) {
          irwrite.sendNEC(work_code[3], 32);
          delay(50);
        }
        if (analogRead(Ox) < 200) {
          irwrite.sendNEC(work_code[4], 32);
          delay(50);
        }
      break;
  }
}

