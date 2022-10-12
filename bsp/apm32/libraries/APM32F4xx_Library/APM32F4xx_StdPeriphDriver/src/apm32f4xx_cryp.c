/*!
 * @file        apm32f4xx_cryp.c
 *
 * @brief       This file provides all the CRYP firmware functions
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

#include "apm32f4xx_cryp.h"
#include "apm32f4xx_rcm.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @defgroup CRYP_Driver
  * @brief CRYP driver modules
  @{
*/

/** @defgroup CRYP_Functions
  @{
*/

/*!
 * @brief     Reset CRYP
 *
 * @param     None
 *
 * @retval    None
 */
void CRYP_Reset(void)
{
    RCM_EnableAHB2PeriphReset(RCM_AHB2_PERIPH_CRYP);
    RCM_DisableAHB2PeriphReset(RCM_AHB2_PERIPH_CRYP);
}

/*!
 * @brief     Configure CRYP
 *
 * @param     crypConfig: pointer to a CRYP_Config_T structure
 *
 * @retval    None
 */
void CRYP_Config(CRYP_Config_T *crypConfig)
{
    CRYP->CTRL_B.ALGODIRSEL = crypConfig->algoDir;
    CRYP->CTRL_B.ALGOMSEL   = crypConfig->algoMode;
    CRYP->CTRL_B.DTSEL      = crypConfig->dataType;

    /* select Key size (only AES algorithm)*/
    if (crypConfig->algoMode >= CRYP_ALGOMODE_AES_ECB)
    {
        CRYP->CTRL_B.KSIZESEL = crypConfig->keySize;
    }
}

/*!
 * @brief     Default the CRYP_ConfigStructInit member value.
 *
 * @param     crcyConfig: pointer to a CRYP_Config_T structure
 *
 * @retval    None
 */
void CRYP_ConfigStructInit(CRYP_Config_T *crypConfig)
{
    crypConfig->algoDir  = CRYP_ALGODIR_ENCRYPT;
    crypConfig->algoMode = CRYP_ALGOMODE_TDES_ECB;
    crypConfig->dataType = CRYP_DATATYPE_32B;
    crypConfig->keySize  = CRYP_KEYSIZE_128B;
}

/*!
 * @brief     Configure CRYP Keys
 *
 * @param     keyConfig: pointer to a CRYP_KeyConfig_T structure.
 *
 * @retval    None
 */
void CRYP_ConfigKey(CRYP_KeyConfig_T *keyConfig)
{
    /* Key Initialisation */
    CRYP->K0L = keyConfig->key0Left;
    CRYP->K0R = keyConfig->key0Right;
    CRYP->K1L = keyConfig->key1Left;
    CRYP->K1R = keyConfig->key1Right;
    CRYP->K2L = keyConfig->key2Left;
    CRYP->K2R = keyConfig->key2Right;
    CRYP->K3L = keyConfig->key3Left;
    CRYP->K3R = keyConfig->key3Right;
}

/*!
 * @brief     Default the CRYP_KeyConfigStructInit member value.
 *
 * @param     keyConfig: pointer to a CRYP_KeyConfig_T structure.
 *
 * @retval    None
 */
void CRYP_ConfigKeyStructInit(CRYP_KeyConfig_T *keyConfig)
{
    keyConfig->key0Left  = 0;
    keyConfig->key0Right = 0;
    keyConfig->key1Left  = 0;
    keyConfig->key1Right = 0;
    keyConfig->key2Left  = 0;
    keyConfig->key2Right = 0;
    keyConfig->key3Left  = 0;
    keyConfig->key3Right = 0;
}

/*!
 * @brief     Configure CRYP Initialization Vectors(IV)
 *
 * @param     IVConfig: pointer to a CRYP_IVConfig_T structure.
 *
 * @retval    None
 */
void CRYP_ConfigIV(CRYP_IVConfig_T *IVConfig)
{
    CRYP->IV0L = IVConfig->IV0Left;
    CRYP->IV0R = IVConfig->IV0Right;
    CRYP->IV1L = IVConfig->IV1Left;
    CRYP->IV1R = IVConfig->IV1Right;
}

/*!
 * @brief     Default the CRYP_ConfigIVStructInit member value.
 *
 * @param     keyConfig: pointer to a CRYP_IVConfig_T structure.
 *
 * @retval    None
 */
void CRYP_ConfigIVStructInit(CRYP_IVConfig_T *IVConfig)
{
    IVConfig->IV0Left  = 0;
    IVConfig->IV0Right = 0;
    IVConfig->IV1Left  = 0;
    IVConfig->IV1Right = 0;
}

/*!
 * @brief     Flushes the IN and OUT FIFOs
 *
 * @param     None
 *
 * @retval    None
 *
 * @note      The FIFOs must be flushed only when BUSY flag is reset.
 */
void CRYP_FlushFIFO(void)
{
    CRYP->CTRL_B.FFLUSH = SET;
}

/*!
 * @brief     Enables the CRYP peripheral.
 *
 * @param     None
 *
 * @retval    None
 */
void CRYP_Enable(void)
{
    CRYP->CTRL_B.CRYPEN = SET;
}
/*!
 * @brief     Disable the CRYP peripheral.
 *
 * @param     None
 *
 * @retval    None
 */
void CRYP_Disable(void)
{
    CRYP->CTRL_B.CRYPEN = RESET;
}

/*!
 * @brief     Writes data in the Data Input register.
 *
 * @param     Data: data to write in Data Input register
 *
 * @retval    None
 *
 * @note      After the DATAIN register has been read once or several times,
 *            the FIFO must be flushed (using CRYP_FlushFIFO()).
 */
void CRYP_InData(uint32_t Data)
{
    CRYP->DATAIN = Data;
}

/*!
 * @brief     Returns the last data into the output FIFO.
 *
 * @param     None
 *
 * @retval    Last data into the output FIFO.
 */
uint32_t CRYP_OutData(void)
{
    return CRYP->DATAOUT;
}

/*!
 * @brief     Saves the CRYP peripheral Context.
 *
 * @param     context: pointer to a CRYP_Context_T structure.
 *
 * @param     keyConfig: pointer to a CRYP_IVConfig_T structure.
 *
 * @retval    None
 *
 * @note      This function stops DMA transfer before to save the context. After
 *            restoring the context, you have to enable the DMA again (if the DMA
 *            was previously used).
 */
uint32_t CRYP_SaveContext(CRYP_Context_T *context, CRYP_KeyConfig_T *keyConfig)
{
    uint32_t flag = 0;
    uint32_t bitstatus = 0;
    uint32_t timeout = 0;
    uint32_t status = 0;

    /* Stop DMA transfers on the IN FIFO */
    CRYP->DMACTRL_B.INEN = RESET;

    if (CRYP->CTRL_B.ALGOMSEL <= 0x01)
    {
        flag =  CRYP_FLAG_IFEMPT | CRYP_FLAG_BUSY ;
    }
    else /* AES or DES */
    {
        flag =  CRYP_FLAG_IFEMPT | CRYP_FLAG_BUSY | CRYP_FLAG_OFEMPT;
    }

    do
    {
        bitstatus = CRYP->STS & flag;
        timeout++;
    }
    while ((timeout != 0xFFFF) && (bitstatus != CRYP_FLAG_IFEMPT));

    if ((CRYP->STS & flag) != CRYP_FLAG_IFEMPT)
    {
        status = ERROR;
    }
    else
    {
        /* Stop DMA transfers on the OUT FIFO  */
        CRYP->DMACTRL_B.OUTEN = BIT_RESET;
        CRYP->CTRL_B.CRYPEN = BIT_RESET;

        /* Save the current configuration (bits [9:2] in the CRYP_CTRL register) */
        context->curCTRL  = CRYP->CTRL & 0xFC;

        /* Save the initialization vectors */
        context->IV0L = CRYP->IV0L;
        context->IV0R = CRYP->IV0R;
        context->IV1L = CRYP->IV1L;
        context->IV1R = CRYP->IV1R;

        /* Save the key value */
        context->K0L = keyConfig->key0Left;
        context->K0R = keyConfig->key0Right;
        context->K1L = keyConfig->key1Left;
        context->K1R = keyConfig->key1Right;
        context->K2L = keyConfig->key2Left;
        context->K2R = keyConfig->key2Right;
        context->K3L = keyConfig->key3Left;
        context->K3R = keyConfig->key3Right;

        status = SUCCESS;
    }

    return status;
}

/*!
 * @brief     Restores the CRYP peripheral Context.
 *
 * @param     context: pointer to a CRYP_Context_T structure
 *
 * @retval    None
 *
 * @note      Since the DMA transfer is stopped in CRYP_SaveContext() function,
 *            after restoring the context, you have to enable the DMA again (if the
 *            DMA was previously used).
 */
void CRYP_RestoreContext(CRYP_Context_T *context)
{
    /* Restore The CTRL value */
    CRYP->CTRL = context->curCTRL;

    /* Restore The key value */
    CRYP->K0L = context->K0L;
    CRYP->K0R = context->K0R;
    CRYP->K1L = context->K1L;
    CRYP->K1R = context->K1R;
    CRYP->K2L = context->K2L;
    CRYP->K2R = context->K2R;
    CRYP->K3L = context->K3L;
    CRYP->K3R = context->K3R;

    /* Restore the IV */
    CRYP->IV0L = context->IV0L;
    CRYP->IV0R = context->IV0R;
    CRYP->IV1L = context->IV1L;
    CRYP->IV1R = context->IV1R;

    /* Enable the cryptographic processor */
    CRYP->CTRL_B.CRYPEN = BIT_SET;
}
/*!
 * @brief     Enable the CRYP DMA.
 *
 * @param     dmaReq: CRYP DMA transfer request
 *              This parameter can be one of the following values:
 *              @arg CRYP_DMAREQ_DATAIN     : DMA Input Enable
 *              @arg CRYP_DMAREQ_DATAOUT    : DMA Output Enable
 *
 * @retval    None
 */
void CRYP_EnableDMA(CRYP_DMAREQ_T dmaReq)
{
    if (dmaReq == CRYP_DMAREQ_DATAIN)
    {
        CRYP->DMACTRL_B.INEN = SET;
    }
    else if (dmaReq == CRYP_DMAREQ_DATAOUT)
    {
        CRYP->DMACTRL_B.OUTEN = SET;
    }
}

/*!
 * @brief     Disable  the CRYP DMA.
 *
 * @param     dmaReq: CRYP DMA transfer request
 *              This parameter can be one of the following values:
 *              @arg CRYP_DMAREQ_DATAIN     : DMA Input Enable
 *              @arg CRYP_DMAREQ_DATAOUT    : DMA Output Enable
 *
 * @retval    None
 */
void CRYP_DisableDMA(CRYP_DMAREQ_T dmaReq)
{
    if (dmaReq == CRYP_DMAREQ_DATAIN)
    {
        CRYP->DMACTRL_B.INEN = RESET;
    }
    else if (dmaReq == CRYP_DMAREQ_DATAOUT)
    {
        CRYP->DMACTRL_B.OUTEN = RESET;
    }
}

/*!
 * @brief     Enable the CRYP Interrupt.
 *
 * @param     interrupt: specifies the CRYP interrupt sources
 *            This parameter can be any combination of the following values:
 *              @arg CRYP_INT_IN:  Input FIFO interrupt
 *              @arg CRYP_INT_OUT: Output FIFO interrupt
 *
 * @retval    None
 */
void CRYP_EnableInterrupt(uint8_t interrupt)
{
    CRYP->INTMASK |= interrupt;
}

/*!
 * @brief     Disable the CRYP Interrupt.
 *
 * @param     interrupt: specifies the CRYP interrupt sources
 *            This parameter can be any combination of the following values:
 *              @arg CRYP_INT_IN:  Input FIFO interrupt
 *              @arg CRYP_INT_OUT: Output FIFO interrupt
 *
 * @retval    None
 */
void CRYP_DisableInterrupt(uint8_t interrupt)
{
    CRYP->INTMASK &= ~interrupt;
}

/*!
 * @brief     Read the CRYP Interrupt flag.
 *
 * @param     flag: specifies the CRYP flag
 *            This parameter can be one of the following values:
 *              @arg CRYP_INT_IN:  Input FIFO interrupt
 *              @arg CRYP_INT_OUT: Output FIFO interrupt
 *
 * @retval    SET or RESET
 */

uint8_t CRYP_ReadIntFlag(CRYP_INT_T flag)
{
    return (CRYP->INTMASK & flag) ? SET : RESET;
}

/*!
 * @brief     Reads the CRYP flag.
 *
 * @param     flag: specifies the flag to check.
 *            This parameter can be one of the following values:
 *              @arg CRYP_FLAG_IFEMPT:  Input FIFO Empty flag.
 *              @arg CRYP_FLAG_IFFULL:  Input FIFO Not Full flag.
 *              @arg CRYP_FLAG_OFEMPT:  Output FIFO Not Empty flag
 *              @arg CRYP_FLAG_OFFULL:  Output FIFO Full flag.
 *              @arg CRYP_FLAG_BUSY:    Busy flag.
 *              @arg CRYP_FLAG_INISTS:  Input FIFO raw interrupt flag.
 *              @arg CRYP_FLAG_OUTISTS: Output FIFO raw interrupt flag.
 *
 * @retval    SET or RESET.
 */
uint8_t CRYP_ReadStatusFlag(CRYP_FLAG_T flag)
{
    if (flag & 0x20)
    {
        return (CRYP->INTSTS & flag) ? SET : RESET;
    }
    else
    {
        return (CRYP->STS & flag) ? SET : RESET;
    }
}

/*!
 * @brief     Returns the CRYP peripheral Cmd
 *
 * @param     None
 *
 * @retval    ENABLE or DISABLE
 */
uint8_t CRYP_ReadCmdStatus(void)
{
    return (CRYP->CTRL_B.CRYPEN);
}

/**@} end of group CRYP_Functions */
/**@} end of group CRYP_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
