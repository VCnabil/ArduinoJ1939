#include "Arduino.h"
#include "AnalogueInterface.h"

AnalogueInterface::AnalogueInterface() {
  // Constructor
}

void AnalogueInterface::begin() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
}

void AnalogueInterface::run() {
  joystickX = analogRead(A0);
  joystickY = analogRead(A1);
  sliderL = 1023 - analogRead(A2);
  sliderR = 1023 - analogRead(A3);
  pot1=analogRead(A4);
}

int AnalogueInterface::getJoystickX() {
  return joystickX;
}

int AnalogueInterface::getJoystickY() {
  return joystickY;
}

int AnalogueInterface::getSliderL() {
  return sliderL;
}

int AnalogueInterface::getSliderR() {
  return sliderR;
}

int AnalogueInterface::getPot1()
{
  return pot1;
}
