/*************************************************************
 *       Stack Machine                                       *
 *************************************************************/



/*************************************************************
 *       Representation of the operators                     *
 *************************************************************/

/* Representation of the ntcc operators (Internal representation)*/
enum operators_code {TELLR, WHENR, REPR, PARR, SUMR, UNLESSR,
                     NEXTR, NEXTUPNR, STARR, BOUNDEDREPR,
                     BOUNDEDSTARR, WHENEVERR, ABORTR, SKIPR, LOCALR, ENDR, RPARR, PNAME, INVOC};

/* External Representation */
char *operators_name[] = {"tell", "when", "rep", "par", "sum", "unless",
                          "next", "nextupn", "star", "boundedrep",
                          "boundedstar", "whenever", "abort", "skip", "localr", "end", "rpar", "pname", "invoc"}; 


/* Representation of the ntcc constraints operators (Internal representation)*/
enum type_internal {INTR,DOUBLE,CHAR,ENDC,ENDCC,SYMBOLR};

/* External Representation */
char *type_external[]={"int","double","char","end","endc","symbol"};


/*************************************************************
 *       Structures                                          *
 *************************************************************/

/*Structure of a constraint systems*/
struct constSystems
{
  char *cs;
};

/*Structure of a process*/
struct process
{
  enum operators_code oc;
  char *c_arg;
  int dp_arg[2];
};


/*Structure of a constraint*/
struct constraint
{
  enum type_internal type; 
  char *value;
  int intValue;
  double doubleValue; 
  char *proc_name;
  char *cs;
  int local_var;
};

/*Structure of an invocation*/
struct invocation
{
  int type; // type 1: process_name, type 0: parameter, type 2: end
  char *name;
  char *cs;   // if type is a process_name cs="wcs" without constraint system 
  char *proc_name;
  enum operators_code oc;
  char *c_arg;
  int dp_arg[2]; 
};






/*************************************************************
 *       Instances                                           *
 *************************************************************/


/*Array with the constraints*/
struct constraint program_constraints[999];

/*Array with the processes*/
struct process processes_code[999];

/*Array with the constraint systems*/
struct constSystems constraintSystems[999];

/* Array with the process invocations*/
struct invocation processes_invocations[999];



/*Instances*/
struct process inst;
struct constSystems constSyst;
struct constraint constraint_var;
struct invocation instance_process_invocation;


/*************************************************************
 *       Variable definitions                                *
 *************************************************************/

/*Iterators*/

int count = 0;
int cs_count = 0;
int const_count = 0;
int iterator_process_invocation = 0;



/*Another variables*/


int local_variable = 0;
int new_iterator_constraint = 0;
char *current_proc_name = "";

/*************************************************************
 *       Functions                                           *
 *************************************************************/


/* Function used in order to change a local name*/

void change_local_name(char *new_name, char *old_name, char *proc_name)
{
  struct constraint temporal_constraint_var;

  do{
    temporal_constraint_var = program_constraints[new_iterator_constraint];  
    new_iterator_constraint++;
	if(temporal_constraint_var.type==CHAR)
      {     
   
        if(strcmp(temporal_constraint_var.value,old_name)==0)
          {
	           program_constraints[new_iterator_constraint-1].value = new_name;
          }
      }
 
  }while(temporal_constraint_var.type != ENDCC);
}

/* Function used in order to generate the local variables  */



void generate_local_variables(FILE *file)
{
  localVariables *result;
  fprintf(file,"parms(");
  for(result = lvars_table; result != (localVariables *)0; result = (localVariables *) result->next)
    {
      if (strcmp (result->proc_name, current_proc_name) == 0)
      {
         char *tmpVar = (char *)malloc(512);
        strcat(tmpVar,"LV__");
        strcat (tmpVar,result->name);                      
        fprintf(file," %s",tmpVar);
        change_local_name(tmpVar,result->name, result->proc_name);

      }
       
    }
  fprintf(file,")");
}


/*Generate variables*/
void generate_variables(FILE *file)
{
    vardefinition *result,*last;
    fprintf(file,"parms(");

    last = NULL;
    while (vardef_table != last)
    {
    	result = vardef_table;

    	 while (result-> next != last)
  	{
  		result= result -> next;
  	}    	 	 		
	if (strcmp (result->proc_name, current_proc_name) == 0)
	{                            
		fprintf(file," %s",result->name);   
	}	
  	last = result;
    }		
		
     fprintf(file,")");
  /*for(result = vardef_table; result != (vardefinition *)0; result = (vardefinition *) result->next)
    {
      if (strcmp (result->proc_name, current_proc_name) == 0)
      {                            
        fprintf(file," %s",result->name);   
      }
       
     }*/
  			
}



/* Constraint code generation*/

void generate_process_constraint(FILE *file)
{  
    char * label = "current";
  int xriVar = 0;
  do{ 
    constraint_var = program_constraints[const_count];
    const_count++;

    switch(constraint_var.type)
      {
      case CHAR :  
        if((strcmp (constraint_var.cs,"fd") == 0)&&local_variable==0)
          { 
            xriVar=0;
            fprintf (file,"Root.%s.%s ", label ,constraint_var.value); break;             
          }else if((strcmp (constraint_var.cs,"fd") == 0)&&local_variable==1)
          {
            xriVar=0;
            fprintf (file,"{Nth Root.%s.list  %s}", label, constraint_var.value); break;  
          }else if((strcmp (constraint_var.cs,"xri") == 0)&&local_variable==0)
          {
            xriVar=1;
            fprintf (file,"Root.%s.%s ", label, constraint_var.value); break;  
          }else if((strcmp (constraint_var.cs,"xri") == 0)&&local_variable==1)
          {
            xriVar=1;
            fprintf (file,"{Nth Root.%s.list %s} ", label, constraint_var.value); break;  
          }else
          {
            fprintf (file,"%s ", constraint_var.value); break; 
          } 


      case SYMBOLR :        
	label="residual";	        
        if(xriVar==1)
          {
            fprintf (file,"%s ", constraint_var.value); break;      
          }else
          {
            if(constraint_var.intValue == 1)
              {
                fprintf(file,"%s ", constraint_var.value); break;
              }else
              {
                fprintf(file,"%s: ", constraint_var.value); break;

              }
		
          } 
        
      case DOUBLE :         
        fprintf (file,"%f ", constraint_var.doubleValue); break;
           
      case INTR :
        fprintf (file,"%i ", constraint_var.intValue); break;
      }
	
	fprintf(file," ");       
  }
  while(constraint_var.type != ENDC);
  
}



 /* Generate code for invocations */

void generate_invocation_call(FILE *file, int call_in_proc)
{
  do{
    instance_process_invocation = processes_invocations[iterator_process_invocation];
    iterator_process_invocation++;		
    
    switch(instance_process_invocation.type)
      {
      case 1: 
        fprintf (file,"{%s parms(", instance_process_invocation.name); 
        break;
      case 0:
        fprintf (file," %s", instance_process_invocation.name);		
        break;
      case 2: fprintf (file, ")} ");
        
        instance_process_invocation.type=3;
        break; 
      }
	
  }while(instance_process_invocation.type != 3);  
  instance_process_invocation.type=2;	  
}



/* Generate process code*/

void generate_process(FILE *file)
{          
  int local_iterator = 0;
  do 
    {

      inst = processes_code[count]; 
      count++;
      switch(inst.oc)
        {
        case TELLR :     

          fprintf (file," tell(proc{$ Root} ");           
          generate_process_constraint(file);
          fprintf (file," end)\n");     
     
          break;

        case WHENR : 
          // fprintf (file," when(proc{$ Root} %s end \n", inst.c_arg); break;
          fprintf (file," when(proc{$ Root} ");
          generate_process_constraint(file);   
          fprintf (file," end\n");       
          break;


        case PARR :               
          fprintf (file,"par( \n"); break;
          
        case LOCALR :
          local_variable = 1;
          local_iterator++;
          fprintf (file," localvar(fun{$ "); 
          generate_local_variables(file);
  
          fprintf (file,"}");
          break;
         
        case NEXTR : 
          fprintf (file," next(\n");  break;

        case UNLESSR :
          //fprintf (file,"unless(proc{$ Root} %s end \n",inst.c_arg);  break;
          fprintf (file," unless(proc{$ Root} ");
          generate_process_constraint(file);   
          fprintf (file," end\n");
          break;

        case STARR :
          fprintf (file," star(\n");  break;
          
        case REPR :
          fprintf (file," rep(\n");  break;          
          
        case SKIPR :
          fprintf (file," skip\n"); break;
         
        case ABORTR :
          fprintf(file," abort \n"); break;          

        case SUMR : 
          fprintf (file," sum( \n");   break;          
          
        case NEXTUPNR :
          fprintf (file," nextupn( %i", inst.dp_arg[0]);   break;

        case BOUNDEDREPR :
          fprintf (file," boundedrep(%i %i",inst.dp_arg[0], inst.dp_arg[1]);  break;

        case BOUNDEDSTARR :
          fprintf (file," boundedstar(%i %i",inst.dp_arg[0], inst.dp_arg[1]); break;        
          
        case WHENEVERR : 
          //  fprintf(file,"whenever(proc{$ Root} %s end",inst.c_arg);  break;        
          fprintf (file," whenever(proc{$ Root} ");
          generate_process_constraint(file);   
          fprintf (file," end\n");
          break;
          
        case RPARR :        
          if(inst.dp_arg[0]==1)
            {            
              if(inst.dp_arg[1]==1)
                local_variable=0;

              fprintf (file,"end)  \n"); break;
            }else if(inst.dp_arg[1]==1)
            {
              local_variable = 0;
              fprintf (file,"end  \n"); break;
            }else
            {           
              fprintf (file,") \n"); break;
            }
          
        case INVOC :
          generate_invocation_call(file, 1);
          break;
          
        case PNAME :        
          fprintf (file,"%s = ",inst.c_arg);
          current_proc_name = inst.c_arg;
          fprintf(file, "fun{$ ");
          generate_variables(file); 
          fprintf(file,"}\n");	
          break;
          // default : printf ("sie -> \n"); printf( "%sInternal Error: Something is wrong\n"); break;
        }
    }
  while(inst.oc != ENDR);
}

 /* Generate code for invocations */

void generate_invocation(FILE *file, int call_in_proc)
{
	if(call_in_proc==0)	
		fprintf(file,"System = par(");	
	do{
		instance_process_invocation = processes_invocations[iterator_process_invocation];
		iterator_process_invocation++;		

		switch(instance_process_invocation.type)
      		{
      			case 1: 
				fprintf (file,"{%s parms(", instance_process_invocation.name); 
				break;
			case 0:
				fprintf (file," %s", instance_process_invocation.name);		
				break;
			case 2: fprintf (file, ")} ");
				if(call_in_proc==1)
					instance_process_invocation.type=3;
				break; 
		}
		
	}
	while(instance_process_invocation.type != 3);
	
	if(call_in_proc==0)
	{
		inst = processes_code[count]; 
		if(inst.oc != ENDR)
		{		
			printf("llamado");
	        	generate_process(file);			
		}
		fprintf(file,")\n");  
	}else
	{
		instance_process_invocation.type=2;	
	}
}


/* Generate the simulation time*/
void generate_simulation_time(FILE *file,int time)
{
  int prueba = time;
  fprintf (file,"SimulationTime = %i \n",prueba);
}

/* Generate the constraint systems (list) used in the simulation*/
void generate_constSystems(FILE *file)
{
  fprintf (file,"ConstraintSystems = [");
  do{
    constSyst = constraintSystems[cs_count];
    cs_count++;
    if(constSyst.cs != "end")
      {
        fprintf (file,"%s \n",constSyst.cs);
      }        
  }
  while(constSyst.cs != "end");

  fprintf (file,"]\n");
}


/*************************************************************
 * 	begin head/tail of file 				     *
 *************************************************************/

   void printHead(FILE *file)
   {
     //fprintf (file,"local \n [SNTCC] = {Module.link ['ntcc_interpreter.ozf']} \n Answer \n ");
     fprintf (file,"functor \n import \n NtccInterpreter \n export \n define \n ");
   }
   
void printTail(FILE *file, char * fileName )
   {
     fprintf (file, " \n {NtccInterpreter.simulate [System] \nVars \n SimulationTime \n '%s' } \n end \n",fileName);
   }
   


/*************************************************************
 *       End Stack Machine                                       *
 *************************************************************/
