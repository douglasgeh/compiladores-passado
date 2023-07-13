/*
Parser da linguagem

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/

#include "Utils.hpp"
#include <string>

extern "C" {
    #include "ValorLexico.h"
}

using namespace std;

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