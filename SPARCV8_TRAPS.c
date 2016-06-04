/*
  ------------------------------------------------------------------------------------------------------------------------------------------
  Project       : Sparc_V8 Emulator
  File          : SPARCV8_TRAPS.c
  Description   : Sparc V8 Trap addresses initialization
  Author        : Monahopoulos Konstantinos
  ------------------------------------------------------------------------------------------------------------------------------------------
*/
/*
  ----------------------------------------------------------------------------------------------------------------------------------------
  Includes
  ----------------------------------------------------------------------------------------------------------------------------------------
*/

#include "SPARCV8_TRAPS.h"

/* TRAP HANDLERS INITIALIZATION */

void sparcv8_trap_initialize(struct TRAP_HANDLER_TABLE *trap_handler_tmp_ptr)
{

    trap_handler_tmp_ptr->reset=0x00;
    trap_handler_tmp_ptr->data_store_error=0x2B;
    trap_handler_tmp_ptr->instruction_access_MMU_miss=0x3C;
    trap_handler_tmp_ptr->instruction_access_error=0x21;
    trap_handler_tmp_ptr->r_register_access_error=0x20;
    trap_handler_tmp_ptr->instruction_access_exception=0x01;
    trap_handler_tmp_ptr->privileged_instruction=0x03;
    trap_handler_tmp_ptr->illegal_instruction=0x02;
    trap_handler_tmp_ptr->fp_disabled=0x04;
    trap_handler_tmp_ptr->cp_disabled=0x24;
    trap_handler_tmp_ptr->unimplemented_FLUSH=0x25;
    trap_handler_tmp_ptr->watchpoint_detected=0x0B;
    trap_handler_tmp_ptr->window_overflow=0x05;
    trap_handler_tmp_ptr->window_underflow=0x06;
    trap_handler_tmp_ptr->mem_address_not_aligned=0x07;
    trap_handler_tmp_ptr->fp_exception=0x08;
    trap_handler_tmp_ptr->cp_exception=0x28;
    trap_handler_tmp_ptr->data_access_error=0x29;
    trap_handler_tmp_ptr->data_access_MMU_miss=0x2C;
    trap_handler_tmp_ptr->data_access_exception=0x09;
    trap_handler_tmp_ptr->tag_overflow=0x0A;
    trap_handler_tmp_ptr->division_by_zero=0x2A;
    trap_handler_tmp_ptr->trap_instruction=0x80;

    trap_handler_tmp_ptr->interrupt_level[14]=0x1F;
    trap_handler_tmp_ptr->interrupt_level[13]= 0x1E;
    trap_handler_tmp_ptr->interrupt_level[12]= 0x1D;
    trap_handler_tmp_ptr->interrupt_level[11]= 0x1C;
    trap_handler_tmp_ptr->interrupt_level[10]= 0x1B;
    trap_handler_tmp_ptr->interrupt_level[9]= 0x1A;
    trap_handler_tmp_ptr->interrupt_level[8]= 0x19;
    trap_handler_tmp_ptr->interrupt_level[7]= 0x18;
    trap_handler_tmp_ptr->interrupt_level[6]= 0x17;
    trap_handler_tmp_ptr->interrupt_level[5]= 0x16;
    trap_handler_tmp_ptr->interrupt_level[4]= 0x15;
    trap_handler_tmp_ptr->interrupt_level[3]= 0x14;
    trap_handler_tmp_ptr->interrupt_level[2]= 0x13;
    trap_handler_tmp_ptr->interrupt_level[1]= 0x12;
    trap_handler_tmp_ptr->interrupt_level[0]=0x11;

    trap_handler_ptr=trap_handler_tmp_ptr;
    return;
}
