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
#include "SyntacticalType.hpp"
#include "ValorLexico.hpp"
#include "Code.hpp"

typedef enum {
    literalKind = 1,
    variableKind,
    functionKind,
    vectorKind,
} Kind;

typedef struct {
    int line;
    Kind kind;
    SyntacticalType type;
    int size;
    ValorLexico *lexicalValue;

    OffsetAndScope variableScope; //deslocamento em relação a rbss ou rfp
    int functionLabel; //label da função. main é sempre L0. 
    int sizeOfParameters; //o total de espaço ocupado por todos os parametros da funcao
    //first: primeiro registrador usado pela funcao
    //second: ultimo 
    pair<int, int> registersUsedFunction;
} SymbolTableNode;

void printValue(SymbolTableNode symbolTableValue);
void printKind(Kind kind);
void printSyntacticalType(SyntacticalType type);

SymbolTableNode createNode(int line, ValorLexico* lexicalValue, SyntacticalType sType, Kind kind);
SymbolTableNode createLiteral(int line, ValorLexico *lexicalValue, SyntacticalType sType);
SymbolTableNode createVariableWithUndefinedType(int line, ValorLexico *lexicalValue);
SymbolTableNode createFunctionWithTypeNoParameters(int line, ValorLexico *lexicalValue, SyntacticalType sType);
SymbolTableNode createVariableWithType(int line, ValorLexico *lexicalValue, SyntacticalType sType);
SymbolTableNode createVectorWithUndefinedType(int line, ValorLexico *lexicalValue, int indexerValue);


#endif