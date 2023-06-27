/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_ALPHACOMPILER_PARSER_H_INCLUDED
# define YY_YY_ALPHACOMPILER_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID = 258,                      /* ID  */
    STRING = 259,                  /* STRING  */
    INTEGER = 260,                 /* INTEGER  */
    REAL = 261,                    /* REAL  */
    ASSIGN = 262,                  /* ASSIGN  */
    OR = 263,                      /* OR  */
    AND = 264,                     /* AND  */
    EQUAL = 265,                   /* EQUAL  */
    NOT_EQUAL = 266,               /* NOT_EQUAL  */
    GREATER_THAN = 267,            /* GREATER_THAN  */
    GREATER_EQUAL = 268,           /* GREATER_EQUAL  */
    LESSER_THAN = 269,             /* LESSER_THAN  */
    LESSER_EQUAL = 270,            /* LESSER_EQUAL  */
    LOWER_THAN_ELSE = 271,         /* LOWER_THAN_ELSE  */
    PLUS = 272,                    /* PLUS  */
    MINUS = 273,                   /* MINUS  */
    MULTIPLY = 274,                /* MULTIPLY  */
    DIV = 275,                     /* DIV  */
    MODULO = 276,                  /* MODULO  */
    UMINUS = 277,                  /* UMINUS  */
    NOT = 278,                     /* NOT  */
    INCREMENT = 279,               /* INCREMENT  */
    DECREMENT = 280,               /* DECREMENT  */
    DOT = 281,                     /* DOT  */
    DOUBLE_DOT = 282,              /* DOUBLE_DOT  */
    LEFT_SQR_BRK = 283,            /* LEFT_SQR_BRK  */
    RIGHT_SQR_BRK = 284,           /* RIGHT_SQR_BRK  */
    LEFT_PARENTHESIS = 285,        /* LEFT_PARENTHESIS  */
    RIGHT_PARENTHESIS = 286,       /* RIGHT_PARENTHESIS  */
    SEMICOLON = 287,               /* SEMICOLON  */
    LEFT_BRK = 288,                /* LEFT_BRK  */
    RIGHT_BRK = 289,               /* RIGHT_BRK  */
    COMMA = 290,                   /* COMMA  */
    COLON = 291,                   /* COLON  */
    DOUBLE_COLON = 292,            /* DOUBLE_COLON  */
    IF = 293,                      /* IF  */
    ELSE = 294,                    /* ELSE  */
    WHILE = 295,                   /* WHILE  */
    FOR = 296,                     /* FOR  */
    FUNC = 297,                    /* FUNC  */
    RT = 298,                      /* RT  */
    BRK = 299,                     /* BRK  */
    CONT = 300,                    /* CONT  */
    LOCAL_TKN = 301,               /* LOCAL_TKN  */
    TRUE_TKN = 302,                /* TRUE_TKN  */
    FALSE_TKN = 303,               /* FALSE_TKN  */
    ENDL = 304,                    /* ENDL  */
    NIL = 305                      /* NIL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 43 "AlphaCompiler/syntax_analyzer.y"

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

#line 128 "AlphaCompiler/parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_ALPHACOMPILER_PARSER_H_INCLUDED  */
