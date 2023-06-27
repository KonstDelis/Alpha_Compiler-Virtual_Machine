/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "AlphaCompiler/syntax_analyzer.y"

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
    
    

#line 113 "AlphaCompiler/parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_STRING = 4,                     /* STRING  */
  YYSYMBOL_INTEGER = 5,                    /* INTEGER  */
  YYSYMBOL_REAL = 6,                       /* REAL  */
  YYSYMBOL_ASSIGN = 7,                     /* ASSIGN  */
  YYSYMBOL_OR = 8,                         /* OR  */
  YYSYMBOL_AND = 9,                        /* AND  */
  YYSYMBOL_EQUAL = 10,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 11,                 /* NOT_EQUAL  */
  YYSYMBOL_GREATER_THAN = 12,              /* GREATER_THAN  */
  YYSYMBOL_GREATER_EQUAL = 13,             /* GREATER_EQUAL  */
  YYSYMBOL_LESSER_THAN = 14,               /* LESSER_THAN  */
  YYSYMBOL_LESSER_EQUAL = 15,              /* LESSER_EQUAL  */
  YYSYMBOL_LOWER_THAN_ELSE = 16,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_PLUS = 17,                      /* PLUS  */
  YYSYMBOL_MINUS = 18,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 19,                  /* MULTIPLY  */
  YYSYMBOL_DIV = 20,                       /* DIV  */
  YYSYMBOL_MODULO = 21,                    /* MODULO  */
  YYSYMBOL_UMINUS = 22,                    /* UMINUS  */
  YYSYMBOL_NOT = 23,                       /* NOT  */
  YYSYMBOL_INCREMENT = 24,                 /* INCREMENT  */
  YYSYMBOL_DECREMENT = 25,                 /* DECREMENT  */
  YYSYMBOL_DOT = 26,                       /* DOT  */
  YYSYMBOL_DOUBLE_DOT = 27,                /* DOUBLE_DOT  */
  YYSYMBOL_LEFT_SQR_BRK = 28,              /* LEFT_SQR_BRK  */
  YYSYMBOL_RIGHT_SQR_BRK = 29,             /* RIGHT_SQR_BRK  */
  YYSYMBOL_LEFT_PARENTHESIS = 30,          /* LEFT_PARENTHESIS  */
  YYSYMBOL_RIGHT_PARENTHESIS = 31,         /* RIGHT_PARENTHESIS  */
  YYSYMBOL_SEMICOLON = 32,                 /* SEMICOLON  */
  YYSYMBOL_LEFT_BRK = 33,                  /* LEFT_BRK  */
  YYSYMBOL_RIGHT_BRK = 34,                 /* RIGHT_BRK  */
  YYSYMBOL_COMMA = 35,                     /* COMMA  */
  YYSYMBOL_COLON = 36,                     /* COLON  */
  YYSYMBOL_DOUBLE_COLON = 37,              /* DOUBLE_COLON  */
  YYSYMBOL_IF = 38,                        /* IF  */
  YYSYMBOL_ELSE = 39,                      /* ELSE  */
  YYSYMBOL_WHILE = 40,                     /* WHILE  */
  YYSYMBOL_FOR = 41,                       /* FOR  */
  YYSYMBOL_FUNC = 42,                      /* FUNC  */
  YYSYMBOL_RT = 43,                        /* RT  */
  YYSYMBOL_BRK = 44,                       /* BRK  */
  YYSYMBOL_CONT = 45,                      /* CONT  */
  YYSYMBOL_LOCAL_TKN = 46,                 /* LOCAL_TKN  */
  YYSYMBOL_TRUE_TKN = 47,                  /* TRUE_TKN  */
  YYSYMBOL_FALSE_TKN = 48,                 /* FALSE_TKN  */
  YYSYMBOL_ENDL = 49,                      /* ENDL  */
  YYSYMBOL_NIL = 50,                       /* NIL  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_program = 52,                   /* program  */
  YYSYMBOL_statements = 53,                /* statements  */
  YYSYMBOL_loopstart = 54,                 /* loopstart  */
  YYSYMBOL_loopend = 55,                   /* loopend  */
  YYSYMBOL_loopstmt = 56,                  /* loopstmt  */
  YYSYMBOL_stmt = 57,                      /* stmt  */
  YYSYMBOL_expression = 58,                /* expression  */
  YYSYMBOL_59_1 = 59,                      /* $@1  */
  YYSYMBOL_60_2 = 60,                      /* $@2  */
  YYSYMBOL_61_3 = 61,                      /* $@3  */
  YYSYMBOL_62_4 = 62,                      /* $@4  */
  YYSYMBOL_M = 63,                         /* M  */
  YYSYMBOL_N = 64,                         /* N  */
  YYSYMBOL_term = 65,                      /* term  */
  YYSYMBOL_assignexr = 66,                 /* assignexr  */
  YYSYMBOL_primary = 67,                   /* primary  */
  YYSYMBOL_lvalue = 68,                    /* lvalue  */
  YYSYMBOL_member = 69,                    /* member  */
  YYSYMBOL_call = 70,                      /* call  */
  YYSYMBOL_callsuffix = 71,                /* callsuffix  */
  YYSYMBOL_normcall = 72,                  /* normcall  */
  YYSYMBOL_methodcall = 73,                /* methodcall  */
  YYSYMBOL_elist = 74,                     /* elist  */
  YYSYMBOL_objectdef = 75,                 /* objectdef  */
  YYSYMBOL_indexed = 76,                   /* indexed  */
  YYSYMBOL_indexedelem = 77,               /* indexedelem  */
  YYSYMBOL_block = 78,                     /* block  */
  YYSYMBOL_79_5 = 79,                      /* $@5  */
  YYSYMBOL_80_6 = 80,                      /* $@6  */
  YYSYMBOL_funcblockstart = 81,            /* funcblockstart  */
  YYSYMBOL_funcblockend = 82,              /* funcblockend  */
  YYSYMBOL_funcname = 83,                  /* funcname  */
  YYSYMBOL_funcprefix = 84,                /* funcprefix  */
  YYSYMBOL_funcargs = 85,                  /* funcargs  */
  YYSYMBOL_funcbody = 86,                  /* funcbody  */
  YYSYMBOL_F = 87,                         /* F  */
  YYSYMBOL_funcdef = 88,                   /* funcdef  */
  YYSYMBOL_const = 89,                     /* const  */
  YYSYMBOL_idlist = 90,                    /* idlist  */
  YYSYMBOL_91_7 = 91,                      /* $@7  */
  YYSYMBOL_idlists = 92,                   /* idlists  */
  YYSYMBOL_93_8 = 93,                      /* $@8  */
  YYSYMBOL_ifprefix = 94,                  /* ifprefix  */
  YYSYMBOL_elseprefix = 95,                /* elseprefix  */
  YYSYMBOL_ifstmt = 96,                    /* ifstmt  */
  YYSYMBOL_whilestart = 97,                /* whilestart  */
  YYSYMBOL_whilecond = 98,                 /* whilecond  */
  YYSYMBOL_whilestmt = 99,                 /* whilestmt  */
  YYSYMBOL_forprefix = 100,                /* forprefix  */
  YYSYMBOL_forstmt = 101,                  /* forstmt  */
  YYSYMBOL_102_9 = 102,                    /* $@9  */
  YYSYMBOL_103_10 = 103,                   /* $@10  */
  YYSYMBOL_returnstmt = 104                /* returnstmt  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  73
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   554

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  114
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  200

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   305


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    89,    89,    94,   105,   109,   112,   115,   119,   121,
     123,   125,   127,   129,   133,   137,   139,   141,   145,   147,
     152,   156,   160,   164,   168,   172,   176,   180,   184,   184,
     190,   190,   196,   196,   200,   200,   204,   207,   210,   213,
     215,   217,   219,   221,   223,   225,   227,   231,   249,   252,
     254,   256,   260,   264,   279,   291,   303,   306,   309,   313,
     314,   317,   322,   326,   330,   333,   338,   343,   348,   352,
     355,   359,   362,   367,   370,   374,   379,   379,   381,   381,
     385,   388,   391,   392,   398,   412,   421,   424,   428,   445,
     450,   454,   457,   461,   465,   467,   472,   472,   480,   483,
     483,   490,   494,   498,   503,   505,   518,   521,   527,   530,
     534,   535,   534,   542,   553
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "STRING",
  "INTEGER", "REAL", "ASSIGN", "OR", "AND", "EQUAL", "NOT_EQUAL",
  "GREATER_THAN", "GREATER_EQUAL", "LESSER_THAN", "LESSER_EQUAL",
  "LOWER_THAN_ELSE", "PLUS", "MINUS", "MULTIPLY", "DIV", "MODULO",
  "UMINUS", "NOT", "INCREMENT", "DECREMENT", "DOT", "DOUBLE_DOT",
  "LEFT_SQR_BRK", "RIGHT_SQR_BRK", "LEFT_PARENTHESIS", "RIGHT_PARENTHESIS",
  "SEMICOLON", "LEFT_BRK", "RIGHT_BRK", "COMMA", "COLON", "DOUBLE_COLON",
  "IF", "ELSE", "WHILE", "FOR", "FUNC", "RT", "BRK", "CONT", "LOCAL_TKN",
  "TRUE_TKN", "FALSE_TKN", "ENDL", "NIL", "$accept", "program",
  "statements", "loopstart", "loopend", "loopstmt", "stmt", "expression",
  "$@1", "$@2", "$@3", "$@4", "M", "N", "term", "assignexr", "primary",
  "lvalue", "member", "call", "callsuffix", "normcall", "methodcall",
  "elist", "objectdef", "indexed", "indexedelem", "block", "$@5", "$@6",
  "funcblockstart", "funcblockend", "funcname", "funcprefix", "funcargs",
  "funcbody", "F", "funcdef", "const", "idlist", "$@7", "idlists", "$@8",
  "ifprefix", "elseprefix", "ifstmt", "whilestart", "whilecond",
  "whilestmt", "forprefix", "forstmt", "$@9", "$@10", "returnstmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-169)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-79)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     187,  -169,  -169,  -169,  -169,   291,   291,    16,    16,    19,
     235,  -169,   -30,     5,   -21,  -169,   -13,    23,   243,    -1,
       3,    37,  -169,  -169,  -169,  -169,    50,   187,  -169,   371,
    -169,  -169,  -169,    48,  -169,     6,  -169,  -169,    30,  -169,
    -169,   187,  -169,    33,  -169,  -169,  -169,  -169,  -169,  -169,
      28,   -14,     6,   -14,   291,   334,    42,    59,    56,   419,
      46,   187,    58,  -169,   291,   291,  -169,  -169,  -169,   387,
    -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,   291,
     291,   291,   291,   291,   291,   291,   291,   291,  -169,   291,
    -169,  -169,    92,    93,   291,   291,  -169,  -169,  -169,    95,
     291,   291,    96,  -169,    63,   291,  -169,   291,    66,   117,
     291,  -169,  -169,    70,  -169,    74,   139,  -169,   434,    78,
    -169,  -169,  -169,   291,   291,    94,    94,    94,    94,    38,
      38,  -169,  -169,  -169,   508,  -169,    87,   464,    88,  -169,
     486,    90,  -169,   102,    85,  -169,   187,   449,   187,  -169,
     108,    74,   291,  -169,  -169,   291,  -169,  -169,  -169,   291,
     291,   312,   312,   291,  -169,  -169,  -169,  -169,   105,  -169,
    -169,  -169,  -169,  -169,  -169,  -169,   353,   110,   291,   521,
     533,   116,   146,  -169,  -169,  -169,  -169,  -169,  -169,   403,
    -169,  -169,  -169,  -169,  -169,   105,  -169,  -169,  -169,  -169
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    53,    91,    89,    90,     0,     0,     0,     0,    70,
       0,    17,    76,     0,     0,   106,     0,    83,     0,     0,
       0,     0,    93,    94,    95,    92,     0,     2,     4,     0,
      36,    18,    46,    48,    56,    49,    50,    15,     0,    16,
      52,     0,     9,     0,    10,    38,    11,    12,    40,    41,
       0,    42,     0,    44,     0,    68,     0,     0,    73,     0,
       0,     0,     0,    55,     0,    70,    82,    84,   114,     0,
      13,    14,    54,     1,     3,    34,    32,    28,    30,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     8,     0,
      43,    45,     0,     0,     0,    70,    62,    64,    65,     0,
       0,    70,    98,    80,   104,     0,     5,    70,     0,     0,
      70,    71,    72,     0,    39,    51,     0,    79,     0,     0,
     113,    37,    37,     0,     0,    24,    25,    26,    27,    19,
      20,    21,    22,    23,    47,    57,     0,     0,     0,    59,
       0,     0,    96,     0,     0,   103,     0,     0,     0,   108,
       0,     0,     0,    69,    74,    70,    77,   102,    37,     0,
       0,    29,    31,    70,    58,    66,    60,    61,   101,    85,
      86,    87,   105,   107,     6,    38,     0,     0,     0,    35,
      33,     0,     0,    97,    81,     7,   110,    75,    63,     0,
      67,    99,    88,   111,   109,   101,     5,   100,    38,   112
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -169,  -169,    89,  -169,  -169,   -45,   -26,     0,  -169,  -169,
    -169,  -169,  -120,  -168,  -169,  -169,  -169,    13,  -169,    21,
    -169,  -169,  -169,   -62,  -169,    41,  -169,    11,  -169,  -169,
    -169,  -169,  -169,  -169,  -169,  -169,  -169,     1,  -169,  -169,
    -169,   -39,  -169,  -169,  -169,  -169,  -169,  -169,  -169,  -169,
    -169,  -169,  -169,  -169
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    26,    27,   148,   185,   149,    28,    55,   123,   124,
     122,   121,   159,   107,    30,    31,    32,    33,    34,    35,
      96,    97,    98,    56,    36,    57,    58,    37,    61,    62,
     144,   192,    67,    38,   103,   171,   184,    39,    40,   143,
     168,   183,   195,    41,   146,    42,    43,   106,    44,    45,
      46,   193,   196,    47
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,    74,   160,   119,   -78,    48,    49,   186,    63,    64,
      59,    60,    92,    93,    94,   104,    95,    65,    69,     1,
      51,    53,     1,     2,     3,     4,    66,    29,    52,    52,
     199,    70,    99,   138,   100,    71,   101,     5,   178,   141,
      72,    29,     6,     7,     8,   150,    50,     9,   153,    10,
      73,   108,    54,    13,   109,    89,    13,    85,    86,    87,
     102,    29,    21,   105,   118,    21,    22,    23,    24,    25,
      17,   111,    90,    91,    92,    93,    94,   115,    95,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   112,   134,
      74,   113,   117,   177,   137,   135,   136,   151,   139,   142,
     140,   181,   145,    54,   155,   147,   -79,   -79,   -79,   -79,
     158,    83,    84,    85,    86,    87,    29,   163,    12,   165,
     172,   167,   174,   161,   162,    75,    76,    77,    78,    79,
      80,    81,    82,   169,    83,    84,    85,    86,    87,   175,
     182,   188,     1,     2,     3,     4,    29,   190,    29,   191,
     116,   198,   176,   152,   154,   170,   197,     5,     0,   179,
     180,     0,     6,     7,     8,     0,     0,     9,     0,    10,
       0,    11,    12,   156,     0,     0,    13,    14,   189,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
       1,     2,     3,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     5,     0,     0,     0,     0,
       6,     7,     8,     0,     0,     9,     0,    10,     0,    11,
      12,     0,     0,     0,    13,    14,     0,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,     1,     2,
       3,     4,     0,     0,     0,     0,     1,     2,     3,     4,
       0,     0,     0,     5,     0,     0,     0,     0,     6,     7,
       8,     5,     0,     9,     0,    10,     6,     7,     8,     0,
       0,     9,    13,    10,     0,    68,     0,    17,     0,     0,
      13,    21,    22,    23,    24,    25,     0,     0,     0,    21,
      22,    23,    24,    25,     1,     2,     3,     4,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       0,     0,     0,     0,     6,     7,     8,     0,     0,     9,
       0,    10,   -79,   -79,    79,    80,    81,    82,    13,    83,
      84,    85,    86,    87,     0,     0,     0,    21,    22,    23,
      24,    25,    75,    76,    77,    78,    79,    80,    81,    82,
       0,    83,    84,    85,    86,    87,     0,     0,     0,     0,
       0,    75,    76,    77,    78,    79,    80,    81,    82,   110,
      83,    84,    85,    86,    87,     0,     0,     0,     0,    75,
      76,    77,    78,    79,    80,    81,    82,   187,    83,    84,
      85,    86,    87,     0,     0,    75,    76,    77,    78,    79,
      80,    81,    82,    88,    83,    84,    85,    86,    87,     0,
       0,    75,    76,    77,    78,    79,    80,    81,    82,   120,
      83,    84,    85,    86,    87,     0,     0,    75,    76,    77,
      78,    79,    80,    81,    82,   194,    83,    84,    85,    86,
      87,     0,    75,    76,    77,    78,    79,    80,    81,    82,
     114,    83,    84,    85,    86,    87,     0,    75,    76,    77,
      78,    79,    80,    81,    82,   157,    83,    84,    85,    86,
      87,     0,    75,    76,    77,    78,    79,    80,    81,    82,
     173,    83,    84,    85,    86,    87,     0,     0,     0,     0,
       0,     0,     0,   164,    75,    76,    77,    78,    79,    80,
      81,    82,     0,    83,    84,    85,    86,    87,     0,     0,
       0,     0,     0,     0,     0,   166,    75,    76,    77,    78,
      79,    80,    81,    82,     0,    83,    84,    85,    86,    87,
      76,    77,    78,    79,    80,    81,    82,     0,    83,    84,
      85,    86,    87,    77,    78,    79,    80,    81,    82,     0,
      83,    84,    85,    86,    87
};

static const yytype_int16 yycheck[] =
{
       0,    27,   122,    65,    34,     5,     6,   175,     3,    30,
      10,    10,    26,    27,    28,    41,    30,    30,    18,     3,
       7,     8,     3,     4,     5,     6,     3,    27,     7,     8,
     198,    32,    26,    95,    28,    32,    30,    18,   158,   101,
       3,    41,    23,    24,    25,   107,    30,    28,   110,    30,
       0,    50,    33,    37,    54,     7,    37,    19,    20,    21,
      30,    61,    46,    30,    64,    46,    47,    48,    49,    50,
      42,    29,    24,    25,    26,    27,    28,    31,    30,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    29,    89,
     116,    35,    34,   155,    94,     3,     3,    31,     3,     3,
     100,   163,    39,    33,    30,   105,    12,    13,    14,    15,
      32,    17,    18,    19,    20,    21,   116,    30,    33,    31,
     146,    31,   148,   123,   124,     8,     9,    10,    11,    12,
      13,    14,    15,    31,    17,    18,    19,    20,    21,    31,
      35,    31,     3,     4,     5,     6,   146,    31,   148,     3,
      61,   196,   152,    36,   113,   144,   195,    18,    -1,   159,
     160,    -1,    23,    24,    25,    -1,    -1,    28,    -1,    30,
      -1,    32,    33,    34,    -1,    -1,    37,    38,   178,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
       3,     4,     5,     6,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,
      23,    24,    25,    -1,    -1,    28,    -1,    30,    -1,    32,
      33,    -1,    -1,    -1,    37,    38,    -1,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,     3,     4,
       5,     6,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
      -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,    23,    24,
      25,    18,    -1,    28,    -1,    30,    23,    24,    25,    -1,
      -1,    28,    37,    30,    -1,    32,    -1,    42,    -1,    -1,
      37,    46,    47,    48,    49,    50,    -1,    -1,    -1,    46,
      47,    48,    49,    50,     3,     4,     5,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,
      -1,    -1,    -1,    -1,    23,    24,    25,    -1,    -1,    28,
      -1,    30,    10,    11,    12,    13,    14,    15,    37,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    46,    47,    48,
      49,    50,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,     8,     9,    10,    11,    12,    13,    14,    15,    35,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,     8,
       9,    10,    11,    12,    13,    14,    15,    34,    17,    18,
      19,    20,    21,    -1,    -1,     8,     9,    10,    11,    12,
      13,    14,    15,    32,    17,    18,    19,    20,    21,    -1,
      -1,     8,     9,    10,    11,    12,    13,    14,    15,    32,
      17,    18,    19,    20,    21,    -1,    -1,     8,     9,    10,
      11,    12,    13,    14,    15,    32,    17,    18,    19,    20,
      21,    -1,     8,     9,    10,    11,    12,    13,    14,    15,
      31,    17,    18,    19,    20,    21,    -1,     8,     9,    10,
      11,    12,    13,    14,    15,    31,    17,    18,    19,    20,
      21,    -1,     8,     9,    10,    11,    12,    13,    14,    15,
      31,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    29,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    17,    18,    19,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    29,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    17,    18,    19,    20,    21,
       9,    10,    11,    12,    13,    14,    15,    -1,    17,    18,
      19,    20,    21,    10,    11,    12,    13,    14,    15,    -1,
      17,    18,    19,    20,    21
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,    18,    23,    24,    25,    28,
      30,    32,    33,    37,    38,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    52,    53,    57,    58,
      65,    66,    67,    68,    69,    70,    75,    78,    84,    88,
      89,    94,    96,    97,    99,   100,   101,   104,    58,    58,
      30,    68,    70,    68,    33,    58,    74,    76,    77,    58,
      88,    79,    80,     3,    30,    30,     3,    83,    32,    58,
      32,    32,     3,     0,    57,     8,     9,    10,    11,    12,
      13,    14,    15,    17,    18,    19,    20,    21,    32,     7,
      24,    25,    26,    27,    28,    30,    71,    72,    73,    26,
      28,    30,    30,    85,    57,    30,    98,    64,    88,    58,
      35,    29,    29,    35,    31,    31,    53,    34,    58,    74,
      32,    62,    61,    59,    60,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,     3,     3,    58,    74,     3,
      58,    74,     3,    90,    81,    39,    95,    58,    54,    56,
      74,    31,    36,    74,    76,    30,    34,    31,    32,    63,
      63,    58,    58,    30,    29,    31,    29,    31,    91,    31,
      78,    86,    57,    31,    57,    31,    58,    74,    63,    58,
      58,    74,    35,    92,    87,    55,    64,    34,    31,    58,
      31,     3,    82,   102,    32,    93,   103,    92,    56,    64
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    53,    53,    54,    55,    56,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    59,    58,
      60,    58,    61,    58,    62,    58,    58,    63,    64,    65,
      65,    65,    65,    65,    65,    65,    65,    66,    67,    67,
      67,    67,    67,    68,    68,    68,    68,    69,    69,    69,
      69,    70,    70,    70,    71,    71,    72,    73,    74,    74,
      74,    75,    75,    76,    76,    77,    79,    78,    80,    78,
      81,    82,    83,    83,    84,    85,    86,    87,    88,    89,
      89,    89,    89,    89,    89,    89,    91,    90,    90,    93,
      92,    92,    94,    95,    96,    96,    97,    98,    99,   100,
     102,   103,   101,   104,   104
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     0,     0,     3,     2,     1,
       1,     1,     1,     2,     2,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     0,     4,
       0,     4,     0,     5,     0,     5,     1,     0,     0,     3,
       2,     2,     2,     2,     2,     2,     1,     3,     1,     1,
       1,     3,     1,     1,     2,     2,     1,     3,     4,     3,
       4,     4,     2,     6,     1,     1,     3,     5,     1,     3,
       0,     3,     3,     1,     3,     5,     0,     4,     0,     3,
       0,     0,     1,     0,     2,     3,     1,     0,     6,     1,
       1,     1,     1,     1,     1,     1,     0,     3,     0,     0,
       4,     0,     4,     1,     2,     4,     1,     3,     3,     7,
       0,     0,     9,     3,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: statements  */
#line 89 "AlphaCompiler/syntax_analyzer.y"
                           { if(printSyntax) printf("line %d:program->stmt statements\n",yylineno);}
#line 1690 "AlphaCompiler/parser.c"
    break;

  case 3: /* statements: statements stmt  */
#line 94 "AlphaCompiler/syntax_analyzer.y"
                               {
                        resettemp();
                        (yyval.statement) = malloc(sizeof(struct stmt_t));
                        int brk1=0, brk2=0, cont1=0, cont2=0, ret1=0, ret2=0;
                        if((yyvsp[-1].statement)){brk1=(yyvsp[-1].statement)->breakList; cont1=(yyvsp[-1].statement)->contList; ret1=(yyvsp[-1].statement)->retList;}
                        if((yyvsp[0].statement)){brk2=(yyvsp[0].statement)->breakList; cont2=(yyvsp[0].statement)->contList; ret2=(yyvsp[0].statement)->retList;}
                        (yyval.statement)->breakList = mergelist(brk1,brk2);
                        (yyval.statement)->contList = mergelist(cont1,cont2);
                        (yyval.statement)->retList = mergelist(ret1,ret2);
                        }
#line 1705 "AlphaCompiler/parser.c"
    break;

  case 4: /* statements: stmt  */
#line 105 "AlphaCompiler/syntax_analyzer.y"
                     {(yyval.statement)=(yyvsp[0].statement);}
#line 1711 "AlphaCompiler/parser.c"
    break;

  case 5: /* loopstart: %empty  */
#line 109 "AlphaCompiler/syntax_analyzer.y"
                {loopcounter++;}
#line 1717 "AlphaCompiler/parser.c"
    break;

  case 6: /* loopend: %empty  */
#line 112 "AlphaCompiler/syntax_analyzer.y"
                {loopcounter--;}
#line 1723 "AlphaCompiler/parser.c"
    break;

  case 7: /* loopstmt: loopstart stmt loopend  */
#line 115 "AlphaCompiler/syntax_analyzer.y"
                                      { (yyval.statement) = (yyvsp[-1].statement);}
#line 1729 "AlphaCompiler/parser.c"
    break;

  case 8: /* stmt: expression SEMICOLON  */
#line 119 "AlphaCompiler/syntax_analyzer.y"
                                    { if(printSyntax)  printf("line %d:stmt->expression;\n",yylineno); icode_bool_stmt((yyvsp[-1].expression)); (yyval.statement)=NULL;}
#line 1735 "AlphaCompiler/parser.c"
    break;

  case 9: /* stmt: ifstmt  */
#line 121 "AlphaCompiler/syntax_analyzer.y"
                       { if(printSyntax)printf("line %d:stmt->ifstmt\n",yylineno); (yyval.statement)=(yyvsp[0].statement);}
#line 1741 "AlphaCompiler/parser.c"
    break;

  case 10: /* stmt: whilestmt  */
#line 123 "AlphaCompiler/syntax_analyzer.y"
                          {if(printSyntax) printf("line %d:stmt->whilestmt\n",yylineno);(yyval.statement)=NULL;}
#line 1747 "AlphaCompiler/parser.c"
    break;

  case 11: /* stmt: forstmt  */
#line 125 "AlphaCompiler/syntax_analyzer.y"
                        { if(printSyntax) printf("line %d:stmt->forstmt\n",yylineno); (yyval.statement)=NULL;}
#line 1753 "AlphaCompiler/parser.c"
    break;

  case 12: /* stmt: returnstmt  */
#line 127 "AlphaCompiler/syntax_analyzer.y"
                           { if(printSyntax) printf("line %d:stmt->returnstmt\n",yylineno); (yyval.statement)=(yyvsp[0].statement);}
#line 1759 "AlphaCompiler/parser.c"
    break;

  case 13: /* stmt: BRK SEMICOLON  */
#line 129 "AlphaCompiler/syntax_analyzer.y"
                              {  if(loopcounter<=0)yyerror("cannot 'break' when not in loop");if(printSyntax) printf("line %d:stmt->BREAK;\n",yylineno);
                                (yyval.statement) = icode_break();
                                }
#line 1767 "AlphaCompiler/parser.c"
    break;

  case 14: /* stmt: CONT SEMICOLON  */
#line 133 "AlphaCompiler/syntax_analyzer.y"
                               { if(loopcounter<=0)yyerror("cannot 'continue' when not in loop");if(printSyntax) printf("line %d:stmt->CONT;\n",yylineno);
                                  (yyval.statement) = icode_continue();
                                  }
#line 1775 "AlphaCompiler/parser.c"
    break;

  case 15: /* stmt: block  */
#line 137 "AlphaCompiler/syntax_analyzer.y"
                      { if(printSyntax) printf("line %d:stmt->block\n",yylineno);}
#line 1781 "AlphaCompiler/parser.c"
    break;

  case 16: /* stmt: funcdef  */
#line 139 "AlphaCompiler/syntax_analyzer.y"
                        { if(printSyntax) printf("line %d:stmt->funcdef\n",yylineno); (yyval.statement)=NULL;}
#line 1787 "AlphaCompiler/parser.c"
    break;

  case 17: /* stmt: SEMICOLON  */
#line 141 "AlphaCompiler/syntax_analyzer.y"
                          {if(printSyntax) printf("line %d:stmt->;\n",yylineno); (yyval.statement)=NULL;}
#line 1793 "AlphaCompiler/parser.c"
    break;

  case 18: /* expression: assignexr  */
#line 145 "AlphaCompiler/syntax_analyzer.y"
                          {if(printSyntax) printf("line %d:expression->assignexr\n",yylineno);}
#line 1799 "AlphaCompiler/parser.c"
    break;

  case 19: /* expression: expression PLUS expression  */
#line 147 "AlphaCompiler/syntax_analyzer.y"
                                            { 
                                                (yyval.expression) = icode_arithmetic_plus((yyvsp[-2].expression),(yyvsp[0].expression));
                                                if(printSyntax) printf("line %d:expression->expression + expression\n",yylineno);                                   
                                                }
#line 1808 "AlphaCompiler/parser.c"
    break;

  case 20: /* expression: expression MINUS expression  */
#line 152 "AlphaCompiler/syntax_analyzer.y"
                                            {   
                                                (yyval.expression) = icode_arithmetic_minus((yyvsp[-2].expression),(yyvsp[0].expression));
                                                if(printSyntax) printf("line %d:expression->expression - expression\n",yylineno);}
#line 1816 "AlphaCompiler/parser.c"
    break;

  case 21: /* expression: expression MULTIPLY expression  */
#line 156 "AlphaCompiler/syntax_analyzer.y"
                                               {    
                                                (yyval.expression) = icode_arithmetic_mul((yyvsp[-2].expression),(yyvsp[0].expression));
                                                if(printSyntax) printf("line %d:expression->expression * expression\n",yylineno);}
#line 1824 "AlphaCompiler/parser.c"
    break;

  case 22: /* expression: expression DIV expression  */
#line 160 "AlphaCompiler/syntax_analyzer.y"
                                          {     
                                                (yyval.expression) = icode_arithmetic_i_div((yyvsp[-2].expression),(yyvsp[0].expression));
                                                if(printSyntax) printf("line %d:expression->expression / expression\n",yylineno);}
#line 1832 "AlphaCompiler/parser.c"
    break;

  case 23: /* expression: expression MODULO expression  */
#line 164 "AlphaCompiler/syntax_analyzer.y"
                                             {  
                                                (yyval.expression) = icode_arithmetic_mod((yyvsp[-2].expression),(yyvsp[0].expression));
                                                if(printSyntax) printf("line %d:expression->expression %c expression\n",yylineno,'%');}
#line 1840 "AlphaCompiler/parser.c"
    break;

  case 24: /* expression: expression GREATER_THAN expression  */
#line 168 "AlphaCompiler/syntax_analyzer.y"
                                                   { 
                                                 (yyval.expression) = icode_relop((yyvsp[-2].expression),(yyvsp[0].expression),if_greater); 
                                                 if(printSyntax) printf("line %d:expression->expression > expression\n",yylineno);}
#line 1848 "AlphaCompiler/parser.c"
    break;

  case 25: /* expression: expression GREATER_EQUAL expression  */
#line 172 "AlphaCompiler/syntax_analyzer.y"
                                                    { 
                                                 (yyval.expression) = icode_relop((yyvsp[-2].expression),(yyvsp[0].expression),if_greatereq);   
                                                 if(printSyntax) printf("line %d:expression->expression >= expression\n",yylineno);}
#line 1856 "AlphaCompiler/parser.c"
    break;

  case 26: /* expression: expression LESSER_THAN expression  */
#line 176 "AlphaCompiler/syntax_analyzer.y"
                                                  { 
                                                (yyval.expression) = icode_relop((yyvsp[-2].expression),(yyvsp[0].expression),if_less); 
                                                if(printSyntax) printf("line %d:expression->expression < expression\n",yylineno);}
#line 1864 "AlphaCompiler/parser.c"
    break;

  case 27: /* expression: expression LESSER_EQUAL expression  */
#line 180 "AlphaCompiler/syntax_analyzer.y"
                                                   { 
                                                (yyval.expression) = icode_relop((yyvsp[-2].expression),(yyvsp[0].expression),if_lesseq);    
                                                if(printSyntax) printf("line %d:expression->expression <= expression\n",yylineno);}
#line 1872 "AlphaCompiler/parser.c"
    break;

  case 28: /* $@1: %empty  */
#line 184 "AlphaCompiler/syntax_analyzer.y"
                                 {icode_bool_stmt((yyvsp[-1].expression));}
#line 1878 "AlphaCompiler/parser.c"
    break;

  case 29: /* expression: expression EQUAL $@1 expression  */
#line 184 "AlphaCompiler/syntax_analyzer.y"
                                                                  {  
                                                icode_bool_stmt((yyvsp[0].expression));
                                                (yyval.expression) = icode_relop((yyvsp[-3].expression),(yyvsp[0].expression),if_eq); 
                                                icode_bool_stmt((yyval.expression)); 
                                                if(printSyntax) printf("line %d:expression->expression == expression \n",yylineno);}
#line 1888 "AlphaCompiler/parser.c"
    break;

  case 30: /* $@2: %empty  */
#line 190 "AlphaCompiler/syntax_analyzer.y"
                                     {icode_bool_stmt((yyvsp[-1].expression));}
#line 1894 "AlphaCompiler/parser.c"
    break;

  case 31: /* expression: expression NOT_EQUAL $@2 expression  */
#line 190 "AlphaCompiler/syntax_analyzer.y"
                                                                      {   
                                                icode_bool_stmt((yyvsp[0].expression));
                                                (yyval.expression) = icode_relop((yyvsp[-3].expression),(yyvsp[0].expression),if_noteq); 
                                                icode_bool_stmt((yyval.expression));
                                                if(printSyntax) printf("line %d:expression->expression != expression\n",yylineno);}
#line 1904 "AlphaCompiler/parser.c"
    break;

  case 32: /* $@3: %empty  */
#line 196 "AlphaCompiler/syntax_analyzer.y"
                               {(yyvsp[-1].expression) = make_boolean_expr((yyvsp[-1].expression));}
#line 1910 "AlphaCompiler/parser.c"
    break;

  case 33: /* expression: expression AND $@3 M expression  */
#line 196 "AlphaCompiler/syntax_analyzer.y"
                                                                         {   
                                                (yyval.expression) = icode_and((yyvsp[-4].expression),(yyvsp[0].expression),(yyvsp[-1].mquad));
                                                if(printSyntax) printf("line %d:expression->expression and expression\n",yylineno);}
#line 1918 "AlphaCompiler/parser.c"
    break;

  case 34: /* $@4: %empty  */
#line 200 "AlphaCompiler/syntax_analyzer.y"
                              {(yyvsp[-1].expression) = make_boolean_expr((yyvsp[-1].expression));}
#line 1924 "AlphaCompiler/parser.c"
    break;

  case 35: /* expression: expression OR $@4 M expression  */
#line 200 "AlphaCompiler/syntax_analyzer.y"
                                                                        {    
                                                (yyval.expression) = icode_or((yyvsp[-4].expression),(yyvsp[0].expression),(yyvsp[-1].mquad));              
                                                if(printSyntax) printf("line %d:expression->expression or expression\n",yylineno);}
#line 1932 "AlphaCompiler/parser.c"
    break;

  case 36: /* expression: term  */
#line 204 "AlphaCompiler/syntax_analyzer.y"
                      {if(printSyntax) printf("line %d:expression->term\n",yylineno);}
#line 1938 "AlphaCompiler/parser.c"
    break;

  case 37: /* M: %empty  */
#line 207 "AlphaCompiler/syntax_analyzer.y"
                {(yyval.mquad) = nextquadlabel();}
#line 1944 "AlphaCompiler/parser.c"
    break;

  case 38: /* N: %empty  */
#line 210 "AlphaCompiler/syntax_analyzer.y"
                {(yyval.mquad) = nextquadlabel(); emit(jump,NULL,NULL,NULL,0,yylineno);}
#line 1950 "AlphaCompiler/parser.c"
    break;

  case 39: /* term: LEFT_PARENTHESIS expression RIGHT_PARENTHESIS  */
#line 213 "AlphaCompiler/syntax_analyzer.y"
                                                              { (yyval.expression)=(yyvsp[-1].expression); if(printSyntax) printf("line %d:term->(expression)\n",yylineno);}
#line 1956 "AlphaCompiler/parser.c"
    break;

  case 40: /* term: MINUS expression  */
#line 215 "AlphaCompiler/syntax_analyzer.y"
                                       { (yyval.expression)=icode_uminus((yyvsp[0].expression)); if(printSyntax) printf("line %d:term->-expression\n",yylineno);}
#line 1962 "AlphaCompiler/parser.c"
    break;

  case 41: /* term: NOT expression  */
#line 217 "AlphaCompiler/syntax_analyzer.y"
                                        {(yyval.expression)=icode_not((yyvsp[0].expression)); if(printSyntax) printf("line %d:term->!expression\n",yylineno);}
#line 1968 "AlphaCompiler/parser.c"
    break;

  case 42: /* term: INCREMENT lvalue  */
#line 219 "AlphaCompiler/syntax_analyzer.y"
                                        { (yyval.expression)=icode_incr_lvalue((yyvsp[0].expression)); checkIfFunc((yyvsp[0].expression)); if(printSyntax) printf("line %d:term->++lvalue\n",yylineno);}
#line 1974 "AlphaCompiler/parser.c"
    break;

  case 43: /* term: lvalue INCREMENT  */
#line 221 "AlphaCompiler/syntax_analyzer.y"
                                        { (yyval.expression)= icode_lvalue_incr((yyvsp[-1].expression)); checkIfFunc((yyvsp[-1].expression)); if(printSyntax) printf("line %d:term->lvalue++\n",yylineno);}
#line 1980 "AlphaCompiler/parser.c"
    break;

  case 44: /* term: DECREMENT lvalue  */
#line 223 "AlphaCompiler/syntax_analyzer.y"
                                        { (yyval.expression)=icode_decr_lvalue((yyvsp[0].expression)); checkIfFunc((yyvsp[0].expression)); if(printSyntax) printf("line %d:term->--lvalue\n",yylineno);}
#line 1986 "AlphaCompiler/parser.c"
    break;

  case 45: /* term: lvalue DECREMENT  */
#line 225 "AlphaCompiler/syntax_analyzer.y"
                                        { (yyval.expression)= icode_lvalue_decr((yyvsp[-1].expression)); checkIfFunc((yyvsp[-1].expression)); if(printSyntax) printf("line %d:term->lvalue--\n",yylineno);}
#line 1992 "AlphaCompiler/parser.c"
    break;

  case 46: /* term: primary  */
#line 227 "AlphaCompiler/syntax_analyzer.y"
                        { (yyval.expression)=(yyvsp[0].expression); if(printSyntax) printf("line %d:term->primary\n",yylineno);}
#line 1998 "AlphaCompiler/parser.c"
    break;

  case 47: /* assignexr: lvalue ASSIGN expression  */
#line 231 "AlphaCompiler/syntax_analyzer.y"
                                       {    
                                            if((yyvsp[-2].expression)!=NULL && (yyvsp[0].expression)!=NULL){
                                                if((yyvsp[-2].expression)->sym!=NULL && (yyvsp[-2].expression)->sym->s_type==USERFUNC){
                                                    yyerror("functions and variables are not allowed to have the same name");
                                                    checkErrors();
                                                }
                                                if((yyvsp[-2].expression)->sym!=NULL && (yyvsp[-2].expression)->sym->s_type==LIBFUNC){
                                                    yyerror("oveshadowing library funstions is not allowed");
                                                    checkErrors();
                                                }
                                            }
                                            icode_bool_stmt((yyvsp[0].expression));
                                            
                                            (yyval.expression) = icode_assignment((yyvsp[-2].expression),(yyvsp[0].expression));
                                            
                                            if(printSyntax) printf("line %d:assignexr->lvalue=expression\n",yylineno);}
#line 2019 "AlphaCompiler/parser.c"
    break;

  case 48: /* primary: lvalue  */
#line 249 "AlphaCompiler/syntax_analyzer.y"
                                { if(printSyntax) printf("line %d:primary->lvalue\n",yylineno);
                                  (yyval.expression) = emit_iftableitem((yyvsp[0].expression));}
#line 2026 "AlphaCompiler/parser.c"
    break;

  case 49: /* primary: call  */
#line 252 "AlphaCompiler/syntax_analyzer.y"
                                {if(printSyntax) printf("line %d:primary->call\n",yylineno);}
#line 2032 "AlphaCompiler/parser.c"
    break;

  case 50: /* primary: objectdef  */
#line 254 "AlphaCompiler/syntax_analyzer.y"
                                {if(printSyntax) printf("line %d:primary->objectdef\n",yylineno);}
#line 2038 "AlphaCompiler/parser.c"
    break;

  case 51: /* primary: LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS  */
#line 256 "AlphaCompiler/syntax_analyzer.y"
                                                                { if(printSyntax) printf("line %d:primary->(funcdef)\n",yylineno);
                                                                 (yyval.expression) = newexpr(programfunc_e);
                                                                 (yyval.expression)->sym = (yyvsp[-1].symbolval);}
#line 2046 "AlphaCompiler/parser.c"
    break;

  case 52: /* primary: const  */
#line 260 "AlphaCompiler/syntax_analyzer.y"
                                {if(printSyntax) printf("line %d:primary->const\n",yylineno);}
#line 2052 "AlphaCompiler/parser.c"
    break;

  case 53: /* lvalue: ID  */
#line 264 "AlphaCompiler/syntax_analyzer.y"
                                    {   SymbolTableEntry rt = NULL;
                                        enum SymbolType type = USERFUNC;
                                        rt = SymTable_lookup(oSymTable, (yyvsp[0].strval), scope, ALL_TYPES);
                                        if(rt==NULL) rt = SymTable_lookupall(oSymTable, (yyvsp[0].strval), scope, fstack->top->def_scope, yylineno);
                                        if(rt==NULL) rt = SymTable_lookup(oSymTable, (yyvsp[0].strval), GLOBAL_SCOPE, ALL_TYPES);
                                        enum SymbolType stype = scope>0 ? LOCAL:GLOBAL; 
                                        if(rt == NULL && checkSymbol((yyvsp[0].strval), scope,LOCAL,FALSE)==0){
                                            rt = SymTable_insert(oSymTable, (yyvsp[0].strval), NULL, stype, yylineno, scope, currscopespace(), currscopeoffset()); 
                                            inccurrscopeoffset();
                                        }
                                       
                                        (yyval.expression) = lvalue_expr(rt);
                                        
                                        if(printSyntax) printf("line %d:lvalue->ID : %s\n",yylineno, (yyvsp[0].strval)); }
#line 2071 "AlphaCompiler/parser.c"
    break;

  case 54: /* lvalue: LOCAL_TKN ID  */
#line 279 "AlphaCompiler/syntax_analyzer.y"
                                    {   SymbolTableEntry rt = NULL;
                                        enum SymbolType s_type = scope>0? LOCAL:GLOBAL;
                                        rt = SymTable_lookup(oSymTable, (yyvsp[0].strval), scope, ALL_TYPES);
                                        enum SymbolType stype = scope>0 ? LOCAL:GLOBAL; 
                                        if(rt == NULL && checkSymbol((yyvsp[0].strval), scope,s_type,FALSE)==0) {
                                            rt = SymTable_insert(oSymTable, (yyvsp[0].strval), NULL, stype, yylineno, scope, currscopespace(), currscopeoffset());
                                            inccurrscopeoffset();
                                        }
                                        (yyval.expression) = lvalue_expr(rt);
                                        
                                        if(printSyntax) printf("line %d:lvalue->LOCAL_TKN ID\n",yylineno);}
#line 2087 "AlphaCompiler/parser.c"
    break;

  case 55: /* lvalue: DOUBLE_COLON ID  */
#line 291 "AlphaCompiler/syntax_analyzer.y"
                                    {   expr* val = NULL;
                                        SymbolTableEntry rt = NULL;
                                        rt = SymTable_lookup(oSymTable, (yyvsp[0].strval), GLOBAL_SCOPE, ALL_TYPES);
                                        if(rt!=NULL)
                                            val = lvalue_expr(rt);
                                        else{
                                            yyerror("cannot access global variable that is undefined");
                                            checkErrors();
                                        }  
                                        (yyval.expression)=val;
                                        if(printSyntax) printf("line %d:lvalue->::ID\n",yylineno);}
#line 2103 "AlphaCompiler/parser.c"
    break;

  case 56: /* lvalue: member  */
#line 303 "AlphaCompiler/syntax_analyzer.y"
                                        {(yyval.expression) = (yyvsp[0].expression); if(printSyntax) printf("line %d:lvalue->member\n",yylineno);}
#line 2109 "AlphaCompiler/parser.c"
    break;

  case 57: /* member: lvalue DOT ID  */
#line 306 "AlphaCompiler/syntax_analyzer.y"
                                                                {if(printSyntax) printf("line %d:member->lvalue.ID\n",yylineno);
                                                                (yyval.expression) = member_item((yyvsp[-2].expression), (yyvsp[0].strval));}
#line 2116 "AlphaCompiler/parser.c"
    break;

  case 58: /* member: lvalue LEFT_SQR_BRK expression RIGHT_SQR_BRK  */
#line 309 "AlphaCompiler/syntax_analyzer.y"
                                                                {if(printSyntax) printf("line %d:member->lvalue[expression]\n",yylineno);
                                                                (yyval.expression) = icode_member_expression_index((yyvsp[-3].expression),(yyvsp[-1].expression));
                                                                }
#line 2124 "AlphaCompiler/parser.c"
    break;

  case 59: /* member: call DOT ID  */
#line 313 "AlphaCompiler/syntax_analyzer.y"
                                                                {(yyval.expression) = member_item((yyvsp[-2].expression), (yyvsp[0].strval)); if(printSyntax) printf("line %d:member->call.ID\n",yylineno);}
#line 2130 "AlphaCompiler/parser.c"
    break;

  case 60: /* member: call LEFT_SQR_BRK expression RIGHT_SQR_BRK  */
#line 314 "AlphaCompiler/syntax_analyzer.y"
                                                                {(yyval.expression) = icode_call_sqr_expr_sqr((yyvsp[-3].expression),(yyvsp[-1].expression)); if(printSyntax) printf("line %d:member->call[expression]\n",yylineno);}
#line 2136 "AlphaCompiler/parser.c"
    break;

  case 61: /* call: call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS  */
#line 317 "AlphaCompiler/syntax_analyzer.y"
                                                                {   if(printSyntax) printf("line%d:call->(elist)\n",yylineno);
                                                                    (yyvsp[-1].expression) = reverse_elist((yyvsp[-1].expression));
                                                                    (yyval.expression) = make_call((yyvsp[-3].expression),(yyvsp[-1].expression));
                                                                }
#line 2145 "AlphaCompiler/parser.c"
    break;

  case 62: /* call: lvalue callsuffix  */
#line 322 "AlphaCompiler/syntax_analyzer.y"
                                    {   if(printSyntax) printf("line %d:call->lvalue callsuffix\n",yylineno);
                                        (yyval.expression) = icode_lvalue_callsufix((yyvsp[-1].expression),(yyvsp[0].callval));
                                    }
#line 2153 "AlphaCompiler/parser.c"
    break;

  case 63: /* call: LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS  */
#line 326 "AlphaCompiler/syntax_analyzer.y"
                                                                                                     {if(printSyntax) printf("line %d:call->(funcdef)(elist)\n",yylineno);
                                                                                                      (yyval.expression) = icode_funcdef_call((yyvsp[-4].symbolval),(yyvsp[-1].expression));}
#line 2160 "AlphaCompiler/parser.c"
    break;

  case 64: /* callsuffix: normcall  */
#line 330 "AlphaCompiler/syntax_analyzer.y"
                                {if(printSyntax) printf("line %d:callsuffix->normcall\n",yylineno);
                                 (yyval.callval) = (yyvsp[0].callval);}
#line 2167 "AlphaCompiler/parser.c"
    break;

  case 65: /* callsuffix: methodcall  */
#line 333 "AlphaCompiler/syntax_analyzer.y"
                                {if(printSyntax) printf("line %d:callsuffix->methodcall\n",yylineno);
                                 (yyval.callval) = (yyvsp[0].callval);}
#line 2174 "AlphaCompiler/parser.c"
    break;

  case 66: /* normcall: LEFT_PARENTHESIS elist RIGHT_PARENTHESIS  */
#line 338 "AlphaCompiler/syntax_analyzer.y"
                                                            {if(printSyntax) printf("line %d:normcall->(elist)\n",yylineno);
                                                             (yyval.callval)=icode_normcall((yyvsp[-1].expression));}
#line 2181 "AlphaCompiler/parser.c"
    break;

  case 67: /* methodcall: DOUBLE_DOT ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS  */
#line 343 "AlphaCompiler/syntax_analyzer.y"
                                                                        {method_call=1; if(printSyntax) printf("line %d:methodcall->..ID(elist)\n",yylineno);
                                                                         (yyval.callval) = icode_methodcall((yyvsp[-3].strval),(yyvsp[-1].expression));}
#line 2188 "AlphaCompiler/parser.c"
    break;

  case 68: /* elist: expression  */
#line 348 "AlphaCompiler/syntax_analyzer.y"
                                            {if(printSyntax) printf("line %d:elist->expression\n",yylineno);
                                            icode_bool_stmt((yyvsp[0].expression)); (yyval.expression)=(yyvsp[0].expression); (yyval.expression)->next=NULL;
                                            }
#line 2196 "AlphaCompiler/parser.c"
    break;

  case 69: /* elist: expression COMMA elist  */
#line 352 "AlphaCompiler/syntax_analyzer.y"
                                            {if(printSyntax) printf("line %d:elist->expression,elist\n",yylineno);
                                            (yyvsp[-2].expression)->next = (yyvsp[0].expression); (yyval.expression)=(yyvsp[-2].expression);
                                            }
#line 2204 "AlphaCompiler/parser.c"
    break;

  case 70: /* elist: %empty  */
#line 355 "AlphaCompiler/syntax_analyzer.y"
                  {(yyval.expression)=NULL;}
#line 2210 "AlphaCompiler/parser.c"
    break;

  case 71: /* objectdef: LEFT_SQR_BRK elist RIGHT_SQR_BRK  */
#line 359 "AlphaCompiler/syntax_analyzer.y"
                                                    {if(printSyntax) printf("line %d:objectdef->[elist]\n",yylineno);
                                                    (yyval.expression) = icode_objdef_elist((yyvsp[-1].expression));
                                                    }
#line 2218 "AlphaCompiler/parser.c"
    break;

  case 72: /* objectdef: LEFT_SQR_BRK indexed RIGHT_SQR_BRK  */
#line 362 "AlphaCompiler/syntax_analyzer.y"
                                                        {if(printSyntax) printf("line %d:objectdef->[indexed]\n",yylineno);
                                                        (yyval.expression) = icode_objdef_indexed((yyvsp[-1].expression));
                                                        }
#line 2226 "AlphaCompiler/parser.c"
    break;

  case 73: /* indexed: indexedelem  */
#line 367 "AlphaCompiler/syntax_analyzer.y"
                                                {if(printSyntax) printf("line %d:indexed->indexedelem\n",yylineno);
                                                (yyval.expression)=(yyvsp[0].expression); (yyval.expression)->next=NULL;}
#line 2233 "AlphaCompiler/parser.c"
    break;

  case 74: /* indexed: indexedelem COMMA indexed  */
#line 370 "AlphaCompiler/syntax_analyzer.y"
                                                {if(printSyntax) printf("line %d:indexed->indexedelem,indexed\n",yylineno);
                                                (yyvsp[-2].expression)->next = (yyvsp[0].expression); (yyval.expression)=(yyvsp[-2].expression);}
#line 2240 "AlphaCompiler/parser.c"
    break;

  case 75: /* indexedelem: LEFT_BRK expression COLON expression RIGHT_BRK  */
#line 374 "AlphaCompiler/syntax_analyzer.y"
                                                                    {if(printSyntax) printf("line %d:indexedelem->{expression,expression}\n",yylineno);
                                                                    icode_bool_stmt((yyvsp[-1].expression));
                                                                    (yyval.expression) = make_indexed((yyvsp[-3].expression), (yyvsp[-1].expression));}
#line 2248 "AlphaCompiler/parser.c"
    break;

  case 76: /* $@5: %empty  */
#line 379 "AlphaCompiler/syntax_analyzer.y"
                        {scope++;}
#line 2254 "AlphaCompiler/parser.c"
    break;

  case 77: /* block: LEFT_BRK $@5 statements RIGHT_BRK  */
#line 379 "AlphaCompiler/syntax_analyzer.y"
                                                        {hide_scope(oSymTable,scope);scope--;if(printSyntax) printf("line %d:block->{statements}\n",yylineno);(yyval.statement)=(yyvsp[-1].statement);}
#line 2260 "AlphaCompiler/parser.c"
    break;

  case 78: /* $@6: %empty  */
#line 381 "AlphaCompiler/syntax_analyzer.y"
                        {scope++;}
#line 2266 "AlphaCompiler/parser.c"
    break;

  case 79: /* block: LEFT_BRK $@6 RIGHT_BRK  */
#line 381 "AlphaCompiler/syntax_analyzer.y"
                                              {hide_scope(oSymTable,scope);scope--;if(printSyntax) printf("line %d:block->{statements}\n",yylineno);(yyval.statement)=NULL;}
#line 2272 "AlphaCompiler/parser.c"
    break;

  case 80: /* funcblockstart: %empty  */
#line 385 "AlphaCompiler/syntax_analyzer.y"
                    {loopstack_push(loopcounterstack,loopcounter); loopcounter=0;}
#line 2278 "AlphaCompiler/parser.c"
    break;

  case 81: /* funcblockend: %empty  */
#line 388 "AlphaCompiler/syntax_analyzer.y"
                    {loopcounter = loopstack_pop(loopcounterstack);}
#line 2284 "AlphaCompiler/parser.c"
    break;

  case 82: /* funcname: ID  */
#line 391 "AlphaCompiler/syntax_analyzer.y"
                  {(yyval.strval) = (yyvsp[0].strval);}
#line 2290 "AlphaCompiler/parser.c"
    break;

  case 83: /* funcname: %empty  */
#line 392 "AlphaCompiler/syntax_analyzer.y"
                    {char* funcname = malloc(sizeof(char)*100);
                    sprintf(funcname, "_f%d",nameless_funcs++);
                    (yyval.strval) = funcname;                                                                      
                    }
#line 2299 "AlphaCompiler/parser.c"
    break;

  case 84: /* funcprefix: FUNC funcname  */
#line 398 "AlphaCompiler/syntax_analyzer.y"
                             {  if(checkSymbol((yyvsp[0].strval), scope,USERFUNC,FALSE)==0){
                                    (yyval.symbolval) = SymTable_insert(oSymTable, (yyvsp[0].strval), NULL, USERFUNC, yylineno, scope, programvar, 0);
                                    expr* pref = malloc(sizeof(struct expr));
                                    pref->sym = (yyval.symbolval);
                                    pref->type = programfunc_e;
                                    emit(jump, NULL, NULL, NULL, 0, yylineno);
                                    (yyval.symbolval)->iaddress = nextquadlabel();
                                    emit(funcstart,pref,NULL,NULL,0,yylineno);
                                }
                                func_def(fstack, scope,currscopeoffset());
                                enterscopespace();resetformalargsoffset();
                            }
#line 2316 "AlphaCompiler/parser.c"
    break;

  case 85: /* funcargs: LEFT_PARENTHESIS idlist RIGHT_PARENTHESIS  */
#line 413 "AlphaCompiler/syntax_analyzer.y"
                                        {
                                            if(printSyntax) printf("line %d:funcdef->FUNC ID(idlist) \n",yylineno); 
                                            inFunction++;
                                            (yyval.mquad) = nextquadlabel()-2;
                                            enterscopespace();
                                            resetfunctionlocaloffset();}
#line 2327 "AlphaCompiler/parser.c"
    break;

  case 86: /* funcbody: block  */
#line 421 "AlphaCompiler/syntax_analyzer.y"
                      {(yyval.statement)=(yyvsp[0].statement);}
#line 2333 "AlphaCompiler/parser.c"
    break;

  case 87: /* F: %empty  */
#line 424 "AlphaCompiler/syntax_analyzer.y"
                {(yyval.unsignedval) = currscopeoffset();
                      exitscopespace();}
#line 2340 "AlphaCompiler/parser.c"
    break;

  case 88: /* funcdef: funcprefix funcargs funcblockstart funcbody F funcblockend  */
#line 428 "AlphaCompiler/syntax_analyzer.y"
                                                                             {inFunction--;
                                                struct func_def_info *finfo = exit_func_def(fstack); 
                                                exitscopespace();
                                                restorecurrscopeoffset(finfo->next_scope_offset);
                                                //free(finfo);
                                                (yyvsp[-5].symbolval)->totalScopeOffset = (yyvsp[-1].unsignedval);
                                                expr* pref = malloc(sizeof(struct expr));
                                                pref->sym = (yyvsp[-5].symbolval);
                                                pref->type = programfunc_e;
                                                if((yyvsp[-2].statement))patchlist((yyvsp[-2].statement)->retList, nextquadlabel());
                                                emit(funcend,pref,NULL,NULL,0,yylineno);
                                                patchlabel((yyvsp[-4].mquad),nextquadlabel());
                                                }
#line 2358 "AlphaCompiler/parser.c"
    break;

  case 89: /* const: INTEGER  */
#line 445 "AlphaCompiler/syntax_analyzer.y"
                            {
                            (yyval.expression) = newexpr_constarith((double)(yyvsp[0].intval)); 
                            if(printSyntax) printf("line %d:const->INTEGER\n",yylineno);
                            }
#line 2367 "AlphaCompiler/parser.c"
    break;

  case 90: /* const: REAL  */
#line 450 "AlphaCompiler/syntax_analyzer.y"
                            {
                            (yyval.expression) = newexpr_constarith((double)(yyvsp[0].fval)); 
                            if(printSyntax) printf("line %d:const->REAL\n",yylineno);}
#line 2375 "AlphaCompiler/parser.c"
    break;

  case 91: /* const: STRING  */
#line 454 "AlphaCompiler/syntax_analyzer.y"
                            {(yyval.expression) = newexpr_conststring((yyvsp[0].strval));
                            if(printSyntax) printf("line %d:const->STRING\n",yylineno);}
#line 2382 "AlphaCompiler/parser.c"
    break;

  case 92: /* const: NIL  */
#line 457 "AlphaCompiler/syntax_analyzer.y"
                            {(yyval.expression) = newexpr(nil_e);
                            if(printSyntax) printf("line %d:const->NIL\n",yylineno);
                            }
#line 2390 "AlphaCompiler/parser.c"
    break;

  case 93: /* const: TRUE_TKN  */
#line 461 "AlphaCompiler/syntax_analyzer.y"
                            {if(printSyntax) printf("line %d:const->TRUE_TKN\n",yylineno);
                            (yyval.expression) = newexpr_constbool(1);
                            }
#line 2398 "AlphaCompiler/parser.c"
    break;

  case 94: /* const: FALSE_TKN  */
#line 465 "AlphaCompiler/syntax_analyzer.y"
                            {if(printSyntax) printf("line %d:const->FALSE_TKN\n",yylineno);
                            (yyval.expression) = newexpr_constbool(0);}
#line 2405 "AlphaCompiler/parser.c"
    break;

  case 95: /* const: ENDL  */
#line 467 "AlphaCompiler/syntax_analyzer.y"
                            {if(printSyntax) printf("line %d:const->ENDL\n",yylineno);
                            (yyval.expression) = newexpr_conststring("\n");
                            }
#line 2413 "AlphaCompiler/parser.c"
    break;

  case 96: /* $@7: %empty  */
#line 472 "AlphaCompiler/syntax_analyzer.y"
                            {   if(checkSymbol((yyvsp[0].strval), scope+1,FORMAL,FALSE)==0){
                                    SymTable_insert(oSymTable, (yyvsp[0].strval), NULL, FORMAL, yylineno, scope+1, currscopespace(), currscopeoffset());
                                    inccurrscopeoffset();
                                }
                                
                                if(printSyntax) printf("line %d: idlist->ID\n",yylineno);}
#line 2424 "AlphaCompiler/parser.c"
    break;

  case 98: /* idlist: %empty  */
#line 480 "AlphaCompiler/syntax_analyzer.y"
                                {resetformalargsoffset();}
#line 2430 "AlphaCompiler/parser.c"
    break;

  case 99: /* $@8: %empty  */
#line 483 "AlphaCompiler/syntax_analyzer.y"
                                   {   if(checkSymbol((yyvsp[0].strval), scope+1,FORMAL,FALSE)==0){
                                            SymTable_insert(oSymTable, (yyvsp[0].strval), NULL, FORMAL, yylineno, scope+1, currscopespace(), currscopeoffset());
                                            inccurrscopeoffset();
                                        }
                                    }
#line 2440 "AlphaCompiler/parser.c"
    break;

  case 102: /* ifprefix: IF LEFT_PARENTHESIS expression RIGHT_PARENTHESIS  */
#line 494 "AlphaCompiler/syntax_analyzer.y"
                                                                    { if(printSyntax) printf("line %d:ifstmt->IF(\n",yylineno);
                                                                    (yyval.mquad) = icode_ifprefix((yyvsp[-1].expression));}
#line 2447 "AlphaCompiler/parser.c"
    break;

  case 103: /* elseprefix: ELSE  */
#line 498 "AlphaCompiler/syntax_analyzer.y"
                     {(yyval.mquad) = nextquadlabel();
                      emit(jump,NULL,NULL,NULL,0,yylineno);}
#line 2454 "AlphaCompiler/parser.c"
    break;

  case 104: /* ifstmt: ifprefix stmt  */
#line 503 "AlphaCompiler/syntax_analyzer.y"
                                         {patchlabel((yyvsp[-1].mquad),nextquadlabel());(yyval.statement)=(yyvsp[0].statement);}
#line 2460 "AlphaCompiler/parser.c"
    break;

  case 105: /* ifstmt: ifprefix stmt elseprefix stmt  */
#line 505 "AlphaCompiler/syntax_analyzer.y"
                                                                         {if(printSyntax) printf("line %d:ifstmt->ifstmt ELSE stmt\n",yylineno);
                                                                          patchlabel((yyvsp[-3].mquad),(yyvsp[-1].mquad)+1); patchlabel((yyvsp[-1].mquad),nextquadlabel());
                                                                          int brk1=0,brk2=0,cont1=0,cont2=0, ret1=0, ret2=0;
                                                                          (yyval.statement) = make_stmt();
                                                                          if((yyvsp[-2].statement)){brk1=(yyvsp[-2].statement)->breakList; cont1=(yyvsp[-2].statement)->contList; ret1=(yyvsp[-2].statement)->retList;}
                                                                          if((yyvsp[0].statement)){brk2=(yyvsp[0].statement)->breakList; cont2=(yyvsp[0].statement)->contList; ret2=(yyvsp[0].statement)->retList;}
                                                                          (yyval.statement)->breakList = mergelist(brk1,brk2);
                                                                          (yyval.statement)->contList = mergelist(cont1,cont2);
                                                                          (yyval.statement)->retList = mergelist(ret1,ret2);
                                                                          }
#line 2475 "AlphaCompiler/parser.c"
    break;

  case 106: /* whilestart: WHILE  */
#line 518 "AlphaCompiler/syntax_analyzer.y"
                      { (yyval.mquad) = nextquadlabel();}
#line 2481 "AlphaCompiler/parser.c"
    break;

  case 107: /* whilecond: LEFT_PARENTHESIS expression RIGHT_PARENTHESIS  */
#line 522 "AlphaCompiler/syntax_analyzer.y"
                                  {if(printSyntax)printf("line %d:whilestmt->while(expression)\n",yylineno); inLoop++;
                                   (yyval.mquad) = icode_whilecond((yyvsp[-1].expression));}
#line 2488 "AlphaCompiler/parser.c"
    break;

  case 108: /* whilestmt: whilestart whilecond loopstmt  */
#line 527 "AlphaCompiler/syntax_analyzer.y"
                                             {inLoop--; icode_whilestmt((yyvsp[-2].mquad),(yyvsp[-1].mquad),(yyvsp[0].statement)); if((yyvsp[0].statement))patchlist((yyvsp[0].statement)->contList, nextquadlabel()-1); if((yyvsp[0].statement))patchlist((yyvsp[0].statement)->breakList, nextquadlabel());}
#line 2494 "AlphaCompiler/parser.c"
    break;

  case 109: /* forprefix: FOR LEFT_PARENTHESIS elist SEMICOLON M expression SEMICOLON  */
#line 531 "AlphaCompiler/syntax_analyzer.y"
                          { (yyval.forpref) = icode_forprefix((yyvsp[-2].mquad),(yyvsp[-1].expression));}
#line 2500 "AlphaCompiler/parser.c"
    break;

  case 110: /* $@9: %empty  */
#line 534 "AlphaCompiler/syntax_analyzer.y"
                                                      {if(printSyntax)printf("line %d:forstmt-> for(elist; expression; elist)\n",yylineno);}
#line 2506 "AlphaCompiler/parser.c"
    break;

  case 111: /* $@10: %empty  */
#line 535 "AlphaCompiler/syntax_analyzer.y"
                {inLoop++;}
#line 2512 "AlphaCompiler/parser.c"
    break;

  case 112: /* forstmt: forprefix N elist RIGHT_PARENTHESIS N $@9 $@10 loopstmt N  */
#line 535 "AlphaCompiler/syntax_analyzer.y"
                                     {
                    icode_forstmt((yyvsp[-8].forpref),(yyvsp[-7].mquad),(yyvsp[-4].mquad),(yyvsp[-1].statement),(yyvsp[0].mquad));
                    if((yyvsp[-1].statement))patchlist((yyvsp[-1].statement)->contList, nextquadlabel()-1); if((yyvsp[-1].statement))patchlist((yyvsp[-1].statement)->breakList, nextquadlabel());
                    inLoop--;
                }
#line 2522 "AlphaCompiler/parser.c"
    break;

  case 113: /* returnstmt: RT expression SEMICOLON  */
#line 542 "AlphaCompiler/syntax_analyzer.y"
                                        {
                                        if(printSyntax) printf("line %d:returnstmt->RT expression\n",yylineno);
                                        if(inFunction<=0)yyerror("cannot 'return' when not inside a function");
                                        icode_bool_stmt((yyvsp[-1].expression));
                                        emit(ret, NULL, NULL, (yyvsp[-1].expression), 0, yylineno);
                                        if(printSyntax) printf("line %d: returnstmt -> ;\n",yylineno);
                                        (yyval.statement) = make_stmt();
                                        (yyval.statement)->retList = newList(nextquadlabel());
                                        emit(jump,NULL,NULL,NULL,0,yylineno);
                                        }
#line 2537 "AlphaCompiler/parser.c"
    break;

  case 114: /* returnstmt: RT SEMICOLON  */
#line 553 "AlphaCompiler/syntax_analyzer.y"
                                {if(inFunction<=0)yyerror("cannot 'return' when not inside a function");
                                if(printSyntax) printf("line %d:returnstmt-> RT ;\n",yylineno);
                                (yyval.statement) = make_stmt();
                                emit(ret, NULL, NULL, NULL, 0, yylineno);
                                (yyval.statement)->retList = newList(nextquadlabel());
                                emit(jump,NULL,NULL,NULL,0,yylineno);
                                }
#line 2549 "AlphaCompiler/parser.c"
    break;


#line 2553 "AlphaCompiler/parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 563 "AlphaCompiler/syntax_analyzer.y"


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
