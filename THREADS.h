#ifndef THREADS_H_INCLUDED
#define THREADS_H_INCLUDED

/*
  --------------------------------------------------------------------------------------------------
  Includes
  --------------------------------------------------------------------------------------------------
*/

#include "TYPES.h"

/*
  --------------------------------------------------------------------------------------------------
  Structures
  --------------------------------------------------------------------------------------------------
*/

struct THREAD_INFO_context{

LPSECURITY_ATTRIBUTES lpThreadAttributes;
SIZE_T dwStackSize;
DWORD dwCreationFlags;
HANDLE ghMutex;
HANDLE Thread_Handles[2];
LPDWORD lpExitCode;
LPDWORD lpThreadId[2];
UINT8 thread_suspend;
UINT8 thread_exit;
};

struct THREAD_INFO_context thread_info_ctx;
struct THREAD_INFO_context *thread_info_ptr;

/*
  --------------------------------------------------------------------------------------------------
  Function Prototyping
  --------------------------------------------------------------------------------------------------
*/

void thread_flag_initializer(struct THREAD_INFO_context *thread_info_tmp_ptr);


#endif // THREADS_H_INCLUDED
