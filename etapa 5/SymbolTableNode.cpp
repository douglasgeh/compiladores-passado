/*
SymboleTableNode

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/

#include "SymbolTableNode.hpp"

void printValue(SymbolTableNode node) {

    printf(" ---- Table value -----");
    printf("Line: %d \n", node.line);
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

SymbolTableNode createNode(int line, ValorLexico* lexicalValue, SyntacticalType sType, Kind kind) {

    int size = getSizeForSyntacticalType(sType);
    
    SymbolTableNode newNode;
    newNode.type = sType;
    newNode.line = line;
    newNode.lexicalValue = lexicalValue;
    newNode.kind = kind;
    newNode.size = size;

    return newNode;
} 

SymbolTableNode createLiteral(int line, ValorLexico *lexicalValue, SyntacticalType sType) {
    return createNode(line, lexicalValue, sType, literalKind);
}

SymbolTableNode createVariableWithUndefinedType(int line, ValorLexico *lexicalValue) {
    return createNode(line, lexicalValue, undefinedSType, variableKind);
}

SymbolTableNode createFunctionWithTypeNoParameters(int line, ValorLexico *lexicalValue, SyntacticalType sType) {
    return createNode(line, lexicalValue, sType, functionKind);
}

SymbolTableNode createVariableWithType(int line, ValorLexico *lexicalValue, SyntacticalType sType) {
    return createNode(line, lexicalValue, sType, variableKind);
}

SymbolTableNode createVectorWithUndefinedType(int line, ValorLexico *lexicalValue, int indexerValue) {
    return createNode(line, lexicalValue, undefinedSType, vectorKind);
}