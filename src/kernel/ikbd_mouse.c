/**
 * Entertainment Software Kernel for Atari ST
 * (c) 2016/18 by Matthias Arndt / ASM Software
 *
 * The MIT License applies to this software. Refer to the file COPYING for
 * details.
 *
 * @file  ikbd_mouse.c
 * @brief implementation of IKBD related routines for handling mouse input
 */

#include <stdint.h>
#include <stdbool.h>

#include "eswkernel4st_services.h"

/* --------------------------------------------------------------------------
 * local definitions
 * --------------------------------------------------------------------------
 */

/**
 * @brief structure for kernel internal mouse data
 */
typedef struct
{
    ESWK_MouseState state;
    int16_t  w;
    int16_t  h;
    bool     limit;
    uint8_t  threshold;
} ESWK_int_MouseData;


/* --------------------------------------------------------------------------
 * local variables
 * --------------------------------------------------------------------------
 */

/**
 * @brief kernel internal mouse data in RAM
 */
static volatile ESWK_int_MouseData ESWK_Mouse =
{
    {0,0,0}, 320,200,true,128
};

/* --------------------------------------------------------------------------
 * kernel internal variables
 * --------------------------------------------------------------------------
 */

extern volatile uint8_t        IKBD_MouseB;         /**< Mouse on port 0, buttons (driver internal) */
extern volatile int16_t        IKBD_MouseX;         /**< Mouse X position (driver internal) */
extern volatile int16_t        IKBD_MouseY;         /**< Mouse Y position (driver internal) */


/* --------------------------------------------------------------------------
 * public user accessible functions
 * --------------------------------------------------------------------------
 */

/**
 * @brief reads the accumulated mouse packets and update the mouse position
 */
void ESWK_IKBD_ReadMouse(ESWK_MouseState * mouseData)
{
    int16_t xoffset, yoffset;

    if(ESWK_Mouse.threshold > 0)
    {
        /* scale the mouse movement by the configurable threshold */
        xoffset = (int16_t)((int32_t)(IKBD_MouseX * ESWK_Mouse.threshold) / 128);
        yoffset = (int16_t)((int32_t)(IKBD_MouseY * ESWK_Mouse.threshold) / 128);
    }
    else
    {
        /* 0% scaling is not allowed -> scale as 100% */
        xoffset = IKBD_MouseX;
        yoffset = IKBD_MouseY;
    }

    ESWK_Mouse.state.b = IKBD_MouseB;
    ESWK_Mouse.state.x += xoffset;
    ESWK_Mouse.state.y += yoffset;

    if(ESWK_Mouse.limit == true)
    {
        /* mouse coordinates limitation is active? */
        if(ESWK_Mouse.state.x < 0)
        {
            ESWK_Mouse.state.x = 0;
        }
        else if(ESWK_Mouse.state.x > ESWK_Mouse.w)
        {
            ESWK_Mouse.state.x = ESWK_Mouse.w;
        }
        else
        {
            /* do nothing */
        }

        if(ESWK_Mouse.state.y < 0)
        {
            ESWK_Mouse.state.y = 0;
        }
        else if(ESWK_Mouse.state.y > ESWK_Mouse.h)
        {
            ESWK_Mouse.state.y = ESWK_Mouse.h;
        }
        else
        {
            /* do nothing */
        }
    }

    /* acknowledge accumulated mouse vector (driver internals) */
    IKBD_MouseX = 0;
    IKBD_MouseY = 0;

    /* update user mouse values: */
    *mouseData = ESWK_Mouse.state;
    return;
}

/**
 * @brief allows to configure the scaling of relative mouse movement
 */
void ESWK_IKBD_SetMouseThreshold(uint8_t new_threshold)
{
    ESWK_Mouse.threshold = new_threshold;
    return;
}

/**
 * @brief set current mouse position and define the screen size
 */
void ESWK_IKBD_SetMouseOrigin(int16_t x, int16_t y, uint16_t w, uint16_t h)
{
    ESWK_Mouse.state.x = x;
    ESWK_Mouse.state.y = y;
    ESWK_Mouse.state.b = 0;
    ESWK_Mouse.w = w;
    ESWK_Mouse.h = h;    
    ESWK_Mouse.limit = true;
    ESWK_Mouse.threshold = 128;
    IKBD_MouseX = 0;
    IKBD_MouseY = 0;
    return;
}
