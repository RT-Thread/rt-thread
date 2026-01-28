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
 * @file n32h76x_78x_mdma.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "n32h76x_78x_mdma.h"


/**
*\*\name    MDMA_ControllerCmd.
*\*\fun     Enable or disable MDMA Controller peripheral.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void MDMA_ControllerCmd(MDMA_Module *const MDMAy, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the MDMA Controller */
        SET_BIT(MDMAy->CFG, MDMA_CFG_EN);
    }
    else
    {
        /* Disable the MDMA Controller */
        CLEAR_BIT(MDMAy->CFG, MDMA_CFG_EN);
    }
}

/**
*\*\name    MDMA_ControllerIsEnabled.
*\*\fun     Check MDMA Controller peripheral is enabled.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\return  true or false
**/
bool MDMA_ControllerIsEnabled(MDMA_Module *const MDMAy)
{
    bool ret;
    ret = READ_BIT(MDMAy->CFG, MDMA_CFG_EN) ? true : false;
    return ret;
}

/**
*\*\name    MDMA_ControllerSoftReset.
*\*\fun     Software Reset MDMA Controller.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\return  none
**/
void MDMA_ControllerSoftReset(MDMA_Module *const MDMAy)
{
    /* Sets MDMA reset request bit */
    SET_BIT(MDMAy->SWRST, MDMA_SWRST_RSTREQ);

    /* Wait until reset request bit is 0 */
    while ((READ_BIT(MDMAy->SWRST, MDMA_SWRST_RSTREQ)))
    {
        /* Wait for reset to complete */
    }
}

/**
*\*\name    MDMA_ChannelCmd.
*\*\fun     Enable or disable a MDMA channel.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void MDMA_ChannelCmd(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the MDMA channel */
        WRITE_REG(MDMAy->CHEN, (MDMA_CH_ENABLE << ChNum));
    }
    else
    {
        /* Disable the MDMA channel */
        WRITE_REG(MDMAy->CHEN, (MDMA_CH_DISABLE << ChNum));

        while (READ_BIT((uint16_t)MDMAy->CHEN, ((uint16_t)0x1U << ChNum)) != 0U)
        {
            /* Wait until channel is disabled */
        }
    }
}

/**
*\*\name    MDMA_ChannelIsEnabled.
*\*\fun     Check whether a MDMA channel enabled.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\return  true or false
**/
bool MDMA_ChannelIsEnabled(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum)
{
    bool ret;
    ret = READ_BIT((uint16_t)MDMAy->CHEN, ((uint16_t)0x1U << ChNum)) ? true : false;
    return ret;
}

/**
*\*\name    MDMA_ChannelInit.
*\*\fun     Initialize a MDMA channel with provided channel configuration
*\*\        The function sets up the following channel configuration parameters for
*\*\        a MDMA channel specified paramters like:
*\*\           Source and Destination addresses ( and linked list address if required)
*\*\           Source and Destination handshake method as software/hardware selection
*\*\           and transfer flow and transfer type
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   MDMA_ChInitParam :
*\*\          - Pointer to the MDMA_ChInitType structure which will be initialized.
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\return  One of MDMA_ChStatusType.
**/
MDMA_ChStatusType MDMA_ChannelInit(MDMA_Module *const MDMAy, MDMA_ChInitType *const MDMA_ChInitParam, MDMA_ChNumType ChNum)
{
    uint32_t TempValue;
    MDMA_ChStatusType RetStatus;

    /* Check whether the specified MDMA controller is enabled */
    if (MDMA_ControllerIsEnabled(MDMAy) == ENABLE)
    {
        /* Checks whether the specified MDMA channel is disabled */
        if (MDMA_ChannelIsEnabled(MDMAy, ChNum) == DISABLE)
        {
            /* Sets channel n source multi-block transfer type */
            MODIFY_REG(MDMAy->CH[ChNum].CFG, MDMA_CHNCFG_SMBTT, ((uint64_t)MDMA_ChInitParam->SrcMultBlkTfrType << 0x00U));
            /* Sets channel n destination multi-block transfer type */
            MODIFY_REG(MDMAy->CH[ChNum].CFG, MDMA_CHNCFG_DMBTT, ((uint64_t)MDMA_ChInitParam->DstMultBlkTfrType << 0x02U));

            /* Sets channel n transfer type and flow control */
            MODIFY_REG(MDMAy->CH[ChNum].CFG, MDMA_CHNCFG_TTFC, ((uint64_t)MDMA_ChInitParam->TfrTypeFlowCtrl << 0x20U));
            /* Sets channel n priority */
            MODIFY_REG(MDMAy->CH[ChNum].CFG, MDMA_CHNCFG_CHPRIOR, ((uint64_t)MDMA_ChInitParam->ChannelPriority << 0x2FU));

            /* Configure source handshaking hardware mode */
            if (MDMA_ChInitParam->SrcHandshaking == MDMA_CH_SRC_HANDSHAKING_HARDWARE)
            {
                TempValue = ((uint32_t)MDMA_ChInitParam->SrcHsInterface & 0xFU);
                /* Select hardware handshake I/F [0-15] */
                MODIFY_REG(MDMAy->CH[ChNum].CFG, MDMA_CHNCFG_SRCPER, ((uint64_t)TempValue << 0x4U));

                /* Sets source hardware handshaking interface polarity */
                MODIFY_REG(MDMAy->CH[ChNum].CFG, MDMA_CHNCFG_SRCHHIPOL, ((uint64_t)MDMA_ChInitParam->SrcHsInterfacePol << 0x25U));

                /* Enable hardware handshake to source peripheral */
                CLEAR_BIT(MDMAy->CH[ChNum].CFG, MDMA_CHNCFG_HSSELSRC);
            }

            /* Configure destination handshaking hardware mode */
            if (MDMA_ChInitParam->DstHandshaking == MDMA_CH_DST_HANDSHAKING_HARDWARE)
            {
                TempValue = ((uint32_t)MDMA_ChInitParam->DstHsInterface & 0xFU);
                /* Select hardware handshake I/F [0-15] */
                MODIFY_REG(MDMAy->CH[ChNum].CFG, MDMA_CHNCFG_DSTPER, ((uint64_t)TempValue << 0xBU));

                /* Sets destination hardware handshaking interface polarity */
                MODIFY_REG(MDMAy->CH[ChNum].CFG, MDMA_CHNCFG_DSTHHIPOL, ((uint64_t)MDMA_ChInitParam->DstHsInterfacePol << 0x26U));

                /* Enable hardware handshake to destionation peripheral */
                CLEAR_BIT(MDMAy->CH[ChNum].CFG, MDMA_CHNCFG_HSSELDST);
            }

            /* Sets channel n source address register */
            WRITE_REG(MDMAy->CH[ChNum].SA, MDMA_ChInitParam->SrcAddr);
            /* Sets channel n destination address register */
            WRITE_REG(MDMAy->CH[ChNum].DA, MDMA_ChInitParam->DstAddr);
            /* Sets channel n linked list pointer register */
            WRITE_REG(MDMAy->CH[ChNum].LLP, (uint32_t)MDMA_ChInitParam->pLinkListItem);
            /* Sets channel n block transfer size register */
            WRITE_REG(MDMAy->CH[ChNum].BTS, MDMA_ChInitParam->BlkSize);
            /* Sets channel n control register */
            WRITE_REG(MDMAy->CH[ChNum].CTRL, MDMA_ChInitParam->ChCtrl);

            /* Clear the MDMA all common register interrupt status */
            WRITE_REG(MDMAy->CRINTCLR, MDMA_COMMON_INT_CLEAR);
            /* Clear the all interrupt status for the specified MDMA channel */
            WRITE_REG(MDMAy->CH[ChNum].INTCLR, MDMA_CH_INT_CLEAR);

            /* Disable common register interrupt status */
            CLEAR_BIT(MDMAy->CRINTSTSEN, MDMA_COMMON_INT_STS_MASK);
            /* Disable common register interrupt signal */
            CLEAR_BIT(MDMAy->CRINTSGLEN, MDMA_COMMON_INT_SGL_MASK);
            /* Disable Channel n interrupt status */
            CLEAR_BIT(MDMAy->CH[ChNum].INTSTSEN, MDMA_CH_INT_STS_MASK);
            /* Disable Channel n interrupt signal */
            CLEAR_BIT(MDMAy->CH[ChNum].INTSGLEN, MDMA_CH_INT_SGL_MASK);

            RetStatus = MDMA_CH_STS_OK;
        }
        else
        {
            RetStatus = MDMA_CH_STS_BUSY;
        }
    }
    else
    {
        RetStatus = MDMA_CH_STS_ERROR;
    }

    return RetStatus;
}

/**
*\*\name    MDMA_ChannelStructInit.
*\*\fun     Initializes the structure parameter of type MDMA_ChInitType used to
*\*\        initialize MDMA. This function is usually called before initializing
*\*\        a parameter of type MDMA_ChInitType.
*\*\param   MDMA_ChInitParam :
*\*\          - Pointer to the MDMA_ChInitType structure which will be initialized.
*\*\return  none
**/
void MDMA_ChannelStructInit(MDMA_ChInitType *const MDMA_ChInitParam)
{
    MDMA_ChInitParam->SrcMasterSel       = MDMA_CH_MASTER_1;
    MDMA_ChInitParam->DstMasterSel       = MDMA_CH_MASTER_1;
    MDMA_ChInitParam->SrcAddrInc         = MDMA_CH_ADDRESS_COUNT_MODE_INCREMENT;
    MDMA_ChInitParam->DstAddrInc         = MDMA_CH_ADDRESS_COUNT_MODE_INCREMENT;
    MDMA_ChInitParam->SrcTfrWidth        = MDMA_CH_TRANSFER_WIDTH_32;
    MDMA_ChInitParam->DstTfrWidth        = MDMA_CH_TRANSFER_WIDTH_32;
    MDMA_ChInitParam->SrcBurstTranLen    = MDMA_CH_BURST_TRAN_LEN_1;
    MDMA_ChInitParam->DstBurstTranLen    = MDMA_CH_BURST_TRAN_LEN_1;
    MDMA_ChInitParam->NonPosLastWriteEn  = false;
    MDMA_ChInitParam->SrcBurstLenEn      = false;
    MDMA_ChInitParam->SrcBurstLen        = 0x0U;
    MDMA_ChInitParam->DstBurstLenEn      = false;
    MDMA_ChInitParam->DstBurstLen        = 0x0U;
    MDMA_ChInitParam->IocBlkTfr          = false;
    MDMA_ChInitParam->SdwLlILast         = false;
    MDMA_ChInitParam->SdwLlIValid        = false;

    MDMA_ChInitParam->SrcAddr            = 0x0U;
    MDMA_ChInitParam->DstAddr            = 0x0U;
    MDMA_ChInitParam->pLinkListItem      = NULL;
    MDMA_ChInitParam->BlkSize            = 0x0U;

    MDMA_ChInitParam->ChannelPriority    = MDMA_CH_PRIORITY_15;
    MDMA_ChInitParam->SrcHandshaking     = MDMA_CH_SRC_HANDSHAKING_SOFTWARE;
    MDMA_ChInitParam->SrcHsInterface     = MDMA_CH_HARDWARE_HANDSHAKING_IF_0;
    MDMA_ChInitParam->SrcHsInterfacePol  = MDMA_CH_HARDWARE_HANDSHAKING_IF_POL_H;
    MDMA_ChInitParam->DstHandshaking     = MDMA_CH_DST_HANDSHAKING_SOFTWARE;
    MDMA_ChInitParam->DstHsInterface     = MDMA_CH_HARDWARE_HANDSHAKING_IF_0;
    MDMA_ChInitParam->DstHsInterfacePol  = MDMA_CH_HARDWARE_HANDSHAKING_IF_POL_H;

    MDMA_ChInitParam->TfrTypeFlowCtrl    = MDMA_CH_TRANSFER_FLOW_P2P_MDMA;
    MDMA_ChInitParam->SrcMultBlkTfrType  = MDMA_CH_MULTI_BLOCK_CONTIGUOUS;
    MDMA_ChInitParam->DstMultBlkTfrType  = MDMA_CH_MULTI_BLOCK_CONTIGUOUS;
}

/**
*\*\name    MDMA_ChannelSuspend.
*\*\fun     Suspend a MDMA channel.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\return  none
**/
void MDMA_ChannelSuspend(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum)
{
    /* Suspend the MDMA channel */
    WRITE_REG(MDMAy->CHSUSP, (MDMA_CH_SUSPEND << ChNum));
}

/**
*\*\name    MDMA_ChannelIsSuspended.
*\*\fun     Check whether a MDMA channel suspended.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\return  true or false
**/
bool MDMA_ChannelIsSuspended(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum)
{
    bool ret;
    ret = READ_BIT((uint16_t)MDMAy->CHSUSP, ((uint16_t)0x1U << ChNum)) ? true : false;
    return ret;
}

/**
*\*\name    MDMA_ChannelResume.
*\*\fun     Resume a MDMA channel.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\return  none
**/
void MDMA_ChannelResume(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum)
{
    /* Resume the MDMA channel */
    WRITE_REG(MDMAy->CHSUSP, (MDMA_CH_RESUME << ChNum));
}

/**
*\*\name    MDMA_GlobalInterruptCmd.
*\*\fun     Enable or disable MDMA globally interrupt.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void MDMA_GlobalInterruptCmd(MDMA_Module *const MDMAy, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the MDMA global interrupt */
        SET_BIT(MDMAy->CFG, MDMA_CFG_GLBINTEN);
    }
    else
    {
        /* Disable the MDMA global interrupt */
        CLEAR_BIT(MDMAy->CFG, MDMA_CFG_GLBINTEN);
    }
}

/**
*\*\name    MDMA_CommonInterruptStatusCmd.
*\*\fun     Enable or disable MDMA common register interrupt status.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   Interrupt (The input parameter must be one or more of the following values (logical OR)):
*\*\          - MDMA_COMMON_INT_SIURDEI
*\*\          - MDMA_COMMON_INT_SICRWOHEI
*\*\          - MDMA_COMMON_INT_SICRR2WOEI
*\*\          - MDMA_COMMON_INT_SICRW2ROEI
*\*\          - MDMA_COMMON_INT_SICRDEI
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void MDMA_CommonInterruptStatusCmd(MDMA_Module *const MDMAy, uint32_t Interrupt, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the MDMA corresponding common register interrupt status */
        SET_BIT(MDMAy->CRINTSTSEN, Interrupt);
    }
    else
    {
        /* Disable the MDMA corresponding common register interrupt status */
        CLEAR_BIT(MDMAy->CRINTSTSEN, Interrupt);
    }
}

/**
*\*\name    MDMA_CommonInterruptSignalCmd.
*\*\fun     Enable or disable MDMA common register interrupt signal.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   Interrupt (The input parameter must be one or more of the following values (logical OR)):
*\*\          - MDMA_COMMON_INT_SIURDEI
*\*\          - MDMA_COMMON_INT_SICRWOHEI
*\*\          - MDMA_COMMON_INT_SICRR2WOEI
*\*\          - MDMA_COMMON_INT_SICRW2ROEI
*\*\          - MDMA_COMMON_INT_SICRDEI
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void MDMA_CommonInterruptSignalCmd(MDMA_Module *const MDMAy, uint32_t Interrupt, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the MDMA corresponding common register interrupt signal */
        SET_BIT(MDMAy->CRINTSGLEN, Interrupt);
    }
    else
    {
        /* Disable the MDMA corresponding common register interrupt signal */
        CLEAR_BIT(MDMAy->CRINTSGLEN, Interrupt);
    }
}

/**
*\*\name    MDMA_ClearCommonInterruptStatus.
*\*\fun     Clear MDMA common register interrupt status.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   Interrupt (The input parameter must be one or more of the following values (logical OR)):
*\*\          - MDMA_COMMON_INT_SIURDEI
*\*\          - MDMA_COMMON_INT_SICRWOHEI
*\*\          - MDMA_COMMON_INT_SICRR2WOEI
*\*\          - MDMA_COMMON_INT_SICRW2ROEI
*\*\          - MDMA_COMMON_INT_SICRDEI
*\*\return  none
**/
void MDMA_ClearCommonInterruptStatus(MDMA_Module *const MDMAy, uint32_t Interrupt)
{
    /* Clear the MDMA corresponding common register interrupt status */
    WRITE_REG(MDMAy->CRINTCLR, Interrupt);
}

/**
*\*\name    MDMA_GetCombinedStatus.
*\*\fun     Get the MDMA combined interrupt status.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\return  MDMA_INTSTS register value
**/
uint64_t MDMA_GetCombinedStatus(MDMA_Module *const MDMAy)
{
    return (uint64_t)(READ_REG(MDMAy->INTSTS) & 0x10000FFFFUL);
}

/**
*\*\name    MDMA_GetCommonInterruptStatus.
*\*\fun     Get MDMA common register interrupt status.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   Interrupt (The input parameters must be the following values):
*\*\          - MDMA_COMMON_INT_SIURDEI
*\*\          - MDMA_COMMON_INT_SICRWOHEI
*\*\          - MDMA_COMMON_INT_SICRR2WOEI
*\*\          - MDMA_COMMON_INT_SICRW2ROEI
*\*\          - MDMA_COMMON_INT_SICRDEI
*\*\return  SET or RESET
**/
INTStatus MDMA_GetCommonInterruptStatus(MDMA_Module *const MDMAy, uint32_t Interrupt)
{
    INTStatus RetStatus = RESET;

    /* Read the status of the corresponding interrupt */
    if (READ_BIT(MDMAy->CRINTSTS, Interrupt) != (uint32_t)RESET)
    {
        /* This status of the interrupt is SET */
        RetStatus = SET;
    }
    else
    {
        /* This status of the interrupt is RESET */
        RetStatus = RESET;
    }

    /* Return status */
    return RetStatus;
}

/**
*\*\name    MDMA_ChannelInterruptStatusCmd.
*\*\fun     Enable or disable a MDMA channel interrupt status.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\param   Interrupt (The input parameter must be one or more of the following values (logical OR)):
*\*\          - MDMA_CH_INT_CH_ABORTED
*\*\          - MDMA_CH_INT_CH_DISABLED
*\*\          - MDMA_CH_INT_CH_SUSPENDED
*\*\          - MDMA_CH_INT_CH_SRC_SUSPENDED
*\*\          - MDMA_CH_INT_CH_LOCK_CLEARED
*\*\          - MDMA_CH_INT_SLV_IF_W_ON_HOLD_ERR
*\*\          - MDMA_CH_INT_SLV_IF_W_ON_CH_EN_ERR
*\*\          - MDMA_CH_INT_SLV_IF_R2WO_ERR
*\*\          - MDMA_CH_INT_SLV_IF_W2RO_ERR
*\*\          - MDMA_CH_INT_SLV_IF_DEC_ERR
*\*\          - MDMA_CH_INT_SLV_IF_MULTI_BLK_TYPE_ERR
*\*\          - MDMA_CH_INT_SDW_REG_LLI_INVALID_ERR
*\*\          - MDMA_CH_INT_LLI_W_SLV_ERR
*\*\          - MDMA_CH_INT_LLI_R_SLV_ERR
*\*\          - MDMA_CH_INT_LLI_W_DEC_ERR
*\*\          - MDMA_CH_INT_LLI_R_DEC_ERR
*\*\          - MDMA_CH_INT_DST_SLV_ERR
*\*\          - MDMA_CH_INT_SRC_SLV_ERR
*\*\          - MDMA_CH_INT_DST_DEC_ERR
*\*\          - MDMA_CH_INT_SRC_DEC_ERR
*\*\          - MDMA_CH_INT_DST_TRAN_COMPLE
*\*\          - MDMA_CH_INT_SRC_TRAN_COMPLE
*\*\          - MDMA_CH_INT_DMA_TRF_DONE
*\*\          - MDMA_CH_INT_BLK_TRF_DONE
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void MDMA_ChannelInterruptStatusCmd(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, uint32_t Interrupt, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the corresponding interrupt status for the specified MDMA channel */
        SET_BIT(MDMAy->CH[ChNum].INTSTSEN, Interrupt);
    }
    else
    {
        /* Disable the corresponding interrupt status for the specified MDMA channel */
        CLEAR_BIT(MDMAy->CH[ChNum].INTSTSEN, Interrupt);
    }
}

/**
*\*\name    MDMA_ChannelInterruptSignalCmd.
*\*\fun     Enable or disable a MDMA channel interrupt signal.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\param   Interrupt (The input parameter must be one or more of the following values (logical OR)):
*\*\          - MDMA_CH_INT_CH_ABORTED
*\*\          - MDMA_CH_INT_CH_DISABLED
*\*\          - MDMA_CH_INT_CH_SUSPENDED
*\*\          - MDMA_CH_INT_CH_SRC_SUSPENDED
*\*\          - MDMA_CH_INT_CH_LOCK_CLEARED
*\*\          - MDMA_CH_INT_SLV_IF_W_ON_HOLD_ERR
*\*\          - MDMA_CH_INT_SLV_IF_W_ON_CH_EN_ERR
*\*\          - MDMA_CH_INT_SLV_IF_R2WO_ERR
*\*\          - MDMA_CH_INT_SLV_IF_W2RO_ERR
*\*\          - MDMA_CH_INT_SLV_IF_DEC_ERR
*\*\          - MDMA_CH_INT_SLV_IF_MULTI_BLK_TYPE_ERR
*\*\          - MDMA_CH_INT_SDW_REG_LLI_INVALID_ERR
*\*\          - MDMA_CH_INT_LLI_W_SLV_ERR
*\*\          - MDMA_CH_INT_LLI_R_SLV_ERR
*\*\          - MDMA_CH_INT_LLI_W_DEC_ERR
*\*\          - MDMA_CH_INT_LLI_R_DEC_ERR
*\*\          - MDMA_CH_INT_DST_SLV_ERR
*\*\          - MDMA_CH_INT_SRC_SLV_ERR
*\*\          - MDMA_CH_INT_DST_DEC_ERR
*\*\          - MDMA_CH_INT_SRC_DEC_ERR
*\*\          - MDMA_CH_INT_DST_TRAN_COMPLE
*\*\          - MDMA_CH_INT_SRC_TRAN_COMPLE
*\*\          - MDMA_CH_INT_DMA_TRF_DONE
*\*\          - MDMA_CH_INT_BLK_TRF_DONE
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void MDMA_ChannelInterruptSignalCmd(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, uint32_t Interrupt, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the corresponding interrupt signal for the specified MDMA channel */
        SET_BIT(MDMAy->CH[ChNum].INTSGLEN, Interrupt);
    }
    else
    {
        /* Disable the corresponding interrupt signal for the specified MDMA channel */
        CLEAR_BIT(MDMAy->CH[ChNum].INTSGLEN, Interrupt);
    }
}

/**
*\*\name    MDMA_ClearChannelInterruptStatus.
*\*\fun     Clear MDMA Channel interrupt status.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\param   Interrupt (The input parameter must be one or more of the following values (logical OR)):
*\*\          - MDMA_CH_INT_CH_ABORTED
*\*\          - MDMA_CH_INT_CH_DISABLED
*\*\          - MDMA_CH_INT_CH_SUSPENDED
*\*\          - MDMA_CH_INT_CH_SRC_SUSPENDED
*\*\          - MDMA_CH_INT_CH_LOCK_CLEARED
*\*\          - MDMA_CH_INT_SLV_IF_W_ON_HOLD_ERR
*\*\          - MDMA_CH_INT_SLV_IF_W_ON_CH_EN_ERR
*\*\          - MDMA_CH_INT_SLV_IF_R2WO_ERR
*\*\          - MDMA_CH_INT_SLV_IF_W2RO_ERR
*\*\          - MDMA_CH_INT_SLV_IF_DEC_ERR
*\*\          - MDMA_CH_INT_SLV_IF_MULTI_BLK_TYPE_ERR
*\*\          - MDMA_CH_INT_SDW_REG_LLI_INVALID_ERR
*\*\          - MDMA_CH_INT_LLI_W_SLV_ERR
*\*\          - MDMA_CH_INT_LLI_R_SLV_ERR
*\*\          - MDMA_CH_INT_LLI_W_DEC_ERR
*\*\          - MDMA_CH_INT_LLI_R_DEC_ERR
*\*\          - MDMA_CH_INT_DST_SLV_ERR
*\*\          - MDMA_CH_INT_SRC_SLV_ERR
*\*\          - MDMA_CH_INT_DST_DEC_ERR
*\*\          - MDMA_CH_INT_SRC_DEC_ERR
*\*\          - MDMA_CH_INT_DST_TRAN_COMPLE
*\*\          - MDMA_CH_INT_SRC_TRAN_COMPLE
*\*\          - MDMA_CH_INT_DMA_TRF_DONE
*\*\          - MDMA_CH_INT_BLK_TRF_DONE
*\*\return  none
**/
void MDMA_ClearChannelInterruptStatus(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, uint32_t Interrupt)
{
    /* Clear the corresponding interrupt for the specified MDMA channel */
    WRITE_REG(MDMAy->CH[ChNum].INTCLR, Interrupt);
}

/**
*\*\name    MDMA_GetChannelInterruptStatus.
*\*\fun     Get MDMA Channel interrupt status.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\param   Interrupt (The input parameters must be the following values):
*\*\          - MDMA_CH_INT_CH_ABORTED
*\*\          - MDMA_CH_INT_CH_DISABLED
*\*\          - MDMA_CH_INT_CH_SUSPENDED
*\*\          - MDMA_CH_INT_CH_SRC_SUSPENDED
*\*\          - MDMA_CH_INT_CH_LOCK_CLEARED
*\*\          - MDMA_CH_INT_SLV_IF_W_ON_HOLD_ERR
*\*\          - MDMA_CH_INT_SLV_IF_W_ON_CH_EN_ERR
*\*\          - MDMA_CH_INT_SLV_IF_R2WO_ERR
*\*\          - MDMA_CH_INT_SLV_IF_W2RO_ERR
*\*\          - MDMA_CH_INT_SLV_IF_DEC_ERR
*\*\          - MDMA_CH_INT_SLV_IF_MULTI_BLK_TYPE_ERR
*\*\          - MDMA_CH_INT_SDW_REG_LLI_INVALID_ERR
*\*\          - MDMA_CH_INT_LLI_W_SLV_ERR
*\*\          - MDMA_CH_INT_LLI_R_SLV_ERR
*\*\          - MDMA_CH_INT_LLI_W_DEC_ERR
*\*\          - MDMA_CH_INT_LLI_R_DEC_ERR
*\*\          - MDMA_CH_INT_DST_SLV_ERR
*\*\          - MDMA_CH_INT_SRC_SLV_ERR
*\*\          - MDMA_CH_INT_DST_DEC_ERR
*\*\          - MDMA_CH_INT_SRC_DEC_ERR
*\*\          - MDMA_CH_INT_DST_TRAN_COMPLE
*\*\          - MDMA_CH_INT_SRC_TRAN_COMPLE
*\*\          - MDMA_CH_INT_DMA_TRF_DONE
*\*\          - MDMA_CH_INT_BLK_TRF_DONE
*\*\return  SET or RESET
**/
INTStatus MDMA_GetChannelInterruptStatus(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, uint32_t Interrupt)
{
    INTStatus RetStatus = RESET;

    /* Read the status of the corresponding interrupt */
    if (READ_BIT(MDMAy->CH[ChNum].INTSTS, Interrupt) != (uint32_t)RESET)
    {
        /* This status of the interrupt is SET */
        RetStatus = SET;
    }
    else
    {
        /* This status of the interrupt is RESET */
        RetStatus = RESET;
    }

    /* Return status */
    return RetStatus;
}

/**
*\*\name    MDMA_SetChannelSourceAddress.
*\*\fun     Sets the source address of the specified channel.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\param   Addr:
*\*\          - Source address
*\*\return  none
**/
void MDMA_SetChannelSourceAddress(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, uint64_t Addr)
{
    WRITE_REG(MDMAy->CH[ChNum].SA, Addr);
}

/**
*\*\name    MDMA_SetChannelDestinationAddress.
*\*\fun     Sets the destination address of the specified channel.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\param   Addr:
*\*\          - Destination address
*\*\return  none
**/
void MDMA_SetChannelDestinationAddress(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, uint64_t Addr)
{
    WRITE_REG(MDMAy->CH[ChNum].DA, Addr);
}

/**
*\*\name    MDMA_SetChannelBlockSize.
*\*\fun     Sets block size lenght for specific channel.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\param   Size:
*\*\          - Block tranfer size for tranfering
*\*\return  none
**/
void MDMA_SetChannelBlockSize(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, uint32_t Size)
{
    WRITE_REG(MDMAy->CH[ChNum].BTS, Size);
}

/**
*\*\name    MDMA_GetTransferredNumber.
*\*\fun     Gets the number of data that has been transmitted by the current channel.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\return  Number of data sent
**/
uint32_t MDMA_GetTransferredNumber(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum)
{
    return READ_REG(MDMAy->CH[ChNum].BTS);
}

/**
*\*\name    MDMA_SetChannelLinkedListPointer.
*\*\fun     Sets linked list pointer function.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\param   StrAddr:
*\*\          - MDMA linked list item structure address
*\*\return  none
**/
void MDMA_SetChannelLinkedListPointer(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, uint64_t StrAddr)
{
    WRITE_REG(MDMAy->CH[ChNum].LLP, StrAddr);
}

/**
*\*\name    MDMA_SetChannelSrcMultiBlockType.
*\*\fun     Sets channel source multi block transfer type.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\param   Type (The input parameters must be the following values):
*\*\          - MDMA_CH_MULTI_BLOCK_CONTIGUOUS
*\*\          - MDMA_CH_MULTI_BLOCK_RELOAD
*\*\          - MDMA_CH_MULTI_BLOCK_LINKED_LIST
*\*\return  none
**/
void MDMA_SetChannelSrcMultiBlockType(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, MDMA_ChMultBlkTfrType Type)
{
    MODIFY_REG(MDMAy->CH[ChNum].CFG, MDMA_CHNCFG_SMBTT, ((uint64_t)Type << 0U));
}

/**
*\*\name    MDMA_SetChannelDstMultiBlockType.
*\*\fun     Sets channel destination multi block transfer type.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\param   Type (The input parameters must be the following values):
*\*\          - MDMA_CH_MULTI_BLOCK_CONTIGUOUS
*\*\          - MDMA_CH_MULTI_BLOCK_RELOAD
*\*\          - MDMA_CH_MULTI_BLOCK_LINKED_LIST
*\*\return  none
**/
void MDMA_SetChannelDstMultiBlockType(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, MDMA_ChMultBlkTfrType Type)
{
    MODIFY_REG(MDMAy->CH[ChNum].CFG, MDMA_CHNCFG_DMBTT, ((uint64_t)Type << 2U));
}

/**
*\*\name    MDMA_TriggerSourceRequest.
*\*\fun     Trigger a software source handshake request.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\param   Type (The input parameters must be the following values):
*\*\          - MDMA_CH_SOFTWARE_HANDSHAKING_TFR_SINGLE
*\*\          - MDMA_CH_SOFTWARE_HANDSHAKING_TFR_BURST
*\*\param   isLast:
*\*\          - true or false
*\*\return  none
**/
void MDMA_TriggerSourceRequest(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, MDMA_ChSwHsTfrType Type, bool isLast)
{
    if (Type == MDMA_CH_SOFTWARE_HANDSHAKING_TFR_SINGLE)
    {
        /* Enable Channel n Source peripheral request for a single dma transfer */
        WRITE_REG(MDMAy->CH[ChNum].SHSRC, (MDMA_CHNSHSRC_SHSRWE | MDMA_CHNSHSRC_SHSR));
    }
    else
    {
        /* Enable Channel n Source peripheral request for a burst dma transfer */
        WRITE_REG(MDMAy->CH[ChNum].SHSRC, (MDMA_CHNSHSRC_SHRWE | MDMA_CHNSHSRC_SHR));
    }

    if (isLast == true)
    {
        /* Indication that the curent transfer is the last transfer */
        WRITE_REG(MDMAy->CH[ChNum].SHSRC, (MDMA_CHNSHSRC_SHLRWE | MDMA_CHNSHSRC_SHLR));
    }
}

/**
*\*\name    MDMA_TriggerDestinationRequest.
*\*\fun     Trigger a software Destination handshake request.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\param   Type (The input parameters must be the following values):
*\*\          - MDMA_CH_SOFTWARE_HANDSHAKING_TFR_SINGLE
*\*\          - MDMA_CH_SOFTWARE_HANDSHAKING_TFR_BURST
*\*\param   isLast:
*\*\          - true or false
*\*\return  none
**/
void MDMA_TriggerDestinationRequest(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum, MDMA_ChSwHsTfrType Type, bool isLast)
{
    if (Type == MDMA_CH_SOFTWARE_HANDSHAKING_TFR_SINGLE)
    {
        /* Enable Channel n Destination peripheral request for a single dma transfer */
        WRITE_REG(MDMAy->CH[ChNum].SHDST, (MDMA_CHNSHDST_SHSRWE | MDMA_CHNSHDST_SHSR));
    }
    else
    {
        /* Enable Channel n Destination peripheral request for a burst dma transfer */
        WRITE_REG(MDMAy->CH[ChNum].SHDST, (MDMA_CHNSHDST_SHRWE | MDMA_CHNSHDST_SHR));
    }

    if (isLast == true)
    {
        /* Indication that the curent transfer is the last transfer */
        WRITE_REG(MDMAy->CH[ChNum].SHDST, (MDMA_CHNSHDST_SHLRWE | MDMA_CHNSHDST_SHLR));
    }
}

/**
*\*\name    MDMA_BlockTransferResumeRequest.
*\*\fun     Requests for resumption of block transfer during Linked-List-based
*\*\        multi-block transfer.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\return  none
**/
void MDMA_BlockTransferResumeRequest(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum)
{
    /* Request for resuming the block transfer */
    WRITE_REG(MDMAy->CH[ChNum].BTRR, MDMA_CHNBTRR_RESREQ);
}

/**
*\*\name    MDMA_SetChannelLinkedListItemValid.
*\*\fun     Set the MDMA channel LLI valid.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\return  none
**/
void MDMA_SetChannelLinkedListItemValid(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum)
{
    SET_BIT(MDMAy->CH[ChNum].CTRL, MDMA_CHNCTRL_SRLLI);
}

/**
*\*\name    MDMA_ChannelLinkedListItemIsValid.
*\*\fun     Check whether a MDMA channel LLI valid.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\return  true or false
**/
bool MDMA_ChannelLinkedListItemIsValid(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum)
{
    bool ret;
    ret = READ_BIT(MDMAy->CH[ChNum].CTRL, MDMA_CHNCTRL_SRLLI) ? true : false;
    return ret;
}

/**
*\*\name    MDMA_SetChannelLastLinkedListItem.
*\*\fun     Set the current LLI to the last LLI.
*\*\param   MDMAy (The input parameters must be the following values):
*\*\          - MDMA
*\*\param   ChNum (The input parameters must be the following values):
*\*\          - MDMA_CHANNEL_0
*\*\          - MDMA_CHANNEL_1
*\*\          - MDMA_CHANNEL_2
*\*\          - MDMA_CHANNEL_3
*\*\          - MDMA_CHANNEL_4
*\*\          - MDMA_CHANNEL_5
*\*\          - MDMA_CHANNEL_6
*\*\          - MDMA_CHANNEL_7
*\*\          - MDMA_CHANNEL_8
*\*\          - MDMA_CHANNEL_9
*\*\          - MDMA_CHANNEL_10
*\*\          - MDMA_CHANNEL_11
*\*\          - MDMA_CHANNEL_12
*\*\          - MDMA_CHANNEL_13
*\*\          - MDMA_CHANNEL_14
*\*\          - MDMA_CHANNEL_15
*\*\return  none
**/
void MDMA_SetChannelLastLinkedListItem(MDMA_Module *const MDMAy, MDMA_ChNumType ChNum)
{
    SET_BIT(MDMAy->CH[ChNum].CTRL, MDMA_CHNCTRL_LSRLLI);
}

