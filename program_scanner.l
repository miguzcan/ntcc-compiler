%{
      #include <stdio.h>
      #include <stdlib.h>
      #include <string.h>
      #include "program_parser.tab.h" 
      int line=0;
%}

%option yylineno
DIGIT [0-9]
NUMBER {DIGIT}+("."{DIGIT}+)?
ID [a-z][a-z0-9A-Z]*
PROCID [A-Z][a-z0-9A-Z]*


%%
"->"	      {return(ARROW);}
"**"	      {return(STAR);}
"||"	      {return(PAR);}
"<-"	      {return(ASSIGN);}
"::"          {return(DOMVAR);}
":::"         {return(DOMALLVARS);}
allvars       {return(ALLVARS);}
cs	      {return(DEFCS);}	
system        {return(SYSTEM);}
def           {return(DEF);}
timeUnits     {return(TU);}
tell	      {return(TELL);}
when	      {return(WHEN);}
do	      {return(DO);}
local	      {return(LOCAL);}
in	      {return(IN);}
next	      {return(NEXT);}
unless	      {return(UNLESS);}
whenever     {return(WEVER);}
skip	      {return(SKIP);}
abort	      {return(ABORT);}
not 	      {return(NOT);}
exists	      {return(EXISTS);}
fd	      {yylval.text = (char *) strdup(yytext); return(FD);}
xri	      {yylval.text = (char *) strdup(yytext); return(XRI);}
eq	      {yylval.text = (char *) strdup(yytext); return(EQ);}
sqrt	      {yylval.text = (char *) strdup(yytext); return(SQRT);}
times         {yylval.text = (char *) strdup(yytext); return(TIMES);}
plus          {yylval.text = (char *) strdup(yytext); return(PLUS);}
sin           {yylval.text = (char *) strdup(yytext); return(SIN);}
cos           {yylval.text = (char *) strdup(yytext); return(COS);}
tan           {yylval.text = (char *) strdup(yytext); return(TAN);}
abs           {yylval.text = (char *) strdup(yytext); return(ABS);}
square        {yylval.text = (char *) strdup(yytext); return(SQUARE);}
geq           {yylval.text = (char *) strdup(yytext); return(GEQXRI);}
gt            {yylval.text = (char *) strdup(yytext); return(GTXRI);}
ne            {yylval.text = (char *) strdup(yytext); return(NEXRI);}
lt            {yylval.text = (char *) strdup(yytext); return(LTXRI);}
leq           {yylval.text = (char *) strdup(yytext); return(LEQXRI);}
">="	      {yylval.text = (char *) strdup(yytext); return(GEQ);}
">"	      {yylval.text = (char *) strdup(yytext); return(GREATER);}
"<"	      {yylval.text = (char *) strdup(yytext); return(LESS);}
"="	      {yylval.text = (char *) strdup(yytext); return(EQUAL);}
"<="	      {yylval.text = (char *) strdup(yytext); return(LEQ);}
"!="	      {yylval.text = (char *) strdup(yytext); return(DIFFERENT);}
begin	      {return(BEG);}
end	      {return(END);}
{DIGIT}+      {yylval.integer = atoi( yytext ); return(INT);} 
{NUMBER}      {yylval.real=atof(yytext); return(NUMBER);}
{PROCID}+	      {yylval.id = (char *) strdup(yytext); return(NAME);}
{ID}+	      {yylval.id = (char *) strdup(yytext); return(INVOCNAME);}
"\n"	      {line++;}
"%".* 	      /*   comments  */
[ \t\n]+      /* blank, tab, new line: eat up whitespace */
[#,=().{}:\[\]!^+&*-]          {return yytext[0];}
.	      { printf ("lexic error: \"%s\" line(%i) \n", yytext, line);
	        return yytext[0]; 
	      }
%%
 
