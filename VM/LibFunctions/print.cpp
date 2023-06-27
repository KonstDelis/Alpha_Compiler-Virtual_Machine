#include "LibFunctions.hpp"

void lib_print(void){
    avm_memcellclear(&retval);
    unsigned n = avm_totalactuals();
    retval.type = nil_m;

    for(unsigned i =0; i<n; ++i){
        std::string s = avm_tostring(avm_getactual(i));
        if(DEBUG) green();
        std::cout<<s;
        if(DEBUG) resetOut();
    }
}