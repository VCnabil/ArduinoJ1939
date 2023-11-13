#include "Arduino.h"
#include "ValueConvertor.h"

ValueConvertor::ValueConvertor() {
  // Constructor
}

#pragma region Angles


//watch out this one returns
// 0-90 when swiping around CCW from east north 
// -89 - -0 CCW swiping north to west
// 0 - 90  swipping CCW east to south 
// -90 - -0  swipping CCW  south  to` east
int radtodeg(float rad) { return rad * (180 / M_PI); }


int vectorangle_EAST(int x, int y) {
  if (x == 0) // special cases
      return (y > 0) ? 90
      : (y == 0) ? 0
      : 270;
  else if (y == 0) // special cases
      return (x >= 0) ? 0
      : 180;

  int ret = radtodeg(atanf((float)y / x));
  if (x < 0 && y < 0) // quadrant III
      ret = 180 + ret;
  else if (x < 0) // quadrant II
      ret = 180 + ret; // it actually substracts
  else if (y < 0) // quadrant IV
      ret = 270 + (90 + ret); // it actually substracts    
  return ret; 
}
int vectorangle_NORTH(int x, int y) {

 

int ret = radtodeg(atanf((float)y / x));

    if (x == 0 && y == 0) {
        return 0;
    }

    // Special cases for cardinal directions
    if (x == 0 && y > 0) ret= 0;
    else
    if (x == 0 && y < 0) ret= 180;
     else
    if (x > 0 && y == 0) ret= 270;
     else
    if (x < 0 && y == 0) ret= 90;
     else

    if (x > 0 && y > 0) ret = 270 + ret; // quadrant  1
     else
    if (x < 0 && y > 0) ret = 90 + ret; // quadrant  2
     else
    if (x < 0 && y < 0) ret = 90 + ret; // quadrant  3           
      else
    if (x > 0 && y < 0) ret = 270 + ret; // quadrant  4      


return ret; 



 
}

//watch out this one returns
// 0-180 when swiping around CCW from east north west
// -180 - -0 swipping CW east south west
float RADtoDEG(float rad) {
    return rad * (180.0 / 3.141592653589793238463);
}

float VECTORtoAUNGLE_EAST(int x, int y) {
    if (x == 0) // special cases
        return (y > 0) ? 90.0
        : (y == 0) ? 0.0
        : 270.0;
    else if (y == 0) // special cases
        return (x >= 0) ? 0.0
        : 180.0;

    float ret = RADtoDEG(atan2((float)y, (float)x));
    if (ret < 0) {
        ret = 360 + ret;
    }
 
    return ret;
}

float VECTORtoAUNGLE_NORTH(int x, int y) {
  float ret = RADtoDEG(atan2((float)y, (float)x));
  if (x == 0 && y == 0) {return 0.0f;}
  // Special cases for cardinal directions
  if (x == 0 && y > 0) ret= 0.0f;
  else
  if (x == 0 && y < 0) ret= 180.0f;
    else
  if (x > 0 && y == 0) ret= 270.0f;
    else
  if (x < 0 && y == 0) ret= 90.0f;
    else
  if (x > 0 && y > 0) ret = 270.0f + ret; // quadrant  1
    else
  if (x < 0 && y > 0) ret = ret-90.0f; // quadrant  2
    else
  if (x < 0 && y < 0) ret =  ret+270.0f ; // quadrant  3           
    else
  if (x > 0 && y < 0) ret = 270.0f + ret;//   quadrant  4      
    return ret;
}

#pragma endregion


void ValueConvertor::convertToBytes(float argValue) {
  uint16_t val = (uint16_t)(argValue * 256);  // Assuming 2 decimal places
  B_first = (val >> 8) & 0xFF;
  B_second = val & 0xFF;
}

float ValueConvertor::convertToFloat(byte argB1, byte argB2) {
  uint16_t val = ((uint16_t)argB1 << 8) | argB2;
  floatVal = val / 100.0;
  return floatVal;
}

float ValueConvertor::mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
    floatMapped= (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    return floatMapped;
}
 

byte ValueConvertor::getFirstByte() {
  return B_first;
}

byte ValueConvertor::getSecondByte() {
  return B_second;
}

int ValueConvertor::getAngle_INT(int arg_cartesianX, int arg_cartesianY){
  
   return vectorangle_NORTH(arg_cartesianX,arg_cartesianY);
   
   }
float ValueConvertor::getAngle_FLOAT(int arg_cartesianX, int arg_cartesianY){return VECTORtoAUNGLE_NORTH(arg_cartesianX,arg_cartesianY);}

// Function to convert float to two bytes and return as byte array
byte* ValueConvertor::floatToTwoByteArray(float value) {
  static byte result[2];  // Static so it persists outside the function
  uint16_t intVal = (uint16_t)(value * 100);  // Convert float to integer

  result[0] = (intVal >> 8) & 0xFF;  // High byte
  result[1] = intVal & 0xFF;         // Low byte

  return result;
}

byte* ValueConvertor::floatToTwoByteArraySmaller(float value) {
  static byte result[2];  // Static so it persists outside the function
  uint16_t intVal = (uint16_t)(value * 1);  // Convert float to integer

  result[0] = (intVal >> 8) & 0xFF;  // High byte
  result[1] = intVal & 0xFF;         // Low byte

  return result;
}





/*
usage
ValueConvertor valueConvertor;
byte* bytes = valueConvertor.floatToTwoByteArray(359.98f);
byte high = bytes[0];
byte low = bytes[1];
*/