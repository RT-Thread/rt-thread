/**
 * \file
 *
 * \brief CTRL_ACCESS interface for common SD/MMC stack
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
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

#ifndef _SD_MMC_MEM_H_
#define _SD_MMC_MEM_H_

/**
 * \ingroup sd_mmc_stack_group
 * \defgroup sd_mmc_stack_mem SD/MMC Memory
 *
 * SD/MMC memory APIs required by CTRL_ACCESS module
 * (\ref group_common_services_storage_ctrl_access).
 *
 * For usual application which use the SD/MMC card in
 * memory mode through a file system or a USB device MSC,
 * only a call of \ref sd_mmc_init() function is required in the startup.
 *
 * @{
 */

#include "conf_access.h"
#include "ctrl_access.h"

#if (SD_MMC_0_MEM == ENABLE) || (SD_MMC_1_MEM == ENABLE)

/*! \name Control Interface
 */
//! @{

/*! \brief Tests the memory state and initializes the memory if required.
 *
 * The TEST UNIT READY SCSI primary command allows an application client to poll
 * a LUN until it is ready without having to allocate memory for returned data.
 *
 * This command may be used to check the media status of LUNs with removable
 * media.
 *
 * \param slot SD/MMC Slot Card Selected.
 *
 * \return Status.
 */
extern Ctrl_status sd_mmc_test_unit_ready(uint8_t slot);
//! Instance Declaration for sd_mmc_test_unit_ready Slot O
extern Ctrl_status sd_mmc_test_unit_ready_0(void);
//! Instance Declaration for sd_mmc_test_unit_ready Slot 1
extern Ctrl_status sd_mmc_test_unit_ready_1(void);

/*! \brief Returns the address of the last valid sector in the memory.
 *
 * \param slot SD/MMC Slot Card Selected.
 * \param u32_nb_sector Pointer to the address of the last valid sector.
 *
 * \return Status.
 */
extern Ctrl_status sd_mmc_read_capacity(uint8_t slot,uint32_t *u32_nb_sector);
//! Instance Declaration for sd_mmc_read_capacity Slot O
extern Ctrl_status sd_mmc_read_capacity_0(uint32_t *u32_nb_sector);
//! Instance Declaration for sd_mmc_read_capacity Slot 1
extern Ctrl_status sd_mmc_read_capacity_1(uint32_t *u32_nb_sector);

/*! \brief Unload/Load the SD/MMC card selected
 *
 * The START STOP UNIT SCSI optional command allows an application client to
 * eject the removable medium on a LUN.
 *
 * \param slot SD/MMC Slot Card Selected.
 * \param unload \c true to unload the medium, \c false to load the medium.
 *
 * \return \c true if unload/load done success.
 */
extern bool sd_mmc_unload(uint8_t slot, bool unload);
//! Instance Declaration for sd_mmc_unload Slot O
extern bool sd_mmc_unload_0(bool unload);
//! Instance Declaration for sd_mmc_unload Slot 1
extern bool sd_mmc_unload_1(bool unload);

/*! \brief Returns the write-protection state of the memory.
 *
*  \param slot SD/MMC Slot Card Selected.
 * \return \c true if the memory is write-protected, else \c false.
 *
 * \note Only used by removable memories with hardware-specific write
 *       protection.
 */
extern bool sd_mmc_wr_protect(uint8_t slot);
//! Instance Declaration for sd_mmc_wr_protect Slot O
extern bool sd_mmc_wr_protect_0(void);
//! Instance Declaration for sd_mmc_wr_protect Slot 1
extern bool sd_mmc_wr_protect_1(void);

/*! \brief Tells whether the memory is removable.
 *
 * \param slot SD/MMC Slot Card Selected.
 * \return \c true if the memory is removable, else \c false.
 */
extern bool sd_mmc_removal(uint8_t slot);
//! Instance Declaration for sd_mmc_removal Slot O
extern bool sd_mmc_removal_0(void);
//! Instance Declaration for sd_mmc_removal Slot 1
extern bool sd_mmc_removal_1(void);

//! @}


#if ACCESS_USB == true

/*! \name MEM <-> USB Interface
 */
//! @{

/*! \brief Transfers data from the memory to USB.
 *
 * \param slot SD/MMC Slot Card Selected.
 * \param addr      Address of first memory sector to read.
 * \param nb_sector Number of sectors to transfer.
 *
 * \return Status.
 */
extern Ctrl_status sd_mmc_usb_read_10(uint8_t slot,uint32_t addr, uint16_t nb_sector);
//! Instance Declaration for sd_mmc_usb_read_10 Slot O
extern Ctrl_status sd_mmc_usb_read_10_0(uint32_t addr, uint16_t nb_sector);
//! Instance Declaration for sd_mmc_usb_read_10 Slot 1
extern Ctrl_status sd_mmc_usb_read_10_1(uint32_t addr, uint16_t nb_sector);

/*! \brief Transfers data from USB to the memory.
 *
 * \param slot SD/MMC Slot Card Selected.
 * \param addr      Address of first memory sector to write.
 * \param nb_sector Number of sectors to transfer.
 *
 * \return Status.
 */
extern Ctrl_status sd_mmc_usb_write_10(uint8_t slot,uint32_t addr, uint16_t nb_sector);
//! Instance Declaration for sd_mmc_usb_write_10 Slot O
extern Ctrl_status sd_mmc_usb_write_10_0(uint32_t addr, uint16_t nb_sector);
//! Instance Declaration for sd_mmc_usb_write_10 Slot 1
extern Ctrl_status sd_mmc_usb_write_10_1(uint32_t addr, uint16_t nb_sector);

//! @}

#endif


#if ACCESS_MEM_TO_RAM == true

/*! \name MEM <-> RAM Interface
 */
//! @{

/*! \brief Copies 1 data sector from the memory to RAM.
 *
 * \param slot SD/MMC Slot Card Selected.
 * \param addr  Address of first memory sector to read.
 * \param ram   Pointer to RAM buffer to write.
 *
 * \return Status.
 */
extern Ctrl_status sd_mmc_mem_2_ram(uint8_t slot, uint32_t addr, void *ram);
//! Instance Declaration for sd_mmc_mem_2_ram Slot O
extern Ctrl_status sd_mmc_mem_2_ram_0(uint32_t addr, void *ram);
//! Instance Declaration for sd_mmc_mem_2_ram Slot 1
extern Ctrl_status sd_mmc_mem_2_ram_1(uint32_t addr, void *ram);

/*! \brief Copies 1 data sector from RAM to the memory.
 *
 * \param slot SD/MMC Slot Card Selected.
 * \param addr  Address of first memory sector to write.
 * \param ram   Pointer to RAM buffer to read.
 *
 * \return Status.
 */
extern Ctrl_status sd_mmc_ram_2_mem(uint8_t slot, uint32_t addr, const void *ram);
//! Instance Declaration for sd_mmc_mem_2_ram Slot O
extern Ctrl_status sd_mmc_ram_2_mem_0(uint32_t addr, const void *ram);
//! Instance Declaration for sd_mmc_mem_2_ram Slot 1
extern Ctrl_status sd_mmc_ram_2_mem_1(uint32_t addr, const void *ram);

//! @}

#endif
#endif

//! @}

#endif // _SD_MMC_MEM_H_
