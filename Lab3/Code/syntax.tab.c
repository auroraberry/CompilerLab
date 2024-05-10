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
#line 1 "./syntax.y"

    #define YYSTYPE Node*
    #include <stdio.h>
    #include "SyntaxTree.h"
    #include "lex.yy.c"

    Node* root = NULL;
    bool syntax_error = false;
    bool needHandling(int lineno); 
    
    void handleError(int lineno, char* msg) {
        if(needHandling(lineno)){
            syntax_error = true;
            printf("Error type B at Line %d: Syntax Error. %s", yylineno, msg); 
        }
    }

    void yyerror(char* msg){}


#line 92 "./syntax.tab.c"

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

#include "syntax.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_ID = 5,                         /* ID  */
  YYSYMBOL_TYPE = 6,                       /* TYPE  */
  YYSYMBOL_SEMI = 7,                       /* SEMI  */
  YYSYMBOL_COMMA = 8,                      /* COMMA  */
  YYSYMBOL_RELOP = 9,                      /* RELOP  */
  YYSYMBOL_ASSIGNOP = 10,                  /* ASSIGNOP  */
  YYSYMBOL_PLUS = 11,                      /* PLUS  */
  YYSYMBOL_MINUS = 12,                     /* MINUS  */
  YYSYMBOL_STAR = 13,                      /* STAR  */
  YYSYMBOL_DIV = 14,                       /* DIV  */
  YYSYMBOL_AND = 15,                       /* AND  */
  YYSYMBOL_OR = 16,                        /* OR  */
  YYSYMBOL_DOT = 17,                       /* DOT  */
  YYSYMBOL_NOT = 18,                       /* NOT  */
  YYSYMBOL_LP = 19,                        /* LP  */
  YYSYMBOL_RP = 20,                        /* RP  */
  YYSYMBOL_LB = 21,                        /* LB  */
  YYSYMBOL_RB = 22,                        /* RB  */
  YYSYMBOL_LC = 23,                        /* LC  */
  YYSYMBOL_RC = 24,                        /* RC  */
  YYSYMBOL_STRUCT = 25,                    /* STRUCT  */
  YYSYMBOL_RETURN = 26,                    /* RETURN  */
  YYSYMBOL_IF = 27,                        /* IF  */
  YYSYMBOL_ELSE = 28,                      /* ELSE  */
  YYSYMBOL_WHILE = 29,                     /* WHILE  */
  YYSYMBOL_LOWER_THAN_ELSE = 30,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 31,                  /* $accept  */
  YYSYMBOL_Program = 32,                   /* Program  */
  YYSYMBOL_ExtDefList = 33,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 34,                    /* ExtDef  */
  YYSYMBOL_ExtDecList = 35,                /* ExtDecList  */
  YYSYMBOL_Specifier = 36,                 /* Specifier  */
  YYSYMBOL_StructSpecifier = 37,           /* StructSpecifier  */
  YYSYMBOL_OptTag = 38,                    /* OptTag  */
  YYSYMBOL_Tag = 39,                       /* Tag  */
  YYSYMBOL_VarDec = 40,                    /* VarDec  */
  YYSYMBOL_FunDec = 41,                    /* FunDec  */
  YYSYMBOL_VarList = 42,                   /* VarList  */
  YYSYMBOL_ParamDec = 43,                  /* ParamDec  */
  YYSYMBOL_CompSt = 44,                    /* CompSt  */
  YYSYMBOL_StmtList = 45,                  /* StmtList  */
  YYSYMBOL_Stmt = 46,                      /* Stmt  */
  YYSYMBOL_DefList = 47,                   /* DefList  */
  YYSYMBOL_Def = 48,                       /* Def  */
  YYSYMBOL_DecList = 49,                   /* DecList  */
  YYSYMBOL_Dec = 50,                       /* Dec  */
  YYSYMBOL_Exp = 51,                       /* Exp  */
  YYSYMBOL_Args = 52                       /* Args  */
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   472

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  169

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    59,    59,    68,    76,    79,    88,    92,   100,   104,
     115,   122,   137,   144,   153,   164,   168,   172,   182,   189,
     192,   204,   211,   221,   225,   231,   241,   245,   254,   258,
     264,   273,   282,   295,   305,   309,   315,   323,   326,   334,
     338,   345,   354,   358,   369,   373,   386,   390,   401,   411,
     419,   422,   431,   435,   441,   448,   459,   466,   475,   484,
     493,   497,   506,   515,   524,   533,   542,   551,   555,   564,
     573,   577,   585,   593,   603,   612,   622,   626,   630,   639,
     646,   653,   662,   671
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT", "ID",
  "TYPE", "SEMI", "COMMA", "RELOP", "ASSIGNOP", "PLUS", "MINUS", "STAR",
  "DIV", "AND", "OR", "DOT", "NOT", "LP", "RP", "LB", "RB", "LC", "RC",
  "STRUCT", "RETURN", "IF", "ELSE", "WHILE", "LOWER_THAN_ELSE", "$accept",
  "Program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier",
  "StructSpecifier", "OptTag", "Tag", "VarDec", "FunDec", "VarList",
  "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def", "DecList",
  "Dec", "Exp", "Args", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-76)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-51)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      16,    25,   -76,    45,     8,   -76,    16,   171,   -76,   -76,
      38,    52,    66,   -76,   -76,   -76,    44,    73,   -76,    88,
     120,    75,    24,    46,   -76,     1,   115,    96,   -76,    89,
      53,    54,   -76,   116,   124,   100,    81,    67,   106,   -76,
      89,   122,   141,   128,   157,   -76,   176,   130,   -76,   -76,
     160,   178,   108,   135,   -76,     2,    43,   196,   191,   -76,
     -76,   -76,   -76,   183,   -76,    18,   -76,   -76,   -76,   -76,
     -76,   185,   -76,   -76,   186,   251,   251,   261,   271,   190,
     195,   -76,   204,   162,   210,    93,   205,   -76,   251,   251,
     -76,   174,   -76,   251,   251,   239,   232,   131,   150,   379,
     112,   324,   281,   291,   -76,   -76,   203,   -76,   251,   251,
     251,   251,   301,   251,   251,   251,   230,   311,   -76,   -76,
     418,   418,   192,   -76,   418,   337,   -76,   352,   216,   -76,
     -76,   -76,   -76,   163,   392,   177,   405,   -76,   451,   418,
     232,   232,   229,   131,   131,   440,   429,   -76,   147,   365,
     -76,   251,   -76,   189,   189,   189,   189,   418,   -76,   -76,
     -76,   209,   233,   -76,   -76,   189,   189,   -76,   -76
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    12,     0,     0,     2,     0,     0,    13,     8,
       0,    20,     0,    17,     1,     3,     0,    21,     7,     0,
      10,     0,     0,     0,     6,     0,     0,     0,     5,     0,
       0,     0,     9,     0,     0,     0,     0,     0,     0,    29,
       0,     0,    31,     0,     0,    27,     0,     0,    21,    11,
       0,     0,     0,     0,    53,     0,    56,     0,    54,    16,
      49,    15,    14,    32,    26,     0,    23,    28,    25,    24,
      22,     0,    80,    81,    79,     0,     0,     0,     0,     0,
       0,    40,     0,     0,     0,     0,     0,    52,     0,     0,
      51,     0,    30,     0,     0,     0,    71,    72,     0,     0,
       0,     0,     0,     0,    35,    36,     0,    38,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,    33,
      58,    57,     0,    55,    60,     0,    74,    83,     0,    70,
      69,    42,    41,     0,     0,     0,     0,    39,    63,    59,
      64,    65,     0,    66,    68,    61,    62,    78,     0,     0,
      77,     0,    73,     0,     0,     0,     0,    67,    76,    75,
      82,    44,    43,    48,    47,     0,     0,    46,    45
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -76,   -76,   254,   -76,   238,     4,   -76,   -76,   -76,   -29,
     -76,   -21,   -76,   217,   -38,   -10,    65,   -76,   180,   -76,
     -75,   117
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     4,     5,     6,    19,    34,     8,    12,    13,    20,
      21,    41,    42,    81,    82,    83,    35,    36,    57,    58,
      84,   128
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      96,    97,    99,   101,     7,    56,    46,     2,    14,    87,
       7,    63,    88,   120,   121,    86,    -4,     1,   124,   125,
     127,    39,     2,    26,     2,    33,     3,   134,   136,    40,
       2,    40,     9,   138,   139,   140,   141,   143,   144,   145,
     146,     3,   149,     3,    92,   105,    10,    37,   -50,     3,
      11,    24,     2,    89,    50,    52,    51,   -50,   -50,   -50,
       2,    22,    56,    25,    30,    26,   -50,   157,   -19,    40,
     -50,     3,   -50,   -50,    54,   -18,   127,   -50,   -50,     3,
     -50,   -50,    33,   -50,   -50,   -50,   -50,     2,    38,    23,
      47,    61,    27,   -50,    48,    28,    53,    44,    31,   -50,
     -50,    60,     2,    93,   -50,   -50,     3,   -50,   -50,    71,
     -50,    72,    73,    74,    94,    54,    45,   118,    43,   131,
      75,     3,    93,    54,    59,    55,    76,    77,    29,    48,
      62,    31,   -37,    94,    78,    79,    85,    80,    72,    73,
      74,    30,    64,   161,   162,   163,   164,    75,   116,    65,
      66,    26,   117,    76,    77,   167,   168,    93,    31,   -37,
      93,    78,    79,    71,    80,    72,    73,    74,    94,   158,
     129,    94,    16,    93,    75,   122,    17,    67,    18,    48,
      76,    77,    69,   153,    94,    31,   -37,    93,    78,    79,
      71,    80,    72,    73,    74,    93,    68,   155,    94,    91,
      70,    75,    88,    90,    30,    95,    94,    76,    77,   102,
     137,   106,    31,    26,   103,    78,    79,   107,    80,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   104,   119,
      71,   117,    72,    73,    74,   147,   152,   165,    32,    93,
      71,    75,    72,    73,    74,   112,   113,    76,    77,   116,
      94,    75,    71,   117,    72,    73,    74,    76,    77,   126,
      15,   166,    98,    75,    72,    73,    74,    49,   160,    76,
      77,   123,   100,    75,    72,    73,    74,     0,     0,    76,
      77,     0,   133,    75,    72,    73,    74,     0,     0,    76,
      77,     0,   135,    75,    72,    73,    74,     0,     0,    76,
      77,     0,   142,    75,    72,    73,    74,     0,     0,    76,
      77,     0,   148,    75,    72,    73,    74,     0,     0,    76,
      77,     0,     0,    75,     0,     0,     0,     0,     0,    76,
      77,   132,     0,   108,   109,   110,   111,   112,   113,   114,
     115,   116,     0,     0,     0,   117,   108,   109,   110,   111,
     112,   113,   114,   115,   116,     0,     0,     0,   117,   150,
     151,   108,   109,   110,   111,   112,   113,   114,   115,   116,
       0,     0,     0,   117,   108,   109,   110,   111,   112,   113,
     114,   115,   116,     0,     0,     0,   117,   159,   108,   109,
     110,   111,   112,   113,   114,   115,   116,     0,     0,   130,
     117,   108,   109,   110,   111,   112,   113,   114,   115,   116,
       0,     0,   154,   117,   108,   109,   110,   111,   112,   113,
     114,   115,   116,     0,     0,   156,   117,   108,   109,   110,
     111,   112,   113,   114,   115,   116,     0,     0,   108,   117,
     110,   111,   112,   113,   114,     0,   116,     0,     0,   108,
     117,   110,   111,   112,   113,     0,     0,   116,     0,     0,
       0,   117,   110,   111,   112,   113,     0,     0,   116,     0,
       0,     0,   117
};

static const yytype_int16 yycheck[] =
{
      75,    76,    77,    78,     0,    34,    27,     6,     0,     7,
       6,    40,    10,    88,    89,    53,     0,     1,    93,    94,
      95,    20,     6,    21,     6,     1,    25,   102,   103,    25,
       6,    27,     7,   108,   109,   110,   111,   112,   113,   114,
     115,    25,   117,    25,    65,    83,     1,     1,    24,    25,
       5,     7,     6,    10,     1,     1,     3,     3,     4,     5,
       6,    23,    91,    19,    21,    21,    12,   142,    23,    65,
      24,    25,    18,    19,     7,    23,   151,    23,    24,    25,
      26,    27,     1,    29,     3,     4,     5,     6,    23,    23,
       1,    24,    19,    12,     5,     7,    31,     1,    23,    18,
      19,    36,     6,    10,    23,    24,    25,    26,    27,     1,
      29,     3,     4,     5,    21,     7,    20,    24,     3,     7,
      12,    25,    10,     7,    24,     1,    18,    19,     8,     5,
      24,    23,    24,    21,    26,    27,     1,    29,     3,     4,
       5,    21,    20,   153,   154,   155,   156,    12,    17,     8,
      22,    21,    21,    18,    19,   165,   166,    10,    23,    24,
      10,    26,    27,     1,    29,     3,     4,     5,    21,    22,
      20,    21,     1,    10,    12,     1,     5,    20,     7,     5,
      18,    19,    22,    20,    21,    23,    24,    10,    26,    27,
       1,    29,     3,     4,     5,    10,    20,    20,    21,     8,
      22,    12,    10,     7,    21,    19,    21,    18,    19,    19,
       7,     1,    23,    21,    19,    26,    27,     7,    29,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    24,    24,
       1,    21,     3,     4,     5,     5,    20,    28,    21,    10,
       1,    12,     3,     4,     5,    13,    14,    18,    19,    17,
      21,    12,     1,    21,     3,     4,     5,    18,    19,    20,
       6,    28,     1,    12,     3,     4,     5,    29,   151,    18,
      19,    91,     1,    12,     3,     4,     5,    -1,    -1,    18,
      19,    -1,     1,    12,     3,     4,     5,    -1,    -1,    18,
      19,    -1,     1,    12,     3,     4,     5,    -1,    -1,    18,
      19,    -1,     1,    12,     3,     4,     5,    -1,    -1,    18,
      19,    -1,     1,    12,     3,     4,     5,    -1,    -1,    18,
      19,    -1,    -1,    12,    -1,    -1,    -1,    -1,    -1,    18,
      19,     7,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    -1,    -1,    -1,    21,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    -1,    -1,    21,    22,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    -1,    -1,    21,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    -1,    21,    22,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    -1,    20,
      21,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    -1,    20,    21,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    20,    21,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,     9,    21,
      11,    12,    13,    14,    15,    -1,    17,    -1,    -1,     9,
      21,    11,    12,    13,    14,    -1,    -1,    17,    -1,    -1,
      -1,    21,    11,    12,    13,    14,    -1,    -1,    17,    -1,
      -1,    -1,    21
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     6,    25,    32,    33,    34,    36,    37,     7,
       1,     5,    38,    39,     0,    33,     1,     5,     7,    35,
      40,    41,    23,    23,     7,    19,    21,    19,     7,     8,
      21,    23,    44,     1,    36,    47,    48,     1,    47,    20,
      36,    42,    43,     3,     1,    20,    42,     1,     5,    35,
       1,     3,     1,    47,     7,     1,    40,    49,    50,    24,
      47,    24,    24,    40,    20,     8,    22,    20,    20,    22,
      22,     1,     3,     4,     5,    12,    18,    19,    26,    27,
      29,    44,    45,    46,    51,     1,    45,     7,    10,    10,
       7,     8,    42,    10,    21,    19,    51,    51,     1,    51,
       1,    51,    19,    19,    24,    45,     1,     7,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    21,    24,    24,
      51,    51,     1,    49,    51,    51,    20,    51,    52,    20,
      20,     7,     7,     1,    51,     1,    51,     7,    51,    51,
      51,    51,     1,    51,    51,    51,    51,     5,     1,    51,
      22,     8,    20,    20,    20,    20,    20,    51,    22,    22,
      52,    46,    46,    46,    46,    28,    28,    46,    46
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    34,    34,    34,
      35,    35,    36,    36,    37,    37,    37,    37,    38,    38,
      39,    40,    40,    40,    40,    41,    41,    41,    41,    41,
      42,    42,    43,    44,    44,    44,    45,    45,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    47,
      47,    48,    48,    48,    49,    49,    50,    50,    50,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    52,    52
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     3,     2,     2,     3,
       1,     3,     1,     1,     5,     5,     5,     2,     1,     0,
       1,     1,     4,     4,     4,     4,     4,     3,     4,     3,
       3,     1,     2,     4,     4,     4,     2,     0,     2,     3,
       1,     3,     3,     5,     5,     7,     7,     5,     5,     2,
       0,     3,     3,     2,     1,     3,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     3,     3,
       3,     2,     2,     4,     3,     4,     4,     4,     3,     1,
       1,     1,     3,     1
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

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: ExtDefList  */
#line 59 "./syntax.y"
                     {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*1);
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Program", 1, kids);
    root = yyval;
}
#line 1419 "./syntax.tab.c"
    break;

  case 3: /* ExtDefList: ExtDef ExtDefList  */
#line 68 "./syntax.y"
                               {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = yyvsp[-1];
    kids[1] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "ExtDefList", 2, kids);
}
#line 1432 "./syntax.tab.c"
    break;

  case 4: /* ExtDefList: %empty  */
#line 76 "./syntax.y"
  { yyval = NULL; }
#line 1438 "./syntax.tab.c"
    break;

  case 5: /* ExtDef: Specifier ExtDecList SEMI  */
#line 79 "./syntax.y"
                                   {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = yyvsp[-2];
    kids[1] = yyvsp[-1];
    kids[2] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "ExtDef", 3, kids);
}
#line 1452 "./syntax.tab.c"
    break;

  case 6: /* ExtDef: Specifier error SEMI  */
#line 88 "./syntax.y"
                       {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Error in global definition.\n");
}
#line 1461 "./syntax.tab.c"
    break;

  case 7: /* ExtDef: Specifier SEMI  */
#line 92 "./syntax.y"
                 {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = yyvsp[-1];
    kids[1] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "ExtDef", 2, kids);
}
#line 1474 "./syntax.tab.c"
    break;

  case 8: /* ExtDef: error SEMI  */
#line 100 "./syntax.y"
             {
    //$$ = NULL;
    handleError((yylsp[0]).first_line, "Error in global definition.\n");
}
#line 1483 "./syntax.tab.c"
    break;

  case 9: /* ExtDef: Specifier FunDec CompSt  */
#line 104 "./syntax.y"
                          {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = yyvsp[-2];
    kids[1] = yyvsp[-1];
    kids[2] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "ExtDef", 3, kids);
}
#line 1497 "./syntax.tab.c"
    break;

  case 10: /* ExtDecList: VarDec  */
#line 115 "./syntax.y"
                    {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "ExtDecList", 1, kids);
}
#line 1509 "./syntax.tab.c"
    break;

  case 11: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 122 "./syntax.y"
                          {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = yyvsp[-2];
    kids[1] = yyvsp[-1];
    kids[2] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "ExtDecList", 3, kids);
}
#line 1523 "./syntax.tab.c"
    break;

  case 12: /* Specifier: TYPE  */
#line 137 "./syntax.y"
                 {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Specifier", 1, kids);
}
#line 1535 "./syntax.tab.c"
    break;

  case 13: /* Specifier: StructSpecifier  */
#line 144 "./syntax.y"
                  {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Specifier", 1, kids);
}
#line 1547 "./syntax.tab.c"
    break;

  case 14: /* StructSpecifier: STRUCT OptTag LC DefList RC  */
#line 153 "./syntax.y"
                                              {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*5);
    kids[0] = yyvsp[-4];
    kids[1] = yyvsp[-3];
    kids[2] = yyvsp[-2];
    kids[3] = yyvsp[-1];
    kids[4] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "StructSpecifier", 5, kids);
}
#line 1563 "./syntax.tab.c"
    break;

  case 15: /* StructSpecifier: STRUCT OptTag LC error RC  */
#line 164 "./syntax.y"
                            {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Error in Struct definition.\n");
}
#line 1572 "./syntax.tab.c"
    break;

  case 16: /* StructSpecifier: STRUCT error LC DefList RC  */
#line 168 "./syntax.y"
                             {
    //$$ = NULL;
    handleError((yylsp[-4]).first_line, "Error in Struct definition.\n");
}
#line 1581 "./syntax.tab.c"
    break;

  case 17: /* StructSpecifier: STRUCT Tag  */
#line 172 "./syntax.y"
             {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = yyvsp[-1];
    kids[1] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "StructSpecifier", 2, kids);
}
#line 1594 "./syntax.tab.c"
    break;

  case 18: /* OptTag: ID  */
#line 182 "./syntax.y"
            {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "OptTag", 1, kids);
}
#line 1606 "./syntax.tab.c"
    break;

  case 19: /* OptTag: %empty  */
#line 189 "./syntax.y"
  { yyval = NULL; }
#line 1612 "./syntax.tab.c"
    break;

  case 20: /* Tag: ID  */
#line 192 "./syntax.y"
         {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Tag", 1, kids);
}
#line 1624 "./syntax.tab.c"
    break;

  case 21: /* VarDec: ID  */
#line 204 "./syntax.y"
            {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "VarDec", 1, kids);
}
#line 1636 "./syntax.tab.c"
    break;

  case 22: /* VarDec: VarDec LB INT RB  */
#line 211 "./syntax.y"
                   {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*4);
    kids[0] = yyvsp[-3];
    kids[1] = yyvsp[-2];
    kids[2] = yyvsp[-1];
    kids[3] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "VarDec", 4, kids);
}
#line 1651 "./syntax.tab.c"
    break;

  case 23: /* VarDec: error LB INT RB  */
#line 221 "./syntax.y"
                  {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Error in var declaration.\n");
}
#line 1660 "./syntax.tab.c"
    break;

  case 24: /* VarDec: VarDec LB error RB  */
#line 225 "./syntax.y"
                     {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Error in var declaration.\n");
}
#line 1669 "./syntax.tab.c"
    break;

  case 25: /* FunDec: ID LP VarList RP  */
#line 231 "./syntax.y"
                          {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*4);
    kids[0] = yyvsp[-3];
    kids[1] = yyvsp[-2];
    kids[2] = yyvsp[-1];
    kids[3] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "FunDec", 4, kids);
}
#line 1684 "./syntax.tab.c"
    break;

  case 26: /* FunDec: error LP VarList RP  */
#line 241 "./syntax.y"
                      {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Error in func declaration.\n");
}
#line 1693 "./syntax.tab.c"
    break;

  case 27: /* FunDec: ID LP RP  */
#line 245 "./syntax.y"
           {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = yyvsp[-2];
    kids[1] = yyvsp[-1];
    kids[2] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "FunDec", 3, kids);
}
#line 1707 "./syntax.tab.c"
    break;

  case 28: /* FunDec: ID LP error RP  */
#line 254 "./syntax.y"
                 {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Error in func declaration.\n");
}
#line 1716 "./syntax.tab.c"
    break;

  case 29: /* FunDec: error LP RP  */
#line 258 "./syntax.y"
              {
    //$$ = NULL;
    handleError((yylsp[-1]).first_line, "Error in func declaration.\n");
}
#line 1725 "./syntax.tab.c"
    break;

  case 30: /* VarList: ParamDec COMMA VarList  */
#line 264 "./syntax.y"
                                 {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = yyvsp[-2];
    kids[1] = yyvsp[-1];
    kids[2] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "VarList", 3, kids);
}
#line 1739 "./syntax.tab.c"
    break;

  case 31: /* VarList: ParamDec  */
#line 273 "./syntax.y"
           {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "VarList", 1, kids);
}
#line 1751 "./syntax.tab.c"
    break;

  case 32: /* ParamDec: Specifier VarDec  */
#line 282 "./syntax.y"
                            {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = yyvsp[-1];
    kids[1] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "ParamDec", 2, kids);
}
#line 1764 "./syntax.tab.c"
    break;

  case 33: /* CompSt: LC DefList StmtList RC  */
#line 295 "./syntax.y"
                                {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*4);
    kids[0] = yyvsp[-3];
    kids[1] = yyvsp[-2];
    kids[2] = yyvsp[-1];
    kids[3] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "CompSt", 4, kids);
}
#line 1779 "./syntax.tab.c"
    break;

  case 34: /* CompSt: LC DefList error RC  */
#line 305 "./syntax.y"
                      {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Error in CompSt.\n");
}
#line 1788 "./syntax.tab.c"
    break;

  case 35: /* CompSt: LC error StmtList RC  */
#line 309 "./syntax.y"
                       {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Error in definition.\n");
}
#line 1797 "./syntax.tab.c"
    break;

  case 36: /* StmtList: Stmt StmtList  */
#line 315 "./syntax.y"
                         {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = yyvsp[-1];
    kids[1] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "StmtList", 2, kids);
}
#line 1810 "./syntax.tab.c"
    break;

  case 37: /* StmtList: %empty  */
#line 323 "./syntax.y"
  { yyval = NULL; }
#line 1816 "./syntax.tab.c"
    break;

  case 38: /* Stmt: Exp SEMI  */
#line 326 "./syntax.y"
                {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = yyvsp[-1];
    kids[1] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Stmt", 2, kids);
}
#line 1829 "./syntax.tab.c"
    break;

  case 39: /* Stmt: Exp error SEMI  */
#line 334 "./syntax.y"
                 {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Invalid statement.\n");
}
#line 1838 "./syntax.tab.c"
    break;

  case 40: /* Stmt: CompSt  */
#line 338 "./syntax.y"
         {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Stmt", 1, kids);
}
#line 1850 "./syntax.tab.c"
    break;

  case 41: /* Stmt: RETURN Exp SEMI  */
#line 345 "./syntax.y"
                  {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = yyvsp[-2];
    kids[1] = yyvsp[-1];
    kids[2] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Stmt", 3, kids);
}
#line 1864 "./syntax.tab.c"
    break;

  case 42: /* Stmt: RETURN error SEMI  */
#line 354 "./syntax.y"
                    {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Invalid statement.\n");
}
#line 1873 "./syntax.tab.c"
    break;

  case 43: /* Stmt: IF LP Exp RP Stmt  */
#line 358 "./syntax.y"
                                          {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*5);
    kids[0] = yyvsp[-4];
    kids[1] = yyvsp[-3];
    kids[2] = yyvsp[-2];
    kids[3] = yyvsp[-1];
    kids[4] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Stmt", 5, kids);
}
#line 1889 "./syntax.tab.c"
    break;

  case 44: /* Stmt: IF LP error RP Stmt  */
#line 369 "./syntax.y"
                                            {
    //$$ = NULL;
    handleError((yylsp[-3]).first_line, "Invalid statement.\n");
}
#line 1898 "./syntax.tab.c"
    break;

  case 45: /* Stmt: IF LP Exp RP Stmt ELSE Stmt  */
#line 373 "./syntax.y"
                              {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*7);
    kids[0] = yyvsp[-6];
    kids[1] = yyvsp[-5];
    kids[2] = yyvsp[-4];
    kids[3] = yyvsp[-3];
    kids[4] = yyvsp[-2];
    kids[5] = yyvsp[-1];
    kids[6] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Stmt", 7, kids);
}
#line 1916 "./syntax.tab.c"
    break;

  case 46: /* Stmt: IF LP error RP Stmt ELSE Stmt  */
#line 386 "./syntax.y"
                                {
    //$$ = NULL;
    handleError((yylsp[-5]).first_line, "Invalid statement.\n");
}
#line 1925 "./syntax.tab.c"
    break;

  case 47: /* Stmt: WHILE LP Exp RP Stmt  */
#line 390 "./syntax.y"
                       {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*5);
    kids[0] = yyvsp[-4];
    kids[1] = yyvsp[-3];
    kids[2] = yyvsp[-2];
    kids[3] = yyvsp[-1];
    kids[4] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Stmt", 5, kids);
}
#line 1941 "./syntax.tab.c"
    break;

  case 48: /* Stmt: WHILE LP error RP Stmt  */
#line 401 "./syntax.y"
                         {
    //$$ = NULL;
    handleError((yylsp[-3]).first_line, "Invalid statement.\n");
}
#line 1950 "./syntax.tab.c"
    break;

  case 49: /* DefList: Def DefList  */
#line 411 "./syntax.y"
                      {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = yyvsp[-1];
    kids[1] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "DefList", 2, kids);
}
#line 1963 "./syntax.tab.c"
    break;

  case 50: /* DefList: %empty  */
#line 419 "./syntax.y"
  { yyval = NULL; }
#line 1969 "./syntax.tab.c"
    break;

  case 51: /* Def: Specifier DecList SEMI  */
#line 422 "./syntax.y"
                             {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = yyvsp[-2];
    kids[1] = yyvsp[-1];
    kids[2] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Def", 3, kids);
}
#line 1983 "./syntax.tab.c"
    break;

  case 52: /* Def: Specifier error SEMI  */
#line 431 "./syntax.y"
                       {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Error in definition.\n");
}
#line 1992 "./syntax.tab.c"
    break;

  case 53: /* Def: error SEMI  */
#line 435 "./syntax.y"
             {
    //$$ = NULL;
    handleError((yylsp[-1]).first_line, "Error in definition.\n");
}
#line 2001 "./syntax.tab.c"
    break;

  case 54: /* DecList: Dec  */
#line 441 "./syntax.y"
              {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "DecList", 1, kids);
}
#line 2013 "./syntax.tab.c"
    break;

  case 55: /* DecList: Dec COMMA DecList  */
#line 448 "./syntax.y"
                    {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = yyvsp[-2];
    kids[1] = yyvsp[-1];
    kids[2] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "DecList", 3, kids);
}
#line 2027 "./syntax.tab.c"
    break;

  case 56: /* Dec: VarDec  */
#line 459 "./syntax.y"
             {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Dec", 1, kids);
}
#line 2039 "./syntax.tab.c"
    break;

  case 57: /* Dec: VarDec ASSIGNOP Exp  */
#line 466 "./syntax.y"
                      {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = yyvsp[-2];
    kids[1] = yyvsp[-1];
    kids[2] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Dec", 3, kids);
}
#line 2053 "./syntax.tab.c"
    break;

  case 58: /* Dec: error ASSIGNOP Exp  */
#line 475 "./syntax.y"
                     {
    handleError((yylsp[-1]).first_line, "Error in declaration.\n");
}
#line 2061 "./syntax.tab.c"
    break;

  case 59: /* Exp: Exp ASSIGNOP Exp  */
#line 484 "./syntax.y"
                       {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = yyvsp[-2];
    kids[1] = yyvsp[-1];
    kids[2] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 3, kids);
}
#line 2075 "./syntax.tab.c"
    break;

  case 60: /* Exp: error ASSIGNOP Exp  */
#line 493 "./syntax.y"
                     {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Error in exp.\n");
}
#line 2084 "./syntax.tab.c"
    break;

  case 61: /* Exp: Exp AND Exp  */
#line 497 "./syntax.y"
              {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = yyvsp[-2];
    kids[1] = yyvsp[-1];
    kids[2] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 3, kids);
}
#line 2098 "./syntax.tab.c"
    break;

  case 62: /* Exp: Exp OR Exp  */
#line 506 "./syntax.y"
             {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = yyvsp[-2];
    kids[1] = yyvsp[-1];
    kids[2] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 3, kids);
}
#line 2112 "./syntax.tab.c"
    break;

  case 63: /* Exp: Exp RELOP Exp  */
#line 515 "./syntax.y"
                {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = yyvsp[-2];
    kids[1] = yyvsp[-1];
    kids[2] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 3, kids);
}
#line 2126 "./syntax.tab.c"
    break;

  case 64: /* Exp: Exp PLUS Exp  */
#line 524 "./syntax.y"
               {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = yyvsp[-2];
    kids[1] = yyvsp[-1];
    kids[2] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 3, kids);
}
#line 2140 "./syntax.tab.c"
    break;

  case 65: /* Exp: Exp MINUS Exp  */
#line 533 "./syntax.y"
                {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = yyvsp[-2];
    kids[1] = yyvsp[-1];
    kids[2] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 3, kids);
}
#line 2154 "./syntax.tab.c"
    break;

  case 66: /* Exp: Exp STAR Exp  */
#line 542 "./syntax.y"
               {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = yyvsp[-2];
    kids[1] = yyvsp[-1];
    kids[2] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 3, kids);
}
#line 2168 "./syntax.tab.c"
    break;

  case 67: /* Exp: Exp STAR error Exp  */
#line 551 "./syntax.y"
                     {
    //$$ = NULL;
    handleError((yylsp[-3]).first_line, "Error in exp.\n");
}
#line 2177 "./syntax.tab.c"
    break;

  case 68: /* Exp: Exp DIV Exp  */
#line 555 "./syntax.y"
              {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = yyvsp[-2];
    kids[1] = yyvsp[-1];
    kids[2] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 3, kids);
}
#line 2191 "./syntax.tab.c"
    break;

  case 69: /* Exp: LP Exp RP  */
#line 564 "./syntax.y"
            {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = yyvsp[-2];
    kids[1] = yyvsp[-1];
    kids[2] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 3, kids);
}
#line 2205 "./syntax.tab.c"
    break;

  case 70: /* Exp: LP error RP  */
#line 573 "./syntax.y"
              {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Error in exp.\n");
}
#line 2214 "./syntax.tab.c"
    break;

  case 71: /* Exp: MINUS Exp  */
#line 577 "./syntax.y"
            {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = yyvsp[-1];
    kids[1] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 2, kids);
}
#line 2227 "./syntax.tab.c"
    break;

  case 72: /* Exp: NOT Exp  */
#line 585 "./syntax.y"
          {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = yyvsp[-1];
    kids[1] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 2, kids);
}
#line 2240 "./syntax.tab.c"
    break;

  case 73: /* Exp: ID LP Args RP  */
#line 593 "./syntax.y"
                {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*4);
    kids[0] = yyvsp[-3];
    kids[1] = yyvsp[-2];
    kids[2] = yyvsp[-1];
    kids[3] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 4, kids);
}
#line 2255 "./syntax.tab.c"
    break;

  case 74: /* Exp: ID LP RP  */
#line 603 "./syntax.y"
           {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = yyvsp[-2];
    kids[1] = yyvsp[-1];
    kids[2] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 3, kids);
}
#line 2269 "./syntax.tab.c"
    break;

  case 75: /* Exp: Exp LB Exp RB  */
#line 612 "./syntax.y"
                {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*4);
    kids[0] = yyvsp[-3];
    kids[1] = yyvsp[-2];
    kids[2] = yyvsp[-1];
    kids[3] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 4, kids);
}
#line 2284 "./syntax.tab.c"
    break;

  case 76: /* Exp: Exp LB error RB  */
#line 622 "./syntax.y"
                  {
    //$$ = NULL;
    handleError((yylsp[-3]).first_line, "Error in exp.\n");
}
#line 2293 "./syntax.tab.c"
    break;

  case 77: /* Exp: error LB Exp RB  */
#line 626 "./syntax.y"
                  {
    //$$ = NULL;
    handleError((yylsp[-3]).first_line, "Error in exp.\n");
}
#line 2302 "./syntax.tab.c"
    break;

  case 78: /* Exp: Exp DOT ID  */
#line 630 "./syntax.y"
             {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = yyvsp[-2];
    kids[1] = yyvsp[-1];
    kids[2] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 3, kids);
}
#line 2316 "./syntax.tab.c"
    break;

  case 79: /* Exp: ID  */
#line 639 "./syntax.y"
     {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 1, kids);
}
#line 2328 "./syntax.tab.c"
    break;

  case 80: /* Exp: INT  */
#line 646 "./syntax.y"
      {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 1, kids);
}
#line 2340 "./syntax.tab.c"
    break;

  case 81: /* Exp: FLOAT  */
#line 653 "./syntax.y"
        {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 1, kids);
}
#line 2352 "./syntax.tab.c"
    break;

  case 82: /* Args: Exp COMMA Args  */
#line 662 "./syntax.y"
                      {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = yyvsp[-2];
    kids[1] = yyvsp[-1];
    kids[2] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Args", 3, kids);
}
#line 2366 "./syntax.tab.c"
    break;

  case 83: /* Args: Exp  */
#line 671 "./syntax.y"
      {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Args", 1, kids);
}
#line 2378 "./syntax.tab.c"
    break;


#line 2382 "./syntax.tab.c"

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
  *++yylsp = yyloc;

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
      yyerror (YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 683 "./syntax.y"
