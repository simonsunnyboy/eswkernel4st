/**
 * Entertainment Software Kernel for Atari ST
 * (c) 2016/18 by Matthias Arndt / ASM Software
 *
 * The MIT License applies to this software. Refer to the file COPYING for
 * details.
 *
 * @file  ikbd_keyb.c
 * @brief implementation of IKBD related routines for reading the keyboard
 */

#include <osbind.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "eswkernel4st_services.h"

/* --------------------------------------------------------------------------
 * local definitions
 * --------------------------------------------------------------------------
 */

#define _200HZ_TICK (*(volatile uint32_t const *)0x000004baUL)

/* --------------------------------------------------------------------------
 * local variables
 * --------------------------------------------------------------------------
 */

/* --------------------------------------------------------------------------
 * kernel internal variables
 * --------------------------------------------------------------------------
 */

extern volatile uint8_t IKBD_Keyboard[128];  /**< Key press table  (driver internal) */
extern volatile uint8_t IKBD_Joystick0;      /**< Joystick state on port 0 (driver internal) */
extern volatile uint8_t IKBD_Joystick1;      /**< Joystick state on port 1 (driver internal) */
extern volatile uint8_t IKBD_Mousemode;      /**< flag indicating if mouse is active (driver internal) */

/* --------------------------------------------------------------------------
 * public user accessible functions
 * --------------------------------------------------------------------------
 */

/**
 * @brief flushes all pending keyboard and joystick events
 */
void ESWK_IKBD_Flush(void)
{
    uint16_t i;
    uint16_t flush_ok;
    uint32_t tick;

    ESWK_MouseState currMouse;

    do
    {
        tick = _200HZ_TICK;

        /* read mouse data if active: */
        if(IKBD_Mousemode != 0)
        {
            ESWK_IKBD_ReadMouse(&currMouse);
        }
        else
        {
            currMouse.b = 0;
        }

        flush_ok = (  (currMouse.b == 0)
                    &&(IKBD_Joystick0 == 0)
                    &&(IKBD_Joystick1 == 0));

        for(i=0; i<128; i++)
        {
            if((ESWK_KeyPress)IKBD_Keyboard[i] == ESWK_IKBD_KEY_PRESSED)
            {
                flush_ok = 0;
                break;			/* allow some time to pass */
            }
        }
        /* await Timer C to count */
        while((tick + 10) < _200HZ_TICK )
        {
            /* wait for time */
        }


    } while(!flush_ok);
    return;
}

/**
 * @brief   read and debounce a key by scancode
 * @details If the given key is pressed, the status is cleared internally. Use to read input.
 * @return  key press state
 * @see     ESWK_KeyPress
 */
ESWK_KeyPress ESWK_IKBD_ReadKey(uint8_t scancode)
{
    /* undefined key state -> means key not pressed */
    ESWK_KeyPress keystatus = ESWK_IKBD_KEY_RELEASED;


    if((scancode & 0x80) != 0)
    {
        /* upper bit of scancode set -> scancode is invalid */
        keystatus = ESWK_IKBD_KEY_RELEASED;
    }
    else
    {
        keystatus = (ESWK_KeyPress)IKBD_Keyboard[scancode];

        if((keystatus == ESWK_IKBD_KEY_PRESSED)||(keystatus == ESWK_IKBD_KEY_RELEASED))
        {
            /* current key in defined state -> read it and set as read */
            IKBD_Keyboard[scancode] = ESWK_IKBD_KEY_UNDEFINED;
        }
        else
        {
            keystatus = ESWK_IKBD_KEY_RELEASED;
        }
    }

    return keystatus;
}

/**
 * @brief   read key press state by scancode
 * @details The internal state is not changed. A subsequent read still may return the state "key is pressed down"
 * @return  key press state
 * @see     ESWK_KeyPress
 */
ESWK_KeyPress ESWK_IKBD_IsKeyPressed(uint8_t scancode)
{
    ESWK_KeyPress keystatus = (ESWK_KeyPress)IKBD_Keyboard[scancode];

    if(keystatus != ESWK_IKBD_KEY_PRESSED)
    {
        keystatus = ESWK_IKBD_KEY_RELEASED;
    }

    return keystatus;
}
