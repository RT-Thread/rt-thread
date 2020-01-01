/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
 *文件名：  lib_timer.c
 *作  者：  Liut
 *版  本：  V1.00
 *日  期：  2017/07/14
 *描  述：  定时器模块库函数
 *备  注：  适用于 ES8P508x芯片
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 ***************************************************************/
#include "lib_timer.h"

/***************************************************************
  函数名：T16Nx_BaseInit
  描  述：T16Nx基本初始化
  输入值：T16Nx：可以是T16N0/1/2/3 、TIM_BaseInitStruct：初始化配置结构体地址
  输出值：无
  返回值：无
 ***************************************************************/
void T16Nx_BaseInit(T16N_TypeDef* T16Nx,TIM_BaseInitStruType* TIM_BaseInitStruct)
{
    T16Nx->CON0.CS = TIM_BaseInitStruct->TIM_ClkS;
    T16Nx->CON0.SYNC = TIM_BaseInitStruct->TIM_SYNC;
    T16Nx->CON0.EDGE = TIM_BaseInitStruct->TIM_EDGE;
    T16Nx->CON0.MOD = TIM_BaseInitStruct->TIM_Mode;
}
/***************************************************************
  函数名：T32Nx_BaseInit
  描  述：T32Nx基本初始化
  输入值：T32Nx：可以是T32N0 、TIM_BaseInitStruct：初始化配置结构体地址
  输出值：无
  返回值：无
 ***************************************************************/
void T32Nx_BaseInit(T32N_TypeDef* T32Nx,TIM_BaseInitStruType* TIM_BaseInitStruct)
{
    T32Nx->CON0.CS = TIM_BaseInitStruct->TIM_ClkS;
    T32Nx->CON0.SYNC = TIM_BaseInitStruct->TIM_SYNC;
    T32Nx->CON0.EDGE = TIM_BaseInitStruct->TIM_EDGE;
    T32Nx->CON0.MOD = TIM_BaseInitStruct->TIM_Mode;
}
/***************************************************************
  函数名：T16Nx_CapInit
  描  述：T16Nx捕捉初始化
  输入值：：T16Nx：可以是T16N0/1/2/3、 TIM_CapInitStruct：初始化配置结构体地址
  输出值：无
  返回值：无
 ***************************************************************/
void T16Nx_CapInit(T16N_TypeDef* T16Nx,TIM_CapInitStruType* TIM_CapInitStruct)
{
    T16Nx->CON1.CAPPE = TIM_CapInitStruct->TIM_CapRise;
    T16Nx->CON1.CAPNE = TIM_CapInitStruct->TIM_CapFall;
    T16Nx->CON1.CAPIS0 = TIM_CapInitStruct->TIM_CapIS0;
    T16Nx->CON1.CAPIS1 = TIM_CapInitStruct->TIM_CapIS1;
    T16Nx->CON1.CAPT = TIM_CapInitStruct->TIM_CapTime;
}
/***************************************************************
  函数名：T32Nx_CapInit
  描  述：T32Nx捕捉初始化
  输入值：：T32Nx：可以是T32N0、 TIM_CapInitStruct：初始化配置结构体地址
  输出值：无
  返回值：无
 ***************************************************************/
void T32Nx_CapInit(T32N_TypeDef* T32Nx,TIM_CapInitStruType* TIM_CapInitStruct)
{
    T32Nx->CON1.CAPPE = TIM_CapInitStruct->TIM_CapRise;
    T32Nx->CON1.CAPNE = TIM_CapInitStruct->TIM_CapFall;
    T32Nx->CON1.CAPIS0 = TIM_CapInitStruct->TIM_CapIS0;
    T32Nx->CON1.CAPIS1 = TIM_CapInitStruct->TIM_CapIS1;
    T32Nx->CON1.CAPT = TIM_CapInitStruct->TIM_CapTime;
}
/***************************************************************
  函数名：T16Nx_MATxITConfig
  描  述：T16Nx匹配后的工作模式配置
  输入值：T16Nx：可以是T16N0/1/2/3、 Type：匹配后的工作模式
  输出值：无
  返回值：无
 ***************************************************************/
void T16Nx_MAT0ITConfig(T16N_TypeDef* T16Nx,TIM_TYPE_MATCON Type)
{
    T16Nx->CON0.MAT0S = Type;
}
void T16Nx_MAT1ITConfig(T16N_TypeDef* T16Nx,TIM_TYPE_MATCON Type)
{
    T16Nx->CON0.MAT1S = Type;
}
void T16Nx_MAT2ITConfig(T16N_TypeDef* T16Nx,TIM_TYPE_MATCON Type)
{
    T16Nx->CON0.MAT2S = Type;
}
void T16Nx_MAT3ITConfig(T16N_TypeDef* T16Nx,TIM_TYPE_MATCON Type)
{
    T16Nx->CON0.MAT3S = Type;
}
/***************************************************************
  函数名：T32Nx_MATxITConfig
  描  述：T32Nx匹配后的工作模式配置
  输入值：T32Nx：可以是T32N0、 Type：匹配后的工作模式
  输出值：无
  返回值：无
 ***************************************************************/
void T32Nx_MAT0ITConfig(T32N_TypeDef* T32Nx,TIM_TYPE_MATCON Type)
{
    T32Nx->CON0.MAT0S = Type;
}
void T32Nx_MAT1ITConfig(T32N_TypeDef* T32Nx,TIM_TYPE_MATCON Type)
{
    T32Nx->CON0.MAT1S = Type;
}
void T32Nx_MAT2ITConfig(T32N_TypeDef* T32Nx,TIM_TYPE_MATCON Type)
{
    T32Nx->CON0.MAT2S = Type;
}
void T32Nx_MAT3ITConfig(T32N_TypeDef* T32Nx,TIM_TYPE_MATCON Type)
{
    T32Nx->CON0.MAT3S = Type;
}
/***************************************************************
  函数名：T16Nx_MATxOutxConfig
  描  述：T16Nx匹配后的输出端口的模式配置
  输入值：T16Nx：可以是T16N0/1/2/3 、 Type：匹配后端口的工作模式
  输出值：无
  返回值：无
 ***************************************************************/
void T16Nx_MAT0Out0Config(T16N_TypeDef* T16Nx,TIM_TYPE_MATOUT Type)
{
    T16Nx->CON2.MOM0 = Type;
}
void T16Nx_MAT1Out0Config(T16N_TypeDef* T16Nx,TIM_TYPE_MATOUT Type)
{
    T16Nx->CON2.MOM1 = Type;
}
void T16Nx_MAT2Out1Config(T16N_TypeDef* T16Nx,TIM_TYPE_MATOUT Type)
{
    T16Nx->CON2.MOM2 = Type;
}
void T16Nx_MAT3Out1Config(T16N_TypeDef* T16Nx,TIM_TYPE_MATOUT Type)
{
    T16Nx->CON2.MOM3 = Type;
}
/***************************************************************
  函数名：T32Nx_MATxOutxConfig
  描  述：T32Nx匹配后的输出端口的模式配置
  输入值：T32Nx：可以是T32N0 、 Type：匹配后端口的工作模式
  输出值：无
  返回值：无
 ***************************************************************/
void T32Nx_MAT0Out0Config(T32N_TypeDef* T32Nx,TIM_TYPE_MATOUT Type)
{
    T32Nx->CON2.MOM0 = Type;
}
void T32Nx_MAT1Out0Config(T32N_TypeDef* T32Nx,TIM_TYPE_MATOUT Type)
{
    T32Nx->CON2.MOM1 = Type;
}
void T32Nx_MAT2Out1Config(T32N_TypeDef* T32Nx,TIM_TYPE_MATOUT Type)
{
    T32Nx->CON2.MOM2 = Type;
}
void T32Nx_MAT3Out1Config(T32N_TypeDef* T32Nx,TIM_TYPE_MATOUT Type)
{
    T32Nx->CON2.MOM3 = Type;
}
/***************************************************************
  函数名：T16Nx_ITConfig
  描  述：T16N中断配置
  输入值：T16Nx：可以是T16N0/1/2/3、 Type：中断类型 、 NewState：使能/失能
  输出值：无
  返回值：无
 ***************************************************************/
void T16Nx_ITConfig(T16N_TypeDef* T16Nx,TIM_TYPE_IT Type,TYPE_FUNCEN NewState)
{
    if (NewState != DISABLE)
        T16Nx->IE.Word |= (uint32_t)Type;
    else
        T16Nx->IE.Word &= (~(uint32_t)Type);
}
/***************************************************************
  函数名：T32Nx_ITConfig
  描  述：T32N中断配置
  输入值：T32Nx：可以是T32N0、 Type：中断类型 、 NewState：使能/失能
  输出值：无
  返回值：无
 ***************************************************************/
void T32Nx_ITConfig(T32N_TypeDef* T32Nx,TIM_TYPE_IT Type,TYPE_FUNCEN NewState)
{
    if (NewState != DISABLE)
        T32Nx->IE.Word|= (uint32_t)Type;
    else
        T32Nx->IE.Word &= (~(uint32_t)Type);
}
/***************************************************************
  函数名：T16Nx_PWMOutConfig
  描  述：T16N0OUT0,T16N1OUT0、T16N2OUT0、T16N3OUT0 输出配置。原理为使用uart的脉宽调制，因此不能与uart同时使用。
  输入值：
  输出值：无
  返回值：无
 ***************************************************************/
void T16Nx_PWMOutConfig(T16N_TypeDef* T16Nx,T16Nx_PWMInitStruType* T16Nx_PWMInitStruct)
{
    T16Nx->CON2.MOE0 = T16Nx_PWMInitStruct->T16Nx_MOE0;           //配置输出端口0是否使能
    T16Nx->CON2.MOE1 = T16Nx_PWMInitStruct->T16Nx_MOE1;           //配置输出端口1是否使能
    T16Nx->CON2.POL0 = T16Nx_PWMInitStruct->T16Nx_POL0;           //配置T16NxOut0输出极性
    T16Nx->CON2.POL1 = T16Nx_PWMInitStruct->T16Nx_POL1;           //配置T16NxOut1输出极性
}
/***************************************************************
  函数名：T16Nx_PWMBK_Config
  描  述：配置PWM刹车功能
  输入值：T16Nx：可以是T16N0/1/2/3 ,Type 配置PWM刹车结构体
  输出值：无
  返回值：无
 ***************************************************************/
void T16Nx_PWMBK_Config(T16N_TypeDef* T16Nx,T16Nx_PWMBK_Type* type)
{
    T16Nx->CON2.PBKL0 = type->T16Nx_PWMBKL0;        //PWM通道0刹车输出电平选择
    T16Nx->CON2.PBKL1 = type->T16Nx_PWMBKL1;        //PWM通道1刹车输出电平选择
    T16Nx->CON2.PBKS = type->T16Nx_PWMBKS;          //PWM信号源选择
    T16Nx->CON2.PBKPS = type->T16Nx_PWMBKPS;        //PWM通道刹车信号极性选择
    T16Nx->CON2.PBKEN = type->T16Nx_PWMBKEN;        //PWM通道刹车使能
}
/***************************************************************
  函数名：T16Nx_TRG_Config
  描  述: 配置T16N ADC触发使能
  输入值：T16Nx：可以是T16N0/1/2/3 
  输出值：无
  返回值：无
 ***************************************************************/
void T16Nx_TRG_Config(T16N_TypeDef* T16Nx,T16Nx_PWMTRG_type Type,TYPE_FUNCEN NewState)
{
    if(Type == T16Nx_MAT0)
        T16Nx->TRG.MAT0TAR = 1;
    else if(Type == T16Nx_MAT1)
        T16Nx->TRG.MAT1TAR = 1;
    else if(Type == T16Nx_MAT2)
        T16Nx->TRG.MAT2TAR = 1;
    else if(Type == T16Nx_MAT3)
        T16Nx->TRG.MAT3TAR = 1;

    T16Nx->TRG.OVTAR = NewState;
}
/***************************************************************
  函数名：T16Nx_GetPWMBKF
  描  述：获取PWMBKF刹车标志位
  输入值：T16Nx：可以是T16N0/1/2/3 
  输出值：PWMBKF标志位的值。SET：发生刹车事件，RESET：未发生刹车事件
  返回值：无
 ***************************************************************/
FlagStatus T16Nx_GetPWMBKF(T16N_TypeDef* T16Nx)
{
    if(T16Nx->CON2.PBKF == 1)
        return SET;
    else
        return RESET;
}
/***************************************************************
  函数名：T16Nx_ResetPWMBKF
  描  述: 清除PWMBKF标志，标志清除后PWM端口恢复正常shuc
  输入值：T16Nx：可以是T16N0/1/2/3 
  输出值：无
  返回值：无
 ***************************************************************/
void T16Nx_ResetPWMBKF(T16N_TypeDef* T16Nx)
{
    T16Nx->CON2.PBKF = 1;
}
/***************************************************************
  函数名：T16Nx_SetCNT
  描  述：设置计数值
  输入值：T16Nx：可以是T16N0/1/2/3、 Value：16位数值
  输出值：无
  返回值：无
 ***************************************************************/
void T16Nx_SetCNT(T16N_TypeDef* T16Nx,uint16_t Value)
{
    T16Nx->CNT.CNT = Value;
}
/***************************************************************
  函数名：T32Nx_SetCNT
  描  述：设置计数值
  输入值：T32Nx：可以是T32N0、 Value：32位数值（16位时右对齐）
  输出值：无
  返回值：无
 ***************************************************************/
void T32Nx_SetCNT(T32N_TypeDef* T32Nx,uint32_t Value)
{
    T32Nx->CNT.CNT = Value;
}
/***************************************************************
  函数名：T16Nx_SetPRECNT
  描  述：设置预分频计数寄存器值
  输入值：T16Nx：可以是T16N0/1/2/3 、 Value：8位数值
  输出值：无
  返回值：无
 ***************************************************************/
void T16Nx_SetPRECNT(T16N_TypeDef* T16Nx,uint8_t Value)
{
    T16Nx->PRECNT.PRECNT = Value;
}
/***************************************************************
  函数名：T32Nx_SetPRECNT
  描  述：设置预分频计数寄存器值
  输入值：T32Nx：可以是T32N0、  Value：8位数值
  输出值：无
  返回值：无
 ***************************************************************/
void T32Nx_SetPRECNT(T32N_TypeDef* T32Nx,uint8_t Value)
{
    T32Nx->PRECNT.PRECNT = Value - 1;
}
/***************************************************************
  函数名：T16Nx_SetPREMAT
  描  述：设置预分频计数匹配寄存器值
  输入值：T16Nx：可以是T16N0/1/2/3、 Value：8位数值
  输出值：无
  返回值：无
 ***************************************************************/
void T16Nx_SetPREMAT(T16N_TypeDef* T16Nx,uint8_t Value)
{
    T16Nx->PREMAT.PREMAT = Value - 1;
}
/***************************************************************
  函数名：T32Nx_SetPREMAT
  描  述：设置预分频计数匹配寄存器值
  输入值：T32Nx：可以是T32N0、 、 Value：8位数值
  输出值：无
  返回值：无
 ***************************************************************/
void T32Nx_SetPREMAT(T32N_TypeDef* T32Nx,uint8_t Value)
{
    T32Nx->PREMAT.PREMAT = Value - 1;
}
/***************************************************************
  函数名：T16Nx_SetMATx
  描  述：设置匹配寄存器
  输入值：T16Nx：可以是T16N0/1/2/3、 MATx：可以是TIM_MAT0/1/2/3 、 Value：16位数值
  输出值：无
  返回值：无
 ***************************************************************/
void T16Nx_SetMAT0(T16N_TypeDef* T16Nx,uint16_t Value)
{
    T16Nx->MAT0.MAT0 = Value;
}
void T16Nx_SetMAT1(T16N_TypeDef* T16Nx,uint16_t Value)
{
    T16Nx->MAT1.MAT1 = Value;
}
void T16Nx_SetMAT2(T16N_TypeDef* T16Nx,uint16_t Value)
{
    T16Nx->MAT2.MAT2 = Value;
}
void T16Nx_SetMAT3(T16N_TypeDef* T16Nx,uint16_t Value)
{
    T16Nx->MAT3.MAT3 = Value;
}
/***************************************************************
  函数名：T32Nx_SetMATx
  描  述：设置匹配寄存器
  输入值：T32Nx：可以是T32N0、 MATx：可以是TIM_MAT0/1/2/3 、 Value：32位数值
  输出值：无
  返回值：无
 ***************************************************************/
void T32Nx_SetMAT0(T32N_TypeDef* T32Nx,uint32_t Value)
{
    T32Nx->MAT0.MAT0 = Value;
}
void T32Nx_SetMAT1(T32N_TypeDef* T32Nx,uint32_t Value)
{
    T32Nx->MAT1.MAT1 = Value;
}
void T32Nx_SetMAT2(T32N_TypeDef* T32Nx,uint32_t Value)
{
    T32Nx->MAT2.MAT2 = Value;
}
void T32Nx_SetMAT3(T32N_TypeDef* T32Nx,uint32_t Value)
{
    T32Nx->MAT3.MAT3 = Value;
}
/***************************************************************
  函数名：T16Nx_GetMATx
  描  述：读取匹配寄存器值
  输入值：T16Nx：可以是T16N0/1/2/3
  输出值：无
  返回值：16位数值
 ***************************************************************/
uint16_t T16Nx_GetMAT0(T16N_TypeDef* T16Nx)
{
    return (T16Nx->MAT0.MAT0);
}
uint16_t T16Nx_GetMAT1(T16N_TypeDef* T16Nx)
{
    return (T16Nx->MAT1.MAT1);
}
uint16_t T16Nx_GetMAT2(T16N_TypeDef* T16Nx)
{
    return (T16Nx->MAT2.MAT2);
}
uint16_t T16Nx_GetMAT3(T16N_TypeDef* T16Nx)
{
    return (T16Nx->MAT3.MAT3);
}
/***************************************************************
  函数名：T32Nx_GetMATx
  描  述：读取匹配寄存器值
  输入值：T32Nx：可以是T32N0/3 MATx：可以是TIM_MAT0/1/2/3
  输出值：无
  返回值：32位数值
 ***************************************************************/
uint32_t T32Nx_GetMAT0(T32N_TypeDef* T32Nx)
{
    return (T32Nx->MAT0.MAT0);
}
uint32_t T32Nx_GetMAT1(T32N_TypeDef* T32Nx)
{
    return (T32Nx->MAT1.MAT1);
}
uint32_t T32Nx_GetMAT2(T32N_TypeDef* T32Nx)
{
    return (T32Nx->MAT2.MAT2);
}
uint32_t T32Nx_GetMAT3(T32N_TypeDef* T32Nx)
{
    return (T32Nx->MAT3.MAT3);
}
/***************************************************************
  函数名：T16Nx_GetCNT
  描  述：读取计数寄存器值
  输入值：T16Nx：可以是T16N0/1/2/3、
  返回值：16位数值
 ***************************************************************/
uint16_t T16Nx_GetCNT(T16N_TypeDef* T16Nx)
{
    return (T16Nx->CNT.CNT);
}
/***************************************************************
  函数名：T32Nx_GetCNT
  描  述：读取计数寄存器值
  输入值：T32Nx：可以是T32N0/3、
  返回值：16/32位数值
 ***************************************************************/
uint32_t T32Nx_GetCNT(T32N_TypeDef* T32Nx)
{
    return (T32Nx->CNT.CNT);
}
/***************************************************************
  函数名：T16Nx_GetPRECNT
  描  述：读取预分频计数寄存器值
  输入值：T16Nx：可以是T16N0/1/2/3
  输出值：无
  返回值：8位数值
 ***************************************************************/
uint8_t T16Nx_GetPRECNT(T16N_TypeDef* T16Nx)
{
    return (uint8_t)(T16Nx->PRECNT.PRECNT);
}
/***************************************************************
  函数名：T32Nx_GetPRECNT
  描  述：读取预分频计数寄存器值
  输入值：T32Nx：可以是T32N0
  输出值：无
  返回值：8位数值
 ***************************************************************/
uint8_t T32Nx_GetPRECNT(T32N_TypeDef* T32Nx)
{
    return (uint8_t)(T32Nx->PRECNT.PRECNT);
}
/***************************************************************
  函数名：T16Nx_GetFlagStatus
  描  述：读取指定标志位
  输入值：T16Nx：可以是T16N0/1/2/3、 TIM_Flag：中断标志位
  输出值：无
  返回值：RESET/SET
 ***************************************************************/
FlagStatus T16Nx_GetFlagStatus(T16N_TypeDef* T16Nx,TIM_TYPE_IF TIM_Flag)
{
    FlagStatus bitstatus = RESET;

    if((T16Nx->IF.Word & (uint32_t)TIM_Flag) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return bitstatus;
}
/***************************************************************
  函数名：T32Nx_GetFlagStatus
  描  述：读取指定标志位
  输入值：T32Nx：可以是T32N0、、 TIM_Flag：中断标志位
  输出值：无
  返回值：RESET/SET
 ***************************************************************/
FlagStatus T32Nx_GetFlagStatus(T32N_TypeDef* T32Nx,TIM_TYPE_IF TIM_Flag)
{
    FlagStatus bitstatus = RESET;

    if((T32Nx->IF.Word & (uint32_t)TIM_Flag) != (uint32_t)RESET)
        bitstatus = SET;
    else
        bitstatus = RESET;

    return bitstatus;
}

/***************************************************************
  函数名：T16Nx_GetITStatus
  描  述：读取指定中断标志位,未使能相应中断时不会返回SET
  输入值：T16Nx：可以是T16N0/1/2/3、 TIM_Flag：中断标志位
  输出值：无
  返回值：RESET/SET
 ***************************************************************/
ITStatus T16Nx_GetITStatus(T16N_TypeDef* T16Nx,TIM_TYPE_IT TIM_Flag)
{
    ITStatus bitstatus = RESET;
    uint32_t itstatus = 0x0, itenable = 0x0;

    itstatus = T16Nx->IF.Word & (uint32_t)TIM_Flag;
    itenable = T16Nx->IE.Word & (uint32_t)TIM_Flag;

    if ((itstatus != (uint32_t)RESET) && (itenable != (uint32_t)RESET))
        bitstatus = SET;
    else
        bitstatus = RESET;

    return bitstatus;
}
/***************************************************************
  函数名：T32Nx_GetITStatus
  描  述：读取指定中断标志位,未使能相应中断时不会返回SET
  输入值：T32Nx：可以是T32N0、 TIM_Flag：中断标志位
  输出值：无
  返回值：RESET/SET
 ***************************************************************/
ITStatus T32Nx_GetITStatus(T32N_TypeDef* T32Nx,TIM_TYPE_IT TIM_Flag)
{
    ITStatus bitstatus = RESET;
    uint32_t itstatus = 0x0, itenable = 0x0;

    itstatus = T32Nx->IF.Word  & (uint32_t)TIM_Flag;
    itenable = T32Nx->IE.Word  & (uint32_t)TIM_Flag;

    if ((itstatus != (uint32_t)RESET) && (itenable != (uint32_t)RESET))
        bitstatus = SET;
    else
        bitstatus = RESET;

    return bitstatus;
}
/***************************************************************
  函数名：T16Nx_ClearIFPendingBit
  描  述：清除指定的中断标志位
  输入值：T16Nx：可以是T16N0/1/2/3、 TIM_Flag：中断标志位
  输出值：无
  返回值：无
 ***************************************************************/
void T16Nx_ClearIFPendingBit(T16N_TypeDef* T16Nx,TIM_TYPE_IF TIM_Flag)
{
    T16Nx->IF.Word = (uint32_t)TIM_Flag;
}
/***************************************************************
  函数名：T32Nx_ClearIFPendingBit
  描  述：清除指定的中断标志位
  输入值：T32Nx：可以是T32N0、 TIM_Flag：中断标志位
  输出值：无
  返回值：无
 ***************************************************************/
void T32Nx_ClearIFPendingBit(T32N_TypeDef* T32Nx,TIM_TYPE_IF TIM_Flag)
{
    T32Nx->IF.Word = (uint32_t)TIM_Flag;
}

/*************************END OF FILE**********************/
