#ifndef DRV_PINMUX_H__
#define DRV_PINMUX_H__

#include <rtthread.h>

/*
 * Shared S100 pinctrl helpers.
 *
 * GPIO, UART, SPI and other MCU-side drivers can reuse this layer to switch
 * mux function and electrical attributes without duplicating pin register
 * knowledge in every peripheral driver.
 */
typedef rt_uint8_t s100_pin_t;

typedef enum
{
    S100_PIN_PULL_NONE = 0,
    S100_PIN_PULL_DOWN,
    S100_PIN_PULL_UP,
} s100_pin_pull_t;

typedef enum
{
    S100_PIN_FUNC0 = 0,
    S100_PIN_FUNC1,
    S100_PIN_FUNC2,
    S100_PIN_FUNC_GPIO,
} s100_pin_function_t;

#define S100_GPIO_PIN_COUNT 88U

/* Returns RT_FALSE for reserved/unsupported pins, including the SDK blacklist. */
rt_bool_t s100_pin_is_valid(s100_pin_t pin);
rt_err_t s100_pin_set_function(s100_pin_t pin, s100_pin_function_t function);
rt_err_t s100_pin_set_pull(s100_pin_t pin, s100_pin_pull_t pull);

#endif

