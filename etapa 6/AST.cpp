/*
AST

Autores:
  --> Douglas Gehring
  --> Tobias Soares

Grupo: O
*/

#include "AST.hpp"
#include <cstdio>
#include <stdlib.h>

AST* createNodeNoType(ValorLexico *value) {

    AST newNode;
    newNode.child = NULL;
    newNode.parent_next_child = NULL;
    newNode.value = value;
    newNode.nodeType = noType;
  
    AST *newNodePointer = (AST*) malloc(sizeof(newNode));

    *newNodePointer = newNode;
    return newNodePointer;
}

AST* createNodeNoTypeWithSType(ValorLexico *value, SyntacticalType sType) {
    AST* newNode = createNodeNoType(value);
    newNode->sType = sType;
    return newNode;
}

AST* createNodeNoLexicalValue(NodeType type) {
    
    AST newNode;
    newNode.nodeType = type;
    newNode.value = NULL;
    newNode.child = NULL;
    newNode.parent_next_child = NULL;
 
    AST *newNodePointer = (AST*) malloc(sizeof(newNode));
    *newNodePointer = newNode;
    return newNodePointer;
}

AST* createNodeWithLexicalTypeAndValue(NodeType type, ValorLexico *value) {
    
    AST *newNodePointer = (AST*) malloc(sizeof(AST));

    AST newNode;
    newNode.nodeType = type;
    newNode.value = value;
    newNode.child = NULL;
    newNode.parent_next_child = NULL;
    
    *newNodePointer = newNode;
    return newNodePointer;
}


void appendChild(AST *rootNode, AST *newChild) {

    if (rootNode == NULL) { return; }

    AST *currentChild = rootNode->child;
    AST *previousChild = rootNode->child;

    while (currentChild != NULL) {
        previousChild = currentChild;
        currentChild = currentChild->parent_next_child;
    }
    if (previousChild != NULL) {
        previousChild->parent_next_child = newChild;
    }else {
        rootNode->child = newChild;
    }

}

void prependChild(AST *rootNode, AST *newChild) {

    if (rootNode == NULL) { return; }

    AST *firstChild = rootNode->child;

    newChild->parent_next_child = firstChild;
    rootNode->child = newChild;

}

void printAdresses(AST *tree) {

    if (tree == NULL) { return; }
    
    AST *first_child = tree->child;
    AST *child = tree->child;

    while (child != NULL) {
        printf("%p, %p\n", tree, child);
        child = child->parent_next_child;
    }
    while (first_child != NULL)
    {
        printAdresses(first_child);
        first_child = first_child->parent_next_child;
    }

}

void printValues(AST *tree) {

    if (tree == NULL) { return; }
    
    AST *first_child = tree->child;

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
        first_child = first_child->parent_next_child;
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
    AST *next_child = tree_root->parent_next_child;
    ValorLexico *value = tree_root->value;

    libera(next_child);
    libera(first_child);
    free_valor_lexico(value);
    free(tree_root);
    tree_root = NULL;
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

AST *getLastChild(AST *rootNode) {

    if (rootNode == NULL) { return NULL; }

    AST *first_child = rootNode->child;

    while (first_child != NULL && first_child->parent_next_child != NULL) {
        first_child = first_child->parent_next_child;
    }
    return first_child;
}