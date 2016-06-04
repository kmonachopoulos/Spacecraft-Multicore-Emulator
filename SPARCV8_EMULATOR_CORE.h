#ifndef SPARCV8_EMULATOR_CORE_H_INCLUDED
#define SPARCV8_EMULATOR_CORE_H_INCLUDED

/*
  --------------------------------------------------------------------------------------------------
  Includes
  --------------------------------------------------------------------------------------------------
*/

#include "TYPES.h"

/*
  --------------------------------------------------------------------------------------------------
  Structures
  --------------------------------------------------------------------------------------------------
*/

struct SPARCV8_EMULATOR_CORE_CONTEXT
{
    UINT32 instruction_counter;
    ULONG* instruction;
    UINT32 filesize;
    ULONG op;
    ULONG op2;
    ULONG op3;
    ULONG op3_bit_0_to_3;
    ULONG op3_bit_4_to_5;
    ULONG opf;
    /*TIME COUNTER VARIABLES*/
    double final_time_of_execution;
    double PCFreq;
    __int64 CounterStart;
    LARGE_INTEGER li;
};

struct SPARCV8_EMULATOR_CORE_CONTEXT sparc_emulator_core_ctx ;
struct SPARCV8_EMULATOR_CORE_CONTEXT *sparc_emulator_core_ptr ;

/*
  --------------------------------------------------------------------------------------------------
  Function Prototyping
  --------------------------------------------------------------------------------------------------
*/

DWORD WINAPI sparcv8_emulator_core_main_loop(LPVOID thread_info_ptr);
void sparcv8_emulator_core_initialize(struct SPARCV8_EMULATOR_CORE_CONTEXT *sparc_emulator_core_tmp_ptr);

/*
  --------------------------------------------------------------------------------------------------
  Variables Declaration
  --------------------------------------------------------------------------------------------------
*/



#endif // SPARCV8_EMULATOR_CORE_H_INCLUDED
