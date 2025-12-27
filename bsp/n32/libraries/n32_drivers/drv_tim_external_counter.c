/**
 * @file drv_tim_external_counter.c
 * @brief
 * @author jiache (wanghuan3037@fiberhome.com)
 * @version 1.0
 * @date 2025-11-28
 * 2025-11-28
 *  1.驱动的优化，并测试额所有的定时器均可实现外部时钟1方式计数
                name=eclktm1 ===》 TIM1 PA8
                name=eclktm2 ===》 TIM2 PA15
                name=eclktm3 ===》 TIM3 PA6
                name=eclktm4 ===》 TIM4 PB6
                name=eclktm5 ===》 TIM5 PA0
                name=eclktm8 ===》 TIM8 PC6
    2.RT_USING_DEVICE_OPS操作方式的实现
    3.日志标签的加入
*2025-12-1
    1.测试了每个定时器的通道1，通道的默认复用引脚，外部时钟1计数均OK
    2.外部计数的引脚复用全部采用Kconfig方式配置
 * 202512-2
 *      1.将定时器的时钟和gpio时钟统一放在drv_base.c中

2025-12-08
    1.移植兼容N32L40X的兼容代码，修改了Kconfig添加了配置
    2.测试了TIM1的PA8,测量1MHz的脉冲没有问题；测量10M也是OK的，示波器显示10.7MHz，实测10666668
 * 2025-12-12
    1.添加了N32L406的TIM2,TIM3的外部计数配置添加
 *-
 * @copyright Copyright (c) 2025  58
 *
 */
#include <rtthread.h>
#ifdef BSP_USING_TIM_EXT_COUNTER
#include "board.h"
#include <rtdevice.h>

#define DBG_TAG "TIM_CH_CNT"
#ifdef BSP_USING_TIM_ETR_CNT_DEBUG
#define DBG_LVL DBG_LOG
#else
#define DBG_LVL DBG_INFO
#endif
#include <rtdbg.h>
#include "drv_base.h"
enum
{
#ifdef BSP_USING_TIM1_EXT_COUNTER
    EXT_CLK_TIM1,
#endif
#ifdef BSP_USING_TIM2_EXT_COUNTER
    EXT_CLK_TIM2,
#endif
#ifdef BSP_USING_TIM3_EXT_COUNTER
    EXT_CLK_TIM3,
#endif
#ifdef BSP_USING_TIM4_EXT_COUNTER
    EXT_CLK_TIM4,
#endif
#ifdef BSP_USING_TIM5_EXT_COUNTER
    EXT_CLK_TIM5,
#endif
#ifdef BSP_USING_TIM8_EXT_COUNTER
    EXT_CLK_TIM8,
#endif
    EXT_CLK_NUM
};
struct n32_tim_ext_counter_config
{
    TIM_Module *timer_periph; /* 定时器外设 */
    GPIO_Module *gpio_periph; /* GPIO外设 */
    uint16_t gpio_pin;        /* GPIO引脚 */
    uint32_t gpio_af;         /* GPIO复用功能 */
    uint16_t tim_channel;     /* 定时器通道 */
    uint16_t polarity;        /* 极性配置 */
    uint16_t filter;          /* 滤波配置 */
    IRQn_Type irqn;           /* 中断号 */
    const char *info;         /* 设备信息 */
};

/* 外部计数器设备结构体 */
struct n32_tim_ext_counter_device
{
    struct rt_device parent;
    struct n32_tim_ext_counter_config *config;
    rt_uint32_t count_value;
    rt_uint32_t overflow_count;
    void (*overflow_callback)(rt_device_t dev); /* 修正回调函数签名 */
    void *callback_args;
};

static rt_err_t n32_tim_ext_counter_register(struct n32_tim_ext_counter_device *device,
                                             const char *name,
                                             struct n32_tim_ext_counter_config *config);
/* TIM1外部计数器初始化 */

static struct n32_tim_ext_counter_config tim1_ext_counter_config[EXT_CLK_NUM] =
    {
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
#define N32_EXT_CLK_CNT_G457 
#ifdef BSP_USING_TIM1_EXT_COUNTER /*CH1=PA8(0,1,2),PE9(3) ; CH2=PA9(0,1,2),PE11(3)*/

        {
            .timer_periph = TIM1,
            .polarity = TIM_IC_POLARITY_RISING,
            .filter = 0x0,
            .irqn = TIM1_UP_IRQn,

#ifdef TIM1_CH1_PA8
            .tim_channel = TIM_CH_1,
            .gpio_periph = GPIOA,
            .gpio_pin = GPIO_PIN_8,
            .gpio_af = 0,
            .info = "TIM1 PA8",
#endif /*TIM1_CH1_PA8*/

#ifdef TIM1_CH1_PE9
            .tim_channel = TIM_CH_1,
            .gpio_periph = GPIOE,
            .gpio_pin = GPIO_PIN_9,
            .gpio_af = GPIO_ALL_RMP_TIM1,
            .info = "TIM1 PE9",
#endif /*TIM1_CH1_PE9*/

#ifdef TIM1_CH2_PA9
            .tim_channel = TIM_CH_2,
            .gpio_periph = GPIOA,
            .gpio_pin = GPIO_PIN_9,
            .gpio_af = 0,
            .info = "TIM1 PA9",
#endif /*TIM1_CH2_PA9*/

#ifdef TIM1_CH2_PE11
            .tim_channel = TIM_CH_2,
            .gpio_periph = GPIOE,
            .gpio_pin = GPIO_PIN_11,
            .gpio_af = GPIO_ALL_RMP_TIM1,
            .info = "TIM1 PE11",
#endif /*TIM1_CH1_PA8*/
        },
#endif /*BSP_USING_TIM1_EXT_COUNTER*/

#ifdef BSP_USING_TIM2_EXT_COUNTER /******CH1=PA0(0,2),PA15(1,3) ; CH2=PA1(0,2),PB3(1,3)******************************* */

        {
            .timer_periph = TIM2,
            .polarity = TIM_IC_POLARITY_RISING,
            .filter = 0x0,
            .irqn = TIM2_IRQn,
#ifdef TIM2_CH1_PA0
            .tim_channel = TIM_CH_1,
            .gpio_periph = GPIOA,
            .gpio_pin = GPIO_PIN_0,
            .gpio_af = 0,
            .info = "TIM2 PA0",
#endif /*TIM2_CH1_PA0*/

#ifdef TIM2_CH1_PA15
            .tim_channel = TIM_CH_1,
            .gpio_periph = GPIOA,
            .gpio_pin = GPIO_PIN_15,
            .gpio_af = GPIO_ALL_RMP_TIM2,
            .info = "TIM2 PA15",
#endif /*TIM2_CH1_PA15*/

#ifdef TIM2_CH2_PA1
            .tim_channel = TIM_CH_2,
            .gpio_periph = GPIOA,
            .gpio_pin = GPIO_PIN_1,
            .gpio_af = 0,
            .info = "TIM2 PA1",
#endif /*TIM2_CH2_PA1*/

#ifdef TIM2_CH2_PB3
            .tim_channel = TIM_CH_2,
            .gpio_periph = GPIOB,
            .gpio_pin = GPIO_PIN_3,
            .gpio_af = GPIO_ALL_RMP_TIM2,
            .info = "TIM2 PB3",
#endif /*TIM2_CH2_PB3*/
        },
#endif /*BSP_USING_TIM2_EXT_COUNTER*/

#ifdef BSP_USING_TIM3_EXT_COUNTER /******Select TIM2 CH1=PA6(0),PB4(2),PC6(3) ; CH2=PA7(0),PB5(2),PC7(3)******************************* */

        {
            .timer_periph = TIM3,
            .polarity = TIM_IC_POLARITY_RISING,
            .filter = 0x0,
            .irqn = TIM3_IRQn,
#ifdef TIM3_CH1_PA6
            .tim_channel = TIM_CH_1,
            .gpio_periph = GPIOA,
            .gpio_pin = GPIO_PIN_6,
            .gpio_af = 0,
            .info = "TIM3 PA6",
#endif /*TIM3_CH1_PA6*/

#ifdef TIM3_CH1_PB4
            .tim_channel = TIM_CH_1,
            .gpio_periph = GPIOB,
            .gpio_pin = GPIO_PIN_4,
            .gpio_af = GPIO_PART1_RMP_TIM3,
            .info = "TIM3 PB4",
#endif /*TIM3_CH1_PB4*/

#ifdef TIM3_CH1_PC6
            .tim_channel = TIM_CH_1,
            .gpio_periph = GPIOC,
            .gpio_pin = GPIO_PIN_6,
            .gpio_af = GPIO_ALL_RMP_TIM3,
            .info = "TIM3 PC6",
#endif /*TIM3_CH1_PC6*/

#ifdef TIM3_CH2_PA7
            .tim_channel = TIM_CH_2,
            .gpio_periph = GPIOA,
            .gpio_pin = GPIO_PIN_7,
            .gpio_af = 0,
            .info = "TIM3 PA7",
#endif /*TIM3_CH2_PA7*/

#ifdef TIM3_CH2_PB5
            .tim_channel = TIM_CH_2,
            .gpio_periph = GPIOB,
            .gpio_pin = GPIO_PIN_5,
            .gpio_af = GPIO_PART1_RMP_TIM3,
            .info = "TIM3 PB5",
#endif /*TIM3_CH2_PB5*/

#ifdef TIM3_CH2_PC7
            .tim_channel = TIM_CH_2,
            .gpio_periph = GPIOC,
            .gpio_pin = GPIO_PIN_7,
            .gpio_af = GPIO_ALL_RMP_TIM3,
            .info = "TIM3 PC7",
#endif /*TIM3_CH2_PC7*/
        },
#endif /*BSP_USING_TIM3_EXT_COUNTER*/

#ifdef BSP_USING_TIM4_EXT_COUNTER /******CH1=PA0(0,2),PA15(1,3) ; CH2=PA1(0,2),PB3(1,3)******************************* */

        {
            .timer_periph = TIM4,
            .polarity = TIM_IC_POLARITY_RISING,
            .filter = 0x0,
            .irqn = TIM4_IRQn,
#ifdef TIM4_CH1_PB6
            .tim_channel = TIM_CH_1,
            .gpio_periph = GPIOB,
            .gpio_pin = GPIO_PIN_6,
            .gpio_af = 0,
            .info = "TIM4 PB6",
#endif /*TIM4_CH1_PB6*/

#ifdef TIM4_CH1_PD12
            .tim_channel = TIM_CH_1,
            .gpio_periph = GPIOD,
            .gpio_pin = GPIO_PIN_12,
            .gpio_af = GPIO_RMP_TIM4,
            .info = "TIM4 PD12",
#endif /*TIM4_CH1_PD12*/

#ifdef TIM4_CH2_PB7
            .tim_channel = TIM_CH_2,
            .gpio_periph = GPIOB,
            .gpio_pin = GPIO_PIN_7,
            .gpio_af = 0,
            .info = "TIM4 PB7",
#endif /*TIM4_CH2_PB7*/

#ifdef TIM4_CH2_PD13
            .tim_channel = TIM_CH_2,
            .gpio_periph = GPIOD,
            .gpio_pin = GPIO_PIN_13,
            .gpio_af = GPIO_RMP_TIM4,
            .info = "TIM4 PD13",
#endif /*TIM4_CH2_PD13*/
        },
#endif /*BSP_USING_TIM4_EXT_COUNTER*/

#ifdef BSP_USING_TIM5_EXT_COUNTER /******Select TIM5 CH1=PA0; CH2=PA1******************************* */

        {
            .timer_periph = TIM5,
            .polarity = TIM_IC_POLARITY_RISING,
            .filter = 0x0,
            .irqn = TIM5_IRQn,
#ifdef TIM5_CH1_PA0
            .tim_channel = TIM_CH_1,
            .gpio_periph = GPIOA,
            .gpio_pin = GPIO_PIN_0,
            .gpio_af = 0,
            .info = "TIM5 PA0",
#endif /*TIM5_CH1_PA0*/

#ifdef TIM5_CH1_PA1
            .tim_channel = TIM_CH_2,
            .gpio_periph = GPIOA,
            .gpio_pin = GPIO_PIN_1,
            .gpio_af = 0,
            .info = "TIM5 PA1",
#endif /*TIM5_CH1_PA1*/

        },
#endif /*BSP_USING_TIM5_EXT_COUNTER*/

#ifdef BSP_USING_TIM8_EXT_COUNTER /******Select TIM8 CH1=PC6(0,1),PD14(3) ; CH2=PC7(0,1),PD15(3)****************************** */

        {
            .timer_periph = TIM8,
            .polarity = TIM_IC_POLARITY_RISING,
            .filter = 0x0,
            .irqn = TIM8_UP_IRQn,
#ifdef TIM8_CH1_PC6
            .tim_channel = TIM_CH_1,
            .gpio_periph = GPIOC,
            .gpio_pin = GPIO_PIN_6,
            .gpio_af = 0,
            .info = "TIM8 PC6",
#endif /*TIM8_CH1_PC6*/

#ifdef TIM8_CH1_PD14
            .tim_channel = TIM_CH_1,
            .gpio_periph = GPIOD,
            .gpio_pin = GPIO_PIN_14,
            .gpio_af = GPIO_RMP3_TIM8,
            .info = "TIM8 PD14",
#endif /*TIM8_CH1_PD14*/

#ifdef TIM8_CH2_PC7
            .tim_channel = TIM_CH_2,
            .gpio_periph = GPIOC,
            .gpio_pin = GPIO_PIN_7,
            .gpio_af = 0,
            .info = "TIM8 PC7",
#endif /*TIM8_CH2_PC7*/

#ifdef TIM8_CH2_PD15
            .tim_channel = TIM_CH_2,
            .gpio_periph = GPIOD,
            .gpio_pin = GPIO_PIN_15,
            .gpio_af = GPIO_RMP3_TIM8,
            .info = "TIM8 PD15",
#endif /*TIM8_CH2_PD15*/
        },
#endif /*BSP_USING_TIM8_EXT_COUNTER*/
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
#define N32_EXT_CLK_CNT_L406
#ifdef BSP_USING_TIM1_EXT_COUNTER
        {

            .timer_periph = TIM1,
            .polarity = TIM_IC_POLARITY_RISING,
            .filter = 0x0,
            .irqn = TIM1_UP_IRQn,
#ifdef TIM1_CH1_PA8
            .tim_channel = TIM_CH_1,
            .gpio_periph = GPIOA,
            .gpio_pin = GPIO_PIN_8,
            .gpio_af = GPIO_AF2_TIM1,
            .info = "TIM1 PA8",
#endif /*TIM1_CH1_PA8*/
        },
#endif /*BSP_USING_TIM1_EXT_COUNTER*/

#ifdef BSP_USING_TIM2_EXT_COUNTER
        {

            .timer_periph = TIM2,
            .polarity = TIM_IC_POLARITY_RISING,
            .filter = 0x0,
            .irqn = TIM1_UP_IRQn,
#ifdef TIM2_CH1_PA0
            .tim_channel = TIM_CH_1,
            .gpio_periph = GPIOA,
            .gpio_pin = GPIO_PIN_0,
            .gpio_af = GPIO_AF2_TIM2,
            .info = "TIM2 PA0",
#endif /*TIM2_CH1_PA0*/
#ifdef TIM2_CH1_PA15
            .tim_channel = TIM_CH_1,
            .gpio_periph = GPIOA,
            .gpio_pin = GPIO_PIN_15,
            .gpio_af = GPIO_AF5_TIM2,
            .info = "TIM2 PA15",
#endif /*TIM2_CH1_PA15*/
#ifdef TIM2_CH2_PA1
            .tim_channel = TIM_CH_2,
            .gpio_periph = GPIOA,
            .gpio_pin = GPIO_PIN_1,
            .gpio_af = GPIO_AF2_TIM2,
            .info = "TIM2 PA1",
#endif /*TIM2_CH2_PA1*/
#ifdef TIM2_CH2_PB3
            .tim_channel = TIM_CH_2,
            .gpio_periph = GPIOB,
            .gpio_pin = GPIO_PIN_3,
            .gpio_af = GPIO_AF2_TIM2,
            .info = "TIM2 PB3",
#endif /*TIM2_CH2_PB3*/
        },
#endif /*BSP_USING_TIM2_EXT_COUNTER*/


#ifdef BSP_USING_TIM3_EXT_COUNTER
        {

            .timer_periph = TIM3,
            .polarity = TIM_IC_POLARITY_RISING,
            .filter = 0x0,
            .irqn = TIM1_UP_IRQn,
#ifdef TIM3_CH1_PA6
            .tim_channel = TIM_CH_1,
            .gpio_periph = GPIOA,
            .gpio_pin = GPIO_PIN_6,
            .gpio_af = GPIO_AF2_TIM3,
            .info = "TIM3 PA6",
#endif /*TIM3_CH1_PA6*/
#ifdef TIM3_CH1_PB4
            .tim_channel = TIM_CH_1,
            .gpio_periph = GPIOB,
            .gpio_pin = GPIO_PIN_4,
            .gpio_af = GPIO_AF5_TIM3,
            .info = "TIM3 PB4",
#endif /*TIM3_CH1_PB4*/
#ifdef TIM3_CH1_PC6
            .tim_channel = TIM_CH_1,
            .gpio_periph = GPIOC,
            .gpio_pin = GPIO_PIN_6,
            .gpio_af = GPIO_AF5_TIM3,
            .info = "TIM3 PC6",
#endif /*TIM3_CH1_PC6*/
#ifdef TIM3_CH2_PA7
            .tim_channel = TIM_CH_2,
            .gpio_periph = GPIOA,
            .gpio_pin = GPIO_PIN_7,
            .gpio_af = GPIO_AF2_TIM3,
            .info = "TIM3 PA7",
#endif /*TIM3_CH2_PA7*/
#ifdef TIM3_CH2_PB5
            .tim_channel = TIM_CH_2,
            .gpio_periph = GPIOB,
            .gpio_pin = GPIO_PIN_5,
            .gpio_af = GPIO_AF2_TIM3,
            .info = "TIM3 PB5",
#endif /*TIM3_CH2_PB5*/
#ifdef TIM3_CH2_PC7
            .tim_channel = TIM_CH_2,
            .gpio_periph = GPIOC,
            .gpio_pin = GPIO_PIN_7,
            .gpio_af = GPIO_AF2_TIM3,
            .info = "TIM3 PC7",
#endif /*TIM3_CH2_PC7*/
        },
#endif /*BSP_USING_TIM3_EXT_COUNTER*/


#endif

};

static struct n32_tim_ext_counter_device tim1_ext_counter_device[EXT_CLK_NUM];
static int rt_hw_tim1_ext_counter_init(void)
{

    char name[32];
    for (int i = 0; i < EXT_CLK_NUM; i++)
    {
        rt_memset(name, 0, 32);
        rt_snprintf(name, 32, "eclktm%d", i);
        n32_tim_ext_counter_register(tim1_ext_counter_device + i,
                                     name,
                                     tim1_ext_counter_config + i);
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_tim1_ext_counter_init);

// /* TIM2外部计数器初始化 */
// #ifdef BSP_USING_TIM2_EXT_COUNTER

// static struct n32_tim_ext_counter_device tim2_ext_counter_device;
// static struct n32_tim_ext_counter_config tim2_ext_counter_config =
//     {
//         .timer_periph = TIM2,
//         .gpio_periph = GPIOA,
//         .gpio_pin = GPIO_PIN_15,      /* PA15 - TIM2_CH1 */
//         .gpio_af = GPIO_ALL_RMP_TIM2, /* TIM2全重映射 */
//         .tim_channel = TIM_CH_1,
//         .polarity = TIM_IC_POLARITY_RISING,
//         .filter = 0x0,
//         .irqn = TIM2_IRQn,
//         .info = "TIM2 PA15"};

// static int rt_hw_tim2_ext_counter_init(void)
// {
//     return n32_tim_ext_counter_register(&tim2_ext_counter_device,
//                                         "eclktm2",
//                                         &tim2_ext_counter_config);
// }
// INIT_DEVICE_EXPORT(rt_hw_tim2_ext_counter_init);
// #endif

// /* TIM3外部计数器初始化 */
// #ifdef BSP_USING_TIM3_EXT_COUNTER
// static struct n32_tim_ext_counter_device tim3_ext_counter_device;
// static struct n32_tim_ext_counter_config tim3_ext_counter_config =
//     {
//         .timer_periph = TIM3,
//         .gpio_periph = GPIOA,
//         .gpio_pin = GPIO_PIN_6, /* PA6 - TIM3_CH1 */
//         .gpio_af = 0,           /* TIM3默认映射 */
//         .tim_channel = TIM_CH_1,
//         .polarity = TIM_IC_POLARITY_RISING,
//         .filter = 0x0,
//         .irqn = TIM3_IRQn,
//         .info = "TIM3 PA6"};

// static int rt_hw_tim3_ext_counter_init(void)
// {
//     return n32_tim_ext_counter_register(&tim3_ext_counter_device,
//                                         "eclktm3",
//                                         &tim3_ext_counter_config);
// }
// INIT_DEVICE_EXPORT(rt_hw_tim3_ext_counter_init);
// #endif

// /* TIM4外部计数器初始化 */
// #ifdef BSP_USING_TIM4_EXT_COUNTER
// static struct n32_tim_ext_counter_device tim4_ext_counter_device;
// static struct n32_tim_ext_counter_config tim4_ext_counter_config =
//     {
//         .timer_periph = TIM4,
//         .gpio_periph = GPIOB,
//         .gpio_pin = GPIO_PIN_6, /* PB6 - TIM4_CH1 */
//         .gpio_af = 0,           /* TIM4默认映射 */
//         .tim_channel = TIM_CH_1,
//         .polarity = TIM_IC_POLARITY_RISING,
//         .filter = 0x0,
//         .irqn = TIM4_IRQn,
//         .info = "TIM4 PB6"};

// static int rt_hw_tim4_ext_counter_init(void)
// {
//     return n32_tim_ext_counter_register(&tim4_ext_counter_device,
//                                         "eclktm4",
//                                         &tim4_ext_counter_config);
// }
// INIT_DEVICE_EXPORT(rt_hw_tim4_ext_counter_init);
// #endif

// /* TIM5外部计数器初始化 */
// #ifdef BSP_USING_TIM5_EXT_COUNTER
// static struct n32_tim_ext_counter_device tim5_ext_counter_device;
// static struct n32_tim_ext_counter_config tim5_ext_counter_config =
//     {
//         .timer_periph = TIM5,
//         .gpio_periph = GPIOA,
//         .gpio_pin = GPIO_PIN_0, /* PA0 - TIM5_CH1 */
//         .gpio_af = 0,           /* TIM5默认映射 */
//         .tim_channel = TIM_CH_1,
//         .polarity = TIM_IC_POLARITY_RISING,
//         .filter = 0x0,
//         .irqn = TIM5_IRQn,
//         .info = "TIM5 PA0"};

// static int rt_hw_tim5_ext_counter_init(void)
// {
//     return n32_tim_ext_counter_register(&tim5_ext_counter_device,
//                                         "eclktm5",
//                                         &tim5_ext_counter_config);
// }
// INIT_DEVICE_EXPORT(rt_hw_tim5_ext_counter_init);
// #endif

// /* TIM8外部计数器初始化 */
// #ifdef BSP_USING_TIM8_EXT_COUNTER
// static struct n32_tim_ext_counter_device tim8_ext_counter_device;
// static struct n32_tim_ext_counter_config tim8_ext_counter_config =
//     {
//         .timer_periph = TIM8,
//         .gpio_periph = GPIOC,
//         .gpio_pin = GPIO_PIN_6, /* PC6 - TIM8_CH1 */
//         .gpio_af = 0,           /* TIM8默认映射 */
//         .tim_channel = TIM_CH_1,
//         .polarity = TIM_IC_POLARITY_RISING,
//         .filter = 0x0,
//         .irqn = TIM8_UP_IRQn,
//         .info = "TIM8 PC6"};

// static int rt_hw_tim8_ext_counter_init(void)
// {
//     return n32_tim_ext_counter_register(&tim8_ext_counter_device,
//                                         "eclktm8",
//                                         &tim8_ext_counter_config);
// }
// INIT_DEVICE_EXPORT(rt_hw_tim8_ext_counter_init);
// #endif

// static void gpio_rcc_enable(GPIO_Module *GPIOx)
// {
//     /* Check the parameters */
//     assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
//     /* Enable the GPIO Clock */
//     if (GPIOx == GPIOA)
//     {
//         RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
//     }
//     else if (GPIOx == GPIOB)
//     {
//         RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
//     }
//     else if (GPIOx == GPIOC)
//     {
//         RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
//     }
//     else if (GPIOx == GPIOD)
//     {
//         RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
//     }
//     else if (GPIOx == GPIOE)
//     {
//         RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOE, ENABLE);
//     }
//     else if (GPIOx == GPIOF)
//     {
//         RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOF, ENABLE);
//     }
//     else if (GPIOx == GPIOG)
//     {
//         RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOG, ENABLE);
//     }
//     LOG_D("%s", __FUNCTION__);
// }

// /*
//     定时器的时钟使能
//     time：定时器编号
// */
// void bsp_time_rcc_en(TIM_Module *time)
// {

//     if (TIM1 == time)
//     {
//         RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1, ENABLE);
//     }
//     else if (TIM8 == time)
//     {
//         RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM8, ENABLE);
//     }
//     else if (TIM2 == time)
//     {
//         RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2, ENABLE);
//     }
//     else if (TIM3 == time)
//     {
//         RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);
//     }
//     else if (TIM4 == time)
//     {
//         RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM4, ENABLE);
//     }
//     else if (TIM5 == time)
//     {
//         RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM5, ENABLE);
//     }
//     else if (TIM6 == time)
//     {
//         RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM6, ENABLE);
//     }
//     else if (TIM7_BASE == time)
//     {
//         RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM7, ENABLE);
//     }
//     LOG_D("%s", __FUNCTION__);
// }

static rt_err_t n32_tim_ext_counter_init_hw(struct n32_tim_ext_counter_device *device)
{
    struct n32_tim_ext_counter_config *config = device->config;
    GPIO_InitType GPIO_InitStructure;
    TIM_TimeBaseInitType TIM_TimeBaseStructure;

    /* 使能时钟 */
    n32_gpio_rcc_enable(config->gpio_periph);
    n32_time_rcc_config(config->timer_periph);
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)

    /* 配置GPIO为输入模式 */
    GPIO_InitStructure.Pin = config->gpio_pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; /* 浮空输入 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitPeripheral(config->gpio_periph, &GPIO_InitStructure);

    /* 配置GPIO复用功能 */
    if (config->gpio_af)
        GPIO_ConfigPinRemap(config->gpio_af, ENABLE);
    if (GPIOA == config->gpio_periph && GPIO_PIN_15 == config->gpio_pin)
    {
        GPIO_ConfigPinRemap(GPIO_RMP_SW_JTAG_SW_ENABLE, ENABLE); /*!< JTAG-DP Disabled and SW-DP Enabled */
        LOG_I("use pa15");
    }
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin = config->gpio_pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Alternate = config->gpio_af;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_Slew_Rate_High;
    GPIO_InitPeripheral(config->gpio_periph, &GPIO_InitStructure);
#endif
    /* 复位定时器 */
    TIM_DeInit(config->timer_periph);

    /* 配置定时器基本参数 */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Period = 0xFFFF; /* 最大计数值 */
    TIM_TimeBaseStructure.Prescaler = 0;   /* 不分频 */
    TIM_TimeBaseStructure.ClkDiv = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.CntMode = TIM_CNT_MODE_UP;
    TIM_InitTimeBase(config->timer_periph, &TIM_TimeBaseStructure);

    /* 配置外部时钟模式1 - 按照手册步骤 */
    uint16_t ext_clk_src;
    if (config->tim_channel == TIM_CH_1)
    {
        ext_clk_src = TIM_EXT_CLK_SRC_TI1;
        LOG_D("Configuring TI1 as external clock source");
    }
    else if (config->tim_channel == TIM_CH_2)
    {
        ext_clk_src = TIM_EXT_CLK_SRC_TI2;
        LOG_D("Configuring TI2 as external clock source");
    }
    else
    {
        LOG_E("Unsupported channel for external clock");
        return RT_ERROR;
    }

    /* 使用库函数配置外部时钟 */
    TIM_ConfigExtTrigAsClk(config->timer_periph, ext_clk_src, config->polarity, config->filter);

    /* 验证配置 - 读取寄存器确认设置 */
    LOG_D("SMCTRL register: 0x%08X", config->timer_periph->SMCTRL);
    LOG_D("CCMOD1 register: 0x%08X", config->timer_periph->CCMOD1);
    LOG_D("CCEN register: 0x%08X", config->timer_periph->CCEN);

    /* 配置更新中断（溢出中断） */
    TIM_ConfigInt(config->timer_periph, TIM_INT_UPDATE, ENABLE);
    TIM_ClearFlag(config->timer_periph, TIM_FLAG_UPDATE); // 中断标志清零

    /* 清零计数器 */
    TIM_SetCnt(config->timer_periph, 0);

    /* 使能定时器 */
    TIM_Enable(config->timer_periph, ENABLE);

    LOG_I("External counter initialized: %s", config->info);
    return RT_EOK;
}

static rt_err_t n32_tim_ext_counter_open(rt_device_t dev, rt_uint16_t oflag)
{
    struct n32_tim_ext_counter_device *device = (struct n32_tim_ext_counter_device *)dev;

    /* 初始化硬件 */
    n32_tim_ext_counter_init_hw(device);

    /* 使能中断 */
    NVIC_SetPriority(device->config->irqn, 3);
    NVIC_EnableIRQ(device->config->irqn);

    LOG_D("External counter %s opened", device->config->name);
    return RT_EOK;
}

static rt_err_t n32_tim_ext_counter_close(rt_device_t dev)
{
    struct n32_tim_ext_counter_device *device = (struct n32_tim_ext_counter_device *)dev;

    /* 禁用定时器 */
    TIM_Enable(device->config->timer_periph, DISABLE);

    /* 禁用中断 */
    NVIC_DisableIRQ(device->config->irqn);

    LOG_D("External counter %s closed", device->config->name);
    return RT_EOK;
}
static rt_ssize_t n32_tim_ext_counter_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    struct n32_tim_ext_counter_device *device = (struct n32_tim_ext_counter_device *)dev;
    rt_uint32_t *count_buf = (rt_uint32_t *)buffer;

    if (size < sizeof(rt_uint32_t))
        return 0;

    /* 读取当前计数值 */
    rt_uint16_t current_count = TIM_GetCnt(device->config->timer_periph);
    device->count_value = (device->overflow_count << 16) + current_count;

    // 清零计数器
    TIM_SetCnt(device->config->timer_periph, 0);
    device->overflow_count = 0;

    *count_buf = device->count_value;
    return sizeof(rt_uint32_t);
}

static rt_err_t n32_tim_ext_counter_control(rt_device_t dev, int cmd, void *args)
{
    struct n32_tim_ext_counter_device *device = (struct n32_tim_ext_counter_device *)dev;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RESUME:
        /* 复位计数器 */
        TIM_SetCnt(device->config->timer_periph, 0);
        device->overflow_count = 0;
        device->count_value = 0;
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* 设置溢出回调函数 */
        if (args)
        {
            struct rt_device_notify *notify = (struct rt_device_notify *)args;
            device->overflow_callback = notify->notify;
            device->callback_args = notify->dev; /* 使用dev字段传递参数 */
        }
        break;

    default:
        return RT_EINVAL;
    }

    return RT_EOK;
}

/* 中断处理函数模板 */
void n32_tim_ext_counter_irq_handler(struct n32_tim_ext_counter_device *device)
{
    rt_interrupt_enter(); // 进入中断
    if (TIM_GetIntStatus(device->config->timer_periph, TIM_INT_UPDATE) != RESET)
    {
        /* 清除中断标志 */
        TIM_ClrIntPendingBit(device->config->timer_periph, TIM_INT_UPDATE);

        /* 溢出计数 */
        device->overflow_count++;

        /* 调用回调函数 */
        if (device->overflow_callback)
        {
            device->overflow_callback((rt_device_t)device->callback_args);
        }
    }
    rt_interrupt_leave(); // 离开中断
}
#ifdef RT_USING_DEVICE_OPS
/**设备操作函数接口 */
static const struct rt_device_ops ops = {
    .init = RT_NULL,
    .open = n32_tim_ext_counter_open,
    .close = n32_tim_ext_counter_close,
    .write = RT_NULL,
    .control = n32_tim_ext_counter_control,
    .read = n32_tim_ext_counter_read,

};
#endif
static rt_err_t n32_tim_ext_counter_register(struct n32_tim_ext_counter_device *device,
                                             const char *name,
                                             struct n32_tim_ext_counter_config *config)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(config != RT_NULL);

    device->config = config;
    device->count_value = 0;
    device->overflow_count = 0;
    device->overflow_callback = RT_NULL;
    device->callback_args = RT_NULL;
    device->parent.type = RT_Device_Class_Miscellaneous;
    device->parent.user_data = config;
#ifdef RT_USING_DEVICE_OPS
    device->parent.ops = &ops;
#else

    device->parent.init = RT_NULL;
    device->parent.open = n32_tim_ext_counter_open;
    device->parent.close = n32_tim_ext_counter_close;
    device->parent.read = n32_tim_ext_counter_read;
    device->parent.write = RT_NULL;
    device->parent.control = n32_tim_ext_counter_control;

#endif
    LOG_I("device name = %s infomations %s", name, config->info);
    return rt_device_register(&device->parent, name, RT_DEVICE_FLAG_RDONLY);
}

/* TIM1外部计数器中断处理 */
#ifdef BSP_USING_TIM1_EXT_COUNTER
void TIM1_UP_IRQHandler(void)
{
    rt_interrupt_enter();
    n32_tim_ext_counter_irq_handler(tim1_ext_counter_device + EXT_CLK_TIM1);
    rt_interrupt_leave();
}
#endif

/* TIM2外部计数器中断处理 */
#ifdef BSP_USING_TIM2_EXT_COUNTER
void TIM2_IRQHandler(void)
{
    rt_interrupt_enter();
    n32_tim_ext_counter_irq_handler(tim1_ext_counter_device + EXT_CLK_TIM2);
    rt_interrupt_leave();
}
#endif

/* TIM3外部计数器中断处理 */
#ifdef BSP_USING_TIM3_EXT_COUNTER
void TIM3_IRQHandler(void)
{
    rt_interrupt_enter();
    n32_tim_ext_counter_irq_handler(tim1_ext_counter_device + EXT_CLK_TIM3);
    rt_interrupt_leave();
}
#endif

/* TIM4外部计数器中断处理 */
#ifdef BSP_USING_TIM4_EXT_COUNTER
void TIM4_IRQHandler(void)
{
    rt_interrupt_enter();
    n32_tim_ext_counter_irq_handler(tim1_ext_counter_device + EXT_CLK_TIM4);
    rt_interrupt_leave();
}
#endif

/* TIM5外部计数器中断处理 */
#ifdef BSP_USING_TIM5_EXT_COUNTER
void TIM5_IRQHandler(void)
{
    rt_interrupt_enter();
    n32_tim_ext_counter_irq_handler(tim1_ext_counter_device + EXT_CLK_TIM5);
    rt_interrupt_leave();
}
#endif

/* TIM8外部计数器中断处理 */
#ifdef BSP_USING_TIM8_EXT_COUNTER
void TIM8_UP_IRQHandler(void)
{
    rt_interrupt_enter();
    n32_tim_ext_counter_irq_handler(tim1_ext_counter_device + EXT_CLK_TIM8);
    rt_interrupt_leave();
}
#endif /**/

/*************************************shell 中断指令用于测试*************************************************************** */
#ifdef RT_USING_FINSH
#include <stdlib.h>
#include <string.h>
#include <finsh.h>

enum pwm_list_parameters
{
    ETR_LIST_PROBE = 1,
    ETR_LIST_GET,
};

CMD_OPTIONS_STATEMENT(eclk_cnt_list)

static int eclk_cnt_list(int argc, char **argv)
{
    rt_err_t result = -RT_ERROR;
    char *result_str;
    static rt_device_t device = RT_NULL;
    int arg2 = 0;
    uint32_t count = 0;
    if (argc > 1)
    {
        if (MSH_OPT_ID_GET(eclk_cnt_list) == ETR_LIST_PROBE)
        {
            if (argc == 3)
            {
                device = rt_device_find(argv[2]);
                if (device)
                {
                    rt_device_open(device, 0);
                }
                result_str = (device == RT_NULL) ? "failure" : "success";
                rt_kprintf("probe %s %s\n", argv[2], result_str);
                return (device == RT_NULL) ? -RT_ERROR : RT_EOK;
            }
            else
            {
                rt_kprintf("eclk_cnt  probe <device name>                  - probe eclk_cnt  by name\n");
                return -RT_EINVAL;
            }
        }
        else if (device == RT_NULL)
        {
            rt_kprintf("Please using 'eclk_cnt  probe <device name>' first.\n");
            return -RT_ERROR;
        }

        switch (MSH_OPT_ID_GET(eclk_cnt_list))
        {

        case ETR_LIST_GET:
            // arg2 = atoi(argv[2]);
            rt_device_read(device, 0, &count, sizeof(count));
            // count = bsp_timer_count_etr_get_count(device);
            rt_kprintf("Info of device count=  [%d]:\n", count);
            return RT_EOK;

            break;

        default:
            goto _usage;
        }
    }
    else
    {
        goto _usage;
    }
    return result;

_usage:
    rt_kprintf("Usage: \n");
    rt_kprintf("eclk_cnt  probe      <device name>                - probe eclk_cnt  by name\n");
    rt_kprintf("eclk_cnt  get                           - get eclk_cnt  cnt info\n");

    result = -RT_ERROR;
    return result;
}
CMD_OPTIONS_NODE_START(eclk_cnt_list)
CMD_OPTIONS_NODE(ETR_LIST_PROBE, probe, probe eclk_cnt name)
CMD_OPTIONS_NODE(ETR_LIST_GET, get, get eclk_cnt count)
CMD_OPTIONS_NODE_END
MSH_CMD_EXPORT_ALIAS(eclk_cnt_list, eclk_cnt, control eclk_cnt device, optenable);

#endif /* RT_USING_FINSH */
/*************************************shell 中断指令用于测试*************************************************************** */

#ifdef BSP_USING_EXT_COUNTER_DEMO
                
#define ETR_DEV_NAME "eclktm1"

static rt_mailbox_t mb_etr;
static void timout_etr(void *parameter)
{
    uint32_t count = 0;
    rt_device_t etr_dev = (rt_device_t)parameter;
    rt_device_read(etr_dev, 0, &count, sizeof(count));
    rt_mb_send_wait(mb_etr, count, 0);
}
static void thd_entry_etr(void *parameter)
{
    uint32_t value = 0;
    while (1)
    {
        if (RT_EOK == rt_mb_recv(mb_etr, &value, RT_WAITING_FOREVER))
        {
            LOG_I("ETR CNT %d", value);
        }
    }
}
static int extr_app_demo(void)
{
    static rt_device_t etr_dev = RT_NULL;
    etr_dev = rt_device_find(ETR_DEV_NAME);
    if (etr_dev)
    {
        rt_device_open(etr_dev, 0);
    }
    else
    {
        LOG_W("ETR device not find");
    }
    mb_etr = rt_mb_create(ETR_DEV_NAME, 5, RT_IPC_FLAG_FIFO);
    RT_ASSERT(mb_etr);
    rt_thread_t thd_etr = rt_thread_create(ETR_DEV_NAME, thd_entry_etr, etr_dev, 512, 20, 5);
    RT_ASSERT(thd_etr);
    rt_thread_startup(thd_etr);
    rt_timer_t timer = rt_timer_create(ETR_DEV_NAME, timout_etr, etr_dev, 1000, RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_HARD_TIMER);
    RT_ASSERT(timer);
    rt_timer_start(timer);
    return RT_EOK;
}
INIT_APP_EXPORT(extr_app_demo);
#endif /* BSP_USING_EXT_COUNTER_DEMO */

#endif /*BSP_USING_TIM_EXT_COUNTER*/
/*************************************************************************************************** */

