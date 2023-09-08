#ifndef PGN_FF02_OBJ_h
#define PGN_FF02_OBJ_h

#include <Arduino.h>

class PGN_FF02_OBJ {
public:
    PGN_FF02_OBJ(long pgn, int priority, int dataLength, byte sourceAddress, byte destAddress);
    long getPgn() const;
    int getPriority() const;
    int getDataLength() const;
    byte getSourceAddress() const;
    byte getDestAddress() const;
    
  
    void setByteArrayData(int index, byte argByteValue);
     byte* getByteArrayData() ; // Return the whole byte array


private:
    long _pgn;
    int _priority;
    int _dataLength;
    byte _sourceAddress;
    byte _destAddress;
    byte _byteArray[8];
};

#endif
