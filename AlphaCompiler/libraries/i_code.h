#include "quads.h"

expr* icode_assignment(expr* lvalue, expr* rvalue);

expr* icode_arithmetic_plus(expr* lvalue, expr* rvalue );

expr* icode_arithmetic_minus(expr* lvalue, expr* rvalue );

expr*  icode_arithmetic_i_div(expr* lvalue, expr* rvalue );

expr* icode_arithmetic_mul(expr* lvalue, expr* rvalue );

expr* icode_arithmetic_mod(expr* lvalue, expr* rvalue );

expr* icode_member_expression_index(expr* lvalue, expr* expression);

expr* icode_lvalue_callsufix(expr* lvalue, struct call_type* callsufix);

expr* icode_funcdef_call(SymbolTableEntry fdef, expr* elist);

struct call_type* icode_normcall(expr* elist);

struct call_type* icode_methodcall(char* id, expr* elist);

expr* icode_objdef_elist(expr* elist);

expr* icode_objdef_indexed(expr* indexed);

expr* icode_lvalue_incr(expr* lvalue);

expr* icode_lvalue_decr(expr* lvalue);

expr* icode_incr_lvalue(expr* lvalue);

expr* icode_decr_lvalue(expr* lvalue);

expr* icode_uminus(expr* e);

expr* icode_call_sqr_expr_sqr(expr* lvalue, expr* e);

expr* make_boolean_expr(expr* e);

expr* icode_relop(expr* e1, expr* e2, enum iopcode op);

expr* icode_and(expr* e1, expr* e2, unsigned int m_quad);

expr* icode_or(expr* e1, expr* e2, unsigned int m_quad);

expr* icode_not(expr* e);

void icode_bool_stmt(expr* e);

unsigned int icode_ifprefix(expr* e);

unsigned int icode_whilecond(expr* e);

void icode_whilestmt(unsigned int whilestart, unsigned int whilecond, struct stmt_t* statement);

struct for_struct* icode_forprefix(unsigned int M, expr* e);

void icode_forstmt(for_struct* forprefix,unsigned int N1,unsigned int N2,stmt_t* stmt,unsigned int N3);

stmt_t* icode_break();

stmt_t* icode_continue();