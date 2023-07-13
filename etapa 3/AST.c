/*
AST

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/

#include "AST.h"
#include <stdio.h>
#include <stdlib.h>

AST* createNodeNoType(ValorLexico *value) {

    AST newNode;
    newNode.child = NULL;
    newNode.sister = NULL;
    newNode.value = value;
    newNode.nodeType = noType;
  
    AST *newNodePointer = malloc(sizeof(newNode));

    *newNodePointer = newNode;
    return newNodePointer;
}

AST* createNodeNoLexicalValue(NodeType type) {
    
    AST newNode;
    newNode.nodeType = type;
    newNode.value = NULL;
    newNode.child = NULL;
    newNode.sister = NULL;
 
    AST *newNodePointer = malloc(sizeof(newNode));
    *newNodePointer = newNode;
    return newNodePointer;
}

AST* createNodeWithLexicalTypeAndValue(NodeType type, ValorLexico *value) {
    
    AST *newNodePointer = malloc(sizeof(AST));

    AST newNode;
    newNode.nodeType = type;
    newNode.value = value;
    newNode.child = NULL;
    newNode.sister = NULL;
    
    *newNodePointer = newNode;
    return newNodePointer;
}


void appendChild(AST *rootNode, AST *newChild) {

    if (rootNode == NULL) { return; }

    AST *firstChild = rootNode->child;
    AST *firstChildPrev = rootNode->child;

    while (firstChild != NULL) {
        firstChildPrev = firstChild;
        firstChild = firstChild->sister;
    }
    if (firstChildPrev != NULL) {
        firstChildPrev->sister = newChild;
    }else {
        rootNode->child = newChild;
    }

}

void prependChild(AST *rootNode, AST *newChild) {

    if (rootNode == NULL) { return; }

    AST *firstChild = rootNode->child;
    
    newChild->sister = firstChild;
    rootNode->child = newChild;

}

void printAdresses(AST *tree) {

    if (tree == NULL) { return; }
    
    AST *first_child = tree->child;
    AST *child = tree->child;

    while (child != NULL) {
        printf("%p, %p\n", tree, child);
        child = child->sister;
    }
    while (first_child != NULL)
    {
        printAdresses(first_child);
        first_child = first_child->sister;
    }

}

void printValues(AST *tree) {

    if (tree == NULL) { return; }
    
    AST *first_child = tree->child;
    AST *child = tree->child;

    printf("%p [label=\"", tree);

    if (tree->nodeType != noType) {
        printNodeType(tree->nodeType);
    }
    if (tree->value != NULL) {
        
        print_valor_literal(tree->value->valorTipoTokenLiteral);
    } 
    printf("\"];\n");

    while (first_child != NULL)
    {
        printValues(first_child);
        first_child = first_child->sister;
    }

}

void exporta(void *arvore) {

    AST *tree_root = (AST *) arvore;
    printAdresses(tree_root);
    printValues(tree_root);

}

void libera(void *arvore) {

    AST *tree_root = (AST *) arvore;
    if (tree_root == NULL) { return; }
    
    AST *first_child = tree_root->child;
    AST *first_sister = tree_root->sister;
    ValorLexico *value = tree_root->value;

    free_valor_lexico(value);
    free(tree_root);
    libera(first_sister);
    libera(first_child);

}


void printNodeType(NodeType nodeType) {

    switch (nodeType)
    {
        case whileType:
            printf("%s", "while");
            break;
        case ifType:
            printf("%s","if");
            break;
        case returnType:
            printf("%s","return");
            break;
        case indexerType:
            printf("%s","[]");
            break;
        case functionCallType:
            printf("call ");
            break;
        case indexerElement:
            printf("^");
            break;
        default:
            break;
    }

}