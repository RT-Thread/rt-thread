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
#ifndef __HOSAL_PWM_H__
#define __HOSAL_PWM_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup hosal_pwm PWM
 *  HOSAL PWM API
 *
 *  @{
 */

#include <stdint.h>
/**
 * @brief pwm config struct
 *
 */
typedef struct {
    uint8_t    pin;        /**< pwm pin  */
    uint32_t   duty_cycle; /**< the pwm duty_cycle 0 ~ 10000(0 ~ 100%)*/
    uint32_t   freq;       /**< the pwm freq,range is between 0 and 40M */
} hosal_pwm_config_t;

/**
 * @brief pwm dev struct
 *
 */
typedef struct {
    uint8_t       port;         /**< pwm port */
    hosal_pwm_config_t  config; /**< pwm config */
    void         *priv;         /**< priv data */
} hosal_pwm_dev_t;

/**
 * @brief Initialises a PWM pin
 *
 * @param[in]  pwm  the PWM device
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int hosal_pwm_init(hosal_pwm_dev_t *pwm);

/**
 * @brief Starts Pulse-Width Modulation signal output on a PWM pin
 *
 * @param[in]  pwm  the PWM device
 *
 * @return  
 *     - 0 : success
 *     - other : fail 
 */
int hosal_pwm_start(hosal_pwm_dev_t *pwm);

/**
 * @brief Stops output on a PWM pin
 *
 * @param[in]  pwm  the PWM device
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int hosal_pwm_stop(hosal_pwm_dev_t *pwm);

/**
 * @change the para of pwm
 *
 * @param[in]  pwm   the PWM device
 * @param[in]  para  the para of pwm
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int hosal_pwm_para_chg(hosal_pwm_dev_t *pwm, hosal_pwm_config_t para);

/**
 * @brief update PWM frequency
 *
 * @param[in]  pwm   the PWM device
 * @param[in]  freq  the PWM frequency (0~40M under limited duty)
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int hosal_pwm_freq_set(hosal_pwm_dev_t *pwm, uint32_t freq);

/**
 * @brief get PWM frequency
 *
 * @param[in]  pwm   the PWM device
 * @param[out] p_freq  the pointer to memory frequency
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int hosal_pwm_freq_get(hosal_pwm_dev_t *pwm, uint32_t *p_freq);

/**
 * @brief set PWM duty
 *
 * @param[in]  pwm   the PWM device
 * @param[in]  duty        the PWM duty (original duty * 100)
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int hosal_pwm_duty_set(hosal_pwm_dev_t *pwm, uint32_t duty);

/**
 * @brief get PWM duty
 *
 * @param[in]  pwm   the PWM device
 * @param[out] p_duty  the pointer to memory duty(original duty * 100)
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int hosal_pwm_duty_get(hosal_pwm_dev_t *pwm, uint32_t *p_duty);

/**
 * @brief De-initialises an PWM interface, Turns off an PWM hardware interface
 *
 * @param[in]  pwm  the interface which should be de-initialised
 *
 * @return  
 *     -  0 : success
 *     - other: fail
 */
int hosal_pwm_finalize(hosal_pwm_dev_t *pwm);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* HAL_PWM_H */

