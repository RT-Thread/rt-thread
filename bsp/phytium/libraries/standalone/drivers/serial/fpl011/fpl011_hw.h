/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fpl011_hw.h
 * Date: 2021-11-02 14:53:42
 * LastEditTime: 2022-02-18 09:06:10
 * Description:  This file is for definition of uart register
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  huanghe 2021/11/2  first commit
 * 1.1  liushengming 2022/02/18  modified some defines
 */

#ifndef FPL011_HW_H
#define FPL011_HW_H

#include "ftypes.h"
#include "fassert.h"
#include "fio.h"


#ifdef __cplusplus
extern "C"
{
#endif



/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/** @name Register Map
 *
 * Register offsets for the UART.
 */
#define FPL011DR_OFFSET 0U  /* Data */
#define FPL011RSR_OFFSET 4U /* Receive Status Register/Error Clear */
#define FPL011ECR_OFFSET FPL011RSR_OFFSET
#define FPL011FTR_OFFSET  0x18U   /* Flag Register */
#define FPL011ILPR_OFFSET 0x020U  /* IrDA Low-Power Counter */
#define FPL011IBRD_OFFSET 0x024U  /* Integer Baud Rate */
#define FPL011FBRD_OFFSET 0x028U  /* Fractional Baud Rate */
#define FPL011LCR_H_OFFSET 0x02cU /* Line Control */
#define FPL011CR_OFFSET 0x030U    /* Control */
#define FPL011IFLS_OFFSET 0x034U  /* Interrupt FIFO Level Select */
#define FPL011IMSC_OFFSET 0x038U  /* Interrupt Mask Set/Clear */
#define FPL011RIS_OFFSET 0x03cU   /* Raw interrupt Status  */
#define FPL011MIS_OFFSET 0x040U   /* Mask interrupt Status  */
#define FPL011ICR_OFFSET 0x044U   /* Interrupt Clear */
#define FPL011DMACR_OFFSET 0x048U /* DMA Control */

/* Data RW */
#define FPL011DR_OE 0x800U /* This bit is set to 1 if data is received and the received FIFO is full */
#define FPL011DR_BE 0x400U /* Break error */
#define FPL011DR_PE 0x200U /*  Parity error */
#define FPL011DR_FE 0x100U /*  Frame error */
#define FPL011DR_ALLE (FPL011DR_OE | FPL011DR_BE | FPL011DR_PE | FPL011DR_FE)
#define FPL011DR_DATA 0xffU

/* Receive Status Register/Error Clear RW */
#define FPL011RSR_OE 0x8U /* overflow error  */
#define FPL011RSR_BE 0x4U /* Break error  */
#define FPL011RSR_PE 0x2U /* Parity error */
#define FPL011RSR_FE 0x1U /* Frame error */

#define FPL011ECR_CLE 0xffU /* Clear */

/* Flag Register  RO */
#define FPL011FTR_RI 0x100U  /* Ring indicator */
#define FPL011FTR_TXFE 0x80U /* Transmit FIFO empty */
#define FPL011FTR_RXFF 0x40U /*  Receive FIFO full */
#define FPL011FTR_TXFF 0x20U /*  Transmit FIFO full. */
#define FPL011FTR_RXFE 0x10U /* Receive FIFO empty */
#define FPL011FTR_BUSY 0x08U /* UART busy */
#define FPL011FTR_DCD 0x04U  /*  Data carrier detect. */
#define FPL011FTR_DSR 0x02U  /* Data set ready.  */
#define FPL011FTR_CTS 0x1U   /* Clear to send */

/* IrDA Low-Power Counter RW */
#define FPL011ILPR_ILPDVSR 0xffU /* 8-bit low-power divisor value. These bits are cleared to 0 at reset */

/* Integer Baud Rate RW */
#define FPL011IBRD_BAUD_DIVFRAC 0xffffU /* The fractional baud rate divisor. */

/* Fractional Baud Rate RW */
#define FPL011FBRD_BAUD_DIVFRAC 0x3fU /* The fractional baud rate divisor. */

/* Line Control RW */
#define FPL011LCR_H_SPS 0x80U  /* Stick parity select.  */
#define FPL011LCR_H_WLEN 0x60U /*  Word length. */
#define FPL011LCR_H_FEN 0x10U  /*  Enable FIFOs. */
#define FPL011LCR_H_STP2 0x08U /* Two stop bits select. */
#define FPL011LCR_H_EPS 0x04U  /*  Even parity select. */
#define FPL011LCR_H_PEN 0x02U  /*  Parity enable. */
#define FPL011LCR_H_BRK 0x01U  /* send break  */

#define FPL011LCR_H_WLEN_SHIFT  0x00000005U /* Word length shift */
#define FPL011LCR_H_WLEN_5_BIT  0x00000000U /* 5 bits data */
#define FPL011LCR_H_WLEN_6_BIT  0x00000020U /* 6 bits data */
#define FPL011LCR_H_WLEN_7_BIT  0x00000040U /* 7 bits data */
#define FPL011LCR_H_WLEN_8_BIT  0x00000060U /* 8 bits data */
#define FPL011LCR_H_STP_1_BIT   0x00000000U

#define FPL011LCR_H_STP_MASK    0x00000008U /* Stop bits mask */
#define FPL011LCR_H_STP_SHIFT   0x00000003U /* Stop bits shift */
#define FPL011LCR_H_PARITY_EVEN 0x00000004U /* Even parity mode */
#define FPL011LCR_H_PARITY_MASK 0x00000002U /* Parity mask */
#define FPL011LCR_H_PARITY_SHIFT    0x00000001U /* Parity shift */
#define FPL011LCR_H_PARITY_NONE 0x00000000U /* No parity mode */
#define FPL011LCR_H_PARITY_ODD  0x00000000U /* Odd parity mode */

/* Control  RW */
#define FPL011CR_CTSEN 0x8000U /* CTS hardware flow control enable.  */
#define FPL011CR_RTSEN 0x4000U /* RTS hardware flow control enable.  */
#define FPL011CR_OUT2 0x2000U  /* This bit is the complement of the UART Out2 (nUARTOut2) modem status output. */
#define FPL011CR_OUT1 0x1000U  /* This bit is the complement of the UART Out1 (nUARTOut1) modem status output. */
#define FPL011CR_RTS 0x0800U   /*  Request to send. */
#define FPL011CR_DTR 0x0400U   /* Data transmit ready */
#define FPL011CR_RXE 0x0200U   /*  Receive enable. */
#define FPL011CR_TXE 0x0100U   /* Transmit enable. */
#define FPL011CR_LBE 0x0080U   /* Loop back enable.*/
#define FPL011CR_SIRLP 0x4U    /* IrDA SIR low power mode. */
#define FPL011CR_SIREN 0x2U    /*  SIR enable. */
#define FPL011CR_UARTEN 0x1U   /* UART enable. */
#define FPL011CR_MODE_NORMAL    0x00000000U /* Normal Mode */


/* Interrupt FIFO Level Select RW  */
#define FPL011IFLS_RXIFLSEL_MASK    0x00000038U /* Receive interrupt FIFO level select mask */
#define FPL011IFLS_TXIFLSEL_MASK    0x00000007U /* Receive interrupt FIFO level select mask */
#define FPL011IFLS_RXIFLSEL_1_8     0x00000000U /* Receive FIFO becomes . 1/8 full */
#define FPL011IFLS_RXIFLSEL_1_4     0x00000008U /* Receive FIFO becomes . 1/4 full */
#define FPL011IFLS_RXIFLSEL_1_2     0x00000010U /* Receive FIFO becomes * . 1/2 full */
#define FPL011IFLS_RXIFLSEL_3_4     0x00000018U /* Receive FIFO becomes * . 3/4 full */
#define FPL011IFLS_RXIFLSEL_7_8     0x00000020U /* Receive FIFO becomes * . 7/8 full */
#define FPL011IFLS_TXIFLSEL_1_8     0x00000000U /* Transmit FIFO becomes * . 1/8 full */
#define FPL011IFLS_TXIFLSEL_1_4     0x00000001U /* Transmit FIFO becomes * . 1/4 full */
#define FPL011IFLS_TXIFLSEL_1_2     0x00000002U /* Transmit FIFO becomes * . 1/2 full */
#define FPL011IFLS_TXIFLSEL_3_4     0x00000003U /* Transmit FIFO becomes * . 3/4 full */
#define FPL011IFLS_TXIFLSEL_7_8     0x00000004U /* Transmit FIFO becomes * . 7/8 full */

/* Interrupt Mask Set/Clear  RW */
#define FPL011IMSC_OEIM 0x400U /* Overrun error interrupt mask.  */
#define FPL011IMSC_BEIM 0x200U /* Break error interrupt mask  */
#define FPL011IMSC_PEIM 0x100U /* Parity error interrupt mask.  */
#define FPL011IMSC_FEIM 0x80U  /*  Framing error interrupt mask.  */
#define FPL011IMSC_RTIM 0x40U  /* Receive timeout interrupt mask.   */
#define FPL011IMSC_TXIM 0x20U  /* Transmit interrupt mask.  */
#define FPL011IMSC_RXIM 0x10U  /*  Receive interrupt mask.  */
#define FPL011IMSC_DSRMIM 0x8U /* nUARTDSR modem interrupt mask.  */
#define FPL011IMSC_DCDMIM 0x4U /* nUARTDCD modem interrupt mask.   */
#define FPL011IMSC_CTSMIM 0x2U /* nUARTCTS modem interrupt mask.  */
#define FPL011IMSC_RIMIM 0x1U  /* nUARTRI modem interrupt mask.  */
#define FPL011IMSC_ALLM 0x7ffU /* all interrupt mask */

/* Raw interrupt Status   RO */

#define FPL011RIS_OEIS 0x400U /* Overrun error interrupt mask.  */
#define FPL011RIS_BEIS 0x200U /* Break error interrupt mask  */
#define FPL011RIS_PEIS 0x100U /* Parity error interrupt mask.  */
#define FPL011RIS_FEIS 0x80U  /*  Framing error interrupt mask.  */
#define FPL011RIS_RTIS 0x40U  /* Receive timeout interrupt mask.   */
#define FPL011RIS_TXIS 0x20U  /* Transmit interrupt mask.  */
#define FPL011RIS_RXIS 0x10U  /*  Receive interrupt mask.  */
#define FPL011RIS_DSRMIS 0x8U /* nUARTDSR modem interrupt mask.  */
#define FPL011RIS_DCDMIS 0x4U /* nUARTDCD modem interrupt mask.   */
#define FPL011RIS_CTSMIS 0x2U /* nUARTCTS modem interrupt mask.  */
#define FPL011RIS_RIMIS 0x1U  /* nUARTRI modem interrupt mask.  */

/* Mask interrupt Status R0  */

#define FPL011MIS_OEMIS 0x400U /* Overrun error interrupt mask.  */
#define FPL011MIS_BEMIS 0x200U /* Break error interrupt mask  */
#define FPL011MIS_PEMIS 0x100U /* Parity error interrupt mask.  */
#define FPL011MIS_FEMIS 0x80U  /*  Framing error interrupt mask.  */
#define FPL011MIS_RTMIS 0x40U  /* Receive timeout interrupt mask.   */
#define FPL011MIS_TXMIS 0x20U  /* Transmit interrupt mask.  */
#define FPL011MIS_RXMIS 0x10U  /*  Receive interrupt mask.  */
#define FPL011MIS_DSRMMIS 0x8U /* nUARTDSR modem interrupt mask.  */
#define FPL011MIS_DCDMMIS 0x4U /* nUARTDCD modem interrupt mask.   */
#define FPL011MIS_CTSMMIS 0x2U /* nUARTCTS modem interrupt mask.  */
#define FPL011MIS_RIMMIS 0x1U  /* nUARTRI modem interrupt mask.  */

/* Interrupt Clear WO */
#define FPL011ICR_OEIC 0x400U /* Overrun error interrupt mask.  */
#define FPL011ICR_BEIC 0x200U /* Break error interrupt mask  */
#define FPL011ICR_PEIC 0x100U /* Parity error interrupt mask.  */
#define FPL011ICR_FEIC 0x80U  /*  Framing error interrupt mask.  */
#define FPL011ICR_RTIC 0x40U  /* Receive timeout interrupt mask.   */
#define FPL011ICR_TXIC 0x20U  /* Transmit interrupt mask.  */
#define FPL011ICR_RXIC 0x10U  /*  Receive interrupt mask.  */
#define FPL011ICR_DSRMIC 0x8U /* nUARTDSR modem interrupt mask.  */
#define FPL011ICR_DCDMIC 0x4U /* nUARTDCD modem interrupt mask.   */
#define FPL011ICR_CTSMIC 0x2U /* nUARTCTS modem interrupt mask.  */
#define FPL011ICR_RIMIC 0x1U  /* nUARTRI modem interrupt mask.  */
#define FPL011ICR_ALL_CLEAR (FPL011ICR_OEIC |FPL011ICR_BEIC |FPL011ICR_PEIC |FPL011ICR_FEIC |FPL011ICR_RTIC |FPL011ICR_TXIC |FPL011ICR_RXIC |FPL011ICR_DSRMIC |FPL011ICR_DCDMIC |FPL011ICR_CTSMIC |FPL011ICR_RIMIC )

/* DMA Control RW */
#define FPL011DMACR_DMAONERR 0x4U /* DMA on error. */
#define FPL011DMACR_TXDMAE 0x2U   /* Transmit DMA enable. */
#define FPL011DMACR_RXDMAE 0x1U   /* Receive DMA enable. */

/***************** Macros (Inline Functions) Definitions *********************/

#define FUART_READREG32(addr, reg_offset) FtIn32(addr + (u32)reg_offset)
#define FUART_WRITEREG32(addr, reg_offset, reg_value) FtOut32(addr + (u32)reg_offset, (u32)reg_value)

/**
 * @name: FUART_RECEIVEDATAEMPTY
 * @msg:  Used to confirm whether data has been received
 * @param addr contains the base address of the device.
 * @return {bool} true 是不存在数据 ， false 是存在数据
 *
 */
#define FUART_RECEIVEDATAEMPTY(addr) (FtIn32(addr + FPL011FTR_OFFSET) & FPL011FTR_RXFE)

/**
 * @name: FUART_ISTRANSMITFULL
 * @msg:  Used to confirm whether data can be sent
 * @param addr contains the base address of the device.
 * @return {bool} true 是数据已满 ， false 可以发送数据
 */
#define FUART_ISTRANSMITFULL(addr) ((FtIn32(addr + FPL011FTR_OFFSET) & (u32)FPL011FTR_TXFF) == FPL011FTR_TXFF)


/**
 * @name: FUART_ISTRANSMITBUSY
 * @msg:  Determine if a byte of data can be sent with the transmitter.
 * @return TRUE if the TX is busy, FALSE if a byte can be put in the
 *          FIFO.
 */
#define FUART_ISTRANSMITBUSY(addr) ((FtIn32(addr + FPL011FTR_OFFSET) & (u32)FPL011FTR_BUSY) == FPL011FTR_BUSY)

/************************** Function Prototypes ******************************/

void FPl011SendByte(uintptr addr, u8 byte);
u8 FPl011RecvByte(uintptr addr);

#ifdef __cplusplus
}
#endif

#endif
