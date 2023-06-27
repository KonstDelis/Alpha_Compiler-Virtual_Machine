#include "VM_dispatcher.hpp"
#include "loader.hpp"
#include "VM_env.hpp"
#include "VM_structs.hpp"
#include "test_help.cpp"
#include "ErrMsg.hpp"
extern unsigned totalActuals;
bool DEBUG = false;

void printLine(){printf("------------------------------------------\n");};

int main(int argc, char* argv[]){
    readBinary(argc, argv);
    avm_initstack();
    pc = 1;
    topsp = AVM_STACKSIZE-totalVarOffset-1;
    top = topsp;
    executionFinished = false;
    codeSize = totalInstructions;
    totalActuals = 0;
    int counter = 1;

    if(DEBUG)printf("\n\n----------------------Instructions--------------------\n\n");
    while(!executionFinished){
        if(DEBUG)printLine();
        if(DEBUG)printf("%-4d| ",pc);
        if(DEBUG)printOpcode(code[pc].opcode);
        if(DEBUG)printVMarg(&code[pc].arg1);
        if(DEBUG)printVMarg(&code[pc].arg2);
        if(DEBUG)printVMarg(&code[pc].result);
        if(DEBUG)printf("\n");
        if(DEBUG)fflush(stdout);
        execute_cycle();
    }

    if(DEBUG)std::cout<<"Execution finished!"<<std::endl;
    return 0;
}