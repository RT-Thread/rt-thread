/**
 * \file
 *
 * \brief SAM Divide and Square Root Accelerator (DIVAS) Driver
 *
 * Copyright (c) 2015 Atmel Corporation. All rights reserved.
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

#include "divas.h"

/**
 * \internal
 * \brief Initializes and enables the Divide and Square Root Accelerator (DIVAS) Driver.
 *
 * Enable the clocks used by Divide and Square Root Accelerator (DIVAS) Driver.
 * Enable leading zero optimization.
 *
 * \note When SYSTEM module is used, this function will be invoked by
 * \ref system_init() automatically if the module is included.
 */
void _system_divas_init(void);
void _system_divas_init(void)
{
	/* Turn on the digital interface clock. */
	system_ahb_clock_set_mask(MCLK_AHBMASK_DIVAS);

	DIVAS->CTRLA.reg &= ~DIVAS_CTRLA_DLZ;
}

/**
 * \brief Signed division operation
 *
 * Run the signed division operation and return the quotient.
 *
 * \param[in]  numerator   The dividend of the signed division operation
 * \param[in]  denominator The divisor of the signed division operation
 *
 * \return The quotient of the DIVAS signed division operation.
 */
int32_t divas_idiv(int32_t numerator, int32_t denominator)
{
	/* Disable interrupt. */
	cpu_irq_enter_critical();

	/* Signed division. */
	DIVAS->CTRLA.reg |= DIVAS_CTRLA_SIGNED;

	/* Write the dividend to DIVIDEND register. */
	DIVAS->DIVIDEND.reg = numerator;
	/* Write the divisor to DIVISOR register. */
	DIVAS->DIVISOR.reg = denominator;

	while(DIVAS->STATUS.bit.BUSY){
		/* Wait the division is complete. */
	}

	int32_t quotient = DIVAS->RESULT.reg;

	/* Enable interrupt. */
	cpu_irq_leave_critical();

	return quotient;
}

/**
 * \brief Unsigned division operation
 *
 * Run the unsigned division operation and return the results.
 *
 * \param[in]  numerator   The dividend of the unsigned division operation
 * \param[in]  denominator The divisor of the unsigned division operation
 *
 * \return The quotient of the DIVAS unsigned division operation.
 */
uint32_t divas_uidiv(uint32_t numerator, uint32_t denominator)
{
	/* Disable interrupt. */
	cpu_irq_enter_critical();

	/* Unsigned division. */
	DIVAS->CTRLA.reg &= ~DIVAS_CTRLA_SIGNED;

	/* Write the dividend to DIVIDEND register. */
	DIVAS->DIVIDEND.reg = numerator;
	/* Write the divisor to DIVISOR register. */
	DIVAS->DIVISOR.reg = denominator;

	while(DIVAS->STATUS.bit.BUSY){
		/* Wait the division is complete. */
	}

	uint32_t quotient = DIVAS->RESULT.reg;

	/* Enable interrupt. */
	cpu_irq_leave_critical();

	return quotient;
}

/**
 * \brief Signed division remainder operation
 *
 * Run the signed division operation and return the remainder.
 *
 * \param[in]  numerator   The dividend of the signed division operation
 * \param[in]  denominator The divisor of the signed division operation
 *
 * \return The remainder of the DIVAS signed division operation.
 */
int32_t divas_idivmod(int32_t numerator, int32_t denominator)
{
	/* Disable interrupt. */
	cpu_irq_enter_critical();

	/* Signed division. */
	DIVAS->CTRLA.reg |= DIVAS_CTRLA_SIGNED;

	/* Write the dividend to DIVIDEND register. */
	DIVAS->DIVIDEND.reg = numerator;
	/* Write the divisor to DIVISOR register. */
	DIVAS->DIVISOR.reg = denominator;

	while(DIVAS->STATUS.bit.BUSY){
		/* Wait the division is complete. */
	}

	int32_t remainder = DIVAS->REM.reg;

	/* Enable interrupt. */
	cpu_irq_leave_critical();

	return remainder;
}

/**
 * \brief Unsigned division remainder operation
 *
 * Run the unsigned division operation and return the remainder.
 *
 * \param[in]  numerator   The dividend of the unsigned division operation
 * \param[in]  denominator The divisor of the unsigned division operation
 *
 * \return The remainder of the DIVAS unsigned division operation.
 */
uint32_t divas_uidivmod(uint32_t numerator, uint32_t denominator)
{
	/* Disable interrupt. */
	cpu_irq_enter_critical();

	/* Unsigned division. */
	DIVAS->CTRLA.reg &= ~DIVAS_CTRLA_SIGNED;

	/* Write the dividend to DIVIDEND register. */
	DIVAS->DIVIDEND.reg = numerator;
	/* Write the divisor to DIVISOR register. */
	DIVAS->DIVISOR.reg = denominator;

	while(DIVAS->STATUS.bit.BUSY){
		/* Wait the division is complete. */
	}

	uint32_t remainder = DIVAS->REM.reg;

	/* Enable interrupt. */
	cpu_irq_leave_critical();

	return remainder;
}

/**
 * \brief Square root operation
 *
 * Run the square root operation and return the results.
 *
 * \param[in]  radicand  The radicand of the square root operation
 *
 * \return The result of the DIVAS square root operation.
 */
uint32_t  divas_sqrt(uint32_t radicand)
{
	/* Disable interrupt. */
	cpu_irq_enter_critical();

	/* Write the radicand to DIVIDEND register. */
	DIVAS->SQRNUM.reg = radicand;

	while(DIVAS->STATUS.bit.BUSY){
		/* Wait the square root is complete. */
	}

	uint32_t result_sqrt = DIVAS->RESULT.reg;

	/* Enable interrupt. */
	cpu_irq_leave_critical();

	return result_sqrt;
}

/**
 * \name DIVAS Operation Overloading
 * @{
 */

#if DIVAS_OVERLOAD_MODE == true
#  if defined ( __GNUC__ )

/**
 * \brief Signed division operation overload
 *
 * Run the signed division operation and return the results.
 *
 * \param[in]  numerator   The dividend of the signed division operation
 * \param[in]  denominator The divisor of the signed division operation
 *
 * \return The quotient of the DIVAS signed division operation.
 */
int32_t __aeabi_idiv(int32_t numerator, int32_t denominator)
{
	return divas_idiv(numerator, denominator);
}

/**
 * \brief Unsigned division operation overload
 *
 * Run the unsigned division operation and return the results.
 *
 * \param[in]  numerator   The dividend of the unsigned division operation
 * \param[in]  denominator The divisor of the unsigned division operation
 *
 * \return The quotient of the DIVAS unsigned division operation.
 */
uint32_t __aeabi_uidiv(uint32_t numerator, uint32_t denominator)
{
	return divas_uidiv(numerator, denominator);
}

/**
 * \brief Signed division remainder operation overload
 *
 * Run the signed division operation and return the remainder.
 *
 * \param[in]  numerator   The dividend of the signed division operation
 * \param[in]  denominator The divisor of the signed division operation
 *
 * \return The remainder of the DIVAS signed division operation.
 */
uint64_t __aeabi_idivmod(int32_t numerator, int32_t denominator)
{
	uint64_t uret;
	int32_t quotient, remainder;

	/* Disable interrupt. */
	cpu_irq_enter_critical();

	/* Signed division. */
	DIVAS->CTRLA.reg |= DIVAS_CTRLA_SIGNED;

	/* Write the dividend to DIVIDEND register. */
	DIVAS->DIVIDEND.reg = numerator;
	/* Write the divisor to DIVISOR register. */
	DIVAS->DIVISOR.reg = denominator;

	while(DIVAS->STATUS.bit.BUSY){
		/* Wait the division is complete. */
	}

	/* Read out the result. */
	quotient = DIVAS->RESULT.reg;
	remainder = DIVAS->REM.reg;

	/* quotient in r0, remainder in r1 */
	uret = ((uint64_t)quotient & 0x00000000FFFFFFFF ) |
			(((uint64_t)remainder ) << 32);

	/* Enable interrupt. */
	cpu_irq_leave_critical();

	return uret;
}

/**
 * \brief Unsigned division remainder operation overload
 *
 * Run the unsigned division operation and return the remainder.
 *
 * \param[in]  numerator   The dividend of the unsigned division operation
 * \param[in]  denominator The divisor of the unsigned division operation
 *
 * \return The remainder of the DIVAS unsigned division operation.
 */
uint64_t __aeabi_uidivmod(uint32_t numerator, uint32_t denominator)
{
	uint64_t uret;
	uint32_t quotient, remainder;

	/* Disable interrupt. */
	cpu_irq_enter_critical();

	/* Unsigned division. */
	DIVAS->CTRLA.reg &= ~DIVAS_CTRLA_SIGNED;

	/* Write the dividend to DIVIDEND register. */
	DIVAS->DIVIDEND.reg = numerator;
	/* Write the divisor to DIVISOR register. */
	DIVAS->DIVISOR.reg = denominator;

	while(DIVAS->STATUS.bit.BUSY){
	/* Wait the division is complete. */
	}

	/* Read out the result. */
	quotient = DIVAS->RESULT.reg;
	remainder = DIVAS->REM.reg;

	/* quotient in r0, remainder in r1 */
	uret = quotient | (((uint64_t)remainder) << 32);

	/* Enable interrupt. */
	cpu_irq_leave_critical();

	return uret;
}

#  elif defined ( __ICCARM__ )
/**
 * \brief Signed division operation overload
 *
 * Run the signed division operation and return the results.
 *
 * \param[in]  numerator   The dividend of the signed division operation
 * \param[in]  denominator The divisor of the signed division operation
 *
 * \return The quotient of the DIVAS signed division operation.
 */
int32_t __aeabi_idiv(int32_t numerator, int32_t denominator)
{
	return divas_idiv(numerator, denominator);
}

/**
 * \brief Unsigned division operation overload
 *
 * Run the unsigned division operation and return the results.
 *
 * \param[in]  numerator   The dividend of the unsigned division operation
 * \param[in]  denominator The divisor of the unsigned division operation
 *
 * \return The quotient of the DIVAS unsigned division operation.
 */
uint32_t __aeabi_uidiv(uint32_t numerator, uint32_t denominator)
{
	return divas_uidiv(numerator, denominator);
}

/**
 * \brief Signed division remainder operation overload
 *
 * Run the signed division operation and return the remainder.
 * \param[in]  numerator   The dividend of the signed division operation
 * \param[in]  denominator The divisor of the signed division operation
 *
 * \return The remainder of the DIVAS signed division operation.
 */
__value_in_regs idiv_return __aeabi_idivmod(int numerator, int denominator)
{
	idiv_return result;

	/* Disable interrupt. */
	cpu_irq_enter_critical();

	/* Signed division. */
	DIVAS->CTRLA.reg |= DIVAS_CTRLA_SIGNED;

	/* Write the dividend to DIVIDEND register. */
	DIVAS->DIVIDEND.reg = numerator;
	/* Write the divisor to DIVISOR register. */
	DIVAS->DIVISOR.reg = denominator;

	while(DIVAS->STATUS.bit.BUSY){
		/* Wait the division is complete. */
	}

	/* Read out the result. */
	result.quotient = DIVAS->RESULT.reg;
	result.remainder = DIVAS->REM.reg;

	/* Enable interrupt. */
	cpu_irq_leave_critical();

	return result;
}

/**
 * \brief Unsigned division remainder operation overload
 *
 * Run the unsigned division operation and return the remainder.
 * \param[in]  numerator   The dividend of the unsigned division operation
 * \param[in]  denominator The divisor of the unsigned division operation
 *
 * \return The remainder of the DIVAS unsigned division operation.
 */
__value_in_regs uidiv_return __aeabi_uidivmod(unsigned numerator, unsigned denominator)
{
	uidiv_return result;

	/* Disable interrupt. */
	cpu_irq_enter_critical();

	/* Unsigned division. */
	DIVAS->CTRLA.reg &= ~DIVAS_CTRLA_SIGNED;

	/* Write the dividend to DIVIDEND register. */
	DIVAS->DIVIDEND.reg = numerator;
	/* Write the divisor to DIVISOR register. */
	DIVAS->DIVISOR.reg = denominator;

	while(DIVAS->STATUS.bit.BUSY){
		/* Wait the division is complete. */
	}

	/* Read out the result. */
	result.quotient = DIVAS->RESULT.reg;
	result.remainder = DIVAS->REM.reg;

	/* Enable interrupt. */
	cpu_irq_leave_critical();

	return result;
}

#  endif
#endif

/** @} */

