/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**@file
 *
 * @defgroup nrf_bootloader_info Bootloader Information
 * @{
 * @ingroup nrf_bootloader
 */

#ifndef NRF_BOOTLOADER_INFO_H__
#define NRF_BOOTLOADER_INFO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "app_util.h"
#include "nrf.h"
#include "nrf_mbr.h"

/** @brief Macro for getting the start address of the bootloader image.
 *
 * The macro is not a compile time symbol. It cannot be used as a
 * constant expression, for example, inside a static assert or linker script
 * at-placement.
 */
#ifndef BOOTLOADER_START_ADDR
#if (__LINT__ == 1)
    #define BOOTLOADER_START_ADDR (0x3AC00)
#elif defined(CODE_START)
    #define BOOTLOADER_START_ADDR (CODE_START)
#else
    #error Not a valid compiler/linker for BOOTLOADER_START_ADDR.
#endif
#endif


/** @brief Macro for getting the size of the bootloader image.
 */
#ifndef BOOTLOADER_SIZE
#if (__LINT__ == 1)
    #define BOOTLOADER_SIZE        (0x6000)
#elif defined ( NRF51 )
    #define BOOTLOADER_SIZE (BOOTLOADER_SETTINGS_ADDRESS - BOOTLOADER_START_ADDR)
#elif defined( NRF52_SERIES )
    #define BOOTLOADER_SIZE (NRF_MBR_PARAMS_PAGE_ADDRESS - BOOTLOADER_START_ADDR)
#endif
#endif


/**
 * @brief Location of the pointer to the start of the bootloader.
 *
 * See also @c BOOTLOADER_ADDRESS in @c app_util.h.
 */
#define NRF_UICR_BOOTLOADER_START_ADDRESS       (MBR_BOOTLOADER_ADDR)


// The following macros are for accessing the SoftDevice information structure,
// which is found inside the SoftDevice binary.

/** @brief Macro for converting an offset inside the SoftDevice information struct to an absolute address.
 */
#define SD_INFO_ABS_OFFSET_GET(baseaddr, offset) ((baseaddr) + (SOFTDEVICE_INFO_STRUCT_OFFSET) + (offset))

/** @brief Macros for reading a byte or a word at a particular offset inside a SoftDevice information struct.
 *         Use MBR_SIZE as baseaddr when the SoftDevice is installed just above the MBR (the usual case).
 */
#define SD_OFFSET_GET_UINT32(baseaddr, offset) (*((uint32_t *) SD_INFO_ABS_OFFSET_GET(baseaddr, offset)))
#define SD_OFFSET_GET_UINT16(baseaddr, offset) (*((uint16_t *) SD_INFO_ABS_OFFSET_GET(baseaddr, offset)))
#define SD_OFFSET_GET_UINT8(baseaddr, offset)  (*((uint8_t *)  SD_INFO_ABS_OFFSET_GET(baseaddr, offset)))


#if defined(BLE_STACK_SUPPORT_REQD) || defined(ANT_STACK_SUPPORT_REQD)
#include "nrf_sdm.h"
#else
/** @brief The offset inside the SoftDevice at which the information struct is placed.
 *         To see the layout of the information struct, see the SoftDevice specification.
 */
#define SOFTDEVICE_INFO_STRUCT_OFFSET (0x2000)

#define SD_INFO_STRUCT_SIZE(baseaddr) SD_OFFSET_GET_UINT8(baseaddr,  0x00)

/** @brief Macro for reading the size of a SoftDevice at a given base address.
 */
#ifndef SD_SIZE_GET
#define SD_SIZE_GET(baseaddr)         SD_OFFSET_GET_UINT32(baseaddr, 0x08)
#endif

/** @brief Macro for reading the version of a SoftDevice at a given base address.
 *         This expression checks the length of the information struct to see if the version is present.
 *         The version number is constructed like this:
 *             major_version * 1000000 + minor_version * 1000 + bugfix_version
 */
#ifndef SD_VERSION_GET
#define SD_VERSION_GET(baseaddr)    ((SD_INFO_STRUCT_SIZE(baseaddr) > (0x14)) \
                                    ? SD_OFFSET_GET_UINT32(baseaddr, 0x14)    \
                                    : 0)
#endif
#endif


/** @brief Macro for reading the magic number of a SoftDevice at a given base address.
 */
#ifndef SD_MAGIC_NUMBER_GET
#define SD_MAGIC_NUMBER_GET(baseaddr) SD_OFFSET_GET_UINT32(baseaddr, 0x04)
#endif

/** @brief Macro for getting the absolute address of the magic number.
 */
#define SD_MAGIC_NUMBER_ABS_OFFSET_GET(baseaddr) SD_INFO_ABS_OFFSET_GET(baseaddr, 0x04)

/** @brief The number present at a specific location in all SoftDevices.
 */
#define SD_MAGIC_NUMBER ((uint32_t)0x51B1E5DB)

/** @brief Whether a SoftDevice is at its regular location.
 */
#ifndef SD_PRESENT
#define SD_PRESENT ((SD_MAGIC_NUMBER_GET(MBR_SIZE)) == (SD_MAGIC_NUMBER))
#endif

/** @brief The multiplier for the major version of the SoftDevice. See \ref SD_VERSION_GET
 */
#define SD_MAJOR_VERSION_MULTIPLIER (1000000)

/** @brief Read the major version of the SoftDevice from the raw version number. See \ref SD_VERSION_GET.
 */
#define SD_MAJOR_VERSION_EXTRACT(raw_version) ((raw_version)/SD_MAJOR_VERSION_MULTIPLIER)


#define BOOTLOADER_DFU_GPREGRET_MASK            (0xF8)      /**< Mask for GPGPREGRET bits used for the magic pattern written to GPREGRET register to signal between main app and DFU. */
#define BOOTLOADER_DFU_GPREGRET                 (0xB0)      /**< Magic pattern written to GPREGRET register to signal between main app and DFU. The 3 lower bits are assumed to be used for signalling purposes.*/
#define BOOTLOADER_DFU_START_BIT_MASK           (0x01)      /**< Bit mask to signal from main application to enter DFU mode using a buttonless service. */

#define BOOTLOADER_DFU_GPREGRET2_MASK           (0xF8)      /**< Mask for GPGPREGRET2 bits used for the magic pattern written to GPREGRET2 register to signal between main app and DFU. */
#define BOOTLOADER_DFU_GPREGRET2                (0xA8)      /**< Magic pattern written to GPREGRET2 register to signal between main app and DFU. The 3 lower bits are assumed to be used for signalling purposes.*/
#define BOOTLOADER_DFU_SKIP_CRC_BIT_MASK        (0x01)      /**< Bit mask to signal from main application that CRC-check is not needed for image verification. */


#define BOOTLOADER_DFU_START    (BOOTLOADER_DFU_GPREGRET | BOOTLOADER_DFU_START_BIT_MASK)      /**< Magic number to signal that bootloader should enter DFU mode because of signal from Buttonless DFU in main app.*/
#define BOOTLOADER_DFU_SKIP_CRC (BOOTLOADER_DFU_GPREGRET2 | BOOTLOADER_DFU_SKIP_CRC_BIT_MASK)  /**< Magic number to signal that CRC can be skipped due to low power modes.*/


/** @brief Macro based on @c NRF_DFU_DEBUG_VERSION that can be checked for true/false instead of defined/not defined.
 */
#ifndef NRF_DFU_DEBUG
#ifdef NRF_DFU_DEBUG_VERSION
#define NRF_DFU_DEBUG 1
#else
#define NRF_DFU_DEBUG 0
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif // #ifndef NRF_BOOTLOADER_INFO_H__
/** @} */
