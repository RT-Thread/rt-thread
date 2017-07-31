// led接口
// 使用低电平点亮led，高电平熄灭led


#include "ls1c_gpio.h"


// 初始化led
// @led_gpio led所在gpio引脚
void led_init(unsigned int led_gpio)
{
    gpio_init(led_gpio, gpio_mode_output);
    gpio_set(led_gpio, gpio_level_high);        // 指示灯默认熄灭

    return ;
}


// 点亮led
// @led_gpio led所在gpio引脚
void led_on(unsigned int led_gpio)
{
    gpio_set(led_gpio, gpio_level_low);

    return ;
}


// 熄灭led
// @led_gpio
void led_off(unsigned int led_gpio)
{
    gpio_set(led_gpio, gpio_level_high);

    return ;
}




