/*
SyntacticalType

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/


#ifndef SYNTACTICALTYPE_H
#define SYNTACTICALTYPE_H

typedef enum SyntacticalType {
    floatSType = 0,
    intSType,
    boolSType,
    charSType,
    undefinedSType,
} SyntacticalType;

int getSizeForSyntacticalType(SyntacticalType type);

#endif