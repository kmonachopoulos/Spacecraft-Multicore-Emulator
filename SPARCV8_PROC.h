#ifndef SPARCV8_PROC_H_INCLUDED
#define SPARCV8_PROC_H_INCLUDED

/*
  --------------------------------------------------------------------------------------------------
  Includes
  --------------------------------------------------------------------------------------------------
*/

#include "SPARCV8_PROC_COPROCESSOR.h"
#include "SPARCV8_PROC_FLOATING_POINT_UNIT.h"
#include "SPARCV8_PROC_INTEGER_UNIT.h"
#include "SPARCV8_MMU.h"

/*
  --------------------------------------------------------------------------------------------------
  Structures
  --------------------------------------------------------------------------------------------------
*/

struct SPARCV8_PROC_Context /* SUPERSTRUCT DECLARATION INCLUDING PROCESSOR COMPONENTS STRUCTS */
{
    struct SPARCV8_PROC_COPROCESSOR_Context                 sparc_coprocessor_ctx;
    struct SPARCV8_PROC_FLOATING_POINT_UNIT_Context         sparc_fpu_ctx;
    struct SPARCV8_PROC_INTEGER_UNIT_Context                sparc_intunit_ctx;
};

struct SPARCV8_PROC_Context sparc_proc;

/*
  --------------------------------------------------------------------------------------------------
  Function Prototyping
  --------------------------------------------------------------------------------------------------
*/

void sparcv8_proc_initialization(void);

#endif // SPARCV8_PROC_H_INCLUDED
