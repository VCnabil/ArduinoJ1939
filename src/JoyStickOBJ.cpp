#include "JoyStickOBJ.h"

JoyStickOBJ::JoyStickOBJ() {
  // Constructor
}

void JoyStickOBJ::updateValues(int rawX, int rawY) {
  filterValues(rawX, rawY);
  cartesianX = filtered_X - 500;  // Assuming 500 is the center for X
  cartesianY = filtered_Y - 500;  // Assuming 500 is the center for Y
  angle = valueConvertor.getAngle_FLOAT(cartesianX, cartesianY);
}

float JoyStickOBJ::getAngle() {
  return angle;
}

void JoyStickOBJ::filterValues(int rawX, int rawY) {
  int deadzoneX = 12;
  int centerX = 500;
  int deadzoneY = 12;
  int centerY = 500;
  int deadzoneX_Lower = centerX - deadzoneX;
  int deadzoneX_Upper = centerX + deadzoneX;
  int deadzoneY_Lower = centerY - deadzoneY;
  int deadzoneY_Upper = centerY + deadzoneY;

  filtered_X = rawX;
  filtered_Y = rawY;

  if (filtered_X > deadzoneX_Lower && filtered_X < deadzoneX_Upper) filtered_X = centerX;
  if (filtered_Y > deadzoneY_Lower && filtered_Y < deadzoneY_Upper) filtered_Y = centerY;

  if (filtered_X > 1000) filtered_X = 1000;
  if (filtered_Y > 1000) filtered_Y = 1000;
}
