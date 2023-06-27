#include "LibFunctions.hpp"

void lib_objCopy(void){
    avm_memcellclear(&retval);
     unsigned n = avm_totalactuals();

    if(n!=1)
        error_msg("library function objCopy expected 1 argument but "+std::to_string(n)+" have been pushed", currLine);

     if(avm_getactual(0)->type!=table_m)
        error_msg("library function objCopy expected an argument of type number but an argument of type "+typeStrings[avm_getactual(0)->type]+" was pushed", currLine);   


    avm_assign(&retval,avm_getactual(0));
}