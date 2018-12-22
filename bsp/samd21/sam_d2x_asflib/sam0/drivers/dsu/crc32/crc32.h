/**
 *
 * \file
 *
 * \brief SAM DSU CRC32 driver.
 *
 * Copyright (c) 2016 Atmel Corporation. All rights reserved.
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

#ifndef DSU_CRC32_H_INCLUDED
#define DSU_CRC32_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup asfdoc_sam0_drivers_crc32_group SAM 32-bit cyclic redundancy check (CRC32) Driver
 *
 * This driver for Atmel&reg; | SMART ARM&reg;-based microcontrollers provides an interface for the configuration
 * and management of the device's CRC32 (via DSU) functionality. The following
 * driver API modes are covered by this manual:
 *
 *  - Polled APIs
 *
 * The following peripheral is used by this module:
 *  - DSU (Device Service Unit)
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM D21
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_sam0_drivers_crc32_prerequisites
 *  - \ref asfdoc_sam0_drivers_crc32_module_overview
 *  - \ref asfdoc_sam0_drivers_crc32_special_considerations
 *  - \ref asfdoc_sam0_drivers_crc32_api_overview
 *
 *
 * \section asfdoc_sam0_drivers_crc32_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_sam0_drivers_crc32_module_overview Module Overview
 *
 * A cyclic redundancy check (CRC) is an error detection technique used to find accidental
 * errors in data. It is commonly used to determine whether the data during a transmission,
 * or data present in data and programme memories has been corrupted or not. A CRC takes a data
 * stream or a block of data as input and generates a 16- or 32-bit output that can be appended
 * to the data and used as a checksum. When the same data are later received or read, the device
 * or application repeats the calculation.
 * If the new CRC result does not match the one calculated earlier, the block contains a data error.
 * The application will then detect this and may take a corrective action, such as requesting the data
 * to be sent again or simply not using the incorrect data.
 *
 * The DSU unit provides support for calculating a 32-bit cyclic redundancy check (CRC32)
 * value for a memory area (including flash and AHB RAM).
 *
 * \section asfdoc_sam0_drivers_crc32_special_considerations Special Considerations
 *
 * There are no special considerations for this module.
 *
 * \section asfdoc_sam0_drivers_crc32_api_overview API Overview
 * @{
 */

#include <compiler.h>
#include <system.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief CRC initialization function
 *
 * Enables CRC peripheral, clocks and initializes CRC driver.
 */
static inline void dsu_crc32_init(void)
{
#if (SAML21) || (SAML22) || (SAMC20) || (SAMC21) || (SAMR30)
		/* Turn on the digital interface clock */
		system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBB, MCLK_APBBMASK_DSU);
#else
		/* Turn on the digital interface clock */
		system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBB, PM_APBBMASK_DSU);
#endif

}

enum status_code dsu_crc32_cal(const uint32_t addr, const uint32_t len, uint32_t *pcrc32);

#ifdef __cplusplus
}
#endif

 /** @} */

/**
 * \page asfdoc_sam0_drivers_crc32_extra Extra Information for CRC32
 *
 * \section asfdoc_sam0_drivers_crc32_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 *
 * <table>
 *  <tr>
 *      <th>Acronym</th>
 *      <th>Definition</th>
 *  </tr>
 *  <tr>
 *      <td>DSU</td>
 *      <td>Device Service Unit</td>
 * </tr>
 *  <tr>
 *      <td>CRC32</td>
 *      <td>32-bit cyclic redundancy check</td>
 * </tr>
 * </table>
 *
 *
 * \section asfdoc_sam0_drivers_crc32_extra_dependencies Dependencies
 * This driver has the following dependencies:
 *
 *  - DSU
 *
 *
 * \section asfdoc_sam0_drivers_crc32_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_sam0_drivers_crc32_extra_history Module History
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
 *		<td>Initial release</td>
 *	</tr>
 * </table>
 */

/**
 * \page asfdoc_sam0_drivers_crc32_exqsg Examples for CRC32
 *
 * This is a list of the available Quick Start Guides (QSGs) and example
 * applications for \ref asfdoc_sam0_drivers_crc32_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that a QSG can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_sam0_crc32_basic_use_case
 *
 * \page asfdoc_sam0_drivers_crc32_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *      <th>Doc. Rev.</td>
 *		<th>Date</td>
 *		<th>Comments</td>
 *	</tr>
 *	<tr>
 *		<td>06/2016</td>
 *		<td>Initial release</td>
 *	</tr>
 * </table>
 *
 */

 #ifdef __cplusplus
}
#endif

#endif  /* DSU_CRC32_H_INCLUDED */
