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

#ifndef __HOSAL_ADC_H_
#define __HOSAL_ADC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "hosal_dma.h"

/** @addtogroup hosal_adc ADC
 *  HOSAL ADC API
 *
 *  @{
 */

#define HOSAL_WAIT_FOREVER        0xFFFFFFFFU  /**< @brief Define the wait forever timeout macro */

/**
 * @brief ADC interrupt events
 */
typedef enum __ADC_INT_EVENTS__{
    HOSAL_ADC_INT_OV,         /**< @brief Overrun error */
    HOSAL_ADC_INT_EOS,        /**< @brief End of sample */
    HOSAL_ADC_INT_DMA_TRH,    /**< @brief DMA transceive half */
    HOSAL_ADC_INT_DMA_TRC,    /**< @brief DMA transceive complete */
    HOSAL_ADC_INT_DMA_TRE,    /**< @briefDMA transceive error */
} hosal_adc_event_t;

/**
 * @brief ADC data type
 */
typedef struct {
    uint32_t size;  /**< @brief sampled data size */
    void *data;     /**< @brief sampled data, aligned with resolution (until the next power of two) */
} hosal_adc_data_t;

/**
 * @brief ADC MODE type
 */
typedef enum {
    HOSAL_ADC_ONE_SHOT,       /**< @brief Single time sampling */
    HOSAL_ADC_CONTINUE        /**< @brief Continuous sampling */
} hosal_adc_sample_mode_t;

/**
 * @brief Define ADC config args
 */
typedef struct {
    uint32_t sampling_freq;             /**< @brief sampling frequency in Hz */
    uint32_t pin;                        /**< @brief adc pin */
    hosal_adc_sample_mode_t mode;       /**< @brief adc sampling mode */
    uint8_t sample_resolution;          /**< @brief adc sampling resolution */
} hosal_adc_config_t;

/**
 * @brief ADC interrupt function
 *
 *@param[in] parg  Set the custom parameters specified
 *
 */
typedef void (*hosal_adc_irq_t)(void *parg);

/**
 * @brief Define ADC dev hosal handle
 */
typedef struct {
    uint8_t port;                    /**< @brief adc port */
    hosal_adc_config_t config;        /**< @brief adc config */
    hosal_dma_chan_t dma_chan;        /**< @brief adc dma channel */ 
    hosal_adc_irq_t cb;               /**< @brief adc callback */
    void *p_arg;                      /**< @brief p_arg data */
    void *priv;                       /**< @brief priv data */
} hosal_adc_dev_t;

/**
 * @brief ADC interrupt callback
 *
 * @param[in] parg  Set the custom parameters specified when the callback function is set
 *
 */
typedef void (*hosal_adc_cb_t)(hosal_adc_event_t event, void *data, uint32_t size);

/**
 * @brief Initialises an ADC interface, Prepares an ADC hardware interface for sampling
 *
 * @param[in]  adc  the interface which should be initialised
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_adc_init(hosal_adc_dev_t *adc);

/**
 * @brief Add a channel to an ADC interface
 *
 * @param[in]   adc      the interface which should be sampled
 * @param[in]   channel  adc channel
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_adc_add_channel(hosal_adc_dev_t *adc, uint32_t channel);

/**
 * @brief Remove a channel to an ADC interface
 *
 * @param[in]   adc      the interface which should be sampled
 * @param[in]   channel  adc channel
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_adc_remove_channel(hosal_adc_dev_t *adc, uint32_t channel);

/**
 * @brief Takes adc device handle from an ADC interface
 *
 * @return  
 *	- other  get adc device success
 *	- NULL   if an error occurred with any step
 */
hosal_adc_dev_t *hosal_adc_device_get(void);

/**
 * @brief Takes a single sample from an ADC interface
 *
 * @param[in]   adc      the interface which should be sampled
 * @param[in]   channel  adc channel
 * @param[in]   timeout  ms timeout
 *
 * @return  
 *	- other  get adc data success
 *	- -1     if an error occurred with any step
 */
int hosal_adc_value_get(hosal_adc_dev_t *adc, uint32_t channel, uint32_t timeout);

/**
 * @brief Takes a tsen sample from an ADC interface
 *
 * @param[in]   adc      the interface which should be sampled
 *
 * @return  
 *	- other  get adc data success
 *	- -1     if an error occurred with any step
 */
int hosal_adc_tsen_value_get(hosal_adc_dev_t *adc);

/**
 * @brief ADC sampling cb register
 *
 * @param [in]   adc          the ADC interface
 * @param [in]   cb           Non-zero pointer is the sample callback handler
 *                            NULL pointer for send unregister operation
 *                            adc in cb must be the same pointer with adc pointer passed to hosal_adc_sample_cb_reg
 *                            driver must notify upper layer by calling cb if ADC data is ready in HW or memory(DMA)
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_adc_sample_cb_reg(hosal_adc_dev_t *adc, hosal_adc_cb_t cb);

/**
 * @brief ADC sampling start
 *
 * @param[in]   adc             the ADC interface
 * @param[in]   data            adc data buffer
 * @param[in]   size            data buffer size aligned with resolution (until the next power of two)
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_adc_start(hosal_adc_dev_t *adc, void *data, uint32_t size);

/**
 * @brief ADC sampling stop
 *
 * @param[in]   adc             the ADC interface
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_adc_stop(hosal_adc_dev_t *adc);

/**
 * @brief De-initialises an ADC interface, Turns off an ADC hardware interface
 *
 * @param[in]  adc  the interface which should be de-initialised
 *
 * @return  
 *	- 0    on success
 *	- EIO  if an error occurred with any step
 */
int hosal_adc_finalize(hosal_adc_dev_t *adc);

#ifdef __cplusplus
}
#endif

#endif /* __HOSAL_ADC_H_ */

/* end of file */
