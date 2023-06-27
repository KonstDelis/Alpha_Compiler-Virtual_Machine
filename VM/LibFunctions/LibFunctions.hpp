#ifndef LIB_FUNCTIONS_HPP
#define LIB_FUNCTIONS_HPP

#include "../VM_structs.hpp"
#include "../VM_env.hpp"
#include "../VM_dispatcher.hpp"
#include "../ErrMsg.hpp"
#include <map>

std::string typeof_typeStrings(avm_memcell_t type);
void lib_typeof(void);
void lib_print(void);
void lib_input(void);
void lib_totalArgs(void);
void lib_argument(void);
void lib_objTotalMembers(void);
void lib_objMemberKeys(void);
void lib_objCopy(void);
void lib_sin(void);
void lib_cos(void);
void lib_sqrt(void);
void lib_strToNum(void);

void lib_dtoi(void);
void lib_abs(void);
void lib_assert(void);
void lib_objMemberindices(void);
void lib_objMemberStrings(void);
void lib_pow(void);

extern std::map<std::string, library_func_t> ImplementedLibraries;

#endif