#include <rtthread.h>
#include <rtdevice.h>
#include "drv_pin.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_inputmux.h"
#include "fsl_gpio.h"
#include <stdbool.h>
#include "fsl_reset.h"
#include "fsl_ctimer.h"

#define HWTIMER_DEV_NAME "timer0" /* device name */
#define HWTIMER_DEV2_NAME "timer1" /* device name */

#define THREAD_PRIORITY         25
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        5
static rt_thread_t tid1 = RT_NULL;
static rt_thread_t tid2 = RT_NULL;
rt_uint8_t timeout_flag = 0;
rt_uint8_t timeout2_flag = 0;
static rt_bool_t led_state = RT_FALSE;        /* Current LED state */
#define LED_PIN        ((3*32)+18)  /* Original LED pin */

static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
//    rt_kprintf("this is hwtimer timeout callback fucntion!\n");
//    rt_kprintf("tick is :%d !\n", rt_tick_get());
		
	  timeout_flag = 1;
		
    return 0;
}

int test_hwtimer()
{
    rt_err_t ret = RT_EOK;
    rt_hwtimerval_t timeout_s;
    rt_device_t hw_dev = RT_NULL;
    rt_hwtimer_mode_t mode;
    rt_uint32_t freq = 10000000;
		
    hw_dev = rt_device_find(HWTIMER_DEV_NAME);
	  rt_kprintf("find device success,device=%x\r\n",hw_dev);
    if (hw_dev == RT_NULL)
    {
        rt_kprintf("hwtimer sample run failed! can't find %s device!\n", HWTIMER_DEV_NAME);
        return -RT_ERROR;
    }
		
    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
		rt_kprintf("open device success\r\n");
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", HWTIMER_DEV_NAME);
        return ret;
    }

    rt_device_set_rx_indicate(hw_dev, timeout_cb);

    rt_device_control(hw_dev, HWTIMER_CTRL_FREQ_SET, &freq);

    mode = HWTIMER_MODE_PERIOD;
    ret = rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);
    if (ret != RT_EOK)
    {
        rt_kprintf("set mode failed! ret is :%d\n", ret);
        return ret;
    }

    /* Example Set the timeout period of the timer */
    timeout_s.sec = 3;  /* secend */
    timeout_s.usec = 0; /* microsecend */
    if (rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s)) != sizeof(timeout_s))
    {
        rt_kprintf("set timeout value failed\n");
        return -RT_ERROR;
    }
		rt_kprintf("init success\r\n");
    while (1)
    {
        //rt_thread_mdelay(3000);
			  if(timeout_flag)
				{
					timeout_flag = 0;
					rt_hwtimer_t *timer = (rt_hwtimer_t *)hw_dev;
					rt_device_read(hw_dev, 0, &timeout_s, sizeof(timeout_s));
					rt_uint32_t timer_start = timer->ops->count_get(timer);
					rt_kprintf("Read: Sec = %d, Usec = %d \r\n", timeout_s.sec, timeout_s.usec);
					rt_uint32_t timer_end = timer->ops->count_get(timer);
					rt_kprintf("printf elapse: %d us,start:%d end:%d\n", (timer_end - timer_start)/10,timer_start,timer_end);
				}
    }
    return ret;
}
MSH_CMD_EXPORT(test_hwtimer, hwtimer sample);



static rt_err_t timeout_cb2(rt_device_t dev, rt_size_t size)
{
//    rt_kprintf("this is hwtimer timeout callback fucntion!\n");
//    rt_kprintf("tick is :%d !\n", rt_tick_get());
		timeout2_flag = 1;
    return 0;
}

int test_hwtimer2()
{
    rt_err_t ret = RT_EOK;
    rt_hwtimerval_t timeout_s;
    rt_device_t hw_dev = RT_NULL;
    rt_hwtimer_mode_t mode;
    rt_uint32_t freq = 100000;
		
    hw_dev = rt_device_find(HWTIMER_DEV2_NAME);
	  rt_kprintf("find device2 success,device=%x\r\n",hw_dev);
    if (hw_dev == RT_NULL)
    {
        rt_kprintf("hwtimer sample run failed! can't find %s device!\n", HWTIMER_DEV_NAME);
        return -RT_ERROR;
    }
		
    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
		rt_kprintf("open device2 success\r\n");
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", HWTIMER_DEV_NAME);
        return ret;
    }

    rt_device_set_rx_indicate(hw_dev, timeout_cb2);

    rt_device_control(hw_dev, HWTIMER_CTRL_FREQ_SET, &freq);

    mode = HWTIMER_MODE_PERIOD;
    ret = rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);
    if (ret != RT_EOK)
    {
        rt_kprintf("set mode failed! ret is :%d\n", ret);
        return ret;
    }

    /* Example Set the timeout period of the timer */
    timeout_s.sec = 0;  /* secend */
    timeout_s.usec = 100000; /* microsecend */
    if (rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s)) != sizeof(timeout_s))
    {
        rt_kprintf("set timeout value failed\n");
        return -RT_ERROR;
    }
		rt_kprintf("init device2  success\r\n");
    while (1)
    {
        //rt_thread_mdelay(3000);
			  if(timeout2_flag)
				{
					timeout2_flag = 0;
						/* Toggle LED state */
					led_state = !led_state;

					rt_pin_write(LED_PIN, led_state ? PIN_HIGH : PIN_LOW);
				}
    }
    return ret;
}

static void thread1_entry(void *parameter)
{
    test_hwtimer();
}

static void thread2_entry(void *parameter)
{
    test_hwtimer2();
}


int create_tester_hwtimer_thread(void)
{
    //* CTimer functional clock needs to be greater than or equal to SYSTEM_CLK */
    CLOCK_SetClockDiv(kCLOCK_DivCTIMER0, 1u);
    CLOCK_AttachClk(kFRO_HF_to_CTIMER0);
	
	
    tid1 = rt_thread_create("thread1",
                            thread1_entry, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY, THREAD_TIMESLICE);

    
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);
		
		rt_thread_mdelay(1000);
		CLOCK_SetClockDiv(kCLOCK_DivCTIMER1, 1u);
    CLOCK_AttachClk(kFRO_HF_to_CTIMER1);
		
		tid2 = rt_thread_create("thread2",
                            thread2_entry, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY, THREAD_TIMESLICE);

    
    if (tid2 != RT_NULL)
        rt_thread_startup(tid2);

    return 0;
}