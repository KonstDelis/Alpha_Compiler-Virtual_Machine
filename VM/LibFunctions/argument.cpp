#include "LibFunctions.hpp"

void lib_argument(void){
    unsigned n = avm_totalactuals();
    avm_memcellclear(&retval);
    retval.type = nil_m;
    if(n!=1)
        error_msg("library function argument expected 1 argument but "+std::to_string(n)+" have been pushed", currLine);
    
    if(avm_getactual(0)->type != number_m){
        error_msg("library function argument expected an argument of type number but an argument of type "+(typeStrings[avm_getactual(0)->type])+" was pushed", currLine);
    }
    
    unsigned p_topsp = avm_get_envvalue(topsp+AVM_SAVEDTOPSP_OFFSET);
    if(!p_topsp){
        error_msg("argument() was called outside a function", currLine);
    }

    if(avm_getactual(0)->data.numVal >= avm_get_envvalue(p_topsp+AVM_NUMACTUALS_OFFSET) ||
        avm_getactual(0)->data.numVal < 0)
    {
        error_msg("argument was called with parameter '"+std::to_string((avm_getactual(0)->data.numVal))+"' but no such argument index exists", currLine);
    }

    avm_memcell* arg = &stack[p_topsp + AVM_STACKENV_SIZE +1+ (int)avm_getactual(0)->data.numVal];
    avm_assign(&retval, arg);
}