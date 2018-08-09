/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
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

#ifndef NFC_FIXES_H__
#define NFC_FIXES_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @file
 * @defgroup nfc_fixes NFC fixes and workarounds
 * @{
 * @ingroup nfc_t4t
 * @brief @tagAPI52 Fixes for hardware-related anomalies.
 *
 * If you are using PCA10040 (part of nRF52 Development Kit), 
 * you must define the macro HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND in order to apply 
 * workarounds for the following anomalies:
 * - 79. NFCT: A false EVENTS_FIELDDETECTED event occurs after the field is lost.
 * - 116. NFCT does not release HFCLK when switching from ACTIVATED to SENSE mode.
 *
 * If you are using PCA10056 Engineering A (part of nRF52840 Development Kit), 
 * you must define the macro HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND in order to apply 
 * workarounds for the following anomalies:
 * - 98. NFCT: The NFCT is not able to communicate with the peer.
 * - 116. NFCT does not release HFCLK when switching from ACTIVATED to SENSE mode.
 * - 144. NFCT: Not optimal NFC performance
 *
 * If you are using PCA10056 Engineering B or C (part of nRF52840 Development Kit), 
 * you must define the macro HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND in order to apply 
 * workarounds for the following anomalies:
 * - 190. NFCT: Event FIELDDETECTED may be generated too early.
 *
 * The use of implemented workarounds for PCA10056 are determined at the runtime and depends 
 * on the chip variant.
 *
 * The current code contains a patch for anomaly 25 (NFCT: Reset value of 
 * SENSRES register is incorrect), so that it now works on Windows Phone.
 */
 
#ifdef BOARD_PCA10040           // assume nRF52832 chip in IC rev. Engineering B or Engineering C
    #define HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND
#elif defined(BOARD_PCA10056)   // assume nRF52840 chip in IC rev. Engineering A, B or C
    #define HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND
#endif

/**
 * @brief Internal auxiliary function to check if the program is running on NRF52840 chip
 * @retval true  It is NRF52480 chip
 * @retval false It is other chip
 */
static inline bool type_52840_check(void)
{
    return ((((*(uint32_t *)0xF0000FE0) & 0xFF) == 0x08) &&
        (((*(uint32_t *)0xF0000FE4) & 0x0F) == 0x0));
}

/**
 * @brief Internal auxiliary function to check if the program is running on first sample of
 *        NRF52840 chip
 * @retval true  It is NRF52480 chip and it is first sample version
 * @retval false It is other chip
 */
static inline bool type_52840_sample_check(void)
{
    return ( type_52840_check() &&
               ( ((*(uint32_t *)0xF0000FE8) & 0xF0) == 0x00 ) &&
               ( ((*(uint32_t *)0xF0000FEC) & 0xF0) == 0x00 ) );
}

/**
 * @brief Internal auxiliary function to check if the program is running on final version of
 *        NRF52840 chip
 * @retval true  It is NRF52480 chip and it is final version
 * @retval false It is other chip
 */
static inline bool type_52840_final_check(void)
{
    return ( type_52840_check() &&
              ( ( ((*(uint32_t *)0xF0000FE8) & 0xF0) != 0x00 ) ||
                ( ((*(uint32_t *)0xF0000FEC) & 0xF0) != 0x00 ) ));
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* NFC_FIXES_H__ */

