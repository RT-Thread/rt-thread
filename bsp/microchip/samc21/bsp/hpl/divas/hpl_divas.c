/**
 * \file
 *
 * \brief Division operation related functionality.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

#include <compiler.h>
#include <hpl_div.h>
#include <hpl_divas_config.h>

#include <hal_atomic.h>
#define _DIVAS_CRITICAL_ENTER()                                                                                        \
	do {                                                                                                               \
		volatile hal_atomic_t _divas_atomic;                                                                           \
		_divas_atomic = __get_PRIMASK();                                                                               \
		__disable_irq();
#define _DIVAS_CRITICAL_LEAVE()                                                                                        \
	__set_PRIMASK(_divas_atomic);                                                                                      \
	}                                                                                                                  \
	while (0)

/** Return 32 bit result, the result only. */
#define _divas_result32() (DIVAS->RESULT.reg)

/** Return 64 bit result, the result and remainder. */
#define _divas_result64() (*((uint64_t *)(&DIVAS->RESULT.reg)))

/** \brief Execute hardware for division
 *  \param[in] s Indicate operation mode: signed/unsigned
 *  \param[in] n The dividend
 *  \param[in] d The divisor
 */
static inline void _divas_div(const uint8_t s, const uint32_t n, const uint32_t d)
{
	DIVAS->CTRLA.bit.SIGNED = s;
	DIVAS->DIVIDEND.reg     = n;
	DIVAS->DIVISOR.reg      = d;
	while (DIVAS->STATUS.bit.BUSY) {
		/* Wait the division is complete. */
	}
}

/**
 * \brief Initialize hardware for division operation
 */
void _div_init(void)
{
	hri_divas_write_CTRLA_DLZ_bit(DIVAS, CONF_DIVAS_DLZ);
}

/**
 * \brief Do signed division
 */
int32_t __aeabi_idiv(int32_t numerator, int32_t denominator)
{
	int32_t res;
	_DIVAS_CRITICAL_ENTER();
	_divas_div(1, numerator, denominator);
	res = _divas_result32();
	_DIVAS_CRITICAL_LEAVE();
	return res;
}

/**
 * \brief Do unsigned division
 */
uint32_t __aeabi_uidiv(uint32_t numerator, uint32_t denominator)
{
	uint32_t res;
	_DIVAS_CRITICAL_ENTER();
	_divas_div(0, numerator, denominator);
	res = _divas_result32();
	_DIVAS_CRITICAL_LEAVE();
	return res;
}

/**
 * \brief Do signed division, return result and remainder
 */
uint64_t __aeabi_idivmod(int numerator, int denominator)
{
	uint64_t res;
	_DIVAS_CRITICAL_ENTER();
	_divas_div(1, numerator, denominator);
	res = _divas_result64();
	_DIVAS_CRITICAL_LEAVE();
	return res;
}

/**
 * \brief Do unsigned division, return result and remainder
 */
uint64_t __aeabi_uidivmod(unsigned numerator, unsigned denominator)
{
	uint64_t res;
	_DIVAS_CRITICAL_ENTER();
	_divas_div(0, numerator, denominator);
	res = _divas_result64();
	_DIVAS_CRITICAL_LEAVE();
	return res;
}
