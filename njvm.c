#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "njvm.h"
#include "stack.h"
#include "check_input.h"

// TODOS
// Frage: support.c nicht includen?
// cloning object / duplicate()

unsigned int version = 6;
unsigned int versionBin;
unsigned int numberOfInstructions;
unsigned int stackS_G;

char format[4];

ObjRef *stack_G;
int *memory;
unsigned int feld[10];
unsigned int ir;

unsigned int pc;

FILE *f = NULL;
char *fileName;

bool debug = false;

int main(int argc, char *argv[]) {
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
            fileName = (char*) malloc(strlen(argv[i]));
            fileName = argv[i];
        }
    }
    
    checkInput();

    if(debug) {
        printf("DEBUG: file '%s' loaded (code size = %d, data size = %d)\n", fileName, numberOfInstructions, stackS_G);
    }
    
    printf("Ninja Virtual Machine started\n");

    pc = 0;
    do {
        ir = memory[pc];
        pc++;
    } while(execute(ir));

    printf("Ninja Virtual Machine stopped\n");
}
