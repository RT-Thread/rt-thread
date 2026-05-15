/*
 * Copyright 2019-2021, 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <rtthread.h>
#include "display_support.h"
#include "fsl_gpio.h"
#include "fsl_mipi_dsi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*
 * The DPHY bit clock must be fast enough to send out the pixels, it should be
 * larger than:
 *
 *         (Pixel clock * bit per output pixel) / number of MIPI data lane
 *
 * Here the desired DPHY bit clock multiplied by ( 9 / 8 = 1.125) to ensure
 * it is fast enough.
 */
#define DEMO_MIPI_DPHY_BIT_CLK_ENLARGE(origin) (((origin) / 8) * 9)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void BOARD_PullPanelResetPin(bool pullUp);
static void BOARD_PullPanelPowerPin(bool pullUp);
static void BOARD_InitLcdifClock(void);
static void BOARD_InitMipiDsiClock(void);
static status_t BOARD_DSI_Transfer(dsi_transfer_t *xfer);

/*******************************************************************************
 * Variables
 ******************************************************************************/

static uint32_t mipiDsiTxEscClkFreq_Hz;
static uint32_t mipiDsiDphyBitClkFreq_Hz;
static uint32_t mipiDsiDphyRefClkFreq_Hz;
static uint32_t mipiDsiDpiClkFreq_Hz;

const MIPI_DSI_Type g_mipiDsi = {
    .host = DSI_HOST,
    .apb  = DSI_HOST_APB_PKT_IF,
    .dpi  = DSI_HOST_DPI_INTFC,
    .dphy = DSI_HOST_DPHY_INTFC,
};

#if defined(DISPLAY_USING_RK055AHD091)

static mipi_dsi_device_t dsiDevice = {
    .virtualChannel = 0,
    .xferFunc       = BOARD_DSI_Transfer,
};

static const rm68200_resource_t rm68200Resource = {
    .dsiDevice    = &dsiDevice,
    .pullResetPin = BOARD_PullPanelResetPin,
    .pullPowerPin = BOARD_PullPanelPowerPin,
};

static display_handle_t rm68200Handle = {
    .resource = &rm68200Resource,
    .ops      = &rm68200_ops,
};

#elif defined(DISPLAY_USING_RK055MHD091)

static mipi_dsi_device_t dsiDevice = {
    .virtualChannel = 0,
    .xferFunc       = BOARD_DSI_Transfer,
};

static const hx8394_resource_t hx8394Resource = {
    .dsiDevice    = &dsiDevice,
    .pullResetPin = BOARD_PullPanelResetPin,
    .pullPowerPin = BOARD_PullPanelPowerPin,
};

static display_handle_t hx8394Handle = {
    .resource = &hx8394Resource,
    .ops      = &hx8394_ops,
};

#elif defined(DISPLAY_USING_RK055IQH091)

static mipi_dsi_device_t dsiDevice = {
    .virtualChannel = 0,
    .xferFunc       = BOARD_DSI_Transfer,
};

static const rm68191_resource_t rm68191Resource = {
    .dsiDevice    = &dsiDevice,
    .pullResetPin = BOARD_PullPanelResetPin,
    .pullPowerPin = BOARD_PullPanelPowerPin,
};

static display_handle_t rm68191Handle = {
    .resource = &rm68191Resource,
    .ops      = &rm68191_ops,
};

#endif

#if defined(BSP_USING_LCDIFV2)
static dc_fb_lcdifv2_handle_t s_dcFbLcdifv2Handle = {0};

static const dc_fb_lcdifv2_config_t s_dcFbLcdifv2Config = {
    .lcdifv2       = DEMO_LCDIF,
    .width         = LCD_MIPI_WIDTH,
    .height        = LCD_MIPI_HEIGHT,
    .hsw           = LCD_MIPI_HSW,
    .hfp           = LCD_MIPI_HFP,
    .hbp           = LCD_MIPI_HBP,
    .vsw           = LCD_MIPI_VSW,
    .vfp           = LCD_MIPI_VFP,
    .vbp           = LCD_MIPI_VBP,
    .polarityFlags = DEMO_LCDIF_POL_FLAGS,
    .lineOrder     = kLCDIFV2_LineOrderRGB,
/* CM4 is domain 1, CM7 is domain 0. */
#if (__CORTEX_M <= 4)
    .domain = 1,
#else
    .domain = 0,
#endif
};

const dc_fb_t g_dc = {
    .ops     = &g_dcFbOpsLcdifv2,
    .prvData = &s_dcFbLcdifv2Handle,
    .config  = &s_dcFbLcdifv2Config,
};

#elif defined(BSP_USING_ELCDIF)

dc_fb_elcdif_handle_t s_dcFbElcdifHandle = {0}; /* The handle must be initialized to 0. */

const dc_fb_elcdif_config_t s_dcFbElcdifConfig = {
    .elcdif        = DEMO_LCDIF,
    .width         = LCD_MIPI_WIDTH,
    .height        = LCD_MIPI_HEIGHT,
    .hsw           = LCD_MIPI_HSW,
    .hfp           = LCD_MIPI_HFP,
    .hbp           = LCD_MIPI_HBP,
    .vsw           = LCD_MIPI_VSW,
    .vfp           = LCD_MIPI_VFP,
    .vbp           = LCD_MIPI_VBP,
    .polarityFlags = DEMO_LCDIF_POL_FLAGS,
#if (!DEMO_USE_XRGB8888) && (DEMO_USE_LUT8)
    .dataBus       = kELCDIF_DataBus8Bit,
#else
    .dataBus       = kELCDIF_DataBus24Bit,
#endif
};

const dc_fb_t g_dc = {
    .ops     = &g_dcFbOpsElcdif,
    .prvData = &s_dcFbElcdifHandle,
    .config  = &s_dcFbElcdifConfig,
};
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

static void BOARD_PullPanelResetPin(bool pullUp)
{
    if (pullUp)
    {
        GPIO_PinWrite(BOARD_MIPI_PANEL_RST_GPIO, BOARD_MIPI_PANEL_RST_PIN, 1);
    }
    else
    {
        GPIO_PinWrite(BOARD_MIPI_PANEL_RST_GPIO, BOARD_MIPI_PANEL_RST_PIN, 0);
    }
}

static void BOARD_PullPanelPowerPin(bool pullUp)
{
    if (pullUp)
    {
        GPIO_PinWrite(BOARD_MIPI_PANEL_POWER_GPIO, BOARD_MIPI_PANEL_POWER_PIN, 1);
    }
    else
    {
        GPIO_PinWrite(BOARD_MIPI_PANEL_POWER_GPIO, BOARD_MIPI_PANEL_POWER_PIN, 0);
    }
}

static status_t BOARD_DSI_Transfer(dsi_transfer_t *xfer)
{
    return DSI_TransferBlocking(DEMO_LCD_MIPI, xfer);
}

static void BOARD_InitLcdifClock(void)
{
    /*
     * The pixel clock is (height + VSW + VFP + VBP) * (width + HSW + HFP + HBP) * frame rate.
     *
     * For 60Hz frame rate, the RK055IQH091 pixel clock should be 36MHz.
     * the RK055AHD091 pixel clock should be 62MHz.
     */
    const clock_root_config_t lcdifClockConfig = {
        .clockOff = false,
        .mux      = 4, /*!< PLL_528. */
#if (defined(DISPLAY_USING_RK055AHD091) || defined(DISPLAY_USING_RK055MHD091))
        .div = 9,
#elif defined(DISPLAY_USING_RK055IQH091)
        .div = 15,
#endif
    };

#if defined(BSP_USING_LCDIFV2)
    CLOCK_SetRootClock(kCLOCK_Root_Lcdifv2, &lcdifClockConfig);

    mipiDsiDpiClkFreq_Hz = CLOCK_GetRootClockFreq(kCLOCK_Root_Lcdifv2);

#elif defined(BSP_USING_ELCDIF)

    CLOCK_SetRootClock(kCLOCK_Root_Lcdif, &lcdifClockConfig);

    mipiDsiDpiClkFreq_Hz = CLOCK_GetRootClockFreq(kCLOCK_Root_Lcdif);
#endif
}

static void BOARD_InitMipiDsiClock(void)
{
    uint32_t mipiDsiEscClkFreq_Hz;

    /* RxClkEsc max 60MHz, TxClkEsc 12 to 20MHz. */
    /* RxClkEsc = 528MHz / 11 = 48MHz. */
    /* TxClkEsc = 528MHz / 11 / 4 = 16MHz. */
    const clock_root_config_t mipiEscClockConfig = {
        .clockOff = false,
        .mux      = 4, /*!< PLL_528. */
        .div      = 11,
    };

    CLOCK_SetRootClock(kCLOCK_Root_Mipi_Esc, &mipiEscClockConfig);

    mipiDsiEscClkFreq_Hz = CLOCK_GetRootClockFreq(kCLOCK_Root_Mipi_Esc);

    const clock_group_config_t mipiEscClockGroupConfig = {
        .clockOff = false, .resetDiv = 2, .div0 = 2, /* TX esc clock. */
    };

    CLOCK_SetGroupConfig(kCLOCK_Group_MipiDsi, &mipiEscClockGroupConfig);

    mipiDsiTxEscClkFreq_Hz = mipiDsiEscClkFreq_Hz / 3;

    /* DPHY reference clock, use OSC 24MHz clock. */
    const clock_root_config_t mipiDphyRefClockConfig = {
        .clockOff = false,
        .mux      = 1, /*!< OSC_24M. */
        .div      = 1,
    };

    CLOCK_SetRootClock(kCLOCK_Root_Mipi_Ref, &mipiDphyRefClockConfig);

    mipiDsiDphyRefClkFreq_Hz = BOARD_XTAL0_CLK_HZ;
}

static status_t BOARD_InitLcdPanel(void)
{
    status_t status;

    const gpio_pin_config_t pinConfig = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};

    const display_config_t displayConfig = {
        .resolution   = FSL_VIDEO_RESOLUTION(LCD_MIPI_WIDTH, LCD_MIPI_HEIGHT),
        .hsw          = LCD_MIPI_HSW,
        .hfp          = LCD_MIPI_HFP,
        .hbp          = LCD_MIPI_HBP,
        .vsw          = LCD_MIPI_VSW,
        .vfp          = LCD_MIPI_VFP,
        .vbp          = LCD_MIPI_VBP,
        .controlFlags = 0,
        .dsiLanes     = DEMO_LCD_MIPI_LANE_NUM,
    };

    GPIO_PinInit(BOARD_MIPI_PANEL_POWER_GPIO, BOARD_MIPI_PANEL_POWER_PIN, &pinConfig);
    GPIO_PinInit(BOARD_MIPI_PANEL_BL_GPIO, BOARD_MIPI_PANEL_BL_PIN, &pinConfig);
    GPIO_PinInit(BOARD_MIPI_PANEL_RST_GPIO, BOARD_MIPI_PANEL_RST_PIN, &pinConfig);

#if defined(DISPLAY_USING_RK055AHD091)
    status = RM68200_Init(&rm68200Handle, &displayConfig);
#elif defined(DISPLAY_USING_RK055MHD091)
    status = HX8394_Init(&hx8394Handle, &displayConfig);
#elif defined(DISPLAY_USING_RK055IQH091)
    status = RM68191_Init(&rm68191Handle, &displayConfig);
#endif

    if (status == kStatus_Success)
    {
        GPIO_PinWrite(BOARD_MIPI_PANEL_BL_GPIO, BOARD_MIPI_PANEL_BL_PIN, 1);
    }

    return status;
}

static void BOARD_SetMipiDsiConfig(void)
{
    dsi_config_t dsiConfig;
    dsi_dphy_config_t dphyConfig;

    const dsi_dpi_config_t dpiConfig = {.pixelPayloadSize = LCD_MIPI_WIDTH,
                                        .dpiColorCoding   = kDSI_Dpi24Bit,
                                        .pixelPacket      = kDSI_PixelPacket24Bit,
                                        .videoMode        = kDSI_DpiBurst,
                                        .bllpMode         = kDSI_DpiBllpLowPower,
                                        .polarityFlags    = kDSI_DpiVsyncActiveLow | kDSI_DpiHsyncActiveLow,
                                        .hfp              = LCD_MIPI_HFP,
                                        .hbp              = LCD_MIPI_HBP,
                                        .hsw              = LCD_MIPI_HSW,
                                        .vfp              = LCD_MIPI_VFP,
                                        .vbp              = LCD_MIPI_VBP,
                                        .panelHeight      = LCD_MIPI_HEIGHT,
                                        .virtualChannel   = 0};

    /*
     * dsiConfig.numLanes = 4;
     * dsiConfig.enableNonContinuousHsClk = false;
     * dsiConfig.autoInsertEoTp = true;
     * dsiConfig.numExtraEoTp = 0;
     * dsiConfig.htxTo_ByteClk = 0;
     * dsiConfig.lrxHostTo_ByteClk = 0;
     * dsiConfig.btaTo_ByteClk = 0;
     */
    DSI_GetDefaultConfig(&dsiConfig);
    dsiConfig.numLanes       = DEMO_LCD_MIPI_LANE_NUM;
    dsiConfig.autoInsertEoTp = true;

    /* Init the DSI module. */
    DSI_Init(DEMO_LCD_MIPI, &dsiConfig);

    /* Init DPHY.
     *
     * The DPHY bit clock must be fast enough to send out the pixels, it should be
     * larger than:
     *
     *         (Pixel clock * bit per output pixel) / number of MIPI data lane
     *
     * Here the desired DPHY bit clock multiplied by ( 9 / 8 = 1.125) to ensure
     * it is fast enough.
     *
     * Note that the DSI output pixel is 24bit per pixel.
     */
    mipiDsiDphyBitClkFreq_Hz = mipiDsiDpiClkFreq_Hz * (24 / DEMO_LCD_MIPI_LANE_NUM);

    mipiDsiDphyBitClkFreq_Hz = DEMO_MIPI_DPHY_BIT_CLK_ENLARGE(mipiDsiDphyBitClkFreq_Hz);

    DSI_GetDphyDefaultConfig(&dphyConfig, mipiDsiDphyBitClkFreq_Hz, mipiDsiTxEscClkFreq_Hz);

    mipiDsiDphyBitClkFreq_Hz = DSI_InitDphy(DEMO_LCD_MIPI, &dphyConfig, mipiDsiDphyRefClkFreq_Hz);

    /* Init DPI interface. */
    DSI_SetDpiConfig(DEMO_LCD_MIPI, &dpiConfig, DEMO_LCD_MIPI_LANE_NUM, mipiDsiDpiClkFreq_Hz, mipiDsiDphyBitClkFreq_Hz);
}

status_t BOARD_InitDisplayInterface(void)
{
    CLOCK_EnableClock(kCLOCK_Video_Mux);

#if defined(BSP_USING_LCDIFV2)
    /* LCDIF v2 output to MIPI DSI. */
    VIDEO_MUX->VID_MUX_CTRL.SET = VIDEO_MUX_VID_MUX_CTRL_MIPI_DSI_SEL_MASK;
#elif defined(BSP_USING_ELCDIF)
    /* ELCDIF output to MIPI DSI. */
    VIDEO_MUX->VID_MUX_CTRL.CLR = VIDEO_MUX_VID_MUX_CTRL_MIPI_DSI_SEL_MASK;
#endif

    /* 1. Power on and isolation off. */
    PGMC_BPC4->BPC_POWER_CTRL |= (PGMC_BPC_BPC_POWER_CTRL_PSW_ON_SOFT_MASK | PGMC_BPC_BPC_POWER_CTRL_ISO_OFF_SOFT_MASK);

    /* 2. Assert MIPI reset. */
    IOMUXC_GPR->GPR62 &=
        ~(IOMUXC_GPR_GPR62_MIPI_DSI_PCLK_SOFT_RESET_N_MASK | IOMUXC_GPR_GPR62_MIPI_DSI_ESC_SOFT_RESET_N_MASK |
          IOMUXC_GPR_GPR62_MIPI_DSI_BYTE_SOFT_RESET_N_MASK | IOMUXC_GPR_GPR62_MIPI_DSI_DPI_SOFT_RESET_N_MASK);

    /* 3. Setup clock. */
    BOARD_InitMipiDsiClock();

    /* 4. Deassert PCLK and ESC reset. */
    IOMUXC_GPR->GPR62 |=
        (IOMUXC_GPR_GPR62_MIPI_DSI_PCLK_SOFT_RESET_N_MASK | IOMUXC_GPR_GPR62_MIPI_DSI_ESC_SOFT_RESET_N_MASK);

    /* 5. Configures peripheral. */
    BOARD_SetMipiDsiConfig();

    /* 6. Deassert BYTE and DBI reset. */
    IOMUXC_GPR->GPR62 |=
        (IOMUXC_GPR_GPR62_MIPI_DSI_BYTE_SOFT_RESET_N_MASK | IOMUXC_GPR_GPR62_MIPI_DSI_DPI_SOFT_RESET_N_MASK);

    /* 7. Configure the panel. */
    return BOARD_InitLcdPanel();
}

#if defined(BSP_USING_LCDIFV2)
void LCDIFv2_IRQHandler(void)
{
    DC_FB_LCDIFV2_IRQHandler(&g_dc);
}
#elif defined(BSP_USING_ELCDIF)
void eLCDIF_IRQHandler(void)
{
    DC_FB_ELCDIF_IRQHandler(&g_dc);
}
#endif

status_t BOARD_VerifyDisplayClockSource(void)
{
    status_t status;
    uint32_t srcClkFreq;

    /*
     * In this implementation, the SYSPLL2 (528M) clock is used as the source
     * of LCDIFV2 pixel clock and MIPI DSI ESC clock. The OSC24M clock is used
     * as the MIPI DSI DPHY PLL reference clock. This function checks the clock
     * source are valid. OSC24M is always valid, so only verify the SYSPLL2.
     */
    srcClkFreq = CLOCK_GetPllFreq(kCLOCK_PllSys2);
    if (528 != (srcClkFreq / 1000000))
    {
        status = kStatus_Fail;
    }
    else
    {
        status = kStatus_Success;
    }

    return status;
}

status_t BOARD_PrepareDisplayController(void)
{
    status_t status;

    status = BOARD_VerifyDisplayClockSource();

    if (status != kStatus_Success)
    {
        return status;
    }

    BOARD_InitLcdifClock();

    status = BOARD_InitDisplayInterface();

    if (kStatus_Success == status)
    {
#if defined(BSP_USING_LCDIFV2)
        NVIC_ClearPendingIRQ(LCDIFv2_IRQn);
        NVIC_SetPriority(LCDIFv2_IRQn, 3);
        EnableIRQ(LCDIFv2_IRQn);
#elif defined(BSP_USING_ELCDIF)
        NVIC_ClearPendingIRQ(eLCDIF_IRQn);
        NVIC_SetPriority(eLCDIF_IRQn, 3);
        EnableIRQ(eLCDIF_IRQn);
#endif
    }

    return kStatus_Success;
}
