#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"

void add_comment(struct ml_comment_stack *stack, int line_start, int line_end){
    struct ml_comment_info* new_comment = (struct ml_comment_info*)malloc(sizeof(struct ml_comment_info));
    new_comment->line_start = line_start;
    new_comment->line_end = line_end;
    new_comment->prev = stack->top;
    stack->top = new_comment;
    stack->size++;
}

char* pop_comment(struct ml_comment_stack *stack){
    char *line_start = malloc(sizeof(char)*45);
    char line_end[20]; 

    if(stack->size==0){
        fprintf(stderr,"Comment stack is empty\n");
        return NULL;
    }
    sprintf(line_start,"%d",stack->top->line_start);
    sprintf(line_end,"%d",stack->top->line_end);
    char* dash = "-";
    strcat(line_start, dash);
    strcat(line_start, line_end);

    struct ml_comment_info* tmp=stack->top;
    stack->top = stack->top->prev;
    stack->size--;
    return line_start;
}
