/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     ck_pwm.c
 * @brief    CSI Source File for PWM Driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#include "ck_pwm.h"
#include "drv_pwm.h"
#include "soc.h"

#define ERR_PWM(errno) (CSI_DRV_ERRNO_PWM_BASE | errno)

#define PWM_NULL_PARAM_CHK(para)                    \
    do {                                        \
        if (para == NULL) {                     \
            return ERR_PWM(EDRV_PARAMETER);   \
        }                                       \
    } while (0)

typedef struct {
    uint32_t base;
    uint32_t irq;
    uint32_t ch_num;
} ck_pwm_priv_t;

static ck_pwm_priv_t pwm_instance[CONFIG_PWM_NUM];

int32_t __attribute__((weak)) target_pwm_init(pin_t pwm_pin, uint32_t *ch_num, uint32_t *base, uint32_t *irq)
{
    return -1;
}

/**
  \brief       Initialize PWM Interface. 1. Initializes the resources needed for the PWM interface 2.registers event callback function
  \param[in]   pwm pin of gpio
  \return      handle pwm handle to operate.
*/
pwm_handle_t drv_pwm_initialize(pin_t pwm_pin)
{
    uint32_t base = 0u;
    uint32_t irq = 0u;
    uint32_t ch_num = 0u;

    int32_t idx = target_pwm_init(pwm_pin, &ch_num, &base, &irq);

    if (idx < 0 || idx >= CONFIG_PWM_NUM) {
        return NULL;
    }

    ck_pwm_priv_t *pwm_priv = &pwm_instance[idx];

    pwm_priv->base      = base;
    pwm_priv->irq       = irq;
    pwm_priv->ch_num    = ch_num;

    return pwm_priv;
}

/**
  \brief       De-initialize PWM Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle pwm handle to operate.
  \return      \ref execution_status
*/
int32_t drv_pwm_uninitialize(pwm_handle_t handle)
{
    PWM_NULL_PARAM_CHK(handle);

    return 0;
}

/**
  \brief       config pwm mode.
  \param[in]   handle pwm handle to operate.
  \param[in]   sysclk  configured system clock.
  \param[in]   period_us  the PWM period in us
  \param[in]   duty      the PMW duty.  ( 0 - 10000 represents 0% - 100% ,other values are invalid)
  \return      \ref execution_status
*/
int32_t drv_pwm_config(pwm_handle_t handle, uint32_t sysclk, uint32_t period_us, uint32_t duty)
{
    if (handle == NULL || duty > 10000) {
        return ERR_PWM(EDRV_PARAMETER);
    }

    ck_pwm_priv_t *pwm_priv = handle;
    uint32_t chn = pwm_priv->ch_num;

    uint32_t counter = (sysclk / 1000000 * period_us);

    if (counter >= 0xffff) {
        return ERR_PWM(EDRV_PARAMETER);
    }

    uint32_t data_width;

    data_width = (uint32_t)((counter * duty / 10000));

    ck_pwm_reg_t *addr = (ck_pwm_reg_t *)(pwm_priv->base);
    uint32_t ctl_tmp = addr->PWMCTL;
    uint32_t temp;

    if (chn == CKENUM_PWM_CH0 || chn == CKENUM_PWM_CH1) {
        ctl_tmp &= 0xfffffffe;
        addr->PWMCTL = ctl_tmp | (uint32_t)CKENUM_PWM_COUNT_UP;

        temp = addr->PWM01LOAD;
        temp &= 0xffff0000;
        addr->PWM01LOAD = temp | counter;

        temp = addr->PWM0CMP;

        if (chn == CKENUM_PWM_CH0) {
            temp &= 0xffff0000;
            addr->PWM0CMP = temp | data_width;
        } else {
            temp &= 0x0000ffff;
            addr->PWM0CMP = temp | data_width << 16;
        }
    }

    if (chn == CKENUM_PWM_CH2 || chn == CKENUM_PWM_CH3) {
        ctl_tmp &= 0xfffffffd;
        addr->PWMCTL = ctl_tmp | (uint32_t)CKENUM_PWM_COUNT_UP << 1;

        temp = addr->PWM01LOAD;
        temp &= 0x0000ffff;
        addr->PWM01LOAD = temp | counter << 16 ;

        temp = addr->PWM1CMP;

        if (chn == CKENUM_PWM_CH2) {
            temp &= 0xffff0000;
            addr->PWM1CMP = temp | data_width;
        } else {
            temp &= 0x0000ffff;
            addr->PWM1CMP = temp | data_width << 16;
        }
    }

    if (chn == CKENUM_PWM_CH4 || chn == CKENUM_PWM_CH5) {
        ctl_tmp &= 0xfffffffb;
        addr->PWMCTL = ctl_tmp | (uint32_t)CKENUM_PWM_COUNT_UP << 2;

        temp = addr->PWM23LOAD;
        temp &= 0xffff0000;
        addr->PWM23LOAD = temp | counter;

        temp = addr->PWM2CMP;

        if (chn == CKENUM_PWM_CH4) {
            temp &= 0xffff0000;
            addr->PWM2CMP = temp | data_width;
        } else {
            temp &= 0x0000ffff;
            addr->PWM2CMP = temp | data_width << 16;
        }
    }

    if (chn == CKENUM_PWM_CH6 || chn == CKENUM_PWM_CH7) {
        ctl_tmp &= 0xfffffff7;
        addr->PWMCTL = ctl_tmp | (uint32_t)CKENUM_PWM_COUNT_UP << 3;

        temp = addr->PWM23LOAD;
        temp &= 0x0000ffff;
        addr->PWM23LOAD = temp | counter << 16 ;

        temp = addr->PWM3CMP;

        if (chn == CKENUM_PWM_CH6) {
            temp &= 0xffff0000;
            addr->PWM3CMP = temp | data_width;
        } else {
            temp &= 0x0000ffff;
            addr->PWM3CMP = temp | data_width << 16;
        }
    }

    if (chn == CKENUM_PWM_CH8 || chn == CKENUM_PWM_CH9) {
        ctl_tmp &= 0xffffffef;
        addr->PWMCTL = ctl_tmp | (uint32_t)CKENUM_PWM_COUNT_UP << 4;

        temp = addr->PWM45LOAD;
        temp &= 0xffff0000;
        addr->PWM45LOAD = temp | counter ;

        temp = addr->PWM4CMP;

        if (chn == CKENUM_PWM_CH8) {
            temp &= 0xffff0000;
            addr->PWM4CMP = temp | data_width;
        } else {
            temp &= 0x0000ffff;
            addr->PWM4CMP = temp | data_width << 16;
        }
    }

    if (chn == CKENUM_PWM_CH10 || chn == CKENUM_PWM_CH11) {
        ctl_tmp &= 0xffffffdf;
        addr->PWMCTL = ctl_tmp | (uint32_t)CKENUM_PWM_COUNT_UP << 5;

        temp = addr->PWM45LOAD;
        temp &= 0x0000ffff;
        addr->PWM45LOAD = temp | counter << 16 ;

        temp = addr->PWM5CMP;

        if (chn == CKENUM_PWM_CH10) {
            temp &= 0xffff0000;
            addr->PWM5CMP = temp | data_width;
        } else {
            temp &= 0x0000ffff;
            addr->PWM5CMP = temp | data_width << 16;
        }
    }

    return 0;
}

/**
  \brief       start generate pwm signal.
  \param[in]   handle pwm handle to operate.
  \param[in]   pwm channel number.
  \return      \ref execution_status
*/
int32_t drv_pwm_start(pwm_handle_t handle)
{
    PWM_NULL_PARAM_CHK(handle);

    ck_pwm_priv_t *pwm_priv = handle;
    ck_pwm_reg_t *addr = (ck_pwm_reg_t *)(pwm_priv->base);
    uint32_t chn = pwm_priv->ch_num;

    if (chn == CKENUM_PWM_CH0 || chn == CKENUM_PWM_CH1) {
        addr->PWMCFG |= 0x00000003;        /* PWM0 output enable */
    }

    if (chn == CKENUM_PWM_CH2 || chn == CKENUM_PWM_CH3) {
        addr->PWMCFG |= 0x0000000C;        /* PWM1 output enable */
    }

    if (chn == CKENUM_PWM_CH4 || chn == CKENUM_PWM_CH5) {
        addr->PWMCFG |= 0x00000030;        /* PWM2 output enable */
    }

    if (chn == CKENUM_PWM_CH6 || chn == CKENUM_PWM_CH7) {
        addr->PWMCFG |= 0x000000C0;        /* PWM3 output enable */
    }

    if (chn == CKENUM_PWM_CH8 || chn == CKENUM_PWM_CH9) {
        addr->PWMCFG |= 0x00000300;        /* PWM4 output enable */
    }

    if (chn == CKENUM_PWM_CH10 || chn == CKENUM_PWM_CH11) {
        addr->PWMCFG |= 0x00000C00;        /* PWM5 output enable */
    }

    return 0;
}

/**
  \brief       Stop generate pwm signal.
  \param[in]   handle pwm handle to operate.
  \return      \ref execution_status
*/
int32_t drv_pwm_stop(pwm_handle_t handle)
{
    PWM_NULL_PARAM_CHK(handle);

    ck_pwm_priv_t *pwm_priv = handle;
    ck_pwm_reg_t *addr = (ck_pwm_reg_t *)(pwm_priv->base);
    uint32_t chn = pwm_priv->ch_num;

    if (chn == CKENUM_PWM_CH0 || chn == CKENUM_PWM_CH1) {
        addr->PWMCFG &= ~0x00000003;        /* PWM0 output disable */
    }

    if (chn == CKENUM_PWM_CH2 || chn == CKENUM_PWM_CH3) {
        addr->PWMCFG &= ~0x0000000C;        /* PWM1 output disable */
    }

    if (chn == CKENUM_PWM_CH4 || chn == CKENUM_PWM_CH5) {
        addr->PWMCFG &= ~0x00000030;        /* PWM2 output disable */
    }

    if (chn == CKENUM_PWM_CH6 || chn == CKENUM_PWM_CH7) {
        addr->PWMCFG &= ~0x000000C0;        /* PWM3 output disable */
    }

    if (chn == CKENUM_PWM_CH8 || chn == CKENUM_PWM_CH9) {
        addr->PWMCFG &= ~0x00000300;        /* PWM4 output disable */
    }

    if (chn == CKENUM_PWM_CH10 || chn == CKENUM_PWM_CH11) {
        addr->PWMCFG &= ~0x00000C00;        /* PWM5 output disable */
    }

    return 0;
}

