/**
 * Entertainment Software Kernel for Atari ST
 * (c) 2016/18 by Matthias Arndt / ASM Software
 *
 * The MIT License applies to this software. Refer to the file COPYING for
 * details.
 *
 * @file  ikbd_joy.c
 * @brief implementation of IKBD related routines for reading the joysticks
 */

#include <stdint.h>
#include "eswkernel4st_services.h"

/* --------------------------------------------------------------------------
 * local definitions
 * --------------------------------------------------------------------------
 */

/* --------------------------------------------------------------------------
 * local variables
 * --------------------------------------------------------------------------
 */

/* --------------------------------------------------------------------------
 * kernel internal variables
 * --------------------------------------------------------------------------
 */

extern volatile uint8_t IKBD_Joystick0;      /**< Joystick state on port 0 (driver internal) */
extern volatile uint8_t IKBD_Joystick1;      /**< Joystick state on port 1 (driver internal) */

/* --------------------------------------------------------------------------
 * public user accessible functions
 * --------------------------------------------------------------------------
 */

/**
 * @brief  read given joystick state
 * @param  portnr indicated the joystick port queried
 * @return joystick reading composed of IKBD_JOY_... bits
 */
uint8_t ESWK_IKBD_ReadJoystick(uint8_t portnr)
{
    uint8_t joyreading = IKBD_Joystick1;

    if(portnr == 0)
    {
        joyreading = IKBD_Joystick0;
    }

    return joyreading;
}

/**
 * @brief   map Atari Powerpad reading to IKBD compatible joystick reading
 * @details Any powerpad fire button maps to the joystick button
 * @param   jagpad_reading composed of JAGPAD_... bits
 * @return  joystick reading composed of IKBD_JOY_... bits
 */
uint8_t ESWK_MapJagpadToJoystick(uint32_t jagpad_reading)
{
    uint32_t jagpad_masked = (jagpad_reading & (JAGPAD_UP|JAGPAD_DOWN|JAGPAD_LEFT|JAGPAD_RIGHT));
    uint8_t  ikbd_mapping = (uint8_t)jagpad_masked;

    /* any fire button pressed? */
    if((jagpad_reading & JAGPAD_FIRE) != 0)
    {
        ikbd_mapping |= IKBD_JOY_FIRE;
    }

    return ikbd_mapping;

}
