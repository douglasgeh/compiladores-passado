/*
AST

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/

#ifndef AST_H
#define AST_H

#include "ValorLexico.h"
#include "SyntacticalType.h"

 /* definicao dos tipos de nodos existentes.
    noType é usado geralmente quando há um valor léxico no nodo, como literais, identificadores, 
    operadores,..
  */
typedef enum {

    noType = 0,
    intKwType,
    floatKwType,
    charKwType,
    boolKwType,
    functionType,
    whileType,
    ifType,
    returnType,
    indexerType,
    indexerElement,
    attributionType,
    functionCallType

} NodeType;

 /* definicao de um nodo da arvore AST */
typedef struct AST {

    SyntacticalType sType; // E4
    NodeType nodeType;

    ValorLexico *value; 

    struct AST *child;
    struct AST *parent_next_child;

} AST;


AST* createNodeNoLexicalValue(NodeType type);
AST* createNodeNoType(ValorLexico *value); 
AST* createNodeWithLexicalTypeAndValue(NodeType type, ValorLexico *value); 
AST* createNodeNoTypeWithSType(ValorLexico *value, SyntacticalType sType);

void exporta(void *arvore);
void libera(void *arvore);

void printNodeType(NodeType nodeType);
void appendChild(AST *rootNode, AST *newChild);
void prependChild(AST *rootNode, AST *newChild);
void printValues(AST *tree);


#endif