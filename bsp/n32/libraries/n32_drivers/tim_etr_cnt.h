#ifndef __N32_BSP_TIME_COUNT__ETR_H__
#define __N32_BSP_TIME_COUNT__ETR_H__

/*
    文件功能
*/
/*****************枚举定义 开始*******************/
#include <rtthread.h>


typedef enum
{
#ifdef BSP_USING_TIM1_ETR_CNT
    TIME1_ETR,
#endif
#ifdef BSP_USING_TIM2_ETR_CNT
    TIME2_ETR,
#endif
#ifdef BSP_USING_TIM3_ETR_CNT
    TIME3_ETR,
#endif
#ifdef BSP_USING_TIM4_ETR_CNT
    TIME4_ETR,
#endif

#ifdef BSP_USING_TIM8_ETR_CNT
    TIME8_ETR,
#endif
#ifdef BSP_USING_TIM9_ETR_CNT
    TIME9_ETR,
#endif

    TIME_COUNT_ETR_NUM,
} em_tim_count_etr;

/*****************枚举定义 结束*******************/

/*****************函数声明 结束*******************/

#endif
