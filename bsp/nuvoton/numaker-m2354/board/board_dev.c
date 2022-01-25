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

