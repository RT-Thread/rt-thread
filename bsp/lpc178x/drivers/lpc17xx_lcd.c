#include <rtthread.h>

#include "LPC177x_8x.h"
#include "lpc177x_8x_pinsel.h"

/* LCD BL P5_4 */
void rt_hw_lcd_init(void)
{
    PINSEL_ConfigPin(5, 4, 0);
	LPC_GPIO5->DIR |= 1<<4;
	LPC_GPIO5->CLR  = 1<<4;
	LPC_GPIO5->SET  = 1<<4;
}
