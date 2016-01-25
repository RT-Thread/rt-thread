/**
  ******************************************************************************
  * @file    idd.h
  * @author  MCD Application Team
  * @version V4.0.1
  * @date    21-July-2015
  * @brief   This file contains all the functions prototypes for the IDD driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IDD_H
#define __IDD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @addtogroup BSP
  * @{
  */

/** @addtogroup Components
  * @{
  */
    
/** @addtogroup IDD
  * @{
  */

/** @defgroup IDD_Exported_Types IDD Exported Types
  * @{
  */

/** @defgroup IDD_Config_structure  IDD Configuration structure
  * @{
  */
typedef struct
{
  uint16_t AmpliGain;       /*!< Specifies ampli gain value
                                 */
  uint16_t VddMin;          /*!< Specifies minimum MCU VDD can reach to protect MCU from reset
                                  */
  uint16_t Shunt0Value;     /*!< Specifies value of Shunt 0 if existing
                                 */
  uint16_t Shunt1Value;     /*!< Specifies value of Shunt 1 if existing
                                 */
  uint16_t Shunt2Value;     /*!< Specifies value of Shunt 2 if existing
                                 */
  uint16_t Shunt3Value;     /*!< Specifies value of Shunt 3 if existing
                                 */
  uint16_t Shunt4Value;     /*!< Specifies value of Shunt 4 if existing
                                  */
  uint16_t Shunt0StabDelay; /*!< Specifies delay of Shunt 0 stabilization if existing
                                  */
  uint16_t Shunt1StabDelay; /*!< Specifies delay of Shunt 1 stabilization if existing
                                  */
  uint16_t Shunt2StabDelay; /*!< Specifies delay of Shunt 2 stabilization if existing
                                  */
  uint16_t Shunt3StabDelay; /*!< Specifies delay of Shunt 3 stabilization if existing
                                  */
  uint16_t Shunt4StabDelay; /*!< Specifies delay of Shunt 4 stabilization if existing
                                  */
  uint8_t ShuntNbOnBoard;   /*!< Specifies number of shunts that are present on board
                                 This parameter can be a value of @ref IDD_shunt_number */
  uint8_t ShuntNbUsed;      /*!< Specifies number of shunts used for measurement
                                 This parameter can be a value of @ref IDD_shunt_number */
  uint8_t VrefMeasurement;  /*!< Specifies if Vref is automatically measured before each Idd measurement
                                 This parameter can be a value of @ref IDD_Vref_Measurement */
  uint8_t Calibration;      /*!< Specifies if calibration is done before each Idd measurement
                                  */
  uint8_t PreDelayUnit;     /*!< Specifies Pre delay unit 
                                 This parameter can be a value of @ref IDD_PreDelay */
  uint8_t PreDelayValue;    /*!< Specifies Pre delay value in selected unit
                                  */
  uint8_t MeasureNb;        /*!< Specifies number of Measure to be performed 
                                 This parameter can be a value between 1 and 256 */
  uint8_t DeltaDelayUnit;   /*!< Specifies Delta delay unit
                                  This parameter can be a value of @ref IDD_DeltaDelay */
  uint8_t DeltaDelayValue;  /*!< Specifies Delta delay between 2 measures
                                  value can be between 1 and 128 */
}IDD_ConfigTypeDef;
/**
  * @}
  */

/** @defgroup IDD_Driver_structure  IDD Driver structure
  * @{
  */
typedef struct
{
  void       (*Init)(uint16_t);
  void       (*DeInit)(uint16_t);
  uint16_t   (*ReadID)(uint16_t);
  void       (*Reset)(uint16_t);
  void       (*LowPower)(uint16_t);
  void       (*WakeUp)(uint16_t);
  void       (*Start)(uint16_t);
  void       (*Config)(uint16_t,IDD_ConfigTypeDef);
  void       (*GetValue)(uint16_t, uint32_t *);
  void       (*EnableIT)(uint16_t);
  void       (*ClearIT)(uint16_t);
  uint8_t    (*GetITStatus)(uint16_t);
  void       (*DisableIT)(uint16_t);
  void       (*ErrorEnableIT)(uint16_t);
  void       (*ErrorClearIT)(uint16_t);
  uint8_t    (*ErrorGetITStatus)(uint16_t);
  void       (*ErrorDisableIT)(uint16_t);
  uint8_t    (*ErrorGetSrc)(uint16_t);
  uint8_t    (*ErrorGetCode)(uint16_t);
}IDD_DrvTypeDef;
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __IDD_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
