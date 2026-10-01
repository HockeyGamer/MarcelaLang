// I love you marcela <3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/parser.h"
#include "include/ast.h"
#include "include/codegen.h"
#include "include/semantic.h"
#include "include/file.h"
#include "include/x86.h"

int main(int argc, char* argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: marcela_compiler [-s] <file>");
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
    
    printf("Starting lexer\n");
    TokenList list = lex(buffer);

    free(buffer);

    ASTNode* tree = parse(&list);

    printAST(tree, 0);

    freeTokenList(&list);

    tree = analyze(tree);

    ByteBuffer byteBuffer = {0};

    if (giveAssembly){
        byteBuffer.listing = fopen("out.asm", "w");
    }

    generateProgram(tree, &byteBuffer);

    FILE* out = fopen("out.bin", "wb");
    fwrite(byteBuffer.data, 1, byteBuffer.size, out);
    fclose(out);

    if(byteBuffer.listing) fclose(byteBuffer.listing);
    free(byteBuffer.data);

    free(tree);

    fclose(file);

    return 0;
}