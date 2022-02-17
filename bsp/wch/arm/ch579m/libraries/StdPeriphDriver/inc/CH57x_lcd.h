


#ifndef __CH57x_LCD_H__
#define __CH57x_LCD_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "CH579SFR.h"
#include "core_cm0.h"

/**
  * @brief  Configuration LCD driver power
  */
typedef enum
{
    LCD_PS_3V3 = 0,                 // 3.3V 驱动
    LCD_PS_2V5,                     // 2.5V 驱动
}LCDDrvPowerTypeDef;


/**
  * @brief  Configuration LCD bias
  */
typedef enum
{
    LCD_1_2_Bias = 0,               // 2级分压
    LCD_1_3_Bias,                   // 3级分压
}LCDBiasTypeDef;

/**
  * @brief  Configuration LCD duty
  */
typedef enum
{
    LCD_1_2_Duty = 0,               // COM0-COM1
    LCD_1_3_Duty,                   // COM0-COM2
    LCD_1_4_Duty,                   // COM0-COM3
}LCDDutyTypeDef;

/**
  * @brief  Configuration LCD scan clk
  */
typedef enum
{
    LCD_CLK_256 = 0,                // 256Hz
    LCD_CLK_512,                    // 512Hz
    LCD_CLK_1000,                   // 1KHz
    LCD_CLK_128                     // 128Hz
}LCDSCANCLKTypeDef;


void LCD_DefInit( void );               /* LCD段式屏驱动默认初始化配置 */

#define LCD_PowerDown()         (R8_LCD_CTRL_MOD &= ~(RB_LCD_POWER_ON|RB_SYS_POWER_ON))     /* LCD功能模块关闭 */
#define LCD_PowerOn()           (R8_LCD_CTRL_MOD |= (RB_LCD_POWER_ON|RB_SYS_POWER_ON))      /* LCD功能模块开启 */

// 输入值参考 LCDDrvPowerTypeDef
#define LCD_PowerCfg( d )       (R8_LCD_CTRL_MOD=R8_LCD_CTRL_MOD&0x7F|(d<<7))               /* 配置LCD的 供电电压选择 */
// 输入值参考 LCDSCANCLKTypeDef
#define LCD_ScanCLKCfg( d )     (R8_LCD_CTRL_MOD=R8_LCD_CTRL_MOD&0x9F|(d<<5))               /* 配置LCD的 扫描时钟选择 */
// 输入值参考 LCDDutyTypeDef
#define LCD_DutyCfg( d )        (R8_LCD_CTRL_MOD=R8_LCD_CTRL_MOD&0xE7|(d<<3))               /* 配置LCD的 duty选择 */
// 输入值参考 LCDBiasTypeDef
#define LCD_BiasCfg( d )        (R8_LCD_CTRL_MOD=R8_LCD_CTRL_MOD&0xFB|(d<<2))               /* 配置LCD的 bias选择 */

#define LCD_WriteData0( d )     (R32_LCD_RAM0=R32_LCD_RAM0&0xffffff00|((UINT32)d))          /* 填充SEG0驱动数值 */
#define LCD_WriteData1( d )     (R32_LCD_RAM0=R32_LCD_RAM0&0xffff00ff|((UINT32)d<<8))       /* 填充SEG1驱动数值 */
#define LCD_WriteData2( d )     (R32_LCD_RAM0=R32_LCD_RAM0&0xff00ffff|((UINT32)d<<16))      /* 填充SEG2驱动数值 */
#define LCD_WriteData3( d )     (R32_LCD_RAM0=R32_LCD_RAM0&0x00ffffff|((UINT32)d<<24))      /* 填充SEG3驱动数值 */

#define LCD_WriteData4( d )     (R32_LCD_RAM1=R32_LCD_RAM1&0xffffff00|((UINT32)d))          /* 填充SEG4驱动数值 */
#define LCD_WriteData5( d )     (R32_LCD_RAM1=R32_LCD_RAM1&0xffff00ff|((UINT32)d<<8))       /* 填充SEG5驱动数值 */
#define LCD_WriteData6( d )     (R32_LCD_RAM1=R32_LCD_RAM1&0xff00ffff|((UINT32)d<<16))      /* 填充SEG6驱动数值 */
#define LCD_WriteData7( d )     (R32_LCD_RAM1=R32_LCD_RAM1&0x00ffffff|((UINT32)d<<24))      /* 填充SEG7驱动数值 */

#define LCD_WriteData8( d )     (R32_LCD_RAM2=R32_LCD_RAM2&0xffffff00|((UINT32)d))          /* 填充SEG8驱动数值 */
#define LCD_WriteData9( d )     (R32_LCD_RAM2=R32_LCD_RAM2&0xffff00ff|((UINT32)d<<8))       /* 填充SEG9驱动数值 */
#define LCD_WriteData10( d )        (R32_LCD_RAM2=R32_LCD_RAM2&0xff00ffff|((UINT32)d<<16))      /* 填充SEG10驱动数值 */
#define LCD_WriteData11( d )        (R32_LCD_RAM2=R32_LCD_RAM2&0x00ffffff|((UINT32)d<<24))      /* 填充SEG11驱动数值 */



#ifdef __cplusplus
}
#endif

#endif  // __CH57x_LCD_H__

