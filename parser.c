#include "include/parser.h"

#include <stdio.h>
#include <stdbool.h>


// this is because theres deadass like 4 tokens rn later I am going to make a way more complicated system so it doesnt become a mess but for now whatever
static const TokenType allowedAfterNumber[] = {
    TOKEN_PLUS,
    TOKEN_EOF
};

bool allowedAfterToken(const TokenType list[], TokenType tokenType, int listSize) {
    for (int i = 0; i < listSize; i++) {
        if (tokenType == list[i]) {
            return true;
        }
    }
    return false;
}

void parse(const TokenList* list) {
    printf("Parsing %d tokens\n", list->count);
    
    for(int i = 0; i < list->count; i++) {
        const Token* token = &list->tokens[i];
        const Token* nextToken = (i + 1 < list->count) ? &list->tokens[i + 1] : NULL;
        const Token* prevToken = (i - 1 >= 0) ? &list->tokens[i - 1] : NULL;


        if(token->type == TOKEN_NUMBER) {
            printf("parsed number: %d\n", token->value);

            if (nextToken && !allowedAfterToken(allowedAfterNumber, nextToken->type, sizeof(allowedAfterNumber) / sizeof(allowedAfterNumber[0]))) {
                fprintf(stderr, "Error: Unexpected token after number\n");
                return;
            }
        } else if (token->type == TOKEN_PLUS) {
            printf("parsed plus\n");

            if (nextToken && nextToken->type == TOKEN_PLUS){
                fprintf(stderr, "Error: Unexpected token after plus\n");
                return;
            }
        } else if (token->type == TOKEN_EOF) {
            printf("parsed EOF\n");
        }
    }
}