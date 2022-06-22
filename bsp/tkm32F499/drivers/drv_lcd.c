/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-14    spaceman   first version
 */

#include <board.h>

#ifdef BSP_USING_LCD
#include <lcd_port.h>
#include "lcd.h"
#include "drv_gpio.h"

#define DRV_DEBUG
#define LOG_TAG             "drv.lcd"
#include <drv_log.h>

#define LCD_DEVICE(dev)     (struct drv_lcd_device*)(dev)


static __align(256) volatile rt_uint32_t LTDC_Buf1[LCD_WIDTH * LCD_HEIGHT] = {0x00};
static __align(256) volatile rt_uint32_t LTDC_Buf2[LCD_WIDTH * LCD_HEIGHT] = {0x00};


struct drv_lcd_device
{
    struct rt_device parent;

    struct rt_device_graphic_info lcd_info;

    struct rt_semaphore lcd_lock;

    /* 0:front_buf is being used 1: back_buf is being used*/
    rt_uint8_t cur_buf;
    rt_uint8_t *front_buf;
    rt_uint8_t *back_buf;
};

struct drv_lcd_device _lcd;

static rt_err_t drv_lcd_init(struct rt_device *device)
{
    struct drv_lcd_device *lcd = LCD_DEVICE(device);
    /* nothing, right now */
    lcd = lcd;
    return RT_EOK;
}

static rt_err_t drv_lcd_control(struct rt_device *device, int cmd, void *args)
{
    struct drv_lcd_device *lcd = LCD_DEVICE(device);

    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
    {
        /* update */
        if (_lcd.cur_buf)
        {
            /* back_buf is being used */
            _lcd.lcd_info.framebuffer = _lcd.back_buf;
            /* Configure the color frame buffer start address */
            LTDC->DP_SWT = 0;
            _lcd.cur_buf = 0;
        }
        else
        {
            /* front_buf is being used */
            _lcd.lcd_info.framebuffer = _lcd.front_buf;
            /* Configure the color frame buffer start address */
            LTDC->DP_SWT = 1;
            _lcd.cur_buf = 1;
        }
        rt_sem_take(&_lcd.lcd_lock, RT_TICK_PER_SECOND / 20);
    }
    break;

    case RTGRAPHIC_CTRL_GET_INFO:
    {
        struct rt_device_graphic_info *info = (struct rt_device_graphic_info *)args;

        RT_ASSERT(info != RT_NULL);
        info->pixel_format  = lcd->lcd_info.pixel_format;
        info->bits_per_pixel = LCD_BITS_PER_PIXEL;
        info->width         = lcd->lcd_info.width;
        info->height        = lcd->lcd_info.height;
        info->framebuffer   = lcd->lcd_info.framebuffer;
    }
    break;
    }

    return RT_EOK;
}





rt_err_t stm32_lcd_init(struct drv_lcd_device *lcd)
{
    LCD_Initial((rt_uint32_t)lcd->front_buf, (rt_uint32_t)lcd->back_buf);
    return RT_EOK;
}
#if defined(LCD_BACKLIGHT_USING_PWM)
void turn_on_lcd_backlight(void)
{
    struct rt_device_pwm *pwm_dev;

    /* turn on the LCD backlight */
    pwm_dev = (struct rt_device_pwm *)rt_device_find(LCD_PWM_DEV_NAME);
    /* pwm frequency:100K = 10000ns */
    rt_pwm_set(pwm_dev, LCD_PWM_DEV_CHANNEL, 10000, 10000);
    rt_pwm_enable(pwm_dev, LCD_PWM_DEV_CHANNEL);
}
#elif defined(LCD_BACKLIGHT_USING_GPIO)
void turn_on_lcd_backlight(void)
{
    rt_pin_mode(LCD_BL_GPIO_NUM, PIN_MODE_OUTPUT);
    rt_pin_mode(LCD_DISP_GPIO_NUM, PIN_MODE_OUTPUT);

    rt_pin_write(LCD_DISP_GPIO_NUM, PIN_HIGH);
    rt_pin_write(LCD_BL_GPIO_NUM, PIN_HIGH);
}
#else
void turn_on_lcd_backlight(void)
{

}
#endif

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


void Lcd_ColorBox(struct drv_lcd_device *lcd, rt_uint16_t xStart, rt_uint16_t yStart, rt_uint16_t xLong, rt_uint16_t yLong, rt_uint32_t Color)
{
    rt_uint16_t i, j;
    rt_uint32_t temp;
    rt_uint32_t *LTDC_Buf = (rt_uint32_t *)lcd->lcd_info.framebuffer;
    temp = lcd->lcd_info.height * xStart;
    for (i = 0; i < yLong; i++)
    {
        for (j = 0; j < xLong; j++)
            LTDC_Buf[yStart + i + lcd->lcd_info.height * j + temp] = Color;
    }
    lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);
}

void LCD_Fill_Pic(struct drv_lcd_device *lcd, rt_uint16_t x, rt_uint16_t y, rt_uint16_t pic_H, rt_uint16_t pic_V, rt_uint32_t *pic)
{
    rt_uint32_t *LTDC_Buf = (rt_uint32_t *)lcd->lcd_info.framebuffer;
    rt_uint16_t i, j;
    rt_uint32_t Xstart, k = 0;
    Xstart = lcd->lcd_info.height * x;
    for (i = 0; i < pic_V; i++)
    {
        for (j = 0; j < pic_H; j++)
            LTDC_Buf[Xstart + i + lcd->lcd_info.height * j + y] = pic[k++];
    }
}

void DrawPixel(struct drv_lcd_device *lcd, rt_uint16_t x, rt_uint16_t y, int Color)
{
    rt_uint32_t *LTDC_Buf = (rt_uint32_t *)lcd->lcd_info.framebuffer;
    LTDC_Buf[y + lcd->lcd_info.height * x] = Color;
}




int drv_lcd_hw_init(void)
{
    rt_err_t result = RT_EOK;
    struct rt_device *device = &_lcd.parent;

    /* memset _lcd to zero */
    rt_memset(&_lcd, 0x00, sizeof(_lcd));

    /* init lcd_lock semaphore */
    result = rt_sem_init(&_lcd.lcd_lock, "lcd_lock", 0, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        LOG_E("init semaphore failed!\n");
        result = -RT_ENOMEM;
        goto __exit;
    }

    /* config LCD dev info */
    _lcd.lcd_info.height = LCD_HEIGHT;
    _lcd.lcd_info.width = LCD_WIDTH;
    _lcd.lcd_info.bits_per_pixel = LCD_BITS_PER_PIXEL;
    _lcd.lcd_info.pixel_format = LCD_PIXEL_FORMAT;

    /* malloc memory for Triple Buffering */
    _lcd.back_buf = (rt_uint8_t *)LTDC_Buf1;
    _lcd.front_buf = (rt_uint8_t *)LTDC_Buf2;
    _lcd.lcd_info.framebuffer = _lcd.back_buf;
    if (_lcd.lcd_info.framebuffer == RT_NULL || _lcd.back_buf == RT_NULL || _lcd.front_buf == RT_NULL)
    {
        LOG_E("init frame buffer failed!\n");
        result = -RT_ENOMEM;
        goto __exit;
    }

    /* memset buff to 0xFF */
    rt_memset(_lcd.back_buf, 0xFF, LCD_BUF_SIZE);
    rt_memset(_lcd.front_buf, 0xFF, LCD_BUF_SIZE);

    device->type    = RT_Device_Class_Graphic;
#ifdef RT_USING_DEVICE_OPS
    device->ops     = &lcd_ops;
#else
    device->init    = drv_lcd_init;
    device->control = drv_lcd_control;
#endif

    /* register lcd device */
    rt_device_register(device, "lcd", RT_DEVICE_FLAG_RDWR);

    /* init stm32 LTDC */
    if (stm32_lcd_init(&_lcd) != RT_EOK)
    {
        result = -RT_ERROR;
        goto __exit;
    }
    else
    {
        turn_on_lcd_backlight();
    }
    LOG_D("lcd register successful!");

__exit:
    if (result != RT_EOK)
    {
        rt_sem_detach(&_lcd.lcd_lock);
    }
    return result;
}
INIT_DEVICE_EXPORT(drv_lcd_hw_init);

#ifdef DRV_DEBUG
#ifdef FINSH_USING_MSH
int lcd_test()
{
    struct drv_lcd_device *lcd;
    lcd = (struct drv_lcd_device *)rt_device_find("lcd");
    if(lcd == RT_NULL)
    {
        LOG_E("find lcd device failed!\n");
        return -1;
    }
    rt_uint32_t *LTDC_Buf = RT_NULL;

    LOG_D("red");
    /* red */
    LTDC_Buf = (rt_uint32_t *)lcd->lcd_info.framebuffer;
    for (int i = 0; i < LCD_BUF_SIZE / 4; i++)
        LTDC_Buf[i] = Red;
    lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);
    rt_thread_mdelay(1000);
    LOG_D("green");
    /* green */
    LTDC_Buf = (rt_uint32_t *)lcd->lcd_info.framebuffer;
    for (int i = 0; i < LCD_BUF_SIZE / 4; i++)
        LTDC_Buf[i] = Green;
    lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);
    rt_thread_mdelay(1000);
    LOG_D("blue");
    /* blue */
    LTDC_Buf = (rt_uint32_t *)lcd->lcd_info.framebuffer;
    for (int i = 0; i < LCD_BUF_SIZE / 4; i++)
        LTDC_Buf[i] = Blue;
    lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);

    return 0;
}
MSH_CMD_EXPORT(lcd_test, lcd_test);





#endif /* FINSH_USING_MSH */
#endif /* DRV_DEBUG */
#endif /* BSP_USING_LCD */
