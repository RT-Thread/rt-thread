/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-03-24     spaceman          the first version
 */

#include <board.h>

#ifdef BSP_USING_LCD_SPI
#include <drv_spi.h>
#include <drv_lcd_spi.h>
#include <drv_lcd_spi_ext.h>
#include <lcd_port.h>
#include <string.h>

#define DRV_DEBUG
#define LOG_TAG "drv.lcd"
#include <drv_log.h>

#define ABS(X) ((X) > 0 ? (X) : -(X))

static struct drv_lcd_device _lcd;
static rt_uint8_t lcd_bn = 0;

// 因为这类SPI的屏幕，每次更新显示时，需要先配置坐标区域、再写显存，
// 在显示字符时，如果是一个个点去写坐标写显存，会非常慢，
// 因此开辟一片缓冲区，先将需要显示的数据写进缓冲区，最后再批量写入显存。
// 用户可以根据实际情况去修改此处缓冲区的大小，
// 例如，用户需要显示32*32的汉字时，需要的大小为 32*32*2 = 2048 字节（每个像素点占2字节）
static uint16_t LCD_Buff[1024]; // LCD缓冲区，16位宽（每个像素点占2字节）

static void set_lcd_backlight(rt_uint8_t value)
{
    if (value)
        rt_pin_write(LCD_BACKLIGHT_PIN, PIN_HIGH);
    else
        rt_pin_write(LCD_BACKLIGHT_PIN, PIN_LOW);
    lcd_bn = value;
}

static rt_uint8_t get_lcd_backlight(void)
{
    return lcd_bn;
}

static void lcd_writecommand(uint8_t lcd_command)
{
    rt_pin_write(LCD_CMD_DATA_PIN, PIN_LOW); // cmd
    rt_spi_send((struct rt_spi_device *)_lcd.lcd_spi_dev, &lcd_command, 1);
}

static void lcd_writedata_8bit(uint8_t lcd_data)
{
    rt_pin_write(LCD_CMD_DATA_PIN, PIN_HIGH); // data
    rt_spi_send((struct rt_spi_device *)_lcd.lcd_spi_dev, &lcd_data, 1);
}

static void lcd_writedata_16bit(uint16_t lcd_data)
{
    uint8_t lcd_data_buff[2];         // 数据发送区
    lcd_data_buff[0] = lcd_data >> 8; // 将数据拆分
    lcd_data_buff[1] = lcd_data;

    rt_pin_write(LCD_CMD_DATA_PIN, PIN_HIGH); // data
    rt_spi_send((struct rt_spi_device *)_lcd.lcd_spi_dev, lcd_data_buff, 2);
}

void lcd_writebuff(uint16_t *databuff, uint16_t datasize)
{
    struct stm32_spi *spi_drv =  rt_container_of(((struct rt_spi_device *)_lcd.lcd_spi_dev)->bus, struct stm32_spi, spi_bus);
    SPI_HandleTypeDef *spi_handle = &spi_drv->handle;

    rt_pin_write(LCD_CMD_DATA_PIN, PIN_HIGH); // data

    // Additional setting (FifoThreshold) are required here, so we do not use rt_spi_configure
    spi_handle->Init.DataSize   = SPI_DATASIZE_16BIT;
    spi_handle->Init.FifoThreshold = SPI_FIFO_THRESHOLD_02DATA;
    HAL_SPI_Init(spi_handle);

    rt_spi_send((struct rt_spi_device *)_lcd.lcd_spi_dev, databuff, datasize);

    spi_handle->Init.DataSize   = SPI_DATASIZE_8BIT;
    spi_handle->Init.FifoThreshold = SPI_FIFO_THRESHOLD_08DATA;
    HAL_SPI_Init(spi_handle);
}

void lcd_setaddress(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    lcd_writecommand(0x2a); //  列地址设置，即X坐标
    lcd_writedata_16bit(x1);
    lcd_writedata_16bit(x2);

    lcd_writecommand(0x2b); //  行地址设置，即Y坐标
    lcd_writedata_16bit(y1);
    lcd_writedata_16bit(y2);

    lcd_writecommand(0x2c); //  开始写入显存，即要显示的颜色数据
}

void lcd_clear(uint32_t color)
{
    rt_err_t res;
    struct stm32_spi *spi_drv =  rt_container_of(((struct rt_spi_device *)_lcd.lcd_spi_dev)->bus, struct stm32_spi, spi_bus);
    SPI_HandleTypeDef *spi_handle = &spi_drv->handle;

    lcd_setaddress(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1); // 设置坐标

    rt_pin_write(LCD_CMD_DATA_PIN, PIN_HIGH); // data

    // Additional setting (FifoThreshold) are required here, so we do not use rt_spi_configure
    spi_handle->Init.DataSize   = SPI_DATASIZE_16BIT;
    spi_handle->Init.FifoThreshold = SPI_FIFO_THRESHOLD_02DATA;
    HAL_SPI_Init(spi_handle);

    rt_pin_write(LCD_SPI_DEV_CS_PIN, PIN_LOW); // cs
    res = SPI_Transmit_Ext((uint16_t)color, LCD_WIDTH * LCD_HEIGHT);
    rt_pin_write(LCD_SPI_DEV_CS_PIN, PIN_HIGH); // cs
    if(res != RT_EOK)
        LOG_E("SPI_Transmit_Ext error: %d", res);

    spi_handle->Init.DataSize   = SPI_DATASIZE_8BIT;
    spi_handle->Init.FifoThreshold = SPI_FIFO_THRESHOLD_08DATA;
    HAL_SPI_Init(spi_handle);
}

void lcd_clearrect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color)
{
    rt_err_t res;
    struct stm32_spi *spi_drv =  rt_container_of(((struct rt_spi_device *)_lcd.lcd_spi_dev)->bus, struct stm32_spi, spi_bus);
    SPI_HandleTypeDef *spi_handle = &spi_drv->handle;

    lcd_setaddress(x, y, x + width - 1, y + height - 1); // 设置坐标

    rt_pin_write(LCD_CMD_DATA_PIN, PIN_HIGH); // data

    // Additional setting (FifoThreshold) are required here, so we do not use rt_spi_configure
    spi_handle->Init.DataSize   = SPI_DATASIZE_16BIT;
    spi_handle->Init.FifoThreshold = SPI_FIFO_THRESHOLD_02DATA;
    HAL_SPI_Init(spi_handle);

    rt_pin_write(LCD_SPI_DEV_CS_PIN, PIN_LOW); // cs
    res = SPI_Transmit_Ext((uint16_t)color, width * height);
    rt_pin_write(LCD_SPI_DEV_CS_PIN, PIN_HIGH); // cs
    if(res != RT_EOK)
        LOG_E("SPI_Transmit_Ext error: %d", res);

    spi_handle->Init.DataSize   = SPI_DATASIZE_8BIT;
    spi_handle->Init.FifoThreshold = SPI_FIFO_THRESHOLD_08DATA;
    HAL_SPI_Init(spi_handle);
}

void lcd_copybuffer(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t *databuff)
{
    rt_err_t res;
    struct stm32_spi *spi_drv =  rt_container_of(((struct rt_spi_device *)_lcd.lcd_spi_dev)->bus, struct stm32_spi, spi_bus);
    SPI_HandleTypeDef *spi_handle = &spi_drv->handle;

    lcd_setaddress(x, y, x + width - 1, y + height - 1); // 设置坐标

    rt_pin_write(LCD_CMD_DATA_PIN, PIN_HIGH); // data

    // Additional setting (FifoThreshold) are required here, so we do not use rt_spi_configure
    spi_handle->Init.DataSize   = SPI_DATASIZE_16BIT;
    spi_handle->Init.FifoThreshold = SPI_FIFO_THRESHOLD_02DATA;
    HAL_SPI_Init(spi_handle);

    rt_pin_write(LCD_SPI_DEV_CS_PIN, PIN_LOW); // cs
    res = SPI_TransmitBuffer_Ext(databuff, width * height);
    rt_pin_write(LCD_SPI_DEV_CS_PIN, PIN_HIGH); // cs
    if(res != RT_EOK)
        LOG_E("SPI_TransmitBuffer_Ext error: %d", res);

    spi_handle->Init.DataSize   = SPI_DATASIZE_8BIT;
    spi_handle->Init.FifoThreshold = SPI_FIFO_THRESHOLD_08DATA;
    HAL_SPI_Init(spi_handle);
}

void lcd_drawpoint(uint16_t x, uint16_t y, uint32_t color)
{
    lcd_setaddress(x, y, x, y); //  设置坐标
    lcd_writedata_16bit(color);
}

void lcd_drawline(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color)
{
    int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
            yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
            curpixel = 0;

    deltax = ABS(x2 - x1); /* The difference between the x's */
    deltay = ABS(y2 - y1); /* The difference between the y's */
    x      = x1;           /* Start x off at the first pixel */
    y      = y1;           /* Start y off at the first pixel */

    if (x2 >= x1) /* The x-values are increasing */
    {
        xinc1 = 1;
        xinc2 = 1;
    } else /* The x-values are decreasing */
    {
        xinc1 = -1;
        xinc2 = -1;
    }

    if (y2 >= y1) /* The y-values are increasing */
    {
        yinc1 = 1;
        yinc2 = 1;
    } else /* The y-values are decreasing */
    {
        yinc1 = -1;
        yinc2 = -1;
    }

    if (deltax >= deltay) /* There is at least one x-value for every y-value */
    {
        xinc1     = 0; /* Don't change the x when numerator >= denominator */
        yinc2     = 0; /* Don't change the y for every iteration */
        den       = deltax;
        num       = deltax / 2;
        numadd    = deltay;
        numpixels = deltax; /* There are more x-values than y-values */
    } else                  /* There is at least one y-value for every x-value */
    {
        xinc2     = 0; /* Don't change the x for every iteration */
        yinc1     = 0; /* Don't change the y when numerator >= denominator */
        den       = deltay;
        num       = deltay / 2;
        numadd    = deltax;
        numpixels = deltay; /* There are more y-values than x-values */
    }
    for (curpixel = 0; curpixel <= numpixels; curpixel++) {
        lcd_drawpoint(x, y, color); /* Draw the current pixel */
        num += numadd;              /* Increase the numerator by the top of the fraction */
        if (num >= den)             /* Check if numerator >= denominator */
        {
            num -= den; /* Calculate the new numerator value */
            x += xinc1; /* Change the x as appropriate */
            y += yinc1; /* Change the y as appropriate */
        }
        x += xinc2; /* Change the x as appropriate */
        y += yinc2; /* Change the y as appropriate */
    }
}

void lcd_drawline_v(uint16_t x, uint16_t y, uint16_t height, uint32_t color)
{
    uint16_t i; // 计数变量
    for (i = 0; i < height; i++) {
        LCD_Buff[i] = color; // 写入缓冲区
    }
    lcd_setaddress(x, y, x, y + height - 1); // 设置坐标
    lcd_writebuff(LCD_Buff, height); // 写入显存
}

void lcd_drawline_h(uint16_t x, uint16_t y, uint16_t width, uint32_t color)
{
    uint16_t i; // 计数变量
    for (i = 0; i < width; i++) {
        LCD_Buff[i] = color; // 写入缓冲区
    }
    lcd_setaddress(x, y, x + width - 1, y); // 设置坐标
    lcd_writebuff(LCD_Buff, width); // 写入显存
}

static rt_err_t stm32_lcd_init(struct drv_lcd_device *lcd)
{
    rt_err_t result;
    struct rt_spi_configuration cfg;

    result = rt_hw_spi_device_attach(LCD_SPI_BUS_NAME, LCD_SPI_DEV_NAME, LCD_SPI_DEV_CS_PIN);

    lcd->lcd_spi_dev = rt_device_find(LCD_SPI_DEV_NAME);
    cfg.data_width = 8;
    cfg.mode       = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB | RT_SPI_3WIRE;
    cfg.max_hz     = LCD_SPI_MAX_SPEED;
    rt_spi_configure((struct rt_spi_device *)lcd->lcd_spi_dev, &cfg);

    rt_pin_mode(LCD_BACKLIGHT_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LCD_CMD_DATA_PIN, PIN_MODE_OUTPUT);

    // init lcd
    rt_thread_mdelay(10);
    lcd_writecommand(0x36);   // 显存访问控制 指令，用于设置访问显存的方式
    lcd_writedata_8bit(0x00); // 配置成 从上到下、从左到右，RGB像素格式 垂直显示
    // lcd_writedata_8bit(0x70); // 横屏显示
    // lcd_writedata_8bit(0xA0); // 横屏显示，并上下翻转，RGB像素格式
    // lcd_writedata_8bit(0xC0); // 垂直显示，并上下翻转，RGB像素格式

    lcd_writecommand(0x3A);   // 接口像素格式 指令，用于设置使用 12位、16位还是18位色
    lcd_writedata_8bit(0x05); // 此处配置成 16位 像素格式

    // 接下来很多都是电压设置指令，直接使用厂家给设定值
    lcd_writecommand(0xB2);
    lcd_writedata_8bit(0x0C);
    lcd_writedata_8bit(0x0C);
    lcd_writedata_8bit(0x00);
    lcd_writedata_8bit(0x33);
    lcd_writedata_8bit(0x33);

    lcd_writecommand(0xB7);   // 栅极电压设置指令
    lcd_writedata_8bit(0x35); // VGH = 13.26V，VGL = -10.43V

    lcd_writecommand(0xBB);   // 公共电压设置指令
    lcd_writedata_8bit(0x19); // VCOM = 1.35V

    lcd_writecommand(0xC0);
    lcd_writedata_8bit(0x2C);

    lcd_writecommand(0xC2);   // VDV 和 VRH 来源设置
    lcd_writedata_8bit(0x01); // VDV 和 VRH 由用户自由配置

    lcd_writecommand(0xC3);   // VRH电压 设置指令
    lcd_writedata_8bit(0x12); // VRH电压 = 4.6+( vcom+vcom offset+vdv)

    lcd_writecommand(0xC4);   // VDV电压 设置指令
    lcd_writedata_8bit(0x20); // VDV电压 = 0v

    lcd_writecommand(0xC6);   // 正常模式的帧率控制指令
    lcd_writedata_8bit(0x0F); // 设置屏幕控制器的刷新帧率为60帧

    lcd_writecommand(0xD0);   // 电源控制指令
    lcd_writedata_8bit(0xA4); // 无效数据，固定写入0xA4
    lcd_writedata_8bit(0xA1); // AVDD = 6.8V ，AVDD = -4.8V ，VDS = 2.3V

    lcd_writecommand(0xE0); // 正极电压伽马值设定
    lcd_writedata_8bit(0xD0);
    lcd_writedata_8bit(0x04);
    lcd_writedata_8bit(0x0D);
    lcd_writedata_8bit(0x11);
    lcd_writedata_8bit(0x13);
    lcd_writedata_8bit(0x2B);
    lcd_writedata_8bit(0x3F);
    lcd_writedata_8bit(0x54);
    lcd_writedata_8bit(0x4C);
    lcd_writedata_8bit(0x18);
    lcd_writedata_8bit(0x0D);
    lcd_writedata_8bit(0x0B);
    lcd_writedata_8bit(0x1F);
    lcd_writedata_8bit(0x23);

    lcd_writecommand(0xE1); // 负极电压伽马值设定
    lcd_writedata_8bit(0xD0);
    lcd_writedata_8bit(0x04);
    lcd_writedata_8bit(0x0C);
    lcd_writedata_8bit(0x11);
    lcd_writedata_8bit(0x13);
    lcd_writedata_8bit(0x2C);
    lcd_writedata_8bit(0x3F);
    lcd_writedata_8bit(0x44);
    lcd_writedata_8bit(0x51);
    lcd_writedata_8bit(0x2F);
    lcd_writedata_8bit(0x1F);
    lcd_writedata_8bit(0x1F);
    lcd_writedata_8bit(0x20);
    lcd_writedata_8bit(0x23);

    lcd_writecommand(0x21); // 打开反显，因为面板是常黑型，操作需要反过来

    // 退出休眠指令，LCD控制器在刚上电、复位时，会自动进入休眠模式 ，因此操作屏幕之前，需要退出休眠
    lcd_writecommand(0x11); // 退出休眠 指令
    rt_thread_mdelay(120);  // 需要等待120ms，让电源电压和时钟电路稳定下来

    // 打开显示指令，LCD控制器在刚上电、复位时，会自动关闭显示
    lcd_writecommand(0x29); // 打开显示

    // set spi handler to ensure SPI_Transmit_Ext/SPI_TransmitBuffer_Ext function can be used
    struct stm32_spi *spi_drv =  rt_container_of(((struct rt_spi_device *)lcd->lcd_spi_dev)->bus, struct stm32_spi, spi_bus);
    SPI_HandleTypeDef *spi_handle = &spi_drv->handle;
    Set_SPI_Handle_Ext(spi_handle);

    lcd_clear(0xFFFFFF);                   // 清屏

    // 全部设置完毕之后，打开背光
    set_lcd_backlight(1);

    LOG_D("lcd init ok");

    // lcd_drawline_v(120, 0, LCD_HEIGHT, 0xffaaff);
    // lcd_drawline_h(0, 120, LCD_WIDTH, 0xffaaff);

    return result;
}

static rt_err_t drv_lcd_init(struct rt_device *device)
{
    struct drv_lcd_device *lcd = LCD_DEVICE(device);
    return stm32_lcd_init(lcd);
}

static rt_err_t drv_lcd_control(struct rt_device *device, int cmd, void *args)
{
    struct drv_lcd_device *lcd = LCD_DEVICE(device);

    switch (cmd) {
        case RTGRAPHIC_CTRL_RECT_UPDATE: {
            lcd_setaddress(0, 0, lcd->lcd_info.width - 1, lcd->lcd_info.height - 1);
            lcd_writebuff((uint16_t*)lcd->lcd_info.framebuffer, LCD_BUF_SIZE / 2); // 16 bit write buffer
        } break;

        case RTGRAPHIC_CTRL_GET_INFO: {
            struct rt_device_graphic_info *info = (struct rt_device_graphic_info *)args;

            RT_ASSERT(info != RT_NULL);
            info->pixel_format   = lcd->lcd_info.pixel_format;
            info->bits_per_pixel = 16;
            info->width          = lcd->lcd_info.width;
            info->height         = lcd->lcd_info.height;
            info->framebuffer    = lcd->lcd_info.framebuffer;
        } break;

        case RTGRAPHIC_CTRL_SET_BRIGHTNESS: {
            set_lcd_backlight(*((rt_uint8_t *)args));
        } break;

        case RTGRAPHIC_CTRL_GET_BRIGHTNESS: {
            *((rt_uint8_t *)args) = get_lcd_backlight();
        } break;

        default:
            return -RT_EINVAL;
    }

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops lcd_ops =
{
    drv_lcd_init,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    drv_lcd_control
};
#endif

static void set_pixel(const char *pixel, int x, int y)
{
    lcd_drawpoint(x, y, *pixel);
}

void draw_hline(const char *pixel, int x1, int x2, int y)
{
    lcd_drawline_h(x1, y, ABS(x2 - x1), *((uint16_t*)pixel));
}

void draw_vline(const char *pixel, int x, int y1, int y2)
{
    lcd_drawline_v(x, y1, ABS(y2 - y1), *((uint16_t*)pixel));
}

const static struct rt_device_graphic_ops lcd_graphic_ops =
{
    set_pixel,
    RT_NULL,
    draw_hline,
    draw_vline,
    RT_NULL
};

int drv_hw_lcd_init(void)
{
    rt_err_t result          = RT_EOK;
    struct rt_device *device = &_lcd.parent;

    /* memset _lcd to zero */
    memset(&_lcd, 0x00, sizeof(_lcd));

    /* init lcd_lock semaphore */
    result = rt_sem_init(&_lcd.lcd_lock, "lcd_lock", 0, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK) {
        LOG_E("init semaphore failed!\n");
        result = -RT_ENOMEM;
        goto __exit;
    }

    /* config LCD dev info */
    _lcd.lcd_info.height         = LCD_HEIGHT;
    _lcd.lcd_info.width          = LCD_WIDTH;
    _lcd.lcd_info.bits_per_pixel = LCD_BITS_PER_PIXEL;
    _lcd.lcd_info.pixel_format   = LCD_PIXEL_FORMAT;

    /* malloc memory for Triple Buffering */
    _lcd.lcd_info.framebuffer = rt_malloc_align(LCD_BUF_SIZE, 32);
    _lcd.back_buf             = rt_malloc_align(LCD_BUF_SIZE, 32);
    _lcd.front_buf            = rt_malloc_align(LCD_BUF_SIZE, 32);
    if (_lcd.lcd_info.framebuffer == RT_NULL || _lcd.back_buf == RT_NULL || _lcd.front_buf == RT_NULL) {
        LOG_E("init frame buffer failed!\n");
        result = -RT_ENOMEM;
        goto __exit;
    }

    /* memset buff to 0xFF */
    memset(_lcd.lcd_info.framebuffer, 0xFF, LCD_BUF_SIZE);
    memset(_lcd.back_buf, 0xFF, LCD_BUF_SIZE);
    memset(_lcd.front_buf, 0xFF, LCD_BUF_SIZE);

    device->type = RT_Device_Class_Graphic;
#ifdef RT_USING_DEVICE_OPS
    device->ops = &lcd_ops;
#else
    device->init    = drv_lcd_init;
    device->control = drv_lcd_control;
#endif
    device->user_data = (void*)&lcd_graphic_ops;

    /* register lcd device */
    rt_device_register(device, "lcd", RT_DEVICE_FLAG_RDWR);

    /* init stm32 spi lcd */
    if (rt_device_init(device) != RT_EOK) {
        result = -RT_ERROR;
        goto __exit;
    }

__exit:
    if (result != RT_EOK) {
        rt_sem_delete(&_lcd.lcd_lock);

        if (_lcd.lcd_info.framebuffer) {
            rt_free_align(_lcd.lcd_info.framebuffer);
        }

        if (_lcd.back_buf) {
            rt_free_align(_lcd.back_buf);
        }

        if (_lcd.front_buf) {
            rt_free_align(_lcd.front_buf);
        }
    }
    return result;
}
INIT_DEVICE_EXPORT(drv_hw_lcd_init);

#ifdef DRV_DEBUG
#ifdef FINSH_USING_MSH
int lcd_test()
{
    struct drv_lcd_device *lcd;
    lcd = (struct drv_lcd_device *)rt_device_find("lcd");

    rt_device_open((rt_device_t)lcd, RT_DEVICE_FLAG_RDWR);

    while (1) {
        /* red */
        for (int i = 0; i < LCD_BUF_SIZE / 2; i++) {
            lcd->lcd_info.framebuffer[2 * i]     = 0x00;
            lcd->lcd_info.framebuffer[2 * i + 1] = 0xF8;
        }
        // lcd_clear(0xFFFF00);
        rt_device_control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);
        rt_thread_mdelay(1000);
        /* green */
        for (int i = 0; i < LCD_BUF_SIZE / 2; i++) {
            lcd->lcd_info.framebuffer[2 * i]     = 0xE0;
            lcd->lcd_info.framebuffer[2 * i + 1] = 0x07;
        }
        // lcd_clear(0xFF00FF);
        rt_device_control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);
        rt_thread_mdelay(1000);
        /* blue */
        for (int i = 0; i < LCD_BUF_SIZE / 2; i++) {
            lcd->lcd_info.framebuffer[2 * i]     = 0x1F;
            lcd->lcd_info.framebuffer[2 * i + 1] = 0x00;
        }
        // lcd_clear(0x00FFFF);
        rt_device_control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);
        rt_thread_mdelay(1000);
    }
}
MSH_CMD_EXPORT(lcd_test, lcd_test);

void lcd_auto_fill(void *para)
{
    int num = (int)para;
    do
    {
        lcd_clear(rt_tick_get());
        rt_thread_mdelay(1000);
    }while(--num);
}

#include <stdlib.h> /* atoi */
void lcd_fill(int argc, void **argv)
{
    static rt_uint8_t lcd_init = 0;
    rt_device_t lcd = RT_NULL;

    if(lcd_init == 0)
    {
        lcd_init = 1;

        lcd = rt_device_find("lcd");
        rt_device_init(lcd);
    }

    if(argc == 1)
    {
        lcd_auto_fill((void *)1);
    }
    else if(argc == 3)
    {
        if(rt_strcmp(argv[1], "-t")==0)
        {
            rt_thread_t tid = RT_NULL;
            tid = rt_thread_create("lcd_fill", lcd_auto_fill, (void *)atoi(argv[2]), 512, 23,10);
            rt_thread_startup(tid);
        }
    }
}
MSH_CMD_EXPORT(lcd_fill, lcd fill test for mcu lcd);
#endif /* FINSH_USING_MSH */
#endif /* DRV_DEBUG */
#endif /* BSP_USING_LCD */
