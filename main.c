#include <stdio.h>
#include <stdlib.h>

#include "include/parser.h"
#include "include/ast.h"
#include "include/codegen.h"
#include "include/semantic.h"
#include "assembler/assembler.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    char* filename = argv[1];

    char buffer[1024];
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return 1;
    }

    printf("File opened successfully: %s\n", filename);

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("Starting lexer\n");
        TokenList list = lex(buffer);

        ASTNode* tree = parse(&list);

        printAST(tree, 0);

        freeTokenList(&list);

        tree = analyze(tree);

        FILE* out = fopen("out.asm", "w");
        generateProgram(tree, out);
        fclose(out);
    }

    system("nasm out.asm -o out.o");

    fclose(file);

    return 0;
}