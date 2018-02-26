#include <stdint.h>
#include <osbind.h>

#include "eswkernel4st.h"
#include "eswkernel4st_services.h"

#include "internals.h"

int main(void)
{
    static uint16_t my_palette[] = { 0x0031, 0x0000, 0x0000, 0x0000,
                                     0x0000, 0x0000, 0x0000, 0x0000,
                                     0x0000, 0x0000, 0x0000, 0x0000,
                                     0x0000, 0x0000, 0x0000, 0x0FFF
                                   };

    ESWK_int_InitScreens();

    ESWK_SetPalette(my_palette);

	(void)Cconws( "press any key\n");

	Cconin();

    return 0;
}

