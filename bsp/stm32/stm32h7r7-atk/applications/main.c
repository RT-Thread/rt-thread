/*
 * @Author       : wenshan
 * @Date         : 2025-05-14 20:21:24
 * @LastEditors: Do not edit
 * @LastEditTime: 2025-06-05 14:32:18
 * @Description  :
 * @FilePath: \undefinedf:\github\rtthread\rt-thread\bsp\stm32\stm32h7r7-atk\applications\main.c
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"


#define LED_PIN GET_PIN(D, 14)

int main(void)
{
    while(1)
    {
        rt_thread_mdelay(500);
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_PIN, PIN_LOW);
    }
    return RT_EOK;
}

#include "stm32h7rsxx.h"
static int vtor_config(void)
{
    /* Vector Table Relocation in Internal XSPI1_BASE */
    SCB->VTOR = XSPI1_BASE;
    return 0;
}
INIT_BOARD_EXPORT(vtor_config);

