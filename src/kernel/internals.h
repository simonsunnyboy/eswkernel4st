/**
 * Entertainment Software Kernel for Atari ST
 * (c) 2016/18 by Matthias Arndt / ASM Software
 *
 * The MIT License applies to this software. Refer to the file COPYING for
 * details.
 *
 * @file  internals.h
 * @brief internal API definition for interfacing inside th kernel itself
 * @attention Do not use this header in your own application!
 */

#ifndef INTERNALS_H
    #define INTERNALS_H

    void ESWK_int_InitScreens(void);
    void ESWK_int_InitInterrupts(void);

    void ESWK_int_ReadJagpads(void);
    void ESWK_int_SetJagpadRoutine(uint32_t mch_cookie_value);

    void ESWK_int_50hz_ISR(void);
    void ESWK_int_200hz_ISR(void);
    void ESWK_int_VBL_ISR(void);

#endif
