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
    #include <stdbool.h>

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

    /* --------------------------------------------------------------------------
     * Atari Powerpad reading bitmap: 1 4 7 * 3 6 9 # 2 5 8 0 o p c b a r l d u
     * --------------------------------------------------------------------------
     */

    #define JAGPAD_UP   		0x00000001  /**< ... */
    #define JAGPAD_DOWN 		0x00000002
    #define JAGPAD_LEFT		 	0x00000004
    #define JAGPAD_RIGHT 		0x00000008
    #define JAGPAD_BUT_A   		0x00000010
    #define JAGPAD_BUT_B   		0x00000020
    #define JAGPAD_BUT_C    	0x00000040
    #define JAGPAD_BUT_PAUSE    0x00000080
    #define JAGPAD_BUT_OPTION   0x00000100
    #define JAGPAD_BUT_0        0x00000200
    #define JAGPAD_BUT_8        0x00000400
    #define JAGPAD_BUT_5        0x00000800
    #define JAGPAD_BUT_2        0x00001000
    #define JAGPAD_BUT_HASH     0x00002000
    #define JAGPAD_BUT_9        0x00004000
    #define JAGPAD_BUT_6        0x00008000
    #define JAGPAD_BUT_3        0x00010000
    #define JAGPAD_BUT_STAR     0x00020000
    #define JAGPAD_BUT_7        0x00040000
    #define JAGPAD_BUT_4        0x00080000
    #define JAGPAD_BUT_1        0x00100000

    #define JAGPAD_FIRE         (JAGPAD_BUT_A|JAGPAD_BUT_B|JAGPAD_BUT_C)  /**< any of the buttons A,B or C is pressed */

    /* --------------------------------------------------------------------------
     * IKBD joystick reading bitmap
     * --------------------------------------------------------------------------
     */

    #define IKBD_JOY_UP          0x01
    #define IKBD_JOY_DOWN        0x02
    #define IKBD_JOY_LEFT        0x04
    #define IKBD_JOY_RIGHT       0x08
    #define IKBD_JOY_FIRE        0x80

    /* --------------------------------------------------------------------------
     * mouse reading structure
     * --------------------------------------------------------------------------
     */

    /**
     * @brief mouse state data structure
     */
    typedef struct
    {
        int16_t	 x;      /**< x position */
        int16_t	 y;      /**< y position */
        uint8_t  b;      /**< button state, 1 = left 2 = right, 3 = both buttons pressed */
    } ESWK_MouseState;


    /* --------------------------------------------------------------------------
     * mouse button state values
     * --------------------------------------------------------------------------
     */
    #define IKBD_MOUSE_BUTTON_LEFT  1
    #define IKBD_MOUSE_BUTTON_RIGHT 2
    #define IKBD_MOUSE_BOTH_BUTTONS 3

    /* --------------------------------------------------------------------------
     * key press/release flags
     * --------------------------------------------------------------------------
     */

    /**
     * @brief key press states used by the API
     */
    typedef enum
    {
        ESWK_IKBD_KEY_PRESSED = 0xff,   /**< ... */
        ESWK_IKBD_KEY_UNDEFINED = 0x80, /**< only used internally */
        ESWK_IKBD_KEY_RELEASED = 0      /**< ... */
    } ESWK_KeyPress;

    /* --------------------------------------------------------------------------
     * keyboard scancodes for language agnostic keys
     * --------------------------------------------------------------------------
     */

    #define IKBD_KEY_F1          59
    #define IKBD_KEY_F2          60
    #define IKBD_KEY_F3          61
    #define IKBD_KEY_F4          62
    #define IKBD_KEY_F5          63
    #define IKBD_KEY_F6          64
    #define IKBD_KEY_F7          65
    #define IKBD_KEY_F8          66
    #define IKBD_KEY_F9          67
    #define IKBD_KEY_F10         68

    #define IKBD_KEY_SPACE       0x39
    #define IKBD_KEY_RETURN      0x1c
    #define IKBD_KEY_UP          0x48
    #define IKBD_KEY_DOWN        0x50
    #define IKBD_KEY_LEFT        0x4b
    #define IKBD_KEY_RIGHT       0x4d
    #define IKBD_KEY_BACKSPACE   0x0e
    #define IKBD_KEY_DELETE      0x53
    #define IKBD_KEY_ESC         0x01
    #define IKBD_KEY_TAB         0x0F
    #define IKBD_KEY_CONTROL     0x1d
    #define IKBD_KEY_ALT         0x38
    #define IKBD_KEY_LSHIFT      0x2a
    #define IKBD_KEY_RSHIFT      0x36
    #define IKBD_KEY_INSERT      0x52
    #define IKBD_KEY_HELP        0x62
    #define IKBD_KEY_UNDO        0x61
    #define IKBD_KEY_CLRHOME     0x47
    #define IKBD_KEY_CAPSLOCK    0x3a


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
     * @brief   read a complete 16 color palette in ST format
     * @details A palette consists of 16 consecutive uint16_t values.
     * @param   paletteaddr points to destination in RAM
     */
    void ESWK_GetPalette(void * paletteaddr);

    /**
     * @brief   calculates addresses for screen and palette information for NEOCHROME picture in RAM
     * @details Use this to access the data parts of the picture independently.
     * @param   neopicture_addr points to NEOCHROME picture in RAM
     * @param   dest_screen_data is updated with a RAM address relative to neopicture_addr pointing to screen pixel data
     * @param   dest_palette_data is updated with a RAM address relative to neopicture_addr pointing to palette information
     */
    void ESWK_CalcNEOPictureDataAddr(void *neopicture_addr, void *dest_screen_data, void *dest_palette_data);

    /**
     * @brief   calculates addresses for screen and palette information for DEGAS picture in RAM
     * @details Use this to access the data parts of the picture independently.
     * @param   degaspicture_addr points to DEGAS picture in RAM
     * @param   dest_screen_data is updated with a RAM address relative to neopicture_addr pointing to screen pixel data
     * @param   dest_palette_data is updated with a RAM address relative to neopicture_addr pointing to palette information
     */
    void ESWK_CalcPI1PictureDataAddr(void *degaspicture_addr, void *dest_screen_data, void *dest_palette_data);

    /**
     * @brief display NEOCHROME picture with setting the associated palette
     * @param neopicture_addr points to NEOCHROME file in RAM
     * @param dest points to destionation screen
     */
    void ESWK_ShowNEOPicture(void *neopicture_addr, void *dest);

    /**
     * @brief display DEGAS picture with setting the associated palette
     * @param degaspicture_addr points to DEGAS file in RAM
     * @param dest points to destionation screen
     */
    void ESWK_ShowPI1Picture(void *degaspicture_addr, void *dest);

    /**
     * @brief depack packed DEGAS picture to destination address
     * @param pc1_picture_addr points to packed PC1 image in RAM
     * @param dest points to buffer for DEGAS file in RAM (32034 bytes)
     */
    void ESWK_DepackPC1Picture(void *pc1_picture_addr, void *dest);

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

    /**
     * @brief   read the given Atari Powerpad
     * @details A reading of 0 (no buttons pressed) is returned on machines not supporting the Extended Joystick Ports.
     * @param  joypad_nr denotes the port to read, 0 = A, 1 = B
     * @return bitvector with JAGPAD... encoded bitmasks
     */
    uint32_t ESWK_ReadJagpad(uint8_t joypad_nr);

    /**
     * @brief checks if the kernel detected Extended Joystick Ports
     */
    bool ESWK_HasJagpad(void);

    /**
     * @brief install optional IKBD handling to read keyboard, mouse and joystick
     */
    void ESWK_InstallIKBD(void);

    /**
     * @brief uninstall IKBD handling routines
     */
    void ESWK_UninstallIKBD(void);

    /**
     * @brief   deactivate mouse position reporting
     * @details This activates joystick 0 reporting.
     */
    void ESWK_IKBD_MouseOff(void);

    /**
     * @brief activate mouse position reporting
     * @details This deactivates joystick 0 reporting.
     */
    void ESWK_IKBD_MouseOn(void);

    /**
     * @brief set current mouse position and define the screen size
     * @param x position of mouse in pixels
     * @param y position of mouse in pixels
     * @param w width of screen in pixels
     * @param h height of screen in pixels
     */
    void ESWK_IKBD_SetMouseOrigin(int16_t x, int16_t y, uint16_t w, uint16_t h);

    /**
     * @brief allows to configure the scaling of relative mouse movement
     * @param new_threshold in 1/128 per digit (e.q. 128 = 100%)
     */
    void ESWK_IKBD_SetMouseThreshold(uint8_t new_threshold);

    /**
     * @brief reads the accumulated mouse packets and update the mouse position
     */
    void ESWK_IKBD_ReadMouse(ESWK_MouseState * mouseData);

    /**
     * @brief flushes all pending keyboard and joystick events
     */
    void ESWK_IKBD_Flush(void);

    /**
     * @brief read and debounce a key by scancode
     */
    ESWK_KeyPress ESWK_IKBD_ReadKey(uint8_t scancode);

    /**
     * @brief read key press state by scancode
     */
    ESWK_KeyPress ESWK_IKBD_IsKeyPressed(uint8_t scancode);

    /**
     * @brief  read given joystick state
     * @param  portnr indicated the joystick port queried
     * @return joystick reading composed of IKBD_JOY_... bits
     */
    uint8_t ESWK_IKBD_ReadJoystick(uint8_t portnr);

    /**
     * @brief   map Atari Powerpad reading to IKBD compatible joystick reading
     * @details Any powerpad fire button maps to the joystick button
     * @param   jagpad_reading composed of JAGPAD_... bits
     * @return  joystick reading composed of IKBD_JOY_... bits
     */
    uint8_t ESWK_MapJagpadToJoystick(uint32_t jagpad_reading);


#endif
