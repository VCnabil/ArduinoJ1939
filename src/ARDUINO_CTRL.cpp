#include "ARDUINO_CTRL.h"

 ARDUINO_CTRL::ARDUINO_CTRL() : pgnFF02(0xFF8E, 6, 8, 0x00, 0x00) {
//   // Constructor body
 }

// ARDUINO_CTRL::ARDUINO_CTRL() : pgnFF02(0xFEFC, 6, 8, 0x00, 0x00) {
//   // Constructor body
// }
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

    int hackery1= JoyX;
    int hackery2= JoyY;
    if(hackery1>1000)hackery1=1000;
    if(hackery2>1000)hackery1=1000;
    angle=(float)hackery1;
    magnitude=(float) hackery2;

    // byte* bytes_angle = valueConvertor.floatToTwoByteArray(angle); // 35998 is 8C9E
    // byte high_ang = bytes_angle[0];
    // byte low_ang = bytes_angle[1];

    // byte* bytes_mag = valueConvertor.floatToTwoByteArray(magnitude); // should be 100 max
    // byte high_mag = bytes_mag[0];
    // byte low_mag = bytes_mag[1];

    
    byte* bytes_angle = valueConvertor.floatToTwoByteArraySmaller(angle); // 35998 is 8C9E
    byte high_ang = bytes_angle[0];
     byte low_ang = bytes_angle[1];

     byte* bytes_mag = valueConvertor.floatToTwoByteArraySmaller(magnitude); // should be 100 max
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

void ARDUINO_CTRL::RunLoop_SystemInfo()
{

    byte _byteArray_SysFaults[8] = {0,0,0,0,0,0,0,0};
    canSender.sendMessage(0x18,0x18FF8D,0x00, _byteArray_SysFaults );


  byte _arra_FF8C_Sysinfo[8] = {0,7,0,0,0,4,2,0};
  canSender.sendMessage(0x18,0x18FF8C,0x00, _arra_FF8C_Sysinfo );





    byte _byteArray_Info_Active[8] = {0,13,0,0,0,0,0,0};
 // canSender.sendMessage(0x18,0x18FF11,0x00, _byteArray_Info_Active );

      byte _byteArray_InfoChangover[8] = {0,0,0,0,0,0,0,0};
 // canSender.sendMessage(0x18,0x18FF21,0x00, _byteArray_InfoChangover );

}

void ARDUINO_CTRL::RunLoop_Sim_Feedbacks(byte argAddress00011110)
{

    analogueInterface.run();

    int JoyX = analogueInterface.getJoystickX();  // 0    508 ish +/- 5    1020
    int JoyY = analogueInterface.getPot1();

    if(JoyX>1000)JoyX=1000;
    if(JoyY>1000)JoyY=1000;
    
    float joyxF= ((float)JoyX / 1000.0f)*250;
    float joyyF= ((float)JoyY / 1000.0f)*250;

  int joyxInt= (int)joyxF;
  int joyyInt= (int)joyyF;
    
 int slider_L =analogueInterface.getSliderL();
 int slider_R =analogueInterface.getSliderR();
    if(slider_L>1023)JoyX=1023;
    if(slider_R>1023)JoyY=1023;

    float SliderLF= ((float)slider_L / 1023.0f)*250;
    float SliderRF= ((float)slider_R / 1023.0f)*250;

  int SliderLInt= (int)SliderLF;
  int SliderRInt= (int)SliderRF;

    pgnFF02.setByteArrayData(0,SliderLInt);
    pgnFF02.setByteArrayData(2,joyxInt);

    pgnFF02.setByteArrayData(3,joyyInt);
    pgnFF02.setByteArrayData(5,SliderRInt);

  
    byte ardd= 0x00;
    long pgncom=0xFEFC;
    
    canSender.sendMessage(pgnFF02.getPriority(),pgncom,argAddress00011110, pgnFF02.getByteArrayData() );

}
