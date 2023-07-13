/*
Função principal
*/
#include <stdio.h>
#include "CodeGenerator.hpp"
#include "ScopesManager.hpp"
#include "CodePrinter.hpp"

void *arvore = NULL;
ScopesManager scopesManager;
CodeGenerator codeGenerator;

extern "C" {
    int yyparse(void);
    int yylex_destroy(void);
}

int main (int argc, char **argv)
{
    scopesManager.beginNewScope();
    int ret = yyparse();
    CodePrinter cp;
    cp.printTree (arvore);
    arvore = NULL;
    yylex_destroy();
    return ret;
}