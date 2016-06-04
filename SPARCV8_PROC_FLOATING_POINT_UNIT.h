#ifndef SPARCV8_PROC_FLOATING_POINT_UNIT_H_INCLUDED
#define SPARCV8_PROC_FLOATING_POINT_UNIT_H_INCLUDED

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

struct SPARCV8_PROC_FLOATING_POINT_UNIT_Context  /*INITIALIZE FLOATING-POINT UNIT*/
{
    ULONG FSR;  /*Floating - Point State Register*/
    ULONG FQ;   /*Implementation-Ddependent FP Deferred-Trap Queue*/
    FLOAT32 FREG[32];  /*FloatingPoint 32-bit registers*/
};

struct SPARCV8_PROC_FLOATING_POINT_UNIT_Context *sparc_fpu_ptr;

/*
  --------------------------------------------------------------------------------------------------
  Function Prototyping
  --------------------------------------------------------------------------------------------------
*/

void sparcv8_proc_fpu_initialization(struct SPARCV8_PROC_FLOATING_POINT_UNIT_Context *sparc_proc_ptr);

#endif // SPARCV8_PROC_FLOATING_POINT_UNIT_H_INCLUDED
