#ifndef HWINTERFACE_H
#define HWINTERFACE_H

#include <Arduino.h>

class HWInterface {
public:
  HWInterface();
  void setup();
   unsigned char* getMessage();
//   int readAnalogPinA0();
//   int readAnalogPinA1();
//   bool readDigitalPin22();
//   void writeDigitalPin23(bool value);
 //  float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
};

#endif // HWINTERFACE_H
