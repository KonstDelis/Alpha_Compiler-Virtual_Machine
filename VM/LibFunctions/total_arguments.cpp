#include "LibFunctions.hpp"

void lib_totalArgs(void){
    unsigned n = avm_totalactuals();
    avm_memcellclear(&retval);
    retval.type = nil_m;
    if(n!=0)
        error_msg("library function total_arguments expected no arguments but "+std::to_string(n)+" have been pushed", currLine);

    unsigned p_topsp = avm_get_envvalue(topsp+AVM_SAVEDTOPSP_OFFSET);

    if(!p_topsp){
        error_msg("total_arguments() was called outside a function", currLine);
    }
    else{
        retval.type=number_m;
        retval.data.numVal=avm_get_envvalue(p_topsp+AVM_NUMACTUALS_OFFSET);
    }
}