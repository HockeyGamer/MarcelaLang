#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdint.h>
#include <stdio.h>

#include "ast.h"


typedef struct {
    uint8_t* data;
    size_t size;
    size_t capacity;
    FILE* listing;
} ByteBuffer;


void generateProgram(ASTNode* tree, ByteBuffer* b);

#endif // CODEGEN_H