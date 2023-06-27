#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <assert.h>
#include "ErrMsg.hpp"
#include "loader.hpp"
#include "VM_dispatcher.hpp"
#include <stdlib.h>
using namespace std;

unsigned totalStringOffset;
unsigned totalUserFuncOffset;
unsigned totalLibFuncOffset;
unsigned totalNumConstOffset;
unsigned totalVarOffset;
unsigned totalInstructions;

vector<string> stringConst_vm;
vector<double> numConst_vm;
vector<userfunc> userFuncs_vm;
vector<string> libFuncs_vm;
vector<instruction> code;


bool endsWith(string const &str, string const &suffix) {
    if (str.length() < suffix.length()) {
        return false;
    }
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

string readStr(FILE* fbin){
    char c;
    string retStr = "";
    while((c=fgetc(fbin))!='\0'){
        retStr += c;
    }
    //assert(retStr.empty());
    return retStr;
}

int readBinary(int argc, char* argv[]){

    unsigned magicnumber = 340200501, read_magic=0;
    double number;


    if(argc != 2 && argc!=3)
        error_msg("Error: Invalid parameters\nRun program as './avm binary.abc'\n", 0);
    string binary_filepath = argv[1];
    if(!endsWith(binary_filepath, ".abc"))
        error_msg("Error: Invalid parameters\nParameter is not an alpha binary file(.abc)\n",0);
    if(argc==3 && strcmp(argv[2],"-debug")!=0)
        error_msg("Error: Invalid parameters\nOnly third parameter allowed is '-debug'\n",0);
    if(argc==3 && strcmp(argv[2],"-debug")==0)
        DEBUG=true;

    FILE *fbin = fopen(binary_filepath.c_str(), "rb");

    fread(&read_magic,sizeof(magicnumber),1,fbin);
    if(read_magic!=magicnumber){
        error_msg("Binary file has incorrect magic number",0);
    }

    if(DEBUG)cout<<"Magic num is correct "<<read_magic<<endl;

    fread(&totalVarOffset,sizeof(unsigned),1,fbin);
    
    fread(&totalStringOffset,sizeof(totalStringOffset),1,fbin);
    if(DEBUG)cout<<"Total string offset: "<<totalStringOffset<<endl;
    
    for(int i = 0; i<totalStringOffset; ++i){
        stringConst_vm.push_back(readStr(fbin));
    }
    
    fread(&totalNumConstOffset,sizeof(totalNumConstOffset),1,fbin);
    if(DEBUG)cout<<"Total num offset: "<<totalNumConstOffset<<endl;
    for(int i = 0; i<totalNumConstOffset; ++i){
        fread(&number,sizeof(number),1,fbin);
        numConst_vm.push_back(number);
    }
    
    fread(&totalUserFuncOffset,sizeof(totalUserFuncOffset),1,fbin);
    if(DEBUG)cout<<"Total usrFuncs offset: "<<totalUserFuncOffset<<endl;
    for(int i = 0; i<totalUserFuncOffset; ++i){
        userfunc usrf;
        fread(&usrf.address,sizeof(usrf.address),1,fbin);
        fread(&usrf.localSize,sizeof(usrf.localSize),1,fbin);
        usrf.id = readStr(fbin);
        userFuncs_vm.push_back(usrf);
        
    }

    fread(&totalLibFuncOffset,sizeof(totalLibFuncOffset),1,fbin);
    if(DEBUG)cout<<"Total libFunc offset: "<<totalLibFuncOffset<<endl;
    for(int i=0; i<totalLibFuncOffset; ++i){
        libFuncs_vm.push_back(readStr(fbin));
    }


    fread(&totalInstructions,sizeof(totalInstructions),1,fbin);
    for(int i=0; i<totalInstructions; ++i){
        instruction inst;
        fread(&inst,sizeof(instruction),1,fbin);
        code.push_back(inst);
    }
    
    if(DEBUG)cout<<"Read complete: "<<code.size()<<"\n";
    fclose(fbin);

    if(DEBUG){
        printf("\n-----------------StringConstsTable------------------\n");
        for(int j=0; j<totalStringOffset; j++){
            printf("%-4d| \"%s\"\n",j, stringConst_vm[j].c_str());
        }
        printf("\n-----------------NumConstsTable------------------\n");
        if(totalNumConstOffset)
        for(int j=0; j<totalNumConstOffset; j++){
            printf("%-4d| %lf\n",j, numConst_vm[j]);
        }
        printf("\n-----------------LibConstsTable------------------\n");
        if(totalLibFuncOffset)
        for(int j=0; j<totalLibFuncOffset; j++){
            printf("%-4d| \"%s\"\n",j, libFuncs_vm[j].c_str());
        }
        printf("\n-----------------UserFuncsTable------------------\n");
        if(totalUserFuncOffset)
        for(int j=0; j<totalUserFuncOffset; j++){
            printf("%-4d| \"%s\" address=%d | local=%d\n",j, userFuncs_vm[j].id.c_str(), userFuncs_vm[j].address, userFuncs_vm[j].localSize);
        }
    }

    return 0;
}

//------------------------------------------For debugging------------------------------------------
void printOpcode(vmopcode vop){
    switch (vop)
    {
    case assign_v:
        printf("assign ");
        break;
    case add_v:
        printf("add ");
        break;
    case sub_v:
        printf("sub ");
        break;
    case mul_v:
        printf("mul ");
        break;
    case div_v:
        printf("div ");
        break;
    case mod_v:
        printf("mod ");
        break;
    case jump_v:
        printf("jump ");
        break;
    case jeq_v:
        printf("jeq ");
        break;
    case jne_v:
        printf("jne ");
        break;
    case jle_v:
        printf("jle ");
        break;
    case jge_v:
        printf("jge ");
        break;
    case jlt_v:
        printf("jlt ");
        break;
    case jgt_v:
        printf("jgt ");
        break;
    case call_v:
        printf("call ");
        break;
    case pusharg_v:
        printf("pusharg ");
        break;
    case funcenter_v:
        printf("funcenter ");
        break;
    case funcexit_v:
        printf("funcexit ");
        break;
    case newtable_v:
        printf("newtable ");
        break;
    case tablegetelem_v:
        printf("tablegetelem ");
        break;
    case tablesetelem_v:
        printf("tablesetelem ");
        break;
    case nop_v:
        printf("nop ");
        break;
    default:
        printf("Error\n");
        break;
    }
}

void printVMarg(vmarg* v){
    if(!v) printf(" -NULL- ");
    switch (v->type)
    {
    case label_a:
        printf("label:");
        break;
    case global_a:
        printf("global:");
        break;
    case formal_a:
        printf("formal:");
        break;
    case local_a:
        printf("local:");
        break;
    case number_a:
        printf("number:");
        break;
    case string_a:
        printf("string:");
        break;
    case bool_a:
        printf("bool:");
        break;
    case nil_a:
        printf("nil:");
        break;
    case userfunc_a:
        printf("userfunc:");
        break;
    case libfunc_a:
        printf("libfunc:");
        break;
    case retval_a:
        printf("retval:() ");
        return;
    default:
        printf("(NULL)");
        return;
        break;
    }
    printf("%d ",v->val);
}