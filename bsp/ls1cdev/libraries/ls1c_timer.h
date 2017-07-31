// 硬件定时器头文件


#ifndef __OPENLOONGSON_TIMER_H
#define __OPENLOONGSON_TIMER_H


#include "ls1c_public.h"


// 硬件定时器
typedef enum
{
    TIMER_PWM0,                     // PWM0用作硬件定时器
    TIMER_PWM1,                     // PWM1用作硬件定时器
    TIMER_PWM2,                     // PWM2用作硬件定时器
    TIMER_PWM3                      // PWM3用作硬件定时器
}ls1c_timer_t;


// 硬件定时器信息
typedef struct
{
    ls1c_timer_t timer;                  // 硬件定时器
    unsigned long time_ns;          // 定时时间
}timer_info_t;



/*
 * 初始化定时器，并开始定时
 * @timer_info 定时器和定时时间信息
 */
void timer_init(timer_info_t *timer_info);


/*
 * 判断指定定时器是否超时
 * @timer_info 定时器
 * @ret TRUE or FALSE
 */
BOOL timer_is_time_out(timer_info_t *timer_info);


/*
 * 停止定时器
 * @timer_info 定时器
 */
void timer_stop(timer_info_t *timer_info);



/*
 * 获取定时器从初始化到现在的时间(实现计时功能)，单位ns
 * @timer_info 硬件定时器
 * @ret 时间，单位ns
 */
unsigned long timer_get_time_ns(timer_info_t *timer_info);


/*
 * 打印timer相关寄存器的值
 * @timer_info 硬件定时器
 */
void timer_print_regs(timer_info_t *timer_info);


#endif

