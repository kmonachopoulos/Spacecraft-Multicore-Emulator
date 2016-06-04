#ifndef EMU_MEMORY_H_INCLUDED
#define EMU_MEMORY_H_INCLUDED

/*
  --------------------------------------------------------------------------------------------------
  Includes
  --------------------------------------------------------------------------------------------------
*/

#include "TYPES.h"


void *emu_memory_data_ptr; /* POINTER TO MAIN MEMORY IS GLOBAL */
void *emu_memory_stack_ptr; /* POINTER TO STACK MEMORY IS GLOBAL */
void *emu_memory_program_ptr; /* POINTER TO PROGRAM MEMORY IS GLOBAL */
/*
  --------------------------------------------------------------------------------------------------
  Function Prototyping
  --------------------------------------------------------------------------------------------------
*/

ULONG* emu_memory_program_return_ptr(void);
ULONG* emu_memory_stack_return_ptr(void);
void emu_memory_data_init(void);
void emu_memory_data_stack_init(ULONG WIM);
INT8 emu_memory_data_load_signed_byte(ULONG emu_memory_data_offset,ULONG halfword_offset);
INT16 emu_memory_data_load_signed_halfword(ULONG emu_memory_data_offset,ULONG halfword_offset);
UINT8 emu_memory_data_load_unsigned_byte(ULONG emu_memory_data_offset,ULONG byte_offset);
UINT16 emu_memory_data_load_unsigned_halfword(ULONG emu_memory_data_offset,ULONG halfword_offset);
INT32 emu_memory_data_load_word(ULONG emu_memory_data_offset);
UINT32 emu_memory_data_load_doubleword(ULONG emu_memory_data_offset,INT8 significant_word);
FLOAT32 emu_memory_data_load_floating_point(ULONG emu_memory_data_offset);
FLOAT32 emu_memory_data_load_double_floating_point(ULONG emu_memory_data_offset,INT8 significant_word);
void emu_memory_data_store_byte(ULONG data_to_memory,ULONG emu_memory_data_offset);
void emu_memory_data_store_halfword(ULONG data_to_memory,ULONG emu_memory_data_offset);
void emu_memory_data_store_word(ULONG data_to_memory,ULONG emu_memory_data_offset);
void emu_memory_data_store_doubleword(ULONG data_to_memory,ULONG emu_memory_data_offset,INT8 significant_word);
UINT32 emu_memory_stack_load_word(ULONG stack_memory_data_offset);
void emu_memory_stack_store_word(ULONG data_to_memory,ULONG stack_memory_data_offset);

void emu_memory_program_init(void);
INT32 emu_memory_program_load_word(ULONG emu_memory_data_offset);
void emu_memory_program_store_word(ULONG data_to_memory,ULONG emu_memory_data_offset);


#endif // EMU_MEMORY_H_INCLUDED
