/*************************************************************************************
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
/******************************************************************************/
/** \file rtc.c
 **
 ** RTC function driver API.
 ** @link SampleGroup Some description @endlink
 **
 **   - 2019-04-10    First version 
 **
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "hc32l196_rtc.h"
/**
 ******************************************************************************
 ** \addtogroup RtcGroup
 ******************************************************************************/
//@{

/******************************************************************************/
/* Local pre-processor symbols/macros ('#define')                             */
/******************************************************************************/

/******************************************************************************/
/* Local function prototypes ('const')                                       */
/******************************************************************************/
const uint8_t Leap_Month_Base[]     =    {3,6,0,3,5,1,3,6,2,4,0,2};
const uint8_t NonLeap_Month_Base[]  =    {4,0,0,3,5,1,3,6,2,4,0,2};
const uint8_t Cnst_Month_Tbl[12]={0x31,0x28,0x31,0x30,0x31,0x30,0x31,0x31,0x30,0x31,0x30,0x31};
/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/

/******************************************************************************/
/* Local variable prototypes ('static')                                       */
/******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/
 
/**
******************************************************************************
    ** \brief  RTC计数器的使能或停止
    ** 
    ** @param  NewState : TRUE 或 FALSE
    ** \retval 无
    **
******************************************************************************/ 
void Rtc_Cmd(boolean_t NewState)
{
    SetBit((uint32_t)(&(M0P_RTC->CR0)), 7, NewState);
}

/**
******************************************************************************
    ** \brief  RTC计数器启动等待函数，如启动RTC计数器后立即进入低功耗模式，
    **         进入低功耗模式之前需执行此函数，以确保RTC已启动完成
    ** 
    ** @param  NewState : TRUE 或 FALSE
    ** \retval 无
    **
******************************************************************************/ 
void Rtc_StartWait(void)
{
    M0P_RTC->CR1_f.WAIT = 1;
    while (M0P_RTC->CR1_f.WAITF != 1)  //等待直到WAITF=1
    {
        ;
    }
    M0P_RTC->CR1_f.WAIT = 0;
    while (M0P_RTC->CR1_f.WAITF != 0)  //等待直到WAITF=0 
    {
        ;
    }
}
 
/**
******************************************************************************
    ** \brief  RTC的1Hz输出的使能或停止
    ** @param  pricision : RtcHz1selGeneralPricision 或 RtcHz1selHighPricision
    ** @param  NewState : Hz1o_Disable 或 HZ1o_Enable
    ** \retval 无
    **
******************************************************************************/ 
void Rtc_Hz1Cmd(en_rtc_hz1sel_t pricision, boolean_t NewState)
{
    SetBit((uint32_t)(&(M0P_RTC->CR0)), 6, pricision);  //设置普通精度或者高精度1Hz输出
    SetBit((uint32_t)(&(M0P_RTC->CR0)), 5, NewState);   //设置1Hz输出使能或禁止
}    

/**
******************************************************************************
    ** \brief  设置周期中断的类型(PRDSEL)及其所选类型的时间(PRDS或PRDX)
    ** 
  ** @param   pstCyc: 根据结构体的定义设置PRDSEL、PRDS与PRDX
    ** \retval  Ok、Error 或 ErrorInvalidParameter
    **
******************************************************************************/ 
en_result_t Rtc_SetCyc(stc_rtc_cyccfg_t* pstCyc)
{
    en_result_t enRet = Error;
    M0P_RTC->CR0_f.PRDSEL = pstCyc->rtcPrdsel;
    if(pstCyc->rtcPrdsel == RtcPrds)
    {
        M0P_RTC->CR0_f.PRDS = pstCyc->rtcPrds; 
    }
    else if(pstCyc->rtcPrdsel == RtcPrdx)
    {
        if(pstCyc->rtcPrdx>=64)
        {
            enRet = ErrorInvalidParameter;
            return enRet;
        }
        M0P_RTC->CR0_f.PRDX = pstCyc->rtcPrdx;
    }
    else
    {
        ;
    }
    enRet = Ok;
    return enRet;
}    

/**
******************************************************************************
    ** \brief  RTC闹钟中断的使能或停止
    ** 
    ** @param  NewState : TRUE 或 FALSE
    ** \retval 无
    **
******************************************************************************/
void Rtc_AlmIeCmd(boolean_t NewState)
{
    SetBit((uint32_t)(&(M0P_RTC->CR1)), 3, 0);        //清除周期中断标志位
    SetBit((uint32_t)(&(M0P_RTC->CR1)), 4, 0);        //清除周期中断标志位
    SetBit((uint32_t)(&(M0P_RTC->CR1)), 6, NewState);
}
 
/**
******************************************************************************
    ** \brief  RTC闹钟的使能或停止
    ** 
    ** @param  NewState : Almen_Disable 或 Almen_Enable
    ** \retval 无
    **
******************************************************************************/ 
void Rtc_AlmEnCmd(boolean_t NewState)
{
    SetBit((uint32_t)(&(M0P_RTC->CR1)), 7, NewState);
}

/**
******************************************************************************
    ** \brief  获取RTC闹钟中断状态位
    ** 
    ** @param  无
    ** \retval TRUE 或 FALSE
    **
******************************************************************************/
boolean_t Rtc_GetAlmfItStatus(void)
{
    return GetBit((uint32_t)(&(M0P_RTC->CR1)), 4);
}

/**
******************************************************************************
    ** \brief  清除RTC闹钟中断状态位
    ** 
    ** @param  无
    ** \retval 无
    **
******************************************************************************/
void Rtc_ClearAlmfItStatus(void)
{
    SetBit((uint32_t)(&(M0P_RTC->CR1)), 4, 0);
}

/**
******************************************************************************
    ** \brief  清除RTC周期中断状态位
    ** 
    ** @param  无
    ** \retval 无
    **
******************************************************************************/
void Rtc_ClearPrdfItStatus(void)
{
    SetBit((uint32_t)(&(M0P_RTC->CR1)), 3, 0);
}

/**
******************************************************************************
    ** \brief  获取RTC周期中断状态位
    ** 
    ** @param  无
    ** \retval TRUE 或 FALSE
    **
******************************************************************************/
boolean_t Rtc_GetPridItStatus(void)
{
    return GetBit((uint32_t)(&(M0P_RTC->CR1)), 3);
}

/**
******************************************************************************
    ** \brief  配置RTC的误差补偿寄存器
    ** 
    ** @param  CompValue:数值的范围为：32-256
    ** @param  NewStatus: RtcCompenDisable 或 RtcAmCompenEnable
    ** \retval Ok  ErrorInvalidParameter
    **
******************************************************************************/
en_result_t Rtc_CompCfg(uint16_t CompVlue, en_rtc_compen_t NewStatus)
{
    en_result_t enRet = Error;
    if(CompVlue<=256)
    {
        M0P_RTC->COMPEN_f.EN = NewStatus;
        M0P_RTC->COMPEN_f.CR = CompVlue;
    }
    else
    {
        enRet = ErrorInvalidParameter;
    }
    return enRet;
}

/**
 ******************************************************************************
 ** \brief  RTC根据日期计算周数
 **
 ** \param pu8buf时间数据
 ** \param u8limit_min最小值
 ** \param u8limit_max最大值
 **
 ** \retval Error 错误，Ok校验正确
 ** 
 ******************************************************************************/
en_result_t Check_BCD_Format(uint8_t u8data,uint8_t u8limit_min, uint8_t u8limit_max)
{

    if (((u8data & 0x0F) > 0x09) || ((u8data & 0xF0) > 0x90)
    ||(u8data > u8limit_max) || (u8data < u8limit_min))
    {
        return Error;
    }
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  RTC 平、闰年检测
 **
** \param  u8year:年十进制低两位:0-99
 **
 ** \retval  1:闰年  0：平年
 **
 ******************************************************************************/
uint8_t Rtc_CheckLeapYear(uint8_t u8year)
{
        uint16_t tmp;
        tmp=2000+u8year;
        if((((tmp % 4)==0) && ((tmp % 100) !=0))|| ((tmp % 400) ==0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 ******************************************************************************
 ** \brief  RTC根据年获取二月的天数
 **
 ** \param [in] u8month月份，u8year年份
 **
** \retval u8day天数:28或29
 ** 
 ******************************************************************************/
uint8_t Get_Month2_Day( uint8_t u8year)
{
    uint8_t u8day = 0;
    
    u8day = 28;
    if(Rtc_CheckLeapYear(u8year) == 1)
    {
        u8day++;
    }
    return u8day;
}

/**
 ******************************************************************************
 ** \brief  RTC获取时间函数
 **
 ** \param time: 用于存放读取自时间寄存器的时间数据，格式为BCD码格式
 **
 ** \retval Ok  获取正常
 ** \retval ErrorTimeout 时间溢出错误
 ******************************************************************************/
en_result_t Rtc_ReadDateTime(stc_rtc_time_t* time)
{
    uint32_t u32TimeOut;
    ASSERT(NULL != pstcTimeDate);  
    u32TimeOut = 1000;
    if(1 == M0P_RTC->CR0_f.START)
    {
        M0P_RTC->CR1_f.WAIT = 1;
        while(u32TimeOut--)
        {
            if(M0P_RTC->CR1_f.WAITF)
            {
            break;
            }
        }
        if(u32TimeOut==0)
        {
            return ErrorTimeout;
        }
    }
    time->u8Second  = M0P_RTC->SEC;
    time->u8Minute  = M0P_RTC->MIN;
    if(1 == M0P_RTC->CR0_f.AMPM)
    {
        time->u8Hour   = M0P_RTC->HOUR;
    }
    else
    {
        time->u8Hour   = M0P_RTC->HOUR&0x1f;
    }
    time->u8Day       = M0P_RTC->DAY;
    time->u8DayOfWeek = M0P_RTC->WEEK;
    time->u8Month     = M0P_RTC->MON;
    time->u8Year      = M0P_RTC->YEAR;

    M0P_RTC->CR1_f.WAIT = 0;
    if(1 == M0P_RTC->CR0_f.START)
    {
            while(M0P_RTC->CR1_f.WAITF)
            {}
    }
    
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  向RTC时间寄存器写入时间
 **
 ** \param time： 存放时间的结构体，各个时间均为BCD码格式
 **
 ** \retval ErrorTimeout 或 Ok
 ** 
 ******************************************************************************/
en_result_t Rtc_SetTime(stc_rtc_time_t* time)
{
    en_result_t enRet = Ok;
    uint16_t u16TimeOut;
    u16TimeOut = 1000;
    if(M0P_RTC->CR0_f.START == 1)
    {
        M0P_RTC->CR1_f.WAIT = 1;
        while(--u16TimeOut)
        {
            if(M0P_RTC->CR1_f.WAITF)
            {
                    break;
            }
        }
        if(u16TimeOut==0)
        {
            return ErrorTimeout;
        }
    }
    M0P_RTC->SEC   = time->u8Second;
    M0P_RTC->MIN   = time->u8Minute;
    M0P_RTC->HOUR  = time->u8Hour;
    M0P_RTC->DAY   = time->u8Day;
    M0P_RTC->MON   = time->u8Month;
    M0P_RTC->YEAR  = time->u8Year;
    M0P_RTC->WEEK  = time->u8DayOfWeek;

    M0P_RTC->CR1_f.WAIT = 0;
    if(M0P_RTC->CR0_f.START == 1)
    {
        while(M0P_RTC->CR1_f.WAITF)
        {}
    }
    enRet = Ok;
    return enRet;
}

/**
 ******************************************************************************
 ** \brief  RTC闹钟中断时间获取
 **
 ** \param pstcAlarmTime：存放闹钟时间寄存器数据：秒 分 时 周 
 **
 ** \retval 无
 ** 
 ******************************************************************************/
void Rtc_GetAlarmTime(stc_rtc_alarmtime_t* pstcAlarmTime)
{
    pstcAlarmTime->RtcAlarmSec    = M0P_RTC->ALMSEC;
    pstcAlarmTime->RtcAlarmMinute = M0P_RTC->ALMMIN;
    pstcAlarmTime->RtcAlarmHour     = M0P_RTC->ALMHOUR;
    pstcAlarmTime->RtcAlarmWeek     = M0P_RTC->ALMWEEK;
}

/**
 ******************************************************************************
 ** \brief  RTC闹钟设置
 **
 ** \param [in] pstcAlarmTime闹钟时间：秒 分 时 周
 **
 ** \retval Ok  设置正常
 ** 
 ******************************************************************************/
en_result_t Rtc_SetAlarmTime(stc_rtc_alarmtime_t* pstcAlarmTime)
{
    en_result_t enRet = Ok;
//    ASSERT(NULL != pstcAlarmTime);
    Rtc_AlmEnCmd(FALSE);      //闹钟禁止以后再设置闹钟时间
    enRet = Check_BCD_Format(pstcAlarmTime->RtcAlarmSec,0x00,0x59);
    if(M0P_RTC->CR0_f.AMPM == RtcAm)
    {
        enRet = Check_BCD_Format(pstcAlarmTime->RtcAlarmHour,0x00,0x12);
    }
    else
    {
        enRet = Check_BCD_Format(pstcAlarmTime->RtcAlarmHour,0x00,0x24);
    }
    if(enRet != Ok)
    {
        return enRet;
    }
    enRet = Check_BCD_Format(pstcAlarmTime->RtcAlarmMinute,0x00,0x59);
    if(enRet != Ok)
    {
        return enRet;
    }

    if(enRet != Ok)
    {
            return enRet; 
    }
    M0P_RTC->ALMSEC  = pstcAlarmTime->RtcAlarmSec & 0x7f;
    M0P_RTC->ALMMIN  = pstcAlarmTime->RtcAlarmMinute & 0x7f;
    M0P_RTC->ALMHOUR = pstcAlarmTime->RtcAlarmHour & 0x3f;
    M0P_RTC->ALMWEEK = pstcAlarmTime->RtcAlarmWeek;
    Rtc_AlmEnCmd(TRUE);      //闹钟许可
    enRet = Ok;
    return enRet;
}

/**
******************************************************************************
    ** \brief  初始化RTC
    ** 
    ** @param  Rtc_InitStruct 存放stc_rtc_initstruct_t类型的结构体
    ** \retval 无
    **
******************************************************************************/
void Rtc_Init(stc_rtc_initstruct_t* Rtc_InitStruct)
{
    Rtc_Cmd(FALSE);
    M0P_RTC->CR0_f.AMPM = Rtc_InitStruct->rtcAmpm;        //实时时钟小时的时制
    Rtc_SetCyc(&Rtc_InitStruct->rtcPrdsel);                //设置周期中断的类型(PRDSEL)及其所选类型的时间(PRDS或PRDX)
    M0P_RTC->CR1_f.CKSEL = Rtc_InitStruct->rtcClksrc;      //实时时钟RTC的时钟源
    Rtc_CompCfg(Rtc_InitStruct->rtcCompValue, Rtc_InitStruct->rtcCompen); //配置时钟误差补偿寄存器
    Rtc_SetTime(&Rtc_InitStruct->rtcTime);                 //设置初始时钟
}



