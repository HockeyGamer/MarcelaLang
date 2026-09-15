#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_EOF,
    TOKEN_ERROR
} TokenType;

typedef struct {
    TokenType type;
    int value;
} Token;

typedef struct {
    Token* tokens;
    int count;
    int capacity;
} TokenList;

// Function prototypes for the lexer
TokenList lex(const char* input);

void freeTokenList(TokenList* list);

#endif // LEXER_H