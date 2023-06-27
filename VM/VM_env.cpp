#include "VM_env.hpp"
#include "VM_dispatcher.hpp"
#include "loader.hpp"
#include <assert.h>
#include <iomanip>
#include <sstream>
#include "ErrMsg.hpp"
#include "LibFunctions/LibFunctions.hpp"

avm_memcell ax, bx, cx;
avm_memcell retval;
unsigned top, topsp;
unsigned totalActuals = 0;
avm_memcell stack[AVM_STACKSIZE];

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg){

    if(arg->type == -10)
        arg->type = nil_a;

    switch (arg->type){

        case global_a: return &(stack[AVM_STACKSIZE-1-(arg->val)]);
        case local_a: return &stack[topsp-arg->val];
        case formal_a:  return &stack[topsp+AVM_STACKENV_SIZE+1+arg->val];
        case retval_a: return &retval;

        case number_a: {
            reg->type = number_m;
            reg->data.numVal = consts_getnumber(arg->val);
            return reg;          
        }

        case string_a: {
            reg->type = string_m;
            reg->data.strVal = consts_getstring(arg->val);
            return reg; 
        }

        case bool_a: {
            reg->type = bool_m;
            reg->data.boolVal = arg->val;

            return reg; 
        }

        case nil_a: reg->type = nil_m; return reg;

        case userfunc_a: {
            if(DEBUG){red(); std::cerr<<"Enter uf translate\n";reset();}
            reg->type = userfunc_m;
            reg->data.funcVal = arg->val;
            return reg;
        }

        case libfunc_a: {
            reg->type = libfunc_m;
            reg->data.libfuncVal = libfuncs_getused(arg->val);
            return reg;
        }

        default: assert(0);

    }
    return NULL;
}


void avm_assign(avm_memcell* lv, avm_memcell* rv){

    if(lv == rv) return;

    avm_memcellclear(lv);

    if(lv->type == table_m && 
       rv->type == table_m &&
       lv->data.tableVal == rv->data.tableVal)
       return;

    if(rv->type == undef_m)
        warning_msg("assigning from 'undef' content!",currLine);

    switch(rv->type){
        case number_m:{
            lv->type=number_m;
            lv->data.numVal = rv->data.numVal;
            break;
        }
        case string_m:{
            lv->type=string_m;
            
            lv->data.strVal = rv->data.strVal;
            break;
        }
        case libfunc_m:{
            lv->type=libfunc_m;
            lv->data.libfuncVal = rv->data.libfuncVal;
            break;
        }
        case userfunc_m:{
            lv->type=userfunc_m;
            if(DEBUG){red();std::cerr<<"Assigning uf\n";reset();}
            lv->data.funcVal = rv->data.funcVal;
            if(DEBUG){red();std::cerr<<"New lv funcval"<<lv->data.funcVal<<"\n";reset();}
            break;
        }
        case bool_m:{
            lv->type=bool_m;
            lv->data.boolVal = rv->data.boolVal;
            break;
        }
        case nil_m:{
            lv->type=nil_m;
            lv->data.numVal = rv->data.numVal;
            break;
        }
        case undef_m:{
            lv->type=undef_m;
            break;
        }
        case table_m:{
            lv->type = table_m;
            lv->data.tableVal = rv->data.tableVal;
            break;
        }


    }
 
    if(lv->type == table_m)
        lv->data.tableVal->incrRef();
}

void avm_dec_top(void){

    if(!top){
        error_msg("stack overflow",currLine);
        executionFinished = 1;
    } else {
        --top;
    }
}

void avm_push_envvalue(unsigned val){

    stack[top].type = number_m;
    stack[top].data.numVal = val;
    avm_dec_top();

}

void avm_callsaveenvironment(void){

    avm_push_envvalue(totalActuals);
    avm_push_envvalue(pc+1);
    avm_push_envvalue(top + totalActuals +2);
    avm_push_envvalue(topsp);
}


unsigned avm_get_envvalue(unsigned i){

    assert(stack[i].type == number_m);
    unsigned val = (unsigned)stack[i].data.numVal;
    assert(stack[i].data.numVal == ((double)val));
    return val;
}

library_func_t avm_getlibraryfunc(std::string id){
    library_func_t lib = ImplementedLibraries[id];
    if(!ImplementedLibraries.count(id)){
        return NULL;
    }
    return lib;
}

void avm_calllibfunc(std::string id){

    library_func_t f = avm_getlibraryfunc(id);

    if(!f){
        error_msg("unsupported lib func '"+id+"' called!",currLine);
        executionFinished = 1;
    } else {

        topsp = top;
        totalActuals = 0;

        (*f)();

        if(!executionFinished)
            execute_funcexit((instruction*)0);
    }
}

unsigned avm_totalactuals(void){

    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell* avm_getactual(unsigned i){

    assert(i < avm_totalactuals());

    return &stack[topsp + AVM_STACKENV_SIZE +1+i];
}

double consts_getnumber(unsigned index){
    return numConst_vm[index];
}
std::string consts_getstring(unsigned index){
    return stringConst_vm[index];
}
std::string libfuncs_getused(unsigned index){
    return libFuncs_vm[index];
}

tostring_func_t tostringFuncs[] = {

    number_tostring,
    string_tostring,
    bool_tostring,
    table_tostring,
    userfunc_tostring,
    libfunc_tostring,
    nil_tostring,
    undef_tostring
};

tobool_func_t toboolFuncs[] = {

    number_tobool,
    string_tobool,
    bool_tobool,
    table_tobool,
    userfunc_tobool,
    libfunc_tobool,
    nil_tobool,
    undef_tobool
};

std::string avm_tostring(avm_memcell* m){
    assert(m->type >= 0 && m->type<=undef_m);
    return (*tostringFuncs[m->type])(m);
}

userfunc* avm_getfuncinfo(unsigned address){
    for(auto &uf : userFuncs_vm){
        if(uf.address == address)
            return &uf;
    }
    error_msg("function with address "+(std::to_string(address)+" not found"), currLine);
    return NULL;
}

std::string number_tostring(avm_memcell* m){
    assert(m && m->type==number_m);
    double number = m->data.numVal;
    std::ostringstream precision3;
    precision3 << std::fixed;
    precision3 << std::setprecision(3);
    precision3 << number;
    return (number-(int)number)==0? std::to_string((int)number) : precision3.str();
}
std::string string_tostring(avm_memcell* m){
    assert(m && m->type==string_m);
    return m->data.strVal;
}
std::string bool_tostring(avm_memcell* m){
    assert(m && m->type==bool_m);
    return m->data.boolVal?"true":"false";
}
std::string table_tostring(avm_memcell* m){
    assert(m && m->type==table_m);
    std::string retStr = "(table)[";
    for(auto &element : m->data.tableVal->table_int){
        retStr += " { ";
        retStr += std::to_string(element.first);
        retStr += ", ";
        retStr += avm_tostring(&element.second);
        retStr += "} ";
    }
    for(auto &element : m->data.tableVal->table_str){
        retStr += " { ";
        retStr += element.first;
        retStr += ", ";
        retStr += avm_tostring(&element.second);
        retStr += "} ";
    }
    retStr += "]";
    return retStr;
}
std::string table_tostringWarning(avm_memcell* m){
    assert(m && m->type==table_m);
    std::string retStr = "\n(table)[\n";
    for(auto element : m->data.tableVal->table_int){
        retStr += "\t{ ";
        retStr += std::to_string(element.first);
        retStr += ", ";
        retStr += avm_tostring(&element.second);
        retStr += "}\n";
    }
    for(auto element : m->data.tableVal->table_str){
        retStr += "\t{ ";
        retStr += element.first;
        retStr += ", ";
        retStr += avm_tostring(&element.second);
        retStr += "}\n";
    }
    retStr += "]\n";
    return retStr;
}
std::string userfunc_tostring(avm_memcell* m){
    assert(m && m->type==userfunc_m);
    if(DEBUG)std::cerr<<"Func val = "<<m->data.funcVal<<"\n";
    std::string retStr= "(user function: '";
    retStr += userFuncs_vm[m->data.funcVal].id;
    retStr += "')";
    return retStr;
}
std::string libfunc_tostring(avm_memcell* m){
    assert(m && m->type==libfunc_m);
    std::string retStr= "(library function: '";
    retStr += libFuncs_vm[m->data.funcVal];
    retStr += "')";
    return retStr;
}
std::string nil_tostring(avm_memcell* m){
    assert(m && m->type==nil_m);
    return "(nil)";
}
std::string undef_tostring(avm_memcell* m){
    assert(m && m->type==undef_m);
    return "(undefined)";
}

bool number_tobool(avm_memcell* m){
    return m->data.numVal != 0;
}
bool string_tobool(avm_memcell* m){
    return true;
}
bool bool_tobool(avm_memcell* m){
    return m->data.boolVal;
}
bool table_tobool(avm_memcell* m){
    return 1;
}
bool userfunc_tobool(avm_memcell* m){
    return 1;
}
bool libfunc_tobool(avm_memcell* m){
    return 1;
}
bool nil_tobool(avm_memcell* m){
    return 0;
}
bool undef_tobool(avm_memcell* m){
    assert(0);
    return 0;
}

bool avm_tobool(avm_memcell* m){

    assert(m->type >= 0 && m->type < undef_m );

    return (*toboolFuncs[m->type])(m);
}

void avm_call_functor(avm_table* t){

    cx.type = string_m;
    cx.data.strVal = "()";
    avm_memcell* f = t->getelem(&cx);

    if(!f) error_msg("in calling table: no '()' element found!",currLine);
    else if(f->type == table_m)
        avm_call_functor(f->data.tableVal);
    else if(f->type == userfunc_m){

        avm_push_table_arg(t);
        avm_callsaveenvironment();
        pc = userFuncs_vm[f->data.funcVal].address;
        assert(pc < AVM_ENDING_PC);
        assert(code[pc].opcode == funcenter_v);
    }else
        error_msg("in calling table: illegal '()' element value!",currLine);
    

}


