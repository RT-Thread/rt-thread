#include <rtthread.h>

#ifdef RW007_NOT_USE_EXAMPLE_DRIVERS
#include <rtdevice.h>
#include <drv_spi.h>
#include <board.h>
#include <spi_wifi_rw007.h>

#define RW007_AT_MODE   3
#define RW007_SPI_MODE  1

#define RW007_RST_PIN       70
#define RW007_INT_BUSY_PIN  69
#define RW007_BOOT0_PIN     19
#define RW007_BOOT1_PIN     103

extern void spi_wifi_isr(int vector);

static void set_rw007_mode(int mode)
{
    /* Configure IO */
    rt_pin_mode(RW007_RST_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(RW007_INT_BUSY_PIN, PIN_MODE_INPUT_PULLDOWN);
    rt_pin_mode(RW007_BOOT0_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(RW007_BOOT1_PIN, PIN_MODE_OUTPUT);

    /* Reset rw007 and config mode */
    rt_pin_write(RW007_RST_PIN, PIN_LOW);
    rt_pin_write(RW007_BOOT0_PIN, mode & 0x01 ? PIN_HIGH : PIN_LOW);
    rt_pin_write(RW007_BOOT1_PIN, mode & 0x02 ? PIN_HIGH : PIN_LOW);
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

    // GPIO_TypeDef *cs_gpiox;
    // uint16_t cs_pin;

    // cs_gpiox = (GPIO_TypeDef *)((rt_base_t)GPIOA + (rt_base_t)(RW007_CS_PIN / 16) * 0x0400UL);
    // cs_pin = (uint16_t)(1 << RW007_CS_PIN % 16);

    set_rw007_mode(RW007_SPI_MODE);
    //rt_hw_spi_device_attach(RW007_SPI_BUS_NAME, "wspi", cs_gpiox, cs_pin);
    //rt_hw_wifi_init("wspi");
    rt_hw_wifi_init(TC_USING_TC_BOARD_SPI);

    rt_wlan_set_mode(RT_WLAN_DEVICE_STA_NAME, RT_WLAN_STATION);
    rt_wlan_set_mode(RT_WLAN_DEVICE_AP_NAME, RT_WLAN_AP);

    rw007_sn_get(sn_version);
    rt_kprintf("\nrw007  sn: [%s]\n", sn_version);
    rw007_version_get(sn_version);
    rt_kprintf("rw007 ver: [%s]\n\n", sn_version);

    return 0;
}
//INIT_APP_EXPORT(wifi_spi_device_init);

rt_err_t rw007_reset(void)
{
    /* Reset rw007 and config mode */
    rt_pin_write(RW007_RST_PIN, PIN_LOW);
    rt_thread_delay(rt_tick_from_millisecond(500));
    rt_pin_write(RW007_RST_PIN, PIN_HIGH);
    return RT_EOK;
}

static int rw007_update(void)
{
    rt_device_t device = rt_device_find("spi1");
    struct stm32_spi *hspi = (struct stm32_spi *)device->user_data;
    __HAL_SPI_DISABLE((SPI_HandleTypeDef *)hspi);
    HAL_SPI_MspDeInit((SPI_HandleTypeDef *)hspi);
    set_rw007_mode(RW007_AT_MODE);
    return 0;
}
MSH_CMD_EXPORT(rw007_update, rw007_update);

static void int_wifi_irq(void * p)
{
    ((void)p);
    if( rt_pin_read(RW007_INT_BUSY_PIN) == PIN_HIGH )
    {
        //rt_kprintf("%d",__LINE__);
        spi_wifi_isr(0);
    }
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

#endif /* RW007_NOT_USE_EXAMPLE_DRIVERS */
