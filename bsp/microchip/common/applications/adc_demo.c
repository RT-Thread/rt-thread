/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date        Author    Email                    Notes
 * 2022-04-16  Kevin.Liu kevin.liu.mchp@gmail.com First Release
 */

#include <rtthread.h>

#include <atmel_start.h>

#include "adc_demo.h"

#ifdef SAM_ADC_EXAMPLE

#if defined(SOC_SAMC21) || defined(SOC_SAML10)
#define ADC_RESOLUTION_12BIT    ADC_CTRLC_RESSEL_12BIT_Val
#define ADC_RESOLUTION_16BIT    ADC_CTRLC_RESSEL_16BIT_Val
#elif defined(SOC_SAME54)
#define ADC_RESOLUTION_12BIT    ADC_CTRLB_RESSEL_12BIT_Val
#define ADC_RESOLUTION_16BIT    ADC_CTRLB_RESSEL_16BIT_Val
#elif defined(SOC_SAME70)
#define ADC_RESOLUTION_12BIT    AFEC_EMR_RES_NO_AVERAGE_Val
#define ADC_RESOLUTION_16BIT    AFEC_EMR_RES_OSR256_Val
#else
#error "ADC undefined SOC Platform"
#endif

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

    /* ADC 16-bit resolution */
    adc_sync_disable_channel(&ADC_0, 0);
    adc_sync_set_resolution(&ADC_0,  ADC_RESOLUTION_16BIT);
    adc_sync_enable_channel(&ADC_0,  0);
#ifndef RT_USING_FINSH
    rt_kprintf("buf[0]=0x%02X buf[1]=0x%02X\r\n", buffer[0], buffer[1]);
#endif

    /* ADC 12-bit resolution */
    adc_sync_disable_channel(&ADC_0, 0);
    adc_sync_set_resolution(&ADC_0,  ADC_RESOLUTION_12BIT);
    adc_sync_enable_channel(&ADC_0,  0);
#ifndef RT_USING_FINSH
    rt_kprintf("buf[0]=0x%02X buf[1]=0x%02X\r\n", buffer[0], buffer[1]);
#endif

    return RT_EOK;
}
#endif

/*@}*/
