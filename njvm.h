#include <stdbool.h>
#include <stdio.h>

#ifndef __NJVM_H_
#define __NJVM_H_

extern unsigned int pc;
extern unsigned int *stack_G;
extern unsigned int stackS_G;
extern unsigned int ir;
extern bool debug;
extern FILE *f;
extern unsigned int numberOfInstructions;
extern unsigned int version;
extern unsigned int versionBin;
extern char format[4];
extern int *memory;

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

#define EQ 17
#define NE 18
#define LT 19
#define LE 20
#define GT 21
#define GE 22

#define JMP 23
#define BRF 24
#define BRT 25

#endif