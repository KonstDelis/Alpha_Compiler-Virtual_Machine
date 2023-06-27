#include "loopstack.h"
#include <stdlib.h>
#include <stdio.h>



void loopstack_push(struct loopstack* stack, int loopcounter){

     struct loopstack_info* new_loopcounter = malloc(sizeof(struct loopstack_info));
    new_loopcounter->loopcounter = loopcounter;
    new_loopcounter->prev = stack->top;
    stack->top = new_loopcounter;
    stack->size++;
    
}

int loopstack_pop(struct loopstack* stack){


      
    if(stack->size==0){
        fprintf(stderr,"loopcounter stack is empty\n");
        return 1;
    }

     struct loopstack_info* tmp = malloc(sizeof(struct loopstack_info));
     tmp = stack->top;
    stack->top = stack->top->prev;
    stack->size--;
    
    return tmp->loopcounter;
}