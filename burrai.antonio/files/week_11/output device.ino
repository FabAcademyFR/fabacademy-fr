
#include <Servo.h>  
Servo myservoDX; 
Servo myservoSX; 
int motorPin = 5;
int led13 = 13;
int led12 = 12;
int led11 = 11;
int LDR = 0;
int pos = 0; 
void setup() {                
  pinMode(led13, OUTPUT); //red led
  pinMode(led12, OUTPUT); //yellow led
  pinMode(led11, OUTPUT); //green led
  pinMode(LDR, INPUT);
myservoDX.attach(9);  
myservoSX.attach(10);  
   Serial.begin(9600);
}

void loop() {
   int v = analogRead(LDR);
   Serial.println(v);
   delay(50);
if ( v >=600 && v <=800)
{
  digitalWrite(led11, HIGH);
  digitalWrite(led12, LOW); 
  digitalWrite(led13, LOW);
  myservoDX.write(50);  
  myservoSX.write(90);  
  delay(5);
} 

if ( v >500 && v <600)
{
  digitalWrite(led11, LOW);
  digitalWrite(led12, HIGH); 
  digitalWrite(led13, LOW); 
  myservoDX.write(100);  
  myservoSX.write(50);  
  delay(5);
} 
if ( v >800)
{
  digitalWrite(led11, LOW);
  digitalWrite(led12, HIGH); 
  digitalWrite(led13, LOW);
  myservoDX.write(10);  
  myservoSX.write(140); 
  delay(5);
} 
  if ( v <=500)
{
  digitalWrite(led11, LOW); 
  digitalWrite(led12, LOW); 
  digitalWrite(led13, HIGH); 
  myservoDX.write(100);  
  myservoSX.write(50);  
  delay(5);
} 
}
