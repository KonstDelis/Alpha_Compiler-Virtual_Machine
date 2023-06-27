#include "../AlphaCompiler/libraries/target_structs.h"
#include "VM_structs.hpp"
#ifndef DISPATCHER_HPP
#define DISPATCHER_HPP

#define AVM_MAX_INSTRUCTIONS (unsigned)nop_v
#define AVM_ENDING_PC codeSize

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

#define execute_jle execute_comparison
#define execute_jge execute_comparison
#define execute_jlt execute_comparison
#define execute_jgt execute_comparison

extern bool executionFinished;
extern unsigned pc;
extern unsigned currLine;
extern unsigned codeSize;
extern unsigned oldPC;

typedef void(*execute_func_t)(instruction*);

extern void execute_assign(instruction*);
extern void execute_add(instruction*);
extern void execute_sub(instruction*);
extern void execute_mul(instruction*);
extern void execute_div(instruction*);
extern void execute_mod(instruction*);
extern void execute_jump(instruction*);
extern void execute_jeq(instruction*);
extern void execute_jne(instruction*);
extern void execute_jle(instruction*);
extern void execute_jge(instruction*);
extern void execute_jlt(instruction*);
extern void execute_jgt(instruction*);
extern void execute_call(instruction*);
extern void execute_pusharg(instruction*);
extern void execute_funcenter(instruction*);
extern void execute_funcexit(instruction*);
extern void execute_newtable(instruction*);
extern void execute_tablegetelem(instruction*);
extern void execute_tablesetelem(instruction*);
extern void execute_nop(instruction*);

void execute_cycle(void);

void execute_arithmetic(instruction*);

void execute_comparison(instruction*);


typedef double (*arithmetic_func_t)(double x, double y);

typedef bool (*comparison_func_t)(double x, double y);

double add_impl (double x,double y);
double sub_impl (double x,double y);
double mul_impl (double x,double y);
double div_impl (double x,double y);
double mod_impl (double x,double y);

bool jle_impl (double x, double y);
bool jge_impl (double x, double y);
bool jlt_impl (double x, double y);
bool jgt_impl (double x, double y);


#endif
