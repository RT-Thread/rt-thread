/*!
 * @file        apm32f4xx_hash.c
 *
 * @brief       This file provides all the HASH firmware functions
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

#include "apm32f4xx_hash.h"
#include "apm32f4xx_rcm.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @defgroup HASH_Driver
  * @brief HASH driver modules
  @{
*/

/** @defgroup HASH_Functions
  @{
*/

/*!
 * @brief     Reset the HASH peripheral register.
 *
 * @param     None
 *
 * @retval    None
 */
void HASH_Reset(void)
{
    RCM_EnableAHB2PeriphReset(RCM_AHB2_PERIPH_HASH);
    RCM_DisableAHB2PeriphReset(RCM_AHB2_PERIPH_HASH);
}

/*!
 * @brief     Config the HASH peripheral according to the specified parameters in the hashConfig.
 *
 * @param     hashConfig: pointer to a HASH_Config_T structure.
 *
 * @retval    None
 */
void HASH_Config(HASH_Config_T *hashConfig)
{
    /* Configure the Algorithm used, algorithm mode and the datatype */
    HASH->CTRL_B.ALGSEL = RESET;
    HASH->CTRL_B.DTYPE = RESET;
    HASH->CTRL_B.MODESEL = RESET;

    HASH->CTRL_B.ALGSEL = hashConfig->algoSelect;
    HASH->CTRL_B.DTYPE = hashConfig->dataType;
    HASH->CTRL_B.MODESEL = hashConfig->algoMode;

    /* if algorithm mode is HMAC, set the Key */
    if (hashConfig->algoMode == HASH_ALGO_MODE_HMAC)
    {
        HASH->CTRL_B.LKEYSEL = RESET;
        HASH->CTRL_B.LKEYSEL = hashConfig->hmacKeyType;
    }

    /* Reset the HASH processor core, so that the HASH will be ready to compute
     the message digest of a new message */
    HASH->CTRL_B.INITCAL = SET;
}

/*!
 * @brief     Fills each HASH_Config_T member with its default value.
 *
 * @param     hashConfig: pointer to an HASH_Config_T structure.
 *
 * @retval    None
 */
void HASH_ConfigStructInit(HASH_Config_T *hashConfig)
{
    hashConfig->algoSelect = HASH_ALGO_SELECTION_SHA1;
    hashConfig->algoMode = HASH_ALGO_MODE_HASH;
    hashConfig->dataType = HASH_DATA_TYPE_32B;
    hashConfig->hmacKeyType = HASH_HMAC_KEY_TYPE_SHORTKEY;
}

/*!
 * @brief     Resets the HASH processor core.
 *
 * @param     None
 *
 * @retval    None
 */
void HASH_ResetProceCore(void)
{
    HASH->CTRL_B.INITCAL = SET;
}

/*!
 * @brief     Configure the Number of valid bits in last word of the message.
 *
 * @param     ValidNumber: Number of valid bits in last word of the message.
 *
 * @retval    None
 */
void HASH_ConfigLastWordValidBitsNbr(uint16_t validNumber)
{
    HASH->START_B.LWNUM = RESET;
    HASH->START_B.LWNUM = validNumber;
}

/*!
 * @brief     Writes data in the Input Data FIFO.
 *
 * @param     data: new data of the message to be processed.
 *
 * @retval    None
 */
void HASH_WritesInputData(uint32_t data)
{
    HASH->INDATA_B.INDATA = data;
}

/*!
 * @brief     Read the number of words already pushed into the IN FIFO.
 *
 * @param     None
 *
 * @retval    None
 */
uint8_t HASH_ReadInFIFOWordsNbr(void)
{
    return (HASH->CTRL_B.WNUM);
}

/*!
 * @brief     Read the provides message digest.
 *
 * @param     messageDigest: pointer to a HASH_Config_T structure.
 *
 * @retval    None
 */
void HASH_ReadDigest(HASH_MessageDigest_T *messageDigest)
{
    /* Read the data field */
    messageDigest->Data[0] = HASH->DIG[0];
    messageDigest->Data[1] = HASH->DIG[1];
    messageDigest->Data[2] = HASH->DIG[2];
    messageDigest->Data[3] = HASH->DIG[3];
    messageDigest->Data[4] = HASH->DIG[4];
}

/*!
 * @brief     Start the Digest calculation.
 *
 * @param     None
 *
 * @retval    None
 */
void HASH_StartDigest(void)
{
    HASH->START_B.DIGCAL = SET;
}

/*!
 * @brief     Read the Hash peripheral Context.
 *
 * @param     contextRead: pointer to a HASH_Context_T structure that contains
 *            the repository for current context.
 *
 * @retval    None
 */
void HASH_ReadContext(HASH_Context_T *contextRead)
{
    uint8_t i = 0;

    contextRead->HASH_INT = HASH->INT;
    contextRead->HASH_START = HASH->START;
    contextRead->HASH_CTRL  = HASH->CTRL;

    for (i = 0; i <= 50; i++)
    {
        contextRead->HASH_CTSWAP[i] = HASH->CTSWAP[i];
    }
}

/*!
 * @brief     Write the Hash peripheral Context.
 *
 * @param     contextWrite: pointer to a HASH_Context_T structure that contains
 *            the repository for current context.
 *
 * @retval    None
 */
void HASH_WriteContext(HASH_Context_T *contextWrite)
{
    uint8_t i = 0;

    HASH->INT = contextWrite->HASH_INT;
    HASH->START = contextWrite->HASH_START;
    HASH->CTRL = contextWrite->HASH_CTRL;

    HASH->CTRL_B.INITCAL = SET;

    for (i = 0; i <= 50; i++)
    {
        HASH->CTSWAP[i] = contextWrite->HASH_CTSWAP[i];
    }
}

/*!
 * @brief     Enables the HASH DMA interface.
 *
 * @param     None
 *
 * @retval    None
 */
void HASH_EnableDMA(void)
{
    HASH->CTRL_B.DMAEN = SET;
}

/*!
 * @brief     Disabled the HASH DMA interface.
 *
 * @param     None
 *
 * @retval    None
 */
void HASH_DisableDMA(void)
{
    HASH->CTRL_B.DMAEN = RESET;
}

/*!
 * @brief     Enables the specified HASH interrupts.
 *
 * @param     interrupt: Select the ADC interrupt sources
 *                       This parameter can be any combination of the following values:
 *                       @arg HASH_INT_INDATAINT: Input Data interrupt mask
 *                       @arg HASH_INT_DCALCINT: Digest calculation completion Data interrupt mask
 *
 * @retval    None
 */
void HASH_EnableInterrupt(uint32_t interrupt)
{
    HASH->INT |= interrupt;
}

/*!
 * @brief     Disables the specified HASH interrupts.
 *
 * @param     interrupt: Select the ADC interrupt sources
 *                       This parameter can be any combination of the following values:
 *                       @arg HASH_INT_INDATAINT: Input Data interrupt mask
 *                       @arg HASH_INT_DCALCINT: Digest calculation completion Data interrupt mask
 *
 * @retval    None
 */
void HASH_DisableInterrupt(uint32_t interrupt)
{
    HASH->INT &= (uint32_t)~interrupt;
}

/*!
 * @brief     Reads the pending HASH flag
 *
 * @param     flag: Select the flag to check
 *                  This parameter can be one of the following values:
 *             @arg HASH_FLAG_INDATAINT: Data input interrupt status flag
 *             @arg HASH_FLAG_DCALCINT: Digest calculation completion interrupt status flag
 *             @arg HASH_FLAG_DMA: DMAS Status flag
 *             @arg HASH_FLAG_BUSY: Busy flag
 *             @arg HASH_FLAG_DINNEMPT: Data Input register (DIN) not empty status flag
 *
 * @retval    SET or RESET
 */
uint8_t HASH_ReadFlagStatus(HASH_FLAG_T flag)
{
    uint32_t reg = 0;

    if (flag == HASH_FLAG_DINNEMPT)
    {
        reg = HASH->CTRL;
    }
    else
    {
        reg = HASH->STS;
    }

    return (reg & flag) ? SET : RESET;
}

/*!
 * @brief     Clears the pending HASH flag
 *
 * @param     flag: Select the flag to check
 *                  This parameter can be one of the following values:
 *             @arg HASH_FLAG_INDATAINT: Data input interrupt status flag
 *             @arg HASH_FLAG_DCALCINT: Digest calculation completion interrupt status flag
 *
 * @retval    None
 */
void HASH_ClearStatusFlag(HASH_FLAG_T flag)
{
    if (flag == HASH_FLAG_INDATAINT)
    {
        HASH->STS_B.INDATAINT = BIT_RESET;
    }
    else if (flag == HASH_FLAG_DCALCINT)
    {
        HASH->STS_B.DCALCINT = BIT_RESET;
    }
}

/*!
 * @brief     Reads the specified HASH Interrupt flag.
 *
 * @param     flag: Select the ADC interrupt source.
 *                  This parameter can be one of the following values:
 *             @arg HASH_INT_FLAG_INDATA: Input Data interrupt
 *             @arg HASH_INT_FLAG_DCALC: Digest Calculation Completion Interrupt
 *
 * @retval    SET or RESET
 */
uint8_t HASH_ReadIntFlag(HASH_INT_FLAG_T flag)
{
    uint32_t intStatus = 0, reg = 0;

    intStatus = HASH->INT;
    reg = HASH->STS;

    return (intStatus & (reg & flag)) ? SET : RESET;
}

/*!
 * @brief     Clears the pending HASH flag
 *
 * @param     flag: Select the flag to check
 *                  This parameter can be one of the following values:
 *             @arg HASH_INT_FLAG_INDATA: Input Data interrupt
 *             @arg HASH_INT_FLAG_DCALC: Digest Calculation Completion Interrupt
 *
 * @retval    None
 */
void HASH_ClearIntFlag(HASH_INT_FLAG_T flag)
{
    if (flag == HASH_INT_FLAG_INDATA)
    {
        HASH->STS_B.INDATAINT = BIT_RESET;
    }
    else if (flag == HASH_INT_FLAG_DCALC)
    {
        HASH->STS_B.DCALCINT = BIT_RESET;
    }
}

/*!
 * @brief     Waits for Compute data
 *
 * @param      timeOut: Waits for Compute time
 *
 * @retval    0: No block is currently being compute
 *            1: The hash core is compute a block of data
 *
 */
uint8_t HASH_WaitForCompute(uint32_t timeOut)
{
    __IO uint8_t flag = SET;
    uint32_t time = timeOut;

    while ((flag == SET) && (time > 0))
    {
        flag = HASH_ReadFlagStatus(HASH_FLAG_BUSY);
        time --;
    }

    if ((flag == RESET) && (time > 0))
    {
        return 0;
    }

    return 1;
}

/**@} end of group HASH_Functions */
/**@} end of group HASH_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
