/*
 * Copyright 2020-2022,2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_mipi_dsi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.mipi_dsi_split"
#endif

/* The timeout cycles to wait for DSI state machine idle. */
#ifndef FSL_MIPI_DSI_IDLE_TIMEOUT
#define FSL_MIPI_DSI_IDLE_TIMEOUT 0x1000U
#endif

/* PLL CN should be in the range of 1 to 32. */
#define DSI_DPHY_PLL_CN_MIN 1U
#define DSI_DPHY_PLL_CN_MAX 32U

/* PLL refClk / CN should be in the range of 24M to 30M. */
#define DSI_DPHY_PLL_REFCLK_CN_MIN 24000000U
#define DSI_DPHY_PLL_REFCLK_CN_MAX 30000000U

/* PLL CM should be in the range of 16 to 255. */
#define DSI_DPHY_PLL_CM_MIN 16U
#define DSI_DPHY_PLL_CM_MAX 255U

#define PKT_CONTROL_WORD_COUNT(wc)  ((uint32_t)(wc) << 0U)
#define PKT_CONTROL_VC(vc)          ((uint32_t)(vc) << 16U)
#define PKT_CONTROL_HEADER_TYPE(ht) ((uint32_t)(ht) << 18U)
#define PKT_CONTROL_HS_MASK         (1UL << 24U)
#define PKT_CONTROL_BTA_MASK        (1UL << 25U)
#define PKT_CONTROL_BTA_ONLY_MASK   (1UL << 26U)

/* Macro used for D-PHY timing setting. */
#define DSI_THS_ZERO_BYTE_CLK_BASE         6U
#define DSI_TCLK_ZERO_BYTE_CLK_BASE        3U
#define DSI_THS_PREPARE_HALF_ESC_CLK_BASE  2U
#define DSI_TCLK_PREPARE_HALF_ESC_CLK_BASE 2U

#define DSI_THS_PREPARE_HALF_ESC_CLK_MIN  (DSI_THS_PREPARE_HALF_ESC_CLK_BASE)
#define DSI_TCLK_PREPARE_HALF_ESC_CLK_MIN (DSI_TCLK_PREPARE_HALF_ESC_CLK_BASE)

#define DSI_THS_PREPARE_HALF_ESC_CLK_MAX  (5U)
#define DSI_TCLK_PREPARE_HALF_ESC_CLK_MAX (3U)

/* Convert ns to byte clock. */
#define DSI_NS_TO_BYTE_CLK(ns, byte_clk_khz) ((ns) * (byte_clk_khz) / 1000000U)
/* Convert ns+UI to byte clock. */
#define DSI_NS_UI_TO_BYTE_CLK(ns, UI, byte_clk_khz) ((((ns) * (byte_clk_khz)) + ((UI)*125000U)) / 1000000U)

/* Packet overhead for HSA, HFP, HBP */
#define DSI_HSA_OVERHEAD_BYTE 10UL /* HSS + HSA header + HSA CRC. */
#define DSI_HFP_OVERHEAD_BYTE 12UL /* RGB data packet CRC + HFP header + HFP CRC. */
#define DSI_HBP_OVERHEAD_BYTE 10UL /* HSE + HBP header + HBP CRC + RGB data packet header */

#define DSI_INT_STATUS_TRIGGER_MASK                                                                           \
    ((uint32_t)kDSI_InterruptGroup1ResetTriggerReceived | (uint32_t)kDSI_InterruptGroup1TearTriggerReceived | \
     (uint32_t)kDSI_InterruptGroup1AckTriggerReceived)
#define DSI_INT_STATUS_ERROR_REPORT_MASK (0xFFFFU << 9U)

#if (defined(FSL_FEATURE_DSI_CSR_OFFSET) && (0 != FSL_FEATURE_DSI_CSR_OFFSET))
#if (defined(FSL_FEATURE_LDB_COMBO_PHY) && (0 != FSL_FEATURE_LDB_COMBO_PHY))
typedef MIPI_DSI_LVDS_COMBO_CSR_Type MIPI_DSI_CSR_Type;
#define MIPI_DSI_CSR_ULPS_CTRL(csr)      ((csr)->ULPS_CTRL)
#define MIPI_DSI_CSR_ULPS_CTRL_ULPS_MASK MIPI_DSI_LVDS_COMBO_CSR_ULPS_CTRL_TX_ULPS_MASK
#define MIPI_DSI_CSR_PXL2DPI(csr)        ((csr)->PXL2DPI_CTRL)
#else
#define MIPI_DSI_CSR_ULPS_CTRL(csr)      ((csr)->TX_ULPS_ENABLE)
#define MIPI_DSI_CSR_ULPS_CTRL_ULPS_MASK MIPI_DSI_TX_ULPS_ENABLE_TX_ULPS_ENABLE_MASK
#define MIPI_DSI_CSR_PXL2DPI(csr)        ((csr)->PXL2DPI_CONFIG)
#endif

#define DSI_GET_CSR(dsi_base) ((MIPI_DSI_CSR_Type *)(((uint32_t)(dsi_base)) - (uint32_t)FSL_FEATURE_DSI_CSR_OFFSET))
#endif

/*! @brief Typedef for MIPI DSI interrupt handler. */
typedef void (*dsi_isr_t)(const MIPI_DSI_Type *base, dsi_handle_t *handle);

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined(DSI_HOST_DSI_IRQS)
/* Array of DSI IRQ number. */
static const IRQn_Type s_dsiIRQ[] = DSI_HOST_DSI_IRQS;
#endif
/*! @brief Pointers to MIPI DSI bases for each instance. */
static DSI_HOST_Type *const s_dsiBases[] = DSI_HOST_BASE_PTRS;
/*! @brief MIPI DSI internal handle pointer array */
static dsi_handle_t *s_dsiHandle[ARRAY_SIZE(s_dsiBases)];
/*! @brief Pointer to IRQ handler. */
static dsi_isr_t s_dsiIsr;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to MIPI DSI clocks for each instance. */
static const clock_ip_name_t s_dsiClocks[] = MIPI_DSI_HOST_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get the MIPI DSI host controller instance from peripheral base address.
 *
 * @param base MIPI DSI peripheral base address.
 * @return MIPI DSI instance.
 */
static uint32_t DSI_GetInstance(const MIPI_DSI_Type *base);

#if !((defined(FSL_FEATURE_MIPI_NO_DPHY_PLL)) && (0 != FSL_FEATURE_MIPI_DSI_HOST_NO_DPHY_PLL))
/*!
 * @brief Convert the D-PHY PLL CN to the value could be set to register.
 *
 * @param cn The CN value.
 * @return The register value.
 */
static uint8_t DSI_EncodeDphyPllCn(uint8_t cn);

/*!
 * @brief Convert the D-PHY PLL CM to the value could be set to register.
 *
 * @param cm The CM value.
 * @return The register value.
 */
static uint8_t DSI_EncodeDphyPllCm(uint8_t cm);

/*!
 * @brief Calculate the D-PHY PLL dividers to generate the desired output frequency.
 *
 * Calculate the PLL dividers to generate the most close desired output PLL frequency.
 *
 * txHsBitClk_Hz = refClkFreq_Hz * CM / (CN * CO).
 * CM: 16 ~ 255
 * CN: 1 ~ 32
 * CO: 1, 2, 4, 8
 *
 * @param cn The CN value, convert using @ref DSI_EncodeDphyPllCn before setting to register.
 * @param cm The CM value, convert using @ref DSI_EncodeDphyPllCm before setting to register.
 * @param co The CO value, could set to register directly.
 * @param refClkFreq_Hz The D-PHY input reference clock frequency (REF_CLK).
 * @param desiredOutFreq_Hz Desired PLL output frequency.
 * @return The actually output frequency using the returned dividers. If could not
 * find suitable dividers, return 0.
 */
static uint32_t DSI_DphyGetPllDivider(
    uint32_t *cn, uint32_t *cm, uint32_t *co, uint32_t refClkFreq_Hz, uint32_t desiredOutFreq_Hz);
#endif

/*!
 * @brief Clear the RX FIFO.
 *
 * @param base MIPI DSI host peripheral base address.
 */
static void DSI_ApbClearRxFifo(const MIPI_DSI_Type *base);

/*!
 * @brief Handle the DSI transfer result.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param xfer The transfer definition.
 * @param intFlags1 Interrupt flag group 1.
 * @param intFlags2 Interrupt flag group 2.
 * @retval kStatus_Success No error happens.
 * @retval kStatus_Timeout Hardware timeout detected.
 * @retval kStatus_DSI_RxDataError RX data error.
 * @retval kStatus_DSI_ErrorReportReceived Error Report packet received.
 * @retval kStatus_DSI_Fail Transfer failed for other reasons.
 */
static status_t DSI_HandleResult(const MIPI_DSI_Type *base,
                                 uint32_t intFlags1,
                                 uint32_t intFlags2,
                                 dsi_transfer_t *xfer);

/*!
 * @brief Prepare for the DSI APB transfer.
 *
 * This function fills TX data to DSI TX FIFO and sets the packet control
 * register. Packet transfer could start using @ref DSI_SendApbPacket after
 * this function.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param xfer The transfer definition.
 * @retval kStatus_Success It is ready to start transfer.
 * @retval kStatus_DSI_NotSupported The transfer format is not supported.
 */
static status_t DSI_PrepareApbTransfer(const MIPI_DSI_Type *base, dsi_transfer_t *xfer);

/*!
 * @brief Convert time from nano-second to count of byte clock.
 *
 * @param ns Time in nano-second.
 * @param byteclk_khz Byte clock frequency in kHz.
 * @return Time in byte clock.
 */
static uint32_t DSI_NsToByteClk(uint32_t ns, uint32_t byteclk_khz)
{
    return (ns * byteclk_khz) / 1000000UL;
}

/*!
 * @brief Convert the time to count of byte clock.
 *
 * The time is the sum of nano-second specified by ns and count of UI.
 *
 * @param ns Time in nano-second.
 * @param UI Count of UI.
 * @param byteclk_khz Byte clock frequency in kHz.
 * @return Time in byte clock.
 */
static uint32_t DSI_NsUiToByteClk(uint32_t ns, uint32_t UI, uint32_t byteclk_khz)
{
    return ((ns * byteclk_khz) + (UI * 125000UL)) / 1000000UL;
}

/*******************************************************************************
 * Code
 ******************************************************************************/

static uint32_t DSI_GetInstance(const MIPI_DSI_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_dsiBases); instance++)
    {
        if (MSDK_REG_SECURE_ADDR(s_dsiBases[instance]) == MSDK_REG_SECURE_ADDR(base->host))
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_dsiBases));

    return instance;
}

#if !((defined(FSL_FEATURE_MIPI_NO_DPHY_PLL)) && (0 != FSL_FEATURE_MIPI_DSI_HOST_NO_DPHY_PLL))
static uint8_t DSI_EncodeDphyPllCn(uint8_t cn)
{
    uint8_t ret = 0U;

    assert((cn >= 1U) && (cn <= 32U));

    if (1U == cn)
    {
        ret = 0x1FU;
    }
    else
    {
        ret = (uint8_t)((0x65BD44E0UL >> ((uint32_t)cn - 2U)) & 0x1FU);
    }

    return ret;
}

static uint8_t DSI_EncodeDphyPllCm(uint8_t cm)
{
    uint8_t ret = 0U;

    assert(cm >= 16U);

    if (cm <= 31U)
    {
        ret = 0xE0U | cm;
    }
    else if (cm <= 63U)
    {
        ret = 0xC0U | (cm & 0x1FU);
    }
    else if (cm <= 127U)
    {
        ret = 0x80U | (cm & 0x3FU);
    }
    else
    {
        ret = cm & 0xCFU;
    }

    return ret;
}

static uint32_t DSI_DphyGetPllDivider(
    uint32_t *cn, uint32_t *cm, uint32_t *co, uint32_t refClkFreq_Hz, uint32_t desiredOutFreq_Hz)
{
    uint32_t cnCur;
    uint32_t cmCur;
    uint32_t coShiftCur;
    uint32_t pllFreqCur;
    uint32_t diffCur;
    uint32_t vcoFreq;
    uint32_t refClk_CN;
    uint32_t diff             = 0xFFFFFFFFU;
    uint32_t pllFreqCandidate = 0U;

    /* CO available values are 1, 2, 4, 8, so the shift values are 0, 1, 2, 3.  */
    for (coShiftCur = 0U; coShiftCur <= 3U; coShiftCur++)
    {
        /* Desired VCO output frequency. */
        vcoFreq = desiredOutFreq_Hz << coShiftCur;

        /* If desired VCO output frequency is too small, try larger CO value. */
        if (vcoFreq < DSI_DPHY_PLL_VCO_MIN)
        {
            continue;
        }

        /* If desired VCO output frequency is too large, search finished. */
        if (vcoFreq > DSI_DPHY_PLL_VCO_MAX)
        {
            break;
        }

        /* Now search the best CN and CM to generate disired VCO output frequency. */
        for (cnCur = DSI_DPHY_PLL_CN_MIN; cnCur <= DSI_DPHY_PLL_CN_MAX; cnCur++)
        {
            /* REF_CLK / CN. */
            refClk_CN = refClkFreq_Hz / cnCur;

            /* If desired REF_CLK / CN frequency is too large, try larger CN value. */
            if (refClk_CN > DSI_DPHY_PLL_REFCLK_CN_MAX)
            {
                continue;
            }

            /* If desired REF_CLK / CN frequency is too small, stop search. */
            if (refClk_CN < DSI_DPHY_PLL_REFCLK_CN_MIN)
            {
                break;
            }

            /* Get the CM most close. */
            cmCur = (vcoFreq + (refClk_CN / 2U)) / refClk_CN;

            /* If calculated value is (DSI_DPHY_PLL_CM_MAX + 1), use DSI_DPHY_PLL_CM_MAX. */
            if ((DSI_DPHY_PLL_CM_MAX + 1U) == cmCur)
            {
                cmCur = DSI_DPHY_PLL_CM_MAX;
            }

            if ((cmCur < DSI_DPHY_PLL_CM_MIN) || (cmCur > DSI_DPHY_PLL_CM_MAX))
            {
                continue;
            }

            /* Output frequency using current dividers. */
            pllFreqCur = (refClk_CN * cmCur) >> coShiftCur;

            if (pllFreqCur > desiredOutFreq_Hz)
            {
                diffCur = (pllFreqCur - desiredOutFreq_Hz);
            }
            else
            {
                diffCur = (desiredOutFreq_Hz - pllFreqCur);
            }

            /* If the dividers is better. */
            if (diffCur < diff)
            {
                diff             = diffCur;
                *cm              = cmCur;
                *cn              = cnCur;
                *co              = coShiftCur;
                pllFreqCandidate = pllFreqCur;

                /* If the output PLL frequency is exactly the disired value, return directly. */
                if (0U == diff)
                {
                    break;
                }
            }
        }

        /* If the output PLL frequency is exactly the disired value, return directly. */
        if (0U == diff)
        {
            break;
        }
    }

    return pllFreqCandidate;
}
#endif

static void DSI_ApbClearRxFifo(const MIPI_DSI_Type *base)
{
    volatile uint32_t dummy = 0U;
    uint32_t level          = base->apb->PKT_FIFO_RD_LEVEL;

    while (0U != (level--))
    {
        dummy = base->apb->PKT_RX_PAYLOAD;
    }

    (void)dummy;
}

/*!
 * brief Initializes an MIPI DSI host with the user configuration.
 *
 * This function initializes the MIPI DSI host with the configuration, it should
 * be called first before other MIPI DSI driver functions.
 *
 * param base MIPI DSI host peripheral base address.
 * param config Pointer to a user-defined configuration structure.
 */
void DSI_Init(const MIPI_DSI_Type *base, const dsi_config_t *config)
{
    assert(NULL != config);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && (0 != FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL))
    (void)CLOCK_EnableClock(s_dsiClocks[DSI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    DSI_HOST_Type *host = base->host;

#if (defined(FSL_FEATURE_DSI_CSR_OFFSET) && (0 != FSL_FEATURE_DSI_CSR_OFFSET))
    MIPI_DSI_CSR_Type *csr = DSI_GET_CSR(base);
    if (config->enableTxUlps)
    {
        MIPI_DSI_CSR_ULPS_CTRL(csr) = MIPI_DSI_CSR_ULPS_CTRL_ULPS_MASK;
    }
    else
    {
        MIPI_DSI_CSR_ULPS_CTRL(csr) = 0U;
    }
#endif

    host->CFG_NUM_LANES = config->numLanes - 1UL;

    if (config->enableNonContinuousHsClk)
    {
        host->CFG_NONCONTINUOUS_CLK = 0x01U;
    }
    else
    {
        host->CFG_NONCONTINUOUS_CLK = 0x00U;
    }

    if (config->autoInsertEoTp)
    {
        host->CFG_AUTOINSERT_EOTP = 0x01U;
    }
    else
    {
        host->CFG_AUTOINSERT_EOTP = 0x00U;
    }

    host->CFG_EXTRA_CMDS_AFTER_EOTP = config->numExtraEoTp;
    host->CFG_HTX_TO_COUNT          = config->htxTo_ByteClk;
    host->CFG_LRX_H_TO_COUNT        = config->lrxHostTo_ByteClk;
    host->CFG_BTA_H_TO_COUNT        = config->btaTo_ByteClk;

    DSI_ApbClearRxFifo(base);

    /* Disable all interrupts by default, user could enable
     * the desired interrupts later.
     */
    base->apb->IRQ_MASK  = 0xFFFFFFFFU;
    base->apb->IRQ_MASK2 = 0xFFFFFFFFU;
}

/*!
 * brief Deinitializes an MIPI DSI host.
 *
 * This function should be called after all bother MIPI DSI driver functions.
 *
 * param base MIPI DSI host peripheral base address.
 */
void DSI_Deinit(const MIPI_DSI_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && (0 != FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL))
    (void)CLOCK_DisableClock(s_dsiClocks[DSI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Get the default configuration to initialize the MIPI DSI host.
 *
 * The default value is:
 * code
    config->numLanes = 4;
    config->enableNonContinuousHsClk = false;
    config->enableTxUlps = false;
    config->autoInsertEoTp = true;
    config->numExtraEoTp = 0;
    config->htxTo_ByteClk = 0;
    config->lrxHostTo_ByteClk = 0;
    config->btaTo_ByteClk = 0;
   endcode
 *
 * param config Pointer to a user-defined configuration structure.
 */
void DSI_GetDefaultConfig(dsi_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->numLanes                 = 4;
    config->enableNonContinuousHsClk = false;
    config->enableTxUlps             = false;
    config->autoInsertEoTp           = true;
    config->numExtraEoTp             = 0;
    config->htxTo_ByteClk            = 0;
    config->lrxHostTo_ByteClk        = 0;
    config->btaTo_ByteClk            = 0;
}

/*!
 * brief Configure the DPI interface core.
 *
 * This function sets the DPI interface configuration, it should be used in
 * video mode.
 *
 * param base MIPI DSI host peripheral base address.
 * param config Pointer to the DPI interface configuration.
 * param numLanes Lane number, should be same with the setting in ref dsi_dpi_config_t.
 * param dpiPixelClkFreq_Hz The DPI pixel clock frequency in Hz.
 * param dsiHsBitClkFreq_Hz The DSI high speed bit clock frequency in Hz. It is
 * the same with DPHY PLL output.
 */
void DSI_SetDpiConfig(const MIPI_DSI_Type *base,
                      const dsi_dpi_config_t *config,
                      uint8_t numLanes,
                      uint32_t dpiPixelClkFreq_Hz,
                      uint32_t dsiHsBitClkFreq_Hz)
{
    assert(NULL != config);

    /* coefficient DPI event size to number of DSI bytes. */
    float coff = ((float)numLanes * (float)dsiHsBitClkFreq_Hz) / ((float)dpiPixelClkFreq_Hz * 8.0f);

    DSI_HOST_DPI_INTFC_Type *dpi = base->dpi;

#if (defined(FSL_FEATURE_DSI_CSR_OFFSET) && (0 != FSL_FEATURE_DSI_CSR_OFFSET))
    MIPI_DSI_CSR_Type *csr    = DSI_GET_CSR(base);
    MIPI_DSI_CSR_PXL2DPI(csr) = (uint32_t)config->dpiColorCoding;
#endif

    dpi->PIXEL_PAYLOAD_SIZE     = config->pixelPayloadSize;
    dpi->INTERFACE_COLOR_CODING = (uint32_t)config->dpiColorCoding;
    dpi->PIXEL_FORMAT           = (uint32_t)config->pixelPacket;
    dpi->VIDEO_MODE             = (uint32_t)config->videoMode;

    if (kDSI_DpiBllpLowPower == config->bllpMode)
    {
        dpi->BLLP_MODE         = 0x1U;
        dpi->USE_NULL_PKT_BLLP = 0x0U;
    }
    else if (kDSI_DpiBllpBlanking == config->bllpMode)
    {
        dpi->BLLP_MODE         = 0x0U;
        dpi->USE_NULL_PKT_BLLP = 0x0U;
    }
    else
    {
        dpi->BLLP_MODE         = 0x0U;
        dpi->USE_NULL_PKT_BLLP = 0x1U;
    }

    if (0U != (config->polarityFlags & (uint32_t)kDSI_DpiVsyncActiveHigh))
    {
        dpi->VSYNC_POLARITY = 0x01U;
    }
    else
    {
        dpi->VSYNC_POLARITY = 0x00U;
    }

    if (0U != (config->polarityFlags & (uint32_t)kDSI_DpiHsyncActiveHigh))
    {
        dpi->HSYNC_POLARITY = 0x01U;
    }
    else
    {
        dpi->HSYNC_POLARITY = 0x00U;
    }

    dpi->HFP                   = (uint32_t)((float)config->hfp * coff - (float)DSI_HFP_OVERHEAD_BYTE);
    dpi->HBP                   = (uint32_t)((float)config->hbp * coff - (float)DSI_HBP_OVERHEAD_BYTE);
    dpi->HSA                   = (uint32_t)((float)config->hsw * coff - (float)DSI_HSA_OVERHEAD_BYTE);
    dpi->PIXEL_FIFO_SEND_LEVEL = config->pixelPayloadSize;

    dpi->VBP = config->vbp;
    dpi->VFP = config->vfp;

    dpi->VACTIVE = config->panelHeight;

    /* TODO: Configure VC if it is available. */
}

/*!
 * brief Initializes the D-PHY
 *
 * This function configures the D-PHY timing and setups the D-PHY PLL based on
 * user configuration. The configuration structure could be got by the function
 * ref DSI_GetDphyDefaultConfig.
 *
 * param base MIPI DSI host peripheral base address.
 * param config Pointer to the D-PHY configuration.
 * param refClkFreq_Hz The REFCLK frequency in Hz.
 * return The actual D-PHY PLL output frequency. If could not configure the
 * PLL to the target frequency, the return value is 0.
 */
uint32_t DSI_InitDphy(const MIPI_DSI_Type *base, const dsi_dphy_config_t *config, uint32_t refClkFreq_Hz)
{
    assert(NULL != config);

    DSI_HOST_NXP_FDSOI28_DPHY_INTFC_Type *dphy = base->dphy;
    DSI_HOST_Type *host                        = base->host;

#if !((defined(FSL_FEATURE_MIPI_NO_DPHY_PLL)) && (0 != FSL_FEATURE_MIPI_DSI_HOST_NO_DPHY_PLL))
    uint32_t cn = 0x0U;
    uint32_t cm = 0x0U;
    uint32_t co = 0x0U;
    uint32_t outputPllFreq;

    outputPllFreq = DSI_DphyGetPllDivider(&cn, &cm, &co, refClkFreq_Hz, config->txHsBitClk_Hz);

    /* If could not find dividers for the output PLL frequency. */
    if (0U == outputPllFreq)
    {
        return 0U;
    }

    /* Set the DPHY parameters. */
    dphy->CN = (uint32_t)DSI_EncodeDphyPllCn((uint8_t)cn);
    dphy->CM = (uint32_t)DSI_EncodeDphyPllCm((uint8_t)cm);
    dphy->CO = co;
#endif

    /* Set the timing parameters. */
    dphy->M_PRG_HS_PREPARE  = (uint32_t)config->tHsPrepare_HalfEscClk - DSI_THS_PREPARE_HALF_ESC_CLK_BASE;
    dphy->MC_PRG_HS_PREPARE = (uint32_t)config->tClkPrepare_HalfEscClk - DSI_TCLK_PREPARE_HALF_ESC_CLK_BASE;
    dphy->M_PRG_HS_ZERO     = (uint32_t)config->tHsZero_ByteClk - DSI_THS_ZERO_BYTE_CLK_BASE;
    dphy->MC_PRG_HS_ZERO    = (uint32_t)config->tClkZero_ByteClk - DSI_TCLK_ZERO_BYTE_CLK_BASE;
    dphy->M_PRG_HS_TRAIL    = config->tHsTrail_ByteClk;
    dphy->MC_PRG_HS_TRAIL   = config->tClkTrail_ByteClk;

    host->CFG_T_PRE   = config->tClkPre_ByteClk;
    host->CFG_T_POST  = config->tClkPost_ByteClk;
    host->CFG_TX_GAP  = config->tHsExit_ByteClk;
    host->CFG_TWAKEUP = config->tWakeup_EscClk;

#if defined(MIPI_RTERM_SEL_dphy_rterm_sel_MASK)
    dphy->RTERM_SEL = MIPI_RTERM_SEL_dphy_rterm_sel_MASK;
#endif
#if defined(MIPI_TX_RCAL_dphy_tx_rcal_MASK)
    dphy->TX_RCAL = 1;
#endif
    dphy->RXLPRP = 1;
    dphy->RXCDRP = 1;

    /* Auto power down the inactive lanes. */
    dphy->AUTO_PD_EN = 0x1U;

    dphy->TST = 0x25U;

#if !((defined(FSL_FEATURE_MIPI_NO_PLL) && (0 != FSL_FEATURE_MIPI_DSI_HOST_NO_PLL)))
    /* Power up the PLL. */
    dphy->PD_PLL = 0U;

    /* Wait for the PLL lock. */
    while (0UL == dphy->LOCK)
    {
    }
#endif

    /* Power up the DPHY. */
    dphy->PD_TX = 0U;

#if !((defined(FSL_FEATURE_MIPI_NO_PLL) && (0 != FSL_FEATURE_MIPI_DSI_HOST_NO_PLL)))
    return outputPllFreq;
#else
    return config->txHsBitClk_Hz;
#endif
}

/*!
 * brief Deinitializes the D-PHY
 *
 * Power down the D-PHY PLL and shut down D-PHY.
 *
 * param base MIPI DSI host peripheral base address.
 */
void DSI_DeinitDphy(const MIPI_DSI_Type *base)
{
#if !((defined(FSL_FEATURE_MIPI_NO_DPHY_PLL)) && (0 != FSL_FEATURE_MIPI_DSI_HOST_NO_DPHY_PLL))
    /* Power down the PLL. */
    base->dphy->PD_PLL = 1U;
#endif

    /* Power down the DPHY. */
    base->dphy->PD_TX = 1U;
}

/*!
 * brief Get the default D-PHY configuration.
 *
 * Gets the default D-PHY configuration, the timing parameters are set according
 * to D-PHY specification. User could use the configuration directly, or change
 * some parameters according to the special device.
 *
 * param config Pointer to the D-PHY configuration.
 * param txHsBitClk_Hz High speed bit clock in Hz.
 * param txEscClk_Hz Esc clock in Hz.
 */
void DSI_GetDphyDefaultConfig(dsi_dphy_config_t *config, uint32_t txHsBitClk_Hz, uint32_t txEscClk_Hz)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    uint32_t byteClkFreq_kHz = txHsBitClk_Hz / 8U / 1000U;
    uint32_t txEscClk_kHz    = txEscClk_Hz / 1000U;

    config->txHsBitClk_Hz = txHsBitClk_Hz;

    /* THS-EXIT in byte clock. At least 100ns. */
    config->tHsExit_ByteClk = (uint8_t)(DSI_NsToByteClk(100U, byteClkFreq_kHz) + 1U);

    /* T-WAKEUP. At least 1ms. */
    config->tWakeup_EscClk = (txEscClk_Hz / 1000U) + 1U;

    /* THS-PREPARE. 40ns+4*UI to 85ns+6*UI. */
    config->tHsPrepare_HalfEscClk =
        (uint8_t)(((40U * txEscClk_kHz * 2U) / 1000000U) + (4U * txEscClk_Hz * 2U / txHsBitClk_Hz) + 1U);
    if (config->tHsPrepare_HalfEscClk < DSI_THS_PREPARE_HALF_ESC_CLK_MIN)
    {
        config->tHsPrepare_HalfEscClk = DSI_THS_PREPARE_HALF_ESC_CLK_MIN;
    }
    else if (config->tHsPrepare_HalfEscClk > DSI_THS_PREPARE_HALF_ESC_CLK_MAX)
    {
        config->tHsPrepare_HalfEscClk = DSI_THS_PREPARE_HALF_ESC_CLK_MAX;
    }
    else
    {
        /* For MISRA check. */
    }

    /* TCLK-PREPARE. 38ns to 95ns. */
    config->tClkPrepare_HalfEscClk = (uint8_t)((38U * txEscClk_kHz * 2U) / 1000000U + 1U);
    if (config->tClkPrepare_HalfEscClk < DSI_TCLK_PREPARE_HALF_ESC_CLK_MIN)
    {
        config->tClkPrepare_HalfEscClk = DSI_TCLK_PREPARE_HALF_ESC_CLK_MIN;
    }
    else if (config->tClkPrepare_HalfEscClk > DSI_TCLK_PREPARE_HALF_ESC_CLK_MAX)
    {
        config->tClkPrepare_HalfEscClk = DSI_TCLK_PREPARE_HALF_ESC_CLK_MAX;
    }
    else
    {
        /* For MISRA check. */
    }

    /* THS-ZERO, At least 105ns+6*UI. */
    config->tHsZero_ByteClk = (uint8_t)(DSI_NsUiToByteClk(105U, 6U, byteClkFreq_kHz) + 1U);
    if (config->tHsZero_ByteClk < DSI_THS_ZERO_BYTE_CLK_BASE)
    {
        config->tHsZero_ByteClk = DSI_THS_ZERO_BYTE_CLK_BASE;
    }

    /* TCLK-ZERO, At least 262ns. */
    config->tClkZero_ByteClk = (uint8_t)(DSI_NsToByteClk(262U, byteClkFreq_kHz) + 1U);
    if (config->tClkZero_ByteClk < DSI_TCLK_ZERO_BYTE_CLK_BASE)
    {
        config->tClkZero_ByteClk = DSI_TCLK_ZERO_BYTE_CLK_BASE;
    }

    /* THS-TRAIL, 60ns+4*UI to 105ns+12UI. */
    /* Due to IP design, extra 4*UI should be added. */
    config->tHsTrail_ByteClk = (uint8_t)(DSI_NsUiToByteClk(60U, 8U, byteClkFreq_kHz) + 1U);

    /* TCLK-TRAIL, at least 60ns. */
    /* Due to IP design, extra 4*UI should be added. */
    config->tClkTrail_ByteClk = (uint8_t)(DSI_NsUiToByteClk(60U, 4U, byteClkFreq_kHz) + 1U);

    /*
     * T_LPX + T_CLK-PREPARE + T_CLK-ZERO + T_CLK-PRE
     * T_LPX >= 50ns
     * T_CLK-PREPARE >= 38ns
     * T_CLK-ZERO >= 262ns
     * T_CLK-PRE >= 8*UI
     */
    config->tClkPre_ByteClk = (uint8_t)(DSI_NsUiToByteClk(88U, 8U, byteClkFreq_kHz) + 1U) + config->tClkZero_ByteClk;

    /*
     * T_CLK-POST + T_CLK-TRAIL
     * T_CLK-POST >= 60ns + 52*UI.
     * T_CLK-TRAIL >= 60ns
     */
    config->tClkPost_ByteClk = (uint8_t)(DSI_NsUiToByteClk(60U, 52U, byteClkFreq_kHz) + 1U) + config->tClkTrail_ByteClk;
}

/*!
 * brief Configure the APB packet to send.
 *
 * This function configures the next APB packet transfer. After configuration,
 * the packet transfer could be started with function ref DSI_SendApbPacket.
 * If the packet is long packet, Use ref DSI_WriteApbTxPayload to fill the payload
 * before start transfer.
 *
 * param base MIPI DSI host peripheral base address.
 * param wordCount For long packet, this is the byte count of the payload.
 * For short packet, this is (data1 << 8) | data0.
 * param virtualChannel Virtual channel.
 * param dataType The packet data type, (DI).
 * param flags The transfer control flags, see ref _dsi_transfer_flags.
 */
void DSI_SetApbPacketControl(
    const MIPI_DSI_Type *base, uint16_t wordCount, uint8_t virtualChannel, dsi_tx_data_type_t dataType, uint8_t flags)
{
    uint32_t pktCtrl = PKT_CONTROL_WORD_COUNT(wordCount) | PKT_CONTROL_HEADER_TYPE(dataType);

#if defined(DSI_HOST_PKT_CONTROL_VC)
    pktCtrl |= (uint32_t)DSI_HOST_PKT_CONTROL_VC(virtualChannel);
#endif

    if (0U != (flags & (uint8_t)kDSI_TransferUseHighSpeed))
    {
        pktCtrl |= PKT_CONTROL_HS_MASK;
    }

    if (0U != (flags & (uint8_t)kDSI_TransferPerformBTA))
    {
        pktCtrl |= PKT_CONTROL_BTA_MASK;
    }

    base->apb->PKT_CONTROL = pktCtrl;
}

/*!
 * brief Fill the long APB packet payload.
 *
 * Write the long packet payload to TX FIFO.
 *
 * param base MIPI DSI host peripheral base address.
 * param payload Pointer to the payload.
 * param payloadSize Payload size in byte.
 */
void DSI_WriteApbTxPayload(const MIPI_DSI_Type *base, const uint8_t *payload, uint16_t payloadSize)
{
    DSI_WriteApbTxPayloadExt(base, payload, payloadSize, false, 0U);
}

void DSI_WriteApbTxPayloadExt(
    const MIPI_DSI_Type *base, const uint8_t *payload, uint16_t payloadSize, bool sendDscCmd, uint8_t dscCmd)
{
    uint32_t firstWord;
    uint16_t i;
    uint16_t payloadSizeLocal   = payloadSize;
    const uint8_t *payloadLocal = payload;

    DSI_HOST_APB_PKT_IF_Type *apb = base->apb;

    if (sendDscCmd)
    {
        payloadSizeLocal += 1U;
    }

    assert(payloadSizeLocal <= FSL_DSI_TX_MAX_PAYLOAD_BYTE);

    /* The first 4-byte. */
    if (sendDscCmd)
    {
        firstWord = dscCmd;
    }
    else
    {
        firstWord = *payloadLocal;
        payloadLocal++;
    }

    payloadSizeLocal--;

    for (i = 1U; i < 4U; i++)
    {
        if (payloadSizeLocal > 0U)
        {
            firstWord |= ((uint32_t)(*payloadLocal) << (i << 3U));
            payloadLocal++;
            payloadSizeLocal--;
        }
        else
        {
            break;
        }
    }

    apb->TX_PAYLOAD = firstWord;

    /* Write the payloadLocal to the FIFO. */
    for (i = 0; i < (payloadSizeLocal / 4U); i++)
    {
        apb->TX_PAYLOAD = ((uint32_t)payloadLocal[3] << 24U) | ((uint32_t)payloadLocal[2] << 16U) |
                          ((uint32_t)payloadLocal[1] << 8U) | payloadLocal[0];
        payloadLocal = &payloadLocal[4];
    }

    /* Write the remaining data. */
    switch (payloadSizeLocal & 0x03U)
    {
        case 3:
            apb->TX_PAYLOAD = ((uint32_t)payloadLocal[2] << 16U) | ((uint32_t)payloadLocal[1] << 8U) | payloadLocal[0];
            break;
        case 2:
            apb->TX_PAYLOAD = ((uint32_t)payloadLocal[1] << 8U) | payloadLocal[0];
            break;
        case 1:
            apb->TX_PAYLOAD = payloadLocal[0];
            break;
        default:
            /* For MISRA 2012 16.4 */
            break;
    }
}

static status_t DSI_PrepareApbTransfer(const MIPI_DSI_Type *base, dsi_transfer_t *xfer)
{
    /* The receive data size should be smaller than the RX FIRO. */
    assert(xfer->rxDataSize <= FSL_DSI_RX_MAX_PAYLOAD_BYTE);
    assert(xfer->txDataSize <= FSL_DSI_TX_MAX_PAYLOAD_BYTE);

    uint8_t txDataIndex;
    uint16_t wordCount;
    uint32_t intFlags1;
    uint32_t intFlags2;
    uint32_t txDataSize;

    status_t status;

    if (xfer->rxDataSize > FSL_DSI_RX_MAX_PAYLOAD_BYTE)
    {
        status = kStatus_DSI_NotSupported;
    }
    else
    {
        if (xfer->rxDataSize != 0U)
        {
            xfer->flags |= (uint8_t)kDSI_TransferPerformBTA;
        }

        /* ========================== Prepare TX. ========================== */
        /* If xfer->sendDscCmd is true, then the DSC command is not included in the
           xfer->txData, but specified by xfer->dscCmd.
         */
        if (xfer->sendDscCmd)
        {
            txDataSize = (uint32_t)xfer->txDataSize + 1U;
        }
        else
        {
            txDataSize = (uint32_t)xfer->txDataSize;
        }

        /* Short packet. */
        if (txDataSize <= 2U)
        {
            if (0U == txDataSize)
            {
                wordCount = 0U;
            }
            else
            {
                txDataIndex = 0;

                if (xfer->sendDscCmd)
                {
                    wordCount = xfer->dscCmd;
                }
                else
                {
                    wordCount = xfer->txData[txDataIndex++];
                }

                if (2U == txDataSize)
                {
                    wordCount |= ((uint16_t)xfer->txData[txDataIndex] << 8U);
                }
            }
        }
        /* Long packet. */
        else
        {
            wordCount = (uint16_t)txDataSize;
            DSI_WriteApbTxPayloadExt(base, xfer->txData, xfer->txDataSize, xfer->sendDscCmd, xfer->dscCmd);
        }

        DSI_SetApbPacketControl(base, wordCount, xfer->virtualChannel, xfer->txDataType, xfer->flags);

        /* Clear the interrupt flags set by previous transfer. */
        DSI_GetAndClearInterruptStatus(base, &intFlags1, &intFlags2);

        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Read the long APB packet payload.
 *
 * Read the long packet payload from RX FIFO. This function reads directly but
 * does not check the RX FIFO status. Upper layer should make sure there are
 * available data.
 *
 * param base MIPI DSI host peripheral base address.
 * param payload Pointer to the payload.
 * param payloadSize Payload size in byte.
 */
void DSI_ReadApbRxPayload(const MIPI_DSI_Type *base, uint8_t *payload, uint16_t payloadSize)
{
    uint32_t tmp;
    uint16_t i;
    uint8_t *payloadLocal = payload;

    for (i = 0; i < payloadSize / 4U; i++)
    {
        tmp             = base->apb->PKT_RX_PAYLOAD;
        payloadLocal[0] = (uint8_t)(tmp & 0xFFU);
        payloadLocal[1] = (uint8_t)((tmp >> 8U) & 0xFFU);
        payloadLocal[2] = (uint8_t)((tmp >> 16U) & 0xFFU);
        payloadLocal[3] = (uint8_t)((tmp >> 24U) & 0xFFU);
        payloadLocal    = &payloadLocal[4];
    }

    /* Read out the remaining data. */
    if (0U != (payloadSize & 0x03U))
    {
        tmp = base->apb->PKT_RX_PAYLOAD;

        for (i = 0; i < (payloadSize & 0x3U); i++)
        {
            payloadLocal[i] = (uint8_t)(tmp & 0xFFU);
            tmp >>= 8U;
        }
    }
}

/*!
 * brief APB data transfer using blocking method.
 *
 * Perform APB data transfer using blocking method. This function waits until all
 * data send or received, or timeout happens.
 *
 * param base MIPI DSI host peripheral base address.
 * param xfer Pointer to the transfer structure.
 * retval kStatus_Success Data transfer finished with no error.
 * retval kStatus_Timeout Transfer failed because of timeout.
 * retval kStatus_DSI_RxDataError RX data error, user could use ref DSI_GetRxErrorStatus
 * to check the error details.
 * retval kStatus_DSI_ErrorReportReceived Error Report packet received, user could use
 *        ref DSI_GetAndClearHostStatus to check the error report status.
 * retval kStatus_DSI_NotSupported Transfer format not supported.
 * retval kStatus_DSI_Fail Transfer failed for other reasons.
 */
status_t DSI_TransferBlocking(const MIPI_DSI_Type *base, dsi_transfer_t *xfer)
{
    status_t status;
    uint32_t intFlags1Old;
    uint32_t intFlags2Old;
    uint32_t intFlags1New;
    uint32_t intFlags2New;

    DSI_HOST_APB_PKT_IF_Type *apb = base->apb;

    /* Wait for the APB state idle. */
    while (0U != (apb->PKT_STATUS & (uint32_t)kDSI_ApbNotIdle))
    {
    }

    status = DSI_PrepareApbTransfer(base, xfer);

    if (kStatus_Success == status)
    {
        DSI_SendApbPacket(base);

        /* Make sure the transfer is started. */
        while (true)
        {
            DSI_GetAndClearInterruptStatus(base, &intFlags1Old, &intFlags2Old);

            if (0U != (intFlags1Old & (uint32_t)kDSI_InterruptGroup1ApbNotIdle))
            {
                break;
            }
        }

        /* Wait for transfer finished. */
        while (true)
        {
            /* Transfer completed. */
            if (0U == (apb->PKT_STATUS & (uint32_t)kDSI_ApbNotIdle))
            {
                break;
            }

            /* Time out. */
            if (0U != (base->host->RX_ERROR_STATUS &
                       ((uint32_t)kDSI_RxErrorHtxTo | (uint32_t)kDSI_RxErrorLrxTo | (uint32_t)kDSI_RxErrorBtaTo)))
            {
                status = kStatus_Timeout;
                break;
            }
        }

        DSI_GetAndClearInterruptStatus(base, &intFlags1New, &intFlags2New);

        if (kStatus_Success == status)
        {
            status = DSI_HandleResult(base, intFlags1Old | intFlags1New, intFlags2Old | intFlags2New, xfer);
        }
    }

    return status;
}

static status_t DSI_HandleResult(const MIPI_DSI_Type *base,
                                 uint32_t intFlags1,
                                 uint32_t intFlags2,
                                 dsi_transfer_t *xfer)
{
    uint32_t rxPktHeader;
    uint16_t actualRxByteCount;
    dsi_rx_data_type_t rxDataType;
    bool readRxDataFromPayload;

    /* If hardware detect timeout. */
    if (0U != (((uint32_t)kDSI_InterruptGroup1HtxTo | (uint32_t)kDSI_InterruptGroup1LrxTo |
                (uint32_t)kDSI_InterruptGroup1BtaTo) &
               intFlags1))
    {
        return kStatus_Timeout;
    }

    /* If received data error. */
    if (0U != (((uint32_t)kDSI_InterruptGroup2EccMultiBit | (uint32_t)kDSI_InterruptGroup2CrcError) & intFlags2))
    {
        return kStatus_DSI_RxDataError;
    }

    /* If BTA is performed. */
    if (0U != (xfer->flags & (uint32_t)kDSI_TransferPerformBTA))
    {
        if (0U != (intFlags1 & DSI_INT_STATUS_ERROR_REPORT_MASK))
        {
            return kStatus_DSI_ErrorReportReceived;
        }

        if (0U != ((uint32_t)kDSI_InterruptGroup1ApbRxHeaderReceived & intFlags1))
        {
            rxPktHeader = DSI_GetRxPacketHeader(base);
            rxDataType  = DSI_GetRxPacketType(rxPktHeader);

            /* If received error report. */
            if (kDSI_RxDataAckAndErrorReport == rxDataType)
            {
                return kStatus_DSI_ErrorReportReceived;
            }
            else
            {
                if ((kDSI_RxDataGenShortRdResponseOneByte == rxDataType) ||
                    (kDSI_RxDataDcsShortRdResponseOneByte == rxDataType))
                {
                    readRxDataFromPayload = false;
                    actualRxByteCount     = 1U;
                }
                else if ((kDSI_RxDataGenShortRdResponseTwoByte == rxDataType) ||
                         (kDSI_RxDataDcsShortRdResponseTwoByte == rxDataType))
                {
                    readRxDataFromPayload = false;
                    actualRxByteCount     = 2U;
                }
                else if ((kDSI_RxDataGenLongRdResponse == rxDataType) || (kDSI_RxDataDcsLongRdResponse == rxDataType))
                {
                    readRxDataFromPayload = true;
                    actualRxByteCount     = DSI_GetRxPacketWordCount(rxPktHeader);
                }
                else
                {
                    readRxDataFromPayload = false;
                    xfer->rxDataSize      = 0U;
                    actualRxByteCount     = 0U;
                }

                xfer->rxDataSize = MIN(xfer->rxDataSize, actualRxByteCount);

                if (xfer->rxDataSize > 0U)
                {
                    if (readRxDataFromPayload)
                    {
                        DSI_ReadApbRxPayload(base, xfer->rxData, xfer->rxDataSize);
                    }
                    else
                    {
                        xfer->rxData[0] = (uint8_t)(rxPktHeader & 0xFFU);

                        if (2U == xfer->rxDataSize)
                        {
                            xfer->rxData[1] = (uint8_t)((rxPktHeader >> 8U) & 0xFFU);
                        }
                    }
                }

                return kStatus_Success;
            }
        }

        return kStatus_Success;
    }
    else
    {
        /* Tx Done. */
        if (0U != ((uint32_t)kDSI_InterruptGroup1ApbTxDone & intFlags1))
        {
            return kStatus_Success;
        }
    }

    return kStatus_Fail;
}

/*!
 * brief Create the MIPI DSI handle.
 *
 * This function initializes the MIPI DSI handle which can be used for other transactional APIs.
 *
 * param base MIPI DSI host peripheral base address.
 * param handle Handle pointer.
 * param callback Callback function.
 * param userData User data.
 */
status_t DSI_TransferCreateHandle(const MIPI_DSI_Type *base,
                                  dsi_handle_t *handle,
                                  dsi_callback_t callback,
                                  void *userData)
{
    assert(NULL != handle);

    uint32_t instance = DSI_GetInstance(base);

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Initialize the handle */
    s_dsiHandle[instance] = handle;
    handle->callback      = callback;
    handle->userData      = userData;
    handle->isBusy        = false;
    handle->dsi           = base;
    s_dsiIsr              = DSI_TransferHandleIRQ;

#if defined(DSI_HOST_DSI_IRQS)
    /* Enable interrupt in NVIC. */
    (void)EnableIRQ(s_dsiIRQ[instance]);
#endif

    return kStatus_Success;
}

/*!
 * brief APB data transfer using interrupt method.
 *
 * Perform APB data transfer using interrupt method, when transfer finished,
 * upper layer could be informed through callback function.
 *
 * param base MIPI DSI host peripheral base address.
 * param handle pointer to dsi_handle_t structure which stores the transfer state.
 * param xfer Pointer to the transfer structure.
 *
 * retval kStatus_Success Data transfer started successfully.
 * retval kStatus_DSI_Busy Failed to start transfer because DSI is busy with pervious transfer.
 * retval kStatus_DSI_NotSupported Transfer format not supported.
 */
status_t DSI_TransferNonBlocking(const MIPI_DSI_Type *base, dsi_handle_t *handle, dsi_transfer_t *xfer)
{
    status_t status;

    if (handle->isBusy)
    {
        status = kStatus_DSI_Busy;
    }
    else if (0U != (base->apb->PKT_STATUS & (uint32_t)kDSI_ApbNotIdle))
    {
        status = kStatus_DSI_Busy;
    }
    else
    {
        handle->xfer = *xfer;

        status = DSI_PrepareApbTransfer(base, &handle->xfer);

        if (kStatus_Success == status)
        {
            DSI_SendApbPacket(base);
            handle->isBusy = true;

            /* Enable the interrupts. */
            if (0U != (handle->xfer.flags & (uint32_t)kDSI_TransferPerformBTA))
            {
                DSI_EnableInterrupts(
                    base,
                    DSI_INT_STATUS_TRIGGER_MASK | (uint32_t)kDSI_InterruptGroup1ApbRxHeaderReceived |
                        (uint32_t)kDSI_InterruptGroup1ApbRxPacketReceived | (uint32_t)kDSI_InterruptGroup1BtaTo |
                        (uint32_t)kDSI_InterruptGroup1LrxTo | (uint32_t)kDSI_InterruptGroup1HtxTo |
                        (uint32_t)kDSI_InterruptGroup1AckTriggerReceived,
                    (uint32_t)kDSI_InterruptGroup2EccMultiBit | (uint32_t)kDSI_InterruptGroup2CrcError);
            }
            else
            {
                DSI_EnableInterrupts(base,
                                     (uint32_t)kDSI_InterruptGroup1ApbTxDone | (uint32_t)kDSI_InterruptGroup1HtxTo, 0U);
            }
        }
    }

    return status;
}

/*!
 * brief Abort current APB data transfer.
 *
 * param base MIPI DSI host peripheral base address.
 * param handle pointer to dsi_handle_t structure which stores the transfer state.
 */
void DSI_TransferAbort(const MIPI_DSI_Type *base, dsi_handle_t *handle)
{
    assert(NULL != handle);

    if (handle->isBusy)
    {
        /* Disable the interrupts. */
        DSI_DisableInterrupts(base,
                              (uint32_t)kDSI_InterruptGroup1ApbTxDone | DSI_INT_STATUS_TRIGGER_MASK |
                                  DSI_INT_STATUS_ERROR_REPORT_MASK | (uint32_t)kDSI_InterruptGroup1ApbRxHeaderReceived |
                                  (uint32_t)kDSI_InterruptGroup1ApbRxPacketReceived |
                                  (uint32_t)kDSI_InterruptGroup1BtaTo | (uint32_t)kDSI_InterruptGroup1LrxTo |
                                  (uint32_t)kDSI_InterruptGroup1HtxTo,
                              (uint32_t)kDSI_InterruptGroup2EccMultiBit | (uint32_t)kDSI_InterruptGroup2CrcError);

        /* Reset transfer info. */
        (void)memset(&handle->xfer, 0, sizeof(handle->xfer));

        /* Reset the state to idle. */
        handle->isBusy = false;
    }
}

/*!
 * brief Interrupt handler for the DSI.
 *
 * param base MIPI DSI host peripheral base address.
 * param handle pointer to dsi_handle_t structure which stores the transfer state.
 */
void DSI_TransferHandleIRQ(const MIPI_DSI_Type *base, dsi_handle_t *handle)
{
    assert(NULL != handle);

    status_t status;
    uint32_t intFlags1;
    uint32_t intFlags2;
    uint32_t timeout;
    const MIPI_DSI_Type *dsi = handle->dsi;

    /* If no transfer in progress, return directly. */
    if (handle->isBusy)
    {
        /* Make sure the transfer is completed. */
        timeout = FSL_MIPI_DSI_IDLE_TIMEOUT;
        while (0U != (timeout--))
        {
            if (0U == (dsi->apb->PKT_STATUS & (uint32_t)kDSI_ApbNotIdle))
            {
                break;
            }
        }

        if (0U == timeout)
        {
            DSI_TransferAbort(dsi, handle);
            status = kStatus_Timeout;
        }
        else
        {
            /* Disable the interrupts. */
            DSI_DisableInterrupts(
                dsi,
                (uint32_t)kDSI_InterruptGroup1ApbTxDone | DSI_INT_STATUS_TRIGGER_MASK |
                    DSI_INT_STATUS_ERROR_REPORT_MASK | (uint32_t)kDSI_InterruptGroup1ApbRxHeaderReceived |
                    (uint32_t)kDSI_InterruptGroup1ApbRxPacketReceived | (uint32_t)kDSI_InterruptGroup1BtaTo |
                    (uint32_t)kDSI_InterruptGroup1LrxTo | (uint32_t)kDSI_InterruptGroup1HtxTo,
                (uint32_t)kDSI_InterruptGroup2EccMultiBit | (uint32_t)kDSI_InterruptGroup2CrcError);

            DSI_GetAndClearInterruptStatus(dsi, &intFlags1, &intFlags2);

            status         = DSI_HandleResult(dsi, intFlags1, intFlags2, &handle->xfer);
            handle->isBusy = false;
        }

        if (NULL != handle->callback)
        {
            handle->callback(dsi, handle, status, handle->userData);
        }
    }

    return;
}

#if defined(DSI_HOST)
void MIPI_DSI_DriverIRQHandler(void);
void MIPI_DSI_DriverIRQHandler(void)
{
    /* The first parameter is not used, use the peripheral address defined in
     * handle.
     */
    s_dsiIsr(NULL, s_dsiHandle[0]);
}
#endif
