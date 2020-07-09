/**
 * \file
 *
 * \brief In System Programming API
 *
 * Copyright (c) 2011-2015 Atmel Corporation. All rights reserved.
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

#ifndef _ISP_H_
#define _ISP_H_

#include "conf_isp.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup isp In System Programming API
 *
 * @{
 */

/**
 * \name Main In System Programming functions
 * @{
 */

/**
 * \brief Initializes the ISP interface
 *
 * Example, load the JTAG ID in signature memory
 */
void isp_init(void);

/**
 * \brief Gives the security state of the chip
 *
 * \return \c 1 if chip is secured, otherwise \c 0.
 */
bool isp_is_security(void);

/**
 * \brief Change the boot process configuration
 * to enable/disable the ISP mode for the next startup.
 *
 * \param force  Enable the ISP mode for the next startup if true
 */
void isp_force_boot_isp(bool force);

/**
 * \brief Erase the application flash area and eventually the eeprom
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
bool isp_erase_chip(void);

/**
 * \brief Erase a part of the application flash area
 * This function must be called again as long as it returns 0.
 *
 * \return \c 1 if the whole application flash area is erased, otherwise it is
 * not finished.
 *
 * This function has been created to split a long erase so that
 * the ISP application is able to answer external pending requests.
 */

bool isp_erase_chip_split(void);

/**
 * \brief Resets the device to start the user application
 *
 * The ISP mode must be disabled before (See isp_force_boot_isp(false))
 * to allow the boot process to jump to the user application.
 *
 * \note: this function is usually implemented by using a watchdog reset
 * or a software reset to restart the CPU.
 */
void isp_start_appli(void);
//! @}


//! Data type for holding flash memory addresses
#ifdef ISP_SMALL_MEMORY_SIZE
	typedef uint16_t isp_addr_t;
#else
	typedef uint32_t isp_addr_t;
#endif

//! Memory API definition
typedef struct {
	//! Size of the memory (unit Byte)
	uint32_t size;
	//! Function to read memory
	void (*fnct_read) (void *dst, isp_addr_t src, uint16_t nbytes);
	//! Function to write memory
	void (*fnct_write) (isp_addr_t dst, const void *src, uint16_t nbytes);
} isp_mem_t;

/**
 * \name Memory units index values
 * Used to access at a memory through \ref isp_memories list.
 * @{
 */
#define ISP_MEM_FLASH                        0x00
#define ISP_MEM_EEPROM                       0x01
#define ISP_MEM_SECURITY                     0x02
#define ISP_MEM_CONFIGURATION                0x03
#define ISP_MEM_BOOTLOADER                   0x04
#define ISP_MEM_SIGNATURE                    0x05
#define ISP_MEM_USER                         0x06
#define ISP_MEM_INT_RAM                      0x07
#define ISP_MEM_EXT_MEM_CS0                  0x08
#define ISP_MEM_EXT_MEM_CS1                  0x09
#define ISP_MEM_EXT_MEM_CS2                  0x0A
#define ISP_MEM_EXT_MEM_CS3                  0x0B
#define ISP_MEM_EXT_MEM_CS4                  0x0C
#define ISP_MEM_EXT_MEM_CS5                  0x0D
#define ISP_MEM_EXT_MEM_CS6                  0x0E
#define ISP_MEM_EXT_MEM_CS7                  0x0F
#define ISP_MEM_EXT_MEM_DF                   0x10
#define ISP_MEM_COUNT                        0x11 // Number of memory units
//! @}

//! Memories list structure
typedef union {
	isp_mem_t const *mem[ISP_MEM_COUNT];
	struct {
		isp_mem_t const *flash;
		isp_mem_t const *eeprom;
		isp_mem_t const *security;
		isp_mem_t const *conf;
		isp_mem_t const *bootloader;
		isp_mem_t const *signature;
		isp_mem_t const *user;
		isp_mem_t const *int_ram;
		isp_mem_t const *ext_mem_cs0;
		isp_mem_t const *ext_mem_cs1;
		isp_mem_t const *ext_mem_cs2;
		isp_mem_t const *ext_mem_cs3;
		isp_mem_t const *ext_mem_cs4;
		isp_mem_t const *ext_mem_cs5;
		isp_mem_t const *ext_mem_cs6;
		isp_mem_t const *ext_mem_cs7;
		isp_mem_t const *ext_mem_df;
	}list;
} isp_mems_t;

//! Memories list declaration
extern const isp_mems_t isp_memories;

COMPILER_PACK_SET(1) // alignment requested to simulate a memory

//! Memory signature structure to store JTAG ID
typedef union {
	uint8_t mem[4];
	struct {
		uint8_t manufacture;
		uint8_t product_number_msb;
		uint8_t product_number_lsb;
		uint8_t product_revision;
	};
} isp_mem_signature_t;


/**
 * Memory bootloader structure
 *
 * In the FLIP protocol, this structure is used to store medium
 * and minor bootloader versions:
 * - Example, Version 0x00 give 1.0.0 on batchisp log
 * - Example, Version 0x03 give 1.0.3 on batchisp log
 * - Example, Version 0x25 give 1.2.5 on batchisp log
 * - id1 & id2 are not used and must always be 0.
 */
typedef struct {
	uint8_t version;
	uint8_t id1;
	uint8_t id2;
} isp_mem_bootloader_t;

COMPILER_PACK_RESET()

//! @}

#ifdef __cplusplus
}
#endif

#endif // _ISP_H_
