/*
SyntacticalType

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/


#include "SyntacticalType.hpp"
#include <string.h>

int getSizeForSyntacticalType(SyntacticalType type) {
    switch (type)
    {
    case floatSType:
        return 8;
    case intSType:
        return 4;
    case boolSType:
        return 1;
    case charSType:
        return 1;
    default:
        return 0;
    }
}