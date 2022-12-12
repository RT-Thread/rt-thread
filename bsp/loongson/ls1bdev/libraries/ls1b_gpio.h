/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-06     勤为本       first version
 */


#ifndef __LOONGSON_GPIO_H
#define __LOONGSON_GPIO_H



// 龙芯1c的gpio是按照0,1,2,3,4...这样的顺序编号的，
// 但在操作寄存器的时候，又是按照每32个一组来分的
// 这里利用这个特性，将每组的32个gpio叫做一个"port"，每个gpio在每组中的索引叫"pin"
// port = gpio / 32
// pin  = gpio % 32
// 例如GPIO50，port=1,pin=18
#define GPIO_GET_PORT(gpio)                 ((gpio) / 32)
#define GPIO_GET_PIN(gpio)                  ((gpio) % 32)


// gpio的工作模式--输入、输出
typedef enum{
    gpio_mode_output = 0,       // 输出
    gpio_mode_input = 1         // 输入
}gpio_mode_t;


//  gpio高低电平值
typedef enum{
    gpio_level_low = 0,         // 低电平
    gpio_level_high = 1         // 高电平
}gpio_level_t;


typedef enum {
    // 上升沿触发
	IRQ_TYPE_EDGE_RISING	= 0x00000001,
	// 下降沿触发
	IRQ_TYPE_EDGE_FALLING	= 0x00000002,
	IRQ_TYPE_EDGE_BOTH	= (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING),
	// 高电平触发
	IRQ_TYPE_LEVEL_HIGH	= 0x00000004,
	// 低电平触发
	IRQ_TYPE_LEVEL_LOW	= 0x00000008,
	IRQ_TYPE_LEVEL_MASK	= (IRQ_TYPE_LEVEL_LOW | IRQ_TYPE_LEVEL_HIGH),	
}gpio_irq_type_t;



/*
 * 获取指定gpio的CFG寄存器
 * @gpio gpio编号
 * @ret CFG寄存器
 */
volatile unsigned int *gpio_get_cfg_reg(unsigned int gpio);

/*
 * gpio初始化
 * @gpio gpio引脚，取值范围[0, 127]
 * @mode gpio的工作模式(输入、输出)
 *
 * 例: 将gpio50初始化为输出
 * gpio_init(50, gpio_mode_output);
 */
void gpio_init(unsigned int gpio, gpio_mode_t mode);


/*
 * 在指定gpio输出高电平或低电平
 * @gpio gpio引脚，取值范围[0, 127]
 * @level 电平值
 *
 * 例: 在gpio50上输出低电平
 * gpio_set(50, gpio_level_low);
 */
void gpio_set(unsigned int gpio, gpio_level_t level);



/*
 * 读取指定gpio引脚的值
 * @gpio gpio引脚，取值范围[0,127]
 *
 * 例: 读取gpio50引脚上的值
 * gpio_level_t level;
 * level = gpio_get(50);
 */
unsigned int gpio_get(unsigned int gpio);



/**
 * 设置中断类型
 * @gpio gpio引脚
 * @type 触发中断的条件。高电平触发、低电平触发、上升沿触发 or 下降沿触发
 */
void gpio_set_irq_type(unsigned int gpio, gpio_irq_type_t type);



#endif

