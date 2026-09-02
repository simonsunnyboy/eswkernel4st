/**
 * Entertainment Software Kernel for Atari ST
 * (c) 2016/18 by Matthias Arndt / ASM Software
 *
 * The MIT License applies to this software. Refer to the file COPYING for
 * details.
 *
 * @file  picture.c
 * @brief implementation of picture format handling system
 */

#include <osbind.h>
#include <stdint.h>
#include <stdlib.h>

#include "eswkernel4st/eswkernel4st_services.h"

/* --------------------------------------------------------------------------
 * local definitions
 * --------------------------------------------------------------------------
 */

/**
 * @brief internal data structure for header of NEOCHROME picture
 * @details The header contains 128 bytes before the first data byte.
 */
typedef struct
{
    uint32_t unused1;                 /**< unused meta information */
    uint16_t palette[16];             /**< ST compatible palette data */
    uint32_t unused2[23];             /**< unused data for color animation */
    uint16_t first_screen_data_word;  /**< first word of screen data */
} NEO_header;

/**
 * @brief internal data structure for header of DEGAS picture
 * @details The header contains 34 bytes before the first data byte.
 */
typedef struct
{
    uint16_t unused1;                 /**< unused meta information */
    uint16_t palette[16];             /**< ST compatible palette data */
    uint16_t first_screen_data_word;  /**< first word of screen data */
} DEGAS_header;

/* --------------------------------------------------------------------------
 * local variables
 * --------------------------------------------------------------------------
 */

/* --------------------------------------------------------------------------
 * kernel internal functions
 * --------------------------------------------------------------------------
 */


/* --------------------------------------------------------------------------
 * public user accessible functions
 * --------------------------------------------------------------------------
 */

void ESWK_CalcNEOPictureDataAddr(void *neopicture_addr, PictureInformation * picinfo)
{
    /* decode file header and calculate addresses: */
    NEO_header * header = (NEO_header *)neopicture_addr;
    picinfo->data = (void *)&(header->first_screen_data_word);
    picinfo->palette = (void *)&(header->palette[0]);

    return;
}

void ESWK_CalcPI1PictureDataAddr(void *degaspicture_addr,  PictureInformation * picinfo)
{
    /* decode file header and calculate addresses: */
    DEGAS_header * header = (DEGAS_header *)degaspicture_addr;
    picinfo->data = (void *)&(header->first_screen_data_word);
    picinfo->palette = (void *)&(header->palette[0]);

    return;
}

void ESWK_ShowNEOPicture(void *neopicture_addr, void *dest)
{
    PictureInformation current;
    ESWK_CalcNEOPictureDataAddr(neopicture_addr, &current);
    ESWK_SetPalette(current.palette);
    ESWK_CopyScreen(current.data, dest);

    return;
}

void ESWK_ShowPI1Picture(void *degaspicture_addr, void *dest)
{
    PictureInformation current;
    ESWK_CalcPI1PictureDataAddr(degaspicture_addr, &current);
    ESWK_SetPalette(current.palette);
    ESWK_CopyScreen(current.data, dest);

    return;
}

