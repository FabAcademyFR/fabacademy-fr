int pinLed1 = 7; // the number of the red Led pin
int pinLed2 = 8; // the number of the yellow Led pin
int buttonPin = 3; // the number of the pushbutton pin
int brightnessLed1 = 0; // how bright the red LED 
int brightnessLed2 = 255; // how bright the yellow LED 
int fadeAmount = 5; // how many points to fade the Led
int buttonState = 0; // variable for reading the pushbutton status
 
void setup() {               
  pinMode(pinLed1, OUTPUT);  // initialize the LED pin as an output
  pinMode(pinLed2, OUTPUT);  // initialize the LED pin as an output
  pinMode(buttonPin, INPUT); // initialize the pushbutton pin as an input
}
 
void loop() {
  int buttonState = digitalRead(buttonPin); // read the state of the pushbutton value
 switch (buttonState) {                     // switch two options
   case 1:                                  // option 1
   digitalWrite( pinLed1, 0);               // turn red LED off
   digitalWrite( pinLed2, 0);               // turn yellow LED off
   break;
   case 0:                                  // option 0
   analogWrite( pinLed1, brightnessLed1);   // set the brightness of pin 7            
   analogWrite( pinLed2, brightnessLed2);   // set the brightness of pin 8 
  
   brightnessLed1 = brightnessLed1 + fadeAmount; // change the brightness of Leds 
   brightnessLed2 = brightnessLed2 - fadeAmount; // for next time through the loop
  
   if (brightnessLed1 == 0 || brightnessLed1 == 255){ // reverse the direction of the 
   fadeAmount = -fadeAmount;                          // fading at the ends of the fade
   }
   delay(150); // wait for 150 milliseconds to see the dimming effect
   break;
   }
  }
  

 
