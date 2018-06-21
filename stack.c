#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "njvm.h"
#include "bigint/build/include/bigint.h"
#include "bigint/build/include/support.h"

int op;
int val;
const int stackS = 10000;
StackSlot stack[10000];
int sp = 0;
int fp = 0;
ObjRef retVal;

int stackH_G = 0;

int *breakpoints;

bool running = false;

void pusha(int v) {
    if(sp < stackS - 1) {
        stack[sp].isObjRef = false;
        stack[sp].u.number = v;
        sp++;
    } else {
        exit(-1);
    }
}

void pusho(ObjRef objRef) {
    if(sp < stackS - 1) {
        stack[sp].isObjRef = true;
        stack[sp].u.objRef = objRef;
        sp++;
    } else {
        exit(-1);
    }
}

int popa(void) {
    if(sp > 0 && !stack[sp - 1].isObjRef) {
        sp--;
        return stack[sp].u.number;
    } else {
        exit(-1);
    }
}

ObjRef popo(void) {
    if(sp > 0 && stack[sp - 1].isObjRef) {
        sp--;
        return stack[sp].u.objRef;
    } else {
        exit(-1);
    }
}

int halt(void) {
    return 0;
}

void pushc(int v) {
    bigFromInt(v);
    pusho(bip.res);
}

void add(void) {
    bip.op2 = popo();
    bip.op1 = popo();
    bigAdd();
    pusho(bip.res);
}

void sub(void) {
    bip.op2 = popo();
    bip.op1 = popo();
    bigSub();
    pusho(bip.res);
}

void mul(void) {
    bip.op2 = popo();
    bip.op1 = popo();
    bigMul();
    pusho(bip.res);
}

void div_(void) {
    bip.op2 = popo();
    bip.op1 = popo();
    bigDiv();
    pusho(bip.res);
}

void mod(void) {
    bip.op2 = popo();
    bip.op1 = popo();
    bigDiv();
    pusho(bip.rem);
}

void rdint(void) {
    bigRead(stdin);
    pusho(bip.res);
}

void wrint(void) {
    bip.op1 = popo();
    bigPrint(stdout);
}

void rdchr(void) {
    char val = getchar();
    pushc(val);
}

void wrchr(void) {
    bip.op1 = popo();
    char res = bigToInt();
    printf("%c", res);
}

void pushg(void) {
    pusho(stack_G[val]);
}

void popg(void) {
    stack_G[val] = popo();
}

void asf(void) {
    pusha(fp);
    fp = sp;
    sp = sp + val;
}

void rsf(void) {
    sp = fp;
    fp = popa();
}

void pushl(void) {
    pusho(stack[fp + val].u.objRef);
}

void popl(void) {
    ObjRef v = popo();
    stack[fp + val].isObjRef = true;
    stack[fp + val].u.objRef = v;
}

void eq(void) {
    bip.op2 = popo();
    bip.op1 = popo();
    int res = bigCmp();
    pushc(res == 0);
}

void ne(void) {
    bip.op2 = popo();
    bip.op1 = popo();
    int res = bigCmp();
    pushc(res != 0);
}

void lt(void) {
    bip.op2 = popo();
    bip.op1 = popo();
    int res = bigCmp();
    pushc(res < 0);
}

void le(void) {
    bip.op2 = popo();
    bip.op1 = popo();
    int res = bigCmp();
    pushc(res < 0 || res == 0);
}

void gt(void) {
    bip.op2 = popo();
    bip.op1 = popo();
    int res = bigCmp();
    pushc(res > 0);
}

void ge(void) {
    bip.op2 = popo();
    bip.op1 = popo();
    int res = bigCmp();
    pushc(res > 0 || res == 0);
}

void jmp(void) {
    pc = val;
}

void brf(void) {
    bip.op1 = popo();
    int b = bigToInt();
    if(!b) {
        pc = val;
    }
}

void brt(void) {
    bip.op1 = popo();
    int b = bigToInt();
    if(b) {
        pc = val;
    }
}

void call(void) {
    pusha(pc);
    jmp();
}

void ret(void) {
    pc = popa();
}

void drop(void) {
    for(int i = 0; i < val; i++) {
        popo();
    }
}

void pushr(void) {
    pusho(retVal);
}

void popr(void) {
    ObjRef v = popo();
    retVal = v;
}

void dup(void) { //TODO: cloning object
    ObjRef v = popo();
    pusho(v);
    pusho(v);
}

void listProgram(int pc, bool all) {
    int ir = 0;
    int op = 0;
    int val = 0;
    do {
        ir = memory[pc];

        op = ir >> 24;
        val = SIGN_EXTEND(ir & 0x00FFFFFF);
        
        switch(op) {    
            case HALT:  printf("%04d:\tHALT\t\n",  pc);      return;
            case PUSHC: printf("%04d:\tPUSHC\t%d", pc, val); break;
            case ADD:   printf("%04d:\tADD\t",     pc);      break;
            case SUB:   printf("%04d:\tSUB\t",     pc);      break;
            case MUL:   printf("%04d:\tMUL\t",     pc);      break;
            case DIV:   printf("%04d:\tDIV\t",     pc);      break;
            case MOD:   printf("%04d:\tMOD\t",     pc);      break;
            case RDINT: printf("%04d:\tRDINT\t",   pc);      break;
            case WRINT: printf("%04d:\tWRINT\t",   pc);      break;
            case RDCHR: printf("%04d:\tRDCHR\t",   pc);      break;
            case WRCHR: printf("%04d:\tWRCHR\t",   pc);      break;
            case PUSHG: printf("%04d:\tPUSHG\t%d", pc, val); break;
            case POPG:  printf("%04d:\tPOPG\t%d",  pc, val); break;
            case ASF:   printf("%04d:\tASF\t%d",   pc, val); break;
            case RSF:   printf("%04d:\tRSF\t",     pc);      break;
            case PUSHL: printf("%04d:\tPUSHL\t%d", pc, val); break;
            case POPL:  printf("%04d:\tPOPL\t%d",  pc, val); break;
            case EQ:    printf("%04d:\tEQ\t",      pc);      break;
            case NE:    printf("%04d:\tNE\t",      pc);      break;
            case LT:    printf("%04d:\tLT\t",      pc);      break;
            case LE:    printf("%04d:\tLE\t",      pc);      break;
            case GT:    printf("%04d:\tGT\t",      pc);      break;
            case GE:    printf("%04d:\tGE\t",      pc);      break;
            case JMP:   printf("%04d:\tJMP\t%d",   pc, val); break;
            case BRF:   printf("%04d:\tBRF\t%d",   pc, val); break;
            case BRT:   printf("%04d:\tBRT\t%d",   pc, val); break;
            case CALL:  printf("%04d:\tCALL\t%d",  pc, val); break;
            case RET:   printf("%04d:\tRET\t",     pc);      break;
            case DROP:  printf("%04d:\tDROP\t%d",  pc, val); break;
            case PUSHR: printf("%04d:\tPUSHR\t",   pc);      break;
            case POPR:  printf("%04d:\tPOPR\t",    pc);      break;
            case DUP:   printf("%04d:\tDUP\t",     pc);      break;
        }
        pc++;
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
                if(!strncmp(input, "inspect", 1)) {
                    printf("DEBUG [inspect]: stack, data, object?\n");
                    char in[100];
                    scanf("%s", in);
                    if(!strncmp(in, "stack", 1)) {
                        for(int i = sp; i >= 0; i--) {
                            bool isObjRef = stack[i].isObjRef;
                            if(i == sp && sp == fp) {
                                printf("sp, fp\t--->\t%04d:\t(xxxxxx) xxxxxx\n", i);
                            } else if(i == sp) {
                                printf("sp\t--->\t%04d:\t(xxxxxx) xxxxxx\n", i);
                            } else if(i == fp) {
                                if(isObjRef) {
                                    printf("fp\t--->\t%04d:\t(%s) %p\n", i, "objref", (void*)stack[i].u.objRef);
                                } else {
                                    printf("fp\t--->\t%04d:\t(%s) %d\n", i, "number", stack[i].u.number);
                                }
                            } else {
                                if(isObjRef) {
                                    printf("\t\t%04d:\t(%s) %p\n", i, "objref", (void*)stack[i].u.objRef);
                                } else {
                                    printf("\t\t%04d:\t(%s) %d\n", i, "number", stack[i].u.number);
                                }
                            }
                        }
                        printf("                --- bottom of stack ---\n");
                    } else if(!strncmp(in, "data", 1)) {
                        for(int i = 0; i < stackS_G; i++) {
                            printf("data[%04d]:\t%s %p\n", i, "(objref)", (void*)stack_G[i]);
                        }
                        printf("        --- end of data ---\n");
                    } else if(!strncmp(in, "object", 1)) {
                        printf("object reference?\n");
                        char ref[30];
                        scanf("%s", ref);
                        long unsigned int nux;
                        sscanf(ref, "%lx", &nux);
                        for(int y = 0; y < stackS_G; y++) {
                            if((long unsigned int)*(stack_G + y) == nux) {
                                printf("value = %d\n", (int)(stack_G[y] -> data[0]));
                            }
                        }
                    }
                    continue;
                } else if(!strncmp(input, "list", 1)) {
                    listProgram(0, true);
                    printf("        --- end of code ---\n");
                    continue;
                } else if(!strncmp(input, "breakpoint", 1)) {
                    printf("DEBUG [breakpoint]: address to set, -1 to clear\n");
                    running = false;
                    int pos = 0;
                    scanf("%d", &pos);
                    if(pos < numberOfInstructions && pos >= 0) {
                        breakpoints[pos] = 1;
                        printf("DEBUG [breakpoint]: now set at %d\n", pos - 1);
                    }
                    if(pos == -1) {
                        for(int i = 0; i < numberOfInstructions; i++) {
                            breakpoints[i] = 0;
                        }
                    }
                    continue;
                } else if(!strncmp(input, "step", 1)) {
                    // do nothing
                } else if(!strncmp(input, "run", 1)) {
                    running = true;
                } else if(!strncmp(input, "quit", 1)) {
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
        case PUSHC: pushc(val); break;
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
