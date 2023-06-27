#include <stdlib.h>
#ifndef TARGET_CODE_H
#define TARGET_CODE_H
#include <stdio.h>
#include <string.h>
#include "SymTable.h"
#include "quads.h"
#include "target_structs.h"

#define EXPAND_SIZE 1024
#define CURR_SIZE_I totalInstruction*sizeof(instruction)
#define NEW_SIZE_I (EXPAND_SIZE*sizeof(instruction)+CURR_SIZE_I)

#define CURR_SIZE_LF totalnamedLibfuncs*sizeof(char*)
#define NEW_SIZE_LF (EXPAND_SIZE*sizeof(char*)+CURR_SIZE_LF)
#define CURR_SIZE_UF totalUserFuncs*sizeof(userfunc)
#define NEW_SIZE_UF (EXPAND_SIZE*sizeof(userfunc)+CURR_SIZE_UF)
#define CURR_SIZE_NC totalNumConsts*sizeof(double)
#define NEW_SIZE_NC (EXPAND_SIZE*sizeof(double)+CURR_SIZE_NC)
#define CURR_SIZE_SC totalStringConsts*sizeof(char*)
#define NEW_SIZE_SC (EXPAND_SIZE*sizeof(char*)+CURR_SIZE_SC)

extern void check_malloc(void*,char*);

typedef struct userfunc{
    unsigned address;
    unsigned localSize;
    char* id;

}userfunc;

typedef struct incomplete_jump{

    unsigned instrNo;
    unsigned iaddress;
    struct incomplete_jump* next;


}incomplete_jump;

extern unsigned totalNumConsts;
extern unsigned totalStringConsts;
extern unsigned totalnamedLibfuncs;
extern unsigned totalUserFuncs;
extern double* numConsts;
extern unsigned currNumConsts;
extern char** stringConsts;
extern unsigned currStringConsts;
extern char** namedLibfuncs;
extern unsigned currNamedLibFuncs;
extern userfunc* userFuncs;
extern unsigned currUserFuncs;

//----------------------------------------------------------------------

// enum avm_memcell_t {
//     number_m,
//     string_m,
//     bool_m,
//     table_m,
//     userfunc_m,
//     libfunc_m,
//     nil_m,
//     undef_m
// }typedef avm_memcell_t;

// struct avm_table;
// typedef struct avm_memcell{
//     avm_memcell_t type;
//     union{
//         double numVal;
//         char* strVal;
//         unsigned char boolVal;
//         struct avm_table* tableVal;
//         unsigned funcVal;
//         char* libfuncVal;
//     }data;

// }avm_memcell;

// avm_memcell stack[AVM_STACKSIZE];

//-----------------------------------------------------------------

unsigned consts_newstring(char* s);
unsigned consts_newnumber(double n);
unsigned libfuncs_newused(char* s);
unsigned userfuncs_newfunc(SymbolTableEntry sym);
void expand_conststr();
void expand_constnum();
void expand_libfunc();
void expand_usrfunc();

void make_operand(expr* e, vmarg* arg);

void make_numberoperand(vmarg* arg, double val);
void make_booloperand(vmarg* arg, unsigned val);
void make_retvaloperand(vmarg* arg);

void add_incomplete_jump(unsigned instrNo, unsigned iaddress);
void patch_incomplete_jumps();

void generate(vmopcode op,quad* q);

unsigned nextinstructionlabel();
unsigned currprocessedquad();

void generate_ADD(quad* q);
void generate_SUB(quad* q);
void generate_MUL(quad* q);
void generate_DIV(quad* q);
void generate_MOD(quad* q);
void generate_UMINUS(quad* q);
void generate_NEWTABLE(quad* q);
void generate_TABLEGETELEM(quad* q);
void generate_TABLESETELEM(quad* q);
void generate_ASSIGN(quad* q);
void generate_NOP();
void generate_relational(vmopcode op, quad* q);
void generate_JUMP(quad* q);
void generate_IF_EQ(quad* q);
void generate_IF_NOTEQ(quad* q);
void generate_IF_GREATER(quad* q);
void generate_IF_GREATEREQ(quad* q);
void generate_IF_LESS(quad* q);
void generate_IF_LESSEQ(quad* q);
void generate_PARAM(quad* q);
void generate_CALL(quad* q);
void generate_GETRETVAL(quad* q);
void generate_FUNCSTART(quad* q);
void generate_FUNCEND(quad* q);
void generate_RETURN(quad* q);

void reset_operand(vmarg* arg);

void emit_instruction(instruction t);

void expand_instruction(void);

typedef void (*generator_func_t)(quad*);

void generate_instr(void);
#endif