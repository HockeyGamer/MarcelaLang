#include "include/parser.h"
#include "include/ast.h"

#include <stdio.h>
#include <stdlib.h>

static Token peek(Parser* p) {
    return p->list->tokens[p->pos];
}

static Token advance(Parser* p) {
    return p->list->tokens[p->pos++];
}

static Token expect(Parser* p, TokenType type, const char* msg) {
    if (peek(p).type != type) {
        fprintf(stderr, "Error: %s\n", msg);
        exit(1);
    }
    return advance(p);
}

ASTNode* parsePrimary(Parser* p) {
    Token t = peek(p);
    if (t.type == TOKEN_NUMBER) {
        advance(p);
        return createNumberNode(t.value);
    } // put future types here
    fprintf(stderr, "Error: Expected a number\n");
    exit(1);
}

ASTNode* parseExpression(Parser* p) {
    ASTNode* left = parsePrimary(p);

    while (peek(p).type == TOKEN_PLUS || peek(p).type == TOKEN_MINUS) {
        char op = (peek(p).type == TOKEN_PLUS) ? '+' : '-';
        advance(p);
        ASTNode* right = parsePrimary(p);
        left = makeBinOpNode(left, right, op);
    }

    return left;
}

ASTNode* parseProgram(Parser* p) {
    ASTNode* tree = parseExpression(p);
    expect(p, TOKEN_EOF, "Expected end of input");
    return tree;
}


ASTNode* parse(const TokenList* list) {
    Parser p = {list, 0};
    return parseProgram(&p);
}
