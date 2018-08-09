/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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
#ifndef NRF_BOOTLOADER_WDT_H
#define NRF_BOOTLOADER_WDT_H

/**@file
 *
 * @defgroup nrf_bootloader_wdt  Automated feeding of the watchdog
 * @{
 * @ingroup  nrf_bootloader
 * @brief Module that keeps the WDT from timing out if the WDT has been started in the application.
 */

#include "sdk_errors.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Function for checking whether the WDT peripheral is started and for getting its configuration.
 *
 * The module uses app_timer to start regular feeding of the watchdog. Timer interval
 * is chosen based on watchdog settings. When @ref nrf_bootloader_wdt_feed is called, internal
 * feeding is stopped assuming that the application takes responsibity of watchdog feeding.
 * However, if @ref NRF_BL_WDT_MAX_SCHEDULER_LATENCY_MS or the watchdog is configured to
 * run during sleep, then internal feeding (from app_timer handler context) is kept active.
 */
void nrf_bootloader_wdt_init(void);


/**
 * @brief Function for feeding the watchdog (if active).
 */
void nrf_bootloader_wdt_feed(void);

#ifdef __cplusplus
}
#endif

/** @} */

#endif //NRF_BOOTLOADER_WDT_H
