/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-05-23     godmial      Refactor to conform to RT-Thread coding style.
 */

#include <board.h>
#include "gd32f4xx.h"
#include "gd32f4xx_tli.h"
#include "drv_lcd.h"
#include "font.h"


#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
/* Keil MDK Compiler */
uint16_t ltdc_lcd_framebuf0[800][480] __attribute__((at(LCD_FRAME_BUF_ADDR)));
#elif defined(__GNUC__)
/* GCC Compiler (used by RT-Thread) */
uint16_t ltdc_lcd_framebuf0[10][10];
#endif

static void tli_gpio_config(void);
static void tli_config(void);
static void ipa_config(void);
static void lcd_disp_en_config(void);
static void lcd_disp_off(void);
static void lcd_disp_on(void);


/**
 * @brief    Configure and initialize the LCD display.
 *
 * @note     This function enables display power, initializes TLI GPIO and IPA,
 *           and sets up TLI and its layer configuration.
 *
 * @param    None
 *
 * @return   None
 *
 * @warning  Should be called during system initialization phase.
 */
void lcd_disp_config(void)
{
    lcd_disp_en_config();
    lcd_disp_off();

    /* configure the GPIO of TLI */
    tli_gpio_config();
    lcd_disp_on();

    tli_config();
    tli_layer_enable(LAYER0);
    tli_reload_config(TLI_FRAME_BLANK_RELOAD_EN);
    tli_enable();
    ipa_config();
}

/**
 * @brief    Initialize the TLI peripheral and layer configuration.
 *
 * @note     This function sets up the TLI clock, background color, timing parameters,
 *           and layer 0 settings including framebuffer and blending configuration.
 *
 * @param    None
 *
 * @return   None
 *
 * @warning  Must be called after clock and GPIO initialization.
 */
static void tli_config(void)
{
    tli_parameter_struct       tli_init_struct;
    tli_layer_parameter_struct tli_layer_init_struct;

    rcu_periph_clock_enable(RCU_TLI);
    tli_gpio_config();
    /* configure PLLSAI to generate TLI clock */
    // if(ERROR == rcu_pllsai_config(216, 2, 3)){
    if (ERROR == rcu_pllsai_config(192, 2, 3))
    {
        while (1);
    }
    rcu_tli_clock_div_config(RCU_PLLSAIR_DIV2);

    rcu_osci_on(RCU_PLLSAI_CK);

    if (ERROR == rcu_osci_stab_wait(RCU_PLLSAI_CK))
    {
        while (1);
    }

    /* configure TLI parameter struct */
    tli_init_struct.signalpolarity_hs      = TLI_HSYN_ACTLIVE_LOW;
    tli_init_struct.signalpolarity_vs      = TLI_VSYN_ACTLIVE_LOW;
    tli_init_struct.signalpolarity_de      = TLI_DE_ACTLIVE_LOW;
    tli_init_struct.signalpolarity_pixelck = TLI_PIXEL_CLOCK_TLI;
    /* LCD display timing configuration */
    tli_init_struct.synpsz_hpsz   = HORIZONTAL_SYNCHRONOUS_PULSE - 1;
    tli_init_struct.synpsz_vpsz   = VERTICAL_SYNCHRONOUS_PULSE - 1;
    tli_init_struct.backpsz_hbpsz = HORIZONTAL_SYNCHRONOUS_PULSE + HORIZONTAL_BACK_PORCH - 1;
    tli_init_struct.backpsz_vbpsz = VERTICAL_SYNCHRONOUS_PULSE + VERTICAL_BACK_PORCH - 1;
    tli_init_struct.activesz_hasz = HORIZONTAL_SYNCHRONOUS_PULSE + HORIZONTAL_BACK_PORCH + ACTIVE_WIDTH - 1;
    tli_init_struct.activesz_vasz = VERTICAL_SYNCHRONOUS_PULSE + VERTICAL_BACK_PORCH + ACTIVE_HEIGHT - 1;
    tli_init_struct.totalsz_htsz  = HORIZONTAL_SYNCHRONOUS_PULSE + HORIZONTAL_BACK_PORCH + ACTIVE_WIDTH + HORIZONTAL_FRONT_PORCH - 1;
    tli_init_struct.totalsz_vtsz  = VERTICAL_SYNCHRONOUS_PULSE + VERTICAL_BACK_PORCH + ACTIVE_HEIGHT + VERTICAL_FRONT_PORCH - 1;
    /* configure LCD background R,G,B values */
    tli_init_struct.backcolor_red   = 0xFF;
    tli_init_struct.backcolor_green = 0xFF;
    tli_init_struct.backcolor_blue  = 0xFF;
    tli_init(&tli_init_struct);

#if 1
    /* TLI layer0 configuration */
    /* TLI window size configuration */
    tli_layer_init_struct.layer_window_leftpos   = HORIZONTAL_SYNCHRONOUS_PULSE + HORIZONTAL_BACK_PORCH;
    tli_layer_init_struct.layer_window_rightpos  = (ACTIVE_WIDTH + HORIZONTAL_SYNCHRONOUS_PULSE + HORIZONTAL_BACK_PORCH - 1);
    tli_layer_init_struct.layer_window_toppos    = VERTICAL_SYNCHRONOUS_PULSE + VERTICAL_BACK_PORCH;
    tli_layer_init_struct.layer_window_bottompos = (ACTIVE_HEIGHT + VERTICAL_SYNCHRONOUS_PULSE + VERTICAL_BACK_PORCH - 1);
    /* TLI window pixel format configuration */
    tli_layer_init_struct.layer_ppf = LAYER_PPF_RGB565;
    /* TLI window specified alpha configuration */
    tli_layer_init_struct.layer_sa = 255;
    /* TLI layer default alpha R,G,B value configuration */
    tli_layer_init_struct.layer_default_blue  = 0x00;
    tli_layer_init_struct.layer_default_green = 0x00;
    tli_layer_init_struct.layer_default_red   = 0x00;
    tli_layer_init_struct.layer_default_alpha = 0x00;
    /* TLI window blend configuration */
    tli_layer_init_struct.layer_acf1 = LAYER_ACF1_SA;
    tli_layer_init_struct.layer_acf2 = LAYER_ACF2_SA;
    /* TLI layer frame buffer base address configuration */
    tli_layer_init_struct.layer_frame_bufaddr           = (uint32_t)ltdc_lcd_framebuf0;
    tli_layer_init_struct.layer_frame_line_length       = ((ACTIVE_WIDTH * 2) + 3);
    tli_layer_init_struct.layer_frame_buf_stride_offset = (ACTIVE_WIDTH * 2);
    tli_layer_init_struct.layer_frame_total_line_number = ACTIVE_HEIGHT;
    tli_layer_init(LAYER0, &tli_layer_init_struct);
    tli_dither_config(TLI_DITHER_ENABLE);
#endif
}

/**
 * @brief    Initialize the IPA peripheral.
 *
 * @note     Enable clock and interrupt for the IPA module.
 *
 * @param    None
 *
 * @return   None
 */
static void ipa_config(void)
{
    rcu_periph_clock_enable(RCU_IPA);
    nvic_irq_enable(IPA_IRQn, 0, 2);
}

/**
 * @brief    Configure the GPIO pins used for TLI display.
 *
 * @note     Includes alternate function mapping and output mode setup
 *           for RGB and sync signals.
 *
 * @param    None
 *
 * @return   None
 */
static void tli_gpio_config(void)
{
    /* enable the periphral clock */
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_GPIOF);
    rcu_periph_clock_enable(RCU_GPIOG);

    /* configure HSYNC(PC6), VSYNC(PA4), PCLK(PG7), DE(PF10) */
    /* configure LCD_R7(PG6), LCD_R6(PA8), LCD_R5(PA12), LCD_R4(PA11), LCD_R3(PB0),
                 LCD_G7(PD3), LCD_G6(PC7), LCD_G5(PB11), LCD_G4(PB10), LCD_G3(PG10), LCD_G2(PA6),
                 LCD_B7(PB9), LCD_B6(PB8), LCD_B5(PA3), LCD_B4(PG12), LCD_B3(PG11) */
    gpio_af_set(GPIOA, GPIO_AF_14, GPIO_PIN_3);
    gpio_af_set(GPIOA, GPIO_AF_14, GPIO_PIN_4);
    gpio_af_set(GPIOA, GPIO_AF_14, GPIO_PIN_6);
    gpio_af_set(GPIOA, GPIO_AF_14, GPIO_PIN_8);
    gpio_af_set(GPIOA, GPIO_AF_14, GPIO_PIN_11);
    gpio_af_set(GPIOA, GPIO_AF_14, GPIO_PIN_12);

    gpio_af_set(GPIOB, GPIO_AF_9, GPIO_PIN_0);
    gpio_af_set(GPIOB, GPIO_AF_14, GPIO_PIN_8);
    gpio_af_set(GPIOB, GPIO_AF_14, GPIO_PIN_9);
    gpio_af_set(GPIOB, GPIO_AF_14, GPIO_PIN_10);
    gpio_af_set(GPIOB, GPIO_AF_14, GPIO_PIN_11);

    gpio_af_set(GPIOC, GPIO_AF_14, GPIO_PIN_6);
    gpio_af_set(GPIOC, GPIO_AF_14, GPIO_PIN_7);

    gpio_af_set(GPIOD, GPIO_AF_14, GPIO_PIN_3);

    gpio_af_set(GPIOF, GPIO_AF_14, GPIO_PIN_10);

    gpio_af_set(GPIOG, GPIO_AF_14, GPIO_PIN_6);
    gpio_af_set(GPIOG, GPIO_AF_14, GPIO_PIN_7);
    gpio_af_set(GPIOG, GPIO_AF_9, GPIO_PIN_10);
    gpio_af_set(GPIOG, GPIO_AF_14, GPIO_PIN_11);
    gpio_af_set(GPIOG, GPIO_AF_9, GPIO_PIN_12);

    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_8 | GPIO_PIN_11 | GPIO_PIN_12);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_8 | GPIO_PIN_11 | GPIO_PIN_12);

    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_0 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11);

    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_6 | GPIO_PIN_7);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6 | GPIO_PIN_7);

    gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3);
    gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_3);

    gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_10);
    gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

    gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12);
}

/**
 * @brief    Configure the GPIO pin for DISP enable control.
 *
 * @note     This function enables the clock for GPIOD and sets up pin 13
 *           as push-pull output to control the display on/off signal.
 *
 * @param    None
 *
 * @return   None
 *
 * @warning  Must be called before attempting to control the LCD display.
 */
static void lcd_disp_en_config(void)
{
    /* enable the periphral clock */
    rcu_periph_clock_enable(RCU_GPIOD);
    gpio_mode_set(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_13);
    gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);
}

/**
 * @brief    Turn off the LCD display by resetting the DISP GPIO.
 *
 * @note     This function clears the DISP control pin to disable
 *           the LCD backlight or power depending on hardware design.
 *
 * @param    None
 *
 * @return   None
 *
 * @warning  Only valid if the DISP GPIO has been previously configured.
 */
static void lcd_disp_off(void)
{
    gpio_bit_reset(GPIOD, GPIO_PIN_13);
}

/**
 * @brief    Turn on the LCD display by setting the DISP GPIO.
 *
 * @note     This function sets the DISP control pin to enable
 *           the LCD backlight or power depending on hardware design.
 *
 * @param    None
 *
 * @return   None
 *
 * @warning  Only valid if the DISP GPIO has been previously configured.
 */
static void lcd_disp_on(void)
{
    gpio_bit_set(GPIOD, GPIO_PIN_13);
}


/**
 * @brief    Draw a pixel on the LCD at specified coordinates.
 *
 * @note     This function writes a color value directly to the framebuffer.
 *           Coordinates must be within the valid LCD dimensions.
 *
 * @param    x      Horizontal coordinate of the pixel.
 * @param    y      Vertical coordinate of the pixel.
 * @param    color  Color of the pixel in RGB565 format.
 *
 * @return   None
 */
void tli_draw_point(uint16_t x, uint16_t y, uint16_t color)
{
    *(ltdc_lcd_framebuf0[0] + (LCD_WIDTH * y + x)) = color;
}

/**
 * @brief    Draw a straight line between two points.
 *
 * @note     Uses Bresenham's line drawing algorithm to connect two points.
 *           Coordinates should be within LCD bounds.
 *
 * @param    sx      Start point X coordinate.
 * @param    sy      Start point Y coordinate.
 * @param    ex      End point X coordinate.
 * @param    ey      End point Y coordinate.
 * @param    color   Line color in RGB565 format.
 *
 * @return   None
 */
void tli_draw_line(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color)
{
    uint16_t t;
    int      xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int      incx, incy, uRow, uCol;

    delta_x = ex - sx;
    delta_y = ey - sy;
    uRow    = sx;
    uCol    = sy;
    if (delta_x > 0)
        incx = 1;
    else if (delta_x == 0)
        incx = 0;
    else
    {
        incx    = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)
        incy = 1;
    else if (delta_y == 0)
        incy = 0;
    else
    {
        incy    = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)
        distance = delta_x;
    else
        distance = delta_y;
    for (t = 0; t <= distance + 1; t++)
    {
        tli_draw_point(uRow, uCol, color);
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}
/**
 * @brief    Draw a rectangle on the screen, optionally filled.
 *
 * @note     The rectangle is defined by top-left and bottom-right corners.
 *           If fill is set to 1, the rectangle will be filled with the color.
 *
 * @param    sx      X coordinate of the top-left corner.
 * @param    sy      Y coordinate of the top-left corner.
 * @param    ex      X coordinate of the bottom-right corner.
 * @param    ey      Y coordinate of the bottom-right corner.
 * @param    color   Color of the rectangle in RGB565 format.
 * @param    fill    Fill mode: 1 = filled, 0 = only borders.
 *
 * @return   None
 */
void tli_draw_rectangle(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color, uint16_t fill)
{
    int i = 0, j = 0;
    if (fill)
    {
        for (i = sx; i < ex; i++)
        {
            for (j = sy; j < ey; j++)
            {
                tli_draw_point(i, j, color);
            }
        }
    }
    else
    {
        tli_draw_line(sx, sy, ex, sy, color);
        tli_draw_line(sx, sy, sx, ey, color);
        tli_draw_line(sx, ey, ex, ey, color);
        tli_draw_line(ex, sy, ex, ey, color);
    }
}

/**
 * @brief    Draw eight symmetric points of a circle.
 *
 * @note     This function is used internally to draw points in all eight
 *           symmetrical positions around a circle center.
 *
 * @param    xc      X coordinate of the circle center.
 * @param    yc      Y coordinate of the circle center.
 * @param    x       Relative X offset from the center.
 * @param    y       Relative Y offset from the center.
 * @param    c       Color of the point in RGB565 format.
 *
 * @return   None
 */

static void _draw_circle_8(int xc, int yc, int x, int y, uint16_t c)
{
    tli_draw_point(xc + x, yc + y, c);

    tli_draw_point(xc - x, yc + y, c);

    tli_draw_point(xc + x, yc - y, c);

    tli_draw_point(xc - x, yc - y, c);

    tli_draw_point(xc + y, yc + x, c);

    tli_draw_point(xc - y, yc + x, c);

    tli_draw_point(xc + y, yc - x, c);

    tli_draw_point(xc - y, yc - x, c);
}

/**
 * @brief    Draw a circle on the screen with optional fill.
 *
 * @note     Uses the midpoint circle algorithm to render the circle.
 *           When fill is enabled, the circle is drawn as a filled disk.
 *
 * @param    xc      X coordinate of the circle center.
 * @param    yc      Y coordinate of the circle center.
 * @param    c       Color of the circle in RGB565 format.
 * @param    r       Radius of the circle.
 * @param    fill    Fill mode: 1 = filled, 0 = outline only.
 *
 * @return   None
 */
void tli_draw_circle(int xc, int yc, uint16_t c, int r, int fill)
{
    int x = 0, y = r, yi, d;

    d = 3 - 2 * r;

    if (fill)
    {
        while (x <= y)
        {
            for (yi = x; yi <= y; yi++)
                _draw_circle_8(xc, yc, x, yi, c);

            if (d < 0)
            {
                d = d + 4 * x + 6;
            }
            else
            {
                d = d + 4 * (x - y) + 10;
                y--;
            }
            x++;
        }
    }
    else
    {
        while (x <= y)
        {
            _draw_circle_8(xc, yc, x, y, c);
            if (d < 0)
            {
                d = d + 4 * x + 6;
            }
            else
            {
                d = d + 4 * (x - y) + 10;
                y--;
            }
            x++;
        }
    }
}

/**
 * @brief    Swap the values of two 16-bit unsigned integers.
 *
 * @note     This utility function is used internally to simplify sorting
 *           or reordering logic, such as coordinate alignment.
 *
 * @param    a   Pointer to the first variable.
 * @param    b   Pointer to the second variable.
 *
 * @return   None
 */
static void _swap(uint16_t *a, uint16_t *b)
{
    uint16_t tmp;
    tmp = *a;
    *a  = *b;
    *b  = tmp;
}

/**
 * @brief    Draw a triangle with optional fill.
 *
 * @note     The triangle is defined by three vertex points. When fill is set,
 *           it is rendered as a filled triangle using scan-line rasterization.
 *
 * @param    x0      X coordinate of the first vertex.
 * @param    y0      Y coordinate of the first vertex.
 * @param    x1      X coordinate of the second vertex (typically the top).
 * @param    y1      Y coordinate of the second vertex.
 * @param    x2      X coordinate of the third vertex.
 * @param    y2      Y coordinate of the third vertex.
 * @param    color   Color of the triangle in RGB565 format.
 * @param    fill    Fill mode: 1 = filled, 0 = outline only.
 *
 * @return   None
 */
void tli_draw_triangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color, uint16_t fill)
{
    uint16_t a, b, y, last;
    int      dx01, dy01, dx02, dy02, dx12, dy12;
    long     sa = 0;
    long     sb = 0;

    if (fill == 0)
    {
        tli_draw_line(x0, y0, x1, y1, color);
        tli_draw_line(x1, y1, x2, y2, color);
        tli_draw_line(x2, y2, x0, y0, color);
    }
    else
    {
        if (y0 > y1)
        {
            _swap(&y0, &y1);
            _swap(&x0, &x1);
        }
        if (y1 > y2)
        {
            _swap(&y2, &y1);
            _swap(&x2, &x1);
        }
        if (y0 > y1)
        {
            _swap(&y0, &y1);
            _swap(&x0, &x1);
        }
        if (y0 == y2)
        {
            a = b = x0;
            if (x1 < a)
            {
                a = x1;
            }
            else if (x1 > b)
            {
                b = x1;
            }
            if (x2 < a)
            {
                a = x2;
            }
            else if (x2 > b)
            {
                b = x2;
            }
            tli_draw_rectangle(a, y0, b, y0, color, 0);
            return;
        }
        dx01 = x1 - x0;
        dy01 = y1 - y0;
        dx02 = x2 - x0;
        dy02 = y2 - y0;
        dx12 = x2 - x1;
        dy12 = y2 - y1;

        if (y1 == y2)
        {
            last = y1;
        }
        else
        {
            last = y1 - 1;
        }
        for (y = y0; y <= last; y++)
        {
            a   = x0 + sa / dy01;
            b   = x0 + sb / dy02;
            sa += dx01;
            sb += dx02;
            if (a > b)
            {
                _swap(&a, &b);
            }
            tli_draw_rectangle(a, y, b, y, color, 0);
        }
        sa = dx12 * (y - y1);
        sb = dx02 * (y - y0);
        for (; y <= y2; y++)
        {
            a   = x1 + sa / dy12;
            b   = x0 + sb / dy02;
            sa += dx12;
            sb += dx02;
            if (a > b)
            {
                _swap(&a, &b);
            }

            tli_draw_rectangle(a, y, b, y, color, 0);
        }
    }
}


/**
 * @brief    Enlarge a single point by drawing a square block.
 *
 * @note     The enlarged point is drawn as a 2D cross pattern made of four
 *           rectangles centered at (x, y) with specified magnification.
 *
 * @param    x         X coordinate of the center point.
 * @param    y         Y coordinate of the center point.
 * @param    color     Color to fill the enlarged point.
 * @param    magnify   Enlargement factor (minimum value is 1).
 *
 * @return   None
 */
void tli_point_enlarge(uint16_t x, uint16_t y, uint16_t color, char magnify)
{
    tli_draw_rectangle(x - magnify, y - magnify, x, y, color, 1);

    tli_draw_rectangle(x, y - magnify, x + magnify, y, color, 1);

    tli_draw_rectangle(x - magnify, y, x, y + magnify, color, 1);

    tli_draw_rectangle(x, y, x + magnify, y + magnify, color, 1);
}

/**
 * @brief    Display a single ASCII character at the specified position.
 *
 * @note     Uses a fixed-size 16x8 font to render the character with optional
 *           enlargement and overlay mode.
 *
 * @param    x      X coordinate of the character start position.
 * @param    y      Y coordinate of the character start position.
 * @param    fc     Foreground color.
 * @param    bc     Background color.
 * @param    num    ASCII character to display.
 * @param    size   Enlargement factor (minimum 1).
 * @param    mode   Overlay mode: 0 = non-overlay, 1 = overlay.
 *
 * @return   None
 */
void tli_show_char(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t num, uint8_t size, uint8_t mode)
{
    uint8_t  temp;
    uint8_t  pos, t;
    uint16_t x0 = 0;
    uint16_t y0 = 0;
    num         = num - ' ';

    for (pos = 0; pos < 16; pos++)
    {
        temp = asc2_1608[num][pos];
        for (t = 0; t < 16 / 2; t++)
        {
            if (!mode)
            {
                if (temp & 0x01)
                    tli_point_enlarge(x + x0, y + y0, fc, size);
                else
                    tli_point_enlarge(x + x0, y + y0, bc, size);
            }
            else
            {
                if (temp & 0x01) tli_point_enlarge(x + x0, y + y0, fc, size);
            }
            temp >>= 1;
            x0     = x0 + size;
        }
        x0 = 0;
        y0 = y0 + size;
    }
}

/**
 * @brief    Display a null-terminated ASCII string on the screen.
 *
 * @note     Automatically handles line boundaries and skips illegal characters.
 *
 * @param    x      X coordinate of the start position.
 * @param    y      Y coordinate of the start position.
 * @param    fc     Foreground color.
 * @param    bc     Background color.
 * @param    size   Font enlargement factor (base size is 16x8).
 * @param    p      Pointer to the string.
 * @param    mode   Overlay mode: 0 = non-overlay, 1 = overlay.
 *
 * @return   None
 */
void tli_show_string(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t size, uint8_t *p, uint8_t mode)
{
    while ((*p <= '~') && (*p >= ' '))
    {
        if (x > (LCD_WIDTH - 1) || y > (LCD_HEIGHT - 1)) return;

        tli_show_char(x, y, fc, bc, *p, size, mode);
        x += 16 * size / 2;
        p++;
    }
}


/**
 * @brief    Display a picture at a specified position on the screen.
 *
 * @note     The image data is expected to be in RGB565 format, with each pixel
 *           occupying two consecutive bytes in the array.
 *
 * @param    x      X coordinate of the top-left corner.
 * @param    y      Y coordinate of the top-left corner.
 * @param    w      Width of the image in pixels.
 * @param    h      Height of the image in pixels.
 * @param    pic    Pointer to the image data array.
 *
 * @return   None
 */
void tli_show_picture(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const unsigned char pic[])
{
    uint16_t i, j;
    uint32_t k  = 0;
    uint16_t x0 = x, y0 = y;
    for (i = y; i < h + y0; i++)
    {
        for (j = x; j < w + x0; j++)
        {
            tli_draw_point(j, i, pic[k * 2] << 8 | pic[k * 2 + 1]);
            k++;
        }
    }
}


/**
 * @brief    Draw a filled rounded rectangle button.
 *
 * @note     This function draws a button with four rounded corners and fills
 *           the background. The radius must be less than half of the height.
 *
 * @param    x        X coordinate of the top-left corner.
 * @param    y        Y coordinate of the top-left corner.
 * @param    width    Width of the button.
 * @param    height   Height of the button.
 * @param    radius   Radius of the corners.
 * @param    color    Fill color of the button.
 *
 * @return   None
 */
void tli_show_button(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t radius, uint16_t color)
{
    int i = 0;
    int j = 0;


    if (radius >= (height / 2)) return;


    tli_draw_circle(x + radius, y + radius, color, radius, 1);
    tli_draw_circle(x + width - radius - 1, y + radius, color, radius, 1);
    tli_draw_circle(x + radius, y + height - radius - 1, color, radius, 1);
    tli_draw_circle(x + width - radius - 1, y + height - radius - 1, color, radius, 1);

    tli_draw_line(x + radius, y, x + width - radius - 1, y, color);
    tli_draw_line(x + radius, y + height - 1, x + width - radius - 1, y + height - 1, color);
    tli_draw_line(x, y + radius, x, y + height - radius - 1, color);
    tli_draw_line(x + width - 1, y + radius, x + width - 1, y + height - radius - 1, color);

    tli_draw_rectangle(x + radius, y + radius, x + width - radius, y + height - radius, color, 1);
    tli_draw_rectangle(x + radius, y, x + width - radius, y + radius, color, 1);
    tli_draw_rectangle(x, y + radius, x + width, y + height - radius, color, 1);
    tli_draw_rectangle(x + radius, y + height - radius, x + width - radius, y + height, color, 1);
}

/**
 * @brief    Draw a switch (toggle) component with visual state.
 *
 * @note     The switch has a rounded rectangle base with a circular knob
 *           indicating on or off state. Automatically validates layout rules.
 *
 * @param    x           X coordinate of the top-left corner.
 * @param    y           Y coordinate of the top-left corner.
 * @param    width       Total width of the switch.
 * @param    height      Total height of the switch.
 * @param    on_color    Color of the switch when turned on.
 * @param    off_color   Color of the switch when turned off.
 * @param    sw          Switch state: 1 = on, 0 = off.
 *
 * @return   None
 */
void tli_show_switch(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t on_color, uint16_t off_color, char sw)
{
    int radius = height / 2 - 1;

    if (width < 2 * (radius + 1)) return;

    if (sw == 0)
    {
        tli_show_button(x, y, width, height, radius, off_color);
        tli_draw_circle(x + radius, y + radius, WHITE, radius / 2, 1);
    }
    else
    {
        tli_show_button(x, y, width, height, radius, on_color);
        tli_draw_circle(x + width - radius, y + radius, WHITE, radius / 2, 1);
    }
}


