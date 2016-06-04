/*
  ------------------------------------------------------------------------------------------------------------------------------------------
  Project       : Sparc_V8 Emulator
  File          : SPARCV8_EMULATOR_CORE.c
  Description   : Main core implementation for SPARCV8 instriction set execution
  Author        : Monahopoulos Konstantinos
  ------------------------------------------------------------------------------------------------------------------------------------------
*/
/*
  ----------------------------------------------------------------------------------------------------------------------------------------
  Includes
  ----------------------------------------------------------------------------------------------------------------------------------------
*/

#include "SPARCV8_EMULATOR_CORE.h"
#include "SPARCV8_INSTRUCTION_SET.h"
#include "THREADS.h"


void sparcv8_emulator_core_initialize(struct SPARCV8_EMULATOR_CORE_CONTEXT *sparc_emulator_core_tmp_ptr ) /* SPARC_V8 EMULATOR CORE MAIN LOOP INITIALIZER*/
{
    sparc_emulator_core_tmp_ptr->instruction=sparcv8_inst_set_extra_CALL_PC();
    sparc_emulator_core_tmp_ptr->filesize =_msize(sparc_emulator_core_tmp_ptr->instruction)/sizeof(UINT32);
    sparc_emulator_core_tmp_ptr->instruction_counter=0;
    sparc_emulator_core_tmp_ptr->CounterStart=0;
    sparc_emulator_core_tmp_ptr->final_time_of_execution=0.0;
    sparc_emulator_core_tmp_ptr->PCFreq=0.0;
    sparc_emulator_core_ptr = sparc_emulator_core_tmp_ptr;

    return;
}

DWORD WINAPI sparcv8_emulator_core_main_loop(LPVOID thread_info_ptr) /* SPARC_V8 EMULATOR CORE MAIN LOOP EXECUTION*/
{
    if(!QueryPerformanceFrequency(&sparc_emulator_core_ptr->li))
    printf("QueryPerformanceFrequency failed!\n");

    sparc_emulator_core_ptr->PCFreq = (double)(sparc_emulator_core_ptr->li.QuadPart)/1000000.0; /*FOR CALCULATION IN MICROSECONDS*/
    QueryPerformanceCounter(&sparc_emulator_core_ptr->li); /*START THE COUNTER*/
    sparc_emulator_core_ptr->CounterStart = sparc_emulator_core_ptr->li.QuadPart; /*SAVE COUNTER'S CURRENT TIME*/

    while( ( sparc_emulator_core_ptr->instruction_counter != sparc_emulator_core_ptr->filesize )  )
        /* IF 0 ->>> FOR TESTING, IF 1 ->>> FOR EXECUTING */
    {
#if 1
        /* IF – INSTRUCTION FETCH FIND OP FIELD*/

        sparc_emulator_core_ptr->op = helper_instruction_field_op(*sparc_emulator_core_ptr->instruction);

        switch (sparc_emulator_core_ptr->op)
        {
            /* ID – INSTRUCTION DECODE */
        case 0:
            sparc_emulator_core_ptr->op2 = helper_instruction_field_op2(*sparc_emulator_core_ptr->instruction);
            switch (sparc_emulator_core_ptr->op2)
            {
            case 0:
                ( *  instruction_ptr->instruction_ptr_op0[0][0] ) ((void*)*sparc_emulator_core_ptr->instruction);     /* EX – EXECUTE */
                break;
            case 2:
                ( *  instruction_ptr->instruction_ptr_op0[0][1] ) ((void*)*sparc_emulator_core_ptr->instruction);   /* EX – EXECUTE */
                break;
            case 4:
                ( *  instruction_ptr->instruction_ptr_op0[0][2] ) ((void*)*sparc_emulator_core_ptr->instruction);  /* EX – EXECUTE */
                break;
            case 6:
                ( *  instruction_ptr->instruction_ptr_op0[0][3] ) ((void*)*sparc_emulator_core_ptr->instruction);   /* EX – EXECUTE */
                break;
            case 7:
                ( *  instruction_ptr->instruction_ptr_op0[0][4] ) ((void*)*sparc_emulator_core_ptr->instruction);   /* EX – EXECUTE */

                break;
            }
            break;
            /* ID – INSTRUCTION DECODE */
        case 1:
            ( *  instruction_ptr->instruction_ptr_op1 ) ((void*)*sparc_emulator_core_ptr->instruction);   /* EX – EXECUTE */
            break;
            /* ID – INSTRUCTION DECODE */
        case 2:
            sparc_emulator_core_ptr->op3=helper_instruction_field_op3 (*sparc_emulator_core_ptr->instruction);
            switch (sparc_emulator_core_ptr->op3)
            {
            case 34:
                sparc_emulator_core_ptr->opf=helper_instruction_field_opf (*sparc_emulator_core_ptr->instruction);

                printf("\n TABLE F-5 HAS NOT INSTRUCTIONS YET, LATER CALL: TABLE F-5[%lu][0] INSTRUCTION \n",sparc_emulator_core_ptr->opf);   /* EX – EXECUTE */
                break;
            case 35:
                sparc_emulator_core_ptr->opf=helper_instruction_field_opf (*sparc_emulator_core_ptr->instruction);

                printf("\n TABLE F-5 HAS NOT INSTRUCTIONS YET, LATER CALL: TABLE F-6[%lu][0] INSTRUCTION \n",sparc_emulator_core_ptr->opf);   /* EX – EXECUTE */
                break;
            case 0x3A:
                ( *  instruction_ptr->instruction_ptr_op2[10][3] ) ((void*)*sparc_emulator_core_ptr->instruction);   /* EX – EXECUTE */
                break;
            default:
                sparc_emulator_core_ptr->op3_bit_0_to_3 =helper_read_value(19,22,*sparc_emulator_core_ptr->instruction);
                sparc_emulator_core_ptr->op3_bit_4_to_5=helper_read_value(23,24,*sparc_emulator_core_ptr->instruction);
                ( *instruction_ptr->instruction_ptr_op2[sparc_emulator_core_ptr->op3_bit_0_to_3][sparc_emulator_core_ptr->op3_bit_4_to_5] ) ((void*)*sparc_emulator_core_ptr->instruction);   /* EX – EXECUTE */
                break;
            }
            break;
            /* ID – INSTRUCTION DECODE */
        case 3:
            /* MA – MEMORY ACCESS OR WB – WRITE BACK */

            sparc_emulator_core_ptr->op3_bit_0_to_3 =helper_read_value(19,22,*sparc_emulator_core_ptr->instruction);
            sparc_emulator_core_ptr->op3_bit_4_to_5=helper_read_value(23,24,*sparc_emulator_core_ptr->instruction);
            ( *instruction_ptr->instruction_ptr_op3[sparc_emulator_core_ptr->op3_bit_0_to_3][sparc_emulator_core_ptr->op3_bit_4_to_5] ) ((void*)*sparc_emulator_core_ptr->instruction);   /* EX – EXECUTE */
            break;
        }

        sparc_emulator_core_ptr->instruction=sparcv8_inst_set_extra_CALL_PC();
        sparc_emulator_core_ptr->instruction_counter++;
#endif
        if ( ((struct THREAD_INFO_context*) thread_info_ptr)->thread_suspend == TRUE)
        {
            SuspendThread(((struct THREAD_INFO_context*) thread_info_ptr)->Thread_Handles[1]);
        }

    }

    QueryPerformanceCounter(&sparc_emulator_core_ptr->li); /*STOP COUNTER*/
    sparc_emulator_core_ptr->final_time_of_execution=(sparc_emulator_core_ptr->li.QuadPart- sparc_emulator_core_ptr->CounterStart)/ sparc_emulator_core_ptr->PCFreq; /*SAVE THE INTERMEDIATE TIME*/
    return 0;
}

