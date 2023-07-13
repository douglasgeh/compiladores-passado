/*
Parser da linguagem

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/

#include "Utils.hpp"
#include "ValorLexico.hpp"
#include <string>

using namespace std;

int integerFromLiteralValue(ValorTipoTokenLiteral literalTokenValueAndType) {
    
    TipoTokenLiteral litTokenType = literalTokenValueAndType.tipo;
    
    if (litTokenType == tipoSequenciaCharacteres) {
        return 0;
    } else if (litTokenType == tipoInteger) {
        return literalTokenValueAndType.valor.integerValue;
    } else if (litTokenType == tipoFloat) {
        return 0;
    } else if (litTokenType == tipoBool) {
        return literalTokenValueAndType.valor.boolValue;
    } else if (litTokenType == tipoChar) {
        return (int)(literalTokenValueAndType.valor.charValue); 
    } 
    return -1;
}

string stringFromLiteralValue(ValorTipoTokenLiteral literalTokenValueAndType) {
    
    TipoTokenLiteral litTokenType = literalTokenValueAndType.tipo;
    
    if (litTokenType == tipoSequenciaCharacteres) {
        return string(literalTokenValueAndType.valor.charSequenceValue);
    } else if (litTokenType == tipoInteger) {
        return to_string(literalTokenValueAndType.valor.integerValue);
    } else if (litTokenType == tipoFloat) {
        return to_string(literalTokenValueAndType.valor.floatValue);
    } else if (litTokenType == tipoBool) {
        return to_string(literalTokenValueAndType.valor.boolValue);
    } else if (litTokenType == tipoChar) {
        string convertedString(1, literalTokenValueAndType.valor.charValue);
        return convertedString;
    } 
    return "";
}