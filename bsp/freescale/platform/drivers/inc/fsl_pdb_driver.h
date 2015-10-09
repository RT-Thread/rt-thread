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

#ifndef __FSL_PDB_DRIVER_H__
#define __FSL_PDB_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_pdb_hal.h"
#if FSL_FEATURE_SOC_PDB_COUNT

/*!
 * @addtogroup pdb_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * @brief Defines the type of structure for configuring ADC's pre_trigger.
 * @internal gui name="ADC pre-trigger configuration" id="pdbAdcTrgCfg"
 */
typedef struct PdbAdcPreTriggerConfig
{
    uint32_t adcPreTriggerIdx; /*!< Setting pre_trigger's index. @internal gui name="Pre-Trigger index value" id="adcPreTriggerIdx" range="0..7" */
    bool preTriggerEnable; /*!< Enables the pre_trigger. @internal gui name="Pre-Trigger index" id="preTriggerEnable" */
    bool preTriggerOutputEnable; /*!< Enables the pre_trigger output. @internal gui name="Pre-Trigger output" id="AdcTriggerOutput" */
    bool preTriggerBackToBackEnable; /*!< Enables the back to back mode for ADC pre_trigger. @internal gui name="Back-To-Back mode" id="AdcBackToBackMode" */
} pdb_adc_pretrigger_config_t;

#if FSL_FEATURE_PDB_HAS_DAC
/*!
 * @brief Defines the type of flag for PDB pre-trigger events.
 * @internal gui name="DAC trigger configuration" id="pdbDacTrgCfg"
 */
typedef struct PdbDacIntervalConfig
{
    bool intervalTriggerEnable; /*!< Enable the DAC interval trigger. @internal gui name="Interval trigger" id="intervalTriggerEnable" */
    bool extTriggerInputEnable; /*!< Enable DAC external trigger input . @internal gui name="External trigger" id="DacExternalTrigger" */
} pdb_dac_interval_config_t;
#endif

/*! @brief Table of base addresses for PDB instances. */
extern PDB_Type * const g_pdbBase[];

/*! @brief Table to save PDB IRQ enumeration numbers defined in the CMSIS header file. */
extern const IRQn_Type g_pdbIrqId[PDB_INSTANCE_COUNT];

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the PDB counter and triggers input.
 *
 * This function initializes the PDB counter and triggers the input.
 * It resets PDB registers and enables the PDB clock. Therefore, it should be 
 * called before any other operation. After it is initialized, the PDB can
 * act as a triggered timer, which enables other features in PDB module.
 *
 * @param instance PDB instance ID.
 * @param userConfigPtr Pointer to the user configuration structure. See the "pdb_user_config_t".
 * @return Execution status.
 */
pdb_status_t PDB_DRV_Init(uint32_t instance, const pdb_timer_config_t *userConfigPtr);

/*!
 * @brief Deinitializes the PDB module.
 *
 * This function deinitializes the PDB module.
 * Calling this function shuts down the PDB module and reduces the power consumption.
 *
 * @param instance PDB instance ID.
 * @return Execution status.
 */
pdb_status_t PDB_DRV_Deinit(uint32_t instance);

/*!
 * @brief Triggers the PDB with a software trigger.
 *
 * This function triggers the PDB with a software trigger.
 * When the PDB is set to use the software trigger as input, calling this function
 * triggers the PDB.
 *
 * @param instance PDB instance ID.
 */
void PDB_DRV_SoftTriggerCmd(uint32_t instance);

/*!
 * @brief Gets the current counter value in the PDB module.
 *
 * This function gets the current counter value.
 *
 * @param instance PDB instance ID.
 * @return Current PDB counter value.
 */
uint32_t PDB_DRV_GetTimerValue(uint32_t instance);

/*!
 * @brief Gets the PDB interrupt flag.
 *
 * This function gets the PDB interrupt flag. It is asserted if the PDB interrupt occurs.
 *
 * @param instance PDB instance ID.
 * @return Assertion of indicated event.
 */
bool PDB_DRV_GetTimerIntFlag(uint32_t instance);

/*!
 * @brief Clears the interrupt flag.
 *
 * This function clears the interrupt flag.
 *
 * @param instance PDB instance ID.
 */
void PDB_DRV_ClearTimerIntFlag(uint32_t instance);
   
/*!
 * @brief Executes the command of loading values.
 *
 * This function executes the command of loading values.
 *
 * @param instance PDB instance ID.
 * @param value Setting value.
 */
void PDB_DRV_LoadValuesCmd(uint32_t instance);

/*!
 * @brief Sets the value of timer modulus.
 *
 * This function sets the value of timer modulus.
 *
 * @param instance PDB instance ID.
 * @param value Setting value.
 */
void PDB_DRV_SetTimerModulusValue(uint32_t instance, uint32_t value);

/*!
 * @brief Sets the value for the timer interrupt.
 *
 * This function sets the value for the timer interrupt.
 *
 * @param instance PDB instance ID.
 * @param value Setting value.
 */
void PDB_DRV_SetValueForTimerInterrupt(uint32_t instance, uint32_t value);

/*!
 * @brief Configures the ADC pre_trigger in the PDB module.
 *
 * This function configures the ADC pre_trigger in the PDB module.
 *
 * @param instance PDB instance ID.
 * @param chn ADC channel.
 * @param configPtr Pointer to the user configuration structure. See the "pdb_adc_pretrigger_config_t".
 * @return Execution status.
 */
pdb_status_t PDB_DRV_ConfigAdcPreTrigger(uint32_t instance, uint32_t chn, const pdb_adc_pretrigger_config_t *configPtr);

/*!
 * @brief Gets the ADC pre_trigger flag in the PDB module.
 *
 * This function gets the ADC pre_trigger flags in the PDB module.
 *
 * @param instance PDB instance ID.
 * @param chn ADC channel.
 * @param preChnMask ADC pre_trigger channels mask.
 * @return Assertion of indicated flag.
 */    
uint32_t PDB_DRV_GetAdcPreTriggerFlags(uint32_t instance, uint32_t chn, uint32_t preChnMask);

/*!
 * @brief Clears the ADC pre_trigger flag in the PDB module.
 *
 * This function clears the ADC pre_trigger flags in the PDB module.
 *
 * @param instance PDB instance ID.
 * @param chn ADC channel.
 * @param preChnMask ADC pre_trigger channels mask.
 */    
void PDB_DRV_ClearAdcPreTriggerFlags(uint32_t instance, uint32_t chn, uint32_t preChnMask);

/*!
 * @brief Gets the ADC pre_trigger flag in the PDB module.
 *
 * This function gets the ADC pre_trigger flags in the PDB module.
 *
 * @param instance PDB instance ID.
 * @param chn ADC channel.
 * @param preChnMask ADC pre_trigger channels mask.
 * @return Assertion of indicated flag.
 */  
uint32_t PDB_DRV_GetAdcPreTriggerSeqErrFlags(uint32_t instance, uint32_t chn, uint32_t preChnMask);

/*!
 * @brief Clears the ADC pre_trigger flag in the PDB module.
 *
 * This function clears the ADC pre_trigger sequence error flags in the PDB module.
 *
 * @param instance PDB instance ID.
 * @param chn ADC channel.
 * @param preChnMask ADC pre_trigger channels mask.
 */ 
void PDB_DRV_ClearAdcPreTriggerSeqErrFlags(uint32_t instance, uint32_t chn, uint32_t preChnMask);

/*!
 * @brief Sets the ADC pre_trigger delay value in the PDB module.
 *
 * This function sets Set the ADC pre_trigger delay value in the PDB module.
 *
 * @param instance PDB instance ID.
 * @param chn ADC channel.
 * @param preChn ADC pre_channel.
 * @param value Setting value.
 */
void PDB_DRV_SetAdcPreTriggerDelayValue(uint32_t instance, uint32_t chn, uint32_t preChn, uint32_t value);

#if FSL_FEATURE_PDB_HAS_DAC
/*!
 * @brief Configures the DAC interval in the PDB module.
 *
 * This function configures the DAC interval in the PDB module.
 *
 * @param instance PDB instance ID.
 * @param dacChn DAC channel.
 * @param configPtr Pointer to the user configuration structure. See the "pdb_dac_interval_config_t".
 * @return Execution status.
 */
pdb_status_t PDB_DRV_ConfigDacInterval(uint32_t instance, uint32_t dacChn, const pdb_dac_interval_config_t *configPtr);

/*!
 * @brief Sets the DAC interval value in the PDB module.
 *
 * This function sets the DAC interval value in the PDB module.
 *
 * @param instance PDB instance ID.
 * @param dacChn DAC channel.
 * @param value Setting value.
 */
void PDB_DRV_SetDacIntervalValue(uint32_t instance, uint32_t dacChn, uint32_t value);
#endif

/*!
 * @brief Switches on/off the CMP pulse out in the PDB module.
 *
 * This function switches the CMP pulse on/off in the PDB module.
 *
 * @param instance PDB instance ID.
 * @param pulseChnMask Pulse channel mask.
 * @param enable Switcher to assert the feature.
 */
void PDB_DRV_SetCmpPulseOutEnable(uint32_t instance, uint32_t pulseChnMask, bool enable);

/*!
 * @brief Sets the CMP pulse out delay value for high in the PDB module.
 *
 * This function sets the CMP pulse out delay value for high in the PDB module.
 *
 * @param instance PDB instance ID.
 * @param pulseChn Pulse channel.
 * @param value Setting value.
 */
void PDB_DRV_SetCmpPulseOutDelayForHigh(uint32_t instance, uint32_t pulseChn, uint32_t value);

/*!
 * @brief Sets the CMP pulse out delay value for low in the PDB module.
 *
 * This function sets the CMP pulse out delay value for low in the PDB module.
 *
 * @param instance PDB instance ID.
 * @param pulseChn Pulse channel.
 * @param value Setting value.
 */
void PDB_DRV_SetCmpPulseOutDelayForLow(uint32_t instance, uint32_t pulseChn, uint32_t value);

#if defined(__cplusplus)
}
#endif

/*!
 *@}
 */

#endif
#endif /* __FSL_PDB_DRIVER_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

