#include "HWInterface.h"
unsigned char msgRequest_pots[8];

HWInterface::HWInterface() {
  // Constructor
}
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
unsigned char* HWInterface::getMessage() {

  int sensorValue_00 = analogRead(A0);
  float floatValue_00 = mapFloat(sensorValue_00, 0, 1024, 0.0, 20.0);

  // Convert the float to a fixed-point representation using 8 bits for the fractional part
  int fixedPointValue_00 = (int)(floatValue_00 * 256);
  // Extract the two bytes
  byte byte7 = (fixedPointValue_00 >> 8) & 0xFF;
  byte byte6 = fixedPointValue_00 & 0xFF; 
  msgRequest_pots[7] = byte7;
  msgRequest_pots[6] = byte6;
  
  int sensorValue_01 = analogRead(A1);
  float floatValue_01 = mapFloat(sensorValue_01, 0, 1024, 0.0, 20.0);

  // Convert the float to a fixed-point representation using 8 bits for the fractional part
  int fixedPointValue_01 = (int)(floatValue_01 * 256);
  // Extract the two bytes
  byte byte5 = (fixedPointValue_01 >> 8) & 0xFF;
  byte byte4 = fixedPointValue_01 & 0xFF; 
  msgRequest_pots[5] = byte5;
  msgRequest_pots[4] = byte4;


  return msgRequest_pots;
}

void HWInterface::setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
   
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
 