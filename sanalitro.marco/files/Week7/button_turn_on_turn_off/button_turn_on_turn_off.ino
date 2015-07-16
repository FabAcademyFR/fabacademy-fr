 int pinLed1 = 7;          // the number of the red Led pin
 int pinLed2 = 8;          // the number of the yellow Led pin
 int buttonPin = 3;        // the number of the pushbutton pin
 int ledState = 0;         // variable for reading the Led status
 int buttonState = 0;      // variable for reading the pushbutton status
 int old_buttonState = 0;  // variable memory of the pushbutton old status

 void setup() {
   pinMode(pinLed1, OUTPUT);   // initialize the LED pin as an output
   pinMode(pinLed2, OUTPUT);   // initialize the LED pin as an output
   pinMode(buttonPin, INPUT);  // initialize the pushbutton pin as an input
  }

 void loop() {
    int buttonState = digitalRead(buttonPin); // read the state of the pushbutton value
    
    if (buttonState == 0 && old_buttonState == 1){ // debouncing: use the pushbutton status
      ledState = !ledState;                        // and a small delay 
      delay(20);                                    
      }
     
    old_buttonState = buttonState; // give memory of pushbutton status
    if (ledState == 1){
      digitalWrite( pinLed1, 1); // turn red LED on
      digitalWrite( pinLed2, 1); // turn yellow LED on
      }  
    else {
      digitalWrite( pinLed1, 0); // turn red LED off
      digitalWrite( pinLed2, 0); // turn yellow LED off
      }
  }
  
  
  
  
  
  
  
  
  
