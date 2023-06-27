#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#ifndef VM_STRUCTS_HPP
#define VM_STRUCTS_HPP

#define AVM_STACKSIZE 4096
#define AVM_WIPEOUT(m) memset(&(m),0,sizeof(m))
#define AVM_TABLE_HASHSIZE 211


enum avm_memcell_t {

    number_m,
    string_m,
    bool_m,
    table_m,
    userfunc_m,
    libfunc_m,
    nil_m,
    undef_m
}typedef avm_memcell_t;

class avm_table;

struct avm_memcell{
    public:
    enum avm_memcell_t  type;

    struct{

        double numVal;
        std::string strVal;
        unsigned char boolVal;
        avm_table* tableVal;
        unsigned funcVal;
        std::string libfuncVal;

    }data;
    avm_memcell();
    ~avm_memcell();
};

class avm_table{
    public:
    unsigned refCounter;
    int table_no;
    std::map<int, avm_memcell> table_int;
    std::map<std::string, avm_memcell> table_str;
    unsigned total();
    avm_memcell* getelem(avm_memcell* key);
    void setelem(avm_memcell* key, avm_memcell* value);
    void incrRef();
    void decrRef();

    avm_table();
    ~avm_table();
};

extern avm_memcell stack[AVM_STACKSIZE];

static void avm_initstack(void){

    for(unsigned i=0; i<AVM_STACKSIZE; ++i){
        stack[i].type = undef_m;
    }
}

extern std::string typeStrings[];

void avm_memcellclear(avm_memcell* m);

void avm_push_table_arg(avm_table* t);
#endif

