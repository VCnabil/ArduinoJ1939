#ifndef DIGITALINTERFACE_H
#define DIGITALINTERFACE_H

#include <Arduino.h>


class DigitalInterface {
public:
  DigitalInterface();
  void setup();
  void run();
  int getRED_LEDState();
  int getGreen_LEDState();
  int getDIPState(int index); // Method to query DIP switch state
private:
  const int BUTTON_R_PIN = 35;
  const int LED_red_PIN = 37;
  int ledRedState;
  int last_R_ButtonState;
  int current_R_ButtonState;
  unsigned long lastDebounceTime_R;  // the last time the output pin was toggled
  unsigned long debounceDelay;   


  const int BUTTON_L_PIN = 39;
  const int Green_red_PIN = 41;
  int ledGreenState;
  int last_L_ButtonState;
  int current_L_ButtonState;
  unsigned long lastDebounceTime_L; 

  const int DIP_PINS[6] = {33, 31, 29, 27, 25, 23};
  int DIP_Pin_states[6];
  
};

#endif // DIGITALINTERFACE_H
