 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     drv/adc.h
 * @brief    Header File for ADC Driver
 * @version  V1.0
 * @date     08. Apr 2020
 * @model    adc
 ******************************************************************************/

#ifndef _DRV_ADC_H_
#define _DRV_ADC_H_

#include <stdint.h>
#include <stdbool.h>

#include <drv/common.h>
#include <drv/dma.h>

#ifdef __cplusplus
extern "C" {
#endif

/****** ADC Event *****/
typedef enum {
    ADC_EVENT_CONVERT_COMPLETE = 0,      ///< All data convert completed
    ADC_EVENT_CONVERT_HALF_DONE,         ///< Convert half done
    ADC_EVENT_ERROR                      ///< All errors including but not limited to what converted data has not been read before the new conversion result is load to the data register
} csi_adc_event_t;

typedef struct csi_adc csi_adc_t;
struct csi_adc {
    csi_dev_t                dev;        ///< Hw-device info
    void (*callback)(csi_adc_t *adc, csi_adc_event_t event, void *arg);  ///< User callback ,signaled by driver event
    void                    *arg;        ///< User private param ,passed to user callback
    uint32_t                *data;       ///< Data buf
    uint32_t                 num;        ///< Data size by word
    csi_dma_ch_t            *dma;        ///< Dma channel handle
    csi_error_t             (*start)(csi_adc_t *adc);  ///< Start function
    csi_error_t             (*stop)(csi_adc_t *adc);   ///< Stop function
    csi_state_t             state;       ///< ADC current state
    void                    *priv;
};

/**
  \brief       Initialize adc Interface. Initialize the resources needed for the adc interface
  \param[in]   adc    ADC handle to operate
  \param[in]   idx    ADC controller index
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_adc_init(csi_adc_t *adc, uint32_t idx);

/**
  \brief       De-initialize adc Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle    ADC handle to operate
  \return      None
*/
void csi_adc_uninit(csi_adc_t *adc);

/**
  \brief       Set adc receive buffer
  \param[in]   adc    ADC handle to operate
  \param[in]   num    The receive data length by word.
  \return     Error code \ref csi_error_t
*/
csi_error_t csi_adc_set_buffer(csi_adc_t *adc, uint32_t *data, uint32_t num);

/**
  \brief       Start adc
  \param[in]   handle    ADC handle to operate
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_adc_start(csi_adc_t *adc);

/**
  \brief       Enable dma or interrupt, and start adc conversion
  \param[in]   handle    ADC handle to operate
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_adc_start_async(csi_adc_t *adc);

/**
  \brief       Stop adc
  \param[in]   handle    ADC handle to operate
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_adc_stop(csi_adc_t *adc);

/**
  \brief       Disable dma or interrupt, and stop adc conversion
  \param[in]   handle    ADC handle to operate
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_adc_stop_async(csi_adc_t *adc);

/**
  \brief       ADC channel enable
  \param[in]   adc          ADC handle to operate
  \param[in]   ch_id        ADC channel id
  \param[in]   is_enable    true->enable, false->disable
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_adc_channel_enable(csi_adc_t *adc, uint8_t ch_id, bool is_enable);

/**
  \brief       Set the ADC sampling time for the selected channel
  \param[in]   adc          ADC handle to operate
  \param[in]   ch_id        ADC channel id
  \param[in]   clock_num    Channel sampling clock number
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_adc_channel_sampling_time(csi_adc_t *adc, uint8_t ch_id, uint16_t clock_num);

/**
  \brief       Set the ADC controller sampling time
  \param[in]   adc          ADC handle to operate
  \param[in]   clock_num    ADC controller sampling clock number
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_adc_sampling_time(csi_adc_t *adc, uint16_t clock_num);

/**
  \brief       Enable the continue mode of ADC
  \param[in]   adc          ADC handle to operate
  \param[in]   is_enable    true->enable, false->disable
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_adc_continue_mode(csi_adc_t *adc, bool is_enable);

/**
  \brief       Set ADC frequence division
  \param[in]   adc    ADC handle to operate
  \param[in]   div    The division of frequence
  \return      The actual config frequency
*/
uint32_t csi_adc_freq_div(csi_adc_t *adc, uint32_t div);

/**
  \brief       Receiving data from ADC receiver
  \param[in]   handle    ADC handle to operate
  \return      If read successful, this function shall return the result of convert value
               otherwise, the function shall return error code
*/
int32_t csi_adc_read(csi_adc_t *adc);

/**
  \brief       Get ADC state
  \param[in]   adc      ADC handle to operate
  \param[in]   state    ADC state
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_adc_get_state(csi_adc_t *adc, csi_state_t *state);

/**
  \brief       Attach the callback handler to adc
  \param[in]   adc         Operate handle
  \param[in]   callback    Callback function
  \param[in]   arg         User can define it by himself as callback's param
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_adc_attach_callback(csi_adc_t *adc, void *callback, void *arg);

/**
  \brief       Detach the callback handler
  \param[in]   adc    Operate handle
  \return      None
*/
void        csi_adc_detach_callback(csi_adc_t *adc);

/**
  \brief       Link DMA channel to adc device
  \param[in]   adc    ADC handle to operate
  \param[in]   dma    The DMA channel handle for send, when it is NULL means to unlink the channel
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_adc_link_dma(csi_adc_t *adc, csi_dma_ch_t *dma);

/**
  \brief       Enable adc low power mode
  \param[in]   adc    ADC handle to operate
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_adc_enable_pm(csi_adc_t *adc);

/**
  \brief       Disable adc low power mode
  \param[in]   adc    ADC handle to operate
  \return      None
*/
void csi_adc_disable_pm(csi_adc_t *adc);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_ADC_H_ */
