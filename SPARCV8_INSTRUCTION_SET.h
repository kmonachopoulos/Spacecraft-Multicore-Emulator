#ifndef SPARCV8_INSTRUCTION_SET_H_INCLUDED
#define SPARCV8_INSTRUCTION_SET_H_INCLUDED

/*
  --------------------------------------------------------------------------------------------------
  Includes
  --------------------------------------------------------------------------------------------------
*/

#include "TYPES.h"
#include "HELPER.h"
/*
  --------------------------------------------------------------------------------------------------
  Enums
  --------------------------------------------------------------------------------------------------
*/

/* REFERENCE NAMES TO REGISTERS */

enum PSRfield {IMPL,VERPSR,ICC_ALL,ICC_NEGATIVE,ICC_ZERO,ICC_OVERFLOW,ICC_CARRY,RESERVED,EC,EF,PIL,S,PS,ET,CWP,PSRALL};
enum WIMfield {WIMBIT,WIMALL};
enum TBRfield {TBA,TT,ZERO,TBRALL};
enum ASRfield {ASRBIT,ASRALL};
enum FSRfield {RD,UHIGH,TEM,NS,RES,VERFSR,FTT,QNE,ULOW,FCC,AEXC,CEXC,FSRALL};
enum CSRfield {CSRBIT,CSRALL};
enum Yfield   {YBIT,YALL};
enum PCfield  {PCBIT,PCALL};
enum NPCfield  {NPCBIT,NPCALL};

/*
  --------------------------------------------------------------------------------------------------
  Structures
  --------------------------------------------------------------------------------------------------
*/

struct SPARCV8_INST_SET_INTERFACE_SIGNALS  /* NON HARDWARE INTERFACE SIGNALS STRUCT */
{
    INT8 bp_IRL;
    INT8 bp_reset_in;
    INT8 pb_error;
    INT8 pb_block_ldst_word;
    INT8 pb_block_ldst_byte;
    INT8 bp_FPU_present;
    INT8 bp_FPU_exception;
    INT8 bp_FPU_cc;
    INT8 bp_CP_present;
    INT8 bp_CP_exception;
    INT8 bp_CP_cc;
};

struct SPARCV8_INST_SET_INTERFACE_SIGNALS sparcv8_inst_set_interface_signals_ctx;
struct SPARCV8_INST_SET_INTERFACE_SIGNALS *interface_signals_ptr;


typedef void* (*instruction_pointer) (void*); /* FUNCTION POINTER */
struct SPARCV8_INST_SET_FUNCTIONS_INDEX  /* FUNCTION POINTER ARRAYS STRUCT */
{
    instruction_pointer instruction_ptr_op0[1][5];
    instruction_pointer instruction_ptr_op1;
    instruction_pointer instruction_ptr_op2[15][4];
    instruction_pointer instruction_ptr_op3[15][4];
    instruction_pointer instruction_ptr_table_F5[32][1];
    instruction_pointer instruction_ptr_table_F6[6][1];
    instruction_pointer instruction_ptr_table_F7[15][4];
};

struct SPARCV8_INST_SET_FUNCTIONS_INDEX *instruction_ptr;
struct SPARCV8_INST_SET_FUNCTIONS_INDEX sparcv8_inst_set_functions_index_ctx;


/*
  --------------------------------------------------------------------------------------------------
  Function Prototyping
  --------------------------------------------------------------------------------------------------
*/

/* DATA TRANSFER BASE EXTRA FUNCTIONS DECLARATION */

ULONG sparcv8_inst_set_extra_RDPSR(enum PSRfield field);
void sparcv8_inst_set_extra_WRPSR(enum PSRfield field,INT32 value);
ULONG sparcv8_inst_set_extra_RDWIM(INT32 bitnumber,enum WIMfield field);
void sparcv8_inst_set_extra_WRWIM(INT32 bitnumber,enum WIMfield field,INT32 value);
ULONG sparcv8_inst_set_extra_RDTBR(enum TBRfield field);
void sparcv8_inst_set_extra_WRTBR(enum TBRfield field,INT32 value);
ULONG sparcv8_inst_set_extra_RDASR(INT32 bitnumber,enum ASRfield field);
void sparcv8_inst_set_extra_WRASR(INT32 bitnumber,enum ASRfield field,INT32 value);
ULONG sparcv8_inst_set_extra_RDFSR(enum FSRfield field);
void sparcv8_inst_set_extra_WRFSR(enum FSRfield field,INT32 value);
ULONG sparcv8_inst_set_extra_RDCSR(INT32 bitnumber,enum CSRfield field);
void sparcv8_inst_set_extra_WRCSR(INT32 bitnumber,enum CSRfield field,INT32 value);
ULONG sparcv8_inst_set_extra_RDY(INT32 bitnumber,enum Yfield field);
void sparcv8_inst_set_extra_WRY(INT32 bitnumber,enum Yfield field,INT32 value);
ULONG sparcv8_inst_set_extra_RPC(INT32 bitnumber,enum PCfield field);
void sparcv8_inst_set_extra_WRPC(INT32 bitnumber,enum Yfield field,INT32 value);
ULONG sparcv8_inst_set_extra_RnPC(INT32 bitnumber,enum NPCfield field);
void sparcv8_inst_set_extra_WRnPC(INT32 bitnumber,enum NPCfield field,INT32 value);
ULONG* sparcv8_inst_set_extra_CALL_PC(void);

/* DATA TRANSFER FUNCTIONS DECLARATION */

void sparcv8_inst_set_RDASR_or_RDY_or_STBAR(ULONG instruction_field);
void sparcv8_inst_set_WRASR_or_WRY(ULONG instruction_field);
void sparcv8_inst_set_WRPSR(ULONG instruction_field);
void sparcv8_inst_set_WRWIM(ULONG instruction_field);
void sparcv8_inst_set_WRTBR(ULONG instruction_field);
void sparcv8_inst_set_RDPSR(ULONG instruction_field);
void sparcv8_inst_set_RDWIM(ULONG instruction_field);
void sparcv8_inst_set_RDTBR(ULONG instruction_field);

/*  INTEGER ARITHMETIC FUNCTIONS DECLARATION */

void sparcv8_inst_set_ADD(ULONG infunc_instruction);
void sparcv8_inst_set_ADDX(ULONG instruction_field);
void sparcv8_inst_set_SLL(ULONG instruction_field);
void sparcv8_inst_set_SRL(ULONG instruction_field);
void sparcv8_inst_set_SRA(ULONG instruction_field);
void sparcv8_inst_set_SUB(ULONG instruction_field);
void sparcv8_inst_set_SUBX(ULONG instruction_field);
void sparcv8_inst_set_AND(ULONG instruction_field);
void sparcv8_inst_set_NAND(ULONG instruction_field);
void sparcv8_inst_set_OR(ULONG instruction_field);
void sparcv8_inst_set_NOR(ULONG instruction_field);
void sparcv8_inst_set_XOR(ULONG instruction_field);
void sparcv8_inst_set_XNOR(ULONG instruction_field);
void sparcv8_inst_set_SETHI_or_NOP(ULONG instruction_field);
void sparcv8_inst_set_UMUL(ULONG instruction_field);
void sparcv8_inst_set_SMUL(ULONG instruction_field);
void sparcv8_inst_set_UDIV(ULONG instruction_field);
void sparcv8_inst_set_SDIV(ULONG instruction_field);

/*  CONTROL TRANSFER FUNCTIONS DECLARATION */

void sparcv8_inst_set_CALL(ULONG instruction_field);
void sparcv8_inst_set_SAVE(ULONG instruction_field);
void sparcv8_inst_set_RESTORE(ULONG instruction_field);
void sparcv8_inst_set_BICC(ULONG instruction_field);
void sparcv8_inst_set_FBFCC(ULONG instruction_field);
void sparcv8_inst_set_CBCCC(ULONG instruction_field);
void sparcv8_inst_set_JMPL(ULONG instruction_field);
void sparcv8_inst_set_TICC(ULONG instruction_field);

/*  LOAD - STORE FUNCTIONS DECLARATION */

void sparcv8_inst_set_LDSB(ULONG instruction_field);
void sparcv8_inst_set_LDSH(ULONG instruction_field);
void sparcv8_inst_set_LDUB(ULONG instruction_field);
void sparcv8_inst_set_LDUH(ULONG instruction_field);
void sparcv8_inst_set_LD(ULONG instruction_field);
void sparcv8_inst_set_LDD(ULONG instruction_field);
void sparcv8_inst_set_LDF(ULONG instruction_field);
void sparcv8_inst_set_LDDF(ULONG instruction_field);
void sparcv8_inst_set_LDFSR(ULONG instruction_field);
void sparcv8_inst_set_LDC(ULONG instruction_field);
void sparcv8_inst_set_LDDC(ULONG instruction_field);
void sparcv8_inst_set_LDCSR(ULONG instruction_field);
void sparcv8_inst_set_STB(ULONG instruction_field);
void sparcv8_inst_set_STH(ULONG instruction_field);
void sparcv8_inst_set_ST(ULONG instruction_field);
void sparcv8_inst_set_STD(ULONG instruction_field);
void sparcv8_inst_set_STF(ULONG instruction_field);
void sparcv8_inst_set_STDF(ULONG instruction_field);
void sparcv8_inst_set_STFSR(ULONG instruction_field);
void sparcv8_inst_set_STC(ULONG instruction_field);
void sparcv8_inst_set_STDC(ULONG instruction_field);
void sparcv8_inst_set_STCSR(ULONG instruction_field);

/*  FLOATING POINT FUNCTIONS DECLARATION */

/*  COPROCESSOR OPERATE FUNCTIONS DECLARATION */

/*  ADDITIONAL INSTRUCTION SET FUNCTION DECLARATION */

void sparcv8_inst_set_additional_ADDCC(ULONG instruction_field);
void sparcv8_inst_set_additional_ADDXCC(ULONG instruction_field);
void sparcv8_inst_set_additional_SUBCC(ULONG instruction_field);
void sparcv8_inst_set_additional_SUBXCC(ULONG instruction_field);
void sparcv8_inst_set_additional_ANDCC(ULONG instruction_field);
void sparcv8_inst_set_additional_NANDCC(ULONG instruction_field);
void sparcv8_inst_set_additional_ORCC(ULONG instruction_field);
void sparcv8_inst_set_additional_NORCC(ULONG instruction_field);
void sparcv8_inst_set_additional_XORCC(ULONG instruction_field);
void sparcv8_inst_set_additional_XNORCC(ULONG instruction_field);
void sparcv8_inst_set_additional_MULSCC(ULONG instruction_field);
void sparcv8_inst_set_additional_UMULCC(ULONG instruction_field);
void sparcv8_inst_set_additional_SMULCC(ULONG instruction_field);
void sparcv8_inst_set_additional_UDIVCC(ULONG instruction_field);
void sparcv8_inst_set_additional_SDIVCC(ULONG instruction_field);
void sparcv8_inst_set_initialize_interface_signals(struct SPARCV8_INST_SET_INTERFACE_SIGNALS *interface_signals_tmp_ptr);
void sparcv8_instruction_set_initialize_function_ptr(struct SPARCV8_INST_SET_FUNCTIONS_INDEX *instruction_tmp_ptr);
void sparcv8_inst_set_default_inst(ULONG instruction_field);



#endif // SPARCV8_INSTRUCTION_SET_H_INCLUDED
