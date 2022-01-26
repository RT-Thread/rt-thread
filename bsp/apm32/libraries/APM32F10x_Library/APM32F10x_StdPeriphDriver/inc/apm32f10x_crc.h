/*!
 * @file       apm32f10x_crc.h
 *
 * @brief      This file contains all the functions prototypes for the CRC firmware library
 *
 * @version    V1.0.1
 *
 * @date       2021-03-23
 *
 */

#ifndef __APM32F10X_CRC_H
#define __APM32F10X_CRC_H

#include "apm32f10x.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup CRC_Driver CRC Driver
  @{
*/

/** @addtogroup CRC_Fuctions Fuctions
  @{
*/

/** Reset DATA */
void CRC_ResetDATA(void);

/** Operation functions */
uint32_t CRC_CalculateCRC(uint32_t data);
uint32_t CRC_CalculateBlockCRC(uint32_t *buf, uint32_t bufLen);
uint32_t CRC_ReadCRC(void);
void CRC_WriteIDRegister(uint8_t inData);
uint8_t CRC_ReadIDRegister(void);

/**@} end of group CRC_Fuctions*/
/**@} end of group CRC_Driver */
/**@} end of group Peripherals_Library*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32F10X_CRC_H */

