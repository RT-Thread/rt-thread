/******************************************************************************
* Copyright (C) 2019, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/
/*****************************************************************************/
/** \file rtc.h
 **
 ** Headerfile for RTC functions
 **  
 **
 ** History:
 **   - 2019-04-10        First Version
 **
 *****************************************************************************/

#ifndef __RTC_H__
#define __RTC_H__

/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup RtcGroup Real Time Clock (RTC)
 **
 ******************************************************************************/
//@{

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief rtc周期中断的时间间隔                       RTC_CR0  PRDS
 *****************************************************************************/
typedef enum
{
    RtcNone   = 0u, //无周期中断
    Rtc05S    = 1u, //0.5S中断
    Rtc1S     = 2u, //1秒
    Rtc1Min   = 3u, //1分钟
    Rtc1H     = 4u, //1小时
    Rtc1Day   = 5u, //1天
    Rtc1Mon   = 6u  //1月
}en_rtc_prds_t;

/**
 ******************************************************************************
 ** \brief rtc 12h制或24h制方式选择                   RTC_CR0  AMPM
 *****************************************************************************/
typedef enum
{
    RtcAm = 0u,     //12小时制
    RtcPm = 1u      //24小时制
}en_rtc_ampm_t;

/**
 ******************************************************************************
 ** \brief 普通精度与高精度1Hz输出                   RTC_CR0  HZ1SEL
 *****************************************************************************/
typedef enum
{
    RtcHz1selGeneralPricision = 0u,    //普通精度1Hz输出
    RtcHz1selHighPricision = 1u        //高精度1Hz输出
}en_rtc_hz1sel_t;

/**
 ******************************************************************************
 ** \brief 周期中断选择                             RTC_CR0  PRDSEL
 *****************************************************************************/
typedef enum
{
    RtcPrds = 0u,   //使用PRDS所设定的周期中断事件间隔
    RtcPrdx = 1u    //使用PRDX所设定的周期中断事件间隔
}en_rtc_prdsel_t;

/**
 ******************************************************************************
 ** \brief rtc的时钟选择                           RTC_CR1  CKSEL
 *****************************************************************************/
typedef enum 
{
    RtcClkXtl      = 0u, //外部低速时钟XTL  32.768k    
    RtcClkRcl      = 2u, //内部低速时钟RCL  32k   
    RtcClkXth128   = 4u, //外部晶振4M       XTH/128
    RtcClkXth256   = 5u, //外部晶振8M       XTH/256
    RtcClkXth512   = 6u, //外部晶振16M      XTH/512
    RtcClkXth1024  = 7u  //外部晶振32M      XTH/1024
}en_rtc_cksel_t;

/**
 ******************************************************************************
 ** \brief 时钟误差补偿使能或禁止                      RTC_COMPEN  EN
 *****************************************************************************/
typedef enum
{
    RtcCompenDisable = 0u,
    RtcCompenEnable  = 1u
}en_rtc_compen_t;

/**
 ******************************************************************************
** \brief 配置PRD中断使能及其周期类型                      
 *****************************************************************************/
typedef struct
{
    en_rtc_prdsel_t rtcPrdsel;
    uint8_t         rtcPrdx;
    en_rtc_prds_t   rtcPrds;
}stc_rtc_cyccfg_t;

/**
 ******************************************************************************
 ** \brief 闹钟源配置
 *****************************************************************************/
typedef struct
{
    uint8_t  RtcAlarmSec;    //闹钟秒钟
    uint8_t  RtcAlarmMinute; //闹钟分钟
    uint8_t  RtcAlarmHour;   //闹钟小时
    uint8_t  RtcAlarmWeek;   //闹钟周
}stc_rtc_alarmtime_t;

/**
 ******************************************************************************
 ** \brief 时间
 *****************************************************************************/
/**
 ******************************************************************************
 ** \brief rtc时钟年、月、日、时、分、秒读写结构
 *****************************************************************************/
typedef struct stc_rtc_time
{
    uint8_t  u8Second;      //时间：秒    
    uint8_t  u8Minute;      //时间：分
    uint8_t  u8Hour;        //时间：时
    uint8_t  u8DayOfWeek;   //时间：周
    uint8_t  u8Day;         //时间：日    
    uint8_t  u8Month;       //时间：月
    uint8_t  u8Year;        //时间：年
} stc_rtc_time_t;

/**
 ******************************************************************************
 ** \brief 初始化RTC的结构体
 *****************************************************************************/
typedef struct
{
    en_rtc_ampm_t         rtcAmpm;      //小时的时制
    stc_rtc_cyccfg_t      rtcPrdsel;    //确定PRDS或者PRDX所设定的周期中断时间间隔类型
    en_rtc_cksel_t        rtcClksrc;    //实时时钟的时钟源
    en_rtc_compen_t       rtcCompen;    //时钟误差补偿使能与禁止
    uint16_t              rtcCompValue; //使能补偿的情况下，补偿值取值范围为:0-255
    stc_rtc_time_t        rtcTime;      //要写入时间寄存器的时间
}stc_rtc_initstruct_t;

/******************************************************************************
  Global function prototypes (definition in C source)
*******************************************************************************/
//RTC计数器的使能或停止
extern void Rtc_Cmd(boolean_t NewState);
//RTC计数器启动等待函数
extern void Rtc_StartWait(void);
//RTC的1Hz输出的使能或停止
extern void Rtc_Hz1Cmd(en_rtc_hz1sel_t pricision, boolean_t NewState);
//设置周期中断的类型(PRDSEL)及其所选类型的时间(PRDS或PRDX)
extern en_result_t Rtc_SetCyc(stc_rtc_cyccfg_t* pstCyc);
//RTC闹钟中断的使能或停止
extern void Rtc_AlmIeCmd(boolean_t NewState);
//RTC闹钟的使能或停止
extern void Rtc_AlmEnCmd(boolean_t NewState);
//获取RTC闹钟中断状态位
extern boolean_t Rtc_GetAlmfItStatus(void);
//清除RTC闹钟中断状态位
extern void Rtc_ClearAlmfItStatus(void);
//清除RTC周期中断状态位
extern void Rtc_ClearPrdfItStatus(void);
//获取RTC周期中断状态位
extern boolean_t Rtc_GetPridItStatus(void);
//配置RTC的误差补偿寄存器
extern en_result_t Rtc_CompCfg(uint16_t CompVlue, en_rtc_compen_t NewStatus);
//RTC根据日期计算周数
extern en_result_t Check_BCD_Format(uint8_t u8data,uint8_t u8limit_min, uint8_t u8limit_max);
//RTC获取时间函数
extern en_result_t Rtc_ReadDateTime(stc_rtc_time_t* time);
//向RTC时间寄存器写入时间
extern en_result_t Rtc_SetTime(stc_rtc_time_t* time);
//RTC闹钟中断时间获取
extern void Rtc_GetAlarmTime(stc_rtc_alarmtime_t* pstcAlarmTime);
//RTC闹钟设置
extern en_result_t Rtc_SetAlarmTime(stc_rtc_alarmtime_t* pstcAlarmTime);
//初始化RTC
extern void Rtc_Init(stc_rtc_initstruct_t* Rtc_InitStruct);
#endif /* __RTC_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/    


