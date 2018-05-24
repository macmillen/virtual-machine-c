#ifndef __NJVM_H_
#define __NJVM_H_

extern unsigned int pc;
extern unsigned int *stack_G;
extern unsigned int stackS_G;

#define IMMEDIATE(x) ((x) & 0x00FFFFFF)
#define SIGN_EXTEND(i) ((i) & 0x00800000 ? (i) | 0xFF000000 : (i))

#define STACK 0
#define GLOBAL_STACK 1
#define LOCAL_STACK 2

#define HALT 0

#define PUSHC 1

#define ADD 2
#define SUB 3
#define MUL 4
#define DIV 5
#define MOD 6

#define RDINT 7
#define WRINT 8
#define RDCHR 9
#define WRCHR 10

#define PUSHG 11
#define POPG 12

#define ASF 13
#define RSF 14
#define PUSHL 15
#define POPL 16

#endif