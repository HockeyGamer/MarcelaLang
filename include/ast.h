#ifndef AST_H
#define AST_H

typedef enum {
    NODE_NUMBER,
    NODE_BINOP
} NodeType;

typedef struct ASTNode {
    NodeType type;
    int value;
    char op;
    struct ASTNode* left;
    struct ASTNode* right;
} ASTNode;

ASTNode* createNumberNode(int value);

ASTNode* makeBinOpNode(ASTNode* left, ASTNode* right, char op);

void printAST(ASTNode* node, int depth);

#endif // AST_H