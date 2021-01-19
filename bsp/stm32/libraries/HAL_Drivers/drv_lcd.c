/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-01-08     zylx         first version
 */

#include <board.h>

#ifdef BSP_USING_LCD
#include <lcd_port.h>
#include <string.h>

//#define DRV_DEBUG
#define LOG_TAG             "drv.lcd"
#include <drv_log.h>

#define LCD_DEVICE(dev)     (struct drv_lcd_device*)(dev)

static LTDC_HandleTypeDef LtdcHandle = {0};

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
            memcpy(_lcd.front_buf, _lcd.lcd_info.framebuffer, LCD_BUF_SIZE);
            /* Configure the color frame buffer start address */
            LTDC_LAYER(&LtdcHandle, 0)->CFBAR &= ~(LTDC_LxCFBAR_CFBADD);
            LTDC_LAYER(&LtdcHandle, 0)->CFBAR = (uint32_t)(_lcd.front_buf);
            _lcd.cur_buf = 0;
        }
        else
        {
            /* front_buf is being used */
            memcpy(_lcd.back_buf, _lcd.lcd_info.framebuffer, LCD_BUF_SIZE);
            /* Configure the color frame buffer start address */
            LTDC_LAYER(&LtdcHandle, 0)->CFBAR &= ~(LTDC_LxCFBAR_CFBADD);
            LTDC_LAYER(&LtdcHandle, 0)->CFBAR = (uint32_t)(_lcd.back_buf);
            _lcd.cur_buf = 1;
        }
        rt_sem_take(&_lcd.lcd_lock, RT_TICK_PER_SECOND / 20);
        HAL_LTDC_Relaod(&LtdcHandle, LTDC_SRCR_VBR);
    }
    break;

    case RTGRAPHIC_CTRL_GET_INFO:
    {
        struct rt_device_graphic_info *info = (struct rt_device_graphic_info *)args;

        RT_ASSERT(info != RT_NULL);
        info->pixel_format  = lcd->lcd_info.pixel_format;
        info->bits_per_pixel = 16;
        info->width         = lcd->lcd_info.width;
        info->height        = lcd->lcd_info.height;
        info->framebuffer   = lcd->lcd_info.framebuffer;
    }
    break;
    }

    return RT_EOK;
}

void HAL_LTDC_ReloadEventCallback(LTDC_HandleTypeDef *hltdc)
{
    /* emable line interupt */
    __HAL_LTDC_ENABLE_IT(&LtdcHandle, LTDC_IER_LIE);
}

void HAL_LTDC_LineEventCallback(LTDC_HandleTypeDef *hltdc)
{
    rt_sem_release(&_lcd.lcd_lock);
}

void LTDC_IRQHandler(void)
{
    rt_enter_critical();

    HAL_LTDC_IRQHandler(&LtdcHandle);

    rt_exit_critical();
}

rt_err_t stm32_lcd_init(struct drv_lcd_device *lcd)
{
    LTDC_LayerCfgTypeDef pLayerCfg = {0};

    /* LTDC Initialization -------------------------------------------------------*/

    /* Polarity configuration */
    /* Initialize the horizontal synchronization polarity as active low */
    LtdcHandle.Init.HSPolarity = LTDC_HSPOLARITY_AL;
    /* Initialize the vertical synchronization polarity as active low */
    LtdcHandle.Init.VSPolarity = LTDC_VSPOLARITY_AL;
    /* Initialize the data enable polarity as active low */
    LtdcHandle.Init.DEPolarity = LTDC_DEPOLARITY_AL;
    /* Initialize the pixel clock polarity as input pixel clock */
    LtdcHandle.Init.PCPolarity = LTDC_PCPOLARITY_IPC;

    /* Timing configuration */
    /* Horizontal synchronization width = Hsync - 1 */
    LtdcHandle.Init.HorizontalSync = LCD_HSYNC_WIDTH - 1;
    /* Vertical synchronization height = Vsync - 1 */
    LtdcHandle.Init.VerticalSync = LCD_VSYNC_HEIGHT - 1;
    /* Accumulated horizontal back porch = Hsync + HBP - 1 */
    LtdcHandle.Init.AccumulatedHBP = LCD_HSYNC_WIDTH + LCD_HBP - 1;
    /* Accumulated vertical back porch = Vsync + VBP - 1 */
    LtdcHandle.Init.AccumulatedVBP = LCD_VSYNC_HEIGHT + LCD_VBP - 1;
    /* Accumulated active width = Hsync + HBP + Active Width - 1 */
    LtdcHandle.Init.AccumulatedActiveW = LCD_HSYNC_WIDTH + LCD_HBP + lcd->lcd_info.width - 1 ;
    /* Accumulated active height = Vsync + VBP + Active Heigh - 1 */
    LtdcHandle.Init.AccumulatedActiveH = LCD_VSYNC_HEIGHT + LCD_VBP + lcd->lcd_info.height - 1;
    /* Total height = Vsync + VBP + Active Heigh + VFP - 1 */
    LtdcHandle.Init.TotalHeigh = LtdcHandle.Init.AccumulatedActiveH + LCD_VFP;
    /* Total width = Hsync + HBP + Active Width + HFP - 1 */
    LtdcHandle.Init.TotalWidth = LtdcHandle.Init.AccumulatedActiveW + LCD_HFP;

    /* Configure R,G,B component values for LCD background color */
    LtdcHandle.Init.Backcolor.Blue = 0;
    LtdcHandle.Init.Backcolor.Green = 0;
    LtdcHandle.Init.Backcolor.Red = 0;

    LtdcHandle.Instance = LTDC;

    /* Layer1 Configuration ------------------------------------------------------*/

    /* Windowing configuration */
    pLayerCfg.WindowX0 = 0;
    pLayerCfg.WindowX1 = lcd->lcd_info.width;
    pLayerCfg.WindowY0 = 0;
    pLayerCfg.WindowY1 = lcd->lcd_info.height;

    /* Pixel Format configuration*/
    if (lcd->lcd_info.pixel_format == RTGRAPHIC_PIXEL_FORMAT_RGB565)
    {
        pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
    }
    else if (lcd->lcd_info.pixel_format == RTGRAPHIC_PIXEL_FORMAT_ARGB888)
    {
        pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
    }
    else if (lcd->lcd_info.pixel_format == RTGRAPHIC_PIXEL_FORMAT_RGB888)
    {
        pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB888;
    }
    else if (lcd->lcd_info.pixel_format == RTGRAPHIC_PIXEL_FORMAT_RGB888)
    {
        pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB888;
    }
    else
    {
        LOG_E("unsupported pixel format");
        return -RT_ERROR;
    }

    /* Start Address configuration : frame buffer is located at FLASH memory */
    pLayerCfg.FBStartAdress = (uint32_t)lcd->front_buf;

    /* Alpha constant (255 totally opaque) */
    pLayerCfg.Alpha = 255;

    /* Default Color configuration (configure A,R,G,B component values) */
    pLayerCfg.Alpha0 = 255;
    pLayerCfg.Backcolor.Blue = 0;
    pLayerCfg.Backcolor.Green = 0;
    pLayerCfg.Backcolor.Red = 0;

    /* Configure blending factors */
    /* Constant Alpha value:  pLayerCfg.Alpha / 255
       C: Current Layer Color
       Cs: Background color
       BC = Constant Alpha x C + (1 - Constant Alpha ) x Cs */
    /* BlendingFactor1: Pixel Alpha x Constant Alpha */
    pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
    /* BlendingFactor2: 1 - (Pixel Alpha x Constant Alpha) */
    pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;

    /* Configure the number of lines and number of pixels per line */
    pLayerCfg.ImageWidth = lcd->lcd_info.width;
    pLayerCfg.ImageHeight = lcd->lcd_info.height;

    /* Configure the LTDC */
    if (HAL_LTDC_Init(&LtdcHandle) != HAL_OK)
    {
        LOG_E("LTDC init failed");
        return -RT_ERROR;
    }

    /* Configure the Background Layer*/
    if (HAL_LTDC_ConfigLayer(&LtdcHandle, &pLayerCfg, 0) != HAL_OK)
    {
        LOG_E("LTDC layer init failed");
        return -RT_ERROR;
    }
    else
    {
        /* enable LTDC interrupt */
        HAL_NVIC_SetPriority(LTDC_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(LTDC_IRQn);
        LOG_D("LTDC init success");
        return RT_EOK;
    }
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

int drv_lcd_hw_init(void)
{
    rt_err_t result = RT_EOK;
    struct rt_device *device = &_lcd.parent;

    /* memset _lcd to zero */
    memset(&_lcd, 0x00, sizeof(_lcd));

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
    _lcd.lcd_info.framebuffer = rt_malloc(LCD_BUF_SIZE);
    _lcd.back_buf = rt_malloc(LCD_BUF_SIZE);
    _lcd.front_buf = rt_malloc(LCD_BUF_SIZE);
    if (_lcd.lcd_info.framebuffer == RT_NULL || _lcd.back_buf == RT_NULL || _lcd.front_buf == RT_NULL)
    {
        LOG_E("init frame buffer failed!\n");
        result = -RT_ENOMEM;
        goto __exit;
    }

    /* memset buff to 0xFF */
    memset(_lcd.lcd_info.framebuffer, 0xFF, LCD_BUF_SIZE);
    memset(_lcd.back_buf, 0xFF, LCD_BUF_SIZE);
    memset(_lcd.front_buf, 0xFF, LCD_BUF_SIZE);

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

__exit:
    if (result != RT_EOK)
    {
        rt_sem_detach(&_lcd.lcd_lock);

        if (_lcd.lcd_info.framebuffer)
        {
            rt_free(_lcd.lcd_info.framebuffer);
        }

        if (_lcd.back_buf)
        {
            rt_free(_lcd.back_buf);
        }

        if (_lcd.front_buf)
        {
            rt_free(_lcd.front_buf);
        }
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

    while (1)
    {
        /* red */
        for (int i = 0; i < LCD_BUF_SIZE / 2; i++)
        {
            lcd->lcd_info.framebuffer[2 * i] = 0x00;
            lcd->lcd_info.framebuffer[2 * i + 1] = 0xF8;
        }
        lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);
        rt_thread_mdelay(1000);
        /* green */
        for (int i = 0; i < LCD_BUF_SIZE / 2; i++)
        {
            lcd->lcd_info.framebuffer[2 * i] = 0xE0;
            lcd->lcd_info.framebuffer[2 * i + 1] = 0x07;
        }
        lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);
        rt_thread_mdelay(1000);
        /* blue */
        for (int i = 0; i < LCD_BUF_SIZE / 2; i++)
        {
            lcd->lcd_info.framebuffer[2 * i] = 0x1F;
            lcd->lcd_info.framebuffer[2 * i + 1] = 0x00;
        }
        lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);
        rt_thread_mdelay(1000);
    }
}
MSH_CMD_EXPORT(lcd_test, lcd_test);
#endif /* FINSH_USING_MSH */
#endif /* DRV_DEBUG */
#endif /* BSP_USING_LCD */
