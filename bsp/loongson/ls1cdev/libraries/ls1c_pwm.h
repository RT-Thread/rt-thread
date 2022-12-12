/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-06     勤为本       first version
 */


#ifndef __OPENLOONGSON_PWM_H
#define __OPENLOONGSON_PWM_H


// pwm引脚定义
#define LS1C_PWM0_GPIO06                    (6)         // gpio06用作pwm0
#define LS1C_PWM0_GPIO04                    (4)         // gpio04复用为pwm0
#define LS1C_PWM1_GPIO92                    (92)        // gpio92用作pwm1
#define LS1C_PWM1_GPIO05                    (5)         // gpio05复用为pwm1
#define LS1C_PWM2_GPIO52                    (52)        // gpio52复用为pwm2
#define LS1C_PWM2_GPIO46                    (46)        // gpio46复用为pwm2
#define LS1C_PWM3_GPIO47                    (47)        // gpio47复用为pwm3
#define LS1C_PWM3_GPIO53                    (53)        // gpio53复用为pwm3
// ...还有一些gpio可以复用为gpio的，有需要可以自己添加



// pwm控制寄存器的每个bit
#define LS1C_PWM_INT_LRC_EN                 (11)        // 低脉冲计数器中断使能
#define LS1C_PWM_INT_HRC_EN                 (10)        // 高脉冲计数器中断使能
#define LS1C_PWM_CNTR_RST                   (7)         // 使能CNTR计数器清零
#define LS1C_PWM_INT_SR                     (6)         // 中断状态位
#define LS1C_PWM_INTEN                      (5)         // 中断使能位
#define LS1C_PWM_SINGLE                     (4)         // 单脉冲控制位
#define LS1C_PWM_OE                         (3)         // 脉冲输出使能
#define LS1C_PWM_CNT_EN                     (0)         // 主计数器使能


// 硬件pwm工作模式
enum
{
    // 正常模式--连续输出pwm波形
    PWM_MODE_NORMAL = 0,
    
    // 单脉冲模式，每次调用只发送一个脉冲，调用间隔必须大于pwm周期
    PWM_MODE_PULSE
};


// 硬件pwm信息
typedef struct
{
    unsigned int gpio;                      // PWMn所在的gpio
    unsigned int mode;                      // 工作模式(单脉冲、连续脉冲)
    float duty;                             // pwm的占空比
    unsigned long period_ns;                // pwm周期(单位ns)
}pwm_info_t;




/*
 * 初始化PWMn
 * @pwm_info PWMn的详细信息
 */
void pwm_init(pwm_info_t *pwm_info);


/*
 * 禁止pwm
 * @pwm_info PWMn的详细信息
 */
void pwm_disable(pwm_info_t *pwm_info);



/*
 * 使能PWM
 * @pwm_info PWMn的详细信息
 */
void pwm_enable(pwm_info_t *pwm_info);


#endif

