

#include "IRremote2.h"

const int ldrPin = 4;  
const int tempPin = 5;


IRsend irsend;

void setup()
{
  Serial.begin(9600);
}

void loop() {
int light = analogRead(ldrPin);
int temp = analogRead(tempPin);
Serial.print(light);
Serial.print("/");  
Serial.println(temp);


delay(100);
 if (Serial.available() > 0) {
    int code = Serial.parseInt();
  if(code == 1){ // on
     Serial.println("Turn ON\nCommand 'HVAC_HOT, 21, FAN_SPEED_AUTO, VANNE_AUTO_MOVE'  Next Command in 10 sec.");
      irsend.sendHvacMitsubishi(HVAC_HOT, 23, FAN_SPEED_1, VANNE_AUTO_MOVE, false);
      delay(10000);
    }else if(code == 0){
    Serial.println("Switch OFF and Wait 15 Seconds to send ON command.");
      irsend.sendHvacMitsubishi(HVAC_HOT, 21, FAN_SPEED_AUTO, VANNE_AUTO_MOVE, true);
      delay(15000); 
    }
     
  }
 
  }


