/*
Gerenciamento de escopos

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/

#ifndef SCOPESMANAGER_HPP
#define SCOPESMANAGER_HPP

extern "C" {
    #include "SyntacticalType.h"
    #include "ValorLexico.h"
    #include "AST.h"
    #include "SymbolTableNode.h"
}

#include "SymbolsTable.hpp"
#include <list>
#include <string>

using namespace std;
    
typedef struct {

    bool found;
    SymbolTableNode valueFound;

} SearchResult;

class ScopesManager {
private:
    // the highest is the "index", the oldest is the scope
    // the global scope always is the last one
    // when a new context is began, a new table is inserted in the front
    // when a context is end, a table is removed from the front
    list<SymbolTable> listOfTables;
    void insertNewItem(string key, SymbolTableNode value);
    list<string> variablesWithPendantTypes;
    string lastDeclaredFunction;
    // TODO LISTA DE PARAMETROS
    //list<Parameter> pendantParameters;

public:
    ScopesManager();
    void beginNewScope();
    
    SearchResult find(string element);
    SearchResult findInScope(string element);
    
    void endLastScope();
    void endAllScopes();
    
    int verifyCoersion(SyntacticalType variableType, SyntacticalType attributionType);
    
    void verifyVectorNode(AST *identificatorNode, AST *indexerSymbolNode, AST *indexerNode);
    void makeAttributionVector(AST *attributionSymbolNode, AST *attributionNode, AST *indexerSymbolNode);
    void makeAttributionVariable(AST *variableNode, AST *attributionSymbolNode, AST *attributionNode);
    void makeInitialization(AST *variableNode, AST *initializationSymbolNode, AST *initializationValueNode);
    void makeFunctionCall(AST *identificatorNode, AST *parametersNode);
    void insertParameterWithType(int line, int column, ValorLexico *lexicalValue, SyntacticalType sType);
    void insertVectorWithPendantType(int line, int column, ValorLexico *lexicalValue, int indexerValue);
    void insertVariableWithUndefinedType(int line, int column, ValorLexico *lexicalValue);
    void insertVariableWithType(int line, int column, ValorLexico *lexicalValue, SyntacticalType sType);
    void insertFunction(int line, int column, AST *identificatorNode, SyntacticalType sType);
    void insertLiteral(int line, int column, ValorLexico *lexicalValue, SyntacticalType sType);
    void updateTypeOfVariablesWithPendantTypes(SyntacticalType type);
    void printItself();
    void updateFunctionWithPendantParameters();
    void makeBinaryOperation(AST *exp1Node, AST *operandNode, AST *exp2Node);
    void makeUnaryOperation(AST *exp1Node, AST *operatorSymbolNode);
    SyntacticalType getInferenceBinaryOperation(SyntacticalType type1, SyntacticalType type2);
    int countNumberOfGivenParameters(AST *functionCallNode);
    void checkStringCharOperation(AST *exp1Node);
    void verifyIdentificatorNode(AST *identificatorNode);

};

#endif