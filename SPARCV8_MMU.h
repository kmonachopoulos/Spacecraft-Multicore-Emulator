#ifndef SPARCV8_MMU_H_INCLUDED
#define SPARCV8_MMU_H_INCLUDED

/*
  --------------------------------------------------------------------------------------------------
  Includes
  --------------------------------------------------------------------------------------------------
*/

#include "TYPES.h"

/*
  --------------------------------------------------------------------------------------------------
  Function Prototyping
  --------------------------------------------------------------------------------------------------
*/

ULONG* sparcv8_mmu_memory_program_return_ptr(void);
ULONG* sparcv8_mmu_memory_stack_return_ptr(void);
void sparcv8_mmu_memory_data_stack_init(ULONG wim);
void sparcv8_mmu_memory_data_main_init(void);
INT8 sparcv8_mmu_memory_data_load_signed_byte(ULONG address,ULONG byte_offset);
INT16 sparcv8_mmu_memory_data_load_signed_halfword(ULONG address,ULONG halfword_offset);
UINT8 sparcv8_memory_load_unsigned_byte(ULONG address,ULONG byte_offset);
UINT16 sparcv8_mmu_memory_data_load_unsigned_halfword(ULONG address,ULONG halfword_offset);
INT32 sparcv8_mmu_memory_data_load_word(ULONG address);
UINT32 sparcv8_mmu_memory_data_load_doubleword(ULONG address,INT8 significant_word);
FLOAT32 sparcv8_mmu_memory_data_load_floating_point(ULONG address);
FLOAT32 sparcv8_mmu_memory_data_load_double_floating_point(ULONG address,INT8 significant_word);
void sparcv8_mmu_memory_data_store_byte(ULONG data_to_memory,ULONG emu_memory_main_ptr);
void sparcv8_mmu_memory_data_store_halfword(ULONG data_to_memory,ULONG emu_memory_main_ptr);
void sparcv8_mmu_memory_data_store_word(ULONG data_to_memory,ULONG emu_memory_main_ptr);
void sparcv8_mmu_memory_data_store_doubleword(ULONG data_to_memory,ULONG emu_memory_main_ptr,INT8 significant_word);
UINT32 sparcv8_mmu_memory_stack_load_word(ULONG stack_address);
void sparcv8_mmu_memory_stack_store_word(ULONG data_to_memory,ULONG emu_memory_main_ptr);
void sparcv8_mmu_memory_program_main_init(void);
UINT32 sparcv8_mmu_memory_program_load_word(ULONG address);
void sparcv8_mmu_memory_program_store_word(ULONG data_to_memory,ULONG emu_memory_main_ptr);


#endif // SPARCV8_MMU_H_INCLUDED
