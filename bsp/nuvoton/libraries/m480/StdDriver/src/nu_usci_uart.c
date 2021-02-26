/**************************************************************************//**
 * @file     usci_uart.c
 * @version  V3.00
 * @brief    M480 series USCI UART (UUART) driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup USCI_UART_Driver USCI_UART Driver
  @{
*/

/** @addtogroup USCI_UART_EXPORTED_FUNCTIONS USCI_UART Exported Functions
  @{
*/

/**
 *    @brief        Clear USCI_UART specified interrupt flag
 *
 *    @param[in]    uuart   The pointer of the specified USCI_UART module.
 *    @param[in]    u32Mask The combination of all related interrupt sources.
 *                          Each bit corresponds to a interrupt source.
 *                          This parameter decides which interrupt flags will be cleared. It could be the combination of:
 *                          - \ref UUART_ABR_INT_MASK
 *                          - \ref UUART_RLS_INT_MASK
 *                          - \ref UUART_BUF_RXOV_INT_MASK
 *                          - \ref UUART_TXST_INT_MASK
 *                          - \ref UUART_TXEND_INT_MASK
 *                          - \ref UUART_RXST_INT_MASK
 *                          - \ref UUART_RXEND_INT_MASK
 *
 *    @return       None
 *
 *    @details      The function is used to clear USCI_UART related interrupt flags specified by u32Mask parameter.
 */

void UUART_ClearIntFlag(UUART_T* uuart, uint32_t u32Mask)
{

    if(u32Mask & UUART_ABR_INT_MASK)   /* Clear Auto-baud Rate Interrupt */
    {
        uuart->PROTSTS = UUART_PROTSTS_ABRDETIF_Msk;
    }

    if(u32Mask & UUART_RLS_INT_MASK)   /* Clear Receive Line Status Interrupt */
    {
        uuart->PROTSTS = (UUART_PROTSTS_BREAK_Msk | UUART_PROTSTS_FRMERR_Msk | UUART_PROTSTS_PARITYERR_Msk);
    }

    if(u32Mask & UUART_BUF_RXOV_INT_MASK)   /* Clear Receive Buffer Over-run Error Interrupt */
    {
        uuart->BUFSTS = UUART_BUFSTS_RXOVIF_Msk;
    }

    if(u32Mask & UUART_TXST_INT_MASK)   /* Clear Transmit Start Interrupt */
    {
        uuart->PROTSTS = UUART_PROTSTS_TXSTIF_Msk;
    }

    if(u32Mask & UUART_TXEND_INT_MASK)   /* Clear Transmit End Interrupt */
    {
        uuart->PROTSTS = UUART_PROTSTS_TXENDIF_Msk;
    }

    if(u32Mask & UUART_RXST_INT_MASK)   /* Clear Receive Start Interrupt */
    {
        uuart->PROTSTS = UUART_PROTSTS_RXSTIF_Msk;
    }

    if(u32Mask & UUART_RXEND_INT_MASK)   /* Clear Receive End Interrupt */
    {
        uuart->PROTSTS = UUART_PROTSTS_RXENDIF_Msk;
    }

}

/**
 *    @brief        Get USCI_UART specified interrupt flag
 *
 *    @param[in]    uuart   The pointer of the specified USCI_UART module.
 *    @param[in]    u32Mask The combination of all related interrupt sources.
 *                          Each bit corresponds to a interrupt source.
 *                          This parameter decides which interrupt flags will be read. It is combination of:
 *                          - \ref UUART_ABR_INT_MASK
 *                          - \ref UUART_RLS_INT_MASK
 *                          - \ref UUART_BUF_RXOV_INT_MASK
 *                          - \ref UUART_TXST_INT_MASK
 *                          - \ref UUART_TXEND_INT_MASK
 *                          - \ref UUART_RXST_INT_MASK
 *                          - \ref UUART_RXEND_INT_MASK
 *
 *    @return       Interrupt flags of selected sources.
 *
 *    @details      The function is used to get USCI_UART related interrupt flags specified by u32Mask parameter.
 */

uint32_t UUART_GetIntFlag(UUART_T* uuart, uint32_t u32Mask)
{
    uint32_t u32IntFlag = 0ul;
    uint32_t u32Tmp1, u32Tmp2;

    /* Check Auto-baud Rate Interrupt Flag */
    u32Tmp1 = (u32Mask & UUART_ABR_INT_MASK);
    u32Tmp2 = (uuart->PROTSTS & UUART_PROTSTS_ABRDETIF_Msk);
    if(u32Tmp1 && u32Tmp2)
    {
        u32IntFlag |= UUART_ABR_INT_MASK;
    }

    /* Check Receive Line Status Interrupt Flag */
    u32Tmp1 = (u32Mask & UUART_RLS_INT_MASK);
    u32Tmp2 = (uuart->PROTSTS & (UUART_PROTSTS_BREAK_Msk | UUART_PROTSTS_FRMERR_Msk | UUART_PROTSTS_PARITYERR_Msk));
    if(u32Tmp1 && u32Tmp2)
    {
        u32IntFlag |= UUART_RLS_INT_MASK;
    }

    /* Check Receive Buffer Over-run Error Interrupt Flag */
    u32Tmp1 = (u32Mask & UUART_BUF_RXOV_INT_MASK);
    u32Tmp2 = (uuart->BUFSTS & UUART_BUFSTS_RXOVIF_Msk);
    if(u32Tmp1 && u32Tmp2)
    {
        u32IntFlag |= UUART_BUF_RXOV_INT_MASK;
    }

    /* Check Transmit Start Interrupt Flag */
    u32Tmp1 = (u32Mask & UUART_TXST_INT_MASK);
    u32Tmp2 = (uuart->PROTSTS & UUART_PROTSTS_TXSTIF_Msk);
    if(u32Tmp1 && u32Tmp2)
    {
        u32IntFlag |= UUART_TXST_INT_MASK;
    }

    /* Check Transmit End Interrupt Flag */
    u32Tmp1 = (u32Mask & UUART_TXEND_INT_MASK);
    u32Tmp2 = (uuart->PROTSTS & UUART_PROTSTS_TXENDIF_Msk);
    if(u32Tmp1 && u32Tmp2)
    {
        u32IntFlag |= UUART_TXEND_INT_MASK;
    }

    /* Check Receive Start Interrupt Flag */
    u32Tmp1 = (u32Mask & UUART_RXST_INT_MASK);
    u32Tmp2 = (uuart->PROTSTS & UUART_PROTSTS_RXSTIF_Msk);
    if(u32Tmp1 && u32Tmp2)
    {
        u32IntFlag |= UUART_RXST_INT_MASK;
    }

    /* Check Receive End Interrupt Flag */
    u32Tmp1 = (u32Mask & UUART_RXEND_INT_MASK);
    u32Tmp2 = (uuart->PROTSTS & UUART_PROTSTS_RXENDIF_Msk);
    if(u32Tmp1 && u32Tmp2)
    {
        u32IntFlag |= UUART_RXEND_INT_MASK;
    }

    return u32IntFlag;

}


/**
 *  @brief      Disable USCI_UART function mode
 *
 *  @param[in]  uuart The pointer of the specified USCI_UART module.
 *
 *  @return     None
 *
 *  @details    The function is used to disable USCI_UART function mode.
 */
void UUART_Close(UUART_T* uuart)
{
    uuart->CTL = 0ul;
}


/**
 *    @brief        Disable interrupt function.
 *
 *    @param[in]    uuart   The pointer of the specified USCI_UART module.
 *    @param[in]    u32Mask The combination of all related interrupt enable bits.
 *                          Each bit corresponds to a interrupt enable bit.
 *                          This parameter decides which interrupts will be disabled. It is combination of:
 *                          - \ref UUART_ABR_INT_MASK
 *                          - \ref UUART_RLS_INT_MASK
 *                          - \ref UUART_BUF_RXOV_INT_MASK
 *                          - \ref UUART_TXST_INT_MASK
 *                          - \ref UUART_TXEND_INT_MASK
 *                          - \ref UUART_RXST_INT_MASK
 *                          - \ref UUART_RXEND_INT_MASK
 *
 *    @return       None
 *
 *    @details      The function is used to disabled USCI_UART related interrupts specified by u32Mask parameter.
 */
void UUART_DisableInt(UUART_T* uuart, uint32_t u32Mask)
{

    /* Disable Auto-baud rate interrupt flag */
    if((u32Mask & UUART_ABR_INT_MASK) == UUART_ABR_INT_MASK)
    {
        uuart->PROTIEN &= ~UUART_PROTIEN_ABRIEN_Msk;
    }

    /* Disable receive line status interrupt flag */
    if((u32Mask & UUART_RLS_INT_MASK) == UUART_RLS_INT_MASK)
    {
        uuart->PROTIEN &= ~UUART_PROTIEN_RLSIEN_Msk;
    }

    /* Disable RX overrun interrupt flag */
    if((u32Mask & UUART_BUF_RXOV_INT_MASK) == UUART_BUF_RXOV_INT_MASK)
    {
        uuart->BUFCTL &= ~UUART_BUFCTL_RXOVIEN_Msk;
    }

    /* Disable TX start interrupt flag */
    if((u32Mask & UUART_TXST_INT_MASK) == UUART_TXST_INT_MASK)
    {
        uuart->INTEN &= ~UUART_INTEN_TXSTIEN_Msk;
    }

    /* Disable TX end interrupt flag */
    if((u32Mask & UUART_TXEND_INT_MASK) == UUART_TXEND_INT_MASK)
    {
        uuart->INTEN &= ~UUART_INTEN_TXENDIEN_Msk;
    }

    /* Disable RX start interrupt flag */
    if((u32Mask & UUART_RXST_INT_MASK) == UUART_RXST_INT_MASK)
    {
        uuart->INTEN &= ~UUART_INTEN_RXSTIEN_Msk;
    }

    /* Disable RX end interrupt flag */
    if((u32Mask & UUART_RXEND_INT_MASK) == UUART_RXEND_INT_MASK)
    {
        uuart->INTEN &= ~UUART_INTEN_RXENDIEN_Msk;
    }
}


/**
 *    @brief        Enable interrupt function.
 *
 *    @param[in]    uuart       The pointer of the specified USCI_UART module.
 *    @param[in]    u32Mask     The combination of all related interrupt enable bits.
 *                              Each bit corresponds to a interrupt enable bit.
 *                              This parameter decides which interrupts will be enabled. It is combination of:
 *                              - \ref UUART_ABR_INT_MASK
 *                              - \ref UUART_RLS_INT_MASK
 *                              - \ref UUART_BUF_RXOV_INT_MASK
 *                              - \ref UUART_TXST_INT_MASK
 *                              - \ref UUART_TXEND_INT_MASK
 *                              - \ref UUART_RXST_INT_MASK
 *                              - \ref UUART_RXEND_INT_MASK
 *
 *    @return       None
 *
 *    @details      The function is used to enable USCI_UART related interrupts specified by u32Mask parameter.
 */
void UUART_EnableInt(UUART_T*  uuart, uint32_t u32Mask)
{
    /* Enable Auto-baud rate interrupt flag */
    if((u32Mask & UUART_ABR_INT_MASK) == UUART_ABR_INT_MASK)
    {
        uuart->PROTIEN |= UUART_PROTIEN_ABRIEN_Msk;
    }

    /* Enable receive line status interrupt flag */
    if((u32Mask & UUART_RLS_INT_MASK) == UUART_RLS_INT_MASK)
    {
        uuart->PROTIEN |= UUART_PROTIEN_RLSIEN_Msk;
    }

    /* Enable RX overrun interrupt flag */
    if((u32Mask & UUART_BUF_RXOV_INT_MASK) == UUART_BUF_RXOV_INT_MASK)
    {
        uuart->BUFCTL |= UUART_BUFCTL_RXOVIEN_Msk;
    }

    /* Enable TX start interrupt flag */
    if((u32Mask & UUART_TXST_INT_MASK) == UUART_TXST_INT_MASK)
    {
        uuart->INTEN |= UUART_INTEN_TXSTIEN_Msk;
    }

    /* Enable TX end interrupt flag */
    if((u32Mask & UUART_TXEND_INT_MASK) == UUART_TXEND_INT_MASK)
    {
        uuart->INTEN |= UUART_INTEN_TXENDIEN_Msk;
    }

    /* Enable RX start interrupt flag */
    if((u32Mask & UUART_RXST_INT_MASK) == UUART_RXST_INT_MASK)
    {
        uuart->INTEN |= UUART_INTEN_RXSTIEN_Msk;
    }

    /* Enable RX end interrupt flag */
    if((u32Mask & UUART_RXEND_INT_MASK) == UUART_RXEND_INT_MASK)
    {
        uuart->INTEN |= UUART_INTEN_RXENDIEN_Msk;
    }
}


/**
 *    @brief        Open and set USCI_UART function
 *
 *    @param[in]    uuart           The pointer of the specified USCI_UART module.
 *    @param[in]    u32baudrate     The baud rate of USCI_UART module.
 *
 *    @return       Real baud rate of USCI_UART module.
 *
 *    @details      This function use to enable USCI_UART function and set baud-rate.
 */
uint32_t UUART_Open(UUART_T* uuart, uint32_t u32baudrate)
{
    uint32_t u32PCLKFreq, u32PDSCnt, u32DSCnt, u32ClkDiv;
    uint32_t u32Tmp, u32Tmp2, u32Min, u32MinClkDiv, u32MinDSCnt;
    uint32_t u32Div;

    /* Get PCLK frequency */
    if( uuart == UUART0)
    {
        u32PCLKFreq = CLK_GetPCLK0Freq();
    }
    else
    {
        u32PCLKFreq = CLK_GetPCLK1Freq();
    }

    u32Div = u32PCLKFreq / u32baudrate;
    u32Tmp = (u32PCLKFreq / u32Div) - u32baudrate;
    u32Tmp2 = u32baudrate - (u32PCLKFreq / (u32Div+1ul));

    if(u32Tmp >= u32Tmp2) u32Div = u32Div + 1ul;

    u32Tmp = 0x400ul * 0x10ul;
    for(u32PDSCnt = 1ul; u32PDSCnt <= 0x04ul; u32PDSCnt++)
    {
        if(u32Div <= (u32Tmp * u32PDSCnt)) break;
    }

    if(u32PDSCnt > 0x4ul) u32PDSCnt = 0x4ul;

    u32Div = u32Div / u32PDSCnt;

    /* Find best solution */
    u32Min = (uint32_t) - 1;
    u32MinDSCnt = 0ul;
    u32MinClkDiv = 0ul;
    u32Tmp = 0ul;

    for(u32DSCnt = 6ul; u32DSCnt <= 0x10ul; u32DSCnt++)   /* DSCNT could be 0x5~0xF */
    {

        u32ClkDiv = u32Div / u32DSCnt;

        if(u32ClkDiv > 0x400ul)
        {
            u32ClkDiv = 0x400ul;
            u32Tmp = u32Div - (u32ClkDiv * u32DSCnt);
            u32Tmp2 = u32Tmp + 1ul;
        }
        else
        {
            u32Tmp = u32Div - (u32ClkDiv * u32DSCnt);
            u32Tmp2 = ((u32ClkDiv+1ul) * u32DSCnt) - u32Div;
        }

        if(u32Tmp >= u32Tmp2)
        {
            u32ClkDiv = u32ClkDiv + 1ul;
        }
        else u32Tmp2 = u32Tmp;

        if(u32Tmp2 < u32Min)
        {
            u32Min = u32Tmp2;
            u32MinDSCnt = u32DSCnt;
            u32MinClkDiv = u32ClkDiv;

            /* Break when get good results */
            if(u32Min == 0ul)
            {
                break;
            }
        }
    }

    /* Enable USCI_UART protocol */
    uuart->CTL &= ~UUART_CTL_FUNMODE_Msk;
    uuart->CTL = 2ul << UUART_CTL_FUNMODE_Pos;

    /* Set USCI_UART line configuration */
    uuart->LINECTL = UUART_WORD_LEN_8 | UUART_LINECTL_LSB_Msk;
    uuart->DATIN0 = (2ul << UUART_DATIN0_EDGEDET_Pos);  /* Set falling edge detection */

    /* Set USCI_UART baud rate */
    uuart->BRGEN = ((u32MinClkDiv-1ul) << UUART_BRGEN_CLKDIV_Pos) |
                   ((u32MinDSCnt-1ul) << UUART_BRGEN_DSCNT_Pos) |
                   ((u32PDSCnt-1ul) << UUART_BRGEN_PDSCNT_Pos);

    uuart->PROTCTL |= UUART_PROTCTL_PROTEN_Msk;

    return (u32PCLKFreq/u32PDSCnt/u32MinDSCnt/u32MinClkDiv);
}


/**
 *    @brief        Read USCI_UART data
 *
 *    @param[in]    uuart           The pointer of the specified USCI_UART module.
 *    @param[in]    pu8RxBuf        The buffer to receive the data of receive buffer.
 *    @param[in]    u32ReadBytes    The read bytes number of data.
 *
 *    @return       Receive byte count
 *
 *    @details      The function is used to read Rx data from RX buffer and the data will be stored in pu8RxBuf.
 */
uint32_t UUART_Read(UUART_T* uuart, uint8_t pu8RxBuf[], uint32_t u32ReadBytes)
{
    uint32_t  u32Count, u32delayno;

    for(u32Count = 0ul; u32Count < u32ReadBytes; u32Count++)
    {
        u32delayno = 0ul;

        while(uuart->BUFSTS & UUART_BUFSTS_RXEMPTY_Msk)   /* Check RX empty => failed */
        {
            u32delayno++;
            if(u32delayno >= 0x40000000ul)
            {
                break;
            }
        }

        if(u32delayno >= 0x40000000ul)
        {
            break;
        }

        pu8RxBuf[u32Count] = (uint8_t)uuart->RXDAT;    /* Get Data from USCI RX  */
    }

    return u32Count;

}


/**
 *    @brief        Set USCI_UART line configuration
 *
 *    @param[in]    uuart           The pointer of the specified USCI_UART module.
 *    @param[in]    u32baudrate     The register value of baud rate of USCI_UART module.
 *                                  If u32baudrate = 0, USCI_UART baud rate will not change.
 *    @param[in]    u32data_width   The data length of USCI_UART module.
 *                                  - \ref UUART_WORD_LEN_6
 *                                  - \ref UUART_WORD_LEN_7
 *                                  - \ref UUART_WORD_LEN_8
 *                                  - \ref UUART_WORD_LEN_9
 *    @param[in]    u32parity       The parity setting (none/odd/even) of USCI_UART module.
 *                                  - \ref UUART_PARITY_NONE
 *                                  - \ref UUART_PARITY_ODD
 *                                  - \ref UUART_PARITY_EVEN
 *    @param[in]    u32stop_bits    The stop bit length (1/2 bit) of USCI_UART module.
 *                                  - \ref UUART_STOP_BIT_1
 *                                  - \ref UUART_STOP_BIT_2
 *
 *    @return       Real baud rate of USCI_UART module.
 *
 *    @details      This function use to config USCI_UART line setting.
 */
uint32_t UUART_SetLine_Config(UUART_T* uuart, uint32_t u32baudrate, uint32_t u32data_width, uint32_t u32parity, uint32_t u32stop_bits)
{
    uint32_t u32PCLKFreq, u32PDSCnt, u32DSCnt, u32ClkDiv;
    uint32_t u32Tmp, u32Tmp2, u32Min, u32MinClkDiv, u32MinDSCnt;
    uint32_t u32Div;

    /* Get PCLK frequency */
    if(uuart == UUART0)
    {
        u32PCLKFreq = CLK_GetPCLK0Freq();
    }
    else     /* UUART1 */
    {
        u32PCLKFreq = CLK_GetPCLK1Freq();
    }

    if(u32baudrate != 0ul)
    {
        u32Div = u32PCLKFreq / u32baudrate;
        u32Tmp = (u32PCLKFreq / u32Div) - u32baudrate;
        u32Tmp2 = u32baudrate - (u32PCLKFreq / (u32Div+1ul));

        if(u32Tmp >= u32Tmp2) u32Div = u32Div + 1ul;

        u32Tmp = 0x400ul * 0x10ul;
        for(u32PDSCnt = 1ul; u32PDSCnt <= 0x04ul; u32PDSCnt++)
        {
            if(u32Div <= (u32Tmp * u32PDSCnt)) break;
        }

        if(u32PDSCnt > 0x4ul) u32PDSCnt = 0x4ul;

        u32Div = u32Div / u32PDSCnt;

        /* Find best solution */
        u32Min = (uint32_t) - 1;
        u32MinDSCnt = 0ul;
        u32MinClkDiv = 0ul;

        for(u32DSCnt = 6ul; u32DSCnt <= 0x10ul; u32DSCnt++)   /* DSCNT could be 0x5~0xF */
        {
            u32ClkDiv = u32Div / u32DSCnt;

            if(u32ClkDiv > 0x400ul)
            {
                u32ClkDiv = 0x400ul;
                u32Tmp = u32Div - (u32ClkDiv * u32DSCnt);
                u32Tmp2 = u32Tmp + 1ul;
            }
            else
            {
                u32Tmp = u32Div - (u32ClkDiv * u32DSCnt);
                u32Tmp2 = ((u32ClkDiv+1ul) * u32DSCnt) - u32Div;
            }

            if(u32Tmp >= u32Tmp2)
            {
                u32ClkDiv = u32ClkDiv + 1ul;
            }
            else u32Tmp2 = u32Tmp;

            if(u32Tmp2 < u32Min)
            {
                u32Min = u32Tmp2;
                u32MinDSCnt = u32DSCnt;
                u32MinClkDiv = u32ClkDiv;

                /* Break when get good results */
                if(u32Min == 0ul)
                {
                    break;
                }
            }
        }

        /* Set USCI_UART baud rate */
        uuart->BRGEN = ((u32MinClkDiv-1ul) << UUART_BRGEN_CLKDIV_Pos) |
                       ((u32MinDSCnt-1ul) << UUART_BRGEN_DSCNT_Pos) |
                       ((u32PDSCnt-1ul) << UUART_BRGEN_PDSCNT_Pos);
    }
    else
    {
        u32PDSCnt = ((uuart->BRGEN & UUART_BRGEN_PDSCNT_Msk) >> UUART_BRGEN_PDSCNT_Pos) + 1ul;
        u32MinDSCnt = ((uuart->BRGEN & UUART_BRGEN_DSCNT_Msk) >> UUART_BRGEN_DSCNT_Pos) + 1ul;
        u32MinClkDiv = ((uuart->BRGEN & UUART_BRGEN_CLKDIV_Msk) >> UUART_BRGEN_CLKDIV_Pos) + 1ul;
    }

    /* Set USCI_UART line configuration */
    uuart->LINECTL = (uuart->LINECTL & ~UUART_LINECTL_DWIDTH_Msk) | u32data_width;
    uuart->PROTCTL = (uuart->PROTCTL & ~(UUART_PROTCTL_STICKEN_Msk | UUART_PROTCTL_EVENPARITY_Msk |
                                         UUART_PROTCTL_PARITYEN_Msk)) | u32parity;
    uuart->PROTCTL = (uuart->PROTCTL & ~UUART_PROTCTL_STOPB_Msk ) | u32stop_bits;

    return (u32PCLKFreq/u32PDSCnt/u32MinDSCnt/u32MinClkDiv);
}


/**
 *    @brief        Write USCI_UART data
 *
 *    @param[in]    uuart           The pointer of the specified USCI_UART module.
 *    @param[in]    pu8TxBuf        The buffer to send the data to USCI transmission buffer.
 *    @param[out]   u32WriteBytes   The byte number of data.
 *
 *    @return       Transfer byte count
 *
 *    @details      The function is to write data into TX buffer to transmit data by USCI_UART.
 */
uint32_t UUART_Write(UUART_T* uuart, uint8_t pu8TxBuf[], uint32_t u32WriteBytes)
{
    uint32_t  u32Count, u32delayno;

    for(u32Count = 0ul; u32Count != u32WriteBytes; u32Count++)
    {
        u32delayno = 0ul;
        while((uuart->BUFSTS & UUART_BUFSTS_TXEMPTY_Msk) == 0ul)   /* Wait Tx empty */
        {
            u32delayno++;
            if(u32delayno >= 0x40000000ul)
            {
                break;
            }
        }

        if(u32delayno >= 0x40000000ul)
        {
            break;
        }

        uuart->TXDAT = (uint8_t)pu8TxBuf[u32Count];    /* Send USCI_UART Data to buffer */
    }

    return u32Count;

}


/**
 *    @brief        Enable USCI_UART Wake-up Function
 *
 *    @param[in]    uuart           The pointer of the specified USCI_UART module.
 *    @param[in]    u32WakeupMode   The wakeup mode of USCI_UART module.
 *                                   - \ref UUART_PROTCTL_DATWKEN_Msk    : Data wake-up Mode
 *                                   - \ref UUART_PROTCTL_CTSWKEN_Msk    : nCTS wake-up Mode
 *
 *    @return       None
 *
 *    @details      The function is used to enable Wake-up function of USCI_UART.
 */
void UUART_EnableWakeup(UUART_T* uuart, uint32_t u32WakeupMode)
{
    uuart->PROTCTL |= u32WakeupMode;
    uuart->WKCTL |= UUART_WKCTL_WKEN_Msk;
}


/**
 *    @brief        Disable USCI_UART Wake-up Function
 *
 *    @param[in]    uuart   The pointer of the specified USCI_UART module.
 *
 *    @return       None
 *
 *    @details      The function is used to disable Wake-up function of USCI_UART.
 */
void UUART_DisableWakeup(UUART_T* uuart)
{
    uuart->PROTCTL &= ~(UUART_PROTCTL_DATWKEN_Msk|UUART_PROTCTL_CTSWKEN_Msk);
    uuart->WKCTL &= ~UUART_WKCTL_WKEN_Msk;
}

/**
 *    @brief        Enable USCI_UART auto flow control
 *
 *    @param[in]    uuart   The pointer of the specified USCI_UART module.
 *
 *    @return       None
 *
 *    @details      The function is used to enable USCI_UART auto flow control.
 */
void UUART_EnableFlowCtrl(UUART_T* uuart)
{
    /* Set RTS signal is low level active */
    uuart->LINECTL &= ~UUART_LINECTL_CTLOINV_Msk;

    /* Set CTS signal is low level active */
    uuart->CTLIN0 &= ~UUART_CTLIN0_ININV_Msk;

    /* Enable CTS and RTS auto flow control function */
    uuart->PROTCTL |= UUART_PROTCTL_RTSAUTOEN_Msk|UUART_PROTCTL_CTSAUTOEN_Msk;
}

/**
 *    @brief        Disable USCI_UART auto flow control
 *
 *    @param[in]    uuart    The pointer of the specified USCI_UART module.
 *
 *    @return       None
 *
 *    @details      The function is used to disable USCI_UART auto flow control.
 */
void UUART_DisableFlowCtrl(UUART_T* uuart)
{
    /* Disable CTS and RTS auto flow control function */
    uuart->PROTCTL &= ~(UUART_PROTCTL_RTSAUTOEN_Msk|UUART_PROTCTL_CTSAUTOEN_Msk);
}




/*@}*/ /* end of group USCI_UART_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group USCI_UART_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/

