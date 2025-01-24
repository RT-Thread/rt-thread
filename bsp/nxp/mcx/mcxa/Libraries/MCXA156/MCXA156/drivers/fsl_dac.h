/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020, 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_DAC_H_
#define FSL_DAC_H_

#include "fsl_common.h"

/*!
 * @addtogroup dac
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief DAC driver version 2.1.2. */
#define FSL_DAC_DRIVER_VERSION (MAKE_VERSION(2, 1, 2))
/*! @} */

/*!
 * @brief DAC reset control.
 */
enum
{
    kDAC_ResetFIFO  = LPDAC_RCR_FIFORST_MASK, /*!< Resets the FIFO pointers and flags. */
    kDAC_ResetLogic = LPDAC_RCR_SWRST_MASK,   /*!< Resets all DAC registers and internal logic. */
};

/*!
 * @brief DAC interrupts.
 */
enum
{
    kDAC_FIFOFullInterruptEnable      = LPDAC_IER_FULL_IE_MASK,  /*!< FIFO full interrupt enable. */
    kDAC_FIFOEmptyInterruptEnable     = LPDAC_IER_EMPTY_IE_MASK, /*!< FIFO empty interrupt enable. */
    kDAC_FIFOWatermarkInterruptEnable = LPDAC_IER_WM_IE_MASK,    /*!< FIFO watermark interrupt enable. */
    kDAC_SwingBackInterruptEnable     = LPDAC_IER_SWBK_IE_MASK,  /*!< Swing back one cycle complete interrupt enable. */
    kDAC_FIFOOverflowInterruptEnable  = LPDAC_IER_OF_IE_MASK,    /*!< FIFO overflow interrupt enable. */
    kDAC_FIFOUnderflowInterruptEnable = LPDAC_IER_UF_IE_MASK,    /*!< FIFO underflow interrupt enable. */
#if defined(FSL_FEATURE_LPDAC_HAS_PERIODIC_TRIGGER_MODE) && FSL_FEATURE_LPDAC_HAS_PERIODIC_TRIGGER_MODE
    kDAC_PeriodTriggerCompleteInterruptEnable =
        LPDAC_IER_PTGCOCO_IE_MASK, /*!< Period trigger mode conversion complete interrupt enable */
#endif                             /* FSL_FEATURE_LPDAC_HAS_PERIODIC_TRIGGER_MODE */
};

/*!
 * @brief DAC DMA switchers.
 */
enum
{
    kDAC_FIFOEmptyDMAEnable     = LPDAC_DER_EMPTY_DMAEN_MASK, /*!< FIFO empty DMA enable. */
    kDAC_FIFOWatermarkDMAEnable = LPDAC_DER_WM_DMAEN_MASK,    /*!< FIFO watermark DMA enable. */
};

/*!
 * @brief DAC status flags.
 */
enum
{
    kDAC_FIFOUnderflowFlag = LPDAC_FSR_UF_MASK, /*!< This flag means that there is a new trigger after the buffer is
empty. The FIFO read pointer will not
increase in this case and the data sent to DAC analog conversion will not changed. This flag is cleared by writing a 1
to it. */

    kDAC_FIFOOverflowFlag =
        LPDAC_FSR_OF_MASK, /*!< This flag indicates that data is intended to write into FIFO after the
buffer is full. The writer pointer will
not increase in this case. The extra data will not be written into the FIFO. This flag is cleared by writing a 1 to it.
*/

    kDAC_FIFOSwingBackFlag = LPDAC_FSR_SWBK_MASK, /*!< This flag indicates that the DAC has completed one period of
conversion in swing back mode. It means
that the read pointer has increased to the top (write pointer) once and then decreased to zero once. For
example, after three data is written to FIFO, the writer pointer is now 3. Then, if continually triggered, the
read pointer will swing like: 0-1-2-1-0-1-2-, and so on. After the fourth trigger, the flag is set. This flag is
cleared by writing a 1 to it. */

    kDAC_FIFOWatermarkFlag = LPDAC_FSR_WM_MASK, /*!< This field is set if the remaining data in FIFO is less than or
                     equal to the setting value of wartermark. By writing data into FIFO by DMA or CPU, this flag is
                     cleared automatically when the data in FIFO is more than the setting value of watermark. */

    kDAC_FIFOEmptyFlag = LPDAC_FSR_EMPTY_MASK, /*!< FIFO empty flag. */
    kDAC_FIFOFullFlag  = LPDAC_FSR_FULL_MASK,  /*!< FIFO full flag. */
#if defined(FSL_FEATURE_LPDAC_HAS_PERIODIC_TRIGGER_MODE) && FSL_FEATURE_LPDAC_HAS_PERIODIC_TRIGGER_MODE
    kDAC_PeriodTriggerCompleteFlag = LPDAC_FSR_PTGCOCO_MASK, /*!< Period trigger mode conversion complete flag. */
#endif                                                       /* FSL_FEATURE_LPDAC_HAS_PERIODIC_TRIGGER_MODE */
};

/*!
 * @brief DAC FIFO trigger mode.
 */
typedef enum _dac_fifo_trigger_mode
{
    kDAC_FIFOTriggerByHardwareMode = 0U, /*!< Buffer would be triggered by hardware. */
    kDAC_FIFOTriggerBySoftwareMode = 1U, /*!< Buffer would be triggered by software. */
} dac_fifo_trigger_mode_t;

/*!
 * @brief DAC FIFO work mode.
 */
typedef enum _dac_fifo_work_mode
{
    kDAC_FIFODisabled = 0U, /*!< FIFO mode is disabled and buffer mode is enabled. Any data written to DATA[DATA] goes
                                 to buffer then goes to conversion. */
    kDAC_FIFOWorkAsNormalMode = 1U, /*!< FIFO mode is enabled. Data will be first read from FIFO to buffer then goes to
                                         conversion. */
    kDAC_FIFOWorkAsSwingMode = 2U, /*!< In swing mode, the read pointer swings between the writer pointer and zero. That
                                        is, the trigger increases the read pointer till reach the writer pointer and
                                        decreases the read pointer till zero, and so on. The FIFO empty/full/watermark
                                        flag will not update during swing back mode. */
#if defined(FSL_FEATURE_LPDAC_HAS_PERIODIC_TRIGGER_MODE) && FSL_FEATURE_LPDAC_HAS_PERIODIC_TRIGGER_MODE
    kDAC_FIFOWorkAsPeriodTriggerMode =
        3U, /*!< In periodic trigger mode, user only needs to send the first trigger. Then after every [PTG_PERIOD+1]
               RCLK cycles, DAC will be automatically triggered by internal trigger. There will be [PTG_NUM] internal
               triggers, thus in total [PTG_NUM+1] conversions including the first trigger sent by user. User can
               terminate the current conversion queue by clearing the GCR[PTGEN] bit. Then, after the current conversion
               is completed, the conversion is terminated and the PTGCOCO flag is set. If PCR[PTG_NUM] is set to zero,
               there will be infinite triggers following the first hardware/software trigger, until the GCR[PTGEN] is
               cleared by software. In any case, the conversion can be terminated by FIFORST/SWRST. */
    kDAC_FIFOWorkAsPeriodTriggerAndSwingMode = 4U, /*!< Periodically trigger DAC and swing back. */
#endif                                             /* FSL_FEATURE_LPDAC_HAS_PERIODIC_TRIGGER_MODE */
} dac_fifo_work_mode_t;

/*!
 * @brief DAC reference voltage source.
 */
typedef enum _dac_reference_voltage_source
{
#if defined(FSL_FEATURE_ANALOG_NUM_OF_VREF_SRC) && (FSL_FEATURE_ANALOG_NUM_OF_VREF_SRC == 3)
    kDAC_ReferenceVoltageSourceAlt1 = 0U, /*!< The DAC selects VDD_ANA as the reference voltage. */
    kDAC_ReferenceVoltageSourceAlt2 = 1U, /*!< The DAC selects VREF_OUT as the reference voltage. */
    kDAC_ReferenceVoltageSourceAlt3 = 2U, /*!< THe DAC selects VREFH as the reference voltage. */
#else
    kDAC_ReferenceVoltageSourceAlt1 = 0U, /*!< The DAC selects VREFH_INT as the reference voltage. */
    kDAC_ReferenceVoltageSourceAlt2 = 1U, /*!< The DAC selects VREFH_EXT as the reference voltage. */
#endif /* FSL_FEATURE_ANALOG_NUM_OF_VREF_SRC  */
} dac_reference_voltage_source_t;

#if defined(FSL_FEATURE_LPDAC_HAS_INTERNAL_REFERENCE_CURRENT) && FSL_FEATURE_LPDAC_HAS_INTERNAL_REFERENCE_CURRENT
/*
 * @brief DAC internal reference current source
 */
typedef enum _dac_reference_current_source
{
    kDAC_ReferenceCurrentSourcePtat = LPDAC_GCR_IREF_PTAT_EXT_SEL_MASK, /* Internal PTAT Current Reference selected */
    kDAC_ReferenceCurrentSourceZtc  = LPDAC_GCR_IREF_ZTC_EXT_SEL_MASK,  /* Internal ZTC Current Reference selected */
} dac_reference_current_source_t;
#endif /* FSL_FEATURE_LPDAC_HAS_INTERNAL_REFERENCE_CURRENT */

/*!
 * @brief DAC configuration structure.
 */
typedef struct _dac_config
{
    uint32_t fifoWatermarkLevel;             /*!< FIFO's watermark, the max value can be the hardware FIFO size. */
    dac_fifo_trigger_mode_t fifoTriggerMode; /*!< Select the trigger mode for FIFO. */
    dac_fifo_work_mode_t fifoWorkMode;       /*!< Select the work mode for FIFO. */
#if defined(FSL_FEATURE_LPDAC_HAS_GCR_BUF_EN) && FSL_FEATURE_LPDAC_HAS_GCR_BUF_EN
    bool enableOpampBuffer; /*!< Opamp is used as buffer. */
#endif                      /* FSL_FEATURE_LPDAC_HAS_GCR_BUF_EN */
#if defined(FSL_FEATURE_LPDAC_HAS_GCR_RCV_TRG) && FSL_FEATURE_LPDAC_HAS_GCR_RCV_TRG
    bool enableExternalTriggerSource; /* DAC uses another DAC's hardware/software trigger as its trigger source. */
#endif                                /* FSL_FEATURE_LPDAC_HAS_GCR_RCV_TRG */
#if defined(FSL_FEATURE_LPDAC_HAS_GCR_BUF_SPD_CTRL) && FSL_FEATURE_LPDAC_HAS_GCR_BUF_SPD_CTRL
    bool enableLowerLowPowerMode; /*!< Enable the lower low power mode. */
#else
    bool enableLowPowerMode;              /*!< Enable the low power mode. */
#endif /* FSL_FEATURE_LPDAC_HAS_GCR_BUF_SPD_CTRL */
#if defined(FSL_FEATURE_LPDAC_HAS_PERIODIC_TRIGGER_MODE) && FSL_FEATURE_LPDAC_HAS_PERIODIC_TRIGGER_MODE
    uint32_t periodicTriggerNumber; /*!< There will be 'periodicTriggerNumber' internal triggers following the first
                                      hardware/software trigger. So there will be 'periodicTriggerNumber + 1'
                                      conversions in total. If set to zero, there will be infinite triggers following
                                      the first hw/sw trigger, until the GCR[PTGEN] is cleared. */
    uint32_t periodicTriggerWidth; /*!< Control the periodic trigger frequency. There will be 'periodicTriggerWidth + 1'
                                      RCLK cycles between each periodic trigger. The periodic trigger frequency should
                                      be configured to not larger than the analog conversion speed. */
#endif                             /* FSL_FEATURE_LPDAC_HAS_PERIODIC_TRIGGER_MODE */
#if defined(FSL_FEATURE_LPDAC_HAS_GCR_LATCH_CYC) && FSL_FEATURE_LPDAC_HAS_GCR_LATCH_CYC
    uint32_t syncTime; /*!< RCLK cycles before data latch. accessible range is 0-15. It is used to configure the DAC
                          sync cycles which is helpful to reduce glitch on the output. The sync time is (LATCH_CYC+1)
                          RCLK cycles. User should configure this register according to the RCLK frequency. The
                          recommended sync time is at least 40ns.*/
#endif                 /* FSL_FEATURE_LPDAC_HAS_GCR_LATCH_CYC */
#if defined(FSL_FEATURE_LPDAC_HAS_INTERNAL_REFERENCE_CURRENT) && FSL_FEATURE_LPDAC_HAS_INTERNAL_REFERENCE_CURRENT
    dac_reference_current_source_t referenceCurrentSource; /*!< Select the internal reference current source. */
#endif                                                     /* FSL_FEATURE_LPDAC_HAS_INTERNAL_REFERENCE_CURRENT */
    dac_reference_voltage_source_t referenceVoltageSource; /*!< Select the reference voltage source. */
} dac_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and de-initialization
 * @{
 */

/*!
 * @brief Initialize the DAC module with common configuartion.
 *
 * The clock will be enabled in this function.
 *
 * @param base DAC peripheral base address.
 * @param config Pointer to configuration structure.
 */
void DAC_Init(LPDAC_Type *base, const dac_config_t *config);

/*!
 * @brief Get the default settings for initialization's configuration.
 *
 * This function initializes the user configuration structure to a default value. The default values are:
 * @code
 *   config->fifoWatermarkLevel = 0U;
 *   config->fifoTriggerMode = kDAC_FIFOTriggerByHardwareMode;
 *   config->fifoWorkMode = kDAC_FIFODisabled;
 *   config->enableLowPowerMode = false;
 *   config->referenceVoltageSource = kDAC_ReferenceVoltageSourceAlt1;
 * @endcode
 *
 * @param config Pointer to configuration structure.
 */
void DAC_GetDefaultConfig(dac_config_t *config);

/*!
 * @brief De-initialize the DAC module.
 *
 * The clock will be disabled in this function.
 *
 * @param base DAC peripheral base address.
 */
void DAC_Deinit(LPDAC_Type *base);

/*!
 * @brief Assert the reset control to part hardware.
 *
 * This function is to assert the reset control to part hardware. Responding part hardware would remain reset untill
 * cleared by software.
 *
 * @param base DAC peripheral base address.
 * @param mask The reset control mask, see to _dac_reset_control_t.
 */
static inline void DAC_SetReset(LPDAC_Type *base, uint32_t mask)
{
    base->RCR |= mask;
}

/*!
 * @brief Clear the reset control to part hardware.
 *
 * This function is to clear the reset control to part hardware. Responding part hardware would work after the reset
 * control is cleared by software.
 *
 * @param base DAC peripheral base address.
 * @param mask The reset control mask, see to _dac_reset_control_t.
 */
static inline void DAC_ClearReset(LPDAC_Type *base, uint32_t mask)
{
    base->RCR &= ~mask;
}

/*!
 * @brief Enable the DAC hardware system or not.
 *
 * This function is to start the Programmable Reference Generator operation or not.
 *
 * @param base DAC peripheral base address.
 * @param enable Assertion of indicated event.
 */
static inline void DAC_Enable(LPDAC_Type *base, bool enable)
{
    if (enable)
    {
        base->GCR |= LPDAC_GCR_DACEN_MASK;
    }
    else
    {
        base->GCR &= ~LPDAC_GCR_DACEN_MASK;
    }
}

/*! @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enable the interrupts.
 *
 * @param base DAC peripheral base address.
 * @param mask Mask value of indicated interrupt events. See to _dac_interrupt_enable.
 */
static inline void DAC_EnableInterrupts(LPDAC_Type *base, uint32_t mask)
{
    base->IER |= mask;
}

/*!
 * @brief Disable the interrupts.
 *
 * @param base DAC peripheral base address.
 * @param mask Mask value of indicated interrupt events. See to _dac_interrupt_enable.
 */
static inline void DAC_DisableInterrupts(LPDAC_Type *base, uint32_t mask)
{
    base->IER &= ~mask;
}

/*! @} */

/*!
 * @name DMA control
 * @{
 */

/*!
 * @brief Enable the DMA switchers or not.
 *
 * @param base DAC peripheral base address.
 * @param mask Mask value of indicated DMA requeset. See to _dac_dma_enable.
 * @param enable Enable the DMA or not.
 */
static inline void DAC_EnableDMA(LPDAC_Type *base, uint32_t mask, bool enable)
{
    if (enable)
    {
        base->DER |= mask;
    }
    else
    {
        base->DER &= ~mask;
    }
}

/*! @} */

/*!
 * @name Status flags
 * @{
 */

/*!
 * @brief Get status flags of DAC module.
 *
 * @param base DAC peripheral base address.
 * @return Mask value of status flags. See to _dac_status_flags.
 */
static inline uint32_t DAC_GetStatusFlags(LPDAC_Type *base)
{
    return base->FSR;
}

/*!
 * @brief Clear status flags of DAC module.
 *
 * @param base DAC peripheral base address.
 * @param flags Mask value of status flags to be cleared. See to _dac_status_flags.
 */
static inline void DAC_ClearStatusFlags(LPDAC_Type *base, uint32_t flags)
{
    base->FSR = flags;
}

/*! @} */

/*!
 * @name Functional feature
 * @{
 */

/*!
 * @brief Set data into the entry of FIFO buffer.
 *
 * @param base DAC peripheral base address.
 * @param value Setting value into FIFO buffer.
 */
static inline void DAC_SetData(LPDAC_Type *base, uint32_t value)
{
    base->DATA = LPDAC_DATA_DATA(value);
}

/*!
 * @brief Get the value of the FIFO write pointer.
 *
 * @param base DAC peripheral base address.
 * @return Current value of the FIFO write pointer.
 */

static inline uint32_t DAC_GetFIFOWritePointer(LPDAC_Type *base)
{
    return (LPDAC_FPR_FIFO_WPT_MASK & base->FPR) >> LPDAC_FPR_FIFO_WPT_SHIFT;
}

/*!
 * @brief  Get the value of the FIFO read pointer.
 *
 * @param base DAC peripheral base address.
 * @return Current value of the FIFO read pointer.
 */

static inline uint32_t DAC_GetFIFOReadPointer(LPDAC_Type *base)
{
    return (LPDAC_FPR_FIFO_RPT_MASK & base->FPR) >> LPDAC_FPR_FIFO_RPT_SHIFT;
}

/*!
 * @brief Do software trigger to FIFO when in software mode.
 *
 * @param base DAC peripheral base address.
 */

static inline void DAC_DoSoftwareTriggerFIFO(LPDAC_Type *base)
{
    base->TCR = LPDAC_TCR_SWTRG_MASK;
}

/*! @} */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* FSL_DAC12_H_ */
