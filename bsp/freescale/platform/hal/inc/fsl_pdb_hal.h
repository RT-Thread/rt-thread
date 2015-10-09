/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
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

#ifndef __FSL_PDB_HAL_H__
#define __FSL_PDB_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_PDB_COUNT

/*!
 * @addtogroup pdb_hal
 * @{
 */

/******************************************************************************
 * Definitions
 *****************************************************************************/

/*!
 * @brief PDB status return codes.
 */
typedef enum _pdb_status
{
    kStatus_PDB_Success = 0U, /*!< Success. */
    kStatus_PDB_InvalidArgument = 1U, /*!< Invalid argument existed. */
    kStatus_PDB_Failed = 2U /*!< Execution failed. */
} pdb_status_t;

/*!
 * @brief Defines the type of value load mode for the PDB module.
 *
 * Some timing related registers, such as the MOD, IDLY, CHnDLYm, INTx and POyDLY, 
 * buffer the setting values. Only the load operation is triggered.
 * The setting value is loaded from a buffer and takes effect. There are
 * four loading modes to fit different applications.
 */
typedef enum _pdb_load_value_mode
{
    kPdbLoadValueImmediately = 0U, 
        /*!<  Loaded immediately after load operation. @internal gui name="Immediately" */
    kPdbLoadValueAtModuloCounter = 1U, 
        /*!< Loaded when counter hits the modulo after load operation. @internal gui name="Modulo counter" */
    kPdbLoadValueAtNextTrigger = 2U,
        /*!< Loaded when detecting an input trigger after load operation. @internal gui name="Next trigger" */
    kPdbLoadValueAtModuloCounterOrNextTrigger = 3U 
        /*!< Loaded when counter hits the modulo or detecting an input trigger after load operation. @internal gui name="Modulo counter/Next trigger" */
} pdb_load_value_mode_t;

/*!
 * @brief Defines the type of prescaler divider for the PDB counter clock.
 */
typedef enum _pdb_clk_prescaler_div
{
    kPdbClkPreDivBy1   = 0U, /*!< Counting divided by multiplication factor selected by MULT. @internal gui name="1" */
    kPdbClkPreDivBy2   = 1U, /*!< Counting divided by multiplication factor selected by 2 times of MULT. @internal gui name="2" */
    kPdbClkPreDivBy4   = 2U, /*!< Counting divided by multiplication factor selected by 4 times of MULT. @internal gui name="4" */
    kPdbClkPreDivBy8   = 3U, /*!< Counting divided by multiplication factor selected by 8 times of MULT. @internal gui name="8" */
    kPdbClkPreDivBy16  = 4U, /*!< Counting divided by multiplication factor selected by 16 times of MULT. @internal gui name="16" */
    kPdbClkPreDivBy32  = 5U, /*!< Counting divided by multiplication factor selected by 32 times of MULT. @internal gui name="32" */
    kPdbClkPreDivBy64  = 6U, /*!< Counting divided by multiplication factor selected by 64 times of MULT. @internal gui name="64" */
    kPdbClkPreDivBy128 = 7U, /*!< Counting divided by multiplication factor selected by 128 times of MULT. @internal gui name="128" */
} pdb_clk_prescaler_div_t;

/*!
 * @brief Defines the type of trigger source mode for the PDB.
 *
 * Selects the trigger input source for the PDB. The trigger input source can
 * be internal or external (EXTRG pin), or the software trigger.
 */
typedef enum _pdb_trigger_src
{
    kPdbTrigger0  = 0U,  /*!< Select trigger-In 0. @internal gui name="External trigger" */
    kPdbTrigger1  = 1U,  /*!< Select trigger-In 1. @internal gui name="Trigger 1" */
    kPdbTrigger2  = 2U,  /*!< Select trigger-In 2. @internal gui name="Trigger 2" */
    kPdbTrigger3  = 3U,  /*!< Select trigger-In 3. @internal gui name="Trigger 3" */
    kPdbTrigger4  = 4U,  /*!< Select trigger-In 4. @internal gui name="Trigger 4" */
    kPdbTrigger5  = 5U,  /*!< Select trigger-In 5. @internal gui name="Trigger 5" */
    kPdbTrigger6  = 6U,  /*!< Select trigger-In 6. @internal gui name="Trigger 6" */
    kPdbTrigger7  = 7U,  /*!< Select trigger-In 7. @internal gui name="Trigger 7" */
    kPdbTrigger8  = 8U,  /*!< Select trigger-In 8. @internal gui name="Trigger 8" */
    kPdbTrigger9  = 9U,  /*!< Select trigger-In 8. @internal gui name="Trigger 9" */
    kPdbTrigger10 = 10U, /*!< Select trigger-In 10. @internal gui name="Trigger 10" */
    kPdbTrigger11 = 11U, /*!< Select trigger-In 11. @internal gui name="Trigger 11" */
    kPdbTrigger12 = 12U, /*!< Select trigger-In 12. @internal gui name="Trigger 12" */
    kPdbTrigger13 = 13U, /*!< Select trigger-In 13. @internal gui name="Trigger 13" */
    kPdbTrigger14 = 14U, /*!< Select trigger-In 14. @internal gui name="Trigger 14" */
    kPdbSoftTrigger = 15U, /*!< Select software trigger. @internal gui name="Software trigger" */
} pdb_trigger_src_t;

/*!
 * @brief Defines the type of the multiplication source mode for PDB.
 *
 * Selects the multiplication factor of the prescaler divider for the PDB counter clock.
 */
typedef enum _pdb_clk_prescaler_mult_factor
{
    kPdbClkPreMultFactorAs1  = 0U, /*!< Multiplication factor is 1. @internal gui name="1" */
    kPdbClkPreMultFactorAs10 = 1U, /*!< Multiplication factor is 10. @internal gui name="10" */
    kPdbClkPreMultFactorAs20 = 2U, /*!< Multiplication factor is 20. @internal gui name="20" */
    kPdbClkPreMultFactorAs40 = 3U  /*!< Multiplication factor is 40. @internal gui name="40" */
} pdb_clk_prescaler_mult_factor_t;

/*!
 * @brief Defines the type of structure for basic timer in PDB.
 *
 * @internal gui name="Basic configuration" id="pdbCfg"
 */
typedef struct PdbTimerConfig
{
    pdb_load_value_mode_t loadValueMode; /*!< Select the load mode. @internal gui name="Load mode" id="LoadMode" */
    bool seqErrIntEnable; /*!< Enable PDB Sequence Error Interrupt. @internal gui name="Sequence error interrupt" id="SequenceErrorInterrupt" */
    pdb_clk_prescaler_div_t clkPreDiv; /*!< Select the prescaler divider. @internal gui name="Prescaler divider" id="Divider" */
    pdb_clk_prescaler_mult_factor_t clkPreMultFactor; /*!< Select multiplication factor for prescaler. @internal gui name="Prescaler multiplication factor" id="Multiplier" */
    pdb_trigger_src_t triggerInput; /*!< Select the trigger input source. @internal gui name="Trigger" id="Trigger" */
    bool continuousModeEnable; /*!< Enable the continuous mode. @internal gui name="Continuous mode" id="ContinuousMode" */
    bool dmaEnable; /*!< Enable the dma for timer. @internal gui name="DMA" id="DMA" */
    bool intEnable; /*!< Enable the interrupt for timer. @internal gui name="Interrupt" id="Interrupt" */
} pdb_timer_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief Resets the PDB registers to a known state.
 *
 * This function resets the PDB registers to a known state. This state is
 * defined in a reference manual and is power-on-reset value.
 *
 * @param base Register base address for the module.
 */
void PDB_HAL_Init(PDB_Type * base);

/*!
 * @brief Configures the PDB timer.
 *
 * This function configures the PDB basic timer.
 *
 * @param base Register base address for the module.
 * @param configPtr Pointer to configuration structure, see to "pdb_timer_config_t".
 * @return Execution status.
 */
pdb_status_t PDB_HAL_ConfigTimer(PDB_Type * base, const pdb_timer_config_t *configPtr);

/*!
 * @brief Triggers the DAC by software if enabled.
 *
 * If enabled, this function triggers the DAC by using software.
 *
 * @param base Register base address for the module.
 */
static inline void PDB_HAL_SetSoftTriggerCmd(PDB_Type * base)
{
    PDB_BWR_SC_SWTRIG(base, 1U);
}

/*!
 * @brief Switches on to enable the PDB module.
 *
 * This function switches on to enable the PDB module.
 *
 * @param base Register base address for the module.
 */
static inline void PDB_HAL_Enable(PDB_Type * base)
{
    PDB_BWR_SC_PDBEN(base, 1U);
}
/*!
 * @brief Switches to disable the PDB module.
 *
 * This function switches to disable the PDB module.
 *
 * @param base Register base address for the module.
 */
static inline void PDB_HAL_Disable(PDB_Type * base)
{
    PDB_BWR_SC_PDBEN(base, 0U);
}

/*!
 * @brief Gets the PDB delay interrupt flag.
 *
 * This function gets the PDB delay interrupt flag.
 *
 * @param base Register base address for the module.
 * @return Flat status, true if the flag is set.
 */
static inline bool PDB_HAL_GetTimerIntFlag(PDB_Type * base)
{
    return (1U == PDB_BRD_SC_PDBIF(base));
}

/*!
 * @brief Clears the PDB delay interrupt flag.
 *
 * This function clears the PDB delay interrupt flag.
 *
 * @param base Register base address for the module.
 * @return Flat status, true if the flag is set.
 */
static inline void PDB_HAL_ClearTimerIntFlag(PDB_Type * base)
{
    PDB_BWR_SC_PDBIF(base, 0U);
}

/*!
 * @brief Loads the delay registers value for the PDB module.
 *
 * This function sets the LDOK bit and loads the delay registers value.
 * Writing one  to this bit updates the internal registers MOD, IDLY, CHnDLYm, 
 * DACINTx, and POyDLY with the values written to their buffers. The MOD, IDLY, 
 * CHnDLYm, DACINTx, and POyDLY take effect according to the load mode settings.
 *
 * After one is written to the LDOK bit, the values in the buffers of the above mentioned registers 
 * are not effective and cannot be written until the values in the
 * buffers are loaded into their internal registers. 
 * The LDOK can be written only when the the PDB is enabled or as alone with it. It is
 * automatically cleared either when the values in the buffers are loaded into the
 * internal registers or when the PDB is disabled.
 *
 * @param base Register base address for the module.
 */
static inline void PDB_HAL_SetLoadValuesCmd(PDB_Type * base)
{
    PDB_BWR_SC_LDOK(base, 1U);
}

/*!
 * @brief Sets the modulus value for the PDB module.
 *
 * This function sets the modulus value for the PDB module.
 * When the counter reaches the setting value, it is automatically reset to zero.
 * When in continuous mode, the counter begins to increase
 * again.
 *
 * @param base Register base address for the module.
 * @param value The setting value of upper limit for PDB counter.
 */
static inline void PDB_HAL_SetTimerModulusValue(PDB_Type * base, uint32_t value)
{
    PDB_BWR_MOD_MOD(base, value);
}

/*!
 * @brief Gets the PDB counter value of PDB timer.
 *
 * This function gets the PDB counter value of PDB timer.
 *
 * @param base Register base address for the module.
 * @return The current counter value.
 */
static inline uint32_t PDB_HAL_GetTimerValue(PDB_Type * base)
{
    return PDB_BRD_CNT_CNT(base);
}

/*!
 * @brief Sets the interrupt delay milestone of the PDB counter.
 *
 * This function sets the interrupt delay milestone of the PDB counter.
 * If enabled, a PDB interrupt is generated when the counter is equal to the 
 * setting value. 
 *
 * @param base Register base address for the module.
 * @param value The setting value for interrupt delay milestone of PDB counter.
 */
static inline void PDB_HAL_SetValueForTimerInterrupt(PDB_Type * base, uint32_t value)
{
    PDB_BWR_IDLY_IDLY(base, value);
}

/*!
 * @brief Switches to enable the pre-trigger back-to-back mode.
 *
 * This function switches to enable the pre-trigger back-to-back mode.
 *
 * @param base Register base address for the module.
 * @param chn ADC instance index for trigger.
 * @param preChnMask ADC channel group index mask for trigger.
 * @param enable Switcher to assert the feature.
 */
void PDB_HAL_SetAdcPreTriggerBackToBackEnable(PDB_Type * base, uint32_t chn, uint32_t preChnMask, bool enable);

/*!
 * @brief Switches to enable the pre-trigger output.
 *
 * This function switches to enable pre-trigger output.
 *
 * @param base Register base address for the module.
 * @param chn ADC instance index for trigger.
 * @param preChnMask ADC channel group index mask for trigger.
 * @param enable Switcher to assert the feature.
 */
void PDB_HAL_SetAdcPreTriggerOutputEnable(PDB_Type * base, uint32_t chn, uint32_t preChnMask, bool enable);

/*!
 * @brief Switches to enable the pre-trigger.
 *
 * This function switches to enable the pre-trigger.
 *
 * @param base Register base address for the module.
 * @param chn ADC instance index for trigger.
 * @param preChnMask ADC channel group index mask for trigger.
 * @param enable Switcher to assert the feature.
 */
void PDB_HAL_SetAdcPreTriggerEnable(PDB_Type * base, uint32_t chn, uint32_t preChnMask, bool enable);

/*!
 * @brief Gets the flag which indicates whether the PDB counter has reached the pre-trigger delay value.
 *
 * This function gets the flag which indicates the PDB counter has reached the
 * pre-trigger delay value.
 *
 * @param base Register base address for the module.
 * @param chn ADC instance index for trigger.
 * @param preChnMask ADC channel group index mask for trigger.
 * @return Flag mask. Indicated bit would be 1 if the event is asserted.
 */
static inline uint32_t PDB_HAL_GetAdcPreTriggerFlags(PDB_Type * base, uint32_t chn, uint32_t preChnMask)
{
    assert(chn < PDB_C1_COUNT);
    return (preChnMask & PDB_BRD_S_CF(base, chn) );
}

/*!
 * @brief Clears the flag which indicates that the PDB counter has reached the pre-trigger delay value.
 *
 * This function clears the flag which indicates that the PDB counter has reached  the
 * pre-trigger delay value.
 *
 * @param base Register base address for the module.
 * @param chn ADC instance index for trigger.
 * @param preChnMask ADC channel group index mask for trigger.
 */
void PDB_HAL_ClearAdcPreTriggerFlags(PDB_Type * base, uint32_t chn, uint32_t preChnMask);

/*!
 * @brief Gets the flag which indicates whether a sequence error is detected.
 *
 * This function gets the flag which indicates whether a sequence error is detected.
 *
 * @param base Register base address for the module.
 * @param chn ADC instance index for trigger.
 * @param preChnMask ADC channel group index mask for trigger.
 * @return Flag mask. Indicated bit would be 1 if the event is asserted.
 */
static inline uint32_t PDB_HAL_GetAdcPreTriggerSeqErrFlags(PDB_Type * base, uint32_t chn, uint32_t preChnMask)
{
    assert(chn < PDB_C1_COUNT);
    return ( preChnMask & PDB_BRD_S_ERR(base, chn) );
}

/*!
 * @brief Clears the flag which indicates that a sequence error has been detected.
 *
 * This function clears the flag which indicates that the sequence error has been detected.
 *
 * @param base Register base address for the module.
 * @param chn ADC instance index for trigger.
 * @param preChnMask ADC channel group index mask for trigger.
 */
void PDB_HAL_ClearAdcPreTriggerSeqErrFlags(PDB_Type * base, uint32_t chn, uint32_t preChnMask);

/*!
 * @brief Sets the pre-trigger delay value.
 *
 * This function sets the pre-trigger delay value.
 *
 * @param base Register base address for the module.
 * @param chn ADC instance index for trigger.
 * @param preChn ADC channel group index for trigger.
 * @param value Setting value for pre-trigger's delay value.
 */
void PDB_HAL_SetAdcPreTriggerDelayValue(PDB_Type * base, uint32_t chn, uint32_t preChn, uint32_t value);

#if FSL_FEATURE_PDB_HAS_DAC
/*!
 * @brief Switches to enable the DAC external trigger input.
 *
 * This function switches to enable the DAC external trigger input.
 *
 * @param base Register base address for the module.
 * @param dacChn DAC instance index for trigger.
 * @param value Setting value for pre-trigger's delay value.
 * @param enable Switcher to assert the feature.
 */
static inline void PDB_HAL_SetDacExtTriggerInputEnable(PDB_Type * base, uint32_t dacChn, bool enable)
{
    assert(dacChn < PDB_INTC_COUNT);
    PDB_BWR_INTC_EXT(base, dacChn, (enable ? 1U: 0U) );
}

/*!
 * @brief Switches to enable the DAC external trigger input.
 *
 * This function switches to enable the DAC external trigger input.
 *
 * @param base Register base address for the module.
 * @param dacChn DAC instance index for trigger.
 * @param enable Switcher to assert the feature.
 */
static inline void PDB_HAL_SetDacIntervalTriggerEnable(PDB_Type * base, uint32_t dacChn, bool enable)
{
    assert(dacChn < PDB_INTC_COUNT);
    PDB_BWR_INTC_TOE(base, dacChn, (enable ? 1U: 0U) );
}

/*!
 * @brief Sets the interval value for the DAC trigger.
 *
 * This function sets the interval value for the DAC trigger.
 *
 * @param base Register base address for the module.
 * @param dacChn DAC instance index for trigger.
 * @param value Setting value for DAC trigger interval.
 */
static inline void PDB_HAL_SetDacIntervalValue(PDB_Type * base, uint32_t dacChn, uint32_t value)
{
    assert(dacChn < PDB_INT_COUNT);
    PDB_BWR_INT_INT(base, dacChn, value);
}
#endif

/*!
 * @brief Switches to enable the pulse-out trigger.
 *
 * This function switches to enable the pulse-out trigger.
 *
 * @param base Register base address for the module.
 * @param pulseChnMask Pulse-out channel index mask for trigger.
 * @param enable Switcher to assert the feature.
 */
void PDB_HAL_SetCmpPulseOutEnable(PDB_Type * base, uint32_t pulseChnMask, bool enable);

/*!
 * @brief Sets the counter delay value for the pulse-out goes high.
 *
 * This function sets the counter delay value for the pulse-out goes high.
 *
 * @param base Register base address for the module.
 * @param pulseChn Pulse-out channel index for trigger.
 * @param value Setting value for PDB delay .
 */
static inline void PDB_HAL_SetCmpPulseOutDelayForHigh(PDB_Type * base, uint32_t pulseChn, uint32_t value)
{
    assert(pulseChn < PDB_PODLY_COUNT);
    PDB_BWR_PODLY_DLY1(base, pulseChn, value);
}

/*!
 * @brief Sets the counter delay value for the pulse-out goes low.
 *
 * This function sets the counter delay value for the pulse-out goes low.
 *
 * @param base Register base address for the module.
 * @param pulseChn Pulse-out channel index for trigger.
 * @param value Setting value for PDB delay .
 */
static inline void PDB_HAL_SetCmpPulseOutDelayForLow(PDB_Type * base, uint32_t pulseChn, uint32_t value)
{
    assert(pulseChn < PDB_PODLY_COUNT);
    PDB_BWR_PODLY_DLY2(base, pulseChn, value);
}

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif
#endif /* __FSL_PDB_HAL_H__ */

/******************************************************************************
 * EOF
 *****************************************************************************/

