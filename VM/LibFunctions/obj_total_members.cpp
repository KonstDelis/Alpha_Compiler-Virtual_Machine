#include "LibFunctions.hpp"



void lib_objTotalMembers(void){
    avm_memcellclear(&retval);
    unsigned n = avm_totalactuals();

    if(n!=1)
        error_msg("library function objTotalMembers expected 1 argument but "+std::to_string(n)+" have been pushed", currLine);

     if(avm_getactual(0)->type!=table_m)
        error_msg("library function objTotalMembers expected an argument of type table but an argument of type "+typeStrings[avm_getactual(0)->type]+" was pushed", currLine);   




    retval.type = number_m;
    retval.data.numVal = avm_getactual(0)->data.tableVal->total();
    
}