/*
  ------------------------------------------------------------------------------------------------------------------------------------------
  Project       : Sparc_V8 Emulator
  File          : SPARCV8_PROC.c
  Description   : Sparc V8 Main processor components initialization
  Author        : Monachopoulos Konstantinos
  ------------------------------------------------------------------------------------------------------------------------------------------
*/
/*
  ----------------------------------------------------------------------------------------------------------------------------------------
  Includes
  ----------------------------------------------------------------------------------------------------------------------------------------
*/

#include "SPARCV8_PROC.h"

void sparcv8_proc_initialization(void) /*INITIALIZATION OF ALL UNINTS*/
{
    sparcv8_mmu_memory_data_main_init();
    sparcv8_mmu_memory_program_main_init();
    sparcv8_mmu_memory_data_stack_init(sparc_proc.sparc_intunit_ctx.WIM>>4);
    sparcv8_proc_intunit_initialization(&sparc_proc.sparc_intunit_ctx);
    sparcv8_proc_cop_initialization(&sparc_proc.sparc_coprocessor_ctx);
    sparcv8_proc_fpu_initialization(&sparc_proc.sparc_fpu_ctx);
    sparc_proc.sparc_intunit_ctx.windowregs.IREG[62]=(ULONG)sparcv8_mmu_memory_stack_return_ptr();
    sparc_proc.sparc_intunit_ctx.windowregs.OREG[62]=(ULONG)sparcv8_mmu_memory_stack_return_ptr()-96;

}

