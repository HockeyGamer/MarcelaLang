#include <stdlib.h>

#include "include/x86.h"
#include "include/codegen.h"

#include <string.h>



OpcodeEntry opcodeTable[] = {
    {"mov", FORM_REG_REG, 0x89},
    {"mov", FORM_REG_IMM32, 0xB8},
    {"add", FORM_REG_REG, 0x01},
    {"sub", FORM_REG_REG, 0x29},
    {"imul", FORM_REG_REG, 0x0F},
    {"idiv", FORM_REG_REG, 0xF7},
    {"push", FORM_REG_REG, 0x50},
    {"pop", FORM_REG_REG, 0x58},
    {"cdq", FORM_NONE, 0x99},
    {NULL, FORM_NONE, 0} // Sentinel value to mark the end of the table
};

void bufferPush(ByteBuffer* b, uint8_t byte) {
    if(b->size == b->capacity){
        size_t newCap = (b->capacity == 0) ? 64 : b->capacity * 2;
        uint8_t* newData = realloc(b->data, newCap);
        if(newData == NULL) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            exit(1);
        }
        b->data = newData;
        b->capacity = newCap;
    }    
    b->data[b->size++] = byte;
}

void bufferPushInt(ByteBuffer* b, int value) {
    for(int i = 0; i < 4; i++) {
        bufferPush(b, (value >> (i * 8)) & 0xFF);
    }
}

const char* getRegName(uint8_t reg) {
    const char* regs[] = {"eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"};
    return regs[reg];
}

void printOperand(FILE* f, Operand op) {
    if (op.type == OPERAND_REG) {
        fprintf(f, "%s", getRegName(op.reg));
    } else if (op.type == OPERAND_IMM) {
        fprintf(f, "%d", op.immValue);
    } else if (op.type == OPERAND_MEM) {
        fprintf(f, "[%s]", getRegName(op.reg));
    }
}



void assemble(const char* name, Operand dest, Operand src, ByteBuffer* b) {
    FormatType currentFormat = FORM_NONE;

    if(dest.type == OPERAND_REG && src.type == OPERAND_REG) {
        currentFormat = FORM_REG_REG;
    } else if (dest.type == OPERAND_REG && src.type == OPERAND_IMM) {
        currentFormat = FORM_REG_IMM32;
    }

    for(int i = 0; opcodeTable[i].name != NULL; i++) {
        if (strcmp(opcodeTable[i].name, name) == 0 && opcodeTable[i].format == currentFormat) {
            uint8_t base = opcodeTable[i].baseOpcode;

            if (currentFormat == FORM_REG_REG) {
                bufferPush(b, base);
                uint8_t modrm = (0x3 << 6) | (src.reg << 3) | dest.reg;
                bufferPush(b, modrm);
            } else if (currentFormat == FORM_REG_IMM32) {
                bufferPush(b, base + dest.reg);
                bufferPushInt(b, src.immValue);
            }


            if (b->listing != NULL) {
                fprintf(b->listing, "    %s ", name);

                if (currentFormat == FORM_REG_REG || currentFormat == FORM_REG_IMM32) {
                    printOperand(b->listing, dest);
                    fprintf(b->listing, ", ");
                    printOperand(b->listing, src);
                } else {
                    printOperand(b->listing, dest);
                }

                fprintf(b->listing, "\n");
            }

            return;
        }
    }

    fprintf(stderr, "Error: Unsupported instruction format for %s\n", name);
}