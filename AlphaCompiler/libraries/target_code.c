#include "target_code.h"
#include "utils.h"

unsigned totalNumConsts;
unsigned totalStringConsts;
unsigned totalnamedLibfuncs;
unsigned totalUserFuncs;
double* numConsts;
unsigned currNumConsts;
char** stringConsts;
unsigned currStringConsts;
char** namedLibfuncs;
unsigned currNamedLibFuncs;
userfunc* userFuncs;
unsigned currUserFuncs;


extern quad* quads;
extern int printSyntax;

instruction* instructions = (instruction*) 0;

unsigned currInstruction = 1;
unsigned totalInstruction = 1;
static unsigned i=0;

incomplete_jump* ij_head = NULL;
unsigned ij_total = 0;

void expand_instruction(void){
    assert(totalInstruction == currInstruction);
    instruction* p = (instruction*)malloc(NEW_SIZE_I);
    check_malloc(p,"Error: malloc for new quad failed. File: quads.c");
    if(instructions){
        memcpy(p, instructions, CURR_SIZE_I);
        free(instructions);
    }
    instructions = p;
    totalInstruction += EXPAND_SIZE;
}

void expand_conststr(){
    assert(totalStringConsts==currStringConsts);
    char** c = malloc(NEW_SIZE_SC);
    check_malloc(c, "malloc for constant string table expansion failed");
    if(stringConsts){
        memcpy(c, stringConsts, CURR_SIZE_SC);
        free(stringConsts);
    }
    stringConsts = c;
    totalStringConsts += EXPAND_SIZE;
}
void expand_constnum(){
    assert(totalNumConsts==currNumConsts);
    double* n = malloc(NEW_SIZE_NC);
    check_malloc(n, "malloc for constant number table expansion failed");
    if(numConsts){
        memcpy(n, numConsts, CURR_SIZE_NC);
        free(numConsts);
    }
    numConsts = n;
    totalNumConsts += EXPAND_SIZE;
}
void expand_libfunc(){
    assert(totalnamedLibfuncs==currNamedLibFuncs);
    char** l = malloc(NEW_SIZE_LF);
    check_malloc(l, "malloc for named library functions table expansion failed");
    if(namedLibfuncs){
        memcpy(l, namedLibfuncs, CURR_SIZE_LF);
        free(namedLibfuncs);
    }
    namedLibfuncs = l;
    totalnamedLibfuncs += EXPAND_SIZE;
}
void expand_usrfunc(){
    assert(totalUserFuncs==currUserFuncs);
    userfunc*  u= malloc(NEW_SIZE_UF);
    check_malloc(u, "malloc for user function table expansion failed");
    if(userFuncs){
        memcpy(u, userFuncs, CURR_SIZE_UF);
        free(userFuncs);
    }
    userFuncs = u;
    totalUserFuncs += EXPAND_SIZE;
}


unsigned consts_newstring(char* s){
    if(totalStringConsts==currStringConsts) expand_conststr();
    for(int j=0; j<currStringConsts; j++){
        if(strcmp(stringConsts[j],s)==0){
            return j;
        }
    }
    stringConsts[currStringConsts] = strdup(s);
    return currStringConsts++;
}
unsigned consts_newnumber(double n){
    if(totalNumConsts==currNumConsts) expand_constnum();
    for(int j=0; j<currNumConsts; j++){
        if(numConsts[j]==n){
            return j;
        }
    }
    numConsts[currNumConsts] = n;
    return currNumConsts++;
}
unsigned libfuncs_newused(char* s){
    if(totalnamedLibfuncs==currNamedLibFuncs) expand_libfunc();
    for(int j=0; j<currNamedLibFuncs; j++){
        if(strcmp(namedLibfuncs[j],s)==0){
            return j;
        }
    }
    namedLibfuncs[currNamedLibFuncs] = strdup(s);
    return currNamedLibFuncs++;
}
unsigned userfuncs_newfunc(SymbolTableEntry sym){
    if(totalUserFuncs==currUserFuncs) expand_usrfunc();
    for(int j=0; j<currUserFuncs; j++){
        if(strcmp(userFuncs[j].id,sym->name)==0){
            return j;
        }
    }
    userFuncs[currUserFuncs].address = sym->iaddress;
    userFuncs[currUserFuncs].localSize = sym->totalScopeOffset;
    userFuncs[currUserFuncs].id = strdup(sym->name);
    return currUserFuncs++;
}


void make_operand(expr* e, vmarg* arg){
    if(!e) {
        arg->type = -10;
        arg->val=0;
        return;
    }
    switch(e->type){

        case var_e:
        case tableitem_e:
        case arithexpr_e:
        case assignexpr_e:
        case boolexpr_e:
        case newtable_e: {

            assert(e->sym);
            arg->val = e->sym->offset;

            switch(e->sym->space){

                case programvar:    arg->type = global_a; break;
                case functionlocal: arg->type = local_a; break;
                case formalarg:     arg->type = formal_a; break;
                default:    assert(0);
            }
            break;
        }
        case constbool_e: {

            arg->val = e->boolConst;
            arg->type = bool_a; 
            break;
        }
        case conststring_e: {
            arg->val = consts_newstring(e->strConst);
            arg->type = string_a;
            break;
        }
        case constnum_e: {
            arg->val = consts_newnumber(e->numConst);
            arg->type = number_a;
            break;
        }
        case nil_e: {
            arg->type = nil_a;
            break;
        }
        case programfunc_e: {
            arg->type = userfunc_a;
            arg->val = userfuncs_newfunc(e->sym);
            break;
        }
        case libraryfunc_e: {
            arg->type = libfunc_a;
            arg->val = libfuncs_newused(e->sym->name);
            break;
        }
        default: assert(0);
    }
}

void make_numberoperand(vmarg* arg, double val){

    arg->val = consts_newnumber(val);
    arg->type = number_a;
}

void make_booloperand(vmarg* arg, unsigned val){

    arg->val = val;
    arg->type = bool_a;
}

void make_retvaloperand(vmarg* arg){

    arg->type = retval_a;
}

void add_incomplete_jump(unsigned instrNo, unsigned iaddress){

    incomplete_jump* ij = malloc(sizeof(incomplete_jump));

    ij->instrNo = instrNo;
    ij->iaddress = iaddress;
    ij->next = ij_head;
    ij_head = ij;
    ij_total++;
}

void patch_incomplete_jumps(){

   
}

unsigned nextinstructionlabel(){

   return currInstruction; 
}

void emit_instruction(instruction t){


    if(currInstruction == totalInstruction) expand_instruction();
    instruction *p = instructions + currInstruction++;
    p->opcode=t.opcode;
    p->arg1 = t.arg1;
    p->arg2 = t.arg2;
    p->result = t.result;
    p->srcLine = t.srcLine;
}

void reset_operand(vmarg* arg){

    arg = (vmarg*)0;
}

unsigned currprocessedquad(){
    return i;
}

//--------------------------------------------Generators-----------------------------------------------------
void generate(vmopcode op,quad* q){

    instruction t;
    t.opcode = op;
    make_operand(q->arg1,&t.arg1);
    make_operand(q->arg2,&t.arg2);
    make_operand(q->result,&t.result);
    q->taddress = nextinstructionlabel();
    t.srcLine = q->line;
    emit_instruction(t);
    
}

void generate_ADD(quad* q){ generate(add_v,q);}

void generate_SUB(quad* q){ generate(sub_v,q);}

void generate_MUL(quad* q){ generate(mul_v,q);}

void generate_UMINUS(quad* q){
    q->arg2 = newexpr_constarith(-1);
    generate(mul_v,q);
}

void generate_DIV(quad* q){ generate(div_v,q);}

void generate_MOD(quad* q){ generate(mod_v,q);}

void generate_NEWTABLE(quad* q){ generate(newtable_v,q);}

void generate_TABLEGETELEM(quad* q){ generate(tablegetelem_v,q);}

void generate_TABLESETELEM(quad* q){ generate(tablesetelem_v,q);}

void generate_ASSIGN(quad* q){ generate(assign_v,q);}

void generate_NOP(){ 
    instruction t;
    t.opcode = nop_v;
    t.srcLine = 0;
    emit_instruction(t);
}

void generate_relational(vmopcode op, quad* q){

    instruction t;
    t.opcode = op;
    make_operand(q->arg1, &t.arg1);
    make_operand(q->arg2, &t.arg2);

    t.result.type = label_a;

    t.result.val = q->label;
    t.srcLine = q->line;
    q->taddress = nextinstructionlabel();
    emit_instruction(t);
}

void generate_JUMP(quad* q){ generate_relational(jump_v,q);}
void generate_IF_EQ(quad* q){ generate_relational(jeq_v,q);}
void generate_IF_NOTEQ(quad* q){ generate_relational(jne_v,q);}
void generate_IF_GREATER(quad* q){ generate_relational(jgt_v,q);}
void generate_IF_GREATEREQ(quad* q){ generate_relational(jge_v,q);}
void generate_IF_LESS(quad* q){ generate_relational(jlt_v,q);}
void generate_IF_LESSEQ(quad* q){ generate_relational(jle_v,q);}

void generate_PARAM(quad* q){

    q->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = pusharg_v;
    make_operand(q->arg1,&t.arg1);
    t.arg2.type=-10;
    t.arg2.val=0;
    t.result.type=-10;
    t.result.val=0;
    t.srcLine = q->line;
    emit_instruction(t);
}

void generate_CALL(quad* q){

    q->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = call_v;
    make_operand(q->arg1,&t.arg1);
    t.arg2.type = -10;
    t.arg2.val=0;
    t.result.type = -10;
    t.result.val = 0;
    t.srcLine = q->line;
    emit_instruction(t);
}

void generate_GETRETVAL(quad* q){

    q->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = assign_v;
    make_operand(q->result,&t.result);
    make_retvaloperand(&t.arg1);
    t.arg2.type = -10;
    t.arg2.val=0;
    t.srcLine = q->line;
    emit_instruction(t);
}

void generate_FUNCSTART(quad* q){

    q->taddress = nextinstructionlabel();

    instruction t;
    t.opcode = funcenter_v;
    make_operand(q->arg1,&t.result);
    t.arg1.type = -10;
    t.arg1.val = 0;
    t.arg2.type = -10;
    t.arg2.val = 0;
    t.srcLine = q->line;
    emit_instruction(t);
}

void generate_RETURN(quad* q){

    q->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = assign_v;
    make_retvaloperand(&t.result);
    make_operand(q->result,&t.arg1);
    t.arg2.type = -10;
    t.arg2.val = 0;
    t.srcLine = q->line;
    emit_instruction(t);
}

void generate_FUNCEND(quad* q){

    q->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = funcexit_v;
    make_operand(q->arg1,&t.result);
    t.arg1.type = -10;
    t.arg1.val = 0;
    t.arg2.type = -10;
    t.arg2.val = 0;
    t.srcLine = q->line;
    emit_instruction(t);
}

generator_func_t generators[] = {

    generate_ASSIGN,
    generate_ADD,
    generate_SUB,
    generate_MUL,
    generate_DIV,
    generate_MOD,
    generate_UMINUS,
    generate_IF_EQ,
    generate_IF_NOTEQ,
    generate_IF_LESSEQ,
    generate_IF_GREATEREQ,
    generate_IF_LESS,
    generate_IF_GREATER,
    generate_CALL,
    generate_PARAM,
    generate_RETURN,
    generate_GETRETVAL,
    generate_FUNCSTART,
    generate_FUNCEND,
    generate_NEWTABLE,
    generate_TABLEGETELEM,
    generate_TABLESETELEM,
    generate_JUMP,
    generate_NOP
};
//-----------------------------------------------------------------------------------------------------------

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
        printf("-NULL- ");
        return;
    }
    printf("%d ",v->val);
}

void generate_instr(void){
    if(printSyntax)printf("Start target code \n");
    for(i = 1; i<nextquadlabel(); ++i){
        (*generators[quads[i].op])(quads+i);

        if(printSyntax){/*For debugging*/
            printf("%-4d| ",i);
            printOpcode(instructions[i].opcode);
            printVMarg(&instructions[i].arg1);
            printVMarg(&instructions[i].arg2);
            printVMarg(&instructions[i].result);
            printf("\n");
            fflush(stdout);
        }
    }
    if(printSyntax){/*For debugging*/
        printf("\n-----------------StringConstsTable------------------\n");
        if(stringConsts)
        for(int j=0; j<currStringConsts; j++){
            printf("%-4d| \"%s\"\n",j, stringConsts[j]);
        }
        printf("\n-----------------NumConstsTable------------------\n");
        if(numConsts)
        for(int j=0; j<currNumConsts; j++){
            printf("%-4d| %lf\n",j, numConsts[j]);
        }
        printf("\n-----------------LibConstsTable------------------\n");
        if(namedLibfuncs)
        for(int j=0; j<currNamedLibFuncs; j++){
            printf("%-4d| \"%s\"\n",j, namedLibfuncs[j]);
        }
        printf("\n-----------------UserFuncsTable------------------\n");
        if(userFuncs)
        for(int j=0; j<currUserFuncs; j++){
            printf("%-4d| \"%s\" address=%d | local=%d\n",j, userFuncs[j].id, userFuncs[j].address, userFuncs[j].localSize);
        }
    }
}
