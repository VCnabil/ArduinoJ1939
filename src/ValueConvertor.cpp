#include "Arduino.h"
#include "ValueConvertor.h"

ValueConvertor::ValueConvertor() {
  // Constructor
}

void ValueConvertor::convertToBytes(float argValue) {
  uint16_t val = (uint16_t)(argValue * 256);  // Assuming 2 decimal places
  B_first = (val >> 8) & 0xFF;
  B_second = val & 0xFF;
}

float ValueConvertor::convertToFloat(byte argB1, byte argB2) {
  uint16_t val = ((uint16_t)argB1 << 8) | argB2;
  floatVal = val / 100.0;
  return floatVal;
}

float ValueConvertor::mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
    floatMapped= (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    return floatMapped;
}
 

byte ValueConvertor::getFirstByte() {
  return B_first;
}

byte ValueConvertor::getSecondByte() {
  return B_second;
}
