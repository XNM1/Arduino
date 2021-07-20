#include <NewPing.h>

#define LED_FAR 10
#define LED_CLOSER 11
#define TRIG 2
#define ECHO 4
#define MAX_DISTANSE 100
NewPing sonar(TRIG,ECHO,MAX_DISTANSE);
void setup() {
 pinMode(LED_FAR,OUTPUT);
 pinMode(LED_CLOSER,OUTPUT); 
 Serial.begin(115200);
}
void loop() {
 int current_distanse = getDistance();
  if (current_distanse !=0 && current_distanse <=25) {
    digitalWrite(LED_FAR,LOW);
    digitalWrite(LED_CLOSER,HIGH);
  }
  else {
   digitalWrite(LED_CLOSER,LOW);
  digitalWrite(LED_FAR,HIGH); 
  }
}
int getDistance() {
  int distanse = sonar.convert_cm(sonar.ping_median(15));
  Serial.println(distanse);
  return distanse;
}
