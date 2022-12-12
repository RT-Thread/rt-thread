/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-06     勤为本       first version
 */


#include "ls1c_clock.h"




/*
 * 延时指定时间，单位ms
 * @j 延时时间，单位ms
 */
void delay_ms(int j)
{
    int k_max = clk_get_cpu_rate()/1000/92;  // 除以1000表示ms，另外一个除数为实验测得的经验值
    int k = k_max;

    for ( ; j > 0; j--)
    {
        for (k = k_max; k > 0; k--)
        {
            __asm__ ("nop");        // 注意，这里必须用内联汇编，否则会被优化掉
        }
    }

    return ;
}


/*
 * 延时指定时间，单位us
 * @n 延时时间，单位us
 */
void delay_us(int n)
{
    int count_1us = 252000000 / 1000000 / 84;           // 延时1us的循环次数
                    // 252000000为cpu频率，除以1000000表示延时单位为us，92为实验测得的经验值
    int count_max;                                      // 延时n微秒的循环次数
    int tmp;

    // 微调
    count_max = n * count_1us;
    if (10 >= n)                // <=10us
    {
        count_max = count_max / 3;
    }
    else if (100 >= n)          // <= 100us
    {
        count_max = count_max - count_max / 5;
    }
    else                        // > 100us
    {
        count_max = count_max - count_max / 10;
    }

    // 延时
    for (tmp = count_max; tmp > 0; tmp--)
    {
        __asm__ ("nop");        // 注意，这里必须用内联汇编，否则会被优化掉            
    }

    return ;
}


/*
 * 延时指定时间，单位s
 * @i 延时时间，单位s
 */
void delay_s(int i)
{
    for ( ; i > 0; i--)
    {
        delay_ms(1000);
    }

    return ;
}



