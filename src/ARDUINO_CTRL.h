#ifndef ARDUINO_CTRL_H
#define ARDUINO_CTRL_H

#include "CanSender.h"
#include "AnalogueInterface.h"
#include "ValueConvertor.h"
#include "JoyStickOBJ.h"
#include "PGN_FF02_OBJ.h"

class ARDUINO_CTRL {
public:
  ARDUINO_CTRL();
  void setup();
  void RunLoop_ArduinoController(int argMod,int argUSePotIfDip0IsOn);
private:
  AnalogueInterface analogueInterface;
  ValueConvertor valueConvertor;
  CanSender canSender;
  JoyStickOBJ joystick;
  PGN_FF02_OBJ pgnFF02;
};

#endif // ARDUINO_CTRL_H
