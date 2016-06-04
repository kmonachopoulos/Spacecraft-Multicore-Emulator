#ifndef SPARCV8_TRAPS_H_INCLUDED
#define SPARCV8_TRAPS_H_INCLUDED

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

struct TRAP_HANDLER_TABLE
{

    /* EACH WILL CONTAIN AN ADDRESS */

    ULONG reset;
    ULONG data_store_error;
    ULONG instruction_access_MMU_miss;
    ULONG instruction_access_error;
    ULONG r_register_access_error;
    ULONG instruction_access_exception;
    ULONG privileged_instruction;
    ULONG illegal_instruction;
    ULONG fp_disabled;
    ULONG cp_disabled;
    ULONG unimplemented_FLUSH;
    ULONG watchpoint_detected;
    ULONG window_overflow;
    ULONG window_underflow;
    ULONG mem_address_not_aligned;
    ULONG fp_exception;
    ULONG cp_exception;
    ULONG data_access_error;
    ULONG data_access_MMU_miss;
    ULONG data_access_exception;
    ULONG tag_overflow;
    ULONG division_by_zero;
    ULONG trap_instruction;
    ULONG interrupt_level[15];

};

struct TRAP_HANDLER_TABLE trap_handler_table_ctx;
struct TRAP_HANDLER_TABLE *trap_handler_ptr;

/*
  --------------------------------------------------------------------------------------------------
  Function Prototyping
  --------------------------------------------------------------------------------------------------
*/

void sparcv8_trap_initialize(struct TRAP_HANDLER_TABLE *trap_handler_tmp_ptr);

#endif // SPARCV8_TRAPS_H_INCLUDED
