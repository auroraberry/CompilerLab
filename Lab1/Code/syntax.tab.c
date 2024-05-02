/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

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


#line 91 "./syntax.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    FLOAT = 259,
    ID = 260,
    TYPE = 261,
    SEMI = 262,
    COMMA = 263,
    RELOP = 264,
    ASSIGNOP = 265,
    PLUS = 266,
    MINUS = 267,
    STAR = 268,
    DIV = 269,
    AND = 270,
    OR = 271,
    DOT = 272,
    NOT = 273,
    LP = 274,
    RP = 275,
    LB = 276,
    RB = 277,
    LC = 278,
    RC = 279,
    STRUCT = 280,
    RETURN = 281,
    IF = 282,
    ELSE = 283,
    WHILE = 284,
    LOWER_THAN_ELSE = 285
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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

#define YYUNDEFTOK  2
#define YYMAXUTOK   285


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "ID", "TYPE", "SEMI",
  "COMMA", "RELOP", "ASSIGNOP", "PLUS", "MINUS", "STAR", "DIV", "AND",
  "OR", "DOT", "NOT", "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT",
  "RETURN", "IF", "ELSE", "WHILE", "LOWER_THAN_ELSE", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285
};
# endif

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
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,    19,    34,     8,    12,    13,    20,
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

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
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

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
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

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
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


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

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

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
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
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
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
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
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
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 2:
#line 59 "./syntax.y"
                     {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*1);
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Program", 1, kids);
    root = yyval;
}
#line 1631 "./syntax.tab.c"
    break;

  case 3:
#line 68 "./syntax.y"
                               {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = yyvsp[-1];
    kids[1] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "ExtDefList", 2, kids);
}
#line 1644 "./syntax.tab.c"
    break;

  case 4:
#line 76 "./syntax.y"
  { yyval = NULL; }
#line 1650 "./syntax.tab.c"
    break;

  case 5:
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
#line 1664 "./syntax.tab.c"
    break;

  case 6:
#line 88 "./syntax.y"
                       {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Error in global definition.\n");
}
#line 1673 "./syntax.tab.c"
    break;

  case 7:
#line 92 "./syntax.y"
                 {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = yyvsp[-1];
    kids[1] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "ExtDef", 2, kids);
}
#line 1686 "./syntax.tab.c"
    break;

  case 8:
#line 100 "./syntax.y"
             {
    //$$ = NULL;
    handleError((yylsp[0]).first_line, "Error in global definition.\n");
}
#line 1695 "./syntax.tab.c"
    break;

  case 9:
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
#line 1709 "./syntax.tab.c"
    break;

  case 10:
#line 115 "./syntax.y"
                    {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "ExtDecList", 1, kids);
}
#line 1721 "./syntax.tab.c"
    break;

  case 11:
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
#line 1735 "./syntax.tab.c"
    break;

  case 12:
#line 137 "./syntax.y"
                 {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Specifier", 1, kids);
}
#line 1747 "./syntax.tab.c"
    break;

  case 13:
#line 144 "./syntax.y"
                  {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Specifier", 1, kids);
}
#line 1759 "./syntax.tab.c"
    break;

  case 14:
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
#line 1775 "./syntax.tab.c"
    break;

  case 15:
#line 164 "./syntax.y"
                            {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Error in Struct definition.\n");
}
#line 1784 "./syntax.tab.c"
    break;

  case 16:
#line 168 "./syntax.y"
                             {
    //$$ = NULL;
    handleError((yylsp[-4]).first_line, "Error in Struct definition.\n");
}
#line 1793 "./syntax.tab.c"
    break;

  case 17:
#line 172 "./syntax.y"
             {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = yyvsp[-1];
    kids[1] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "StructSpecifier", 2, kids);
}
#line 1806 "./syntax.tab.c"
    break;

  case 18:
#line 182 "./syntax.y"
            {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "OptTag", 1, kids);
}
#line 1818 "./syntax.tab.c"
    break;

  case 19:
#line 189 "./syntax.y"
  { yyval = NULL; }
#line 1824 "./syntax.tab.c"
    break;

  case 20:
#line 192 "./syntax.y"
         {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Tag", 1, kids);
}
#line 1836 "./syntax.tab.c"
    break;

  case 21:
#line 204 "./syntax.y"
            {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "VarDec", 1, kids);
}
#line 1848 "./syntax.tab.c"
    break;

  case 22:
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
#line 1863 "./syntax.tab.c"
    break;

  case 23:
#line 221 "./syntax.y"
                  {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Error in var declaration.\n");
}
#line 1872 "./syntax.tab.c"
    break;

  case 24:
#line 225 "./syntax.y"
                     {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Error in var declaration.\n");
}
#line 1881 "./syntax.tab.c"
    break;

  case 25:
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
#line 1896 "./syntax.tab.c"
    break;

  case 26:
#line 241 "./syntax.y"
                      {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Error in func declaration.\n");
}
#line 1905 "./syntax.tab.c"
    break;

  case 27:
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
#line 1919 "./syntax.tab.c"
    break;

  case 28:
#line 254 "./syntax.y"
                 {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Error in func declaration.\n");
}
#line 1928 "./syntax.tab.c"
    break;

  case 29:
#line 258 "./syntax.y"
              {
    //$$ = NULL;
    handleError((yylsp[-1]).first_line, "Error in func declaration.\n");
}
#line 1937 "./syntax.tab.c"
    break;

  case 30:
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
#line 1951 "./syntax.tab.c"
    break;

  case 31:
#line 273 "./syntax.y"
           {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "VarList", 1, kids);
}
#line 1963 "./syntax.tab.c"
    break;

  case 32:
#line 282 "./syntax.y"
                            {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = yyvsp[-1];
    kids[1] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "ParamDec", 2, kids);
}
#line 1976 "./syntax.tab.c"
    break;

  case 33:
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
#line 1991 "./syntax.tab.c"
    break;

  case 34:
#line 305 "./syntax.y"
                      {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Error in CompSt.\n");
}
#line 2000 "./syntax.tab.c"
    break;

  case 35:
#line 309 "./syntax.y"
                       {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Error in definition.\n");
}
#line 2009 "./syntax.tab.c"
    break;

  case 36:
#line 315 "./syntax.y"
                         {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = yyvsp[-1];
    kids[1] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "StmtList", 2, kids);
}
#line 2022 "./syntax.tab.c"
    break;

  case 37:
#line 323 "./syntax.y"
  { yyval = NULL; }
#line 2028 "./syntax.tab.c"
    break;

  case 38:
#line 326 "./syntax.y"
                {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = yyvsp[-1];
    kids[1] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Stmt", 2, kids);
}
#line 2041 "./syntax.tab.c"
    break;

  case 39:
#line 334 "./syntax.y"
                 {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Invalid statement.\n");
}
#line 2050 "./syntax.tab.c"
    break;

  case 40:
#line 338 "./syntax.y"
         {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Stmt", 1, kids);
}
#line 2062 "./syntax.tab.c"
    break;

  case 41:
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
#line 2076 "./syntax.tab.c"
    break;

  case 42:
#line 354 "./syntax.y"
                    {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Invalid statement.\n");
}
#line 2085 "./syntax.tab.c"
    break;

  case 43:
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
#line 2101 "./syntax.tab.c"
    break;

  case 44:
#line 369 "./syntax.y"
                                            {
    //$$ = NULL;
    handleError((yylsp[-3]).first_line, "Invalid statement.\n");
}
#line 2110 "./syntax.tab.c"
    break;

  case 45:
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
#line 2128 "./syntax.tab.c"
    break;

  case 46:
#line 386 "./syntax.y"
                                {
    //$$ = NULL;
    handleError((yylsp[-5]).first_line, "Invalid statement.\n");
}
#line 2137 "./syntax.tab.c"
    break;

  case 47:
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
#line 2153 "./syntax.tab.c"
    break;

  case 48:
#line 401 "./syntax.y"
                         {
    //$$ = NULL;
    handleError((yylsp[-3]).first_line, "Invalid statement.\n");
}
#line 2162 "./syntax.tab.c"
    break;

  case 49:
#line 411 "./syntax.y"
                      {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = yyvsp[-1];
    kids[1] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "DefList", 2, kids);
}
#line 2175 "./syntax.tab.c"
    break;

  case 50:
#line 419 "./syntax.y"
  { yyval = NULL; }
#line 2181 "./syntax.tab.c"
    break;

  case 51:
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
#line 2195 "./syntax.tab.c"
    break;

  case 52:
#line 431 "./syntax.y"
                       {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Error in definition.\n");
}
#line 2204 "./syntax.tab.c"
    break;

  case 53:
#line 435 "./syntax.y"
             {
    //$$ = NULL;
    handleError((yylsp[-1]).first_line, "Error in definition.\n");
}
#line 2213 "./syntax.tab.c"
    break;

  case 54:
#line 441 "./syntax.y"
              {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "DecList", 1, kids);
}
#line 2225 "./syntax.tab.c"
    break;

  case 55:
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
#line 2239 "./syntax.tab.c"
    break;

  case 56:
#line 459 "./syntax.y"
             {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Dec", 1, kids);
}
#line 2251 "./syntax.tab.c"
    break;

  case 57:
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
#line 2265 "./syntax.tab.c"
    break;

  case 58:
#line 475 "./syntax.y"
                     {
    handleError((yylsp[-1]).first_line, "Error in declaration.\n");
}
#line 2273 "./syntax.tab.c"
    break;

  case 59:
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
#line 2287 "./syntax.tab.c"
    break;

  case 60:
#line 493 "./syntax.y"
                     {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Error in exp.\n");
}
#line 2296 "./syntax.tab.c"
    break;

  case 61:
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
#line 2310 "./syntax.tab.c"
    break;

  case 62:
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
#line 2324 "./syntax.tab.c"
    break;

  case 63:
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
#line 2338 "./syntax.tab.c"
    break;

  case 64:
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
#line 2352 "./syntax.tab.c"
    break;

  case 65:
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
#line 2366 "./syntax.tab.c"
    break;

  case 66:
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
#line 2380 "./syntax.tab.c"
    break;

  case 67:
#line 551 "./syntax.y"
                     {
    //$$ = NULL;
    handleError((yylsp[-3]).first_line, "Error in exp.\n");
}
#line 2389 "./syntax.tab.c"
    break;

  case 68:
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
#line 2403 "./syntax.tab.c"
    break;

  case 69:
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
#line 2417 "./syntax.tab.c"
    break;

  case 70:
#line 573 "./syntax.y"
              {
    //$$ = NULL;
    handleError((yylsp[-2]).first_line, "Error in exp.\n");
}
#line 2426 "./syntax.tab.c"
    break;

  case 71:
#line 577 "./syntax.y"
            {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = yyvsp[-1];
    kids[1] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 2, kids);
}
#line 2439 "./syntax.tab.c"
    break;

  case 72:
#line 585 "./syntax.y"
          {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = yyvsp[-1];
    kids[1] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 2, kids);
}
#line 2452 "./syntax.tab.c"
    break;

  case 73:
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
#line 2467 "./syntax.tab.c"
    break;

  case 74:
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
#line 2481 "./syntax.tab.c"
    break;

  case 75:
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
#line 2496 "./syntax.tab.c"
    break;

  case 76:
#line 622 "./syntax.y"
                  {
    //$$ = NULL;
    handleError((yylsp[-3]).first_line, "Error in exp.\n");
}
#line 2505 "./syntax.tab.c"
    break;

  case 77:
#line 626 "./syntax.y"
                  {
    //$$ = NULL;
    handleError((yylsp[-3]).first_line, "Error in exp.\n");
}
#line 2514 "./syntax.tab.c"
    break;

  case 78:
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
#line 2528 "./syntax.tab.c"
    break;

  case 79:
#line 639 "./syntax.y"
     {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 1, kids);
}
#line 2540 "./syntax.tab.c"
    break;

  case 80:
#line 646 "./syntax.y"
      {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 1, kids);
}
#line 2552 "./syntax.tab.c"
    break;

  case 81:
#line 653 "./syntax.y"
        {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Exp", 1, kids);
}
#line 2564 "./syntax.tab.c"
    break;

  case 82:
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
#line 2578 "./syntax.tab.c"
    break;

  case 83:
#line 671 "./syntax.y"
      {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = yyvsp[0];
    yyval = createVariableNode((yyloc).first_line, val, "Args", 1, kids);
}
#line 2590 "./syntax.tab.c"
    break;


#line 2594 "./syntax.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 683 "./syntax.y"
