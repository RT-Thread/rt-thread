#ifndef BOARD_LED_H__
#define BOARD_LED_H__

struct led_io_def
{
    enum gpio_port  port;
    enum gpio_pin   pin;
};

void rt_hw_led_off(int led);
void rt_hw_led_on (int led);

#endif
