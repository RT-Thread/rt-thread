/******************************************************************************
* Copyright (C) 2017, Huada Semiconductor Co.,Ltd All rights reserved.
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
 **   - 2017-05-10   Cathy     First Version
 **
 *****************************************************************************/

#ifndef __RTC_H__
#define __RTC_H__

/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l136.h"

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
 ** \brief rtc时钟源选择
 *****************************************************************************/
typedef enum en_rtc_clk
{
    RtcClk32768   = 0u, ///<外部32.768k    
    RtcClk32768_1 = 1u, ///<外部32.768k
    RtcClk32      = 2u, ///<内部RC32   
    RtcClk32_1    = 3u, ///<内部RC32
    RtcClkHxt128  = 4u, ///<外部晶振4M
    RtcClkHxt256  = 5u, ///<外部晶振8M
    RtcClkHxt512  = 6u, ///<外部晶振16M
    RtcClkHxt1024 = 7u, ///<外部晶振32M
}en_rtc_clk_t;
/**
 ******************************************************************************
 ** \brief rtc周期中断方式选择
 *****************************************************************************/
typedef enum en_rtc_cyc
{
    RtcPrads = 0u, ///<月、天、时分秒
    RtcPradx = 1u, ///<step 0.5s
}en_rtc_cyc_t;
/**
 ******************************************************************************
 ** \brief rtc 12h制或24h制方式选择
 *****************************************************************************/
typedef enum en_rtc_ampm
{
    Rtc12h = 0u, ///<12h
    Rtc24h = 1u, ///<24h
}en_rtc_ampm_t;
/**
 ******************************************************************************
 ** \brief prds中断周期
 *****************************************************************************/
typedef enum en_rtc_cycprds
{
    Rtc_None   = 0u, ///<无周期中断
    Rtc_05S    = 1u, ///<0.5S中断
    Rtc_1S     = 2u, ///<1s
    Rtc_1Min   = 3u, ///<1min
    Rtc_1H     = 4u, ///<1h
    Rtc_1Day   = 5u, ///<1d
    Rtc_1Mon   = 6u, ///<1月
    Rtc_1Mon_1 = 7u, ///<1月
}en_rtc_cycprds_t;
/**
 ******************************************************************************
 ** \brief rtc周期中断总配置
 *****************************************************************************/
typedef struct stc_rtc_cyc_sel
{
    en_rtc_cyc_t      enCyc_sel; ///<周期类型配置
    en_rtc_cycprds_t  enPrds_sel;///<周期配置
    uint8_t u8Prdx;
}stc_rtc_cyc_sel_t;
/**
 ******************************************************************************
 ** \brief 闹钟源配置
 *****************************************************************************/
typedef struct stc_rtc_alarmset
{
    uint8_t  u8Minute; ///<闹钟分钟
    uint8_t  u8Hour;   ///<闹钟小时
    uint8_t  u8Week;   ///<闹钟周
}stc_rtc_alarmset_t;
/**
 ******************************************************************************
 ** \brief 闹钟中断使能设置
 *****************************************************************************/
typedef enum en_rtc_alarmirq
{
    Rtc_AlarmInt_Disable = 0u,///<闹钟中断禁止
    Rtc_AlarmInt_Enable  = 1u,///<闹钟中断使能
}en_rtc_alarmirq_t;

/**
 ******************************************************************************
 ** \brief rtc 1hz补偿功能开启设置
 *****************************************************************************/
typedef enum en_rtc_compen_en
{
    Rtc_Comp_Disable = 0u,///<时钟补偿禁止
    Rtc_Comp_Enable  = 1u,///<时钟补偿使能
}en_rtc_compen_en_t;
/**
 ******************************************************************************
 ** \brief rtc计数功能使能设置
 *****************************************************************************/
typedef enum en_rtc_count_en
{
    Rtc_Count_Disable = 0u,///<计数禁止
    Rtc_Count_Enable  = 1u,///<计数使能
}en_rtc_count_en_t;
/**
 ******************************************************************************
 ** \brief rtc计数模式还是读写模式状态
 *****************************************************************************/
typedef enum en_rtc_status
{
    RtcRunStatus = 0u, ///<计数状态
    RtcRdWStatus = 1u, ///<读写状态
}en_rtc_status_t;
/**
 ******************************************************************************
 ** \brief rtc 中断请求标志
 *****************************************************************************/
typedef enum en_rtc_status_irq
{
    RtcAlmf  = 0u, ///<闹钟中断请求
    RtcPrdf  = 1u, ///<周期中断请求
}en_rtc_status_irq_t;
/**
 ******************************************************************************
 ** \brief rtc时钟年、月、日、时、分、秒读写结构
 *****************************************************************************/
typedef struct stc_rtc_time
{
    uint8_t  u8Second;      ///<秒    
    uint8_t  u8Minute;      ///<分
    uint8_t  u8Hour;        ///<时
    uint8_t  u8DayOfWeek;   ///<周
    uint8_t  u8Day;         ///<日    
    uint8_t  u8Month;       ///<月
    uint8_t  u8Year;        ///<年
} stc_rtc_time_t;
/**
 ******************************************************************************
 ** \brief rtc功能描述
 ******************************************************************************/
typedef enum en_rtc_func
{
    RtcCount     = 0u,    ///< RTC计数使能
    RtcAlarmEn   = 1u,    ///< RTC闹钟使能
    Rtc_ComenEn  = 2u,    ///<RTC补偿使能
    Rtc1HzOutEn  = 3u,    ///<使能1hz输出
}en_rtc_func_t;
/**
 ******************************************************************************
 ** \brief rtc 闹钟及周期中断处理函数
 *****************************************************************************/
typedef struct stc_rtc_irq_cb
{
    func_ptr_t               pfnAlarmIrqCb; ///<闹钟中断服务函数     
    func_ptr_t               pfnTimerIrqCb; ///<周期中断服务函数
}stc_rtc_irq_cb_t, stc_rtc_intern_cb_t;
/**
 ******************************************************************************
 ** \brief rtc 总体配置结构体
 *****************************************************************************/
typedef struct stc_rtc_config
{
    en_rtc_clk_t          enClkSel;    ///<时钟源配置
    en_rtc_ampm_t        enAmpmSel;    ///<时制配置
    stc_rtc_cyc_sel_t*   pstcCycSel;   ///<周期配置
    stc_rtc_time_t*      pstcTimeDate; ///<时间日期初值配置
    stc_rtc_irq_cb_t*     pstcIrqCb;   ///<中断服务函数
    boolean_t            bTouchNvic;   ///<NVIC中断配置                   
} stc_rtc_config_t;

//rtc 计数时钟源选择
en_result_t Rtc_SelClk(en_rtc_clk_t enClk);
//rtc 计数周期设置
en_result_t Rtc_SetCyc(stc_rtc_cyc_sel_t* pstcCyc);
//rtc ampm模式设置
en_result_t Rtc_SetAmPm(en_rtc_ampm_t enMode);
//rtc时制模式获取
boolean_t Rtc_GetHourMode(void);
//rtc 闹钟相关配置
en_result_t Rtc_SetAlarmTime(stc_rtc_alarmset_t* pstcAlarmTime);
en_result_t Rtc_GetAlarmTime(stc_rtc_alarmset_t* pstcAlarmTime);
//1hz 输出模式及补偿值设置
en_result_t Rtc_Set1HzMode(boolean_t bMode);
en_result_t Rtc_SetCompCr(uint16_t u16Cr);
//周计算
uint8_t Rtc_CalWeek(uint8_t* pu8Date);
//判断是否闰年
uint8_t Rtc_CheckLeapYear(uint8_t u8year);
//12时制上午或下午读取
boolean_t Rtc_RDAmPm(void);
//rtc 读写时间计数器
en_result_t Rtc_WriteDateTime(stc_rtc_time_t* pstcTimeDate,boolean_t bUpdateTime,
                            boolean_t bUpdateDate);
en_result_t Rtc_ReadDateTime(stc_rtc_time_t* pstcTimeDate);
//格式转换函数
uint8_t Change_DateTimeFormat(uint8_t u8sr);
//时间格式检查函数
en_result_t Rtc_CheckDateTimeFormat(uint8_t* pu8TimeDate,uint8_t u8Mode);
//数据大小判断函数
en_result_t Check_BCD_Format(uint8_t u8data, uint8_t u8limit_min, uint8_t u8limit_max);
//获取某年某月最大天数
uint8_t Get_Month_Max_Day(uint8_t u8month, uint8_t u8year);
//rtc 读取当前状态(读写状态或计数状态)，中断请求状态、中断清除状态
en_result_t Rtc_EnAlarmIrq(en_rtc_alarmirq_t enIrqEn);
boolean_t Rtc_RDStatus(void);
boolean_t Rtc_GetIrqStatus(en_rtc_status_irq_t enIrqSel);
en_result_t Rtc_ClrIrqStatus(en_rtc_status_irq_t enIrqSel);

//rtc功能使能禁止函数
en_result_t Rtc_EnableFunc(en_rtc_func_t enFunc);
en_result_t Rtc_DisableFunc(en_rtc_func_t enFunc);
//rtc初始化、禁止函数
en_result_t Rtc_Init(stc_rtc_config_t* pstcRtcConfig);
en_result_t Rtc_DeInit(void);

//@} // RtcGroup

#ifdef __cplusplus
#endif

#endif /* __RTC_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/    


