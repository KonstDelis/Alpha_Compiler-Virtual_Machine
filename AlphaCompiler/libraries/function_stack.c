#include <stdio.h>
#include <stdlib.h>
#include "function_stack.h"

struct function_stack* init_function_stack(){
    struct function_stack* rt = malloc(sizeof(struct function_stack));
    if(rt==NULL)fprintf(stderr, "Error: memory allocation failed\n");

    rt->size=0;
    struct func_def_info* def = (struct func_def_info*)malloc(sizeof(struct func_def_info));
    def->next_scope_offset = 0;
    def->prev = NULL;
    rt->top = def;
    rt->size++;
    return rt;
}

void func_def(struct function_stack *stack, int def_scope, unsigned int next_scope_offset){
    struct func_def_info* new_func = (struct func_def_info*)malloc(sizeof(struct func_def_info));
    new_func->next_scope_offset = next_scope_offset;
    new_func->prev = stack->top;
    new_func->def_scope=def_scope;
    stack->top = new_func;
    stack->size++;
}

struct func_def_info* exit_func_def(struct function_stack* stack){
    struct func_def_info* rt = stack->top;
    stack->top=rt->prev;
    rt->prev=NULL;
    stack->size--;
    return rt;
}

void free_stack(struct function_stack* s){
    while(s->size>0){
        struct func_def_info* temp = s->top;
        s->top=temp->prev;
        s->size--;
    }
}