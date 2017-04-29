/*
  ------------------------------------------------------------------------------------------------------------------------------------------
  Project       : Sparc_V8 Emulator
  File          : HELPER.c
  Description   : Helper functions for SPARCV8 EMULATOR process
  Author        : Monachopoulos Konstantinos
  ------------------------------------------------------------------------------------------------------------------------------------------
*/
/*
  ----------------------------------------------------------------------------------------------------------------------------------------
  Includes
  ----------------------------------------------------------------------------------------------------------------------------------------
*/

#include "HELPER.h"

/*CONVERT LITTLEENDIAN TO BIGENDIAN - works in 32bit register*/

ULONG helper_Byteswap(ULONG Littleendian)
{
    ULONG bigendian=( ((Littleendian>>24) & 0x000000ff) /*1 to 4*/ | ((Littleendian>>8) & 0x0000ff00)/*2 to 3*/ | ((Littleendian<<8) & 0x00ff0000)/*3 to 2*/ | ((Littleendian<<24) & 0xff000000 )/*4 to 1*/);
    return bigendian;
}

/*CONVERT AN INTEGER TO 32-BIT CHAR STRING*/

char* helper_ulong32_to_char(ULONG buffer)
{
    double i= pow(2, REG_SIZE-1);
    char* binary=malloc((REG_SIZE+1)*sizeof(char));
    INT32 counter=0;
    while (1)
    {
        if (buffer >= i)
        {
            buffer=buffer-floor(i);
            binary[counter]='1';
        }
        else
        {
            binary[counter]='0';
        }
        counter+=1;
        if (i/2<1)
        {
            binary[counter]='\0';
            break;
        }
        i=i/2;
    }
    return binary;
}

/*CONVERT AN 32-BIT CHAR STRING TO INTEGER*/

ULONG helper_char_to_ulong32(char* bits)
{
    if (strlen(bits)>REG_SIZE) printf("the string of bits is bigger than 32\n");
    else if (strlen(bits)<REG_SIZE )printf("the string of bits is smaller than 32\n");
    INT32 i;
    double integer=0;
    for(i=0; i<REG_SIZE; i++)
    {
        if (bits[i]=='1')
        {
            integer=integer+floor(pow(2,((REG_SIZE-1)-i)));
        }
        else
        {
            integer=integer+0;
        }
    }

    INT32 full=0xffffffff;

    ULONG temp= (ULLONG32)integer & full;
    return temp;
}

/* WRITE TO BUFFERFIELD A VALUE */

ULONG helper_write_value(INT32 startbit,INT32 lastbit,ULONG buffer,INT32 value)
{
    double integermask=0;  /*start counting from startbit (right-end) , stop counting to finalbit including it*/
    INT32 counter=0;
    char* charmask=malloc((REG_SIZE+1)*sizeof(char));
    while(counter<=(REG_SIZE-1))   /*fill in a character array with as many zeros (ascii) as the number of bits you want to change*/
    {
        if(counter>=((REG_SIZE-1)-lastbit) && counter<=(REG_SIZE-1)-startbit)
        {
            charmask[counter]='0';
        }
        else
        {
            charmask[counter]='1';
        }
        counter++;
    }
    charmask[counter]='\0';
    for (counter=(REG_SIZE-1); counter>=0 ; counter--)   /*convert character array to integer value*/
    {
        if (charmask[counter]=='1')
        {
            integermask=integermask+pow(2,(REG_SIZE-1)-counter);
        }
        else
        {
            integermask=integermask+0;
        }
    }
    UINT32 tempbuf= (ULLONG32)buffer & (ULLONG32)integermask;  /*zeroing the bits of interest that you want to change*/
    INT32 shiftedvalue=(value<<(startbit));  /*shift the writable value until it is aligned with the field of interest*/
    UINT32 compare= (ULLONG32)integermask ^ 0xffffffff;  /*check if writable value fits in the register's field  */
    compare=(compare>>(startbit));
    if (value>compare)
    {
        printf("the integer value is bigger than the buffer field\n");
        return 1;
    }
    ULONG finalbuf=shiftedvalue | tempbuf;  /*put the new value in the field of interest*/
    return finalbuf;
}

/* FETCH A BIT FIELD FROM A 32-BIT BUFFER*/

ULONG helper_read_value(INT32 firstbit,INT32 lastbit,ULONG buffer)
{
    /*start counting from startbit (right-end) from zero, stop counting to finalbit you want including it*/
    /*put all the bits of interest at start (right-end) of a 32-bit buffer, rest initialize to zero, size doesn't matter*/
    INT32 shiftbuffer=buffer>>(firstbit);
    INT32 i=0;
    double integermask=0;
    char* charmask=malloc((REG_SIZE+1)*sizeof(char));

    while(i<=(REG_SIZE-1))   /*fill in a character array with as many ones (ascii) as the number of bits you want to fetch*/
    {
        if(firstbit>lastbit)
        {
            charmask[(REG_SIZE-1)-i]='0';
        }
        else
        {
            charmask[(REG_SIZE-1)-i]='1';
        }
        i++;
        firstbit++;
    }
    charmask[i]='\0';

    for (i=0; i<=(REG_SIZE-1); i++) /*CONVERT CHARACTER ARRAY TO INTEGER VALUE*/
    {
        if (charmask[(REG_SIZE-1)-i]=='1')
        {
            integermask=integermask+pow(2,i);
        }
        else
        {
            integermask=integermask+0;
        }
    }

    ULONG finalvalue= (ULLONG32)integermask & (ULLONG32)shiftbuffer; /*DO LOGICAL AND THE BITS OF INTEREST WITH THE INTEGER VALUE THAT REPRESENTS THE MASK*/
    return finalvalue;
}

/*FETCH UNSIGNED LONG LONG'S MOST SIGNIFICANT WORD*/

ULONG helper_unsigned_ll_msw(DOUBLE64 value)
{
    ULONG mswdouble;
    //memcpy(&mswdouble, &value, sizeof(mswdouble)); depending on endianness
    memcpy(&mswdouble, (char *)&value + 4, sizeof(mswdouble));
    return mswdouble;
}

/*FETCH UNSIGNED LONG LONG'S LEAST SIGNIFICANT WORD*/

ULONG helper_unsigned_ll_lsw(DOUBLE64 value)
{
    ULONG mswdouble;
    memcpy(&mswdouble, &value, sizeof(mswdouble));
    //memcpy(&mswdouble, (char *)&value + 4, sizeof(mswdouble));depending on endianness
    return mswdouble;
}

///////////////////////////////////////////////////////////////// READ INSTRUCTION FIELD FUNCTIONS ////////////////////////////////////////////////////////////////////////


ULONG helper_instruction_field_disp30(ULONG instruction)
{
    return (instruction & 0x3fffffff);
}

ULONG helper_instruction_field_op(ULONG instruction)
{
    return (instruction & 0xc0000000)>> 30;
}

ULONG helper_instruction_field_rd(ULONG instruction)
{
    return (instruction & 0x3e000000)>>25;
}

ULONG helper_instruction_field_op2(ULONG instruction)
{
    return (instruction & 0x1c00000)>>22;
}

ULONG helper_instruction_field_a(ULONG instruction)
{
    return (instruction & 0x20000000)>>29;
}

ULONG helper_instruction_field_cond(ULONG instruction)
{
    return (instruction & 0x1E000000)>>25;
}

ULONG helper_instruction_field_imm22(ULONG instruction)
{
    return (instruction & 0x3FFFFF);
}

ULONG helper_instruction_field_disp22(ULONG instruction)
{
    return (instruction & 0x3FFFFF);
}

ULONG helper_instruction_field_op3(ULONG instruction)
{
    return (instruction & 0x1F80000)>>19;
}

ULONG helper_instruction_field_rs1(ULONG instruction)
{
    return (instruction & 0x7C000)>>14;
}

ULONG helper_instruction_field_i(ULONG instruction)
{
    return (instruction & 0x2000)>>13;
}

/* COOPERATES WITH PAGE TABLE ENTRY */

ULONG helper_instruction_field_asi(ULONG instruction)
{
    return (instruction & 0x1FE0)>>5;
}

ULONG helper_instruction_field_rs2(ULONG instruction)
{
    return (instruction & 0x1F);
}

ULONG helper_instruction_field_simm13(ULONG instruction)
{
    return (instruction & 0x1FFF);
}

ULONG helper_instruction_field_sign_ext_simm13(ULONG instruction)
{
    return (instruction | 0xFFFFE000);
}

/* RANGE -4096..4095 OF 13BIT SIGNED FIELD . FROM 0 TO 4095 RETURNS POSSITIVE, FROM 4096 TO 8191 RETURNS NEGATIVE RECONSTRUCTION TO INTEGER 32BIT */

UINT32 helper_instruction_field_usimm13(ULONG instruction)
{

    if( (instruction & 0x1FFF) > 0xFFF )
    {
        return (instruction | 0xFFFFE000) ;
    }
    else
    {
        return (instruction & 0x1FFF);
    }
}


ULONG helper_instruction_field_opf(ULONG instruction)
{
    return (instruction & 0x3FE0)>>5;
}


/* RANGE -64..64 OF 7BIT SIGNED FIELD . FROM 0 TO 64 RETURNS POSSITIVE, FROM 65 TO 127 RETURNS NEGATIVE RECONSTRUCTION TO INTEGER 7BIT */

UINT32 helper_instruction_field_imm7(ULONG instruction)
{

    if( (instruction & 0xFFFFFF80) > 0xFFFFFFC0 )
    {
        return (instruction  | 0xFFFFFFC0) ;
    }
    else
    {
        return (instruction & 0xFFFFFF80);
    }
}

/* RANGE 0..127 OF 7BIT INSIGNED FIELD */

ULONG helper_instruction_field_uimm7(ULONG instruction)
{

    return (instruction & 0x7F);

}

