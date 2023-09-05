#ifndef DIGITALINTERFACE_H
#define DIGITALINTERFACE_H

#include <Arduino.h>


class DigitalInterface {
public:
  DigitalInterface();
  void setup();
  void run();
  int getLEDState();
private:
  const int BUTTON_PIN = 7;
  const int LED_PIN = 23;
  int ledState;
  int lastButtonState;
  int currentButtonState;
  unsigned long lastDebounceTime;  // the last time the output pin was toggled
  unsigned long debounceDelay;   
};

#endif // DIGITALINTERFACE_H
