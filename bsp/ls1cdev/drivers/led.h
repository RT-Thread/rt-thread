// led接口
// 使用低电平点亮led，高电平熄灭led

#ifndef __OPENLOONGSON_LED_H
#define __OPENLOONGSON_LED_H


// 初始化led
// @led_gpio led所在gpio引脚
void led_init(unsigned int led_gpio);


// 点亮led
// @led_gpio led所在gpio引脚
void led_on(unsigned int led_gpio);


// 熄灭led
// @led_gpio
void led_off(unsigned int led_gpio);





#endif

