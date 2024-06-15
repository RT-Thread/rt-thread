#include "LPC17xx.h"
#include "led.h"

void rt_hw_led_init(void)
{
    LPC_GPIO2->FIODIR0 |= 1<<0; /* led0:P2.0 */
    LPC_GPIO2->FIODIR0 |= 1<<1; /* led1:P2.1 */
}

void rt_hw_led_on(rt_uint32_t led)
{
    switch(led)
    {
    case 0: /* P2.0 = 1 */
        LPC_GPIO2->FIOSET0 = 1<<0;
        break;
    case 1: /* P2.1 = 1 */
        LPC_GPIO2->FIOSET0 = 1<<1;
        break;
    default:
        break;
    }
}

void rt_hw_led_off(rt_uint32_t led)
{
    switch(led)
    {
    case 0: /* P2.0 = 0 */
        LPC_GPIO2->FIOCLR0 = 1<<0;
        break;
    case 1: /* P2.1 = 0 */
        LPC_GPIO2->FIOCLR0 = 1<<1;
        break;
    default:
        break;
    }
}
