#ifndef CANSENDER_H
#define CANSENDER_H

#include <Arduino.h>
#include <mcp_can.h>
#include <can_ext.h>

class CanSender {
public:
  CanSender();
  void setup();
  void sendMessage(int priority, long PGN, byte sourceAddress, unsigned char* message);
};

#endif // CANSENDER_H
