#include <Arduino.h>
#include <stdlib.h>
#include <SPI.h>

#include <mcp_can.h>
#include <can_ext.h>

// Simulation parameters --------------------------------------------------
// ------------------------------------------------------------------------
#define PGN_RequestMessage                      0x18FF02 //0x00EA00
#define PGN_EngineTemperature                   0x18FF00//0x00FEEE
#define PGN_EngineTemperatureMSB                0x00
#define PGN_EngineTemperature2ND            	0xFE
#define PGN_EngineTemperatureLSB                0xEE

#define NODE_Request                            0x20
#define NODEPV780_Request                            0x09
#define NODE_Response                           0x30

unsigned char msgEngineTemperature[8] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38}; 
unsigned char msgRequest[] = {PGN_EngineTemperatureLSB, PGN_EngineTemperature2ND, PGN_EngineTemperatureMSB};
unsigned char msgRequest_0[]={0x00, 0x00, 0x00, 0x00, 0xA1, 0x0E, 0x08, 0x10};
unsigned char msgRequest_1[]={0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0xA1, 0x0E};

// ------------------------------------------------------------------------
//  Check serial monitor for user input
// ------------------------------------------------------------------------
bool ReadSerialMonitorString(void)
{
  bool bRetCode = false;
  char sString[2];
  
  if(Serial.available() > 0)
  {
    Serial.setTimeout(1);
    Serial.readBytes(sString, 1);  
    bRetCode = true;  
  }
  
  return bRetCode;

}// end ReadSerialMonitorString



// put function declarations here:
int myFunction(int, int);
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) ;
void looper();

 




void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
   int result = myFunction(2, 3);

     // Set the serial interface baud rate
  Serial.begin(115200);
  
  // Initialize the CAN controller
  if (canInitialize(CAN_250KBPS) == CAN_OK)  // Baud rates defined in mcp_can_dfs.h
    Serial.print("CAN Init OK.\n\r\n\r");
  else
    Serial.print("CAN Init Failed.\n\r");
}


// the loop function runs over and over again forever
void loop() {
  // digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  // delay(1000);                      // wait for a second
  // digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  // delay(1000);                      // wait for a second

  looper();
}



// put function definitions here:
void looper() 
{
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
  
int sensorValue = analogRead(A0);
float floatValue = mapFloat(sensorValue, 0, 1024, 0.0, 20.0);

//weird 4 bytes 
  // byte floatBytes[4];
  // memcpy(floatBytes, &floatValue, 4);
  // Serial.print("0x");
  // Serial.print(floatBytes[0], HEX);
  // Serial.print(" 0x");
  // Serial.print(floatBytes[1], HEX);
  // Serial.print(" 0x");
  // Serial.print(floatBytes[2], HEX);
  // Serial.print(" 0x");
  // Serial.println(floatBytes[3], HEX);

  // Convert the float to a fixed-point representation using 8 bits for the fractional part
  int fixedPointValue = (int)(floatValue * 256);

  // Extract the two bytes
  byte byte1 = (fixedPointValue >> 8) & 0xFF;
  byte byte2 = fixedPointValue & 0xFF;

  // Transmit the two bytes in hexadecimal format
  // Serial.print("0x");
  // Serial.print(byte1, HEX);
  // Serial.print(" 0x");
  // Serial.println(byte2, HEX);

  msgRequest_0[7] = byte1;
  msgRequest_0[6] = byte2;
 j1939Transmit(PGN_RequestMessage, 6, NODEPV780_Request, NODE_Response, msgRequest_0, 8);


 //  Serial.println(sensorValue);
  // Check for user input per serial monitor
  // Send request message with user input
  if(ReadSerialMonitorString() == true){
    //j1939Transmit(PGN_RequestMessage, 6, NODE_Request, NODE_Response, msgRequest, 3);
    j1939Transmit(PGN_RequestMessage, 6, NODEPV780_Request, NODE_Response, msgRequest_0, 8);
  }

}// end loop



 float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int myFunction(int x, int y) {
  return x + y;
}