/*
  ------------------------------------------------------------------------------------------------------------------------------------------
  Project       : Sparc_V8 Emulator
  File          : SPARCV8_PROC_INTEGER_UNIT.c
  Description   : Sparc V8 Integer Unit initialization
  Author        : Monachopoulos Konstantinos
  ------------------------------------------------------------------------------------------------------------------------------------------
*/
/*
  ----------------------------------------------------------------------------------------------------------------------------------------
  Includes
  ----------------------------------------------------------------------------------------------------------------------------------------
*/

#include "SPARCV8_PROC_INTEGER_UNIT.h"

void sparcv8_proc_intunit_initialization(struct SPARCV8_PROC_INTEGER_UNIT_Context *sparc_proc_ptr) /* INITIALIZATION OF INTEGER UNIT */
{

    INT32 counter1,counter2,win_var_num=0;

    /* The compiler normally produces binaries that assumes that the target processor has 8 register
    windows. However, by compiling and linking with the -mflat switch, it is possible to produce
    binaries that will run on processors with only 2 register windows. WIM sets the windows number */

    sparc_proc_ptr->PSR=0x30E7; /* CWP VALUE */
    sparc_proc_ptr->WIM=0x00000080; /* WIM HAS 8 WINDOWS (BIT NUMBER 8 IS SET) */
    sparc_proc_ptr->TBR=0;
    sparc_proc_ptr->Y=1;
    sparc_proc_ptr->PC=sparcv8_mmu_memory_program_return_ptr()-1;
    sparc_proc_ptr->nPC=sparcv8_mmu_memory_program_return_ptr() ;
    sparc_proc_ptr->ASR=0;
    sparc_proc_ptr->IUD=0;


    for (counter1=0; counter1<8; counter1++)
    {
        sparc_proc_ptr->windowregs.GREG[counter1]=0;
    }
    for(counter1=0; counter1<(sparc_proc_ptr->WIM) >> 4; counter1++)  /* FILL THEM BY GROUPS OF 8 */
    {
        for(counter2=(counter1*8); counter2<((counter1+1)*8); counter2++)
        {
            sparc_proc_ptr->windowregs.OREG[counter2]=0;
            sparc_proc_integer_unit_windowregs_ptr[win_var_num] = &sparc_proc_ptr->windowregs.OREG[counter2]; /* PTR'S ARRAY OF NON CONTIGUOUS ADDRESS MEMORY */

            win_var_num++;
        }
        for(counter2=(counter1*8); counter2<((counter1+1)*8); counter2++)
        {
            sparc_proc_ptr->windowregs.LREG[counter2]=0;
            sparc_proc_integer_unit_windowregs_ptr[win_var_num]  = &sparc_proc_ptr->windowregs.LREG[counter2];
            win_var_num++;
        }
        for(counter2=(counter1*8); counter2<((counter1+1)*8); counter2++)
        {
            sparc_proc_ptr->windowregs.IREG[counter2]=0;
            sparc_proc_integer_unit_windowregs_ptr[win_var_num]  = &sparc_proc_ptr->windowregs.IREG[counter2];

            win_var_num++;
        }
    }
    sparc_intunit_ptr=sparc_proc_ptr; /* FOR REFERENCE THROUGH POINTER */
}



