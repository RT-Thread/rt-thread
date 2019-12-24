/* ------------------------------------------
 * Copyright (c) 2016, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * \version 2016.05
 * \date 2014-06-20
 * \author Huaqi Fang(Huaqi.Fang@synopsys.com)
--------------------------------------------- */

/**
 * \file
 * \ingroup	DEVICE_DW_IIC
 * \brief	DesignWare UART driver hardware description related header file
 * \details	detailed hardware related definitions of DesignWare UART driver
 */

#ifndef _DEVICE_DW_UART_HAL_H_
#define _DEVICE_DW_UART_HAL_H_

/* DW APB UART bit definitions */

/**
 * \name	DesignWare UART HAL IER Marcos
 * \brief	DesignWare UART hal IER related macros
 * @{
 */
/* IER */
#define DW_UART_IER_DATA_AVAIL			(0x01)
#define DW_UART_IER_XMIT_EMPTY			(0x02)
#define DW_UART_IER_LINE_STATUS			(0x04)
#define DW_UART_IER_MDM_STATUS			(0x08)
#define DW_UART_IER_PTIME			(0x80)
/** @} */

/**
 * \name	DesignWare UART HAL IIR Marcos
 * \brief	DesignWare UART hal IIR related macros
 * @{
 */
/* IIR */
/* IIR READ */
#define DW_UART_IIR_IP				(0x01)
#define DW_UART_IIR_MASK			(0x0E)
#define DW_UART_IIR_READ_FIFO_ENABLE		(0xC0)

/* Possible interrupt IIR_MASK values */
#define DW_UART_IIR_MDM_STATUS			(0x00)
#define DW_UART_IIR_XMIT_EMPTY			(0x02)
#define DW_UART_IIR_DATA_AVAIL			(0x04)
#define DW_UART_IIR_LINE_STATUS			(0x06)
#define DW_UART_IIR_RX_TIMEOUT			(0x0C)
#define DW_UART_IIR_INT_ID_MASK			(0x0f)

/* IIR WRITE */
#define DW_UART_IIR_FIFO_ENABLE			(0x01)
#define DW_UART_IIR_RCVR_FIFO_RESET		(0x02)
#define DW_UART_IIR_XMIT_FIFO_RESET		(0x04)
#define DW_UART_IIR_DMA_MODE_SELECT		(0x08)
#define DW_UART_IIR_RCV_TRIGGER_MASK		(0xC0)

/* Values for IIR receive trigger */
#define DW_UART_IIR_TRIGGER_LEVEL_1_CHAR	(0x00)
#define DW_UART_IIR_TRIGGER_LEVEL_1_4_FULL	(0x40)
#define DW_UART_IIR_TRIGGER_LEVEL_1_2_FULL	(0x80)
#define DW_UART_IIR_TRIGGER_LEVEL_2_LESS_FULL	(0xC0)
/** @} */

/**
 * \name	DesignWare UART HAL LCR Marcos
 * \brief	DesignWare UART hal LCR related macros
 * @{
 */
/* LCR */
#define DW_UART_LCR_WORD_LEN_MASK		(0x03)
#define DW_UART_LCR_STOP_BIT_MASK		(0x04)
#define DW_UART_LCR_PARITY_MASK			(0x38)
#define DW_UART_LCR_DPS_MASK			(0x3F)
#define DW_UART_LCR_STICK_PARITY		(0x20)
#define DW_UART_LCR_BREAK			(0x40)
#define DW_UART_LCR_DLAB			(0x80)

/* Word length values */
#define DW_UART_LCR_WORD_LEN5			(0x00)
#define DW_UART_LCR_WORD_LEN6			(0x01)
#define DW_UART_LCR_WORD_LEN7			(0x02)
#define DW_UART_LCR_WORD_LEN8			(0x03)

/* stop bit values */
#define DW_UART_LCR_1_STOP_BIT			(0x00)
#define DW_UART_LCR_1D5_STOP_BIT		(0x04)
#define DW_UART_LCR_2_STOP_BIT			(0x04)

/* Parity bit values */
#define DW_UART_LCR_PARITY_NONE			(0x00)
#define DW_UART_LCR_PARITY_ODD			(0x08)
#define DW_UART_LCR_PARITY_EVEN			(0x18)
#define DW_UART_LCR_PARITY_MARK			(0x28)
#define DW_UART_LCR_PARITY_SPACE		(0x38)

/** @} */

/**
 * \name	DesignWare UART HAL MCR Marcos
 * \brief	DesignWare UART hal MCR related macros
 * @{
 */
/* MCR */
#define DW_UART_MCR_DTR				(0x01)
#define DW_UART_MCR_RTS				(0x02)
#define DW_UART_MCR_LOOPBACK			(0x10)
#define DW_UART_MCR_AFCE			(0x20)
#define DW_UART_MCR_SIRE			(0x40)
/** @} */

/**
 * \name	DesignWare UART HAL LSR Marcos
 * \brief	DesignWare UART hal LSR related macros
 * @{
 */
/* LSR */
#define DW_UART_LSR_DR				(0x01)
#define DW_UART_LSR_OVERRUN			(0x02)
#define DW_UART_LSR_PARITYERR			(0x04)
#define DW_UART_LSR_FRAMEERR			(0x08)
#define DW_UART_LSR_BREAKRCVD			(0x10)
#define DW_UART_LSR_TXD_EMPTY			(0x20)
#define DW_UART_LSR_TX_STATUS			(0x40)
#define DW_UART_LSR_RX_FIFOERR			(0x80)
/** @} */

/**
 * \name	DesignWare UART HAL MSR Marcos
 * \brief	DesignWare UART hal MSR related macros
 * @{
 */
/* MSR */
#define DW_UART_MSR_DCTS			(0x01)
#define DW_UART_MSR_DDSR			(0x02)
#define DW_UART_MSR_TERI			(0x04)
#define DW_UART_MSR_DDCD			(0x08)
#define DW_UART_MSR_CTS				(0x10)
#define DW_UART_MSR_DSR				(0x20)
#define DW_UART_MSR_RIC				(0x40)
#define DW_UART_MSR_DCD				(0x80)
/** @} */

/**
 * \name	DesignWare UART HAL FCR Marcos
 * \brief	DesignWare UART hal FCR related macros
 * @{
 */
/* FCR */
#define DW_UART_FCR_FEN				(0x01)
#define DW_UART_FCR_RFR				(0x02)
#define DW_UART_FCR_TFR				(0x04)
#define DW_UART_FCR_DMS				(0x08)
#define DW_UART_FCR_RTL				(0xC0)
/** @} */

/**
 * \name	DesignWare UART HAL USR Marcos
 * \brief	DesignWare UART hal USR related macros
 * @{
 */
/* USR */
#define DW_UART_USR_BUSY			(0x01)
#define DW_UART_USR_TFNF			(0x02)
#define DW_UART_USR_TFE				(0x04)
#define DW_UART_USR_RFNE			(0x08)
#define DW_UART_USR_RFF				(0x10)
/** @} */

/**
 * \name	DesignWare UART HAL SFE Marcos
 * \brief	DesignWare UART hal SFE related macros
 * @{
 */
/* SFE */
#define DW_UART_SFE_SHADOW_FIFO_ENABLE		(0x01)
/** @} */

/**
 * \name	DesignWare UART HAL SRR Marcos
 * \brief	DesignWare UART hal SRR related macros
 * @{
 */
/* SRR */
#define DW_UART_SRR_UR				(0x01)
#define DW_UART_SRR_RFR				(0x02)
#define DW_UART_SRR_XFR				(0x04)
/** @} */

/**
 * \name	DesignWare UART HAL SRT Marcos
 * \brief	DesignWare UART hal SRT related macros
 * @{
 */
/* SRT */
#define DW_UART_SRT_TRIGGER_LEVEL_1_CHAR	(0x00)
#define DW_UART_SRT_TRIGGER_LEVEL_1_4_FULL	(0x01)
#define DW_UART_SRT_TRIGGER_LEVEL_1_2_FULL	(0x02)
#define DW_UART_SRT_TRIGGER_LEVEL_2_LESS_FULL	(0x03)
/** @} */

/**
 * \name	DesignWare UART HAL STET Marcos
 * \brief	DesignWare UART hal STET related macros
 * @{
 */
/* STET*/
#define DW_UART_STET_FIFO_EMPTY			(0x00)
#define DW_UART_STET_2_CHARS_IN_FIFO		(0x01)
#define DW_UART_STET_1_4_FULL			(0x02)
#define DW_UART_STET_1_2_FULL			(0x03)
/** @} */

/**
 * \name	DesignWare UART HAL CPR Marcos
 * \brief	DesignWare UART hal CPR related macros
 * @{
 */
/* CPR*/
#define DW_UART_CPR_FIFO_STAT			(1<<10)
#define DW_UART_CPR_FIFO_MODE_OFS		(16)
#define DW_UART_CPR_FIFO_MODE_MASK		(0xFF)
#define DW_UART_CPR_FIFO_MODE			(0xFF0000)
/** @} */

#endif /* _DEVICE_DW_UART_HAL_H_ */
