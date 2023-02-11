/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_FLEXCAN_H_
#define _FSL_FLEXCAN_H_

#include "fsl_common.h"

/*!
 * @addtogroup flexcan_driver
 * @{
 */

/******************************************************************************
 * Definitions
 *****************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief FlexCAN driver version. */
#define FSL_FLEXCAN_DRIVER_VERSION (MAKE_VERSION(2, 8, 6))
/*@}*/

#if !(defined(FLEXCAN_WAIT_TIMEOUT) && FLEXCAN_WAIT_TIMEOUT)
/* Define to 1000 means keep waiting 1000 times until the flag is assert/deassert.  */
#define FLEXCAN_WAIT_TIMEOUT (1000U)
#endif

/*! @brief FlexCAN frame length helper macro. */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
#define DLC_LENGTH_DECODE(dlc) (((dlc) <= 8U) ? (dlc) : (((dlc) <= 12U) ? (((dlc)-6U) * 4U) : (((dlc)-11U) * 16U)))
#endif

/*! @brief FlexCAN Frame ID helper macro. */
#define FLEXCAN_ID_STD(id) \
    (((uint32_t)(((uint32_t)(id)) << CAN_ID_STD_SHIFT)) & CAN_ID_STD_MASK) /*!< Standard Frame ID helper macro. */
#define FLEXCAN_ID_EXT(id)                                \
    (((uint32_t)(((uint32_t)(id)) << CAN_ID_EXT_SHIFT)) & \
     (CAN_ID_EXT_MASK | CAN_ID_STD_MASK)) /*!< Extend Frame ID helper macro. */

/*! @brief FlexCAN Rx Message Buffer Mask helper macro. */
#define FLEXCAN_RX_MB_STD_MASK(id, rtr, ide)                                   \
    (((uint32_t)((uint32_t)(rtr) << 31) | (uint32_t)((uint32_t)(ide) << 30)) | \
     FLEXCAN_ID_STD(id)) /*!< Standard Rx Message Buffer Mask helper macro. */
#define FLEXCAN_RX_MB_EXT_MASK(id, rtr, ide)                                   \
    (((uint32_t)((uint32_t)(rtr) << 31) | (uint32_t)((uint32_t)(ide) << 30)) | \
     FLEXCAN_ID_EXT(id)) /*!< Extend Rx Message Buffer Mask helper macro. */

/*! @brief FlexCAN Legacy Rx FIFO Mask helper macro. */
#define FLEXCAN_RX_FIFO_STD_MASK_TYPE_A(id, rtr, ide)                          \
    (((uint32_t)((uint32_t)(rtr) << 31) | (uint32_t)((uint32_t)(ide) << 30)) | \
     (FLEXCAN_ID_STD(id) << 1)) /*!< Standard Rx FIFO Mask helper macro Type A helper macro. */
#define FLEXCAN_RX_FIFO_STD_MASK_TYPE_B_HIGH(id, rtr, ide)                     \
    (((uint32_t)((uint32_t)(rtr) << 31) | (uint32_t)((uint32_t)(ide) << 30)) | \
     (((uint32_t)(id)&0x7FF) << 19)) /*!< Standard Rx FIFO Mask helper macro Type B upper part helper macro. */
#define FLEXCAN_RX_FIFO_STD_MASK_TYPE_B_LOW(id, rtr, ide)                      \
    (((uint32_t)((uint32_t)(rtr) << 15) | (uint32_t)((uint32_t)(ide) << 14)) | \
     (((uint32_t)(id)&0x7FF) << 3)) /*!< Standard Rx FIFO Mask helper macro Type B lower part helper macro. */
#define FLEXCAN_RX_FIFO_STD_MASK_TYPE_C_HIGH(id) \
    (((uint32_t)(id)&0x7F8) << 21) /*!< Standard Rx FIFO Mask helper macro Type C upper part helper macro. */
#define FLEXCAN_RX_FIFO_STD_MASK_TYPE_C_MID_HIGH(id) \
    (((uint32_t)(id)&0x7F8) << 13) /*!< Standard Rx FIFO Mask helper macro Type C mid-upper part helper macro. */
#define FLEXCAN_RX_FIFO_STD_MASK_TYPE_C_MID_LOW(id) \
    (((uint32_t)(id)&0x7F8) << 5) /*!< Standard Rx FIFO Mask helper macro Type C mid-lower part helper macro. */
#define FLEXCAN_RX_FIFO_STD_MASK_TYPE_C_LOW(id) \
    (((uint32_t)(id)&0x7F8) >> 3) /*!< Standard Rx FIFO Mask helper macro Type C lower part helper macro. */
#define FLEXCAN_RX_FIFO_EXT_MASK_TYPE_A(id, rtr, ide)                          \
    (((uint32_t)((uint32_t)(rtr) << 31) | (uint32_t)((uint32_t)(ide) << 30)) | \
     (FLEXCAN_ID_EXT(id) << 1)) /*!< Extend Rx FIFO Mask helper macro Type A helper macro. */
#define FLEXCAN_RX_FIFO_EXT_MASK_TYPE_B_HIGH(id, rtr, ide)                        \
    (                                                                             \
        ((uint32_t)((uint32_t)(rtr) << 31) | (uint32_t)((uint32_t)(ide) << 30)) | \
        ((FLEXCAN_ID_EXT(id) & 0x1FFF8000)                                        \
         << 1)) /*!< Extend Rx FIFO Mask helper macro Type B upper part helper macro. */
#define FLEXCAN_RX_FIFO_EXT_MASK_TYPE_B_LOW(id, rtr, ide)                      \
    (((uint32_t)((uint32_t)(rtr) << 15) | (uint32_t)((uint32_t)(ide) << 14)) | \
     ((FLEXCAN_ID_EXT(id) & 0x1FFF8000) >>                                     \
      15)) /*!< Extend Rx FIFO Mask helper macro Type B lower part helper macro. */
#define FLEXCAN_RX_FIFO_EXT_MASK_TYPE_C_HIGH(id) \
    ((FLEXCAN_ID_EXT(id) & 0x1FE00000) << 3) /*!< Extend Rx FIFO Mask helper macro Type C upper part helper macro. */
#define FLEXCAN_RX_FIFO_EXT_MASK_TYPE_C_MID_HIGH(id) \
    ((FLEXCAN_ID_EXT(id) & 0x1FE00000) >>            \
     5) /*!< Extend Rx FIFO Mask helper macro Type C mid-upper part helper macro. */
#define FLEXCAN_RX_FIFO_EXT_MASK_TYPE_C_MID_LOW(id) \
    ((FLEXCAN_ID_EXT(id) & 0x1FE00000) >>           \
     13) /*!< Extend Rx FIFO Mask helper macro Type C mid-lower part helper macro. */
#define FLEXCAN_RX_FIFO_EXT_MASK_TYPE_C_LOW(id) \
    ((FLEXCAN_ID_EXT(id) & 0x1FE00000) >> 21) /*!< Extend Rx FIFO Mask helper macro Type C lower part helper macro. */

/*! @brief FlexCAN Rx FIFO Filter helper macro. */
#define FLEXCAN_RX_FIFO_STD_FILTER_TYPE_A(id, rtr, ide) \
    FLEXCAN_RX_FIFO_STD_MASK_TYPE_A(id, rtr, ide) /*!< Standard Rx FIFO Filter helper macro Type A helper macro. */
#define FLEXCAN_RX_FIFO_STD_FILTER_TYPE_B_HIGH(id, rtr, ide) \
    FLEXCAN_RX_FIFO_STD_MASK_TYPE_B_HIGH(                    \
        id, rtr, ide) /*!< Standard Rx FIFO Filter helper macro Type B upper part helper macro. */
#define FLEXCAN_RX_FIFO_STD_FILTER_TYPE_B_LOW(id, rtr, ide) \
    FLEXCAN_RX_FIFO_STD_MASK_TYPE_B_LOW(                    \
        id, rtr, ide) /*!< Standard Rx FIFO Filter helper macro Type B lower part helper macro. */
#define FLEXCAN_RX_FIFO_STD_FILTER_TYPE_C_HIGH(id) \
    FLEXCAN_RX_FIFO_STD_MASK_TYPE_C_HIGH(          \
        id) /*!< Standard Rx FIFO Filter helper macro Type C upper part helper macro. */
#define FLEXCAN_RX_FIFO_STD_FILTER_TYPE_C_MID_HIGH(id) \
    FLEXCAN_RX_FIFO_STD_MASK_TYPE_C_MID_HIGH(          \
        id) /*!< Standard Rx FIFO Filter helper macro Type C mid-upper part helper macro. */
#define FLEXCAN_RX_FIFO_STD_FILTER_TYPE_C_MID_LOW(id) \
    FLEXCAN_RX_FIFO_STD_MASK_TYPE_C_MID_LOW(          \
        id) /*!< Standard Rx FIFO Filter helper macro Type C mid-lower part helper macro. */
#define FLEXCAN_RX_FIFO_STD_FILTER_TYPE_C_LOW(id) \
    FLEXCAN_RX_FIFO_STD_MASK_TYPE_C_LOW(          \
        id) /*!< Standard Rx FIFO Filter helper macro Type C lower part helper macro.  */
#define FLEXCAN_RX_FIFO_EXT_FILTER_TYPE_A(id, rtr, ide) \
    FLEXCAN_RX_FIFO_EXT_MASK_TYPE_A(id, rtr, ide) /*!< Extend Rx FIFO Filter helper macro Type A helper macro. */
#define FLEXCAN_RX_FIFO_EXT_FILTER_TYPE_B_HIGH(id, rtr, ide) \
    FLEXCAN_RX_FIFO_EXT_MASK_TYPE_B_HIGH(                    \
        id, rtr, ide) /*!< Extend Rx FIFO Filter helper macro Type B upper part helper macro. */
#define FLEXCAN_RX_FIFO_EXT_FILTER_TYPE_B_LOW(id, rtr, ide) \
    FLEXCAN_RX_FIFO_EXT_MASK_TYPE_B_LOW(                    \
        id, rtr, ide) /*!< Extend Rx FIFO Filter helper macro Type B lower part helper macro. */
#define FLEXCAN_RX_FIFO_EXT_FILTER_TYPE_C_HIGH(id) \
    FLEXCAN_RX_FIFO_EXT_MASK_TYPE_C_HIGH(          \
        id) /*!< Extend Rx FIFO Filter helper macro Type C upper part helper macro.           */
#define FLEXCAN_RX_FIFO_EXT_FILTER_TYPE_C_MID_HIGH(id) \
    FLEXCAN_RX_FIFO_EXT_MASK_TYPE_C_MID_HIGH(          \
        id) /*!< Extend Rx FIFO Filter helper macro Type C mid-upper part helper macro. */
#define FLEXCAN_RX_FIFO_EXT_FILTER_TYPE_C_MID_LOW(id) \
    FLEXCAN_RX_FIFO_EXT_MASK_TYPE_C_MID_LOW(          \
        id) /*!< Extend Rx FIFO Filter helper macro Type C mid-lower part helper macro. */
#define FLEXCAN_RX_FIFO_EXT_FILTER_TYPE_C_LOW(id) \
    FLEXCAN_RX_FIFO_EXT_MASK_TYPE_C_LOW(id) /*!< Extend Rx FIFO Filter helper macro Type C lower part helper macro. */

#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
/*! @brief FlexCAN Enhanced Rx FIFO Filter and Mask helper macro. */
#define ENHANCED_RX_FIFO_FSCH(x) (((uint32_t)(((uint32_t)(x)) << 30)) & 0xC0000000U)
#define RTR_STD_HIGH(x)          (((uint32_t)(((uint32_t)(x)) << 27)) & 0x08000000U)
#define RTR_STD_LOW(x)           (((uint32_t)(((uint32_t)(x)) << 11)) & 0x00000800U)
#define RTR_EXT(x)               (((uint32_t)(((uint32_t)(x)) << 29)) & 0x40000000U)
#define ID_STD_LOW(id)           (((uint32_t)id) & 0x7FFU)
#define ID_STD_HIGH(id)          (((uint32_t)(((uint32_t)(id)) << 16)) & 0x07FF0000U)
#define ID_EXT(id)               (((uint32_t)id) & 0x1FFFFFFFU)

/*! Standard ID filter element with filter + mask scheme. */
#define FLEXCAN_ENHANCED_RX_FIFO_STD_MASK_AND_FILTER(id, rtr, id_mask, rtr_mask) \
    (ENHANCED_RX_FIFO_FSCH(0x0) | RTR_STD_HIGH(rtr) | ID_STD_HIGH(id) | RTR_STD_LOW(rtr_mask) | ID_STD_LOW(id_mask))
/*! Standard ID filter element with filter range. */
#define FLEXCAN_ENHANCED_RX_FIFO_STD_FILTER_WITH_RANGE(id_upper, rtr, id_lower, rtr_mask)             \
    (ENHANCED_RX_FIFO_FSCH(0x1) | RTR_STD_HIGH(rtr) | ID_STD_HIGH(id_upper) | RTR_STD_LOW(rtr_mask) | \
     ID_STD_LOW(id_lower))
/*! Standard ID filter element with two filters without masks. */
#define FLEXCAN_ENHANCED_RX_FIFO_STD_TWO_FILTERS(id1, rtr1, id2, rtr2) \
    (ENHANCED_RX_FIFO_FSCH(0x2) | RTR_STD_HIGH(rtr1) | ID_STD_HIGH(id1) | RTR_STD_LOW(rtr2) | ID_STD_LOW(id2))
/*! Extended ID filter element with  filter + mask scheme low word. */
#define FLEXCAN_ENHANCED_RX_FIFO_EXT_MASK_AND_FILTER_LOW(id, rtr) \
    (ENHANCED_RX_FIFO_FSCH(0x0) | RTR_EXT(rtr) | ID_EXT(id))
/*! Extended ID filter element with  filter + mask scheme high word. */
#define FLEXCAN_ENHANCED_RX_FIFO_EXT_MASK_AND_FILTER_HIGH(id_mask, rtr_mask) \
    (ENHANCED_RX_FIFO_FSCH(0x0) | RTR_EXT(rtr_mask) | ID_EXT(id_mask))
/*! Extended ID filter element with range scheme low word. */
#define FLEXCAN_ENHANCED_RX_FIFO_EXT_FILTER_WITH_RANGE_LOW(id_upper, rtr) \
    (ENHANCED_RX_FIFO_FSCH(0x1) | RTR_EXT(rtr) | ID_EXT(id_upper))
/*! Extended ID filter element with range scheme high word. */
#define FLEXCAN_ENHANCED_RX_FIFO_EXT_FILTER_WITH_RANGE_HIGH(id_lower, rtr_mask) \
    (ENHANCED_RX_FIFO_FSCH(0x1) | RTR_EXT(rtr_mask) | ID_EXT(id_lower))
/*! Extended ID filter element with two filters without masks low word. */
#define FLEXCAN_ENHANCED_RX_FIFO_EXT_TWO_FILTERS_LOW(id2, rtr2) \
    (ENHANCED_RX_FIFO_FSCH(0x2) | RTR_EXT(rtr2) | ID_EXT(id2))
/*! Extended ID filter element with two filters without masks high word. */
#define FLEXCAN_ENHANCED_RX_FIFO_EXT_TWO_FILTERS_HIGH(id1, rtr1) \
    (ENHANCED_RX_FIFO_FSCH(0x2) | RTR_EXT(rtr1) | ID_EXT(id1))
#endif

#if (defined(FSL_FEATURE_FLEXCAN_HAS_PN_MODE) && FSL_FEATURE_FLEXCAN_HAS_PN_MODE)
/*! @brief FlexCAN Pretended Networking ID Mask helper macro. */
#define FLEXCAN_PN_STD_MASK(id, rtr)                            \
    ((uint32_t)((uint32_t)(rtr) << CAN_FLT_ID1_FLT_RTR_SHIFT) | \
     FLEXCAN_ID_STD(id)) /*!< Standard Rx Message Buffer Mask helper macro. */
#define FLEXCAN_PN_EXT_MASK(id, rtr)                                                                 \
    ((uint32_t)CAN_FLT_ID1_FLT_IDE_MASK | (uint32_t)((uint32_t)(rtr) << CAN_FLT_ID1_FLT_RTR_SHIFT) | \
     FLEXCAN_ID_EXT(id)) /*!< Extend Rx Message Buffer Mask helper macro. */
#endif

/*! @brief FlexCAN interrupt/status flag helper macro. */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_PN_MODE) && FSL_FEATURE_FLEXCAN_HAS_PN_MODE)
#define FLEXCAN_PN_INT_MASK(x)      (((uint64_t)(((uint64_t)(x)) << 32)) & 0x3000000000000U)
#define FLEXCAN_PN_INT_UNMASK(x)    (((uint32_t)(((uint64_t)(x)) >> 32)) & 0x00030000U)
#define FLEXCAN_PN_STATUS_MASK(x)   (((uint64_t)(((uint64_t)(x)) << 16)) & 0x300000000U)
#define FLEXCAN_PN_STATUS_UNMASK(x) (((uint32_t)(((uint64_t)(x)) >> 16)) & 0x00030000U)
#endif
#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
#define FLEXCAN_EFIFO_INT_MASK(x)      (((uint64_t)(((uint64_t)(x)) << 32)) & 0xF000000000000000U)
#define FLEXCAN_EFIFO_INT_UNMASK(x)    (((uint32_t)(((uint64_t)(x)) >> 32)) & 0xF0000000U)
#define FLEXCAN_EFIFO_STATUS_MASK(x)   (((uint64_t)(((uint64_t)(x)) << 32)) & 0xF003000000000000U)
#define FLEXCAN_EFIFO_STATUS_UNMASK(x) (((uint32_t)(((uint64_t)(x)) >> 32)) & 0xF0030000U)
#endif
#if (defined(FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL) && FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL)
#define FLEXCAN_MECR_INT_MASK(x)      (((uint64_t)(((uint64_t)(x)) << 16)) & 0xD00000000U)
#define FLEXCAN_MECR_INT_UNMASK(x)    (((uint32_t)(((uint64_t)(x)) >> 16)) & 0x000D0000U)
#define FLEXCAN_MECR_STATUS_MASK(x)   (((uint64_t)(((uint64_t)(x)) << 34)) & 0x34003400000000U)
#define FLEXCAN_MECR_STATUS_UNMASK(x) (((uint32_t)(((uint64_t)(x)) >> 34)) & 0x000D000DU)
#endif

#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
#define FLEXCAN_ERROR_AND_STATUS_INIT_FLAG                                                                            \
    ((uint32_t)kFLEXCAN_ErrorOverrunFlag | (uint32_t)kFLEXCAN_FDErrorIntFlag | (uint32_t)kFLEXCAN_BusoffDoneIntFlag | \
     (uint32_t)kFLEXCAN_TxWarningIntFlag | (uint32_t)kFLEXCAN_RxWarningIntFlag | (uint32_t)kFLEXCAN_BusOffIntFlag |   \
     (uint32_t)kFLEXCAN_ErrorIntFlag | FLEXCAN_MEMORY_ERROR_INIT_FLAG)
#else
#define FLEXCAN_ERROR_AND_STATUS_INIT_FLAG                                                                          \
    ((uint32_t)kFLEXCAN_TxWarningIntFlag | (uint32_t)kFLEXCAN_RxWarningIntFlag | (uint32_t)kFLEXCAN_BusOffIntFlag | \
     (uint32_t)kFLEXCAN_ErrorIntFlag | FLEXCAN_MEMORY_ERROR_INIT_FLAG)
#endif
#if (defined(FSL_FEATURE_FLEXCAN_HAS_PN_MODE) && FSL_FEATURE_FLEXCAN_HAS_PN_MODE)
#define FLEXCAN_WAKE_UP_FLAG \
    ((uint32_t)kFLEXCAN_WakeUpIntFlag | (uint64_t)kFLEXCAN_PNMatchIntFlag | (uint64_t)kFLEXCAN_PNTimeoutIntFlag)
#else
#define FLEXCAN_WAKE_UP_FLAG ((uint32_t)kFLEXCAN_WakeUpIntFlag)
#endif
#if (defined(FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL) && FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL)
#define FLEXCAN_MEMORY_ERROR_INIT_FLAG ((uint64_t)kFLEXCAN_AllMemoryErrorFlag)
#else
#define FLEXCAN_MEMORY_ERROR_INIT_FLAG (0U)
#endif

#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
#define FLEXCAN_MEMORY_ENHANCED_RX_FIFO_INIT_FLAG                                             \
    ((uint64_t)kFLEXCAN_ERxFifoUnderflowIntFlag | (uint64_t)kFLEXCAN_ERxFifoOverflowIntFlag | \
     (uint64_t)kFLEXCAN_ERxFifoWatermarkIntFlag | (uint64_t)kFLEXCAN_ERxFifoDataAvlIntFlag)
#define FLEXCAN_MEMORY_ENHANCED_RX_FIFO_INIT_MASK \
    (CAN_ERFIER_ERFUFWIE_MASK | CAN_ERFIER_ERFOVFIE_MASK | CAN_ERFIER_ERFWMIIE_MASK | CAN_ERFIER_ERFDAIE_MASK)
#endif

/*! @brief FlexCAN Enhanced Rx FIFO base address helper macro. */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
#define E_RX_FIFO(base) ((uint32_t)(base) + 0x2000U)
#endif
/*! @brief FlexCAN transfer status. */
enum
{
    kStatus_FLEXCAN_TxBusy       = MAKE_STATUS(kStatusGroup_FLEXCAN, 0), /*!< Tx Message Buffer is Busy. */
    kStatus_FLEXCAN_TxIdle       = MAKE_STATUS(kStatusGroup_FLEXCAN, 1), /*!< Tx Message Buffer is Idle. */
    kStatus_FLEXCAN_TxSwitchToRx = MAKE_STATUS(
        kStatusGroup_FLEXCAN, 2), /*!< Remote Message is send out and Message buffer changed to Receive one. */
    kStatus_FLEXCAN_RxBusy         = MAKE_STATUS(kStatusGroup_FLEXCAN, 3), /*!< Rx Message Buffer is Busy. */
    kStatus_FLEXCAN_RxIdle         = MAKE_STATUS(kStatusGroup_FLEXCAN, 4), /*!< Rx Message Buffer is Idle. */
    kStatus_FLEXCAN_RxOverflow     = MAKE_STATUS(kStatusGroup_FLEXCAN, 5), /*!< Rx Message Buffer is Overflowed. */
    kStatus_FLEXCAN_RxFifoBusy     = MAKE_STATUS(kStatusGroup_FLEXCAN, 6), /*!< Rx Message FIFO is Busy. */
    kStatus_FLEXCAN_RxFifoIdle     = MAKE_STATUS(kStatusGroup_FLEXCAN, 7), /*!< Rx Message FIFO is Idle. */
    kStatus_FLEXCAN_RxFifoOverflow = MAKE_STATUS(kStatusGroup_FLEXCAN, 8), /*!< Rx Message FIFO is overflowed. */
    kStatus_FLEXCAN_RxFifoWarning  = MAKE_STATUS(kStatusGroup_FLEXCAN, 9), /*!< Rx Message FIFO is almost overflowed. */
    kStatus_FLEXCAN_ErrorStatus    = MAKE_STATUS(kStatusGroup_FLEXCAN, 10), /*!< FlexCAN Module Error and Status. */
    kStatus_FLEXCAN_WakeUp         = MAKE_STATUS(kStatusGroup_FLEXCAN, 11), /*!< FlexCAN is waken up from STOP mode. */
    kStatus_FLEXCAN_UnHandled      = MAKE_STATUS(kStatusGroup_FLEXCAN, 12), /*!< UnHadled Interrupt asserted. */
    kStatus_FLEXCAN_RxRemote = MAKE_STATUS(kStatusGroup_FLEXCAN, 13), /*!< Rx Remote Message Received in Mail box. */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
    kStatus_FLEXCAN_RxFifoUnderflow =
        MAKE_STATUS(kStatusGroup_FLEXCAN, 14), /*!< Enhanced Rx Message FIFO is underflow. */
#endif
};

/*! @brief FlexCAN frame format. */
typedef enum _flexcan_frame_format
{
    kFLEXCAN_FrameFormatStandard = 0x0U, /*!< Standard frame format attribute. */
    kFLEXCAN_FrameFormatExtend   = 0x1U, /*!< Extend frame format attribute. */
} flexcan_frame_format_t;

/*! @brief FlexCAN frame type. */
typedef enum _flexcan_frame_type
{
    kFLEXCAN_FrameTypeData   = 0x0U, /*!< Data frame type attribute. */
    kFLEXCAN_FrameTypeRemote = 0x1U, /*!< Remote frame type attribute. */
} flexcan_frame_type_t;

/*! @brief FlexCAN clock source.
 *  @deprecated Do not use the kFLEXCAN_ClkSrcOs.  It has been superceded kFLEXCAN_ClkSrc0
 *  @deprecated Do not use the kFLEXCAN_ClkSrcPeri.  It has been superceded kFLEXCAN_ClkSrc1
 */
typedef enum _flexcan_clock_source
{
    kFLEXCAN_ClkSrcOsc  = 0x0U, /*!< FlexCAN Protocol Engine clock from Oscillator. */
    kFLEXCAN_ClkSrcPeri = 0x1U, /*!< FlexCAN Protocol Engine clock from Peripheral Clock. */
    kFLEXCAN_ClkSrc0    = 0x0U, /*!< FlexCAN Protocol Engine clock selected by user as SRC == 0. */
    kFLEXCAN_ClkSrc1    = 0x1U, /*!< FlexCAN Protocol Engine clock selected by user as SRC == 1. */
} flexcan_clock_source_t;

/*! @brief FlexCAN wake up source. */
typedef enum _flexcan_wake_up_source
{
    kFLEXCAN_WakeupSrcUnfiltered = 0x0U, /*!< FlexCAN uses unfiltered Rx input to detect edge. */
    kFLEXCAN_WakeupSrcFiltered   = 0x1U, /*!< FlexCAN uses filtered Rx input to detect edge. */
} flexcan_wake_up_source_t;

/*! @brief FlexCAN Rx Fifo Filter type. */
typedef enum _flexcan_rx_fifo_filter_type
{
    kFLEXCAN_RxFifoFilterTypeA = 0x0U, /*!< One full ID (standard and extended) per ID Filter element. */
    kFLEXCAN_RxFifoFilterTypeB =
        0x1U, /*!< Two full standard IDs or two partial 14-bit ID slices per ID Filter Table element. */
    kFLEXCAN_RxFifoFilterTypeC =
        0x2U, /*!< Four partial 8-bit Standard or extended ID slices per ID Filter Table element. */
    kFLEXCAN_RxFifoFilterTypeD = 0x3U, /*!< All frames rejected. */
} flexcan_rx_fifo_filter_type_t;

#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
/*!
 * @brief FlexCAN Message Buffer Payload size.
 */
typedef enum _flexcan_mb_size
{
    kFLEXCAN_8BperMB  = 0x0U, /*!< Selects 8 bytes per Message Buffer. */
    kFLEXCAN_16BperMB = 0x1U, /*!< Selects 16 bytes per Message Buffer. */
    kFLEXCAN_32BperMB = 0x2U, /*!< Selects 32 bytes per Message Buffer. */
    kFLEXCAN_64BperMB = 0x3U, /*!< Selects 64 bytes per Message Buffer. */
} flexcan_mb_size_t;

/*!
 * @brief FlexCAN CAN FD frame supporting data length (available DLC values).
 *
 * For Tx, when the Data size corresponding to DLC value stored in the MB selected for transmission is larger than the
 * MB Payload size, FlexCAN adds the necessary number of bytes with constant 0xCC pattern to complete the expected DLC.
 * For Rx, when the Data size corresponding to DLC value received from the CAN bus is larger than the MB Payload size,
 * the high order bytes that do not fit the Payload size will lose.
 */
enum _flexcan_fd_frame_length
{
    kFLEXCAN_0BperFrame = 0x0U, /*!< Frame contains 0 valid data bytes. */
    kFLEXCAN_1BperFrame,        /*!< Frame contains 1 valid data bytes. */
    kFLEXCAN_2BperFrame,        /*!< Frame contains 2 valid data bytes. */
    kFLEXCAN_3BperFrame,        /*!< Frame contains 3 valid data bytes. */
    kFLEXCAN_4BperFrame,        /*!< Frame contains 4 valid data bytes. */
    kFLEXCAN_5BperFrame,        /*!< Frame contains 5 valid data bytes. */
    kFLEXCAN_6BperFrame,        /*!< Frame contains 6 valid data bytes. */
    kFLEXCAN_7BperFrame,        /*!< Frame contains 7 valid data bytes. */
    kFLEXCAN_8BperFrame,        /*!< Frame contains 8 valid data bytes. */
    kFLEXCAN_12BperFrame,       /*!< Frame contains 12 valid data bytes. */
    kFLEXCAN_16BperFrame,       /*!< Frame contains 16 valid data bytes. */
    kFLEXCAN_20BperFrame,       /*!< Frame contains 20 valid data bytes. */
    kFLEXCAN_24Bperrame,        /*!< Frame contains 24 valid data bytes. */
    kFLEXCAN_32BperFrame,       /*!< Frame contains 32 valid data bytes. */
    kFLEXCAN_48BperFrame,       /*!< Frame contains 48 valid data bytes. */
    kFLEXCAN_64BperFrame,       /*!< Frame contains 64 valid data bytes. */
};
#endif

#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
/*! @brief FlexCAN Enhanced Rx Fifo DMA transfer per read length enumerations. */
typedef enum _flexcan_efifo_dma_per_read_length
{
    kFLEXCAN_1WordPerRead = 0x0U, /*!< Transfer 1 32-bit words (CS).*/
    kFLEXCAN_2WordPerRead,        /*!< Transfer 2 32-bit words (CS + ID).*/
    kFLEXCAN_3WordPerRead,        /*!< Transfer 3 32-bit words (CS + ID + 1~4 bytes data).*/
    kFLEXCAN_4WordPerRead,        /*!< Transfer 4 32-bit words (CS + ID + 5~8 bytes data).*/
    kFLEXCAN_5WordPerRead,        /*!< Transfer 5 32-bit words (CS + ID + 9~12 bytes data).*/
    kFLEXCAN_6WordPerRead,        /*!< Transfer 6 32-bit words (CS + ID + 13~16 bytes data).*/
    kFLEXCAN_7WordPerRead,        /*!< Transfer 7 32-bit words (CS + ID + 17~20 bytes data).*/
    kFLEXCAN_8WordPerRead,        /*!< Transfer 8 32-bit words (CS + ID + 21~24 bytes data).*/
    kFLEXCAN_9WordPerRead,        /*!< Transfer 9 32-bit words (CS + ID + 25~28 bytes data).*/
    kFLEXCAN_10WordPerRead,       /*!< Transfer 10 32-bit words (CS + ID + 29~32 bytes data).*/
    kFLEXCAN_11WordPerRead,       /*!< Transfer 11 32-bit words (CS + ID + 33~36 bytes data).*/
    kFLEXCAN_12WordPerRead,       /*!< Transfer 12 32-bit words (CS + ID + 37~40 bytes data).*/
    kFLEXCAN_13WordPerRead,       /*!< Transfer 13 32-bit words (CS + ID + 41~44 bytes data).*/
    kFLEXCAN_14WordPerRead,       /*!< Transfer 14 32-bit words (CS + ID + 45~48 bytes data).*/
    kFLEXCAN_15WordPerRead,       /*!< Transfer 15 32-bit words (CS + ID + 49~52 bytes data).*/
    kFLEXCAN_16WordPerRead,       /*!< Transfer 16 32-bit words (CS + ID + 53~56 bytes data).*/
    kFLEXCAN_17WordPerRead,       /*!< Transfer 17 32-bit words (CS + ID + 57~60 bytes data).*/
    kFLEXCAN_18WordPerRead,       /*!< Transfer 18 32-bit words (CS + ID + 61~64 bytes data).*/
    kFLEXCAN_19WordPerRead        /*!< Transfer 19 32-bit words (CS + ID + 64 bytes data + ID HIT).*/
} flexcan_efifo_dma_per_read_length_t;
#endif

/*!
 * @brief FlexCAN Enhanced/Legacy Rx FIFO priority.
 *
 * The matching process starts from the Rx MB(or Enhanced/Legacy Rx FIFO) with higher priority.
 * If no MB(or Enhanced/Legacy Rx FIFO filter) is satisfied, the matching process goes on with
 * the Enhanced/Legacy Rx FIFO(or Rx MB) with lower priority.
 */
typedef enum _flexcan_rx_fifo_priority
{
    kFLEXCAN_RxFifoPrioLow  = 0x0U, /*!< Matching process start from Rx Message Buffer first. */
    kFLEXCAN_RxFifoPrioHigh = 0x1U, /*!< Matching process start from Enhanced/Legacy Rx FIFO first. */
} flexcan_rx_fifo_priority_t;

/*!
 * @brief FlexCAN interrupt enable enumerations.
 *
 * This provides constants for the FlexCAN interrupt enable enumerations for use in the FlexCAN functions.
 * @note FlexCAN Message Buffers and Legacy Rx FIFO interrupts not included in.
 */
enum _flexcan_interrupt_enable
{
    kFLEXCAN_BusOffInterruptEnable    = CAN_CTRL1_BOFFMSK_MASK, /*!< Bus Off interrupt, use bit 15. */
    kFLEXCAN_ErrorInterruptEnable     = CAN_CTRL1_ERRMSK_MASK,  /*!< CAN Error interrupt, use bit 14. */
    kFLEXCAN_TxWarningInterruptEnable = CAN_CTRL1_TWRNMSK_MASK, /*!< Tx Warning interrupt, use bit 11. */
    kFLEXCAN_RxWarningInterruptEnable = CAN_CTRL1_RWRNMSK_MASK, /*!< Rx Warning interrupt, use bit 10. */
    kFLEXCAN_WakeUpInterruptEnable    = CAN_MCR_WAKMSK_MASK,    /*!< Self Wake Up interrupt, use bit 26. */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    kFLEXCAN_FDErrorInterruptEnable = CAN_CTRL2_ERRMSK_FAST_MASK, /*!< CAN FD Error interrupt, use bit 31. */
#endif
#if (defined(FSL_FEATURE_FLEXCAN_HAS_PN_MODE) && FSL_FEATURE_FLEXCAN_HAS_PN_MODE)
    /*! PN Match Wake Up interrupt, use high word bit 17. */
    kFLEXCAN_PNMatchWakeUpInterruptEnable = FLEXCAN_PN_INT_MASK(CAN_CTRL1_PN_WTOF_MSK_MASK),
    /*! PN Timeout Wake Up interrupt, use high word bit 16. */
    kFLEXCAN_PNTimeoutWakeUpInterruptEnable = FLEXCAN_PN_INT_MASK(CAN_CTRL1_PN_WUMF_MSK_MASK),
#endif
#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
    /*!< Enhanced Rx FIFO Underflow interrupt, use high word bit 31. */
    kFLEXCAN_ERxFifoUnderflowInterruptEnable = FLEXCAN_EFIFO_INT_MASK(CAN_ERFIER_ERFUFWIE_MASK),
    /*!< Enhanced Rx FIFO Overflow interrupt, use high word bit 30. */
    kFLEXCAN_ERxFifoOverflowInterruptEnable = FLEXCAN_EFIFO_INT_MASK(CAN_ERFIER_ERFOVFIE_MASK),
    /*!< Enhanced Rx FIFO Watermark interrupt, use high word bit 29. */
    kFLEXCAN_ERxFifoWatermarkInterruptEnable = FLEXCAN_EFIFO_INT_MASK(CAN_ERFIER_ERFWMIIE_MASK),
    /*!< Enhanced Rx FIFO Data Avilable interrupt, use high word bit 28. */
    kFLEXCAN_ERxFifoDataAvlInterruptEnable = FLEXCAN_EFIFO_INT_MASK(CAN_ERFIER_ERFDAIE_MASK),
#endif
#if (defined(FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL) && FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL)
    /*! Host Access With Non-Correctable Errors interrupt, use high word bit 0. */
    kFLEXCAN_HostAccessNCErrorInterruptEnable = FLEXCAN_MECR_INT_MASK(CAN_MECR_HANCEI_MSK_MASK),
    /*! FlexCAN Access With Non-Correctable Errors interrupt, use high word bit 2. */
    kFLEXCAN_FlexCanAccessNCErrorInterruptEnable = FLEXCAN_MECR_INT_MASK(CAN_MECR_FANCEI_MSK_MASK),
    /*! Host or FlexCAN Access With Correctable Errors interrupt, use high word bit 3. */
    kFLEXCAN_HostOrFlexCanCErrorInterruptEnable = FLEXCAN_MECR_INT_MASK(CAN_MECR_CEI_MSK_MASK),
#endif
};

/*!
 * @brief FlexCAN status flags.
 *
 * This provides constants for the FlexCAN status flags for use in the FlexCAN functions.
 * @note The CPU read action clears the bits corresponding to the FlEXCAN_ErrorFlag macro, therefore user need to
 * read status flags and distinguish which error is occur using @ref _flexcan_error_flags enumerations.
 */
enum _flexcan_flags
{
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    kFLEXCAN_ErrorOverrunFlag  = CAN_ESR1_ERROVR_MASK,      /*!< Error Overrun Status. */
    kFLEXCAN_FDErrorIntFlag    = CAN_ESR1_ERRINT_FAST_MASK, /*!< CAN FD Error Interrupt Flag. */
    kFLEXCAN_BusoffDoneIntFlag = CAN_ESR1_BOFFDONEINT_MASK, /*!< Bus Off process completed Interrupt Flag. */
#endif
    kFLEXCAN_SynchFlag            = CAN_ESR1_SYNCH_MASK,   /*!< CAN Synchronization Status. */
    kFLEXCAN_TxWarningIntFlag     = CAN_ESR1_TWRNINT_MASK, /*!< Tx Warning Interrupt Flag. */
    kFLEXCAN_RxWarningIntFlag     = CAN_ESR1_RWRNINT_MASK, /*!< Rx Warning Interrupt Flag. */
    kFLEXCAN_IdleFlag             = CAN_ESR1_IDLE_MASK,    /*!< FlexCAN In IDLE Status. */
    kFLEXCAN_FaultConfinementFlag = CAN_ESR1_FLTCONF_MASK, /*!< FlexCAN Fault Confinement State. */
    kFLEXCAN_TransmittingFlag     = CAN_ESR1_TX_MASK,      /*!< FlexCAN In Transmission Status. */
    kFLEXCAN_ReceivingFlag        = CAN_ESR1_RX_MASK,      /*!< FlexCAN In Reception Status. */
    kFLEXCAN_BusOffIntFlag        = CAN_ESR1_BOFFINT_MASK, /*!< Bus Off Interrupt Flag. */
    kFLEXCAN_ErrorIntFlag         = CAN_ESR1_ERRINT_MASK,  /*!< CAN Error Interrupt Flag. */
    kFLEXCAN_WakeUpIntFlag        = CAN_ESR1_WAKINT_MASK,  /*!< Self Wake-Up Interrupt Flag. */
    kFLEXCAN_ErrorFlag =
        (uint32_t)(/*!< All FlexCAN Read Clear Error Status. */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
                   CAN_ESR1_STFERR_FAST_MASK | CAN_ESR1_FRMERR_FAST_MASK | CAN_ESR1_CRCERR_FAST_MASK |
                   CAN_ESR1_BIT0ERR_FAST_MASK | CAN_ESR1_BIT1ERR_FAST_MASK | CAN_ESR1_ERROVR_MASK |
#endif
                   CAN_ESR1_TXWRN_MASK | CAN_ESR1_RXWRN_MASK | CAN_ESR1_BIT1ERR_MASK | CAN_ESR1_BIT0ERR_MASK |
                   CAN_ESR1_ACKERR_MASK | CAN_ESR1_CRCERR_MASK | CAN_ESR1_FRMERR_MASK | CAN_ESR1_STFERR_MASK),
#if (defined(FSL_FEATURE_FLEXCAN_HAS_PN_MODE) && FSL_FEATURE_FLEXCAN_HAS_PN_MODE)
    kFLEXCAN_PNMatchIntFlag   = FLEXCAN_PN_STATUS_MASK(CAN_WU_MTC_WUMF_MASK), /*!< PN Matching Event Interrupt Flag. */
    kFLEXCAN_PNTimeoutIntFlag = FLEXCAN_PN_STATUS_MASK(CAN_WU_MTC_WTOF_MASK), /*!< PN Timeout Event Interrupt Flag. */
#endif
#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
    kFLEXCAN_ERxFifoUnderflowIntFlag =
        FLEXCAN_EFIFO_STATUS_MASK(CAN_ERFSR_ERFUFW_MASK), /*!< Enhanced Rx FIFO underflow Interrupt Flag. */
    kFLEXCAN_ERxFifoOverflowIntFlag =
        FLEXCAN_EFIFO_STATUS_MASK(CAN_ERFSR_ERFOVF_MASK), /*!< Enhanced Rx FIFO overflow Interrupt Flag. */
    kFLEXCAN_ERxFifoWatermarkIntFlag =
        FLEXCAN_EFIFO_STATUS_MASK(CAN_ERFSR_ERFWMI_MASK), /*!< Enhanced Rx FIFO watermark Interrupt Flag. */
    kFLEXCAN_ERxFifoDataAvlIntFlag =
        FLEXCAN_EFIFO_STATUS_MASK(CAN_ERFSR_ERFDA_MASK), /*!< Enhanced Rx FIFO data available Interrupt Flag. */
    kFLEXCAN_ERxFifoEmptyFlag = FLEXCAN_EFIFO_STATUS_MASK(CAN_ERFSR_ERFE_MASK), /*!< Enhanced Rx FIFO empty status. */
    kFLEXCAN_ERxFifoFullFlag  = FLEXCAN_EFIFO_STATUS_MASK(CAN_ERFSR_ERFF_MASK), /*!< Enhanced Rx FIFO full status. */
#endif
#if (defined(FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL) && FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL)
    /*! Host Access With Non-Correctable Error Interrupt Flag. */
    kFLEXCAN_HostAccessNonCorrectableErrorIntFlag = FLEXCAN_MECR_INT_MASK(CAN_ERRSR_HANCEIF_MASK),
    /*! FlexCAN Access With Non-Correctable Error Interrupt Flag. */
    kFLEXCAN_FlexCanAccessNonCorrectableErrorIntFlag = FLEXCAN_MECR_INT_MASK(CAN_ERRSR_FANCEIF_MASK),
    /*! Correctable Error Interrupt Flag. */
    kFLEXCAN_CorrectableErrorIntFlag = FLEXCAN_MECR_INT_MASK(CAN_ERRSR_CEIF_MASK),
    /*! Host Access With Non-Correctable Error Interrupt Overrun Flag. */
    kFLEXCAN_HostAccessNonCorrectableErrorOverrunFlag = FLEXCAN_MECR_INT_MASK(CAN_ERRSR_HANCEIOF_MASK),
    /*! FlexCAN Access With Non-Correctable Error Interrupt Overrun Flag. */
    kFLEXCAN_FlexCanAccessNonCorrectableErrorOverrunFlag = FLEXCAN_MECR_INT_MASK(CAN_ERRSR_FANCEIOF_MASK),
    /*! Correctable Error Interrupt Overrun Flag. */
    kFLEXCAN_CorrectableErrorOverrunFlag = FLEXCAN_MECR_INT_MASK(CAN_ERRSR_CEIOF_MASK),
    /*! All Memory Error Flags. */
    kFLEXCAN_AllMemoryErrorFlag =
        (kFLEXCAN_HostAccessNonCorrectableErrorIntFlag | kFLEXCAN_FlexCanAccessNonCorrectableErrorIntFlag |
         kFLEXCAN_CorrectableErrorIntFlag | kFLEXCAN_HostAccessNonCorrectableErrorOverrunFlag |
         kFLEXCAN_FlexCanAccessNonCorrectableErrorOverrunFlag | kFLEXCAN_CorrectableErrorOverrunFlag)
#endif
};

/*!
 * @brief FlexCAN error status flags.
 *
 * The FlexCAN Error Status enumerations is used to report current error of the FlexCAN bus.
 * This enumerations should be used with KFLEXCAN_ErrorFlag in @ref _flexcan_flags enumerations
 * to ditermine which error is generated.
 */
enum _flexcan_error_flags
{
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    kFLEXCAN_FDStuffingError = CAN_ESR1_STFERR_FAST_MASK,       /*!< Stuffing Error. */
    kFLEXCAN_FDFormError     = CAN_ESR1_FRMERR_FAST_MASK,       /*!< Form Error. */
    kFLEXCAN_FDCrcError      = CAN_ESR1_CRCERR_FAST_MASK,       /*!< Cyclic Redundancy Check Error. */
    kFLEXCAN_FDBit0Error     = CAN_ESR1_BIT0ERR_FAST_MASK,      /*!< Unable to send dominant bit. */
    kFLEXCAN_FDBit1Error     = (int)CAN_ESR1_BIT1ERR_FAST_MASK, /*!< Unable to send recessive bit. */
#endif
    kFLEXCAN_TxErrorWarningFlag = CAN_ESR1_TXWRN_MASK,   /*!< Tx Error Warning Status. */
    kFLEXCAN_RxErrorWarningFlag = CAN_ESR1_RXWRN_MASK,   /*!< Rx Error Warning Status. */
    kFLEXCAN_StuffingError      = CAN_ESR1_STFERR_MASK,  /*!< Stuffing Error. */
    kFLEXCAN_FormError          = CAN_ESR1_FRMERR_MASK,  /*!< Form Error. */
    kFLEXCAN_CrcError           = CAN_ESR1_CRCERR_MASK,  /*!< Cyclic Redundancy Check Error. */
    kFLEXCAN_AckError           = CAN_ESR1_ACKERR_MASK,  /*!< Received no ACK on transmission. */
    kFLEXCAN_Bit0Error          = CAN_ESR1_BIT0ERR_MASK, /*!< Unable to send dominant bit. */
    kFLEXCAN_Bit1Error          = CAN_ESR1_BIT1ERR_MASK, /*!< Unable to send recessive bit. */
};

/*!
 * @brief FlexCAN Legacy Rx FIFO status flags.
 *
 * The FlexCAN Legacy Rx FIFO Status enumerations are used to determine the status of the
 * Rx FIFO. Because Rx FIFO occupy the MB0 ~ MB7 (Rx Fifo filter also occupies
 * more Message Buffer space), Rx FIFO status flags are mapped to the corresponding
 * Message Buffer status flags.
 */
enum
{
    kFLEXCAN_RxFifoOverflowFlag = CAN_IFLAG1_BUF7I_MASK, /*!< Rx FIFO overflow flag. */
    kFLEXCAN_RxFifoWarningFlag  = CAN_IFLAG1_BUF6I_MASK, /*!< Rx FIFO almost full flag. */
    kFLEXCAN_RxFifoFrameAvlFlag = CAN_IFLAG1_BUF5I_MASK, /*!< Frames available in Rx FIFO flag. */
};

#if (defined(FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL) && FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL)
/*!
 * @brief FlexCAN Memory Error Type.
 */
typedef enum _flexcan_memory_error_type
{
    kFLEXCAN_CorrectableError = 0U, /*!< The memory error is correctable which means on bit error. */
    kFLEXCAN_NonCorrectableError    /*!< The memory error is non-correctable which means two bit errors. */
} flexcan_memory_error_type_t;

/*!
 * @brief FlexCAN Memory Access Type.
 */
typedef enum _flexcan_memory_access_type
{
    kFLEXCAN_MoveOutFlexCanAccess = 0U, /*!< The memory error was detected during move-out FlexCAN access. */
    kFLEXCAN_MoveInAccess,              /*!< The memory error was detected during move-in FlexCAN access. */
    kFLEXCAN_TxArbitrationAccess,       /*!< The memory error was detected during Tx Arbitration FlexCAN access. */
    kFLEXCAN_RxMatchingAccess,          /*!< The memory error was detected during Rx Matching FlexCAN access. */
    kFLEXCAN_MoveOutHostAccess          /*!< The memory error was detected during Rx Matching Host (CPU) access. */
} flexcan_memory_access_type_t;

/*!
 * @brief FlexCAN Memory Error Byte Syndrome.
 */
typedef enum _flexcan_byte_error_syndrome
{
    kFLEXCAN_NoError          = 0U,  /*!< No bit error in this byte. */
    kFLEXCAN_ParityBits0Error = 1U,  /*!< Parity bit 0 error in this byte. */
    kFLEXCAN_ParityBits1Error = 2U,  /*!< Parity bit 1 error in this byte. */
    kFLEXCAN_ParityBits2Error = 4U,  /*!< Parity bit 2 error in this byte. */
    kFLEXCAN_ParityBits3Error = 8U,  /*!< Parity bit 3 error in this byte. */
    kFLEXCAN_ParityBits4Error = 16U, /*!< Parity bit 4 error in this byte. */
    kFLEXCAN_DataBits0Error   = 28U, /*!< Data bit 0 error in this byte. */
    kFLEXCAN_DataBits1Error   = 22U, /*!< Data bit 1 error in this byte. */
    kFLEXCAN_DataBits2Error   = 19U, /*!< Data bit 2 error in this byte. */
    kFLEXCAN_DataBits3Error   = 25U, /*!< Data bit 3 error in this byte. */
    kFLEXCAN_DataBits4Error   = 26U, /*!< Data bit 4 error in this byte. */
    kFLEXCAN_DataBits5Error   = 7U,  /*!< Data bit 5 error in this byte. */
    kFLEXCAN_DataBits6Error   = 21U, /*!< Data bit 6 error in this byte. */
    kFLEXCAN_DataBits7Error   = 14U, /*!< Data bit 7 error in this byte. */
    kFLEXCAN_AllZeroError     = 6U,  /*!< All-zeros non-correctable error in this byte. */
    kFLEXCAN_AllOneError      = 31U, /*!< All-ones non-correctable error in this byte. */
    kFLEXCAN_NonCorrectableErrors    /*!< Non-correctable error in this byte. */
} flexcan_byte_error_syndrome_t;

/*!
 * @brief FlexCAN memory error register status structure
 *
 * This structure contains the memory access properties that caused a memory error access.
 * It is used as the parameter of FLEXCAN_GetMemoryErrorReportStatus() function. And user can
 * use FLEXCAN_GetMemoryErrorReportStatus to get the status of the last memory error access.
 */
typedef struct _flexcan_memory_error_report_status
{
    flexcan_memory_error_type_t errorType;   /*!< The type of memory error that giving rise to the report. */
    flexcan_memory_access_type_t accessType; /*!< The type of memory access that giving rise to the memory error. */
    uint16_t accessAddress;                  /*!< The address where memory error detected. */
    uint32_t errorData;                      /*!< The raw data word read from memory with error. */
    struct
    {
        bool byteIsRead; /*!< The byte n (0~3) was read or not. */
        /*!< The type of error and which bit in byte (n) is affected by the error. */
        flexcan_byte_error_syndrome_t bitAffected;
    } byteStatus[4];
} flexcan_memory_error_report_status_t;
#endif

#if defined(__CC_ARM)
#pragma anon_unions
#endif
/*! @brief FlexCAN message frame structure. */
typedef struct _flexcan_frame
{
    struct
    {
        uint32_t timestamp : 16; /*!< FlexCAN internal Free-Running Counter Time Stamp. */
        uint32_t length : 4;     /*!< CAN frame data length in bytes (Range: 0~8). */
        uint32_t type : 1;       /*!< CAN Frame Type(DATA or REMOTE). */
        uint32_t format : 1;     /*!< CAN Frame Identifier(STD or EXT format). */
        uint32_t : 1;            /*!< Reserved. */
        uint32_t idhit : 9;      /*!< CAN Rx FIFO filter hit id(This value is only used in Rx FIFO receive mode). */
    };
    struct
    {
        uint32_t id : 29; /*!< CAN Frame Identifier, should be set using FLEXCAN_ID_EXT() or FLEXCAN_ID_STD() macro. */
        uint32_t : 3;     /*!< Reserved. */
    };
    union
    {
        struct
        {
            uint32_t dataWord0; /*!< CAN Frame payload word0. */
            uint32_t dataWord1; /*!< CAN Frame payload word1. */
        };
        struct
        {
            uint8_t dataByte3; /*!< CAN Frame payload byte3. */
            uint8_t dataByte2; /*!< CAN Frame payload byte2. */
            uint8_t dataByte1; /*!< CAN Frame payload byte1. */
            uint8_t dataByte0; /*!< CAN Frame payload byte0. */
            uint8_t dataByte7; /*!< CAN Frame payload byte7. */
            uint8_t dataByte6; /*!< CAN Frame payload byte6. */
            uint8_t dataByte5; /*!< CAN Frame payload byte5. */
            uint8_t dataByte4; /*!< CAN Frame payload byte4. */
        };
    };
} flexcan_frame_t;

#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
/*! @brief CAN FD message frame structure.
 *
 * The CAN FD message supporting up to sixty four bytes can be used for a data frame, depending on the length
 * selected for the message buffers. The length should be a enumeration member, see @ref _flexcan_fd_frame_length.
 */
typedef struct _flexcan_fd_frame
{
    struct
    {
        uint32_t timestamp : 16; /*!< FlexCAN internal Free-Running Counter Time Stamp. */
        uint32_t length : 4; /*!< CAN FD frame data length code (DLC), range see @ref _flexcan_fd_frame_length, When the
                                length <= 8, it equal to the data length, otherwise the number of valid frame data is
                                not equal to the length value.  user can
                                use DLC_LENGTH_DECODE(length) macro to get the number of valid data bytes. */
        uint32_t type : 1;   /*!< CAN Frame Type(DATA or REMOTE). */
        uint32_t format : 1; /*!< CAN Frame Identifier(STD or EXT format). */
        uint32_t srr : 1;    /*!< Substitute Remote request. */
        uint32_t : 6;
        uint32_t esi : 1; /*!< Error State Indicator. */
        uint32_t brs : 1; /*!< Bit Rate Switch. */
        uint32_t edl : 1; /*!< Extended Data Length. */
    };
    struct
    {
        uint32_t id : 29; /*!< CAN Frame Identifier, should be set using FLEXCAN_ID_EXT() or FLEXCAN_ID_STD() macro. */
        uint32_t : 3;     /*!< Reserved. */
    };
    union
    {
        struct
        {
            uint32_t dataWord[16]; /*!< CAN FD Frame payload, 16 double word maximum. */
        };
        /* Note: the maximum databyte* below is actually 64, user can add them if needed,
           or just use dataWord[*] instead. */
        struct
        {
            uint8_t dataByte3; /*!< CAN Frame payload byte3. */
            uint8_t dataByte2; /*!< CAN Frame payload byte2. */
            uint8_t dataByte1; /*!< CAN Frame payload byte1. */
            uint8_t dataByte0; /*!< CAN Frame payload byte0. */
            uint8_t dataByte7; /*!< CAN Frame payload byte7. */
            uint8_t dataByte6; /*!< CAN Frame payload byte6. */
            uint8_t dataByte5; /*!< CAN Frame payload byte5. */
            uint8_t dataByte4; /*!< CAN Frame payload byte4. */
        };
    };
#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
    /*! @note ID HIT offset is changed dynamically according to data length code (DLC), when DLC is 15, they will be
     * located below. Using FLEXCAN_FixEnhancedRxFifoFrameIdHit API is recommended to ensure this idhit value is
     * correct.*/
    uint32_t idhit; /*!< CAN Enhanced Rx FIFO filter hit id (This value is only used in Enhanced Rx FIFO receive
                       mode). */
#endif
} flexcan_fd_frame_t;
#endif

/*! @brief FlexCAN protocol timing characteristic configuration structure. */
typedef struct _flexcan_timing_config
{
    uint16_t preDivider; /*!< Classic CAN or CAN FD nominal phase bit rate prescaler. */
    uint8_t rJumpwidth;  /*!< Classic CAN or CAN FD nominal phase Re-sync Jump Width. */
    uint8_t phaseSeg1;   /*!< Classic CAN or CAN FD nominal phase Segment 1. */
    uint8_t phaseSeg2;   /*!< Classic CAN or CAN FD nominal phase Segment 2. */
    uint8_t propSeg;     /*!< Classic CAN or CAN FD nominal phase Propagation Segment. */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    uint16_t fpreDivider; /*!< CAN FD data phase bit rate prescaler. */
    uint8_t frJumpwidth;  /*!< CAN FD data phase Re-sync Jump Width. */
    uint8_t fphaseSeg1;   /*!< CAN FD data phase Phase Segment 1. */
    uint8_t fphaseSeg2;   /*!< CAN FD data phase Phase Segment 2. */
    uint8_t fpropSeg;     /*!< CAN FD data phase Propagation Segment. */
#endif
} flexcan_timing_config_t;

/*! @brief FlexCAN module configuration structure.
 *  @deprecated Do not use the baudRate. It has been superceded bitRate
 *  @deprecated Do not use the baudRateFD. It has been superceded bitRateFD
 */
typedef struct _flexcan_config
{
    union
    {
        struct
        {
            uint32_t baudRate; /*!< FlexCAN bit rate in bps, for classical CAN or CANFD nominal phase. */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
            uint32_t baudRateFD; /*!< FlexCAN FD bit rate in bps, for CANFD data phase. */
#endif
        };
        struct
        {
            uint32_t bitRate; /*!< FlexCAN bit rate in bps, for classical CAN or CANFD nominal phase. */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
            uint32_t bitRateFD; /*!< FlexCAN FD bit rate in bps, for CANFD data phase. */
#endif
        };
    };
    flexcan_clock_source_t clkSrc;      /*!< Clock source for FlexCAN Protocol Engine. */
    flexcan_wake_up_source_t wakeupSrc; /*!< Wake up source selection. */
    uint8_t maxMbNum;                   /*!< The maximum number of Message Buffers used by user. */
    bool enableLoopBack;                /*!< Enable or Disable Loop Back Self Test Mode. */
    bool enableTimerSync;               /*!< Enable or Disable Timer Synchronization. */
    bool enableSelfWakeup;              /*!< Enable or Disable Self Wakeup Mode. */
    bool enableIndividMask;             /*!< Enable or Disable Rx Individual Mask and Queue feature. */
    bool disableSelfReception;          /*!< Enable or Disable Self Reflection. */
    bool enableListenOnlyMode;          /*!< Enable or Disable Listen Only Mode. */
#if !(defined(FSL_FEATURE_FLEXCAN_HAS_NO_SUPV_SUPPORT) && FSL_FEATURE_FLEXCAN_HAS_NO_SUPV_SUPPORT)
    bool enableSupervisorMode; /*!< Enable or Disable Supervisor Mode, enable this mode will make registers allow only
                                  Supervisor access. */
#endif
#if (defined(FSL_FEATURE_FLEXCAN_HAS_DOZE_MODE_SUPPORT) && FSL_FEATURE_FLEXCAN_HAS_DOZE_MODE_SUPPORT)
    bool enableDoze; /*!< Enable or Disable Doze Mode. */
#endif
#if (defined(FSL_FEATURE_FLEXCAN_HAS_PN_MODE) && FSL_FEATURE_FLEXCAN_HAS_PN_MODE)
    bool enablePretendedeNetworking; /*!< Enable or Disable the Pretended Networking mode. */
#endif
#if (defined(FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL) && FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL)
    bool enableMemoryErrorControl; /*!< Enable or Disable the memory errors detection and correction mechanism. */
    bool enableNonCorrectableErrorEnterFreeze; /*!< Enable or Disable Non-Correctable Errors In FlexCAN Access Put
                                                    Device In Freeze Mode. */
#endif
#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_BIT_TIMING_REG) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_BIT_TIMING_REG)
    bool enableTransceiverDelayMeasure; /*!< Enable or Disable the transceiver delay measurement, when it is enabled,
                                             then the secondary sample point position is determined by the sum of the
                                             transceiver delay measurement plus the enhanced TDC offset. */
#endif
    flexcan_timing_config_t timingConfig; /* Protocol timing . */
} flexcan_config_t;

/*!
 * @brief FlexCAN Receive Message Buffer configuration structure
 *
 * This structure is used as the parameter of FLEXCAN_SetRxMbConfig() function.
 * The FLEXCAN_SetRxMbConfig() function is used to configure FlexCAN Receive
 * Message Buffer. The function abort previous receiving process, clean the
 * Message Buffer and activate the Rx Message Buffer using given Message Buffer
 * setting.
 */
typedef struct _flexcan_rx_mb_config
{
    uint32_t id;                   /*!< CAN Message Buffer Frame Identifier, should be set using
                                        FLEXCAN_ID_EXT() or FLEXCAN_ID_STD() macro. */
    flexcan_frame_format_t format; /*!< CAN Frame Identifier format(Standard of Extend). */
    flexcan_frame_type_t type;     /*!< CAN Frame Type(Data or Remote). */
} flexcan_rx_mb_config_t;

#if (defined(FSL_FEATURE_FLEXCAN_HAS_PN_MODE) && FSL_FEATURE_FLEXCAN_HAS_PN_MODE)
/*! @brief FlexCAN Pretended Networking match source selection. */
typedef enum _flexcan_pn_match_source
{
    kFLEXCAN_PNMatSrcID = 0U,   /*!< Message match with ID filtering. */
    kFLEXCAN_PNMatSrcIDAndData, /*!< Message match with ID filtering and payload filtering. */
} flexcan_pn_match_source_t;

/*! @brief FlexCAN Pretended Networking mode match type. */
typedef enum _flexcan_pn_match_mode
{
    kFLEXCAN_PNMatModeEqual = 0x0U, /*!< Match upon ID/Payload contents against an exact target value. */
    kFLEXCAN_PNMatModeGreater, /*!< Match upon an ID/Payload value greater than or equal to a specified target value.
                                */
    kFLEXCAN_PNMatModeSmaller, /*!< Match upon an ID/Payload value smaller than or equal to a specified target value.
                                */
    kFLEXCAN_PNMatModeRange,   /*!< Match upon an ID/Payload value inside a range, greater than or equal to a specified
                                lower limit, and smaller than or equal to a specified upper limit */
} flexcan_pn_match_mode_t;

/*!
 * @brief FlexCAN Pretended Networking configuration structure
 *
 * This structure is used as the parameter of FLEXCAN_SetPNConfig() function.
 * The FLEXCAN_SetPNConfig() function is used to configure FlexCAN Networking work mode.
 */
typedef struct _flexcan_pn_config
{
    bool enableTimeout;    /*!< Enable or Disable timeout event trigger wakeup.*/
    uint16_t timeoutValue; /*!< The timeout value that generates a wakeup event, the counter timer is incremented based
                             on 64 times the CAN Bit Time unit. */
    bool enableMatch;      /*!< Enable or Disable match event trigger wakeup.*/
    flexcan_pn_match_source_t matchSrc; /*!< Selects the match source (ID and/or data match) to trigger wakeup. */
    uint8_t matchNum; /*!< The number of times a given message must match the predefined ID and/or data before
                         generating a wakeup event, range in 0x1 ~ 0xFF. */
    flexcan_pn_match_mode_t idMatchMode;   /*!< The ID match type. */
    flexcan_pn_match_mode_t dataMatchMode; /*!< The data match type. */
    uint32_t idLower;    /*!< The ID target values 1 which used either for ID match "equal to", "smaller than",
                          "greater than" comparisons, or as the lower limit value in ID match "range detection". */
    uint32_t idUpper;    /*!< The ID target values 2 which used only as the upper limit value in ID match "range
                                detection" or used to store the ID mask in "equal to". */
    uint8_t lengthLower; /*!< The lower limit for length of data bytes which used only in data match "range
                                detection". Range in 0x0 ~ 0x8.*/
    uint8_t lengthUpper; /*!< The upper limit for length of data bytes which used only in data match "range
                                detection". Range in 0x0 ~ 0x8.*/
    union
    {
        /*!< The data target values 1 which used either for data match "equal to", "smaller than",
                                   "greater than" comparisons, or as the lower limit value in data match "range
           detection". */
        struct
        {
            uint32_t lowerWord0; /*!< CAN Frame payload word0. */
            uint32_t lowerWord1; /*!< CAN Frame payload word1. */
        };
        struct
        {
            uint8_t lowerByte3; /*!< CAN Frame payload byte3. */
            uint8_t lowerByte2; /*!< CAN Frame payload byte2. */
            uint8_t lowerByte1; /*!< CAN Frame payload byte1. */
            uint8_t lowerByte0; /*!< CAN Frame payload byte0. */
            uint8_t lowerByte7; /*!< CAN Frame payload byte7. */
            uint8_t lowerByte6; /*!< CAN Frame payload byte6. */
            uint8_t lowerByte5; /*!< CAN Frame payload byte5. */
            uint8_t lowerByte4; /*!< CAN Frame payload byte4. */
        };
    };
    union
    {
        /*!< The data target values 2 which used only as the upper limit value in data match "range
                                    detection" or used to store the data mask in "equal to". */
        struct
        {
            uint32_t upperWord0; /*!< CAN Frame payload word0. */
            uint32_t upperWord1; /*!< CAN Frame payload word1. */
        };
        struct
        {
            uint8_t upperByte3; /*!< CAN Frame payload byte3. */
            uint8_t upperByte2; /*!< CAN Frame payload byte2. */
            uint8_t upperByte1; /*!< CAN Frame payload byte1. */
            uint8_t upperByte0; /*!< CAN Frame payload byte0. */
            uint8_t upperByte7; /*!< CAN Frame payload byte7. */
            uint8_t upperByte6; /*!< CAN Frame payload byte6. */
            uint8_t upperByte5; /*!< CAN Frame payload byte5. */
            uint8_t upperByte4; /*!< CAN Frame payload byte4. */
        };
    };
} flexcan_pn_config_t;
#endif

/*! @brief FlexCAN Legacy Rx FIFO configuration structure. */
typedef struct _flexcan_rx_fifo_config
{
    uint32_t *idFilterTable;                    /*!< Pointer to the FlexCAN Legacy Rx FIFO identifier filter table. */
    uint8_t idFilterNum;                        /*!< The FlexCAN Legacy Rx FIFO Filter elements quantity. */
    flexcan_rx_fifo_filter_type_t idFilterType; /*!< The FlexCAN Legacy Rx FIFO Filter type. */
    flexcan_rx_fifo_priority_t priority;        /*!< The FlexCAN Legacy Rx FIFO receive priority. */
} flexcan_rx_fifo_config_t;

#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
/*! @brief FlexCAN Enhanced Rx FIFO Standard ID filter element structure. */
typedef struct _flexcan_enhanced_rx_fifo_std_id_filter
{
    uint32_t filterType : 2; /*!< FlexCAN internal Free-Running Counter Time Stamp. */
    uint32_t : 2;
    uint32_t rtr1 : 1;  /*!< CAN FD frame data length code (DLC), range see @ref _flexcan_fd_frame_length, When the
                             length <= 8, it equal to the data length, otherwise the number of valid frame data is
                             not equal to the length value.  user can
                             use DLC_LENGTH_DECODE(length) macro to get the number of valid data bytes. */
    uint32_t std1 : 11; /*!< CAN Frame Type(DATA or REMOTE). */
    uint32_t : 4;
    uint32_t rtr2 : 1;  /*!< CAN Frame Identifier(STD or EXT format). */
    uint32_t std2 : 11; /*!< Substitute Remote request. */
} flexcan_enhanced_rx_fifo_std_id_filter_t;

/*! @brief FlexCAN Enhanced Rx FIFO Extended ID filter element structure. */
typedef struct _flexcan_enhanced_rx_fifo_ext_id_filter
{
    uint32_t filterType : 2; /*!< FlexCAN internal Free-Running Counter Time Stamp. */
    uint32_t rtr1 : 1;       /*!< CAN FD frame data length code (DLC), range see @ref _flexcan_fd_frame_length, When the
                                  length <= 8, it equal to the data length, otherwise the number of valid frame data is
                                  not equal to the length value.  user can
                                  use DLC_LENGTH_DECODE(length) macro to get the number of valid data bytes. */
    uint32_t std1 : 29;      /*!< CAN Frame Type(DATA or REMOTE). */
    uint32_t : 2;
    uint32_t rtr2 : 1;  /*!< CAN Frame Identifier(STD or EXT format). */
    uint32_t std2 : 29; /*!< Substitute Remote request. */
} flexcan_enhanced_rx_fifo_ext_id_filter_t;
/*! @brief FlexCAN Enhanced Rx FIFO configuration structure. */
typedef struct _flexcan_enhanced_rx_fifo_config
{
    uint32_t *idFilterTable; /*!< Pointer to the FlexCAN Enhanced Rx FIFO identifier filter table, each table member
                             occupies 32 bit word, table size should be equal to idFilterNum. There are two types of
                           Enhanced Rx FIFO filter elements that can be stored in table : extended-ID filter element
                           (1 word, occupie 1 table members) and standard-ID filter element (2 words, occupies 2 table
                           members), the extended-ID filter element needs to be placed in front of the table. */
    uint8_t idFilterPairNum; /*!< (idFilterPairNum + 1) is the Enhanced Rx FIFO identifier filter element pair numbers,
                                each pair of filter elements occupies 2 words and can consist of one extended ID filter
                                element or two standard ID filter elements. */
    uint8_t extendIdFilterNum; /*!< The number of extended ID filter element items in the FlexCAN enhanced Rx FIFO
                                  identifier filter table, each extended-ID filter element occupies 2 words,
                                  extendIdFilterNum need less than or equal to (idFilterPairNum + 1). */
    uint8_t fifoWatermark; /*!< (fifoWatermark + 1) is the minimum number of CAN messages stored in the Enhanced RX FIFO
                              which can trigger FIFO watermark interrupt or a DMA request. */
    flexcan_efifo_dma_per_read_length_t dmaPerReadLength; /*!< Define the length of each read of the Enhanced RX FIFO
                                                             element by the DAM, see @ref _flexcan_fd_frame_length. */
    flexcan_rx_fifo_priority_t priority;                  /*!< The FlexCAN Enhanced Rx FIFO receive priority. */
} flexcan_enhanced_rx_fifo_config_t;
#endif

/*! @brief FlexCAN Message Buffer transfer. */
typedef struct _flexcan_mb_transfer
{
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    flexcan_fd_frame_t *framefd;
#endif
    flexcan_frame_t *frame; /*!< The buffer of CAN Message to be transfer. */
    uint8_t mbIdx;          /*!< The index of Message buffer used to transfer Message. */
} flexcan_mb_transfer_t;

/*! @brief FlexCAN Rx FIFO transfer. */
typedef struct _flexcan_fifo_transfer
{
#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
    flexcan_fd_frame_t *framefd; /*!< The buffer of CAN Message to be received from Enhanced Rx FIFO. */
    size_t frameNum;             /*!< Number of CAN Message need to be received from Ehanced Rx FIFO. */
#endif
    flexcan_frame_t *frame; /*!< The buffer of CAN Message to be received from Rx FIFO. */
} flexcan_fifo_transfer_t;

/*! @brief FlexCAN handle structure definition. */
typedef struct _flexcan_handle flexcan_handle_t;

/*! @brief FlexCAN transfer callback function.
 *
 *  The FlexCAN transfer callback returns a value from the underlying layer.
 *  If the status equals to kStatus_FLEXCAN_ErrorStatus, the result parameter is the Content of
 *  FlexCAN status register which can be used to get the working status(or error status) of FlexCAN module.
 *  If the status equals to other FlexCAN Message Buffer transfer status, the result is the index of
 *  Message Buffer that generate transfer event.
 *  If the status equals to other FlexCAN Message Buffer transfer status, the result is meaningless and should be
 *  Ignored.
 */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_PN_MODE) && FSL_FEATURE_FLEXCAN_HAS_PN_MODE) || \
    (defined(FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL) && FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL)
#define FLEXCAN_CALLBACK(x) \
    void(x)(CAN_Type * base, flexcan_handle_t * handle, status_t status, uint64_t result, void *userData)
typedef void (*flexcan_transfer_callback_t)(
    CAN_Type *base, flexcan_handle_t *handle, status_t status, uint64_t result, void *userData);
#else
#define FLEXCAN_CALLBACK(x) \
    void(x)(CAN_Type * base, flexcan_handle_t * handle, status_t status, uint32_t result, void *userData)
typedef void (*flexcan_transfer_callback_t)(
    CAN_Type *base, flexcan_handle_t *handle, status_t status, uint32_t result, void *userData);
#endif

/*! @brief FlexCAN handle structure. */
struct _flexcan_handle
{
    flexcan_transfer_callback_t callback; /*!< Callback function. */
    void *userData;                       /*!< FlexCAN callback function parameter.*/
    flexcan_frame_t
        *volatile mbFrameBuf[CAN_WORD1_COUNT]; /*!< The buffer for received CAN data from Message Buffers. */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    flexcan_fd_frame_t
        *volatile mbFDFrameBuf[CAN_WORD1_COUNT]; /*!< The buffer for received CAN FD data from Message Buffers. */
#endif
    flexcan_frame_t *volatile rxFifoFrameBuf; /*!< The buffer for received CAN data from Legacy Rx FIFO. */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
    flexcan_fd_frame_t *volatile rxFifoFDFrameBuf; /*!< The buffer for received CAN FD data from Ehanced Rx FIFO. */
    size_t frameNum;                               /*!< The number of CAN messages remaining to be received. */
    size_t transferTotalNum; /*!< Total CAN Message number need to be received from Ehanced Rx FIFO. */
#endif
    volatile uint8_t mbState[CAN_WORD1_COUNT];    /*!< Message Buffer transfer state. */
    volatile uint8_t rxFifoState;                 /*!< Rx FIFO transfer state. */
    volatile uint32_t timestamp[CAN_WORD1_COUNT]; /*!< Mailbox transfer timestamp. */
};

/******************************************************************************
 * API
 *****************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Enter FlexCAN Freeze Mode.
 *
 * This function makes the FlexCAN work under Freeze Mode.
 *
 * @param base FlexCAN peripheral base address.
 */
void FLEXCAN_EnterFreezeMode(CAN_Type *base);

/*!
 * @brief Exit FlexCAN Freeze Mode.
 *
 * This function makes the FlexCAN leave Freeze Mode.
 *
 * @param base FlexCAN peripheral base address.
 */
void FLEXCAN_ExitFreezeMode(CAN_Type *base);

/*!
 * @brief Get the FlexCAN instance from peripheral base address.
 *
 * @param base FlexCAN peripheral base address.
 * @return FlexCAN instance.
 */
uint32_t FLEXCAN_GetInstance(CAN_Type *base);

/*!
 * @brief Calculates the improved timing values by specific bit Rates for classical CAN.
 *
 * This function use to calculates the Classical CAN timing values according to the given bit rate. The Calculated
 * timing values will be set in CTRL1/CBT/ENCBT register. The calculation is based on the recommendation of the CiA 301
 * v4.2.0 and previous version document.
 *
 * @param base FlexCAN peripheral base address.
 * @param bitRate  The classical CAN speed in bps defined by user, should be less than or equal to 1Mbps.
 * @param sourceClock_Hz The Source clock frequency in Hz.
 * @param pTimingConfig Pointer to the FlexCAN timing configuration structure.
 *
 * @return TRUE if timing configuration found, FALSE if failed to find configuration.
 */
bool FLEXCAN_CalculateImprovedTimingValues(CAN_Type *base,
                                           uint32_t bitRate,
                                           uint32_t sourceClock_Hz,
                                           flexcan_timing_config_t *pTimingConfig);

/*!
 * @brief Initializes a FlexCAN instance.
 *
 * This function initializes the FlexCAN module with user-defined settings.
 * This example shows how to set up the flexcan_config_t parameters and how
 * to call the FLEXCAN_Init function by passing in these parameters.
 *  @code
 *   flexcan_config_t flexcanConfig;
 *   flexcanConfig.clkSrc               = kFLEXCAN_ClkSrc0;
 *   flexcanConfig.bitRate              = 1000000U;
 *   flexcanConfig.maxMbNum             = 16;
 *   flexcanConfig.enableLoopBack       = false;
 *   flexcanConfig.enableSelfWakeup     = false;
 *   flexcanConfig.enableIndividMask    = false;
 *   flexcanConfig.enableDoze           = false;
 *   flexcanConfig.disableSelfReception = false;
 *   flexcanConfig.enableListenOnlyMode = false;
 *   flexcanConfig.timingConfig         = timingConfig;
 *   FLEXCAN_Init(CAN0, &flexcanConfig, 40000000UL);
 *   @endcode
 *
 * @param base FlexCAN peripheral base address.
 * @param pConfig Pointer to the user-defined configuration structure.
 * @param sourceClock_Hz FlexCAN Protocol Engine clock source frequency in Hz.
 */
void FLEXCAN_Init(CAN_Type *base, const flexcan_config_t *pConfig, uint32_t sourceClock_Hz);

#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
/*!
 * @brief Calculates the improved timing values by specific bit rates for CANFD.
 *
 * This function use to calculates the CANFD timing values according to the given nominal phase bit rate and data phase
 * bit rate. The Calculated timing values will be set in CBT/ENCBT and FDCBT/EDCBT registers. The calculation is based
 * on the recommendation of the CiA 1301 v1.0.0 document.
 *
 * @param base FlexCAN peripheral base address.
 * @param bitRate  The CANFD bus control speed in bps defined by user.
 * @param bitRateFD  The CAN FD data phase speed in bps defined by user. Equal to bitRate means disable bit rate
 * switching.
 * @param sourceClock_Hz The Source clock frequency in Hz.
 * @param pTimingConfig Pointer to the FlexCAN timing configuration structure.
 *
 * @return TRUE if timing configuration found, FALSE if failed to find configuration
 */
bool FLEXCAN_FDCalculateImprovedTimingValues(CAN_Type *base,
                                             uint32_t bitRate,
                                             uint32_t bitRateFD,
                                             uint32_t sourceClock_Hz,
                                             flexcan_timing_config_t *pTimingConfig);
/*!
 * @brief Initializes a FlexCAN instance.
 *
 * This function initializes the FlexCAN module with user-defined settings.
 * This example shows how to set up the flexcan_config_t parameters and how
 * to call the FLEXCAN_FDInit function by passing in these parameters.
 *  @code
 *   flexcan_config_t flexcanConfig;
 *   flexcanConfig.clkSrc               = kFLEXCAN_ClkSrc0;
 *   flexcanConfig.bitRate              = 1000000U;
 *   flexcanConfig.bitRateFD            = 2000000U;
 *   flexcanConfig.maxMbNum             = 16;
 *   flexcanConfig.enableLoopBack       = false;
 *   flexcanConfig.enableSelfWakeup     = false;
 *   flexcanConfig.enableIndividMask    = false;
 *   flexcanConfig.disableSelfReception = false;
 *   flexcanConfig.enableListenOnlyMode = false;
 *   flexcanConfig.enableDoze           = false;
 *   flexcanConfig.timingConfig         = timingConfig;
 *   FLEXCAN_FDInit(CAN0, &flexcanConfig, 80000000UL, kFLEXCAN_16BperMB, true);
 *   @endcode
 *
 * @param base FlexCAN peripheral base address.
 * @param pConfig Pointer to the user-defined configuration structure.
 * @param sourceClock_Hz FlexCAN Protocol Engine clock source frequency in Hz.
 * @param dataSize FlexCAN Message Buffer payload size. The actual transmitted or received CAN FD frame data size needs
 *                to be less than or equal to this value.
 * @param brs True if bit rate switch is enabled in FD mode.
 */
void FLEXCAN_FDInit(
    CAN_Type *base, const flexcan_config_t *pConfig, uint32_t sourceClock_Hz, flexcan_mb_size_t dataSize, bool brs);
#endif

/*!
 * @brief De-initializes a FlexCAN instance.
 *
 * This function disables the FlexCAN module clock and sets all register values
 * to the reset value.
 *
 * @param base FlexCAN peripheral base address.
 */
void FLEXCAN_Deinit(CAN_Type *base);

/*!
 * @brief Gets the default configuration structure.
 *
 * This function initializes the FlexCAN configuration structure to default values. The default
 * values are as follows.
 *   flexcanConfig->clkSrc                               = kFLEXCAN_ClkSrc0;
 *   flexcanConfig->bitRate                              = 1000000U;
 *   flexcanConfig->bitRateFD                            = 2000000U;
 *   flexcanConfig->maxMbNum                             = 16;
 *   flexcanConfig->enableLoopBack                       = false;
 *   flexcanConfig->enableSelfWakeup                     = false;
 *   flexcanConfig->enableIndividMask                    = false;
 *   flexcanConfig->disableSelfReception                 = false;
 *   flexcanConfig->enableListenOnlyMode                 = false;
 *   flexcanConfig->enableDoze                           = false;
 *   flexcanConfig->enableMemoryErrorControl             = true;
 *   flexcanConfig->enableNonCorrectableErrorEnterFreeze = true;
 *   flexcanConfig.timingConfig                          = timingConfig;
 *
 * @param pConfig Pointer to the FlexCAN configuration structure.
 */
void FLEXCAN_GetDefaultConfig(flexcan_config_t *pConfig);

/* @} */

/*!
 * @name Configuration.
 * @{
 */

/*!
 * @brief Sets the FlexCAN protocol timing characteristic.
 *
 * This function gives user settings to classical CAN or CANFD nominal phase timing characteristic.
 * The function is for an experienced user. For less experienced users, call the FLEXCAN_GetDefaultConfig()
 * and get the default timing characteristicsthe, then call FLEXCAN_Init() and fill the
 * bit rate field.
 *
 * @note Calling FLEXCAN_SetTimingConfig() overrides the bit rate set in FLEXCAN_Init().
 *
 * @param base FlexCAN peripheral base address.
 * @param pConfig Pointer to the timing configuration structure.
 */
void FLEXCAN_SetTimingConfig(CAN_Type *base, const flexcan_timing_config_t *pConfig);

#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
/*!
 * @brief Sets the FlexCAN CANFD data phase timing characteristic.
 *
 * This function gives user settings to CANFD data phase timing characteristic.
 * The function is for an experienced user. For less experienced users, call the FLEXCAN_GetDefaultConfig()
 * and get the default timing characteristicsthe, then call FLEXCAN_FDInit() and fill the
 * data phase bit rate field.
 *
 * @note Calling FLEXCAN_SetFDTimingConfig() overrides the bit rate set in FLEXCAN_FDInit().
 *
 * @param base FlexCAN peripheral base address.
 * @param pConfig Pointer to the timing configuration structure.
 */
void FLEXCAN_SetFDTimingConfig(CAN_Type *base, const flexcan_timing_config_t *pConfig);
#endif

/*!
 * @brief Sets the FlexCAN receive message buffer global mask.
 *
 * This function sets the global mask for the FlexCAN message buffer in a matching process.
 * The configuration is only effective when the Rx individual mask is disabled in the FLEXCAN_Init().
 *
 * @param base FlexCAN peripheral base address.
 * @param mask Rx Message Buffer Global Mask value.
 */
void FLEXCAN_SetRxMbGlobalMask(CAN_Type *base, uint32_t mask);

/*!
 * @brief Sets the FlexCAN receive FIFO global mask.
 *
 * This function sets the global mask for FlexCAN FIFO in a matching process.
 *
 * @param base FlexCAN peripheral base address.
 * @param mask Rx Fifo Global Mask value.
 */
void FLEXCAN_SetRxFifoGlobalMask(CAN_Type *base, uint32_t mask);

/*!
 * @brief Sets the FlexCAN receive individual mask.
 *
 * This function sets the individual mask for the FlexCAN matching process.
 * The configuration is only effective when the Rx individual mask is enabled in the FLEXCAN_Init().
 * If the Rx FIFO is disabled, the individual mask is applied to the corresponding Message Buffer.
 * If the Rx FIFO is enabled, the individual mask for Rx FIFO occupied Message Buffer is applied to
 * the Rx Filter with the same index. Note that only the first 32
 * individual masks can be used as the Rx FIFO filter mask.
 *
 * @param base FlexCAN peripheral base address.
 * @param maskIdx The Index of individual Mask.
 * @param mask Rx Individual Mask value.
 */
void FLEXCAN_SetRxIndividualMask(CAN_Type *base, uint8_t maskIdx, uint32_t mask);

/*!
 * @brief Configures a FlexCAN transmit message buffer.
 *
 * This function aborts the previous transmission, cleans the Message Buffer, and
 * configures it as a Transmit Message Buffer.
 *
 * @param base FlexCAN peripheral base address.
 * @param mbIdx The Message Buffer index.
 * @param enable Enable/disable Tx Message Buffer.
 *               - true: Enable Tx Message Buffer.
 *               - false: Disable Tx Message Buffer.
 */
void FLEXCAN_SetTxMbConfig(CAN_Type *base, uint8_t mbIdx, bool enable);

#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
/*!
 * @brief Configures a FlexCAN transmit message buffer.
 *
 * This function aborts the previous transmission, cleans the Message Buffer, and
 * configures it as a Transmit Message Buffer.
 *
 * @param base FlexCAN peripheral base address.
 * @param mbIdx The Message Buffer index.
 * @param enable Enable/disable Tx Message Buffer.
 *               - true: Enable Tx Message Buffer.
 *               - false: Disable Tx Message Buffer.
 */
void FLEXCAN_SetFDTxMbConfig(CAN_Type *base, uint8_t mbIdx, bool enable);
#endif

/*!
 * @brief Configures a FlexCAN Receive Message Buffer.
 *
 * This function cleans a FlexCAN build-in Message Buffer and configures it
 * as a Receive Message Buffer.
 *
 * @param base FlexCAN peripheral base address.
 * @param mbIdx The Message Buffer index.
 * @param pRxMbConfig Pointer to the FlexCAN Message Buffer configuration structure.
 * @param enable Enable/disable Rx Message Buffer.
 *               - true: Enable Rx Message Buffer.
 *               - false: Disable Rx Message Buffer.
 */
void FLEXCAN_SetRxMbConfig(CAN_Type *base, uint8_t mbIdx, const flexcan_rx_mb_config_t *pRxMbConfig, bool enable);

#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
/*!
 * @brief Configures a FlexCAN Receive Message Buffer.
 *
 * This function cleans a FlexCAN build-in Message Buffer and configures it
 * as a Receive Message Buffer.
 *
 * @param base FlexCAN peripheral base address.
 * @param mbIdx The Message Buffer index.
 * @param pRxMbConfig Pointer to the FlexCAN Message Buffer configuration structure.
 * @param enable Enable/disable Rx Message Buffer.
 *               - true: Enable Rx Message Buffer.
 *               - false: Disable Rx Message Buffer.
 */
void FLEXCAN_SetFDRxMbConfig(CAN_Type *base, uint8_t mbIdx, const flexcan_rx_mb_config_t *pRxMbConfig, bool enable);
#endif

/*!
 * @brief Configures the FlexCAN Legacy Rx FIFO.
 *
 * This function configures the FlexCAN Rx FIFO with given configuration.
 * @note Legacy Rx FIFO only can receive classic CAN message.
 *
 * @param base FlexCAN peripheral base address.
 * @param pRxFifoConfig Pointer to the FlexCAN Legacy Rx FIFO configuration structure. Can be NULL when enable parameter
 *                      is false.
 * @param enable Enable/disable Legacy Rx FIFO.
 *               - true: Enable Legacy Rx FIFO.
 *               - false: Disable Legacy Rx FIFO.
 */
void FLEXCAN_SetRxFifoConfig(CAN_Type *base, const flexcan_rx_fifo_config_t *pRxFifoConfig, bool enable);

#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
/*!
 * @brief Configures the FlexCAN Enhanced Rx FIFO.
 *
 * This function configures the Enhanced Rx FIFO with given configuration.
 * @note Enhanced Rx FIFO support receive classic CAN or CAN FD messages, Legacy Rx FIFO and Enhanced Rx FIFO
 *       cannot be enabled at the same time.
 *
 * @param base    FlexCAN peripheral base address.
 * @param pConfig Pointer to the FlexCAN Enhanced Rx FIFO configuration structure. Can be NULL when enable parameter
 *                is false.
 * @param enable  Enable/disable Enhanced Rx FIFO.
 *                - true: Enable Enhanced Rx FIFO.
 *                - false: Disable Enhanced Rx FIFO.
 */
void FLEXCAN_SetEnhancedRxFifoConfig(CAN_Type *base, const flexcan_enhanced_rx_fifo_config_t *pConfig, bool enable);
#endif

#if (defined(FSL_FEATURE_FLEXCAN_HAS_PN_MODE) && FSL_FEATURE_FLEXCAN_HAS_PN_MODE)
/*!
 * @brief Configures the FlexCAN Pretended Networking mode.
 *
 * This function configures the FlexCAN Pretended Networking mode with given configuration.
 *
 * @param base FlexCAN peripheral base address.
 * @param pConfig Pointer to the FlexCAN Rx FIFO configuration structure.
 */
void FLEXCAN_SetPNConfig(CAN_Type *base, const flexcan_pn_config_t *pConfig);
#endif
/* @} */

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets the FlexCAN module interrupt flags.
 *
 * This function gets all FlexCAN status flags. The flags are returned as the logical
 * OR value of the enumerators @ref _flexcan_flags. To check the specific status,
 * compare the return value with enumerators in @ref _flexcan_flags.
 *
 * @param base FlexCAN peripheral base address.
 * @return FlexCAN status flags which are ORed by the enumerators in the _flexcan_flags.
 */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_PN_MODE) && FSL_FEATURE_FLEXCAN_HAS_PN_MODE) ||                   \
    (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) || \
    (defined(FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL) && FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL)
static inline uint64_t FLEXCAN_GetStatusFlags(CAN_Type *base)
{
    uint64_t tempflag = (uint64_t)base->ESR1;
#if (defined(FSL_FEATURE_FLEXCAN_HAS_PN_MODE) && FSL_FEATURE_FLEXCAN_HAS_PN_MODE)
    /* Get PN Wake Up status. */
    tempflag |= FLEXCAN_PN_STATUS_MASK(base->WU_MTC);
#endif
#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
    /* Get Enhanced Rx FIFO status. */
    tempflag |= FLEXCAN_EFIFO_STATUS_MASK(base->ERFSR);
#endif
#if (defined(FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL) && FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL)
    /* Get Memory Error status. */
    tempflag |= FLEXCAN_MECR_STATUS_MASK(base->ERRSR);
#endif
    return tempflag;
}
#else
static inline uint32_t FLEXCAN_GetStatusFlags(CAN_Type *base)
{
    return base->ESR1;
}
#endif
/*!
 * @brief Clears status flags with the provided mask.
 *
 * This function clears the FlexCAN status flags with a provided mask. An automatically cleared flag
 * can't be cleared by this function.
 *
 * @param base FlexCAN peripheral base address.
 * @param mask The status flags to be cleared, it is logical OR value of @ref _flexcan_flags.
 */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_PN_MODE) && FSL_FEATURE_FLEXCAN_HAS_PN_MODE) ||                   \
    (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) || \
    (defined(FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL) && FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL)
static inline void FLEXCAN_ClearStatusFlags(CAN_Type *base, uint64_t mask)
{
#if (defined(FSL_FEATURE_FLEXCAN_HAS_PN_MODE) && FSL_FEATURE_FLEXCAN_HAS_PN_MODE)
    /* Clear PN Wake Up status. */
    base->WU_MTC = FLEXCAN_PN_STATUS_UNMASK(mask);
#endif
#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
    /* Clear Enhanced Rx FIFO status. */
    base->ERFSR |= FLEXCAN_EFIFO_STATUS_UNMASK(mask);
#endif
#if (defined(FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL) && FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL)
    /* Clear Memory Error status. */
    base->ERRSR = FLEXCAN_MECR_STATUS_UNMASK(mask);
#endif
    base->ESR1 = (uint32_t)(mask & 0xFFFFFFFFU);
}
#else
static inline void FLEXCAN_ClearStatusFlags(CAN_Type *base, uint32_t mask)
{
    /* Write 1 to clear status flag. */
    base->ESR1 = mask;
}
#endif
/*!
 * @brief Gets the FlexCAN Bus Error Counter value.
 *
 * This function gets the FlexCAN Bus Error Counter value for both Tx and
 * Rx direction. These values may be needed in the upper layer error handling.
 *
 * @param base FlexCAN peripheral base address.
 * @param txErrBuf Buffer to store Tx Error Counter value.
 * @param rxErrBuf Buffer to store Rx Error Counter value.
 */
static inline void FLEXCAN_GetBusErrCount(CAN_Type *base, uint8_t *txErrBuf, uint8_t *rxErrBuf)
{
    if (NULL != txErrBuf)
    {
        *txErrBuf = (uint8_t)((base->ECR & CAN_ECR_TXERRCNT_MASK) >> CAN_ECR_TXERRCNT_SHIFT);
    }

    if (NULL != rxErrBuf)
    {
        *rxErrBuf = (uint8_t)((base->ECR & CAN_ECR_RXERRCNT_MASK) >> CAN_ECR_RXERRCNT_SHIFT);
    }
}

/*!
 * @brief Gets the FlexCAN Message Buffer interrupt flags.
 *
 * This function gets the interrupt flags of a given Message Buffers.
 *
 * @param base FlexCAN peripheral base address.
 * @param mask The ORed FlexCAN Message Buffer mask.
 * @return The status of given Message Buffers.
 */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_EXTENDED_FLAG_REGISTER)) && (FSL_FEATURE_FLEXCAN_HAS_EXTENDED_FLAG_REGISTER > 0)
static inline uint64_t FLEXCAN_GetMbStatusFlags(CAN_Type *base, uint64_t mask)
#else
static inline uint32_t FLEXCAN_GetMbStatusFlags(CAN_Type *base, uint32_t mask)
#endif
{
#if (defined(FSL_FEATURE_FLEXCAN_HAS_EXTENDED_FLAG_REGISTER)) && (FSL_FEATURE_FLEXCAN_HAS_EXTENDED_FLAG_REGISTER > 0)
    uint64_t tempflag = (uint64_t)base->IFLAG1;
    return (tempflag | (((uint64_t)base->IFLAG2) << 32)) & mask;
#else
    return (base->IFLAG1 & mask);
#endif
}

/*!
 * @brief Clears the FlexCAN Message Buffer interrupt flags.
 *
 * This function clears the interrupt flags of a given Message Buffers.
 *
 * @param base FlexCAN peripheral base address.
 * @param mask The ORed FlexCAN Message Buffer mask.
 */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_EXTENDED_FLAG_REGISTER)) && (FSL_FEATURE_FLEXCAN_HAS_EXTENDED_FLAG_REGISTER > 0)
static inline void FLEXCAN_ClearMbStatusFlags(CAN_Type *base, uint64_t mask)
#else
static inline void FLEXCAN_ClearMbStatusFlags(CAN_Type *base, uint32_t mask)
#endif
{
#if (defined(FSL_FEATURE_FLEXCAN_HAS_EXTENDED_FLAG_REGISTER)) && (FSL_FEATURE_FLEXCAN_HAS_EXTENDED_FLAG_REGISTER > 0)
    base->IFLAG1 = (uint32_t)(mask & 0xFFFFFFFFU);
    base->IFLAG2 = (uint32_t)(mask >> 32);
#else
    base->IFLAG1 = mask;
#endif
}

#if (defined(FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL) && FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL)
/*!
 * @brief Gets the FlexCAN Memory Error Report registers status.
 *
 * This function gets the FlexCAN Memory Error Report registers status.
 *
 * @param base FlexCAN peripheral base address.
 * @param errorStatus Pointer to FlexCAN Memory Error Report registers status structure.
 */
void FLEXCAN_GetMemoryErrorReportStatus(CAN_Type *base, flexcan_memory_error_report_status_t *errorStatus);
#endif

#if (defined(FSL_FEATURE_FLEXCAN_HAS_PN_MODE) && FSL_FEATURE_FLEXCAN_HAS_PN_MODE)
/*!
 * @brief Gets the FlexCAN Number of Matches when in Pretended Networking.
 *
 * This function gets the number of times a given message has matched the predefined filtering criteria for ID and/or PL
 * before a wakeup event.
 *
 * @param base FlexCAN peripheral base address.
 * @return The number of received wake up msessages.
 */
static inline uint8_t FLEXCAN_GetPNMatchCount(CAN_Type *base)
{
    return (uint8_t)((base->WU_MTC & CAN_WU_MTC_MCOUNTER_MASK) >> CAN_WU_MTC_MCOUNTER_SHIFT);
}
#endif

#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
/*!
 * @brief Gets the number of FlexCAN Enhanced Rx FIFO available frames.
 *
 * This function gets the number of CAN messages stored in the Enhanced Rx FIFO.
 *
 * @param base FlexCAN peripheral base address.
 * @return The number of available CAN messages stored in the Enhanced Rx FIFO.
 */
static inline uint32_t FLEXCAN_GetEnhancedFifoDataCount(CAN_Type *base)
{
    return (base->ERFSR & CAN_ERFSR_ERFEL_MASK);
}
#endif
/* @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables FlexCAN interrupts according to the provided mask.
 *
 * This function enables the FlexCAN interrupts according to the provided mask. The mask
 * is a logical OR of enumeration members, see @ref _flexcan_interrupt_enable.
 *
 * @param base FlexCAN peripheral base address.
 * @param mask The interrupts to enable. Logical OR of @ref _flexcan_interrupt_enable.
 */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_PN_MODE) && FSL_FEATURE_FLEXCAN_HAS_PN_MODE) ||                   \
    (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) || \
    (defined(FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL) && FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL)
static inline void FLEXCAN_EnableInterrupts(CAN_Type *base, uint64_t mask)
#else
static inline void FLEXCAN_EnableInterrupts(CAN_Type *base, uint32_t mask)
#endif
{
    /* Solve Self Wake Up interrupt. */
    base->MCR |= (uint32_t)(mask & (uint32_t)kFLEXCAN_WakeUpInterruptEnable);

#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    if (0 != FSL_FEATURE_FLEXCAN_INSTANCE_HAS_FLEXIBLE_DATA_RATEn(base))
    {
        /* Solve CAN FD frames data phase error interrupt. */
        base->CTRL2 |= (uint32_t)(mask & (uint32_t)kFLEXCAN_FDErrorInterruptEnable);
    }
#endif

#if (defined(FSL_FEATURE_FLEXCAN_HAS_PN_MODE) && FSL_FEATURE_FLEXCAN_HAS_PN_MODE)
    /* Solve PN Wake Up interrupt. */
    base->CTRL1_PN |= FLEXCAN_PN_INT_UNMASK(mask);
#endif

#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
    /* Solve Enhanced Rx FIFO interrupt. */
    base->ERFIER |= FLEXCAN_EFIFO_INT_UNMASK(mask);
#endif

#if (defined(FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL) && FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL)
    /* Solve Memory Error interrupt. */
    base->MECR |= FLEXCAN_MECR_INT_UNMASK(mask);
#endif

    /* Solve interrupt enable bits in CTRL1 register. */
    base->CTRL1 |=
        (uint32_t)(mask & ((uint32_t)kFLEXCAN_BusOffInterruptEnable | (uint32_t)kFLEXCAN_ErrorInterruptEnable |
                           (uint32_t)kFLEXCAN_RxWarningInterruptEnable | (uint32_t)kFLEXCAN_TxWarningInterruptEnable));
}

/*!
 * @brief Disables FlexCAN interrupts according to the provided mask.
 *
 * This function disables the FlexCAN interrupts according to the provided mask. The mask
 * is a logical OR of enumeration members, see @ref _flexcan_interrupt_enable.
 *
 * @param base FlexCAN peripheral base address.
 * @param mask The interrupts to disable. Logical OR of @ref _flexcan_interrupt_enable.
 */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_PN_MODE) && FSL_FEATURE_FLEXCAN_HAS_PN_MODE) || \
    (defined(FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL) && FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL)
static inline void FLEXCAN_DisableInterrupts(CAN_Type *base, uint64_t mask)
#else
static inline void FLEXCAN_DisableInterrupts(CAN_Type *base, uint32_t mask)
#endif
{
    /* Solve Wake Up Interrupt. */
    base->MCR &= ~(uint32_t)(mask & (uint32_t)kFLEXCAN_WakeUpInterruptEnable);

#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
    if (0 != FSL_FEATURE_FLEXCAN_INSTANCE_HAS_FLEXIBLE_DATA_RATEn(base))
    {
        /* Solve CAN FD frames data phase error interrupt. */
        base->CTRL2 &= ~(uint32_t)(mask & (uint32_t)kFLEXCAN_FDErrorInterruptEnable);
    }
#endif

#if (defined(FSL_FEATURE_FLEXCAN_HAS_PN_MODE) && FSL_FEATURE_FLEXCAN_HAS_PN_MODE)
    /* Solve PN Wake Up Interrupt. */
    base->CTRL1_PN &= ~FLEXCAN_PN_STATUS_UNMASK(mask);
#endif

#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
    /* Solve Enhanced Rx FIFO interrupt. */
    base->ERFIER &= ~FLEXCAN_EFIFO_INT_UNMASK(mask);
#endif

#if (defined(FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL) && FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL)
    /* Solve Memory Error Interrupt. */
    base->MECR &= ~FLEXCAN_MECR_STATUS_UNMASK(mask);
#endif

    /* Solve interrupt enable bits in CTRL1 register. */
    base->CTRL1 &=
        ~(uint32_t)(mask & ((uint32_t)kFLEXCAN_BusOffInterruptEnable | (uint32_t)kFLEXCAN_ErrorInterruptEnable |
                            (uint32_t)kFLEXCAN_RxWarningInterruptEnable | (uint32_t)kFLEXCAN_TxWarningInterruptEnable));
}

/*!
 * @brief Enables FlexCAN Message Buffer interrupts.
 *
 * This function enables the interrupts of given Message Buffers.
 *
 * @param base FlexCAN peripheral base address.
 * @param mask The ORed FlexCAN Message Buffer mask.
 */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_EXTENDED_FLAG_REGISTER)) && (FSL_FEATURE_FLEXCAN_HAS_EXTENDED_FLAG_REGISTER > 0)
static inline void FLEXCAN_EnableMbInterrupts(CAN_Type *base, uint64_t mask)
#else
static inline void FLEXCAN_EnableMbInterrupts(CAN_Type *base, uint32_t mask)
#endif
{
#if (defined(FSL_FEATURE_FLEXCAN_HAS_EXTENDED_FLAG_REGISTER)) && (FSL_FEATURE_FLEXCAN_HAS_EXTENDED_FLAG_REGISTER > 0)
    base->IMASK1 |= (uint32_t)(mask & 0xFFFFFFFFU);
    base->IMASK2 |= (uint32_t)(mask >> 32);
#else
    base->IMASK1 |= mask;
#endif
}

/*!
 * @brief Disables FlexCAN Message Buffer interrupts.
 *
 * This function disables the interrupts of given Message Buffers.
 *
 * @param base FlexCAN peripheral base address.
 * @param mask The ORed FlexCAN Message Buffer mask.
 */
#if (defined(FSL_FEATURE_FLEXCAN_HAS_EXTENDED_FLAG_REGISTER)) && (FSL_FEATURE_FLEXCAN_HAS_EXTENDED_FLAG_REGISTER > 0)
static inline void FLEXCAN_DisableMbInterrupts(CAN_Type *base, uint64_t mask)
#else
static inline void FLEXCAN_DisableMbInterrupts(CAN_Type *base, uint32_t mask)
#endif
{
#if (defined(FSL_FEATURE_FLEXCAN_HAS_EXTENDED_FLAG_REGISTER)) && (FSL_FEATURE_FLEXCAN_HAS_EXTENDED_FLAG_REGISTER > 0)
    base->IMASK1 &= ~((uint32_t)(mask & 0xFFFFFFFFU));
    base->IMASK2 &= ~((uint32_t)(mask >> 32));
#else
    base->IMASK1 &= ~mask;
#endif
}

/* @} */

#if (defined(FSL_FEATURE_FLEXCAN_HAS_RX_FIFO_DMA) && FSL_FEATURE_FLEXCAN_HAS_RX_FIFO_DMA)
/*!
 * @name DMA Control
 * @{
 */

/*!
 * @brief Enables or disables the FlexCAN Rx FIFO DMA request.
 *
 * This function enables or disables the DMA feature of FlexCAN build-in Rx FIFO.
 *
 * @param base FlexCAN peripheral base address.
 * @param enable true to enable, false to disable.
 */
void FLEXCAN_EnableRxFifoDMA(CAN_Type *base, bool enable);

/*!
 * @brief Gets the Rx FIFO Head address.
 *
 * This function returns the FlexCAN Rx FIFO Head address, which is mainly used for the DMA/eDMA use case.
 *
 * @param base FlexCAN peripheral base address.
 * @return FlexCAN Rx FIFO Head address.
 */
static inline uintptr_t FLEXCAN_GetRxFifoHeadAddr(CAN_Type *base)
{
    return (uintptr_t) & (base->MB[0].CS);
}

/* @} */
#endif /* FSL_FEATURE_FLEXCAN_HAS_RX_FIFO_DMA */

/*!
 * @name Bus Operations
 * @{
 */

/*!
 * @brief Enables or disables the FlexCAN module operation.
 *
 * This function enables or disables the FlexCAN module.
 *
 * @param base FlexCAN base pointer.
 * @param enable true to enable, false to disable.
 */
static inline void FLEXCAN_Enable(CAN_Type *base, bool enable)
{
    if (enable)
    {
        base->MCR &= ~CAN_MCR_MDIS_MASK;

        /* Wait FlexCAN exit from low-power mode. */
        while (0U != (base->MCR & CAN_MCR_LPMACK_MASK))
        {
        }
    }
    else
    {
        base->MCR |= CAN_MCR_MDIS_MASK;

        /* Wait FlexCAN enter low-power mode. */
        while (0U == (base->MCR & CAN_MCR_LPMACK_MASK))
        {
        }
    }
}

/*!
 * @brief Writes a FlexCAN Message to the Transmit Message Buffer.
 *
 * This function writes a CAN Message to the specified Transmit Message Buffer
 * and changes the Message Buffer state to start CAN Message transmit. After
 * that the function returns immediately.
 *
 * @param base FlexCAN peripheral base address.
 * @param mbIdx The FlexCAN Message Buffer index.
 * @param pTxFrame Pointer to CAN message frame to be sent.
 * @retval kStatus_Success - Write Tx Message Buffer Successfully.
 * @retval kStatus_Fail    - Tx Message Buffer is currently in use.
 */
status_t FLEXCAN_WriteTxMb(CAN_Type *base, uint8_t mbIdx, const flexcan_frame_t *pTxFrame);

/*!
 * @brief Reads a FlexCAN Message from Receive Message Buffer.
 *
 * This function reads a CAN message from a specified Receive Message Buffer.
 * The function fills a receive CAN message frame structure with
 * just received data and activates the Message Buffer again.
 * The function returns immediately.
 *
 * @param base FlexCAN peripheral base address.
 * @param mbIdx The FlexCAN Message Buffer index.
 * @param pRxFrame Pointer to CAN message frame structure for reception.
 * @retval kStatus_Success            - Rx Message Buffer is full and has been read successfully.
 * @retval kStatus_FLEXCAN_RxOverflow - Rx Message Buffer is already overflowed and has been read successfully.
 * @retval kStatus_Fail               - Rx Message Buffer is empty.
 */
status_t FLEXCAN_ReadRxMb(CAN_Type *base, uint8_t mbIdx, flexcan_frame_t *pRxFrame);

#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
/*!
 * @brief Writes a FlexCAN FD Message to the Transmit Message Buffer.
 *
 * This function writes a CAN FD Message to the specified Transmit Message Buffer
 * and changes the Message Buffer state to start CAN FD Message transmit. After
 * that the function returns immediately.
 *
 * @param base FlexCAN peripheral base address.
 * @param mbIdx The FlexCAN FD Message Buffer index.
 * @param pTxFrame Pointer to CAN FD message frame to be sent.
 * @retval kStatus_Success - Write Tx Message Buffer Successfully.
 * @retval kStatus_Fail    - Tx Message Buffer is currently in use.
 */
status_t FLEXCAN_WriteFDTxMb(CAN_Type *base, uint8_t mbIdx, const flexcan_fd_frame_t *pTxFrame);

/*!
 * @brief Reads a FlexCAN FD Message from Receive Message Buffer.
 *
 * This function reads a CAN FD message from a specified Receive Message Buffer.
 * The function fills a receive CAN FD message frame structure with
 * just received data and activates the Message Buffer again.
 * The function returns immediately.
 *
 * @param base FlexCAN peripheral base address.
 * @param mbIdx The FlexCAN FD Message Buffer index.
 * @param pRxFrame Pointer to CAN FD message frame structure for reception.
 * @retval kStatus_Success            - Rx Message Buffer is full and has been read successfully.
 * @retval kStatus_FLEXCAN_RxOverflow - Rx Message Buffer is already overflowed and has been read successfully.
 * @retval kStatus_Fail               - Rx Message Buffer is empty.
 */
status_t FLEXCAN_ReadFDRxMb(CAN_Type *base, uint8_t mbIdx, flexcan_fd_frame_t *pRxFrame);
#endif

/*!
 * @brief Reads a FlexCAN Message from Legacy Rx FIFO.
 *
 * This function reads a CAN message from the FlexCAN Legacy Rx FIFO.
 *
 * @param base FlexCAN peripheral base address.
 * @param pRxFrame Pointer to CAN message frame structure for reception.
 * @retval kStatus_Success - Read Message from Rx FIFO successfully.
 * @retval kStatus_Fail    - Rx FIFO is not enabled.
 */
status_t FLEXCAN_ReadRxFifo(CAN_Type *base, flexcan_frame_t *pRxFrame);

#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
/*!
 * @brief Reads a FlexCAN Message from Enhanced Rx FIFO.
 *
 * This function reads a CAN or CAN FD message from the FlexCAN Enhanced Rx FIFO.
 *
 * @param  base FlexCAN peripheral base address.
 * @param  pRxFrame Pointer to CAN FD message frame structure for reception.
 * @retval kStatus_Success - Read Message from Rx FIFO successfully.
 * @retval kStatus_Fail    - Rx FIFO is not enabled.
 */
status_t FLEXCAN_ReadEnhancedRxFifo(CAN_Type *base, flexcan_fd_frame_t *pRxFrame);
#endif

#if (defined(FSL_FEATURE_FLEXCAN_HAS_PN_MODE) && FSL_FEATURE_FLEXCAN_HAS_PN_MODE)
/*!
 * @brief Reads a FlexCAN Message from Wake Up MB.
 *
 * This function reads a CAN message from the FlexCAN Wake up Message Buffers. There are four Wake up Message Buffers
 * (WMBs) used to store incoming messages in Pretended Networking mode. The WMB index indicates the arrival order. The
 * last message is stored in WMB3.
 *
 * @param base FlexCAN peripheral base address.
 * @param pRxFrame Pointer to CAN message frame structure for reception.
 * @param mbIdx The FlexCAN Wake up Message Buffer index. Range in 0x0 ~ 0x3.
 * @retval kStatus_Success - Read Message from Wake up Message Buffer successfully.
 * @retval kStatus_Fail    - Wake up Message Buffer has no valid content.
 */
status_t FLEXCAN_ReadPNWakeUpMB(CAN_Type *base, uint8_t mbIdx, flexcan_frame_t *pRxFrame);
#endif
/* @} */

/*!
 * @name Transactional
 * @{
 */

#if (defined(FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE) && FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE)
/*!
 * @brief Performs a polling send transaction on the CAN bus.
 *
 * @note  A transfer handle does not need to be created before calling this API.
 *
 * @param base FlexCAN peripheral base pointer.
 * @param mbIdx The FlexCAN FD Message Buffer index.
 * @param pTxFrame Pointer to CAN FD message frame to be sent.
 * @retval kStatus_Success - Write Tx Message Buffer Successfully.
 * @retval kStatus_Fail    - Tx Message Buffer is currently in use.
 */
status_t FLEXCAN_TransferFDSendBlocking(CAN_Type *base, uint8_t mbIdx, flexcan_fd_frame_t *pTxFrame);

/*!
 * @brief Performs a polling receive transaction on the CAN bus.
 *
 * @note  A transfer handle does not need to be created before calling this API.
 *
 * @param base FlexCAN peripheral base pointer.
 * @param mbIdx The FlexCAN FD Message Buffer index.
 * @param pRxFrame Pointer to CAN FD message frame structure for reception.
 * @retval kStatus_Success            - Rx Message Buffer is full and has been read successfully.
 * @retval kStatus_FLEXCAN_RxOverflow - Rx Message Buffer is already overflowed and has been read successfully.
 * @retval kStatus_Fail               - Rx Message Buffer is empty.
 */
status_t FLEXCAN_TransferFDReceiveBlocking(CAN_Type *base, uint8_t mbIdx, flexcan_fd_frame_t *pRxFrame);

/*!
 * @brief Sends a message using IRQ.
 *
 * This function sends a message using IRQ. This is a non-blocking function, which returns
 * right away. When messages have been sent out, the send callback function is called.
 *
 * @param base FlexCAN peripheral base address.
 * @param handle FlexCAN handle pointer.
 * @param pMbXfer FlexCAN FD Message Buffer transfer structure. See the #flexcan_mb_transfer_t.
 * @retval kStatus_Success        Start Tx Message Buffer sending process successfully.
 * @retval kStatus_Fail           Write Tx Message Buffer failed.
 * @retval kStatus_FLEXCAN_TxBusy Tx Message Buffer is in use.
 */
status_t FLEXCAN_TransferFDSendNonBlocking(CAN_Type *base, flexcan_handle_t *handle, flexcan_mb_transfer_t *pMbXfer);

/*!
 * @brief Receives a message using IRQ.
 *
 * This function receives a message using IRQ. This is non-blocking function, which returns
 * right away. When the message has been received, the receive callback function is called.
 *
 * @param base FlexCAN peripheral base address.
 * @param handle FlexCAN handle pointer.
 * @param pMbXfer FlexCAN FD Message Buffer transfer structure. See the #flexcan_mb_transfer_t.
 * @retval kStatus_Success        - Start Rx Message Buffer receiving process successfully.
 * @retval kStatus_FLEXCAN_RxBusy - Rx Message Buffer is in use.
 */
status_t FLEXCAN_TransferFDReceiveNonBlocking(CAN_Type *base, flexcan_handle_t *handle, flexcan_mb_transfer_t *pMbXfer);

/*!
 * @brief Aborts the interrupt driven message send process.
 *
 * This function aborts the interrupt driven message send process.
 *
 * @param base FlexCAN peripheral base address.
 * @param handle FlexCAN handle pointer.
 * @param mbIdx The FlexCAN FD Message Buffer index.
 */
void FLEXCAN_TransferFDAbortSend(CAN_Type *base, flexcan_handle_t *handle, uint8_t mbIdx);

/*!
 * @brief Aborts the interrupt driven message receive process.
 *
 * This function aborts the interrupt driven message receive process.
 *
 * @param base FlexCAN peripheral base address.
 * @param handle FlexCAN handle pointer.
 * @param mbIdx The FlexCAN FD Message Buffer index.
 */
void FLEXCAN_TransferFDAbortReceive(CAN_Type *base, flexcan_handle_t *handle, uint8_t mbIdx);
#endif

/*!
 * @brief Performs a polling send transaction on the CAN bus.
 *
 * @note  A transfer handle does not need to be created  before calling this API.
 *
 * @param base FlexCAN peripheral base pointer.
 * @param mbIdx The FlexCAN Message Buffer index.
 * @param pTxFrame Pointer to CAN message frame to be sent.
 * @retval kStatus_Success - Write Tx Message Buffer Successfully.
 * @retval kStatus_Fail    - Tx Message Buffer is currently in use.
 */
status_t FLEXCAN_TransferSendBlocking(CAN_Type *base, uint8_t mbIdx, flexcan_frame_t *pTxFrame);

/*!
 * @brief Performs a polling receive transaction on the CAN bus.
 *
 * @note  A transfer handle does not need to be created  before calling this API.
 *
 * @param base FlexCAN peripheral base pointer.
 * @param mbIdx The FlexCAN Message Buffer index.
 * @param pRxFrame Pointer to CAN message frame structure for reception.
 * @retval kStatus_Success            - Rx Message Buffer is full and has been read successfully.
 * @retval kStatus_FLEXCAN_RxOverflow - Rx Message Buffer is already overflowed and has been read successfully.
 * @retval kStatus_Fail               - Rx Message Buffer is empty.
 */
status_t FLEXCAN_TransferReceiveBlocking(CAN_Type *base, uint8_t mbIdx, flexcan_frame_t *pRxFrame);

/*!
 * @brief Performs a polling receive transaction from Legacy Rx FIFO on the CAN bus.
 *
 * @note  A transfer handle does not need to be created before calling this API.
 *
 * @param base FlexCAN peripheral base pointer.
 * @param pRxFrame Pointer to CAN message frame structure for reception.
 * @retval kStatus_Success - Read Message from Rx FIFO successfully.
 * @retval kStatus_Fail    - Rx FIFO is not enabled.
 */
status_t FLEXCAN_TransferReceiveFifoBlocking(CAN_Type *base, flexcan_frame_t *pRxFrame);

#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
/*!
 * @brief Performs a polling receive transaction from Enhanced Rx FIFO on the CAN bus.
 *
 * @note  A transfer handle does not need to be created before calling this API.
 *
 * @param base FlexCAN peripheral base pointer.
 * @param pRxFrame Pointer to CAN FD message frame structure for reception.
 * @retval kStatus_Success - Read Message from Rx FIFO successfully.
 * @retval kStatus_Fail    - Rx FIFO is not enabled.
 */
status_t FLEXCAN_TransferReceiveEnhancedFifoBlocking(CAN_Type *base, flexcan_fd_frame_t *pRxFrame);
#endif

/*!
 * @brief Initializes the FlexCAN handle.
 *
 * This function initializes the FlexCAN handle, which can be used for other FlexCAN
 * transactional APIs. Usually, for a specified FlexCAN instance,
 * call this API once to get the initialized handle.
 *
 * @param base FlexCAN peripheral base address.
 * @param handle FlexCAN handle pointer.
 * @param callback The callback function.
 * @param userData The parameter of the callback function.
 */
void FLEXCAN_TransferCreateHandle(CAN_Type *base,
                                  flexcan_handle_t *handle,
                                  flexcan_transfer_callback_t callback,
                                  void *userData);

/*!
 * @brief Sends a message using IRQ.
 *
 * This function sends a message using IRQ. This is a non-blocking function, which returns
 * right away. When messages have been sent out, the send callback function is called.
 *
 * @param base FlexCAN peripheral base address.
 * @param handle FlexCAN handle pointer.
 * @param pMbXfer FlexCAN Message Buffer transfer structure. See the #flexcan_mb_transfer_t.
 * @retval kStatus_Success        Start Tx Message Buffer sending process successfully.
 * @retval kStatus_Fail           Write Tx Message Buffer failed.
 * @retval kStatus_FLEXCAN_TxBusy Tx Message Buffer is in use.
 */
status_t FLEXCAN_TransferSendNonBlocking(CAN_Type *base, flexcan_handle_t *handle, flexcan_mb_transfer_t *pMbXfer);

/*!
 * @brief Receives a message using IRQ.
 *
 * This function receives a message using IRQ. This is non-blocking function, which returns
 * right away. When the message has been received, the receive callback function is called.
 *
 * @param base FlexCAN peripheral base address.
 * @param handle FlexCAN handle pointer.
 * @param pMbXfer FlexCAN Message Buffer transfer structure. See the #flexcan_mb_transfer_t.
 * @retval kStatus_Success        - Start Rx Message Buffer receiving process successfully.
 * @retval kStatus_FLEXCAN_RxBusy - Rx Message Buffer is in use.
 */
status_t FLEXCAN_TransferReceiveNonBlocking(CAN_Type *base, flexcan_handle_t *handle, flexcan_mb_transfer_t *pMbXfer);

/*!
 * @brief Receives a message from Rx FIFO using IRQ.
 *
 * This function receives a message using IRQ. This is a non-blocking function, which returns
 * right away. When all messages have been received, the receive callback function is called.
 *
 * @param base FlexCAN peripheral base address.
 * @param handle FlexCAN handle pointer.
 * @param pFifoXfer FlexCAN Rx FIFO transfer structure. See the @ref flexcan_fifo_transfer_t.
 * @retval kStatus_Success            - Start Rx FIFO receiving process successfully.
 * @retval kStatus_FLEXCAN_RxFifoBusy - Rx FIFO is currently in use.
 */
status_t FLEXCAN_TransferReceiveFifoNonBlocking(CAN_Type *base,
                                                flexcan_handle_t *handle,
                                                flexcan_fifo_transfer_t *pFifoXfer);

#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
/*!
 * @brief Receives a message from Enhanced Rx FIFO using IRQ.
 *
 * This function receives a message using IRQ. This is a non-blocking function, which returns
 * right away. When all messages have been received, the receive callback function is called.
 *
 * @param base FlexCAN peripheral base address.
 * @param handle FlexCAN handle pointer.
 * @param pFifoXfer FlexCAN Rx FIFO transfer structure. See the ref flexcan_fifo_transfer_t.@
 * @retval kStatus_Success            - Start Rx FIFO receiving process successfully.
 * @retval kStatus_FLEXCAN_RxFifoBusy - Rx FIFO is currently in use.
 */
status_t FLEXCAN_TransferReceiveEnhancedFifoNonBlocking(CAN_Type *base,
                                                        flexcan_handle_t *handle,
                                                        flexcan_fifo_transfer_t *pFifoXfer);

/*!
 * @brief Gets the Enhanced Rx Fifo transfer status during a interrupt non-blocking receive.
 *
 * @param base FlexCAN peripheral base address.
 * @param handle FlexCAN handle pointer.
 * @param count Number of CAN messages receive so far by the non-blocking transaction.
 * @retval kStatus_InvalidArgument count is Invalid.
 * @retval kStatus_Success Successfully return the count.
 */

status_t FLEXCAN_TransferGetReceiveEnhancedFifoCount(CAN_Type *base, flexcan_handle_t *handle, size_t *count);
#endif

/*!
 * @brief Gets the detail index of Mailbox's Timestamp by handle.
 *
 * Then function can only be used when calling non-blocking Data transfer (TX/RX) API,
 * After TX/RX data transfer done (User can get the status by handler's callback function),
 * we can get the detail index of Mailbox's timestamp by handle,
 * Detail non-blocking data transfer API (TX/RX) contain.
 *   -FLEXCAN_TransferSendNonBlocking
 *   -FLEXCAN_TransferFDSendNonBlocking
 *   -FLEXCAN_TransferReceiveNonBlocking
 *   -FLEXCAN_TransferFDReceiveNonBlocking
 *   -FLEXCAN_TransferReceiveFifoNonBlocking
 *
 * @param handle FlexCAN handle pointer.
 * @param mbIdx The FlexCAN Message Buffer index.
 * @retval the index of mailbox 's timestamp stored in the handle.
 *
 */
uint32_t FLEXCAN_GetTimeStamp(flexcan_handle_t *handle, uint8_t mbIdx);

/*!
 * @brief Aborts the interrupt driven message send process.
 *
 * This function aborts the interrupt driven message send process.
 *
 * @param base FlexCAN peripheral base address.
 * @param handle FlexCAN handle pointer.
 * @param mbIdx The FlexCAN Message Buffer index.
 */
void FLEXCAN_TransferAbortSend(CAN_Type *base, flexcan_handle_t *handle, uint8_t mbIdx);

/*!
 * @brief Aborts the interrupt driven message receive process.
 *
 * This function aborts the interrupt driven message receive process.
 *
 * @param base FlexCAN peripheral base address.
 * @param handle FlexCAN handle pointer.
 * @param mbIdx The FlexCAN Message Buffer index.
 */
void FLEXCAN_TransferAbortReceive(CAN_Type *base, flexcan_handle_t *handle, uint8_t mbIdx);

/*!
 * @brief Aborts the interrupt driven message receive from Rx FIFO process.
 *
 * This function aborts the interrupt driven message receive from Rx FIFO process.
 *
 * @param base FlexCAN peripheral base address.
 * @param handle FlexCAN handle pointer.
 */
void FLEXCAN_TransferAbortReceiveFifo(CAN_Type *base, flexcan_handle_t *handle);

#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
/*!
 * @brief Aborts the interrupt driven message receive from Enhanced Rx FIFO process.
 *
 * This function aborts the interrupt driven message receive from Enhanced Rx FIFO process.
 *
 * @param base FlexCAN peripheral base address.
 * @param handle FlexCAN handle pointer.
 */
void FLEXCAN_TransferAbortReceiveEnhancedFifo(CAN_Type *base, flexcan_handle_t *handle);
#endif

/*!
 * @brief FlexCAN IRQ handle function.
 *
 * This function handles the FlexCAN Error, the Message Buffer, and the Rx FIFO IRQ request.
 *
 * @param base FlexCAN peripheral base address.
 * @param handle FlexCAN handle pointer.
 */
void FLEXCAN_TransferHandleIRQ(CAN_Type *base, flexcan_handle_t *handle);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_FLEXCAN_H_ */
