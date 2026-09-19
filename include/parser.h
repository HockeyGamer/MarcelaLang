#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

typedef struct {
    const TokenList* list;
    int pos;
} Parser;

ASTNode* parse(const TokenList* list);

#endif // PARSER_H