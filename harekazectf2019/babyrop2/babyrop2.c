//
// This file was generated by the Retargetable Decompiler
// Website: https://retdec.com
// Copyright (c) 2019 Retargetable Decompiler <info@retdec.com>
//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ------------------------ Structures ------------------------

struct _IO_FILE {
    int32_t e0;
};

// --------------------- Global Variables ---------------------

struct _IO_FILE * g1 = NULL;
struct _IO_FILE * g2 = NULL;

// ------------------------ Functions -------------------------

// Address range: 0x400636 - 0x4006cc
int main(int argc, char ** argv) {
    // 0x400636
    setvbuf(g1, NULL, 2, 0);
    setvbuf(g2, NULL, 2, 0);
    printf("What's your name? ");
    int64_t buf; // bp-40
    int32_t v1 = read(0, &buf, 256); // 0x40069a
    int64_t v2; // rbp
    *(char *)(v2 - 32 + (int64_t)(v1 - 1)) = 0;
    printf("Welcome to the Pwn World again, %s!\n", &buf);
    return 0;
}

// --------------- Dynamically Linked Functions ---------------

// int printf(const char * restrict format, ...);
// ssize_t read(int fd, void * buf, size_t nbytes);
// int setvbuf(FILE * restrict stream, char * restrict buf, int modes, size_t n);

// --------------------- Meta-Information ---------------------

// Detected compiler/packer: gcc (5.4.0)
// Detected functions: 1
// Decompilation date: 2019-08-01 16:28:27
