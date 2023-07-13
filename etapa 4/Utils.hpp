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

extern "C" {
    #include "ValorLexico.h"
}

using namespace std;

string stringFromLiteralValue(ValorTipoTokenLiteral literalTokenValueAndType);

#endif