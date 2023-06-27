#include "LibFunctions.hpp"
#include <math.h>

void lib_dtoi(void){
    avm_memcellclear(&retval);
    unsigned n = avm_totalactuals();

    if(n!=1)
        error_msg("library function real2int expected 1 argument but "+std::to_string(n)+" have been pushed", currLine);


    if(avm_getactual(0)->type!=number_m)
        error_msg("library function real2int expected an argument of type number but an argument of type "+typeStrings[avm_getactual(0)->type]+" was pushed", currLine);

    retval.type = number_m;
    retval.data.numVal = (int)avm_getactual(0)->data.numVal;
}

void lib_assert(void){
    avm_memcellclear(&retval);
    unsigned n = avm_totalactuals();
    retval.type=nil_m;

    if(n<1)
        error_msg("library function assert expected at least 1 argument but "+std::to_string(n)+" have been pushed", currLine);

    for(int i=0; i<n; i++) {
        if(avm_getactual(i)->type!=bool_m)
            error_msg("library function assert expected an argument of type bool but an argument of type "+typeStrings[avm_getactual(0)->type]+" was pushed", currLine);
        if(avm_getactual(i)->data.boolVal == false){
            red();
            std::cerr<<"Assertion failed: line "<<currLine<<": failed on assertion number "<<i+1<<"\n";
            reset();
            exit(10);
        }
    }
}

void lib_abs(void){
    avm_memcellclear(&retval);
    unsigned n = avm_totalactuals();

    if(n!=1)
        error_msg("library function abs expected 1 argument but "+std::to_string(n)+" have been pushed", currLine);


    if(avm_getactual(0)->type!=number_m)
        error_msg("library function abs expected an argument of type number but an argument of type "+typeStrings[avm_getactual(0)->type]+" was pushed", currLine);


    retval.type = number_m;
    retval.data.numVal = abs(avm_getactual(0)->data.numVal);
}

void lib_objMemberindices(void){
    unsigned n = avm_totalactuals();
    avm_memcellclear(&retval);

    if(n!=1)
        error_msg("library function objectmemberindices expected 1 argument but "+std::to_string(n)+" have been pushed", currLine);

     if(avm_getactual(0)->type!=table_m)
        error_msg("library function objectmemberindices expected an argument of type table but an argument of type "+typeStrings[avm_getactual(0)->type]+" was pushed", currLine);   


    retval.type = table_m;
    retval.data.tableVal = new avm_table();
    retval.data.tableVal->incrRef();

    avm_memcell new_key, old_key;

    unsigned counter = 0;

    for(auto &tmp : avm_getactual(0)->data.tableVal->table_int){

        new_key.type = number_m;
        new_key.data.numVal = counter++;
        old_key.type = number_m;
        old_key.data.numVal = tmp.first;
        retval.data.tableVal->setelem(&new_key, &old_key);
    }
}

void lib_objMemberStrings(void){
    unsigned n = avm_totalactuals();
    avm_memcellclear(&retval);

    if(n!=1)
        error_msg("library function objectmemberstrings expected 1 argument but "+std::to_string(n)+" have been pushed", currLine);

     if(avm_getactual(0)->type!=table_m)
        error_msg("library function objectmemberstrings expected an argument of type table but an argument of type "+typeStrings[avm_getactual(0)->type]+" was pushed", currLine);   


    retval.type = table_m;
    retval.data.tableVal = new avm_table();
    retval.data.tableVal->incrRef();

    avm_memcell new_key, old_key;

    unsigned counter = 0;

    for(auto &tmp : avm_getactual(0)->data.tableVal->table_str){

        new_key.type = number_m;
        new_key.data.numVal = counter++;
        old_key.type = string_m;
        old_key.data.strVal = tmp.first;
        retval.data.tableVal->setelem(&new_key, &old_key);
    }
}

void lib_pow(void){
    avm_memcellclear(&retval);
    unsigned n = avm_totalactuals();

    if(n!=2)
        error_msg("library function pow expected 2 arguments but "+std::to_string(n)+" "+(n==1?"has":"have")+" been pushed", currLine);


    if(avm_getactual(0)->type!=number_m)
        error_msg("library function pow expected arguments of type number but the first argument is of type "+typeStrings[avm_getactual(0)->type], currLine);

    if(avm_getactual(1)->type!=number_m)
        error_msg("library function pow expected arguments of type number but the second argument is of type "+typeStrings[avm_getactual(0)->type], currLine);


    retval.type = number_m;
    retval.data.numVal = pow(avm_getactual(0)->data.numVal, avm_getactual(1)->data.numVal);
}