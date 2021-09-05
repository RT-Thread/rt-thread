/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-03-31 14:59:20
 * @LastEditTime: 2021-04-02 14:14:34
 * @Description:  This files is for definition of uart register
 *
 * @Modify History: * * Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef FT_UART_HW_H
#define FT_UART_HW_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ft_types.h"
#include "ft_assert.h"
#include "ft_io.h"

    /************************** Constant Definitions *****************************/

    /** @name Register Map
 *
 * Register offsets for the UART.
 * @{
 */

#define UARTDR_OFFSET 0U  /* 数据寄存器 */
#define UARTRSR_OFFSET 4U /* 接收状态寄存器/错误清除寄存器 */
#define UARTECR_OFFSET UARTRSR_OFFSET
#define UARTFTR_OFFSET 0x18U    /* 标志寄存器 */
#define UARTILPR_OFFSET 0x020U  /* 低功耗计数寄存器 */
#define UARTIBRD_OFFSET 0x024U  /* 波特率整数值配置寄存器 */
#define UARTFBRD_OFFSET 0x028U  /* 波特率小数值配置寄存器 */
#define UARTLCR_H_OFFSET 0x02cU /* 线控寄存器 */
#define UARTCR_OFFSET 0x030U    /* 控制寄存器 */
#define UARTIFLS_OFFSET 0x034U  /* FIFO阈值选择寄存器 */
#define UARTIMSC_OFFSET 0x038U  /* 中断屏蔽选择清除寄存器 */
#define UARTRIS_OFFSET 0x03cU   /* 中断状态寄存器 */
#define UARTMIS_OFFSET 0x040U   /* 中断屏蔽状态寄存器 */
#define UARTICR_OFFSET 0x044U   /* 中断清除寄存器 */
#define UARTDMACR_OFFSET 0x048U /* DMA控制寄存器 */

    /* 数据寄存器 RW */

#define UARTDR_OE 0x800U /* 如果接收到数据并且接收的 FIFO 已满，该位设置为 1 */
#define UARTDR_BE 0x400U /* 突发错误 */
#define UARTDR_PE 0x200U /*  奇偶校验错误。 */
#define UARTDR_FE 0x100U /*  帧错误。 */
#define UARTDR_ALLE (UARTDR_OE | UARTDR_BE | UARTDR_PE | UARTDR_FE)
#define UARTDR_DATA 0xffU /* R 接收数据 ，W 传输数据  */

    /* 接收状态寄存器 RW */

#define UARTRSR_OE 0x8U /* 溢出错误。 */
#define UARTRSR_BE 0x4U /* 突发错误 */
#define UARTRSR_PE 0x2U /* 奇偶校验错误。 */
#define UARTRSR_FE 0x1U /* 帧错误 */

#define UARTECR_CLE 0xffU /* 清除 */

/* 标志寄存器  RO */
#define UARTFTR_RI 0x100U  /* Ring indicator */
#define UARTFTR_TXFE 0x80U /* Transmit FIFO empty */
#define UARTFTR_RXFF 0x40U /*  Receive FIFO full */
#define UARTFTR_TXFF 0x20U /*  Transmit FIFO full. */
#define UARTFTR_RXFE 0x10U /* Receive FIFO empty */
#define UARTFTR_BUSY 0x08U /* UART busy */
#define UARTFTR_DCD 0x04U  /*  Data carrier detect. */
#define UARTFTR_DSR 0x02U  /* Data set ready.  */
#define UARTFTR_CTS 0x1U   /* Clear to send */

/* IrDA 低功耗计数寄存器 RW */
#define UARTILPR_ILPDVSR 0xffU /* 8-bit low-power divisor value. These bits are cleared to 0 at reset */

/* 波特率整数值配置寄存器 RW */
#define UARTIBRD_BAUD_DIVFRAC 0xffffU /* The fractional baud rate divisor. */

/* 波特率小数值配置寄存器 RW */
#define UARTFBRD_BAUD_DIVFRAC 0x3fU /* The fractional baud rate divisor. */

/* 线控寄存器 RW */
#define UARTLCR_H_SPS 0x80U  /* Stick parity select.  */
#define UARTLCR_H_WLEN 0x60U /*  Word length. */
#define UARTLCR_H_FEN 0x10U  /*  Enable FIFOs. */
#define UARTLCR_H_STP2 0x08U /* Two stop bits select. */
#define UARTLCR_H_EPS 0x04U  /*  Even parity select. */
#define UARTLCR_H_PEN 0x02U  /*  Parity enable. */
#define UARTLCR_H_BRK 0x01U  /* send break  */

/* 控制寄存器  RW */
#define UARTCR_CTSEN 0x8000U /* CTS hardware flow control enable.  */
#define UARTCR_RTSEN 0x4000U /* RTS hardware flow control enable.  */
#define UARTCR_OUT2 0x2000U  /* This bit is the complement of the UART Out2 (nUARTOut2) modem status output. */
#define UARTCR_Out1 0x1000U  /* This bit is the complement of the UART Out1 (nUARTOut1) modem status output. */
#define UARTCR_RTS 0x0800U   /*  Request to send. */
#define UARTCR_DTR 0x0400U   /* Data transmit ready */
#define UARTCR_RXE 0x0200U   /*  Receive enable. */
#define UARTCR_TXE 0x0100U   /* Transmit enable. */
#define UARTCR_LBE 0x0080U   /* Loop back enable.*/
#define UARTCR_SIRLP 0x4U    /* IrDA SIR low power mode. */
#define UARTCR_SIREN 0x2U    /*  SIR enable. */
#define UARTCR_UARTEN 0x1U   /* UART enable. */

/* FIFO阈值选择寄存器 RW  */
#define UARTIFLS_RXIFLSEL 0x38U /* Receive interrupt FIFO level select. */
#define UARTIFLS_TXIFLSEL 0x7U  /* Transmit interrupt FIFO level select. */

/* 中断屏蔽选择清除寄存器  RW */
#define UARTIMSC_OEIM 0x400U /* Overrun error interrupt mask.  */
#define UARTIMSC_BEIM 0x200U /* Break error interrupt mask  */
#define UARTIMSC_PEIM 0x100U /* Parity error interrupt mask.  */
#define UARTIMSC_FEIM 0x80U  /*  Framing error interrupt mask.  */
#define UARTIMSC_RTIM 0x40U  /* Receive timeout interrupt mask.   */
#define UARTIMSC_TXIM 0x20U  /* Transmit interrupt mask.  */
#define UARTIMSC_RXIM 0x10U  /*  Receive interrupt mask.  */
#define UARTIMSC_DSRMIM 0x8U /* nUARTDSR modem interrupt mask.  */
#define UARTIMSC_DCDMIM 0x4U /* nUARTDCD modem interrupt mask.   */
#define UARTIMSC_CTSMIM 0x2U /* nUARTCTS modem interrupt mask.  */
#define UARTIMSC_RIMIM 0x1U  /* nUARTRI modem interrupt mask.  */
#define UARTIMSC_ALLM 0x3ffU /* all interrupt mask */

    /* 中断状态寄存器   RO */

#define UARTRIS_OEIS 0x400U /* Overrun error interrupt mask.  */
#define UARTRIS_BEIS 0x200U /* Break error interrupt mask  */
#define UARTRIS_PEIS 0x100U /* Parity error interrupt mask.  */
#define UARTRIS_FEIS 0x80U  /*  Framing error interrupt mask.  */
#define UARTRIS_RTIS 0x40U  /* Receive timeout interrupt mask.   */
#define UARTRIS_TXIS 0x20U  /* Transmit interrupt mask.  */
#define UARTRIS_RXIS 0x10U  /*  Receive interrupt mask.  */
#define UARTRIS_DSRMIS 0x8U /* nUARTDSR modem interrupt mask.  */
#define UARTRIS_DCDMIS 0x4U /* nUARTDCD modem interrupt mask.   */
#define UARTRIS_CTSMIS 0x2U /* nUARTCTS modem interrupt mask.  */
#define UARTRIS_RIMIS 0x1U  /* nUARTRI modem interrupt mask.  */

    /* 中断屏蔽状态寄存器 R0  */

#define UARTMIS_OEMIS 0x400U /* Overrun error interrupt mask.  */
#define UARTMIS_BEMIS 0x200U /* Break error interrupt mask  */
#define UARTMIS_PEMIS 0x100U /* Parity error interrupt mask.  */
#define UARTMIS_FEMIS 0x80U  /*  Framing error interrupt mask.  */
#define UARTMIS_RTMIS 0x40U  /* Receive timeout interrupt mask.   */
#define UARTMIS_TXMIS 0x20U  /* Transmit interrupt mask.  */
#define UARTMIS_RXMIS 0x10U  /*  Receive interrupt mask.  */
#define UARTMIS_DSRMMIS 0x8U /* nUARTDSR modem interrupt mask.  */
#define UARTMIS_DCDMMIS 0x4U /* nUARTDCD modem interrupt mask.   */
#define UARTMIS_CTSMMIS 0x2U /* nUARTCTS modem interrupt mask.  */
#define UARTMIS_RIMMIS 0x1U  /* nUARTRI modem interrupt mask.  */

/* 中断清除寄存器 WO */
#define UARTICR_OEIC 0x400U /* Overrun error interrupt mask.  */
#define UARTICR_BEIC 0x200U /* Break error interrupt mask  */
#define UARTICR_PEIC 0x100U /* Parity error interrupt mask.  */
#define UARTICR_FEIC 0x80U  /*  Framing error interrupt mask.  */
#define UARTICR_RTIC 0x40U  /* Receive timeout interrupt mask.   */
#define UARTICR_TXIC 0x20U  /* Transmit interrupt mask.  */
#define UARTICR_RXIC 0x10U  /*  Receive interrupt mask.  */
#define UARTICR_DSRMIC 0x8U /* nUARTDSR modem interrupt mask.  */
#define UARTICR_DCDMIC 0x4U /* nUARTDCD modem interrupt mask.   */
#define UARTICR_CTSMIC 0x2U /* nUARTCTS modem interrupt mask.  */
#define UARTICR_RIMIC 0x1U  /* nUARTRI modem interrupt mask.  */

/* DMA控制寄存器 RW */
#define UARTDMACR_DMAONERR 0x4U /* DMA on error. */
#define UARTDMACR_TXDMAE 0x2U   /* Transmit DMA enable. */
#define UARTDMACR_RXDMAE 0x1U   /* Receive DMA enable. */

/***************** Macros (Inline Functions) Definitions *********************/

/**
 * @name: FT_UART_ReadReg
 * @msg:  读取串口寄存器
 * @param {u32} BaseAddress 串口的基地址
 * @param {u32} RegOffset   串口的寄存器的偏移
 * @return {u32} 寄存器参数
 */
#define FT_UART_ReadReg(BaseAddress, RegOffset) Ft_in32(BaseAddress + (u32)RegOffset)

/**
 * @name: FT_UART_WriteReg
 * @msg:  写入串口寄存器
 * @param {u32} BaseAddress 串口的基地址
 * @param {u32} RegOffset   串口的寄存器的偏移
 * @param {u32} RegisterValue 写入寄存器参数
 * @return {void}
 */
#define FT_UART_WriteReg(BaseAddress, RegOffset, RegisterValue) Ft_out32(BaseAddress + (u32)RegOffset, (u32)RegisterValue)

/**
 * @name: FT_UART_ISRECEIVEDATA
 * @msg:  用于确认是否接收到数据
 * @param {u32} BaseAddress 串口的基地址
 * @return {bool} true 是存在数据 ， false 是不存在数据
 *
 */
#define FT_UART_IsReceiveData(BaseAddress) (Ft_in32(BaseAddress + UARTFTR_OFFSET) & UARTFTR_RXFE)

/**
 * @name: FT_UART_ISTRANSMITFULL
 * @msg:  用于确认是否能够发送数据
 * @param {u32} BaseAddress 串口的基地址
 * @return {bool} true 是数据已满 ， false 可以发送数据
 */
#define FT_UART_IsTransmitFull(BaseAddress) ((Ft_in32(BaseAddress + UARTFTR_OFFSET) & (u32)UARTFTR_TXFF) == UARTFTR_TXFF)

    void FUart_SendByte(u32 BaseAddress, u8 Byte);
    u8 FUart_RecvByte(u32 BaseAddress);
    u8 FUart_GetChar(u32 BaseAddress);

#ifdef __cplusplus
}
#endif

#endif
