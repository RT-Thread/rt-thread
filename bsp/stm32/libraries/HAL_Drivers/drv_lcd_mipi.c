/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-01     tyustli      the first version
 *
 */
#include <board.h>

#define DBG_TAG "drv_mipi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct lcd_mipi_intf
{
    struct rt_lcd_intf *intf;
    DSI_HandleTypeDef   hdsi;
    DSI_VidCfgTypeDef   hdsi_video;
    LTDC_HandleTypeDef  hltdc;
    LTDC_LayerCfgTypeDef layer_cfg;
};
static struct lcd_mipi_intf mipi_intf;

static rt_err_t _mipi_write_cmd(struct rt_lcd_intf *device, void *p, rt_uint32_t num)
{
    rt_uint8_t *write;
    write = (rt_uint8_t *)p;

    if (num <= 1)
    {
        HAL_DSI_ShortWrite(&mipi_intf.hdsi, mipi_intf.hdsi_video.VirtualChannelID, DSI_DCS_SHORT_PKT_WRITE_P1, write[0], write[1]);
    }
    else
    {
        HAL_DSI_LongWrite(&mipi_intf.hdsi, mipi_intf.hdsi_video.VirtualChannelID, DSI_DCS_LONG_PKT_WRITE, num, write[num], p);
    }

    return RT_EOK;
}

static rt_err_t _mipi_intf_config(struct rt_lcd_intf *device, struct rt_lcd_intf_config *config)
{
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
    DSI_PLLInitTypeDef dsi_pll;
    DSI_PHY_TimerTypeDef dsi_phy;

    rt_uint32_t laneByteClk_kHz = 0;
    rt_uint32_t lcd_clock      = 27429;  

    rt_uint32_t HSA = config->hsync, HFP = config->hfp, HBP = config->hbp, HACT = config->info.width;
    rt_uint32_t VSA = config->vsync, VFP = config->vfp, VBP = config->vbp, VACT = config->info.height;

    /** @brief Enable the LTDC clock */
    __HAL_RCC_LTDC_CLK_ENABLE();
    /** @brief Toggle Sw reset of LTDC IP */
    __HAL_RCC_LTDC_FORCE_RESET();
    __HAL_RCC_LTDC_RELEASE_RESET();

    /** @brief Enable DSI Host and wrapper clocks */
    __HAL_RCC_DSI_CLK_ENABLE();

    /** @brief Soft Reset the DSI Host and wrapper */
    __HAL_RCC_DSI_FORCE_RESET();
    __HAL_RCC_DSI_RELEASE_RESET();

    /* Base address of DSI Host/Wrapper registers to be set before calling De-Init */
    mipi_intf.hdsi.Instance = DSI;

    HAL_DSI_DeInit(&mipi_intf.hdsi);
    dsi_pll.PLLNDIV  = 125;
    dsi_pll.PLLIDF   = DSI_PLL_IN_DIV2;
    dsi_pll.PLLODF   = DSI_PLL_OUT_DIV1;

    laneByteClk_kHz = 62500; 

    /* Set number of Lanes */
    mipi_intf.hdsi.Init.NumberOfLanes = DSI_TWO_DATA_LANES;
    mipi_intf.hdsi.Init.TXEscapeCkdiv = laneByteClk_kHz / 15620;
    HAL_DSI_Init(&mipi_intf.hdsi, &dsi_pll);

    mipi_intf.hdsi_video.VirtualChannelID             = config->channel;
    mipi_intf.hdsi_video.ColorCoding                  = DSI_RGB888;
    mipi_intf.hdsi_video.VSPolarity                   = DSI_VSYNC_ACTIVE_HIGH;
    mipi_intf.hdsi_video.HSPolarity                   = DSI_HSYNC_ACTIVE_HIGH;
    mipi_intf.hdsi_video.DEPolarity                   = DSI_DATA_ENABLE_ACTIVE_HIGH;
    mipi_intf.hdsi_video.Mode                         = DSI_VID_MODE_BURST; /* Mode Video burst ie : one LgP per line */
    mipi_intf.hdsi_video.NullPacketSize               = 0xFFF;
    mipi_intf.hdsi_video.NumberOfChunks               = 0;
    mipi_intf.hdsi_video.PacketSize                   = HACT;
    mipi_intf.hdsi_video.HorizontalSyncActive         = (HSA * laneByteClk_kHz) / lcd_clock;
    mipi_intf.hdsi_video.HorizontalBackPorch          = (HBP * laneByteClk_kHz) / lcd_clock;
    mipi_intf.hdsi_video.HorizontalLine               = ((HACT + HSA + HBP + HFP) * laneByteClk_kHz) / lcd_clock;
    mipi_intf.hdsi_video.VerticalSyncActive           = VSA;
    mipi_intf.hdsi_video.VerticalBackPorch            = VBP;
    mipi_intf.hdsi_video.VerticalFrontPorch           = VFP;
    mipi_intf.hdsi_video.VerticalActive               = VACT;

    /* Enable or disable sending LP command while streaming is active in video mode */
    mipi_intf.hdsi_video.LPCommandEnable              = DSI_LP_COMMAND_ENABLE;
    mipi_intf.hdsi_video.LPLargestPacketSize          = 16;
    mipi_intf.hdsi_video.LPVACTLargestPacketSize      = 0;
    mipi_intf.hdsi_video.LPHorizontalFrontPorchEnable = DSI_LP_HFP_ENABLE;
    mipi_intf.hdsi_video.LPHorizontalBackPorchEnable  = DSI_LP_HBP_ENABLE;
    mipi_intf.hdsi_video.LPVerticalActiveEnable       = DSI_LP_VACT_ENABLE;
    mipi_intf.hdsi_video.LPVerticalFrontPorchEnable   = DSI_LP_VFP_ENABLE;
    mipi_intf.hdsi_video.LPVerticalBackPorchEnable    = DSI_LP_VBP_ENABLE;
    mipi_intf.hdsi_video.LPVerticalSyncActiveEnable   = DSI_LP_VSYNC_ENABLE;

    /* Configure DSI Video mode timings with settings set above */
    HAL_DSI_ConfigVideoMode(&mipi_intf.hdsi, &mipi_intf.hdsi_video);

    /* Configure DSI PHY HS2LP and LP2HS timings */
    dsi_phy.ClockLaneHS2LPTime  = 35;
    dsi_phy.ClockLaneLP2HSTime  = 35;
    dsi_phy.DataLaneHS2LPTime   = 35;
    dsi_phy.DataLaneLP2HSTime   = 35;
    dsi_phy.DataLaneMaxReadTime = 0;
    dsi_phy.StopWaitTime        = 10;
    HAL_DSI_ConfigPhyTimer(&mipi_intf.hdsi, &dsi_phy);
    /*************************End DSI Initialization*******************************/

    /************************LTDC Initialization***********************************/

    /* Timing Configuration */
    mipi_intf.hltdc.Init.HorizontalSync     = (HSA - 1);
    mipi_intf.hltdc.Init.AccumulatedHBP     = (HSA + HBP - 1);
    mipi_intf.hltdc.Init.AccumulatedActiveW = (config->info.width + HSA + HBP - 1);
    mipi_intf.hltdc.Init.TotalWidth         = (config->info.width + HSA + HBP + HFP - 1);

    /* Initialize the LCD pixel width and pixel height */
    mipi_intf.hltdc.LayerCfg->ImageWidth    = config->info.width;
    mipi_intf.hltdc.LayerCfg->ImageHeight   = config->info.height;

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    PeriphClkInitStruct.PLLSAI.PLLSAIN = 384;
    PeriphClkInitStruct.PLLSAI.PLLSAIR = 7;
    PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

    /* Background value */
    mipi_intf.hltdc.Init.Backcolor.Blue     = 0x00;
    mipi_intf.hltdc.Init.Backcolor.Green    = 0x00;
    mipi_intf.hltdc.Init.Backcolor.Red      = 0x00;
    mipi_intf.hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
    mipi_intf.hltdc.Instance = LTDC;

    /* Get LTDC Configuration from DSI Configuration */
    HAL_LTDCEx_StructInitFromVideoConfig(&mipi_intf.hltdc, &(mipi_intf.hdsi_video));

    /* Initialize the LTDC */
    HAL_LTDC_Init(&(mipi_intf.hltdc));

    /* Enable the DSI host and wrapper after the LTDC initialization
     To avoid any synchronization issue, the DSI shall be started after enabling the LTDC */
    HAL_DSI_Start(&(mipi_intf.hdsi));

    mipi_intf.layer_cfg.WindowX0        = 0;
    mipi_intf.layer_cfg.WindowX1        = config->info.width;
    mipi_intf.layer_cfg.WindowY0        = 0;
    mipi_intf.layer_cfg.WindowY1        = config->info.height;
    mipi_intf.layer_cfg.PixelFormat     = LTDC_PIXEL_FORMAT_ARGB8888;
    mipi_intf.layer_cfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
    mipi_intf.layer_cfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
    mipi_intf.layer_cfg.Alpha           = 255;
    mipi_intf.layer_cfg.Alpha0          = 0;
    mipi_intf.layer_cfg.ImageWidth      = config->info.width;
    mipi_intf.layer_cfg.ImageHeight     = config->info.height;
    mipi_intf.layer_cfg.Backcolor.Blue  = 0;
    mipi_intf.layer_cfg.Backcolor.Green = 0;
    mipi_intf.layer_cfg.Backcolor.Red   = 0;
    mipi_intf.layer_cfg.FBStartAdress   = (rt_uint32_t)config->info.framebuffer;

    HAL_LTDC_ConfigLayer(&mipi_intf.hltdc, &mipi_intf.layer_cfg, 0);

    return RT_EOK;
}

static struct rt_lcd_intf_ops mipi_ops =
{
    _mipi_write_cmd,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    _mipi_intf_config,
};

int rt_lcd_intf_init(void)
{
    rt_err_t result;

    result = RT_EOK;

    mipi_intf.intf = (struct rt_lcd_intf *)rt_malloc(sizeof(struct rt_lcd_intf));

    if (mipi_intf.intf == RT_NULL)
    {
        LOG_E("malloc memory failed\n");
        return -RT_ERROR;
    }

    result = rt_lcd_intf_register(mipi_intf.intf, "lcd_intf", &mipi_ops, RT_NULL);

    if (result != RT_EOK)
    {
        LOG_E("register lcd interface device failed error code = %d\n", result);
    }

    return result;
}

INIT_PREV_EXPORT(rt_lcd_intf_init);

/*********************** end of file ***********************/
