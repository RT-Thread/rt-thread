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



#if defined(BOARD_USING_ESP8266)
#include <at_device_esp8266.h>

#define LOG_TAG     "at.sample.esp"
#undef DBG_TAG
#include <at_log.h>

static struct at_device_esp8266 esp0 =
{
    "esp0",          /* esp8266 device name */
    "uart4",         /* esp8266 serial device name, EX: uart1, uuart1 */

    "NT_ZY_BUFFALO", /* Wi-Fi SSID */
    "12345678",      /* Wi-Fi PASSWORD */
    1024             /* Receive buffer length */
};

static int rt_hw_esp8266_port(void)
{
    struct at_device_esp8266 *esp8266 = &esp0;
    rt_base_t esp_rst_pin = NU_GET_PININDEX(NU_PC, 13);
    rt_base_t esp_fwupdate_pin = NU_GET_PININDEX(NU_PD, 12);

    /* ESP8266 reset pin PC.13 */
    rt_pin_mode(esp_rst_pin, PIN_MODE_OUTPUT);
    rt_pin_write(esp_rst_pin, 1);

    /* ESP8266 reset pin PD.12 */
    rt_pin_mode(esp_fwupdate_pin, PIN_MODE_OUTPUT);
    rt_pin_write(esp_fwupdate_pin, 1);

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

#if defined(NU_PKG_USING_ADC_TOUCH_SW)

#include "adc_touch.h"
#include "touch_sw.h"
#include "NuMicro.h"

#define NU_MFP_POS(PIN)          ((PIN % 8) * 4)
#define NU_MFP_MSK(PIN)          (0xful << NU_MFP_POS(PIN))

S_CALIBRATION_MATRIX g_sCalMat = { 52, 6247, -2804852, 4917, 47, -2309716, 65536 };

static void nu_pin_func(rt_base_t pin, int data)
{
    uint32_t pin_index      = NU_GET_PINS(pin);
    uint32_t port_index     = NU_GET_PORT(pin);
    __IO uint32_t *GPx_MFPx = ((__IO uint32_t *) &SYS->GPA_MFPL) + port_index * 2 + (pin_index / 8);
    uint32_t MFP_Msk        = NU_MFP_MSK(pin_index);

    *GPx_MFPx  = (*GPx_MFPx & (~MFP_Msk)) | data;
}

static void tp_switch_to_analog(rt_base_t pin)
{
    GPIO_T *port = (GPIO_T *)(GPIOA_BASE + (0x40) * NU_GET_PORT(pin));

    if (pin == NU_GET_PININDEX(NU_PB, 11))
        nu_pin_func(pin, SYS_GPB_MFPH_PB11MFP_EADC0_CH11);
    else if (pin == NU_GET_PININDEX(NU_PB, 8))
        nu_pin_func(pin, SYS_GPB_MFPH_PB8MFP_EADC0_CH8);

    GPIO_DISABLE_DIGITAL_PATH(port, NU_GET_PIN_MASK(NU_GET_PINS(pin)));
}

static void tp_switch_to_digital(rt_base_t pin)
{
    GPIO_T *port = (GPIO_T *)(GPIOA_BASE + (0x40) * NU_GET_PORT(pin));

    nu_pin_func(pin, 0);

    /* Enable digital path on these EADC pins */
    GPIO_ENABLE_DIGITAL_PATH(port, NU_GET_PIN_MASK(NU_GET_PINS(pin)));
}

static S_TOUCH_SW sADCTP =
{
    .adc_name    = "eadc0",
    .i32ADCChnYU = 11,
    .i32ADCChnXR = 8,
    .pin =
    {
        NU_GET_PININDEX(NU_PB, 10), // XL
        NU_GET_PININDEX(NU_PB, 11), // YU
        NU_GET_PININDEX(NU_PB, 8), // XR
        NU_GET_PININDEX(NU_PB, 9), // YD
    },
    .switch_to_analog  = tp_switch_to_analog,
    .switch_to_digital = tp_switch_to_digital,
};

#endif

#include <lcd_ili9341.h>
#if defined(PKG_USING_GUIENGINE)
    #include <rtgui/driver.h>
#endif
int rt_hw_ili9341_port(void)
{
    if (rt_hw_lcd_ili9341_spi_init("spi1", RT_NULL) != RT_EOK)
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

#if defined(NU_PKG_USING_ADC_TOUCH_SW)
    nu_adc_touch_sw_register(&sADCTP);
#endif

    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_ili9341_port);
#endif /* BOARD_USING_LCD_ILI9341 */