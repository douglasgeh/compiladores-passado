/*
Funções extras para o trabalho

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/

extern "C" {
  extern int yylineno;
}

int get_line_number() {
  return yylineno;
}
