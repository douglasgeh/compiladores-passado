

#include "SymbolTableNode.h"

/*
SymboleTableNode

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/


void printValue(SymbolTableNode node) {

    printf(" ---- Table value -----");
    printf("Line: %d \n", node.line);
    printf( "Column: %d\n",node.column);
    printf("Kind: \n");
    printKind(node.kind);
    printf("\n");
    printf("Size: %d\n", node.size);
    printf("Type: ");
    printSyntacticalType(node.type);
    printf("\n");
    printf("Lexical Value: ");
    print_valor_lexico(*(node.lexicalValue));
    printf("\n");
}

void printKind(Kind kind) {
     switch (kind)
    {
    case literalKind:
        printf("Literal") ;
        break;
    case variableKind:
        printf("Variable");
        break;
    case functionKind:
        printf("Function");
        break;
    case vectorKind:
        printf("Vector");
        break;
    default:
        printf("No Kind");
        break;
    }
}

void printSyntacticalType(SyntacticalType type) {
    switch (type)
    {
    case charSType:
        printf("char");
        break;
    case boolSType:
        printf("bool");
        break;
    case floatSType:
        printf("float");
        break;
    case intSType:
        printf("integer");
        break;
    default:
        printf("undefined");
        break;
    }
}

SymbolTableNode createNode(int line, int column, ValorLexico* lexicalValue, SyntacticalType sType, Kind kind) {

    int size = getSizeForSyntacticalType(sType);
    
    SymbolTableNode newNode;
    newNode.type = sType;
    newNode.line = line;
    newNode.column = column;
    newNode.lexicalValue = lexicalValue;
    newNode.kind = kind;
    newNode.size = size;

    return newNode;
} 

SymbolTableNode createLiteral(int line, int column, ValorLexico *lexicalValue, SyntacticalType sType) {
    return createNode(line, column, lexicalValue, sType, literalKind);
}

SymbolTableNode createVariableWithUndefinedType(int line, int column, ValorLexico *lexicalValue) {
    return createNode(line, column, lexicalValue, undefinedSType, variableKind);
}

SymbolTableNode createFunctionWithTypeNoParameters(int line, int column, ValorLexico *lexicalValue, SyntacticalType sType) {
    return createNode(line, column, lexicalValue, sType, functionKind);
}

SymbolTableNode createVariableWithType(int line, int column, ValorLexico *lexicalValue, SyntacticalType sType) {
    return createNode(line, column, lexicalValue, sType, variableKind);
}

SymbolTableNode createVectorWithUndefinedType(int line, int column, ValorLexico *lexicalValue, int indexerValue) {
    return createNode(line, column, lexicalValue, undefinedSType, vectorKind);
}