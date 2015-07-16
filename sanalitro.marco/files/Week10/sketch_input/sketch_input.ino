
int Led = 12; //A5; 
int Sensor = A0;//A4;
int V = 0;
int VN = 0;
int VMin = 1023;
int VMax = 0;

void setup() {
  pinMode(Led, OUTPUT);
  pinMode(Sensor, INPUT);
  
  digitalWrite(Led, HIGH);
  
  while (millis() <5000) {
    V = analogRead(Sensor);
  
  if (V > VMax) {
      VMax = V;
    } 
    
  if (V < VMin) {
      VMin = V;
    }
  }
  
  digitalWrite(Led, LOW);
  
  Serial.begin(9600); 

}

void loop() {
  V = analogRead(Sensor);
  VN = map(V, VMin, VMax, 0, 255); 
  VN = constrain (VN, 0, 255);

 if(VN < 75){
  digitalWrite(Led, HIGH);  
 }else{
   digitalWrite(Led, LOW);
 }   
  Serial.print(V);
  Serial.print(" --> ");
  Serial.println(VN);
  delay(250);
}
