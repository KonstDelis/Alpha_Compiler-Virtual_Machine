#include <stdio.h>
#include <stdlib.h>

#ifndef UTILS_H
#define UTILS_H

struct alpha_token_t* alpha(void *yval, FILE* in);

void red () ;
void yellow () ;
void reset ();

void runtimeError(char* msg, unsigned int lineno);

void check_malloc(void* ptr, char* errmsg);
#endif