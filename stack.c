#include <stdio.h>
#include <stdlib.h>
#include "njvm.h"

int op;
int val;
const int stackS = 10000;
int stack[10000];
int stackH = 0;

int stackH_G = 0;

void push(int v) {
    if(stackH < 9999) {
        stack[stackH] = v;
        stackH++;
    } else {
        exit(-1);
    }
}

int pop() {
    if(stackH > 0) {
        stackH--;
        return stack[stackH];
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
    printf("Enter Int: ");
    int val;
    scanf("%d", &val);
    push(val);
}

void wrint() {
    int val = pop();
    printf("%d", val);
}

void rdchr() {
    printf("Enter Char: ");
    char val = getchar();
    push(val);
}

void wrchr() {
    char val = pop();
    printf("%c", val);
}

void pushg() {
    if(stackH_G < stackS_G) {
        stack_G[stackH_G] = val;
        stackH_G++;
    } else {
        exit(-1);
    }
}

int popg() {
    if(stackH_G > 0) {
        stackH_G--;
        return stack_G[stackH_G];
    } else {
        exit(-1);
    }
}

int execute(int ir) {
    op = ir >> 24;
    val = SIGN_EXTEND(IMMEDIATE(ir));

    switch(op) {
        case HALT:  return halt();
        case PUSHC: pushc(); break;
        case ADD:   add();   break;
        case SUB:   sub();   break;
        case MUL:   mul();   break;
        case DIV:   div_();  break;
        case MOD:   mod();   break;
        case RDINT: rdint(); break;
        case WRINT: wrint(); break;
        case RDCHR: rdchr(); break;
        case WRCHR: wrchr(); break;
    }
    return 1; 
}

int listProgram(int ir) {
    op = ir >> 24;
    val = SIGN_EXTEND(ir & 0x00FFFFFF);
    
    switch(op) {    
        case HALT:  printf("\n%03d:\tHALT\t",    pc);       printf("\n"); return 0;
        case PUSHC: printf("\n%03d:\tPUSHC\t%d", pc, val);  break;
        case ADD:   printf("\n%03d:\tADD\t",     pc);       break;
        case SUB:   printf("\n%03d:\tSUB\t",     pc);       break;
        case MUL:   printf("\n%03d:\tMUL\t",     pc);       break;
        case DIV:   printf("\n%03d:\tDIV\t",     pc);       break;
        case MOD:   printf("\n%03d:\tMOD\t",     pc);       break;
        case RDINT: printf("\n%03d:\tRDINT\t",   pc);       break;
        case WRINT: printf("\n%03d:\tWRINT\t",   pc);       break;
        case RDCHR: printf("\n%03d:\tRDCHR\t",   pc);       break;
        case WRCHR: printf("\n%03d:\tWRCHR\t",   pc);       break;
        case PUSHG: printf("\n%03d:\tPUSHG\t",   pc);       break;
        case POPG:  printf("\n%03d:\tPOPG\t",    pc);       break;
        case ASF:   printf("\n%03d:\tASF\t",     pc);       break;
        case RSF:   printf("\n%03d:\tRSF\t",     pc);       break;
        case PUSHL: printf("\n%03d:\tPUSHL\t",   pc);       break;
        case POPL:  printf("\n%03d:\tPOPL\t",    pc);       break;
    }
    return 1;
}