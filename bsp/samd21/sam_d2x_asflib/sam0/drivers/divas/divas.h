/**
 * \file
 *
 * \brief SAM Divide and Square Root Accelerator (DIVAS) Driver
 *
 * Copyright (c) 2015-2016 Atmel Corporation. All rights reserved.
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

#ifndef DIVAS_H_INCLUDED
#define DIVAS_H_INCLUDED

/**
 * \defgroup asfdoc_sam0_divas_group SAM Divide and Square Root Accelerator (DIVAS) Driver
 *
 * This driver for Atmel&reg; | SMART ARM&reg;-based microcontrollers provides an
 * interface for the configuration and management of the device's Divide and
 * Square Root Accelerator functionality.
 *
 * The following peripherals are used by this module:
 *  - DIVAS (Divide and Square Root Accelerator)
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM C20/C21
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_sam0_divas_prerequisites
 *  - \ref asfdoc_sam0_divas_module_overview
 *  - \ref asfdoc_sam0_divas_special_considerations
 *  - \ref asfdoc_sam0_divas_extra_info
 *  - \ref asfdoc_sam0_divas_examples
 *  - \ref asfdoc_sam0_divas_api_overview
 *
 *
 * \section asfdoc_sam0_divas_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_sam0_divas_module_overview Module Overview
 *
 * This driver provides an interface for the Divide and Square Root Accelerator
 * on the device.
 *
 * The DIVAS is a programmable 32-bit signed or unsigned hardware divider and a 
 * 32-bit unsigned square root hardware engine. When running signed division, 
 * both the input and the result will be in two's complement format. The result of
 * signed division is that the remainder has the same sign as the dividend and 
 * the quotient is negative if the dividend and divisor have opposite signs.
 * When the square root input register is programmed, the square root function 
 * starts and the result will be stored in the Remainder register.
 *
 * There are two ways to calculate the results:
 * - Call the DIVAS API
 * - Overload "/" and "%" operation
 * \note Square root operation can't implement overload operation.
 
 * \subsection asfdoc_sam0_divas_module_overview_overload Overload Operation
 * The operation is implemented automatically by EABI (Enhanced Application Binary 
 * Interface). EABI is a standard calling convention, which is defined by ARM. 
 * The four functions interface can implement division and mod operation in EABI.
 *
 * The following prototypes for EABI division operation in ICCARM tool chain:
 * \code
    int __aeabi_idiv(int numerator, int denominator);
    unsigned __aeabi_uidiv(unsigned numerator, unsigned denominator);
    __value_in_regs idiv_return __aeabi_idivmod( int numerator, int denominator);
    __value_in_regs uidiv_return __aeabi_uidivmod( unsigned numerator, 
												unsigned denominator);
   \endcode
 * The following prototypes for EABI division operation in GNUC tool chain:
 * \code
    int __aeabi_idiv(int numerator, int denominator);
    unsigned __aeabi_uidiv(unsigned numerator, unsigned denominator);
    uint64_t __aeabi_idivmod( int numerator, int denominator);
    uint64_t uidiv_return __aeabi_uidivmod( unsigned numerator, 
											unsigned denominator);
   \endcode
 * No matter what kind of tool chain, by using DIVAS module in the four functions 
 * body, the user can transparently access the DIVAS module when writing normal C 
 * code. For example:
 * \code
    void division(int32_t b, int32_t c)
    {
        int32_t a;
        a = b / c;
        return a;
    }
   \endcode
 * Similarly, the user can use the "a = b % c;" symbol to implement the operation with 
 * DIVAS, and needn't to care about the internal operation process.
 * 
 * \subsection asfdoc_sam0_divas_module_overview_operand Operand Size
 *  - Divide: The DIVAS can perform 32-bit signed and unsigned division.
 *  - Square Root: The DIVAS can perform 32-bit unsigned division.
 
 * \subsection asfdoc_sam0_divas_module_overview_Signed Signed Division
 *  When the signed flag is one, both the input and the result will be in two's 
 *  complement format. The result of signed division is that the remainder has 
 *  the same sign as the dividend and the quotient is negative if the dividend 
 *  and divisor have opposite signs.
 *  \note When the maximum negative number is divided by the minimum negative 
 *  number, the resulting quotient overflows the signed integer range and will 
 *  return the maximum negative number with no indication of the overflow. This 
 *  occurs for 0x80000000 / 0xFFFFFFFF in 32-bit operation and 0x8000 / 0xFFFF 
 *  in 16-bit operation.
 *
 * \subsection asfdoc_sam0_divas_module_overview_zero Divide By Zero
 *  A divide by zero will cause a fault if the DIVISOR is programmed to zero. The 
 *  result is that the quotient is zero and the reminder is equal to the dividend.
 *
 * \subsection asfdoc_sam0_divas_module_overview_square Unsigned Square Root
 *  When the square root input register is programmed, the square root function 
 *  starts and the result will be stored in the Result and Remainder registers.
 * \note The square root function can't overload.
 *
 * \section asfdoc_sam0_divas_special_considerations Special Considerations
 *
 * There are no special considerations for this module.
 *
 * \section asfdoc_sam0_divas_extra_info Extra Information
 *
 *
 * For extra information, see \ref asfdoc_sam0_divas_extra. This includes:
 *  - \ref asfdoc_sam0_divas_extra_acronyms
 *  - \ref asfdoc_sam0_divas_extra_dependencies
 *  - \ref asfdoc_sam0_divas_extra_errata
 *  - \ref asfdoc_sam0_divas_extra_history
 *
 *
 * \section asfdoc_sam0_divas_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_sam0_divas_exqsg.
 *
 *
 * \section asfdoc_sam0_divas_api_overview API Overview
 * @{
 */

#include <compiler.h>
#include <system.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief DIVAS signed division operator result output structure.
 *
 *  DIVAS signed division operator output data structure.
 */
typedef struct {
	/** Signed division operator result: quotient */
	int32_t quotient; 
	/** Signed division operator result: remainder */
	int32_t remainder;
} idiv_return;

/**
 * \brief DIVAS unsigned division operator result output structure.
 *
 *  DIVAS unsigned division operator output data structure.
 */
typedef struct {
	/** Unsigned division operator result: quotient */
	uint32_t quotient; 
	/** Unsigned division operator result: remainder */
	uint32_t remainder;
} uidiv_return; 

/**
 * \brief Enables DIVAS leading zero optimization.
 *
 *  Enable leading zero optimization from the Divide and Square Root Accelerator
 *  module. When leading zero optimization is enable, 16-bit division completes 
 *  in 2-8 cycles and 32-bit division completes in 2-16 cycles.
 *
 */
static inline void divas_enable_dlz(void)
{
	/* Enable DLZ. */
	DIVAS->CTRLA.reg &= ~DIVAS_CTRLA_DLZ;
}

/**
 * \brief Disables DIVAS leading zero optimization.
 *
 *  Disable leading zero optimization from the Divide and Square Root Accelerator
 *  module. When leading zero optimization is disable, 16-bit division completes 
 *  in 8 cycles and 32-bit division completes in 16 cycles.
 *
 */
static inline void divas_disable_dlz(void)
{
	/* Disable DLZ. */
	DIVAS->CTRLA.reg |= DIVAS_CTRLA_DLZ;
}

/**
 * \name Call the DIVAS API Operation
 * @{
 * In this mode, the way that directly call the DIVAS API implement division or 
 * mod operation. 
 */

int32_t divas_idiv(int32_t numerator, int32_t denominator);
uint32_t divas_uidiv(uint32_t numerator, uint32_t denominator);
int32_t divas_idivmod(int32_t numerator, int32_t denominator);
uint32_t divas_uidivmod(uint32_t numerator, uint32_t denominator);
uint32_t divas_sqrt(uint32_t radicand);

/** @} */

/**
 * \name DIVAS Overload '/' and '%' Operation
 * @{
 * In this mode, the user can transparently access the DIVAS module when writing 
 * normal C code. E.g. "a = b / c;" or "a = b % c;" will be translated to a 
 * subroutine call, which uses the DIVAS.
 */

#if DIVAS_OVERLOAD_MODE == true
#  if defined ( __GNUC__ )
int32_t __aeabi_idiv(int32_t numerator, int32_t denominator);
uint32_t __aeabi_uidiv(uint32_t numerator, uint32_t denominator);
uint64_t __aeabi_idivmod(int32_t numerator, int32_t denominator);
uint64_t __aeabi_uidivmod(uint32_t numerator, uint32_t denominator);

#  elif defined ( __ICCARM__ )
int32_t __aeabi_idiv(int32_t numerator, int32_t denominator);
uint32_t __aeabi_uidiv(uint32_t numerator, uint32_t denominator);
__value_in_regs idiv_return __aeabi_idivmod(int numerator, int denominator);
__value_in_regs uidiv_return __aeabi_uidivmod(unsigned numerator, unsigned denominator); 
#  endif
#endif

/** @} */

#ifdef __cplusplus
}
#endif

/** @} */

/**
 * \page asfdoc_sam0_divas_extra Extra Information for DIVAS Driver
 *
 * \section asfdoc_sam0_divas_extra_acronyms Acronyms
 *
 * <table>
 *	<tr>
 *		<th>Acronym</th>
 *		<th>Description</th>
 *	</tr>
 *  <tr>
 *		<td>DIVAS</td>
 *		<td>Divide and Square Root Accelerator</td>
 *	</tr>
 *  <tr>
 *		<td>EABI</td>
 *		<td>Enhanced Application Binary Interface</td>
 *	</tr>
 * </table>
 *
 *
 * \section asfdoc_sam0_divas_extra_dependencies Dependencies
 * This driver has no dependencies.
 *
 *
 * \section asfdoc_sam0_divas_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_sam0_divas_extra_history Module History
 * An overview of the module history is presented in the table below, with
 * details on the enhancements and fixes made to the module since its first
 * release. The current version of this corresponds to the newest version in
 * the table.
 *
 * <table>
 *	<tr>
 *		<th>Changelog</th>
 *	</tr>
  *	<tr>
 *		<td>Initial Release</td>
 *	</tr>
 * </table>
 */

/**
 * \page asfdoc_sam0_divas_exqsg Examples for DIVAS Driver
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_sam0_divas_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that a QSG can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_sam0_divas_basic_use_case
 *  - \subpage asfdoc_sam0_divas_overload_use_case
 *
 * \page asfdoc_sam0_divas_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *		<th>Doc. Rev.</td>
 *		<th>Date</td>
 *		<th>Comments</td>
 *	</tr>
 *	<tr>
 *		<td>42644A</td>
 *		<td>01/2016</td>
 *		<td>Initial document release</td>
 *	</tr>
 * </table>
 */

#endif /* DIVAS_H_INCLUDED */

