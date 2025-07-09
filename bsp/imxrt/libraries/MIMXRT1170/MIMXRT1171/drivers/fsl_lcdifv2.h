/*
 * Copyright 2019-2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_LCDIFV2_H_
#define FSL_LCDIFV2_H_

#include "fsl_common.h"

#if (defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && (0 != FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET))
#include "fsl_memory.h"
#endif

/*!
 * @addtogroup lcdifv2
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief LCDIF v2 driver version */
#define FSL_LCDIFV2_DRIVER_VERSION (MAKE_VERSION(2, 3, 3))
/*! @} */

#if defined(FSL_FEATURE_LCDIFV2_LAYER_COUNT) && (!defined(LCDIFV2_LAYER_COUNT))
#define LCDIFV2_LAYER_COUNT FSL_FEATURE_LCDIFV2_LAYER_COUNT
#endif

#if defined(FSL_FEATURE_LCDIFV2_LAYER_CSC_COUNT) && (!defined(LCDIFV2_LAYER_CSC_COUNT))
#define LCDIFV2_LAYER_CSC_COUNT FSL_FEATURE_LCDIFV2_LAYER_CSC_COUNT
#endif

#if (defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && (0 != FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET))
#define LCDIFV2_ADDR_CPU_2_IP(addr) (MEMORY_ConvertMemoryMapAddress((uint32_t)(addr), kMEMORY_Local2DMA))
#else
#define LCDIFV2_ADDR_CPU_2_IP(addr) (addr)
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */

/*! @brief LCDIF v2 FIFO empty interrupt. */
#define LCDIFV2_MAKE_FIFO_EMPTY_INTERRUPT(layer) (1UL << ((uint32_t)(layer) + 24U))
/*! @brief LCDIF v2 DMA done interrupt. */
#define LCDIFV2_MAKE_DMA_DONE_INTERRUPT(layer) (1UL << ((uint32_t)(layer) + 16U))
/*! @brief LCDIF v2 DMA error interrupt. */
#define LCDIFV2_MAKE_DMA_ERROR_INTERRUPT(layer) (1UL << ((uint32_t)(layer) + 8U))

/* LUT memory entery number. */
#define LCDIFV2_LUT_ENTRY_NUM 256U

/*!
 * @brief LCDIF v2 signal polarity flags
 */
enum _lcdifv2_polarity_flags
{
    kLCDIFV2_VsyncActiveHigh          = 0U, /*!< VSYNC active high. */
    kLCDIFV2_HsyncActiveHigh          = 0U, /*!< HSYNC active high. */
    kLCDIFV2_DataEnableActiveHigh     = 0U, /*!< Data enable line active high. */
    kLCDIFV2_DriveDataOnRisingClkEdge = 0U, /*!< Output data on rising clock edge, capture data
                                                 on falling clock edge. */
    kLCDIFV2_DataActiveHigh = 0U,           /*!< Data active high. */

    kLCDIFV2_VsyncActiveLow            = LCDIFV2_CTRL_INV_VS_MASK,   /*!< VSYNC active low. */
    kLCDIFV2_HsyncActiveLow            = LCDIFV2_CTRL_INV_HS_MASK,   /*!< HSYNC active low. */
    kLCDIFV2_DataEnableActiveLow       = LCDIFV2_CTRL_INV_DE_MASK,   /*!< Data enable line active low. */
    kLCDIFV2_DriveDataOnFallingClkEdge = LCDIFV2_CTRL_INV_PXCK_MASK, /*!< Output data on falling clock edge, capture
                                                                        data on rising clock edge. */
    kLCDIFV2_DataActiveLow = LCDIFV2_CTRL_NEG_MASK,                  /*!< Data active high. */
};

/*!
 * @brief The LCDIF v2 interrupts.
 */
enum _lcdifv2_interrupt
{
    kLCDIFV2_Layer0FifoEmptyInterrupt  = LCDIFV2_MAKE_FIFO_EMPTY_INTERRUPT(0), /*!< Layer 0 FIFO empty. */
    kLCDIFV2_Layer1FifoEmptyInterrupt  = LCDIFV2_MAKE_FIFO_EMPTY_INTERRUPT(1), /*!< Layer 1 FIFO empty. */
    kLCDIFV2_Layer2FifoEmptyInterrupt  = LCDIFV2_MAKE_FIFO_EMPTY_INTERRUPT(2), /*!< Layer 2 FIFO empty. */
    kLCDIFV2_Layer3FifoEmptyInterrupt  = LCDIFV2_MAKE_FIFO_EMPTY_INTERRUPT(3), /*!< Layer 3 FIFO empty. */
    kLCDIFV2_Layer4FifoEmptyInterrupt  = LCDIFV2_MAKE_FIFO_EMPTY_INTERRUPT(4), /*!< Layer 4 FIFO empty. */
    kLCDIFV2_Layer5FifoEmptyInterrupt  = LCDIFV2_MAKE_FIFO_EMPTY_INTERRUPT(5), /*!< Layer 5 FIFO empty. */
    kLCDIFV2_Layer6FifoEmptyInterrupt  = LCDIFV2_MAKE_FIFO_EMPTY_INTERRUPT(6), /*!< Layer 6 FIFO empty. */
    kLCDIFV2_Layer7FifoEmptyInterrupt  = LCDIFV2_MAKE_FIFO_EMPTY_INTERRUPT(7), /*!< Layer 7 FIFO empty. */
    kLCDIFV2_Layer0DmaDoneInterrupt    = LCDIFV2_MAKE_DMA_DONE_INTERRUPT(0),   /*!< Layer 0 DMA done. */
    kLCDIFV2_Layer1DmaDoneInterrupt    = LCDIFV2_MAKE_DMA_DONE_INTERRUPT(1),   /*!< Layer 1 DMA done. */
    kLCDIFV2_Layer2DmaDoneInterrupt    = LCDIFV2_MAKE_DMA_DONE_INTERRUPT(2),   /*!< Layer 2 DMA done. */
    kLCDIFV2_Layer3DmaDoneInterrupt    = LCDIFV2_MAKE_DMA_DONE_INTERRUPT(3),   /*!< Layer 3 DMA done. */
    kLCDIFV2_Layer4DmaDoneInterrupt    = LCDIFV2_MAKE_DMA_DONE_INTERRUPT(4),   /*!< Layer 4 DMA done. */
    kLCDIFV2_Layer5DmaDoneInterrupt    = LCDIFV2_MAKE_DMA_DONE_INTERRUPT(5),   /*!< Layer 5 DMA done. */
    kLCDIFV2_Layer6DmaDoneInterrupt    = LCDIFV2_MAKE_DMA_DONE_INTERRUPT(6),   /*!< Layer 6 DMA done. */
    kLCDIFV2_Layer7DmaDoneInterrupt    = LCDIFV2_MAKE_DMA_DONE_INTERRUPT(7),   /*!< Layer 7 DMA done. */
    kLCDIFV2_Layer0DmaErrorInterrupt   = LCDIFV2_MAKE_DMA_ERROR_INTERRUPT(0),  /*!< Layer 0 DMA error. */
    kLCDIFV2_Layer1DmaErrorInterrupt   = LCDIFV2_MAKE_DMA_ERROR_INTERRUPT(1),  /*!< Layer 1 DMA error. */
    kLCDIFV2_Layer2DmaErrorInterrupt   = LCDIFV2_MAKE_DMA_ERROR_INTERRUPT(2),  /*!< Layer 2 DMA error. */
    kLCDIFV2_Layer3DmaErrorInterrupt   = LCDIFV2_MAKE_DMA_ERROR_INTERRUPT(3),  /*!< Layer 3 DMA error. */
    kLCDIFV2_Layer4DmaErrorInterrupt   = LCDIFV2_MAKE_DMA_ERROR_INTERRUPT(4),  /*!< Layer 4 DMA error. */
    kLCDIFV2_Layer5DmaErrorInterrupt   = LCDIFV2_MAKE_DMA_ERROR_INTERRUPT(5),  /*!< Layer 5 DMA error. */
    kLCDIFV2_Layer6DmaErrorInterrupt   = LCDIFV2_MAKE_DMA_ERROR_INTERRUPT(6),  /*!< Layer 6 DMA error. */
    kLCDIFV2_Layer7DmaErrorInterrupt   = LCDIFV2_MAKE_DMA_ERROR_INTERRUPT(7),  /*!< Layer 7 DMA error. */
    kLCDIFV2_VerticalBlankingInterrupt = (1U << 2U), /*!< Start of vertical blanking period. */
    kLCDIFV2_OutputUnderrunInterrupt   = (1U << 1U), /*!< Output buffer underrun. */
    kLCDIFV2_VsyncEdgeInterrupt        = (1U << 0U), /*!< Interrupt at VSYNC edge. */
};

/*! @brief The LCDIF v2 output line order. */
typedef enum _lcdifv2_line_order
{
    kLCDIFV2_LineOrderRGB = 0, /*!< RGB */
    kLCDIFV2_LineOrderRBG,     /*!< RBG */
    kLCDIFV2_LineOrderGBR,     /*!< GBR */
    kLCDIFV2_LineOrderGRB,     /*!< GRB */
    kLCDIFV2_LineOrderBRG,     /*!< BRG */
    kLCDIFV2_LineOrderBGR,     /*!< BGR */
} lcdifv2_line_order_t;

/*!
 * @brief LCDIF v2 display configure structure.
 */
typedef struct _lcdifv2_display_config
{
    uint16_t panelWidth;    /*!< Display panel width, pixels per line. */
    uint16_t panelHeight;   /*!< Display panel height, how many lines per panel. */
    uint8_t hsw;            /*!< HSYNC pulse width. */
    uint8_t hfp;            /*!< Horizontal front porch. */
    uint8_t hbp;            /*!< Horizontal back porch. */
    uint8_t vsw;            /*!< VSYNC pulse width. */
    uint8_t vfp;            /*!< Vrtical front porch. */
    uint8_t vbp;            /*!< Vertical back porch. */
    uint32_t polarityFlags; /*!< OR'ed value of @ref _lcdifv2_polarity_flags, used to contol the signal polarity. */
    lcdifv2_line_order_t lineOrder; /*!< Line order. */
} lcdifv2_display_config_t;

/*! @brief LCDIF v2 color space conversion mode. */
typedef enum _lcdifv2_csc_mode
{
    kLCDIFV2_CscDisable = 0U, /*!< Disable the CSC. */
    kLCDIFV2_CscYUV2RGB,      /*!< YUV to RGB. */
    kLCDIFV2_CscYCbCr2RGB,    /*!< YCbCr to RGB. */
} lcdifv2_csc_mode_t;

/*! @brief LCDIF v2 pixel format. */
typedef enum _lcdifv2_pixel_format
{
    kLCDIFV2_PixelFormatIndex1BPP = LCDIFV2_CTRLDESCL5_BPP(0U), /*!< LUT index 1 bit. */
    kLCDIFV2_PixelFormatIndex2BPP = LCDIFV2_CTRLDESCL5_BPP(1U), /*!< LUT index 2 bit. */
    kLCDIFV2_PixelFormatIndex4BPP = LCDIFV2_CTRLDESCL5_BPP(2U), /*!< LUT index 4 bit. */
    kLCDIFV2_PixelFormatIndex8BPP = LCDIFV2_CTRLDESCL5_BPP(3U), /*!< LUT index 8 bit. */
    kLCDIFV2_PixelFormatRGB565    = LCDIFV2_CTRLDESCL5_BPP(4U), /*!< RGB565, two pixels use 32 bits. */
    kLCDIFV2_PixelFormatARGB1555  = LCDIFV2_CTRLDESCL5_BPP(5U), /*!< ARGB1555, two pixels use 32 bits. */
    kLCDIFV2_PixelFormatARGB4444  = LCDIFV2_CTRLDESCL5_BPP(6U), /*!< ARGB4444, two pixels use 32 bits. */
    kLCDIFV2_PixelFormatUYVY      = LCDIFV2_CTRLDESCL5_BPP(7U) |
                               LCDIFV2_CTRLDESCL5_YUV_FORMAT(0U), /*!< UYVY, only layer 0 and layer 1 support this. */
    kLCDIFV2_PixelFormatVYUY = LCDIFV2_CTRLDESCL5_BPP(7U) |
                               LCDIFV2_CTRLDESCL5_YUV_FORMAT(1U), /*!< VYUY, only layer 0 and layer 1 support this. */
    kLCDIFV2_PixelFormatYUYV = LCDIFV2_CTRLDESCL5_BPP(7U) |
                               LCDIFV2_CTRLDESCL5_YUV_FORMAT(2U), /*!< YUYV, only layer 0 and layer 1 support this. */
    kLCDIFV2_PixelFormatYVYU = LCDIFV2_CTRLDESCL5_BPP(7U) |
                               LCDIFV2_CTRLDESCL5_YUV_FORMAT(3U), /*!< YVYU, only layer 0 and layer 1 support this. */
    kLCDIFV2_PixelFormatRGB888   = LCDIFV2_CTRLDESCL5_BPP(8U),    /*!< RGB888 packed, one pixel uses 24 bits. */
    kLCDIFV2_PixelFormatARGB8888 = LCDIFV2_CTRLDESCL5_BPP(9U),    /*!< ARGB8888 unpacked, one pixel uses 32 bits. */
    kLCDIFV2_PixelFormatABGR8888 = LCDIFV2_CTRLDESCL5_BPP(10U),   /*!< ABGR8888 unpacked, one pixel uses 32 bits. */
} lcdifv2_pixel_format_t;

/*! @brief LCDIF v2 source buffer configuration. */
typedef struct _lcdifv2_buffer_config
{
    uint16_t strideBytes; /*!< Number of bytes between two vertically adjacent pixels, suggest 64-bit aligned. */
    lcdifv2_pixel_format_t pixelFormat; /*!< Source buffer pixel format. */
} lcdifv2_buffer_config_t;

/*!
 * @brief LCDIF v2 layer alpha blending mode.
 */
typedef enum _lcdifv2_alpha_mode
{
    kLCDIFV2_AlphaDisable,   /*!< Disable alpha blend. */
    kLCDIFV2_AlphaOverride,  /*!< Use the gobal alpha value, pixel defined alpha value is overridden. */
    kLCDIFV2_AlphaEmbedded,  /*!< Use the pixel defined alpha value. */
    kLCDIFV2_AlphaPoterDuff, /*!< Use the PoterDuff alpha blending. */
} lcdifv2_alpha_mode_t;

/*!
 * @brief LCDIF v2 PoterDuff alpha mode.
 */
typedef enum _lcdifv2_pd_alpha_mode
{
    kLCDIFV2_PD_AlphaStraight = 0, /*!< Straight mode. */
    kLCDIFV2_PD_AlphaInversed = 1, /*!< Inversed mode. */
} lcdifv2_pd_alpha_mode_t;

/*!
 * @brief LCDIF v2 PoterDuff color mode.
 */
typedef enum _lcdifv2_pd_color_mode
{
    kLCDIFV2_PD_ColorNoAlpha   = 0, /*!< Output color directly. */
    kLCDIFV2_PD_ColorWithAlpha = 1, /*!< Output color multiples alpha. */
} lcdifv2_pd_color_mode_t;

/*!
 * @brief LCDIF v2 PoterDuff global alpha mode.
 */
typedef enum _lcdifv2_pd_global_alpha_mode
{
    kLCDIFV2_PD_GlobalAlpha = 0, /*!< Use global alpha. */
    kLCDIFV2_PD_LocalAlpha  = 1, /*!< Use local alpha. */
    kLCDIFV2_PD_ScaledAlpha = 2, /*!< Use scaled alpha. */
} lcdifv2_pd_global_alpha_mode_t;

/*!
 * @brief LCDIF v2 PoterDuff factor mode.
 */
typedef enum _lcdifv2_pd_factor_mode
{
    kLCDIFV2_PD_FactorOne           = 0, /*!< Use 1. */
    kLCDIFV2_PD_FactorZero          = 1, /*!< Use 0. */
    kLCDIFV2_PD_FactorStraightAlpha = 2, /*!< Use straight alpha. */
    kLCDIFV2_PD_FactorInversedAlpha = 3, /*!< Use inversed alpha. */
} lcdifv2_pd_factor_mode_t;

/*!
 * @brief LCDIF v2 layer alpha blending configuration.
 */
typedef struct _lcdifv2_blend_config
{
    uint8_t globalAlpha;                              /*!< Global alpha value, only used when
                                                        @ref alphaMode is @ref kLCDIFV2_AlphaOverride or
                                                        @ref kLCDIFV2_AlphaPoterDuff */
    lcdifv2_alpha_mode_t alphaMode;                   /*!< Alpha mode. */
    lcdifv2_pd_alpha_mode_t pdAlphaMode;              /*!< PoterDuff alpha mode, only used when @ref alphaMode is @ref
                                                        kLCDIFV2_AlphaPoterDuff */
    lcdifv2_pd_color_mode_t pdColorMode;              /*!< PoterDuff color mode, only used when @ref alphaMode is @ref
                                                        kLCDIFV2_AlphaPoterDuff */
    lcdifv2_pd_global_alpha_mode_t pdGlobalAlphaMode; /*!< PoterDuff global alpha mode, only used when @ref alphaMode is
                                           @ref kLCDIFV2_AlphaPoterDuff */
    lcdifv2_pd_factor_mode_t pdFactorMode;            /*!< PoterDuff factor mode, only used when @ref alphaMode is @ref
                                                      kLCDIFV2_AlphaPoterDuff */
} lcdifv2_blend_config_t;

/*! @brief LCDIFv2 Porter Duff blend mode. Note: Don't change the enum item value */
typedef enum _lcdifv2_pd_blend_mode
{
    kLCDIFV2_PD_Src = 0, /*!< Source Only */
    kLCDIFV2_PD_Atop,    /*!< Source Atop */
    kLCDIFV2_PD_Over,    /*!< Source Over */
    kLCDIFV2_PD_In,      /*!< Source In. */
    kLCDIFV2_PD_Out,     /*!< Source Out. */
    kLCDIFV2_PD_Dst,     /*!< Destination Only. */
    kLCDIFV2_PD_DstAtop, /*!< Destination Atop. */
    kLCDIFV2_PD_DstOver, /*!< Destination Over. */
    kLCDIFV2_PD_DstIn,   /*!< Destination In. */
    kLCDIFV2_PD_DstOut,  /*!< Destination Out. */
    kLCDIFV2_PD_Xor,     /*!< XOR. */
    kLCDIFV2_PD_Clear,   /*!< Clear. */
    kLCDIFV2_PD_Max,     /*!< Used for boarder detection. */
} lcdifv2_pd_blend_mode_t;

/*! @brief LCDIFv2 Porter Duff layer. Note: Don't change the enum item value */
typedef enum _lcdifv2_pd_layer
{
    kLCDIFV2_PD_SrcLayer  = 0, /*!< Source layer.      */
    kLCDIFV2_PD_DestLayer = 1, /*!< Destination layer. */
    kLCDIFV2_PD_LayerMax  = 2, /*!< Used for boarder detection. */
} lcdifv2_pd_layer_t;

/*******************************************************************************
 * APIs
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name LCDIF v2 initialization and de-initialization
 * @{
 */

/*!
 * @brief Initializes the LCDIF v2.
 *
 * This function ungates the LCDIF v2 clock and release the peripheral reset.
 *
 * @param base LCDIF v2 peripheral base address.
 */
void LCDIFV2_Init(LCDIFV2_Type *base);

/*!
 * @brief Deinitializes the LCDIF peripheral.
 *
 * @param base LCDIF peripheral base address.
 */
void LCDIFV2_Deinit(LCDIFV2_Type *base);

/*!
 * @brief Reset the LCDIF v2.
 *
 * @param base LCDIF peripheral base address.
 */
void LCDIFV2_Reset(LCDIFV2_Type *base);

/*! @} */

/*!
 * @name Display
 * @{
 */

/*!
 * @brief Gets the LCDIF display default configuration structure.
 *
 * This function sets the configuration structure to default values.
 * The default configuration is set to the following values.
 * @code
    config->panelWidth    = 0U;
    config->panelHeight   = 0U;
    config->hsw           = 3U;
    config->hfp           = 3U;
    config->hbp           = 3U;
    config->vsw           = 3U;
    config->vfp           = 3U;
    config->vbp           = 3U;
    config->polarityFlags = kLCDIFV2_VsyncActiveHigh | kLCDIFV2_HsyncActiveHigh | kLCDIFV2_DataEnableActiveHigh |
                            kLCDIFV2_DriveDataOnRisingClkEdge | kLCDIFV2_DataActiveHigh;
    config->lineOrder       = kLCDIFV2_LineOrderRGB;
    @endcode
 *
 * @param config Pointer to the LCDIF configuration structure.
 */
void LCDIFV2_DisplayGetDefaultConfig(lcdifv2_display_config_t *config);

/*!
 * @brief Set the LCDIF v2 display configurations.
 *
 * @param base LCDIF peripheral base address.
 * @param config Pointer to the LCDIF configuration structure.
 */
void LCDIFV2_SetDisplayConfig(LCDIFV2_Type *base, const lcdifv2_display_config_t *config);

/*!
 * @brief Enable or disable the display
 *
 * @param base LCDIF peripheral base address.
 * @param enable Enable or disable.
 */
static inline void LCDIFV2_EnableDisplay(LCDIFV2_Type *base, bool enable)
{
    if (enable)
    {
        base->DISP_PARA |= LCDIFV2_DISP_PARA_DISP_ON_MASK;
    }
    else
    {
        base->DISP_PARA &= ~LCDIFV2_DISP_PARA_DISP_ON_MASK;
    }
}

/*! @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables LCDIF interrupt requests.
 *
 * @param base LCDIF peripheral base address.
 * @param domain CPU domain the interrupt signal routed to.
 * @param mask interrupt source, OR'ed value of _lcdifv2_interrupt.
 */
static inline void LCDIFV2_EnableInterrupts(LCDIFV2_Type *base, uint8_t domain, uint32_t mask)
{
    base->INT[domain].INT_ENABLE |= mask;
}

/*!
 * @brief Disables LCDIF interrupt requests.
 *
 * @param base LCDIF peripheral base address.
 * @param domain CPU domain the interrupt signal routed to.
 * @param mask interrupt source, OR'ed value of _lcdifv2_interrupt.
 */
static inline void LCDIFV2_DisableInterrupts(LCDIFV2_Type *base, uint8_t domain, uint32_t mask)
{
    base->INT[domain].INT_ENABLE &= ~mask;
}

/*!
 * @brief Get LCDIF interrupt peding status.
 *
 * @param base LCDIF peripheral base address.
 * @param domain CPU domain the interrupt signal routed to.
 * @return Interrupt pending status, OR'ed value of _lcdifv2_interrupt.
 */
static inline uint32_t LCDIFV2_GetInterruptStatus(LCDIFV2_Type *base, uint8_t domain)
{
    return base->INT[domain].INT_STATUS;
}

/*!
 * @brief Clear LCDIF interrupt peding status.
 *
 * @param base LCDIF peripheral base address.
 * @param domain CPU domain the interrupt signal routed to.
 * @param mask of the flags to clear, OR'ed value of _lcdifv2_interrupt.
 */
static inline void LCDIFV2_ClearInterruptStatus(LCDIFV2_Type *base, uint8_t domain, uint32_t mask)
{
    base->INT[domain].INT_STATUS = mask;
}

/*! @} */

/*!
 * @name LUT
 * @{
 */

/*!
 * @brief Set the LUT data.
 *
 * This function sets the specific layer LUT data, if @p useShadowLoad is true,
 * call @ref LCDIFV2_TriggerLayerShadowLoad after this function, the
 * LUT will be loaded to the hardware during next vertical blanking period.
 * If @p useShadowLoad is false, the LUT data is loaded to hardware directly.
 *
 * @param base LCDIF v2 peripheral base address.
 * @param layerIndex Which layer to set.
 * @param lutData The LUT data to load.
 * @param count Count of @p lutData.
 * @param useShadowLoad Use shadow load.
 * @retval kStatus_Success Set success.
 * @retval kStatus_Fail Previous LUT data is not loaded to hardware yet.
 */
status_t LCDIFV2_SetLut(
    LCDIFV2_Type *base, uint8_t layerIndex, const uint32_t *lutData, uint16_t count, bool useShadowLoad);

/*! @} */

/*!
 * @name Layer operation
 * @{
 */

/*!
 * @brief Set the layer dimension.
 *
 * @param base LCDIFv2 peripheral base address.
 * @param layerIndex Layer layerIndex.
 * @param width Layer width in pixel.
 * @param height Layer height.
 *
 * @note The layer width must be in multiples of the number of pixels that can be stored in 32 bits
 */
static inline void LCDIFV2_SetLayerSize(LCDIFV2_Type *base, uint8_t layerIndex, uint16_t width, uint16_t height)
{
    base->LAYER[layerIndex].CTRLDESCL1 =
        ((uint32_t)height << LCDIFV2_CTRLDESCL1_HEIGHT_SHIFT) | ((uint32_t)width << LCDIFV2_CTRLDESCL1_WIDTH_SHIFT);
}

/*!
 * @brief Set the layer position in output frame.
 *
 * @param base LCDIFv2 peripheral base address.
 * @param layerIndex Layer layerIndex.
 * @param offsetX Horizontal offset, start from 0.
 * @param offsetY Vertical offset, start from 0.
 */
static inline void LCDIFV2_SetLayerOffset(LCDIFV2_Type *base, uint8_t layerIndex, uint16_t offsetX, uint16_t offsetY)
{
    base->LAYER[layerIndex].CTRLDESCL2 =
        ((uint32_t)offsetX << LCDIFV2_CTRLDESCL2_POSX_SHIFT) | ((uint32_t)offsetY << LCDIFV2_CTRLDESCL2_POSY_SHIFT);
}

/*!
 * @brief Set the layer source buffer configuration.
 *
 * @param base LCDIFv2 peripheral base address.
 * @param layerIndex Layer layerIndex.
 * @param config Pointer to the configuration.
 */
void LCDIFV2_SetLayerBufferConfig(LCDIFV2_Type *base, uint8_t layerIndex, const lcdifv2_buffer_config_t *config);

/*!
 * @brief Set the layer source buffer address.
 *
 * This function is used for fast runtime source buffer change.
 *
 * @param base LCDIFv2 peripheral base address.
 * @param layerIndex Layer layerIndex.
 * @param addr The new source buffer address passed to the layer, should be 64-bit aligned.
 */
static inline void LCDIFV2_SetLayerBufferAddr(LCDIFV2_Type *base, uint8_t layerIndex, uint32_t addr)
{
    base->LAYER[layerIndex].CTRLDESCL4 = LCDIFV2_ADDR_CPU_2_IP(addr);
}

/*!
 * @brief Enable or disable the layer.
 *
 * @param base LCDIFv2 peripheral base address.
 * @param layerIndex Layer layerIndex.
 * @param enable Pass in true to enable, false to disable.
 */
static inline void LCDIFV2_EnableLayer(LCDIFV2_Type *base, uint8_t layerIndex, bool enable)
{
    if (enable)
    {
        base->LAYER[layerIndex].CTRLDESCL5 |= LCDIFV2_CTRLDESCL5_EN_MASK;
    }
    else
    {
        base->LAYER[layerIndex].CTRLDESCL5 &= ~LCDIFV2_CTRLDESCL5_EN_MASK;
    }
}

/*!
 * @brief Trigger the layer configuration shadow load.
 *
 * The new layer configurations are written to the shadow registers first,
 * When all configurations written finished, call this function, then shadowed
 * control registers are updated to the active control registers on VSYNC of
 * next frame.
 *
 * @param base LCDIFv2 peripheral base address.
 * @param layerIndex Layer layerIndex.
 */
static inline void LCDIFV2_TriggerLayerShadowLoad(LCDIFV2_Type *base, uint8_t layerIndex)
{
    base->LAYER[layerIndex].CTRLDESCL5 |= LCDIFV2_CTRLDESCL5_SHADOW_LOAD_EN_MASK;
}

/*!
 * @brief Set the layer back ground color.
 *
 * The back ground color is used when layer not actived.
 *
 * @param base LCDIFv2 peripheral base address.
 * @param layerIndex Index of the layer.
 * @param backGroundColor Background color to use when this layer is not active.
 */
static inline void LCDIFV2_SetLayerBackGroundColor(LCDIFV2_Type *base, uint8_t layerIndex, uint32_t backGroundColor)
{
    base->LAYER[layerIndex].CTRLDESCL6 = backGroundColor;
}

/*!
 * @brief Set the layer alpha blend mode.
 *
 * @param base LCDIFv2 peripheral base address.
 * @param layerIndex Index of the CSC unit.
 * @param config Pointer to the blend configuration.
 */
void LCDIFV2_SetLayerBlendConfig(LCDIFV2_Type *base, uint8_t layerIndex, const lcdifv2_blend_config_t *config);

/*!
 * @brief Set the color space conversion mode.
 *
 * Supports YUV2RGB and YCbCr2RGB.
 *
 * @param base LCDIFv2 peripheral base address.
 * @param layerIndex Index of the layer.
 * @param mode The conversion mode.
 */
void LCDIFV2_SetCscMode(LCDIFV2_Type *base, uint8_t layerIndex, lcdifv2_csc_mode_t mode);

/*! @} */

/*!
 * @name Porter Duff
 * @{
 */

/*!
 * @brief Get the blend configuration for Porter Duff blend.
 *
 * This function gets the blend configuration for Porter Duff blend,
 * config->pdFactorMode is set according to @p layer and @p mode,
 * other blend configurations are set to:
 *
 * @code
    config->pdAlphaMode = kLCDIFV2_PD_AlphaStraight;
    config->pdColorMode = kLCDIFV2_PD_ColorStraight;
    config->pdGlobalAlphaMode = kLCDIFV2_PD_LocalAlpha;
    config->alphaMode = kLCDIFV2_AlphaPoterDuff;
   @endcode
 *
 * This is the basic Porter Duff blend configuration, user still could
 * modify the configurations after this function.
 *
 * @param mode Porter Duff blend mode.
 * @param layer The configuration for source layer or destination layer.
 * @param config Pointer to the configuration.
 * @retval kStatus_Success Get the configuration successfully.
 * @retval kStatus_InvalidArgument The argument is invalid.
 */
status_t LCDIFV2_GetPorterDuffConfig(lcdifv2_pd_blend_mode_t mode,
                                     lcdifv2_pd_layer_t layer,
                                     lcdifv2_blend_config_t *config);

/*! @} */

/*!
 * @name Misc
 * @{
 */

/*!
 * @brief Get the global alpha values for multiple layer blend.
 *
 * This function calculates the global alpha value for each layer based on the
 * desired blended alpha.
 *
 * When all layers use the global alpha, the relationship of blended alpha
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
 * This function calculates the global alpha based on the blended alpha. The @p blendedAlpha and
 * @p globalAlpha are all arrays of size @p layerCount. The first layer is a background layer,
 * so blendedAlpha[0] is useless, globalAlpha[0] is always 255.
 *
 * @param[in] blendedAlpha The desired blended alpha value, alpha range 0~255.
 * @param[out] globalAlpha Calculated global alpha set to each layer register.
 * @param[in] layerCount Total layer count.
 * @retval kStatus_Success Get successfully.
 * @retval kStatus_InvalidArgument The argument is invalid.
 */
status_t LCDIFV2_GetMultiLayerGlobalAlpha(const uint8_t blendedAlpha[], uint8_t globalAlpha[], uint8_t layerCount);

/*! @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /*FSL_LCDIFV2_H_*/
