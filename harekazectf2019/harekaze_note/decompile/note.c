//
// This file was generated by the Retargetable Decompiler
// Website: https://retdec.com
// Copyright (c) 2019 Retargetable Decompiler <info@retdec.com>
//

#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// ------------------------ Structures ------------------------

struct _IO_FILE {
    int32_t e0;
};

// ------------------- Function Prototypes --------------------

int64_t entry_point(int64_t a1, int64_t a2, int64_t a3, int64_t a4);
int64_t function_1000(void);
void function_1030(int64_t * ptr);
int32_t function_1040(char * s);
void function_1050(void);
int32_t function_1060(char * format, ...);
int32_t function_1070(int32_t seconds);
int32_t function_1080(int32_t fd, int64_t * buf, int32_t nbytes);
int32_t function_1090(char * s1, char * s2);
void (*function_10a0(int32_t sig, void (*handler)(int32_t)))(int32_t);
int64_t * function_10b0(int32_t size);
int32_t function_10c0(struct _IO_FILE * stream, char * buf, int32_t modes, int32_t n);
int32_t function_10d0(char * nptr);
void function_10e0(int32_t status);
void function_10f0(int64_t * d);
int64_t function_1130(void);
int64_t function_1160(void);
int64_t function_11a0(void);
int64_t function_11e0(void);
int64_t function_11e5(void);
int64_t function_11ff(void);
int64_t function_1297(int64_t * a1, int64_t a2);
int64_t function_1326(void);
int64_t function_1370(void);
int64_t function_13c1(void);
int64_t function_145a(int64_t * str);
int64_t function_14bc(void);
int64_t function_15ba(void);
int64_t function_1640(void);
int64_t function_16fc(void);
int64_t function_1770(int64_t a1, int64_t a2, int64_t a3);
int64_t function_17d0(void);
int64_t function_17d4(void);

// --------------------- Global Variables ---------------------

int64_t g1 = 0x11e0;
int64_t g2 = 0x11a0;
struct _IO_FILE * g3 = NULL;
struct _IO_FILE * g4 = NULL;
struct _IO_FILE * g5 = NULL;
char g6 = 0;
int32_t g7 = 0;
int32_t g8 = 0;
char * g9;
char * g10;
char * g11;
int32_t g12;

// ------------------------ Functions -------------------------

// Address range: 0x1000 - 0x1017
int64_t function_1000(void) {
    // 0x1000
    int64_t result; // 0x1016
    if (*(int64_t *)0x3fe8 != 0) {
        // 0x1010
        __gmon_start__();
        result = &g12;
    } else {
        result = 0;
    }
    // 0x1012
    return result;
}

// Address range: 0x1030 - 0x1036
void function_1030(int64_t * ptr) {
    // 0x1030
    free(ptr);
}

// Address range: 0x1040 - 0x1046
int32_t function_1040(char * s) {
    // 0x1040
    return puts(s);
}

// Address range: 0x1050 - 0x1056
void function_1050(void) {
    // 0x1050
    __stack_chk_fail();
}

// Address range: 0x1060 - 0x1066
int32_t function_1060(char * format, ...) {
    // 0x1060
    return printf(format);
}

// Address range: 0x1070 - 0x1076
int32_t function_1070(int32_t seconds) {
    // 0x1070
    return alarm(seconds);
}

// Address range: 0x1080 - 0x1086
int32_t function_1080(int32_t fd, int64_t * buf, int32_t nbytes) {
    // 0x1080
    return read(fd, buf, nbytes);
}

// Address range: 0x1090 - 0x1096
int32_t function_1090(char * s1, char * s2) {
    // 0x1090
    return strcmp(s1, s2);
}

// Address range: 0x10a0 - 0x10a6
void (*function_10a0(int32_t sig, void (*handler)(int32_t)))(int32_t) {
    // 0x10a0
    return signal(sig, handler);
}

// Address range: 0x10b0 - 0x10b6
int64_t * function_10b0(int32_t size) {
    // 0x10b0
    return malloc(size);
}

// Address range: 0x10c0 - 0x10c6
int32_t function_10c0(struct _IO_FILE * stream, char * buf, int32_t modes, int32_t n) {
    // 0x10c0
    return setvbuf(stream, buf, modes, n);
}

// Address range: 0x10d0 - 0x10d6
int32_t function_10d0(char * nptr) {
    // 0x10d0
    return atoi(nptr);
}

// Address range: 0x10e0 - 0x10e6
void function_10e0(int32_t status) {
    // 0x10e0
    exit(status);
}

// Address range: 0x10f0 - 0x10f6
void function_10f0(int64_t * d) {
    // 0x10f0
    __cxa_finalize(d);
}

// Address range: 0x1100 - 0x112b
int64_t entry_point(int64_t a1, int64_t a2, int64_t a3, int64_t a4) {
    // 0x1100
    int64_t v1;
    __libc_start_main(0x16fc, (int32_t)a4, (char **)&v1, (void (*)())0x1770, (void (*)())0x17d0, (void (*)())a3);
    __asm_hlt();
    // UNREACHABLE
}

// Address range: 0x1130 - 0x1159
int64_t function_1130(void) {
    // 0x1130
    return 0x4010;
}

// Address range: 0x1160 - 0x1199
int64_t function_1160(void) {
    // 0x1160
    return 0;
}

// Address range: 0x11a0 - 0x11d9
int64_t function_11a0(void) {
    // 0x11a0
    if (g6 != 0) {
        // 0x11d8
        int64_t result; // rax
        return result;
    }
    if (*(int64_t *)0x3ff8 != 0) {
        // 0x11b7
        __cxa_finalize((int64_t *)*(int64_t *)0x4008);
    }
    // 0x11c3
    g6 = 1;
    return function_1130();
}

// Address range: 0x11e0 - 0x11e5
int64_t function_11e0(void) {
    // 0x11e0
    return function_1160();
}

// Address range: 0x11e5 - 0x11ff
int64_t function_11e5(void) {
    // 0x11e5
    puts("time out!");
    exit(-1);
    // UNREACHABLE
}

// Address range: 0x11ff - 0x1297
int64_t function_11ff(void) {
    // 0x11ff
    setvbuf(g4, NULL, 2, 0);
    setvbuf(g3, NULL, 2, 0);
    setvbuf(g5, NULL, 2, 0);
    signal(SIGALARM, 0x11e5);
    alarm(60);
    g10 = (char *)&g9;
    g11 = (char *)&g9;
    return (int64_t)&g9;
}

// Address range: 0x1297 - 0x1326
int64_t function_1297(int64_t * a1, int64_t a2) {
    int64_t v1 = (int64_t)a1; // 0x129f
    int64_t result; // 0x131d
    if ((int32_t)a2 <= 0) {
        // 0x1310
        result = a2 - 1 + v1;
        *(char *)result = 0;
        return result;
    }
    int64_t v2 = 0;
    while (true) {
        int64_t buf = v2 + v1; // 0x12b9
        if (read(0, (int64_t *)buf, 1) != 1) {
            // break -> 0x12d4
            break;
        }
        char * v3 = (char *)buf; // 0x12eb
        if (*v3 == 10) {
            // 0x12f2
            *v3 = 0;
            goto lab_0x1310;
        }
        int64_t v4 = v2 + 1;
        if (v4 >= 0x100000000 * a2 / 0x100000000) {
          lab_0x1310:
            // 0x1310
            result = a2 - 1 + v1;
            *(char *)result = 0;
            return result;
        }
        v2 = v4;
    }
    // 0x12d4
    exit(-1);
    // UNREACHABLE
}

// Address range: 0x1326 - 0x1370
int64_t function_1326(void) {
    int64_t v1 = __readfsqword(40); // 0x132e
    int64_t str; // bp-56
    function_1297(&str, 32);
    int32_t str_as_i = atoi((char *)&str); // 0x1355
    int64_t result; // 0x136f
    if (__readfsqword(40) == v1) {
        // 0x1326
        result = str_as_i;
    } else {
        // 0x1369
        __stack_chk_fail();
        result = &g12;
    }
    // 0x136e
    return result;
}

// Address range: 0x1370 - 0x13c1
int64_t function_1370(void) {
    // 0x1370
    puts("1. Create note");
    puts("2. Write content");
    puts("3. Show content");
    puts("4. Delete note");
    printf("Choice: ");
    return function_1326();
}

// Address range: 0x13c1 - 0x145a
int64_t function_13c1(void) {
    // 0x13c1
    if (g7 > 79) {
        // 0x13d4
        puts("Too many notes");
    }
    int64_t * mem = malloc(40); // 0x13e5
    int64_t v1 = (int64_t)mem; // 0x13e5
    printf("Title: ");
    function_1297(mem, 16);
    *(int64_t *)(v1 + 24) = (int64_t)&g9;
    *(int64_t *)(v1 + 16) = (int64_t)g10;
    *(int64_t *)((int64_t)g10 + 24) = v1;
    g10 = (char *)mem;
    g7 = &g8;
    return &g8;
}

// Address range: 0x145a - 0x14bc
int64_t function_145a(int64_t * str) {
    // 0x145a
    if (g11 == (char *)&g9) {
        // 0x14a9
        puts("No such a note with the title");
        // 0x14ba
        return 0;
    }
    int64_t result = (int64_t)g11; // 0x14a313
    char * str2 = g11;
    while (true) {
        // 0x1473
        if (strcmp((char *)(int64_t)str, str2) == 0) {
            // break -> 0x14ba
            break;
        }
        int64_t v1 = *(int64_t *)(result + 24); // 0x1494
        if (v1 == (int64_t)&g9) {
            // 0x14a9
            puts("No such a note with the title");
            // 0x14ba
            return 0;
        }
        result = v1;
        str2 = (char *)v1;
    }
    // 0x14ba
    return result;
}

// Address range: 0x14bc - 0x15ba
int64_t function_14bc(void) {
    int64_t v1 = __readfsqword(40); // 0x14c4
    printf("Title of note to write content: ");
    int64_t v2; // bp-40
    function_1297(&v2, 16);
    int64_t v3 = function_145a(&v2); // 0x14fc
    if (v3 != 0) {
        int64_t * v4 = (int64_t *)(v3 + 32); // 0x1514
        if (*v4 == 0) {
            // 0x152b
            printf("Size of content: ");
            int64_t v5 = function_1326(); // 0x1541
            int32_t size = v5; // 0x1546
            if (size > 80) {
                // 0x1555
                puts("Too big");
            } else {
                // 0x1563
                *v4 = (int64_t)malloc(size);
                printf("Content: ");
                function_1297((int64_t *)*v4, v5 & 0xffffffff);
            }
        } else {
            // 0x151d
            puts("You have already written content");
        }
    }
    // 0x15a4
    int64_t result; // 0x15b9
    if (__readfsqword(40) != v1) {
        // 0x15b3
        __stack_chk_fail();
        result = &g12;
    } else {
        result = 0;
    }
    // 0x15b8
    return result;
}

// Address range: 0x15ba - 0x1640
int64_t function_15ba(void) {
    int64_t v1 = __readfsqword(40); // 0x15c2
    printf("Title of note to show content: ");
    int64_t v2; // bp-40
    function_1297(&v2, 16);
    int64_t v3 = function_145a(&v2); // 0x15fa
    if (v3 != 0) {
        int64_t * str = (int64_t *)(v3 + 32); // 0x160e
        if (*str != 0) {
            // 0x1617
            puts((char *)*str);
        }
    }
    // 0x162a
    int64_t result; // 0x163f
    if (__readfsqword(40) != v1) {
        // 0x1639
        __stack_chk_fail();
        result = &g12;
    } else {
        result = 0;
    }
    // 0x163e
    return result;
}

// Address range: 0x1640 - 0x16fc
int64_t function_1640(void) {
    int64_t v1 = __readfsqword(40); // 0x1648
    printf("Title of note to delete: ");
    int64_t v2; // bp-40
    function_1297(&v2, 16);
    int64_t v3 = function_145a(&v2); // 0x1680
    if (v3 != 0) {
        int64_t * v4 = (int64_t *)(v3 + 16); // 0x1694
        int64_t * v5 = (int64_t *)(v3 + 24); // 0x169c
        *(int64_t *)(*v4 + 24) = *v5;
        *(int64_t *)(*v5 + 16) = *v4;
        free((int64_t *)*(int64_t *)(v3 + 32));
        free((int64_t *)v3);
        g7--;
    }
    // 0x16e6
    int64_t result; // 0x16fb
    if (__readfsqword(40) != v1) {
        // 0x16f5
        __stack_chk_fail();
        result = &g12;
    } else {
        result = 0;
    }
    // 0x16fa
    return result;
}

// Address range: 0x16fc - 0x176f
int64_t function_16fc(void) {
    while (true) {
        int32_t v1 = function_1370(); // 0x1714
        if (v1 == 2) {
            // 0x173d
            function_14bc();
            // continue -> 0x170a
            continue;
        }
        if (v1 > 2) {
            switch (v1) {
                case 3: {
                    // 0x1749
                    function_15ba();
                    // continue -> 0x170a
                    continue;
                }
                case 4: {
                    // 0x1755
                    function_1640();
                    // continue -> 0x170a
                    continue;
                }
            }
            // 0x1761
            puts("Invalid choice");
            // continue -> 0x170a
            continue;
        }
        if (v1 != 1) {
            // 0x1761
            puts("Invalid choice");
            // continue -> 0x170a
            continue;
        }
        // 0x1731
        function_13c1();
    }
}

// Address range: 0x1770 - 0x17cd
int64_t function_1770(int64_t a1, int64_t a2, int64_t a3) {
    int64_t result = function_1000(); // 0x1798
    if (((int64_t)&g2 - (int64_t)&g1) / 8 != 0) {
        int64_t v1 = 0; // 0x17b52
        while (v1 + 1 != ((int64_t)&g2 - (int64_t)&g1) / 8) {
            // 0x17a8
            v1++;
        }
    }
    // 0x17be
    return result;
}

// Address range: 0x17d0 - 0x17d1
int64_t function_17d0(void) {
    // 0x17d0
    int64_t result; // rax
    return result;
}

// Address range: 0x17d4 - 0x17dd
int64_t function_17d4(void) {
    // 0x17d4
    int64_t result; // rax
    return result;
}

// --------------- Dynamically Linked Functions ---------------

// void __cxa_finalize(void * d);
// void __gmon_start__(void);
// int __libc_start_main(int *(main)(int, char **, char **), int argc, char ** ubp_av, void(* init)(void), void(* fini)(void), void(* rtld_fini)(void), void(* stack_end));
// void __stack_chk_fail(void);
// unsigned int alarm(unsigned int seconds);
// int atoi(const char * nptr);
// void exit(int status);
// void free(void * ptr);
// void * malloc(size_t size);
// int printf(const char * restrict format, ...);
// int puts(const char * s);
// ssize_t read(int fd, void * buf, size_t nbytes);
// int setvbuf(FILE * restrict stream, char * restrict buf, int modes, size_t n);
// __sighandler_t signal(int sig, __sighandler_t handler);
// int strcmp(const char * s1, const char * s2);

// --------------------- Meta-Information ---------------------

// Detected compiler/packer: gcc (8.3.0)
// Detected functions: 33
// Decompilation date: 2019-08-01 16:29:41
