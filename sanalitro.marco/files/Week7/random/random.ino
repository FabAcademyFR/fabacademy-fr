int pinLed1 = 7;     // the number of the red Led pin
int pinLed2 = 8;     // the number of the yellow Led pin
int buttonPin = 3;   // the number of the pushbutton pin
long randomNumber;   // variable for reading the pushbutton status
int buttonState = 1; // variable for reading the pushbutton status



void setup() {

  pinMode(pinLed1, OUTPUT);  // initialize the LED pin as an output
  pinMode(pinLed2, OUTPUT);  // initialize the LED pin as an output
  pinMode(buttonPin, INPUT); // initialize the pushbutton pin as an input
  
  randomSeed( analogRead(A2));  // use randomSeed() to initialize the random number 
  }                             // generator with a random input, 
                                // such as analogRead() on an unconnected pin.
void loop() {
  int buttonState = digitalRead(buttonPin); // read the state of the pushbutton value
 
   switch (buttonState) {          // switch two options
   case 1:                         // option 1
   digitalWrite( pinLed1, 0);      // turn red LED off
   digitalWrite( pinLed2, 0);      // turn yellow LED off
   break;
   case 0:                         // option 0
   randomNumber = random(5,9);     // random range
   digitalWrite(randomNumber, 1);  // turn random LED on
   delay(2000);
   digitalWrite(randomNumber, 0);  // turn random LED off
   break;
   }
  
}
