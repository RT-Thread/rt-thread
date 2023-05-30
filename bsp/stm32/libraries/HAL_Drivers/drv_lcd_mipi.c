/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-05-23     WillianChan    first version
 */

#include <board.h>

#ifdef BSP_USING_LCD_MIPI
#include <lcd_port.h>
#include <string.h>

DSI_HandleTypeDef   hdsi;
DSI_VidCfgTypeDef   hdsi_video;
LTDC_HandleTypeDef  hltdc;

struct stm32_lcd
{
    struct rt_device parent;
    struct rt_device_graphic_info info;
};
static struct stm32_lcd lcd;

extern void stm32_mipi_lcd_init(void);
extern void stm32_mipi_lcd_config(rt_uint32_t pixel_format);
extern void stm32_mipi_display_on(void);
extern void stm32_mipi_display_off(void);

rt_err_t ltdc_init(void)
{
    uint32_t lcd_clock      = 27429;
    uint32_t lanebyte_clock = 62500;

    uint32_t HSA = LCD_HSYNC, HFP = LCD_HFP, HBP = LCD_HBP, HACT = LCD_WIDTH;
    uint32_t VSA = LCD_VSYNC, VFP = LCD_VFP, VBP = LCD_VBP, VACT = LCD_HEIGHT;

    stm32_mipi_lcd_init();

    __HAL_RCC_LTDC_CLK_ENABLE();
    __HAL_RCC_LTDC_FORCE_RESET();
    __HAL_RCC_LTDC_RELEASE_RESET();

    __HAL_RCC_DSI_CLK_ENABLE();
    __HAL_RCC_DSI_FORCE_RESET();
    __HAL_RCC_DSI_RELEASE_RESET();

    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    PeriphClkInitStruct.PLLSAI.PLLSAIN       = 384;
    PeriphClkInitStruct.PLLSAI.PLLSAIR       = 7;
    PeriphClkInitStruct.PLLSAIDivR           = RCC_PLLSAIDIVR_2;
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

    HAL_NVIC_SetPriority(LTDC_IRQn,  3, 0);
    HAL_NVIC_SetPriority(DSI_IRQn,   3, 0);

    HAL_NVIC_EnableIRQ(LTDC_IRQn);
    HAL_NVIC_EnableIRQ(DSI_IRQn);

    DSI_PLLInitTypeDef dsi_pll;

    hdsi.Instance = DSI;
    hdsi.Init.NumberOfLanes = DSI_TWO_DATA_LANES;
    hdsi.Init.TXEscapeCkdiv = lanebyte_clock / 15620;

    dsi_pll.PLLNDIV  = 125;
    dsi_pll.PLLIDF   = DSI_PLL_IN_DIV2;
    dsi_pll.PLLODF   = DSI_PLL_OUT_DIV1;

    HAL_DSI_DeInit(&hdsi);
    HAL_DSI_Init(&hdsi, &dsi_pll);

    hdsi_video.VirtualChannelID             = 0;
    hdsi_video.ColorCoding                  = DSI_RGB888;
    hdsi_video.VSPolarity                   = DSI_VSYNC_ACTIVE_HIGH;
    hdsi_video.HSPolarity                   = DSI_HSYNC_ACTIVE_HIGH;
    hdsi_video.DEPolarity                   = DSI_DATA_ENABLE_ACTIVE_HIGH;
    hdsi_video.Mode                         = DSI_VID_MODE_BURST;
    hdsi_video.NullPacketSize               = 0xFFF;
    hdsi_video.NumberOfChunks               = 0;
    hdsi_video.PacketSize                   = HACT;
    hdsi_video.HorizontalSyncActive         = (HSA * lanebyte_clock) / lcd_clock;
    hdsi_video.HorizontalBackPorch          = (HBP * lanebyte_clock) / lcd_clock;
    hdsi_video.HorizontalLine               = ((HACT + HSA + HBP + HFP) * lanebyte_clock) / lcd_clock;
    hdsi_video.VerticalSyncActive           = VSA;
    hdsi_video.VerticalBackPorch            = VBP;
    hdsi_video.VerticalFrontPorch           = VFP;
    hdsi_video.VerticalActive               = VACT;
    hdsi_video.LPCommandEnable              = DSI_LP_COMMAND_ENABLE;
    hdsi_video.LPLargestPacketSize          = 16;
    hdsi_video.LPVACTLargestPacketSize      = 0;
    hdsi_video.LPHorizontalFrontPorchEnable = DSI_LP_HFP_ENABLE;
    hdsi_video.LPHorizontalBackPorchEnable  = DSI_LP_HBP_ENABLE;
    hdsi_video.LPVerticalActiveEnable       = DSI_LP_VACT_ENABLE;
    hdsi_video.LPVerticalFrontPorchEnable   = DSI_LP_VFP_ENABLE;
    hdsi_video.LPVerticalBackPorchEnable    = DSI_LP_VBP_ENABLE;
    hdsi_video.LPVerticalSyncActiveEnable   = DSI_LP_VSYNC_ENABLE;
    HAL_DSI_ConfigVideoMode(&hdsi, &hdsi_video);

    DSI_PHY_TimerTypeDef dsi_phy;

    dsi_phy.ClockLaneHS2LPTime  = 35;
    dsi_phy.ClockLaneLP2HSTime  = 35;
    dsi_phy.DataLaneHS2LPTime   = 35;
    dsi_phy.DataLaneLP2HSTime   = 35;
    dsi_phy.DataLaneMaxReadTime = 0;
    dsi_phy.StopWaitTime        = 10;
    HAL_DSI_ConfigPhyTimer(&hdsi, &dsi_phy);

    hltdc.Instance = LTDC;

    hltdc.Init.PCPolarity         = LTDC_PCPOLARITY_IPC;
    hltdc.Init.HorizontalSync     = (HSA - 1);
    hltdc.Init.AccumulatedHBP     = (HSA + HBP - 1);
    hltdc.Init.AccumulatedActiveW = (LCD_WIDTH + HSA + HBP - 1);
    hltdc.Init.TotalWidth         = (LCD_WIDTH + HSA + HBP + HFP - 1);

    hltdc.LayerCfg->ImageWidth    = LCD_WIDTH;
    hltdc.LayerCfg->ImageHeight   = LCD_HEIGHT;
    hltdc.Init.Backcolor.Blue     = 0x00;
    hltdc.Init.Backcolor.Green    = 0x00;
    hltdc.Init.Backcolor.Red      = 0x00;
    HAL_LTDCEx_StructInitFromVideoConfig(&hltdc, &(hdsi_video));
    HAL_LTDC_Init(&(hltdc));

    HAL_DSI_Start(&(hdsi));

    stm32_mipi_lcd_config(RTGRAPHIC_PIXEL_FORMAT_ARGB888);

    return RT_EOK;
}

void ltdc_layer_init(uint16_t index, uint32_t framebuffer)
{
    LTDC_LayerCfgTypeDef layer_cfg;

    layer_cfg.WindowX0        = 0;
    layer_cfg.WindowX1        = LCD_WIDTH;
    layer_cfg.WindowY0        = 0;
    layer_cfg.WindowY1        = LCD_HEIGHT;
    layer_cfg.PixelFormat     = LTDC_PIXEL_FORMAT_ARGB8888;
    layer_cfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
    layer_cfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
    layer_cfg.Alpha           = 255;
    layer_cfg.Alpha0          = 0;
    layer_cfg.ImageWidth      = LCD_WIDTH;
    layer_cfg.ImageHeight     = LCD_HEIGHT;
    layer_cfg.Backcolor.Blue  = 0;
    layer_cfg.Backcolor.Green = 0;
    layer_cfg.Backcolor.Red   = 0;
    layer_cfg.FBStartAdress   = framebuffer;

    HAL_LTDC_ConfigLayer(&hltdc, &layer_cfg, index);
}

void LTDC_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_LTDC_IRQHandler(&hltdc);
    rt_interrupt_leave();
}

static rt_err_t stm32_lcd_init(rt_device_t device)
{
    lcd.info.width          = LCD_WIDTH;
    lcd.info.height         = LCD_HEIGHT;
    lcd.info.pixel_format   = RTGRAPHIC_PIXEL_FORMAT_ARGB888;
    lcd.info.bits_per_pixel = 32;
    lcd.info.framebuffer    = (void *)rt_malloc_align(LCD_WIDTH * LCD_HEIGHT * (lcd.info.bits_per_pixel / 8), 32);
    memset(lcd.info.framebuffer, 0, LCD_WIDTH * LCD_HEIGHT * (lcd.info.bits_per_pixel / 8));
    ltdc_init();
    ltdc_layer_init(0, (uint32_t)lcd.info.framebuffer);

    return RT_EOK;
}

static rt_err_t stm32_lcd_control(rt_device_t device, int cmd, void *args)
{
    switch(cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
        break;

    case RTGRAPHIC_CTRL_POWERON:
        stm32_mipi_display_on();
        break;

    case RTGRAPHIC_CTRL_POWEROFF:
        stm32_mipi_display_off();
        break;

    case RTGRAPHIC_CTRL_GET_INFO:
        rt_memcpy(args, &lcd.info, sizeof(lcd.info));
        break;

    case RTGRAPHIC_CTRL_SET_MODE:
        break;

    case RTGRAPHIC_CTRL_GET_EXT:
        break;
    }

    return RT_EOK;
}

int rt_hw_lcd_init(void)
{
    rt_err_t ret;

    rt_memset(&lcd, 0x00, sizeof(lcd));

    lcd.parent.type    = RT_Device_Class_Graphic;
    lcd.parent.init    = stm32_lcd_init;
    lcd.parent.open    = RT_NULL;
    lcd.parent.close   = RT_NULL;
    lcd.parent.read    = RT_NULL;
    lcd.parent.write   = RT_NULL;
    lcd.parent.control = stm32_lcd_control;

    lcd.parent.user_data = (void *)&lcd.info;

    ret = rt_device_register(&lcd.parent, "lcd", RT_DEVICE_FLAG_RDWR);

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_lcd_init);


RT_WEAK void stm32_mipi_lcd_init(void)
{
    rt_kprintf("please Implementation function %s\n", __func__);
}

RT_WEAK void stm32_mipi_lcd_config(rt_uint32_t pixel_format)
{
    rt_kprintf("please Implementation function %s\n", __func__);
}

RT_WEAK void stm32_mipi_display_on(void)
{
    rt_kprintf("please Implementation function %s\n", __func__);
}

RT_WEAK void stm32_mipi_display_off(void)
{
    rt_kprintf("please Implementation function %s\n", __func__);
}

#endif /* BSP_USING_LCD_MIPI */
