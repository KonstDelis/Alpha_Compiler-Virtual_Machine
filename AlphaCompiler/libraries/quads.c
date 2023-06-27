#include "quads.h"
#include "utils.h"

extern int scope;
extern int yylineno;
extern SymTable_T oSymTable;
extern int yyerror(char*);
extern void checkErrors();

unsigned total = 1;
unsigned int currQuad = 1;
int tempcounter = 0;
unsigned programVarOffset = 0;
unsigned functionLocalOffset = 0;
unsigned formalArgOffset = 0;
unsigned scopeSpaceCounter = 1;

quad* quads = (quad*) 0;


void expand(void){
    assert(total == currQuad);
    quad* p = (quad*)malloc(NEW_SIZE);
    check_malloc(p,"Error: malloc for new quad failed. File: quads.c");
    if(quads){
        memcpy(p, quads, CURR_SIZE);
        free(quads);
    }
    quads = p;
    total += EXPAND_SIZE;
}

void emit(enum iopcode op, expr* arg1, expr* arg2, expr* result, unsigned int label, int line){

    if(currQuad == total) expand();
    quad *p = quads + currQuad++;
    p->op=op;
    p->arg1 = arg1;
    p->arg2 = arg2;
    p->result = result;
    p->label = label;
    p->line = line;
}

char* newtempname(){

    char* tempname = malloc(sizeof(char)*100);
    check_malloc(tempname,"Error: malloc for new tempname. File: quads.c");
    sprintf(tempname, "_t%d",tempcounter++);

    return tempname;
}

SymbolTableEntry newtemp(){

    char* name = newtempname();
    SymbolTableEntry sym = SymTable_lookup(oSymTable,name,currscopespace(),ALL_TYPES);

    if(sym == NULL) {
        sym = SymTable_insert(oSymTable,name,NULL,scope?LOCAL:GLOBAL,yylineno,scope,currscopespace(),currscopeoffset());
        inccurrscopeoffset();
        return sym;
    }
    else
        return sym;
    
}

void resettemp(){

    tempcounter = 0;
}

enum scopespace_t currscopespace(void){

    if(scopeSpaceCounter == 1) return programvar;
    else if(scopeSpaceCounter % 2 == 0) return formalarg;
    else return functionlocal;
} 

unsigned currscopeoffset(void){

    switch (currscopespace()) {
        case programvar : return programVarOffset;
        case functionlocal : return functionLocalOffset;
        case formalarg : return formalArgOffset;
        default : assert(0);
    }
}

void inccurrscopeoffset(void){

    switch (currscopespace()) {
        case programvar : ++programVarOffset; break;
        case functionlocal : ++functionLocalOffset; break;
        case formalarg : ++formalArgOffset; break;
        default : assert(0);
    }
}

void enterscopespace(void){
    ++scopeSpaceCounter;
}

void exitscopespace(void){
    assert(scopeSpaceCounter>1);
    --scopeSpaceCounter;
}

void resetformalargsoffset(void){

    formalArgOffset = 0;
}

void resetfunctionlocaloffset(void){

    functionLocalOffset = 0;
}

void restorecurrscopeoffset(unsigned n){

    switch(currscopespace()){
        case programvar : programVarOffset = n; break;
        case functionlocal : functionLocalOffset = n; break;
        case formalarg : formalArgOffset = n; break;
        default : assert(0);

    }
}

unsigned nextquadlabel(void){

    return currQuad;
}

void patchlabel(unsigned quadNo, unsigned label){

    assert(quadNo<currQuad);
    quads[quadNo].label = label;
}

//---------------------------------------------------------------------------------------------------------------------

expr* lvalue_expr(SymbolTableEntry sym){
    checkErrors();
    assert(sym);
    expr* e = (expr*) malloc(sizeof(expr));
    check_malloc(e,"Error: malloc for new lvalue_expr. File: quads.c");
    memset(e,0,sizeof(expr));

    e->next = (expr*)0;
    e->sym = sym;

    switch(sym->type){
        case var_s : e->type = var_e; break;
        case programfunc_s : e->type = programfunc_e; break;
        case libraryfunc_s : e->type = libraryfunc_e; break;
        default : assert(0);
    }

    return e;
}

expr* newexpr(enum expr_t t){

    expr* e = (expr*)malloc(sizeof(expr));
    check_malloc(e,"Error: malloc for new expression. File: quads.c");
    memset(e,0,sizeof(expr));
    e->type = t;
    return e;
}

expr* newexpr_conststring(char* s){

    expr* e = newexpr(conststring_e);
    e->strConst = strdup(s);
    return e;
}

expr* newexpr_constbool(char value){
    assert(value==0 || value==1);
    expr* e = newexpr(constbool_e);
    e->boolConst=value;
    return e;
}

expr* newexpr_constarith(double value){
    expr* e = newexpr(constnum_e);
    e->numConst = value;
    return e;
}

expr* emit_iftableitem(expr* e){

    if(e->type != tableitem_e) return e;
    else{
        expr* result = newexpr(var_e);
        result->sym = newtemp();
        emit(tablegetelem,e,e->index,result,0,yylineno);
        return result;
    }

}

expr* member_item(expr* lv, char* name){

    lv = emit_iftableitem(lv);
    expr* ti = newexpr(tableitem_e);
    ti->sym = lv->sym;
    ti->index = newexpr_conststring(name);
    return ti;
}

expr* make_indexed(expr* index, expr* value){
    value->index=index;
    return value;
}

expr* make_call(expr* lv, expr* reversed_elist){

    expr* func = emit_iftableitem(lv);
    if(lv->sym->type==programfunc_s)
        func->type=programfunc_e;
    else if(lv->sym->type==libraryfunc_s)
        func->type=libraryfunc_e;
    else
        func->type=var_e;
    while(reversed_elist){
        emit(param,reversed_elist,NULL,NULL,0,yylineno);
        reversed_elist = reversed_elist->next;
    }
    emit(i_call,func,NULL,NULL,0,yylineno);
    expr* result = newexpr(var_e);
    result->sym = newtemp();
    emit(getretval,NULL,NULL,result,0,yylineno);
    return result;
}

//--------------------------------------------------------------------------------------------------------------

void check_arith(expr* e, char* context){

    if(e->type == constbool_e ||
       e->type == conststring_e ||
       e->type == nil_e ||
       e->type == newtable_e ||
       e->type == programfunc_e ||
       e->type == libraryfunc_e ||
       e->type == boolexpr_e) yyerror(context);
}

int expr_is_int(expr* e){
    return ( e->type!=constnum_e || ((e->numConst - (int)e->numConst) == 0.0) ) ? TRUE:FALSE;
}

//--------------------------------------------------------------------------------------------------------------

expr* reverse_elist(expr* elist){
    expr* prev = NULL, *current = elist, *next=NULL;
    while(current!=NULL){
        next=current->next;
        current->next = prev;
        prev=current;
        current=next;
    }
    return prev;
}

//--------------------------------------------------------------------------------------------------------------


void print_op(FILE* fstream, enum iopcode op){
    switch (op)
    {
    case assign:
        fprintf(fstream, "%-12s","ASSIGN");
        break;
    case add:
        fprintf(fstream, "%-12s", "ADD");
        break;
    case sub:
        fprintf(fstream, "%-12s", "SUB");
        break;
    case mul:
        fprintf(fstream, "%-12s", "MUL");
        break;
    case i_div:
        fprintf(fstream, "%-12s", "DIV");
        break;
    case mod:
        fprintf(fstream, "%-12s", "MOD");
        break;
    case uminus:
        fprintf(fstream, "%-12s", "UMINUS");
        break;
    case if_eq:
        fprintf(fstream, "%-12s", "IF_EQ");
        break;
    case if_noteq:
        fprintf(fstream, "%-12s", "IF_NOTEQ");
        break;
    case if_less:
        fprintf(fstream, "%-12s", "IF_LESS");
        break;
    case if_lesseq:
        fprintf(fstream, "%-12s", "IF_LESSEQ");
        break;
    case if_greatereq:
        fprintf(fstream, "%-12s", "IF_GREATEREQ");
        break;
    case if_greater:
        fprintf(fstream, "%-12s", "IF_GREATER");
        break;
    case i_call:
        fprintf(fstream, "%-12s", "CALL");
        break;
    case param:
        fprintf(fstream, "%-12s", "PARAM");
        break;
    case ret:
        fprintf(fstream, "%-12s", "RET");
        break;
    case getretval:
        fprintf(fstream, "%-12s", "GETRETVAL");
        break;
    case funcstart:
        fprintf(fstream, "%-12s", "FUNCSTART");
        break;
    case funcend:
        fprintf(fstream, "%-12s", "FUNCEND");
        break;
    case tablecreate:
        fprintf(fstream, "%-12s", "TABLECREATE");
        break;
    case tablegetelem:
        fprintf(fstream, "%-12s", "TABLEGETELEM");
        break;
    case tablesetelem:
        fprintf(fstream, "%-12s", "TABLESETELEM");
        break;
    case jump:
        fprintf(fstream, "%-12s", "JUMP");
        break;
    
    default:
        break;
    }
}

void print_expr(FILE* fstream, expr* e){


    switch (e->type)
    {
    case var_e:
        fprintf(fstream, "%-15s",e->sym->name);
        break;
    case tableitem_e:
        fprintf(fstream, "%-15s",e->sym->name);
        break;
    case programfunc_e:
        fprintf(fstream, "%-15s",e->sym->name);
        break;
    case libraryfunc_e:
        fprintf(fstream, "%-15s",e->sym->name);
        break;
    case arithexpr_e:
        fprintf(fstream, "%-15s",e->sym->name);
        break;
    case boolexpr_e:
        fprintf(fstream, "%-15s",e->sym->name);
        break;
    case assignexpr_e:
        fprintf(fstream, "%-15s",e->sym->name);
        break;
    case newtable_e:
        fprintf(fstream, "%-15s",e->sym->name);
        break;
    case constnum_e:
        if(expr_is_int(e))
            fprintf(fstream, "%-15d",(int)e->numConst);
        else
            fprintf(fstream, "%-15lf",e->numConst);
        break;
    case constbool_e:
        fprintf(fstream, "%-15s",e->boolConst? "true\0":"false\0");
        break;
    case conststring_e:{
        char* temp_str = malloc((strlen(e->strConst)+5)*sizeof(char));
        check_malloc(temp_str,NULL);
        temp_str[0]='\"'; temp_str[1]='\0';
        strcat(temp_str, e->strConst);
        strcat(temp_str, "\"\0");
        fprintf(fstream, "%-15s",temp_str);
        free(temp_str);
        break;
	}
    case nil_e:
        fprintf(fstream, "%-15s", "NILL\0");
        break;
    default:
        break;

}

}

void print_quads(FILE* fstream){
    fprintf(fstream, "%-8s  %-12s  %-15s  %-15s  %-15s  %-15s %-5s\n","QUAD_NO\0", "I_OPCODE\0", "ARG_1\0", "ARG_2\0", "RESULT\0", "LABEL\0", "LINE\0");
    for(int i=0; i<95; i++) fprintf(fstream, "-");
    fprintf(fstream, "-\n");
    fflush(fstream);
    for(int i=1; i<currQuad; i++){
        fprintf(fstream, "%-8d", i);
        fprintf(fstream, "  ");
        print_op(fstream, quads[i].op);

        fprintf(fstream, "  ");
        if(quads[i].arg1!=NULL)print_expr(fstream, quads[i].arg1);
        else fprintf(fstream, "%-15s", "\0");

        fprintf(fstream, "  ");
        if(quads[i].arg2!=NULL)print_expr(fstream, quads[i].arg2);
        else fprintf(fstream, "%-15s", "\0");

        fprintf(fstream, "  ");
        if(quads[i].result!=NULL)print_expr(fstream, quads[i].result);
        else fprintf(fstream, "%-15s", "\0");

        fprintf(fstream, "  ");
        if(quads[i].label) fprintf(fstream, "%-15d",quads[i].label);
        else fprintf(fstream, "%-15s","");

        fprintf(fstream, "  ");
        fprintf(fstream, "%-8d",quads[i].line);
        

        fprintf(fstream, "\n");
        fflush(fstream);
    }
}

stmt_t* make_stmt(){

    stmt_t* s = malloc(sizeof(struct stmt_t));
    s->breakList = 0;
    s->contList = 0;
    s->retList = 0;
    return s;
}

int newList(unsigned int i){
    if(currQuad==total)
        expand();
    quads[i].label = 0;

    return i;
}

int mergelist(int l1, int l2){

    if(!l1) return l2;
    else if(!l2) return l1;
    else{

        int i = l1;
        while(quads[i].label)
            i = quads[i].label;
        quads[i].label = l2;
        return l1;
    }
}

void patchlist(int list, int label){

    while(list){
        int next = quads[list].label;
        quads[list].label = label;
        list = next;
    }
}
