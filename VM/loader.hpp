#include <vector>
#include <string>
#include "../AlphaCompiler/libraries/target_structs.h"
#ifndef LOADER_HPP
#define LOADER_HPP

extern unsigned totalStringOffset;
extern unsigned totalUserFuncOffset;
extern unsigned totalLibFuncOffset;
extern unsigned totalNumConstOffset;
extern unsigned totalVarOffset;
extern unsigned totalInstructions;

class userfunc{
    public:
    unsigned address;
    unsigned localSize;
    std::string id;

};

extern std::vector<std::string> stringConst_vm;
extern std::vector<double> numConst_vm;
extern std::vector<userfunc> userFuncs_vm;
extern std::vector<std::string> libFuncs_vm;
extern std::vector<instruction> code;

int readBinary(int argc, char* argv[]);

#endif