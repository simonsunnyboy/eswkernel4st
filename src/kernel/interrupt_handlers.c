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
#include <stdbool.h>
#include <stdlib.h>

#include "internals.h"
#include "eswkernel4st_services.h"


/* --------------------------------------------------------------------------
 * local variables
 * --------------------------------------------------------------------------
 */

static void (*ESWK_50hz_UserRoutine_ptr)(void) = NULL;  /**< internal function pointer to user supplied routine run at 50Hz from Timer C */
static void (*ESWK_200hz_UserRoutine_ptr)(void) = NULL;  /**< internal function pointer to user supplied routine run at 200Hz from Timer C */
static void (*ESWK_VBL_UserRoutine_ptr)(void) = NULL;  /**< internal function pointer to user supplied routine run from VBL interrupt */
static void (*ESWK_JagpadHandler_ptr)(void) = NULL;  /**< internal function pointer to user supplied routine run from VBL interrupt */

/* --------------------------------------------------------------------------
 * kernel global variables
 * --------------------------------------------------------------------------
 */

volatile uint32_t ESWK_int_JagpadReading[2];  /**< internal state of Atari Powerpads */

/* --------------------------------------------------------------------------
 * kernel internal functions
 * --------------------------------------------------------------------------
 */


void ESWK_int_50hz_ISR(void)
{
    /* service Atari Powerpads if available on hardware: */
    if(ESWK_HasJagpad() == true)
    {
        ESWK_JagpadHandler_ptr();
    }
    else
    {
        /* no pads connected, return sane values */
        ESWK_int_JagpadReading[0] = 0;
        ESWK_int_JagpadReading[1] = 0;
    }

    /* service user 50hz routine: */
    if(ESWK_50hz_UserRoutine_ptr != NULL)
    {
        ESWK_50hz_UserRoutine_ptr();
    }

    return;
}

void ESWK_int_200hz_ISR(void)
{
    /* service user 200hz routine: */
    if(ESWK_200hz_UserRoutine_ptr != NULL)
    {
        ESWK_200hz_UserRoutine_ptr();
    }

    return;
}

void ESWK_int_VBL_ISR(void)
{
    /* service user VBL routine: */
    if(ESWK_VBL_UserRoutine_ptr != NULL)
    {
        ESWK_VBL_UserRoutine_ptr();
    }

    return;
}

void ESWK_int_SetJagpadRoutine(uint32_t mch_cookie_value)
{
    /* enable Atari Powerpad support for 1040STE and Falcon 030: */
    if(((mch_cookie_value & MCH_STE) == MCH_STE) ||
       (((mch_cookie_value & MCH_FALCON) == MCH_FALCON))
      )
    {
        ESWK_JagpadHandler_ptr = &ESWK_int_ReadJagpads;
    }
    else
    {
        ESWK_JagpadHandler_ptr = NULL;
    }

    return;
}

/* --------------------------------------------------------------------------
 * public user accessible functions
 * --------------------------------------------------------------------------
 */

bool ESWK_HasJagpad(void)
{
    bool has_ejp = false;

    if(ESWK_JagpadHandler_ptr != NULL)
    {
        has_ejp = true;
    }

    return has_ejp;
}

uint32_t ESWK_ReadJagpad(uint8_t joypad_nr)
{
    uint32_t jagpad = 0;

    if(joypad_nr < 2)
    {
        /* return value of valid power pad: */
        jagpad = ESWK_int_JagpadReading[joypad_nr];
    }

    return jagpad;
}

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
