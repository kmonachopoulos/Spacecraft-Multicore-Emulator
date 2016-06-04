#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

/*
  --------------------------------------------------------------------------------------------------
  Includes
  --------------------------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include <windows.h>
#include <signal.h>
#include <time.h>
/*
  --------------------------------------------------------------------------------------------------
  Defines
  --------------------------------------------------------------------------------------------------
*/

#define REG_SIZE 32 /* REGISTER SIZE */

typedef float FLOAT32;
typedef double DOUBLE64;
typedef unsigned long long ULLONG32;

/*TYPES ARE KNOWN IN ALL HEADERS FOR GENERAL USE INCLUDED FROM WINDOWS.H*/
/*
typedef unsigned long ULONG;
typedef unsigned int UINT32;
typedef int INT32;
typedef float FLOAT32;
typedef int8_t INT8;
typedef int16_t INT16;
typedef uint8_t UINT8;
typedef uint16_t UINT16;
typedef unsigned long ULONG32;
#define TRUE 1
#define FALSE 0
*/


#endif // TYPES_H_INCLUDED
