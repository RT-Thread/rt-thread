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
#ifndef HOSAL_TIMER_H
#define HOSAL_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup hal_timer TIMER
 *  timer hal API.
 *
 *  @{
 */

#include <stdint.h>

#define TIMER_RELOAD_PERIODIC 1 /**< timer reload automatic */
#define TIMER_RELOAD_ONCE     2 /**< timer reload once and need to reload manually */

typedef void (*hosal_timer_cb_t)(void *arg); /**< Define timer handle function type */

/**
 * Define timer config args 
 */
typedef struct {
    uint32_t          period;         /**< timer period, us */
    uint8_t           reload_mode;    /**< auto reload or not */
    hosal_timer_cb_t  cb;             /**< timer handle when expired */
    void              *arg;           /**< timer handle args */
} hosal_timer_config_t;

/** 
 * Define timer dev handle 
 */
typedef struct {
    int8_t                port;   /**< timer port */
    hosal_timer_config_t  config; /**< timer config */
    void                  *priv;   /**< priv data */
} hosal_timer_dev_t;

/**
 * init a hardware timer
 *
 * @param[in]  tim  timer device
 *
 * @return  
 *       - 0 : success 
 *       - other :error
 */
int hosal_timer_init(hosal_timer_dev_t *tim);

/**
 * start a hardware timer
 *
 * @param[in]  tim  timer device
 *
 * @return
 *       - 0 : success 
 *       - other : error
 */
int hosal_timer_start(hosal_timer_dev_t *tim);

/**
 * stop a hardware timer
 *
 * @param[in]  tim  timer device
 *
 * @return  none
 */
void hosal_timer_stop(hosal_timer_dev_t *tim);

/**
 * De-initialises an TIMER interface, Turns off an TIMER hardware interface
 *
 * @param[in]  tim  timer device
 *
 * @return  
 *       - 0 : success
 *       - other : error
 */
int hosal_timer_finalize(hosal_timer_dev_t *tim);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* HAL_TIMER_H */

