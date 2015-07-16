int hbridge_in1 = 6;    //motor 1 in1
int hbridge_in2 = 5;    //motor 1 in2
int hbridge_in3 = 9;    //motor 2 in1
int hbridge_in4 = 10;   //motor 2 in2
char command; 
 
void setup() {
  pinMode(hbridge_in1,OUTPUT);
  pinMode(hbridge_in2,OUTPUT);
  pinMode(hbridge_in3,OUTPUT);
  pinMode(hbridge_in4,OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()){
  command = Serial.read();
  }
  if (command == 'A'){         //Robot go Forward
  analogWrite(hbridge_in1,150);
  analogWrite(hbridge_in2,0);
  analogWrite(hbridge_in3,150);
  analogWrite(hbridge_in4,0);
  delay(300);
  }
  if (command == 'B'){         //Robot go Backward
  analogWrite(hbridge_in1,0);
  analogWrite(hbridge_in2,150);
  analogWrite(hbridge_in3,0);
  analogWrite(hbridge_in4,150);  
  delay(300);
  }
  if (command == 'C'){         //Robot go Left
  analogWrite(hbridge_in1,150);
  analogWrite(hbridge_in2,0);
  analogWrite(hbridge_in3,0);
  analogWrite(hbridge_in4,0);  
  delay(300);
  }
  if (command == 'D'){         //Robot go Right
  analogWrite(hbridge_in1,0);
  analogWrite(hbridge_in2,0);
  analogWrite(hbridge_in3,150);
  analogWrite(hbridge_in4,0);  
  delay(300);
  }
  if (command == 'S'){         //Robot Stop
  analogWrite(hbridge_in1,0);
  analogWrite(hbridge_in2,0);
  analogWrite(hbridge_in3,0);
  analogWrite(hbridge_in4,0);  
  }
  if (command == 'X'){        //Robot Dance
  analogWrite(hbridge_in1,0);
  analogWrite(hbridge_in2,150);
  analogWrite(hbridge_in3,150);
  analogWrite(hbridge_in4,0);
  delay(500);
  analogWrite(hbridge_in1,150);
  analogWrite(hbridge_in2,0);
  analogWrite(hbridge_in3,0);
  analogWrite(hbridge_in4,150);
  delay(500);
  analogWrite(hbridge_in1,0);
  analogWrite(hbridge_in2,150);
  analogWrite(hbridge_in3,150);
  analogWrite(hbridge_in4,0);
  delay(500);
  analogWrite(hbridge_in1,150);
  analogWrite(hbridge_in2,0);
  analogWrite(hbridge_in3,0);
  analogWrite(hbridge_in4,150);
  delay(500);
  analogWrite(hbridge_in1,0);
  analogWrite(hbridge_in2,150);
  analogWrite(hbridge_in3,150);
  analogWrite(hbridge_in4,0);
  delay(500);
  analogWrite(hbridge_in1,150);
  analogWrite(hbridge_in2,0);
  analogWrite(hbridge_in3,0);
  analogWrite(hbridge_in4,150);
  delay(500);

  }
}
