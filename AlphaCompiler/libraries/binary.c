#include "binary.h"

extern unsigned currInstruction;
extern instruction* instructions;
extern unsigned programVarOffset;


void createBinary(FILE* out){
    instruction inst;
    unsigned magicnumber = 340200501;
    double number;
    char* string;
    userfunc userfunc;
    char* libfunc;

    fwrite(&magicnumber,sizeof(magicnumber),1,out);


    fwrite(&programVarOffset,sizeof(unsigned),1,out);

    fwrite(&currStringConsts,sizeof(currStringConsts),1,out);
    for(int i = 0; i<currStringConsts; ++i){

        string = stringConsts[i];
        fwrite(string,strlen(string)+1,1,out);
    }

    fwrite(&currNumConsts,sizeof(currNumConsts),1,out);
    for(int i = 0; i<currNumConsts; ++i){

        number = numConsts[i];
        fwrite(&number,sizeof(number),1,out);
    }

    fwrite(&currUserFuncs,sizeof(currUserFuncs),1,out);
    for(int i = 0; i<currUserFuncs; ++i){

        userfunc = userFuncs[i];
        fwrite(&userfunc.address,sizeof(userfunc.address),1,out);
        fwrite(&userfunc.localSize,sizeof(userfunc.localSize),1,out);
        fwrite(userfunc.id,strlen(userfunc.id)+1,1,out);
        
    }

    fwrite(&currNamedLibFuncs,sizeof(currNamedLibFuncs),1,out);
    for(int i=0; i<currNamedLibFuncs; ++i){

        libfunc = namedLibfuncs[i];
        fwrite(libfunc,strlen(libfunc)+1,1,out);
    }

    fwrite(&currInstruction,sizeof(currInstruction),1,out);
    for(int i=0; i<currInstruction; ++i){
        inst = instructions[i];
        fwrite(&inst,sizeof(inst),1,out);
    }

    fclose(out);
}