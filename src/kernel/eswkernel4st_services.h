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

    /* --------------------------------------------------------------------------
     * cookie tag values
     * --------------------------------------------------------------------------
     */

    #define COOKIE_CPU      0x5f435055UL   /**< cookie tag for _CPU cookie */
    #define COOKIE_VDO      0x5f56444fUL   /**< cookie tag for _VDO cookie */
    #define COOKIE_FPU      0x5f465055UL   /**< cookie tag for _FPU cookie */
    #define COOKIE_FDC      0x5f464443UL   /**< cookie tag for _FDC cookie */
    #define COOKIE_SND      0x5f534e44UL   /**< cookie tag for _SND cookie */
    #define COOKIE_MCH      0x5f4d4348UL   /**< cookie tag for _MCH cookie */
    #define COOKIE_SWI      0x5f535749UL   /**< cookie tag for _SWI cookie */
    #define COOKIE_FRB      0x5f465242UL   /**< cookie tag for _FRB cookie */
    #define COOKIE_FLK      0x5f464c4bUL   /**< cookie tag for _FLK cookie */
    #define COOKIE_NET      0x5f4e4554UL   /**< cookie tag for _NET cookie */
    #define COOKIE_IDT      0x5f494454UL   /**< cookie tag for _IDT cookie */
    #define COOKIE_AKP      0x5f414b50UL   /**< cookie tag for _AKP cookie */

    /* --------------------------------------------------------------------------
     * values of MCH cookie
     * --------------------------------------------------------------------------
     */

    #define MCH_NOHARD  0xffffffffUL  /**< No ST-compatible hardware */
    #define MCH_ST      0x00000000UL  /**< STF class machine */
    #define MCH_STE     0x00010000UL  /**< 1040STE class machine with extended joystick ports */
    #define MCH_MSTE    0x00010010UL  /**< Mega STE clss machine without extended joystick ports */
    #define MCH_TT      0x00020000UL  /**< TT class machine */
    #define MCH_FALCON  0x00030000UL  /**< Falcon class machine */
    #define MCH_MILAN_C 0x00040000UL  /**< Milan */
    #define MCH_ARANYM  0x00050000UL  /**< Aranym or GEM compatible clone */

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

    /**
     * @brief   set function pointer to call from Timer C in 50hz intervals
     * @details If NULL is given, no routine is executed.
     * @param   userrout is a function pointer with void ...(void) prototype
     */
    void ESWK_Set50HzRoutine(void (*userrout)(void));

    /**
     * @brief   set function pointer to call from Timer C in 200hz intervals
     * @details If NULL is given, no routine is executed.
     * @param   userrout is a function pointer with void ...(void) prototype
     */
    void ESWK_Set200HzRoutine(void (*userrout)(void));

    /**
     * @brief   set function pointer to call from VBL interrupt
     * @details If NULL is given, no routine is executed.
     * @param   userrout is a function pointer with void ...(void) prototype
     */
    void ESWK_SetVBLRoutine(void (*userrout)(void));

    /**
     * @brief     get cookie from TOS cookie jar
     * @param     cookietag denotes the desired cookie such as "_MCH", use COOKIE_... macros
     * @return    value of cookie if found or 0
     * @attention cookies with valid content 0 cannot be distinguished if the jar is missing
     */
    uint32_t ESWK_GetCookie(uint32_t cookietag);

    /**
     * @brief   get machine type via the cookie jar
     * @details The _MCH cookie is returned. In case of missing cookie jar, running on STF class machine is assumed.
     * @return  value of _MCH cookie, see MCH_... values
     */
    uint32_t ESWK_GetMachine(void);

#endif
