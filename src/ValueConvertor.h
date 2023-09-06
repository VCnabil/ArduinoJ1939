#ifndef ValueConvertor_h
#define ValueConvertor_h

#include "Arduino.h"

class ValueConvertor {
  public:
    ValueConvertor();
    void convertToBytes(float argValue);
    float convertToFloat(byte argB1, byte argB2);
    float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
    byte getFirstByte();
    byte getSecondByte();


  private:
    byte B_first;
    byte B_second;
    float floatVal;
    float floatMapped;
};

#endif
