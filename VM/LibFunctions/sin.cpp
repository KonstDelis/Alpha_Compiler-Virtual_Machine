#include "LibFunctions.hpp"
#include <math.h>


void lib_sin(void){
    avm_memcellclear(&retval);
    unsigned n = avm_totalactuals();

    if(n!=1)
        error_msg("library function sin expected 1 argument but "+std::to_string(n)+" have been pushed", currLine);


    if(avm_getactual(0)->type!=number_m)
        error_msg("library function sin expected an argument of type number but an argument of type "+typeStrings[avm_getactual(0)->type]+" was pushed", currLine);


    retval.type = number_m;
    retval.data.numVal = sin(avm_getactual(0)->data.numVal*(M_PI/180));
}