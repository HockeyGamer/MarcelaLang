#include "include/codegen.h"
#include "include/x86.h"

void codegen(ASTNode* node, ByteBuffer* b) {
    if (node->type == NODE_NUMBER) {
        Operand dest = {.type = OPERAND_REG, .reg = REG_EAX};
        Operand src = {.type = OPERAND_IMM, .immValue = node->value};
        assemble("mov", dest, src, b);
    } else if  (node->type == NODE_BINOP) {
        codegen(node->left, b);

        Operand eaxOp = {.type = OPERAND_REG, .reg = REG_EAX};
        assemble("push", eaxOp, (Operand){0}, b);

        codegen(node->right, b);

        Operand ebxOp = {.type = OPERAND_REG, .reg = REG_EBX};
        assemble("mov", ebxOp, (Operand){0}, b);

        assemble("pop", eaxOp, (Operand){0}, b);

        if (node->op == '+') {
            assemble("add", eaxOp, ebxOp, b);
        } else if (node->op == '-') {
            assemble("sub", eaxOp, ebxOp, b);
        } else if (node->op == '*') {
            assemble("imul", eaxOp, ebxOp, b);
        } else if (node->op == '/') {
            assemble("cdq", (Operand){0}, (Operand){0}, b);
            assemble("idiv", ebxOp, (Operand){0}, b);
        }
    }
}

void generateProgram(ASTNode* tree, ByteBuffer* b) {
    codegen(tree, b);
    /*#ifdef __linux__
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
    #endif */
}// this is just here for future reference