/********************************** (C) COPYRIGHT *******************************
* File Name          : CH57x_int.c
* Author             : WCH
* Version            : V1.0
* Date               : 2020/03/18
* Description
*******************************************************************************/

#include "CH57x_common.h"

/*******************************************************************************
* Function Name  : NMI_Handler
* Description    : NMI中断函数
* Input          : None
* Return         : None
*******************************************************************************/
//__attribute__((section("NMICode")))
void NMI_Handler( void )
{
    UINT32  i=0;

        if( (R8_HFCK_PWR_CTRL & RB_CLK_INT32M_PON) == 0 )
        {
            R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
                R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
                R8_HFCK_PWR_CTRL |= RB_CLK_INT32M_PON;                          // 打开内部32M
        }
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R16_CLK_SYS_CFG = 5;                                                                // 降频 HSI/5=6.4M
    R16_POWER_PLAN &= ~(RB_PWR_DCDC_EN|RB_PWR_DCDC_PRE);        // 旁路 DC/DC
        R8_HFCK_PWR_CTRL |= RB_CLK_PLL_PON;                                         // 打开PLL
        R8_SAFE_ACCESS_SIG = 0;

    while(1)
    {
        if(R8_BAT_STATUS & RB_BAT_STAT_LOWER)   i = 0;
        else i++;
        if( i>2000 )
                {
                    /* 执行系统复位 */
                    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
                    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
                    R8_RST_WDOG_CTRL = RB_SOFTWARE_RESET;
                    R8_SAFE_ACCESS_SIG = 0;
                }
    }
}

/*******************************************************************************
* Function Name  : LowPower_Halt_1
* Description    : 低功耗-Halt_1模式。
                   此低功耗切到HSI/5时钟运行，唤醒后需要用户自己重新选择系统时钟源
* Input          : None
* Return         : None
*******************************************************************************/
//__attribute__((section("NMICode")))
void LowPower_Halt_1( void )
{
    UINT8  x32Kpw, x32Mpw;

    x32Kpw = R8_XT32K_TUNE;
    x32Mpw = R8_XT32M_TUNE;
    x32Mpw = (x32Mpw&0xfc)|0x03;            // 150%额定电流
    if(R16_RTC_CNT_32K>0x3fff){     // 超过500ms
        x32Kpw = (x32Kpw&0xfc)|0x01;        // LSE驱动电流降低到额定电流
    }

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_SLP_POWER_CTRL &= ~RB_SLP_ROM_PWR_DN;          // flash待机
    R8_BAT_DET_CTRL = 0;                              // 关闭电压监控
    R8_XT32K_TUNE = x32Kpw;
    R8_XT32M_TUNE = x32Mpw;
    R16_CLK_SYS_CFG = 5;                // 降频 HSI/5=6.4M
    R8_SAFE_ACCESS_SIG = 0;

    SCB -> SCR |= SCB_SCR_SLEEPDEEP_Msk;                //deep sleep
    __WFI();
    R8_SAFE_ACCESS_SIG = 0;

    /* 开启电压监控 */
    PowerMonitor( ENABLE );
}

/*******************************************************************************
* Function Name  : LowPower_Halt_2
* Description    : 低功耗-Halt_2模式。
                   此低功耗切到HSI/5时钟运行，唤醒后需要用户自己重新选择系统时钟源
* Input          : None
* Return         : None
*******************************************************************************/
//__attribute__((section("NMICode")))
void LowPower_Halt_2( void )
{
    UINT8  x32Kpw, x32Mpw;

    x32Kpw = R8_XT32K_TUNE;
    x32Mpw = R8_XT32M_TUNE;
    x32Mpw = (x32Mpw&0xfc)|0x03;            // 150%额定电流
    if(R16_RTC_CNT_32K>0x3fff){     // 超过500ms
        x32Kpw = (x32Kpw&0xfc)|0x01;        // LSE驱动电流降低到额定电流
    }

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_SLP_POWER_CTRL |= RB_SLP_ROM_PWR_DN;           // flash停机
    R8_BAT_DET_CTRL = 0;                              // 关闭电压监控
    R8_XT32K_TUNE = x32Kpw;
    R8_XT32M_TUNE = x32Mpw;
    R16_CLK_SYS_CFG = 5;                // 降频 HSI/5=6.4M
    R8_SAFE_ACCESS_SIG = 0;

    SCB -> SCR |= SCB_SCR_SLEEPDEEP_Msk;                //deep sleep
    __WFI();
    R8_SAFE_ACCESS_SIG = 0;

    /* 开启电压监控 */
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R8_BAT_DET_CFG = 1;                     // 2.05V - 2.33V
        R8_BAT_DET_CTRL = RB_BAT_DET_EN;
        R8_SAFE_ACCESS_SIG = 0;
        __nop();    __nop();
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R8_BAT_DET_CTRL = RB_BAT_LOW_IE|RB_BAT_LOWER_IE|RB_BAT_DET_EN;
        R8_SAFE_ACCESS_SIG = 0;
}

/*******************************************************************************
* Function Name  : LowPower_Sleep
* Description    : 低功耗-Sleep模式。
                   此低功耗切到HSI/5时钟运行，唤醒后需要用户自己重新选择系统时钟源
                   注意调用此函数，DCDC功能强制关闭，唤醒后可以手动再次打开
* Input          : rm:
                    RB_PWR_RAM2K    -   最后2K SRAM 供电
                    RB_PWR_RAM14K   -   0x20004000 - 0x20007800 14K SRAM 供电
                    RB_PWR_EXTEND   -   USB和RF 单元保留区域供电
                   NULL -   以上单元都断电
* Return         : None
*******************************************************************************/
//__attribute__((section("NMICode")))
void LowPower_Sleep( UINT8 rm )
{
    UINT8  x32Kpw, x32Mpw;

    x32Kpw = R8_XT32K_TUNE;
    x32Mpw = R8_XT32M_TUNE;
    x32Mpw = (x32Mpw&0xfc)|0x03;            // 150%额定电流
    if(R16_RTC_CNT_32K>0x3fff){     // 超过500ms
        x32Kpw = (x32Kpw&0xfc)|0x01;        // LSE驱动电流降低到额定电流
    }

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R16_POWER_PLAN = RB_PWR_PLAN_EN         \
                    |RB_PWR_MUST_0010       \
                    |RB_PWR_CORE            \
                    |rm;
    R8_SAFE_ACCESS_SIG = 0;

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_BAT_DET_CTRL = 0;                // 关闭电压监控
    R8_XT32K_TUNE = x32Kpw;
    R8_XT32M_TUNE = x32Mpw;
    R16_CLK_SYS_CFG = 5;                // 降频 HSI/5=6.4M
    R8_SAFE_ACCESS_SIG = 0;

    SCB -> SCR |= SCB_SCR_SLEEPDEEP_Msk;                //deep sleep
    __WFI();
    R8_SAFE_ACCESS_SIG = 0;

    /* 开启电压监控 */
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R8_BAT_DET_CFG = 1;                     // 2.05V - 2.33V
        R8_BAT_DET_CTRL = RB_BAT_DET_EN;
        R8_SAFE_ACCESS_SIG = 0;
        __nop();    __nop();
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R8_BAT_DET_CTRL = RB_BAT_LOW_IE|RB_BAT_LOWER_IE|RB_BAT_DET_EN;
        R8_SAFE_ACCESS_SIG = 0;
}

/*******************************************************************************
* Function Name  : LowPower_Shutdown
* Description    : 低功耗-Shutdown模式。
                   此低功耗切到HSI/5时钟运行，唤醒后需要用户自己重新选择系统时钟源
                   注意调用此函数，DCDC功能强制关闭，唤醒后可以手动再次打开
* Input          : rm:
                    RB_PWR_RAM2K    -   最后2K SRAM 供电
                   NULL -   以上单元都断电
* Return         : None
*******************************************************************************/
//__attribute__((section("NMICode")))
void LowPower_Shutdown( UINT8 rm )
{
    UINT8  x32Kpw, x32Mpw;

    x32Kpw = R8_XT32K_TUNE;
    x32Mpw = R8_XT32M_TUNE;
    x32Mpw = (x32Mpw&0xfc)|0x03;            // 150%额定电流
    if(R16_RTC_CNT_32K>0x3fff){     // 超过500ms
        x32Kpw = (x32Kpw&0xfc)|0x01;        // LSE驱动电流降低到额定电流
    }

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R16_POWER_PLAN = RB_PWR_PLAN_EN         \
                    |RB_PWR_MUST_0010       \
                    |rm;
    R8_SAFE_ACCESS_SIG = 0;

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_BAT_DET_CTRL = 0;                // 关闭电压监控
    R8_XT32K_TUNE = x32Kpw;
    R8_XT32M_TUNE = x32Mpw;
    R16_CLK_SYS_CFG = 5;                // 降频 HSI/5=6.4M
    R8_SAFE_ACCESS_SIG = 0;

    SCB -> SCR |= SCB_SCR_SLEEPDEEP_Msk;                //deep sleep
    __WFI();
    R8_SAFE_ACCESS_SIG = 0;

    /* 开启电压监控 */
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R8_BAT_DET_CFG = 1;                     // 2.05V - 2.33V
        R8_BAT_DET_CTRL = RB_BAT_DET_EN;
        R8_SAFE_ACCESS_SIG = 0;
        __nop();    __nop();
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R8_BAT_DET_CTRL = RB_BAT_LOW_IE|RB_BAT_LOWER_IE|RB_BAT_DET_EN;
    R8_RST_WDOG_CTRL |= RB_SOFTWARE_RESET;
        R8_SAFE_ACCESS_SIG = 0;
}

