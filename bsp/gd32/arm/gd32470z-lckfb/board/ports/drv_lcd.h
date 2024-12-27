#ifndef GD32F450Z_LCD_H
#define GD32F450Z_LCD_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#ifdef BSP_USING_SDRAM
#include <sdram_port.h>
#endif /* BSP_USING_SDRAM */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define LCD_WIDTH             800
#define LCD_HEIGHT            480
#define LCD_FB_BYTE_PER_PIXEL 1

#define HORIZONTAL_SYNCHRONOUS_PULSE 10
#define HORIZONTAL_BACK_PORCH        150
#define ACTIVE_WIDTH                 800
#define HORIZONTAL_FRONT_PORCH       15

#define VERTICAL_SYNCHRONOUS_PULSE 10
#define VERTICAL_BACK_PORCH        140
#define ACTIVE_HEIGHT              480
#define VERTICAL_FRONT_PORCH       40


#define LCD_FRAME_BUF_ADDR 0XC0000000

//画笔颜色
#define WHITE   0xFFFF
#define BLACK   0x0000
#define BLUE    0x001F
#define BRED    0XF81F
#define GRED    0XFFE0
#define GBLUE   0X07FF
#define RED     0xF800
#define MAGENTA 0xF81F
#define GREEN   0x07E0
#define CYAN    0x7FFF
#define YELLOW  0xFFE0
#define BROWN   0XBC40 //棕色
#define BRRED   0XFC07 //棕红色
#define GRAY    0X8430 //灰色
//GUI颜色

#define DARKBLUE  0X01CF //深蓝色
#define LIGHTBLUE 0X7D7C //浅蓝色
#define GRAYBLUE  0X5458 //灰蓝色
//以上三色为PANEL的颜色

#define LIGHTGREEN 0X841F //浅绿色
//#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY 0XC618     //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE 0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE    0X2B12 //浅棕蓝色(选择条目的反色)


#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
// Keil MDK 编译器
extern uint16_t ltdc_lcd_framebuf0[800][480] __attribute__((at(LCD_FRAME_BUF_ADDR)));
#elif defined(__GNUC__)
// GCC 编译器 (如 RT-Thread 使用的 GCC)
extern uint16_t ltdc_lcd_framebuf0[10][10];
#endif


/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


void lcd_disp_config(void);

#if defined(__cplusplus)
}
#endif

#endif /* GD32F450Z_LCD_H */
