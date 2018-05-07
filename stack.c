#include <stdio.h>
#include <stdlib.h>
#include "njvm.h"

int op;
int val;
int stack[1000];
int stackSize = 0;

void push(int v) {
    if(stackSize < 999) {
        stack[stackSize] = v;
        stackSize++;
    } else {
        exit(-1);
    }
}

int pop() {
    if(stackSize > 0) {
        stackSize--;
        return stack[stackSize];
    } else {
        exit(-1);
    }
}

int halt() {
    return 0;
}

void pushc() {
    push(val);
}

void add() {
    int val1 = pop();
    int val2 = pop();
    push(val2 + val1);
}

void sub() {
    int val1 = pop();
    int val2 = pop();
    push(val2 - val1);
}

void mul() {
    int val1 = pop();
    int val2 = pop();
    push(val2 * val1);
}

void div_() {
    int val1 = pop();
    int val2 = pop();
    if(val1 != 0) {
        push(val2 / val1);
    } else {
        exit(-1);
    }
}

void mod() {
    int val1 = pop();
    int val2 = pop();
    if(val1 != 0) {
        push(val2 % val1);
    } else {
        exit(-1);
    }
}

void rdint() {
    int val;
    scanf("%d", &val);
    push(val);
}

void wrint() {
    int val = pop();
    printf("%d", val);
}

void rdchr() {
    char val = getchar();
    push(val);
}

void wrchr() {
    char val = pop();
    printf("%c", val);
}

int execute(int ir) {

    op = ir >> 24;
    val = ir & 0x00FFFFFF;

    switch(op) {
        case HALT:  printf("\n%03d:\tHALT\t",    pc);         return halt();
        case PUSHC: printf("\n%03d:\tPUSHC\t%d", pc, val);    pushc(); break;
        case ADD:   printf("\n%03d:\tADD\t",     pc);         add();   break;
        case SUB:   printf("\n%03d:\tSUB\t",     pc);         sub();   break;
        case MUL:   printf("\n%03d:\tMUL\t",     pc);         mul();   break;
        case DIV:   printf("\n%03d:\tDIV\t",     pc);         div_();  break;
        case MOD:   printf("\n%03d:\tMOD\t",     pc);         mod();   break;
        case RDINT: printf("\n%03d:\tRDINT\t",   pc);         rdint(); break;
        case WRINT: printf("\n%03d:\tWRINT\t",   pc);         wrint(); break;
        case RDCHR: printf("\n%03d:\tRDCHR\t",   pc);         rdchr(); break;
        case WRCHR: printf("\n%03d:\tWRCHR\t",   pc);         wrchr(); break;
    }
    return 1; 
}