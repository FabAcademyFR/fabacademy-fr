#include "HardwareSerial.h"

#define RFCHANNEL        0       // Let's use channel 0
#define SYNCWORD1        0xB5    // Synchronization word, high byte
#define SYNCWORD0        0x47    // Synchronization word, low byte
#define SOURCE_ADDR      4       // Sender address
#define DESTINATION_ADDR 5       // Receiver address

CCPACKET txPacket;  // packet object
byte count = 0;

int red = 255;
int grn = 255;
int blu = 255;
int LDRvalue = 0;
int redstrip = 3;
int grnstrip = 5;
int blustrip = 6;

/**
 * This function is called whenever a wireless packet is received
 */
void rfPacketReceived(CCPACKET *packet)
{   
  if (packet->length > 1)
  { 
    LDRvalue = int(packet->data[1]);
    
  }
}

void setup()
{
pinMode (redstrip, OUTPUT);
pinMode (grnstrip, OUTPUT);
pinMode (blustrip, OUTPUT);
 analogWrite (redstrip, red);
 analogWrite (grnstrip, grn);
 analogWrite (blustrip, blu);


  Serial.begin(9600);
  Serial.println("RADIO...");
  
  //panstamp.init(CFREQ_868);
  panstamp.radio.setChannel(RFCHANNEL);
  panstamp.radio.setSyncWord(SYNCWORD1, SYNCWORD0);
  panstamp.radio.setDevAddress(DESTINATION_ADDR);
  panstamp.radio.setCCregs();

  // Let's disable address check for the current project so that our device
  // will receive packets even not addressed to it.
  //panstamp.radio.disableAddressCheck();

  // Declare RF callback function
  panstamp.setPacketRxCallback(rfPacketReceived);
}

void loop()

{ int ritardo = map (LDRvalue, 0, 255, 0, 1000);
 
    analogWrite (redstrip, red);
    analogWrite (grnstrip, grn);
    analogWrite (blustrip, blu);
    delay(ritardo);
    analogWrite (redstrip, 0);
    analogWrite (grnstrip, 0);
    analogWrite (blustrip, 0);
    delay(ritardo); 
 
  }
  











