#include "LibFunctions.hpp"

void lib_typeof(){
    unsigned n = avm_totalactuals();

    if(n!=1)
        error_msg("library function typeof expected 1 argument but "+std::to_string(n)+" have been pushed", currLine);
    
    avm_memcellclear(&retval);
    retval.type = string_m;
    retval.data.strVal = typeof_typeStrings(avm_getactual(0)->type);
}

std::string typeof_typeStrings(avm_memcell_t type){
    std::string retStr; 
    switch(type){
        case number_m:{
            retStr = "number";
            break;
        }
        case string_m:{
            retStr = "string";
            break;
        }
        case bool_m:{
            retStr = "bool";
            break;
        }
        case table_m:{
            retStr = "table";
            break;
        }
        case userfunc_m:{
            retStr = "user function";
            break;
        }
        case libfunc_m:{
            retStr = "library function";
            break;
        }
        case nil_m:{
            retStr = "nil";
            break;
        }
        case undef_m:{
            retStr = "undefined";
            break;
        }
        default:{
            error_msg("Unexpected error, typeof", -51);
        }
    }
    return retStr;
}