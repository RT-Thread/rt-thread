/**
 * \file
 *
 * \brief SAM Two-Wire Interface
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

#include <hpl_i2c_m_sync.h>
#include <hpl_twihs_config.h>
#include <utils.h>
#include <utils_assert.h>

/**
 * \internal Set baudrate for TWIHS
 *
 * \param[in] hw       TWIHS Base Address
 * \param[in] clk      TWIHS peripheral clock rate in HZ
 * \param[in] baudrate TWIHS I2C baudrate in HZ
 */
static int32_t _twihs_set_baudrate(void *const hw, uint32_t clk, uint32_t baudrate);

/**
 * \internal Retrieve I2C Master Sync configuration instance
 *
 * \param[in] hw The pointer of TWIHS hardware instance
 *
 * \return The I2C Master Sync configuration instance
 */
static const struct _i2cm_sync_cfg *_get_i2cm_sync_cfg(void *hw);

/**
 * \internal I2C Master Sync read operation
 *
 * \param[in] dev The pointer of I2C Master instance
 * \param[in] msg The pointer of I2C message struct
 *
 * \return The status of the operation
 * \retval ERR_NONE Operation sucessfully
 */
static inline int32_t _i2c_m_sync_read(struct _i2c_m_sync_device *const dev, struct _i2c_m_msg *msg);

/**
 * \internal I2C Master Sync write operation
 *
 * \param[in] dev The pointer of I2C Master instance
 * \param[in] msg The pointer of I2C message struct
 *
 * \return The status of the operation
 * \retval ERR_NONE Operation sucessfully
 */
static inline int32_t _i2c_m_sync_write(struct _i2c_m_sync_device *const dev, struct _i2c_m_msg *msg);

/**
 * \brief TWIHS I2C Master Sync configuration Type
 */
struct _i2cm_sync_cfg {
	void *                hw; /*!< instance of TWIHS */
	hri_twihs_cr_reg_t    ctrl;
	hri_twihs_smbtr_reg_t smbtr;
	hri_twihs_filtr_reg_t filtr;
	hri_twihs_cwgr_reg_t  cwgr;
	uint32_t              clkrate;
};

/**
 * \brief Array of I2C Master Sync configurations
 */
static const struct _i2cm_sync_cfg _i2cm_sync_cfgs[1] = {
    {(void *)TWIHS0,
     CONF_TWIHS0_CR_REG,
     CONF_TWIHS0_SMBTR_REG,
     CONF_TWIHS0_FILTR_REG,
     CONF_TWIHS0_CWGR_REG,
     CONF_TWIHS0_FREQUENCY / 1000},
};

/**
 * \berif Retrieve I2C Master Sync configuration instance
 */
static const struct _i2cm_sync_cfg *_get_i2cm_sync_cfg(void *hw)
{
	uint8_t i;

	for (i = 0; i < ARRAY_SIZE(_i2cm_sync_cfgs); i++) {
		if (_i2cm_sync_cfgs[i].hw == hw) {
			return &(_i2cm_sync_cfgs[i]);
		}
	}
	return NULL;
}

int32_t _i2c_m_sync_init(struct _i2c_m_sync_device *const dev, void *const hw)
{
	ASSERT(dev && hw);

	const struct _i2cm_sync_cfg *cfg;

	dev->hw = hw;
	cfg     = _get_i2cm_sync_cfg(dev->hw);

	// hri_twihs_write_CR_reg(hw, TWIHS_CR_SWRST);
	// hri_twihs_read_RHR_reg(hw);
	hri_twihs_write_CR_reg(dev->hw, cfg->ctrl);
	hri_twihs_write_SMBTR_reg(dev->hw, cfg->smbtr);
	hri_twihs_write_FILTR_reg(dev->hw, cfg->filtr);
	hri_twihs_write_CWGR_reg(dev->hw, cfg->cwgr);

	return ERR_NONE;
}

int32_t _i2c_m_sync_deinit(struct _i2c_m_sync_device *const dev)
{
	ASSERT(dev);

	hri_twihs_write_CR_reg(dev->hw, TWIHS_CR_SWRST);
	dev->hw = NULL;

	return ERR_NONE;
}

int32_t _i2c_m_sync_enable(struct _i2c_m_sync_device *const dev)
{
	ASSERT(dev);

	hri_twihs_write_CR_reg(dev->hw, TWIHS_CR_MSEN);

	return ERR_NONE;
}

int32_t _i2c_m_sync_disable(struct _i2c_m_sync_device *const dev)
{
	ASSERT(dev);

	hri_twihs_write_CR_reg(dev->hw, TWIHS_CR_MSDIS);

	return ERR_NONE;
}

int32_t _i2c_m_sync_set_baudrate(struct _i2c_m_sync_device *const dev, uint32_t clkrate, uint32_t baudrate)
{
	ASSERT(dev && baudrate);
	(void)clkrate;

	const struct _i2cm_sync_cfg *cfg = _get_i2cm_sync_cfg(dev->hw);

	return _twihs_set_baudrate(dev->hw, cfg->clkrate, baudrate);
}

int32_t _i2c_m_sync_send_stop(struct _i2c_m_sync_device *const dev)
{
	ASSERT(dev && dev->hw);

	hri_twihs_write_CR_reg(dev->hw, TWIHS_CR_STOP);

	return ERR_NONE;
}

int32_t _i2c_m_sync_transfer(struct _i2c_m_sync_device *const dev, struct _i2c_m_msg *msg)
{
	ASSERT(dev && msg);

	if (dev->service.msg.flags & I2C_M_BUSY) {
		return I2C_ERR_BUSY;
	}

	if (msg->flags & I2C_M_RD) {
		return _i2c_m_sync_read(dev, msg);
	} else {
		return _i2c_m_sync_write(dev, msg);
	}
}

static inline int32_t _i2c_m_sync_write(struct _i2c_m_sync_device *const dev, struct _i2c_m_msg *msg)
{
	uint32_t i;
	uint32_t sr;
	int      ret = ERR_NONE;

	msg->flags |= I2C_M_BUSY;

	if (msg->addr & I2C_M_TEN) {
		hri_twihs_write_MMR_reg(dev->hw, TWIHS_MMR_DADR(0x78 | (msg->addr >> 8)) | TWIHS_MMR_IADRSZ(1));
		hri_twihs_write_IADR_reg(dev->hw, msg->addr & 0xff);
	} else {
		hri_twihs_write_MMR_reg(dev->hw, TWIHS_MMR_DADR(msg->addr));
	}

	for (i = 0; i < msg->len; i++) {
		/* Wait for data is transferred from TWIHS_THR or if NACK is detected */
		do {
			sr = hri_twihs_read_SR_reg(dev->hw);
			if (sr & TWIHS_SR_NACK) {
				ret = I2C_NACK;
				break;
			}
		} while (!(sr & TWIHS_SR_TXRDY));

		if (ret != ERR_NONE)
			break;
		hri_twihs_write_THR_reg(dev->hw, msg->buffer[i]);
	}

	if (msg->flags & I2C_M_STOP) {
		hri_twihs_write_CR_reg(dev->hw, TWIHS_CR_STOP);
		while (!hri_twihs_get_SR_TXCOMP_bit(dev->hw)) {
		};
	}

	dev->service.msg.flags &= ~I2C_M_BUSY;

	return ret;
}

static inline int32_t _i2c_m_sync_read(struct _i2c_m_sync_device *const dev, struct _i2c_m_msg *msg)
{
	uint32_t i;

	msg->flags |= I2C_M_BUSY;

	if (msg->addr & I2C_M_TEN) {
		hri_twihs_write_MMR_reg(dev->hw,
		                        TWIHS_MMR_DADR(0x78 | (msg->addr >> 8)) | TWIHS_MMR_IADRSZ(1) | TWIHS_MMR_MREAD);
		hri_twihs_write_IADR_reg(dev->hw, msg->addr & 0xff);
	} else {
		hri_twihs_write_MMR_reg(dev->hw, TWIHS_MMR_DADR(msg->addr) | TWIHS_MMR_MREAD);
	}
	/* In single data byte master read, the START and STOP must both be set */
	hri_twihs_write_CR_reg(dev->hw, TWIHS_CR_START | ((msg->len == 1) ? TWIHS_CR_STOP : 0));

	for (i = 0; i < msg->len; i++) {
		/* Wait for a byte has been received in TWIHS_RHR since last read */
		while (!hri_twihs_get_SR_RXRDY_bit(dev->hw)) {
			/* Check whether slave acknowledge received after the address byte */
			if (hri_twihs_get_SR_NACK_bit(dev->hw))
				return I2C_NACK;
		};

		msg->buffer[i] = hri_twihs_read_RHR_reg(dev->hw);
		/* In multiple data bytes master read, the STOP must be set after the
		 * last data received but one */
		if (i == (msg->len - 2)) {
			hri_twihs_write_CR_reg(dev->hw, TWIHS_CR_STOP);
		}
	}

	while (!hri_twihs_get_SR_TXCOMP_bit(dev->hw)) {
	};
	dev->service.msg.flags &= ~I2C_M_BUSY;

	return ERR_NONE;
}

static int32_t _twihs_set_baudrate(void *const hw, uint32_t clk, uint32_t baudrate)
{
	uint8_t  ckdiv = 0; /* CWGR_CKDIV */
	uint32_t cldiv;     /* CWGR_CLDIV */

	cldiv = clk / (baudrate * 2);

	/* cldiv(CWGR_CLDIV) must fit in 8 bits and
	 * ckdiv(CWGR_CKDIV) must fit in 3 bits
	 *
	 * cldiv may overflow 255 by ckdiv = 0 in previous step,
	 * So here will check cldiv, if cldiv > 255 then will loop ckdiv from 1 to
	 * 7 for find a valid cldiv value
	 */
	while ((cldiv > 255) && (ckdiv < 7)) {
		/* Increase clock divider */
		ckdiv++;
		/* Divide cldiv value */
		cldiv = cldiv >> 1;
	}

	if (cldiv > 255) {
		return ERR_INVALID_DATA;
	}
	/* set CWGR(Clock Waveform Generator Register) */
	hri_twihs_write_CWGR_reg(hw, TWIHS_CWGR_CKDIV(ckdiv) | TWIHS_CWGR_CLDIV(cldiv) | TWIHS_CWGR_CHDIV(cldiv));

	return ERR_NONE;
}
