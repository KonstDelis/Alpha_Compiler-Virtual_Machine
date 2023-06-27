#include "VM_structs.hpp"
#include <assert.h>
#include "ErrMsg.hpp"
#include "VM_env.hpp"
#include "VM_dispatcher.hpp"

extern unsigned totalActuals;
int table_num = 0;


std::string typeStrings[] = {
    "number",
    "string",
    "bool",
    "table",
    "userfunc",
    "libfunc",
    "nil",
    "undef"
};

avm_memcell::avm_memcell(){data.tableVal=NULL;}
avm_memcell::~avm_memcell(){if(type == table_m && data.tableVal!=NULL) avm_memcellclear(this);}

unsigned int avm_table::total(){return table_int.size()+table_str.size();}
void avm_table::incrRef(){refCounter++; if(DEBUG) std::cerr<<"Table "<<table_no<<" :: Increasing ref to "<<refCounter<<"\n";}
void avm_table::decrRef(){refCounter--; if(DEBUG) std::cerr<<"Table "<<table_no<<" :: Decreasing ref to "<<refCounter<<"\n";}
void avm_table::setelem(avm_memcell* key, avm_memcell* value){
    if(value->type == table_m && value->data.tableVal) value->data.tableVal->incrRef();
    if(key->type!=string_m && key->type != number_m){
        error_msg("key of table must be a number or a string, key '"+avm_tostring(key)+"' is neither", currLine);
    }
    if(key->type == number_m){
        table_int[(int)key->data.numVal] = *value;
    }
    else{
        table_str[key->data.strVal] = *value;
    }
}
avm_memcell* avm_table::getelem(avm_memcell* key){
    if(key->type!=string_m && key->type != number_m){
        error_msg("key of table must be a number or a string, key '"+avm_tostring(key)+"' is neither", currLine);
    }
    if(key->type == number_m){
        if(table_int.count((int)key->data.numVal))
            return &table_int[(int)key->data.numVal];
    }
    else{
        if(table_str.count(key->data.strVal))
            return &table_str[key->data.strVal];
    }
    return NULL;
}
avm_table::avm_table(){
    table_no = table_num++;
    refCounter = 0;
    if(DEBUG) std::cerr<<"Constructor table number "<<table_no<<" created\n";
}
avm_table::~avm_table(){
    if(DEBUG) std::cout << "Table "<<table_no<<" :: Destructor called\n";
    for(auto &element : this->table_int){
        avm_memcellclear(&(element.second));
    }
    for(auto &element : this->table_str){
        avm_memcellclear(&(element.second));
    }
}


void avm_memcellclear(avm_memcell* m){
    if(m->type==table_m){
        m->data.tableVal->decrRef();
        if(m->data.tableVal->refCounter==0){
            if(DEBUG) std::cerr<<"Clearing table\n";
            delete m->data.tableVal;
        }
        m->data.tableVal = NULL;
        m->type = undef_m;
    }
    if(m->type != undef_m){
        m->type = undef_m;
    }  
} 

void avm_push_table_arg(avm_table* t){


    stack[top].type = table_m;
    stack[top].data.tableVal = t;
    stack[top].data.tableVal->incrRef();
    ++totalActuals;
    avm_dec_top();

}
