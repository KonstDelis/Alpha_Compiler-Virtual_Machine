#include "VM_dispatcher.hpp"
#include "loader.hpp"
#include "assert.h"
#include "ErrMsg.hpp"



bool executionFinished = false;
unsigned pc = 0;
unsigned currLine = 0;
unsigned codeSize = 0;

execute_func_t executeFuncs[] = {

    execute_assign,
    execute_add,
    execute_sub,
    execute_mul,
    execute_div,
    execute_mod,
    NULL,
    NULL,
    NULL,
    NULL,
    execute_jump,
    execute_jeq,
    execute_jne,
    execute_jle,
    execute_jge,
    execute_jlt,
    execute_jgt,
    execute_call,
    execute_pusharg,
    execute_funcenter,
    execute_funcexit,
    execute_newtable,
    execute_tablegetelem,
    execute_tablesetelem,
    execute_nop

};

void execute_cycle(void){

    if(executionFinished) return;
    else if(pc == AVM_ENDING_PC){
        executionFinished = 1;
        return;
    } else {
        assert(pc < AVM_ENDING_PC);
        instruction* instr = &code[pc];
        assert(
                instr->opcode >= 0 &&
                instr->opcode <= AVM_MAX_INSTRUCTIONS
        );

        if(instr->srcLine!=0){
            currLine = instr->srcLine;
            if(DEBUG) std::cout<<"line: "<<currLine<<std::endl;
        }
           

        unsigned oldPC = pc;
        if(DEBUG)std::cout<<"OP is "<<instr->opcode<<std::endl;
        (*executeFuncs[instr->opcode])(instr);

        if(pc == oldPC)
            ++pc;
    }
}

double add_impl (double x,double y){
    return x+y;
}
double sub_impl (double x,double y){
    return x-y;
}
double mul_impl (double x,double y){
    return x*y;
}
double div_impl (double x,double y){

    if(y == 0) error_msg("can't divide with 0",currLine);

    return x/y;
}
double mod_impl (double x,double y){
    if(y == 0) error_msg("modulo with 0 is not allowed",currLine);

    if( (x-(int)x)!=0 || (y-(int)y)!=0) warning_msg("modulo doesn't allow doubles, implicit conversion from double to int",currLine);

    return ((unsigned)x % (unsigned)y);
}

bool jle_impl (double x, double y){
    return x <= y;
}
bool jge_impl (double x, double y){
    return x >= y;
}
bool jlt_impl (double x, double y){
    return x < y;
}
bool jgt_impl (double x, double y){
    return x > y;
}


