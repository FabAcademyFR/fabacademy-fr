#include <Servo.h>

Servo myservo;

int posizione = 6;

void setup() {
myservo.attach(6);                          //Il Pin del servo lo collego al Pin6\
}

void loop() {
while(posizione <180){
  posizione ++;
  myservo.write(posizione);
  delay (15);
}
while(posizione >0){
  posizione --;
  myservo.write(posizione);
  delay (15);
}
}
