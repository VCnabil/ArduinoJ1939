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
    int getAngle_INT(int arg_cartesianX, int arg_cartesianY);
    float getAngle_FLOAT(int arg_cartesianX, int arg_cartesianY);
    byte* floatToTwoByteArray(float value);


  private:
    byte B_first;
    byte B_second;
    float floatVal;
    float floatMapped;
};

#endif
