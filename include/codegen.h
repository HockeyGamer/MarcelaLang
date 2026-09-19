#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include <stdio.h>

void codegen(ASTNode* node, FILE* out);
void generateProgram(ASTNode* tree, FILE* out);

#endif // CODEGEN_H