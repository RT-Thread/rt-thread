/**
 * @file drv_pwm.c
 * @brief
 * @author jiache (wanghuan3037@fiberhome.com)
 * @version 1.0
 * @date 2025-12-02
 *
 * @copyright Copyright (c) 2025  58
 *
 * 2025-12-2
 *      1.PWM驱动的日志加入标签
 *      2.pwm驱动设置都是设置的周期时间单位ns，脉宽也是时间ns
 *      3.pwm驱动使用Kconfig方式配置，将头文件的配置移动到c文件中；定时器1的4个复用通道测试OK
 *      4.定时器2的remap=0，测试PA0-PA3输出pwm OK ；remap=3PA15 PB3 PB10 PB11测试OK
 *      5.定时器3的remap=0，测试PA6,PA7,PB0,PB1输出pwm OK ；定时器3remap=3 PC6-PC9输出测试OK
 *
 *2025-12-06
        1.N32L406的定时器2pwm PA15,PB3，PB10,PB11可用，添加了Kconfig配置
        2.测试发现tim2 的PA0,PA1,输出pwm异常，PA2,PB11输出正常
        3.测试发现tim2 的PA8,PA9,PA10,PA11,输出pwm出正常
        4.测试发现tim3 的PA6,PA7,PB0,PB1,输出pwm出正常
        5.测试发现tim3 的Pb4,pb5,pc8,pc9,输出pwm出正常
        6.测试发现tim3 的pc6,pc7,输出pwm出正常

2025-12-18
    n32g52x的定时器tim1的pa-pa11的pwm配置加上了，未测试
 */
#include <rtconfig.h>
#ifdef BSP_USING_PWM

#define DBG_TAG "PWM"
#include <rtdbg.h>
#define PWM_LOG_E(...) LOG_E(__VA_ARGS__)
#define PWM_LOG_D(...) LOG_I(__VA_ARGS__)

#include <board.h>
#include <rtconfig.h>
#include <drivers\dev_pwm.h>
#include <drv_pwm.h>
#include <drv_base.h>

#define MAX_PERIOD 0xffff
#define MIN_PERIOD 1
#define MIN_PULSE 1

struct n32_pwm_channel
{
    GPIO_Module *gpio_grp; // pwm 使用的gpio分组
    uint16_t pin;          // pwm 使用的gpio pin
    uint16_t pwm_mode;     // pwm 使用的gpio pin
#if defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    uint32_t gpio_af; // 引脚复用功能
#endif
    char *info;
};

struct n32_pwm
{
    struct rt_device_pwm pwm_device; // 设备驱动框架的pwm对象
    TIM_Module *tim;                 // 定时器指针
    struct n32_pwm_channel ch[4];    // 定时器通道
    uint32_t prescaler;              // 定时器预分频系数
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
    uint32_t gpio_af; // 引脚复用功能
#endif
    char *name; // pwm名字也是驱动的名字
};

/**
 * @brief 定义定时器对象
 *
 */
static struct n32_pwm n32_pwm_obj[] =
    {
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
/* ================================================定时器1配置定义================================================*/
#ifdef BSP_USING_TIM1_PWM
        {
            .tim = TIM1,
            .name = "pwm1",

/****************************通道定义*********************************** */

#ifdef TIM1_REMAP_0
            .gpio_af = 0,

#ifdef BSP_USING_TIM1_PWM_CH1
            .ch[0].gpio_grp = GPIOA,
            .ch[0].pin = GPIO_PIN_8,
            .ch[0].pwm_mode = TIM_OCMODE_PWM1,
            .ch[0].info = "TIM1 PWMCH1 PA8",
#endif /* BSP_USING_TIM1_PWM_CH1 */
#ifdef BSP_USING_TIM1_PWM_CH2
            .ch[1].gpio_grp = GPIOA,
            .ch[1].pin = GPIO_PIN_9,
            .ch[1].pwm_mode = TIM_OCMODE_PWM1,
            .ch[1].info = "TIM1 PWMCH2 PA9",
#endif /* BSP_USING_TIM1_PWM_CH2 */
#ifdef BSP_USING_TIM1_PWM_CH3
            .ch[2].gpio_grp = GPIOA,
            .ch[2].pin = GPIO_PIN_10,
            .ch[2].pwm_mode = TIM_OCMODE_PWM1,
            .ch[2].info = "TIM1 PWMCH3 PA10",
#endif /* BSP_USING_TIM1_PWM_CH3 */
#ifdef BSP_USING_TIM1_PWM_CH4
            .ch[3].gpio_grp = GPIOA,
            .ch[3].pin = GPIO_PIN_11,
            .ch[3].pwm_mode = TIM_OCMODE_PWM1,
            .ch[3].info = "TIM1 PWMCH4 PA11",
#endif /* BSP_USING_TIM1_PWM_CH4 */
#endif /*TIM1_REMAP_0*/

#ifdef TIM1_REMAP_3
            .gpio_af = GPIO_ALL_RMP_TIM1,

#ifdef BSP_USING_TIM1_PWM_CH1
            .ch[0].gpio_grp = GPIOE,
            .ch[0].pin = GPIO_PIN_9,
            .ch[0].pwm_mode = TIM_OCMODE_PWM1,
            .ch[0].info = "TIM1 PWMCH1 PE9",
#endif /* TIM1_PWM_CFG_CH1 */
#ifdef BSP_USING_TIM1_PWM_CH2
            .ch[1].gpio_grp = GPIOE,
            .ch[1].pin = GPIO_PIN_11,
            .ch[1].pwm_mode = TIM_OCMODE_PWM1,
            .ch[1].info = "TIM1 PWMCH2 PE11",
#endif /* TIM1_PWM_CFG_CH2 */
#ifdef BSP_USING_TIM1_PWM_CH3
            .ch[2].gpio_grp = GPIOE,
            .ch[2].pin = GPIO_PIN_13,
            .ch[2].pwm_mode = TIM_OCMODE_PWM1,
            .ch[2].info = "TIM1 PWMCH3 PE13",
#endif /* TIM1_PWM_CFG_CH3 */
#ifdef BSP_USING_TIM1_PWM_CH4
            .ch[3].gpio_grp = GPIOE,
            .ch[3].pin = GPIO_PIN_14,
            .ch[3].pwm_mode = TIM_OCMODE_PWM1,
            .ch[3].info = "TIM1 PWMCH4 PE14",
#endif /* TIM1_PWM_CFG_CH4 */
#endif /*TIM1_REMAP_3*/

            /****************************通道定义*********************************** */
        },
#endif /*BSP_USING_TIM1_PWM*/

/* ================================================定时器1配置定义================================================*/

/* ================================================定时器2配置定义================================================*/
#ifdef BSP_USING_TIM2_PWM
        {
            .tim = TIM2,
            .name = "pwm2",

/****************************通道定义*********************************** */

#ifdef TIM2_REMAP_0
            .gpio_af = 0,
#endif
#ifdef TIM2_REMAP_1
            .gpio_af = GPIO_PartialRemap1_TIM2,
#endif
#ifdef TIM2_REMAP_2
            .gpio_af = GPIO_PART2_RMP_TIM2,
#endif
#ifdef TIM2_REMAP_3
            .gpio_af = GPIO_ALL_RMP_TIM2,
#endif

#if defined(TIM2_REMAP_0) || defined(TIM2_REMAP_2)
#ifdef BSP_USING_TIM2_PWM_CH0
            .ch[0].gpio_grp = GPIOA,
            .ch[0].pin = GPIO_PIN_0,
            .ch[0].pwm_mode = TIM_OCMODE_PWM1,
            .ch[0].info = "TIM2 PWMCH0 PA0",
#endif /*TIM2_PWM_CFG_CH1  */

#ifdef BSP_USING_TIM2_PWM_CH1
            .ch[1].gpio_grp = GPIOA,
            .ch[1].pin = GPIO_PIN_1,
            .ch[1].pwm_mode = TIM_OCMODE_PWM1,
            .ch[1].info = "TIM2 PWMCH1 PA1",
#endif /*TIM2_PWM_CFG_CH2  */
#endif /*TIM2_REMAP_1   TIM2_REMAP_3  */

#if defined(TIM2_REMAP_1) || defined(TIM2_REMAP_3)
#ifdef BSP_USING_TIM2_PWM_CH0
            .ch[0].gpio_grp = GPIOA,
            .ch[0].pin = GPIO_PIN_15,
            .ch[0].pwm_mode = TIM_OCMODE_PWM1,
            .ch[0].info = "TIM2 PWMCH0 PA15",
#endif /*TIM2_PWM_CFG_CH1  */

#ifdef BSP_USING_TIM2_PWM_CH1
            .ch[1].gpio_grp = GPIOB,
            .ch[1].pin = GPIO_PIN_3,
            .ch[1].pwm_mode = TIM_OCMODE_PWM1,
            .ch[1].info = "TIM2 PWMCH1 PB3",
#endif /*TIM2_PWM_CFG_CH2  */
#endif /*defined(TIM2_REMAP_2) ||defined(TIM2_REMAP_4)  */

#if defined(TIM2_REMAP_0) || defined(TIM2_REMAP_1)
#ifdef BSP_USING_TIM2_PWM_CH2
            .ch[2].gpio_grp = GPIOA,
            .ch[2].pin = GPIO_PIN_2,
            .ch[2].pwm_mode = TIM_OCMODE_PWM1,
            .ch[2].info = "TIM2 PWMCH2 PA2",
#endif /*TIM2_PWM_CFG_CH2  */
#ifdef BSP_USING_TIM2_PWM_CH3
            .ch[3].gpio_grp = GPIOA,
            .ch[3].pin = GPIO_PIN_3,
            .ch[3].pwm_mode = TIM_OCMODE_PWM1,
            .ch[3].info = "TIM2 PWMCH3 PA3",
#endif /*TIM2_PWM_CFG_CH2  */
#endif /*defined(TIM2_REMAP_0) ||defined(TIM2_REMAP_1)*/

#if defined(TIM2_REMAP_2) || defined(TIM2_REMAP_3)
#ifdef BSP_USING_TIM2_PWM_CH2
            .ch[2].gpio_grp = GPIOB,
            .ch[2].pin = GPIO_PIN_10,
            .ch[2].pwm_mode = TIM_OCMODE_PWM1,
            .ch[2].info = "TIM2 PWMCH2 PB10",
#endif /*TIM2_PWM_CFG_CH2  */
#ifdef BSP_USING_TIM2_PWM_CH3
            .ch[3].gpio_grp = GPIOB,
            .ch[3].pin = GPIO_PIN_11,
            .ch[3].pwm_mode = TIM_OCMODE_PWM1,
            .ch[3].info = "TIM2 PWMCH3 PB11",
#endif /*TIM2_PWM_CFG_CH2  */
#endif /*defined(TIM2_REMAP_2) ||defined(TIM2_REMAP_3)*/

#endif /*BSP_USING_TIM2_PWM*/
        },

/* ================================================定时器3配置定义================================================*/
#ifdef BSP_USING_TIM3_PWM
        {
            .tim = TIM3,
            .name = "pwm3",
#ifdef TIM3_REMAP_0
            .gpio_af = 0,
#endif
#ifdef TIM3_REMAP_2
            .gpio_af = GPIO_PART1_RMP_TIM3,
#endif
#ifdef TIM3_REMAP_3
            .gpio_af = GPIO_ALL_RMP_TIM3,
#endif
#if defined(TIM3_REMAP_0)
#ifdef BSP_USING_TIM3_PWM_CH0
            .ch[0].gpio_grp = GPIOA,
            .ch[0].pin = GPIO_PIN_6,
            .ch[0].pwm_mode = TIM_OCMODE_PWM1,
            .ch[0].info = "TIM3 PWMCH0 PA6",
#endif /*TIM2_PWM_CFG_CH1  */

#ifdef BSP_USING_TIM3_PWM_CH1
            .ch[1].gpio_grp = GPIOA,
            .ch[1].pin = GPIO_PIN_7,
            .ch[1].pwm_mode = TIM_OCMODE_PWM1,
            .ch[1].info = "TIM3 PWMCH1 PA7",
#endif /*TIM2_PWM_CFG_CH2  */
#endif /*TIM2_REMAP_0     */

#if defined(TIM3_REMAP_2)
#ifdef BSP_USING_TIM3_PWM_CH0
            .ch[0].gpio_grp = GPIOB,
            .ch[0].pin = GPIO_PIN_4,
            .ch[0].pwm_mode = TIM_OCMODE_PWM1,
            .ch[0].info = "TIM3 PWMCH0 PB4",
#endif /*TIM2_PWM_CFG_CH1  */

#ifdef BSP_USING_TIM3_PWM_CH1
            .ch[1].gpio_grp = GPIOB,
            .ch[1].pin = GPIO_PIN_5,
            .ch[1].pwm_mode = TIM_OCMODE_PWM1,
            .ch[1].info = "TIM3 PWMCH1 PB5",
#endif /*TIM2_PWM_CFG_CH2  */
#endif /*TIM2_REMAP_2     */

#if defined(TIM3_REMAP_0) || defined(TIM3_REMAP_2)
#ifdef BSP_USING_TIM3_PWM_CH2
            .ch[2].gpio_grp = GPIOB,
            .ch[2].pin = GPIO_PIN_0,
            .ch[2].pwm_mode = TIM_OCMODE_PWM1,
            .ch[2].info = "TIM3 PWMCH2 PB0",
#endif /*BSP_USING_TIM3_PWM_CH2  */
#ifdef BSP_USING_TIM3_PWM_CH3
            .ch[3].gpio_grp = GPIOB,
            .ch[3].pin = GPIO_PIN_1,
            .ch[3].pwm_mode = TIM_OCMODE_PWM1,
            .ch[3].info = "TIM3 PWMCH3 PB1",
#endif /*BSP_USING_TIM3_PWM_CH3  */
#endif /*defined(TIM3_REMAP_0) || defined(TIM3_REMAP_2)*/

#if defined(TIM3_REMAP_3)
#ifdef BSP_USING_TIM3_PWM_CH0
            .ch[0].gpio_grp = GPIOC,
            .ch[0].pin = GPIO_PIN_6,
            .ch[0].pwm_mode = TIM_OCMODE_PWM1,
            .ch[0].info = "TIM3 PWMCH0 PC6",
#endif /*BSP_USING_TIM3_PWM_CH0  */
#ifdef BSP_USING_TIM3_PWM_CH1
            .ch[1].gpio_grp = GPIOC,
            .ch[1].pin = GPIO_PIN_7,
            .ch[1].pwm_mode = TIM_OCMODE_PWM1,
            .ch[1].info = "TIM3 PWMCH1 PC7",
#endif /*BSP_USING_TIM3_PWM_CH1  */
#ifdef BSP_USING_TIM3_PWM_CH2
            .ch[2].gpio_grp = GPIOC,
            .ch[2].pin = GPIO_PIN_8,
            .ch[2].pwm_mode = TIM_OCMODE_PWM1,
            .ch[2].info = "TIM3 PWMCH2 PC8",
#endif /*BSP_USING_TIM3_PWM_CH2  */
#ifdef BSP_USING_TIM3_PWM_CH3
            .ch[3].gpio_grp = GPIOC,
            .ch[3].pin = GPIO_PIN_9,
            .ch[3].pwm_mode = TIM_OCMODE_PWM1,
            .ch[3].info = "TIM3 PWMCH3 PC9",
#endif /*BSP_USING_TIM3_PWM_CH3  */
#endif /*defined(TIM3_REMAP_3)*/
        },
#endif /*BSP_USING_TIM3_PWM */

#else //=========================== defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)=====================

#ifdef BSP_USING_TIM1_PWM //-------------------BSP_USING_TIM1_PWM--------------------------
#define N32L406_CFG
        {
            .tim = TIM1,
            .name = "pwm1",
#ifdef BSP_USING_TIM1_PWM_CH1
            .ch[0].gpio_grp = GPIOA,
            .ch[0].pin = GPIO_PIN_8,
            .ch[0].pwm_mode = TIM_OCMODE_PWM1,
            .ch[0].info = "TIM1 PWMCH1 PA8",
            .ch[0].gpio_af = GPIO_AF2_TIM1,
#endif /* TIM1_PWM_CFG_CH1 */

#ifdef BSP_USING_TIM1_PWM_CH2
            .ch[1].gpio_grp = GPIOA,
            .ch[1].pin = GPIO_PIN_9,
            .ch[1].pwm_mode = TIM_OCMODE_PWM1,
            .ch[1].info = "TIM1 PWMCH2 PA9",
            .ch[1].gpio_af = GPIO_AF2_TIM1,
#endif /* TIM1_PWM_CFG_CH2 */
#ifdef BSP_USING_TIM1_PWM_CH3
            .ch[2].gpio_grp = GPIOA,
            .ch[2].pin = GPIO_PIN_10,
            .ch[2].pwm_mode = TIM_OCMODE_PWM1,
            .ch[2].info = "TIM1 PWMCH3 PA10",
            .ch[2].gpio_af = GPIO_AF2_TIM1,
#endif /* TIM1_PWM_CFG_CH3 */
#ifdef BSP_USING_TIM1_PWM_CH4
            .ch[3].gpio_grp = GPIOA,
            .ch[3].pin = GPIO_PIN_11,
            .ch[3].pwm_mode = TIM_OCMODE_PWM1,
            .ch[3].info = "TIM1 PWMCH4 PA11",
            .ch[3].gpio_af = GPIO_AF2_TIM1,
#endif /* TIM1_PWM_CFG_CH4 */
        },
#endif /*-------------------------------------BSP_USING_TIM1_PWM--------------11111------------*/

#ifdef BSP_USING_TIM2_PWM //-------------------BSP_USING_TIM2_PWM--------------222222------------
#define N32L406_CFG_TIM2
        {
            .tim = TIM2,
            .name = "pwm2",
#ifdef BSP_USING_TIM2_PWM_CH1
#ifdef TIM2_PWM_CH1_PA0
            .ch[0].gpio_grp = GPIOA,
            .ch[0].pin = GPIO_PIN_0,
            .ch[0].info = "TIM2 PWMCH1 PA0",
            .ch[0].gpio_af = GPIO_AF2_TIM2,
#endif /* TIM2_PWM_CH1_PA0 */
#ifdef TIM2_PWM_CH1_PA15
            .ch[0].gpio_grp = GPIOA,
            .ch[0].pin = GPIO_PIN_15,
            .ch[0].info = "TIM2 PWMCH1 PA15",
            .ch[0].gpio_af = GPIO_AF5_TIM2,
#endif /* TIM2_PWM_CH1_PA15 */
            .ch[0].pwm_mode = TIM_OCMODE_PWM1,
#endif /* TIM2_PWM_CFG_CH1 */

#ifdef BSP_USING_TIM2_PWM_CH2
#ifdef TIM2_PWM_CH2_PA1
            .ch[1].gpio_grp = GPIOA,
            .ch[1].pin = GPIO_PIN_1,
            .ch[1].info = "TIM2 PWMCH2 PA1",
#endif /* TIM2_PWM_CH2_PA1 */
#ifdef TIM2_PWM_CH2_PB3
            .ch[1].gpio_grp = GPIOB,
            .ch[1].pin = GPIO_PIN_3,
            .ch[1].info = "TIM2 PWMCH2 PB3",
#endif /* TIM2_PWM_CH2_PB3 */
            .ch[1].gpio_af = GPIO_AF2_TIM2,
            .ch[1].pwm_mode = TIM_OCMODE_PWM1,
#endif /* TIM2_PWM_CFG_CH2 */
#ifdef BSP_USING_TIM2_PWM_CH3
#ifdef TIM2_PWM_CH3_PA2
            .ch[2].gpio_grp = GPIOA,
            .ch[2].pin = GPIO_PIN_2,
            .ch[2].info = "TIM2 PWMCH3 PA2",
#endif /* TIM2_PWM_CH3_PA2 */
#ifdef TIM2_PWM_CH3_PB10
            .ch[2].gpio_grp = GPIOB,
            .ch[2].pin = GPIO_PIN_10,
            .ch[2].info = "TIM2 PWMCH3 PB10",
#endif /* TIM2_PWM_CH3_PB10 */
            .ch[2].pwm_mode = TIM_OCMODE_PWM1,
            .ch[2].gpio_af = GPIO_AF2_TIM2,
#endif /* TIM2_PWM_CFG_CH3 */
#ifdef BSP_USING_TIM2_PWM_CH4
            .ch[3].gpio_grp = GPIOB,
            .ch[3].pin = GPIO_PIN_11,
            .ch[3].info = "TIM2 PWMCH4 PB11",
            .ch[3].gpio_af = GPIO_AF2_TIM2,
            .ch[3].pwm_mode = TIM_OCMODE_PWM1,
#endif /* TIM2_PWM_CFG_CH4 */
        },
#endif /*-------------------------------------BSP_USING_TIM2_PWM-------------------222222-------*/

#ifdef BSP_USING_TIM3_PWM //-------------------BSP_USING_TIM3_PWM--------------33333333------------
#define N32L406_CFG_TIM3
        {
            .tim = TIM3,
            .name = "pwm3",
#ifdef BSP_USING_TIM3_PWM_CH1
#ifdef TIM3_PWM_CH1_PA6
            .ch[0].gpio_grp = GPIOA,
            .ch[0].pin = GPIO_PIN_6,
            .ch[0].info = "TIM3 PWMCH1 PA6",

#endif /* TIM3_PWM_CH1_PA6 */
#ifdef TIM3_PWM_CH1_PB4
            .ch[0].gpio_grp = GPIOB,
            .ch[0].pin = GPIO_PIN_4,
            .ch[0].info = "TIM3 PWMCH1 PB4",
#endif /* TIM3_PWM_CH1_PB4 */
#ifdef TIM3_PWM_CH1_PC6
            .ch[0].gpio_grp = GPIOC,
            .ch[0].pin = GPIO_PIN_6,
            .ch[0].info = "TIM3 PWMCH1 PC6",
#endif /* TIM3_PWM_CH1_PC6 */
            .ch[0].gpio_af = GPIO_AF2_TIM3,
            .ch[0].pwm_mode = TIM_OCMODE_PWM1,
#endif /* TIM3_PWM_CFG_CH1 */

#ifdef BSP_USING_TIM3_PWM_CH2
#ifdef TIM3_PWM_CH2_PA7
            .ch[1].gpio_grp = GPIOA,
            .ch[1].pin = GPIO_PIN_7,
            .ch[1].info = "TIM3 PWMCH2 PA7",
            .ch[1].gpio_af = GPIO_AF2_TIM3,
#endif /* TIM3_PWM_CH2_PA7 */
#ifdef TIM3_PWM_CH2_PB5
            .ch[1].gpio_grp = GPIOB,
            .ch[1].pin = GPIO_PIN_5,
            .ch[1].info = "TIM3 PWMCH2 PB5",
            .ch[1].gpio_af = GPIO_AF4_TIM3,
#endif /* TIM3_PWM_CH2_PB5 */
#ifdef TIM3_PWM_CH2_PC7
            .ch[1].gpio_grp = GPIOC,
            .ch[1].pin = GPIO_PIN_7,
            .ch[1].info = "TIM3 PWMCH2 PC7",
            .ch[1].gpio_af = GPIO_AF2_TIM3,
#endif /* TIM3_PWM_CH2_PC7 */
            .ch[1].pwm_mode = TIM_OCMODE_PWM1,
#endif /* TIM3_PWM_CFG_CH2 */
#ifdef BSP_USING_TIM3_PWM_CH3
#ifdef TIM3_PWM_CH3_PB0
            .ch[2].gpio_grp = GPIOB,
            .ch[2].pin = GPIO_PIN_0,
            .ch[2].info = "TIM3 PWMCH3 PB0",
#endif /* TIM3_PWM_CH3_PB0 */
#ifdef TIM3_PWM_CH3_PC8
            .ch[2].gpio_grp = GPIOC,
            .ch[2].pin = GPIO_PIN_8,
            .ch[2].info = "TIM3 PWMCH3 PC8",
#endif /* TIM3_PWM_CH3_PC8 */
            .ch[2].pwm_mode = TIM_OCMODE_PWM1,
            .ch[2].gpio_af = GPIO_AF2_TIM3,
#endif /* TIM3_PWM_CFG_CH3 */
#ifdef BSP_USING_TIM3_PWM_CH4
#ifdef TIM3_PWM_CH4_PB1
            .ch[3].gpio_grp = GPIOB,
            .ch[3].pin = GPIO_PIN_1,
            .ch[3].info = "TIM3 PWMCH4 PB1",
#endif /* TIM3_PWM_CH4_PB1 */
#ifdef TIM3_PWM_CH4_PC9
            .ch[3].gpio_grp = GPIOC,
            .ch[3].pin = GPIO_PIN_9,
            .ch[3].info = "TIM3 PWMCH4 PC9",
#endif /* TIM3_PWM_CH4_PC9 */
            .ch[3].gpio_af = GPIO_AF2_TIM3,
            .ch[3].pwm_mode = TIM_OCMODE_PWM1,
#endif /* TIM3_PWM_CFG_CH4 */
        },
#endif /*-------------------------------------BSP_USING_TIM3_PWM-------------------3333333-------*/

#endif
};

// /**
//  * @brief 通道配置加载，根据配置宏加载
//  *
//  */
// void n32_load_channel_cfg(void)
// {
//     PWM_LOG_D("%s %d ", __FUNCTION__, __LINE__);
//     /*******************************BSP_USING_TIM1_PWM********************************* */
// #ifdef BSP_USING_TIM1_PWM
//     rt_memset(n32_pwm_obj[TIM1_INDEX].ch, 0, 4 * sizeof(struct n32_pwm_channel));
// #ifdef BSP_USING_TIM2_PWM_CH1
//     struct n32_pwm_channel t1h1 = TIM1_PWM_CFG_CH1;
//     RT_ASSERT(t1h1.ch_num < 4);
//     n32_pwm_obj[TIM1_INDEX].ch[t1h1.ch_num] = t1h1;
// #endif
// #ifdef BSP_USING_TIM1_PWM_CH4
//     struct n32_pwm_channel t1h4 = TIM1_PWM_CFG_CH4;
//     RT_ASSERT(t1h4.ch_num < 4);
//     n32_pwm_obj[TIM1_INDEX].ch[t1h4.ch_num] = t1h4;
// #endif
// #endif
//     /*******************************BSP_USING_TIM2_PWM********************************* */

// #ifdef BSP_USING_TIM2_PWM // 定时器2
//     rt_memset(n32_pwm_obj[TIM2_INDEX].ch, 0, 4 * sizeof(struct n32_pwm_channel));
// #ifdef BSP_USING_TIM2_PWM_CH1 // 通道一
//     struct n32_pwm_channel t2h1 = TIM2_PWM_CFG_CH1;
//     RT_ASSERT(t2h1.ch_num < 4);
//     n32_pwm_obj[TIM2_INDEX].ch[t2h1.ch_num] = t2h1;
// #endif
// #ifdef BSP_USING_TIM2_PWM_CH2 // 通道2
//     struct n32_pwm_channel t2h2 = TIM2_PWM_CFG_CH2;
//     RT_ASSERT(t2h2.ch_num < 4);
//     n32_pwm_obj[TIM2_INDEX].ch[t2h2.ch_num] = t2h2;
// #endif
// #endif
// }
/**
 * 获取定时器时钟频率
 */
static rt_uint32_t tim_clock_get(TIM_Module *htim)
{
    RCC_ClocksType RCC_Clocks;
    RCC_GetClocksFreqValue(&RCC_Clocks);
    if (htim == TIM1 || htim == TIM8)
    {
        return RCC_Clocks.Pclk2Freq * 2;
    }
    else
    {
        return RCC_Clocks.Pclk1Freq * 2;
    }
}

/**
 *
 * 通道pwm输出使能控制
 *
 */
static rt_err_t drv_pwm_enable(struct n32_pwm *pwm, const rt_uint32_t channel, rt_bool_t enable)
{
    TIM_Module *time = pwm->tim;

    uint16_t tim_ch;
    switch (channel)
    {
    case 0:
        tim_ch = TIM_CH_1;
        break;
    case 1:
        tim_ch = TIM_CH_2;
        break;
    case 2:
        tim_ch = TIM_CH_3;
        break;
    case 3:
        tim_ch = TIM_CH_4;

    default:
        break;
    }

    TIM_EnableCapCmpCh(time, tim_ch, enable ? TIM_CAP_CMP_ENABLE : TIM_CAP_CMP_DISABLE);

    PWM_LOG_D("%s %d ch enable ch = %x ", __FUNCTION__, __LINE__, channel);
    return RT_EOK;
}
/*
互补输出使能控制
*/
static rt_err_t drv_pwmn_enable(struct n32_pwm *pwm, const rt_uint16_t channel, rt_bool_t enable)
{
    /* Converts the channel number to the channel number of Hal library */
    uint16_t tim_ch;
    switch (channel)
    {
    case 0:
        tim_ch = TIM_CH_1;
        break;
    case 1:
        tim_ch = TIM_CH_2;
        break;
    case 2:
        tim_ch = TIM_CH_3;
        break;
    case 3:
        tim_ch = TIM_CH_4;

    default:
        break;
    }
    // 互补输出控制
    TIM_EnableCapCmpChN(pwm->tim, tim_ch, enable ? TIM_CAP_CMP_N_ENABLE : TIM_CAP_CMP_N_DISABLE);

    return RT_EOK;
}
/**
 * @brief 获取定时器的工作周期和占空比ns
 */
static rt_err_t drv_pwm_get(struct n32_pwm *pwm, struct rt_pwm_configuration *configuration)
{
    TIM_Module *htim = pwm->tim;

    TIM_Module *tim = pwm->tim;
    // 得到定时器的时钟频率
    rt_uint32_t tim_clock = tim_clock_get(tim);
    /* 转换为纳秒Convert nanosecond to frequency and duty cycle. 1s = 1 * 1000 * 1000 * 1000 ns */
    // 1.计算得到定时器的时钟频率，单位MHz
    tim_clock /= 1000000UL;
    // 计算得到周期，单位nS 重载值x分频值
    uint32_t period = TIM_GetAutoReload(tim) + 1;
    uint32_t psc = tim->PSC + 1;
    configuration->period = period * psc * 1000UL / tim_clock;

    // 计算得到脉宽，单位nS
    uint32_t cmp = 0;
    switch (configuration->channel)
    {
    case 0:
        cmp = TIM_GetCap1(htim);
        break;
    case 1:
        cmp = TIM_GetCap2(htim);
        break;
    case 2:
        cmp = TIM_GetCap3(htim);
        break;
    case 3:
        cmp = TIM_GetCap4(htim);
        break;
    default:
        cmp = 0;
        break;
    }

    configuration->pulse = (cmp + 1) * (psc) * 1000UL / tim_clock;
    PWM_LOG_D("period = %d pulse= %d ", __FUNCTION__, __LINE__, configuration->period, configuration->pulse);

    return RT_EOK;
}

/**
 * @brief 设置定时器的工作周期
 *
 * @param  pwm
 * @param  configuration
 * @return rt_err_t
 */
static rt_err_t drv_pwm_set_period(struct n32_pwm *pwm, struct rt_pwm_configuration *configuration)
{

    rt_uint32_t period;
    rt_uint64_t tim_clock, psc;

    tim_clock = tim_clock_get(pwm->tim);
    /* Convert nanosecond to frequency and duty cycle. 1s = 1 * 1000 * 1000 * 1000 ns */
    tim_clock /= 1000000UL;
    period = (rt_uint64_t)configuration->period * tim_clock / 1000ULL;
    psc = period / MAX_PERIOD + 1;
    period = period / psc;
    // 1.设置分频
    TIM_ConfigPrescaler(pwm->tim, psc - 1, TIM_PSC_RELOAD_MODE_UPDATE);

    if (period < MIN_PERIOD)
    {
        period = MIN_PERIOD;
    }
    // 2.修改重载值，也就是周期
    TIM_SetAutoReload(pwm->tim, period - 1);

    PWM_LOG_D("%s %d psc=%d  period %d ", __FUNCTION__, __LINE__, psc, period);
    return RT_EOK;
}
/**
 * @brief 设置定时器的占空比
 *
 * @param  pwm
 * @param  configuration
 * @return rt_err_t
 */
static rt_err_t drv_pwm_set_pulse(struct n32_pwm *pwm, struct rt_pwm_configuration *configuration)
{

    rt_uint32_t period, pulse;
    rt_uint32_t tim_clock;
    /* Converts the channel number to the channel number of Hal library */
    TIM_Module *tim = pwm->tim;
    tim_clock = tim_clock_get(tim);
    /* Convert nanosecond to frequency and duty cycle. 1s = 1 * 1000 * 1000 * 1000 ns */
    // 1.计算得到定时器的时钟频率，单位MHz
    tim_clock /= 1000000UL;
    // 计算得到比较器的值
    period = (TIM_GetAutoReload(tim) + 1) * (TIM_GetPrescaler(tim) + 1) * 1000UL / tim_clock;
    pulse = (rt_uint64_t)configuration->pulse * (TIM_GetAutoReload(tim) + 1) / period;

    if (pulse < MIN_PULSE)
    {
        pulse = MIN_PULSE;
    }
    /*To determine user input, output high level is required*/
    else if (pulse >= period)
    {
        pulse = period + 1;
    }
    PWM_LOG_D("pulse = %d", pulse);
    // 设置比较值
    switch (configuration->channel)
    {
    case 0:
        TIM_SetCmp1(tim, pulse);
        break;
    case 1:
        TIM_SetCmp2(tim, pulse);
        break;
    case 2:
        TIM_SetCmp3(tim, pulse);
        break;
    case 3:
        TIM_SetCmp4(tim, pulse);
        break;
    default:
        configuration->pulse = 0;
        break;
    }

    TIM_SetCnt(tim, 0);
    TIM_GenerateEvent(tim, TIM_EVT_SRC_UPDATE);

    return RT_EOK;
}

static rt_err_t drv_pwm_set(struct n32_pwm *pwm, struct rt_pwm_configuration *configuration)
{

    rt_uint32_t period, pulse;
    rt_uint32_t tim_clock, psc;
    /* Converts the channel number to the channel number of Hal library */
    TIM_Module *tim = pwm->tim;
    tim_clock = tim_clock_get(tim);
    /* Convert nanosecond to frequency and duty cycle. 1s = 1 * 1000 * 1000 * 1000 ns */
    // 1.计算得到定时器的时钟频率，单位MHz
    tim_clock /= 1000000UL;
    PWM_LOG_D("TIME CLK = %dMHz,PWM fre = %dHz", tim_clock, 1000 * 1000 * 1000 / configuration->period);
    period = (rt_uint64_t)configuration->period * tim_clock / 1000ULL;
    // 得到预分频值
    psc = period / MAX_PERIOD + 1;
    // 得到重载值
    period = period / psc;

    // 1.设置分频
    TIM_ConfigPrescaler(tim, psc - 1, TIM_PSC_RELOAD_MODE_UPDATE);

    if (period < MIN_PERIOD)
    {
        period = MIN_PERIOD;
    }
    // 2.修改重载值，也就是周期
    TIM_SetAutoReload(tim, period - 1);
    // PWM_LOG_D("TIME period %d", period);
    // 计算得到比较器的值
    pulse = (rt_uint64_t)configuration->pulse * tim_clock / psc / 1000ULL;
    if (pulse < MIN_PULSE)
    {
        pulse = MIN_PULSE;
    }
    /*To determine user input, output high level is required*/
    else if (pulse >= period)
    {
        pulse = period + 1;
    }
    PWM_LOG_D("TIME ch %d = pulse %d psc=%d period=%d", configuration->channel, pulse, psc, period);

    // 设置比较值
    switch (configuration->channel)
    {
    case 0:
        TIM_SetCmp1(tim, pulse);
        break;
    case 1:
        TIM_SetCmp2(tim, pulse);
        break;
    case 2:
        TIM_SetCmp3(tim, pulse);
        break;
    case 3:
        TIM_SetCmp4(tim, pulse);
        break;
    default:
        configuration->pulse = 0;
        break;
    }

    TIM_SetCnt(tim, 0);
    TIM_GenerateEvent(tim, TIM_EVT_SRC_UPDATE);

    return RT_EOK;
}

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    struct n32_pwm *pwm = (struct n32_pwm *)device->parent.user_data;
    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        // 互补使能
        if (configuration->complementary)
        {
            drv_pwmn_enable(pwm, configuration->channel, RT_TRUE);
        }
        return drv_pwm_enable(pwm, configuration->channel, RT_TRUE);

    case PWM_CMD_DISABLE:
        if (configuration->complementary)
        {
            drv_pwmn_enable(pwm, configuration->channel, RT_FALSE);
        }
        return drv_pwm_enable(pwm, configuration->channel, RT_FALSE);
    case PWM_CMD_SET:

        return drv_pwm_set(pwm, configuration);
    case PWM_CMD_SET_PERIOD:
        return drv_pwm_set_period(pwm, configuration);
    case PWM_CMD_SET_PULSE:
        return drv_pwm_set_pulse(pwm, configuration);
    case PWM_CMD_GET:
        return drv_pwm_get(pwm, configuration);
    default:
        return -RT_EINVAL;
    }
}

/**
 * @brief  配置pwm输出对应的gpio引脚
 */
static void pwm_time_gpio_config(struct n32_pwm_channel *chanel)

{
    PWM_LOG_D("%s %d config %s is ok", __FUNCTION__, __LINE__, chanel->info);
    GPIO_InitType GPIO_InitStructure;

#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)

    gpio_remap_JTAGOFF_SWDON(chanel->gpio_grp, chanel->pin);

    GPIO_InitStruct(&GPIO_InitStructure);
    /* pwm mode gpio cofig*/
    GPIO_InitStructure.Pin = chanel->pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitPeripheral(chanel->gpio_grp, &GPIO_InitStructure);

#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin = chanel->pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Alternate = chanel->gpio_af;
    GPIO_InitPeripheral(chanel->gpio_grp, &GPIO_InitStructure);

    // GPIO_ConfigPinRemap(GPIOA_PORT_SOURCE, GPIO_PIN_SOURCE0, GPIO_AF2_TIM2);
    // GPIO_ConfigPinRemap(GPIOA_PORT_SOURCE, GPIO_PIN_SOURCE1, GPIO_AF2_TIM2);

#endif
}

static void pwm_oc_init(const rt_uint16_t chanel, const rt_uint16_t mode, TIM_Module *tim)
{
    OCInitType TIM_OCInitStructure;
    /*输出通道配置*/
    TIM_OCInitStructure.OcMode = mode; // pwm的工作模式
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse = 500;
    TIM_OCInitStructure.OcPolarity = TIM_OC_POLARITY_HIGH;

    switch (chanel)
    {

    case 0:
        TIM_InitOc1(tim, &TIM_OCInitStructure);
        TIM_ConfigOc1Preload(tim, TIM_OC_PRE_LOAD_ENABLE);
        break;
    case 1:
        TIM_InitOc2(tim, &TIM_OCInitStructure);
        TIM_ConfigOc2Preload(tim, TIM_OC_PRE_LOAD_ENABLE);
        break;
    case 2:
        TIM_InitOc3(tim, &TIM_OCInitStructure);
        TIM_ConfigOc3Preload(tim, TIM_OC_PRE_LOAD_ENABLE);
        break;
    case 3:
        TIM_InitOc4(tim, &TIM_OCInitStructure);
        TIM_ConfigOc4Preload(tim, TIM_OC_PRE_LOAD_ENABLE);
        break;
    default:

        break;
    }
}

static rt_err_t n32_hw_pwm_init(struct n32_pwm *device)
{
    rt_err_t result = RT_EOK;
    TIM_TimeBaseInitType TIM_TimeBaseStructure;

    RT_ASSERT(device != RT_NULL);
    // 使能时钟
    n32_time_rcc_config(device->tim);

    // 配置定时器
    TIM_TimeBaseStructure.Period = 1000; //
    TIM_TimeBaseStructure.Prescaler = device->prescaler;
    TIM_TimeBaseStructure.ClkDiv = 0;
    TIM_TimeBaseStructure.CntMode = TIM_CNT_MODE_UP;
    TIM_InitTimeBase(device->tim, &TIM_TimeBaseStructure);
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)

    // 时钟使能
    if (device->gpio_af)
    {
        // 引脚重映射
        GPIO_ConfigPinRemap(device->gpio_af, ENABLE);
    }
#endif

    /*输出通道配置*/
    for (int i = 0; i < 4; i++)
    {
        if (device->ch[i].gpio_grp)
        {
            /**gpio rcc */
            n32_gpio_rcc_enable(device->ch[i].gpio_grp);
            // 配置gpio复用功能
            pwm_time_gpio_config(device->ch + i);
            // pwm输出设置
            pwm_oc_init(i, device->ch[i].pwm_mode, device->tim);
            // 关闭输出
            drv_pwm_enable(device, i, RT_FALSE);
        }
    }

    // 使能定时器
    TIM_ConfigArPreload(device->tim, ENABLE);
    TIM_Enable(device->tim, ENABLE);
    // 使能PWM输出通道
    if (device->tim == TIM1 || device->tim == TIM8)
    {
        TIM_EnableCtrlPwmOutputs(device->tim, ENABLE);
    }

    return result;
}

static struct rt_pwm_ops drv_ops =
    {
        .control = drv_pwm_control,
};

static int n32_pwm_init(void)
{
    int i = 0;
    int result = RT_EOK;
    // 加载通道配置
    // n32_load_channel_cfg();

    for (i = 0; i < sizeof(n32_pwm_obj) / sizeof(n32_pwm_obj[0]); i++)
    {
        /* pwm init */
        if (n32_hw_pwm_init(&n32_pwm_obj[i]) != RT_EOK)
        {
            PWM_LOG_E("%s init failed", n32_pwm_obj[i].name);
            result = -RT_ERROR;
            goto __exit;
        }
        else
        {

            /* register pwm device */
            if (rt_device_pwm_register(&n32_pwm_obj[i].pwm_device, n32_pwm_obj[i].name, &drv_ops, n32_pwm_obj + i) == RT_EOK)
            {
                // PWM_LOG_D("%s register success", n32_pwm_obj[i].name);
            }
            else
            {
                PWM_LOG_E("%s register failed", n32_pwm_obj[i].name);
                result = -RT_ERROR;
            }
        }
    }

__exit:
    return result;
}
INIT_DEVICE_EXPORT(n32_pwm_init);

#if 0 // pem demo
#include <rtthread.h>
#include <rtdevice.h>

#define PWM_DEV_NAME "pwm1" /* PWM设备名称 */
#define PWM_DEV_CHANNEL 0   /* PWM通道 */

struct rt_device_pwm *pwm; /* PWM设备句柄 */

static int pwm_led_sample(void)
{
    rt_uint32_t period, pulse;

    period = 1000000;       /* 周期为0.5ms，单位为纳秒ns */
    pulse = period >> 1; /* PWM脉冲宽度值，单位为纳秒ns */
//    pulse=0.1f*period;
    /* 查找设备 */
    pwm = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm == RT_NULL)
    {
        LOG_D("pwm sample run ERROR! can't find %s device!\n", PWM_DEV_NAME);
        return RT_ERROR;
    }

    /* 设置PWM周期和脉冲宽度默认值 */
    // rt_pwm_set(pwm, 0, period, pulse);
    // /* 使能设备 */
    // rt_pwm_enable(pwm, 0);

    // /* 设置PWM周期和脉冲宽度默认值 */
    // rt_pwm_set(pwm, 1, period, pulse);
    // /* 使能设备 */
    // rt_pwm_enable(pwm, 1);

    // /* 设置PWM周期和脉冲宽度默认值 */
    // rt_pwm_set(pwm, 2, period, pulse);
    // /* 使能设备 */
    // rt_pwm_enable(pwm, 2);

    /* 设置PWM周期和脉冲宽度默认值 */
    rt_pwm_set(pwm, 3, period, pulse);
    /* 使能设备 */
    rt_pwm_enable(pwm, 3);
    return 0;
}
/* 导出到 msh 命令列表中 */
// MSH_CMD_EXPORT(pwm_led_sample, pwm sample);

INIT_APP_EXPORT(pwm_led_sample);
#endif

#endif /* BSP_USING_PWM */
