/*!
 * @file        apm32f4xx_crc.c
 *
 * @brief       This file provides all the CRC firmware functions
 *
 * @version     V1.0.2
 *
 * @date        2022-06-23
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#include "apm32f4xx_crc.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @defgroup CRC_Driver
  * @brief CRC driver modules
  @{
*/

/** @defgroup CRC_Functions
  @{
*/

/*!
 * @brief     Reset CRC data register.
 *
 * @param     None
 *
 * @retval    None
 */
void CRC_ResetDATA(void)
{
    CRC->CTRL_B.RST = BIT_SET;
}

/*!
 * @brief     Calculate CRC of a 32bit data word.
 *
 * @param     data: a data word to compute its CRC.
 *                  This parameter can be a 32bit value:
 *
 * @retval    A 32-bit CRC value
 */
uint32_t CRC_CalculateCRC(uint32_t data)
{
    CRC->DATA = data;

    return (CRC->DATA);
}

/*!
 * @brief     Computes the 32-bit CRC of a given buffer of data word(32-bit).
 *
 * @param     buf: Pointer to the buffer containing the data to be computed.
 *
 * @param     bufLen: The length of buffer which is computed.
 *
 * @retval    A 32-bit CRC value
 */
uint32_t CRC_CalculateBlockCRC(uint32_t *buf, uint32_t bufLen)
{
    while (bufLen--)
    {
        CRC->DATA = *buf++;
    }

    return (CRC->DATA);
}

/*!
 * @brief     Returns the current CRC value.
 *
 * @param     None
 *
 * @retval    A 32-bit CRC value
 */
uint32_t CRC_ReadCRC(void)
{
    return (CRC->DATA);
}

/*!
 * @brief     Saves a 8bit data in the Independent Data register(INDATA).
 *
 * @param     inData: a 8-bit value to be stored in the ID register
 *
 * @retval    None
 */
void CRC_WriteIDRegister(uint8_t inData)
{
    CRC->INDATA = inData;
}

/*!
 * @brief      Reads a 8-bit data saved in the Independent Data register(INDATA).
 *
 * @param      None
 *
 * @retval     a 8-bit value from the INDATA register
 */
uint8_t CRC_ReadIDRegister(void)
{
    return (CRC->INDATA);
}

/**@} end of group CRC_Functions */
/**@} end of group CRC_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
