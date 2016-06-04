#ifndef SPARCV8_PROC_COPROCESSOR_H_INCLUDED
#define SPARCV8_PROC_COPROCESSOR_H_INCLUDED

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

struct SPARCV8_PROC_COPROCESSOR_Context   /*INITIALIZE COPROCESSOR*/
{
    ULONG CSR;  /*Implementation-Ddependent Coprocessor State Register*/
    ULONG CQ;   /*Implementation-Ddependent Coprocessor Deferred-Trap Queue*/
    ULONG CREG[32];  /*Coprocessor 32-bit registers*/
};

struct SPARCV8_PROC_COPROCESSOR_Context *sparc_coprocessor_ptr;

/*
  --------------------------------------------------------------------------------------------------
  Function Prototyping
  --------------------------------------------------------------------------------------------------
*/

void sparcv8_proc_cop_initialization(struct SPARCV8_PROC_COPROCESSOR_Context *sparc_coprocessor_ptr);

#endif // SPARCV8_PROC_COPROCESSOR_H_INCLUDED
