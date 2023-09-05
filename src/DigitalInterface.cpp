#include "DigitalInterface.h"
DigitalInterface::DigitalInterface() : ledState(LOW), lastButtonState(HIGH), currentButtonState(HIGH), lastDebounceTime(0), debounceDelay(50) {
  // Constructor
}

void DigitalInterface::setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  currentButtonState = digitalRead(BUTTON_PIN);
}

void DigitalInterface::run() { 
    int reading = digitalRead(BUTTON_PIN);
  
  // If the logic level has changed, reset the debouncing timer
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the button state has changed
    if (reading != currentButtonState) {
      currentButtonState = reading;
      
      // If the new button state is LOW, then the button was pressed
      if (currentButtonState == LOW) {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
      }
    }
  }
  
  lastButtonState = reading;
}

int DigitalInterface::getLEDState() {
  return ledState;
}
