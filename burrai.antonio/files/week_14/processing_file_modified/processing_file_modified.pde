import processing.serial.*;
import cc.arduino.*;
import controlP5.*;
ControlP5 controlP5;
Arduino arduino;
int servoAngle1 = 90;
int servoAngle2 = 90;
void setup() {

 size(400,100);

 println(Arduino.list());
 arduino = new Arduino(this, Arduino.list()[0], 57600);

 for (int i = 0; i <= 13; i++)
 arduino.pinMode(i, Arduino.OUTPUT);

 controlP5 = new ControlP5(this);
 controlP5.addSlider("servoAngle1",0,180,servoAngle1,20,10,180,20);
 controlP5.addSlider("servoAngle2",0,180,servoAngle2,20,40,180,20);
 
}
void draw() {
 arduino.analogWrite(9, servoAngle1);
 arduino.analogWrite(10, servoAngle2);
 //delay(15);
}
