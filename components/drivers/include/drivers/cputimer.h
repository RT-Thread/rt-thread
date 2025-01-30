/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-02-13     zhkag           first version
 * 2025-01-30     wumingzi        add doxygen comment
 */

#ifndef CPUTIMER_H__
#define CPUTIMER_H__

#include <rtthread.h>

/**
 * @addtogroup  Drivers                 RTTHREAD Driver
 * @defgroup    cputimer                cputimer
 * @brief       cputimer driver api
 * @ingroup     Drivers
 * @addtogroup  cputimer
 *
 * @note Cputimer, a highly precise hardware clock, is essential to implement in
         the BSP if you intend to use it in your application.
 *
 * Example for implementing driver
 *
 * @code
 *
 * #include <rthw.h>
 * #include <rtdevice.h>
 * #include <rtthread.h>
 *
 * #include <board.h>
 *
 * #define HWTIMER_DEV_NAME   "timer7"
 *
 * rt_uint64_t count = 0;
 *
 * rt_uint64_t timeout_tick = 0;
 *
 * void (*hwtimer_timeout)(void *param);
 * void *parameter = RT_NULL;
 *
 * static double cortexm_cputime_getres(void)
 * {
 *     return 10000;
 * }
 *
 * static uint64_t cortexm_cputime_gettime(void)
 * {
 *     return count;
 * }
 *
 * static int cortexm_cputime_settimeout(uint64_t tick, void (*timeout)(void *param), void *param)
 * {
 *     timeout_tick = tick;
 *     hwtimer_timeout = timeout;
 *     parameter = param;
 *     return 0;
 * }
 *
 * const static struct rt_clock_cputime_ops _cortexm_ops =
 * {
 *     cortexm_cputime_getres,
 *     cortexm_cputime_gettime,
 *     cortexm_cputime_settimeout
 * };
 *
 * int cortexm_cputime_init(void)
 * {
 *     clock_cpu_setops(&_cortexm_ops);
 *     return 0;
 * }
 * INIT_BOARD_EXPORT(cortexm_cputime_init);
 *
 * static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
 * {
 *     count++;
 *     if(count == timeout_tick)
 *     {
 *         timeout_tick = 0;
 *         if(hwtimer_timeout != RT_NULL)
 *             hwtimer_timeout(parameter);
 *     }
 *     return 0;
 * }
 *
 * static int hwtimer_init()
 * {
 *     rt_err_t ret = RT_EOK;
 *     rt_hwtimerval_t timeout_s;
 *     rt_device_t hw_dev = RT_NULL;
 *     rt_hwtimer_mode_t mode;
 *     rt_uint32_t freq = 1000000;
 *
 *     hw_dev = rt_device_find(HWTIMER_DEV_NAME);
 *     if (hw_dev == RT_NULL)
 *     {
 *         _cortexm_ops.cputime_settimeout = RT_NULL;
 *         rt_kprintf("hwtimer sample run failed! can't find %s device!\n", HWTIMER_DEV_NAME);
 *         return -RT_ERROR;
 *     }
 *
 *     ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
 *     if (ret != RT_EOK)
 *     {
 *         _cortexm_ops.cputime_settimeout = RT_NULL;
 *         rt_kprintf("open %s device failed!\n", HWTIMER_DEV_NAME);
 *         return ret;
 *     }
 *     rt_device_set_rx_indicate(hw_dev, timeout_cb);
 *
 *     rt_device_control(hw_dev, HWTIMER_CTRL_FREQ_SET, &freq);
 *     mode = HWTIMER_MODE_PERIOD;
 *     ret = rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);
 *     if (ret != RT_EOK)
 *     {
 *         _cortexm_ops.cputime_settimeout = RT_NULL;
 *         rt_kprintf("set mode failed! ret is :%d\n", ret);
 *         return ret;
 *     }
 *     timeout_s.sec = 0;
 *     timeout_s.usec = 10;
 *
 *     if (rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s)) != sizeof(timeout_s))
 *     {
 *         _cortexm_ops.cputime_settimeout = RT_NULL;
 *         rt_kprintf("set timeout value failed\n");
 *         return -RT_ERROR;
 *     }
 *     return ret;
 * }
 * INIT_APP_EXPORT(hwtimer_init);
 * @endcode
 *
 * @{
 */

/**
 * @brief   Cputimer structure
 *
 */
struct rt_cputimer
{
    struct rt_object parent; /**< inherit from rt_object */
    rt_list_t row;
    void (*timeout_func)(void *parameter);
    void *parameter;
    rt_uint64_t init_tick;
    rt_uint64_t timeout_tick;
    struct rt_semaphore sem;
};
typedef struct rt_cputimer *rt_cputimer_t;

rt_err_t rt_cputimer_detach(rt_cputimer_t timer);

#ifdef RT_USING_HEAP
void rt_cputimer_init(rt_cputimer_t timer,
                      const char *name,
                      void (*timeout)(void *parameter),
                      void *parameter,
                      rt_uint64_t tick,
                      rt_uint8_t flag);
rt_err_t rt_cputimer_delete(rt_cputimer_t timer);
#endif

rt_err_t rt_cputimer_start(rt_cputimer_t timer);
rt_err_t rt_cputimer_stop(rt_cputimer_t timer);
rt_err_t rt_cputimer_control(rt_cputimer_t timer, int cmd, void *arg);
rt_err_t rt_cputime_sleep(rt_uint64_t tick);
rt_err_t rt_cputime_ndelay(rt_uint64_t ns);
rt_err_t rt_cputime_udelay(rt_uint64_t us);
rt_err_t rt_cputime_mdelay(rt_uint64_t ms);

#endif
/*! @}*/