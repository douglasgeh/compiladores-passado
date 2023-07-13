/*
ValorLexico

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/

#ifndef ValorLexico_H
#define ValorLexico_H

typedef union {
    char * charSequenceValue;
    int integerValue;
    float floatValue;
    int boolValue;
    char charValue;
} ValorTokenLiteral;

typedef enum { 
    tipoSequenciaCharacteres = 0,
    tipoInteger = 1,
    tipoFloat = 2,
    tipoBool = 3,
    tipoChar = 4
} TipoTokenLiteral;

typedef enum { 
    characterEspecial = 0,
    operadorComposto = 1,
    identificador = 2,
    literal = 3,
} TipoToken;

typedef struct {
    ValorTokenLiteral valor;
    TipoTokenLiteral tipo;
} ValorTipoTokenLiteral;

typedef struct ValorLexico {
    int numeroLinha; // da spec: 2.1 (a)
    TipoToken tipoToken; // da spec: 2.1 (b)
    ValorTipoTokenLiteral valorTipoTokenLiteral; // da spec: 2.1 (c)
} ValorLexico;

void print_valor_lexico(ValorLexico valorLexico);
void print_valor_literal(ValorTipoTokenLiteral valorTipoTokenLiteral);
ValorLexico* valor_lexico_de_token_literal(int numeroLinha, char *texto, TipoTokenLiteral tipo);
ValorLexico* valor_lexico_de_token_nao_literal(int numerolinha, char *texto, TipoToken tipo);
char *remover_primeiro_e_ultimo(char *texto);
void free_valor_lexico(ValorLexico *valorLexico);

#endif