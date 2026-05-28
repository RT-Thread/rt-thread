#ifndef _DRV_DISPLAY_H_
#define _DRV_DISPLAY_H_

#include <rtdevice.h>

/* K230D board pins */
#define K230D_LCD_RESET_PIN      3
#define K230D_LCD_BACKLIGHT_PIN  5

#define K230_DISPLAY_FB_ALIGN    4096

#define LCD_CTRL_BACKLIGHT_OFF   0
#define LCD_CTRL_BACKLIGHT_ON    1
#define LCD_CTRL_SET_BG_COLOR    2

int k230_display_init(void);

#endif /* _DRV_DISPLAY_H_ */
