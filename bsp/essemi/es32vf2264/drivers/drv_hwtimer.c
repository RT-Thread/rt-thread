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
 * 2019-3-19      wangyq       the first version
 * 2019-11-01     wangyq        update libraries
 * 2021-04-20     liuhy         the second version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drv_hwtimer.h>
#include <board.h>


#ifdef RT_USING_HWTIMER

struct es32f3_hwtimer_dev
{
    rt_hwtimer_t parent;
    ald_timer_handle_t *hwtimer_periph;
    IRQn_Type IRQn;
};

#ifdef BSP_USING_AD16C4T0_HWTIMER
static struct es32f3_hwtimer_dev ad16c4t0_hwtimer;

static struct rt_hwtimer_info ad16c4t0_info =
{
    ES_SYS_HCLK_CLK >> ES_CMU_PCLK_DIV, /* maximum count frequency */
    (ES_SYS_HCLK_CLK >> ES_CMU_PCLK_DIV)/(1U<<16),        /* minimum count frequency */
    0xFFFF,    /* counter maximum value */
    ES_AD16C4T0_HWTIMER_MODE
};

void __attribute__((interrupt)) AD16C4T_Handler(void)
{
    rt_interrupt_enter();
    ald_timer_clear_flag_status(ad16c4t0_hwtimer.hwtimer_periph, ALD_TIMER_FLAG_UPDATE);
    rt_device_hwtimer_isr(&ad16c4t0_hwtimer.parent);
    rt_interrupt_leave();
}

#endif

#ifdef BSP_USING_GP16C4T0_HWTIMER

static struct es32f3_hwtimer_dev gp16c4t0_hwtimer;

static struct rt_hwtimer_info gp16c4t0_info =
{
    ES_SYS_HCLK_CLK >> ES_CMU_PCLK_DIV, /* maximum count frequency */
    (ES_SYS_HCLK_CLK >> ES_CMU_PCLK_DIV)/(1U<<16),        /* minimum count frequency */
    0xFFFF,    /* counter maximum value */
    ES_GP16C4T0_HWTIMER_MODE
};

void __attribute__((interrupt)) GPTIMB0_Handler(void)
{
    rt_interrupt_enter();
    ald_timer_clear_flag_status(gp16c4t0_hwtimer.hwtimer_periph, TIMER_FLAG_UPDATE);
    rt_device_hwtimer_isr(&gp16c4t0_hwtimer.parent);
    rt_interrupt_leave();
}

#endif
#ifdef BSP_USING_GP16C4T1_HWTIMER

static struct es32f3_hwtimer_dev gp16c4t1_hwtimer;

static struct rt_hwtimer_info gp16c4t1_info =
{
    ES_SYS_HCLK_CLK >> ES_CMU_PCLK_DIV, /* maximum count frequency */
    (ES_SYS_HCLK_CLK >> ES_CMU_PCLK_DIV)/(1U<<16),        /* minimum count frequency */
    0xFFFF,    /* counter maximum value */
    ES_GP16C4T1_HWTIMER_MODE
};

void __attribute__((interrupt)) GPTIMB1_Handler(void)
{
    rt_interrupt_enter();
    ald_timer_clear_flag_status(gp16c4t1_hwtimer.hwtimer_periph, TIMER_FLAG_UPDATE);
    rt_device_hwtimer_isr(&gp16c4t1_hwtimer.parent);
    rt_interrupt_leave();
}

#endif
#ifdef BSP_USING_GP16C4T1_HWTIMER

static struct es32f3_hwtimer_dev gp16c4t1_hwtimer;

static struct rt_hwtimer_info gp16c4t1_info =
{
    ES_SYS_HCLK_CLK >> ES_CMU_PCLK_DIV, /* maximum count frequency */
    (ES_SYS_HCLK_CLK >> ES_CMU_PCLK_DIV)/(1U<<16),        /* minimum count frequency */
    0xFFFF,    /* counter maximum value */
    ES_GP16C4T1_HWTIMER_MODE
};

void __attribute__((interrupt)) GPTIMB2_Handler(void)
{
    rt_interrupt_enter();
    ald_timer_clear_flag_status(gp16c4t1_hwtimer.hwtimer_periph, TIMER_FLAG_UPDATE);
    rt_device_hwtimer_isr(&gp16c4t1_hwtimer.parent);
    rt_interrupt_leave();
}

#endif
#ifdef BSP_USING_BS16T0_HWTIMER

static struct es32f3_hwtimer_dev bs16t0_hwtimer;

static struct rt_hwtimer_info bs16t0_info =
{
    ES_SYS_HCLK_CLK >> ES_CMU_PCLK_DIV, /* maximum count frequency */
    (ES_SYS_HCLK_CLK >> ES_CMU_PCLK_DIV)/(1U<<16),        /* minimum count frequency */
    0xFFFF,    /* counter maximum value */
    ES_BS16T0_HWTIMER_MODE
};

void __attribute__((interrupt)) BSTIM0_Handler(void)
{
    rt_interrupt_enter();
    ald_timer_clear_flag_status(bs16t0_hwtimer.hwtimer_periph, TIMER_FLAG_UPDATE);
    rt_device_hwtimer_isr(&bs16t0_hwtimer.parent);
    rt_interrupt_leave();
}

#endif

static void es32f3_hwtimer_init(rt_hwtimer_t *timer, rt_uint32_t state)
{
    struct es32f3_hwtimer_dev *hwtimer = (struct es32f3_hwtimer_dev *)timer->parent.user_data;

    struct rt_hwtimer_info *hwtimer_info = (struct rt_hwtimer_info *)timer->info;

    RT_ASSERT(hwtimer != RT_NULL);

    if (1 == state)
    {
        ald_timer_base_init(hwtimer->hwtimer_periph);
        ald_timer_interrupt_config(hwtimer->hwtimer_periph, ALD_TIMER_IT_UPDATE, ENABLE);
        csi_vic_enable_sirq(hwtimer->IRQn);
    }

    hwtimer->parent.freq = ald_cmu_get_pclk_clock()/((hwtimer->hwtimer_periph->perh->PRES & 0xFFFF)+1);
    hwtimer_info->maxfreq = hwtimer->parent.freq;
    hwtimer_info->minfreq = (hwtimer->parent.freq)/0xFFFF;

}

static rt_err_t es32f3_hwtimer_start(rt_hwtimer_t *timer,
                                     rt_uint32_t cnt,
                                     rt_hwtimer_mode_t mode)
{
    struct es32f3_hwtimer_dev *hwtimer = (struct es32f3_hwtimer_dev *)timer->parent.user_data;

    RT_ASSERT(hwtimer != RT_NULL);

    WRITE_REG(hwtimer->hwtimer_periph->perh->AR, cnt);
    ald_timer_base_start(hwtimer->hwtimer_periph);

    return RT_EOK;
}

static void es32f3_hwtimer_stop(rt_hwtimer_t *timer)
{
    struct es32f3_hwtimer_dev *hwtimer = (struct es32f3_hwtimer_dev *)timer->parent.user_data;

    RT_ASSERT(hwtimer != RT_NULL);

    ald_timer_base_stop(hwtimer->hwtimer_periph);
}

static rt_uint32_t es32f3_hwtimer_count_get(rt_hwtimer_t *timer)
{
    struct es32f3_hwtimer_dev *hwtimer = (struct es32f3_hwtimer_dev *)timer->parent.user_data;
    uint32_t hwtimer_count = 0;

    RT_ASSERT(hwtimer != RT_NULL);

    hwtimer_count = READ_REG(hwtimer->hwtimer_periph->perh->COUNT);

    return hwtimer_count;
}

static rt_err_t es32f3_hwtimer_control(rt_hwtimer_t *timer,
                                       rt_uint32_t cmd,
                                       void *args)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t freq = 0;
    struct es32f3_hwtimer_dev *hwtimer = (struct es32f3_hwtimer_dev *)timer->parent.user_data;

    RT_ASSERT(hwtimer != RT_NULL);

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
        freq = *(rt_uint32_t *)args;

        ret = -RT_ERROR;

        if(freq)
        {
            double temp,target;
            temp = (double)ald_cmu_get_pclk_clock();
            target = temp/freq;

            if(target < 0x10001)   /*最大分频 = max(PRES)+1*/
            {
                temp = target - (int)(target);

                if((temp > 0.998)&&(target < 0x10000))
                {
                    hwtimer->hwtimer_periph->perh->PRES = (uint32_t)target;
                    ret = RT_EOK;
                }
                if((temp < 0.002)&&(target >= 0x1))
                {
                    hwtimer->hwtimer_periph->perh->PRES = (uint32_t)target - 1;
                    ret = RT_EOK;
                }

            }

            if(ret == RT_EOK)     /*更新信息*/
                hwtimer->parent.freq = ald_cmu_get_pclk_clock()/((hwtimer->hwtimer_periph->perh->PRES & 0xFFFF)+1);

        }

        break;

    case HWTIMER_CTRL_STOP:
        ald_timer_base_stop(hwtimer->hwtimer_periph);
        break;

    default:
        ret = RT_EINVAL;
        break;
    }

    return ret;
}

static struct rt_hwtimer_ops es32f3_hwtimer_ops =
{
    es32f3_hwtimer_init,
    es32f3_hwtimer_start,
    es32f3_hwtimer_stop,
    es32f3_hwtimer_count_get,
    es32f3_hwtimer_control
};

int rt_hw_hwtimer_init(void)
{
    rt_err_t ret = RT_EOK;

#ifdef BSP_USING_AD16C4T0_HWTIMER
    static ald_timer_handle_t ad16c4t0_hwtimer_periph;

    ad16c4t0_hwtimer_periph.perh = AD16C4T;
    ad16c4t0_hwtimer.IRQn = AD16C4T_IRQn;

    ad16c4t0_hwtimer_periph.init.prescaler = ES_AD16C4T0_HWTIMER_PRES - 1;
    ad16c4t0_hwtimer_periph.init.mode = ( ES_AD16C4T0_HWTIMER_MODE == HWTIMER_CNTMODE_UP )? ALD_TIMER_CNT_MODE_UP : ALD_TIMER_CNT_MODE_DOWN;
    ad16c4t0_hwtimer.hwtimer_periph = &ad16c4t0_hwtimer_periph;

    ad16c4t0_hwtimer.parent.info = &ad16c4t0_info;
    ad16c4t0_hwtimer.parent.ops = &es32f3_hwtimer_ops;
    ret = rt_device_hwtimer_register(&ad16c4t0_hwtimer.parent, ES_DEVICE_NAME_AD16C4T0_HWTIMER, &ad16c4t0_hwtimer);
#endif

#ifdef BSP_USING_GP16C4T0_HWTIMER
    static timer_handle_t gp16c4t0_hwtimer_periph;

    gp16c4t0_hwtimer_periph.perh = GP16C4T0;
    gp16c4t0_hwtimer.IRQn = GP16C4T0_IRQn;

    gp16c4t0_hwtimer_periph.init.prescaler = ES_GP16C4T0_HWTIMER_PRES - 1;
    gp16c4t0_hwtimer_periph.init.mode = ( ES_GP16C4T0_HWTIMER_MODE == HWTIMER_CNTMODE_UP )? TIMER_CNT_MODE_UP : TIMER_CNT_MODE_DOWN;
    gp16c4t0_hwtimer.hwtimer_periph = &gp16c4t0_hwtimer_periph;

    gp16c4t0_hwtimer.parent.info = &gp16c4t0_info;
    gp16c4t0_hwtimer.parent.ops = &es32f3_hwtimer_ops;
    ret = rt_device_hwtimer_register(&gp16c4t0_hwtimer.parent, ES_DEVICE_NAME_GP16C4T0_HWTIMER, &gp16c4t0_hwtimer);
#endif

#ifdef BSP_USING_GP16C4T1_HWTIMER
    static timer_handle_t gp16c4t1_hwtimer_periph;

    gp16c4t1_hwtimer_periph.perh = GP16C4T1;
    gp16c4t1_hwtimer.IRQn = GP16C4T1_IRQn;

    gp16c4t1_hwtimer_periph.init.prescaler = ES_GP16C4T1_HWTIMER_PRES - 1;
    gp16c4t1_hwtimer_periph.init.mode = ( ES_GP16C4T1_HWTIMER_MODE == HWTIMER_CNTMODE_UP )? TIMER_CNT_MODE_UP : TIMER_CNT_MODE_DOWN;
    gp16c4t1_hwtimer.hwtimer_periph = &gp16c4t1_hwtimer_periph;

    gp16c4t1_hwtimer.parent.info = &gp16c4t1_info;
    gp16c4t1_hwtimer.parent.ops = &es32f3_hwtimer_ops;
    ret = rt_device_hwtimer_register(&gp16c4t1_hwtimer.parent, ES_DEVICE_NAME_GP16C4T1_HWTIMER, &gp16c4t1_hwtimer);
#endif

#ifdef BSP_USING_GP16C4T2_HWTIMER
    static timer_handle_t gp16c4t2_hwtimer_periph;

    gp16c4t2_hwtimer_periph.perh = GP16C4T2;
    gp16c4t2_hwtimer.IRQn = GP16C4T2_IRQn;

    gp16c4t2_hwtimer_periph.init.prescaler = ES_GP16C4T2_HWTIMER_PRES - 1;
    gp16c4t2_hwtimer_periph.init.mode = ( ES_GP16C4T2_HWTIMER_MODE == HWTIMER_CNTMODE_UP )? TIMER_CNT_MODE_UP : TIMER_CNT_MODE_DOWN;
    gp16c4t2_hwtimer.hwtimer_periph = &gp16c4t2_hwtimer_periph;

    gp16c4t2_hwtimer.parent.info = &gp16c4t2_info;
    gp16c4t2_hwtimer.parent.ops = &es32f3_hwtimer_ops;
    ret = rt_device_hwtimer_register(&gp16c4t2_hwtimer.parent, ES_DEVICE_NAME_GP16C4T2_HWTIMER, &gp16c4t2_hwtimer);
#endif

#ifdef BSP_USING_BS16T0_HWTIMER
    static timer_handle_t bs16t0_hwtimer_periph;

    bs16t0_hwtimer_periph.perh = BS16T0;
    bs16t0_hwtimer.IRQn = BS16T0_IRQn;

    bs16t0_hwtimer_periph.init.prescaler = ES_BS16T0_HWTIMER_PRES - 1;
    bs16t0_hwtimer_periph.init.mode = ( ES_BS16T0_HWTIMER_MODE == HWTIMER_CNTMODE_UP )? TIMER_CNT_MODE_UP : TIMER_CNT_MODE_DOWN;
    bs16t0_hwtimer.hwtimer_periph = &bs16t0_hwtimer_periph;

    bs16t0_hwtimer.parent.info = &bs16t0_info;
    bs16t0_hwtimer.parent.ops = &es32f3_hwtimer_ops;
    ret = rt_device_hwtimer_register(&bs16t0_hwtimer.parent, ES_DEVICE_NAME_BS16T0_HWTIMER, &bs16t0_hwtimer);
#endif

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_hwtimer_init);

#endif
