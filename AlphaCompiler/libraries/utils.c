#include "utils.h"

void red () {
    fprintf(stderr, "\033[1;31m");
}
void yellow () {
    fprintf(stderr, "\033[0;33m");
}
void reset () {
    fprintf(stderr, "\033[0m");
}
void check_malloc(void* ptr, char* errmsg){
    if(ptr==NULL){
        red();
        fprintf(stderr, "%s\n", errmsg?errmsg:"Error: Memory allocation failed");
        reset();
        exit(-2);
    }
}
void runtimeError(char* msg, unsigned int lineno){
    red();
    fprintf(stderr, "Runtime Error: line %d : %s\n", lineno, msg);
    reset();
    exit(-2);
}