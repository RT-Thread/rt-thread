// 软件延时源文件


#include "ls1c_clock.h"




/*
 * 延时指定时间，单位ms
 * @j 延时时间，单位ms
 */
void delay_ms(int j)
{
    int k_max = clk_get_cpu_rate()/1000/3;  // 除以1000表示ms，除以3为测试所得的经验(可以理解为最内层循环执行一次需要的时钟个数)
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
    int count_1us = clk_get_cpu_rate() / 1000000 / 3;   // 延时1us的循环次数
    int count_max;                                      // 延时n微秒的循环次数
    int tmp;

    // 根据延时长短微调(注意，这里是手动优化的，cpu频率改变了可能需要重新优化，此时cpu频率为252Mhz)
    if (10 >= n)                // <=10us
    {
        count_1us -= 35;
    }
    else if (100 >= n)          // <= 100us
    {
        count_1us -= 6;
    }
    else                        // > 100us
    {
        count_1us -= 1;
    }
    count_max = n * count_1us;

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



