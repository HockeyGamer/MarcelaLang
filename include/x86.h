#ifndef x86_H
#define x86_H

#include <stddef.h>
#include <stdio.h>

typedef struct {
    unsigned char* data;
    size_t size;
    size_t capacity;
    FILE* listing;
} ByteBuffer;

void emitMovEaxImm(ByteBuffer* b, int value);
void emitPushEax(ByteBuffer* b);
void emitPopEbx(ByteBuffer* b);
void emitAddEaxEbx(ByteBuffer* b);
void emitSubEaxEbx(ByteBuffer* b);
void emitRet(ByteBuffer* b);
void emitXchgEaxEbx(ByteBuffer* b);
void emitImulEaxEbx(ByteBuffer* b);
void emitIdivEbx(ByteBuffer* b);
void emitCdq(ByteBuffer* b);

#endif // x86_H