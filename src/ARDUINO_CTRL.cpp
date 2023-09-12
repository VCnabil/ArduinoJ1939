#include "ARDUINO_CTRL.h"

ARDUINO_CTRL::ARDUINO_CTRL() : pgnFF02(0xFF02, 6, 8, 0x09, 0x30) {
  // Constructor body
}

void ARDUINO_CTRL::setup() {
  analogueInterface.begin();
  canSender.setup();
}


//  ** **   ** **   ** **   ** **
//  0  1 
//  mag
//          2  3
//          angle 
//                  4  5
//                  sliderL
//                           6  7
//                           sliderT
void ARDUINO_CTRL::RunLoop_ArduinoController() {
  analogueInterface.run();

  int JoyX = analogueInterface.getJoystickX();  // 0    508 ish +/- 5    1020
  int JoyY = analogueInterface.getJoystickY();

  joystick.updateValues(JoyX, JoyY);
  float angle = joystick.getAngle();
  float magnitude=  joystick.getMagnitude();

  byte* bytes_angle = valueConvertor.floatToTwoByteArray(angle); // 35998 is 8C9E
  byte high_ang = bytes_angle[0];
  byte low_ang = bytes_angle[1];

  byte* bytes_mag = valueConvertor.floatToTwoByteArray(magnitude); // should be 100 max
  byte high_mag = bytes_mag[0];
  byte low_mag = bytes_mag[1];

  int sliderL = analogueInterface.getSliderL();
  float floatValueMAPPED_sliderL =valueConvertor.mapFloat(sliderL,0,1023,0.0,19.6);
  valueConvertor.convertToBytes(floatValueMAPPED_sliderL);

  pgnFF02.setByteArrayData(4,valueConvertor.getSecondByte());
  pgnFF02.setByteArrayData(5,valueConvertor.getFirstByte());

  int sliderR = analogueInterface.getSliderR();
  float floatValueMAPPED_sliderR =valueConvertor.mapFloat(sliderR,0,1023,0.0,19.6);
  valueConvertor.convertToBytes(floatValueMAPPED_sliderR);

  pgnFF02.setByteArrayData(6,valueConvertor.getSecondByte());
  pgnFF02.setByteArrayData(7,valueConvertor.getFirstByte());

  pgnFF02.setByteArrayData(2,low_ang);
  pgnFF02.setByteArrayData(3,high_ang);

  pgnFF02.setByteArrayData(0,low_mag);
  pgnFF02.setByteArrayData(1,high_mag);

  canSender.sendMessage(pgnFF02.getPriority(),pgnFF02.getPgn(),pgnFF02.getSourceAddress(), pgnFF02.getByteArrayData() );
  //j1939Transmit(pgnFF02.getPgn(), pgnFF02.getPriority(), pgnFF02.getSourceAddress(),  pgnFF02.getSourceAddress(), pgnFF02.getByteArrayData(), 8);
  //delay(150);
}
