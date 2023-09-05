// #include "canOBJ.h"

// CanOBJ canObj;

// void setup() {
//   canObj.setup();
// }

// void loop() {
//   //canObj.looper();
//   canObj.ReadAndSend2Pots();
// }


#include "CanSender.h"
#include "canSerialMsgParser.h"

CanSender canSender;
CanSerialMsgParser canSerialMsgParser;

void setup() {
  canSender.setup();
  Serial.begin(115200);
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

void loop() {
  if (Serial.available()) {
  //loopDisplayReceived();
   loopSendMessage();
  }
}
