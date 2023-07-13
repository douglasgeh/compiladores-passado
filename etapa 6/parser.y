/*
Parser da linguagem

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/

%{
    #include <stdio.h>
    #include "SymbolsTable.hpp"
    #include "ScopesManager.hpp"
    #include "AST.hpp"
    #include "CodeGenerator.hpp"
    #include "SyntacticalType.hpp"
    #include "ValorLexico.hpp"
    #include "SymbolTableNode.hpp"
    
    extern "C" {
        int yylex(void);  
        int yyparse(void);
    }
    void yyerror (char const *s);
    
    extern int get_line_number();
    extern void* arvore;
    extern ScopesManager scopesManager;
    extern CodeGenerator codeGenerator;
%}

%define parse.error verbose
//%define parse.trace

%union {
	struct ValorLexico *valor_lexico;
	struct AST *node;
    int syntacticalType;
}

%token TK_PR_INT
%token TK_PR_FLOAT
%token TK_PR_BOOL
%token TK_PR_CHAR
%token TK_PR_IF
%token TK_PR_THEN
%token TK_PR_ELSE
%token TK_PR_WHILE
%token TK_PR_INPUT
%token TK_PR_OUTPUT
%token TK_PR_RETURN
%token TK_PR_FOR
%token TK_ERRO
%token<valor_lexico> TK_OC_LE
%token<valor_lexico> TK_OC_GE
%token<valor_lexico> TK_OC_EQ
%token<valor_lexico> TK_OC_NE
%token<valor_lexico> TK_OC_AND
%token<valor_lexico> TK_OC_OR
%token<valor_lexico> TK_LIT_INT
%token<valor_lexico> TK_LIT_FLOAT
%token<valor_lexico> TK_LIT_FALSE
%token<valor_lexico> TK_LIT_TRUE
%token<valor_lexico> TK_LIT_CHAR
%token<valor_lexico> TK_IDENTIFICADOR
%token<valor_lexico> '=' '+' '-' '*' '/' '%' '<' '>' '!' '?'
%token ',' ';' ':' '(' ')' '[' ']' '{' '}'

%start programa

// ---- Tipos -----

%type<node> programa
%type<node> lista_de_elementos
%type<node> lista_de_elementos_tail
%type<node> funcao
%type<node> funcao_header
%type<node> funcao_tail
%type<node> variaveis_globais
%type<node> lista_argumentos_func
%type<node> corpo
%type<node> argumentos
%type<node> argumento
%type<node> literal
%type<node> bloco_de_comandos
%type<node> lista_comando_simples
%type<node> comando_simples
%type<node> cmdAtribuicao
%type<node> cmdAttribuicaoArranjoLista
%type<node> cmdReturn
%type<node> cmdIf
%type<node> optionalElse
%type<node> cmdWhile
%type<node> cmdDecVariavelLocal
%type<node> cmdDecVariavelLocalList
%type<node> cmdDecVariavelLocalInicializacao
%type<node> cmdChamadaFuncao
%type<node> cmdChamadaFuncaoArgumentos

// Operadores
%type<node> opUnario
%type<node> opNivel1
%type<node> opNivel2
%type<node> opNivel3
%type<node> opNivel4
%type<node> opNivel5
%type<node> opNivel6

// Operando
%type<node> operando

// Expressoes
%type<node> expressao
%type<node> exp1
%type<node> exp2
%type<node> exp3
%type<node> exp4
%type<node> exp5
%type<node> exp6
%type<node> exp7

%type<syntacticalType> tipo

%%

programa: lista_de_elementos {
        arvore = (void*)$1;
        $$ = $1;
    }
    | { $$ = NULL; } ;

lista_de_elementos: funcao lista_de_elementos_tail{ 
        //codeGenerator.appendCode($1, $2);
        appendChild($1, $2);
        $$ = $1;
    }
    | variaveis_globais lista_de_elementos_tail { $$ = $2; }
    | funcao  { $$ = $1; }
    | variaveis_globais { $$ = NULL; };

lista_de_elementos_tail: funcao lista_de_elementos_tail { 
        appendChild($1, $2);
        $$ = $1;
    }
    | variaveis_globais lista_de_elementos_tail { $$ = $2; }
    | funcao { $$ = $1; }
    | variaveis_globais { $$ = NULL; };

variaveis_globais: tipo lista_de_variaveis_globais ';' {
    SyntacticalType tipo = (SyntacticalType) $1;
	scopesManager.updateTypeOfVariablesWithPendantTypes(tipo);    
};

lista_de_variaveis_globais: lista_de_variaveis_globais ',' nome_global
    | nome_global;

nome_global: TK_IDENTIFICADOR {
        scopesManager.insertVariableWithUndefinedType($1->numeroLinha, $1);
    }
    | TK_IDENTIFICADOR '[' multi_dimensao ']' {
        //int indexerValue = $3->literalTokenValueAndType.value.integerValue;
	    //scopesManager.insertVectorWithPendantType($1->lineNumber, $1, indexerValue);
    };

multi_dimensao: TK_LIT_INT
    | multi_dimensao '^' TK_LIT_INT; 

tipo: TK_PR_INT  { $$ = intSType; scopesManager.saveLastReadType(intSType); }
    | TK_PR_FLOAT { $$ = floatSType; scopesManager.saveLastReadType(floatSType); }
    | TK_PR_BOOL { $$ = boolSType; scopesManager.saveLastReadType(boolSType); }
    | TK_PR_CHAR { $$ = charSType; scopesManager.saveLastReadType(charSType); } ;

literal: TK_LIT_INT { 
        $$ = createNodeNoTypeWithSType($1, intSType); 
        scopesManager.insertLiteral(get_line_number(), $1, intSType);
        //codeGenerator.makeLiteralCode($$);
    }
    | TK_LIT_FLOAT { 
        $$ = createNodeNoTypeWithSType($1, floatSType);
        scopesManager.insertLiteral(get_line_number(), $1, floatSType);    
    }
    | TK_LIT_FALSE { 
        $$ = createNodeNoTypeWithSType($1, boolSType);
        scopesManager.insertLiteral(get_line_number(), $1, boolSType);
    }
    | TK_LIT_TRUE { 
        $$ = createNodeNoTypeWithSType($1, boolSType);
        scopesManager.insertLiteral(get_line_number(), $1, boolSType);
    }
    | TK_LIT_CHAR{
        $$ = createNodeNoTypeWithSType($1, charSType);
        scopesManager.insertLiteral(get_line_number(), $1, charSType);
    };

funcao: funcao_header funcao_tail {
    appendChild($1, $2);
    $$ = $1;
};

funcao_header: tipo TK_IDENTIFICADOR {
    AST* nodeFuncDec = createNodeWithLexicalTypeAndValue(functionType, $2);
    $$ = nodeFuncDec;
    scopesManager.insertFunction($2->numeroLinha, nodeFuncDec, (SyntacticalType) $1);
    scopesManager.beginNewScope();
};

funcao_tail: '(' lista_argumentos_func ')' corpo {
    $$ = $4;
    scopesManager.endLastScope();
};

lista_argumentos_func: argumentos { $$ = $1; }
    | { $$ = NULL; };

argumentos: argumentos ',' argumento { 
        appendChild($3, $1);
        $$ = $3;
    }
    | argumento { $$ = $1; }; 

argumento: tipo TK_IDENTIFICADOR {
        AST* nodoArgumento = createNodeNoType($2);
        $$ = nodoArgumento;
    };


corpo: '{' lista_comando_simples '}' { $$ = $2; };

bloco_de_comandos: inicia_escopo '{' lista_comando_simples '}' { 
     $$ = $3; 
     scopesManager.endLastScope();
};

inicia_escopo: {
    scopesManager.beginNewScope();
 };

lista_comando_simples: comando_simples ';' lista_comando_simples { 
         if ($1 != NULL) {
            appendChild($1, $3);
            //codeGenerator.appendCode($1, $3);
            $$ = $1;
        } else {
            $$ = $3;
        }
    }
    | { $$ = NULL; }

comando_simples: cmdAtribuicao { $$ = $1; }
    | cmdReturn { $$ = $1; }
    | cmdIf { $$ = $1; }
    | cmdWhile { $$ = $1; }
    | cmdDecVariavelLocal { $$ = $1; }
    | cmdChamadaFuncao { $$ = $1; }
    | bloco_de_comandos { $$ = $1; }
    | { $$ = NULL; };

/* 
Comando atribuicao: 
    Descricao:  O comando de atribuição consiste em um identificador seguido pelo caractere de igualdade
    seguido por uma expressão.
    Um identificador pode ser um arranjo multidimensional. Neste caso, os índices são especificados,
    após o identificador, através de uma lista de expressões, iniciada com abre-colchetes [ e
    terminada com fecha-colchetes ], e cada elemento da lista é separado pelo caractere circunflexo ^.
*/

cmdAtribuicao: TK_IDENTIFICADOR '=' expressao {
        AST *nodoAtribuicao = createNodeWithLexicalTypeAndValue(attributionType, $2); 
        AST *nodoIdentificador = createNodeNoType($1);
        
        appendChild(nodoAtribuicao, nodoIdentificador);
        appendChild(nodoAtribuicao, $3);

        $$ = nodoAtribuicao;

        scopesManager.verifyIdentificatorNode(nodoIdentificador);
        scopesManager.makeAttributionVariable(nodoIdentificador, nodoAtribuicao, $3);
    }
    | TK_IDENTIFICADOR '[' cmdAttribuicaoArranjoLista ']' '=' expressao {

        AST *nodoAtribuicao = createNodeWithLexicalTypeAndValue(attributionType, $5); 
        AST *nodoIndexador = createNodeNoLexicalValue(indexerType);
        AST *nodoIdentificador = createNodeNoType($1);
        
        appendChild(nodoAtribuicao, nodoIndexador);
        appendChild(nodoIndexador, nodoIdentificador);
        appendChild(nodoIndexador, $3);
        appendChild(nodoAtribuicao, $6);

        $$ = nodoAtribuicao;

        scopesManager.verifyVectorNode(nodoIdentificador, nodoIndexador, $3);
        scopesManager.makeAttributionVector(nodoAtribuicao, $6, nodoIndexador);
    };

/// REVISITAR ESSA PARTE DE  cmdAttribuicaoArranjoLista - Acho que esta certa

cmdAttribuicaoArranjoLista: cmdAttribuicaoArranjoLista '^' expressao {
        AST *nodoIndexador = createNodeNoLexicalValue(indexerElement);
        appendChild(nodoIndexador, $1);
        appendChild(nodoIndexador, $3);
        $$ = nodoIndexador;
    }
    | expressao {
        $$ = $1;
    };
/* 
Comando Return: 
    Descricao: Trata-se do token return seguido de uma expressão.
*/

cmdReturn: TK_PR_RETURN expressao {
        AST *nodoReturn = createNodeNoLexicalValue(returnType);
        appendChild(nodoReturn, $2);
        $$ = nodoReturn;
    };

/* 
Comando IF: 
    Descricao: If seguido de uma expressão entre parênteses, seguido pelo token then
    seguido então por um bloco de comandos obrigatório. 
*/
 
cmdIf: TK_PR_IF '(' expressao ')' TK_PR_THEN bloco_de_comandos {
        AST *nodoIf = createNodeNoLexicalValue(ifType);
        appendChild(nodoIf, $3);
        appendChild(nodoIf, $6);
        $$ = nodoIf;
    }
    | TK_PR_IF '(' expressao ')' TK_PR_THEN bloco_de_comandos optionalElse {
        AST *nodoIf = createNodeNoLexicalValue(ifType);
        appendChild(nodoIf, $3);
        appendChild(nodoIf, $6);
        appendChild(nodoIf, $7);
        $$ = nodoIf;
    };

optionalElse: TK_PR_ELSE bloco_de_comandos { $$ = $2; };

/* 
Comando While: 
    Descricao: Temos apenas uma construção de repetição que é o token while seguido de 
    uma expressão entre parênteses e de um bloco de comandos.
*/

cmdWhile: TK_PR_WHILE '(' expressao ')' bloco_de_comandos {
    AST *nodoWhile = createNodeNoLexicalValue(whileType);
	appendChild(nodoWhile, $3);
	appendChild(nodoWhile, $5);
	$$ = nodoWhile;
};

/* 
Comando Declaracao de variavel local: 
    Descricao:  Consiste no tipo da variável seguido de uma lista composta de pelo menos um nome
    de variável (identificador) separadas por vírgula. Os tipos podem ser aqueles descritos
    na seção sobre variáveis globais.
    Uma variável local pode ser opcionalmente inicializada caso sua declaração seja seguida
    do operador composto <= e de um literal. 

    Importante: Arranjos multidimencionais so podem ser declarados como variaveis globais.
*/

cmdDecVariavelLocal: tipo cmdDecVariavelLocalList { 
    $$ = $2; 
    SyntacticalType tipo = (SyntacticalType) $1;
    scopesManager.updateTypeOfVariablesWithPendantTypes(tipo); 
}; 

cmdDecVariavelLocalList: TK_IDENTIFICADOR  { 
        $$ = NULL; 
        scopesManager.insertVariableWithUndefinedType($1->numeroLinha, $1);
    }
    | cmdDecVariavelLocalInicializacao { $$ = $1; }
    | TK_IDENTIFICADOR ',' cmdDecVariavelLocalList { 
        $$ = $3; 
        scopesManager.insertVariableWithUndefinedType($1->numeroLinha, $1);
    }
    | cmdDecVariavelLocalInicializacao ',' cmdDecVariavelLocalList {
        appendChild($1, $3);
        $$ = $1;
    };
    
cmdDecVariavelLocalInicializacao: TK_IDENTIFICADOR TK_OC_LE literal { 
        AST *nodoInicialization = createNodeNoType($2);
        AST *identifierNode = createNodeNoTypeWithSType($1, scopesManager.getLastReadType());
        appendChild(nodoInicialization, identifierNode);
        appendChild(nodoInicialization, $3);
        $$ = nodoInicialization;   

        scopesManager.makeInitialization(identifierNode, nodoInicialization, $3);
        scopesManager.insertVariableWithType($1->numeroLinha, $1, scopesManager.getLastReadType());
    };

/* 
Comando Chamada de funcao: 
    Descricao:  Uma chamada de função consiste no nome da função, seguida de argumentos
    entre parênteses separados por vírgula. Um argumento pode ser uma expressão.
*/

cmdChamadaFuncao: TK_IDENTIFICADOR '(' cmdChamadaFuncaoArgumentos ')'{
        AST *nodoFunctionCall = createNodeWithLexicalTypeAndValue(functionCallType, $1);
        appendChild(nodoFunctionCall, $3);
        $$ = nodoFunctionCall;
    };

cmdChamadaFuncaoArgumentos: expressao { $$ = $1; }
    | expressao ',' cmdChamadaFuncaoArgumentos {
        appendChild($1, $3);
        $$ = $1;
    }
    | { $$ = NULL; };

/*
Operadores binarios:
*/

opNivel1: '*' { $$ = createNodeNoType($1); };
    | '/' { $$ = createNodeNoType($1); };
    | '%' { $$ = createNodeNoType($1); };

opNivel2: '+' { $$ = createNodeNoType($1); };
    | '-' { $$ = createNodeNoType($1); };

 /* relacionais */
opNivel3: TK_OC_LE { $$ = createNodeNoType($1); }
    | TK_OC_GE { $$ = createNodeNoType($1); }
    | '<' { $$ = createNodeNoType($1); }
    | '>' { $$ = createNodeNoType($1); };

/* equalidade */
opNivel4: TK_OC_EQ { $$ = createNodeNoType($1); }
    | TK_OC_NE { $$ = createNodeNoType($1); };

 /* logical and */ 
opNivel5: TK_OC_AND { $$ = createNodeNoType($1); };

 /* logical or */
opNivel6: TK_OC_OR { $$ = createNodeNoType($1); };

/*
Operadores unarios:
*/

opUnario: '-' { $$ = createNodeNoType($1); }
    | '!' { $$ = createNodeNoType($1); }

/*
Expressoes:
*/

expressao: exp1 { $$ = $1; }
    | exp1 opNivel6 expressao { 
        appendChild($2, $1);
        appendChild($2, $3);
        $$ = $2;
        scopesManager.makeBinaryOperation($1, $2, $3);
    };

exp1: exp2 { $$ = $1; }
    | exp2 opNivel5 exp1 { 
        appendChild($2, $1);
        appendChild($2, $3);
        $$ = $2;
        scopesManager.makeBinaryOperation($1, $2, $3);
    };

exp2: exp3 { $$ = $1; }
    | exp3 opNivel4 exp2 { 
        appendChild($2, $1);
        appendChild($2, $3);
        $$ = $2;
        scopesManager.makeBinaryOperation($1, $2, $3);
    };

exp3: exp4 { $$ = $1; }
    | exp3 opNivel3 exp4 { 
        appendChild($2, $1);
        appendChild($2, $3);
        $$ = $2; 
        scopesManager.makeBinaryOperation($1, $2, $3);
    };

exp4: exp5 { $$ = $1; }
    | exp4 opNivel2 exp5 { 
        appendChild($2, $1);
        appendChild($2, $3);
        $$ = $2;
        scopesManager.makeBinaryOperation($1, $2, $3);
    };

exp5: exp6 { $$ = $1; }
    | exp5 opNivel1 exp6 {
        appendChild($2, $1);
        appendChild($2, $3);
        $$ = $2;
        scopesManager.makeBinaryOperation($1, $2, $3);
    };

exp6: exp7 { $$ = $1; }
    | opUnario exp7 { 
        appendChild($1, $2);
        $$ = $1;
        scopesManager.makeUnaryOperation($2, $1);
    };

exp7: operando { $$ = $1; }
    | '(' expressao ')' { 
        $$ = $2; 
    };

operando: TK_IDENTIFICADOR {
        $$ = createNodeNoType($1); 
	    scopesManager.verifyIdentificatorNode($$);
    }
    | TK_IDENTIFICADOR '[' cmdAttribuicaoArranjoLista ']' {
        AST *nodeIndexador = createNodeNoLexicalValue(indexerType);
        AST *nodoIdentificador = createNodeNoType($1);
        appendChild(nodeIndexador, nodoIdentificador);
        appendChild(nodeIndexador, $3);
        $$ = nodeIndexador;
        scopesManager.verifyVectorNode(nodoIdentificador, nodeIndexador, $3);
    }
    | literal { $$ = $1; }
    | cmdChamadaFuncao { $$ = $1; };

%%

void yyerror(const char *s) {
   printf("Erro sintatico [%s] na linha %d\n", s, get_line_number());
}
