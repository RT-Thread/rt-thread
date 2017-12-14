/*
 * File      : usart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-17     Tanek        first implementation
 */

#include <rtthread.h>
#include <string.h>
#include "stm32f4xx_hal.h"

#define  RT_HW_LCD_WIDTH                ((uint16_t)800)     /* LCD PIXEL WIDTH            */
#define  RT_HW_LCD_HEIGHT               ((uint16_t)480)     /* LCD PIXEL HEIGHT           */
#define  LCD_800_480_HSYNC              ((uint16_t)96)      /* Horizontal synchronization */
#define  LCD_800_480_HBP                ((uint16_t)10)     /* Horizontal back porch      */
#define  LCD_800_480_HFP                ((uint16_t)10)      /* Horizontal front porch     */
#define  LCD_800_480_VSYNC              ((uint16_t)2)       /* Vertical synchronization   */
#define  LCD_800_480_VBP                ((uint16_t)10)      /* Vertical back porch        */
#define  LCD_800_480_VFP                ((uint16_t)10)      /* Vertical front porch       */

#define LCD_BITS_PER_PIXEL              16


static LTDC_HandleTypeDef hltdc;
static DMA2D_HandleTypeDef hdma2d;

static rt_uint16_t *lcd_framebuffer = RT_NULL;
static rt_uint16_t *_rt_framebuffer = RT_NULL;

static struct rt_device_graphic_info _lcd_info;
static struct rt_device lcd;

void HAL_LTDC_MspInit(LTDC_HandleTypeDef* hltdc)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    if(hltdc->Instance==LTDC)
    {
        /* Peripheral clock enable */
        __HAL_RCC_LTDC_CLK_ENABLE();
        __HAL_RCC_DMA2D_CLK_ENABLE();
        __HAL_RCC_GPIOE_CLK_ENABLE();
        __HAL_RCC_GPIOI_CLK_ENABLE();
        __HAL_RCC_GPIOJ_CLK_ENABLE();
        __HAL_RCC_GPIOK_CLK_ENABLE();
        
        /**LTDC GPIO Configuration    
        PI12     ------> LTDC_HSYNC
        PI13     ------> LTDC_VSYNC
        PI14     ------> LTDC_CLK
        PI15     ------> LTDC_R0
        PJ0     ------> LTDC_R1
        PJ2     ------> LTDC_R3
        PJ3     ------> LTDC_R4
        PJ4     ------> LTDC_R5
        PJ5     ------> LTDC_R6
        PJ6     ------> LTDC_R7
        PJ9     ------> LTDC_G2
        PJ10     ------> LTDC_G3
        PJ11     ------> LTDC_G4
        PK0     ------> LTDC_G5
        PK1     ------> LTDC_G6
        PK2     ------> LTDC_G7
        PJ15     ------> LTDC_B3
        PK3     ------> LTDC_B4
        PK4     ------> LTDC_B5
        PK5     ------> LTDC_B6
        PK6     ------> LTDC_B7
        PK7     ------> LTDC_DE 
        */
        GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
        HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4 
                              |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_9|GPIO_PIN_10 
                              |GPIO_PIN_11|GPIO_PIN_15;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
        HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                              |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
        HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);
    }

}

void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* hltdc)
{
    if(hltdc->Instance==LTDC)
    {
        /* Peripheral clock disable */
        __HAL_RCC_LTDC_CLK_DISABLE();
        
        /**LTDC GPIO Configuration    
        PE5     ------> LTDC_G0
        PE6     ------> LTDC_G1
        PI12     ------> LTDC_HSYNC
        PI13     ------> LTDC_VSYNC
        PI14     ------> LTDC_CLK
        PI15     ------> LTDC_R0
        PJ0     ------> LTDC_R1
        PJ1     ------> LTDC_R2
        PJ2     ------> LTDC_R3
        PJ3     ------> LTDC_R4
        PJ4     ------> LTDC_R5
        PJ5     ------> LTDC_R6
        PJ6     ------> LTDC_R7
        PJ9     ------> LTDC_G2
        PJ10     ------> LTDC_G3
        PJ11     ------> LTDC_G4
        PK0     ------> LTDC_G5
        PK1     ------> LTDC_G6
        PK2     ------> LTDC_G7
        PJ12     ------> LTDC_B0
        PJ13     ------> LTDC_B1
        PJ14     ------> LTDC_B2
        PJ15     ------> LTDC_B3
        PK3     ------> LTDC_B4
        PK4     ------> LTDC_B5
        PK5     ------> LTDC_B6
        PK6     ------> LTDC_B7
        PK7     ------> LTDC_DE 
        */
        HAL_GPIO_DeInit(GPIOE, GPIO_PIN_5|GPIO_PIN_6);

        HAL_GPIO_DeInit(GPIOI, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

        HAL_GPIO_DeInit(GPIOJ, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                              |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_9 
                              |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13 
                              |GPIO_PIN_14|GPIO_PIN_15);

        HAL_GPIO_DeInit(GPIOK, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                              |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
    }
}

static void LTDC_CLK_Config(void)
{
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
    
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    PeriphClkInitStruct.PLLSAI.PLLSAIN = 100;
    PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
    PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
        RT_ASSERT(RT_NULL);
    }
}

/* LTDC init function */
static void MX_LTDC_Init(void)
{
    LTDC_LayerCfgTypeDef pLayerCfg;

    hltdc.Instance = LTDC;
    hltdc.Init.HSPolarity         = LTDC_HSPOLARITY_AL;
    hltdc.Init.VSPolarity         = LTDC_VSPOLARITY_AL;
    hltdc.Init.DEPolarity         = LTDC_DEPOLARITY_AL;
    hltdc.Init.PCPolarity         = LTDC_PCPOLARITY_IPC;
    
    hltdc.Init.Backcolor.Blue     = 0;
    hltdc.Init.Backcolor.Green    = 0;
    hltdc.Init.Backcolor.Red      = 0;
    
    hltdc.Init.HorizontalSync     = LCD_800_480_HSYNC;
    hltdc.Init.VerticalSync       = LCD_800_480_VSYNC;
    hltdc.Init.AccumulatedHBP     = LCD_800_480_HSYNC + LCD_800_480_HBP;
    hltdc.Init.AccumulatedVBP     = LCD_800_480_VSYNC + LCD_800_480_VBP;
    hltdc.Init.AccumulatedActiveW = RT_HW_LCD_WIDTH + LCD_800_480_HSYNC + LCD_800_480_HBP;
    hltdc.Init.AccumulatedActiveH = RT_HW_LCD_HEIGHT + LCD_800_480_VSYNC + LCD_800_480_VBP;
    hltdc.Init.TotalWidth         = RT_HW_LCD_WIDTH + LCD_800_480_HSYNC + LCD_800_480_HBP + LCD_800_480_HFP;
    hltdc.Init.TotalHeigh         = RT_HW_LCD_HEIGHT + LCD_800_480_VSYNC + LCD_800_480_VBP + LCD_800_480_VFP;
    
    hltdc.LayerCfg->ImageHeight   = RT_HW_LCD_HEIGHT;
    hltdc.LayerCfg->ImageWidth    = RT_HW_LCD_WIDTH;

    if (HAL_LTDC_Init(&hltdc) != HAL_OK)
    {
        RT_ASSERT(RT_NULL);
    }
    
    lcd_framebuffer = rt_malloc_align(sizeof(rt_uint16_t) * RT_HW_LCD_WIDTH * RT_HW_LCD_HEIGHT, 32);
    RT_ASSERT(lcd_framebuffer != RT_NULL);
    rt_memset(lcd_framebuffer, 0, sizeof(rt_uint16_t) * RT_HW_LCD_WIDTH * RT_HW_LCD_HEIGHT);

    pLayerCfg.WindowX0 = 0;
    pLayerCfg.WindowX1 = RT_HW_LCD_WIDTH;
    pLayerCfg.WindowY0 = 0;
    pLayerCfg.WindowY1 = RT_HW_LCD_HEIGHT;
    pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
    pLayerCfg.Alpha = 0xFF;
    pLayerCfg.Alpha0 = 0xFF;
    pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
    pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR1_CA;
    pLayerCfg.FBStartAdress = (uint32_t)lcd_framebuffer;
    pLayerCfg.ImageWidth = RT_HW_LCD_WIDTH;
    pLayerCfg.ImageHeight = RT_HW_LCD_HEIGHT;
    pLayerCfg.Backcolor.Blue = 0;
    pLayerCfg.Backcolor.Green = 0;
    pLayerCfg.Backcolor.Red = 0;
    if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
    {
        RT_ASSERT(RT_NULL);
    }
}

/* DMA2D init function */
static void MX_DMA2D_Init(void)
{

    hdma2d.Instance = DMA2D;
    hdma2d.Init.Mode = DMA2D_M2M;
    hdma2d.Init.ColorMode = DMA2D_OUTPUT_RGB565;
    hdma2d.Init.OutputOffset = 0;
    hdma2d.LayerCfg[0].InputOffset = 0;
    hdma2d.LayerCfg[0].InputColorMode = DMA2D_INPUT_RGB565;
    hdma2d.LayerCfg[0].AlphaMode = DMA2D_NO_MODIF_ALPHA;
    hdma2d.LayerCfg[0].InputAlpha = 0;
    if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
    {
        RT_ASSERT(RT_NULL);
    }

    if (HAL_DMA2D_ConfigLayer(&hdma2d, 0) != HAL_OK)
    {
        RT_ASSERT(RT_NULL);
    }
}

static void lcd_backlight_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
}

static rt_err_t rt_lcd_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rt_lcd_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_lcd_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rt_lcd_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
    {        
        memcpy((void *)lcd_framebuffer, _rt_framebuffer, sizeof(rt_uint16_t)*RT_HW_LCD_HEIGHT * RT_HW_LCD_WIDTH);
    }
    break;
    
    case RTGRAPHIC_CTRL_POWERON:
        break;
    
    case RTGRAPHIC_CTRL_POWEROFF:
        break;
    
    case RTGRAPHIC_CTRL_GET_INFO:
        memcpy(args, &_lcd_info, sizeof(_lcd_info));
        break;
    
    case RTGRAPHIC_CTRL_SET_MODE:
        break;
    }

    return RT_EOK;
}

int stm32_hw_lcd_init(void)
{
    _rt_framebuffer = rt_malloc_align(sizeof(rt_uint16_t) * RT_HW_LCD_WIDTH * RT_HW_LCD_HEIGHT, 32);
    if (_rt_framebuffer == RT_NULL) 
        return -1; /* no memory yet */
    
    LTDC_CLK_Config();
    MX_LTDC_Init();
    lcd_backlight_init();
    MX_DMA2D_Init();
    
    _lcd_info.bits_per_pixel = LCD_BITS_PER_PIXEL;
    _lcd_info.pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565;		// RTGRAPHIC_PIXEL_FORMAT_ARGB888
    _lcd_info.framebuffer = (void *)_rt_framebuffer;
    _lcd_info.width = RT_HW_LCD_WIDTH;
    _lcd_info.height = RT_HW_LCD_HEIGHT;
    
        /* init device structure */
    lcd.type = RT_Device_Class_Graphic;
    lcd.init = rt_lcd_init;
    lcd.open = rt_lcd_open;
    lcd.close = rt_lcd_close;
    lcd.read = NULL;
    lcd.write = NULL;
    lcd.control = rt_lcd_control;
    lcd.user_data = (void *)&_lcd_info;
    
    /* register lcd device to RT-Thread */
    rt_device_register(&lcd, "lcd", RT_DEVICE_FLAG_RDWR);
    
    return 0;
}
INIT_APP_EXPORT(stm32_hw_lcd_init);
