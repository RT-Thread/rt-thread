/**************************************************************************//**
 * @file     pdma.c
 * @version  V3.00
 * $Revision: 2 $
 * $Date: 15/05/04 3:27p $
 * @brief    PDMA driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NUC100Series.h"



/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup PDMA_Driver PDMA Driver
  @{
*/


/** @addtogroup PDMA_EXPORTED_FUNCTIONS PDMA Exported Functions
  @{
*/

/**
 * @brief       PDMA Open
 *
 * @param[in]   u32Mask     Channel enable bits.
 *
 * @return      None
 *
 * @details     This function enable the PDMA channels.
 */
void PDMA_Open(uint32_t u32Mask)
{
    PDMA_GCR->GCRCSR |= (u32Mask << 8);
}

/**
 * @brief       PDMA Close
 *
 * @param       None
 *
 * @return      None
 *
 * @details     This function disable all PDMA channels.
 */
void PDMA_Close(void)
{
    PDMA_GCR->GCRCSR = 0;
}

/**
 * @brief       Set PDMA Transfer Count
 *
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32Width        Data width. Valid values are
 *                - \ref PDMA_WIDTH_8
 *                - \ref PDMA_WIDTH_16
 *                - \ref PDMA_WIDTH_32
 * @param[in]   u32TransCount   Transfer count
 *
 * @return      None
 *
 * @details     This function set the selected channel data width and transfer count.
 */
void PDMA_SetTransferCnt(uint32_t u32Ch, uint32_t u32Width, uint32_t u32TransCount)
{
    PDMA_T *pdma;
    pdma = (PDMA_T *)((uint32_t) PDMA0_BASE + (0x100 * u32Ch));
    pdma->CSR = (pdma->CSR & ~PDMA_CSR_APB_TWS_Msk) | u32Width;
    switch(u32Width)
    {
    case PDMA_WIDTH_32:
        pdma->BCR = (u32TransCount << 2);
        break;

    case PDMA_WIDTH_8:
        pdma->BCR = u32TransCount;
        break;

    case PDMA_WIDTH_16:
        pdma->BCR = (u32TransCount << 1);
        break;

    default:
        ;
    }
}

/**
 * @brief       Set PDMA Transfer Address
 *
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32SrcAddr      Source address
 * @param[in]   u32SrcCtrl      Source control attribute. Valid values are
 *                - \ref PDMA_SAR_INC
 *                - \ref PDMA_SAR_FIX
 * @param[in]   u32DstAddr      destination address
 * @param[in]   u32DstCtrl      destination control attribute. Valid values are
 *                - \ref PDMA_DAR_INC
 *                - \ref PDMA_DAR_FIX
 *
 * @return      None
 *
 * @details     This function set the selected channel source/destination address and attribute.
 */
void PDMA_SetTransferAddr(uint32_t u32Ch, uint32_t u32SrcAddr, uint32_t u32SrcCtrl, uint32_t u32DstAddr, uint32_t u32DstCtrl)
{
    PDMA_T *pdma;
    pdma = (PDMA_T *)((uint32_t) PDMA0_BASE + (0x100 * u32Ch));

    pdma->SAR = u32SrcAddr;
    pdma->DAR = u32DstAddr;
    pdma->CSR = (pdma->CSR & ~(PDMA_CSR_SAD_SEL_Msk | PDMA_CSR_DAD_SEL_Msk)) | (u32SrcCtrl | u32DstCtrl);
}

/**
 * @brief       Set PDMA Transfer Mode
 *
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32Peripheral   The selected peripheral. Valid values are
 *                - \ref PDMA_SPI0_TX
 *                - \ref PDMA_SPI1_TX
 *                - \ref PDMA_SPI2_TX
 *                - \ref PDMA_SPI3_TX
 *                - \ref PDMA_UART0_TX
 *                - \ref PDMA_UART1_TX
 *                - \ref PDMA_I2S_TX
 *                - \ref PDMA_SPI0_RX
 *                - \ref PDMA_SPI1_RX
 *                - \ref PDMA_SPI2_RX
 *                - \ref PDMA_SPI3_RX
 *                - \ref PDMA_UART0_RX
 *                - \ref PDMA_UART1_RX
 *                - \ref PDMA_I2S_RX
 *                - \ref PDMA_ADC
 *                - \ref PDMA_MEM
 * @param[in]   u32ScatterEn    Scatter-gather mode enable
 * @param[in]   u32DescAddr     Scatter-gather descriptor address
 *
 * @return      None
 *
 * @details     This function set the selected channel transfer mode. Include peripheral setting.
 */
void PDMA_SetTransferMode(uint32_t u32Ch, uint32_t u32Peripheral, uint32_t u32ScatterEn, uint32_t u32DescAddr)
{
    uint32_t u32Index = 0;
    PDMA_T *pdma;
    pdma = (PDMA_T *)((uint32_t) PDMA0_BASE + (0x100 * u32Ch));

    if(u32Peripheral > PDMA_ADC) /* Memory-to-Memory */
        pdma->CSR = (pdma->CSR & ~(PDMA_CSR_MODE_SEL_Msk));
    else if(u32Peripheral > PDMA_I2S_TX) /* Peripheral-to-Memory */
        pdma->CSR = (pdma->CSR & ~(PDMA_CSR_MODE_SEL_Msk) | (0x1 << PDMA_CSR_MODE_SEL_Pos));
    else /* Memory-to-Peripheral */
        pdma->CSR = (pdma->CSR & ~(PDMA_CSR_MODE_SEL_Msk) | (0x2 << PDMA_CSR_MODE_SEL_Pos));

    switch(u32Peripheral)
    {
    case 0:
        PDMA_GCR->PDSSR0 = (PDMA_GCR->PDSSR0 & ~PDMA_PDSSR0_SPI0_TXSEL_Msk) | (u32Ch << PDMA_PDSSR0_SPI0_TXSEL_Pos);
        break;
    case 1:
        PDMA_GCR->PDSSR0 = (PDMA_GCR->PDSSR0 & ~PDMA_PDSSR0_SPI1_TXSEL_Msk) | (u32Ch << PDMA_PDSSR0_SPI1_TXSEL_Pos);
        break;
    case 2:
        PDMA_GCR->PDSSR0 = (PDMA_GCR->PDSSR0 & ~PDMA_PDSSR0_SPI2_TXSEL_Msk) | (u32Ch << PDMA_PDSSR0_SPI2_TXSEL_Pos);
        break;
    case 3:
        PDMA_GCR->PDSSR0 = (PDMA_GCR->PDSSR0 & ~PDMA_PDSSR0_SPI3_TXSEL_Msk) | (u32Ch << PDMA_PDSSR0_SPI3_TXSEL_Pos);
        break;
    case 4:
        PDMA_GCR->PDSSR1 = (PDMA_GCR->PDSSR1 & ~PDMA_PDSSR1_UART0_TXSEL_Msk) | (u32Ch << PDMA_PDSSR1_UART0_TXSEL_Pos);
        break;
    case 5:
        PDMA_GCR->PDSSR1 = (PDMA_GCR->PDSSR1 & ~PDMA_PDSSR1_UART1_TXSEL_Msk) | (u32Ch << PDMA_PDSSR1_UART1_TXSEL_Pos);
        break;
    case 6:
        PDMA_GCR->PDSSR2 = (PDMA_GCR->PDSSR2 & ~PDMA_PDSSR2_I2S_TXSEL_Msk) | (u32Ch << PDMA_PDSSR2_I2S_TXSEL_Pos);
        break;
    case 7:
        PDMA_GCR->PDSSR0 = (PDMA_GCR->PDSSR0 & ~PDMA_PDSSR0_SPI0_RXSEL_Msk) | (u32Ch << PDMA_PDSSR0_SPI0_RXSEL_Pos);
        break;
    case 8:
        PDMA_GCR->PDSSR0 = (PDMA_GCR->PDSSR0 & ~PDMA_PDSSR0_SPI1_RXSEL_Msk) | (u32Ch << PDMA_PDSSR0_SPI1_RXSEL_Pos);
        break;
    case 9:
        PDMA_GCR->PDSSR0 = (PDMA_GCR->PDSSR0 & ~PDMA_PDSSR0_SPI2_RXSEL_Msk) | (u32Ch << PDMA_PDSSR0_SPI2_RXSEL_Pos);
        break;
    case 10:
        PDMA_GCR->PDSSR0 = (PDMA_GCR->PDSSR0 & ~PDMA_PDSSR0_SPI3_RXSEL_Msk) | (u32Ch << PDMA_PDSSR0_SPI3_RXSEL_Pos);
        break;
    case 11:
        PDMA_GCR->PDSSR1 = (PDMA_GCR->PDSSR1 & ~PDMA_PDSSR1_UART0_RXSEL_Msk) | (u32Ch << PDMA_PDSSR1_UART0_RXSEL_Pos);
        break;
    case 12:
        PDMA_GCR->PDSSR1 = (PDMA_GCR->PDSSR1 & ~PDMA_PDSSR1_UART1_RXSEL_Msk) | (u32Ch << PDMA_PDSSR1_UART1_RXSEL_Pos);
        break;
    case 13:
        PDMA_GCR->PDSSR2 = (PDMA_GCR->PDSSR2 & ~PDMA_PDSSR2_I2S_RXSEL_Msk) | (u32Ch << PDMA_PDSSR2_I2S_RXSEL_Pos);
        break;
    case 14:
        PDMA_GCR->PDSSR1 = (PDMA_GCR->PDSSR1 & ~PDMA_PDSSR1_ADC_RXSEL_Msk) | (u32Ch << PDMA_PDSSR1_ADC_RXSEL_Pos);
        break;

    default:/* select PDMA channel as memory to memory */
        for(u32Index = 0; u32Index < 8; u32Index++)
        {
            if((PDMA_GCR->PDSSR0 & (0xF << (u32Index * 4))) == (u32Ch << (u32Index * 4)))
                PDMA_GCR->PDSSR0 |= 0xF << (u32Index * 4);
            if((PDMA_GCR->PDSSR1 & (0xF << (u32Index * 4))) == (u32Ch << (u32Index * 4)))
                PDMA_GCR->PDSSR1 |= 0xF << (u32Index * 4);
            if((PDMA_GCR->PDSSR2 & (0xF << (u32Index * 4))) == (u32Ch << (u32Index * 4)))
                PDMA_GCR->PDSSR2 |= 0xF << (u32Index * 4);
        }
    }
}

/**
 * @brief       Trigger PDMA
 *
 * @param[in]   u32Ch           The selected channel
 *
 * @return      None
 *
 * @details     This function trigger the selected channel.
 */
void PDMA_Trigger(uint32_t u32Ch)
{
    PDMA_T *pdma;
    pdma = (PDMA_T *)((uint32_t) PDMA0_BASE + (0x100 * u32Ch));

    pdma->CSR |= (PDMA_CSR_TRIG_EN_Msk | PDMA_CSR_PDMACEN_Msk);
}

/**
 * @brief       Enable Interrupt
 *
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32Mask         The Interrupt Type
 *
 * @return      None
 *
 * @details     This function enable the selected channel interrupt.
 */
void PDMA_EnableInt(uint32_t u32Ch, uint32_t u32Mask)
{
    PDMA_T *pdma;
    pdma = (PDMA_T *)((uint32_t) PDMA0_BASE + (0x100 * u32Ch));

    pdma->IER |= u32Mask;
}

/**
 * @brief       Disable Interrupt
 *
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32Mask         The Interrupt Type
 *
 * @return      None
 *
 * @details     This function disable the selected channel interrupt.
 */
void PDMA_DisableInt(uint32_t u32Ch, uint32_t u32Mask)
{
    PDMA_T *pdma;
    pdma = (PDMA_T *)((uint32_t) PDMA0_BASE + (0x100 * u32Ch));

    pdma->IER &= ~u32Mask;
}


/*@}*/ /* end of group PDMA_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group PDMA_Driver */

/*@}*/ /* end of group Device_Driver */

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
