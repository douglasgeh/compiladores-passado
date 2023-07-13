/*
SymbleTableNode

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/

#ifndef SYMBOLE_TABLE_NODE_HX
#define SYMBOLE_TABLE_NODE_HX

#include <stdio.h>
#include "SyntacticalType.h"
#include "ValorLexico.h"

typedef enum {
    literalKind = 1,
    variableKind,
    functionKind,
    vectorKind,
} Kind;

typedef struct {
    int line;
    int column;
    Kind kind;
    SyntacticalType type;
    int size;
    ValorLexico *lexicalValue;
   // Todo parametros de funcao
} SymbolTableNode;

void printValue(SymbolTableNode symbolTableValue);
void printKind(Kind kind);
void printSyntacticalType(SyntacticalType type);

SymbolTableNode createNode(int line, int column, ValorLexico* lexicalValue, SyntacticalType sType, Kind kind);
SymbolTableNode createLiteral(int line, int column, ValorLexico *lexicalValue, SyntacticalType sType);
SymbolTableNode createVariableWithUndefinedType(int line, int column, ValorLexico *lexicalValue);
SymbolTableNode createFunctionWithTypeNoParameters(int line, int column, ValorLexico *lexicalValue, SyntacticalType sType);
SymbolTableNode createVariableWithType(int line, int column, ValorLexico *lexicalValue, SyntacticalType sType);
SymbolTableNode createVectorWithUndefinedType(int line, int column, ValorLexico *lexicalValue, int indexerValue);


#endif