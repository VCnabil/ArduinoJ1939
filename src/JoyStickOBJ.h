#ifndef JoyStickOBJ_h
#define JoyStickOBJ_h

#include "Arduino.h"
#include "ValueConvertor.h"

class JoyStickOBJ {
public:
  JoyStickOBJ();
  void updateValues(int rawX, int rawY);
  float getAngle();
  float getMagnitude();

private:
  ValueConvertor valueConvertor;
  int deadzoneX ;
  int centerX ;
  int deadzoneY ;
  int centerY ;
  int max_x;
  int max_y;

  int filtered_X;
  int filtered_Y;
  int cartesianX;
  int cartesianY;
  float angle;
  float magnitude_percentage;
  void filterValues(int rawX, int rawY);
  //float calculateMagnitudePercentage(int x, int y);
};

#endif
