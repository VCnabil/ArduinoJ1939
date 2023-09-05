#include "canOBJ.h"

CanOBJ canObj;

void setup() {
  canObj.setup();
}

void loop() {
  //canObj.looper();
  canObj.ReadAndSend2Pots();
}