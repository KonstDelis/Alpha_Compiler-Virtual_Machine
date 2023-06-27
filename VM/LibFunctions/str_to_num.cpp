#include "LibFunctions.hpp"
#include <sstream>

void lib_strToNum(void){
    unsigned n = avm_totalactuals();
    avm_memcellclear(&retval);

    if(n!=1)
        error_msg("library function strtonum expected 1 arguments but "+std::to_string(n)+" have been pushed", currLine);

    avm_memcell* arg = avm_getactual(0);

    if(arg->type!=string_m)
        error_msg("library function strtonum expected an argument of type string but an argument of type "+typeStrings[arg->type]+" was pushed", currLine);   

    double dbl = 0.0;
    std::istringstream num(arg->data.strVal);

    num >> dbl;

    if(!num.fail() && num.eof()){
        retval.type = number_m;
        retval.data.numVal = dbl;
        return;
    }

    warning_msg("String: \n\""+arg->data.strVal+"\"\n could not be cast to a number", currLine);
    retval.type=nil_m;
}