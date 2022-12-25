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

//FIXME no BL808/BL606p header file including is Allowed here
#ifdef BL808
#include <bl808_pwm.h>
#include <bl808_glb.h>
#elif defined(BL606P)
#include <bl606p_pwm.h>
#include <bl606p_glb.h>
#else
#error "Use CHIP BL808/BL606P for this module"
#endif

#include "hosal_pwm.h"
#include "blog.h"


#define PWM_CHANNAL_MAX 4
#define PWM_XCLK_CLK 40000000
#define PWM_DUTY_MAX 10000


/**
 * Initialises a PWM pin
 *
 *
 * @param[in]  pwm  the PWM device
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hosal_pwm_init(hosal_pwm_dev_t *pwm)
{
    GLB_GPIO_Cfg_Type gpioCfg = {
        .gpioPin = 0,
        .gpioFun = GPIO_FUN_PWM0, //GPIO_FUN_PWM1
        .gpioMode = GPIO_MODE_OUTPUT,
        .pullType = GPIO_PULL_DOWN,
        .drive = 0,
        .smtCtrl = 1,
    };

    PWMx_CFG_Type pwmxCfg = {
        .clk = PWM_CLK_XCLK,
        .stopMode = PWM_STOP_GRACEFUL,
        .clkDiv = 1,
        .period = 0,
        .intPulseCnt = 0,
        .extPol = PWM_BREAK_Polarity_HIGH,
        .stpRept = DISABLE,
        .adcSrc = PWM_TRIGADC_SOURCE_NONE,
    };

    PWM_CHx_CFG_Type chxCfg = {
        .modP = PWM_MODE_ENABLE,
        .modN = PWM_MODE_ENABLE,
        .polP = PWM_POL_ACTIVE_HIGH,
        .polN = PWM_POL_ACTIVE_HIGH,
        .idlP = PWM_IDLE_STATE_INACTIVE,
        .idlN = PWM_IDLE_STATE_INACTIVE,
        .brkP = PWM_BREAK_STATE_INACTIVE,
        .brkN = PWM_BREAK_STATE_INACTIVE,
        .thresholdL = 0,
        .thresholdH = 0,
        .dtg = 0,
    };

    if (NULL == pwm || (pwm->port != PWM0_ID && pwm->port != PWM1_ID)) {
        blog_error("arg error.\r\n");
        return -1;
    }

    gpioCfg.gpioPin = pwm->config.pin;
    if (pwm->port == PWM0_ID)
       gpioCfg.gpioFun = GPIO_FUN_PWM0;
    else if (pwm->port == PWM1_ID)
       gpioCfg.gpioFun = GPIO_FUN_PWM1;
    GLB_GPIO_Init(&gpioCfg);

    PWMx_Disable(pwm->port);
    pwmxCfg.period = PWM_XCLK_CLK/pwm->config.freq;
    PWMx_Init(pwm->port, &pwmxCfg);
    chxCfg.thresholdL = 0;
    chxCfg.thresholdH = (PWM_XCLK_CLK/pwm->config.freq)*pwm->config.duty_cycle/PWM_DUTY_MAX;
    PWM_Channelx_Init(pwm->port, pwm->config.pin%PWM_CHANNAL_MAX, &chxCfg);
    PWM_Channelx_Pwm_Mode_Set(pwm->port, pwm->config.pin%PWM_CHANNAL_MAX, PWM_MODE_DISABLE, PWM_MODE_DISABLE);
    PWMx_Enable(pwm->port);
    return 0;
}

/**
 * Starts Pulse-Width Modulation signal output on a PWM pin
 *
 * @param[in]  pwm  the PWM device
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hosal_pwm_start(hosal_pwm_dev_t *pwm)
{
    if (NULL == pwm || (pwm->port != PWM0_ID && pwm->port != PWM1_ID)) {
        blog_error("arg error.\r\n");
        return -1;
    }

    PWM_Channelx_Pwm_Mode_Set(pwm->port, pwm->config.pin%PWM_CHANNAL_MAX, PWM_MODE_ENABLE, PWM_MODE_ENABLE);
    return 0;
}

/**
 * Stops output on a PWM pin
 *
 * @param[in]  pwm  the PWM device, para  set duty and  freq
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hosal_pwm_para_chg(hosal_pwm_dev_t *pwm, hosal_pwm_config_t para)
{
    PWM_CHx_CFG_Type chxCfg = {
        .modP = PWM_MODE_ENABLE,
        .modN = PWM_MODE_ENABLE,
        .polP = PWM_POL_ACTIVE_HIGH,
        .polN = PWM_POL_ACTIVE_HIGH,
        .idlP = PWM_IDLE_STATE_INACTIVE,
        .idlN = PWM_IDLE_STATE_INACTIVE,
        .brkP = PWM_BREAK_STATE_INACTIVE,
        .brkN = PWM_BREAK_STATE_INACTIVE,
        .thresholdL = 0,
        .thresholdH = 0,
        .dtg = 0,
    };

    if (NULL == pwm || (pwm->port != PWM0_ID && pwm->port != PWM1_ID)) {
        blog_error("arg error.\r\n");
        return -1;
    }

    chxCfg.thresholdL = 0;
    chxCfg.thresholdH = (PWM_XCLK_CLK/para.freq)*para.duty_cycle/PWM_DUTY_MAX;
    PWM_Channelx_Init(pwm->port, pwm->config.pin%PWM_CHANNAL_MAX, &chxCfg);
    return 0;
}

/**
 * set pwm freq
 *
 *@param[in] id pwm channel
 *@param[in] freq pwm freq
 *
 *@return 0 : on success -1 : fail
 */
int hosal_pwm_freq_set(hosal_pwm_dev_t *pwm, uint32_t freq)
{
    return -1;
}

int hosal_pwm_freq_get(hosal_pwm_dev_t *pwm,  uint32_t *p_freq)
{
    if (NULL == pwm || (pwm->port != PWM0_ID && pwm->port != PWM1_ID)) {
        blog_error("arg error.\r\n");
        return -1;
    }

    *p_freq = pwm->config.freq;
    return 0;
}

int hosal_pwm_duty_set(hosal_pwm_dev_t *pwm, uint32_t duty)
{
    PWM_CHx_CFG_Type chxCfg = {
        .modP = PWM_MODE_ENABLE,
        .modN = PWM_MODE_ENABLE,
        .polP = PWM_POL_ACTIVE_HIGH,
        .polN = PWM_POL_ACTIVE_HIGH,
        .idlP = PWM_IDLE_STATE_INACTIVE,
        .idlN = PWM_IDLE_STATE_INACTIVE,
        .brkP = PWM_BREAK_STATE_INACTIVE,
        .brkN = PWM_BREAK_STATE_INACTIVE,
        .thresholdL = 0,
        .thresholdH = 0,
        .dtg = 0,
    };

    if (NULL == pwm || (pwm->port != PWM0_ID && pwm->port != PWM1_ID)) {
        blog_error("arg error.\r\n");
        return -1;
    }

    chxCfg.thresholdL = 0;
    chxCfg.thresholdH = (PWM_XCLK_CLK/pwm->config.freq)*duty/PWM_DUTY_MAX;
    PWM_Channelx_Init(pwm->port, pwm->config.pin%PWM_CHANNAL_MAX, &chxCfg);
    return 0;
}

int hosal_pwm_duty_get(hosal_pwm_dev_t *pwm, uint32_t *p_duty)
{
    if (NULL == pwm || (pwm->port != PWM0_ID && pwm->port != PWM1_ID)) {
        blog_error("arg error.\r\n");
        return -1;
    }

    *p_duty = pwm->config.duty_cycle;
    return 0;
}
/**
 * Stops output on a PWM pin
 *
 * @param[in]  pwm  the PWM device
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hosal_pwm_stop(hosal_pwm_dev_t *pwm)
{
    if (NULL == pwm || (pwm->port != PWM0_ID && pwm->port != PWM1_ID)) {
        blog_error("arg error.\r\n");
        return -1;
    }

    PWM_Channelx_Pwm_Mode_Set(pwm->port, pwm->config.pin%PWM_CHANNAL_MAX, PWM_MODE_DISABLE, PWM_MODE_DISABLE);
    return 0;
}

/**
 * De-initialises an PWM interface, Turns off an PWM hardware interface
 *
 * @param[in]  pwm  the interface which should be de-initialised
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int hosal_pwm_finalize(hosal_pwm_dev_t *pwm)
{
    if (NULL == pwm || (pwm->port != PWM0_ID && pwm->port != PWM1_ID)) {
        blog_error("arg error.\r\n");
        return -1;
    }

    PWMx_Disable(pwm->port);
    return 0;
}


