#include "LibFunctions.hpp"
#include <sstream>

void lib_input(void){
    unsigned n = avm_totalactuals();
    const char* typeOfWhitespaces = " \t\n\r\f\v";
    avm_memcellclear(&retval);

    if(n!=0)
        error_msg("library function input expected no arguments but "+std::to_string(n)+" have been pushed", currLine);

    std::string s;
    std::getline(std::cin, s);

    //trim s_copy string
    std::string s_copy = s;
    s_copy.erase(s_copy.find_last_not_of(typeOfWhitespaces) + 1);
    s_copy.erase(0,s_copy.find_first_not_of(typeOfWhitespaces));

    if(s_copy.compare("nil") == 0){
        retval.type=nil_m;
        return;
    }
    if(s_copy.compare("true") == 0){
        retval.type=bool_m;
        retval.data.boolVal=true;
        return;
    }
    if(s_copy.compare("false") == 0){
        retval.type=bool_m;
        retval.data.boolVal=false;
        return;
    }
    
    double dbl = 0.0;
    std::istringstream num(s_copy);

    num >> dbl;

    if(!num.fail() && num.eof()){
        retval.type = number_m;
        retval.data.numVal = dbl;
        return;
    }




    retval.type=string_m;
    retval.data.strVal=s;
}