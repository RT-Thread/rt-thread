/**************************************************************************//**
 * @file     uart.c
 * @brief    UART driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#include <stdio.h>
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup UART_Driver UART Driver
  @{
*/

/** @addtogroup UART_EXPORTED_FUNCTIONS UART Exported Functions
  @{
*/

static void UART_GetSrcClkSetting(UART_T *uart, uint32_t *pu32ClkSrcFreq, uint32_t *pu32ClkDivNum);

/**
  * @brief  This function make UART module be ready to transfer.
  * @param[in]  pu32ClkSrcFreq will return UART source clock frequency(In HZ).
  * @param[in]  pu32ClkSrcFreq will return UART source clock frequency(In HZ).
  * @param[in]  pu32ClkDivNum will return UART source clock divider.
  * @return None.
  * @details
    *           0: HXT
    *           1: SYSCLK1
    *           2: LXT
    *           3: HIRC
    * @note   If u32BusClock = 0, DIVIDER setting will be set to the maximum value.
  */

static void UART_GetSrcClkSetting(UART_T *uart, uint32_t *pu32ClkSrcFreq, uint32_t *pu32ClkDivNum)
{
    uint32_t u32UartClkSrcSel = 0u, u32UartClkDivNum = 0u;
    uint32_t u32SrcClkFreq = 0u;
    uint32_t u32UartPort;

    if (uart == (UART_T *)UART16)
    {
        u32UartPort = 16;
    }
    else
    {
        u32UartPort = ((uint32_t)uart & 0xf0000) >> 16;
    }

    if (u32UartPort < 8)
    {
        u32UartClkSrcSel = ((CLK->CLKSEL2 >> (16 + u32UartPort * 2)) & 0x3ul);

        if (u32UartPort < 4)
        {
            u32UartClkDivNum = ((CLK->CLKDIV1 >> ((u32UartPort + 4) * 4)) & 0xful);
        }
        else
        {
            u32UartClkDivNum = ((CLK->CLKDIV2 >> ((u32UartPort - 4) * 4)) & 0xful);
        }
    }
    else if (u32UartPort <= 16)
    {
        u32UartClkSrcSel = ((CLK->CLKSEL3 >> ((u32UartPort - 8) * 2)) & 0x3ul);

        if (u32UartPort < 12)
        {
            u32UartClkDivNum = ((CLK->CLKDIV2 >> ((u32UartPort - 4) * 4)) & 0xful);
        }
        else
        {
            u32UartClkDivNum = ((CLK->CLKDIV3 >> ((u32UartPort - 12) * 4)) & 0xful);
        }
    }

    /* Get PLL clock frequency if UART clock source selection is PLL */
    switch (u32UartClkSrcSel)
    {
    case 0u:
        u32SrcClkFreq = __HXT;
        break;
    case 1u:
        u32SrcClkFreq = CLK_GetSYSCLK1Freq();   //TODO
        break;
    default:
        u32SrcClkFreq = 0;
        break;
    }

    if (pu32ClkSrcFreq)
        *pu32ClkSrcFreq = u32SrcClkFreq;

    if (pu32ClkDivNum)
        *pu32ClkDivNum = u32UartClkDivNum;
}

/**
 *    @brief        Clear UART specified interrupt flag
 *
 *    @param[in]    uart                The pointer of the specified UART module.
 *    @param[in]    u32InterruptFlag    The specified interrupt of UART module.
 *                                      - \ref UART_INTSTS_WKIF_Msk      : Wake-up interrupt
 *                                      - \ref UART_INTSTS_BUFEINT_Msk : Buffer Error interrupt
 *                                      - \ref UART_INTSTS_MODEMINT_Msk  : Modem Status interrupt
 *                                      - \ref UART_INTSTS_RLSINT_Msk    : Receive Line Status interrupt
 *
 *    @return       None
 *
 *    @details      The function is used to clear UART specified interrupt flag.
 */

void UART_ClearIntFlag(UART_T *uart, uint32_t u32InterruptFlag)
{

    if (u32InterruptFlag & UART_INTSTS_RLSINT_Msk)  /* Clear Receive Line Status Interrupt */
    {
        uart->FIFOSTS = UART_FIFOSTS_BIF_Msk | UART_FIFOSTS_FEF_Msk | UART_FIFOSTS_PEF_Msk;
        uart->FIFOSTS = UART_FIFOSTS_ADDRDETF_Msk;
    }

    if (u32InterruptFlag & UART_INTSTS_MODEMINT_Msk)  /* Clear Modem Status Interrupt */
    {
        uart->MODEMSTS |= UART_MODEMSTS_CTSDETF_Msk;
    }
    else
    {
    }

    if (u32InterruptFlag & UART_INTSTS_BUFEINT_Msk)  /* Clear Buffer Error Interrupt */
    {
        uart->FIFOSTS = UART_FIFOSTS_RXOVIF_Msk | UART_FIFOSTS_TXOVIF_Msk;
    }

    if (u32InterruptFlag & UART_INTSTS_WKINT_Msk)  /* Clear Wake-up Interrupt */
    {
        uart->WKSTS = UART_WKSTS_CTSWKF_Msk  | UART_WKSTS_DATWKF_Msk  |
                      UART_WKSTS_RFRTWKF_Msk | UART_WKSTS_RS485WKF_Msk |
                      UART_WKSTS_TOUTWKF_Msk;
    }

}


/**
 *  @brief      Disable UART interrupt
 *
 *  @param[in]  uart The pointer of the specified UART module.
 *
 *  @return     None
 *
 *  @details    The function is used to disable UART interrupt.
 */
void UART_Close(UART_T *uart)
{
    uart->INTEN = 0ul;
}


/**
 *  @brief      Disable UART auto flow control function
 *
 *  @param[in]  uart The pointer of the specified UART module.
 *
 *  @return     None
 *
 *  @details    The function is used to disable UART auto flow control.
 */
void UART_DisableFlowCtrl(UART_T *uart)
{
    uart->INTEN &= ~(UART_INTEN_ATORTSEN_Msk | UART_INTEN_ATOCTSEN_Msk);
}


/**
 *    @brief        Disable UART specified interrupt
 *
 *    @param[in]    uart                The pointer of the specified UART module.
 *    @param[in]    u32InterruptFlag    The specified interrupt of UART module.
 *                                      - \ref UART_INTEN_WKIEN_Msk      : Wake-up interrupt
 *                                      - \ref UART_INTEN_BUFEIEN_Msk  : Buffer Error interrupt
 *                                      - \ref UART_INTEN_RXTOIEN_Msk    : Rx time-out interrupt
 *                                      - \ref UART_INTEN_MODEMIEN_Msk   : Modem status interrupt
 *                                      - \ref UART_INTEN_RLSIEN_Msk     : Receive Line status interrupt
 *                                      - \ref UART_INTEN_THREIEN_Msk    : Tx empty interrupt
 *                                      - \ref UART_INTEN_RDAIEN_Msk     : Rx ready interrupt *
 *
 *    @return       None
 *
 *    @details      The function is used to disable UART specified interrupt and disable NVIC UART IRQ.
 */
void UART_DisableInt(UART_T  *uart, uint32_t u32InterruptFlag)
{
    /* Disable UART specified interrupt */
    UART_DISABLE_INT(uart, u32InterruptFlag);
}


/**
 *    @brief        Enable UART auto flow control function
 *
 *    @param[in]    uart    The pointer of the specified UART module.
 *
 *    @return       None
 *
 *    @details      The function is used to Enable UART auto flow control.
 */
void UART_EnableFlowCtrl(UART_T *uart)
{
    /* Set RTS pin output is low level active */
    uart->MODEM |= UART_MODEM_RTSACTLV_Msk;

    /* Set CTS pin input is low level active */
    uart->MODEMSTS |= UART_MODEMSTS_CTSACTLV_Msk;

    /* Set RTS and CTS auto flow control enable */
    uart->INTEN |= UART_INTEN_ATORTSEN_Msk | UART_INTEN_ATOCTSEN_Msk;
}


/**
 *    @brief        The function is used to enable UART specified interrupt and enable NVIC UART IRQ.
 *
 *    @param[in]    uart                The pointer of the specified UART module.
 *    @param[in]    u32InterruptFlag    The specified interrupt of UART module:
 *                                      - \ref UART_INTEN_WKIEN_Msk      : Wake-up interrupt
 *                                      - \ref UART_INTEN_BUFEIEN_Msk  : Buffer Error interrupt
 *                                      - \ref UART_INTEN_RXTOIEN_Msk    : Rx time-out interrupt
 *                                      - \ref UART_INTEN_MODEMIEN_Msk   : Modem status interrupt
 *                                      - \ref UART_INTEN_RLSIEN_Msk     : Receive Line status interrupt
 *                                      - \ref UART_INTEN_THREIEN_Msk    : Tx empty interrupt
 *                                      - \ref UART_INTEN_RDAIEN_Msk     : Rx ready interrupt *
 *
 *    @return       None
 *
 *    @details      The function is used to enable UART specified interrupt and enable NVIC UART IRQ.
 */
void UART_EnableInt(UART_T  *uart, uint32_t u32InterruptFlag)
{
    /* Enable UART specified interrupt */
    UART_ENABLE_INT(uart, u32InterruptFlag);
}


/**
 *    @brief        Open and set UART function
 *
 *    @param[in]    uart            The pointer of the specified UART module.
 *    @param[in]    u32baudrate     The baudrate of UART module.
 *
 *    @return       None
 *
 *    @details      This function use to enable UART function and set baud-rate.
 */
void UART_Open(UART_T *uart, uint32_t u32baudrate)
{
    uint32_t u32UartSrcClkFreq = 0ul, u32UartClkDivNum = 0ul;
    uint32_t u32Baud_Div = 0ul;

    /* Select UART function */
    uart->FUNCSEL = UART_FUNCSEL_UART;

    /* Set UART line configuration */
    uart->LINE = UART_WORD_LEN_8 | UART_PARITY_NONE | UART_STOP_BIT_1;

    /* Set UART Rx and RTS trigger level */
    uart->FIFO &= ~(UART_FIFO_RFITL_Msk | UART_FIFO_RTSTRGLV_Msk);

    /* Get Source clock frequency and its divider of curret setting */
    UART_GetSrcClkSetting(uart, &u32UartSrcClkFreq, &u32UartClkDivNum);

    /* Set UART baud rate */
    if (u32baudrate != 0ul)
    {
        u32Baud_Div = UART_BAUD_MODE2_DIVIDER(u32UartSrcClkFreq / (u32UartClkDivNum + 1ul), u32baudrate);

        if (u32Baud_Div > 0xFFFFul)
        {
            uart->BAUD = (UART_BAUD_MODE0 | UART_BAUD_MODE0_DIVIDER(u32UartSrcClkFreq / (u32UartClkDivNum + 1ul), u32baudrate));
        }
        else
        {
            uart->BAUD = (UART_BAUD_MODE2 | u32Baud_Div);
        }
    }
}


/**
 *    @brief        Read UART data
 *
 *    @param[in]    uart            The pointer of the specified UART module.
 *    @param[in]    pu8RxBuf        The buffer to receive the data of receive FIFO.
 *    @param[in]    u32ReadBytes    The the read bytes number of data.
 *
 *    @return       u32Count Receive byte count
 *
 *    @details      The function is used to read Rx data from RX FIFO and the data will be stored in pu8RxBuf.
 */
uint32_t UART_Read(UART_T *uart, uint8_t pu8RxBuf[], uint32_t u32ReadBytes)
{
    uint32_t  u32Count, u32delayno;
    uint32_t  u32Exit = 0ul;

    for (u32Count = 0ul; u32Count < u32ReadBytes; u32Count++)
    {
        u32delayno = 0ul;

        while (uart->FIFOSTS & UART_FIFOSTS_RXEMPTY_Msk)  /* Check RX empty => failed */
        {
            u32delayno++;
            if (u32delayno >= 0x40000000ul)
            {
                u32Exit = 1ul;
                break;
            }
            else
            {
            }
        }

        if (u32Exit == 1ul)
        {
            break;
        }
        else
        {
            pu8RxBuf[u32Count] = (uint8_t)uart->DAT; /* Get Data from UART RX  */
        }
    }

    return u32Count;

}


/**
 *    @brief        Set UART line configuration
 *
 *    @param[in]    uart            The pointer of the specified UART module.
 *    @param[in]    u32baudrate     The register value of baudrate of UART module.
 *                                  If u32baudrate = 0, UART baudrate will not change.
 *    @param[in]    u32data_width   The data length of UART module.
 *                                  - \ref UART_WORD_LEN_5
 *                                  - \ref UART_WORD_LEN_6
 *                                  - \ref UART_WORD_LEN_7
 *                                  - \ref UART_WORD_LEN_8
 *    @param[in]    u32parity       The parity setting (none/odd/even/mark/space) of UART module.
 *                                  - \ref UART_PARITY_NONE
 *                                  - \ref UART_PARITY_ODD
 *                                  - \ref UART_PARITY_EVEN
 *                                  - \ref UART_PARITY_MARK
 *                                  - \ref UART_PARITY_SPACE
 *    @param[in]    u32stop_bits    The stop bit length (1/1.5/2 bit) of UART module.
 *                                  - \ref UART_STOP_BIT_1
 *                                  - \ref UART_STOP_BIT_1_5
 *                                  - \ref UART_STOP_BIT_2
 *
 *    @return       None
 *
 *    @details      This function use to config UART line setting.
 */
void UART_SetLineConfig(UART_T *uart, uint32_t u32baudrate, uint32_t u32data_width, uint32_t u32parity, uint32_t  u32stop_bits)
{
    uint32_t u32UartSrcClkFreq = 0ul, u32UartClkDivNum = 0ul;
    uint32_t u32Baud_Div = 0ul;

    /* Get Source clock frequency and its divider of curret setting */
    UART_GetSrcClkSetting(uart, &u32UartSrcClkFreq, &u32UartClkDivNum);

    /* Set UART baud rate */
    if (u32baudrate != 0ul)
    {
        u32Baud_Div = UART_BAUD_MODE2_DIVIDER(u32UartSrcClkFreq / (u32UartClkDivNum + 1ul), u32baudrate);

        if (u32Baud_Div > 0xFFFFul)
        {
            uart->BAUD = (UART_BAUD_MODE0 | UART_BAUD_MODE0_DIVIDER(u32UartSrcClkFreq / (u32UartClkDivNum + 1ul), u32baudrate));
        }
        else
        {
            uart->BAUD = (UART_BAUD_MODE2 | u32Baud_Div);
        }
    }

    /* Set UART line configuration */
    uart->LINE = u32data_width | u32parity | u32stop_bits;
}


/**
 *    @brief        Set Rx timeout count
 *
 *    @param[in]    uart    The pointer of the specified UART module.
 *    @param[in]    u32TOC  Rx timeout counter.
 *
 *    @return       None
 *
 *    @details      This function use to set Rx timeout count.
 */
void UART_SetTimeoutCnt(UART_T *uart, uint32_t u32TOC)
{
    /* Set time-out interrupt comparator */
    uart->TOUT = (uart->TOUT & ~UART_TOUT_TOIC_Msk) | (u32TOC);

    /* Set time-out counter enable */
    uart->INTEN |= UART_INTEN_TOCNTEN_Msk;
}


/**
 *    @brief        Select and configure IrDA function
 *
 *    @param[in]    uart            The pointer of the specified UART module.
 *    @param[in]    u32Buadrate     The baudrate of UART module.
 *    @param[in]    u32Direction    The direction of UART module in IrDA mode:
 *                                  - \ref UART_IRDA_TXEN
 *                                  - \ref UART_IRDA_RXEN
 *
 *    @return       None
  *
 *    @details      The function is used to configure IrDA relative settings. It consists of TX or RX mode and baudrate.
 */
void UART_SelectIrDAMode(UART_T *uart, uint32_t u32Buadrate, uint32_t u32Direction)
{
    uint32_t u32UartSrcClkFreq = 0ul, u32UartClkDivNum = 0ul;
    uint32_t u32Baud_Div;

    /* Select IrDA function mode */
    uart->FUNCSEL = UART_FUNCSEL_IrDA;

    /* Get Source clock frequency and its divider of curret setting */
    UART_GetSrcClkSetting(uart, &u32UartSrcClkFreq, &u32UartClkDivNum);

    /* Set UART IrDA baud rate in mode 0 */
    if (u32Buadrate != 0ul)
    {
        u32Baud_Div = UART_BAUD_MODE0_DIVIDER(u32UartSrcClkFreq / (u32UartClkDivNum + 1ul), u32Buadrate);

        if (u32Baud_Div < 0xFFFFul)
        {
            uart->BAUD = (UART_BAUD_MODE0 | u32Baud_Div);
        }
        else
        {
        }
    }

    /* Configure IrDA relative settings */
    if (u32Direction == UART_IRDA_RXEN)
    {
        uart->IRDA |= UART_IRDA_RXINV_Msk;     /*Rx signal is inverse*/
        uart->IRDA &= ~UART_IRDA_TXEN_Msk;
    }
    else
    {
        uart->IRDA &= ~UART_IRDA_TXINV_Msk;    /*Tx signal is not inverse*/
        uart->IRDA |= UART_IRDA_TXEN_Msk;
    }

}


/**
 *    @brief        Select and configure RS485 function
 *
 *    @param[in]    uart        The pointer of the specified UART module.
 *    @param[in]    u32Mode     The operation mode(NMM/AUD/AAD).
 *                              - \ref UART_ALTCTL_RS485NMM_Msk
 *                              - \ref UART_ALTCTL_RS485AUD_Msk
 *                              - \ref UART_ALTCTL_RS485AAD_Msk
 *    @param[in]    u32Addr     The RS485 address.
 *
 *    @return       None
 *
 *    @details      The function is used to set RS485 relative setting.
 */
void UART_SelectRS485Mode(UART_T *uart, uint32_t u32Mode, uint32_t u32Addr)
{
    /* Select UART RS485 function mode */
    uart->FUNCSEL = UART_FUNCSEL_RS485;

    /* Set RS585 configuration */
    uart->ALTCTL &= ~(UART_ALTCTL_RS485NMM_Msk | UART_ALTCTL_RS485AUD_Msk | UART_ALTCTL_RS485AAD_Msk | UART_ALTCTL_ADDRMV_Msk);
    uart->ALTCTL |= (u32Mode | (u32Addr << UART_ALTCTL_ADDRMV_Pos));
}


/**
 *    @brief        Write UART data
 *
 *    @param[in]    uart            The pointer of the specified UART module.
 *    @param[in]    pu8TxBuf        The buffer to send the data to UART transmission FIFO.
 *    @param[out]   u32WriteBytes   The byte number of data.
 *
 *    @return       u32Count transfer byte count
 *
 *    @details      The function is to write data into TX buffer to transmit data by UART.
 */
uint32_t UART_Write(UART_T *uart, uint8_t pu8TxBuf[], uint32_t u32WriteBytes)
{
    uint32_t  u32Count, u32delayno;
    uint32_t  u32Exit = 0ul;

    for (u32Count = 0ul; u32Count != u32WriteBytes; u32Count++)
    {
        u32delayno = 0ul;
        while (uart->FIFOSTS & UART_FIFOSTS_TXFULL_Msk)  /* Check Tx Full */
        {
            u32delayno++;
            if (u32delayno >= 0x40000000ul)
            {
                u32Exit = 1ul;
                break;
            }
            else
            {
            }
        }

        if (u32Exit == 1ul)
        {
            break;
        }
        else
        {
            uart->DAT = pu8TxBuf[u32Count];    /* Send UART Data from buffer */
        }
    }

    return u32Count;
}


/*@}*/ /* end of group UART_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group UART_Driver */

/*@}*/ /* end of group Standard_Driver */

