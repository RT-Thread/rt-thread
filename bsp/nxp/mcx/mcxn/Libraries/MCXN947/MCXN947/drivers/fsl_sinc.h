/*
 * Copyright 2022-2024 NXP
 *
 * All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_SINC_H_
#define FSL_SINC_H_

#include "fsl_common.h"

/*!
 * @addtogroup sinc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief lower_component_name driver version 2.1.4. */
#define FSL_SINC_DRIVER_VERSION (MAKE_VERSION(2, 1, 4))
/*! @} */
#if defined(FSL_FEATURE_SINC_CHANNEL_COUNT)
#define SINC_CHANNEL_COUNT (FSL_FEATURE_SINC_CHANNEL_COUNT)
#else
#error "The definition of FSL_FEATURE_SINC_CHANNEL_COUNT is missing!"
#endif
#define SINC_NORMAL_INT_REG_ID     (0ULL)
#define SINC_NORMAL_INT_NAME_COCIE (0ULL)
#define SINC_NORMAL_INT_NAME_CHFIE (1ULL)
#define SINC_NORMAL_INT_NAME_ZCDIE (2ULL)

#define SINC_ERROR_INT_REG_ID      (1ULL)
#define SINC_ERROR_INT_NAME_SCDIE  (0ULL)
#define SINC_ERROR_INT_NAME_WLMTIE (1ULL)
#define SINC_ERROR_INT_NAME_LLMTIE (2ULL)
#define SINC_ERROR_INT_NAME_HLMTIE (3ULL)

#define SINC_FIFO_CAD_INT_REG_ID (2ULL)
#define SINC_FIFO_CAD_INT_FUNFIE (0ULL)
#define SINC_FIFO_CAD_INT_FOVFIE (1ULL)
#define SINC_FIFO_CAD_INT_CADIE  (2ULL)
#define SINC_FIFO_CAD_INT_SATIE  (3ULL)

#define SINC_ENCODE_INTERRUPT(regId, name, channelId)                                           \
    ((((1ULL << (uint64_t)(channelId))) << ((uint64_t)(name) * (uint64_t)(SINC_CHANNEL_COUNT))) \
     << (uint64_t)(regId)*20ULL)

#define SINC_DECODE_INTERRUPT(interruptMask)                               \
    normalIntMask  = ((uint32_t)(interruptMask) & (0xFFFFFUL));            \
    errorIntMask   = ((uint32_t)((interruptMask) >> 20ULL) & (0xFFFFFUL)); \
    fifoCadIntMask = ((uint32_t)((interruptMask) >> 40ULL) & (0xFFFFFUL))

#define SINC_FIND_INT_FIELD_VALUE(mask, name)                                     \
    ((((uint32_t)(mask) >> ((uint32_t)(name) * ((uint32_t)SINC_CHANNEL_COUNT))) & \
      ((1UL << ((uint32_t)SINC_CHANNEL_COUNT)) - 1UL))                            \
     << (8UL * (uint32_t)(name)))

#define SINC_FIND_STATUS_FIELD_VALUE(statusValue, name)                \
    (((uint64_t)(statusValue) & (0xFFUL << ((uint64_t)(name)*8UL))) >> \
     ((uint64_t)(name) * (8UL - ((uint64_t)SINC_CHANNEL_COUNT))))
/*!
 * @brief The enumeration of SINC module's interrupts.
 * @anchor sinc_interrupt_enable_t
 */
enum _sinc_interrupt_enable
{
    /* Normal interrupts enable. */
    /* Enable the conversion complete interrupt for channel 0. */
    kSINC_CH0ConvCompleteIntEnable = SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_COCIE, 0ULL),
    /* Enable the conversion complete interrupt for channel 1. */
    kSINC_CH1ConvCompleteIntEnable = SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_COCIE, 1ULL),
    /* Enable the conversion complete interrupt for channel 2. */
    kSINC_CH2ConvCompleteIntEnable = SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_COCIE, 2ULL),
    /* Enable the conversion complete interrupt for channel 3. */
    kSINC_CH3ConvCompleteIntEnable = SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_COCIE, 3ULL),
#if (SINC_CHANNEL_COUNT >= 5UL)
    /* Enable the conversion complete interrupt for channel 4. */
    kSINC_CH4ConvCompleteIntEnable = SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_COCIE, 4ULL),
#endif

    /* Enable the data output ready interrupt for channel 0. */
    kSINC_CH0DataReadyIntEnable = SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_CHFIE, 0ULL),
    /* Enable the data output ready interrupt for channel 1. */
    kSINC_CH1DataReadyIntEnable = SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_CHFIE, 1ULL),
    /* Enable the data output ready interrupt for channel 2. */
    kSINC_CH2DataReadyIntEnable = SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_CHFIE, 2ULL),
    /* Enable the data output ready interrupt for channel 3. */
    kSINC_CH3DataReadyIntEnable = SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_CHFIE, 3ULL),
#if (SINC_CHANNEL_COUNT >= 5UL)
    /* Enable the data output ready interrupt for channel 4. */
    kSINC_CH4DataReadyIntEnable = SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_CHFIE, 4ULL),
#endif

    /* Enable the zero cross detected interrupt for channel 0. */
    kSINC_CH0ZeroCrossDetectedIntEnable =
        SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_ZCDIE, 0ULL),
    /* Enable the zero cross detected interrupt for channel 1. */
    kSINC_CH1ZeroCrossDetectedIntEnable =
        SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_ZCDIE, 1ULL),
    /* Enable the zero cross detected interrupt for channel 2. */
    kSINC_CH2ZeroCrossDetectedIntEnable =
        SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_ZCDIE, 2ULL),
    /* Enable the zero cross detected interrupt for channel 3. */
    kSINC_CH3ZeroCrossDetectedIntEnable =
        SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_ZCDIE, 3ULL),
#if (SINC_CHANNEL_COUNT >= 5UL)
    /* Enable the zero cross detected interrupt for channel 4. */
    kSINC_CH4ZeroCrossDetectedIntEnable =
        SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_ZCDIE, 4ULL),
#endif

    /* Error interrupts enable. */
    /* Enable the short circuit detected interrupt for channel 0. */
    kSINC_CH0SCDIntEnable = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_SCDIE, 0ULL),
    /* Enable the short circuit detected interrupt for channel 1. */
    kSINC_CH1SCDIntEnable = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_SCDIE, 1ULL),
    /* Enable the short circuit detected interrupt for channel 2. */
    kSINC_CH2SCDIntEnable = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_SCDIE, 2ULL),
    /* Enable the short circuit detected interrupt for channel 3. */
    kSINC_CH3SCDIntEnable = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_SCDIE, 3ULL),
#if (SINC_CHANNEL_COUNT >= 5UL)
    /* Enable the short circuit detected interrupt for channel 4. */
    kSINC_CH4SCDIntEnable = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_SCDIE, 4ULL),
#endif

    /* Enable the window limit interrupt for channel 0. */
    kSINC_CH0WindowLimitIntEnable = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_WLMTIE, 0ULL),
    /* Enable the window limit interrupt for channel 1. */
    kSINC_CH1WindowLimitIntEnable = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_WLMTIE, 1ULL),
    /* Enable the window limit interrupt for channel 2. */
    kSINC_CH2WindowLimitIntEnable = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_WLMTIE, 2ULL),
    /* Enable the window limit interrupt for channel 3. */
    kSINC_CH3WindowLimitIntEnable = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_WLMTIE, 3ULL),
#if (SINC_CHANNEL_COUNT >= 5UL)
    /* Enable the window limit interrupt for channel 4. */
    kSINC_CH4WindowLimitIntEnable = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_WLMTIE, 4ULL),
#endif

    /* Enable the low limit interrupt for channel 0. */
    kSINC_CH0LowLimitIntEnable = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_LLMTIE, 0ULL),
    /* Enable the low limit interrupt for channel 1. */
    kSINC_CH1LowLimitIntEnable = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_LLMTIE, 1ULL),
    /* Enable the low limit interrupt for channel 2. */
    kSINC_CH2LowLimitIntEnable = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_LLMTIE, 2ULL),
    /* Enable the low limit interrupt for channel 3. */
    kSINC_CH3LowLimitIntEnable = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_LLMTIE, 3ULL),
#if (SINC_CHANNEL_COUNT >= 5UL)
    /* Enable the low limit interrupt for channel 4. */
    kSINC_CH4LowLimitIntEnable = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_LLMTIE, 4ULL),
#endif

    /* Enable the high limit interrupt for channel 0. */
    kSINC_CH0HighLimitIntEnable = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_HLMTIE, 0ULL),
    /* Enable the high limit interrupt for channel 1. */
    kSINC_CH1HighLimitIntEnable = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_HLMTIE, 1ULL),
    /* Enable the high limit interrupt for channel 2. */
    kSINC_CH2HighLimitIntEnable = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_HLMTIE, 2ULL),
    /* Enable the high limit interrupt for channel 3. */
    kSINC_CH3HighLimitIntEnable = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_HLMTIE, 3ULL),
#if (SINC_CHANNEL_COUNT >= 5UL)
    /* Enable the high limit interrupt for channel 4. */
    kSINC_CH4HighLimitIntEnable = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_HLMTIE, 4ULL),
#endif

    /* FIFO and CAD(clock-absence detector) Error interrupts enable. */
    /* Enable the FIFO underflow interrupt for channel 0. */
    kSINC_CH0FifoUnderflowIntEnable = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_FUNFIE, 0ULL),
    /* Enable the FIFO underflow interrupt for channel 1. */
    kSINC_CH1FifoUnderflowIntEnable = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_FUNFIE, 1ULL),
    /* Enable the FIFO underflow interrupt for channel 2. */
    kSINC_CH2FifoUnderflowIntEnable = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_FUNFIE, 2ULL),
    /* Enable the FIFO underflow interrupt for channel 3. */
    kSINC_CH3FifoUnderflowIntEnable = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_FUNFIE, 3ULL),
#if (SINC_CHANNEL_COUNT >= 5UL)
    /* Enable the FIFO underflow interrupt for channel 4. */
    kSINC_CH4FifoUnderflowIntEnable = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_FUNFIE, 4ULL),
#endif

    /* Enable the FIFO overflow interrupt for channel 0. */
    kSINC_CH0FifoOverflowIntEnable = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_FOVFIE, 0ULL),
    /* Enable the FIFO overflow interrupt for channel 1. */
    kSINC_CH1FifoOverflowIntEnable = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_FOVFIE, 1ULL),
    /* Enable the FIFO overflow interrupt for channel 2. */
    kSINC_CH2FifoOverflowIntEnable = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_FOVFIE, 2ULL),
    /* Enable the FIFO overflow interrupt for channel 3. */
    kSINC_CH3FifoOverflowIntEnable = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_FOVFIE, 3ULL),
#if (SINC_CHANNEL_COUNT >= 5UL)
    /* Enable the FIFO overflow interrupt for channel 4. */
    kSINC_CH4FifoOverflowIntEnable = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_FOVFIE, 4ULL),
#endif

    /* Enable the clock absence interrupt for channel 0. */
    kSINC_CH0CADIntEnable = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_CADIE, 0ULL),
    /* Enable the clock absence interrupt for channel 1. */
    kSINC_CH1CADIntEnable = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_CADIE, 1ULL),
    /* Enable the clock absence interrupt for channel 2. */
    kSINC_CH2CADIntEnable = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_CADIE, 2ULL),
    /* Enable the clock absence interrupt for channel 3. */
    kSINC_CH3CADIntEnable = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_CADIE, 3ULL),
#if (SINC_CHANNEL_COUNT >= 5UL)
    /* Enable the clock absence interrupt for channel 4. */
    kSINC_CH4CADIntEnable = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_CADIE, 4ULL),
#endif

    /* Enable the saturation interrupt for channel 0. */
    kSINC_CH0SaturationIntEnable = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_SATIE, 0ULL),
    /* Enable the saturation interrupt for channel 1. */
    kSINC_CH1SaturationIntEnable = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_SATIE, 1ULL),
    /* Enable the saturation interrupt for channel 2. */
    kSINC_CH2SaturationIntEnable = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_SATIE, 2ULL),
    /* Enable the saturation interrupt for channel 3. */
    kSINC_CH3SaturationIntEnable = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_SATIE, 3ULL),
#if (SINC_CHANNEL_COUNT >= 5UL)
    /* Enable the saturation interrupt for channel 4. */
    kSINC_CH4SaturationIntEnable = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_SATIE, 4ULL),
#endif
};

/*!
 * @brief The enumeration of SINC interrupt status flags.
 * @anchor sinc_interrupt_status_t
 */
enum _sinc_interrupt_status
{
    /* Normal interrupts status. */
    /* One conversion has finished and data is available in channel 0. */
    kSINC_CH0ConvCompleteIntStatus = SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_COCIE, 0ULL),
    /* One conversion has finished and data is available in channel 1. */
    kSINC_CH1ConvCompleteIntStatus = SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_COCIE, 1ULL),
    /* One conversion has finished and data is available in channel 2. */
    kSINC_CH2ConvCompleteIntStatus = SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_COCIE, 2ULL),
    /* One conversion has finished and data is available in channel 3. */
    kSINC_CH3ConvCompleteIntStatus = SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_COCIE, 3ULL),
#if (SINC_CHANNEL_COUNT >= 5UL)
    /* One conversion has finished and data is available in channel 4. */
    kSINC_CH4ConvCompleteIntStatus = SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_COCIE, 4ULL),
#endif /* (SINC_CHANNEL_COUNT >= 5UL) */

    /* The FIFO of channel 0 has exceeded its watermark level and the data is available in channel 0 result register. */
    kSINC_CH0DataReadyIntStatus = SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_CHFIE, 0ULL),
    /* The FIFO of channel 1 has exceeded its watermark level and the data is available in channel 1 result register. */
    kSINC_CH1DataReadyIntStatus = SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_CHFIE, 1ULL),
    /* The FIFO of channel 2 has exceeded its watermark level and the data is available in channel 2 result register. */
    kSINC_CH2DataReadyIntStatus = SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_CHFIE, 2ULL),
    /* The FIFO of channel 3 has exceeded its watermark level and the data is available in channel 3 result register. */
    kSINC_CH3DataReadyIntStatus = SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_CHFIE, 3ULL),
#if (SINC_CHANNEL_COUNT >= 5UL)
    /* The FIFO of channel 4 has exceeded its watermark level and the data is available in channel 4 result register. */
    kSINC_CH4DataReadyIntStatus = SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_CHFIE, 4ULL),
#endif /* (SINC_CHANNEL_COUNT >= 5UL) */

    /* The resulting data on channel 0 crossed zero and changed sign. */
    kSINC_CH0ZeroCrossDetectedIntStatus =
        SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_ZCDIE, 0ULL),
    /* The resulting data on channel 1 crossed zero and changed sign. */
    kSINC_CH1ZeroCrossDetectedIntStatus =
        SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_ZCDIE, 1ULL),
    /* The resulting data on channel 2 crossed zero and changed sign. */
    kSINC_CH2ZeroCrossDetectedIntStatus =
        SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_ZCDIE, 2ULL),
    /* The resulting data on channel 3 crossed zero and changed sign. */
    kSINC_CH3ZeroCrossDetectedIntStatus =
        SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_ZCDIE, 3ULL),
#if (SINC_CHANNEL_COUNT >= 5UL)
    /* The resulting data on channel 4 crossed zero and changed sign. */
    kSINC_CH4ZeroCrossDetectedIntStatus =
        SINC_ENCODE_INTERRUPT(SINC_NORMAL_INT_REG_ID, SINC_NORMAL_INT_NAME_ZCDIE, 4ULL),
#endif /* (SINC_CHANNEL_COUNT >= 5UL) */

    /* Error interrupts Status. */
    /* SINC detected a short circuit on channel 0. */
    kSINC_CH0SCDIntStatus = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_SCDIE, 0ULL),
    /* SINC detected a short circuit on channel 1. */
    kSINC_CH1SCDIntStatus = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_SCDIE, 1ULL),
    /* SINC detected a short circuit on channel 2. */
    kSINC_CH2SCDIntStatus = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_SCDIE, 2ULL),
    /* SINC detected a short circuit on channel 3. */
    kSINC_CH3SCDIntStatus = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_SCDIE, 3ULL),
#if (SINC_CHANNEL_COUNT >= 5UL)
    /* SINC detected a short circuit on channel 4. */
    kSINC_CH4SCDIntStatus = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_SCDIE, 4ULL),
#endif /* (SINC_CHANNEL_COUNT >= 5UL) */

    /* Indicates channel 0 exceeded its window limit. */
    kSINC_CH0WindowLimitIntStatus = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_WLMTIE, 0ULL),
    /* Indicates channel 1 exceeded its window limit. */
    kSINC_CH1WindowLimitIntStatus = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_WLMTIE, 1ULL),
    /* Indicates channel 2 exceeded its window limit. */
    kSINC_CH2WindowLimitIntStatus = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_WLMTIE, 2ULL),
    /* Indicates channel 3 exceeded its window limit. */
    kSINC_CH3WindowLimitIntStatus = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_WLMTIE, 3ULL),
#if (SINC_CHANNEL_COUNT >= 5UL)
    /* Indicates channel 4 exceeded its window limit. */
    kSINC_CH4WindowLimitIntStatus = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_WLMTIE, 4ULL),
#endif /* (SINC_CHANNEL_COUNT >= 5UL) */

    /* Indicates channel 0 exceeded its low limit. */
    kSINC_CH0LowLimitIntStatus = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_LLMTIE, 0ULL),
    /* Indicates channel 1 exceeded its window limit. */
    kSINC_CH1LowLimitIntStatus = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_LLMTIE, 1ULL),
    /* Indicates channel 2 exceeded its window limit. */
    kSINC_CH2LowLimitIntStatus = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_LLMTIE, 2ULL),
    /* Indicates channel 3 exceeded its window limit. */
    kSINC_CH3LowLimitIntStatus = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_LLMTIE, 3ULL),
#if (SINC_CHANNEL_COUNT >= 5UL)
    /* Indicates channel 4 exceeded its window limit. */
    kSINC_CH4LowLimitIntStatus = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_LLMTIE, 4ULL),
#endif /* (SINC_CHANNEL_COUNT >= 5UL) */

    /* Indicates channel 0 exceeded its high limit. */
    kSINC_CH0HighLimitIntStatus = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_HLMTIE, 0ULL),
    /* Indicates channel 1 exceeded its high limit. */
    kSINC_CH1HighLimitIntStatus = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_HLMTIE, 1ULL),
    /* Indicates channel 2 exceeded its high limit. */
    kSINC_CH2HighLimitIntStatus = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_HLMTIE, 2ULL),
    /* Indicates channel 3 exceeded its high limit. */
    kSINC_CH3HighLimitIntStatus = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_HLMTIE, 3ULL),
#if (SINC_CHANNEL_COUNT >= 5UL)
    /* Indicates channel 4 exceeded its high limit. */
    kSINC_CH4HighLimitIntStatus = SINC_ENCODE_INTERRUPT(SINC_ERROR_INT_REG_ID, SINC_ERROR_INT_NAME_HLMTIE, 4ULL),
#endif /* (SINC_CHANNEL_COUNT >= 5UL) */

    /* FIFO and CAD(clock-absence detector) Error interrupts Status. */
    /* A FIFO underflow occurred on channel 0. */
    kSINC_CH0FifoUnderflowIntStatus = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_FUNFIE, 0ULL),
    /* A FIFO underflow occurred on channel 1. */
    kSINC_CH1FifoUnderflowIntStatus = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_FUNFIE, 1ULL),
    /* A FIFO underflow occurred on channel 2. */
    kSINC_CH2FifoUnderflowIntStatus = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_FUNFIE, 2ULL),
    /* A FIFO underflow occurred on channel 3. */
    kSINC_CH3FifoUnderflowIntStatus = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_FUNFIE, 3ULL),
#if (SINC_CHANNEL_COUNT >= 5UL)
    /* A FIFO underflow occurred on channel 4. */
    kSINC_CH4FifoUnderflowIntStatus = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_FUNFIE, 4ULL),
#endif /* (SINC_CHANNEL_COUNT >= 5UL) */

    /* A FIFO overflow occurred on channel 0. */
    kSINC_CH0FifoOverflowIntStatus = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_FOVFIE, 0ULL),
    /* A FIFO overflow occurred on channel 1. */
    kSINC_CH1FifoOverflowIntStatus = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_FOVFIE, 1ULL),
    /* A FIFO overflow occurred on channel 2. */
    kSINC_CH2FifoOverflowIntStatus = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_FOVFIE, 2ULL),
    /* A FIFO overflow occurred on channel 3. */
    kSINC_CH3FifoOverflowIntStatus = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_FOVFIE, 3ULL),
#if (SINC_CHANNEL_COUNT >= 5UL)
    /* A FIFO overflow occurred on channel 4. */
    kSINC_CH4FifoOverflowIntStatus = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_FOVFIE, 4ULL),
#endif /* (SINC_CHANNEL_COUNT >= 5UL) */

    /* SINC detected the absence of a clock on channel 0. */
    kSINC_CH0CADIntStatus = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_CADIE, 0ULL),
    /* SINC detected the absence of a clock on channel 1. */
    kSINC_CH1CADIntStatus = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_CADIE, 1ULL),
    /* SINC detected the absence of a clock on channel 2. */
    kSINC_CH2CADIntStatus = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_CADIE, 2ULL),
    /* SINC detected the absence of a clock on channel 3. */
    kSINC_CH3CADIntStatus = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_CADIE, 3ULL),
#if (SINC_CHANNEL_COUNT >= 5UL)
    /* SINC detected the absence of a clock on channel 4. */
    kSINC_CH4CADIntStatus = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_CADIE, 4ULL),
#endif /* (SINC_CHANNEL_COUNT >= 5UL) */

    /* Channel 0 is saturated. */
    kSINC_CH0SaturationIntStatus = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_SATIE, 0ULL),
    /* Channel 1 is saturated. */
    kSINC_CH1SaturationIntStatus = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_SATIE, 1ULL),
    /* Channel 2 is saturated. */
    kSINC_CH2SaturationIntStatus = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_SATIE, 2ULL),
    /* Channel 3 is saturated. */
    kSINC_CH3SaturationIntStatus = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_SATIE, 3ULL),
#if (SINC_CHANNEL_COUNT >= 5UL)
    /* Channel 4 is saturated. */
    kSINC_CH4SaturationIntStatus = SINC_ENCODE_INTERRUPT(SINC_FIFO_CAD_INT_REG_ID, SINC_FIFO_CAD_INT_SATIE, 4ULL),
#endif /* (SINC_CHANNEL_COUNT >= 5UL) */
};

/*!
 * @brief The enumeration of channel id, the sinc module contains 4 channels.
 */
typedef enum _sinc_channel_id
{
    kSINC_Channel0 = 0U, /*!< Channel 0. */
    kSINC_Channel1,      /*!< Channel 1. */
    kSINC_Channel2,      /*!< Channel 2. */
    kSINC_Channel3,      /*!< Channel 3. */
} sinc_channel_id_t;

/*!
 * @brief The enumeration of modulator clock name.
 * @anchor _sinc_modulator_clock
 */
enum _sinc_modulator_clock
{
    kSINC_ModClk0 = 1UL, /*!< Modulator Clock 0 output. */
    kSINC_ModClk1 = 2UL, /*!< Modulator Clock 1 output. */
    kSINC_ModClk2 = 4UL, /*!< Modulator Clock 2 output. */
};

/*!
 * @brief The enumeration of input clock.
 */
typedef enum _sinc_inputClk_source
{
    kSINC_InputClk_SourceMclkOut0             = 0U, /*!< MCLK_OUT0 with internal routeback. */
    kSINC_InputClk_SourceMclkOut1             = 1U, /*!< MCLK_OUT1 with internal routeback. */
    kSINC_InputClk_SourceMclkOut2             = 2U, /*!< MCLK_OUT2 with internal routeback. */
    kSINC_InputClk_SourceExternalModulatorClk = 3U, /*!< External modulator clock dedicated to the selected channel. */
    kSINC_InputClk_SourceAdjacentChannelClk   = 7U, /*!< Grouped clock shared with an adjacent channel. */
} sinc_inputClk_source_t;

/*!
 * @brief The enumeration of clock edge.
 */
typedef enum _sinc_inputClk_edge
{
    kSINC_InputClk_EdgePositive = 1U, /*!< Positive edge. */
    kSINC_InputClk_EdgeNegative,      /*!< Negative edge. */
    kSINC_InputClk_EdgeBoth,          /*!< Both edges. */
    kSINC_InputClk_EdgeOddPositive,   /*!< Every other odd positive edge. */
    kSINC_InputClk_EdgeEvenPositive,  /*!< Every other even positive edge. */
    kSINC_InputClk_EdgeOddNegative,   /*!< Every other odd negative edge. */
    kSINC_InputClk_EdgeEvenNegative,  /*!< Every other even negative edge. */
} sinc_inputClk_edge_t;

/*!
 * @brief The enumeration of input bit format.
 */
typedef enum _sinc_inputBit_format
{
    kSINC_InputBit_FormatExternalBitstream = 0U,    /*!< External bitstream from the MBIT[n] signal. */
    kSINC_InputBit_FormatExternalManchesterCode,    /*!< External Manchester code. */
    kSINC_InputBit_FormatInternal16bitParallelData, /*!< Internal 16-bit parallel data from MPDATA register. */
    kSINC_InputBit_FormatInternal32bitSerialData,   /*!< Internal 32-bit serial data from MPDATA. */
} sinc_inputBit_format_t;

/*!
 * @brief The enumeration of input bit source.
 */
typedef enum _sinc_inputBit_source
{
    kSINC_InputBit_SourceExternalBitstream = 0U, /*!< External bitstream from the MBIT[n] signal. */
    kSINC_InputBit_SourceInternalBitstream = 1U, /*!< Alternate internal bitstream from the INP[n] signal. */
    kSINC_InputBit_SourceAdjacentChannel   = 3U, /*!< Grouped bitstream shared with an adjacent chanel. */
} sinc_inputBit_source_t;

/*!
 * @brief The enumeration of trigger source.
 */
typedef enum _sinc_conv_trigger_source
{
    kSINC_ConvTrig_SoftPosEdge     = 0x0U, /*!< Positive edge software trigger. */
    kSINC_ConvTrig_SoftHighLevel   = 0x4U, /*!< High level software trigger. */
    kSINC_ConvTrig_HardPosEdge     = 0x1U, /*!< Positive edge hardware trigger. */
    kSINC_ConvTrig_HardHighLevel   = 0x5U, /*!< High level hardware trigger. */
    kSINC_ConvTrig_AdjacentChannel = 0x3U, /*!< Grouped hardware trigger shared with an adjacent channel. */
} sinc_conv_trigger_source_t;

/*!
 * @brief The enumeration of conversion mode.
 */
typedef enum _sinc_conv_mode
{
    kSINC_ConvMode_Single = 0U, /*!< One conversion that follows an edge or level trigger event. */
    kSINC_ConvMode_Continuous,  /*!< Multiple conversions that follow a triggering event, a new triggering event
                                    cancels and restarts conversion. */
    kSINC_ConvMode_Always,      /*!< Multiple conversions that follow the first triggering event, SINC ignores the
                                    next triggering event. */
    kSINC_ConvMode_FixedNumber, /*!< Fixed number conversions that follow the first triggering event, a new
                                    triggering event cancels and restarts conversion. */
} sinc_conv_mode_t;

/*!
 * @brief The enumeration of pulse trigger mux.
 */
typedef enum _sinc_pulse_trigger_mux
{
    kSINC_PulseTrigger_Disabled = 0U,              /*!< Disable pulse trigger output. */
    kSINC_PulseTrigger_MuxHighLimitLevelSignal,    /*!< Select high limit level signal for pulse trigger output. */
    kSINC_PulseTrigger_MuxLowLimitLevelSignal,     /*!< Select low limit level signal for pulse trigger output. */
    kSINC_PulseTrigger_MuxHighLowLimitLevelSignal, /*!< Select low or high limit level signal for pulse trigger output.
                                                    */
    kSINC_PulseTrigger_MuxWindowLimitLevelSignal,  /*!< Select window limit level signal for pulse trigger output. */
    kSINC_PulseTrigger_MuxZeroCrossRisingLevelSignal,  /*!< Select zero cross rising level signal for pulse trigger
                                                          output. */
    kSINC_PulseTrigger_MuxZeroCrossFallingLevelSignal, /*!< Select zero cross falling level signal for pulse trigger
                                                          output. */
    kSINC_PulseTrigger_MuxRsLimHighLevelSignal,        /*!< Select level signal that indicates a high level from an RS
                                                          flip-flop or a schmitt trigger for pulse trigger output. */
    kSINC_PulseTrigger_MuxRsLimLowLevelSignal, /*!< Select level signal that indicates a low level from an RS flip-flop
                                                  or a schmitt trigger for pulse trigger output. */
    kSINC_PulseTrigger_MuxChannelRawInputModBitStream,  /*!< Select channel raw input modulator bitstream for pulse
                                                           trigger output. */
    kSINC_PulseTrigger_MuxChannelRawInputModClock,      /*!< Select channel raw input modulator clock for pulse trigger
                                                           output. */
    kSINC_PulseTrigger_MuxChannelRecoveredModBitStream, /*!< Select channel output recovered modulator bitstream for
                                                           pulse trigger output. */
    kSINC_PulseTrigger_MuxChannelRecoveredModClock,     /*!< Select channel output recovered modulator clock for pulse
                                                           trigger output. */
    kSINC_PulseTrigger_MuxHighLimitPulseSignal,         /*!< Select high limit pulse signal for pulse trigger output. */
    kSINC_PulseTrigger_MuxLowLimitPulseSignal,          /*!< Select low limit pulse signal for pulse trigger output. */
    kSINC_PulseTrigger_MuxLimitPulseSignal, /*!< Select the pulse signal that indicates a high/low/window limit for
                                               pulse trigger output. */
    kSINC_PulseTrigger_MuxWindowLimitPulseSignal,   /*!< Select window limit pulse signal for pulse trigger output. */
    kSINC_PulseTrigger_MuxHighLowLimitPulseSignal,  /*!< Select the pulse signal that indicates a high or low limit for
                                                       pulse trigger output. */
    kSINC_PulseTrigger_MuxZeroCrossRisePulseSignal, /*!< Select zero cross rise pulse signal for trigger output. */
    kSINC_PulseTrigger_MuxZeroCrossFallPulseSignal, /*!< Select zero cross fall pulse signal for trigger output. */
    kSINC_PulseTrigger_MuxZeroCrossRiseFallPulseSignal, /*!< Select zero cross rise/fall pulse signal for trigger
                                                           output. */
    kSINC_PulseTrigger_MuxFifoWatermarkOkPulseSignal, /*!< Select FIFO watermark OK pulse signal for trigger output. */
    kSINC_PulseTrigger_MuxFifoOverflowPulseSignal,    /*!< Select FIFO overflow pulse signal. */
    kSINC_PulseTrigger_MuxFifoUnderflowPulseSignal,   /*!< Select FIFO underflow pulse signal. */
    kSINC_PulseTrigger_MuxFifoEmptyPulseSignal,       /*!< Select FIFO empty pulse signal. */
    kSINC_PulseTrigger_MuxClockMonitorAssertPulseSignal, /*!< Select clock monitor assert pulse signal. */
    kSINC_PulseTrigger_MuxShortCircuitAssertPulseSignal, /*!< Select short circuit assert pulse signal. */
    kSINC_PulseTrigger_MuxSaturationPulseSignal,         /*!< Select saturation pulse signal. */
    kSINC_PulseTrigger_MuxConversionCompletePulseSignal, /*!< Select conversion complete pulse signal. */
} sinc_pulse_trigger_mux_t;

/*!
 * @brief The enumeration of zero cross detector operate mode.
 */
typedef enum _sinc_zero_cross_operate_mode
{
    kSINC_ZCD_BothRiseAndFall = 0U, /*!< Zero cross detector operate on both rise and fall. */
    kSINC_ZCD_OnlyFall,             /*!< Zero cross detector operate on fall edge. */
    kSINC_ZCD_OnlyRise,             /*!< Zero cross detector operate on rise edge. */
    kSINC_ZCD_Disabled = 0xFU,      /*!< Zero cross detector disabled. */
} sinc_zero_cross_operate_mode_t;

/*!
 * @brief The enumeration of primary filter order.
 */
typedef enum _sinc_primary_filter_order
{
    kSINC_PF_FastSinc = 0U, /*!< Fast sinc filter, ORD is 4. */
    kSINC_PF_FirstOrder,    /*!< First order filter, ORD is 1. */
    kSINC_PF_SecondOrder,   /*!< Second order filter, ORD is 2. */
    kSINC_PF_ThirdOrder,    /*!< Third order filter, ORD is 3. */
} sinc_primary_filter_order_t;

/*!
 * @brief The enumeration of clock prescale that specify the clock divider ratio for the modulator clock.
 */
typedef enum _sinc_clock_prescale
{
    kSINC_ClkPrescale1 = 0UL, /*!< No prescale. */
    kSINC_ClkPrescale2,       /*!< Modulator clock divider ratio is 2. */
    kSINC_ClkPrescale4,       /*!< Modulator clock divider ratio is 4. */
    kSINC_ClkPrescale8,       /*!< Modulator clock divider ratio is 8. */
} sinc_clock_prescale_t;

/*!
 * @brief The enumeration of primary filter shift direction.
 */
typedef enum _sinc_primary_filter_shift_direction
{
    kSINC_PF_ShiftRight = 0U,       /*!< Right shift the raw data. */
    kSINC_PF_ShiftLeft  = 1U << 4U, /*!< Left shift the raw data. */
} sinc_primary_filter_shift_direction_t;

/*!
 * @brief The enumeration of primary filer bias sign.
 */
typedef enum _sinc_primary_filter_bias_sign
{
    kSINC_PF_BiasPositive = 0UL, /*!< The bias sign is positive. */
    kSINC_PF_BiasNegative,       /*!< The bias sign is negative. */
} sinc_primary_filter_bias_sign_t;

/*!
 * @brief The enumeration of HPF DC remover Alpha coefficient.
 */
typedef enum _sinc_primary_filter_hpf_alpha_coeff
{
    kSINC_PF_HPFAlphaCoeff0 = 0UL, /*!< Disabled HPF. */
    kSINC_PF_HPFAlphaCoeff1,       /*!< Alpha coefficient = 1 - (2^-5) */
    kSINC_PF_HPFAlphaCoeff2,       /*!< Alpha coefficient = 1 - (2^-6) */
    kSINC_PF_HPFAlphaCoeff3,       /*!< Alpha coefficient = 1 - (2^-7) */
    kSINC_PF_HPFAlphaCoeff4,       /*!< Alpha coefficient = 1 - (2^-8) */
    kSINC_PF_HPFAlphaCoeff5,       /*!< Alpha coefficient = 1 - (2^-9) */
    kSINC_PF_HPFAlphaCoeff6,       /*!< Alpha coefficient = 1 - (2^-10) */
    kSINC_PF_HPFAlphaCoeff7,       /*!< Alpha coefficient = 1 - (2^-11) */
    kSINC_PF_HPFAlphaCoeff8,       /*!< Alpha coefficient = 1 - (2^-12) */
    kSINC_PF_HPFAlphaCoeff9,       /*!< Alpha coefficient = 1 - (2^-13) */
    kSINC_PF_HPFAlphaCoeff10,      /*!< Alpha coefficient = 1 - (2^-14) */
    kSINC_PF_HPFAlphaCoeff11,      /*!< Alpha coefficient = 1 - (2^-15) */
    kSINC_PF_HPFAlphaCoeff12,      /*!< Alpha coefficient = 1 - (2^-16) */
    kSINC_PF_HPFAlphaCoeff13,      /*!< Alpha coefficient = 1 - (2^-17) */
    kSINC_PF_HPFAlphaCoeff14,      /*!< Alpha coefficient = 1 - (2^-18) */
    kSINC_PF_HPFAlphaCoeff15,      /*!< Alpha coefficient = 1 - (2^-19) */
} sin_primary_filter_hpf_alpha_coeff_t;

/*!
 * @brief The enumeration of input bit delay.
 */
typedef enum _sinc_inputBit_delay
{
    kSINC_InputBit_DelayDisabled = 0U, /*!< Input modulator bitstream delay disabled. */
    kSINC_InputBit_Delay1ClkCycle,     /*!< Input modulator bitstream delay 1 PRE_CLK cycle. */
    kSINC_InputBit_Delay2ClkCycle,     /*!< Input modulator bitstream delay 2 PRE_CLK cycle. */
    kSINC_InputBit_Delay3ClkCycle,     /*!< Input modulator bitstream delay 3 PRE_CLK cycle. */
    kSINC_InputBit_Delay4ClkCycle,     /*!< Input modulator bitstream delay 4 PRE_CLK cycle. */
    kSINC_InputBit_Delay5ClkCycle,     /*!< Input modulator bitstream delay 5 PRE_CLK cycle. */
    kSINC_InputBit_Delay6ClkCycle,     /*!< Input modulator bitstream delay 6 PRE_CLK cycle. */
    kSINC_InputBit_Delay7ClkCycle,     /*!< Input modulator bitstream delay 7 PRE_CLK cycle. */
    kSINC_InputBit_Delay8ClkCycle,     /*!< Input modulator bitstream delay 8 PRE_CLK cycle. */
    kSINC_InputBit_Delay9ClkCycle,     /*!< Input modulator bitstream delay 9 PRE_CLK cycle. */
    kSINC_InputBit_Delay10ClkCycle,    /*!< Input modulator bitstream delay 10 PRE_CLK cycle. */
    kSINC_InputBit_Delay11ClkCycle,    /*!< Input modulator bitstream delay 11 PRE_CLK cycle. */
    kSINC_InputBit_Delay12ClkCycle,    /*!< Input modulator bitstream delay 12 PRE_CLK cycle. */
    kSINC_InputBit_Delay13ClkCycle,    /*!< Input modulator bitstream delay 13 PRE_CLK cycle. */
    kSINC_InputBit_Delay14ClkCycle,    /*!< Input modulator bitstream delay 14 PRE_CLK cycle. */
    kSINC_InputBit_Delay15ClkCycle,    /*!< Input modulator bitstream delay 15 PRE_CLK cycle. */
} sinc_inputBit_delay_t;

/*!
 * @brief The enumeration of short-circuit detector operate mode.
 */
typedef enum _sinc_scd_operate_mode
{
    kSINC_Scd_OperateAtChannelEnabled = 0U, /*!< SCD operates when the channel is enabled. */
    kSINC_Scd_OperateAtConversion,          /*!< SCD operates when the PF is performing a conversion. */
    kSINC_Scd_OperateDisabled = 0xFU,       /*!< Short circuit detect is disabled. */
} sinc_scd_operate_mode_t;

/*!
 * @brief The enumeration of short-circuit detector option.
 */
typedef enum _sinc_scd_option
{
    kSINC_Scd_DetectRepeating0And1 = 0U, /*!< Both repeating 0 and 1 increment the SCD counter. */
    kSINC_Scd_DetectRepeatingOnly1,      /*!< Only repeating 1 increment the SCD counter. */
    kSINC_Scd_DetectRepeatingOnly0,      /*!< Only repeating 1 increment the SCD counter. */
} sinc_scd_option_t;

/*!
 * @brief The mode of limit detector.
 *
 * @note The value of each limit detector contains lot of information:
 *  bit[1:0]: limit detection options,
 *  bit[2]: low limit break signal.
 *  bit[3]: window limit break signal.
 *  bit[4]: High limit break signal.
 *  bit[7]: Enable/disable limit detector.
 */
typedef enum _sinc_limit_detector_mode
{
    kSINC_Lmt_BothHighAndLowLimit = 0x94U, /*!< Limit detector is enabled, and compare the filter sample value to high
                                            and low limit, if the value larger than high limit will trigger
                                            interrupt or break, and if the value lower than low limit will trigger
                                            interrupt or break. */
    kSINC_Lmt_OnlyHighLimit = 0x91U, /*!< Limit detector is enabled, and compare the filter sample value to high limit,
                                if the value larger than high limit will trigger interrupt or break. */
    kSINC_Lmt_OnlyLowLimit = 0x86U, /*!< Limit detector is enabled, and compare the filter sample value to low limit, if
                                the value lower than low limit will trigger interrupt or break. */
    kSINC_Lmt_WindowedValue = 0x8BU, /*!< Limit detector is enabled, and compare the filter sample value to high and low
                                 limit, if the value higher than low limit and lower than high limit will trigger
                                 interrupt or break. */
    kSINC_Lmt_Disabled = 0x0U,       /*!< Limit detector is disabled. */

} sinc_limit_detector_mode_t;

/*!
 * @brief The enumeration of clock-absence threshold.
 */
typedef enum _sinc_cad_threshold
{
    kSINC_Cad_Disabled = 0U,   /*!< Clock absence detector is disabled. */
    kSINC_Cad_Count1ClkCycle,  /*!< Clock absence detector threshold is 1 clock cycle. */
    kSINC_Cad_Count2ClkCycle,  /*!< Clock absence detector threshold is 2 clock cycle. */
    kSINC_Cad_Count3ClkCycle,  /*!< Clock absence detector threshold is 3 clock cycle. */
    kSINC_Cad_Count4ClkCycle,  /*!< Clock absence detector threshold is 4 clock cycle. */
    kSINC_Cad_Count5ClkCycle,  /*!< Clock absence detector threshold is 5 clock cycle. */
    kSINC_Cad_Count6ClkCycle,  /*!< Clock absence detector threshold is 6 clock cycle. */
    kSINC_Cad_Count7ClkCycle,  /*!< Clock absence detector threshold is 7 clock cycle. */
    kSINC_Cad_Count8ClkCycle,  /*!< Clock absence detector threshold is 8 clock cycle. */
    kSINC_Cad_Count9ClkCycle,  /*!< Clock absence detector threshold is 9 clock cycle. */
    kSINC_Cad_Count10ClkCycle, /*!< Clock absence detector threshold is 10 clock cycle. */
    kSINC_Cad_Count11ClkCycle, /*!< Clock absence detector threshold is 11 clock cycle. */
    kSINC_Cad_Count12ClkCycle, /*!< Clock absence detector threshold is 12 clock cycle. */
    kSINC_Cad_Count13ClkCycle, /*!< Clock absence detector threshold is 13 clock cycle. */
    kSINC_Cad_Count14ClkCycle, /*!< Clock absence detector threshold is 14 clock cycle. */
    kSINC_Cad_Count15ClkCycle, /*!< Clock absence detector threshold is 15 clock cycle. */
} sinc_cad_threshold_t;

#if (defined(FSL_FEATURE_SINC_CACFR_HAS_ADMASEL) && FSL_FEATURE_SINC_CACFR_HAS_ADMASEL)
/*!
 * @brief The enumeration of alternate DMA source.
 */
typedef enum _sinc_alternate_dma_source
{
    kSINC_AltDma_Disabled = 0U,        /*!< Alternate DMA disabled. */
    kSINC_AltDma_PfConvComplete,       /*!< Select PF conversion complete for alternate DMA. */
    kSINC_AltDma_PfDataOutputReady,    /*!< Select PF data output ready for alternate DMA. */
    kSINC_AltDma_ZeroCrossDetected,    /*!< Select zero crossing detected for alternate DMA. */
    kSINC_AltDma_ShortCircuitDetected, /*!< Select short circuit detected for alternate DMA. */
    kSINC_AltDma_WindowLimitDetected,  /*!< Select window limit detected for alternate DMA. */
    kSINC_AltDma_LowLimitDetected,     /*!< Select low limit detected for alternate DMA. */
    kSINC_AltDma_HighLimitDetected,    /*!< Select high limit detected for alternate DMA. */
    kSINC_AltDma_FifoUnderflow,        /*!< Select FIFO underflow detected for alternate DMA. */
    kSINC_AltDma_FifoOverflow,         /*!< Select FIFO overflow detected for alternate DMA. */
    kSINC_AltDma_ClockAbsence,         /*!< Select clock absence detected for alternate DMA. */
    kSINC_AltDma_Saturation,           /*!< Select channel saturation for alternate DMA. */
} sinc_alternate_dma_source_t;
#endif /* (defined(FSL_FEATURE_SINC_CACFR_HAS_ADMASEL) && FSL_FEATURE_SINC_CACFR_HAS_ADMASEL) */

/*!
 * @brief The enumeration of result data format.
 */
typedef enum _sinc_result_data_format
{
    kSINC_LeftJustifiedSigned = 0U, /*!< Left justified, signed. */
    kSINC_LeftJustifiedUnsigned,    /*!< Left justified, unsigned. */
} sinc_result_data_format_t;

/*!
 * @brief The enumeration of debug output.
 */
typedef enum _sinc_debug_output
{
    kSINC_Debug_PfFinalData = 0U,              /*!< Final data from PF(24 bits). */
    kSINC_Debug_OffsetData,                    /*!< Offset data(24 bits). */
    kSINC_Debug_PfShiftedData,                 /*!< Shifted data from the PF(24 bits). */
    kSINC_Debug_HpfData,                       /*!< DC remover(HPF) data(32 bits). */
    kSINC_Debug_CicRawData,                    /*!< Raw data from the PF's CIC filter. */
    kSINC_Debug_ScdHistoricalData,             /*!< Historical data from SCD. */
    kSINC_Debug_ManchesterDecoderData,         /*!< Data from the Manchester decoder. */
    kSINC_Debug_CadData,                       /*!< Data from CAD. */
    kSINC_Debug_FifoEntriesNum,                /*!< Number of available entries in the FIFO. */
    kSINC_Debug_ParallelSerialConverterStatus, /*!< Status of the parallel or serial data converter. */
} sinc_debug_output_t;

/*!
 * @brief The structure of channel input options, including input bit settings and input clock settings.
 */
typedef struct _sinc_channel_input_option
{
    sinc_inputBit_format_t inputBitFormat; /*!< Specify input bit format, please refer
                                                to @ref sinc_inputBit_format_t. */
    sinc_inputBit_source_t inputBitSource; /*!< Specify input bit source, please refer
                                                to @ref sinc_inputBit_source_t. */
    sinc_inputBit_delay_t inputBitDelay;   /*!< Specify input bit delay, please refer to @ref sinc_inputBit_delay_t. */

    sinc_inputClk_source_t inputClkSource; /*!< Specify input clock source, please refer
                                                to @ref sinc_inputClk_source_t. */
    sinc_inputClk_edge_t inputClkEdge;     /*!< Specify input clock edge, please refer to @ref sinc_inputClk_edge_t. */
} sinc_channel_input_option_t;

/*!
 * @brief The structure of channel conversion options, including CIC filter settings, HPF settings, shift settings,
 * bias settings and so on.
 */
typedef struct _sinc_channel_conv_option
{
    sinc_conv_mode_t convMode; /*!< Specify conversion mode, please refer to @ref sinc_conv_mode_t. */
    sinc_conv_trigger_source_t convTriggerSource; /*!< Specify conversion trigger source, please
                                                        refer to @ref sinc_conv_trigger_source_t. */

    bool enableChPrimaryFilter;                   /*!< Enable/disable channel's primary filter. */
    sinc_primary_filter_order_t pfOrder;          /*!< Specify the order of primary filter, please
                                                      refer to @ref sinc_primary_filter_order_t.  */
    uint16_t u16pfOverSampleRatio;                /*!< Control primary filter's OSR, the minimum permissible value is 3,
                                                      low value produce unpredictable result, the maximum permissible value depend on
                                                      PF order and the desired data format, if PF order is third order and data format
                                                      is signed, the maximum OSR value is 1289, if PF order is third order and data
                                                      format is unsigned, the maximum OSR value is 1624, otherwise the maximum OSR
                                                      value is 2047. Please note that the OSR for equation is
                                                      u16pfOverSampleRatio + 1*/

    sin_primary_filter_hpf_alpha_coeff_t pfHpfAlphaCoeff;   /*!< Specify HPF's alpha coeff, please
                                                                refer to @ref sin_primary_filter_hpf_alpha_coeff_t.  */

    sinc_primary_filter_shift_direction_t pfShiftDirection; /*!< Select shift direction, right or left. */
    uint8_t u8pfShiftBitsNum; /*!< Specify the number of bits to shift the data, ranges from 0 to 15. */

    sinc_primary_filter_bias_sign_t pfBiasSign; /*!< Select bias sign, please refer
                                                    to @ref sinc_primary_filter_bias_sign_t. */
    uint32_t u32pfBiasValue;                    /*!< Range from 0 to 0x7FFFFFUL. */
} sinc_channel_conv_option_t;

/*!
 * @brief The structure of channel protection options, including limit check settings, short-circuit settings,
 * clock-absence settings, and zero-crossing settings.
 */
typedef struct _sinc_channel_protection_option
{
    sinc_limit_detector_mode_t limitDetectorMode; /*!< Specify limit detector mode, please
                                                      refer to @ref sinc_limit_detector_mode_t. */
    bool bEnableLmtBreakSignal;                   /*!< Enable/disable limit break signal,
                                                      the details of break signal is depended on detector mode. */
    uint32_t u32LowLimitThreshold;          /*!< Specify the low-limit threshold value, range from 0 to 0xFFFFFFUL. */
    uint32_t u32HighLimitThreshold;         /*!< Specify the high-limit threshold value, range from 0 to 0xFFFFFFUL. */

    sinc_scd_operate_mode_t scdOperateMode; /*!< Enable/disable scd, and set SCD operate timming.  */
    uint8_t u8ScdLimitThreshold;            /*!< Range from 2 to 255, 0 and 1 are prohibited. */
    sinc_scd_option_t scdOption;            /*!< Specify SCD options, please refer to @ref sinc_scd_option_t. */
    bool bEnableScdBreakSignal;             /*!< Enable/disable SCD break signal.  */

    sinc_cad_threshold_t cadLimitThreshold; /*!< Specify the threshold value for the CAD counter. */
    bool bEnableCadBreakSignal;             /*!< Enable/disable CAD break signal. */

    sinc_zero_cross_operate_mode_t zcdOperateMode; /*!< Specify zero cross detector operate mode. */
} sinc_channel_protection_option_t;

/*!
 * @brief The structure of channel configurations, including channel input option, channel conversion options, channel
 * protection options, and so on.
 */
typedef struct _sinc_channel_config
{
    bool bEnableChannel;                      /*!< Enable/disable channel. */
    bool bEnableFifo;                         /*!< Enable/disable channel's FIFO. */
    uint8_t u8FifoWaterMark;                  /*!< Specify the fifo watermark, range from 0 to 15. */
    bool bEnablePrimaryDma;                   /*!< Used to enable/disable primary DMA. */
#if (defined(FSL_FEATURE_SINC_CACFR_HAS_ADMASEL) && FSL_FEATURE_SINC_CACFR_HAS_ADMASEL)
    sinc_alternate_dma_source_t altDmaSource; /*!< Set channel's alternate DMA source, please refer
                                                  to @ref sinc_alternate_dma_source_t. */
#endif /* (defined(FSL_FEATURE_SINC_CACFR_HAS_ADMASEL) && FSL_FEATURE_SINC_CACFR_HAS_ADMASEL) */
    sinc_result_data_format_t dataFormat;       /*!< Set channel's result data format, please refer
                                                    to @ref sinc_result_data_format_t. */

    sinc_channel_input_option_t *chInputOption; /*!< The pointer to @ref sinc_channel_input_option_t that contains
                                                   channel input options. */
    sinc_channel_conv_option_t *chConvOption;   /*!< The pointer to @ref sinc_channel_conv_option_t that contains
                                                    channel conversion options. */
    sinc_channel_protection_option_t *chProtectionOption; /*!< The pointer to @ref sinc_channel_protection_option_t
                                                  that contains channel protection options. */
} sinc_channel_config_t;

/*!
 * @brief The structure of sinc configurations, including clock settings anc channels' settings.
 */
typedef struct _sinc_config
{
    sinc_clock_prescale_t clockPreDivider; /*!< Specify modulator clock pre divider, please
                                               refer to @ref sinc_clock_prescale_t. */
    uint32_t modClkDivider;    /*!<  Range from 2 to 256, 0 and 1 are prohibited, to obtain a 50% duty cycle in
                                   the MCLK output, write an even value to*/
    bool disableModClk0Output; /*!< Disable/enable modulator clock0 output. */
    bool disableModClk1Output; /*!< Disable/enable modulator clock1 output. */
    bool disableModClk2Output; /*!< Disable/enable modulator clock2 output. */

    sinc_channel_config_t *channelsConfigArray[SINC_CHANNEL_COUNT]; /*!< The array that contains 4 elements, and the
                                                   type of each element is \b sinc_channel_config_t *,
                                                   channelsConfigArray[0] corresponding to channel0,
                                                   channelsConfigArray[1] corresponding to channel1,
                                                   channelsConfigArray[2] corresponding to channel2,
                                                   channelsConfigArray[3] corresponding to channel3, if some channels
                                                   are not used, the corresponding elements should be set as NULL. */

    bool disableDozeMode; /*!< Disable/enable SINC module when the chip enters Doze or stop mode.  */
    bool enableMaster;    /*!< Enable/disable all function blocks of SINC module. */
} sinc_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @name SINC Generic Functional Control APIs
 * @{
 */

/*!
 * @brief Initialize selected SINC instance, including clock options and channel options.
 *
 * @param base SINC peripheral base address.
 * @param config The pointer to @ref sinc_config_t structure.
 */
void SINC_Init(SINC_Type *base, const sinc_config_t *config);

/*!
 * @brief De-initialize selected SINC instance.
 *
 * @param base SINC peripheral base address.
 */
void SINC_Deinit(SINC_Type *base);

/*!
 * @brief Get default configuration.
 *
 * @code {.c}
 *     config->clockPreDivider = kSINC_ClkPrescale1;
 *     config->modClkDivider   = 2UL;
 *     config->disableModClk0Output = false;
 *     config->disableModClk1Output = false;
 *     config->disableModClk2Output = false;
 *
 *     config->channelsConfigArray[4] = {NULL, NULL, NULL, NULL};
 *
 *     config->disableDozeMode      = false;
 *     config->enableMaster         = false;
 * @endcode
 *
 *
 * @param config The pointer to @ref sinc_config_t structure, must not be NULL.
 */
void SINC_GetDefaultConfig(sinc_config_t *config);

/*! @} */

/*!
 * @name SINC Generic Low Level Control APIs
 * @{
 */

/*!
 * @brief Enable/disable all function blocks enabled in their respective registers.
 *
 * @param base SINC peripheral base address.
 * @param enable Used to enable/disable all function blocks:
 *          - \b true Enable all function blocks, please note that clock must be configured previously;
 *          - \b false Disable all function blocks.
 */
static inline void SINC_EnableMaster(SINC_Type *base, bool enable)
{
    if (enable)
    {
        base->MCR |= SINC_MCR_MEN_MASK;
    }
    else
    {
        base->MCR &= ~SINC_MCR_MEN_MASK;
    }
}

/*!
 * @brief Reset all function blocks(except for the clock blocks), interrupt statuses.
 *
 * @param base SINC peripheral base address.
 */
static inline void SINC_DoSoftwareReset(SINC_Type *base)
{
    base->MCR |= SINC_MCR_RST_MASK;
    base->MCR &= ~SINC_MCR_RST_MASK;
}

/*!
 * @brief Disable/enable SINC module when the chip enters Doze or Stop mode.
 *
 * @param base SINC peripheral base address.
 * @param disable Used to control if module functional when the chip enters Doze and Stop mode:
 *          - \b true Disable SINC when the chip enters Doze or Stop mode;
 *          - \b false Enable SINC when the chip enters Doze or stop mode.
 */
static inline void SINC_DisableDozeMode(SINC_Type *base, bool disable)
{
    if (disable)
    {
        base->MCR |= SINC_MCR_DOZEN_MASK;
    }
    else
    {
        base->MCR &= ~SINC_MCR_DOZEN_MASK;
    }
}

/*! @} */

/*!
 * @name Clock Control APIs
 * @{
 */

/*!
 * @brief Check whether selected modulator clocks are ready.
 *
 * @note The result of this APIs means all selected modulator clocks are (not) ready.
 *
 * @param base SINC peripheral base address.
 * @param modClkMasks The mask of modulator clocks, please refer to @ref _sinc_modulator_clock.
 *
 * @retval true The input mask of modulator clocks are ready.
 * @retval false The input mask of modulator clocks are not ready.
 */
static inline bool SINC_CheckModulatorClockReady(SINC_Type *base, uint32_t modClkMasks)
{
    return ((base->SR & (modClkMasks << SINC_SR_MCLKRDY0_SHIFT)) != 0UL);
}

/*!
 * @brief Disable/enable modulator clocks' output.
 *
 * @note By default, modulator clock's output is enabled.
 *
 * @param base SINC peripheral base address.
 * @param modClkMasks The mask of modulator clocks, please refer to @ref _sinc_modulator_clock.
 * @param disable Used to enable/disable clock output:
 *          - \b true Disable modulator clocks' output;
 *          - \b false Enable modulator clocks' output.
 */
static inline void SINC_DisableModulatorClockOutput(SINC_Type *base, uint32_t modClkMasks, bool disable)
{
    if (disable)
    {
        base->MCR |= (modClkMasks << SINC_MCR_MCLK0DIS_SHIFT);
    }
    else
    {
        base->MCR &= ~(modClkMasks << SINC_MCR_MCLK0DIS_SHIFT);
    }
}

/*!
 * @brief Set the clock divider ratio for the modulator clock.
 *
 * @param base SINC peripheral base address.
 * @param clkPrescale Clock prescale value, please refer to @ref sinc_clock_prescale_t.
 */
static inline void SINC_SetClkPrescale(SINC_Type *base, sinc_clock_prescale_t clkPrescale)
{
    base->MCR = (((base->MCR) & (~SINC_MCR_PRESCALE_MASK)) | SINC_MCR_PRESCALE(clkPrescale));
}

/*!
 * @brief Set modulator clock divider value.
 *
 * @note IMCLK0 = PRE_CLK / modClkDivider, the minimum clock divider ration is 2.
 *
 * @param base SINC peripheral base address.
 * @param modClkDivider Range from 2 to 256, 0 and 1 are prohibited, to obtain a 50% duty cycle in the MCLK output,
 *                      write an even value to \b modClkDivider .
 */
static inline void SINC_SetModulatorClockDivider(SINC_Type *base, uint32_t modClkDivider)
{
    assert(modClkDivider != 0UL);
    assert(modClkDivider != 1UL);

    base->MCR = (((base->MCR) & (~SINC_MCR_MCLKDIV_MASK)) | SINC_MCR_MCLKDIV((modClkDivider - 1UL)));
}

/* !} */

/*!
 * @name Channel Functional Control APIs
 * @{
 */

/*!
 * @brief Set channel configurations, including input options, conversion options and protection options.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param chConfig Pointer to @ref sinc_channel_config_t structure, must not be NULL.
 */
void SINC_SetChannelConfig(SINC_Type *base, sinc_channel_id_t chId, sinc_channel_config_t *chConfig);

/*!
 * @brief Set channel input options, including input bit format, input bit source, input bit delay, input clock source,
 * input clock edge.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param chInputOption Pointer to @ref sinc_channel_input_option_t structure, must not be NULL.
 */
void SINC_SetChannelInputOption(SINC_Type *base, sinc_channel_id_t chId, sinc_channel_input_option_t *chInputOption);

/*!
 * @brief Set channel conversion options, including conversion mode, trigger source, and primary filter settings.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param chConvOption Pointer to @ref sinc_channel_conv_option_t structure, must not be NULL.
 */
void SINC_SetChannelConversionOption(SINC_Type *base, sinc_channel_id_t chId, sinc_channel_conv_option_t *chConvOption);

/*!
 * @brief Set channel protection options, including limit check, short-circuit detector, clock-absence detector, and
 * zero-crossing detector.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param chProtection Pointer to @ref sinc_channel_protection_option_t, must not be NULL.
 */
void SINC_SetChannelProtectionOption(SINC_Type *base,
                                     sinc_channel_id_t chId,
                                     sinc_channel_protection_option_t *chProtection);

/*! @} */

/*!
 * @name Channel Result/FIFO Low Level Control APIs
 * @{
 */

/*!
 * @brief Read selected channel's result data.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 *
 * @return Result data of the selected channel, 24 bits width.
 */
static inline uint32_t SINC_ReadChannelResultData(SINC_Type *base, sinc_channel_id_t chId)
{
    return ((base->CHANNEL[(uint8_t)chId].CRDATA & SINC_CRDATA_RDATA_MASK) >> SINC_CRDATA_RDATA_SHIFT);
}

/*!
 * @brief Enable/disable FIFO transfers for the primary filter.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param enable Used to enable/disable channl FIFO:
 *          - \b true Enable channel FIFO.
 *          - \b false Disable channle FIFO.
 */
static inline void SINC_EnableChannelFIFO(SINC_Type *base, sinc_channel_id_t chId, bool enable)
{
    if (enable)
    {
        base->CHANNEL[(uint8_t)chId].CCR |= SINC_CCR_FIFOEN_MASK;
    }
    else
    {
        base->CHANNEL[(uint8_t)chId].CCR &= ~SINC_CCR_FIFOEN_MASK;
    }
}

/*!
 * @brief Set the FIFO watermark.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param fifoWaterMark Specify the fifo watermark, range from 0 to 15.
 */
static inline void SINC_SetChannelFifoWatermark(SINC_Type *base, sinc_channel_id_t chId, uint8_t fifoWaterMark)
{
    base->CHANNEL[(uint8_t)chId].CCFR =
        ((base->CHANNEL[(uint8_t)chId].CCFR) & (~SINC_CCFR_FIFOWMK_MASK)) | (SINC_CCFR_FIFOWMK(fifoWaterMark));
}

/*!
 * @brief Enable/disable selected channel.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param enable Used to enable/disable selected channel:
 *          - \b true Enable selected channel;
 *          - \b false Disable selected channel.
 */
static inline void SINC_EnableChannel(SINC_Type *base, sinc_channel_id_t chId, bool enable)
{
    if (enable)
    {
        base->CHANNEL[(uint8_t)chId].CCR |= SINC_CCR_CHEN_MASK;
    }
    else
    {
        base->CHANNEL[(uint8_t)chId].CCR &= ~SINC_CCR_CHEN_MASK;
    }
}

/*!
 * @brief Enable/disable selected channel's primary DMA transfers when the channel's FIFO exceeds its watermark.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param enable Used to enable/disable primary DMA :
 *          - \b true Enable primary DMA;
 *          - \b false Disable primary DMA.
 */
static inline void SINC_EnableChannelPrimaryDma(SINC_Type *base, sinc_channel_id_t chId, bool enable)
{
    if (enable)
    {
        base->CHANNEL[(uint8_t)chId].CCR |= SINC_CCR_DMAEN_MASK;
    }
    else
    {
        base->CHANNEL[(uint8_t)chId].CCR &= ~SINC_CCR_DMAEN_MASK;
    }
}

#if (defined(FSL_FEATURE_SINC_CACFR_HAS_ADMASEL) && FSL_FEATURE_SINC_CACFR_HAS_ADMASEL)
/*!
 * @brief Set selected channel's alternate DMA source selection.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param altDmaSource Specify the trigger source for alternate DMA, please refer to @ref sinc_alternate_dma_source_t.
 */
static inline void SINC_SetChannelAltDmaSource(SINC_Type *base,
                                               sinc_channel_id_t chId,
                                               sinc_alternate_dma_source_t altDmaSource)
{
    base->CHANNEL[(uint8_t)chId].CACFR =
        ((base->CHANNEL[(uint8_t)chId].CACFR & ~SINC_CACFR_ADMASEL_MASK) | SINC_CACFR_ADMASEL(altDmaSource));
}
#endif /* (defined(FSL_FEATURE_SINC_CACFR_HAS_ADMASEL) && FSL_FEATURE_SINC_CACFR_HAS_ADMASEL) */

/*!
 * @brief Set selected channel's result data format.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param dataFormat Specify the result data format, please refer to @ref sinc_result_data_format_t.
 */
static inline void SINC_SetChannelResultDataFormat(SINC_Type *base,
                                                   sinc_channel_id_t chId,
                                                   sinc_result_data_format_t dataFormat)
{
    if (dataFormat == kSINC_LeftJustifiedSigned)
    {
        base->CHANNEL[(uint8_t)chId].CCFR &= ~SINC_CCFR_RDFMT_MASK;
    }
    else
    {
        base->CHANNEL[(uint8_t)chId].CCFR |= SINC_CCFR_RDFMT_MASK;
    }
}

/*!
 * @brief Get the number of remaining data entries in the FIFO.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 *
 * @return The number of remaining data entries in the FIFO.
 */
static inline uint8_t SINC_GetChannelFifoCount(SINC_Type *base, sinc_channel_id_t chId)
{
    return (uint8_t)(base->CHANNEL[(uint8_t)chId].CSR & SINC_CSR_FIFOAVIL_MASK);
}

/*!
 * @brief Check whether the data in selected channel's result data register is stable when FIFO is disabled.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, refer to @ref sinc_channel_id_t for details.
 *
 * @retval true Data in selected channel's result data regiter is stable.
 * @retval false Data in selected channel's result data register is not stable.
 */
static inline bool SINC_CheckChannelResultDataReady(SINC_Type *base, sinc_channel_id_t chId)
{
    return ((base->CHANNEL[(uint8_t)chId].CSR & SINC_CSR_RDRS_MASK) != SINC_CSR_RDRS_MASK);
}

/*!
 * @brief Check whether selected channel's FIFO is empty.
 *
 * @param base SINC peripheral base address.
 * @param chId The id of sinc channel to check.
 *
 * @retval true Selected channel's FIFO is empty.
 * @retval false Selected channel's FIFO is not empty.
 */
static inline bool SINC_CheckChannelFifoEmpty(SINC_Type *base, sinc_channel_id_t chId)
{
    return ((base->SR & (SINC_SR_FIFOEMPTY0_MASK << (uint32_t)chId)) != 0UL);
}

/*! @} */

/*!
 * @name Channel Conversion Low Level Control APIs
 * @{
 */

/*!
 * @brief Trigger selected channel's conversion.
 *
 * @param base SINC peripheral base address.
 * @param chMask The mask of channels to trigger.
 */
static inline void SINC_AffirmChannelSoftwareTrigger(SINC_Type *base, uint32_t chMask)
{
    base->MCR |= chMask;
}

/*!
 * @brief Negate the trigger of selected channel.
 *
 * @param base SINC peripheral base address.
 * @param chMask The mask of channels.
 */
static inline void SINC_NegateChannelSoftwareTrigger(SINC_Type *base, uint32_t chMask)
{
    base->MCR &= ~chMask;
}

/*!
 * @brief Set selected channel's conversion mode.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param mode The conversion mode to set, please refer to @ref sinc_conv_mode_t.
 */
static inline void SINC_SetChannelConversionMode(SINC_Type *base, sinc_channel_id_t chId, sinc_conv_mode_t mode)
{
    base->CHANNEL[(uint8_t)chId].CDR = ((base->CHANNEL[(uint8_t)chId].CDR & ~SINC_CDR_PFCM_MASK) | SINC_CDR_PFCM(mode));
}

/*!
 * @brief Set selected channel's trigger source.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param triggerSource Trigger source to set, please refer to @ref sinc_conv_trigger_source_t.
 */
static inline void SINC_SetChannelTriggerSource(SINC_Type *base,
                                                sinc_channel_id_t chId,
                                                sinc_conv_trigger_source_t triggerSource)
{
    base->CHANNEL[(uint8_t)chId].CCFR =
        (((base->CHANNEL[(uint8_t)chId].CCFR) & ~(SINC_CCFR_ITLVL_MASK | SINC_CCFR_ITSEL_MASK)) |
         SINC_CCFR_ITLVL((((uint32_t)triggerSource) & 0x4UL) >> 2UL) |
         SINC_CCFR_ITSEL((uint32_t)triggerSource & 0x3UL));
}

/*!
 * @brief Set multipurpose data to selected channel.
 *
 * @note If input bit format is set as ManchesterCode, multipurpose data indicates the Manchester decoder threshold
 * value and is 11 bits width; if input bit format is set as parallel, multipurpose data indicates the parallel 16-bit
 * data and is 16 bits width; if input bit format is set as serial, multipurpose data indicates the serial data and is
 * 32 bits width.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param data Multipurpose data to set.
 */
static inline void SINC_SetChannelMultipurposeData(SINC_Type *base, sinc_channel_id_t chId, uint32_t data)
{
    base->CHANNEL[(uint8_t)chId].CMPDATA = SINC_CMPDATA_MPDATA(data);
}

/*!
 * @brief Set selected channel's PF order.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param pfOrder Primary filter order to set, please refer to @ref sinc_primary_filter_order_t
 */
static inline void SINC_SetChannelPfOrder(SINC_Type *base, sinc_channel_id_t chId, sinc_primary_filter_order_t pfOrder)
{
    base->CHANNEL[(uint8_t)chId].CDR =
        ((base->CHANNEL[(uint8_t)chId].CDR) & (~SINC_CDR_PFORD_MASK)) | (SINC_CDR_PFORD(pfOrder));
}

/*!
 * @brief Set selected channel's PF over sample rate.
 *
 * @note If PF order is third order and data format is signed, the maximum OSR value is 1289, if PF order is third
 * order and data format is unsigned, the maximum OSR value is 1624, otherwise the maximum OSR value is 2047.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param pfOsr Control the channel's PF OSR, the minimum permissible value is 3, low value produce unpredictable
 * result, the maximum permissible value depend on PF order and the desired data format.
 */
static inline void SINC_SetChannelPfOsr(SINC_Type *base, sinc_channel_id_t chId, uint16_t pfOsr)
{
    base->CHANNEL[(uint8_t)chId].CDR =
        ((base->CHANNEL[(uint8_t)chId].CDR) & (~SINC_CDR_PFOSR_MASK)) | (SINC_CDR_PFOSR(pfOsr));
}

/*!
 * @brief set selected channel's HPF DC remover Alpha coefficient.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param pfHpfAlphaCoeff Specify the HPF alpha coefficient or disable HPF as described in @ref
 * sin_primary_filter_hpf_alpha_coeff_t.
 */
static inline void SINC_SetChannelPfHpfAlphaCoeff(SINC_Type *base,
                                                  sinc_channel_id_t chId,
                                                  sin_primary_filter_hpf_alpha_coeff_t pfHpfAlphaCoeff)
{
    base->CHANNEL[(uint8_t)chId].CACFR =
        ((base->CHANNEL[(uint8_t)chId].CACFR) & (~SINC_CACFR_HPFA_MASK)) | (SINC_CACFR_HPFA(pfHpfAlphaCoeff));
}

/*!
 * @brief Set the value that shifts the PF data for the correct 24-bit precision.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param pfShiftDirection Specify the PF shift direction, including right and left.
 * @param pfShiftBitsNum Specify the PF shift value, range from 0 to 15.
 */
static inline void SINC_SetChannelPfShiftConfig(SINC_Type *base,
                                                sinc_channel_id_t chId,
                                                sinc_primary_filter_shift_direction_t pfShiftDirection,
                                                uint8_t pfShiftBitsNum)
{
    base->CHANNEL[(uint8_t)chId].CCFR = ((base->CHANNEL[(uint8_t)chId].CCFR) & (~SINC_CCFR_PFSFT_MASK)) |
                                        (SINC_CCFR_PFSFT((uint32_t)pfShiftDirection | (uint32_t)pfShiftBitsNum));
}

/*!
 * @brief Set the bias offset for the selected channel's PF.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param pfBiasSign Specify the bias sign, please refer to @ref sinc_primary_filter_bias_sign_t for details.
 * @param pfBiasValue The bias value to subtracted from the output of PF shift block, range from 0 to 0x7FFFFFUL.
 */
static inline void SINC_SetChannelPfBiasConfig(SINC_Type *base,
                                               sinc_channel_id_t chId,
                                               sinc_primary_filter_bias_sign_t pfBiasSign,
                                               uint32_t pfBiasValue)
{
    base->CHANNEL[(uint8_t)chId].CBIAS = (uint32_t)pfBiasSign << 31UL | pfBiasValue << SINC_CBIAS_BIAS_SHIFT;
}

/*!
 * @brief Enable/disable selected channel's primary filter.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param enable Used to enable primary filter:
 *          - \b true Enable channel's PF;
 *          - \b false Disable channel's PF.
 */
static inline void SINC_EnableChannelPrimaryFilter(SINC_Type *base, sinc_channel_id_t chId, bool enable)
{
    if (enable)
    {
        base->CHANNEL[(uint8_t)chId].CCR |= SINC_CCR_PFEN_MASK;
    }
    else
    {
        base->CHANNEL[(uint8_t)chId].CCR &= ~SINC_CCR_PFEN_MASK;
    }
}

/*!
 * @brief Check whether selected channel's multipurpose data is ready to write parallel or serial data.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, refer to @ref sinc_channel_id_t for details.
 *
 * @retval true Selected channel's multipurpose data is ready to write parallel or serial data.
 * @retval false Selected channel's multipurpose data is not ready to write parallel or serial data.
 */
static inline bool SINC_CheckChannelParallelSerialDataReady(SINC_Type *base, sinc_channel_id_t chId)
{
    return ((base->CHANNEL[(uint8_t)chId].CSR & SINC_CSR_PSRDY_MASK) == SINC_CSR_PSRDY_MASK);
}

/*!
 * @brief Check whether primary CIC filter saturation occurred.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, refer to @ref sinc_channel_id_t for details.
 *
 * @retval true Selected channel's primary CIC filter saturation occurred.
 * @retval false Selected channel's primary CIC filter saturation did not occurred.
 */
static inline bool SINC_CheckChannelPrimaryCICSaturation(SINC_Type *base, sinc_channel_id_t chId)
{
    return ((base->CHANNEL[(uint8_t)chId].CSR & SINC_CSR_PFSAT_MASK) == SINC_CSR_PFSAT_MASK);
}

/*!
 * @brief Check whether HPF saturation occurred.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, refer to @ref sinc_channel_id_t for details.
 *
 * @retval true Selected channel's HPF saturation occurred.
 * @retval false Selected channel's HPF saturation did not occurred.
 */
static inline bool SINC_CheckChannelHPFSaturation(SINC_Type *base, sinc_channel_id_t chId)
{
    return ((base->CHANNEL[(uint8_t)chId].CSR & SINC_CSR_HPFSAT_MASK) == SINC_CSR_HPFSAT_MASK);
}

/*!
 * @brief Check whether Shift saturation occurred.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, refer to @ref sinc_channel_id_t for details.
 *
 * @retval true Selected channel's shift saturation occurred.
 * @retval false Selected channel's shift saturation did not occurred.
 */
static inline bool SINC_CheckChannelShiftSaturation(SINC_Type *base, sinc_channel_id_t chId)
{
    return ((base->CHANNEL[(uint8_t)chId].CSR & SINC_CSR_SFTSAT_MASK) == SINC_CSR_SFTSAT_MASK);
}

/*!
 * @brief Check whether bias saturation occurred.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, refer to @ref sinc_channel_id_t for details.
 *
 * @retval true Selected channel's bias saturation occurred.
 * @retval false Selected channel's bias saturation did not occurred.
 */
static inline bool SINC_CheckChannelBiasSaturation(SINC_Type *base, sinc_channel_id_t chId)
{
    return ((base->CHANNEL[(uint8_t)chId].CSR & SINC_CSR_BIASSAT_MASK) == SINC_CSR_BIASSAT_MASK);
}

/*!
 * @brief Get selected channel's number of conversions.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, refer to @ref sinc_channel_id_t for details.
 * @return uint8_t Selected channel's number of conversions.
 */
uint8_t SINC_GetChannelConversionCount(SINC_Type *base, sinc_channel_id_t chId);

/*!
 * @brief Check whether the selected channel is in conversion.
 *
 * @param base SINC peripheral base address.
 * @param chId The id of sinc channel to check.
 *
 * @retval false Selected channel conversion not in progress.
 * @retval true Selected channel conversion in progress.
 */
static inline bool SINC_CheckChannelConvProgress(SINC_Type *base, sinc_channel_id_t chId)
{
    return ((base->SR & (((uint32_t)SINC_SR_CIP0_MASK) << (uint32_t)chId)) != 0UL);
}

/*!
 * @brief Check whether the selected channel is ready for conversion.
 *
 * @param base SINC peripheral base address.
 * @param chId The id of sinc channel to check.
 *
 * @retval true Selected channel is ready for conversion.
 * @retval false Selected channel is not ready for conversion.
 */
static inline bool SINC_CheckChannelReadyForConv(SINC_Type *base, sinc_channel_id_t chId)
{
    return ((base->SR & (((uint32_t)SINC_SR_CHRDY0_MASK) << (uint32_t)chId)) != 0UL);
}

/*! @} */

/*!
 * @name Channel Protection Low Level Control APIs
 * @{
 */

/*!
 * @brief Set selected channel's low-limit threshold value.
 *
 * @note When the data exceeds the low-limit threshold value, a low-limit event occurs, and the limit threshold format
 * is determines by channel's result data format @ref sinc_result_data_format_t.
 *
 * @note Low limit value must lower than high limit value, otherwise the low-limit threshold does not work.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param lowLimitThreshold Specify the low-limit threshold value, range from 0 to 0xFFFFFFUL.
 */
static inline void SINC_SetChannelLowLimitThreshold(SINC_Type *base, sinc_channel_id_t chId, uint32_t lowLimitThreshold)
{
    base->CHANNEL[(uint8_t)chId].CLOLMT = SINC_CLOLMT_LOLMT(lowLimitThreshold);
}

/*!
 * @brief Set selected channel's high-limit threshold value.
 *
 * @note When the data exceeds the high-limit threshold value, a high-limit event occurs, and the limit threshold format
 * is determines by channel's result data format @ref sinc_result_data_format_t.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param highLimitThreshold Specify the high-limit threshold value, range from 0 to 0xFFFFFFUL.
 */
static inline void SINC_SetChannelHighLimitThreshold(SINC_Type *base,
                                                     sinc_channel_id_t chId,
                                                     uint32_t highLimitThreshold)
{
    base->CHANNEL[(uint8_t)chId].CHILMT = SINC_CHILMT_HILMT(highLimitThreshold);
}

/*!
 * @brief Set selected channel's limit detector mode.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param mode Specify the mode of limit detector, please refer to @ref sinc_limit_detector_mode_t.
 */
static inline void SINC_SetChannelLimitDetectorMode(SINC_Type *base,
                                                    sinc_channel_id_t chId,
                                                    sinc_limit_detector_mode_t mode)
{
    if (mode == kSINC_Lmt_Disabled)
    {
        base->CHANNEL[(uint8_t)chId].CCR &= ~SINC_CCR_LMTEN_MASK;
    }
    else
    {
        base->CHANNEL[(uint8_t)chId].CPROT =
            (base->CHANNEL[(uint8_t)chId].CPROT & ~SINC_CPROT_LMTOP_MASK) | SINC_CPROT_LMTOP((uint32_t)mode & 0x3UL);
        base->CHANNEL[(uint8_t)chId].CCR |= SINC_CCR_LMTEN_MASK;
    }
}

/*!
 * @brief Enable/disable selected channel's high limit break signal.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param enable Used to enable/disable high limit break signal:
 *          - \b true Enable the automatic assertion of the BREAK_HIGH signal when SINC detects a high-limit event on
 *                    the selected channel.
 *          - \b false Disable high limit break signal.
 */
static inline void SINC_EnableChannelHighLimitBreakSignal(SINC_Type *base, sinc_channel_id_t chId, bool enable)
{
    if (enable)
    {
        base->CHANNEL[(uint8_t)chId].CPROT |= SINC_CPROT_HLMTBK_MASK;
    }
    else
    {
        base->CHANNEL[(uint8_t)chId].CPROT &= ~SINC_CPROT_HLMTBK_MASK;
    }
}

/*!
 * @brief Enable/disable selected channel's window limit break signal.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param enable Used to enable/disable window limit break signal:
 *          - \b true Enable the automatic assertion of the BREAK_WIN signal when SINC detects a window-limit event on
 *                    the selected channel.
 *          - \b false Disable window limit break signal.
 */
static inline void SINC_EnableChannelWindowLimitBreakSignal(SINC_Type *base, sinc_channel_id_t chId, bool enable)
{
    if (enable)
    {
        base->CHANNEL[(uint8_t)chId].CPROT |= SINC_CPROT_WLMTBK_MASK;
    }
    else
    {
        base->CHANNEL[(uint8_t)chId].CPROT &= ~SINC_CPROT_WLMTBK_MASK;
    }
}

/*!
 * @brief Enable/disable selected channel's low limit break signal.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param enable  Used to enable/disable low limit break signal:
 *          - \b true Enable the automatic assertion of the BREAK_LOW signal when SINC detects a low-limit event on
 *                    the selected channel.
 *          - \b false Disable low limit break signal.
 */
static inline void SINC_EnableChannelLowLimitBreakSignal(SINC_Type *base, sinc_channel_id_t chId, bool enable)
{
    if (enable)
    {
        base->CHANNEL[(uint8_t)chId].CPROT |= SINC_CPROT_HLMTBK_MASK;
    }
    else
    {
        base->CHANNEL[(uint8_t)chId].CPROT &= ~SINC_CPROT_HLMTBK_MASK;
    }
}

/*!
 * @brief Set selected channel's short-circuit detector operate mode.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param opMode Specify the operate mode to set, please refer to @ref sinc_scd_operate_mode_t.
 */
static inline void SINC_SetChannelScdOperateMode(SINC_Type *base,
                                                 sinc_channel_id_t chId,
                                                 sinc_scd_operate_mode_t opMode)
{
    if (opMode == kSINC_Scd_OperateDisabled)
    {
        base->CHANNEL[(uint8_t)chId].CCR &= ~SINC_CCR_SCDEN_MASK;
    }
    else
    {
        base->CHANNEL[(uint8_t)chId].CPROT =
            ((base->CHANNEL[(uint8_t)chId].CPROT & ~SINC_CPROT_SCDCM_MASK) | SINC_CPROT_SCDCM(opMode));
        base->CHANNEL[(uint8_t)chId].CCR |= SINC_CCR_SCDEN_MASK;
    }
}

/*!
 * @brief Set selected channel's Scd limit threshold.
 *
 * @note The SCD counter tracks the number of received bits with the same repeating value(always 0 or always 1, set by
 * SINC_SetChannelScdOption()), if that
 * number exceeds the scdLimitThreshold, an SCD event occurs on the associated channel.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param u8ScdLimitThreshold Specify the threshold value for the SCD counter, range from 2 to 255.
 */
static inline void SINC_SetChannelScdLimitThreshold(SINC_Type *base,
                                                    sinc_channel_id_t chId,
                                                    uint8_t u8ScdLimitThreshold)
{
    assert(u8ScdLimitThreshold != 0U);
    assert(u8ScdLimitThreshold != 1U);

    base->CHANNEL[(uint8_t)chId].CPROT =
        ((base->CHANNEL[(uint8_t)chId].CPROT) & (~SINC_CPROT_SCDLMT_MASK)) | (SINC_CPROT_SCDLMT(u8ScdLimitThreshold));
}

/*!
 * @brief Set selected channel's SDC option.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param option Specify which repeating bit value increments the SCD counter.
 */
static inline void SINC_SetChannelScdOption(SINC_Type *base, sinc_channel_id_t chId, sinc_scd_option_t option)
{
    base->CHANNEL[(uint8_t)chId].CPROT =
        ((base->CHANNEL[(uint8_t)chId].CPROT) & (~SINC_CPROT_SCDOP_MASK)) | (SINC_CPROT_SCDOP(option));
}

/*!
 * @brief Enable/disable the automatic assertion of the BREAK_SCD signal when SINC detects an SCD event on the selected
 * channel.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param enable Used to enable/disable SCD break signal:
 *          - \b true Enable SCD break signal.
 *          - \b false Disable SCD break signal.
 */
static inline void SINC_EnableChannelScdBreakSignal(SINC_Type *base, sinc_channel_id_t chId, bool enable)
{
    if (enable)
    {
        base->CHANNEL[(uint8_t)chId].CPROT |= SINC_CPROT_SCDBK_MASK;
    }
    else
    {
        base->CHANNEL[(uint8_t)chId].CPROT &= ~SINC_CPROT_SCDBK_MASK;
    }
}

/*!
 * @brief Set the threshold value for the CAD counter.
 *
 * @note The CAD counter tracks the number of clock cycles during which SINC does not detect a clock, if that number
 * exceeds the threshold value, a CAD event occurs on the selected channel.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param cadLimitThreshold Specify the threshold value for the CAD counter, please refer to @ref sinc_cad_threshold_t.
 */
static inline void SINC_SetChannelCadLimitThreshold(SINC_Type *base,
                                                    sinc_channel_id_t chId,
                                                    sinc_cad_threshold_t cadLimitThreshold)
{
    base->CHANNEL[(uint8_t)chId].CPROT =
        ((base->CHANNEL[(uint8_t)chId].CPROT) & (~SINC_CPROT_CADLMT_MASK)) | (SINC_CPROT_CADLMT(cadLimitThreshold));
    if (cadLimitThreshold == kSINC_Cad_Disabled)
    {
        base->CHANNEL[(uint8_t)chId].CCR &= ~SINC_CCR_CADEN_MASK;
    }
    else
    {
        base->CHANNEL[(uint8_t)chId].CCR |= SINC_CCR_CADEN_MASK;
    }
}

/*!
 * @brief Enable/disable the automatic assertion of the BREAK_CAD signal when SINC detects a CAD event on the assoicated
 * channel.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param enable Used to enable/disble CAD break signal:
 *          - \b true Enable selected channel's CAD break signal;
 *          - \b false Disable selected channel's CAD break signal.
 */
static inline void SINC_EnableChannelCadBreakSignal(SINC_Type *base, sinc_channel_id_t chId, bool enable)
{
    if (enable)
    {
        base->CHANNEL[(uint8_t)chId].CPROT |= SINC_CPROT_CADBK_MASK;
    }
    else
    {
        base->CHANNEL[(uint8_t)chId].CPROT &= ~SINC_CPROT_CADBK_MASK;
    }
}

/*!
 * @brief Set selected channel's zero-crossing detector operate mode.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param opMode Specify the operate mode, please refer to @ref sinc_zero_cross_operate_mode_t.
 */
static inline void SINC_SetChannelZcdOperateMode(SINC_Type *base,
                                                 sinc_channel_id_t chId,
                                                 sinc_zero_cross_operate_mode_t opMode)
{
    if (opMode == kSINC_ZCD_Disabled)
    {
        base->CHANNEL[(uint8_t)chId].CCR &= ~SINC_CCR_ZCDEN_MASK;
    }
    else
    {
        base->CHANNEL[(uint8_t)chId].CCFR =
            ((base->CHANNEL[(uint8_t)chId].CCFR) & (~SINC_CCFR_ZCOP_MASK)) | (SINC_CCFR_ZCOP(opMode));
        base->CHANNEL[(uint8_t)chId].CCR |= SINC_CCR_ZCDEN_MASK;
    }
}

/*! @} */

/*!
 * @name Channel Debug Low Level Control APIs
 * @{
 */

#if !((defined(FSL_FEATURE_SINC_CACFR_HAS_NO_PTMUX) && FSL_FEATURE_SINC_CACFR_HAS_NO_PTMUX))
/*!
 * @brief Set selected channel's pulse trigger mux.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param pulseTrigMux Used to selected the signal for pulse-trigger output.
 */
static inline void SINC_SetChannelPulseTriggerMux(SINC_Type *base,
                                                  sinc_channel_id_t chId,
                                                  sinc_pulse_trigger_mux_t pulseTrigMux)
{
    base->CHANNEL[(uint8_t)chId].CACFR =
        ((base->CHANNEL[(uint8_t)chId].CACFR & ~SINC_CACFR_PTMUX_MASK) | SINC_CACFR_PTMUX(pulseTrigMux));
}
#endif /* !(defined(FSL_FEATURE_SINC_CACFR_HAS_NO_PTMUX) && FSL_FEATURE_SINC_CACFR_HAS_NO_PTMUX) */

/*!
 * @brief Set selected channel's debug output.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 * @param debugOutput Used to select debug output, please refer to @ref sinc_debug_output_t.
 */
static inline void SINC_SetChannelDebugOutput(SINC_Type *base, sinc_channel_id_t chId, sinc_debug_output_t debugOutput)
{
    base->CHANNEL[(uint8_t)chId].CCR =
        ((base->CHANNEL[(uint8_t)chId].CCR & ~SINC_CCR_DBGSEL_MASK) | SINC_CCR_DBGSEL(debugOutput));
}

/*!
 * @brief Start selected channel's debug data latch proceduce.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 */
static inline void SINC_LatchChannelDebugProceduce(SINC_Type *base, sinc_channel_id_t chId)
{
    base->CHANNEL[(uint8_t)chId].CSR |= SINC_CSR_SRDS_MASK;
}

/*!
 * @brief Check if the selected channel's debug data is valid.
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 *
 * @retval true Data is valid.
 * @retval false Data is invalid.
 */
static inline bool SINC_CheckChannelDebugDataValid(SINC_Type *base, sinc_channel_id_t chId)
{
    return ((base->CHANNEL[(uint8_t)chId].CSR & (SINC_CSR_SRDS_MASK | SINC_CSR_DBGRS_MASK)) == 0UL);
}

/*!
 * @brief Return selected channel's the debug data that requested by SINC_SetChannelDebugOutput().
 *
 * @param base SINC peripheral base address.
 * @param chId Selected channel id, please refer to @ref sinc_channel_id_t.
 *
 * @return Selected channel's debug data.
 */
static inline uint32_t SINC_GetChannelDebugData(SINC_Type *base, sinc_channel_id_t chId)
{
    return base->CHANNEL[(uint8_t)chId].CDBGR;
}

/*! @} */

/*!
 * @name Interrupt Control APIs
 * @{
 */

/*!
 * @brief Enable the mask of interrupts, such as channel data ready interrupt, channel limit detect interrupt and so on.
 *
 * @param base SINC peripheral base address.
 * @param interruptMasks Mask of interrupts to enable, should be the OR'ed value of @ref sinc_interrupt_enable_t.
 */
static inline void SINC_EnableInterrupts(SINC_Type *base, uint64_t interruptMasks)
{
    uint32_t normalIntMask;
    uint32_t errorIntMask;
    uint32_t fifoCadIntMask;

    /*
     * #define SINC_DECODE_INTERRUPT(interruptMask)    \
     *      normalIntMask = ((uint32_t)(interruptMask) & (0xFFFFFUL));  \
     *      errorIntMask = ((uint32_t)((interruptMask) >> 20ULL) & (0xFFFFFUL));  \
     *      fifoCadIntMask = ((uint32_t)((interruptMask) >> 40ULL) & (0xFFFFFUL))
     */
    SINC_DECODE_INTERRUPT(interruptMasks);

    base->NIE |= SINC_FIND_INT_FIELD_VALUE(normalIntMask, SINC_NORMAL_INT_NAME_COCIE) |
                 SINC_FIND_INT_FIELD_VALUE(normalIntMask, SINC_NORMAL_INT_NAME_CHFIE) |
                 SINC_FIND_INT_FIELD_VALUE(normalIntMask, SINC_NORMAL_INT_NAME_ZCDIE);

    base->EIE |= SINC_FIND_INT_FIELD_VALUE(errorIntMask, SINC_ERROR_INT_NAME_SCDIE) |
                 SINC_FIND_INT_FIELD_VALUE(errorIntMask, SINC_ERROR_INT_NAME_WLMTIE) |
                 SINC_FIND_INT_FIELD_VALUE(errorIntMask, SINC_ERROR_INT_NAME_LLMTIE) |
                 SINC_FIND_INT_FIELD_VALUE(errorIntMask, SINC_ERROR_INT_NAME_HLMTIE);

    base->FIFOIE |= SINC_FIND_INT_FIELD_VALUE(fifoCadIntMask, SINC_FIFO_CAD_INT_FUNFIE) |
                    SINC_FIND_INT_FIELD_VALUE(fifoCadIntMask, SINC_FIFO_CAD_INT_FOVFIE) |
                    SINC_FIND_INT_FIELD_VALUE(fifoCadIntMask, SINC_FIFO_CAD_INT_CADIE) |
                    SINC_FIND_INT_FIELD_VALUE(fifoCadIntMask, SINC_FIFO_CAD_INT_SATIE);
}

/*!
 * @brief Enable the mask of interrupts, such as channel data ready interrupt, channel limit detect interrupt and so on.
 *
 * @param base SINC peripheral base address.
 * @param interruptMasks Mask of interrupts to disable, should be the OR'ed value of @ref sinc_interrupt_enable_t.
 */
static inline void SINC_DisableInterrupts(SINC_Type *base, uint64_t interruptMasks)
{
    uint32_t normalIntMask;
    uint32_t errorIntMask;
    uint32_t fifoCadIntMask;

    /*
     * #define SINC_DECODE_INTERRUPT(interruptMask)    \
     *      normalIntMask = ((uint32_t)(interruptMask) & (0xFFFFFUL));  \
     *      errorIntMask = ((uint32_t)((interruptMask) >> 20ULL) & (0xFFFFFUL));  \
     *      fifoCadIntMask = ((uint32_t)((interruptMask) >> 40ULL) & (0xFFFFFUL))
     */
    SINC_DECODE_INTERRUPT(interruptMasks);

    base->NIE &= ~(SINC_FIND_INT_FIELD_VALUE(normalIntMask, SINC_NORMAL_INT_NAME_COCIE) |
                   SINC_FIND_INT_FIELD_VALUE(normalIntMask, SINC_NORMAL_INT_NAME_CHFIE) |
                   SINC_FIND_INT_FIELD_VALUE(normalIntMask, SINC_NORMAL_INT_NAME_ZCDIE));

    base->EIE &= ~(SINC_FIND_INT_FIELD_VALUE(errorIntMask, SINC_ERROR_INT_NAME_SCDIE) |
                   SINC_FIND_INT_FIELD_VALUE(errorIntMask, SINC_ERROR_INT_NAME_WLMTIE) |
                   SINC_FIND_INT_FIELD_VALUE(errorIntMask, SINC_ERROR_INT_NAME_LLMTIE) |
                   SINC_FIND_INT_FIELD_VALUE(errorIntMask, SINC_ERROR_INT_NAME_HLMTIE));

    base->FIFOIE &= ~(SINC_FIND_INT_FIELD_VALUE(fifoCadIntMask, SINC_FIFO_CAD_INT_FUNFIE) |
                      SINC_FIND_INT_FIELD_VALUE(fifoCadIntMask, SINC_FIFO_CAD_INT_FOVFIE) |
                      SINC_FIND_INT_FIELD_VALUE(fifoCadIntMask, SINC_FIFO_CAD_INT_CADIE) |
                      SINC_FIND_INT_FIELD_VALUE(fifoCadIntMask, SINC_FIFO_CAD_INT_SATIE));
}

/*!
 * @brief Get interrupt status flags.
 *
 * @param base SINC peripheral base address.
 *
 * @return SINC module's interrupt status flags, the OR'ed value of @ref sinc_interrupt_status_t.
 */
static inline uint64_t SINC_GetInterruptStatus(SINC_Type *base)
{
    uint64_t allIntStatusValue     = 0ULL;
    uint32_t normalIntStatusValue  = base->NIS;
    uint32_t errorIntStatusValue   = base->EIS;
    uint32_t fifoCadIntStatusValue = base->FIFOIS;

    allIntStatusValue |= ((uint64_t)SINC_FIND_STATUS_FIELD_VALUE(normalIntStatusValue, SINC_NORMAL_INT_NAME_COCIE) |
                          (uint64_t)SINC_FIND_STATUS_FIELD_VALUE(normalIntStatusValue, SINC_NORMAL_INT_NAME_CHFIE) |
                          (uint64_t)SINC_FIND_STATUS_FIELD_VALUE(normalIntStatusValue, SINC_NORMAL_INT_NAME_ZCDIE));

    allIntStatusValue |= (((uint64_t)SINC_FIND_STATUS_FIELD_VALUE(errorIntStatusValue, SINC_ERROR_INT_NAME_SCDIE) |
                           (uint64_t)SINC_FIND_STATUS_FIELD_VALUE(errorIntStatusValue, SINC_ERROR_INT_NAME_WLMTIE) |
                           (uint64_t)SINC_FIND_STATUS_FIELD_VALUE(errorIntStatusValue, SINC_ERROR_INT_NAME_LLMTIE) |
                           (uint64_t)SINC_FIND_STATUS_FIELD_VALUE(errorIntStatusValue, SINC_ERROR_INT_NAME_HLMTIE))
                          << 20ULL);

    allIntStatusValue |= (((uint64_t)SINC_FIND_STATUS_FIELD_VALUE(fifoCadIntStatusValue, SINC_FIFO_CAD_INT_FUNFIE) |
                           (uint64_t)SINC_FIND_STATUS_FIELD_VALUE(fifoCadIntStatusValue, SINC_FIFO_CAD_INT_FOVFIE) |
                           (uint64_t)SINC_FIND_STATUS_FIELD_VALUE(fifoCadIntStatusValue, SINC_FIFO_CAD_INT_CADIE) |
                           (uint64_t)SINC_FIND_STATUS_FIELD_VALUE(fifoCadIntStatusValue, SINC_FIFO_CAD_INT_SATIE))
                          << 40ULL);

    return (uint64_t)allIntStatusValue;
}

/*!
 * @brief Clear selected mask of interrupt status flags.
 *
 * @param base SINC peripheral base address.
 * @param statusMasks The mask of interrupt status flags to clear, should be the OR'ed
 *                    value of @ref sinc_interrupt_status_t.
 */
static inline void SINC_ClearInterruptStatus(SINC_Type *base, uint64_t statusMasks)
{
    uint32_t normalIntMask;
    uint32_t errorIntMask;
    uint32_t fifoCadIntMask;

    /*
     * #define SINC_DECODE_INTERRUPT(interruptMask)    \
     *      normalIntMask = ((uint32_t)(interruptMask) & (0xFFFFFUL));  \
     *      errorIntMask = ((uint32_t)((interruptMask) >> 20ULL) & (0xFFFFFUL));  \
     *      fifoCadIntMask = ((uint32_t)((interruptMask) >> 40ULL) & (0xFFFFFUL))
     */
    SINC_DECODE_INTERRUPT(statusMasks);

    base->EIS = (SINC_FIND_INT_FIELD_VALUE(errorIntMask, SINC_ERROR_INT_NAME_SCDIE) |
                 SINC_FIND_INT_FIELD_VALUE(errorIntMask, SINC_ERROR_INT_NAME_WLMTIE) |
                 SINC_FIND_INT_FIELD_VALUE(errorIntMask, SINC_ERROR_INT_NAME_LLMTIE) |
                 SINC_FIND_INT_FIELD_VALUE(errorIntMask, SINC_ERROR_INT_NAME_HLMTIE));

    base->FIFOIS = (SINC_FIND_INT_FIELD_VALUE(fifoCadIntMask, SINC_FIFO_CAD_INT_FUNFIE) |
                    SINC_FIND_INT_FIELD_VALUE(fifoCadIntMask, SINC_FIFO_CAD_INT_FOVFIE) |
                    SINC_FIND_INT_FIELD_VALUE(fifoCadIntMask, SINC_FIFO_CAD_INT_CADIE) |
                    SINC_FIND_INT_FIELD_VALUE(fifoCadIntMask, SINC_FIFO_CAD_INT_SATIE));

    base->NIS = (SINC_FIND_INT_FIELD_VALUE(normalIntMask, SINC_NORMAL_INT_NAME_COCIE) |
                 SINC_FIND_INT_FIELD_VALUE(normalIntMask, SINC_NORMAL_INT_NAME_CHFIE) |
                 SINC_FIND_INT_FIELD_VALUE(normalIntMask, SINC_NORMAL_INT_NAME_ZCDIE));
}

/*! @} */

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* FSL_SINC_H__ */
