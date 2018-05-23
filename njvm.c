#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "njvm.h"
#include "stack.h"

// TODOS
// muss bei 000 anfangen?

unsigned int version = 2;
unsigned int versionBin;
unsigned int numberOfInstructions;
unsigned int numberOfGlobalVars;

char format[4];

unsigned int *globalVars;
int *memory;
unsigned int feld[10];
unsigned int ir;

unsigned int pc;

FILE *f;

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
            printf("Ninja Virtual Machine version %d (%s %s)\n", version, __DATE__, __TIME__);
            return 0;
        }
    }

    f = fopen("prog1.bin", "r");
    if(f == NULL) {
        printf("Could not open file");
        exit(99);
    }

    // READ FORMAT
    if(fread (&format, sizeof (char), 4, f) != 4) {
        printf("Overflow");
        exit(99);
    }
    if(strncmp("NJBF", format, 4)) {
        printf("Wrong binary format");
        exit(99);
    }

    // READ VERSION
    if(fread (&versionBin, sizeof (unsigned int), 1, f) != 1) {
        printf("Overflow");
        exit(99);
    }
    if(version != versionBin) {
        printf("Version is not identical");
        exit(99);
    }
    printf("%s",format);
    printf("\nNinja Virtual Machine started\n");

    // READ NUMBER OF INSTRUCTIONS
    if(fread(&numberOfInstructions, sizeof (unsigned int), 1, f) != 1) {
        printf("Overflow");
        exit(99);
    }
    memory = (int*) malloc(numberOfInstructions * 4);

    // READ NUMBER OF VARIABLES FOR STATIC AREA
    if(fread(&numberOfGlobalVars, sizeof (unsigned int), 1, f) != 1) {
        printf("Overflow");
        exit(99);
    }
    globalVars = (unsigned int*) malloc(numberOfGlobalVars * 4);

    // READ REST OF THE FILE (INSTRUCTIONS)
    if(fread(memory, sizeof (int), numberOfInstructions, f) != numberOfInstructions) {
        printf("Overflow");
        exit(99);
    }

    do {
        ir = memory[pc];
        pc++;
    } while(listProgram(ir));

    pc = 0;
    do {
        ir = memory[pc];
        pc++;
    } while(execute(ir));

    printf("Ninja Virtual Machine stopped\n");
}
