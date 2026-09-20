// I love you marcela <3
#include <stdio.h>
#include <stdlib.h>

#include "include/parser.h"
#include "include/ast.h"
#include "include/codegen.h"
#include "include/semantic.h"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    char* filename = argv[1];

    FILE* file = fopen(filename, "r");

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* buffer = malloc(size + 1);

    fread(buffer, size, 1, file);
    buffer[size] = '\0';

    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return 1;
    }

    printf("File opened successfully: %s\n", filename);

    fread(buffer, 1, size, file);
    
    printf("Starting lexer\n");
    TokenList list = lex(buffer);

    ASTNode* tree = parse(&list);

    printAST(tree, 0);

    freeTokenList(&list);

    tree = analyze(tree);

    FILE* out = fopen("out.asm", "w");
    generateProgram(tree, out);
    fclose(out);

    free(tree);

    //system("nasm out.asm -o out.o"); // remove comment to compile the assembly

    fclose(file);

    return 0;
}