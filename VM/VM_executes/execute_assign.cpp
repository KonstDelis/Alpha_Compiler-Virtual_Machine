#include "../VM_dispatcher.hpp"
#include "../VM_env.hpp"
#include <assert.h>
#include "../ErrMsg.hpp"

extern void avm_warning(std::string content);


void execute_assign(instruction* instr){

    avm_memcell* lv = avm_translate_operand(&instr->result, (avm_memcell*)0);
    avm_memcell* rv = avm_translate_operand(&instr->arg1, &ax);
    if(DEBUG)std::cerr<<"Type of rv = "<<rv->type<<std::endl;

    //assert(lv && (&stack[N-1] >= lv && lv > &stack[top] || lv == &retval));
    assert(rv);

    avm_assign(lv,rv);
}