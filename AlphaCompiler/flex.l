%{  
    #include "libraries/utils.h"
    #include "libraries/token_list.h"
    #include "libraries/stack.h"
    #include "parser.h"
    #include <string.h>

    #define BUFSZ 1024

    int column_fl = 1;
    int next_column = 1;

    int nested_comments=-1;
    int number_nested = 0;
    int number=0;
    int comment_start,comment_end;
    struct ml_comment_stack comment_stack;
    int yyparse(void);

    size_t n = 0;
    size_t consumed = 0;
    size_t available = 0;
    size_t min(size_t a, size_t b);
    #define HANDLE_COLUMN column_fl = next_column; next_column += strlen(yytext)
%}

%option noyywrap
%option yylineno


/* Definitions */
nl \n
left_parenthesis "("
right_parenthesis ")"
left_brk "{"
right_brk "}"
left_sqr_brk "["
right_sqr_brk "]"
semicolon ";"
comma ","
colon ":"
double_colon "::"
dot "."
double_dot ".."
plus "+"
assign "="
minus "-"
slash "/"
multiply "*"
modulo "%"
not_equal "!="
equal "=="
increment "++"
decrement "--"
less_than "<"
greater_than ">"
less_equal_than "<="
greater_equal_than ">="
if "if"
else "else"
while "while"
for "for"
func "function"
rt "return"
brk "break"
cont "continue"
and "and"
not "not"
or "or"
local "local"
true "true"
false "false"
endl "endl"
nil "nil"
id [a-zA-Z][a-zA-Z_0-9]*
integer [0-9]+
real [0-9]+[.][0-9]+

/*Rules*/

%%


"\"" {
    int extend = 1;
    int current = 0;
    next_column++;
    int strSZ = BUFSZ;
    char c, look_aylval;
    char* str = malloc(sizeof(char)*BUFSZ*extend);
    if(str==NULL){red();fprintf(stderr, "Error: cannot allocate memory for string value in line %d\n",yylineno);reset();exit(2);}
    while((c = input()) != EOF){
        int found_special = 0, unputflg=0;
        next_column++;
        if(current>=strSZ){
            extend++;
            str = (char*) realloc(str, sizeof(char)*BUFSZ*extend);
            if(str==NULL){red();fprintf(stderr, "Error: cannot allocate memory for string value in line %d\n",yylineno);reset();exit(2);}
            strSZ = BUFSZ*extend;
        }
        if(c=='\"'){
            str[current]='\0';
            yylval.strval =strdup(str);
            next_column++;
            return STRING;
        }
        if(c=='\\'){
            look_aylval=input();
            next_column++;
            unputflg=1;
            if(look_aylval=='n'){
                str[current++]='\n';
                found_special=1;
            }
            if(look_aylval=='t'){
                str[current++]='\t';
                found_special=1;
            }
            if(look_aylval=='\\'){
                str[current++]='\\';
                found_special=1;
            }
            if(look_aylval=='\"'){
                str[current++]='\"';
                found_special=1;
            }
        }
        if(found_special) continue;
        if(unputflg) {
            unput(look_aylval);
            next_column--;
            yellow();
            fprintf(stderr,"Warning: unknown escape character '\\%c' in line: %d\n",look_aylval,yylineno);
            reset();
        }
        str[current++]=c;
    }
    if(c==EOF){
        red();
        fprintf(stderr,"Error: string doesn't end, line %d\n",yylineno);
        reset();
        return(-2);
    }
}

"//" {
    char c;
    int extend = 1;
    int current = 0;
    int strSZ = BUFSZ;
    char* comment = malloc(sizeof(char)*BUFSZ*extend);
    next_column+=2;
    if(comment==NULL){red();fprintf(stderr, "Error: cannot allocate memory for line comment value in line %d\n",yylineno);reset();exit(2);}
    while((c = input())!='\0'){
        next_column++;
        if(current>=strSZ){
            extend++;
            comment = (char*) realloc(comment, sizeof(char)*BUFSZ*extend);
            if(comment==NULL){red();fprintf(stderr, "Error: cannot allocate memory for line comment value in line %d\n",yylineno);reset();exit(2);}
            strSZ = BUFSZ*extend;
        }
        if(c=='\n'){
            comment[current++]='\0';
            next_column=1;
            number++; 
            break;
        }
        comment[current++]=c;
    }
    if(current>=strSZ){
        extend++;
        comment = (char*) realloc(comment, sizeof(char)*BUFSZ*extend);
        if(comment==NULL){red();fprintf(stderr, "Error: cannot allocate memory for line comment value in line %d\n",yylineno);reset();exit(2);}
        strSZ = BUFSZ*extend;
    }
    comment[current++]='\0';
    if(c=='\0') {number++;
    return 0;}
}


"/*" { number_nested++;
    next_column+=2;
    char c,c_next;
    while((c=input())!='\0'){
        next_column++;
        if(c=='\n'){
            next_column = 1;
        }
        if(c=='*'){
            c_next=input();
            if(c_next=='/'){
                number_nested--;
                next_column++;
            }     
            else{
                unput(c_next);
            }
               
        }
        if(c=='/'){
            c_next=input();
            if(c_next=='*'){
                number_nested++;
                next_column++;
            }
            else{
                unput(c_next);

            }
        }
        if(number_nested<=0) break;

    }
    if(c=='\0'){red();fprintf(stderr, "Error: multiline comment never closes\n");reset();
    exit(-1);}
}


{left_parenthesis} {HANDLE_COLUMN;
 return LEFT_PARENTHESIS;
}

{right_parenthesis} {HANDLE_COLUMN;
return RIGHT_PARENTHESIS;
}

{nl} {next_column=1;
}

" " {next_column++;
}
"\t" {next_column+=8;
}
"\v" {next_column++;
}

{left_brk} {HANDLE_COLUMN;
return LEFT_BRK ;
}

{right_brk} {HANDLE_COLUMN;
return RIGHT_BRK;
}

{left_sqr_brk} {HANDLE_COLUMN;
return LEFT_SQR_BRK;
}


{right_sqr_brk} {HANDLE_COLUMN;
return RIGHT_SQR_BRK;
}

{semicolon} {HANDLE_COLUMN;
return SEMICOLON;
}

{comma} {HANDLE_COLUMN;
return COMMA;
}

{colon} {HANDLE_COLUMN;
return COLON;
}

{double_colon} {HANDLE_COLUMN;
return DOUBLE_COLON;}

{dot} {HANDLE_COLUMN;
return  DOT;}

{double_dot} {HANDLE_COLUMN;
return DOUBLE_DOT;}

{plus} {HANDLE_COLUMN;
return PLUS;}

{assign} {HANDLE_COLUMN;
return ASSIGN;}

{minus} {HANDLE_COLUMN;
return MINUS;}

{slash} {HANDLE_COLUMN;
return DIV;}

{multiply} {HANDLE_COLUMN;
return MULTIPLY;}

{modulo} {HANDLE_COLUMN;
return MODULO;}

{not_equal} {HANDLE_COLUMN;
return NOT_EQUAL;}

{equal} {HANDLE_COLUMN;
return EQUAL;}

{increment} {HANDLE_COLUMN;
return INCREMENT;}

{decrement} {HANDLE_COLUMN;
return DECREMENT;}

{less_than} {HANDLE_COLUMN; 
return LESSER_THAN;}

{greater_than} {HANDLE_COLUMN;
return GREATER_THAN;}

{less_equal_than} {HANDLE_COLUMN;
return LESSER_EQUAL;}

{greater_equal_than} {HANDLE_COLUMN;
return GREATER_EQUAL;}

{if} {HANDLE_COLUMN; 
return IF;}

{else} {HANDLE_COLUMN; 
return ELSE;}

{while} {HANDLE_COLUMN;
return WHILE;}

{for} {HANDLE_COLUMN;
return FOR;}

{func} {HANDLE_COLUMN; 
return FUNC;}

{rt} {HANDLE_COLUMN;
return RT;}

{brk} {HANDLE_COLUMN;
return BRK;}

{cont} {HANDLE_COLUMN;
return CONT;}

{endl} {HANDLE_COLUMN;
return ENDL;}

{and} {HANDLE_COLUMN;
return AND;}

{not} {HANDLE_COLUMN;
return NOT;}

{or} {HANDLE_COLUMN;
return OR;}

{local} {HANDLE_COLUMN;
return LOCAL_TKN;}

{true} {HANDLE_COLUMN;
return TRUE_TKN;}

{false} {HANDLE_COLUMN;
return FALSE_TKN;}

{nil} {HANDLE_COLUMN;
return NIL;}

{real} {HANDLE_COLUMN;
    
    yylval.fval = atof(yytext);
    return REAL;}

{integer} {HANDLE_COLUMN;
    
    yylval.intval = atoi(yytext);
     return INTEGER;}

{id} {HANDLE_COLUMN;
    
    yylval.strval = strdup(yytext);
    return ID;}

. {
    red();
    fprintf(stderr,"Error: token not recognised in line %d\n", yylineno);
    reset();
    return(-1);
    }

<<EOF>> {
    return 0;
}


%%

size_t min(size_t a, size_t b) {
    return b < a ? b : a;
}