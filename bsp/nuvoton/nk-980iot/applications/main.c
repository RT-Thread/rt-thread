/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-12-12      Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>
#include <rtdevice.h>

#if defined(RT_USING_PIN)
#include <drv_gpio.h>

/* defined the LED_R pin: PB13 */
#define LED_R   NU_GET_PININDEX(NU_PB, 13)

/* defined the LED_Y pin: PB8 */
#define LED_Y   NU_GET_PININDEX(NU_PB, 8)

#if !defined(BSP_USING_USBH)
/* defined the Key1 pin: PE10 */
#define KEY_1   NU_GET_PININDEX(NU_PE, 10)

/* defined the Key2 pin: PE12 */
#define KEY_2   NU_GET_PININDEX(NU_PE, 12)

static uint32_t u32Key1 = KEY_1;
static uint32_t u32Key2 = KEY_2;

void nu_button_cb(void *args)
{
    uint32_t u32Key = *((uint32_t *)(args));

    switch (u32Key)
    {
    case KEY_1:
        rt_pin_write(LED_Y, PIN_HIGH);
        break;
    case KEY_2:
        rt_pin_write(LED_Y, PIN_LOW);
        break;
    }
}
#endif

#endif

int main(int argc, char **argv)
{
#if defined(RT_USING_PIN)
    int counter = 1000;

    /* set LED_R pin mode to output */
    rt_pin_mode(LED_R, PIN_MODE_OUTPUT);

    /* set LED_Y pin mode to output */
    rt_pin_mode(LED_Y, PIN_MODE_OUTPUT);

#if !defined(BSP_USING_USBH)
    /* set KEY_1 pin mode to input */
    rt_pin_mode(KEY_1, PIN_MODE_INPUT_PULLUP);

    /* set KEY_2 pin mode to output */
    rt_pin_mode(KEY_2, PIN_MODE_INPUT_PULLUP);

    rt_pin_attach_irq(KEY_1, PIN_IRQ_MODE_FALLING, nu_button_cb, &u32Key1);
    rt_pin_irq_enable(KEY_1, PIN_IRQ_ENABLE);

    rt_pin_attach_irq(KEY_2, PIN_IRQ_MODE_FALLING, nu_button_cb, &u32Key2);
    rt_pin_irq_enable(KEY_2, PIN_IRQ_ENABLE);
#endif

    while (counter--)
    {
        rt_pin_write(LED_R, PIN_HIGH);
        rt_thread_mdelay(100);
        rt_pin_write(LED_R, PIN_LOW);
        rt_thread_mdelay(100);
    }

#endif

    return 0;
}
