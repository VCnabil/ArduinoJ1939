#include "JoyStickOBJ.h"

JoyStickOBJ::JoyStickOBJ() {
  // Constructor
    deadzoneX = 15;
   centerX = 500;
   deadzoneY = 15;
   centerY = 500;
   max_x=1000;
   max_y=1000;
}

float  calculateMagnitudePercentage(int x, int y){
// Calculate the magnitude of the vector

    if (x<0)x*=-1;
    if(y<0)y*=-1;
    float xfloat= static_cast<float>(x);
    float yfloat= static_cast<float>(y);
    float xyxy= (xfloat * xfloat) + (yfloat * yfloat);
    float magnitude = sqrtf(xyxy);
    if (magnitude>502.0f) magnitude=502.0f;
   if (magnitude <= 0.0f) magnitude=0.0f; 
       // Calculate the percentage as a fraction of 500
    float percentage = (magnitude / 502.0f) * 100.0f;
    if(percentage<0.0f)percentage=0.0f;
    if(percentage>100.0f)percentage=100.0f;

// don't serial print anywhere else but from serialmanager
    // Serial.print("x= ");
    // Serial.print(x );
    // Serial.print(" y= ");
    // Serial.print(y);
    // Serial.print(" m= ");
    // Serial.print(magnitude);
    // Serial.print(" %= ");
    // Serial.print(percentage);

    // Serial.println(" ");

    // Ensure that the magnitude is not zero before calculating the percentage
 



  
 return percentage;
     
}   

void JoyStickOBJ::updateValues(int rawX, int rawY) {
  filterValues(rawX, rawY);
  cartesianX = filtered_X - 500;  // Assuming 500 is the center for X
  cartesianY = filtered_Y - 500;  // Assuming 500 is the center for Y
  angle = valueConvertor.getAngle_FLOAT(cartesianX, cartesianY);
  magnitude_percentage=calculateMagnitudePercentage(cartesianX, cartesianY);
}

float JoyStickOBJ::getAngle() {
  return angle;
}

float JoyStickOBJ::getMagnitude()
{
  return magnitude_percentage;
}

void JoyStickOBJ::filterValues(int rawX, int rawY) {

  int deadzoneX_Lower = centerX - deadzoneX;
  int deadzoneX_Upper = centerX + deadzoneX;
  int deadzoneY_Lower = centerY - deadzoneY;
  int deadzoneY_Upper = centerY + deadzoneY;

  filtered_X = rawX;
  filtered_Y = rawY;

  if (filtered_X > deadzoneX_Lower && filtered_X < deadzoneX_Upper) filtered_X = centerX;
  if (filtered_Y > deadzoneY_Lower && filtered_Y < deadzoneY_Upper) filtered_Y = centerY;

  if (filtered_X > max_x) filtered_X = max_x;
  if (filtered_Y > max_y) filtered_Y = max_y;
}

