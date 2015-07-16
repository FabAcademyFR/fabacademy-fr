
void setup() {
  pinMode(8, OUTPUT); // initialize the yellow LED pin as an output
  pinMode(7, OUTPUT); // initialize the red LED pin as an output
  }

void loop() {
  
  digitalWrite(8, 1);    // turn the yellow LED ON
  digitalWrite(7, 0);    // turn the red LED OFF
  delay(1000);              // wait for a second
  digitalWrite(8, 0);    // turn the yellow LED OFF 
  digitalWrite(7, 1);    // turn the red LED ON
  delay(1000);              // wait for a second
}
