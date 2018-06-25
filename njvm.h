#include <stdbool.h>
#include <stdio.h>
#include "bigint/build/include/support.h"

#ifndef __NJVM_H_
#define __NJVM_H_

typedef struct {
    bool isObjRef;
    union {
        ObjRef objRef; /* used if isObjRef=TRUE */
        int number; /* used if isObjRef=FALSE */
    } u;
} StackSlot;

extern unsigned int pc;
extern ObjRef *stack_G;
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

#define CALL 26
#define RET 27
#define DROP 28
#define PUSHR 29
#define POPR 30

#define DUP 31

#define NEW 32
#define GETF 33
#define PUTF 34

#define NEWA 35
#define GETFA 36
#define PUTFA 37

#define GETSZ 38

#define PUSHN 39
#define REFEQ 40
#define REFNE 41

#endif