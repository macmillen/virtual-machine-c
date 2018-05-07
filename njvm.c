#include <stdio.h>
#include <string.h>
#include "njvm.h"
#include "stack.h"

// TODOS
// vorzeichen beachten
// newline nicht mit ausgeben
// muss bei 000 anfangen?

char version[] = "0";

unsigned int *memory;
unsigned int ir;

unsigned int pc;

unsigned int code1[] = {
    (PUSHC << 24) | IMMEDIATE(3),
    (PUSHC << 24) | IMMEDIATE(4), 
    (ADD << 24),
    (PUSHC << 24) | IMMEDIATE(10),
    (PUSHC << 24) | IMMEDIATE(6),
    (SUB << 24),
    (MUL << 24),
    (WRINT << 24),
    (PUSHC << 24) | IMMEDIATE(10),
    (WRCHR << 24),
    (HALT << 24)
};

unsigned int code2[] = {
    (PUSHC << 24) | IMMEDIATE(-2), 
    (RDINT << 24), 
    (MUL << 24),
    (PUSHC << 24) | IMMEDIATE(3),
    (ADD << 24),
    (WRINT << 24),
    (PUSHC << 24) | IMMEDIATE('\n'),
    (WRCHR << 24),
    (HALT << 24)
};

unsigned int code3[] = {
    (RDCHR << 24),
	(WRINT << 24),
	(PUSHC << 24) | IMMEDIATE('\n'),
	(WRCHR << 24),
	(HALT << 24)
};

int main(int argc, char *argv[]) {
    printf("\n");
    for(int i = 0; i < argc; ++i) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    printf("\n");

    for(int i = 0; i < argc; i++) {
        if(!strcmp(argv[i], "--help")) {
            printf("usage: ./njvm [option] [option] ...\n");
            printf("\t--version        show version and exit\n");
            printf("\t--help           show this help and exit\n");
            return 0;
        } else if(!strcmp(argv[i], "--version")) {
            printf("Ninja Virtual Machine version %s (%s %s)\n", version, __DATE__, __TIME__);
            return 0;
        } else if(!strcmp(argv[i], "--prog1")) {
            memory = code1;
        } else if(!strcmp(argv[i], "--prog2")) {
            memory = code2;
        } else if(!strcmp(argv[i], "--prog3")) {
            memory = code3;
        } 
    }

    printf("\nNinja Virtual Machine started\n");

    do {
        ir = memory[pc];
        pc++;
    } while(execute(ir));

    printf("Ninja Virtual Machine stopped\n");
}
