/*
 * Copyright 2017-2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_PXP_H_
#define _FSL_PXP_H_

#include "fsl_common.h"

/* Compatibility macro map. */
#if defined(PXP_AS_CTRL_ALPHA_INVERT_MASK) && (!defined(PXP_AS_CTRL_ALPHA0_INVERT_MASK))
#define PXP_AS_CTRL_ALPHA0_INVERT_MASK PXP_AS_CTRL_ALPHA_INVERT_MASK
#endif

#if defined(PXP_AS_CTRL_ALPHA_INVERT_MASK) && (!defined(PXP_AS_CTRL_ALPHA_INVERT_MASK))
#define PXP_AS_CTRL_ALPHA0_INVERT_MASK PXP_AS_CTRL_ALPHA_INVERT_MASK
#endif

#if defined(PXP_STAT_IRQ_MASK) && (!defined(PXP_STAT_IRQ0_MASK))
#define PXP_STAT_IRQ0_MASK PXP_STAT_IRQ_MASK
#endif

#if defined(PXP_STAT_AXI_READ_ERROR_MASK) && (!defined(PXP_STAT_AXI_READ_ERROR_0_MASK))
#define PXP_STAT_AXI_READ_ERROR_0_MASK PXP_STAT_AXI_READ_ERROR_MASK
#endif

#if defined(PXP_STAT_AXI_WRITE_ERROR_MASK) && (!defined(PXP_STAT_AXI_WRITE_ERROR_0_MASK))
#define PXP_STAT_AXI_WRITE_ERROR_0_MASK PXP_STAT_AXI_WRITE_ERROR_MASK
#endif

/*!
 * @addtogroup pxp_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* PXP global LUT table is 16K. */
#define PXP_LUT_TABLE_BYTE (16UL * 1024UL)
/* Intenral memory for LUT, the size is 256 bytes. */
#define PXP_INTERNAL_RAM_LUT_BYTE (256)

/*! @name Driver version */
/*@{*/
#define FSL_PXP_DRIVER_VERSION (MAKE_VERSION(2, 4, 0))
/*@}*/

/* This macto indicates whether the rotate sub module is shared by process surface and output buffer. */
#if defined(PXP_CTRL_ROT_POS_MASK)
#define PXP_SHARE_ROTATE 1
#else
#define PXP_SHARE_ROTATE 0
#endif

/* This macto indicates whether PXP needs mux the process path. */
#if defined(PXP_DATA_PATH_CTRL0_MUX0_SEL_MASK)
#define PXP_USE_PATH 1
#else
#define PXP_USE_PATH 0
#endif

#if PXP_USE_PATH
#define PXP_PATH(mux, sel)          (((mux) << 8U) | (sel))
#define PXP_GET_MUX_FROM_PATH(path) ((path) >> 8U)
#define PXP_GET_SEL_FROM_PATH(path) ((path)&0x03U)
#endif /* PXP_USE_PATH */

/*! @brief PXP interrupts to enable. */
enum _pxp_interrupt_enable
{
    kPXP_CompleteInterruptEnable    = PXP_CTRL_IRQ_ENABLE_MASK,      /*!< PXP process completed. bit 1 */
    kPXP_CommandLoadInterruptEnable = PXP_CTRL_NEXT_IRQ_ENABLE_MASK, /*!< Interrupt to show that the command set by @ref
                                                                        PXP_SetNextCommand has been loaded. bit 2 */
#if !(defined(FSL_FEATURE_PXP_HAS_NO_LUT) && FSL_FEATURE_PXP_HAS_NO_LUT)
    kPXP_LutDmaLoadInterruptEnable =
        PXP_CTRL_LUT_DMA_IRQ_ENABLE_MASK, /*!< The LUT table has been loaded by DMA. bit 3 */
#endif
#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3
    kPXP_CompressDoneInterruptEnable =
        PXP_IRQ_MASK_COMPRESS_DONE_IRQ_EN_MASK >> 16U, /*!< Compress done interrupt enable. bit 15 */
    kPXP_InputFetchCh0InterruptEnable = PXP_IRQ_MASK_FIRST_CH0_PREFETCH_IRQ_EN_MASK
                                        << 16U, /*!< Input fetch channel 0 completed. bit 16 */
    kPXP_InputFetchCh1InterruptEnable = PXP_IRQ_MASK_FIRST_CH1_PREFETCH_IRQ_EN_MASK
                                        << 16U, /*!< Input fetch channel 1 completed. bit 17 */
    kPXP_InputStoreCh0InterruptEnable = PXP_IRQ_MASK_FIRST_CH0_STORE_IRQ_EN_MASK
                                        << 16U, /*!< Input store channel 0 completed. bit 18 */
    kPXP_InputStoreCh1InterruptEnable = PXP_IRQ_MASK_FIRST_CH1_STORE_IRQ_EN_MASK
                                        << 16U, /*!< Input store channel 1 completed. bit 19 */
    kPXP_DitherFetchCh0InterruptEnable = PXP_IRQ_MASK_DITHER_CH0_PREFETCH_IRQ_EN_MASK
                                         << 16U, /*!< Dither fetch channel 0 completed. bit 20 */
    kPXP_DitherFetchCh1InterruptEnable = PXP_IRQ_MASK_DITHER_CH1_PREFETCH_IRQ_EN_MASK
                                         << 16U, /*!< Dither fetch channel 1 completed. bit 21 */
    kPXP_DitherStoreCh0InterruptEnable = PXP_IRQ_MASK_DITHER_CH0_STORE_IRQ_EN_MASK
                                         << 16U, /*!< Dither store channle 0 completed. bit 22 */
    kPXP_DitherStoreCh1InterruptEnable = PXP_IRQ_MASK_DITHER_CH1_STORE_IRQ_EN_MASK
                                         << 16U, /*!< Dither store channle 1 completed. bit 23 */
    kPXP_WfeaStoreCh0InterruptEnable = PXP_IRQ_MASK_WFE_A_CH0_STORE_IRQ_EN_MASK
                                       << 16U, /*!< WFE-A store channel 0 completed. bit 24 */
    kPXP_WfeaStoreCh1InterruptEnable = PXP_IRQ_MASK_WFE_A_CH1_STORE_IRQ_EN_MASK
                                       << 16U, /*!< WFE-A store channel 1 completed. bit 25 */
    kPXP_WfebStoreCh0InterruptEnable = PXP_IRQ_MASK_WFE_B_CH0_STORE_IRQ_EN_MASK
                                       << 16U, /*!< WFE-B store channel 0 completed. bit 26 */
    kPXP_WfebStoreCh1InterruptEnable = PXP_IRQ_MASK_WFE_B_CH1_STORE_IRQ_EN_MASK
                                       << 16U, /*!< WFE-B store channel 1 completed. bit 27 */
    kPXP_InputStoreInterruptEnable  = PXP_IRQ_MASK_FIRST_STORE_IRQ_EN_MASK << 16U, /*!< Input store completed. bit 28 */
    kPXP_DitherStoreInterruptEnable = PXP_IRQ_MASK_DITHER_STORE_IRQ_EN_MASK
                                      << 16U,                                    /*!< Dither store completed. bit 29 */
    kPXP_WfeaStoreInterruptEnable = PXP_IRQ_MASK_WFE_A_STORE_IRQ_EN_MASK << 16U, /*!< WFE-A store completed. bit 30 */
    kPXP_WfebStoreInterruptEnable = PXP_IRQ_MASK_WFE_B_STORE_IRQ_EN_MASK << 16U, /*!< WFE-B store completed. bit 31 */
#endif                                                                           /* FSL_FEATURE_PXP_V3 */
};

/*!
 * @brief PXP status flags.
 *
 * @note These enumerations are meant to be OR'd together to form a bit mask.
 */
enum _pxp_flags
{
    kPXP_CompleteFlag       = PXP_STAT_IRQ0_MASK,              /*!< PXP process completed. bit 0 */
    kPXP_Axi0WriteErrorFlag = PXP_STAT_AXI_WRITE_ERROR_0_MASK, /*!< PXP encountered an AXI write error and processing
                                                                  has been terminated. bit 1*/
    kPXP_Axi0ReadErrorFlag = PXP_STAT_AXI_READ_ERROR_0_MASK,   /*!< PXP encountered an AXI read error and processing has
                                                                  been terminated. bit 2 */
    kPXP_CommandLoadFlag = PXP_STAT_NEXT_IRQ_MASK, /*!< The command set by @ref PXP_SetNextCommand has been loaded,
                                                      could set new command. bit 3 */
#if !(defined(FSL_FEATURE_PXP_HAS_NO_LUT) && FSL_FEATURE_PXP_HAS_NO_LUT)
    kPXP_LutDmaLoadFlag = PXP_STAT_LUT_DMA_LOAD_DONE_IRQ_MASK, /*!< The LUT table has been loaded by DMA. bit 8 */
#endif
#if defined(PXP_STAT_AXI_READ_ERROR_1_MASK)
    kPXP_Axi1WriteErrorFlag = PXP_STAT_AXI_WRITE_ERROR_1_MASK, /*!< PXP encountered an AXI write error and processing
                                                                  has been terminated. bit 9 */
    kPXP_Axi1ReadErrorFlag = PXP_STAT_AXI_READ_ERROR_1_MASK,   /*!< PXP encountered an AXI read error and processing has
                                                                  been terminated. bit 10 */
#endif
#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3
    kPXP_CompressDoneFlag          = PXP_IRQ_COMPRESS_DONE_IRQ_MASK >> 16U, /*!< Compress done. bit 15 */
    kPXP_InputFetchCh0CompleteFlag = PXP_IRQ_FIRST_CH0_PREFETCH_IRQ_MASK
                                     << 16U, /*!< Input fetch channel 0 completed. bit 16 */
    kPXP_InputFetchCh1CompleteFlag = PXP_IRQ_FIRST_CH1_PREFETCH_IRQ_MASK
                                     << 16U, /*!< Input fetch channel 1 completed. bit 17 */
    kPXP_InputStoreCh0CompleteFlag = PXP_IRQ_FIRST_CH0_STORE_IRQ_MASK
                                     << 16U, /*!< Input store channel 0 completed. bit 18 */
    kPXP_InputStoreCh1CompleteFlag = PXP_IRQ_FIRST_CH1_STORE_IRQ_MASK
                                     << 16U, /*!< Input store channel 1 completed. bit 19 */
    kPXP_DitherFetchCh0CompleteFlag = PXP_IRQ_DITHER_CH0_PREFETCH_IRQ_MASK
                                      << 16U, /*!< Dither fetch channel 0 completed. bit 20 */
    kPXP_DitherFetchCh1CompleteFlag = PXP_IRQ_DITHER_CH1_PREFETCH_IRQ_MASK
                                      << 16U, /*!< Dither fetch channel 1 completed. bit 21 */
    kPXP_DitherStoreCh0CompleteFlag = PXP_IRQ_DITHER_CH0_STORE_IRQ_MASK
                                      << 16U, /*!< Dither store channel 0 completed. bit 22 */
    kPXP_DitherStoreCh1CompleteFlag = PXP_IRQ_DITHER_CH1_STORE_IRQ_MASK
                                      << 16U, /*!< Dither store channel 1 completed. bit 23 */
    kPXP_WfeaStoreCh0CompleteFlag = PXP_IRQ_WFE_A_CH0_STORE_IRQ_MASK
                                    << 16U, /*!< WFE-A store channel 0 completed. bit 24 */
    kPXP_WfeaStoreCh1CompleteFlag = PXP_IRQ_WFE_A_CH1_STORE_IRQ_MASK
                                    << 16U, /*!< WFE-A store channel 1 completed. bit 25 */
    kPXP_WfebStoreCh0CompleteFlag = PXP_IRQ_WFE_B_CH0_STORE_IRQ_MASK
                                    << 16U, /*!< WFE-B store channel 0 completed. bit 26 */
    kPXP_WfebStoreCh1CompleteFlag = PXP_IRQ_WFE_B_CH1_STORE_IRQ_MASK
                                    << 16U,                              /*!< WFE-B store channel 1 completed. bit 27 */
    kPXP_InputStoreCompleteFlag  = PXP_IRQ_FIRST_STORE_IRQ_MASK << 16U,  /*!< Input store completed. bit 28 */
    kPXP_DitherStoreCompleteFlag = PXP_IRQ_DITHER_STORE_IRQ_MASK << 16U, /*!< Dither store completed. bit 29 */
    kPXP_WfeaStoreCompleteFlag   = PXP_IRQ_WFE_A_STORE_IRQ_MASK << 16U,  /*!< WFE-A store completed. bit 30 */
    kPXP_WfebStoreCompleteFlag   = PXP_IRQ_WFE_B_STORE_IRQ_MASK << 16U,  /*!< WFE-B store completed. bit 31 */
#endif                                                                   /* FSL_FEATURE_PXP_V3 */
};

#if PXP_USE_PATH
#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3
typedef enum _pxp_path
{
    kPXP_Mux0SelectProcessSurfaceEngine     = PXP_PATH(0U, 0U), /*!< MUX0 select Process Surface engine. */
    kPXP_Mux0SelectInputFetchEngineChannel0 = PXP_PATH(0U, 1U), /*!< MUX0 select input Fetch engine channel 0. */
    kPXP_Mux0SelectInputFetchEngineChannel1 = PXP_PATH(0U, 2U), /*!< MUX0 select input Fetch engine channel 1. */
    kPXP_Mux0SelectNone                     = PXP_PATH(0U, 3U), /*!< MUX0 select no output. */
    kPXP_Mux1SelectInputFetchEngineChannel0 = PXP_PATH(1U, 0U), /*!< MUX1 select input Fetch engine channel 0. */
    kPXP_Mux1SelectRotation1Engine          = PXP_PATH(1U, 1U), /*!< MUX1 select Rotation1 engine output. */
    kPXP_Mux1SelectNone                     = PXP_PATH(1U, 2U), /*!< MUX1 select no output. */
    kPXP_Mux2SelectInputFetchEngineChannel1 = PXP_PATH(2U, 0U), /*!< MUX2 select input Fetch engine channel 1. */
    kPXP_Mux2SelectRotation1Engine          = PXP_PATH(2U, 1U), /*!< MUX2 select Rotation1 engine output. */
    kPXP_Mux2SelectNone                     = PXP_PATH(2U, 2U), /*!< MUX2 select no output. */
    kPXP_Mux3SelectCsc1Engine               = PXP_PATH(3U, 0U), /*!< MUX3 select output of CSC1 engine. */
    kPXP_Mux3SelectRotation1Engine          = PXP_PATH(3U, 1U), /*!< MUX3 select output of Rotation1 engine. */
    kPXP_Mux3SelectNone                     = PXP_PATH(3U, 2U), /*!< MUX3 select no output. */
    kPXP_Mux5SelectMux1                     = PXP_PATH(5U, 0U), /*!< MUX5 select output of MUX1. */
    kPXP_Mux5SelectAlphaBlending1       = PXP_PATH(5U, 1U),  /*!< MUX5 select output of alpha blending / color key 1. */
    kPXP_Mux5SelectNone                 = PXP_PATH(5U, 2U),  /*!< MUX5 select no output. */
    kPXP_Mux6SelectAlphaBlending1       = PXP_PATH(6U, 0U),  /*!< MUX6 select output of alpha blending / color key 1. */
    kPXP_Mux6SelectAlphaBlending0       = PXP_PATH(6U, 1U),  /*!< MUX6 select output of alpha blending / color key 0. */
    kPXP_Mux6SelectNone                 = PXP_PATH(6U, 2U),  /*!< MUX6 select no output. */
    kPXP_Mux7SelectMux5                 = PXP_PATH(7U, 0U),  /*!< MUX7 select output of MUX5. */
    kPXP_Mux7SelectCsc2Engine           = PXP_PATH(7U, 1U),  /*!< MUX7 select output of CSC2 engine. */
    kPXP_Mux7SelectNone                 = PXP_PATH(7U, 2U),  /*!< MUX7 select no output. */
    kPXP_Mux8SelectCsc2Engine           = PXP_PATH(8U, 0U),  /*!< MUX8 select output of CSC2 engine. */
    kPXP_Mux8SelectAlphaBlending0       = PXP_PATH(8U, 1U),  /*!< MUX8 select output of alpha blending / color key 0. */
    kPXP_Mux8SelectNone                 = PXP_PATH(8U, 2U),  /*!< MUX8 select no output. */
    kPXP_Mux9SelectMux7                 = PXP_PATH(9U, 0U),  /*!< MUX9 select output of MUX7. */
    kPXP_Mux9SelectMux8                 = PXP_PATH(9U, 1U),  /*!< MUX9 select output of MUX8. */
    kPXP_Mux9SelectNone                 = PXP_PATH(9U, 2U),  /*!< MUX9 select no output. */
    kPXP_Mux10SelectMux7                = PXP_PATH(10U, 0U), /*!< MUX10 select output of MUX7. */
    kPXP_Mux10SelectLut                 = PXP_PATH(10U, 1U), /*!< MUX10 select output of LUT. */
    kPXP_Mux10SelectNone                = PXP_PATH(10U, 2U), /*!< MUX10 select no output. */
    kPXP_Mux11SelectLut                 = PXP_PATH(11U, 0U), /*!< MUX11 select output of LUT. */
    kPXP_Mux11SelectMux8                = PXP_PATH(11U, 1U), /*!< MUX11 select output of MUX8. */
    kPXP_Mux11SelectNone                = PXP_PATH(11U, 2U), /*!< MUX11 select no output. */
    kPXP_Mux12SelectMux10               = PXP_PATH(12U, 0U), /*!< MUX12 select output of MUX10. */
    kPXP_Mux12SelectMux11               = PXP_PATH(12U, 1U), /*!< MUX12 select output of MUX11. */
    kPXP_Mux12SelectNone                = PXP_PATH(12U, 2U), /*!< MUX12 select no output. */
    kPXP_Mux13SelectNone                = PXP_PATH(13U, 0U), /*!< MUX13 select no output. */
    kPXP_Mux13SelectFetchEngineChannel1 = PXP_PATH(13U, 1U), /*!< MUX13 select input Fetch engine channel 1. */
    kPXP_Mux14SelectRotation0Engine     = PXP_PATH(14U, 0U), /*!< MUX14 select output of Rotation0 engine. */
    kPXP_Mux14SelectMux11               = PXP_PATH(14U, 1U), /*!< MUX14 select output of MUX11. */
    kPXP_Mux14SelectNone                = PXP_PATH(14U, 2U), /*!< MUX14 select no output. */
    kPXP_Mux15SelectFetchEngineChannel0 = PXP_PATH(15U, 0U), /*!< MUX15 select input Fetch engine channel 0. */
    kPXP_Mux15SelectMux10               = PXP_PATH(15U, 1U), /*!< MUX15 select output of MUX10. */
    kPXP_Mux15SelectNone                = PXP_PATH(15U, 2U), /*!< MUX15 select no output. */
    kPXP_Mux16SelectAluA                = PXP_PATH(16U, 0U), /*!< MUX16 select output of ALU A. */
    kPXP_Mux16SelectOutput              = PXP_PATH(16U, 1U), /*!< MUX16 select output of legacy output. */
    kPXP_Mux16SelectAluB                = PXP_PATH(16U, 2U), /*!< MUX16 select output of ALU B. */
    kPXP_Mux16SelectNone                = PXP_PATH(16U, 3U), /*!< MUX16 select no output. */
    kPXP_Mux17SelectAluA                = PXP_PATH(17U, 0U), /*!< MUX17 select output of ALU A. */
    kPXP_Mux17SelectAluB                = PXP_PATH(17U, 1U), /*!< MUX17 select output of ALU B. */
    kPXP_Mux17SelectNone                = PXP_PATH(17U, 2U), /*!< MUX17 select no output. */
} pxp_path_t;
#else
typedef enum _pxp_path
{
    kPXP_Mux0SelectFetchDataArray   = PXP_PATH(0U, 0U),  /*!< MUX0 select Fetch Data Array. */
    kPXP_Mux0SelectAlu              = PXP_PATH(0U, 1U),  /*!< MUX0 select output of ALU. */
    kPXP_Mux0SelectNone             = PXP_PATH(0U, 2U),  /*!< MUX0 select no output. */
    kPXP_Mux1SelectLut              = PXP_PATH(1U, 0U),  /*!< MUX1 select output of LUT. */
    kPXP_Mux1SelectMux0             = PXP_PATH(1U, 1U),  /*!< MUX1 select output of MUX0. */
    kPXP_Mux1SelectNone             = PXP_PATH(1U, 2U),  /*!< MUX1 select no output. */
    kPXP_Mux3SelectRotation1Engine  = PXP_PATH(3U, 0U),  /*!< MUX3 select output of Rotation1 engine. */
    kPXP_Mux3SelectCsc1Engine       = PXP_PATH(3U, 1U),  /*!< MUX3 select output of CSC1 engine. */
    kPXP_Mux3SelectNone             = PXP_PATH(3U, 2U),  /*!< MUX3 select no output. */
    kPXP_Mux8SelectCsc2Engine       = PXP_PATH(8U, 0U),  /*!< MUX8 select output of CSC2 engine. */
    kPXP_Mux8SelectAlphaBlending0   = PXP_PATH(8U, 1U),  /*!< MUX8 select output of alpha blending / color key 0. */
    kPXP_Mux8SelectNone             = PXP_PATH(8U, 2U),  /*!< MUX8 select no output. */
    kPXP_Mux9SelectMux0             = PXP_PATH(9U, 0U),  /*!< MUX9 select output of MUX0. */
    kPXP_Mux9SelectMux8             = PXP_PATH(9U, 1U),  /*!< MUX9 select output of MUX8. */
    kPXP_Mux9SelectNone             = PXP_PATH(9U, 2U),  /*!< MUX9 select no output. */
    kPXP_Mux11SelectLut             = PXP_PATH(11U, 0U), /*!< MUX11 select output of LUT. */
    kPXP_Mux11SelectMux8            = PXP_PATH(11U, 1U), /*!< MUX11 select output of MUX8. */
    kPXP_Mux11SelectNone            = PXP_PATH(11U, 2U), /*!< MUX11 select no output. */
    kPXP_Mux12SelectRotation0Engine = PXP_PATH(12U, 0U), /*!< MUX12 select output of Rotation0 engine. */
    kPXP_Mux12SelectMux11           = PXP_PATH(12U, 1U), /*!< MUX12 select output of MUX11. */
    kPXP_Mux12SelectNone            = PXP_PATH(12U, 2U), /*!< MUX12 select no output. */
    kPXP_Mux14SelectDitherEngine    = PXP_PATH(14U, 0U), /*!< MUX14 select output of Dither engine. */
    kPXP_Mux14SelectMux12           = PXP_PATH(14U, 1U), /*!< MUX14 select output of MUX12. */
    kPXP_Mux14SelectNone            = PXP_PATH(14U, 2U), /*!< MUX14 select no output. */
    kPXP_Mux16SelectOutputBuffer    = PXP_PATH(16U, 0U), /*!< MUX16 select output of output buffer. */
    kPXP_Mux16SelectStoreEngine     = PXP_PATH(16U, 1U), /*!< MUX16 select output of store engine. */
    kPXP_Mux16SelectNone            = PXP_PATH(16U, 2U), /*!< MUX16 select no output. */
    kPXP_Mux17SelectOutputBuffer    = PXP_PATH(17U, 0U), /*!< MUX17 select output of output buffer. */
    kPXP_Mux17SelectStoreEngine     = PXP_PATH(17U, 1U), /*!< MUX17 select output of store engine. */
    kPXP_Mux17SelectNone            = PXP_PATH(17U, 2U), /*!< MUX17 select no output. */
} pxp_path_t;
#endif /* FSL_FEATURE_PXP_V3 */
#endif /* PXP_USE_PATH */

/*! @brief PXP output flip mode. */
typedef enum _pxp_flip_mode
{
    kPXP_FlipDisable    = 0U,    /*!< Flip disable. */
    kPXP_FlipHorizontal = 0x01U, /*!< Horizontal flip. */
    kPXP_FlipVertical   = 0x02U, /*!< Vertical flip. */
    kPXP_FlipBoth       = 0x03U, /*!< Flip both directions. */
} pxp_flip_mode_t;

/*! @brief PXP rotate mode. */
typedef enum _pxp_rotate_position
{
    kPXP_RotateOutputBuffer = 0U, /*!< Rotate the output buffer. */
    kPXP_RotateProcessSurface,    /*!< Rotate the process surface. */
} pxp_rotate_position_t;

/*! @brief PXP rotate degree. */
typedef enum _pxp_rotate_degree
{
    kPXP_Rotate0 = 0U, /*!< Clock wise rotate 0 deg. */
    kPXP_Rotate90,     /*!< Clock wise rotate 90 deg. */
    kPXP_Rotate180,    /*!< Clock wise rotate 180 deg. */
    kPXP_Rotate270,    /*!< Clock wise rotate 270 deg. */
} pxp_rotate_degree_t;

/*! @brief PXP interlaced output mode. */
typedef enum _pxp_interlaced_output_mode
{
    kPXP_OutputProgressive = 0U, /*!< All data written in progressive format to output buffer 0. */
    kPXP_OutputField0,           /*!< Only write field 0 data to output buffer 0. */
    kPXP_OutputField1,           /*!< Only write field 1 data to output buffer 0. */
    kPXP_OutputInterlaced,       /*!< Field 0 write to buffer 0, field 1 write to buffer 1. */
} pxp_interlaced_output_mode_t;

/*! @brief PXP output buffer format. */
typedef enum _pxp_output_pixel_format
{
    kPXP_OutputPixelFormatARGB8888  = 0x0,  /*!< 32-bit pixels with alpha. */
    kPXP_OutputPixelFormatRGB888    = 0x4,  /*!< 32-bit pixels without alpha (unpacked 24-bit format) */
    kPXP_OutputPixelFormatRGB888P   = 0x5,  /*!< 24-bit pixels without alpha (packed 24-bit format) */
    kPXP_OutputPixelFormatARGB1555  = 0x8,  /*!< 16-bit pixels with alpha. */
    kPXP_OutputPixelFormatARGB4444  = 0x9,  /*!< 16-bit pixels with alpha. */
    kPXP_OutputPixelFormatRGB555    = 0xC,  /*!< 16-bit pixels without alpha. */
    kPXP_OutputPixelFormatRGB444    = 0xD,  /*!< 16-bit pixels without alpha. */
    kPXP_OutputPixelFormatRGB565    = 0xE,  /*!< 16-bit pixels without alpha. */
    kPXP_OutputPixelFormatYUV1P444  = 0x10, /*!< 32-bit pixels (1-plane XYUV unpacked). */
    kPXP_OutputPixelFormatUYVY1P422 = 0x12, /*!< 16-bit pixels (1-plane U0,Y0,V0,Y1 interleaved bytes) */
    kPXP_OutputPixelFormatVYUY1P422 = 0x13, /*!< 16-bit pixels (1-plane V0,Y0,U0,Y1 interleaved bytes) */
    kPXP_OutputPixelFormatY8        = 0x14, /*!< 8-bit monochrome pixels (1-plane Y luma output) */
    kPXP_OutputPixelFormatY4        = 0x15, /*!< 4-bit monochrome pixels (1-plane Y luma, 4 bit truncation) */
    kPXP_OutputPixelFormatYUV2P422  = 0x18, /*!< 16-bit pixels (2-plane UV interleaved bytes) */
    kPXP_OutputPixelFormatYUV2P420  = 0x19, /*!< 16-bit pixels (2-plane UV) */
    kPXP_OutputPixelFormatYVU2P422  = 0x1A, /*!< 16-bit pixels (2-plane VU interleaved bytes) */
    kPXP_OutputPixelFormatYVU2P420  = 0x1B, /*!< 16-bit pixels (2-plane VU) */
} pxp_output_pixel_format_t;

/*! @brief PXP output buffer configuration. */
typedef struct _pxp_output_buffer_config
{
    pxp_output_pixel_format_t pixelFormat;       /*!< Output buffer pixel format. */
    pxp_interlaced_output_mode_t interlacedMode; /*!< Interlaced output mode. */
    uint32_t buffer0Addr;                        /*!< Output buffer 0 address. */
    uint32_t buffer1Addr;                        /*!< Output buffer 1 address, used for UV data in YUV 2-plane mode, or
                                                      field 1 in output interlaced mode. */
    uint16_t pitchBytes;                         /*!< Number of bytes between two vertically adjacent pixels. */
    uint16_t width;                              /*!< Pixels per line. */
    uint16_t height;                             /*!< How many lines in output buffer. */
} pxp_output_buffer_config_t;

/*! @brief PXP process surface buffer pixel format. */
typedef enum _pxp_ps_pixel_format
{
    kPXP_PsPixelFormatRGB888    = 0x4,  /*!< 32-bit pixels without alpha (unpacked 24-bit format) */
    kPXP_PsPixelFormatRGB555    = 0xC,  /*!< 16-bit pixels without alpha. */
    kPXP_PsPixelFormatRGB444    = 0xD,  /*!< 16-bit pixels without alpha. */
    kPXP_PsPixelFormatRGB565    = 0xE,  /*!< 16-bit pixels without alpha. */
    kPXP_PsPixelFormatYUV1P444  = 0x10, /*!< 32-bit pixels (1-plane XYUV unpacked). */
    kPXP_PsPixelFormatUYVY1P422 = 0x12, /*!< 16-bit pixels (1-plane U0,Y0,V0,Y1 interleaved bytes) */
    kPXP_PsPixelFormatVYUY1P422 = 0x13, /*!< 16-bit pixels (1-plane V0,Y0,U0,Y1 interleaved bytes) */
    kPXP_PsPixelFormatY8        = 0x14, /*!< 8-bit monochrome pixels (1-plane Y luma output) */
    kPXP_PsPixelFormatY4        = 0x15, /*!< 4-bit monochrome pixels (1-plane Y luma, 4 bit truncation) */
    kPXP_PsPixelFormatYUV2P422  = 0x18, /*!< 16-bit pixels (2-plane UV interleaved bytes) */
    kPXP_PsPixelFormatYUV2P420  = 0x19, /*!< 16-bit pixels (2-plane UV) */
    kPXP_PsPixelFormatYVU2P422  = 0x1A, /*!< 16-bit pixels (2-plane VU interleaved bytes) */
    kPXP_PsPixelFormatYVU2P420  = 0x1B, /*!< 16-bit pixels (2-plane VU) */
    kPXP_PsPixelFormatYVU422    = 0x1E, /*!< 16-bit pixels (3-plane) */
    kPXP_PsPixelFormatYVU420    = 0x1F, /*!< 16-bit pixels (3-plane) */
} pxp_ps_pixel_format_t;

/*! @brief PXP process surface buffer YUV format. */
typedef enum _pxp_ps_yuv_format
{
    kPXP_PsYUVFormatYUV = 0U, /*!< YUV format.   */
    kPXP_PsYUVFormatYCbCr,    /*!< YCbCr format. */
} pxp_ps_yuv_format_t;

/*! @brief PXP process surface buffer configuration. */
typedef struct _pxp_ps_buffer_config
{
    pxp_ps_pixel_format_t pixelFormat; /*!< PS buffer pixel format. */
    bool swapByte;                     /*!< For each 16 bit word, set true to swap the two bytes. */
    uint32_t bufferAddr;               /*!< Input buffer address for the first panel. */
    uint32_t bufferAddrU;              /*!< Input buffer address for the second panel. */
    uint32_t bufferAddrV;              /*!< Input buffer address for the third panel. */
    uint16_t pitchBytes;               /*!< Number of bytes between two vertically adjacent pixels. */
} pxp_ps_buffer_config_t;

/*! @brief PXP alpha surface buffer pixel format. */
typedef enum _pxp_as_pixel_format
{
    kPXP_AsPixelFormatARGB8888 = 0x0, /*!< 32-bit pixels with alpha. */
    kPXP_AsPixelFormatRGB888   = 0x4, /*!< 32-bit pixels without alpha (unpacked 24-bit format) */
    kPXP_AsPixelFormatARGB1555 = 0x8, /*!< 16-bit pixels with alpha. */
    kPXP_AsPixelFormatARGB4444 = 0x9, /*!< 16-bit pixels with alpha. */
    kPXP_AsPixelFormatRGB555   = 0xC, /*!< 16-bit pixels without alpha. */
    kPXP_AsPixelFormatRGB444   = 0xD, /*!< 16-bit pixels without alpha. */
    kPXP_AsPixelFormatRGB565   = 0xE, /*!< 16-bit pixels without alpha. */
} pxp_as_pixel_format_t;

/*! @brief PXP alphs surface buffer configuration. */
typedef struct _pxp_as_buffer_config
{
    pxp_as_pixel_format_t pixelFormat; /*!< AS buffer pixel format. */
    uint32_t bufferAddr;               /*!< Input buffer address. */
    uint16_t pitchBytes;               /*!< Number of bytes between two vertically adjacent pixels. */
} pxp_as_buffer_config_t;

/*!
 * @brief PXP alpha mode during blending.
 */
typedef enum _pxp_alpha_mode
{
    kPXP_AlphaEmbedded, /*!< The alpha surface pixel alpha value will be used for blend. */
    kPXP_AlphaOverride, /*!< The user defined alpha value will be used for blend directly. */
    kPXP_AlphaMultiply, /*!< The alpha surface pixel alpha value scaled the user defined
                             alpha value will be used for blend, for example, pixel alpha set
                             set to 200, user defined alpha set to 100, then the reault alpha
                             is 200 * 100 / 255. */
    kPXP_AlphaRop       /*!< Raster operation. */
} pxp_alpha_mode_t;

/*!
 * @brief PXP ROP mode during blending.
 *
 * Explanation:
 * - AS: Alpha surface
 * - PS: Process surface
 * - nAS: Alpha surface NOT value
 * - nPS: Process surface NOT value
 */
typedef enum _pxp_rop_mode
{
    kPXP_RopMaskAs     = 0x0, /*!< AS AND PS. */
    kPXP_RopMaskNotAs  = 0x1, /*!< nAS AND PS. */
    kPXP_RopMaskAsNot  = 0x2, /*!< AS AND nPS. */
    kPXP_RopMergeAs    = 0x3, /*!< AS OR PS. */
    kPXP_RopMergeNotAs = 0x4, /*!< nAS OR PS. */
    kPXP_RopMergeAsNot = 0x5, /*!< AS OR nPS. */
    kPXP_RopNotCopyAs  = 0x6, /*!< nAS. */
    kPXP_RopNot        = 0x7, /*!< nPS. */
    kPXP_RopNotMaskAs  = 0x8, /*!< AS NAND PS. */
    kPXP_RopNotMergeAs = 0x9, /*!< AS NOR PS. */
    kPXP_RopXorAs      = 0xA, /*!< AS XOR PS. */
    kPXP_RopNotXorAs   = 0xB  /*!< AS XNOR PS. */
} pxp_rop_mode_t;

/*!
 * @brief PXP alpha surface blending configuration.
 */
typedef struct _pxp_as_blend_config
{
    uint8_t alpha;    /*!< User defined alpha value, only used when @ref alphaMode is @ref kPXP_AlphaOverride or @ref
                         kPXP_AlphaRop. */
    bool invertAlpha; /*!< Set true to invert the alpha. */
    pxp_alpha_mode_t alphaMode; /*!< Alpha mode. */
    pxp_rop_mode_t ropMode;     /*!< ROP mode, only valid when @ref alphaMode is @ref kPXP_AlphaRop. */
} pxp_as_blend_config_t;

#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3
/*!
 * @brief PXP secondary alpha surface blending engine configuration.
 */
typedef struct _pxp_as_blend_secondary_config
{
    bool invertAlpha;       /*!< Set true to invert the alpha. */
    bool ropEnable;         /*!< Enable rop mode. */
    pxp_rop_mode_t ropMode; /*!< ROP mode, only valid when ropEnable is true. */
} pxp_as_blend_secondary_config_t;
#endif /* FSL_FEATURE_PXP_V3 */

/*! @brief PXP process block size. */
typedef enum _pxp_block_size
{
    kPXP_BlockSize8 = 0U, /*!< Process 8x8 pixel blocks. */
    kPXP_BlockSize16,     /*!< Process 16x16 pixel blocks. */
} pxp_block_size_t;

/*! @brief PXP CSC1 mode. */
typedef enum _pxp_csc1_mode
{
    kPXP_Csc1YUV2RGB = 0U, /*!< YUV to RGB. */
    kPXP_Csc1YCbCr2RGB,    /*!< YCbCr to RGB. */
} pxp_csc1_mode_t;

/*! @brief PXP CSC2 mode. */
typedef enum _pxp_csc2_mode
{
    kPXP_Csc2YUV2RGB = 0U, /*!< YUV to RGB. */
    kPXP_Csc2YCbCr2RGB,    /*!< YCbCr to RGB. */
    kPXP_Csc2RGB2YUV,      /*!< RGB to YUV. */
    kPXP_Csc2RGB2YCbCr,    /*!< RGB to YCbCr. */
} pxp_csc2_mode_t;

/*!
 * @brief PXP CSC2 configuration.
 *
 * Converting from YUV/YCbCr color spaces to the RGB color space uses the
 * following equation structure:
 *
 * R = A1(Y+D1) + A2(U+D2) + A3(V+D3)
 * G = B1(Y+D1) + B2(U+D2) + B3(V+D3)
 * B = C1(Y+D1) + C2(U+D2) + C3(V+D3)
 *
 * Converting from the RGB color space to YUV/YCbCr color spaces uses the
 * following equation structure:
 *
 * Y = A1*R + A2*G + A3*B + D1
 * U = B1*R + B2*G + B3*B + D2
 * V = C1*R + C2*G + C3*B + D3
 */
typedef struct _pxp_csc2_config
{
    pxp_csc2_mode_t mode; /*!< Convertion mode. */
    float A1;             /*!< A1. */
    float A2;             /*!< A2. */
    float A3;             /*!< A3. */
    float B1;             /*!< B1. */
    float B2;             /*!< B2. */
    float B3;             /*!< B3. */
    float C1;             /*!< C1. */
    float C2;             /*!< C2. */
    float C3;             /*!< C3. */
    int16_t D1;           /*!< D1. */
    int16_t D2;           /*!< D2. */
    int16_t D3;           /*!< D3. */
} pxp_csc2_config_t;

#if !(defined(FSL_FEATURE_PXP_HAS_NO_LUT) && FSL_FEATURE_PXP_HAS_NO_LUT)
/*! @brief PXP LUT lookup mode. */
typedef enum _pxp_lut_lookup_mode
{
    kPXP_LutCacheRGB565 = 0U, /*!< LUT ADDR = R[7:3],G[7:2],B[7:3]. Use all 16KB of LUT
                                   for indirect cached 128KB lookup. */
    kPXP_LutDirectY8,         /*!< LUT ADDR = 16'b0,Y[7:0]. Use the first 256 bytes of LUT.
                                   Only third data path byte is tranformed. */
    kPXP_LutDirectRGB444,     /*!< LUT ADDR = R[7:4],G[7:4],B[7:4]. Use one 8KB bank of LUT
                                   selected by @ref PXP_Select8kLutBank. */
    kPXP_LutDirectRGB454,     /*!< LUT ADDR = R[7:4],G[7:3],B[7:4]. Use all 16KB of LUT. */
} pxp_lut_lookup_mode_t;

/*! @brief PXP LUT output mode. */
typedef enum _pxp_lut_out_mode
{
    kPXP_LutOutY8 = 1U,     /*!< R/Y byte lane 2 lookup, bytes 1,0 bypassed. */
    kPXP_LutOutRGBW4444CFA, /*!< Byte lane 2 = CFA_Y8, byte lane 1,0 = RGBW4444. */
    kPXP_LutOutRGB888,      /*!< RGB565->RGB888 conversion for Gamma correction. */
} pxp_lut_out_mode_t;

/*! @brief PXP LUT 8K bank index used when lookup mode is @ref kPXP_LutDirectRGB444. */
typedef enum _pxp_lut_8k_bank
{
    kPXP_Lut8kBank0 = 0U, /*!< The first 8K bank used. */
    kPXP_Lut8kBank1,      /*!< The second 8K bank used. */
} pxp_lut_8k_bank_t;

/*! @brief PXP LUT configuration. */
typedef struct _pxp_lut_config
{
    pxp_lut_lookup_mode_t lookupMode; /*!< Look up mode. */
    pxp_lut_out_mode_t outMode;       /*!< Out mode. */
    uint32_t cfaValue;                /*!< The CFA value used when look up mode is @ref kPXP_LutOutRGBW4444CFA. */
} pxp_lut_config_t;
#endif /* FSL_FEATURE_PXP_HAS_NO_LUT */

/*! @brief PXP internal memory. */
typedef enum _pxp_ram
{
    kPXP_RamDither0Lut = 0U, /*!< Dither 0 LUT memory. */
    kPXP_RamDither1Lut = 3U, /*!< Dither 1 LUT memory. */
    kPXP_RamDither2Lut = 4U, /*!< Dither 2 LUT memory. */
#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3
    kPXP_RamDither0Err0 = 1U, /*!< Dither 0 ERR0 memory. */
    kPXP_RamDither0Err1 = 2U, /*!< Dither 0 ERR1 memory. */
    kPXP_RamAluA        = 5U, /*!< ALU A instr memory. */
    kPXP_RamAluB        = 6U, /*!< ALU B instr memory. */
    kPXP_WfeAFetch      = 7U, /*!< WFE-A fetch memory. */
    kPXP_WfeBFetch      = 8U, /*!< WFE-B fetch memory. */
#endif                        /* FSL_FEATURE_PXP_V3 */
} pxp_ram_t;

/*! @brief PXP dither mode. */
enum _pxp_dither_mode
{
    kPXP_DitherPassThrough    = 0U, /*!< Pass through, no dither. */
    kPXP_DitherFloydSteinberg = 1U, /*!< Floyd-Steinberg. For dither engine 0 only. */
    kPXP_DitherAtkinson       = 2U, /*!< Atkinson. For dither engine 0 only. */
    kPXP_DitherOrdered        = 3U, /*!< Ordered dither. */
    kPXP_DitherQuantOnly      = 4U, /*!< No dithering, only quantization. */
    kPXP_DitherSierra         = 5U, /*!< Sierra. For dither engine 0 only. */
};

/*! @brief PXP dither LUT mode. */
enum _pxp_dither_lut_mode
{
    kPXP_DitherLutOff = 0U,   /*!< The LUT memory is not used for LUT, could be used as ordered dither index matrix. */
    kPXP_DitherLutPreDither,  /*!< Use LUT at the pre-dither stage, The pre-dither LUT could only be used in Floyd mode
                                   or Atkinson mode, which are not supported by current PXP module. */
    kPXP_DitherLutPostDither, /*!< Use LUT at the post-dither stage. */
};

/*! @brief PXP dither matrix size. */
enum _pxp_dither_matrix_size
{
    kPXP_DitherMatrix4 = 0, /*!< The dither index matrix is 4x4. */
    kPXP_DitherMatrix8,     /*!< The dither index matrix is 8x8. */
    kPXP_DitherMatrix16,    /*!< The dither index matrix is 16x16. */
};

/*! @brief PXP dither final LUT data. */
typedef struct _pxp_dither_final_lut_data
{
    uint32_t data_3_0;   /*!< Data 3 to data 0. Data 0 is the least significant byte. */
    uint32_t data_7_4;   /*!< Data 7 to data 4. Data 4 is the least significant byte. */
    uint32_t data_11_8;  /*!< Data 11 to data 8. Data 8 is the least significant byte. */
    uint32_t data_15_12; /*!< Data 15 to data 12. Data 12 is the least significant byte. */
} pxp_dither_final_lut_data_t;

/*! @brief PXP dither configuration. */
typedef struct _pxp_dither_config
{
    uint32_t enableDither0 : 1;  /*!< Enable dither engine 0 or not, set 1 to enable, 0 to disable. */
    uint32_t enableDither1 : 1;  /*!< Enable dither engine 1 or not, set 1 to enable, 0 to disable. */
    uint32_t enableDither2 : 1;  /*!< Enable dither engine 2 or not, set 1 to enable, 0 to disable. */
    uint32_t ditherMode0 : 3;    /*!< Dither mode for dither engine 0. See @ref _pxp_dither_mode. */
    uint32_t ditherMode1 : 3;    /*!< Dither mode for dither engine 1. See @ref _pxp_dither_mode. */
    uint32_t ditherMode2 : 3;    /*!< Dither mode for dither engine 2. See @ref _pxp_dither_mode. */
    uint32_t quantBitNum : 3;    /*!< Number of bits quantize down to, the valid value is 1~7. */
    uint32_t lutMode : 2;        /*!< How to use the memory LUT, see @ref _pxp_dither_lut_mode. This must be set to @ref
                                    kPXP_DitherLutOff
                                      if any dither engine uses @ref kPXP_DitherOrdered mode. */
    uint32_t idxMatrixSize0 : 2; /*!< Size of index matrix used for dither for dither engine 0, see @ref
                                    _pxp_dither_matrix_size. */
    uint32_t idxMatrixSize1 : 2; /*!< Size of index matrix used for dither for dither engine 1, see @ref
                                    _pxp_dither_matrix_size. */
    uint32_t idxMatrixSize2 : 2; /*!< Size of index matrix used for dither for dither engine 2, see @ref
                                    _pxp_dither_matrix_size. */
    uint32_t enableFinalLut : 1; /*!< Enable the final LUT, set 1 to enable, 0 to disable. */
    uint32_t : 8;
} pxp_dither_config_t;

/*!
 * @brief Porter Duff factor mode.
 * @anchor pxp_porter_duff_factor_mode
 */
enum
{
    kPXP_PorterDuffFactorOne = 0U, /*!< Use 1. */
    kPXP_PorterDuffFactorZero,     /*!< Use 0. */
    kPXP_PorterDuffFactorStraight, /*!< Use straight alpha. */
    kPXP_PorterDuffFactorInversed, /*!< Use inversed alpha. */
};

/*!
 * @brief Porter Duff global alpha mode.
 * @anchor pxp_porter_duff_global_alpha_mode
 */
enum
{
    kPXP_PorterDuffGlobalAlpha = 0U, /*!< Use global alpha. */
    kPXP_PorterDuffLocalAlpha,       /*!< Use local alpha in each pixel. */
    kPXP_PorterDuffScaledAlpha,      /*!< Use global alpha * local alpha. */
};

/*!
 * @brief Porter Duff alpha mode.
 * @anchor pxp_porter_duff_alpha_mode
 */
enum
{
    kPXP_PorterDuffAlphaStraight = 0U, /*!< Use straight alpha, s0_alpha' = s0_alpha. */
    kPXP_PorterDuffAlphaInversed       /*!< Use inversed alpha, s0_alpha' = 0xFF - s0_alpha. */
};

/*!
 * @brief Porter Duff color mode.
 * @anchor pxp_porter_duff_color_mode
 */
enum
{
    kPXP_PorterDuffColorStraight  = 0, /*!< @deprecated Use kPXP_PorterDuffColorNoAlpha. */
    kPXP_PorterDuffColorInversed  = 1, /*!< @deprecated Use kPXP_PorterDuffColorWithAlpha. */
    kPXP_PorterDuffColorNoAlpha   = 0, /*!< s0_pixel' = s0_pixel. */
    kPXP_PorterDuffColorWithAlpha = 1, /*!< s0_pixel' = s0_pixel * s0_alpha". */
};

/*! @brief PXP Porter Duff configuration. */
typedef struct
{
    uint32_t enable : 1;             /*!< Enable or disable Porter Duff. */
    uint32_t srcFactorMode : 2;      /*!< Source layer (or AS, s1) factor mode, see @ref pxp_porter_duff_factor_mode. */
    uint32_t dstGlobalAlphaMode : 2; /*!< Destination layer (or PS, s0) global alpha mode, see
                                        @ref pxp_porter_duff_global_alpha_mode. */
    uint32_t dstAlphaMode : 1; /*!< Destination layer (or PS, s0) alpha mode, see @ref pxp_porter_duff_alpha_mode. */
    uint32_t dstColorMode : 1; /*!< Destination layer (or PS, s0) color mode, see @ref pxp_porter_duff_color_mode. */
    uint32_t : 1;
    uint32_t dstFactorMode : 2; /*!< Destination layer (or PS, s0) factor mode, see @ref pxp_porter_duff_factor_mode. */
    uint32_t srcGlobalAlphaMode : 2; /*!< Source layer (or AS, s1) global alpha mode, see
                                        @ref pxp_porter_duff_global_alpha_mode. */
    uint32_t srcAlphaMode : 1;       /*!< Source layer (or AS, s1) alpha mode, see @ref pxp_porter_duff_alpha_mode. */
    uint32_t srcColorMode : 1;       /*!< Source layer (or AS, s1) color mode, see @ref pxp_porter_duff_color_mode. */
    uint32_t : 2;
    uint32_t dstGlobalAlpha : 8; /*!< Destination layer (or PS, s0) global alpha value, 0~255. */
    uint32_t srcGlobalAlpha : 8; /*!< Source layer (or AS, s1) global alpha value, 0~255. */
} pxp_porter_duff_config_t;

/*! @brief PXP Porter Duff blend mode. Note: don't change the enum item value */
typedef enum _pxp_porter_duff_blend_mode
{
    kPXP_PorterDuffSrc = 0, /*!< Source Only */
    kPXP_PorterDuffAtop,    /*!< Source Atop */
    kPXP_PorterDuffOver,    /*!< Source Over */
    kPXP_PorterDuffIn,      /*!< Source In. */
    kPXP_PorterDuffOut,     /*!< Source Out. */
    kPXP_PorterDuffDst,     /*!< Destination Only. */
    kPXP_PorterDuffDstAtop, /*!< Destination Atop. */
    kPXP_PorterDuffDstOver, /*!< Destination Over. */
    kPXP_PorterDuffDstIn,   /*!< Destination In. */
    kPXP_PorterDuffDstOut,  /*!< Destination Out. */
    kPXP_PorterDuffXor,     /*!< XOR. */
    kPXP_PorterDuffClear,   /*!< Clear. */
    kPXP_PorterDuffMax,
} pxp_porter_duff_blend_mode_t;

/*! @brief PXP Porter Duff blend mode. Note: don't change the enum item value */
typedef struct _pxp_pic_copy_config
{
    uint32_t srcPicBaseAddr;           /*!< Source picture base address. */
    uint16_t srcPitchBytes;            /*!< Pitch of the source buffer. */
    uint16_t srcOffsetX;               /*!< Copy position in source picture. */
    uint16_t srcOffsetY;               /*!< Copy position in source picture. */
    uint32_t destPicBaseAddr;          /*!< Destination picture base address. */
    uint16_t destPitchBytes;           /*!< Pitch of the destination buffer. */
    uint16_t destOffsetX;              /*!< Copy position in destination picture. */
    uint16_t destOffsetY;              /*!< Copy position in destination picture. */
    uint16_t width;                    /*!< Pixel number each line to copy. */
    uint16_t height;                   /*!< Lines to copy. */
    pxp_as_pixel_format_t pixelFormat; /*!< Buffer pixel format. */
} pxp_pic_copy_config_t;

#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3

/*!
 * @brief PXP process engine enumeration
 */
typedef enum _pxp_process_engine_name
{
    kPXP_PsAsOutEngine         = PXP_CTRL_ENABLE_PS_AS_OUT_MASK,
    kPXP_DitherEngine          = PXP_CTRL_ENABLE_DITHER_MASK,
    kPXP_WfeaEngine            = PXP_CTRL_ENABLE_WFE_A_MASK,
    kPXP_WfebEngine            = PXP_CTRL_ENABLE_WFE_B_MASK,
    kPXP_InputFetchStoreEngine = PXP_CTRL_ENABLE_INPUT_FETCH_STORE_MASK,
    kPXP_Alpha1Engine          = PXP_CTRL_ENABLE_ALPHA_B_MASK,
    kPXP_Csc2Engine            = PXP_CTRL_ENABLE_CSC2_MASK,
    kPXP_LutEngine             = PXP_CTRL_ENABLE_LUT_MASK,
    kPXP_Rotate0Engine         = PXP_CTRL_ENABLE_ROTATE0_MASK,
    kPXP_Rotate1Engine         = PXP_CTRL_ENABLE_ROTATE1_MASK,
} pxp_process_engine_name_t;

/* Fetch engine configuration. */
/*!
 * @brief PXP fetch engine enumeration
 *
 * There are actually 4 fetch engine implemented, the others are WFE-A fetch engine and WFE-B fetch engine,
 * whose registers are reserved from developer.
 */
typedef enum _pxp_fetch_engine_name
{
    kPXP_FetchInput,
    kPXP_FetchDither,
} pxp_fetch_engine_name_t;

/*! @brief PXP fetch engine interface mode with the upstream store engine. */
typedef enum _pxp_fetch_interface_mode
{
    kPXP_FetchModeNormal    = 0U,
    kPXP_FetchModeHandshake = 0x1U,
    kPXP_FetchModeBypass    = 0x2U,
} pxp_fetch_interface_mode_t;

/*! @brief PXP fetch/store engine burst length for scanline mode. */
typedef enum _pxp_scanline_burst
{
    kPXP_Scanline8bytes,
    kPXP_Scanline16bytes,
    kPXP_Scanline32bytes,
    kPXP_Scanline64bytes,
} pxp_scanline_burst_t;

/*! @brief PXP fetch engine block configuration. */
typedef struct _pxp_block_format_config
{
    bool
        enableblock;  /*!< Enable to use block mode instead of scanline mode. Note: 1.Make sure to enable if rotate or
                         flip mode is enabled. 2.Block mode cannot work on 64bpp data stream where activeBits = 64. 3. If
                         LUT processing is in the path between the fetch and store engind, block mode must be enabled. */
    bool blockSize16; /*!< Enable to use 16*16 block, otherwise it will be 8*8 block. */
    pxp_scanline_burst_t burstLength; /*!< When using scanline mode, configure this for burst length. */
} pxp_block_config_t;

/*!
 * @brief PXP fetch/store engine input/output active bits configuration.
 *
 * Since fetch engine is 64-bit input and 32-bit output per channel, need to configure both channels to use 64-bit input
 * mode. And expand configuration will have no effect.
 */
typedef enum _pxp_activeBits
{
    kPXP_Active8Bits  = 0x0,
    kPXP_Active16Bits = 0x1,
    kPXP_Active32Bits = 0x2,
    kPXP_Active64Bits = 0x3,
} pxp_active_bits_t;

/*! @brief PXP fetch engine output word order when using 2 channels for 64-bit mode. */
typedef enum _pxp_fetch_output_word_order
{
    kPXP_FetchOutputChannel1channel0 = 0x0, /*!< In 64bit mode, channel 1 output high byte. */
    kPXP_FetchOutputChannel0channel1 = 0x1, /*!< In 64bit mode, channel 0 output high byte. */
} pxp_fetch_output_word_order_t;

/*!
 * @brief PXP fetch engine shift component configuration.
 *
 * Fetch engine can divded each word into 4 components and shift them.
 */
typedef struct _pxp_fetch_shift_component
{
    uint8_t offset;
    uint8_t width;
} pxp_fetch_shift_component_t;

/*!
 * @brief PXP fetch engine shift configuration.
 *
 * Fetch engine can divded each word into 4 components and shift them.
 * For example, to change YUV444 to YVU444, U and V positions need to be shifted: OFFSET0=8, OFFSET1=0, OFFSET2=16,
 * OFFSET3=24, WIDTH0/1/2/3=8
 */
typedef struct _pxp_fetch_shift_config
{
    bool shiftBypass; /* Bypass the shift */
    pxp_fetch_shift_component_t component0;
    pxp_fetch_shift_component_t component1;
    pxp_fetch_shift_component_t component2;
    pxp_fetch_shift_component_t component3;
} pxp_fetch_shift_config_t;

/*! @brief PXP fetch engine input pixel format. */
typedef enum _pxp_fetch_pixel_format
{
    kPXP_FetchFormatRGB565     = 0x0,
    kPXP_FetchFormatRGB555     = 0x1,
    kPXP_FetchFormatARGB1555   = 0x2,
    kPXP_FetchFormatRGB444     = 0x3,
    kPXP_FetchFormatARGB4444   = 0x4,
    kPXP_FetchFormatYUYVorYVYU = 0x5,
    kPXP_FetchFormatUYVYorVYUY = 0x6,
    kPXP_FetchFormatYUV422_2P  = 0x7,
} pxp_fetch_pixel_format_t;

/*! @brief PXP fetch engine configuration for one of the channel. */
typedef struct _pxp_fetch_engine_config
{
    bool channelEnable; /*!< Enable channel. */
    /* Address configuration */
    uint32_t inputBaseAddr0; /*!< The input base address. Used for Y plane input when pixel format is YUV422_2p. */
    uint32_t inputBaseAddr1; /*!< Must configure this for UV plane when input pixel format is YUV422_2p. */
    /* Size configuration */
    uint16_t totalHeight; /*!< Total height for the actual fetch size. */
    uint16_t totalWidth;  /*!< Total width for the actual fetch size. */
    uint16_t pitchBytes;  /*!< Channel input pitch */
    uint16_t
        ulcX; /*!< X coordinate of upper left coordinate in pixels of the active surface of the total input memory */
    uint16_t
        ulcY; /*!< Y coordinate of upper left coordinate in pixels of the active surface of the total input memory */
    uint16_t
        lrcX; /*!< X coordinate of Lower right coordinate in pixels of the active surface of the total input memory */
    uint16_t
        lrcY; /*!< Y coordinate of Lower right coordinate in pixels of the active surface of the total input memory */
    /* Interface configuration */
    pxp_fetch_interface_mode_t interface; /*!< Interface mode, normal/bypass/handshake */
    /* Pixel configuration */
    pxp_active_bits_t activeBits;         /*!< Input active bits. */
    pxp_fetch_pixel_format_t pixelFormat; /*!< Input pixel fetch format */
    bool expandEnable; /*!< If enabled, input pixel will be expanded to ARGB8888, RGB888 or YUV444 of 32-bit format at
                          the output. */
    /* Fetch format configuration */
    pxp_flip_mode_t flipMode;         /*!< Flip the fetched input. */
    pxp_rotate_degree_t rotateDegree; /*!< Rotate the fetched input. */
    pxp_block_config_t
        fetchFormat; /*!< Block mode configuration. Make sure to enable block if rotate or flip mode is enabled. */
    /* Output configuration. */
    pxp_fetch_shift_config_t shiftConfig;    /*!< Shift operation configuration. */
    pxp_fetch_output_word_order_t wordOrder; /*!< Output word order when using 2 channels for 64-bit mode. */
} pxp_fetch_engine_config_t;

/* Store engine configuration. */

/*!
 * @brief PXP store engine enumeration
 *
 * There are actually 4 store engine implemented, the others are WFE-A store engine and WFE-B store engine,
 * whose registers are reserved from developer.
 */
typedef enum _pxp_store_engine_name
{
    kPXP_StoreInput,
    kPXP_StoreDither,
} pxp_store_engine_name_t;

/*! @brief PXP store engine interface mode with the downstream fetch engine. */
typedef enum _pxp_store_interface_mode
{
    kPXP_StoreModeBypass    = 0x20U,
    kPXP_StoreModeNormal    = 0x40U,
    kPXP_StoreModeHandshake = 0x43U,
    kPXP_StoreModeDual      = 0x60U, /*!< Store engine outputs data directly to downstream fetch engine(Bypass) but also
                                        storing it to memory at the same time. */
} pxp_store_interface_mode_t;

/*! @brief PXP store engine YUV output mode. */
typedef enum _pxp_store_yuv_mode
{
    kPXP_StoreYUVDisable = 0U, /*!< Do not output YUV pixel format. */
    kPXP_StoreYUVPlane1 =
        0x1U, /*!< Use channel to output YUV422_1p pixel format, need to use shift operation to make sure each pixel
                 component in its proper position: 64-bits of pixel data format and each 32 bits as {Y0, U0, Y1, V0}. */
    kPXP_StoreYUVPlane2 =
        0x2U, /*!< Use channel to output YUV422_2p pixel format, need to use shift operation to make sure each pixel
                 component in its proper position: channel 0 {Y0,Y1}, channel 1 {U0,V0}. */
} pxp_store_yuv_mode_t;

/*! @brief Shift configuration for PXP store engine. */
typedef struct _pxp_store_shift_config
{
    /* Data/Flag shift */
    bool shiftBypass;         /*!< Bypass the data shift */
    uint64_t *pDataShiftMask; /*!< Pointer to mask0~mask7 to mask the 64-bit of output data, data is masked first then
                                 shifted according to width. */
    uint8_t *pDataShiftWidth; /*!< Pointer to width0~width7. Bit 7 is for shifted direction, 0 to right. Bit0~5 is for
                                 shift width. */
    uint8_t *pFlagShiftMask;  /*!< Pointer to mask0~mask7 to mask the 8-bit of output flag, flag is masked first then
                                 shifted according to width. */
    uint8_t *pFlagShiftWidth; /*!< Pointer to width0~width7. Bit 6 is for shifted direction, 0 to right. Bit0~5 is for
                                 shift width. */
} pxp_store_shift_config_t;

/*! @brief PXP store engine configuration for one of the channel. */
typedef struct _pxp_store_engine_config
{
    bool channelEnable; /*!< Enable channel. */
    /* Address configuration */
    uint32_t outputBaseAddr0; /*!< The channel 0 output address if using 2 channels. If using 1 channel(must be channel
                                 0) and YUV422_2p output format, is for Y plane address. */
    uint32_t outputBaseAddr1; /*!< The channel 1 output address if using 2 channels. If using 1 channel(must be channel
                                 0) and YUV422_2p output format, is for UV plane address. */
    /* Size configuration */
    uint16_t totalHeight; /*!< Total height for the actual store size. */
    uint16_t totalWidth;  /*!< Total width for the actual store size. */
    uint16_t pitchBytes;  /*!< Channel input pitch */
    /* Interface configuration */
    pxp_store_interface_mode_t interface; /*!< Interface mode, normal/bypass/handshake/dual. Make sure 2 channels use
                                               the same mode if both enabled. */
    /* pxp_store_handshake_array_t arraySize; !< If interfase mode is handshake, need to configure the array size. When
                                              block is disabled, the scanline can only be 1. TODO no need now. */
    /* Pixel configuration */
    pxp_active_bits_t activeBits; /*!< Output active bits. */
    pxp_store_yuv_mode_t yuvMode; /*!< Whether to output YUV pixel format. */
    /* Fixed data configuration, only apply for channel 0. */
    bool useFixedData; /*!< Whether to use fixed value for the output data. Can be used to write fixed value to specific
                          memory location for memory initialization. */
    uint32_t fixedData; /*!< The value of the fixed data. */
    /* Data packing */
    bool packInSelect; /*!< When enabled, channel 0 will select low 32 bit shift out data to pack while channel i select
                          high 32 bit, otherwise all 64bit of data will be selected. */
    /* Data store format */
    pxp_block_config_t storeFormat;       /*!< The format to store data, block or otherwise. */
    pxp_store_shift_config_t shiftConfig; /*!< Shift operation configuration. */
} pxp_store_engine_config_t;

/* Pre-dither CFA engine configuration */

/*! @brief PXP pre-dither CFA engine input pixel format. */
typedef enum _pxp_cfa_input_format
{
    kPXP_CfaRGB888,
    kPXP_CfaRGB444,
} pxp_cfa_input_format_t;

/*! @brief PXP pre-dither CFA engine configuration. */
typedef struct _pxp_cfa_config
{
    bool bypass;                          /*!< Bypass the CFA process */
    pxp_cfa_input_format_t pixelInFormat; /*!< The pixel input format for CFA. */
    uint8_t arrayWidth;                   /*!< CFA array vertical size in pixels, min 3 max 15. */
    uint8_t arrayHeight;                  /*!< CFA array horizontal size in pixels, min 3 max 15. */
    uint16_t totalHeight; /*!< Total height for the buffer size, make sure it is aligned with the dither fetch engine
                             and dither engine. */
    uint16_t totalWidth;  /*!< Total width for the buffer size, make sure it is aligned with the dither fetch engine and
                             dither engine. */
    uint32_t *cfaValue; /*!< Pointer to the value for the CFA array. 2-bit per component: 00-R,01-G,10-B,11-W. For a 4x4
                           array, 32 bits are need. */
} pxp_cfa_config_t;

/* Histogram configuration and status */

/*! @brief PXP histogram mask condition. */
typedef enum _pxp_histogram_mask_condition
{
    kPXP_HistogramMaskEqual    = 0x0U, /*!< Value that equal to value0 will pass the mask operation. */
    kPXP_HistogramMaskNotequal = 0x1U, /*!< Value that not equal to value0 will pass the mask operation. */
    kPXP_HistogramMaskIn  = 0x2U, /*!< Value that within the range of value0-value1 will pass the mask operation. */
    kPXP_HistogramMaskOut = 0x3U, /*!< Value that without the range of value0-value1 will pass the mask operation. */
} pxp_histogram_mask_condition_t;

/*! @brief PXP Histogram configuration. */
typedef struct _pxp_histogram_config
{
    bool enable;            /*!< Enable histogram process. */
    uint8_t *pParamValue;   /*!< Pointer to the 62(2+4+8+16+32) byte of param value for 2-level, 4-level.....32-level
                               parameters. Only low 5-bit of each byte is valid. */
    uint8_t lutValueOffset; /*!< The starting bit position of the LUT value. */
    uint8_t lutValueWidth;  /*!< The bit width of the LUT value, should be no more than 6 bits since only 63 LUTs are
                               supported. */
    /* Mask configuration */
    bool enableMask;    /*!< Enable mask operation. */
    uint8_t maskValue0; /*!< Value 0 for the condition judgement. */
    uint8_t maskValue1; /*!< Value 1 for the condition judgement. */
    uint8_t maskOffset; /*!< The starting bit position of the field to be checked against mask condition. */
    uint8_t maskWidth;  /*!< The width of the field to be checked against mask condition. */
    pxp_histogram_mask_condition_t condition; /*!< The mask condition. */
    /* Size configuration */
    uint16_t totalHeight; /*!< Total height for the buffer size, make sure it is aligned with the output of legacy flow
                             or the WFE-A/B engine. */
    uint16_t totalWidth; /*!< Total width for the buffer size, make sure it is aligned with the output of legacy flow or
                            the WFE-A/B engine. */
} pxp_histogram_config_t;

/*! @brief PXP Histogram mask result. */
typedef struct _pxp_histogram_mask_result
{
    uint32_t pixelCount; /*!< The total count of the pixels that pass the mask(collided pixels). */
    uint32_t minX;       /*!< The x offset of the ULC of the minimal histogram that covers all passed pixels. */
    uint32_t minY;       /*!< The y offset of the ULC of the minimal histogram that covers all passed pixels. */
    uint32_t maxX;       /*!< The x offset of the LRC of the minimal histogram that covers all passed pixels. */
    uint32_t maxY;       /*!< The y offset of the LRC of the minimal histogram that covers all passed pixels. */
    uint64_t lutlist; /*!< The 64-bit LUT list of collided pixels, if pixel of LUT17 is collided, bit17 in the list is
                         set. */
} pxp_histogram_mask_result_t;

/*! @brief PXP Histogram operation result flags. */
enum _pxp_histgram_flags
{
    kPXP_Histogram2levelMatch  = 1 << 0U, /* Bitmap pixels are fully contained within the HIST2 histogram. */
    kPXP_Histogram4levelMatch  = 1 << 1U, /* Bitmap pixels are fully contained within the HIST4 histogram. */
    kPXP_Histogram8levelMatch  = 1 << 2U, /* Bitmap pixels are fully contained within the HIST8 histogram. */
    kPXP_Histogram16levelMatch = 1 << 3U, /* Bitmap pixels are fully contained within the HIST16 histogram. */
    kPXP_Histogram32levelMatch = 1 << 4U, /* Bitmap pixels are fully contained within the HIST32 histogram. */
};

/*! @brief PXP WFE-A engine configuration. */
typedef struct _pxp_wfea_engine_config
{
    uint32_t y4Addr;       /*!< Address for Y4 buffer. */
    uint32_t y4cAddr;      /*!< Address for Y4C buffer, {Y4[3:0],3'b000,collision}, 8bpp. */
    uint32_t wbAddr;       /*!< Address for EPDC working buffer. */
    uint16_t updateWidth;  /*!< Width of the update area. */
    uint16_t updateHeight; /*!< Height of the update area. */
    uint16_t updatePitch;  /*!< Pitch of the update area. */
    uint16_t ulcX;         /*!< X coordinate of upper left coordinate of the total input memory */
    uint16_t ulcY;         /*!< Y coordinate of upper left coordinate of the total input memory */
    uint16_t resX;         /*!< Horizontal resolution in pixels. */
    uint8_t lutNum;        /*!< The EPDC LUT number for the update. */
    bool fullUpdateEnable; /*!< Enable full update. */
    bool alphaEnable; /*!< Enable alpha field, upd is {Y4[3:0],3'b000,alpha} format, otherwise its {Y4[3:0],4'b0000}. */
    bool detectionOnly; /*!< Detection only, do not write working buffer. */
} pxp_wfea_engine_config_t;

#endif /* FSL_FEATURE_PXP_V3 */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Initialize the PXP.
 *
 * This function enables the PXP peripheral clock, and resets the PXP registers
 * to default status.
 *
 * @param base PXP peripheral base address.
 */
void PXP_Init(PXP_Type *base);

/*!
 * @brief De-initialize the PXP.
 *
 * This function disables the PXP peripheral clock.
 *
 * @param base PXP peripheral base address.
 */
void PXP_Deinit(PXP_Type *base);

/*!
 * @brief Reset the PXP.
 *
 * This function resets the PXP peripheral registers to default status.
 *
 * @param base PXP peripheral base address.
 */
void PXP_Reset(PXP_Type *base);
/* @} */

/*!
 * @name Global operations
 * @{
 */

/*!
 * @brief Start process.
 *
 * Start PXP process using current configuration.
 *
 * @param base PXP peripheral base address.
 */
static inline void PXP_Start(PXP_Type *base)
{
    base->CTRL_SET = PXP_CTRL_ENABLE_MASK;
}

/*!
 * @brief Enable or disable LCD hand shake.
 *
 * @param base PXP peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void PXP_EnableLcdHandShake(PXP_Type *base, bool enable)
{
#if defined(PXP_CTRL_ENABLE_LCD_HANDSHAKE_MASK)
    if (enable)
    {
        base->CTRL_SET = PXP_CTRL_ENABLE_LCD_HANDSHAKE_MASK;
    }
    else
    {
        base->CTRL_CLR = PXP_CTRL_ENABLE_LCD_HANDSHAKE_MASK;
    }
#else
    if (enable)
    {
        base->CTRL_SET = PXP_CTRL_ENABLE_LCD0_HANDSHAKE_MASK;
    }
    else
    {
        base->CTRL_CLR = PXP_CTRL_ENABLE_LCD0_HANDSHAKE_MASK;
    }
#endif
}

#if (defined(FSL_FEATURE_PXP_HAS_EN_REPEAT) && FSL_FEATURE_PXP_HAS_EN_REPEAT)
/*!
 * @brief Enable or disable continous run.
 *
 * If continous run not enabled, @ref PXP_Start starts the PXP process. When completed,
 * PXP enters idle mode and flag @ref kPXP_CompleteFlag asserts.
 *
 * If continous run enabled, the PXP will repeat based on the current configuration register
 * settings.
 *
 * @param base PXP peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void PXP_EnableContinousRun(PXP_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL_SET = PXP_CTRL_EN_REPEAT_MASK;
    }
    else
    {
        base->CTRL_CLR = PXP_CTRL_EN_REPEAT_MASK;
    }
}
#endif /* FSL_FEATURE_PXP_HAS_EN_REPEAT */

/*!
 * @brief Set the PXP processing block size
 *
 * This function chooses the pixel block size that PXP using during process.
 * Larger block size means better performace, but be careful that when PXP is
 * rotating, the output must be divisible by the block size selected.
 *
 * @param base PXP peripheral base address.
 * @param size The pixel block size.
 */
static inline void PXP_SetProcessBlockSize(PXP_Type *base, pxp_block_size_t size)
{
    base->CTRL = (base->CTRL & ~PXP_CTRL_BLOCK_SIZE_MASK) | PXP_CTRL_BLOCK_SIZE(size);
}

#if PXP_USE_PATH
/*!
 * @brief Sets the path for one of the MUX
 *
 * @param base PXP peripheral base address.
 * @param path the path configuration for one of the mux.
 */
void PXP_SetPath(PXP_Type *base, pxp_path_t path);
#endif /* PXP_USE_PATH */

#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3
/*!
 * @brief Enables or disables PXP engines in the process flow.
 *
 * @param base PXP peripheral base address.
 * @param mask The engines to enable. Logical OR of @ref pxp_process_engine_name_t.
 * @param enable true to enable, false to disable.
 */
static inline void PXP_EnableProcessEngine(PXP_Type *base, uint32_t mask, bool enable)
{
    mask &= 0xF3F0000UL;

    if (enable)
    {
        base->CTRL_SET = mask;
    }
    else
    {
        base->CTRL_CLR = mask;
    }
}
#endif /* FSL_FEATURE_PXP_V3 */

/* @} */

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets PXP status flags.
 *
 * This function gets all PXP status flags. The flags are returned as the logical
 * OR value of the enumerators @ref _pxp_flags. To check a specific status,
 * compare the return value with enumerators in @ref _pxp_flags.
 * For example, to check whether the PXP has completed process, use like this:
 * @code
       if (kPXP_CompleteFlag & PXP_GetStatusFlags(PXP))
       {
           ...
       }
   @endcode
 *
 * @param base PXP peripheral base address.
 * @return PXP status flags which are OR'ed by the enumerators in the _pxp_flags.
 */
static inline uint32_t PXP_GetStatusFlags(PXP_Type *base)
{
#if defined(PXP_STAT_AXI_READ_ERROR_1_MASK)
    uint32_t status = base->STAT & (PXP_STAT_NEXT_IRQ_MASK | PXP_STAT_IRQ0_MASK | PXP_STAT_AXI_READ_ERROR_0_MASK |
                                    PXP_STAT_AXI_WRITE_ERROR_0_MASK | PXP_STAT_AXI_READ_ERROR_1_MASK |
                                    PXP_STAT_AXI_WRITE_ERROR_1_MASK);
#else
    uint32_t status = base->STAT & (PXP_STAT_NEXT_IRQ_MASK | PXP_STAT_IRQ0_MASK | PXP_STAT_AXI_READ_ERROR_0_MASK |
                                    PXP_STAT_AXI_WRITE_ERROR_0_MASK);
#endif
#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3
    status |= (base->IRQ >> 16U | base->IRQ << 16U);
#endif /* FSL_FEATURE_PXP_V3 */
    return status;
}

/*!
 * @brief Clears status flags with the provided mask.
 *
 * This function clears PXP status flags with a provided mask.
 *
 * @param base PXP peripheral base address.
 * @param statusMask The status flags to be cleared; it is logical OR value of @ref _pxp_flags.
 */
static inline void PXP_ClearStatusFlags(PXP_Type *base, uint32_t statusMask)
{
    base->STAT_CLR = statusMask;
#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3
    statusMask &= 0xFFFF8000UL;
    base->IRQ_CLR = (statusMask >> 16U | statusMask << 16U);
#endif /* FSL_FEATURE_PXP_V3 */
}

/*!
 * @brief Gets the AXI ID of the failing bus operation.
 *
 * @param base PXP peripheral base address.
 * @param axiIndex Whitch AXI to get
 *        - 0: AXI0
 *        - 1: AXI1
 * @return The AXI ID of the failing bus operation.
 */
static inline uint8_t PXP_GetAxiErrorId(PXP_Type *base, uint8_t axiIndex)
{
#if defined(PXP_STAT_AXI_ERROR_ID_1_MASK)
    if (0U == axiIndex)
    {
        return (uint8_t)((base->STAT & PXP_STAT_AXI_ERROR_ID_0_MASK) >> PXP_STAT_AXI_ERROR_ID_0_SHIFT);
    }
    else
    {
        return (uint8_t)((base->STAT & PXP_STAT_AXI_ERROR_ID_1_MASK) >> PXP_STAT_AXI_ERROR_ID_1_SHIFT);
    }
#else
    return (uint8_t)((base->STAT & PXP_STAT_AXI_ERROR_ID_MASK) >> PXP_STAT_AXI_ERROR_ID_SHIFT);
#endif
}

/* @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables PXP interrupts according to the provided mask.
 *
 * This function enables the PXP interrupts according to the provided mask. The mask
 * is a logical OR of enumeration members. See @ref _pxp_interrupt_enable.
 * For example, to enable PXP process complete interrupt and command loaded
 * interrupt, do the following.
 * @code
    PXP_EnableInterrupts(PXP, kPXP_CommandLoadInterruptEnable | kPXP_CompleteInterruptEnable);
   @endcode
 *
 * @param base PXP peripheral base address.
 * @param mask The interrupts to enable. Logical OR of @ref _pxp_interrupt_enable.
 */
static inline void PXP_EnableInterrupts(PXP_Type *base, uint32_t mask)
{
    base->CTRL_SET = (mask & 0xEUL);
#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3
    mask &= 0xFFFF8000UL;
    base->IRQ_MASK_SET = (mask >> 16U | mask << 16U);
#endif /* FSL_FEATURE_PXP_V3 */
}

/*!
 * @brief Disables PXP interrupts according to the provided mask.
 *
 * This function disables the PXP interrupts according to the provided mask. The mask
 * is a logical OR of enumeration members. See @ref _pxp_interrupt_enable.
 *
 * @param base PXP peripheral base address.
 * @param mask The interrupts to disable. Logical OR of @ref _pxp_interrupt_enable.
 */
static inline void PXP_DisableInterrupts(PXP_Type *base, uint32_t mask)
{
    base->CTRL_CLR = (mask & 0xEUL);
#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3
    mask &= 0xFFFF8000UL;
    base->IRQ_MASK_CLR = (mask >> 16U | mask << 16U);
#endif /* FSL_FEATURE_PXP_V3 */
}

/* @} */

/*!
 * @name Alpha surface
 * @{
 */

/*!
 * @brief Set the alpha surface input buffer configuration.
 *
 * @param base PXP peripheral base address.
 * @param config Pointer to the configuration.
 */
void PXP_SetAlphaSurfaceBufferConfig(PXP_Type *base, const pxp_as_buffer_config_t *config);

/*!
 * @brief Set the alpha surface blending configuration.
 *
 * @param base PXP peripheral base address.
 * @param config Pointer to the configuration structure.
 */
void PXP_SetAlphaSurfaceBlendConfig(PXP_Type *base, const pxp_as_blend_config_t *config);

#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3
/*!
 * @brief Set the alpha surface blending configuration for the secondary engine.
 *
 * @param base PXP peripheral base address.
 * @param config Pointer to the configuration structure.
 */
void PXP_SetAlphaSurfaceBlendSecondaryConfig(PXP_Type *base, const pxp_as_blend_secondary_config_t *config);

/*!
 * @brief Set the alpha surface overlay color key.
 *
 * If a pixel in the current overlay image with a color that falls in the range
 * from the @p colorKeyLow to @p colorKeyHigh range, it will use the process surface
 * pixel value for that location. If no PS image is present or if the PS image also
 * matches its colorkey range, the PS background color is used.
 *
 * @param base PXP peripheral base address.
 * @param num instance number. 0 for alpha engine A, 1 for alpha engine B.
 * @param colorKeyLow Color key low range.
 * @param colorKeyHigh Color key high range.
 *
 * @note Colorkey operations are higher priority than alpha or ROP operations
 */
void PXP_SetAlphaSurfaceOverlayColorKey(PXP_Type *base, uint8_t num, uint32_t colorKeyLow, uint32_t colorKeyHigh);

/*!
 * @brief Enable or disable the alpha surface color key.
 *
 * @param base PXP peripheral base address.
 * @param num instance number. 0 for alpha engine A, 1 for alpha engine B.
 * @param enable True to enable, false to disable.
 */
static inline void PXP_EnableAlphaSurfaceOverlayColorKey(PXP_Type *base, uint32_t num, bool enable)
{
    switch (num)
    {
        case 0:
            base->AS_CTRL =
                (base->AS_CTRL & ~PXP_AS_CTRL_ENABLE_COLORKEY_MASK) | PXP_AS_CTRL_ENABLE_COLORKEY((uint32_t)enable);
            break;

        case 1:
            base->ALPHA_B_CTRL_1 = (base->ALPHA_B_CTRL_1 & ~PXP_ALPHA_B_CTRL_1_OL_CLRKEY_ENABLE_MASK) |
                                   PXP_ALPHA_B_CTRL_1_OL_CLRKEY_ENABLE((uint32_t)enable);
            break;

        default:
            /* Only 2 alpha process engine instances are supported. */
            assert(false);
            break;
    }
}
#else
/*!
 * @brief Set the alpha surface overlay color key.
 *
 * If a pixel in the current overlay image with a color that falls in the range
 * from the p colorKeyLow to p colorKeyHigh range, it will use the process surface
 * pixel value for that location. If no PS image is present or if the PS image also
 * matches its colorkey range, the PS background color is used.
 *
 * @param base PXP peripheral base address.
 * @param colorKeyLow Color key low range.
 * @param colorKeyHigh Color key high range.
 *
 * @note Colorkey operations are higher priority than alpha or ROP operations
 */
void PXP_SetAlphaSurfaceOverlayColorKey(PXP_Type *base, uint32_t colorKeyLow, uint32_t colorKeyHigh);

/*!
 * @brief Enable or disable the alpha surface color key.
 *
 * @param base PXP peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void PXP_EnableAlphaSurfaceOverlayColorKey(PXP_Type *base, bool enable)
{
    if (enable)
    {
        base->AS_CTRL |= PXP_AS_CTRL_ENABLE_COLORKEY_MASK;
    }
    else
    {
        base->AS_CTRL &= ~PXP_AS_CTRL_ENABLE_COLORKEY_MASK;
    }
}
#endif /* FSL_FEATURE_PXP_V3 */

/*!
 * @brief Set the alpha surface position in output buffer.
 *
 * @param base PXP peripheral base address.
 * @param upperLeftX X of the upper left corner.
 * @param upperLeftY Y of the upper left corner.
 * @param lowerRightX X of the lower right corner.
 * @param lowerRightY Y of the lower right corner.
 */
void PXP_SetAlphaSurfacePosition(
    PXP_Type *base, uint16_t upperLeftX, uint16_t upperLeftY, uint16_t lowerRightX, uint16_t lowerRightY);
/* @} */

/*!
 * @name Process surface
 * @{
 */
#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3
/*!
 * @brief Set the back ground color of PS.
 *
 * @param base PXP peripheral base address.
 * @param num instance number. 0 for alpha engine A, 1 for alpha engine B.
 * @param backGroundColor Pixel value of the background color.
 */
static inline void PXP_SetProcessSurfaceBackGroundColor(PXP_Type *base, uint8_t num, uint32_t backGroundColor)
{
    switch (num)
    {
        case 0:
            base->PS_BACKGROUND_0 = backGroundColor;
            break;

        case 1:
            base->PS_BACKGROUND_1 = backGroundColor;
            break;

        default:
            /* Only 2 alpha process engine instances are supported. */
            assert(false);
            break;
    }
}
#else
/*!
 * @brief Set the back ground color of PS.
 *
 * @param base PXP peripheral base address.
 * @param backGroundColor Pixel value of the background color.
 */
static inline void PXP_SetProcessSurfaceBackGroundColor(PXP_Type *base, uint32_t backGroundColor)
{
#if defined(PXP_PS_BACKGROUND_0_COLOR_MASK)
    base->PS_BACKGROUND_0 = backGroundColor;
#else
    base->PS_BACKGROUND = backGroundColor;
#endif
}
#endif /* FSL_FEATURE_PXP_V3 */

/*!
 * @brief Set the process surface input buffer configuration.
 *
 * @param base PXP peripheral base address.
 * @param config Pointer to the configuration.
 */
void PXP_SetProcessSurfaceBufferConfig(PXP_Type *base, const pxp_ps_buffer_config_t *config);

/*!
 * @brief Set the process surface scaler configuration.
 *
 * The valid down scale fact is 1/(2^12) ~ 16.
 *
 * @param base PXP peripheral base address.
 * @param inputWidth Input image width.
 * @param inputHeight Input image height.
 * @param outputWidth Output image width.
 * @param outputHeight Output image height.
 */
void PXP_SetProcessSurfaceScaler(
    PXP_Type *base, uint16_t inputWidth, uint16_t inputHeight, uint16_t outputWidth, uint16_t outputHeight);

/*!
 * @brief Set the process surface position in output buffer.
 *
 * @param base PXP peripheral base address.
 * @param upperLeftX X of the upper left corner.
 * @param upperLeftY Y of the upper left corner.
 * @param lowerRightX X of the lower right corner.
 * @param lowerRightY Y of the lower right corner.
 */
void PXP_SetProcessSurfacePosition(
    PXP_Type *base, uint16_t upperLeftX, uint16_t upperLeftY, uint16_t lowerRightX, uint16_t lowerRightY);

#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3
/*!
 * @brief Set the process surface color key.
 *
 * If the PS image matches colorkey range, the PS background color is output. Set
 * @p colorKeyLow to 0xFFFFFFFF and p colorKeyHigh to 0 will disable the colorkeying.
 *
 * @param base PXP peripheral base address.
 * @param num instance number. 0 for alpha engine A, 1 for alpha engine B.
 * @param colorKeyLow Color key low range.
 * @param colorKeyHigh Color key high range.
 */
void PXP_SetProcessSurfaceColorKey(PXP_Type *base, uint8_t num, uint32_t colorKeyLow, uint32_t colorKeyHigh);
#else
/*!
 * @brief Set the process surface color key.
 *
 * If the PS image matches colorkey range, the PS background color is output. Set
 * @p colorKeyLow to 0xFFFFFFFF and @p colorKeyHigh to 0 will disable the colorkeying.
 *
 * @param base PXP peripheral base address.
 * @param colorKeyLow Color key low range.
 * @param colorKeyHigh Color key high range.
 */
void PXP_SetProcessSurfaceColorKey(PXP_Type *base, uint32_t colorKeyLow, uint32_t colorKeyHigh);
#endif /* FSL_FEATURE_PXP_V3 */

/*!
 * @brief Set the process surface input pixel format YUV or YCbCr.
 *
 * If process surface input pixel format is YUV and CSC1 is not enabled,
 * in other words, the process surface output pixel format is also YUV,
 * then this function should be called to set whether input pixel format
 * is YUV or YCbCr.
 *
 * @param base PXP peripheral base address.
 * @param format The YUV format.
 */
static inline void PXP_SetProcessSurfaceYUVFormat(PXP_Type *base, pxp_ps_yuv_format_t format)
{
    if (kPXP_PsYUVFormatYUV == format)
    {
        base->CSC1_COEF0 &= ~PXP_CSC1_COEF0_YCBCR_MODE_MASK;
    }
    else
    {
        base->CSC1_COEF0 |= PXP_CSC1_COEF0_YCBCR_MODE_MASK;
    }
}
/* @} */

/*!
 * @name Output buffer
 * @{
 */

/*!
 * @brief Set the PXP outpt buffer configuration.
 *
 * @param base PXP peripheral base address.
 * @param config Pointer to the configuration.
 */
void PXP_SetOutputBufferConfig(PXP_Type *base, const pxp_output_buffer_config_t *config);

/*!
 * @brief Set the global overwritten alpha value.
 *
 * If global overwritten alpha is enabled, the alpha component in output buffer pixels
 * will be overwritten, otherwise the computed alpha value is used.
 *
 * @param base PXP peripheral base address.
 * @param alpha The alpha value.
 */
static inline void PXP_SetOverwrittenAlphaValue(PXP_Type *base, uint8_t alpha)
{
    base->OUT_CTRL = (base->OUT_CTRL & ~PXP_OUT_CTRL_ALPHA_MASK) | PXP_OUT_CTRL_ALPHA(alpha);
}

/*!
 * @brief Enable or disable the global overwritten alpha value.
 *
 * If global overwritten alpha is enabled, the alpha component in output buffer pixels
 * will be overwritten, otherwise the computed alpha value is used.
 *
 * @param base PXP peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void PXP_EnableOverWrittenAlpha(PXP_Type *base, bool enable)
{
    if (enable)
    {
        base->OUT_CTRL_SET = PXP_OUT_CTRL_ALPHA_OUTPUT_MASK;
    }
    else
    {
        base->OUT_CTRL_CLR = PXP_OUT_CTRL_ALPHA_OUTPUT_MASK;
    }
}

/*!
 * @brief Set the rotation configuration.
 *
 * The PXP could rotate the process surface or the output buffer. There are
 * two PXP versions:
 *  - Version 1: Only has one rotate sub module, the output buffer and process
 *    surface share the same rotate sub module, which means the process surface
 *    and output buffer could not be rotate at the same time. When pass in
 *    @ref kPXP_RotateOutputBuffer, the process surface could not use the rotate,
 *    Also when pass in @ref kPXP_RotateProcessSurface, output buffer could not
 *    use the rotate.
 *  - Version 2: Has two seperate rotate sub modules, the output buffer and
 *    process surface could configure the rotation independently.
 *
 * Upper layer could use the macro PXP_SHARE_ROTATE to check which version is.
 * PXP_SHARE_ROTATE=1 means version 1.
 *
 * @param base PXP peripheral base address.
 * @param position Rotate process surface or output buffer.
 * @param degree Rotate degree.
 * @param flipMode Flip mode.
 *
 * @note This function is different depends on the macro PXP_SHARE_ROTATE.
 */
static inline void PXP_SetRotateConfig(PXP_Type *base,
                                       pxp_rotate_position_t position,
                                       pxp_rotate_degree_t degree,
                                       pxp_flip_mode_t flipMode)
{
#if PXP_SHARE_ROTATE
    base->CTRL =
        (base->CTRL & ~(PXP_CTRL_ROTATE_MASK | PXP_CTRL_ROT_POS_MASK | PXP_CTRL_VFLIP_MASK | PXP_CTRL_HFLIP_MASK)) |
        PXP_CTRL_ROTATE(degree) | PXP_CTRL_ROT_POS(position) | ((uint32_t)flipMode << PXP_CTRL_HFLIP_SHIFT);
#else
    uint32_t ctrl = base->CTRL;

    if (kPXP_RotateOutputBuffer == position)
    {
        ctrl &= ~(PXP_CTRL_HFLIP0_MASK | PXP_CTRL_VFLIP0_MASK | PXP_CTRL_ROTATE0_MASK);
        ctrl |= (PXP_CTRL_ROTATE0(degree) | ((uint32_t)flipMode << PXP_CTRL_HFLIP0_SHIFT));
    }
    else
    {
        ctrl &= ~(PXP_CTRL_HFLIP1_MASK | PXP_CTRL_VFLIP1_MASK | PXP_CTRL_ROTATE1_MASK);
        ctrl |= (PXP_CTRL_ROTATE1(degree) | ((uint32_t)flipMode << PXP_CTRL_HFLIP1_SHIFT));
    }

    base->CTRL = ctrl;
#endif
}

/*!
 * @brief Build a solid rectangle of given pixel value.
 *
 * @param base PXP peripheral base address.
 * @param outFormat output pixel format.
 * @param value The value of the pixel to be filled in the rectangle in ARGB8888 format.
 * @param width width of the rectangle.
 * @param height height of the rectangle.
 * @param pitch output pitch in byte.
 * @param outAddr address of the memory to store the rectangle.
 */
void PXP_BuildRect(PXP_Type *base,
                   pxp_output_pixel_format_t outFormat,
                   uint32_t value,
                   uint16_t width,
                   uint16_t height,
                   uint16_t pitch,
                   uint32_t outAddr);
/* @} */

/*!
 * @name Command queue
 * @{
 */

/*!
 * @brief Set the next command.
 *
 * The PXP supports a primitive ability to queue up one operation while the current
 * operation is running. Workflow:
 *
 * 1. Prepare the PXP register values except STAT, CSCCOEFn, NEXT in the memory
 * in the order they appear in the register map.
 * 2. Call this function sets the new operation to PXP.
 * 3. There are two methods to check whether the PXP has loaded the new operation.
 * The first method is using @ref PXP_IsNextCommandPending. If there is new operation
 * not loaded by the PXP, this function returns true. The second method is checking
 * the flag @ref kPXP_CommandLoadFlag, if command loaded, this flag asserts. User
 * could enable interrupt @ref kPXP_CommandLoadInterruptEnable to get the loaded
 * signal in interrupt way.
 * 4. When command loaded by PXP, a new command could be set using this function.
 *
 * @code
   uint32_t pxp_command1[48];
   uint32_t pxp_command2[48];

   pxp_command1[0] = ...;
   pxp_command1[1] = ...;
   ...
   pxp_command2[0] = ...;
   pxp_command2[1] = ...;
   ...

   while (PXP_IsNextCommandPending(PXP))
   {
   }

   PXP_SetNextCommand(PXP, pxp_command1);

   while (PXP_IsNextCommandPending(PXP))
   {
   }

   PXP_SetNextCommand(PXP, pxp_command2);
   @endcode
 *
 * @param base PXP peripheral base address.
 * @param commandAddr Address of the new command.
 */
void PXP_SetNextCommand(PXP_Type *base, void *commandAddr);

/*!
 * @brief Check whether the next command is pending.
 *
 * @param base UART peripheral base address.
 * @return True is pending, false is not.
 */
static inline bool PXP_IsNextCommandPending(PXP_Type *base)
{
    return (bool)(base->NEXT & PXP_NEXT_ENABLED_MASK);
}

/*!
 * @brief Cancel command set by @ref PXP_SetNextCommand
 *
 * @param base UART peripheral base address.
 */
static inline void PXP_CancelNextCommand(PXP_Type *base)
{
    /* Write PXP_NEXT_ENABLED_MASK to the register NEXT_CLR to canel the command. */
    uint32_t regAddr = (uint32_t) & (base->NEXT);
    regAddr += 8U;
    *(uint32_t *)regAddr = PXP_NEXT_ENABLED_MASK;
}

/* @} */

/*!
 * @name Color space conversion
 * @{
 */

#if !(defined(FSL_FEATURE_PXP_HAS_NO_CSC2) && FSL_FEATURE_PXP_HAS_NO_CSC2)
/*!
 * @brief Set the CSC2 configuration.
 *
 * The CSC2 module receives pixels in any color space and can convert the pixels
 * into any of RGB, YUV, or YCbCr color spaces. The output pixels are passed
 * onto the LUT and rotation engine for further processing
 *
 * @param base PXP peripheral base address.
 * @param config Pointer to the configuration.
 */
void PXP_SetCsc2Config(PXP_Type *base, const pxp_csc2_config_t *config);

/*!
 * @brief Enable or disable the CSC2.
 *
 * @param base PXP peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void PXP_EnableCsc2(PXP_Type *base, bool enable)
{
    if (enable)
    {
        base->CSC2_CTRL &= ~PXP_CSC2_CTRL_BYPASS_MASK;
    }
    else
    {
        base->CSC2_CTRL |= PXP_CSC2_CTRL_BYPASS_MASK;
    }
}
#endif /* FSL_FEATURE_PXP_HAS_NO_CSC2 */

/*!
 * @brief Set the CSC1 mode.
 *
 * The CSC1 module receives scaled YUV/YCbCr444 pixels from the scale engine and
 * converts the pixels to the RGB888 color space. It could only be used by process
 * surface.
 *
 * @param base PXP peripheral base address.
 * @param mode The conversion mode.
 */
void PXP_SetCsc1Mode(PXP_Type *base, pxp_csc1_mode_t mode);

/*!
 * @brief Enable or disable the CSC1.
 *
 * @param base PXP peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void PXP_EnableCsc1(PXP_Type *base, bool enable)
{
    if (enable)
    {
        base->CSC1_COEF0 &= ~PXP_CSC1_COEF0_BYPASS_MASK;
    }
    else
    {
        base->CSC1_COEF0 |= PXP_CSC1_COEF0_BYPASS_MASK;
    }
}
/* @} */

#if !(defined(FSL_FEATURE_PXP_HAS_NO_LUT) && FSL_FEATURE_PXP_HAS_NO_LUT)
/*!
 * @name LUT operations
 * @{
 */

/*!
 * @brief Set the LUT configuration.
 *
 * The lookup table (LUT) is used to modify pixels in a manner that is not linear
 * and that cannot be achieved by the color space conversion modules. To setup
 * the LUT, the complete workflow is:
 * 1. Use @ref PXP_SetLutConfig to set the configuration, such as the lookup mode.
 * 2. Use @ref PXP_LoadLutTable to load the lookup table to PXP.
 * 3. Use @ref PXP_EnableLut to enable the function.
 *
 * @param base PXP peripheral base address.
 * @param config Pointer to the configuration.
 */
void PXP_SetLutConfig(PXP_Type *base, const pxp_lut_config_t *config);

/*!
 * @brief Set the look up table to PXP.
 *
 * If lookup mode is DIRECT mode, this function loads @p bytesNum of values
 * from the address @p memAddr into PXP LUT address @p lutStartAddr. So this
 * function allows only update part of the PXP LUT.
 *
 * If lookup mode is CACHE mode, this function sets the new address to @p memAddr
 * and invalid the PXP LUT cache.
 *
 * @param base PXP peripheral base address.
 * @param lookupMode Which lookup mode is used. Note that this parameter is only
 * used to distinguish DIRECT mode and CACHE mode, it does not change the register
 * value PXP_LUT_CTRL[LOOKUP_MODE]. To change that value, use function @ref PXP_SetLutConfig.
 * @param bytesNum How many bytes to set. This value must be divisable by 8.
 * @param memAddr Address of look up table to set.
 * @param lutStartAddr The LUT value will be loaded to LUT from index lutAddr. It should
 * be 8 bytes aligned.
 *
 * @retval kStatus_Success Load successfully.
 * @retval kStatus_InvalidArgument Failed because of invalid argument.
 */
status_t PXP_LoadLutTable(
    PXP_Type *base, pxp_lut_lookup_mode_t lookupMode, uint32_t bytesNum, uint32_t memAddr, uint16_t lutStartAddr);

/*!
 * @brief Enable or disable the LUT.
 *
 * @param base PXP peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void PXP_EnableLut(PXP_Type *base, bool enable)
{
    if (enable)
    {
        base->LUT_CTRL &= ~PXP_LUT_CTRL_BYPASS_MASK;
    }
    else
    {
        base->LUT_CTRL |= PXP_LUT_CTRL_BYPASS_MASK;
    }
}

/*!
 * @brief Select the 8kB LUT bank in DIRECT_RGB444 mode.
 *
 * @param base PXP peripheral base address.
 * @param bank The bank to select.
 */
static inline void PXP_Select8kLutBank(PXP_Type *base, pxp_lut_8k_bank_t bank)
{
    base->LUT_CTRL = (base->LUT_CTRL & ~PXP_LUT_CTRL_SEL_8KB_MASK) | PXP_LUT_CTRL_SEL_8KB(bank);
}
/* @} */
#endif /* FSL_FEATURE_PXP_HAS_NO_LUT */

#if (defined(FSL_FEATURE_PXP_HAS_DITHER) && FSL_FEATURE_PXP_HAS_DITHER)
/*!
 * @name Dither
 * @{
 */

/*!
 * @brief Write data to the PXP internal memory.
 *
 * @param base PXP peripheral base address.
 * @param ram Which internal memory to write.
 * @param bytesNum How many bytes to write.
 * @param data Pointer to the data to write.
 * @param memStartAddr The start address in the internal memory to write the data.
 */
void PXP_SetInternalRamData(PXP_Type *base, pxp_ram_t ram, uint32_t bytesNum, uint8_t *data, uint16_t memStartAddr);

/*!
 * @brief Set the dither final LUT data.
 *
 * The dither final LUT is only applicble to dither engine 0. It takes the bits[7:4]
 * of the output pixel and looks up and 8 bit value from the 16 value LUT to generate
 * the final output pixel to the next process module.
 *
 * @param base PXP peripheral base address.
 * @param data Pointer to the LUT data to set.
 */
void PXP_SetDitherFinalLutData(PXP_Type *base, const pxp_dither_final_lut_data_t *data);

/*!
 * @brief Set the configuration for the dither block.
 *
 * If the pre-dither LUT, post-dither LUT or ordered dither is used, please call
 * @ref PXP_SetInternalRamData to set the LUT data to internal memory.
 *
 * If the final LUT is used, please call @ref PXP_SetDitherFinalLutData to set
 * the LUT data.
 *
 * @param base PXP peripheral base address.
 * @param config Pointer to the configuration.
 *
 * @note When using ordered dithering, please set the PXP process block size same
 * with the ordered dithering matrix size using function @ref PXP_SetProcessBlockSize.
 */
static inline void PXP_SetDitherConfig(PXP_Type *base, const pxp_dither_config_t *config)
{
    typedef union
    {
        pxp_dither_config_t _dither_config;
        uint32_t _u32;
    } pxp_reg_convert_t;

    pxp_reg_convert_t pid;

    pid._dither_config = *config;
    base->DITHER_CTRL  = pid._u32 & 0x00FFFFFFU;
}

/*!
 * @brief Enable or disable dither engine in the PXP process path.
 *
 * After the initialize function @ref PXP_Init, the dither engine is disabled and not
 * use in the PXP processing path. This function enables the dither engine and
 * routes the dither engine output to the output buffer. When the dither engine
 * is enabled using this function, @ref PXP_SetDitherConfig must be called to
 * configure dither engine correctly, otherwise there is not output to the output
 * buffer.
 *
 * @param base PXP peripheral base address.
 * @param enable Pass in true to enable, false to disable.
 */
void PXP_EnableDither(PXP_Type *base, bool enable);

/* @} */

#endif /* FSL_FEATURE_PXP_HAS_DITHER */

/*!
 * @name Porter Duff
 * @{
 */
#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3
/*!
 * @brief Set the Porter Duff configuration for one of the alpha process engine.
 *
 * @param base PXP peripheral base address.
 * @param num instance number.
 * @param config Pointer to the configuration.
 */
void PXP_SetPorterDuffConfig(PXP_Type *base, uint8_t num, const pxp_porter_duff_config_t *config);
#endif /* FSL_FEATURE_PXP_V3 */

#if !(defined(FSL_FEATURE_PXP_HAS_NO_PORTER_DUFF_CTRL) && FSL_FEATURE_PXP_HAS_NO_PORTER_DUFF_CTRL)
/*!
 * @brief Set the Porter Duff configuration.
 *
 * @param base PXP peripheral base address.
 * @param config Pointer to the configuration.
 */
void PXP_SetPorterDuffConfig(PXP_Type *base, const pxp_porter_duff_config_t *config);
#endif /* FSL_FEATURE_PXP_HAS_NO_PORTER_DUFF_CTRL */

#if (!(defined(FSL_FEATURE_PXP_HAS_NO_PORTER_DUFF_CTRL) && FSL_FEATURE_PXP_HAS_NO_PORTER_DUFF_CTRL)) || \
    (defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3)
/*!
 * @brief Get the Porter Duff configuration by blend mode.
 *
 * The FactorMode are selected based on blend mode, the AlphaMode are set to
 * @ref kPXP_PorterDuffAlphaStraight, the ColorMode are set to
 * @ref kPXP_PorterDuffColorWithAlpha, the GlobalAlphaMode are set to
 * @ref kPXP_PorterDuffLocalAlpha. These values could be modified after calling
 * this function.
 *
 * @param mode The blend mode.
 * @param config Pointer to the configuration.
 * @retval kStatus_Success Successfully get the configuratoin.
 * @retval kStatus_InvalidArgument The blend mode not supported.
 */
status_t PXP_GetPorterDuffConfig(pxp_porter_duff_blend_mode_t mode, pxp_porter_duff_config_t *config);

/* @} */
#endif /* FSL_FEATURE_PXP_V3 || FSL_FEATURE_PXP_HAS_NO_PORTER_DUFF_CTRL  */

/* @} */

/*!
 * @name Buffer copy
 * @{
 */

/*!
 * @brief Copy picture from one buffer to another buffer.
 *
 * This function copies a rectangle from one buffer to another buffer.
 *
 * @verbatim
                      Source buffer:
   srcPicBaseAddr
   +-----------------------------------------------------------+
   |                                                           |
   |  (srcOffsetX, srcOffsetY)                                 |
   |           +-------------------+                           |
   |           |                   |                           |
   |           |                   |                           |
   |           |                   | height                    |
   |           |                   |                           |
   |           |                   |                           |
   |           +-------------------+                           |
   |                 width                                     |
   |                                                           |
   |                       srcPicthBytes                       |
   +-----------------------------------------------------------+

                     Destination buffer:
   destPicBaseAddr
   +-------------------------------------------+
   |                                           |
   |                                           |
   |                                           |
   |  (destOffsetX, destOffsetY)               |
   |       +-------------------+               |
   |       |                   |               |
   |       |                   |               |
   |       |                   | height        |
   |       |                   |               |
   |       |                   |               |
   |       +-------------------+               |
   |             width                         |
   |                                           |
   |                                           |
   |                                           |
   |                  destPicthBytes           |
   +-------------------------------------------+
   @endverbatim
 *
 * @note This function resets the old PXP settings, which means the settings
 * like rotate, flip, will be reseted to disabled status.
 *
 * @param base PXP peripheral base address.
 * @param config Pointer to the picture copy configuration structure.
 * @retval kStatus_Success Successfully started the copy process.
 * @retval kStatus_InvalidArgument Invalid argument.
 */
status_t PXP_StartPictureCopy(PXP_Type *base, const pxp_pic_copy_config_t *config);

/*!
 * @brief Copy continous memory.
 *
 * @note The copy size should be 512 byte aligned.
 * @note This function resets the old PXP settings, which means the settings
 * like rotate, flip, will be reseted to disabled status.
 *
 * @param base PXP peripheral base address.
 * @param srcAddr Source memory address.
 * @param destAddr Destination memory address.
 * @param size How many bytes to copy, should be 512 byte aligned.
 * @retval kStatus_Success Successfully started the copy process.
 * @retval kStatus_InvalidArgument Invalid argument.
 */
status_t PXP_StartMemCopy(PXP_Type *base, uint32_t srcAddr, uint32_t destAddr, uint32_t size);

/*!
 * @brief Copy continous memory.
 *
 * @note This function resets the old PXP settings, which means the settings
 * like rotate, flip, will be reseted to disabled status.
 *
 * @note Compare with @PXP_StartMemCopy, this function supports size not aligned to
 * 512 bytes. This function returns when copy finished, upper layer doesn't need to
 * wait @ref kPXP_CompleteFlag.
 *
 * @param base PXP peripheral base address.
 * @param srcAddr Source memory address.
 * @param destAddr Destination memory address.
 * @param size How many bytes to copy, should be 512 byte aligned.
 * @retval kStatus_Success Successfully started the copy process.
 * @retval kStatus_InvalidArgument Invalid argument.
 */
status_t PXP_MemCopy(PXP_Type *base, uint32_t srcAddr, uint32_t destAddr, uint32_t size);

/* @} */

#if defined(FSL_FEATURE_PXP_V3) && FSL_FEATURE_PXP_V3

/*!
 * @name Fetch engine
 * @{
 */
/*!
 * @brief Configures one channel of some block's fetch engine.
 *
 * Fetch engine is 64-bit input and 32-bit output per channel
 *
 * @param base PXP peripheral base address.
 * @param name which block the fetch engine belongs to.
 * @param channel channel number.
 * @param config pointer to the configuration structure.
 * @retval kStatus_Success Successfully configured the engine.
 * @retval kStatus_InvalidArgument Invalid argument.
 */
status_t PXP_SetFetchEngineConfig(PXP_Type *base,
                                  pxp_fetch_engine_name_t name,
                                  uint8_t channel,
                                  const pxp_fetch_engine_config_t *config);

/*!
 * @brief Enables/disables the fetch engine.
 *
 * @param base PXP peripheral base address.
 * @param name which block the fetch engine belongs to.
 * @param channel channel number.
 * @param enable true to enable, false to disable.
 */
static inline void PXP_EnableFetchEngine(PXP_Type *base, pxp_fetch_engine_name_t name, uint8_t channel, bool enable)
{
    if (enable)
    {
        if (name == kPXP_FetchInput)
        {
            switch (channel)
            {
                case 0:
                    base->INPUT_FETCH_CTRL_CH0_SET = PXP_INPUT_FETCH_CTRL_CH0_CH_EN_MASK;
                    break;

                case 1:
                    base->INPUT_FETCH_CTRL_CH1_SET = PXP_INPUT_FETCH_CTRL_CH1_CH_EN_MASK;
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
                    base->DITHER_FETCH_CTRL_CH0_SET = PXP_DITHER_FETCH_CTRL_CH0_CH_EN_MASK;
                    break;

                case 1:
                    base->DITHER_FETCH_CTRL_CH1_SET = PXP_DITHER_FETCH_CTRL_CH1_CH_EN_MASK;
                    break;

                default:
                    /* Only 2 channels are supported per fetch engine. */
                    assert(false);
                    break;
            }
        }
    }
    else
    {
        if (name == kPXP_FetchInput)
        {
            switch (channel)
            {
                case 0:
                    base->INPUT_FETCH_CTRL_CH0_CLR = PXP_INPUT_FETCH_CTRL_CH0_CH_EN_MASK;
                    break;

                case 1:
                    base->INPUT_FETCH_CTRL_CH1_CLR = PXP_INPUT_FETCH_CTRL_CH1_CH_EN_MASK;
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
                    base->DITHER_FETCH_CTRL_CH0_CLR = PXP_DITHER_FETCH_CTRL_CH0_CH_EN_MASK;
                    break;

                case 1:
                    base->DITHER_FETCH_CTRL_CH1_CLR = PXP_DITHER_FETCH_CTRL_CH1_CH_EN_MASK;
                    break;

                default:
                    /* Only 2 channels are supported per fetch engine. */
                    assert(false);
                    break;
            }
        }
    }
}
/* @} */

/*!
 * @name Store engine
 * @{
 */

/*!
 * @brief Configures one channel of some block's store engine.
 *
 * Store engine is 32-bit input and 64-bit output per channel.
 * @note: If there is only one channel used for data input, channel 0 must be used rather than channel 1.
 *
 * @param base PXP peripheral base address.
 * @param name the store engine belongs to which block.
 * @param channel channel number.
 * @param config pointer to the configuration structure.
 * @retval kStatus_Success Successfully configured the engine.
 * @retval kStatus_InvalidArgument Invalid argument.
 */
status_t PXP_SetStoreEngineConfig(PXP_Type *base,
                                  pxp_store_engine_name_t name,
                                  uint8_t channel,
                                  const pxp_store_engine_config_t *config);

/*!
 * @brief Enables/disables the store engine.
 *
 * @param base PXP peripheral base address.
 * @param name which block the store engine belongs to.
 * @param channel channel number.
 * @param enable true to enable, false to disable.
 */
static inline void PXP_EnableStoreEngine(PXP_Type *base, pxp_store_engine_name_t name, uint8_t channel, bool enable)
{
    if (enable)
    {
        if (name == kPXP_StoreInput)
        {
            switch (channel)
            {
                case 0:
                    base->INPUT_STORE_CTRL_CH0_SET = PXP_INPUT_STORE_CTRL_CH0_CH_EN_MASK;
                    break;

                case 1:
                    base->INPUT_STORE_CTRL_CH1_SET = PXP_INPUT_STORE_CTRL_CH1_CH_EN_MASK;
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
                    base->DITHER_STORE_CTRL_CH0_SET = PXP_DITHER_STORE_CTRL_CH0_CH_EN_MASK;
                    break;

                case 1:
                    base->DITHER_STORE_CTRL_CH1_SET = PXP_DITHER_STORE_CTRL_CH1_CH_EN_MASK;
                    break;

                default:
                    /* Only 2 channels are supported per fetch engine. */
                    assert(false);
                    break;
            }
        }
    }
    else
    {
        if (name == kPXP_StoreInput)
        {
            switch (channel)
            {
                case 0:
                    base->INPUT_STORE_CTRL_CH0_CLR = PXP_INPUT_STORE_CTRL_CH0_CH_EN_MASK;
                    break;

                case 1:
                    base->INPUT_STORE_CTRL_CH1_CLR = PXP_INPUT_STORE_CTRL_CH1_CH_EN_MASK;
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
                    base->DITHER_STORE_CTRL_CH0_CLR = PXP_DITHER_STORE_CTRL_CH0_CH_EN_MASK;
                    break;

                case 1:
                    base->DITHER_STORE_CTRL_CH1_CLR = PXP_DITHER_STORE_CTRL_CH1_CH_EN_MASK;
                    break;

                default:
                    /* Only 2 channels are supported per fetch engine. */
                    assert(false);
                    break;
            }
        }
    }
}

/*!
 * @brief Combines the 2 channels of some store engine.
 *
 * Store engine is 32-bit input and 64-bit output per channel. If both channels of store engine's
 * input and 8 bits flag contain valid data, then need set combine to true to support total 64-bit input.
 *
 * @param base PXP peripheral base address.
 * @param name the store engine belongs to which block.
 * @param combine true to combine the 2 channels.
 */
static inline void PXP_CombineStoreEngineChannel(PXP_Type *base, pxp_store_engine_name_t name, bool combine)
{
    if (name == kPXP_StoreInput)
    {
        if (combine)
        {
            base->INPUT_STORE_CTRL_CH0_SET = PXP_INPUT_STORE_CTRL_CH0_SET_COMBINE_2CHANNEL_MASK;
        }
        else
        {
            base->INPUT_STORE_CTRL_CH0_CLR = PXP_INPUT_STORE_CTRL_CH0_SET_COMBINE_2CHANNEL_MASK;
        }
    }
    else
    {
        if (combine)
        {
            base->DITHER_STORE_CTRL_CH0_SET = PXP_DITHER_STORE_CTRL_CH0_SET_COMBINE_2CHANNEL_MASK;
        }
        else
        {
            base->DITHER_STORE_CTRL_CH0_CLR = PXP_DITHER_STORE_CTRL_CH0_SET_COMBINE_2CHANNEL_MASK;
        }
    }
}
/* @} */

/*!
 * @name Pre-dither CFA engine
 * @{
 */
/*!
 * @brief Configures the pre-dither CFA engine.
 *
 * @param base PXP peripheral base address.
 * @param config pointer to the configuration structure.
 * @retval kStatus_Success Successfully configured the engine.
 * @retval kStatus_InvalidArgument Invalid argument.
 */
status_t PXP_SetCfaConfig(PXP_Type *base, const pxp_cfa_config_t *config);

/*!
 * @brief Enables/disables the CFA block.
 *
 * @param base PXP peripheral base address.
 * @param enable true to enable, false to disable.
 */
static inline void PXP_EnableCfa(PXP_Type *base, bool enable)
{
    if (enable)
    {
        base->CFA_CTRL_CLR = PXP_CFA_CTRL_CFA_BYPASS_MASK;
    }
    else
    {
        base->CFA_CTRL_SET = PXP_CFA_CTRL_CFA_BYPASS_MASK;
    }
}
/* @} */

/*!
 * @name Histogram engine
 * @{
 */
/*!
 * @brief Configures histogram engine.
 *
 * @param base PXP peripheral base address.
 * @param num instance number.
 * @param config pointer to the configuration structure.
 * @retval kStatus_Success Successfully configured the engine.
 * @retval kStatus_InvalidArgument Invalid argument.
 */
status_t PXP_SetHistogramConfig(PXP_Type *base, uint8_t num, const pxp_histogram_config_t *config);

/*!
 * @brief Enables/disables the histogram engine.
 *
 * @param base PXP peripheral base address.
 * @param num instance number.
 * @param enable true to enable, false to disable.
 */
static inline void PXP_EnableHistogram(PXP_Type *base, uint8_t num, bool enable)
{
    switch (num)
    {
        case 0:
            base->HIST_A_CTRL =
                (base->HIST_A_CTRL & ~PXP_HIST_A_CTRL_ENABLE_MASK) | PXP_HIST_A_CTRL_ENABLE((uint32_t)enable);
            break;

        case 1:
            base->HIST_B_CTRL =
                (base->HIST_B_CTRL & ~PXP_HIST_B_CTRL_ENABLE_MASK) | PXP_HIST_B_CTRL_ENABLE((uint32_t)enable);
            break;

        default:
            /* Only 2 instances are supported per fetch engine. */
            assert(false);
            break;
    }
}

/*!
 * @brief Gets the results of histogram mask operation.
 *
 * @param base PXP peripheral base address.
 * @param num instance number.
 * @param result pointer to the result structure.
 */
void PXP_GetHistogramMaskResult(PXP_Type *base, uint8_t num, pxp_histogram_mask_result_t *result);

/*!
 * @brief Gets the PXP Histogram operation result
 *
 * @param base PXP peripheral base address.
 * @param num instance number.
 * @return bit map of the match result in @ref _pxp_histgram_flags ORed together
 */
static inline uint8_t PXP_GetHistogramMatchResult(PXP_Type *base, uint8_t num)
{
    uint8_t result = 0U;
    switch (num)
    {
        case 0:
            result = (uint8_t)((base->HIST_A_CTRL & PXP_HIST_A_CTRL_STATUS_MASK) >> PXP_HIST_A_CTRL_STATUS_SHIFT);
            break;

        case 1:
            result = (uint8_t)((base->HIST_B_CTRL & PXP_HIST_B_CTRL_STATUS_MASK) >> PXP_HIST_B_CTRL_STATUS_SHIFT);
            break;

        default:
            /* Only 2 histogram instances are supported. */
            assert(false);
            break;
    }

    return result;
}

/*!
 * @brief Clears the current histogram operation result.
 *
 * Clears the current histogram operation result, including mask operation result and from 2-level to 32-level match
 * result.
 *
 * @param base PXP peripheral base address.
 * @param num instance number.
 */
static inline void PXP_ClearHistogramResult(PXP_Type *base, uint8_t num)
{
    switch (num)
    {
        case 0:
            base->HIST_A_CTRL |= PXP_HIST_A_CTRL_CLEAR_MASK;
            break;

        case 1:
            base->HIST_B_CTRL |= PXP_HIST_B_CTRL_CLEAR_MASK;
            break;

        default:
            /* Only 2 histogram instances are supported. */
            assert(false);
            break;
    }
}

/*!
 * @brief Gets the results of histogram mask operation.
 *
 * @param base PXP peripheral base address.
 * @param num instance number.
 * @param width the width of the updated block
 * @param height the height of the updated block
 */
static inline void PXP_SetHistogramSize(PXP_Type *base, uint8_t num, uint16_t width, uint16_t height)
{
    switch (num)
    {
        case 0:
            base->HIST_A_BUF_SIZE = ((uint32_t)height << 16U) | (uint32_t)width;
            break;

        case 1:
            base->HIST_B_BUF_SIZE = ((uint32_t)height << 16U) | (uint32_t)width;
            break;

        default:
            /* Only 2 histogram instances are supported. */
            assert(false);
            break;
    }
}
/* @} */

/*!
 * @name WFE engine
 * @{
 */

/*!
 * @brief Initializes the WFE-A engine for waveform process.
 *
 * @param base PXP peripheral base address.
 * @param ditherHandshake true to enable handshake mode with upstream dither store engine.
 */
void PXP_WfeaInit(PXP_Type *base, bool ditherHandshake);

/*!
 * @brief Enables/disables hanshake mode with upstream dither engine.
 *
 * @param base PXP peripheral base address.
 * @param enable true to enable handshake mode with upstream dither store engine.
 */
static inline void PXP_WfeaEnableDitherHandshake(PXP_Type *base, bool enable)
{
    if (enable)
    {
        base->WFA_FETCH_CTRL |= PXP_WFA_FETCH_CTRL_BF1_HSK_MODE_MASK;
    }
    else
    {
        base->WFA_FETCH_CTRL &= ~PXP_WFA_FETCH_CTRL_BF1_HSK_MODE_MASK;
    }
}

/*!
 * @brief Configure the WFE-A engine
 *
 * @param base PXP peripheral base address.
 * @param config pointer to the configuration structure.
 */
void PXP_SetWfeaConfig(PXP_Type *base, const pxp_wfea_engine_config_t *config);

/*!
 * @brief Sets the LUT usage status for waveform engine.
 *
 * If any EPDC LUT(s) has been occupied, use this API to set its usage for PXP WFE-A.
 *
 * @param base PXP base pointer
 * @param lutStatus the status mask of the LUT(s) to be set, can be a single flag or several flags up to all 64 LUTs.
 *  If user wants to set LUT17 usage, set bit 17 in the lutStatus.
 */
static inline void PXP_SetLutUsage(PXP_Type *base, uint64_t lutStatus)
{
    base->WFE_A_STG1_8X1_OUT0_0 |= (uint32_t)lutStatus;
    base->WFE_A_STG1_8X1_OUT0_1 |= (uint32_t)(lutStatus >> 32U);
}

/*!
 * @brief Clears the LUT usage status for waveform engine.
 *
 * If any EPDC LUT(s) has finished processing and is(are) free, use this API to clear its usage for PXP WFE-A.
 *
 * @param base PXP base pointer
 * @param lutStatus the status mask of the LUT(s) to be cleared, can be a single flag or several flags up to all 64
 * LUTs. If user wants to clear LUT17, set bit 17.
 */
static inline void PXP_ClearLutUsage(PXP_Type *base, uint64_t lutStatus)
{
    base->WFE_A_STG1_8X1_OUT0_0 &= ~(uint32_t)lutStatus;
    base->WFE_A_STG1_8X1_OUT0_1 &= ~(uint32_t)(lutStatus >> 32U);
}

/*!
 * @brief Gets the occupied LUT list.
 *
 * @param base PXP base pointer
 * @return lutStatus the status mask of the LUT(s) that is(are) occupied
 */
static inline uint64_t PXP_GetLutUsage(PXP_Type *base)
{
    return ((uint64_t)base->WFE_A_STG1_8X1_OUT0_0 | (uint64_t)base->WFE_A_STG1_8X1_OUT0_1 << 32U);
}

/* @} */

#endif /* FSL_FEATURE_PXP_V3 */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_PXP_H_ */
