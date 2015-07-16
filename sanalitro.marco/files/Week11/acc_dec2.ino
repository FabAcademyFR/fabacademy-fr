int in1 = 6;
int in2 = 5;



void setup() {
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);

}

void loop() {
  
  
  
  analogWrite(in1,85);
  analogWrite(in2,0);
  delay(500);
  
  analogWrite(in1,0);
  analogWrite(in2,0);
  delay(500);
  
  analogWrite(in1,0);
  analogWrite(in2,85);
  delay(500);
  
  analogWrite(in1,0);
  analogWrite(in2,0);
  delay(500);
  
   
}
