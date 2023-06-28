#include <rtthread.h>

#ifdef PKG_USING_RW007
#include <rtdevice.h>
#include <drv_spi.h>
#include <drv_pin.h>
#include <board.h>
#include <spi_wifi_rw007.h>

#ifndef PKG_USING_RW007_LATEST_VERSION
#error "please select rw007 latest version."
#endif

#define RW007_SPI_BUS_NAME    "spi2"
#define RW007_CS_PIN          GET_PIN(1, 29) /* IOMUXC_UART4_RX_DATA_ECSPI2_SS0 IOMUXC_UART4_RX_DATA_GPIO1_IO29 */
#define RW007_INT_BUSY_PIN    GET_PIN(5, 0)  /* IOMUXC_SNVS_SNVS_TAMPER0_GPIO5_IO00 */
#define RW007_RST_PIN         GET_PIN(5, 1)  /* IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01 */

extern void spi_wifi_isr(int vector);

static int rw007_gpio_init(void)
{
    int ret = 0;
    uint8_t errorCnt = 10;
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
        rt_thread_delay(rt_tick_from_millisecond(100));
        if (errorCnt)
        {
            errorCnt--;
        }
        else
        {
            ret = -1;
            break;
        }
    }

    rt_thread_delay(rt_tick_from_millisecond(200));
    rt_pin_mode(RW007_INT_BUSY_PIN, PIN_MODE_INPUT_PULLUP);
    return ret;
}

int wifi_spi_device_init(void)
{
    char sn_version[32];

    if (rw007_gpio_init() == -1)
    {
        rt_hw_wifi_init("rw007 gpio init fault!\n");
        return -1;
    }
    rt_hw_spi_device_attach(RW007_SPI_BUS_NAME, "rw007", RW007_CS_PIN);
    rt_hw_wifi_init("rw007");

    rt_wlan_set_mode(RT_WLAN_DEVICE_STA_NAME, RT_WLAN_STATION);
    rt_wlan_set_mode(RT_WLAN_DEVICE_AP_NAME, RT_WLAN_AP);

    rw007_sn_get(sn_version);
    rt_kprintf("\nrw007  sn: [%s]\n", sn_version);
    rw007_version_get(sn_version);
    rt_kprintf("rw007 ver: [%s]\n\n", sn_version);

#ifdef RW007_DAFAULT_SSID
    rt_wlan_connect(RW007_DAFAULT_SSID, RW007_DAFAULT_PASSWARD);
#endif

    return 0;
}
INIT_APP_EXPORT(wifi_spi_device_init);

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

#endif /* RW007_USING_STM32_DRIVERS */
