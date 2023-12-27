/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2018-08-27     ZYLX              the first version
 */

#include <rtdevice.h>
#include <enc28j60.h>
#include <drv_spi.h>
#include <drv_gpio.h>
#include <board.h>

#define PIN_NRF_IRQ             GET_PIN(E,2)
#define PIN_SPI_CS              GET_PIN(A,4)

int enc28j60_init(void)
{
    __HAL_RCC_GPIOD_CLK_ENABLE();
    rt_hw_spi_device_attach("spi1", "spi11", PIN_SPI_CS);

    /* attach enc28j60 to spi. spi11 cs - PA4 */
    enc28j60_attach("spi11");

    /* init interrupt pin */
    rt_pin_mode(PIN_NRF_IRQ, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(PIN_NRF_IRQ, PIN_IRQ_MODE_FALLING, (void(*)(void*))enc28j60_isr, RT_NULL);
    rt_pin_irq_enable(PIN_NRF_IRQ, PIN_IRQ_ENABLE);

    return 0;
}
INIT_COMPONENT_EXPORT(enc28j60_init);
