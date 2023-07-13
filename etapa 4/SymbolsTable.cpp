/*
SymblesTable

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/


#include "SymbolsTable.hpp"
#include <unordered_map>
#include <list>

SymbolTable::SymbolTable() {}

void SymbolTable::insertNewItem(string key, SymbolTableNode value) {
	if (value.kind == literalKind) {
		if (this->hasKeyLiterals(key)) {
			free_valor_lexico(this->symbolTableLiterals[key].lexicalValue);
		}
        this->symbolTableLiterals[key] = value;
	} else {
		this->symbolTableVariables[key] = value;
	}
	
}
bool SymbolTable::hasKeyLiterals(string key) {
	return (this->symbolTableLiterals.find (key) != this->symbolTableLiterals.end());
}
bool SymbolTable::hasKeyVariables(string key) {
	return (this->symbolTableVariables.find (key) != this->symbolTableVariables.end());
}
SymbolTableNode SymbolTable::getValueForKey(string key) {
	return this->symbolTableVariables[key];
}
unordered_map<string, SymbolTableNode> SymbolTable::getTableVariables() {
	return this->symbolTableVariables;
}
unordered_map<string, SymbolTableNode> SymbolTable::getTableLiterals() {
	return this->symbolTableLiterals;
}
void SymbolTable::updateType(string key, SyntacticalType type) {
	this->symbolTableVariables[key].type = type;
	if (this->symbolTableVariables[key].kind == vectorKind) {
		this->symbolTableVariables[key].size *= getSizeForSyntacticalType(type);
	} else {
		this->symbolTableVariables[key].size = getSizeForSyntacticalType(type);
	}
}
// void SymbolTable::updateParameters(list<Parameter> parameters, string functionIdentifier) {
// 	this->symbolTableVariables[functionIdentifier].listOfParameters = parameters;
// }