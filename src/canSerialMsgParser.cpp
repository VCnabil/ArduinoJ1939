#include "canSerialMsgParser.h"

int priority;
long PGN;
byte nSourceAddr;
unsigned char msgRequest[8];

CanSerialMsgParser::CanSerialMsgParser() {
  // Constructor
}

void CanSerialMsgParser::parseSerialString(const String& serialString) {
  char* token;
  char buf[50];
  serialString.toCharArray(buf, 50);

  // Parse priority
  token = strtok(buf, ",");
  priority = atoi(token);

  // Parse PGN
  token = strtok(NULL, ",");
  PGN = strtol(token, NULL, 16);

  // Parse source address
  token = strtok(NULL, ",");
  nSourceAddr = strtol(token, NULL, 16);

  // Initialize message bytes to zero
  memset(msgRequest, 0, sizeof(msgRequest));

  // Parse message bytes
  for (int i = 0; i < 8; i++) {
    token = strtok(NULL, ",");
    if (token != NULL) {
      msgRequest[i] = strtol(token, NULL, 16);
    }
  }
}

int CanSerialMsgParser::getPriority() {
  return priority;
}

long CanSerialMsgParser::getPGN() {
  return PGN;
}

byte CanSerialMsgParser::getSourceAddress() {
  return nSourceAddr;
}

unsigned char* CanSerialMsgParser::getMessage() {
  return msgRequest;
}
