/*************************************************************
 *       Code generator                                      *
 *************************************************************/

/*************************************************************
 *       Functions used in order to generate code	     *
 *************************************************************/


/* Variables definition*/
int code_offset = 0; /* Initial offset*/
int counter = 0;
int constraint_counter = 0;
int invocation_counter = 0;

/* Generates code for basic processes (definitions)*/
void generate_code( enum operators_code operation)
{ 
  processes_code[code_offset].oc = operation;
  code_offset++;
}

/* Generates code for derived processes (dp -- definitions) */
void generate_code_dp( enum operators_code operation,char *c_arg,  int arg_dp1, int arg_dp2)
{
  processes_code[code_offset].oc = operation;
  processes_code[code_offset].c_arg = c_arg;
  processes_code[code_offset].dp_arg[0] = arg_dp1;
  processes_code[code_offset].dp_arg[1] = arg_dp2;
  code_offset++;
}

/* Generates code for the constraint system*/
void generate_cs(char *var_cs)
{
  constraintSystems[counter].cs = var_cs;
  counter++;
}

/* Generates code for the constraints (definitions)*/
void generate_constraint(enum type_internal type, char *value, int intValue, double doubleValue, char *proc_name)
{
  program_constraints[constraint_counter].type = type;
  program_constraints[constraint_counter].value = value;
  program_constraints[constraint_counter].intValue = intValue;
  program_constraints[constraint_counter].doubleValue = doubleValue;
  program_constraints[constraint_counter].proc_name = proc_name;
  constraint_counter++; 
}

/* Generates code for the constraints using a name (definitions)*/
void generate_constraint_name(enum type_internal type, char *value, int intValue, double doubleValue, char *proc_name, char *cs, int local)
{
  program_constraints[constraint_counter].type = type;
  program_constraints[constraint_counter].value = value;
  program_constraints[constraint_counter].intValue = intValue;
  program_constraints[constraint_counter].doubleValue = doubleValue;
  program_constraints[constraint_counter].proc_name = proc_name;
  program_constraints[constraint_counter].cs = cs;
  program_constraints[constraint_counter].local_var = local;
  constraint_counter++; 
}

/* Generates code for the processes invocation*/
void generate_process_invocation(int type, char *name, char *cs, char *proc_name)
{
  processes_invocations[invocation_counter].type = type;
  processes_invocations[invocation_counter].name = name;
  processes_invocations[invocation_counter].cs = cs;
  processes_invocations[invocation_counter].proc_name = proc_name;
  invocation_counter++;
}

/*************************************************************
 *       End Code generator                                  *
 *************************************************************/

