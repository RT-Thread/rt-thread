/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtdevice.h>
#include "board.h"
#include "drv_spi.h"

#ifdef RT_USING_FINSH
#include <finsh.h>

#if defined(BSP_USING_UART1) || defined(BSP_USING_UART2)
static int uart_loop(int argc, char **argv)
{
    static const rt_uint8_t pattern[] = {
        0x55, 0xAA, 0x00, 0xFF, 0x31, 0xC3, 0x7E, 0x81
    };
    rt_uint8_t received[sizeof(pattern)];
    rt_uint8_t discard;
    rt_device_t device;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_size_t length = 0;
    rt_tick_t start;

    if (argc != 2 ||
        (rt_strcmp(argv[1], "uart1") != 0 && rt_strcmp(argv[1], "uart2") != 0))
    {
        rt_kprintf("Usage: uart_loop uart1|uart2\n");
        return -RT_EINVAL;
    }

    device = rt_device_find(argv[1]);
    if (device == RT_NULL)
    {
        rt_kprintf("FAIL: %s is not enabled\n", argv[1]);
        return -RT_ENOSYS;
    }
    if (rt_device_open(device, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_INT_RX) != RT_EOK)
    {
        rt_kprintf("FAIL: cannot open %s\n", argv[1]);
        return -RT_ERROR;
    }
    if (rt_device_control(device, RT_DEVICE_CTRL_CONFIG, &config) != RT_EOK)
    {
        rt_device_close(device);
        rt_kprintf("FAIL: cannot configure %s\n", argv[1]);
        return -RT_ERROR;
    }

    while (rt_device_read(device, 0, &discard, 1) == 1)
    {
    }
    if (rt_device_write(device, 0, pattern, sizeof(pattern)) != sizeof(pattern))
    {
        rt_device_close(device);
        rt_kprintf("FAIL: %s write\n", argv[1]);
        return -RT_EIO;
    }

    start = rt_tick_get();
    while (length < sizeof(pattern) &&
           rt_tick_get() - start < rt_tick_from_millisecond(1000))
    {
        length += rt_device_read(device, 0, &received[length], sizeof(pattern) - length);
        if (length < sizeof(pattern))
        {
            rt_thread_mdelay(1);
        }
    }
    rt_device_close(device);

    if (length != sizeof(pattern) || rt_memcmp(pattern, received, sizeof(pattern)) != 0)
    {
        rt_kprintf("FAIL: %s loopback received %u/%u bytes\n", argv[1],
                   (unsigned int)length, (unsigned int)sizeof(pattern));
        return -RT_EIO;
    }

    rt_kprintf("PASS: %s 115200-8-N-1 loopback\n", argv[1]);
    return RT_EOK;
}
MSH_CMD_EXPORT(uart_loop, test uart1 or uart2 TX to RX loopback);
#endif

#ifdef BSP_USING_I2C0
static int p3t1755(void)
{
    struct rt_i2c_bus_device *bus;
    rt_uint8_t reg = 0;
    rt_uint8_t data[2];
    struct rt_i2c_msg messages[2] = {
        {
            .addr = 0x48,
            .flags = RT_I2C_WR,
            .len = 1,
            .buf = &reg,
        },
        {
            .addr = 0x48,
            .flags = RT_I2C_RD,
            .len = sizeof(data),
            .buf = data,
        },
    };
    rt_int32_t sixteenths;
    rt_uint32_t magnitude;

    bus = rt_i2c_bus_device_find("i2c0");
    if (bus == RT_NULL || rt_i2c_transfer(bus, messages, 2) != 2)
    {
        rt_kprintf("FAIL: P3T1755 did not acknowledge at 0x48\n");
        return -RT_EIO;
    }

    sixteenths = (rt_int16_t)(((rt_uint16_t)data[0] << 8) | data[1]) / 16;
    magnitude = sixteenths < 0 ? (rt_uint32_t)-sixteenths : (rt_uint32_t)sixteenths;
    rt_kprintf("PASS: P3T1755 0x48 temperature %s%u.%04u C\n",
               sixteenths < 0 ? "-" : "", (unsigned int)(magnitude / 16),
               (unsigned int)((magnitude % 16) * 625));

    return RT_EOK;
}
MSH_CMD_EXPORT(p3t1755, read onboard P3T1755 temperature with repeated START);
#endif

#ifdef BSP_USING_SPI0
static struct rt_spi_device *spi_loop_device;

static int spi_loop(void)
{
    static const rt_uint8_t transmitted[] = {
        0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
        0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF
    };
    struct rt_spi_configuration config = {
        .mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB,
        .data_width = 8,
        .max_hz = 1000000,
    };
    rt_uint8_t received[sizeof(transmitted)];
    struct rt_spi_message second = {
        .send_buf = &transmitted[8],
        .recv_buf = &received[8],
        .length = 8,
        .cs_take = 0,
        .cs_release = 1,
        .next = RT_NULL,
    };
    struct rt_spi_message first = {
        .send_buf = transmitted,
        .recv_buf = received,
        .length = 8,
        .cs_take = 1,
        .cs_release = 0,
        .next = &second,
    };

    if (spi_loop_device == RT_NULL)
    {
        if (rt_hw_spi_device_attach("spi0", "spi0_test", GET_PINS(3, 11)) != RT_EOK)
        {
            rt_kprintf("FAIL: cannot attach spi0_test\n");
            return -RT_ERROR;
        }
        spi_loop_device = (struct rt_spi_device *)rt_device_find("spi0_test");
    }

    if (rt_spi_configure(spi_loop_device, &config) != RT_EOK)
    {
        rt_kprintf("FAIL: cannot configure spi0_test\n");
        return -RT_ERROR;
    }

    if (rt_spi_transfer_message(spi_loop_device, &first) != RT_NULL ||
        rt_memcmp(transmitted, received, sizeof(transmitted)) != 0)
    {
        rt_kprintf("FAIL: spi0 loopback mismatch\n");
        return -RT_EIO;
    }

    rt_kprintf("PASS: spi0 compound data loopback\n");
    return RT_EOK;
}
MSH_CMD_EXPORT(spi_loop, test spi0 SDO to SDI compound loopback);
#endif

#ifdef BSP_USING_WDT
static int wwdt(int argc, char **argv)
{
    rt_device_t device;
    rt_uint32_t timeout = 3;

    if (argc != 2 ||
        (rt_strcmp(argv[1], "refresh") != 0 && rt_strcmp(argv[1], "timeout") != 0))
    {
        rt_kprintf("Usage: wwdt refresh|timeout\n");
        return -RT_EINVAL;
    }

    device = rt_device_find("wdt");
    if (device == RT_NULL || rt_device_open(device, RT_DEVICE_OFLAG_RDWR) != RT_EOK ||
        rt_device_control(device, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout) != RT_EOK ||
        rt_device_control(device, RT_DEVICE_CTRL_WDT_START, RT_NULL) != RT_EOK)
    {
        rt_kprintf("FAIL: cannot start WWDT0\n");
        return -RT_ERROR;
    }

    if (rt_strcmp(argv[1], "timeout") == 0)
    {
        rt_kprintf("WWDT0 is not refreshed; reset is expected in 3 seconds\n");
        rt_thread_mdelay(5000);
        rt_kprintf("FAIL: WWDT0 did not reset the MCU\n");
        return -RT_ERROR;
    }

    rt_kprintf("WWDT0 is refreshed every second; press RESET to stop the test\n");
    while (1)
    {
        rt_device_control(device, RT_DEVICE_CTRL_WDT_KEEPALIVE, RT_NULL);
        rt_thread_mdelay(1000);
    }
}
MSH_CMD_EXPORT(wwdt, test WWDT0 refresh or timeout reset);
#endif

#ifdef BSP_USING_CTIMER1
static volatile rt_uint32_t ctimer_events;

static rt_err_t ctimer_timeout(rt_device_t device, rt_size_t size)
{
    RT_UNUSED(device);
    RT_UNUSED(size);

    ctimer_events++;
    return RT_EOK;
}

static int ctimer_test(int argc, char **argv)
{
    rt_clock_timerval_t timeout = {
        .sec = 0,
        .usec = 100000,
    };
    rt_clock_timer_mode_t mode;
    rt_device_t device;
    rt_uint32_t frequency = 1000000;
    rt_uint32_t minimum;
    rt_uint32_t maximum;
    rt_err_t result;

    if (argc != 3 || rt_strcmp(argv[1], "timer1") != 0 ||
        (rt_strcmp(argv[2], "oneshot") != 0 && rt_strcmp(argv[2], "periodic") != 0))
    {
        rt_kprintf("Usage: ctimer_test timer1 oneshot|periodic\n");
        rt_kprintf("timer0 is reserved for the RT-Thread clock-time backend\n");
        return -RT_EINVAL;
    }

    device = rt_device_find(argv[1]);
    if (device == RT_NULL || rt_device_open(device, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
    {
        rt_kprintf("FAIL: %s is not enabled\n", argv[1]);
        return -RT_ENOSYS;
    }

    mode = rt_strcmp(argv[2], "oneshot") == 0 ? CLOCK_TIMER_MODE_ONESHOT : CLOCK_TIMER_MODE_PERIOD;
    minimum = mode == CLOCK_TIMER_MODE_ONESHOT ? 1 : 4;
    maximum = mode == CLOCK_TIMER_MODE_ONESHOT ? 1 : 6;
    ctimer_events = 0;
    rt_device_set_rx_indicate(device, ctimer_timeout);

    result = rt_device_control(device, CLOCK_TIMER_CTRL_FREQ_SET, &frequency);
    if (result == RT_EOK)
    {
        result = rt_device_control(device, CLOCK_TIMER_CTRL_MODE_SET, &mode);
    }
    if (result == RT_EOK &&
        rt_device_write(device, 0, &timeout, sizeof(timeout)) != sizeof(timeout))
    {
        result = -RT_EIO;
    }
    if (result == RT_EOK)
    {
        rt_thread_mdelay(mode == CLOCK_TIMER_MODE_ONESHOT ? 350 : 550);
        rt_device_control(device, CLOCK_TIMER_CTRL_STOP, RT_NULL);
    }
    rt_device_set_rx_indicate(device, RT_NULL);
    rt_device_close(device);

    if (result != RT_EOK || ctimer_events < minimum || ctimer_events > maximum)
    {
        rt_kprintf("FAIL: %s %s generated %u interrupts\n", argv[1], argv[2],
                   (unsigned int)ctimer_events);
        return -RT_ERROR;
    }

    rt_kprintf("PASS: %s %s generated %u interrupt(s)\n", argv[1], argv[2],
               (unsigned int)ctimer_events);
    return RT_EOK;
}
MSH_CMD_EXPORT(ctimer_test, test CTIMER1 one - shot or periodic mode);
#endif

#ifdef BSP_USING_CTIMER0
static int ctimer0_test(void)
{
    struct rt_clock_hrtimer timer;
    rt_tick_t start;
    rt_tick_t elapsed;
    rt_err_t result;

    rt_clock_hrtimer_delay_init(&timer);
    start = rt_tick_get();
    result = rt_clock_hrtimer_start(&timer, rt_clock_time_get_freq() / 10U);
    if (result == RT_EOK)
    {
        result = rt_completion_wait(&timer.completion, rt_tick_from_millisecond(1000));
    }
    elapsed = rt_tick_get() - start;
    if (result != RT_EOK)
    {
        rt_clock_hrtimer_stop(&timer);
    }
    rt_clock_hrtimer_delay_detach(&timer);

    if (result != RT_EOK || elapsed < rt_tick_from_millisecond(90) ||
        elapsed > rt_tick_from_millisecond(200))
    {
        rt_kprintf("FAIL: timer0 clock-time one-shot took %u ticks\n",
                   (unsigned int)elapsed);
        return -RT_ERROR;
    }

    rt_kprintf("PASS: timer0 clock-time one-shot took %u ticks\n",
               (unsigned int)elapsed);
    return RT_EOK;
}
MSH_CMD_EXPORT(ctimer0_test, test CTIMER0 through the RT - Thread clock - time backend);
#endif

#if defined(BSP_USING_RTC) && defined(RT_USING_ALARM)
static struct rt_completion rtc_alarm_completion;

static void rtc_alarm_callback(rt_alarm_t alarm, time_t timestamp)
{
    RT_UNUSED(alarm);
    RT_UNUSED(timestamp);

    rt_completion_done(&rtc_alarm_completion);
}

static int rtc_alarm_test(void)
{
    struct rt_alarm_setup setup = {
        .flag = RT_ALARM_ONESHOT,
    };
    rt_device_t device;
    rt_alarm_t alarm;
    time_t timestamp;
    rt_err_t result;

    device = rt_device_find("rtc");
    if (device == RT_NULL || rt_device_open(device, RT_DEVICE_OFLAG_RDWR) != RT_EOK ||
        get_timestamp(&timestamp) != RT_EOK)
    {
        rt_kprintf("FAIL: cannot open rtc\n");
        return -RT_ERROR;
    }

    timestamp += 3;
#ifdef RT_ALARM_USING_LOCAL_TIME
    localtime_r(&timestamp, &setup.wktime);
#else
    gmtime_r(&timestamp, &setup.wktime);
#endif
    rt_completion_init(&rtc_alarm_completion);
    alarm = rt_alarm_create(rtc_alarm_callback, &setup);
    if (alarm == RT_NULL)
    {
        rt_kprintf("FAIL: cannot create RTC0 alarm\n");
        rt_device_close(device);
        return -RT_ERROR;
    }
    if (rt_alarm_start(alarm) != RT_EOK)
    {
        rt_kprintf("FAIL: cannot start RTC0 alarm\n");
        rt_alarm_delete(alarm);
        rt_device_close(device);
        return -RT_ERROR;
    }

    result = rt_completion_wait(&rtc_alarm_completion, rt_tick_from_millisecond(6000));
    rt_alarm_delete(alarm);
    rt_device_close(device);
    rt_kprintf("%s: RTC0 one-shot alarm\n", result == RT_EOK ? "PASS" : "FAIL");

    return result;
}
MSH_CMD_EXPORT(rtc_alarm_test, test RTC0 one - shot alarm after 3 seconds);
#endif

#endif /* RT_USING_FINSH */
