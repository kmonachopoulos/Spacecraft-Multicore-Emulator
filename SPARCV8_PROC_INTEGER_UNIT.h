#ifndef SPARCV8_PROC_INTEGER_UNIT_H_INCLUDED
#define SPARCV8_PROC_INTEGER_UNIT_H_INCLUDED

/*
  --------------------------------------------------------------------------------------------------
  Includes
  --------------------------------------------------------------------------------------------------
*/

#include "TYPES.h"

/*
  --------------------------------------------------------------------------------------------------
  Defines
  --------------------------------------------------------------------------------------------------
*/

#define MAXWIM 0x00000008;

/*
  --------------------------------------------------------------------------------------------------
  Externs
  --------------------------------------------------------------------------------------------------
*/

extern ULONG* sparcv8_mmu_memory_program_return_ptr(void);
extern struct SPARCV8_PROC_Context sparc_proc;

/*
  --------------------------------------------------------------------------------------------------
  Structures
  --------------------------------------------------------------------------------------------------
*/

struct SPARCV8_PROC_INTEGER_UNIT_Context  /*INITIALIZE INTEGER UNIT*/
{

    ULONG PSR; /*Processor Status Register */
    ULONG WIM; /*Window Invalid Mask*/
    ULONG TBR; /*Trap Base Register*/
    ULONG Y; /*Multiply/Divide Register*/
    ULONG *PC; /*Program Counter*/
    ULONG *nPC;/*Next Program Counter*/
    ULONG ASR; /*Implementation-Ddependent Ancilary State Registers*/
    ULONG IUD; /*Implementation-Ddependent IU Deferred-Trap Queue*/


    struct SPARCV8_PROC_INTEGER_UNIT_Context_windowregs
    {
        ULONG GREG[8];   /*global registers*/

        ULONG OREG[8*0x00000008];  /*out registers - MAXWIM WIM=8*/

        ULONG LREG[8*0x00000008];  /*local registers - MAXWIM WIM=8*/

        ULONG IREG[8*0x00000008];  /*input registers - MAXWIM WIM=8*/

    } windowregs;
};

struct SPARCV8_PROC_INTEGER_UNIT_Context *sparc_intunit_ptr;

/*
  --------------------------------------------------------------------------------------------------
  Function Prototyping
  --------------------------------------------------------------------------------------------------
*/

void sparcv8_proc_intunit_initialization(struct SPARCV8_PROC_INTEGER_UNIT_Context *sparc_proc_ptr);
ULONG *sparc_proc_integer_unit_windowregs_ptr[24*0x00000008];

#endif // SPARCV8_PROC_INTEGER_UNIT_H_INCLUDED
