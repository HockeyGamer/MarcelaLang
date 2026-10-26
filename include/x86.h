#ifndef x86_H
#define x86_H

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#include "codegen.h"

typedef enum {
    REG_EAX = 0,
    REG_ECX = 1,
    REG_EDX = 2,
    REG_EBX = 3,
    REG_ESP = 4,
    REG_EBP = 5,
    REG_ESI = 6,
    REG_EDI = 7
} x86Reg;

typedef enum {
    OPERAND_NONE,
    OPERAND_REG,
    OPERAND_MEM,
    OPERAND_IMM,
} OperandType;

typedef struct {
    OperandType type;
    x86Reg reg;
    uint32_t immValue;
} Operand;


typedef enum {
    FORM_REG_REG,
    FORM_REG_IMM32,
    FORM_REG_MEM,
    FORM_MEM_REG,
    FORM_MEM_IMM32,
    FORM_IMM32_REG,
    FORM_IMM32_MEM,
    FORM_REG_NONE,
    FORM_NONE
} FormatType;

typedef struct {
    const char* name;
    FormatType format;
    uint8_t baseOpcode;
} OpcodeEntry;


void assemble(const char* name, Operand dest, Operand src, ByteBuffer* b);
#endif // x86_H