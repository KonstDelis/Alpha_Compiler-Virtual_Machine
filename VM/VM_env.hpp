#include "VM_structs.hpp"
#include "../AlphaCompiler/libraries/target_structs.h"
#include "loader.hpp"

#ifndef VM_ENV_HPP
#define VM_ENV_HPP

#define AVM_STACKENV_SIZE 4
#define AVM_NUMACTUALS_OFFSET +4
#define AVM_SAVEDPC_OFFSET +3
#define AVM_SAVEDTOP_OFFSET +2
#define AVM_SAVEDTOPSP_OFFSET +1


extern avm_memcell ax, bx, cx;
extern avm_memcell retval;
extern unsigned top, topsp;

double consts_getnumber(unsigned index);
std::string consts_getstring(unsigned index);
std::string libfuncs_getused(unsigned index);

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg);


std::string avm_tostring(avm_memcell*);
std::string table_tostringWarning(avm_memcell*);
std::string number_tostring(avm_memcell*);
std::string string_tostring(avm_memcell*);
std::string bool_tostring(avm_memcell*);
std::string table_tostring(avm_memcell*);
std::string userfunc_tostring(avm_memcell*);
std::string libfunc_tostring(avm_memcell*);
std::string nil_tostring(avm_memcell*);
std::string undef_tostring(avm_memcell*);

typedef std::string (*tostring_func_t)(avm_memcell*);

void avm_assign(avm_memcell* lv, avm_memcell* rv);

void avm_dec_top(void);
void avm_push_envvalue(unsigned val);
void avm_callsaveenvironment(void);

userfunc* avm_getfuncinfo(unsigned address);
unsigned avm_get_envvalue(unsigned i);

typedef void (*library_func_t)(void);
library_func_t avm_getlibraryfunc(std::string id);

void avm_calllibfunc(std::string id);

unsigned avm_totalactuals(void);
avm_memcell* avm_getactual(unsigned i);


typedef bool (*tobool_func_t)(avm_memcell*);

bool number_tobool(avm_memcell* m);
bool string_tobool(avm_memcell* m);
bool bool_tobool(avm_memcell* m);
bool table_tobool(avm_memcell* m);
bool userfunc_tobool(avm_memcell* m);
bool libfunc_tobool(avm_memcell* m);
bool nil_tobool(avm_memcell* m);
bool undef_tobool(avm_memcell* m);

bool avm_tobool(avm_memcell* m);

void avm_call_functor(avm_table* t);


#endif


