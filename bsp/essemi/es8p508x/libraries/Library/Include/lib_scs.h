/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
 *文件名： lib_scs.h
 *作 者： Liut
 *版 本： V1.00
 *日 期： 2017/07/14
 *描 述： 内核模块库函数头文件
 *备 注： 适用于 ES8P508x芯片
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 ***************************************************************/
#ifndef __LIBNVIC_H__
#define __LIBNVIC_H__

#include "ES8P508x.h"
#include "type.h"

/* 中断源选择 */
typedef enum
{
    NVIC_PINT0_IRQn = 0,
    NVIC_PINT1_IRQn = 1,
    NVIC_PINT2_IRQn = 2,
    NVIC_PINT3_IRQn = 3,
    NVIC_PINT4_IRQn = 4,
    NVIC_PINT5_IRQn = 5,
    NVIC_PINT6_IRQn = 6,
    NVIC_PINT7_IRQn = 7,
    NVIC_T16N0_IRQn = 8,
    NVIC_T16N1_IRQn = 9,
    NVIC_T16N2_IRQn = 10,
    NVIC_T16N3_IRQn = 11,
    NVIC_T32N0_IRQn = 12,
    NVIC_IWDT_IRQn = 14,
    NVIC_WWDT_IRQn = 15,
    NVIC_CCM_IRQn = 16,
    NVIC_PLK_IRQn = 17,
    NVIC_LVD_IRQn = 18,
    NVIC_KINT_IRQn = 19,
    NVIC_RTC_IRQn = 20,
    NVIC_ADC_IRQn = 21,
    NVIC_AES_IRQn = 23,
    NVIC_UART0_IRQn = 24,
    NVIC_UART1_IRQn = 25,
    NVIC_UART2_IRQn = 26,
    NVIC_UART3_IRQn = 27,
    NVIC_UART4_IRQn = 28,
    NVIC_UART5_IRQn = 29,
    NVIC_SPI0_IRQn = 30,
    NVIC_I2C0_IRQn = 31,
}NVIC_IRQChannel;

/* 优先级 */
typedef enum
{
    NVIC_Priority_0 = 0x0 ,
    NVIC_Priority_1 = 0x1 ,
    NVIC_Priority_2 = 0x2 ,
    NVIC_Priority_3 = 0x3 ,
}NVIC_IRQPriority;

/* 休眠模式 */
typedef enum
{
    SCB_LP_SleepOnExit = 0x02 , //从ISR中断处理程序返回到线程模式时，是否休眠
    SCB_LP_SleepDeep = 0x04 ,   //深度睡眠
    SCB_LP_SEVOPend = 0x10 ,    //中断挂起时，是否作为唤醒的选择位
}SCB_TYPE_SCR;

/* SysTick时钟源选择 */
typedef enum
{
    SysTick_ClkS_Base = 0x0 , //基准时钟(Hclk/3)
    SysTick_ClkS_Cpu = 0x1 ,  //处理器时钟(Hclk)
}SYST_TYPE_CLKS;

/* SysTick初始化配置结构体定义 */
typedef struct
{
    uint32_t  SysTick_Value;           //递减数值：24位，右对齐
    SYST_TYPE_CLKS  SysTick_ClkSource; //时钟源选择
    TYPE_FUNCEN  SysTick_ITEnable;     //中断使能、失能
}SYSTICK_InitStruType;

/**************模块宏定义*************/

/*SysTick使能*/
#define SysTick_Enable()  (SysTick->CTRL |= 0x00000001)
#define SysTick_Disable() (SysTick->CTRL &= 0xFFFFFFFE)

/************SCS模块函数声明***********/
void NVIC_Init(NVIC_IRQChannel Channel,NVIC_IRQPriority Priority,TYPE_FUNCEN Cmd);
void SCB_SystemLPConfig(SCB_TYPE_SCR LowPowerMode, TYPE_FUNCEN NewState);
uint32_t SCB_GetCpuID(void);
void SysTick_Init(SYSTICK_InitStruType* SysT_InitStruct);
 
#endif

/*************************END OF FILE**********************/
