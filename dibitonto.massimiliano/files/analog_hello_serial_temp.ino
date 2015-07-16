const int ldrPin = 4;  
const int tempPin = 1;
const int ledPin =  13;      // the number of the LED pin

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
int light = analogRead(ldrPin);
int temp = analogRead(tempPin);
float t  = temp * 0.48828125; // LM35 vuole una costante
//temp = temp * 0.137;
Serial.print(light);
Serial.print("/");  
Serial.println(temp);
 if(light > 400){
digitalWrite(13,HIGH); 
}else{
digitalWrite(13,LOW); 
}
delay(50);
}
