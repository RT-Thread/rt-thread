/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
 *文件名： lib_scu.h
 *作 者： Liut
 *版 本： V1.00
 *日 期： 2017/07/14
 *描 述： 内核模块库函数头文件
 *备 注： 适用于 ES8P508x芯片
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 ***************************************************************/
#ifndef __LIBSCU_H
#define __LIBSCU_H

#include "system_ES8P508x.h"
#include "ES8P508x.h"
#include "type.h"

/* NMI不可屏蔽中断选择 */
typedef enum
{
    SCU_PINT0_IRQn = 0,
    SCU_PINT1_IRQn = 1,
    SCU_PINT2_IRQn = 2,
    SCU_PINT3_IRQn = 3,
    SCU_PINT4_IRQn = 4,
    SCU_PINT5_IRQn = 5,
    SCU_PINT6_IRQn = 6,
    SCU_PINT7_IRQn = 7,
    SCU_T16N0_IRQn = 8,
    SCU_T16N1_IRQn = 9,
    SCU_T16N2_IRQn = 10,
    SCU_T16N3_IRQn = 11,
    SCU_T32N0_IRQn = 12,
    SCU_IWDT_IRQn = 14,
    SCU_WWDT_IRQn = 15,
    SCU_CCM_IRQn = 16,
    SCU_PLK_IRQn = 17,
    SCU_LVD_IRQn = 18,
    SCU_KINT_IRQn = 19,
    SCU_RTC_IRQn = 20,
    SCU_ADC_IRQn = 21,
    SCU_AES_IRQn = 23,
    SCU_UART0_IRQn = 24,
    SCU_UART1_IRQn = 25,
    SCU_UART2_IRQn = 26,
    SCU_UART3_IRQn = 27,
    SCU_UART4_IRQn = 28,
    SCU_UART5_IRQn = 29,
    SCU_SPI0_IRQn = 30,
    SCU_I2C0_IRQn = 31,
}SCU_TYPE_NMICS;

/* PWRC复位状态寄存器标志位 */
typedef enum
{
    SCU_PWRC_PORF= 0X00001,         //POR复位标志位
    SCU_PWRC_RRCF = 0X00002,        //PORC复位标志位
    SCU_PWRC_PORRSTF = 0x00004,     //POR总复位标志
    SCU_PWRC_BORF = 0x00008,        //BOR总复位标志
    SCU_PWRC_WWDTRSTF = 0x00010,    //WWDT复位标志
    SCU_PWRC_IWDTRSTF = 0x00020,    //IWDT复位标志
    SCU_PWRC_MRSTF = 0x00040,       //MRSTn复位标志
    SCU_PWRC_SOFTRSTF = 0x00080,    //软件复位标志
}SCU_TYPE_PWRC;

/* LVD寄存器标志位 */
typedef enum
{
    SCU_LVDFlag_IF = 0x0100,  //LVD中断标志
    SCU_LVDFlag_Out = 0x8000, //输出状态位
}SCU_TYPE_LVD0CON;

/* 时钟选择 */
typedef enum
{
    SCU_SysClk_HRC  = 0x0 ,  //内部20MHZ RC时钟
    SCU_SysClk_XTAL = 0x1 ,   //外部晶振主时钟
    SCU_SysClk_PLL  = 0x2 ,   //PLL
}SCU_TYPE_SYSCLK;

/*clk_sel时钟源选择*/
typedef enum
{
    CLK_SEL_HRC    = 0x0,   //HRC 20M
    CLK_SEL_LRC    = 0x1,   //LRC 32KHz
    CLK_SEL_XTAL   = 0x2,   //外接晶振XTAL
}SCU_TYPE_CLK_SEL;

/* PLL时钟源选择 */
typedef enum
{
    SCU_PLL_HRC   = 0x0 ,   //PLL时钟源HRC
    SCU_PLL_LRC  = 0x2 ,    //PLL时钟源LRC
    SCU_PLL_XTAL_32K  = 0x3 ,    //PLL时钟源XTAL
    SCU_PLL_XTAL_4M  = 0x4 ,    //PLL时钟源XTAL
    SCU_PLL_XTAL_8M  = 0x5,     //PLL时钟源XTAL
    SCU_PLL_XTAL_16M = 0x6,     //PLL时钟源XTAL
    SCU_PLL_XTAL_20M = 0x7,     //PLL时钟源XTAL
} SCU_PLL_Origin;

/* PLL时钟输出频率旋择 */
typedef enum
{
    SCU_PLL_32M   = 0x0 ,   //PLL时钟输出为32MHz
    SCU_PLL_48M   = 0x1 ,   //PLL时钟输出为48Mhz
} SCU_PLL_Out;

/************SCU模块宏定义***********/
/* SCU写保护控制 */
#define SCU_RegUnLock() (SCU->PROT.Word = 0x55AA6996)
#define SCU_RegLock()   (SCU->PROT.Word = 0x00000000)

/* NMI使能控制 */
#define SCU_NMI_Enable()  (SCU->NMICON.NMIEN = 0x1)
#define SCU_NMI_Disable() (SCU->NMICON.NMIEN = 0x0)

/*-------LVD模块-------*/

/* LVD使能控制 */
#define SCU_LVD_Enable()  (SCU->LVDCON.EN = 0x1)
#define SCU_LVD_Disable() (SCU->LVDCON.EN = 0x0)

/* LVD滤波使能控制 */
#define SCU_LVDFLT_Enable()  (SCU->LVDCON.FLTEN = 0x1)
#define SCU_LVDFLT_Disable() (SCU->LVDCON.FLTEN = 0x0)

/* LVD触发电压选择 */
#define SCU_LVDVS_2V0() (SCU->LVDCON.VS = 0x0)
#define SCU_LVDVS_2V1() (SCU->LVDCON.VS = 0x1)
#define SCU_LVDVS_2V2() (SCU->LVDCON.VS = 0x2)
#define SCU_LVDVS_2V4() (SCU->LVDCON.VS = 0x3)
#define SCU_LVDVS_2V6() (SCU->LVDCON.VS = 0x4)
#define SCU_LVDVS_2V8() (SCU->LVDCON.VS = 0x5)
#define SCU_LVDVS_3V0() (SCU->LVDCON.VS = 0x6)
#define SCU_LVDVS_3V6() (SCU->LVDCON.VS = 0x7)
#define SCU_LVDVS_4V()  (SCU->LVDCON.VS = 0x8)
#define SCU_LVDVS_4V6() (SCU->LVDCON.VS = 0x9)
#define SCU_LVDVS_2V3() (SCU->LVDCON.VS = 0xA)
#define SCU_LVDVS_LVDIN() (SCU->LVDCON.VS = 0xE)

/* LVD中断使能控制 */
#define SCU_LVDIT_Enable()  (SCU->LVDCON.IE = 0x1)
#define SCU_LVDIT_Disable() (SCU->LVDCON.IE = 0x0)

/* LVD中断标志位清除 */
#define SCU_LVDClearIFBit() (SCU->LVDCON.IF = 1)

/* LVD中断产生模式选择 */
#define SCU_LVDIFS_Rise() (SCU->LVDCON.IFS = 0x0) //LVDO上升沿产生中断
#define SCU_LVDIFS_Fall() (SCU->LVDCON.IFS = 0x1) //LVDO下降沿产生中断
#define SCU_LVDIFS_High() (SCU->LVDCON.IFS = 0x2) //LVDO高电平产生中断
#define SCU_LVDIFS_Low()  (SCU->LVDCON.IFS = 0x3)   //LVDO低电平产生中断 
#define SCU_LVDIFS_Change() (SCU->LVDCON.IFS = 0x4) //LVDO电平变化产生中断

/* FLASH访问等待时间选择 */
#define SCU_FlashWait_1Tclk()  (SCU->FLASHWAIT.ACCT = 0x0)
#define SCU_FlashWait_2Tclk()  (SCU->FLASHWAIT.ACCT = 0x1)
#define SCU_FlashWait_3Tclk()  (SCU->FLASHWAIT.ACCT = 0x2)
#define SCU_FlashWait_4Tclk()  (SCU->FLASHWAIT.ACCT = 0x3)
#define SCU_FlashWait_5Tclk()  (SCU->FLASHWAIT.ACCT = 0x4)
#define SCU_FlashWait_6Tclk()  (SCU->FLASHWAIT.ACCT = 0x5)
#define SCU_FlashWait_7Tclk()  (SCU->FLASHWAIT.ACCT = 0x6)
#define SCU_FlashWait_8Tclk()  (SCU->FLASHWAIT.ACCT = 0x7)
#define SCU_FlashWait_9Tclk()  (SCU->FLASHWAIT.ACCT = 0x8)
#define SCU_FlashWait_10Tclk() (SCU->FLASHWAIT.ACCT = 0x9)
#define SCU_FlashWait_11Tclk() (SCU->FLASHWAIT.ACCT = 0xA)
#define SCU_FlashWait_12Tclk() (SCU->FLASHWAIT.ACCT = 0xB)
#define SCU_FlashWait_13Tclk() (SCU->FLASHWAIT.ACCT = 0xC)
#define SCU_FlashWait_14Tclk() (SCU->FLASHWAIT.ACCT = 0xD)
#define SCU_FlashWait_15Tclk() (SCU->FLASHWAIT.ACCT = 0xE)
#define SCU_FlashWait_16Tclk() (SCU->FLASHWAIT.ACCT = 0xF)

/* 系统时钟后分频选择 */
#define SCU_SysClk_Div1()   (SCU->SCLKEN0.SYSCLK_DIV = 0)
#define SCU_SysClk_Div2()   (SCU->SCLKEN0.SYSCLK_DIV = 1)
#define SCU_SysClk_Div4()   (SCU->SCLKEN0.SYSCLK_DIV = 2)
#define SCU_SysClk_Div8()  (SCU->SCLKEN0.SYSCLK_DIV = 3)
#define SCU_SysClk_Div16()  (SCU->SCLKEN0.SYSCLK_DIV = 4)
#define SCU_SysClk_Div32()  (SCU->SCLKEN0.SYSCLK_DIV = 5)
#define SCU_SysClk_Div64()  (SCU->SCLKEN0.SYSCLK_DIV = 6)
#define SCU_SysClk_Div128() (SCU->SCLKEN0.SYSCLK_DIV = 7)

/* HRC使能控制 (内部20Mhz) */
#define SCU_HRC_Enable()  (SCU->SCLKEN1.HRC_EN = 1)
#define SCU_HRC_Disable() (SCU->SCLKEN1.HRC_EN = 0)

/* XTAL使能控制 */
#define SCU_XTAL_Enable()  (SCU->SCLKEN1.XTAL_EN = 1)
#define SCU_XTAL_Disable() (SCU->SCLKEN1.XTAL_EN = 0)

/* PLL模式使能控制 */
#define SCU_PLL_Enable()  (SCU->SCLKEN1.PLL_EN = 1)
#define SCU_PLL_Disable() (SCU->SCLKEN1.PLL_EN = 0)

/*-------外设时钟控制-------*/
/* SCU时钟使能控制 */
#define SCU_SCUCLK_Enable()  (SCU->PCLKEN0.SCU_EN = 1)
#define SCU_SCUCLK_Disable() (SCU->PCLKEN0.SCU_EN = 0)

/* GPIO时钟使能控制 */
#define SCU_GPIOCLK_Enable()  (SCU->PCLKEN0.GPIO_EN = 1)
#define SCU_GPIOCLK_Disable() (SCU->PCLKEN0.GPIO_EN = 0)

/* FLASH IAP时钟使能控制 */
#define SCU_IAPCLK_Enable()  (SCU->PCLKEN0.IAP_EN = 1)
#define SCU_IAPCLK_Disable() (SCU->PCLKEN0.IAP_EN = 0)

/* CRC时钟使能控制 */
#define SCU_CRCCLK_Enable()  (SCU->PCLKEN0.CRC_EN = 1)
#define SCU_CRCCLK_Disable() (SCU->PCLKEN0.CRC_EN = 0)

/* ADC时钟使能控制 */
#define SCU_ADCCLK_Enable()  (SCU->PCLKEN0.ADC_EN = 1)
#define SCU_ADCCLK_Disable() (SCU->PCLKEN0.ADC_EN = 0)

/* RTC时钟使能控制 */
#define SCU_RTCCLK_Enable()  (SCU->PCLKEN0.RTC_EN = 1)
#define SCU_RTCCLK_Disable() (SCU->PCLKEN0.RTC_EN = 0)

/* IWDT时钟使能控制 */
#define SCU_IWDTCLK_Enable()  (SCU->PCLKEN0.IWDT_EN = 1)
#define SCU_IWDTCLK_Disable() (SCU->PCLKEN0.IWDT_EN = 0)

/* WWDT时钟使能控制 */
#define SCU_WWDTCLK_Enable()  (SCU->PCLKEN0.WWDT_EN = 1)
#define SCU_WWDTCLK_Disable() (SCU->PCLKEN0.WWDT_EN = 0)

/* AES时钟使能控制 */
#define SCU_AESCLK_Enable()  (SCU->PCLKEN0.AES_EN = 1)
#define SCU_AESCLK_Disable() (SCU->PCLKEN0.AES_EN = 0)

/* T16N0时钟使能控制 */
#define SCU_T16N0CLK_Enable()  (SCU->PCLKEN1.T16N0_EN = 1)
#define SCU_T16N0CLK_Disable() (SCU->PCLKEN1.T16N0_EN = 0)

/* T16N1时钟使能控制 */
#define SCU_T16N1CLK_Enable()  (SCU->PCLKEN1.T16N1_EN = 1)
#define SCU_T16N1CLK_Disable() (SCU->PCLKEN1.T16N1_EN = 0)

/* T16N2时钟使能控制 */
#define SCU_T16N2CLK_Enable()  (SCU->PCLKEN1.T16N2_EN = 1)
#define SCU_T16N2CLK_Disable() (SCU->PCLKEN1.T16N2_EN = 0)

/* T16N3时钟使能控制 */
#define SCU_T16N3CLK_Enable()  (SCU->PCLKEN1.T16N3_EN = 1)
#define SCU_T16N3CLK_Disable() (SCU->PCLKEN1.T16N3_EN = 0)

/* T32N0时钟使能控制 */
#define SCU_T32N0CLK_Enable()  (SCU->PCLKEN1.T32N0_EN = 1)
#define SCU_T32N0CLK_Disable() (SCU->PCLKEN1.T32N0_EN = 0)

/* UART0时钟使能控制 */
#define SCU_UART0CLK_Enable()  (SCU->PCLKEN1.UART0_EN = 1)
#define SCU_UART0CLK_Disable() (SCU->PCLKEN1.UART0_EN = 0)

/* UART1时钟使能控制 */
#define SCU_UART1CLK_Enable()  (SCU->PCLKEN1.UART1_EN = 1)
#define SCU_UART1CLK_Disable() (SCU->PCLKEN1.UART1_EN = 0)

/* UART2时钟使能控制 */
#define SCU_UART2CLK_Enable()  (SCU->PCLKEN1.UART2_EN = 1)
#define SCU_UART2CLK_Disable() (SCU->PCLKEN1.UART2_EN = 0)

/* UART3时钟使能控制 */
#define SCU_UART3CLK_Enable()  (SCU->PCLKEN1.UART3_EN = 1)
#define SCU_UART3CLK_Disable() (SCU->PCLKEN1.UART3_EN = 0)

/* UART4时钟使能控制 */
#define SCU_UART4CLK_Enable()  (SCU->PCLKEN1.UART4_EN = 1)
#define SCU_UART4CLK_Disable() (SCU->PCLKEN1.UART4_EN = 0)

/* UART5时钟使能控制 */
#define SCU_UART5CLK_Enable()  (SCU->PCLKEN1.UART5_EN = 1)
#define SCU_UART5CLK_Disable() (SCU->PCLKEN1.UART5_EN = 0)

/* SPI0时钟使能控制 */
#define SCU_SPI0CLK_Enable()  (SCU->PCLKEN1.SPI0_EN = 1)
#define SCU_SPI0CLK_Disable() (SCU->PCLKEN1.SPI0_EN = 0)

/* IIC0时钟使能控制 */
#define SCU_IIC0CLK_Enable()  (SCU->PCLKEN1.I2C0_EN = 1)
#define SCU_IIC0CLK_Disable() (SCU->PCLKEN1.I2C0_EN = 0)

/* 中断向量表重映射使能控制 */
#define SCU_TBLRemap_Enable()  (SCU->TBLREMAPEN.EN= 1)
#define SCU_TBLRemap_Disable() (SCU->TBLREMAPEN.EN= 0)

/* 中断向量表偏移寄存器 x最大为2^24=16777216 */
#define SCU_TBL_Offset(x) (SCU->TBLOFF.TBLOFF = (uint32_t)x)

/************SCU模块函数声明***********/
void SCU_OpenXTAL(void);
void SCU_NMISelect(SCU_TYPE_NMICS NMI_Type);
FlagStatus SCU_GetPWRCFlagStatus(SCU_TYPE_PWRC PWRC_Flag);
void SCU_ClearPWRCFlagBit(SCU_TYPE_PWRC PWRC_Flag);
FlagStatus SCU_GetLVDFlagStatus(SCU_TYPE_LVD0CON LVD_Flag);
void SCU_SysClkSelect(SCU_TYPE_SYSCLK Sysclk);
SCU_TYPE_SYSCLK SCU_GetSysClk(void);
FlagStatus SCU_HRCReadyFlag(void);
FlagStatus  SCU_XTALReadyFlag(void);
FlagStatus  SCU_PLLReadyFlag(void);
void SystemClockConfig(void);
void SystemClockConfig_1(void);
void DeviceClockAllEnable(void);
void DeviceClockAllDisable(void);
void SystemClockSelect(SCU_TYPE_SYSCLK SYSCLKx , SCU_TYPE_CLK_SEL CLK_SEL);
void PLLClock_Config(TYPE_FUNCEN pll_en , SCU_PLL_Origin  pll_origin ,SCU_PLL_Out pll_out,TYPE_FUNCEN sys_pll);
#endif
/*************************END OF FILE**********************/





