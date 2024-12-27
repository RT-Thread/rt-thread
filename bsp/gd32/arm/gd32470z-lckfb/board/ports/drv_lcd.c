#include <board.h>
#include "gd32f4xx.h"
#include "gd32f4xx_tli.h"
#include "drv_lcd.h"
#include "font.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
//Keil MDK 编译器
uint16_t ltdc_lcd_framebuf0[800][480] __attribute__((at(LCD_FRAME_BUF_ADDR)));
#elif defined(__GNUC__)
// GCC 编译器 (如 RT-Thread 使用的 GCC)
uint16_t ltdc_lcd_framebuf0[10][10];
#endif

static void tli_gpio_config(void);
static void tli_config(void);
static void ipa_config(void);
static void lcd_disp_en_config(void);
static void lcd_disp_off(void);
static void lcd_disp_on(void);

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

/*!
    \brief      IPA initialize and configuration
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void ipa_config(void)
{
    rcu_periph_clock_enable(RCU_IPA);
    nvic_irq_enable(IPA_IRQn, 0, 2);
}

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

/*!
    \brief      configure DISP ON/OFF GPIO
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void lcd_disp_en_config(void)
{
    /* enable the periphral clock */
    rcu_periph_clock_enable(RCU_GPIOD);
    gpio_mode_set(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_13);
    gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);
}

/*!
    \brief      DISP GPIO OFF
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void lcd_disp_off(void)
{
    gpio_bit_reset(GPIOD, GPIO_PIN_13);
}

/*!
    \brief      DISP GPIO ON
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void lcd_disp_on(void)
{
    gpio_bit_set(GPIOD, GPIO_PIN_13);
}


/**********************************************************
 * 函 数 名 称：tli_draw_point
 * 函 数 功 能：画点
 * 传 入 参 数：(x,y)：起点坐标
 * 				color：点的颜色
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：无
**********************************************************/
void tli_draw_point(uint16_t x, uint16_t y, uint16_t color)
{
    *(ltdc_lcd_framebuf0[0] + (LCD_WIDTH * y + x)) = color;
}

/**********************************************************
 * 函 数 名 称：tli_draw_line
 * 函 数 功 能：画线
 * 传 入 参 数：(sx,sy)：起点坐标
 * 				(ex,ey)：终点坐标
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：无
**********************************************************/
void tli_draw_line(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color)
{
    uint16_t t;
    int      xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int      incx, incy, uRow, uCol;

    delta_x = ex - sx; //计算坐标增量
    delta_y = ey - sy;
    uRow    = sx;
    uCol    = sy;
    if (delta_x > 0)
        incx = 1; //设置单步方向
    else if (delta_x == 0)
        incx = 0; //垂直线
    else
    {
        incx    = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)
        incy = 1;
    else if (delta_y == 0)
        incy = 0; //水平线
    else
    {
        incy    = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)
        distance = delta_x; //选取基本增量坐标轴
    else
        distance = delta_y;
    for (t = 0; t <= distance + 1; t++)    //画线输出
    {
        tli_draw_point(uRow, uCol, color); //画点
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
/**********************************************************
 * 函 数 名 称：tli_draw_Rectangle
 * 函 数 功 能：画矩形填充
 * 传 入 参 数：(sx,sy) ：起点坐标
 * 			    (sx,sy) ：终点坐标
 * 				color：笔画颜色
* 				fill：填充标志  =1填充颜色  =0不填充
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：无
**********************************************************/
void tli_draw_Rectangle(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color, uint16_t fill)
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

/**********************************************************
 * 函 数 名 称：_draw_circle_8
 * 函 数 功 能：8对称性画圆算法(内部调用)
 * 传 入 参 数：  (xc,yc):圆中心坐标
                    (x,y):光标相对于圆心的坐标
 * 					    c:点的颜色
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：内部调用
**********************************************************/
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

/**********************************************************
 * 函 数 名 称：tli_draw_circle
 * 函 数 功 能：在指定位置画一个指定大小的圆
 * 传 入 参 数：  (xc,yc) :圆中心坐标
 * 						c:填充的颜色
 *                  	r:圆半径
 *                   fill:填充判断标志，1-填充，0-不填充
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：无
**********************************************************/
void tli_draw_circle(int xc, int yc, uint16_t c, int r, int fill)
{
    int x = 0, y = r, yi, d;

    d = 3 - 2 * r;

    if (fill)
    {
        // 如果填充（画实心圆）
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
        // 如果不填充（画空心圆）
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

/**********************************************************
 * 函 数 名 称：_swap
 * 函 数 功 能：数据交换
 * 传 入 参 数：a=交换方1  b=交换方2
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：仅内部使用
**********************************************************/
static void _swap(uint16_t *a, uint16_t *b)
{
    uint16_t tmp;
    tmp = *a;
    *a  = *b;
    *b  = tmp;
}

/**********************************************************
 * 函 数 名 称：tli_draw_triange
 * 函 数 功 能：画三角形
 * 传 入 参 数：(x0,y0)：第一个边角的坐标
 * 				(x1,y1)：顶点的坐标
 * 				(x2,y2)：第二个边角的坐标
 * 				color：三角形颜色
 * 				fill:填充判断标志，1-填充，0-不填充
 * 函 数 返 回：
 * 作       者：LCKFB
 * 备       注：
**********************************************************/

void tli_draw_triange(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color, uint16_t fill)
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
            tli_draw_Rectangle(a, y0, b, y0, color, 0);
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
            tli_draw_Rectangle(a, y, b, y, color, 0);
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

            tli_draw_Rectangle(a, y, b, y, color, 0);
        }
    }
}


/**********************************************************
 * 函 数 名 称：point_enlargement
 * 函 数 功 能：将一个点放大
 * 传 入 参 数：(x,y)：点的起始坐标
 * 				color：点的颜色
 * 				magnify：点的放大倍数 最小为1
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：无
**********************************************************/
void point_enlargement(uint16_t x, uint16_t y, uint16_t color, char magnify)
{
    tli_draw_Rectangle(x - magnify, y - magnify, x, y, color, 1);

    tli_draw_Rectangle(x, y - magnify, x + magnify, y, color, 1);

    tli_draw_Rectangle(x - magnify, y, x, y + magnify, color, 1);

    tli_draw_Rectangle(x, y, x + magnify, y + magnify, color, 1);
}

/**********************************************************
 * 函 数 名 称：LCD_ShowChar
 * 函 数 功 能：显示一个字符
 * 传 入 参 数：(x,y)：字符显示的起点坐标
				fc：笔画颜色
				bc：背景颜色
				num：显示的字符
				size：字符放大倍数 最小为1
				mode：是否叠加显示	0=非叠加方式  1=叠加方式
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：以16x8大小的字符作为放大模板
**********************************************************/
void tli_show_char(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t num, uint8_t size, uint8_t mode)
{
    uint8_t  temp;
    uint8_t  pos, t;
    uint16_t x0 = 0;
    uint16_t y0 = 0;
    num         = num - ' '; //得到偏移后的值

    for (pos = 0; pos < 16; pos++)
    {
        temp = asc2_1608[num][pos]; //调用1608字体
        for (t = 0; t < 16 / 2; t++)
        {
            if (!mode)
            {
                if (temp & 0x01)
                    point_enlargement(x + x0, y + y0, fc, size); //画一个点
                else
                    point_enlargement(x + x0, y + y0, bc, size); //画一个点
            }
            else
            {
                if (temp & 0x01) point_enlargement(x + x0, y + y0, fc, size); //画一个点
            }
            temp >>= 1;
            x0     = x0 + size;
        }
        x0 = 0;
        y0 = y0 + size;
    }
}

/**********************************************************
 * 函 数 名 称：tli_Show_String
 * 函 数 功 能：显示字符串
 * 传 入 参 数：(x,y)：起始坐标
 * 				fc：笔画颜色
 * 				bc：背景颜色
 * 				size：字符放大倍数（以16作为基数放大 16*size 16*size 16*size）
 * 				p：显示的字符串
 * 				mode：是否叠加显示	0=非叠加方式  1=叠加方式
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：无
**********************************************************/
void tli_show_string(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t size, uint8_t *p, uint8_t mode)
{
    while ((*p <= '~') && (*p >= ' ')) //判断是不是非法字符
    {
        if (x > (LCD_WIDTH - 1) || y > (LCD_HEIGHT - 1)) return;

        tli_show_char(x, y, fc, bc, *p, size, mode);
        x += 16 * size / 2;
        p++;
    }
}


/**********************************************************
 * 函 数 名 称：tli_show_font16
 * 函 数 功 能：显示单个16*16大小的字体
 * 传 入 参 数：(x,y)：字体显示的起始坐标
 *   			   	fc：字体笔画颜色
 * 					bc：字体背景颜色
 * 					s：字体索引
 * 					mode：是否叠加显示	0=非叠加方式  1=叠加方式
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：无
**********************************************************/
void tli_show_font16(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s, uint8_t mode)
{
    uint8_t  i, j;
    uint16_t k;
    uint16_t HZnum;
    uint16_t x0 = x;
    HZnum       = sizeof(tfont16) / sizeof(typFNT_GB16); //自动统计汉字数目

    for (k = 0; k < HZnum; k++)
    {
        if ((tfont16[k].Index[0] == *(s)) && (tfont16[k].Index[1] == *(s + 1)))
        {
            for (i = 0; i < 16 * 2; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (!mode)
                    {
                        if (tfont16[k].Msk[i] & (0x80 >> j))
                            tli_draw_point(x, y, fc); //画一个点
                        else
                            tli_draw_point(x, y, bc); //画一个点
                    }
                    else
                    {
                        if (tfont16[k].Msk[i] & (0x80 >> j)) tli_draw_point(x, y, fc); //画一个点
                    }
                    x++;
                    if ((x - x0) == 16)
                    {
                        x = x0;
                        y++;
                        break;
                    }
                }
            }
        }
        continue; //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
    }
}

/**********************************************************
 * 函 数 名 称：tli_show_font24
 * 函 数 功 能：显示单个24*24大小的字体
 * 传 入 参 数：(x,y)：字体显示的起始坐标
 *   			   	fc：字体笔画颜色
 * 					bc：字体背景颜色
 * 					s：字体索引
 * 					mode：是否叠加显示	0=非叠加方式  1=叠加方式
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：无
**********************************************************/
void tli_show_font24(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s, uint8_t mode)
{
    uint8_t  i, j;
    uint16_t k;
    uint16_t HZnum;
    uint16_t x0 = x;
    HZnum       = sizeof(tfont24) / sizeof(typFNT_GB24); //自动统计汉字数目

    for (k = 0; k < HZnum; k++)
    {
        if ((tfont24[k].Index[0] == *(s)) && (tfont24[k].Index[1] == *(s + 1)))
        {
            for (i = 0; i < 24 * 3; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (!mode)
                    {
                        if (tfont24[k].Msk[i] & (0x80 >> j))
                            tli_draw_point(x, y, fc); //画一个点
                        else
                            tli_draw_point(x, y, bc); //画一个点
                    }
                    else
                    {
                        if (tfont24[k].Msk[i] & (0x80 >> j)) tli_draw_point(x, y, fc); //画一个点
                    }
                    x++;
                    if ((x - x0) == 24)
                    {
                        x = x0;
                        y++;
                        break;
                    }
                }
            }
        }
        continue; //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
    }
}


/**********************************************************
 * 函 数 名 称：tli_show_font32
 * 函 数 功 能：显示单个32*32大小的字体
 * 传 入 参 数：(x,y)：字体显示的起始坐标
 *   			   	fc：字体笔画颜色
 * 					bc：字体背景颜色
 * 					s：字体索引
 * 					mode：是否叠加显示	0=非叠加方式  1=叠加方式
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：无
**********************************************************/
void tli_show_font32(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s, uint8_t mode)
{
    uint8_t  i, j;
    uint16_t k;
    uint16_t HZnum;
    uint16_t x0 = x;
    HZnum       = sizeof(tfont32) / sizeof(typFNT_GB32); //自动统计汉字数目
    for (k = 0; k < HZnum; k++)
    {
        if ((tfont32[k].Index[0] == *(s)) && (tfont32[k].Index[1] == *(s + 1)))
        {
            for (i = 0; i < 32 * 4; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (!mode)
                    {
                        if (tfont32[k].Msk[i] & (0x80 >> j))
                            tli_draw_point(x, y, fc); //画一个点
                        else
                            tli_draw_point(x, y, bc); //画一个点
                    }
                    else
                    {
                        if (tfont32[k].Msk[i] & (0x80 >> j)) tli_draw_point(x, y, fc); //画一个点
                    }
                    x++;
                    if ((x - x0) == 32)
                    {
                        x = x0;
                        y++;
                        break;
                    }
                }
            }
        }
        continue; //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
    }
}


/**********************************************************
 * 函 数 名 称：tli_show_Chinese_string
 * 函 数 功 能：显示中文字符串
 * 传 入 参 数：(x,y)：字符串显示的起始坐标
 *   			   	fc：字符串笔画颜色
 * 					bc：字符串背景颜色
 * 					str：字符串
 * 					size：字符串大小 16，24，32
 * 					mode：是否叠加显示	0=非叠加方式  1=叠加方式
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：显示的中文请确保有其字模，可去font.h查看
**********************************************************/
void tli_show_Chinese_string(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *str, uint8_t size, uint8_t mode)
{
    while (*str != 0) //数据未结束
    {
        if (x > (LCD_WIDTH - size) || y > (LCD_HEIGHT - size)) return;

        if (size == 32)
            tli_show_font32(x, y, fc, bc, str, mode);
        else if (size == 24)
            tli_show_font24(x, y, fc, bc, str, mode);
        else
            tli_show_font16(x, y, fc, bc, str, mode);

        str += 2;
        x   += size; //下一个汉字偏移
    }
}
/**********************************************************
 * 函 数 名 称：tli_show_picture
 * 函 数 功 能：显示图片
 * 传 入 参 数：(x,y)：显示图片的起点坐标
 * 				w：图片宽度
 * 				h：图片高度
 * 				pic：图片地址
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：无
**********************************************************/
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


/**********************************************************
 * 函 数 名 称：tli_show_button
 * 函 数 功 能：绘制一个填充的圆角按钮
 * 传 入 参 数：(x,y)：按钮的左上角的起始位置
 * 				width：按钮宽度
 * 				height：按钮高度
 * 				radius：按钮的4个圆角半径
 * 				color：按钮填充颜色
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：要求w >= 2*(r+1); h >= 2*(r+1);  radius > h/2
**********************************************************/
void tli_show_button(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t radius, uint16_t color)
{
    int i = 0;
    int j = 0;

    //如果小于则绘制出来的结果不好看
    if (radius >= (height / 2)) return;

    // 绘制四个圆角
    tli_draw_circle(x + radius, y + radius, color, radius, 1);
    tli_draw_circle(x + width - radius - 1, y + radius, color, radius, 1);
    tli_draw_circle(x + radius, y + height - radius - 1, color, radius, 1);
    tli_draw_circle(x + width - radius - 1, y + height - radius - 1, color, radius, 1);

    // 绘制边框线
    tli_draw_line(x + radius, y, x + width - radius - 1, y, color);
    tli_draw_line(x + radius, y + height - 1, x + width - radius - 1, y + height - 1, color);
    tli_draw_line(x, y + radius, x, y + height - radius - 1, color);
    tli_draw_line(x + width - 1, y + radius, x + width - 1, y + height - radius - 1, color);

    //绘制内部颜色填充
    tli_draw_Rectangle(x + radius, y + radius, x + width - radius, y + height - radius, color, 1);
    tli_draw_Rectangle(x + radius, y, x + width - radius, y + radius, color, 1);
    tli_draw_Rectangle(x, y + radius, x + width, y + height - radius, color, 1);
    tli_draw_Rectangle(x + radius, y + height - radius, x + width - radius, y + height, color, 1);
}

/**********************************************************
 * 函 数 名 称：tli_show_switch
 * 函 数 功 能：绘制一个开关
 * 传 入 参 数：(x,y)：开关左上角的起始位置
 * 				width：开关的宽度
 * 				height：开关的高度
 * 				on_color：开关打开之后的颜色
 * 				off_color：开关关闭之后的颜色
 * 				sw：开关的状态	=1打开  =0关闭
 * 函 数 返 回：无
 * 作       者：LCKFB
 * 备       注：要求w >= 2*(height/2+1);  不符合要求则无法绘制
**********************************************************/
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




