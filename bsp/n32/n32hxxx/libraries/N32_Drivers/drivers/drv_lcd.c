/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-08     ox-horse     first version
 */

#include <board.h>

#ifdef BSP_USING_LCD
#include <rtdevice.h>
#include <string.h>
#include "n32h7xx_lcdc.h"

#define DRV_DEBUG
#define LOG_TAG "drv.lcd"
#include <drv_log.h>

#define LCD_BUF_SIZE    (BSP_LCD_WIDTH_PIXEL * BSP_LCD_HEIGHT_PIXEL * BSP_BITS_PER_PIXEL / 8U)
#define LCD_DEVICE(dev) (struct drv_lcd_device *)(dev)

struct drv_lcd_device
{
    struct rt_device parent;

    struct rt_device_graphic_info lcd_info;

    struct rt_semaphore lcd_lock;
};

struct drv_lcd_device _lcd;

static rt_err_t drv_lcd_init(struct rt_device *device)
{
    struct drv_lcd_device *lcd = LCD_DEVICE(device);
    /* nothing, right now */
    (void)lcd;
    return RT_EOK;
}

static rt_err_t drv_lcd_control(struct rt_device *device, int cmd, void *args)
{
    struct drv_lcd_device *lcd = LCD_DEVICE(device);

    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
    {
        if (rt_sem_take(&_lcd.lcd_lock, RT_TICK_PER_SECOND / 20) != RT_EOK)
        {
            LOG_E("lcd frame update timeout");
            return -RT_ETIMEOUT;
        }
        LCDC_ReloadConfig(LCDC_VBRELOAD);
    }
    break;

    case RTGRAPHIC_CTRL_GET_INFO:
    {
        struct rt_device_graphic_info *info = (struct rt_device_graphic_info *)args;

        RT_ASSERT(info != RT_NULL);
        info->pixel_format = lcd->lcd_info.pixel_format;
        info->bits_per_pixel = lcd->lcd_info.bits_per_pixel;
        info->width = lcd->lcd_info.width;
        info->height = lcd->lcd_info.height;
        info->framebuffer = lcd->lcd_info.framebuffer;
    }
    break;

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

/**
 * LCDC event interrupt handler. Handles:
 * - Line interrupt (LI): fired at configured scan line position
 * - FIFO underrun interrupt (FU): FIFO empty during active data phase
 * - Register reload interrupt (RR): fired after vertical blanking reload, used for frame sync
 */
void LCD_EV_IRQHandler(void)
{
    rt_interrupt_enter();

    /* Line interrupt: triggered at configured scan line position */
    if (LCDC_GetFlagStatus(LCDC_FLAG_L))
    {
        LCDC_ClearFlag(LCDC_FLAG_L);
    }

    /* FIFO underrun: FIFO empty during active data phase */
    if (LCDC_GetFlagStatus(LCDC_FLAG_FU))
    {
        LCDC_ClearFlag(LCDC_FLAG_FU);
        LOG_E("LCDC FIFO underrun");
    }

    /* Register reload complete: release semaphore for frame sync */
    if (LCDC_GetFlagStatus(LCDC_FLAG_RR))
    {
        LCDC_ClearFlag(LCDC_FLAG_RR);
        rt_sem_release(&_lcd.lcd_lock);
    }

    rt_interrupt_leave();
}

/**
 * LCDC error interrupt handler. Handles:
 * - BUS error interrupt (BE): AHB bus error during transfer
 */
void LCD_ER_IRQHandler(void)
{
    rt_interrupt_enter();

    if (LCDC_GetFlagStatus(LCDC_FLAG_BE))
    {
        LCDC_ClearFlag(LCDC_FLAG_BE);
        LOG_E("LCDC AHB bus error");
    }

    rt_interrupt_leave();
}

/**
 * Configure LCDC power domain, peripheral clocks and pixel clock.
 * This function provides a default configuration for N32H7xx HMI boards.
 * Override this function at the board level if different clock settings are needed.
 */
rt_weak void n32_lcd_clock_config(void)
{
    /* Enable LCDC power domain */
    PWR_MoudlePowerEnable(GRAPHIC_LCDC_PWRCTRL, ENABLE);

    /* Enable LCDC AXI peripheral clocks (LCDC core, low-power, APB, APB low-power) */
    RCC_EnableAXIPeriphClk2(RCC_AXI_PERIPHEN_M7_LCDC | RCC_AXI_PERIPHEN_M7_LCDCLP |
                                RCC_AXI_PERIPHEN_M7_LCDCAPB | RCC_AXI_PERIPHEN_M7_LCDCAPBLP,
                            ENABLE);

    /* Configure pixel clock source: AXI divided by 8 (600MHz / 8 = 75MHz) */
    RCC_ConfigLCDCPixelClk(RCC_LCDCPIXELCLK_SRC_AXIDIV, RCC_LCDCPIXELCLK_AXIDIV8);
}

static rt_err_t n32_lcd_init(struct drv_lcd_device *lcd)
{
    LCDC_InitType LCDC_InitStruct;
    LCDC_Layer_InitType LCDC_Layer_InitStruct;

    /* Configure LCDC power and clocks */
    n32_lcd_clock_config();

    /* Initialize structs with default values */
    LCDC_StructInit(&LCDC_InitStruct);
    LCDC_LayerStructInit(&LCDC_Layer_InitStruct);

    /* Polarity configuration */
    LCDC_InitStruct.LCDC_HSPolarity = LCDC_HSPOLARITY_LOW;
    LCDC_InitStruct.LCDC_VSPolarity = LCDC_VSPOLARITY_LOW;
    LCDC_InitStruct.LCDC_DEPolarity = LCDC_DEPOLARITY_LOW;
    LCDC_InitStruct.LCDC_PCPolarity = LCDC_PCPOLARITY_IPC;

    /* Timing configuration */
    /* Horizontal synchronization width = HSW - 1 */
    LCDC_InitStruct.LCDC_HorizontalSync = BSP_LCD_HSYNC_WIDTH_PIXEL - 1;
    /* Vertical synchronization height = VSW - 1 */
    LCDC_InitStruct.LCDC_VerticalSync = BSP_LCD_VSYNC_HEIGHT_PIXEL - 1;
    /* Accumulated horizontal back porch = HSW + HBP - 1 */
    LCDC_InitStruct.LCDC_AccumulatedHBP = BSP_LCD_HSYNC_WIDTH_PIXEL + BSP_LCD_HBP_PIXEL - 1;
    /* Accumulated vertical back porch = VSW + VBP - 1 */
    LCDC_InitStruct.LCDC_AccumulatedVBP = BSP_LCD_VSYNC_HEIGHT_PIXEL + BSP_LCD_VBP_PIXEL - 1;
    /* Accumulated active width = HSW + HBP + Active Width - 1 */
    LCDC_InitStruct.LCDC_AccumulatedActiveW = BSP_LCD_HSYNC_WIDTH_PIXEL + BSP_LCD_HBP_PIXEL + lcd->lcd_info.width - 1;
    /* Accumulated active height = VSW + VBP + Active Height - 1 */
    LCDC_InitStruct.LCDC_AccumulatedActiveH = BSP_LCD_VSYNC_HEIGHT_PIXEL + BSP_LCD_VBP_PIXEL + lcd->lcd_info.height - 1;
    /* Total height = VSW + VBP + Active Height + VFP - 1 */
    LCDC_InitStruct.LCDC_TotalHeight = LCDC_InitStruct.LCDC_AccumulatedActiveH + BSP_LCD_VFP_PIXEL;
    /* Total width = HSW + HBP + Active Width + HFP - 1 */
    LCDC_InitStruct.LCDC_TotalWidth = LCDC_InitStruct.LCDC_AccumulatedActiveW + BSP_LCD_HFP_PIXEL;

    /* Configure R,G,B component values for LCD background color: black */
    LCDC_InitStruct.LCDC_BackgroundRedValue = 0;
    LCDC_InitStruct.LCDC_BackgroundGreenValue = 0;
    LCDC_InitStruct.LCDC_BackgroundBlueValue = 0;

    /* Initialize LCDC global registers */
    LCDC_Init(&LCDC_InitStruct);

    /* Layer 1 Configuration */

    /* Windowing configuration */
    LCDC_Layer_InitStruct.LCDC_HorizontalStart = BSP_LCD_HSYNC_WIDTH_PIXEL + BSP_LCD_HBP_PIXEL;
    LCDC_Layer_InitStruct.LCDC_HorizontalStop = BSP_LCD_HSYNC_WIDTH_PIXEL + BSP_LCD_HBP_PIXEL + lcd->lcd_info.width - 1;
    LCDC_Layer_InitStruct.LCDC_VerticalStart = BSP_LCD_VSYNC_HEIGHT_PIXEL + BSP_LCD_VBP_PIXEL;
    LCDC_Layer_InitStruct.LCDC_VerticalStop = BSP_LCD_VSYNC_HEIGHT_PIXEL + BSP_LCD_VBP_PIXEL + lcd->lcd_info.height - 1;

    /* Pixel Format configuration */
    if (lcd->lcd_info.pixel_format == RTGRAPHIC_PIXEL_FORMAT_RGB565)
    {
        LCDC_Layer_InitStruct.LCDC_PixelFormat = LCDC_PIXEL_FORMAT_RGB565;
    }
    else if (lcd->lcd_info.pixel_format == RTGRAPHIC_PIXEL_FORMAT_ARGB888)
    {
        LCDC_Layer_InitStruct.LCDC_PixelFormat = LCDC_PIXEL_FORMAT_ARGB8888;
    }
    else if (lcd->lcd_info.pixel_format == RTGRAPHIC_PIXEL_FORMAT_RGB888)
    {
        LCDC_Layer_InitStruct.LCDC_PixelFormat = LCDC_PIXEL_FORMAT_RGB888;
    }
    else
    {
        LOG_E("unsupported pixel format");
        return -RT_ERROR;
    }

    /* Start Address configuration: point LCDC directly at framebuffer (zero-copy) */
    LCDC_Layer_InitStruct.LCDC_CFBStartAdress = (uint32_t)lcd->lcd_info.framebuffer;

    /* Alpha constant (255 = totally opaque) */
    LCDC_Layer_InitStruct.LCDC_ConstantAlpha = 255;

    /* Default Color configuration */
    LCDC_Layer_InitStruct.LCDC_DefaultAlpha = 0;
    LCDC_Layer_InitStruct.LCDC_DefaultColorRed = 0;
    LCDC_Layer_InitStruct.LCDC_DefaultColorGreen = 0;
    LCDC_Layer_InitStruct.LCDC_DefaultColorBlue = 0xFF;

    /* Configure blending factors: Constant Alpha blending */
    LCDC_Layer_InitStruct.LCDC_BlendingFactor1 = LCDC_BLENDING_FACTOR1_CA;
    LCDC_Layer_InitStruct.LCDC_BlendingFactor2 = LCDC_BLENDING_FACTOR2_CA;

    /* Configure the line length, pitch and number of lines */
    LCDC_Layer_InitStruct.LCDC_CFBLineLength = (lcd->lcd_info.width * (lcd->lcd_info.bits_per_pixel / 8)) + 7;
    LCDC_Layer_InitStruct.LCDC_CFBPitch = lcd->lcd_info.width * (lcd->lcd_info.bits_per_pixel / 8);
    LCDC_Layer_InitStruct.LCDC_CFBLineNumber = lcd->lcd_info.height;

    /* Initialize LCDC Layer 1 */
    LCDC_LayerInit(LCDC_Layer1, &LCDC_Layer_InitStruct);

    /* Reload layer config immediately */
    LCDC_LayerReloadConfig(LCDC_Layer1, LCDC_LAYER_IMRELOAD);

    /* Enable Layer 1 */
    LCDC_LayerEnable(LCDC_Layer1, ENABLE);

    /* Reload layer config again after enable */
    LCDC_LayerReloadConfig(LCDC_Layer1, LCDC_LAYER_IMRELOAD);

    /* Enable LCDC */
    LCDC_Enable(ENABLE);

    /* Configure line interrupt to trigger at last active line (reserved for TE sync) */
    LCDC_LINTPConfig(LCDC_InitStruct.LCDC_AccumulatedActiveH);

    /* Enable LCDC event interrupts: RR (frame sync), LI (line interrupt), FU (FIFO underrun) */
    LCDC_ConfigInt(LCDC_INT_RRIEN | LCDC_INT_LIEN | LCDC_INT_FUIEN, ENABLE);

    /* Enable LCDC error interrupts: BE (AHB bus error) */
    LCDC_ConfigInt(LCDC_INT_BEIEN, ENABLE);

    /* Configure NVIC for LCDC event and error interrupts */
    NVIC_SetPriority(LCD_EV_IRQn, 1);
    NVIC_EnableIRQ(LCD_EV_IRQn);
    NVIC_SetPriority(LCD_ER_IRQn, 1);
    NVIC_EnableIRQ(LCD_ER_IRQn);

    LOG_D("LCDC init success");
    return RT_EOK;
}

#if defined(BSP_LCD_BACKLIGHT_USING_PWM)
void turn_on_lcd_backlight(void)
{
    struct rt_device_pwm *pwm_dev;

    /* turn on the LCD backlight */
    pwm_dev = (struct rt_device_pwm *)rt_device_find(BSP_LCD_PWM_DEV_NAME);
    /* pwm frequency: 100K = 10000ns */
    rt_pwm_set(pwm_dev, BSP_LCD_PWM_DEV_CHANNEL, 10000, 10000);
    rt_pwm_enable(pwm_dev, BSP_LCD_PWM_DEV_CHANNEL);
}
#elif defined(BSP_LCD_BACKLIGHT_USING_GPIO)
void turn_on_lcd_backlight(void)
{
    rt_pin_mode(BSP_LCD_BACKLIGHT_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(BSP_LCD_DISPLAY_PIN, PIN_MODE_OUTPUT);

    rt_pin_write(BSP_LCD_DISPLAY_PIN, PIN_HIGH);
    rt_pin_write(BSP_LCD_BACKLIGHT_PIN, PIN_HIGH);
}
#else
void turn_on_lcd_backlight(void)
{
}
#endif

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops lcd_ops = {
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

    /* init lcd_lock semaphore, initial value 1 so the first frame update can proceed */
    result = rt_sem_init(&_lcd.lcd_lock, "lcd_lock", 1, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        LOG_E("init semaphore failed!\n");
        result = -RT_ENOMEM;
        goto __exit;
    }

    /* config LCD dev info */
    _lcd.lcd_info.height = BSP_LCD_HEIGHT_PIXEL;
    _lcd.lcd_info.width = BSP_LCD_WIDTH_PIXEL;
    _lcd.lcd_info.bits_per_pixel = BSP_BITS_PER_PIXEL;

#if defined(BSP_LCD_PIXEL_FORMAT_RGB565)
    _lcd.lcd_info.pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565;
#elif defined(BSP_LCD_PIXEL_FORMAT_ARGB8888)
    _lcd.lcd_info.pixel_format = RTGRAPHIC_PIXEL_FORMAT_ARGB888;
#elif defined(BSP_LCD_PIXEL_FORMAT_RGB888)
    _lcd.lcd_info.pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB888;
#endif

    /* malloc single framebuffer (zero-copy, LCDC points directly to this buffer) */
    _lcd.lcd_info.framebuffer = rt_malloc_align(LCD_BUF_SIZE, 64);
    if (_lcd.lcd_info.framebuffer == RT_NULL)
    {
        LOG_E("init frame buffer failed!\n");
        result = -RT_ENOMEM;
        goto __exit;
    }

    /* memset buff to 0xFF (white) */
    memset(_lcd.lcd_info.framebuffer, 0xFF, LCD_BUF_SIZE);

    device->type = RT_Device_Class_Graphic;
#ifdef RT_USING_DEVICE_OPS
    device->ops = &lcd_ops;
#else
    device->init = drv_lcd_init;
    device->control = drv_lcd_control;
#endif

    /* register lcd device */
    rt_device_register(device, "lcd", RT_DEVICE_FLAG_RDWR);

    /* init N32 LCDC */
    if (n32_lcd_init(&_lcd) != RT_EOK)
    {
        LOG_E("lcd hardware init failed");
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
            rt_free_align(_lcd.lcd_info.framebuffer);
        }
    }
    return result;
}
INIT_DEVICE_EXPORT(drv_lcd_hw_init);


#endif /* BSP_USING_LCD */
