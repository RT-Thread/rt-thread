#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define LED0_PIN 0
#define LED1_PIN 1
#define SW0_PIN  2
#define SW1_PIN  3

extern void sw0_isr(void *args);
extern void sw1_isr(void *args);

int main(void)
{
    int count = 1;

    rt_pin_attach_irq(SW0_PIN, PIN_IRQ_MODE_RISING, sw0_isr, RT_NULL);
    rt_pin_attach_irq(SW1_PIN, PIN_IRQ_MODE_RISING, sw1_isr, RT_NULL);
    
    rt_pin_irq_enable(SW0_PIN, PIN_IRQ_ENABLE);
    rt_pin_irq_enable(SW1_PIN, PIN_IRQ_ENABLE);

    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT); 
    
    while(count++)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(100);

        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_thread_mdelay(100);
    }
    
    return RT_EOK;
}
