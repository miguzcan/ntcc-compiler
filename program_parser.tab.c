/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "program_parser.y"


 /********************************
  * parser header			 *
  ********************************/
  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>
  #include <string.h>
  #include <strings.h>

  #include <ctype.h>
  #include "symbol_table.h"
  #include "stack_machine.h"
  #include "code_generator.h"
  #define YYERROR_VERBOSE
  #define YYDEBUG 1/* For Debugging*/
  #define OZFILE "output.oz"  
  extern int yylex(void);
  extern char *yytext;
  extern int yylineno;
  extern FILE *yyin;  
  char *ozOutputFileTmp = "";
  int errors;
  int timeUnits;
  char *process_name;
  int local_var = 0;

  /*Cambiar esto*/
  int allvarsdom = 0; 
  int csNum = 0;
  int eqvar = 0;
/////////// 
/* Creo que aqui lo mejor es tener una struct que represente los limites de los
dominios, con el objetivo de poder definir diferentes typos de datos para los dominios.
*/
  int linf=0;
  int lsup=0;
  double linfR = 0.0;
  double lsupR = 0.0; 
///////////

  int system_call = 0;

 /********************************
  * end header			 *
  ********************************/


  /********************************
   * begin symbol table functions *
   ********************************/

  
  saveSymbol(char *symbolName, char *symbolCs)
    {    
      symrec *s;
      s = getSymbol(symbolName);     
      if(s == 0)
        {
          s = newSymbol(symbolName, symbolCs);
        }     
      else
        {
	  printf ("%s is already defined\n", symbolName);
          errors++;
        }      
    }

   saveSymbolDomain(char *symbolName, char *symbolCs)
    {    
      symrec *s;
      s = getSymbol(symbolName);     
      if(s == 0)
        {
          struct domain domain;
	  if(lsup!=0)
	  {
          	domain.domainInfI = linf;
          	domain.domainSupI = lsup;
          	s = newSymbolDomain(symbolName, symbolCs, domain);
	  	linf = 0;
          	lsup = 0;	
	  }
	  else
	  {
		domain.domainInfR = linfR;
		domain.domainSupR = lsupR;
		s = newSymbolDomain(symbolName, symbolCs, domain);
	  }
        }     
      else
        {
	  printf ("%s is already defined\n", symbolName);	
          errors++;
        }      
    } 

 
   saveNewVarDefinition(char *symbolName, char *symbolCs, char *proc_name)
     {
	vardefinition *s;
	s = getDefSymbol(symbolName);
	if(s == 0)
	{		
		s = newVarDefinition(symbolName, symbolCs, proc_name);
	}
	else
	{
		if(strcmp(s->proc_name,proc_name)==0)
		{
			printf("%s is already defined\n", symbolName);
			errors++;
		}else
		{
			s = newVarDefinition(symbolName, symbolCs, proc_name);
		}
	}
     }

   saveSymbolLocal(char *symbolName, char *symbolCs, char *proc_name)
     {    
       localVariables *s;
       s = getLocalSymbol(symbolName);     
       if(s == 0)
         {
           s = newLocalSymbol(symbolName, symbolCs, proc_name);          
         }     
       else
         {
           errors++;
           printf ("%s is already defined\n", symbolName);
         }      
     }
  
   
   int checkSymbol(char *symbolName)
    {
      symrec *name;
      name = getSymbol(symbolName);
      if(name == 0)
        {
          errors++;
          printf ("%s has not been defined yet\n",symbolName);
	  return 0;
        }      
	return 1;
    }

   int checkDefSymbol(char *symbolName, char *proc_name)
    {
     	vardefinition *s;
	s = getDefSymbol(symbolName);
	if(s == 0)
	{		
		printf("%s has not been defined yet\n", symbolName);
		errors++;
		return 0;
	}else
	{
		if(strcmp(s->proc_name,proc_name)!=0)
		{
			printf("%s has not been defined yet\n", symbolName);
			errors++;
			return 0;
		}
	}
	return 1;
    }

   char * getConstraintSystem(char *symbolName)
   {     
      symrec *name;

      name = getSymbol(symbolName);   
      return name->cs;
   }
 
   
  
   /********************************
   * end symbol table functions *
   ********************************/



 
 
  


/* Line 268 of yacc.c  */
#line 263 "program_parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     INT = 259,
     NAME = 260,
     INVOCNAME = 261,
     DEF = 262,
     SYSTEM = 263,
     TELL = 264,
     WHEN = 265,
     DO = 266,
     LOCAL = 267,
     IN = 268,
     NEXT = 269,
     UNLESS = 270,
     WEVER = 271,
     SKIP = 272,
     ABORT = 273,
     NOT = 274,
     EXISTS = 275,
     ARROW = 276,
     STAR = 277,
     PAR = 278,
     TU = 279,
     FD = 280,
     XRI = 281,
     EQ = 282,
     SQRT = 283,
     TIMES = 284,
     PLUS = 285,
     SIN = 286,
     COS = 287,
     TAN = 288,
     ABS = 289,
     SQUARE = 290,
     BEG = 291,
     END = 292,
     ASSIGN = 293,
     LESS = 294,
     LEQ = 295,
     EQUAL = 296,
     DIFFERENT = 297,
     GEQXRI = 298,
     GTXRI = 299,
     NEXRI = 300,
     LTXRI = 301,
     LEQXRI = 302,
     GREATER = 303,
     GEQ = 304,
     DOMVAR = 305,
     ALLVARS = 306,
     DOMALLVARS = 307,
     DEFCS = 308
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 193 "program_parser.y"

  double real;
  int integer;
  char* text;
  char* id;




/* Line 293 of yacc.c  */
#line 362 "program_parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 374 "program_parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   189

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  60
/* YYNRULES -- Number of rules.  */
#define YYNRULES  122
/* YYNRULES -- Number of states.  */
#define YYNSTATES  223

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    65,     2,    62,     2,     2,    11,     2,
      63,    64,     9,     8,    61,     7,    70,    10,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    60,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    68,     2,    69,    12,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    66,     2,    67,     2,     2,     2,     2,
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
       5,     6,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,    11,    20,    22,    26,    28,    29,    34,
      37,    39,    41,    45,    48,    51,    53,    56,    60,    64,
      68,    73,    76,    78,    81,    82,    83,    92,    94,    96,
      98,   100,   105,   106,   113,   114,   122,   123,   131,   132,
     138,   139,   147,   148,   152,   153,   157,   159,   161,   162,
     169,   170,   179,   180,   189,   190,   196,   197,   205,   207,
     211,   213,   217,   218,   225,   226,   232,   233,   240,   242,
     244,   247,   249,   251,   253,   257,   258,   263,   264,   266,
     268,   270,   271,   276,   277,   282,   283,   288,   290,   292,
     294,   296,   298,   300,   301,   307,   309,   311,   313,   315,
     317,   319,   321,   324,   325,   331,   333,   335,   337,   339,
     341,   343,   345,   347,   349,   351,   353,   356,   357,   363,
     365,   367,   369
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      72,     0,    -1,    42,    74,    78,    79,    83,   104,    73,
      -1,    42,    74,    78,    79,    80,    83,   104,    73,    -1,
      43,    -1,    59,    60,    75,    -1,    77,    -1,    -1,    77,
      61,    76,    75,    -1,    77,    61,    -1,    31,    -1,    32,
      -1,    30,    60,     4,    -1,    30,    60,    -1,    30,     4,
      -1,    82,    -1,    82,    79,    -1,    57,    58,    81,    -1,
       4,    62,     4,    -1,     3,    62,     3,    -1,    77,     6,
      56,    81,    -1,    77,     6,    -1,    84,    -1,    84,    83,
      -1,    -1,    -1,    13,     5,    85,    63,   127,    64,    86,
      87,    -1,    88,    -1,    97,    -1,     5,    -1,   106,    -1,
      15,    63,   111,    64,    -1,    -1,    63,    89,    87,    29,
     102,    64,    -1,    -1,    16,    63,   111,    64,    17,    90,
      87,    -1,    -1,    18,    91,    63,   127,    64,    19,    87,
      -1,    -1,    20,    63,    92,    87,    64,    -1,    -1,    21,
      63,   111,    64,    20,    93,    87,    -1,    -1,    28,    94,
      87,    -1,    -1,    65,    95,    87,    -1,    23,    -1,    24,
      -1,    -1,    66,    96,    87,     8,   103,    67,    -1,    -1,
      28,    68,     4,    61,     4,    69,    98,    87,    -1,    -1,
      65,    68,     4,    61,     4,    69,    99,    87,    -1,    -1,
      20,    12,     4,   100,    87,    -1,    -1,    22,   101,    63,
     111,    64,    17,    87,    -1,    87,    -1,    87,    29,   102,
      -1,    87,    -1,    87,     8,   103,    -1,    -1,    14,    60,
      66,   105,   110,    67,    -1,    -1,     5,    63,   107,   130,
      64,    -1,    -1,     5,    70,    63,   109,   130,    64,    -1,
      87,    -1,   108,    -1,   108,   110,    -1,   112,    -1,   120,
      -1,   113,    -1,   113,    11,   112,    -1,    -1,   115,   119,
     114,   115,    -1,    -1,     5,    -1,     6,    -1,     4,    -1,
      -1,   115,     7,   116,   115,    -1,    -1,   115,     8,   117,
     115,    -1,    -1,   115,     9,   118,   115,    -1,    54,    -1,
      55,    -1,    45,    -1,    47,    -1,    46,    -1,    48,    -1,
      -1,   122,    63,   121,   123,    64,    -1,    53,    -1,    49,
      -1,    50,    -1,    51,    -1,    52,    -1,    33,    -1,   124,
      -1,   124,   123,    -1,    -1,   126,    63,   125,   123,    64,
      -1,     3,    -1,     5,    -1,     6,    -1,    34,    -1,    36,
      -1,    35,    -1,    40,    -1,    41,    -1,    37,    -1,    38,
      -1,    39,    -1,    77,     5,    -1,    -1,    77,     5,    61,
     128,   127,    -1,     6,    -1,     5,    -1,   129,    -1,   129,
      61,   130,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   252,   252,   253,   257,   260,   263,   264,   264,   265,
     268,   269,   272,   273,   274,   277,   278,   281,   284,   285,
     288,   289,   292,   293,   296,   296,   296,   300,   301,   302,
     303,   306,   307,   307,   308,   308,   309,   309,   310,   310,
     311,   311,   312,   312,   313,   313,   314,   315,   316,   316,
     320,   320,   321,   321,   322,   322,   323,   323,   326,   327,
     330,   331,   337,   337,   341,   341,   344,   344,   345,   348,
     349,   353,   354,   357,   358,   361,   361,   364,   365,   372,
     377,   378,   378,   379,   379,   380,   380,   384,   385,   386,
     387,   388,   389,   392,   392,   412,   413,   414,   415,   416,
     417,   420,   421,   424,   424,   429,   430,   435,   443,   444,
     445,   446,   447,   448,   449,   450,   456,   457,   457,   460,
     461,   464,   465
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "INT", "NAME", "INVOCNAME",
  "'-'", "'+'", "'*'", "'/'", "'&'", "'^'", "DEF", "SYSTEM", "TELL",
  "WHEN", "DO", "LOCAL", "IN", "NEXT", "UNLESS", "WEVER", "SKIP", "ABORT",
  "NOT", "EXISTS", "ARROW", "STAR", "PAR", "TU", "FD", "XRI", "EQ", "SQRT",
  "TIMES", "PLUS", "SIN", "COS", "TAN", "ABS", "SQUARE", "BEG", "END",
  "ASSIGN", "LESS", "LEQ", "EQUAL", "DIFFERENT", "GEQXRI", "GTXRI",
  "NEXRI", "LTXRI", "LEQXRI", "GREATER", "GEQ", "DOMVAR", "ALLVARS",
  "DOMALLVARS", "DEFCS", "':'", "','", "'#'", "'('", "')'", "'!'", "'{'",
  "'}'", "'['", "']'", "'.'", "$accept", "program", "end", "def_css",
  "css", "$@1", "cs", "stime", "var_defs", "domains", "domains_boundaries",
  "var_def", "proc_defs", "proc_def", "$@2", "$@3", "process",
  "basic_process", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "$@11", "complex_process", "$@12", "$@13", "$@14", "$@15", "rep_proc",
  "sum_proc", "system", "$@16", "def_process_invocation", "$@17",
  "call_proc", "$@18", "call_procs", "c", "fd_constraints",
  "fd_constraint", "$@19", "fd_exp", "$@20", "$@21", "$@22",
  "fd_relational_op", "xri_constraint", "$@23", "relational_op",
  "xri_exps", "xri_exp", "$@24", "arithmetic_op", "names", "$@25",
  "call_name", "call_names", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,    45,    43,    42,
      47,    38,    94,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
      58,    44,    35,    40,    41,    33,   123,   125,    91,    93,
      46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    71,    72,    72,    73,    74,    75,    76,    75,    75,
      77,    77,    78,    78,    78,    79,    79,    80,    81,    81,
      82,    82,    83,    83,    85,    86,    84,    87,    87,    87,
      87,    88,    89,    88,    90,    88,    91,    88,    92,    88,
      93,    88,    94,    88,    95,    88,    88,    88,    96,    88,
      98,    97,    99,    97,   100,    97,   101,    97,   102,   102,
     103,   103,   105,   104,   107,   106,   109,   108,   108,   110,
     110,   111,   111,   112,   112,   114,   113,   115,   115,   115,
     115,   116,   115,   117,   115,   118,   115,   119,   119,   119,
     119,   119,   119,   121,   120,   122,   122,   122,   122,   122,
     122,   123,   123,   125,   124,   124,   124,   124,   126,   126,
     126,   126,   126,   126,   126,   126,   127,   128,   127,   129,
     129,   130,   130
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     7,     8,     1,     3,     1,     0,     4,     2,
       1,     1,     3,     2,     2,     1,     2,     3,     3,     3,
       4,     2,     1,     2,     0,     0,     8,     1,     1,     1,
       1,     4,     0,     6,     0,     7,     0,     7,     0,     5,
       0,     7,     0,     3,     0,     3,     1,     1,     0,     6,
       0,     8,     0,     8,     0,     5,     0,     7,     1,     3,
       1,     3,     0,     6,     0,     5,     0,     6,     1,     1,
       2,     1,     1,     1,     3,     0,     4,     0,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     1,     1,     1,
       1,     1,     1,     0,     5,     1,     1,     1,     1,     1,
       1,     1,     2,     0,     5,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     0,     5,     1,
       1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     1,     0,     0,     0,    10,
      11,     5,     6,    14,    13,     0,     0,    15,     7,    12,
      21,     0,     0,     0,     0,    22,    16,     0,     0,    24,
       0,     0,     0,     0,    23,     8,     0,     0,    20,     0,
      17,     0,     0,     4,     2,     0,     0,     0,     3,    62,
      19,    18,     0,     0,     0,   116,    25,    29,     0,     0,
      36,     0,     0,    56,    46,    47,    42,    32,    44,    48,
      68,    27,    28,    30,    69,     0,   117,     0,    64,     0,
      77,    77,     0,     0,    38,    77,     0,     0,     0,     0,
       0,     0,     0,    70,    63,     0,    29,    26,     0,    66,
      80,    78,    79,   100,    96,    97,    98,    99,    95,     0,
      71,    73,     0,    72,     0,     0,     0,    54,     0,     0,
      77,     0,    43,     0,     0,    45,     0,   118,   120,   119,
     121,     0,     0,    31,    77,    81,    83,    85,    89,    91,
      90,    92,    87,    88,    75,    93,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    65,     0,    74,
      77,    77,    77,    77,     0,    34,     0,    55,    39,    40,
       0,     0,    58,     0,     0,    60,     0,   122,    67,    82,
      84,    86,    76,   105,   106,   107,   108,   110,   109,   113,
     114,   115,   111,   112,     0,   101,     0,     0,     0,     0,
       0,    50,     0,    33,    52,     0,    49,    94,   102,   103,
      35,    37,    41,    57,     0,    59,     0,    61,     0,    51,
      53,     0,   104
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    44,     4,    11,    27,    52,     8,    16,    23,
      38,    17,    24,    25,    39,    77,    70,    71,    89,   197,
      82,   118,   199,    88,    91,    92,    72,   214,   216,   148,
      86,   173,   176,    33,    54,    73,    98,    74,   132,    75,
     109,   110,   111,   163,   112,   160,   161,   162,   144,   113,
     164,   114,   194,   195,   218,   196,    53,    95,   130,   131
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -191
static const yytype_int16 yypact[] =
{
     -29,     0,    61,     2,    39,  -191,   -23,    -3,   -23,  -191,
    -191,  -191,     9,  -191,    73,    67,    -9,   -23,    54,  -191,
      44,    81,    56,   102,   103,   102,  -191,   -23,    29,  -191,
      29,   103,    58,    76,  -191,  -191,    62,    64,  -191,    53,
    -191,    76,    63,  -191,  -191,   124,   126,   -23,  -191,  -191,
    -191,  -191,   127,    70,     1,    72,  -191,   -60,    68,    75,
    -191,   -10,    77,  -191,  -191,  -191,    74,  -191,    78,  -191,
    -191,  -191,  -191,  -191,     1,    80,  -191,    22,  -191,    82,
      30,    30,    86,   131,  -191,    30,    87,   132,    22,    22,
     137,    22,    22,  -191,  -191,   -23,    88,  -191,    46,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,    79,
    -191,   133,    47,  -191,    89,    84,   -23,  -191,    22,    90,
      30,    92,  -191,   128,    94,  -191,   148,  -191,  -191,  -191,
      97,    95,    46,  -191,    85,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,   143,    98,    22,    99,
     141,   100,   161,    22,   162,    22,    46,  -191,   105,  -191,
      85,    85,    85,    85,    69,  -191,   149,  -191,  -191,  -191,
     150,   101,   142,   108,   106,   165,   107,  -191,  -191,   167,
     167,  -191,   104,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,   113,    69,   115,    22,    22,    22,
      22,  -191,    22,  -191,  -191,    22,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,    22,  -191,    22,  -191,    69,  -191,
    -191,   116,  -191
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -191,  -191,   138,  -191,   154,  -191,    41,  -191,   166,  -191,
     152,  -191,    -5,  -191,  -191,  -191,   -77,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,   -18,   -20,   155,  -191,  -191,  -191,  -191,  -191,   114,
     -55,    55,  -191,  -191,   -64,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -190,  -191,  -191,  -191,   -56,  -191,  -191,  -125
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -10
static const yytype_int16 yytable[] =
{
      97,    13,    83,    78,    21,   208,    57,   158,     9,    10,
      79,   122,   123,     1,   125,   126,    58,    59,    31,    60,
      34,    61,    62,    63,    64,    65,   115,    96,   221,    66,
     119,   177,    36,    37,   100,   101,   102,    58,    59,   127,
      60,   149,    61,    62,    63,    64,    65,    12,    22,    15,
      66,   128,   129,    84,   135,   136,   137,    14,    15,     3,
     147,     5,     6,   103,    67,   151,    68,    69,    12,     7,
      18,   167,   183,    20,   184,   185,   172,    19,   175,   104,
     105,   106,   107,   108,    -9,    67,    29,    68,    69,   100,
     101,   102,   138,   139,   140,   141,   179,   180,   181,   182,
      28,   142,   143,   186,   187,   188,   189,   190,   191,   192,
     193,   135,   136,   137,    30,    21,    47,    32,    42,    43,
     210,   211,   212,   213,    45,   172,    46,    50,   175,    49,
      51,    80,    55,    76,    56,   117,   121,   219,    81,   220,
      85,   124,    87,   133,   134,    99,    90,    94,   146,   116,
     120,    78,   145,   152,   150,   154,   155,   153,   156,   157,
     165,   169,   166,   168,   170,   171,   174,   200,   198,   178,
     201,   202,   203,   205,   206,   204,   137,   207,   209,    48,
     222,    35,    40,    26,   215,   217,    41,     0,    93,   159
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-191))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      77,     4,    12,    63,    13,   195,     5,   132,    31,    32,
      70,    88,    89,    42,    91,    92,    15,    16,    23,    18,
      25,    20,    21,    22,    23,    24,    81,     5,   218,    28,
      85,   156,     3,     4,     4,     5,     6,    15,    16,    95,
      18,   118,    20,    21,    22,    23,    24,     6,    57,     8,
      28,     5,     6,    63,     7,     8,     9,    60,    17,    59,
     116,     0,    60,    33,    63,   120,    65,    66,    27,    30,
      61,   148,     3,     6,     5,     6,   153,     4,   155,    49,
      50,    51,    52,    53,    30,    63,     5,    65,    66,     4,
       5,     6,    45,    46,    47,    48,   160,   161,   162,   163,
      56,    54,    55,    34,    35,    36,    37,    38,    39,    40,
      41,     7,     8,     9,    58,    13,    63,    14,    60,    43,
     197,   198,   199,   200,    62,   202,    62,     3,   205,    66,
       4,    63,     5,    61,    64,     4,     4,   214,    63,   216,
      63,     4,    68,    64,    11,    63,    68,    67,    64,    63,
      63,    63,    63,    61,    64,    61,     8,    29,    61,    64,
      17,    20,    64,    64,    64,     4,     4,    17,    19,    64,
      69,    29,    64,     8,    67,    69,     9,    64,    63,    41,
      64,    27,    30,    17,   202,   205,    31,    -1,    74,   134
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    42,    72,    59,    74,     0,    60,    30,    78,    31,
      32,    75,    77,     4,    60,    77,    79,    82,    61,     4,
       6,    13,    57,    80,    83,    84,    79,    76,    56,     5,
      58,    83,    14,   104,    83,    75,     3,     4,    81,    85,
      81,   104,    60,    43,    73,    62,    62,    63,    73,    66,
       3,     4,    77,   127,   105,     5,    64,     5,    15,    16,
      18,    20,    21,    22,    23,    24,    28,    63,    65,    66,
      87,    88,    97,   106,   108,   110,    61,    86,    63,    70,
      63,    63,    91,    12,    63,    63,   101,    68,    94,    89,
      68,    95,    96,   110,    67,   128,     5,    87,   107,    63,
       4,     5,     6,    33,    49,    50,    51,    52,    53,   111,
     112,   113,   115,   120,   122,   111,    63,     4,    92,   111,
      63,     4,    87,    87,     4,    87,    87,   127,     5,     6,
     129,   130,   109,    64,    11,     7,     8,     9,    45,    46,
      47,    48,    54,    55,   119,    63,    64,   127,   100,    87,
      64,   111,    61,    29,    61,     8,    61,    64,   130,   112,
     116,   117,   118,   114,   121,    17,    64,    87,    64,    20,
      64,     4,    87,   102,     4,    87,   103,   130,    64,   115,
     115,   115,   115,     3,     5,     6,    34,    35,    36,    37,
      38,    39,    40,    41,   123,   124,   126,    90,    19,    93,
      17,    69,    29,    64,    69,     8,    67,    64,   123,    63,
      87,    87,    87,    87,    98,   102,    99,   103,   125,    87,
      87,   123,    64
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
      int yyn = yypact[*yyssp];
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
      yychar = YYLEX;
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:

/* Line 1806 of yacc.c  */
#line 257 "program_parser.y"
    {generate_code(ENDR); generate_constraint(ENDCC,"endcc",0,0.0," ");  generate_cs("end");}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 263 "program_parser.y"
    {csNum++; generate_cs((yyvsp[(1) - (1)].text));}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 264 "program_parser.y"
    {csNum++; generate_cs((yyvsp[(1) - (2)].text));}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 265 "program_parser.y"
    {errors++; printf ("Syntax error, missing constraint symbol\n");}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 272 "program_parser.y"
    {timeUnits = (yyvsp[(3) - (3)].integer);}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 273 "program_parser.y"
    {errors++; printf("Syntax error, missing integer \n");}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 274 "program_parser.y"
    {errors++; printf("Syntax error, missing assign symbol");}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 281 "program_parser.y"
    {allvarsdom=1;}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 284 "program_parser.y"
    {linf=(yyvsp[(1) - (3)].integer); lsup=(yyvsp[(3) - (3)].integer);}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 285 "program_parser.y"
    {linfR=(yyvsp[(1) - (3)].real); lsupR=(yyvsp[(3) - (3)].real);}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 288 "program_parser.y"
    {if(local_var==0){saveSymbolDomain((yyvsp[(2) - (4)].text), (yyvsp[(1) - (4)].text));}else{saveSymbolLocal((yyvsp[(2) - (4)].text), (yyvsp[(1) - (4)].text), process_name);}}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 289 "program_parser.y"
    {if(local_var==0){saveSymbol((yyvsp[(2) - (2)].text), (yyvsp[(1) - (2)].text));}else{saveSymbolLocal((yyvsp[(2) - (2)].text), (yyvsp[(1) - (2)].text), process_name);}}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 296 "program_parser.y"
    {process_name=(yyvsp[(2) - (2)].text);}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 296 "program_parser.y"
    { saveSymbol((yyvsp[(2) - (6)].text),"wcs"); generate_code_dp(PNAME, (yyvsp[(2) - (6)].text),0,0);}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 296 "program_parser.y"
    { generate_code_dp(RPARR,"",0,1);}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 302 "program_parser.y"
    {checkSymbol((yyvsp[(1) - (1)].text)); generate_code_dp(PNAME, (yyvsp[(1) - (1)].text),1,0);}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 303 "program_parser.y"
    {generate_code(INVOC);}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 306 "program_parser.y"
    {generate_code(TELLR);}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 307 "program_parser.y"
    {generate_code(PARR);}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 307 "program_parser.y"
    {generate_code(RPARR);}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 308 "program_parser.y"
    {generate_code(WHENR);}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 308 "program_parser.y"
    {generate_code(RPARR);}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 309 "program_parser.y"
    {generate_code(LOCALR); local_var = 1; }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 309 "program_parser.y"
    { generate_code_dp(RPARR,"",1,1); local_var=0;}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 310 "program_parser.y"
    {generate_code(NEXTR);}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 310 "program_parser.y"
    {generate_code(RPARR);}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 311 "program_parser.y"
    {generate_code(UNLESSR);}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 311 "program_parser.y"
    {generate_code(RPARR);}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 312 "program_parser.y"
    {generate_code(STARR);}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 312 "program_parser.y"
    {generate_code(RPARR);}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 313 "program_parser.y"
    {generate_code(REPR);}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 313 "program_parser.y"
    {generate_code(RPARR);}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 314 "program_parser.y"
    {generate_code(SKIPR);}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 315 "program_parser.y"
    {generate_code(ABORTR);}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 316 "program_parser.y"
    {generate_code(SUMR);}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 316 "program_parser.y"
    {generate_code(RPARR);}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 320 "program_parser.y"
    {generate_code_dp(BOUNDEDSTARR,"", (yyvsp[(3) - (6)].integer), (yyvsp[(5) - (6)].integer));}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 320 "program_parser.y"
    {generate_code(RPARR);}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 321 "program_parser.y"
    {generate_code_dp(BOUNDEDREPR,"", (yyvsp[(3) - (6)].integer), (yyvsp[(5) - (6)].integer));}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 321 "program_parser.y"
    {generate_code(RPARR);}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 322 "program_parser.y"
    {generate_code_dp(NEXTUPNR,"", (yyvsp[(3) - (3)].integer),0);}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 322 "program_parser.y"
    {generate_code(RPARR);}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 323 "program_parser.y"
    {generate_code(WHENEVERR);}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 323 "program_parser.y"
    {generate_code(RPARR);}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 337 "program_parser.y"
    {system_call=1; generate_code(ENDR); generate_constraint(ENDCC,"endcc",0,0.0," ");}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 337 "program_parser.y"
    {generate_process_invocation(3,"","","");}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 341 "program_parser.y"
    {generate_process_invocation(1,(yyvsp[(1) - (2)].text),"wcs",(yyvsp[(1) - (2)].text)); process_name=(yyvsp[(1) - (2)].text);}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 341 "program_parser.y"
    { generate_process_invocation(2,"","","");}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 344 "program_parser.y"
    {generate_process_invocation(1,(yyvsp[(1) - (3)].text),"wcs",(yyvsp[(1) - (3)].text)); process_name=(yyvsp[(1) - (3)].text);}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 344 "program_parser.y"
    {generate_process_invocation(2,"","","");}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 353 "program_parser.y"
    {generate_constraint(ENDC,"end",0,0.0,process_name); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 361 "program_parser.y"
    {generate_constraint(SYMBOLR,(yyvsp[(2) - (2)].text),0,0.0,process_name);}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 365 "program_parser.y"
    {	
        	if (local_var==1)
          	{ generate_constraint_name(CHAR,(yyvsp[(1) - (1)].text),0,0.0,process_name, getCsSymbol((yyvsp[(1) - (1)].text)), 1); }
        	else
          	{ 
			if(checkDefSymbol((yyvsp[(1) - (1)].text), process_name) !=0)
			{generate_constraint_name(CHAR,(yyvsp[(1) - (1)].text),0,0.0,process_name, getCsSymbol((yyvsp[(1) - (1)].text)), 0); }}}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 372 "program_parser.y"
    {if(system_call==1) 
         {if (local_var==1)
             { generate_constraint_name(CHAR,(yyvsp[(1) - (1)].text),0,0.0,process_name, getConstraintSystem((yyvsp[(1) - (1)].text)), 1); }
           else
             { generate_constraint_name(CHAR,(yyvsp[(1) - (1)].text),0,0.0,process_name, getConstraintSystem((yyvsp[(1) - (1)].text)), 0); }}else{errors++;}}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 377 "program_parser.y"
    {generate_constraint(INTR,"",(yyvsp[(1) - (1)].integer),0.0,process_name); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 378 "program_parser.y"
    {generate_constraint(SYMBOLR,"-",1,0.0,process_name);}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 379 "program_parser.y"
    {generate_constraint(SYMBOLR,"+",1,0.0,process_name);}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 380 "program_parser.y"
    {generate_constraint(SYMBOLR,"*",1,0.0,process_name);}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 392 "program_parser.y"
    {
  		char *tmpVar = (char *)malloc(512);
        
        	if(strcmp ((yyvsp[(1) - (2)].text),"eq") == 0)
          	{
            		strcat(tmpVar,"{RI.hc4 ");
            		strcat(tmpVar,(yyvsp[(1) - (2)].text));
            		strcat(tmpVar,"(");            
          	}else
          	{
            		strcat(tmpVar,"{RI.");
            		strcat(tmpVar,(yyvsp[(1) - (2)].text));
            		strcat(tmpVar," (");
          	}
  	
  		generate_constraint(SYMBOLR,tmpVar,0,0.0,process_name);}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 407 "program_parser.y"
    {eqvar=0;  
        	generate_constraint(SYMBOLR,")}",0,0.0,process_name);           
   		generate_constraint(ENDC,"end",0,0.0,process_name); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 424 "program_parser.y"
    {
  	   char *tmpVar = (char *)malloc(512);
  	   strcat(tmpVar,(yyvsp[(1) - (2)].text));
  	   strcat (tmpVar,"(");
  	   generate_constraint(SYMBOLR,tmpVar,0,0.0,process_name);}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 428 "program_parser.y"
    { generate_constraint(SYMBOLR,")",0,0.0,process_name);}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 429 "program_parser.y"
    {generate_constraint(DOUBLE,"",0,(yyvsp[(1) - (1)].real),process_name); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 430 "program_parser.y"
    {
	         if (local_var==1)
    	      {generate_constraint_name(CHAR,(yyvsp[(1) - (1)].text),0,0.0,process_name,getCsSymbol((yyvsp[(1) - (1)].text)),1);} 
  	         else
	         {generate_constraint_name(CHAR,(yyvsp[(1) - (1)].text),0,0.0,process_name, getCsSymbol((yyvsp[(1) - (1)].text)), 0);}}
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 435 "program_parser.y"
    {if(system_call==1) 
            {if (local_var==1)
                { generate_constraint_name(CHAR,(yyvsp[(1) - (1)].text),0,0.0,process_name, getConstraintSystem((yyvsp[(1) - (1)].text)), 1); }
             else
               { generate_constraint_name(CHAR,(yyvsp[(1) - (1)].text),0,0.0,process_name, getConstraintSystem((yyvsp[(1) - (1)].text)), 0); }}else{errors++;}}
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 456 "program_parser.y"
    {if(local_var==0){saveNewVarDefinition((yyvsp[(2) - (2)].text), (yyvsp[(1) - (2)].text), process_name);}else{saveSymbolLocal((yyvsp[(2) - (2)].text), (yyvsp[(1) - (2)].text), process_name);}}
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 457 "program_parser.y"
    {if(local_var == 0){saveNewVarDefinition((yyvsp[(2) - (3)].text), (yyvsp[(1) - (3)].text), process_name);}else{saveSymbolLocal((yyvsp[(2) - (3)].text), (yyvsp[(1) - (3)].text), process_name);}}
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 460 "program_parser.y"
    {if(checkSymbol((yyvsp[(1) - (1)].text))==1){generate_process_invocation(0,(yyvsp[(1) - (1)].text),getConstraintSystem((yyvsp[(1) - (1)].text)),process_name);}}
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 461 "program_parser.y"
    { if(system_call==1){errors++; printf("syntax error: the variable %s is not defined yet\n",(yyvsp[(1) - (1)].text));}else{ generate_process_invocation(0,(yyvsp[(1) - (1)].text),"wcs_",process_name);}}
    break;



/* Line 1806 of yacc.c  */
#line 2331 "program_parser.tab.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 469 "program_parser.y"
 



char *getNameFile(char* mystr) 
{
char *retstr;
    char *lastdot;
    if (mystr == NULL)
         return NULL;
    if ((retstr = malloc (strlen (mystr) + 1)) == NULL)
        return NULL;
    strcpy (retstr, mystr);
    lastdot = strrchr (retstr, '.');
    if (lastdot != NULL)
        *lastdot = '\0';
    return retstr;
}

int main(int argc, char **argv)
{
	if(argc>1)
	{
		yyin=fopen(argv[1],"rt");
        ozOutputFileTmp = argv[1];
	}
	else
      	{
		yyin=stdin; // Entrada por consola 		
        //nombre_archivo_entrada = stdin;
        	//yyin=fopen("p5.txt","rt"); // Entrada por archivos

      	}
   	
    	errors = 0;
    	timeUnits = 0;	
	yyparse();
    
   
    	if(errors==0)
      	{


          if((allvarsdom != 0) && (csNum >1))
            {
              printf("Error: allvars only cannot be used more than one constraint system.");
            }
            else
            {

              char *ozOutputFile = (char *)malloc(512);
              char *ozOutFileTxt = (char *)malloc(512);
              strcat(ozOutputFile,getNameFile(ozOutputFileTmp));
              strcat(ozOutFileTxt,ozOutputFile);
              strcat(ozOutFileTxt,"c.txt");
              strcat(ozOutputFile, ".oz");
            //  printf("Este es el nombre del archivo %s\n",ozOutputFile);
              // char *ozOutputFile = (char *)malloc(512);
              
             // FILE *outputFile = fopen(OZFILE,"w+");
	      FILE *outputFile = fopen(ozOutputFile,"w+");              
              printHead(outputFile);
              printVars(outputFile);
              if(allvarsdom == 0)
                {
                  printVarsDomains(outputFile);
                }else
                {
  	                struct domain domain;
			if (lsup != 0)
			{
			  	domain.domainInfI = linf;
			  	domain.domainSupI = lsup;
	                  	printAllVarsDomain(outputFile,domain,1);
			}else
			{
				domain.domainInfR = linfR;
			  	domain.domainSupR = lsupR;
	                  	printAllVarsDomain(outputFile,domain, 0);
			}
                }        
              
              generate_constSystems(outputFile);
              generate_simulation_time(outputFile,timeUnits);    
              generate_process(outputFile);
              generate_invocation(outputFile,0);
              printTail(outputFile,ozOutFileTxt); 
            
            
              printf("Process completed successfully.\n");
            }
      	}
   	return 0;
} 

yyerror(char *s)
{
  errors++;
  printf("Syntax error %s at line (%i) \n",s,yylineno);
}

