/*
 * Copyright 2017-2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_pxp.h"

#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
#include "fsl_memory.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.pxp"
#endif

/* The CSC2 coefficient is ###.####_#### */
#define PXP_CSC2_COEF_INT_WIDTH  2
#define PXP_CSC2_COEF_FRAC_WIDTH 8

/* Compatibility map macro. */
#if defined(PXP_PS_CLRKEYLOW_0_PIXEL_MASK) && (!defined(PXP_PS_CLRKEYLOW_PIXEL_MASK))
#define PS_CLRKEYLOW  PS_CLRKEYLOW_0
#define PS_CLRKEYHIGH PS_CLRKEYHIGH_0
#endif
#if defined(PXP_AS_CLRKEYLOW_0_PIXEL_MASK) && (!defined(PXP_AS_CLRKEYLOW_PIXEL_MASK))
#define AS_CLRKEYLOW  AS_CLRKEYLOW_0
#define AS_CLRKEYHIGH AS_CLRKEYHIGH_0
#endif

#define PXP_MAX_HEIGHT ((PXP_OUT_LRC_Y_MASK >> PXP_OUT_LRC_Y_SHIFT) + 1U)

/* Compatibility macro remap. */
#if (!defined(PXP_PORTER_DUFF_CTRL_PORTER_DUFF_ENABLE_MASK) && defined(PXP_PORTER_DUFF_CTRL_POTER_DUFF_ENABLE_MASK))
#define PXP_PORTER_DUFF_CTRL_PORTER_DUFF_ENABLE_MASK PXP_PORTER_DUFF_CTRL_POTER_DUFF_ENABLE_MASK
#endif

#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
#define PXP_ADDR_CPU_2_IP(addr) (MEMORY_ConvertMemoryMapAddress((uint32_t)(addr), kMEMORY_Local2DMA))
#else
#define PXP_ADDR_CPU_2_IP(addr) (addr)
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */

#if !(defined(FSL_FEATURE_PXP_HAS_NO_PORTER_DUFF_CTRL) && FSL_FEATURE_PXP_HAS_NO_PORTER_DUFF_CTRL)
#define S1_COLOR_MODE           PXP_PORTER_DUFF_CTRL_S1_COLOR_MODE
#define S1_ALPHA_MODE           PXP_PORTER_DUFF_CTRL_S1_ALPHA_MODE
#define S1_GLOBAL_ALPHA_MODE    PXP_PORTER_DUFF_CTRL_S1_GLOBAL_ALPHA_MODE
#define S1_S0_FACTOR_MODE       PXP_PORTER_DUFF_CTRL_S1_S0_FACTOR_MODE
#define S0_COLOR_MODE           PXP_PORTER_DUFF_CTRL_S0_COLOR_MODE
#define S0_ALPHA_MODE           PXP_PORTER_DUFF_CTRL_S0_ALPHA_MODE
#define S0_GLOBAL_ALPHA_MODE    PXP_PORTER_DUFF_CTRL_S0_GLOBAL_ALPHA_MODE
#define S0_S1_FACTOR_MODE       PXP_PORTER_DUFF_CTRL_S0_S1_FACTOR_MODE
#define PORTER_DUFF_ENABLE_MASK PXP_PORTER_DUFF_CTRL_PORTER_DUFF_ENABLE_MASK
#endif /* FSL_FEATURE_PXP_HAS_NO_PORTER_DUFF_CTRL */

#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3
#define S1_COLOR_MODE           PXP_ALPHA_A_CTRL_S1_COLOR_MODE
#define S1_ALPHA_MODE           PXP_ALPHA_A_CTRL_S1_ALPHA_MODE
#define S1_GLOBAL_ALPHA_MODE    PXP_ALPHA_A_CTRL_S1_GLOBAL_ALPHA_MODE
#define S1_S0_FACTOR_MODE       PXP_ALPHA_A_CTRL_S1_S0_FACTOR_MODE
#define S0_COLOR_MODE           PXP_ALPHA_A_CTRL_S0_COLOR_MODE
#define S0_ALPHA_MODE           PXP_ALPHA_A_CTRL_S0_ALPHA_MODE
#define S0_GLOBAL_ALPHA_MODE    PXP_ALPHA_A_CTRL_S0_GLOBAL_ALPHA_MODE
#define S0_S1_FACTOR_MODE       PXP_ALPHA_A_CTRL_S0_S1_FACTOR_MODE
#define PORTER_DUFF_ENABLE_MASK PXP_ALPHA_A_CTRL_PORTER_DUFF_ENABLE_MASK
#endif /* FSL_FEATURE_PXP_V3 */

typedef union _u32_f32
{
    float f32;
    uint32_t u32;
} u32_f32_t;

typedef union _pxp_pvoid_u32
{
    void *pvoid;
    uint32_t u32;
} pxp_pvoid_u32_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get the instance from the base address
 *
 * @param base PXP peripheral base address
 *
 * @return The PXP module instance
 */
static uint32_t PXP_GetInstance(PXP_Type *base);

#if !(defined(FSL_FEATURE_PXP_HAS_NO_CSC2) && FSL_FEATURE_PXP_HAS_NO_CSC2)
/*!
 * @brief Convert IEEE 754 float value to the value could be written to registers.
 *
 * This function converts the float value to integer value to set the scaler
 * and CSC parameters.
 *
 * This function is an alternative implemention of the following code with no
 * MISRA 2004 rule 10.4 error:
 *
 * @code
   return (uint32_t)(floatValue * (float)(1 << fracBits));
   @endcode
 *
 * @param floatValue The float value to convert.
 * @param intBits Bits number of integer part in result.
 * @param fracBits Bits number of fractional part in result.
 * @return The value to set to register.
 */
static uint32_t PXP_ConvertFloat(float floatValue, uint8_t intBits, uint8_t fracBits);
#endif

/*!
 * @brief Convert the desired scale fact to DEC and PS_SCALE.
 *
 * @param inputDimension Input dimension.
 * @param outputDimension Output dimension.
 * @param dec The decimation filter contr0l value.
 * @param scale The scale value set to register PS_SCALE.
 */
static void PXP_GetScalerParam(uint16_t inputDimension, uint16_t outputDimension, uint8_t *dec, uint32_t *scale);

/*!
 * @brief Reset the PXP to initialized state.
 *
 * @param base PXP peripheral base address.
 */
static void PXP_ResetToInit(PXP_Type *base);

/*!
 * @brief Copy rectangle.
 *
 * @param base PXP peripheral base address.
 * @param srcAddr Start address of the soruce rectangle.
 * @param srcPitchBytes Pitch of source buffer.
 * @param destAddr Start address of the destination rectangle.
 * @param destPitchBytes Pitch of destination buffer.
 * @param width How many pixels one line to copy.
 * @param height How many lines to copy.
 * @param pixelFormat Pixel format.
 */
static void PXP_StartRectCopy(PXP_Type *base,
                              uint32_t srcAddr,
                              uint16_t srcPitchBytes,
                              uint32_t destAddr,
                              uint16_t destPitchBytes,
                              uint16_t width,
                              uint16_t height,
                              pxp_as_pixel_format_t pixelFormat);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to PXP bases for each instance. */
static PXP_Type *const s_pxpBases[] = PXP_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to PXP clocks for each PXP submodule. */
static const clock_ip_name_t s_pxpClocks[] = PXP_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t PXP_GetInstance(PXP_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_pxpBases); instance++)
    {
        if (s_pxpBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_pxpBases));

    return instance;
}

#if !(defined(FSL_FEATURE_PXP_HAS_NO_CSC2) && FSL_FEATURE_PXP_HAS_NO_CSC2)
static uint32_t PXP_ConvertFloat(float floatValue, uint8_t intBits, uint8_t fracBits)
{
    /* One bit reserved for sign bit. */
    assert(intBits + fracBits < 32U);

    u32_f32_t u32_f32;
    uint32_t ret;

    u32_f32.f32        = floatValue;
    uint32_t floatBits = u32_f32.u32;
    int32_t expValue   = (int32_t)((uint16_t)((floatBits & 0x7F800000UL) >> 23U)) - 127;

    ret = (floatBits & 0x007FFFFFU) | 0x00800000U;
    expValue += (int32_t)fracBits;

    if (expValue < 0)
    {
        return 0U;
    }
    else if (expValue > 23)
    {
        /* should not exceed 31-bit when left shift. */
        assert((expValue - 23) <= 7);
        ret <<= ((uint16_t)expValue - 23U);
    }
    else
    {
        ret >>= (23U - (uint16_t)expValue);
    }

    /* Set the sign bit. */
    if ((floatBits & 0x80000000UL) != 0U)
    {
        ret = ((~ret) + 1UL) & ~(((uint32_t)-1) << ((uint32_t)intBits + (uint32_t)fracBits + 1UL));
    }

    return ret;
}
#endif

static void PXP_GetScalerParam(uint16_t inputDimension, uint16_t outputDimension, uint8_t *dec, uint32_t *scale)
{
    uint32_t scaleFact = ((uint32_t)inputDimension << 12U) / outputDimension;

    if (scaleFact >= (16UL << 12U))
    {
        /* Desired fact is two large, use the largest support value. */
        *dec   = 3U;
        *scale = 0x2000U;
    }
    else
    {
        if (scaleFact > (8UL << 12U))
        {
            *dec = 3U;
        }
        else if (scaleFact > (4UL << 12U))
        {
            *dec = 2U;
        }
        else if (scaleFact > (2UL << 12U))
        {
            *dec = 1U;
        }
        else
        {
            *dec = 0U;
        }

        *scale = scaleFact >> (*dec);

        if (0U == *scale)
        {
            *scale = 1U;
        }
    }
}

static void PXP_ResetToInit(PXP_Type *base)
{
    uint32_t ctrl = 0U;

    PXP_Reset(base);

/* Enable the process engine in primary processing flow. */
#if defined(PXP_CTRL_ENABLE_ROTATE0_MASK)
    ctrl |= PXP_CTRL_ENABLE_ROTATE0_MASK;
#endif
#if defined(PXP_CTRL_ENABLE_ROTATE1_MASK)
    ctrl |= PXP_CTRL_ENABLE_ROTATE1_MASK;
#endif
#if defined(PXP_CTRL_ENABLE_CSC2_MASK)
    ctrl |= PXP_CTRL_ENABLE_CSC2_MASK;
#endif
#if defined(PXP_CTRL_ENABLE_LUT_MASK)
    ctrl |= PXP_CTRL_ENABLE_LUT_MASK;
#endif
#if defined(PXP_CTRL_ENABLE_PS_AS_OUT_MASK)
    ctrl |= PXP_CTRL_ENABLE_PS_AS_OUT_MASK;
#endif

    base->CTRL = ctrl;
}

/*!
 * brief Initialize the PXP.
 *
 * This function enables the PXP peripheral clock, and resets the PXP registers
 * to default status.
 *
 * param base PXP peripheral base address.
 */
void PXP_Init(PXP_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    uint32_t instance = PXP_GetInstance(base);
    CLOCK_EnableClock(s_pxpClocks[instance]);
#endif

    PXP_ResetToInit(base);

    /* Disable the alpha surface. */
    PXP_SetAlphaSurfacePosition(base, 0xFFFFU, 0xFFFFU, 0U, 0U);
}

/*!
 * brief De-initialize the PXP.
 *
 * This function disables the PXP peripheral clock.
 *
 * param base PXP peripheral base address.
 */
void PXP_Deinit(PXP_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    uint32_t instance = PXP_GetInstance(base);
    CLOCK_DisableClock(s_pxpClocks[instance]);
#endif
}

/*!
 * brief Reset the PXP.
 *
 * This function resets the PXP peripheral registers to default status.
 *
 * param base PXP peripheral base address.
 */
void PXP_Reset(PXP_Type *base)
{
    base->CTRL_SET = PXP_CTRL_SFTRST_MASK;
    base->CTRL_CLR = (PXP_CTRL_SFTRST_MASK | PXP_CTRL_CLKGATE_MASK);
}

/*!
 * brief Set the alpha surface input buffer configuration.
 *
 * param base PXP peripheral base address.
 * param config Pointer to the configuration.
 */
void PXP_SetAlphaSurfaceBufferConfig(PXP_Type *base, const pxp_as_buffer_config_t *config)
{
    assert(NULL != config);

    base->AS_CTRL = (base->AS_CTRL & ~PXP_AS_CTRL_FORMAT_MASK) | PXP_AS_CTRL_FORMAT(config->pixelFormat);

    base->AS_BUF   = PXP_ADDR_CPU_2_IP(config->bufferAddr);
    base->AS_PITCH = config->pitchBytes;
}

/*!
 * brief Set the alpha surface blending configuration.
 *
 * param base PXP peripheral base address.
 * param config Pointer to the configuration structure.
 */
void PXP_SetAlphaSurfaceBlendConfig(PXP_Type *base, const pxp_as_blend_config_t *config)
{
    assert(NULL != config);
    uint32_t reg;

    reg = base->AS_CTRL;
    reg &=
        ~(PXP_AS_CTRL_ALPHA0_INVERT_MASK | PXP_AS_CTRL_ROP_MASK | PXP_AS_CTRL_ALPHA_MASK | PXP_AS_CTRL_ALPHA_CTRL_MASK);
    reg |= (PXP_AS_CTRL_ROP(config->ropMode) | PXP_AS_CTRL_ALPHA(config->alpha) |
            PXP_AS_CTRL_ALPHA_CTRL(config->alphaMode));

    if (config->invertAlpha)
    {
        reg |= PXP_AS_CTRL_ALPHA0_INVERT_MASK;
    }

    base->AS_CTRL = reg;
}

#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3
/*!
 * brief Set the alpha surface blending configuration for the secondary engine.
 *
 * param base PXP peripheral base address.
 * param config Pointer to the configuration structure.
 */
void PXP_SetAlphaSurfaceBlendSecondaryConfig(PXP_Type *base, const pxp_as_blend_secondary_config_t *config)
{
    assert(NULL != config);

    base->ALPHA_B_CTRL_1 =
        (base->ALPHA_B_CTRL_1 & ~(PXP_ALPHA_B_CTRL_1_ROP_MASK | PXP_ALPHA_B_CTRL_1_ROP_ENABLE_MASK)) |
        PXP_ALPHA_B_CTRL_1_ROP((uint32_t)config->ropMode) | PXP_ALPHA_B_CTRL_1_ROP_ENABLE((uint32_t)config->ropEnable);

    if (config->invertAlpha)
    {
        base->AS_CTRL |= PXP_AS_CTRL_ALPHA1_INVERT_MASK;
    }
    else
    {
        base->AS_CTRL &= ~PXP_AS_CTRL_ALPHA1_INVERT_MASK;
    }
}
#endif /* FSL_FEATURE_PXP_V3 */

/*!
 * brief Set the alpha surface position in output buffer.
 *
 * param base PXP peripheral base address.
 * param upperLeftX X of the upper left corner.
 * param upperLeftY Y of the upper left corner.
 * param lowerRightX X of the lower right corner.
 * param lowerRightY Y of the lower right corner.
 */
void PXP_SetAlphaSurfacePosition(
    PXP_Type *base, uint16_t upperLeftX, uint16_t upperLeftY, uint16_t lowerRightX, uint16_t lowerRightY)
{
    base->OUT_AS_ULC = PXP_OUT_AS_ULC_Y(upperLeftY) | PXP_OUT_AS_ULC_X(upperLeftX);
    base->OUT_AS_LRC = PXP_OUT_AS_LRC_Y(lowerRightY) | PXP_OUT_AS_LRC_X(lowerRightX);
}

#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3
/*!
 * brief Set the alpha surface overlay color key.
 *
 * If a pixel in the current overlay image with a color that falls in the range
 * from the p colorKeyLow to p colorKeyHigh range, it will use the process surface
 * pixel value for that location. If no PS image is present or if the PS image also
 * matches its colorkey range, the PS background color is used.
 *
 * param base PXP peripheral base address.
 * param num instance number. 0 for alpha engine A, 1 for alpha engine B.
 * param colorKeyLow Color key low range.
 * param colorKeyHigh Color key high range.
 *
 * note Colorkey operations are higher priority than alpha or ROP operations
 */
void PXP_SetAlphaSurfaceOverlayColorKey(PXP_Type *base, uint8_t num, uint32_t colorKeyLow, uint32_t colorKeyHigh)
{
    switch (num)
    {
        case 0:
            base->AS_CLRKEYLOW  = colorKeyLow;
            base->AS_CLRKEYHIGH = colorKeyHigh;
            break;

        case 1:
            base->AS_CLRKEYLOW_1  = colorKeyLow;
            base->AS_CLRKEYHIGH_1 = colorKeyHigh;
            break;

        default:
            /* Only 2 alpha process engine instances are supported. */
            assert(false);
            break;
    }
}
#else
/*!
 * brief Set the alpha surface overlay color key.
 *
 * If a pixel in the current overlay image with a color that falls in the range
 * from the p colorKeyLow to p colorKeyHigh range, it will use the process surface
 * pixel value for that location. If no PS image is present or if the PS image also
 * matches its colorkey range, the PS background color is used.
 *
 * param base PXP peripheral base address.
 * param colorKeyLow Color key low range.
 * param colorKeyHigh Color key high range.
 *
 * note Colorkey operations are higher priority than alpha or ROP operations
 */
void PXP_SetAlphaSurfaceOverlayColorKey(PXP_Type *base, uint32_t colorKeyLow, uint32_t colorKeyHigh)
{
    base->AS_CLRKEYLOW  = colorKeyLow;
    base->AS_CLRKEYHIGH = colorKeyHigh;
}
#endif /* FSL_FEATURE_PXP_V3 */

/*!
 * brief Set the process surface input buffer configuration.
 *
 * param base PXP peripheral base address.
 * param config Pointer to the configuration.
 */
void PXP_SetProcessSurfaceBufferConfig(PXP_Type *base, const pxp_ps_buffer_config_t *config)
{
    assert(NULL != config);

    base->PS_CTRL = ((base->PS_CTRL & ~(PXP_PS_CTRL_FORMAT_MASK | PXP_PS_CTRL_WB_SWAP_MASK)) |
                     PXP_PS_CTRL_FORMAT(config->pixelFormat) | PXP_PS_CTRL_WB_SWAP(config->swapByte));

    base->PS_BUF   = PXP_ADDR_CPU_2_IP(config->bufferAddr);
    base->PS_UBUF  = PXP_ADDR_CPU_2_IP(config->bufferAddrU);
    base->PS_VBUF  = PXP_ADDR_CPU_2_IP(config->bufferAddrV);
    base->PS_PITCH = config->pitchBytes;
}

/*!
 * brief Set the process surface scaler configuration.
 *
 * The valid down scale fact is 1/(2^12) ~ 16.
 *
 * param base PXP peripheral base address.
 * param inputWidth Input image width.
 * param inputHeight Input image height.
 * param outputWidth Output image width.
 * param outputHeight Output image height.
 */
void PXP_SetProcessSurfaceScaler(
    PXP_Type *base, uint16_t inputWidth, uint16_t inputHeight, uint16_t outputWidth, uint16_t outputHeight)
{
    uint8_t decX, decY;
    uint32_t scaleX, scaleY;

    PXP_GetScalerParam(inputWidth, outputWidth, &decX, &scaleX);
    PXP_GetScalerParam(inputHeight, outputHeight, &decY, &scaleY);

    base->PS_CTRL = (base->PS_CTRL & ~(PXP_PS_CTRL_DECX_MASK | PXP_PS_CTRL_DECY_MASK)) | PXP_PS_CTRL_DECX(decX) |
                    PXP_PS_CTRL_DECY(decY);

    base->PS_SCALE = PXP_PS_SCALE_XSCALE(scaleX) | PXP_PS_SCALE_YSCALE(scaleY);
}

/*!
 * brief Set the process surface position in output buffer.
 *
 * param base PXP peripheral base address.
 * param upperLeftX X of the upper left corner.
 * param upperLeftY Y of the upper left corner.
 * param lowerRightX X of the lower right corner.
 * param lowerRightY Y of the lower right corner.
 */
void PXP_SetProcessSurfacePosition(
    PXP_Type *base, uint16_t upperLeftX, uint16_t upperLeftY, uint16_t lowerRightX, uint16_t lowerRightY)
{
    base->OUT_PS_ULC = PXP_OUT_PS_ULC_Y(upperLeftY) | PXP_OUT_PS_ULC_X(upperLeftX);
    base->OUT_PS_LRC = PXP_OUT_PS_LRC_Y(lowerRightY) | PXP_OUT_PS_LRC_X(lowerRightX);
}

#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3
/*!
 * brief Set the process surface color key.
 *
 * If the PS image matches colorkey range, the PS background color is output. Set
 * p colorKeyLow to 0xFFFFFFFF and p colorKeyHigh to 0 will disable the colorkeying.
 *
 * param base PXP peripheral base address.
 * param num instance number. 0 for alpha engine A, 1 for alpha engine B.
 * param colorKeyLow Color key low range.
 * param colorKeyHigh Color key high range.
 */
void PXP_SetProcessSurfaceColorKey(PXP_Type *base, uint8_t num, uint32_t colorKeyLow, uint32_t colorKeyHigh)
{
    switch (num)
    {
        case 0:
            base->PS_CLRKEYLOW  = colorKeyLow;
            base->PS_CLRKEYHIGH = colorKeyHigh;
            break;

        case 1:
            base->PS_CLRKEYLOW_1  = colorKeyLow;
            base->PS_CLRKEYHIGH_1 = colorKeyHigh;
            break;

        default:
            /* Only 2 alpha process engine instances are supported. */
            assert(false);
            break;
    }
}
#else
/*!
 * brief Set the process surface color key.
 *
 * If the PS image matches colorkey range, the PS background color is output. Set
 * p colorKeyLow to 0xFFFFFFFF and p colorKeyHigh to 0 will disable the colorkeying.
 *
 * param base PXP peripheral base address.
 * param colorKeyLow Color key low range.
 * param colorKeyHigh Color key high range.
 */
void PXP_SetProcessSurfaceColorKey(PXP_Type *base, uint32_t colorKeyLow, uint32_t colorKeyHigh)
{
    base->PS_CLRKEYLOW  = colorKeyLow;
    base->PS_CLRKEYHIGH = colorKeyHigh;
}
#endif /* FSL_FEATURE_PXP_V3 */

/*!
 * brief Set the PXP outpt buffer configuration.
 *
 * param base PXP peripheral base address.
 * param config Pointer to the configuration.
 */
void PXP_SetOutputBufferConfig(PXP_Type *base, const pxp_output_buffer_config_t *config)
{
    assert(NULL != config);

    base->OUT_CTRL = (base->OUT_CTRL & ~(PXP_OUT_CTRL_FORMAT_MASK | PXP_OUT_CTRL_INTERLACED_OUTPUT_MASK)) |
                     PXP_OUT_CTRL_FORMAT(config->pixelFormat) | PXP_OUT_CTRL_INTERLACED_OUTPUT(config->interlacedMode);

    base->OUT_BUF  = PXP_ADDR_CPU_2_IP(config->buffer0Addr);
    base->OUT_BUF2 = PXP_ADDR_CPU_2_IP(config->buffer1Addr);

    base->OUT_PITCH = config->pitchBytes;
    base->OUT_LRC   = PXP_OUT_LRC_Y((uint32_t)config->height - 1U) | PXP_OUT_LRC_X((uint32_t)config->width - 1U);

/*
 * The dither store size must be set to the same with the output buffer size,
 * otherwise the dither engine could not work.
 */
#if defined(PXP_DITHER_STORE_SIZE_CH0_OUT_WIDTH_MASK)
    base->DITHER_STORE_SIZE_CH0 = PXP_DITHER_STORE_SIZE_CH0_OUT_WIDTH((uint32_t)config->width - 1U) |
                                  PXP_DITHER_STORE_SIZE_CH0_OUT_HEIGHT((uint32_t)config->height - 1U);
#endif
}

/*!
 * brief Build a solid rectangle of given pixel value.
 *
 * param base PXP peripheral base address.
 * param outFormat output pixel format.
 * param value The value of the pixel to be filled in the rectangle in ARGB8888 format.
 * param width width of the rectangle.
 * param height height of the rectangle.
 * param pitch output pitch in byte.
 * param outAddr address of the memory to store the rectangle.
 */
void PXP_BuildRect(PXP_Type *base,
                   pxp_output_pixel_format_t outFormat,
                   uint32_t value,
                   uint16_t width,
                   uint16_t height,
                   uint16_t pitch,
                   uint32_t outAddr)
{
    /* Only support RGB format output. */
    assert((uint8_t)outFormat <= (uint8_t)kPXP_OutputPixelFormatRGB565);

    /* PS configuration */
#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3
    PXP_SetProcessSurfaceBackGroundColor(base, 0U, value);
#else
    PXP_SetProcessSurfaceBackGroundColor(base, value);
#endif
    PXP_SetProcessSurfacePosition(base, 0xFFFF, 0xFFFF, 0, 0);

    if ((outFormat == kPXP_OutputPixelFormatARGB8888) || (outFormat == kPXP_OutputPixelFormatARGB1555) ||
        (outFormat == kPXP_OutputPixelFormatARGB4444))
    {
        uint8_t alpha                         = (uint8_t)(value >> 24U);
        pxp_as_buffer_config_t asBufferConfig = {
            .pixelFormat = kPXP_AsPixelFormatARGB8888,
            .bufferAddr  = outAddr,
            .pitchBytes  = pitch,
        };
        PXP_SetAlphaSurfaceBufferConfig(base, &asBufferConfig);

        pxp_as_blend_config_t asBlendConfig = {
            .alpha = alpha, .invertAlpha = false, .alphaMode = kPXP_AlphaOverride, .ropMode = kPXP_RopMergeAs};
        PXP_SetAlphaSurfaceBlendConfig(base, &asBlendConfig);
#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3
        PXP_SetAlphaSurfaceOverlayColorKey(base, 0U, 0U, 0xFFFFFFFFUL);
        PXP_EnableAlphaSurfaceOverlayColorKey(base, 0U, true);
#else
        PXP_SetAlphaSurfaceOverlayColorKey(base, 0U, 0xFFFFFFFFUL);
        PXP_EnableAlphaSurfaceOverlayColorKey(base, true);
#endif
        PXP_SetAlphaSurfacePosition(base, 0, 0, width, height);
    }
    else
    {
        /* No need to configure AS for formats that do not have alpha value. */
        PXP_SetAlphaSurfacePosition(base, 0xFFFFU, 0xFFFFU, 0, 0);
    }

    /* Output config. */
    pxp_output_buffer_config_t outputBufferConfig;
    outputBufferConfig.pixelFormat    = outFormat;
    outputBufferConfig.interlacedMode = kPXP_OutputProgressive;
    outputBufferConfig.buffer0Addr    = outAddr;
    outputBufferConfig.buffer1Addr    = 0U;
    outputBufferConfig.pitchBytes     = pitch;
    outputBufferConfig.width          = width;
    outputBufferConfig.height         = height;
    PXP_SetOutputBufferConfig(base, &outputBufferConfig);

    PXP_EnableCsc1(base, false);

#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3
    PXP_SetPath(PXP, kPXP_Mux3SelectCsc1Engine);
    PXP_SetPath(PXP, kPXP_Mux8SelectAlphaBlending0);
    PXP_SetPath(PXP, kPXP_Mux11SelectMux8);
    PXP_SetPath(PXP, kPXP_Mux14SelectMux11);
    PXP_SetPath(PXP, kPXP_Mux0SelectNone);
    PXP_SetPath(PXP, kPXP_Mux6SelectNone);
    PXP_SetPath(PXP, kPXP_Mux9SelectNone);
    PXP_SetPath(PXP, kPXP_Mux12SelectNone);
#endif

    PXP_ClearStatusFlags(base, (uint32_t)kPXP_CompleteFlag);
    /* Start PXP. */
    PXP_Start(base);
    /* Wait for process complete. */
    while (0UL == ((uint32_t)kPXP_CompleteFlag & PXP_GetStatusFlags(base)))
    {
    }
}

/*!
 * brief Set the next command.
 *
 * The PXP supports a primitive ability to queue up one operation while the current
 * operation is running. Workflow:
 *
 * 1. Prepare the PXP register values except STAT, CSCCOEFn, NEXT in the memory
 * in the order they appear in the register map.
 * 2. Call this function sets the new operation to PXP.
 * 3. There are two methods to check whether the PXP has loaded the new operation.
 * The first method is using ref PXP_IsNextCommandPending. If there is new operation
 * not loaded by the PXP, this function returns true. The second method is checking
 * the flag ref kPXP_CommandLoadFlag, if command loaded, this flag asserts. User
 * could enable interrupt ref kPXP_CommandLoadInterruptEnable to get the loaded
 * signal in interrupt way.
 * 4. When command loaded by PXP, a new command could be set using this function.
 *
 * param base PXP peripheral base address.
 * param commandAddr Address of the new command.
 */
void PXP_SetNextCommand(PXP_Type *base, void *commandAddr)
{
    pxp_pvoid_u32_t addr;

    /* Make sure commands have been saved to memory. */
    __DSB();

    addr.pvoid = commandAddr;

    base->NEXT = PXP_ADDR_CPU_2_IP(addr.u32) & PXP_NEXT_POINTER_MASK;
}

#if !(defined(FSL_FEATURE_PXP_HAS_NO_CSC2) && FSL_FEATURE_PXP_HAS_NO_CSC2)
/*!
 * brief Set the CSC2 configuration.
 *
 * The CSC2 module receives pixels in any color space and can convert the pixels
 * into any of RGB, YUV, or YCbCr color spaces. The output pixels are passed
 * onto the LUT and rotation engine for further processing
 *
 * param base PXP peripheral base address.
 * param config Pointer to the configuration.
 */
void PXP_SetCsc2Config(PXP_Type *base, const pxp_csc2_config_t *config)
{
    assert(NULL != config);
    uint32_t tempReg;

    base->CSC2_CTRL = (base->CSC2_CTRL & ~PXP_CSC2_CTRL_CSC_MODE_MASK) | PXP_CSC2_CTRL_CSC_MODE(config->mode);

    tempReg =
        (PXP_ConvertFloat(config->A1, PXP_CSC2_COEF_INT_WIDTH, PXP_CSC2_COEF_FRAC_WIDTH) << PXP_CSC2_COEF0_A1_SHIFT);
    base->CSC2_COEF0 = tempReg | (PXP_ConvertFloat(config->A2, PXP_CSC2_COEF_INT_WIDTH, PXP_CSC2_COEF_FRAC_WIDTH)
                                  << PXP_CSC2_COEF0_A2_SHIFT);

    tempReg =
        (PXP_ConvertFloat(config->A3, PXP_CSC2_COEF_INT_WIDTH, PXP_CSC2_COEF_FRAC_WIDTH) << PXP_CSC2_COEF1_A3_SHIFT);
    base->CSC2_COEF1 = tempReg | (PXP_ConvertFloat(config->B1, PXP_CSC2_COEF_INT_WIDTH, PXP_CSC2_COEF_FRAC_WIDTH)
                                  << PXP_CSC2_COEF1_B1_SHIFT);

    tempReg =
        (PXP_ConvertFloat(config->B2, PXP_CSC2_COEF_INT_WIDTH, PXP_CSC2_COEF_FRAC_WIDTH) << PXP_CSC2_COEF2_B2_SHIFT);
    base->CSC2_COEF2 = tempReg | (PXP_ConvertFloat(config->B3, PXP_CSC2_COEF_INT_WIDTH, PXP_CSC2_COEF_FRAC_WIDTH)
                                  << PXP_CSC2_COEF2_B3_SHIFT);

    tempReg =
        (PXP_ConvertFloat(config->C1, PXP_CSC2_COEF_INT_WIDTH, PXP_CSC2_COEF_FRAC_WIDTH) << PXP_CSC2_COEF3_C1_SHIFT);
    base->CSC2_COEF3 = tempReg | (PXP_ConvertFloat(config->C2, PXP_CSC2_COEF_INT_WIDTH, PXP_CSC2_COEF_FRAC_WIDTH)
                                  << PXP_CSC2_COEF3_C2_SHIFT);

    tempReg =
        (PXP_ConvertFloat(config->C3, PXP_CSC2_COEF_INT_WIDTH, PXP_CSC2_COEF_FRAC_WIDTH) << PXP_CSC2_COEF4_C3_SHIFT);
    base->CSC2_COEF4 = tempReg | PXP_CSC2_COEF4_D1(config->D1);

    base->CSC2_COEF5 = PXP_CSC2_COEF5_D2(config->D2) | PXP_CSC2_COEF5_D3(config->D3);
}
#endif

/*!
 * brief Set the CSC1 mode.
 *
 * The CSC1 module receives scaled YUV/YCbCr444 pixels from the scale engine and
 * converts the pixels to the RGB888 color space. It could only be used by process
 * surface.
 *
 * param base PXP peripheral base address.
 * param mode The conversion mode.
 */
void PXP_SetCsc1Mode(PXP_Type *base, pxp_csc1_mode_t mode)
{
    /*
     * The equations used for Colorspace conversion are:
     *
     * R = C0*(Y+Y_OFFSET)                   + C1(V+UV_OFFSET)
     * G = C0*(Y+Y_OFFSET) + C3(U+UV_OFFSET) + C2(V+UV_OFFSET)
     * B = C0*(Y+Y_OFFSET) + C4(U+UV_OFFSET)
     */

    if (kPXP_Csc1YUV2RGB == mode)
    {
        base->CSC1_COEF0 = (base->CSC1_COEF0 & ~(PXP_CSC1_COEF0_C0_MASK | PXP_CSC1_COEF0_Y_OFFSET_MASK |
                                                 PXP_CSC1_COEF0_UV_OFFSET_MASK | PXP_CSC1_COEF0_YCBCR_MODE_MASK)) |
                           PXP_CSC1_COEF0_C0(0x100U)         /* 1.00. */
                           | PXP_CSC1_COEF0_Y_OFFSET(0x0U)   /* 0. */
                           | PXP_CSC1_COEF0_UV_OFFSET(0x0U); /* 0. */
        base->CSC1_COEF1 = PXP_CSC1_COEF1_C1(0x0123U)        /* 1.140. */
                           | PXP_CSC1_COEF1_C4(0x0208U);     /* 2.032. */
        base->CSC1_COEF2 = PXP_CSC1_COEF2_C2(0x076BU)        /* -0.851. */
                           | PXP_CSC1_COEF2_C3(0x079BU);     /* -0.394. */
    }
    else
    {
        base->CSC1_COEF0 = (base->CSC1_COEF0 &
                            ~(PXP_CSC1_COEF0_C0_MASK | PXP_CSC1_COEF0_Y_OFFSET_MASK | PXP_CSC1_COEF0_UV_OFFSET_MASK)) |
                           PXP_CSC1_COEF0_YCBCR_MODE_MASK | PXP_CSC1_COEF0_C0(0x12AU) /* 1.164. */
                           | PXP_CSC1_COEF0_Y_OFFSET(0x1F0U)                          /* -16. */
                           | PXP_CSC1_COEF0_UV_OFFSET(0x180U);                        /* -128. */
        base->CSC1_COEF1 = PXP_CSC1_COEF1_C1(0x0198U)                                 /* 1.596. */
                           | PXP_CSC1_COEF1_C4(0x0204U);                              /* 2.017. */
        base->CSC1_COEF2 = PXP_CSC1_COEF2_C2(0x0730U)                                 /* -0.813. */
                           | PXP_CSC1_COEF2_C3(0x079CU);                              /* -0.392. */
    }
}

#if !(defined(FSL_FEATURE_PXP_HAS_NO_LUT) && FSL_FEATURE_PXP_HAS_NO_LUT)
/*!
 * brief Set the LUT configuration.
 *
 * The lookup table (LUT) is used to modify pixels in a manner that is not linear
 * and that cannot be achieved by the color space conversion modules. To setup
 * the LUT, the complete workflow is:
 * 1. Use ref PXP_SetLutConfig to set the configuration, such as the lookup mode.
 * 2. Use ref PXP_LoadLutTable to load the lookup table to PXP.
 * 3. Use ref PXP_EnableLut to enable the function.
 *
 * param base PXP peripheral base address.
 * param config Pointer to the configuration.
 */
void PXP_SetLutConfig(PXP_Type *base, const pxp_lut_config_t *config)
{
    base->LUT_CTRL = (base->LUT_CTRL & ~(PXP_LUT_CTRL_OUT_MODE_MASK | PXP_LUT_CTRL_LOOKUP_MODE_MASK)) |
                     PXP_LUT_CTRL_LRU_UPD_MASK | /* Use Least Recently Used Policy Update Control. */
                     PXP_LUT_CTRL_OUT_MODE(config->outMode) | PXP_LUT_CTRL_LOOKUP_MODE(config->lookupMode);

    if (kPXP_LutOutRGBW4444CFA == config->outMode)
    {
        base->CFA = config->cfaValue;
    }
}

/*!
 * brief Set the look up table to PXP.
 *
 * If lookup mode is DIRECT mode, this function loads p bytesNum of values
 * from the address p memAddr into PXP LUT address p lutStartAddr. So this
 * function allows only update part of the PXP LUT.
 *
 * If lookup mode is CACHE mode, this function sets the new address to p memAddr
 * and invalid the PXP LUT cache.
 *
 * param base PXP peripheral base address.
 * param lookupMode Which lookup mode is used. Note that this parameter is only
 * used to distinguish DIRECT mode and CACHE mode, it does not change the register
 * value PXP_LUT_CTRL[LOOKUP_MODE]. To change that value, use function ref PXP_SetLutConfig.
 * param bytesNum How many bytes to set. This value must be divisable by 8.
 * param memAddr Address of look up table to set.
 * param lutStartAddr The LUT value will be loaded to LUT from index lutAddr. It should
 * be 8 bytes aligned.
 *
 * retval kStatus_Success Load successfully.
 * retval kStatus_InvalidArgument Failed because of invalid argument.
 */
status_t PXP_LoadLutTable(
    PXP_Type *base, pxp_lut_lookup_mode_t lookupMode, uint32_t bytesNum, uint32_t memAddr, uint16_t lutStartAddr)
{
    memAddr = PXP_ADDR_CPU_2_IP(memAddr);

    if (kPXP_LutCacheRGB565 == lookupMode)
    {
        /* Make sure the previous memory write is finished, especially the LUT data memory. */
        __DSB();

        base->LUT_EXTMEM = memAddr;
        /* Invalid cache. */
        base->LUT_CTRL |= PXP_LUT_CTRL_INVALID_MASK;
    }
    else
    {
        /* Number of bytes must be divisable by 8. */
        if (((bytesNum & 0x07U) != 0U) || (bytesNum < 8U) || ((lutStartAddr & 0x07U) != 0U) ||
            (bytesNum + (uint32_t)lutStartAddr > PXP_LUT_TABLE_BYTE))
        {
            return kStatus_InvalidArgument;
        }

        base->LUT_EXTMEM = memAddr;
        base->LUT_ADDR   = PXP_LUT_ADDR_ADDR(lutStartAddr) | PXP_LUT_ADDR_NUM_BYTES(bytesNum);

        base->STAT_CLR = PXP_STAT_LUT_DMA_LOAD_DONE_IRQ_MASK;

        /* Start DMA transfer. */
        base->LUT_CTRL |= PXP_LUT_CTRL_DMA_START_MASK;

        __DSB();

        /* Wait for transfer completed. */
        while (0U == (base->STAT & PXP_STAT_LUT_DMA_LOAD_DONE_IRQ_MASK))
        {
        }
    }

    return kStatus_Success;
}
#endif /* FSL_FEATURE_PXP_HAS_NO_LUT */

#if (defined(FSL_FEATURE_PXP_HAS_DITHER) && FSL_FEATURE_PXP_HAS_DITHER)
/*!
 * brief Write data to the PXP internal memory.
 *
 * param base PXP peripheral base address.
 * param ram Which internal memory to write.
 * param bytesNum How many bytes to write.
 * param data Pointer to the data to write.
 * param memStartAddr The start address in the internal memory to write the data.
 */
void PXP_SetInternalRamData(PXP_Type *base, pxp_ram_t ram, uint32_t bytesNum, uint8_t *data, uint16_t memStartAddr)
{
    assert(((uint32_t)memStartAddr + bytesNum) <= (uint32_t)PXP_INTERNAL_RAM_LUT_BYTE);

    base->INIT_MEM_CTRL =
        PXP_INIT_MEM_CTRL_ADDR(memStartAddr) | PXP_INIT_MEM_CTRL_SELECT(ram) | PXP_INIT_MEM_CTRL_START_MASK;

    while (0U != bytesNum--)
    {
        base->INIT_MEM_DATA = (uint32_t)(*data);
        data++;
    }

    base->INIT_MEM_CTRL = 0U;
}

/*!
 * brief Set the dither final LUT data.
 *
 * The dither final LUT is only applicble to dither engine 0. It takes the bits[7:4]
 * of the output pixel and looks up and 8 bit value from the 16 value LUT to generate
 * the final output pixel to the next process module.
 *
 * param base PXP peripheral base address.
 * param data Pointer to the LUT data to set.
 */
void PXP_SetDitherFinalLutData(PXP_Type *base, const pxp_dither_final_lut_data_t *data)
{
    base->DITHER_FINAL_LUT_DATA0 = data->data_3_0;
    base->DITHER_FINAL_LUT_DATA1 = data->data_7_4;
    base->DITHER_FINAL_LUT_DATA2 = data->data_11_8;
    base->DITHER_FINAL_LUT_DATA3 = data->data_15_12;
}

/*!
 * brief Enable or disable dither engine in the PXP process path.
 *
 * After the initialize function ref PXP_Init, the dither engine is disabled and not
 * use in the PXP processing path. This function enables the dither engine and
 * routes the dither engine output to the output buffer. When the dither engine
 * is enabled using this function, ref PXP_SetDitherConfig must be called to
 * configure dither engine correctly, otherwise there is not output to the output
 * buffer.
 *
 * param base PXP peripheral base address.
 * param enable Pass in true to enable, false to disable.
 */
void PXP_EnableDither(PXP_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL_SET = PXP_CTRL_ENABLE_DITHER_MASK;
    }
    else
    {
        base->CTRL_CLR = PXP_CTRL_ENABLE_DITHER_MASK;
    }
}
#endif /* FSL_FEATURE_PXP_HAS_DITHER */

#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3
/*!
 * brief Set the Porter Duff configuration for one of the alpha process engine.
 *
 * param base PXP peripheral base address.
 * param num instance number.
 * param config Pointer to the configuration.
 */
void PXP_SetPorterDuffConfig(PXP_Type *base, uint8_t num, const pxp_porter_duff_config_t *config)
{
    assert(NULL != config);

    union
    {
        pxp_porter_duff_config_t pdConfigStruct;
        uint32_t u32;
    } pdConfig;

    pdConfig.pdConfigStruct = *config;

    switch (num)
    {
        case 0:
            base->ALPHA_A_CTRL = pdConfig.u32;
            break;

        case 1:
            base->ALPHA_B_CTRL = pdConfig.u32;
            break;

        default:
            /* Only 2 alpha process engine instances are supported. */
            assert(false);
            break;
    }
}
#endif /* FSL_FEATURE_PXP_V3 */

#if !(defined(FSL_FEATURE_PXP_HAS_NO_PORTER_DUFF_CTRL) && FSL_FEATURE_PXP_HAS_NO_PORTER_DUFF_CTRL)
/*!
 * brief Set the Porter Duff configuration.
 *
 * param base PXP peripheral base address.
 * param config Pointer to the configuration.
 */
void PXP_SetPorterDuffConfig(PXP_Type *base, const pxp_porter_duff_config_t *config)
{
    assert(NULL != config);

    union
    {
        pxp_porter_duff_config_t pdConfigStruct;
        uint32_t u32;
    } pdConfig;

    pdConfig.pdConfigStruct = *config;

    base->PORTER_DUFF_CTRL = pdConfig.u32;
}
#endif /* FSL_FEATURE_PXP_HAS_NO_PORTER_DUFF_CTRL */

#if (!(defined(FSL_FEATURE_PXP_HAS_NO_PORTER_DUFF_CTRL) && FSL_FEATURE_PXP_HAS_NO_PORTER_DUFF_CTRL)) || \
    (defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3)
/*!
 * brief Get the Porter Duff configuration by blend mode.
 *
 * param mode The blend mode.
 * param config Pointer to the configuration.
 * retval kStatus_Success Successfully get the configuratoin.
 * retval kStatus_InvalidArgument The blend mode not supported.
 */
status_t PXP_GetPorterDuffConfig(pxp_porter_duff_blend_mode_t mode, pxp_porter_duff_config_t *config)
{
    status_t status;

    union
    {
        pxp_porter_duff_config_t pdConfigStruct;
        uint32_t u32;
    } pdConfig;

    static const uint32_t pdCtrl[] = {
        /* kPXP_PorterDuffSrc */
        PORTER_DUFF_ENABLE_MASK | S0_S1_FACTOR_MODE(kPXP_PorterDuffFactorOne) |
            S1_S0_FACTOR_MODE(kPXP_PorterDuffFactorZero),

        /* kPXP_PorterDuffAtop */
        PORTER_DUFF_ENABLE_MASK | S0_S1_FACTOR_MODE(kPXP_PorterDuffFactorStraight) |
            S1_S0_FACTOR_MODE(kPXP_PorterDuffFactorInversed),

        /* kPXP_PorterDuffOver */
        PORTER_DUFF_ENABLE_MASK | S0_S1_FACTOR_MODE(kPXP_PorterDuffFactorOne) |
            S1_S0_FACTOR_MODE(kPXP_PorterDuffFactorInversed),

        /* kPXP_PorterDuffIn */
        PORTER_DUFF_ENABLE_MASK | S0_S1_FACTOR_MODE(kPXP_PorterDuffFactorStraight) |
            S1_S0_FACTOR_MODE(kPXP_PorterDuffFactorZero),

        /* kPXP_PorterDuffOut */
        PORTER_DUFF_ENABLE_MASK | S0_S1_FACTOR_MODE(kPXP_PorterDuffFactorInversed) |
            S1_S0_FACTOR_MODE(kPXP_PorterDuffFactorZero),

        /* kPXP_PorterDuffDst */
        PORTER_DUFF_ENABLE_MASK | S0_S1_FACTOR_MODE(kPXP_PorterDuffFactorZero) |
            S1_S0_FACTOR_MODE(kPXP_PorterDuffFactorOne),

        /* kPXP_PorterDuffDstAtop */
        PORTER_DUFF_ENABLE_MASK | S0_S1_FACTOR_MODE(kPXP_PorterDuffFactorInversed) |
            S1_S0_FACTOR_MODE(kPXP_PorterDuffFactorStraight),

        /* kPXP_PorterDuffDstOver */
        PORTER_DUFF_ENABLE_MASK | S0_S1_FACTOR_MODE(kPXP_PorterDuffFactorInversed) |
            S1_S0_FACTOR_MODE(kPXP_PorterDuffFactorOne),

        /* kPXP_PorterDuffDstIn */
        PORTER_DUFF_ENABLE_MASK | S0_S1_FACTOR_MODE(kPXP_PorterDuffFactorZero) |
            S1_S0_FACTOR_MODE(kPXP_PorterDuffFactorStraight),

        /* kPXP_PorterDuffDstOut */
        PORTER_DUFF_ENABLE_MASK | S0_S1_FACTOR_MODE(kPXP_PorterDuffFactorZero) |
            S1_S0_FACTOR_MODE(kPXP_PorterDuffFactorInversed),

        /* kPXP_PorterDuffXor */
        PORTER_DUFF_ENABLE_MASK | S0_S1_FACTOR_MODE(kPXP_PorterDuffFactorInversed) |
            S1_S0_FACTOR_MODE(kPXP_PorterDuffFactorInversed),

        /* kPXP_PorterDuffClear */
        PORTER_DUFF_ENABLE_MASK | S0_S1_FACTOR_MODE(kPXP_PorterDuffFactorZero) |
            S1_S0_FACTOR_MODE(kPXP_PorterDuffFactorZero),
    };

    if (mode >= kPXP_PorterDuffMax)
    {
        status = kStatus_InvalidArgument;
    }
    else
    {
        pdConfig.u32 = pdCtrl[(uint32_t)mode] | S0_GLOBAL_ALPHA_MODE(kPXP_PorterDuffLocalAlpha) |
                       S1_GLOBAL_ALPHA_MODE(kPXP_PorterDuffLocalAlpha) | S0_COLOR_MODE(kPXP_PorterDuffColorWithAlpha) |
                       S1_COLOR_MODE(kPXP_PorterDuffColorWithAlpha) | S0_ALPHA_MODE(kPXP_PorterDuffAlphaStraight) |
                       S1_ALPHA_MODE(kPXP_PorterDuffAlphaStraight);

        *config = pdConfig.pdConfigStruct;

        status = kStatus_Success;
    }

    return status;
}
#endif /* FSL_FEATURE_PXP_V3 || FSL_FEATURE_PXP_HAS_NO_PORTER_DUFF_CTRL  */

static void PXP_StartRectCopy(PXP_Type *base,
                              uint32_t srcAddr,
                              uint16_t srcPitchBytes,
                              uint32_t destAddr,
                              uint16_t destPitchBytes,
                              uint16_t width,
                              uint16_t height,
                              pxp_as_pixel_format_t pixelFormat)
{
    pxp_output_buffer_config_t outputBufferConfig;
    pxp_as_buffer_config_t asBufferConfig;
    uint32_t intMask;

#if !(defined(FSL_FEATURE_PXP_HAS_NO_LUT) && FSL_FEATURE_PXP_HAS_NO_LUT)
    intMask =
        base->CTRL & (PXP_CTRL_NEXT_IRQ_ENABLE_MASK | PXP_CTRL_IRQ_ENABLE_MASK | PXP_CTRL_LUT_DMA_IRQ_ENABLE_MASK);
#else
    intMask = base->CTRL & (PXP_CTRL_NEXT_IRQ_ENABLE_MASK | PXP_CTRL_IRQ_ENABLE_MASK);
#endif

    PXP_ResetToInit(base);

    /* Restore previous interrupt configuration. */
    PXP_EnableInterrupts(base, intMask);

    /* Disable PS */
    PXP_SetProcessSurfacePosition(base, 0xFFFFU, 0xFFFFU, 0U, 0U);

    /* Input buffer. */
    asBufferConfig.pixelFormat = pixelFormat;
    asBufferConfig.bufferAddr  = srcAddr;
    asBufferConfig.pitchBytes  = srcPitchBytes;

    PXP_SetAlphaSurfaceBufferConfig(base, &asBufferConfig);
    PXP_SetAlphaSurfacePosition(base, 0U, 0U, width - 1U, height - 1U);

    /* Alpha mode set to ROP, AS OR PS */
    const pxp_as_blend_config_t asBlendConfig = {
        .alpha = 0U, .invertAlpha = false, .alphaMode = kPXP_AlphaRop, .ropMode = kPXP_RopMergeAs};

    PXP_SetAlphaSurfaceBlendConfig(base, &asBlendConfig);

    /* Output buffer. */
    outputBufferConfig.pixelFormat    = (pxp_output_pixel_format_t)pixelFormat;
    outputBufferConfig.interlacedMode = kPXP_OutputProgressive;
    outputBufferConfig.buffer0Addr    = destAddr;
    outputBufferConfig.buffer1Addr    = 0U;
    outputBufferConfig.pitchBytes     = destPitchBytes;
    outputBufferConfig.width          = width;
    outputBufferConfig.height         = height;

    PXP_SetOutputBufferConfig(base, &outputBufferConfig);

    PXP_ClearStatusFlags(base, (uint32_t)kPXP_CompleteFlag);

    PXP_Start(base);
}

/*!
 * brief Copy picture from one buffer to another buffer.
 *
 * This function copies a rectangle from one buffer to another buffer.
 *
 * param base PXP peripheral base address.
 * retval kStatus_Success Successfully started the copy process.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t PXP_StartPictureCopy(PXP_Type *base, const pxp_pic_copy_config_t *config)
{
    uint8_t bytePerPixel;
    uint32_t copyFromAddr;
    uint32_t copyToAddr;

    if ((0U == config->height) || (0U == config->width))
    {
        return kStatus_InvalidArgument;
    }

    if ((config->pixelFormat == kPXP_AsPixelFormatARGB8888) || (config->pixelFormat == kPXP_AsPixelFormatRGB888))
    {
        bytePerPixel = 4U;
    }
    else
    {
        bytePerPixel = 2U;
    }

    copyFromAddr = config->srcPicBaseAddr + ((uint32_t)config->srcOffsetY * (uint32_t)config->srcPitchBytes) +
                   bytePerPixel * config->srcOffsetX;
    copyToAddr = config->destPicBaseAddr + ((uint32_t)config->destOffsetY * (uint32_t)config->destPitchBytes) +
                 bytePerPixel * config->destOffsetX;

    PXP_StartRectCopy(base, copyFromAddr, config->srcPitchBytes, copyToAddr, config->destPitchBytes, config->width,
                      config->height, config->pixelFormat);

    return kStatus_Success;
}

/*!
 * brief Copy continous memory.
 *
 * The copy size should be 512 byte aligned.
 *
 * param base PXP peripheral base address.
 * retval kStatus_Success Successfully started the copy process.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t PXP_StartMemCopy(PXP_Type *base, uint32_t srcAddr, uint32_t destAddr, uint32_t size)
{
    uint16_t pitchBytes;
    uint32_t height;

    if ((0U == size) || ((size % 512U) != 0U))
    {
        return kStatus_InvalidArgument;
    }

    /*
     * By default, PXP process block is 8x8. For better performance, choose
     * width and height dividable by block size.
     */
    if (size < 8U * 512U)
    {
        height     = 8U;
        pitchBytes = (uint16_t)(size / height);
    }
    else
    {
        pitchBytes = 512U;
        height     = size / pitchBytes;
    }

    if (height > PXP_MAX_HEIGHT)
    {
        return kStatus_InvalidArgument;
    }

    PXP_StartRectCopy(base, srcAddr, pitchBytes, destAddr, pitchBytes, pitchBytes / 4U, (uint16_t)height,
                      kPXP_AsPixelFormatARGB8888);

    return kStatus_Success;
}

/*!
 * brief Copy continous memory.
 *
 * param base PXP peripheral base address.
 * retval kStatus_Success Successfully started the copy process.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t PXP_MemCopy(PXP_Type *base, uint32_t srcAddr, uint32_t destAddr, uint32_t size)
{
    uint16_t pitchBytes;
    uint32_t height;
    uint32_t unalignedSize;

    if (0U == size)
    {
        return kStatus_InvalidArgument;
    }

    /* For 512 not aligned part, copy by CPU. */
    unalignedSize = size % 512U;

    if (0UL != unalignedSize)
    {
        (void)memcpy((uint8_t *)destAddr, (uint8_t *)srcAddr, unalignedSize);

        destAddr += unalignedSize;
        srcAddr += unalignedSize;
        size -= unalignedSize;
    }

    if (0UL != size)
    {
        /*
         * By default, PXP process block is 8x8. For better performance, choose
         * width and height dividable by block size.
         */
        if (size < 8U * 512U)
        {
            height     = 8U;
            pitchBytes = (uint16_t)(size / height);
        }
        else
        {
            pitchBytes = 512U;
            height     = size / pitchBytes;
        }

        if (height > PXP_MAX_HEIGHT)
        {
            return kStatus_InvalidArgument;
        }

        PXP_StartRectCopy(base, srcAddr, pitchBytes, destAddr, pitchBytes, pitchBytes / 4U, (uint16_t)height,
                          kPXP_AsPixelFormatARGB8888);

        while (0UL == ((uint32_t)kPXP_CompleteFlag & PXP_GetStatusFlags(base)))
        {
        }

        PXP_ClearStatusFlags(base, (uint32_t)kPXP_CompleteFlag);
    }

    return kStatus_Success;
}

#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3

/*!
 * brief Configures one channle of some block's fetch engine.
 *
 * Fetch engine is 64-bit input and 32-bit output per channel
 *
 * param base PXP peripheral base address.
 * param name which block the fetch engine belongs to.
 * param channel channel number.
 * param config pointer to the configuration structure.
 * retval kStatus_Success Successfully configured the engine.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t PXP_SetFetchEngineConfig(PXP_Type *base,
                                  pxp_fetch_engine_name_t name,
                                  uint8_t channel,
                                  const pxp_fetch_engine_config_t *config)
{
    assert(NULL != config);

    /* Check fetch address */
    if ((config->inputBaseAddr0 == 0U) ||
        ((config->inputBaseAddr1 == 0U) && (config->pixelFormat == kPXP_FetchFormatYUV422_2P)))
    {
        return kStatus_InvalidArgument;
    }
    /* Must enable expand when input pixel format is YUV422_2P, to combine Y and UV buffer to one output. */
    if ((config->expandEnable == false) && (config->pixelFormat == kPXP_FetchFormatYUV422_2P))
    {
        return kStatus_InvalidArgument;
    }
    /* Must enable block if flip or rotation is enabled. */
    if ((config->fetchFormat.enableblock == false) &&
        ((config->flipMode != kPXP_FlipDisable) || (config->rotateDegree != kPXP_Rotate0)))
    {
        return kStatus_InvalidArgument;
    }
    /* Block mode cannot work in 64-bit mode */
    if ((config->fetchFormat.enableblock == true) && (config->activeBits == kPXP_Active64Bits))
    {
        return kStatus_InvalidArgument;
    }

    uint32_t ctrlReg        = 0U;
    uint32_t ulcReg         = 0U;
    uint32_t lrcReg         = 0U;
    uint32_t fetchSizeReg   = 0U;
    uint32_t shiftCtrlReg   = 0U;
    uint32_t shiftOffsetReg = 0U;
    uint32_t shiftWidthReg  = 0U;
    uint8_t scanlineNum     = 0U;

    /* When block disabled, handshake scanline mode can only use 1 line mode where scanlineNum = 0. */
    if (config->fetchFormat.enableblock)
    {
        /*  */
        if (config->fetchFormat.blockSize16)
        {
            scanlineNum = 2;
        }
        else
        {
            scanlineNum = 1;
        }
    }

    ctrlReg = PXP_INPUT_FETCH_CTRL_CH0_HANDSHAKE_SCAN_LINE_NUM((uint32_t)scanlineNum) |
              PXP_INPUT_FETCH_CTRL_CH0_RD_NUM_BYTES(config->fetchFormat.burstLength) |
              PXP_INPUT_FETCH_CTRL_CH0_ROTATION_ANGLE((uint32_t)config->rotateDegree) |
              ((uint32_t)config->flipMode << PXP_INPUT_FETCH_CTRL_CH0_HFLIP_SHIFT) |
              PXP_INPUT_FETCH_CTRL_CH0_HIGH_BYTE((uint32_t)config->wordOrder) |
              ((uint32_t)config->interface << PXP_INPUT_FETCH_CTRL_CH0_HANDSHAKE_EN_SHIFT) |
              PXP_INPUT_FETCH_CTRL_CH0_BLOCK_EN((uint32_t)config->fetchFormat.enableblock) |
              PXP_INPUT_FETCH_CTRL_CH0_BLOCK_16((uint32_t)config->fetchFormat.blockSize16) |
              PXP_INPUT_FETCH_CTRL_CH0_CH_EN((uint32_t)config->channelEnable);
    ulcReg       = (((uint32_t)config->ulcY) << 16U) | (uint32_t)config->ulcX;
    lrcReg       = (((uint32_t)config->lrcY) << 16U) | (uint32_t)config->lrcX;
    fetchSizeReg = (((uint32_t)config->totalHeight) << 16U) | ((uint32_t)config->totalWidth);
    shiftCtrlReg = PXP_INPUT_FETCH_SHIFT_CTRL_CH0_INPUT_ACTIVE_BPP((uint32_t)config->activeBits) |
                   PXP_INPUT_FETCH_SHIFT_CTRL_CH0_EXPAND_FORMAT((uint32_t)config->pixelFormat) |
                   PXP_INPUT_FETCH_SHIFT_CTRL_CH0_EXPAND_EN((uint32_t)config->expandEnable) |
                   PXP_INPUT_FETCH_SHIFT_CTRL_CH0_SHIFT_BYPASS((uint32_t)config->shiftConfig.shiftBypass);
    if (!config->shiftConfig.shiftBypass)
    {
        shiftOffsetReg = (uint32_t)config->shiftConfig.component0.offset |
                         ((uint32_t)(config->shiftConfig.component1.offset) << 8U) |
                         ((uint32_t)(config->shiftConfig.component2.offset) << 16U) |
                         ((uint32_t)(config->shiftConfig.component3.offset) << 24U);
        shiftWidthReg = (uint32_t)config->shiftConfig.component0.width |
                        ((uint32_t)(config->shiftConfig.component1.width) << 4U) |
                        ((uint32_t)(config->shiftConfig.component2.width) << 8U) |
                        ((uint32_t)(config->shiftConfig.component3.width) << 12U);
    }

    if (name == kPXP_FetchInput)
    {
        switch (channel)
        {
            case 0:
                base->INPUT_FETCH_CTRL_CH0            = ctrlReg;
                base->INPUT_FETCH_ACTIVE_SIZE_ULC_CH0 = ulcReg;
                base->INPUT_FETCH_ACTIVE_SIZE_LRC_CH0 = lrcReg;
                base->INPUT_FETCH_SIZE_CH0            = fetchSizeReg;
                base->INPUT_FETCH_PITCH = (base->INPUT_FETCH_PITCH & PXP_INPUT_FETCH_PITCH_CH1_INPUT_PITCH_MASK) |
                                          (uint32_t)config->pitchBytes;
                base->INPUT_FETCH_SHIFT_CTRL_CH0 = shiftCtrlReg;
                base->INPUT_FETCH_ADDR_0_CH0     = config->inputBaseAddr0;
                base->INPUT_FETCH_ADDR_1_CH0     = config->inputBaseAddr1;
                if (!config->shiftConfig.shiftBypass)
                {
                    base->INPUT_FETCH_SHIFT_OFFSET_CH0 = shiftOffsetReg;
                    base->INPUT_FETCH_SHIFT_WIDTH_CH0  = shiftWidthReg;
                }
                break;

            case 1:
                base->INPUT_FETCH_CTRL_CH1            = ctrlReg;
                base->INPUT_FETCH_ACTIVE_SIZE_ULC_CH1 = ulcReg;
                base->INPUT_FETCH_ACTIVE_SIZE_LRC_CH1 = lrcReg;
                base->INPUT_FETCH_SIZE_CH1            = fetchSizeReg;
                base->INPUT_FETCH_PITCH = (base->INPUT_FETCH_PITCH & PXP_INPUT_FETCH_PITCH_CH0_INPUT_PITCH_MASK) |
                                          ((uint32_t)config->pitchBytes << 16U);
                base->INPUT_FETCH_SHIFT_CTRL_CH1 = shiftCtrlReg;
                base->INPUT_FETCH_ADDR_0_CH1     = config->inputBaseAddr0;
                base->INPUT_FETCH_ADDR_1_CH1     = config->inputBaseAddr1;
                if (!config->shiftConfig.shiftBypass)
                {
                    base->INPUT_FETCH_SHIFT_OFFSET_CH1 = shiftOffsetReg;
                    base->INPUT_FETCH_SHIFT_WIDTH_CH1  = shiftWidthReg;
                }
                break;

            default:
                /* Only 2 channels are supported per fetch engine. */
                assert(false);
                break;
        }
    }
    else
    {
        switch (channel)
        {
            case 0:
                base->DITHER_FETCH_CTRL_CH0            = ctrlReg;
                base->DITHER_FETCH_ACTIVE_SIZE_ULC_CH0 = ulcReg;
                base->DITHER_FETCH_ACTIVE_SIZE_LRC_CH0 = lrcReg;
                base->DITHER_FETCH_SIZE_CH0            = fetchSizeReg;
                base->DITHER_FETCH_PITCH = (base->INPUT_FETCH_PITCH & PXP_INPUT_FETCH_PITCH_CH1_INPUT_PITCH_MASK) |
                                           (uint32_t)config->pitchBytes;
                base->DITHER_FETCH_SHIFT_CTRL_CH0 = shiftCtrlReg;
                base->DITHER_FETCH_ADDR_0_CH0     = config->inputBaseAddr0;
                base->DITHER_FETCH_ADDR_1_CH0     = config->inputBaseAddr1;
                if (!config->shiftConfig.shiftBypass)
                {
                    base->DITHER_FETCH_SHIFT_OFFSET_CH0 = shiftOffsetReg;
                    base->DITHER_FETCH_SHIFT_WIDTH_CH0  = shiftWidthReg;
                }
                break;

            case 1:
                base->DITHER_FETCH_CTRL_CH1            = ctrlReg;
                base->DITHER_FETCH_ACTIVE_SIZE_ULC_CH1 = ulcReg;
                base->DITHER_FETCH_ACTIVE_SIZE_LRC_CH1 = lrcReg;
                base->DITHER_FETCH_SIZE_CH1            = fetchSizeReg;
                base->DITHER_FETCH_PITCH = (base->INPUT_FETCH_PITCH & PXP_INPUT_FETCH_PITCH_CH0_INPUT_PITCH_MASK) |
                                           ((uint32_t)config->pitchBytes << 16U);
                base->DITHER_FETCH_SHIFT_CTRL_CH1 = shiftCtrlReg;
                base->DITHER_FETCH_ADDR_0_CH1     = config->inputBaseAddr0;
                base->DITHER_FETCH_ADDR_1_CH1     = config->inputBaseAddr1;
                if (!config->shiftConfig.shiftBypass)
                {
                    base->DITHER_FETCH_SHIFT_OFFSET_CH1 = shiftOffsetReg;
                    base->DITHER_FETCH_SHIFT_WIDTH_CH1  = shiftWidthReg;
                }
                break;

            default:
                /* Only 2 channels are supported per fetch engine. */
                assert(false);
                break;
        }
    }
    return kStatus_Success;
}

/*!
 * brief Configures one channel of some block's store engine.
 *
 * Store engine is 32-bit input and 64-bit output per channel.
 * note: If there is only one channel used for data input, channel 0 must be used rather than channel 1.
 *
 * param base PXP peripheral base address.
 * param name the store engine belongs to which block.
 * param channel channel number.
 * param config pointer to the configuration structure.
 * retval kStatus_Success Successfully configured the engine.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t PXP_SetStoreEngineConfig(PXP_Type *base,
                                  pxp_store_engine_name_t name,
                                  uint8_t channel,
                                  const pxp_store_engine_config_t *config)
{
    assert(NULL != config);
    /* Can only choose one plane for YUV422_2p for one channel output */
    if ((uint32_t)config->yuvMode == 0x3U)
    {
        return kStatus_InvalidArgument;
    }

    /* Block mode cannot work in 64-bit mode or YUV422_2p mode */
    if ((config->storeFormat.enableblock == true) &&
        ((config->activeBits == kPXP_Active64Bits) || (config->yuvMode != kPXP_StoreYUVDisable)))
    {
        return kStatus_InvalidArgument;
    }

    /* When block mode is disabled the interface array size can only be 1. TODO. The availiable fetch engine now are
       only input&fetch that can only use handshake 1x1, no need to check */
    // if ((config->storeFormat.enableblock == false) && (config->arraySize != kPXP_StoreHandshake1x1))
    // {
    //     return kStatus_InvalidArgument;
    // }

    uint32_t ctrlReg               = 0U;
    uint32_t shiftCtrlReg          = 0U;
    uint32_t sizeReg               = 0U;
    uint32_t dataShiftMaskRegAddr  = 0U;
    uint32_t dataShiftWidthRegAddr = 0U;
    uint32_t flagShiftMaskRegAddr  = 0U;
    uint32_t flagShiftWidthRegAddr = 0U;

    ctrlReg = PXP_INPUT_STORE_CTRL_CH0_WR_NUM_BYTES((uint32_t)config->storeFormat.burstLength) |
              PXP_INPUT_STORE_CTRL_CH0_FILL_DATA_EN((uint32_t)config->useFixedData) |
              PXP_INPUT_STORE_CTRL_CH0_PACK_IN_SEL((uint32_t)config->packInSelect) |
              ((uint32_t)config->interface << PXP_INPUT_STORE_CTRL_CH0_HANDSHAKE_EN_SHIFT) |
              // PXP_INPUT_STORE_CTRL_CH0_ARRAY_LINE_NUM((uint32_t)config->arraySize) |
              PXP_INPUT_STORE_CTRL_CH0_ARRAY_LINE_NUM(0U) |
              PXP_INPUT_STORE_CTRL_CH0_BLOCK_16((uint32_t)config->storeFormat.enableblock) |
              PXP_INPUT_STORE_CTRL_CH0_BLOCK_EN((uint32_t)config->storeFormat.blockSize16) |
              PXP_INPUT_STORE_CTRL_CH0_CH_EN((uint32_t)config->channelEnable);
    shiftCtrlReg = PXP_INPUT_STORE_SHIFT_CTRL_CH0_SHIFT_BYPASS((uint32_t)config->shiftConfig.shiftBypass) |
                   ((uint32_t)config->yuvMode << PXP_INPUT_STORE_SHIFT_CTRL_CH0_OUT_YUV422_1P_EN_SHIFT) |
                   PXP_INPUT_STORE_SHIFT_CTRL_CH0_OUTPUT_ACTIVE_BPP((uint32_t)config->activeBits);
    sizeReg = (((uint32_t)config->totalHeight) << 16U) | ((uint32_t)config->totalWidth);

    if (name == kPXP_StoreInput)
    {
        switch (channel)
        {
            case 0:
                base->INPUT_STORE_CTRL_CH0 = ctrlReg;
                base->INPUT_STORE_SIZE_CH0 = sizeReg;
                base->INPUT_STORE_PITCH    = (base->INPUT_STORE_PITCH & PXP_INPUT_STORE_PITCH_CH0_OUT_PITCH_MASK) |
                                          (uint32_t)(config->pitchBytes);
                base->INPUT_STORE_SHIFT_CTRL_CH0 = shiftCtrlReg;
                base->INPUT_STORE_ADDR_0_CH0     = config->outputBaseAddr0;
                base->INPUT_STORE_ADDR_1_CH0     = config->outputBaseAddr1;
                base->INPUT_STORE_FILL_DATA_CH0  = config->fixedData;
                dataShiftMaskRegAddr             = (uint32_t) & (base->INPUT_STORE_D_MASK0_H_CH0);
                dataShiftWidthRegAddr            = (uint32_t) & (base->INPUT_STORE_D_SHIFT_L_CH0);
                flagShiftMaskRegAddr             = (uint32_t) & (base->INPUT_STORE_F_MASK_L_CH0);
                flagShiftWidthRegAddr            = (uint32_t) & (base->INPUT_STORE_F_SHIFT_L_CH0);
                break;

            case 1:
                base->INPUT_STORE_CTRL_CH1 = ctrlReg;
                base->INPUT_STORE_SIZE_CH1 = sizeReg;
                base->INPUT_STORE_PITCH    = (base->INPUT_STORE_PITCH & PXP_INPUT_STORE_PITCH_CH0_OUT_PITCH_MASK) |
                                          ((uint32_t)(config->pitchBytes) << 16U);
                base->INPUT_STORE_SHIFT_CTRL_CH1 = shiftCtrlReg;
                base->INPUT_STORE_ADDR_0_CH1     = config->outputBaseAddr0;
                base->INPUT_STORE_ADDR_1_CH1     = config->outputBaseAddr1;
                dataShiftMaskRegAddr             = (uint32_t) & (base->INPUT_STORE_D_MASK0_H_CH0);
                dataShiftWidthRegAddr            = (uint32_t) & (base->INPUT_STORE_D_SHIFT_L_CH0);
                flagShiftMaskRegAddr             = (uint32_t) & (base->INPUT_STORE_F_MASK_L_CH0);
                flagShiftWidthRegAddr            = (uint32_t) & (base->INPUT_STORE_F_SHIFT_L_CH0);
                break;

            default:
                /* Only 2 channels are supported per fetch engine. */
                assert(false);
                break;
        }
    }
    else
    {
        switch (channel)
        {
            case 0:
                base->DITHER_STORE_CTRL_CH0 = ctrlReg;
                base->DITHER_STORE_SIZE_CH0 = sizeReg;
                base->DITHER_STORE_PITCH    = (base->DITHER_STORE_PITCH & PXP_DITHER_STORE_PITCH_CH0_OUT_PITCH_MASK) |
                                           (uint32_t)(config->pitchBytes);
                base->DITHER_STORE_SHIFT_CTRL_CH0 = shiftCtrlReg;
                base->DITHER_STORE_ADDR_0_CH0     = config->outputBaseAddr0;
                base->DITHER_STORE_ADDR_1_CH0     = config->outputBaseAddr1;
                base->DITHER_STORE_FILL_DATA_CH0  = config->fixedData;
                dataShiftMaskRegAddr              = (uint32_t) & (base->DITHER_STORE_D_MASK0_H_CH0);
                dataShiftWidthRegAddr             = (uint32_t) & (base->DITHER_STORE_D_SHIFT_L_CH0);
                flagShiftMaskRegAddr              = (uint32_t) & (base->DITHER_STORE_F_MASK_L_CH0);
                flagShiftWidthRegAddr             = (uint32_t) & (base->DITHER_STORE_F_SHIFT_L_CH0);
                break;

            case 1:
                base->DITHER_STORE_CTRL_CH1 = ctrlReg;
                base->DITHER_STORE_SIZE_CH1 = sizeReg;
                base->DITHER_STORE_PITCH    = (base->DITHER_STORE_PITCH & PXP_DITHER_STORE_PITCH_CH0_OUT_PITCH_MASK) |
                                           ((uint32_t)(config->pitchBytes) << 16U);
                base->DITHER_STORE_SHIFT_CTRL_CH1 = shiftCtrlReg;
                base->DITHER_STORE_ADDR_0_CH1     = config->outputBaseAddr0;
                base->DITHER_STORE_ADDR_1_CH1     = config->outputBaseAddr1;
                dataShiftMaskRegAddr              = (uint32_t) & (base->DITHER_STORE_D_MASK0_H_CH0);
                dataShiftWidthRegAddr             = (uint32_t) & (base->DITHER_STORE_D_SHIFT_L_CH0);
                flagShiftMaskRegAddr              = (uint32_t) & (base->DITHER_STORE_F_MASK_L_CH0);
                flagShiftWidthRegAddr             = (uint32_t) & (base->DITHER_STORE_F_SHIFT_L_CH0);
                break;

            default:
                /* Only 2 channels are supported per fetch engine. */
                assert(false);
                break;
        }
    }

    /* Shift configuration */
    if (!config->shiftConfig.shiftBypass)
    {
        uint8_t i;
        uint32_t dataShiftMaskAddr  = (uint32_t) & (config->shiftConfig.pDataShiftMask);
        uint32_t dataShiftWidthAddr = (uint32_t) & (config->shiftConfig.pDataShiftWidth);
        uint32_t flagShiftMaskAddr  = (uint32_t) & (config->shiftConfig.pFlagShiftMask);
        uint32_t flagShiftWidthAddr = (uint32_t) & (config->shiftConfig.pFlagShiftWidth);

        /* Configure data shift mask */
        for (i = 0U; i < 8U; i++)
        {
            *(uint32_t *)dataShiftMaskRegAddr = (uint32_t)(*(uint64_t *)dataShiftMaskAddr >> 32U);
            dataShiftMaskRegAddr += 0x10U;
            *(uint32_t *)dataShiftMaskRegAddr = (uint32_t)(*(uint64_t *)dataShiftMaskAddr);
            dataShiftMaskRegAddr += 0x10U;
            dataShiftMaskAddr += 8U;
        }

        /* Configure data shift width, flag shift mask/width */
        for (i = 0U; i < 8U; i++)
        {
            *(uint8_t *)dataShiftWidthRegAddr = *(uint8_t *)dataShiftWidthAddr;
            *(uint8_t *)flagShiftMaskRegAddr  = *(uint8_t *)flagShiftMaskAddr;
            *(uint8_t *)flagShiftWidthRegAddr = *(uint8_t *)flagShiftWidthAddr;
            dataShiftWidthRegAddr++;
            flagShiftMaskRegAddr++;
            flagShiftWidthRegAddr++;
            dataShiftWidthAddr++;
            flagShiftMaskAddr++;
            flagShiftWidthAddr++;
            if (i == 3U)
            {
                dataShiftWidthRegAddr += 12U;
                flagShiftMaskRegAddr += 12U;
                flagShiftWidthRegAddr += 12U;
            }
        }
    }

    return kStatus_Success;
}

/*!
 * brief Configures the pre-dither CFA engine.
 *
 * param base PXP peripheral base address.
 * param config pointer to the configuration structure.
 * retval kStatus_Success Successfully configured the engine.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t PXP_SetCfaConfig(PXP_Type *base, const pxp_cfa_config_t *config)
{
    assert(NULL != config);
    /* The CFA array cannot be larger than 15x15. */
    if ((config->arrayWidth > 15U) || (config->arrayHeight > 15U))
    {
        return kStatus_InvalidArgument;
    }

    uint32_t cfaArrayRegAddr = (uint32_t) & (base->CFA_ARRAY0);
    uint32_t cfaValueAddr    = (uint32_t) & (config->cfaValue);
    uint8_t wordCount        = 0U; /* How many 32-bit word does the CFA array need. */

    base->CFA_CTRL = PXP_CFA_CTRL_CFA_ARRAY_HSIZE((uint32_t)config->arrayWidth) |
                     PXP_CFA_CTRL_CFA_ARRAY_VSIZE((uint32_t)config->arrayHeight) |
                     PXP_CFA_CTRL_CFA_IN_RGB444((uint32_t)config->pixelInFormat) |
                     PXP_CFA_CTRL_CFA_BYPASS((uint32_t)config->bypass);
    base->CFA_SIZE = ((uint32_t)(config->totalWidth) << 16U) | (uint32_t)(config->totalHeight);

    /* Configure the CFA array value. */
    wordCount = (config->arrayWidth * config->arrayHeight * 2U + 32U) / 32U;

    for (uint8_t i = 0U; i < wordCount; i++)
    {
        *(uint32_t *)cfaArrayRegAddr = *(uint32_t *)cfaValueAddr;
        cfaArrayRegAddr += 0x10U;
        cfaValueAddr += 4U;
    }

    return kStatus_Success;
}

/*!
 * brief Configures histogram engine.
 *
 * param base PXP peripheral base address.
 * param num instance number.
 * param config pointer to the configuration structure.
 * retval kStatus_Success Successfully configured the engine.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t PXP_SetHistogramConfig(PXP_Type *base, uint8_t num, const pxp_histogram_config_t *config)
{
    assert(NULL != config);
    /* The LUT value width can not be larger than 6. */
    if ((uint32_t)config->lutValueWidth > 6U)
    {
        return kStatus_InvalidArgument;
    }

    uint32_t ctrlReg = 0U;
    uint32_t maskReg = 0U;

    ctrlReg = PXP_HIST_A_CTRL_ENABLE((uint32_t)config->enable) |
              PXP_HIST_A_CTRL_PIXEL_OFFSET((uint32_t)config->lutValueOffset) |
              PXP_HIST_A_CTRL_PIXEL_WIDTH((uint32_t)config->lutValueWidth);
    maskReg = PXP_HIST_A_MASK_MASK_EN((uint32_t)config->enableMask) |
              PXP_HIST_A_MASK_MASK_MODE((uint32_t)config->condition) |
              PXP_HIST_A_MASK_MASK_OFFSET((uint32_t)config->maskOffset) |
              PXP_HIST_A_MASK_MASK_WIDTH((uint32_t)config->maskWidth) |
              PXP_HIST_A_MASK_MASK_VALUE0((uint32_t)config->maskValue0) |
              PXP_HIST_A_MASK_MASK_VALUE1((uint32_t)config->maskValue1);

    switch (num)
    {
        case 0:
            base->HIST_A_CTRL     = ctrlReg;
            base->HIST_A_MASK     = maskReg;
            base->HIST_A_BUF_SIZE = ((uint32_t)(config->totalHeight) << 16U) | (uint32_t)config->totalWidth;
            break;

        case 1:
            base->HIST_B_CTRL     = ctrlReg;
            base->HIST_B_MASK     = maskReg;
            base->HIST_B_BUF_SIZE = ((uint32_t)(config->totalHeight) << 16U) | (uint32_t)config->totalWidth;
            break;

        default:
            /* Only 2 histogram instances are supported. */
            assert(false);
            break;
    }

    /* Only configure the histogram params when user choose to, otherwise use the registers' reset value as default. */
    if (config->pParamValue != NULL)
    {
        uint32_t paramRegAddr   = (uint32_t) & (base->HIST2_PARAM);
        uint32_t paramValueAddr = (uint32_t) & (config->pParamValue);
        /* Configure the 2/4/8/16/32-level histogram params. */
        for (uint8_t i = 0; i < 62U; i++)
        {
            *(uint8_t *)paramRegAddr = *(uint8_t *)paramValueAddr;
            paramValueAddr += 1U;
            paramRegAddr++;
            if ((i % 4U) == 1U)
            {
                paramRegAddr += 12U;
                if (i == 1U)
                {
                    paramRegAddr += 2U;
                }
            }
        }
    }

    return kStatus_Success;
}

/*!
 * brief Gets the results of histogram mask operation.
 *
 * param base PXP peripheral base address.
 * param num instance number.
 * param result pointer to the result structure.
 */
void PXP_GetHistogramMaskResult(PXP_Type *base, uint8_t num, pxp_histogram_mask_result_t *result)
{
    assert(NULL != result);
    /* Initializes the result structure to zero. */
    (void)memset(result, 0, sizeof(*result));

    switch (num)
    {
        case 0:
            result->pixelCount = base->HIST_A_TOTAL_PIXEL;
            result->minX       = (uint16_t)base->HIST_A_ACTIVE_AREA_X;
            result->maxX       = (uint16_t)(base->HIST_A_ACTIVE_AREA_X >> 16U);
            result->minY       = (uint16_t)base->HIST_A_ACTIVE_AREA_Y;
            result->maxY       = (uint16_t)(base->HIST_A_ACTIVE_AREA_Y >> 16U);
            result->lutlist    = (uint64_t)base->HIST_A_RAW_STAT0 | ((uint64_t)base->HIST_A_RAW_STAT1 << 32U);
            break;

        case 1:
            result->pixelCount = base->HIST_B_TOTAL_PIXEL;
            result->minX       = (uint16_t)base->HIST_B_ACTIVE_AREA_X;
            result->maxX       = (uint16_t)(base->HIST_B_ACTIVE_AREA_X >> 16U);
            result->minY       = (uint16_t)base->HIST_B_ACTIVE_AREA_Y;
            result->maxY       = (uint16_t)(base->HIST_B_ACTIVE_AREA_Y >> 16U);
            result->lutlist    = (uint64_t)base->HIST_B_RAW_STAT0 | ((uint64_t)base->HIST_B_RAW_STAT1 << 32U);
            break;

        default:
            /* Only 2 histogram instances are supported. */
            assert(false);
            break;
    }
}

/*!
 * brief Initializes the WFE-A engine for waveform process.
 *
 * param base PXP peripheral base address.
 * param ditherHandshake true to enable handshake mode with upstream dither store engine.
 */
void PXP_WfeaInit(PXP_Type *base, bool ditherHandshake)
{
    /* FETCH engine configuration, user fetch buffer1 for Y4 data buffer and buffer2 for working buffer. */
    /* Enable buffer1&2 fetch. 2 bytes in each pixel for the buffer2.
       Other default configurations: fetch data from external axi bus, normal(not hanshake or by pass) mode, burst
       length 4, normal border pixels select(not sw reg mode), 1 line fetch, done IRQ disabled. */
    base->WFA_FETCH_CTRL = PXP_WFA_FETCH_CTRL_BF1_EN(1UL) | PXP_WFA_FETCH_CTRL_BF2_EN(1UL) |
                           PXP_WFA_FETCH_CTRL_BF2_BYTES_PP(1UL) |
                           PXP_WFA_FETCH_CTRL_BF1_HSK_MODE((uint32_t)ditherHandshake);
    /* Select pixel from bufer 2, set the right/left bit position on the original pixel as 0/3 */
    /* Other default configurations: x/y offset=0, positive offset. */
    base->WFA_ARRAY_PIXEL0_MASK = PXP_WFA_ARRAY_PIXEL0_MASK_BUF_SEL(1UL) | PXP_WFA_ARRAY_PIXEL0_MASK_L_OFS(3UL);
    /* Select pixel from bufer 2, set the right/left bit position on the original pixel as 4/7 */
    base->WFA_ARRAY_PIXEL1_MASK = PXP_WFA_ARRAY_PIXEL0_MASK_BUF_SEL(1UL) | PXP_WFA_ARRAY_PIXEL0_MASK_H_OFS(4UL) |
                                  PXP_WFA_ARRAY_PIXEL0_MASK_L_OFS(7UL);
    /* Select pixel from bufer 2, set the right/left bit position on the original pixel as 8/9 */
    base->WFA_ARRAY_PIXEL2_MASK = PXP_WFA_ARRAY_PIXEL0_MASK_BUF_SEL(1UL) | PXP_WFA_ARRAY_PIXEL0_MASK_H_OFS(8UL) |
                                  PXP_WFA_ARRAY_PIXEL0_MASK_L_OFS(9UL);
    /* Select pixel from bufer 2, set the right/left bit position on the original pixel as 10/15 */
    base->WFA_ARRAY_PIXEL3_MASK = PXP_WFA_ARRAY_PIXEL0_MASK_BUF_SEL(1UL) | PXP_WFA_ARRAY_PIXEL0_MASK_H_OFS(10UL) |
                                  PXP_WFA_ARRAY_PIXEL0_MASK_L_OFS(15UL);
    /* Select pixel from bufer 1, set the right/left bit position on the original pixel as 4/7 */
    base->WFA_ARRAY_PIXEL4_MASK = PXP_WFA_ARRAY_PIXEL0_MASK_H_OFS(4UL) | PXP_WFA_ARRAY_PIXEL0_MASK_L_OFS(7UL);
    /* Software define flag0=1, other flags 1~15 =0 */
    base->WFA_ARRAY_REG2 = 1UL;

    /* STORE engine configuration */
    /* Channel 0 y4, channel 1 wb */
    /* Enable channel 0, store data to memory, select low 32 bit shift out data to pack, enable combine 2 channel. */
    /* Other default configurations: Arbitration disable(if using 2 channels, will output 2 axi bus sets), 8 bytes in a
       burst, fill data mode disable, block mode disable. */
    base->WFE_A_STORE_CTRL_CH0 = PXP_WFE_A_STORE_CTRL_CH0_CH_EN(1UL) | PXP_WFE_A_STORE_CTRL_CH0_STORE_MEMORY_EN(1UL) |
                                 PXP_WFE_A_STORE_CTRL_CH0_PACK_IN_SEL(1UL) |
                                 PXP_WFE_A_STORE_CTRL_CH0_COMBINE_2CHANNEL(1UL);
    /* Enable channel 1, store data to memory, select low 32 bit shift out data to pack, 16 bytes in a write burst. */
    base->WFE_A_STORE_CTRL_CH1 = PXP_WFE_A_STORE_CTRL_CH1_CH_EN(1UL) | PXP_WFE_A_STORE_CTRL_CH1_STORE_MEMORY_EN(1UL) |
                                 PXP_WFE_A_STORE_CTRL_CH1_PACK_IN_SEL(1UL) | PXP_WFE_A_STORE_CTRL_CH1_WR_NUM_BYTES(1UL);
    /* 8 Bpp, disable YUV planes, disable shift bypass. */
    base->WFE_A_STORE_SHIFT_CTRL_CH0 = 0UL;
    /* 16 Bpp, disable YUV planes, disable shift bypass. */
    base->WFE_A_STORE_SHIFT_CTRL_CH1 = PXP_WFE_A_STORE_SHIFT_CTRL_CH1_OUTPUT_ACTIVE_BPP(1);
    base->WFE_A_STORE_FILL_DATA_CH0  = 0UL;
    /* 8 data masks, mask 0-7. Only use mask 0-4 */
    /* mask 0: 0xF << 32; mask 1: 0xF00 << 28; mask 2: 0x0 << 24; mask 3: 0x3F00'0000 << 18; mask 4: 0xF'0000'0000 >> 28
     */
    base->WFE_A_STORE_D_MASK0_H_CH0 = 0UL;
    base->WFE_A_STORE_D_MASK0_L_CH0 = PXP_WFE_A_STORE_D_MASK0_L_CH0_D_MASK0_L_CH0(0xfUL); /* fetch CP */
    base->WFE_A_STORE_D_MASK1_H_CH0 = 0UL;
    base->WFE_A_STORE_D_MASK1_L_CH0 = PXP_WFE_A_STORE_D_MASK1_L_CH0_D_MASK1_L_CH0(0xf00UL); /* fetch NP */
    base->WFE_A_STORE_D_MASK2_H_CH0 = 0UL;
    base->WFE_A_STORE_D_MASK2_L_CH0 = 0UL;
    base->WFE_A_STORE_D_MASK3_H_CH0 = 0UL;
    base->WFE_A_STORE_D_MASK3_L_CH0 = PXP_WFE_A_STORE_D_MASK3_L_CH0_D_MASK3_L_CH0(0x3f000000UL); /* fetch LUT */
    base->WFE_A_STORE_D_MASK4_H_CH0 = PXP_WFE_A_STORE_D_MASK4_H_CH0_D_MASK4_H_CH0(0xfUL);
    base->WFE_A_STORE_D_MASK4_L_CH0 = 0UL; /* fetch Y4 */
    base->WFE_A_STORE_D_SHIFT_L_CH0 =
        PXP_WFE_A_STORE_D_SHIFT_L_CH0_D_SHIFT_WIDTH0(32UL) | PXP_WFE_A_STORE_D_SHIFT_L_CH0_D_SHIFT_FLAG0(1UL) |
        PXP_WFE_A_STORE_D_SHIFT_L_CH0_D_SHIFT_WIDTH1(28UL) | PXP_WFE_A_STORE_D_SHIFT_L_CH0_D_SHIFT_FLAG1(1UL) |
        PXP_WFE_A_STORE_D_SHIFT_L_CH0_D_SHIFT_WIDTH2(24UL) | PXP_WFE_A_STORE_D_SHIFT_L_CH0_D_SHIFT_FLAG2(1UL) |
        PXP_WFE_A_STORE_D_SHIFT_L_CH0_D_SHIFT_WIDTH3(18UL) | PXP_WFE_A_STORE_D_SHIFT_L_CH0_D_SHIFT_FLAG3(1UL);
    base->WFE_A_STORE_D_SHIFT_H_CH0 = PXP_WFE_A_STORE_D_SHIFT_H_CH0_D_SHIFT_WIDTH4(28UL);

    /* 8 flag masks, mask 0-7. Only use mask 0-3 */
    /* mask 0: 0x1 << 1; mask 1: 0x2 >> 1; mask 2: 0x4 << 38; mask 3: 0x8 << 38 */
    /* Switch flag bit 0&1, bit 2&3 << 38 */
    base->WFE_A_STORE_F_MASK_H_CH0 = 0UL;
    base->WFE_A_STORE_F_MASK_L_CH0 =
        PXP_WFE_A_STORE_F_MASK_L_CH0_F_MASK0(0x1UL) | PXP_WFE_A_STORE_F_MASK_L_CH0_F_MASK1(0x2UL) |
        PXP_WFE_A_STORE_F_MASK_L_CH0_F_MASK2(0x4UL) | PXP_WFE_A_STORE_F_MASK_L_CH0_F_MASK3(0x8UL);
    base->WFE_A_STORE_F_SHIFT_H_CH0 = 0UL;
    base->WFE_A_STORE_F_SHIFT_L_CH0 =
        PXP_WFE_A_STORE_F_SHIFT_L_CH0_F_SHIFT_WIDTH0(1UL) | PXP_WFE_A_STORE_F_SHIFT_L_CH0_F_SHIFT_FLAG0(1UL) |
        PXP_WFE_A_STORE_F_SHIFT_L_CH0_F_SHIFT_WIDTH1(1UL) | PXP_WFE_A_STORE_F_SHIFT_L_CH0_F_SHIFT_FLAG1(0UL) |
        PXP_WFE_A_STORE_F_SHIFT_L_CH0_F_SHIFT_WIDTH2(32UL + 6UL) | PXP_WFE_A_STORE_F_SHIFT_L_CH0_F_SHIFT_FLAG2(1UL) |
        PXP_WFE_A_STORE_F_SHIFT_L_CH0_F_SHIFT_WIDTH3(32UL + 6UL) | PXP_WFE_A_STORE_F_SHIFT_L_CH0_F_SHIFT_FLAG3(1UL);

    /* Enable and bypass the ALU process. */
    base->ALU_A_INST_ENTRY = 0UL;
    base->ALU_A_PARAM      = 0UL;
    base->ALU_A_CONFIG     = 0UL;
    base->ALU_A_LUT_CONFIG = 0UL;
    base->ALU_A_LUT_DATA0  = 0UL;
    base->ALU_A_LUT_DATA1  = 0UL;
    base->ALU_A_CTRL       = PXP_ALU_A_CTRL_BYPASS(1UL) | PXP_ALU_A_CTRL_ENABLE(1UL);

    /* WFE A */
    base->WFE_A_STAGE1_MUX0  = 0x3F3F0303UL;
    base->WFE_A_STAGE1_MUX1  = 0x0C00000CUL;
    base->WFE_A_STAGE1_MUX2  = 0x01040000UL;
    base->WFE_A_STAGE1_MUX3  = 0x0A0A0904UL;
    base->WFE_A_STAGE1_MUX4  = 0x00000B0BUL;
    base->WFE_A_STAGE2_MUX0  = 0x1800280EUL;
    base->WFE_A_STAGE2_MUX1  = 0x00280E01UL;
    base->WFE_A_STAGE2_MUX2  = 0x280E0118UL;
    base->WFE_A_STAGE2_MUX3  = 0x00011800UL;
    base->WFE_A_STAGE2_MUX4  = 0UL;
    base->WFE_A_STAGE2_MUX5  = 0x1800280EUL;
    base->WFE_A_STAGE2_MUX6  = 0x00280E01UL;
    base->WFE_A_STAGE2_MUX7  = 0x1A0E0118UL;
    base->WFE_A_STAGE2_MUX8  = 0x1B012911UL;
    base->WFE_A_STAGE2_MUX9  = 0x00002911UL;
    base->WFE_A_STAGE2_MUX10 = 0UL;
    base->WFE_A_STAGE2_MUX11 = 0UL;
    base->WFE_A_STAGE2_MUX12 = 0UL;
    base->WFE_A_STAGE3_MUX0  = 0x07060504UL;
    base->WFE_A_STAGE3_MUX1  = 0x3F3F3F08UL;
    base->WFE_A_STAGE3_MUX2  = 0x03020100UL;
    base->WFE_A_STAGE3_MUX3  = 0x3F3F3F3FUL;

    /* WFE_A_STG1_8X1_OUT0_0/1 is used to store LUT occupation status */
    /* Set LUT64-255 to occupied since we only have 64 LUTs in EPDC */
    base->WFE_A_STG1_8X1_OUT0_2 = 0xFFFFFFFFUL;
    base->WFE_A_STG1_8X1_OUT0_3 = 0xFFFFFFFFUL;
    base->WFE_A_STG1_8X1_OUT0_4 = 0xFFFFFFFFUL;
    base->WFE_A_STG1_8X1_OUT0_5 = 0xFFFFFFFFUL;
    base->WFE_A_STG1_8X1_OUT0_6 = 0xFFFFFFFFUL;
    base->WFE_A_STG1_8X1_OUT0_7 = 0xFFFFFFFFUL;
    /* OUT1.2.3 LUT0-255 */
    base->WFE_A_STG1_8X1_OUT1_0 = 0UL;
    base->WFE_A_STG1_8X1_OUT1_1 = 0UL;
    base->WFE_A_STG1_8X1_OUT1_2 = 0UL;
    base->WFE_A_STG1_8X1_OUT1_3 = 0UL;
    base->WFE_A_STG1_8X1_OUT1_4 = 0UL;
    base->WFE_A_STG1_8X1_OUT1_5 = 0UL;
    base->WFE_A_STG1_8X1_OUT1_6 = 0UL;
    base->WFE_A_STG1_8X1_OUT1_7 = 0UL;
    base->WFE_A_STG1_8X1_OUT2_0 = 0UL;
    base->WFE_A_STG1_8X1_OUT2_1 = 0UL;
    base->WFE_A_STG1_8X1_OUT2_2 = 0UL;
    base->WFE_A_STG1_8X1_OUT2_3 = 0UL;
    base->WFE_A_STG1_8X1_OUT2_4 = 0UL;
    base->WFE_A_STG1_8X1_OUT2_5 = 0UL;
    base->WFE_A_STG1_8X1_OUT2_6 = 0UL;
    base->WFE_A_STG1_8X1_OUT2_7 = 0UL;
    base->WFE_A_STG1_8X1_OUT3_0 = 0UL;
    base->WFE_A_STG1_8X1_OUT3_1 = 0UL;
    base->WFE_A_STG1_8X1_OUT3_2 = 0UL;
    base->WFE_A_STG1_8X1_OUT3_3 = 0UL;
    base->WFE_A_STG1_8X1_OUT3_4 = 0UL;
    base->WFE_A_STG1_8X1_OUT3_5 = 0UL;
    base->WFE_A_STG1_8X1_OUT3_6 = 0UL;
    base->WFE_A_STG1_8X1_OUT3_7 = 0UL;
    /* LUTOUT0-31 for OUT0-3.
       The 5x6 LUT output value for input value n. This output value determines which input to select (flag, data). */
    base->WFE_A_STG2_5X6_OUT0_0 = 0x04040404UL;
    base->WFE_A_STG2_5X6_OUT0_1 = 0x04040404UL;
    base->WFE_A_STG2_5X6_OUT0_2 = 0x04050505UL;
    base->WFE_A_STG2_5X6_OUT0_3 = 0x04040404UL;
    base->WFE_A_STG2_5X6_OUT0_4 = 0x04040404UL;
    base->WFE_A_STG2_5X6_OUT0_5 = 0x04040404UL;
    base->WFE_A_STG2_5X6_OUT0_6 = 0x04040404UL;
    base->WFE_A_STG2_5X6_OUT0_7 = 0x04040404UL;
    base->WFE_A_STG2_5X6_OUT1_0 = 0x05050505UL;
    base->WFE_A_STG2_5X6_OUT1_1 = 0x05050505UL;
    base->WFE_A_STG2_5X6_OUT1_2 = 0x05080808UL;
    base->WFE_A_STG2_5X6_OUT1_3 = 0x05050505UL;
    base->WFE_A_STG2_5X6_OUT1_4 = 0x05050505UL;
    base->WFE_A_STG2_5X6_OUT1_5 = 0x05050505UL;
    base->WFE_A_STG2_5X6_OUT1_6 = 0x05050505UL;
    base->WFE_A_STG2_5X6_OUT1_7 = 0x05050505UL;
    base->WFE_A_STG2_5X6_OUT2_0 = 0x07070707UL;
    base->WFE_A_STG2_5X6_OUT2_1 = 0x07070707UL;
    base->WFE_A_STG2_5X6_OUT2_2 = 0x070C0C0CUL;
    base->WFE_A_STG2_5X6_OUT2_3 = 0x07070707UL;
    base->WFE_A_STG2_5X6_OUT2_4 = 0X0F0F0F0FUL;
    base->WFE_A_STG2_5X6_OUT2_5 = 0X0F0F0F0FUL;
    base->WFE_A_STG2_5X6_OUT2_6 = 0X0F0F0F0FUL;
    base->WFE_A_STG2_5X6_OUT2_7 = 0X0F0F0F0FUL;
    base->WFE_A_STG2_5X6_OUT3_0 = 0UL;
    base->WFE_A_STG2_5X6_OUT3_1 = 0UL;
    base->WFE_A_STG2_5X6_OUT3_2 = 0UL;
    base->WFE_A_STG2_5X6_OUT3_3 = 0UL;
    base->WFE_A_STG2_5X6_OUT3_4 = 0UL;
    base->WFE_A_STG2_5X6_OUT3_5 = 0UL;
    base->WFE_A_STG2_5X6_OUT3_6 = 0UL;
    base->WFE_A_STG2_5X6_OUT3_7 = 0UL;
    /* MASK0-3, 5 bits each mask.
       Each set mask bit enables one of the corresponding flag input bits. There is one mask per 5x6 LUT. */
    base->WFE_A_STAGE2_5X6_MASKS_0 = 0x001F1F1FUL;
    /* MUXADDR 0-3, 6 bits each.
       Each Address specifies the MUX position in the MUX array. There is one MUXADDR per 5x6 LUT.*/
    base->WFE_A_STAGE2_5X6_ADDR_0 = 0x3f030100UL;
    /* Flag of LUTOUT0-31 for OUT0-3.
       The 5x1 LUT output value for input value n. This output value results in a flag that is added to the flag array.
     */
    base->WFE_A_STG2_5X1_OUT0 = 0x00000700UL;
    base->WFE_A_STG2_5X1_OUT1 = 0x00007000UL;
    base->WFE_A_STG2_5X1_OUT2 = 0x0000A000UL;
    base->WFE_A_STG2_5X1_OUT3 = 0x000000C0UL;
    /* MASK0-3, 5 bits each mask.
       Each set mask bit enables one of the corresponding flag input bits. There is one mask per 5x1 LUT. */
    base->WFE_A_STG2_5X1_MASKS = 0x071F1F1FUL;
}

/*!
 * brief Configure the WFE-A engine
 *
 * param base PXP peripheral base address.
 * param config pointer to the configuration structure.
 */
void PXP_SetWfeaConfig(PXP_Type *base, const pxp_wfea_engine_config_t *config)
{
    /* Fetch */
    base->WFA_FETCH_BUF1_ADDR  = config->y4Addr;
    base->WFA_FETCH_BUF1_PITCH = config->updatePitch;
    base->WFA_FETCH_BUF1_SIZE  = PXP_WFA_FETCH_BUF1_SIZE_BUF_HEIGHT((uint32_t)config->updateHeight - 1UL) |
                                PXP_WFA_FETCH_BUF1_SIZE_BUF_WIDTH((uint32_t)config->updateWidth - 1UL);
    base->WFA_FETCH_BUF1_CORD  = 0UL;
    base->WFA_FETCH_BUF2_ADDR  = config->wbAddr;
    base->WFA_FETCH_BUF2_PITCH = (uint32_t)config->resX * 2U; /* 2 bytes per pixel */
    base->WFA_FETCH_BUF2_SIZE  = PXP_WFA_FETCH_BUF1_SIZE_BUF_HEIGHT((uint32_t)config->updateHeight - 1UL) |
                                PXP_WFA_FETCH_BUF1_SIZE_BUF_WIDTH((uint32_t)config->updateWidth - 1UL);
    base->WFA_FETCH_BUF2_CORD =
        PXP_WFA_FETCH_BUF2_CORD_YCORD((uint32_t)config->ulcY) | PXP_WFA_FETCH_BUF2_CORD_XCORD((uint32_t)config->ulcX);

    /* Store */
    base->WFE_A_STORE_SIZE_CH0 = PXP_WFE_A_STORE_SIZE_CH0_OUT_WIDTH((uint32_t)config->updateWidth - 1UL) |
                                 PXP_WFE_A_STORE_SIZE_CH0_OUT_HEIGHT((uint32_t)config->updateHeight - 1UL);
    base->WFE_A_STORE_SIZE_CH1 = PXP_WFE_A_STORE_SIZE_CH0_OUT_WIDTH((uint32_t)config->updateWidth - 1UL) |
                                 PXP_WFE_A_STORE_SIZE_CH0_OUT_HEIGHT((uint32_t)config->updateHeight - 1UL);
    /* Channel 1: 2 byte per pixel. */
    base->WFE_A_STORE_PITCH = PXP_WFE_A_STORE_PITCH_CH0_OUT_PITCH((uint32_t)config->resX) |
                              PXP_WFE_A_STORE_PITCH_CH1_OUT_PITCH((uint32_t)config->resX * 2U);
    base->WFE_A_STORE_ADDR_0_CH0 = PXP_WFE_A_STORE_ADDR_0_CH0_OUT_BASE_ADDR0(config->y4cAddr);
    base->WFE_A_STORE_ADDR_1_CH0 = 0U;
    /* Channel 1: 2 bytes per pixel. */
    base->WFE_A_STORE_ADDR_0_CH1 = PXP_WFE_A_STORE_ADDR_0_CH1_OUT_BASE_ADDR0(
        (uint32_t)config->wbAddr + ((uint32_t)config->ulcX + (uint32_t)config->ulcY * (uint32_t)config->resX) * 2UL);
    base->WFE_A_STORE_ADDR_1_CH1 = 0U;

    /* ALU */
    base->ALU_A_BUF_SIZE = PXP_ALU_A_BUF_SIZE_BUF_WIDTH((uint32_t)config->updateWidth) |
                           PXP_ALU_A_BUF_SIZE_BUF_HEIGHT((uint32_t)config->updateHeight);

    /* WFE */
    /* Height and width of the updete region */
    base->WFE_A_DIMENSIONS =
        PXP_WFE_A_DIMENSIONS_WIDTH(config->updateWidth) | PXP_WFE_A_DIMENSIONS_HEIGHT(config->updateHeight);
    /* The distance from the frame origin to the update region origin in the X/Y direction. */
    base->WFE_A_OFFSET = PXP_WFE_A_OFFSET_X_OFFSET(config->ulcX) | PXP_WFE_A_OFFSET_Y_OFFSET(config->ulcY);
    /* val3,val2=0, val1=F, val0=lutNum */
    base->WFE_A_SW_DATA_REGS = (config->lutNum & 0x000000FFUL) | 0x00000F00UL;
    /* val3,val2=0, val1=0(disable reagl/-d), val0=partial(1)full(0) */
    base->WFE_A_SW_FLAG_REGS = ((uint32_t)(!config->fullUpdateEnable) | (0U << 1U));
    /* Enable and reset WFE-A state. Disable register of ALU inside waveform as default. */
    base->WFE_A_CTRL = PXP_WFE_A_CTRL_ENABLE(1UL) | PXP_WFE_A_CTRL_SW_RESET(1UL);

    if (config->alphaEnable)
    {
        base->WFA_ARRAY_FLAG0_MASK = 0U;
    }
    else
    {
        base->WFA_ARRAY_FLAG0_MASK = PXP_WFA_ARRAY_FLAG0_MASK_BUF_SEL(2UL);
    }

    /* disable CH1 when only doing detection */
    if (config->detectionOnly)
    {
        base->WFE_A_STORE_CTRL_CH1 &= ~PXP_WFE_A_STORE_CTRL_CH1_CH_EN(1UL);
    }
    else
    {
        base->WFE_A_STORE_CTRL_CH1 |= PXP_WFE_A_STORE_CTRL_CH1_CH_EN(1UL);
    }
    /* Enable engine */
    base->CTRL_SET = PXP_CTRL_ENABLE_WFE_A(1UL);
}
#endif /* FSL_FEATURE_PXP_V3 */

#if PXP_USE_PATH
/*!
 * brief Sets the path for one of the MUX
 *
 * param base PXP peripheral base address.
 * param path the path configuration for one of the mux.
 */
void PXP_SetPath(PXP_Type *base, pxp_path_t path)
{
    volatile uint32_t *pathReg;
    uint32_t mux = PXP_GET_MUX_FROM_PATH((uint32_t)path);
    uint32_t sel = PXP_GET_SEL_FROM_PATH((uint32_t)path);

    if (mux > 15U)
    {
        pathReg = &(base->DATA_PATH_CTRL1);
        mux -= 15U;
    }
    else
    {
        pathReg = &(base->DATA_PATH_CTRL0);
    }

    /* Convert mux to the register shift. */
    mux *= 2U;
    *pathReg = (*pathReg & ~(3UL << mux)) | (sel << mux);
}
#endif /* PXP_USE_PATH */
