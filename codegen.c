#include "include/codegen.h"

void codegen(ASTNode* node, FILE* out){
    if (node->type == NODE_NUMBER) {
        fprintf(out, "    mov eax, %d\n", node->value);
    } else if  (node->type == NODE_BINOP) {
        codegen(node->left, out);
        fprintf(out, "    push eax\n");
        codegen(node->right, out);
        fprintf(out, "    pop ebx\n");
        if (node->op == '+') {
            fprintf(out, "    add eax, ebx\n");
        }
    }
}

void generateProgram(ASTNode* tree, FILE* out) {
    fprintf(out, "section .text\n");
    fprintf(out, "global _start\n");
    fprintf(out, "_start:\n");
    codegen(tree, out);
    fprintf(out, "    ; Exit the program\n");
    fprintf(out, "    mov ebx, eax\n");
    fprintf(out, "    mov eax, 1\n");
    fprintf(out, "    int 0x80\n");
}