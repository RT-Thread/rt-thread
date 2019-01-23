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
 * \date 2014-06-30
 * \author Huaqi Fang(Huaqi.Fang@synopsys.com)
--------------------------------------------- */

/**
 * \defgroup	DEVICE_DW_IIC	Designware IIC Driver
 * \ingroup	DEVICE_DW
 * \brief	Designware IIC Driver Implementation
 */

/**
 * \file
 * \brief	Designware iic driver
 * \ingroup	DEVICE_DW_IIC
 */
#include <string.h>

#include "inc/embARC_toolchain.h"
#include "inc/embARC_error.h"

#include "inc/arc/arc_exception.h"

#include "device/designware/iic/dw_iic_hal.h"
#include "device/designware/iic/dw_iic.h"

/** check expressions used in DesignWare IIC driver implementation */
#define DW_IIC_CHECK_EXP(EXPR, ERROR_CODE)		CHECK_EXP(EXPR, ercd, ERROR_CODE, error_exit)

#ifndef DISABLE_DEVICE_OBJECT_VALID_CHECK
/** valid check of iic info object */
#define VALID_CHK_IIC_INFO_OBJECT(iicinfo_obj_ptr)		{			\
			DW_IIC_CHECK_EXP((iicinfo_obj_ptr)!=NULL, E_OBJ);		\
			DW_IIC_CHECK_EXP(((iicinfo_obj_ptr)->iic_ctrl)!=NULL, E_OBJ);	\
 		}
#endif

/**
 * \name	DesignWare IIC Interrupt Callback Routine Select Marcos
 * \brief	DesignWare IIC interrupt callback routines select macros definitions
 * @{
 */
#define DW_IIC_RDY_SND					(1U)	/*!< ready to send callback */
#define DW_IIC_RDY_RCV					(2U)	/*!< ready to receive callback */
/** @} */

/**
 * \defgroup	DEVICE_DW_IIC_STATIC	DesignWare IIC Driver Static Functions
 * \ingroup	DEVICE_DW_IIC
 * \brief	Static or inline functions, variables for DesignWare IIC handle iic operations,
 * 	only used in this file.
 * @{
 */
/** Disable designware iic device */
Inline void dw_iic_disable(DW_IIC_REG *iic_reg_ptr)
{
	iic_reg_ptr->IC_ENABLE = DW_IIC_DISABLE;
}
/** Enable designware iic device */
Inline void dw_iic_enable(DW_IIC_REG *iic_reg_ptr)
{
	iic_reg_ptr->IC_ENABLE = DW_IIC_ENABLE;
}

/** Clear all designware iic interrupt */
Inline void dw_iic_clear_interrupt_all(DW_IIC_REG *iic_reg_ptr)
{
	(void)iic_reg_ptr->IC_CLR_INTR;
}

/** test whether iic is ready to write, 1 ready, 0 not ready */
Inline int32_t dw_iic_putready(DW_IIC_REG *iic_reg_ptr)
{
	return ((iic_reg_ptr->IC_STATUS & IC_STATUS_TFNF) != 0);
}
/** test whether iic is ready to receive, 1 ready, 0 not ready */
Inline int32_t dw_iic_getready(DW_IIC_REG *iic_reg_ptr)
{
	return ((iic_reg_ptr->IC_STATUS & IC_STATUS_RFNE) != 0);
}
/** Write data into IIC TX FIFO with STOP/RESTART Condition, and R/W bit */
Inline void dw_iic_putdata(DW_IIC_REG *iic_reg_ptr, uint32_t data)
{
	iic_reg_ptr->IC_DATA_CMD = data;
}

/** Read Data from IIC RX FIFO */
Inline uint32_t dw_iic_getdata(DW_IIC_REG *iic_reg_ptr)
{
	return (iic_reg_ptr->IC_DATA_CMD) & 0xff;
}

/** Enable designware iic bit interrupt with mask */
Inline void dw_iic_unmask_interrupt(DW_IIC_REG *iic_reg_ptr, uint32_t mask)
{
	iic_reg_ptr->IC_INTR_MASK |= mask;
}

/** Disable designware iic bit interrupt with mask */
Inline void dw_iic_mask_interrupt(DW_IIC_REG *iic_reg_ptr, uint32_t mask)
{
	iic_reg_ptr->IC_INTR_MASK &= ~mask;
}

/** Get TX FIFO Length */
Inline uint32_t dw_iic_get_txfifo_len(DW_IIC_REG *iic_reg_ptr)
{
	uint32_t txfifolen;

	txfifolen = ((iic_reg_ptr->IC_COMP_PARAM_1 >> 16) & 0xff) + 1;

	return txfifolen;
}

/** Get RX FIFO Length */
Inline uint32_t dw_iic_get_rxfifo_len(DW_IIC_REG *iic_reg_ptr)
{
	uint32_t rxfifolen;

	rxfifolen = ((iic_reg_ptr->IC_COMP_PARAM_1 >> 8) & 0xff) + 1;

	return rxfifolen;
}

/** Set designware iic transfer in 7bit of 10bit addressing mode as a master */
Inline void dw_iic_set_mstaddr_mode(DW_IIC_REG *iic_reg_ptr, uint32_t mode)
{
#if DW_IIC_DYNAMIC_TAR_UPDATE_SUPPORT
	if (mode == IIC_7BIT_ADDRESS) {
		iic_reg_ptr->IC_TAR &= ~IC_10BITADDR_MASTER;
	} else {
		iic_reg_ptr->IC_TAR |= IC_10BITADDR_MASTER;
	}
#else
	dw_iic_disable(iic_reg_ptr);
	if (mode == IIC_7BIT_ADDRESS) {
		iic_reg_ptr->IC_CON &= ~MST_10_BIT_ADDR_MODE;
	} else {
		iic_reg_ptr->IC_CON |= MST_10_BIT_ADDR_MODE;
	}
	dw_iic_enable(iic_reg_ptr);
#endif
}

/** Set designware iic transfer in 7bit of 10bit addressing mode as a slave */
Inline void dw_iic_set_slvaddr_mode(DW_IIC_REG *iic_reg_ptr, uint32_t mode)
{
	dw_iic_disable(iic_reg_ptr);
	if (mode == IIC_7BIT_ADDRESS) {
		iic_reg_ptr->IC_CON &= ~SLV_10_BIT_ADDR_MODE;
	} else {
		iic_reg_ptr->IC_CON |= SLV_10_BIT_ADDR_MODE;
	}
	dw_iic_enable(iic_reg_ptr);
}

/** Set designware iic transfer target address for addressing any iic slave device as a master */
Inline void dw_iic_set_taraddr(DW_IIC_REG *iic_reg_ptr, uint32_t address)
{
#if DW_IIC_DYNAMIC_TAR_UPDATE_SUPPORT
	iic_reg_ptr->IC_TAR &= ~(IC_TAR_10BIT_ADDR_MASK);
	iic_reg_ptr->IC_TAR |= (IC_TAR_10BIT_ADDR_MASK & address);
#else
	dw_iic_disable(iic_reg_ptr);
	iic_reg_ptr->IC_TAR &= ~(IC_TAR_10BIT_ADDR_MASK);
	iic_reg_ptr->IC_TAR |= (IC_TAR_10BIT_ADDR_MASK & address);
	dw_iic_enable(iic_reg_ptr);
#endif
}

/** Set designware iic slave address as a slave */
Inline void dw_iic_set_slvaddr(DW_IIC_REG *iic_reg_ptr, uint32_t address)
{
	dw_iic_disable(iic_reg_ptr);
	iic_reg_ptr->IC_SAR &= ~(IC_SAR_10BIT_ADDR_MASK);
	iic_reg_ptr->IC_SAR |= (IC_SAR_10BIT_ADDR_MASK & address);
	dw_iic_enable(iic_reg_ptr);
}

/** Select speed mode, and return proper speed mode configuration */
Inline uint32_t dw_iic_select_speedmode(uint32_t speedmode)
{
	uint32_t speedcfg;

	if (speedmode == IIC_SPEED_STANDARD) {
		speedcfg = IC_CON_SPEED_STANDARD;
	} else if (speedmode == IIC_SPEED_FAST) {
		speedcfg = IC_CON_SPEED_FAST;
	} else if (speedmode == IIC_SPEED_FASTPLUS) {
		speedcfg = IC_CON_SPEED_FAST;
	} else if (speedmode == IIC_SPEED_HIGH) {
		speedcfg = IC_CON_SPEED_HIGH;
	} else {
		speedcfg = IC_CON_SPEED_HIGH;
	}
	return speedcfg;
}
/** Set designware iic speed mode */
Inline void dw_iic_set_speedmode(DW_IIC_REG *iic_reg_ptr, uint32_t speedmode)
{
	uint32_t ic_con_val;

	dw_iic_disable(iic_reg_ptr);
	ic_con_val = iic_reg_ptr->IC_CON & (~IC_CON_SPEED_MASK);
	ic_con_val |= dw_iic_select_speedmode(speedmode);
	iic_reg_ptr->IC_CON = ic_con_val;
	dw_iic_enable(iic_reg_ptr);
}

/** Set designware working mode as master or slave */
Inline void dw_iic_set_working_mode(DW_IIC_REG *iic_reg_ptr, uint32_t mode)
{
	uint32_t ic_con_val;
	dw_iic_disable(iic_reg_ptr);
	ic_con_val = iic_reg_ptr->IC_CON & (~IC_CON_MST_SLV_MODE_MASK);
	if (mode == DEV_MASTER_MODE) {
		ic_con_val |= IC_CON_ENA_MASTER_MODE;
	} else {
		ic_con_val |= IC_CON_ENA_SLAVE_MODE;
	}
	dw_iic_enable(iic_reg_ptr);
}

/** Set IC_CLK frequency by configuration the *CNT registers for different speed modes */
Inline void dw_iic_set_scl_cnt(DW_IIC_REG *iic_reg_ptr, DW_IIC_SCL_CNT *scl_cnt)
{
	dw_iic_disable(iic_reg_ptr);
	iic_reg_ptr->IC_SS_SCL_HCNT = scl_cnt->ss_scl_hcnt;
	iic_reg_ptr->IC_SS_SCL_LCNT = scl_cnt->ss_scl_lcnt;
	iic_reg_ptr->IC_FS_SCL_HCNT = scl_cnt->fs_scl_hcnt;
	iic_reg_ptr->IC_FS_SCL_LCNT = scl_cnt->fs_scl_lcnt;
	iic_reg_ptr->IC_HS_SCL_HCNT = scl_cnt->hs_scl_hcnt;
	iic_reg_ptr->IC_HS_SCL_LCNT = scl_cnt->hs_scl_lcnt;
	dw_iic_enable(iic_reg_ptr);
}

/** Set spike suppression configuration */
Inline void dw_iic_set_spike_len(DW_IIC_REG *iic_reg_ptr, DW_IIC_SPKLEN *spklen)
{
	dw_iic_disable(iic_reg_ptr);
	iic_reg_ptr->IC_FS_SPKLEN = spklen->fs_spklen;
	iic_reg_ptr->IC_HS_SPKLEN = spklen->hs_spklen;
	dw_iic_enable(iic_reg_ptr);
}

Inline void dw_iic_flush_tx(DW_IIC_REG *iic_reg_ptr)
{
	(void)iic_reg_ptr->IC_CLR_INTR;
}

Inline void dw_iic_flush_rx(DW_IIC_REG *iic_reg_ptr)
{
}

static uint32_t dw_iic_get_slv_state(DW_IIC_REG *iic_reg_ptr)
{
	uint32_t status;
	uint32_t slv_state = IIC_SLAVE_STATE_FREE;

	status = iic_reg_ptr->IC_RAW_INTR_STAT;
	if (status & IC_INTR_STAT_GEN_CALL) {
	/* General Call address is received and it is acknowledged */
		slv_state |= IIC_SLAVE_STATE_GC_REQ;
	}
	if (status & IC_INTR_STAT_RX_FULL) {
	/* master is attempting to write data to this slave */
		slv_state |= IIC_SLAVE_STATE_WR_REQ;
	}
	if (status & IC_INTR_STAT_RD_REQ) {
	/* master is attempting to read data from this slave */
		slv_state |= IIC_SLAVE_STATE_RD_REQ;
	}
	if (status & IC_INTR_STAT_RX_DONE) {
	/* master does not acknowledge a transmitted byte, and transmission is done */
		slv_state |= IIC_SLAVE_STATE_RD_DONE;
		status = iic_reg_ptr->IC_CLR_RX_DONE;
	}
	if (status & IC_INTR_STAT_START_DET) {
	/* a START or RESTART condition has occurred */
		slv_state |= IIC_SLAVE_STATE_START;
		status = iic_reg_ptr->IC_CLR_START_DET; /* Clear it when read */
	}
	if (status & IC_INTR_STAT_STOP_DET) {
	/* a STOP condition has occurred */
		slv_state |= IIC_SLAVE_STATE_STOP;
		status = iic_reg_ptr->IC_CLR_STOP_DET;  /* Clear it when read */
	}
	if (status & (IC_INTR_STAT_TX_ABRT|IC_INTR_STAT_TX_OVER\
		|IC_INTR_STAT_RX_OVER|IC_INTR_STAT_RX_UNDER)) {
	/* error case */
		slv_state |= IIC_SLAVE_STATE_ERROR;
		status = iic_reg_ptr->IC_CLR_TX_ABRT;  /* Clear it when read */
		status = iic_reg_ptr->IC_CLR_TX_OVER;
		status = iic_reg_ptr->IC_CLR_RX_OVER;
		status = iic_reg_ptr->IC_CLR_RX_UNDER;
	}

	return slv_state;
}

/** Init Designware IIC Device into Master mode */
static void dw_iic_master_init(DW_IIC_CTRL *iic_ctrl_ptr, uint32_t speed_mode, uint32_t addr_mode, uint32_t tar_addr)
{
	uint32_t ic_con_val = 0;
	DW_IIC_REG *iic_reg_ptr = iic_ctrl_ptr->dw_iic_regs;

	dw_iic_disable(iic_reg_ptr);

	/* disable all iic interrupt */
	iic_reg_ptr->IC_INTR_MASK = IC_INT_DISABLE_ALL;

	/* Set to 7bit addressing and update target address */
	iic_reg_ptr->IC_TAR = (tar_addr & IC_TAR_10BIT_ADDR_MASK) | IC_TAR_SPECIAL | IC_TAR_GC_OR_START;
	/* master mode, restart enabled */
	ic_con_val = dw_iic_select_speedmode(speed_mode) | IC_CON_ENA_MASTER_MODE | IC_CON_RESTART_EN;

#if DW_IIC_DYNAMIC_TAR_UPDATE_SUPPORT
	if (addr_mode == IIC_10BIT_ADDRESS) {
		iic_reg_ptr->IC_TAR |= MST_10_BIT_ADDR_MODE;
	}
#else
	if (addr_mode == IIC_10BIT_ADDRESS) {
		ic_con_val |= MST_10_BIT_ADDR_MODE;
	}
#endif
	/* Set final IC_CON value */
	iic_reg_ptr->IC_CON = ic_con_val;
	/* FIFO threshold settings */
	iic_reg_ptr->IC_TX_TL = IIC_TX_THRESHOLD;
	iic_reg_ptr->IC_RX_TL = IIC_RX_THRESHOLD;
	/* Master code settings */
	iic_reg_ptr->IC_HS_MADDR = iic_ctrl_ptr->iic_master_code;
	dw_iic_enable(iic_reg_ptr);

	/* Clock Settings */
	dw_iic_set_scl_cnt(iic_reg_ptr, &(iic_ctrl_ptr->iic_scl_cnt));
	dw_iic_set_spike_len(iic_reg_ptr, &(iic_ctrl_ptr->iic_spklen));
}

/** Init Designware IIC Device into Slave mode */
static void dw_iic_slave_init(DW_IIC_CTRL *iic_ctrl_ptr, uint32_t addr_mode, uint32_t slv_addr)
{
	uint32_t ic_con_val = 0;
	DW_IIC_REG *iic_reg_ptr = iic_ctrl_ptr->dw_iic_regs;

	dw_iic_disable(iic_reg_ptr);

	/* disable all iic interrupt */
	iic_reg_ptr->IC_INTR_MASK = IC_INT_DISABLE_ALL;

	/* Set slave device address as a slave */
	iic_reg_ptr->IC_SAR = slv_addr & IC_SAR_10BIT_ADDR_MASK;
	/* slave mode, 7 bit slave address */
	ic_con_val = IC_CON_ENA_SLAVE_MODE;
	/* If addr mode select to be 10 bit address mode */
	if (addr_mode == IIC_10BIT_ADDRESS) {
		ic_con_val |= SLV_10_BIT_ADDR_MODE;
	}

	/* Set final IC_CON value */
	iic_reg_ptr->IC_CON = ic_con_val;
	/* FIFO threshold settings */
	iic_reg_ptr->IC_TX_TL = IIC_TX_THRESHOLD;
	iic_reg_ptr->IC_RX_TL = IIC_RX_THRESHOLD;

	dw_iic_enable(iic_reg_ptr);
}

/** Check error for IIC master device */
static int32_t dw_iic_mst_chkerr(DW_IIC_CTRL *iic_ctrl_ptr)
{
	uint32_t status;
	int32_t ercd = IIC_ERR_NONE;
	DW_IIC_REG *iic_reg_ptr = (DW_IIC_REG *)(iic_ctrl_ptr->dw_iic_regs);

	status = iic_reg_ptr->IC_RAW_INTR_STAT;
	if (status & IC_INTR_STAT_TX_ABRT) {
		status = iic_reg_ptr->IC_TX_ABRT_SOURCE;
		if (status & IIC_MST_ABRT_LOST_BUS) {
			ercd = IIC_ERR_LOST_BUS;
		} else if (status & IIC_MST_ABRT_ADDR_NOACK) {
			ercd = IIC_ERR_ADDR_NOACK;
		} else if (status & IIC_MST_ABRT_DATA_NOACK) {
			ercd = IIC_ERR_DATA_NOACK;
		} else {
			ercd = IIC_ERR_UNDEF;
		}
		status = iic_reg_ptr->IC_CLR_TX_ABRT;
	} else {
		if (status & IC_INTR_STAT_TX_OVER) {
			iic_ctrl_ptr->iic_tx_over ++;
			status = iic_reg_ptr->IC_CLR_TX_OVER;
		}
		if (status & (IC_INTR_STAT_RX_OVER|IC_INTR_STAT_RX_UNDER)) {
			iic_ctrl_ptr->iic_rx_over ++;
			status = iic_reg_ptr->IC_CLR_RX_OVER;
			status = iic_reg_ptr->IC_CLR_RX_UNDER;
		}
	}
	return ercd;
}

/** Check error for IIC slave device */
static int32_t dw_iic_slv_chkerr(DW_IIC_CTRL *iic_ctrl_ptr)
{
	uint32_t status;
	int32_t ercd = IIC_ERR_NONE;
	DW_IIC_REG *iic_reg_ptr = (DW_IIC_REG *)(iic_ctrl_ptr->dw_iic_regs);

	status = iic_reg_ptr->IC_RAW_INTR_STAT;
	if (status & IC_INTR_STAT_TX_ABRT) {
		status = iic_reg_ptr->IC_TX_ABRT_SOURCE;
		if (status & IIC_SLV_ABRT_LOST_BUS) {
			ercd = IIC_ERR_LOST_BUS;
		} else if (status & IC_TX_ABRT_SLVFLUSH_TXFIFO) {
			/* Flush tx fifo */
			status = iic_reg_ptr->IC_TX_ABRT_SOURCE;
		} else {
			ercd = IIC_ERR_UNDEF;
		}
		status = iic_reg_ptr->IC_CLR_TX_ABRT;
	} else {
		if (status & IC_INTR_STAT_TX_OVER) {
			iic_ctrl_ptr->iic_tx_over ++;
			status = iic_reg_ptr->IC_CLR_TX_OVER;
		}
		if (status & (IC_INTR_STAT_RX_OVER|IC_INTR_STAT_RX_UNDER)) {
			iic_ctrl_ptr->iic_rx_over ++;
			status = iic_reg_ptr->IC_CLR_RX_OVER;
			status = iic_reg_ptr->IC_CLR_RX_UNDER;
		}
	}
	return ercd;
}

/** enable designware iic */
static void dw_iic_enable_device(DEV_IIC_INFO *iic_info_ptr)
{
	DW_IIC_CTRL *iic_ctrl_ptr = (DW_IIC_CTRL *)(iic_info_ptr->iic_ctrl);
	DW_IIC_REG *iic_reg_ptr = (DW_IIC_REG *)(iic_ctrl_ptr->dw_iic_regs);

	if ((iic_info_ptr->status & DEV_ENABLED) == 0) {
		dw_iic_enable(iic_reg_ptr);
		iic_info_ptr->status |= DEV_ENABLED;
	}
}

/** disable designware iic */
static void dw_iic_disable_device(DEV_IIC_INFO *iic_info_ptr)
{
	DW_IIC_CTRL *iic_ctrl_ptr = (DW_IIC_CTRL *)(iic_info_ptr->iic_ctrl);
	DW_IIC_REG *iic_reg_ptr = (DW_IIC_REG *)(iic_ctrl_ptr->dw_iic_regs);
	uint32_t i;

	for (i=0; i<DW_IIC_DISABLE_MAX_T_POLL_CNT; i++) {
		dw_iic_disable(iic_reg_ptr);
		if ((iic_reg_ptr->IC_ENABLE_STATUS & IC_ENABLE_STATUS_IC_EN) == 0) {
			break;
		}
	}
	iic_info_ptr->status &= ~DEV_ENABLED;
}

static void dw_iic_reset_device(DEV_IIC_INFO *iic_info_ptr)
{
	DW_IIC_CTRL *iic_ctrl_ptr = (DW_IIC_CTRL *)(iic_info_ptr->iic_ctrl);
	DW_IIC_REG *iic_reg_ptr = (DW_IIC_REG *)(iic_ctrl_ptr->dw_iic_regs);

	dw_iic_disable_device(iic_info_ptr);
	dw_iic_clear_interrupt_all(iic_reg_ptr);
	iic_info_ptr->next_cond = IIC_MODE_STOP;
	iic_info_ptr->cur_state = IIC_FREE;
	iic_info_ptr->err_state = IIC_ERR_NONE;
	iic_ctrl_ptr->iic_tx_over = 0;
	iic_ctrl_ptr->iic_rx_over = 0;
	dw_iic_enable_device(iic_info_ptr);
}

/** Disable iic master interrupt for transmit or receive */
static void dw_iic_mst_dis_cbr(DW_IIC_CTRL *iic_ctrl_ptr, uint32_t cbrtn)
{
	DW_IIC_REG *iic_reg_ptr = (DW_IIC_REG *)(iic_ctrl_ptr->dw_iic_regs);

	switch (cbrtn) {
		case DW_IIC_RDY_SND:
			dw_iic_mask_interrupt(iic_reg_ptr, IC_INT_MST_TX_ENABLE);
			iic_ctrl_ptr->int_status &= ~DW_IIC_TXINT_ENABLE;
			break;
		case DW_IIC_RDY_RCV:
			dw_iic_mask_interrupt(iic_reg_ptr, IC_INT_MST_RX_ENABLE);
			iic_ctrl_ptr->int_status &= ~DW_IIC_RXINT_ENABLE;
			break;
		default:
			break;
	}
}

/** Disable iic slave interrupt for transmit or receive */
static void dw_iic_slv_dis_cbr(DW_IIC_CTRL *iic_ctrl_ptr, uint32_t cbrtn)
{
	DW_IIC_REG *iic_reg_ptr = (DW_IIC_REG *)(iic_ctrl_ptr->dw_iic_regs);

	switch (cbrtn) {
		case DW_IIC_RDY_SND:
			dw_iic_mask_interrupt(iic_reg_ptr, IC_INT_SLV_TX_ENABLE);
			iic_ctrl_ptr->int_status &= ~DW_IIC_TXINT_ENABLE;
			break;
		case DW_IIC_RDY_RCV:
			dw_iic_mask_interrupt(iic_reg_ptr, IC_INT_SLV_RX_ENABLE);
			iic_ctrl_ptr->int_status &= ~DW_IIC_RXINT_ENABLE;
			break;
		default:
			break;
	}
}

/** Enable iic master interrupt for transmit or receive */
static void dw_iic_mst_ena_cbr(DW_IIC_CTRL *iic_ctrl_ptr, uint32_t cbrtn)
{
	DW_IIC_REG *iic_reg_ptr = (DW_IIC_REG *)(iic_ctrl_ptr->dw_iic_regs);

	switch (cbrtn) {
		case DW_IIC_RDY_SND:
			iic_ctrl_ptr->int_status |= DW_IIC_TXINT_ENABLE;
			dw_iic_unmask_interrupt(iic_reg_ptr, IC_INT_MST_TX_ENABLE);
			break;
		case DW_IIC_RDY_RCV:
			iic_ctrl_ptr->int_status |= DW_IIC_RXINT_ENABLE;
			dw_iic_unmask_interrupt(iic_reg_ptr, IC_INT_MST_RX_ENABLE);
			break;
		default:
			break;
	}
}

/** Enable iic slave interrupt for transmit or receive */
static void dw_iic_slv_ena_cbr(DW_IIC_CTRL *iic_ctrl_ptr, uint32_t cbrtn)
{
	DW_IIC_REG *iic_reg_ptr = (DW_IIC_REG *)(iic_ctrl_ptr->dw_iic_regs);

	switch (cbrtn) {
		case DW_IIC_RDY_SND:
			iic_ctrl_ptr->int_status |= DW_IIC_TXINT_ENABLE;
			dw_iic_unmask_interrupt(iic_reg_ptr, IC_INT_SLV_TX_ENABLE);
			break;
		case DW_IIC_RDY_RCV:
			iic_ctrl_ptr->int_status |= DW_IIC_RXINT_ENABLE;
			dw_iic_unmask_interrupt(iic_reg_ptr, IC_INT_SLV_RX_ENABLE);
			break;
		default:
			break;
	}
}

/**
 * \brief	disable designware iic send or receive interrupt
 * \param[in]	DEV_IIC_INFO 	*iic_info_ptr
 * \param[in]	cbrtn		control code of callback routine of send or receive
 */
static void dw_iic_dis_cbr(DEV_IIC_INFO *iic_info_ptr, uint32_t cbrtn)
{
	DW_IIC_CTRL *iic_ctrl_ptr = (DW_IIC_CTRL *)(iic_info_ptr->iic_ctrl);

	if (iic_info_ptr->mode == DEV_MASTER_MODE) {
		dw_iic_mst_dis_cbr(iic_ctrl_ptr, cbrtn);
	} else {
		dw_iic_slv_dis_cbr(iic_ctrl_ptr, cbrtn);
	}

	if (iic_ctrl_ptr->int_status & DW_IIC_GINT_ENABLE) {
		if ((iic_ctrl_ptr->int_status & (DW_IIC_RXINT_ENABLE|DW_IIC_TXINT_ENABLE)) == 0) {
			int_disable(iic_ctrl_ptr->intno);
			iic_ctrl_ptr->int_status &= ~DW_IIC_GINT_ENABLE;
		}
	}
}

/**
 * \brief	enable DesignWare IIC send or receive interrupt
 * \param[in]	DEV_IIC_INFO 	*iic_info_ptr
 * \param[in]	cbrtn		control code of callback routine of send or receive
 */
static void dw_iic_ena_cbr(DEV_IIC_INFO *iic_info_ptr, uint32_t cbrtn)
{
	DW_IIC_CTRL *iic_ctrl_ptr = (DW_IIC_CTRL *)(iic_info_ptr->iic_ctrl);

	if (iic_info_ptr->mode == DEV_MASTER_MODE) {
		dw_iic_mst_ena_cbr(iic_ctrl_ptr, cbrtn);
	} else {
		dw_iic_slv_ena_cbr(iic_ctrl_ptr, cbrtn);
	}

	if ((iic_ctrl_ptr->int_status & DW_IIC_GINT_ENABLE) == 0) {
		if (iic_ctrl_ptr->int_status & (DW_IIC_RXINT_ENABLE|DW_IIC_TXINT_ENABLE)) {
			iic_ctrl_ptr->int_status |= DW_IIC_GINT_ENABLE;
			int_enable(iic_ctrl_ptr->intno);
		}
	}
}

/**
 * \brief	enable designware iic interrupt
 * \param	iic_info_ptr	iic information structure pointer
 */
static void dw_iic_enable_interrupt(DEV_IIC_INFO *iic_info_ptr)
{
	DW_IIC_CTRL *iic_ctrl_ptr = (DW_IIC_CTRL *)(iic_info_ptr->iic_ctrl);

	int_handler_install(iic_ctrl_ptr->intno, iic_ctrl_ptr->dw_iic_int_handler);
	iic_ctrl_ptr->int_status |= DW_IIC_GINT_ENABLE;
	int_enable(iic_ctrl_ptr->intno);	/** enable iic interrupt */
}
/**
 * \brief	disable designware iic interrupt
 * \param	iic_info_ptr	iic information structure pointer
 */
static void dw_iic_disable_interrupt(DEV_IIC_INFO *iic_info_ptr)
{
	DW_IIC_CTRL *iic_ctrl_ptr = (DW_IIC_CTRL *)(iic_info_ptr->iic_ctrl);

	/** disable iic send&receive interrupt after disable iic interrupt */
	dw_iic_dis_cbr(iic_info_ptr, DW_IIC_RDY_SND);
	dw_iic_dis_cbr(iic_info_ptr, DW_IIC_RDY_RCV);
	/* disable iic interrupt */
	int_disable(iic_ctrl_ptr->intno);
	iic_ctrl_ptr->int_status &= ~(DW_IIC_GINT_ENABLE|DW_IIC_TXINT_ENABLE|DW_IIC_RXINT_ENABLE);
}

/** abort current interrupt transmit transfer */
static void dw_iic_abort_tx(DEV_IIC *iic_obj)
{
	DEV_IIC_INFO *iic_info_ptr = &(iic_obj->iic_info);
	DW_IIC_CTRL *iic_ctrl_ptr = (DW_IIC_CTRL *)(iic_info_ptr->iic_ctrl);

	if (iic_ctrl_ptr->int_status & DW_IIC_TXINT_ENABLE) {
		dw_iic_dis_cbr(iic_info_ptr, DW_IIC_RDY_SND);
		iic_info_ptr->status |= DEV_IN_TX_ABRT;
		if (iic_info_ptr->iic_cbs.tx_cb != NULL) {
			iic_info_ptr->iic_cbs.tx_cb(iic_obj);
		}
		iic_info_ptr->status &= ~(DEV_IN_TX_ABRT);
	}
}

/** abort current interrupt receive transfer */
static void dw_iic_abort_rx(DEV_IIC *iic_obj)
{
	DEV_IIC_INFO *iic_info_ptr = &(iic_obj->iic_info);
	DW_IIC_CTRL *iic_ctrl_ptr = (DW_IIC_CTRL *)(iic_info_ptr->iic_ctrl);

	if (iic_ctrl_ptr->int_status & DW_IIC_RXINT_ENABLE) {
		dw_iic_dis_cbr(iic_info_ptr, DW_IIC_RDY_RCV);
		iic_info_ptr->status |= DEV_IN_RX_ABRT;
		if (iic_info_ptr->iic_cbs.rx_cb != NULL) {
			iic_info_ptr->iic_cbs.rx_cb(iic_obj);
		}
		iic_info_ptr->status &= ~(DEV_IN_RX_ABRT);
	}
}

/** Get available transmit fifo count */
static int32_t dw_iic_get_txavail(DW_IIC_CTRL *iic_ctrl_ptr)
{
	int32_t tx_avail = 0;
	DW_IIC_REG *iic_reg_ptr = (DW_IIC_REG *)(iic_ctrl_ptr->dw_iic_regs);

	if (iic_ctrl_ptr->tx_fifo_len <= 1) {
		if (dw_iic_putready(iic_reg_ptr) == 1) {
			tx_avail = 1;
		} else {
			tx_avail = 0;
		}
	} else {
		tx_avail = iic_ctrl_ptr->tx_fifo_len - iic_reg_ptr->IC_TXFLR;
	}
	return tx_avail;
}

/** Get available receive fifo count */
static int32_t dw_iic_get_rxavail(DW_IIC_CTRL *iic_ctrl_ptr)
{
	int32_t rx_avail = 0;
	DW_IIC_REG *iic_reg_ptr = (DW_IIC_REG *)(iic_ctrl_ptr->dw_iic_regs);

	if (iic_ctrl_ptr->rx_fifo_len <= 1) {
		if (dw_iic_getready(iic_reg_ptr) == 1) {
			rx_avail = 1;
		} else {
			rx_avail = 0;
		}
	} else {
		rx_avail = iic_reg_ptr->IC_RXFLR;
	}
	return rx_avail;
}

/**
 * IIC Master device transmit 1 data,
 * next_cond can be \ref IC_DATA_CMD_STOP,
 * \ref IC_DATA_CMD_RESTART and ref IC_DATA_CMD_NONE
 */
static int32_t dw_iic_mst_write_data(DW_IIC_CTRL *iic_ctrl_ptr, uint32_t data, uint32_t next_cond)
{
	uint32_t i = 0;
	int32_t ercd = IIC_ERR_NONE;
	DW_IIC_REG *iic_reg_ptr = (DW_IIC_REG *)(iic_ctrl_ptr->dw_iic_regs);

	while (dw_iic_putready(iic_reg_ptr) == 0) {
		if (i++ > iic_ctrl_ptr->retry_cnt) return IIC_ERR_TIMEOUT;
		ercd = dw_iic_mst_chkerr(iic_ctrl_ptr);
		if (ercd != IIC_ERR_NONE) return ercd;
	}
	dw_iic_putdata(iic_reg_ptr, data|IC_DATA_CMD_WRITE_REQ|next_cond);

	return ercd;
}

/** IIC Slave device transmit 1 data */
static int32_t dw_iic_slv_write_data(DW_IIC_CTRL *iic_ctrl_ptr, uint32_t data)
{
	uint32_t i = 0;
	int32_t ercd = IIC_ERR_NONE;
	uint32_t slv_state, temp;
	uint32_t ready2send = 0;
	DW_IIC_REG *iic_reg_ptr = (DW_IIC_REG *)(iic_ctrl_ptr->dw_iic_regs);

	for (i = 0; i < iic_ctrl_ptr->retry_cnt; i++) {
		ercd = dw_iic_slv_chkerr(iic_ctrl_ptr);
		if (ercd != IIC_ERR_NONE) return ercd;
		slv_state = iic_reg_ptr->IC_RAW_INTR_STAT;
		if (slv_state & IC_INTR_STAT_RD_REQ) {
			if (dw_iic_putready(iic_reg_ptr)) {
				temp = iic_reg_ptr->IC_CLR_RD_REQ;
				ready2send = 1;
				break;
			}
		} else if (slv_state & IC_INTR_STAT_RX_DONE) { /* Put RX Done before STOP */
			temp = iic_reg_ptr->IC_CLR_RX_DONE;
			return IIC_ERR_MSTSTOP;
		} else if (slv_state & IC_INTR_STAT_STOP_DET) {
			temp = iic_reg_ptr->IC_CLR_STOP_DET;
			return IIC_ERR_MSTSTOP;
		}
	}
	if (ready2send) {
		dw_iic_putdata(iic_reg_ptr, data|IC_DATA_CMD_WRITE_REQ);
	} else {
		ercd = IIC_ERR_TIMEOUT;
	}

	return ercd;
}

/**
 * IIC Master device receive 1 data,
 * next_cond can be \ref IC_DATA_CMD_STOP,
 * \ref IC_DATA_CMD_RESTART and ref IC_DATA_CMD_NONE
 */
static int32_t dw_iic_mst_read_data(DW_IIC_CTRL *iic_ctrl_ptr, uint32_t *data, uint32_t next_cond)
{
	uint32_t i = 0;
	int32_t ercd = IIC_ERR_NONE;
	DW_IIC_REG *iic_reg_ptr = (DW_IIC_REG *)(iic_ctrl_ptr->dw_iic_regs);

	/* Issue a read request */
	while (dw_iic_putready(iic_reg_ptr) == 0) {
		if (i++ > iic_ctrl_ptr->retry_cnt) return IIC_ERR_TIMEOUT;
		ercd = dw_iic_mst_chkerr(iic_ctrl_ptr);
		if (ercd != IIC_ERR_NONE) return ercd;
	}
	dw_iic_putdata(iic_reg_ptr, next_cond|IC_DATA_CMD_READ_REQ);
	/* Wait to read data */
	i = 0;
	while (dw_iic_getready(iic_reg_ptr) == 0) {
		if (i++ > iic_ctrl_ptr->retry_cnt) return IIC_ERR_TIMEOUT;
		ercd = dw_iic_mst_chkerr(iic_ctrl_ptr);
		if (ercd != IIC_ERR_NONE) return ercd;
	}
	*data = dw_iic_getdata(iic_reg_ptr);
	return ercd;
}

/** IIC Slave device receive 1 data */
static int32_t dw_iic_slv_read_data(DW_IIC_CTRL *iic_ctrl_ptr, uint32_t *data)
{
	uint32_t i = 0;
	int32_t ercd = IIC_ERR_NONE;
	uint32_t slv_state, temp;
	uint32_t ready2read = 0;
	DW_IIC_REG *iic_reg_ptr = (DW_IIC_REG *)(iic_ctrl_ptr->dw_iic_regs);

	for (i = 0; i < iic_ctrl_ptr->retry_cnt; i++) {
		ercd = dw_iic_slv_chkerr(iic_ctrl_ptr);
		if (ercd != IIC_ERR_NONE) return ercd;
		slv_state = iic_reg_ptr->IC_RAW_INTR_STAT;
		if (slv_state & IC_INTR_STAT_START_DET) {
			temp = iic_reg_ptr->IC_CLR_START_DET;
		}
		if (slv_state & IC_INTR_STAT_RX_FULL) {
			if (dw_iic_getready(iic_reg_ptr)) {
				ready2read = 1;
				break;
			}
		} else if (slv_state & IC_INTR_STAT_STOP_DET) {
			temp = iic_reg_ptr->IC_CLR_STOP_DET;
			return IIC_ERR_MSTSTOP;
		}
	}
	if (ready2read) {
		*data = dw_iic_getdata(iic_reg_ptr);
	} else {
		ercd = IIC_ERR_TIMEOUT;
	}

	return ercd;
}

/** IIC Master transmit called in interrupt */
static void dw_iic_mst_int_write(DEV_IIC *iic_obj)
{
	DEV_IIC_INFO *iic_info_ptr = &(iic_obj->iic_info);
	DW_IIC_CTRL *iic_ctrl_ptr = (DW_IIC_CTRL_PTR)(iic_info_ptr->iic_ctrl);
	DW_IIC_REG *iic_reg_ptr = (DW_IIC_REG_PTR)(iic_ctrl_ptr->dw_iic_regs);
	uint32_t iic_int_status; /** iic interrupt status */
	uint32_t last_cond, xmit_data, xmit_end = 0;
	DEV_BUFFER *buf_ptr;
	uint8_t *p_charbuf;

	if (iic_info_ptr->next_cond == IIC_MODE_STOP) {
		last_cond = IC_DATA_CMD_STOP;
	} else {
		last_cond = IC_DATA_CMD_RESTART;
	}
	iic_int_status = (iic_reg_ptr->IC_INTR_STAT);
	buf_ptr = &(iic_info_ptr->tx_buf);
	p_charbuf = (uint8_t *)buf_ptr->buf;
	if (p_charbuf) {
		if (iic_int_status & IC_INTR_STAT_TX_EMPTY) {
			xmit_end = 0;
			while (dw_iic_putready(iic_reg_ptr)) {
				xmit_data = (uint32_t)(p_charbuf[buf_ptr->ofs])|IC_DATA_CMD_WRITE_REQ;
				if (buf_ptr->ofs == (buf_ptr->len-1)) {
					xmit_end = 1;
					xmit_data |= last_cond;
				} else {
					xmit_data |= IC_DATA_CMD_NONE;
				}
				buf_ptr->ofs ++;
				dw_iic_putdata(iic_reg_ptr, xmit_data);
				if (xmit_end) {
					dw_iic_dis_cbr(iic_info_ptr, DW_IIC_RDY_SND);
					iic_info_ptr->cur_state = IIC_FREE;
					if (iic_info_ptr->iic_cbs.tx_cb) {
						iic_info_ptr->iic_cbs.tx_cb(iic_obj);
					}
					/* clear the send buffer pointer */
					memset(buf_ptr, 0, sizeof(DEV_BUFFER));
					break;
				}
			}
		}
		if (iic_int_status & IC_INTR_STAT_TX_OVER) {
			iic_ctrl_ptr->iic_tx_over ++;
		}
		if (iic_int_status & IC_INTR_STAT_TX_ABRT) {
			iic_info_ptr->err_state = dw_iic_mst_chkerr(iic_ctrl_ptr);
			if (iic_info_ptr->err_state != IIC_ERR_NONE) {
				dw_iic_dis_cbr(iic_info_ptr, DW_IIC_RDY_SND);
				iic_info_ptr->cur_state = IIC_FREE;
				if (iic_info_ptr->iic_cbs.err_cb) {
					iic_info_ptr->iic_cbs.err_cb(iic_obj);
				}
				/* clear the send buffer pointer */
				memset(buf_ptr, 0, sizeof(DEV_BUFFER));
			}
		}
	} else {
		dw_iic_dis_cbr(iic_info_ptr, DW_IIC_RDY_SND);
		iic_info_ptr->cur_state = IIC_FREE;
	}
	/* Clear Interrupt */
	iic_int_status = iic_reg_ptr->IC_CLR_INTR;
}

/** IIC Master receive called in interrupt */
static void dw_iic_mst_int_read(DEV_IIC *iic_obj)
{
	DEV_IIC_INFO *iic_info_ptr = &(iic_obj->iic_info);
	DW_IIC_CTRL *iic_ctrl_ptr = (DW_IIC_CTRL_PTR)(iic_info_ptr->iic_ctrl);
	DW_IIC_REG *iic_reg_ptr = (DW_IIC_REG_PTR)(iic_ctrl_ptr->dw_iic_regs);
	uint32_t iic_int_status; /** iic interrupt status */
	uint32_t last_cond, xmit_data;
	DEV_BUFFER *buf_ptr;
	DW_IIC_BUFFER *dw_iic_rxbuf_ptr;
	uint8_t *p_charbuf;

	if (iic_info_ptr->next_cond == IIC_MODE_STOP) {
		last_cond = IC_DATA_CMD_STOP;
	} else {
		last_cond = IC_DATA_CMD_RESTART;
	}
	iic_int_status = (iic_reg_ptr->IC_INTR_STAT);
	buf_ptr = &(iic_info_ptr->rx_buf);
	p_charbuf = (uint8_t *)buf_ptr->buf;
	if (p_charbuf) {
		dw_iic_rxbuf_ptr = &(iic_ctrl_ptr->dw_iic_rxbuf);
		if (iic_int_status & IC_INTR_STAT_TX_EMPTY) {
			while (dw_iic_putready(iic_reg_ptr)) {
				if (dw_iic_rxbuf_ptr->ofs >= dw_iic_rxbuf_ptr->len) {
					dw_iic_mask_interrupt(iic_reg_ptr, IC_INTR_STAT_TX_EMPTY);
					break;
				}
				xmit_data = IC_DATA_CMD_READ_REQ;
				if (dw_iic_rxbuf_ptr->ofs == (dw_iic_rxbuf_ptr->len-1)) {
					xmit_data |= last_cond;
				} else {
					xmit_data |= IC_DATA_CMD_NONE;
				}
				dw_iic_rxbuf_ptr->ofs ++;
				dw_iic_putdata(iic_reg_ptr, xmit_data);
			}
		}
		if (iic_int_status & IC_INTR_STAT_RX_FULL) {
			while (dw_iic_getready(iic_reg_ptr)) {
				p_charbuf[buf_ptr->ofs] = dw_iic_getdata(iic_reg_ptr);
				buf_ptr->ofs ++;
				if (buf_ptr->ofs >= buf_ptr->len) {
					dw_iic_dis_cbr(iic_info_ptr, DW_IIC_RDY_RCV);
					iic_info_ptr->cur_state = IIC_FREE;
					if (iic_info_ptr->iic_cbs.rx_cb) {
						iic_info_ptr->iic_cbs.rx_cb(iic_obj);
					}
					/* clear the send buffer pointer */
					memset(buf_ptr, 0, sizeof(DEV_BUFFER));
					dw_iic_rxbuf_ptr->ofs = 0;
					dw_iic_rxbuf_ptr->len = 0;
					break;
				}
			}
		}
		if (iic_int_status & (IC_INTR_STAT_RX_OVER|IC_INTR_STAT_RX_UNDER)) {
			iic_ctrl_ptr->iic_rx_over ++;
		}
		if (iic_int_status & IC_INTR_STAT_TX_ABRT) {
			iic_info_ptr->err_state = dw_iic_mst_chkerr(iic_ctrl_ptr);
			if (iic_info_ptr->err_state != IIC_ERR_NONE) {
				dw_iic_dis_cbr(iic_info_ptr, DW_IIC_RDY_RCV);
				iic_info_ptr->cur_state = IIC_FREE;
				if (iic_info_ptr->iic_cbs.err_cb) {
					iic_info_ptr->iic_cbs.err_cb(iic_obj);
				}
				/* clear the send buffer pointer */
				memset(buf_ptr, 0, sizeof(DEV_BUFFER));
				dw_iic_rxbuf_ptr->ofs = 0;
				dw_iic_rxbuf_ptr->len = 0;
			}
		}
	} else {
		dw_iic_dis_cbr(iic_info_ptr, DW_IIC_RDY_RCV);
		iic_info_ptr->cur_state = IIC_FREE;
	}
	/* Clear Interrupt */
	iic_int_status = iic_reg_ptr->IC_CLR_INTR;
}

/** IIC Slave transmit called in interrupt */
static void dw_iic_slv_int_process(DEV_IIC *iic_obj)
{
	DEV_IIC_INFO *iic_info_ptr = &(iic_obj->iic_info);
	DW_IIC_CTRL *iic_ctrl_ptr = (DW_IIC_CTRL_PTR)(iic_info_ptr->iic_ctrl);
	DW_IIC_REG *iic_reg_ptr = (DW_IIC_REG_PTR)(iic_ctrl_ptr->dw_iic_regs);
	uint32_t iic_int_status; /** iic interrupt status */

	iic_int_status = (iic_reg_ptr->IC_INTR_STAT);
	if (iic_int_status & IC_INTR_STAT_RD_REQ) { /* Read request from master */
		if (iic_info_ptr->iic_cbs.tx_cb) {
			iic_info_ptr->iic_cbs.tx_cb(iic_obj);
		} else { /* When tx callback function is not set disable this tx int for slave */
			dw_iic_dis_cbr(iic_info_ptr, DW_IIC_RDY_SND);
		}
	}
	if (iic_int_status & IC_INTR_STAT_RX_FULL) { /* Write request from master */
		if (iic_info_ptr->iic_cbs.rx_cb) {
			iic_info_ptr->iic_cbs.rx_cb(iic_obj);
		} else { /* When rx callback function is not set disable this rx int for slave */
			dw_iic_dis_cbr(iic_info_ptr, DW_IIC_RDY_RCV);
		}
	}
	if (iic_int_status & IC_INTR_STAT_TX_OVER) {
		iic_ctrl_ptr->iic_tx_over ++;
	}
	if (iic_int_status & (IC_INTR_STAT_RX_OVER|IC_INTR_STAT_RX_UNDER)) {
		iic_ctrl_ptr->iic_rx_over ++;
	}
	if (iic_int_status & IC_INTR_STAT_TX_ABRT) {
		iic_info_ptr->err_state = dw_iic_slv_chkerr(iic_ctrl_ptr);
		if (iic_info_ptr->err_state != IIC_ERR_NONE) {
			if (iic_info_ptr->iic_cbs.err_cb) {
				iic_info_ptr->iic_cbs.err_cb(iic_obj);
			}
		}
	}
	/* Clear Interrupt */
	iic_int_status = iic_reg_ptr->IC_CLR_INTR;
}

/** @} end of group DEVICE_DW_IIC_STATIC */

/**
 * \defgroup	DEVICE_DW_IIC_IMPLEMENT	DesignWare IIC Driver Function API Implement
 * \ingroup	DEVICE_DW_IIC
 * \brief	implement device hal iic api with DesignWare IIC
 * @{
 */

/**
 * \brief	open a designware iic device
 * \param[in]	iic_obj	iic device object pointer
 * \param[in]	mode	iic working mode (master or slave)
 * \param[in]	param	When mode is \ref DEV_MASTER_MODE, param stands for \ref dev_iic_info::speed_mode "speed mode",
 *			when mode is \ref DEV_SLAVE_MODE, param stands for \ref dev_iic_info::slv_addr "slave device 7bit address"
 * \retval	E_OK	Open successfully without any issues
 * \retval	E_OPNED	If device was opened before with different parameters,
 *			then just increase the \ref dev_iic_info::opn_cnt "opn_cnt" and return \ref E_OPNED
 * \retval	E_OBJ	Device object is not valid
 * \retval	E_SYS	Device is opened for different mode before, if you want to open it with different mode, you need to fully close it first.
 * \retval	E_PAR	Parameter is not valid
 * \retval	E_NOSPT	Open settings are not supported
 */
int32_t dw_iic_open (DEV_IIC *iic_obj, uint32_t mode, uint32_t param)
{
	int32_t ercd = E_OK;
	uint32_t support_modes;
	uint32_t param2check;
	DEV_IIC_INFO *iic_info_ptr = &(iic_obj->iic_info);

	/* START ERROR CHECK */
	VALID_CHK_IIC_INFO_OBJECT(iic_info_ptr);
	DW_IIC_CHECK_EXP((mode==DEV_MASTER_MODE)||(mode==DEV_SLAVE_MODE), E_PAR);
	if (mode == DEV_MASTER_MODE) {
		DW_IIC_CHECK_EXP((param>=IIC_SPEED_STANDARD) && (param<=IIC_SPEED_ULTRA), E_PAR);
	}
	/* END OF ERROR CHECK */

	DW_IIC_CTRL *iic_ctrl_ptr = (DW_IIC_CTRL *)(iic_info_ptr->iic_ctrl);

	/* Check supported modes, master or slave */
	support_modes = iic_ctrl_ptr->support_modes;
	DW_IIC_CHECK_EXP( (((support_modes)&DW_IIC_MASTER_SUPPORTED)&&(mode == DEV_MASTER_MODE)) || \
				(((support_modes)&DW_IIC_SLAVE_SUPPORTED)&&(mode == DEV_SLAVE_MODE)), E_NOSPT);

	/** Check opened before use case */
	if (iic_info_ptr->opn_cnt > 0) {
		if (mode != iic_info_ptr->mode) {
			/* current working mode is different from passing mode */
			return E_SYS;
		}
		if (mode == DEV_MASTER_MODE) { /* param is speed_mode when as master */
			param2check = iic_info_ptr->speed_mode;
		} else { /* param is slv_addr when as slave */
			param2check = iic_info_ptr->slv_addr;
		}
		iic_info_ptr->opn_cnt ++;
		if (param != param2check) { /* open with different speed mode */
			return E_OPNED;
		} else {
			return E_OK;
		}
	}
	/* auto increase open count */
	iic_info_ptr->opn_cnt ++;

	iic_info_ptr->mode = mode;
	if (iic_info_ptr->addr_mode == IIC_7BIT_ADDRESS) {
		iic_info_ptr->tar_addr &= IIC_7BIT_ADDRESS_MASK;
		iic_info_ptr->slv_addr &= IIC_7BIT_ADDRESS_MASK;
	} else {
		iic_info_ptr->addr_mode = IIC_10BIT_ADDRESS;
		iic_info_ptr->tar_addr &= IIC_10BIT_ADDRESS_MASK;
		iic_info_ptr->slv_addr &= IIC_10BIT_ADDRESS_MASK;
	}

/* Do FIFO Length get before init */
#if DW_IIC_CALC_FIFO_LEN_ENABLE
	iic_ctrl_ptr->tx_fifo_len = dw_iic_get_txfifo_len(iic_ctrl_ptr->dw_iic_regs);
	iic_ctrl_ptr->rx_fifo_len = dw_iic_get_rxfifo_len(iic_ctrl_ptr->dw_iic_regs);
#endif

	/* Disable device before init it */
	dw_iic_disable_device(iic_info_ptr);

	if (mode == DEV_MASTER_MODE) {
		iic_info_ptr->speed_mode = param;
		dw_iic_master_init(iic_ctrl_ptr, param, iic_info_ptr->addr_mode, iic_info_ptr->tar_addr);
	} else {
		iic_info_ptr->slv_addr = param;
		dw_iic_slave_init(iic_ctrl_ptr, iic_info_ptr->addr_mode, param);
	}
	iic_info_ptr->status = DEV_ENABLED;
	iic_info_ptr->cur_state = IIC_FREE;
	iic_info_ptr->err_state = IIC_ERR_NONE;
	iic_info_ptr->next_cond = IIC_MODE_STOP;
	iic_info_ptr->extra = NULL;

	iic_ctrl_ptr->iic_tx_over = 0;
	iic_ctrl_ptr->iic_rx_over = 0;
	iic_ctrl_ptr->int_status = 0;
	memset(&(iic_ctrl_ptr->dw_iic_rxbuf), 0, sizeof(DW_IIC_BUFFER));
	iic_ctrl_ptr->dw_iic_rxbuf.buf = &(iic_info_ptr->rx_buf);
	/** install iic interrupt into system */
	dw_iic_disable_interrupt(iic_info_ptr);
	int_handler_install(iic_ctrl_ptr->intno, iic_ctrl_ptr->dw_iic_int_handler);
	memset(&(iic_info_ptr->tx_buf), 0, sizeof(DEV_BUFFER));
	memset(&(iic_info_ptr->rx_buf), 0, sizeof(DEV_BUFFER));
	memset(&(iic_info_ptr->iic_cbs), 0, sizeof(DEV_IIC_CBS));

error_exit:
	return ercd;
}

/**
 * \brief	Close a DesignWare IIC device
 * \param[in]	iic_obj	iic device object pointer
 * \retval	E_OK	Close successfully without any issues(including secenary that device is already closed)
 * \retval	E_OPNED	Device is still opened, the device \ref dev_iic_info::opn_cnt "opn_cnt" decreased by 1
 * \retval	E_OBJ	Device object is not valid
 */
int32_t dw_iic_close (DEV_IIC *iic_obj)
{
	int32_t ercd = E_OK;
	DEV_IIC_INFO *iic_info_ptr = &(iic_obj->iic_info);

	/* START ERROR CHECK */
	VALID_CHK_IIC_INFO_OBJECT(iic_info_ptr);
	DW_IIC_CHECK_EXP(iic_info_ptr->opn_cnt > 0, E_OK);
	/* END OF ERROR CHECK */

	iic_info_ptr->opn_cnt --;
	if (iic_info_ptr->opn_cnt == 0) {
		dw_iic_disable_interrupt(iic_info_ptr);
		dw_iic_abort_tx(iic_obj);
		dw_iic_abort_rx(iic_obj);
		memset(&(iic_info_ptr->tx_buf), 0, sizeof(DEV_BUFFER));
		memset(&(iic_info_ptr->rx_buf), 0, sizeof(DEV_BUFFER));
		memset(&(iic_info_ptr->iic_cbs), 0, sizeof(DEV_IIC_CBS));
		dw_iic_disable_device(iic_info_ptr);
		iic_info_ptr->status = DEV_DISABLED;
		iic_info_ptr->next_cond = IIC_MODE_STOP;
		iic_info_ptr->extra = NULL;
	} else {
		ercd = E_OPNED;
	}

error_exit:
	return ercd;
}

/**
 * \brief	Control iic by ctrl command
 * \param[in]	iic_obj	iic device object pointer
 * \param[in]		ctrl_cmd	\ref DEVICE_HAL_IIC_CTRLCMD "control command", to change or get some thing related to iic
 * \param[in,out]	param		parameters that maybe argument of the command,
 * 					or return values of the command, must not be NULL
 * \retval	E_OK	Control device successfully
 * \retval	E_CLSED	Device is not opened
 * \retval	E_OBJ	Device object is not valid or not exists
 * \retval	E_PAR	Parameter is not valid for current control command
 * \retval	E_SYS	Control device failed, due to hardware issues, such as device is disabled
 * \retval	E_CTX	Control device failed, due to different reasons like in transfer state
 * \retval	E_NOSPT	Control command is not supported or not valid
 */
int32_t dw_iic_control (DEV_IIC *iic_obj, uint32_t ctrl_cmd, void *param)
{
	int32_t ercd = E_OK;
	DEV_IIC_INFO *iic_info_ptr = &(iic_obj->iic_info);

	/* START ERROR CHECK */
	VALID_CHK_IIC_INFO_OBJECT(iic_info_ptr);
	DW_IIC_CHECK_EXP(iic_info_ptr->opn_cnt > 0, E_CLSED);
	/* END OF ERROR CHECK */

	uint32_t val32; /** to receive unsigned int value */
	DEV_BUFFER *devbuf;

	DW_IIC_CTRL *iic_ctrl_ptr = (DW_IIC_CTRL *)(iic_info_ptr->iic_ctrl);
	DW_IIC_REG *iic_reg_ptr = (DW_IIC_REG *)(iic_ctrl_ptr->dw_iic_regs);

	/* check whether current device is disabled */
	if ((iic_info_ptr->status & DEV_ENABLED) == 0) {
		/** When device is disabled,
		 * only IIC_CMD_ENA_DEV, IIC_CMD_DIS_DEV, IIC_CMD_GET_STATUS, IIC_CMD_RESET
		 * are available, other commands will return E_SYS
		 */
		if ((ctrl_cmd != IIC_CMD_ENA_DEV) && \
			(ctrl_cmd != IIC_CMD_DIS_DEV) && \
			(ctrl_cmd != IIC_CMD_GET_STATUS) && \
			(ctrl_cmd != IIC_CMD_RESET) ) {
			return E_SYS;
		}
	}

	switch (ctrl_cmd) {
		/* Commmon commands for both master and slave mode */
		case IIC_CMD_GET_STATUS:
			DW_IIC_CHECK_EXP((param!=NULL) && CHECK_ALIGN_4BYTES(param), E_PAR);
			*((int32_t *)param) = iic_info_ptr->status;
			break;
		case IIC_CMD_ENA_DEV:
			dw_iic_enable_device(iic_info_ptr);
			break;
		case IIC_CMD_DIS_DEV:
			dw_iic_disable_device(iic_info_ptr);
			break;
		case IIC_CMD_RESET:
			dw_iic_reset_device(iic_info_ptr);
			break;
		case IIC_CMD_FLUSH_TX:
			dw_iic_flush_tx(iic_reg_ptr);
			break;
		case IIC_CMD_FLUSH_RX:
			dw_iic_flush_rx(iic_reg_ptr);
			break;
		case IIC_CMD_SET_ADDR_MODE:
			val32 = (uint32_t)param;
			DW_IIC_CHECK_EXP((val32==IIC_7BIT_ADDRESS) || (val32==IIC_10BIT_ADDRESS), E_PAR);
			if (iic_info_ptr->mode == DEV_MASTER_MODE) {
				dw_iic_set_mstaddr_mode(iic_reg_ptr, val32);
			} else {
				dw_iic_set_slvaddr_mode(iic_reg_ptr, val32);
			}
			iic_info_ptr->addr_mode = val32;
			break;
		case IIC_CMD_GET_RXAVAIL:
			DW_IIC_CHECK_EXP((param!=NULL) && CHECK_ALIGN_4BYTES(param), E_PAR);
			*((int32_t *)param) = dw_iic_get_rxavail(iic_ctrl_ptr);
			break;
		case IIC_CMD_GET_TXAVAIL:
			DW_IIC_CHECK_EXP((param!=NULL) && CHECK_ALIGN_4BYTES(param), E_PAR);
			*((int32_t *)param) = dw_iic_get_txavail(iic_ctrl_ptr);
			break;
		case IIC_CMD_SET_TXCB:
			DW_IIC_CHECK_EXP(CHECK_ALIGN_4BYTES(param), E_PAR);
			iic_info_ptr->iic_cbs.tx_cb = param;
			break;
		case IIC_CMD_SET_RXCB:
			DW_IIC_CHECK_EXP(CHECK_ALIGN_4BYTES(param), E_PAR);
			iic_info_ptr->iic_cbs.rx_cb = param;
			break;
		case IIC_CMD_SET_ERRCB:
			DW_IIC_CHECK_EXP(CHECK_ALIGN_4BYTES(param), E_PAR);
			iic_info_ptr->iic_cbs.err_cb = param;
			break;
		case IIC_CMD_ABORT_TX:
			dw_iic_abort_tx(iic_obj);
			if ((iic_info_ptr->mode == DEV_MASTER_MODE) \
				&& (iic_info_ptr->cur_state == IIC_IN_TX)) {
				iic_info_ptr->cur_state = IIC_FREE;
			}
			break;
		case IIC_CMD_ABORT_RX:
			dw_iic_abort_rx(iic_obj);
			if ((iic_info_ptr->mode == DEV_MASTER_MODE) \
				&& (iic_info_ptr->cur_state == IIC_IN_RX)) {
				iic_info_ptr->cur_state = IIC_FREE;
			}
			break;
		case IIC_CMD_SET_TXINT:
			if (iic_info_ptr->mode == DEV_MASTER_MODE) {
				DW_IIC_CHECK_EXP(iic_info_ptr->cur_state != IIC_IN_RX, E_CTX);
			}
			val32 = (uint32_t)param;
			if (val32 == 0) {
				dw_iic_dis_cbr(iic_info_ptr, DW_IIC_RDY_SND);
				iic_info_ptr->cur_state = IIC_FREE;
			} else {
				iic_info_ptr->cur_state = IIC_IN_TX;
				dw_iic_ena_cbr(iic_info_ptr, DW_IIC_RDY_SND);
			}
			break;
		case IIC_CMD_SET_RXINT:
			if (iic_info_ptr->mode == DEV_MASTER_MODE) {
				DW_IIC_CHECK_EXP(iic_info_ptr->cur_state != IIC_IN_TX, E_CTX);
			}
			val32 = (uint32_t)param;
			if (val32 == 0) {
				iic_info_ptr->cur_state = IIC_FREE;
				dw_iic_dis_cbr(iic_info_ptr, DW_IIC_RDY_RCV);
			} else {
				iic_info_ptr->cur_state = IIC_IN_RX;
				dw_iic_ena_cbr(iic_info_ptr, DW_IIC_RDY_RCV);
			}
			break;
		case IIC_CMD_SET_TXINT_BUF:
			if (iic_info_ptr->mode == DEV_MASTER_MODE) {
				DW_IIC_CHECK_EXP(iic_info_ptr->cur_state != IIC_IN_TX, E_CTX);
			}
			DW_IIC_CHECK_EXP(CHECK_ALIGN_4BYTES(param), E_PAR);
			if (param != NULL) {
				devbuf = (DEV_BUFFER *)param;
				iic_info_ptr->tx_buf = *devbuf;
				iic_info_ptr->tx_buf.ofs = 0;
			} else {
				iic_info_ptr->tx_buf.buf = NULL;
				iic_info_ptr->tx_buf.len = 0;
				iic_info_ptr->tx_buf.ofs = 0;
			}
			break;
		case IIC_CMD_SET_RXINT_BUF:
			if (iic_info_ptr->mode == DEV_MASTER_MODE) {
				DW_IIC_CHECK_EXP(iic_info_ptr->cur_state != IIC_IN_RX, E_CTX);
			}
			DW_IIC_CHECK_EXP(CHECK_ALIGN_4BYTES(param), E_PAR);
			if (param != NULL) {
				devbuf = (DEV_BUFFER *)param;
				iic_info_ptr->rx_buf = *devbuf;
				iic_info_ptr->rx_buf.ofs = 0;
				iic_ctrl_ptr->dw_iic_rxbuf.ofs = 0;
				iic_ctrl_ptr->dw_iic_rxbuf.len = devbuf->len;
			} else {
				iic_info_ptr->rx_buf.buf = NULL;
				iic_info_ptr->rx_buf.len = 0;
				iic_info_ptr->rx_buf.ofs = 0;
				iic_ctrl_ptr->dw_iic_rxbuf.ofs = 0;
				iic_ctrl_ptr->dw_iic_rxbuf.len = 0;
			}
			break;

		/* Master mode only commands */
		case IIC_CMD_MST_SET_SPEED_MODE:
			DW_IIC_CHECK_EXP(iic_info_ptr->mode == DEV_MASTER_MODE, E_NOSPT);
			val32 = (uint32_t)param;
			DW_IIC_CHECK_EXP((val32>=IIC_SPEED_STANDARD) && (val32<=IIC_SPEED_ULTRA), E_PAR);
			dw_iic_set_speedmode(iic_reg_ptr, val32);
			iic_info_ptr->speed_mode = val32;
			break;
		case IIC_CMD_MST_SET_TAR_ADDR:
			DW_IIC_CHECK_EXP(iic_info_ptr->mode == DEV_MASTER_MODE, E_NOSPT);
			if (iic_info_ptr->addr_mode == IIC_7BIT_ADDRESS) {
				val32 = ((uint32_t)param) & IIC_7BIT_ADDRESS_MASK;
			} else {
				val32 = ((uint32_t)param) & IIC_10BIT_ADDRESS_MASK;
			}
			if (val32 != iic_info_ptr->tar_addr) {
				dw_iic_set_taraddr(iic_reg_ptr, val32);
				iic_info_ptr->tar_addr = val32;
			}
			break;
		case IIC_CMD_MST_SET_NEXT_COND:
			DW_IIC_CHECK_EXP(iic_info_ptr->mode == DEV_MASTER_MODE, E_NOSPT);
			val32 = (uint32_t)param;
			DW_IIC_CHECK_EXP((val32==IIC_MODE_STOP) || (val32==IIC_MODE_RESTART), E_PAR);
			iic_info_ptr->next_cond = (uint32_t)param;
			break;

		/* Slave mode only commands */
		case IIC_CMD_SLV_SET_SLV_ADDR:
			DW_IIC_CHECK_EXP(iic_info_ptr->mode == DEV_SLAVE_MODE, E_NOSPT);
			if (iic_info_ptr->addr_mode == IIC_7BIT_ADDRESS) {
				val32 = ((uint32_t)param) & IIC_7BIT_ADDRESS_MASK;
			} else {
				val32 = ((uint32_t)param) & IIC_10BIT_ADDRESS_MASK;
			}
			dw_iic_set_slvaddr(iic_reg_ptr, val32);
			iic_info_ptr->slv_addr = val32;
			break;
		case IIC_CMD_SLV_GET_SLV_STATE:
			DW_IIC_CHECK_EXP(iic_info_ptr->mode == DEV_SLAVE_MODE, E_NOSPT);
			DW_IIC_CHECK_EXP((param!=NULL) && CHECK_ALIGN_4BYTES(param), E_PAR);
			*((uint32_t *)param) = dw_iic_get_slv_state(iic_reg_ptr);
			break;

		default:
			ercd = E_NOSPT;
			break;
	}

error_exit:
	return ercd;
}

/**
 * \brief	poll transmit data through DesignWare IIC as master or slave
 * \param[in]	iic_obj	iic device object pointer
 * \param[in]	data	data that need to send (data must be uint8_t type)
 * \param[in]	len	data length need to send
 * \retval	>0	Byte count that was successfully sent for poll method,
 * 			it might can't send that much due to \ref \ref dev_iic_info::err_state "different error state".
 * \retval	E_OBJ	Device object is not valid or not exists
 * \retval	E_PAR	Parameter is not valid
 * \retval	E_CTX	Device is still in transfer state
 * \retval	E_SYS	Can't write data to hardware due to hardware issues, such as device is disabled
 */
int32_t dw_iic_write (DEV_IIC *iic_obj, const void *data, uint32_t len)
{
	int32_t ercd = E_OK;
	DEV_IIC_INFO *iic_info_ptr = &(iic_obj->iic_info);

	/* START ERROR CHECK */
	VALID_CHK_IIC_INFO_OBJECT(iic_info_ptr);
	DW_IIC_CHECK_EXP(iic_info_ptr->opn_cnt > 0, E_CLSED);
	DW_IIC_CHECK_EXP(iic_info_ptr->status & DEV_ENABLED, E_SYS);
	DW_IIC_CHECK_EXP(data!=NULL, E_PAR);
	DW_IIC_CHECK_EXP(len>0, E_PAR);
	/* END OF ERROR CHECK */

	int32_t i = 0;
	uint32_t last_cond = 0; /* Last data for transmit, STOP or RESTART */
	int32_t error_state = IIC_ERR_NONE;
	const uint8_t *p_charbuf = (const uint8_t *)data;

	DW_IIC_CTRL *iic_ctrl_ptr = (DW_IIC_CTRL_PTR)(iic_info_ptr->iic_ctrl);

	if (iic_info_ptr->mode == DEV_MASTER_MODE) { /* Master mode transmit data */
		if (iic_info_ptr->next_cond == IIC_MODE_STOP) {
			last_cond = IC_DATA_CMD_STOP;
		} else {
			last_cond = IC_DATA_CMD_RESTART;
		}

		/* Try to transmit 0 -> (len-1) data */
		len = len - 1; /* Last data write differently */
		while (i < len) {
			error_state = dw_iic_mst_write_data(iic_ctrl_ptr, (uint32_t)(p_charbuf[i]), IC_DATA_CMD_NONE);
			if (error_state != IIC_ERR_NONE) {
				break;
			}
			i ++;
		}
		/* Try to transmit the last data with STOP or RESTART condition */
		if (error_state == IIC_ERR_NONE) {
			error_state = dw_iic_mst_write_data(iic_ctrl_ptr, (uint32_t)(p_charbuf[len]), last_cond);
			if (error_state == IIC_ERR_NONE) {
				i = i + 1; /* Add last data into send count */
			}
		}
	} else { /* Slave mode transmit data */
		while (i < len) {
			error_state = dw_iic_slv_write_data(iic_ctrl_ptr, (uint32_t)(p_charbuf[i]));
			if (error_state != IIC_ERR_NONE) {
				break;
			}
			i ++;
		}
	}
	iic_info_ptr->err_state = error_state;
	ercd = i;

error_exit:
	return ercd;
}

/**
 * \brief	read data through DesignWare IIC
 * \param[in]	iic_obj	iic device object pointer
 * \param[out]	data	data that need to read (data must be uint8_t type)
 * \param[in]	len	data count need to read
 * \retval	>0	Byte count that was successfully received for poll method,
 * 			it might can't send that much due to \ref \ref dev_iic_info::err_state "different error state".
 * \retval	E_OBJ	Device object is not valid or not exists
 * \retval	E_CTX	Device is still in transfer state
 * \retval	E_PAR	Parameter is not valid
 * \retval	E_SYS	Can't receive data from hardware due to hardware issues, such as device is disabled
 */
int32_t dw_iic_read (DEV_IIC *iic_obj, void *data, uint32_t len)
{
	int32_t ercd = E_OK;
	DEV_IIC_INFO *iic_info_ptr = &(iic_obj->iic_info);

	/* START ERROR CHECK */
	VALID_CHK_IIC_INFO_OBJECT(iic_info_ptr);
	DW_IIC_CHECK_EXP(iic_info_ptr->opn_cnt > 0, E_CLSED);
	DW_IIC_CHECK_EXP(iic_info_ptr->status & DEV_ENABLED, E_SYS);
	DW_IIC_CHECK_EXP(data!=NULL, E_PAR);
	DW_IIC_CHECK_EXP(len>0, E_PAR);
	/* END OF ERROR CHECK */

	int32_t i = 0;
	uint32_t last_cond = 0; /* Last data for receive, STOP or RESTART */
	uint32_t val32 = 0;
	int32_t error_state = IIC_ERR_NONE;
	uint8_t *p_charbuf = (uint8_t *)data;

	DW_IIC_CTRL *iic_ctrl_ptr = (DW_IIC_CTRL_PTR)(iic_info_ptr->iic_ctrl);

	if (iic_info_ptr->mode == DEV_MASTER_MODE) { /* Master mode receive data */
		if (iic_info_ptr->next_cond == IIC_MODE_STOP) {
			last_cond = IC_DATA_CMD_STOP;
		} else {
			last_cond = IC_DATA_CMD_RESTART;
		}

		/* Try to receive 0 -> (len-1) data */
		len = len - 1; /* Last data write differently */
		while (i < len) {
			error_state = dw_iic_mst_read_data(iic_ctrl_ptr, &val32, IC_DATA_CMD_NONE);
			if (error_state != IIC_ERR_NONE) {
				break;
			} else {
				p_charbuf[i] = (uint8_t)val32;
			}
			i ++;
		}
		/* Try to receive the last data with STOP or RESTART condition */
		if (error_state == IIC_ERR_NONE) {
			error_state = dw_iic_mst_read_data(iic_ctrl_ptr, &val32, last_cond);
			if (error_state == IIC_ERR_NONE) {
				p_charbuf[len] = (uint8_t)val32;
				i = i + 1; /* Add last data into send count */
			}
		}
	} else { /* Slave mode receive data */
		while (i < len) {
			error_state = dw_iic_slv_read_data(iic_ctrl_ptr, &val32);
			if (error_state != IIC_ERR_NONE) {
				break;
			} else {
				p_charbuf[i] = (uint8_t)val32;
			}
			i ++;
		}
	}
	iic_info_ptr->err_state = error_state;
	ercd = i;

error_exit:
	return ercd;
}

/**
 * \brief	DesignWare IIC interrupt processing routine
 * \param[in]	iic_info_ptr	DEV_IIC *iic_obj
 * \param[in]	ptr		extra information
 */
void dw_iic_isr(DEV_IIC *iic_obj, void *ptr)
{
	int32_t ercd = E_OK;
	DEV_IIC_INFO *iic_info_ptr = &(iic_obj->iic_info);

	/* START ERROR CHECK */
	VALID_CHK_IIC_INFO_OBJECT(iic_info_ptr);
	/* END OF ERROR CHECK */

	if (iic_info_ptr->mode == DEV_MASTER_MODE) {
		if (iic_info_ptr->cur_state == IIC_IN_TX) {
			dw_iic_mst_int_write(iic_obj);
		} else {
			dw_iic_mst_int_read(iic_obj);
		}
	} else {
		dw_iic_slv_int_process(iic_obj);
	}

error_exit:
	return;
}
/** @} end of group DEVICE_DW_IIC_IMPLEMENT */
