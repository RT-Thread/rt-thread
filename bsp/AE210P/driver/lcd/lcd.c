#include "hal.h"
#include "lcd/lcd.h"
#include "lcd-info.h"

#ifdef CONFIG_PLAT_AG101P_16MB
	#define LCD_BASE		0x00e10000
#else
	#define LCD_BASE		0x90600000
#endif

#define LCD_TIME0_OFFSET	0x00
#define LCD_TIME1_OFFSET	0x04
#define LCD_TIME2_OFFSET	0x08
#define LCD_BASE_OFFSET		0x10
#define LCD_INT_EN_OFFSET	0x18
#define LCD_CTRL_OFFSET		0x1C
#define LCD_INT_CLR_OFFSET	0x20
#define LCD_INT_MSK_OFFSET	0x24

static pixel_t _drv_lcd_fb[ LCD_PANEL_WIDTH * LCD_PANEL_HEIGHT] __attribute__((aligned (64)));
static pixel_t _drv_lcd_bg[ LCD_PANEL_WIDTH * LCD_PANEL_HEIGHT] __attribute__((aligned (64)));

static pixel_t *drv_lcd_fb = _drv_lcd_fb;
static pixel_t *drv_lcd_bg = _drv_lcd_bg;
extern void nds32_dcache_flush();

void drv_lcd_flip(void)
{
	pixel_t *tmp = drv_lcd_fb;

	drv_lcd_fb = drv_lcd_bg;
	drv_lcd_bg = tmp;

	OUT32(LCD_BASE + LCD_BASE_OFFSET, drv_lcd_fb);
}

pixel_t *drv_lcd_get_fb(void)
{
	return drv_lcd_fb;
}

pixel_t *drv_lcd_get_bg(void)
{
	return drv_lcd_bg;
}

void drv_lcd_get_param(int *width, int *height, int *bpp)
{
	if (width)
		*width = LCD_PANEL_WIDTH;

	if (height)
		*height = LCD_PANEL_HEIGHT;

	if (bpp)
		*bpp = LCD_PANEL_BPP;
}

void drv_lcd_fill_bg(void)
{
	pixel_t *base = drv_lcd_bg;

	int i, j;
	for (i = j = 0; j < LCD_PANEL_HEIGHT; j++) {
		for (i = 0; i < LCD_PANEL_WIDTH; i++) {
#if defined(CONFIG_COLOR_DEPTH16)
			if (i == 0 || i == (LCD_PANEL_WIDTH - 1) || j == 0 || j == (LCD_PANEL_HEIGHT - 1))
				*base++ = 0xFFFFu;
			else
				*base++ = 0x0000u;
#elif defined(CONFIG_COLOR_DEPTH24)
			if (i == 0 || i == (LCD_PANEL_WIDTH - 1) || j == 0 || j == (LCD_PANEL_HEIGHT - 1))
				*base++ = 0x00FFFFFFu;
			else
				*base++ = 0x00000000u;
#else
#error "COLOR DEPTH not supported!"
#endif
		}
	}
}

void drv_lcd_draw_bg(void)
{
	pixel_t *src = drv_lcd_bg;
	pixel_t *dst = drv_lcd_fb;

	int i = 0;
	while (i++ < LCD_PANEL_WIDTH * LCD_PANEL_HEIGHT)
		*dst++ = *src++;
}

static void _drv_lcd_init(void)
{
	OUT32(LCD_BASE + LCD_TIME0_OFFSET, LCD_TIME0);
	OUT32(LCD_BASE + LCD_TIME1_OFFSET, LCD_TIME1);
	OUT32(LCD_BASE + LCD_TIME2_OFFSET, LCD_TIME2);
	OUT32(LCD_BASE + LCD_CTRL_OFFSET, LCD_CTRL);

	OUT32(LCD_BASE + LCD_BASE_OFFSET, drv_lcd_fb);
}

void drv_lcd_draw_rect(int x, int w, int y, int h, int r, int g, int b)
{
	pixel_t *base = drv_lcd_fb;

	int i, j;
	for (i = y; i < y + h; i++)
		for (j = x; j < x + w; j++)
#if defined(CONFIG_COLOR_DEPTH16)
			base[ i * LCD_PANEL_WIDTH + j] = (pixel_t)(((r >> 3)  << 11) | ((g >> 2) << 5) | ((b >> 3)  << 0));
#elif defined(CONFIG_COLOR_DEPTH24)
			base[ i * LCD_PANEL_WIDTH + j] = (pixel_t)((r << 16) | (g << 8) | b);
#endif
	nds32_dcache_flush(); /* undefine CONFIG_CPU_DCACHE_WRITETHROUGH ,flush DCACHE for lcd screen */
}

void drv_lcd_erase_rect(int x, int w, int y, int h)
{
	pixel_t *base = drv_lcd_fb;

	int i, j;
	for (i = y; i < y + h; i++)
		for (j = x; j < x + w; j++)
			base[ i * LCD_PANEL_WIDTH + j] = drv_lcd_bg[ i * LCD_PANEL_WIDTH + j];
}

void draw_blk(int x, int y, int sz, int border, int r, int g, int b)
{
	drv_lcd_draw_rect(x, sz, y, sz, r, g, b);
	drv_lcd_draw_rect(x + border, sz - 2 * border, y + border, sz - 2 * border, r ^ 0xff, g ^ 0xff, b ^ 0xff);
}

int drv_lcd_init(void)
{
	_drv_lcd_init();
	drv_lcd_fill_bg();
	drv_lcd_draw_bg();
	drv_lcd_flip();

	return 0;
}
