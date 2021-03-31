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

/* defined the LED_G1 pin: PC3 */
#define LED_G1   NU_GET_PININDEX(NU_PC, 3)

/* defined the LED_G2 pin: PC11 */
#define LED_G2   NU_GET_PININDEX(NU_PC, 11)

/* defined the BUTTON pin: PC15 */
#define BUTTON   NU_GET_PININDEX(NU_PC, 15)

static uint32_t u32Button = BUTTON;

void nu_button_cb(void *args)
{
    static int u32ToggleFlag = 0;
    uint32_t u32Key = *((uint32_t *)(args));

    switch (u32Key)
    {
    case BUTTON:
        u32ToggleFlag = ~u32ToggleFlag;
        rt_pin_write(LED_G1, u32ToggleFlag);
        break;
    }
}
#endif

int main(int argc, char **argv)
{
#if defined(RT_USING_PIN)
    int counter = 1000;

    /* set LED_G1 pin mode to output */
    rt_pin_mode(LED_G1, PIN_MODE_OUTPUT);

    /* set LED_G2 pin mode to output */
    rt_pin_mode(LED_G2, PIN_MODE_OUTPUT);

    /* set BUTTON pin mode to input */
    rt_pin_mode(BUTTON, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(BUTTON, PIN_IRQ_MODE_FALLING, nu_button_cb, &u32Button);
    rt_pin_irq_enable(BUTTON, PIN_IRQ_ENABLE);

    while (counter--)
    {
        rt_pin_write(LED_G2, PIN_HIGH);
        rt_thread_mdelay(200);
        rt_pin_write(LED_G2, PIN_LOW);
        rt_thread_mdelay(200);
    }
#endif

    return 0;
}
