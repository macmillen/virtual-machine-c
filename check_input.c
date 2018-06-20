#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "njvm.h"
#include "stack.h"

void checkInput(void) {
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

    // READ NUMBER OF INSTRUCTIONS
    if(fread(&numberOfInstructions, sizeof (unsigned int), 1, f) != 1) {
        printf("Overflow");
        exit(99);
    }
    memory = (int*) malloc(numberOfInstructions * 4);
    breakpoints = (int*) calloc(numberOfInstructions, sizeof(int));
    
    // READ NUMBER OF VARIABLES FOR STATIC AREA
    if(fread(&stackS_G, sizeof (unsigned int), 1, f) != 1) {
        printf("Overflow");
        exit(99);
    }
    stack_G = (ObjRef*) malloc(stackS_G * 4);

    // READ REST OF THE FILE (INSTRUCTIONS)
    if(fread(memory, sizeof (int), numberOfInstructions, f) != numberOfInstructions) {
        printf("Overflow");
        exit(99);
    }
    fclose(f);
}