#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <rtthread.h>

#include "led.h"

int main(void)
{
    printf("hello rt-thread\n");

    while (1)
    {
        /* light on leds for one second */
        rt_hw_led_on(LED2|LED3);
        rt_hw_led_off(LED1|LED4);
        rt_thread_delay(100);
    
        /* light off leds for one second */
        rt_hw_led_off(LED2|LED3);
        rt_hw_led_on(LED1|LED4);
        rt_thread_delay(100);
    }   

    return 0;
}


