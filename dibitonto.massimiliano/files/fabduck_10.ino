#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
//#define BUFFER 1024 // size of the buffer in bytes

#define DST_IP "api.thingspeak.com" //my web site, replace with yours

const long accInterval = 500;
const long updInterval = 30000;
const long inactivityInterval = 120000;
String cmd;   // AT command string

SoftwareSerial ESP8266(10, 11); // RX, TX
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

bool sending = false;
bool updatedW = false;


long lastActivity = 0;
bool bored = false;


//values of weather and time
int todayTemp = 0;
int todayCode = 0;
int todayHigh = 0;
int todayMin = 0;
int tomorrowCode = 0;
int hour = 2;
int mins = 0;
int weekd= 0;

int waterTemp = 0;

long lastUpdate = 0;
long lastAcc= 0;




#define DEBUG Serial      // Send debug messages to serial monitor
//#define ESP8266 Serial1   // Use Serial1 to talk to ESP8266 (Mega)

// By default we expect OK\r\n back


//=====================================================================
void setup() {
  pinMode(13,OUTPUT);
  pinMode(6,OUTPUT);//red led
  pinMode(5,OUTPUT);//blu
  pinMode(3,OUTPUT);//green
  digitalWrite(13,LOW);
   digitalWrite(6,LOW);//white!
   digitalWrite(5,LOW);
   digitalWrite(3,LOW);
   
  delay(1000);
   digitalWrite(6,HIGH);//off
   digitalWrite(5,HIGH);
   digitalWrite(3,HIGH);
   delay(1000);
    digitalWrite(13,LOW);
   digitalWrite(6,LOW);//white!
   digitalWrite(5,LOW);
   digitalWrite(3,LOW);
    delay(1000);
      digitalWrite(6,HIGH);//off
   digitalWrite(5,HIGH);
   digitalWrite(3,HIGH);
  cmd.reserve(122);
  ESP8266.begin(9600);
  DEBUG.begin(9600); // Start seriam monitor comms for debug messages
  Serial.println(F("Initialising..."));
  
 // initESP8266(); // Initialise the ESP8266 module
 sensors.begin();
 randomSeed(analogRead(0)); // seed for random generator
 tempReq();
}

//=====================================================================
byte waitForResponse(int timeout) {
  unsigned long t=millis();
  bool found=false;
  int i=0;
 
  // wait for at most timeout milliseconds
  // or if OK\r\n is found
  while(millis()<(t+timeout)) {
  if(ESP8266.find("OK")||(ESP8266.find(">"))){
    found=true;
   Serial.println(F("send get request WE"));
     Serial.println(freeRam());
          break;
  }
    
  }


if(ESP8266.find("/123")){
String cbRead = ESP8266.readStringUntil('\n');
char charBuf[50];
cbRead.toCharArray(charBuf, 50);
  DEBUG.println(charBuf);
  char*p = charBuf;
  char* values;
 // = strtok_r(charBuf, "/",&charBuf);
  int count = 0;
  while ((values = strtok_r(p, "/", &p)) != NULL){ // delimiter is the semicolon
  // Serial.println(sizeof(values));
  if(count == 0){ 
    todayTemp =atoi(values);
  }
  if(count == 1){
    todayCode =atoi(values);
  }
   if(count == 2){
    todayHigh =atoi(values);
  } 
 if(count == 3){
   todayMin=atoi(values);
 }
  if(count == 4){
   tomorrowCode=atoi(values);
 }
  if(count == 5){
   hour=atoi(values);
 }
  if(count == 6){
   mins=atoi(values);
 }
  if(count == 7){
   weekd=atoi(values);
 }
  count++;
 //  Serial.println(values);
}

//todayHigh = atoi(&values[2]);
//Serial.print("temp ");  
//Serial.println(todayTemp);
//Serial.print("code ");
//Serial.println(todayCode);
//Serial.print("high ");
//Serial.println(todayHigh);
//Serial.print("min ");
//Serial.println(todayMin);
//Serial.print("tomoCode ");
//Serial.println(tomorrowCode);
//Serial.print("hour ");
//Serial.println(hour);
//Serial.print("weekd ");
//Serial.println(weekd);
delay(1000);
//phrase();
updatedW = true;
  
}
  //Serial.println(cbRead);
  delay(100);
//  while(ESP8266.available() > 0){
// String lastbuf = ESP8266.readString();
//  //Serial.print("buf: ");
//  Serial.println(lastbuf);
//  }
  return found;
}

byte waitForTwitterResp(int timeout) {
  unsigned long t=millis();
   while(millis()<(t+timeout)) {
     if(ESP8266.find("OK")||(ESP8266.find(">"))){
          //found=true;
     Serial.println(F("twr"));
     Serial.println(freeRam());
         while (ESP8266.available() > 0){
         String twRead = ESP8266.readString();
         Serial.print(F("bufT1: "));
         Serial.println(twRead);
         }
      break;
      }else{
          while (ESP8266.available() > 0) {
          String twRead = ESP8266.readString();
          Serial.print(F("bufT2: "));
          Serial.println(twRead);
          }
        break;
       }
   }
}



//=====================================================================
void getTheWeather() {
 
  sending = true;
  Serial.println("wg");
  cmd = F("AT+CIPSTART=\"TCP\",\"");
  cmd += DST_IP;
  cmd += "\",80";
  ESP8266.println(cmd);  //send command to device
  waitForResponse(10000);
  
  cmd =  F("GET /apps/thinghttp/send_request?api_key=9M96JTL06I8NPA25&temp=26");  //construct http GET request
 // cmd += waterTemp;
  cmd += " HTTP/1.0\r\n\r\n";  //construct http GET request
  //cmd += "Host:  api.thingspeak.com\r\n\r\n";        //test file on my web
  ESP8266.print(F("AT+CIPSEND="));
  ESP8266.println(cmd.length());  //esp8266 needs to know message length of incoming messa
  //ESP8266.println("70");
  waitForResponse(10000);
  
  ESP8266.print(cmd);
  waitForResponse(60000);
  
  ESP8266.println(F("AT+CIPCLOSE")); // Close the TCP connection
  waitForResponse(5000);
  
  DEBUG.println(F("end get weather"));
  if(updatedW){
    delay(500);
   phrase(); 
  }
  updatedW= false;
  sending = false;
  digitalWrite(6,LOW);//off
  
   digitalWrite(3,LOW);
    digitalWrite(5,HIGH);
}

void tweet(String msg) {
 
  digitalWrite(13,HIGH);
  sending = true;
  DEBUG.println(F("send tweet"));
 //  ESP8266.println("AT+CIPCLOSE"); // Close the TCP connection
 // delay(1000);
  cmd =  "AT+CIPSTART=\"TCP\",\"";
  cmd += DST_IP;
  cmd += "\",80";
  ESP8266.println(cmd);  //send command to device
  waitForTwitterResp(10000);
  
  cmd = "GET /apps/thinghttp/send_request?api_key=LVZ7I7W3LYMUWOZQ&msg=";
  cmd += msg;
  cmd += " HTTP/1.0\r\n\r\n";  //construct http GET request
  //cmd += "Host:  api.thingspeak.com\r\n\r\n";        //test file on my web
  ESP8266.print(F("AT+CIPSEND="));
  ESP8266.println(cmd.length());  //esp8266 needs to know message length of incoming messa
  waitForTwitterResp(10000);
  
  ESP8266.print(cmd);
  waitForTwitterResp(60000);
  
  ESP8266.println(F("AT+CIPCLOSE")); // Close the TCP connection
  waitForTwitterResp(5000);
  
  DEBUG.println(F("tw"));
  sending= false;
  digitalWrite(13,LOW);
}


void phrase(){
  Serial.println(F("phrase"));
  if(hour >= 0 && hour < 20){ //send message only during the day
int rand = random(1,9);
DEBUG.println(rand);
String msg= "";
 switch (rand) {
    case 1:
      msg = "Quack!!!";
      break;
    case 2:
      msg = F("Don't waste water, I need it to swim!");
      //msg += mins;
      break;
      case 3:
      if(todayCode >28 && todayCode < 35){
      msg = F("Today the weather is amazing! Wanna swim?");
      //msg += mins;
      }else if(tomorrowCode >28 && tomorrowCode < 35){
      msg = F("Tomorrow will be sunny! Get ready for a swim!");
      //msg += mins;  
      }else{
      msg= F("This weather makes me sad");
      //msg += mins;
      }
      break;
       case 4:
       if(todayHigh >28){
        msg = "Today will be very very hot.  ";
       msg  += todayHigh;
       msg += " degrees. Get into the water!";
       //msg += mins;
       }else{
         msg="Brrr!";
        msg = msg + todayHigh;
        msg = msg +" degrees!!Today you need a woolen swimming suite!";
        //msg += mins;
       }
      break;
      
       case 5:
       msg = "Today the water is at ";
      msg = msg + waterTemp;
      msg = msg + " degrees.";
      //msg += mins;
      if(waterTemp > 25){
      msg = msg + "Perfect for swimming!";
      //msg += mins;
      }else{
       msg = msg + "Cold water keeps me young!!";
      //msg += mins; 
      }
      break;
      
      case 6:
      if(weekd == 5){
      msg = "It's friday I'm in love!!!";
      }else if(weekd == 6 || weekd == 0){
      msg = "It's the weekend. Let's go party?";
     //msg += mins; 
      }else if(weekd == 1){
        msg = "It's monday :(";
       // msg += mins;
      }else{
         msg ="Hold on, the weekend will come soon!";
         //msg += mins;
      }
      break;
      case 7:
      msg ="42!";
      break;  
      case 8:
      if(bored){
        msg = "I'm feeling alone...";
      }else{
       msg = "hey, there is a party here!"; 
      } 
      break;
      case 9:
      msg = "Does androids swim with electric ducks?";
      break;
  }
  Serial.println(msg); 
  tweet(msg);
  } 
  
}

void tempReq(){
 sensors.requestTemperatures(); // Send the command to get temperatures
  waterTemp = (sensors.getTempCByIndex(0));    
  //Serial.println("water ");
  //Serial.println(waterTemp);
  
}


//=====================================================================
void loop() { 
//   digitalWrite(6,HIGH);//red
//   digitalWrite(3,HIGH);//green
//      digitalWrite(5,HIGH);//blu
if(millis() - lastUpdate> updInterval && sending == false){
   digitalWrite(6,LOW);//white!
   digitalWrite(5,LOW);
   digitalWrite(3,LOW);
  tempReq();
 getTheWeather();
  lastUpdate = millis();
}  
if(millis() - lastAcc> accInterval){
//  //phrase();
//   digitalWrite(6,HIGH);//red
//   digitalWrite(3,LOW);//green
//      digitalWrite(5,LOW);//blu
  checkAccel();
  lastAcc = millis();
}   
  //Serial.println(freeRam());
}

void checkAccel(){
  //Serial.println("check");
int rawZ= analogRead(5);
Serial.println(rawZ);
 if(rawZ < 295){ //upside down
     //Serial.println("trouble");
      tweet("Help!I'm sinking, maybe someone is in trouble!");
   digitalWrite(6,LOW);//red
   digitalWrite(5,HIGH);
   digitalWrite(3,HIGH);
   }else if(rawZ>500){
      if(sending == false){
      //Serial.println("bomb dive");
      digitalWrite(6,LOW);//yellow
      digitalWrite(3,LOW);
      digitalWrite(5,HIGH);
      tweet("Nice cannonball! But I can do it better!");
      }
  bored = false;
  lastActivity = millis();
  //twitta
  }else if(rawZ < 414 || rawZ > 435){
     //Serial.println("wave");
     if(bored && sending == false){
     //twitta felice
    // Serial.println("hey, someone is here :)");
    digitalWrite(6,LOW);//red
    digitalWrite(5,HIGH);
     digitalWrite(3,HIGH);
     tweet("hey, someone's here :)");
   
     }  
   bored = false;
   lastActivity = millis();
  }
  
if(millis()-lastActivity > inactivityInterval){

 if(bored == false && sending == false){
   //twitta
  // DEBUG.println("I'm getting very bored...");
   //tweet("I'm getting very bored...");

  
 }
 bored = true;
}


  if(waterTemp < 24){ //blue if the water is cold green if it's good
   digitalWrite(6,HIGH);//blue
   digitalWrite(5,LOW);
   digitalWrite(3,HIGH);
}else{
  digitalWrite(6,HIGH);//green
   digitalWrite(5,HIGH);
   digitalWrite(3,LOW);
}

}

int freeRam() {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
  delay(500);
}
