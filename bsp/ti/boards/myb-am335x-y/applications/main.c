#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <rtthread.h>
#include <rtdevice.h>

int main(void)
{
    rt_base_t led;

    printf("hello rt-thread\n");

    led = rt_pin_get("P3.18");
    if (led < 0)
        goto die;
    rt_pin_mode(led, PIN_MODE_OUTPUT);

    for (;;)
    {
        rt_pin_write(led, !rt_pin_read(led));
        rt_thread_mdelay(500);
    }

die:
    return 0;
}

