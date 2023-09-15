#include "ARDUINO_CTRL.h"
#include "DigitalInterface.h"
ARDUINO_CTRL arduinoCtrl;
DigitalInterface digiface;
void setup() {
  Serial.begin(115200);
  digiface.setup();
  arduinoCtrl.setup();
}

void loop() {
  digiface.run();
  if(digiface.getRED_LEDState()==HIGH)return; 
  arduinoCtrl.RunLoop_ArduinoController(digiface.getDipNumeric(), digiface.getDIPState(0));
  delay(150);
}



/*
#include "CanSender.h"
#include "canSerialMsgParser.h"
#include "DigitalInterface.h"
#include "AnalogueInterface.h"
#include "ValueConvertor.h"
#include "JoyStickOBJ.h"
#include "PGN_FF02_OBJ.h"

AnalogueInterface analogueInterface;
ValueConvertor valueConvertor;
DigitalInterface digitalInterface; 
CanSender canSender;
CanSerialMsgParser canSerialMsgParser;
JoyStickOBJ joystick;
PGN_FF02_OBJ pgnFF02(0xFF02, 6, 8, 0x09, 0x30);

unsigned char DATA[8];
long PGN_=0xFF02;

void setup() {
  Serial.begin(115200);
  digitalInterface.setup();
  analogueInterface.begin();
  canSender.setup();
   
}


void loopDisplayReceived(){  
    String serialString = Serial.readStringUntil('\n');
    canSerialMsgParser.parseSerialString(serialString);

    Serial.print("Priority: ");
    Serial.println(canSerialMsgParser.getPriority());

    Serial.print("PGN: ");
    Serial.println(canSerialMsgParser.getPGN(), HEX);

    Serial.print("Source Address: ");
    Serial.println(canSerialMsgParser.getSourceAddress(), HEX);
    Serial.print("Message: ");
    unsigned char* message = canSerialMsgParser.getMessage();
    for (int i = 0; i < 8; i++) {
      Serial.print(message[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
void loopSendMessage(){
 // Read and parse the incoming serial string
    String serialString = Serial.readStringUntil('\n');
    canSerialMsgParser.parseSerialString(serialString);
    // Retrieve the parsed values
    int priority = canSerialMsgParser.getPriority();
    long PGN = canSerialMsgParser.getPGN();
    byte sourceAddress = canSerialMsgParser.getSourceAddress();
    unsigned char* message = canSerialMsgParser.getMessage();
    // Send the CAN message using the parsed values
    canSender.sendMessage(priority, PGN, sourceAddress, message);

  
}

void looppots() {
 analogueInterface.run();

  int joystickX = analogueInterface.getJoystickX();
  int joystickY = analogueInterface.getJoystickY();
  int sliderL = analogueInterface.getSliderL();
  int sliderR = analogueInterface.getSliderR();

  Serial.print("Joystick X: "); Serial.println(joystickX);
  Serial.print("Joystick Y: "); Serial.println(joystickY);
  Serial.print("Slider L: "); Serial.println(sliderL);
  Serial.print("Slider R: "); Serial.println(sliderR);


  delay(500);
}
void loopDips(){
  digitalInterface.run();
  for(int x=0; x<6; x++){
     Serial.print(digitalInterface.getDIPState(x));
      Serial.print(" ");
  }
   Serial.println("");

}

void loop_arbitraryTransmit() {
  analogueInterface.run();
  int sliderL = analogueInterface.getSliderL();
  float floatValueMAPPED_sliderL =valueConvertor.mapFloat(sliderL,0,1023,0.0,19.6);
  valueConvertor.convertToBytes(floatValueMAPPED_sliderL);

  Serial.print(sliderL);
  Serial.print(" ");

  Serial.print(floatValueMAPPED_sliderL);
  Serial.print(" ");
  Serial.print(valueConvertor.getFirstByte(),HEX);
  Serial.print(" ");
  Serial.print(valueConvertor.getSecondByte(),HEX);
  Serial.println("");


 memset(DATA, 0, sizeof(DATA));
DATA[7]=valueConvertor.getFirstByte();
DATA[6]=valueConvertor.getSecondByte();
DATA[5]=valueConvertor.getFirstByte();
DATA[4]=valueConvertor.getSecondByte();
j1939Transmit(PGN_, 0x06, 0x09, 0x09, DATA, 8);

delay(100);
 
}


void loop() {

digitalInterface.run();
if (digitalInterface.getRED_LEDState()== HIGH)
return;

  analogueInterface.run();
  int JoyX = analogueInterface.getJoystickX();  // 0    508 ish +/- 5    1020
  int JoyY = analogueInterface.getJoystickY();

  joystick.updateValues(JoyX, JoyY);
  float angle = joystick.getAngle();
   float magnitude=  joystick.getMagnitude();

byte* bytes = valueConvertor.floatToTwoByteArray(angle); // 35998 is 8C9E
byte high = bytes[0];
byte low = bytes[1];

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




pgnFF02.setByteArrayData(2,low);
pgnFF02.setByteArrayData(3,high);
 // byte* byteArray = pgnFF02.getByteArrayData();

j1939Transmit(pgnFF02.getPgn(), pgnFF02.getPriority(), pgnFF02.getSourceAddress(),  pgnFF02.getSourceAddress(), pgnFF02.getByteArrayData(), 8);
 delay(150);
 return;

  //Serial.print(cartesianX);
  Serial.print(" ");
  Serial.print(JoyX); //9E  for the input   35998 is 8C9E
  Serial.print(" ");
  Serial.print(JoyY); //8C   for the input   35998 is 8C9E
  Serial.print(" ");
  Serial.print(magnitude);
  Serial.println("");

 

 
}

*/