/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date        Author    Email                    Notes
 * 2019-07-16  Kevin.Liu kevin.liu.mchp@gmail.com First Release
 */

#include <rtthread.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
#include <shell.h>
#endif

#include <atmel_start.h>

#include "adc_demo.h"

#ifdef SAM_ADC_EXAMPLE

/**
 * @brief    Call this function will run ADC test code.
 *
 * @note     Test code will try to read ADC conversion result.
 *
 * @param    None.
 *
 * @return   RT_OK or -RT_ERROR.
 */

rt_err_t adc_demo_run(void)
{
    rt_uint8_t buffer[2];

    /* enable ADC driver module */
    adc_sync_enable_channel(&ADC_0, 0);

    adc_sync_read_channel(&ADC_0, 0, buffer, 2);
#ifndef RT_USING_FINSH
    rt_kprintf("buf[0]=0x%02X buf[1]=0x%02X\r\n", buffer[0], buffer[1]);
#endif

    adc_sync_disable_channel(&ADC_0, 0);
    adc_sync_set_resolution(&ADC_0,  ADC_CTRLB_RESSEL_8BIT_Val);
    adc_sync_enable_channel(&ADC_0,  0);
#ifndef RT_USING_FINSH
    rt_kprintf("buf[0]=0x%02X buf[1]=0x%02X\r\n", buffer[0], buffer[1]);
#endif

    adc_sync_disable_channel(&ADC_0, 0);
    adc_sync_set_resolution(&ADC_0,  ADC_CTRLB_RESSEL_12BIT_Val);
    adc_sync_enable_channel(&ADC_0,  0);
#ifndef RT_USING_FINSH
    rt_kprintf("buf[0]=0x%02X buf[1]=0x%02X\r\n", buffer[0], buffer[1]);
#endif

    adc_sync_disable_channel(&ADC_0, 0);
    adc_sync_set_resolution(&ADC_0,  ADC_CTRLB_RESSEL_10BIT_Val);
    adc_sync_enable_channel(&ADC_0,  0);
#ifndef RT_USING_FINSH
    rt_kprintf("buf[0]=0x%02X buf[1]=0x%02X\r\n", buffer[0], buffer[1]);
#endif

    adc_sync_disable_channel(&ADC_0, 0);
    adc_sync_set_resolution(&ADC_0,  ADC_CTRLB_RESSEL_16BIT_Val);
    adc_sync_enable_channel(&ADC_0,  0);
#ifndef RT_USING_FINSH
    rt_kprintf("buf[0]=0x%02X buf[1]=0x%02X\r\n", buffer[0], buffer[1]);
#endif

    return RT_EOK;
}
#endif

/*@}*/
