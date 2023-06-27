#include "../VM_dispatcher.hpp"
#include "../VM_env.hpp"
#include "../loader.hpp"
#include "assert.h"
#include "../ErrMsg.hpp"




extern unsigned totalActuals;

void execute_call(instruction* instr){

    avm_memcell* func = avm_translate_operand(&instr->arg1, &ax);
    assert(func);
    avm_callsaveenvironment();

    switch(func->type){

        case userfunc_m: {
            pc = userFuncs_vm[func->data.funcVal].address;
            assert(pc< AVM_ENDING_PC);
            assert(code[pc].opcode == funcenter_v);
            break;
        }
        case string_m: avm_calllibfunc(func->data.strVal); break;
        case libfunc_m: avm_calllibfunc(func->data.libfuncVal); break;
        case table_m: avm_call_functor(func->data.tableVal); break;

        default: {
            std::string s = avm_tostring(func);
            error_msg("call: cannot bind "+s+" to function!",currLine);
            executionFinished = 1;
        } 
    }
}

void execute_funcenter(instruction* instr){

    avm_memcell* func = avm_translate_operand(&instr->result, &ax);
    assert(func);
    assert(pc == userFuncs_vm[func->data.funcVal].address);
    totalActuals = 0;
    userfunc* funcInfo = avm_getfuncinfo(pc);
    topsp = top;
    top = top - funcInfo->localSize;
}

void execute_funcexit(instruction* unused){

    unsigned oldTop = top;
    top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
    pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
    topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);

    while(++oldTop <= top){
        avm_memcellclear(&stack[oldTop]);
    }
}

void execute_pusharg(instruction* instr){
    if(DEBUG)std::cerr<<"Pushing (translate)\n";
    avm_memcell* arg = avm_translate_operand(&instr->arg1, &ax);
    if(DEBUG)std::cerr<<"Pushing (translate complete): type = "<<arg->type<<"\n";
    assert(arg);
    avm_assign(&stack[top],arg);
    ++totalActuals;
    avm_dec_top();
}

