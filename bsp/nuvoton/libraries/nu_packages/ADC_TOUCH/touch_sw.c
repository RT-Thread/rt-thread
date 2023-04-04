/**************************************************************************//**
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-02-22      Wayne        First version
*
******************************************************************************/

#include <rtthread.h>

#if defined(NU_PKG_USING_ADC_TOUCH_SW)

#include "rtdevice.h"
#include "touch_sw.h"

/* Private define ---------------------------------------------------------------*/
#define DEF_ADC_TOUCH_SMPL_TICK  40
#define TOUCH_MQ_LENGTH   32

/* Private Typedef --------------------------------------------------------------*/
static rt_timer_t g_psRtTouchMenuTimer;
static rt_mq_t    g_pmqTouchXYZ;

static S_TOUCH_SW *g_psTouchSW = RT_NULL;
static rt_bool_t  bDoSmpling = RT_FALSE;

struct nu_adc_touch_data
{
    uint32_t    u32X;
    uint32_t    u32Y;
    uint32_t    u32Z0;
    uint32_t    u32Z1;
};
typedef struct nu_adc_touch_data *nu_adc_touch_data_t;

static rt_uint32_t Get_X(S_TOUCH_SW *psTouchSW)
{
    /*=== Get X from ADC input ===*/
    rt_pin_mode(psTouchSW->pin[evXR], PIN_MODE_OUTPUT);
    rt_pin_mode(psTouchSW->pin[evYD], PIN_MODE_INPUT);
    rt_pin_mode(psTouchSW->pin[evXL], PIN_MODE_OUTPUT);

    rt_pin_write(psTouchSW->pin[evXR], PIN_HIGH);
    rt_pin_write(psTouchSW->pin[evXL], PIN_LOW);

    psTouchSW->switch_to_digital(psTouchSW->pin[evXR]);
    psTouchSW->switch_to_digital(psTouchSW->pin[evYD]);
    psTouchSW->switch_to_digital(psTouchSW->pin[evXL]);

    /* Disable the digital input path to avoid the leakage current. */
    /* Configure the ADC analog input pins.  */
    psTouchSW->switch_to_analog(psTouchSW->pin[evYU]);

    return rt_adc_read((rt_adc_device_t)psTouchSW->adc, psTouchSW->i32ADCChnYU) & 0x0FFF;
}

static rt_uint32_t Get_Y(S_TOUCH_SW *psTouchSW)
{
    /*=== Get Y from ADC input ===*/
    rt_pin_mode(psTouchSW->pin[evYU], PIN_MODE_OUTPUT);
    rt_pin_mode(psTouchSW->pin[evYD], PIN_MODE_OUTPUT);
    rt_pin_mode(psTouchSW->pin[evXL], PIN_MODE_INPUT);

    rt_pin_write(psTouchSW->pin[evYU], PIN_HIGH);
    rt_pin_write(psTouchSW->pin[evYD], PIN_LOW);

    psTouchSW->switch_to_digital(psTouchSW->pin[evYU]);
    psTouchSW->switch_to_digital(psTouchSW->pin[evYD]);
    psTouchSW->switch_to_digital(psTouchSW->pin[evXL]);

    /* Disable the digital input path to avoid the leakage current. */
    /* Configure the ADC analog input pins.  */
    psTouchSW->switch_to_analog(psTouchSW->pin[evXR]);

    return rt_adc_read((rt_adc_device_t)psTouchSW->adc, psTouchSW->i32ADCChnXR) & 0x0FFF;
}

static void nu_adc_touch_smpl(void *p)
{
    static rt_bool_t bDrop = RT_FALSE;
    static uint32_t u32LastZ0 = 0xffffu;

    struct nu_adc_touch_data point;
    S_TOUCH_SW *psTouchSW;

    if (!bDoSmpling)
        return ;

    psTouchSW = (S_TOUCH_SW *)p;

    rt_memset(&point, 0, sizeof(struct nu_adc_touch_data));

    /* Get X, Y ADC converting data */
    point.u32X  = Get_X(psTouchSW);
    point.u32Y  = Get_Y(psTouchSW);
    if ((point.u32X < 4000) && (point.u32Y  < 4000))
    {
        point.u32Z0 = point.u32Z1 = 1;
        bDrop = RT_FALSE;
    }
    else
    {
        bDrop = RT_TRUE;
    }

    // rt_kprintf("%04x %04x %d %d\n", point.u32X, point.u32Y, point.u32Z0, bDrop);
    if ((!bDrop || (u32LastZ0 != 0)) && (rt_mq_send(g_pmqTouchXYZ, (const void *)&point, sizeof(struct nu_adc_touch_data)) == RT_EOK))
    {
        if (psTouchSW->psRtTouch != RT_NULL)
            rt_hw_touch_isr(psTouchSW->psRtTouch);
    }
    u32LastZ0 = point.u32Z0;
}

int32_t nu_adc_touch_read_xyz(uint32_t *bufX, uint32_t *bufY, uint32_t *bufZ0, uint32_t *bufZ1, int32_t dataCnt)
{
    int i;
    struct nu_adc_touch_data value;

    for (i = 0 ; i < dataCnt; i++)
    {
        if (rt_mq_recv(g_pmqTouchXYZ, (void *)&value, sizeof(struct nu_adc_touch_data), 0) == -RT_ETIMEOUT)
            break;

        bufX[i]  = value.u32X;
        bufY[i]  = value.u32Y;
        bufZ0[i] = value.u32Z0;
        bufZ1[i] = value.u32Z1;
    }
    return i;
}


void nu_adc_touch_detect(rt_bool_t bStartDetect)
{
}

rt_err_t nu_adc_touch_enable(rt_touch_t psRtTouch)
{
    if (g_psTouchSW->adc)
    {
        g_psTouchSW->psRtTouch = psRtTouch;

        rt_adc_enable((rt_adc_device_t)g_psTouchSW->adc, g_psTouchSW->i32ADCChnXR);
        rt_adc_enable((rt_adc_device_t)g_psTouchSW->adc, g_psTouchSW->i32ADCChnYU);
        bDoSmpling = RT_TRUE;

        /* Start sampling procedure. */
        rt_timer_start(g_psRtTouchMenuTimer);
        return RT_EOK;
    }

    return -RT_ERROR;
}

rt_err_t nu_adc_touch_disable(void)
{
    if (g_psTouchSW->adc)
    {
        /* Stop sampling procedure. */
        rt_timer_stop(g_psRtTouchMenuTimer);

        bDoSmpling = RT_FALSE;
        rt_adc_disable((rt_adc_device_t)g_psTouchSW->adc, g_psTouchSW->i32ADCChnXR);
        rt_adc_disable((rt_adc_device_t)g_psTouchSW->adc, g_psTouchSW->i32ADCChnYU);
        g_psTouchSW->psRtTouch = RT_NULL;
        return RT_EOK;
    }

    return -RT_ERROR;
}

rt_err_t nu_adc_touch_sw_register(S_TOUCH_SW *psTouchSW)
{
    RT_ASSERT(psTouchSW);

    psTouchSW->adc = rt_device_find(psTouchSW->adc_name);
    RT_ASSERT(psTouchSW->adc);

    g_pmqTouchXYZ = rt_mq_create("ADC_TOUCH_SW", sizeof(struct nu_adc_touch_data), TOUCH_MQ_LENGTH, RT_IPC_FLAG_FIFO);
    RT_ASSERT(g_pmqTouchXYZ);

    g_psRtTouchMenuTimer = rt_timer_create("TOUCH_SMPL_TIMER", nu_adc_touch_smpl, (void *)psTouchSW, DEF_ADC_TOUCH_SMPL_TICK, RT_TIMER_FLAG_PERIODIC);
    RT_ASSERT(g_psRtTouchMenuTimer);

    g_psTouchSW = psTouchSW;

    return RT_EOK;
}

#endif //#if defined(NU_PKG_USING_ADC_TOUCH_SW)
