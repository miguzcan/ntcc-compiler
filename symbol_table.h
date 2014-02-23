/*************************************************************
 *       Symbol Table                                       *
 *************************************************************/

/*************************************************************
 *       Structures                                          *
 *************************************************************/


/* Structure of a domain (that belong to a symbol)*/
struct domain
{
  double domainInfR; 
  double domainSupR;
  int domainInfI;
  int domainSupI;
};

/* Structure of the symbol table records*/
struct symrec
{
  char *name; /* name of symbol*/
  int offset; /* data offset*/
  char *cs;   /* Constraint system*/
  struct domain domain;
  struct symrec *next;/* link field*/
};
typedef struct symrec symrec;

/* Structure of the variable definition*/
struct vardefinition
{
  char *name;
  int offset;
  char *cs;
  char *proc_name;
  struct vardefinition *next;
};
typedef struct vardefinition vardefinition;

/*Structure of the local variables table records*/
struct localVariables
{
  char *name;
  int offset;
  char *cs;
  char *proc_name;
  //int position;
  struct localVariables *next;
};
typedef struct localVariables localVariables;



/*************************************************************
 *       Symbol tables                                       *
 *************************************************************/

/* The symbol table per se, of the invocations*/
symrec *sym_table = (symrec *)0; 

/* Symbol table of the variables of the definitions*/
vardefinition *vardef_table = (vardefinition *)0;

/*Symbol Table with the local variables*/
localVariables *lvars_table = (localVariables *)0;


/*************************************************************
 *       Operations applied over the symbol tables           *
 *************************************************************/

/* Variables definition (initial offsets)*/
int data_offset = 0; 
int vardef_offset = 0;
int lvars_offset =0;

/* Reserve a location for a symbol*/
int location(int offset)
{
	return offset++;
}

/*************************************************************
 *       Operations over the variable definition ST          *
 *************************************************************/


/* Insert a new variable into the symbol table*/
vardefinition * newVarDefinition (char *varName, char *cs, char *proc_name)
{
  vardefinition *new_var;
  new_var = (vardefinition *) malloc (sizeof(vardefinition));
  new_var->name = (char *) malloc (strlen(varName));
  strcpy (new_var->name, varName);
  new_var->offset =location(vardef_offset);
  new_var->cs = (char *) malloc (strlen(cs));
  strcpy (new_var->cs, cs);

  new_var->proc_name = (char *) malloc (strlen(proc_name));
  strcpy (new_var->proc_name, proc_name);
 
  new_var->next = (struct vardefinition *) vardef_table;
  vardef_table = new_var;
  return new_var;
  }



/* Return the constraint system of a variable into the symbol table*/
char * getCsSymbol (char *varName)
{
  char *result="";
  vardefinition *result_var;
  for(result_var = vardef_table; result_var != (vardefinition *)0; result_var = (vardefinition *)result_var->next)
    if (strcmp (result_var->name, varName) == 0)
      {
        result = result_var->cs;
        return result;
      }
  return result;
}

/* Return a symbol of the vardef symbol table*/
vardefinition * getDefSymbol (char *symbolName)
{
  vardefinition *result_symbol;
  for(result_symbol = vardef_table; result_symbol != (vardefinition *)0; result_symbol = (vardefinition *)result_symbol->next)
    if (strcmp (result_symbol->name, symbolName) == 0)
      {
        return result_symbol;
      }
  return 0;
}

/*************************************************************
 *       Operations over the invocations ST		     *
 *************************************************************/

/* Insert a new symbol into the symbol table*/
symrec * newSymbol (char *symbolName, char *symbolConstSyst)
{
  symrec *new_symbol;
  new_symbol = (symrec *) malloc (sizeof(symrec));
  new_symbol->name = (char *) malloc (strlen(symbolName));
  strcpy (new_symbol->name, symbolName);
  new_symbol->offset = location(data_offset);
  new_symbol->cs = (char *) malloc (strlen(symbolConstSyst));
  strcpy (new_symbol->cs, symbolConstSyst);
  new_symbol->next = (struct symrec *) sym_table;
  sym_table = new_symbol;
  return new_symbol;

  }

/* Insert a new symbol with its domain into the symbol table*/
symrec * newSymbolDomain (char *symbolName, char *symbolConstSyst, struct domain domainSymbol)
{
  symrec *new_symbol;
  new_symbol = (symrec *) malloc (sizeof(symrec));
  new_symbol->name = (char *) malloc (strlen(symbolName));
  strcpy (new_symbol->name, symbolName);
  new_symbol->offset = location(data_offset);
  new_symbol->cs = (char *) malloc (strlen(symbolConstSyst));
  strcpy (new_symbol->cs, symbolConstSyst);
  new_symbol->domain =  domainSymbol;
  new_symbol->next = (struct symrec *) sym_table;
  sym_table = new_symbol;
  return new_symbol;
  }

/* Return a symbol of the local symbol table*/
symrec * getSymbol (char *symbolName)
{
  symrec *result_symbol;
  for(result_symbol = sym_table; result_symbol != (symrec *)0; result_symbol = (symrec *)result_symbol->next)
    if (strcmp (result_symbol->name, symbolName) == 0)
      {
        return result_symbol;
      }
  return 0;
}

/*************************************************************
 *       Operations over the local ST		     *
 *************************************************************/

/* Insert a new symbol into the local symbol table*/
localVariables * newLocalSymbol (char *varName, char *cs, char *proc_name)
{
  localVariables *new_symbol;
  new_symbol = (localVariables *) malloc (sizeof(localVariables));
  new_symbol->name = (char *) malloc (strlen(varName));
  strcpy (new_symbol->name, varName);
  new_symbol->offset = location(lvars_offset);
  new_symbol->cs = (char *) malloc (strlen(cs));
  strcpy (new_symbol->cs, cs);
  new_symbol->proc_name = (char *) malloc (strlen(proc_name));
  strcpy (new_symbol->proc_name, proc_name);
  new_symbol->next = (struct localVariables *) lvars_table;
  lvars_table = new_symbol;
  return new_symbol;
}


/* Return a Local Symbol*/
localVariables * getLocalSymbol (char *symbolName)
{
  localVariables *result_symbol;
  for(result_symbol = lvars_table; result_symbol != (localVariables *)0; result_symbol = (localVariables *)result_symbol->next)
    if (strcmp (result_symbol->name, symbolName) == 0)
      {
        return result_symbol;
      }
  return 0;
}



/*************************************************************
 *       Functions used in order to print the variables	     *
 *************************************************************/

/* Print the variables of the simulation, with their respectives domains*/
void printVars(FILE *file)
{
  symrec *symbolTable;  
  fprintf (file,"Lvars = [");
  for(symbolTable= sym_table; symbolTable != (symrec *)0; symbolTable = (symrec *)symbolTable->next)
    {
      if(strcmp (symbolTable->cs,"wcs") != 0)
        {
          //fprintf (file,"%s#%s\n",symbolTable->name,symbolTable->cs);
		fprintf (file,"%s\n",symbolTable->name);  
        }
    }  
  fprintf (file,"]\n");
  fprintf (file,"Vars = {MakeRecord var Lvars} \n");

  }


/* Print the domain of each variable of the simulation*/
void printVarsDomains(FILE *file)
{
  symrec *symbolTable;  

  for(symbolTable= sym_table; symbolTable != (symrec *)0; symbolTable = (symrec *)symbolTable->next)
    {
      if(strcmp (symbolTable->cs,"wcs") != 0)
        {
           fprintf (file,"%s::%i#%i\n",symbolTable->name,symbolTable->domain.domainInfI, symbolTable->domain.domainSupI); 
          // printf ("%s::%i#%i\n",symbolTable->name,symbolTable->domain.domainInfI, symbolTable->domain.domainSupI); 
        }
    }
}

/* Print the general domain of the variables of the simulation*/
//void printAllVarsDomain(FILE *file,int inf, int sup)
void printAllVarsDomain(FILE *file,struct domain domainSymbol, int isInteger )
{
	if (isInteger == 1)  
	{
		fprintf(file,"Vars:::%i#%i\n",domainSymbol.domainInfI,domainSymbol.domainSupI);
	}else
	{
		fprintf(file,"Vars:::%f#%f\n",domainSymbol.domainInfR,domainSymbol.domainInfR);
	}

}




/*************************************************************
 *       End symbol table                                    *
 *************************************************************/
