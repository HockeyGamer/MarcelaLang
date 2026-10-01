#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include "x86.h"
#include <stdio.h>

void generateProgram(ASTNode* tree, ByteBuffer* buffer);

#endif // CODEGEN_H