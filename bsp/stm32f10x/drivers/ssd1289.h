#ifndef SSD1289_H_INCLUDED
#define SSD1289_H_INCLUDED

#include <rtthread.h>

// Compatible list:
// ssd1289

/* LCD color */
#define White            0xFFFF
#define Black            0x0000
#define Grey             0xF7DE
#define Blue             0x001F
#define Blue2            0x051F
#define Red              0xF800
#define Magenta          0xF81F
#define Green            0x07E0
#define Cyan             0x7FFF
#define Yellow           0xFFE0

/*---------------------- Graphic LCD size definitions ------------------------*/
#define LCD_WIDTH       240                 /* Screen Width (in pixels)           */
#define LCD_HEIGHT      320                 /* Screen Hight (in pixels)           */
#define BPP             16                  /* Bits per pixel                     */
#define BYPP            ((BPP+7)/8)         /* Bytes per pixel                    */

void ssd1289_init(void);

//#define _ILI_REVERSE_DIRECTION_

rt_size_t lcd_ssd1289_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size);
rt_size_t lcd_ssd1289_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size);

#endif // SSD1289_H_INCLUDED
