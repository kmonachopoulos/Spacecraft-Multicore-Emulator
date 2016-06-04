
/*
  ------------------------------------------------------------------------------------------------------------------------------------------
  ExcelMicroTechnologies - emtech
  Copyright 2013-2014
  ------------------------------------------------------------------------------------------------------------------------------------------
*/
/*
  ------------------------------------------------------------------------------------------------------------------------------------------
  Project       : Sparc_V8 Emulator
  File          : SPARCV8_INSTRUCTION_SET.c
  Description   : Sparc V8 instruction set
  Author        : Monahopoulos Konstantinos
  ------------------------------------------------------------------------------------------------------------------------------------------
*/
/*
  ----------------------------------------------------------------------------------------------------------------------------------------
  Includes
  ----------------------------------------------------------------------------------------------------------------------------------------
*/

#include "SPARCV8_INSTRUCTION_SET.h"
#include "SPARCV8_TRAPS.h"
#include "SPARCV8_PROC.h"



void sparcv8_instruction_set_initialize_function_ptr(struct SPARCV8_INST_SET_FUNCTIONS_INDEX *instruction_tmp_ptr)
{
    /* CASE OP=0 */
    instruction_tmp_ptr->instruction_ptr_op0[0][0] = (void* (*) (void*) )sparcv8_inst_set_default_inst; /* NEEDS UNIMP */
    instruction_tmp_ptr->instruction_ptr_op0[0][1] = (void* (*) (void*) ) sparcv8_inst_set_BICC;
    instruction_tmp_ptr->instruction_ptr_op0[0][2] = (void* (*) (void*) ) sparcv8_inst_set_SETHI_or_NOP;
    instruction_tmp_ptr->instruction_ptr_op0[0][3] = (void* (*) (void*) ) sparcv8_inst_set_FBFCC;
    instruction_tmp_ptr->instruction_ptr_op0[0][4] = (void* (*) (void*) ) sparcv8_inst_set_CBCCC;
    /* CASE OP=1 */
    instruction_tmp_ptr->instruction_ptr_op1=(void* (*) (void*) )sparcv8_inst_set_CALL;
    /* CASE OP=2 */
    instruction_tmp_ptr->instruction_ptr_op2[0][0]=(void* (*) (void*) )sparcv8_inst_set_ADD;
    instruction_tmp_ptr->instruction_ptr_op2[1][0]=(void* (*) (void*) )sparcv8_inst_set_AND;
    instruction_tmp_ptr->instruction_ptr_op2[2][0]=(void* (*) (void*) )sparcv8_inst_set_OR;
    instruction_tmp_ptr->instruction_ptr_op2[3][0]=(void* (*) (void*) )sparcv8_inst_set_XOR;
    instruction_tmp_ptr->instruction_ptr_op2[4][0]=(void* (*) (void*) )sparcv8_inst_set_SUB;
    instruction_tmp_ptr->instruction_ptr_op2[5][0]=(void* (*) (void*) )sparcv8_inst_set_NAND;
    instruction_tmp_ptr->instruction_ptr_op2[6][0]=(void* (*) (void*) )sparcv8_inst_set_NOR;
    instruction_tmp_ptr->instruction_ptr_op2[7][0]=(void* (*) (void*) )sparcv8_inst_set_XNOR;
    instruction_tmp_ptr->instruction_ptr_op2[8][0]=(void* (*) (void*) )sparcv8_inst_set_ADDX;
    instruction_tmp_ptr->instruction_ptr_op2[9][0]=(void* (*) (void*) )sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op2[10][0]=(void* (*) (void*) )sparcv8_inst_set_UMUL;
    instruction_tmp_ptr->instruction_ptr_op2[11][0]=(void* (*) (void*) )sparcv8_inst_set_SMUL;
    instruction_tmp_ptr->instruction_ptr_op2[12][0]=(void* (*) (void*) )sparcv8_inst_set_SUBX;
    instruction_tmp_ptr->instruction_ptr_op2[13][0]=(void* (*) (void*) )sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op2[14][0]=(void* (*) (void*) ) sparcv8_inst_set_UDIV;
    instruction_tmp_ptr->instruction_ptr_op2[15][0]=(void* (*) (void*) )sparcv8_inst_set_SDIV;
    instruction_tmp_ptr->instruction_ptr_op2[0][1]=(void* (*) (void*) )sparcv8_inst_set_additional_ADDCC;
    instruction_tmp_ptr->instruction_ptr_op2[2][1]=(void* (*) (void*) )sparcv8_inst_set_additional_ANDCC;
    instruction_tmp_ptr->instruction_ptr_op2[3][1]=(void* (*) (void*) )sparcv8_inst_set_additional_ORCC;
    instruction_tmp_ptr->instruction_ptr_op2[4][1]=(void* (*) (void*) )sparcv8_inst_set_additional_XORCC;
    instruction_tmp_ptr->instruction_ptr_op2[5][1]=(void* (*) (void*) )sparcv8_inst_set_additional_SUBCC;
    instruction_tmp_ptr->instruction_ptr_op2[6][1]=(void* (*) (void*) )sparcv8_inst_set_additional_NANDCC;
    instruction_tmp_ptr->instruction_ptr_op2[7][1]=(void* (*) (void*) )sparcv8_inst_set_additional_XNORCC;
    instruction_tmp_ptr->instruction_ptr_op2[8][1]=(void* (*) (void*) )sparcv8_inst_set_additional_ADDXCC;
    instruction_tmp_ptr->instruction_ptr_op2[9][1]=(void* (*) (void*) )sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op2[10][1]=(void* (*) (void*) )sparcv8_inst_set_additional_UMULCC;
    instruction_tmp_ptr->instruction_ptr_op2[11][1]=(void* (*) (void*) )sparcv8_inst_set_additional_SMULCC;
    instruction_tmp_ptr->instruction_ptr_op2[12][1]=(void* (*) (void*) )sparcv8_inst_set_additional_SUBXCC;
    instruction_tmp_ptr->instruction_ptr_op2[13][1]=(void* (*) (void*) )sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op2[14][1]=(void* (*) (void*) )sparcv8_inst_set_additional_UDIVCC;
    instruction_tmp_ptr->instruction_ptr_op2[15][1]=(void* (*) (void*) )sparcv8_inst_set_additional_SDIVCC;
    instruction_tmp_ptr->instruction_ptr_op2[0][2]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS TADDCC */
    instruction_tmp_ptr->instruction_ptr_op2[1][2]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS TSUBCC */
    instruction_tmp_ptr->instruction_ptr_op2[2][2]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS TADDCCTV */
    instruction_tmp_ptr->instruction_ptr_op2[3][2]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS TSUBCCTV */
    instruction_tmp_ptr->instruction_ptr_op2[4][2]=(void* (*) (void*) ) sparcv8_inst_set_additional_MULSCC;
    instruction_tmp_ptr->instruction_ptr_op2[5][2]=(void* (*) (void*) ) sparcv8_inst_set_SLL;
    instruction_tmp_ptr->instruction_ptr_op2[6][2]=(void* (*) (void*) ) sparcv8_inst_set_SRL;
    instruction_tmp_ptr->instruction_ptr_op2[7][2]=(void* (*) (void*) ) sparcv8_inst_set_SRA;
    instruction_tmp_ptr->instruction_ptr_op2[8][2]=(void* (*) (void*) ) sparcv8_inst_set_RDASR_or_RDY_or_STBAR;
    instruction_tmp_ptr->instruction_ptr_op2[9][2]=(void* (*) (void*) ) sparcv8_inst_set_extra_RDPSR;
    instruction_tmp_ptr->instruction_ptr_op2[10][2]=(void* (*) (void*) ) sparcv8_inst_set_extra_RDWIM;
    instruction_tmp_ptr->instruction_ptr_op2[11][2]=(void* (*) (void*) ) sparcv8_inst_set_extra_RDTBR;
    instruction_tmp_ptr->instruction_ptr_op2[12][2]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op2[13][2]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op2[14][2]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op2[15][2]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op2[0][3]=(void* (*) (void*) ) sparcv8_inst_set_WRASR_or_WRY;
    instruction_tmp_ptr->instruction_ptr_op2[1][3]=(void* (*) (void*) ) sparcv8_inst_set_WRPSR;
    instruction_tmp_ptr->instruction_ptr_op2[2][3]=(void* (*) (void*) ) sparcv8_inst_set_WRWIM;
    instruction_tmp_ptr->instruction_ptr_op2[3][3]=(void* (*) (void*) ) sparcv8_inst_set_WRTBR;
    instruction_tmp_ptr->instruction_ptr_op2[4][3]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* SEE TABLE F-5 */
    instruction_tmp_ptr->instruction_ptr_op2[5][3]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* SEE TABLE F-6 */
    instruction_tmp_ptr->instruction_ptr_op2[6][3]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS CPOP1 */
    instruction_tmp_ptr->instruction_ptr_op2[7][3]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS CPOP2 */
    instruction_tmp_ptr->instruction_ptr_op2[8][3]=(void* (*) (void*) ) sparcv8_inst_set_JMPL;
    instruction_tmp_ptr->instruction_ptr_op2[9][3]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS RETT */
    instruction_tmp_ptr->instruction_ptr_op2[10][3]=(void* (*) (void*) ) sparcv8_inst_set_TICC;
    instruction_tmp_ptr->instruction_ptr_op2[11][3]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FLUSH */
    instruction_tmp_ptr->instruction_ptr_op2[12][3]=(void* (*) (void*) ) sparcv8_inst_set_SAVE;
    instruction_tmp_ptr->instruction_ptr_op2[13][3]=(void* (*) (void*) ) sparcv8_inst_set_RESTORE;
    instruction_tmp_ptr->instruction_ptr_op2[14][3]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op2[15][3]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    /* CASE OP=3 */
    instruction_tmp_ptr->instruction_ptr_op3[0][0]=(void* (*) (void*) ) sparcv8_inst_set_LD;
    instruction_tmp_ptr->instruction_ptr_op3[1][0]=(void* (*) (void*) ) sparcv8_inst_set_LDUB;
    instruction_tmp_ptr->instruction_ptr_op3[2][0]=(void* (*) (void*) ) sparcv8_inst_set_LDUH;
    instruction_tmp_ptr->instruction_ptr_op3[3][0]=(void* (*) (void*) ) sparcv8_inst_set_LDD;
    instruction_tmp_ptr->instruction_ptr_op3[4][0]=(void* (*) (void*) ) sparcv8_inst_set_ST;
    instruction_tmp_ptr->instruction_ptr_op3[5][0]=(void* (*) (void*) ) sparcv8_inst_set_STB;
    instruction_tmp_ptr->instruction_ptr_op3[6][0]=(void* (*) (void*) ) sparcv8_inst_set_STH;
    instruction_tmp_ptr->instruction_ptr_op3[7][0]=(void* (*) (void*) ) sparcv8_inst_set_STD;
    instruction_tmp_ptr->instruction_ptr_op3[8][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[9][0]=(void* (*) (void*) ) sparcv8_inst_set_LDSB;
    instruction_tmp_ptr->instruction_ptr_op3[10][0]=(void* (*) (void*) ) sparcv8_inst_set_LDSH;
    instruction_tmp_ptr->instruction_ptr_op3[11][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[12][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[13][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;/* NEEDS LDSTUB */
    instruction_tmp_ptr->instruction_ptr_op3[14][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[15][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS SWAP */
    instruction_tmp_ptr->instruction_ptr_op3[0][1]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS LDA */
    instruction_tmp_ptr->instruction_ptr_op3[1][1]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS LDUBA */
    instruction_tmp_ptr->instruction_ptr_op3[2][1]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS LDUHA */
    instruction_tmp_ptr->instruction_ptr_op3[3][1]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS LDDA */
    instruction_tmp_ptr->instruction_ptr_op3[4][1]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS STA */
    instruction_tmp_ptr->instruction_ptr_op3[5][1]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS STBA */
    instruction_tmp_ptr->instruction_ptr_op3[6][1]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS STHA */
    instruction_tmp_ptr->instruction_ptr_op3[7][1]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS STDA */
    instruction_tmp_ptr->instruction_ptr_op3[8][1]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[9][1]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS LDSBA */
    instruction_tmp_ptr->instruction_ptr_op3[10][1]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS LDSHA */
    instruction_tmp_ptr->instruction_ptr_op3[11][1]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[12][1]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[13][1]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS LDSTUBA */
    instruction_tmp_ptr->instruction_ptr_op3[14][1]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[15][1]=(void* (*) (void*) )sparcv8_inst_set_default_inst; /* NEEDS SWAPA */
    instruction_tmp_ptr->instruction_ptr_op3[0][2]=(void* (*) (void*) ) sparcv8_inst_set_LDF;
    instruction_tmp_ptr->instruction_ptr_op3[1][2]=(void* (*) (void*) ) sparcv8_inst_set_LDFSR;
    instruction_tmp_ptr->instruction_ptr_op3[2][2]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[3][2]=(void* (*) (void*) ) sparcv8_inst_set_LDDF;
    instruction_tmp_ptr->instruction_ptr_op3[4][2]=(void* (*) (void*) ) sparcv8_inst_set_STF;
    instruction_tmp_ptr->instruction_ptr_op3[5][2]=(void* (*) (void*) ) sparcv8_inst_set_STFSR;
    instruction_tmp_ptr->instruction_ptr_op3[6][2]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS STFQ */
    instruction_tmp_ptr->instruction_ptr_op3[7][2]=(void* (*) (void*) ) sparcv8_inst_set_STDF;
    instruction_tmp_ptr->instruction_ptr_op3[8][2]=(void* (*) (void*) )sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[9][2]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[10][2]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[11][2]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[12][2]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[13][2]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[14][2]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[15][2]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[0][3]=(void* (*) (void*) ) sparcv8_inst_set_LDC;
    instruction_tmp_ptr->instruction_ptr_op3[1][3]=(void* (*) (void*) ) sparcv8_inst_set_LDCSR;
    instruction_tmp_ptr->instruction_ptr_op3[2][3]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[3][3]=(void* (*) (void*) ) sparcv8_inst_set_LDDC;
    instruction_tmp_ptr->instruction_ptr_op3[4][3]=(void* (*) (void*) ) sparcv8_inst_set_STC;
    instruction_tmp_ptr->instruction_ptr_op3[5][3]=(void* (*) (void*) ) sparcv8_inst_set_STCSR;
    instruction_tmp_ptr->instruction_ptr_op3[6][3]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS STCQ */
    instruction_tmp_ptr->instruction_ptr_op3[7][3]=(void* (*) (void*) ) sparcv8_inst_set_STDC;
    instruction_tmp_ptr->instruction_ptr_op3[8][3]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[9][3]=(void* (*) (void*) )  sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[10][3]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[11][3]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[12][3]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[13][3]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[14][3]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    instruction_tmp_ptr->instruction_ptr_op3[15][3]=(void* (*) (void*) ) sparcv8_inst_set_default_inst;
    /* CASE OP=2,0P3=0x34 */
    instruction_tmp_ptr->instruction_ptr_table_F5[0][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FMOVS */
    instruction_tmp_ptr->instruction_ptr_table_F5[1][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FNEGS */
    instruction_tmp_ptr->instruction_ptr_table_F5[2][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FABSS */
    instruction_tmp_ptr->instruction_ptr_table_F5[3][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FSQRTS */
    instruction_tmp_ptr->instruction_ptr_table_F5[4][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FSQRTD */
    instruction_tmp_ptr->instruction_ptr_table_F5[5][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FSQRTQ */
    instruction_tmp_ptr->instruction_ptr_table_F5[6][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FADDS */
    instruction_tmp_ptr->instruction_ptr_table_F5[7][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FADDD */
    instruction_tmp_ptr->instruction_ptr_table_F5[8][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FADDQ */
    instruction_tmp_ptr->instruction_ptr_table_F5[9][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FSUBS */
    instruction_tmp_ptr->instruction_ptr_table_F5[10][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FSUBD */
    instruction_tmp_ptr->instruction_ptr_table_F5[11][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FSUBQ */
    instruction_tmp_ptr->instruction_ptr_table_F5[12][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FMULS */
    instruction_tmp_ptr->instruction_ptr_table_F5[13][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FMULD */
    instruction_tmp_ptr->instruction_ptr_table_F5[14][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FMULQ */
    instruction_tmp_ptr->instruction_ptr_table_F5[15][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FDIVS */
    instruction_tmp_ptr->instruction_ptr_table_F5[16][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FDIVD */
    instruction_tmp_ptr->instruction_ptr_table_F5[17][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FDIVQ */
    instruction_tmp_ptr->instruction_ptr_table_F5[18][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FSMULD */
    instruction_tmp_ptr->instruction_ptr_table_F5[19][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FDMULQ */
    instruction_tmp_ptr->instruction_ptr_table_F5[20][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FITOS */
    instruction_tmp_ptr->instruction_ptr_table_F5[21][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FDTOS */
    instruction_tmp_ptr->instruction_ptr_table_F5[22][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FQTOS */
    instruction_tmp_ptr->instruction_ptr_table_F5[23][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FITOD */
    instruction_tmp_ptr->instruction_ptr_table_F5[24][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FSTOD */
    instruction_tmp_ptr->instruction_ptr_table_F5[25][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FQTOD */
    instruction_tmp_ptr->instruction_ptr_table_F5[26][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FITOQ */
    instruction_tmp_ptr->instruction_ptr_table_F5[27][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FSTOQ */
    instruction_tmp_ptr->instruction_ptr_table_F5[28][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FDTOQ */
    instruction_tmp_ptr->instruction_ptr_table_F5[29][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FSTOI */
    instruction_tmp_ptr->instruction_ptr_table_F5[30][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FDTOI */
    instruction_tmp_ptr->instruction_ptr_table_F5[31][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FQTOI */
    /* CASE OP=2,0P3=0x35 */
    instruction_tmp_ptr->instruction_ptr_table_F6[0][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FCMPS */
    instruction_tmp_ptr->instruction_ptr_table_F6[1][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FCMPD */
    instruction_tmp_ptr->instruction_ptr_table_F6[2][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FCMPQ */
    instruction_tmp_ptr->instruction_ptr_table_F6[3][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FCMPES */
    instruction_tmp_ptr->instruction_ptr_table_F6[4][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FCMPED */
    instruction_tmp_ptr->instruction_ptr_table_F6[5][0]=(void* (*) (void*) ) sparcv8_inst_set_default_inst; /* NEEDS FCMPEQ */
    instruction_ptr=instruction_tmp_ptr;

}

void sparcv8_inst_set_initialize_interface_signals(struct SPARCV8_INST_SET_INTERFACE_SIGNALS *interface_signals_tmp_ptr)
{
    interface_signals_tmp_ptr->bp_IRL=0;
    interface_signals_tmp_ptr->bp_reset_in=0;
    interface_signals_tmp_ptr->pb_error=0;
    interface_signals_tmp_ptr->pb_block_ldst_word=0;
    interface_signals_tmp_ptr->pb_block_ldst_byte=0;
    interface_signals_tmp_ptr->bp_FPU_present=0;
    interface_signals_tmp_ptr->bp_FPU_exception=0;
    interface_signals_tmp_ptr->bp_FPU_cc=0;
    interface_signals_tmp_ptr->bp_CP_present=0;
    interface_signals_tmp_ptr->bp_CP_exception=0;
    interface_signals_tmp_ptr->bp_CP_cc=0;
    interface_signals_ptr=interface_signals_tmp_ptr;
}

///////////////////////////////////////////////////////////////// READ/WRITE DATA REGISTER INSTRUCTIONS  ////////////////////////////////////////////////////////////////////////

/* READ VALUE OF PSR (BASE - EXTRA FUNCTION) */

ULONG sparcv8_inst_set_extra_RDPSR(enum PSRfield field)
{
    INT32 startbit;
    INT32 lastbit;
    switch(field)
    {
    case IMPL:
        startbit=28;
        lastbit=31;
        break;
    case VERPSR:
        startbit=24;
        lastbit=27;
        break;
    case ICC_ALL:
        startbit=20;
        lastbit=23;
        break;
    case ICC_NEGATIVE:
        startbit=23;
        lastbit=23;
        break;
    case ICC_ZERO:
        startbit=22;
        lastbit=22;
        break;
    case ICC_OVERFLOW:
        startbit=21;
        lastbit=21;
        break;
    case ICC_CARRY:
        startbit=20;
        lastbit=20;
        break;
    case RESERVED:
        startbit=14;
        lastbit=19;
        break;
    case EC:
        startbit=13;
        lastbit=13;
        break;
    case EF:
        startbit=12;
        lastbit=12;
        break;
    case PIL:
        startbit=8;
        lastbit=11;
        break;
    case S:
        startbit=7;
        lastbit=7;
        break;
    case PS:
        startbit=6;
        lastbit=6;
        break;
    case ET:
        startbit=5;
        lastbit=5;
        break;
    case CWP:
        startbit=0;
        lastbit=4;
        break;
    case PSRALL:
        startbit=0;
        lastbit=31;
        break;
    default:
        printf("not an expected field tag of PSR\n");
        break;
    }
    return helper_read_value(startbit,lastbit,sparc_intunit_ptr->PSR);
}


/* WRITE VALUE TO PSR (BASE - EXTRA FUNCTION) */

void sparcv8_inst_set_extra_WRPSR(enum PSRfield field,INT32 value)
{
    INT32 startbit;
    INT32 lastbit;
    switch(field)
    {
    case IMPL:
        startbit=28;
        lastbit=31;
        break;
    case VERPSR:
        startbit=24;
        lastbit=27;
        break;
    case ICC_ALL:
        startbit=20;
        lastbit=23;
        break;
    case ICC_NEGATIVE:
        startbit=23;
        lastbit=23;
        break;
    case ICC_ZERO:
        startbit=22;
        lastbit=22;
        break;
    case ICC_OVERFLOW:
        startbit=21;
        lastbit=21;
        break;
    case ICC_CARRY:
        startbit=20;
        lastbit=20;
        break;
    case RESERVED:
        startbit=14;
        lastbit=19;
        break;
    case EC:
        startbit=13;
        lastbit=13;
        break;
    case EF:
        startbit=12;
        lastbit=12;
        break;
    case PIL:
        startbit=8;
        lastbit=11;
        break;
    case S:
        startbit=7;
        lastbit=7;
        break;
    case PS:
        startbit=6;
        lastbit=6;
        break;
    case ET:
        startbit=5;
        lastbit=5;
        break;
    case CWP:
        startbit=0;
        lastbit=4;
        break;
    case PSRALL:
        startbit=0;
        lastbit=31;
        break;
    default:
        printf("not an expected field tag of PSR\n");
        break;
    }
    sparc_intunit_ptr->PSR= helper_write_value(startbit,lastbit,sparc_intunit_ptr->PSR,value);
}

/* READ VALUE OF WIM (BASE - EXTRA FUNCTION) */

ULONG sparcv8_inst_set_extra_RDWIM(INT32 bitnumber,enum WIMfield field)
{
    INT32 startbit;
    INT32 lastbit;
    switch(field)
    {
    case WIMBIT:
        startbit=bitnumber;
        lastbit=bitnumber;
        break;
    case WIMALL:
        bitnumber=0;
        startbit=0;
        lastbit=31;
        break;
    default:
        printf("not an expected field tag of WIM\n");
        break;
    }
    return helper_read_value(startbit,lastbit,sparc_intunit_ptr->WIM);
}

/* WRITE VALUE TO WIM (BASE - EXTRA FUNCTION) */

void sparcv8_inst_set_extra_WRWIM(INT32 bitnumber,enum WIMfield field,INT32 value)
{
    INT32 startbit;
    INT32 lastbit;
    switch(field)
    {
    case WIMBIT:
        startbit=bitnumber;
        lastbit=bitnumber;
        break;
    case WIMALL:
        startbit=0;
        lastbit=31;
        break;
    default:
        printf("not an expected field tag of WIM\n");
        break;
    }
    sparc_intunit_ptr->WIM= helper_write_value(startbit,lastbit,sparc_intunit_ptr->WIM,value);
}

/* READ VALUE OF TBR (BASE - EXTRA FUNCTION) */

ULONG sparcv8_inst_set_extra_RDTBR(enum TBRfield field)
{
    INT32 startbit;
    INT32 lastbit;
    switch(field)
    {
    case TBA:
        startbit=12;
        lastbit=31;
        break;
    case TT:
        startbit=4;
        lastbit=11;
        break;
    case ZERO:
        startbit=0;
        lastbit=3;
        break;
    case TBRALL:
        startbit=0;
        lastbit=31;
        break;
    default:
        printf("not an expected field tag of TBR\n");
        break;
    }
    return helper_read_value(startbit,lastbit,sparc_intunit_ptr->TBR);
}

/* WRITE VALUE TO TBR (BASE - EXTRA FUNCTION) */

void sparcv8_inst_set_extra_WRTBR(enum TBRfield field,INT32 value)
{
    INT32 startbit;
    INT32 lastbit;
    switch(field)
    {
    case TBA:
        startbit=12;
        lastbit=31;
        break;
    case TT:
        startbit=4;
        lastbit=11;
        break;
    case ZERO:
        startbit=0;
        lastbit=3;
        break;
    case TBRALL:
        startbit=0;
        lastbit=31;
        break;
    default:
        printf("not an expected field tag of TBR\n");
        break;
    }
    sparc_intunit_ptr->TBR= helper_write_value(startbit,lastbit,sparc_intunit_ptr->TBR,value);
}


/* FUNCTION OF Y REGISTER*/

/*
Function of Y will use the helper  to fetch Most Significant Word of ALU output......
*/

/* READ VALUE OF ASR (BASE - EXTRA FUNCTION) */

ULONG sparcv8_inst_set_extra_RDASR(INT32 bitnumber,enum ASRfield field)
{
    /*  TRAP CATALOGUE FOR JMPL INSTRUCTION
     *  privileged_instruction (except RDY) -- DONE
     *  illegal_instruction (RDASR only; implementation-dependent) -- REMAINING
     */

    if ( sparcv8_inst_set_extra_RDPSR(S) == 0 )
    {
        sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->privileged_instruction);
		sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
        sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
    }

    INT32 startbit;
    INT32 lastbit;
    switch(field)
    {
    case ASRBIT:
        startbit=bitnumber;
        lastbit=bitnumber;
        break;
    case ASRALL:
        bitnumber=0;
        startbit=0;
        lastbit=31;
        break;
    default:
        printf("not an expected field tag of ASR\n");
        break;
    }
    return helper_read_value(startbit,lastbit,sparc_intunit_ptr->ASR);
}

/* WRITE VALUE TO ASR (BASE - EXTRA FUNCTION) */

void sparcv8_inst_set_extra_WRASR(INT32 bitnumber,enum ASRfield field,INT32 value)
{
    INT32 startbit;
    INT32 lastbit;
    switch(field)
    {
    case ASRBIT:
        startbit=bitnumber;
        lastbit=bitnumber;
        break;
    case ASRALL:
        startbit=0;
        lastbit=31;
        break;
    default:
        printf("not an expected field tag of ASR\n");
        break;
    }
    sparc_intunit_ptr->ASR= helper_write_value(startbit,lastbit,sparc_intunit_ptr->ASR,value);
}


/* READ VALUE OF FSR (BASE - EXTRA FUNCTION) */

ULONG sparcv8_inst_set_extra_RDFSR(enum FSRfield field)
{
    INT32 startbit;
    INT32 lastbit;
    switch(field)
    {
    case RD:
        startbit=30;
        lastbit=31;
        break;
    case UHIGH:
        startbit=28;
        lastbit=29;
        break;
    case TEM:
        startbit=23;
        lastbit=27;
        break;
    case NS:
        startbit=22;
        lastbit=22;
        break;
    case RES:
        startbit=20;
        lastbit=21;
        break;
    case VERFSR:
        startbit=17;
        lastbit=19;
        break;
    case FTT:
        startbit=14;
        lastbit=16;
        break;
    case QNE:
        startbit=13;
        lastbit=13;
        break;
    case ULOW:
        startbit=12;
        lastbit=12;
        break;
    case FCC:
        startbit=10;
        lastbit=11;
        break;
    case AEXC:
        startbit=5;
        lastbit=9;
        break;
    case CEXC:
        startbit=5;
        lastbit=9;
        break;
    case FSRALL:
        startbit=0;
        lastbit=31;
        break;
    default:
        printf("not an expected field tag of FSR\n");
        break;
    }
    return helper_read_value(startbit,lastbit,sparc_fpu_ptr->FSR);
}


/* WRITE VALUE TO FSR (BASE - EXTRA FUNCTION) */

void sparcv8_inst_set_extra_WRFSR(enum FSRfield field,INT32 value)
{
    INT32 startbit;
    INT32 lastbit;
    switch(field)
    {
    case RD:
        startbit=30;
        lastbit=31;
        break;
    case UHIGH:
        startbit=28;
        lastbit=29;
        break;
    case TEM:
        startbit=23;
        lastbit=27;
        break;
    case NS:
        startbit=22;
        lastbit=22;
        break;
    case RES:
        startbit=20;
        lastbit=21;
        break;
    case VERFSR:
        startbit=17;
        lastbit=19;
        break;
    case FTT:
        startbit=14;
        lastbit=16;
        break;
    case QNE:
        startbit=13;
        lastbit=13;
        break;
    case ULOW:
        startbit=12;
        lastbit=12;
        break;
    case FCC:
        startbit=10;
        lastbit=11;
        break;
    case AEXC:
        startbit=5;
        lastbit=9;
        break;
    case CEXC:
        startbit=5;
        lastbit=9;
        break;
    case FSRALL:
        startbit=0;
        lastbit=31;
        break;
    default:
        printf("not an expected field tag of FSR\n");
        break;
    }
    sparc_fpu_ptr->FSR= helper_write_value(startbit,lastbit,sparc_fpu_ptr->FSR,value);
}

/* READ VALUE OF CSR (BASE - EXTRA FUNCTION) */

ULONG sparcv8_inst_set_extra_RDCSR(INT32 bitnumber,enum CSRfield field)
{
    INT32 startbit;
    INT32 lastbit;
    switch(field)
    {
    case CSRBIT:
        startbit=bitnumber;
        lastbit=bitnumber;
        break;
    case CSRALL:
        bitnumber=0;
        startbit=0;
        lastbit=31;
        break;
    default:
        printf("not an expected field tag of CSR\n");
        break;
    }
    return helper_read_value(startbit,lastbit,sparc_coprocessor_ptr->CSR);
}

/* WRITE VALUE TO CSR (BASE - EXTRA FUNCTION) */

void sparcv8_inst_set_extra_WRCSR(INT32 bitnumber,enum CSRfield field,INT32 value)
{
    INT32 startbit;
    INT32 lastbit;
    switch(field)
    {
    case CSRBIT:
        startbit=bitnumber;
        lastbit=bitnumber;
        break;
    case CSRALL:
        startbit=0;
        lastbit=31;
        break;
    default:
        printf("not an expected field tag of CSR\n");
        break;
    }
    sparc_coprocessor_ptr->CSR= helper_write_value(startbit,lastbit,sparc_coprocessor_ptr->CSR,value);
}



/* READ VALUE OF Y (BASE - EXTRA FUNCTION) */

ULONG sparcv8_inst_set_extra_RDY(INT32 bitnumber,enum Yfield field)
{
    INT32 startbit;
    INT32 lastbit;
    switch(field)
    {
    case YBIT:
        startbit=bitnumber;
        lastbit=bitnumber;
        break;
    case YALL:
        startbit=0;
        lastbit=31;
        break;
    default:
        printf("not an expected field tag of Y\n");
        break;
    }
    return helper_read_value(startbit,lastbit,sparc_intunit_ptr->Y);
}

/* WRITE VALUE TO Y (BASE - EXTRA FUNCTION) */

void sparcv8_inst_set_extra_WRY(INT32 bitnumber,enum Yfield field,INT32 value)
{
    INT32 startbit;
    INT32 lastbit;
    switch(field)
    {
    case YBIT:
        startbit=bitnumber;
        lastbit=bitnumber;
        break;
    case YALL:
        startbit=0;
        lastbit=31;
        break;
    default:
        printf("not an expected field tag of Y\n");
        break;
    }
    sparc_intunit_ptr->Y=helper_write_value(startbit,lastbit,sparc_intunit_ptr->Y,value);
}

/* READ VALUE OF PC (BASE - EXTRA FUNCTION) */

ULONG sparcv8_inst_set_extra_RPC(INT32 bitnumber,enum PCfield field)
{
    INT32 startbit;
    INT32 lastbit;
    switch(field)
    {
    case PCBIT:
        startbit=bitnumber;
        lastbit=bitnumber;
        break;
    case PCALL:
        startbit=0;
        lastbit=31;
        break;
    default:
        printf("not an expected field tag of PC\n");
        break;
    }
    return helper_read_value(startbit,lastbit, *sparc_intunit_ptr->PC);
}

/* WRITE VALUE TO PC (BASE - EXTRA FUNCTION) */

void sparcv8_inst_set_extra_WRPC(INT32 bitnumber,enum Yfield field,INT32 value)
{
    INT32 startbit;
    INT32 lastbit;
    switch(field)
    {
    case PCBIT:
        startbit=bitnumber;
        lastbit=bitnumber;
        break;
    case PCALL:
        startbit=0;
        lastbit=31;
        break;
    default:
        printf("not an expected field tag of PC\n");
        break;
    }
    *sparc_intunit_ptr->PC=helper_write_value(startbit,lastbit,*sparc_intunit_ptr->PC,value);
}

/* READ VALUE OF nPC (BASE - EXTRA FUNCTION) */

ULONG sparcv8_inst_set_extra_RnPC(INT32 bitnumber,enum NPCfield field)
{
    INT32 startbit;
    INT32 lastbit;
    switch(field)
    {
    case NPCBIT:
        startbit=bitnumber;
        lastbit=bitnumber;
        break;
    case NPCALL:
        startbit=0;
        lastbit=31;
        break;
    default:
        printf("not an expected field tag of nPC\n");
        break;
    }
    return helper_read_value(startbit,lastbit, *sparc_intunit_ptr->nPC);
}

/* WRITE VALUE TO nPC (BASE - EXTRA FUNCTION) */

void sparcv8_inst_set_extra_WRnPC(INT32 bitnumber,enum NPCfield field,INT32 value)
{
    INT32 startbit;
    INT32 lastbit;
    switch(field)
    {
    case NPCBIT:
        startbit=bitnumber;
        lastbit=bitnumber;
        break;
    case NPCALL:
        startbit=0;
        lastbit=31;
        break;
    default:
        printf("not an expected field tag of PC\n");
        break;
    }
    *sparc_intunit_ptr->nPC=helper_write_value(startbit,lastbit,*sparc_intunit_ptr->nPC,value);
}

/* READ VALUE OF (ASR OR Y) OR (STBAR INSTRUCTION) */

void sparcv8_inst_set_RDASR_or_RDY_or_STBAR(ULONG instruction_field)
{
    ULONG RD=helper_instruction_field_rd(instruction_field);

    if (helper_instruction_field_rs1(instruction_field) >  0xF)
    {

        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=sparcv8_inst_set_extra_RDASR(0,ASRALL);
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=sparcv8_inst_set_extra_RDASR(0,ASRALL);
        }
    }
    else   if (helper_instruction_field_rs1(instruction_field) == 0)
    {
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=sparcv8_inst_set_extra_RDY(0,YALL);
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=sparcv8_inst_set_extra_RDY(0,YALL);
        }
    }
    else if ((helper_instruction_field_rs1(instruction_field) == 0xF) && (helper_instruction_field_rd(instruction_field)== 0 ))
    {
        /* EXECUTE STBAR INSTRUCTION */
        printf("\nTHE STBAR INSTRUCTION IS NOT READY YET\n");
        return ;
    }
    else
    {
        /* RESERVED FOR FUTURE VERSIONS */
        printf("RESERVED FOR FUTURE VERSIONS");
        return ;
    }
}

/* WRITE VALUE OF ASR OR Y  */

void sparcv8_inst_set_WRASR_or_WRY(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }

    if (helper_instruction_field_i(instruction_field) == 0x00)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);

        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }


        if((helper_instruction_field_rd(instruction_field) ==0x00) && (helper_instruction_field_op3(instruction_field) == 0x30) )
        {
            sparcv8_inst_set_extra_WRY(0,YALL,RS1 ^ RS2);
        }
        else  if((helper_instruction_field_rd(instruction_field) > 0xF) && (helper_instruction_field_op3(instruction_field) == 0x30) )
        {
            sparcv8_inst_set_extra_WRASR(0,ASRALL,RS1 ^ RS2);
        }

        else
        {
            /* RESERVED FOR FUTURE VERSIONS */
            printf("RESERVED FOR FUTURE VERSIONS");
            return;
        }
    }
    else if (helper_instruction_field_i(instruction_field) == 0x01)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);

        if((helper_instruction_field_rd(instruction_field) ==0x00) && (helper_instruction_field_op3(instruction_field) == 0x30) )
        {
            sparcv8_inst_set_extra_WRY(0,YALL,RS1 ^ ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
        }
        else  if((helper_instruction_field_rd(instruction_field) > 0xF) && (helper_instruction_field_op3(instruction_field) == 0x30 ))
        {
            sparcv8_inst_set_extra_WRASR(0,ASRALL,RS1 ^ ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
        }
        else
        {
            /* RESERVED FOR FUTURE VERSIONS */
            printf("RESERVED FOR FUTURE VERSIONS");
            return;
        }
    }

}

/* WRITE VALUE OF PSR */

void sparcv8_inst_set_WRPSR(ULONG instruction_field)
{

    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }

    if (helper_instruction_field_i(instruction_field) == 0x00)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);

        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }


        if (((ULONG)pow(2,helper_read_value(0,4,RS1^RS2)-1) == 0) /* COMPARE CWP WITH WIM  */  && ( ((ULONG)pow(2,helper_read_value(0,4,RS1^RS2)+1) & sparcv8_inst_set_extra_RDWIM(0,WIMALL)) != 0))
        {
            /* ILLEGAL INSTRUCTION TRAP */
            printf("ILLEGAL INSTRUCTION TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->illegal_instruction);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
            return;
        }
        sparcv8_inst_set_extra_WRPSR(PSRALL,RS1 ^ RS2);

    }
    else if (helper_instruction_field_i(instruction_field) == 0x01)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if (((ULONG)pow(2,helper_read_value(0,4,RS1^((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))-1) == 0) /* COMPARE CWP WITH WIM  */  && ( ((ULONG)pow(2,helper_read_value(0,4,RS1^((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))+1) & sparcv8_inst_set_extra_RDWIM(0,WIMALL)) != 0))
        {
            /* ILLEGAL INSTRUCTION TRAP */
            printf("ILLEGAL INSTRUCTION TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->illegal_instruction);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
            return;
        }
        sparcv8_inst_set_extra_WRPSR(PSRALL ,RS1 ^ ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
    }
}

/* WRITE VALUE OF WIM */

void sparcv8_inst_set_WRWIM(ULONG instruction_field)
{

    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if (helper_instruction_field_i(instruction_field) == 0x00)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);

        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }

        sparcv8_inst_set_extra_WRWIM(0,WIMALL ,RS1 ^ RS2);
    }
    else if (helper_instruction_field_i(instruction_field) == 0x01)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        sparcv8_inst_set_extra_WRWIM(0,WIMALL ,RS1 ^ ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
    }
}


/* WRITE VALUE OF TBR */

void sparcv8_inst_set_WRTBR(ULONG instruction_field)
{

    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }

    if (helper_instruction_field_i(instruction_field) == 0x00)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);

        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        sparcv8_inst_set_extra_WRTBR(TBRALL ,RS1 ^ RS2);

    }
    else if (helper_instruction_field_i(instruction_field) == 0x01)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        sparcv8_inst_set_extra_WRTBR(TBRALL ,RS1 ^ ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
    }
}


/* READ VALUE OF PSR */

void sparcv8_inst_set_RDPSR(ULONG instruction_field)
{
    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD<8)
    {
        sparc_intunit_ptr->windowregs.GREG[RD]=sparcv8_inst_set_extra_RDPSR(PSRALL);
    }
    else
    {
        *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=sparcv8_inst_set_extra_RDPSR(PSRALL);
    }
}

/* READ VALUE OF WIM */

void sparcv8_inst_set_RDWIM(ULONG instruction_field)
{
    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD<8)
    {
        sparc_intunit_ptr->windowregs.GREG[RD]=sparcv8_inst_set_extra_RDWIM(0,WIMALL);
    }
    else
    {
        *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=sparcv8_inst_set_extra_RDWIM(0,WIMALL);
    }
}

/* READ VALUE OF TBR */

void sparcv8_inst_set_RDTBR(ULONG instruction_field)
{
    ULONG RD=helper_instruction_field_rd(instruction_field);

    if(RD<8)
    {
        sparc_intunit_ptr->windowregs.GREG[RD]=sparcv8_inst_set_extra_RDTBR(TBRALL);
    }
    else
    {
        *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=sparcv8_inst_set_extra_RDWIM(0,WIMALL);

    }
}

///////////////////////////////////////////////////////////////////////  DATA TRANSFER //////////////////////////////////////////////////////////////////////////////////////////
/* LOAD SIGNED BYTE */

void sparcv8_inst_set_LDSB(ULONG instruction_field)
{

    /*  TRAP CATALOGUE FOR LDSB INSTRUCTION
    *
    *  illegal_instruction (load alternate with i = 1; LDD, LDDA with odd rd) -- NO NEED
    *  privileged_instruction (load alternate space only) -- NO NEED
    *  mem_address_not_aligned (excluding LDSB, LDSBA, LDUB, LDUBA) -- NO NEED
    *  data_access_exception -- REMAINING
    *  data_access_error -- REMAINING
    */


    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    ULONG RD=helper_instruction_field_rd(instruction_field) ;

    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }

    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if( RD < 8 && RD != 0)

        {
            sparc_intunit_ptr->windowregs.GREG[RD]= sparcv8_mmu_memory_data_load_signed_byte((RS1+RS2),helper_read_value(0,1,(RS1+RS2)));
            sparc_intunit_ptr->windowregs.GREG[RD]=(sparc_intunit_ptr->windowregs.GREG[RD] & 0xFF) | ((sparc_intunit_ptr->windowregs.GREG[RD] & 0x80) ? 0xFFFFFF00 : 0);   /* SIGN-EXTENDED OR ZERO_EXTEND CONTEX*/
        }
        else if( RD >= 8 &&  RD != 0 )
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=sparcv8_mmu_memory_data_load_signed_byte((RS1+RS2),helper_read_value(0,1,(RS1+RS2)));
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=( *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))]) & 0xFF) | (( *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))]) & 0x80) ? 0xFFFFFF00 : 0);   /* SIGN-EXTENDED OR ZERO_EXTEND CONTEX*/
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);

        if( RD < 8 && RD != 0)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=sparcv8_mmu_memory_data_load_signed_byte((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))),helper_read_value(0,1,(RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))));  /* SIGN-EXTENDED OR ZERO_EXTEND SIMM13*/
            sparc_intunit_ptr->windowregs.GREG[RD]=(sparc_intunit_ptr->windowregs.GREG[RD] & 0xFF) | (  (sparc_intunit_ptr->windowregs.GREG[RD] & 0x80) ? 0xFFFFFF00 : 0);   /* SIGN-EXTENDED OR ZERO_EXTEND CONTEX*/
        }
        else if( RD >= 8 &&  RD != 0 )
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=sparcv8_mmu_memory_data_load_signed_byte((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))),helper_read_value(0,1,(RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))); /* SIGN-EXTENDED OR ZERO_EXTEND CONTEX*/
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=(*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))]) & 0xFF) | (  (*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))]) & 0x80) ? 0xFFFFFF00 : 0);   /* SIGN-EXTENDED OR ZERO_EXTEND CONTEX*/
        }
    }

    return;
}

/* LOAD SIGNED HALFWORD */

void sparcv8_inst_set_LDSH(ULONG instruction_field)
{

    /*  TRAP CATALOGUE FOR LDSH INSTRUCTION
    *
    *  illegal_instruction (load alternate with i = 1; LDD, LDDA with odd rd) -- NO NEED
    *  privileged_instruction (load alternate space only) -- NO NEED
    *  mem_address_not_aligned (excluding LDSB, LDSBA, LDUB, LDUBA) -- DONE
    *  data_access_exception -- REMAINING
    *  data_access_error -- REMAINING
    */

    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    ULONG RD=helper_instruction_field_rd(instruction_field) ;

    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }

    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }

        if ( ((RS1+RS2) & 0x01) !=0 )
        {
            /* MEMORY ADDRESS NOT ALLIGNED TRAP */

            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC+1;
        }

        if( RD < 8 && RD != 0)

        {
            sparc_intunit_ptr->windowregs.GREG[RD]= sparcv8_mmu_memory_data_load_signed_halfword((RS1+RS2),helper_read_value(0,1,(RS1+RS2)));
            sparc_intunit_ptr->windowregs.GREG[RD]=(sparc_intunit_ptr->windowregs.GREG[RD] & 0xFFFF) | ((sparc_intunit_ptr->windowregs.GREG[RD] & 0x8000) ? 0xFFFF0000 : 0);   /* SIGN-EXTENDED OR ZERO_EXTEND CONTEX*/
        }
        else if( RD >= 8 &&  RD != 0 )
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=sparcv8_mmu_memory_data_load_signed_halfword((RS1+RS2),helper_read_value(0,1,(RS1+RS2)));
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=( *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))]) & 0xFFFF) | (( *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))]) & 0x8000) ? 0xFFFF0000 : 0);   /* SIGN-EXTENDED OR ZERO_EXTEND CONTEX*/
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);

        if( RD < 8 && RD != 0)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=sparcv8_mmu_memory_data_load_signed_halfword((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))),helper_read_value(0,1,(RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))));  /* SIGN-EXTENDED OR ZERO_EXTEND SIMM13*/
            sparc_intunit_ptr->windowregs.GREG[RD]=(sparc_intunit_ptr->windowregs.GREG[RD] & 0xFFFF) | (  (sparc_intunit_ptr->windowregs.GREG[RD] & 0x8000) ? 0xFFFF0000 : 0);   /* SIGN-EXTENDED OR ZERO_EXTEND CONTEX*/
        }
        else if( RD >= 8 &&  RD != 0 )
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=sparcv8_mmu_memory_data_load_signed_halfword((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))),helper_read_value(0,1,(RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))); /* SIGN-EXTENDED OR ZERO_EXTEND CONTEX*/
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=(*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))]) & 0xFFFF) | (  (*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))]) & 0x8000) ? 0xFFFF0000 : 0);   /* SIGN-EXTENDED OR ZERO_EXTEND CONTEX*/
        }
    }
    return;
}


/* LOAD UNSIGNED BYTE */

void sparcv8_inst_set_LDUB(ULONG instruction_field)
{

    /*  TRAP CATALOGUE FOR LDUB INSTRUCTION
    *
    *  illegal_instruction (load alternate with i = 1; LDD, LDDA with odd rd) -- NO NEED
    *  privileged_instruction (load alternate space only) -- NO NEED
    *  mem_address_not_aligned (excluding LDSB, LDSBA, LDUB, LDUBA) -- NO NEED
    *  data_access_exception -- REMAINING
    *  data_access_error -- REMAINING
    */


    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    ULONG RD=helper_instruction_field_rd(instruction_field) ;

    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }

    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }


        if( RD < 8 && RD != 0)

        {
            sparc_intunit_ptr->windowregs.GREG[RD]= sparcv8_memory_load_unsigned_byte((RS1+RS2),helper_read_value(0,1,(RS1+RS2)));
            sparc_intunit_ptr->windowregs.GREG[RD]=(sparc_intunit_ptr->windowregs.GREG[RD] & 0xFF) | ((sparc_intunit_ptr->windowregs.GREG[RD] & 0x80) ? 0xFFFFFF00 : 0);   /* SIGN-EXTENDED OR ZERO_EXTEND CONTEX*/
        }
        else if( RD >= 8 &&  RD != 0 )
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=sparcv8_memory_load_unsigned_byte((RS1+RS2),helper_read_value(0,1,(RS1+RS2)));
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=( *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))]) & 0xFF) | (( *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))]) & 0x80) ? 0xFFFFFF00 : 0);   /* SIGN-EXTENDED OR ZERO_EXTEND CONTEX*/
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);

        if( RD < 8 && RD != 0)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=sparcv8_memory_load_unsigned_byte((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))),helper_read_value(0,1,(RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))));  /* SIGN-EXTENDED OR ZERO_EXTEND SIMM13*/
            sparc_intunit_ptr->windowregs.GREG[RD]=(sparc_intunit_ptr->windowregs.GREG[RD] & 0xFF) | (  (sparc_intunit_ptr->windowregs.GREG[RD] & 0x80) ? 0xFFFFFF00 : 0);   /* SIGN-EXTENDED OR ZERO_EXTEND CONTEX*/
        }
        else if( RD >= 8 &&  RD != 0 )
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=sparcv8_memory_load_unsigned_byte((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))),helper_read_value(0,1,(RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))); /* SIGN-EXTENDED OR ZERO_EXTEND CONTEX*/
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=(*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))]) & 0xFF) | (  (*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))]) & 0x80) ? 0xFFFFFF00 : 0);   /* SIGN-EXTENDED OR ZERO_EXTEND CONTEX*/
        }
    }

    return;
}


/* LOAD UNSIGNED HALFWORD */

void sparcv8_inst_set_LDUH(ULONG instruction_field)
{

    /*  TRAP CATALOGUE FOR LDUH INSTRUCTION
    *
    *  illegal_instruction (load alternate with i = 1; LDD, LDDA with odd rd) -- NO NEED
    *  privileged_instruction (load alternate space only) -- NO NEED
    *  mem_address_not_aligned (excluding LDSB, LDSBA, LDUB, LDUBA) -- DONE
    *  data_access_exception -- REMAINING
    *  data_access_error -- REMAINING
    */

    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    ULONG RD=helper_instruction_field_rd(instruction_field) ;

    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }

    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);

        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if ( ((RS1+RS2) & 0x01) !=0 )
        {
            /* MEMORY ADDRESS NOT ALLIGNED TRAP */

            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        if( RD < 8 && RD != 0)

        {
            sparc_intunit_ptr->windowregs.GREG[RD]= sparcv8_mmu_memory_data_load_unsigned_halfword((RS1+RS2),helper_read_value(0,1,(RS1+RS2)));
            sparc_intunit_ptr->windowregs.GREG[RD]=(sparc_intunit_ptr->windowregs.GREG[RD] & 0xFFFF) | ((sparc_intunit_ptr->windowregs.GREG[RD] & 0x8000) ? 0xFFFF0000 : 0);   /* SIGN-EXTENDED OR ZERO_EXTEND CONTEX*/
        }
        else if( RD >= 8 &&  RD != 0 )
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=sparcv8_mmu_memory_data_load_unsigned_halfword((RS1+RS2),helper_read_value(0,1,(RS1+RS2)));
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=( *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))]) & 0xFFFF) | (( *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))]) & 0x8000) ? 0xFFFF0000 : 0);   /* SIGN-EXTENDED OR ZERO_EXTEND CONTEX*/
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);

        if( RD < 8 && RD != 0)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=sparcv8_mmu_memory_data_load_unsigned_halfword((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))),helper_read_value(0,1,(RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))));  /* SIGN-EXTENDED OR ZERO_EXTEND SIMM13*/
            sparc_intunit_ptr->windowregs.GREG[RD]=(sparc_intunit_ptr->windowregs.GREG[RD] & 0xFFFF) | (  (sparc_intunit_ptr->windowregs.GREG[RD] & 0x8000) ? 0xFFFF0000 : 0);   /* SIGN-EXTENDED OR ZERO_EXTEND CONTEX*/
        }
        else if( RD >= 8 &&  RD != 0 )
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=sparcv8_mmu_memory_data_load_unsigned_halfword((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))),helper_read_value(0,1,(RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))); /* SIGN-EXTENDED OR ZERO_EXTEND CONTEX*/
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=(*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))]) & 0xFFFF) | (  (*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))]) & 0x8000) ? 0xFFFF0000 : 0);   /* SIGN-EXTENDED OR ZERO_EXTEND CONTEX*/
        }
    }
    return;
}

/* LOAD WORD */

void sparcv8_inst_set_LD(ULONG instruction_field)
{

    /*  TRAP CATALOGUE FOR LD INSTRUCTION
    *
    *  illegal_instruction (load alternate with i = 1; LDD, LDDA with odd rd) -- NO NEED
    *  privileged_instruction (load alternate space only) -- NO NEED
    *  mem_address_not_aligned (excluding LDSB, LDSBA, LDUB, LDUBA) -- DONE
    *  data_access_exception -- REMAINING
    *  data_access_error -- REMAINING
    */

    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    ULONG RD=helper_instruction_field_rd(instruction_field) ;

    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }

    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        /* THE TWO LSB OF THE ADDRESS MUST BE ZERO FROM 0x00 TO 0x03. 4 BYTES SPACE (32 BITS) */

        if ( ((RS1+RS2) & 0x03)  !=0 )
        {
            /* MEMORY ADDRESS NOT ALLIGNED TRAP */

            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        if( RD < 8 && RD !=0)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]= sparcv8_mmu_memory_data_load_word(RS1+RS2);
        }
        else if( RD >= 8 && RD !=0 )
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=sparcv8_mmu_memory_data_load_word(RS1+RS2);
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if( RD < 8 &&  RD !=0)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=sparcv8_mmu_memory_data_load_word(RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
        }
        else if( RD >= 8 &&  RD !=0 )
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=sparcv8_mmu_memory_data_load_word(RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
        }
        /* THE TWO LSB OF THE ADDRESS MUST BE ZERO FROM 0x00 TO 0x03. 4 BYTES SPACE (32 BITS) */
        if ( ((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) & 0x03) !=0 )
        {
            /* MEMORY ADDRESS NOT ALLIGNED TRAP */

            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
    }
    return;
}

/* LOAD DOUBLEWORD */

void sparcv8_inst_set_LDD(ULONG instruction_field)
{

    /*  TRAP CATALOGUE FOR LDD INSTRUCTION
    *
    *  illegal_instruction (load alternate with i = 1; LDD, LDDA with odd rd) -- DONE
    *  privileged_instruction (load alternate space only) -- NO NEED
    *  mem_address_not_aligned (excluding LDSB, LDSBA, LDUB, LDUBA) -- DONE
    *  data_access_exception -- REMAINING
    *  data_access_error -- REMAINING
    */

    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    /* THE LEAST SIGNIFICANT BIT OF THE RD FIELD (5-BIT) IS UNUSED AND SHOULD BE SET TO ZERO BY SOFTWARE FOR EVEN REGISTER RD CHOICE */

    ULONG RD=helper_instruction_field_rd(instruction_field) & 0x1E ;

    if ((RD & 0x1) != 0)
    {
        /* ILLEGAL INSTRUCTION TRAP */
        printf("ILLEGAL INSTRUCTION TRAP \n");
        sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->illegal_instruction);
        sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
        sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
    }

    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }

    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2 < 8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        /* THE THREE LSB OF THE ADDRESS MUST BE ZERO FROM 0x00 TO 0x07. 8 BYTES SPACE (64 BITS) */

        if ( ((RS1+RS2) & 0x07) !=0 )
        {
            /* MEMORY ADDRESS NOT ALLIGNED TRAP */

            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }


        if( RD < 8 && ((RD & 0x1) == 0) ) /* THE MOST SIGNIFICANT WORD AT THE EFFECTIVE MEMORY ADDRESS IS MOVED INTO THE EVEN RD REGISTER */
        {
            sparc_intunit_ptr->windowregs.GREG[RD]= sparcv8_mmu_memory_data_load_doubleword((RS1+RS2),1); /* 0 MEANS LSW, 1 MEANS MSW  */
            sparc_intunit_ptr->windowregs.GREG[RD+1]= sparcv8_mmu_memory_data_load_doubleword((RS1+RS2),0);
        }
        else if( RD >= 8 && ((RD & 0x1) == 0) )/* THE MORE SIGNIFICANT WORD AT THE EFFECTIVE MEMORY ADDRESS IS MOVED INTO THE EVEN R REGISTER */
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=sparcv8_mmu_memory_data_load_doubleword((RS1+RS2),1); /* 0 MEANS LSW, 1 MEANS MSW  */
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-7))])= sparcv8_mmu_memory_data_load_doubleword((RS1+RS2),0);
        }

    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if( RD < 8 && ((RD & 0x1) == 0) ) /* THE MORE SIGNIFICANT WORD AT THE EFFECTIVE MEMORY ADDREDD IS MOVED INTO THE EVEN R REGISTER */
        {
            sparc_intunit_ptr->windowregs.GREG[RD]= sparcv8_mmu_memory_data_load_doubleword((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))),1); /* 0 MEANS LSW, 1 MEANS MSW  */
            sparc_intunit_ptr->windowregs.GREG[RD+1]=sparcv8_mmu_memory_data_load_doubleword((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))),0);
        }
        else if( RD >= 8 && ((RD & 0x1) == 0) )/* THE MORE SIGNIFICANT WORD AT THE EFFECTIVE MEMORY ADDREDD IS MOVED INTO THE EVEN R REGISTER */
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=sparcv8_mmu_memory_data_load_doubleword((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))),1); /* 0 MEANS LSW, 1 MEANS MSW  */
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-7))])= sparcv8_mmu_memory_data_load_doubleword((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))),0);
        }

        /* THE THREE LSB OF THE ADDRESS MUST BE ZERO FROM 0x00 TO 0x07. 8 BYTES SPACE (64 BITS) */

        if ( ((RS1 + ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) & 0x07) !=0 )
        {

            /* MEMORY ADDRESS NOT ALLIGNED TRAP */

            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
    }
    return;
}

/* LOAD FLOATING POINT REGISTER */

void sparcv8_inst_set_LDF(ULONG instruction_field)
{

    /*  TRAP CATALOGUE FOR LDF INSTRUCTION
    *
    *  fp_disabled -- DONE
    *  fp_exception (sequence_error, invalid_fp_register(LDDF)) -- REMAINING
    *  data_access_exception -- REMAINING
    *  mem_address_not_aligned -- DONE
    *  data_access_error -- REMAINING
    */

    if ((sparcv8_inst_set_extra_RDPSR(EF) == 0) | (interface_signals_ptr->bp_FPU_present ==0 ))
    {
        printf(" FLOATING POINT DESABLED TRAP \n");
        sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->fp_disabled);
        sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
        sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
    }

    ULONG RD=helper_instruction_field_rd(instruction_field) & 0x1E ;

    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }

    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if ( ((RS1+RS2) & 0x03)  !=0 )
        {
            /* MEMORY ADDRESS NOT ALLIGNED TRAP */

            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }

        sparc_fpu_ptr->FREG[RD]=sparcv8_mmu_memory_data_load_floating_point(RS1+RS2);
    }

    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);

        if ( ((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) & 0x03)  !=0 )
        {
            /* MEMORY ADDRESS NOT ALLIGNED TRAP */

            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }

        sparc_fpu_ptr->FREG[RD]=sparcv8_mmu_memory_data_load_floating_point(RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
    }

    return;
}


/* LOAD DOUBLE FLOATING POINT REGISTER */

void sparcv8_inst_set_LDDF(ULONG instruction_field)
{

    /*  TRAP CATALOGUE FOR LDDF INSTRUCTION
    *
    *  fp_disabled -- DONE
    *  fp_exception (sequence_error, invalid_fp_register(LDDF)) -- DONE
    *  data_access_exception -- REMAINING
    *  mem_address_not_aligned -- DONE
    *  data_access_error -- REMAINING
    */

    if ((sparcv8_inst_set_extra_RDPSR(EF) == 0) | (interface_signals_ptr->bp_FPU_present ==0 ))
    {
        printf(" FLOATING POINT DESABLED TRAP \n");
        sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->fp_disabled);
        sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
        sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
    }


    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    /* THE LEAST SIGNIFICANT BIT OF THE RD FIELD (5-BIT) IS UNUSED AND SHOULD BE SET TO ZERO BY SOFTWARE FOR EVEN REGISTER RD CHOICE */

    ULONG RD=helper_instruction_field_rd(instruction_field) & 0x1E ;

    if ( (RD & 0x01) !=0 )
    {
        printf(" FLOATING POINT EXCEPTION TRAP \n");
        sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->fp_exception);
        sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
        sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
    }

    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }

    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);

        if(RS2 < 8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }

        if ( ((RS1+RS2) & 0x07) !=0 )
        {
            /* MEMORY ADDRESS NOT ALLIGNED TRAP */

            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }

        if((RD & 0x1) == 0) /* THE MORE SIGNIFICANT WORD AT THE EFFECTIVE MEMORY ADDREDD IS MOVED INTO THE EVEN R REGISTER */
        {
            sparc_fpu_ptr->FREG[RD]= sparcv8_mmu_memory_data_load_double_floating_point((RS1+RS2),1); /* 0 MEANS LSW, 1 MEANS MSW  */
            sparc_fpu_ptr->FREG[RD+1]= sparcv8_mmu_memory_data_load_double_floating_point((RS1+RS2),0);
        }
    }

    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);

        if ( ((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) & 0x07) !=0 )
        {
            /* MEMORY ADDRESS NOT ALLIGNED TRAP */

            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }

        if( (RD & 0x1) == 0) /* THE MOST SIGNIFICANT WORD AT THE EFFECTIVE MEMORY ADDREDD IS MOVED INTO THE EVEN R REGISTER */
        {
            sparc_fpu_ptr->FREG[RD]= sparcv8_mmu_memory_data_load_double_floating_point((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))),1); /* 0 MEANS LSW, 1 MEANS MSW  */
            sparc_fpu_ptr->FREG[RD+1]= sparcv8_mmu_memory_data_load_double_floating_point((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))),0);
        }
    }
    return;
}

/* LOAD FLOATING POINT STATE REGISTER */

void sparcv8_inst_set_LDFSR(ULONG instruction_field)
{

    /*  TRAP CATALOGUE FOR LDFSR INSTRUCTION
    *
    *  fp_disabled -- DONE
    *  fp_exception (sequence_error, invalid_fp_register(LDDF)) -- REMAINING
    *  data_access_exception -- REMAINING
    *  mem_address_not_aligned -- DONE
    *  data_access_error -- REMAINING
    */

    if ((sparcv8_inst_set_extra_RDPSR(EF) == 0) | (interface_signals_ptr->bp_FPU_present ==0 ))
    {
        printf(" FLOATING POINT DESABLED TRAP \n");
        sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->fp_disabled);
        sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
        sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
    }

    /*(WHILE FPOP INST ARE NOT EXECUTED) {WAIT}*/

    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }

    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }

        if ( ((RS1+RS2) & 0x03)  !=0 )
        {
            /* MEMORY ADDRESS NOT ALLIGNED TRAP */

            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }

        sparc_fpu_ptr->FSR=sparcv8_mmu_memory_data_load_word(RS1+RS2);
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if ( ((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) & 0x03) !=0 )
        {
            /* MEMORY ADDRESS NOT ALLIGNED TRAP */

            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        sparc_fpu_ptr->FSR=sparcv8_mmu_memory_data_load_word(RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
    }
    return;
}

/* LOAD WORD COPROCESSOR REGISTER */

void sparcv8_inst_set_LDC(ULONG instruction_field)
{

    /*  TRAP CATALOGUE FOR LDC INSTRUCTION
    *
    *  cp_disabled -- DONE
    *  cp_exception -- REMAINING
    *  data_access_exception -- REMAINING
    *  mem_address_not_aligned -- DONE
    *  data_access_error -- REMAINING
    */

    if ((sparcv8_inst_set_extra_RDPSR(EC) == 0) | (interface_signals_ptr->bp_CP_present ==0 ))
    {
        printf(" COPROCESSOR UNIT DESABLED TRAP \n");
        sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->cp_disabled);
        sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
        sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
    }

    ULONG RD=helper_instruction_field_rd(instruction_field);
    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }

    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }


        if ( ((RS1+RS2) & 0x03)  !=0 )
        {
            /* MEMORY ADDRESS NOT ALLIGNED TRAP */

            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }

        sparc_coprocessor_ptr->CREG[RD]=sparcv8_mmu_memory_data_load_word(RS1+RS2);
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if ( ((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) & 0x03)  !=0 )
        {
            /* MEMORY ADDRESS NOT ALLIGNED TRAP */

            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        sparc_coprocessor_ptr->CREG[RD]=sparcv8_mmu_memory_data_load_word(RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
    }

    return;
}

/* LOAD DOUBLE COPROCESSOR REGISTER */

void sparcv8_inst_set_LDDC(ULONG instruction_field)
{

    /*  TRAP CATALOGUE FOR LDDC INSTRUCTION
    *
    *  cp_disabled -- DONE
    *  cp_exception -- DONE
    *  data_access_exception -- REMAINING
    *  mem_address_not_aligned -- DONE
    *  data_access_error -- REMAINING
    */

    if ((sparcv8_inst_set_extra_RDPSR(EC) == 0) | (interface_signals_ptr->bp_CP_present ==0 ))
    {
        printf(" COPROCESSOR UNIT DESABLED TRAP \n");
        sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->cp_disabled);
        sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
        sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
    }

    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    /* THE LEAST SIGNIFICANT BIT OF THE RD FIELD (5-BIT) IS UNUSED AND SHOULD BE SET TO ZERO BY SOFTWARE FOR EVEN REGISTER RD CHOICE */

    ULONG RD=helper_instruction_field_rd(instruction_field) & 0x1E ;

    if ( (RD & 0x01) !=0 )
    {
        printf(" COPROCESSOR UNIT EXCEPTION TRAP \n");
        sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->cp_exception);
        sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
        sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
    }
    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }

    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);

        if(RS2 < 8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }

        if ( ((RS1+RS2) & 0x07) !=0 )
        {
            /* MEMORY ADDRESS NOT ALLIGNED TRAP */

            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        if((RD & 0x1) == 0) /* THE MORE SIGNIFICANT WORD AT THE EFFECTIVE MEMORY ADDREDD IS MOVED INTO THE EVEN R REGISTER */
        {
            sparc_coprocessor_ptr->CREG[RD]= sparcv8_mmu_memory_data_load_doubleword((RS1+RS2),1); /* 0 MEANS LSW, 1 MEANS MSW  */
            sparc_coprocessor_ptr->CREG[RD+1]= sparcv8_mmu_memory_data_load_doubleword((RS1+RS2),0);
        }

    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);

        if ( ((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) & 0x07) !=0 )
        {
            /* MEMORY ADDRESS NOT ALLIGNED TRAP */

            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }

        if( (RD & 0x1) == 0) /* THE MORE SIGNIFICANT WORD AT THE EFFECTIVE MEMORY ADDREDD IS MOVED INTO THE EVEN R REGISTER */
        {
            sparc_coprocessor_ptr->CREG[RD]= sparcv8_mmu_memory_data_load_doubleword((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))),1); /* 0 MEANS LSW, 1 MEANS MSW  */
            sparc_coprocessor_ptr->CREG[RD+1]= sparcv8_mmu_memory_data_load_doubleword((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))),0);
        }
    }
    return;
}

/* LOAD WORD COPROCESSOR STATE REGISTER */

void sparcv8_inst_set_LDCSR(ULONG instruction_field)
{

    /*  TRAP CATALOGUE FOR LDCSR INSTRUCTION
    *
    *  cp_disabled -- DONE
    *  cp_exception -- REMAINING
    *  data_access_exception -- REMAINING
    *  mem_address_not_aligned -- DONE
    *  data_access_error -- REMAINING
    */

    if ((sparcv8_inst_set_extra_RDPSR(EC) == 0) | (interface_signals_ptr->bp_CP_present ==0 ))
    {
        printf(" COPROCESSOR UNIT DESABLED TRAP \n");
        sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->cp_disabled);
        sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
        sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
    }

    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }

    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }

        if ( ((RS1+RS2) & 0x03)  !=0 )
        {
            /* MEMORY ADDRESS NOT ALLIGNED TRAP */

            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        sparc_coprocessor_ptr->CSR=sparcv8_mmu_memory_data_load_word(RS1+RS2);
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);

        if ( ((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) & 0x03)  !=0 )
        {
            /* MEMORY ADDRESS NOT ALLIGNED TRAP */

            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        sparc_coprocessor_ptr->CSR=sparcv8_mmu_memory_data_load_word(RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
    }

    return;
}

/* STORE BYTE */

void sparcv8_inst_set_STB(ULONG instruction_field)
{

    /*  TRAP CATALOGUE FOR STB INSTRUCTION
    *
    *  illegal_instruction (store alternate with i = 1; STD, STDA with odd rd) -- NO NEED
    *  privileged_instruction (store alternate only) -- NO NEED
    *  mem_address_not_aligned (excluding STB and STBA) -- NO NEED
    *  data_access_exception -- NO NEED
    *  data_access_error -- NO NEED
    *  data_store_error -- NO NEED
    */


    ULONG RD=helper_instruction_field_rd(instruction_field);
    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    if(RD<8)
    {
        RD=(sparc_intunit_ptr->windowregs.GREG[RD] & 0x000000FF);
    }
    else
    {
        RD=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))]) ;
    }
    if(RS1 < 8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        sparcv8_mmu_memory_data_store_byte(RD,RS1+RS2);

    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);

        sparcv8_mmu_memory_data_store_byte(RD,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
    }
}

/* STORE HALFWORD */

void sparcv8_inst_set_STH(ULONG instruction_field)
{
    /*  TRAP CATALOGUE FOR STH INSTRUCTION
    *
    *  illegal_instruction (store alternate with i = 1; STD, STDA with odd rd) -- NO NEED
    *  privileged_instruction (store alternate only) -- NO NEED
    *  mem_address_not_aligned (excluding STB and STBA) -- DONE
    *  data_access_exception -- NO NEED
    *  data_access_error -- NO NEED
    *  data_store_error -- NO NEED
    */

    ULONG RD=helper_instruction_field_rd(instruction_field);
    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    if(RD<8)
    {
        RD=(sparc_intunit_ptr->windowregs.GREG[RD] & 0x0000FFFF);
    }
    else
    {
        RD=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))]);
    }

    if(RS1 < 8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if (((RS1+RS2) & 0x01) != 0)
        {
            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        sparcv8_mmu_memory_data_store_halfword(RD,RS1+RS2);

    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if (((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) & 0x01) != 0)
        {
            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        sparcv8_mmu_memory_data_store_halfword(RD,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
    }
}

/* STORE WORD */

void sparcv8_inst_set_ST(ULONG instruction_field)
{
    /*  TRAP CATALOGUE FOR ST INSTRUCTION
    *
    *  illegal_instruction (store alternate with i = 1; STD, STDA with odd rd) -- NO NEED
    *  privileged_instruction (store alternate only) -- NO NEED
    *  mem_address_not_aligned (excluding STB and STBA) -- DONE
    *  data_access_exception -- NO NEED
    *  data_access_error -- NO NEED
    *  data_store_error -- NO NEED
    */

    ULONG RD=helper_instruction_field_rd(instruction_field);
    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    if(RD<8)
    {
        RD=sparc_intunit_ptr->windowregs.GREG[RD];
    }
    else
    {
        RD=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))]);
    }

    if(RS1 < 8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }

        if (((RS1+RS2) & 0x03) != 0)
        {
            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        sparcv8_mmu_memory_data_store_word(RD,RS1+RS2);

    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);

        if (((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) & 0x03) != 0)
        {
            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        sparcv8_mmu_memory_data_store_word(RD,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
    }
}

/* STORE DOUBLEWORD */

void sparcv8_inst_set_STD(ULONG instruction_field)
{
    /*  TRAP CATALOGUE FOR STD INSTRUCTION
    *
    *  illegal_instruction (store alternate with i = 1; STD, STDA with odd rd) -- DONE
    *  privileged_instruction (store alternate only) -- NO NEED
    *  mem_address_not_aligned (excluding STB and STBA) -- DONE
    *  data_access_exception -- NO NEED
    *  data_access_error -- NO NEED
    *  data_store_error -- NO NEED
    */

    ULONG RD=helper_instruction_field_rd(instruction_field) & 0x1E ; /* THE LEAST SIGNIFICANT BIT OF THE RD FIELD (5-BIT) IS UNUSED AND SHOULD BE SET TO ZERO BY SOFTWARE */
    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    ULONG RD0;
    ULONG RD1;

    if ((RD & 0x1) != 0)
    {
        /* ILLEGAL INSTRUCTION TRAP */
        printf("ILLEGAL INSTRUCTION TRAP \n");
        sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->illegal_instruction);
        sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
        sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
    }

    if( RD < 8 && ((RD & 0x1) == 0) ) /* THE MORE SIGNIFICANT WORD AT THE EFFECTIVE MEMORY ADDRESS IS MOVED INTO THE EVEN R REGISTER */
    {
        RD0=sparc_intunit_ptr->windowregs.GREG[RD];
        RD1=sparc_intunit_ptr->windowregs.GREG[RD+1];
    }
    else if( RD >= 8 && ((RD & 0x1) == 0) )/* THE MORE SIGNIFICANT WORD AT THE EFFECTIVE MEMORY ADDRESS IS MOVED INTO THE EVEN R REGISTER */
    {
        RD0= *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(helper_instruction_field_rd(instruction_field)-8))]);
        RD1= *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(helper_instruction_field_rd(instruction_field)-7))]);
    }

    if(RS1 < 8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if (((RS1+RS2) & 0x07) != 0)
        {
            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        sparcv8_mmu_memory_data_store_doubleword(RD0,RS1+RS2,1); /* 0 MEANS LSW, 1 MEANS MSW  */
        sparcv8_mmu_memory_data_store_doubleword(RD1,RS1+RS2,0);
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);

        if (((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) & 0x07) != 0)
        {
            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }

        sparcv8_mmu_memory_data_store_doubleword(RD0,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)),1); /* 0 MEANS LSW, 1 MEANS MSW  */
        sparcv8_mmu_memory_data_store_doubleword(RD1,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)),0);
    }
}

/* STORE FLOATING POINT */

void sparcv8_inst_set_STF(ULONG instruction_field)
{
    /*  TRAP CATALOGUE FOR STF INSTRUCTION
    *
    *  fp_disabled -- DONE
    *  fp_exception (sequence_error(STDFQ)) -- NO NEED
    *  privileged_instruction (STDFQ only) -- NO NEED
    *  mem_address_not_aligned -- DONE
    *  data_access_exception-- NO NEED
    *  data_access_error -- NO NEED
    *  data_store_error -- NO NEED
    */

    if ((sparcv8_inst_set_extra_RDPSR(EF) == 0) | (interface_signals_ptr->bp_FPU_present ==0 ))
    {
        printf(" FLOATING POINT DESABLED TRAP \n");
        sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->fp_disabled);
        sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
        sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
    }

    ULONG RD=helper_instruction_field_rd(instruction_field) & 0x1E ;/* THE LEAST SIGNIFICANT BIT OF THE RD FIELD (5-BIT) IS UNUSED AND SHOULD BE SET TO ZERO BY SOFTWARE */
    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    if(RS1 < 8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }

        if (((RS1+RS2) & 0x03) != 0)
        {
            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        sparcv8_mmu_memory_data_store_word(sparc_fpu_ptr->FREG[RD],RS1+RS2);
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if (((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) & 0x03) != 0)
        {
            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        sparcv8_mmu_memory_data_store_word(sparc_fpu_ptr->FREG[RD],RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
    }
}

/* STORE DOUBLE FLOATING POINT */

void sparcv8_inst_set_STDF(ULONG instruction_field)
{
    /*  TRAP CATALOGUE FOR STF INSTRUCTION
    *
    *  fp_disabled -- DONE
    *  fp_exception (sequence_error(STDFQ)) -- DONE
    *  privileged_instruction (STDFQ only) -- NO NEED
    *  mem_address_not_aligned -- DONE
    *  data_access_exception-- NO NEED
    *  data_access_error -- NO NEED
    *  data_store_error -- NO NEED
    */

    if ((sparcv8_inst_set_extra_RDPSR(EF) == 0) | (interface_signals_ptr->bp_FPU_present ==0 ))
    {
        printf(" FLOATING POINT DESABLED TRAP \n");
        sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->fp_disabled);
        sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
        sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
    }

    ULONG RD=helper_instruction_field_rd(instruction_field) & 0x1E ; /* THE LEAST SIGNIFICANT BIT OF THE RD FIELD (5-BIT) IS UNUSED AND SHOULD BE SET TO ZERO BY SOFTWARE */

    if ( (RD & 0x01) !=0 )
    {
        printf(" FLOATING POINT EXCEPTION TRAP \n");
        sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->fp_exception);
        sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
        sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
    }

    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    if(RS1 < 8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if (((RS1+RS2) & 0x07) != 0)
        {
            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }

        sparcv8_mmu_memory_data_store_doubleword(sparc_fpu_ptr->FREG[RD],RS1+RS2,1); /* 0 MEANS LSW, 1 MEANS MSW  */
        sparcv8_mmu_memory_data_store_doubleword(sparc_fpu_ptr->FREG[RD+1],RS1+RS2,0);
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);

        if (((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) & 0x07) != 0)
        {
            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }

        sparcv8_mmu_memory_data_store_doubleword(sparc_fpu_ptr->FREG[RD],RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)),1); /* 0 MEANS LSW, 1 MEANS MSW  */
        sparcv8_mmu_memory_data_store_doubleword(sparc_fpu_ptr->FREG[RD+1],RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)),0);
    }
}

/* STORE FSR */
void sparcv8_inst_set_STFSR(ULONG instruction_field)
{
    /*  TRAP CATALOGUE FOR STF INSTRUCTION
    *
    *  fp_disabled -- DONE
    *  fp_exception (sequence_error(STDFQ)) -- DONE
    *  privileged_instruction (STDFQ only) -- NO NEED
    *  mem_address_not_aligned -- DONE
    *  data_access_exception-- NO NEED
    *  data_access_error -- NO NEED
    *  data_store_error -- NO NEED
    */

    if ((sparcv8_inst_set_extra_RDPSR(EF) == 0) | (interface_signals_ptr->bp_FPU_present ==0 ))
    {
        printf(" FLOATING POINT DESABLED TRAP \n");
        sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->fp_disabled);
        sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
        sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
    }

    /*(WHILE FPOP INST ARE NOT EXECUTED) {WAIT}*/
    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }

    while(sparcv8_inst_set_extra_RDFSR(QNE) == TRUE)
    {
        /* { wait for pending floating-point instructions to complete } */
    }

    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);

        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if (((RS1+RS2) & 0x03) != 0)
        {
            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        sparcv8_mmu_memory_data_store_word(sparc_fpu_ptr->FSR,RS1+RS2);
    }

    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);

        if (((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) & 0x03) != 0)
        {
            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }

        sparcv8_mmu_memory_data_store_word(sparc_fpu_ptr->FSR,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));

    }
    helper_write_value(14,16,sparc_fpu_ptr->FSR,0); /*STFSR may zero FSR.ftt after writing the FSR to memory*/

    return;
}

/* STORE COPROCESSOR */

void sparcv8_inst_set_STC(ULONG instruction_field)
{
    /*  TRAP CATALOGUE FOR STF INSTRUCTION
    *
    *  cp_disabled -- DONE
    *  cp_exception -- NO NEED
    *  privileged_instruction (STDCQ only) -- NO NEED
    *  mem_address_not_aligned -- DONE
    *  data_access_exception -- NO NEED
    *  illegal_instruction (STDCQ only; implementation-dependent) -- NO NEED
    *  data_access_error -- NO NEED
    *  data_store_error -- NO NEED
    */

    if ((sparcv8_inst_set_extra_RDPSR(EC) == 0) | (interface_signals_ptr->bp_CP_present ==0 ))
    {
        printf(" COPROCESSOR UNIT DESABLED TRAP \n");
        sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->cp_disabled);
        sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
        sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
    }

    ULONG RD=helper_instruction_field_rd(instruction_field) & 0x30; /* THE LEAST SIGNIFICANT BIT OF THE RD FIELD (5-BIT) IS UNUSED AND SHOULD BE SET TO ZERO BY SOFTWARE */
    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    if((RD & 0x1) == 1) /* THE MORE SIGNIFICANT WORD AT THE EFFECTIVE MEMORY ADDREDD IS MOVED INTO THE EVEN R REGISTER */
    {
        printf("THE RD (FIELD)  REGISTER IS NOT EVEN");
    }
    if(RS1 < 8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if (((RS1+RS2) & 0x03) != 0)
        {
            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        sparcv8_mmu_memory_data_store_word(sparc_coprocessor_ptr->CREG[RD],RS1+RS2);
    }

    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if (((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) & 0x03) != 0)
        {
            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        sparcv8_mmu_memory_data_store_word(sparc_coprocessor_ptr->CREG[RD],RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
    }
}

/* STORE DOUBLE COPROCESSOR */

void sparcv8_inst_set_STDC(ULONG instruction_field)
{
    /*  TRAP CATALOGUE FOR STF INSTRUCTION
    *
    *  cp_disabled -- DONE
    *  cp_exception -- NO NEED
    *  privileged_instruction (STDCQ only) -- NO NEED
    *  mem_address_not_aligned -- DONE
    *  data_access_exception -- NO NEED
    *  illegal_instruction (STDCQ only; implementation-dependent) -- NO NEED
    *  data_access_error -- NO NEED
    *  data_store_error -- NO NEED
    */
    if ((sparcv8_inst_set_extra_RDPSR(EC) == 0) | (interface_signals_ptr->bp_CP_present ==0 ))
    {
        printf(" COPROCESSOR UNIT DESABLED TRAP \n");
        sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->cp_disabled);
        sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
        sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
    }

    ULONG RD=helper_instruction_field_rd(instruction_field) & 0x30; /* THE LEAST SIGNIFICANT BIT OF THE RD FIELD (5-BIT) IS UNUSED AND SHOULD BE SET TO ZERO BY SOFTWARE */
    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    if(RS1 < 8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if (((RS1+RS2) & 0x07) != 0)
        {
            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        sparcv8_mmu_memory_data_store_doubleword(sparc_coprocessor_ptr->CREG[RD],RS1+RS2,1); /* 0 MEANS LSW, 1 MEANS MSW  */
        sparcv8_mmu_memory_data_store_doubleword(sparc_coprocessor_ptr->CREG[RD+1],RS1+RS2,0);
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if (((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) & 0x07) != 0)
        {
            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        sparcv8_mmu_memory_data_store_doubleword(sparc_coprocessor_ptr->CREG[RD],RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)),1); /* 0 MEANS LSW, 1 MEANS MSW  */
        sparcv8_mmu_memory_data_store_doubleword(sparc_coprocessor_ptr->CREG[RD+1],RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)),0);
    }
}

/* STORE COPROCESSOR STATE */

void sparcv8_inst_set_STCSR(ULONG instruction_field)
{
    /*  TRAP CATALOGUE FOR STF INSTRUCTION
    *
    *  cp_disabled -- DONE
    *  cp_exception -- NO NEED
    *  privileged_instruction (STDCQ only) -- NO NEED
    *  mem_address_not_aligned -- DONE
    *  data_access_exception -- NO NEED
    *  illegal_instruction (STDCQ only; implementation-dependent) -- NO NEED
    *  data_access_error -- NO NEED
    *  data_store_error -- NO NEED
    */
    if ((sparcv8_inst_set_extra_RDPSR(EC) == 0) | (interface_signals_ptr->bp_CP_present ==0 ))
    {
        printf(" COPROCESSOR UNIT DESABLED TRAP \n");
        sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->cp_disabled);
        sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
        sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
    }

    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];

    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }

    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if (((RS1+RS2) & 0x03) != 0)
        {
            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        sparcv8_mmu_memory_data_store_word(sparcv8_inst_set_extra_RDCSR(0,CSRALL),RS1+RS2);
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if (((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) & 0x03) != 0)
        {
            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        sparcv8_mmu_memory_data_store_word(sparcv8_inst_set_extra_RDCSR(0,CSRALL),RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
    }

    return;
}

///////////////////////////////////////////////////////////////////////   ARITHMETIC & LOGICAL OPERATIONS INSTRUCTIONS //////////////////////////////////////////////////////////////////////////////////

/* SHIFT LEFT LOGICAL  */

void sparcv8_inst_set_SLL(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);

        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2] & 0x1F; /* IF i=0 THE 27 MSB OF R[RS2] ARE IGNORED*/
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]) & 0x1F; /* IF i=0 THE 27 MSB OF R[RS2] ARE IGNORED*/
        }

        if(RS1<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RS1] = sparc_intunit_ptr->windowregs.GREG[RS1] << RS2;
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]) = *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]) << RS2;
        }
    }
    else if(helper_instruction_field_i(instruction_field) == TRUE)
    {
        if(RS1<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RS1] = sparc_intunit_ptr->windowregs.GREG[RS1]  << helper_instruction_field_simm13(instruction_field & 0x1F);/* IF i=1 BITS 5-12 OF
        THE SHIFT INSTRUCTION ARE RESERVED AND SHOULD BE SUPPLIED AS ZERO BY SOFTEARE*/
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]) = *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]) << helper_instruction_field_simm13(instruction_field & 0x1F);/* IF i=1 BITS 5-12 OF
        THE SHIFT INSTRUCTION ARE RESERVED AND SHOULD BE SUPPLIED AS ZERO BY SOFTEARE*/
        }
    }
}

/* SHIFT RIGHT LOGICAL  */

void sparcv8_inst_set_SRL(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);

        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2] & 0x1F; /* IF i=0 THE 27 MSB OF R[RS2] ARE IGNORED*/
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]) & 0x1F; /* IF i=0 THE 27 MSB OF R[RS2] ARE IGNORED*/
        }

        if(RS1<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RS1] = sparc_intunit_ptr->windowregs.GREG[RS1] >> RS2;
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]) = *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]) >> RS2;
        }
    }
    else if(helper_instruction_field_i(instruction_field) == TRUE)
    {
        if(RS1<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RS1] = sparc_intunit_ptr->windowregs.GREG[RS1]  >> helper_instruction_field_simm13(instruction_field & 0x1F);/* IF i=1 BITS 5-12 OF
        THE SHIFT INSTRUCTION ARE RESERVED AND SHOULD BE SUPPLIED AS ZERO BY SOFTEARE*/
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]) = *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]) >> helper_instruction_field_simm13(instruction_field & 0x1F);/* IF i=1 BITS 5-12 OF
        THE SHIFT INSTRUCTION ARE RESERVED AND SHOULD BE SUPPLIED AS ZERO BY SOFTEARE*/
        }
    }
}


/* SHIFT RIGHT ARITHMETIC  */

void sparcv8_inst_set_SRA(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    UINT8 counter;
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);

        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2] & 0x1F; /* IF i=0 THE 27 MSB OF R[RS2] ARE IGNORED*/
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]) & 0x1F; /* IF i=0 THE 27 MSB OF R[RS2] ARE IGNORED*/
        }

        if(RS1<8)
        {
            if(helper_read_value(31,31,sparc_intunit_ptr->windowregs.GREG[RS1]) ==1 )
            {
                sparc_intunit_ptr->windowregs.GREG[RS1] = sparc_intunit_ptr->windowregs.GREG[RS1] >> RS2;

                /* SRA FILLS VACATED POSITION WITH THE MOST SIGNIFICANT BIT OF R[RS1] */

                for(counter=0; counter<=RS2; counter++)
                {
                    helper_write_value(31-counter,31-counter, sparc_intunit_ptr->windowregs.GREG[RS1],1);
                }
            }
            else
            {
                sparc_intunit_ptr->windowregs.GREG[RS1] = sparc_intunit_ptr->windowregs.GREG[RS1] >> RS2;
            }
        }
        else
        {
            if(helper_read_value(31,31,sparc_intunit_ptr->windowregs.GREG[RS1]) ==1 )
            {
                *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]) = *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]) >> RS2;

                /* SRA FILLS VACATED POSITION WITH THE MOST SIGNIFICANT BIT OF R[RS1] */

                for(counter=0; counter<=RS2; counter++)
                {
                    helper_write_value(31-counter,31-counter, *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]),1);
                }
            }
            else
            {
                *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]) = *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]) >> RS2;
            }
        }
    }
    else if(helper_instruction_field_i(instruction_field) == TRUE)
    {
        if(RS1<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RS1] = sparc_intunit_ptr->windowregs.GREG[RS1]  >> helper_instruction_field_simm13(instruction_field & 0x1F);/* IF i=1 BITS 5-12 OF
        THE SHIFT INSTRUCTION ARE RESERVED AND SHOULD BE SUPPLIED AS ZERO BY SOFTEARE*/
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]) = *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]) >> helper_instruction_field_simm13(instruction_field & 0x1F);/* IF i=1 BITS 5-12 OF
        THE SHIFT INSTRUCTION ARE RESERVED AND SHOULD BE SUPPLIED AS ZERO BY SOFTEARE*/
        }
    }
}




/*SETHI INSTRUCTION*/

void sparcv8_inst_set_SETHI_or_NOP(ULONG instruction_field)
{
    if (helper_instruction_field_imm22(instruction_field) != 0)
    {

        ULONG RD=helper_instruction_field_rd(instruction_field);

        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]= (sparc_intunit_ptr->windowregs.GREG[RD] & 0x0) | (helper_instruction_field_imm22(instruction_field) << 9) ;
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=(sparc_intunit_ptr->windowregs.GREG[RD] & 0x0) & (helper_instruction_field_imm22(instruction_field) << 9) ;
        }
    }
    else if (helper_instruction_field_imm22(instruction_field) == 0)
    {
        /*NOP INSTRUCTION*/
        sparc_intunit_ptr->PC=sparc_intunit_ptr->nPC;
        sparc_intunit_ptr->nPC+=4;
        return;
    }
}

void sparcv8_inst_set_default_inst(ULONG instruction_field)
{
    /*NOTHING TO BE DONE FOR THEIS INSTRUCTION*/
    return;
}

/* ADD INSTRUCTION */

void sparcv8_inst_set_ADD(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }
    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1+RS2;
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1+RS2;
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));
        }
    }
}


/* ADD INSTRUCTION WITH CARRY*/

void sparcv8_inst_set_ADDX(ULONG instruction_field) /* ADD eXtended */
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }


    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1+RS2+sparcv8_inst_set_extra_RDPSR(ICC_CARRY);/* ADD CARRY */
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1+RS2+sparcv8_inst_set_extra_RDPSR(ICC_CARRY); /* ADD CARRY */
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))+sparcv8_inst_set_extra_RDPSR(ICC_CARRY); /* ADD CARRY */
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))+sparcv8_inst_set_extra_RDPSR(ICC_CARRY); /* ADD CARRY */
        }
    }
}


/* SUBSTRUCT INSTRUCTION */

void sparcv8_inst_set_SUB(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }


    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1-RS2;
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1-RS2;
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1-((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1-((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));
        }
    }
}



/* SUBSTRUCT INSTRUCTION WITH CARRY */

void sparcv8_inst_set_SUBX(ULONG instruction_field) /* SUBSTRUCT eXtended */
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }


    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1-RS2-sparcv8_inst_set_extra_RDPSR(ICC_CARRY); /* SUBSTRUCT CARRY */
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1-RS2-sparcv8_inst_set_extra_RDPSR(ICC_CARRY); /* SUBSTRUCT CARRY */
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1-((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))-sparcv8_inst_set_extra_RDPSR(ICC_CARRY); /* SUBSTRUCT CARRY */
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1-((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))-sparcv8_inst_set_extra_RDPSR(ICC_CARRY); /* SUBSTRUCT CARRY */
        }
    }
}





/* UNSIGNED MULTIPLY INSTRUCTION */

void sparcv8_inst_set_UMUL(ULONG instruction_field)
{

    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    ULONG RD=helper_instruction_field_rd(instruction_field);

    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }
    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=helper_unsigned_ll_lsw((DOUBLE64)(RS1*RS2)); /* LSW */
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=helper_unsigned_ll_lsw((DOUBLE64)(RS1*RS2)); /* LSW */
        }
        sparcv8_inst_set_extra_WRY(0,YALL,helper_unsigned_ll_msw((DOUBLE64)(RS1*RS2))); /* MSW */
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=helper_unsigned_ll_lsw((DOUBLE64)(RS1*((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))); /* LSW */
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=helper_unsigned_ll_lsw((DOUBLE64)(RS1*((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))); /* LSW */
        }
        sparcv8_inst_set_extra_WRY(0,YALL,helper_unsigned_ll_msw((DOUBLE64)(RS1*((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))); /* MSW */
    }
}




/* SIGNED MULTIPLY INSTRUCTION */

void sparcv8_inst_set_SMUL(ULONG instruction_field)
{

    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    ULONG RD=helper_instruction_field_rd(instruction_field);

    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }
    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8) /* USE OF RD VALUE NEEDS (INT32) CASTING */
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=helper_unsigned_ll_lsw((DOUBLE64)((INT32)RS1*(INT32)RS2)); /* LSW */
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=helper_unsigned_ll_lsw((DOUBLE64)((INT32)RS1*(INT32)RS2)); /* LSW */
        }
        sparcv8_inst_set_extra_WRY(0,YALL,helper_unsigned_ll_msw((DOUBLE64)(RS1*RS2))); /* MSW */
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=helper_unsigned_ll_lsw((DOUBLE64)((INT32)RS1*(INT32)((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))); /* LSW */
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=helper_unsigned_ll_lsw((DOUBLE64)((INT32)RS1*(INT32)((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))); /* LSW */
        }
        sparcv8_inst_set_extra_WRY(0,YALL,helper_unsigned_ll_msw((DOUBLE64)((INT32)RS1*(INT32)((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))); /* MSW */
    }
}




/* UNSIGNED DIVIDE INSTRUCTION */

void sparcv8_inst_set_UDIV(ULONG instruction_field)
{
    /*  TRAP CATALOGUE FOR UDIV INSTRUCTION
     *  division_by_zero
     */

    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    ULONG Y=sparcv8_inst_set_extra_RDY(0,YALL);
    ULONG RD=helper_instruction_field_rd(instruction_field);

    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }
    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if (RS2 == 0)
        {
            printf(" DIVISION BY ZERO TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->division_by_zero);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }

        if(RD<8)
        {
            if ( (((DOUBLE64)(RS1*Y))/RS2) > 0xffffffff )
            {
                sparc_intunit_ptr->windowregs.GREG[RD]=0xffffffff;
            }
            else
            {
                sparc_intunit_ptr->windowregs.GREG[RD]=(((DOUBLE64)(RS1*Y))/RS2);
            }
        }
        else
        {
            if ( (   (     (DOUBLE64)(RS1*Y)    )   /RS2) > 0xffffffff )
            {
                *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=0xffffffff;
            }
            else
            {
                *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=(((DOUBLE64)(RS1*Y))/RS2);
            }
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);

        if (((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)) == 0)
        {
            printf(" DIVISION BY ZERO TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->division_by_zero);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        if(RD<8)
        {
            if ( (((DOUBLE64)(RS1*Y))/((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) > 0xffffffff )
            {
                sparc_intunit_ptr->windowregs.GREG[RD]=0xffffffff ;
            }
            else
            {
                sparc_intunit_ptr->windowregs.GREG[RD]=(((DOUBLE64)(RS1*Y))/((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
            }
        }
        else
        {
            if ( (((DOUBLE64)(RS1*Y))/((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) > 0xffffffff )
            {
                *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=0xffffffff;
            }
            else
            {
                *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=(((DOUBLE64)(RS1*Y))/((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
            }
        }
    }
}



/* SIGNED DIVIDE INSTRUCTION */

void sparcv8_inst_set_SDIV(ULONG instruction_field)
{
    /*  TRAP CATALOGUE FOR SDIV INSTRUCTION
     *  division_by_zero
     */

    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    ULONG Y=sparcv8_inst_set_extra_RDY(0,YALL);
    ULONG RD=helper_instruction_field_rd(instruction_field);

    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }
    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if (RS2 == 0)
        {
            printf(" DIVISION BY ZERO TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->division_by_zero);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        if(RD<8)
        {
            if (((DOUBLE64)((INT32)RS1*(INT32)Y)/RS2) > 0x7fffffff)
            {
                sparc_intunit_ptr->windowregs.GREG[RD]=0x7fffffff;
            }
            else if (((DOUBLE64)((INT32)RS1*(INT32)Y)/RS2) < 0x80000000)
            {
                sparc_intunit_ptr->windowregs.GREG[RD]=0x80000000;
            }
            else
            {
                sparc_intunit_ptr->windowregs.GREG[RD]=(((DOUBLE64)((INT32)RS1*(INT32)Y))/RS2);
            }
        }
        else
        {
            if (((DOUBLE64)((INT32)RS1*(INT32)Y)/RS2) > 0x7fffffff)
            {
                *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=0x7fffffff;
            }
            else if (((DOUBLE64)((INT32)RS1*(INT32)Y)/RS2)< 0x80000000)
            {
                *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=0x80000000;
            }
            else
            {
                *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=(((DOUBLE64)((INT32)RS1*(INT32)Y))/RS2);
            }
        }
    }

    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);

        if (((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)) == 0)
        {
            printf(" DIVISION BY ZERO TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->division_by_zero);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        if(RD<8)
        {
            if (((DOUBLE64)((INT32)RS1*(INT32)Y) / ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) > 0x7fffffff)
            {
                sparc_intunit_ptr->windowregs.GREG[RD]=0x7fffffff ;
            }
            else if (((DOUBLE64)((INT32)RS1*(INT32)Y) / ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) < 0x80000000)
            {
                sparc_intunit_ptr->windowregs.GREG[RD]=0x80000000;
            }
            else
            {
                sparc_intunit_ptr->windowregs.GREG[RD]=(((DOUBLE64)((INT32)RS1*(INT32)Y))/((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
            }
        }
        else
        {
            if (((DOUBLE64)((INT32)RS1*(INT32)Y) / ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) > 0x7fffffff)
            {
                *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=0x7fffffff;
            }
            else if (((DOUBLE64)((INT32)RS1*(INT32)Y) / ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))  < 0x80000000)
            {
                *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=0x80000000;
            }
            else
            {
                *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=(((DOUBLE64)((INT32)RS1*(INT32)Y))/((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
            }
        }
    }
}
/* LOGICAL INSTRUCTION AND  */

void sparcv8_inst_set_AND(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }


    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1 & RS2;
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1 & RS2;
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1 & ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1 & ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));
        }
    }
}



/* LOGICAL INSTRUCTION NAND */

void sparcv8_inst_set_NAND(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }


    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=~(RS1 & RS2);
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=~(RS1 & RS2);
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=~(RS1 & ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=~(RS1 & ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
        }
    }
}



/* LOGICAL INSTRUCTION OR  */

void sparcv8_inst_set_OR(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }


    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1 | RS2;
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1 | RS2;
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1 | ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1 | ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));
        }
    }
}


/* LOGICAL INSTRUCTION NOR */

void sparcv8_inst_set_NOR(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }


    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=~(RS1 | RS2);
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=~(RS1 | RS2);
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=~(RS1 | ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=~(RS1 | ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
        }
    }
}




/* LOGICAL INSTRUCTION XOR  */

void sparcv8_inst_set_XOR(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }


    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1 ^ RS2;
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1 ^ RS2;
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1 ^ ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1 ^ ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));
        }
    }
}




/* LOGICAL INSTRUCTION XNOR */

void sparcv8_inst_set_XNOR(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }


    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=~(RS1 ^ RS2);
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=~(RS1 ^ RS2);
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=~(RS1 ^ ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=~(RS1 ^ ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
        }
    }
}


///////////////////////////////////////////////////////////////////////  CONTROL TRANSFER INSTRUCTIONS /////////////////////////////////////////////////////////////////////////////////////

/* SAVE INSTRUCTION */

void sparcv8_inst_set_SAVE(ULONG instruction_field)
{
    /*  TRAP CATALOGUE FOR SAVE INSTRUCTION
    *   window_overflow (SAVE only)
    */

    ULONG registers;
    if  ((ULONG)pow(2,sparcv8_inst_set_extra_RDPSR(CWP)) == 0) /* COMPARE CWP WITH WIM  */
    {
        printf("TRAP  - WINDOW OVERFLOW\n");
        sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->window_overflow);
        sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
        sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        return;
    }
    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED  \n");
        return;
    }

    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparcv8_inst_set_extra_WRPSR(CWP,sparcv8_inst_set_extra_RDPSR(CWP)-1);
            sparc_intunit_ptr->windowregs.GREG[RD]=(RS1 + RS2);

        }
        else
        {
            sparcv8_inst_set_extra_WRPSR(CWP,sparcv8_inst_set_extra_RDPSR(CWP)-1);
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=(RS1 + RS2);
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparcv8_inst_set_extra_WRPSR(CWP,sparcv8_inst_set_extra_RDPSR(CWP)-1);
            sparc_intunit_ptr->windowregs.GREG[RD]=(RS1 + ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));

        }
        else
        {
            sparcv8_inst_set_extra_WRPSR(CWP,sparcv8_inst_set_extra_RDPSR(CWP)-1);
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=(RS1 + ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
        }
    }
    /*COPY OUTGOING REGISTERS OF  WINDOW[CWP] TO INPUT REGISTERS OF WINDOW[CWP-1]*/
    for (registers=0; registers<8; registers++)
    {
        *sparc_proc_integer_unit_windowregs_ptr[(24*sparcv8_inst_set_extra_RDPSR(CWP))+16+registers] = *sparc_proc_integer_unit_windowregs_ptr[(24*(sparcv8_inst_set_extra_RDPSR(CWP)+1))+registers];
    }
    /* INCREASE NEW STACK POINTER BY 96 BYTES THAN NEW FP (OLD WINDOW SP)*/
    *sparc_proc_integer_unit_windowregs_ptr[(24*sparcv8_inst_set_extra_RDPSR(CWP))+6] = *sparc_proc_integer_unit_windowregs_ptr[(24*sparcv8_inst_set_extra_RDPSR(CWP))+22] - 96;
}

/* RESTORE INSTRUCTION */

void sparcv8_inst_set_RESTORE(ULONG instruction_field)
{
    /*  TRAP CATALOGUE FOR RETORE INSTRUCTION
    *  window_underflow (RESTORE only)
    */

    ULONG registers;

    if ( ((ULONG)pow(2,sparcv8_inst_set_extra_RDPSR(CWP)) & sparcv8_inst_set_extra_RDWIM(0,WIMALL)) != 0)
    {
        printf("trap occured - WINDOW UNDERFLOW\n");
        sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->window_underflow);
        sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
        sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        return;
    }
    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED -- trap \n");
        return;
    }

    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparcv8_inst_set_extra_WRPSR(CWP,sparcv8_inst_set_extra_RDPSR(CWP)+1);
            sparc_intunit_ptr->windowregs.GREG[RD]=(RS1 + RS2);


        }
        else
        {
            sparcv8_inst_set_extra_WRPSR(CWP,sparcv8_inst_set_extra_RDPSR(CWP)+1);
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=(RS1 + RS2);
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparcv8_inst_set_extra_WRPSR(CWP,sparcv8_inst_set_extra_RDPSR(CWP)+1);
            sparc_intunit_ptr->windowregs.GREG[RD]=(RS1 + ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));


        }
        else
        {
            sparcv8_inst_set_extra_WRPSR(CWP,sparcv8_inst_set_extra_RDPSR(CWP)+1);
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=(RS1 + ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
        }
    }
    /*COPY OUTGOING REGISTERS OF  WINDOW[CWP] TO INPUT REGISTERS OF WINDOW[CWP-1]*/
    for (registers=0; registers<8; registers++)
    {
        *sparc_proc_integer_unit_windowregs_ptr[(24*sparcv8_inst_set_extra_RDPSR(CWP))+registers] = *sparc_proc_integer_unit_windowregs_ptr[(24*(sparcv8_inst_set_extra_RDPSR(CWP)-1))+16+registers];
    }
    /* DECREASE OLD STACK POINTER BY 96 BYTES THAN OLD FP (NEW WINDOW SP)*/
    *sparc_proc_integer_unit_windowregs_ptr[(24*sparcv8_inst_set_extra_RDPSR(CWP))+22] = *sparc_proc_integer_unit_windowregs_ptr[(24*sparcv8_inst_set_extra_RDPSR(CWP))+6] + 96;
}

/* BRANCH INTEGER INSTRUCTIONS */

void sparcv8_inst_set_BICC(ULONG instruction_field)
{
    ULONG cond=helper_instruction_field_cond(instruction_field);
    INT8 eval_icc;
    switch (cond)
    {
    case 0b1000:
        eval_icc=TRUE;
        break;
    case 0b0000:
        eval_icc=FALSE;
        break;
    case 0b1001:
        if(sparcv8_inst_set_extra_RDPSR(ICC_ZERO)==FALSE)
        {
            eval_icc=TRUE;
        }
        else
        {
            eval_icc=FALSE;
        }
        break;
    case 0b0001:
        if(sparcv8_inst_set_extra_RDPSR(ICC_ZERO)==TRUE)
        {
            eval_icc=TRUE;
        }
        else
        {
            eval_icc=FALSE;
        }
        break;
    case 0b1010:
        if    ((sparcv8_inst_set_extra_RDPSR(ICC_ZERO) | (sparcv8_inst_set_extra_RDPSR(ICC_NEGATIVE) ^ sparcv8_inst_set_extra_RDPSR(ICC_OVERFLOW))) == FALSE )
        {
            eval_icc=TRUE;
        }
        else
        {
            eval_icc=FALSE;
        }
        break;
    case 0b0010:
        if    ((sparcv8_inst_set_extra_RDPSR(ICC_ZERO) | (sparcv8_inst_set_extra_RDPSR(ICC_NEGATIVE) ^ sparcv8_inst_set_extra_RDPSR(ICC_OVERFLOW))) == TRUE )
        {
            eval_icc=TRUE;
        }
        else
        {
            eval_icc=FALSE;
        }
        break;
    case 0b1011:
        if ( (sparcv8_inst_set_extra_RDPSR(ICC_NEGATIVE) ^ sparcv8_inst_set_extra_RDPSR(ICC_OVERFLOW)) == FALSE )
        {
            eval_icc=TRUE;
        }
        else
        {
            eval_icc=FALSE;
        }
        break;
    case 0b0011:
        if ( (sparcv8_inst_set_extra_RDPSR(ICC_NEGATIVE) ^ sparcv8_inst_set_extra_RDPSR(ICC_OVERFLOW)) == TRUE )
        {
            eval_icc=TRUE;
        }
        else
        {
            eval_icc=FALSE;
        }
        break;
    case 0b1100:
        if (sparcv8_inst_set_extra_RDPSR(ICC_CARRY) == FALSE && sparcv8_inst_set_extra_RDPSR(ICC_ZERO) == FALSE )
        {
            eval_icc=TRUE;
        }
        else
        {
            eval_icc=FALSE;
        }
        break;
    case 0b0100:
        if (sparcv8_inst_set_extra_RDPSR(ICC_CARRY) == TRUE && sparcv8_inst_set_extra_RDPSR(ICC_ZERO) == TRUE )
        {
            eval_icc=TRUE;
        }
        else
        {
            eval_icc=FALSE;
        }
        break;
    case 0b1101:
        if (sparcv8_inst_set_extra_RDPSR(ICC_CARRY) == FALSE)
        {
            eval_icc=TRUE;
        }
        else
        {
            eval_icc=FALSE;
        }
        break;
    case 0b0101:
        if (sparcv8_inst_set_extra_RDPSR(ICC_CARRY) == TRUE)
        {
            eval_icc=TRUE;
        }
        else
        {
            eval_icc=FALSE;
        }
        break;
    case 0b1110:
        if (sparcv8_inst_set_extra_RDPSR(ICC_NEGATIVE) == FALSE)
        {
            eval_icc=TRUE;
        }
        else
        {
            eval_icc=FALSE;
        }
        break;
    case 0b0110:
        if (sparcv8_inst_set_extra_RDPSR(ICC_NEGATIVE) == TRUE)
        {
            eval_icc=TRUE;
        }
        else
        {
            eval_icc=FALSE;
        }
        break;
    case 0b1111:
        if (sparcv8_inst_set_extra_RDPSR(ICC_OVERFLOW) == FALSE)
        {
            eval_icc=TRUE;
        }
        else
        {
            eval_icc=FALSE;
        }
        break;
    case 0b0111:
        if (sparcv8_inst_set_extra_RDPSR(ICC_OVERFLOW) == TRUE)
        {
            eval_icc=TRUE;
        }
        else
        {
            eval_icc=FALSE;
        }
        break;
    }
    sparc_intunit_ptr->PC=sparc_intunit_ptr->nPC;

    /* TEST IF THE BRANCH IS TAKEN OR NOT */

    if (eval_icc == TRUE)
    {
        sparc_intunit_ptr->nPC = ((helper_instruction_field_disp22(instruction_field) | 0xFFC00000) << 2) + ((ULONG)sparc_intunit_ptr->PC+sparcv8_mmu_memory_program_return_ptr()) ;
        if (cond == 0b1000 && helper_instruction_field_a(instruction_field) == TRUE)
        {
            /* ANNUL */
        }
    }
    else
    {
        sparc_intunit_ptr->nPC+=1;
        if (helper_instruction_field_a(instruction_field) == TRUE)
        {
            /* ANNUL */
        }
    }
}

/* BRANCH FLOATING POINT INSTRUCTIONS */

void sparcv8_inst_set_FBFCC(ULONG instruction_field)
{
    ULONG cond=helper_instruction_field_cond(instruction_field);
    INT8 fcc=sparcv8_inst_set_extra_RDFSR(FTT);
    INT8 eval_fcc;
    switch (cond)
    {
    case 0b1000:
        eval_fcc=TRUE;
        break;
    case 0b0000:

        eval_fcc=FALSE;
        break;
    case 0b0111:
        if (fcc == 3)
        {

            eval_fcc=TRUE;
        }
        else
        {
            eval_fcc=FALSE;
        }
        break;
    case 0b0110:
        if (fcc == 2)
        {

            eval_fcc=TRUE;
        }
        else
        {
            eval_fcc=FALSE;
        }
        break;
    case 0b0101:
        if (fcc == 2 || fcc == 3)
        {

            eval_fcc=TRUE;
        }
        else
        {
            eval_fcc=FALSE;
        }
        break;
    case 0b0100:
        if (fcc == 1)
        {

            eval_fcc=TRUE;
        }
        else
        {
            eval_fcc=FALSE;
        }

        break;
    case 0b0011:
        if (fcc == 1 || fcc == 3)
        {
            eval_fcc=TRUE;
        }
        else
        {
            eval_fcc=FALSE;
        }

        break;
    case 0b0010:
        if (fcc == 1 || fcc == 2)
        {

            eval_fcc=TRUE;
        }
        else
        {
            eval_fcc=FALSE;
        }

        break;
    case 0b0001:
        if (fcc == 1 || fcc == 2 || fcc == 3)
        {

            eval_fcc=TRUE;
        }
        else
        {
            eval_fcc=FALSE;
        }

        break;
    case 0b1001:
        if (fcc == 0)
        {

            eval_fcc=TRUE;
        }
        else
        {
            eval_fcc=FALSE;
        }

        break;
    case 0b1010:
        if (fcc == 0 || fcc == 3)
        {

            eval_fcc=TRUE;
        }
        else
        {
            eval_fcc=FALSE;
        }

        break;
    case 0b1011:
        if (fcc == 0 || fcc == 2)
        {

            eval_fcc=TRUE;
        }
        else
        {
            eval_fcc=FALSE;
        }

        break;
    case 0b1100:
        if (fcc == 0 || fcc == 2 || fcc == 3)
        {

            eval_fcc=TRUE;
        }
        else
        {
            eval_fcc=FALSE;
        }

        break;
    case 0b1101:
        if (fcc == 0 || fcc == 1)
        {

            eval_fcc=TRUE;
        }
        else
        {
            eval_fcc=FALSE;
        }

        break;
    case 0b1110:
        if (fcc == 0 || fcc == 1 || fcc == 3)
        {

            eval_fcc=TRUE;
        }
        else
        {
            eval_fcc=FALSE;
        }


        break;
    case 0b1111:
        if (fcc == 0 || fcc == 1 || fcc == 2)
        {

            eval_fcc=TRUE;
        }
        else
        {
            eval_fcc=FALSE;
        }

        break;
    }
    sparc_intunit_ptr->PC=sparc_intunit_ptr->nPC;
    /* TEST IF THE BRANCH IS TAKEN OR NOT */
    if (eval_fcc == TRUE)
    {
        sparc_intunit_ptr->nPC = ((helper_instruction_field_disp22(instruction_field) | 0xFFC00000) << 2) + ((ULONG)sparc_intunit_ptr->PC+sparcv8_mmu_memory_program_return_ptr()) ;
        if (cond == 0b1000 && helper_instruction_field_a(instruction_field) == TRUE)
        {
            /* ANNUL */
        }
    }
    else
    {
        sparc_intunit_ptr->nPC+=1;
        if (helper_instruction_field_a(instruction_field) == TRUE)
        {
            /* ANNUL */
        }
    }
}

/* BRANCH COPROCESSOR INSTRUCTIONS */

void sparcv8_inst_set_CBCCC(ULONG instruction_field)
{
    ULONG cond=helper_instruction_field_cond(instruction_field);
    INT8 eval_bp_CP_cc;

    switch (cond)
    {
    case 0b1000:
        eval_bp_CP_cc=TRUE;
        break;
    case 0b0000:

        eval_bp_CP_cc=FALSE;
        break;
    case 0b0111:
        if (interface_signals_ptr->bp_CP_cc == 3)
        {

            eval_bp_CP_cc=TRUE;
        }
        else
        {
            eval_bp_CP_cc=FALSE;
        }
        break;
    case 0b0110:
        if (interface_signals_ptr->bp_CP_cc == 2)
        {

            eval_bp_CP_cc=TRUE;
        }
        else
        {
            eval_bp_CP_cc=FALSE;
        }
        break;
    case 0b0101:
        if (interface_signals_ptr->bp_CP_cc == 2 || interface_signals_ptr->bp_CP_cc == 3)
        {

            eval_bp_CP_cc=TRUE;
        }
        else
        {
            eval_bp_CP_cc=FALSE;
        }
        break;
    case 0b0100:
        if (interface_signals_ptr->bp_CP_cc == 1)
        {

            eval_bp_CP_cc=TRUE;
        }
        else
        {
            eval_bp_CP_cc=FALSE;
        }

        break;
    case 0b0011:

        if (interface_signals_ptr->bp_CP_cc == 1 || interface_signals_ptr->bp_CP_cc == 3)
        {
            eval_bp_CP_cc=TRUE;
        }
        else
        {
            eval_bp_CP_cc=FALSE;
        }

        break;
    case 0b0010:
        if (interface_signals_ptr->bp_CP_cc == 1 || interface_signals_ptr->bp_CP_cc == 2)
        {

            eval_bp_CP_cc=TRUE;
        }
        else
        {
            eval_bp_CP_cc=FALSE;
        }

        break;
    case 0b0001:
        if (interface_signals_ptr->bp_CP_cc== 1 || interface_signals_ptr->bp_CP_cc == 2 || interface_signals_ptr->bp_CP_cc == 3)
        {

            eval_bp_CP_cc=TRUE;
        }
        else
        {
            eval_bp_CP_cc=FALSE;
        }

        break;
    case 0b1001:
        if (interface_signals_ptr->bp_CP_cc == 0)
        {

            eval_bp_CP_cc=TRUE;
        }
        else
        {
            eval_bp_CP_cc=FALSE;
        }

        break;
    case 0b1010:
        if (interface_signals_ptr->bp_CP_cc == 0 || interface_signals_ptr->bp_CP_cc == 3)
        {

            eval_bp_CP_cc=TRUE;
        }
        else
        {

            eval_bp_CP_cc=FALSE;
        }

        break;
    case 0b1011:
        if (interface_signals_ptr->bp_CP_cc == 0 || interface_signals_ptr->bp_CP_cc == 2)
        {

            eval_bp_CP_cc=TRUE;
        }
        else
        {
            eval_bp_CP_cc=FALSE;
        }

        break;
    case 0b1100:
        if (interface_signals_ptr->bp_CP_cc == 0 || interface_signals_ptr->bp_CP_cc == 2 || interface_signals_ptr->bp_CP_cc == 3)
        {

            eval_bp_CP_cc=TRUE;
        }
        else
        {
            eval_bp_CP_cc=FALSE;
        }

        break;
    case 0b1101:
        if (interface_signals_ptr->bp_CP_cc == 0 || interface_signals_ptr->bp_CP_cc == 1)
        {

            eval_bp_CP_cc=TRUE;
        }
        else
        {
            eval_bp_CP_cc=FALSE;
        }
        break;
    case 0b1110:
        if (interface_signals_ptr->bp_CP_cc == 0 || interface_signals_ptr->bp_CP_cc == 1 || interface_signals_ptr->bp_CP_cc == 3)
        {

            eval_bp_CP_cc=TRUE;
        }
        else
        {
            eval_bp_CP_cc=FALSE;
        }
        break;
    case 0b1111:
        if (interface_signals_ptr->bp_CP_cc == 0 || interface_signals_ptr->bp_CP_cc == 1 || interface_signals_ptr->bp_CP_cc == 2)
        {

            eval_bp_CP_cc=TRUE;
        }
        else
        {
            eval_bp_CP_cc=FALSE;
        }
        break;
    }
    sparc_intunit_ptr->PC=sparc_intunit_ptr->nPC;
    /* TEST IF THE BRANCH IS TAKEN OR NOT */
    if (eval_bp_CP_cc == TRUE)
    {
        sparc_intunit_ptr->nPC = ((helper_instruction_field_disp22(instruction_field) | 0xFFC00000) << 2) + ((ULONG)sparc_intunit_ptr->PC+sparcv8_mmu_memory_program_return_ptr()) ;
        if (cond == 0b1000 && helper_instruction_field_a(instruction_field) == TRUE)
        {
            /* ANNUL */
        }
    }
    else
    {
        sparc_intunit_ptr->nPC+=1;
        if (helper_instruction_field_a(instruction_field) == TRUE)
        {
            /* ANNUL */
        }
    }
}

/* CALL AND LINK INSTRUCTION */

void sparcv8_inst_set_CALL(ULONG instruction_field)
{
    sparc_intunit_ptr->nPC = ((helper_instruction_field_disp22(instruction_field) | 0xFFC00000) << 2) + ((ULONG)sparc_intunit_ptr->PC+sparcv8_mmu_memory_program_return_ptr()) ;/* UNCONDITIONAL , BRANCH ALWAYS */
    sparc_intunit_ptr->nPC= sparc_intunit_ptr->nPC  + 1 ;
    *sparc_proc_integer_unit_windowregs_ptr[(24*(sparcv8_inst_set_extra_RDPSR(CWP))+7)] = (ULONG)sparc_intunit_ptr->PC; /* ADDRESS OF CALL INSTRUCTION TO %O7 */

    return;
}

ULONG* sparcv8_inst_set_extra_CALL_PC()
{
    sparc_intunit_ptr->PC= sparc_intunit_ptr->nPC;
    sparc_intunit_ptr->nPC++;
    return sparc_intunit_ptr->PC;
}

/* JUMP AND LINK INSTRUCTION */

void sparcv8_inst_set_JMPL(ULONG instruction_field)
{
    /*  TRAP CATALOGUE FOR JMPL INSTRUCTION
     *  mem_address_not_aligned -- DONE
     */

    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    ULONG RD=helper_instruction_field_rd(instruction_field);

    if(RD == FALSE)
    {
        printf(" RETURN FROM A SUBROUTINE\n ");
        return;
    }
    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if ( ((RS1+RS2) & 0x03) !=0 )
        {
            /* MEMORY ADDRESS NOT ALLIGNED TRAP */

            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        if(RD<8)
        {
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)(RS1+RS2);
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1+RS2;

        }
        else
        {
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)(RS1+RS2);
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1+RS2;
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);

        if (((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))  & 0x03 )!=0 )
        {
            /* MEMORY ADDRESS NOT ALLIGNED TRAP */

            printf(" MEMORY ADDRESS NOT ALLIGNED TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->mem_address_not_aligned);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        if(RD<8)
        {
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)(RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));
        }
        else
        {
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)(RS1 + ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));
        }
    }
}

/* TRAP (TICC) */

void sparcv8_inst_set_TICC(ULONG instruction_field)
{
    ULONG cond=helper_instruction_field_cond(instruction_field);
    INT8 trap_eval_icc;

    switch (cond)
    {
    case 0b1000:
        trap_eval_icc=TRUE;
        break;
    case 0b0000:
        trap_eval_icc=FALSE;
        break;
    case 0b1001:
        if(sparcv8_inst_set_extra_RDPSR(ICC_ZERO) == 0)
        {
            trap_eval_icc=TRUE;
        }
        else
        {
            trap_eval_icc=FALSE;
        }
        break;
    case 0b0001:
        if( sparcv8_inst_set_extra_RDPSR(ICC_ZERO) == 1)
        {
            trap_eval_icc=TRUE;
        }
        else
        {
            trap_eval_icc=FALSE;
        }
        break;
    case 0b1010:
        if((sparcv8_inst_set_extra_RDPSR(ICC_ZERO)  | (  sparcv8_inst_set_extra_RDPSR(ICC_NEGATIVE) ^ sparcv8_inst_set_extra_RDPSR(ICC_OVERFLOW)) ) == 0)
        {
            trap_eval_icc=TRUE;
        }
        else
        {
            trap_eval_icc=FALSE;
        }
        break;
    case 0b0010:
        if(    (sparcv8_inst_set_extra_RDPSR(ICC_ZERO) | (  sparcv8_inst_set_extra_RDPSR(ICC_NEGATIVE) ^ sparcv8_inst_set_extra_RDPSR(ICC_OVERFLOW)) ) == 1)
        {
            trap_eval_icc=TRUE;
        }
        else
        {
            trap_eval_icc=FALSE;
        }
        break;

    case 0b1011:
        if    ((sparcv8_inst_set_extra_RDPSR(ICC_NEGATIVE) ^ sparcv8_inst_set_extra_RDPSR(ICC_OVERFLOW) ) == 0)
        {
            trap_eval_icc=TRUE;
        }
        else
        {
            trap_eval_icc=FALSE;
        }
        break;

    case 0b0011:
        if((sparcv8_inst_set_extra_RDPSR(ICC_NEGATIVE) ^ sparcv8_inst_set_extra_RDPSR(ICC_OVERFLOW) ) == 1)
        {
            trap_eval_icc=TRUE;
        }
        else
        {
            trap_eval_icc=FALSE;
        }
        break;
    case 0b1100:
        if ((sparcv8_inst_set_extra_RDPSR(ICC_CARRY) ==0)  && (sparcv8_inst_set_extra_RDPSR(ICC_ZERO)==0))
        {
            trap_eval_icc=TRUE;
        }
        else
        {
            trap_eval_icc=FALSE;
        }
        break;
    case 0b0100:
        if((sparcv8_inst_set_extra_RDPSR(ICC_CARRY) ==1)  && (sparcv8_inst_set_extra_RDPSR(ICC_ZERO)==1))
        {
            trap_eval_icc=TRUE;
        }
        else
        {
            trap_eval_icc=FALSE;
        }
        break;
    case 0b1101:
        if(sparcv8_inst_set_extra_RDPSR(ICC_CARRY)==0)
        {
            trap_eval_icc=TRUE;
        }
        else
        {
            trap_eval_icc=FALSE;
        }
        break;
    case 0b0101:
        if(sparcv8_inst_set_extra_RDPSR(ICC_CARRY)==1)
        {
            trap_eval_icc=TRUE;
        }
        else
        {
            trap_eval_icc=FALSE;
        }
        break;
    case 0b1110:
        if(sparcv8_inst_set_extra_RDPSR(ICC_NEGATIVE)==0)
        {
            trap_eval_icc=TRUE;
        }
        else
        {
            trap_eval_icc=FALSE;
        }
        break;
    case 0b0110:
        if(sparcv8_inst_set_extra_RDPSR(ICC_NEGATIVE)==1)
        {
            trap_eval_icc=TRUE;
        }
        else
        {
            trap_eval_icc=FALSE;
        }
        break;


    case 0b1111:
        if(sparcv8_inst_set_extra_RDPSR(ICC_OVERFLOW)==0)
        {
            trap_eval_icc=TRUE;
        }
        else
        {
            trap_eval_icc=FALSE;
        }

        break;
    case 0b0111:
        if(sparcv8_inst_set_extra_RDPSR(ICC_OVERFLOW)==1)
        {
            trap_eval_icc=TRUE;
        }
        else
        {
            trap_eval_icc=FALSE;
        }

        break;
    }


    if (trap_eval_icc == TRUE)
    {
        /* INSTRUCTION TRAP */

        ULONG RS1=helper_instruction_field_rs1(instruction_field);

        if(RS1<8)
        {
            RS1=(sparc_intunit_ptr->windowregs.GREG[RS1]) & 0x7F;
        }
        else
        {
            RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]) & 0x7F  ;
        }
        if(helper_instruction_field_i(instruction_field)==FALSE)
        {
            ULONG RS2=helper_instruction_field_rs2(instruction_field);
            if(RS2<8)
            {
                RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
            }
            else
            {
                RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
            }

            sparcv8_inst_set_extra_WRTBR(TT,0x80+RS1+RS2);

        }
        else if(helper_instruction_field_i(instruction_field)==TRUE)
        {
            sparcv8_inst_set_extra_WRTBR(TT,0x80+RS1+(helper_instruction_field_imm7(instruction_field)|0xFFFFFF80));
        }

        sparcv8_inst_set_extra_WRPSR(CWP,sparcv8_inst_set_extra_RDPSR(CWP)-1);

        /* DECREMENTS THE CWP AND SAVES PC AND nPC TO LOCAL 1 AND LOCAL 2 REGISTERS */
        *sparc_proc_integer_unit_windowregs_ptr[(24*sparcv8_inst_set_extra_RDPSR(CWP))+9] = (ULONG)sparc_intunit_ptr->PC;
        *sparc_proc_integer_unit_windowregs_ptr[(24*sparcv8_inst_set_extra_RDPSR(CWP))+10] = (ULONG)sparc_intunit_ptr->nPC;
        sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);

        /* AFTER A TAKEN TICC THE PROCESSOR ENTERS SUPERVISOR MODE AND DISABLES TRAPS */
        sparcv8_inst_set_extra_WRPSR(ET,0);
        sparcv8_inst_set_extra_WRPSR(S,1);
    }
    else
    {
        sparc_intunit_ptr->PC=sparc_intunit_ptr->nPC;
        sparc_intunit_ptr->nPC+=1;
    }
    /* FOR THE MOMENT THE FIRST FOUR INSTRUCTIONS OF EACH TRAP WILL NO EXECUTE HERE. THE TBR CONTEXT WILL BE DIRECTLY THE ADDRESS */
}

////////////////////////////////////////////////////////////////// ADDITIONAL INSTRUCTION SET //////////////////////////////////////////////////////////////////////////

/* ADD INSTRUCTION AND MODIFY ICC*/

void sparcv8_inst_set_additional_ADDCC(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }
    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1+RS2;
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1+RS2;
        }
        if (helper_read_value(31,31,RS1+RS2))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if((RS1+RS2) == 0)
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        if((helper_read_value(31,31,RS1) &&   helper_read_value(31,31,RS2) && (~helper_read_value(31,31,RS1+RS2))) || ((~ helper_read_value(31,31,RS1)) && (~ helper_read_value(31,31,RS2)) && helper_read_value(31,31,RS1+RS2)))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,TRUE);
        }
        if (  (helper_read_value(31,31,RS1+RS2) &&  helper_read_value(31,31,RS2)) || ((~helper_read_value(31,31,RS1+RS2)) && (helper_read_value(31,31,RS1) || helper_read_value(31,31,RS2))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_CARRY,TRUE);
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));
        }
        if (helper_read_value(31,31,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) == 0)
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        if((helper_read_value(31,31,RS1) &&   helper_read_value(31,31,((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) && (~helper_read_value(31,31,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))) || ((~ helper_read_value(31,31,RS1)) && (~ helper_read_value(31,31,((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))) && helper_read_value(31,31,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,TRUE);
        }
        if (  (helper_read_value(31,31,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) &&  helper_read_value(31,31,((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))) || ((~helper_read_value(31,31,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))) && (helper_read_value(31,31,RS1) || helper_read_value(31,31,((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_CARRY,TRUE);
        }
    }
}


/* ADD INSTRUCTION WITH CARRY AND MODIFY ICC*/

void sparcv8_inst_set_additional_ADDXCC(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }
    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1+RS2;
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1+RS2+sparcv8_inst_set_extra_RDPSR(ICC_CARRY);
        }
        if (helper_read_value(31,31,RS1+RS2+sparcv8_inst_set_extra_RDPSR(ICC_CARRY)))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if((RS1+RS2) == 0)
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        if((helper_read_value(31,31,RS1) &&   helper_read_value(31,31,RS2) && (~helper_read_value(31,31,RS1+RS2+sparcv8_inst_set_extra_RDPSR(ICC_CARRY)))) || ((~ helper_read_value(31,31,RS1)) && (~ helper_read_value(31,31,RS2)) && helper_read_value(31,31,RS1+RS2+sparcv8_inst_set_extra_RDPSR(ICC_CARRY))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,TRUE);
        }
        if (  (helper_read_value(31,31,RS1+RS2+sparcv8_inst_set_extra_RDPSR(ICC_CARRY)) &&  helper_read_value(31,31,RS2)) || ((~helper_read_value(31,31,RS1+RS2+sparcv8_inst_set_extra_RDPSR(ICC_CARRY))) && (helper_read_value(31,31,RS1) || helper_read_value(31,31,RS2))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_CARRY,TRUE);
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))+sparcv8_inst_set_extra_RDPSR(ICC_CARRY);
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))+sparcv8_inst_set_extra_RDPSR(ICC_CARRY);
        }
        if (helper_read_value(31,31,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) == 0)
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        if((helper_read_value(31,31,RS1) &&   helper_read_value(31,31,((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) && (~helper_read_value(31,31,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))+sparcv8_inst_set_extra_RDPSR(ICC_CARRY)))) || ((~ helper_read_value(31,31,RS1)) && (~ helper_read_value(31,31,((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))) && helper_read_value(31,31,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))+sparcv8_inst_set_extra_RDPSR(ICC_CARRY))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,TRUE);
        }
        if (  (helper_read_value(31,31,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))+sparcv8_inst_set_extra_RDPSR(ICC_CARRY)) &&  helper_read_value(31,31,((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))) || ((~helper_read_value(31,31,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))+sparcv8_inst_set_extra_RDPSR(ICC_CARRY))) && (helper_read_value(31,31,RS1) || helper_read_value(31,31,((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_CARRY,TRUE);
        }
    }
}

/* SUBSTRUCT INSTRUCTION AND MODIFY ICC */

void sparcv8_inst_set_additional_SUBCC(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }


    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1-RS2;
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1-RS2;
        }
        if (helper_read_value(31,31,RS1+RS2))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if((RS1+RS2) == 0)
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        if((helper_read_value(31,31,RS1) &&   (~helper_read_value(31,31,RS2)) && (~helper_read_value(31,31,RS1+RS2))) || ((~ helper_read_value(31,31,RS1)) &&  helper_read_value(31,31,RS2) && helper_read_value(31,31,RS1+RS2)))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,TRUE);
        }
        if (  ((~helper_read_value(31,31,RS1+RS2)) &&  helper_read_value(31,31,RS2)) || (helper_read_value(31,31,RS1+RS2) && ((~helper_read_value(31,31,RS1)) || helper_read_value(31,31,RS2))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_CARRY,TRUE);
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1-((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1-((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));
        }
        if (helper_read_value(31,31,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) == 0)
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        if((helper_read_value(31,31,RS1) &&   (~helper_read_value(31,31,((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))) && (~helper_read_value(31,31,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))) || ((~ helper_read_value(31,31,RS1)) &&  helper_read_value(31,31,((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) && helper_read_value(31,31,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,TRUE);
        }
        if (  ((~helper_read_value(31,31,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))) &&  helper_read_value(31,31,((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))) || (helper_read_value(31,31,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) && ((~helper_read_value(31,31,RS1)) || helper_read_value(31,31,((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_CARRY,TRUE);
        }
    }
}

/* SUBSTRUCT INSTRUCTION WITH CARRY AND MODIFY ICC */

void sparcv8_inst_set_additional_SUBXCC(ULONG instruction_field) /* SUBSTRUCT eXtended */
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }

    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1-RS2-sparcv8_inst_set_extra_RDPSR(ICC_CARRY);
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1-RS2-sparcv8_inst_set_extra_RDPSR(ICC_CARRY);
        }
        if (helper_read_value(31,31,RS1-RS2-sparcv8_inst_set_extra_RDPSR(ICC_CARRY)))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if((RS1-RS2-sparcv8_inst_set_extra_RDPSR(ICC_CARRY)) == 0)
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        if((helper_read_value(31,31,RS1) &&   (~helper_read_value(31,31,RS2)) && (~helper_read_value(31,31,RS1-RS2-sparcv8_inst_set_extra_RDPSR(ICC_CARRY)))) || ((~ helper_read_value(31,31,RS1)) &&  helper_read_value(31,31,RS2) && helper_read_value(31,31,RS1-RS2-sparcv8_inst_set_extra_RDPSR(ICC_CARRY))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,TRUE);
        }
        if (  ((~helper_read_value(31,31,RS1-RS2-sparcv8_inst_set_extra_RDPSR(ICC_CARRY))) &&  helper_read_value(31,31,RS2)) || (helper_read_value(31,31,RS1-RS2-sparcv8_inst_set_extra_RDPSR(ICC_CARRY)) && ((~helper_read_value(31,31,RS1)) || helper_read_value(31,31,RS2))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_CARRY,TRUE);
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1-((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))-sparcv8_inst_set_extra_RDPSR(ICC_CARRY);
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1-((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))-sparcv8_inst_set_extra_RDPSR(ICC_CARRY);
        }
        if (helper_read_value(31,31,RS1-((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))-sparcv8_inst_set_extra_RDPSR(ICC_CARRY)))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if((RS1-((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))-sparcv8_inst_set_extra_RDPSR(ICC_CARRY)) == 0)
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        if((helper_read_value(31,31,RS1) &&   (~helper_read_value(31,31,((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))) && (~helper_read_value(31,31,RS1-((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))-sparcv8_inst_set_extra_RDPSR(ICC_CARRY)))) || ((~ helper_read_value(31,31,RS1)) &&  helper_read_value(31,31,((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) && helper_read_value(31,31,RS1-((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))-sparcv8_inst_set_extra_RDPSR(ICC_CARRY))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,TRUE);
        }
        if (  ((~helper_read_value(31,31,RS1-((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))-sparcv8_inst_set_extra_RDPSR(ICC_CARRY))) &&  helper_read_value(31,31,((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))) || (helper_read_value(31,31,RS1-((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))-sparcv8_inst_set_extra_RDPSR(ICC_CARRY)) && ((~helper_read_value(31,31,RS1)) || helper_read_value(31,31,((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_CARRY,TRUE);
        }
    }
}


/* LOGICAL INSTRUCTION AND AND MODIFY ICC */

void sparcv8_inst_set_additional_ANDCC(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }

    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1 & RS2;
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1 & RS2;
        }
        if (helper_read_value(31,31,RS1&RS2))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if ( RS1 && RS2 == FALSE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
        sparcv8_inst_set_extra_WRPSR(ICC_CARRY,FALSE);
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1 & ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1 & ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));
        }
        if (helper_read_value(31,31,RS1&((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if ( RS1 && ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)) == FALSE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
        sparcv8_inst_set_extra_WRPSR(ICC_CARRY,FALSE);
    }
}

/* LOGICAL INSTRUCTION NAND AND MODIFY ICC */

void sparcv8_inst_set_additional_NANDCC(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }

    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=~(RS1 & RS2);
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=~(RS1 & RS2);
        }
        if (helper_read_value(31,31,~(RS1 & RS2)))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if ( ~(RS1 & RS2) == FALSE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
        sparcv8_inst_set_extra_WRPSR(ICC_CARRY,FALSE);
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=~(RS1 & ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=~(RS1 & ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
        }
        if (helper_read_value(31,31,~(RS1 & ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if ( ~(RS1 & ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) == FALSE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
        sparcv8_inst_set_extra_WRPSR(ICC_CARRY,FALSE);
    }
}

/* LOGICAL INSTRUCTION OR AND MODIFY ICC */

void sparcv8_inst_set_additional_ORCC(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }

    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1 | RS2;
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1 | RS2;
        }
        if (helper_read_value(31,31,RS1|RS2))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if ( RS1||RS2 == FALSE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
        sparcv8_inst_set_extra_WRPSR(ICC_CARRY,FALSE);
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1 | ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1 | ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));
        }
        if (helper_read_value(31,31,RS1|((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if ( RS1||((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)) == FALSE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
        sparcv8_inst_set_extra_WRPSR(ICC_CARRY,FALSE);
    }

}


/* LOGICAL INSTRUCTION NOR AND MODIFY ICC */

void sparcv8_inst_set_additional_NORCC(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }

    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=~(RS1 | RS2);
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=~(RS1 | RS2);
        }
        if (helper_read_value(31,31,~(RS1 | RS2)))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if ( ~(RS1 || RS2) == FALSE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
        sparcv8_inst_set_extra_WRPSR(ICC_CARRY,FALSE);
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=~(RS1 | ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=~(RS1 | ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
        }
        if (helper_read_value(31,31,~(RS1 | ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if ( ~(RS1 || ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) == FALSE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
        sparcv8_inst_set_extra_WRPSR(ICC_CARRY,FALSE);
    }
}


/* LOGICAL INSTRUCTION XOR AND MODIFY ICC */

void sparcv8_inst_set_additional_XORCC(ULONG instruction_field)
{

    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }

    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1 ^ RS2;
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1 ^ RS2;
        }
        if (helper_read_value(31,31,RS1 ^ RS2))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if ( (RS1 != RS2) == FALSE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
        sparcv8_inst_set_extra_WRPSR(ICC_CARRY,FALSE);
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS1 ^ ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS1 ^ ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));
        }
        if (helper_read_value(31,31,RS1^((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if ( (RS1!=((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) == FALSE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
        sparcv8_inst_set_extra_WRPSR(ICC_CARRY,FALSE);
    }


}



/* LOGICAL INSTRUCTION XNOR AND MODIFY ICC */

void sparcv8_inst_set_additional_XNORCC(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);

    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }

    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=~(RS1 ^ RS2);
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=~(RS1 ^ RS2);
        }
        if (helper_read_value(31,31,~(RS1 ^ RS2)))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if ( ~(RS1 ^ RS2) == FALSE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
        sparcv8_inst_set_extra_WRPSR(ICC_CARRY,FALSE);
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=~(RS1 ^ ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=~(RS1 ^ ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
        }
        if (helper_read_value(31,31,~(RS1 ^ ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if ( ~(RS1 ^ ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) == FALSE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
        sparcv8_inst_set_extra_WRPSR(ICC_CARRY,FALSE);
    }
}

/*  MULTIPLY STEP INSTRUCTION AND MODIFY ICC */

void sparcv8_inst_set_additional_MULSCC(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    ULONG RD=helper_instruction_field_rd(instruction_field);
    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }
    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1]>>1;
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))])>>1;
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if ( sparcv8_inst_set_extra_RDY(0,YBIT) == TRUE )
        {
            RS2=RS1+RS2;
            if (helper_read_value(31,31,RS1+RS2))
            {
                sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
            }
            if((RS1+RS2) == 0)
            {
                sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
            }
            if((helper_read_value(31,31,RS1) &&   helper_read_value(31,31,RS2) && (~helper_read_value(31,31,RS1+RS2))) || ((~ helper_read_value(31,31,RS1)) && (~ helper_read_value(31,31,RS2)) && helper_read_value(31,31,RS1+RS2)))
            {
                sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,TRUE);
            }
            if (  (helper_read_value(31,31,RS1+RS2) &&  helper_read_value(31,31,RS2)) || ((~helper_read_value(31,31,RS1+RS2)) && (helper_read_value(31,31,RS1) || helper_read_value(31,31,RS2))))
            {
                sparcv8_inst_set_extra_WRPSR(ICC_CARRY,TRUE);
            }
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=RS2;
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=RS2;
        }
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if ( sparcv8_inst_set_extra_RDY(0,YBIT) == TRUE )
        {
            simm13=RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0));

            if (helper_read_value(31,31,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))
            {
                sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
            }
            if((RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) == 0)
            {
                sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
            }
            if((helper_read_value(31,31,RS1) &&   helper_read_value(31,31,((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) && (~helper_read_value(31,31,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))) || ((~ helper_read_value(31,31,RS1)) && (~ helper_read_value(31,31,((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))) && helper_read_value(31,31,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))))
            {
                sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,TRUE);
            }
            if (  (helper_read_value(31,31,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) &&  helper_read_value(31,31,((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))) || ((~helper_read_value(31,31,RS1+((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))) && (helper_read_value(31,31,RS1) || helper_read_value(31,31,((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))))
            {
                sparcv8_inst_set_extra_WRPSR(ICC_CARRY,TRUE);
            }
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=simm13;
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=simm13;
        }
    }
    sparc_intunit_ptr->Y=sparc_intunit_ptr->Y>>1;
    sparcv8_inst_set_extra_WRY(31,YALL,helper_read_value(0,0,RS1));
}


/* UNSIGNED MULTIPLY INSTRUCTION AND MODIFY ICC */

void sparcv8_inst_set_additional_UMULCC(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    ULONG RD=helper_instruction_field_rd(instruction_field);

    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }
    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=helper_unsigned_ll_lsw((DOUBLE64)(RS1*RS2)); /* LSW */
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=helper_unsigned_ll_lsw((DOUBLE64)(RS1*RS2)); /* LSW */
        }
        sparcv8_inst_set_extra_WRY(0,YALL,helper_unsigned_ll_msw((DOUBLE64)(RS1*RS2))); /* MSW */

        if (helper_read_value(31,31,(DOUBLE64)(RS1*RS2)))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if ( (DOUBLE64)(RS1*RS2) == FALSE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
        sparcv8_inst_set_extra_WRPSR(ICC_CARRY,FALSE);
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=helper_unsigned_ll_lsw((DOUBLE64)(RS1*((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))); /* LSW */
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=helper_unsigned_ll_lsw((DOUBLE64)(RS1*((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))); /* LSW */
        }
        sparcv8_inst_set_extra_WRY(0,YALL,helper_unsigned_ll_msw((DOUBLE64)(RS1*((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))); /* MSW */

        if (helper_read_value(31,31,(DOUBLE64)(RS1*((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if ( (DOUBLE64)(RS1*((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) == FALSE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
        sparcv8_inst_set_extra_WRPSR(ICC_CARRY,FALSE);
    }
}

/* SIGNED MULTIPLY INSTRUCTION AND MODIFY ICC*/

void sparcv8_inst_set_additional_SMULCC(ULONG instruction_field)
{
    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    ULONG RD=helper_instruction_field_rd(instruction_field);

    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }
    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if(RD<8) /* USE OF RD VALUE NEEDS (INT32) CASTING */
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=helper_unsigned_ll_lsw((DOUBLE64)((INT32)RS1*(INT32)RS2)); /* LSW */
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=helper_unsigned_ll_lsw((DOUBLE64)((INT32)RS1*(INT32)RS2)); /* LSW */
        }
        sparcv8_inst_set_extra_WRY(0,YALL,helper_unsigned_ll_msw((DOUBLE64)(RS1*RS2))); /* MSW */
        if (helper_read_value(31,31,(DOUBLE64)((INT32)RS1*(INT32)RS2)))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if ( (DOUBLE64)((INT32)RS1*(INT32)RS2) == FALSE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
        sparcv8_inst_set_extra_WRPSR(ICC_CARRY,FALSE);
    }
    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);
        if(RD<8)
        {
            sparc_intunit_ptr->windowregs.GREG[RD]=helper_unsigned_ll_lsw((DOUBLE64)((INT32)RS1*(INT32)((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))); /* LSW */
        }
        else
        {
            *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=helper_unsigned_ll_lsw((DOUBLE64)((INT32)RS1*(INT32)((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))); /* LSW */
        }
        sparcv8_inst_set_extra_WRY(0,YALL,helper_unsigned_ll_msw((DOUBLE64)((INT32)RS1*(INT32)((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))))); /* MSW */
        if (helper_read_value(31,31,(DOUBLE64)((INT32)RS1*(INT32)((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))))
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if ( ((DOUBLE64)((INT32)RS1*(INT32)((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))) == FALSE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
        sparcv8_inst_set_extra_WRPSR(ICC_CARRY,FALSE);
    }
}


/* UNSIGNED DIVIDE INSTRUCTION AND MODIFY ICC*/

void sparcv8_inst_set_additional_UDIVCC(ULONG instruction_field)
{
    /*  TRAP CATALOGUE FOR UDIVCC INSTRUCTION
     *  division_by_zero
     */

    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    ULONG Y=sparcv8_inst_set_extra_RDY(0,YALL);
    ULONG RD=helper_instruction_field_rd(instruction_field);

    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }
    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if (RS2 == 0)
        {
            printf(" DIVISION BY ZERO TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->division_by_zero);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }

        if(RD<8)
        {
            if ( (((DOUBLE64)(RS1*Y))/RS2) > 0xffffffff )
            {
                sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
                sparc_intunit_ptr->windowregs.GREG[RD]=0xffffffff;
            }
            else
            {
                sparc_intunit_ptr->windowregs.GREG[RD]=(((DOUBLE64)(RS1*Y))/RS2);
            }
        }
        else
        {
            if ( (((DOUBLE64)(RS1*Y))/RS2) > 0xffffffff )
            {
                sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
                *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=0xffffffff;
            }
            else
            {
                *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=(((DOUBLE64)(RS1*Y))/RS2);
            }
        }
        if (helper_read_value(31,31,(((DOUBLE64)(RS1*Y))/RS2)) == TRUE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if (( ((DOUBLE64)(RS1*Y))/RS2) == FALSE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        sparcv8_inst_set_extra_WRPSR(ICC_CARRY,FALSE);
    }

    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);

        if (((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)) == 0)
        {
            printf(" DIVISION BY ZERO TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->division_by_zero);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        if(RD<8)
        {
            if ( (((DOUBLE64)(RS1*Y))/((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) > 0xffffffff )
            {
                sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
                sparc_intunit_ptr->windowregs.GREG[RD]=0xffffffff ;
            }
            else
            {
                sparc_intunit_ptr->windowregs.GREG[RD]=(((DOUBLE64)(RS1*Y))/((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
            }
        }
        else
        {
            if ( (((DOUBLE64)(RS1*Y))/((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) > 0xffffffff )
            {
                sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
                *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=0xffffffff;
            }
            else
            {
                *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=(((DOUBLE64)(RS1*Y))/((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
            }
        }
        if (helper_read_value(31,31,(((DOUBLE64)(RS1*Y))/((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))) == TRUE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if ( (DOUBLE64)((INT32)RS1*(INT32)((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) == FALSE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        sparcv8_inst_set_extra_WRPSR(ICC_CARRY,FALSE);
    }
}

/* SIGNED DIVIDE INSTRUCTION AND MODIFY ICC */

void sparcv8_inst_set_additional_SDIVCC(ULONG instruction_field)
{
    /*  TRAP CATALOGUE FOR SDIVCC INSTRUCTION
     *  division_by_zero
     */

    ULONG RS1=helper_instruction_field_rs1(instruction_field);
    ULONG Y=sparcv8_inst_set_extra_RDY(0,YALL);
    ULONG RD=helper_instruction_field_rd(instruction_field);

    if(RD == FALSE)
    {
        printf("WRITING IN GENERAL REGISTER[0] IS NOT ALLOWED\n");
        return;
    }
    if(RS1<8)
    {
        RS1=sparc_intunit_ptr->windowregs.GREG[RS1];
    }
    else
    {
        RS1=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS1-8))]);
    }
    if(helper_instruction_field_i(instruction_field)==FALSE)
    {
        ULONG RS2=helper_instruction_field_rs2(instruction_field);
        if(RS2<8)
        {
            RS2=sparc_intunit_ptr->windowregs.GREG[RS2];
        }
        else
        {
            RS2=*(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RS2-8))]);
        }
        if (RS2 == 0)
        {
            printf(" DIVISION BY ZERO TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->division_by_zero);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }

        if(RD<8)
        {
            if (((DOUBLE64)((INT32)RS1*(INT32)Y)/RS2) > 0x7fffffff)
            {
                sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
                sparc_intunit_ptr->windowregs.GREG[RD]=0x7fffffff;
            }
            else if (((DOUBLE64)((INT32)RS1*(INT32)Y)/RS2) < 0x80000000)
            {
                sparc_intunit_ptr->windowregs.GREG[RD]=0x80000000;
            }
            else
            {
                sparc_intunit_ptr->windowregs.GREG[RD]=(((DOUBLE64)((INT32)RS1*(INT32)Y))/RS2);
            }
        }
        else
        {
            if ((((DOUBLE64)((INT32)RS1*(INT32)Y))/RS2) > 0x7fffffff)
            {
                sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
                *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=0x7fffffff;
            }
            else if (((DOUBLE64)((INT32)RS1*(INT32)Y)/RS2)< 0x80000000)
            {
                *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=0x80000000;
            }

            else
            {
                *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=(((DOUBLE64)((INT32)RS1*(INT32)Y))/RS2);
            }
        }
        if (helper_read_value(31,31,(((DOUBLE64)((INT32)RS1*(INT32)Y))/RS2)) == TRUE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if ((((DOUBLE64)((INT32)RS1*(INT32)Y))/RS2) == FALSE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        sparcv8_inst_set_extra_WRPSR(ICC_CARRY,FALSE);
    }

    else if(helper_instruction_field_i(instruction_field)==TRUE)
    {
        ULONG simm13=helper_instruction_field_simm13(instruction_field);

        if (((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)) == 0)
        {
            printf(" DIVISION BY ZERO TRAP \n");
            sparcv8_inst_set_extra_WRTBR(TT,trap_handler_ptr->division_by_zero);
            sparc_intunit_ptr->PC=sparcv8_mmu_memory_program_return_ptr()+(ULONG)sparcv8_inst_set_extra_RDTBR(TBRALL);
            sparc_intunit_ptr->nPC=sparc_intunit_ptr->PC + 1;
        }
        if(RD<8)
        {
            if (((DOUBLE64)((INT32)RS1*(INT32)Y) / ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) > 0x7fffffff)
            {
                sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
                sparc_intunit_ptr->windowregs.GREG[RD]=0x7fffffff ;
            }
            else if (((DOUBLE64)((INT32)RS1*(INT32)Y) / ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) < 0x80000000)
            {
                sparc_intunit_ptr->windowregs.GREG[RD]=0x80000000;
            }
            else
            {
                sparc_intunit_ptr->windowregs.GREG[RD]=(((DOUBLE64)((INT32)RS1*(INT32)Y))/((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
            }
        }
        else
        {
            if (((DOUBLE64)((INT32)RS1*(INT32)Y) / ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) > 0x7fffffff)
            {
                sparcv8_inst_set_extra_WRPSR(ICC_OVERFLOW,FALSE);
                *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=0x7fffffff;
            }
            else if (((DOUBLE64)((INT32)RS1*(INT32)Y) / ((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))  < 0x80000000)
            {
                *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=0x80000000;
            }
            else
            {
                *(sparc_proc_integer_unit_windowregs_ptr[((24*sparcv8_inst_set_extra_RDPSR(CWP))+(RD-8))])=(((DOUBLE64)((INT32)RS1*(INT32)Y))/((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)));
            }
        }
        if (helper_read_value(31,31,(((DOUBLE64)((INT32)RS1*(INT32)Y))/((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0)))) == TRUE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_NEGATIVE,TRUE);
        }
        if ( (((DOUBLE64)((INT32)RS1*(INT32)Y))/((simm13 & 0x1FFF)|((simm13 & 0x1000) ? 0xFCFFF000:0))) == FALSE )
        {
            sparcv8_inst_set_extra_WRPSR(ICC_ZERO,TRUE);
        }
        sparcv8_inst_set_extra_WRPSR(ICC_CARRY,FALSE);
    }
}

///////////////////////////////////////////////////////////////////////  FLOATING POINT OPERATE INSTRUCTIONS ////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////  COPROCESSOR OPERATE INSTRUCTIONS ////////////////////////////////////////////////////////////////////

