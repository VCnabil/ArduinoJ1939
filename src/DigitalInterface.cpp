#include "DigitalInterface.h"

DigitalInterface::DigitalInterface() : 
    ledRedState(LOW), 
    last_R_ButtonState(HIGH), 
    current_R_ButtonState(HIGH), 
    lastDebounceTime_R(0), 
    debounceDelay(50),
    ledGreenState(LOW), 
    last_L_ButtonState(HIGH), 
    current_L_ButtonState(HIGH), 
    lastDebounceTime_L(0) 
    {
        //contructor
        // Initialize DIP_Pin_states to LOW
        for (int i = 0; i < 6; ++i) {
            DIP_Pin_states[i] = LOW;
        }
}

void DigitalInterface::setup() {
  pinMode(BUTTON_R_PIN, INPUT_PULLUP);
  pinMode(LED_red_PIN, OUTPUT);
  current_R_ButtonState = digitalRead(BUTTON_R_PIN);

  pinMode(BUTTON_L_PIN, INPUT_PULLUP);
  pinMode(Green_red_PIN, OUTPUT);
  current_L_ButtonState = digitalRead(BUTTON_L_PIN);

        // Initialize DIP switch pins
    for (int i = 0; i < 6; ++i) {
        pinMode(DIP_PINS[i], INPUT_PULLUP);
    }
}

void DigitalInterface::run() { 
  // Handling the right button and red LED
  int reading_R = digitalRead(BUTTON_R_PIN);
  if (reading_R != last_R_ButtonState) {
    lastDebounceTime_R = millis();
  }
  if ((millis() - lastDebounceTime_R) > debounceDelay) {
    if (reading_R != current_R_ButtonState) {
      current_R_ButtonState = reading_R;
      if (current_R_ButtonState == LOW) {
        ledRedState = !ledRedState;
        digitalWrite(LED_red_PIN, ledRedState);
      }
    }
  }
  last_R_ButtonState = reading_R;

  // Handling the left button and green LED
  int reading_L = digitalRead(BUTTON_L_PIN);
  if (reading_L != last_L_ButtonState) {
    lastDebounceTime_L = millis();
  }
  if ((millis() - lastDebounceTime_L) > debounceDelay) {
    if (reading_L != current_L_ButtonState) {
      current_L_ButtonState = reading_L;
      if (current_L_ButtonState == LOW) {
        ledGreenState = !ledGreenState;
        digitalWrite(Green_red_PIN, ledGreenState);
      }
    }
  }
  last_L_ButtonState = reading_L;

    // Update DIP switch states
  for (int i = 0; i < 6; ++i) {
    DIP_Pin_states[i] = !digitalRead(DIP_PINS[i]);
  }
}

int DigitalInterface::getRED_LEDState() {
  // For now, returning red LED state; you may want to extend this
  return ledRedState;
}

int DigitalInterface::getGreen_LEDState() {
  // For now, returning red LED state; you may want to extend this
  return ledGreenState;
}

int DigitalInterface::getDIPState(int index) {
  if (index >= 0 && index < 6) {
    return DIP_Pin_states[index];
  }
  return -1; // Invalid index
}