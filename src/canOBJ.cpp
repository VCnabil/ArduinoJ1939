#include "canOBJ.h"
// Simulation parameters
#define PGN_RequestMessage 0x18FF02
#define PGN_EngineTemperature 0x18FF00
#define PGN_EngineTemperatureLSB 0xEE
#define PGN_EngineTemperature2ND 0xFE
#define PGN_EngineTemperatureMSB 0x00
#define NODE_Request 0x20
#define NODEPV780_Request 0x09
#define NODE_Response 0x30
unsigned char msgEngineTemperature[8] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38};
unsigned char msgRequest_0[] = {0x00, 0x00, 0x00, 0x00, 0xA1, 0x0E, 0x08, 0x10};

CanOBJ::CanOBJ() {
  // Constructor
}

void CanOBJ::setup() {
  pinMode(LED_BUILTIN, OUTPUT);
//   Serial.begin(115200);
  if (canInitialize(CAN_250KBPS) == CAN_OK) {
    Serial.print("CAN Init OK.\n\r\n\r");
  } else {
    Serial.print("CAN Init Failed.\n\r");
  }
}

bool CanOBJ::ReadSerialMonitorString() {
  bool bRetCode = false;
  char sString[2];
  if (Serial.available() > 0) {
    Serial.setTimeout(1);
    Serial.readBytes(sString, 1);
    bRetCode = true;
  }
  return bRetCode;
}

void CanOBJ::looper() {
  // Your existing looper code here
   // Declarations
  byte nPriority;
  byte nSrcAddr;
  byte nDestAddr;
  byte nData[8];
  int nDataLen;
  long lPGN;
  
  char sString[80];
  
  // Check for received J1939 messages
  if(j1939Receive(&lPGN, &nPriority, &nSrcAddr, &nDestAddr, nData, &nDataLen) == 0)
  {
    // Display the received message on the serial monitor 
    sprintf(sString, "PGM: 0x%X Srz: 0x%X Destz: 0x%X ", (int)lPGN, nSrcAddr, nDestAddr);
    Serial.print(sString);
    if(nDataLen == 0 )
      Serial.print("No Data.\n\r");
    else
    {
      Serial.print("Dataz: ");
      for(int nIndex = 0; nIndex < nDataLen; nIndex++)
      {          
        sprintf(sString, "0x%X ", nData[nIndex]);
        Serial.print(sString);
        
      }// end for
      Serial.print("\n\r");
      
    }// end else
    
    // Analyze the received PGN
    switch(lPGN)
    {
      case PGN_RequestMessage:
      
        if(nData[0] == PGN_EngineTemperatureLSB
        && nData[1] == PGN_EngineTemperature2ND
        && nData[2] == PGN_EngineTemperatureMSB)
        {
           // Request message for engine temperature was received
           j1939Transmit(PGN_EngineTemperature, 6, NODE_Response, NODE_Request, msgEngineTemperature, 8);  // Transmit the message
        }
      
        break;
        
      // Add more 'case' statements here...
      
    }// end switch
        
  }// end if
  


 
  // Check for user input per serial monitor
  // Send request message with user input
  if(ReadSerialMonitorString() == true){
    //j1939Transmit(PGN_RequestMessage, 6, NODE_Request, NODE_Response, msgRequest, 3);
    j1939Transmit(PGN_RequestMessage, 6, NODEPV780_Request, NODE_Response, msgRequest_0, 8);
  }
}

void CanOBJ::ReadAndSend2Pots() {
  int sensorValue_00 = analogRead(A0);
  float floatValue_00 = mapFloat(sensorValue_00, 0, 1024, 0.0, 20.0);

  // Convert the float to a fixed-point representation using 8 bits for the fractional part
  int fixedPointValue_00 = (int)(floatValue_00 * 256);
  // Extract the two bytes
  byte byte7 = (fixedPointValue_00 >> 8) & 0xFF;
  byte byte6 = fixedPointValue_00 & 0xFF; 
  msgRequest_0[7] = byte7;
  msgRequest_0[6] = byte6;
  
  int sensorValue_01 = analogRead(A1);
  float floatValue_01 = mapFloat(sensorValue_01, 0, 1024, 0.0, 20.0);

  // Convert the float to a fixed-point representation using 8 bits for the fractional part
  int fixedPointValue_01 = (int)(floatValue_01 * 256);
  // Extract the two bytes
  byte byte5 = (fixedPointValue_01 >> 8) & 0xFF;
  byte byte4 = fixedPointValue_01 & 0xFF; 
  msgRequest_0[5] = byte5;
  msgRequest_0[4] = byte4;







 j1939Transmit(PGN_RequestMessage, 6, NODEPV780_Request, NODE_Response, msgRequest_0, 8);
}

float CanOBJ::mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}