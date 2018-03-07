/**
 * Entertainment Software Kernel for Atari ST
 * (c) 2016/18 by Matthias Arndt / ASM Software
 *
 * The MIT License applies to this software. Refer to the file COPYING for
 * details.
 *
 * @file  demoapp.c
 * @brief demonstration application for the kernel based on functions called by the kernel
 */

#include <stdint.h>
#include <osbind.h>

#include "eswkernel4st.h"
#include "eswkernel4st_services.h"

volatile uint16_t col = 0x000;
volatile uint16_t tmr = 0;

static void UserCode_50Hz_ISR(void)
{
    tmr++;
    if(tmr > (50 * 5))
    {
        ESWK_RequestExit();
    }
}

static void UserCode_200Hz_ISR(void)
{
    *(uint16_t *)0xFFFF8240 = col;
    col += 2;

}

static void UserCode_VBL_ISR(void)
{
    col = 0x000;
}

void UserCode_Init(void)
{
    static uint16_t my_palette[] = { 0x0000, 0x0000, 0x0000, 0x0000,
                                     0x0000, 0x0000, 0x0000, 0x0000,
                                     0x0000, 0x0000, 0x0000, 0x0000,
                                     0x0000, 0x0000, 0x0000, 0x0FFF
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
