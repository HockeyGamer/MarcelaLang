#include "lexer.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void initTokenList(TokenList* list) {
    list->tokens = malloc(list->capacity * sizeof(Token));
    list->count = 0;
    list->capacity = 8;
}

void addToken(TokenList* list, Token token) {
    if (list->count >= list->capacity) {
        list->capacity *= 2;
        list->tokens = realloc(
            list->tokens,
            list->capacity * sizeof(Token)
        );
    }
    list->tokens[list->count] = token;
    list->count++;
}

void freeTokenList(TokenList* list) {
    free(list->tokens);
}

Token nextToken(const char* input, int* position) {
    char c = input[*position];

    while (c == ' ') {
        (*position)++;
        c = input[*position];
    }

    if(isdigit(c)) {
        int number = 0;

        while(isdigit(c)) {
            number = number * 10 + (input[*position] - '0');
            (*position)++;
            c = input[*position];
        }
        return (Token){TOKEN_NUMBER, number};
    }

    if (c == '+') {
        (*position)++;
        return (Token){TOKEN_PLUS, 0};
    }
    if (c == '\0') {
        return (Token){TOKEN_EOF, 0};
    }

    return (Token){TOKEN_ERROR, 0};
}

TokenList lex(const char* input) {
    printf("Lexing: %s\n", input);

    TokenList list;
    initTokenList(&list);


    int position = 0;
    Token token;

    do {
        token = nextToken(input, &position);

        addToken(&list, token);


        switch(token.type) {
            case TOKEN_NUMBER:
                printf("TOKEN: NUMBER: %d\n", token.value);
                break;

            case TOKEN_PLUS:
                printf("TOKEN: PLUS\n");
                break;

            case TOKEN_EOF:
                printf("TOKEN: EOF\n");
                break;

            case TOKEN_ERROR:
                fprintf(stderr, "Error: Invalid token\n");
                break;
        }

    } while(token.type != TOKEN_EOF && token.type != TOKEN_ERROR);

    printf("Lexing finished successfully\n");
    return list;
}
