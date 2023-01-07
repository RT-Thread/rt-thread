/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef HAL_WDG_H
#define HAL_WDG_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup hosal_wdg WATCHDOG 
 *  HOSAL WATCHDOG API
 *
 *  @{
 */

#include <stdint.h>

/**
 * @brief wdg config struct
 *
 */
typedef struct {
    uint32_t timeout; /*!< Watchdag timeout in ms*/
} hosal_wdg_config_t;

/**
 * @brief wdg dev struct
 *
 */
typedef struct {
    uint8_t       port;   /**< wdg port */
    hosal_wdg_config_t  config; /**< wdg config */
    void         *priv;   /**< priv data */
} hosal_wdg_dev_t;

/**
 * @brief This function will initialize the on board CPU hardware watch dog
 *
 * @param[in]  wdg  the watch dog device
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int hosal_wdg_init(hosal_wdg_dev_t *wdg);

/**
 * @brief Reload watchdog counter.
 *
 * @param[in]  wdg  the watch dog device
 */
void hosal_wdg_reload(hosal_wdg_dev_t *wdg);

/**
 * @brief This function performs any platform-specific cleanup needed for hardware watch dog.
 *
 * @param[in]  wdg  the watch dog device
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int hosal_wdg_finalize(hosal_wdg_dev_t *wdg);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* HAL_WDG_H */

