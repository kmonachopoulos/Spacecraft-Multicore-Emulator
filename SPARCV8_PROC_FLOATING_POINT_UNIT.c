/*
  ------------------------------------------------------------------------------------------------------------------------------------------
  ExcelMicroTechnologies - emtech
  Copyright 2013-2014
  ------------------------------------------------------------------------------------------------------------------------------------------
*/
/*
  ------------------------------------------------------------------------------------------------------------------------------------------
  Project       : Sparc_V8 Emulator
  File          : SPARCV8_PROC_FLOATING_POINT_UNIT.c
  Description   : Sparc V8 Floating Point Unit initialization
  Author        : Monahopoulos Konstantinos
  ------------------------------------------------------------------------------------------------------------------------------------------
*/
/*
  ----------------------------------------------------------------------------------------------------------------------------------------
  Includes
  ----------------------------------------------------------------------------------------------------------------------------------------
*/

#include "SPARCV8_PROC_FLOATING_POINT_UNIT.h"

void sparcv8_proc_fpu_initialization(struct SPARCV8_PROC_FLOATING_POINT_UNIT_Context *sparc_proc_ptr) /* INITIALIZATION OF FLOATING POINT UNIT  */
{
    int initializer_to_zero;
    sparc_proc_ptr->FSR=0;
    sparc_proc_ptr->FQ=0;

    for (initializer_to_zero=0; initializer_to_zero<sizeof(sparc_proc_ptr->FREG)/sizeof(FLOAT32); initializer_to_zero++)
    {
        sparc_proc_ptr->FREG[initializer_to_zero]=0;
    }
    sparc_fpu_ptr=sparc_proc_ptr; /* FOR REFERENCE THROUGH POINTER */
}
