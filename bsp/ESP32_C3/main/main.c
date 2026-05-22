
#include <rtthread.h>
#include <stdlib.h> // For atoi()
#include <finsh.h>  // For MSH_CMD_EXPORT

// The global variable you want to expose to FinSH
// NOTE: It must be a global or static global variable.
int app_data_value = 100;

// Function to handle reading and setting the variable
// All FinSH commands in msh mode must have this signature: (int argc, char **argv)
void app_data_cmd(int argc, char **argv)
{
    // Check if the FinSH C-style interpreter is disabled
    #ifndef FINSH_USING_MSH
    rt_kprintf("Error: This command requires msh mode enabled.\n");
    return;
    #endif

    if (argc == 1)
    {
        // Case 1: No arguments (e.g., 'app_data_cmd') -> Read the current value
        rt_kprintf("app_data_value (current): %d\n", app_data_value);
    }
    else if (argc == 2)
    {
        // Case 2: One argument (e.g., 'app_data_cmd 250') -> Set a new value
        int new_value = atoi(argv[1]);
        app_data_value = new_value;
        rt_kprintf("app_data_value set to: %d\n", app_data_value);
    }
    else
    {
        // Case 3: Invalid number of arguments
        rt_kprintf("Usage:\n");
        rt_kprintf("  Read: app_data_cmd\n");
        rt_kprintf("  Write: app_data_cmd <value>\n");
    }
}

// Export the function as a FinSH command. 
// Format: MSH_CMD_EXPORT(function_name, description)
MSH_CMD_EXPORT(app_data_cmd, Get or set the application data value);
/*
 * Copyright (c) 2021-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2022-04-24     supperthomas  first version
 * 2022-06-02     supperthomas  fix version
 * 2023-10-20     WCX1024979076 add wifi application
 */
#define RT_BSP_LED_PIN    2
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef BSP_USING_BLE
void app_main()
{
    while(1)
    {

    }
}
#endif /* BSP_USING_BLE */

int main(void)
{
    rt_kprintf("Hello!RT-THREAD!\r\n");
    rt_pin_mode(RT_BSP_LED_PIN, PIN_MODE_OUTPUT);

#ifdef BSP_USING_BLE
    extern void app_main(void);
    esp_timer_init();
    app_main(); //该函数为nimble样例程序入口
#endif /* BSP_USING_BLE */

#ifdef RT_USING_WIFI
    /* set wifi work mode */
    rt_wlan_set_mode(RT_WLAN_DEVICE_STA_NAME, RT_WLAN_STATION);
    rt_wlan_set_mode(RT_WLAN_DEVICE_AP_NAME, RT_WLAN_AP);
#endif /* RT_USING_WIFI */

    while (1)
    {
        rt_pin_write(RT_BSP_LED_PIN, PIN_HIGH);
        rt_thread_mdelay(1000);
        rt_pin_write(RT_BSP_LED_PIN, PIN_LOW);
        rt_thread_mdelay(1000);
    }
}
