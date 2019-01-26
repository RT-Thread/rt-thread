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
 * \defgroup	DEVICE_DW_UART	Designware UART Driver
 * \ingroup	DEVICE_DW
 * \brief	Designware UART Driver Implementation
 */

/**
 * \file
 * \ingroup	DEVICE_DW_UART
 * \brief	DesignWare UART driver implementation based on device hal layer definition (\ref dev_uart.h)
 */
#include <string.h>

#include "inc/embARC_toolchain.h"
#include "inc/embARC_error.h"

#include "inc/arc/arc_exception.h"

#include "device/designware/uart/dw_uart_hal.h"
#include "device/designware/uart/dw_uart.h"


/**
 * \name	DesignWare UART Driver Macros
 * \brief	DesignWare UART driver macros used in uart driver
 * @{
 */
/** check expressions used in DesignWare UART driver implementation */
#define DW_UART_CHECK_EXP(EXPR, ERROR_CODE)		CHECK_EXP(EXPR, ercd, ERROR_CODE, error_exit)

#ifndef DISABLE_DEVICE_OBJECT_VALID_CHECK
/** valid check of uart info object */
#define VALID_CHK_UART_INFO_OBJECT(uartinfo_obj_ptr)		{				\
			DW_UART_CHECK_EXP((uartinfo_obj_ptr)!=NULL, E_OBJ);			\
			DW_UART_CHECK_EXP(((uartinfo_obj_ptr)->uart_ctrl)!=NULL, E_OBJ);	\
 		}
#endif

/** convert DesignWare baudrate to divisor */
#define DW_UART_BAUD2DIV(perifreq, baud)		((perifreq) / ((baud)*16))

/**
 * \name	DesignWare UART Interrupt Callback Routine Select Marcos
 * \brief	DesignWare UART interrupt callback routines select macros definitions
 * @{
 */
#define DW_UART_RDY_SND					(1U)	/*!< ready to send callback */
#define DW_UART_RDY_RCV					(2U)	/*!< ready to receive callback */
/** @} */

/** @} */

/**
 * \defgroup	DEVICE_DW_UART_STATIC	DesignWare UART Driver Static Functions
 * \ingroup	DEVICE_DW_UART
 * \brief	Static or inline functions, variables for DesignWare UART handle uart operations,
 * 	only used in this file
 * @{
 */
const uint8_t dw_uart_databits[] = { \
	DW_UART_LCR_WORD_LEN5, DW_UART_LCR_WORD_LEN6, \
	DW_UART_LCR_WORD_LEN7, DW_UART_LCR_WORD_LEN8};
const uint8_t dw_uart_parity[] = {
	DW_UART_LCR_PARITY_NONE, DW_UART_LCR_PARITY_ODD,
	DW_UART_LCR_PARITY_EVEN, DW_UART_LCR_PARITY_MASK,
	DW_UART_LCR_PARITY_SPACE
};
const uint8_t dw_uart_stopbits[] = {
	DW_UART_LCR_1_STOP_BIT, DW_UART_LCR_1D5_STOP_BIT,
	DW_UART_LCR_2_STOP_BIT
};

/** test whether uart is ready to send, 1 ready, 0 not ready */
Inline int32_t dw_uart_putready(DW_UART_REG *uart_reg_ptr)
{
	return ((uart_reg_ptr->USR & DW_UART_USR_TFNF) != 0);
}
/** test whether uart is ready to receive, 1 ready, 0 not ready */
Inline int32_t dw_uart_getready(DW_UART_REG *uart_reg_ptr)
{
	return ((uart_reg_ptr->USR & DW_UART_USR_RFNE) != 0);
}
/** write char to uart send fifo */
Inline void dw_uart_putchar(DW_UART_REG *uart_reg_ptr, char chr)
{
	uart_reg_ptr->DATA = chr;
}
/** read data from uart receive fifo, return data received */
Inline int32_t dw_uart_getchar(DW_UART_REG *uart_reg_ptr)
{
	return (int32_t)uart_reg_ptr->DATA;
}
/**
 * \brief	send char by uart when available,
 * 	mostly used in interrupt method, non-blocked function
 * \param[in]	uart_reg_ptr	uart register structure pointer
 * \param[in]	chr		char to be sent
 * \retval	0		send successfully
 * \retval	-1		not ready to send data
 */
Inline int32_t dw_uart_snd_chr(DW_UART_REG *uart_reg_ptr, char chr)
{
	if (dw_uart_putready(uart_reg_ptr)) {
		dw_uart_putchar(uart_reg_ptr, chr);
		return 0;
	}
	return -1;
}
/**
 * \brief	receive one char from uart,
 * 	mostly used in interrupt routine, non-blocked function
 * \param[in]	uart_reg_ptr	uart register structure pointer
 * \return	data received by the uart
 */
Inline int32_t dw_uart_rcv_chr(DW_UART_REG *uart_reg_ptr)
{
	return dw_uart_getchar(uart_reg_ptr);
}
/**
 * \brief	send char by uart in poll method, blocked function
 * \param[in]	uart_reg_ptr	uart register structure pointer
 * \param[in]	chr		char to be sent
 */
Inline void dw_uart_psnd_chr(DW_UART_REG *uart_reg_ptr, char chr)
{
	/** wait until uart is ready to send */
	while (!dw_uart_putready(uart_reg_ptr)); /* blocked */
	/** send char */
	dw_uart_putchar(uart_reg_ptr, chr);
}
/**
 * \brief	receive one char from uart in poll method, blocked function
 * \param[in]	uart_reg_ptr	uart register structure pointer
 * \return	data received by the uart
 */
Inline int32_t dw_uart_prcv_chr(DW_UART_REG *uart_reg_ptr)
{
	/** wait until uart is ready to receive */
	while (!dw_uart_getready(uart_reg_ptr)); /* blocked */
	/** receive data */
	return dw_uart_getchar(uart_reg_ptr);
}

/** Get TX FIFO Length */
Inline uint32_t dw_uart_get_txfifo_len(DW_UART_REG *uart_reg_ptr)
{
	uint32_t txfifolen;
	uint32_t uart_cpr;

	uart_cpr = uart_reg_ptr->CPR;
	if (uart_cpr & DW_UART_CPR_FIFO_STAT) {
		txfifolen = ((uart_cpr & DW_UART_CPR_FIFO_MODE) >> DW_UART_CPR_FIFO_MODE_OFS) << 4;
	} else {
		txfifolen = 0;
	}

	return txfifolen;
}

/** Get RX FIFO Length */
Inline uint32_t dw_uart_get_rxfifo_len(DW_UART_REG *uart_reg_ptr)
{
	uint32_t rxfifolen;
	uint32_t uart_cpr;

	uart_cpr = uart_reg_ptr->CPR;
	if (uart_cpr & DW_UART_CPR_FIFO_STAT) {
		rxfifolen = ((uart_cpr & DW_UART_CPR_FIFO_MODE) >> DW_UART_CPR_FIFO_MODE_OFS) << 4;
	} else {
		rxfifolen = 0;
	}

	return rxfifolen;
}

/**
 * \brief	set designware uart DPS value
 * \param	uart_reg_ptr	uart register structure
 * \param	dps		data bits/parity bit/stop bits parameter
 * \retval	0	Set ok
 * \retval	!0	Set failed
 */
static int32_t dw_uart_set_dps(DW_UART_REG *uart_reg_ptr, UART_DPS_FORMAT *dps)
{
	uint32_t dps_value = 0;

	if (dps == NULL) return -1;
	/* data bits check */
	if ((dps->databits < 5) || (dps->databits > 8)) return -1;
	/* stop bits check */
	if (dps->stopbits > UART_STPBITS_TWO) return -1;
	/* parity bit type check */
	if (dps->parity > UART_PARITY_SPACE) return -1;

	dps_value |= (uint32_t)dw_uart_databits[dps->databits-5];
	dps_value |= (uint32_t)dw_uart_stopbits[dps->stopbits];
	dps_value |= (uint32_t)dw_uart_parity[dps->parity];

	/* clear dps bits */
	uart_reg_ptr->LCR &= (~DW_UART_LCR_DPS_MASK);
	/* set dps bits */
	uart_reg_ptr->LCR |= dps_value;

	return 0;
}

/**
 * \brief	set designware uart baudrate
 * \param	uart_reg_ptr	uart register structure
 * \param	baud_divisor	uart baudrate divisor
 */
static void dw_uart_set_baud(DW_UART_REG *uart_reg_ptr, uint32_t baud_divisor)
{
	/* enable uart baudrate update */
	uart_reg_ptr->LCR |= DW_UART_LCR_DLAB;
	/**
	 * setting uart baudrate registers
	 */
	uart_reg_ptr->DATA = baud_divisor & 0xff;	/*!< DLL */
	uart_reg_ptr->IER = (baud_divisor>>8) & 0xff;	/*!< DLH */
	/** disable DLAB */
	uart_reg_ptr->LCR &= ~(DW_UART_LCR_DLAB);
}

/**
 * \brief	Do uart software reset
 * \param	uart_reg_ptr	uart register structure
 */
Inline void dw_uart_software_reset(DW_UART_REG *uart_reg_ptr)
{
	uart_reg_ptr->SRR = DW_UART_SRR_UR|DW_UART_SRR_RFR|DW_UART_SRR_XFR;
	while(uart_reg_ptr->USR & DW_UART_USR_BUSY); /* wait until software reset completed */
}

/**
 * \brief	set designware uart baudrate
 * \param	uart_reg_ptr	uart register structure
 * \param	hwfc		uart hardware flow control type
 * \note	Need to set corresponding pin functions
 */
static void dw_uart_set_hwfc(DW_UART_REG *uart_reg_ptr, UART_HW_FLOW_CONTROL hwfc)
{
	if (hwfc == UART_FC_NONE) {
		uart_reg_ptr->MCR &= ~(DW_UART_MCR_AFCE|DW_UART_MCR_RTS);
	}
	if ((hwfc == UART_FC_RTS) || (hwfc == UART_FC_BOTH)) {
		uart_reg_ptr->MCR |= (DW_UART_MCR_AFCE|DW_UART_MCR_RTS);
	}
	if ((hwfc == UART_FC_CTS) || (hwfc == UART_FC_BOTH)) {
		uart_reg_ptr->MCR |= (DW_UART_MCR_AFCE);
	}
}

Inline void dw_uart_set_break(DW_UART_REG *uart_reg_ptr)
{
	uart_reg_ptr->LCR |= DW_UART_LCR_BREAK;
}

Inline void dw_uart_clr_break(DW_UART_REG *uart_reg_ptr)
{
	uart_reg_ptr->LCR &= ~DW_UART_LCR_BREAK;
}

/**
 * \brief	init designware uart with selected baud
 * \param[in]	uart_reg_ptr	uart register structure pointer
 * \param[in]	baud_divisor	baudrate divisor
 */
static void dw_uart_init(DW_UART_REG *uart_reg_ptr, uint32_t baud_divisor, UART_DPS_FORMAT *dps, UART_HW_FLOW_CONTROL hwfc)
{
	dw_uart_software_reset(uart_reg_ptr);

	dw_uart_set_hwfc(uart_reg_ptr, hwfc);
	dw_uart_set_dps(uart_reg_ptr, dps);
	dw_uart_set_baud(uart_reg_ptr, baud_divisor);

	uart_reg_ptr->IIR = 0x1;	/** enable uart fifo (FCR IIR is the same) */
	uart_reg_ptr->IER = 0x0;	/** disable all uart interrupt */
}

/**
 * \brief	set designware uart baudrate
 * \param	uart_info_ptr	uart information structure pointer
 */
static void dw_uart_flush_output(DEV_UART_INFO *uart_info_ptr)
{
	uint32_t i;
	char *p_charbuf;

	DW_UART_CTRL *uart_ctrl_ptr = (DW_UART_CTRL_PTR)(uart_info_ptr->uart_ctrl);
	DW_UART_REG *uart_reg_ptr = (DW_UART_REG_PTR)(uart_ctrl_ptr->dw_uart_regbase);

	if (uart_info_ptr->tx_buf.buf != NULL) {
		p_charbuf = (char *)(uart_info_ptr->tx_buf.buf);
		for (i = uart_info_ptr->tx_buf.ofs; i < uart_info_ptr->tx_buf.len; i ++) {
			dw_uart_psnd_chr(uart_reg_ptr, p_charbuf[i]);
		}
		/* clear transmit buffer */
		uart_info_ptr->tx_buf.buf = NULL;
		uart_info_ptr->tx_buf.len = 0;
		uart_info_ptr->tx_buf.ofs = 0;
	}
	/* wait until transmit fifo is empty */
	while ((uart_reg_ptr->USR & DW_UART_USR_TFE) == 0);
	while (uart_reg_ptr->USR & DW_UART_USR_BUSY);
}

/**
 * \brief	disable designware uart send or receive interrupt
 * \param[in]	DEV_UART_INFO 	*uart_info_ptr
 * \param[in]	cbrtn		control code of callback routine of send or receive
 */
static void dw_uart_dis_cbr(DEV_UART_INFO *uart_info_ptr, uint32_t cbrtn)
{
	DW_UART_CTRL *uart_ctrl_ptr = (DW_UART_CTRL_PTR)(uart_info_ptr->uart_ctrl);
	DW_UART_REG *uart_reg_ptr = (DW_UART_REG_PTR)(uart_ctrl_ptr->dw_uart_regbase);

	switch (cbrtn) {
		case DW_UART_RDY_SND:
			uart_reg_ptr->IER &= ~DW_UART_IER_XMIT_EMPTY;
			uart_ctrl_ptr->int_status &= ~DW_UART_TXINT_ENABLE;
			break;
		case DW_UART_RDY_RCV:
			uart_reg_ptr->IER &= ~DW_UART_IER_DATA_AVAIL;
			uart_ctrl_ptr->int_status &= ~DW_UART_RXINT_ENABLE;
			break;
		default:
			break;
	}
	if (uart_ctrl_ptr->int_status & DW_UART_GINT_ENABLE) {
		if ((uart_ctrl_ptr->int_status & (DW_UART_RXINT_ENABLE|DW_UART_TXINT_ENABLE)) == 0) {
			int_disable(uart_ctrl_ptr->intno);
			uart_ctrl_ptr->int_status &= ~DW_UART_GINT_ENABLE;
		}
	}
}

/**
 * \brief	enable DesignWare UART send or receive interrupt
 * \param[in]	DEV_UART_INFO 	*uart_info_ptr
 * \param[in]	cbrtn		control code of callback routine of send or receive
 */
static void dw_uart_ena_cbr(DEV_UART_INFO *uart_info_ptr, uint32_t cbrtn)
{
	DW_UART_CTRL *uart_ctrl_ptr = (DW_UART_CTRL_PTR)(uart_info_ptr->uart_ctrl);
	DW_UART_REG *uart_reg_ptr = (DW_UART_REG_PTR)(uart_ctrl_ptr->dw_uart_regbase);

	switch (cbrtn) {
		case DW_UART_RDY_SND:
			uart_ctrl_ptr->int_status |= DW_UART_TXINT_ENABLE;
			uart_reg_ptr->IER |= DW_UART_IER_XMIT_EMPTY;
			break;
		case DW_UART_RDY_RCV:
			uart_ctrl_ptr->int_status |= DW_UART_RXINT_ENABLE;
			uart_reg_ptr->IER |= DW_UART_IER_DATA_AVAIL;
			break;
		default:
			break;
	}
	if ((uart_ctrl_ptr->int_status & DW_UART_GINT_ENABLE) == 0) {
		if (uart_ctrl_ptr->int_status & (DW_UART_RXINT_ENABLE|DW_UART_TXINT_ENABLE)) {
			uart_ctrl_ptr->int_status |= DW_UART_GINT_ENABLE;
			int_enable(uart_ctrl_ptr->intno);
		}
	}
}

/**
 * \brief	enable designware uart interrupt
 * \param	uart_info_ptr	uart information structure pointer
 */
static void dw_uart_enable_interrupt(DEV_UART_INFO *uart_info_ptr)
{
	DW_UART_CTRL *uart_ctrl_ptr = (DW_UART_CTRL_PTR)(uart_info_ptr->uart_ctrl);

	int_handler_install(uart_ctrl_ptr->intno, uart_ctrl_ptr->dw_uart_int_handler);
	uart_ctrl_ptr->int_status |= DW_UART_GINT_ENABLE;
	int_enable(uart_ctrl_ptr->intno);	/** enable uart interrupt */
}
/**
 * \brief	disable designware uart interrupt
 * \param	uart_info_ptr	uart information structure pointer
 */
static void dw_uart_disable_interrupt(DEV_UART_INFO *uart_info_ptr)
{
	DW_UART_CTRL *uart_ctrl_ptr = (DW_UART_CTRL_PTR)(uart_info_ptr->uart_ctrl);

	/** disable uart send&receive interrupt after disable uart interrupt */
	dw_uart_dis_cbr(uart_info_ptr, DW_UART_RDY_SND);
	dw_uart_dis_cbr(uart_info_ptr, DW_UART_RDY_RCV);
	/* disable uart interrupt */
	int_disable(uart_ctrl_ptr->intno);
	uart_ctrl_ptr->int_status &= ~(DW_UART_GINT_ENABLE|DW_UART_TXINT_ENABLE|DW_UART_RXINT_ENABLE);
}

/** enable designware uart */
static void dw_uart_enable_device(DEV_UART_INFO *uart_info_ptr)
{
	DW_UART_CTRL *uart_ctrl_ptr = (DW_UART_CTRL_PTR)(uart_info_ptr->uart_ctrl);
	DW_UART_REG *uart_reg_ptr = (DW_UART_REG_PTR)(uart_ctrl_ptr->dw_uart_regbase);

	if ((uart_info_ptr->status & DEV_ENABLED) == 0) {
		dw_uart_set_baud(uart_reg_ptr, uart_info_ptr->baudrate);
		uart_info_ptr->status |= DEV_ENABLED;
	}
}

/** disable designware uart */
static void dw_uart_disable_device(DEV_UART_INFO *uart_info_ptr)
{
	DW_UART_CTRL *uart_ctrl_ptr = (DW_UART_CTRL_PTR)(uart_info_ptr->uart_ctrl);
	DW_UART_REG *uart_reg_ptr = (DW_UART_REG_PTR)(uart_ctrl_ptr->dw_uart_regbase);

	if ((uart_info_ptr->status & DEV_ENABLED) == DEV_ENABLED) {
		dw_uart_set_baud(uart_reg_ptr, 0);
		uart_info_ptr->status &= ~DEV_ENABLED;
	}
}

/** abort current interrupt transmit transfer */
static void dw_uart_abort_tx(DEV_UART *uart_obj)
{
	DEV_UART_INFO *uart_info_ptr = &(uart_obj->uart_info);
	DW_UART_CTRL *uart_ctrl_ptr = (DW_UART_CTRL_PTR)(uart_info_ptr->uart_ctrl);

	if (uart_ctrl_ptr->int_status & DW_UART_TXINT_ENABLE) {
		dw_uart_dis_cbr(uart_info_ptr, DW_UART_RDY_SND);
		uart_info_ptr->status |= DEV_IN_TX_ABRT;
		if (uart_info_ptr->uart_cbs.tx_cb != NULL) {
			uart_info_ptr->uart_cbs.tx_cb(uart_obj);
		}
		uart_info_ptr->status &= ~(DEV_IN_TX_ABRT);
	}
}

/** abort current interrupt receive transfer */
static void dw_uart_abort_rx(DEV_UART *uart_obj)
{
	DEV_UART_INFO *uart_info_ptr = &(uart_obj->uart_info);
	DW_UART_CTRL *uart_ctrl_ptr = (DW_UART_CTRL_PTR)(uart_info_ptr->uart_ctrl);

	if (uart_ctrl_ptr->int_status & DW_UART_RXINT_ENABLE) {
		dw_uart_dis_cbr(uart_info_ptr, DW_UART_RDY_RCV);
		uart_info_ptr->status |= DEV_IN_RX_ABRT;
		if (uart_info_ptr->uart_cbs.rx_cb != NULL) {
			uart_info_ptr->uart_cbs.rx_cb(uart_obj);
		}
		uart_info_ptr->status &= ~(DEV_IN_RX_ABRT);
	}
}

/** Get available transmit fifo count */
static int32_t dw_uart_get_txavail(DW_UART_CTRL *uart_ctrl_ptr)
{
	int32_t tx_avail = 0;
	DW_UART_REG *uart_reg_ptr = (DW_UART_REG *)(uart_ctrl_ptr->dw_uart_regbase);

	if (uart_ctrl_ptr->tx_fifo_len <= 1) {
		if (dw_uart_putready(uart_reg_ptr) == 1) {
			tx_avail = 1;
		} else {
			tx_avail = 0;
		}
	} else {
		tx_avail = uart_ctrl_ptr->tx_fifo_len - uart_reg_ptr->TFL;
	}
	return tx_avail;
}

/** Get available receive fifo count */
static int32_t dw_uart_get_rxavail(DW_UART_CTRL *uart_ctrl_ptr)
{
	int32_t rx_avail = 0;
	DW_UART_REG *uart_reg_ptr = (DW_UART_REG *)(uart_ctrl_ptr->dw_uart_regbase);

	if (uart_ctrl_ptr->rx_fifo_len <= 1) {
		if (dw_uart_getready(uart_reg_ptr) == 1) {
			rx_avail = 1;
		} else {
			rx_avail = 0;
		}
	} else {
		rx_avail = uart_reg_ptr->RFL;
	}
	return rx_avail;
}


/** @} end of group DEVICE_DW_UART_STATIC */

/**
 * \brief	open a designware uart device
 * \param[in]	uart_obj	uart object structure pointer
 * \param[in]	baud		baudrate to initialized
 * \retval	E_OK	Open successfully without any issues
 * \retval	E_OPNED	If device was opened before with different baudrate, then return E_OPNED
 * \retval	E_OBJ	Device object is not valid
 * \retval	E_PAR	Parameter is not valid
 * \retval	E_NOSPT	Open settings are not supported
 */
int32_t dw_uart_open (DEV_UART *uart_obj, uint32_t baud)
{
	int32_t ercd = E_OK;
	DEV_UART_INFO *uart_info_ptr = &(uart_obj->uart_info);

	/* START ERROR CHECK */
	VALID_CHK_UART_INFO_OBJECT(uart_info_ptr);
	DW_UART_CHECK_EXP(baud>0, E_PAR);
	/* END OF ERROR CHECK */

	uart_info_ptr->opn_cnt ++;
	if (uart_info_ptr->opn_cnt > 1) { /* opened before */
		if (baud == uart_info_ptr->baudrate) { /* baudrate is the same */
			return E_OK;
		} else { /* open with different baudrate */
			return E_OPNED;
		}
	}

	int32_t baud_divisor = 0;

	DW_UART_CTRL *uart_ctrl_ptr = (DW_UART_CTRL_PTR)(uart_info_ptr->uart_ctrl);
	DW_UART_REG *uart_reg_ptr = (DW_UART_REG_PTR)(uart_ctrl_ptr->dw_uart_regbase);

	/* Get FIFO Length */
	uart_ctrl_ptr->tx_fifo_len = dw_uart_get_txfifo_len(uart_reg_ptr);
	uart_ctrl_ptr->rx_fifo_len = dw_uart_get_rxfifo_len(uart_reg_ptr);

	/** init uart */
	uart_info_ptr->baudrate = baud;
	baud_divisor = DW_UART_BAUD2DIV(uart_ctrl_ptr->dw_apb_bus_freq, baud);
	uart_info_ptr->dps_format = dps_format_default;
	uart_info_ptr->hwfc = hwfc_default;
	dw_uart_init(uart_reg_ptr, baud_divisor, &(uart_info_ptr->dps_format), uart_info_ptr->hwfc);

	uart_info_ptr->status = DEV_ENABLED;
	uart_info_ptr->extra = NULL;

	/**
	 * uart interrupt related init
	 */
	dw_uart_disable_interrupt(uart_info_ptr);
	/** install uart interrupt into system */
	int_handler_install(uart_ctrl_ptr->intno, uart_ctrl_ptr->dw_uart_int_handler);

	memset(&(uart_info_ptr->tx_buf), 0, sizeof(DEV_BUFFER));
	memset(&(uart_info_ptr->rx_buf), 0, sizeof(DEV_BUFFER));
	memset(&(uart_info_ptr->uart_cbs), 0, sizeof(DEV_UART_CBS));

error_exit:
	return ercd;
}

/**
 * \brief	close a DesignWare UART device
 * \param[in]	uart_obj	uart object structure pointer
 * \retval	E_OK	Open successfully without any issues
 * \retval	E_OPNED	Device is still opened, the device opn_cnt decreased by 1
 * \retval	E_OBJ	Device object is not valid
 */
int32_t dw_uart_close (DEV_UART *uart_obj)
{
	int32_t ercd = E_OK;
	DEV_UART_INFO *uart_info_ptr = &(uart_obj->uart_info);

	/* START ERROR CHECK */
	VALID_CHK_UART_INFO_OBJECT(uart_info_ptr);
	DW_UART_CHECK_EXP(uart_info_ptr->opn_cnt > 0, E_OK);
	/* END OF ERROR CHECK */

	uart_info_ptr->opn_cnt --;
	if (uart_info_ptr->opn_cnt == 0) {
		dw_uart_disable_interrupt(uart_info_ptr);
		dw_uart_abort_tx(uart_obj);
		dw_uart_abort_rx(uart_obj);
		dw_uart_flush_output(uart_info_ptr);
		memset(&(uart_info_ptr->tx_buf), 0, sizeof(DEV_BUFFER));
		memset(&(uart_info_ptr->rx_buf), 0, sizeof(DEV_BUFFER));
		memset(&(uart_info_ptr->uart_cbs), 0, sizeof(DEV_UART_CBS));
		dw_uart_disable_device(uart_info_ptr);
		uart_info_ptr->status = 0;
		uart_info_ptr->extra = NULL;
	} else {
		ercd = E_OPNED;
	}

error_exit:
	return ercd;
}

/**
 * \brief	control uart by ctrl command
 * \param[in]	uart_obj	uart object structure pointer
 * \param[in]	ctrl_cmd	control command code to do specific uart work
 * \param[in,out]	param	parameters used to control uart or return something
 * \retval	E_OK	Control device successfully
 * \retval	E_CLSED	Device is not opened
 * \retval	E_DIS	Device is disabled
 * \retval	E_OBJ	Device object is not valid or not exists
 * \retval	E_PAR	Parameter is not valid for current control command
 * \retval	E_SYS	Control device failed, due to hardware issues
 * \retval	E_CTX	Control device failed, due to different reasons like in transfer state
 * \retval	E_NOSPT	Control command is not supported or not valid
 */
int32_t dw_uart_control (DEV_UART *uart_obj, uint32_t ctrl_cmd, void *param)
{
	int32_t ercd = E_OK;
	DEV_UART_INFO *uart_info_ptr = &(uart_obj->uart_info);

	/* START ERROR CHECK */
	VALID_CHK_UART_INFO_OBJECT(uart_info_ptr);
	DW_UART_CHECK_EXP(uart_info_ptr->opn_cnt > 0, E_CLSED);
	/* END OF ERROR CHECK */

	uint32_t val32; /** to receive unsigned int value */
	int32_t baud_divisor = 0;
	DEV_BUFFER *devbuf;
	UART_DPS_FORMAT *dps_ptr;
	UART_HW_FLOW_CONTROL hwfc_local;

	DW_UART_CTRL *uart_ctrl_ptr = (DW_UART_CTRL_PTR)(uart_info_ptr->uart_ctrl);
	DW_UART_REG *uart_reg_ptr = (DW_UART_REG_PTR)(uart_ctrl_ptr->dw_uart_regbase);

	/* check whether current device is disabled */
	if ((uart_info_ptr->status & DEV_ENABLED) == 0) {
		/** When device is disabled,
		 * only UART_CMD_ENA_DEV, UART_CMD_DIS_DEV, UART_CMD_GET_STATUS
		 * are available, other commands will return E_SYS
		 */
		if ((ctrl_cmd != UART_CMD_ENA_DEV) && \
			(ctrl_cmd != UART_CMD_DIS_DEV) && \
			(ctrl_cmd != UART_CMD_GET_STATUS) ) {
			return E_SYS;
		}
	}

	switch (ctrl_cmd) {
		case UART_CMD_SET_BAUD:
			val32 = (uint32_t)param;
			DW_UART_CHECK_EXP(val32>0, E_PAR);
			if (val32 != uart_info_ptr->baudrate) {
				baud_divisor = DW_UART_BAUD2DIV(uart_ctrl_ptr->dw_apb_bus_freq, val32);
				dw_uart_set_baud(uart_reg_ptr, baud_divisor);
				uart_info_ptr->baudrate = val32;
			}
			break;
		case UART_CMD_GET_STATUS:
			DW_UART_CHECK_EXP((param!=NULL) && CHECK_ALIGN_4BYTES(param), E_PAR);
			*((int32_t *)param) = uart_info_ptr->status;
			break;
		case UART_CMD_ENA_DEV:
			dw_uart_enable_device(uart_info_ptr);
			break;
		case UART_CMD_DIS_DEV:
			dw_uart_disable_device(uart_info_ptr);
			break;
		case UART_CMD_FLUSH_OUTPUT:
			dw_uart_flush_output(uart_info_ptr);
			break;
		case UART_CMD_GET_RXAVAIL:
			DW_UART_CHECK_EXP((param!=NULL) && CHECK_ALIGN_4BYTES(param), E_PAR);
			*((int32_t *)param) = dw_uart_get_rxavail(uart_ctrl_ptr);
			break;
		case UART_CMD_GET_TXAVAIL:
			DW_UART_CHECK_EXP((param!=NULL) && CHECK_ALIGN_4BYTES(param), E_PAR);
			*((int32_t *)param) = dw_uart_get_txavail(uart_ctrl_ptr);
			break;
		case UART_CMD_BREAK_SET:
			dw_uart_set_break(uart_reg_ptr);
			break;
		case UART_CMD_BREAK_CLR:
			dw_uart_clr_break(uart_reg_ptr);
			break;
		case UART_CMD_SET_DPS_FORMAT:
			DW_UART_CHECK_EXP(param!=NULL, E_PAR);
			dps_ptr = (UART_DPS_FORMAT *)param;
			if (dw_uart_set_dps(uart_reg_ptr, dps_ptr) == 0) {
				uart_info_ptr->dps_format = *dps_ptr;
			} else {
				ercd = E_PAR;
			}
			break;
		case UART_CMD_SET_HWFC:
			hwfc_local = (UART_HW_FLOW_CONTROL)param;
			DW_UART_CHECK_EXP(((hwfc_local>=UART_FC_NONE) && (hwfc_local<=UART_FC_BOTH)), E_PAR);
			dw_uart_set_hwfc(uart_reg_ptr, hwfc_local);
			uart_info_ptr->hwfc = hwfc_local;
			break;
		case UART_CMD_SET_TXCB:
			DW_UART_CHECK_EXP(CHECK_ALIGN_4BYTES(param), E_PAR);
			uart_info_ptr->uart_cbs.tx_cb = param;
			break;
		case UART_CMD_SET_RXCB:
			DW_UART_CHECK_EXP(CHECK_ALIGN_4BYTES(param), E_PAR);
			uart_info_ptr->uart_cbs.rx_cb = param;
			break;
		case UART_CMD_SET_ERRCB:
			DW_UART_CHECK_EXP(CHECK_ALIGN_4BYTES(param), E_PAR);
			uart_info_ptr->uart_cbs.err_cb = param;
			break;
		case UART_CMD_ABORT_TX:
			dw_uart_abort_tx(uart_obj);
			break;
		case UART_CMD_ABORT_RX:
			dw_uart_abort_rx(uart_obj);
			break;
		case UART_CMD_SET_TXINT:
			val32 = (uint32_t)param;
			if (val32 == 0) {
				dw_uart_dis_cbr(uart_info_ptr, DW_UART_RDY_SND);
			} else {
				dw_uart_ena_cbr(uart_info_ptr, DW_UART_RDY_SND);
			}
			break;
		case UART_CMD_SET_RXINT:
			val32 = (uint32_t)param;
			if (val32 == 0) {
				dw_uart_dis_cbr(uart_info_ptr, DW_UART_RDY_RCV);
			} else {
				dw_uart_ena_cbr(uart_info_ptr, DW_UART_RDY_RCV);
			}
			break;
		case UART_CMD_SET_TXINT_BUF:
			DW_UART_CHECK_EXP(CHECK_ALIGN_4BYTES(param), E_PAR);
			if (param != NULL) {
				devbuf = (DEV_BUFFER *)param;
				uart_info_ptr->tx_buf = *devbuf;
				uart_info_ptr->tx_buf.ofs = 0;
			} else {
				uart_info_ptr->tx_buf.buf = NULL;
				uart_info_ptr->tx_buf.len = 0;
				uart_info_ptr->tx_buf.ofs = 0;
			}
			break;
		case UART_CMD_SET_RXINT_BUF:
			DW_UART_CHECK_EXP(CHECK_ALIGN_4BYTES(param), E_PAR);
			if (param != NULL) {
				devbuf = (DEV_BUFFER *)param;
				uart_info_ptr->rx_buf = *devbuf;
				uart_info_ptr->rx_buf.ofs = 0;
			} else {
				uart_info_ptr->rx_buf.buf = NULL;
				uart_info_ptr->rx_buf.len = 0;
				uart_info_ptr->rx_buf.ofs = 0;
			}
			break;
		default:
			ercd = E_NOSPT;
			break;
	}

error_exit:
	return ercd;
}

/**
 * \brief	send data through DesignWare UART
 * \param[in]	uart_obj	uart object structure pointer
 * \param[in]	data		data that need to send (data must be char type)
 * \param[in]	len		data length need to send
 * \retval	>0	Byte count that was successfully sent for poll method
 * \retval	E_OBJ	Device object is not valid or not exists
 * \retval	E_PAR	Parameter is not valid for current control command
 * \retval	E_SYS	Can't write data to hardware due to hardware issues
 */
int32_t dw_uart_write (DEV_UART *uart_obj, const void *data, uint32_t len)
{
	int32_t ercd = E_OK;
	DEV_UART_INFO *uart_info_ptr = &(uart_obj->uart_info);

	/* START ERROR CHECK */
	VALID_CHK_UART_INFO_OBJECT(uart_info_ptr);
	DW_UART_CHECK_EXP(uart_info_ptr->opn_cnt > 0, E_CLSED);
	DW_UART_CHECK_EXP(uart_info_ptr->status & DEV_ENABLED, E_SYS);
	DW_UART_CHECK_EXP(data!=NULL, E_PAR);
	DW_UART_CHECK_EXP(len>0, E_PAR);
	/* END OF ERROR CHECK */

	int32_t i = 0;
	const char *p_charbuf = (const char *)data;

	DW_UART_CTRL *uart_ctrl_ptr = (DW_UART_CTRL_PTR)(uart_info_ptr->uart_ctrl);
	DW_UART_REG *uart_reg_ptr = (DW_UART_REG_PTR)(uart_ctrl_ptr->dw_uart_regbase);

	while (i < len) {
		dw_uart_psnd_chr(uart_reg_ptr, p_charbuf[i++]);
	}
	ercd = i;

error_exit:
	return ercd;
}

/**
 * \brief	read data through DesignWare UART
 * \param[in]	uart_obj	uart object structure pointer
 * \param[out]	data		data that need to read (data must be char type)
 * \param[in]	len		data count need to read
 * \retval	>0	Byte count that was successfully sent for poll method
 * \retval	E_OBJ	Device object is not valid or not exists
 * \retval	E_PAR	Parameter is not valid for current control command
 * \retval	E_SYS	Can't receive data from hardware due to hardware issues, such as device is disabled
 */
int32_t dw_uart_read (DEV_UART *uart_obj, void *data, uint32_t len)
{
	int32_t ercd = E_OK;
	DEV_UART_INFO *uart_info_ptr = &(uart_obj->uart_info);

	/* START ERROR CHECK */
	VALID_CHK_UART_INFO_OBJECT(uart_info_ptr);
	DW_UART_CHECK_EXP(uart_info_ptr->opn_cnt > 0, E_CLSED);
	DW_UART_CHECK_EXP(uart_info_ptr->status & DEV_ENABLED, E_SYS);
	DW_UART_CHECK_EXP(data!=NULL, E_PAR);
	DW_UART_CHECK_EXP(len>0, E_PAR);
	/* END OF ERROR CHECK */

	int32_t i = 0;
	char *p_charbuf = (char *)data;

	DW_UART_CTRL *uart_ctrl_ptr = (DW_UART_CTRL_PTR)(uart_info_ptr->uart_ctrl);
	DW_UART_REG *uart_reg_ptr = (DW_UART_REG_PTR)(uart_ctrl_ptr->dw_uart_regbase);

	while (i < len) {
		p_charbuf[i++] = dw_uart_prcv_chr(uart_reg_ptr);
	}
	ercd = i;

error_exit:
	return ercd;
}

/**
 * \brief	DesignWare UART interrupt processing routine
 * \param[in]	uart_obj	uart object structure pointer
 * \param[in]	ptr		extra information
 */
void dw_uart_isr (DEV_UART *uart_obj, void *ptr)
{
	int32_t ercd = E_OK;
	DEV_UART_INFO *uart_info_ptr = &(uart_obj->uart_info);

	/* START ERROR CHECK */
	VALID_CHK_UART_INFO_OBJECT(uart_info_ptr);
	/* END OF ERROR CHECK */

	uint32_t uart_int_status; /** uart interrupt status */
	volatile uint32_t temp; /** read error status to clear interrupt */
	DEV_BUFFER *buf_ptr;
	char *p_charbuf;

	DW_UART_CTRL *uart_ctrl_ptr = (DW_UART_CTRL_PTR)(uart_info_ptr->uart_ctrl);
	DW_UART_REG *uart_reg_ptr = (DW_UART_REG_PTR)(uart_ctrl_ptr->dw_uart_regbase);

	/** get uart interrupt status */
	uart_int_status = (uart_reg_ptr->IIR) & DW_UART_IIR_INT_ID_MASK;

	switch (uart_int_status) {
		case DW_UART_IIR_MDM_STATUS:
			temp = (volatile uint32_t)(uart_reg_ptr->MSR);
			break;
		case DW_UART_IIR_LINE_STATUS:
			if (uart_info_ptr->uart_cbs.err_cb) {
				uart_info_ptr->uart_cbs.err_cb(uart_info_ptr);
			}
			temp = (volatile uint32_t)(uart_reg_ptr->LSR);
			break;
		case DW_UART_IIR_XMIT_EMPTY:
			buf_ptr = &(uart_info_ptr->tx_buf);
			p_charbuf = (char *)buf_ptr->buf;
			if (p_charbuf != NULL) {
				while (dw_uart_putready(uart_reg_ptr)) {
					dw_uart_putchar(uart_reg_ptr, p_charbuf[buf_ptr->ofs]);
					buf_ptr->ofs ++;
					if (buf_ptr->ofs >= buf_ptr->len) {
						dw_uart_dis_cbr(uart_info_ptr, DW_UART_RDY_SND);
						if (uart_info_ptr->uart_cbs.tx_cb) {
							uart_info_ptr->uart_cbs.tx_cb(uart_obj);
						}
						/* clear the send buffer pointer */
						memset(buf_ptr, 0, sizeof(DEV_BUFFER));
						break;
					}
				}
			} else {
				if (uart_info_ptr->uart_cbs.tx_cb) {
					uart_info_ptr->uart_cbs.tx_cb(uart_obj);
				}
			}
			break;
		case DW_UART_IIR_RX_TIMEOUT:
			temp = dw_uart_getchar(uart_reg_ptr);
			break;
		case DW_UART_IIR_DATA_AVAIL:
			buf_ptr = &(uart_info_ptr->rx_buf);
			p_charbuf = (char *)buf_ptr->buf;
			if (p_charbuf != NULL) {
				while (dw_uart_getready(uart_reg_ptr)) {
					p_charbuf[buf_ptr->ofs] = (char)dw_uart_getchar(uart_reg_ptr);
					buf_ptr->ofs ++;
					if (buf_ptr->ofs >= buf_ptr->len) {
						dw_uart_dis_cbr(uart_info_ptr, DW_UART_RDY_RCV);
						if (uart_info_ptr->uart_cbs.rx_cb) {
							uart_info_ptr->uart_cbs.rx_cb(uart_obj);
						}
						/* clear the send buffer pointer */
						memset(buf_ptr, 0, sizeof(DEV_BUFFER));
						break;
					}
				}
			} else {
				if (uart_info_ptr->uart_cbs.rx_cb) {
					uart_info_ptr->uart_cbs.rx_cb(uart_obj);
				}
			}
			break;
		default:
			temp = (volatile uint32_t)(uart_reg_ptr->USR);
			break;
	}

error_exit:
	return;
}
