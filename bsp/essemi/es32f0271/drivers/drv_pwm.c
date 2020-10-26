/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-10-23     yuzrain       the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "md_gpio.h"

/* PWM device control struct */
struct pwm_dev_ctrl {
    AD16C4T_TypeDef *timx;
    rt_uint8_t  chnm;   /* Cannel number */
    struct rt_pwm_configuration *cfg;
};

#ifdef BSP_USING_PWM_GP16C2T1

/* Remember channel configuration */
static struct rt_pwm_configuration pwm_ch_cfg_gp16c2t1[2]  = {
    [0] = {
        .channel    = 1,
        .period     = 0,
        .pulse      = 0
    },
    [1] = {
        .channel    = 2,
        .period     = 0,
        .pulse      = 0
    }
};

/* Define static device */
static struct rt_device_pwm pwm_dev_gp16c2t1;
static struct pwm_dev_ctrl pwm_dev_gp16c2t1_ctrl;
#endif
#ifdef BSP_USING_PWM_GP16C2T4

/* Remember channel configuration */
static struct rt_pwm_configuration pwm_ch_cfg_gp16c2t4[2]  = {
    [0] = {
        .channel    = 1,
        .period     = 0,
        .pulse      = 0
    },
    [1] = {
        .channel    = 2,
        .period     = 0,
        .pulse      = 0
    }
};

/* Define static device */
static struct rt_device_pwm pwm_dev_gp16c2t4;
static struct pwm_dev_ctrl pwm_dev_gp16c2t4_ctrl;
#endif

static void pwm_auto_config_freq(AD16C4T_TypeDef *timerx, uint32_t ns)
{
    uint32_t temp_ar;
    uint32_t temp_pres = timerx->PRES & 0xFFFF;
    uint32_t err_cnt = 0;

    /* Automatic setting frequency division ratio */
    while (err_cnt++ < 65536)
    {
        temp_ar = (uint64_t)SystemCoreClock * ns / 1000000000 / (temp_pres + 1);
        if (temp_ar <= 0xFFFF)
            break;
        temp_pres++;
    }

    /* Write back to PRES */
    timerx->PRES    = (uint16_t)(temp_pres & 0xFFFF);
    timerx->AR      = temp_ar;
}

static void pwm_set_duty(AD16C4T_TypeDef *timerx, uint8_t ch, uint32_t ns)
{
    uint32_t temp_pres = timerx->PRES & 0xFFFF;
    uint64_t tmp = (uint64_t)SystemCoreClock * ns / 1000000000 / (temp_pres + 1);

    if (ch == 1)
        WRITE_REG(timerx->CCVAL1, (uint32_t)tmp);
    else if (ch == 2)
        WRITE_REG(timerx->CCVAL2, (uint32_t)tmp);
}

static rt_err_t es32f0_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    rt_err_t ret = RT_EOK;
    struct pwm_dev_ctrl *dev_ctrl
                    = (struct pwm_dev_ctrl *)device->parent.user_data;
    struct rt_pwm_configuration *cfg = (struct rt_pwm_configuration *)arg;
    AD16C4T_TypeDef *timerx = (AD16C4T_TypeDef *)dev_ctrl->timx;

    switch (cmd)
    {
        case PWM_CMD_ENABLE:
        {
            if (cfg->channel == 1)
                SET_BIT(timerx->CCEP, AD16C4T_CCEP_CC1EN_MSK);
            else if (cfg->channel == 2)
                SET_BIT(timerx->CCEP, AD16C4T_CCEP_CC2EN_MSK);
            break;
        }
        case PWM_CMD_DISABLE:
        {
            if (cfg->channel == 1)
                CLEAR_BIT(timerx->CCEP, AD16C4T_CCEP_CC1EN_MSK);
            else if (cfg->channel == 2)
                CLEAR_BIT(timerx->CCEP, AD16C4T_CCEP_CC2EN_MSK);
            break;
        }
        case PWM_CMD_SET:
        {
            /* count registers max 0xFFFF, auto adjust prescaler */
            pwm_auto_config_freq(timerx, cfg->period);
            pwm_set_duty(timerx, cfg->channel, cfg->pulse);
            /* Remember configuration */
            dev_ctrl->cfg[cfg->channel-1].period = cfg->period;
            dev_ctrl->cfg[cfg->channel-1].pulse  = cfg->pulse;
            break;
        }
        case PWM_CMD_GET:
        {
            cfg->period = dev_ctrl->cfg[cfg->channel-1].period;
            cfg->pulse  = dev_ctrl->cfg[cfg->channel-1].pulse;
            break;
        }

        default:
            break;
    }
    return ret;
}

const static struct rt_pwm_ops es32f0_pwm_ops =
{
    es32f0_pwm_control
};

int rt_hw_pwm_init(void)
{
    rt_err_t ret = RT_EOK;

#ifdef BSP_USING_PWM_GP16C2T1 /* 2 channels */
    /* Open clock */
    SET_BIT(RCU->APB2EN, RCU_APB2EN_GP16C2T1EN_MSK);

    /* GPIO configuration */
    md_gpio_set_mode        (GPIOB, MD_GPIO_PIN_1,   MD_GPIO_MODE_FUNCTION);
    md_gpio_set_mode        (GPIOB, MD_GPIO_PIN_2,   MD_GPIO_MODE_FUNCTION);
    md_gpio_set_function0_7 (GPIOB, MD_GPIO_PIN_1,   MD_GPIO_AF5);
    md_gpio_set_function0_7 (GPIOB, MD_GPIO_PIN_2,   MD_GPIO_AF5);

    /* Timer configuration */
    MODIFY_REG(GP16C2T1->CHMR1, AD16C4T_CHMR1_OUTPUT_CH1MOD_MSK, 
                                (6 << AD16C4T_CHMR1_OUTPUT_CH1MOD_POSS));
    MODIFY_REG(GP16C2T1->CHMR1, AD16C4T_CHMR1_OUTPUT_CH2MOD_MSK, 
                                (6 << AD16C4T_CHMR1_OUTPUT_CH2MOD_POSS));
    SET_BIT(GP16C2T1->BDCFG, AD16C4T_BDCFG_GOEN_MSK);
    SET_BIT(GP16C2T1->CON1, AD16C4T_CON1_CNTEN_MSK);

    pwm_dev_gp16c2t1_ctrl.chnm       = 2;
    pwm_dev_gp16c2t1_ctrl.timx       = GP16C2T1;
    pwm_dev_gp16c2t1_ctrl.cfg        = pwm_ch_cfg_gp16c2t1;
    /* Register PWM device */
    ret = rt_device_pwm_register(&pwm_dev_gp16c2t1,
                                "pwm1", &es32f0_pwm_ops, &pwm_dev_gp16c2t1_ctrl);
#endif

#ifdef BSP_USING_PWM_GP16C2T4 /* 2 channels */
    /* Open clock */
    SET_BIT(RCU->APB2EN, RCU_APB2EN_GP16C2T4EN_MSK);

    /* GPIO configuration */
    md_gpio_set_mode        (GPIOB, MD_GPIO_PIN_12,   MD_GPIO_MODE_FUNCTION);
    md_gpio_set_mode        (GPIOB, MD_GPIO_PIN_14,   MD_GPIO_MODE_FUNCTION);
    md_gpio_set_function8_15(GPIOB, MD_GPIO_PIN_12,   MD_GPIO_AF5);
    md_gpio_set_function8_15(GPIOB, MD_GPIO_PIN_14,   MD_GPIO_AF5);

    /* Timer configuration */
    MODIFY_REG(GP16C2T4->CHMR1, AD16C4T_CHMR1_OUTPUT_CH1MOD_MSK, 
                                (6 << AD16C4T_CHMR1_OUTPUT_CH1MOD_POSS));
    MODIFY_REG(GP16C2T4->CHMR1, AD16C4T_CHMR1_OUTPUT_CH2MOD_MSK, 
                                (6 << AD16C4T_CHMR1_OUTPUT_CH2MOD_POSS));
    SET_BIT(GP16C2T4->BDCFG, AD16C4T_BDCFG_GOEN_MSK);
    SET_BIT(GP16C2T4->CON1, AD16C4T_CON1_CNTEN_MSK);

    pwm_dev_gp16c2t4_ctrl.chnm       = 2;
    pwm_dev_gp16c2t4_ctrl.timx       = GP16C2T4;
    pwm_dev_gp16c2t4_ctrl.cfg        = pwm_ch_cfg_gp16c2t4;
    /* Register PWM device */
    ret = rt_device_pwm_register(&pwm_dev_gp16c2t4,
                                "pwm2", &es32f0_pwm_ops, &pwm_dev_gp16c2t4_ctrl);
#endif

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_pwm_init);
