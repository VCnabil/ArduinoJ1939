#include "PGN_FF02_OBJ.h"

PGN_FF02_OBJ::PGN_FF02_OBJ(long pgn, int priority, int dataLength, byte sourceAddress, byte destAddress)
    : _pgn(pgn), _priority(priority), _dataLength(dataLength), _sourceAddress(sourceAddress), _destAddress(destAddress) {

         memset(_byteArray, 0, sizeof(_byteArray));
    }

long PGN_FF02_OBJ::getPgn() const {
    return _pgn;
}

int PGN_FF02_OBJ::getPriority() const {
    return _priority;
}

int PGN_FF02_OBJ::getDataLength() const {
    return _dataLength;
}

byte PGN_FF02_OBJ::getSourceAddress() const {
    return _sourceAddress;
}

byte PGN_FF02_OBJ::getDestAddress() const {
    return _destAddress;
}


void PGN_FF02_OBJ::setByteArrayData(int index, byte argByteValue) {
    if (index >= 0 && index < 8) {
        _byteArray[index] = argByteValue;
    }
}

 byte* PGN_FF02_OBJ::getByteArrayData()  {
    return _byteArray; // Return a pointer to the whole byte array
}
