/**************************************************************************//**
 * @file     pdma.c
 * @version  V3.00
 * @brief    M2354 series PDMA driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NuMicro.h"


static uint8_t au8ChSelect[PDMA_CH_MAX];

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
 * @param[in]   pdma            The pointer of the specified PDMA module
 * @param[in]   u32Mask         Channel enable bits.
 *
 * @return      None
 *
 * @details     This function enable the PDMA channels.
 */
void PDMA_Open(PDMA_T *pdma, uint32_t u32Mask)
{
    uint32_t i;

    for(i = 0UL; i < (int)PDMA_CH_MAX; i++)
    {
        if((1 << i) & u32Mask)
        {
            (pdma)->DSCT[i].CTL = 0UL;
            au8ChSelect[i] = (uint8_t)PDMA_MEM;
        }
    }

    (pdma)->CHCTL |= u32Mask;
}

/**
 * @brief       PDMA Close
 *
 * @param[in]   pdma            The pointer of the specified PDMA module
 *
 * @return      None
 *
 * @details     This function disable all PDMA channels.
 */
void PDMA_Close(PDMA_T *pdma)
{
    (pdma)->CHCTL = 0UL;
}

/**
 * @brief       Set PDMA Transfer Count
 *
 * @param[in]   pdma            The pointer of the specified PDMA module
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
void PDMA_SetTransferCnt(PDMA_T *pdma, uint32_t u32Ch, uint32_t u32Width, uint32_t u32TransCount)
{
    (pdma)->DSCT[u32Ch].CTL &= ~(PDMA_DSCT_CTL_TXCNT_Msk | PDMA_DSCT_CTL_TXWIDTH_Msk);
    (pdma)->DSCT[u32Ch].CTL |= (u32Width | ((u32TransCount - 1UL) << PDMA_DSCT_CTL_TXCNT_Pos));
}

/**
 * @brief       Set PDMA Stride Mode
 *
 * @param[in]   pdma            The pointer of the specified PDMA module
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32DestLen      Destination stride count
 * @param[in]   u32SrcLen       Source stride count
 * @param[in]   u32TransCount   Transfer count
 *
 * @return      None
 *
 * @details     This function set the selected stride mode.
 */
void PDMA_SetStride(PDMA_T *pdma, uint32_t u32Ch, uint32_t u32DestLen, uint32_t u32SrcLen, uint32_t u32TransCount)
{
    (pdma)->DSCT[u32Ch].CTL |= PDMA_DSCT_CTL_STRIDEEN_Msk;
    (pdma)->STRIDE[u32Ch].ASOCR = (u32DestLen << 16) | u32SrcLen;
    (pdma)->STRIDE[u32Ch].STCR = u32TransCount;
}

/**
 * @brief       Set PDMA Repeat
  *
 * @param[in]   pdma                The pointer of the specified PDMA module
 * @param[in]   u32Ch               The selected channel
 * @param[in]   u32DestInterval     Destination address interval count
 * @param[in]   u32SrcInterval      Source address interval count
 * @param[in]   u32RepeatCount      Repeat count
 *
 * @return      None
 *
 * @details     This function set the selected repeat.
 */
void PDMA_SetRepeat(PDMA_T * pdma, uint32_t u32Ch, uint32_t u32DestInterval, uint32_t u32SrcInterval, uint32_t u32RepeatCount)
{
    pdma->DSCT[u32Ch].CTL |= PDMA_DSCT_CTL_STRIDEEN_Msk;
    pdma->REPEAT[u32Ch].AICTL = ((u32DestInterval) << 16) | (u32SrcInterval);
    pdma->REPEAT[u32Ch].RCNT = u32RepeatCount;
}

/**
 * @brief       Set PDMA Transfer Address
 *
 * @param[in]   pdma            The pointer of the specified PDMA module
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
void PDMA_SetTransferAddr(PDMA_T *pdma, uint32_t u32Ch, uint32_t u32SrcAddr, uint32_t u32SrcCtrl, uint32_t u32DstAddr, uint32_t u32DstCtrl)
{
    (pdma)->DSCT[u32Ch].SA = u32SrcAddr;
    (pdma)->DSCT[u32Ch].DA = u32DstAddr;
    (pdma)->DSCT[u32Ch].CTL &= ~(PDMA_DSCT_CTL_SAINC_Msk | PDMA_DSCT_CTL_DAINC_Msk);
    (pdma)->DSCT[u32Ch].CTL |= (u32SrcCtrl | u32DstCtrl);
}

/**
 * @brief       Set PDMA Transfer Mode
 *
 * @param[in]   pdma            The pointer of the specified PDMA module
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32Peripheral   The selected peripheral. Valid values are
 *                - \ref PDMA_MEM
 *                - \ref PDMA_USB_TX
 *                - \ref PDMA_USB_RX
 *                - \ref PDMA_UART0_TX
 *                - \ref PDMA_UART0_RX
 *                - \ref PDMA_UART1_TX
 *                - \ref PDMA_UART1_RX
 *                - \ref PDMA_UART2_TX
 *                - \ref PDMA_UART2_RX
 *                - \ref PDMA_UART3_TX
 *                - \ref PDMA_UART3_RX
 *                - \ref PDMA_UART4_TX
 *                - \ref PDMA_UART4_RX
 *                - \ref PDMA_UART5_TX
 *                - \ref PDMA_UART5_RX
 *                - \ref PDMA_USCI0_TX
 *                - \ref PDMA_USCI0_RX
 *                - \ref PDMA_USCI1_TX
 *                - \ref PDMA_USCI1_RX
 *                - \ref PDMA_QSPI0_TX
 *                - \ref PDMA_QSPI0_RX
 *                - \ref PDMA_SPI0_TX
 *                - \ref PDMA_SPI0_RX
 *                - \ref PDMA_SPI1_TX
 *                - \ref PDMA_SPI1_RX
 *                - \ref PDMA_SPI2_TX
 *                - \ref PDMA_SPI2_RX
 *                - \ref PDMA_SPI3_TX
 *                - \ref PDMA_SPI3_RX
 *                - \ref PDMA_EPWM0_P1_RX
 *                - \ref PDMA_EPWM0_P2_RX
 *                - \ref PDMA_EPWM0_P3_RX
 *                - \ref PDMA_EPWM1_P1_RX
 *                - \ref PDMA_EPWM1_P2_RX
 *                - \ref PDMA_EPWM1_P3_RX
 *                - \ref PDMA_I2C0_TX
 *                - \ref PDMA_I2C0_RX
 *                - \ref PDMA_I2C1_TX
 *                - \ref PDMA_I2C1_RX
 *                - \ref PDMA_I2C2_TX
 *                - \ref PDMA_I2C2_RX
 *                - \ref PDMA_I2S0_TX
 *                - \ref PDMA_I2S0_RX
 *                - \ref PDMA_TMR0
 *                - \ref PDMA_TMR1
 *                - \ref PDMA_TMR2
 *                - \ref PDMA_TMR3
 *                - \ref PDMA_ADC_RX
 *                - \ref PDMA_DAC0_TX
 *                - \ref PDMA_DAC1_TX
 *                - \ref PDMA_EPWM0_CH0_TX
 *                - \ref PDMA_EPWM0_CH1_TX
 *                - \ref PDMA_EPWM0_CH2_TX
 *                - \ref PDMA_EPWM0_CH3_TX
 *                - \ref PDMA_EPWM0_CH4_TX
 *                - \ref PDMA_EPWM0_CH5_TX
 *                - \ref PDMA_EPWM1_CH0_TX
 *                - \ref PDMA_EPWM1_CH1_TX
 *                - \ref PDMA_EPWM1_CH2_TX
 *                - \ref PDMA_EPWM1_CH3_TX
 *                - \ref PDMA_EPWM1_CH4_TX
 *                - \ref PDMA_EPWM1_CH5_TX
 * @param[in]   u32ScatterEn    Scatter-gather mode enable
 * @param[in]   u32DescAddr     Scatter-gather descriptor address
 *
 * @return      None
 *
 * @details     This function set the selected channel transfer mode. Include peripheral setting.
 */
void PDMA_SetTransferMode(PDMA_T *pdma, uint32_t u32Ch, uint32_t u32Peripheral, uint32_t u32ScatterEn, uint32_t u32DescAddr)
{
    au8ChSelect[u32Ch] = (uint8_t)u32Peripheral;
    switch(u32Ch)
    {
        case 0UL:
            (pdma)->REQSEL0_3 = ((pdma)->REQSEL0_3 & ~PDMA_REQSEL0_3_REQSRC0_Msk) | u32Peripheral;
            break;
        case 1UL:
            (pdma)->REQSEL0_3 = ((pdma)->REQSEL0_3 & ~PDMA_REQSEL0_3_REQSRC1_Msk) | (u32Peripheral << PDMA_REQSEL0_3_REQSRC1_Pos);
            break;
        case 2UL:
            (pdma)->REQSEL0_3 = ((pdma)->REQSEL0_3 & ~PDMA_REQSEL0_3_REQSRC2_Msk) | (u32Peripheral << PDMA_REQSEL0_3_REQSRC2_Pos);
            break;
        case 3UL:
            (pdma)->REQSEL0_3 = ((pdma)->REQSEL0_3 & ~PDMA_REQSEL0_3_REQSRC3_Msk) | (u32Peripheral << PDMA_REQSEL0_3_REQSRC3_Pos);
            break;
        case 4UL:
            (pdma)->REQSEL4_7 = ((pdma)->REQSEL4_7 & ~PDMA_REQSEL4_7_REQSRC4_Msk) | u32Peripheral;
            break;
        case 5UL:
            (pdma)->REQSEL4_7 = ((pdma)->REQSEL4_7 & ~PDMA_REQSEL4_7_REQSRC5_Msk) | (u32Peripheral << PDMA_REQSEL4_7_REQSRC5_Pos);
            break;
        case 6UL:
            (pdma)->REQSEL4_7 = ((pdma)->REQSEL4_7 & ~PDMA_REQSEL4_7_REQSRC6_Msk) | (u32Peripheral << PDMA_REQSEL4_7_REQSRC6_Pos);
            break;
        case 7UL:
            (pdma)->REQSEL4_7 = ((pdma)->REQSEL4_7 & ~PDMA_REQSEL4_7_REQSRC7_Msk) | (u32Peripheral << PDMA_REQSEL4_7_REQSRC7_Pos);
            break;
        default:
            break;
    }

    if(u32ScatterEn)
    {
        (pdma)->DSCT[u32Ch].CTL = ((pdma)->DSCT[u32Ch].CTL & ~PDMA_DSCT_CTL_OPMODE_Msk) | PDMA_OP_SCATTER;
        (pdma)->DSCT[u32Ch].NEXT = u32DescAddr - ((pdma)->SCATBA);
    }
    else
    {
        (pdma)->DSCT[u32Ch].CTL = ((pdma)->DSCT[u32Ch].CTL & ~PDMA_DSCT_CTL_OPMODE_Msk) | PDMA_OP_BASIC;
    }
}

/**
 * @brief       Set PDMA Burst Type and Size
 *
 * @param[in]   pdma            The pointer of the specified PDMA module
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32BurstType    Burst mode or single mode. Valid values are
 *                - \ref PDMA_REQ_SINGLE
 *                - \ref PDMA_REQ_BURST
 * @param[in]   u32BurstSize    Set the size of burst mode. Valid values are
 *                - \ref PDMA_BURST_128
 *                - \ref PDMA_BURST_64
 *                - \ref PDMA_BURST_32
 *                - \ref PDMA_BURST_16
 *                - \ref PDMA_BURST_8
 *                - \ref PDMA_BURST_4
 *                - \ref PDMA_BURST_2
 *                - \ref PDMA_BURST_1
 *
 * @return      None
 *
 * @details     This function set the selected channel burst type and size.
 */
void PDMA_SetBurstType(PDMA_T *pdma, uint32_t u32Ch, uint32_t u32BurstType, uint32_t u32BurstSize)
{
    (pdma)->DSCT[u32Ch].CTL &= ~(PDMA_DSCT_CTL_TXTYPE_Msk | PDMA_DSCT_CTL_BURSIZE_Msk);
    (pdma)->DSCT[u32Ch].CTL |= (u32BurstType | u32BurstSize);
}

/**
 * @brief       Enable timeout function
 *
 * @param[in]   pdma            The pointer of the specified PDMA module
 * @param[in]   u32Mask         Channel enable bits.
 *
 * @return      None
 *
 * @details     This function enable timeout function of the selected channel(s).
 * @note        This function is only supported in channel 0 and channel 1.
 */
void PDMA_EnableTimeout(PDMA_T *pdma, uint32_t u32Mask)
{
    (pdma)->TOUTEN |= u32Mask;
}

/**
 * @brief       Disable timeout function
 *
 * @param[in]   pdma            The pointer of the specified PDMA module
 * @param[in]   u32Mask         Channel enable bits.
 *
 * @return      None
 *
 * @details     This function disable timeout function of the selected channel(s).
 * @note        This function is only supported in channel 0 and channel 1.
 */
void PDMA_DisableTimeout(PDMA_T *pdma, uint32_t u32Mask)
{
    (pdma)->TOUTEN &= ~u32Mask;
}

/**
 * @brief       Set PDMA Timeout Count
 *
 * @param[in]   pdma            The pointer of the specified PDMA module
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32OnOff        Enable/disable timeout function
 * @param[in]   u32TimeOutCnt   Timeout count
 *
 * @return      None
 *
 * @details     This function set the timeout count.
 * @note        This function is only supported in channel 0 and channel 1.
 */
void PDMA_SetTimeOut(PDMA_T *pdma, uint32_t u32Ch, uint32_t u32OnOff, uint32_t u32TimeOutCnt)
{
    switch(u32Ch)
    {
        case 0UL:
            (pdma)->TOC0_1 = ((pdma)->TOC0_1 & ~PDMA_TOC0_1_TOC0_Msk) | u32TimeOutCnt;
            break;
        case 1UL:
            (pdma)->TOC0_1 = ((pdma)->TOC0_1 & ~PDMA_TOC0_1_TOC1_Msk) | (u32TimeOutCnt << PDMA_TOC0_1_TOC1_Pos);
            break;

        default:
            break;
    }
    if(u32OnOff)
    {
        (pdma)->TOUTEN |= (1UL << u32Ch);
    }
    else
    {
        (pdma)->TOUTEN &= ~(1UL << u32Ch);
    }
}

/**
 * @brief       Trigger PDMA
 *
 * @param[in]   pdma            The pointer of the specified PDMA module
 * @param[in]   u32Ch           The selected channel
 *
 * @return      None
 *
 * @details     This function trigger the selected channel.
 */
void PDMA_Trigger(PDMA_T *pdma, uint32_t u32Ch)
{
    if(au8ChSelect[u32Ch] == PDMA_MEM)
    {
        (pdma)->SWREQ = (1UL << u32Ch);
    }
}

/**
 * @brief       Enable Interrupt
 *
 * @param[in]   pdma            The pointer of the specified PDMA module
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32Mask         The Interrupt Type. Valid values are
 *                - \ref PDMA_INT_TRANS_DONE
 *                - \ref PDMA_INT_TABLE
 *                - \ref PDMA_INT_TIMEOUT
 *                - \ref PDMA_INT_ALIGN
 *
 * @return      None
 *
 * @details     This function enable the selected channel interrupt.
 * @note        PDMA_INT_TIMEOUT is only supported in channel 0 and channel 1.
 */
void PDMA_EnableInt(PDMA_T *pdma, uint32_t u32Ch, uint32_t u32Mask)
{
    switch(u32Mask)
    {
        case PDMA_INT_TRANS_DONE:
        case PDMA_INT_ALIGN:
            (pdma)->INTEN |= (1UL << u32Ch);
            break;
        case PDMA_INT_TABLE:
            (pdma)->DSCT[u32Ch].CTL &= ~PDMA_DSCT_CTL_TBINTDIS_Msk;
            break;
        case PDMA_INT_TIMEOUT:
            (pdma)->TOUTIEN |= (1UL << u32Ch);
            break;

        default:
            break;
    }
}

/**
 * @brief       Disable Interrupt
 *
 * @param[in]   pdma            The pointer of the specified PDMA module
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32Mask         The Interrupt Type. Valid values are
 *                - \ref PDMA_INT_TRANS_DONE
 *                - \ref PDMA_INT_TABLE
 *                - \ref PDMA_INT_TIMEOUT
 *                - \ref PDMA_INT_ALIGN
 *
 * @return      None
 *
 * @details     This function disable the selected channel interrupt.
 * @note        PDMA_INT_TIMEOUT is only supported in channel 0 and channel 1.
 * @note        The transfer done interrupt is disabled when table empty interrupt is disabled(PDMA_INT_TEMPTY).
 */
void PDMA_DisableInt(PDMA_T *pdma, uint32_t u32Ch, uint32_t u32Mask)
{
    switch(u32Mask)
    {
        case PDMA_INT_TRANS_DONE:
        case PDMA_INT_ALIGN:
            (pdma)->INTEN &= ~(1UL << u32Ch);
            break;
        case PDMA_INT_TABLE:
            (pdma)->DSCT[u32Ch].CTL |= PDMA_DSCT_CTL_TBINTDIS_Msk;
            break;
        case PDMA_INT_TIMEOUT:
            (pdma)->TOUTIEN &= ~(1UL << u32Ch);
            break;

        default:
            break;
    }
}

/**@}*/ /* end of group PDMA_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group PDMA_Driver */

/**@}*/ /* end of group Standard_Driver */

