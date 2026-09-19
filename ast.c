#include "include/ast.h"

#include <stdlib.h>
#include <stdio.h>

ASTNode* createNumberNode(int value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_NUMBER;
    node->value = value;
    return node;
}

ASTNode* makeBinOpNode(ASTNode* left, ASTNode* right, char op) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node-> type = NODE_BINOP;
    node->op = op;
    node->left = left;
    node->right = right;
    return node;
}

void printAST(ASTNode* node, int depth) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < depth; i++) {
        printf("  "); // two spaces per depth level
    }

    if (node->type == NODE_NUMBER) {
        printf("NUMBER: %d\n", node->value);
    } else if (node->type == NODE_BINOP) {
        printf("BINOP: %c\n", node->op);
        printAST(node->left, depth + 1);
        printAST(node->right, depth + 1);
    }
}