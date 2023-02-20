#include <rtthread.h>
#include <rtdevice.h>
#include <drv_usart.h>
/* defined the LED1 pin: PC0 */
#define LED1_PIN 32

int main(void)
{
    int count = 1;
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(LED1_PIN, PIN_LOW);
    while (count++)
    {
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}
