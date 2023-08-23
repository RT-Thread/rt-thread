#include "rtthread.h"
#include "rtdevice.h"

#define LED_PIN 0

int main(void)
{
    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);
    rt_uint8_t out = 0;

    while(1)
    {
        rt_thread_mdelay(500);
        rt_pin_write(LED_PIN, out);
        out = (out + 1) % 2;
    }
    return 0;
}
