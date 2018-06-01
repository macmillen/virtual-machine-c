#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "njvm.h"
#include "stack.h"

// TODOS
// muss bei 000 anfangen?

unsigned int version = 3;
unsigned int versionBin;
unsigned int numberOfInstructions;
unsigned int stackS_G;

char format[4];

unsigned int *stack_G;
int *memory;
unsigned int feld[10];
unsigned int ir;

unsigned int pc;

FILE *f;
char *file;

bool debug = false;

int main(int argc, char *argv[]) {
    printf("\n");
    /*
    for(int i = 0; i < argc; ++i) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    printf("\n");
    */
    for(int i = 0; i < argc; i++) {
        if(!strcmp(argv[i], "--help")) {
            printf("Usage: ./njvm [options] <code file>\n");
            printf("Options:\n");
            printf("\t--debug          start virtual machine in debug mode\n");
            printf("\t--version        show version and exit\n");
            printf("\t--help           show this help and exit\n");
            return 0;
        } else if(!strcmp(argv[i], "--version")) {
            printf("Ninja Virtual Machine version %d (%s %s)\n", version, __DATE__, __TIME__);
            return 0;
        } else if(!strcmp(argv[i], "--debug")) {
            debug = true;
        } else {
            f = fopen(argv[i], "r");
            if(debug) {
                printf("DEBUG: file '../programs/prog6.bin' loaded (code size = 27, data size = 2)");
            }
        }
    }
    
    checkInput();

    pc = 0;
    do {
        ir = memory[pc];
        pc++;
    } while(execute(ir));

    printf("Ninja Virtual Machine stopped\n");
    getchar();
}
