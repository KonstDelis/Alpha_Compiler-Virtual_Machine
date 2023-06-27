#include <stdlib.h>

#ifndef FUNC_STACK_H
#define FUNC_STACK_H

struct function_stack{
    int size;
    struct func_def_info* top;
};

struct func_def_info {
    unsigned int next_scope_offset;
    int def_scope;
    struct func_def_info *prev;
};

struct function_stack* init_function_stack();

void free_stack(struct function_stack* s);

void func_def(struct function_stack *stack, int def_scope, unsigned int next_scope_offset);

struct func_def_info* exit_func_def(struct function_stack* s);
#endif