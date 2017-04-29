/*
  ------------------------------------------------------------------------------------------------------------------------------------------
  Project       : Sparc_V8 Emulator
  File          : SPARCV8_TRAPS.c
  Description   : Sparc V8 Multithreading flags initialization
  Author        : Monachopoulos Konstantinos
  ------------------------------------------------------------------------------------------------------------------------------------------
*/
/*
  ----------------------------------------------------------------------------------------------------------------------------------------
  Includes
  ----------------------------------------------------------------------------------------------------------------------------------------
*/

#include "THREADS.h"

void thread_flag_initializer(struct THREAD_INFO_context *thread_info_tmp_ptr)
{
    thread_info_tmp_ptr->dwCreationFlags=0x00000004; /* The thread is created in a suspended state, and does not run until the ResumeThread function is called. */
    thread_info_tmp_ptr->lpThreadAttributes=NULL; /* A pointer to a SECURITY_ATTRIBUTES structure that
    determines whether the returned handle can be inherited by child processes.
    If lpThreadAttributes is NULL, the handle cannot be inherited. */
    thread_info_tmp_ptr->dwStackSize=0; /* The initial size of the stack, in bytes. The system rounds this value to the nearest page.
    If this parameter is zero, the new thread uses the default size for the executable. For more information, see Thread Stack Size. */
    //thread_info_tmp_ptr->ghMutex=0; /* create ghmutex for locking variable's value or function calls */
    thread_info_tmp_ptr->thread_suspend=TRUE;
    thread_info_tmp_ptr->thread_exit=FALSE;
    thread_info_tmp_ptr->Thread_Handles[0]=NULL;
    thread_info_tmp_ptr->Thread_Handles[1]=NULL;

    thread_info_tmp_ptr->ghMutex = CreateMutex(
                             NULL,              // default security attributes
                             FALSE,             // initially not owned
                             "child thread keep alive");

        if (thread_info_tmp_ptr->ghMutex  == NULL)
        {
            printf("CreateMutex error: %lu\n", GetLastError());
            return ;
        }
    thread_info_ptr=thread_info_tmp_ptr;
    return;
}

