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

#include "eswkernel4st_services.h"

/* --------------------------------------------------------------------------
 * local definitions
 * --------------------------------------------------------------------------
 */

/**
 * @brief internal data structure for header of NEOCHROME picture
 */
typedef struct
{
    uint32_t unused1;                 /**< ... */
    uint16_t palette[16];             /**< ... */
    uint32_t unused2[23];             /**< ... */
    uint16_t first_screen_data_word;  /**< ... */
} NEO_header;

/**
 * @brief internal data structure for header of DEGAS picture
 */
typedef struct
{
    uint16_t unused1;                 /**< ... */
    uint16_t palette[16];             /**< ... */
    uint16_t first_screen_data_word;  /**< ... */
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

/**
 * @brief   calculates addresses for screen and palette information for NEOCHROME picture in RAM
 * @details Use this to access the data parts of the picture independently.
 * @param   neopicture_addr points to NEOCHROME picture in RAM
 * @param   dest_screen_data is updated with a RAM address relative to neopicture_addr pointing to screen pixel data
 * @param   dest_palette_data is updated with a RAM address relative to neopicture_addr pointing to palette information
 */
void ESWK_CalcNEOPictureDataAddr(void *neopicture_addr, void *dest_screen_data, void *dest_palette_data)
{
    /* decode file header and calculate addresses: */
    NEO_header * header = (NEO_header *)neopicture_addr;
    dest_screen_data = &(header->first_screen_data_word);
    dest_palette_data = &(header->palette[0]);

    /* parameters are updated butnot directly used: */
    (void)dest_screen_data;
    (void)dest_palette_data;

    return;
}

/**
 * @brief   calculates addresses for screen and palette information for DEGAS picture in RAM
 * @details Use this to access the data parts of the picture independently.
 * @param   degaspicture_addr points to DEGAS picture in RAM
 * @param   dest_screen_data is updated with a RAM address relative to neopicture_addr pointing to screen pixel data
 * @param   dest_palette_data is updated with a RAM address relative to neopicture_addr pointing to palette information
 */
void ESWK_CalcPI1PictureDataAddr(void *degaspicture_addr, void *dest_screen_data, void *dest_palette_data)
{
    /* decode file header and calculate addresses: */
    NEO_header * header = (NEO_header *)degaspicture_addr;
    dest_screen_data = &(header->first_screen_data_word);
    dest_palette_data = &(header->palette[0]);

    /* parameters are updated butnot directly used: */
    (void)dest_screen_data;
    (void)dest_palette_data;

    return;
}

/**
 * @brief display NEOCHROME picture with setting the associated palette
 * @param neopicture_addr points to NEOCHROME file in RAM
 * @param dest points to destionation screen
 */
void ESWK_ShowNEOPicture(void *neopicture_addr, void *dest)
{
    void * ptr_data = NULL;
    void * ptr_pal = NULL;
    ESWK_CalcNEOPictureDataAddr(neopicture_addr, ptr_data, ptr_pal);
    ESWK_SetPalette(ptr_pal);
    ESWK_CopyScreen(ptr_data, dest);

    return;
}

/**
 * @brief display DEGAS picture with setting the associated palette
 * @param degaspicture_addr points to DEGAS file in RAM
 * @param dest points to destionation screen
 */
void ESWK_ShowPI1Picture(void *degaspicture_addr, void *dest)
{
    DEGAS_header * header = (DEGAS_header *)degaspicture_addr;
    ESWK_SetPalette(&(header->palette[0]));
    ESWK_CopyScreen((void *)&(header->first_screen_data_word), dest);

    return;
}

