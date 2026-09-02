/**
 * Entertainment Software Kernel for Atari ST
 * (c) 2016/18/26 by Matthias Arndt / ASM Software
 *
 * The MIT License applies to this software. Refer to the file COPYING for
 * details.
 *
 * @file  internals.h
 * @brief internal API definition for interfacing inside the kernel itself
 * @attention Do not use this header in your own application!
 */

#ifndef INTERNALS_H
    #define INTERNALS_H

    /**
     * @brief provides routine to initialize the video hardware for ST-LOW on ST, STe, Mega-ST,TT,Falcon,CT60
     * @details The implementation is a slight variation of the Multi Atari Boot code by Leonard/Oxygene
     *          - see http://leonard.oxg.free.fr/articles/multi_atari/multi_atari.html	
     */
    void ESWK_int_InitSTLow(void);

    /**
     * @brief initializes 2 screen buffers for ST-LOW
     * @details Adresses should be aligned on 256 byte boundaries.
     */
    void ESWK_int_InitScreens(void);

    /**
     * @brief initialize the Atari ST interrupt handlers for 50Hz, 200Hz and VBL
     * @details The kernel hooks its own handler for TC at 50 and 200hz aswell as the VBL. 
     *          User routines can be set through callbacks.
     */
    void ESWK_int_InitInterrupts(void);

    /**
     * @brief  read Jaguar Power pads from the Extended Joystick Ports on STE and Falcon 030
     * @details Reading the registers on Mega STE works but produces erratic results.
     *          The function should only be called by the kernel for the Atari STE and Falcon 030
     *          but not for Mega STE.
     *           
     *          It is only enabled through @ref ESWK_int_SetJagpadRoutine.
     */
    void ESWK_int_ReadJagpads(void);

    /**
     * @brief internal function to set the user supplied Atari Powerpad routine
     * @details The kernel enables Atari Powerpad support for 1040STE and Falcon 030.
     *          The kernel will call this routine at 50Hz from Timer C.
     * @param mch_cookie_value The value of the MCH cookie from the cookie jar.
     */
    void ESWK_int_SetJagpadRoutine(uint32_t mch_cookie_value);

    /**
     * @brief internal interrupt service routines for Atari ST
     * @details The kernel hooks its own handler for TC at 50 and 200hz
     */
    void ESWK_int_50hz_ISR(void);

    /**
     * @brief internal interrupt service routine for 200hz timer
     */
    void ESWK_int_200hz_ISR(void);

    /**
     * @brief internal interrupt service routine for vertical blank
     */
    void ESWK_int_VBL_ISR(void);

    /**
     * @brief provides routine to perform the reset of the ST
     * @details The implementation assumes that the supervisor mode is already active.
     */
    void ESWK_int_ResetST(void);

#endif
