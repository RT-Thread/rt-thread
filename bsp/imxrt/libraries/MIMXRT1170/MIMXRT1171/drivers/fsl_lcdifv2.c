/*
 * Copyright 2019-2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_lcdifv2.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lcdifv2"
#endif

#define LCDIFV2_LUT_MEM(base) \
    ((volatile uint32_t *)(((uint32_t)(base)) + (uint32_t)FSL_FEATURE_LCDIFV2_CLUT_RAM_OFFSET))

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get instance number for LCDIF module.
 *
 * @param base LCDIF peripheral base address
 */
static uint32_t LCDIFV2_GetInstance(const LCDIFV2_Type *base);

/*!
 * @brief Reset register value to default status.
 *
 * @param base LCDIF peripheral base address
 */
static void LCDIFV2_ResetRegister(LCDIFV2_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to LCDIF clock for each instance. */
static const clock_ip_name_t s_lcdifv2Clocks[] = LCDIFV2_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Codes
 ******************************************************************************/
static uint32_t LCDIFV2_GetInstance(const LCDIFV2_Type *base)
{
    static LCDIFV2_Type *const s_lcdifv2Bases[] = LCDIFV2_BASE_PTRS;

    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_lcdifv2Bases); instance++)
    {
        if (MSDK_REG_SECURE_ADDR(s_lcdifv2Bases[instance]) == MSDK_REG_SECURE_ADDR(base))
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_lcdifv2Bases));

    return instance;
}

static void LCDIFV2_ResetRegister(LCDIFV2_Type *base)
{
    uint32_t i;

    base->DISP_PARA         = 0U;
    base->CTRL              = 0x80000000U;
    base->DISP_SIZE         = 0U;
    base->HSYN_PARA         = 0x00C01803U;
    base->VSYN_PARA         = 0x00C01803U;
    base->INT[0].INT_ENABLE = 0U;
    base->INT[1].INT_ENABLE = 0U;

    for (i = 0; i < (uint32_t)LCDIFV2_LAYER_COUNT; i++)
    {
        base->LAYER[i].CTRLDESCL5 = 0U;
        base->LAYER[i].CTRLDESCL1 = 0U;
        base->LAYER[i].CTRLDESCL2 = 0U;
        base->LAYER[i].CTRLDESCL3 = 0U;
        base->LAYER[i].CTRLDESCL4 = 0U;
        base->LAYER[i].CTRLDESCL6 = 0U;
    }

    for (i = 0; i < (uint32_t)LCDIFV2_LAYER_CSC_COUNT; i++)
    {
        base->LAYER[i].CSC_COEF0 = 0x04000000U;
        base->LAYER[i].CSC_COEF1 = 0x01230208U;
        base->LAYER[i].CSC_COEF2 = 0x076B079CU;
    }

    /* Clear interrupt status. */
    base->INT[0].INT_STATUS = 0xFFFFFFFFU;
    base->INT[1].INT_STATUS = 0xFFFFFFFFU;
}

/*!
 * brief Initializes the LCDIF v2.
 *
 * This function ungates the LCDIF v2 clock and release the peripheral reset.
 *
 * param base LCDIF v2 peripheral base address.
 */
void LCDIFV2_Init(LCDIFV2_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && (0 != FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL))
    uint32_t instance = LCDIFV2_GetInstance(base);
    /* Enable the clock. */
    CLOCK_EnableClock(s_lcdifv2Clocks[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    LCDIFV2_ResetRegister(base);

    /* Out of reset. */
    base->CTRL = 0U;
}

/*!
 * brief Deinitializes the LCDIF peripheral.
 *
 * param base LCDIF peripheral base address.
 */
void LCDIFV2_Deinit(LCDIFV2_Type *base)
{
    LCDIFV2_ResetRegister(base);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && (0 != FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL))
    uint32_t instance = LCDIFV2_GetInstance(base);
    /* Disable the clock. */
    CLOCK_DisableClock(s_lcdifv2Clocks[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Reset the LCDIF v2.
 *
 * param base LCDIF peripheral base address.
 */
void LCDIFV2_Reset(LCDIFV2_Type *base)
{
    LCDIFV2_ResetRegister(base);

    /* Release and ready to work. */
    base->CTRL = 0U;
}

/*!
 * brief Gets the LCDIF display default configuration structure.
 *
 * param config Pointer to the LCDIF configuration structure.
 */
void LCDIFV2_DisplayGetDefaultConfig(lcdifv2_display_config_t *config)
{
    assert(NULL != config);

    config->panelWidth    = 0U;
    config->panelHeight   = 0U;
    config->hsw           = 3U;
    config->hfp           = 3U;
    config->hbp           = 3U;
    config->vsw           = 3U;
    config->vfp           = 3U;
    config->vbp           = 3U;
    config->polarityFlags = (uint32_t)kLCDIFV2_VsyncActiveHigh | (uint32_t)kLCDIFV2_HsyncActiveHigh |
                            (uint32_t)kLCDIFV2_DataEnableActiveHigh | (uint32_t)kLCDIFV2_DriveDataOnRisingClkEdge |
                            (uint32_t)kLCDIFV2_DataActiveHigh;
    config->lineOrder = kLCDIFV2_LineOrderRGB;
}

/*!
 * brief Set the LCDIF v2 display configurations.
 *
 * param base LCDIF peripheral base address.
 * param config Pointer to the LCDIF configuration structure.
 */
void LCDIFV2_SetDisplayConfig(LCDIFV2_Type *base, const lcdifv2_display_config_t *config)
{
    assert(NULL != config);

    /* Configure the parameters. */
    base->DISP_SIZE = ((uint32_t)config->panelWidth << LCDIFV2_DISP_SIZE_DELTA_X_SHIFT) |
                      ((uint32_t)config->panelHeight << LCDIFV2_DISP_SIZE_DELTA_Y_SHIFT);

    base->HSYN_PARA = ((uint32_t)config->hsw << LCDIFV2_HSYN_PARA_PW_H_SHIFT) |
                      ((uint32_t)config->hbp << LCDIFV2_HSYN_PARA_BP_H_SHIFT) |
                      ((uint32_t)config->hfp << LCDIFV2_HSYN_PARA_FP_H_SHIFT);

    base->VSYN_PARA = ((uint32_t)config->vsw << LCDIFV2_VSYN_PARA_PW_V_SHIFT) |
                      ((uint32_t)config->vbp << LCDIFV2_VSYN_PARA_BP_V_SHIFT) |
                      ((uint32_t)config->vfp << LCDIFV2_VSYN_PARA_FP_V_SHIFT);

    base->DISP_PARA = LCDIFV2_DISP_PARA_LINE_PATTERN((uint32_t)config->lineOrder);

    base->CTRL = (uint32_t)(config->polarityFlags);
}

/*!
 * brief Set the color space conversion mode.
 *
 * Supports YUV2RGB and YCbCr2RGB.
 *
 * param base LCDIFv2 peripheral base address.
 * param layerIndex Index of the layer.
 * param mode The conversion mode.
 */
void LCDIFV2_SetCscMode(LCDIFV2_Type *base, uint8_t layerIndex, lcdifv2_csc_mode_t mode)
{
    assert(layerIndex < (uint32_t)LCDIFV2_LAYER_CSC_COUNT);

    /*
     * The equations used for Colorspace conversion are:
     *
     * R = C0*(Y+Y_OFFSET)                   + C1(V+UV_OFFSET)
     * G = C0*(Y+Y_OFFSET) + C3(U+UV_OFFSET) + C2(V+UV_OFFSET)
     * B = C0*(Y+Y_OFFSET) + C4(U+UV_OFFSET)
     */

    if (kLCDIFV2_CscYUV2RGB == mode)
    {
        base->LAYER[layerIndex].CSC_COEF0 = LCDIFV2_CSC_COEF0_ENABLE_MASK | LCDIFV2_CSC_COEF0_C0(0x100U) /* 1.00. */
                                            | LCDIFV2_CSC_COEF0_Y_OFFSET(0x0U)                           /* 0. */
                                            | LCDIFV2_CSC_COEF0_UV_OFFSET(0x0U);                         /* 0. */

        base->LAYER[layerIndex].CSC_COEF1 = LCDIFV2_CSC_COEF1_C1(0x0123U)    /* 1.140. */
                                            | LCDIFV2_CSC_COEF1_C4(0x0208U); /* 2.032. */
        base->LAYER[layerIndex].CSC_COEF2 = LCDIFV2_CSC_COEF2_C2(0x076BU)    /* -0.851. */
                                            | LCDIFV2_CSC_COEF2_C3(0x079BU); /* -0.394. */
    }
    else if (kLCDIFV2_CscYCbCr2RGB == mode)
    {
        base->LAYER[layerIndex].CSC_COEF0 = LCDIFV2_CSC_COEF0_ENABLE_MASK | LCDIFV2_CSC_COEF0_YCBCR_MODE_MASK |
                                            LCDIFV2_CSC_COEF0_C0(0x12AU)           /* 1.164. */
                                            | LCDIFV2_CSC_COEF0_Y_OFFSET(0x1F0U)   /* -16. */
                                            | LCDIFV2_CSC_COEF0_UV_OFFSET(0x180U); /* -128. */
        base->LAYER[layerIndex].CSC_COEF1 = LCDIFV2_CSC_COEF1_C1(0x0198U)          /* 1.596. */
                                            | LCDIFV2_CSC_COEF1_C4(0x0204U);       /* 2.017. */
        base->LAYER[layerIndex].CSC_COEF2 = LCDIFV2_CSC_COEF2_C2(0x0730U)          /* -0.813. */
                                            | LCDIFV2_CSC_COEF2_C3(0x079CU);       /* -0.392. */
    }
    else
    {
        base->LAYER[layerIndex].CSC_COEF0 = 0U;
        base->LAYER[layerIndex].CSC_COEF1 = 0U;
        base->LAYER[layerIndex].CSC_COEF2 = 0U;
    }
}

/*!
 * brief Set the layer source buffer configuration.
 *
 * param base LCDIFv2 peripheral base address.
 * param layerIndex Layer layerIndex.
 * param config Pointer to the configuration.
 */
void LCDIFV2_SetLayerBufferConfig(LCDIFV2_Type *base, uint8_t layerIndex, const lcdifv2_buffer_config_t *config)
{
    assert(NULL != config);
    uint32_t reg;

    base->LAYER[layerIndex].CTRLDESCL3 = config->strideBytes;

    reg = base->LAYER[layerIndex].CTRLDESCL5;
    reg = (reg & ~(LCDIFV2_CTRLDESCL5_BPP_MASK | LCDIFV2_CTRLDESCL5_YUV_FORMAT_MASK)) | (uint32_t)config->pixelFormat;

    if (0U == (reg & LCDIFV2_CTRLDESCL5_AB_MODE_MASK))
    {
        reg |= LCDIFV2_CTRLDESCL5_SAFETY_EN_MASK;
    }

    base->LAYER[layerIndex].CTRLDESCL5 = reg;
}

/*!
 * brief Set the LUT data.
 *
 * This function sets the specific layer LUT data, if useShadowLoad is true,
 * call LCDIFV2_TriggerLayerShadowLoad after this function, the
 * LUT will be loaded to the hardware during next vertical blanking period.
 * If useShadowLoad is false, the LUT data is loaded to hardware directly.
 *
 * param base LCDIF v2 peripheral base address.
 * param layerIndex Which layer to set.
 * param lutData The LUT data to load.
 * param count Count of lutData.
 * retval kStatus_Success Set success.
 * retval kStatus_Fail Previous LUT data is not loaded to hardware yet.
 */
status_t LCDIFV2_SetLut(
    LCDIFV2_Type *base, uint8_t layerIndex, const uint32_t *lutData, uint16_t count, bool useShadowLoad)
{
    assert(count <= LCDIFV2_LUT_ENTRY_NUM);

    uint16_t i;
    status_t status;

    /* Previous setting is not updated. */
    if ((base->CLUT_LOAD & LCDIFV2_CLUT_LOAD_CLUT_UPDATE_EN_MASK) != 0U)
    {
        status = kStatus_Fail;
    }
    else
    {
        if (useShadowLoad)
        {
            base->CLUT_LOAD = LCDIFV2_CLUT_LOAD_SEL_CLUT_NUM(layerIndex) | LCDIFV2_CLUT_LOAD_CLUT_UPDATE_EN_MASK;
        }
        else
        {
            base->CLUT_LOAD = LCDIFV2_CLUT_LOAD_SEL_CLUT_NUM(layerIndex);
        }

        for (i = 0; i < count; i++)
        {
            (LCDIFV2_LUT_MEM(base))[i + (LCDIFV2_LUT_ENTRY_NUM * layerIndex)] = lutData[i];
        }

        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Set the layer alpha blend mode.
 *
 * param base LCDIFv2 peripheral base address.
 * param layerIndex Index of the CSC unit.
 * param config Pointer to the blend configuration.
 */
void LCDIFV2_SetLayerBlendConfig(LCDIFV2_Type *base, uint8_t layerIndex, const lcdifv2_blend_config_t *config)
{
    assert(NULL != config);

    uint32_t reg;

    reg = base->LAYER[layerIndex].CTRLDESCL5;
    reg &= ~(LCDIFV2_CTRLDESCL5_GLOBAL_ALPHA_MASK | LCDIFV2_CTRLDESCL5_AB_MODE_MASK |
             LCDIFV2_CTRLDESCL5_PD_FACTOR_MODE_MASK | LCDIFV2_CTRLDESCL5_PD_ALPHA_MODE_MASK |
             LCDIFV2_CTRLDESCL5_PD_COLOR_MODE_MASK | LCDIFV2_CTRLDESCL5_PD_GLOBAL_ALPHA_MODE_MASK |
             LCDIFV2_CTRLDESCL5_SAFETY_EN_MASK);

    reg |=
        (LCDIFV2_CTRLDESCL5_GLOBAL_ALPHA(config->globalAlpha) | LCDIFV2_CTRLDESCL5_AB_MODE(config->alphaMode) |
         LCDIFV2_CTRLDESCL5_PD_FACTOR_MODE(config->pdFactorMode) |
         LCDIFV2_CTRLDESCL5_PD_ALPHA_MODE(config->pdAlphaMode) | LCDIFV2_CTRLDESCL5_PD_COLOR_MODE(config->pdColorMode) |
         LCDIFV2_CTRLDESCL5_PD_GLOBAL_ALPHA_MODE(config->pdGlobalAlphaMode));

    if (config->alphaMode == kLCDIFV2_AlphaDisable)
    {
        reg |= LCDIFV2_CTRLDESCL5_SAFETY_EN_MASK;
    }

    base->LAYER[layerIndex].CTRLDESCL5 = reg;
}

/*
 * brief Get the blend configuration for Porter Duff blend.
 *
 * This is the basic Porter Duff blend configuration, user still could
 * modify the configurations after this function.
 *
 * param mode Porter Duff blend mode.
 * param layer The configuration for source layer or destination layer.
 * param config Pointer to the configuration.
 * retval kStatus_Success Get the configuration successfully.
 * retval kStatus_InvalidArgument The argument is invalid.
 */
status_t LCDIFV2_GetPorterDuffConfig(lcdifv2_pd_blend_mode_t mode,
                                     lcdifv2_pd_layer_t layer,
                                     lcdifv2_blend_config_t *config)
{
    static const lcdifv2_pd_factor_mode_t s_lcdifv2PdLayerFactors[][2] = {
        /* kLCDIFV2_PD_Src */
        {
            /* s1_s0_factor_mode. */
            kLCDIFV2_PD_FactorZero,

            /* s0_s1_factor_mode. */
            kLCDIFV2_PD_FactorOne,
        },

        /* kLCDIFV2_PD_Atop */
        {kLCDIFV2_PD_FactorInversedAlpha, kLCDIFV2_PD_FactorStraightAlpha},

        /* kLCDIFV2_PD_Over */
        {kLCDIFV2_PD_FactorInversedAlpha, kLCDIFV2_PD_FactorOne},

        /* kLCDIFV2_PD_In */
        {kLCDIFV2_PD_FactorZero, kLCDIFV2_PD_FactorStraightAlpha},

        /* kLCDIFV2_PD_Out */
        {kLCDIFV2_PD_FactorZero, kLCDIFV2_PD_FactorInversedAlpha},

        /* kLCDIFV2_PD_Dst */
        {kLCDIFV2_PD_FactorOne, kLCDIFV2_PD_FactorZero},

        /* kLCDIFV2_PD_DstAtop */
        {kLCDIFV2_PD_FactorStraightAlpha, kLCDIFV2_PD_FactorInversedAlpha},

        /* kLCDIFV2_PD_DstOver */
        {kLCDIFV2_PD_FactorOne, kLCDIFV2_PD_FactorInversedAlpha},

        /* kLCDIFV2_PD_DstIn */
        {kLCDIFV2_PD_FactorStraightAlpha, kLCDIFV2_PD_FactorZero},

        /* kLCDIFV2_PD_DstOut */
        {kLCDIFV2_PD_FactorInversedAlpha, kLCDIFV2_PD_FactorZero},

        /* kLCDIFV2_PD_Xor */
        {kLCDIFV2_PD_FactorInversedAlpha, kLCDIFV2_PD_FactorInversedAlpha},

        /* kLCDIFV2_PD_Clear */
        {
            kLCDIFV2_PD_FactorZero,
            kLCDIFV2_PD_FactorZero,
        },
    };

    status_t status;

    if ((NULL == config) || (mode >= kLCDIFV2_PD_Max) || (layer >= kLCDIFV2_PD_LayerMax))
    {
        status = kStatus_InvalidArgument;
    }
    else
    {
        config->pdAlphaMode       = kLCDIFV2_PD_AlphaStraight;
        config->pdColorMode       = kLCDIFV2_PD_ColorWithAlpha;
        config->pdGlobalAlphaMode = kLCDIFV2_PD_LocalAlpha;
        config->pdFactorMode      = s_lcdifv2PdLayerFactors[mode][(uint8_t)layer];
        config->alphaMode         = kLCDIFV2_AlphaPoterDuff;

        status = kStatus_Success;
    }

    return status;
}

/*
 * brief Get the global alpha values for multiple layer blend.
 *
 * When all layers use the global alpha, the relationship blended alpha
 * and global alpha of each layer is:
 *
 * Layer 7: ba7 = ga7
 * Layer 6: ba6 = ga6 * (1-ga7)
 * Layer 5: ba5 = ga5 * (1-ga6) * (1-ga7)
 * Layer 4: ba4 = ga4 * (1-ga5) * (1-ga6) * (1-ga7)
 * Layer 3: ba3 = ga3 * (1-ga4) * (1-ga5) * (1-ga6) * (1-ga7)
 * Layer 2: ba2 = ga2 * (1-ga3) * (1-ga4) * (1-ga5) * (1-ga6) * (1-ga7)
 * Layer 1: ba1 = ga1 * (1-ga2) * (1-ga3) * (1-ga4) * (1-ga5) * (1-ga6) * (1-ga7)
 * Layer 0: ba0 =   1 * (1-ga1) * (1-ga2) * (1-ga3) * (1-ga4) * (1-ga5) * (1-ga6) * (1-ga7)
 *
 * Here baN is the blended alpha of layer N, gaN is the global alpha configured to layer N.
 *
 * This function calculates the global alpha based on the blended alpha. The blendedAlpha and
 * globalAlpha are all arrays of size layerCount. The first layer is a background layer,
 * so blendedAlpha[0] is useless, globalAlpha[0] is always 255.
 *
 * param blendedAlpha The desired blended alpha value, alpha range 0~255.
 * param globalAlpha Calculated global alpha set to each layer register.
 * param layerCount Total layer count.
 * retval kStatus_Success Get successfully.
 * retval kStatus_InvalidArgument The argument is invalid.
 */
status_t LCDIFV2_GetMultiLayerGlobalAlpha(const uint8_t blendedAlpha[], uint8_t globalAlpha[], uint8_t layerCount)
{
    status_t status  = kStatus_Success;
    int16_t curLayer = (int16_t)layerCount - 1;
    int left         = 255;
    int tmpAlpha;

    assert((layerCount > 1U) && (layerCount <= (uint8_t)LCDIFV2_LAYER_COUNT));

    /*
     * Assume the layer counter is 7, and alpha range is 0~1, define:
     *
     *   left_7 = 1
     *   left_i = (1-ga_(i+1)) * ... * (1-ga7)
     *
     * Then:
     *   ba_i   = ga_i * left_i
     *   left_i = left_(i+1) - ba_i
     *   ga_i = ba_i / left_i
     *
     * Now change alpha range to 0~255, then:
     *
     *   ga_i   = ba_i * 255 / left_i
     *   left_i = left_(i+1) - ba_i
     */

    globalAlpha[0] = 255U;

    while (curLayer > 0)
    {
        tmpAlpha = (int)blendedAlpha[curLayer] * 255 / left;
        if (tmpAlpha > 255)
        {
            status = kStatus_InvalidArgument;
            break;
        }

        globalAlpha[curLayer] = (uint8_t)tmpAlpha;
        left -= (int)blendedAlpha[curLayer];

        if (left <= 0)
        {
            status = kStatus_InvalidArgument;
            break;
        }

        curLayer--;
    }

    return status;
}
