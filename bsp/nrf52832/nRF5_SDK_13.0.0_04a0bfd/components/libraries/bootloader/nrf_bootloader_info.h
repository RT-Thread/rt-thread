/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
 * @defgroup sdk_bootloader_info Information
 * @{
 * @ingroup sdk_bootloader
 */

#ifndef NRF_BOOTLOADER_INFO_H__
#define NRF_BOOTLOADER_INFO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "nrf.h"
#include "nrf_mbr.h"

#if defined(SOFTDEVICE_PRESENT)
#include "nrf_sdm.h"
#else
#include "nrf_mbr.h"
#endif

/** @brief External definitions of symbols for the start of the application image.
 */
#if (__LINT__ == 1)
    // No implementation
#elif defined ( __CC_ARM )
    extern uint32_t* Image$$ER_IROM1$$Base   __attribute__((used));
#elif defined ( __GNUC__ )
    extern uint32_t * __isr_vector;
#elif defined ( __ICCARM__ )
    extern void * __vector_table;
#else
    #error Not a valid compiler/linker for application image symbols.
#endif


/** @brief Macro for getting the start address of the application image.
 *
 * This macro is valid only when absolute placement is used for the application
 * image. The macro is not a compile time symbol. It cannot be used as a
 * constant expression, for example, inside a static assert or linker script
 * at-placement.
 */
#if (__LINT__ == 1)
    #define BOOTLOADER_START_ADDR        (0x3AC00)
#elif BOOTLOADER_START_ADDR
    // Bootloader start address is defined at project level
#elif defined (__CC_ARM)
    #define BOOTLOADER_START_ADDR        (uint32_t)&Image$$ER_IROM1$$Base
#elif defined (__GNUC__)
    #define BOOTLOADER_START_ADDR        (uint32_t)&__isr_vector
#elif defined (__ICCARM__)
    #define BOOTLOADER_START_ADDR        (uint32_t)&__vector_table
#else
    #error Not a valid compiler/linker for BOOTLOADER_START_ADDR.
#endif


/**
 * @brief Bootloader start address in UICR.
 *
 * Register location in UICR where the bootloader start address is stored.
 *
 * @note If the value at the given location is 0xFFFFFFFF, the bootloader address is not set.
 */
#define NRF_UICR_BOOTLOADER_START_ADDRESS       (NRF_UICR_BASE + 0x14)


#ifndef MAIN_APPLICATION_START_ADDR


#if defined(SOFTDEVICE_PRESENT)

/** @brief  Main application start address (if the project uses a SoftDevice).
 *
 * @note   The start address is equal to the end address of the SoftDevice.
 */
#define MAIN_APPLICATION_START_ADDR             (SD_SIZE_GET(MBR_SIZE))

#else
#define MAIN_APPLICATION_START_ADDR             MBR_SIZE
#endif // #ifdef SOFTDEVICE_PRESENT
#endif // #ifndef MAIN_APPLICATION_START_ADDR


#ifdef __cplusplus
}
#endif

#endif // #ifndef NRF_BOOTLOADER_INFO_H__
/** @} */
