#include "LibFunctions.hpp"
#include <math.h>


void lib_cos(void){
    avm_memcellclear(&retval);
    unsigned n = avm_totalactuals();

    if(n!=1)
        error_msg("library function cos expected 1 argument but "+std::to_string(n)+" have been pushed", currLine);


    if(avm_getactual(0)->type!=number_m)
        error_msg("library function cos expected an argument of type number but an argument of type "+typeStrings[avm_getactual(0)->type]+" was pushed", currLine);


    retval.type = number_m;
    retval.data.numVal = cos(avm_getactual(0)->data.numVal*(M_PI/180));
}