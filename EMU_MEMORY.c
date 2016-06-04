
/*
  ------------------------------------------------------------------------------------------------------------------------------------------
  ExcelMicroTechnologies - emtech
  Copyright 2013-2014
  ------------------------------------------------------------------------------------------------------------------------------------------
*/
/*
  ------------------------------------------------------------------------------------------------------------------------------------------
  Project       : Sparc_V8 Emulator
  File          : EMU_MEMORY.c
  Description   : Memory manage and initialization for SPARCV8 EMULATOR
  Author        : Monahopoulos Konstantinos
  ------------------------------------------------------------------------------------------------------------------------------------------
*/
/*
  ----------------------------------------------------------------------------------------------------------------------------------------
  Includes
  ----------------------------------------------------------------------------------------------------------------------------------------
*/

#include "EMU_MEMORY.h"


///////////////////////////////////////////////////////////////////////////////// PROGRAM MEMORY //////////////////////////////////////////////////////////////////////////////////////////


ULONG* emu_memory_program_return_ptr(void)
{
    return (ULONG*)emu_memory_program_ptr;
}

ULONG* emu_memory_stack_return_ptr(void)
{
    return (ULONG*)emu_memory_stack_ptr;
}

/* INITIALIZATION OF PROGRAM MEMORY UNIT */

void emu_memory_program_init(void)
{
    emu_memory_program_ptr=(int*)malloc(100*sizeof(int)); /* 100 COMMANDS MAX */
}

/* LOAD WORD FROM PROGRAM MEMORY */

INT32 emu_memory_program_load_word(ULONG emu_memory_data_offset)
{
    return  *(UINT32*)(((UINT8*)emu_memory_program_ptr + emu_memory_data_offset));
}

/* STORE UNSIGNED WORD TO PROGRAM MEMORY */

void emu_memory_program_store_word(ULONG data_to_memory,ULONG emu_memory_data_offset)
{
    *(ULONG*)((UINT8*) emu_memory_program_ptr + emu_memory_data_offset )=data_to_memory;
}

///////////////////////////////////////////////////////////////////////////////// DATA MEMORY //////////////////////////////////////////////////////////////////////////////////////////

/* INITIALIZATION OF DATA MEMORY UNIT */

void emu_memory_data_init(void)
{
    emu_memory_data_ptr=(int*)malloc((128/4)*(1024)*sizeof(int)); /*MEMORY ADDRESS SPACE. OFFICIAL 2^32 IN MY CASE 128MB*/
}

///////////////////////////////////////////////////////////////////////////////// STACK MEMORY //////////////////////////////////////////////////////////////////////////////////////////


/*INITIALIZE STACK ADDRESS SPACE*/

void emu_memory_data_stack_init(ULONG WIM)
{
    emu_memory_stack_ptr=malloc(WIM*(96)*sizeof(char)); /* 168 (32-BIT) ADDRESSES */
     UINT32 end_of_memory_block=_msize(emu_memory_stack_ptr);
     emu_memory_stack_ptr+=end_of_memory_block; /*POINTS AT THE END OF STACK AVAILABLE FOR FIRST WINDOW (WINDOW-7)*/
}


/* LOAD SIGNED BYTE FROM MEMORY */

INT8 emu_memory_data_load_signed_byte(ULONG emu_memory_data_offset,ULONG byte_offset)
{
    return    *(INT8*)((UINT8*)(emu_memory_data_ptr + emu_memory_data_offset) + byte_offset);

}

/* LOAD SIGNED HALFWORD FROM MEMORY */

INT16 emu_memory_data_load_signed_halfword(ULONG emu_memory_data_offset,ULONG halfword_offset)
{
    return    *(INT16*)(((UINT8*)emu_memory_data_ptr + emu_memory_data_offset) + (halfword_offset >> 1));
}

/* LOAD SIGNED BYTE FROM MEMORY */

UINT8 emu_memory_data_load_unsigned_byte(ULONG emu_memory_data_offset,ULONG byte_offset)
{
    return    *(UINT8*)(((UINT8*)emu_memory_data_ptr + emu_memory_data_offset) + byte_offset);
}

/* LOAD UNSIGNED BYTE FROM MEMORY */

UINT16 emu_memory_data_load_unsigned_halfword(ULONG emu_memory_data_offset,ULONG halfword_offset)
{

    return    *(UINT16*)(((UINT8*)emu_memory_data_ptr + emu_memory_data_offset) + (halfword_offset >> 1));
}

/* LOAD WORD FROM MEMORY */

INT32 emu_memory_data_load_word(ULONG emu_memory_data_offset)
{
    return    *(UINT32*)(((UINT8*)emu_memory_data_ptr + emu_memory_data_offset));
}

/* LOAD DOUBLEWORD FROM MEMORY */

UINT32 emu_memory_data_load_doubleword(ULONG emu_memory_data_offset,INT8 significant_word)
{
    /* 0 MEANS LSW, 1 MEANS MSW  */

    return  *(UINT32*)( ((UINT8*)emu_memory_data_ptr + emu_memory_data_offset) + 1 - significant_word );
}

/* LOAD FLOATING POINT FROM MEMORY */

FLOAT32 emu_memory_data_load_floating_point(ULONG emu_memory_data_offset)
{
    return    *(FLOAT32*)(((UINT8*)emu_memory_data_ptr + emu_memory_data_offset));
}

/* LOAD DOUBLE FLOATING POINT FROM MEMORY */

FLOAT32 emu_memory_data_load_double_floating_point(ULONG emu_memory_data_offset,INT8 significant_word)
{
    /* 0 MEANS LSW, 1 MEANS MSW  */
    return  *(FLOAT32*)( ((UINT8*)emu_memory_data_ptr + emu_memory_data_offset) + 1 - significant_word );
}

/* STORE UNSIGNED BYTE TO MEMORY */

void emu_memory_data_store_byte(ULONG data_to_memory,ULONG emu_memory_data_offset)
{
    *(UINT8*) ( ((UINT8*)emu_memory_data_ptr + emu_memory_data_offset) + 3 - (emu_memory_data_offset & 0x03) ) = data_to_memory;
}

/* STORE UNSIGNED HALFWORD TO MEMORY */

void emu_memory_data_store_halfword(ULONG data_to_memory,ULONG emu_memory_data_offset)
{
    *(UINT16*) ( ((UINT8*)emu_memory_data_ptr + emu_memory_data_offset) + 3 - (emu_memory_data_offset & 0x03) ) = data_to_memory;
}

/* STORE UNSIGNED WORD TO MEMORY */

void emu_memory_data_store_word(ULONG data_to_memory,ULONG emu_memory_data_offset)
{
    *(ULONG*)((UINT8*) emu_memory_data_ptr + emu_memory_data_offset )=data_to_memory;
}

/* STORE DOUBLEWORD TO MEMORY */

void emu_memory_data_store_doubleword(ULONG data_to_memory,ULONG emu_memory_data_offset,INT8 significant_word)
{
    /* 0 MEANS LSW, 1 MEANS MSW  */
    *(ULONG*) (((UINT8*) emu_memory_data_ptr + emu_memory_data_offset ) + 1 -  significant_word) = data_to_memory ;
}

/* LOAD WORD FROM STACK MEMORY */

UINT32 emu_memory_stack_load_word(ULONG stack_memory_data_offset)
{
    return    *(UINT32*)(((UINT8*)emu_memory_stack_ptr + stack_memory_data_offset));
}

/* STORE WORD TO STACK MEMORY */

void emu_memory_stack_store_word(ULONG data_to_memory,ULONG stack_memory_data_offset)
{
    *(ULONG*)((UINT8*) emu_memory_stack_ptr + stack_memory_data_offset )=data_to_memory;
}
