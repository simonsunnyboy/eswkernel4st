/**
 * Entertainment Software Kernel for Atari ST
 * (c) 2016/18 by Matthias Arndt / ASM Software
 *
 * The MIT License applies to this software. Refer to the file COPYING for
 * details.
 *
 * @file  eswkernel4st_services.h
 * @brief public API definition for services provided by the kernel to user applications
 */
#ifndef ESWKERNEL4ST_SERVICES_H
    #define ESWKERNEL4ST_SERVICES_H

    #include <stdint.h>

    /**
     * @brief callback for the user application to terminate the main loop
     */
    void ESWK_RequestExit(void);


    /**
     * @brief kernel provided address of logical 32K Atari ST screen in RAM (aligned to 256 byte boundary)
     * @attention Do not change the pointer unless necessary.
     */
    extern void * ESWK_logbase;

    /**
     * @brief kernel provided address of physical 32K Atari ST screen in RAM (aligned to 256 byte boundary)
     * @details This is used as a source address to copy data from.
     * @attention Do not change the pointer unless necessary. ESWK_SwapScreens uses this to program the Shifter registers.
     * @see ESWK_SwapScreens
     */
    extern void * ESWK_physbase;

    /**
     * @brief   swaps screen buffers and activates the new physical screen
     * @details Contents of ESWK_logbase and ESWK_physbase are exchanged. Then the new physical screen address is used for the Shifter to display.
     */
    void ESWK_SwapScreens(void);

    /**
     * @brief clears a 32K Atari ST screen with zeroes
     * @param screenaddr points to start of 32K Atari ST screen in RAM
     */
    void ESWK_ClearScreen(void * screenaddr);

    /**
     * @brief copies a 32K Atari ST screen to a destination screen buffer in RAM
     * @param src_screenaddr points to start of 32K Atari ST source screen in RAM
     * @param dest_screenaddr points to start of 32K Atari ST source screen in RAM
     */
    void ESWK_CopyScreen(void * src_screenaddr, void * dest_screenaddr);

    /**
     * @brief sets a complete 16 color palette in ST format
     * @details A palette consists of 16 consecutive uint16_t values.
     * @param paletteaddr points to palette in RAM
     */
    void ESWK_SetPalette(void * paletteaddr);

#endif
