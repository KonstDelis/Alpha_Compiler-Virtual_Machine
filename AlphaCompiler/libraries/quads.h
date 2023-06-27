#include <string.h>
#include <stdio.h>

#ifndef QUADS_H
#define QUADS_H

#include "SymTable.h"

#define EXPAND_SIZE 1024
#define CURR_SIZE total*sizeof(quad)
#define NEW_SIZE (EXPAND_SIZE*sizeof(quad)+CURR_SIZE)

enum iopcode {
    assign, add, sub,
    mul, i_div, mod,
    uminus, if_eq, if_noteq,
    if_lesseq, if_greatereq, if_less,
    if_greater, i_call, param,
    ret, getretval, funcstart,
    funcend, tablecreate,
    tablegetelem, tablesetelem,
    jump
};


enum expr_t{

    var_e, tableitem_e, 
    programfunc_e, libraryfunc_e, 
    arithexpr_e, boolexpr_e,
    assignexpr_e, newtable_e,
    constnum_e, constbool_e,
    conststring_e, nil_e
};


typedef struct expr{

    enum expr_t type;
    SymbolTableEntry sym;
    struct expr* index;
    double numConst;
    char* strConst;
    unsigned char boolConst;
    int truelist;
    int falselist;
    struct expr* next;
}expr;

typedef struct quad{

   enum iopcode op;
    expr* result;
    expr* arg1;
    expr* arg2;
    unsigned int label;
    int line;
    unsigned int taddress;

}quad;


struct call_type{

    expr* elist;
    unsigned char method;
    char* name;

};

typedef struct stmt_t {

    int breakList;
    int contList;
    int retList;

}stmt_t;

typedef struct for_struct {

    unsigned int test;
    unsigned int enter;

}for_struct;


void expand(void);

void emit(enum iopcode op, expr* arg1, expr* arg2, expr* result, unsigned int label, int line);

char* newtempname();

SymbolTableEntry newtemp();

void resettemp();

enum scopespace_t currscopespace(void);



unsigned currscopeoffset(void);

void inccurrscopeoffset(void);

void enterscopespace(void);

void exitscopespace(void);

void resetformalargsoffset(void);

void resetfunctionlocaloffset(void);

void restorecurrscopeoffset(unsigned n);

unsigned nextquadlabel(void);

void patchlabel(unsigned quadNo, unsigned label);

expr* lvalue_expr(SymbolTableEntry sym);

expr* newexpr(enum expr_t t);

expr* newexpr_conststring(char* s);

expr* emit_iftableitem(expr* e);

expr* member_item(expr* lv, char* name);

expr* make_indexed(expr* index, expr* value);

expr* make_call(expr* lv, expr* reversed_elist);

expr* newexpr_constbool(char value);

expr* newexpr_constarith(double value);

expr* reverse_elist(expr* elist);

void check_arith(expr* e, char* context);

int expr_is_int(expr* e);

void print_expr(FILE* fstream, expr* e);

void print_quads(FILE*);

stmt_t* make_stmt();

int newList(unsigned int i);

int mergelist(int l1, int l2);

void patchlist(int list, int label);

#endif