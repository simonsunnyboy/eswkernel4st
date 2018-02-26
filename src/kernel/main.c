/**
 * Entertainment Software Kernel for Atari ST
 * (c) 2016/18 by Matthias Arndt / ASM Software
 *
 * The MIT License applies to this software. Refer to the file COPYING for
 * details.
 *
 * @file  main.c
 * @brief main function and loop implementation of the kernel
 */

#include <stdint.h>
#include <stdbool.h>
#include <osbind.h>

#include "eswkernel4st.h"
#include "eswkernel4st_services.h"

#include "internals.h"

/* --------------------------------------------------------------------------
 * local variables
 * --------------------------------------------------------------------------
 */

static volatile bool ESWK_int_running;

/* --------------------------------------------------------------------------
 * kernel internal functions
 * --------------------------------------------------------------------------
 */

int main(void)
{

    /* init kernel subsystems: */
    ESWK_int_InitScreens();
    /* ESWK_int_InitInterrupts(); */
    ESWK_int_running = true;

    /* run user initialization: */
    UserCode_Init();

    /* main loop until the user requests termination: */
    while(ESWK_int_running == true)
    {
        UserCode_Mainloop();
    }

    UserCode_TerminateLoop();

    return 0;
}

/* --------------------------------------------------------------------------
 * public user accessible functions
 * --------------------------------------------------------------------------
 */

void ESWK_RequestExit(void)
{
    ESWK_int_running = false;
    return;
}
