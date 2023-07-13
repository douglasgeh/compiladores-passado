/*
ValorLexico

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ValorLexico.h"

/* funcao usada para debug */
void print_valor_lexico(ValorLexico valorLexico) {

    printf("Numero da linha = %d\n", valorLexico.numeroLinha);
    printf("Tipo do token = %d\n", valorLexico.tipoToken);
    
    TipoTokenLiteral tipoTokenLiteral = valorLexico.valorTipoTokenLiteral.tipo;
    printf("Tipo do token literal = %d\n", tipoTokenLiteral);

    printf("Valor do token literal = ");

    print_valor_literal(valorLexico.valorTipoTokenLiteral);
    printf("\n");
}

/* funcao usada para printar o valor literal */
void print_valor_literal(ValorTipoTokenLiteral valorTipoTokenLiteral) {
    
    TipoTokenLiteral tipoTokenLit = valorTipoTokenLiteral.tipo;
    
    if (tipoTokenLit == tipoSequenciaCharacteres) {
        printf("%s", valorTipoTokenLiteral.valor.charSequenceValue);
    } else if (tipoTokenLit == tipoInteger) {
        printf("%d", valorTipoTokenLiteral.valor.integerValue);
    } else if (tipoTokenLit == tipoFloat) {
        printf("%f", valorTipoTokenLiteral.valor.floatValue);
    } else if (tipoTokenLit == tipoBool) {
        printf("%d", valorTipoTokenLiteral.valor.boolValue);
    } else if (tipoTokenLit == tipoChar) {
        printf("%c", valorTipoTokenLiteral.valor.charValue);
    } 

}

 /* cria um valor lexico a partir de um token literal */
ValorLexico* valor_lexico_de_token_literal(int numeroLinha, char *texto, TipoTokenLiteral tipo) {
    
    ValorTokenLiteral valorLit;

    switch (tipo)
    {
    case tipoSequenciaCharacteres:
        valorLit.charSequenceValue = strdup(remover_primeiro_e_ultimo(texto));
        break;
    case tipoInteger:
        valorLit.integerValue = atoi(texto);
        break;
    case tipoFloat:
        valorLit.floatValue = atof(texto);
        break;
    case tipoBool:
        valorLit.boolValue = (strncmp (texto,"true",4) == 1);
        break;
    case tipoChar:
        strncpy(&valorLit.charValue, remover_primeiro_e_ultimo(texto), 1);
        break;
    default:
        break;
    }
    //LiteralTokenType litType = tipo;
    ValorTipoTokenLiteral valorTipoTokenLiteral = { valorLit, tipo };
    TipoToken tipoToken = literal;
    ValorLexico valorLexico = { numeroLinha, tipoToken, valorTipoTokenLiteral };
    
    ValorLexico *valor_lexico = malloc(sizeof(valorLexico)); 
    *valor_lexico = valorLexico;
    return valor_lexico;
}

 /* cria um valor lexico a partir de um token nao literal
    Exemplos: caracteres especiais, operadores compostos e identificadores
  */
ValorLexico* valor_lexico_de_token_nao_literal(int numerolinha, char *texto, TipoToken tipo) {

    ValorTokenLiteral valorLit;
    valorLit.charSequenceValue = strdup(texto);

    TipoTokenLiteral tipoLit = tipoSequenciaCharacteres;
    ValorTipoTokenLiteral valorTipoTokenLiteral = { valorLit, tipoLit };
    
    TipoToken tipoToken = tipo;
    ValorLexico valorLexico = { numerolinha, tipoToken, valorTipoTokenLiteral };
    
    ValorLexico *valor_lexico = malloc(sizeof(valorLexico)); 
    *valor_lexico = valorLexico;
    return valor_lexico;

}

 /* remove valor lexico. Caso tenha uma string armazenada, remove ela também. */
void free_valor_lexico(ValorLexico *valorLexico) {

    if (valorLexico == NULL) { return; }

    if (valorLexico->valorTipoTokenLiteral.tipo == tipoSequenciaCharacteres) {
        free(valorLexico->valorTipoTokenLiteral.valor.charSequenceValue);
    }

    free(valorLexico);

}

 /* remove primeiro e ultimo caracter */
 char *remover_primeiro_e_ultimo(char *texto) {
    char *mystr = texto;
    mystr++; /* removing first item */
    mystr[strlen(mystr) - 1] = '\0';  /* removing last item */
    return mystr;
}