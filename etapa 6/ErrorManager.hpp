/*
Gerenciamento de erros

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/

#ifndef ERRORMANAGER_HPP
#define ERRORMANAGER_HPP

#include <string>
#include "AST.hpp"
#include "SymbolTableNode.hpp"

using namespace std;

class ErrorManager {
public:
    static void printLine(int line);
    static string stringFromExpression(AST *expressionNode);
    static void printAttributionErrorExpression(string variableKey);
    static void printAttributionError(string variableKey, string attributionKey);
    static void errorDeclared(string variableKey, SymbolTableNode valueFound);
    static void errorElementNotFound(string undeclared);
    static void errorCharToX(string variableKey, AST *attributionNode, SyntacticalType variableType);
    static void errorCharOrStringToXOperation(AST *expressionNode, SyntacticalType type);
    static void errorFunctionVector(string variableKey);
    static void errorFunctionVariable(string variableKey);
    static void errorVectorFunction(string variableKey);
    static void errorVectorVariable(string variableKey);
    static void errorVariableFunction(string variableKey);
    static void errorVariableVector(string variableKey);
    static void errorWrongType(AST *attributionNode, SyntacticalType expectedType, int errorCode);
    static void errorException();
    static void terminate(int errorCode);
};

#endif