/**
 * \file
 *
 * \brief SAM Control Area Network (CAN) Low Level Driver
 *
 * Copyright (C) 2015-2016 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include "can.h"
#include <string.h>

/* Instance for GCLK setting. */
struct system_gclk_chan_config gclk_chan_conf;

/* Message ram definition. */
COMPILER_ALIGNED(4)
static struct can_rx_element_buffer can0_rx_buffer[CONF_CAN0_RX_BUFFER_NUM];
COMPILER_ALIGNED(4)
static struct can_rx_element_fifo_0 can0_rx_fifo_0[CONF_CAN0_RX_FIFO_0_NUM];
COMPILER_ALIGNED(4)
static struct can_rx_element_fifo_1 can0_rx_fifo_1[CONF_CAN0_RX_FIFO_1_NUM];
COMPILER_ALIGNED(4)
static struct can_tx_element can0_tx_buffer[CONF_CAN0_TX_BUFFER_NUM + CONF_CAN0_TX_FIFO_QUEUE_NUM];
COMPILER_ALIGNED(4)
static struct can_tx_event_element can0_tx_event_fifo[CONF_CAN0_TX_EVENT_FIFO];
COMPILER_ALIGNED(4)
static struct can_standard_message_filter_element can0_rx_standard_filter[CONF_CAN0_RX_STANDARD_ID_FILTER_NUM];
COMPILER_ALIGNED(4)
static struct can_extended_message_filter_element can0_rx_extended_filter[CONF_CAN0_RX_EXTENDED_ID_FILTER_NUM];

COMPILER_ALIGNED(4)
static struct can_rx_element_buffer can1_rx_buffer[CONF_CAN1_RX_BUFFER_NUM];
COMPILER_ALIGNED(4)
static struct can_rx_element_fifo_0 can1_rx_fifo_0[CONF_CAN1_RX_FIFO_0_NUM];
COMPILER_ALIGNED(4)
static struct can_rx_element_fifo_1 can1_rx_fifo_1[CONF_CAN1_RX_FIFO_1_NUM];
COMPILER_ALIGNED(4)
static struct can_tx_element can1_tx_buffer[CONF_CAN1_TX_BUFFER_NUM + CONF_CAN1_TX_FIFO_QUEUE_NUM];
COMPILER_ALIGNED(4)
static struct can_tx_event_element can1_tx_event_fifo[CONF_CAN1_TX_EVENT_FIFO];
COMPILER_ALIGNED(4)
static struct can_standard_message_filter_element can1_rx_standard_filter[CONF_CAN1_RX_STANDARD_ID_FILTER_NUM];
COMPILER_ALIGNED(4)
static struct can_extended_message_filter_element can1_rx_extended_filter[CONF_CAN1_RX_EXTENDED_ID_FILTER_NUM];

static void _can_message_memory_init(Can *hw)
{
	if (hw == CAN0) {
		hw->SIDFC.reg = CAN_SIDFC_FLSSA((uint32_t)can0_rx_standard_filter) |
				CAN_SIDFC_LSS(CONF_CAN0_RX_STANDARD_ID_FILTER_NUM);
		hw->XIDFC.reg = CAN_XIDFC_FLESA((uint32_t)can0_rx_extended_filter) |
				CAN_XIDFC_LSE(CONF_CAN0_RX_EXTENDED_ID_FILTER_NUM);
		hw->RXF0C.reg = CAN_RXF0C_F0SA((uint32_t)can0_rx_fifo_0) |
				CAN_RXF0C_F0S(CONF_CAN0_RX_FIFO_0_NUM);
		hw->RXF1C.reg = CAN_RXF1C_F1SA((uint32_t)can0_rx_fifo_1) |
				CAN_RXF1C_F1S(CONF_CAN0_RX_FIFO_1_NUM);
		hw->RXBC.reg = CAN_RXBC_RBSA((uint32_t)can0_rx_buffer);
		hw->TXBC.reg = CAN_TXBC_TBSA((uint32_t)can0_tx_buffer) |
				CAN_TXBC_NDTB(CONF_CAN0_TX_BUFFER_NUM) |
				CAN_TXBC_TFQS(CONF_CAN0_TX_FIFO_QUEUE_NUM);
		hw->TXEFC.reg = CAN_TXEFC_EFSA((uint32_t)can0_tx_event_fifo) |
				CAN_TXEFC_EFS(CONF_CAN0_TX_EVENT_FIFO);
	} else if (hw == CAN1) {
		hw->SIDFC.reg = CAN_SIDFC_FLSSA((uint32_t)can1_rx_standard_filter) |
				CAN_SIDFC_LSS(CONF_CAN1_RX_STANDARD_ID_FILTER_NUM);
		hw->XIDFC.reg = CAN_XIDFC_FLESA((uint32_t)can1_rx_extended_filter) |
				CAN_XIDFC_LSE(CONF_CAN1_RX_EXTENDED_ID_FILTER_NUM);
		hw->RXF0C.reg = CAN_RXF0C_F0SA((uint32_t)can1_rx_fifo_0) |
				CAN_RXF0C_F0S(CONF_CAN1_RX_FIFO_0_NUM);
		hw->RXF1C.reg = CAN_RXF1C_F1SA((uint32_t)can1_rx_fifo_1) |
				CAN_RXF1C_F1S(CONF_CAN1_RX_FIFO_1_NUM);
		hw->RXBC.reg = CAN_RXBC_RBSA((uint32_t)can1_rx_buffer);
		hw->TXBC.reg = CAN_TXBC_TBSA((uint32_t)can1_tx_buffer) |
				CAN_TXBC_NDTB(CONF_CAN1_TX_BUFFER_NUM) |
				CAN_TXBC_TFQS(CONF_CAN1_TX_FIFO_QUEUE_NUM);
		hw->TXEFC.reg = CAN_TXEFC_EFSA((uint32_t)can1_tx_event_fifo) |
				CAN_TXEFC_EFS(CONF_CAN1_TX_EVENT_FIFO);
	}

	/**
	 * The data size in conf_can.h should be 8/12/16/20/24/32/48/64,
	 * The corresponding setting value in register is 0/1//2/3/4/5/6/7.
	 * To simplify the calculation, seperate to two group 8/12/16/20/24 which
	 * increased with 4 and 32/48/64 which increased with 16.
	 */
	if (CONF_CAN_ELEMENT_DATA_SIZE <= 24) {
		hw->RXESC.reg = CAN_RXESC_RBDS((CONF_CAN_ELEMENT_DATA_SIZE - 8) / 4) |
				CAN_RXESC_F0DS((CONF_CAN_ELEMENT_DATA_SIZE - 8) / 4) |
				CAN_RXESC_F1DS((CONF_CAN_ELEMENT_DATA_SIZE - 8) / 4);
		hw->TXESC.reg = CAN_TXESC_TBDS((CONF_CAN_ELEMENT_DATA_SIZE - 8) / 4);
	} else {
		hw->RXESC.reg = CAN_RXESC_RBDS((CONF_CAN_ELEMENT_DATA_SIZE - 32) / 16 + 5) |
				CAN_RXESC_F0DS((CONF_CAN_ELEMENT_DATA_SIZE - 32) / 16 + 5) |
				CAN_RXESC_F1DS((CONF_CAN_ELEMENT_DATA_SIZE - 32) / 16 + 5);
		hw->TXESC.reg = CAN_TXESC_TBDS((CONF_CAN_ELEMENT_DATA_SIZE - 32) / 16 + 5);
	}
}

static void _can_set_configuration(Can *hw, struct can_config *config)
{
	/* Timing setting. */
	hw->NBTP.reg = CAN_NBTP_NBRP(CONF_CAN_NBTP_NBRP_VALUE) |
			CAN_NBTP_NSJW(CONF_CAN_NBTP_NSJW_VALUE) |
			CAN_NBTP_NTSEG1(CONF_CAN_NBTP_NTSEG1_VALUE) |
			CAN_NBTP_NTSEG2(CONF_CAN_NBTP_NTSEG2_VALUE);
	hw->DBTP.reg = CAN_DBTP_DBRP(CONF_CAN_DBTP_DBRP_VALUE) |
			CAN_DBTP_DSJW(CONF_CAN_DBTP_DSJW_VALUE) |
			CAN_DBTP_DTSEG1(CONF_CAN_DBTP_DTSEG1_VALUE) |
			CAN_DBTP_DTSEG2(CONF_CAN_DBTP_DTSEG2_VALUE);

	if (config->tdc_enable) {
		hw->DBTP.reg |= CAN_DBTP_TDC;
	}
	
	if (config->run_in_standby) {
		hw->MRCFG.reg |= 0x01<<6;
	}

	hw->RWD.reg |= CAN_RWD_WDC(config->watchdog_configuration);

	if (config->transmit_pause) {
		hw->CCCR.reg |= CAN_CCCR_TXP;
	}

	if (config->edge_filtering) {
		hw->CCCR.reg |= CAN_CCCR_EFBI;
	}

	if (config->protocol_exception_handling) {
		hw->CCCR.reg |= CAN_CCCR_PXHD;
	}

	if (!config->automatic_retransmission) {
		hw->CCCR.reg |= CAN_CCCR_DAR;
	}

	if (config->clock_stop_request) {
		hw->CCCR.reg |= CAN_CCCR_CSR;
	}

	if (config->clock_stop_acknowledge) {
		hw->CCCR.reg |= CAN_CCCR_CSA;
	}

	hw->TSCC.reg = CAN_TSCC_TCP(config->timestamp_prescaler) |
			CAN_TSCC_TSS_INC_Val;

	hw->TOCC.reg = CAN_TOCC_TOP(config->timeout_period) |
			config->timeout_mode | config->timeout_enable;

	hw->TDCR.reg = CAN_TDCR_TDCO(config->delay_compensation_offset) |
			CAN_TDCR_TDCF(config->delay_compensation_filter_window_length);

	hw->GFC.reg = CAN_GFC_ANFS(config->nonmatching_frames_action_standard) |
			CAN_GFC_ANFE(config->nonmatching_frames_action_extended);
	if (config->remote_frames_standard_reject) {
		hw->GFC.reg |= CAN_GFC_RRFS;
	}
	if (config->remote_frames_extended_reject) {
		hw->GFC.reg |= CAN_GFC_RRFE;
	}

	hw->XIDAM.reg = config->extended_id_mask;

	if (config->rx_fifo_0_overwrite) {
		hw->RXF0C.reg |= CAN_RXF0C_F0OM;
	}
	hw->RXF0C.reg |= CAN_RXF0C_F0WM(config->rx_fifo_0_watermark);

	if (config->rx_fifo_1_overwrite) {
		hw->RXF1C.reg |= CAN_RXF1C_F1OM;
	}
	hw->RXF1C.reg |= CAN_RXF1C_F1WM(config->rx_fifo_1_watermark);

	if (config->tx_queue_mode) {
		hw->TXBC.reg |= CAN_TXBC_TFQM;
	}

	hw->TXEFC.reg |= CAN_TXEFC_EFWM(config->tx_event_fifo_watermark);
}

static void _can_enable_peripheral_clock(struct can_module *const module_inst)
{
	if (module_inst->hw == CAN0) {
		/* Turn on the digital interface clock. */
		system_ahb_clock_set_mask(MCLK_AHBMASK_CAN0);
	} else if (module_inst->hw == CAN1) {
		/* Turn on the digital interface clock. */
		system_ahb_clock_set_mask(MCLK_AHBMASK_CAN1);
	}
}

void can_init(struct can_module *const module_inst, Can *hw,
		struct can_config *config)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(hw);
	Assert(config);

	/* Associate the software module instance with the hardware module */
	module_inst->hw = hw;

	/* Enable peripheral clock */
	_can_enable_peripheral_clock(module_inst);

	/* Configure GCLK channel */
	system_gclk_chan_get_config_defaults(&gclk_chan_conf);
	gclk_chan_conf.source_generator = config->clock_source;

	if (hw == CAN0) {
		system_gclk_chan_set_config(CAN0_GCLK_ID, &gclk_chan_conf);
		system_gclk_chan_enable(CAN0_GCLK_ID);
	} else if (hw == CAN1) {
		system_gclk_chan_set_config(CAN1_GCLK_ID, &gclk_chan_conf);
		system_gclk_chan_enable(CAN1_GCLK_ID);
	}


	/* Configuration Change Enable. */
	hw->CCCR.reg |= CAN_CCCR_CCE;

	/* Initialize the message memory address. */
	_can_message_memory_init(hw);

	/* Set the configuration. */
	_can_set_configuration(hw, config);

	/* Enable the interrupt setting which no need change. */
	hw->ILE.reg = CAN_ILE_EINT0 | CAN_ILE_EINT1;
	hw->TXBTIE.reg = CAN_TXBTIE_MASK;
	hw->TXBCIE.reg = CAN_TXBCIE_MASK;
}

void can_set_baudrate(Can *hw, uint32_t baudrate)
{
	uint32_t gclk_can_value = 0;
	uint32_t can_nbtp_nbrp_value;
	uint32_t can_nbtp_nsgw_value = 3, can_nbtp_ntseg1_value = 10, can_nbtp_ntseg2_value = 3;
	
	if (hw == CAN0) {
		gclk_can_value = system_gclk_chan_get_hz(CAN0_GCLK_ID);
		} else if (hw == CAN1) {
		gclk_can_value = system_gclk_chan_get_hz(CAN1_GCLK_ID);
	}
	
	can_nbtp_nbrp_value = gclk_can_value / baudrate / (3 + can_nbtp_ntseg1_value + can_nbtp_ntseg2_value);
	
	hw->NBTP.reg = CAN_NBTP_NBRP(can_nbtp_nbrp_value) |
			CAN_NBTP_NSJW(can_nbtp_nsgw_value) |
			CAN_NBTP_NTSEG1(can_nbtp_ntseg1_value) |
			CAN_NBTP_NTSEG2(can_nbtp_ntseg2_value);
}

void can_fd_set_baudrate(Can *hw, uint32_t baudrate)
{
	uint32_t gclk_can_fd_value = 0;
	uint32_t can_fd_dbtp_dbrp_value;
	uint32_t can_fd_dbtp_dsgw_value = 3, can_fd_dbtp_dtseg1_value = 10, can_fd_dbtp_dtseg2_value = 3;
	
	if (hw == CAN0) {
		gclk_can_fd_value = system_gclk_chan_get_hz(CAN0_GCLK_ID);
		} else if (hw == CAN1) {
		gclk_can_fd_value = system_gclk_chan_get_hz(CAN1_GCLK_ID);
	}
	
	can_fd_dbtp_dbrp_value = gclk_can_fd_value / baudrate / (3 + can_fd_dbtp_dtseg1_value + can_fd_dbtp_dtseg2_value);
	
	hw->NBTP.reg = CAN_DBTP_DBRP(can_fd_dbtp_dbrp_value) |
			CAN_DBTP_DSJW(can_fd_dbtp_dsgw_value) |
			CAN_DBTP_DTSEG1(can_fd_dbtp_dtseg1_value) |
			CAN_DBTP_DTSEG2(can_fd_dbtp_dtseg2_value);
}

void can_start(struct can_module *const module_inst)
{
	module_inst->hw->CCCR.reg &= ~CAN_CCCR_INIT;
	/* Wait for the sync. */
	while (module_inst->hw->CCCR.reg & CAN_CCCR_INIT);
}

void can_stop(struct can_module *const module_inst)
{
	module_inst->hw->CCCR.reg |= CAN_CCCR_INIT;
	/* Wait for the sync. */
	while (!(module_inst->hw->CCCR.reg & CAN_CCCR_INIT));
}

void can_enable_fd_mode(struct can_module *const module_inst)
{
	module_inst->hw->CCCR.reg |= CAN_CCCR_INIT;
	/* Wait for the sync. */
	while (!(module_inst->hw->CCCR.reg & CAN_CCCR_INIT));
	module_inst->hw->CCCR.reg |= CAN_CCCR_CCE;

	module_inst->hw->CCCR.reg |= CAN_CCCR_FDOE;
	module_inst->hw->CCCR.reg |= CAN_CCCR_BRSE;
}

void can_disable_fd_mode(struct can_module *const module_inst)
{
	module_inst->hw->CCCR.reg &= ~CAN_CCCR_FDOE;
}

void can_enable_restricted_operation_mode(
		struct can_module *const module_inst)
{
	module_inst->hw->CCCR.reg |= CAN_CCCR_INIT;
	/* Wait for the sync. */
	while (!(module_inst->hw->CCCR.reg & CAN_CCCR_INIT));
	module_inst->hw->CCCR.reg |= CAN_CCCR_CCE;

	module_inst->hw->CCCR.reg |= CAN_CCCR_ASM;
}

void can_disable_restricted_operation_mode(
		struct can_module *const module_inst)
{
	module_inst->hw->CCCR.reg &= ~CAN_CCCR_ASM;
}

void can_enable_bus_monitor_mode(struct can_module *const module_inst)
{
	module_inst->hw->CCCR.reg |= CAN_CCCR_INIT;
	/* Wait for the sync. */
	while (!(module_inst->hw->CCCR.reg & CAN_CCCR_INIT));
	module_inst->hw->CCCR.reg |= CAN_CCCR_CCE;

	module_inst->hw->CCCR.reg |= CAN_CCCR_MON;
}

void can_disable_bus_monitor_mode(struct can_module *const module_inst)
{
	module_inst->hw->CCCR.reg &= ~CAN_CCCR_MON;
}

void can_enable_sleep_mode(struct can_module *const module_inst)
{
	module_inst->hw->CCCR.reg |= CAN_CCCR_CSR;
	/* Wait for the sync. */
	while (!(module_inst->hw->CCCR.reg & CAN_CCCR_INIT));

	while (!(module_inst->hw->CCCR.reg & CAN_CCCR_CSA));
}

void can_disable_sleep_mode(struct can_module *const module_inst)
{
	/* Enable peripheral clock */
	_can_enable_peripheral_clock(module_inst);
	if (module_inst->hw == CAN0) {
		system_gclk_chan_set_config(CAN0_GCLK_ID, &gclk_chan_conf);
		system_gclk_chan_enable(CAN0_GCLK_ID);
	}

	if (module_inst->hw == CAN1) {
		system_gclk_chan_set_config(CAN1_GCLK_ID, &gclk_chan_conf);
		system_gclk_chan_enable(CAN1_GCLK_ID);
	}
	module_inst->hw->CCCR.reg &= CAN_CCCR_CSR;
	while ((module_inst->hw->CCCR.reg & CAN_CCCR_CSA));
}

void can_enable_test_mode(struct can_module *const module_inst)
{
	module_inst->hw->CCCR.reg |= CAN_CCCR_INIT;
	/* Wait for the sync. */
	while (!(module_inst->hw->CCCR.reg & CAN_CCCR_INIT));
	module_inst->hw->CCCR.reg |= CAN_CCCR_CCE;

	module_inst->hw->CCCR.reg |= CAN_CCCR_TEST;
	module_inst->hw->TEST.reg |= CAN_TEST_LBCK;
}

void can_disable_test_mode(struct can_module *const module_inst)
{
	module_inst->hw->CCCR.reg &= ~CAN_CCCR_TEST;
}

enum status_code can_set_rx_standard_filter(
		struct can_module *const module_inst,
		struct can_standard_message_filter_element *sd_filter, uint32_t index)
{
	if (module_inst->hw == CAN0) {
		can0_rx_standard_filter[index].S0.reg = sd_filter->S0.reg;
		return STATUS_OK;
	} else if (module_inst->hw == CAN1) {
		can1_rx_standard_filter[index].S0.reg = sd_filter->S0.reg;
		return STATUS_OK;
	}
	return STATUS_ERR_INVALID_ARG;
}

enum status_code can_set_rx_extended_filter(
		struct can_module *const module_inst,
		struct can_extended_message_filter_element *et_filter, uint32_t index)
{
	if (module_inst->hw == CAN0) {
		can0_rx_extended_filter[index].F0.reg = et_filter->F0.reg;
		can0_rx_extended_filter[index].F1.reg = et_filter->F1.reg;
		return STATUS_OK;
	} else if (module_inst->hw == CAN1) {
		can1_rx_extended_filter[index].F0.reg = et_filter->F0.reg;
		can1_rx_extended_filter[index].F1.reg = et_filter->F1.reg;
		return STATUS_OK;
	}
	return STATUS_ERR_INVALID_ARG;
}

enum status_code can_get_rx_buffer_element(
		struct can_module *const module_inst,
		struct can_rx_element_buffer *rx_element, uint32_t index)
{
	if (module_inst->hw == CAN0) {
		memcpy(rx_element, &can0_rx_buffer[index], sizeof(struct can_rx_element_buffer));
		return STATUS_OK;
	} else if (module_inst->hw == CAN1) {
		memcpy(rx_element, &can1_rx_buffer[index], sizeof(struct can_rx_element_buffer));
		return STATUS_OK;
	}
	return STATUS_ERR_INVALID_ARG;
}

enum status_code can_get_rx_fifo_0_element(
		struct can_module *const module_inst,
		struct can_rx_element_fifo_0 *rx_element, uint32_t index)
{
	if (module_inst->hw == CAN0) {
		memcpy(rx_element, &can0_rx_fifo_0[index], sizeof(struct can_rx_element_buffer));
		return STATUS_OK;
	} else if (module_inst->hw == CAN1) {
		memcpy(rx_element, &can1_rx_fifo_0[index], sizeof(struct can_rx_element_buffer));
		return STATUS_OK;
	}
	return STATUS_ERR_INVALID_ARG;
}

enum status_code can_get_rx_fifo_1_element(
		struct can_module *const module_inst,
		struct can_rx_element_fifo_1 *rx_element, uint32_t index)
{
	if (module_inst->hw == CAN0) {
		memcpy(rx_element, &can0_rx_fifo_1[index], sizeof(struct can_rx_element_buffer));
		return STATUS_OK;
	} else if (module_inst->hw == CAN1) {
		memcpy(rx_element, &can1_rx_fifo_1[index], sizeof(struct can_rx_element_buffer));
		return STATUS_OK;
	}
	return STATUS_ERR_INVALID_ARG;
}

enum status_code can_set_tx_buffer_element(
		struct can_module *const module_inst,
		struct can_tx_element *tx_element, uint32_t index)
{
	uint32_t i;
	if (module_inst->hw == CAN0) {
		can0_tx_buffer[index].T0.reg = tx_element->T0.reg;
		can0_tx_buffer[index].T1.reg = tx_element->T1.reg;
		for (i = 0; i < CONF_CAN_ELEMENT_DATA_SIZE; i++) {
			can0_tx_buffer[index].data[i] = tx_element->data[i];
		}
		return STATUS_OK;
	} else if (module_inst->hw == CAN1) {
		can1_tx_buffer[index].T0.reg = tx_element->T0.reg;
		can1_tx_buffer[index].T1.reg = tx_element->T1.reg;
		for (i = 0; i < CONF_CAN_ELEMENT_DATA_SIZE; i++) {
			can1_tx_buffer[index].data[i] = tx_element->data[i];
		}
		return STATUS_OK;
	}
	return STATUS_ERR_INVALID_ARG;
}

enum status_code can_get_tx_event_fifo_element(
		struct can_module *const module_inst,
		struct can_tx_event_element *tx_event_element, uint32_t index)
{
	if (module_inst->hw == CAN0) {
		tx_event_element->E0.reg = can0_tx_event_fifo[index].E0.reg;
		tx_event_element->E1.reg = can0_tx_event_fifo[index].E1.reg;
		return STATUS_OK;
	} else if (module_inst->hw == CAN1) {
		tx_event_element->E0.reg = can1_tx_event_fifo[index].E0.reg;
		tx_event_element->E1.reg = can1_tx_event_fifo[index].E1.reg;
		return STATUS_OK;
	}
	return STATUS_ERR_INVALID_ARG;
}

