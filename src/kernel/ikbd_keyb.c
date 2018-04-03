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

/* --------------------------------------------------------------------------
 * local variables
 * --------------------------------------------------------------------------
 */

/* --------------------------------------------------------------------------
 * kernel internal variables
 * --------------------------------------------------------------------------
 */

extern volatile uint8_t IKBD_Mousemode;  /**< flag indicating if mouse is active (driver internal) */

/* --------------------------------------------------------------------------
 * public user accessible functions
 * --------------------------------------------------------------------------
 */
