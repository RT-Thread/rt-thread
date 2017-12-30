/**************************************************************************//**
 * @file     uart.c
 * @version  V1.00
 * $Revision: 14 $
 * $Date: 15/11/26 10:47a $
 * @brief    NUC472/NUC442 UART driver source file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include "NUC472_442.h"

/*---------------------------------------------------------------------------------------------------------*/
/* Includes of local headers                                                                               */
/*---------------------------------------------------------------------------------------------------------*/


/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_UART_Driver UART Driver
  @{
*/


/** @addtogroup NUC472_442_UART_EXPORTED_FUNCTIONS UART Exported Functions
  @{
*/


/**
 *    @brief  The function is used to clear UART specified interrupt flag.
 *
 *    @param[in]  uart                The base address of UART module.
 *    @param[in]  u32InterruptFlag    The specified interrupt of UART module..
 *
 *    @return None
 */
void UART_ClearIntFlag(UART_T* uart , uint32_t u32InterruptFlag)
{
    if(u32InterruptFlag & UART_INTSTS_RLSINT_Msk) { /* clear Receive Line Status Interrupt */
        uart->FIFOSTS |= UART_FIFOSTS_BIF_Msk | UART_FIFOSTS_FEF_Msk | UART_FIFOSTS_PEF_Msk;
        uart->FIFOSTS |= UART_FIFOSTS_ADDRDETF_Msk;
    }

    if(u32InterruptFlag & UART_INTSTS_MODEMINT_Msk)  /* clear Modem Interrupt */
        uart->MODEMSTS |= UART_MODEMSTS_CTSDETF_Msk;

    if(u32InterruptFlag & UART_INTSTS_BUFERRINT_Msk) { /* clear Buffer Error Interrupt */
        uart->FIFOSTS |= UART_FIFOSTS_RXOVIF_Msk | UART_FIFOSTS_TXOVIF_Msk;
    }

    if(u32InterruptFlag & UART_INTSTS_RXTOINT_Msk)  /* clear Modem Interrupt */
        uart->INTSTS |= UART_INTSTS_RXTOIF_Msk;

}


/**
 *  @brief  The function is used to disable UART.
 *
 *  @param[in]  uart        The base address of UART module.
 *
 *  @return None
 */
void UART_Close(UART_T* uart)
{
    uart->INTEN = 0;
}


/**
 *  @brief The function is used to disable UART auto flow control.
 *
 *  @param[in] uart        The base address of UART module.
 *
 *  @return None
 */
void UART_DisableFlowCtrl(UART_T* uart)
{
    uart->INTEN &= ~(UART_INTEN_ATORTSEN_Msk | UART_INTEN_ATOCTSEN_Msk);
}


/**
 *    @brief    The function is used to disable UART specified interrupt and disable NVIC UART IRQ.
 *
 *    @param[in]    uart                The base address of UART module.
 *    @param[in]    u32InterruptFlag    The specified interrupt of UART module.
 *                                  - \ref UART_INTEN_TOCNTEN_Msk    : Rx Time Out interrupt
 *                                  - \ref UART_INTEN_WKCTSIEN_Msk   : Wakeup interrupt
 *                                  - \ref UART_INTEN_BUFERRIEN_Msk  : Buffer Error interrupt
 *                                  - \ref UART_INTEN_RXTOIEN_Msk    : Rx time-out interrupt
 *                                  - \ref UART_INTEN_MODEMIEN_Msk   : Modem interrupt
 *                                  - \ref UART_INTEN_RLSIEN_Msk     : Rx Line status interrupt
 *                                  - \ref UART_INTEN_THREIEN_Msk    : Tx empty interrupt
 *                                  - \ref UART_INTEN_RDAIEN_Msk     : Rx ready interrupt
 *
 *    @return    None
 */
void UART_DisableInt(UART_T*  uart, uint32_t u32InterruptFlag )
{
    uart->INTEN &= ~ u32InterruptFlag;
}



/**
 *    @brief    The function is used to Enable UART auto flow control.
 *
 *    @param[in]    uart    The base address of UART module.
 *
 *    @return   None
 */
void UART_EnableFlowCtrl(UART_T* uart )
{
    uart->MODEM    |= UART_MODEM_RTSACTLV_Msk;
    uart->MODEM    &= ~UART_MODEM_RTS_Msk;
    uart->MODEMSTS |= UART_MODEMSTS_CTSACTLV_Msk;
    uart->INTEN    |= UART_INTEN_ATORTSEN_Msk | UART_INTEN_ATOCTSEN_Msk;
}


/**
 *    @brief    The function is used to enable UART specified interrupt and disable NVIC UART IRQ.
 *
 *    @param[in]    uart                The base address of UART module.
 *    @param[in]    u32InterruptFlag    The specified interrupt of UART module:
 *                                  - \ref UART_INTEN_TOCNTEN_Msk    : Rx Time Out interrupt
 *                                  - \ref UART_INTEN_WKCTSIEN_Msk   : Wakeup interrupt
 *                                  - \ref UART_INTEN_BUFERRIEN_Msk  : Buffer Error interrupt
 *                                  - \ref UART_INTEN_RXTOIEN_Msk    : Rx time-out interrupt
 *                                  - \ref UART_INTEN_MODEMIEN_Msk   : Modem interrupt
 *                                  - \ref UART_INTEN_RLSIEN_Msk     : Rx Line status interrupt
 *                                  - \ref UART_INTEN_THREIEN_Msk    : Tx empty interrupt
 *                                  - \ref UART_INTEN_RDAIEN_Msk     : Rx ready interrupt
 *
 *    @return   None
 */
void UART_EnableInt(UART_T*  uart, uint32_t u32InterruptFlag )
{
    uart->INTEN |= u32InterruptFlag;
}


/**
 *    @brief    This function use to enable UART function and set baud-rate.
 *
 *    @param[in]    uart           The base address of UART module.
 *    @param[in]    u32baudrate    The baudrate of UART module.
 *
 *    @return   None
 */
void UART_Open(UART_T* uart, uint32_t u32baudrate)
{
    uint8_t u8UartClkSrcSel;
    uint32_t u32ClkTbl[4] = {__HXT, 0, __HIRC, __HIRC};
    uint32_t u32Clk;
    uint32_t u32Baud_Div;

    u32ClkTbl[1] = CLK_GetPLLClockFreq();

    u8UartClkSrcSel = (CLK->CLKSEL1 & CLK_CLKSEL1_UARTSEL_Msk) >> CLK_CLKSEL1_UARTSEL_Pos;

    uart->FUNCSEL = UART_FUNCSEL_UART;
    uart->LINE = UART_WORD_LEN_8 | UART_PARITY_NONE | UART_STOP_BIT_1;
    uart->FIFO = UART_FIFO_RFITL_1BYTE | UART_FIFO_RTSTRGLV_1BYTE;

    u32Clk = (u32ClkTbl[u8UartClkSrcSel]) / (((CLK->CLKDIV0 & CLK_CLKDIV0_UARTDIV_Msk) >> CLK_CLKDIV0_UARTDIV_Pos) + 1);

    if(u32baudrate != 0) {
        u32Baud_Div = UART_BAUD_MODE2_DIVIDER(u32Clk, u32baudrate);

        if(u32Baud_Div > 0xFFFF)
            uart->BAUD = (UART_BAUD_MODE0 | UART_BAUD_MODE0_DIVIDER(u32Clk, u32baudrate));
        else
            uart->BAUD = (UART_BAUD_MODE2 | u32Baud_Div);
    }
}


/**
 *    @brief    The function is used to read Rx data from RX FIFO and the data will be stored in pu8RxBuf.
 *
 *    @param[in]    uart            The base address of UART module.
 *    @param[out]    pu8RxBuf        The buffer to receive the data of receive FIFO.
 *    @param[in]    u32ReadBytes    The the read bytes number of data.
 *
 *    @return   u32Count: Receive byte count
 *
 */
uint32_t UART_Read(UART_T* uart, uint8_t *pu8RxBuf, uint32_t u32ReadBytes)
{
    uint32_t  u32Count;

    for(u32Count=0; u32Count < u32ReadBytes; u32Count++) {
        if(uart->FIFOSTS & UART_FIFOSTS_RXEMPTY_Msk) { /* Check RX empty => failed */
            return u32Count;
        }
        pu8RxBuf[u32Count] = uart->DAT;    /* Get Data from UART RX  */
    }

    return u32Count;
}


/**
 *    @brief    This function use to config UART line setting.
 *
 *    @param[in]    uart            The base address of UART module.
 *    @param[in]    u32baudrate     The register value of baudrate of UART module.
 *                                  if u32baudrate = 0, UART baudrate will not change.
 *    @param[in]    u32data_width   The data length of UART module. [ \ref UART_WORD_LEN_5 / \ref UART_WORD_LEN_6 / \ref UART_WORD_LEN_7 / \ref UART_WORD_LEN_8]
 *    @param[in]    u32parity       The parity setting (odd/even/none) of UART module. [ \ref UART_PARITY_NONE / \ref UART_PARITY_ODD /
 *                                                                                       \ref UART_PARITY_EVEN / \ref UART_PARITY_MARK / \ref UART_PARITY_SPACE]
 *    @param[in]    u32stop_bits    The stop bit length (1/1.5/2 bit) of UART module. [ \ref UART_STOP_BIT_1 / \ref UART_STOP_BIT_1_5 / \ref UART_STOP_BIT_2]
 *
 *    @return   None
 */
void UART_SetLine_Config(UART_T* uart, uint32_t u32baudrate, uint32_t u32data_width, uint32_t u32parity, uint32_t  u32stop_bits)
{
    uint8_t u8UartClkSrcSel;
    uint32_t u32ClkTbl[4] = {__HXT, 0, __HIRC, __HIRC};
    uint32_t u32Clk;
    uint32_t u32Baud_Div = 0;

    u32ClkTbl[1] = CLK_GetPLLClockFreq();

    u8UartClkSrcSel = (CLK->CLKSEL1 & CLK_CLKSEL1_UARTSEL_Msk) >> CLK_CLKSEL1_UARTSEL_Pos;

    u32Clk = (u32ClkTbl[u8UartClkSrcSel]) / (((CLK->CLKDIV0 & CLK_CLKDIV0_UARTDIV_Msk) >> CLK_CLKDIV0_UARTDIV_Pos) + 1);

    if(u32baudrate != 0) {
        u32Baud_Div = UART_BAUD_MODE2_DIVIDER(u32Clk, u32baudrate);

        if(u32Baud_Div > 0xFFFF)
            uart->BAUD = (UART_BAUD_MODE0 | UART_BAUD_MODE0_DIVIDER(u32Clk, u32baudrate));
        else
            uart->BAUD = (UART_BAUD_MODE2 | u32Baud_Div);
    }

    uart->LINE = u32data_width | u32parity | u32stop_bits;
}


/**
 *    @brief    This function use to set Rx timeout count.
 *
 *    @param[in]    uart    The base address of UART module.
 *    @param[in]    u32TOC  Rx timeout counter.
 *
 *    @return   None
 */
void UART_SetTimeoutCnt(UART_T* uart, uint32_t u32TOC)
{
    uart->TOUT = (uart->TOUT & ~UART_TOUT_TOIC_Msk)| (u32TOC);
    uart->INTEN |= UART_INTEN_TOCNTEN_Msk;
}


/**
 *    @brief    The function is used to configure IrDA relative settings. It consists of TX or RX mode and baudrate.
 *
 *    @param[in]    uart            The base address of UART module.
 *    @param[in]    u32Buadrate     The baudrate of UART module.
 *    @param[in]    u32Direction    The direction(transmit:1/receive:0) of UART module in IrDA mode.
 *
 *    @return   None
 */
void UART_SelectIrDAMode(UART_T* uart, uint32_t u32Buadrate, uint32_t u32Direction)
{
    uint8_t u8UartClkSrcSel;
    uint32_t u32ClkTbl[4] = {__HXT, 0, __HIRC, __HIRC};
    uint32_t u32Clk;

    u32ClkTbl[1] = CLK_GetPLLClockFreq();

    u8UartClkSrcSel = (CLK->CLKSEL1 & CLK_CLKSEL1_UARTSEL_Msk) >> CLK_CLKSEL1_UARTSEL_Pos;

    u32Clk = (u32ClkTbl[u8UartClkSrcSel]) / (((CLK->CLKDIV0 & CLK_CLKDIV0_UARTDIV_Msk) >> CLK_CLKDIV0_UARTDIV_Pos) + 1);

    uart->BAUD = UART_BAUD_MODE0 | UART_BAUD_MODE0_DIVIDER(u32Clk, u32Buadrate);

    uart->IRDA    &= ~UART_IRDA_TXINV_Msk;
    uart->IRDA    |=  UART_IRDA_RXINV_Msk;
    uart->IRDA     =  u32Direction ? uart->IRDA | UART_IRDA_TXEN_Msk : uart->IRDA &~ UART_IRDA_TXEN_Msk;
    uart->FUNCSEL  =  (0x2 << UART_FUNCSEL_FUNCSEL_Pos);
}


/**
 *    @brief    The function is used to set RS485 relative setting.
 *
 *    @param[in]    uart        The base address of UART module.
 *    @param[in]    u32Mode     The operation mode( \ref UART_ALTCTL_RS485NMM_Msk / \ref UART_ALTCTL_RS485AUD_Msk / \ref UART_ALTCTL_RS485AAD_Msk).
 *    @param[in]    u32Addr     The RS485 address.
 *
 *    @return   None
 */
void UART_SelectRS485Mode(UART_T* uart, uint32_t u32Mode, uint32_t u32Addr)
{
    uart->FUNCSEL = UART_FUNCSEL_RS485;
    uart->ALTCTL  = 0;
    uart->ALTCTL |= u32Mode | (u32Addr << UART_ALTCTL_ADDRMV_Pos);
}


/**
 *    @brief    The function is to write data into TX buffer to transmit data by UART.
 *
 *    @param[in]    uart            The base address of UART module.
 *    @param[in]    pu8TxBuf        The buffer to send the data to UART transmission FIFO.
 *    @param[in]    u32WriteBytes   The byte number of data.
 *
 *    @return   u32Count: transfer byte count
 */
uint32_t UART_Write(UART_T* uart,uint8_t *pu8TxBuf, uint32_t u32WriteBytes)
{
    uint32_t  u32Count;

    for(u32Count=0; u32Count != u32WriteBytes; u32Count++) {
        if(uart->FIFOSTS & UART_FIFOSTS_TXFULL_Msk) { /* Wait Tx empty and Time-out manner */
            return u32Count;
        }
        uart->DAT = pu8TxBuf[u32Count];    /* Send UART Data from buffer */
    }

    return u32Count;
}


/*@}*/ /* end of group NUC472_442_UART_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_UART_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/


