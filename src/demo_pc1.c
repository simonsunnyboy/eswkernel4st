/**
 * Entertainment Software Kernel for Atari ST
 * (c) 2016/18 by Matthias Arndt / ASM Software
 *
 * The MIT License applies to this software. Refer to the file COPYING for
 * details.
 *
 * @file  demo_pc1.c
 * @brief demonstration application for the kernel based on functions called by the kernel for DEGAS picture support
 */

#include <stdint.h>
#include <osbind.h>

#include "eswkernel4st.h"
#include "eswkernel4st_services.h"

#include "demo_pc1.h" /* demo picture packed */

uint8_t degas_picture[32034];

volatile uint16_t tmr = 0;

static void UserCode_50Hz_ISR(void)
{
    tmr++;
    if(tmr > (50 * 10))
    {
        ESWK_RequestExit();
    }
}

void UserCode_Init(void)
{
    /* depack example PC1 to PI1 and display onscreen: */
    ESWK_DepackPC1Picture(&GIRL2_PC1[0], &degas_picture[0]);
    ESWK_ShowPI1Picture(&degas_picture[0], ESWK_physbase);


    /* Set all user vectors: */
    ESWK_Set50HzRoutine(&UserCode_50Hz_ISR);

    return;
}

void UserCode_Mainloop(void)
{
    Vsync();
}

void UserCode_TerminateLoop(void)
{

}
