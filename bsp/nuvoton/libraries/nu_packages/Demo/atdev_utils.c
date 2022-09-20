/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-9-19       Wayne        First version
*
******************************************************************************/

#include <rtthread.h>

#if defined(PKG_USING_AT_DEVICE)

#include <at_device.h>

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

#endif /* #if defined(PKG_USING_AT_DEVICE) */

