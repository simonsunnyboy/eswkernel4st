/**
 * Entertainment Software Kernel for Atari ST
 * (c) 2016/18/26 by Matthias Arndt / ASM Software
 *
 * The MIT License applies to this software. Refer to the file COPYING for
 * details.
 *
 * @file  screen_buffer.c
 * @brief implementation of screen buffer initialization
 * @details The user may opt to compile the kernel without this file. 
 *          In this case the user application has to provide its own screen buffer initialization.
 */

#include <osbind.h>
#include <stdint.h>

#include "eswkernel4st/eswkernel4st_services.h"

/* --------------------------------------------------------------------------
 * public variables
 * --------------------------------------------------------------------------
 */

/* --------------------------------------------------------------------------
 * local variables
 * --------------------------------------------------------------------------
 */

static uint8_t new_screen_buffer[64256];  /**< RAM buffer for 2 Atari ST screens + overspil to align addresses on 256 byte boundaries */

/* --------------------------------------------------------------------------
 * kernel internal functions
 * --------------------------------------------------------------------------
 */


/* --------------------------------------------------------------------------
 * public user accessible functions
 * --------------------------------------------------------------------------
 */

void ESWK_InitScreenBuffers(ScreenBufferInformation* buffers)
{
    /* set new screen address */
    uintptr_t new_screen = (uintptr_t)&new_screen_buffer[0];

    new_screen = ESWK_AlignScreenBufferAddress(new_screen);    

    /* in the simples case the physical screen directly follows the logical screen and vice versa: */
    buffers->physbase = (void *)new_screen;
    buffers->logbase  = (void *)(new_screen + 32000);

    ESWK_ClearScreen(buffers->physbase);
    ESWK_ClearScreen(buffers->logbase);

    ESWK_SwapScreens();

    return;
}
