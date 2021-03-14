/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-01-10     zylx         first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef BSP_USING_DSI
#include <lcd_port_dsi.h>
#include <string.h>
#include "drv_gpio.h"
#include "gfxmmu_lut_390x390_24bpp.h"

#define DRV_DEBUG
#define LOG_TAG             "drv.lcd"
#include <drv_log.h>

static DSI_HandleTypeDef    DsiHandle;

struct drv_lcd_dsi_device
{
    struct rt_device parent;

    struct rt_device_graphic_info lcd_info;

    struct rt_semaphore lcd_lock;

    rt_uint8_t *front_buf;
};

struct drv_lcd_dsi_device _lcd;

static DMA2D_HandleTypeDef   Dma2dHandle;
static void CopyInVirtualBuffer(uint32_t *pSrc, uint32_t *pDst, uint16_t x, uint16_t y, uint16_t xsize, uint16_t ysize)
{
    uint32_t destination = (uint32_t)pDst + (y * 390 + x) * 4;
    uint32_t source      = (uint32_t)pSrc;

    Dma2dHandle.Instance          = DMA2D;

    /*##-1- Configure the DMA2D Mode, Color Mode and output offset #############*/
    Dma2dHandle.Init.Mode           = DMA2D_M2M_PFC;
    Dma2dHandle.Init.ColorMode      = DMA2D_OUTPUT_RGB888;
    Dma2dHandle.Init.OutputOffset   = 1024 - 390;
    /* No Output Alpha Inversion */
    Dma2dHandle.Init.AlphaInverted  = DMA2D_REGULAR_ALPHA;
    /* No Output Red & Blue swap */
    Dma2dHandle.Init.RedBlueSwap    = DMA2D_RB_REGULAR;
    /* Regular output byte order */
    Dma2dHandle.Init.BytesSwap      = DMA2D_BYTES_REGULAR;
    /* Pixel mode */
    Dma2dHandle.Init.LineOffsetMode = DMA2D_LOM_PIXELS;

    /*##-2- Foreground Configuration ###########################################*/
    Dma2dHandle.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
    Dma2dHandle.LayerCfg[1].InputOffset    = 0;
    Dma2dHandle.LayerCfg[1].AlphaMode      = DMA2D_NO_MODIF_ALPHA;
    /* Not used */
    Dma2dHandle.LayerCfg[1].InputAlpha     = 0xFF;
    /* No ForeGround Red/Blue swap */
    Dma2dHandle.LayerCfg[1].RedBlueSwap    = DMA2D_RB_REGULAR;
    /* No ForeGround Alpha inversion */
    Dma2dHandle.LayerCfg[1].AlphaInverted  = DMA2D_REGULAR_ALPHA;

    /* DMA2D Initialization */
    if (HAL_DMA2D_Init(&Dma2dHandle) == HAL_OK)
    {
        if (HAL_DMA2D_ConfigLayer(&Dma2dHandle, 1) == HAL_OK)
        {
            if (HAL_DMA2D_Start(&Dma2dHandle, source, destination, xsize, ysize) == HAL_OK)
            {
                /* Polling For DMA transfer */
                HAL_DMA2D_PollForTransfer(&Dma2dHandle, 100);
            }
        }
    }
}

static rt_err_t drv_lcd_init(struct rt_device *device)
{
    struct drv_lcd_dsi_device *lcd = (struct drv_lcd_dsi_device *)device;
    /* nothing, right now */
    lcd = lcd;
    return RT_EOK;
}

static rt_err_t drv_lcd_control(struct rt_device *device, int cmd, void *args)
{
    struct drv_lcd_dsi_device *lcd = (struct drv_lcd_dsi_device *)device;
    rt_uint8_t color = 0;
    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
    {
        /* update */
        rt_sem_take(&_lcd.lcd_lock, RT_TICK_PER_SECOND / 20);
        CopyInVirtualBuffer((uint32_t *)_lcd.lcd_info.framebuffer, (uint32_t *)LAYER_ADDRESS, 0, 0, 390, 390);
        HAL_DSI_Refresh(&DsiHandle);
    }
    break;

    case RTGRAPHIC_CTRL_GET_INFO:
    {
        struct rt_device_graphic_info *info = (struct rt_device_graphic_info *)args;

        RT_ASSERT(info != RT_NULL);
        info->pixel_format  = lcd->lcd_info.pixel_format;
        info->bits_per_pixel = 32;
        info->width         = lcd->lcd_info.width;
        info->height        = lcd->lcd_info.height;
        info->framebuffer   = lcd->lcd_info.framebuffer;
    }
    break;
    }

    return RT_EOK;
}

LTDC_HandleTypeDef   LtdcHandle;
rt_err_t stm32_lcd_init(struct drv_lcd_dsi_device *lcd)
{
    DSI_PLLInitTypeDef      dsiPllInit = {0};
    DSI_PHY_TimerTypeDef    PhyTimings = {0};
    DSI_HOST_TimeoutTypeDef HostTimeouts = {0};
    DSI_LPCmdTypeDef        LPCmd = {0};
    DSI_CmdCfgTypeDef       CmdCfg = {0};
    GFXMMU_HandleTypeDef GfxmmuHandle = {0};
    LTDC_LayerCfgTypeDef    LayerCfg = {0};

    /* GFXMMU CONFIGURATION */
    __HAL_GFXMMU_RESET_HANDLE_STATE(&GfxmmuHandle);
    GfxmmuHandle.Instance = GFXMMU;
    GfxmmuHandle.Init.BlocksPerLine                     = GFXMMU_192BLOCKS;
    GfxmmuHandle.Init.DefaultValue                      = 0xFFFFFFFF;
    GfxmmuHandle.Init.Buffers.Buf0Address               = (uint32_t)lcd->front_buf;
    GfxmmuHandle.Init.Buffers.Buf1Address               = 0;
    GfxmmuHandle.Init.Buffers.Buf2Address               = 0;
    GfxmmuHandle.Init.Buffers.Buf3Address               = 0;
    GfxmmuHandle.Init.Interrupts.Activation             = DISABLE;
    GfxmmuHandle.Init.Interrupts.UsedInterrupts         = GFXMMU_AHB_MASTER_ERROR_IT;
    if (HAL_OK != HAL_GFXMMU_Init(&GfxmmuHandle))
    {
        return -RT_ERROR;
    }

    /* Initialize LUT */
    if (HAL_OK != HAL_GFXMMU_ConfigLut(&GfxmmuHandle, 0, 390, (uint32_t) gfxmmu_lut_config_rgb888))
    {
        return -RT_ERROR;
    }

    /* Disable non visible lines : from line 390 to 1023 (634 lines) */
    if (HAL_OK != HAL_GFXMMU_DisableLutLines(&GfxmmuHandle, 390, 634))
    {
        return -RT_ERROR;
    }

    /**********************/
    /* LTDC CONFIGURATION */
    /**********************/
    /* LTDC initialization */
    __HAL_LTDC_RESET_HANDLE_STATE(&LtdcHandle);
    LtdcHandle.Instance = LTDC;
    LtdcHandle.Init.HSPolarity         = LTDC_HSPOLARITY_AL;
    LtdcHandle.Init.VSPolarity         = LTDC_VSPOLARITY_AL;
    LtdcHandle.Init.DEPolarity         = LTDC_DEPOLARITY_AL;
    LtdcHandle.Init.PCPolarity         = LTDC_PCPOLARITY_IPC;
    /* HSYNC width - 1 */
    LtdcHandle.Init.HorizontalSync     = 0;
    /* VSYNC width - 1 */
    LtdcHandle.Init.VerticalSync       = 0;
    /* HSYNC width + HBP - 1 */
    LtdcHandle.Init.AccumulatedHBP     = 1;
    /* VSYNC width + VBP - 1 */
    LtdcHandle.Init.AccumulatedVBP     = 1;
    /* HSYNC width + HBP + Active width - 1 */
    LtdcHandle.Init.AccumulatedActiveW = 391;
    /* VSYNC width + VBP + Active height - 1 */
    LtdcHandle.Init.AccumulatedActiveH = 391;
    /* HSYNC width + HBP + Active width + HFP - 1 */
    LtdcHandle.Init.TotalWidth         = 392;
    /* VSYNC width + VBP + Active height + VFP - 1 */
    LtdcHandle.Init.TotalHeigh         = 392;
    LtdcHandle.Init.Backcolor.Red      = 0;
    LtdcHandle.Init.Backcolor.Green    = 0;
    LtdcHandle.Init.Backcolor.Blue     = 0;
    LtdcHandle.Init.Backcolor.Reserved = 0xFF;
    if (HAL_LTDC_Init(&LtdcHandle) != HAL_OK)
    {
        return -RT_ERROR;
    }

    /* LTDC layer 1 configuration */
    LayerCfg.WindowX0        = 0;
    LayerCfg.WindowX1        = 390;
    LayerCfg.WindowY0        = 0;
    LayerCfg.WindowY1        = 390;
    LayerCfg.PixelFormat     = LTDC_PIXEL_FORMAT_RGB888;
    LayerCfg.Alpha           = 0xFF;
    LayerCfg.Alpha0          = 0;
    LayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
    LayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
    LayerCfg.FBStartAdress   = LAYER_ADDRESS;
    /* virtual frame buffer contains 768 pixels per line for 24bpp */
    /* (192 blocs * 16) / (24bpp/3) = 1024 pixels per ligne        */
    LayerCfg.ImageWidth      = 1024;
    LayerCfg.ImageHeight     = 390;
    LayerCfg.Backcolor.Red   = 0;
    LayerCfg.Backcolor.Green = 0;
    LayerCfg.Backcolor.Blue  = 0;
    LayerCfg.Backcolor.Reserved = 0xFF;
    if (HAL_LTDC_ConfigLayer(&LtdcHandle, &LayerCfg, LTDC_LAYER_1) != HAL_OK)
    {
        return -RT_ERROR;
    }

    /*********************/
    /* DSI CONFIGURATION */
    /*********************/

    /* DSI initialization */
    __HAL_DSI_RESET_HANDLE_STATE(&DsiHandle);
    DsiHandle.Instance = DSI;
    DsiHandle.Init.AutomaticClockLaneControl = DSI_AUTO_CLK_LANE_CTRL_DISABLE;
    /* We have 1 data lane at 500Mbps => lane byte clock at 500/8 = 62,5 MHZ */
    /* We want TX escape clock at arround 20MHz and under 20MHz so clock division is set to 4 */
    DsiHandle.Init.TXEscapeCkdiv             = 4;
    DsiHandle.Init.NumberOfLanes             = DSI_ONE_DATA_LANE;
    /* We have HSE value at 16 Mhz and we want data lane at 500Mbps */
    dsiPllInit.PLLNDIV = 20;
    dsiPllInit.PLLIDF  = DSI_PLL_IN_DIV1;
    dsiPllInit.PLLODF  = DSI_PLL_OUT_DIV2;
    if (HAL_DSI_Init(&DsiHandle, &dsiPllInit) != HAL_OK)
    {
        return -RT_ERROR;
    }
    /* Tclk-post + Tclk-trail + Ths-exit = [(60ns + 52xUI) + (60ns) + (300ns)]/16ns */
    PhyTimings.ClockLaneHS2LPTime  = 33;
    /* Tlpx + (Tclk-prepare + Tclk-zero) + Tclk-pre = [150ns + 300ns + 8xUI]/16ns */
    PhyTimings.ClockLaneLP2HSTime  = 30;
    /* Ths-trail + Ths-exit = [(60ns + 4xUI) + 100ns]/16ns */
    PhyTimings.DataLaneHS2LPTime   = 11;
    /* Tlpx + (Ths-prepare + Ths-zero) + Ths-sync = [150ns + (145ns + 10xUI) + 8xUI]/16ns */
    PhyTimings.DataLaneLP2HSTime   = 21;
    PhyTimings.DataLaneMaxReadTime = 0;
    PhyTimings.StopWaitTime        = 7;
    if (HAL_DSI_ConfigPhyTimer(&DsiHandle, &PhyTimings) != HAL_OK)
    {
        return -RT_ERROR;
    }

    HostTimeouts.TimeoutCkdiv                 = 1;
    HostTimeouts.HighSpeedTransmissionTimeout = 0;
    HostTimeouts.LowPowerReceptionTimeout     = 0;
    HostTimeouts.HighSpeedReadTimeout         = 0;
    HostTimeouts.LowPowerReadTimeout          = 0;
    HostTimeouts.HighSpeedWriteTimeout        = 0;
    HostTimeouts.HighSpeedWritePrespMode      = 0;
    HostTimeouts.LowPowerWriteTimeout         = 0;
    HostTimeouts.BTATimeout                   = 0;
    if (HAL_DSI_ConfigHostTimeouts(&DsiHandle, &HostTimeouts) != HAL_OK)
    {
        return -RT_ERROR;
    }

    LPCmd.LPGenShortWriteNoP  = DSI_LP_GSW0P_ENABLE;
    LPCmd.LPGenShortWriteOneP = DSI_LP_GSW1P_ENABLE;
    LPCmd.LPGenShortWriteTwoP = DSI_LP_GSW2P_ENABLE;
    LPCmd.LPGenShortReadNoP   = DSI_LP_GSR0P_ENABLE;
    LPCmd.LPGenShortReadOneP  = DSI_LP_GSR1P_ENABLE;
    LPCmd.LPGenShortReadTwoP  = DSI_LP_GSR2P_ENABLE;
    LPCmd.LPGenLongWrite      = DSI_LP_GLW_DISABLE;
    LPCmd.LPDcsShortWriteNoP  = DSI_LP_DSW0P_ENABLE;
    LPCmd.LPDcsShortWriteOneP = DSI_LP_DSW1P_ENABLE;
    LPCmd.LPDcsShortReadNoP   = DSI_LP_DSR0P_ENABLE;
    LPCmd.LPDcsLongWrite      = DSI_LP_DLW_DISABLE;
    LPCmd.LPMaxReadPacket     = DSI_LP_MRDP_DISABLE;
    LPCmd.AcknowledgeRequest  = DSI_ACKNOWLEDGE_DISABLE;
    if (HAL_DSI_ConfigCommand(&DsiHandle, &LPCmd) != HAL_OK)
    {
        return -RT_ERROR;
    }

    CmdCfg.VirtualChannelID      = 0;
#if LCD_BITS_PER_PIXEL == 16
    CmdCfg.ColorCoding           = DSI_RGB565;
#else
    CmdCfg.ColorCoding           = DSI_RGB888;
#endif
    CmdCfg.CommandSize           = 390;
    CmdCfg.TearingEffectSource   = DSI_TE_DSILINK;
    CmdCfg.TearingEffectPolarity = DSI_TE_FALLING_EDGE;
    CmdCfg.HSPolarity            = DSI_HSYNC_ACTIVE_LOW;
    CmdCfg.VSPolarity            = DSI_VSYNC_ACTIVE_LOW;
    CmdCfg.DEPolarity            = DSI_DATA_ENABLE_ACTIVE_HIGH;
    CmdCfg.VSyncPol              = DSI_VSYNC_FALLING;
    CmdCfg.AutomaticRefresh      = DSI_AR_ENABLE;
    CmdCfg.TEAcknowledgeRequest  = DSI_TE_ACKNOWLEDGE_ENABLE;
    if (HAL_DSI_ConfigAdaptedCommandMode(&DsiHandle, &CmdCfg) != HAL_OK)
    {
        return -RT_ERROR;
    }

    /* Disable the Tearing Effect interrupt activated by default on previous function */
    __HAL_DSI_DISABLE_IT(&DsiHandle, DSI_IT_TE);

    if (HAL_DSI_ConfigFlowControl(&DsiHandle, DSI_FLOW_CONTROL_BTA) != HAL_OK)
    {
        return -RT_ERROR;
    }

    /* Enable DSI */
    __HAL_DSI_ENABLE(&DsiHandle);

    /*************************/
    /* LCD POWER ON SEQUENCE */
    /*************************/
    /* Step 1 */
    /* Go to command 2 */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xFE, 0x01);
    /* IC Frame rate control, set power, sw mapping, mux swithc timing command */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x06, 0x62);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x0E, 0x80);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x0F, 0x80);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x10, 0x71);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x13, 0x81);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x14, 0x81);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x15, 0x82);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x16, 0x82);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x18, 0x88);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x19, 0x55);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x1A, 0x10);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x1C, 0x99);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x1D, 0x03);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x1E, 0x03);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x1F, 0x03);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x20, 0x03);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x25, 0x03);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x26, 0x8D);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x2A, 0x03);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x2B, 0x8D);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x36, 0x00);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x37, 0x10);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x3A, 0x00);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x3B, 0x00);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x3D, 0x20);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x3F, 0x3A);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x40, 0x30);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x41, 0x1A);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x42, 0x33);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x43, 0x22);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x44, 0x11);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x45, 0x66);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x46, 0x55);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x47, 0x44);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x4C, 0x33);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x4D, 0x22);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x4E, 0x11);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x4F, 0x66);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x50, 0x55);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x51, 0x44);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x57, 0x33);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x6B, 0x1B);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x70, 0x55);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x74, 0x0C);

    /* Go to command 3 */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xFE, 0x02);
    /* Set the VGMP/VGSP coltage control */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x9B, 0x40);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x9C, 0x00);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x9D, 0x20);

    /* Go to command 4 */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xFE, 0x03);
    /* Set the VGMP/VGSP coltage control */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x9B, 0x40);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x9C, 0x00);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x9D, 0x20);

    /* Go to command 5 */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xFE, 0x04);
    /* VSR command */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x5D, 0x10);
    /* VSR1 timing set */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x00, 0x8D);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x01, 0x00);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x02, 0x01);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x03, 0x01);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x04, 0x10);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x05, 0x01);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x06, 0xA7);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x07, 0x20);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x08, 0x00);
    /* VSR2 timing set */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x09, 0xC2);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x0A, 0x00);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x0B, 0x02);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x0C, 0x01);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x0D, 0x40);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x0E, 0x06);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x0F, 0x01);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x10, 0xA7);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x11, 0x00);
    /* VSR3 timing set */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x12, 0xC2);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x13, 0x00);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x14, 0x02);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x15, 0x01);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x16, 0x40);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x17, 0x07);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x18, 0x01);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x19, 0xA7);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x1A, 0x00);
    /* VSR4 timing set */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x1B, 0x82);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x1C, 0x00);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x1D, 0xFF);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x1E, 0x05);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x1F, 0x60);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x20, 0x02);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x21, 0x01);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x22, 0x7C);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x23, 0x00);
    /* VSR5 timing set */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x24, 0xC2);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x25, 0x00);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x26, 0x04);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x27, 0x02);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x28, 0x70);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x29, 0x05);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x2A, 0x74);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x2B, 0x8D);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x2D, 0x00);
    /* VSR6 timing set */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x2F, 0xC2);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x30, 0x00);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x31, 0x04);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x32, 0x02);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x33, 0x70);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x34, 0x07);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x35, 0x74);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x36, 0x8D);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x37, 0x00);
    /* VSR marping command */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x5E, 0x20);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x5F, 0x31);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x60, 0x54);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x61, 0x76);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x62, 0x98);

    /* Go to command 6 */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xFE, 0x05);
    /* Set the ELVSS voltage */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x05, 0x17);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x2A, 0x04);
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x91, 0x00);

    /* Go back in standard commands */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xFE, 0x00);

    /* Set the Pixel format */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x3A, 0x07);

    /* Set tear off */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, DSI_SET_TEAR_OFF, 0x0);

    /* Set DSI mode to internal timing added vs ORIGINAL for Command mode */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xC2, 0x0);

    /* Set memory address MODIFIED vs ORIGINAL */
    {
        uint8_t InitParam1[4] = {0x00, 0x04, 0x01, 0x89};
        uint8_t InitParam2[4] = {0x00, 0x00, 0x01, 0x85};

        HAL_DSI_LongWrite(&DsiHandle, 0, DSI_DCS_LONG_PKT_WRITE, 4, DSI_SET_COLUMN_ADDRESS, InitParam1);
        HAL_DSI_LongWrite(&DsiHandle, 0, DSI_DCS_LONG_PKT_WRITE, 4, DSI_SET_PAGE_ADDRESS, InitParam2);
    }

    /* Sleep out */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P0, DSI_EXIT_SLEEP_MODE, 0x0);

    HAL_Delay(120);

    /* Set default Brightness */
    HAL_DSI_ShortWrite(&DsiHandle, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x51, BRIGHTNESS_NORMAL);

    /* Set display on */
    if (HAL_DSI_ShortWrite(&DsiHandle,
                           0,
                           DSI_DCS_SHORT_PKT_WRITE_P0,
                           DSI_SET_DISPLAY_ON,
                           0x0) != HAL_OK)
    {
        LOG_E("set display on failed");
        return -RT_ERROR;
    }

    /* Enable DSI Wrapper */
    __HAL_DSI_WRAPPER_ENABLE(&DsiHandle);

    /* NVIC configuration for DSI interrupt that is now enabled */
    HAL_NVIC_SetPriority(DSI_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(DSI_IRQn);

    HAL_DSI_Refresh(&DsiHandle);
    LOG_D("LCD init success");

    return RT_EOK;
}

#if defined(LCD_BACKLIGHT_USING_PWM)
void turn_on_lcd_backlight(void)
{
    struct rt_device_pwm *pwm_dev;

    /* turn on the LCD backlight */
    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    /* pwm frequency:100K = 10000ns */
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, 10000, 10000);
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
}
#elif defined(LCD_BACKLIGHT_USING_GPIO)
void turn_on_lcd_backlight(void)
{
    rt_pin_mode(LCD_BL_GPIO_NUM, PIN_MODE_OUTPUT);

    rt_pin_write(LCD_BL_GPIO_NUM, PIN_HIGH);
}
#endif

void DSI_IRQHandler(void)
{
    HAL_DSI_IRQHandler(&DsiHandle);
}

void HAL_DSI_EndOfRefreshCallback(DSI_HandleTypeDef *hdsi)
{
    rt_sem_release(&_lcd.lcd_lock);
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

    /* malloc memory */
    _lcd.lcd_info.framebuffer = rt_malloc_align(LCD_DSI_BUF_SIZE, 16);
    _lcd.front_buf = rt_malloc_align(LCD_DSI_BUF_SIZE_ROUND, 16);
    if (_lcd.lcd_info.framebuffer == RT_NULL || _lcd.front_buf == RT_NULL)
    {
        LOG_E("init frame buffer failed!\n");
        result = -RT_ENOMEM;
        goto __exit;
    }

    /* memset buff to 0xFF */
    memset(_lcd.lcd_info.framebuffer, 0xFF, LCD_DSI_BUF_SIZE);
    memset(_lcd.front_buf, 0xFF, LCD_DSI_BUF_SIZE_ROUND);

    device->type    = RT_Device_Class_Graphic;
#ifdef RT_USING_DEVICE_OPS
    device->ops     = &lcd_ops;
#else
    device->init    = drv_lcd_init;
    device->control = drv_lcd_control;
#endif

    /* register lcd device */
    rt_device_register(device, "lcd_dsi", RT_DEVICE_FLAG_RDWR);

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
        rt_sem_delete(&_lcd.lcd_lock);

        if (_lcd.lcd_info.framebuffer)
        {
            rt_free(_lcd.lcd_info.framebuffer);
        }

        if (_lcd.front_buf)
        {

            rt_free(_lcd.front_buf);
        }
    }
    return result;
}
INIT_DEVICE_EXPORT(drv_lcd_hw_init);

#if defined(PKG_USING_GUIENGINE)

#include <rtgui/driver.h>
int graphic_device_init(void)
{
    struct rt_device *device;
    device = rt_device_find("lcd_dsi");
    if (device)
    {
        rtgui_graphic_set_device(device);
    }

    return 0;
}
INIT_ENV_EXPORT(graphic_device_init);
#endif

#ifdef DRV_DEBUG
#ifdef FINSH_USING_MSH
int lcd_dsi_test()
{
    struct drv_lcd_dsi_device *lcd;
    lcd = (struct drv_lcd_dsi_device *)rt_device_find("lcd_dsi");
    rt_uint8_t *ptr = lcd->lcd_info.framebuffer;
    while (1)
    {
        /* red */
        for (unsigned long long i = 0; i < LCD_DSI_BUF_SIZE/4; i++)
        {
            ptr[4 * i] = 0x00;
            ptr[4 * i + 1] = 0x00;
            ptr[4 * i + 2] = 0xFF;
            ptr[4 * i + 3] = 0xFF;
        }
        rt_device_control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);
        rt_thread_mdelay(1000);

        /* green */
        for (int i = 0; i < LCD_DSI_BUF_SIZE/4; i++)
        {
            ptr[4 * i] = 0x00;
            ptr[4 * i + 1] = 0xFF;
            ptr[4 * i + 2] = 0x00;
            ptr[4 * i + 3] = 0xFF;
        }
        rt_device_control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);
        rt_thread_mdelay(1000);

        /* blue */
        for (int i = 0; i < LCD_DSI_BUF_SIZE/4; i++)
        {
            ptr[4 * i] = 0xFF;
            ptr[4 * i + 1] = 0x00;
            ptr[4 * i + 2] = 0x00;
            ptr[4 * i + 3] = 0xFF;
        }
        rt_device_control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);
        rt_thread_mdelay(1000);
    }
}
MSH_CMD_EXPORT(lcd_dsi_test, lcd_dsi_test);

//draw a line in screen
void line()
{
    struct drv_lcd_dsi_device *lcd;
    lcd = (struct drv_lcd_dsi_device *)rt_device_find("lcd_dsi");
    rt_uint8_t *ptr = lcd->lcd_info.framebuffer;

        /* red */
        for (unsigned long long i = LCD_DSI_BUF_SIZE/4/2; i <LCD_DSI_BUF_SIZE/4/2+390; i++)
        {
                ptr[4 * i] = 0x00;
                ptr[4 * i + 1] = 0x00;
                ptr[4 * i + 2] = 0xFF;
                ptr[4 * i + 3] = 0xFF;
        }
        rt_device_control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);


}
MSH_CMD_EXPORT(line, line);

#endif /* FINSH_USING_MSH */
#endif /* DRV_DEBUG */
#endif /* BSP_USING_LCD */
