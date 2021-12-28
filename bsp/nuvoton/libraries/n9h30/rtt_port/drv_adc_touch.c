/**************************************************************************//**
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2021-04-20      Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_ADC_TOUCH)

#include "NuMicro.h"
#include <rtdevice.h>
#include "drv_adc.h"
#include "touch.h"

typedef struct
{
    struct rt_touch_device dev;
    rt_uint32_t x_range;
    rt_uint32_t y_range;
} nu_adc_touch;
typedef nu_adc_touch *nu_adc_touch_t;

static nu_adc_touch s_NuAdcTouch = {0};

#define DEF_CALDATA_LENGTH 7

#if defined(LCM_USING_FW043TFT)
    #define LCM_WIDTH     480
    #define LCM_HEIGHT    272
    static int cal_data_a[DEF_CALDATA_LENGTH] = { 8824, -34, -2261272, -70, -6302, 21805816, 65536 };
#else
    #define LCM_WIDTH     800
    #define LCM_HEIGHT    480
    #if defined(LCM_USING_FW070TFT)
    static int cal_data_a[DEF_CALDATA_LENGTH] = { 13230, -66, -1161952, -85, 8600, -1636996, 65536 };
    #else
    static int cal_data_a[DEF_CALDATA_LENGTH] = { 1, 0, 0, 0, 1, 0, 1 };
    #endif
#endif

static const int cal_zero[DEF_CALDATA_LENGTH] = { 1, 0, 0, 0, 1, 0, 1 };

static void nu_adc_touch_cal(int *sumx, int *sumy)
{
    int xtemp, ytemp;

    xtemp = *sumx;
    ytemp = *sumy;
    *sumx = (cal_data_a[2] +
             cal_data_a[0] * xtemp +
             cal_data_a[1] * ytemp) / cal_data_a[6];
    *sumy = (cal_data_a[5] +
             cal_data_a[3] * xtemp +
             cal_data_a[4] * ytemp) / cal_data_a[6];
}

static rt_size_t nu_adc_touch_readpoint(struct rt_touch_device *device, void *buf, rt_size_t read_num)
{
    static int last_report_x = 0, last_report_y = 0;
    struct rt_touch_data *pPoint = (struct rt_touch_data *)buf;
    nu_adc_touch_t psNuAdcTouch = (nu_adc_touch_t)device;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(buf != RT_NULL);

    int i;

    for (i = 0; i < read_num; i++)
    {
        int bufZ0 = 0, bufZ1 = 0;
        int sumx = 0, sumy = 0;
        pPoint[i].timestamp = rt_touch_get_ts();
        pPoint[i].track_id = 0;

        if (nu_adc_read_touch_xyz((uint16_t *)&sumx, (uint16_t *)&sumy, (uint16_t *)&bufZ0, (uint16_t *)&bufZ1, 1) != 1)
            break;

        if (bufZ0 == 0)
        {
            /* Workaround: In this case, x, y values are unstable. so, report last point's coordinate.*/
            pPoint[i].event = RT_TOUCH_EVENT_UP;
            pPoint[i].x_coordinate = last_report_x;
            pPoint[i].y_coordinate = last_report_y;
        }
        else
        {
            nu_adc_touch_cal(&sumx, &sumy);
            pPoint[i].event = RT_TOUCH_EVENT_DOWN;
            pPoint[i].x_coordinate = sumx;
            pPoint[i].y_coordinate = sumy;
            last_report_x = sumx;
            last_report_y = sumy;
        }

        bufZ0 = bufZ0 >> 3;

        pPoint[i].width = (bufZ0 > 255) ? 255 : bufZ0;

        //Limit max x, y coordinate if value is over its range.
        pPoint[i].x_coordinate = (pPoint[i].x_coordinate > psNuAdcTouch->x_range) ? psNuAdcTouch->x_range : pPoint[i].x_coordinate;
        pPoint[i].y_coordinate = (pPoint[i].y_coordinate > psNuAdcTouch->y_range) ? psNuAdcTouch->y_range : pPoint[i].y_coordinate;
    }
    return (rt_size_t)i;
}

static rt_err_t nu_adc_touch_control(struct rt_touch_device *device, int cmd, void *data)
{
    nu_adc_touch_t psNuAdcTouch = (nu_adc_touch_t)device;
    RT_ASSERT(psNuAdcTouch != RT_NULL);

    switch (cmd)
    {
    case RT_TOUCH_CTRL_SET_X_RANGE: /* set x range */
        psNuAdcTouch->x_range = *((rt_int32_t *)data);
        break;

    case RT_TOUCH_CTRL_SET_Y_RANGE: /* set y range */
        psNuAdcTouch->y_range = *((rt_int32_t *)data);
        break;

    case RT_TOUCH_CTRL_ENABLE_INT: /* enable pen_down interrupt */
        nu_adc_touch_detect(RT_TRUE);
        break;

    case RT_TOUCH_CTRL_DISABLE_INT: /* disable pen_down interrupt */
        nu_adc_touch_detect(RT_FALSE);
        break;

    case RT_TOUCH_CTRL_POWER_ON:    /* Touch Power On */
        return nu_adc_touch_enable(device);

    case RT_TOUCH_CTRL_POWER_OFF:   /* Touch Power Off */
        return nu_adc_touch_disable();

    default:
        return -RT_ERROR;
    }
    return RT_EOK;
}

static struct rt_touch_ops touch_ops =
{
    .touch_readpoint = nu_adc_touch_readpoint,
    .touch_control = nu_adc_touch_control,
};

void nu_adc_touch_update_caldata(int *psi32NewValue)
{
    rt_memcpy(&cal_data_a[0], &psi32NewValue[0], sizeof(cal_data_a));
}

void nu_adc_touch_reset_caldata(int *psi32NewValue)
{
    rt_memcpy(&cal_data_a[0], &cal_zero[0], sizeof(cal_data_a));
}

int rt_hw_adc_touch_init(void)
{
    /* Register touch device */
    s_NuAdcTouch.dev.info.type = RT_TOUCH_TYPE_RESISTANCE;
    s_NuAdcTouch.dev.info.vendor = RT_TOUCH_VENDOR_UNKNOWN;
    s_NuAdcTouch.dev.info.point_num = 1;
    s_NuAdcTouch.dev.info.range_x = LCM_WIDTH;
    s_NuAdcTouch.dev.info.range_y = LCM_HEIGHT;

    s_NuAdcTouch.dev.ops = &touch_ops;

    return (int)rt_hw_touch_register(&s_NuAdcTouch.dev, "adc_touch", RT_DEVICE_FLAG_INT_RX, RT_NULL);
}
INIT_DEVICE_EXPORT(rt_hw_adc_touch_init);


static rt_thread_t  adc_touch_thread = RT_NULL;
static rt_sem_t     adc_touch_sem = RT_NULL;
static int          adc_touch_worker_run = 0;
static rt_err_t adc_touch_rx_callback(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(adc_touch_sem);
    return 0;
}

static void adc_touch_entry(void *parameter)
{
    struct rt_touch_data touch_point;

    rt_err_t result;
    rt_device_t pdev = &s_NuAdcTouch.dev.parent;

    int max_range;

    adc_touch_sem = rt_sem_create("adc_touch_sem", 0, RT_IPC_FLAG_FIFO);
    RT_ASSERT(adc_touch_sem != RT_NULL);

    result = rt_device_open(pdev, RT_DEVICE_FLAG_INT_RX);
    RT_ASSERT(result == RT_EOK);

    result = rt_device_set_rx_indicate(pdev, adc_touch_rx_callback);
    RT_ASSERT(result == RT_EOK);

    max_range = LCM_WIDTH;
    result = rt_device_control(pdev, RT_TOUCH_CTRL_SET_X_RANGE, (void *)&max_range);
    RT_ASSERT(result == RT_EOK);

    max_range = LCM_HEIGHT;
    result = rt_device_control(pdev, RT_TOUCH_CTRL_SET_Y_RANGE, (void *)&max_range);
    RT_ASSERT(result == RT_EOK);

    // nu_adc_touch_reset_caldata(int *psi32NewValue);
    // nu_adc_touch_update_caldata(int *psi32NewValue);

    result = rt_device_control(pdev, RT_TOUCH_CTRL_POWER_ON, RT_NULL);
    RT_ASSERT(result == RT_EOK);

    while (adc_touch_worker_run)
    {
        if ((-RT_ETIMEOUT == rt_sem_take(adc_touch_sem, rt_tick_from_millisecond(100))))
            continue;

        rt_memset(&touch_point, 0, sizeof(struct rt_touch_data));

        if (rt_device_read(pdev, 0, &touch_point, s_NuAdcTouch.dev.info.point_num) == s_NuAdcTouch.dev.info.point_num)
        {
            if (touch_point.event == RT_TOUCH_EVENT_DOWN
                    || touch_point.event == RT_TOUCH_EVENT_UP
                    || touch_point.event == RT_TOUCH_EVENT_MOVE)
            {

#if defined(PKG_USING_LVGL)
                extern void nu_touch_inputevent_cb(rt_int16_t x, rt_int16_t y, rt_uint8_t state);
                nu_touch_inputevent_cb(touch_point.x_coordinate, touch_point.y_coordinate, touch_point.event);
#elif defined(PKG_USING_LITTLEVGL2RTT)
                extern void littlevgl2rtt_send_input_event(rt_int16_t x, rt_int16_t y, rt_uint8_t state);
                littlevgl2rtt_send_input_event(touch_point.x_coordinate, touch_point.y_coordinate, touch_point.event);
#endif

#if defined(PKG_USING_NUEMWIN)
                extern void nuemwin_send_input_event(rt_int16_t x, rt_int16_t y, rt_uint8_t state);
                nuemwin_send_input_event(touch_point.x_coordinate, touch_point.y_coordinate, touch_point.event);
#endif
                rt_kprintf("[%d-%d] id=%d width=%d x=%d y=%d\n",
                           touch_point.timestamp,
                           touch_point.event,
                           touch_point.track_id,
                           touch_point.width,
                           touch_point.x_coordinate,
                           touch_point.y_coordinate);
            }
        }
    }

    result = rt_device_control(pdev, RT_TOUCH_CTRL_POWER_OFF, RT_NULL);
    RT_ASSERT(result == RT_EOK);

    result = rt_device_close(pdev);
    RT_ASSERT(result == RT_EOK);
}


/* Support "nu_touch_start" command line in msh mode */
static rt_err_t nu_touch_start(int argc, char **argv)
{
    if (adc_touch_thread == RT_NULL)
    {
        adc_touch_thread = rt_thread_create("adc_touch_thread",
                                            adc_touch_entry,
                                            RT_NULL,
                                            1024,
                                            25,
                                            5);
        adc_touch_worker_run = 1;
        if (adc_touch_thread != RT_NULL)
            rt_thread_startup(adc_touch_thread);
    }
    return 0;
}
MSH_CMD_EXPORT(nu_touch_start, e.g: start adc touch);

/* Support "nu_touch_stop" command line in msh mode */
static rt_err_t nu_touch_stop(int argc, char **argv)
{
    adc_touch_worker_run = 0;
    adc_touch_thread = RT_NULL;
    return 0;
}
MSH_CMD_EXPORT(nu_touch_stop, e.g: stop adc touch);

#endif //#if defined(BSP_USING_ADC_TOUCH)
