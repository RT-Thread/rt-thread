/********************************** (C) COPYRIGHT *******************************
* File Name          : CH57x_timer0.c
* Author             : WCH
* Version            : V1.0
* Date               : 2018/12/15
* Description
*******************************************************************************/

#include "CH57x_common.h"


/*******************************************************************************
* Function Name  : TMR0_TimerInit
* Description    : 定时功能初始化
* Input          : t: 定时时间，基于当前系统时钟Tsys, 最长定时周期 67108864

* Return         : None
*******************************************************************************/
void TMR0_TimerInit( UINT32 t )
{
    R32_TMR0_CNT_END = t;
    R8_TMR0_CTRL_MOD = RB_TMR_ALL_CLEAR;
    R8_TMR0_CTRL_MOD = RB_TMR_COUNT_EN;
}

/*******************************************************************************
* Function Name  : TMR0_EXTSingleCounterInit
* Description    : 外部信号计数功能初始化
* Input          : c: 外部送入信号脉冲计数, 最长计数 67108864
* Return         : None
*******************************************************************************/
void TMR0_EXTSingleCounterInit( UINT32 c )
{
    R32_TMR0_CNT_END = c;
    R8_TMR0_CTRL_MOD = RB_TMR_ALL_CLEAR;
    R8_TMR0_CTRL_MOD = RB_TMR_CAP_COUNT|RB_TMR_MODE_IN|RB_TMR_COUNT_EN;
}

/*******************************************************************************
* Function Name  : TMR0_CountInit
* Description    : 边沿计数功能初始化
* Input          : cap: 采集计数类型
                    CAP_NULL - 不计数
                    Edge_To_Edge - 计数任意边沿
                    FallEdge_To_FallEdge - 计数下降沿
                    RiseEdge_To_RiseEdge - 计数上升沿
* Return         : None
*******************************************************************************/
void TMR0_CountInit( CapModeTypeDef cap )
{
    R8_TMR0_CTRL_MOD = RB_TMR_ALL_CLEAR;
    R8_TMR0_CTRL_MOD = RB_TMR_COUNT_EN      \
                      |RB_TMR_CAP_COUNT     \
                      |RB_TMR_MODE_IN       \
                      |(cap<<6);
}

/*******************************************************************************
* Function Name  : TMR0_PWMInit
* Description    : PWM 输出初始化
* Input          : pr:  select wave polar
                    refer to PWMX_PolarTypeDef
                   ts:  set pwm repeat times
                    refer to PWM_RepeatTsTypeDef
* Return         : None
*******************************************************************************/
void TMR0_PWMInit( PWMX_PolarTypeDef pr, PWM_RepeatTsTypeDef ts )
{
//    R8_TMR0_CTRL_MOD = RB_TMR_ALL_CLEAR;
    R8_TMR0_CTRL_MOD = RB_TMR_COUNT_EN      \
                        |RB_TMR_OUT_EN      \
                        |(pr<<4)            \
                        |(ts<<6);
}


/*******************************************************************************
* Function Name  : TMR0_CapInit
* Description    : 外部信号捕捉功能初始化
* Input          : cap:  select capture mode
                    refer to CapModeTypeDef
* Return         : None
*******************************************************************************/
void TMR0_CapInit( CapModeTypeDef cap )
{
        R8_TMR0_CTRL_MOD = RB_TMR_ALL_CLEAR;
        R8_TMR0_CTRL_MOD = RB_TMR_COUNT_EN      \
                            |RB_TMR_MODE_IN     \
                            |(cap<<6);
}






