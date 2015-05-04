/*
 * File      : interrupt.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2015, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-04-14     ArdaFu      first version
 */
 
#include "asm9260t.h"
#include "rtthread.h"
#include "uart.h"

void Hw_UartDisable(HW_USART_TypeDef* uartBase)
{
    uartBase->INTR[R_CLR] = ASM_UART_INTR_RXIEN | ASM_UART_INTR_TXIEN | ASM_UART_INTR_RTIS;
    uartBase->CTRL2[R_CLR] = ASM_UART_CTRL2_TXE | ASM_UART_CTRL2_RXE;
}

void Hw_UartEnable(HW_USART_TypeDef* uartBase)
{
    uartBase->CTRL2[R_CLR] = 0x0000C000UL; //clear CTSEN and RTSEN
    uartBase->CTRL2[R_SET] = ASM_UART_CTRL2_TXE | ASM_UART_CTRL2_RXE | ASM_UART_CTRL2_USARTEN;
    uartBase->INTR[R_SET] = ASM_UART_INTR_RXIEN | ASM_UART_INTR_RTIEN;
}

void Hw_UartReset(HW_USART_TypeDef* uartBase)
{
    uartBase->CTRL0[R_CLR] = ASM_UART_CTRL0_SFTRST | ASM_UART_CTRL0_CLKGATE | ASM_UART_CTRL0_RXTO_ENABLE;
    uartBase->CTRL0[R_SET] = ASM_UART_CTRL0_SFTRST | ASM_UART_CTRL0_CLKGATE | ASM_UART_CTRL0_RXTO_ENABLE;
}

void Hw_UartConfig(HW_USART_TypeDef* uartBase,int baudRate, int dataBits, int stopBits,int parity)
{
    rt_uint32_t mode = ASM_UART_LINECTRL_FEN;

    switch (dataBits)
    {
    case 8:
        mode |= ASM_UART_LINECTRL_WLEN8;
        break;
    case 7:
        mode |= ASM_UART_LINECTRL_WLEN7;
        break;
    case 6:
        mode |= ASM_UART_LINECTRL_WLEN6;
        break;
    case 5:
        mode |= ASM_UART_LINECTRL_WLEN5;
        break;
    default:
        mode |= ASM_UART_LINECTRL_WLEN8;
        break;
    }

    switch (stopBits)
    {
    case 2:
        mode |= ASM_UART_LINECTRL_STP2;
        break;
    case 1:
    default:
        break;
    }

    switch (parity)
    {
    case 1:
        mode |= ASM_UART_LINECTRL_PEN;
        break;
    case 2:
        mode |= ASM_UART_LINECTRL_PEN | ASM_UART_LINECTRL_EPS;
        break;
    case 0:
    default:
        break;
    }
    //16bit nBaudDivint
    mode |= (((12000000 <<2 ) / baudRate) & UART_BAUD_DIVINT_MASK) << 10;
    //6bit nNaudDivfrac
    mode |= (((12000000 <<2 ) / baudRate) & UART_BAUD_DIVFRAC_MASK) << 8;


    uartBase->LINECTRL[R_VAL] = mode;
}

void Hw_UartInit(int index)
{
    // uart0 = bit11, uart9 = bit20
    int ctrl_bit = index + 11;
    outl(1UL<<ctrl_bit,REG_SET(HW_AHBCLKCTRL0));    //UART4 ENABLE bit15
    outl(0x1, HW_UART0CLKDIV + index*4);            //UART4 div 2
    outl(1UL<<ctrl_bit,REG_CLR(HW_AHBCLKCTRL0));    //UART4 clk gate
    outl(1UL<<ctrl_bit,REG_SET(HW_AHBCLKCTRL0));    //UART4 clk gate
    outl(1UL<<ctrl_bit,REG_CLR(HW_PRESETCTRL0));    //UART4 reset
    outl(1UL<<ctrl_bit,REG_SET(HW_PRESETCTRL0));    //UART4 reset
}
