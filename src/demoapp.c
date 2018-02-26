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

void UserCode_Init(void)
{
    static uint16_t my_palette[] = { 0x0031, 0x0000, 0x0000, 0x0000,
                                     0x0000, 0x0000, 0x0000, 0x0000,
                                     0x0000, 0x0000, 0x0000, 0x0000,
                                     0x0000, 0x0000, 0x0000, 0x0FFF
                                   };
    ESWK_SetPalette(my_palette);

    (void)Cconws( "press any key\n");

    Cconin();

    return;
}

void UserCode_Mainloop(void)
{
    ESWK_RequestExit();
}

void UserCode_50Hz_ISR(void)
{

}

void UserCode_VBL_ISR(void)
{

}

void UserCode_TerminateLoop(void)
{

}
