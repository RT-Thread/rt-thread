 /*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 *                             first version
 */
// 硬件定时器源码

#include <ls1c.h>  
#include "ls1c_public.h"
#include "ls1c_pin.h"
#include "ls1c_clock.h"
#include "ls1c_regs.h"
#include "ls1c_pwm.h"
#include "ls1c_timer.h"


// 定时器中计数器(CNTR、HRC和LRC)的最大值
#define TIMER_COUNTER_MAX               (0xffffff)



/*
 * 获取指定定时器的寄存器基地址
 * @timer 硬件定时器
 * @ret 基地址
 */
unsigned int timer_get_reg_base(ls1c_timer_t timer)
{
    unsigned int reg_base = 0;

    switch (timer)
    {
        case TIMER_PWM0:
            reg_base = LS1C_REG_BASE_PWM0;
            break;

        case TIMER_PWM1:
            reg_base = LS1C_REG_BASE_PWM1;
            break;

        case TIMER_PWM2:
            reg_base = LS1C_REG_BASE_PWM2;
            break;

        case TIMER_PWM3:
            reg_base = LS1C_REG_BASE_PWM3;
            break;
    }

    return reg_base;
}


/*
 * 初始化定时器，并开始定时
 * @timer_info 定时器和定时时间信息
 */
void timer_init(timer_info_t *timer_info)
{
    unsigned int timer_reg_base = 0;        // 寄存器基地址
    unsigned long timer_clk = 0;            // 硬件定时器的时钟
    unsigned long tmp;
    unsigned int ctrl = 0;                  // 控制寄存器中的控制信息
    
    // 判断入参
    if (NULL == timer_info)
    {
        return ;
    }

    /*
     * 把定时时间换算为计数器的值
     * 计数器值 = 定时器的时钟 * 定时时间(单位ns) / 1000000000
     * 龙芯1c的定时器时钟为APB时钟，达到126Mhz，
     * 为避免计算过程发生溢出，这里采用手动优化上面的计算式，也可以采用浮点运算
     */
    timer_clk = clk_get_apb_rate();
    tmp = (timer_clk / 1000000) * (timer_info->time_ns / 1000);     // 将1000000000拆分为1000000和1000
    tmp = MIN(tmp, TIMER_COUNTER_MAX);

    // 控制寄存器信息
    ctrl = (1 << LS1C_PWM_INT_LRC_EN)
           | (0 << LS1C_PWM_INT_HRC_EN)
           | (0 << LS1C_PWM_CNTR_RST)
           | (0 << LS1C_PWM_INT_SR)
           | (1 << LS1C_PWM_INTEN)
           | (1 << LS1C_PWM_SINGLE)
           | (1 << LS1C_PWM_OE)
           | (1 << LS1C_PWM_CNT_EN);

    // 设置各个寄存器
    timer_reg_base = timer_get_reg_base(timer_info->timer);     // 获取寄存器基地址
    reg_write_32(0,                     (volatile unsigned int *)(timer_reg_base + LS1C_PWM_HRC));
    reg_write_32(tmp--,                 (volatile unsigned int *)(timer_reg_base + LS1C_PWM_LRC));
    reg_write_32(0,                     (volatile unsigned int *)(timer_reg_base + LS1C_PWM_CNTR));
    reg_write_32(ctrl,                  (volatile unsigned int *)(timer_reg_base + LS1C_PWM_CTRL));

    return ;
}


/*
 * 判断指定定时器是否超时(实现定时)
 * @timer_info 定时器
 * @ret TRUE or FALSE
 */
BOOL timer_is_time_out(timer_info_t *timer_info)
{
    unsigned int timer_reg_base = 0;        // 寄存器基地址
    unsigned int ctrl;                      // 控制寄存器的值
    
    // 判断入参
    if (NULL == timer_info)
    {
        return FALSE;
    }

    // 读取控制寄存器
    timer_reg_base = timer_get_reg_base(timer_info->timer);
    ctrl = reg_read_32((volatile unsigned int *)(timer_reg_base + LS1C_PWM_CTRL));

    // 判断中断状态位
    if (ctrl & (1 << LS1C_PWM_INT_SR))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}



/*
 * 停止定时器
 * @timer_info 定时器
 */
void timer_stop(timer_info_t *timer_info)
{
    unsigned int timer_reg_base = 0;
    
    // 判断入参
    if (NULL == timer_info)
    {
        return ;
    }

    timer_reg_base = timer_get_reg_base(timer_info->timer);
    reg_write_32(0, (volatile unsigned int *)(timer_reg_base + LS1C_PWM_CTRL));

    return ;
}

/*
 * 获取定时器从初始化到现在的时间(实现计时功能)，单位ns
 * @timer_info 硬件定时器
 * @ret 时间，单位ns
 */
unsigned long timer_get_time_ns(timer_info_t *timer_info)
{
    unsigned int timer_reg_base = 0;
    unsigned int cntr = 0;                  // 寄存器CNTR的值
    unsigned long time_ns = 0;              // 时间，单位ns
    unsigned long timer_clk = 0;            // 定时器时钟

    // 读取寄存器CNTR的值
    timer_reg_base = timer_get_reg_base(timer_info->timer);
    cntr = reg_read_32((volatile unsigned int *)(timer_reg_base + LS1C_PWM_CNTR));

    /*
     * 将CNTR值换算为时间，单位us
     * 时间 = (计数器值CNTR * 1000000000) / 定时器时钟频率
     * 为避免产生溢出，手动优化上式为 时间 = (计数器值CNTR * 1000) / (定时器时钟频率 / 1000000)
     */
    timer_clk = clk_get_apb_rate();
    time_ns = (cntr * 1000 ) / (timer_clk /1000000);
//    printf("[%s] time_us=%lu, cntr=%d, timer_clk=%d\n", __FUNCTION__, time_ns, cntr, timer_clk);

    return time_ns;
}

/*
 * 打印timer相关寄存器的值
 * @timer_info 硬件定时器
 */
void timer_print_regs(timer_info_t *timer_info)
{
    unsigned int timer_reg_base = 0;

    timer_reg_base = timer_get_reg_base(timer_info->timer);
    printf("CNTR=0x%x, HRC=0x%x, LRC=0x%x, CTRL=0x%x\n",
              reg_read_32((volatile unsigned int *)(timer_reg_base + LS1C_PWM_CNTR)),
              reg_read_32((volatile unsigned int *)(timer_reg_base + LS1C_PWM_HRC)),
              reg_read_32((volatile unsigned int *)(timer_reg_base + LS1C_PWM_LRC)),
              reg_read_32((volatile unsigned int *)(timer_reg_base + LS1C_PWM_CTRL)));

    return ;
}

/*
 * 定时器中断清
 * @timer_info 定时器信息
 */
void timer_int_clr(timer_info_t *timer_info)
{
    unsigned int timer_reg_base = 0;        // 寄存器基地址
    unsigned int ctrl ;  
    
    // 判断入参
    if (NULL == timer_info)
    {
        return ;
    }
    timer_reg_base = timer_get_reg_base(timer_info->timer);     // 获取寄存器基地址
    ctrl = reg_read_32((volatile unsigned int *)(timer_reg_base + LS1C_PWM_CTRL));
    ctrl = ctrl | (1<<LS1C_PWM_INT_SR) ;
    reg_write_32(ctrl , (volatile unsigned int *)(timer_reg_base + LS1C_PWM_CTRL));
    ctrl = ctrl & (~(1<<LS1C_PWM_INT_SR))  ;
    reg_write_32(ctrl , (volatile unsigned int *)(timer_reg_base + LS1C_PWM_CTRL));

    return ;
}
/*
 * 定时器计数清
 * @timer_info 定时器信息
 */
void timer_cnt_clr(timer_info_t *timer_info)
{
    unsigned int timer_reg_base = 0;        // 寄存器基地址
    unsigned int ctrl ;  
    
    // 判断入参
    if (NULL == timer_info)
    {
        return ;
    }
    timer_reg_base = timer_get_reg_base(timer_info->timer);     // 获取寄存器基地址
    ctrl = reg_read_32((volatile unsigned int *)(timer_reg_base + LS1C_PWM_CTRL));
    ctrl = ctrl | (1<<LS1C_PWM_CNTR_RST);
    reg_write_32(ctrl , (volatile unsigned int *)(timer_reg_base + LS1C_PWM_CTRL));
    ctrl = ctrl & (~(1<<LS1C_PWM_CNTR_RST)) ;
    reg_write_32(ctrl , (volatile unsigned int *)(timer_reg_base + LS1C_PWM_CTRL));

    return ;
}

/*
 * 初始化定时器，并开始中断定时
 * @timer_info 定时器和定时时间信息
 * @hrc 高中断 lrc 低中断 为1打开，为0关闭
*/
void timer_int_init(timer_info_t *timer_info, int hrc, int lrc)
{
    unsigned int timer_reg_base = 0;        // 寄存器基地址
    unsigned long timer_clk = 0;            // 硬件定时器的时钟
    unsigned long h_value, l_value;
    unsigned int ctrl = 0;                  // 控制寄存器中的控制信息
    
    // 判断入参
    if (NULL == timer_info)
    {
        return ;
    }

    /*
     * 把定时时间换算为计数器的值
     * 计数器值 = 定时器的时钟 * 定时时间(单位ns) / 1000000000
     * 龙芯1c的定时器时钟为APB时钟，达到126Mhz，
     * 为避免计算过程发生溢出，这里采用手动优化上面的计算式，也可以采用浮点运算
     */
    timer_clk = clk_get_apb_rate();
    l_value = (timer_clk / 1000000) * (timer_info->time_ns / 1000);     // 将1000000000拆分为1000000和1000
    l_value = MIN(l_value, TIMER_COUNTER_MAX);
    h_value = (timer_clk / 1000000) * (timer_info->time_h_ns / 1000);     // 将1000000000拆分为1000000和1000
    h_value = MIN(h_value, l_value);

    // 控制寄存器信息
    ctrl = (lrc << LS1C_PWM_INT_LRC_EN)
           | (hrc << LS1C_PWM_INT_HRC_EN)
           | (0 << LS1C_PWM_CNTR_RST)
           | (0 << LS1C_PWM_INT_SR)
           | (1 << LS1C_PWM_INTEN)
           | (1 << LS1C_PWM_SINGLE)
           | (1 << LS1C_PWM_OE)
           | (1 << LS1C_PWM_CNT_EN);

    // 设置各个寄存器
    timer_reg_base = timer_get_reg_base(timer_info->timer);     // 获取寄存器基地址
    reg_write_32(0,                     (volatile unsigned int *)(timer_reg_base + LS1C_PWM_HRC));
    reg_write_32(l_value--,                 (volatile unsigned int *)(timer_reg_base + LS1C_PWM_LRC));
    reg_write_32(h_value--,                 (volatile unsigned int *)(timer_reg_base + LS1C_PWM_HRC));
    reg_write_32(0,                     (volatile unsigned int *)(timer_reg_base + LS1C_PWM_CNTR));
    reg_write_32(ctrl,                  (volatile unsigned int *)(timer_reg_base + LS1C_PWM_CTRL));

    return ;
}
