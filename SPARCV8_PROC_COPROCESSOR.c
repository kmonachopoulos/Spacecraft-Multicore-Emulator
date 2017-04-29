/*
  ------------------------------------------------------------------------------------------------------------------------------------------
  Project       : Sparc_V8 Emulator
  File          : SPARCV8_PROC_COPROCESSOR.c
  Description   : Sparc V8 CoProcessor initialization
  Author        : Monachopoulos Konstantinos
  ------------------------------------------------------------------------------------------------------------------------------------------
*/
/*
  ----------------------------------------------------------------------------------------------------------------------------------------
  Includes
  ----------------------------------------------------------------------------------------------------------------------------------------
*/

#include "SPARCV8_PROC_COPROCESSOR.h"

void sparcv8_proc_cop_initialization(struct SPARCV8_PROC_COPROCESSOR_Context *sparc_proc_ptr)  /* INITIALIZATION OF COPROCESSOR UNIT */
{
    int initializer_to_zero;
    sparc_proc_ptr->CSR=0;
    sparc_proc_ptr->CQ=0;

    for (initializer_to_zero=0; initializer_to_zero<sizeof(sparc_proc_ptr->CREG)/sizeof(ULONG); initializer_to_zero++)
    {
        sparc_proc_ptr->CREG[initializer_to_zero]=0;
    }
    sparc_coprocessor_ptr=sparc_proc_ptr; /* FOR REFERENCE THROUGH POINTER */
}
