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
 * local definitions
 * --------------------------------------------------------------------------
 */

#define CONTERM_SYSVAR (*((uint8_t *)0x00000484UL))   /**< pointer to conterm system variable */

/* --------------------------------------------------------------------------
 * local variables
 * --------------------------------------------------------------------------
 */
/** @brief flag indicating if the kernel is running
 *  @details Set to false to terminate the main loop and exit the kernel via \ref ESWK_RequestExit
 */
static volatile bool ESWK_int_running; 

/* --------------------------------------------------------------------------
 * kernel internal functions
 * --------------------------------------------------------------------------
 */

 /** @brief Main kernel function to be run in Supervisor mode
  *  @details This function initializes the kernel and runs the main loop until the user requests termination.
  */
static void ESWK_int_Main(void)
{
    const uint32_t mch_cookie = ESWK_GetMachine();

    /* hide VT52 cursor: ESC f*/
    (void)Cconws("\0x1B""f");

    /* check for sane machine before continuing: */
    if(mch_cookie >= MCH_MILAN_C)
    {
        (void)Cconws("WARNING - non genuine Atari hardware detected! Your software may fail!\r\n");
    }

    /* init kernel subsystems: */
    ESWK_int_InitSTLow();
    ESWK_int_InitScreens();
    ESWK_int_InitInterrupts();

    /* deactivate keyclick: */
    CONTERM_SYSVAR &= 0xFEU;

    /* kill YM2149 sound: */
    (void)Giaccess(0,0x88);
    (void)Giaccess(0,0x89);
    (void)Giaccess(0,0x8A);

    /* enable Atari Powerpads if machine provides it: */
    ESWK_int_SetJagpadRoutine(mch_cookie);

    /* The kernel is running and initialized now, handle user application: */
    ESWK_int_running = true;

    /* run user initialization: */
    UserCode_Init();

    /* main loop until the user requests termination: */
    while(ESWK_int_running == true)
    {
        UserCode_Mainloop();
    }

    UserCode_TerminateLoop();

    ESWK_int_ResetST();
}

int main(void)
{
    Supexec(ESWK_int_Main); /* force Supervisor */
    return 0; /* never reached due to machine reset, however necessary so the compiler does not complain */
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
