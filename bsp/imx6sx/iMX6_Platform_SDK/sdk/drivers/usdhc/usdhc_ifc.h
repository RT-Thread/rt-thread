/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//!@addtogroup diag_usdhc
//!@{

/*!
 * @file usdhc_ifc.h
 * @brief uSDHC driver public interface. 
 */

#ifndef __USDHC_IFC_H__
#define __USDHC_IFC_H__

#include "sdk.h"
#include "registers/regsusdhc.h"

//////////////////////////////////////////////////////////////////////////////
// Definitions
/////////////////////////////////////////////////////////////////////////////

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef FAIL
#define FAIL 1
#endif

//! @brief boot part
typedef enum {
    EMMC_PART_USER,
    EMMC_PART_BOOT1,
    EMMC_PART_BOOT2
} emmc_part_e;

//! @brief eMMC bus width
typedef enum {
    EMMC_BOOT_SDR1,
    EMMC_BOOT_SDR4,
    EMMC_BOOT_SDR8,
    EMMC_BOOT_DDR4,
    EMMC_BOOT_DDR8
} emmc_bus_width_e;

//////////////////////////////////////////////////////////////////////////////////
// API
//////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif
/*!
 * @brief Set Card access mode
 *
 * @param sdma Whether to enable ADMA when read/write from/to card.
 *      If enabled, then use ADMA for transfer, or else, use polling IO.
 * @param intr Whether use interrupt to indicate end of transfer
 *      If enabled, will attach the status to interrupt, or else, poll the status.
 */
extern void set_card_access_mode(uint32_t sdma, uint32_t intr);

/*!
 * @brief Returns whether ADMA mode is currently enabled.
 */
extern uint32_t read_usdhc_adma_mode();

/*!
 * @brief Returns whether interrupt mode is currently enabled.
 */
extern uint32_t read_usdhc_intr_mode(); 

/*!
 * @brief Initialize usdhc controller and card inserted
 *
 * @param instance     Instance number of the uSDHC module.
 * @param bus_width    Bus width that card would be accessed: 1 bit, 4 bits, 8 bits(MMC only)
 * 
 * @return             0 if successful; 1 otherwise
 */
extern int card_init(uint32_t instance, int bus_width);
/*!
 * @brief Read data from card
 * 
 * @param   instance       Instance number of the uSDHC module.
 * @param   dst_ptr        Buffer to store data read
 * @param   length         Size in bytes of data to be read
 * @param   offset         Which sector in card should data be started to read
 *
 * @return   0 if successful; non-zero otherwise 
*/
extern int card_data_read(uint32_t instance, int *dst_ptr,  int length, uint32_t offset);

/*!
 * @brief Write data to card
 * 
 * @param   instance       Instance number of the uSDHC module.
 * @param   src_ptr        Buffer that store the source data
 * @param   length         Size in bytes of data to be written
 * @param   offset         Which sector in card should data be started to written
 *
 * @return  0 if successful; non-zero otherwise 
*/
extern int card_data_write(uint32_t instance, int *src_ptr, int length, int offset);

/*!
 * @brief Read the data transfer status(only in interrupt mode)
 * 
 * @param   instance       Instance number of the uSDHC module.
 * @param   status         Store the readback status. 0: busy, 1: success, 2: error
 *
 * @return 0 if successful; non-zero otherwise
 */
extern int card_xfer_result(uint32_t instance, int *status);

/*!
 * @brief Wait for the transfer complete. It covers the interrupt mode, DMA mode and PIO mode
 *
 * @param instance     Instance number of the uSDHC module.
 * 
 * @return             0 if successful; 1 otherwise
 */
extern int card_wait_xfer_done(uint32_t instance);

/*!
 * eMMC specific functions
 */
 
/*!
 * @brief Initialize the eMMC card
 * 
 * @param   instance     Instance number of the uSDHC module.
 *
 * @return 0 if successful; non-zero otherwise
 */ 
extern int card_emmc_init(uint32_t instance);

/*!
 * @brief Print out configuration information
 * 
 * @param   instance     Instance number of the uSDHC module.
 *
 * @return 0 if successful; non-zero otherwise
 */ 
extern void emmc_print_cfg_info(uint32_t instance);

/*!
 * @brief Acknowledge the boot 
 * 
 * @param   instance     Instance number of the uSDHC module.
 *
 * @return 0 if successful; non-zero otherwise
 */ 
extern int mmc_set_boot_ack(uint32_t instance, int enable);

/*!
 * @brief Set partition
 * 
 * @param   instance     Instance number of the uSDHC module.
 *
 * @return 0 if successful; non-zero otherwise
 */ 
extern int mmc_set_boot_partition(uint32_t instance, emmc_part_e part);

/*!
 * @brief Set bus width
 * 
 * @param   instance     Instance number of the uSDHC module.
 *
 * @return 0 if successful; non-zero otherwise
 */ 
extern int mmc_set_boot_bus_width(uint32_t instance, emmc_bus_width_e width);

//! @name Board support functions
//!
//! These functions are called by the driver in order to factor out board
//! specific functionality. They must be defined by the board support
//! library or the application.
//@{
//! @brief Configure IOMUX for the USDHC driver.
void usdhc_iomux_config(int instance);
//@}

#if defined (__cplusplus)
}
#endif

//! @}
#endif  /*__USDHC_IFC_H__ */ 
/////////////////////////////////////////////////////////////////////////////////
// EOF
/////////////////////////////////////////////////////////////////////////////////
