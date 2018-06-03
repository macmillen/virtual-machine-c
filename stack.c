#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "njvm.h"

int op;
int val;
const int stackS = 10000;
int stack[10000];
int sp = 0;
int fp = 0;
int retVal;

int stackH_G = 0;

int *breakpoints;

bool running = false;

void push(int v) {
    if(sp < 9999) {
        stack[sp] = v;
        sp++;
    } else {
        exit(-1);
    }
}

int pop(void) {
    if(sp > 0) {
        sp--;
        return stack[sp];
    } else {
        exit(-1);
    }
}

int halt(void) {
    return 0;
}

void pushc(void) {
    push(val);
}

void add(void) {
    int val1 = pop();
    int val2 = pop();
    push(val2 + val1);
}

void sub(void) {
    int val1 = pop();
    int val2 = pop();
    push(val2 - val1);
}

void mul(void) {
    int val1 = pop();
    int val2 = pop();
    push(val2 * val1);
}

void div_(void) {
    int val1 = pop();
    int val2 = pop();
    if(val1 != 0) {
        push(val2 / val1);
    } else {
        exit(-1);
    }
}

void mod(void) {
    int val1 = pop();
    int val2 = pop();
    if(val1 != 0) {
        push(val2 % val1);
    } else {
        exit(-1);
    }
}

void rdint(void) {
    printf("Enter Int: ");
    int val;
    scanf("%d", &val);
    push(val);
}

void wrint(void) {
    int val = pop();
    printf("%d", val);
}

void rdchr(void) {
    printf("Enter Char: ");
    char val = getchar();
    push(val);
}

void wrchr(void) {
    char val = pop();
    printf("%c", val);
}

void pushg(void) {
    push(stack_G[val]);
}

void popg(void) {
    stack_G[val] = pop();
}

void asf(void) {
    push(fp);
    fp = sp;
    sp = sp + val;
}

void rsf(void) {
    sp = fp;
    fp = pop();
}

void pushl(void) {
    push(stack[fp + val]);
}

void popl(void) {
    int v = pop();
    stack[fp + val] = v;
}

void eq(void) {
    int n1 = pop();
    int n2 = pop();
    push(n2 == n1);
}

void ne(void) {
    int n1 = pop();
    int n2 = pop();
    push(n2 != n1);
}

void lt(void) {
    int n1 = pop();
    int n2 = pop();
    push(n2 < n1);
}

void le(void) {
    int n1 = pop();
    int n2 = pop();
    push(n2 <= n1);
}

void gt(void) {
    int n1 = pop();
    int n2 = pop();
    push(n2 > n1);
}

void ge(void) {
    int n1 = pop();
    int n2 = pop();
    push(n2 >= n1);
}

void jmp(void) {
    pc = val;
}

void brf(void) {
    int b = pop();
    if(!b) {
        pc = val;
    }
}

void brt(void) {
    int b = pop();
    if(b) {
        pc = val;
    }
}

void call(void) {
    push(pc);
    jmp();
}

void ret(void) {
    pc = pop();
}

void drop(void) {
    for(int i = 0; i < val; i++) {
        pop();
    }
}

void pushr(void) {
    push(retVal);
}

void popr(void) {
    retVal = pop();
}

void dup(void) {
    int v = pop();
    push(v);
    push(v);
}


void listProgram(int pc, bool all) {
    int ir = 0;
    int op = 0;
    int val = 0;
    do {
        ir = memory[pc];
        pc++;

        op = ir >> 24;
        val = SIGN_EXTEND(ir & 0x00FFFFFF);
        
        switch(op) {    
            case HALT:  printf("%03d:\tHALT\t\n",  pc);      return;
            case PUSHC: printf("%03d:\tPUSHC\t%d", pc, val); break;
            case ADD:   printf("%03d:\tADD\t",     pc);      break;
            case SUB:   printf("%03d:\tSUB\t",     pc);      break;
            case MUL:   printf("%03d:\tMUL\t",     pc);      break;
            case DIV:   printf("%03d:\tDIV\t",     pc);      break;
            case MOD:   printf("%03d:\tMOD\t",     pc);      break;
            case RDINT: printf("%03d:\tRDINT\t",   pc);      break;
            case WRINT: printf("%03d:\tWRINT\t",   pc);      break;
            case RDCHR: printf("%03d:\tRDCHR\t",   pc);      break;
            case WRCHR: printf("%03d:\tWRCHR\t",   pc);      break;
            case PUSHG: printf("%03d:\tPUSHG\t%d", pc, val); break;
            case POPG:  printf("%03d:\tPOPG\t%d",  pc, val); break;
            case ASF:   printf("%03d:\tASF\t%d",   pc, val); break;
            case RSF:   printf("%03d:\tRSF\t",     pc);      break;
            case PUSHL: printf("%03d:\tPUSHL\t%d", pc, val); break;
            case POPL:  printf("%03d:\tPOPL\t%d",  pc, val); break;
            case EQ:    printf("%03d:\tEQ\t",      pc);      break;
            case NE:    printf("%03d:\tNE\t",      pc);      break;
            case LT:    printf("%03d:\tLT\t",      pc);      break;
            case LE:    printf("%03d:\tLE\t",      pc);      break;
            case GT:    printf("%03d:\tGT\t",      pc);      break;
            case GE:    printf("%03d:\tGE\t",      pc);      break;
            case JMP:   printf("%03d:\tJMP\t%d",   pc, val); break;
            case BRF:   printf("%03d:\tBRF\t%d",   pc, val); break;
            case BRT:   printf("%03d:\tBRT\t%d",   pc, val); break;
            case CALL:  printf("%03d:\tCALL\t%d",  pc, val); break;
            case RET:   printf("%03d:\tRET\t",     pc);      break;
            case DROP:  printf("%03d:\tDROP\t%d",  pc, val); break;
            case PUSHR: printf("%03d:\tPUSHR\t",   pc);      break;
            case POPR:  printf("%03d:\tPOPR\t",    pc);      break;
            case DUP:   printf("%03d:\tDUP\t",     pc);      break;
        }
        printf("\n");
        if(!all) return;
    } while(1);
}

int execute(int ir) {
    op = ir >> 24;
    val = SIGN_EXTEND(IMMEDIATE(ir));

    if(debug) {
        char input[100];
        bool breakpointReached = breakpoints[pc - 1];
        if(!running || breakpointReached) {
            if(breakpointReached) {
                running = false;
            }
            while(1) {
                listProgram(pc - 1, false);
                printf("DEBUG: inspect, list, breakpoint, step, run, quit?\n");
                scanf("%s", input);
                if(!strcmp(input, "inspect")) {
                    printf("DEBUG [inspect]: stack, data?\n");
                    char in[100];
                    scanf("%s", in);
                    if(!strcmp(in, "stack")) {
                        for(int i = sp; i >= 0; i--) {
                            if(sp == fp) {
                                printf("sp, fp\t--->\t%04d:\txxxx\n", i);
                            } else if(i == sp) {
                                printf("sp\t--->\t%04d:\txxxx\n", i);
                            } else if(i == fp) {
                                printf("fp\t--->\t%04d:\t%d\n", i, stack[i]);
                            } else {
                                printf("\t\t%04d:\t%d\n", i, stack[i]);
                            }
                        }
                        printf("                --- bottom of stack ---\n");
                    } else if(!strcmp(in, "data")) {
                        for(int i = 0; i < stackS_G; i++) {
                            printf("data[%04d]:\t%d\n", i, stack_G[i]);
                        }
                        printf("        --- end of data ---\n");
                    }
                    continue;
                } else if(!strcmp(input, "list")) {
                    listProgram(0, true);
                    printf("        --- end of code ---\n");
                    continue;
                } else if(!strcmp(input, "breakpoint")) {
                    printf("DEBUG [breakpoint]: cleared\n");
                    printf("DEBUG [breakpoint]: address to set, -1 to clear, <ret> for no change?\n");
                    running = false;
                    int pos = 0;
                    scanf("%d", &pos);
                    breakpoints[pos - 1] = 1;
                    printf("DEBUG [breakpoint]: now set at %d\n", pos - 1);
                    continue;
                } else if(!strcmp(input, "step")) {
                    // do nothing
                } else if(!strcmp(input, "run")) {
                    running = true;
                } else if(!strcmp(input, "quit")) {
                    return 0;
                } else {
                    continue;
                }
                break;
            }
        }
    }

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
        case PUSHG: pushg(); break;
        case POPG:  popg();  break;
        case ASF:   asf();   break;
        case RSF:   rsf();   break;
        case PUSHL: pushl(); break;
        case POPL:  popl();  break;
        case EQ:    eq();    break;
        case NE:    ne();    break;
        case LT:    lt();    break;
        case LE:    le();    break;
        case GT:    gt();    break;
        case GE:    ge();    break;
        case JMP:   jmp();   break;
        case BRF:   brf();   break;
        case BRT:   brt();   break;
        case CALL:  call();  break;
        case RET:   ret();   break;
        case DROP:  drop();  break;
        case PUSHR: pushr(); break;
        case POPR:  popr();  break;
        case DUP:   dup();   break;
    }

    return 1; 
}
