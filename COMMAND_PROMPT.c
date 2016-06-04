/*
  ------------------------------------------------------------------------------------------------------------------------------------------
  ExcelMicroTechnologies - emtech
  Copyright 2013-2014
  ------------------------------------------------------------------------------------------------------------------------------------------
*/
/*
  ------------------------------------------------------------------------------------------------------------------------------------------
  Project       : Sparc_V8 Emulator
  File          : COMMAND_PROMPT.c
  Description   : Command Prompt manage SPARCV8 EMULATOR Process
  Author        : Monahopoulos Konstantinos
  ------------------------------------------------------------------------------------------------------------------------------------------
*/
/*
  ----------------------------------------------------------------------------------------------------------------------------------------
  Includes
  ----------------------------------------------------------------------------------------------------------------------------------------
*/

#include "COMMAND_PROMPT.h"
#include "EMU_MEMORY.h"
#include "SPARCV8_EMULATOR_CORE.h"
#include "SPARCV8_INSTRUCTION_SET.h"
#include "SPARCV8_PROC.h"
#include "SPARCV8_TRAPS.h"
#include "HELPER.h"
#include "THREADS.h"

#define FILE_PROGRAM_1 "D:\\EMTECH\\EMULATOR PROGRAMMS\\MySparcEmulator\\HLLSPARCPRG\\instructions.exe"

void command_prompt_terminal_initialize(struct COMMAND_PROMT_TERMINAL *command_prompt_terminal_tmp_ptr)
{
    /*COMMAND PROMPT RECOGNITION VALUES*/

    command_prompt_terminal_tmp_ptr->token_delims=" \r\n\t"; /* RECOGNITION OF THESE SYMBOLS IN THE STRING */
    command_prompt_terminal_tmp_ptr->endptr=NULL;
    command_prompt_terminal_tmp_ptr->token=NULL;
    command_prompt_terminal_tmp_ptr->value_from_stdin[0]=0;
    command_prompt_terminal_tmp_ptr->value_from_stdin[1]=0;
    command_prompt_terminal_tmp_ptr->counter=0;

    /*   FUNCTION POINTER INITIALIZATION   */

    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[0] = (void* (*) (void*,void*,void*) )command_prompt_initialize;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[1] = (void* (*) (void*,void*,void*) )command_prompt_halt;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[2] = (void* (*) (void*,void*,void*) )command_prompt_reset;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[3] = (void* (*) (void*,void*,void*) )command_prompt_help;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[4] = (void* (*) (void*,void*,void*) )command_prompt_free_run;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[5] = (void* (*) (void*,void*,void*) )command_prompt_step;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[6] = (void* (*) (void*,void*,void*) )command_prompt_exit;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[7] = (void* (*) (void*,void*,void*) )command_prompt_kill;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[8] = (void* (*) (void*,void*,void*) )command_prompt_status;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[9] = (void* (*) (void*,void*,void*) )command_prompt_read_data_memory;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[10] = (void* (*) (void*,void*,void*) )command_prompt_read_data_memory_for;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[11] = (void* (*) (void*,void*,void*) )command_prompt_read_stack_memory;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[12] = (void* (*) (void*,void*,void*) )command_prompt_read_stack_memory_for;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[13] = (void* (*) (void*,void*,void*) )command_prompt_write_data_memory;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[14] = (void* (*) (void*,void*,void*) )command_prompt_write_data_memory_for;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[15] = (void* (*) (void*,void*,void*) )command_prompt_write_stack_memory;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[16] = (void* (*) (void*,void*,void*) )command_prompt_write_stack_memory_for;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[17] = (void* (*) (void*,void*,void*) )command_prompt_register;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[18] = (void* (*) (void*,void*,void*) )command_prompt_read_all;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[19] = (void* (*) (void*,void*,void*) )command_prompt_read_windowd;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[20] = (void* (*) (void*,void*,void*) )command_prompt_read_psr;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[21] = (void* (*) (void*,void*,void*) )command_prompt_read_wim;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[22] = (void* (*) (void*,void*,void*) )command_prompt_read_tbr;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[23] = (void* (*) (void*,void*,void*) )command_prompt_read_y;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[24] = (void* (*) (void*,void*,void*) )command_prompt_read_pc;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[25] = (void* (*) (void*,void*,void*) )command_prompt_read_npc;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[26] = (void* (*) (void*,void*,void*) )command_prompt_read_asr;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[27] = (void* (*) (void*,void*,void*) )command_prompt_read_fsr;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[28] = (void* (*) (void*,void*,void*) )command_prompt_read_csr;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[29] = (void* (*) (void*,void*,void*) )command_prompt_read_fpreg;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[30] = (void* (*) (void*,void*,void*) )command_prompt_read_coreg;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[31] = (void* (*) (void*,void*,void*) )command_prompt_write_psr;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[32] = (void* (*) (void*,void*,void*) )command_prompt_write_tbr;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[33] = (void* (*) (void*,void*,void*) )command_prompt_write_y;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[34] = (void* (*) (void*,void*,void*) )command_prompt_write_pc;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[35] = (void* (*) (void*,void*,void*) )command_prompt_write_npc;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[36] = (void* (*) (void*,void*,void*) )command_prompt_write_asr;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[37] = (void* (*) (void*,void*,void*) )command_prompt_write_fsr;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[38] = (void* (*) (void*,void*,void*) )command_prompt_write_csr;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[39] = (void* (*) (void*,void*,void*) )command_prompt_clear_terminal;

    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[40] = (void* (*) (void*,void*,void*) )command_prompt_read_program_memory;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[41] = (void* (*) (void*,void*,void*) )command_prompt_read_program_memory_for;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[42] = (void* (*) (void*,void*,void*) )command_prompt_write_program_memory;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[43] = (void* (*) (void*,void*,void*) )command_prompt_write_program_memory_for;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[44] = (void* (*) (void*,void*,void*) )command_prompt_load_program_mean_value;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[45] = (void* (*) (void*,void*,void*) )command_prompt_write_to_general_regs;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[46] = (void* (*) (void*,void*,void*) )command_prompt_time;
    command_prompt_terminal_tmp_ptr->command_prompt_fnc_array[47] = (void* (*) (void*,void*,void*) )command_prompt_load_program_from_file;
    command_prompt_terminal_ptr = command_prompt_terminal_tmp_ptr;

    return;
}


DWORD WINAPI command_prompt(LPVOID thread_info_ptr)
{
    printf("Copyright (C) 2016 Monahopoulos Konstantinos\n"
           "Project       : Sparc V8 Emulator\n"
           "Description   : Spacecraft Multicore Emulator Based on Leon 3 Sparc V8 architecture processor\n"
           "Author        : Monahopoulos Konstantinos\n");
    while(1)
    {

        printf("\n\nSPARCV8 EMULATOR> ");
        fgets (command_prompt_terminal_ptr->cmd_std_input,MAX_COMMAND_SIZE,stdin);

        command_prompt_match_and_execute_command(command_prompt_terminal_ptr->cmd_std_input);
        if (((struct THREAD_INFO_context*) thread_info_ptr)->thread_exit == TRUE)
        {
            break;
        }
    }
    return 0;
}


/* ====>  RECOGNIZE AND CALL FUNCTION THROUGH FUNCTION POINTER  <==== */

void command_prompt_match_and_execute_command(char* stdin_command)
{
    command_prompt_terminal_ptr->token = strtok(stdin_command,command_prompt_terminal_ptr->token_delims);

    if ( command_prompt_terminal_ptr->token == NULL )
    {
        /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
        printf("NO COMMAND SPECIFIED\n");
    }
    else if ( strcmp(command_prompt_terminal_ptr->token, "INITIALIZE") == FALSE )
    {
        /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
        ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[0] ) (NULL,NULL,NULL);
    }
    else if ( strcmp(command_prompt_terminal_ptr->token, "HALT") == FALSE )
    {
        /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
        ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[1] ) (NULL,NULL,NULL);
    }
    else if ( strcmp(command_prompt_terminal_ptr->token, "RESET") == FALSE )
    {
        /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
        ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[2] ) (NULL,NULL,NULL);
    }
    else if ( strcmp(command_prompt_terminal_ptr->token, "HELP") == FALSE )
    {
        /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
        ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[3] ) (NULL,NULL,NULL);
    }
    else if ( strcmp(command_prompt_terminal_ptr->token, "FREERUN") == FALSE )
    {
        /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
        ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[4] ) (NULL,NULL,NULL);
    }
    else if ( strcmp(command_prompt_terminal_ptr->token, "STEP") == FALSE )
    {
        /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
        ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[5] ) (NULL,NULL,NULL);
    }
    else if ( strcmp(command_prompt_terminal_ptr->token, "EXIT") == FALSE )
    {
        /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
        ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[6] ) (NULL,NULL,NULL);
    }
    else if ( strcmp(command_prompt_terminal_ptr->token, "KILL") == FALSE )
    {
        /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
        ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[7] ) (NULL,NULL,NULL);
    }
    else if ( strcmp(command_prompt_terminal_ptr->token, "STATUS") == FALSE )
    {
        //CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION
        ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[8] ) (NULL,NULL,NULL);
    }

    else if ( strcmp(command_prompt_terminal_ptr->token, "READ") == FALSE )
    {
        command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
        if(strcmp(command_prompt_terminal_ptr->token, "DATA") == FALSE)
        {
            command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
            if (strcmp(command_prompt_terminal_ptr->token,"MEMORY")==FALSE)
            {
                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                command_prompt_terminal_ptr->value_from_stdin[0] = strtol(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 16) ;

                if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                {
                    printf("READ DATA MEMORY [X] OPERAND SHOULD BE A HEX INTEGER\n");
                }
                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);

                if ( command_prompt_terminal_ptr->token == NULL )
                {
                    /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                    ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[9] ) ((void*)command_prompt_terminal_ptr->value_from_stdin[0],NULL,NULL); //READ DATA MEMORY %HEX

                }
                else if (strcmp(command_prompt_terminal_ptr->token,"FOR")==FALSE)
                {
                    command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                    command_prompt_terminal_ptr->value_from_stdin[1] = strtol(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 10) ;
                    if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                    {
                        printf("READ DATA MEMORY [X] OPERAND SHOULD BE A HEX, FOR [X] OPERAND SHOULD BE A DEC\n");
                    }
                    /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                    ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[10] ) ((void*)command_prompt_terminal_ptr->value_from_stdin[0],(void*)command_prompt_terminal_ptr->value_from_stdin[1],NULL); //READ MEMORY ADDRESS %HEX FOR %DEC
                }
                else
                {
                    printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
                }

            }
            else
            {
                printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
            }
        }

        else if(strcmp(command_prompt_terminal_ptr->token, "STACK") == FALSE)
        {
            command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
            if (strcmp(command_prompt_terminal_ptr->token,"MEMORY")==FALSE)
            {
                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                command_prompt_terminal_ptr->value_from_stdin[0] = strtol(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 16) ;

                if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                {
                    printf("READ STACK MEMORY [X] OPERAND SHOULD BE A HEX INTEGER\n");
                }
                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);

                if ( command_prompt_terminal_ptr->token == NULL )
                {
                    /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                    ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[11] ) ((void*)command_prompt_terminal_ptr->value_from_stdin[0],NULL,NULL);  //READ STACK MEMORY %HEX
                }
                else if (strcmp(command_prompt_terminal_ptr->token,"FOR")==FALSE)
                {
                    command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                    command_prompt_terminal_ptr->value_from_stdin[1] = strtol(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 10) ;
                    if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                    {
                        printf("READ STACK MEMORY [X] OPERAND SHOULD BE A HEX, FOR [X] OPERAND SHOULD BE A DEC\n");
                    }

                    /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                    ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[12] ) ((void*)command_prompt_terminal_ptr->value_from_stdin[0],(void*)command_prompt_terminal_ptr->value_from_stdin[1],NULL); //READ STACK ADDRESS HEX% FOR %DEC
                }
                else
                {
                    printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
                }

            }
            else
            {
                printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
            }
        }
        else if(strcmp(command_prompt_terminal_ptr->token, "PROGRAM") == FALSE)
        {
            command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
            if (strcmp(command_prompt_terminal_ptr->token,"MEMORY")==FALSE)
            {
                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                command_prompt_terminal_ptr->value_from_stdin[0] = strtol(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 16) ;

                if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                {
                    printf("READ PROGRAM MEMORY [X] OPERAND SHOULD BE A HEX INTEGER\n");
                }
                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);

                if ( command_prompt_terminal_ptr->token == NULL )
                {
                    /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                    ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[40] ) ((void*)command_prompt_terminal_ptr->value_from_stdin[0],NULL,NULL);  //READ PROGRAM MEMORY %HEX
                }
                else if (strcmp(command_prompt_terminal_ptr->token,"FOR")==FALSE)
                {
                    command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                    command_prompt_terminal_ptr->value_from_stdin[1] = strtol(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 10) ;
                    if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                    {
                        printf("READ PROGRAM MEMORY [X] OPERAND SHOULD BE A HEX, FOR [X] OPERAND SHOULD BE A DEC\n");
                    }

                    /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                    ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[41] ) ((void*)command_prompt_terminal_ptr->value_from_stdin[0],(void*)command_prompt_terminal_ptr->value_from_stdin[1],NULL); //READ PROGRAM ADDRESS HEX% FOR %DEC
                }
                else
                {
                    printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
                }

            }
            else
            {
                printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
            }
        }
        else
        {
            printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
        }

    }

    else if ( strcmp(command_prompt_terminal_ptr->token, "WRITE") == FALSE )
    {
        command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
        if(strcmp(command_prompt_terminal_ptr->token, "DATA") == FALSE)
        {
            command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
            if (strcmp(command_prompt_terminal_ptr->token,"MEMORY")==FALSE)
            {
                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                command_prompt_terminal_ptr->value_from_stdin[0] = strtol(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 16) ;

                if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                {
                    printf("WRITE DATA MEMORY [X] OPERAND SHOULD BE A HEX INTEGER\n");
                }
                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                if (strcmp(command_prompt_terminal_ptr->token,"VALUE")==FALSE)
                {
                    command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                    command_prompt_terminal_ptr->value_from_stdin[1] = strtoul(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 16) ;

                    /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                    ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[13] ) ((void*)command_prompt_terminal_ptr->value_from_stdin[0],(void*)command_prompt_terminal_ptr->value_from_stdin[1],NULL); //WRITE MEMORY ADDRESS %HEX  VALUE %HEX

                }
                else if (strcmp(command_prompt_terminal_ptr->token,"FOR")==FALSE)
                {
                    command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                    command_prompt_terminal_ptr->value_from_stdin[1] = strtol(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 10) ;

                    if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                    {
                        printf("WRITE DATA MEMORY FOR [X] OPERAND SHOULD BE A DEC INTEGER\n");
                    }
                    command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);

                    if (strcmp(command_prompt_terminal_ptr->token,"VALUE")==FALSE)
                    {
                        command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                        command_prompt_terminal_ptr->value_from_stdin[2] = strtoul(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 16) ;

                        if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                        {
                            printf("WRITE DATA MEMORY FOR VALUE [X] OPERAND SHOULD BE A HEX INTEGER\n");
                        }
                        /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                        ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[14] ) ((void*)command_prompt_terminal_ptr->value_from_stdin[0],(void*)command_prompt_terminal_ptr->value_from_stdin[1],(void*)command_prompt_terminal_ptr->value_from_stdin[2]); //WRITE MEMORY ADDRESS %HEX FOR %DEC

                    }
                    else
                    {
                        printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
                    }
                }
                else
                {
                    printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
                }
            }
            else
            {
                printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
            }
        }
        else if(strcmp(command_prompt_terminal_ptr->token, "STACK") == FALSE)
        {
            command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
            if (strcmp(command_prompt_terminal_ptr->token,"MEMORY")==FALSE)
            {
                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                command_prompt_terminal_ptr->value_from_stdin[0] = strtol(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 16) ;

                if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                {
                    printf("WRITE STACK MEMORY [X] OPERAND SHOULD BE A HEX INTEGER");
                }
                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                if (strcmp(command_prompt_terminal_ptr->token,"VALUE")==FALSE)
                {
                    command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                    command_prompt_terminal_ptr->value_from_stdin[1] = strtoul(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 16) ;
                    /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                    ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[15] ) ((void*)command_prompt_terminal_ptr->value_from_stdin[0],(void*)command_prompt_terminal_ptr->value_from_stdin[1],NULL); //WRITE MEMORY ADDRESS %HEX  VALUE %HEX
                }
                else if (strcmp(command_prompt_terminal_ptr->token,"FOR")==FALSE)
                {
                    command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                    command_prompt_terminal_ptr->value_from_stdin[1] = strtol(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 10) ;

                    if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                    {
                        printf("WRITE STACK MEMORY FOR [X] OPERAND SHOULD BE A DEC INTEGER");
                    }
                    command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);

                    if (strcmp(command_prompt_terminal_ptr->token,"VALUE")==FALSE)
                    {
                        command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                        command_prompt_terminal_ptr->value_from_stdin[2] = strtoul(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 16) ;

                        if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                        {
                            printf("WRITE STACK MEMORY FOR VALUE [X] OPERAND SHOULD BE A HEX INTEGER");
                        }
                        /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                        ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[16] ) ((void*)command_prompt_terminal_ptr->value_from_stdin[0],(void*)command_prompt_terminal_ptr->value_from_stdin[1],(void*)command_prompt_terminal_ptr->value_from_stdin[2]); //WRITE MEMORY ADDRESS %HEX FOR %DEC
                    }
                }

                else
                {
                    printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
                }
            }
            else
            {
                printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
            }
        }

        else if(strcmp(command_prompt_terminal_ptr->token, "PROGRAM") == FALSE)
        {
            command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
            if (strcmp(command_prompt_terminal_ptr->token,"MEMORY")==FALSE)
            {
                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                command_prompt_terminal_ptr->value_from_stdin[0] = strtol(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 16) ;

                if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                {
                    printf("WRITE PROGRAM MEMORY [X] OPERAND SHOULD BE A HEX INTEGER");
                }
                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                if (strcmp(command_prompt_terminal_ptr->token,"VALUE")==FALSE)
                {
                    command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                    command_prompt_terminal_ptr->value_from_stdin[1] = strtoul(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 16) ;
                    /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                    ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[42] ) ((void*)command_prompt_terminal_ptr->value_from_stdin[0],(void*)command_prompt_terminal_ptr->value_from_stdin[1],NULL); //WRITE PROGRAM MEMORY %HEX  VALUE %HEX
                }
                else if (strcmp(command_prompt_terminal_ptr->token,"FOR")==FALSE)
                {
                    command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                    command_prompt_terminal_ptr->value_from_stdin[1] = strtol(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 10) ;

                    if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                    {
                        printf("WRITE PROGRAM MEMORY FOR [X] OPERAND SHOULD BE A DEC INTEGER");
                    }
                    command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);

                    if (strcmp(command_prompt_terminal_ptr->token,"VALUE")==FALSE)
                    {
                        command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                        command_prompt_terminal_ptr->value_from_stdin[2] = strtoul(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 16) ;

                        if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                        {
                            printf("WRITE PROGRAM MEMORY FOR VALUE [X] OPERAND SHOULD BE A HEX INTEGER");
                        }
                        /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                        ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[43] ) ((void*)command_prompt_terminal_ptr->value_from_stdin[0],(void*)command_prompt_terminal_ptr->value_from_stdin[1],(void*)command_prompt_terminal_ptr->value_from_stdin[2]); //WRITE PROGRAM MEMORY %HEX FOR %DEC
                    }
                }

                else
                {
                    printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
                }
            }
            else
            {
                printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
            }
        }

        else
        {
            printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
        }
    }

    else if ( strcmp(command_prompt_terminal_ptr->token, "REGISTER") == FALSE )
    {
        command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
        if ( command_prompt_terminal_ptr->token == NULL )
        {
            /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
            ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[17] ) (NULL,NULL,NULL);
        }
        else if(strcmp(command_prompt_terminal_ptr->token,"-R")==FALSE)
        {

            command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
            if(strcmp(command_prompt_terminal_ptr->token,"ALL")==FALSE)
            {
                /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[18] ) (NULL,NULL,NULL);
            }
            else    if(strcmp(command_prompt_terminal_ptr->token,"WINDOWD")==FALSE)
            {
                /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[19] ) (NULL,NULL,NULL);
            }
            else   if(strcmp(command_prompt_terminal_ptr->token,"PSR")==FALSE)
            {
                /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[20] ) (NULL,NULL,NULL);
            }
            else   if(strcmp(command_prompt_terminal_ptr->token,"WIM")==FALSE)
            {
                /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[21] ) (NULL,NULL,NULL);
            }
            else   if(strcmp(command_prompt_terminal_ptr->token,"TBR")==FALSE)
            {
                /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[22] ) (NULL,NULL,NULL);
            }
            else   if(strcmp(command_prompt_terminal_ptr->token,"Y")==FALSE)
            {
                /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[23] ) (NULL,NULL,NULL);
            }
            else   if(strcmp(command_prompt_terminal_ptr->token,"PC")==FALSE)
            {
                /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[24] ) (NULL,NULL,NULL);
            }
            else   if(strcmp(command_prompt_terminal_ptr->token,"NPC")==FALSE)
            {
                /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[25] ) (NULL,NULL,NULL);
            }
            else   if(strcmp(command_prompt_terminal_ptr->token,"ASR")==FALSE)
            {
                /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[26] ) (NULL,NULL,NULL);
            }
            else   if(strcmp(command_prompt_terminal_ptr->token,"FSR")==FALSE)
            {
                /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[27] ) (NULL,NULL,NULL);
            }
            else   if(strcmp(command_prompt_terminal_ptr->token,"CSR")==FALSE)
            {
                /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[28] ) (NULL,NULL,NULL);
            }
            else   if(strcmp(command_prompt_terminal_ptr->token,"FPREG")==FALSE)
            {
                /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[29] ) (NULL,NULL,NULL);
            }
            else   if(strcmp(command_prompt_terminal_ptr->token,"COREG")==FALSE)
            {
                /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[30] ) (NULL,NULL,NULL);
            }
            else
            {
                printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
            }

        }/* END OF -R TO REGISTER*/

        else if(strcmp(command_prompt_terminal_ptr->token,"-W")==FALSE)
        {
            command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);

            if(strcmp(command_prompt_terminal_ptr->token,"PSR")==FALSE)
            {

                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                command_prompt_terminal_ptr->value_from_stdin[0] = strtol(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 16) ;
                if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                {
                    printf("WRITE REGISTER [X] OPERAND SHOULD BE A HEX INTEGER");
                }
                /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[31] ) ((void*) command_prompt_terminal_ptr->value_from_stdin[0],NULL ,NULL);
            }
            else   if(strcmp(command_prompt_terminal_ptr->token,"TBR")==FALSE)
            {

                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                command_prompt_terminal_ptr->value_from_stdin[0] = strtol(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 16) ;
                if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                {
                    printf("WRITE REGISTER [X] OPERAND SHOULD BE A HEX INTEGER");
                }
                /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[32] ) ((void*) command_prompt_terminal_ptr->value_from_stdin[0] ,NULL,NULL);
            }
            else   if(strcmp(command_prompt_terminal_ptr->token,"Y")==FALSE)
            {

                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                command_prompt_terminal_ptr->value_from_stdin[0] = strtol(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 16) ;
                if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                {
                    printf("WRITE REGISTER [X] OPERAND SHOULD BE A DEC INTEGER");
                }
                /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[33] ) ((void*) command_prompt_terminal_ptr->value_from_stdin[0] ,NULL,NULL);
            }
            else   if(strcmp(command_prompt_terminal_ptr->token,"PC")==FALSE)
            {

                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                command_prompt_terminal_ptr->value_from_stdin[0] = strtol(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 16) ;
                if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                {
                    printf("WRITE REGISTER [X] OPERAND SHOULD BE A HEX INTEGER");
                }
                /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[34] ) ((void*) command_prompt_terminal_ptr->value_from_stdin[0] ,NULL,NULL);
            }
            else   if(strcmp(command_prompt_terminal_ptr->token,"NPC")==FALSE)
            {

                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                command_prompt_terminal_ptr->value_from_stdin[0] = strtol(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 16) ;
                if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                {
                    printf("WRITE REGISTER [X] OPERAND SHOULD BE A HEX INTEGER");
                }
                /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[35] ) ((void*) command_prompt_terminal_ptr->value_from_stdin[0] ,NULL,NULL);
            }
            else   if(strcmp(command_prompt_terminal_ptr->token,"ASR")==FALSE)
            {

                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                command_prompt_terminal_ptr->value_from_stdin[0] = strtol(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 16) ;
                if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                {
                    printf("WRITE REGISTER [X] OPERAND SHOULD BE A HEX INTEGER");
                }
                /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[36] ) ((void*) command_prompt_terminal_ptr->value_from_stdin[0] ,NULL,NULL);
            }
            else  if(strcmp(command_prompt_terminal_ptr->token,"FSR")==FALSE)
            {

                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                command_prompt_terminal_ptr->value_from_stdin[0] = strtol(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 16) ;
                if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                {
                    printf("WRITE REGISTER [X] OPERAND SHOULD BE A HEX INTEGER");
                }
                /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[37] ) ((void*) command_prompt_terminal_ptr->value_from_stdin[0] ,NULL,NULL);
            }
            else   if(strcmp(command_prompt_terminal_ptr->token,"CSR")==FALSE)
            {

                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                command_prompt_terminal_ptr->value_from_stdin[0] = strtol(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 16) ;
                if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                {
                    printf("WRITE REGISTER [X] OPERAND SHOULD BE A HEX INTEGER");
                }
                /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[38] ) ((void*) command_prompt_terminal_ptr->value_from_stdin[0] ,NULL,NULL);
                return ;
            }

            else   if(strcmp(command_prompt_terminal_ptr->token,"GENERAL")==FALSE)
            {

                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                command_prompt_terminal_ptr->value_from_stdin[0] = strtol(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 10) ;
                if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                {
                    printf("WRITE REGISTER [X] OPERAND SHOULD BE A DEC INTEGER");
                }
                /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);

                if(strcmp(command_prompt_terminal_ptr->token,"VALUE")==FALSE)
                {
                    command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                    command_prompt_terminal_ptr->value_from_stdin[1] = strtoul(command_prompt_terminal_ptr->token, &command_prompt_terminal_ptr->endptr, 16) ;
                    if ( command_prompt_terminal_ptr->endptr == command_prompt_terminal_ptr->token )
                    {
                        printf("WRITE REGISTER [X] OPERAND SHOULD BE A HEX INTEGER");
                    }
                    else
                    {
                        ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[45] ) ((void*) command_prompt_terminal_ptr->value_from_stdin[0],(void*)command_prompt_terminal_ptr->value_from_stdin[1],NULL);
                    }
                }
                else
                {
                    printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
                }
                return ;
            }
            else
            {
                printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
            }
        }/* END OF -W TO REGISTER*/
        else
        {
            printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
        }
    }
    else if ( strcmp(command_prompt_terminal_ptr->token, "CLS") == FALSE )
    {
        /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
        ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[39] ) (NULL,NULL,NULL);
    }
    else if ( strcmp(command_prompt_terminal_ptr->token, "LOAD") == FALSE )
    {
        command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
        if ( strcmp(command_prompt_terminal_ptr->token, "PROGRAM") == FALSE )
        {
            command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
            if ( strcmp(command_prompt_terminal_ptr->token, "MEAN") == FALSE )
            {
                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                if ( strcmp(command_prompt_terminal_ptr->token, "VALUE") == FALSE )
                {
                    ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[44] ) (NULL,NULL,NULL);
                }
                else
                {
                    printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
                }
            }
            else if ( strcmp(command_prompt_terminal_ptr->token, "FROM") == FALSE )
            {
                command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
                if ( strcmp(command_prompt_terminal_ptr->token, "FILE") == FALSE )
                {
                    ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[47] ) (NULL,NULL,NULL);
                }
                else
                {
                    printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
                }
            }
            else
            {
                printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
            }

        }
        else
        {
            printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
        }
    }
    else if ( strcmp(command_prompt_terminal_ptr->token, "TIME") == FALSE )
    {
        command_prompt_terminal_ptr->token = strtok(NULL,command_prompt_terminal_ptr->token_delims);
        if ( command_prompt_terminal_ptr->token == NULL )
        {
            /*CALL FUNCTION POINTER FOR COMMAND PROMPT IMPLEMENTATION*/
            ( *  command_prompt_terminal_ptr->command_prompt_fnc_array[46] ) (NULL,NULL,NULL);
        }
        else
        {
            printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
        }
    }
    else
    {
        printf(" YOU HAVE MADE A SYNTAX ERROR .. \n");
    }
    return ;
}



/* ====>  DEFINE FUNCTIONS  <==== */

void command_prompt_initialize(void)
{
    /* IF YOU PRESS RESET WHILE EMULATOR IS IN FREE RUN, CHILD PROCESS MUST BE KILLED AND REBORNED AGAIN... */

    WaitForSingleObject(((struct THREAD_INFO_context*)thread_info_ptr)->ghMutex,INFINITE); /* handle to mutex  , no time-out interval   */

    /*   LOCK  */

    ((struct THREAD_INFO_context*) thread_info_ptr)->thread_suspend = TRUE;

    /*  UNLOCK  */

    ReleaseMutex(((struct THREAD_INFO_context*)thread_info_ptr)->ghMutex);

    TerminateThread(((struct THREAD_INFO_context*)thread_info_ptr)->Thread_Handles[1] , 0);


    (  (struct THREAD_INFO_context*) thread_info_ptr )->Thread_Handles[1] =  CreateThread(
                ((struct THREAD_INFO_context*) thread_info_ptr)->lpThreadAttributes, // default security attributes
                ((struct THREAD_INFO_context*) thread_info_ptr)->dwStackSize, // use default stack size
                sparcv8_emulator_core_main_loop, // thread function
                thread_info_ptr, // argument to thread function
                ((struct THREAD_INFO_context*) thread_info_ptr)->dwCreationFlags, // use default creation flags
                ((struct THREAD_INFO_context*) thread_info_ptr)->lpThreadId[1] ); // returns the thread identifier

    if (((struct THREAD_INFO_context*) thread_info_ptr)->Thread_Handles[1] == NULL)
    {
        printf("Create Child Thread() failed, error: %lu.\n", GetLastError());
    }
    sparcv8_proc_initialization(); /* STEP1 */
    sparcv8_trap_initialize(&trap_handler_table_ctx); /* STEP4 */
    sparcv8_inst_set_initialize_interface_signals(&sparcv8_inst_set_interface_signals_ctx); /* STEP5 */
    sparcv8_instruction_set_initialize_function_ptr(&sparcv8_inst_set_functions_index_ctx); /* STEP6 */
    sparcv8_emulator_core_initialize(&sparc_emulator_core_ctx);
    printf("EMULATOR INITIALIZED");
    return ;
}

void command_prompt_halt(void)
{
    if(((struct THREAD_INFO_context*) thread_info_ptr)->thread_suspend == TRUE)
    {
        printf("THE EMULATOR IS ALREADY SUSPENTED \n");
    }
    else
    {
        WaitForSingleObject(((struct THREAD_INFO_context*)thread_info_ptr)->ghMutex,INFINITE); /* handle to mutex  , no time-out interval   */

        /*   LOCK  */

        ((struct THREAD_INFO_context*) thread_info_ptr)->thread_suspend = TRUE;

        /*  UNLOCK  */

        ReleaseMutex(((struct THREAD_INFO_context*)thread_info_ptr)->ghMutex);
        printf("THE EMULATOR IS IN HALT MODE \n");
    }
    return ;
}

void command_prompt_reset(void)
{
    /* IF YOU PRESS RESET WHILE EMULATOR IS IN FREE RUN, CHILD PROCESS MUST BE KILLED AND REBORNED AGAIN... */

    WaitForSingleObject(((struct THREAD_INFO_context*)thread_info_ptr)->ghMutex,INFINITE); /* handle to mutex  , no time-out interval   */

    /*   LOCK  */

    ((struct THREAD_INFO_context*) thread_info_ptr)->thread_suspend = TRUE;

    /*  UNLOCK  */

    ReleaseMutex(((struct THREAD_INFO_context*)thread_info_ptr)->ghMutex);

    TerminateThread(((struct THREAD_INFO_context*)thread_info_ptr)->Thread_Handles[1] , 0);


    (  (struct THREAD_INFO_context*) thread_info_ptr )->Thread_Handles[1] =  CreateThread(
                ((struct THREAD_INFO_context*) thread_info_ptr)->lpThreadAttributes, // default security attributes
                ((struct THREAD_INFO_context*) thread_info_ptr)->dwStackSize, // use default stack size
                sparcv8_emulator_core_main_loop, // thread function
                thread_info_ptr, // argument to thread function
                ((struct THREAD_INFO_context*) thread_info_ptr)->dwCreationFlags, // use default creation flags
                ((struct THREAD_INFO_context*) thread_info_ptr)->lpThreadId[1] ); // returns the thread identifier

    if (((struct THREAD_INFO_context*) thread_info_ptr)->Thread_Handles[1] == NULL)
    {
        printf("Create Child Thread() failed, error: %lu.\n", GetLastError());
    }
    sparcv8_proc_initialization(); /* STEP1 */
    sparcv8_trap_initialize(&trap_handler_table_ctx); /* STEP4 */
    sparcv8_inst_set_initialize_interface_signals(&sparcv8_inst_set_interface_signals_ctx); /* STEP5 */
    sparcv8_instruction_set_initialize_function_ptr(&sparcv8_inst_set_functions_index_ctx); /* STEP6 */
    sparcv8_emulator_core_initialize(&sparc_emulator_core_ctx);
    printf("EMULATOR INITIALIZED");
    return ;
}

void command_prompt_help(void)
{
    printf("\nWELCOME TO HELP MANUAL, YOU HAVE THE FOLLOWING OPTIONS :\n\n"
           "INITIALIZE    EMULATOR BY PRESSING                    'INITIALIZE'\n"
           "SUSPEND THE EMULATOR BY PRESSING                      'HALT'\n"
           "RESET THE EMULATOR BY PRESSING                        'RESET'\n"
           "HELP FOR THE USER INTERFACE BY PRESSING               'HELP'\n"
           "START RUNNING EMULATOR BY PRESSING                    'FREERUN'\n"
           "RUN EMULATOR ONCE BY PRESSING                         'STEP'\n"
           "EXIT FROM EMULATOR BY PRESSING                        'EXIT'\n"
           "TERMINATE CHILD THREAD OF EMULATOR BY PRESSING        'KILL'\n"
           "GET EMULATOR'S STATUS BY PRESSING                     'STATUS'\n"
           "CLEAR COMMAND WINDOW PROMPT BY PRESSING               'CLS'\n"
           "READ DATA MEMORY BY PRESSING            'READ DATA  MEMORY *'\n"
           "READ DATA MEMORIESS BY PRESSING         'READ DATA  MEMORY * FOR *'\n"
           "READ STACK MEMORY BY PRESSING           'READ STACK   MEMORY *'\n"
           "READ STACK MEMORIES  BY PRESSING        'READ STACK   MEMORY * FOR *'\n"
           "WRITE DATA MEMORY BY PRESSING           'WRITE DATA MEMORY *'\n"
           "WRITE DATA MEMORY BY PRESSING           'WRITE DATA MEMORY * FOR * VALUE *'\n"
           "WRITE STACK MEMORY  BY PRESSING         'WRITE STACK  MEMORY *'\n"
           "WRITE STACK MEMORY  BY PRESSING         'WRITE STACK  MEMORY * FOR * VALUE *'\n"
           "READ PROGRAM MEMORY BY PRESSING         'READ PROGRAM  MEMORY *'\n"
           "READ PROGRAM MEMORIESS BY PRESSING      'READ PROGRAM  MEMORY * FOR *'\n"
           "WRITE PROGRAM MEMORY  BY PRESSING       'WRITE PROGRAM  MEMORY *'\n"
           "WRITE PROGRAM MEMORY  BY PRESSING       'WRITE PROGRAM  MEMORY * FOR * VALUE *'\n"
           "INITIALIZE PROGRAM  BY PRESSING         'LOAD PROGRAM MEAN VALUE'\n"
           "INITIALIZE FILE PROGRAM BY PRESSING     'LOAD PROGRAM FROM FILE'\n"
           "SHOW EXECUTION TIME  BY PRESSING        'TIME'\n"
           "PRINT REGISTER'S OPTIONS  BY PRESSING   'REGISTER'\n\n");

    return ;
}

void command_prompt_free_run(void)
{
    if(( (struct THREAD_INFO_context*) thread_info_ptr)->thread_suspend == TRUE  )
    {
        WaitForSingleObject(((struct THREAD_INFO_context*)thread_info_ptr)->ghMutex,INFINITE); /* handle to mutex  , no time-out interval   */

        /*   LOCK  */

        ((struct THREAD_INFO_context*) thread_info_ptr)->thread_suspend = FALSE;

        /*  UNLOCK  */

        ReleaseMutex(((struct THREAD_INFO_context*)thread_info_ptr)->ghMutex);
        ResumeThread( ((struct THREAD_INFO_context*) thread_info_ptr) -> Thread_Handles[1]);
        printf("THE EMULATOR IS IN FREE RUN MODE \n");
    }
    else
    {
        printf("THE EMULATOR IS ALREADY IN FREE RUN MODE \n");
    }
    return ;
}

void command_prompt_step(void)
{
    if (((struct THREAD_INFO_context*) thread_info_ptr)->thread_suspend == TRUE)
    {
        ResumeThread( ((struct THREAD_INFO_context*) thread_info_ptr) -> Thread_Handles[1]);
        printf("THE EMULATOR STEPED \n");
    }
    else
    {
        printf("YOU HAVE TO HALT THE EMULATOR FIRST SO YOU CAN STEP AFTER\n");
    }
    return ;
}

void command_prompt_exit(void)
{
    thread_info_ptr->thread_exit=TRUE;
    printf("\nEXITING EMULATOR ...\n ");
    return ;
}

void command_prompt_kill(void)
{
    WaitForSingleObject(((struct THREAD_INFO_context*)thread_info_ptr)->ghMutex,INFINITE); /* handle to mutex  , no time-out interval   */

    /*   LOCK  */

    ((struct THREAD_INFO_context*) thread_info_ptr)->thread_suspend = TRUE;

    /*  UNLOCK  */

    ReleaseMutex(((struct THREAD_INFO_context*)thread_info_ptr)->ghMutex);

    printf("\nCHILD THREAD TERMINATED AND NO LONGER EXIST, PRESS RESET OR INITIALIZE TO CREATE IT AGAIN \n");

    TerminateThread(((struct THREAD_INFO_context*)thread_info_ptr)->Thread_Handles[1] , 0);

    CloseHandle( ((struct THREAD_INFO_context*)thread_info_ptr)->Thread_Handles[1]);
    return ;
}

void command_prompt_status(void)
{
    if( thread_info_ptr->thread_suspend== TRUE )
    {
        printf("EMULATOR IS IN SUSPENTED MODE\n");
    }
    else
    {
        printf("EMULATOR IS IN RUNNING MODE\n");
    }
    return;
}

void command_prompt_register(void)
{
    printf("READ  THE CONTENT OF ALL REGISTERS BY PRESSING        'REGISTER -R ALL'\n"
           "READ  THE CONTENT OF WINDOWD REGISTERS BY PRESSING    'REGISTER -R WINDOWD'\n"
           "READ  THE CONTENT OF PSR REGISTER BY PRESSING         'REGISTER -R PSR'\n"
           "READ  THE CONTENT OF WIM REGISTER BY PRESSING         'REGISTER -R WIM'\n"
           "READ  THE CONTENT OF TBR REGISTER BY PRESSING         'REGISTER -R TBR'\n"
           "READ  THE CONTENT OF Y REGISTER BY PRESSING           'REGISTER -R Y'\n"
           "READ  THE ADDRESS OF PC REGISTER BY PRESSING          'REGISTER -R PC'\n"
           "READ  THE ADDRESS OF PC REGISTER BY PRESSING          'REGISTER -R NPC'\n"
           "READ  THE CONTENT OF ASR REGISTER BY PRESSING         'REGISTER -R ASR'\n"
           "READ  THE CONTENT OF FSR REGISTER BY PRESSING         'REGISTER -R FSR'\n"
           "READ  THE CONTENT OF CSR REGISTER BY PRESSING         'REGISTER -R CSR'\n"
           "READ  THE CONTENT OF FPREG REGISTERS BY PRESSING      'REGISTER -R FPREG'\n"
           "READ  THE CONTENT OF COREG REGISTERS BY PRESSING      'REGISTER -R COREG'\n"
           "WRITE THE CONTENT TO PSR REGISTER BY PRESSING         'REGISTER -W PSR'\n"
           "WRITE THE CONTENT TO TBR REGISTER BY PRESSING         'REGISTER -W TBR'\n"
           "WRITE THE CONTENT TO Y REGISTER BY PRESSING           'REGISTER -W Y'\n"
           "WRITE THE OFFSET  TO PC REGISTER BY PRESSING          'REGISTER -W PC'\n"
           "WRITE THE OFFSET  TO nPC REGISTER BY PRESSING         'REGISTER -W NPC'\n"
           "WRITE THE CONTENT TO ASR REGISTER BY PRESSING         'REGISTER -W ASR'\n"
           "WRITE THE CONTENT TO FSR REGISTER BY PRESSING         'REGISTER -W FSR'\n"
           "WRITE THE CONTENT TO CSR REGISTER BY PRESSING         'REGISTER -W CSR'\n"
           "WRITE THE CONTENT OF G_REGISTERS BY PRESSING    'REGISTER -W GENERAL * VALUE *'\n\n");
    return;
}

void command_prompt_read_program_memory(ULONG command_parameter_address)
{
    printf("PROGRAM MEMORY[0x%x] CONTENT->0x%x\n",(UINT32)command_parameter_address,(UINT32)sparcv8_mmu_memory_program_load_word(command_parameter_address));
    return;
}


void command_prompt_read_program_memory_for(ULONG command_parameter_address,ULONG command_parameter_offset)
{
    for (command_prompt_terminal_ptr->counter=0; command_prompt_terminal_ptr->counter<command_parameter_offset; command_prompt_terminal_ptr->counter++)
    {
        printf("PROGRAM MEMORY[0x%x] CONTENT->0x%x\n",(UINT32)command_parameter_address,(UINT32)sparcv8_mmu_memory_program_load_word(command_parameter_address));
        command_parameter_address+=4;
    }
    return;
}

void command_prompt_write_program_memory(ULONG command_parameter_address,ULONG command_parameter_data)
{
    sparcv8_mmu_memory_program_store_word(command_parameter_data,command_parameter_address);
    printf("\nWRITE PROCESS SUCCEED...");
    return;
}

void command_prompt_write_program_memory_for(ULONG command_parameter_address,ULONG command_parameter_offset,ULONG command_parameter_data)
{
    for (command_prompt_terminal_ptr->counter=0; command_prompt_terminal_ptr->counter<command_parameter_offset; command_prompt_terminal_ptr->counter++)
    {
        sparcv8_mmu_memory_program_store_word(command_parameter_data,command_parameter_address);
        command_parameter_address+=4;
    }
    printf("\nWRITE PROCESS SUCCEED...");
    return;
}

void command_prompt_read_data_memory(ULONG command_parameter_address)
{
    printf("DATA MEMORY[0x%x] CONTENT->0x%x\n",(UINT32)command_parameter_address,(UINT32)sparcv8_mmu_memory_data_load_word(command_parameter_address));
    return;
}

void command_prompt_read_data_memory_for(ULONG command_parameter_address,ULONG command_parameter_offset)
{
    for (command_prompt_terminal_ptr->counter=0; command_prompt_terminal_ptr->counter<command_parameter_offset; command_prompt_terminal_ptr->counter++)
    {
        printf("DATA MEMORY[0x%x] CONTENT->0x%x\n",(UINT32)command_parameter_address,(UINT32)sparcv8_mmu_memory_data_load_word(command_parameter_address));
        command_parameter_address+=4;
    }
    return;
}

void command_prompt_write_data_memory(ULONG command_parameter_address,ULONG command_parameter_data)
{
    sparcv8_mmu_memory_data_store_word(command_parameter_data,command_parameter_address);
    printf("\nWRITE PROCESS SUCCEED...");
    return;
}

void command_prompt_write_data_memory_for(ULONG command_parameter_address,ULONG command_parameter_offset,ULONG command_parameter_data)
{
    for (command_prompt_terminal_ptr->counter=0; command_prompt_terminal_ptr->counter<command_parameter_offset; command_prompt_terminal_ptr->counter++)
    {
        sparcv8_mmu_memory_data_store_word(command_parameter_data,command_parameter_address);
        command_parameter_address+=4;
    }
    printf("\nWRITE PROCESS SUCCEED...");
    return;
}

void command_prompt_read_stack_memory(ULONG command_parameter_address)
{
    printf("STACK MEMORY[0x%x] CONTENT->0x%x\n",(UINT32)command_parameter_address,(UINT32)sparcv8_mmu_memory_stack_load_word(command_parameter_address));
    return;
}

void command_prompt_read_stack_memory_for(ULONG command_parameter_address,ULONG command_parameter_offset)
{
    for (command_prompt_terminal_ptr->counter=0; command_prompt_terminal_ptr->counter<command_parameter_offset; command_prompt_terminal_ptr->counter++)
    {
        printf("STACK MEMORY[0x%x] CONTENT->0x%x\n",(UINT32)command_parameter_address,(UINT32)sparcv8_mmu_memory_stack_load_word(command_parameter_address));
        command_parameter_address+=4;
    }
    return;

}

void command_prompt_write_stack_memory(ULONG command_parameter_address,ULONG command_parameter_data)
{
    sparcv8_mmu_memory_stack_store_word(command_parameter_data,command_parameter_address);
    printf("\nWRITE PROCESS SUCCEED...");
    return;
}

void command_prompt_write_stack_memory_for(ULONG command_parameter_address,ULONG command_parameter_offset,ULONG command_parameter_data)
{
    for (command_prompt_terminal_ptr->counter=0; command_prompt_terminal_ptr->counter<command_parameter_offset; command_prompt_terminal_ptr->counter++)
    {
        sparcv8_mmu_memory_stack_store_word(command_parameter_data,command_parameter_address);
        command_parameter_address+=4;
    }
    printf("\nWRITE PROCESS SUCCEED...");
    return;
}

void command_prompt_read_windowd(void)
{
    char window_number[4];
    printf("CURRENT WINDOW IS %lu GIVE YOUR WINDOW CHOICE : ",  (sparc_intunit_ptr->PSR & 0x1F ) );
    gets (window_number) ;

    for (command_prompt_terminal_ptr->counter=0; command_prompt_terminal_ptr->counter<8; command_prompt_terminal_ptr->counter++)
    {
        printf("\nGENERAL REGISTER %d OF %d WINDOW IS 0x%x",command_prompt_terminal_ptr->counter,atoi(window_number),(UINT32)sparc_intunit_ptr->windowregs.GREG[command_prompt_terminal_ptr->counter]);
    }
    printf("\n\nWINDOWS REGISTERS ARE AS PRESENTED BELOW:");
    for (command_prompt_terminal_ptr->counter=0; command_prompt_terminal_ptr->counter<8; command_prompt_terminal_ptr->counter++)
    {
        printf("\nOUTPUT REGISTER %d OF %d WINDOW IS 0x%x",command_prompt_terminal_ptr->counter,atoi(window_number),(UINT32)*sparc_proc_integer_unit_windowregs_ptr[ (atoi(window_number) * 24)+ command_prompt_terminal_ptr->counter]  );
    }
    for (command_prompt_terminal_ptr->counter=0; command_prompt_terminal_ptr->counter<8; command_prompt_terminal_ptr->counter++)
    {
        printf("\nLOCAL REGISTER %d OF %d WINDOW IS 0x%x",command_prompt_terminal_ptr->counter,atoi(window_number),(UINT32)*sparc_proc_integer_unit_windowregs_ptr[ (atoi(window_number) * 24) + 8 + command_prompt_terminal_ptr->counter]  );
    }
    for (command_prompt_terminal_ptr->counter=0; command_prompt_terminal_ptr->counter<8; command_prompt_terminal_ptr->counter++)
    {
        printf("\nINPUT REGISTER %d OF %d WINDOW IS 0x%x",command_prompt_terminal_ptr->counter,atoi(window_number),(UINT32)*sparc_proc_integer_unit_windowregs_ptr[ (atoi(window_number) * 24) + 16 + command_prompt_terminal_ptr->counter]  );
    }
    return;
}

void command_prompt_write_to_general_regs(ULONG command_parameter_address,ULONG command_parameter_data)
{
    sparc_intunit_ptr->windowregs.GREG[command_parameter_address]=command_parameter_data;
    printf("\nWRITE PROCESS SUCCEED...");
    return;
}

void command_prompt_read_psr(void)
{
    printf("VALUE OF PSR IS  0x%x\n",(UINT32)sparc_intunit_ptr->PSR);
    return;
}

void command_prompt_write_psr(ULONG incoming_command_parameter)
{
    sparcv8_inst_set_extra_WRPSR(PSRALL,incoming_command_parameter);
    printf("\nWRITE PROCESS SUCCEED...");
    return;
}

void command_prompt_read_wim(void)
{
    printf("VALUE OF WIM IS  0x%x\n",(UINT32)sparc_intunit_ptr->WIM);
    return;
}

void command_prompt_read_tbr(void)
{
    printf("VALUE OF TBR IS  0x%x\n",(UINT32)sparc_intunit_ptr->TBR);
    return;
}

void command_prompt_write_tbr(ULONG incoming_command_parameter)
{
    sparcv8_inst_set_extra_WRTBR(TBRALL,incoming_command_parameter);
    printf("\nWRITE PROCESS SUCCEED...");
    return;
}

void command_prompt_read_y(void)
{
    printf("VALUE OF Y IS  0x%x\n",(UINT32)sparc_intunit_ptr->Y);
    return;
}

void command_prompt_write_y(ULONG incoming_command_parameter)
{
    sparcv8_inst_set_extra_WRY(0,YALL,incoming_command_parameter);
    printf("\nWRITE PROCESS SUCCEED...");
    return;
}

void command_prompt_read_pc(void)
{
    printf("VALUE OF PC IS [0x%x] CONTENT->0x%x\n",(((UINT32*)sparc_intunit_ptr->PC)-((UINT32*)emu_memory_program_ptr))*4,*(UINT32*)sparc_intunit_ptr->PC );
    return;
}

void command_prompt_write_pc(ULONG incoming_command_parameter)
{
    sparc_intunit_ptr->PC=(ULONG*)emu_memory_program_ptr+(incoming_command_parameter/4);
    printf("\nWRITE PROCESS SUCCEED...");
    return;
}

void command_prompt_read_npc(void)
{
  //  printf("VALUE OF nPC IS %x \n",*(UINT32*)sparc_intunit_ptr->nPC);
    printf("VALUE OF nPC IS [0x%x] CONTENT->0x%x\n",(((UINT32*)sparc_intunit_ptr->nPC)-((UINT32*)emu_memory_program_ptr))*4,*(UINT32*)sparc_intunit_ptr->nPC );

    return;
}

void command_prompt_write_npc(ULONG incoming_command_parameter)
{
    sparc_intunit_ptr->nPC=(ULONG*)emu_memory_program_ptr+(incoming_command_parameter/4);
    printf("\nWRITE PROCESS SUCCEED...");
    return;
}

void command_prompt_read_asr(void)
{
    printf("VALUE OF ASR IS  0x%x\n",(UINT32)sparc_intunit_ptr->ASR);
    return;
}

void command_prompt_write_asr(ULONG incoming_command_parameter)
{
    sparcv8_inst_set_extra_WRASR(0,ASRALL,incoming_command_parameter);
    printf("\nWRITE PROCESS SUCCEED...");
    return;
}

void command_prompt_read_all(void)
{
    printf("VALUE   OF ASR IS  0x%x\n",(UINT32)sparc_intunit_ptr->ASR);
    printf("VALUE   OF IUD IS  0x%x\n",(UINT32)sparc_intunit_ptr->IUD);
    printf("ADDRESS OF PC  IS  0x%x\n",(UINT32)sparc_intunit_ptr->PC);
    printf("ADDRESS OF nPC IS  0x%x\n",(UINT32)sparc_intunit_ptr->nPC);
    printf("VALUE   OF PC  IS  0x%x\n",*(UINT32*)sparc_intunit_ptr->PC);
    printf("VALUE   OF nPC IS  0x%x\n",*(UINT32*)sparc_intunit_ptr->nPC);
    printf("VALUE   OF PSR IS  0x%x\n",(UINT32)sparc_intunit_ptr->PSR);
    printf("VALUE   OF TBR IS  0x%x\n",(UINT32)sparc_intunit_ptr->TBR);
    printf("VALUE   OF WIM IS  0x%x\n",(UINT32)sparc_intunit_ptr->WIM);
    printf("VALUE   OF Y   IS  0x%x\n",(UINT32)sparc_intunit_ptr->Y);
    printf("VALUE   OF CSR IS  0x%x\n",(UINT32)sparc_coprocessor_ptr->CSR);
    printf("VALUE   OF FSR IS  0x%x\n",(UINT32)sparc_fpu_ptr->FSR);
    return ;
}

void command_prompt_read_fsr(void)
{
    printf("VALUE OF FSR IS  0x%x\n",(UINT32)sparc_fpu_ptr->FSR);
    return;
}

void command_prompt_write_fsr(ULONG incoming_command_parameter)
{
    sparcv8_inst_set_extra_WRFSR(FSRALL,incoming_command_parameter);
    printf("\nWRITE PROCESS SUCCEED...");
    return;
}

void command_prompt_read_csr(void)
{
    printf("VALUE OF CSR IS  0x%x\n",(UINT32)sparc_coprocessor_ptr->CSR);
    return;
}

void command_prompt_write_csr(ULONG incoming_command_parameter)
{
    sparcv8_inst_set_extra_WRCSR(0,CSRALL,incoming_command_parameter);
    printf("\nWRITE PROCESS SUCCEED...");
    return;
}

void command_prompt_read_fpreg(void)
{
    for (command_prompt_terminal_ptr->counter=0; command_prompt_terminal_ptr->counter<32; command_prompt_terminal_ptr->counter++)
    {
        printf("\nFLOATING POINT REGISTER %d HAS VALUE %f",command_prompt_terminal_ptr->counter,sparc_fpu_ptr->FREG[command_prompt_terminal_ptr->counter] ) ;
    }
    return ;
}

void command_prompt_read_coreg(void)
{
    for (command_prompt_terminal_ptr->counter=0; command_prompt_terminal_ptr-> counter<32; command_prompt_terminal_ptr->counter++)
    {
        printf("\nCO PROCESSOR REGISTER %d HAS VALUE 0x%x",command_prompt_terminal_ptr->counter,(UINT32)sparc_coprocessor_ptr->CREG[command_prompt_terminal_ptr->counter]) ;
    }
    return ;
}
void command_prompt_clear_terminal(void)
{
    system("CLS");
    printf("Copyright     : Copyright (C) 2016 Monahopoulos Konstantinos\n"
           "Project       : Sparc_V8 Emulator\n"
           "Description   : Spacecraft Multicore Emulator Based on Leon 3 Sparc V8 architecture processor\n"
           "Author        : Monahopoulos Konstantinos\n");
    return;
}


void command_prompt_load_program_mean_value(void)
{

    /* DATA MEMORY VALUES*/
    sparcv8_mmu_memory_data_store_word(11,0x0);
    sparcv8_mmu_memory_data_store_word(22,0x4);
    sparcv8_mmu_memory_data_store_word(33,0x8);
    sparcv8_mmu_memory_data_store_word(3,0xC);


    /* PROGRAM MEMORY VALUES*/
    sparcv8_mmu_memory_program_store_word(0xC2002000,0x0);
    sparcv8_mmu_memory_program_store_word(0x90000001,0x4);
    sparcv8_mmu_memory_program_store_word(0xC2002004,0x8);
    sparcv8_mmu_memory_program_store_word(0x92000001,0xC);
    sparcv8_mmu_memory_program_store_word(0xC2002008,0x10);
    sparcv8_mmu_memory_program_store_word(0x94000001,0x14);
    sparcv8_mmu_memory_program_store_word(0x95E00000,0x18);
    sparcv8_mmu_memory_program_store_word(0xA0060019,0x1C);
    sparcv8_mmu_memory_program_store_word(0x90068010,0x20);
    sparcv8_mmu_memory_program_store_word(0x95E00000,0x24);
    sparcv8_mmu_memory_program_store_word(0xC200200C,0x28);
    sparcv8_mmu_memory_program_store_word(0xB0760001,0x2C);
    sparcv8_mmu_memory_program_store_word(0x83E80000,0x30);
    sparcv8_mmu_memory_program_store_word(0xB0020000,0x34);
    sparcv8_mmu_memory_program_store_word(0x83E80008,0x38);

    /*ZERO THE REST OF THE PROGRAM MEMORY*/

    for(command_prompt_terminal_ptr->counter=0; command_prompt_terminal_ptr->counter<sparc_emulator_core_ptr->filesize-15; command_prompt_terminal_ptr->counter++)
    {
        sparcv8_mmu_memory_program_store_word(0x000000,(0x3C+(command_prompt_terminal_ptr->counter*4)));
    }
    printf("PROGRAM HAS WRITEN TO PROGRAM MEMORY\n");
    return ;
}

void command_prompt_time(void)
{
    printf("PROGRAM EXECUTION TIME IS %f MICROSECONDS\n",sparc_emulator_core_ptr->final_time_of_execution);
    return;
}

void command_prompt_load_program_from_file(void)
{
    FILE *fileptr = fopen(FILE_PROGRAM_1,"rb");
    if (fileptr==NULL)
    {
        perror("Error");
    }

    fseek(fileptr, 0L, SEEK_END);
    ULONG bytes_number = ftell(fileptr);
    emu_memory_program_ptr=malloc(bytes_number*sizeof(char));
    rewind(fileptr);
    fread((ULONG*)emu_memory_program_ptr,sizeof(int),(bytes_number/sizeof(int)),fileptr);
    printf("PROGRAM HAS WRITEN TO PROGRAM MEMORY\n");
}
