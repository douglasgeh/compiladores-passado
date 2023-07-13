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

SymbolTable::SymbolTable(OffsetAndScope scope) { 
	this->scope = scope;
}

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
void SymbolTable::updateTypeAndOffset(string key, SyntacticalType type, int offset) {
	this->symbolTableVariables[key].type = type;
	this->symbolTableVariables[key].variableScope.offset = offset;

	if (this->symbolTableVariables[key].kind == vectorKind) {
		this->symbolTableVariables[key].size *= getSizeForSyntacticalType(type);
	} else {
		this->symbolTableVariables[key].size = getSizeForSyntacticalType(type);
	}
}

OffsetAndScope SymbolTable::getScopeAndOffset()
{
	return this->scope;
}

void SymbolTable::updateOffset(string key, int offset)
{
	this->symbolTableVariables[key].variableScope.offset = offset;
}

void SymbolTable::incrementOffset(int increment)
{
	this->scope.offset += increment;
}

void SymbolTable::setOffset(int offset)
{
	this->scope.offset = offset;
}
