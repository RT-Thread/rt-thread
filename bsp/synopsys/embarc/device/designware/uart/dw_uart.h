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
 * \ingroup	DEVICE_DW_UART
 * \brief	DesignWare UART driver header file
 * \details     detailed definitions of designware uart driver
 */

#ifndef _DW_UART_H_
#define _DW_UART_H_

#include "device/device_hal/inc/dev_uart.h"

#include "inc/arc/arc_exception.h"

/**
 * if this header file is included,
 * will indicate that this designware uart device
 * is used
 */
#define DEVICE_USE_DESIGNWARE_UART

/**
 * \name	DesignWare UART Register Structure
 * \brief	contains definitions of DesignWare UART register structure.
 * @{
 */
/**
 * \brief	DesignWare UART register structure
 * \details	Detailed struct description of DesignWare UART
 * 	block register information, implementation of dev_uart_info::uart_regs
 */
typedef volatile struct dw_uart_reg {
	uint32_t DATA;		/*!< data in/out and DLL */
	uint32_t IER;		/*!< Interrupt enable register and DLH */
	uint32_t IIR;		/*!< Interrupt Id register and FCR */
	uint32_t LCR;		/*!< Line control Register */
	uint32_t MCR;		/*!< Modem control register */
	uint32_t LSR;		/*!< Line Status Register */
	uint32_t MSR;		/*!< Modem status Register */
	uint32_t SCRATCHPAD;	/*!< Uart scratch pad register */
	uint32_t LPDLL;		/*!< Low Power Divisor Latch (Low) Reg */
	uint32_t LPDLH;		/*!< Low Power Divisor Latch (High) Reg */
	uint32_t RES1[2];	/*!< Reserved */
	uint32_t SHR[16];	/*!< Shadow data register(SRBR and STHR) */
	uint32_t FAR;		/*!< FIFO Access register */
	uint32_t TFR;		/*!< Transmit FIFO Read */
	uint32_t RFW;		/*!< Receive FIFO write */
	uint32_t USR;		/*!< UART status register */
	uint32_t TFL;		/*!< Transmit FIFO level */
	uint32_t RFL;		/*!< Receive FIFO level */
	uint32_t SRR;		/*!< Software reset register */
	uint32_t SRTS;		/*!< Shadow request to send */
	uint32_t SBCR;		/*!< Shadow break control */
	uint32_t SDMAM;		/*!< Shadow DMA mode */
	uint32_t SFE;		/*!< Shadow FIFO enable */
	uint32_t SRT;		/*!< Shadow RCVR Trigger */
	uint32_t STET;		/*!< Shadow TX empty register */
	uint32_t HTX;		/*!< Halt TX */
	uint32_t DMASA;		/*!< DMA Software ACK */
	uint32_t RES2[18];	/*!< Reserved */
	uint32_t CPR;		/*!< Camponent parameter register */
	uint32_t UCV;		/*!< UART Component Version */
	uint32_t CTR;		/*!< Component typw register */
} DW_UART_REG, *DW_UART_REG_PTR;
/** @} */

#define DW_UART_GINT_DISABLED	(0)		/*!< designware interrupt disabled for control uart irq/fiq */
#define DW_UART_GINT_ENABLE	(1<<0)		/*!< designware interrupt enabled for control uart irq/fiq */
#define DW_UART_TXINT_ENABLE	(1<<1)		/*!< designware interrupt enabled for control transmit process */
#define DW_UART_RXINT_ENABLE	(1<<2)		/*!< designware interrupt enabled for control transmit process */

/**
 * \brief	DesignWare UART control structure definition
 * \details	implement of dev_uart_info::uart_ctrl
 */
typedef struct dw_uart_ctrl {
	uint32_t dw_uart_regbase;		/*!< uart ip register base */
	uint32_t dw_apb_bus_freq;		/*!< uart ip apb bus frequency */
	uint32_t intno;				/*!< uart interrupt vector number */
	INT_HANDLER dw_uart_int_handler;	/*!< uart interrupt handler */
	uint32_t tx_fifo_len;			/*!< transmit fifo length, set by user in object implementation */
	uint32_t rx_fifo_len;			/*!< receive fifo length, set by user in object implementation */
	uint32_t int_status;			/*!< interrupt status for designware uart */
} DW_UART_CTRL, *DW_UART_CTRL_PTR;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name	DesignWare UART Function Declaration
 * \brief	contains declarations of designware uart functions.
 * \details	This are only used in uart object implementation source file
 * @{
 */
extern int32_t dw_uart_open (DEV_UART *uart_obj, uint32_t baud);
extern int32_t dw_uart_close (DEV_UART *uart_obj);
extern int32_t dw_uart_control (DEV_UART *uart_obj, uint32_t ctrl_cmd, void *param);
extern int32_t dw_uart_write (DEV_UART *uart_obj, const void *data, uint32_t len);
extern int32_t dw_uart_read (DEV_UART *uart_obj, void *data, uint32_t len);
extern void dw_uart_isr(DEV_UART *uart_obj, void *ptr);
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _DW_UART_H_ */
