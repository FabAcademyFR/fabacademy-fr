#include <Servo.h> 
 
Servo pan;  
Servo tilt;
int posP = 90;    
int posT = 90; 

int hbridge_in1 = 6;
int hbridge_in2 = 9;
int hbridge_in3 = 10;
int hbridge_in4 = 11;
char command; 
 
void setup() {
  pinMode(hbridge_in1,OUTPUT);
  pinMode(hbridge_in2,OUTPUT);
  pinMode(hbridge_in3,OUTPUT);
  pinMode(hbridge_in4,OUTPUT);
  pan.attach(A2);
  tilt.attach(A3);  
  Serial.begin(9600);
  pan.write(posP);
  tilt.write(posT);
  delay(150);
}

void loop() {
  if (Serial.available()){
  command = Serial.read();
  
  if (command == '1'){
  analogWrite(hbridge_in1,0);
  analogWrite(hbridge_in2,255);
  analogWrite(hbridge_in3,255);
  analogWrite(hbridge_in4,0);
  Frena ();
  }
  if (command == '2'){
  analogWrite(hbridge_in1,255);
  analogWrite(hbridge_in2,0);
  analogWrite(hbridge_in3,0);
  analogWrite(hbridge_in4,255); 
 Frena (); 
  }
  if (command == '3'){
  analogWrite(hbridge_in1,0);
  analogWrite(hbridge_in2,255);
  analogWrite(hbridge_in3,0);
  analogWrite(hbridge_in4,255);
Frena ();  
  }
  if (command == '4'){
  analogWrite(hbridge_in1,255);
  analogWrite(hbridge_in2,0);
  analogWrite(hbridge_in3,255);
  analogWrite(hbridge_in4,0); 
 Frena ();
  }
  if (command == '5'){
  if(posP - 15 > 44 && posP + 15< 136){
    posP -=15;
    pan.write(posP);
      }
   
    }
  if (command == '6'){
  if(posP - 15 > 44 && posP + 15 < 136){
    posP +=15;
    pan.write(posP);
      }
    }
  if (command == '7'){
  if(posT - 5 > 79 && posT + 5< 101){
    posT +=5;
    tilt.write(posT);
      }
    }
  if (command == '8'){
  if(posT - 5 > 79 && posT + 5< 101){
    posT -=5;
    tilt.write(posT);
      }
    }
  if (command == '9'){
  posT=90;
  posP=90;
  pan.write(posP);
  tilt.write(posT);
      }
 
  }
}

void Frena (){
  delay(250);
  analogWrite(hbridge_in1,0);
  analogWrite(hbridge_in2,0);
  analogWrite(hbridge_in3,0);
  analogWrite(hbridge_in4,0); }
