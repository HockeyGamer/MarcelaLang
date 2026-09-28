#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include <stdio.h>

void generateProgram(ASTNode* tree, FILE* out);

#endif // CODEGEN_H