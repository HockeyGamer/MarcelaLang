#include "parser.h"

#include <stdio.h>

void parse(const TokenList* list) {
    printf("Parsing %d tokens\n", list->count);
    
    for(int i = 0; i < list->count; i++) {
        const Token* token = &list->tokens[i];
        
        const Token* nextToken = (i + 1 < list->count) ? &list->tokens[i + 1] : NULL;
        if(token->type == TOKEN_NUMBER) {
            printf("parsed number: %d\n", token->value);
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