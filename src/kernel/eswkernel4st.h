/**
 * Entertainment Software Kernel for Atari ST
 * (c) 2016/18 by Matthias Arndt / ASM Software
 *
 * The MIT License applies to this software. Refer to the file COPYING for
 * details.
 *
 * @file  eswkernel4st.h
 * @brief public API definition for interfacing with user applications
 * @details The user application has implement all functions mentioned in this interface. The kernel will call them when needed.
 */
#ifndef ESWKERNEL4ST_H
    #define ESWKERNEL4ST_H

    #include <stdint.h>

    void UserCode_Init(void);
    void UserCode_Mainloop(void);
    void UserCode_50Hz_ISR(void);
    void UserCode_VBL_ISR(void);
    void UserCode_TerminateLoop(void);

#endif
