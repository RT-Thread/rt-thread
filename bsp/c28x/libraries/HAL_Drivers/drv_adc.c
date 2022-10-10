/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-07     qiyu         first version
 */

#include <board.h>
#ifdef BSP_USING_ADC
#include "drv_config.h"

#include "drv_adc.h"
#include "rtdbg.h"


static struct c28x_adc c28x_adc_obj[] =
{
#ifdef BSP_USING_ADC1
    ADC1_CONFIG,
#endif

#ifdef BSP_USING_ADC2
    ADC2_CONFIG,
#endif

#ifdef BSP_USING_ADC3
    ADC3_CONFIG,
#endif
};


static rt_err_t c28x_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    volatile struct ADC_REGS *c28x_adc_regs;
    RT_ASSERT(device != RT_NULL);
    volatile struct c28x_adc *c28x_adc_handler;
    c28x_adc_handler = (struct c28x_adc *)device->parent.user_data;
    c28x_adc_regs = c28x_adc_handler->adc_regs;

    if (enabled)
    {
        /*
         * power up the ADC
         */
        EALLOW;
        c28x_adc_regs->ADCCTL1.bit.ADCPWDNZ = 1;
        EDIS;
        /*
         * delay for 1ms to allow ADC time to power up
         */
        DELAY_US(1000);
    }
    else
    {
        /*
         * power down the ADC
         */
        EALLOW;
        c28x_adc_regs->ADCCTL1.bit.ADCPWDNZ = 0;
        EDIS;
    }

    return RT_EOK;
}

static rt_uint8_t c28x_adc_get_resolution(struct rt_adc_device *device)
{
    struct c28x_adc *c28x_adc_handler;
    volatile struct ADC_REGS *c28x_adc_regs;
    c28x_adc_handler = (struct c28x_adc *)device->parent.user_data;
    c28x_adc_regs = c28x_adc_handler->adc_regs;
    RT_ASSERT(device != RT_NULL);
    switch(c28x_adc_regs->ADCCTL2.bit.RESOLUTION)
    {
        case ADC_RESOLUTION_12BIT:
            return 12;
        case ADC_RESOLUTION_16BIT:
            return 16;
        default:
            return 0;
    }
}

static rt_int16_t c28x_adc_get_vref (struct rt_adc_device *device)
{
    /*
     * TODO
     * Get Vref
     */
    RT_ASSERT(device);
    return 3300;
}

static rt_err_t c28x_adc_get_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    struct c28x_adc *c28x_adc_handler = (struct c28x_adc*)device->parent.user_data;
    volatile struct ADC_REGS *c28x_adc_regs = c28x_adc_handler->adc_regs;
    volatile struct ADC_RESULT_REGS *c28x_adc_result_regs = c28x_adc_handler->adc_results;

    /*
     * configure channel
     * only use SOC0 for now
     */
    EALLOW;
    c28x_adc_regs->ADCSOC0CTL.bit.CHSEL = channel;  /* SOC0 will convert pin A0 */
    EDIS;
    /*
     * start conversions immediately via software, ADCA
     */
    c28x_adc_regs->ADCSOCFRC1.all = 0x0001; //SOC0
    /*
     * wait for ADCA to complete, then acknowledge flag
     */
    while(c28x_adc_regs->ADCINTFLG.bit.ADCINT1 == 0);
    c28x_adc_regs->ADCINTFLGCLR.bit.ADCINT1 = 1;

    /*
     * store results
     */
    *value = (rt_uint32_t)c28x_adc_result_regs->ADCRESULT0;

    return RT_EOK;
}

static const struct rt_adc_ops stm_adc_ops =
{
    .enabled = c28x_adc_enabled,
    .convert = c28x_adc_get_value,
    .get_resolution = c28x_adc_get_resolution,
    .get_vref = c28x_adc_get_vref,
};

static rt_err_t HAL_ADC_Init(volatile struct ADC_REGS *c28x_adc_handler)
{
    int adc_controller_num = 0;
    Uint16 acqps;

    EALLOW;
    /*
     * write configurations
     */
    c28x_adc_handler->ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    if(c28x_adc_handler == &AdcaRegs)
    {
        adc_controller_num = 0;
    }else if(c28x_adc_handler == &AdcbRegs)
    {
        adc_controller_num = 1;
    }
    else if(c28x_adc_handler == &AdccRegs)
    {
        adc_controller_num = 2;
    }
    else if(c28x_adc_handler == &AdcdRegs)
    {
        adc_controller_num = 3;
    }
    AdcSetMode(adc_controller_num, ADC_RESOLUTION, ADC_SIGNALMODE_SINGLE);
    c28x_adc_handler->ADCCTL1.bit.INTPULSEPOS = 1;
    EDIS;

    /*
     * determine minimum acquisition window (in SYSCLKS) based on resolution
     */
    if(ADC_RESOLUTION_12BIT == AdcaRegs.ADCCTL2.bit.RESOLUTION)
    {
        acqps = 14; //75ns
    }
    else
    {
        /*
         * resolution is 16-bit
         */
        acqps = 63; //320ns
    }

    /*
     * Select the channels to convert and end of conversion flag
     */
    EALLOW;
    c28x_adc_handler->ADCSOC0CTL.bit.ACQPS = acqps; //sample window is acqps + 1 SYSCLK cycles
    c28x_adc_handler->ADCINTSEL1N2.bit.INT1SEL = 0; //end of SOC0 will set INT1 flag
    c28x_adc_handler->ADCINTSEL1N2.bit.INT1E = 1;   //enable INT1 flag
    c28x_adc_handler->ADCINTFLGCLR.bit.ADCINT1 = 1; //make sure INT1 flag is cleared
    EDIS;
    return RT_EOK;
}

static int c28x_adc_init(void)
{
    int result = RT_EOK;
    /*
     * save adc name
     */
    int i = 0;
    /* ADC init */
    for (i = 0; i < sizeof(c28x_adc_obj) / sizeof(c28x_adc_obj[0]); i++)
    {
        if (HAL_ADC_Init(c28x_adc_obj[i].adc_regs) != RT_EOK)
        {
            LOG_E("%s init failed", c28x_adc_obj[i].name);
            result = -RT_ERROR;
        }
        else
        {
            /* register ADC device */
            if (rt_hw_adc_register(&c28x_adc_obj[i].c28x_adc_device, c28x_adc_obj[i].name, &stm_adc_ops, &c28x_adc_obj[i]) == RT_EOK)
            {
                LOG_D("%s init success", c28x_adc_obj[i].name);
            }
            else
            {
                LOG_E("%s register failed", c28x_adc_obj[i].name);
                result = -RT_ERROR;
            }
        }
    }

    return result;
}
INIT_BOARD_EXPORT(c28x_adc_init);

#endif /* BSP_USING_ADC */
