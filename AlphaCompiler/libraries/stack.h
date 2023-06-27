#include <stdlib.h>

#ifndef STACK_H
#define STACK_H
struct ml_comment_stack{
    int size;
    struct ml_comment_info* top;
};

struct ml_comment_info {
    int line_start;
    int line_end;
    struct ml_comment_info *prev;
};

void add_comment(struct ml_comment_stack *stack, int line_start, int line_end);

char* pop_comment(struct ml_comment_stack *stack);
#endif