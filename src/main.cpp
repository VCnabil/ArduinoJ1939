#include "CanSender.h"
#include "canSerialMsgParser.h"
//#include "HWInterface.h"
#include "DigitalInterface.h"
#include "AnalogueInterface.h"
//HWInterface hwInterface;
AnalogueInterface analogueInterface;
DigitalInterface digitalInterface; 
CanSender canSender;
CanSerialMsgParser canSerialMsgParser;

void setup() {
  Serial.begin(115200);
  digitalInterface.setup();
  analogueInterface.begin();
  // hwInterface.setup();
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
// void loopSendPots(){
 
//  unsigned char* message = hwInterface.getMessage();
//  canSender.sendMessage(6, 0x18FF02, 0x09, message);
//     for (int i = 0; i < 8; i++) {
//       Serial.print(message[i], HEX);
//       Serial.print(" ");
//     }
//     Serial.println();

// }
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
void loop() {
  //  digitalInterface.run();
looppots();
  //  if(digitalInterface.getLEDState()==HIGH){
  //   loopSendPots();
  //  }
  //  else{
  //   if (Serial.available()) {
  //     loopSendMessage();

  //     }
  //  }
}
