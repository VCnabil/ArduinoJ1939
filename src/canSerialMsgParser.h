#ifndef CANSERIALMSGPARSER_H
#define CANSERIALMSGPARSER_H

#include <Arduino.h>

class CanSerialMsgParser {
public:
  CanSerialMsgParser();
  void parseSerialString(const String& serialString);
  int getPriority();
  long getPGN();
  byte getSourceAddress();
  unsigned char* getMessage();
};

#endif // CANSERIALMSGPARSER_H
