/**
 * Entertainment Software Kernel for Atari ST
 * (c) 2016/18 by Matthias Arndt / ASM Software
 *
 * The MIT License applies to this software. Refer to the file COPYING for
 * details.
 *
 * @file  demo_isr.c
 * @brief demonstration application for the kernel based on functions called by the kernel
 */

#include <stdint.h>
#include <osbind.h>

#include "eswkernel4st/eswkernel4st.h"
#include "eswkernel4st/eswkernel4st_services.h"

static volatile uint16_t col = 0x000U;   /**< current color */
static volatile uint16_t tmr = 0U;       /**< timer */

static void UserCode_50Hz_ISR(void)
{
    tmr++;
    if(tmr > (50 * 5))
    {
        ESWK_RequestExit();
    }
}

/**
 * @brief update the color with every 200Hz interrupt
 */
static void UserCode_200Hz_ISR(void)
{
    *(uint16_t *)0xFFFF8240UL = col;
    col += 2;

}

/**
 * @brief VBL handler to reset the color to black at the beginning of every screen refresh
 */
static void UserCode_VBL_ISR(void)
{
    col = 0x000U;
}

void UserCode_Init(void)
{
    static uint16_t my_palette[] = { 0x0000U, 0x0000U, 0x0000U, 0x0000U,
                                     0x0000U, 0x0000U, 0x0000U, 0x0000U,
                                     0x0000U, 0x0000U, 0x0000U, 0x0000U,
                                     0x0000U, 0x0000U, 0x0000U, 0x0FFFU
                                   };
    ESWK_SetPalette(my_palette);

    /* Set all user vectors: */
    ESWK_Set50HzRoutine(&UserCode_50Hz_ISR);
    ESWK_Set200HzRoutine(&UserCode_200Hz_ISR);
    ESWK_SetVBLRoutine(&UserCode_VBL_ISR);

    return;
}

void UserCode_Mainloop(void)
{
    Vsync();
}

void UserCode_TerminateLoop(void)
{

}
