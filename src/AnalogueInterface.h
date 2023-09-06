#ifndef AnalogueInterface_h
#define AnalogueInterface_h

#include "Arduino.h"

class AnalogueInterface {
  public:
    AnalogueInterface();
    void begin();
    void run();
    int getJoystickX();
    int getJoystickY();
    int getSliderL();
    int getSliderR();
      private:
    int joystickX;
    int joystickY;
    int sliderL;
    int sliderR;
};

#endif
