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
void ARDUINO_CTRL::RunLoop_ArduinoController(int argMod, int argUSePotIfDip0IsOn) {
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




    pgnFF02.setByteArrayData(0,low_mag);
    pgnFF02.setByteArrayData(1,high_mag);

    pgnFF02.setByteArrayData(2,low_ang);
    pgnFF02.setByteArrayData(3,high_ang);

    int sliderL =0;
    if(argUSePotIfDip0IsOn==HIGH){
      sliderL = analogueInterface.getPot1();
    }
    else
    {
      sliderL = analogueInterface.getSliderL();
    }
    float floatValueMAPPED_sliderL =valueConvertor.mapFloat(sliderL,0,1023,0.0,19.6);
    valueConvertor.convertToBytes(floatValueMAPPED_sliderL);

    pgnFF02.setByteArrayData(4,valueConvertor.getSecondByte());
    pgnFF02.setByteArrayData(5,valueConvertor.getFirstByte());

    int sliderR = analogueInterface.getSliderR();
    float floatValueMAPPED_sliderR =valueConvertor.mapFloat(sliderR,0,1023,0.0,19.6);
    valueConvertor.convertToBytes(floatValueMAPPED_sliderR);

    pgnFF02.setByteArrayData(6,valueConvertor.getSecondByte());
    pgnFF02.setByteArrayData(7,valueConvertor.getFirstByte());

    canSender.sendMessage(pgnFF02.getPriority(),pgnFF02.getPgn(),pgnFF02.getSourceAddress(), pgnFF02.getByteArrayData() );


if(argMod==0){return;}
else
if(argMod==1){
    Serial.print("Uhex");
    Serial.print("|");
    Serial.print(argMod);
    Serial.print("|");
    Serial.print(pgnFF02.getPgn(),HEX); 
    Serial.print("|");
    Serial.print(pgnFF02.getSourceAddress(),HEX); 
    Serial.print("|");
    byte value= pgnFF02.getByteArrayData()[0];
    if (value < 0x10) {Serial.print("0");}
    Serial.print(pgnFF02.getByteArrayData()[0],HEX);
    Serial.print("|");
     value= pgnFF02.getByteArrayData()[1];
    if (value < 0x10) {Serial.print("0");}
    Serial.print(pgnFF02.getByteArrayData()[1],HEX);
    Serial.print("|");
     value= pgnFF02.getByteArrayData()[2];
    if (value < 0x10) {Serial.print("0");}
    Serial.print(pgnFF02.getByteArrayData()[2],HEX);
    Serial.print("|");
     value= pgnFF02.getByteArrayData()[3];
    if (value < 0x10) {Serial.print("0");}
    Serial.print(pgnFF02.getByteArrayData()[3],HEX);
    Serial.print("|");
     value= pgnFF02.getByteArrayData()[4];
    if (value < 0x10) {Serial.print("0");}
    Serial.print(pgnFF02.getByteArrayData()[4],HEX);
    Serial.print("|");
     value= pgnFF02.getByteArrayData()[5];
    if (value < 0x10) {Serial.print("0");}
    Serial.print(pgnFF02.getByteArrayData()[5],HEX);
    Serial.print("|");
     value= pgnFF02.getByteArrayData()[6];
    if (value < 0x10) {Serial.print("0");}
    Serial.print(pgnFF02.getByteArrayData()[6],HEX);
    Serial.print("|");
     value= pgnFF02.getByteArrayData()[7];
    if (value < 0x10) {Serial.print("0");}
    Serial.print(pgnFF02.getByteArrayData()[7],HEX);
    Serial.print("|");
    Serial.println("uhex");
}
else
if(argMod==2){
    Serial.print("Udec");
    Serial.print("|");
    Serial.print(argMod);
    Serial.print("|");
    Serial.print(pgnFF02.getPgn(),HEX); 
    Serial.print("|");
    Serial.print(pgnFF02.getSourceAddress(),HEX); 
    Serial.print("|");
    Serial.print(pgnFF02.getByteArrayData()[0]);
    Serial.print("|");
    Serial.print(pgnFF02.getByteArrayData()[1]);
    Serial.print("|");
    Serial.print(pgnFF02.getByteArrayData()[2]);
    Serial.print("|");
    Serial.print(pgnFF02.getByteArrayData()[3]);
    Serial.print("|");
    Serial.print(pgnFF02.getByteArrayData()[4]);
    Serial.print("|");
    Serial.print(pgnFF02.getByteArrayData()[5]);
    Serial.print("|");
    Serial.print(pgnFF02.getByteArrayData()[6]);
    Serial.print("|");
    Serial.print(pgnFF02.getByteArrayData()[7]);
    Serial.print("|");
    Serial.println("udec");
}
else
if(argMod==3){
    Serial.print("Upec");
    Serial.print("|");
    Serial.print(argMod);
    Serial.print("|");
    Serial.print(pgnFF02.getPgn(),HEX); 
    Serial.print("|");
    Serial.print(pgnFF02.getSourceAddress(),HEX); 
    Serial.print("|");
    Serial.print(magnitude);
    Serial.print("|");
    Serial.print(angle);
    Serial.print("|");
    Serial.print(sliderL);
    Serial.print("|");
    Serial.print(sliderR);
    Serial.print("|");
    Serial.print( "0");
    Serial.print("|");
    Serial.print( "0");
    Serial.print("|");
    Serial.print( "0");
    Serial.print("|");
    Serial.print( "0");
    Serial.print("|");
    Serial.println("uperc");
}





  //j1939Transmit(pgnFF02.getPgn(), pgnFF02.getPriority(), pgnFF02.getSourceAddress(),  pgnFF02.getSourceAddress(), pgnFF02.getByteArrayData(), 8);
  //delay(150);
}
