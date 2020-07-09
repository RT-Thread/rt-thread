#ifndef DRV_CLCD_H__
#define DRV_CLCD_H__

#include <rtthread.h>

#ifndef BSP_LCD_WIDTH
#define BSP_LCD_WIDTH   640
#endif

#ifndef BSP_LCD_HEIGHT
#define BSP_LCD_HEIGHT  480
#endif

int drv_clcd_hw_init(void);

#endif
