#include <rtthread.h>

#include "led.h"

#ifdef PKG_USING_GUIENGINE
#include <rtgui/driver.h>
#endif

int main(void)
{
    rt_device_t device;

    rt_kprintf("hello rt-thread\n");

#ifdef PKG_USING_GUIENGINE
    device = rt_device_find("lcd");
    if (device)
    {
        rtgui_graphic_set_device(device);
    }
#endif


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


