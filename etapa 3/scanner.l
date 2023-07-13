/* 
Arquivo para a leitura de tokens
Autores:
  --> Douglas Gehring
  --> Tobias Soares 

Grupo: O
*/

%{
  #include "parser.tab.h"
  #include "ValorLexico.h"
  #include <stdio.h>
%}

%option noyywrap
%option yylineno

%option nounput
%option noinput

%x MULTILINE_COMMENT

space [ \t\n\r]
character [a-zA-Z]
identifier {character}+
integer [0-9]+
float {integer}\.{integer}((e|E){integer})?
char '.?'
special [,;:(){}\[\]+\-*/%^<>=!]
comment "//".*

%%
"/*" { BEGIN(MULTILINE_COMMENT); }
<MULTILINE_COMMENT>"*/" BEGIN(INITIAL);
<MULTILINE_COMMENT>"\n" {}
<MULTILINE_COMMENT><<EOF>>  { return TK_ERRO; }
<MULTILINE_COMMENT>. {}

"int"    { return TK_PR_INT; }
"float"  { return TK_PR_FLOAT; }
"bool"   { return TK_PR_BOOL; }
"char"   { return TK_PR_CHAR; }
"if"     { return TK_PR_IF; }
"then"   { return TK_PR_THEN; }
"else"   { return TK_PR_ELSE; }
"while"  { return TK_PR_WHILE; }
"input"  { return TK_PR_INPUT; }
"output" { return TK_PR_OUTPUT; }
"return" { return TK_PR_RETURN; }
"for"    { return TK_PR_FOR; }

"<=" { 
  valor_lexico_de_token_nao_literal(yylineno, yytext, operadorComposto);
  return TK_OC_LE; 
  }
">=" { 
  valor_lexico_de_token_nao_literal(yylineno, yytext, operadorComposto);
  return TK_OC_GE; 
  }
"==" { 
  valor_lexico_de_token_nao_literal(yylineno, yytext, operadorComposto);
  return TK_OC_EQ; 
  }
"!=" { 
  valor_lexico_de_token_nao_literal(yylineno, yytext, operadorComposto);
  return TK_OC_NE; 
  }
"&&" { 
  valor_lexico_de_token_nao_literal(yylineno, yytext, operadorComposto);
  return TK_OC_AND; 
  }
"||" { 
  valor_lexico_de_token_nao_literal(yylineno, yytext, operadorComposto);
  return TK_OC_OR; 
  }

"true"  { 
  yylval.valor_lexico = valor_lexico_de_token_literal(yylineno, yytext, tipoBool);
  return TK_LIT_TRUE; 
  }
"false" { 
  yylval.valor_lexico = valor_lexico_de_token_literal(yylineno, yytext, tipoBool);
  return TK_LIT_FALSE; 
  }

{identifier} { 
  yylval.valor_lexico = valor_lexico_de_token_nao_literal(yylineno, yytext, identificador);
  return TK_IDENTIFICADOR; 
  }
{char}       { 
  yylval.valor_lexico = valor_lexico_de_token_literal(yylineno, yytext, tipoChar);
  return TK_LIT_CHAR; 
  }
{integer}    { 
  yylval.valor_lexico = valor_lexico_de_token_literal(yylineno, yytext, tipoInteger);
  return TK_LIT_INT; 
  }
{float}      {
  yylval.valor_lexico = valor_lexico_de_token_literal(yylineno, yytext, tipoFloat); 
  return TK_LIT_FLOAT; 
  }
{special}    { 
  yylval.valor_lexico = valor_lexico_de_token_nao_literal(yylineno, yytext, characterEspecial);
  return yytext[0]; 
  }
{space}      {}
{comment}    {}

. { return TK_ERRO; }

%%
