


#ifndef __CH57x_CLK_H__
#define __CH57x_CLK_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "CH579SFR.h"
#include "core_cm0.h"

typedef enum
{
    CLK_SOURCE_LSI = 0,
    CLK_SOURCE_LSE,
    CLK_SOURCE_HSE_32MHz,
    CLK_SOURCE_HSE_16MHz,
    CLK_SOURCE_HSE_8MHz,
    CLK_SOURCE_HSI_32MHz,               //上电默认情况
    CLK_SOURCE_HSI_16MHz,
    CLK_SOURCE_HSI_8MHz,
    CLK_SOURCE_PLL_40MHz,
    CLK_SOURCE_PLL_32MHz,
    CLK_SOURCE_PLL_24MHz,
    CLK_SOURCE_PLL_20MHz,
    CLK_SOURCE_PLL_16MHz,

}SYS_CLKTypeDef;


typedef enum
{
    Clk32M_HSI = 0,
    Clk32M_HSE,

}HClk32MTypeDef;

typedef enum
{
    Clk32K_LSI = 0,
    Clk32K_LSE,

}LClk32KTypeDef;

typedef enum
{
    HSE_RCur_75 = 0,
    HSE_RCur_100,
    HSE_RCur_125,
    HSE_RCur_150

}HSECurrentTypeDef;

typedef enum
{
    HSECap_10p = 0,
    HSECap_12p,  HSECap_14p,  HSECap_16p,  HSECap_18p,
    HSECap_20p,  HSECap_22p,  HSECap_24p

}HSECapTypeDef;

typedef enum
{
    LSE_RCur_70 = 0,
    LSE_RCur_100,
    LSE_RCur_140,
    LSE_RCur_200

}LSECurrentTypeDef;

typedef enum
{
    LSECap_2p = 0,
    LSECap_13p,  LSECap_14p,  LSECap_15p,  LSECap_16p,
    LSECap_17p,  LSECap_18p,  LSECap_19p,  LSECap_20p,
    LSECap_21p,  LSECap_22p,  LSECap_23p,  LSECap_24p,
    LSECap_25p,  LSECap_26p,  LSECap_27p

}LSECapTypeDef;

#define  MAX_DAY        0x00004000
#define  MAX_2_SEC      0x0000A8C0
//#define    MAX_SEC        0x545FFFFF

#define BEGYEAR                                                 2020
#define IsLeapYear(yr)                                  (!((yr) % 400) || (((yr) % 100) && !((yr) % 4)))
#define YearLength(yr)                                  (IsLeapYear(yr) ? 366 : 365)
#define monthLength(lpyr,mon)                       ((mon==1) ? (28+lpyr) : ((mon>6) ? ((mon&1)?31:30) : ((mon&1)?30:31)))

/**
  * @brief  rtc timer mode period define
  */
typedef enum
{
    Period_0_125_S = 0,         // 0.125s 周期
    Period_0_25_S,              // 0.25s 周期
    Period_0_5_S,               // 0.5s 周期
    Period_1_S,                 // 1s 周期
    Period_2_S,                 // 2s 周期
    Period_4_S,                 // 4s 周期
    Period_8_S,                 // 8s 周期
    Period_16_S,                // 16s 周期
}RTC_TMRCycTypeDef;


/**
  * @brief  rtc interrupt event define
  */
typedef enum
{
    RTC_TRIG_EVENT = 0,         // RTC 触发事件
    RTC_TMR_EVENT,              // RTC 周期定时事件

}RTC_EVENTTypeDef;

/**
  * @brief  rtc interrupt event define
  */
typedef enum
{
    RTC_TRIG_MODE = 0,          // RTC 触发模式
    RTC_TMR_MODE,               // RTC 周期定时模式

}RTC_MODETypeDef;


void SystemInit(void);                          /* 系统时钟初始化 */
void SetSysClock( SYS_CLKTypeDef sc);           /* 重设系统运行时钟 */
UINT32 GetSysClock( void );                     /* 获取当前系统时钟 */
void HClk32M_Select( HClk32MTypeDef hc);        /* 32M 高频时钟来源 */
void LClk32K_Select( LClk32KTypeDef hc);        /* 32K 低频时钟来源 */

void HSECFG_Current( HSECurrentTypeDef c );     /* HSE晶体 偏置电流配置 */
void HSECFG_Capacitance( HSECapTypeDef c );     /* HSE晶体 负载电容配置 */
void LSECFG_Current( LSECurrentTypeDef c );     /* LSE晶体 偏置电流配置 */
void LSECFG_Capacitance( LSECapTypeDef c );     /* LSE晶体 负载电容配置 */

UINT16 Calibration_LSI( void );             /* 外部32M时钟校准内部32K时钟 */


void RTC_InitTime( UINT16 y, UINT16 mon, UINT16 d, UINT16 h, UINT16 m, UINT16 s );          /* RTC时钟初始化当前时间 */
void RTC_GetTime( PUINT16 py, PUINT16 pmon, PUINT16 pd, PUINT16 ph, PUINT16 pm, PUINT16 ps );       /* 获取当前时间 */

void RTC_SetCycle32k( UINT32 cyc );                         /* 基于LSE/LSI时钟，配置当前RTC 周期数 */
UINT32 RTC_GetCycle32k( void );                             /* 基于LSE/LSI时钟，获取当前RTC 周期数 */

void RTC_TRIGFunCfg( UINT32 cyc );                          /* RTC触发模式配置间隔时间,基于LSE/LSI时钟，匹配周期数 */
void RTC_TMRFunCfg( RTC_TMRCycTypeDef t );                  /* RTC定时模式配置 */
void RTC_ModeFunDisable( RTC_MODETypeDef m );               /* RTC 模式功能关闭 */

UINT8 RTC_GetITFlag( RTC_EVENTTypeDef f );                  /* 获取RTC中断标志 */
void RTC_ClearITFlag( RTC_EVENTTypeDef f );                 /* 清除RTC中断标志 */




#ifdef __cplusplus
}
#endif

#endif  // __CH57x_CLK_H__

