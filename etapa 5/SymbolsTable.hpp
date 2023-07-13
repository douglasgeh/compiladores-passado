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
#include "SyntacticalType.hpp"
#include "SymbolTableNode.hpp"

using namespace std;

class SymbolTable {
  private:
    unordered_map<string, SymbolTableNode> symbolTableLiterals;
    unordered_map<string, SymbolTableNode> symbolTableVariables;

    /* deslocamento em relacao ao rbss ou rfp */
    /* o deslocamento aqui é como o "indice" da variavel local */
    /* a primeira declaracao, podendo ser parametro ou nao, possui offset = 0 */
    OffsetAndScope scope;
  public:
    void insertNewItem(string key, SymbolTableNode value);
    bool hasKeyLiterals(string key);
    bool hasKeyVariables(string key);
    SymbolTableNode getValueForKey(string key);
    SymbolTable(OffsetAndScope scope);
    unordered_map<string, SymbolTableNode> getTableVariables();
    unordered_map<string, SymbolTableNode> getTableLiterals();
    void updateTypeAndOffset(string key, SyntacticalType type, int offset);

    OffsetAndScope getScopeAndOffset();
    void updateOffset(string key, int offset);
    void incrementOffset(int increment);
    void setOffset(int offset); 
};

#endif