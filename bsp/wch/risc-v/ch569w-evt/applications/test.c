/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-07-15     Emuzit            first version
 * 2022-07-20     Emuzit            add watchdog test
 * 2022-07-26     Emuzit            add hwtimer test
 * 2022-07-30     Emuzit            add spi master test
 * 2022-08-04     Emuzit            add pwm test
 */
#include <rtthread.h>
#include <drivers/dev_pin.h>
#include "drivers/dev_watchdog.h"
#include <drivers/hwtimer.h>
#include "drivers/dev_spi.h"
#include <drivers/dev_pwm.h>
#include "board.h"

#define PWM_CYCLE_MAX   255

static const rt_base_t gpio_int_pins[8] = GPIO_INT_PINS;

/* note : PIN_IRQ_MODE_RISING_FALLING not supported */
static const uint32_t gpint_mode[] =
{
    PIN_IRQ_MODE_RISING,
    PIN_IRQ_MODE_RISING,
    PIN_IRQ_MODE_RISING,
    PIN_IRQ_MODE_RISING,
    PIN_IRQ_MODE_FALLING,
    PIN_IRQ_MODE_FALLING,
    PIN_IRQ_MODE_FALLING,
    PIN_IRQ_MODE_FALLING,
};

static struct rt_mailbox *gpint_mb = RT_NULL;
static struct rt_thread  *gpint_thread = RT_NULL;

static rt_device_t wdg_dev;

static rt_base_t led0, led1;

static void gpio_int_callback(void *pin)
{
    led1 = (led1 == PIN_LOW) ? PIN_HIGH : PIN_LOW;
    rt_pin_write(LED1_PIN, led1);

    if (gpint_mb != RT_NULL)
    {
        /* non-block, silently ignore RT_EFULL */
        rt_mb_send(gpint_mb, (uint32_t)pin);
    }
}

static void gpio_int_thread(void *param)
{
    while (1)
    {
        rt_err_t res;
        uint32_t pin;

        res = rt_mb_recv(gpint_mb, &pin, RT_WAITING_FOREVER);
        if (res == RT_EOK)
        {
            rt_kprintf("gpio_int #%d (%d)\n", pin, rt_pin_read(pin));
        }
        rt_thread_mdelay(100);

#ifdef RT_USING_WDT
        rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, RT_NULL);
#endif
    }
}

static void test_gpio_int(void)
{
    rt_err_t res;
    int i;

    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(LED1_PIN, led1 = PIN_HIGH);

    /* Enable all gpio interrupt with various modes.
     * LED0 or GND touching can be used to trigger pin interrupt.
    */
    gpint_mb = rt_mb_create("pximb", 8, RT_IPC_FLAG_FIFO);
    if (gpint_mb == RT_NULL)
    {
        rt_kprintf("gpint mailbox create failed !\n");
    }
    else
    {
        gpint_thread = rt_thread_create("pxith", gpio_int_thread, RT_NULL,
                                        512, RT_MAIN_THREAD_PRIORITY, 50);
        if (gpint_thread == RT_NULL)
        {
            rt_kprintf("gpint thread create failed !\n");
        }
        else
        {
            rt_thread_startup(gpint_thread);

            for (i = 0; i < 8; i++)
            {
                rt_base_t pin = gpio_int_pins[i];
#ifdef RT_USING_PWM
                if (pin == PWM0_PIN || pin == PWM1_PIN)
                    continue;
#endif
                rt_pin_mode(pin, PIN_MODE_INPUT_PULLUP);
                res = rt_pin_attach_irq(
                      pin, gpint_mode[i], gpio_int_callback, (void *)pin);
                if (res != RT_EOK)
                {
                    rt_kprintf("rt_pin_attach_irq failed (%d:%d)\n", i, res);
                }
                else
                {
                    rt_pin_irq_enable(pin, PIN_IRQ_ENABLE);
                }
            }
        }
    }
}

#ifdef RT_USING_WDT
static void test_watchdog(uint32_t seconds)
{
    /* Test watchdog with 30s timeout, keepalive with gpio interrupt.
     *
     * CAVEAT: With only 8-bit WDOG_COUNT and fixed clocking at Fsys/524288,
     * watchdog of ch56x may be quite limited with very short timeout.
    */
    seconds = 30;
    wdg_dev = rt_device_find("wdt");
    if (!wdg_dev)
    {
        rt_kprintf("watchdog device not found !\n");
    }
    else if (rt_device_init(wdg_dev) != RT_EOK ||
             rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &seconds) != RT_EOK)
    {
        rt_kprintf("watchdog setup failed !\n");
    }
    else
    {
        rt_kprintf("WDT_TIMEOUT in %d seconds, trigger gpio interrupt to keep alive.\n\n", seconds);
    }
}
#else
    #define test_watchdog(tov)  do {} while(0)
#endif

#ifdef RT_USING_HWTIMER
static struct rt_device *tmr_dev_0;
static struct rt_device *tmr_dev_1;

static rt_err_t tmr_timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_tick_t tick = rt_tick_get();

    int tmr = (dev == tmr_dev_1) ? 1 : 0;

    rt_kprintf("hwtimer %d timeout callback fucntion @tick %d\n", tmr, tick);

    return RT_EOK;
}

static void test_hwtimer(void)
{
    rt_hwtimerval_t timerval;
    rt_hwtimer_mode_t mode;
    rt_size_t tsize;

    /* setup two timers, ONESHOT & PERIOD each
    */
    tmr_dev_0 = rt_device_find("timer0");
    tmr_dev_1 = rt_device_find("timer1");
    if (tmr_dev_0 == RT_NULL || tmr_dev_1 == RT_NULL)
    {
        rt_kprintf("hwtimer device(s) not found !\n");
    }
    else if (rt_device_open(tmr_dev_0, RT_DEVICE_OFLAG_RDWR) != RT_EOK ||
             rt_device_open(tmr_dev_1, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
    {
        rt_kprintf("hwtimer device(s) open failed !\n");
    }
    else
    {
        rt_device_set_rx_indicate(tmr_dev_0, tmr_timeout_cb);
        rt_device_set_rx_indicate(tmr_dev_1, tmr_timeout_cb);

        timerval.sec = 3;
        timerval.usec = 500000;
        tsize = sizeof(timerval);
        mode = HWTIMER_MODE_ONESHOT;
        if (rt_device_control(tmr_dev_0, HWTIMER_CTRL_MODE_SET, &mode) != RT_EOK)
        {
            rt_kprintf("timer0 set mode failed !\n");
        }
        else if (rt_device_write(tmr_dev_0, 0, &timerval, tsize) != tsize)
        {
            rt_kprintf("timer0 start failed !\n");
        }
        else
        {
            rt_kprintf("timer0 started !\n");
        }

        timerval.sec = 5;
        timerval.usec = 0;
        tsize = sizeof(timerval);
        mode = HWTIMER_MODE_PERIOD;
        if (rt_device_control(tmr_dev_1, HWTIMER_CTRL_MODE_SET, &mode) != RT_EOK)
        {
            rt_kprintf("timer1 set mode failed !\n");
        }
        else if (rt_device_write(tmr_dev_1, 0, &timerval, tsize) != tsize)
        {
            rt_kprintf("timer1 start failed !\n");
        }
        else
        {
            rt_kprintf("timer1 started !\n\n");
        }
    }
}
#else
    #define test_hwtimer()  do {} while(0)
#endif

#ifdef RT_USING_SPI
static struct rt_spi_device spi_dev_w25q;

static void test_spi_master(void)
{
    struct rt_spi_configuration cfg;
    struct rt_spi_message msg1, msg2;
    rt_err_t res;

    uint8_t buf[16];
    int i;

    cfg.max_hz = 25 * 1000000;
    cfg.data_width = 8;
    cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB;

    res = rt_spi_bus_attach_device(
          &spi_dev_w25q, W25Q32_SPI_NAME, SPI0_BUS_NAME, (void *)W25Q32_CS_PIN);
    if (res == RT_EOK && rt_spi_configure(&spi_dev_w25q, &cfg) == RT_EOK)
    {
        /* cmd : Read Manufacturer / Device ID (90h) */
        buf[0] = 0x90;
        /* address : 0 */
        buf[1] = buf[2] = buf[3] = 0;
        msg1.send_buf   = buf;
        msg1.recv_buf   = RT_NULL;
        msg1.length     = 4;
        msg1.cs_take    = 1;
        msg1.cs_release = 0;
        msg1.next       = &msg2;

        msg2.send_buf   = RT_NULL;
        msg2.recv_buf   = buf;
        msg2.length     = 2;
        msg2.cs_take    = 0;
        msg2.cs_release = 1;
        msg2.next       = RT_NULL;

        rt_spi_transfer_message(&spi_dev_w25q, &msg1);
        rt_kprintf("use rt_spi_transfer_message() read w25q ID is:%x%x\n", buf[0], buf[1]);

        /* cmd : Read Data (03h)  */
        buf[0] = 0x03;
        /* address : 0 */
        buf[1] = buf[2] = buf[3] = 0;
        msg2.length = 16;
        if (rt_spi_transfer_message(&spi_dev_w25q, &msg1) == RT_NULL)
        {
            rt_kprintf("SPI0 16-byte DMA read :");
            for (i = 0; i < 16; i++)
                rt_kprintf(" %02x", buf[i]);
            rt_kprintf("\n\n");
        }
    }
    else
    {
        rt_kprintf("w25q32 attach/configure failed (%d) !\n", res);
    }
}
#else
    #define test_spi_master()  do {} while(0)
#endif

#ifdef RT_USING_PWM
static struct rt_device_pwm *pwm_dev;
static uint32_t pwm_period;

rt_err_t rt_pwm_get(struct rt_device_pwm *device,
                    struct rt_pwm_configuration *cfg);

static void pwm_tick_hook(void)
{
    uint32_t pulse;

    if (pwm_dev)
    {
        /* PWM.CH3 duty cycle : 0%->100% for every ~2.5 seconds */
        pulse = (rt_tick_get() >> 1) % (PWM_CYCLE_MAX + 1);
        pulse = (pwm_period * pulse + PWM_CYCLE_MAX/2) / PWM_CYCLE_MAX;
        rt_pwm_set_pulse(pwm_dev, 3, pulse);
    }
}

static void test_pwm(void)
{
    struct rt_pwm_configuration cfg;
    uint32_t pulse[4];
    int ch;

    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEVICE_NAME);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("can't find %s device !\n", PWM_DEVICE_NAME);
    }
    else
    {
        /* for HCLK@80MHz, allowed period is 3187 ~ 812812 */
        pwm_period = 800*1000;

        pulse[0] = 100*1000;
        pulse[1] = 400*1000;
        pulse[2] = 600*1000;
        pulse[3] = 0;

        for (ch = 0; ch < PWM_CHANNELS; ch++)
        {
            rt_pwm_set(pwm_dev, ch, pwm_period, pulse[ch]);
            rt_pwm_enable(pwm_dev, ch);

            cfg.channel = ch;
            rt_pwm_get(pwm_dev, &cfg);
            rt_kprintf("pwm%d period set/get : %d/%d\n", ch, pwm_period, cfg.period);
            rt_kprintf("pwm%d pulse  set/get : %d/%d\n\n", ch, pulse[ch], cfg.pulse);
        }

        /* disable PWM.CH0 after 1 second, also start changing CH3 */
        rt_thread_mdelay(1000);
        rt_pwm_disable(pwm_dev, 0);

        /* connect PWM3 (PB.2) to LED2 for a visualized PWM effect */
        rt_pin_mode(LED2_PIN, PIN_MODE_INPUT);
        rt_tick_sethook(pwm_tick_hook);
    }
}
#else
    #define test_pwm()  do {} while(0)
#endif

#ifdef RT_USING_USB_DEVICE
#if !defined(RT_USING_EVENT) || !defined(RT_USING_MESSAGEQUEUE)
    #error "event flag or message queue IPC not enabled"
#endif
static struct rt_thread  *udvcom_thread;
static rt_device_t vcom;

static void usbd_vcom_thread(void *param)
{
    char ch;

    while (1)
    {
        while (rt_device_read(vcom, 0, &ch, 1) != 1)
            rt_thread_delay(1);
        rt_kprintf("(%2d) %02x:%c\n", rt_device_write(vcom, 0, &ch, 1), ch, ch);
        rt_pin_write(LED1_PIN, (ch & 1) ? PIN_LOW : PIN_HIGH);
    }
}

static void test_usbd()
{
    char name[] = "vcom";

    vcom = rt_device_find(name);
    if (vcom && rt_device_open(vcom, RT_DEVICE_FLAG_INT_RX) == RT_EOK)
    {
        rt_kprintf("%s opened\n", name);

        rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
        rt_pin_write(LED1_PIN, PIN_LOW);

        udvcom_thread = rt_thread_create("udvcom", usbd_vcom_thread, vcom,
                                         512, 20, 50);
        if (udvcom_thread != RT_NULL)
            rt_thread_startup(udvcom_thread);
        else
            rt_kprintf("usvcom thread create failed !\n");

        rt_device_write(vcom, 0, name, rt_strlen(name));
    }
}
#else
    #define test_usbd()  do {} while(0)
#endif

void main(void)
{
    uint32_t wdog_timeout = 32;

    rt_kprintf("\nCH569W-R0-1v0, HCLK: %dMHz\n\n", sys_hclk_get() / 1000000);

    test_gpio_int();
    test_watchdog(wdog_timeout);
    test_hwtimer();
    test_spi_master();
    test_pwm();
    test_usbd();

    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(LED0_PIN, led0 = PIN_LOW);

    while (1)
    {
        /* flashing LED0 every 1 second */
        rt_thread_mdelay(500);
        led0 = (led0 == PIN_LOW) ? PIN_HIGH : PIN_LOW;
        rt_pin_write(LED0_PIN, led0);
    }
}
