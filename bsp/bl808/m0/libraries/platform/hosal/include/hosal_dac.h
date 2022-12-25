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

#ifndef __HOSAL_DAC_H_
#define __HOSAL_DAC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "hosal_dma.h"

/** @addtogroup hosal_dac DAC
 *  HOSAL DAC API
 *
 *  @{
 */

/**
 * @brief hosal dac callback
 *
 * @param[in] arg Set the custom parameters specified when the callback function is set
 *
 */
typedef void (*hosal_dac_cb_t)(void *arg);

/**
 * @brief This struct define dac config args
 */
typedef struct {
    uint8_t  dma_enable;        /**< @brief 1: use dma, 0: no dma */
    uint32_t  pin;              /**< @brief dac pin */
    uint32_t  freq;             /**< @brief dac freq */
} hosal_dac_config_t;

/**
 * @brief This struct define dac device type
 */
typedef struct {
    uint8_t  port;                    /**< @brief dac id */
    hosal_dac_config_t config;        /**< @brief dac config */
    hosal_dac_cb_t cb;                /**< @brief dma callback */
    hosal_dma_chan_t dma_chan;        /**< @brief dac dma channel */
    void    *arg;                     /**< @brief arg data */
    void    *priv;                    /**< @brief priv data */
} hosal_dac_dev_t;

/**
 * @brief Initialises an dac interface
 *
 * @param[in]  dac  the interface which should be initialised
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_dac_init(hosal_dac_dev_t *dac);

/**
 * @brief De-initialises an dac interface, Turns off an dac hardware interface
 *
 * @param[in]  dac  the interface which should be de-initialised
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_dac_finalize(hosal_dac_dev_t *dac);

/**
 * @brief Start output dac （no DMA mode）
 *
 * @param[in]   dac      the interface which should be started
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_dac_start(hosal_dac_dev_t *dac);

/**
 * @brief Stop output dac
 *
 * @param[in]   dac      the interface which should be stopped
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_dac_stop(hosal_dac_dev_t *dac);

/**
 * @brief Output a value to an dac interface
 *
 * @param[in]   dac      the interface to set value
 *
 * @param[in]   data     the value to output, output unit: μV 
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_dac_set_value(hosal_dac_dev_t *dac, uint32_t data);

/**
 * @brief Returns the last data output value of the selected dac channel
 *
 * @param[in]   dac      the interface to get value
 *
 * @return  dac output value, output unit: μV
 */
int hosal_dac_get_value(hosal_dac_dev_t *dac);

/**
 *  @brief DAC cb register
 *
 * @param [in]   dac          the DAC interface
 * @param [in]   callback     callback handler
 * @param [in]   arg          callback arg
 * 
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_dac_dma_cb_reg(hosal_dac_dev_t *dac, hosal_dac_cb_t callback, void *arg);

/**
 * @brief DAC use DMA mode
 *   
 * @param[in]   adc           the DAC interface
 * @param[in]   data          dac data buffer
 * @param[in]   size          data buffer size
 *        
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_dac_dma_start(hosal_dac_dev_t *dac, uint32_t *data, uint32_t size);

/**
 * @brief Stop output dac
 *
 * @param[in]   dac      the interface which should be stopped
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_dac_dma_stop(hosal_dac_dev_t *dac);

#ifdef __cplusplus
}
#endif

#endif /* __HOSAL_DAC_H_ */

/* end of file */


