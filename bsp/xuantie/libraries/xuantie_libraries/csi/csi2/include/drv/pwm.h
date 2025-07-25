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
 * @file       drv/pwm.h
 * @brief      Header File for PWM Driver
 * @version    V1.0
 * @date       9. Oct 2020
 * @model      pwm
 ******************************************************************************/

#ifndef _DRV_PWM_H_
#define _DRV_PWM_H_

#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PWM_POLARITY_HIGH = 0U,                          ///< High level
    PWM_POLARITY_LOW                                 ///< Low level
} csi_pwm_polarity_t;

typedef enum {
    PWM_CAPTURE_POLARITY_POSEDGE = 0U,               ///< Posedge Edge
    PWM_CAPTURE_POLARITY_NEGEDGE,                    ///< Negedge Edge
    PWM_CAPTURE_POLARITY_BOTHEDGE                    ///< Both Edge
} csi_pwm_capture_polarity_t;

typedef enum {
    PWM_EVENT_CAPTURE_POSEDGE = 0U,                  ///< Capture Posedge Event
    PWM_EVENT_CAPTURE_NEGEDGE,                       ///< Capture Negedge Event
    PWM_EVENT_CAPTURE_BOTHEDGE,                      ///< Capture Bothedge Event
    PWM_EVENT_ERROR,                                 ///< Error
} csi_pwm_event_t;

typedef struct csi_pwm csi_pwm_t;

struct csi_pwm {
    csi_dev_t      dev;
    void (*callback)(csi_pwm_t *pwm, csi_pwm_event_t event, uint32_t ch, uint32_t time_us, void *arg);
    void           *arg;
    void           *priv;
};

/**
  \brief       Initialize PWM interface. Initializes the resources needed for the PWM interface
  \param[in]   pwm    Handle to operate
  \param[in]   idx    PWM idx
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_pwm_init(csi_pwm_t *pwm, uint32_t idx);

/**
  \brief       De-initialize PWM interface. Stops operation and releases the software resources used by the interface
  \param[in]   pwm    Handle to operate
  \return      None
*/
void csi_pwm_uninit(csi_pwm_t *pwm);

/**
  \brief       Config PWM out mode
  \param[in]   pwm               Handle to operate
  \param[in]   channel           Channel num
  \param[in]   period_us         The PWM period in us
  \param[in]   pulse_width_us    The PMW pulse width in us
  \param[in]   polarity          The PWM polarity \ref csi_pwm_polarity_t
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_pwm_out_config(csi_pwm_t *pwm,
                               uint32_t channel,
                               uint32_t period_us,
                               uint32_t pulse_width_us,
                               csi_pwm_polarity_t polarity);

/**
  \brief       Start generate PWM signal
  \param[in]   pwm        Handle to operate
  \param[in]   channel    Channel num
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_pwm_out_start(csi_pwm_t *pwm, uint32_t channel);

/**
  \brief       Stop generate PWM signal
  \param[in]   pwm        Handle to operate
  \param[in]   channel    Channel num
  \return      None
*/
void csi_pwm_out_stop(csi_pwm_t *pwm, uint32_t channel);

/**
  \brief       Config PWM capture mode
  \param[in]   pwm         Handle to operate
  \param[in]   channel     Channel num
  \param[in]   polarity    PWM capture polarity \ref csi_pwm_capture_polarity_t
  \param[in]   count       PWM capture polarity count
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_pwm_capture_config(csi_pwm_t *pwm,
                                   uint32_t channel,
                                   csi_pwm_capture_polarity_t polarity,
                                   uint32_t count);

/**
  \brief       Start PWM capture
  \param[in]   pwm        Handle to operate
  \param[in]   channel    Channel num
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_pwm_capture_start(csi_pwm_t *pwm, uint32_t channel);

/**
  \brief       Stop PWM capture
  \param[in]   pwm        Handle to operate
  \param[in]   channel    Channel num
  \return      None
*/
void csi_pwm_capture_stop(csi_pwm_t *pwm, uint32_t channel);

/**
  \brief       Attach PWM callback
  \param[in]   pwm         Handle to operate
  \param[in]   callback    Callback func
  \param[in]   arg         Callback's param
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_pwm_attach_callback(csi_pwm_t *pwm, void *callback, void *arg);

/**
  \brief       Detach PWM callback
  \param[in]   pwm    Handle to operate
  \return      None
*/
void csi_pwm_detach_callback(csi_pwm_t *pwm);

/**
  \brief       Enable PWM power manage
  \param[in]   pwm    Handle to operate
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_pwm_enable_pm(csi_pwm_t *pwm);

/**
  \brief       Disable PWM power manage
  \param[in]   pwm    Handle to operate
  \return      None
*/
void csi_pwm_disable_pm(csi_pwm_t *pwm);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_PWM_H_ */
