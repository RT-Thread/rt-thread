/**********************************************************************
* $Id$      lpc_gpdma.c         2011-06-02
*//**
* @file     lpc_gpdma.c
* @brief    Contains all functions support for GPDMA firmware library
*           on LPC
* @version  1.0
* @date     02. June. 2011
* @author   NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup GPDMA
 * @{
 */
#ifdef __BUILD_WITH_EXAMPLE__
#include "lpc_libcfg.h"
#else
#include "lpc_libcfg_default.h"
#endif /* __BUILD_WITH_EXAMPLE__ */
#ifdef _GPDMA

/* Includes ------------------------------------------------------------------- */
#include "lpc_gpdma.h"
#include "lpc_clkpwr.h"

/* Private Variables ---------------------------------------------------------- */
/** @defgroup GPDMA_Private_Variables GPDMA Private Variables
 * @{
 */

/**
 * @brief Lookup Table of Connection Type matched with
 * Peripheral Data (FIFO) register base address
 */
volatile const void *GPDMA_LUTPerAddr[] = {
        0,                              // Revered
        (&LPC_MCI->FIFO),               // SD Card
        (&LPC_SSP0->DR),                // SSP0 Tx
        (&LPC_SSP0->DR),                // SSP0 Rx
        (&LPC_SSP1->DR),                // SSP1 Tx
        (&LPC_SSP1->DR),                // SSP1 Rx
        (&LPC_SSP2->DR),                // SSP2 Tx
        (&LPC_SSP2->DR),                // SSP2 Rx
        (&LPC_ADC->GDR),                // ADC
        (&LPC_DAC->CR),                 // DAC
        (&LPC_UART0->/*RBTHDLR.*/THR),  // UART0 Tx
        (&LPC_UART0->/*RBTHDLR.*/RBR),  // UART0 Rx
        (&LPC_UART1->/*RBTHDLR.*/THR),  // UART1 Tx
        (&LPC_UART1->/*RBTHDLR.*/RBR),  // UART1 Rx
        (&LPC_UART2->/*RBTHDLR.*/THR),  // UART2 Tx
        (&LPC_UART2->/*RBTHDLR.*/RBR),  // UART2 Rx
        (&LPC_TIM0->MR0),               // MAT0.0
        (&LPC_TIM0->MR1),               // MAT0.1
        (&LPC_TIM1->MR0),               // MAT1.0
        (&LPC_TIM1->MR1),               // MAT1.1
        (&LPC_TIM2->MR0),               // MAT2.0
        (&LPC_TIM2->MR1),               // MAT2.1
        (&LPC_I2S->TXFIFO),             // I2S Tx
        (&LPC_I2S->RXFIFO),             // I2S Rx
        0,                              // Reverse
        0,                              // Reverse
        (&LPC_UART3->/*RBTHDLR.*/THR),  // UART3 Tx
        (&LPC_UART3->/*RBTHDLR.*/RBR),  // UART3 Rx
        (&LPC_UART4->/*RBTHDLR.*/THR),  // UART4 Tx
        (&LPC_UART4->/*RBTHDLR.*/RBR),  // UART4 Rx
        (&LPC_TIM3->MR0),               // MAT3.0
        (&LPC_TIM3->MR1),               // MAT3.1
};

/**
 * @brief Lookup Table of GPDMA Channel Number matched with
 * GPDMA channel pointer
 */
const LPC_GPDMACH_TypeDef *pGPDMACh[8] = {
        LPC_GPDMACH0,   // GPDMA Channel 0
        LPC_GPDMACH1,   // GPDMA Channel 1
        LPC_GPDMACH2,   // GPDMA Channel 2
        LPC_GPDMACH3,   // GPDMA Channel 3
        LPC_GPDMACH4,   // GPDMA Channel 4
        LPC_GPDMACH5,   // GPDMA Channel 5
        LPC_GPDMACH6,   // GPDMA Channel 6
        LPC_GPDMACH7,   // GPDMA Channel 7
};
/**
 * @brief Optimized Peripheral Source and Destination burst size
 */
const uint8_t GPDMA_LUTPerBurst[] = {
        0,                          // Reserved
        GPDMA_BSIZE_8,              // SD Card
        GPDMA_BSIZE_4,              // SSP0 Tx
        GPDMA_BSIZE_4,              // SSP0 Rx
        GPDMA_BSIZE_4,              // SSP1 Tx
        GPDMA_BSIZE_4,              // SSP1 Rx
        GPDMA_BSIZE_4,              // SSP2 Tx
        GPDMA_BSIZE_4,              // SSP2 Rx
        GPDMA_BSIZE_1,              // ADC
        GPDMA_BSIZE_1,              // DAC
        GPDMA_BSIZE_1,              // UART0 Tx
        GPDMA_BSIZE_1,              // UART0 Rx
        GPDMA_BSIZE_1,              // UART1 Tx
        GPDMA_BSIZE_1,              // UART1 Rx
        GPDMA_BSIZE_1,              // UART2 Tx
        GPDMA_BSIZE_1,              // UART2 Rx
        GPDMA_BSIZE_1,              // MAT0.0
        GPDMA_BSIZE_1,              // MAT0.1
        GPDMA_BSIZE_1,              // MAT1.0
        GPDMA_BSIZE_1,              // MAT1.1
        GPDMA_BSIZE_1,              // MAT2.0
        GPDMA_BSIZE_1,              // MAT2.1
        GPDMA_BSIZE_32,             // I2S channel 0
        GPDMA_BSIZE_32,             // I2S channel 1
        0,                          // Reserved
        0,                          // Reserved
        GPDMA_BSIZE_1,              // UART3 Tx
        GPDMA_BSIZE_1,              // UART3 Rx
        GPDMA_BSIZE_1,              // UART4 Tx
        GPDMA_BSIZE_1,              // UART4 Rx
        GPDMA_BSIZE_1,              // MAT3.0
        GPDMA_BSIZE_1,              // MAT3.1
};
/**
 * @brief Optimized Peripheral Source and Destination transfer width
 */
const uint8_t GPDMA_LUTPerWid[] = {
        0,                              // Reserved
        GPDMA_WIDTH_WORD,               // SD Card
        GPDMA_WIDTH_BYTE,               // SSP0 Tx
        GPDMA_WIDTH_BYTE,               // SSP0 Rx
        GPDMA_WIDTH_BYTE,               // SSP1 Tx
        GPDMA_WIDTH_BYTE,               // SSP1 Rx
        GPDMA_WIDTH_BYTE,               // SSP2 Tx
        GPDMA_WIDTH_BYTE,               // SSP2 Rx
        GPDMA_WIDTH_WORD,               // ADC
        GPDMA_WIDTH_BYTE,               // DAC
        GPDMA_WIDTH_BYTE,               // UART0 Tx
        GPDMA_WIDTH_BYTE,               // UART0 Rx
        GPDMA_WIDTH_BYTE,               // UART1 Tx
        GPDMA_WIDTH_BYTE,               // UART1 Rx
        GPDMA_WIDTH_BYTE,               // UART2 Tx
        GPDMA_WIDTH_BYTE,               // UART2 Rx
        GPDMA_WIDTH_WORD,               // MAT0.0
        GPDMA_WIDTH_WORD,               // MAT0.1
        GPDMA_WIDTH_WORD,               // MAT1.0
        GPDMA_WIDTH_WORD,               // MAT1.1
        GPDMA_WIDTH_WORD,               // MAT2.0
        GPDMA_WIDTH_WORD,               // MAT2.1
        GPDMA_WIDTH_WORD,               // I2S channel 0
        GPDMA_WIDTH_WORD,               // I2S channel 1
        0,                              // Reserved
        0,                              // Reserved
        GPDMA_WIDTH_BYTE,               // UART3 Tx
        GPDMA_WIDTH_BYTE,               // UART3 Rx
        GPDMA_WIDTH_BYTE,               // UART4 Tx
        GPDMA_WIDTH_BYTE,               // UART4 Rx
        GPDMA_WIDTH_WORD,               // MAT3.0
        GPDMA_WIDTH_WORD,               // MAT3.1
};

/**
 * @}
 */

/* Public Functions ----------------------------------------------------------- */
/** @addtogroup GPDMA_Public_Functions
 * @{
 */

/********************************************************************//**
 * @brief       Initialize GPDMA controller
 * @param       None
 * @return      None
 *********************************************************************/
void GPDMA_Init(void)
{
    /* Enable GPDMA clock */
    CLKPWR_ConfigPPWR (CLKPWR_PCONP_PCGPDMA, ENABLE);

    // Reset all channel configuration register
    LPC_GPDMACH0->CConfig = 0;
    LPC_GPDMACH1->CConfig = 0;
    LPC_GPDMACH2->CConfig = 0;
    LPC_GPDMACH3->CConfig = 0;
    LPC_GPDMACH4->CConfig = 0;
    LPC_GPDMACH5->CConfig = 0;
    LPC_GPDMACH6->CConfig = 0;
    LPC_GPDMACH7->CConfig = 0;

    /* Clear all DMA interrupt and error flag */
    LPC_GPDMA->IntTCClear = 0xFF;
    LPC_GPDMA->IntErrClr = 0xFF;
}

/********************************************************************//**
 * @brief       Setup GPDMA channel peripheral according to the specified
 *               parameters in the GPDMAChannelConfig.
 * @param[in]   GPDMAChannelConfig Pointer to a GPDMA_CH_CFG_Type
 *                                  structure that contains the configuration
 *                                  information for the specified GPDMA channel peripheral.
 * @return      ERROR if selected channel is enabled before
 *              or SUCCESS if channel is configured successfully
 *********************************************************************/
Status GPDMA_Setup(GPDMA_Channel_CFG_Type *GPDMAChannelConfig)
{
    LPC_GPDMACH_TypeDef *pDMAch;
    uint32_t tmp1, tmp2;

    if (LPC_GPDMA->EnbldChns & (GPDMA_DMACEnbldChns_Ch(GPDMAChannelConfig->ChannelNum))) {
        // This channel is enabled, return ERROR, need to release this channel first
        return ERROR;
    }

    // Get Channel pointer
    pDMAch = (LPC_GPDMACH_TypeDef *) pGPDMACh[GPDMAChannelConfig->ChannelNum];

    // Reset the Interrupt status
    LPC_GPDMA->IntTCClear = GPDMA_DMACIntTCClear_Ch(GPDMAChannelConfig->ChannelNum);
    LPC_GPDMA->IntErrClr = GPDMA_DMACIntErrClr_Ch(GPDMAChannelConfig->ChannelNum);

    // Clear DMA configure
    pDMAch->CControl = 0x00;
    pDMAch->CConfig = 0x00;

    /* Assign Linker List Item value */
    pDMAch->CLLI = GPDMAChannelConfig->DMALLI;

    /* Set value to Channel Control Registers */
    switch (GPDMAChannelConfig->TransferType)
    {
    // Memory to memory
    case GPDMA_TRANSFERTYPE_M2M:
        // Assign physical source and destination address
        pDMAch->CSrcAddr = GPDMAChannelConfig->SrcMemAddr;
        pDMAch->CDestAddr = GPDMAChannelConfig->DstMemAddr;
        pDMAch->CControl
                = GPDMA_DMACCxControl_TransferSize(GPDMAChannelConfig->TransferSize) \
                        | GPDMA_DMACCxControl_SBSize(GPDMA_BSIZE_32) \
                        | GPDMA_DMACCxControl_DBSize(GPDMA_BSIZE_32) \
                        | GPDMA_DMACCxControl_SWidth(GPDMAChannelConfig->TransferWidth) \
                        | GPDMA_DMACCxControl_DWidth(GPDMAChannelConfig->TransferWidth) \
                        | GPDMA_DMACCxControl_SI \
                        | GPDMA_DMACCxControl_DI \
                        | GPDMA_DMACCxControl_I;
        break;
    // Memory to peripheral
    case GPDMA_TRANSFERTYPE_M2P:
    case GPDMA_TRANSFERTYPE_M2P_DEST_CTRL:
        // Assign physical source
        pDMAch->CSrcAddr = GPDMAChannelConfig->SrcMemAddr;
        // Assign peripheral destination address
        pDMAch->CDestAddr = (uint32_t)GPDMA_LUTPerAddr[GPDMAChannelConfig->DstConn];
        pDMAch->CControl
                = GPDMA_DMACCxControl_TransferSize((uint32_t)GPDMAChannelConfig->TransferSize) \
                        | GPDMA_DMACCxControl_SBSize((uint32_t)GPDMA_LUTPerBurst[GPDMAChannelConfig->DstConn]) \
                        | GPDMA_DMACCxControl_DBSize((uint32_t)GPDMA_LUTPerBurst[GPDMAChannelConfig->DstConn]) \
                        | GPDMA_DMACCxControl_SWidth((uint32_t)GPDMA_LUTPerWid[GPDMAChannelConfig->DstConn]) \
                        | GPDMA_DMACCxControl_DWidth((uint32_t)GPDMA_LUTPerWid[GPDMAChannelConfig->DstConn]) \
                        | GPDMA_DMACCxControl_SI \
                        | GPDMA_DMACCxControl_I;
        break;
    // Peripheral to memory
    case GPDMA_TRANSFERTYPE_P2M:
    case GPDMA_TRANSFERTYPE_P2M_SRC_CTRL:
        // Assign peripheral source address
        pDMAch->CSrcAddr = (uint32_t)GPDMA_LUTPerAddr[GPDMAChannelConfig->SrcConn];
        // Assign memory destination address
        pDMAch->CDestAddr = GPDMAChannelConfig->DstMemAddr;
        pDMAch->CControl
                = GPDMA_DMACCxControl_TransferSize((uint32_t)GPDMAChannelConfig->TransferSize) \
                        | GPDMA_DMACCxControl_SBSize((uint32_t)GPDMA_LUTPerBurst[GPDMAChannelConfig->SrcConn]) \
                        | GPDMA_DMACCxControl_DBSize((uint32_t)GPDMA_LUTPerBurst[GPDMAChannelConfig->SrcConn]) \
                        | GPDMA_DMACCxControl_SWidth((uint32_t)GPDMA_LUTPerWid[GPDMAChannelConfig->SrcConn]) \
                        | GPDMA_DMACCxControl_DWidth((uint32_t)GPDMA_LUTPerWid[GPDMAChannelConfig->SrcConn]) \
                        | GPDMA_DMACCxControl_DI \
                        | GPDMA_DMACCxControl_I;
        break;
    // Peripheral to peripheral
    case GPDMA_TRANSFERTYPE_P2P:
        // Assign peripheral source address
        pDMAch->CSrcAddr = (uint32_t)GPDMA_LUTPerAddr[GPDMAChannelConfig->SrcConn];
        // Assign peripheral destination address
        pDMAch->CDestAddr = (uint32_t)GPDMA_LUTPerAddr[GPDMAChannelConfig->DstConn];
        pDMAch->CControl = GPDMA_DMACCxControl_TransferSize((uint32_t)GPDMAChannelConfig->TransferSize) \
                        | GPDMA_DMACCxControl_SBSize((uint32_t)GPDMA_LUTPerBurst[GPDMAChannelConfig->SrcConn]) \
                        | GPDMA_DMACCxControl_DBSize((uint32_t)GPDMA_LUTPerBurst[GPDMAChannelConfig->DstConn]) \
                        | GPDMA_DMACCxControl_SWidth((uint32_t)GPDMA_LUTPerWid[GPDMAChannelConfig->SrcConn]) \
                        | GPDMA_DMACCxControl_DWidth((uint32_t)GPDMA_LUTPerWid[GPDMAChannelConfig->DstConn]) \
                        | GPDMA_DMACCxControl_I;
        break;
    // Do not support any more transfer type, return ERROR
    default:
        return ERROR;
    }

    /* Re-Configure DMA Request Select for source peripheral */
    if((GPDMAChannelConfig->SrcConn != 8)&&(GPDMAChannelConfig->SrcConn != 9))
    {
        if (GPDMAChannelConfig->SrcConn > 15)
        {
            LPC_SC->DMAREQSEL |= (1<<(GPDMAChannelConfig->SrcConn - 16));
        } else {
            LPC_SC->DMAREQSEL &= ~(1<<(GPDMAChannelConfig->SrcConn));
        }
    }

    /* Re-Configure DMA Request Select for Destination peripheral */
    if((GPDMAChannelConfig->DstConn != 8)&&(GPDMAChannelConfig->DstConn != 9))
    {
        if (GPDMAChannelConfig->DstConn > 15)
        {
            LPC_SC->DMAREQSEL |= (1<<(GPDMAChannelConfig->DstConn - 16));
        } else {
            LPC_SC->DMAREQSEL &= ~(1<<(GPDMAChannelConfig->DstConn));
        }
    }

    /* Enable DMA channels, little endian */
    LPC_GPDMA->Config = GPDMA_DMACConfig_E;
    while (!(LPC_GPDMA->Config & GPDMA_DMACConfig_E));

    // Calculate absolute value for Connection number
    tmp1 = GPDMAChannelConfig->SrcConn;
    tmp1 = ((tmp1 > 15) ? (tmp1 - 16) : tmp1);
    tmp2 = GPDMAChannelConfig->DstConn;
    tmp2 = ((tmp2 > 15) ? (tmp2 - 16) : tmp2);

    // Configure DMA Channel, enable Error Counter and Terminate counter
    pDMAch->CConfig = GPDMA_DMACCxConfig_IE | GPDMA_DMACCxConfig_ITC /*| GPDMA_DMACCxConfig_E*/ \
        | GPDMA_DMACCxConfig_TransferType((uint32_t)GPDMAChannelConfig->TransferType) \
        | GPDMA_DMACCxConfig_SrcPeripheral(tmp1) \
        | GPDMA_DMACCxConfig_DestPeripheral(tmp2);

    return SUCCESS;
}


/*********************************************************************//**
 * @brief       Enable/Disable DMA channel
 * @param[in]   channelNum  GPDMA channel, should be in range from 0 to 7
 * @param[in]   NewState    New State of this command, should be:
 *                  - ENABLE.
 *                  - DISABLE.
 * @return      None
 **********************************************************************/
void GPDMA_ChannelCmd(uint8_t channelNum, FunctionalState NewState)
{
    LPC_GPDMACH_TypeDef *pDMAch;

    // Get Channel pointer
    pDMAch = (LPC_GPDMACH_TypeDef *) pGPDMACh[channelNum];

    if (NewState == ENABLE) {
        pDMAch->CConfig |= GPDMA_DMACCxConfig_E;
    } else {
        pDMAch->CConfig &= ~GPDMA_DMACCxConfig_E;
    }
}
/*********************************************************************//**
 * @brief       Check if corresponding channel does have an active interrupt
 *              request or not
 * @param[in]   type        type of status, should be:
 *                  - GPDMA_STAT_INT:       GPDMA Interrupt Status
 *                  - GPDMA_STAT_INTTC:     GPDMA Interrupt Terminal Count Request Status
 *                  - GPDMA_STAT_INTERR:    GPDMA Interrupt Error Status
 *                  - GPDMA_STAT_RAWINTTC:  GPDMA Raw Interrupt Terminal Count Status
 *                  - GPDMA_STAT_RAWINTERR: GPDMA Raw Error Interrupt Status
 *                  - GPDMA_STAT_ENABLED_CH:GPDMA Enabled Channel Status
 * @param[in]   channel     GPDMA channel, should be in range from 0 to 7
 * @return      IntStatus   status of DMA channel interrupt after masking
 *              Should be:
 *                  - SET: the corresponding channel has no active interrupt request
 *                  - RESET: the corresponding channel does have an active interrupt request
 **********************************************************************/
IntStatus GPDMA_IntGetStatus(GPDMA_Status_Type type, uint8_t channel)
{
    switch (type)
    {
    case GPDMA_STAT_INT: //check status of DMA channel interrupts
        if (LPC_GPDMA->IntStat & (GPDMA_DMACIntStat_Ch(channel)))
            return SET;
        return RESET;
    case GPDMA_STAT_INTTC: // check terminal count interrupt request status for DMA
        if (LPC_GPDMA->IntTCStat & GPDMA_DMACIntTCStat_Ch(channel))
            return SET;
        return RESET;
    case GPDMA_STAT_INTERR: //check interrupt status for DMA channels
        if (LPC_GPDMA->IntErrStat & GPDMA_DMACIntTCClear_Ch(channel))
            return SET;
        return RESET;
    case GPDMA_STAT_RAWINTTC: //check status of the terminal count interrupt for DMA channels
        if (LPC_GPDMA->RawIntErrStat & GPDMA_DMACRawIntTCStat_Ch(channel))
            return SET;
        return RESET;
    case GPDMA_STAT_RAWINTERR: //check status of the error interrupt for DMA channels
        if (LPC_GPDMA->RawIntTCStat & GPDMA_DMACRawIntErrStat_Ch(channel))
            return SET;
        return RESET;
    default: //check enable status for DMA channels
        if (LPC_GPDMA->EnbldChns & GPDMA_DMACEnbldChns_Ch(channel))
            return SET;
        return RESET;
    }
}

/*********************************************************************//**
 * @brief       Clear one or more interrupt requests on DMA channels
 * @param[in]   type        type of interrupt request, should be:
 *                  - GPDMA_STATCLR_INTTC:  GPDMA Interrupt Terminal Count Request Clear
 *                  - GPDMA_STATCLR_INTERR: GPDMA Interrupt Error Clear
 * @param[in]   channel     GPDMA channel, should be in range from 0 to 7
 * @return      None
 **********************************************************************/
void GPDMA_ClearIntPending(GPDMA_StateClear_Type type, uint8_t channel)
{
    if (type == GPDMA_STATCLR_INTTC) // clears the terminal count interrupt request on DMA channel
        LPC_GPDMA->IntTCClear = GPDMA_DMACIntTCClear_Ch(channel);
    else // clear the error interrupt request
        LPC_GPDMA->IntErrClr = GPDMA_DMACIntErrClr_Ch(channel);
}

/**
 * @}
 */

#endif /* _GPDMA */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */

