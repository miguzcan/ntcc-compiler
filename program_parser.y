%{

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



 
 
  
%}

%union
{
  double real;
  int integer;
  char* text;
  char* id;

}

%start program;

%token <real> NUMBER
%token <integer> INT
%token <text> NAME INVOCNAME


%left '-' '+'
%left '*' '/'
%left '&'
%right '^'

 

%token DEF
%token SYSTEM
%token TELL WHEN
%token DO LOCAL
%token IN NEXT
%token UNLESS WEVER
%token SKIP ABORT
%token NOT EXISTS
%token ARROW 
%token STAR 
%token PAR TU
%token <text> FD XRI
%token <text> EQ SQRT TIMES PLUS
%token <text> SIN COS TAN 
%token <text> ABS SQUARE
%token BEG END
%token ASSIGN 
%token <text> LESS LEQ
%token <text> EQUAL DIFFERENT
%token <text> GEQXRI GTXRI
%token <text> NEXRI LTXRI
%token <text> LEQXRI
%token <text> GREATER GEQ
%token DOMVAR
%token ALLVARS DOMALLVARS
%token DEFCS

%type <text> cs
%type <text> relational_op
%type <text> fd_relational_op
%type <text> arithmetic_op 

// used in order to avoid de confict warnings
%expect 2

%%

program:  BEG def_css stime var_defs proc_defs system end
	  |BEG def_css stime var_defs domains proc_defs system end
		;


end:    END {generate_code(ENDR); generate_constraint(ENDCC,"endcc",0,0.0," ");  generate_cs("end");}
        ;

def_css : DEFCS ':' css
	;

css:	cs {csNum++; generate_cs($1);}
|cs ',' {csNum++; generate_cs($1);} css 
        |cs ',' {errors++; printf ("Syntax error, missing constraint symbol\n");}
	;

cs:	FD 
        |XRI  
	;

stime:	TU ':' INT {timeUnits = $3;} 
        |TU ':' {errors++; printf("Syntax error, missing integer \n");}
        |TU INT {errors++; printf("Syntax error, missing assign symbol");}
		;

var_defs: var_def 
          |var_def var_defs
		    ;

domains:  ALLVARS DOMALLVARS domains_boundaries {allvarsdom=1;}
;

domains_boundaries: INT '#' INT {linf=$1; lsup=$3;}
		    |NUMBER '#' NUMBER {linfR=$1; lsupR=$3;};
;

var_def:   cs INVOCNAME DOMVAR domains_boundaries {if(local_var==0){saveSymbolDomain($2, $1);}else{saveSymbolLocal($2, $1, process_name);}}
|cs INVOCNAME {if(local_var==0){saveSymbol($2, $1);}else{saveSymbolLocal($2, $1, process_name);}}
	   ;

proc_defs: proc_def
	   |proc_def proc_defs
	   ;

proc_def:  DEF NAME {process_name=$2;} '(' names ')' { saveSymbol($2,"wcs"); generate_code_dp(PNAME, $2,0,0);} process { generate_code_dp(RPARR,"",0,1);}
            ;

 
process:  basic_process
	  |complex_process
          |NAME {checkSymbol($1); generate_code_dp(PNAME, $1,1,0);} 
	  |def_process_invocation {generate_code(INVOC);}
	  ;

basic_process:  TELL '(' c ')' {generate_code(TELLR);}
		|'(' {generate_code(PARR);} process PAR rep_proc ')' {generate_code(RPARR);}
		|WHEN '('c')' DO {generate_code(WHENR);}  process {generate_code(RPARR);} 
        	|LOCAL {generate_code(LOCALR); local_var = 1; } '('names')' IN process { generate_code_dp(RPARR,"",1,1); local_var=0;}             
                |NEXT '('{generate_code(NEXTR);} process ')' {generate_code(RPARR);}
                |UNLESS '('c')' NEXT {generate_code(UNLESSR);} process {generate_code(RPARR);}
                |STAR {generate_code(STARR);} process {generate_code(RPARR);}
                |'!' {generate_code(REPR);} process {generate_code(RPARR);}
                |SKIP {generate_code(SKIPR);} 
                |ABORT {generate_code(ABORTR);} 
                |'{' {generate_code(SUMR);} process '+'  sum_proc '}' {generate_code(RPARR);}
	//	| sp '+'  sum_proc ')' 	 
		;

complex_process:  STAR '[' INT ',' INT ']' {generate_code_dp(BOUNDEDSTARR,"", $3, $5);} process {generate_code(RPARR);}
                  |'!' '[' INT ',' INT ']' {generate_code_dp(BOUNDEDREPR,"", $3, $5);} process  {generate_code(RPARR);}
                  |NEXT '^' INT {generate_code_dp(NEXTUPNR,"", $3,0);} process {generate_code(RPARR);}
                  |WEVER  {generate_code(WHENEVERR);} '(' c ')' DO process {generate_code(RPARR);}
                  ;

rep_proc:    process 
             |process PAR rep_proc
             ;

sum_proc:    process 
             |process '+' sum_proc
             ;

//sp: /* */'( ' {generate_code(SUMR);} process 
///	;

system: SYSTEM ':' '{' {system_call=1; generate_code(ENDR); generate_constraint(ENDCC,"endcc",0,0.0," ");} call_procs '}' {generate_process_invocation(3,"","","");}
        ;


def_process_invocation: NAME '(' {generate_process_invocation(1,$1,"wcs",$1); process_name=$1;} call_names ')' { generate_process_invocation(2,"","","");}
			;

call_proc: NAME '.' '(' {generate_process_invocation(1,$1,"wcs",$1); process_name=$1;} call_names ')' {generate_process_invocation(2,"","","");}
	  | process	   	 
        ;

call_procs: call_proc	    	    
            |call_proc call_procs
            ;


c: fd_constraints {generate_constraint(ENDC,"end",0,0.0,process_name); }
   |xri_constraint
   ;

fd_constraints: fd_constraint
		|fd_constraint '&' fd_constraints
		;

fd_constraint: fd_exp fd_relational_op {generate_constraint(SYMBOLR,$2,0,0.0,process_name);} fd_exp 		
		;

fd_exp: /*  */
    	|NAME {	
        	if (local_var==1)
          	{ generate_constraint_name(CHAR,$1,0,0.0,process_name, getCsSymbol($1), 1); }
        	else
          	{ 
			if(checkDefSymbol($1, process_name) !=0)
			{generate_constraint_name(CHAR,$1,0,0.0,process_name, getCsSymbol($1), 0); }}}
    	|INVOCNAME {if(system_call==1) 
         {if (local_var==1)
             { generate_constraint_name(CHAR,$1,0,0.0,process_name, getConstraintSystem($1), 1); }
           else
             { generate_constraint_name(CHAR,$1,0,0.0,process_name, getConstraintSystem($1), 0); }}else{errors++;}}
    	|INT {generate_constraint(INTR,"",$1,0.0,process_name); }
	|fd_exp '-' {generate_constraint(SYMBOLR,"-",1,0.0,process_name);} fd_exp
	|fd_exp '+' {generate_constraint(SYMBOLR,"+",1,0.0,process_name);} fd_exp	
	|fd_exp '*' {generate_constraint(SYMBOLR,"*",1,0.0,process_name);} fd_exp
	;


fd_relational_op:   GREATER 
		    |GEQ 
		    |LESS 
		    |EQUAL 
		    |LEQ 
		    |DIFFERENT 
		    ;

xri_constraint: relational_op '(' {
  		char *tmpVar = (char *)malloc(512);
        
        	if(strcmp ($1,"eq") == 0)
          	{
            		strcat(tmpVar,"{RI.hc4 ");
            		strcat(tmpVar,$1);
            		strcat(tmpVar,"(");            
          	}else
          	{
            		strcat(tmpVar,"{RI.");
            		strcat(tmpVar,$1);
            		strcat(tmpVar," (");
          	}
  	
  		generate_constraint(SYMBOLR,tmpVar,0,0.0,process_name);} xri_exps ')' {eqvar=0;  
        	generate_constraint(SYMBOLR,")}",0,0.0,process_name);           
   		generate_constraint(ENDC,"end",0,0.0,process_name); }
		;

relational_op : LEQXRI
		|GEQXRI
		|GTXRI
		|NEXRI
		|LTXRI
		|EQ 
		;

xri_exps : xri_exp
	   |xri_exp xri_exps
	   ;

xri_exp :  arithmetic_op '('  {
  	   char *tmpVar = (char *)malloc(512);
  	   strcat(tmpVar,$1);
  	   strcat (tmpVar,"(");
  	   generate_constraint(SYMBOLR,tmpVar,0,0.0,process_name);} xri_exps ')' { generate_constraint(SYMBOLR,")",0,0.0,process_name);}
	   |NUMBER {generate_constraint(DOUBLE,"",0,$1,process_name); }
	   |NAME {
	         if (local_var==1)
    	      {generate_constraint_name(CHAR,$1,0,0.0,process_name,getCsSymbol($1),1);} 
  	         else
	         {generate_constraint_name(CHAR,$1,0,0.0,process_name, getCsSymbol($1), 0);}}
       	   |INVOCNAME {if(system_call==1) 
            {if (local_var==1)
                { generate_constraint_name(CHAR,$1,0,0.0,process_name, getConstraintSystem($1), 1); }
             else
               { generate_constraint_name(CHAR,$1,0,0.0,process_name, getConstraintSystem($1), 0); }}else{errors++;}}
	   ;


arithmetic_op : SQRT
		|PLUS
		|TIMES 
		|ABS
		|SQUARE 
		|SIN
		|COS
		|TAN
		;




names:	cs NAME {if(local_var==0){saveNewVarDefinition($2, $1, process_name);}else{saveSymbolLocal($2, $1, process_name);}}
	|cs NAME ',' {if(local_var == 0){saveNewVarDefinition($2, $1, process_name);}else{saveSymbolLocal($2, $1, process_name);}} names
	 ;

call_name: INVOCNAME {if(checkSymbol($1)==1){generate_process_invocation(0,$1,getConstraintSystem($1),process_name);}}
	   |NAME { if(system_call==1){errors++; printf("syntax error: the variable %s is not defined yet\n",$1);}else{ generate_process_invocation(0,$1,"wcs_",process_name);}}
	;

call_names :  call_name
	      |call_name ',' call_names
	      ;

			 
%% 



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
