#include "LibFunctions.hpp"


void lib_objMemberKeys(void){
    unsigned n = avm_totalactuals();
    avm_memcellclear(&retval);

    if(n!=1)
        error_msg("library function objMemberKeys expected 1 argument but "+std::to_string(n)+" have been pushed", currLine);

     if(avm_getactual(0)->type!=table_m)
        error_msg("library function objMemberKeys expected an argument of type number but an argument of type "+typeStrings[avm_getactual(0)->type]+" was pushed", currLine);   


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

    for(auto &tmp : avm_getactual(0)->data.tableVal->table_str){

        new_key.type = number_m;
        new_key.data.numVal = counter++;
        old_key.type = string_m;
        old_key.data.strVal = tmp.first;
        retval.data.tableVal->setelem(&new_key, &old_key);
    }
}