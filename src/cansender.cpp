#include "CanSender.h"
#define NODE_Response 0x30
CanSender::CanSender() {
  // Constructor
}

void CanSender::setup() {
  if (canInitialize(CAN_250KBPS) == CAN_OK) {
    Serial.print("CAN Init OK.\n\r\n\r");
  } else {
    Serial.print("CAN Init Failed.\n\r");
  }
}

void CanSender::sendMessage(int priority, long PGN, byte sourceAddress, unsigned char* message) {
  j1939Transmit(PGN, priority, sourceAddress, NODE_Response, message, 8);
}
