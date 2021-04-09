/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-04-14     ArdaFu      first version
 */
#ifndef __UART_H__
#define __UART_H__

#define R_VAL 0
#define R_SET 1
#define R_CLR 2
#define R_TOG 3

typedef struct
{
    volatile rt_uint32_t CTRL0[4];
    volatile rt_uint32_t CTRL1[4];
    volatile rt_uint32_t CTRL2[4];
    volatile rt_uint32_t LINECTRL[4];
    volatile rt_uint32_t INTR[4];
    volatile rt_uint32_t DATA[4];
    volatile rt_uint32_t STAT[4];
    volatile const rt_uint32_t DEBUG[4];
    volatile rt_uint32_t ILPR[4];
    volatile rt_uint32_t RS485CTRL[4];
    volatile rt_uint32_t RS485ADRMATCH[4];
    volatile rt_uint32_t RS485DLY[4];
    volatile rt_uint32_t AUTOBAUD[4];
    volatile rt_uint32_t CTRL3[4];
    volatile rt_uint32_t ISO7816CTRL[4];
    volatile rt_uint32_t ISO7816ERRCNT[4];
    volatile rt_uint32_t ISO7816STATUS[4];
} HW_USART_TypeDef;

#define USART0  ((HW_USART_TypeDef *)UART0_BASE)
#define USART1  ((HW_USART_TypeDef *)UART1_BASE)
#define USART2  ((HW_USART_TypeDef *)UART2_BASE)
#define USART3  ((HW_USART_TypeDef *)UART3_BASE)
#define USART4  ((HW_USART_TypeDef *)UART4_BASE)
#define USART5  ((HW_USART_TypeDef *)UART5_BASE)
#define USART6  ((HW_USART_TypeDef *)UART6_BASE)
#define USART7  ((HW_USART_TypeDef *)UART7_BASE)
#define USART8  ((HW_USART_TypeDef *)UART8_BASE)
#define USART9  ((HW_USART_TypeDef *)UART9_BASE)


#define ASM_UART_INTR_RXIS   (1UL << 4)
#define ASM_UART_INTR_TXIS   (1UL << 5)
#define ASM_UART_INTR_RTIS   (1UL << 6)
#define ASM_UART_INTR_RXIEN  (1UL << 20)
#define ASM_UART_INTR_TXIEN  (1UL << 21)
#define ASM_UART_INTR_RTIEN  (1UL << 22)


#define UART_BAUD_DIVINT_MASK       0x003FFFC0UL
#define UART_BAUD_DIVFRAC_MASK      0x0000003FUL
#define UART_FIFO_ENABLE            0x00000010UL
#define MAIN_CLOCK_EXT12M           0
#define MAIN_CLOCK_SYSPLL           1
#define UART_INT_FIFO_LV_SEL_MASK   0x00770000UL
#define RXTIMEOUT_ENABLE            0x01000000UL
#define RXTIMEOUT_MASK              0x00FF0000UL


#define ASM_UART_CTRL0_SFTRST       (1UL << 31)
#define ASM_UART_CTRL0_CLKGATE      (1UL << 30)
#define ASM_UART_CTRL0_RXTO_ENABLE  (1UL << 24)

#define ASM_UART_CTRL2_USARTEN      (1UL << 0)
#define ASM_UART_CTRL2_TXE          (1UL << 8)
#define ASM_UART_CTRL2_RXE          (1UL << 9)


#define ASM_UART_LINECTRL_PEN       (1UL << 1)
#define ASM_UART_LINECTRL_EPS       (1UL << 2)
#define ASM_UART_LINECTRL_STP2      (1UL << 3)
#define ASM_UART_LINECTRL_FEN       (1UL << 4)
#define ASM_UART_LINECTRL_WLEN5     (0UL << 5)
#define ASM_UART_LINECTRL_WLEN6     (1UL << 5)
#define ASM_UART_LINECTRL_WLEN7     (2UL << 5)
#define ASM_UART_LINECTRL_WLEN8     (3UL << 5)
#define ASM_UART_LINECTRL_SPS       (1UL << 7)

#define ASM_UART_STAT_TXFF (1UL << 25)
#define ASM_UART_STAT_RXFE (1UL << 24)

extern void Hw_UartDisable(HW_USART_TypeDef* uartBase);
extern void Hw_UartEnable(HW_USART_TypeDef* uartBase);
extern void Hw_UartReset(HW_USART_TypeDef* uartBase);
extern void Hw_UartConfig(HW_USART_TypeDef* uartBase, int baudRate,
                          int dataBits, int stopBits, int parity);
extern void Hw_UartInit(int index);
#endif
