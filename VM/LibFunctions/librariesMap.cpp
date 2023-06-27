#include "LibFunctions.hpp"

std::map<std::string, library_func_t> ImplementedLibraries = {
    {"print"                ,lib_print},
    {"typeof"               ,lib_typeof},
    {"input"                ,lib_input},
    {"totalarguments"       ,lib_totalArgs},
    {"argument"             ,lib_argument},
    {"objectcopy"           ,lib_objCopy},
    {"objectmemberkeys"     ,lib_objMemberKeys},
    {"objecttotalmembers"   ,lib_objTotalMembers},
    {"sin"                  ,lib_sin},
    {"cos"                  ,lib_cos},
    {"sqrt"                 ,lib_sqrt},
    /*Extra library functions*/
    {"objectmemberindices"  ,lib_objMemberindices},
    {"objectmemberstrings"  ,lib_objMemberStrings},
    {"abs"                  ,lib_abs},
    {"real2int"             ,lib_dtoi},
    {"assert"               ,lib_assert},
    {"pow"                  ,lib_pow}

};