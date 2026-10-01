#include "include/x86.h"

void bufferPush(ByteBuffer* b, unsigned char byte) {
    if(b->size == b->capacity){
        size_t newCap = (b->capacity == 0) ? 64 : b->capacity * 2;
        unsigned char* newData = realloc(b->data, newCap);
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

void emitMovEaxImm(ByteBuffer* b, int value) {
    bufferPush(b, 0xB8); // opcode for mov eax, imm32
    bufferPushInt(b, value);
    if (b->listing) fprintf(b->listing, "mov eax, %d\n", value);
}

void emitPushEax(ByteBuffer* b) {
    bufferPush(b, 0x50); // opcode for push eax
    if (b->listing) fprintf(b->listing, "push eax\n");
}

void emitPopEbx(ByteBuffer* b) {
    bufferPush(b, 0x58); // opcode for pop ebx
    if (b->listing) fprintf(b->listing, "pop ebx\n");
}

void emitAddEaxEbx(ByteBuffer* b) {
    bufferPush(b, 0x01); // opcode for add eax, ebx
    bufferPush(b, 0xD8);
    if (b->listing) fprintf(b->listing, "add eax, ebx\n");
}

void emitSubEaxEbx(ByteBuffer* b) {
    bufferPush(b, 0x29); // opcode for sub eax, ebx
    bufferPush(b, 0xD8);
    if (b->listing) fprintf(b->listing, "sub eax, ebx\n");
}

void emitRet(ByteBuffer* b) {
    bufferPush(b, 0xC3); // opcode for ret
    if (b->listing) fprintf(b->listing, "ret\n");
}

void emitXchgEaxEbx(ByteBuffer* b) {
    bufferPush(b, 0x87); // opcode for xchg eax, ebx
    bufferPush(b, 0xD8);
    if (b->listing) fprintf(b->listing, "xchg eax, ebx\n");
}

void emitImulEaxEbx(ByteBuffer* b) {
    bufferPush(b, 0x0F); // opcode for imul eax, ebx
    bufferPush(b, 0xAF);
    bufferPush(b, 0xC3);
    if (b->listing) fprintf(b->listing, "imul eax, ebx\n");
}

void emitIdivEbx(ByteBuffer* b) {
    bufferPush(b, 0xF7); // opcode for idiv ebx
    bufferPush(b, 0xF3);
    if (b->listing) fprintf(b->listing, "idiv ebx\n");
}