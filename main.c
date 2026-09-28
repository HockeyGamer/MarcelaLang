// I love you marcela <3
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "include/parser.h"
#include "include/ast.h"
#include "include/codegen.h"
#include "include/semantic.h"
#include "include/file.h"

int main(int argc, char* argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    char* inputFile = argv[1];
    bool giveAssembly = false;

    for(int i = 0; i < argc; i++) {
            char* arg = argv[i];
            if (arg[0] == '-') {
                if (arg[1] == 's') {
                    giveAssembly = true;
                }
                else {
                    fprintf(stderr, "incorrect argument");
                }
            } else {
                inputFile = argv[i];
            }
    }

    if (inputFile == NULL) {
        fprintf(stderr, "Usage: marcela_compiler [-s] <file>\n");
        return 1;
    }

    FILE* file = fopen(inputFile, "r");

    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", inputFile);
        return 1;
    }

    fileSeek(file, 0, SEEK_END);
    FileOffset size = fileTell(file);
    rewind(file);

    char* buffer = malloc(size + 1);

    fread(buffer, size, 1, file);
    buffer[size] = '\0';


    printf("File opened successfully: %s\n", inputFile);

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

    system("nasm out.asm -o out.o");

        if(!giveAssembly) {
        if (remove("out.asm") != 0) {
             perror("Error deleting file");
        }
    }

    fclose(file);

    return 0;
}