/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-04     RT-Thread    the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <drv_spi.h>
#include <board.h>
#include <drv_pin.h>
#include <spi_wifi_rw007.h>

#define DBG_ENABLE
#define DBG_SECTION_NAME "RW007_PORT"
#define DBG_LEVEL DBG_LOG
#include <rtdbg.h>

#define SPI_BUS_NAME "spi0"
#define SPI_DEV_NAME "spi01"
#define INT_BUSY_PIN GET_PIN(GPIO_PORT_G, GPIO_PIN_4) //PG4
#define RESET_PIN GET_PIN(GPIO_PORT_G, GPIO_PIN_5)    //PF4

#define RW007_WORKING_STATION_MODE

extern void spi_wifi_isr(int vector);

static void rw007_gpio_init(void)
{
    rt_pin_mode(RESET_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(INT_BUSY_PIN, PIN_MODE_INPUT);

    rt_pin_write(RESET_PIN, PIN_LOW);
    rt_thread_delay(rt_tick_from_millisecond(100));
    rt_pin_write(RESET_PIN, PIN_HIGH);

    while (!rt_pin_read(INT_BUSY_PIN))
    {
        rt_thread_delay(5);
    }

    rt_thread_delay(rt_tick_from_millisecond(200)); //Time-delay waiting device activated
    rt_pin_mode(INT_BUSY_PIN, PIN_MODE_INPUT_PULLUP);
}

static void _rw007_int(int argc, char *args[])
{
    int v;

    v = atoi(args[1]);

    rt_pin_mode(RESET_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(RESET_PIN, v);
}
MSH_CMD_EXPORT_ALIAS(_rw007_int, _rw007_int, rw007 int pin);

static void _rw007_reset(void)
{
    rt_pin_mode(RESET_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(RESET_PIN, PIN_LOW);
    rt_thread_delay(rt_tick_from_millisecond(100));
    rt_pin_write(RESET_PIN, PIN_HIGH);
}
MSH_CMD_EXPORT_ALIAS(_rw007_reset, rw007_reset, rw007 reset);

void wifi_init_thread_entry(void *p)
{
    char sn_version[32];

    rw007_gpio_init();

#ifdef PKG_USING_DM9051
    extern int dm9051_auto_init(void);
    dm9051_auto_init();
#endif

    rt_hw_wifi_init(SPI_DEV_NAME);
#ifdef RW007_WORKING_STATION_MODE
    rt_wlan_set_mode(RT_WLAN_DEVICE_STA_NAME, RT_WLAN_STATION);
#else
    rt_wlan_set_mode(RT_WLAN_DEVICE_AP_NAME, RT_WLAN_AP);
#endif

    if (rw007_sn_get(sn_version) != RT_EOK)
    {
        LOG_E("rw007 get sn fail !!!");
    }
    LOG_I("rw007  sn: [%s]", sn_version);

    if (rw007_version_get(sn_version) != RT_EOK)
    {
        LOG_E("rw007 get version fail !!!");
    }
    LOG_I("rw007 ver: [%s]", sn_version);

    rt_thread_mdelay(1000);
}

int rt_rw007_init(void)
{
    rt_thread_t thread = NULL;

    thread = rt_thread_create("wifi_init", wifi_init_thread_entry, NULL, 4096, 15, 10);
    if (thread == NULL)
    {
        return -1;
    }

    return rt_thread_startup(thread);
}
#ifdef BSP_USING_SPI0
INIT_COMPONENT_EXPORT(rt_rw007_init);
// MSH_CMD_EXPORT_ALIAS(rt_rw007_init, rw007_init, rw007 init);
#endif

static void int_wifi_irq(void *p)
{
    ((void)p);
    spi_wifi_isr(0);
}

void spi_wifi_hw_init(void)
{
    rt_pin_mode(INT_BUSY_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(INT_BUSY_PIN, PIN_IRQ_MODE_FALLING, int_wifi_irq, 0);
    rt_pin_irq_enable(INT_BUSY_PIN, RT_TRUE);
}
