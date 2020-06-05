#include "config.h"
#include <rthw.h>
#include <rtthread.h>

#define LED0_PIN MSS_GPIO_0
#define LED1_PIN MSS_GPIO_1

int main(void)
{
    int count = 0;

    while(count++)
    {
        MSS_GPIO_set_output(LED0_PIN, 1);
        MSS_GPIO_set_output(LED1_PIN, 1);
        rt_thread_mdelay(500);
         
        MSS_GPIO_set_output(LED0_PIN, 0);
        MSS_GPIO_set_output(LED1_PIN, 0);
        rt_thread_mdelay(500);
    }
    
    return RT_EOK;
}

