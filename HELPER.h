#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

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

ULONG helper_Byteswap(ULONG Littleendian);
char* helper_ulong32_to_char(ULONG buffer);
ULONG helper_char_to_ulong32(char* bits);
ULONG helper_write_value(INT32 startbit,INT32 lastbit,ULONG buffer,INT32 value);
ULONG helper_read_value(INT32 firstbit,INT32 lastbit,ULONG buffer);
ULONG helper_unsigned_ll_msw(DOUBLE64 value);
ULONG helper_unsigned_ll_lsw(DOUBLE64 value);

/* READ INSTRUCTION FIELD FUNCTIONS DECLARATION */

ULONG helper_instruction_field_disp30(ULONG instruction);
ULONG helper_instruction_field_op(ULONG instruction);
ULONG helper_instruction_field_rd(ULONG instruction);
ULONG helper_instruction_field_op2(ULONG instruction);
ULONG helper_instruction_field_a(ULONG instruction);
ULONG helper_instruction_field_cond(ULONG instruction);
ULONG helper_instruction_field_imm22(ULONG instruction);
ULONG helper_instruction_field_disp22(ULONG instruction);
ULONG helper_instruction_field_op3(ULONG instruction);
ULONG helper_instruction_field_rs1(ULONG instruction);
ULONG helper_instruction_field_i(ULONG instruction);
ULONG helper_instruction_field_asi(ULONG instruction);
ULONG helper_instruction_field_rs2(ULONG instruction);
UINT32 helper_instruction_field_usimm13(ULONG instruction);
ULONG helper_instruction_field_simm13(ULONG instruction);
ULONG helper_instruction_field_sign_ext_simm13(ULONG instruction);
ULONG helper_instruction_field_opf(ULONG instruction);
ULONG helper_instruction_field_uimm7(ULONG instruction);
UINT32 helper_instruction_field_imm7(ULONG instruction);

#endif // HELPER_H_INCLUDED
