/**
 * \file
 *
 * \brief Generic RAMECC related functionality.
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

#include <utils.h>
#include <utils_assert.h>
#include <hpl_ramecc.h>

/* RAMECC device descriptor */
struct _ramecc_device device;

/**
 * \brief Initialize RAMECC
 */
int32_t _ramecc_init(void)
{
	if (hri_ramecc_get_STATUS_ECCDIS_bit(RAMECC)) {
		return ERR_ABORTED;
	}

	NVIC_DisableIRQ(RAMECC_IRQn);
	NVIC_ClearPendingIRQ(RAMECC_IRQn);
	NVIC_EnableIRQ(RAMECC_IRQn);

	return ERR_NONE;
}

void _ramecc_register_callback(const enum _ramecc_callback_type type, ramecc_cb_t cb)
{
	if (RAMECC_DUAL_ERROR_CB == type) {
		device.ramecc_cb.dual_bit_err = cb;
		hri_ramecc_write_INTEN_DUALE_bit(RAMECC, NULL != cb);
	} else if (RAMECC_SINGLE_ERROR_CB == type) {
		device.ramecc_cb.single_bit_err = cb;
		hri_ramecc_write_INTEN_SINGLEE_bit(RAMECC, NULL != cb);
	}
}

/**
 * \internal RAMECC interrupt handler
 */
void RAMECC_Handler(void)
{
	struct _ramecc_device *dev      = (struct _ramecc_device *)&device;
	volatile uint32_t      int_mask = hri_ramecc_read_INTFLAG_reg(RAMECC);

	if (int_mask & RAMECC_INTFLAG_DUALE && dev->ramecc_cb.dual_bit_err) {
		dev->ramecc_cb.dual_bit_err((uint32_t)hri_ramecc_read_ERRADDR_reg(RAMECC));
	} else if (int_mask & RAMECC_INTFLAG_SINGLEE && dev->ramecc_cb.single_bit_err) {
		dev->ramecc_cb.single_bit_err((uint32_t)hri_ramecc_read_ERRADDR_reg(RAMECC));
	} else {
		return;
	}
}
