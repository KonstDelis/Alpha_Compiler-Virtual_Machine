#include "../VM_dispatcher.hpp"
#include "../VM_env.hpp"
#include <assert.h>
#include "../ErrMsg.hpp"

void execute_newtable(instruction* instr){

    avm_memcell* lv = avm_translate_operand(&instr->arg1, (avm_memcell*)0);

    assert(lv);

    avm_memcellclear(lv);

    lv->type = table_m;
    lv->data.tableVal = new avm_table();
    lv->data.tableVal->incrRef();

}

void execute_tablegetelem(instruction* instr){
    avm_memcell* value = avm_translate_operand(&instr->result, NULL);
    avm_memcell* table = avm_translate_operand(&instr->arg1, NULL);
    avm_memcell* index = avm_translate_operand(&instr->arg2, &ax);

    assert(table);
    assert(index);
    assert(value);
    avm_memcellclear(value);
    value->type = nil_m;
    if(table->type != table_m){
        error_msg("illegal use of '"+avm_tostring(table)+"', type '"+typeStrings[table->type]+"' cannot be used as a table", currLine);
    }
    else{
        avm_memcell* content = table->data.tableVal->getelem(index);
        if(content){
            avm_assign(value, content);
        }
    }



}

void execute_tablesetelem(instruction* instr){
    avm_memcell* value = avm_translate_operand(&instr->result, &bx);
    avm_memcell* table = avm_translate_operand(&instr->arg1, NULL);
    avm_memcell* index = avm_translate_operand(&instr->arg2, &ax);

    assert(table);
    assert(index);
    assert(value);

    if(table->type != table_m){
        error_msg("illegal use of '"+avm_tostring(table)+"', type '"+typeStrings[table->type]+"' cannot be used as a table", currLine);
    }
    else{
        table->data.tableVal->setelem(index, value);
    }
    
}