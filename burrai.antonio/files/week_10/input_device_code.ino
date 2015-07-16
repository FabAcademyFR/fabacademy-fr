// Photo resistor SETUP
int LDR = 0;//define a pin for Photo resistor
void setup() {                
  pinMode(LDR, INPUT);
   Serial.begin(9600); //Begin serial communcation
}
void loop() {
   int v = analogRead(LDR);
   Serial.println(v);
   delay(50);
 }
