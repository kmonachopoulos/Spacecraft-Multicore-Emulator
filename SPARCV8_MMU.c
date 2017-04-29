/*
  ------------------------------------------------------------------------------------------------------------------------------------------
  Project       : Sparc_V8 Emulator
  File          : SPARCV8_MMU.c
  Description   : Sparc V8 Memory Managment Unit implementation
  Author        : Monachopoulos Konstantinos
  ------------------------------------------------------------------------------------------------------------------------------------------
*/
/*
  ----------------------------------------------------------------------------------------------------------------------------------------
  Includes
  ----------------------------------------------------------------------------------------------------------------------------------------
*/

#include "SPARCV8_MMU.h"
#include "EMU_MEMORY.h"

/* SAME FUNCTION NAMES WITH EMU_MEMORY, MMU CALLS THE MEMORY FUNCTIONS */

void sparcv8_mmu_memory_data_main_init(void)
{
    emu_memory_data_init();

}

void sparcv8_mmu_memory_data_stack_init(ULONG WIM)
{
    emu_memory_data_stack_init(WIM);
}

void sparcv8_mmu_memory_program_main_init(void)
{
    emu_memory_program_init();
}

ULONG* sparcv8_mmu_memory_program_return_ptr(void)
{

    return emu_memory_program_return_ptr();
}

ULONG* sparcv8_mmu_memory_stack_return_ptr(void)
{
     return emu_memory_stack_return_ptr();
}

INT8 sparcv8_mmu_memory_data_load_signed_byte(ULONG address,ULONG byte_offset)
{
    return emu_memory_data_load_signed_byte(address,byte_offset);
}

INT16 sparcv8_mmu_memory_data_load_signed_halfword(ULONG address,ULONG halfword_offset)
{
    return emu_memory_data_load_signed_halfword(address,halfword_offset);
}

UINT8 sparcv8_memory_load_unsigned_byte(ULONG address,ULONG byte_offset)
{
    return emu_memory_data_load_unsigned_byte(address,byte_offset);
}

UINT16 sparcv8_mmu_memory_data_load_unsigned_halfword(ULONG address,ULONG halfword_offset)
{
    return emu_memory_data_load_unsigned_halfword(address,halfword_offset);
}

INT32 sparcv8_mmu_memory_data_load_word(ULONG address)
{
    return emu_memory_data_load_word(address);
}

UINT32 sparcv8_mmu_memory_data_load_doubleword(ULONG address,INT8 significant_word)
{
    return emu_memory_data_load_doubleword(address,significant_word);
}

FLOAT32 sparcv8_mmu_memory_data_load_floating_point(ULONG address)
{
    return emu_memory_data_load_floating_point( address);
}

FLOAT32 sparcv8_mmu_memory_data_load_double_floating_point(ULONG address,INT8 significant_word)
{
    return emu_memory_data_load_double_floating_point( address, significant_word);
}

void sparcv8_mmu_memory_data_store_byte(ULONG data_to_memory,ULONG emu_memory_main_ptr)
{
    emu_memory_data_store_byte( data_to_memory, emu_memory_main_ptr);
}

void sparcv8_mmu_memory_data_store_halfword(ULONG data_to_memory,ULONG emu_memory_main_ptr)
{
    emu_memory_data_store_halfword( data_to_memory, emu_memory_main_ptr);
}

void sparcv8_mmu_memory_data_store_word(ULONG data_to_memory,ULONG emu_memory_main_ptr)
{
    emu_memory_data_store_word( data_to_memory, emu_memory_main_ptr);
}

void sparcv8_mmu_memory_data_store_doubleword(ULONG data_to_memory,ULONG emu_memory_main_ptr,INT8 significant_word)
{
    emu_memory_data_store_doubleword( data_to_memory, emu_memory_main_ptr, significant_word);

}

UINT32 sparcv8_mmu_memory_stack_load_word(ULONG stack_address)
{
 return emu_memory_stack_load_word(stack_address);
}

void sparcv8_mmu_memory_stack_store_word(ULONG data_to_memory,ULONG emu_memory_main_ptr)
{
       emu_memory_stack_store_word( data_to_memory, emu_memory_main_ptr);
}

UINT32 sparcv8_mmu_memory_program_load_word(ULONG address)
{
    return emu_memory_program_load_word(address);
}

void sparcv8_mmu_memory_program_store_word(ULONG data_to_memory,ULONG emu_memory_main_ptr)
{
    emu_memory_program_store_word( data_to_memory, emu_memory_main_ptr);
}


