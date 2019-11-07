/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
 *文件名：  lib_scs.c
 *作  者：  Liut
 *版  本：  V1.00
 *日  期：  2017/07/14
 *描  述：  内核模块库函数
 *备  注：  适用于 ES8P508x芯片
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 ***************************************************************/
#include "lib_scs.h"

/***************************************************************
  函数名：NVIC_Init
  描  述：NVIC初始化配置
  输入值：Channel：中断通道 、 Priority：中断优先级 、 Cmd：失能或使能
  输出值：无
  返回值：无
 ***************************************************************/
void NVIC_Init(NVIC_IRQChannel Channel,NVIC_IRQPriority Priority,TYPE_FUNCEN Cmd)
{
    uint32_t tmppriority = 0x00;

    if (Cmd != DISABLE)
    {
        /* Compute the Corresponding IRQ Priority */    
        tmppriority = NVIC->IP[Channel >> 0x02];
        tmppriority &= (uint32_t)(~(((uint32_t)0xFF) << ((Channel & 0x03) * 8)));
        tmppriority |= (uint32_t)((((uint32_t)Priority << 6) & 0xFF) << ((Channel & 0x03) * 8));    

        NVIC->IP[Channel >> 0x02] = tmppriority;

        /* Enable the Selected IRQ Channels */
        NVIC->ISER[0] = (uint32_t)0x01 << (Channel & (uint8_t)0x1F);
    }
    else
    {
        /* Disable the Selected IRQ Channels */
        NVIC->ICER[0] = (uint32_t)0x01 << (Channel & (uint8_t)0x1F);
    }
}

/***************************************************************
  函数名：SCB_SystemLPConfig
  描  述：配置系统休眠模式
  输入值：LowPowerMode：休眠模式 、 NewState：使能、使能
  输出值：无
  返回值：无
 ***************************************************************/
void SCB_SystemLPConfig(SCB_TYPE_SCR LowPowerMode, TYPE_FUNCEN NewState)
{
    if (NewState != DISABLE)
        SCB->SCR |= LowPowerMode;
    else
        SCB->SCR &= (uint32_t)(~(uint32_t)LowPowerMode);
}

/***************************************************************
  函数名：SCB_GetCpuID
  描  述：获取CPUID
  输入值：无
  输出值：无
  返回值：32位ID值
 ***************************************************************/
uint32_t SCB_GetCpuID(void)
{
    return (SCB->CPUID);
}

/***************************************************************
  函数名：SysTick_Init
  描  述：SysTick初始化配置
  输入值：初始化配置结构体地址
  输出值：无
  返回值：无
 ***************************************************************/
void SysTick_Init(SYSTICK_InitStruType* SysT_InitStruct)
{
    uint32_t temp32 = 0;

    SysTick->LOAD = SysT_InitStruct->SysTick_Value;
    SysTick->VAL = (uint32_t)0;

    if(SysT_InitStruct->SysTick_ClkSource != SysTick_ClkS_Base)
        temp32 |= 0x00000004;
    else
        temp32 &= 0xFFFFFFFB;

    if(SysT_InitStruct->SysTick_ITEnable != DISABLE)
        temp32 |= 0x00000002;
    else
        temp32 &= 0xFFFFFFFD;

    SysTick->CTRL = temp32;
}

/*************************END OF FILE**********************/
