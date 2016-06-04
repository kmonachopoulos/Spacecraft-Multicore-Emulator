#ifndef COMMAND_PROMPT_H_INCLUDED
#define COMMAND_PROMPT_H_INCLUDED

/*
  --------------------------------------------------------------------------------------------------
  Includes
  --------------------------------------------------------------------------------------------------
*/

#include "TYPES.h"

/*
  --------------------------------------------------------------------------------------------------
  Defines
  --------------------------------------------------------------------------------------------------
*/

#define MAX_COMMAND_SIZE 50
#define NUMBER_OF_COMMANDS 48

/*
  --------------------------------------------------------------------------------------------------
  Structures
  --------------------------------------------------------------------------------------------------
*/
typedef void* (*command_prompt_fnc_ptr) (void*,void*,void*);
struct COMMAND_PROMT_TERMINAL
{
    command_prompt_fnc_ptr command_prompt_fnc_array[NUMBER_OF_COMMANDS];
    char cmd_std_input[MAX_COMMAND_SIZE];
    ULONG value_from_stdin[3];
    char *token_delims;
    char *token;
    char *endptr;
    UINT8 counter;
};

struct COMMAND_PROMT_TERMINAL command_prompt_terminal_ctx ;
struct COMMAND_PROMT_TERMINAL *command_prompt_terminal_ptr ;


/*
  --------------------------------------------------------------------------------------------------
  Function Prototyping
  --------------------------------------------------------------------------------------------------
*/

DWORD WINAPI command_prompt(LPVOID thread_info_ptr);
void command_prompt_terminal_initialize(struct COMMAND_PROMT_TERMINAL *command_prompt_terminal_tmp_ptr);
void command_prompt_match_and_execute_command(char* stdin_command);
void command_prompt_initialize(void);
void command_prompt_halt(void);
void command_prompt_reset(void);
void command_prompt_help(void);
void command_prompt_free_run(void);
void command_prompt_step(void);
void command_prompt_exit(void);
void command_prompt_kill(void);
void command_prompt_status(void);
void command_prompt_register(void);
void command_prompt_read_program_memory(ULONG command_parameter_address);
void command_prompt_read_program_memory_for(ULONG command_parameter_address,ULONG command_parameter_offset);
void command_prompt_write_program_memory(ULONG command_parameter_address,ULONG command_parameter_data);
void command_prompt_write_program_memory_for(ULONG command_parameter_address,ULONG command_parameter_offset,ULONG command_parameter_data);
void command_prompt_read_data_memory(ULONG command_parameter_address);
void command_prompt_read_data_memory_for(ULONG command_parameter_address,ULONG command_parameter_offset);
void command_prompt_write_data_memory(ULONG command_parameter_address,ULONG command_parameter_data);
void command_prompt_write_data_memory_for(ULONG command_parameter_address,ULONG command_parameter_offset,ULONG command_parameter_data);
void command_prompt_read_stack_memory(ULONG command_parameter_address);
void command_prompt_read_stack_memory_for(ULONG command_parameter_address,ULONG command_parameter_offset);
void command_prompt_write_stack_memory(ULONG command_parameter_address,ULONG command_parameter_data);
void command_prompt_write_stack_memory_for(ULONG command_parameter_address,ULONG command_parameter_offset,ULONG command_parameter_data);
void command_prompt_read_windowd(void);
void command_prompt_write_to_general_regs(ULONG command_parameter_address,ULONG command_parameter_data);
void command_prompt_read_psr(void);
void command_prompt_write_psr(ULONG incoming_command_parameter);
void command_prompt_read_wim(void);
void command_prompt_read_tbr(void);
void command_prompt_write_tbr(ULONG incoming_command_parameter);
void command_prompt_read_y(void);
void command_prompt_write_y(ULONG incoming_command_parameter);
void command_prompt_read_pc(void);
void command_prompt_write_pc(ULONG incoming_command_parameter);
void command_prompt_read_npc(void);
void command_prompt_write_npc(ULONG incoming_command_parameter);
void command_prompt_read_asr(void);
void command_prompt_write_asr(ULONG incoming_command_parameter);
void command_prompt_read_all(void);
void command_prompt_read_fsr(void);
void command_prompt_write_fsr(ULONG incoming_command_parameter);
void command_prompt_read_csr(void);
void command_prompt_write_csr(ULONG incoming_command_parameter);
void command_prompt_read_fpreg(void);
void command_prompt_read_coreg(void);
void command_prompt_clear_terminal(void);
void command_prompt_time(void);
void command_prompt_load_program_mean_value(void);
void command_prompt_load_program_from_file(void);

#endif // COMMAND_PROMPT_H_INCLUDED
