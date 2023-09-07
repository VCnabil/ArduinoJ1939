#include "CanSender.h"
#include "canSerialMsgParser.h"
#include "DigitalInterface.h"
#include "AnalogueInterface.h"
#include "ValueConvertor.h"

AnalogueInterface analogueInterface;
ValueConvertor valueConvertor;
DigitalInterface digitalInterface; 
CanSender canSender;
CanSerialMsgParser canSerialMsgParser;

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
j1939Transmit(PGN_, 0x06, 0x09, 0x30, DATA, 8);

delay(100);
 
}


void loop() {
  analogueInterface.run();
  int deadzoneX=12;
  int centerX=500;
  int deadzoneY=12;
  int centerY=500; 
  int deadzoneX_Lower= centerX -deadzoneX;
  int deadzoneX_Upper= centerX +deadzoneX;
  int deadzoneY_Lower= centerY -deadzoneY;
  int deadzoneY_Upper= centerY +deadzoneY;


  int JoyX = analogueInterface.getJoystickX();  // 0    508 ish +/- 5    1020
 
  int JoyY = analogueInterface.getJoystickY();

 int filtered_X= JoyX;
 if (filtered_X> deadzoneX_Lower && filtered_X < deadzoneX_Upper) filtered_X=centerX;
 int filtered_Y= JoyY;
 if (filtered_Y> deadzoneY_Lower && filtered_Y < deadzoneY_Upper) filtered_Y=centerY;

 if(filtered_X>1000)filtered_X=1000;
 if(filtered_Y>1000)filtered_Y=1000;

 int cartesianX=filtered_X-centerX;
 
 int cartesianY=filtered_Y-centerY;



  //Serial.print(cartesianX);
  Serial.print(" ");
  Serial.print(valueConvertor.getAngle_INT(cartesianX,cartesianY));
  Serial.print(" ");
  Serial.println("");

 
delay(100);
 
}