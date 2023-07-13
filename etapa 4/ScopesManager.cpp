/*
Gerenciamento de escopos

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/


#include "ScopesManager.hpp"
#include "SymbolsTable.hpp"
#include "ErrorManager.hpp"
#include <string>
#include <list>
#include <iostream>
#include "errors.h"
#include "Utils.hpp"

extern "C" {
    #include "SymbolTableNode.h"
}

using namespace std;

extern "C" {
    #include "SyntacticalType.h"
}

ScopesManager::ScopesManager() {
    // começa o escopo global
    this->beginNewScope(); 
}

void ScopesManager::beginNewScope() {

    SymbolTable newSymbolTable;
    this->listOfTables.push_front(newSymbolTable);
    
}
SearchResult ScopesManager::find(string element) {

    list<SymbolTable>::iterator it;
    for (it = this->listOfTables.begin(); it != this->listOfTables.end(); ++it) {
        if(it->hasKeyVariables(element)) {
            
            SearchResult returnValue = { .found= true, .valueFound= it->getValueForKey(element) };
            return returnValue;
        }
    }
    
    SymbolTableNode emptySymbolTableNode;
    SearchResult returnValue = { .found= false, .valueFound= emptySymbolTableNode };
    return returnValue;
}

SearchResult ScopesManager::findInScope(string element) {

    if (this->listOfTables.empty()) { return {.found= false }; }
    SymbolTable currentScopeTable = this->listOfTables.front();
    if(currentScopeTable.hasKeyVariables(element)) {
            
        SearchResult returnValue = { .found= true, .valueFound= currentScopeTable.getValueForKey(element) };
        return returnValue;
    }
    return { .found= false };
}

void ScopesManager::endLastScope() {

    if (this->listOfTables.empty()) { return; }
    SymbolTable lastScope = this->listOfTables.front();
    /* frees identifiers's table */
    for (pair<string, SymbolTableNode> kv : lastScope.getTableVariables()) {
        
        free_valor_lexico(kv.second.lexicalValue);
    }
    /* frees literals's table */
    for (pair<string, SymbolTableNode> kv : lastScope.getTableLiterals()) {
        
        free_valor_lexico(kv.second.lexicalValue);
    }
    this->listOfTables.pop_front();
}

void ScopesManager::endAllScopes() {

    if (this->listOfTables.empty()) { return; }
    list<SymbolTable>::iterator it;
    for (it = this->listOfTables.begin(); it != this->listOfTables.end(); ++it) {
        /* frees identifiers's table */
       for (pair<string, SymbolTableNode> kv : it->getTableVariables()) {
            free_valor_lexico(kv.second.lexicalValue);
        }
        /* frees literals's table */
        for (pair<string, SymbolTableNode> kv : it->getTableLiterals()) {
            free_valor_lexico(kv.second.lexicalValue);
        }
    }
}


void ScopesManager::insertNewItem(string key, SymbolTableNode value) {
    
    this->listOfTables.front().insertNewItem(key, value);
}

void ScopesManager::verifyVectorNode(AST *identificatorNode, AST *indexerSymbolNode, AST *indexerNode) {
    
    ValorLexico *identificatorLV = identificatorNode->value;
    string variableKey = string(identificatorLV->valorTipoTokenLiteral.valor.charSequenceValue);
    SearchResult resultVariable = this->find(variableKey);
    
    //Verifies ERR UNDECLARED
    if (!resultVariable.found) {
        ErrorManager::printLine(identificatorNode->value->numeroLinha);
        ErrorManager::errorElementNotFound(variableKey);
        return;
    }
    // Verifies ERR VARIABLE
    if (resultVariable.valueFound.kind == variableKind) {
        ErrorManager::printLine(identificatorNode->value->numeroLinha);
        ErrorManager::errorVariableVector(variableKey);
        return;
    }
    // Verifies ERR FUNCTION
    if (resultVariable.valueFound.kind == functionKind) {
        ErrorManager::printLine(identificatorNode->value->numeroLinha);
        ErrorManager::errorFunctionVector(variableKey);
        return;
    }
    // Verifies ERR WRONG TYPE no indexador
    int coersionResult = this->verifyCoersion(indexerNode->sType, intSType);
    if (coersionResult != SUCCESS) {
        ErrorManager::printLine(identificatorNode->value->numeroLinha);
        ErrorManager::errorWrongType(indexerNode, intSType, coersionResult);
        return;
    }

    identificatorNode->sType = resultVariable.valueFound.type;
    indexerSymbolNode->sType = resultVariable.valueFound.type;

}

void ScopesManager::verifyIdentificatorNode(AST *identificatorNode) {
    ValorLexico *identificatorLV = identificatorNode->value;
    string variableKey = string(identificatorLV->valorTipoTokenLiteral.valor.charSequenceValue);
    SearchResult resultVariable = this->find(variableKey);

    //Verifies ERR UNDECLARED
    if (!resultVariable.found) {
        ErrorManager::printLine(identificatorNode->value->numeroLinha);
        ErrorManager::errorElementNotFound(variableKey);
    }
    // Verifies ERR VECTOR
    if (resultVariable.valueFound.kind == vectorKind) {
        ErrorManager::printLine(identificatorNode->value->numeroLinha);
        ErrorManager::errorVectorVariable(variableKey);
    }
    // Verifies ERR FUNCTION
    if (resultVariable.valueFound.kind == functionKind) {
         ErrorManager::printLine(identificatorNode->value->numeroLinha);
        ErrorManager::errorFunctionVariable(variableKey);
    }

    identificatorNode->sType = resultVariable.valueFound.type;
    
}

void ScopesManager::makeInitialization(AST *variableNode, AST *initializationSymbolNode, AST *initializationValueNode) {

    string variableKey = string(variableNode->value->valorTipoTokenLiteral.valor.charSequenceValue);
    string attributionKey = stringFromLiteralValue(initializationSymbolNode->value->valorTipoTokenLiteral);


    //Verifies ERR WRONG TYPE
    int coersionResult = this->verifyCoersion(variableNode->sType, initializationValueNode->sType);
    if (coersionResult != SUCCESS) {
        ErrorManager::printLine(initializationValueNode->value->numeroLinha);
        ErrorManager::printAttributionError(variableKey, attributionKey);
        ErrorManager::errorWrongType(initializationValueNode, variableNode->sType, coersionResult);
    }

    initializationSymbolNode->sType = variableNode->sType;
}

void ScopesManager::makeAttributionVariable(AST *variableNode, AST *attributionSymbolNode, AST *attributionNode) {

    string variableKey = stringFromLiteralValue(variableNode->value->valorTipoTokenLiteral);
    string attKey = stringFromLiteralValue(attributionNode->value->valorTipoTokenLiteral);

    int coersionResult = this->verifyCoersion(variableNode->sType, attributionNode->sType);
    if (coersionResult != SUCCESS) {
        ErrorManager::printLine(attributionSymbolNode->value->numeroLinha);
        ErrorManager::errorWrongType(attributionNode, variableNode->sType, coersionResult);
    }

    attributionSymbolNode->sType = variableNode->sType;

}

void ScopesManager::makeAttributionVector(AST *attributionSymbolNode, AST *attributionNode, 
    AST *indexerSymbolNode) {

    string variableKey = stringFromLiteralValue(indexerSymbolNode->child->value->valorTipoTokenLiteral);

    //Verifies ERR_WRONG_TYPE
    int coersionResult = this->verifyCoersion(indexerSymbolNode->sType, attributionNode->sType);
    if (coersionResult != SUCCESS) {
        ErrorManager::printLine(attributionNode->value->numeroLinha);
        ErrorManager::errorWrongType(attributionNode, indexerSymbolNode->sType, coersionResult);
    }

    attributionSymbolNode->sType = indexerSymbolNode->sType;

}


void ScopesManager::makeFunctionCall(AST *identificatorNode, AST *parametersNode) {

    string variableKey = string(identificatorNode->value->valorTipoTokenLiteral.valor.charSequenceValue);
    SearchResult resultVariable = this->find(variableKey);

    //Verifies ERR_UNDECLARED
    if (!resultVariable.found) {
        ErrorManager::printLine(identificatorNode->value->numeroLinha);
        ErrorManager::errorElementNotFound(variableKey);
    }
    //Verifies ERR_VECTOR
    if (resultVariable.valueFound.kind == vectorKind) {
        ErrorManager::printLine(identificatorNode->value->numeroLinha);
        ErrorManager::errorVectorFunction(variableKey);
    }
    //Verifies ERR_VARIABLE
    if (resultVariable.valueFound.kind == variableKind) {
        ErrorManager::printLine(identificatorNode->value->numeroLinha);
        ErrorManager::errorVariableFunction(variableKey);
    }
    
}

int ScopesManager::countNumberOfGivenParameters(AST *functionCallNode) {

    int counter = 0;
    AST *pointer = functionCallNode;
    while (pointer != NULL) {
        counter += 1;
        pointer = pointer->child;
    }
    return counter;

}

int ScopesManager::verifyCoersion(SyntacticalType variableType, SyntacticalType attributionType) {

    if (attributionType == variableType) { return SUCCESS; }

    if (attributionType == intSType && (variableType == floatSType || 
    variableType == boolSType)) {
        return SUCCESS;
    } 
    if (attributionType == floatSType && (variableType == intSType || 
    variableType == boolSType)) {
        return SUCCESS;
    }
    if (attributionType == boolSType && (variableType == floatSType || 
    variableType == intSType)) {
        return SUCCESS;
    }

    if(variableType == intSType && (attributionType == charSType)) {
        return ERR_CHAR_TO_INT;
    }
    
    if(variableType == floatSType && (attributionType == charSType)) {
        return ERR_CHAR_TO_FLOAT;
    }

    if(variableType == boolSType && (attributionType == charSType)) {
        return ERR_CHAR_TO_BOOL;
    }

    if(variableType == charSType && attributionType != charSType) {
        return ERR_X_TO_CHAR;
    }

    return GENERIC_ERROR;
}

void ScopesManager::insertVectorWithPendantType(int line, int column, ValorLexico *lexicalValue, int indexerValue) {

    string key = stringFromLiteralValue(lexicalValue->valorTipoTokenLiteral);
    SearchResult searchResult = this->findInScope(key);

    //Verifies ERR DECLARED
    if (searchResult.found) { 
        ErrorManager::printLine(line);
        ErrorManager::errorDeclared(key, searchResult.valueFound);
    }

    this->variablesWithPendantTypes.push_back(key);
    SymbolTableNode newValue = createVectorWithUndefinedType(line, column, lexicalValue, indexerValue);
    this->insertNewItem(key, newValue);

}

void ScopesManager::insertLiteral(int line, int column, ValorLexico *lexicalValue, SyntacticalType sType) {
    
    string key = stringFromLiteralValue(lexicalValue->valorTipoTokenLiteral);
    SymbolTableNode newValue = createLiteral(line, column, lexicalValue, sType);
    this->insertNewItem(key, newValue);
}

void ScopesManager::insertVariableWithUndefinedType(int line, int column, ValorLexico *lexicalValue) {

    string key = stringFromLiteralValue(lexicalValue->valorTipoTokenLiteral);
    SearchResult searchResult = this->findInScope(key);

    //Verifies ERR DECLARED
    if (searchResult.found) { 
        ErrorManager::printLine(line);
        ErrorManager::errorDeclared(key, searchResult.valueFound);
    }
    
    SymbolTableNode newValue = createVariableWithUndefinedType(line, column, lexicalValue);
    this->variablesWithPendantTypes.push_back(key);
    this->insertNewItem(key, newValue);
}

void ScopesManager::insertFunction(int line, int column, AST *identificatorNode, SyntacticalType sType) {
    
    string key = string(identificatorNode->value->valorTipoTokenLiteral.valor.charSequenceValue);
    SearchResult searchResult = this->findInScope(key);

    //Verifies ERR DECLARED
    if (searchResult.found) { 
        ErrorManager::printLine(identificatorNode->value->numeroLinha);
        ErrorManager::errorDeclared(key, searchResult.valueFound);
    }

    SymbolTableNode newValue = createFunctionWithTypeNoParameters(line, column, identificatorNode->value, sType);
    this->insertNewItem(key, newValue);
    identificatorNode->sType = sType;
    this->lastDeclaredFunction = key;

}

void ScopesManager::updateFunctionWithPendantParameters() {

   // this->listOfTables.back().updateParameters(this->pendantParameters, this->lastDeclaredFunction);
   // this->pendantParameters.clear();
}

void ScopesManager::insertParameterWithType(int line, int column, ValorLexico *lexicalValue, SyntacticalType sType) {

    string key = stringFromLiteralValue(lexicalValue->valorTipoTokenLiteral);
    SearchResult searchResult = this->findInScope(key);
    
    //Verifies ERR DECLARED
    if (searchResult.found) { 
        ErrorManager::printLine(line);
        ErrorManager::errorDeclared(key, searchResult.valueFound);
    }

    SymbolTableNode newValue = createVariableWithType(line, column, lexicalValue, sType);
    this->insertNewItem(key, newValue);
}

void ScopesManager::insertVariableWithType(int line, int column, ValorLexico *lexicalValue, SyntacticalType sType) {

    string key = string(lexicalValue->valorTipoTokenLiteral.valor.charSequenceValue);
    SearchResult searchResult = this->findInScope(key);

    //Verifies ERR DECLARED
    if (searchResult.found) { 
        ErrorManager::printLine(line);
        ErrorManager::errorDeclared(key, searchResult.valueFound);
    }

    SymbolTableNode newValue = createVariableWithType(line, column, lexicalValue, sType);
    this->insertNewItem(key, newValue);
}

void ScopesManager::updateTypeOfVariablesWithPendantTypes(SyntacticalType type) {
    
    while (!this->variablesWithPendantTypes.empty()) {
        string varKey = this->variablesWithPendantTypes.front();
        this->listOfTables.front().updateType(varKey, type);
        this->variablesWithPendantTypes.pop_front();
    }

}

SyntacticalType ScopesManager::getInferenceBinaryOperation(SyntacticalType type1, SyntacticalType type2) {

    if (type1 == undefinedSType || type2 == undefinedSType || type1 == charSType || type2 == charSType) { return undefinedSType; } 
    else if (type1 == type2) { return type1; }
    else if (type1 == floatSType || type2 == floatSType) { return floatSType; }
    return intSType;

}

void ScopesManager::checkStringCharOperation(AST *exp1Node) {

    SyntacticalType type1 = exp1Node->sType;

    //Verifies ERR_STRING_TO_X and CHAR TO X
    if (type1 == charSType) { 
        ErrorManager::printLine(exp1Node->value->numeroLinha);
        ErrorManager::errorCharOrStringToXOperation(exp1Node, type1);
    }
}


void ScopesManager::makeBinaryOperation(AST *exp1Node, AST *operandNode, AST *exp2Node) {

    SyntacticalType type1 = exp1Node->sType;
    SyntacticalType type2 = exp2Node->sType;
    SyntacticalType finalType = this->getInferenceBinaryOperation(type1, type2);

    this->checkStringCharOperation(exp1Node);
    this->checkStringCharOperation(exp2Node);

    if(this->getInferenceBinaryOperation(type1, type2) == undefinedSType) {
        ErrorManager::errorException();
    }

    operandNode->sType = finalType; 
}

void ScopesManager::makeUnaryOperation(AST *exp1Node, AST *operatorSymbolNode) {

    SyntacticalType type1 = exp1Node->sType;
    string key = stringFromLiteralValue(exp1Node->value->valorTipoTokenLiteral);
    
    this->checkStringCharOperation(exp1Node);

    operatorSymbolNode->sType = type1;
}

void ScopesManager::printItself() {

    list<SymbolTable>::iterator it;
    cout << "Printing total of " << this->listOfTables.size() << "tables" << endl;
    for (it = this->listOfTables.begin(); it != this->listOfTables.end(); ++it) {
        cout << "New Table:" << endl;
        for (pair<string, SymbolTableNode> kv : it->getTableVariables()) {
            cout << endl;
            cout << "Key: " << kv.first << " Value: " << endl;
            printValue(kv.second);
        }
        for (pair<string, SymbolTableNode> kv : it->getTableLiterals()) {
            cout << endl;
            cout << "Key: " << kv.first << " Value: " << endl;
            printValue(kv.second);
        }
    }
}