/*
  ------------------------------------------------------------------------------------------------------------------------------------------
  Project       : Sparc_V8 Emulator
  File          : SPARCV8_MAIN_INITIALIZER.c
  Description   : Sparc V8 initialization, main loop execution
  Author        : Monahopoulos Konstantinos
  ------------------------------------------------------------------------------------------------------------------------------------------
*/
/*
  ----------------------------------------------------------------------------------------------------------------------------------------
  Includes
  ----------------------------------------------------------------------------------------------------------------------------------------
*/

#include "SPARCV8_MAIN_INITIALIZER.h"
#include "THREADS.h"
#include "COMMAND_PROMPT.h"


int main()
{
    command_prompt_terminal_initialize(&command_prompt_terminal_ctx);

    thread_flag_initializer(&thread_info_ctx);

    thread_info_ptr->Thread_Handles[0] = CreateThread(
            NULL,// default security attributes
             0,// use default stack size
            command_prompt, // thread function
            &thread_info_ctx, // argument to thread function
            0, // use default creation flags
            (thread_info_ptr->lpThreadId[0]) ); // returns the thread identifier

            if  (thread_info_ptr->Thread_Handles[0] == NULL)
{
    printf("Create Parrent Thread() failed, error: %lu.\n", GetLastError());
    }

 WaitForSingleObject(thread_info_ptr->Thread_Handles[0],INFINITE); /* handle to mutex  , no time-out interval   */

 CloseHandle( thread_info_ptr->Thread_Handles[0]);

    return 0;

}










