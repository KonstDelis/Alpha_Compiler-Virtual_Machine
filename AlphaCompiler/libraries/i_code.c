#include "i_code.h"
#include "utils.h"
#include "quads.h"
extern int yylineno;
extern unsigned int currQuad;
extern int yywarning(char*);
extern int yyerror(char*);

expr* icode_assignment(expr* lvalue, expr* rvalue){
    expr* result;
    if(lvalue->type == tableitem_e){
        emit(tablesetelem, lvalue, lvalue->index, rvalue, 0, yylineno);
        result = emit_iftableitem(lvalue);
        result->type = assignexpr_e;
    }
    else{
        emit(assign, rvalue, NULL, lvalue, 0,yylineno);
        result = newexpr(assignexpr_e);
        result->sym = newtemp();
        emit(assign,lvalue,NULL,result, 0,yylineno);
    }
    return result;
}


expr* icode_arithmetic_plus(expr*lvalue, expr* rvalue ){
    expr* result;
    check_arith(lvalue, "+");
	check_arith(rvalue, "+");
	expr* e = newexpr(arithexpr_e);
	e->sym = newtemp();
	emit(add, lvalue, rvalue, e, 0, yylineno);
	result= e;
	return result;			
}

expr* icode_arithmetic_minus(expr*lvalue, expr* rvalue ){
    expr* result;
    check_arith(lvalue, "-");
	check_arith(rvalue, "-");
	expr* e = newexpr(arithexpr_e);
	e->sym = newtemp();
	emit(sub, lvalue, rvalue, e, 0, yylineno);
	result= e;
	return result;			
}


expr* icode_arithmetic_mul(expr*lvalue, expr* rvalue ){
    expr* result;
    check_arith(lvalue, "*");
	check_arith(rvalue, "*");
	expr* e = newexpr(arithexpr_e);
	e->sym = newtemp();
	emit(mul, lvalue, rvalue, e, 0,yylineno);
	result= e;
	return result;			
}


expr* icode_arithmetic_i_div(expr*lvalue, expr* rvalue ){
    expr* result;
    check_arith(lvalue, "/");
	check_arith(rvalue, "/");
	expr* e = newexpr(arithexpr_e);
	e->sym = newtemp();
	emit(i_div, lvalue, rvalue, e, 0,yylineno);
	result= e;
	return result;			
}


expr* icode_arithmetic_mod(expr*lvalue, expr* rvalue ){
    expr* result;                                      
    check_arith(lvalue, "%% lvalue");
	check_arith(rvalue, "%% rvalue");
	expr* e = newexpr(arithexpr_e);
	e->sym = newtemp();

    if (!expr_is_int(lvalue))
        yywarning("operand of modulo is not an integer, implicit cast to integer.\n");

    if (!expr_is_int(rvalue))
        yywarning("operand of modulo is not an integer, implicit cast to integer.\n");
    
	emit(mod, lvalue, rvalue, e, 0, yylineno);
	result= e;
	return result;			
}

expr* icode_member_expression_index(expr* lvalue, expr* expression){
    lvalue = emit_iftableitem(lvalue);
    expr* t = newexpr(tableitem_e);
    t->sym = lvalue->sym;
    t->index = expression;
    return t;
}

expr* icode_lvalue_callsufix(expr* lvalue, struct call_type* callsufix){
    lvalue = emit_iftableitem(lvalue);
    if(callsufix->method){
    expr* t = lvalue;
    lvalue = emit_iftableitem(member_item(t,callsufix->name));
    if(callsufix->elist){
        t->next = callsufix->elist;
        callsufix->elist = t;
    }else
    callsufix->elist = t;

    }
    callsufix->elist = reverse_elist(callsufix->elist);
    return make_call(lvalue,callsufix->elist);
}

expr* icode_funcdef_call(SymbolTableEntry fdef, expr* elist){
    expr* func = newexpr(programfunc_e);
    func->sym = fdef;
    elist = reverse_elist(elist);
    return make_call(func,elist);
}

struct call_type* icode_normcall(expr* elist){
    struct call_type* t = malloc(sizeof(struct call_type));
    check_malloc(t, "Error: malloc for new struct call_type filed. File: syntax_analyzer.y");
    t->elist = elist;
    t->method = 0;
    t->name = (char*)0;
    return t;
}

struct call_type* icode_methodcall(char* id, expr* elist){
    struct call_type* t = malloc(sizeof(struct call_type));
    check_malloc(t, "Error: malloc for new struct call_type filed. File: syntax_analyzer.y");
    t->elist = elist;
    t->method = 1;
    t->name = id;
    return t;
}

expr* icode_objdef_elist(expr* elist){
    expr* t = newexpr(newtable_e);
    t->sym = newtemp();
    emit(tablecreate, t, NULL, NULL,0,yylineno);
    for(int i=0; elist!=NULL; elist=elist->next){
        emit(tablesetelem, t, newexpr_constarith(i++), elist,0,yylineno);
    }
    return t;
}

expr* icode_objdef_indexed(expr* indexed){
    expr* t = newexpr(newtable_e);
    t->sym = newtemp();
    emit(tablecreate, t, NULL, NULL,0,yylineno);
    for(int i=0; indexed!=NULL; indexed=indexed->next){
        emit(tablesetelem, t, indexed->index, indexed,0,yylineno);
    }
    return t;
}

expr* icode_lvalue_incr(expr* lvalue){

    expr* result;
    check_arith(lvalue,"lvalue++");
    result = newexpr(var_e);
    result->sym = newtemp();

    if(lvalue->type == tableitem_e){
        expr* val = emit_iftableitem(lvalue);
        emit(assign,val,NULL,result,0,yylineno);
        emit(add,val,newexpr_constarith(1),val,0,yylineno);
        emit(tablesetelem,lvalue,lvalue->index,val,0,yylineno);
    }else{

        emit(assign,lvalue,NULL,result,0,yylineno);
        emit(add,lvalue,newexpr_constarith(1),lvalue,0,yylineno);
    }

    return result;

}

expr* icode_lvalue_decr(expr* lvalue){

    expr* result;
    check_arith(lvalue,"lvalue--");
    result = newexpr(var_e);
    result->sym = newtemp();

    if(lvalue->type == tableitem_e){
        expr* val = emit_iftableitem(lvalue);
        emit(assign,val,NULL,result,0,yylineno);
        emit(sub,val,newexpr_constarith(1),val,0,yylineno);
        emit(tablesetelem,lvalue,lvalue->index,val,0,yylineno);
    }else{

        emit(assign,lvalue,NULL,result,0,yylineno);
        emit(sub,lvalue,newexpr_constarith(1),lvalue,0,yylineno);
    }

    return result;

}

expr* icode_incr_lvalue(expr* lvalue){

    expr* result;

    check_arith(lvalue,"++lvalue");

    if(lvalue->type == tableitem_e){

        result = emit_iftableitem(lvalue);
        emit(add,result,newexpr_constarith(1),result,0,yylineno);
        emit(tablesetelem,lvalue,lvalue->index,result,0,yylineno);
    }else{

        emit(add,lvalue,newexpr_constarith(1),lvalue,0,yylineno);
        result = newexpr(arithexpr_e);
        result->sym = newtemp();
        emit(assign,lvalue,NULL,result,0,yylineno);
    }

    return result;
}

expr* icode_decr_lvalue(expr* lvalue){

    expr* result;

    check_arith(lvalue,"--lvalue");

    if(lvalue->type == tableitem_e){

        result = emit_iftableitem(lvalue);
        emit(sub,result,newexpr_constarith(1),result,0,yylineno);
        emit(tablesetelem,lvalue,lvalue->index,result,0,yylineno);
    }else{

        emit(sub,lvalue,newexpr_constarith(1),lvalue,0,yylineno);
        result = newexpr(arithexpr_e);
        result->sym = newtemp();
        emit(assign,lvalue,NULL,result,0,yylineno);
    }

    return result;
}

expr* icode_uminus(expr* e){

    expr* result;

    check_arith(e,"uminus");
    result = newexpr(arithexpr_e);
    result->sym = newtemp();
    emit(uminus,e,NULL,result,0,yylineno);

    return result;
}

expr* icode_call_sqr_expr_sqr(expr* lvalue, expr* e){

    expr* result;

    lvalue = emit_iftableitem(lvalue);
    result = newexpr(tableitem_e);
    result->sym = lvalue->sym;
    result->index = e;

    return result;

}

/*-------------------------------------------------------------------------------------------------*/

expr* make_boolean_expr(expr* e){
    if(e->type!=boolexpr_e){
        expr* result = newexpr(boolexpr_e);
        if(e->type == libraryfunc_e || e->type == programfunc_e || e->type == newtable_e){
            result->sym = newtemp();
            emit(assign, newexpr_constbool(TRUE),NULL,result,0,yylineno);
        }
        else if(e->type == nil_e){
            emit(assign, newexpr_constbool(FALSE),NULL,result,0,yylineno);
        }
        else if(e->type == constnum_e){
            result->sym = newtemp();
            if(e->numConst==0)
                emit(assign, newexpr_constbool(FALSE),NULL,result,0,yylineno);
            else
                emit(assign, newexpr_constbool(TRUE),NULL,result,0,yylineno);
        }
        else if(e->type == conststring_e){
            result->sym = newtemp();
            if(strcmp(e->strConst,"")==0)
                emit(assign, newexpr_constbool(FALSE),NULL,result,0,yylineno);
            else
                emit(assign, newexpr_constbool(TRUE),NULL,result,0,yylineno);
        }
        else if(e->type == var_e || e->type == assignexpr_e || e->type == arithexpr_e){
            e->truelist = newList(nextquadlabel());
            e->falselist = newList(nextquadlabel()+1);
            emit(if_eq, e, newexpr_constbool(TRUE), NULL, 0, yylineno);
            emit(jump, NULL,NULL,NULL,0,yylineno);
            return e;
        }
        else if(e->type == constbool_e){
            result->truelist = newList(nextquadlabel());
            result->falselist = newList(nextquadlabel()+1);
            emit(if_eq, newexpr_constbool(e->boolConst?TRUE:FALSE), newexpr_constbool(TRUE), NULL, 0, yylineno);
            emit(jump, NULL,NULL,NULL,0,yylineno);
            return result;
        }
        else{
            yyerror("Unexpected error");
        }
        result->truelist = newList(nextquadlabel());
        result->falselist = newList(nextquadlabel()+1);
        emit(if_eq, result, newexpr_constbool(TRUE), NULL, 0, yylineno);
        emit(jump, NULL,NULL,NULL,0,yylineno);
        return result;
    }
    return e;
}

expr* icode_relop(expr* e1, expr* e2, enum iopcode op){
    expr* result;
    result = newexpr(boolexpr_e);
    result->sym = newtemp();

    if( (op!=if_eq && op!=if_noteq) &&
        (e1->type == constbool_e || e2->type == constbool_e ||
        e1->type == boolexpr_e || e2->type == boolexpr_e) ){
            yyerror("Relative operations with boolean values are not allowed in alpha");
    }
    
    result->truelist = newList(nextquadlabel());
    result->falselist = newList(nextquadlabel()+1);

    emit(op, e1,e2, NULL, 0, yylineno);
    emit(jump, NULL, NULL, NULL, 0, yylineno);
    return result;
}

expr* icode_not(expr* e){
    expr* result;
    e = make_boolean_expr(e);
    result =newexpr(boolexpr_e);
    result->sym = e->sym;
    result->falselist = e->truelist;
    result->truelist = e->falselist;
    return result;
}

expr* icode_and(expr* e1, expr* e2, unsigned int m_quad){
    
    expr* result = newexpr(boolexpr_e);
    result->sym = newtemp();
    e2 = make_boolean_expr(e2);
    patchlist(e1->truelist, m_quad);
    result->falselist = mergelist(e1->falselist, e2->falselist);
    result->truelist = e2->truelist;
    return result;
}

expr* icode_or(expr* e1, expr* e2, unsigned int m_quad){
    expr* result = newexpr(boolexpr_e);
    result->sym = newtemp();
    e2 = make_boolean_expr(e2);
    patchlist(e1->falselist, m_quad);
    result->truelist = mergelist(e1->truelist, e2->truelist);
    result->falselist = e2->falselist;
    return result;
}

void icode_bool_stmt(expr* e){
    if(e->type == boolexpr_e){
        if(!e->sym || e->sym->name[0]!='_') e->sym = newtemp();
        patchlist(e->truelist, nextquadlabel());
        emit(assign, newexpr_constbool(TRUE), NULL, e, 0, yylineno);
        emit(jump,NULL,NULL,NULL,nextquadlabel()+2, yylineno);
        patchlist(e->falselist,nextquadlabel());
        emit(assign, newexpr_constbool(FALSE), NULL, e, 0, yylineno);
    }
    return ;
}

unsigned int icode_ifprefix(expr* e){

   unsigned int result;
   icode_bool_stmt(e); 
   emit(if_eq,e,newexpr_constbool(1),NULL,nextquadlabel()+2,yylineno);
   result = nextquadlabel();
   emit(jump,NULL,NULL,NULL,0,yylineno);

   return result;
}

unsigned int icode_whilecond(expr* e){

    unsigned int result;

    icode_bool_stmt(e);
    emit(if_eq,e,newexpr_constbool(1),NULL,nextquadlabel()+2,yylineno);
    result = nextquadlabel();
    emit(jump,NULL,NULL,NULL,0,yylineno);


    return result;
}

void icode_whilestmt(unsigned int whilestart, unsigned int whilecond, struct stmt_t* statement){


    statement = malloc(sizeof(struct stmt_t));
    emit(jump,NULL,NULL,NULL,whilestart,yylineno);
    patchlabel(whilecond,nextquadlabel());
    patchlist(statement->breakList,nextquadlabel());
    patchlist(statement->contList,whilestart);

}

struct for_struct* icode_forprefix(unsigned int M, expr* e){

    for_struct* result;

    icode_bool_stmt(e);
    result = malloc(sizeof(struct for_struct));
    result->test = M;
    result->enter = nextquadlabel();
    emit(if_eq,e,newexpr_constbool(1),NULL,0,yylineno);


    return result;
}

void icode_forstmt(for_struct* forprefix,unsigned int N1,unsigned int N2,stmt_t* stmt,unsigned int N3){

    stmt = malloc(sizeof(struct stmt_t));
    patchlabel(forprefix->enter,N2+1);
    patchlabel(N1,nextquadlabel());
    patchlabel(N2,forprefix->test);
    patchlabel(N3,N1+1);

    if(stmt->breakList)patchlist(stmt->breakList,nextquadlabel());
    if(stmt->contList)patchlist(stmt->contList,N1+1);

}

stmt_t* icode_break(){

    stmt_t* result;

    result = make_stmt();
    result->breakList = newList(nextquadlabel());
    emit(jump,NULL,NULL,NULL,0,yylineno);

    return result;
}

stmt_t* icode_continue(){

    stmt_t* result;

    result = make_stmt();
    result->contList = newList(nextquadlabel());
    emit(jump,NULL,NULL,NULL,0,yylineno);

    return result;
}