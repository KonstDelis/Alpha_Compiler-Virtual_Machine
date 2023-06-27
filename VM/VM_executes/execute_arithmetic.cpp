#include "../VM_dispatcher.hpp"
#include "../VM_env.hpp"
#include <assert.h>
#include "../ErrMsg.hpp"


arithmetic_func_t arithmeticFuncs[] = {

    add_impl,
    sub_impl,
    mul_impl,
    div_impl,
    mod_impl
};

comparison_func_t comparisonFuncs[] = {

    jle_impl,
    jge_impl,
    jlt_impl,
    jgt_impl
};


void execute_arithmetic(instruction* instr){

    avm_memcell* lv = avm_translate_operand(&instr->result, (avm_memcell*)0);
    avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);

    //assert(lv && (&stack[N-1] >= lv && lv > &stack[top] || lv == &retval));
    assert(rv1 && rv2);

    if(rv1->type != number_m || rv2->type != number_m){

        error_msg("not a number in arithmetic!",currLine);
        executionFinished = 1;
    } else {
        arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
        avm_memcellclear(lv);
        lv->type = number_m;
        lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);
    }
}

void execute_comparison(instruction* instr){

    avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);

    assert(rv1 && rv2);

    if(rv1->type != number_m || rv2->type != number_m){

        error_msg("not a number in arithmetic!",currLine);
        executionFinished = 1;
        return;
    } 
    
        bool op = comparisonFuncs[instr->opcode - jle_v](rv1->data.numVal,rv2->data.numVal);
        

        if(executionFinished!=1 && op)
            pc = instr->result.val;
    

}

static bool getEqResult(instruction* instr){

    assert(instr->result.type == label_a);

    avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);
    bool result = 0;

    if(rv1->type == undef_m || rv2->type == undef_m)
        error_msg("'undef' involved in equality!",currLine);
    else if(rv1->type == nil_m || rv2->type == nil_m)
        result = rv1->type == nil_m && rv2->type == nil_m;
    else if(rv1->type == bool_m || rv2->type == bool_m){
        result = (avm_tobool(rv1) == avm_tobool(rv2));
        if(DEBUG)std::cerr<<"entered one is bool || rv1(tobool)="<<avm_tobool(rv1)<<" || rv2(tobool)="<<avm_tobool(rv2)<<std::endl;
    }
    else if(rv1->type != rv2->type)
        error_msg(typeStrings[rv1->type]+" == "+typeStrings[rv2->type]+" is illegal!",currLine);
    else{


        switch(rv1->type){
            case number_m:{
            result = (rv1->data.numVal == rv2->data.numVal);
                break;
            }
            case string_m:{
                result = (rv1->data.strVal == rv2->data.strVal);
                break;
            }
            case libfunc_m:{
                result = (rv1->data.libfuncVal == rv2->data.libfuncVal);
                break;
            }
            case userfunc_m:{
                result = (rv1->data.funcVal == rv2->data.funcVal);
                break;
            }
            case bool_m:{
                assert(0);
                result = false;
                break;
            }
            case nil_m:{
                assert(0);
                result = false;
                break;
            }
            case undef_m:{
                assert(0);
                result = false;
                break;
            }
            case table_m:{
                assert(0);
                result = false;
                break;
            }
        }
    }
    if(DEBUG)std::cerr<<"Result = "<<result<<std::endl;
    return result;
}

void execute_jump(instruction* instr){

    assert(instr->result.val <= codeSize && instr->result.val > 0);

    pc = instr->result.val;

    if(DEBUG)std::cout<<"Jumping to "<<instr->result.val<<std::endl;

}

void execute_jeq(instruction* instr){
    if(!executionFinished && getEqResult(instr))
        pc = instr->result.val;
}

void execute_jne(instruction* instr){
    if(!executionFinished && !getEqResult(instr))
        pc = instr->result.val;
}