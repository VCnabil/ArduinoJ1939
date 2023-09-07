#ifndef JoyStickOBJ_h
#define JoyStickOBJ_h

#include "Arduino.h"
#include "ValueConvertor.h"

class JoyStickOBJ {
public:
  JoyStickOBJ();
  void updateValues(int rawX, int rawY);
  float getAngle();

private:
  ValueConvertor valueConvertor;
  int filtered_X;
  int filtered_Y;
  int cartesianX;
  int cartesianY;
  float angle;
  void filterValues(int rawX, int rawY);
};

#endif
