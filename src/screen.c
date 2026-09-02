/**
 * Entertainment Software Kernel for Atari ST
 * (c) 2016/18 by Matthias Arndt / ASM Software
 *
 * The MIT License applies to this software. Refer to the file COPYING for
 * details.
 *
 * @file  screen.c
 * @brief implementation of screen handling subsystem
 */

#include <osbind.h>
#include <stdint.h>

#include "eswkernel4st/eswkernel4st_services.h"

/* --------------------------------------------------------------------------
 * public variables
 * --------------------------------------------------------------------------
 */
void * ESWK_logbase;    /**< logical screen address, now displayed */
void * ESWK_physbase;   /**< physical screen address, currently active and displayed by the Shifter */

/* --------------------------------------------------------------------------
 * local variables
 * --------------------------------------------------------------------------
 */

static uint8_t new_screen_buffer[64256];  /**< RAM buffer for 2 Atari ST screens + overspil to align addresses on 256 byte boundaries */

/* --------------------------------------------------------------------------
 * kernel internal functions
 * --------------------------------------------------------------------------
 */

void ESWK_int_InitScreens(void)
{
    /* set new screen address */
    uint32_t new_screen = (uint32_t)&new_screen_buffer[0];

    new_screen += 256;
    new_screen &= 0xFFFFFF00UL;

    ESWK_physbase = (void *)new_screen;
    ESWK_logbase  = (void *)(new_screen + 32000);

    ESWK_SwapScreens();

    return;
}

/* --------------------------------------------------------------------------
 * public user accessible functions
 * --------------------------------------------------------------------------
 */

void ESWK_SwapScreens(void)
{
    void * tmp = ESWK_logbase;

    ESWK_logbase = ESWK_physbase;
    ESWK_physbase = tmp;

    Setscreen(ESWK_physbase,ESWK_physbase,-1);
    Vsync();
}

void ESWK_ClearScreen(void * screenaddr)
{
    uint32_t * dest = (uint32_t *)screenaddr;
    uint16_t idx;

    for(idx = 0; idx < 8000; idx ++)
    {
        *dest++ = 0;
    }

    return;
}

void ESWK_CopyScreen(void * src_screenaddr, void * dest_screenaddr)
{
    uint32_t * dest = (uint32_t *)dest_screenaddr;
    uint32_t * src = (uint32_t *)src_screenaddr;
    uint16_t idx;

    for(idx = 0; idx < 8000; idx ++)
    {
        *dest++ = *src++;
    }

    return;
}

void ESWK_SetPalette(void * paletteaddr)
{
    uint16_t * col = (uint16_t *)0xFFFF8240UL;
    uint16_t * src = (uint16_t *)paletteaddr;
    uint16_t idx;

    for(idx = 0; idx < 16; idx++)
    {
        *col++ = *src++;
    }
    return;
}

void ESWK_GetPalette(void * paletteaddr)
{
    uint16_t * col =  (uint16_t *)0xFFFF8240;
    uint16_t * dest = (uint16_t *)paletteaddr;
    int idx;

    for(idx = 0; idx < 16; idx++)
    {
        *dest++ = *col++;
    }
    return;
}
