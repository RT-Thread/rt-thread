#ifndef __LCD_H__
#define __LCD_H__

#include <inttypes.h>
#include "lcd-info.h"

#if defined(CONFIG_COLOR_DEPTH16)
	typedef uint16_t pixel_t;
#elif defined(CONFIG_COLOR_DEPTH24)
	typedef uint32_t pixel_t;
#else
	#error "Unsupported COLOR_DEPTH!"
	typedef int pixel_t;
#endif

extern void	drv_lcd_flip(void);
extern pixel_t *drv_lcd_get_fb(void);
extern pixel_t *drv_lcd_get_bg(void);
extern void	drv_lcd_get_param(int *width, int *height, int *bpp);
extern void	drv_lcd_fill_bg(void);
extern void	drv_lcd_draw_bg(void);
extern void	drv_lcd_draw_rect(int x, int w, int y, int h, int r, int g, int b);
extern void	drv_lcd_erase_rect(int x, int w, int y, int h);
extern void	draw_blk(int x, int y, int sz, int border, int r, int g, int b);
extern int	drv_lcd_init(void);

extern void	draw_font(int x, int y, int ascii);

#endif /* __LCD_H__ */
