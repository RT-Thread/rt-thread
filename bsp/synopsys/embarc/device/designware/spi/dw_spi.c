/* ------------------------------------------
 * Copyright (c) 2017, Synopsys, Inc. All rights reserved.

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
 * \version 2017.03
 * \date 2014-06-25
 * \author Huaqi Fang(Huaqi.Fang@synopsys.com)
--------------------------------------------- */

/**
 * \defgroup	DEVICE_DW_SPI	Designware SPI Driver
 * \ingroup	DEVICE_DW
 * \brief	Designware SPI Driver Implementation
 */

/**
 * \file
 * \brief	DesignWare SPI driver implementation based on device hal layer definition (\ref dev_spi.h)
 * \ingroup	DEVICE_DW_SPI
 */
#include <string.h>

#include "inc/embARC_toolchain.h"
#include "inc/embARC_error.h"

#include "inc/arc/arc_exception.h"

#include "device/designware/spi/dw_spi_hal.h"
#include "device/designware/spi/dw_spi.h"

/**
 * \defgroup	DEVICE_DW_SPI_DEFINES	DesignWare SPI Driver Macros
 * \ingroup	DEVICE_DW_SPI
 * \brief	DesignWare SPI driver macros used in spi driver
 * @{
 */
/** check expressions used in DesignWare SPI driver implementation */
#define DW_SPI_CHECK_EXP(EXPR, ERROR_CODE)		CHECK_EXP(EXPR, ercd, ERROR_CODE, error_exit)

/** convert DesignWare frequence to divisor */
#define DW_SPI_FREQ2DV(perifreq, spifreq)		((perifreq) / (spifreq))

#ifndef DISABLE_DEVICE_OBJECT_VALID_CHECK
/** valid check of spi info object */
#define VALID_CHK_SPI_INFO_OBJECT(spiinfo_obj_ptr)		{			\
			DW_SPI_CHECK_EXP((spiinfo_obj_ptr)!=NULL, E_OBJ);		\
			DW_SPI_CHECK_EXP(((spiinfo_obj_ptr)->spi_ctrl)!=NULL, E_OBJ);	\
 		}
#endif

/**
 * \defgroup	DEVICE_DW_SPI_DEF_CBR	DesignWare SPI Interrupt Callback Routine Select Marcos
 * \ingroup	DEVICE_DW_SPI_DEFINES
 * \brief	DesignWare SPI interrupt callback routines select macros definitions
 * @{
 */
#define DW_SPI_RDY_SND					(1U)	/*!< ready to send callback */
#define DW_SPI_RDY_RCV					(2U)	/*!< ready to receive callback */
#define DW_SPI_RDY_XFER					(3U)	/*!< ready to transfer callback */
/** @} */

/** @} */

/**
 * \defgroup	DEVICE_DW_SPI_STATIC	DesignWare SPI Driver Static Functions
 * \ingroup	DEVICE_DW_SPI
 * \brief	Static or inline functions, variables for DesignWare SPI handle spi operations,
 * 	only used in this file.
 * @{
 */

/** Disable designware spi device */
Inline void dw_spi_disable(DW_SPI_REG *spi_reg_ptr)
{
/** disable spi operations, then program spi control regs is possible */
	spi_reg_ptr->SSIENR = DW_SPI_SSI_DISABLE;
}
/** Enable designware spi device */
Inline void dw_spi_enable(DW_SPI_REG *spi_reg_ptr)
{
	spi_reg_ptr->SSIENR = DW_SPI_SSI_ENABLE;
}

/** Clear all designware spi interrupt */
Inline void dw_spi_clear_interrupt_all(DW_SPI_REG *spi_reg_ptr)
{
	(void)spi_reg_ptr->ICR;
}

/** test whether spi is busy, busy return 1, else 0 */
Inline int32_t dw_spi_busy(DW_SPI_REG *spi_reg_ptr)
{
	return ((spi_reg_ptr->SR & DW_SPI_SR_BUSY) != 0);
}
/** test whether spi is ready to send, 1 ready, 0 not ready */
Inline int32_t dw_spi_putready(DW_SPI_REG *spi_reg_ptr)
{
	return ((spi_reg_ptr->SR & DW_SPI_SR_TFNF) != 0);
}
/** test whether spi is read to receive, 1 ready, 0 not ready */
Inline int32_t dw_spi_getready(DW_SPI_REG *spi_reg_ptr)
{
	return ((spi_reg_ptr->SR & DW_SPI_SR_RFNE) != 0);
}
/** write data to spi send fifo */
Inline void dw_spi_putdata(DW_SPI_REG *spi_reg_ptr, int32_t data)
{
	spi_reg_ptr->DATAREG = (uint32_t)data;
}
/** read data from spi receive fifo, return data received */
Inline int32_t dw_spi_getdata(DW_SPI_REG *spi_reg_ptr)
{
	return (int32_t)spi_reg_ptr->DATAREG;
}
/**
 * \brief	send data by spi when available,
 * 	mostly used in interrupt method, non-blocked function
 * \param[in]	spi_reg_ptr	spi register structure pointer
 * \param[in]	data		data to be sent
 * \retval	E_OK		send successfully
 * \retval	E_OBJ		not ready to send data
 */
Inline int32_t dw_spi_snd_dat(DW_SPI_REG *spi_reg_ptr, int32_t data)
{
	if (dw_spi_putready(spi_reg_ptr)) {
		dw_spi_putdata(spi_reg_ptr, data);
		return E_OK;
	}
	return E_OBJ;
}
/**
 * \brief	receive one char from spi,
 * 	mostly used in interrupt routine, non-blocked function
 * \param[in]	spi_reg_ptr	spi register structure pointer
 * \return	data received by the spi
 */
Inline int32_t dw_spi_rcv_dat(DW_SPI_REG *spi_reg_ptr)
{
	return dw_spi_getdata(spi_reg_ptr);
}
/**
 * \brief	send char by spi in poll method, blocked function
 * \param[in]	spi_reg_ptr	spi register structure pointer
 * \param[in]	data		data to be sent
 */
Inline void dw_spi_psnd_dat(DW_SPI_REG *spi_reg_ptr, int32_t data)
{
	/** wait until spi is ready to send */
	while (!dw_spi_putready(spi_reg_ptr)); /* blocked */
	/** send char */
	dw_spi_putdata(spi_reg_ptr, data);
}
/**
 * \brief	receive one char from spi in poll method, blocked function
 * \param[in]	spi_reg_ptr	spi register structure pointer
 * \return	data received by the spi
 */
Inline int32_t dw_spi_prcv_dat(DW_SPI_REG *spi_reg_ptr)
{
	/** wait until spi is ready to receive */
	while (!dw_spi_getready(spi_reg_ptr)); /* blocked */
	/** receive data */
	return dw_spi_getdata(spi_reg_ptr);
}

/** Reset designware FIFO by disable spi device, then enable device */
Inline void dw_spi_reset_fifo(DW_SPI_REG *spi_reg_ptr)
{
	dw_spi_disable(spi_reg_ptr);
	dw_spi_enable(spi_reg_ptr);
}

/** Enable designware spi bit interrupt with mask */
Inline void dw_spi_unmask_interrupt(DW_SPI_REG *spi_reg_ptr, uint32_t mask)
{
	spi_reg_ptr->IMR |= mask;
}

/** Disable designware spi bit interrupt with mask */
Inline void dw_spi_mask_interrupt(DW_SPI_REG *spi_reg_ptr, uint32_t mask)
{
	spi_reg_ptr->IMR &= ~mask;
}

/** Set designware spi device frequency */
Inline void dw_spi_set_freq(DW_SPI_CTRL *spi_ctrl_ptr, uint32_t freq)
{
	uint32_t sck_divisor;
	DW_SPI_REG *spi_reg_ptr = spi_ctrl_ptr->dw_spi_regs;

	dw_spi_disable(spi_reg_ptr);

	sck_divisor = DW_SPI_FREQ2DV(spi_ctrl_ptr->dw_apb_bus_freq, freq);
	spi_reg_ptr->BAUDR = sck_divisor;
	dw_spi_enable(spi_reg_ptr);
}

/** Set designware spi device data frame size */
static int32_t dw_spi_set_dfs(DW_SPI_REG *spi_reg_ptr, uint32_t dfs)
{
	uint32_t ctrl0_reg;
	if ((dfs <= 3) || (dfs > 16)) return -1;

	dw_spi_disable(spi_reg_ptr);
	ctrl0_reg = spi_reg_ptr->CTRLR0;
	ctrl0_reg &= ~(DW_SPI_CTRLR0_DFS_MASK);
	spi_reg_ptr->CTRLR0 = ctrl0_reg | (dfs-1);
	dw_spi_enable(spi_reg_ptr);

	return 0;
}

/** Choose proper designware spi clock mode setting value */
Inline uint32_t dw_spi_select_clockmode(uint32_t clk_mode)
{
	return (clk_mode << DW_SPI_CTRLR0_SC_OFS);
}

/** Set designware spi clock mode */
Inline int32_t dw_spi_set_clockmode(DW_SPI_REG *spi_reg_ptr, uint32_t clk_mode)
{
	if (clk_mode > SPI_CPOL_1_CPHA_1) {
		return -1;
	}
	dw_spi_disable(spi_reg_ptr);
	spi_reg_ptr->CTRLR0 &= ~(DW_SPI_CTRLR0_SC_MASK);
	spi_reg_ptr->CTRLR0 |= dw_spi_select_clockmode(clk_mode);
	dw_spi_enable(spi_reg_ptr);
	return 0;
}

/** Select a spi slave with slv_line */
Inline int32_t dw_spi_select_slave(DW_SPI_REG *spi_reg_ptr, uint32_t slv_line)
{
	/* check if spi busy */
	if (dw_spi_busy(spi_reg_ptr)) return -1;

	spi_reg_ptr->SER = 1<<slv_line;
	return 0;
}

/** Deselect a spi device */
Inline int32_t dw_spi_deselect_slave(DW_SPI_REG *spi_reg_ptr, uint32_t slv_line)
{
	/* check if spi busy */
	if (dw_spi_busy(spi_reg_ptr)) return -1;

	spi_reg_ptr->SER = 0;
	return 0;
}

Inline void dw_spi_flush_tx(DW_SPI_REG *spi_reg_ptr)
{
	dw_spi_reset_fifo(spi_reg_ptr);
}

Inline void dw_spi_flush_rx(DW_SPI_REG *spi_reg_ptr)
{
	dw_spi_reset_fifo(spi_reg_ptr);
}

/** Get TX FIFO Length.
 *    calculate spi fifo length using fifo threshold method
 *  If you attempt to set bits [7:0] of this register to
 *  a value greater than or equal to the depth of the FIFO,
 *  this field is not written and retains its current value.
 */
static uint32_t dw_spi_get_txfifo_len(DW_SPI_REG *spi_reg_ptr)
{
	uint32_t fifo_thr_lev_tmp, left, right, i;

	fifo_thr_lev_tmp = spi_reg_ptr->TXFTLR;

	if (fifo_thr_lev_tmp != 0) {
		left = fifo_thr_lev_tmp;
	} else {
		left = DW_SPI_MIN_FIFO_LENGTH;
	}
	right = DW_SPI_MAX_FIFO_LENGTH + 1;

	for (i = left; i <= right; i++) {
		spi_reg_ptr->TXFTLR = i;
		if (spi_reg_ptr->TXFTLR != i) {
			break;
		}
	}
	spi_reg_ptr->TXFTLR = fifo_thr_lev_tmp; /* restore old fifo threshold */

	return (i);
}

/** Get RX FIFO Length */
static uint32_t dw_spi_get_rxfifo_len(DW_SPI_REG *spi_reg_ptr)
{
	uint32_t fifo_thr_lev_tmp, left, right, i;

	fifo_thr_lev_tmp = spi_reg_ptr->RXFTLR;

	if (fifo_thr_lev_tmp != 0) {
		left = fifo_thr_lev_tmp;
	} else {
		left = DW_SPI_MIN_FIFO_LENGTH;
	}
	right = DW_SPI_MAX_FIFO_LENGTH + 1;

	for (i = left; i <= right; i++) {
		spi_reg_ptr->RXFTLR = i;
		if (spi_reg_ptr->RXFTLR != i) {
			break;
		}
	}
	spi_reg_ptr->RXFTLR = fifo_thr_lev_tmp; /* restore old fifo threshold */

	return (i);
}

/** Init Designware SPI Hardware */
static void dw_spi_hw_init(DW_SPI_CTRL *spi_ctrl_ptr, uint32_t clk_mode, uint32_t dfs)
{
	uint32_t ctrl0_reg = 0;
	DW_SPI_REG *spi_reg_ptr = spi_ctrl_ptr->dw_spi_regs;

	dw_spi_disable(spi_reg_ptr);

	/* Clear interrupts */
	ctrl0_reg = spi_reg_ptr->ICR;
	/* Mask all interrupts */
	spi_reg_ptr->IMR = 0;

	ctrl0_reg = DW_SPI_CTRLR0_FRF_MOTOROLA | DW_SPI_TMOD_TRANSMIT_RECEIVE \
			| dw_spi_select_clockmode(clk_mode) | (dfs - 1) | DW_SPI_CTRLR0_SLV_OE_ENABLE;
	spi_reg_ptr->CTRLR0 = ctrl0_reg;
	spi_reg_ptr->CTRLR1 = 0;

	/* deselect slaves */
	spi_reg_ptr->SER = 0;

	/* Set threshold values for both tx and rx */
	spi_reg_ptr->TXFTLR = 0;
	spi_reg_ptr->RXFTLR = 0;

	dw_spi_enable(spi_reg_ptr);
}

/** enable designware spi */
static void dw_spi_enable_device(DEV_SPI_INFO *spi_info_ptr)
{
	DW_SPI_CTRL *spi_ctrl_ptr = (DW_SPI_CTRL *)(spi_info_ptr->spi_ctrl);
	DW_SPI_REG *spi_reg_ptr = (DW_SPI_REG *)(spi_ctrl_ptr->dw_spi_regs);

	if ((spi_info_ptr->status & DEV_ENABLED) == 0) {
		dw_spi_enable(spi_reg_ptr);
		spi_info_ptr->status |= DEV_ENABLED;
	}
}

/** disable designware spi */
static void dw_spi_disable_device(DEV_SPI_INFO *spi_info_ptr)
{
	DW_SPI_CTRL *spi_ctrl_ptr = (DW_SPI_CTRL *)(spi_info_ptr->spi_ctrl);
	DW_SPI_REG *spi_reg_ptr = (DW_SPI_REG *)(spi_ctrl_ptr->dw_spi_regs);

	dw_spi_disable(spi_reg_ptr);
	spi_info_ptr->status &= ~DEV_ENABLED;
}


/**
 * \brief	disable designware spi send or receive interrupt
 * \param[in]	DEV_SPI_INFO 	*spi_info_ptr
 * \param[in]	cbrtn		control code of callback routine of send or receive
 */
static int32_t dw_spi_dis_cbr(DEV_SPI_INFO *spi_info_ptr, uint32_t cbrtn)
{
	DW_SPI_CTRL *spi_ctrl_ptr = (DW_SPI_CTRL *)(spi_info_ptr->spi_ctrl);
	int32_t ercd = E_OK;

	if ((spi_info_ptr->status & DW_SPI_IN_XFER) != 0) { /* only in transfer need do check */
		switch (cbrtn) {
			case DW_SPI_RDY_SND:
				DW_SPI_CHECK_EXP((spi_info_ptr->status & DW_SPI_IN_XFER) == DW_SPI_IN_TX, E_CTX);
				spi_info_ptr->status &= ~(DW_SPI_IN_TX);
				break;
			case DW_SPI_RDY_RCV:
				DW_SPI_CHECK_EXP((spi_info_ptr->status & DW_SPI_IN_XFER) == DW_SPI_IN_RX, E_CTX);
				spi_info_ptr->status &= ~(DW_SPI_IN_RX);
				break;
			case DW_SPI_RDY_XFER:
				DW_SPI_CHECK_EXP((spi_info_ptr->status & DW_SPI_IN_XFER) == DW_SPI_IN_XFER, E_CTX);
				spi_info_ptr->status &= ~(DW_SPI_IN_XFER);
				break;
			default:
				break;
		}
	}

	dw_spi_mask_interrupt(spi_ctrl_ptr->dw_spi_regs, DW_SPI_IMR_XFER);

	if (spi_ctrl_ptr->int_status & DW_SPI_GINT_ENABLE) {
		int_disable(spi_ctrl_ptr->intno);
		spi_ctrl_ptr->int_status &= ~DW_SPI_GINT_ENABLE;
	}

error_exit:
	return ercd;
}

/**
 * \brief	enable DesignWare SPI send or receive interrupt
 * \param[in]	DEV_SPI_INFO 	*spi_info_ptr
 * \param[in]	cbrtn		control code of callback routine of send or receive
 */
static int32_t dw_spi_ena_cbr(DEV_SPI_INFO *spi_info_ptr, uint32_t cbrtn)
{
	DW_SPI_CTRL *spi_ctrl_ptr = (DW_SPI_CTRL *)(spi_info_ptr->spi_ctrl);
	int32_t ercd = E_OK;

	DW_SPI_CHECK_EXP((spi_info_ptr->status & DW_SPI_IN_XFER) == 0, E_CTX);
	switch (cbrtn) {
		case DW_SPI_RDY_SND:
			spi_info_ptr->status |= DW_SPI_IN_TX;
			break;
		case DW_SPI_RDY_RCV:
			spi_info_ptr->status |= DW_SPI_IN_RX;
			break;
		case DW_SPI_RDY_XFER:
			spi_info_ptr->status |= DW_SPI_IN_XFER;
			break;
		default:
			break;
	}
	dw_spi_unmask_interrupt(spi_ctrl_ptr->dw_spi_regs, DW_SPI_IMR_XFER);

	if ((spi_ctrl_ptr->int_status & DW_SPI_GINT_ENABLE) == 0) {
		spi_ctrl_ptr->int_status |= DW_SPI_GINT_ENABLE;
		int_enable(spi_ctrl_ptr->intno);
	}

error_exit:
	return ercd;
}

/**
 * \brief	enable designware spi interrupt
 * \param	spi_info_ptr	spi information structure pointer
 */
static void dw_spi_enable_interrupt(DEV_SPI_INFO *spi_info_ptr)
{
	DW_SPI_CTRL *spi_ctrl_ptr = (DW_SPI_CTRL *)(spi_info_ptr->spi_ctrl);

	int_handler_install(spi_ctrl_ptr->intno, spi_ctrl_ptr->dw_spi_int_handler);
	spi_ctrl_ptr->int_status |= DW_SPI_GINT_ENABLE;
	int_enable(spi_ctrl_ptr->intno);	/** enable spi interrupt */
}
/**
 * \brief	disable designware spi interrupt
 * \param	spi_info_ptr	spi information structure pointer
 */
static void dw_spi_disable_interrupt(DEV_SPI_INFO *spi_info_ptr)
{
	DW_SPI_CTRL *spi_ctrl_ptr = (DW_SPI_CTRL *)(spi_info_ptr->spi_ctrl);

	/** disable spi send&receive interrupt after disable spi interrupt */
	dw_spi_dis_cbr(spi_info_ptr, DW_SPI_RDY_SND);
	dw_spi_dis_cbr(spi_info_ptr, DW_SPI_RDY_RCV);
	dw_spi_dis_cbr(spi_info_ptr, DW_SPI_RDY_XFER);
	/* disable spi interrupt */
	dw_spi_mask_interrupt(spi_ctrl_ptr->dw_spi_regs, DW_SPI_IMR_XFER);
	spi_info_ptr->status &= ~DW_SPI_IN_XFER;
	int_disable(spi_ctrl_ptr->intno);
	spi_ctrl_ptr->int_status &= ~(DW_SPI_GINT_ENABLE);
}

static void dw_spi_reset_device(DEV_SPI_INFO *spi_info_ptr)
{
	DW_SPI_CTRL *spi_ctrl_ptr = (DW_SPI_CTRL *)(spi_info_ptr->spi_ctrl);
	DW_SPI_REG *spi_reg_ptr = (DW_SPI_REG *)(spi_ctrl_ptr->dw_spi_regs);

	dw_spi_disable_device(spi_info_ptr);
	dw_spi_disable_interrupt(spi_info_ptr);
	dw_spi_clear_interrupt_all(spi_reg_ptr);
	dw_spi_enable_device(spi_info_ptr);
}

/** abort current interrupt transmit transfer */
static int32_t dw_spi_abort_tx(DEV_SPI *spi_obj)
{
	DEV_SPI_INFO *spi_info_ptr = &(spi_obj->spi_info);
	int32_t ercd = E_OK;

	DW_SPI_CHECK_EXP((spi_info_ptr->status & DW_SPI_IN_XFER) != 0, E_OK);
	DW_SPI_CHECK_EXP((spi_info_ptr->status & DW_SPI_IN_XFER) == DW_SPI_IN_TX, E_CTX);

	dw_spi_dis_cbr(spi_info_ptr, DW_SPI_RDY_SND);
	spi_info_ptr->status |= DEV_IN_TX_ABRT;
	if (spi_info_ptr->spi_cbs.tx_cb != NULL) {
		spi_info_ptr->spi_cbs.tx_cb(spi_obj);
	}
	spi_info_ptr->status &= ~(DEV_IN_TX_ABRT);

error_exit:
	return ercd;
}

/** abort current interrupt receive transfer */
static int32_t dw_spi_abort_rx(DEV_SPI *spi_obj)
{
	DEV_SPI_INFO *spi_info_ptr = &(spi_obj->spi_info);
	int32_t ercd = E_OK;

	DW_SPI_CHECK_EXP((spi_info_ptr->status & DW_SPI_IN_XFER) != 0, E_OK);
	DW_SPI_CHECK_EXP((spi_info_ptr->status & DW_SPI_IN_XFER) == DW_SPI_IN_RX, E_CTX);

	dw_spi_dis_cbr(spi_info_ptr, DW_SPI_RDY_RCV);
	spi_info_ptr->status |= DEV_IN_RX_ABRT;
	if (spi_info_ptr->spi_cbs.rx_cb != NULL) {
		spi_info_ptr->spi_cbs.rx_cb(spi_obj);
	}
	spi_info_ptr->status &= ~(DEV_IN_RX_ABRT);

error_exit:
	return ercd;
}

/** abort current interrupt transfer */
static int32_t dw_spi_abort_xfer(DEV_SPI *spi_obj)
{
	DEV_SPI_INFO *spi_info_ptr = &(spi_obj->spi_info);
	int32_t ercd = E_OK;

	DW_SPI_CHECK_EXP((spi_info_ptr->status & DW_SPI_IN_XFER) != 0, E_OK);
	DW_SPI_CHECK_EXP((spi_info_ptr->status & DW_SPI_IN_XFER) == DW_SPI_IN_XFER, E_CTX);

	dw_spi_dis_cbr(spi_info_ptr, DW_SPI_RDY_XFER);
	spi_info_ptr->status |= DEV_IN_XFER_ABRT;
	if (spi_info_ptr->spi_cbs.xfer_cb != NULL) {
		spi_info_ptr->spi_cbs.xfer_cb(spi_obj);
	}
	spi_info_ptr->status &= ~(DEV_IN_XFER_ABRT);

error_exit:
	return ercd;
}

/** Get available transmit fifo count */
static int32_t dw_spi_get_txavail(DW_SPI_CTRL *spi_ctrl_ptr)
{
	int32_t tx_avail = 0;
	DW_SPI_REG *spi_reg_ptr = (DW_SPI_REG *)(spi_ctrl_ptr->dw_spi_regs);

#if DW_SPI_CALC_FIFO_LEN_ENABLE
	if (spi_ctrl_ptr->tx_fifo_len <= 1) {
		if (dw_spi_putready(spi_reg_ptr) == 1) {
			tx_avail = 1;
		} else {
			tx_avail = 0;
		}
	} else
#endif
	{
		tx_avail = spi_ctrl_ptr->tx_fifo_len - spi_reg_ptr->TXFLR;
	}
	return tx_avail;
}

/** Get available receive fifo count */
static int32_t dw_spi_get_rxavail(DW_SPI_CTRL *spi_ctrl_ptr)
{
	int32_t rx_avail = 0;
	DW_SPI_REG *spi_reg_ptr = (DW_SPI_REG *)(spi_ctrl_ptr->dw_spi_regs);

#if DW_SPI_CALC_FIFO_LEN_ENABLE
	if (spi_ctrl_ptr->rx_fifo_len <= 1) {
		if (dw_spi_getready(spi_reg_ptr) == 1) {
			rx_avail = 1;
		} else {
			rx_avail = 0;
		}
	} else
#endif
	{
		rx_avail = spi_reg_ptr->RXFLR;
	}
	return rx_avail;
}

static uint32_t dw_spi_tx_max(DW_SPI_CTRL *spi_ctrl_ptr)
{
	uint32_t tx_left, tx_room;
	DW_SPI_TRANSFER *xfer = &(spi_ctrl_ptr->dw_xfer);

	tx_left = (xfer->xfer_len - xfer->tx_idx) / xfer->nbytes;
	tx_room = dw_spi_get_txavail(spi_ctrl_ptr);

	return (tx_left < tx_room) ? tx_left : tx_room;
}

static uint32_t dw_spi_rx_max(DW_SPI_CTRL *spi_ctrl_ptr)
{
	uint32_t rx_left, rx_room;
	DW_SPI_TRANSFER *xfer = &(spi_ctrl_ptr->dw_xfer);

	rx_left = (xfer->xfer_len - xfer->rx_idx) / xfer->nbytes;
	rx_room = dw_spi_get_rxavail(spi_ctrl_ptr);

	return (rx_left < rx_room) ? rx_left : rx_room;
}

Inline int32_t dw_spi_rx_end(DW_SPI_CTRL *spi_ctrl_ptr)
{
	DW_SPI_TRANSFER *xfer = &(spi_ctrl_ptr->dw_xfer);

	return (xfer->rx_idx >= xfer->xfer_len);
}

Inline int32_t dw_spi_tx_end(DW_SPI_CTRL *spi_ctrl_ptr)
{
	DW_SPI_TRANSFER *xfer = &(spi_ctrl_ptr->dw_xfer);

	return (xfer->tx_idx >= xfer->xfer_len);
}

/** 1 for end, 0 for not end */
Inline int32_t dw_spi_xfer_end(DW_SPI_CTRL *spi_ctrl_ptr)
{
	return (dw_spi_tx_end(spi_ctrl_ptr) && dw_spi_rx_end(spi_ctrl_ptr));
}

static int32_t dw_spi_writer(DEV_SPI_INFO *spi_info_ptr)
{
	DW_SPI_CTRL *spi_ctrl_ptr = (DW_SPI_CTRL_PTR)(spi_info_ptr->spi_ctrl);
	DW_SPI_TRANSFER *dw_xfer = &(spi_ctrl_ptr->dw_xfer);
	DW_SPI_REG *spi_reg_ptr = (DW_SPI_REG *)(spi_ctrl_ptr->dw_spi_regs);
	uint32_t tx_max = dw_spi_tx_max(spi_ctrl_ptr);
	int32_t tx_w;
	uint32_t tx_cnt = tx_max;

	if (dw_xfer->tx_xfer == NULL) {
		return 0;
	}
	while (tx_max) {
		if (dw_xfer->tx_xfer->tx_idx >= dw_xfer->tx_xfer->tot_len) {
			dw_xfer->tx_xfer = dw_xfer->tx_xfer->next;
			if (dw_xfer->tx_xfer == NULL) {
				break;
			}
		}
		if ( (dw_xfer->tx_xfer->tx_idx >= dw_xfer->tx_xfer->tx_ofs) \
			&& (dw_xfer->tx_xfer->tx_idx < dw_xfer->tx_xfer->tx_totlen)) {
			if (dw_xfer->nbytes == 1) {
				tx_w = (int32_t)(*(int8_t *)(dw_xfer->tx_xfer->tx_buf));
			} else {
				tx_w = (int32_t)(*(int16_t *)(dw_xfer->tx_xfer->tx_buf));
			}
			dw_xfer->tx_xfer->tx_buf += dw_xfer->nbytes;
		} else {
			tx_w = spi_info_ptr->dummy;
		}
		dw_spi_putdata(spi_reg_ptr, tx_w);
		dw_xfer->tx_xfer->tx_idx += dw_xfer->nbytes;
		dw_xfer->tx_idx += dw_xfer->nbytes;
		tx_max --;
	}
	return ((tx_cnt-tx_max) * dw_xfer->nbytes);
}

static int32_t dw_spi_reader(DEV_SPI_INFO *spi_info_ptr)
{
	DW_SPI_CTRL *spi_ctrl_ptr = (DW_SPI_CTRL_PTR)(spi_info_ptr->spi_ctrl);
	DW_SPI_TRANSFER *dw_xfer = &(spi_ctrl_ptr->dw_xfer);
	DW_SPI_REG *spi_reg_ptr = (DW_SPI_REG *)(spi_ctrl_ptr->dw_spi_regs);
	uint32_t rx_max = dw_spi_rx_max(spi_ctrl_ptr);
	int32_t rx_w;
	uint32_t rx_cnt = rx_max;

	if (dw_xfer->rx_xfer == NULL) {
		return 0;
	}
	while (rx_max) {
		if (dw_xfer->rx_xfer->rx_idx >= dw_xfer->rx_xfer->tot_len) {
			dw_xfer->rx_xfer = dw_xfer->rx_xfer->next;
			if (dw_xfer->rx_xfer == NULL) {
				break;
			}
		}
		rx_w = dw_spi_getdata(spi_reg_ptr);
		if ( (dw_xfer->rx_xfer->rx_idx >= dw_xfer->rx_xfer->rx_ofs) \
			&& (dw_xfer->rx_xfer->rx_idx < dw_xfer->rx_xfer->rx_totlen) ) {
			if (dw_xfer->nbytes == 1) {
				*(int8_t *)(dw_xfer->rx_xfer->rx_buf) = rx_w;
			} else {
				*(int16_t *)(dw_xfer->rx_xfer->rx_buf) = rx_w;
			}
			dw_xfer->rx_xfer->rx_buf += dw_xfer->nbytes;
		}
		dw_xfer->rx_xfer->rx_idx += dw_xfer->nbytes;
		dw_xfer->rx_idx += dw_xfer->nbytes;
		rx_max --;
	}
	return ((rx_cnt-rx_max) * dw_xfer->nbytes);
}

Inline uint32_t dw_spi_nbytes(uint32_t dfs)
{
	uint32_t nbytes = 1;

	if (dfs > 8) nbytes = 2;
	return nbytes;
}

static void dw_spi_init_transfer(DW_SPI_CTRL *spi_ctrl_ptr, DEV_SPI_TRANSFER *xfer, uint32_t dfs)
{
	DW_SPI_TRANSFER *dw_xfer= &(spi_ctrl_ptr->dw_xfer);
	uint32_t tot_len = 0;

	dw_xfer->tx_xfer = xfer;
	dw_xfer->rx_xfer = xfer;
	dw_xfer->tx_idx = 0;
	dw_xfer->rx_idx = 0;
	dw_xfer->nbytes = dw_spi_nbytes(dfs);

	/** Calculate all transfer length */
	while (xfer) {
		DEV_SPI_XFER_INIT(xfer);
		tot_len += xfer->tot_len;
		xfer = xfer->next;
	}
	dw_xfer->xfer_len = tot_len;
}

/* Check buffer align status, 0 for aligned, -1 for not-aligned */
static int32_t dw_spi_chk_xfer_aligned(DEV_SPI_TRANSFER *xfer, uint32_t dfs)
{
	uint32_t align_bytes = 1;
	if (xfer == NULL) return -1;

	if (dfs > 8) {
		align_bytes = 2;
	} else {
		return 0;
	}

	while (xfer) {
		/* check tx buffer align status */
		if (xfer->tx_len != 0) {
			if (xfer->tx_len % align_bytes) return -1;
			if (xfer->tx_ofs % align_bytes) return -1;
			if (!CHECK_ALIGN_BYTES(xfer->tx_buf, align_bytes)) return -1;
		}
		/* check tx buffer align status */
		if (xfer->rx_len != 0) {
			if (xfer->rx_len % align_bytes) return -1;
			if (xfer->rx_ofs % align_bytes) return -1;
			if (!CHECK_ALIGN_BYTES(xfer->rx_buf, align_bytes)) return -1;
		}
		xfer = xfer->next;
	}
	return 0;
}

static uint32_t dw_spi_poll_transfer(DEV_SPI_INFO *spi_info_ptr)
{
	uint32_t len = 0;
	DW_SPI_CTRL *spi_ctrl_ptr = (DW_SPI_CTRL_PTR)(spi_info_ptr->spi_ctrl);

	spi_info_ptr->status |= DEV_IN_XFER;
	while (!dw_spi_xfer_end(spi_ctrl_ptr)) {
		len += dw_spi_writer(spi_info_ptr);
		len += dw_spi_reader(spi_info_ptr);
	}
	spi_info_ptr->status &= ~DEV_IN_XFER;

	return len>>1;
}

/** @} */

/**
 * \brief	open a designware spi device
 * \param[in]	spi_obj	spi object pointer
 * \param[in]	mode	spi working mode (master or slave)
 * \param[in]	param	parameter, for master, param is the freq, for slave, param is dfs
 * \retval	E_OK	Open successfully without any issues
 * \retval	E_OPNED	If device was opened before with different parameters,
 *			then just increase the \ref dev_spi_info::opn_cnt "opn_cnt" and return \ref E_OPNED
 * \retval	E_OBJ	Device object is not valid
 * \retval	E_SYS	Device is opened for different mode before, if you want to open it with different mode, you need to fully close it first.
 * \retval	E_PAR	Parameter is not valid
 * \retval	E_NOSPT	Open settings are not supported
 */
int32_t dw_spi_open (DEV_SPI *spi_obj, uint32_t mode, uint32_t param)
{
	int32_t ercd = E_OK;
	uint32_t param2check;
	uint32_t clk_mode, dfs_val;
	uint32_t support_modes;
	DEV_SPI_INFO *spi_info_ptr = &(spi_obj->spi_info);

	/* START ERROR CHECK */
	VALID_CHK_SPI_INFO_OBJECT(spi_info_ptr);
	DW_SPI_CHECK_EXP((mode==DEV_MASTER_MODE)||(mode==DEV_SLAVE_MODE), E_PAR);
	if (mode == DEV_SLAVE_MODE) { /* clock mode should be in the enum structure */
		DW_SPI_CHECK_EXP((param>=SPI_CPOL_0_CPHA_0) && (param<=SPI_CPOL_1_CPHA_1), E_PAR);
	} else { /* frequence should > 0 */
		DW_SPI_CHECK_EXP(param>0, E_PAR);
	}
	/* END OF ERROR CHECK */

	DW_SPI_CTRL *spi_ctrl_ptr = (DW_SPI_CTRL_PTR)(spi_info_ptr->spi_ctrl);

	/* Check supported modes, master or slave */
	support_modes = spi_ctrl_ptr->support_modes;
	DW_SPI_CHECK_EXP( (((support_modes)&DW_SPI_MASTER_SUPPORTED)&&(mode == DEV_MASTER_MODE)) || \
				(((support_modes)&DW_SPI_SLAVE_SUPPORTED)&&(mode == DEV_SLAVE_MODE)), E_NOSPT);

	/** Check opened before use case */
	if (spi_info_ptr->opn_cnt > 0) {
		if (mode != spi_info_ptr->mode) {
			/* current working mode is different from passing mode */
			return E_SYS;
		}
		if (mode == DEV_MASTER_MODE) { /* param is freq when as master */
			param2check = spi_info_ptr->freq;
		} else { /* param is clk_mode when as slave */
			param2check = spi_info_ptr->clk_mode;
		}
		spi_info_ptr->opn_cnt ++;
		if (param != param2check) { /* open with different speed mode */
			return E_OPNED;
		} else {
			return E_OK;
		}
	}
	/* auto increase open count */
	spi_info_ptr->opn_cnt ++;

	/* Do FIFO Length get before init */
#if DW_SPI_CALC_FIFO_LEN_ENABLE
	spi_ctrl_ptr->tx_fifo_len = dw_spi_get_txfifo_len(spi_ctrl_ptr->dw_spi_regs);
	spi_ctrl_ptr->rx_fifo_len = dw_spi_get_rxfifo_len(spi_ctrl_ptr->dw_spi_regs);
#endif
	/* hardware init */
	spi_info_ptr->mode = mode;
	clk_mode = SPI_CLK_MODE_DEFAULT;
	dfs_val = SPI_DFS_DEFAULT;
	if (mode == DEV_SLAVE_MODE) {
		clk_mode = param;
	}
	spi_info_ptr->dfs = dfs_val;
	spi_info_ptr->clk_mode = clk_mode;
	dw_spi_hw_init(spi_ctrl_ptr, clk_mode, dfs_val);
	if (mode == DEV_MASTER_MODE) { /* Deselect all slaves, and set frequence */
		dw_spi_deselect_slave(spi_ctrl_ptr->dw_spi_regs, 0);
		dw_spi_set_freq(spi_ctrl_ptr, param);
		spi_info_ptr->freq = param;
	}

	spi_info_ptr->status = DEV_ENABLED;
	spi_info_ptr->extra = NULL;
	spi_info_ptr->slave = SPI_SLAVE_NOT_SELECTED;
	spi_info_ptr->dummy = 0xff;

	spi_ctrl_ptr->int_status = 0;
	dw_spi_init_transfer(spi_ctrl_ptr, NULL, dfs_val);

	/** install spi interrupt into system */
	dw_spi_disable_interrupt(spi_info_ptr);
	int_handler_install(spi_ctrl_ptr->intno, spi_ctrl_ptr->dw_spi_int_handler);
	memset(&(spi_info_ptr->xfer), 0, sizeof(DEV_SPI_TRANSFER));
	memset(&(spi_info_ptr->spi_cbs), 0, sizeof(DEV_SPI_CBS));

error_exit:
	return ercd;
}

/**
 * \brief	close a DesignWare SPI device
 * \param[in]	spi_obj	spi object pointer
 * \retval	E_OK	Close successfully without any issues(including scenario that device is already closed)
 * \retval	E_OPNED	Device is still opened, the device \ref dev_spi_info::opn_cnt "opn_cnt" decreased by 1
 * \retval	E_OBJ	Device object is not valid
 */
int32_t dw_spi_close (DEV_SPI *spi_obj)
{
	int32_t ercd = E_OK;
	DEV_SPI_INFO *spi_info_ptr = &(spi_obj->spi_info);

	/* START ERROR CHECK */
	VALID_CHK_SPI_INFO_OBJECT(spi_info_ptr);
	DW_SPI_CHECK_EXP(spi_info_ptr->opn_cnt > 0, E_OK);
	/* END OF ERROR CHECK */

	spi_info_ptr->opn_cnt --;
	if (spi_info_ptr->opn_cnt == 0) {
		DW_SPI_CTRL *spi_ctrl_ptr = (DW_SPI_CTRL *)(spi_info_ptr->spi_ctrl);

		dw_spi_disable_interrupt(spi_info_ptr);
		dw_spi_abort_tx(spi_obj);
		dw_spi_abort_rx(spi_obj);
		memset(&(spi_info_ptr->xfer), 0, sizeof(DEV_SPI_TRANSFER));
		memset(&(spi_info_ptr->spi_cbs), 0, sizeof(DEV_SPI_CBS));
		memset(&(spi_ctrl_ptr->dw_xfer), 0, sizeof(DW_SPI_TRANSFER));
		dw_spi_disable_device(spi_info_ptr);
		spi_info_ptr->status = DEV_DISABLED;
		spi_info_ptr->extra = NULL;
	} else {
		ercd = E_OPNED;
	}

error_exit:
	return ercd;
}

/**
 * \brief	control spi by ctrl command
 * \param[in]		spi_obj		spi object pointer
 * \param[in]		ctrl_cmd	control command code to do specific spi work
 * \param[in,out]	param		parameters used to control spi or return something
 * \retval	E_OK	Control device successfully
 * \retval	E_CLSED	Device is not opened
 * \retval	E_OBJ	Device object is not valid or not exists
 * \retval	E_PAR	Parameter is not valid for current control command
 * \retval	E_SYS	Control device failed, due to hardware issues, such as device is disabled
 * \retval	E_CTX	Control device failed, due to different reasons like in transfer state
 * \retval	E_NOSPT	Control command is not supported or not valid
 */
int32_t dw_spi_control (DEV_SPI *spi_obj, uint32_t ctrl_cmd, void *param)
{
	int32_t ercd = E_OK;
	DEV_SPI_INFO *spi_info_ptr = &(spi_obj->spi_info);

	/* START ERROR CHECK */
	VALID_CHK_SPI_INFO_OBJECT(spi_info_ptr);
	DW_SPI_CHECK_EXP(spi_info_ptr->opn_cnt > 0, E_CLSED);
	/* END OF ERROR CHECK */

	uint32_t val32; /** to receive unsigned int value */
	DEV_BUFFER *devbuf;

	DW_SPI_CTRL *spi_ctrl_ptr = (DW_SPI_CTRL *)(spi_info_ptr->spi_ctrl);
	DW_SPI_REG *spi_reg_ptr = (DW_SPI_REG *)(spi_ctrl_ptr->dw_spi_regs);
	DEV_SPI_TRANSFER *spi_xfer = &(spi_info_ptr->xfer);

	/* check whether current device is disabled */
	if ((spi_info_ptr->status & DEV_ENABLED) == 0) {
		/** When device is disabled,
		 * only SPI_CMD_ENA_DEV, SPI_CMD_DIS_DEV, SPI_CMD_GET_STATUS, SPI_CMD_RESET
		 * are available, other commands will return E_SYS
		 */
		if ((ctrl_cmd != SPI_CMD_ENA_DEV) && \
			(ctrl_cmd != SPI_CMD_DIS_DEV) && \
			(ctrl_cmd != SPI_CMD_GET_STATUS) && \
			(ctrl_cmd != SPI_CMD_RESET) ) {
			return E_SYS;
		}
	}

	switch (ctrl_cmd) {
		/* Commmon commands for both master and slave mode */
		case SPI_CMD_GET_STATUS:
			DW_SPI_CHECK_EXP((param!=NULL) && CHECK_ALIGN_4BYTES(param), E_PAR);
			*((int32_t *)param) = spi_info_ptr->status;
			break;
		case SPI_CMD_SET_CLK_MODE:
			DW_SPI_CHECK_EXP((spi_info_ptr->status & DEV_IN_XFER) == 0, E_CTX);
			val32 = (uint32_t)param;
			DW_SPI_CHECK_EXP((val32>=SPI_CPOL_0_CPHA_0) && (val32<=SPI_CPOL_1_CPHA_1), E_PAR);
			if (dw_spi_set_clockmode(spi_reg_ptr, val32) == 0) {
				spi_info_ptr->clk_mode = val32;
			} else {
				ercd = E_SYS;
			}
			break;
		case SPI_CMD_ENA_DEV:
			dw_spi_enable_device(spi_info_ptr);
			break;
		case SPI_CMD_DIS_DEV:
			dw_spi_disable_device(spi_info_ptr);
			break;
		case SPI_CMD_RESET:
			dw_spi_reset_device(spi_info_ptr);
			break;
		case SPI_CMD_FLUSH_TX:
			DW_SPI_CHECK_EXP((spi_info_ptr->status & DEV_IN_XFER) == 0, E_CTX);
			dw_spi_flush_tx(spi_reg_ptr);
			break;
		case SPI_CMD_FLUSH_RX:
			DW_SPI_CHECK_EXP((spi_info_ptr->status & DEV_IN_XFER) == 0, E_CTX);
			dw_spi_flush_rx(spi_reg_ptr);
			break;
		case SPI_CMD_SET_DFS:
			DW_SPI_CHECK_EXP((spi_info_ptr->status & DEV_IN_XFER) == 0, E_CTX);
			val32 = (uint32_t)param;
			DW_SPI_CHECK_EXP(val32>0, E_PAR);
			if (dw_spi_set_dfs(spi_reg_ptr, val32) == 0) {
				spi_info_ptr->dfs = val32;
			} else {
				ercd = E_SYS;
			}
			break;
		case SPI_CMD_SET_DUMMY_DATA:
			val32 = (uint32_t)param;
			spi_info_ptr->dummy = val32;
			break;
		case SPI_CMD_GET_RXAVAIL: /* Notice in bytes unit */
			DW_SPI_CHECK_EXP((param!=NULL) && CHECK_ALIGN_4BYTES(param), E_PAR);
			*((int32_t *)param) = dw_spi_get_rxavail(spi_ctrl_ptr) * dw_spi_nbytes(spi_info_ptr->dfs);
			break;
		case SPI_CMD_GET_TXAVAIL: /* Notice in bytes unit */
			DW_SPI_CHECK_EXP((param!=NULL) && CHECK_ALIGN_4BYTES(param), E_PAR);
			*((int32_t *)param) = dw_spi_get_txavail(spi_ctrl_ptr) * dw_spi_nbytes(spi_info_ptr->dfs);
			break;
		case SPI_CMD_SET_TXCB:
			DW_SPI_CHECK_EXP(CHECK_ALIGN_4BYTES(param), E_PAR);
			spi_info_ptr->spi_cbs.tx_cb = param;
			break;
		case SPI_CMD_SET_RXCB:
			DW_SPI_CHECK_EXP(CHECK_ALIGN_4BYTES(param), E_PAR);
			spi_info_ptr->spi_cbs.rx_cb = param;
			break;
		case SPI_CMD_SET_XFERCB:
			DW_SPI_CHECK_EXP(CHECK_ALIGN_4BYTES(param), E_PAR);
			spi_info_ptr->spi_cbs.xfer_cb = param;
			break;
		case SPI_CMD_SET_ERRCB:
			DW_SPI_CHECK_EXP(CHECK_ALIGN_4BYTES(param), E_PAR);
			spi_info_ptr->spi_cbs.err_cb = param;
			break;
		case SPI_CMD_ABORT_TX:
			ercd = dw_spi_abort_tx(spi_obj);
			break;
		case SPI_CMD_ABORT_RX:
			ercd = dw_spi_abort_rx(spi_obj);
			break;
		case SPI_CMD_ABORT_XFER:
			ercd = dw_spi_abort_xfer(spi_obj);
			break;
		case SPI_CMD_SET_TXINT:
			val32 = (uint32_t)param;
			if (val32 == 0) {
				ercd = dw_spi_dis_cbr(spi_info_ptr, DW_SPI_RDY_SND);
			} else {
				ercd = dw_spi_ena_cbr(spi_info_ptr, DW_SPI_RDY_SND);
			}
			break;
		case SPI_CMD_SET_RXINT:
			val32 = (uint32_t)param;
			if (val32 == 0) {
				ercd = dw_spi_dis_cbr(spi_info_ptr, DW_SPI_RDY_RCV);
			} else {
				ercd = dw_spi_ena_cbr(spi_info_ptr, DW_SPI_RDY_RCV);
			}
			break;
		case SPI_CMD_SET_TXINT_BUF:
			DW_SPI_CHECK_EXP(CHECK_ALIGN_4BYTES(param), E_PAR);
			DW_SPI_CHECK_EXP((spi_info_ptr->status & DEV_IN_XFER) == 0, E_CTX);
			if (param != NULL) {
				devbuf = (DEV_BUFFER *)param;
				DEV_SPI_XFER_SET_TXBUF(spi_xfer, devbuf->buf, 0, devbuf->len);
				DEV_SPI_XFER_SET_RXBUF(spi_xfer, NULL, devbuf->len, 0);
				DEV_SPI_XFER_SET_NEXT(spi_xfer, NULL);
				DW_SPI_CHECK_EXP(dw_spi_chk_xfer_aligned(spi_xfer, spi_info_ptr->dfs) == 0, E_PAR);
				dw_spi_init_transfer(spi_ctrl_ptr, spi_xfer, spi_info_ptr->dfs);
			} else {
				DEV_SPI_XFER_SET_TXBUF(spi_xfer, NULL, 0, 0);
				DEV_SPI_XFER_SET_RXBUF(spi_xfer, NULL, 0, 0);
				DEV_SPI_XFER_SET_NEXT(spi_xfer, NULL);
				dw_spi_init_transfer(spi_ctrl_ptr, NULL, spi_info_ptr->dfs);
			}
			break;
		case SPI_CMD_SET_RXINT_BUF:
			DW_SPI_CHECK_EXP(CHECK_ALIGN_4BYTES(param), E_PAR);
			DW_SPI_CHECK_EXP((spi_info_ptr->status & DEV_IN_XFER) == 0, E_CTX);
			if (param != NULL) {
				devbuf = (DEV_BUFFER *)param;
				DEV_SPI_XFER_SET_TXBUF(spi_xfer, NULL, devbuf->len, 0);
				DEV_SPI_XFER_SET_RXBUF(spi_xfer, devbuf->buf, 0, devbuf->len);
				DEV_SPI_XFER_SET_NEXT(spi_xfer, NULL);
				/* Check transfer align */
				DW_SPI_CHECK_EXP(dw_spi_chk_xfer_aligned(spi_xfer, spi_info_ptr->dfs) == 0, E_PAR);
				dw_spi_init_transfer(spi_ctrl_ptr, spi_xfer, spi_info_ptr->dfs);
			} else {
				DEV_SPI_XFER_SET_TXBUF(spi_xfer, NULL, 0, 0);
				DEV_SPI_XFER_SET_RXBUF(spi_xfer, NULL, 0, 0);
				DEV_SPI_XFER_SET_NEXT(spi_xfer, NULL);
				dw_spi_init_transfer(spi_ctrl_ptr, NULL, spi_info_ptr->dfs);
			}
			break;
		case SPI_CMD_TRANSFER_POLLING:
			DW_SPI_CHECK_EXP(CHECK_ALIGN_4BYTES(param), E_PAR);
			DW_SPI_CHECK_EXP((spi_info_ptr->status & DEV_IN_XFER) == 0, E_CTX);
			if (param != NULL) {
				/* Check transfer align */
				DW_SPI_CHECK_EXP(dw_spi_chk_xfer_aligned((DEV_SPI_TRANSFER *)param, spi_info_ptr->dfs) == 0, E_PAR);
				*spi_xfer = *((DEV_SPI_TRANSFER *)param);
				dw_spi_init_transfer(spi_ctrl_ptr, spi_xfer, spi_info_ptr->dfs);
				/* Transfer data by poll */
				dw_spi_poll_transfer(spi_info_ptr);
			} else {
				ercd = E_PAR;
			}
			break;
		case SPI_CMD_TRANSFER_INT:
			DW_SPI_CHECK_EXP(CHECK_ALIGN_4BYTES(param), E_PAR);
			if (param != NULL) {
				DW_SPI_CHECK_EXP((spi_info_ptr->status & DEV_IN_XFER) == 0, E_CTX);
				/* Check transfer align */
				DW_SPI_CHECK_EXP(dw_spi_chk_xfer_aligned((DEV_SPI_TRANSFER *)param, spi_info_ptr->dfs) == 0, E_PAR);
				*spi_xfer = *((DEV_SPI_TRANSFER *)param);
				dw_spi_init_transfer(spi_ctrl_ptr, spi_xfer, spi_info_ptr->dfs);
				/* Transfer data by interrupt */
				ercd = dw_spi_ena_cbr(spi_info_ptr, DW_SPI_RDY_XFER);
			} else {
				ercd = dw_spi_dis_cbr(spi_info_ptr, DW_SPI_RDY_XFER);
			}
			break;

		/* Master mode only commands */
		case SPI_CMD_MST_SET_FREQ:
			DW_SPI_CHECK_EXP(spi_info_ptr->mode == DEV_MASTER_MODE, E_NOSPT);
			DW_SPI_CHECK_EXP((spi_info_ptr->status & DEV_IN_XFER) == 0, E_CTX);
			val32 = (uint32_t)param;
			DW_SPI_CHECK_EXP(val32>0, E_PAR);
			dw_spi_set_freq(spi_ctrl_ptr, val32);
			spi_info_ptr->freq = val32;
			break;
		case SPI_CMD_MST_SEL_DEV:
			DW_SPI_CHECK_EXP(spi_info_ptr->mode == DEV_MASTER_MODE, E_NOSPT);
			DW_SPI_CHECK_EXP((spi_info_ptr->status & DEV_IN_XFER) == 0, E_CTX);
			val32 = (uint32_t)param;
			if (dw_spi_select_slave(spi_reg_ptr, val32) == 0) {
				spi_info_ptr->slave = val32;
			} else {
				ercd = E_SYS;
			}
			break;
		case SPI_CMD_MST_DSEL_DEV:
			DW_SPI_CHECK_EXP(spi_info_ptr->mode == DEV_MASTER_MODE, E_NOSPT);
			DW_SPI_CHECK_EXP((spi_info_ptr->status & DEV_IN_XFER) == 0, E_CTX);
			val32 = (uint32_t)param;
			if (dw_spi_deselect_slave(spi_reg_ptr, val32) == 0) {
				spi_info_ptr->slave = SPI_SLAVE_NOT_SELECTED;
			} else {
				ercd = E_SYS;
			}
			break;

		/* Slave mode only commands */


		default:
			ercd = E_NOSPT;
			break;
	}

error_exit:
	return ercd;
}

/**
 * \brief	send data through DesignWare SPI
 * \param[in]	spi_obj	spi object pointer
 * \param[in]	data	pointer to data need to send by spi
 * \param[in]	len	length of data to be sent
 * \retval	>0	Byte count that was successfully sent for poll method
 * \retval	E_OBJ	Device object is not valid or not exists
 * \retval	E_PAR	Parameter is not valid
 * \retval	E_CTX	Device is still in transfer state
 * \retval	E_SYS	Can't write data to hardware due to hardware issues, such as device is disabled
 */
int32_t dw_spi_write (DEV_SPI *spi_obj, const void *data, uint32_t len)
{
	int32_t ercd = E_OK;
	DEV_SPI_INFO *spi_info_ptr = &(spi_obj->spi_info);

	/* START ERROR CHECK */
	VALID_CHK_SPI_INFO_OBJECT(spi_info_ptr);
	DW_SPI_CHECK_EXP(spi_info_ptr->opn_cnt > 0, E_CLSED);
	DW_SPI_CHECK_EXP(spi_info_ptr->status & DEV_ENABLED, E_SYS);
	DW_SPI_CHECK_EXP((spi_info_ptr->status & DEV_IN_XFER) == 0, E_CTX);
	DW_SPI_CHECK_EXP(data!=NULL, E_PAR);
	DW_SPI_CHECK_EXP(len>0, E_PAR);
	/* END OF ERROR CHECK */

	DW_SPI_CTRL *spi_ctrl_ptr = (DW_SPI_CTRL_PTR)(spi_info_ptr->spi_ctrl);
	DEV_SPI_TRANSFER spi_xfer;

	/* Master and Slave transmit */
	DEV_SPI_XFER_SET_TXBUF(&spi_xfer, data, 0, len);
	DEV_SPI_XFER_SET_RXBUF(&spi_xfer, NULL, len, 0);
	DEV_SPI_XFER_SET_NEXT(&spi_xfer, NULL);

	/* Check transfer align */
	DW_SPI_CHECK_EXP(dw_spi_chk_xfer_aligned(&spi_xfer, spi_info_ptr->dfs) == 0, E_PAR);

	dw_spi_init_transfer(spi_ctrl_ptr, &spi_xfer, spi_info_ptr->dfs);

	ercd = dw_spi_poll_transfer(spi_info_ptr);

error_exit:
	return ercd;
}

/**
 * \brief	read data through DesignWare SPI
 * \param[in]	spi_info_ptr	spi information structure pointer
 * \param[out]	data		data that need to read (data must be char type)
 * \param[in]	len		data count need to read
 * \retval	>=0		data have been read
 * \retval	E_PAR		arguments passed was wrong
 * \retval	E_OBJ		spi has something error, nothing can be done
 * \retval	E_CLSED		spi was closed, not available for control
 * \retval	<0		other error code not defined here
 */
int32_t dw_spi_read (DEV_SPI *spi_obj, void *data, uint32_t len)
{
	int32_t ercd = E_OK;
	DEV_SPI_INFO *spi_info_ptr = &(spi_obj->spi_info);

	/* START ERROR CHECK */
	VALID_CHK_SPI_INFO_OBJECT(spi_info_ptr);
	DW_SPI_CHECK_EXP(spi_info_ptr->opn_cnt > 0, E_CLSED);
	DW_SPI_CHECK_EXP(spi_info_ptr->status & DEV_ENABLED, E_SYS);
	DW_SPI_CHECK_EXP((spi_info_ptr->status & DEV_IN_XFER) == 0, E_CTX);
	DW_SPI_CHECK_EXP(data!=NULL, E_PAR);
	DW_SPI_CHECK_EXP(len>0, E_PAR);
	/* END OF ERROR CHECK */

	DW_SPI_CTRL *spi_ctrl_ptr = (DW_SPI_CTRL_PTR)(spi_info_ptr->spi_ctrl);
	DEV_SPI_TRANSFER spi_xfer;

	/* Master and Slave transmit */
	DEV_SPI_XFER_SET_TXBUF(&spi_xfer, NULL, len, 0);
	DEV_SPI_XFER_SET_RXBUF(&spi_xfer, data, 0, len);
	DEV_SPI_XFER_SET_NEXT(&spi_xfer, NULL);

	/* Check transfer align */
	DW_SPI_CHECK_EXP(dw_spi_chk_xfer_aligned(&spi_xfer, spi_info_ptr->dfs) == 0, E_PAR);

	dw_spi_init_transfer(spi_ctrl_ptr, &spi_xfer, spi_info_ptr->dfs);

	ercd = dw_spi_poll_transfer(spi_info_ptr);

error_exit:
	return ercd;
}

/**
 * \brief	DesignWare SPI interrupt processing routine
 * \param[in]	spi_info_ptr	DEV_SPI_INFO *spi_info_ptr
 * \param[in]	ptr		extra information
 */
void dw_spi_isr(DEV_SPI *spi_obj, void *ptr)
{
	int32_t ercd = E_OK;
	DEV_SPI_INFO *spi_info_ptr = &(spi_obj->spi_info);

	/* START ERROR CHECK */
	VALID_CHK_SPI_INFO_OBJECT(spi_info_ptr);
	/* END OF ERROR CHECK */

	DW_SPI_CTRL *spi_ctrl_ptr = (DW_SPI_CTRL_PTR)(spi_info_ptr->spi_ctrl);
	DW_SPI_REG *spi_reg_ptr = (DW_SPI_REG *)(spi_ctrl_ptr->dw_spi_regs);

	uint32_t isr_status;

	isr_status = spi_reg_ptr->ISR;

	if (!isr_status) return;
	if (spi_ctrl_ptr->dw_xfer.xfer_len == 0) {
		dw_spi_disable_interrupt(spi_info_ptr);
	} else {
		if (isr_status & (DW_SPI_IMR_TXOIM|DW_SPI_IMR_RXOIM|DW_SPI_IMR_RXUIM)) {
			dw_spi_clear_interrupt_all(spi_reg_ptr);
			dw_spi_disable_interrupt(spi_info_ptr);
			if (spi_info_ptr->spi_cbs.err_cb) {
				spi_info_ptr->spi_cbs.err_cb(spi_obj);
			}
			memset(&(spi_ctrl_ptr->dw_xfer), 0, sizeof(DW_SPI_TRANSFER));
		}
		dw_spi_reader(spi_info_ptr);
		if (isr_status & DW_SPI_IMR_TXEIM) {
			dw_spi_writer(spi_info_ptr);
		}
		if (dw_spi_xfer_end(spi_ctrl_ptr)) {
			if ((spi_info_ptr->status & DW_SPI_IN_XFER) == DW_SPI_IN_TX) {
				dw_spi_dis_cbr(spi_info_ptr, DW_SPI_RDY_SND);
				if (spi_info_ptr->spi_cbs.tx_cb) {
					spi_info_ptr->spi_cbs.tx_cb(spi_obj);
				}
			} else if ((spi_info_ptr->status & DW_SPI_IN_XFER) == DW_SPI_IN_RX) {
				dw_spi_dis_cbr(spi_info_ptr, DW_SPI_RDY_RCV);
				if (spi_info_ptr->spi_cbs.rx_cb) {
					spi_info_ptr->spi_cbs.rx_cb(spi_obj);
				}
			} else if ((spi_info_ptr->status & DW_SPI_IN_XFER) == DW_SPI_IN_XFER) {
				dw_spi_dis_cbr(spi_info_ptr, DW_SPI_RDY_XFER);
				if (spi_info_ptr->spi_cbs.xfer_cb) {
					spi_info_ptr->spi_cbs.xfer_cb(spi_obj);
				}
			} else {
				dw_spi_disable_interrupt(spi_info_ptr);
			}
			memset(&(spi_ctrl_ptr->dw_xfer), 0, sizeof(DW_SPI_TRANSFER));
		}
	}

error_exit:
	return;
}
/** @} */ /* DEVICE_DW_SPI_IMPLEMENT */

/** @} */ /* DEVICE_DW_SPI */
