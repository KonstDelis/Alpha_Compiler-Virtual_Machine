#include <stdlib.h>


struct loopstack{

    int size;

    struct loopstack_info* top;

};

struct loopstack_info{

    int loopcounter;
    struct loopstack_info *prev;

};


void loopstack_push(struct loopstack* stack, int loopcounter);

int loopstack_pop(struct loopstack* stack);