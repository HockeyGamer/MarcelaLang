#include "include/codegen.h"
#include "include/x86.h"

void codegen(ASTNode* node, FILE* out, ByteBuffer* buffer) {
    if (node->type == NODE_NUMBER) {
        emitMovEaxImm(&buffer, node->value);
    } else if  (node->type == NODE_BINOP) {
        codegen(node->left, out, buffer);
        emitPushEax(&buffer);
        codegen(node->right, out, buffer);
        emitPopEbx(&buffer);
        if (node->op == '+') {
            emitAddEaxEbx(&buffer);
        } else if (node->op == '-') {
            emitSubEaxEbx(&buffer);
        } else if (node->op == '*') {
            emitImulEaxEbx(&buffer);
        } else if (node->op == '/') {
            emitXchgEaxEbx(&buffer);
            emitMovEdxEax(&buffer, 0);
            emitIdivEbx(&buffer);
        }
    }
}

void generateProgram(ASTNode* tree, FILE* out, ByteBuffer* buffer) {
    #ifdef __linux__
        fprintf(out, "section .text\n");
        fprintf(out, "global _start\n");
        fprintf(out, "_start:\n");
        codegen(tree, out, buffer);
        fprintf(out, "    ; Exit the program\n");
        fprintf(out, "    mov ebx, eax\n");
        fprintf(out, "    mov eax, 1\n");
        fprintf(out, "    int 0x80\n");
    #else
        fprintf(stderr, "Compiler only supports linux at the time");
    #endif
}