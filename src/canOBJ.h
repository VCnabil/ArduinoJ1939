#ifndef CANOBJ_H
#define CANOBJ_H

#include <Arduino.h>
#include <mcp_can.h>
#include <can_ext.h>

class CanOBJ {
public:
  CanOBJ();
  void setup();
  void looper();
  bool ReadSerialMonitorString() ;
  void ReadAndSend2Pots();
  float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
};

#endif // CANOBJ_H