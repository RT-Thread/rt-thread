/*!
 * @file        apm32f0xx_crc.h
 *
 * @brief       This file contains all the functions prototypes for the CRC firmware library
 *
 * @version     V1.0.3
 *
 * @date        2022-09-20
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __APM32F0XX_CRC_H
#define __APM32F0XX_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32f0xx.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup CRC_Driver
  @{
*/

/** @defgroup CRC_Macros Macros
  @{
*/

/**@} end of group CRC_Macros */

/** @defgroup CRC_Enumerations Enumerations
  @{
*/

/**
 * @brief   CRC Reverse Input Data
 */
typedef enum
{
    CRC_REVERSE_INPUT_DATA_NO   = ((uint8_t)0x00), /*!< Bit order not affected */
    CRC_REVERSE_INPUT_DATA_8B   = ((uint8_t)0x01), /*!< Bit reversal done by byte */
    CRC_REVERSE_INPUT_DATA_16B  = ((uint8_t)0x02), /*!< Bit reversal done by half-word */
    CRC_REVERSE_INPUT_DATA_32B  = ((uint8_t)0x03), /*!< Bit reversal done by word */
} CRC_REVERSE_INPUT_DATA_T;

/**
 * @brief   CRC Polynomial Size
 */
typedef enum
{
    CRC_POLYNOMIAL_SIZE_7   = ((uint8_t)0x03), /*!< 7-bit polynomial for CRC calculation */
    CRC_POLYNOMIAL_SIZE_8   = ((uint8_t)0x02), /*!< 8-bit polynomial for CRC calculation */
    CRC_POLYNOMIAL_SIZE_16  = ((uint8_t)0x01), /*!< 16-bit polynomial for CRC calculation */
    CRC_POLYNOMIAL_SIZE_32  = ((uint8_t)0x00), /*!< 32-bit polynomial for CRC calculation */
} CRC_POLYNOMIAL_SIZE_T;

/**@} end of group CRC_Enumerations*/

/** @defgroup CRC_Structures Structures
  @{
*/

/**@} end of group CRC_Structures */

/** @defgroup CRC_Variables Variables
  @{
*/

/**@} end of group CRC_Variables */

/** @defgroup CRC_Functions Functions
  @{
*/

/* Reset CRC */
void CRC_Reset(void);

/* Reset DATA */
void CRC_ResetDATA(void);

/* CRC Polynomial Size */
void CRC_SetPolynomialSize(CRC_POLYNOMIAL_SIZE_T polynomialSize); /*!< Only for APM32F072 and APM32F091 devices */
void CRC_SetPolynomialValue(uint32_t polynomialValue); /*!< Only for APM32F072 and APM32F091 devices */

/* Performed on input data */
void CRC_SelectReverseInputData(CRC_REVERSE_INPUT_DATA_T revInData);

/* Enable and Disable Reverse Output Data */
void CRC_EnableReverseOutputData(void);
void CRC_DisableReverseOutputData(void);

/* Write INITVAL register */
void CRC_WriteInitRegister(uint32_t initValue);

/* Calculate CRC */
uint32_t CRC_CalculateCRC(uint32_t data);
uint32_t CRC_CalculateCRC8bits(uint8_t data);   /*!< Only for APM32F072 and APM32F091 devices */
uint32_t CRC_CalculateCRC16bits(uint16_t data); /*!< Only for APM32F072 and APM32F091 devices */
uint32_t CRC_CalculateBlockCRC(uint32_t pBuffer[], uint32_t bufferLength);

/* Read CRC */
uint32_t CRC_ReadCRC(void);

/* Independent Data(ID) */
void CRC_WriteIDRegister(uint8_t IDValue);
uint8_t CRC_ReadIDRegister(void);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F0XX_CRC_H */

/**@} end of group CRC_Functions */
/**@} end of group CRC_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */
