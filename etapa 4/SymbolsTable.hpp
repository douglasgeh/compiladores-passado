/*
SymblesTable

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/


#ifndef SYMBOLSTABLE_HPP
#define SYMBOLSTABLE_HPP

#include <unordered_map>
#include <string>

extern "C" {
    #include "SyntacticalType.h"
    #include "SymbolTableNode.h"
}

using namespace std;

class SymbolTable {
    private:
    unordered_map<string, SymbolTableNode> symbolTableLiterals;
    unordered_map<string, SymbolTableNode> symbolTableVariables;
    public:
    void insertNewItem(string key, SymbolTableNode value);
    bool hasKeyLiterals(string key);
    bool hasKeyVariables(string key);
    SymbolTableNode getValueForKey(string key);
    SymbolTable();
    unordered_map<string, SymbolTableNode> getTableVariables();
    unordered_map<string, SymbolTableNode> getTableLiterals();
    void updateType(string key, SyntacticalType type);
   // Todo funcao para atualizar parametros
};

#endif