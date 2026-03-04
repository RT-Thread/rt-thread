/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_fdcan.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "n32h76x_78x_fdcan.h"
#include "n32h76x_78x_rcc.h"

static FDCAN_MsgRamType *pMsgRam[8];

/* Get bytes of data according to the DLC value */
static const uint8_t DLCtoBytes[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64};

/* Private function */
static ErrorStatus FDCAN_InitMsgRam(FDCAN_Module* FDCANx, FDCAN_InitType *FDCAN_InitParam);
static void FDCAN_CopyMsgToRAM(FDCAN_Module *FDCANx, FDCAN_TxHeaderType *pTxHeader, uint8_t *pTxData, uint32_t BufferIndex);
static uint8_t FDCAN_Get_Index(FDCAN_Module *FDCANx);

/**
 *\*\name   FDCAN_DeInit.
 *\*\fun    Reset the FDCANx peripheral registers to their default reset values.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return none
 */
void FDCAN_DeInit(FDCAN_Module* FDCANx)
{
    if (FDCANx == FDCAN1)
    {
        RCC_EnableAPB1PeriphReset5(RCC_APB1_PERIPHRST_FDCAN1);
    }
    else if (FDCANx == FDCAN2)
    {
        RCC_EnableAPB1PeriphReset5(RCC_APB1_PERIPHRST_FDCAN2);
    }
    else if (FDCANx == FDCAN3)
    {
        RCC_EnableAPB2PeriphReset4(RCC_APB2_PERIPHRST_FDCAN3);
    }
    else if (FDCANx == FDCAN4)
    {
        RCC_EnableAPB2PeriphReset4(RCC_APB2_PERIPHRST_FDCAN4);
    }
    else if (FDCANx == FDCAN5)
    {
        RCC_EnableAPB1PeriphReset5(RCC_APB1_PERIPHRST_FDCAN5);
    }
    else if (FDCANx == FDCAN6)
    {
        RCC_EnableAPB1PeriphReset5(RCC_APB1_PERIPHRST_FDCAN6);
    }
    else if (FDCANx == FDCAN7)
    {
        RCC_EnableAPB2PeriphReset4(RCC_APB2_PERIPHRST_FDCAN7);
    }
    else if (FDCANx == FDCAN8)
    {
        RCC_EnableAPB2PeriphReset4(RCC_APB2_PERIPHRST_FDCAN8);
    }
    else
    {
        /* no process*/
    }
}

/**
 *\*\name   FDCAN_Init.
 *\*\fun    Initializes the FDCAN peripheral according to the specified
 *\*\       parameters in the FDCAN_InitParam..
 *\*\param  FDCANx pointer to specified FDCAN,must be one of the following value:
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  FDCAN_InitParam: pointer to a FDCAN_InitType structure.
 *\*\          - FrameFormat:
 *\*\               - FDCAN_FRAME_CLASSIC
 *\*\               - FDCAN_FRAME_FD_NO_BRS
 *\*\               - FDCAN_FRAME_FD_BRS
 *\*\          - Mode:
 *\*\               - FDCAN_MODE_NORMAL
 *\*\               - FDCAN_MODE_RESTRICTED_OPERATION
 *\*\               - FDCAN_MODE_BUS_MONITORING
 *\*\               - FDCAN_MODE_INTERNAL_LOOPBACK
 *\*\               - FDCAN_MODE_EXTERNAL_LOOPBACK
 *\*\          - Prescaler: Must be a value between 1 and 512.
 *\*\          - SyncJumpWidth: Must be a value between 1 and 128.
 *\*\          - TimeSeg1: Must be a value between 2 and 256.
 *\*\          - TimeSeg2: Must be a value between 2 and 128.
 *\*\          - DataPrescaler: Must be a value between 1 and 32.
 *\*\          - DataSyncJumpWidth: Must be a value between 1 and 16.
 *\*\          - DataTimeSeg1: Must be a value between 1 and 32.
 *\*\          - DataTimeSeg2: Must be a value between 1 and 16.
 *\*\          - MsgRamStrAddr:
 *\*\               - FDCAN_START_ADDRESS_SRAM5BANK1 , 0x30050000 as FDCAN base address.
 *\*\               - FDCAN_START_ADDRESS_SRAM5BANK2 , 0x30054000 as FDCAN base address.
 *\*\          - MsgRamOffset: Must be a value between 0 and 0x1000.
 *\*\          - StdFilterSize: Must be a value between 0 and 128.
 *\*\          - ExtFilterSize: Must be a value between 0 and 64.
 *\*\          - RxFifo0Size: Must be a value between 0 and 64.
 *\*\          - RxFifo1Size: Must be a value between 0 and 64.
 *\*\          - RxBufferSize: Must be a value between 0 and 64.
 *\*\          - TxEventSize: Must be a value between 0 and 32.
 *\*\          - TxBufferSize: Must be a value between 0 and 32.
 *\*\          - RxFifo0DataSize:
 *\*\               - FDCAN_DATA_BYTES_8
 *\*\               - FDCAN_DATA_BYTES_12
 *\*\               - FDCAN_DATA_BYTES_16
 *\*\               - FDCAN_DATA_BYTES_20
 *\*\               - FDCAN_DATA_BYTES_24
 *\*\               - FDCAN_DATA_BYTES_32
 *\*\               - FDCAN_DATA_BYTES_48
 *\*\               - FDCAN_DATA_BYTES_64
 *\*\          - RxFifo1DataSize:
 *\*\               - FDCAN_DATA_BYTES_8
 *\*\               - FDCAN_DATA_BYTES_12
 *\*\               - FDCAN_DATA_BYTES_16
 *\*\               - FDCAN_DATA_BYTES_20
 *\*\               - FDCAN_DATA_BYTES_24
 *\*\               - FDCAN_DATA_BYTES_32
 *\*\               - FDCAN_DATA_BYTES_48
 *\*\               - FDCAN_DATA_BYTES_64
 *\*\          - RxBufferDataSize:
 *\*\               - FDCAN_DATA_BYTES_8
 *\*\               - FDCAN_DATA_BYTES_12
 *\*\               - FDCAN_DATA_BYTES_16
 *\*\               - FDCAN_DATA_BYTES_20
 *\*\               - FDCAN_DATA_BYTES_24
 *\*\               - FDCAN_DATA_BYTES_32
 *\*\               - FDCAN_DATA_BYTES_48
 *\*\               - FDCAN_DATA_BYTES_64
 *\*\          - TxBufferDataSize:
 *\*\               - FDCAN_DATA_BYTES_8
 *\*\               - FDCAN_DATA_BYTES_12
 *\*\               - FDCAN_DATA_BYTES_16
 *\*\               - FDCAN_DATA_BYTES_20
 *\*\               - FDCAN_DATA_BYTES_24
 *\*\               - FDCAN_DATA_BYTES_32
 *\*\               - FDCAN_DATA_BYTES_48
 *\*\               - FDCAN_DATA_BYTES_64
 *\*\          - TxFifoQueueMode:
 *\*\               - FDCAN_TX_FIFO_MODE
 *\*\               - FDCAN_TX_QUEUE_MODE
 *\*\          - TxFifoQueueSize: Must be a value between 0 and 32.
 *\*\          - AutoRetransmission:
 *\*\               - ENABLE
 *\*\               - DISABLE
 *\*\          - TransmitPause:
 *\*\               - ENABLE
 *\*\               - DISABLE
 *\*\          - ProtocolException:
 *\*\               - ENABLE
 *\*\               - DISABLE
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_Init(FDCAN_Module* FDCANx, FDCAN_InitType *FDCAN_InitParam)
{
    uint32_t timeout;
    uint32_t tempReg;
    const uint8_t SizeToReg[] = {0, 0, 0, 0, 0, 1, 2, 3, 4, 0, 5, 0, 0, 0, 6, 0, 0, 0, 7};

    /* Exit from Sleep mode */
    FDCANx->CCCR &= ~FDCAN_CCCR_CSR;

    /* Check Sleep mode acknowledge */
    timeout = 0;

    while ((FDCANx->CCCR & FDCAN_CCCR_CSA) == FDCAN_CCCR_CSA)
    {
        if (timeout > FDCAN_TIMEOUT_VALUE)
        {
            return ERROR;
        }

        timeout++;
    }

    /* Request initialisation */
    FDCANx->CCCR |= FDCAN_CCCR_INIT;

    /* Wait until the INIT bit into CCCR register is set */
    timeout = 0;

    while ((FDCANx->CCCR & FDCAN_CCCR_INIT) == 0U)
    {
        if (timeout > FDCAN_TIMEOUT_VALUE)
        {
            return ERROR;
        }

        timeout++;
    }

    /* Enable configuration change */
    FDCANx->CCCR |= FDCAN_CCCR_CCE;

    /* Configuration the CCCR register */
    tempReg = FDCANx->CCCR;

    /* Set the no automatic retransmission */
    if (FDCAN_InitParam->AutoRetransmission == ENABLE)
    {
        tempReg &= ~FDCAN_CCCR_DAR;
    }
    else
    {
        tempReg |= FDCAN_CCCR_DAR;
    }

    /* Set the transmit pause feature */
    if (FDCAN_InitParam->TransmitPause == ENABLE)
    {
        tempReg |= FDCAN_CCCR_TXP;
    }
    else
    {
        tempReg &= ~FDCAN_CCCR_TXP;
    }

    /* Set the Protocol Exception Handling */
    if (FDCAN_InitParam->ProtocolException == ENABLE)
    {
        tempReg &= ~FDCAN_CCCR_PXHD;
    }
    else
    {
        tempReg |= FDCAN_CCCR_PXHD;
    }

    /* Set FDCAN Frame Format */
    tempReg &= ~(FDCAN_CCCR_BRSE | FDCAN_CCCR_FDOE);
    tempReg |= FDCAN_InitParam->FrameFormat;

    /* Set FDCAN Operating Mode:
                  | Normal | Restricted |    Bus     | Internal | External
                  |        | Operation  | Monitoring | LoopBack | LoopBack
        CCCR.TEST |   0    |     0      |     0      |    1     |    1
        CCCR.MON  |   0    |     0      |     1      |    1     |    0
        TEST.LBCK |   0    |     0      |     0      |    1     |    1
        CCCR.ASM  |   0    |     1      |     0      |    0     |    0
    */
    tempReg &= ~(FDCAN_CCCR_TEST | FDCAN_CCCR_MON | FDCAN_CCCR_ASM);
    tempReg |= FDCAN_InitParam->Mode;
    FDCANx->CCCR = tempReg;

    if ((FDCAN_InitParam->Mode & FDCAN_CCCR_TEST) == FDCAN_CCCR_TEST)
    {
        FDCANx->TEST |= FDCAN_TEST_LBCK;
    }
    else
    {
        FDCANx->TEST &= ~FDCAN_TEST_LBCK;
    }

    /* Set the nominal bit timing register */
    FDCANx->NBTP = ( ((FDCAN_InitParam->SyncJumpWidth - 1UL) << FDCAN_NBTP_NSJW_OFFSET)   \
                     |  ((FDCAN_InitParam->TimeSeg1 - 1UL)      << FDCAN_NBTP_NTSEG1_OFFSET) \
                     |  ((FDCAN_InitParam->TimeSeg2 - 1UL)      << FDCAN_NBTP_NTSEG2_OFFSET) \
                     |  ((FDCAN_InitParam->Prescaler - 1UL)     << FDCAN_NBTP_NBRP_OFFSET)   );

    /* If FD operation with BRS is selected, set the data bit timing register */
    if (FDCAN_InitParam->FrameFormat == FDCAN_FRAME_FD_BRS)
    {
        FDCANx->DBTP = ( ((FDCAN_InitParam->DataSyncJumpWidth - 1UL) << FDCAN_DBTP_DSJW_OFFSET)     \
                         |   ((FDCAN_InitParam->DataTimeSeg1 - 1UL)      << FDCAN_DBTP_DTSEG1_OFFSET)   \
                         |   ((FDCAN_InitParam->DataTimeSeg2 - 1UL)      << FDCAN_DBTP_DTSEG2_OFFSET)   \
                         |   ((FDCAN_InitParam->DataPrescaler - 1UL)     << FDCAN_DBTP_DBRP_OFFSET)     );
    }

    /* Select between Tx FIFO and Tx Queue operation modes */
    tempReg  = FDCANx->TXBC & (~FDCAN_TXBC_TFQM);

    if (FDCAN_InitParam->TxFifoQueueSize > 0UL)
    {
        tempReg |= FDCAN_InitParam->TxFifoQueueMode;
    }

    FDCANx->TXBC = tempReg;

    /* Configure Tx element size */
    if ((FDCAN_InitParam->TxBufferSize + FDCAN_InitParam->TxFifoQueueSize) > 0UL)
    {
        FDCANx->TXESC = (uint32_t)(SizeToReg[FDCAN_InitParam->TxBufferDataSize]);
    }
    else
    {
        FDCANx->TXESC = 0;
    }

    tempReg  = 0;

    /* Configure Rx FIFO 0 element size */
    if (FDCAN_InitParam->RxFifo0Size > 0U)
    {
        tempReg |= (uint32_t)(SizeToReg[FDCAN_InitParam->RxFifo0DataSize]) << FDCAN_RXESC_F0DS_OFFSET;
    }

    /* Configure Rx FIFO 1 element size */
    if (FDCAN_InitParam->RxFifo1Size > 0U)
    {
        tempReg |= (uint32_t)(SizeToReg[FDCAN_InitParam->RxFifo1DataSize]) << FDCAN_RXESC_F1DS_OFFSET;
    }

    /* Configure Rx buffer element size */
    if (FDCAN_InitParam->RxBufferSize > 0U)
    {
        tempReg |= (uint32_t)(SizeToReg[FDCAN_InitParam->RxBufferDataSize]) << FDCAN_RXESC_RBDS_OFFSET;
    }

    FDCANx->RXESC = tempReg;

    /* By default operation mode is set to Event-driven communication.
       If Time-triggered communication is needed, user should call the
       FDCAN_TT_Init function just after the FDCAN_Init */
    if (FDCAN_Get_Index(FDCANx) <= 4)
    {
        FDCANx->TTOCF &= ~FDCAN_TTOCF_OM;
    }

    /* Calculate each RAM block address and Return function status */
    return (FDCAN_InitMsgRam(FDCANx, FDCAN_InitParam));
}

/**
 *\*\name   FDCAN_EnterSleep.
 *\*\fun    Enter sleep mode.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_EnterSleep(FDCAN_Module *FDCANx)
{
    uint32_t timeout;

    /* Request clock stop */
    FDCANx->CCCR |= FDCAN_CCCR_CSR;

    timeout = 0;

    /* Wait until FDCAN is ready for power down */
    while ((FDCANx->CCCR & FDCAN_CCCR_CSA) == 0U)
    {
        if (timeout > FDCAN_TIMEOUT_VALUE)
        {
            return ERROR;
        }

        timeout++;
    }

    /* Return function status */
    return SUCCESS;
}

/**
 *\*\name   FDCAN_ExitSleep.
 *\*\fun    Exit sleep mode
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_ExitSleep(FDCAN_Module *FDCANx)
{
    uint32_t timeout;

    /* Reset clock stop request */
    FDCANx->CCCR &= ~FDCAN_CCCR_CSR;

    timeout = 0;

    /* Wait until FDCAN exits sleep mode */
    while ((FDCANx->CCCR & FDCAN_CCCR_CSA) == FDCAN_CCCR_CSA)
    {
        if (timeout > FDCAN_TIMEOUT_VALUE)
        {
            return ERROR;
        }

        timeout++;
    }

    /* Enter normal operation */
    FDCANx->CCCR &= ~FDCAN_CCCR_INIT;

    timeout = 0;

    /* Wait until FDCAN exits sleep mode */
    while ((FDCANx->CCCR & FDCAN_CCCR_INIT) == FDCAN_CCCR_INIT)
    {
        if (timeout > FDCAN_TIMEOUT_COUNT)
        {
            return ERROR;
        }

        timeout++;
    }

    /* Return function status */
    return SUCCESS;
}

/**
 *\*\name   FDCAN_ConfigFilter.
 *\*\fun    Configure the FDCAN reception filter according to the specified
 *\*\       parameters in the FDCAN_FilterType structure.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param sFilterConfig pointer to an FDCAN_FilterTypeDef structure
 *\*\          - IdType
 *\*\               - FDCAN_STANDARD_ID
 *\*\               - FDCAN_EXTENDED_ID
 *\*\          - FilterIndex
 *\*\               This parameter must be a value between:
 *\*\               - 0 and 127, if IdType is FDCAN_STANDARD_ID
 *\*\               - 0 and 63, if IdType is FDCAN_EXTENDED_ID
 *\*\          - FilterType
 *\*\               - FDCAN_FILTER_RANGE
 *\*\               - FDCAN_FILTER_DUAL
 *\*\               - FDCAN_FILTER_MASK
 *\*\               - FDCAN_FILTER_RANGE_NO_EIDM
 *\*\          - FilterConfig
 *\*\               -FDCAN_FILTER_DISABLE
 *\*\               -FDCAN_FILTER_TO_RXFIFO0
 *\*\               -FDCAN_FILTER_TO_RXFIFO1
 *\*\               -FDCAN_FILTER_REJECT
 *\*\               -FDCAN_FILTER_HP
 *\*\               -FDCAN_FILTER_TO_RXFIFO0_HP
 *\*\               -FDCAN_FILTER_TO_RXFIFO1_HP
 *\*\               -FDCAN_FILTER_TO_RXBUFFER
 *\*\          - FilterID1
 *\*\               This parameter must be a value between:
 *\*\               - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
 *\*\               - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID
 *\*\          - FilterID2
 *\*\               This parameter must be a value between:
 *\*\               - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
 *\*\               - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID
 *\*\               This parameter is ignored if FilterConfig is set to FDCAN_FILTER_TO_RXBUFFER
 *\*\          - RxBufferIndex
 *\*\               This parameter must be a value between 0 and 63.
 *\*\               And it is ignored if FilterConfig is not FDCAN_FILTER_TO_RXBUFFER
 *\*\return none
 */
void FDCAN_ConfigFilter(FDCAN_Module *FDCANx, FDCAN_FilterType *sFilterConfig)
{
    uint32_t *FilterAddress;
    FDCAN_MsgRamType *pMsg;

    pMsg = pMsgRam[FDCAN_Get_Index(FDCANx)];

    if (sFilterConfig->IdType == FDCAN_STANDARD_ID)
    {
        /* Calculate filter address */
        FilterAddress = (uint32_t *)(pMsg->StdFilterStrAddr + (sFilterConfig->FilterIndex * 4UL));

        /* Build filter element */
        if (sFilterConfig->FilterConfig == FDCAN_FILTER_TO_RXBUFFER)
        {
            *FilterAddress = (  (sFilterConfig->FilterType)       |
                                (sFilterConfig->FilterConfig << FDCAN_ELEMENT_SFEC_OFFSET) |
                                (sFilterConfig->FilterID1 << FDCAN_ELEMENT_ID1_OFFSET)       |
                                sFilterConfig->RxBufferIndex   );
        }
        else
        {
            *FilterAddress = (  (sFilterConfig->FilterType )   |
                                (sFilterConfig->FilterConfig << FDCAN_ELEMENT_SFEC_OFFSET) |
                                (sFilterConfig->FilterID1 << FDCAN_ELEMENT_ID1_OFFSET)    |
                                sFilterConfig->FilterID2    );
        }
    }
    else /* sFilterConfig->IdType == FDCAN_EXTENDED_ID */
    {
        /* Calculate filter address */
        FilterAddress = (uint32_t *)(pMsg->ExtFilterStrAddr + (sFilterConfig->FilterIndex * FDCAN_EXT_FILTER_WORDS * 4UL));

        /* Build first word of filter element */
        *FilterAddress = ((sFilterConfig->FilterConfig << FDCAN_ELEMENT_EFEC_OFFSET) | sFilterConfig->FilterID1);

        /* Increment FilterAddress pointer to second word of filter element */
        FilterAddress++;

        /* Build second word of filter element */
        if (sFilterConfig->FilterConfig == FDCAN_FILTER_TO_RXBUFFER)
        {
            *FilterAddress = (sFilterConfig->FilterType | sFilterConfig->RxBufferIndex);
        }
        else
        {
            *FilterAddress = (sFilterConfig->FilterType | sFilterConfig->FilterID2);
        }
    }
}

/**
 *\*\name   FDCAN_ConfigGlobalFilter.
 *\*\fun    Configure the FDCAN global filter.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  NonMatchingStd :
 *\*\          - FDCAN_ACCEPT_STD_IN_RX_FIFO0
 *\*\          - FDCAN_ACCEPT_STD_IN_RX_FIFO1
 *\*\          - FDCAN_REJECT_STD
 *\*\param  NonMatchingExt :
 *\*\          - FDCAN_ACCEPT_EXT_IN_RX_FIFO0
 *\*\          - FDCAN_ACCEPT_EXT_IN_RX_FIFO1
 *\*\          - FDCAN_REJECT_EXT
 *\*\param  RejectRemoteStd :
 *\*\          - FDCAN_FILTER_STD_REMOTE
 *\*\          - FDCAN_REJECT_STD_REMOTE
 *\*\param  RejectRemoteExt :
 *\*\          - FDCAN_FILTER_EXT_REMOTE
 *\*\          - FDCAN_REJECT_EXT_REMOTE
 *\*\return
 */
void FDCAN_ConfigGlobalFilter(FDCAN_Module *FDCANx,
                              uint32_t NonMatchingStd,
                              uint32_t NonMatchingExt,
                              uint32_t RejectRemoteStd,
                              uint32_t RejectRemoteExt)
{
    /* Configure global filter */
    FDCANx->GFC =  NonMatchingStd | NonMatchingExt | RejectRemoteStd | RejectRemoteExt;
}

/**
 *\*\name   FDCAN_ConfigExtIdMask.
 *\*\fun    CConfigure the extended ID mask.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  Mask :Extended ID Mask.
 *\*\       This parameter must be a number between 0 and 0x1FFFFFFF
 *\*\return none
 */
void FDCAN_ConfigExtIdMask(FDCAN_Module *FDCANx, uint32_t Mask)
{
    FDCANx->XIDAM = Mask;
}

/**
 *\*\name   FDCAN_ConfigRxFifoMode.
 *\*\fun    Configure the Rx FIFO operation mode.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  RxFifo
 *\*\          - FDCAN_RX_FIFO0
 *\*\          - FDCAN_RX_FIFO1
 *\*\param  Mode
 *\*\          - FDCAN_RX_FIFO_BLOCKING
 *\*\          - FDCAN_RX_FIFO_OVERWRITE
 *\*\return none
 */
void FDCAN_ConfigRxFifoMode(FDCAN_Module *FDCANx, uint32_t RxFifo, uint32_t Mode)
{
    __IO uint32_t *pReg;

    if (RxFifo == FDCAN_RX_FIFO0)
    {
        /* Select FIFO 0 Operation Mode */
        pReg = &(FDCANx->RXF0C);
    }
    else /* RxFifo == FDCAN_RX_FIFO1 */
    {
        /* Select FIFO 1 Operation Mode */
        pReg = &(FDCANx->RXF1C);
    }

    if(Mode == FDCAN_RX_FIFO_OVERWRITE)
    {
        *pReg |= FDCAN_RX_FIFO_OVERWRITE;
    }
    else /* Mode == FDCAN_RX_FIFO_BLOCKING */
    {
        *pReg &= ~FDCAN_RX_FIFO_OVERWRITE;
    }
}

/**
 *\*\name   FDCAN_ConfigFifoWatermark.
 *\*\fun    Configure the Tx/RX FIFO watermark.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  FIFO
 *\*\          - FDCAN_RX_FIFO0
 *\*\          - FDCAN_RX_FIFO1
 *\*\          - FDCAN_TX_EVENT_FIFO
 *\*\param  Watermark level for FIFO watermark interrupt.
 *\*\          This parameter must be a number between:
 *\*\          - 0 and 32, if FIFO is FDCAN_TX_EVENT_FIFO
 *\*\          - 0 and 64, if FIFO is FDCAN_RX_FIFO0 or FDCAN_RX_FIFO1
 *\*\return none
 */
void FDCAN_ConfigFifoWatermark(FDCAN_Module *FDCANx, uint32_t FIFO, uint32_t Watermark)
{
    __IO uint32_t *pReg;
    uint32_t tempReg;

    /* Set the level for FIFO watermark interrupt */
    if (FIFO == FDCAN_TX_EVENT_FIFO)
    {
        pReg = &(FDCANx->TXEFC);
        tempReg = *pReg & (~FDCAN_TXEFC_EFWM);
    }
    else if (FIFO == FDCAN_RX_FIFO0)
    {
        pReg = &(FDCANx->RXF0C);
        tempReg = *pReg & (~FDCAN_RXF0C_F0WM);
    }
    else /* FIFO == FDCAN_RX_FIFO1 */
    {
        pReg = &(FDCANx->RXF1C);
        tempReg = *pReg & (~FDCAN_RXF1C_F1WM);
    }

    tempReg |= Watermark << FDCAN_RXFXC_FXWM_OFFSET;
    *pReg = tempReg;
}

/**
 *\*\name   FDCAN_ConfigRamWatchdog.
 *\*\fun    Configure the RAM watchdog.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  Value Start value of the Message RAM Watchdog Counter.
 *\*\          This parameter must be a number between 0x00 and 0xFF
 *\*\return none
 */
void FDCAN_ConfigRamWatchdog(FDCAN_Module *FDCANx, uint32_t Value)
{
    uint32_t tempReg;

    /* Configure the RAM watchdog counter start value */
    tempReg  = FDCANx->RWD & (~FDCAN_RWD_WDC);
    tempReg |= Value;
    FDCANx->RWD = tempReg;
}

/**
 *\*\name   FDCAN_ConfigTSPrescaler.
 *\*\fun    Configure the timestamp counter Prescaler.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  Prescaler
 *\*\          - FDCAN_TIMESTAMP_PRESC_1
 *\*\          - FDCAN_TIMESTAMP_PRESC_2
 *\*\          - FDCAN_TIMESTAMP_PRESC_3
 *\*\          - FDCAN_TIMESTAMP_PRESC_4
 *\*\          - FDCAN_TIMESTAMP_PRESC_5
 *\*\          - FDCAN_TIMESTAMP_PRESC_6
 *\*\          - FDCAN_TIMESTAMP_PRESC_7
 *\*\          - FDCAN_TIMESTAMP_PRESC_8
 *\*\          - FDCAN_TIMESTAMP_PRESC_9
 *\*\          - FDCAN_TIMESTAMP_PRESC_10
 *\*\          - FDCAN_TIMESTAMP_PRESC_11
 *\*\          - FDCAN_TIMESTAMP_PRESC_12
 *\*\          - FDCAN_TIMESTAMP_PRESC_13
 *\*\          - FDCAN_TIMESTAMP_PRESC_14
 *\*\          - FDCAN_TIMESTAMP_PRESC_15
 *\*\          - FDCAN_TIMESTAMP_PRESC_16
 *\*\return none
 */
void FDCAN_ConfigTSPrescaler(FDCAN_Module *FDCANx, uint32_t Prescaler)
{
    uint32_t tempReg;

    tempReg  = FDCANx->TSCC & (~FDCAN_TSCC_TCP);
    tempReg |= Prescaler;
    FDCANx->TSCC = tempReg;
}

/**
 *\*\name   FDCAN_Config_TS.
 *\*\fun    Config the timestamp mode.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  Select
 *\*\          - FDCAN_TIMESTAMP_DISABLE
 *\*\          - FDCAN_TIMESTAMP_INTERNAL
 *\*\          - FDCAN_TIMESTAMP_EXTERNAL
 *\*\return none
 */
void FDCAN_Config_TS(FDCAN_Module *FDCANx, uint32_t Select)
{
    uint32_t tempReg;

    tempReg  = FDCANx->TSCC & (~FDCAN_TSCC_TSS);
    tempReg |= Select;
    FDCANx->TSCC = tempReg;
}

/**
 *\*\name   FDCAN_Get_TS.
 *\*\fun    Get the timestamp counter value.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return Value Timestamp counter value
 */
uint16_t FDCAN_Get_TS(FDCAN_Module *FDCANx)
{
    return (uint16_t)(FDCANx->TSCV);
}

/**
 *\*\name   FDCAN_Reset_TS.
 *\*\fun    Reset the internal timestamp counter to zero.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return none
 */
void FDCAN_Reset_TS(FDCAN_Module *FDCANx)
{
    if ((FDCANx->TSCC & FDCAN_TSCC_TSS) != FDCAN_TIMESTAMP_EXTERNAL)
    {
        /* Reset timestamp counter.
           Actually any write operation to TSCV clears the counter */
        FDCANx->TSCV = 0;
    }
}

/**
 *\*\name   FDCAN_ConfigTimeoutCounter.
 *\*\fun    Configure the timeout counter.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  TimeoutSelect :
 *\*\          - FDCAN_TIMEOUT_CONTINUOUS
 *\*\          - FDCAN_TIMEOUT_TX_EVENT_FIFO
 *\*\          - FDCAN_TIMEOUT_RX_FIFO0
 *\*\          - FDCAN_TIMEOUT_RX_FIFO1
 *\*\param  TimeoutPeriod :Start value of the timeout down-counter.
 *\*\       This parameter must be a number between 0x0000 and 0xFFFF
 *\*\return none
 */
void FDCAN_ConfigTimeoutCounter(FDCAN_Module *FDCANx, uint32_t TimeoutSelect, uint32_t TimeoutPeriod)
{
    uint32_t tempReg;

    tempReg  = FDCANx->TOCC & (~(FDCAN_TOCC_TOS | FDCAN_TOCC_TOP));
    tempReg |= TimeoutSelect;
    tempReg |= TimeoutPeriod << FDCAN_TOCC_TOP_OFFSET;
    FDCANx->TOCC = tempReg;
}

/**
 *\*\name   FDCAN_EnableTimeoutCounter.
 *\*\fun    Enable the timeout counter.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return none
 */
void FDCAN_EnableTimeoutCounter(FDCAN_Module *FDCANx)
{
    /* Enable timeout counter */
    FDCANx->TOCC |= FDCAN_TOCC_ETOC;
}

/**
 *\*\name   FDCAN_DisableTimeoutCounter.
 *\*\fun    Disable the timeout counter.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return none
 */
void FDCAN_DisableTimeoutCounter(FDCAN_Module *FDCANx)
{
    /* Enable timeout counter */
    FDCANx->TOCC &= ~FDCAN_TOCC_ETOC;
}

/**
 *\*\name   FDCAN_GetTimeoutCounter.
 *\*\fun    Get the timeout counter value.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return Timeout counter value
 */
uint16_t FDCAN_GetTimeoutCounter(FDCAN_Module *FDCANx)
{
    return (uint16_t)(FDCANx->TOCV);
}

/**
 *\*\name   FDCAN_ResetTimeoutCounter.
 *\*\fun    Reset the timeout counter to its start value.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return none
 */
void FDCAN_ResetTimeoutCounter(FDCAN_Module *FDCANx)
{
    FDCANx->TOCV = 0;
}

/**
 *\*\name   FDCAN_ConfigTxDelayCompensation.
 *\*\fun    Configure the transmitter delay compensation.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  Offset :Transmitter Delay Compensation Offset.
 *\*\          This parameter must be a number between 0x00 and 0x7F.
 *\*\param  Filter :Transmitter Delay Compensation Filter Window Length.
 *\*\          This parameter must be a number between 0x00 and 0x7F.
 *\*\return none
 */
void FDCAN_ConfigTxDelayCompensation(FDCAN_Module *FDCANx, uint32_t Offset, uint32_t Filter)
{
    uint32_t tempReg;

    tempReg  = FDCANx->TDCR & (~(FDCAN_TDCR_TDCO | FDCAN_TDCR_TDCF));
    tempReg |= Offset << FDCAN_TDCR_TDCO_OFFSET;
    tempReg |= Filter;
    FDCANx->TDCR = tempReg;
}

/**
 *\*\name   FDCAN_EnableTxDelayCompensation.
 *\*\fun    Enable the transmitter delay compensation.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return none
 */
void FDCAN_EnableTxDelayCompensation(FDCAN_Module *FDCANx)
{
    FDCANx->DBTP |= FDCAN_DBTP_TDC;
}

/**
 *\*\name   FDCAN_DisableTxDelayCompensation.
 *\*\fun    Disable the transmitter delay compensation.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return none
 */
void FDCAN_DisableTxDelayCompensation(FDCAN_Module *FDCANx)
{
    FDCANx->DBTP &= ~FDCAN_DBTP_TDC;
}

/**
 *\*\name   FDCAN_EnableISOMode.
 *\*\fun    Enable ISO 11898-1 protocol mode.
 *\*\       CAN FD frame format is according to ISO 11898-1 standard.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return none
 */
void FDCAN_EnableISOMode(FDCAN_Module *FDCANx)
{
    /* Disable Non ISO protocol mode */
    FDCANx->CCCR &= ~FDCAN_CCCR_NISO;
}

/**
 *\*\name   FDCAN_DisableISOMode.
 *\*\fun    Disable ISO 11898-1 protocol mode.
 *\*\       CAN FD frame format is according to Bosch CAN FD specification V1.0.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return none
 */
void FDCAN_DisableISOMode(FDCAN_Module *FDCANx)
{
    /* Enable Non ISO protocol mode */
    FDCANx->CCCR |= FDCAN_CCCR_NISO;
}

/**
 *\*\name   FDCAN_EnableEdgeFilter.
 *\*\fun    Enable edge filtering during bus integration.
 *\*\       Two consecutive dominant tq are required to detect an edge for hard synchronization.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return none
 */
void FDCAN_EnableEdgeFilter(FDCAN_Module *FDCANx)
{
    /* Enable edge filtering */
    FDCANx->CCCR |= FDCAN_CCCR_EFBI;
}

/**
 *\*\name   FDCAN_DisableEdgeFilter.
 *\*\fun    Disable edge filtering during bus integration.
 *\*\       One dominant tq is required to detect an edge for hard synchronization.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return none
 */
void FDCAN_DisableEdgeFilter(FDCAN_Module *FDCANx)
{
    /* Disable edge filtering */
    FDCANx->CCCR &= ~FDCAN_CCCR_EFBI;
}

/**
 *\*\name   FDCAN_Start.
 *\*\fun    Start the FDCAN module.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return none
 */
void FDCAN_Start(FDCAN_Module *FDCANx)
{
    /* Request leave initialisation */
    FDCANx->CCCR &= ~FDCAN_CCCR_INIT;
}

/**
 *\*\name   FDCAN_Stop.
 *\*\fun    Stop the FDCAN module and enable access to configuration registers.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_Stop(FDCAN_Module *FDCANx)
{
    uint32_t timeout;
    FDCAN_MsgRamType *pMsg;

    pMsg = pMsgRam[FDCAN_Get_Index(FDCANx)];

    /* Request initialisation */
    FDCANx->CCCR |= FDCAN_CCCR_INIT;

    /* Wait until the INIT bit into CCCR register is set */
    timeout = 0;

    while ((FDCANx->CCCR & FDCAN_CCCR_INIT) == 0U)
    {
        if (timeout > FDCAN_TIMEOUT_COUNT)
        {
            return ERROR;
        }

        timeout++;
    }

    /* Exit from Sleep mode */
    FDCANx->CCCR &= ~FDCAN_CCCR_CSR;

    timeout = 0;

    /* Wait until FDCAN exits sleep mode */
    while ((FDCANx->CCCR & FDCAN_CCCR_CSA) == FDCAN_CCCR_CSA)
    {
        if (timeout > FDCAN_TIMEOUT_COUNT)
        {
            return ERROR;
        }

        timeout++;
    }

    /* Enable configuration change */
    FDCANx->CCCR |= FDCAN_CCCR_CCE;

    /* Reset Latest Tx FIFO/Queue Request Buffer Index */
    pMsg->LastTxFifoQReqBuf = 0;

    /* Return function status */
    return SUCCESS;
}

/**
 *\*\name   FDCAN_AddMsgToTxFifoQ.
 *\*\fun    Add a message to the Tx FIFO/Queue and activate the corresponding transmission request
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  pTxHeader :pointer to a FDCAN_TxHeaderType structure.
 *\*\          - IdType
 *\*\               - FDCAN_STANDARD_ID
 *\*\               - FDCAN_EXTENDED_ID
 *\*\          - ID
 *\*\               This parameter must be a value between:
 *\*\               - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
 *\*\               - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID
 *\*\          - TxFrameType
 *\*\               - FDCAN_DATA_FRAME
 *\*\               - FDCAN_REMOTE_FRAME
 *\*\          - DataLength
 *\*\               - FDCAN_DLC_BYTES_0
 *\*\               - FDCAN_DLC_BYTES_1
 *\*\               - FDCAN_DLC_BYTES_2
 *\*\               - FDCAN_DLC_BYTES_3
 *\*\               - FDCAN_DLC_BYTES_4
 *\*\               - FDCAN_DLC_BYTES_5
 *\*\               - FDCAN_DLC_BYTES_6
 *\*\               - FDCAN_DLC_BYTES_7
 *\*\               - FDCAN_DLC_BYTES_8
 *\*\               - FDCAN_DLC_BYTES_12
 *\*\               - FDCAN_DLC_BYTES_16
 *\*\               - FDCAN_DLC_BYTES_20
 *\*\               - FDCAN_DLC_BYTES_24
 *\*\               - FDCAN_DLC_BYTES_32
 *\*\               - FDCAN_DLC_BYTES_48
 *\*\               - FDCAN_DLC_BYTES_64
 *\*\          - ErrorState
 *\*\               - FDCAN_ESI_ACTIVE
 *\*\               - FDCAN_ESI_PASSIVE
 *\*\          - BitRateSwitch
 *\*\               - FDCAN_BRS_OFF
 *\*\               - FDCAN_BRS_ON
 *\*\          - FDFormat
 *\*\               - FDCAN_CLASSIC_CAN
 *\*\               - FDCAN_FD_CAN
 *\*\          - TxEventFifo
 *\*\               - FDCAN_NO_TX_EVENTS
 *\*\               - FDCAN_STORE_TX_EVENTS
 *\*\          - MsgMarker
 *\*\               This parameter must be a value between 0 and 0xFF
 *\*\param  pTxData :pointer to a buffer containing the payload of the Tx frame.
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_AddMsgToTxFifoQ(FDCAN_Module *FDCANx, FDCAN_TxHeaderType *pTxHeader, uint8_t *pTxData)
{
    uint32_t PutIndex;
    FDCAN_MsgRamType *pMsg;

    pMsg = pMsgRam[FDCAN_Get_Index(FDCANx)];

    /* Check that the Tx FIFO/Queue has an allocated area into the RAM */
    if ((FDCANx->TXBC & FDCAN_TXBC_TFQS) == 0U)
    {
        return ERROR;
    }

    /* Check that the Tx FIFO/Queue is not full */
    if ((FDCANx->TXFQS & FDCAN_TXFQS_TFQF) != 0U)
    {
        return ERROR;
    }

    /* Get the Tx FIFO PutIndex */
    PutIndex = ((FDCANx->TXFQS & FDCAN_TXFQS_TFQPI) >> FDCAN_TXFQS_TFQPI_OFFSET);

    /* Add the message to the Tx FIFO/Queue */
    FDCAN_CopyMsgToRAM(FDCANx, pTxHeader, pTxData, PutIndex);

    /* Activate the corresponding transmission request */
    FDCANx->TXBAR = (0x1UL << PutIndex);

    /* Store the Latest Tx FIFO/Queue Request Buffer Index */
    pMsg->LastTxFifoQReqBuf =  (0x1UL << PutIndex);

    /* Return function status */
    return SUCCESS;
}

/**
 *\*\name   FDCAN_AddMsgToTxBuffer.
 *\*\fun    Add a message to a dedicated Tx buffer
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  pTxHeader :pointer to a FDCAN_TxHeaderType structure.
 *\*\          - IdType
 *\*\               - FDCAN_STANDARD_ID
 *\*\               - FDCAN_EXTENDED_ID
 *\*\          - ID
 *\*\               This parameter must be a value between:
 *\*\               - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
 *\*\               - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID
 *\*\          - TxFrameType
 *\*\               - FDCAN_DATA_FRAME
 *\*\               - FDCAN_REMOTE_FRAME
 *\*\          - DataLength
 *\*\               - FDCAN_DLC_BYTES_0
 *\*\               - FDCAN_DLC_BYTES_1
 *\*\               - FDCAN_DLC_BYTES_2
 *\*\               - FDCAN_DLC_BYTES_3
 *\*\               - FDCAN_DLC_BYTES_4
 *\*\               - FDCAN_DLC_BYTES_5
 *\*\               - FDCAN_DLC_BYTES_6
 *\*\               - FDCAN_DLC_BYTES_7
 *\*\               - FDCAN_DLC_BYTES_8
 *\*\               - FDCAN_DLC_BYTES_12
 *\*\               - FDCAN_DLC_BYTES_16
 *\*\               - FDCAN_DLC_BYTES_20
 *\*\               - FDCAN_DLC_BYTES_24
 *\*\               - FDCAN_DLC_BYTES_32
 *\*\               - FDCAN_DLC_BYTES_48
 *\*\               - FDCAN_DLC_BYTES_64
 *\*\          - ErrorState
 *\*\               - FDCAN_ESI_ACTIVE
 *\*\               - FDCAN_ESI_PASSIVE
 *\*\          - BitRateSwitch
 *\*\               - FDCAN_BRS_OFF
 *\*\               - FDCAN_BRS_ON
 *\*\          - FDFormat
 *\*\               - FDCAN_CLASSIC_CAN
 *\*\               - FDCAN_FD_CAN
 *\*\          - TxEventFifo
 *\*\               - FDCAN_NO_TX_EVENTS
 *\*\               - FDCAN_STORE_TX_EVENTS
 *\*\          - MsgMarker
 *\*\               This parameter must be a value between 0 and 0xFF
 *\*\param  pTxData :pointer to a buffer containing the payload of the Tx frame.
 *\*\param  BufferIndex :
 *\*\          - FDCAN_TX_BUFFER0
 *\*\          - FDCAN_TX_BUFFER1
 *\*\          - FDCAN_TX_BUFFER2
 *\*\          - FDCAN_TX_BUFFER3
 *\*\          - FDCAN_TX_BUFFER4
 *\*\          - FDCAN_TX_BUFFER5
 *\*\          - FDCAN_TX_BUFFER6
 *\*\          - FDCAN_TX_BUFFER7
 *\*\          - FDCAN_TX_BUFFER8
 *\*\          - FDCAN_TX_BUFFER9
 *\*\          - FDCAN_TX_BUFFER10
 *\*\          - FDCAN_TX_BUFFER11
 *\*\          - FDCAN_TX_BUFFER12
 *\*\          - FDCAN_TX_BUFFER13
 *\*\          - FDCAN_TX_BUFFER14
 *\*\          - FDCAN_TX_BUFFER15
 *\*\          - FDCAN_TX_BUFFER16
 *\*\          - FDCAN_TX_BUFFER17
 *\*\          - FDCAN_TX_BUFFER18
 *\*\          - FDCAN_TX_BUFFER19
 *\*\          - FDCAN_TX_BUFFER20
 *\*\          - FDCAN_TX_BUFFER21
 *\*\          - FDCAN_TX_BUFFER22
 *\*\          - FDCAN_TX_BUFFER23
 *\*\          - FDCAN_TX_BUFFER24
 *\*\          - FDCAN_TX_BUFFER25
 *\*\          - FDCAN_TX_BUFFER26
 *\*\          - FDCAN_TX_BUFFER27
 *\*\          - FDCAN_TX_BUFFER28
 *\*\          - FDCAN_TX_BUFFER29
 *\*\          - FDCAN_TX_BUFFER30
 *\*\          - FDCAN_TX_BUFFER31
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_AddMsgToTxBuffer(FDCAN_Module *FDCANx, FDCAN_TxHeaderType *pTxHeader, uint8_t *pTxData, uint32_t BufferIndex)
{
    /* Check that the selected buffer has an allocated area into the RAM */
    if (POSITION_VAL(BufferIndex) >= ((FDCANx->TXBC & FDCAN_TXBC_NDTB) >> FDCAN_TXBC_NDTB_OFFSET))
    {
        return ERROR;
    }

    /* Check if there is also transmission request pending for the selected buffer */
    if ((FDCANx->TXBRP & BufferIndex) != 0U)
    {
        return ERROR;
    }

    /* Add the message to the Tx buffer */
    FDCAN_CopyMsgToRAM(FDCANx, pTxHeader, pTxData, POSITION_VAL(BufferIndex));

    /* Return function status */
    return SUCCESS;
}

/**
 *\*\name   FDCAN_EnableTxBufferRequest.
 *\*\fun    Enable transmission request.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  BufferIndex :
 *\*\          - FDCAN_TX_BUFFER0
 *\*\          - FDCAN_TX_BUFFER1
 *\*\          - FDCAN_TX_BUFFER2
 *\*\          - FDCAN_TX_BUFFER3
 *\*\          - FDCAN_TX_BUFFER4
 *\*\          - FDCAN_TX_BUFFER5
 *\*\          - FDCAN_TX_BUFFER6
 *\*\          - FDCAN_TX_BUFFER7
 *\*\          - FDCAN_TX_BUFFER8
 *\*\          - FDCAN_TX_BUFFER9
 *\*\          - FDCAN_TX_BUFFER10
 *\*\          - FDCAN_TX_BUFFER11
 *\*\          - FDCAN_TX_BUFFER12
 *\*\          - FDCAN_TX_BUFFER13
 *\*\          - FDCAN_TX_BUFFER14
 *\*\          - FDCAN_TX_BUFFER15
 *\*\          - FDCAN_TX_BUFFER16
 *\*\          - FDCAN_TX_BUFFER17
 *\*\          - FDCAN_TX_BUFFER18
 *\*\          - FDCAN_TX_BUFFER19
 *\*\          - FDCAN_TX_BUFFER20
 *\*\          - FDCAN_TX_BUFFER21
 *\*\          - FDCAN_TX_BUFFER22
 *\*\          - FDCAN_TX_BUFFER23
 *\*\          - FDCAN_TX_BUFFER24
 *\*\          - FDCAN_TX_BUFFER25
 *\*\          - FDCAN_TX_BUFFER26
 *\*\          - FDCAN_TX_BUFFER27
 *\*\          - FDCAN_TX_BUFFER28
 *\*\          - FDCAN_TX_BUFFER29
 *\*\          - FDCAN_TX_BUFFER30
 *\*\          - FDCAN_TX_BUFFER31
 *\*\return none
 */
void FDCAN_EnableTxBufferRequest(FDCAN_Module *FDCANx, uint32_t BufferIndex)
{
    /* Add transmission request */
    FDCANx->TXBAR = BufferIndex;
}

/**
 *\*\name   FDCAN_GetLastTxFifoQReqBuf.
 *\*\fun    Get Tx buffer index of latest Tx FIFO/Queue request.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return Tx buffer index of last Tx FIFO/Queue request
 *\*\          - 0:  no Tx FIFO/Queue request have been submitted
 *\*\          - FDCAN_TX_BUFFER0
 *\*\          - FDCAN_TX_BUFFER1
 *\*\          - FDCAN_TX_BUFFER2
 *\*\          - FDCAN_TX_BUFFER3
 *\*\          - FDCAN_TX_BUFFER4
 *\*\          - FDCAN_TX_BUFFER5
 *\*\          - FDCAN_TX_BUFFER6
 *\*\          - FDCAN_TX_BUFFER7
 *\*\          - FDCAN_TX_BUFFER8
 *\*\          - FDCAN_TX_BUFFER9
 *\*\          - FDCAN_TX_BUFFER10
 *\*\          - FDCAN_TX_BUFFER11
 *\*\          - FDCAN_TX_BUFFER12
 *\*\          - FDCAN_TX_BUFFER13
 *\*\          - FDCAN_TX_BUFFER14
 *\*\          - FDCAN_TX_BUFFER15
 *\*\          - FDCAN_TX_BUFFER16
 *\*\          - FDCAN_TX_BUFFER17
 *\*\          - FDCAN_TX_BUFFER18
 *\*\          - FDCAN_TX_BUFFER19
 *\*\          - FDCAN_TX_BUFFER20
 *\*\          - FDCAN_TX_BUFFER21
 *\*\          - FDCAN_TX_BUFFER22
 *\*\          - FDCAN_TX_BUFFER23
 *\*\          - FDCAN_TX_BUFFER24
 *\*\          - FDCAN_TX_BUFFER25
 *\*\          - FDCAN_TX_BUFFER26
 *\*\          - FDCAN_TX_BUFFER27
 *\*\          - FDCAN_TX_BUFFER28
 *\*\          - FDCAN_TX_BUFFER29
 *\*\          - FDCAN_TX_BUFFER30
 *\*\          - FDCAN_TX_BUFFER31
 */
uint32_t FDCAN_GetLastTxFifoQReqBuf(FDCAN_Module *FDCANx)
{
    FDCAN_MsgRamType *pMsg;

    pMsg = pMsgRam[FDCAN_Get_Index(FDCANx)];

    /* Return Last Tx FIFO/Queue Request Buffer  */
    return (pMsg->LastTxFifoQReqBuf);
}

/**
 *\*\name   FDCAN_AbortTxRequest.
 *\*\fun    Abort transmission request.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  BufferIndex :
 *\*\          - FDCAN_TX_BUFFER0
 *\*\          - FDCAN_TX_BUFFER1
 *\*\          - FDCAN_TX_BUFFER2
 *\*\          - FDCAN_TX_BUFFER3
 *\*\          - FDCAN_TX_BUFFER4
 *\*\          - FDCAN_TX_BUFFER5
 *\*\          - FDCAN_TX_BUFFER6
 *\*\          - FDCAN_TX_BUFFER7
 *\*\          - FDCAN_TX_BUFFER8
 *\*\          - FDCAN_TX_BUFFER9
 *\*\          - FDCAN_TX_BUFFER10
 *\*\          - FDCAN_TX_BUFFER11
 *\*\          - FDCAN_TX_BUFFER12
 *\*\          - FDCAN_TX_BUFFER13
 *\*\          - FDCAN_TX_BUFFER14
 *\*\          - FDCAN_TX_BUFFER15
 *\*\          - FDCAN_TX_BUFFER16
 *\*\          - FDCAN_TX_BUFFER17
 *\*\          - FDCAN_TX_BUFFER18
 *\*\          - FDCAN_TX_BUFFER19
 *\*\          - FDCAN_TX_BUFFER20
 *\*\          - FDCAN_TX_BUFFER21
 *\*\          - FDCAN_TX_BUFFER22
 *\*\          - FDCAN_TX_BUFFER23
 *\*\          - FDCAN_TX_BUFFER24
 *\*\          - FDCAN_TX_BUFFER25
 *\*\          - FDCAN_TX_BUFFER26
 *\*\          - FDCAN_TX_BUFFER27
 *\*\          - FDCAN_TX_BUFFER28
 *\*\          - FDCAN_TX_BUFFER29
 *\*\          - FDCAN_TX_BUFFER30
 *\*\          - FDCAN_TX_BUFFER31
 *\*\return none
 */
void FDCAN_AbortTxRequest(FDCAN_Module *FDCANx, uint32_t BufferIndex)
{
    /* Add cancellation request */
    FDCANx->TXBCR = BufferIndex;
}

/**
 *\*\name   FDCAN_GetRxMsg.
 *\*\fun    Get an FDCAN frame from the Rx Buffer/FIFO zone into the message RAM.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  RxLocation :
 *\*\          - FDCAN_RX_FIFO0
 *\*\          - FDCAN_RX_FIFO1
 *\*\          - FDCAN_RX_BUFFER0
 *\*\          - FDCAN_RX_BUFFER1
 *\*\          - FDCAN_RX_BUFFER2
 *\*\          - FDCAN_RX_BUFFER3
 *\*\          - FDCAN_RX_BUFFER4
 *\*\          - FDCAN_RX_BUFFER5
 *\*\          - FDCAN_RX_BUFFER6
 *\*\          - FDCAN_RX_BUFFER7
 *\*\          - FDCAN_RX_BUFFER8
 *\*\          - FDCAN_RX_BUFFER9
 *\*\          - FDCAN_RX_BUFFER10
 *\*\          - FDCAN_RX_BUFFER11
 *\*\          - FDCAN_RX_BUFFER12
 *\*\          - FDCAN_RX_BUFFER13
 *\*\          - FDCAN_RX_BUFFER14
 *\*\          - FDCAN_RX_BUFFER15
 *\*\          - FDCAN_RX_BUFFER16
 *\*\          - FDCAN_RX_BUFFER17
 *\*\          - FDCAN_RX_BUFFER18
 *\*\          - FDCAN_RX_BUFFER19
 *\*\          - FDCAN_RX_BUFFER20
 *\*\          - FDCAN_RX_BUFFER21
 *\*\          - FDCAN_RX_BUFFER22
 *\*\          - FDCAN_RX_BUFFER23
 *\*\          - FDCAN_RX_BUFFER24
 *\*\          - FDCAN_RX_BUFFER25
 *\*\          - FDCAN_RX_BUFFER26
 *\*\          - FDCAN_RX_BUFFER27
 *\*\          - FDCAN_RX_BUFFER28
 *\*\          - FDCAN_RX_BUFFER29
 *\*\          - FDCAN_RX_BUFFER30
 *\*\          - FDCAN_RX_BUFFER31
 *\*\          - FDCAN_RX_BUFFER32
 *\*\          - FDCAN_RX_BUFFER33
 *\*\          - FDCAN_RX_BUFFER34
 *\*\          - FDCAN_RX_BUFFER35
 *\*\          - FDCAN_RX_BUFFER36
 *\*\          - FDCAN_RX_BUFFER37
 *\*\          - FDCAN_RX_BUFFER38
 *\*\          - FDCAN_RX_BUFFER39
 *\*\          - FDCAN_RX_BUFFER40
 *\*\          - FDCAN_RX_BUFFER41
 *\*\          - FDCAN_RX_BUFFER42
 *\*\          - FDCAN_RX_BUFFER43
 *\*\          - FDCAN_RX_BUFFER44
 *\*\          - FDCAN_RX_BUFFER45
 *\*\          - FDCAN_RX_BUFFER46
 *\*\          - FDCAN_RX_BUFFER47
 *\*\          - FDCAN_RX_BUFFER48
 *\*\          - FDCAN_RX_BUFFER49
 *\*\          - FDCAN_RX_BUFFER50
 *\*\          - FDCAN_RX_BUFFER51
 *\*\          - FDCAN_RX_BUFFER52
 *\*\          - FDCAN_RX_BUFFER53
 *\*\          - FDCAN_RX_BUFFER54
 *\*\          - FDCAN_RX_BUFFER55
 *\*\          - FDCAN_RX_BUFFER56
 *\*\          - FDCAN_RX_BUFFER57
 *\*\          - FDCAN_RX_BUFFER58
 *\*\          - FDCAN_RX_BUFFER59
 *\*\          - FDCAN_RX_BUFFER60
 *\*\          - FDCAN_RX_BUFFER61
 *\*\          - FDCAN_RX_BUFFER62
 *\*\          - FDCAN_RX_BUFFER63
 *\*\param  pRxHeader :pointer to a FDCAN_RxHeaderType structure.
 *\*\          - IdType
 *\*\               - FDCAN_STANDARD_ID
 *\*\               - FDCAN_EXTENDED_ID
 *\*\          - ID
 *\*\               This parameter must be a value between:
 *\*\               - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
 *\*\               - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID
 *\*\          - RxFrameType
 *\*\               - FDCAN_DATA_FRAME
 *\*\               - FDCAN_REMOTE_FRAME
 *\*\          - DataLength
 *\*\               - FDCAN_DLC_BYTES_0
 *\*\               - FDCAN_DLC_BYTES_1
 *\*\               - FDCAN_DLC_BYTES_2
 *\*\               - FDCAN_DLC_BYTES_3
 *\*\               - FDCAN_DLC_BYTES_4
 *\*\               - FDCAN_DLC_BYTES_5
 *\*\               - FDCAN_DLC_BYTES_6
 *\*\               - FDCAN_DLC_BYTES_7
 *\*\               - FDCAN_DLC_BYTES_8
 *\*\               - FDCAN_DLC_BYTES_12
 *\*\               - FDCAN_DLC_BYTES_16
 *\*\               - FDCAN_DLC_BYTES_20
 *\*\               - FDCAN_DLC_BYTES_24
 *\*\               - FDCAN_DLC_BYTES_32
 *\*\               - FDCAN_DLC_BYTES_48
 *\*\               - FDCAN_DLC_BYTES_64
 *\*\          - ErrorState
 *\*\               - FDCAN_ESI_ACTIVE
 *\*\               - FDCAN_ESI_PASSIVE
 *\*\          - BitRateSwitch
 *\*\               - FDCAN_BRS_OFF
 *\*\               - FDCAN_BRS_ON
 *\*\          - FDFormat
 *\*\               - FDCAN_CLASSIC_CAN
 *\*\               - FDCAN_FD_CAN
 *\*\          - RxTimestamp
 *\*\               This parameter must be a value between 0 and 0xFFFF
 *\*\          - FilterIndex
 *\*\               This parameter must be a value between:
 *\*\               - 0 and 127, if IdType is FDCAN_STANDARD_ID
 *\*\               - 0 and 63, if IdType is FDCAN_EXTENDED_ID
 *\*\          - Matching
 *\*\               - FDCAN_ACCEPT_MACHING_FIDX
 *\*\               - FDCAN_ACCEPT_NON_MATCHING
 *\*\param  pRxData :pointer to a buffer containing the payload of the Rx frame.
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_GetRxMsg(FDCAN_Module *FDCANx, uint32_t RxLocation, FDCAN_RxHeaderType *pRxHeader, uint8_t *pRxData)
{
    uint32_t *RxAddress;
    uint8_t  *pData;
    uint32_t Cnt;
    uint32_t GetIndex;
    FDCAN_MsgRamType *pMsg;

    pMsg = pMsgRam[FDCAN_Get_Index(FDCANx)];
    GetIndex = 0;

    if (RxLocation == FDCAN_RX_FIFO0) /* Rx element is assigned to the Rx FIFO 0 */
    {
        /* Check that the Rx FIFO 0 has an allocated area into the RAM */
        if ((FDCANx->RXF0C & FDCAN_RXF0C_F0S) == 0UL)
        {
            return ERROR;
        }

        /* Check that the Rx FIFO 0 is not empty */
        if ((FDCANx->RXF0S & FDCAN_RXF0S_F0FL) == 0UL)
        {
            return ERROR;
        }

        /* Calculate Rx FIFO 0 element get index*/
        GetIndex = ((FDCANx->RXF0S & FDCAN_RXF0S_F0GI) >> FDCAN_RXFXS_FXGI_OFFSET);

        /* Check that the Rx FIFO 0 is full & overwrite mode is on*/
        if(FDCAN_RXF0S_F0F == (FDCANx->RXF0S & FDCAN_RXF0S_F0F))
        {
            if(FDCAN_RX_FIFO_OVERWRITE == (FDCANx->RXF0C & FDCAN_RXF0C_F0OM))
            {
                /* When overwrite status is on discard first message in FIFO */
                if(GetIndex >= (pMsg->RxFifo0Size - 1UL))
                {
                    GetIndex = 0;
                }
                else
                {
                    GetIndex++;
                }
            }
        }

        /* Calculate Rx FIFO 0 element address */
        RxAddress = (uint32_t *)(pMsg->RxFIFO0StrAddr + (GetIndex * pMsg->RxFifo0DataSize * 4UL));
    }
    else if (RxLocation == FDCAN_RX_FIFO1) /* Rx element is assigned to the Rx FIFO 1 */
    {
        /* Check that the Rx FIFO 1 has an allocated area into the RAM */
        if ((FDCANx->RXF1C & FDCAN_RXF1C_F1S) == 0U)
        {
            return ERROR;
        }

        /* Check that the Rx FIFO 0 is not empty */
        if ((FDCANx->RXF1S & FDCAN_RXF1S_F1FL) == 0U)
        {
            return ERROR;
        }

        /* Calculate Rx FIFO 1 element index*/
        GetIndex = ((FDCANx->RXF1S & FDCAN_RXF1S_F1GI) >> FDCAN_RXFXS_FXGI_OFFSET);

        /* Check that the Rx FIFO 1 is full & overwrite mode is on*/
        if(FDCAN_RXF1S_F1F == (FDCANx->RXF1S & FDCAN_RXF1S_F1F) )
        {
            if(FDCAN_RX_FIFO_OVERWRITE == (FDCANx->RXF1C & FDCAN_RXF1C_F1OM))
            {
                /* When overwrite status is on discard first message in FIFO */
                if(GetIndex >= (pMsg->RxFifo1Size - 1UL))
                {
                    GetIndex = 0;
                }
                else
                {
                    GetIndex++;
                }
            }
        }

        /* Calculate Rx FIFO 1 element address */
        RxAddress = (uint32_t *)(pMsg->RxFIFO1StrAddr + (GetIndex * pMsg->RxFifo1DataSize * 4UL));
    }
    else /* Rx element is assigned to a dedicated Rx buffer */
    {
        /* Check that the selected buffer has an allocated area into the RAM */
        if (RxLocation >= pMsg->RxBufferSize)
        {
            return ERROR;
        }

        /* Calculate Rx buffer address */
        RxAddress = (uint32_t *)(pMsg->RxBufferStrAddr + (RxLocation * pMsg->RxBufferDataSize * 4U));
    }

    /* First word of Rx FIFO element */
    /* Retrieve IdType */
    pRxHeader->IdType = *RxAddress & FDCAN_ELEMENT_XTD;

    /* Retrieve Identifier */
    if (pRxHeader->IdType == FDCAN_STANDARD_ID) /* Standard ID element */
    {
        pRxHeader->ID = ((*RxAddress & FDCAN_ELEMENT_STDID) >> FDCAN_ELEMENT_STDID_OFFSET);
    }
    else /* Extended ID element */
    {
        pRxHeader->ID = (*RxAddress & FDCAN_ELEMENT_EXTID);
    }

    /* Retrieve RxFrameType */
    pRxHeader->RxFrameType = (*RxAddress & FDCAN_ELEMENT_RTR);

    /* Retrieve ErrorStateIndicator */
    pRxHeader->ErrorState = (*RxAddress & FDCAN_ELEMENT_ESI);

    /* Increment RxAddress pointer to second word of Rx FIFO element */
    RxAddress++;

    /* Retrieve RxTimestamp */
    pRxHeader->RxTimestamp = (*RxAddress & FDCAN_ELEMENT_TS);

    /* Retrieve DataLength */
    pRxHeader->DataLength = (*RxAddress & FDCAN_ELEMENT_DLC);

    /* Retrieve BitRateSwitch */
    pRxHeader->BitRateSwitch = (*RxAddress & FDCAN_ELEMENT_BRS);

    /* Retrieve FDFormat */
    pRxHeader->FDFormat = (*RxAddress & FDCAN_ELEMENT_FDF);

    /* Retrieve FilterIndex */
    pRxHeader->FilterIndex = ((*RxAddress & FDCAN_ELEMENT_FIDX) >> FDCAN_ELEMENT_FIDX_OFFSET);

    /* Retrieve NonMatchingFrame */
    pRxHeader->Matching = (*RxAddress & FDCAN_ELEMENT_ANMF);

    /* Increment RxAddress pointer to payload of Rx FIFO element */
    RxAddress++;

    /* Retrieve Rx payload */
    pData = (uint8_t *)RxAddress;

    for (Cnt = 0; Cnt < DLCtoBytes[pRxHeader->DataLength >> FDCAN_ELEMENT_DLC_OFFSET]; Cnt++)
    {
        pRxData[Cnt] = pData[Cnt];
    }

    if (RxLocation == FDCAN_RX_FIFO0) /* Rx element is assigned to the Rx FIFO 0 */
    {
        /* Acknowledge the Rx FIFO 0 that the oldest element is read so that it increments the GetIndex */
        FDCANx->RXF0A = GetIndex;
    }
    else if (RxLocation == FDCAN_RX_FIFO1) /* Rx element is assigned to the Rx FIFO 1 */
    {
        /* Acknowledge the Rx FIFO 1 that the oldest element is read so that it increments the GetIndex */
        FDCANx->RXF1A = GetIndex;
    }
    else /* Rx element is assigned to a dedicated Rx buffer */
    {
        /* Clear the New Data flag of the current Rx buffer */
        if (RxLocation < FDCAN_RX_BUFFER32)
        {
            FDCANx->NDAT1 = (1UL << RxLocation);
        }
        else /* FDCAN_RX_BUFFER32 <= RxLocation <= FDCAN_RX_BUFFER63 */
        {
            FDCANx->NDAT2 = (1UL << (RxLocation & 0x1FUL));
        }
    }

    return SUCCESS;
}

/**
 *\*\name   FDCAN_GetTxEvent.
 *\*\fun    Get an FDCAN Tx event from the Tx Event FIFO zone into the message RAM.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  pTxEvent pointer to a FDCAN_TxEventFifoType structure.
 *\*\          - IdType
 *\*\               - FDCAN_STANDARD_ID
 *\*\               - FDCAN_EXTENDED_ID
 *\*\          - ID
 *\*\               This parameter must be a value between:
 *\*\               - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
 *\*\               - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID
 *\*\          - TxFrameType
 *\*\               - FDCAN_DATA_FRAME
 *\*\               - FDCAN_REMOTE_FRAME
 *\*\          - DataLength
 *\*\               - FDCAN_DLC_BYTES_0
 *\*\               - FDCAN_DLC_BYTES_1
 *\*\               - FDCAN_DLC_BYTES_2
 *\*\               - FDCAN_DLC_BYTES_3
 *\*\               - FDCAN_DLC_BYTES_4
 *\*\               - FDCAN_DLC_BYTES_5
 *\*\               - FDCAN_DLC_BYTES_6
 *\*\               - FDCAN_DLC_BYTES_7
 *\*\               - FDCAN_DLC_BYTES_8
 *\*\               - FDCAN_DLC_BYTES_12
 *\*\               - FDCAN_DLC_BYTES_16
 *\*\               - FDCAN_DLC_BYTES_20
 *\*\               - FDCAN_DLC_BYTES_24
 *\*\               - FDCAN_DLC_BYTES_32
 *\*\               - FDCAN_DLC_BYTES_48
 *\*\               - FDCAN_DLC_BYTES_64
 *\*\          - ErrorState
 *\*\               - FDCAN_ESI_ACTIVE
 *\*\               - FDCAN_ESI_PASSIVE
 *\*\          - BitRateSwitch;
 *\*\               - FDCAN_BRS_OFF
 *\*\               - FDCAN_BRS_ON
 *\*\          - FDFormat;
 *\*\               - FDCAN_CLASSIC_CAN
 *\*\               - FDCAN_FD_CAN
 *\*\          - TxTimestamp;
 *\*\               This parameter must be a value between 0 and 0xFFFF
 *\*\          - MsgMarker;
 *\*\               This parameter must be a value between 0 and 0xFF
 *\*\          - EventType;
 *\*\               - FDCAN_TX_EVENT
 *\*\               - FDCAN_TX_IN_SPITE_OF_ABORT
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_GetTxEvent(FDCAN_Module *FDCANx, FDCAN_TxEventFifoType *pTxEvent)
{
    uint32_t *TxEventAddress;
    uint32_t GetIndex;
    FDCAN_MsgRamType *pMsg;

    pMsg = pMsgRam[FDCAN_Get_Index(FDCANx)];

    /* Check that the Tx Event FIFO has an allocated area into the RAM */
    if ((FDCANx->TXEFC & FDCAN_TXEFC_EFS) == 0UL)
    {
        return ERROR;
    }

    /* Check that the Tx event FIFO is not empty */
    if ((FDCANx->TXEFS & FDCAN_TXEFS_EFFL) == 0UL)
    {
        return ERROR;
    }

    /* Calculate Tx event FIFO element address */
    GetIndex = ((FDCANx->TXEFS & FDCAN_TXEFS_EFGI) >> FDCAN_TXEFS_EFGI_OFFSET);
    TxEventAddress = (uint32_t *)(pMsg->TxEventFIFOStrAddr + (GetIndex * FDCAN_TX_EVENT_FIFO_WORDS * 4UL));

    /* First word of Tx Event FIFO element */
    /* Retrieve IdType */
    pTxEvent->IdType = *TxEventAddress & FDCAN_ELEMENT_XTD;

    /* Retrieve Identifier */
    if (pTxEvent->IdType == FDCAN_STANDARD_ID) /* Standard ID element */
    {
        pTxEvent->ID = ((*TxEventAddress & FDCAN_ELEMENT_STDID) >> FDCAN_ELEMENT_STDID_OFFSET);
    }
    else /* Extended ID element */
    {
        pTxEvent->ID = (*TxEventAddress & FDCAN_ELEMENT_EXTID);
    }

    /* Retrieve TxFrameType */
    pTxEvent->TxFrameType = (*TxEventAddress & FDCAN_ELEMENT_RTR);

    /* Retrieve ErrorStateIndicator */
    pTxEvent->ErrorState = (*TxEventAddress & FDCAN_ELEMENT_ESI);

    /* Increment TxEventAddress pointer to second word of Tx Event FIFO element */
    TxEventAddress++;

    /* Retrieve TxTimestamp */
    pTxEvent->TxTimestamp = (*TxEventAddress & FDCAN_ELEMENT_TS);

    /* Retrieve DataLength */
    pTxEvent->DataLength = (*TxEventAddress & FDCAN_ELEMENT_DLC);

    /* Retrieve BitRateSwitch */
    pTxEvent->BitRateSwitch = (*TxEventAddress & FDCAN_ELEMENT_BRS);

    /* Retrieve FDFormat */
    pTxEvent->FDFormat = (*TxEventAddress & FDCAN_ELEMENT_FDF);

    /* Retrieve EventType */
    pTxEvent->EventType = (*TxEventAddress & FDCAN_ELEMENT_ET);

    /* Retrieve MessageMarker */
    pTxEvent->MsgMarker = ((*TxEventAddress & FDCAN_ELEMENT_MM) >> FDCAN_ELEMENT_MM_OFFSET);

    /* Acknowledge the Tx Event FIFO that the oldest element is read so that it increments the GetIndex */
    FDCANx->TXEFA = GetIndex;

    /* Return function status */
    return SUCCESS;
}

/**
 *\*\name   FDCAN_GetHpMsgStatus.
 *\*\fun    Get high priority message status.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  HpMsgStatus pointer to an FDCAN_HpMsgStatus structure.
 *\*\          - FilterList
 *\*\               - FDCAN_HP_STANDARD_FILTER_LIST
 *\*\               - FDCAN_HP_EXTENDED_FILTER_LIST
 *\*\          - FilterIndex
 *\*\               This parameter can be a value between:
 *\*\               - 0 and 127, if FilterList is FDCAN_HP_STANDARD_FILTER_LIST
 *\*\               - 0 and 63, if FilterList is FDCAN_HP_EXTENDED_FILTER_LIST
 *\*\          - MsgStore
 *\*\               - FDCAN_HP_STORAGE_NO_FIFO
 *\*\               - FDCAN_HP_STORAGE_MSG_LOST
 *\*\               - FDCAN_HP_STORAGE_RXFIFO0
 *\*\               - FDCAN_HP_STORAGE_RXFIFO1
 *\*\          - MsgIndex
 *\*\               - FDCAN_HP_STORAGE_RXFIFO0
 *\*\               - FDCAN_HP_STORAGE_RXFIFO1
 *\*\return none
 */
void FDCAN_GetHpMsgStatus(FDCAN_Module *FDCANx, FDCAN_HpMsgStatus *HpMsgStatus)
{
    HpMsgStatus->FilterList     = (FDCANx->HPMS & FDCAN_HPMS_FLST);
    HpMsgStatus->FilterIndex    = ((FDCANx->HPMS & FDCAN_HPMS_FIDX) >> FDCAN_HPMS_FIDX_OFFSET);
    HpMsgStatus->MsgStore       = (FDCANx->HPMS & FDCAN_HPMS_MSI);
    HpMsgStatus->MsgIndex       = (FDCANx->HPMS & FDCAN_HPMS_BIDX);
}

/**
 *\*\name   FDCAN_GetProtocolStatus.
 *\*\fun    Get protocol status.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  ProtocolStatus pointer to an FDCAN_ProtocolStatus structure.
 *\*\          - uint32_t LastError
 *\*\               - FDCAN_LAST_ERROR_NONE
 *\*\               - FDCAN_LAST_ERROR_STUFF
 *\*\               - FDCAN_LAST_ERROR_FORM
 *\*\               - FDCAN_LAST_ERROR_ACK
 *\*\               - FDCAN_LAST_ERROR_BIT1
 *\*\               - FDCAN_LAST_ERROR_BIT0
 *\*\               - FDCAN_LAST_ERROR_CRC
 *\*\               - FDCAN_LAST_ERROR_NO_CHANGE
 *\*\          - uint32_t LastDataError
 *\*\               - FDCAN_LAST_DATA_ERROR_NONE
 *\*\               - FDCAN_LAST_DATA_ERROR_STUFF
 *\*\               - FDCAN_LAST_DATA_ERROR_FORM
 *\*\               - FDCAN_LAST_DATA_ERROR_ACK
 *\*\               - FDCAN_LAST_DATA_ERROR_BIT1
 *\*\               - FDCAN_LAST_DATA_ERROR_BIT0
 *\*\               - FDCAN_LAST_DATA_ERROR_CRC
 *\*\               - FDCAN_LAST_DATA_ERROR_NO_CHANGE
 *\*\          - uint32_t Activity
 *\*\               - FDCAN_COM_STATE_SYNC
 *\*\               - FDCAN_COM_STATE_IDLE
 *\*\               - FDCAN_COM_STATE_RX
 *\*\               - FDCAN_COM_STATE_TX
 *\*\          - uint32_t Error
 *\*\               - FDCAN_ERROR_ACTIVE
 *\*\               - FDCAN_ERROR_PASSIVE
 *\*\          - uint32_t Warning
 *\*\               - FDCAN_WARNING_BELOW_96
 *\*\               - FDCAN_WARNING_REACH_96
 *\*\          - uint32_t BusOff
 *\*\               - FDCAN_BUS_ON
 *\*\               - FDCAN_BUS_OFF
 *\*\          - uint32_t RxESIflag
 *\*\               - FDCAN_ESI_NOT_SET
 *\*\               - FDCAN_ESI_SET
 *\*\          - uint32_t RxBRSflag
 *\*\               - FDCAN_BRS_NOT_SET
 *\*\               - FDCAN_BRS_SET
 *\*\          - uint32_t RxFDFflag
 *\*\               - FDCAN_FDMSG_NOT_RECEIVED
 *\*\               - FDCAN_FDMSG_RECEIVED
 *\*\          - uint32_t Exception
 *\*\               - FDCAN_NO_EXCEPTION
 *\*\               - FDCAN_HAVE_EXCEPTION
 *\*\          - uint32_t TDCvalue
 *\*\               This parameter can be a value between 0 and 127
 *\*\return none
 */
void FDCAN_GetProtocolStatus(FDCAN_Module *FDCANx, FDCAN_ProtocolStatus *ProtocolStatus)
{
    uint32_t StatusReg;

    /* Read the protocol status register */
    StatusReg = FDCANx->PSR;

    /* Fill the protocol status structure */
    ProtocolStatus->LastError       = (StatusReg & FDCAN_PSR_LEC);
    ProtocolStatus->LastDataError   = (StatusReg & FDCAN_PSR_DLEC);
    ProtocolStatus->Activity        = (StatusReg & FDCAN_PSR_ACT);
    ProtocolStatus->Error           = (StatusReg & FDCAN_PSR_EP);
    ProtocolStatus->Warning         = (StatusReg & FDCAN_PSR_EW);
    ProtocolStatus->BusOff          = (StatusReg & FDCAN_PSR_BO);
    ProtocolStatus->RxESIflag       = (StatusReg & FDCAN_PSR_RESI);
    ProtocolStatus->RxBRSflag       = (StatusReg & FDCAN_PSR_RBRS);
    ProtocolStatus->RxFDFflag       = (StatusReg & FDCAN_PSR_RFDF);
    ProtocolStatus->Exception       = (StatusReg & FDCAN_PSR_PXE);
    ProtocolStatus->TDCvalue        = ((StatusReg & FDCAN_PSR_TDCV) >> FDCAN_PSR_TDCV_OFFSET);
}

/**
 *\*\name   FDCAN_GetErrorCounters.
 *\*\fun    Get error counter values.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  ErrorCounters pointer to an FDCAN_ErrorCounters structure.
 *\*\          - TxErrorCnt
 *\*\               This parameter can be a value between 0 and 255
 *\*\          - RxErrorCnt
 *\*\               This parameter can be a value between 0 and 127
 *\*\          - RxErrorPassive
 *\*\               - FDCAN_RX_ERROR_BELOW_128
 *\*\               - FDCAN_RX_ERROR_REACH_128
 *\*\          - ErrorLogging
 *\*\               This parameter can be a value between 0 and 255.
 *\*\return none
 */
void FDCAN_GetErrorCounters(FDCAN_Module *FDCANx, FDCAN_ErrorCounters *ErrorCounters)
{
    uint32_t CountersReg;

    /* Read the error counters register */
    CountersReg = FDCANx->ECR;

    /* Fill the error counters structure */
    ErrorCounters->TxErrorCnt       = (CountersReg & FDCAN_ECR_TEC);
    ErrorCounters->RxErrorCnt       = ((CountersReg & FDCAN_ECR_REC) >> FDCAN_ECR_REC_OFFSET);
    ErrorCounters->RxErrorPassive   = (CountersReg & FDCAN_ECR_RP);
    ErrorCounters->ErrorLogging     = ((CountersReg & FDCAN_ECR_CEL) >> FDCAN_ECR_CEL_OFFSET);
}

/**
 *\*\name   FDCAN_CheckNewRxBufMsg.
 *\*\fun    Check if a new message is received in the selected Rx buffer.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  Index Rx buffer index.
 *\*\          - FDCAN_RX_BUFFER0
 *\*\          - FDCAN_RX_BUFFER1
 *\*\          - FDCAN_RX_BUFFER2
 *\*\          - FDCAN_RX_BUFFER3
 *\*\          - FDCAN_RX_BUFFER4
 *\*\          - FDCAN_RX_BUFFER5
 *\*\          - FDCAN_RX_BUFFER6
 *\*\          - FDCAN_RX_BUFFER7
 *\*\          - FDCAN_RX_BUFFER8
 *\*\          - FDCAN_RX_BUFFER9
 *\*\          - FDCAN_RX_BUFFER10
 *\*\          - FDCAN_RX_BUFFER11
 *\*\          - FDCAN_RX_BUFFER12
 *\*\          - FDCAN_RX_BUFFER13
 *\*\          - FDCAN_RX_BUFFER14
 *\*\          - FDCAN_RX_BUFFER15
 *\*\          - FDCAN_RX_BUFFER16
 *\*\          - FDCAN_RX_BUFFER17
 *\*\          - FDCAN_RX_BUFFER18
 *\*\          - FDCAN_RX_BUFFER19
 *\*\          - FDCAN_RX_BUFFER20
 *\*\          - FDCAN_RX_BUFFER21
 *\*\          - FDCAN_RX_BUFFER22
 *\*\          - FDCAN_RX_BUFFER23
 *\*\          - FDCAN_RX_BUFFER24
 *\*\          - FDCAN_RX_BUFFER25
 *\*\          - FDCAN_RX_BUFFER26
 *\*\          - FDCAN_RX_BUFFER27
 *\*\          - FDCAN_RX_BUFFER28
 *\*\          - FDCAN_RX_BUFFER29
 *\*\          - FDCAN_RX_BUFFER30
 *\*\          - FDCAN_RX_BUFFER31
 *\*\          - FDCAN_RX_BUFFER32
 *\*\          - FDCAN_RX_BUFFER33
 *\*\          - FDCAN_RX_BUFFER34
 *\*\          - FDCAN_RX_BUFFER35
 *\*\          - FDCAN_RX_BUFFER36
 *\*\          - FDCAN_RX_BUFFER37
 *\*\          - FDCAN_RX_BUFFER38
 *\*\          - FDCAN_RX_BUFFER39
 *\*\          - FDCAN_RX_BUFFER40
 *\*\          - FDCAN_RX_BUFFER41
 *\*\          - FDCAN_RX_BUFFER42
 *\*\          - FDCAN_RX_BUFFER43
 *\*\          - FDCAN_RX_BUFFER44
 *\*\          - FDCAN_RX_BUFFER45
 *\*\          - FDCAN_RX_BUFFER46
 *\*\          - FDCAN_RX_BUFFER47
 *\*\          - FDCAN_RX_BUFFER48
 *\*\          - FDCAN_RX_BUFFER49
 *\*\          - FDCAN_RX_BUFFER50
 *\*\          - FDCAN_RX_BUFFER51
 *\*\          - FDCAN_RX_BUFFER52
 *\*\          - FDCAN_RX_BUFFER53
 *\*\          - FDCAN_RX_BUFFER54
 *\*\          - FDCAN_RX_BUFFER55
 *\*\          - FDCAN_RX_BUFFER56
 *\*\          - FDCAN_RX_BUFFER57
 *\*\          - FDCAN_RX_BUFFER58
 *\*\          - FDCAN_RX_BUFFER59
 *\*\          - FDCAN_RX_BUFFER60
 *\*\          - FDCAN_RX_BUFFER61
 *\*\          - FDCAN_RX_BUFFER62
 *\*\          - FDCAN_RX_BUFFER63
 *\*\return ErrorStatus
 *\*\          - ERROR : No new message on RxBufferIndex.
 *\*\          - SUCCESS : New message received on RxBufferIndex.
 */
ErrorStatus FDCAN_CheckNewRxBufMsg(FDCAN_Module *FDCANx, uint32_t Index)
{
    __IO uint32_t *pReg;
    uint32_t IndexBit;

    /* Get new data register point according to the Rx Buffer Index */
    if(Index < FDCAN_RX_BUFFER32)
    {
        pReg = &(FDCANx->NDAT1);
    }
    else /* FDCAN_RX_BUFFER32 <= Index <= FDCAN_RX_BUFFER63 */
    {
        pReg = &(FDCANx->NDAT2);
    }

    /* Check if the new data flag is set or not. */
    IndexBit = (0x1UL) << (Index & 0x1FUL);

    if(0UL == (*pReg & IndexBit))
    {
        return ERROR;
    }

    /* Clear the new data flag. */
    *pReg = IndexBit;

    return SUCCESS;
}

/**
 *\*\name   FDCAN_CheckTxBufRequest.
 *\*\fun    Check if a transmission request is pending on the selected Tx buffer.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  IndexBit Rx buffer index bit.
 *\*\          - FDCAN_TX_BUFFER0
 *\*\          - FDCAN_TX_BUFFER1
 *\*\          - FDCAN_TX_BUFFER2
 *\*\          - FDCAN_TX_BUFFER3
 *\*\          - FDCAN_TX_BUFFER4
 *\*\          - FDCAN_TX_BUFFER5
 *\*\          - FDCAN_TX_BUFFER6
 *\*\          - FDCAN_TX_BUFFER7
 *\*\          - FDCAN_TX_BUFFER8
 *\*\          - FDCAN_TX_BUFFER9
 *\*\          - FDCAN_TX_BUFFER10
 *\*\          - FDCAN_TX_BUFFER11
 *\*\          - FDCAN_TX_BUFFER12
 *\*\          - FDCAN_TX_BUFFER13
 *\*\          - FDCAN_TX_BUFFER14
 *\*\          - FDCAN_TX_BUFFER15
 *\*\          - FDCAN_TX_BUFFER16
 *\*\          - FDCAN_TX_BUFFER17
 *\*\          - FDCAN_TX_BUFFER18
 *\*\          - FDCAN_TX_BUFFER19
 *\*\          - FDCAN_TX_BUFFER20
 *\*\          - FDCAN_TX_BUFFER21
 *\*\          - FDCAN_TX_BUFFER22
 *\*\          - FDCAN_TX_BUFFER23
 *\*\          - FDCAN_TX_BUFFER24
 *\*\          - FDCAN_TX_BUFFER25
 *\*\          - FDCAN_TX_BUFFER26
 *\*\          - FDCAN_TX_BUFFER27
 *\*\          - FDCAN_TX_BUFFER28
 *\*\          - FDCAN_TX_BUFFER29
 *\*\          - FDCAN_TX_BUFFER30
 *\*\          - FDCAN_TX_BUFFER31
 *\*\return Status
 *\*\          - ERROR : No request pending on TxBufferIndex.
 *\*\          - SUCCESS : Have request pending on RxBufferIndex.
 */
FlagStatus FDCAN_CheckTxBufRequest(FDCAN_Module *FDCANx, uint32_t IndexBit)
{
    FlagStatus status_value;

    /* Check pending transmission request on the selected buffer */
    if (0UL == (FDCANx->TXBRP & IndexBit))
    {
        status_value = RESET;
    }
    else
    {
        status_value = SET;
    }

    return status_value;
}

/**
 *\*\name   FDCAN_CheckBufTxResult.
 *\*\fun    Check if a transmission is sent or not.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  IndexBit Rx buffer index bit.
 *\*\          - FDCAN_TX_BUFFER0
 *\*\          - FDCAN_TX_BUFFER1
 *\*\          - FDCAN_TX_BUFFER2
 *\*\          - FDCAN_TX_BUFFER3
 *\*\          - FDCAN_TX_BUFFER4
 *\*\          - FDCAN_TX_BUFFER5
 *\*\          - FDCAN_TX_BUFFER6
 *\*\          - FDCAN_TX_BUFFER7
 *\*\          - FDCAN_TX_BUFFER8
 *\*\          - FDCAN_TX_BUFFER9
 *\*\          - FDCAN_TX_BUFFER10
 *\*\          - FDCAN_TX_BUFFER11
 *\*\          - FDCAN_TX_BUFFER12
 *\*\          - FDCAN_TX_BUFFER13
 *\*\          - FDCAN_TX_BUFFER14
 *\*\          - FDCAN_TX_BUFFER15
 *\*\          - FDCAN_TX_BUFFER16
 *\*\          - FDCAN_TX_BUFFER17
 *\*\          - FDCAN_TX_BUFFER18
 *\*\          - FDCAN_TX_BUFFER19
 *\*\          - FDCAN_TX_BUFFER20
 *\*\          - FDCAN_TX_BUFFER21
 *\*\          - FDCAN_TX_BUFFER22
 *\*\          - FDCAN_TX_BUFFER23
 *\*\          - FDCAN_TX_BUFFER24
 *\*\          - FDCAN_TX_BUFFER25
 *\*\          - FDCAN_TX_BUFFER26
 *\*\          - FDCAN_TX_BUFFER27
 *\*\          - FDCAN_TX_BUFFER28
 *\*\          - FDCAN_TX_BUFFER29
 *\*\          - FDCAN_TX_BUFFER30
 *\*\          - FDCAN_TX_BUFFER31
 *\*\return Status
 *\*\          - ERROR : Transmission is not finished or cacelled.
 *\*\          - SUCCESS : Transmission is finished.
 */
FlagStatus FDCAN_CheckBufTxResult(FDCAN_Module *FDCANx, uint32_t IndexBit)
{
    FlagStatus status_value;

    /* Check pending transmission request on the selected buffer */
    if (0UL == (FDCANx->TXBTO & IndexBit))
    {
        status_value = RESET;
    }
    else
    {
        status_value = SET;
    }

    return status_value;
}

/**
 *\*\name   FDCAN_CheckBufTxCancel.
 *\*\fun    Check if a transmission is cancelled.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  IndexBit Rx buffer index bit.
 *\*\          - FDCAN_TX_BUFFER0
 *\*\          - FDCAN_TX_BUFFER1
 *\*\          - FDCAN_TX_BUFFER2
 *\*\          - FDCAN_TX_BUFFER3
 *\*\          - FDCAN_TX_BUFFER4
 *\*\          - FDCAN_TX_BUFFER5
 *\*\          - FDCAN_TX_BUFFER6
 *\*\          - FDCAN_TX_BUFFER7
 *\*\          - FDCAN_TX_BUFFER8
 *\*\          - FDCAN_TX_BUFFER9
 *\*\          - FDCAN_TX_BUFFER10
 *\*\          - FDCAN_TX_BUFFER11
 *\*\          - FDCAN_TX_BUFFER12
 *\*\          - FDCAN_TX_BUFFER13
 *\*\          - FDCAN_TX_BUFFER14
 *\*\          - FDCAN_TX_BUFFER15
 *\*\          - FDCAN_TX_BUFFER16
 *\*\          - FDCAN_TX_BUFFER17
 *\*\          - FDCAN_TX_BUFFER18
 *\*\          - FDCAN_TX_BUFFER19
 *\*\          - FDCAN_TX_BUFFER20
 *\*\          - FDCAN_TX_BUFFER21
 *\*\          - FDCAN_TX_BUFFER22
 *\*\          - FDCAN_TX_BUFFER23
 *\*\          - FDCAN_TX_BUFFER24
 *\*\          - FDCAN_TX_BUFFER25
 *\*\          - FDCAN_TX_BUFFER26
 *\*\          - FDCAN_TX_BUFFER27
 *\*\          - FDCAN_TX_BUFFER28
 *\*\          - FDCAN_TX_BUFFER29
 *\*\          - FDCAN_TX_BUFFER30
 *\*\          - FDCAN_TX_BUFFER31
 *\*\return Status
 *\*\          - ERROR : Transmission is not cacelled.
 *\*\          - SUCCESS : Transmission is cacelled.
 */
FlagStatus FDCAN_CheckBufTxCancel(FDCAN_Module *FDCANx, uint32_t IndexBit)
{
    FlagStatus status_value;

    /* Check pending transmission request on the selected buffer */
    if (0UL == (FDCANx->TXBCF & IndexBit))
    {
        status_value = RESET;
    }
    else
    {
        status_value = SET;
    }

    return status_value;
}

/**
 *\*\name   FDCAN_GetRxFifoFillLevel.
 *\*\fun    Return Rx FIFO fill level.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  RxFifo :
 *\*\          - FDCAN_RX_FIFO0
 *\*\          - FDCAN_RX_FIFO1
 *\*\return Rx FIFO fill level.
 */
uint32_t FDCAN_GetRxFifoFillLevel(FDCAN_Module *FDCANx, uint32_t RxFifo)
{
    uint32_t FillLevel;

    if (RxFifo == FDCAN_RX_FIFO0)
    {
        FillLevel = FDCANx->RXF0S & FDCAN_RXF0S_F0FL;
    }
    else /* RxFifo == FDCAN_RX_FIFO1 */
    {
        FillLevel = FDCANx->RXF1S & FDCAN_RXF1S_F1FL;
    }

    /* Return Rx FIFO fill level */
    return FillLevel;
}

/**
 *\*\name   FDCAN_GetTxFifoFreeLevel.
 *\*\fun    Return Tx FIFO free level: number of consecutive free Tx FIFO.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return Tx FIFO free level.
 */
uint32_t FDCAN_GetTxFifoFreeLevel(FDCAN_Module *FDCANx)
{
    uint32_t FreeLevel;

    FreeLevel = FDCANx->TXFQS & FDCAN_TXFQS_TFFL;

    /* Return Tx FIFO free level */
    return FreeLevel;
}

/**
 *\*\name   FDCAN_CheckRestrictedMode.
 *\*\fun    Check if the FDCAN peripheral entered Restricted Operation Mode.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return Status
 *\*\          - FDCAN_MODE_NORMAL : Normal FDCAN operation.
 *\*\          - FDCAN_MODE_RESTRICTED_OPERATION : Restricted Operation Mode active.
 */
uint32_t FDCAN_CheckRestrictedMode(FDCAN_Module *FDCANx)
{
    uint32_t OperationMode;

    /* Get Operation Mode */
    OperationMode = (FDCANx->CCCR & FDCAN_CCCR_ASM);

    return OperationMode;
}

/**
 *\*\name   FDCAN_ExitRestrictedMode.
 *\*\fun    Exit Restricted Operation Mode.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return none
 */
void FDCAN_ExitRestrictedMode(FDCAN_Module *FDCANx)
{
    /* Exit Restricted Operation mode */
    FDCANx->CCCR &= ~FDCAN_CCCR_ASM;
}

/**
 *\*\name   FDCAN_ConfigIntLine.
 *\*\fun    Assign interrupts to either Interrupt line 0 or 1.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  Int :
 *\*\          - FDCAN_INT_RX_FIFO0_NEW_MESSAGE
 *\*\          - FDCAN_INT_RX_FIFO0_WATERMARK
 *\*\          - FDCAN_INT_RX_FIFO0_FULL
 *\*\          - FDCAN_INT_RX_FIFO0_MESSAGE_LOST
 *\*\          - FDCAN_INT_RX_FIFO1_NEW_MESSAGE
 *\*\          - FDCAN_INT_RX_FIFO1_WATERMARK
 *\*\          - FDCAN_INT_RX_FIFO1_FULL
 *\*\          - FDCAN_INT_RX_FIFO1_MESSAGE_LOST
 *\*\          - FDCAN_INT_RX_HIGH_PRIORITY_MSG
 *\*\          - FDCAN_INT_TX_COMPLETE
 *\*\          - FDCAN_INT_TX_ABORT_COMPLETE
 *\*\          - FDCAN_INT_TX_FIFO_EMPTY
 *\*\          - FDCAN_INT_TX_EVT_FIFO_NEW_DATA
 *\*\          - FDCAN_INT_TX_EVT_FIFO_WATERMARK
 *\*\          - FDCAN_INT_TX_EVT_FIFO_FULL
 *\*\          - FDCAN_INT_TX_EVT_FIFO_ELT_LOST
 *\*\          - FDCAN_INT_TIMESTAMP_WRAPAROUND
 *\*\          - FDCAN_INT_RAM_ACCESS_FAILURE
 *\*\          - FDCAN_INT_TIMEOUT_OCCURRED
 *\*\          - FDCAN_INT_RX_BUFFER_NEW_MESSAGE
 *\*\          - FDCAN_INT_BITERROR_CORRECTED
 *\*\          - FDCAN_INT_BITERROR_UNCORRECTED
 *\*\          - FDCAN_INT_ERROR_LOGGING_OVERFLOW
 *\*\          - FDCAN_INT_ERROR_PASSIVE
 *\*\          - FDCAN_INT_ERROR_WARNING
 *\*\          - FDCAN_INT_BUS_OFF
 *\*\          - FDCAN_INT_RAM_WATCHDOG
 *\*\          - FDCAN_INT_ARB_PROTOCOL_ERROR
 *\*\          - FDCAN_INT_DATA_PROTOCOL_ERROR
 *\*\          - FDCAN_INT_RESERVED_ADDRESS_ACCESS
 *\*\param  IntLine :
 *\*\          - FDCAN_INTERRUPT_LINE0
 *\*\          - FDCAN_INTERRUPT_LINE1
 *\*\return none
 */
void FDCAN_ConfigIntLine(FDCAN_Module *FDCANx, uint32_t Int, uint32_t IntLine)
{
    /* Assign list of interrupts to the selected line */
    if (IntLine == FDCAN_INTERRUPT_LINE0)
    {
        FDCANx->ILS &= (~Int);
    }
    else /* IntLine == FDCAN_INTERRUPT_LINE1 */
    {
        FDCANx->ILS |= Int;
    }
}

/**
 *\*\name   FDCAN_EnableInt.
 *\*\fun    Enable the specified FDCAN interrupts.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  Int :
 *\*\          - FDCAN_INT_RX_FIFO0_NEW_MESSAGE
 *\*\          - FDCAN_INT_RX_FIFO0_WATERMARK
 *\*\          - FDCAN_INT_RX_FIFO0_FULL
 *\*\          - FDCAN_INT_RX_FIFO0_MESSAGE_LOST
 *\*\          - FDCAN_INT_RX_FIFO1_NEW_MESSAGE
 *\*\          - FDCAN_INT_RX_FIFO1_WATERMARK
 *\*\          - FDCAN_INT_RX_FIFO1_FULL
 *\*\          - FDCAN_INT_RX_FIFO1_MESSAGE_LOST
 *\*\          - FDCAN_INT_RX_HIGH_PRIORITY_MSG
 *\*\          - FDCAN_INT_TX_COMPLETE
 *\*\          - FDCAN_INT_TX_ABORT_COMPLETE
 *\*\          - FDCAN_INT_TX_FIFO_EMPTY
 *\*\          - FDCAN_INT_TX_EVT_FIFO_NEW_DATA
 *\*\          - FDCAN_INT_TX_EVT_FIFO_WATERMARK
 *\*\          - FDCAN_INT_TX_EVT_FIFO_FULL
 *\*\          - FDCAN_INT_TX_EVT_FIFO_ELT_LOST
 *\*\          - FDCAN_INT_TIMESTAMP_WRAPAROUND
 *\*\          - FDCAN_INT_RAM_ACCESS_FAILURE
 *\*\          - FDCAN_INT_TIMEOUT_OCCURRED
 *\*\          - FDCAN_INT_RX_BUFFER_NEW_MESSAGE
 *\*\          - FDCAN_INT_BITERROR_CORRECTED
 *\*\          - FDCAN_INT_BITERROR_UNCORRECTED
 *\*\          - FDCAN_INT_ERROR_LOGGING_OVERFLOW
 *\*\          - FDCAN_INT_ERROR_PASSIVE
 *\*\          - FDCAN_INT_ERROR_WARNING
 *\*\          - FDCAN_INT_BUS_OFF
 *\*\          - FDCAN_INT_RAM_WATCHDOG
 *\*\          - FDCAN_INT_ARB_PROTOCOL_ERROR
 *\*\          - FDCAN_INT_DATA_PROTOCOL_ERROR
 *\*\          - FDCAN_INT_RESERVED_ADDRESS_ACCESS
 *\*\return none
 */
void FDCAN_EnableInt(FDCAN_Module *FDCANx, uint32_t Int)
{
    FDCANx->IE |= Int;
}

/**
 *\*\name   FDCAN_DisableInt.
 *\*\fun    Disable the specified FDCAN interrupts.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  Int :
 *\*\          - FDCAN_INT_RX_FIFO0_NEW_MESSAGE
 *\*\          - FDCAN_INT_RX_FIFO0_WATERMARK
 *\*\          - FDCAN_INT_RX_FIFO0_FULL
 *\*\          - FDCAN_INT_RX_FIFO0_MESSAGE_LOST
 *\*\          - FDCAN_INT_RX_FIFO1_NEW_MESSAGE
 *\*\          - FDCAN_INT_RX_FIFO1_WATERMARK
 *\*\          - FDCAN_INT_RX_FIFO1_FULL
 *\*\          - FDCAN_INT_RX_FIFO1_MESSAGE_LOST
 *\*\          - FDCAN_INT_RX_HIGH_PRIORITY_MSG
 *\*\          - FDCAN_INT_TX_COMPLETE
 *\*\          - FDCAN_INT_TX_ABORT_COMPLETE
 *\*\          - FDCAN_INT_TX_FIFO_EMPTY
 *\*\          - FDCAN_INT_TX_EVT_FIFO_NEW_DATA
 *\*\          - FDCAN_INT_TX_EVT_FIFO_WATERMARK
 *\*\          - FDCAN_INT_TX_EVT_FIFO_FULL
 *\*\          - FDCAN_INT_TX_EVT_FIFO_ELT_LOST
 *\*\          - FDCAN_INT_TIMESTAMP_WRAPAROUND
 *\*\          - FDCAN_INT_RAM_ACCESS_FAILURE
 *\*\          - FDCAN_INT_TIMEOUT_OCCURRED
 *\*\          - FDCAN_INT_RX_BUFFER_NEW_MESSAGE
 *\*\          - FDCAN_INT_BITERROR_CORRECTED
 *\*\          - FDCAN_INT_BITERROR_UNCORRECTED
 *\*\          - FDCAN_INT_ERROR_LOGGING_OVERFLOW
 *\*\          - FDCAN_INT_ERROR_PASSIVE
 *\*\          - FDCAN_INT_ERROR_WARNING
 *\*\          - FDCAN_INT_BUS_OFF
 *\*\          - FDCAN_INT_RAM_WATCHDOG
 *\*\          - FDCAN_INT_ARB_PROTOCOL_ERROR
 *\*\          - FDCAN_INT_DATA_PROTOCOL_ERROR
 *\*\          - FDCAN_INT_RESERVED_ADDRESS_ACCESS
 *\*\return none
 */
void FDCAN_DisableInt(FDCAN_Module *FDCANx, uint32_t Int)
{
    FDCANx->IE &= (~Int);
}

/**
 *\*\name   FDCAN_GetIntFlag.
 *\*\fun    Check whether the specified FDCAN interrupt is set or not.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  Flag :
 *\*\          - FDCAN_FLAG_RESERVED_ADDRESS_ACCESS
 *\*\          - FDCAN_FLAG_DATA_PROTOCOL_ERROR
 *\*\          - FDCAN_FLAG_ARB_PROTOCOL_ERROR
 *\*\          - FDCAN_FLAG_RAM_WATCHDOG
 *\*\          - FDCAN_FLAG_BUS_OFF
 *\*\          - FDCAN_FLAG_ERROR_WARNING
 *\*\          - FDCAN_FLAG_ERROR_PASSIVE
 *\*\          - FDCAN_FLAG_ERROR_LOGGING_OVERFLOW
 *\*\          - FDCAN_FLAG_BITERROR_UNCORRECTED
 *\*\          - FDCAN_FLAG_BITERROR_CORRECTED
 *\*\          - FDCAN_FLAG_RX_BUFFER_NEW_MESSAGE
 *\*\          - FDCAN_FLAG_TIMEOUT_OCCURRED
 *\*\          - FDCAN_FLAG_RAM_ACCESS_FAILURE
 *\*\          - FDCAN_FLAG_TIMESTAMP_WRAPAROUND
 *\*\          - FDCAN_FLAG_TX_EVT_FIFO_ELT_LOST
 *\*\          - FDCAN_FLAG_TX_EVT_FIFO_FULL
 *\*\          - FDCAN_FLAG_TX_EVT_FIFO_WATERMARK
 *\*\          - FDCAN_FLAG_TX_EVT_FIFO_NEW_DATA
 *\*\          - FDCAN_FLAG_TX_FIFO_EMPTY
 *\*\          - FDCAN_FLAG_TX_ABORT_COMPLETE
 *\*\          - FDCAN_FLAG_TX_COMPLETE
 *\*\          - FDCAN_FLAG_RX_HIGH_PRIORITY_MSG
 *\*\          - FDCAN_FLAG_RX_FIFO1_MESSAGE_LOST
 *\*\          - FDCAN_FLAG_RX_FIFO1_FULL
 *\*\          - FDCAN_FLAG_RX_FIFO1_WATERMARK
 *\*\          - FDCAN_FLAG_RX_FIFO1_NEW_MESSAGE
 *\*\          - FDCAN_FLAG_RX_FIFO0_MESSAGE_LOST
 *\*\          - FDCAN_FLAG_RX_FIFO0_FULL
 *\*\          - FDCAN_FLAG_RX_FIFO0_WATERMARK
 *\*\          - FDCAN_FLAG_RX_FIFO0_NEW_MESSAGE
 *\*\return FlagStatus
 *\*\          - RESET
 *\*\          - SET
 */
FlagStatus FDCAN_GetIntFlag(FDCAN_Module *FDCANx, uint32_t Flag)
{
    FlagStatus status_value = SET;

    /* Check whether the specified FDCAN interrupt is enable or not. */
    if((FDCANx->IE & Flag) != Flag )
    {
        status_value = RESET;
    }

    /* Check whether the specified FDCAN interrupt flag is set or not. */
    if((FDCANx->IR & Flag) != Flag )
    {
        status_value = RESET;
    }

    return status_value;
}

/**
 *\*\name   FDCAN_GetFlag.
 *\*\fun    Check whether the specified FDCAN flag is set or not.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  Flag :
 *\*\          - FDCAN_FLAG_RESERVED_ADDRESS_ACCESS
 *\*\          - FDCAN_FLAG_DATA_PROTOCOL_ERROR
 *\*\          - FDCAN_FLAG_ARB_PROTOCOL_ERROR
 *\*\          - FDCAN_FLAG_RAM_WATCHDOG
 *\*\          - FDCAN_FLAG_BUS_OFF
 *\*\          - FDCAN_FLAG_ERROR_WARNING
 *\*\          - FDCAN_FLAG_ERROR_PASSIVE
 *\*\          - FDCAN_FLAG_ERROR_LOGGING_OVERFLOW
 *\*\          - FDCAN_FLAG_BITERROR_UNCORRECTED
 *\*\          - FDCAN_FLAG_BITERROR_CORRECTED
 *\*\          - FDCAN_FLAG_RX_BUFFER_NEW_MESSAGE
 *\*\          - FDCAN_FLAG_TIMEOUT_OCCURRED
 *\*\          - FDCAN_FLAG_RAM_ACCESS_FAILURE
 *\*\          - FDCAN_FLAG_TIMESTAMP_WRAPAROUND
 *\*\          - FDCAN_FLAG_TX_EVT_FIFO_ELT_LOST
 *\*\          - FDCAN_FLAG_TX_EVT_FIFO_FULL
 *\*\          - FDCAN_FLAG_TX_EVT_FIFO_WATERMARK
 *\*\          - FDCAN_FLAG_TX_EVT_FIFO_NEW_DATA
 *\*\          - FDCAN_FLAG_TX_FIFO_EMPTY
 *\*\          - FDCAN_FLAG_TX_ABORT_COMPLETE
 *\*\          - FDCAN_FLAG_TX_COMPLETE
 *\*\          - FDCAN_FLAG_RX_HIGH_PRIORITY_MSG
 *\*\          - FDCAN_FLAG_RX_FIFO1_MESSAGE_LOST
 *\*\          - FDCAN_FLAG_RX_FIFO1_FULL
 *\*\          - FDCAN_FLAG_RX_FIFO1_WATERMARK
 *\*\          - FDCAN_FLAG_RX_FIFO1_NEW_MESSAGE
 *\*\          - FDCAN_FLAG_RX_FIFO0_MESSAGE_LOST
 *\*\          - FDCAN_FLAG_RX_FIFO0_FULL
 *\*\          - FDCAN_FLAG_RX_FIFO0_WATERMARK
 *\*\          - FDCAN_FLAG_RX_FIFO0_NEW_MESSAGE
 *\*\return FlagStatus
 *\*\          - RESET
 *\*\          - SET
 */
FlagStatus FDCAN_GetFlag(FDCAN_Module *FDCANx, uint32_t Flag)
{
    FlagStatus status_value;

    if((FDCANx->IR & Flag) == Flag )
    {
        status_value = SET;
    }
    else
    {
        status_value = RESET;
    }

    return status_value;
}

/**
 *\*\name   FDCAN_ClearFlag.
 *\*\fun    Clear the specified FDCAN flags.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  Flag :
 *\*\          - FDCAN_FLAG_RESERVED_ADDRESS_ACCESS
 *\*\          - FDCAN_FLAG_DATA_PROTOCOL_ERROR
 *\*\          - FDCAN_FLAG_ARB_PROTOCOL_ERROR
 *\*\          - FDCAN_FLAG_RAM_WATCHDOG
 *\*\          - FDCAN_FLAG_BUS_OFF
 *\*\          - FDCAN_FLAG_ERROR_WARNING
 *\*\          - FDCAN_FLAG_ERROR_PASSIVE
 *\*\          - FDCAN_FLAG_ERROR_LOGGING_OVERFLOW
 *\*\          - FDCAN_FLAG_BITERROR_UNCORRECTED
 *\*\          - FDCAN_FLAG_BITERROR_CORRECTED
 *\*\          - FDCAN_FLAG_RX_BUFFER_NEW_MESSAGE
 *\*\          - FDCAN_FLAG_TIMEOUT_OCCURRED
 *\*\          - FDCAN_FLAG_RAM_ACCESS_FAILURE
 *\*\          - FDCAN_FLAG_TIMESTAMP_WRAPAROUND
 *\*\          - FDCAN_FLAG_TX_EVT_FIFO_ELT_LOST
 *\*\          - FDCAN_FLAG_TX_EVT_FIFO_FULL
 *\*\          - FDCAN_FLAG_TX_EVT_FIFO_WATERMARK
 *\*\          - FDCAN_FLAG_TX_EVT_FIFO_NEW_DATA
 *\*\          - FDCAN_FLAG_TX_FIFO_EMPTY
 *\*\          - FDCAN_FLAG_TX_ABORT_COMPLETE
 *\*\          - FDCAN_FLAG_TX_COMPLETE
 *\*\          - FDCAN_FLAG_RX_HIGH_PRIORITY_MSG
 *\*\          - FDCAN_FLAG_RX_FIFO1_MESSAGE_LOST
 *\*\          - FDCAN_FLAG_RX_FIFO1_FULL
 *\*\          - FDCAN_FLAG_RX_FIFO1_WATERMARK
 *\*\          - FDCAN_FLAG_RX_FIFO1_NEW_MESSAGE
 *\*\          - FDCAN_FLAG_RX_FIFO0_MESSAGE_LOST
 *\*\          - FDCAN_FLAG_RX_FIFO0_FULL
 *\*\          - FDCAN_FLAG_RX_FIFO0_WATERMARK
 *\*\          - FDCAN_FLAG_RX_FIFO0_NEW_MESSAGE
 *\*\return  none
 */
void FDCAN_ClearFlag(FDCAN_Module *FDCANx, uint32_t Flag)
{
    FDCANx->IR = Flag;
}

/**
 *\*\name   FDCAN_ActivateInt.
 *\*\fun    Activate the specified FDCAN interrupts.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  Int :
 *\*\          - FDCAN_INT_RX_FIFO0_NEW_MESSAGE
 *\*\          - FDCAN_INT_RX_FIFO0_WATERMARK
 *\*\          - FDCAN_INT_RX_FIFO0_FULL
 *\*\          - FDCAN_INT_RX_FIFO0_MESSAGE_LOST
 *\*\          - FDCAN_INT_RX_FIFO1_NEW_MESSAGE
 *\*\          - FDCAN_INT_RX_FIFO1_WATERMARK
 *\*\          - FDCAN_INT_RX_FIFO1_FULL
 *\*\          - FDCAN_INT_RX_FIFO1_MESSAGE_LOST
 *\*\          - FDCAN_INT_RX_HIGH_PRIORITY_MSG
 *\*\          - FDCAN_INT_TX_COMPLETE
 *\*\          - FDCAN_INT_TX_ABORT_COMPLETE
 *\*\          - FDCAN_INT_TX_FIFO_EMPTY
 *\*\          - FDCAN_INT_TX_EVT_FIFO_NEW_DATA
 *\*\          - FDCAN_INT_TX_EVT_FIFO_WATERMARK
 *\*\          - FDCAN_INT_TX_EVT_FIFO_FULL
 *\*\          - FDCAN_INT_TX_EVT_FIFO_ELT_LOST
 *\*\          - FDCAN_INT_TIMESTAMP_WRAPAROUND
 *\*\          - FDCAN_INT_RAM_ACCESS_FAILURE
 *\*\          - FDCAN_INT_TIMEOUT_OCCURRED
 *\*\          - FDCAN_INT_RX_BUFFER_NEW_MESSAGE
 *\*\          - FDCAN_INT_BITERROR_CORRECTED
 *\*\          - FDCAN_INT_BITERROR_UNCORRECTED
 *\*\          - FDCAN_INT_ERROR_LOGGING_OVERFLOW
 *\*\          - FDCAN_INT_ERROR_PASSIVE
 *\*\          - FDCAN_INT_ERROR_WARNING
 *\*\          - FDCAN_INT_BUS_OFF
 *\*\          - FDCAN_INT_RAM_WATCHDOG
 *\*\          - FDCAN_INT_ARB_PROTOCOL_ERROR
 *\*\          - FDCAN_INT_DATA_PROTOCOL_ERROR
 *\*\          - FDCAN_INT_RESERVED_ADDRESS_ACCESS
 *\*\param  BufferIndexes :
 *\*\          - FDCAN_TX_BUFFER0
 *\*\          - FDCAN_TX_BUFFER1
 *\*\          - FDCAN_TX_BUFFER2
 *\*\          - FDCAN_TX_BUFFER3
 *\*\          - FDCAN_TX_BUFFER4
 *\*\          - FDCAN_TX_BUFFER5
 *\*\          - FDCAN_TX_BUFFER6
 *\*\          - FDCAN_TX_BUFFER7
 *\*\          - FDCAN_TX_BUFFER8
 *\*\          - FDCAN_TX_BUFFER9
 *\*\          - FDCAN_TX_BUFFER10
 *\*\          - FDCAN_TX_BUFFER11
 *\*\          - FDCAN_TX_BUFFER12
 *\*\          - FDCAN_TX_BUFFER13
 *\*\          - FDCAN_TX_BUFFER14
 *\*\          - FDCAN_TX_BUFFER15
 *\*\          - FDCAN_TX_BUFFER16
 *\*\          - FDCAN_TX_BUFFER17
 *\*\          - FDCAN_TX_BUFFER18
 *\*\          - FDCAN_TX_BUFFER19
 *\*\          - FDCAN_TX_BUFFER20
 *\*\          - FDCAN_TX_BUFFER21
 *\*\          - FDCAN_TX_BUFFER22
 *\*\          - FDCAN_TX_BUFFER23
 *\*\          - FDCAN_TX_BUFFER24
 *\*\          - FDCAN_TX_BUFFER25
 *\*\          - FDCAN_TX_BUFFER26
 *\*\          - FDCAN_TX_BUFFER27
 *\*\          - FDCAN_TX_BUFFER28
 *\*\          - FDCAN_TX_BUFFER29
 *\*\          - FDCAN_TX_BUFFER30
 *\*\          - FDCAN_TX_BUFFER31
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_ActivateInt(FDCAN_Module *FDCANx, uint32_t Int, uint32_t BufferIndexes)
{
    /* Check ActiveITs */
    if((Int & FDCAN_INT_MASK) == 0UL)
    {
        return ERROR;
    }

    /* Enable Interrupt lines */
    if ((Int & FDCANx->ILS) == 0UL)
    {
        /* Enable Interrupt line 0 */
        FDCANx->ILE |= FDCAN_INTERRUPT_LINE0;
    }
    else if ((Int & FDCANx->ILS) == Int)
    {
        /* Enable Interrupt line 1 */
        FDCANx->ILE |= FDCAN_INTERRUPT_LINE1;
    }
    else
    {
        /* Enable Interrupt lines 0 and 1 */
        FDCANx->ILE = (FDCAN_INTERRUPT_LINE0 | FDCAN_INTERRUPT_LINE1);
    }

    if ((Int & FDCAN_INT_TX_COMPLETE) != 0U)
    {
        /* Enable Tx Buffer Transmission Interrupt to set TC flag in IR register,
            but interrupt will only occur if TC is enabled in IE register */
        FDCANx->TXBTIE |= BufferIndexes;
    }

    if ((Int & FDCAN_INT_TX_ABORT_COMPLETE) != 0U)
    {
        /* Enable Tx Buffer Cancellation Finished Interrupt to set TCF flag in IR register,
            but interrupt will only occur if TCF is enabled in IE register */
        FDCANx->TXBCIE |= BufferIndexes;
    }

    /* Enable the selected interrupts */
    FDCAN_EnableInt(FDCANx, Int);

    /* Return function status */
    return SUCCESS;
}

/**
 *\*\name   FDCAN_DeactivateInt.
 *\*\fun    Deactivate the specified FDCAN interrupts.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  Int :
 *\*\          - FDCAN_INT_RX_FIFO0_NEW_MESSAGE
 *\*\          - FDCAN_INT_RX_FIFO0_WATERMARK
 *\*\          - FDCAN_INT_RX_FIFO0_FULL
 *\*\          - FDCAN_INT_RX_FIFO0_MESSAGE_LOST
 *\*\          - FDCAN_INT_RX_FIFO1_NEW_MESSAGE
 *\*\          - FDCAN_INT_RX_FIFO1_WATERMARK
 *\*\          - FDCAN_INT_RX_FIFO1_FULL
 *\*\          - FDCAN_INT_RX_FIFO1_MESSAGE_LOST
 *\*\          - FDCAN_INT_RX_HIGH_PRIORITY_MSG
 *\*\          - FDCAN_INT_TX_COMPLETE
 *\*\          - FDCAN_INT_TX_ABORT_COMPLETE
 *\*\          - FDCAN_INT_TX_FIFO_EMPTY
 *\*\          - FDCAN_INT_TX_EVT_FIFO_NEW_DATA
 *\*\          - FDCAN_INT_TX_EVT_FIFO_WATERMARK
 *\*\          - FDCAN_INT_TX_EVT_FIFO_FULL
 *\*\          - FDCAN_INT_TX_EVT_FIFO_ELT_LOST
 *\*\          - FDCAN_INT_TIMESTAMP_WRAPAROUND
 *\*\          - FDCAN_INT_RAM_ACCESS_FAILURE
 *\*\          - FDCAN_INT_TIMEOUT_OCCURRED
 *\*\          - FDCAN_INT_RX_BUFFER_NEW_MESSAGE
 *\*\          - FDCAN_INT_BITERROR_CORRECTED
 *\*\          - FDCAN_INT_BITERROR_UNCORRECTED
 *\*\          - FDCAN_INT_ERROR_LOGGING_OVERFLOW
 *\*\          - FDCAN_INT_ERROR_PASSIVE
 *\*\          - FDCAN_INT_ERROR_WARNING
 *\*\          - FDCAN_INT_BUS_OFF
 *\*\          - FDCAN_INT_RAM_WATCHDOG
 *\*\          - FDCAN_INT_ARB_PROTOCOL_ERROR
 *\*\          - FDCAN_INT_DATA_PROTOCOL_ERROR
 *\*\          - FDCAN_INT_RESERVED_ADDRESS_ACCESS
 *\*\return none
 */
void FDCAN_DeactivateInt(FDCAN_Module *FDCANx, uint32_t Int)
{
    uint32_t IntLine;
    uint32_t tempReg;

    /* Disable the selected interrupts */
    FDCAN_DisableInt(FDCANx, Int);

    if ((Int & FDCAN_INT_TX_COMPLETE) != 0U)
    {
        /* Disable Tx Buffer Transmission Interrupts */
        FDCANx->TXBTIE = 0;
    }

    if ((Int & FDCAN_INT_TX_ABORT_COMPLETE) != 0U)
    {
        /* Disable Tx Buffer Cancellation Finished Interrupt */
        FDCANx->TXBCIE = 0;
    }

    IntLine = FDCANx->ILS;
    tempReg = FDCANx->ILE;

    if ((FDCANx->IE | IntLine) == IntLine)
    {
        /* Disable Interrupt line 0 */
        tempReg &= (~FDCAN_INTERRUPT_LINE0);
    }

    if ((FDCANx->IE & IntLine) == 0U)
    {
        /* Disable Interrupt line 1 */
        tempReg &= (~FDCAN_INTERRUPT_LINE1);
    }

    FDCANx->ILE = tempReg;
}



/**
 *\*\name   FDCAN_TT_Init.
 *\*\fun    Initialize TT operation parameters.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\param  pTTParams pointer to a FDCAN_TT_InitType structure.
 *\*\          - uint32_t OperationMode
 *\*\               - FDCAN_TT_COMMUNICATION_LEVEL1
 *\*\               - FDCAN_TT_COMMUNICATION_LEVEL2
 *\*\               - FDCAN_TT_COMMUNICATION_LEVEL0
 *\*\          - uint32_t GapEnable
 *\*\               - FDCAN_STRICTLY_TT_OPERATION
 *\*\               - FDCAN_EXT_EVT_SYNC_TT_OPERATION
 *\*\          - uint32_t TimeMaster
 *\*\               - FDCAN_TT_SLAVE
 *\*\               - FDCAN_TT_POTENTIAL_MASTER
 *\*\          - uint32_t SyncDevLimit
 *\*\               This parameter must be a value between 0 and 7
 *\*\          - uint32_t InitRefTrigOffset
 *\*\               This parameter must be a value between 0 and 127
 *\*\          - uint32_t ExternalClkSync
 *\*\               - FDCAN_TT_EXT_CLK_SYNC_DISABLE
 *\*\               - FDCAN_TT_EXT_CLK_SYNC_ENABLE
 *\*\               This parameter is ignored if OperationMode is FDCAN_TT_COMMUNICATION_LEVEL1
 *\*\          - uint32_t AppWdgLimit
 *\*\               This parameter must be a value between 0 and 255.
 *\*\               This parameter is ignored if OperationMode is FDCAN_TT_COMMUNICATION_LEVEL0
 *\*\          - uint32_t GlobalTimeFilter
 *\*\               - FDCAN_TT_GLOB_TIME_FILT_DISABLE
 *\*\               - FDCAN_TT_GLOB_TIME_FILT_ENABLE
 *\*\               This parameter is ignored if OperationMode is set to FDCAN_TT_COMMUNICATION_LEVEL1
 *\*\          - uint32_t ClockCalibration
 *\*\               - FDCAN_TT_AUTO_CLK_CALIB_DISABLE
 *\*\               - FDCAN_TT_AUTO_CLK_CALIB_ENABLE
 *\*\               This parameter is ignored if OperationMode is set to FDCAN_TT_COMMUNICATION_LEVEL1
 *\*\          - uint32_t EvtTrigPolarity
 *\*\               - FDCAN_TT_EVT_TRIG_POL_RISING
 *\*\               - FDCAN_TT_EVT_TRIG_POL_FALLING
 *\*\               This parameter is ignored if OperationMode is set to FDCAN_TT_COMMUNICATION_LEVEL0
 *\*\          - uint32_t BasicCycles
 *\*\               - FDCAN_TT_CYCLES_PER_MATRIX_1
 *\*\               - FDCAN_TT_CYCLES_PER_MATRIX_2
 *\*\               - FDCAN_TT_CYCLES_PER_MATRIX_4
 *\*\               - FDCAN_TT_CYCLES_PER_MATRIX_8
 *\*\               - FDCAN_TT_CYCLES_PER_MATRIX_16
 *\*\               - FDCAN_TT_CYCLES_PER_MATRIX_32
 *\*\               - FDCAN_TT_CYCLES_PER_MATRIX_64
 *\*\          - uint32_t CycleStartSync
 *\*\               - FDCAN_TT_NO_SYNC_PULSE
 *\*\               - FDCAN_TT_SYNC_BASIC_CYCLE_START
 *\*\               - FDCAN_TT_SYNC_MATRIX_START
 *\*\          - uint32_t TxEnableWindow
 *\*\               This parameter must be a value between 1 and 16
 *\*\          - uint32_t ExpTxTrigSize
 *\*\               This parameter must be a value between 0 and 4095
 *\*\          - uint32_t TURNumerator
 *\*\               This parameter must be a value between 0x10000 and 0x1FFFF
 *\*\          - uint32_t TURDenominator
 *\*\               This parameter must be a value between 0x0001 and 0x3FFF
 *\*\          - uint32_t TrigMemorySize
 *\*\               This parameter must be a value between 0 and 64
 *\*\          - uint32_t StopWatchTrigSel
 *\*\               - FDCAN_TT_STOP_WATCH_TRIGGER_0
 *\*\               - FDCAN_TT_STOP_WATCH_TRIGGER_1
 *\*\               - FDCAN_TT_STOP_WATCH_TRIGGER_2
 *\*\               - FDCAN_TT_STOP_WATCH_TRIGGER_3
 *\*\          - uint32_t EventTrigSel
 *\*\               - FDCAN_TT_EVENT_TRIGGER_0
 *\*\               - FDCAN_TT_EVENT_TRIGGER_1
 *\*\               - FDCAN_TT_EVENT_TRIGGER_2
 *\*\               - FDCAN_TT_EVENT_TRIGGER_3
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_TT_Init(FDCAN_Module *FDCANx, FDCAN_TT_InitType *pTTParams)
{
    uint32_t RAMcounter;
    uint32_t OffsetAddress;
    uint32_t StartAddress;
    uint32_t timeout;
    uint32_t tempReg;
    FDCAN_MsgRamType *pMsg;

    pMsg = pMsgRam[FDCAN_Get_Index(FDCANx)];

    /* Stop local time in order to enable write access to the other bits of TURCF register */
    FDCANx->TURCF &= ~FDCAN_TURCF_ELT;

    /* Wait until the ELT bit into TURCF register is reset */
    timeout = 0;

    while ((FDCANx->TURCF & FDCAN_TURCF_ELT) != 0U)
    {
        if (timeout > FDCAN_TIMEOUT_VALUE)
        {
            return ERROR;
        }

        timeout++;
    }

    /* Configure TUR (Time Unit Ratio) */
    FDCANx->TURCF = (pTTParams->TURNumerator - 0x10000UL)                \
                    |   (pTTParams->TURDenominator << FDCAN_TURCF_DC_OFFSET);

    /* Enable local time */
    FDCANx->TURCF |= FDCAN_TURCF_ELT;

    /* Configure TT operation */
    tempReg =   (pTTParams->OperationMode)                                   \
                |   (pTTParams->TimeMaster)                                      \
                |   (pTTParams->SyncDevLimit << FDCAN_TTOCF_LDSDL_OFFSET)        \
                |   (pTTParams->InitRefTrigOffset << FDCAN_TTOCF_IRTO_OFFSET);

    if (pTTParams->OperationMode != FDCAN_TT_COMMUNICATION_LEVEL0)
    {
        tempReg |=  (pTTParams->GapEnable)                                           \
                    |   (pTTParams->AppWdgLimit << FDCAN_TTOCF_AWL_OFFSET)    \
                    |   (pTTParams->EvtTrigPolarity);
    }

    if (pTTParams->OperationMode != FDCAN_TT_COMMUNICATION_LEVEL1)
    {
        tempReg |=  (pTTParams->ExternalClkSync)    \
                    |   (pTTParams->GlobalTimeFilter)  \
                    |   (pTTParams->ClockCalibration);
    }

    FDCANx->TTOCF = tempReg;

    /* Configure system matrix limits */
    tempReg = pTTParams->CycleStartSync;

    if (pTTParams->OperationMode != FDCAN_TT_COMMUNICATION_LEVEL0)
    {
        tempReg |= ((pTTParams->TxEnableWindow - 1UL) << FDCAN_TTMLM_TXEW_OFFSET);
        tempReg |= (pTTParams->ExpTxTrigSize << FDCAN_TTMLM_ENIT_OFFSET);
    }

    if (pTTParams->TimeMaster == FDCAN_TT_POTENTIAL_MASTER)
    {
        tempReg |= pTTParams->BasicCycles;
    }

    FDCANx->TTMLM = tempReg;

    /* Configure input triggers: Stop watch and Event */
    tempReg = FDCANx->TTSS;
    tempReg &= (~(FDCAN_TTSS_SSWT | FDCAN_TTSS_SEVT));
    tempReg |= (pTTParams->StopWatchTrigSel | pTTParams->EventTrigSel);
    FDCANx->TTSS = tempReg;

    /* Configure trigger memory start address and elements number */
    if((FDCANx->TTSS & FDCAN_START_ADDRESS_RAMSEL) == FDCAN_START_ADDRESS_RAMSEL)
    {
        OffsetAddress = (pMsg->EndAddress - FDCAN_START_ADDRESS_SRAM5BANK2) / 4UL;
        StartAddress = FDCAN_START_ADDRESS_SRAM5BANK2;
    }
    else
    {
        OffsetAddress = (pMsg->EndAddress - FDCAN_START_ADDRESS_SRAM5BANK1) / 4UL;
        StartAddress = FDCAN_START_ADDRESS_SRAM5BANK1;
    }

    FDCANx->TTTMC = (OffsetAddress << FDCAN_START_ADDRESS_OFFSET)                | \
                    (pTTParams->TrigMemorySize << FDCAN_SIZE_NUMBER_OFFSET);

    /* Recalculate End Address */
    pMsg->TTMemoryStrAddr = pMsg->EndAddress;
    pMsg->EndAddress +=  (pTTParams->TrigMemorySize * FDCAN_TT_MEMORY_WORDS * 4UL);

    /* Check end address of the Message RAM */
    if (pMsg->EndAddress > (StartAddress + FDCAN_MESSAGE_RAM_SIZE) )
    {
        return ERROR;
    }

    /* Flush the allocated Message RAM area */
    for (RAMcounter = pMsg->TTMemoryStrAddr; RAMcounter < pMsg->EndAddress; RAMcounter += 4UL)
    {
        *(uint32_t *)(RAMcounter) = 0UL;
    }

    /* Return function status */
    return SUCCESS;
}

/**
 *\*\name   FDCAN_TT_ConfigRefMsg.
 *\*\fun    Configure the reference message.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\param  IdType :
 *\*\          - FDCAN_STANDARD_ID
 *\*\          - FDCAN_EXTENDED_ID
 *\*\param  ID Reference Identifier.
 *\*\       This parameter must be a number between:
 *\*\          - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
 *\*\          - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID
 *\*\param  Payload Enable or disable the additional payload.
 *\*\          - FDCAN_TT_REF_MSG_NO_PAYLOAD
 *\*\          - FDCAN_TT_REF_MSG_ADD_PAYLOAD
 *\*\return none
 */
void FDCAN_TT_ConfigRefMsg(FDCAN_Module *FDCANx, uint32_t IdType, uint32_t ID, uint32_t Payload)
{
    uint32_t id_temp;
    uint32_t tempReg;

    /* Configure reference message identifier type, identifier and payload */
    if (IdType == FDCAN_STANDARD_ID)
    {
        id_temp = ID << FDCAN_TTRMC_STD_ID_OFFSET;
    }
    else
    {
        id_temp = ID;
    }

    tempReg  = FDCANx->TTRMC & (~(FDCAN_TTRMC_RID | FDCAN_TTRMC_XTD | FDCAN_TTRMC_RMPS));
    tempReg |= (id_temp | IdType | Payload);
    FDCANx->TTRMC = tempReg;
}

/**
 *\*\name   FDCAN_TT_ConfigTrigger.
 *\*\fun    Configure the FDCAN trigger according to the specified parameters
 *\*\       in the FDCAN_TriggerType structure.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\param  sTriggerConfig :pointer to an FDCAN_TriggerType structure
 *\*\          - TriggerIndex
 *\*\               This parameter must be a number between 0 and 63
 *\*\          - TimeMark
 *\*\               This parameter must be a number between 0 and 0xFFFF
 *\*\          - RepeatFactor
 *\*\               - FDCAN_TT_REPEAT_EVERY_CYCLE
 *\*\               - FDCAN_TT_REPEAT_EVERY_2ND_CYCLE
 *\*\               - FDCAN_TT_REPEAT_EVERY_4TH_CYCLE
 *\*\               - FDCAN_TT_REPEAT_EVERY_8TH_CYCLE
 *\*\               - FDCAN_TT_REPEAT_EVERY_16TH_CYCLE
 *\*\               - FDCAN_TT_REPEAT_EVERY_32ND_CYCLE
 *\*\               - FDCAN_TT_REPEAT_EVERY_64TH_CYCLE
 *\*\          - StartCycle
 *\*\               This parameter must be a value between 0 and RepeatFactor.
 *\*\               This parameter is ignored if RepeatFactor is set to FDCAN_TT_REPEAT_EVERY_CYCLE.
 *\*\          - TmEventInt
 *\*\               - FDCAN_TT_TM_NO_INTERNAL_EVENT
 *\*\               - FDCAN_TT_TM_GEN_INTERNAL_EVENT
 *\*\          - TmEventExt
 *\*\               - FDCAN_TT_TM_NO_EXTERNAL_EVENT
 *\*\               - FDCAN_TT_TM_GEN_EXTERNAL_EVENT
 *\*\          - TriggerType;
 *\*\               - FDCAN_TT_TX_REF_TRIGGER
 *\*\               - FDCAN_TT_TX_REF_TRIGGER_GAP
 *\*\               - FDCAN_TT_TX_TRIGGER_SINGLE
 *\*\               - FDCAN_TT_TX_TRIGGER_CONTINUOUS
 *\*\               - FDCAN_TT_TX_TRIGGER_ARBITRATION
 *\*\               - FDCAN_TT_TX_TRIGGER_MERGED
 *\*\               - FDCAN_TT_WATCH_TRIGGER
 *\*\               - FDCAN_TT_WATCH_TRIGGER_GAP
 *\*\               - FDCAN_TT_RX_TRIGGER
 *\*\               - FDCAN_TT_TIME_BASE_TRIGGER
 *\*\               - FDCAN_TT_END_OF_LIST
 *\*\          - FilterType
 *\*\               - FDCAN_STANDARD_ID
 *\*\               - FDCAN_EXTENDED_ID
 *\*\          - TxBufferIndex
 *\*\               - FDCAN_TX_BUFFER0
 *\*\               - FDCAN_TX_BUFFER1
 *\*\               - FDCAN_TX_BUFFER2
 *\*\               - FDCAN_TX_BUFFER3
 *\*\               - FDCAN_TX_BUFFER4
 *\*\               - FDCAN_TX_BUFFER5
 *\*\               - FDCAN_TX_BUFFER6
 *\*\               - FDCAN_TX_BUFFER7
 *\*\               - FDCAN_TX_BUFFER8
 *\*\               - FDCAN_TX_BUFFER9
 *\*\               - FDCAN_TX_BUFFER10
 *\*\               - FDCAN_TX_BUFFER11
 *\*\               - FDCAN_TX_BUFFER12
 *\*\               - FDCAN_TX_BUFFER13
 *\*\               - FDCAN_TX_BUFFER14
 *\*\               - FDCAN_TX_BUFFER15
 *\*\               - FDCAN_TX_BUFFER16
 *\*\               - FDCAN_TX_BUFFER17
 *\*\               - FDCAN_TX_BUFFER18
 *\*\               - FDCAN_TX_BUFFER19
 *\*\               - FDCAN_TX_BUFFER20
 *\*\               - FDCAN_TX_BUFFER21
 *\*\               - FDCAN_TX_BUFFER22
 *\*\               - FDCAN_TX_BUFFER23
 *\*\               - FDCAN_TX_BUFFER24
 *\*\               - FDCAN_TX_BUFFER25
 *\*\               - FDCAN_TX_BUFFER26
 *\*\               - FDCAN_TX_BUFFER27
 *\*\               - FDCAN_TX_BUFFER28
 *\*\               - FDCAN_TX_BUFFER29
 *\*\               - FDCAN_TX_BUFFER30
 *\*\               - FDCAN_TX_BUFFER31
 *\*\          - FilterIndex
 *\*\               This parameter must be a number between:
 *\*\               - 0 and 127, if FilterType is FDCAN_STANDARD_ID
 *\*\               - 0 and 63, if FilterType is FDCAN_EXTENDED_ID
 *\*\return none
 */
void FDCAN_TT_ConfigTrigger(FDCAN_Module *FDCANx, FDCAN_TriggerType *sTriggerConfig)
{
    uint32_t CycleCode;
    uint32_t MsgNumber;
    uint32_t *TriggerAddress;
    FDCAN_MsgRamType *pMsg;

    pMsg = pMsgRam[FDCAN_Get_Index(FDCANx)];

    /* Calculate trigger address */
    TriggerAddress = (uint32_t *)(pMsg->TTMemoryStrAddr + (sTriggerConfig->TriggerIndex * FDCAN_TT_MEMORY_WORDS * 4UL));

    /* Calculate cycle code */
    if (sTriggerConfig->RepeatFactor == FDCAN_TT_REPEAT_EVERY_CYCLE)
    {
        CycleCode = FDCAN_TT_REPEAT_EVERY_CYCLE;
    }
    else /* sTriggerConfig->RepeatFactor != FDCAN_TT_REPEAT_EVERY_CYCLE */
    {
        CycleCode = sTriggerConfig->RepeatFactor + sTriggerConfig->StartCycle;
    }

    /* Write first word of trigger element to the message RAM */
    *TriggerAddress = ( (sTriggerConfig->TimeMark << FDCAN_ELEMENT_TM_OFFSET)   \
                        |   (CycleCode << FDCAN_ELEMENT_CC_OFFSET)                  \
                        |   (sTriggerConfig->TmEventInt )                           \
                        |   (sTriggerConfig->TmEventExt )                           \
                        |   (sTriggerConfig->TriggerType)   );

    /* Increment TriggerAddress pointer to second word of trigger element */
    TriggerAddress++;

    /* Select message number depending on trigger type (transmission or reception) */
    if (sTriggerConfig->TriggerType == FDCAN_TT_RX_TRIGGER)
    {
        MsgNumber = sTriggerConfig->FilterIndex;
    }
    else if ((sTriggerConfig->TriggerType == FDCAN_TT_TX_TRIGGER_SINGLE) ||
             (sTriggerConfig->TriggerType == FDCAN_TT_TX_TRIGGER_CONTINUOUS) ||
             (sTriggerConfig->TriggerType == FDCAN_TT_TX_TRIGGER_ARBITRATION) ||
             (sTriggerConfig->TriggerType == FDCAN_TT_TX_TRIGGER_MERGED))
    {
        MsgNumber = POSITION_VAL(sTriggerConfig->TxBufferIndex);
    }
    else
    {
        MsgNumber = 0;
    }

    /* Write second word of trigger element to the message RAM */
    *TriggerAddress = (sTriggerConfig->FilterType >> 7U) | (MsgNumber << FDCAN_ELEMENT_MNR_OFFSET);
}

/**
 *\*\name   FDCAN_TT_WaitLCKCReset.
 *\*\fun    Wait until the LCKC bit into TTOCN register is reset.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\return ErrorStatus
 *\*\          - SUCCESS: Register is unlock
 *\*\          - ERROR  : Register is locked
 */
static ErrorStatus FDCAN_TT_WaitLCKCReset(FDCAN_Module *FDCANx)
{
    uint32_t timeout;

    /* Wait until the LCKC bit into TTOCN register is reset */
    timeout = 0;

    while ((FDCANx->TTOCN & FDCAN_TTOCN_LCKC) != 0U)
    {
        /* Check for the Timeout */
        if (timeout > FDCAN_TIMEOUT_COUNT)
        {
            return ERROR;
        }

        timeout++;
    }

    return SUCCESS;
}


/**
 *\*\name   FDCAN_TT_SetGlobalTime.
 *\*\fun    Schedule global time adjustment for the next reference message.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\param  TimePreset :time preset value.
 *\*\       This parameter must be a number between:
 *\*\         - 0x0000 and 0x7FFF, Next_Master_Ref_Mark = Current_Master_Ref_Mark + TimePreset
 *\*\         or
 *\*\         - 0x8001 and 0xFFFF, Next_Master_Ref_Mark = Current_Master_Ref_Mark - (0x10000 - TimePreset)
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_TT_SetGlobalTime(FDCAN_Module *FDCANx, uint32_t TimePreset)
{
    uint32_t tempReg;

    /* Check that the external clock synchronization is enabled */
    if ((FDCANx->TTOCF & FDCAN_TTOCF_EECS) != FDCAN_TTOCF_EECS)
    {
        return ERROR;
    }

    /* Check that no global time preset is pending */
    if ((FDCANx->TTOST & FDCAN_TTOST_WGTD) == FDCAN_TTOST_WGTD)
    {
        return ERROR;
    }

    /* Configure time preset */
    tempReg  = FDCANx->TTGTP & (~(FDCAN_TTGTP_TP));
    tempReg |= TimePreset;
    FDCANx->TTGTP = tempReg;

    /* Wait until the LCKC bit into TTOCN register is reset */
    if(FDCAN_TT_WaitLCKCReset(FDCANx) != SUCCESS)
    {
        return ERROR;
    }

    /* Schedule time preset to take effect by the next reference message */
    FDCANx->TTOCN |= FDCAN_TTOCN_SGT;

    /* Return function status */
    return SUCCESS;
}

/**
 *\*\name   FDCAN_TT_SetClockSync.
 *\*\fun    Schedule TUR numerator update for the next reference message.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\param  NewTURNumerator :new value of the TUR numerator.
 *\*\       This parameter must be a number between 0x10000 and 0x1FFFF.
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_TT_SetClockSync(FDCAN_Module *FDCANx, uint32_t NewTURNumerator)
{
    uint32_t tempReg;

    /* Check that the external clock synchronization is enabled */
    if ((FDCANx->TTOCF & FDCAN_TTOCF_EECS) != FDCAN_TTOCF_EECS)
    {
        return ERROR;
    }

    /* Check that no external clock synchronization is pending */
    if ((FDCANx->TTOST & FDCAN_TTOST_WECS) == FDCAN_TTOST_WECS)
    {
        return ERROR;
    }

    /* Configure new TUR numerator */
    tempReg  = FDCANx->TURCF & (~FDCAN_TURCF_NCL);
    tempReg |= (NewTURNumerator - 0x10000UL);
    FDCANx->TURCF = tempReg;

    /* Wait until the LCKC bit into TTOCN register is reset */
    if(FDCAN_TT_WaitLCKCReset(FDCANx) != SUCCESS)
    {
        return ERROR;
    }

    /* Schedule TUR numerator update by the next reference message */
    FDCANx->TTOCN |= FDCAN_TTOCN_ECS;

    /* Return function status */
    return SUCCESS;
}

/**
 *\*\name   FDCAN_TT_ConfigStopWatch.
 *\*\fun    Configure stop watch source and polarity.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\param  Source :
 *\*\          - FDCAN_TT_STOP_WATCH_DISABLED
 *\*\          - FDCAN_TT_STOP_WATCH_CYCLE_TIME
 *\*\          - FDCAN_TT_STOP_WATCH_LOCAL_TIME
 *\*\          - FDCAN_TT_STOP_WATCH_GLOBAL_TIME
 *\*\param  Polarity :
 *\*\          - FDCAN_TT_STOP_WATCH_RISING
 *\*\          - FDCAN_TT_STOP_WATCH_FALLING
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_TT_ConfigStopWatch(FDCAN_Module *FDCANx, uint32_t Source, uint32_t Polarity)
{
    uint32_t tempReg;

    /* Wait until the LCKC bit into TTOCN register is reset */
    if(FDCAN_TT_WaitLCKCReset(FDCANx) != SUCCESS)
    {
        return ERROR;
    }

    /* Select stop watch source and polarity */
    tempReg  = FDCANx->TTOCN & (~(FDCAN_TTOCN_SWS | FDCAN_TTOCN_SWP));
    tempReg |= (Source | Polarity);
    FDCANx->TTOCN = tempReg;

    /* Return function status */
    return SUCCESS;
}

/**
 *\*\name   FDCAN_TT_ConfigRegTimeMark.
 *\*\fun    Configure register time mark pulse generation.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\param  TimeMarkSource :
 *\*\          - FDCAN_TT_REG_TIMEMARK_DIABLED
 *\*\          - FDCAN_TT_REG_TIMEMARK_CYCLE_TIME
 *\*\          - FDCAN_TT_REG_TIMEMARK_LOCAL_TIME
 *\*\          - FDCAN_TT_REG_TIMEMARK_GLOBAL_TIME
 *\*\param  TimeMarkValue :time mark value (reference).
 *\*\       This parameter must be a number between 0 and 0xFFFF.
 *\*\param  RepeatFactor :
 *\*\          - FDCAN_TT_REPEAT_EVERY_CYCLE
 *\*\          - FDCAN_TT_REPEAT_EVERY_2ND_CYCLE
 *\*\          - FDCAN_TT_REPEAT_EVERY_4TH_CYCLE
 *\*\          - FDCAN_TT_REPEAT_EVERY_8TH_CYCLE
 *\*\          - FDCAN_TT_REPEAT_EVERY_16TH_CYCLE
 *\*\          - FDCAN_TT_REPEAT_EVERY_32ND_CYCLE
 *\*\          - FDCAN_TT_REPEAT_EVERY_64TH_CYCLE
 *\*\param  StartCycle :index of the first cycle in which the time mark becomes valid.
 *\*\       This parameter is ignored if RepeatFactor is set to FDCAN_TT_REPEAT_EVERY_CYCLE.
 *\*\       This parameter must be a number between 0 and RepeatFactor.
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_TT_ConfigRegTimeMark(FDCAN_Module *FDCANx,
                                       uint32_t TimeMarkSource, uint32_t TimeMarkValue,
                                       uint32_t RepeatFactor, uint32_t StartCycle)
{
    uint32_t timeout;
    uint32_t tempReg;
    uint32_t CycleCode;

    /* Wait until the LCKC bit into TTOCN register is reset */
    if(FDCAN_TT_WaitLCKCReset(FDCANx) != SUCCESS)
    {
        return ERROR;
    }

    /* Disable the time mark compare function */
    FDCANx->TTOCN &= ~FDCAN_TTOCN_TMC;

    if (TimeMarkSource == FDCAN_TT_REG_TIMEMARK_DIABLED)
    {
        return SUCCESS;
    }

    /* Calculate cycle code */
    if (RepeatFactor == FDCAN_TT_REPEAT_EVERY_CYCLE)
    {
        CycleCode = FDCAN_TT_REPEAT_EVERY_CYCLE;
    }
    else /* RepeatFactor != FDCAN_TT_REPEAT_EVERY_CYCLE */
    {
        CycleCode = RepeatFactor + StartCycle;
    }

    /* Wait until the LCKM bit into TTTMK register is reset */
    timeout = 0;

    while ((FDCANx->TTTMK & FDCAN_TTTMK_LCKM) != 0U)
    {
        /* Check for the Timeout */
        if (timeout > FDCAN_TIMEOUT_COUNT)
        {
            return ERROR;
        }

        timeout++;
    }

    /* Configure time mark value and cycle code */
    FDCANx->TTTMK = ((TimeMarkValue) | (CycleCode << FDCAN_TTTMK_TICC_OFFSET));

    /* Wait until the LCKC bit into TTOCN register is reset */
    if(FDCAN_TT_WaitLCKCReset(FDCANx) != SUCCESS)
    {
        return ERROR;
    }

    /* Update the register time mark compare source */
    tempReg  = FDCANx->TTOCN & (~FDCAN_TTOCN_TMC);
    tempReg |= TimeMarkSource;
    FDCANx->TTOCN = tempReg;

    /* Return function status */
    return SUCCESS;
}

/**
 *\*\name   FDCAN_TT_EnableRegTMPulse.
 *\*\fun    Enables or disables register time mark pulse generation.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\param   Cmd (The input parameters must be the following values):
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_TT_EnableRegTMPulse(FDCAN_Module *FDCANx, FunctionalState Cmd)
{
    /* Wait until the LCKC bit into TTOCN register is reset */
    if(FDCAN_TT_WaitLCKCReset(FDCANx) != SUCCESS)
    {
        return ERROR;
    }

    if(Cmd == ENABLE)
    {
        /* Enable Register Time Mark Interrupt output on fdcan_rtp */
        FDCANx->TTOCN |= FDCAN_TTOCN_RTIE;
    }
    else
    {
        /* Disable Register Time Mark Interrupt output on fdcan_rtp */
        FDCANx->TTOCN &= (~FDCAN_TTOCN_RTIE);
    }


    /* Return function status */
    return SUCCESS;
}


/**
 *\*\name   FDCAN_TT_EnableTrigTMPulse.
 *\*\fun    Enables or disables trigger time mark pulse generation.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\param   Cmd (The input parameters must be the following values):
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_TT_EnableTrigTMPulse(FDCAN_Module *FDCANx, FunctionalState Cmd)
{
    if ((FDCANx->TTOCF & FDCAN_TTOCF_OM) == FDCAN_TT_COMMUNICATION_LEVEL0)
    {
        /* Feature not supported for TT Level 0 */
        return ERROR;
    }

    /* Wait until the LCKC bit into TTOCN register is reset */
    if(FDCAN_TT_WaitLCKCReset(FDCANx) != SUCCESS)
    {
        return ERROR;
    }

    if(Cmd == ENABLE)
    {
        /* Enable Trigger Time Mark Interrupt output on fdcan_tmp */
        FDCANx->TTOCN |= FDCAN_TTOCN_TTIE;
    }
    else
    {
        /* Disable Trigger Time Mark Interrupt output on fdcan_rtp */
        FDCANx->TTOCN &= (~FDCAN_TTOCN_TTIE);
    }

    /* Return function status */
    return SUCCESS;
}


/**
 *\*\name   FDCAN_TT_EnableGapPinCtrl.
 *\*\fun    Enables or disables gap control by input pin fdcan_evt.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\param   Cmd (The input parameters must be the following values):
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_TT_EnableGapPinCtrl(FDCAN_Module *FDCANx, FunctionalState Cmd)
{
    if ((FDCANx->TTOCF & FDCAN_TTOCF_OM) == FDCAN_TT_COMMUNICATION_LEVEL0)
    {
        /* Feature not supported for TT Level 0 */
        return ERROR;
    }

    /* Wait until the LCKC bit into TTOCN register is reset */
    if(FDCAN_TT_WaitLCKCReset(FDCANx) != SUCCESS)
    {
        return ERROR;
    }

    if(Cmd == ENABLE)
    {
        /* Enable gap control by pin fdcan_evt */
        FDCANx->TTOCN |= FDCAN_TTOCN_GCS;
    }
    else
    {
        /* Disable gap control by pin fdcan_evt */
        FDCANx->TTOCN &=  (~FDCAN_TTOCN_GCS);
    }

    /* Return function status */
    return SUCCESS;
}

/**
 *\*\name   FDCAN_TT_EnableTMGapCtrl.
 *\*\fun    Enables or disables gap control (finish only) by register time mark interrupt.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\param   Cmd (The input parameters must be the following values):
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_TT_EnableTMGapCtrl(FDCAN_Module *FDCANx, FunctionalState Cmd)
{
    if ((FDCANx->TTOCF & FDCAN_TTOCF_OM) == FDCAN_TT_COMMUNICATION_LEVEL0)
    {
        /* Feature not supported for TT Level 0 */
        return ERROR;
    }

    /* Wait until the LCKC bit into TTOCN register is reset */
    if(FDCAN_TT_WaitLCKCReset(FDCANx) != SUCCESS)
    {
        return ERROR;
    }

    if(Cmd == ENABLE)
    {
        /* Enable gap control by register time mark interrupt */
        FDCANx->TTOCN |= FDCAN_TTOCN_TMG;
    }
    else
    {
        /* Disable gap control by register time mark interrupt */
        FDCANx->TTOCN &= (~FDCAN_TTOCN_TMG);
    }

    /* Return function status */
    return SUCCESS;
}

/**
 *\*\name   FDCAN_TT_SetNextIsGap.
 *\*\fun    Transmit next reference message with Next_is_Gap = "1".
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_TT_SetNextIsGap(FDCAN_Module *FDCANx)
{
    /* Check that the node is configured for external event-synchronized TT operation */
    if ((FDCANx->TTOCF & FDCAN_TTOCF_GEN) != FDCAN_TTOCF_GEN)
    {
        return ERROR;
    }

    if ((FDCANx->TTOCF & FDCAN_TTOCF_OM) == FDCAN_TT_COMMUNICATION_LEVEL0)
    {
        /* Feature not supported for TT Level 0 */
        return ERROR;
    }

    /* Wait until the LCKC bit into TTOCN register is reset */
    if(FDCAN_TT_WaitLCKCReset(FDCANx) != SUCCESS)
    {
        return ERROR;
    }

    /* Set Next is Gap */
    FDCANx->TTOCN |= FDCAN_TTOCN_NIG;

    /* Return function status */
    return SUCCESS;
}

/**
 *\*\name   FDCAN_TT_SetEndOfGap.
 *\*\fun    Finish a Gap by requesting start of reference message.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_TT_SetEndOfGap(FDCAN_Module *FDCANx)
{
    /* Check that the node is configured for external event-synchronized TT operation */
    if ((FDCANx->TTOCF & FDCAN_TTOCF_GEN) != FDCAN_TTOCF_GEN)
    {
        return ERROR;
    }

    if ((FDCANx->TTOCF & FDCAN_TTOCF_OM) == FDCAN_TT_COMMUNICATION_LEVEL0)
    {
        /* Feature not supported for TT Level 0 */
        return ERROR;
    }


    /* Wait until the LCKC bit into TTOCN register is reset */
    if(FDCAN_TT_WaitLCKCReset(FDCANx) != SUCCESS)
    {
        return ERROR;
    }

    /* Set Finish Gap */
    FDCANx->TTOCN |= FDCAN_TTOCN_FGP;

    /* Return function status */
    return SUCCESS;
}

/**
 *\*\name   FDCAN_TT_ConfigExtSyncPhase.
 *\*\fun    Configure target phase used for external synchronization by event
 *\*\       trigger input pin.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\param  TargetPhase :defines target value of cycle time when a rising edge
 *\*\       of fdcan_evt is expected.
 *\*\       This parameter must be a number between 0 and 0xFFFF.
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_TT_ConfigExtSyncPhase(FDCAN_Module *FDCANx, uint32_t TargetPhase)
{
    uint32_t tempReg;

    /* Check that no external schedule synchronization is pending */
    if ((FDCANx->TTOCN & FDCAN_TTOCN_ESCN) == FDCAN_TTOCN_ESCN)
    {
        return ERROR;
    }

    /* Configure cycle time target phase */
    tempReg = FDCANx->TTGTP & (~FDCAN_TTGTP_CTP);
    tempReg |= TargetPhase << FDCAN_TTGTP_CTP_OFFSET;
    FDCANx->TTGTP = tempReg;

    /* Return function status */
    return SUCCESS;
}

/**
 *\*\name   FDCAN_TT_EnableExtSync.
 *\*\fun    Enable or disable external schedule synchronization.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\param   Cmd (The input parameters must be the following values):
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_TT_EnableExtSync(FDCAN_Module *FDCANx, FunctionalState Cmd)
{
    /* Wait until the LCKC bit into TTOCN register is reset */
    if(FDCAN_TT_WaitLCKCReset(FDCANx) != SUCCESS)
    {
        return ERROR;
    }

    if(Cmd == ENABLE)
    {
        /* Enable external synchronization */
        FDCANx->TTOCN |= FDCAN_TTOCN_ESCN;
    }
    else
    {
        /* Disable external synchronization */
        FDCANx->TTOCN &= (~FDCAN_TTOCN_ESCN);
    }

    /* Return function status */
    return SUCCESS;
}


/**
 *\*\name   FDCAN_TT_GetStatus.
 *\*\fun    Get TT operation status.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\param  TTStatus pointer to an FDCAN_TT_Status structure.
 *\*\          - ErrorLevel
 *\*\               - FDCAN_TT_NO_ERROR
 *\*\               - FDCAN_TT_WARNING
 *\*\               - FDCAN_TT_ERROR
 *\*\               - FDCAN_TT_SEVERE_ERROR
 *\*\          - MasterState
 *\*\               - FDCAN_TT_MASTER_OFF
 *\*\               - FDCAN_TT_TIME_SLAVE
 *\*\               - FDCAN_TT_BACKUP_TIME_MASTER
 *\*\               - FDCAN_TT_CURRENT_TIME_MASTER
 *\*\          - SyncState
 *\*\               - FDCAN_TT_OUT_OF_SYNC
 *\*\               - FDCAN_TT_SYNCHRONIZING
 *\*\               - FDCAN_TT_IN_GAP
 *\*\               - FDCAN_TT_IN_SCHEDULE
 *\*\          - GTimeQuality
 *\*\               - FDCAN_TT_GTIME_NOT_VALID
 *\*\               - FDCAN_TT_GTIME_IN_MASTER_PHASE
 *\*\          - ClockQuality
 *\*\               - FDCAN_TT_LOCAL_CLOCK_NOT_SYNC
 *\*\               - FDCAN_TT_SYNC_DEV_LESS_THAN_SDL
 *\*\          - RefTrigOffset
 *\*\               This parameter can be a number between 0 and 0xFF
 *\*\          - GTimeDiscPending
 *\*\               - FDCAN_TT_NO_GTIME_PENDING
 *\*\               - FDCAN_TT_WATI_GTIMESYNC_PRESENT
 *\*\          - GapFinished
 *\*\               - FDCAN_TT_GAP_RESET
 *\*\               - FDCAN_TT_GAP_FINISHED
 *\*\          - MasterPriority
 *\*\               This parameter can be a number between 0 and 0x7
 *\*\          - GapStarted
 *\*\               - FDCAN_TT_NO_GAP
 *\*\               - FDCAN_TT_GAP_STARTED
 *\*\          - WaitForEvt
 *\*\               - FDCAN_TT_GAP_NOT_ANNOUNCED
 *\*\               - FDCAN_TT_REF_MSG_RECEIVED
 *\*\          - AppWdgEvt
 *\*\               - FDCAN_TT_WATCHDOG_VALID
 *\*\               - FDCAN_TT_WATCHDOG_INVALID
 *\*\          - ECSPending
 *\*\               - FDCAN_TT_NO_EXT_CLOCK_SYNC
 *\*\               - FDCAN_TT_WAIT_EXT_CLOCK_SYNC
 *\*\          - PhaseLock
 *\*\               - FDCAN_TT_PHASE_OUT_OF_RANGE
 *\*\               - FDCAN_TT_PHASE_IN_RANGE
 *\*\return none
 */
void FDCAN_TT_GetStatus(FDCAN_Module *FDCANx, FDCAN_TT_Status *TTStatus)
{
    uint32_t tempReg;

    /* Read the TT operation status register */
    tempReg = FDCANx->TTOST;

    /* Fill the TT operation status structure */
    TTStatus->ErrorLevel        = (tempReg  & FDCAN_TTOST_EL);
    TTStatus->MasterState       = (tempReg  & FDCAN_TTOST_MS);
    TTStatus->SyncState         = (tempReg  & FDCAN_TTOST_SYS);
    TTStatus->GTimeQuality      = (tempReg  & FDCAN_TTOST_QGTP);
    TTStatus->ClockQuality      = (tempReg  & FDCAN_TTOST_QCS);
    TTStatus->RefTrigOffset     = ((tempReg & FDCAN_TTOST_RTO) >> FDCAN_TTOST_RTO_OFFSET);
    TTStatus->GTimeDiscPending  = (tempReg  & FDCAN_TTOST_WGTD);
    TTStatus->GapFinished       = (tempReg  & FDCAN_TTOST_GFI);
    TTStatus->MasterPriority    = ((tempReg & FDCAN_TTOST_TMP) >> FDCAN_TTOST_TMP_OFFSET);
    TTStatus->GapStarted        = (tempReg  & FDCAN_TTOST_GSI);
    TTStatus->WaitForEvt        = (tempReg  & FDCAN_TTOST_WFE);
    TTStatus->AppWdgEvt         = (tempReg  & FDCAN_TTOST_AWE);
    TTStatus->ECSPending        = (tempReg  & FDCAN_TTOST_WECS);
    TTStatus->PhaseLock         = (tempReg  & FDCAN_TTOST_SPL);
}

/**
 *\*\name   FDCAN_TT_ConfigIntLine.
 *\*\fun    Assign TT interrupts to either Interrupt line 0 or 1.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\param  TT_Int :
 *\*\          - FDCAN_TT_INT_BASIC_CYCLE_START
 *\*\          - FDCAN_TT_INT_MATRIX_CYCLE_START
 *\*\          - FDCAN_TT_INT_SYNC_MODE_CHANGE
 *\*\          - FDCAN_TT_INT_START_OF_GAP
 *\*\          - FDCAN_TT_INT_REG_TIME_MARK
 *\*\          - FDCAN_TT_INT_TRIG_TIME_MARK
 *\*\          - FDCAN_TT_INT_STOP_WATCH
 *\*\          - FDCAN_TT_INT_GLOBAL_TIME_WRAP
 *\*\          - FDCAN_TT_INT_GLOBAL_TIME_DISC
 *\*\          - FDCAN_TT_INT_GLOBAL_TIME_ERROR
 *\*\          - FDCAN_TT_INT_TX_COUNT_UNDERFLOW
 *\*\          - FDCAN_TT_INT_TX_COUNT_OVERFLOW
 *\*\          - FDCAN_TT_INT_SCHEDULING_ERROR_1
 *\*\          - FDCAN_TT_INT_SCHEDULING_ERROR_2
 *\*\          - FDCAN_TT_INT_ERROR_LEVEL_CHANGE
 *\*\          - FDCAN_TT_INT_INIT_WATCH_TRIGGER
 *\*\          - FDCAN_TT_INT_WATCH_TRIGGER
 *\*\          - FDCAN_TT_INT_APPLICATION_WATCHDOG
 *\*\          - FDCAN_TT_INT_CONFIG_ERROR
 *\*\param  IntLine :
 *\*\          - FDCAN_INTERRUPT_LINE0
 *\*\          - FDCAN_INTERRUPT_LINE1
 *\*\return none
 */
void FDCAN_TT_ConfigIntLine(FDCAN_Module *FDCANx, uint32_t TT_Int, uint32_t IntLine)
{
    /* Assign list of interrupts to the selected line */
    if (IntLine == FDCAN_INTERRUPT_LINE0)
    {
        FDCANx->TTILS &= (~TT_Int);
    }
    else /* IntLine == FDCAN_INTERRUPT_LINE1 */
    {
        FDCANx->TTILS |= TT_Int;
    }
}

/**
 *\*\name   FDCAN_TT_EnableInt.
 *\*\fun    Enable or disable the specified FDCAN TT interrupts.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\param  TT_Int :
 *\*\          - FDCAN_TT_INT_BASIC_CYCLE_START
 *\*\          - FDCAN_TT_INT_MATRIX_CYCLE_START
 *\*\          - FDCAN_TT_INT_SYNC_MODE_CHANGE
 *\*\          - FDCAN_TT_INT_START_OF_GAP
 *\*\          - FDCAN_TT_INT_REG_TIME_MARK
 *\*\          - FDCAN_TT_INT_TRIG_TIME_MARK
 *\*\          - FDCAN_TT_INT_STOP_WATCH
 *\*\          - FDCAN_TT_INT_GLOBAL_TIME_WRAP
 *\*\          - FDCAN_TT_INT_GLOBAL_TIME_DISC
 *\*\          - FDCAN_TT_INT_GLOBAL_TIME_ERROR
 *\*\          - FDCAN_TT_INT_TX_COUNT_UNDERFLOW
 *\*\          - FDCAN_TT_INT_TX_COUNT_OVERFLOW
 *\*\          - FDCAN_TT_INT_SCHEDULING_ERROR_1
 *\*\          - FDCAN_TT_INT_SCHEDULING_ERROR_2
 *\*\          - FDCAN_TT_INT_ERROR_LEVEL_CHANGE
 *\*\          - FDCAN_TT_INT_INIT_WATCH_TRIGGER
 *\*\          - FDCAN_TT_INT_WATCH_TRIGGER
 *\*\          - FDCAN_TT_INT_APPLICATION_WATCHDOG
 *\*\          - FDCAN_TT_INT_CONFIG_ERROR
 *\*\return none
 */
void FDCAN_TT_EnableInt(FDCAN_Module *FDCANx, uint32_t TT_Int, FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        FDCANx->TTIE |= TT_Int;
    }
    else
    {
        FDCANx->TTIE &= (~TT_Int);
    }
}


/**
 *\*\name   FDCAN_TT_GetIntFlag.
 *\*\fun    Check whether the specified FDCAN TT interrupt is set or not.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\param  TT_Flag :
 *\*\          - FDCAN_TT_FLAG_BASIC_CYCLE_START
 *\*\          - FDCAN_TT_FLAG_MATRIX_CYCLE_START
 *\*\          - FDCAN_TT_FLAG_SYNC_MODE_CHANGE
 *\*\          - FDCAN_TT_FLAG_START_OF_GAP
 *\*\          - FDCAN_TT_FLAG_REG_TIME_MARK
 *\*\          - FDCAN_TT_FLAG_TRIG_TIME_MARK
 *\*\          - FDCAN_TT_FLAG_STOP_WATCH
 *\*\          - FDCAN_TT_FLAG_GLOBAL_TIME_WRAP
 *\*\          - FDCAN_TT_FLAG_GLOBAL_TIME_DISC
 *\*\          - FDCAN_TT_FLAG_GLOBAL_TIME_ERROR
 *\*\          - FDCAN_TT_FLAG_TX_COUNT_UNDERFLOW
 *\*\          - FDCAN_TT_FLAG_TX_COUNT_OVERFLOW
 *\*\          - FDCAN_TT_FLAG_SCHEDULING_ERROR_1
 *\*\          - FDCAN_TT_FLAG_SCHEDULING_ERROR_2
 *\*\          - FDCAN_TT_FLAG_ERROR_LEVEL_CHANGE
 *\*\          - FDCAN_TT_FLAG_INIT_WATCH_TRIGGER
 *\*\          - FDCAN_TT_FLAG_WATCH_TRIGGER
 *\*\          - FDCAN_TT_FLAG_APPLICATION_WATCHDOG
 *\*\          - FDCAN_TT_FLAG_CONFIG_ERROR
 *\*\return FlagStatus
 *\*\          - RESET
 *\*\          - SET
 */
FlagStatus FDCAN_TT_GetIntFlag(FDCAN_Module *FDCANx, uint32_t TT_Flag)
{
    /* Check whether the specified FDCAN TT interrupt is enable or not. */
    if((FDCANx->TTIE & TT_Flag) != TT_Flag )
    {
        return RESET;
    }

    /* Check whether the specified FDCAN TT interrupt flag is set or not. */
    if((FDCANx->TTIR & TT_Flag) != TT_Flag )
    {
        return RESET;
    }

    return SET;
}

/**
 *\*\name   FDCAN_TT_GetFlag.
 *\*\fun    Check whether the specified FDCAN TT flag is set or not.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\param  TT_Flag :
 *\*\          - FDCAN_TT_FLAG_BASIC_CYCLE_START
 *\*\          - FDCAN_TT_FLAG_MATRIX_CYCLE_START
 *\*\          - FDCAN_TT_FLAG_SYNC_MODE_CHANGE
 *\*\          - FDCAN_TT_FLAG_START_OF_GAP
 *\*\          - FDCAN_TT_FLAG_REG_TIME_MARK
 *\*\          - FDCAN_TT_FLAG_TRIG_TIME_MARK
 *\*\          - FDCAN_TT_FLAG_STOP_WATCH
 *\*\          - FDCAN_TT_FLAG_GLOBAL_TIME_WRAP
 *\*\          - FDCAN_TT_FLAG_GLOBAL_TIME_DISC
 *\*\          - FDCAN_TT_FLAG_GLOBAL_TIME_ERROR
 *\*\          - FDCAN_TT_FLAG_TX_COUNT_UNDERFLOW
 *\*\          - FDCAN_TT_FLAG_TX_COUNT_OVERFLOW
 *\*\          - FDCAN_TT_FLAG_SCHEDULING_ERROR_1
 *\*\          - FDCAN_TT_FLAG_SCHEDULING_ERROR_2
 *\*\          - FDCAN_TT_FLAG_ERROR_LEVEL_CHANGE
 *\*\          - FDCAN_TT_FLAG_INIT_WATCH_TRIGGER
 *\*\          - FDCAN_TT_FLAG_WATCH_TRIGGER
 *\*\          - FDCAN_TT_FLAG_APPLICATION_WATCHDOG
 *\*\          - FDCAN_TT_FLAG_CONFIG_ERROR
 *\*\return FlagStatus
 *\*\          - RESET
 *\*\          - SET
 */
FlagStatus FDCAN_TT_GetFlag(FDCAN_Module *FDCANx, uint32_t TT_Flag)
{
    /* Check whether the specified FDCAN TT interrupt flag is set or not. */
    if((FDCANx->TTIR & TT_Flag) != TT_Flag )
    {
        return RESET;
    }
    else
    {
        return SET;
    }
}

/**
 *\*\name   FDCAN_TT_ClearFlag.
 *\*\fun    Clear the specified FDCAN TT flag.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\param  TT_Flag :
 *\*\          - FDCAN_TT_FLAG_BASIC_CYCLE_START
 *\*\          - FDCAN_TT_FLAG_MATRIX_CYCLE_START
 *\*\          - FDCAN_TT_FLAG_SYNC_MODE_CHANGE
 *\*\          - FDCAN_TT_FLAG_START_OF_GAP
 *\*\          - FDCAN_TT_FLAG_REG_TIME_MARK
 *\*\          - FDCAN_TT_FLAG_TRIG_TIME_MARK
 *\*\          - FDCAN_TT_FLAG_STOP_WATCH
 *\*\          - FDCAN_TT_FLAG_GLOBAL_TIME_WRAP
 *\*\          - FDCAN_TT_FLAG_GLOBAL_TIME_DISC
 *\*\          - FDCAN_TT_FLAG_GLOBAL_TIME_ERROR
 *\*\          - FDCAN_TT_FLAG_TX_COUNT_UNDERFLOW
 *\*\          - FDCAN_TT_FLAG_TX_COUNT_OVERFLOW
 *\*\          - FDCAN_TT_FLAG_SCHEDULING_ERROR_1
 *\*\          - FDCAN_TT_FLAG_SCHEDULING_ERROR_2
 *\*\          - FDCAN_TT_FLAG_ERROR_LEVEL_CHANGE
 *\*\          - FDCAN_TT_FLAG_INIT_WATCH_TRIGGER
 *\*\          - FDCAN_TT_FLAG_WATCH_TRIGGER
 *\*\          - FDCAN_TT_FLAG_APPLICATION_WATCHDOG
 *\*\          - FDCAN_TT_FLAG_CONFIG_ERROR
 *\*\return none
 */
void FDCAN_TT_ClearFlag(FDCAN_Module *FDCANx, uint32_t TT_Flag)
{
    FDCANx->TTIR = TT_Flag;
}

/**
 *\*\name   FDCAN_TT_ActivateInt.
 *\*\fun    Activate the specified FDCAN TT interrupts.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\param  TT_Int :
 *\*\          - FDCAN_TT_INT_BASIC_CYCLE_START
 *\*\          - FDCAN_TT_INT_MATRIX_CYCLE_START
 *\*\          - FDCAN_TT_INT_SYNC_MODE_CHANGE
 *\*\          - FDCAN_TT_INT_START_OF_GAP
 *\*\          - FDCAN_TT_INT_REG_TIME_MARK
 *\*\          - FDCAN_TT_INT_TRIG_TIME_MARK
 *\*\          - FDCAN_TT_INT_STOP_WATCH
 *\*\          - FDCAN_TT_INT_GLOBAL_TIME_WRAP
 *\*\          - FDCAN_TT_INT_GLOBAL_TIME_DISC
 *\*\          - FDCAN_TT_INT_GLOBAL_TIME_ERROR
 *\*\          - FDCAN_TT_INT_TX_COUNT_UNDERFLOW
 *\*\          - FDCAN_TT_INT_TX_COUNT_OVERFLOW
 *\*\          - FDCAN_TT_INT_SCHEDULING_ERROR_1
 *\*\          - FDCAN_TT_INT_SCHEDULING_ERROR_2
 *\*\          - FDCAN_TT_INT_ERROR_LEVEL_CHANGE
 *\*\          - FDCAN_TT_INT_INIT_WATCH_TRIGGER
 *\*\          - FDCAN_TT_INT_WATCH_TRIGGER
 *\*\          - FDCAN_TT_INT_APPLICATION_WATCHDOG
 *\*\          - FDCAN_TT_INT_CONFIG_ERROR
 *\*\return ErrorStatus
 *\*\          - SUCCESS
 *\*\          - ERROR
 */
ErrorStatus FDCAN_TT_ActivateInt(FDCAN_Module *FDCANx, uint32_t TT_Int)
{
    /* Check ActiveITs */
    if((TT_Int & FDCAN_TT_INT_MASK) == 0UL)
    {
        return ERROR;
    }

    /* Enable Interrupt lines */
    if ((TT_Int & FDCANx->TTILS) == 0UL)
    {
        /* Enable Interrupt line 0 */
        FDCANx->ILE |= FDCAN_INTERRUPT_LINE0;
    }
    else if ((TT_Int & FDCANx->TTILS) == TT_Int)
    {
        /* Enable Interrupt line 1 */
        FDCANx->ILE |= FDCAN_INTERRUPT_LINE1;
    }
    else
    {
        /* Enable Interrupt lines 0 and 1 */
        FDCANx->ILE = (FDCAN_INTERRUPT_LINE0 | FDCAN_INTERRUPT_LINE1);
    }

    /* Enable the selected TT interrupts */
    FDCAN_TT_EnableInt(FDCANx, TT_Int, ENABLE);

    return SUCCESS;
}

/**
 *\*\name   FDCAN_TT_DeactivateInt.
 *\*\fun    Deactivate the specified FDCAN TT interrupts.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\param  TT_Int :
 *\*\          - FDCAN_TT_INT_BASIC_CYCLE_START
 *\*\          - FDCAN_TT_INT_MATRIX_CYCLE_START
 *\*\          - FDCAN_TT_INT_SYNC_MODE_CHANGE
 *\*\          - FDCAN_TT_INT_START_OF_GAP
 *\*\          - FDCAN_TT_INT_REG_TIME_MARK
 *\*\          - FDCAN_TT_INT_TRIG_TIME_MARK
 *\*\          - FDCAN_TT_INT_STOP_WATCH
 *\*\          - FDCAN_TT_INT_GLOBAL_TIME_WRAP
 *\*\          - FDCAN_TT_INT_GLOBAL_TIME_DISC
 *\*\          - FDCAN_TT_INT_GLOBAL_TIME_ERROR
 *\*\          - FDCAN_TT_INT_TX_COUNT_UNDERFLOW
 *\*\          - FDCAN_TT_INT_TX_COUNT_OVERFLOW
 *\*\          - FDCAN_TT_INT_SCHEDULING_ERROR_1
 *\*\          - FDCAN_TT_INT_SCHEDULING_ERROR_2
 *\*\          - FDCAN_TT_INT_ERROR_LEVEL_CHANGE
 *\*\          - FDCAN_TT_INT_INIT_WATCH_TRIGGER
 *\*\          - FDCAN_TT_INT_WATCH_TRIGGER
 *\*\          - FDCAN_TT_INT_APPLICATION_WATCHDOG
 *\*\          - FDCAN_TT_INT_CONFIG_ERROR
 *\*\return none
 */
void FDCAN_TT_DeactivateInt(FDCAN_Module *FDCANx, uint32_t TT_Int)
{
    uint32_t IntLine;
    uint32_t tempReg;

    /* Disable the selected TT interrupts */
    FDCAN_TT_EnableInt(FDCANx, TT_Int, DISABLE);

    IntLine = FDCANx->TTILS;
    tempReg = FDCANx->ILE;

    if ((FDCANx->TTIE | IntLine) == IntLine)
    {
        /* Disable Interrupt line 0 */
        tempReg &= (~FDCAN_INTERRUPT_LINE0);
    }

    if ((FDCANx->TTIE & IntLine) == 0U)
    {
        /* Disable Interrupt line 1 */
        tempReg &= (~FDCAN_INTERRUPT_LINE1);
    }

    FDCANx->ILE = tempReg;
}

/**
 *\*\name   FDCAN_InitMsgRam.
 *\*\fun    Calculate each RAM block start address and size,
 *\*\       and also initialize global infomation parameter.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  FDCAN_InitParam:pointer to a FDCAN_InitType structure.
 *\*\return ErrorStatus
 *\*\          - ERROR
 *\*\          - SUCCESS
 */
static ErrorStatus FDCAN_InitMsgRam(FDCAN_Module* FDCANx, FDCAN_InitType *FDCAN_InitParam)
{
    uint32_t ram;
    uint32_t WordOffset;
    uint32_t StartAddress;
    uint32_t tempReg;
    FDCAN_MsgRamType *pMsg;

    /* Config Message Ram base address,this address is shared by FDCAN1~8 */
    if(FDCAN_InitParam->MsgRamStrAddr == FDCAN_START_ADDRESS_SRAM5BANK1)
    {
        FDCANx->TTSS &= (~FDCAN_START_ADDRESS_RAMSEL);
        StartAddress = FDCAN_START_ADDRESS_SRAM5BANK1;
    }
    else
    {
        FDCANx->TTSS |= FDCAN_START_ADDRESS_RAMSEL;
        StartAddress = FDCAN_START_ADDRESS_SRAM5BANK2;
    }

    FDCAN_ClearFlag(FDCANx, FDCAN_FLAG_RESERVED_ADDRESS_ACCESS);

    /* Config the message block for current FDCANx */
    pMsgRam[FDCAN_Get_Index(FDCANx)] = FDCAN_InitParam->pMsgInfo;

    pMsg = FDCAN_InitParam->pMsgInfo;
    pMsg->RxFifo0Size        = FDCAN_InitParam->RxFifo0Size;
    pMsg->RxFifo1Size        = FDCAN_InitParam->RxFifo1Size;
    pMsg->RxBufferSize       = FDCAN_InitParam->RxBufferSize;
    pMsg->TxBufferSize       = FDCAN_InitParam->TxBufferSize;
    pMsg->RxFifo0DataSize    = FDCAN_InitParam->RxFifo0DataSize;
    pMsg->RxFifo1DataSize    = FDCAN_InitParam->RxFifo1DataSize;
    pMsg->RxBufferDataSize   = FDCAN_InitParam->RxBufferDataSize;
    pMsg->TxBufferDataSize   = FDCAN_InitParam->TxBufferDataSize;
    pMsg->LastTxFifoQReqBuf  = 0;

    /* Config the registers raelated to Message Ram and  global Message Ram paramter.
       All address in register are actually the address offset, and counted in words.
       Global Message Ram paramter counted in bytes */

    /* Standard filter list start address */
    WordOffset = FDCAN_InitParam->MsgRamOffset;
    tempReg  = WordOffset << FDCAN_START_ADDRESS_OFFSET;
    /* Standard filter elements number */
    tempReg |= FDCAN_InitParam->StdFilterSize << FDCAN_SIZE_NUMBER_OFFSET;
    FDCANx->SIDFC = tempReg;
    pMsg->StdFilterStrAddr = StartAddress + (WordOffset * 4UL);

    /* Extended filter list start address */
    WordOffset += FDCAN_InitParam->StdFilterSize;
    tempReg  = WordOffset << FDCAN_START_ADDRESS_OFFSET;
    /* Extended filter elements number */
    tempReg |= FDCAN_InitParam->ExtFilterSize << FDCAN_SIZE_NUMBER_OFFSET;
    FDCANx->XIDFC = tempReg;
    pMsg->ExtFilterStrAddr = StartAddress + (WordOffset * 4UL);

    /* Rx FIFO 0 start address */
    WordOffset += (FDCAN_InitParam->ExtFilterSize * FDCAN_EXT_FILTER_WORDS);
    tempReg  = FDCANx->RXF0C & (~(FDCAN_RXF0C_F0SA | FDCAN_RXF0C_F0S));
    tempReg |= WordOffset << FDCAN_START_ADDRESS_OFFSET;
    /* Rx FIFO 0 elements number */
    tempReg |= FDCAN_InitParam->RxFifo0Size << FDCAN_SIZE_NUMBER_OFFSET;
    FDCANx->RXF0C = tempReg;
    pMsg->RxFIFO0StrAddr = StartAddress + (WordOffset * 4UL);

    /* Rx FIFO 1 start address */
    WordOffset += (FDCAN_InitParam->RxFifo0Size * FDCAN_InitParam->RxFifo0DataSize);
    tempReg  = FDCANx->RXF1C & (~(FDCAN_RXF1C_F1SA | FDCAN_RXF1C_F1S));
    tempReg |= WordOffset << FDCAN_START_ADDRESS_OFFSET;
    /* Rx FIFO 1 elements number */
    tempReg |= FDCAN_InitParam->RxFifo1Size << FDCAN_SIZE_NUMBER_OFFSET;
    FDCANx->RXF1C = tempReg;
    pMsg->RxFIFO1StrAddr = StartAddress + (WordOffset * 4UL);

    /* Rx buffer list start address */
    WordOffset += (FDCAN_InitParam->RxFifo1Size * FDCAN_InitParam->RxFifo1DataSize);
    FDCANx->RXBC = WordOffset << FDCAN_START_ADDRESS_OFFSET;
    pMsg->RxBufferStrAddr = StartAddress + (WordOffset * 4UL);

    /* Tx event FIFO start address */
    WordOffset += (FDCAN_InitParam->RxBufferSize * FDCAN_InitParam->RxBufferDataSize);
    tempReg  = FDCANx->TXEFC & (~(FDCAN_TXEFC_EFSA | FDCAN_TXEFC_EFS));
    tempReg |= WordOffset << FDCAN_START_ADDRESS_OFFSET;
    /* Tx event FIFO elements number */
    tempReg |= FDCAN_InitParam->TxEventSize << FDCAN_SIZE_NUMBER_OFFSET;
    FDCANx->TXEFC = tempReg;
    pMsg->TxEventFIFOStrAddr = StartAddress + (WordOffset * 4UL);

    /* Tx buffer list start address */
    WordOffset += (FDCAN_InitParam->TxEventSize * FDCAN_TX_EVENT_FIFO_WORDS);
    tempReg  = FDCANx->TXBC & (~(FDCAN_TXBC_TBSA | FDCAN_TXBC_NDTB | FDCAN_TXBC_TFQS));
    tempReg |= WordOffset << FDCAN_START_ADDRESS_OFFSET;
    /* Dedicated Tx buffers number */
    tempReg |= FDCAN_InitParam->TxBufferSize << FDCAN_SIZE_NUMBER_OFFSET;
    pMsg->TxBufferStrAddr = StartAddress + (WordOffset * 4UL);

    /* Tx FIFO/queue elements number */
    tempReg |= FDCAN_InitParam->TxFifoQueueSize << FDCAN_TXBC_TFQS_OFFSET;
    FDCANx->TXBC = tempReg;
    WordOffset += (FDCAN_InitParam->TxBufferSize * FDCAN_InitParam->TxBufferDataSize);
    pMsg->TxFIFOQueueStrAddr = StartAddress + (WordOffset * 4UL);

    WordOffset += (FDCAN_InitParam->TxFifoQueueSize * FDCAN_InitParam->TxBufferDataSize);
    pMsg->EndAddress = StartAddress + (WordOffset * 4UL);

    /* Check last address of the Message RAM */
    if (pMsg->EndAddress > (StartAddress + FDCAN_MESSAGE_RAM_SIZE))
    {
        return ERROR;
    }

    /* Flush the allocated Message RAM area */
    for (ram = pMsg->StdFilterStrAddr; ram < pMsg->EndAddress; ram += 4UL)
    {
        *(uint32_t *)(ram) = 0UL;
    }

    /* Return function status */
    return SUCCESS;
}

/**
 *\*\name   FDCAN_CopyMsgToRAM.
 *\*\fun    Copy Tx message to the message RAM.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  pTxHeader :pointer to a FDCAN_TxHeaderType structure.
 *\*\          - IdType
 *\*\               - FDCAN_STANDARD_ID
 *\*\               - FDCAN_EXTENDED_ID
 *\*\          - ID
 *\*\               This parameter must be a value between:
 *\*\               - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
 *\*\               - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID
 *\*\          - TxFrameType
 *\*\               - FDCAN_DATA_FRAME
 *\*\               - FDCAN_REMOTE_FRAME
 *\*\          - DataLength
 *\*\               - FDCAN_DLC_BYTES_0
 *\*\               - FDCAN_DLC_BYTES_1
 *\*\               - FDCAN_DLC_BYTES_2
 *\*\               - FDCAN_DLC_BYTES_3
 *\*\               - FDCAN_DLC_BYTES_4
 *\*\               - FDCAN_DLC_BYTES_5
 *\*\               - FDCAN_DLC_BYTES_6
 *\*\               - FDCAN_DLC_BYTES_7
 *\*\               - FDCAN_DLC_BYTES_8
 *\*\               - FDCAN_DLC_BYTES_12
 *\*\               - FDCAN_DLC_BYTES_16
 *\*\               - FDCAN_DLC_BYTES_20
 *\*\               - FDCAN_DLC_BYTES_24
 *\*\               - FDCAN_DLC_BYTES_32
 *\*\               - FDCAN_DLC_BYTES_48
 *\*\               - FDCAN_DLC_BYTES_64
 *\*\          - ErrorState
 *\*\               - FDCAN_ESI_ACTIVE
 *\*\               - FDCAN_ESI_PASSIVE
 *\*\          - BitRateSwitch
 *\*\               - FDCAN_BRS_OFF
 *\*\               - FDCAN_BRS_ON
 *\*\          - FDFormat
 *\*\               - FDCAN_CLASSIC_CAN
 *\*\               - FDCAN_FD_CAN
 *\*\          - TxEventFifo
 *\*\               - FDCAN_NO_TX_EVENTS
 *\*\               - FDCAN_STORE_TX_EVENTS
 *\*\          - MsgMarker
 *\*\               This parameter must be a value between 0 and 0xFF
 *\*\param  pTxData pointer to a buffer containing the payload of the Tx frame.
 *\*\param  BufferIndex index of the buffer to be configured.
 *\*\return none
 */
static void FDCAN_CopyMsgToRAM(FDCAN_Module *FDCANx, FDCAN_TxHeaderType *pTxHeader, uint8_t *pTxData, uint32_t BufferIndex)
{
    uint32_t *TxAddress;
    uint32_t Cnt;
    uint8_t *pRam;
    FDCAN_MsgRamType *pMsg;

    pMsg = pMsgRam[FDCAN_Get_Index(FDCANx)];

    /* Calculate Tx element address */
    TxAddress = (uint32_t *)(pMsg->TxBufferStrAddr + (BufferIndex * pMsg->TxBufferDataSize * 4UL));

    /* Build and write first word of Tx header element to ram */
    if (pTxHeader->IdType == FDCAN_STANDARD_ID)
    {
        *TxAddress = (  pTxHeader->ErrorState   \
                        |   FDCAN_STANDARD_ID       \
                        |   pTxHeader->TxFrameType  \
                        |   (pTxHeader->ID << FDCAN_ELEMENT_STDID_OFFSET)   );
    }
    else /* pTxHeader->IdType == FDCAN_EXTENDED_ID */
    {
        *TxAddress = (  pTxHeader->ErrorState   \
                        |   FDCAN_EXTENDED_ID       \
                        |   pTxHeader->TxFrameType  \
                        |   pTxHeader->ID   );
    }

    /* Increment TxAddress pointer to second word of Tx header element */
    TxAddress++;

    /* Build and write second word of Tx header element to ram */
    *TxAddress = (  (pTxHeader->MsgMarker << FDCAN_ELEMENT_MM_OFFSET)   \
                    |   pTxHeader->TxEventFifo                           \
                    |   pTxHeader->FDFormat                                     \
                    |   pTxHeader->BitRateSwitch                                \
                    |   pTxHeader->DataLength);

    /* Increment TxAddress pointer to Tx data */
    TxAddress++;
    pRam = (uint8_t *)TxAddress;

    /* Write Tx payload to the message RAM */
    for (Cnt = 0; Cnt < DLCtoBytes[pTxHeader->DataLength >> FDCAN_ELEMENT_DLC_OFFSET]; Cnt++)
    {
        pRam[Cnt] = pTxData[Cnt];
    }
}

/**
 *\*\name   FDCAN_ConfigExtTSDivider.
 *\*\fun    Config the clock diveder of external timestamp clock.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  Div :
 *\*\          - FDCAN_EXT_TIMESTAMP_DIV_4
 *\*\          - FDCAN_EXT_TIMESTAMP_DIV_8
 *\*\          - FDCAN_EXT_TIMESTAMP_DIV_16
 *\*\          - FDCAN_EXT_TIMESTAMP_DIV_32
 *\*\          - FDCAN_EXT_TIMESTAMP_DIV_64
 *\*\          - FDCAN_EXT_TIMESTAMP_DIV_128
 *\*\          - FDCAN_EXT_TIMESTAMP_DIV_256
 *\*\          - FDCAN_EXT_TIMESTAMP_DIV_512
 *\*\return none
 */
void FDCAN_ConfigExtTSDivider(FDCAN_Module *FDCANx, uint32_t Div)
{
    uint32_t tempReg;

    tempReg  = FDCANx->TTSS & (~FDCAN_TTSS_TS_SEL);
    tempReg |= Div;
    FDCANx->TTSS = tempReg;
}

/**
 *\*\name   FDCAN_EnableExtTS.
 *\*\fun    Enalbe or disable the external timestamp.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\param  Cmd :
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return none
 */
void FDCAN_EnableExtTS(FDCAN_Module *FDCANx, FunctionalState Cmd)
{
    uint32_t tempReg;

    tempReg = FDCANx->TTSS & (~FDCAN_TTSS_TS_EN);

    if(Cmd != DISABLE)
    {
        tempReg |= FDCAN_EXT_TIMESTAMP_ENABLE;
    }

    FDCANx->TTSS = tempReg;
}


/**
 *\*\name   FDCAN_Get_Index.
 *\*\fun    Get the index number of FDCANx.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return none
 */
static uint8_t FDCAN_Get_Index(FDCAN_Module *FDCANx)
{
    uint32_t FDCANIndex;

    if(FDCANx == FDCAN1)
    {
        FDCANIndex = 0;
    }
    else if(FDCANx == FDCAN2)
    {
        FDCANIndex = 1;
    }
    else if(FDCANx == FDCAN3)
    {
        FDCANIndex = 2;
    }
    else if(FDCANx == FDCAN4)
    {
        FDCANIndex = 3;
    }
    else if(FDCANx == FDCAN5)
    {
        FDCANIndex = 4;
    }
    else if(FDCANx == FDCAN6)
    {
        FDCANIndex = 5;
    }
    else if(FDCANx == FDCAN7)
    {
        FDCANIndex = 6;
    }
    else
    {
        FDCANIndex = 7;
    }

    return (uint8_t)FDCANIndex;
}


