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
#include <drv_timer.h>
#include <board.h>


#ifdef RT_USING_CLOCK_TIME

struct es32f3_clock_timer_dev
{
    rt_clock_timer_t parent;
    ald_timer_handle_t *clock_timer_periph;
    IRQn_Type IRQn;
};

#ifdef BSP_USING_AD16C4T0_CLOCK_TIMER
static struct es32f3_clock_timer_dev ad16c4t0_clock_timer;

static struct rt_clock_timer_info ad16c4t0_info =
{
    ES_SYS_HCLK_CLK >> ES_CMU_PCLK_DIV, /* maximum count frequency */
    (ES_SYS_HCLK_CLK >> ES_CMU_PCLK_DIV)/(1U<<16),        /* minimum count frequency */
    0xFFFF,    /* counter maximum value */
    ES_AD16C4T0_CLOCK_TIMER_MODE
};

void __attribute__((interrupt)) AD16C4T_Handler(void)
{
    rt_interrupt_enter();
    ald_timer_clear_flag_status(ad16c4t0_clock_timer.clock_timer_periph, ALD_TIMER_FLAG_UPDATE);
    rt_clock_timer_isr(&ad16c4t0_clock_timer.parent);
    rt_interrupt_leave();
}

#endif

#ifdef BSP_USING_GP16C4T0_CLOCK_TIMER

static struct es32f3_clock_timer_dev gp16c4t0_clock_timer;

static struct rt_clock_timer_info gp16c4t0_info =
{
    ES_SYS_HCLK_CLK >> ES_CMU_PCLK_DIV, /* maximum count frequency */
    (ES_SYS_HCLK_CLK >> ES_CMU_PCLK_DIV)/(1U<<16),        /* minimum count frequency */
    0xFFFF,    /* counter maximum value */
    ES_GP16C4T0_CLOCK_TIMER_MODE
};

void __attribute__((interrupt)) GPTIMB0_Handler(void)
{
    rt_interrupt_enter();
    ald_timer_clear_flag_status(gp16c4t0_clock_timer.clock_timer_periph, TIMER_FLAG_UPDATE);
    rt_clock_timer_isr(&gp16c4t0_clock_timer.parent);
    rt_interrupt_leave();
}

#endif
#ifdef BSP_USING_GP16C4T1_CLOCK_TIMER

static struct es32f3_clock_timer_dev gp16c4t1_clock_timer;

static struct rt_clock_timer_info gp16c4t1_info =
{
    ES_SYS_HCLK_CLK >> ES_CMU_PCLK_DIV, /* maximum count frequency */
    (ES_SYS_HCLK_CLK >> ES_CMU_PCLK_DIV)/(1U<<16),        /* minimum count frequency */
    0xFFFF,    /* counter maximum value */
    ES_GP16C4T1_CLOCK_TIMER_MODE
};

void __attribute__((interrupt)) GPTIMB1_Handler(void)
{
    rt_interrupt_enter();
    ald_timer_clear_flag_status(gp16c4t1_clock_timer.clock_timer_periph, TIMER_FLAG_UPDATE);
    rt_clock_timer_isr(&gp16c4t1_clock_timer.parent);
    rt_interrupt_leave();
}

#endif
#ifdef BSP_USING_GP16C4T1_CLOCK_TIMER

static struct es32f3_clock_timer_dev gp16c4t1_clock_timer;

static struct rt_clock_timer_info gp16c4t1_info =
{
    ES_SYS_HCLK_CLK >> ES_CMU_PCLK_DIV, /* maximum count frequency */
    (ES_SYS_HCLK_CLK >> ES_CMU_PCLK_DIV)/(1U<<16),        /* minimum count frequency */
    0xFFFF,    /* counter maximum value */
    ES_GP16C4T1_CLOCK_TIMER_MODE
};

void __attribute__((interrupt)) GPTIMB2_Handler(void)
{
    rt_interrupt_enter();
    ald_timer_clear_flag_status(gp16c4t1_clock_timer.clock_timer_periph, TIMER_FLAG_UPDATE);
    rt_clock_timer_isr(&gp16c4t1_clock_timer.parent);
    rt_interrupt_leave();
}

#endif
#ifdef BSP_USING_BS16T0_CLOCK_TIMER

static struct es32f3_clock_timer_dev bs16t0_clock_timer;

static struct rt_clock_timer_info bs16t0_info =
{
    ES_SYS_HCLK_CLK >> ES_CMU_PCLK_DIV, /* maximum count frequency */
    (ES_SYS_HCLK_CLK >> ES_CMU_PCLK_DIV)/(1U<<16),        /* minimum count frequency */
    0xFFFF,    /* counter maximum value */
    ES_BS16T0_CLOCK_TIMER_MODE
};

void __attribute__((interrupt)) BSTIM0_Handler(void)
{
    rt_interrupt_enter();
    ald_timer_clear_flag_status(bs16t0_clock_timer.clock_timer_periph, TIMER_FLAG_UPDATE);
    rt_clock_timer_isr(&bs16t0_clock_timer.parent);
    rt_interrupt_leave();
}

#endif

static void es32f3_clock_timer_init(rt_clock_timer_t *timer, rt_uint32_t state)
{
    struct es32f3_clock_timer_dev *clock_timer = (struct es32f3_clock_timer_dev *)timer->parent.user_data;

    struct rt_clock_timer_info *clock_timer_info = (struct rt_clock_timer_info *)timer->info;

    RT_ASSERT(clock_timer != RT_NULL);

    if (1 == state)
    {
        ald_timer_base_init(clock_timer->clock_timer_periph);
        ald_timer_interrupt_config(clock_timer->clock_timer_periph, ALD_TIMER_IT_UPDATE, ENABLE);
        csi_vic_enable_sirq(clock_timer->IRQn);
    }

    clock_timer->parent.freq = ald_cmu_get_pclk_clock()/((clock_timer->clock_timer_periph->perh->PRES & 0xFFFF)+1);
    clock_timer_info->maxfreq = clock_timer->parent.freq;
    clock_timer_info->minfreq = (clock_timer->parent.freq)/0xFFFF;

}

static rt_err_t es32f3_clock_timer_start(rt_clock_timer_t *timer,
                                     rt_uint32_t cnt,
                                     rt_clock_timer_mode_t mode)
{
    struct es32f3_clock_timer_dev *clock_timer = (struct es32f3_clock_timer_dev *)timer->parent.user_data;

    RT_ASSERT(clock_timer != RT_NULL);

    WRITE_REG(clock_timer->clock_timer_periph->perh->AR, cnt);
    ald_timer_base_start(clock_timer->clock_timer_periph);

    return RT_EOK;
}

static void es32f3_clock_timer_stop(rt_clock_timer_t *timer)
{
    struct es32f3_clock_timer_dev *clock_timer = (struct es32f3_clock_timer_dev *)timer->parent.user_data;

    RT_ASSERT(clock_timer != RT_NULL);

    ald_timer_base_stop(clock_timer->clock_timer_periph);
}

static rt_uint32_t es32f3_clock_timer_count_get(rt_clock_timer_t *timer)
{
    struct es32f3_clock_timer_dev *clock_timer = (struct es32f3_clock_timer_dev *)timer->parent.user_data;
    uint32_t clock_timer_count = 0;

    RT_ASSERT(clock_timer != RT_NULL);

    clock_timer_count = READ_REG(clock_timer->clock_timer_periph->perh->COUNT);

    return clock_timer_count;
}

static rt_err_t es32f3_clock_timer_control(rt_clock_timer_t *timer,
                                       rt_uint32_t cmd,
                                       void *args)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t freq = 0;
    struct es32f3_clock_timer_dev *clock_timer = (struct es32f3_clock_timer_dev *)timer->parent.user_data;

    RT_ASSERT(clock_timer != RT_NULL);

    switch (cmd)
    {
    case CLOCK_TIMER_CTRL_FREQ_SET:
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
                    clock_timer->clock_timer_periph->perh->PRES = (uint32_t)target;
                    ret = RT_EOK;
                }
                if((temp < 0.002)&&(target >= 0x1))
                {
                    clock_timer->clock_timer_periph->perh->PRES = (uint32_t)target - 1;
                    ret = RT_EOK;
                }

            }

            if(ret == RT_EOK)     /*更新信息*/
                clock_timer->parent.freq = ald_cmu_get_pclk_clock()/((clock_timer->clock_timer_periph->perh->PRES & 0xFFFF)+1);

        }

        break;

    case CLOCK_TIMER_CTRL_STOP:
        ald_timer_base_stop(clock_timer->clock_timer_periph);
        break;

    default:
        ret = RT_EINVAL;
        break;
    }

    return ret;
}

static struct rt_clock_timer_ops es32f3_clock_timer_ops =
{
    es32f3_clock_timer_init,
    es32f3_clock_timer_start,
    es32f3_clock_timer_stop,
    es32f3_clock_timer_count_get,
    es32f3_clock_timer_control
};

int rt_hw_clock_timer_init(void)
{
    rt_err_t ret = RT_EOK;

#ifdef BSP_USING_AD16C4T0_CLOCK_TIMER
    static ald_timer_handle_t ad16c4t0_clock_timer_periph;

    ad16c4t0_clock_timer_periph.perh = AD16C4T;
    ad16c4t0_clock_timer.IRQn = AD16C4T_IRQn;

    ad16c4t0_clock_timer_periph.init.prescaler = ES_AD16C4T0_CLOCK_TIMER_PRES - 1;
    ad16c4t0_clock_timer_periph.init.mode = ( ES_AD16C4T0_CLOCK_TIMER_MODE == CLOCK_TIMER_CNTMODE_UP )? ALD_TIMER_CNT_MODE_UP : ALD_TIMER_CNT_MODE_DOWN;
    ad16c4t0_clock_timer.clock_timer_periph = &ad16c4t0_clock_timer_periph;

    ad16c4t0_clock_timer.parent.info = &ad16c4t0_info;
    ad16c4t0_clock_timer.parent.ops = &es32f3_clock_timer_ops;
    ret = rt_clock_timer_register(&ad16c4t0_clock_timer.parent, ES_DEVICE_NAME_AD16C4T0_CLOCK_TIMER, &ad16c4t0_clock_timer);
#endif

#ifdef BSP_USING_GP16C4T0_CLOCK_TIMER
    static timer_handle_t gp16c4t0_clock_timer_periph;

    gp16c4t0_clock_timer_periph.perh = GP16C4T0;
    gp16c4t0_clock_timer.IRQn = GP16C4T0_IRQn;

    gp16c4t0_clock_timer_periph.init.prescaler = ES_GP16C4T0_CLOCK_TIMER_PRES - 1;
    gp16c4t0_clock_timer_periph.init.mode = ( ES_GP16C4T0_CLOCK_TIMER_MODE == CLOCK_TIMER_CNTMODE_UP )? TIMER_CNT_MODE_UP : TIMER_CNT_MODE_DOWN;
    gp16c4t0_clock_timer.clock_timer_periph = &gp16c4t0_clock_timer_periph;

    gp16c4t0_clock_timer.parent.info = &gp16c4t0_info;
    gp16c4t0_clock_timer.parent.ops = &es32f3_clock_timer_ops;
    ret = rt_clock_timer_register(&gp16c4t0_clock_timer.parent, ES_DEVICE_NAME_GP16C4T0_CLOCK_TIMER, &gp16c4t0_clock_timer);
#endif

#ifdef BSP_USING_GP16C4T1_CLOCK_TIMER
    static timer_handle_t gp16c4t1_clock_timer_periph;

    gp16c4t1_clock_timer_periph.perh = GP16C4T1;
    gp16c4t1_clock_timer.IRQn = GP16C4T1_IRQn;

    gp16c4t1_clock_timer_periph.init.prescaler = ES_GP16C4T1_CLOCK_TIMER_PRES - 1;
    gp16c4t1_clock_timer_periph.init.mode = ( ES_GP16C4T1_CLOCK_TIMER_MODE == CLOCK_TIMER_CNTMODE_UP )? TIMER_CNT_MODE_UP : TIMER_CNT_MODE_DOWN;
    gp16c4t1_clock_timer.clock_timer_periph = &gp16c4t1_clock_timer_periph;

    gp16c4t1_clock_timer.parent.info = &gp16c4t1_info;
    gp16c4t1_clock_timer.parent.ops = &es32f3_clock_timer_ops;
    ret = rt_clock_timer_register(&gp16c4t1_clock_timer.parent, ES_DEVICE_NAME_GP16C4T1_CLOCK_TIMER, &gp16c4t1_clock_timer);
#endif

#ifdef BSP_USING_GP16C4T2_CLOCK_TIMER
    static timer_handle_t gp16c4t2_clock_timer_periph;

    gp16c4t2_clock_timer_periph.perh = GP16C4T2;
    gp16c4t2_clock_timer.IRQn = GP16C4T2_IRQn;

    gp16c4t2_clock_timer_periph.init.prescaler = ES_GP16C4T2_CLOCK_TIMER_PRES - 1;
    gp16c4t2_clock_timer_periph.init.mode = ( ES_GP16C4T2_CLOCK_TIMER_MODE == CLOCK_TIMER_CNTMODE_UP )? TIMER_CNT_MODE_UP : TIMER_CNT_MODE_DOWN;
    gp16c4t2_clock_timer.clock_timer_periph = &gp16c4t2_clock_timer_periph;

    gp16c4t2_clock_timer.parent.info = &gp16c4t2_info;
    gp16c4t2_clock_timer.parent.ops = &es32f3_clock_timer_ops;
    ret = rt_clock_timer_register(&gp16c4t2_clock_timer.parent, ES_DEVICE_NAME_GP16C4T2_CLOCK_TIMER, &gp16c4t2_clock_timer);
#endif

#ifdef BSP_USING_BS16T0_CLOCK_TIMER
    static timer_handle_t bs16t0_clock_timer_periph;

    bs16t0_clock_timer_periph.perh = BS16T0;
    bs16t0_clock_timer.IRQn = BS16T0_IRQn;

    bs16t0_clock_timer_periph.init.prescaler = ES_BS16T0_CLOCK_TIMER_PRES - 1;
    bs16t0_clock_timer_periph.init.mode = ( ES_BS16T0_CLOCK_TIMER_MODE == CLOCK_TIMER_CNTMODE_UP )? TIMER_CNT_MODE_UP : TIMER_CNT_MODE_DOWN;
    bs16t0_clock_timer.clock_timer_periph = &bs16t0_clock_timer_periph;

    bs16t0_clock_timer.parent.info = &bs16t0_info;
    bs16t0_clock_timer.parent.ops = &es32f3_clock_timer_ops;
    ret = rt_clock_timer_register(&bs16t0_clock_timer.parent, ES_DEVICE_NAME_BS16T0_CLOCK_TIMER, &bs16t0_clock_timer);
#endif

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_clock_timer_init);

#endif
