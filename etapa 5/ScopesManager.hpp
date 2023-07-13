/*
Gerenciamento de escopos

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/

#ifndef SCOPESMANAGER_HPP
#define SCOPESMANAGER_HPP

#include "SyntacticalType.hpp"
#include "ValorLexico.hpp"
#include "SymbolTableNode.hpp"
#include "AST.hpp"
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
    SyntacticalType lastReadType;
    int lastFunctionOffset;
    list<SyntacticalType> pendantParameters;
    int generateLabelForFunction(string functionName);
    int geSizeOfParametersLastDeclaredFunction();

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
    void insertParameterWithType(int line, ValorLexico *lexicalValue, SyntacticalType sType);
    void insertVectorWithPendantType(int line, ValorLexico *lexicalValue, int indexerValue);
    void insertVariableWithUndefinedType(int line, ValorLexico *lexicalValue);
    void insertVariableWithType(int line, ValorLexico *lexicalValue, SyntacticalType sType);
    void insertFunction(int line, AST *identificatorNode, SyntacticalType sType);
    void insertLiteral(int line, ValorLexico *lexicalValue, SyntacticalType sType);
    void updateTypeOfVariablesWithPendantTypes(SyntacticalType type);
    void printItself();
    void updateFunctionWithPendantParameters();
    void makeBinaryOperation(AST *exp1Node, AST *operandNode, AST *exp2Node);
    void makeUnaryOperation(AST *exp1Node, AST *operatorSymbolNode);
    SyntacticalType getInferenceBinaryOperation(SyntacticalType type1, SyntacticalType type2);
    int countNumberOfGivenParameters(AST *functionCallNode);
    void checkStringCharOperation(AST *exp1Node);
    void verifyIdentificatorNode(AST *identificatorNode);
    void saveLastReadType(SyntacticalType sType);
    SyntacticalType getLastReadType();


    OffsetAndScope getOffsetAndScopeNewScope();
    int getLastFunctionOffset();
    OffsetAndScope getUpdatedOffsetAndScopeForVariable(AST *variableNode);
    int getReturnValueOffsetForFunction(string functionName);
    int getReturnValueOffsetForLastDeclaredFunction();
    int getLabelForFunction(AST *functionNode);
    int getLabelForFunction(string functionName);
    int getLabelForLastDeclaredFunction();
    int getQuantityOfParametersForFunction(AST *functionNode);
    int getQuantityOfParametersForFunction(string functionName);
    int getSizeOfParametersForFunction(string functionName);
    int getSizeOfParametersForFunction(AST *functionNode);
};

#endif