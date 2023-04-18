/*
 * File      : test_driver.h
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <string.h>
#include <drivers/hwtimer.h>
#include <raspi.h>
#include <sys/time.h>

#ifdef BSP_USING_HDMI
#include "drv_fb.h"
#endif

void test_hdmi()
{
    rt_kprintf("Hello Test hdmi!\n");
#ifdef BSP_USING_HDMI
    print_fb_info();
#ifdef BSP_USING_HDMI_DISPLAY
    rt_kprintf("hdmi is tested!\n");
#else
    rt_console_set_device("hdmi");
    rt_kprintf("hdmi is testing!\n");
#endif
    rt_kprintf("search hdmi device");
    rt_device_t hdmi = rt_device_find("hdmi");
    if (hdmi == RT_NULL)
    {
        rt_kprintf("cannot find hdmi device");
    }
    int color = COLOR_YELLOW;
    rt_kprintf("begin test hdmi deivice");
    rt_graphix_ops(hdmi) -> set_pixel((char *)&color, 5, 5);

    rt_graphix_ops(hdmi) -> get_pixel((char *)&color, 5, 5);
    rt_kprintf("color is %x\n",color);
    rt_graphix_ops(hdmi) -> draw_hline((char *)&color, 10, 100, 10);
    color = COLOR_GREEN;
    rt_graphix_ops(hdmi) -> draw_vline((char *)&color, 10, 10, 100);
    int colors[100];
    int i=0;
    for (; i < 20; i++)  colors[i] = COLOR_RED;
    rt_graphix_ops(hdmi) -> blit_line((char *)colors, 20, 20, 20);

#endif
}

#ifdef RT_USING_SMP
#define _CPUS_NR                RT_CPUS_NR
#else
#define _CPUS_NR                1
#endif

#ifdef RT_USING_SMP
static rt_uint8_t rt_thread_stack[_CPUS_NR][128];
static struct rt_thread smp[_CPUS_NR];
void smp_test_entry()
{
    rt_kprintf("cpu %d is running.\n",rt_hw_cpu_id());
}
#endif

void test_cpusmp(void)
{
    rt_kprintf("Hello Test SMP!\n");
#ifdef RT_USING_SMP
    int i;
    char test_name[RT_NAME_MAX];
    for (i = 0; i < _CPUS_NR; i++)
    {
        rt_sprintf(test_name, "smp%d", i);
        rt_thread_init(&smp[i],
                test_name,
                smp_test_entry,
                RT_NULL,
                &rt_thread_stack[i][0],
                sizeof(rt_thread_stack[i]),
                RT_THREAD_PRIORITY_MAX - 2,
                32);
        rt_thread_control(&smp[i], RT_THREAD_CTRL_BIND_CPU, (void*)i);
        /* startup */
        rt_thread_startup(&smp[i]);
        rt_thread_delay(RT_TICK_PER_SECOND);
    }
#endif
}

#ifdef BSP_USING_PIN
#define TEST_PIN_OUT 33
#define TEST_PIN_IN 37

void gpio_rising_test()
{
     rt_kprintf("gpio rising irq function ok!\n");
}
#endif

void test_gpio(void)
{
#ifdef BSP_USING_PIN
    rt_uint32_t ret;
    rt_kprintf("Hello Test GPIO!\n");

    rt_pin_mode(TEST_PIN_OUT, PIN_MODE_OUTPUT);
    rt_pin_write(TEST_PIN_OUT, PIN_HIGH);
    rt_pin_mode(TEST_PIN_IN, PIN_MODE_INPUT);

    ret = rt_pin_read(TEST_PIN_IN);
    rt_kprintf("common high input test read result: %d\n",ret);

    rt_pin_write(TEST_PIN_OUT, PIN_LOW);
    ret = rt_pin_read(TEST_PIN_IN);
    rt_kprintf("common low input test read result: %d\n",ret);

    rt_pin_mode(TEST_PIN_IN, PIN_MODE_INPUT_PULLDOWN);
    rt_pin_attach_irq(TEST_PIN_IN, PIN_IRQ_MODE_RISING, gpio_rising_test, RT_NULL);
    rt_pin_irq_enable(TEST_PIN_IN, PIN_IRQ_ENABLE);
    rt_pin_write(TEST_PIN_OUT, PIN_HIGH);

    rt_pin_irq_enable(TEST_PIN_IN, PIN_IRQ_DISABLE);
#endif
}

#ifdef BSP_USING_I2C1
#define DS3231_I2C_BUS_NAME      "i2c1"
#define DS3231_ADDR               0x68
struct rt_i2c_bus_device *i2c_bus = RT_NULL;
static rt_err_t read_regs(struct rt_i2c_bus_device *bus, rt_uint8_t len, rt_uint8_t *buf)
{
    struct rt_i2c_msg msgs;
    msgs.addr = DS3231_ADDR;
    msgs.flags = RT_I2C_RD;
    msgs.buf = buf;
    msgs.len = len;

    if (rt_i2c_transfer(bus, &msgs, 1) == 1)
        return RT_EOK;
    else
        return -RT_ERROR;
}
#endif

void test_i2c(void)
{
#ifdef BSP_USING_I2C1
    rt_kprintf("Hello Test I2C!\n");
    char name[RT_NAME_MAX];
    rt_uint8_t  buf[]={0x00,0x00,0x43,0x15,0x05,0x01,0x03,0x19};

    rt_strncpy(name, DS3231_I2C_BUS_NAME, RT_NAME_MAX);
    i2c_bus = (struct rt_i2c_bus_device *)rt_device_find(name);
    if (i2c_bus == RT_NULL)
        rt_kprintf("can't find %s device!\n", name);
    else
    {
        read_regs(i2c_bus, 7, buf);
        buf[0] = buf[0]&0x7F; //sec
        buf[1] = buf[1]&0x7F; //min
        buf[2] = buf[2]&0x3F; //hour
        buf[3] = buf[3]&0x07; //week
        buf[4] = buf[4]&0x3F; //day
        buf[5] = buf[5]&0x1F; //mouth
        //year/month/day
        rt_kprintf("20%02x-%02x-%02x ",buf[6],buf[5],buf[4]);
        //hour:minute/second
        rt_kprintf("%02x:%02x:%02x \n",buf[2],buf[1],buf[0]);
    }
#endif
}

#define W25Q_SPI_DEVICE_NAME     "spi0.0"
void test_spi(void)
{
#ifdef BSP_USING_SPI
    rt_kprintf("Hello Test SPI!\n");
    struct rt_spi_device *spi0_dev0;
    struct rt_spi_device *spi0_dev1;

    char name0[RT_NAME_MAX];
    char name1[RT_NAME_MAX];

    rt_uint8_t w25x_read_id = 0x90;
    rt_uint8_t id[5] = {0};

    rt_strncpy(name0, "spi0.0", RT_NAME_MAX);
    rt_strncpy(name1, "spi0.1", RT_NAME_MAX);

    spi0_dev0 = (struct rt_spi_device *)rt_device_find(name0);
    spi0_dev1 = (struct rt_spi_device *)rt_device_find(name1);


    if (!spi0_dev0 || !spi0_dev1)
    {
        rt_kprintf("spi sample run failed! can't find %s device!\n", name0);
    }
    else
    {
        struct rt_spi_message msg1, msg2;

        msg1.send_buf   = &w25x_read_id;
        msg1.recv_buf   = RT_NULL;
        msg1.length     = 1;
        msg1.cs_take    = 1;
        msg1.cs_release = 0;
        msg1.next       = &msg2;

        msg2.send_buf   = RT_NULL;
        msg2.recv_buf   = id;
        msg2.length     = 5;
        msg2.cs_take    = 0;
        msg2.cs_release = 1;
        msg2.next       = RT_NULL;

        rt_spi_transfer_message(spi0_dev0, &msg1);
        rt_kprintf("use rt_spi_transfer_message() read w25q ID is:%x%x\n", id[3], id[4]);

    }
#endif
}

#ifdef BSP_USING_SYSTIMER
#define TIMER   "timer1"

static rt_err_t timer_timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_kprintf("enter hardware timer isr\n");
    return 0;
}
#endif
rt_err_t test_hwtimer(void)
{
#ifdef BSP_USING_SYSTIMER
    rt_kprintf("Hello Test HW Timer!\n");
    rt_err_t err;
    rt_hwtimerval_t val;
    rt_device_t dev = RT_NULL;
    rt_tick_t tick;
    rt_hwtimer_mode_t mode;
    int t = 5;

    if ((dev = rt_device_find(TIMER)) == RT_NULL)
    {
        rt_kprintf("No Device: %s\n", TIMER);
        return -1;
    }

    if (rt_device_open(dev, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
    {
        rt_kprintf("Open %s Fail\n", TIMER);
        return -1;
    }

    mode = HWTIMER_MODE_PERIOD;
    err = rt_device_control(dev, HWTIMER_CTRL_MODE_SET, &mode);

    tick = rt_tick_get();
    rt_kprintf("Start Timer> Tick: %d\n", tick);

    val.sec = t;
    val.usec = 0;
    rt_kprintf("SetTime: Sec %d, Usec %d\n", val.sec, val.usec);
    if (rt_device_write(dev, 0, &val, sizeof(val)) != sizeof(val))
    {
        rt_kprintf("SetTime Fail\n");
        goto EXIT;
    }
    rt_kprintf("Sleep %d sec\n", t);
    rt_thread_delay(t*RT_TICK_PER_SECOND);

    err = rt_device_control(dev, HWTIMER_CTRL_STOP, RT_NULL);
    rt_kprintf("Timer Stoped\n");

    rt_device_read(dev, 0, &val, sizeof(val));
    rt_kprintf("Read: Sec = %d, Usec = %d\n", val.sec, val.usec);

    rt_device_set_rx_indicate(dev, timer_timeout_cb);

    mode = HWTIMER_MODE_PERIOD;
    err = rt_device_control(dev, HWTIMER_CTRL_MODE_SET, &mode);

    val.sec = t;
    val.usec = 0;
    rt_kprintf("SetTime: Sec %d, Usec %d\n", val.sec, val.usec);
    if (rt_device_write(dev, 0, &val, sizeof(val)) != sizeof(val))
    {
        rt_kprintf("SetTime Fail\n");
        goto EXIT;
    }

    rt_thread_delay((t *5 + 1)*RT_TICK_PER_SECOND);

EXIT:
    err = rt_device_close(dev);
    rt_kprintf("Close %s\n", TIMER);

    return err;
#endif
}

#ifdef RT_USING_WDT
#define WDT_DEVICE_NAME    "wdg"    /* the name of the watchdog device */
static rt_device_t wdg_dev;         /* handle of the watchdog device */
static void idle_hook(void)
{
    /* Feed the dog in the callback function of the idle thread */
    rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, NULL);
    //rt_kprintf("feed the dog!\n ");
}

rt_err_t test_wdt(void)
{
    rt_kprintf("Hello Test WDT!\n");
    rt_err_t ret = RT_EOK;
    rt_uint32_t timeout = 1;        /* the overflow time */
    char device_name[RT_NAME_MAX];
    rt_strncpy(device_name, WDT_DEVICE_NAME, RT_NAME_MAX);
    /* find the watchdog device based on the device's name and obtain the device handle */
    wdg_dev = rt_device_find(device_name);
    if (!wdg_dev)
    {
        rt_kprintf("find %s failed!\n", device_name);
        return -RT_ERROR;
    }
    /* initialize the device */
    ret = rt_device_init(wdg_dev);
    if (ret != RT_EOK)
    {
        rt_kprintf("initialize %s failed!\n", device_name);
        return -RT_ERROR;
    }
    /* set the overflow time of the watch dog */
    ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
    if (ret != RT_EOK)
    {
        rt_kprintf("set %s timeout failed!\n", device_name);
        return -RT_ERROR;
    }
    /* start the watchdog */
    ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_START, RT_NULL);
    if (ret != RT_EOK)
    {
        rt_kprintf("start %s failed!\n", device_name);
        return -RT_ERROR;
    }
    /* set idle thread callback function */
    rt_thread_idle_sethook(idle_hook);

    return ret;

}
#else
rt_err_t test_wdt(void)
{
    return RT_EOK;
}
#endif

int test_rtc(void)
{
#ifdef BSP_USING_RTC
    rt_kprintf("Hello Test RTC!\n");
    rt_uint8_t i;
    time_t now;

    rt_err_t ret = RT_EOK;

    rt_kprintf("[RTC Test]RTC Test Start...\n");
    rt_thread_delay(RT_TICK_PER_SECOND);
    rt_kprintf("[RTC Test]Set RTC 2017-04-01 12:30:46\n\n");
    rt_thread_delay(RT_TICK_PER_SECOND);

    ret = set_date(2017, 4, 1);
    if (ret != RT_EOK)
    {
        rt_kprintf("[RTC Test]Set RTC Date failed\n");
        return -RT_ERROR;
    }

    rt_thread_delay(RT_TICK_PER_SECOND);

    ret = set_time(12, 30, 46);
    if (ret != RT_EOK)
    {
        rt_kprintf("[RTC Test]Set RTC Time failed\n");
        return -RT_ERROR;
    }

    rt_thread_delay(RT_TICK_PER_SECOND);

    for (i = 0; i < 10; i++)
    {
        rt_kprintf("[RTC Test]Read RTC Date and Time: ");
        now = time(RT_NULL);
        rt_kprintf("%s", ctime(&now));

        rt_thread_delay(RT_TICK_PER_SECOND);
    }

    rt_kprintf("\n");
#endif
    return RT_EOK;
}

void test_device(int argc, char**argv)
{
    if (0 == strcmp(argv[1],"smp"))
    {
        test_cpusmp();
        return;
    }
    if (0 == strcmp(argv[1],"gpio"))
    {
        test_gpio();
        return;
    }

    if (0 == strcmp(argv[1],"i2c"))
    {
        test_i2c();
        return;
    }

    if (0 == strcmp(argv[1],"spi"))
    {
        test_spi();
        return;
    }

    if (0 == strcmp(argv[1],"hwtimer"))
    {
        test_hwtimer();
        return;
    }

    if (0 == strcmp(argv[1],"wdt"))
    {
        test_wdt();
        return;
    }

    if (0 == strcmp(argv[1],"rtc"))
    {
        test_rtc();
        return;
    }
    if (0 == strcmp(argv[1],"hdmi"))
    {
        test_hdmi();
        return;
    }
    rt_kprintf("param err, please entry test_device <smp|gpio|i2c|spi|hwtimer|wdt|rtc|hdmi>\n");
}
MSH_CMD_EXPORT(test_device, sample: test_device <smp|gpio|i2c|spi|hwtimer|wdt|rtc>);
