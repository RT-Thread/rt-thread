/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_DAC14_H_
#define FSL_DAC14_H_

#include "fsl_common.h"

/*!
 * @addtogroup dac14
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief DAC14 driver version 2.0.0. */
#define FSL_DAC14_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*! @} */

/*!
 * @brief DAC14 interrupts enumeration.
 */
enum _dac14_interrupt_enable
{
    kDAC14_PeriodTriggerCompleteInterruptEnable = HPDAC_IER_PTGCOCO_IE_MASK, /*!< Period trigger mode conversion complete interrupt enable */
    kDAC14_FIFOUnderflowInterruptEnable = HPDAC_IER_UF_IE_MASK,    /*!< FIFO underflow interrupt enable. */
    kDAC14_FIFOOverflowInterruptEnable  = HPDAC_IER_OF_IE_MASK,    /*!< FIFO overflow interrupt enable. */
    kDAC14_SwingBackInterruptEnable     = HPDAC_IER_SWBK_IE_MASK,  /*!< Swing back one cycle complete interrupt enable. */
    kDAC14_FIFOWatermarkInterruptEnable = HPDAC_IER_WM_IE_MASK,    /*!< FIFO watermark interrupt enable. */
    kDAC14_FIFOEmptyInterruptEnable     = HPDAC_IER_EMPTY_IE_MASK, /*!< FIFO empty interrupt enable. */
    kDAC14_FIFOFullInterruptEnable      = HPDAC_IER_FULL_IE_MASK,  /*!< FIFO full interrupt enable. */
};

/*!
 * @brief DAC14 DMA switchers.
 */
enum _dac14_dma_enable
{
    kDAC14_FIFOWatermarkDMAEnable = HPDAC_DER_WM_DMAEN_MASK,    /*!< FIFO watermark DMA enable. */
    kDAC14_FIFOEmptyDMAEnable     = HPDAC_DER_EMPTY_DMAEN_MASK, /*!< FIFO empty DMA enable. */
};

/*!
 * @brief DAC14 status flags.
 */
enum _dac14_status_flags
{
    kDAC14_PeriodTriggerCompleteFlag = HPDAC_FSR_PTGCOCO_MASK, /*!< Period trigger mode conversion complete flag. */
    kDAC14_FIFOUnderflowFlag = HPDAC_FSR_UF_MASK, /*!< This flag means that there is a new trigger after the buffer is empty. The FIFO read pointer will not increase in this case and the data sent to DAC analog conversion will not changed. This flag is cleared by writing a 1
                                                 to it. */
    kDAC14_FIFOOverflowFlag = HPDAC_FSR_OF_MASK, /*!< This flag indicates that data is intended to write into FIFO after the buffer is full. The writer pointer will
                                                not increase in this case. The extra data will not be written into the FIFO. This flag is cleared by writing a 1 to it.
                                                */
    kDAC14_SwingBackCompleteFlag = HPDAC_FSR_SWBK_MASK, /*!< This flag indicates that the DAC has completed one period of conversion in swing back mode. It means that the read pointer has increased to the top (write pointer) once and then decreased to zero once. For
                                                    example, after three data is written to FIFO, the writer pointer is now 3. Then, if continually triggered, the
                                                    read pointer will swing like: 0-1-2-1-0-1-2-, and so on. After the fourth trigger, the flag is set. This flag is
                                                    cleared by writing a 1 to it. */
    kDAC14_FIFOWaterMarkFlag = HPDAC_FSR_WM_MASK, /*!< This field is set if the remaining data in FIFO is less than or
                                                     equal to the setting value of wartermark. By writing data into FIFO by DMA or CPU, this flag is
                                                     cleared automatically when the data in FIFO is more than the setting value of watermark. */
    kDAC14_FIFOEmptyFlag = HPDAC_FSR_EMPTY_MASK, /*!< FIFO empty flag, when CPU or DMA writes data to FIFO, this bit will automatically clear.*/
    kDAC14_FIFOFullFlag  = HPDAC_FSR_FULL_MASK,  /*!< FIFO full flag, when software trigger and hardware trigger read FIFO automatically clears this flag.*/
};

/*!
 * @brief DAC14 trigger source, include software and hardware.
 */
typedef enum _dac14_trigger_source
{
    kDAC14_HardwareTriggerSource = 0U, /*!< Trigger source selection hardware . */
    kDAC14_SoftwareTriggerSource = 1U, /*!< Trigger source selection software . */
} dac14_trigger_source_t;

/*!
 * @brief DAC14 work mode.
 */
typedef enum _dac14_work_mode
{
    kDAC14_BufferWorkMode = 0U, /*!< FIFO mode is disabled and buffer mode is enabled. Any data written to DATA[DATA] goes
                                 to buffer then goes to conversion. */
    kDAC14_FIFOWorkMode = 1U, /*!< FIFO mode is enabled. Data will be first read from FIFO to buffer then goes to
                                         conversion. */
    kDAC14_SwingBackWorkMode = 2U, /*!< In swing mode, the read pointer swings between the writer pointer and zero. That
                                        is, the trigger increases the read pointer till reach the writer pointer and
                                        decreases the read pointer till zero, and so on. The FIFO empty/full/watermark
                                        flag will not update during swing back mode. */
    kDAC14_PeriodTriggerWorkMode = 3U, /*!< In periodic trigger mode, user only needs to send the first trigger. Then after every [PTG_PERIOD+1]
                                        RCLK cycles, DAC will be automatically triggered by internal trigger. There will be [PTG_NUM] internal
                                        triggers, thus in total [PTG_NUM+1] conversions including the first trigger sent by user. User can
                                        terminate the current conversion queue by clearing the GCR[PTGEN] bit. Then, after the current conversion
                                        is completed, the conversion is terminated and the PTGCOCO flag is set. If PCR[PTG_NUM] is set to zero,
                                        there will be infinite triggers following the first hardware/software trigger, until the GCR[PTGEN] is
                                        cleared by software. In any case, the conversion can be terminated by FIFORST/SWRST. */
    kDAC14_PeriodTriggerAndSwingBackWorkMode = 4U, /*!< Periodically trigger DAC and swing back. */
} dac14_work_mode_t;

/*!
 * @brief DAC14 configuration structure.
 */
typedef struct _dac14_config
{
    uint16_t periodicTriggerNumber; /*!< There will be 'periodicTriggerNumber' internal triggers following the first
                                    hardware/software trigger. So there will be 'periodicTriggerNumber + 1'
                                    conversions in total. If set to zero, there will be infinite triggers following
                                    the first hw/sw trigger, until the GCR[PTGEN] is cleared. */
    uint16_t periodicTriggerWidth; /*!< Control the periodic trigger frequency. There will be 'periodicTriggerWidth + 1'
                                    RCLK cycles between each periodic trigger. The periodic trigger frequency should
                                    be configured to not larger than the analog conversion speed. */
    uint8_t fifoWatermarkLevel :5;     /*!< FIFO's watermark, the max value can be the hardware FIFO size. */
    bool enableOpampBuffer :1;         /*!< Opamp is used as buffer.*/
    bool enableDAC :1;                 /*!< Enable the DAC system.*/
    dac14_work_mode_t WorkMode;       /*!< Select DAC work mode.*/
    dac14_trigger_source_t TriggerSource; /*!< Select DAC trigger source. */
} dac14_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization And De-initialization
 * @{
 */

/*!
 * @brief Initialize the DAC14 module with common configuartion.
 *
 * The clock will be enabled in this function.
 *
 * @param base DAC14 peripheral base address.
 * @param config Pointer to configuration structure.
 */
void DAC14_Init(HPDAC_Type *base, const dac14_config_t *config);

/*!
 * @brief Get the default settings for initialization's configuration.
 *
 * This function initializes the user configuration structure to a default value. The default values are:
 * @code
    config->fifoWatermarkLevel = 0U;
    config->TriggerSource    = kDAC14_HardwareTriggerSource;
    config->WorkMode       = kDAC14_BufferWorkMode;
    config->enableOpampBuffer  = false;
    config->enableADC  = false;
    config->periodicTriggerNumber = 0U;
    config->periodicTriggerWidth  = 0U;
 * @endcode
 *
 * @param config Pointer to configuration structure.
 */
void DAC14_GetDefaultConfig(dac14_config_t *config);

/*!
 * @brief De-initialize the DAC14 module.
 *
 * The clock will be disabled in this function.
 *
 * @param base DAC14 peripheral base address.
 */
void DAC14_Deinit(HPDAC_Type *base);

/*!
 * @brief Do software reset .
 *
 * This function is resets all DAC registers and internal logic.
 *
 * @param base DAC14 peripheral base address.
 */
static inline void DAC14_DoSoftwareReset(HPDAC_Type *base)
{
    base->RCR |= HPDAC_RCR_SWRST_MASK;
    base->RCR &= ~HPDAC_RCR_SWRST_MASK;
}

/*!
 * @brief Do FIFO reset.
 *
 * This function is resets the FIFO pointers and flags in FIFO Status.
 *
 * @param base DAC14 peripheral base address.
 */
static inline void DAC14_DoFIFOReset(HPDAC_Type *base)
{
    base->RCR |= HPDAC_RCR_FIFORST_MASK;
    base->RCR &= ~HPDAC_RCR_FIFORST_MASK;
}

/*!
 * @brief Abort DAC14 period trigger conversion sequence.
 *
 * This function is write 0 to PTGEN to terminate the current conversion sequence.
 *
 * @param base DAC14 peripheral base address.
 */
static inline void DAC14_AbortPeriodTriggerConvSequence(HPDAC_Type *base)
{
    base->GCR &= ~HPDAC_GCR_PTGEN_MASK;
}
/*! @} */

/*!
 * @name DAC Control Interface
 * @{
 */

/*!
 * @brief Enable the DAC14 system.
 *
 * @param base DAC14 peripheral base address.
 * @param enable true to enable and false to disable.
 */
static inline void DAC14_Enable(HPDAC_Type *base, bool enable)
{
    if (enable)
    {
        base->GCR |= HPDAC_GCR_DACEN_MASK;
    }
    else
    {
        base->GCR &= ~HPDAC_GCR_DACEN_MASK;
    }
}
/*! @} */

/*!
 * @name Swing Back Mode Control Interface
 * @{
 */
 /*!
 * @brief Enable swing back mode.
 *
 * @param base DAC14 peripheral base address.
 * @param enable true to enable and false to disable.
 */
static inline void DAC14_EnableSwingBackMode(HPDAC_Type *base, bool enable)
{
    if (enable)
    {
        base->GCR |= HPDAC_GCR_SWMD_MASK;
    }
    else
    {
        base->GCR &= ~HPDAC_GCR_SWMD_MASK;
    }
}
/*! @} */

/*!
 * @name FIFO Mode Control Interface
 * @{
 */
 /*!
 * @brief Enable FIFO mode.
 *
 * @param base DAC14 peripheral base address.
 * @param enable true to enable and false to disable.
 */
static inline void DAC14_EnableFIFOMode(HPDAC_Type *base, bool enable)
{
    if (enable)
    {
        base->GCR |= HPDAC_GCR_FIFOEN_MASK;
    }
    else
    {
        base->GCR &= ~HPDAC_GCR_FIFOEN_MASK;
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
 * @param base DAC14 peripheral base address.
 * @param mask Mask value of indicated interrupt events, please see @ref _dac14_interrupt_enable for details.
 */
static inline void DAC14_EnableInterrupts(HPDAC_Type *base, uint32_t mask)
{
    base->IER |= mask;
}

/*!
 * @brief Disable the interrupts.
 *
 * @param base DAC14 peripheral base address.
 * @param mask Mask value of indicated interrupt events, please see @ref _dac14_interrupt_enable for details.
 */
static inline void DAC14_DisableInterrupts(HPDAC_Type *base, uint32_t mask)
{
    base->IER &= ~mask;
}
/*! @} */

/*!
 * @name DMA Control Interface
 * @{
 */
/*!
 * @brief Enable the DMA switchers or not.
 *
 * @param base DAC14 peripheral base address.
 * @param mask Mask value of indicated DMA requeset, please see @ref _dac14_dma_enable for details.
 * @param enable true to enable and false to disable.
 */
static inline void DAC14_EnableDMA(HPDAC_Type *base, uint32_t mask, bool enable)
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
 * @name Status
 * @{
 */
/*!
 * @brief Get status flags of DAC14 module.
 *
 * @param base DAC14 peripheral base address.
 * @return Current DAC status flags.
 */
static inline uint32_t DAC14_GetStatusFlags(HPDAC_Type *base)
{
    return base->FSR;
}

/*!
 * @brief Clear status flags of DAC14 module.
 *
 * @param base DAC14 peripheral base address.
 * @param flags Mask value of status flags to be cleared, please see  @ref _dac14_status_flags for details.
 */
static inline void DAC14_ClearStatusFlags(HPDAC_Type *base, uint32_t flags)
{
    base->FSR = flags;
}
/*! @} */

/*!
 * @name Functional Feature
 * @{
 */
/*!
 * @brief Set data into the entry of FIFO buffer.
 *
 * @param base DAC14 peripheral base address.
 * @param value Setting value into FIFO buffer.
 */
static inline void DAC14_SetData(HPDAC_Type *base, uint32_t value)
{
    base->DATA = HPDAC_DATA_DATA(value);
}

/*!
 * @brief Get the value of the FIFO write pointer.
 *
 * @param base DAC14 peripheral base address.
 * @return Current value of the FIFO write pointer.
 */

static inline uint32_t DAC14_GetFIFOWritePointer(HPDAC_Type *base)
{
    return (HPDAC_FPR_FIFO_WPT_MASK & base->FPR) >> HPDAC_FPR_FIFO_WPT_SHIFT;
}

/*!
 * @brief  Get the value of the FIFO read pointer.
 *
 * @param base DAC14 peripheral base address.
 * @return Current value of the FIFO read pointer.
 */

static inline uint32_t DAC14_GetFIFOReadPointer(HPDAC_Type *base)
{
    return (HPDAC_FPR_FIFO_RPT_MASK & base->FPR) >> HPDAC_FPR_FIFO_RPT_SHIFT;
}

/*!
 * @brief Do software trigger.
 *
 * @param base DAC14 peripheral base address.
 */
static inline void DAC14_DoSoftwareTrigger(HPDAC_Type *base)
{
    base->TCR = HPDAC_TCR_SWTRG_MASK;
}
/*! @} */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* FSL_DAC14_H_ */
