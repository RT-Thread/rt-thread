/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-03-03     lgnq         First version
 */

#include <rtthread.h>
#include <rthw.h>
#include "mb9bf506r.h"
#include "adc.h"
#include "led.h"
#include "lcd.h"

#ifdef RT_USING_RTGUI
#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>
#endif

static struct rt_device adc;

static rt_err_t rt_adc_init(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);

    if(!(dev->flag & RT_DEVICE_FLAG_ACTIVATED))
    {
        /* I/O setting AN08 - P18 */
        FM3_GPIO->ADE |= 0x100;
        FM3_GPIO->PFR1 = 0x100;

        /* A/DC setting */
        FM3_ADC0->SCIS1 = 0x01;
        FM3_ADC0->ADSS1 = 0x00;             /* sampling timming ADST0 */
        FM3_ADC0->ADST1 = 0x43;
        FM3_ADC0->ADCT  = 0x02;
        FM3_ADC0->SCCR  = 0x10;             /* FIFO clear,single mode */
        FM3_ADC0->CMPCR = 0x00;             /* disable comparator */

        /* starting A/DC */
        FM3_ADC0->SCCR |= 0x01;             /* A/DC start */

        dev->flag |= RT_DEVICE_FLAG_ACTIVATED;
    }
    return RT_EOK;
}

static rt_err_t rt_adc_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);

    switch (cmd)
    {
        case RT_DEVICE_CTRL_ADC_START:
            FM3_ADC0->SCCR |= 0x1;
        break;

        case RT_DEVICE_CTRL_ADC_RESULT:
            while(FM3_ADC0->ADSR & 0x1)
                ;
            *((rt_uint16_t*)args) = FM3_ADC0->SCFD;
            *((rt_uint16_t*)args) = *((rt_uint16_t*)args) >> 6;
            *((rt_uint16_t*)args) = (*((rt_uint16_t*)args)*3300)/1024;
        break;
    }
    return RT_EOK;
}

extern struct rt_messagequeue mq;
extern rt_thread_t info_tid;
rt_uint16_t adc_value;
static void adc_thread_entry(void *parameter)
{
    rt_device_t device;

#ifdef RT_USING_RTGUI
    struct rtgui_event_command ecmd;

    RTGUI_EVENT_COMMAND_INIT(&ecmd);
    ecmd.type = RTGUI_CMD_USER_INT;
    ecmd.command_id = ADC_UPDATE;
#else
    struct lcd_msg msg;
#endif

    device = rt_device_find("adc");

    while(1)
    {
        rt_device_control(device, RT_DEVICE_CTRL_ADC_START, RT_NULL);
        rt_device_control(device, RT_DEVICE_CTRL_ADC_RESULT, &adc_value);
        pwm_update(adc_value/3);
#ifdef RT_USING_RTGUI
        rtgui_thread_send(info_tid, &ecmd.parent, sizeof(ecmd));
#else
        msg.type = ADC_MSG;
        msg.adc_value = adc_value;
        rt_mq_send(&mq, &msg, sizeof(msg));
#endif
        rt_thread_delay(20);
    }
}

static rt_thread_t adc_thread;
void rt_hw_adc_init(void)
{
    adc.type        = RT_Device_Class_Char;
    adc.rx_indicate = RT_NULL;
    adc.tx_complete = RT_NULL;
    adc.init        = rt_adc_init;
    adc.open        = RT_NULL;
    adc.close       = RT_NULL;
    adc.read        = RT_NULL;
    adc.write       = RT_NULL;
    adc.control     = rt_adc_control;
    adc.user_data   = RT_NULL;

    adc_thread = rt_thread_create("adc", adc_thread_entry, RT_NULL, 384, 26, 5);
    if(adc_thread != RT_NULL)
        rt_thread_startup(adc_thread);

    /* register a character device */
    rt_device_register(&adc, "adc", RT_DEVICE_FLAG_RDWR);
}

