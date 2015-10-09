/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __FSL_DAC_HAL_H__
#define __FSL_DAC_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"

#if FSL_FEATURE_SOC_DAC_COUNT

/*!
 * @addtogroup dac_hal
 * @{
 */

/******************************************************************************
 * Enumerations
 *****************************************************************************/

/*!
 * @brief DAC status return codes.
 */
typedef enum _dac_status
{
    kStatus_DAC_Success = 0U, /*!< Success. */
    kStatus_DAC_InvalidArgument = 1U, /*!< Invalid argument. */
    kStatus_DAC_Failed = 2U /*!< Execution failed. */
} dac_status_t;

/*!
 * @brief Defines the type of selection for DAC module's reference voltage source.
 *
 * See the appropriate SoC Reference Manual for actual connections.
 */
typedef enum _dac_ref_volt_src_mode
{
    kDacRefVoltSrcOfVref1 = 0U, /*!< Select DACREF_1 as the reference voltage. @internal gui name="Reference 1" */
    kDacRefVoltSrcOfVref2 = 1U  /*!< Select DACREF_2 as the reference voltage. @internal gui name="Reference 2" */
} dac_ref_volt_src_mode_t;

/*!
 * @brief Defines the type of selection for DAC module trigger mode.
 */
typedef enum _dac_trigger_mode
{
    kDacTriggerByHardware = 0U, /*!< Select hardware trigger. @internal gui name="HW" */
    kDacTriggerBySoftware = 1U  /*!< Select software trigger. @internal gui name="SW" */
} dac_trigger_mode_t;

/*!
 * @brief Defines the type of selection for buffer watermark mode.
 *
 * If the buffer feature for DAC module is enabled, a watermark event 
 * occurs when the buffer index reaches the watermark.
 */
typedef enum _dac_buff_watermark_mode
{
    kDacBuffWatermarkFromUpperAs1Word = 0U, /*!< Select 1 word away from the upper limit of buffer. @internal gui name="1 word in normal, 2 words in FIFO mode" */
    kDacBuffWatermarkFromUpperAs2Word = 1U, /*!< Select 2 word away from the upper limit of buffer. @internal gui name="2 word in normal, 4 words in FIFO mode" */
    kDacBuffWatermarkFromUpperAs3Word = 2U, /*!< Select 3 word away from the upper limit of buffer. @internal gui name="3 word in normal, 8 words in FIFO mode" */
    kDacBuffWatermarkFromUpperAs4Word = 3U  /*!< Select 4 word away from the upper limit of buffer. @internal gui name="4 word in normal, 14 words in FIFO mode" */
} dac_buff_watermark_mode_t;

/*!
 * @brief Defines the type of selection for buffer work mode.
 *
 * These are the work modes when the DAC buffer is enabled.\n
 * \li Normal mode - When the buffer index reaches the upper level, it
 *     starts (0) on the next trigger.
 * \li Swing mode - When the buffer index reaches the upper level, it goes backward to
 *    the start and is reduced one-by-one on the next trigger. When the buffer index
 *    reaches the start, it goes backward to the upper level and increases one-by-one
 *    on the next trigger.
 * \li One-Time-Scan mode - The buffer index can only be increased on the next trigger.
 *    When the buffer index reaches the upper level, it is not updated by the trigger.
 * \li FIFO mode - In FIFO mode, the buffer is organized as a FIFO. For a valid 
 *    write to any item, the data is put into the FIFO. The written index
 *    in buffer should be an even number; otherwise, the write is ignored.
 */
typedef enum _dac_buff_work_mode
{
    kDacBuffWorkAsNormalMode = 0U /*!< Buffer works normally. @internal gui name="Normal" */
/* For 1-bit DACBFMD. */
#if DAC_C1_DACBFMD_WIDTH==1
    ,kDacBuffWorkAsOneTimeScanMode = 1U /*!< Buffer works as a one time scan. @internal gui name="" */
/* For 2-bit DACBFMD. */
#elif DAC_C1_DACBFMD_WIDTH==2
#if FSL_FEATURE_DAC_HAS_BUFFER_SWING_MODE
    ,kDacBuffWorkAsSwingMode = 1U /*!< Buffer works as a swing. @internal gui name="Swing mode" */
#endif /* FSL_FEATURE_DAC_HAS_BUFFER_SWING_MODE */
    ,kDacBuffWorkAsOneTimeScanMode = 2U /*!< Buffer works as a one time scan. @internal gui name="One-time scan" */
#if FSL_FEATURE_DAC_HAS_BUFFER_FIFO_MODE
    ,kDacBuffWorkAsFIFOMode = 3U /*!< Buffer works as FIFO. @internal gui name="FIFO" */
#endif /* FSL_FEATURE_DAC_HAS_BUFFER_FIFO_MODE */
#endif /* DAC_C1_DACBFMD_WIDTH */
} dac_buff_work_mode_t;

/******************************************************************************
 * Definitions
 *****************************************************************************/
/*!
 * @brief Defines the type of structure for configuring the DAC converter.
 * @internal gui name="Basic configuration" id="dacCfg"
 */
typedef struct DacConverterConfig
{
    dac_ref_volt_src_mode_t dacRefVoltSrc; /*!< Select the reference voltage source. @internal gui name="Voltage reference" id="VoltageReference" */
    bool lowPowerEnable; /*!< Enable the low power mode. @internal gui name="Low power mode" id="LowPowerMode" */
} dac_converter_config_t;

/*!
 * @brief Defines the type of structure for configuring the DAC buffer.
 * @internal gui name="Buffer configuration" id="dacBuffCfg"
 */
typedef struct DacBufferConfig
{
    bool bufferEnable; /*!< Enable the buffer function. @internal gui name="Buffer" id="Buffer" */
    dac_trigger_mode_t triggerMode; /*!< Select the trigger mode. @internal gui name="Trigger mode" id="TriggerMode" */
    /* Buffer interrupt. */
#if FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION
    bool idxWatermarkIntEnable; 
        /*!< Switcher to enable interrupt when buffer index reaches the watermark. @internal gui name="Watermark interrupt" id="WatermarkInterrupt" */
    dac_buff_watermark_mode_t watermarkMode;
        /*!< Selection of watermark setting. See "dac_buff_watermark_mode_t". @internal gui name="Watermark mode" id="WatermarkMode" */
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION */
    bool idxStartIntEnable;
        /*!< Switcher to enable interrupt when buffer index reaches the start (0). @internal gui name="Buffer bottom interrupt" id="BufferBottomInterrupt" */
    bool idxUpperIntEnable;
        /*!< Switcher to enable interrupt when buffer index reaches the upper limit. @internal gui name="Buffer top interrupt" id="BufferTopInterrupt" */
    bool dmaEnable; /*!< Switcher to enable DMA request by original interrupts. @internal gui name="DMA" id="DMASupport" */
    dac_buff_work_mode_t buffWorkMode;
        /*!< Selection of buffer's work mode. See "dac_buff_work_mode_t". @internal gui name="Buffer mode" id="BufferMode" */
    uint8_t upperIdx; /*!< Setting of the buffer's upper limit, 0-15. @internal gui name="Upper limit" id="UpperLimit" */
} dac_buffer_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief Resets all configurable registers to the reset state for DAC.
 *
 * This function resets all configurable registers to the reset state for DAC.
 * It should be called before configuring the DAC module.
 *
 * @param base The DAC peripheral base address.
 */
void DAC_HAL_Init(DAC_Type * base);

/*--------------------------------------------------------------------------*
* DAC converter.
*--------------------------------------------------------------------------*/
/*!
 * @brief Configures the converter for DAC.
 *
 * This function configures the converter for DAC. The features it covers are a
 * one-time setting in the application. 
 *
 * @param base The DAC peripheral base address.
 * @param configPtr The pointer to configure structure.
 */
void DAC_HAL_ConfigConverter(DAC_Type * base, const dac_converter_config_t *configPtr);

/*--------------------------------------------------------------------------*
* DAC buffer.
*--------------------------------------------------------------------------*/

/*!
 * @brief Configures the buffer for DAC.
 *
 * This function configures the converter for DAC. The features it covers are used
 * for the buffer. 
 *
 * @param base The DAC peripheral base address.
 * @param configPtr The pointer to configure structure.
 */
void DAC_HAL_ConfigBuffer(DAC_Type * base, const dac_buffer_config_t *configPtr);

/*!
 * @brief Sets the 12-bit value for the DAC items in the buffer.
 *
 * This function sets the value assembled by the low 8 bits and high 4
 * bits of 12-bit DAC item in the buffer.
 *
 * @param base The DAC peripheral base address.
 * @param idx Buffer index.
 * @param value Setting value.
 */
void DAC_HAL_SetBuffValue(DAC_Type * base, uint8_t idx, uint16_t value);

/*!
 * @brief Clears the flag of the DAC buffer read pointer.
 *
 * This function clears the flag of the DAC buffer read pointer when it reaches the
 * bottom position.
 *
 * @param base The DAC peripheral base address.
 */
static inline void DAC_HAL_ClearBuffIdxUpperFlag(DAC_Type * base)
{
    DAC_BWR_SR_DACBFRPBF(base, 0U);
}

/*!
 * @brief Gets the flag of the DAC buffer read pointer when it reaches the bottom position.
 *
 * This function gets the flag of DAC buffer read pointer when it reaches the
 * bottom position.
 *
 * @param base The DAC peripheral base address.
 * @return Assertion of indicated event.
 */
static inline bool DAC_HAL_GetBuffIdxUpperFlag(DAC_Type * base)
{
    return ( 1U == DAC_BRD_SR_DACBFRPBF(base) );
}

/*!
 * @brief Clears the flag of the DAC buffer read pointer when it reaches the top position.
 *
 * This function clears the flag of the DAC buffer read pointer when it reaches the
 * top position.
 *
 * @param base The DAC peripheral base address.
 */
static inline void DAC_HAL_ClearBuffIdxStartFlag(DAC_Type * base)
{
    DAC_BWR_SR_DACBFRPTF(base, 0U);
}

/*!
 * @brief Gets the flag of the DAC buffer read pointer when it reaches the top position.
 *
 * This function gets the flag of the DAC buffer read pointer when it reaches the
 * top position.
 *
 * @param base The DAC peripheral base address.
 * @return Assertion of indicated event.
 */
static inline bool DAC_HAL_GetBuffIdxStartFlag(DAC_Type * base)
{
    return ( 1U == DAC_BRD_SR_DACBFRPTF(base) );
}

#if FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION

/*!
 * @brief Gets the flag of the DAC buffer read pointer when it reaches the watermark position.
 *
 * This function gets the flag of the DAC buffer read pointer when it reaches the
 * watermark position.
 *
 * @param base The DAC peripheral base address.
 * @return Assertion of indicated event.
 */
static inline bool DAC_HAL_GetBuffIdxWatermarkFlag(DAC_Type * base)
{
    return ( 1U == DAC_BRD_SR_DACBFWMF(base) );
}

/*!
 * @brief Clears the flag of the DAC buffer read pointer when it reaches the watermark position.
 *
 * This function clears the flag of the DAC buffer read pointer when it reaches the
 * watermark position.
 *
 * @param base The DAC peripheral base address.
 */
static inline void DAC_HAL_ClearBuffIdxWatermarkFlag(DAC_Type * base)
{
    DAC_BWR_SR_DACBFWMF(base, 0U);
}
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION */

/*!
 * @brief Enables the Programmable Reference Generator.
 *
 * This function enables the Programmable Reference Generator. Then, the
 * DAC system is enabled.
 *
 * @param base The DAC peripheral base address.
 */
static inline void DAC_HAL_Enable(DAC_Type * base)
{
    DAC_BWR_C0_DACEN(base, 1U);
}

/*!
 * @brief Disables the Programmable Reference Generator.
 *
 * This function disables the Programmable Reference Generator. Then, the
 * DAC system is disabled.
 *
 * @param base The DAC peripheral base address.
 */
static inline void DAC_HAL_Disable(DAC_Type * base)
{
    DAC_BWR_C0_DACEN(base, 0U);
}

/*!
 * @brief Triggers the converter with software.
 *
 * This function triggers the converter with software. If the DAC software
 * trigger is selected and buffer enabled, calling this API advances the
 * buffer read pointer once.
 *
 * @param base The DAC peripheral base address.
 */
static inline void DAC_HAL_SetSoftTriggerCmd(DAC_Type * base)
{
    /* For supporting some chips with no bit-band access. */
    DAC_SET_C0(base, DAC_C0_DACSWTRG_MASK);  
}

/*!
 * @brief Sets the buffer index for the DAC module.
 *
 * This function sets the current buffer index for the DAC module.
 *
 * @param base the DAC peripheral base address.
 * @param idx Setting buffer index.
 */
static inline void DAC_HAL_SetBuffCurIdx(DAC_Type * base, uint8_t idx)
{
    assert(idx < DAC_DATL_COUNT);
    DAC_BWR_C2_DACBFRP(base, idx);
}

/*!
 * @brief Gets the buffer index for the DAC module.
 *
 * This function gets the current buffer index for the DAC module.
 *
 * @param base the DAC peripheral base address.
 * @return Current index of buffer.
 */
static inline uint8_t DAC_HAL_GetBuffCurIdx(DAC_Type * base)
{
    return DAC_BRD_C2_DACBFRP(base);
}

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif /* __FSL_DAC_HAL_H__ */

/******************************************************************************
 * EOF
 *****************************************************************************/


#endif
