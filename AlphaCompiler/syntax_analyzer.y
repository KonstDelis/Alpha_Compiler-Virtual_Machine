%{
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "libraries/utils.h"
    #include "libraries/SymTable.h"
    #include "libraries/function_stack.h"
    #include "libraries/quads.h"
    #include "libraries/i_code.h"
    #include "libraries/loopstack.h"

    SymTable_T oSymTable;
    struct function_stack* fstack;
    int scope = 0;
    int nameless_funcs=0;
    int loopcounter = 0;
    struct loopstack* loopcounterstack;

    int printSyntax = 0;

    int yylex(void);
    int method_call = 0;
    int isCallVar=0;
    int inFunction=0, inLoop=0; 
    int checkSymbol(char* name, unsigned int scope, enum SymbolType type, int is_call);
    int checkIfFunc(expr* var);
    void checkErrors();
    extern void generate_instr(void);
    extern void createBinary(FILE*);

    extern int yylineno;
    extern int column_fl;
    extern char* lineptr_fl;
    extern FILE* yyin;
    extern FILE* yyout;
    extern int yyerror(const char* msg);

    int error_count = 0;
    
    %}

/*Token types union*/
%union {
    struct varVal* variable;
    struct expr* expression;
    struct call_type* callval;
    struct SymbolTableEntry* symbolval;
    int intval;
    char* strval;
    float fval;
    unsigned unsignedval;
    unsigned int mquad;
    struct stmt_t* statement;
    struct for_struct* forpref;
}

%token <strval> ID STRING 
%token <intval> INTEGER 
%token <fval> REAL 

%right ASSIGN
%left OR
%left AND
%nonassoc EQUAL NOT_EQUAL
%nonassoc GREATER_THAN GREATER_EQUAL LESSER_THAN LESSER_EQUAL LOWER_THAN_ELSE 
%left PLUS MINUS
%left MULTIPLY DIV MODULO
%right UMINUS NOT INCREMENT DECREMENT
%left DOT DOUBLE_DOT
%left LEFT_SQR_BRK RIGHT_SQR_BRK
%left LEFT_PARENTHESIS RIGHT_PARENTHESIS
%token SEMICOLON LEFT_BRK RIGHT_BRK COMMA COLON DOUBLE_COLON
%token IF ELSE WHILE FOR FUNC RT BRK CONT LOCAL_TKN TRUE_TKN FALSE_TKN ENDL NIL

%type <expression> expression const primary assignexr lvalue term member call objectdef elist indexedelem indexed 
%type <callval> callsuffix normcall methodcall
%type <symbolval> funcdef funcprefix
%type <strval> funcname
%type <unsignedval> F
%type <mquad> M ifprefix elseprefix whilestart whilecond N funcargs
%type <statement> stmt  returnstmt statements loopstmt block ifstmt funcbody
%type <forpref> forprefix

%define parse.error verbose //probably need to comment this out if running on mac
%expect 1

%%
    
    program:    statements { if(printSyntax) printf("line %d:program->stmt statements\n",yylineno);}
                ;
  

    statements: 
                statements stmt{
                        resettemp();
                        $$ = malloc(sizeof(struct stmt_t));
                        int brk1=0, brk2=0, cont1=0, cont2=0, ret1=0, ret2=0;
                        if($1){brk1=$1->breakList; cont1=$1->contList; ret1=$1->retList;}
                        if($2){brk2=$2->breakList; cont2=$2->contList; ret2=$2->retList;}
                        $$->breakList = mergelist(brk1,brk2);
                        $$->contList = mergelist(cont1,cont2);
                        $$->retList = mergelist(ret1,ret2);
                        }   
                |
                stmt {$$=$1;}          
                ;


    loopstart:  {loopcounter++;}
                ;

    loopend:    {loopcounter--;}
                ;

    loopstmt:   loopstart stmt loopend{ $$ = $2;}
                ;


    stmt:       expression SEMICOLON{ if(printSyntax)  printf("line %d:stmt->expression;\n",yylineno); icode_bool_stmt($1); $$=NULL;}
                
                |ifstmt{ if(printSyntax)printf("line %d:stmt->ifstmt\n",yylineno); $$=$1;}
                
                |whilestmt{if(printSyntax) printf("line %d:stmt->whilestmt\n",yylineno);$$=NULL;}
                
                |forstmt{ if(printSyntax) printf("line %d:stmt->forstmt\n",yylineno); $$=NULL;}
                
                |returnstmt{ if(printSyntax) printf("line %d:stmt->returnstmt\n",yylineno); $$=$1;}
                
                |BRK SEMICOLON{  if(loopcounter<=0)yyerror("cannot 'break' when not in loop");if(printSyntax) printf("line %d:stmt->BREAK;\n",yylineno);
                                $$ = icode_break();
                                }
                
                |CONT SEMICOLON{ if(loopcounter<=0)yyerror("cannot 'continue' when not in loop");if(printSyntax) printf("line %d:stmt->CONT;\n",yylineno);
                                  $$ = icode_continue();
                                  }
                
                |block{ if(printSyntax) printf("line %d:stmt->block\n",yylineno);}
                
                |funcdef{ if(printSyntax) printf("line %d:stmt->funcdef\n",yylineno); $$=NULL;}
                
                |SEMICOLON{if(printSyntax) printf("line %d:stmt->;\n",yylineno); $$=NULL;}
                ;
    

    expression: assignexr {if(printSyntax) printf("line %d:expression->assignexr\n",yylineno);}
                
                |expression PLUS expression { 
                                                $$ = icode_arithmetic_plus($1,$3);
                                                if(printSyntax) printf("line %d:expression->expression + expression\n",yylineno);                                   
                                                }
                                              
                |expression MINUS expression{   
                                                $$ = icode_arithmetic_minus($1,$3);
                                                if(printSyntax) printf("line %d:expression->expression - expression\n",yylineno);}

                |expression MULTIPLY expression{    
                                                $$ = icode_arithmetic_mul($1,$3);
                                                if(printSyntax) printf("line %d:expression->expression * expression\n",yylineno);}

                |expression DIV expression{     
                                                $$ = icode_arithmetic_i_div($1,$3);
                                                if(printSyntax) printf("line %d:expression->expression / expression\n",yylineno);}
                
                |expression MODULO expression{  
                                                $$ = icode_arithmetic_mod($1,$3);
                                                if(printSyntax) printf("line %d:expression->expression %c expression\n",yylineno,'%');}
                
                |expression GREATER_THAN expression{ 
                                                 $$ = icode_relop($1,$3,if_greater); 
                                                 if(printSyntax) printf("line %d:expression->expression > expression\n",yylineno);}

                |expression GREATER_EQUAL expression{ 
                                                 $$ = icode_relop($1,$3,if_greatereq);   
                                                 if(printSyntax) printf("line %d:expression->expression >= expression\n",yylineno);}
                
                |expression LESSER_THAN expression{ 
                                                $$ = icode_relop($1,$3,if_less); 
                                                if(printSyntax) printf("line %d:expression->expression < expression\n",yylineno);}
                
                |expression LESSER_EQUAL expression{ 
                                                $$ = icode_relop($1,$3,if_lesseq);    
                                                if(printSyntax) printf("line %d:expression->expression <= expression\n",yylineno);}
                
                |expression EQUAL{icode_bool_stmt($1);} expression{  
                                                icode_bool_stmt($4);
                                                $$ = icode_relop($1,$4,if_eq); 
                                                icode_bool_stmt($$); 
                                                if(printSyntax) printf("line %d:expression->expression == expression \n",yylineno);}

                |expression NOT_EQUAL{icode_bool_stmt($1);} expression{   
                                                icode_bool_stmt($4);
                                                $$ = icode_relop($1,$4,if_noteq); 
                                                icode_bool_stmt($$);
                                                if(printSyntax) printf("line %d:expression->expression != expression\n",yylineno);}
                
                |expression AND{$1 = make_boolean_expr($1);} M expression{   
                                                $$ = icode_and($1,$5,$4);
                                                if(printSyntax) printf("line %d:expression->expression and expression\n",yylineno);}
                
                |expression OR{$1 = make_boolean_expr($1);} M expression{    
                                                $$ = icode_or($1,$5,$4);              
                                                if(printSyntax) printf("line %d:expression->expression or expression\n",yylineno);}

                |term {if(printSyntax) printf("line %d:expression->term\n",yylineno);}
                ;

    M:          {$$ = nextquadlabel();}
                ;

    N:          {$$ = nextquadlabel(); emit(jump,NULL,NULL,NULL,0,yylineno);}
                ;

    term:       LEFT_PARENTHESIS expression RIGHT_PARENTHESIS { $$=$2; if(printSyntax) printf("line %d:term->(expression)\n",yylineno);}
                
                |MINUS expression      { $$=icode_uminus($2); if(printSyntax) printf("line %d:term->-expression\n",yylineno);} %prec UMINUS
                
                |NOT expression         {$$=icode_not($2); if(printSyntax) printf("line %d:term->!expression\n",yylineno);}
                
                |INCREMENT lvalue       { $$=icode_incr_lvalue($2); checkIfFunc($2); if(printSyntax) printf("line %d:term->++lvalue\n",yylineno);}
                
                |lvalue INCREMENT       { $$= icode_lvalue_incr($1); checkIfFunc($1); if(printSyntax) printf("line %d:term->lvalue++\n",yylineno);}
                
                |DECREMENT lvalue       { $$=icode_decr_lvalue($2); checkIfFunc($2); if(printSyntax) printf("line %d:term->--lvalue\n",yylineno);}
                
                |lvalue DECREMENT       { $$= icode_lvalue_decr($1); checkIfFunc($1); if(printSyntax) printf("line %d:term->lvalue--\n",yylineno);}
                
                |primary{ $$=$1; if(printSyntax) printf("line %d:term->primary\n",yylineno);}
                ;


    assignexr: lvalue ASSIGN expression{    
                                            if($1!=NULL && $3!=NULL){
                                                if($1->sym!=NULL && $1->sym->s_type==USERFUNC){
                                                    yyerror("functions and variables are not allowed to have the same name");
                                                    checkErrors();
                                                }
                                                if($1->sym!=NULL && $1->sym->s_type==LIBFUNC){
                                                    yyerror("oveshadowing library funstions is not allowed");
                                                    checkErrors();
                                                }
                                            }
                                            icode_bool_stmt($3);
                                            
                                            $$ = icode_assignment($1,$3);
                                            
                                            if(printSyntax) printf("line %d:assignexr->lvalue=expression\n",yylineno);}


    primary:    lvalue          { if(printSyntax) printf("line %d:primary->lvalue\n",yylineno);
                                  $$ = emit_iftableitem($1);}
                
                |call           {if(printSyntax) printf("line %d:primary->call\n",yylineno);}
                
                |objectdef      {if(printSyntax) printf("line %d:primary->objectdef\n",yylineno);}
                
                |LEFT_PARENTHESIS  funcdef RIGHT_PARENTHESIS    { if(printSyntax) printf("line %d:primary->(funcdef)\n",yylineno);
                                                                 $$ = newexpr(programfunc_e);
                                                                 $$->sym = $2;}
                
                |const          {if(printSyntax) printf("line %d:primary->const\n",yylineno);}
                ;


    lvalue:     ID                  {   SymbolTableEntry rt = NULL;
                                        enum SymbolType type = USERFUNC;
                                        rt = SymTable_lookup(oSymTable, $1, scope, ALL_TYPES);
                                        if(rt==NULL) rt = SymTable_lookupall(oSymTable, $1, scope, fstack->top->def_scope, yylineno);
                                        if(rt==NULL) rt = SymTable_lookup(oSymTable, $1, GLOBAL_SCOPE, ALL_TYPES);
                                        enum SymbolType stype = scope>0 ? LOCAL:GLOBAL; 
                                        if(rt == NULL && checkSymbol($1, scope,LOCAL,FALSE)==0){
                                            rt = SymTable_insert(oSymTable, $1, NULL, stype, yylineno, scope, currscopespace(), currscopeoffset()); 
                                            inccurrscopeoffset();
                                        }
                                       
                                        $$ = lvalue_expr(rt);
                                        
                                        if(printSyntax) printf("line %d:lvalue->ID : %s\n",yylineno, $1); }

                |LOCAL_TKN ID       {   SymbolTableEntry rt = NULL;
                                        enum SymbolType s_type = scope>0? LOCAL:GLOBAL;
                                        rt = SymTable_lookup(oSymTable, $2, scope, ALL_TYPES);
                                        enum SymbolType stype = scope>0 ? LOCAL:GLOBAL; 
                                        if(rt == NULL && checkSymbol($2, scope,s_type,FALSE)==0) {
                                            rt = SymTable_insert(oSymTable, $2, NULL, stype, yylineno, scope, currscopespace(), currscopeoffset());
                                            inccurrscopeoffset();
                                        }
                                        $$ = lvalue_expr(rt);
                                        
                                        if(printSyntax) printf("line %d:lvalue->LOCAL_TKN ID\n",yylineno);}

                |DOUBLE_COLON ID    {   expr* val = NULL;
                                        SymbolTableEntry rt = NULL;
                                        rt = SymTable_lookup(oSymTable, $2, GLOBAL_SCOPE, ALL_TYPES);
                                        if(rt!=NULL)
                                            val = lvalue_expr(rt);
                                        else{
                                            yyerror("cannot access global variable that is undefined");
                                            checkErrors();
                                        }  
                                        $$=val;
                                        if(printSyntax) printf("line %d:lvalue->::ID\n",yylineno);}

                |member                 {$$ = $1; if(printSyntax) printf("line %d:lvalue->member\n",yylineno);}
                ;

    member:     lvalue DOT ID                                   {if(printSyntax) printf("line %d:member->lvalue.ID\n",yylineno);
                                                                $$ = member_item($1, $3);}

                |lvalue LEFT_SQR_BRK expression RIGHT_SQR_BRK   {if(printSyntax) printf("line %d:member->lvalue[expression]\n",yylineno);
                                                                $$ = icode_member_expression_index($1,$3);
                                                                }

                |call DOT ID                                    {$$ = member_item($1, $3); if(printSyntax) printf("line %d:member->call.ID\n",yylineno);}
                |call LEFT_SQR_BRK expression RIGHT_SQR_BRK     {$$ = icode_call_sqr_expr_sqr($1,$3); if(printSyntax) printf("line %d:member->call[expression]\n",yylineno);}
                ;

    call:       call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS   {   if(printSyntax) printf("line%d:call->(elist)\n",yylineno);
                                                                    $3 = reverse_elist($3);
                                                                    $$ = make_call($1,$3);
                                                                }

                |lvalue callsuffix  {   if(printSyntax) printf("line %d:call->lvalue callsuffix\n",yylineno);
                                        $$ = icode_lvalue_callsufix($1,$2);
                                    }
            
                |LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS {if(printSyntax) printf("line %d:call->(funcdef)(elist)\n",yylineno);
                                                                                                      $$ = icode_funcdef_call($2,$5);}
                ;

    callsuffix: normcall        {if(printSyntax) printf("line %d:callsuffix->normcall\n",yylineno);
                                 $$ = $1;}
                
                |methodcall     {if(printSyntax) printf("line %d:callsuffix->methodcall\n",yylineno);
                                 $$ = $1;}
                ;


    normcall:   LEFT_PARENTHESIS elist RIGHT_PARENTHESIS    {if(printSyntax) printf("line %d:normcall->(elist)\n",yylineno);
                                                             $$=icode_normcall($2);}
                ;
    

    methodcall: DOUBLE_DOT ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS  {method_call=1; if(printSyntax) printf("line %d:methodcall->..ID(elist)\n",yylineno);
                                                                         $$ = icode_methodcall($2,$4);}
                ;
    

    elist:       expression                 {if(printSyntax) printf("line %d:elist->expression\n",yylineno);
                                            icode_bool_stmt($1); $$=$1; $$->next=NULL;
                                            }

                |expression COMMA elist     {if(printSyntax) printf("line %d:elist->expression,elist\n",yylineno);
                                            $1->next = $3; $$=$1;
                                            }
                | {$$=NULL;}
                ;


    objectdef:  LEFT_SQR_BRK elist RIGHT_SQR_BRK    {if(printSyntax) printf("line %d:objectdef->[elist]\n",yylineno);
                                                    $$ = icode_objdef_elist($2);
                                                    }
                |LEFT_SQR_BRK indexed RIGHT_SQR_BRK     {if(printSyntax) printf("line %d:objectdef->[indexed]\n",yylineno);
                                                        $$ = icode_objdef_indexed($2);
                                                        }
                ;
    
    indexed:    indexedelem                     {if(printSyntax) printf("line %d:indexed->indexedelem\n",yylineno);
                                                $$=$1; $$->next=NULL;} 

                |indexedelem COMMA indexed      {if(printSyntax) printf("line %d:indexed->indexedelem,indexed\n",yylineno);
                                                $1->next = $3; $$=$1;}
                ;

    indexedelem:    LEFT_BRK expression COLON expression RIGHT_BRK  {if(printSyntax) printf("line %d:indexedelem->{expression,expression}\n",yylineno);
                                                                    icode_bool_stmt($4);
                                                                    $$ = make_indexed($2, $4);}
                    ;

    block:      LEFT_BRK{scope++;} statements RIGHT_BRK {hide_scope(oSymTable,scope);scope--;if(printSyntax) printf("line %d:block->{statements}\n",yylineno);$$=$3;}
                |
                LEFT_BRK{scope++;}  RIGHT_BRK {hide_scope(oSymTable,scope);scope--;if(printSyntax) printf("line %d:block->{statements}\n",yylineno);$$=NULL;} 
                ;


    funcblockstart: {loopstack_push(loopcounterstack,loopcounter); loopcounter=0;}
                ;

    funcblockend:   {loopcounter = loopstack_pop(loopcounterstack);}
                ;

    funcname:   ID{$$ = $1;}
                |   {char* funcname = malloc(sizeof(char)*100);
                    sprintf(funcname, "_f%d",nameless_funcs++);
                    $$ = funcname;                                                                      
                    }
                ;

    funcprefix: FUNC funcname{  if(checkSymbol($2, scope,USERFUNC,FALSE)==0){
                                    $$ = SymTable_insert(oSymTable, $2, NULL, USERFUNC, yylineno, scope, programvar, 0);
                                    expr* pref = malloc(sizeof(struct expr));
                                    pref->sym = $$;
                                    pref->type = programfunc_e;
                                    emit(jump, NULL, NULL, NULL, 0, yylineno);
                                    $$->iaddress = nextquadlabel();
                                    emit(funcstart,pref,NULL,NULL,0,yylineno);
                                }
                                func_def(fstack, scope,currscopeoffset());
                                enterscopespace();resetformalargsoffset();
                            }
                ;

    funcargs:   LEFT_PARENTHESIS
                idlist RIGHT_PARENTHESIS{
                                            if(printSyntax) printf("line %d:funcdef->FUNC ID(idlist) \n",yylineno); 
                                            inFunction++;
                                            $$ = nextquadlabel()-2;
                                            enterscopespace();
                                            resetfunctionlocaloffset();}
                ;

    funcbody:   block {$$=$1;}
                ;   
    
    F:          {$$ = currscopeoffset();
                      exitscopespace();}
                ;

    funcdef:    funcprefix funcargs funcblockstart funcbody F funcblockend   {inFunction--;
                                                struct func_def_info *finfo = exit_func_def(fstack); 
                                                exitscopespace();
                                                restorecurrscopeoffset(finfo->next_scope_offset);
                                                //free(finfo);
                                                $1->totalScopeOffset = $5;
                                                expr* pref = malloc(sizeof(struct expr));
                                                pref->sym = $1;
                                                pref->type = programfunc_e;
                                                if($4)patchlist($4->retList, nextquadlabel());
                                                emit(funcend,pref,NULL,NULL,0,yylineno);
                                                patchlabel($2,nextquadlabel());
                                                }

            
                ;
    
    const:      INTEGER     {
                            $$ = newexpr_constarith((double)$1); 
                            if(printSyntax) printf("line %d:const->INTEGER\n",yylineno);
                            }

                |REAL       {
                            $$ = newexpr_constarith((double)$1); 
                            if(printSyntax) printf("line %d:const->REAL\n",yylineno);}
                
                |STRING     {$$ = newexpr_conststring($1);
                            if(printSyntax) printf("line %d:const->STRING\n",yylineno);}
                
                |NIL        {$$ = newexpr(nil_e);
                            if(printSyntax) printf("line %d:const->NIL\n",yylineno);
                            }
                
                |TRUE_TKN   {if(printSyntax) printf("line %d:const->TRUE_TKN\n",yylineno);
                            $$ = newexpr_constbool(1);
                            }
                
                |FALSE_TKN  {if(printSyntax) printf("line %d:const->FALSE_TKN\n",yylineno);
                            $$ = newexpr_constbool(0);}
                |ENDL       {if(printSyntax) printf("line %d:const->ENDL\n",yylineno);
                            $$ = newexpr_conststring("\n");
                            }
                ;
    
    idlist:     ID          {   if(checkSymbol($1, scope+1,FORMAL,FALSE)==0){
                                    SymTable_insert(oSymTable, $1, NULL, FORMAL, yylineno, scope+1, currscopespace(), currscopeoffset());
                                    inccurrscopeoffset();
                                }
                                
                                if(printSyntax) printf("line %d: idlist->ID\n",yylineno);}
                idlists

                |               {resetformalargsoffset();} 
                ;

    idlists:    COMMA ID           {   if(checkSymbol($2, scope+1,FORMAL,FALSE)==0){
                                            SymTable_insert(oSymTable, $2, NULL, FORMAL, yylineno, scope+1, currscopespace(), currscopeoffset());
                                            inccurrscopeoffset();
                                        }
                                    }
                idlists 
                
                |                    
                ;


    ifprefix:   IF LEFT_PARENTHESIS expression RIGHT_PARENTHESIS    { if(printSyntax) printf("line %d:ifstmt->IF(\n",yylineno);
                                                                    $$ = icode_ifprefix($3);}
                ;
    
    elseprefix: ELSE {$$ = nextquadlabel();
                      emit(jump,NULL,NULL,NULL,0,yylineno);}

                ;

    ifstmt:     ifprefix stmt            {patchlabel($1,nextquadlabel());$$=$2;}  %prec LOWER_THAN_ELSE
                
                |ifprefix stmt elseprefix stmt                           {if(printSyntax) printf("line %d:ifstmt->ifstmt ELSE stmt\n",yylineno);
                                                                          patchlabel($1,$3+1); patchlabel($3,nextquadlabel());
                                                                          int brk1=0,brk2=0,cont1=0,cont2=0, ret1=0, ret2=0;
                                                                          $$ = make_stmt();
                                                                          if($2){brk1=$2->breakList; cont1=$2->contList; ret1=$2->retList;}
                                                                          if($4){brk2=$4->breakList; cont2=$4->contList; ret2=$4->retList;}
                                                                          $$->breakList = mergelist(brk1,brk2);
                                                                          $$->contList = mergelist(cont1,cont2);
                                                                          $$->retList = mergelist(ret1,ret2);
                                                                          }
                ;


    whilestart: WHILE { $$ = nextquadlabel();}
                ;

    whilecond:  LEFT_PARENTHESIS expression 
                RIGHT_PARENTHESIS {if(printSyntax)printf("line %d:whilestmt->while(expression)\n",yylineno); inLoop++;
                                   $$ = icode_whilecond($2);}
                ;


    whilestmt:  whilestart whilecond loopstmt{inLoop--; icode_whilestmt($1,$2,$3); if($3)patchlist($3->contList, nextquadlabel()-1); if($3)patchlist($3->breakList, nextquadlabel());}
                ;

    forprefix:  FOR LEFT_PARENTHESIS elist SEMICOLON M expression 
                SEMICOLON { $$ = icode_forprefix($5,$6);}
                ;

    forstmt:    forprefix N elist RIGHT_PARENTHESIS N {if(printSyntax)printf("line %d:forstmt-> for(elist; expression; elist)\n",yylineno);} 
                {inLoop++;}loopstmt N{
                    icode_forstmt($1,$2,$5,$8,$9);
                    if($8)patchlist($8->contList, nextquadlabel()-1); if($8)patchlist($8->breakList, nextquadlabel());
                    inLoop--;
                }
                ;

    returnstmt: RT expression SEMICOLON {
                                        if(printSyntax) printf("line %d:returnstmt->RT expression\n",yylineno);
                                        if(inFunction<=0)yyerror("cannot 'return' when not inside a function");
                                        icode_bool_stmt($2);
                                        emit(ret, NULL, NULL, $2, 0, yylineno);
                                        if(printSyntax) printf("line %d: returnstmt -> ;\n",yylineno);
                                        $$ = make_stmt();
                                        $$->retList = newList(nextquadlabel());
                                        emit(jump,NULL,NULL,NULL,0,yylineno);
                                        }

                |RT SEMICOLON   {if(inFunction<=0)yyerror("cannot 'return' when not inside a function");
                                if(printSyntax) printf("line %d:returnstmt-> RT ;\n",yylineno);
                                $$ = make_stmt();
                                emit(ret, NULL, NULL, NULL, 0, yylineno);
                                $$->retList = newList(nextquadlabel());
                                emit(jump,NULL,NULL,NULL,0,yylineno);
                                }
                ;


%%

int yyerror(const char* msg){
    red();
    fprintf(stderr,"Error: line %d: column %d: %s\n", yylineno, column_fl, msg);
    reset();
    error_count++;
    return 1;
}

int yywarning(char* msg){
    yellow();
    fprintf(stderr,"Warning: line %d: %s\n",yylineno,msg);
    reset();
    return -1;
}

int checkIfFunc(expr* var){
    if(var!=NULL && var->sym!=NULL && (var->sym->s_type == USERFUNC || var->sym->s_type == LIBFUNC))
    {
        yyerror("not allowed to use Increment/Decrement operators on functions");
        return -1;
    }
    return 0;
}

int checkSymbol(char* name, unsigned int scope, enum SymbolType type, int is_call){
    int errorcode = 0;
    assert(is_call==TRUE || is_call==FALSE);
    errorcode = checkSymbolName(oSymTable, name, scope, &type, is_call);
    if(errorcode==OK){
        return 0;
    }
    else if(errorcode==SAME_FUNCNAME_SCOPE_ERR){
        yyerror("multiple functions with the same name in the same scope are not allowed");
        return -1;
    }
    else if(errorcode==DOUBLE_FORMAL_ERR){
        yyerror("double formal name in the same function declaration is not allowed");
        return -1;
    }
    else if(errorcode==LIBFUNC_NAME_ERR){
        yyerror("names of library functions cannot be shadowed");
        return -1;
    }
    else if(errorcode==SAME_SCOPE_FUNC_VAR){
        yyerror("functions and variables are not allowed to have the same name");
        checkErrors();
        return -1;
    }
    else if(errorcode==CALL_UNDEFINED_FUNC){
        yyerror("unable to call undefined function");
        return -1;
    }
    else {
        yyerror("unexpected error code");
        return -2;
    }
}

void checkErrors(){
    if(error_count){
        red();
        printf("\nExited compile with %d errors\n",error_count);
        reset();
        exit(1);
    }
}

void printArgError(){
    red();
    fprintf(stderr, "Error: invalid parameters, run alphac as ./alphac with these flags\n\n"
    "\t'-in input.asc'    : where input.asc in the alpha file that will be compiled. If skiped stdin will be used\n"
    "\t'-o binaryFileName': where binaryFileName the name of the binary file that will be created. Default is 'binary.abc'\n"
    "\t                     Note: don't add file extension, '.abc' will be added\n"
    "\t'-debug'           : syntax analysis, hashtable, intermediate/target code and constant tables will be printed\n");
    reset();
    exit(-5);
}

int main(int argc, char* argv[]){
    FILE *fin, *fout;
    fin=stdin;
    fout=NULL;
    oSymTable = SymTable_new();
    fstack = init_function_stack();
    loopcounterstack = malloc(sizeof(struct loopstack));

    /*Check argumants*/
    if(argc<1 && argc>=6){
        printArgError();
    }
    for(int i=1; i<argc; i++){
        if(strcmp(argv[i],"-debug")==0){/*Enable debug mode flag*/
            printSyntax=1;
        }
        else if(strcmp(argv[i],"-in")==0 && i+1<argc){/*open input file*/
            fin = fopen(argv[++i],"r");
            if(!fin){red();fprintf(stderr,"Error: unable to open file '%s'\n", argv[i]);reset();exit(-5);}
        }
        else if(strcmp(argv[i],"-o")==0 && i+1<argc){/*open output binary file*/
            char* binaryName = malloc(sizeof(char)*(strlen(argv[++i])+4));
            check_malloc(binaryName, "unable to allocate memory for 'binaryName' string");
            strcpy(binaryName,argv[i]);
            strcat(binaryName, ".abc");
            fout = fopen(binaryName,"wb");
            if(!fout){red();fprintf(stderr,"Error: unable to open binary file '%s'\n", argv[i]);reset();exit(-5);}
        }
        else{
            printArgError();
        }
    }

    /*Start syntax analysis and intermediate code generation*/
    yyin = fin;
    yyout = stdout;
    yyparse(); /*If in debug mode grammar rule reduction will be printed*/

    /*If synatx errors were found exit compilation*/
    checkErrors();

    /*print icode and hashtabel if in debug mode*/
    if(printSyntax){
        print_scope_lists(oSymTable);
        FILE* fsteam = fopen("quads_out.txt", "w");
        if(!fsteam) fprintf(stderr, "Cannot open file for quads_out.txt\n");
        print_quads(fsteam);
    }
    /*Generate target code*/
    generate_instr();

    /*Check if output flag was entered and binary is open. If not open default file*/
    if(!fout){
        fout = fopen("binary.abc", "wb");
        if(!fout){red(); fprintf(stderr,"Error: unable to open default binary file\n"); reset(); exit(-5);}
    }
    createBinary(fout);

    /*Done, close files*/
    fclose(fin);
}
