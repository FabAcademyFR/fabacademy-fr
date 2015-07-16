int sensorValue = A0;
 
void setup() {
  Serial.begin(9600);

}
 
void loop() {
  sensorValue = analogRead(A0);            
 
  Serial.print("sensor = " );
  Serial.println(sensorValue);      
 
  delay(1000);
  }
  
