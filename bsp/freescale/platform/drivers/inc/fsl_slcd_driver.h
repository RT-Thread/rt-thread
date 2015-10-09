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
#ifndef __FSL_SLCD_DRIVER_H__
#define __FSL_SLCD_DRIVER_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_slcd_hal.h"

/*! 
 * @addtogroup slcd_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @brief Table of base addresses for SLCD instances. */
extern LCD_Type * const g_slcdBase[LCD_INSTANCE_COUNT];

/*! @brief Table to save SLCD IRQ enumeration numbers defined in the CMSIS header file. */
extern const IRQn_Type g_slcdIrqId[LCD_INSTANCE_COUNT];

/*! 
 * @brief This structure describes SLCD pin configuration.
 *
 * This structure is used when calling the SLCD_DRV_Init function.
 */
typedef struct SlcdPinsConfig
{
   uint32_t slcdLowPinsEnabled;            /*!< low pins from 0 to 31 and if one bit is set means the corresponding pin is enabled @internal gui name="Low pins" id="LCD_PEN_Low" */
   uint32_t slcdHighPinsEnabled;           /*!< high pins from 32 to 63 and if one bit is set means the corresponding pin is enabled @internal gui name="High pins" id="LCD_PEN_High" */
   uint32_t slcdBackPlaneLowPinsEnabled;   /*!< low pins from 0 to 31 and if one bit is set means the corresponding pin is configured as back plane @internal gui name="Back plane low pins" id="LCD_BPEN_Low" */
   uint32_t slcdBackPlaneHighPinsEnabled;  /*!< high pins from 32 to 63 and if the bit is set means the corresponding pin is configured as back plane @internal gui name="Back plane high pins" id="LCD_BPEN_High" */
}slcd_pins_config_t;

/*!
 * @brief This structure describes the programming interface of the for SLCD initialization.
 *
 * This structure is used when calling the SLCD_DRV_Init function.
 * @internal gui name="SLCD configuration" id="slcdCfg"
 */
typedef struct SlcdUserConfig
{
    
    slcd_clk_config_t             clkConfig;      /*!< Configures SLCD clock and frame frequency @internal gui name="Clock" */
    slcd_power_supply_option_t    powerSupply;    /*!< Configures SLCD power supply @internal gui name="Power supply" */
    slcd_load_adjust_t            loadAdjust;     /*!< Configures charge pump or resistor bias to handle different LCD glass capacitance @internal gui name="Load adjust" */
    slcd_duty_cyc_t               dutyCyc;        /*!< Selects the duty cycle of the LCD controller driver @internal gui name="Duty cycle" */
    slcd_regulated_voltage_trim_t trim;           /*!< Adjusts SLCD contrast @internal gui name="Regulated voltage trim" */
    bool                          slcdIntEnable;  /*!< SLCD interrupt enable or disable @internal gui name="Interrupt" */
    slcd_work_mode_t              workMode;       /*!< Configures SLCD low power work mode @internal gui name="Mode" */
}slcd_user_config_t;

 /*******************************************************************************
  * API
  *******************************************************************************/
 
 #if defined(__cplusplus)
 extern "C" {
 #endif
 
 /*! 
  * @name SLCD Driver
  * @{
  */
 
   
 /*!
  * @brief Initializes the SLCD driver.
  *
  * @param instance The SLCD peripheral instance number.
  * @param userConfigPtr The pointer to the SLCD user configure structure, see #slcd_user_config_t.
  * @return kStatus_SLCD_Success means success. Otherwise, means failure.
  */
  slcd_status_t SLCD_DRV_Init(uint32_t instance, const slcd_user_config_t *userConfigPtr);
  
  /*!
  * @brief Deinitializes the SLCD driver.
  *
  * @param instance The SLCD peripheral instance number.
  * @return kStatus_SLCD_Success means success. Otherwise, means failure.
  */
  void SLCD_DRV_Deinit(uint32_t instance);
  
 /*!
  * @brief Starts the SLCD driver.
  *
  * @param instance The SLCD peripheral instance number.
  */  
  void SLCD_DRV_Start(uint32_t instance);
  
 /*!
  * @brief Stops the SLCD driver.
  *
  * @param instance The SLCD peripheral instance number.
  */   
  void SLCD_DRV_Stop(uint32_t instance);

 /*!
  * @brief Configures the SLCD interrupt.
  *
  * @param instance The SLCD peripheral instance number.
  * @param intType interrupt type.
  * @param enable Enables or Disables interrupt.
  */   
  void SLCD_DRV_SetIntCmd(uint32_t instance, slcd_int_type_t intType, bool enable);
  
 /*!
  * @brief Starts the SLCD fault detection.
  *
  * @param instance The SLCD peripheral instance number.
  * @param faultDetectConfigPtr The pointer to SLCD configure fault detection.
  * @return kStatus_SLCD_Success means success. Otherwise, means failure. 
  */
 slcd_status_t SLCD_DRV_StartFaultDetection(uint32_t instance, const slcd_fault_detect_config_t *faultDetectConfigPtr);
 
 /*!
  * @brief Returns the fault detection configuration.
  *
  * @param instance The SLCD peripheral instance number.
  * @return true Fault detection is complete.
  * @return false Fault detection is not complete.
  */
 bool SLCD_DRV_CheckFaultDetectCompleteFlag(uint32_t instance);

 /*!
  * @brief Clears the fault detection complete flag.
  *
  * @param instance The SLCD peripheral instance number.
  */
 void SLCD_DRV_ClearFaultDetectCompleteFlag(uint32_t instance);
 
 /*!
  * @brief Returns the fault detection counter.
  *
  * @param instance The SLCD peripheral instance number.
  * @return The fault detection counter value.
  */ 
 uint8_t SLCD_DRV_GetFaultDetectCounter(uint32_t instance);

 /*!
  * @brief Checks whether the SLCD frame frequency interrupt is enabled or disabled.
  *
  * @param instance The SLCD peripheral instance number.
  * @return True This event causes an interrupt request.
  * @return False No interrupt request is generated by this event.
  */ 
 bool SLCD_DRV_CheckFrameFrequencyIntFlag(uint32_t instance);
 
 /*!
  * @brief Clears the SLCD frame frequency interrupt flag.
  *
  * @param instance The SLCD peripheral instance number.
  */  
 void SLCD_DRV_ClearFrameFrequencyIntFlag(uint32_t instance);
 
 /*!
  * @brief Starts the SLCD blinking mode.
  *
  * @param instance The SLCD peripheral instance number.
  * @param blinkConfigPtr The pointer used to configure SLCD blink configuration.
  * @return kStatus_SLCD_Success means success. Otherwise, means failure.
  */
 slcd_status_t SLCD_DRV_StartBlinkingMode(uint32_t instance, const slcd_blink_config_t *blinkConfigPtr);
 
 /*!
  * @brief Stops the SLCD blinking mode.
  *
  * @param instance The SLCD peripheral instance number.
  */
 void SLCD_DRV_StopBlinkingMode(uint32_t instance);
 
 /*!
  * @brief Starts/stops the SLCD alternating display mode.
  *
  * @param instance The SLCD peripheral instance number.
  * @param enable Disable/Enable SLCD alternating display mode.
  */ 
  void SLCD_DRV_SetAltDisplayModeCmd(uint32_t instance, bool enable);

 /*!
  * @brief Starts/stops the SLCD blank display mode.
  *
  * @param instance The SLCD peripheral instance number.
  * @param enable Disable/Enable SLCD blank display mode.
  */ 
  void SLCD_DRV_SetBlankDisplayModeCmd(uint32_t instance, bool enable);
 
 /*!
  * @brief Sets all SLCD pin configurations.
  *
  * @param instance The SLCD peripheral instance number.
  * @param pinsConfigPtr The pointer used to configure SLCD pins.
  * @return kStatus_SLCD_Success means success. Otherwise, means failure.
  */   
 slcd_status_t SLCD_DRV_SetAllPinsConfig(uint32_t instance, const slcd_pins_config_t *pinsConfigPtr);
 
 /*!
  * @brief Sets all SLCD pin waveforms.
  *
  * @param instance The SLCD peripheral instance number.
  * @param pinIndex The configured SLCD pin index form 0 to 63.
  * @param waveForm The waveForm used to configure the pin wave form.
  */ 
 void SLCD_DRV_SetPinWaveForm(uint32_t instance, uint8_t pinIndex, uint8_t waveForm);
 
 /*!
  * @brief Sets the SLCD back plane phase.
  *
  * @param instance The SLCD peripheral instance number.
  * @param pinIndex The configured SLCD pin index form 0 to 63.
  * @param phase The configured segment from 0 to 7.
  */
  void SLCD_DRV_SetBackPlanePhase(uint32_t instance, uint8_t pinIndex, slcd_phase_index_t phase);
  
 /*!
  * @brief Configures an SLCD pin segment.
  *
  * @param instance The SLCD peripheral instance number.
  * @param pinIndex The specific pin index from 0 to 63.
  * @param phaseIndex The configured segment from 0 to 7.
  * @param enable Enable/Disable the segment.
  */ 
  void SLCD_DRV_SetSegmentEnableCmd(uint32_t instance, uint8_t pinIndex, slcd_phase_index_t phaseIndex, bool enable);
 
 /*@}*/
 
 #if defined(__cplusplus)
 }
 #endif
 
 /*! @}*/
 
 #endif /* __FSL_SLCD_H__*/
 /*******************************************************************************
  * EOF
  *******************************************************************************/

