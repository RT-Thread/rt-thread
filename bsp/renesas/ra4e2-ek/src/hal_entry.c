#include "hal_data.h"
#include <rtdevice.h>

#define LED1_PIN    BSP_IO_PORT_02_PIN_07 /* Onboard LED pins */
#define LED2_PIN    BSP_IO_PORT_01_PIN_04 /* Onboard LED pins */
#define LED3_PIN    BSP_IO_PORT_01_PIN_12 /* Onboard LED pins */

void hal_entry(void)
{
    rt_kprintf("\nHello RT-Thread!\n");

    while (1)
    {
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_pin_write(LED2_PIN, PIN_HIGH);
        rt_pin_write(LED3_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_pin_write(LED2_PIN, PIN_LOW);
        rt_pin_write(LED3_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}

