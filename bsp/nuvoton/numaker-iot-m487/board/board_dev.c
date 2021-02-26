/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-1-16       Wayne        First version
*
******************************************************************************/

#include <rtdevice.h>
#include <drv_gpio.h>

#if defined(BOARD_USING_STORAGE_SPIFLASH)
#if defined(RT_USING_SFUD)
    #include "spi_flash.h"
    #include "spi_flash_sfud.h"
#endif

#include "drv_qspi.h"

#define W25X_REG_READSTATUS    (0x05)
#define W25X_REG_READSTATUS2   (0x35)
#define W25X_REG_WRITEENABLE   (0x06)
#define W25X_REG_WRITESTATUS   (0x01)
#define W25X_REG_QUADENABLE    (0x02)

static rt_uint8_t SpiFlash_ReadStatusReg(struct rt_qspi_device *qspi_device)
{
    rt_uint8_t u8Val;
    rt_err_t result = RT_EOK;
    rt_uint8_t w25x_txCMD1 = W25X_REG_READSTATUS;

    result = rt_qspi_send_then_recv(qspi_device, &w25x_txCMD1, 1, &u8Val, 1);
    RT_ASSERT(result > 0);

    return u8Val;
}

static rt_uint8_t SpiFlash_ReadStatusReg2(struct rt_qspi_device *qspi_device)
{
    rt_uint8_t u8Val;
    rt_err_t result = RT_EOK;
    rt_uint8_t w25x_txCMD1 = W25X_REG_READSTATUS2;

    result = rt_qspi_send_then_recv(qspi_device, &w25x_txCMD1, 1, &u8Val, 1);
    RT_ASSERT(result > 0);

    return u8Val;
}

static rt_err_t SpiFlash_WriteStatusReg(struct rt_qspi_device *qspi_device, uint8_t u8Value1, uint8_t u8Value2)
{
    rt_uint8_t w25x_txCMD1;
    rt_uint8_t au8Val[2];
    rt_err_t result;
    struct rt_qspi_message qspi_message = {0};

    /* Enable WE */
    w25x_txCMD1 = W25X_REG_WRITEENABLE;
    result = rt_qspi_send(qspi_device, &w25x_txCMD1, sizeof(w25x_txCMD1));
    if (result != sizeof(w25x_txCMD1))
        goto exit_SpiFlash_WriteStatusReg;

    /* Prepare status-1, 2 data */
    au8Val[0] = u8Value1;
    au8Val[1] = u8Value2;

    /* 1-bit mode: Instruction+payload */
    qspi_message.instruction.content = W25X_REG_WRITESTATUS;
    qspi_message.instruction.qspi_lines = 1;

    qspi_message.qspi_data_lines   = 1;
    qspi_message.parent.cs_take    = 1;
    qspi_message.parent.cs_release = 1;
    qspi_message.parent.send_buf   = &au8Val[0];
    qspi_message.parent.length     = sizeof(au8Val);
    qspi_message.parent.next       = RT_NULL;

    if (rt_qspi_transfer_message(qspi_device, &qspi_message) != sizeof(au8Val))
    {
        result = -RT_ERROR;
    }

    result  = RT_EOK;

exit_SpiFlash_WriteStatusReg:

    return result;
}

static void SpiFlash_WaitReady(struct rt_qspi_device *qspi_device)
{
    volatile uint8_t u8ReturnValue;

    do
    {
        u8ReturnValue = SpiFlash_ReadStatusReg(qspi_device);
        u8ReturnValue = u8ReturnValue & 1;
    }
    while (u8ReturnValue != 0);   // check the BUSY bit
}

static void SpiFlash_EnterQspiMode(struct rt_qspi_device *qspi_device)
{
    rt_err_t result = RT_EOK;

    uint8_t u8Status1 = SpiFlash_ReadStatusReg(qspi_device);
    uint8_t u8Status2 = SpiFlash_ReadStatusReg2(qspi_device);

    u8Status2 |= W25X_REG_QUADENABLE;

    result = SpiFlash_WriteStatusReg(qspi_device, u8Status1, u8Status2);
    RT_ASSERT(result == RT_EOK);

    SpiFlash_WaitReady(qspi_device);
}

static void SpiFlash_ExitQspiMode(struct rt_qspi_device *qspi_device)
{
    rt_err_t result = RT_EOK;
    uint8_t u8Status1 = SpiFlash_ReadStatusReg(qspi_device);
    uint8_t u8Status2 = SpiFlash_ReadStatusReg2(qspi_device);

    u8Status2 &= ~W25X_REG_QUADENABLE;

    result = SpiFlash_WriteStatusReg(qspi_device, u8Status1, u8Status2);
    RT_ASSERT(result == RT_EOK);

    SpiFlash_WaitReady(qspi_device);
}

static int rt_hw_spiflash_init(void)
{
    /* Here, we use Dual I/O to drive the SPI flash by default. */
    /* If you want to use Quad I/O, you can modify to 4 from 2 and crossover D2/D3 pin of SPI flash. */
    if (nu_qspi_bus_attach_device("qspi0", "qspi01", 2, SpiFlash_EnterQspiMode, SpiFlash_ExitQspiMode) != RT_EOK)
        return -1;

#if defined(RT_USING_SFUD)
    if (rt_sfud_flash_probe("flash0", "qspi01") == RT_NULL)
    {
        return -(RT_ERROR);
    }
#endif
    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_spiflash_init);
#endif /* BOARD_USING_STORAGE_SPIFLASH */


#if defined(BOARD_USING_MAX31875)
#include <sensor_max31875.h>
int rt_hw_max31875_port(void)
{
    struct rt_sensor_config cfg;

    cfg.intf.dev_name = "i2c1";
    cfg.intf.user_data = (void *)MAX31875_I2C_SLAVE_ADR_R0;
    cfg.irq_pin.pin = RT_PIN_NONE;

    rt_hw_max31875_init("max31875", &cfg);
    return 0;
}
INIT_APP_EXPORT(rt_hw_max31875_port);
#endif /* BOARD_USING_MAX31875 */


#if defined(BOARD_USING_BMX055)
#include <sensor_bmx055.h>
int rt_hw_bmx055_port(void)
{
    struct rt_sensor_config cfg;
    cfg.intf.dev_name = "i2c2";
    cfg.intf.user_data = (void *)0;
    cfg.irq_pin.pin = RT_PIN_NONE;

    rt_hw_bmx055_init("bmx055", &cfg);
    return 0;
}
INIT_APP_EXPORT(rt_hw_bmx055_port);
#endif /* BOARD_USING_BMX055  */

#if defined(BOARD_USING_ESP8266)
#include <at_device_esp8266.h>

#define LOG_TAG    "at.sample.esp"
#undef DBG_TAG
#include <at_log.h>

static struct at_device_esp8266 esp0 =
{
    "esp0",          /* esp8266 device name */
    "uart1",         /* esp8266 serial device name, EX: uart1, uuart1 */

    "NT_ZY_BUFFALO", /* Wi-Fi SSID */
    "12345678",      /* Wi-Fi PASSWORD */
    1024             /* Receive buffer length */
};

static int rt_hw_esp8266_port(void)
{
    struct at_device_esp8266 *esp8266 = &esp0;
    rt_base_t esp_rst_pin = NU_GET_PININDEX(NU_PH, 3);
    /* ESP8266 reset pin PH.3 */
    rt_pin_mode(esp_rst_pin, PIN_MODE_OUTPUT);
    rt_pin_write(esp_rst_pin, 1);

    return at_device_register(&(esp8266->device),
                              esp8266->device_name,
                              esp8266->client_name,
                              AT_DEVICE_CLASS_ESP8266,
                              (void *) esp8266);
}
INIT_APP_EXPORT(rt_hw_esp8266_port);

static void at_wifi_set(int argc, char **argv)
{
    struct at_device_ssid_pwd sATDConf;
    struct at_device *at_dev = RT_NULL;

    /* If the number of arguments less than 2 */
    if (argc != 3)
    {
        rt_kprintf("\n");
        rt_kprintf("at_wifi_set <ssid> <password>\n");
        return ;
    }

    sATDConf.ssid     = argv[1]; //ssid
    sATDConf.password = argv[2]; //password

    if ((at_dev = at_device_get_first_initialized()) != RT_NULL)
        at_device_control(at_dev, AT_DEVICE_CTRL_SET_WIFI_INFO, &sATDConf);
    else
    {
        rt_kprintf("Can't find any initialized AT device.\n");
    }
}
#ifdef FINSH_USING_MSH
    MSH_CMD_EXPORT(at_wifi_set, AT device wifi set ssid / password function);
#endif
#endif /* BOARD_USING_ESP8266  */

#if defined(BOARD_USING_LCD_ILI9341) && defined(NU_PKG_USING_ILI9341_SPI)
#include <lcd_ili9341.h>
#if defined(PKG_USING_GUIENGINE)
    #include <rtgui/driver.h>
#endif
int rt_hw_ili9341_port(void)
{
    if (rt_hw_lcd_ili9341_spi_init("spi2") != RT_EOK)
        return -1;

    rt_hw_lcd_ili9341_init();

#if defined(PKG_USING_GUIENGINE)
    rt_device_t lcd_ili9341;
    lcd_ili9341 = rt_device_find("lcd");
    if (lcd_ili9341)
    {
        rtgui_graphic_set_device(lcd_ili9341);
    }
#endif
    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_ili9341_port);
#endif /* BOARD_USING_LCD_ILI9341 */

#if defined(BOARD_USING_NAU88L25) && defined(NU_PKG_USING_NAU88L25)
#include <acodec_nau88l25.h>
S_NU_NAU88L25_CONFIG sCodecConfig =
{
    .i2c_bus_name = "i2c2",

    .i2s_bus_name = "sound0",

    .pin_phonejack_en = NU_GET_PININDEX(NU_PE, 13),

    .pin_phonejack_det = 0,
};

int rt_hw_nau88l25_port(void)
{
    if (nu_hw_nau88l25_init(&sCodecConfig) != RT_EOK)
        return -1;

    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_nau88l25_port);
#endif /* BOARD_USING_NAU88L25 */
