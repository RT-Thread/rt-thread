/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-27     fzxhub       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_adc.h"

#ifdef RT_USING_ADC

#ifdef BSP_USING_ADC

struct lpc_adc
{
    LPC_ADC_TypeDef *ADC;
};
/*
* channel:0-7
*/
static rt_err_t lpc_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    struct lpc_adc *adc;

    RT_ASSERT(device != RT_NULL);
    adc = (struct lpc_adc *)device->parent.user_data;

    //enabled ADC
    if(enabled == RT_FALSE) adc->ADC->CR &= ~(1<<21);
    else adc->ADC->CR |= (1<<21);

    //Select the channel
    adc->ADC->CR |= (1<<channel);

    return RT_EOK;
}

static rt_err_t lpc_adc_convert(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    rt_uint32_t data;

    struct lpc_adc *adc;

    RT_ASSERT(device != RT_NULL);
    adc = (struct lpc_adc *)device->parent.user_data;

    adc->ADC->CR = (LPC_ADC->CR & 0x00FFFF00) | (1<<channel) | (1 << 24);
    while ((adc->ADC->GDR & 0x80000000) == 0);
    adc->ADC->CR = adc->ADC->CR | (1 << 24);
    while ((adc->ADC->GDR & 0x80000000) == 0);

    data = adc->ADC->GDR;
    data = (data >> 4) & 0xFFF;

    *value = data;

    return RT_EOK;
}

static const struct rt_adc_ops lpc_adc_ops =
{
    lpc_adc_enabled,
    lpc_adc_convert,
};

struct lpc_adc lpc_adc0 =
{
    LPC_ADC,
};

struct rt_adc_device adc0;

int rt_hw_adc_init(void)
{
    rt_err_t ret = RT_EOK;
    struct lpc_adc *adc;

    adc = &lpc_adc0;

    adc0.ops = &lpc_adc_ops;
    adc0.parent.user_data = adc;

    //ADC port
    LPC_IOCON->P0_23 = 0x01;     //ADC0[0]
    LPC_IOCON->P0_24 = 0x01;     //ADC0[1]
    LPC_IOCON->P0_25 = 0x01;     //ADC0[2]
    LPC_IOCON->P0_26 = 0x01;     //ADC0[3]
    LPC_IOCON->P1_30 = 0x03;     //ADC0[4]
    LPC_IOCON->P1_31 = 0x03;     //ADC0[5]
    LPC_IOCON->P0_12 = 0x03;     //ADC0[6]
    LPC_IOCON->P0_13 = 0x03;     //ADC0[7]


    //clock
    LPC_SC->PCONP |= (1U << 12);
    //config
    LPC_ADC->CR = 0;
    LPC_ADC->CR = (1 << 0)|      // SEL
                  ((PeripheralClock / 1000000 - 1) << 8) |    // CLKDIV = Fpclk / 1000000 - 1
                  (0 << 16)|     // BURST
                  (0 << 17)|     // CLKS
                  (1 << 21)|     // PDN
                  (0 << 22)|     // TEST1
                  (1 << 24)|     // START
                  (0 << 27);     // EDGE
    //waiting
    while ((LPC_ADC->GDR & 0x80000000) == 0);

    ret = rt_hw_adc_register(&adc0,"adc0",&lpc_adc_ops,adc);

    return ret;
}

INIT_BOARD_EXPORT(rt_hw_adc_init);
#endif /* BSP_USING_ADC */

#endif /* RT_USING_ADC */
