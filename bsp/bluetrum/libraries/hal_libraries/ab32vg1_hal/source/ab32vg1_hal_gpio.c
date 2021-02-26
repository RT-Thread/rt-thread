/*
 * Copyright (c) 2020-2020, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ab32vg1_hal.h"

#ifdef HAL_GPIO_MODULE_ENABLED

#if 0
#define HAL_LOG(...)       hal_printf(__VA_ARGS__)
#else
#define HAL_LOG(...)
#endif

void gpio_afinit(hal_sfr_t gpiox, uint8_t pin, uint32_t alternate, uint32_t af_con)
{
    uint32_t is_rx_map_tx = (alternate & UT1RXMAP_TX) || (alternate & UT0RXMAP_TX);
    if ((af_con & 0xf0u) != GPIO_AFDIS) {
        gpiox[GPIOxFEN]   |= BIT(pin);

        switch (is_rx_map_tx)
        {
        case UT1RXMAP_TX:
            FUNCMCONx(GPIO_GET_AFCON(af_con)) |= GPIO_AF_MAP_CLR(UT1RXMAP_AF);
            break;
        case UT0RXMAP_TX:
            FUNCMCONx(GPIO_GET_AFCON(af_con)) |= GPIO_AF_MAP_CLR(UT0RXMAP_AF);
            break;
        default:
            break;
        }

        FUNCMCONx(GPIO_GET_AFCON(af_con)) |= GPIO_AF_MAP_CLR(af_con & 0x1f);
        FUNCMCONx(GPIO_GET_AFCON(af_con)) |= alternate;
        HAL_LOG("af_con=0x%X AFCON=%d alternate=%d\n", af_con, GPIO_GET_AFCON(af_con), (af_con & 0x1f));
    }
}

/**
 * @brief Initialize the gpio.
 *
 * @param port GPIO port(GPIOAN, GPIOBN, GPIOEN, GPIOFN).
 * @param gpio_init the configuration of the specified GPIO peripheral.
 */
void hal_gpio_init(hal_sfr_t gpiox, gpio_init_t gpio_init)
{
    uint8_t iocurrent = 0;
    if (gpio_init == HAL_NULL) {
        return;
    }

    for (iocurrent = 0; iocurrent < 8; iocurrent++) {
        if ((gpio_init->pin & BIT(iocurrent)) == 0) {
            continue;
        }

        gpio_afinit(gpiox, iocurrent, gpio_init->alternate, gpio_init->af_con);

        switch (gpio_init->dir)
        {
        case GPIO_DIR_INPUT:
            /* When set to input, clear all pull-ups of the port. */
            gpiox[GPIOxDIR]     |= BIT(iocurrent);
            gpiox[GPIOxPU]      &= ~BIT(iocurrent);
            gpiox[GPIOxPU200K]  &= ~BIT(iocurrent);
            gpiox[GPIOxPD200K]  &= ~BIT(iocurrent);
            gpiox[GPIOxPU300K]  &= ~BIT(iocurrent);
            gpiox[GPIOxPD300K]  &= ~BIT(iocurrent);

            switch (gpio_init->pull)
            {
            case GPIO_PULLUP:
                gpiox[GPIOxPU] |= BIT(iocurrent);
                break;
            case GPIO_PULLDOWN:
                gpiox[GPIOxPD] |= BIT(iocurrent);
                break;
            case GPIO_NOPULL:
            default:
                break;
            }
            break;
        case GPIO_DIR_OUTPUT:
            gpiox[GPIOxDIR] &= ~BIT(iocurrent);
            break;
        default:
            break;
        }

        switch (gpio_init->de)
        {
        case GPIO_DIGITAL:
            gpiox[GPIOxDE] |= BIT(iocurrent);
            break;
        case GPIO_ANALOG:
            gpiox[GPIOxDE] &= ~BIT(iocurrent);
            break;
        default:
            break;
        }
    }
}

/**
 * @brief Read the specified input port pin.
 * 
 * @param port GPIO port(GPIOAN, GPIOBN, GPIOEN, GPIOFN).
 * @param pin This parameter can be GPIO_PIN_x where x can be (0.15).
 * @return uint8_t The input port pin value.
 */
uint8_t hal_gpio_read(hal_sfr_t gpiox, uint8_t pin)
{
    return ((gpiox[GPIOx] & BIT(pin)) != GPIO_PIN_LOW) ? GPIO_PIN_HIGH : GPIO_PIN_LOW;
}

/**
 * @brief Set or clear the selected data port bit.
 * 
 * @param port GPIO port(GPIOAN, GPIOBN, GPIOEN, GPIOFN).
 * @param pin This parameter can be GPIO_PIN_x where x can be (0.15).
 * @param state specifies the value to be written to the selected bit.
 *          @arg GPIO_PIN_LOW:
 *          @arg GPIO_PIN_HIGH:
 */
void hal_gpio_write(hal_sfr_t gpiox, uint8_t pin, uint8_t state)
{
    if (state == GPIO_PIN_LOW) {
        gpiox[GPIOx] &= ~BIT(pin);
    } else {
        gpiox[GPIOx] |= BIT(pin);
    }
}

/**
 * @brief Toggle the specified GPIO pin.
 * 
 * @param port GPIO port(GPIOAN, GPIOBN, GPIOEN, GPIOFN).
 * @param pin This parameter can be GPIO_PIN_x where x can be (0.15).
 */
void hal_gpio_toggle(hal_sfr_t gpiox, uint8_t pin)
{
    gpiox[GPIOx] ^= BIT(pin);
}

#endif
