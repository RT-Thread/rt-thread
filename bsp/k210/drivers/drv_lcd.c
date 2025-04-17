/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-12     ZYH          first version
 */


#include <rtthread.h>

#ifdef BSP_USING_LCD

#include <rtdevice.h>
#include "drv_lcd.h"
#include <board.h>
#include <gpiohs.h>
#include <drivers/dev_spi.h>
#include <spi.h>
#include <drv_io_config.h>
#include <rthw.h>
#include "dmalock.h"
#include "sleep.h"

#define DBG_TAG  "LCD"
#define DBG_LVL  DBG_WARNING
#include <rtdbg.h>

#define NO_OPERATION            0x00
#define SOFTWARE_RESET          0x01
#define READ_ID                 0x04
#define READ_STATUS             0x09
#define READ_POWER_MODE         0x0A
#define READ_MADCTL             0x0B
#define READ_PIXEL_FORMAT       0x0C
#define READ_IMAGE_FORMAT       0x0D
#define READ_SIGNAL_MODE        0x0E
#define READ_SELT_DIAG_RESULT   0x0F
#define SLEEP_ON                0x10
#define SLEEP_OFF               0x11
#define PARTIAL_DISPALY_ON      0x12
#define NORMAL_DISPALY_ON       0x13
#define INVERSION_DISPALY_OFF   0x20
#define INVERSION_DISPALY_ON    0x21
#define GAMMA_SET               0x26
#define DISPALY_OFF             0x28
#define DISPALY_ON              0x29
#define HORIZONTAL_ADDRESS_SET  0x2A
#define VERTICAL_ADDRESS_SET    0x2B
#define MEMORY_WRITE            0x2C
#define COLOR_SET               0x2D
#define MEMORY_READ             0x2E
#define PARTIAL_AREA            0x30
#define VERTICAL_SCROL_DEFINE   0x33
#define TEAR_EFFECT_LINE_OFF    0x34
#define TEAR_EFFECT_LINE_ON     0x35
#define MEMORY_ACCESS_CTL       0x36
#define VERTICAL_SCROL_S_ADD    0x37
#define IDLE_MODE_OFF           0x38
#define IDLE_MODE_ON            0x39
#define PIXEL_FORMAT_SET        0x3A
#define WRITE_MEMORY_CONTINUE   0x3C
#define READ_MEMORY_CONTINUE    0x3E
#define SET_TEAR_SCANLINE       0x44
#define GET_SCANLINE            0x45
#define WRITE_BRIGHTNESS        0x51
#define READ_BRIGHTNESS         0x52
#define WRITE_CTRL_DISPALY      0x53
#define READ_CTRL_DISPALY       0x54
#define WRITE_BRIGHTNESS_CTL    0x55
#define READ_BRIGHTNESS_CTL     0x56
#define WRITE_MIN_BRIGHTNESS    0x5E
#define READ_MIN_BRIGHTNESS     0x5F
#define READ_ID1                0xDA
#define READ_ID2                0xDB
#define READ_ID3                0xDC
#define RGB_IF_SIGNAL_CTL       0xB0
#define NORMAL_FRAME_CTL        0xB1
#define IDLE_FRAME_CTL          0xB2
#define PARTIAL_FRAME_CTL       0xB3
#define INVERSION_CTL           0xB4
#define BLANK_PORCH_CTL         0xB5
#define DISPALY_FUNCTION_CTL    0xB6
#define ENTRY_MODE_SET          0xB7
#define BACKLIGHT_CTL1          0xB8
#define BACKLIGHT_CTL2          0xB9
#define BACKLIGHT_CTL3          0xBA
#define BACKLIGHT_CTL4          0xBB
#define BACKLIGHT_CTL5          0xBC
#define BACKLIGHT_CTL7          0xBE
#define BACKLIGHT_CTL8          0xBF
#define POWER_CTL1              0xC0
#define POWER_CTL2              0xC1
#define VCOM_CTL1               0xC5
#define VCOM_CTL2               0xC7
#define NV_MEMORY_WRITE         0xD0
#define NV_MEMORY_PROTECT_KEY   0xD1
#define NV_MEMORY_STATUS_READ   0xD2
#define READ_ID4                0xD3
#define POSITIVE_GAMMA_CORRECT  0xE0
#define NEGATIVE_GAMMA_CORRECT  0xE1
#define DIGITAL_GAMMA_CTL1      0xE2
#define DIGITAL_GAMMA_CTL2      0xE3
#define INTERFACE_CTL           0xF6

#define LCD_SPI_CHANNEL             SPI_DEVICE_0
#define LCD_SPI_CHIP_SELECT         SPI_CHIP_SELECT_0

#if     defined(BSP_BOARD_K210_OPENMV_TEST)
#define LCD_SCAN_DIR           DIR_YX_LRUD
#elif   defined(BSP_BOARD_K210_DRACO)
#define LCD_SCAN_DIR           DIR_YX_LRUD
#elif   defined(BSP_BOARD_KD233)
#define LCD_SCAN_DIR           (DIR_YX_RLUD | 0x08)
#elif   defined(BSP_BOARD_USER)
/*user define.*/
#define LCD_SCAN_DIR           DIR_YX_RLUD
#endif

typedef struct lcd_8080_device
{
    struct rt_device parent;
    struct rt_device_graphic_info lcd_info;
    int spi_channel;
    int cs;
    int dc_pin;
#if BSP_LCD_RST_PIN >= 0
    int rst_pin;
#endif
#if BSP_LCD_BACKLIGHT_PIN >= 0
    int backlight_pin;
#endif
    int dma_channel;
} * lcd_8080_device_t;

static struct lcd_8080_device _lcddev;

static void drv_lcd_cmd(lcd_8080_device_t lcd, rt_uint8_t cmd)
{
    gpiohs_set_pin(lcd->dc_pin, GPIO_PV_LOW);
    spi_init(lcd->spi_channel, SPI_WORK_MODE_0, SPI_FF_OCTAL, 8, 0);
    spi_init_non_standard(lcd->spi_channel, 8 /*instrction length*/, 0 /*address length*/, 0 /*wait cycles*/,
                          SPI_AITM_AS_FRAME_FORMAT /*spi address trans mode*/);
    spi_send_data_normal_dma(lcd->dma_channel, lcd->spi_channel, lcd->cs, &cmd, 1, SPI_TRANS_CHAR);
}

static void drv_lcd_data_byte(lcd_8080_device_t lcd, rt_uint8_t *data_buf, rt_uint32_t length)
{
    gpiohs_set_pin(lcd->dc_pin, GPIO_PV_HIGH);
    spi_init(lcd->spi_channel, SPI_WORK_MODE_0, SPI_FF_OCTAL, 8, 0);
    spi_init_non_standard(lcd->spi_channel, 8 /*instrction length*/, 0 /*address length*/, 0 /*wait cycles*/,
                          SPI_AITM_AS_FRAME_FORMAT /*spi address trans mode*/);
    spi_send_data_normal_dma(lcd->dma_channel, lcd->spi_channel, lcd->cs, data_buf, length, SPI_TRANS_CHAR);
}

static void drv_lcd_data_half_word(lcd_8080_device_t lcd, rt_uint16_t *data_buf, rt_uint32_t length)
{
    gpiohs_set_pin(lcd->dc_pin, GPIO_PV_HIGH);
    spi_init(lcd->spi_channel, SPI_WORK_MODE_0, SPI_FF_OCTAL, 16, 0);
    spi_init_non_standard(lcd->spi_channel, 16 /*instrction length*/, 0 /*address length*/, 0 /*wait cycles*/,
                          SPI_AITM_AS_FRAME_FORMAT /*spi address trans mode*/);
    spi_send_data_normal_dma(lcd->dma_channel, lcd->spi_channel, lcd->cs, data_buf, length, SPI_TRANS_SHORT);
}

static void drv_lcd_data_word(lcd_8080_device_t lcd, rt_uint32_t *data_buf, rt_uint32_t length)
{
    gpiohs_set_pin(lcd->dc_pin, GPIO_PV_HIGH);
    spi_init(lcd->spi_channel, SPI_WORK_MODE_0, SPI_FF_OCTAL, 32, 0);
    spi_init_non_standard(lcd->spi_channel, 0 /*instrction length*/, 32 /*address length*/, 0 /*wait cycles*/,
                          SPI_AITM_AS_FRAME_FORMAT /*spi address trans mode*/);
    spi_send_data_normal_dma(lcd->dma_channel, lcd->spi_channel, lcd->cs, data_buf, length, SPI_TRANS_INT);
}

static void drv_lcd_hw_init(lcd_8080_device_t lcd)
{
#if BSP_LCD_RST_PIN >= 0
    {
        gpiohs_set_drive_mode(lcd->rst_pin, GPIO_DM_OUTPUT);
        gpiohs_set_pin(lcd->rst_pin, GPIO_PV_LOW);
        msleep(20);
        gpiohs_set_pin(lcd->rst_pin, GPIO_PV_HIGH);
        msleep(20);
    }
#endif
#if BSP_LCD_BACKLIGHT_PIN >= 0
    {
        gpiohs_set_drive_mode(lcd->backlight_pin, GPIO_DM_OUTPUT);
#if defined(BSP_LCD_BACKLIGHT_ACTIVE_LOW)
        gpiohs_set_pin(lcd->backlight_pin, GPIO_PV_LOW);
#elif defined(BSP_LCD_BACKLIGHT_ACTIVE_HIGH)
        gpiohs_set_pin(lcd->backlight_pin, GPIO_PV_HIGH);
#else
        gpiohs_set_pin(lcd->backlight_pin, GPIO_PV_LOW);
#endif
    }
#endif

    gpiohs_set_drive_mode(lcd->dc_pin, GPIO_DM_OUTPUT);
    gpiohs_set_pin(lcd->dc_pin, GPIO_PV_HIGH);
    spi_init(lcd->spi_channel, SPI_WORK_MODE_0, SPI_FF_OCTAL, 8, 0);
    spi_set_clk_rate(lcd->spi_channel, BSP_LCD_CLK_FREQ);
}

static void drv_lcd_set_direction(lcd_8080_device_t lcd, lcd_dir_t dir)
{
    if (dir & DIR_XY_MASK)
    {
        lcd->lcd_info.width = BSP_LCD_Y_MAX;
        lcd->lcd_info.height = BSP_LCD_X_MAX;
    }
    else
    {
        lcd->lcd_info.width = BSP_LCD_X_MAX;
        lcd->lcd_info.height = BSP_LCD_Y_MAX;
    }

    drv_lcd_cmd(lcd, MEMORY_ACCESS_CTL);
    drv_lcd_data_byte(lcd, (rt_uint8_t *)&dir, 1);
}

static void drv_lcd_set_area(lcd_8080_device_t lcd, rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2)
{
    rt_uint8_t data[4] = {0};

    data[0] = (rt_uint8_t)(x1 >> 8);
    data[1] = (rt_uint8_t)(x1);
    data[2] = (rt_uint8_t)(x2 >> 8);
    data[3] = (rt_uint8_t)(x2);
    drv_lcd_cmd(lcd, HORIZONTAL_ADDRESS_SET);
    drv_lcd_data_byte(lcd, data, 4);

    data[0] = (rt_uint8_t)(y1 >> 8);
    data[1] = (rt_uint8_t)(y1);
    data[2] = (rt_uint8_t)(y2 >> 8);
    data[3] = (rt_uint8_t)(y2);
    drv_lcd_cmd(lcd, VERTICAL_ADDRESS_SET);
    drv_lcd_data_byte(lcd, data, 4);

    drv_lcd_cmd(lcd, MEMORY_WRITE);
}

static void drv_lcd_set_pixel(lcd_8080_device_t lcd, uint16_t x, uint16_t y, uint16_t color)
{
    drv_lcd_set_area(lcd, x, y, x, y);
    drv_lcd_data_half_word(lcd, &color, 1);
}

static void drv_lcd_clear(lcd_8080_device_t lcd, uint16_t color)
{
    uint32_t data = ((uint32_t)color << 16) | (uint32_t)color;

    drv_lcd_set_area(lcd, 0, 0, lcd->lcd_info.width - 1, lcd->lcd_info.height - 1);
    gpiohs_set_pin(lcd->dc_pin, GPIO_PV_HIGH);
    spi_init(lcd->spi_channel, SPI_WORK_MODE_0, SPI_FF_OCTAL, 32, 0);
    spi_init_non_standard(lcd->spi_channel, 0 /*instrction length*/, 32 /*address length*/, 0 /*wait cycles*/,
                          SPI_AITM_AS_FRAME_FORMAT /*spi address trans mode*/);
    spi_fill_data_dma(lcd->dma_channel, lcd->spi_channel, lcd->cs, (const uint32_t *)&data, lcd->lcd_info.width * lcd->lcd_info.height / 2);
}

static void rt_bitblt(rt_uint16_t * dest, int dest_segment, int dest_common, int dest_x, int dest_y, int width, int height,
        rt_uint16_t *src, int src_segment, int src_common, int src_x, int src_y)
{
    int sx0, sx1, sy0, sy1;
    int dx0, dx1, dy0, dy1;
    rt_uint16_t *buff_src;
    rt_uint16_t *buff_dest;
    int x, y;

    if (width <= 0) {
        return;
    }
    if (height <= 0) {
        return;
    }

    sx0 = src_x;
    sy0 = src_y;
    sx1 = sx0 + width - 1;
    sy1 = sy0 + height - 1;
    dx0 = dest_x;
    dy0 = dest_y;
    dx1 = dx0 + width - 1;
    dy1 = dy0 + height - 1;

    if (sx0 < 0) {
        dx0 -= sx0;
        sx0 = 0;
    }
    if (sy0 < 0) {
        dy0 -= sy0;
        sy0 = 0;
    }
    if (sx1 >= src_segment) {
        dx1 -= (sx1 - src_segment + 1);
        sx1 = src_segment - 1;
    }
    if (sy1 >= src_common) {
        dy1 -= (sy1 - src_common + 1);
        sy1 = src_common - 1;
    }

    if (dx0 < 0) {
        sx0 -= dx0;
        dx0 = 0;
    }
    if (dy0 < 0) {
        sy0 -= dy0;
        dy0 = 0;
    }
    if (dx1 >= dest_segment) {
        sx1 -= (dx1 - dest_segment + 1);
        dx1 = dest_segment - 1;
    }
    if (dy1 >= dest_common) {
        sy1 -= (dy1 - dest_common + 1);
        dy1 = dest_common - 1;
    }

    if (sx1 < 0 || sx0 >= src_segment) {
        return;
    }
    if (sy1 < 0 || sy0 >= src_common) {
        return;
    }
    if (dx1 < 0 || dx0 >= dest_segment) {
        return;
    }
    if (dy1 < 0 || dy0 >= dest_common) {
        return;
    }

    if ((rt_ubase_t)dest < (rt_ubase_t)src) {
        buff_src = src + (sy0 * src_segment) + sx0;
        buff_dest = dest + (dy0 * dest_segment) + dx0;
        for (y = sy0; y <= sy1; y++) {
            src = buff_src;
            dest = buff_dest;
            for (x = sx0; x <= sx1; x++) {
                *dest++ = *src++;
            }
            buff_src += src_segment;
            buff_dest += dest_segment;
        }
    } else {
        buff_src = src + (sy1 * src_segment) + sx1;
        buff_dest = dest + (dy1 * dest_segment) + dx1;
        for (y = sy1; y >= sy0; y--) {
            src = buff_src;
            dest = buff_dest;
            for (x = sx1; x >= sx0; x--) {
                *dest-- = *src--;
            }
            buff_src -= src_segment;
            buff_dest -= dest_segment;
        }
    }
}

static void drv_lcd_rect_update(lcd_8080_device_t lcd, uint16_t x1, uint16_t y1, uint16_t width, uint16_t height)
{
    static rt_uint16_t * rect_buffer = RT_NULL;
    if(!rect_buffer)
    {
        rect_buffer = rt_malloc_align(lcd->lcd_info.height * lcd->lcd_info.width * (lcd->lcd_info.bits_per_pixel / 8), 64);
        if(!rect_buffer)
        {
            return;
        }
    }
    if(x1 == 0 && y1 == 0 && width == lcd->lcd_info.width && height == lcd->lcd_info.height)
    {
        drv_lcd_set_area(lcd, x1, y1, x1 + width - 1, y1 + height - 1);
        drv_lcd_data_half_word(lcd, (rt_uint32_t *)lcd->lcd_info.framebuffer, width * height);
    }
    else
    {
        rt_bitblt(rect_buffer, width, height, 0, 0, width, height,
        (rt_uint16_t *)lcd->lcd_info.framebuffer, lcd->lcd_info.width, lcd->lcd_info.height, x1, y1);
        drv_lcd_set_area(lcd, x1, y1, x1 + width - 1, y1 + height - 1);
        drv_lcd_data_half_word(lcd, (rt_uint16_t *)rect_buffer, width * height);
    }
}

static rt_err_t drv_lcd_init(rt_device_t dev)
{
    rt_err_t ret = RT_EOK;
    lcd_8080_device_t lcd = (lcd_8080_device_t)dev;
    rt_uint8_t data = 0;

    if(!lcd)
    {
        return -RT_ERROR;
    }
    drv_lcd_hw_init(lcd);
    /* reset LCD */
    drv_lcd_cmd(lcd, SOFTWARE_RESET);
    rt_thread_mdelay(100);

    /* Enter normal status */
    drv_lcd_cmd(lcd, SLEEP_OFF);
    rt_thread_mdelay(100);

    /* pixel format rgb565 */
    drv_lcd_cmd(lcd, PIXEL_FORMAT_SET);
    data = 0x55;
    drv_lcd_data_byte(lcd, &data, 1);

    /* set direction */
    drv_lcd_set_direction(lcd, LCD_SCAN_DIR);

    lcd->lcd_info.framebuffer = rt_malloc_align(lcd->lcd_info.height * lcd->lcd_info.width * (lcd->lcd_info.bits_per_pixel / 8), 64);
    RT_ASSERT(lcd->lcd_info.framebuffer);

    uint16_t *framebuffer = (uint16_t *)(lcd->lcd_info.framebuffer);
    for(uint32_t i=0; i<(lcd->lcd_info.height * lcd->lcd_info.width * (lcd->lcd_info.bits_per_pixel / 8))/2; i++) {
        framebuffer[i] = BLACK;
    }
    /*display on*/
    #ifdef BSP_BOARD_K210_DRACO
    drv_lcd_cmd(lcd, INVERSION_DISPALY_ON);
    #endif
    drv_lcd_cmd(lcd, DISPALY_ON);

    /* set to black */
    drv_lcd_clear(lcd, BLACK);
    return ret;
}

static rt_err_t drv_lcd_open(rt_device_t dev, rt_uint16_t oflag)
{

    /* Not need */

    return RT_EOK;
}

static rt_err_t drv_lcd_close(rt_device_t dev)
{

    /* Not need */

    return RT_EOK;
}

static rt_ssize_t drv_lcd_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{

    /* Not need */

    return 0;
}

static rt_ssize_t drv_lcd_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{

    /* Not need */

    return 0;
}

static rt_err_t drv_lcd_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t ret = RT_EOK;
    lcd_8080_device_t lcd = (lcd_8080_device_t)dev;
    rt_base_t level;
    struct rt_device_rect_info* rect_info = (struct rt_device_rect_info*)args;

    RT_ASSERT(dev != RT_NULL);

    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
        if(!rect_info)
        {
            LOG_E("RTGRAPHIC_CTRL_RECT_UPDATE error args");
            return -RT_ERROR;
        }
        drv_lcd_rect_update(lcd, rect_info->x, rect_info->y, rect_info->width, rect_info->height);
        break;

#if BSP_LCD_BACKLIGHT_PIN >= 0
    case RTGRAPHIC_CTRL_POWERON:
#if defined(BSP_LCD_BACKLIGHT_ACTIVE_LOW)
        gpiohs_set_pin(lcd->backlight_pin, GPIO_PV_LOW);
#elif defined(BSP_LCD_BACKLIGHT_ACTIVE_HIGH)
        gpiohs_set_pin(lcd->backlight_pin, GPIO_PV_HIGH);
#else
        gpiohs_set_pin(lcd->backlight_pin, GPIO_PV_LOW);
#endif
        break;

    case RTGRAPHIC_CTRL_POWEROFF:
#if defined(BSP_LCD_BACKLIGHT_ACTIVE_LOW)
        gpiohs_set_pin(lcd->backlight_pin, GPIO_PV_HIGH);
#elif defined(BSP_LCD_BACKLIGHT_ACTIVE_HIGH)
        gpiohs_set_pin(lcd->backlight_pin, GPIO_PV_LOW);
#else
        gpiohs_set_pin(lcd->backlight_pin, GPIO_PV_HIGH);
#endif
        break;
#endif /* BSP_LCD_BACKLIGHT_PIN >= 0 */

    case RTGRAPHIC_CTRL_GET_INFO:
        *(struct rt_device_graphic_info *)args = lcd->lcd_info;
        break;

    case RTGRAPHIC_CTRL_SET_MODE:
        ret = -RT_ENOSYS;
        break;
    case RTGRAPHIC_CTRL_GET_EXT:
        ret = -RT_ENOSYS;
        break;
    default:
        LOG_E("drv_lcd_control cmd: %d", cmd);
        break;
    }

    return ret;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops drv_lcd_ops =
{
    drv_lcd_init,
    drv_lcd_open,
    drv_lcd_close,
    drv_lcd_read,
    drv_lcd_write,
    drv_lcd_control
};
#endif


int rt_hw_lcd_init(void)
{
    rt_err_t ret = RT_EOK;
    lcd_8080_device_t lcd_dev = &_lcddev;

    lcd_dev->cs                         = SPI_CHIP_SELECT_0;
    lcd_dev->dc_pin                     = LCD_DC_PIN;
#if BSP_LCD_RST_PIN >= 0
    lcd_dev->rst_pin                    = LCD_RST_PIN;
#endif
#if BSP_LCD_BACKLIGHT_PIN >= 0
    lcd_dev->backlight_pin              = LCD_BACKLIGHT_PIN;
#endif
    dmalock_sync_take(&lcd_dev->dma_channel, RT_WAITING_FOREVER);
    lcd_dev->spi_channel                = SPI_DEVICE_0;
    lcd_dev->lcd_info.bits_per_pixel    = 16;
    lcd_dev->lcd_info.pixel_format      = RTGRAPHIC_PIXEL_FORMAT_RGB565;

    lcd_dev->parent.type        = RT_Device_Class_Graphic;
    lcd_dev->parent.rx_indicate = RT_NULL;
    lcd_dev->parent.tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    lcd_dev->parent.ops        = &drv_lcd_ops;
#else
    lcd_dev->parent.init    = drv_lcd_init;
    lcd_dev->parent.open    = drv_lcd_open;
    lcd_dev->parent.close   = drv_lcd_close;
    lcd_dev->parent.read    = drv_lcd_read;
    lcd_dev->parent.write   = drv_lcd_write;
    lcd_dev->parent.control = drv_lcd_control;
#endif

    lcd_dev->parent.user_data = RT_NULL;

    ret = rt_device_register(&lcd_dev->parent, "lcd", RT_DEVICE_FLAG_RDWR);

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_lcd_init);

void lcd_set_direction(lcd_dir_t dir)
{
    drv_lcd_set_direction(&_lcddev, dir);
}

#endif
