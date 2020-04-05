/**************************************************************************//**
 * @file     uart.c
 * @version  V3.00
 * $Revision: 4 $
 * $Date: 16/03/04 9:26a $
 * @brief     UART driver source file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include "NUC100Series.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup UART_Driver UART Driver
  @{
*/

/** @addtogroup UART_EXPORTED_FUNCTIONS UART Exported Functions
  @{
*/

/**
 *    @brief        Clear UART specified interrupt flag
 *
 *    @param[in]    uart                The pointer of the specified UART module.
 *    @param[in]    u32InterruptFlag    The specified interrupt of UART module.
 *                                      - UART_ISR_LIN_INT_Msk     : LIN bus interrupt
 *                                      - UART_ISR_BUF_ERR_INT_Msk : Buffer Error interrupt
 *                                      - UART_ISR_MODEM_INT_Msk   : Modem interrupt
 *                                      - UART_ISR_RLS_INT_Msk     : Rx Line status interrupt
 *
 *    @return       None
 *
 *    @details      The function is used to clear UART specified interrupt flag.
 */
void UART_ClearIntFlag(UART_T* uart , uint32_t u32InterruptFlag)
{

    if(u32InterruptFlag & UART_ISR_RLS_INT_Msk)   /* clear Receive Line Status Interrupt */
    {
        uart->FSR = UART_FSR_BIF_Msk | UART_FSR_FEF_Msk | UART_FSR_PEF_Msk;
        uart->FSR = UART_FSR_RS485_ADD_DETF_Msk;
    }

    if(u32InterruptFlag & UART_ISR_MODEM_INT_Msk)  /* clear Modem Interrupt */
        uart->MSR |= UART_MSR_DCTSF_Msk;

    if(u32InterruptFlag & UART_ISR_BUF_ERR_INT_Msk)   /* clear Buffer Error Interrupt */
    {
        uart->FSR = UART_FSR_RX_OVER_IF_Msk | UART_FSR_TX_OVER_IF_Msk;
    }

    if(u32InterruptFlag & UART_ISR_LIN_INT_Msk)   /* clear LIN break Interrupt */
    {
        uart->ISR = UART_ISR_LIN_IF_Msk;
        uart->LIN_SR = UART_LIN_SR_BIT_ERR_F_Msk   | UART_LIN_SR_LINS_BKDET_F_Msk  |
                       UART_LIN_SR_LINS_SYNC_F_Msk | UART_LIN_SR_LINS_IDPERR_F_Msk |
                       UART_LIN_SR_LINS_HERR_F_Msk | UART_LIN_SR_LINS_HDET_F_Msk ;
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
void UART_Close(UART_T* uart)
{
    uart->IER = 0;
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
void UART_DisableFlowCtrl(UART_T* uart)
{
    uart->IER &= ~(UART_IER_AUTO_RTS_EN_Msk | UART_IER_AUTO_CTS_EN_Msk);
}


/**
 *    @brief        Disable UART specified interrupt
 *
 *    @param[in]    uart                The pointer of the specified UART module.
 *    @param[in]    u32InterruptFlag    The specified interrupt of UART module.
 *                                      - UART_IER_LIN_IEN_Msk        : LIN bus interrupt
 *                                      - UART_IER_WAKE_EN_Msk        : Wakeup interrupt
 *                                      - UART_IER_BUF_ERR_IEN_Msk    : Buffer Error interrupt
 *                                      - UART_IER_RTO_IEN_Msk        : Rx time-out interrupt
 *                                      - UART_IER_MODEM_IEN_Msk      : Modem interrupt
 *                                      - UART_IER_RLS_IEN_Msk        : Rx Line status interrupt
 *                                      - UART_IER_THRE_IEN_Msk       : Tx empty interrupt
 *                                      - UART_IER_RDA_IEN_Msk        : Rx ready interrupt
 *
 *    @return       None
 *
 *    @details      The function is used to disable UART specified interrupt and disable NVIC UART IRQ.
 */
void UART_DisableInt(UART_T*  uart, uint32_t u32InterruptFlag)
{
    /* Disable UART specified interrupt */
    UART_DISABLE_INT(uart, u32InterruptFlag);

    /* Disable NVIC UART IRQ */
    if(uart == UART0)
        NVIC_DisableIRQ(UART02_IRQn);
    else if(uart == UART1)
        NVIC_DisableIRQ(UART1_IRQn);
    else
        NVIC_DisableIRQ(UART02_IRQn);
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
void UART_EnableFlowCtrl(UART_T* uart)
{
    /* Set RTS pin output is low level active */
    uart->MCR |= UART_MCR_LEV_RTS_Msk;

    /* Set CTS pin input is low level active */
    uart->MSR |= UART_MSR_LEV_CTS_Msk;

    /* Set RTS and CTS auto flow control enable */
    uart->IER |= UART_IER_AUTO_RTS_EN_Msk | UART_IER_AUTO_CTS_EN_Msk;
}


/**
 *    @brief        Enable UART specified interrupt
 *
 *    @param[in]    uart                The pointer of the specified UART module.
 *    @param[in]    u32InterruptFlag    The specified interrupt of UART module:
 *                                      - UART_IER_LIN_IEN_Msk        : LIN bus interrupt
 *                                      - UART_IER_WAKE_EN_Msk        : Wakeup interrupt
 *                                      - UART_IER_BUF_ERR_IEN_Msk    : Buffer Error interrupt
 *                                      - UART_IER_RTO_IEN_Msk        : Rx time-out interrupt
 *                                      - UART_IER_MODEM_IEN_Msk      : Modem interrupt
 *                                      - UART_IER_RLS_IEN_Msk        : Rx Line status interrupt
 *                                      - UART_IER_THRE_IEN_Msk       : Tx empty interrupt
 *                                      - UART_IER_RDA_IEN_Msk        : Rx ready interrupt
 *
 *    @return       None
 *
 *    @details      The function is used to enable UART specified interrupt and enable NVIC UART IRQ.
 */
void UART_EnableInt(UART_T*  uart, uint32_t u32InterruptFlag)
{

    /* Enable UART specified interrupt */
    UART_ENABLE_INT(uart, u32InterruptFlag);

    /* Enable NVIC UART IRQ */
    if(uart == UART0)
        NVIC_EnableIRQ(UART02_IRQn);
    else if(uart == UART1)
        NVIC_EnableIRQ(UART1_IRQn);
    else
        NVIC_EnableIRQ(UART02_IRQn);

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
void UART_Open(UART_T* uart, uint32_t u32baudrate)
{
    uint8_t u8UartClkSrcSel, u8UartClkDivNum;
    uint32_t u32ClkTbl[4] = {__HXT, 0, 0, __HIRC};
    uint32_t u32Baud_Div = 0;

    /* Get UART clock source selection */
    u8UartClkSrcSel = (CLK->CLKSEL1 & CLK_CLKSEL1_UART_S_Msk) >> CLK_CLKSEL1_UART_S_Pos;

    /* Get UART clock divider number */
    u8UartClkDivNum = (CLK->CLKDIV & CLK_CLKDIV_UART_N_Msk) >> CLK_CLKDIV_UART_N_Pos;

    /* Select UART function */
    uart->FUN_SEL = UART_FUNC_SEL_UART;

    /* Set UART line configuration */
    uart->LCR = UART_WORD_LEN_8 | UART_PARITY_NONE | UART_STOP_BIT_1;

    /* Set UART Rx and RTS trigger level */
    uart->FCR &= ~(UART_FCR_RFITL_Msk | UART_FCR_RTS_TRI_LEV_Msk);

    /* Get PLL clock frequency if UART clock source selection is PLL */
    if(u8UartClkSrcSel == 1)
        u32ClkTbl[u8UartClkSrcSel] = CLK_GetPLLClockFreq();

    /* Set UART baud rate */
    if(u32baudrate != 0)
    {
        u32Baud_Div = UART_BAUD_MODE2_DIVIDER((u32ClkTbl[u8UartClkSrcSel]) / (u8UartClkDivNum + 1), u32baudrate);

        if(u32Baud_Div > 0xFFFF)
            uart->BAUD = (UART_BAUD_MODE0 | UART_BAUD_MODE0_DIVIDER((u32ClkTbl[u8UartClkSrcSel]) / (u8UartClkDivNum + 1), u32baudrate));
        else
            uart->BAUD = (UART_BAUD_MODE2 | u32Baud_Div);
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
 *    @details       The function is used to read Rx data from RX FIFO and the data will be stored in pu8RxBuf.
 */
uint32_t UART_Read(UART_T* uart, uint8_t *pu8RxBuf, uint32_t u32ReadBytes)
{
    uint32_t  u32Count, u32delayno;

    for(u32Count = 0; u32Count < u32ReadBytes; u32Count++)
    {
        u32delayno = 0;

        while(uart->FSR & UART_FSR_RX_EMPTY_Msk)   /* Check RX empty => failed */
        {
            u32delayno++;
            if(u32delayno >= 0x40000000)
                return FALSE;
        }
        pu8RxBuf[u32Count] = uart->RBR;    /* Get Data from UART RX  */
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
 *                                  - UART_WORD_LEN_5
 *                                  - UART_WORD_LEN_6
 *                                  - UART_WORD_LEN_7
 *                                  - UART_WORD_LEN_8
 *    @param[in]    u32parity       The parity setting (none/odd/even/mark/space) of UART module.
 *                                  - UART_PARITY_NONE
 *                                  - UART_PARITY_ODD
 *                                  - UART_PARITY_EVEN
 *                                  - UART_PARITY_MARK
 *                                  - UART_PARITY_SPACE
 *    @param[in]    u32stop_bits    The stop bit length (1/1.5/2 bit) of UART module.
 *                                  - UART_STOP_BIT_1
 *                                  - UART_STOP_BIT_1_5
 *                                  - UART_STOP_BIT_2
 *
 *    @return       None
 *
 *    @details      This function use to config UART line setting.

 */
void UART_SetLine_Config(UART_T* uart, uint32_t u32baudrate, uint32_t u32data_width, uint32_t u32parity, uint32_t  u32stop_bits)
{
    uint8_t u8UartClkSrcSel, u8UartClkDivNum;
    uint32_t u32ClkTbl[4] = {__HXT, 0, 0, __HIRC};
    uint32_t u32Baud_Div = 0;

    /* Get UART clock source selection */
    u8UartClkSrcSel = (CLK->CLKSEL1 & CLK_CLKSEL1_UART_S_Msk) >> CLK_CLKSEL1_UART_S_Pos;

    /* Get UART clock divider number */
    u8UartClkDivNum = (CLK->CLKDIV & CLK_CLKDIV_UART_N_Msk) >> CLK_CLKDIV_UART_N_Pos;

    /* Get PLL clock frequency if UART clock source selection is PLL */
    if(u8UartClkSrcSel == 1)
        u32ClkTbl[u8UartClkSrcSel] = CLK_GetPLLClockFreq();

    /* Set UART baud rate */
    if(u32baudrate != 0)
    {
        u32Baud_Div = UART_BAUD_MODE2_DIVIDER((u32ClkTbl[u8UartClkSrcSel]) / (u8UartClkDivNum + 1), u32baudrate);

        if(u32Baud_Div > 0xFFFF)
            uart->BAUD = (UART_BAUD_MODE0 | UART_BAUD_MODE0_DIVIDER((u32ClkTbl[u8UartClkSrcSel]) / (u8UartClkDivNum + 1), u32baudrate));
        else
            uart->BAUD = (UART_BAUD_MODE2 | u32Baud_Div);
    }

    /* Set UART line configuration */
    uart->LCR = u32data_width | u32parity | u32stop_bits;
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
void UART_SetTimeoutCnt(UART_T* uart, uint32_t u32TOC)
{
    /* Set time-out interrupt comparator */
    uart->TOR = (uart->TOR & ~UART_TOR_TOIC_Msk) | (u32TOC);

    /* Set time-out counter enable */
    uart->IER |= UART_IER_TIME_OUT_EN_Msk;
}


/**
 *    @brief        Select and configure IrDA function
 *
 *    @param[in]    uart            The pointer of the specified UART module.
 *    @param[in]    u32Buadrate     The baudrate of UART module.
 *    @param[in]    u32Direction    The direction(transmit:1/receive:0) of UART module in IrDA mode:
 *                                  - UART_IRCR_TX_SELECT
 *                                  - UART_IRCR_RX_SELECT
 *
 *    @return       None
  *
 *    @details      The function is used to configure IrDA relative settings. It consists of TX or RX mode and baudrate.
 */
void UART_SelectIrDAMode(UART_T* uart, uint32_t u32Buadrate, uint32_t u32Direction)
{
    uint8_t u8UartClkSrcSel, u8UartClkDivNum;
    uint32_t u32ClkTbl[4] = {__HXT, 0, 0, __HIRC};
    uint32_t u32Baud_Div;

    /* Select IrDA function mode */
    uart->FUN_SEL = UART_FUNC_SEL_IrDA;

    /* Get UART clock source selection */
    u8UartClkSrcSel = (CLK->CLKSEL1 & CLK_CLKSEL1_UART_S_Msk) >> CLK_CLKSEL1_UART_S_Pos;

    /* Get UART clock divider number */
    u8UartClkDivNum = (CLK->CLKDIV & CLK_CLKDIV_UART_N_Msk) >> CLK_CLKDIV_UART_N_Pos;

    /* Get PLL clock frequency if UART clock source selection is PLL */
    if(u8UartClkSrcSel == 1)
        u32ClkTbl[u8UartClkSrcSel] = CLK_GetPLLClockFreq();

    /* Set UART IrDA baud rate in mode 0 */
    if(u32Buadrate != 0)
    {
        u32Baud_Div = UART_BAUD_MODE0_DIVIDER((u32ClkTbl[u8UartClkSrcSel]) / (u8UartClkDivNum + 1), u32Buadrate);

        if(u32Baud_Div < 0xFFFF)
            uart->BAUD = (UART_BAUD_MODE0 | u32Baud_Div);
    }

    /* Configure IrDA relative settings */
    if(u32Direction == UART_IRCR_RX_SELECT)
    {
        uart->IRCR |= UART_IRCR_INV_RX_Msk;     //Rx signal is inverse
        uart->IRCR &= ~UART_IRCR_TX_SELECT_Msk;
    }
    else
    {
        uart->IRCR &= ~UART_IRCR_INV_TX_Msk;    //Tx signal is not inverse
        uart->IRCR |= UART_IRCR_TX_SELECT_Msk;
    }
}


/**
 *    @brief        Select and configure RS485 function
 *
 *    @param[in]    uart        The pointer of the specified UART module.
 *    @param[in]    u32Mode     The operation mode(NMM/AUD/AAD).
 *                              - UART_ALT_CSR_RS485_NMM_Msk
 *                              - UART_ALT_CSR_RS485_AUD_Msk
 *                              - UART_ALT_CSR_RS485_AAD_Msk
 *    @param[in]    u32Addr     The RS485 address.
 *
 *    @return       None
 *
 *    @details      The function is used to set RS485 relative setting.
 */
void UART_SelectRS485Mode(UART_T* uart, uint32_t u32Mode, uint32_t u32Addr)
{
    /* Select UART RS485 function mode */
    uart->FUN_SEL = UART_FUNC_SEL_RS485;

    /* Set RS585 configuration */
    uart->ALT_CSR &= ~(UART_ALT_CSR_RS485_NMM_Msk | UART_ALT_CSR_RS485_AUD_Msk | UART_ALT_CSR_RS485_AAD_Msk | UART_ALT_CSR_ADDR_MATCH_Msk);
    uart->ALT_CSR |= (u32Mode | (u32Addr << UART_ALT_CSR_ADDR_MATCH_Pos));
}


/**
 *    @brief        Select and configure LIN function
 *
 *    @param[in]    uart            The pointer of the specified UART module.
 *    @param[in]    u32Mode         The LIN direction :
 *                                  - UART_ALT_CSR_LIN_TX_EN_Msk
 *                                  - UART_ALT_CSR_LIN_RX_EN_Msk
 *                                  - (UART_ALT_CSR_LIN_TX_EN_Msk|UART_ALT_CSR_LIN_RX_EN_Msk)
 *    @param[in]    u32BreakLength  The breakfield length.
 *
 *    @return       None
 *
 *    @details      The function is used to set LIN relative setting.
 */
void UART_SelectLINMode(UART_T* uart, uint32_t u32Mode, uint32_t u32BreakLength)
{
    /* Select LIN function mode */
    uart->FUN_SEL = UART_FUNC_SEL_LIN;

    /* Select LIN function setting : Tx enable, Rx enable and break field length */
    uart->ALT_CSR &= ~(UART_ALT_CSR_LIN_TX_EN_Msk | UART_ALT_CSR_LIN_RX_EN_Msk | UART_ALT_CSR_UA_LIN_BKFL_Msk);
    uart->ALT_CSR |= (u32Mode | (u32BreakLength << UART_ALT_CSR_UA_LIN_BKFL_Pos));
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
uint32_t UART_Write(UART_T* uart, uint8_t *pu8TxBuf, uint32_t u32WriteBytes)
{
    uint32_t  u32Count, u32delayno;

    for(u32Count = 0; u32Count != u32WriteBytes; u32Count++)
    {
        u32delayno = 0;
        while((uart->FSR & UART_FSR_TE_FLAG_Msk) == 0)   /* Wait Tx empty and Time-out manner */
        {
            u32delayno++;
            if(u32delayno >= 0x40000000)
                return FALSE;
        }
        uart->THR = pu8TxBuf[u32Count];    /* Send UART Data from buffer */
    }

    return u32Count;

}


/*@}*/ /* end of group UART_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group UART_Driver */

/*@}*/ /* end of group Device_Driver */

/*** (C) COPYRIGHT 2012 Nuvoton Technology Corp. ***/



