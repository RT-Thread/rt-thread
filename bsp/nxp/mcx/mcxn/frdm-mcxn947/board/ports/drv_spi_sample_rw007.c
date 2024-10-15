#include <rtthread.h>

#ifdef BSP_USING_RW007
#include <rtdbg.h>
#include <rtdevice.h>
#include <board.h>
#include <spi_wifi_rw007.h>

#define BOARD_RW007_DEVICE_NAME "rw007"

extern void spi_wifi_isr(int vector);

static void rw007_gpio_init(void)
{
    /* Configure IO */
    rt_pin_mode(BOARD_RW007_RST_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(BOARD_RW007_INT_BUSY_PIN, PIN_MODE_INPUT_PULLDOWN);

    /* Reset rw007 and config mode */
    rt_pin_write(BOARD_RW007_RST_PIN, PIN_LOW);

    rt_thread_delay(rt_tick_from_millisecond(100));
    rt_pin_write(BOARD_RW007_RST_PIN, PIN_HIGH);

    /* Wait rw007 ready(exit busy stat) */
    while (!rt_pin_read(BOARD_RW007_INT_BUSY_PIN))
    {
        rt_thread_delay(5);
    }

    rt_thread_delay(rt_tick_from_millisecond(200));
    rt_pin_mode(BOARD_RW007_INT_BUSY_PIN, PIN_MODE_INPUT_PULLUP);
}

int wifi_spi_device_init(void)
{
    int ret = 0;
    char sn_version[32];

    struct rt_spi_device *spi_device = rt_malloc(sizeof(struct rt_spi_device));
    if (!spi_device) return -1;

    rw007_gpio_init();
    ret = rt_spi_bus_attach_device_cspin(spi_device, BOARD_RW007_DEVICE_NAME, BOARD_RW007_SPI_BUS_NAME, BOARD_RW007_CS_PIN, RT_NULL);
    if (ret != RT_EOK) return -2;

    rt_hw_wifi_init("rw007");

    rt_wlan_set_mode(RT_WLAN_DEVICE_STA_NAME, RT_WLAN_STATION);
    rt_wlan_set_mode(RT_WLAN_DEVICE_AP_NAME, RT_WLAN_AP);

    rw007_sn_get(sn_version);
    rt_kprintf("\nrw007  sn: [%s]\n", sn_version);
    rw007_version_get(sn_version);
    rt_kprintf("rw007 ver: [%s]\n\n", sn_version);

    return 0;
}
INIT_APP_EXPORT(wifi_spi_device_init);

static void int_wifi_irq(void *p)
{
    ((void)p);
    spi_wifi_isr(0);
}

void spi_wifi_hw_init(void)
{
    rt_pin_attach_irq(BOARD_RW007_INT_BUSY_PIN, PIN_IRQ_MODE_FALLING, int_wifi_irq, 0);
    rt_pin_irq_enable(BOARD_RW007_INT_BUSY_PIN, RT_TRUE);
}

#endif