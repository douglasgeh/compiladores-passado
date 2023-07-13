/*
Gerenciamento de erros

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/


#include "ErrorManager.hpp"
#include "Utils.hpp"

#include <string>
#include <iostream>
#include <cctype>

extern "C" {
    #include "errors.h"
    #include "AST.h"
    #include "ValorLexico.h"
    #include "SymbolTableNode.h"
}

using namespace std;

void ErrorManager::printLine(int line) {
    cout << "ERRO linha: " << line << endl;
}

void ErrorManager::printAttributionErrorExpression(string variableKey) {
    cout << "Não foi possível fazer atribuição de expressão para " << variableKey << endl;
}

void ErrorManager::printAttributionError(string variableKey, string attributionKey) {
    cout << "Não foi possível fazer atribuição de " << attributionKey << " para " << variableKey << endl;
}

// void ErrorManager::errorStringVector(string variableKey) {
//     cout << "Vetor " << variableKey << " não pode ser declarado." << endl;
//     cout << "Motivo: Não é permitido declaração de vetores de string." << endl;
//     ErrorManager::terminate(ERR_STRING_VECTOR);
// }

void ErrorManager::errorDeclared(string variableKey, SymbolTableNode valueFound) {
    cout << "Não foi possível declarar " << variableKey << endl;
    cout << "Nome já foi declarado na linha " << valueFound.line << endl;
    ErrorManager::terminate(ERR_DECLARED);
}

// void ErrorManager::printElementsNotFoundAttribution(string variableKey, string attributionKey, int line) {
//     ErrorManager::printAttributionError(variableKey, attributionKey, line);
//     cout << "Motivo: Nenhum dos elementos foram declarados.";
// }

void ErrorManager::errorElementNotFound(string undeclared) {
    cout << undeclared  << " não foi declarado " << endl;
    ErrorManager::terminate(ERR_UNDECLARED);
}

// void ErrorManager::errorStringToX(string variableKey, string attributionKey,
//  SyntacticalType variableType) {
//     cout << attributionKey  << " é do tipo string, que não pode ser convertido em nenhum tipo. No caso, " << variableKey << " é um ";
//     printSyntacticalType(variableType);
//     cout << endl;
//     ErrorManager::terminate(ERR_STRING_TO_X);
    
// }

string ErrorManager::stringFromExpression(AST *expressionNode) {
   
    if (expressionNode->value->tipoToken == literal || expressionNode->value->tipoToken == identificador) {
        return stringFromLiteralValue(expressionNode->value->valorTipoTokenLiteral);
    } else {
       return "Expressão";
    }
}

void ErrorManager::errorCharToX(string variableKey, AST *attributionNode, SyntacticalType variableType) {

    string element = ErrorManager::stringFromExpression(attributionNode);
    cout << element  << " é do tipo char, que não pode ser convertido em nenhum tipo. No caso, " << variableKey << " é um ";
    printSyntacticalType(variableType);
    cout << endl;
    ErrorManager::terminate(ERR_X_TO_CHAR);
}

void ErrorManager::errorCharOrStringToXOperation(AST *expressionNode, SyntacticalType type) {

    string element = ErrorManager::stringFromExpression(expressionNode);
    cout << element  << " é do tipo ";
    printSyntacticalType(type);
    cout << ", que não pode ser operando de expressões. " << endl;
    
    if (type == charSType) {
        ErrorManager::terminate(ERR_X_TO_CHAR);
    } 
    
}

void ErrorManager::errorFunctionVector(string variableKey) {
    cout << variableKey  << " é uma função e está sendo usada como vetor" << endl;
    ErrorManager::terminate(ERR_FUNCTION);
}

void ErrorManager::errorFunctionVariable(string variableKey) {
    cout << variableKey  << " é uma função e está sendo usada como variável" << endl;
    ErrorManager::terminate(ERR_FUNCTION);
}

void ErrorManager::errorVectorFunction(string variableKey) {
    cout << variableKey  << " é um vetor e está sendo usada como função" << endl;
    ErrorManager::terminate(ERR_ARRAY);
}

void ErrorManager::errorVectorVariable(string variableKey) {
    cout << variableKey  << " é um vetor e está sendo usada como variável" << endl;
    ErrorManager::terminate(ERR_ARRAY);
}

void ErrorManager::errorVariableFunction(string variableKey) {
    cout << variableKey  << " é uma variável e está sendo usada como função" << endl;
    ErrorManager::terminate(ERR_VARIABLE);
}

void ErrorManager::errorVariableVector(string variableKey) {
    cout << variableKey  << " é uma variável e está sendo usada como vetor" << endl;
    ErrorManager::terminate(ERR_VARIABLE);
}

void ErrorManager::errorWrongType(AST *attributionNode, SyntacticalType expectedType, int errorCode) {

    string element = ErrorManager::stringFromExpression(attributionNode);
    cout << element; 
    cout << " possui tipo = ";
    printSyntacticalType(attributionNode->sType);
    cout << " e não pode ser convertido para o tipo esperado = ";
    printSyntacticalType(expectedType);
    cout << endl;

    ErrorManager::terminate(errorCode);
}

void ErrorManager::errorException() {
    cout << "Ocorreu algo imprevisto no código" << endl;
    ErrorManager::terminate(GENERIC_ERROR);
}

void ErrorManager::terminate(int errorCode) {
    cout << "Error code:" << errorCode << endl;
    exit(errorCode);
}