/**
 * \file
 *
 * \brief Control Area Network(CAN) functionality implementation.
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
#include <hpl_can_async.h>
#include <hpl_mcan.h>
#include <string.h>

#ifdef CONF_CAN0_ENABLED
COMPILER_ALIGNED(4)
uint8_t can0_rx_fifo[CONF_CAN0_F0DS * CONF_CAN0_RXF0C_F0S];
COMPILER_ALIGNED(4)
uint8_t can0_tx_fifo[CONF_CAN0_TBDS * CONF_CAN0_TXBC_TFQS];
COMPILER_ALIGNED(4)
static struct _can_tx_event_entry can0_tx_event_fifo[CONF_CAN0_TXEFC_EFS];
COMPILER_ALIGNED(4)
static struct _can_standard_message_filter_element can0_rx_std_filter[CONF_CAN0_SIDFC_LSS];
COMPILER_ALIGNED(4)
static struct _can_extended_message_filter_element can0_rx_ext_filter[CONF_CAN0_XIDFC_LSS];

struct _can_context _can0_context = {.rx_fifo       = can0_rx_fifo,
                                     .tx_fifo       = can0_tx_fifo,
                                     .tx_event      = can0_tx_event_fifo,
                                     .rx_std_filter = can0_rx_std_filter,
                                     .rx_ext_filter = can0_rx_ext_filter};

/** Pointer to hpl device */
static struct _can_async_device *_can0_dev = NULL;
#endif /* CONF_CAN0_ENABLED */

#ifdef CONF_CAN1_ENABLED
COMPILER_ALIGNED(4)
uint8_t can1_rx_fifo[CONF_CAN1_F0DS * CONF_CAN1_RXF0C_F0S];
COMPILER_ALIGNED(4)
uint8_t can1_tx_fifo[CONF_CAN1_TBDS * CONF_CAN1_TXBC_TFQS];
COMPILER_ALIGNED(4)
static struct _can_tx_event_entry can1_tx_event_fifo[CONF_CAN1_TXEFC_EFS];
COMPILER_ALIGNED(4)
static struct _can_standard_message_filter_element can1_rx_std_filter[CONF_CAN1_SIDFC_LSS];
COMPILER_ALIGNED(4)
static struct _can_extended_message_filter_element can1_rx_ext_filter[CONF_CAN1_XIDFC_LSS];

struct _can_context _can1_context = {.rx_fifo       = can1_rx_fifo,
                                     .tx_fifo       = can1_tx_fifo,
                                     .tx_event      = can1_tx_event_fifo,
                                     .rx_std_filter = can1_rx_std_filter,
                                     .rx_ext_filter = can1_rx_ext_filter};

/** Pointer to hpl device */
static struct _can_async_device *_can1_dev = NULL;
#endif /* CONF_CAN1_ENABLED */

/**
 * \brief Initialize CAN.
 */
int32_t _can_async_init(struct _can_async_device *const dev, void *const hw)
{
	dev->hw = hw;
	hri_mcan_set_CCCR_INIT_bit(dev->hw);
	while (hri_mcan_get_CCCR_INIT_bit(dev->hw) == 0)
		;
	hri_mcan_set_CCCR_CCE_bit(dev->hw);

#ifdef CONF_CAN0_ENABLED
	if (hw == MCAN0) {
		dev->context = (void *)&_can0_context;
		hri_mcan_set_CCCR_reg(dev->hw, CONF_CAN0_CCCR_REG);
		hri_mcan_write_NBTP_reg(dev->hw, CONF_CAN0_NBTP_REG);
		hri_mcan_write_DBTP_reg(dev->hw, CONF_CAN0_DBTP_REG);
		hri_mcan_write_TDCR_reg(dev->hw, CONF_CAN0_TDCR_REG);
		hri_mcan_write_RXF0C_reg(dev->hw, CONF_CAN0_RXF0C_REG | (((uint32_t)can0_rx_fifo) & 0xFFFF));
		hri_mcan_write_RXESC_reg(dev->hw, CONF_CAN0_RXESC_REG);
		hri_mcan_write_TXESC_reg(dev->hw, CONF_CAN0_TXESC_REG);
		hri_mcan_write_TXBC_reg(dev->hw, CONF_CAN0_TXBC_REG | (((uint32_t)can0_tx_fifo) & 0xFFFF));
		hri_mcan_write_TXEFC_reg(dev->hw, CONF_CAN0_TXEFC_REG | (((uint32_t)can0_tx_event_fifo) & 0xFFFF));
		hri_mcan_write_GFC_reg(dev->hw, CONF_CAN0_GFC_REG);
		hri_mcan_write_SIDFC_reg(dev->hw, CONF_CAN0_SIDFC_REG | (((uint32_t)can0_rx_std_filter) & 0xFFFF));
		hri_mcan_write_XIDFC_reg(dev->hw, CONF_CAN0_XIDFC_REG | (((uint32_t)can0_rx_ext_filter) & 0xFFFF));
		hri_mcan_write_XIDAM_reg(dev->hw, CONF_CAN0_XIDAM_REG);

		_can0_dev = dev;
		NVIC_DisableIRQ(MCAN0_INT0_IRQn);
		NVIC_ClearPendingIRQ(MCAN0_INT0_IRQn);
		NVIC_EnableIRQ(MCAN0_INT0_IRQn);
		hri_mcan_write_ILE_reg(dev->hw, MCAN_ILE_EINT0);
	}
#endif

#ifdef CONF_CAN1_ENABLED
	if (hw == MCAN1) {
		dev->context = (void *)&_can1_context;
		hri_mcan_set_CCCR_reg(dev->hw, CONF_CAN1_CCCR_REG);
		hri_mcan_write_NBTP_reg(dev->hw, CONF_CAN1_NBTP_REG);
		hri_mcan_write_DBTP_reg(dev->hw, CONF_CAN1_DBTP_REG);
		hri_mcan_write_TDCR_reg(dev->hw, CONF_CAN1_TDCR_REG);
		hri_mcan_write_RXF0C_reg(dev->hw, CONF_CAN1_RXF0C_REG | (((uint32_t)can1_rx_fifo) & 0xFFFF));
		hri_mcan_write_RXESC_reg(dev->hw, CONF_CAN1_RXESC_REG);
		hri_mcan_write_TXESC_reg(dev->hw, CONF_CAN1_TXESC_REG);
		hri_mcan_write_TXBC_reg(dev->hw, CONF_CAN1_TXBC_REG | (((uint32_t)can1_tx_fifo) & 0xFFFF));
		hri_mcan_write_TXEFC_reg(dev->hw, CONF_CAN1_TXEFC_REG | (((uint32_t)can1_tx_event_fifo) & 0xFFFF));
		hri_mcan_write_GFC_reg(dev->hw, CONF_CAN1_GFC_REG);
		hri_mcan_write_SIDFC_reg(dev->hw, CONF_CAN1_SIDFC_REG | (((uint32_t)can1_rx_std_filter) & 0xFFFF));
		hri_mcan_write_XIDFC_reg(dev->hw, CONF_CAN1_XIDFC_REG | (((uint32_t)can1_rx_ext_filter) & 0xFFFF));
		hri_mcan_write_XIDAM_reg(dev->hw, CONF_CAN1_XIDAM_REG);

		_can1_dev = dev;
		NVIC_DisableIRQ(MCAN1_INT0_IRQn);
		NVIC_ClearPendingIRQ(MCAN1_INT0_IRQn);
		NVIC_EnableIRQ(MCAN1_INT0_IRQn);
		hri_mcan_write_ILE_reg(dev->hw, MCAN_ILE_EINT0);
	}
#endif

	/* Disable CCE to prevent Configuration Change */
	hri_mcan_clear_CCCR_CCE_bit(dev->hw);
	hri_mcan_clear_CCCR_INIT_bit(dev->hw);
	while (hri_mcan_get_CCCR_INIT_bit(dev->hw)) {
	};

	return ERR_NONE;
}

/**
 * \brief De-initialize CAN.
 */
int32_t _can_async_deinit(struct _can_async_device *const dev)
{
	hri_mcan_set_CCCR_INIT_bit(dev->hw);
	dev->hw = NULL;
	return ERR_NONE;
}

/**
 * \brief Enable CAN
 */
int32_t _can_async_enable(struct _can_async_device *const dev)
{
	hri_mcan_clear_CCCR_INIT_bit(dev->hw);
	return ERR_NONE;
}

/**
 * \brief Disable CAN
 */
int32_t _can_async_disable(struct _can_async_device *const dev)
{
	hri_mcan_set_CCCR_INIT_bit(dev->hw);
	return ERR_NONE;
}

/**
 * \brief Read a CAN message
 */
int32_t _can_async_read(struct _can_async_device *const dev, struct can_message *msg)
{
	struct _can_rx_fifo_entry *f = NULL;
	hri_mcan_rxf0s_reg_t       get_index;

	if (!hri_mcan_read_RXF0S_F0FL_bf(dev->hw)) {
		return ERR_NOT_FOUND;
	}

	get_index = hri_mcan_read_RXF0S_F0GI_bf(dev->hw);

#ifdef CONF_CAN0_ENABLED
	if (dev->hw == MCAN0) {
		f = (struct _can_rx_fifo_entry *)(can0_rx_fifo + get_index * CONF_CAN0_F0DS);
	}
#endif
#ifdef CONF_CAN1_ENABLED
	if (dev->hw == MCAN1) {
		f = (struct _can_rx_fifo_entry *)(can1_rx_fifo + get_index * CONF_CAN1_F0DS);
	}
#endif

	if (f == NULL) {
		return ERR_NO_RESOURCE;
	}

	if (f->R0.bit.XTD == 1) {
		msg->fmt = CAN_FMT_EXTID;
		msg->id  = f->R0.bit.ID;
	} else {
		msg->fmt = CAN_FMT_STDID;
		/* A standard identifier is stored into ID[28:18] */
		msg->id = f->R0.bit.ID >> 18;
	}

	if (f->R0.bit.RTR == 1) {
		msg->type = CAN_TYPE_REMOTE;
	}

	const uint8_t dlc2len[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64};
	msg->len                = dlc2len[f->R1.bit.DLC];

	memcpy(msg->data, f->data, msg->len);

	hri_mcan_write_RXF0A_F0AI_bf(dev->hw, get_index);

	return ERR_NONE;
}

/**
 * \brief Write a CAN message
 */
int32_t _can_async_write(struct _can_async_device *const dev, struct can_message *msg)
{
	struct _can_tx_fifo_entry *f = NULL;
	hri_mcan_txfqs_reg_t       put_index;

	if (hri_mcan_get_TXFQS_TFQF_bit(dev->hw)) {
		return ERR_NO_RESOURCE;
	}

	put_index = hri_mcan_read_TXFQS_TFQPI_bf(dev->hw);

#ifdef CONF_CAN0_ENABLED
	if (dev->hw == MCAN0) {
		f = (struct _can_tx_fifo_entry *)(can0_tx_fifo + put_index * CONF_CAN0_TBDS);
	}
#endif
#ifdef CONF_CAN1_ENABLED
	if (dev->hw == MCAN1) {
		f = (struct _can_tx_fifo_entry *)(can1_tx_fifo + put_index * CONF_CAN1_TBDS);
	}
#endif
	if (f == NULL) {
		return ERR_NO_RESOURCE;
	}

	if (msg->fmt == CAN_FMT_EXTID) {
		f->T0.val     = msg->id;
		f->T0.bit.XTD = 1;
	} else {
		/* A standard identifier is stored into ID[28:18] */
		f->T0.val = msg->id << 18;
	}

	if (msg->len <= 8) {
		f->T1.bit.DLC = msg->len;
	} else if (msg->len <= 12) {
		f->T1.bit.DLC = 0x9;
	} else if (msg->len <= 16) {
		f->T1.bit.DLC = 0xA;
	} else if (msg->len <= 20) {
		f->T1.bit.DLC = 0xB;
	} else if (msg->len <= 24) {
		f->T1.bit.DLC = 0xC;
	} else if (msg->len <= 32) {
		f->T1.bit.DLC = 0xD;
	} else if (msg->len <= 48) {
		f->T1.bit.DLC = 0xE;
	} else if (msg->len <= 64) {
		f->T1.bit.DLC = 0xF;
	}

	f->T1.bit.FDF = hri_mcan_get_CCCR_FDOE_bit(dev->hw);
	f->T1.bit.BRS = hri_mcan_get_CCCR_BRSE_bit(dev->hw);

	memcpy(f->data, msg->data, msg->len);

	hri_mcan_write_TXBAR_reg(dev->hw, 1 << hri_mcan_read_TXFQS_TFQPI_bf(dev->hw));
	return ERR_NONE;
}

/**
 * \brief Set CAN Interrupt State
 */
void _can_async_set_irq_state(struct _can_async_device *const dev, enum can_async_callback_type type, bool state)
{
	uint32_t ie;

	if (type == CAN_ASYNC_RX_CB) {
		hri_mcan_write_IE_RF0NE_bit(dev->hw, state);
	} else if (type == CAN_ASYNC_TX_CB) {
		hri_mcan_write_IE_TCE_bit(dev->hw, state);
		hri_mcan_write_TXBTIE_reg(dev->hw, MCAN_TXBTIE_MASK);
	} else if (type == CAN_ASYNC_IRQ_CB) {
		ie = hri_mcan_get_IE_reg(dev->hw, MCAN_IE_RF0NE | MCAN_IE_TCE);
		hri_mcan_write_IE_reg(dev->hw, ie | CONF_CAN0_IE_REG);
	}

	return;
}

/**
 * \brief Return number of read errors
 */
uint8_t _can_async_get_rxerr(struct _can_async_device *const dev)
{
	return hri_mcan_read_ECR_REC_bf(dev->hw);
}

/**
 * \brief Return number of write errors
 */
uint8_t _can_async_get_txerr(struct _can_async_device *const dev)
{
	return hri_mcan_read_ECR_TEC_bf(dev->hw);
}

/**
 * \brief Set CAN to the specified mode
 */
int32_t _can_async_set_mode(struct _can_async_device *const dev, enum can_mode mode)
{
	hri_mcan_set_CCCR_INIT_bit(dev->hw);
	while (hri_mcan_get_CCCR_INIT_bit(dev->hw) == 0)
		;
	hri_mcan_set_CCCR_CCE_bit(dev->hw);

	if (mode == CAN_MODE_MONITORING) {
		hri_mcan_set_CCCR_MON_bit(dev->hw);
	} else {
		hri_mcan_clear_CCCR_MON_bit(dev->hw);
	}

	/* Disable CCE to prevent Configuration Change */
	hri_mcan_clear_CCCR_CCE_bit(dev->hw);
	hri_mcan_clear_CCCR_INIT_bit(dev->hw);
	while (hri_mcan_get_CCCR_INIT_bit(dev->hw))
		;

	return ERR_NONE;
}

/**
 * \brief Set CAN to the specified mode
 */
int32_t _can_async_set_filter(struct _can_async_device *const dev, uint8_t index, enum can_format fmt,
                              struct can_filter *filter)
{
	struct _can_standard_message_filter_element *sf;
	struct _can_extended_message_filter_element *ef;

	sf = &((struct _can_context *)dev->context)->rx_std_filter[index];
	ef = &((struct _can_context *)dev->context)->rx_ext_filter[index];

	if (fmt == CAN_FMT_STDID) {
		if (filter == NULL) {
			sf->S0.val = 0;
			return ERR_NONE;
		}
		sf->S0.val       = filter->mask;
		sf->S0.bit.SFID1 = filter->id;
		sf->S0.bit.SFT   = _CAN_SFT_CLASSIC;
		sf->S0.bit.SFEC  = _CAN_SFEC_STF0M;
	} else if (fmt == CAN_FMT_EXTID) {
		if (filter == NULL) {
			ef->F0.val = 0;
			return ERR_NONE;
		}
		ef->F0.val      = filter->id;
		ef->F0.bit.EFEC = _CAN_EFEC_STF0M;
		ef->F1.val      = filter->mask;
		ef->F1.bit.EFT  = _CAN_EFT_CLASSIC;
	}

	return ERR_NONE;
}

/*
 * \brief CAN interrupt handler
 *
 * \param[in] p The pointer to interrupt parameter
 */
static void _can_irq_handler(struct _can_async_device *dev)
{
	uint32_t ir;
	ir = hri_mcan_read_IR_reg(dev->hw);

	if (ir & MCAN_IR_RF0N) {
		dev->cb.rx_done(dev);
	}

	if (ir & MCAN_IR_TC) {
		dev->cb.tx_done(dev);
	}

	if (ir & MCAN_IR_BO) {
		dev->cb.irq_handler(dev, CAN_IRQ_BO);
	}

	if (ir & MCAN_IR_EW) {
		dev->cb.irq_handler(dev, CAN_IRQ_EW);
	}

	if (ir & MCAN_IR_EP) {
		dev->cb.irq_handler(dev, hri_mcan_get_PSR_EP_bit(dev->hw) ? CAN_IRQ_EP : CAN_IRQ_EA);
	}

	if (ir & MCAN_IR_RF0L) {
		dev->cb.irq_handler(dev, CAN_IRQ_DO);
	}

	hri_mcan_write_IR_reg(dev->hw, ir);
}

/**
 * \internal CAN interrupt handler
 */
void MCAN1_INT0_Handler(void)
{
	_can_irq_handler(_can1_dev);
}
