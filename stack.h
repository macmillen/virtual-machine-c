#include <stdbool.h>

#ifndef __STACK_H_
#define __STACK_H_

#define MSB (1 << (8 * sizeof(unsigned int) - 1))
#define IS_PRIM(objRef) ((( objRef)->size & MSB) == 0)
#define GET_SIZE(objRef) ((objRef)->size & ~MSB)
#define GET_REFS(objRef) ((ObjRef *)(objRef)->data)

void pushn(void);
void listProgram(int pc, bool all);
int execute(int ir);

int *breakpoints;

#endif