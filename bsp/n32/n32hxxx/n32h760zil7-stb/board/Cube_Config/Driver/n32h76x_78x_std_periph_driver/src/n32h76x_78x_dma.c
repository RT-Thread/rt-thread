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
 * @file n32h76x_78x_dma.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "n32h76x_78x_dma.h"


#define DMA_EVENT_MAX              (5U)


/**
*\*\name    DMA_ControllerCmd.
*\*\fun     Enable or disable DMA Controller peripheral.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void DMA_ControllerCmd(DMA_Module *const DMAy, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the DMA Controller */
        SET_BIT(DMAy->CFG, DMA_CFG_EN);
    }
    else
    {
        /* Disable the DMA Controller */
        CLEAR_BIT(DMAy->CFG, DMA_CFG_EN);
    }
}

/**
*\*\name    DMA_ControllerIsEnabled.
*\*\fun     Check DMA Controller peripheral is enabled.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\return  true or false
**/
bool DMA_ControllerIsEnabled(DMA_Module *const DMAy)
{
    bool ret;
    ret = READ_BIT(DMAy->CFG, DMA_CFG_EN) ? true : false;
    return ret;
}

/**
*\*\name    DMA_ChannelCmd.
*\*\fun     Enable or disable a DMA channel.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void DMA_ChannelCmd(DMA_Module *const DMAy, DMA_ChNumType ChNum, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the DMA channel */
        WRITE_REG(DMAy->CHEN, (DMA_CH_ENABLE << ChNum));
    }
    else
    {
        /* Disable the DMA channel */
        WRITE_REG(DMAy->CHEN, (DMA_CH_DISABLE << ChNum));

        while (READ_BIT((uint8_t)DMAy->CHEN, ((uint8_t)0x1U << ChNum)) != 0U)
        {
            /* Wait until channel is disabled */
        }
    }
}

/**
*\*\name    DMA_ChannelIsEnabled.
*\*\fun     Check whether a DMA channel enabled.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\return  true or false
**/
bool DMA_ChannelIsEnabled(DMA_Module *const DMAy, DMA_ChNumType ChNum)
{
    bool ret;
    ret = READ_BIT((uint8_t)DMAy->CHEN, ((uint8_t)0x1U << ChNum)) ? true : false;
    return ret;
}

/**
*\*\name    DMA_ChannelInit.
*\*\fun     Initialize a DMA channel with provided channel configuration.
*\*\        The function sets up the following channel configuration parameters for
*\*\        a DMA channel specified paramters like:
*\*\        Source and Destination addresses (and linked list address if required).
*\*\        Source and Destination handshake method as software/hardware selection.
*\*\        Scatter/gather configuration and transfer flow and transfer type.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   DMA_ChInitParam :
*\*\          - Pointer to the DMA_ChInitType structure which will be initialized.
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\return  One of DMA_ChStatusType.
**/
DMA_ChStatusType DMA_ChannelInit(DMA_Module *const DMAy, DMA_ChInitType *const DMA_ChInitParam, DMA_ChNumType ChNum)
{
    uint32_t TempValue;
    DMA_ChStatusType RetStatus;

    /* Check whether the specified DMA controller is enabled */
    if (DMA_ControllerIsEnabled(DMAy) == ENABLE)
    {
        /* Checks whether the specified DMA channel is disabled */
        if (DMA_ChannelIsEnabled(DMAy, ChNum) == DISABLE)
        {
            /* Sets channel n source address register */
            WRITE_REG(DMAy->CH[ChNum].SA, DMA_ChInitParam->SrcAddr);
            /* Sets channel n destination address register */
            WRITE_REG(DMAy->CH[ChNum].DA, DMA_ChInitParam->DstAddr);
            /* Sets channel n linked list pointer register */
            WRITE_REG(DMAy->CH[ChNum].LLP, (uint32_t)DMA_ChInitParam->pLinkListItem);
            /* Sets channel n control register */
            WRITE_REG(DMAy->CH[ChNum].CTRL, DMA_ChInitParam->ChCtrl);

            /* Sets channel n priority */
            MODIFY_REG(DMAy->CH[ChNum].CFG, DMA_CHNCFG_CHPRIOR, ((uint64_t)DMA_ChInitParam->ChannelPriority << 0x5U));
            /* Sets channel n source handshaking interface polarity */
            MODIFY_REG(DMAy->CH[ChNum].CFG, DMA_CHNCFG_SRCHSPOL, ((uint64_t)DMA_ChInitParam->SrcHsInterfacePol << 0x13U));
            /* Sets channel n destination handshaking interface polarity */
            MODIFY_REG(DMAy->CH[ChNum].CFG, DMA_CHNCFG_DSTHSPOL, ((uint64_t)DMA_ChInitParam->DstHsInterfacePol << 0x12U));

            /* Configure scatter and gather */
            if (DMA_ChInitParam->SrcGatherEn)
            {
                /* Write the DMA_CHnSG register */
                WRITE_REG(DMAy->CH[ChNum].SG, DMA_ChInitParam->SrcGatherCtrl);
            }

            if (DMA_ChInitParam->DstScatterEn)
            {
                /* Write the DMA_CHnDS register */
                WRITE_REG(DMAy->CH[ChNum].DS, DMA_ChInitParam->DstScatterCtrl);
            }

            /* Configure source handshaking hardware mode */
            if (DMA_ChInitParam->SrcHandshaking == DMA_CH_SRC_HANDSHAKING_HARDWARE)
            {
                if ((DMA_ChInitParam->TfrTypeFlowCtrl == DMA_CH_TRANSFER_FLOW_P2M_DMA) || \
                        (DMA_ChInitParam->TfrTypeFlowCtrl == DMA_CH_TRANSFER_FLOW_P2P_DMA))
                {
                    TempValue = ((uint32_t)DMA_ChInitParam->SrcHsInterface & 0x7U);
                    /* Select hardware handshake I/F [0-7] */
                    MODIFY_REG(DMAy->CH[ChNum].CFG, DMA_CHNCFG_SRCPER, ((uint64_t)TempValue << 0x27U));

                    /* Enable hardware handshake to source peripheral */
                    CLEAR_BIT(DMAy->CH[ChNum].CFG, DMA_CHNCFG_HSSELSRC);
                }
            }

            /* Configure destination handshaking hardware mode */
            if (DMA_ChInitParam->DstHandshaking == DMA_CH_DST_HANDSHAKING_HARDWARE)
            {
                /* Hardware handshaking interface configuration */
                if ((DMA_ChInitParam->TfrTypeFlowCtrl == DMA_CH_TRANSFER_FLOW_M2P_DMA) || \
                        (DMA_ChInitParam->TfrTypeFlowCtrl == DMA_CH_TRANSFER_FLOW_P2P_DMA))
                {
                    TempValue = ((uint32_t)DMA_ChInitParam->DstHsInterface & 0x7U);
                    /* Select hardware handshake I/F [0-7] */
                    MODIFY_REG(DMAy->CH[ChNum].CFG, DMA_CHNCFG_DSTPER, ((uint64_t)TempValue << 0x2BU));

                    /* Enable hardware handshake to destionation peripheral */
                    CLEAR_BIT(DMAy->CH[ChNum].CFG, DMA_CHNCFG_HSSELDST);
                }
            }

            /* Clear interrupt event status */
            DMA_ClearChannelEventStatus(DMAy, ChNum, (uint32_t)((uint32_t)DMA_CH_EVENT_TRANSFER_COMPLETE | \
                                        (uint32_t)DMA_CH_EVENT_BLOCK_TRANSFER_COMPLETE | \
                                        (uint32_t)DMA_CH_EVENT_SRC_TRANSACTION_COMPLETE | \
                                        (uint32_t)DMA_CH_EVENT_DST_TRANSACTION_COMPLETE | \
                                        (uint32_t)DMA_CH_EVENT_ERROR));

            /* Configure the block tranfer type according to settings */
            switch (DMA_ChInitParam->TfrType)
            {
                case DMA_CH_TRANSFER_TYPE_SINGLE_BLOCK:
                    break;

                case DMA_CH_TRANSFER_TYPE_MULTI_BLOCK_SRCADR_CONTIGUOUS_DSTADR_RELOAD:
                    SET_BIT(DMAy->CH[ChNum].CFG, DMA_CHNCFG_ADR);
                    break;

                case DMA_CH_TRANSFER_TYPE_MULTI_BLOCK_SRCADR_RELOAD_DSTADR_CONTIGUOUS:
                    SET_BIT(DMAy->CH[ChNum].CFG, DMA_CHNCFG_ASR);
                    break;

                case DMA_CH_TRANSFER_TYPE_MULTI_BLOCK_SRCADR_RELOAD_DSTADR_RELOAD:
                    SET_BIT(DMAy->CH[ChNum].CFG, (DMA_CHNCFG_ADR | DMA_CHNCFG_ASR));
                    break;

                case DMA_CH_TRANSFER_TYPE_MULTI_BLOCK_SRCADR_CONTIGUOUS_DSTADR_LINKED:
                    SET_BIT(DMAy->CH[ChNum].CTRL, DMA_CHNCTRL_LLPDSTEN);
                    break;

                case DMA_CH_TRANSFER_TYPE_MULTI_BLOCK_SRCADR_RELOAD_DSTADR_LINKED:
                    SET_BIT(DMAy->CH[ChNum].CFG, DMA_CHNCFG_ASR);
                    SET_BIT(DMAy->CH[ChNum].CTRL, DMA_CHNCTRL_LLPDSTEN);
                    break;

                case DMA_CH_TRANSFER_TYPE_MULTI_BLOCK_SRCADR_LINKED_DSTADR_CONTIGUOUS:
                    SET_BIT(DMAy->CH[ChNum].CTRL, DMA_CHNCTRL_LLPSRCEN);
                    break;

                case DMA_CH_TRANSFER_TYPE_MULTI_BLOCK_SRCADR_LINKED_DSTADR_RELOAD:
                    SET_BIT(DMAy->CH[ChNum].CFG, DMA_CHNCFG_ADR);
                    SET_BIT(DMAy->CH[ChNum].CTRL, DMA_CHNCTRL_LLPSRCEN);
                    break;

                case DMA_CH_TRANSFER_TYPE_MULTI_BLOCK_SRCADR_LINKED_DSTADR_LINKED:
                    SET_BIT(DMAy->CH[ChNum].CTRL, (DMA_CHNCTRL_LLPSRCEN | DMA_CHNCTRL_LLPDSTEN));
                    break;

                default:
                    break;
            }

            RetStatus = DMA_CH_STS_OK;
        }
        else
        {
            RetStatus = DMA_CH_STS_BUSY;
        }
    }
    else
    {
        RetStatus = DMA_CH_STS_ERROR;
    }

    return RetStatus;
}

/**
*\*\name    DMA_ChannelStructInit.
*\*\fun     Initializes the structure parameter of type DMA_ChInitType used to
*\*\        initialize DMA. This function is usually called before initializing
*\*\        a parameter of type DMA_ChInitType.
*\*\param   DMA_ChInitParam :
*\*\          - Pointer to the DMA_ChInitType structure which will be initialized.
*\*\return  none
**/
void DMA_ChannelStructInit(DMA_ChInitType *const DMA_ChInitParam)
{
    DMA_ChInitParam->IntEn              = true;
    DMA_ChInitParam->DstTfrWidth        = DMA_CH_TRANSFER_WIDTH_8;
    DMA_ChInitParam->SrcTfrWidth        = DMA_CH_TRANSFER_WIDTH_8;
    DMA_ChInitParam->DstAddrCountMode   = DMA_CH_ADDRESS_COUNT_MODE_INCREMENT;
    DMA_ChInitParam->SrcAddrCountMode   = DMA_CH_ADDRESS_COUNT_MODE_INCREMENT;
    DMA_ChInitParam->DstBurstLen        = DMA_CH_BURST_LENGTH_4;
    DMA_ChInitParam->SrcBurstLen        = DMA_CH_BURST_LENGTH_4;
    DMA_ChInitParam->SrcGatherEn        = false;
    DMA_ChInitParam->DstScatterEn       = false;
    DMA_ChInitParam->DstMasterSelect    = DMA_CH_AHB_MASTER_1;
    DMA_ChInitParam->SrcMasterSelect    = DMA_CH_AHB_MASTER_1;
    DMA_ChInitParam->TfrTypeFlowCtrl    = DMA_CH_TRANSFER_FLOW_P2P_DMA;
    DMA_ChInitParam->BlkTfrSize         = 0x2U;
    DMA_ChInitParam->SrcAddr            = 0x0U;
    DMA_ChInitParam->DstAddr            = 0x0U;
    DMA_ChInitParam->pLinkListItem      = NULL;
    DMA_ChInitParam->SrcGatherInterval  = 0x0U;
    DMA_ChInitParam->SrcGatherCount     = 0x0U;
    DMA_ChInitParam->DstScatterInterval = 0x0U;
    DMA_ChInitParam->DstScatterCount    = 0x0U;
    DMA_ChInitParam->TfrType            = DMA_CH_TRANSFER_TYPE_SINGLE_BLOCK;
    DMA_ChInitParam->ChannelPriority    = DMA_CH_PRIORITY_0;
    DMA_ChInitParam->SrcHandshaking     = DMA_CH_SRC_HANDSHAKING_SOFTWARE;
    DMA_ChInitParam->SrcHsInterface     = DMA_CH_HARDWARE_HANDSHAKING_IF_0;
    DMA_ChInitParam->SrcHsInterfacePol  = DMA_CH_HANDSHAKING_IF_POL_H;
    DMA_ChInitParam->DstHandshaking     = DMA_CH_DST_HANDSHAKING_SOFTWARE;
    DMA_ChInitParam->DstHsInterface     = DMA_CH_HARDWARE_HANDSHAKING_IF_0;
    DMA_ChInitParam->DstHsInterfacePol  = DMA_CH_HANDSHAKING_IF_POL_H;
}

/**
*\*\name    DMA_ChannelSuspend.
*\*\fun     Suspend a DMA channel.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\return  none
**/
void DMA_ChannelSuspend(DMA_Module *const DMAy, DMA_ChNumType ChNum)
{
    /* Sets the CHSUSP bit of the CHnCFG register */
    SET_BIT(DMAy->CH[ChNum].CFG, DMA_CHNCFG_CHSUSP);
}

/**
*\*\name    DMA_ChannelIsSuspended.
*\*\fun     Check whether a DMA channel suspended.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\return  true or false
**/
bool DMA_ChannelIsSuspended(DMA_Module *const DMAy, DMA_ChNumType ChNum)
{
    bool ret;
    ret = READ_BIT(DMAy->CH[ChNum].CFG, DMA_CHNCFG_CHSUSP) ? true : false;
    return ret;
}

/**
*\*\name    DMA_ChannelResume.
*\*\fun     Resume a DMA channel.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\return  none
**/
void DMA_ChannelResume(DMA_Module *const DMAy, DMA_ChNumType ChNum)
{
    /* Clear the CHSUSP bit of the CHnCFG register */
    CLEAR_BIT(DMAy->CH[ChNum].CFG, DMA_CHNCFG_CHSUSP);
}

/**
*\*\name    DMA_ChannelEventCmd.
*\*\fun     Enable or disable a DMA event.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\param   Event (The input parameter must be one or more of the following values (logical OR)):
*\*\          - DMA_CH_EVENT_TRANSFER_COMPLETE
*\*\          - DMA_CH_EVENT_BLOCK_TRANSFER_COMPLETE
*\*\          - DMA_CH_EVENT_SRC_TRANSACTION_COMPLETE
*\*\          - DMA_CH_EVENT_DST_TRANSACTION_COMPLETE
*\*\          - DMA_CH_EVENT_ERROR
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void DMA_ChannelEventCmd(DMA_Module *const DMAy, DMA_ChNumType ChNum, uint32_t Event, FunctionalStatus Cmd)
{
    uint32_t TempIndex;
    __IO uint32_t *pIntMaskRegBase = &DMAy->TCINTMSK;

    if (Cmd != DISABLE)
    {
        /* Enable the DMA Channel Interrupt Event */
        for (TempIndex = 0U; TempIndex < DMA_EVENT_MAX; TempIndex++)
        {
            if (Event & ((uint32_t)0x1U << TempIndex))
            {
                WRITE_REG(*(pIntMaskRegBase + (TempIndex * 2U)), ((uint32_t)DMA_INT_UNMASK << ChNum));
            }
        }
    }
    else
    {
        /* Disable the DMA Channel Interrupt Event */
        for (TempIndex = 0U; TempIndex < DMA_EVENT_MAX; TempIndex++)
        {
            if (Event & ((uint32_t)0x1U << TempIndex))
            {
                WRITE_REG(*(pIntMaskRegBase + (TempIndex * 2U)), ((uint32_t)DMA_INT_MASK << ChNum));
            }
        }
    }
}

/**
*\*\name    DMA_ClearChannelEventStatus.
*\*\fun     Clear a DMA channel event status.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\param   Event (The input parameter must be one or more of the following values (logical OR)):
*\*\          - DMA_CH_EVENT_TRANSFER_COMPLETE
*\*\          - DMA_CH_EVENT_BLOCK_TRANSFER_COMPLETE
*\*\          - DMA_CH_EVENT_SRC_TRANSACTION_COMPLETE
*\*\          - DMA_CH_EVENT_DST_TRANSACTION_COMPLETE
*\*\          - DMA_CH_EVENT_ERROR
*\*\return  none
**/
void DMA_ClearChannelEventStatus(DMA_Module *const DMAy, DMA_ChNumType ChNum, uint32_t Event)
{
    uint32_t TempIndex;
    __IO uint32_t *pIntClearRegBase = &DMAy->TCINTCLR;

    /* Clear the DMA Channel Interrupt Event */
    for (TempIndex = 0U; TempIndex < DMA_EVENT_MAX; TempIndex++)
    {
        if (Event & ((uint32_t)0x1U << TempIndex))
        {
            WRITE_REG(*(pIntClearRegBase + (TempIndex * 2U)), ((uint32_t)0x1U << ChNum));
        }
    }
}

/**
*\*\name    DMA_GetCombinedStatus.
*\*\fun     Get a DMA combined interrupt status.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\return  DMA_INTCBESTS register value
**/
uint8_t DMA_GetCombinedStatus(DMA_Module *const DMAy)
{
    return (uint8_t)(READ_REG(DMAy->INTCBESTS) & 0x1FU);
}

/**
*\*\name    DMA_GetChannelIntTfrStatus.
*\*\fun     Gets the IntTfr interrupt event status for the specified channel.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\return  SET or RESET
**/
INTStatus DMA_GetChannelIntTfrStatus(DMA_Module *const DMAy, DMA_ChNumType ChNum)
{
    INTStatus RetStatus = RESET;

    /* Read the interrupt status of the corresponding register */
    if (READ_BIT(DMAy->TCINTSTS, (DMA_EVENT_TRANSFER_COMPLETE << ChNum)) != (uint32_t)RESET)
    {
        /* This status of the channel is SET */
        RetStatus = SET;
    }
    else
    {
        /* This status of the channel is RESET */
        RetStatus = RESET;
    }

    /* Return status */
    return RetStatus;
}

/**
*\*\name    DMA_GetChannelIntBlockStatus.
*\*\fun     Gets the IntBlock interrupt event status for the specified channel.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\return  SET or RESET
**/
INTStatus DMA_GetChannelIntBlockStatus(DMA_Module *const DMAy, DMA_ChNumType ChNum)
{
    INTStatus RetStatus = RESET;

    /* Read the interrupt status of the corresponding register */
    if (READ_BIT(DMAy->BTCINTSTS, (DMA_EVENT_BLOCK_TRANSFER_COMPLETE << ChNum)) != (uint32_t)RESET)
    {
        /* This status of the channel is SET */
        RetStatus = SET;
    }
    else
    {
        /* This status of the channel is RESET */
        RetStatus = RESET;
    }

    /* Return status */
    return RetStatus;
}

/**
*\*\name    DMA_GetChannelIntSrcTranStatus.
*\*\fun     Gets the IntSrcTran interrupt event status for the specified channel.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\return  SET or RESET
**/
INTStatus DMA_GetChannelIntSrcTranStatus(DMA_Module *const DMAy, DMA_ChNumType ChNum)
{
    INTStatus RetStatus = RESET;

    /* Read the interrupt status of the corresponding register */
    if (READ_BIT(DMAy->STCINTSTS, (DMA_EVENT_SRC_TRANSACTION_COMPLETE << ChNum)) != (uint32_t)RESET)
    {
        /* This status of the channel is SET */
        RetStatus = SET;
    }
    else
    {
        /* This status of the channel is RESET */
        RetStatus = RESET;
    }

    /* Return status */
    return RetStatus;
}

/**
*\*\name    DMA_GetChannelIntDstTranStatus.
*\*\fun     Gets the IntDstTran interrupt event status for the specified channel.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\return  SET or RESET
**/
INTStatus DMA_GetChannelIntDstTranStatus(DMA_Module *const DMAy, DMA_ChNumType ChNum)
{
    INTStatus RetStatus = RESET;

    /* Read the interrupt status of the corresponding register */
    if (READ_BIT(DMAy->DTCINTSTS, (DMA_EVENT_DST_TRANSACTION_COMPLETE << ChNum)) != (uint32_t)RESET)
    {
        /* This status of the channel is SET */
        RetStatus = SET;
    }
    else
    {
        /* This status of the channel is RESET */
        RetStatus = RESET;
    }

    /* Return status */
    return RetStatus;
}

/**
*\*\name    DMA_GetChannelIntErrStatus.
*\*\fun     Gets the IntErr interrupt event status for the specified channel.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\return  SET or RESET
**/
INTStatus DMA_GetChannelIntErrStatus(DMA_Module *const DMAy, DMA_ChNumType ChNum)
{
    INTStatus RetStatus = RESET;

    /* Read the interrupt status of the corresponding register */
    if (READ_BIT(DMAy->ERRINTSTS, (DMA_EVENT_ERROR << ChNum)) != (uint32_t)RESET)
    {
        /* This status of the channel is SET */
        RetStatus = SET;
    }
    else
    {
        /* This status of the channel is RESET */
        RetStatus = RESET;
    }

    /* Return status */
    return RetStatus;
}

/**
*\*\name    DMA_ChannelSourceGatherCmd.
*\*\fun     Enable or disable a DMA Channel source gather.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void DMA_ChannelSourceGatherCmd(DMA_Module *const DMAy, DMA_ChNumType ChNum, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the Source gather */
        SET_BIT(DMAy->CH[ChNum].CTRL, DMA_CHNCTRL_SRCGATEN);
    }
    else
    {
        /* Disable the Source gather */
        CLEAR_BIT(DMAy->CH[ChNum].CTRL, DMA_CHNCTRL_SRCGATEN);
    }
}

/**
*\*\name    DMA_SetChannelSourceGather.
*\*\fun     Sets the source gather interval and count of the specified channel.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\param   Interval:
*\*\          - Source Gather Interval (0~0xFFFFF)
*\*\param   Count:
*\*\          - Source contiguous transfer count between successive gather boundaries (0~0x1FF)
*\*\return  none
**/
void DMA_SetChannelSourceGather(DMA_Module *const DMAy, DMA_ChNumType ChNum, uint32_t Interval, uint16_t Count)
{
    WRITE_REG(DMAy->CH[ChNum].SG, (Interval | (Count << 20U)));
}

/**
*\*\name    DMA_ChannelDestinationScatterCmd.
*\*\fun     Enable or disable a DMA Channel destination scatter.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void DMA_ChannelDestinationScatterCmd(DMA_Module *const DMAy, DMA_ChNumType ChNum, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the destination scatter */
        SET_BIT(DMAy->CH[ChNum].CTRL, DMA_CHNCTRL_DSTSCAEN);
    }
    else
    {
        /* Disable the destination scatter */
        CLEAR_BIT(DMAy->CH[ChNum].CTRL, DMA_CHNCTRL_DSTSCAEN);
    }
}

/**
*\*\name    DMA_SetChannelDestinationScatter.
*\*\fun     Sets the destination scatter interval and count of the specified channel.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\param   Interval:
*\*\          - Destination scatter Interval (0~0xFFFFF)
*\*\param   Count:
*\*\          - Destination contiguous transfer count between successive scatter boundaries (0~0x1FF)
*\*\return  none
**/
void DMA_SetChannelDestinationScatter(DMA_Module *const DMAy, DMA_ChNumType ChNum, uint32_t Interval, uint16_t Count)
{
    WRITE_REG(DMAy->CH[ChNum].DS, (Interval | (Count << 20U)));
}

/**
*\*\name    DMA_SetChannelSourceAddress.
*\*\fun     Sets the source address of the specified channel.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\param   pAddr:
*\*\          - Pointer to source address
*\*\return  none
**/
void DMA_SetChannelSourceAddress(DMA_Module *const DMAy, DMA_ChNumType ChNum, uint32_t *pAddr)
{
    WRITE_REG(DMAy->CH[ChNum].SA, (uint32_t)pAddr);
}

/**
*\*\name    DMA_SetChannelDestinationAddress.
*\*\fun     Sets the destination address of the specified channel.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\param   pAddr:
*\*\          - Pointer to destination address
*\*\return  none
**/
void DMA_SetChannelDestinationAddress(DMA_Module *const DMAy, DMA_ChNumType ChNum, uint32_t *pAddr)
{
    WRITE_REG(DMAy->CH[ChNum].DA, (uint32_t)pAddr);
}

/**
*\*\name    DMA_SetChannelBlockSize.
*\*\fun     Sets the block transfer size of the specified channel.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\param   Size:
*\*\          - The transferred size
*\*\return  none
**/
void DMA_SetChannelBlockSize(DMA_Module *const DMAy, DMA_ChNumType ChNum, uint32_t Size)
{
    MODIFY_REG(DMAy->CH[ChNum].CTRL, DMA_CHNCTRL_BTS, ((uint64_t)Size << 32U));
}

/**
*\*\name    DMA_GetTransferredNumber.
*\*\fun     Gets the number of data that has been transmitted by the current channel.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\return  Number of data sent
**/
uint16_t DMA_GetTransferredNumber(DMA_Module *const DMAy, DMA_ChNumType ChNum)
{
    return (uint16_t)(READ_BIT(DMAy->CH[ChNum].CTRL, DMA_CHNCTRL_BTS) >> 32U);
}

/**
*\*\name    DMA_SetChannelLinkedListPointer.
*\*\fun     Sets linked list pointer function.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\param   pStr:
*\*\          - Pointer to DMA linked list item structure
*\*\return  none
**/
void DMA_SetChannelLinkedListPointer(DMA_Module *const DMAy, DMA_ChNumType ChNum, DMA_LinkListItemType* pStr)
{
    WRITE_REG(DMAy->CH[ChNum].LLP, (uint32_t)pStr);
}

/**
*\*\name    DMA_TriggerSourceRequest.
*\*\fun     Trigger a software source handshake request.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\param   Type (The input parameters must be the following values):
*\*\          - DMA_CH_TRANSACTION_TYPE_SINGLE
*\*\          - DMA_CH_TRANSACTION_TYPE_BURST
*\*\param   isLast:
*\*\          - true or false
*\*\return  none
**/
void DMA_TriggerSourceRequest(DMA_Module *const DMAy, DMA_ChNumType ChNum, DMA_ChTransacType Type, bool isLast)
{
    if (Type == DMA_CH_TRANSACTION_TYPE_SINGLE)
    {
        /* Enable Channel n Source Single Transaction Request */
        WRITE_REG(DMAy->SRCSGTREQ, (DMA_SSTR_ENABLE << ChNum));
    }

    if (isLast == true)
    {
        /* Enable Channel n Source Last Transaction Request */
        WRITE_REG(DMAy->SRCLTREQ, (DMA_SLTR_ENABLE << ChNum));
    }

    /* Enable Channel n Source Transaction Request */
    WRITE_REG(DMAy->SRCSWTREQ, (DMA_STR_ENABLE << ChNum));
}

/**
*\*\name    DMA_TriggerDestinationRequest.
*\*\fun     Trigger a software Destination handshake request.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\param   Type (The input parameters must be the following values):
*\*\          - DMA_CH_TRANSACTION_TYPE_SINGLE
*\*\          - DMA_CH_TRANSACTION_TYPE_BURST
*\*\param   isLast:
*\*\          - true or false
*\*\return  none
**/
void DMA_TriggerDestinationRequest(DMA_Module *const DMAy, DMA_ChNumType ChNum, DMA_ChTransacType Type, bool isLast)
{
    if (Type == DMA_CH_TRANSACTION_TYPE_SINGLE)
    {
        /* Enable Channel n Destination Single Transaction Request */
        WRITE_REG(DMAy->DSTSGTREQ, (DMA_DSTR_ENABLE << ChNum));
    }

    if (isLast == true)
    {
        /* Enable Channel n Destination Last Transaction Request */
        WRITE_REG(DMAy->DSTLTREQ, (DMA_DLTR_ENABLE << ChNum));
    }

    /* Enable Channel n Destination Transaction Request */
    WRITE_REG(DMAy->DSTSWTREQ, (DMA_DTR_ENABLE << ChNum));
}

/**
*\*\name    DMA_ChannelSourceAddressReloadCmd.
*\*\fun     Enable or disable a DMA Channel source address reload.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void DMA_ChannelSourceAddressReloadCmd(DMA_Module *const DMAy, DMA_ChNumType ChNum, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the Automatic Source Reload */
        SET_BIT(DMAy->CH[ChNum].CFG, DMA_CHNCFG_ASR);
    }
    else
    {
        /* Disable the Automatic Source Reload */
        CLEAR_BIT(DMAy->CH[ChNum].CFG, DMA_CHNCFG_ASR);
    }
}

/**
*\*\name    DMA_ChannelDestinationAddressReloadCmd.
*\*\fun     Enable or disable a DMA Channel destination address reload.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void DMA_ChannelDestinationAddressReloadCmd(DMA_Module *const DMAy, DMA_ChNumType ChNum, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the Automatic Destination Reload */
        SET_BIT(DMAy->CH[ChNum].CFG, DMA_CHNCFG_ADR);
    }
    else
    {
        /* Disable the Automatic Destination Reload */
        CLEAR_BIT(DMAy->CH[ChNum].CFG, DMA_CHNCFG_ADR);
    }
}

/**
*\*\name    DMA_ChannelBusLockCmd.
*\*\fun     Enable or disable a DMA Channel bus lock.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void DMA_ChannelBusLockCmd(DMA_Module *const DMAy, DMA_ChNumType ChNum, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the DMA Channel bus lock */
        SET_BIT(DMAy->CH[ChNum].CFG, DMA_CHNCFG_LOCKB);
    }
    else
    {
        /* Disable the DMA Channel bus lock */
        CLEAR_BIT(DMAy->CH[ChNum].CFG, DMA_CHNCFG_LOCKB);
    }
}

/**
*\*\name    DMA_ChannelLockCmd.
*\*\fun     Enable or disable a DMA Channel lock.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void DMA_ChannelLockCmd(DMA_Module *const DMAy, DMA_ChNumType ChNum, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the DMA Channel lock */
        SET_BIT(DMAy->CH[ChNum].CFG, DMA_CHNCFG_LOCKCH);
    }
    else
    {
        /* Disable the DMA Channel lock */
        CLEAR_BIT(DMAy->CH[ChNum].CFG, DMA_CHNCFG_LOCKCH);
    }
}

/**
*\*\name    DMA_SetChannelBusLockLevel.
*\*\fun     Set DMA Channel bus lock level.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\param   Level (The input parameters must be the following values):
*\*\          - DMA_CH_BUS_LOCK_LEVEL_OCDMATFR
*\*\          - DMA_CH_BUS_LOCK_LEVEL_OCDMABLKTFR
*\*\          - DMA_CH_BUS_LOCK_LEVEL_OCDMATRAN
*\*\return  none
**/
void DMA_SetChannelBusLockLevel(DMA_Module *const DMAy, DMA_ChNumType ChNum, uint64_t Level)
{
    /* Set the DMA Channel bus lock level */
    MODIFY_REG(DMAy->CH[ChNum].CFG, DMA_CHNCFG_LOCKBL, Level);
}

/**
*\*\name    DMA_SetChannelLockLevel.
*\*\fun     Set DMA Channel lock level.
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\          - DMA3
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - DMA_CHANNEL_0
*\*\          - DMA_CHANNEL_1
*\*\          - DMA_CHANNEL_2
*\*\          - DMA_CHANNEL_3
*\*\          - DMA_CHANNEL_4
*\*\          - DMA_CHANNEL_5
*\*\          - DMA_CHANNEL_6
*\*\          - DMA_CHANNEL_7
*\*\param   Level (The input parameters must be the following values):
*\*\          - DMA_CH_LOCK_LEVEL_OCDMATFR
*\*\          - DMA_CH_LOCK_LEVEL_OCDMABLKTFR
*\*\          - DMA_CH_LOCK_LEVEL_OCDMATRAN
*\*\return  none
**/
void DMA_SetChannelLockLevel(DMA_Module *const DMAy, DMA_ChNumType ChNum, uint64_t Level)
{
    /* Set the DMA Channel lock level */
    MODIFY_REG(DMAy->CH[ChNum].CFG, DMA_CHNCFG_LOCKCHL, Level);
}
