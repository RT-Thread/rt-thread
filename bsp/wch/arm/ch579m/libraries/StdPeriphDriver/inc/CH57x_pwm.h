


#ifndef __CH57x_PWM_H__
#define __CH57x_PWM_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "CH579SFR.h"
#include "core_cm0.h"

/**
  * @brief  channel of PWM define
  */

#define CH_PWM4     0x01                // PWM4 通道
#define CH_PWM5     0x02                // PWM5 通道
#define CH_PWM6     0x04                // PWM6 通道
#define CH_PWM7     0x08                // PWM7 通道
#define CH_PWM8     0x10                // PWM8 通道
#define CH_PWM9     0x20                // PWM9 通道
#define CH_PWM10    0x40                // PWM10 通道
#define CH_PWM11    0x80                // PWM11 通道



/**
  * @brief  channel of PWM define
  */
typedef enum
{
    High_Level = 0,                     // 默认低电平，高电平有效
    Low_Level,                          // 默认高电平，低电平有效
}PWMX_PolarTypeDef;


/**
  * @brief  Configuration PWM4_11 Cycle size
  */
typedef enum
{
    PWMX_Cycle_256 = 0,                 // 256 个PWMX周期
    PWMX_Cycle_255,                     // 255 个PWMX周期
    PWMX_Cycle_128,                     // 128 个PWMX周期
    PWMX_Cycle_127,                     // 127 个PWMX周期
    PWMX_Cycle_64,                      // 64 个PWMX周期
    PWMX_Cycle_63,                      // 63 个PWMX周期
    PWMX_Cycle_32,                      // 32 个PWMX周期
    PWMX_Cycle_31,                      // 31 个PWMX周期
}PWMX_CycleTypeDef;


#define PWMX_CLKCfg( d )            (R8_PWM_CLOCK_DIV=d)                /* PWM4-PWM11 通道基准时钟配置，= d*Tsys */
void PWMX_CycleCfg( PWMX_CycleTypeDef cyc );                            /* PWM4-PWM11 通道输出波形周期配置 */

#define PWM4_ActDataWidth( d )      (R8_PWM4_DATA = d)                  /* PWM4 有效数据脉宽 */
#define PWM5_ActDataWidth( d )      (R8_PWM5_DATA = d)                  /* PWM5 有效数据脉宽 */
#define PWM6_ActDataWidth( d )      (R8_PWM6_DATA = d)                  /* PWM6 有效数据脉宽 */
#define PWM7_ActDataWidth( d )      (R8_PWM7_DATA = d)                  /* PWM7 有效数据脉宽 */
#define PWM8_ActDataWidth( d )      (R8_PWM8_DATA = d)                  /* PWM8 有效数据脉宽 */
#define PWM9_ActDataWidth( d )      (R8_PWM9_DATA = d)                  /* PWM9 有效数据脉宽 */
#define PWM10_ActDataWidth( d )     (R8_PWM10_DATA = d)                 /* PWM10 有效数据脉宽 */
#define PWM11_ActDataWidth( d )     (R8_PWM11_DATA = d)                 /* PWM11 有效数据脉宽 */

// 占空比 = 数据有效脉宽/波形周期
void PWMX_ACTOUT( UINT8 ch, UINT8 da, PWMX_PolarTypeDef pr, UINT8 s);   /* PWM4-PWM11通道输出波形配置 */
void PWMX_AlterOutCfg( UINT8 ch, UINT8 s);          /* PWM 交替输出模式配置 */





#ifdef __cplusplus
}
#endif

#endif  // __CH57x_PWM_H__

