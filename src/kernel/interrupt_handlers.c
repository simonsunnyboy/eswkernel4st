/**
 * Entertainment Software Kernel for Atari ST
 * (c) 2016/18 by Matthias Arndt / ASM Software
 *
 * The MIT License applies to this software. Refer to the file COPYING for
 * details.
 *
 * @file  interrupt_handlers.c
 * @brief implementation of interrupt service routine handlers
 * @details The kernel hooks its own handler for TC at 50 and 200hz aswell as the VBL. User routines can be set through callbacks.
 */

#include <osbind.h>
#include <stdint.h>
#include <stdlib.h>

#include "eswkernel4st_services.h"


/* --------------------------------------------------------------------------
 * local variables
 * --------------------------------------------------------------------------
 */

static void (*ESWK_50hz_UserRoutine_ptr)(void) = NULL;  /**< internal function pointer to user supplied routine run at 50Hz from Timer C */
static void (*ESWK_200hz_UserRoutine_ptr)(void) = NULL;  /**< internal function pointer to user supplied routine run at 200Hz from Timer C */
static void (*ESWK_VBL_UserRoutine_ptr)(void) = NULL;  /**< internal function pointer to user supplied routine run from VBL interrupt */

/* --------------------------------------------------------------------------
 * kernel internal functions
 * --------------------------------------------------------------------------
 */

void ESWK_int_50hz_ISR(void)
{
    if(ESWK_50hz_UserRoutine_ptr != NULL)
    {
        ESWK_50hz_UserRoutine_ptr();
    }
}

void ESWK_int_200hz_ISR(void)
{
    if(ESWK_200hz_UserRoutine_ptr != NULL)
    {
        ESWK_200hz_UserRoutine_ptr();
    }
}

void ESWK_int_VBL_ISR(void)
{
    if(ESWK_VBL_UserRoutine_ptr != NULL)
    {
        ESWK_VBL_UserRoutine_ptr();
    }
}

/* --------------------------------------------------------------------------
 * public user accessible functions
 * --------------------------------------------------------------------------
 */

void ESWK_Set50HzRoutine(void (*userrout)(void))
{
    ESWK_50hz_UserRoutine_ptr = userrout;
    return;
}

void ESWK_Set200HzRoutine(void (*userrout)(void))
{
    ESWK_200hz_UserRoutine_ptr = userrout;
    return;
}

void ESWK_SetVBLRoutine(void (*userrout)(void))
{
    ESWK_VBL_UserRoutine_ptr = userrout;
    return;
}
