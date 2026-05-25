#ifndef DRV_GPIO_H__
#define DRV_GPIO_H__

#include "drv_pinmux.h"

/*
 * MCU GPIO access layer used by both the RT-Thread pin device and simple
 * board-level helpers.
 */
typedef enum
{
    S100_PIN_DIR_IN = 0,
    S100_PIN_DIR_OUT,
    S100_PIN_DIR_HIGH_Z,
} s100_pin_direction_t;

typedef enum
{
    S100_PIN_LEVEL_LOW = 0,
    S100_PIN_LEVEL_HIGH,
} s100_pin_level_t;

rt_err_t s100_gpio_set_direction(s100_pin_t pin, s100_pin_direction_t direction);
rt_err_t s100_gpio_write_pin(s100_pin_t pin, s100_pin_level_t level);
rt_err_t s100_gpio_read_pin(s100_pin_t pin, s100_pin_level_t *level);

void s100_gpio_write(rt_uint8_t pin, rt_uint8_t value);
rt_uint8_t s100_gpio_read(rt_uint8_t pin);

#endif

