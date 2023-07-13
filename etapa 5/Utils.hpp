/*
Funçōes utilitarias

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/


#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include "ValorLexico.hpp"


using namespace std;

int integerFromLiteralValue(ValorTipoTokenLiteral literalTokenValueAndType);
string stringFromLiteralValue(ValorTipoTokenLiteral literalTokenValueAndType);

#endif