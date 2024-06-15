/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-11     wangyq       the first version
 * 2019-11-01     wangyq        update libraries
 * 2021-04-20     liuhy         the second version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "es_conf_info_pwm.h"


#ifdef RT_USING_PWM

static void pwm_set_duty(ald_timer_handle_t *timer_initstruct, ald_timer_channel_t ch, uint32_t ns)
{
    uint64_t tmp = (uint64_t)ald_cmu_get_pclk_clock() * ns / 1000000000 /
                   (timer_initstruct->init.prescaler + 1);

    if (ch == ALD_TIMER_CHANNEL_1)
        WRITE_REG(timer_initstruct->perh->CCVAL1, (uint32_t)tmp);
    else if (ch == ALD_TIMER_CHANNEL_2)
        WRITE_REG(timer_initstruct->perh->CCVAL2, (uint32_t)tmp);
    else if (ch == ALD_TIMER_CHANNEL_3)
        WRITE_REG(timer_initstruct->perh->CCVAL3, (uint32_t)tmp);
    else if (ch == ALD_TIMER_CHANNEL_4)
        WRITE_REG(timer_initstruct->perh->CCVAL4, (uint32_t)tmp);
}

static rt_err_t es32f3_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    rt_err_t ret = RT_EOK;
    uint64_t _arr,bus_speed,tmp;
    uint32_t _maxcnt,_ccep_ch_en = 0U;
    ald_timer_channel_t pwm_channel;
    ald_timer_oc_init_t tim_ocinit;
    ald_timer_handle_t *timer_initstruct = (ald_timer_handle_t *)device->parent.user_data;
    struct rt_pwm_configuration *cfg = (struct rt_pwm_configuration *)arg;

    RT_ASSERT(timer_initstruct != RT_NULL);


    /* select pwm output channel */
    if (1 == cfg->channel)
    {
        pwm_channel = ALD_TIMER_CHANNEL_1;
        _ccep_ch_en = timer_initstruct->perh->CCEP & TIMER_CCEP_CC1EN_MSK;
    }
    else if (2 == cfg->channel)
    {
        pwm_channel = ALD_TIMER_CHANNEL_2;
        _ccep_ch_en = timer_initstruct->perh->CCEP & TIMER_CCEP_CC2EN_MSK;
    }
    else if (3 == cfg->channel)
    {
        pwm_channel = ALD_TIMER_CHANNEL_3;
        _ccep_ch_en = timer_initstruct->perh->CCEP & TIMER_CCEP_CC3EN_MSK;
    }
    else if (4 == cfg->channel)
    {
        pwm_channel = ALD_TIMER_CHANNEL_4;
        _ccep_ch_en = timer_initstruct->perh->CCEP & TIMER_CCEP_CC4EN_MSK;
    }
    else
        return RT_EINVAL;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        ald_timer_pwm_start(timer_initstruct, pwm_channel);
        break;

    case PWM_CMD_DISABLE:
        ald_timer_pwm_stop(timer_initstruct, pwm_channel);
        break;

    case PWM_CMD_SET:

          /*当通道没开的时候：关通道，设置输出模式和极性，初始化通道*/
        if(!_ccep_ch_en)
        {
         tim_ocinit.oc_mode      = ES_PWM_OC_MODE;
         tim_ocinit.oc_polarity  = ES_PWM_OC_POLARITY;
         tim_ocinit.oc_fast_en   = DISABLE;
         tim_ocinit.ocn_polarity = ALD_TIMER_OCN_POLARITY_HIGH;
         tim_ocinit.ocn_idle     = ALD_TIMER_OCN_IDLE_RESET;
         tim_ocinit.oc_idle      = ALD_TIMER_OC_IDLE_RESET;

            ald_timer_oc_config_channel(timer_initstruct, &tim_ocinit, pwm_channel);
        }

        bus_speed = (uint64_t)ald_cmu_get_pclk_clock();

        /*判断外设的计数器最大值*/
#ifdef ES32F36xx
        if((timer_initstruct->perh == GP32C4T0)||(timer_initstruct->perh == GP32C4T1))
        {
            _maxcnt = 0xFFFFFFFF;
        }
        else _maxcnt = 0xFFFF;
#else
        _maxcnt = 0xFFFF;
#endif

        /*当最大分频 <= _maxcnt时：估计大概的分频，加快速度 */
        tmp = bus_speed * (cfg->period)/1000000000/_maxcnt;
        timer_initstruct->init.prescaler = (tmp > 2U) ? (tmp - 2U) : 0U ;    /*bus_speed < 500000000*/

        /* count registers max , auto adjust prescaler */
        do
        {
          _arr = bus_speed * (cfg->period) / 1000000000 /(++timer_initstruct->init.prescaler);

        }
        while (_arr > _maxcnt);

        WRITE_REG(timer_initstruct->perh->AR, (uint32_t)_arr);
        timer_initstruct->init.period   = (uint32_t)_arr;

        /* update prescaler */
        WRITE_REG(timer_initstruct->perh->PRES, --timer_initstruct->init.prescaler);

        pwm_set_duty(timer_initstruct, pwm_channel, cfg->pulse);

        break;

    case PWM_CMD_GET:
        cfg->pulse = ald_timer_read_capture_value(timer_initstruct, pwm_channel) * 100 /
                     READ_REG(timer_initstruct->perh->AR);
        break;

    default:
        break;
    }
    return ret;
}

const static struct rt_pwm_ops es32f3_pwm_ops =
{
    es32f3_pwm_control
};

int rt_hw_pwm_init(void)
{
    rt_err_t ret = RT_EOK;
    ald_gpio_init_t gpio_initstructure;

    gpio_initstructure.mode = ALD_GPIO_MODE_OUTPUT;
    gpio_initstructure.od = ALD_GPIO_PUSH_PULL;
    gpio_initstructure.pupd = ALD_GPIO_PUSH_UP;
    gpio_initstructure.odrv = ALD_GPIO_OUT_DRIVE_NORMAL;
    gpio_initstructure.flt  = ALD_GPIO_FILTER_DISABLE;
    gpio_initstructure.type = ALD_GPIO_TYPE_CMOS;

#ifdef BSP_USING_AD16C4T0_PWM /* 4 channels */
    static struct rt_device_pwm ad16c4t0_pwm_dev;
    static ald_timer_handle_t ad16c4t0_timer_initstruct;

    ad16c4t0_timer_initstruct.perh = AD16C4T;
    ald_timer_pwm_init(&ad16c4t0_timer_initstruct);

    /* gpio initialization */

#if  defined(ES_AD16C4T0_CH1_GPIO_FUNC)&&defined(ES_AD16C4T0_CH1_GPIO_PORT)&&defined(ES_AD16C4T0_CH1_GPIO_PIN)
    gpio_initstructure.func = ES_AD16C4T0_CH1_GPIO_FUNC;
    ald_gpio_init(ES_AD16C4T0_CH1_GPIO_PORT, ES_AD16C4T0_CH1_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_AD16C4T0_CH2_GPIO_FUNC)&&defined(ES_AD16C4T0_CH2_GPIO_PORT)&&defined(ES_AD16C4T0_CH2_GPIO_PIN)
    gpio_initstructure.func = ES_AD16C4T0_CH2_GPIO_FUNC;
    ald_gpio_init(ES_AD16C4T0_CH2_GPIO_PORT, ES_AD16C4T0_CH2_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_AD16C4T0_CH3_GPIO_FUNC)&&defined(ES_AD16C4T0_CH3_GPIO_PORT)&&defined(ES_AD16C4T0_CH3_GPIO_FUNC)
    gpio_initstructure.func = ES_AD16C4T0_CH3_GPIO_FUNC;
    ald_gpio_init(ES_AD16C4T0_CH3_GPIO_PORT, ES_AD16C4T0_CH3_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_AD16C4T0_CH4_GPIO_FUNC)&&defined(ES_AD16C4T0_CH4_GPIO_PORT)&&defined(ES_AD16C4T0_CH4_GPIO_PIN)
    gpio_initstructure.func = ES_AD16C4T0_CH4_GPIO_FUNC;
    ald_gpio_init(ES_AD16C4T0_CH4_GPIO_PORT, ES_AD16C4T0_CH4_GPIO_PIN, &gpio_initstructure);
#endif

    ret = rt_device_pwm_register(&ad16c4t0_pwm_dev, ES_DEVICE_NAME_AD16C4T0_PWM, &es32f3_pwm_ops,
                                 &ad16c4t0_timer_initstruct);
#endif

#ifdef BSP_USING_GP16C4T0_PWM /* 4 channels */
    static struct rt_device_pwm gp16c4t0_pwm_dev;
    static ald_timer_handle_t gp16c4t0_timer_initstruct;

    gp16c4t0_timer_initstruct.perh = GP16C4T0;
    ald_timer_pwm_init(&gp16c4t0_timer_initstruct);

    /* gpio initialization */

#if  defined(ES_GP16C4T0_CH1_GPIO_FUNC)&&defined(ES_GP16C4T0_CH1_GPIO_PORT)&&defined(ES_GP16C4T0_CH1_GPIO_PIN)
    gpio_initstructure.func = ES_GP16C4T0_CH1_GPIO_FUNC;
    ald_gpio_init(ES_GP16C4T0_CH1_GPIO_PORT, ES_GP16C4T0_CH1_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_GP16C4T0_CH2_GPIO_FUNC)&&defined(ES_GP16C4T0_CH2_GPIO_PORT)&&defined(ES_GP16C4T0_CH2_GPIO_PIN)
    gpio_initstructure.func = ES_GP16C4T0_CH2_GPIO_FUNC;
    ald_gpio_init(ES_GP16C4T0_CH2_GPIO_PORT, ES_GP16C4T0_CH2_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_GP16C4T0_CH3_GPIO_FUNC)&&defined(ES_GP16C4T0_CH3_GPIO_PORT)&&defined(ES_GP16C4T0_CH3_GPIO_PIN)
    gpio_initstructure.func = ES_GP16C4T0_CH3_GPIO_FUNC;
    ald_gpio_init(ES_GP16C4T0_CH3_GPIO_PORT, ES_GP16C4T0_CH3_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_GP16C4T0_CH4_GPIO_FUNC)&&defined(ES_GP16C4T0_CH4_GPIO_PORT)&&defined(ES_GP16C4T0_CH4_GPIO_PIN)
    gpio_initstructure.func = ES_GP16C4T0_CH4_GPIO_FUNC;
    ald_gpio_init(ES_GP16C4T0_CH4_GPIO_PORT, ES_GP16C4T0_CH4_GPIO_PIN, &gpio_initstructure);
#endif

    ret = rt_device_pwm_register(&gp16c4t0_pwm_dev, ES_DEVICE_NAME_GP16C4T0_PWM, &es32f3_pwm_ops,
                                 &gp16c4t0_timer_initstruct);
#endif

#ifdef BSP_USING_GP16C4T1_PWM /* 4 channels */
    static struct rt_device_pwm gp16c4t1_pwm_dev;
    static ald_timer_handle_t gp16c4t1_timer_initstruct;

    gp16c4t1_timer_initstruct.perh = GP16C4T1;
    ald_timer_pwm_init(&gp16c4t1_timer_initstruct);

    /* gpio initialization */

#if  defined(ES_GP16C4T1_CH1_GPIO_FUNC)&&defined(ES_GP16C4T1_CH1_GPIO_PORT)&&defined(ES_GP16C4T1_CH1_GPIO_PIN)
    gpio_initstructure.func = ES_GP16C4T1_CH1_GPIO_FUNC;
    ald_gpio_init(ES_GP16C4T1_CH1_GPIO_PORT, ES_GP16C4T1_CH1_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_GP16C4T1_CH2_GPIO_FUNC)&&defined(ES_GP16C4T1_CH2_GPIO_PORT)&&defined(ES_GP16C4T1_CH2_GPIO_PIN)
    gpio_initstructure.func = ES_GP16C4T1_CH2_GPIO_FUNC;
    ald_gpio_init(ES_GP16C4T1_CH2_GPIO_PORT, ES_GP16C4T1_CH2_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_GP16C4T1_CH3_GPIO_FUNC)&&defined(ES_GP16C4T1_CH3_GPIO_PORT)&&defined(ES_GP16C4T1_CH3_GPIO_PIN)
    gpio_initstructure.func = ES_GP16C4T1_CH3_GPIO_FUNC;
    ald_gpio_init(ES_GP16C4T1_CH3_GPIO_PORT, ES_GP16C4T1_CH3_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_GP16C4T1_CH4_GPIO_FUNC)&&defined(ES_GP16C4T1_CH4_GPIO_PORT)&&defined(ES_GP16C4T1_CH4_GPIO_PIN)
    gpio_initstructure.func = ES_GP16C4T1_CH4_GPIO_FUNC;
    ald_gpio_init(ES_GP16C4T1_CH4_GPIO_PORT, ES_GP16C4T1_CH4_GPIO_PIN, &gpio_initstructure);
#endif

    ret = rt_device_pwm_register(&gp16c4t1_pwm_dev, ES_DEVICE_NAME_GP16C4T1_PWM, &es32f3_pwm_ops,
                                 &gp16c4t1_timer_initstruct);
#endif

#ifdef BSP_USING_GP16C4T2_PWM /* 4 channels */
    static struct rt_device_pwm gp16c4t2_pwm_dev;
    static ald_timer_handle_t gp16c4t2_timer_initstruct;

    gp16c4t2_timer_initstruct.perh = GP16C4T2;
    ald_timer_pwm_init(&gp16c4t2_timer_initstruct);

    /* gpio initialization */

#if  defined(ES_GP16C4T2_CH1_GPIO_FUNC)&&defined(ES_GP16C4T2_CH1_GPIO_PORT)&&defined(ES_GP16C4T2_CH1_GPIO_PIN)
    gpio_initstructure.func = ES_GP16C4T2_CH1_GPIO_FUNC;
    ald_gpio_init(ES_GP16C4T2_CH1_GPIO_PORT, ES_GP16C4T2_CH1_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_GP16C4T2_CH2_GPIO_FUNC)&&defined(ES_GP16C4T2_CH2_GPIO_PORT)&&defined(ES_GP16C4T2_CH2_GPIO_PIN)
    gpio_initstructure.func = ES_GP16C4T2_CH2_GPIO_FUNC;
    ald_gpio_init(ES_GP16C4T2_CH2_GPIO_PORT, ES_GP16C4T2_CH2_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_GP16C4T2_CH3_GPIO_FUNC)&&defined(ES_GP16C4T2_CH3_GPIO_PORT)&&defined(ES_GP16C4T2_CH3_GPIO_PIN)
    gpio_initstructure.func = ES_GP16C4T2_CH3_GPIO_FUNC;
    ald_gpio_init(ES_GP16C4T2_CH3_GPIO_PORT, ES_GP16C4T2_CH3_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_GP16C4T2_CH4_GPIO_FUNC)&&defined(ES_GP16C4T2_CH4_GPIO_PORT)&&defined(ES_GP16C4T2_CH4_GPIO_PIN)
    gpio_initstructure.func = ES_GP16C4T2_CH4_GPIO_FUNC;
    ald_gpio_init(ES_GP16C4T2_CH4_GPIO_PORT, ES_GP16C4T2_CH4_GPIO_PIN, &gpio_initstructure);
#endif

    ret = rt_device_pwm_register(&gp16c4t2_pwm_dev, ES_DEVICE_NAME_GP16C4T2_PWM, &es32f3_pwm_ops,
                                 &gp16c4t2_timer_initstruct);
#endif

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_pwm_init);

#endif
