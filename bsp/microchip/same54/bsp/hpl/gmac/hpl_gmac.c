/**
 * \file
 *
 * \brief MAC functionality declaration.
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

#include <string.h>
#include <utils_assert.h>
#include <hpl_mac_async.h>
#include <hpl_gmac_config.h>

/**
 * @brief Transmit buffer descriptor
 **/
struct _mac_txbuf_descriptor {
	uint32_t address;
	union gmac_tx_status {
		uint32_t val;
		struct _gmac_tx_status_bm {
			uint32_t len : 14,                   /**< Length of buffer */
			    reserved : 1, last_buf : 1,      /**< Last buffer (in the current frame) */
			    no_crc : 1,                      /**< No CRC */
			    reserved1 : 3, checksum_err : 3, /**< Transmit checksum generation offload error */
			    reserved2 : 3, lco : 1,          /**< Late collision, transmit error detected */
			    exhausted : 1,                   /**< Buffer exhausted in mid frame */
			    reserved3 : 1, error : 1,        /**< Retry limit exceeded, error detected */
			    wrap : 1,                        /**< Marks last descriptor in TD list */
			    used : 1;                        /**< User clear, GMAC sets this to 1 once a frame
			                                          has been successfully transmitted */
		} bm;
	} status;
};

/**
 * @brief Receive buffer descriptor
 **/
struct _mac_rxbuf_descriptor {
	union _gmac_rx_addr {
		uint32_t val;
		struct rx_addr_bm {
			uint32_t ownership : 1, /**< clear before buffer can be used again */
			    wrap : 1,           /**< Marks last entry in array */
			    addr : 30;          /**< Address in number of DW */
		} bm;
	} address;
	union gmac_rx_status {
		uint32_t val;
		struct _gmac_rx_status_bm {
			uint32_t len : 13,                    /**< Length of frame including FCS */
			    fcs : 1,                          /**< Frame has bad FCS */
			    sof : 1,                          /**< Start of frame */
			    eof : 1,                          /**< End of frame */
			    cfi : 1,                          /**< Concatenation Format Indicator */
			    vlan_priority : 3,                /**< VLAN priority (if VLAN detected) */
			    priority_detected : 1,            /**< Priority tag detected */
			    vlan_detected : 1,                /**< VLAN tag detected */
			    type_id_match : 2,                /**< Type ID match */
			    checksumoffload : 1,              /**< Checksum offload specific function */
			    addrmatch : 2,                    /**< Address register match */
			    ext_addr_match : 1,               /**< External address match found */
			    reserved : 1, uni_hash_match : 1, /**< Unicast hash match */
			    multi_hash_match : 1,             /**< Multicast hash match */
			    boardcast_detect : 1;             /**< Global broadcast address detected */
		} bm;
	} status;
};

/* Transmit and Receive buffer descriptor array */
COMPILER_ALIGNED(8) static struct _mac_txbuf_descriptor _txbuf_descrs[CONF_GMAC_TXDESCR_NUM];
COMPILER_ALIGNED(8) static struct _mac_rxbuf_descriptor _rxbuf_descrs[CONF_GMAC_RXDESCR_NUM];

/* Transmit buffer data array */
COMPILER_ALIGNED(32)
static uint8_t _txbuf[CONF_GMAC_TXDESCR_NUM][CONF_GMAC_TXBUF_SIZE];
COMPILER_ALIGNED(32)
static uint8_t _rxbuf[CONF_GMAC_RXDESCR_NUM][CONF_GMAC_RXBUF_SIZE];

COMPILER_PACK_RESET()

/*!< Pointer to hpl device */
static struct _mac_async_device *_gmac_dev = NULL;

/* Transmit and receive Buffer index */
static volatile uint32_t _txbuf_index;
static volatile uint32_t _last_txbuf_index;
static volatile uint32_t _rxbuf_index;

/**
 * \internal Initialize the Transmit and receive buffer descriptor array
 *
 * \param[in] dev Pointer to the HPL MAC descriptor
 */
static void _mac_init_bufdescr(struct _mac_async_device *const dev)
{
	uint32_t i;

	/* TX buffer descriptor */
	for (i = 0; i < CONF_GMAC_TXDESCR_NUM; i++) {
		_txbuf_descrs[i].address        = (uint32_t)_txbuf[i];
		_txbuf_descrs[i].status.val     = 0;
		_txbuf_descrs[i].status.bm.used = 1;
	}

	_txbuf_descrs[CONF_GMAC_TXDESCR_NUM - 1].status.bm.wrap = 1;
	_txbuf_index                                            = 0;
	_last_txbuf_index                                       = 0;

	/* RX buffer descriptor */
	for (i = 0; i < CONF_GMAC_RXDESCR_NUM; i++) {
		_rxbuf_descrs[i].address.val = (uint32_t)_rxbuf[i];
		_rxbuf_descrs[i].status.val  = 0;
	}

	_rxbuf_descrs[CONF_GMAC_RXDESCR_NUM - 1].address.bm.wrap = 1;
	_rxbuf_index                                             = 0;

	hri_gmac_write_TBQB_reg(dev->hw, (uint32_t)_txbuf_descrs);
	hri_gmac_write_RBQB_reg(dev->hw, (uint32_t)_rxbuf_descrs);
}

/*
 * \internal GMAC interrupt handler
 */
void GMAC_Handler(void)
{
	volatile uint32_t tsr;
	volatile uint32_t rsr;

	tsr = hri_gmac_read_TSR_reg(_gmac_dev->hw);
	rsr = hri_gmac_read_RSR_reg(_gmac_dev->hw);
	/* Must be Clear ISR (Clear on read) */
	hri_gmac_read_ISR_reg(_gmac_dev->hw);

	/* Frame transmited */
	if (tsr & GMAC_TSR_TXCOMP) {
		hri_gmac_write_TSR_reg(_gmac_dev->hw, tsr);
		if ((_txbuf_descrs[_txbuf_index].status.bm.used) && (_gmac_dev->cb.transmited != NULL)) {
			_gmac_dev->cb.transmited(_gmac_dev);
		}
	}

	/* Frame received */
	if (rsr & GMAC_RSR_REC) {
		if (_gmac_dev->cb.received != NULL) {
			_gmac_dev->cb.received(_gmac_dev);
		}
	}
	hri_gmac_write_RSR_reg(_gmac_dev->hw, rsr);
}

int32_t _mac_async_init(struct _mac_async_device *const dev, void *const hw)
{
	dev->hw = hw;
	hri_gmac_write_NCR_reg(dev->hw,
	                       (CONF_GMAC_NCR_LBL ? GMAC_NCR_LBL : 0) | (CONF_GMAC_NCR_MPE ? GMAC_NCR_MPE : 0)
	                           | (CONF_GMAC_NCR_WESTAT ? GMAC_NCR_WESTAT : 0) | (CONF_GMAC_NCR_BP ? GMAC_NCR_BP : 0)
	                           | (CONF_GMAC_NCR_ENPBPR ? GMAC_NCR_ENPBPR : 0)
	                           | (CONF_GMAC_NCR_TXPBPF ? GMAC_NCR_TXPBPF : 0));
	hri_gmac_write_NCFGR_reg(
	    dev->hw,
	    (CONF_GMAC_NCFGR_SPD ? GMAC_NCFGR_SPD : 0) | (CONF_GMAC_NCFGR_FD ? GMAC_NCFGR_FD : 0)
	        | (CONF_GMAC_NCFGR_DNVLAN ? GMAC_NCFGR_DNVLAN : 0) | (CONF_GMAC_NCFGR_JFRAME ? GMAC_NCFGR_JFRAME : 0)
	        | (CONF_GMAC_NCFGR_CAF ? GMAC_NCFGR_CAF : 0) | (CONF_GMAC_NCFGR_NBC ? GMAC_NCFGR_NBC : 0)
	        | (CONF_GMAC_NCFGR_MTIHEN ? GMAC_NCFGR_MTIHEN : 0) | (CONF_GMAC_NCFGR_UNIHEN ? GMAC_NCFGR_UNIHEN : 0)
	        | (CONF_GMAC_NCFGR_MAXFS ? GMAC_NCFGR_MAXFS : 0) | (CONF_GMAC_NCFGR_RTY ? GMAC_NCFGR_RTY : 0)
	        | (CONF_GMAC_NCFGR_PEN ? GMAC_NCFGR_PEN : 0) | GMAC_NCFGR_RXBUFO(CONF_GMAC_NCFGR_RXBUFO)
	        | (CONF_GMAC_NCFGR_LFERD ? GMAC_NCFGR_LFERD : 0) | (CONF_GMAC_NCFGR_RFCS ? GMAC_NCFGR_RFCS : 0)
	        | GMAC_NCFGR_CLK(CONF_GMAC_NCFGR_CLK) | (CONF_GMAC_NCFGR_DCPF ? GMAC_NCFGR_DCPF : 0)
	        | (CONF_GMAC_NCFGR_RXCOEN ? GMAC_NCFGR_RXCOEN : 0) | (CONF_GMAC_NCFGR_EFRHD ? GMAC_NCFGR_EFRHD : 0)
	        | (CONF_GMAC_NCFGR_IRXFCS ? GMAC_NCFGR_IRXFCS : 0) | (CONF_GMAC_NCFGR_IPGSEN ? GMAC_NCFGR_IPGSEN : 0)
	        | (CONF_GMAC_NCFGR_RXBP ? GMAC_NCFGR_RXBP : 0) | (CONF_GMAC_NCFGR_IRXER ? GMAC_NCFGR_IRXER : 0));
	hri_gmac_write_UR_reg(dev->hw, (CONF_GMAC_UR_MII ? GMAC_UR_MII : 0));
	hri_gmac_write_DCFGR_reg(
	    dev->hw,
	    GMAC_DCFGR_FBLDO(CONF_GMAC_DCFGR_FBLDO) | (CONF_GMAC_DCFGR_ESMA ? GMAC_DCFGR_ESMA : 0)
	        | (CONF_GMAC_DCFGR_ESPA ? GMAC_DCFGR_ESPA : 0) | GMAC_DCFGR_RXBMS(CONF_GMAC_DCFGR_RXBMS)
	        | (CONF_GMAC_DCFGR_TXPBMS ? GMAC_DCFGR_TXPBMS : 0) | (CONF_GMAC_DCFGR_TXCOEN ? GMAC_DCFGR_TXCOEN : 0)
	        | GMAC_DCFGR_DRBS(CONF_GMAC_DCFGR_DRBS) | (CONF_GMAC_DCFGR_DDRP ? GMAC_DCFGR_DDRP : 0));
	hri_gmac_write_WOL_reg(dev->hw, 0);
	hri_gmac_write_IPGS_reg(dev->hw, GMAC_IPGS_FL((CONF_GMAC_IPGS_FL_MUL << 8) | CONF_GMAC_IPGS_FL_DIV));
	_mac_init_bufdescr(dev);

	_gmac_dev = dev;
	NVIC_DisableIRQ(GMAC_IRQn);
	NVIC_ClearPendingIRQ(GMAC_IRQn);
	NVIC_EnableIRQ(GMAC_IRQn);

	return ERR_NONE;
}

int32_t _mac_async_deinit(struct _mac_async_device *const dev)
{
	/* Disable all GMAC Interrupt */
	hri_gmac_clear_IMR_reg(dev->hw, 0xFFFFFFFF);
	/* Disable transmit/receive */
	hri_gmac_write_NCR_reg(dev->hw, 0x0);
	dev->hw = NULL;
	/* Disable Interrupt */
	NVIC_DisableIRQ(GMAC_IRQn);

	return ERR_NONE;
}

int32_t _mac_async_enable(struct _mac_async_device *const dev)
{
	hri_gmac_set_NCR_reg(dev->hw, GMAC_NCR_RXEN | GMAC_NCR_TXEN);
	return ERR_NONE;
}

int32_t _mac_async_disable(struct _mac_async_device *const dev)
{
	hri_gmac_clear_NCR_reg(dev->hw, GMAC_NCR_RXEN | GMAC_NCR_TXEN);
	return ERR_NONE;
}

int32_t _mac_async_write(struct _mac_async_device *const dev, uint8_t *buf, uint32_t len)
{
	uint32_t pos;
	uint32_t blen;
	uint32_t i;

	if (_txbuf_descrs[_last_txbuf_index].status.bm.used && !_txbuf_descrs[_last_txbuf_index].status.bm.last_buf) {
		/* Set used flag from first descriptor to last descriptor,
		 * as DMA olny set the first used flag */
		for (i = 1; i < CONF_GMAC_TXDESCR_NUM; i++) {
			pos = _last_txbuf_index + i;
			if (pos >= CONF_GMAC_TXDESCR_NUM) {
				pos -= CONF_GMAC_TXDESCR_NUM;
			}
			_txbuf_descrs[pos].status.bm.used = 1;

			if (_txbuf_descrs[pos].status.bm.last_buf) {
				break;
			}
		}
	}

	if (!_txbuf_descrs[_txbuf_index].status.bm.used) {
		return ERR_NO_RESOURCE;
	}

	/* Check if have enough buffers, the first buffer already checked */
	if (len > CONF_GMAC_TXBUF_SIZE) {
		for (i = 1; i < CONF_GMAC_TXDESCR_NUM; i++) {
			pos = _txbuf_index + i;
			if (pos >= CONF_GMAC_TXDESCR_NUM) {
				pos -= CONF_GMAC_TXDESCR_NUM;
			}

			if (!_txbuf_descrs[pos].status.bm.used) {
				return ERR_NO_RESOURCE;
			}

			if ((len - (CONF_GMAC_TXBUF_SIZE * i)) < CONF_GMAC_TXBUF_SIZE) {
				break;
			}
		}
	}
	_last_txbuf_index = _txbuf_index;

	/* Write data to transmit buffer */
	for (i = 0; i < CONF_GMAC_TXDESCR_NUM; i++) {
		blen = min(len, CONF_GMAC_TXBUF_SIZE);
		memcpy(_txbuf[_txbuf_index], buf + (i * CONF_GMAC_TXBUF_SIZE), blen);
		len -= blen;

		if (len > 0) {
			/* Here the Used flag be set to zero */
			_txbuf_descrs[_txbuf_index].status.val = blen;
		} else {
			_txbuf_descrs[_txbuf_index].status.val         = blen;
			_txbuf_descrs[_txbuf_index].status.bm.last_buf = 1;
		}
		_txbuf_index++;
		if (_txbuf_index == CONF_GMAC_TXDESCR_NUM) {
			_txbuf_index                                            = 0;
			_txbuf_descrs[CONF_GMAC_TXDESCR_NUM - 1].status.bm.wrap = 1;
		}
		if (len == 0) {
			break;
		}
	}

	/* Data synchronization barrier */
	__DSB();

	/* Active Transmit */
	hri_gmac_set_NCR_reg(dev->hw, GMAC_NCR_TSTART);

	return ERR_NONE;
}

uint32_t _mac_async_read(struct _mac_async_device *const dev, uint8_t *buf, uint32_t len)
{
	uint32_t i;
	uint32_t j;
	uint32_t pos;
	uint32_t n;
	uint32_t sof       = 0xFFFFFFFF; /* Start of Frame index */
	uint32_t eof       = 0xFFFFFFFF; /* End of Frame index */
	uint32_t total_len = 0;          /* Total length of received package */

	(void)dev;
	for (i = 0; i < CONF_GMAC_RXDESCR_NUM; i++) {
		pos = _rxbuf_index + i;

		if (pos >= CONF_GMAC_RXDESCR_NUM) {
			pos -= CONF_GMAC_RXDESCR_NUM;
		}

		/* No more data for Ethernet package */
		if (!_rxbuf_descrs[pos].address.bm.ownership) {
			break;
		}

		if (_rxbuf_descrs[pos].status.bm.sof) {
			sof = i;
		}

		if ((_rxbuf_descrs[pos].status.bm.eof) && (sof != 0xFFFFFFFF)) {
			/* eof now indicate the number of bufs the frame used */
			eof = i;
			n   = _rxbuf_descrs[pos].status.bm.len;
			len = min(n, len);
			/* Break process since the last data has been found */
			break;
		}
	}

	if (eof != 0xFFFFFFFF) {
		j = eof + 1;
	} else if (sof != 0xFFFFFFFF) {
		j = sof;
	} else {
		j = i;
	}

	/* Copy data to user buffer */
	for (i = 0; i < j; i++) {
		if (eof != 0xFFFFFFFF && i >= sof && i <= eof && len > 0) {
			n = min(len, CONF_GMAC_RXBUF_SIZE);
			memcpy(buf, _rxbuf[_rxbuf_index], n);
			buf += n;
			total_len += n;
			len -= n;
		}

		_rxbuf_descrs[_rxbuf_index].address.bm.ownership = 0;
		_rxbuf_index++;

		if (_rxbuf_index == CONF_GMAC_RXDESCR_NUM) {
			_rxbuf_index = 0;
		}
	}

	return total_len;
}

uint32_t _mac_async_read_len(struct _mac_async_device *const dev)
{
	uint32_t i;
	uint32_t pos;
	bool     sof       = false; /* Start of Frame */
	uint32_t total_len = 0;     /* Total length of received package */

	(void)dev;

	for (i = 0; i < CONF_GMAC_RXDESCR_NUM; i++) {
		pos = _rxbuf_index + i;

		if (pos >= CONF_GMAC_RXDESCR_NUM) {
			pos -= CONF_GMAC_RXDESCR_NUM;
		}

		/* No more data for Ethernet package */
		if (!(_rxbuf_descrs[pos].address.bm.ownership)) {
			break;
		}

		if (_rxbuf_descrs[pos].status.bm.sof) {
			sof = true;
		}
		if (sof == true) {
			total_len += _rxbuf_descrs[pos].status.bm.len;
		}

		if (_rxbuf_descrs[pos].status.bm.eof) {
			/* Break process since the last data has been found */
			break;
		}
	}

	return total_len;
}

void _mac_async_enable_irq(struct _mac_async_device *const dev)
{
	(void)dev;
	NVIC_EnableIRQ(GMAC_IRQn);
}

void _mac_async_disable_irq(struct _mac_async_device *const dev)
{
	(void)dev;
	NVIC_DisableIRQ(GMAC_IRQn);
}

int32_t _mac_async_register_callback(struct _mac_async_device *const dev, const enum mac_async_cb_type type,
                                     const FUNC_PTR func)
{
	switch (type) {
	case MAC_ASYNC_TRANSMIT_CB:
		dev->cb.transmited = (_mac_async_cb_t)func;
		if (func) {
			hri_gmac_set_IMR_TCOMP_bit(dev->hw);
		} else {
			hri_gmac_clear_IMR_TCOMP_bit(dev->hw);
		}
		break;
	case MAC_ASYNC_RECEIVE_CB:
		dev->cb.received = (_mac_async_cb_t)func;
		if (func) {
			hri_gmac_set_IMR_RCOMP_bit(dev->hw);
		} else {
			hri_gmac_set_IMR_RCOMP_bit(dev->hw);
		}
		break;
	default:
		return ERR_INVALID_ARG;
	}
	return ERR_NONE;
}

int32_t _mac_async_set_filter(struct _mac_async_device *const dev, uint8_t index, struct mac_async_filter *filter)
{
	ASSERT(index < 4);

	hri_gmac_write_SAB_reg(dev->hw, index, *((uint32_t *)(filter->mac)));
	hri_gmac_write_SAT_reg(dev->hw, index, *((uint16_t *)(filter->mac + 4)));

	hri_gmac_write_TIDM_reg(dev->hw, index, GMAC_TIDM_TID(*((uint16_t *)(filter->tid)) | filter->tid_enable << 31));
	return ERR_NONE;
}

int32_t _mac_async_set_filter_ex(struct _mac_async_device *const dev, uint8_t mac[6])
{
	uint8_t j;
	uint8_t m;
	uint8_t n;
	uint8_t k = 0;

	/* Apply the hash function */
	for (j = 0; j < 48; j += 6) {
		/* Calculate the shift count */
		n = j / 8;
		m = j % 8;

		/* Update hash value */
		if (!m) {
			k ^= mac[n];
		} else {
			k ^= (mac[n] >> m) | (mac[n + 1] << (8 - m));
		}
	}

	/* The hash value is reduced to a 6-bit index */
	k &= 0x3F;

	if (k < 32) {
		hri_gmac_set_HRB_reg(dev->hw, 1 << k);
	} else {
		hri_gmac_set_HRT_reg(dev->hw, 1 << (k % 32));
	}

	return ERR_NONE;
}

int32_t _mac_async_write_phy_reg(struct _mac_async_device *const dev, uint16_t addr, uint16_t reg, uint16_t data)
{
	hri_gmac_set_NCR_reg(dev->hw, GMAC_NCR_MPE);
	hri_gmac_write_MAN_reg(dev->hw,
	                       GMAC_MAN_OP(1) |            /* 0x01 write operation */
	                           CONF_GMAC_CLTTO << 30 | /* Clause 22/45 operation */
	                           GMAC_MAN_WTN(2) |       /* Must be written to 0x2 */
	                           GMAC_MAN_PHYA(addr) | GMAC_MAN_REGA(reg) | GMAC_MAN_DATA(data));
	/* Wait for the write operation complete */
	while (!hri_gmac_get_NSR_IDLE_bit(dev->hw)) {
	}

	hri_gmac_clear_NCR_reg(dev->hw, GMAC_NCR_MPE);
	return ERR_NONE;
}

int32_t _mac_async_read_phy_reg(struct _mac_async_device *const dev, uint16_t addr, uint16_t reg, uint16_t *data)
{
	hri_gmac_set_NCR_reg(dev->hw, GMAC_NCR_MPE);
	hri_gmac_write_MAN_reg(dev->hw,
	                       GMAC_MAN_OP(2) |            /* 0x02 read operation */
	                           CONF_GMAC_CLTTO << 30 | /* Clause 22/45 operation */
	                           GMAC_MAN_WTN(0x2) |     /* Must be written to 0x2 */
	                           GMAC_MAN_PHYA(addr) | GMAC_MAN_REGA(reg));

	/* Wait for the read operation complete */
	while (!hri_gmac_get_NSR_IDLE_bit(dev->hw)) {
	}

	*data = GMAC_MAN_DATA(hri_gmac_read_MAN_reg(dev->hw));
	hri_gmac_clear_NCR_reg(dev->hw, GMAC_NCR_MPE);

	return ERR_NONE;
}
