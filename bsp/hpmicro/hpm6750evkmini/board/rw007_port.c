
/*
 * Copyright (c) 2022-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include <rtthread.h>

#if defined(RT_USING_WIFI) && defined(BSP_USING_SPI1)
#include <rtdevice.h>
#include <drv_spi.h>
#include <rtt_board.h>
#include <spi_wifi_rw007.h>

#define RW007_AT_MODE   3
#define RW007_SPI_MODE  1

extern void spi_wifi_isr(int vector);


static void rw007_spi_cs_control(uint32_t value)
{
    uint32_t gpio_index = RW007_CS_PIN / 32U;
    uint32_t pin_index = RW007_CS_PIN % 32U;
    if (value != 0)
    {
        RW007_CS_GPIO->DO[gpio_index].SET = (1UL << pin_index);
    }
    else
    {
        RW007_CS_GPIO->DO[gpio_index].CLEAR = (1UL << pin_index);
    }
}

static void rw007_spi_cs_init(void)
{
    HPM_IOC->PAD[RW007_CS_PIN].FUNC_CTL = 0;
    HPM_IOC->PAD[RW007_CS_PIN].PAD_CTL = IOC_PAD_PAD_CTL_DS_SET(7) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);

    uint32_t gpio_index = RW007_CS_PIN / 32U;
    uint32_t pin_index = RW007_CS_PIN % 32U;
    RW007_CS_GPIO->DO[gpio_index].SET = (1UL << pin_index);
    RW007_CS_GPIO->OE[gpio_index].SET = (1UL <<pin_index);
}


static void set_rw007_mode(int mode)
{
    /* Configure IO */
    rt_pin_mode(RW007_RST_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(RW007_INT_BUSY_PIN, PIN_MODE_INPUT_PULLDOWN);

    /* Reset rw007 and config mode */
    rt_pin_write(RW007_RST_PIN, PIN_LOW);
    rt_thread_delay(rt_tick_from_millisecond(100));
    rt_pin_write(RW007_RST_PIN, PIN_HIGH);

    /* Wait rw007 ready(exit busy stat) */
    while(!rt_pin_read(RW007_INT_BUSY_PIN))
    {
    }
    rt_thread_delay(rt_tick_from_millisecond(100));
}

int wifi_spi_device_init(void)
{
    char sn_version[32];
    struct rt_spi_device *spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));

    rw007_spi_cs_init();

    set_rw007_mode(RW007_SPI_MODE);
    rt_hw_spi_device_attach(RW007_SPI_BUS_NAME, "wspi", rw007_spi_cs_control);
    rt_hw_wifi_init("wspi");

    rt_wlan_set_mode(RT_WLAN_DEVICE_STA_NAME, RT_WLAN_STATION);
    rt_wlan_set_mode(RT_WLAN_DEVICE_AP_NAME, RT_WLAN_AP);

    rt_thread_mdelay(2000);
    rw007_sn_get(sn_version);
    rt_kprintf("\nrw007  sn: [%s]\n", sn_version);
    rw007_version_get(sn_version);
    rt_kprintf("rw007 ver: [%s]\n\n", sn_version);

    return 0;
}
INIT_APP_EXPORT(wifi_spi_device_init);

static int rw007_update(void)
{
    rt_device_t device = rt_device_find(RW007_SPI_BUS_NAME);
    struct stm32_spi *hspi = (struct stm32_spi *)device->user_data;
    set_rw007_mode(RW007_AT_MODE);
    return 0;
}
MSH_CMD_EXPORT(rw007_update, rw007_update);

static void int_wifi_irq(void * p)
{
    ((void)p);
    spi_wifi_isr(0);
}

void spi_wifi_hw_init(void)
{
    rt_pin_attach_irq(RW007_INT_BUSY_PIN, PIN_IRQ_MODE_FALLING, int_wifi_irq, 0);
    rt_pin_irq_enable(RW007_INT_BUSY_PIN, RT_TRUE);
}

rt_bool_t spi_wifi_is_busy(void)
{
    return !rt_pin_read(RW007_INT_BUSY_PIN);
}

void spi_wifi_int_cmd(rt_bool_t cmd)
{
    rt_pin_irq_enable(RW007_INT_BUSY_PIN, cmd);
}

#endif /* if defined(RT_USING_WIFI) && defined(BSP_USING_SPI1) */
