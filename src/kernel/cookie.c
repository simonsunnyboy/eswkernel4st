/**
 * Entertainment Software Kernel for Atari ST
 * (c) 2016/18 by Matthias Arndt / ASM Software
 *
 * The MIT License applies to this software. Refer to the file COPYING for
 * details.
 *
 * @file  cookie.c
 * @brief access to cookie jar if available
 */

#include <stdint.h>
#include "eswkernel4st_services.h"

/* --------------------------------------------------------------------------
 * local definitions
 * --------------------------------------------------------------------------
 */

#define COOKIEJAR_ADDRESS 0x5A0U   /**< TOS cookie jar address in RAM */

/* --------------------------------------------------------------------------
 * public user accessible functions
 * --------------------------------------------------------------------------
 */

uint32_t ESWK_GetCookie(uint32_t cookietag)
{
    uint32_t cookie_val = 0;
	uint32_t *cptr = *(uint32_t**)COOKIEJAR_ADDRESS;  /* get pointer to cookiejar */

	if(cptr != 0)
	{
		/* if we have a cookie jar: */
        while((*cptr != cookietag)&&(*cptr != 0))
		{
			/* loop through all cookies */
			cptr = cptr + 2;
		}
        if(*cptr == cookietag)
		{
			/* we found our cookie - return its value */
            cookie_val = (*(cptr+1));
		}
		else
		{
			/* cookie not found - return empty cookie */
		}
	}
	else
	{
		/* no cookie jar available */
	}

    return cookie_val;
}

uint32_t ESWK_GetMachine(void)
{
    return ESWK_GetCookie(COOKIE_MCH);
}
