#include "HardwareSerial.h"
 
#define RFCHANNEL        0       // Let's use channel 0
#define SYNCWORD1        0xB5    // Synchronization word, high byte
#define SYNCWORD0        0x47    // Synchronization word, low byte
#define SOURCE_ADDR      4       // Sender address
#define DESTINATION_ADDR 5       // Receiver address

CCPACKET txPacket;  // packet object
byte count = 0;

#define LDR            A1

void setup()
{
  //  
  pinMode(LDR, INPUT); 
  Serial.begin(9600);
  Serial.println("RADIO...");
  
  //panstamp.init(CFREQ_868);
  panstamp.radio.setChannel(RFCHANNEL);
  panstamp.radio.setSyncWord(SYNCWORD1, SYNCWORD0);
  panstamp.radio.setDevAddress(SOURCE_ADDR);
  panstamp.radio.setCCregs();

  // Let's disable address check for the current project so that our device
  // will receive packets even not addressed to it.
  panstamp.radio.disableAddressCheck();

  // Declare RF callback function
  //panstamp.setPacketRxCallback(rfPacketReceived);
}

void loop()
{
  txPacket.length = 2;  // Let's send a single data byte plus the destination address

  txPacket.data[0] = DESTINATION_ADDR;   // First data byte has to be the destination address
  int sensorValue = analogRead(LDR);
  Serial.println(sensorValue);
  sensorValue = map(sensorValue, 0, 1024, 0, 255);
  txPacket.data[1] = sensorValue;    
  panstamp.radio.sendData(txPacket);     // Transmit packet 
  delay(1000);
 
}

