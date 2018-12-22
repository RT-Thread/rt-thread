/**************************************************************************//**
 * @file     clk.h
 * @version  V3.0
 * $Revision: 17 $
 * $Date: 14/01/28 1:11p $
 * @brief    M051 Series Clock Control Driver Header File
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef __CLK_H__
#define __CLK_H__


#include "M051Series.h"


/** @addtogroup M051_Device_Driver M051 Device Driver
  @{
*/

/** @addtogroup M051_CLK_Driver CLK Driver
  @{
*/

/** @addtogroup M051_CLK_EXPORTED_FUNCTIONS CLK Exported Constants
  @{
*/

#define FREQ_25MHZ         25000000
#define FREQ_50MHZ         50000000
#define FREQ_100MHZ       100000000
#define FREQ_200MHZ       200000000

/*---------------------------------------------------------------------------------------------------------*/
/*  PWRCON constant definitions.                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_PWRCON_HXT_EN       (0x01UL<<CLK_PWRCON_XTL12M_EN_Pos) /*!< Enable 4~24 MHz External High Speed Crystal (HXT) */
#define CLK_PWRCON_HIRC_EN      (0x01UL<<CLK_PWRCON_OSC22M_EN_Pos) /*!< Enable 22.1184 MHz Internal High Speed RC Oscillator (HIRC) */
#define CLK_PWRCON_LIRC_EN      (0x01UL<<CLK_PWRCON_OSC10K_EN_Pos) /*!< Enable 10 kHz Internal Low Speed RC Oscillator (LIRC) */


/*---------------------------------------------------------------------------------------------------------*/
/*  CLKSEL0 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKSEL0_HCLK_S_HXT          0x00UL /*!< Setting HCLK clock source as HXT */
#define CLK_CLKSEL0_HCLK_S_PLL          0x02UL /*!< Setting HCLK clock source as PLL */
#define CLK_CLKSEL0_HCLK_S_LIRC         0x03UL /*!< Setting HCLK clock source as LIRC */
#define CLK_CLKSEL0_HCLK_S_HIRC         0x07UL /*!< Setting HCLKclock source as HIRC */
#define CLK_CLKSEL0_STCLK_S_HXT         0x00UL /*!< Setting SysTick clock source as HXT */
#define CLK_CLKSEL0_STCLK_S_HXT_DIV2    0x10UL /*!< Setting SysTick clock source as HXT/2 */
#define CLK_CLKSEL0_STCLK_S_HCLK_DIV2   0x18UL /*!< Setting SysTick clock source as HCLK/2 */
#define CLK_CLKSEL0_STCLK_S_HIRC_DIV2   0x38UL /*!< Setting SysTick clock source as internal HIRC/2 */


/*---------------------------------------------------------------------------------------------------------*/
/*  CLKSEL1 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKSEL1_WDT_S_HCLK_DIV2048  0x00000002UL /*!< Setting WDT clock source as HCLK/2048 */
#define CLK_CLKSEL1_WDT_S_LIRC          0x00000003UL /*!< Setting WDT clock source as LIRC */
#define CLK_CLKSEL1_ADC_S_HXT           0x00000000UL /*!< Setting ADC clock source as HXT */
#define CLK_CLKSEL1_ADC_S_PLL           0x00000004UL /*!< Setting ADC clock source as PLL */
#define CLK_CLKSEL1_ADC_S_HCLK          0x00000008UL /*!< Setting ADC clock source as HCLK */
#define CLK_CLKSEL1_ADC_S_HIRC          0x0000000CUL /*!< Setting ADC clock source as HIRC */
#define CLK_CLKSEL1_SPI0_S_PLL          0x00000000UL /*!< Setting SPI0 clock source as PLL */
#define CLK_CLKSEL1_SPI0_S_HCLK         0x00000010UL /*!< Setting SPI0 clock source as HCLK */
#define CLK_CLKSEL1_SPI1_S_PLL          0x00000000UL /*!< Setting SPI1 clock source as PLL */
#define CLK_CLKSEL1_SPI1_S_HCLK         0x00000020UL /*!< Setting SPI1 clock source as HCLK */
#define CLK_CLKSEL1_TMR0_S_HXT          0x00000000UL /*!< Setting Timer 0 clock source as HXT */
#define CLK_CLKSEL1_TMR0_S_HCLK         0x00000200UL /*!< Setting Timer 0 clock source as HCLK */
#define CLK_CLKSEL1_TMR0_S_T0           0x00000300UL /*!< Setting Timer 0 clock source as T0 */
#define CLK_CLKSEL1_TMR0_S_LIRC         0x00000500UL /*!< Setting Timer 0 clock source as LIRC */
#define CLK_CLKSEL1_TMR0_S_HIRC         0x00000700UL /*!< Setting Timer 0 clock source as HIRC */
#define CLK_CLKSEL1_TMR1_S_HXT          0x00000000UL /*!< Setting Timer 1 clock source as HXT */
#define CLK_CLKSEL1_TMR1_S_HCLK         0x00002000UL /*!< Setting Timer 1 clock source as HCLK */
#define CLK_CLKSEL1_TMR1_S_T1           0x00003000UL /*!< Setting Timer 1 clock source as T1 */
#define CLK_CLKSEL1_TMR1_S_LIRC         0x00005000UL /*!< Setting Timer 1 clock source as LIRC */
#define CLK_CLKSEL1_TMR1_S_HIRC         0x00007000UL /*!< Setting Timer 1 clock source as HIRC */
#define CLK_CLKSEL1_TMR2_S_HXT          0x00000000UL /*!< Setting Timer 2 clock source as HXT */
#define CLK_CLKSEL1_TMR2_S_S_HCLK       0x00020000UL /*!< Setting Timer 2 clock source as HCLK */
#define CLK_CLKSEL1_TMR2_S_T2           0x00030000UL /*!< Setting Timer 2 clock source as T2 */
#define CLK_CLKSEL1_TMR2_S_LIRC         0x00050000UL /*!< Setting Timer 2 clock source as LIRC */
#define CLK_CLKSEL1_TMR2_S_HIRC         0x00070000UL /*!< Setting Timer 2 clock source as HIRC */
#define CLK_CLKSEL1_TMR3_S_HXT          0x00000000UL /*!< Setting Timer 3 clock source as HXT */
#define CLK_CLKSEL1_TMR3_S_HCLK         0x00200000UL /*!< Setting Timer 3 clock source as HCLK */
#define CLK_CLKSEL1_TMR3_S_S_T3         0x00300000UL /*!< Setting Timer 3 clock source as T3 */
#define CLK_CLKSEL1_TMR3_S_LIRC         0x00500000UL /*!< Setting Timer 3 clock source as LIRC */
#define CLK_CLKSEL1_TMR3_S_HIRC         0x00700000UL /*!< Setting Timer 3 clock source as HIRC */
#define CLK_CLKSEL1_UART_S_HXT          0x00000000UL /*!< Setting UART clock source as HXT */
#define CLK_CLKSEL1_UART_S_PLL          0x01000000UL /*!< Setting UART clock source as PLL */
#define CLK_CLKSEL1_UART_S_HIRC         0x03000000UL /*!< Setting UART clock source as HIRC */
#define CLK_CLKSEL1_PWM01_S_HXT         0x00000000UL /*!< Setting PWM01 clock source as HXT */
#define CLK_CLKSEL1_PWM01_S_LIRC        0x10000000UL /*!< Setting PWM01 clock source as LIRC */
#define CLK_CLKSEL1_PWM01_S_HCLK        0x20000000UL /*!< Setting PWM01 clock source as HCLK */
#define CLK_CLKSEL1_PWM01_S_HIRC        0x30000000UL /*!< Setting PWM01 clock source as HIRC */
#define CLK_CLKSEL1_PWM23_S_HXT         0x00000000UL /*!< Setting PWM23 clock source as HXT */
#define CLK_CLKSEL1_PWM23_S_LIRC        0x40000000UL /*!< Setting PWM23 clock source as LIRC */
#define CLK_CLKSEL1_PWM23_S_HCLK        0x80000000UL /*!< Setting PWM23 clock source as HCLK */
#define CLK_CLKSEL1_PWM23_S_HIRC        0xC0000000UL /*!< Setting PWM23 clock source as HIRC */


/*---------------------------------------------------------------------------------------------------------*/
/*  CLKSEL2 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKSEL2_FRQDIV_S_HXT        0x00000000UL /*!< Setting FRQDIV clock source as HXT */
#define CLK_CLKSEL2_FRQDIV_S_LIRC       0x00000004UL /*!< Setting FRQDIV clock source as LIRC */
#define CLK_CLKSEL2_FRQDIV_S_HCLK       0x00000008UL /*!< Setting FRQDIV clock source as HCLK */
#define CLK_CLKSEL2_FRQDIV_S_HIRC       0x0000000CUL /*!< Setting FRQDIV clock source as HIRC */
#define CLK_CLKSEL2_PWM45_S_HXT         0x00000000UL /*!< Setting PWM45 clock source as HXT */
#define CLK_CLKSEL2_PWM45_S_LIRC        0x00000010UL /*!< Setting PWM45 clock source as LIRC */
#define CLK_CLKSEL2_PWM45_S_HCLK        0x00000020UL /*!< Setting PWM45 clock source as HCLK */
#define CLK_CLKSEL2_PWM45_S_HIRC        0x00000030UL /*!< Setting PWM45 clock source as HIRC */
#define CLK_CLKSEL2_PWM67_S_HXT         0x00000000UL /*!< Setting PWM67 clock source as HXT */
#define CLK_CLKSEL2_PWM67_S_LIRC        0x00000040UL /*!< Setting PWM67 clock source as LIRC */
#define CLK_CLKSEL2_PWM67_S_HCLK        0x00000080UL /*!< Setting PWM67 clock source as HCLK */
#define CLK_CLKSEL2_PWM67_S_HIRC        0x000000C0UL /*!< Setting PWM67 clock source as HIRC */
#define CLK_CLKSEL2_WWDT_S_HCLK_DIV2048 0x00020000UL /*!< Setting WWDT clock source as HCLK/2048 */
#define CLK_CLKSEL2_WWDT_S_LIRC         0x00030000UL /*!< Setting WWDT clock source as LIRC */


/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV constant definitions.                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV_ADC(x)  (((x)-1) << 16) /*!< CLKDIV Setting for ADC clock divider. It could be 1~256 */
#define CLK_CLKDIV_UART(x) (((x)-1) <<  8) /*!< CLKDIV Setting for UART clock divider. It could be 1~16 */
#define CLK_CLKDIV_HCLK(x)  ((x)-1)        /*!< CLKDIV Setting for HCLK clock divider. It could be 1~16 */


/*---------------------------------------------------------------------------------------------------------*/
/*  PLLCON constant definitions. PLL = FIN * NF / NR / NO                                                  */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_PLLCON_PLL_SRC_HXT   0x00000000UL    /*!< For PLL clock source is HXT.  4MHz < FIN < 24MHz */
#define CLK_PLLCON_PLL_SRC_HIRC  0x00080000UL    /*!< For PLL clock source is HIRC. 4MHz < FIN < 24MHz */

#define CLK_PLLCON_NR(x)         (((x)-2)<<9)    /*!< x must be constant and 2 <= x <= 33.  1.6MHz < FIN/NR < 15MHz */
#define CLK_PLLCON_NF(x)          ((x)-2)        /*!< x must be constant and 2 <= x <= 513. 100MHz < FIN*NF/NR < 200MHz. (120MHz < FIN*NF/NR < 200MHz is preferred.) */

#define CLK_PLLCON_NO_1          0x0000UL         /*!< For output divider is 1 */
#define CLK_PLLCON_NO_2          0x4000UL         /*!< For output divider is 2 */
#define CLK_PLLCON_NO_4          0xC000UL         /*!< For output divider is 4 */

#define CLK_PLLCON_50MHz_HXT     (CLK_PLLCON_PLL_SRC_HXT  | CLK_PLLCON_NR(3)  | CLK_PLLCON_NF( 25) | CLK_PLLCON_NO_2) /*!< Predefined PLLCON setting for 50MHz PLL output with 12MHz X'tal */
#define CLK_PLLCON_50MHz_HIRC    (CLK_PLLCON_PLL_SRC_HIRC | CLK_PLLCON_NR(13) | CLK_PLLCON_NF( 59) | CLK_PLLCON_NO_2) /*!< Predefined PLLCON setting for 50.1918MHz PLL output with 22.1184MHz IRC */


/*---------------------------------------------------------------------------------------------------------*/
/*  MODULE constant definitions.                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
#define MODULE_APBCLK(x)         ((x >>31) & 0x1)    /*!< Calculate APBCLK offset on MODULE index */
#define MODULE_CLKSEL(x)         ((x >>29) & 0x3)    /*!< Calculate CLKSEL offset on MODULE index */
#define MODULE_CLKSEL_Msk(x)     ((x >>25) & 0xf)    /*!< Calculate CLKSEL mask offset on MODULE index */
#define MODULE_CLKSEL_Pos(x)     ((x >>20) & 0x1f)   /*!< Calculate CLKSEL position offset on MODULE index */
#define MODULE_CLKDIV(x)         ((x >>18) & 0x3)    /*!< Calculate APBCLK CLKDIV on MODULE index */
#define MODULE_CLKDIV_Msk(x)     ((x >>10) & 0xff)   /*!< Calculate CLKDIV mask offset on MODULE index */
#define MODULE_CLKDIV_Pos(x)     ((x >>5 ) & 0x1f)   /*!< Calculate CLKDIV position offset on MODULE index */
#define MODULE_IP_EN_Pos(x)      ((x >>0 ) & 0x1f)   /*!< Calculate APBCLK offset on MODULE index */
#define MODULE_NoMsk             0x0                 /*!< Not mask on MODULE index */
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                     APBCLK(31)|CLKSEL(30:29)|CLKSEL_Msk(28:25) |CLKSEL_Pos(24:20)|CLKDIV(19:18)|CLKDIV_Msk(17:10)|CLKDIV_Pos(9:5)|IP_EN_Pos(4:0)*/
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
#define WDT_MODULE     ((0x0<<31)|(0x1<<29)    |(0x3<<25)         |( 0<<20)                       |(MODULE_NoMsk<<10)               |CLK_APBCLK_WDT_EN_Pos )     /*!< WDT Module */
#define TMR0_MODULE    ((0x0<<31)|(0x1<<29)    |(0x7<<25)         |( 8<<20)                       |(MODULE_NoMsk<<10)               |CLK_APBCLK_TMR0_EN_Pos)     /*!< TMR0 Module */
#define TMR1_MODULE    ((0x0<<31)|(0x1<<29)    |(0x7<<25)         |(12<<20)                       |(MODULE_NoMsk<<10)               |CLK_APBCLK_TMR1_EN_Pos)     /*!< TMR1 Module */
#define TMR2_MODULE    ((0x0<<31)|(0x1<<29)    |(0x7<<25)         |(16<<20)                       |(MODULE_NoMsk<<10)               |CLK_APBCLK_TMR0_EN_Pos)     /*!< TMR2 Module */
#define TMR3_MODULE    ((0x0<<31)|(0x1<<29)    |(0x7<<25)         |(20<<20)                       |(MODULE_NoMsk<<10)               |CLK_APBCLK_TMR1_EN_Pos)     /*!< TMR3 Module */
#define FDIV_MODULE    ((0x0<<31)|(0x3<<29)    |(0x3<<25)         |( 2<<20)                       |(MODULE_NoMsk<<10)               |CLK_APBCLK_FDIV_EN_Pos)     /*!< FDIV Module */
#define I2C0_MODULE    ((0x0<<31)              |(MODULE_NoMsk<<25)                                |(MODULE_NoMsk<<10)               |CLK_APBCLK_I2C0_EN_Pos)     /*!< I2C0 Module */
#define I2C1_MODULE    ((0x0<<31)              |(MODULE_NoMsk<<25)                                |(MODULE_NoMsk<<10)               |CLK_APBCLK_I2C1_EN_Pos)     /*!< I2C1 Module */
#define SPI0_MODULE    ((0x0<<31)|(0x1<<29)    |(0x1<<25)         |( 4<<20)                       |(MODULE_NoMsk<<10)               |CLK_APBCLK_SPI0_EN_Pos)     /*!< SPI0 Module */
#define SPI1_MODULE    ((0x0<<31)|(0x1<<29)    |(0x1<<25)         |( 5<<20)                       |(MODULE_NoMsk<<10)               |CLK_APBCLK_SPI1_EN_Pos)     /*!< SPI1 Module */
#define UART0_MODULE   ((0x0<<31)|(0x1<<29)    |(0x3<<25)         |(24<<20)         |(0x0<<18)    |(0x0F<<10)       |( 8<<5)        |CLK_APBCLK_UART0_EN_Pos)    /*!< UART0 Module */
#define UART1_MODULE   ((0x0<<31)|(0x1<<29)    |(0x3<<25)         |(24<<20)         |(0x0<<18)    |(0x0F<<10)       |( 8<<5)        |CLK_APBCLK_UART1_EN_Pos)    /*!< UART1 Module */
#define PWM01_MODULE   ((0x0<<31)|(0x1<<29)    |(0x3<<25)         |(28<<20)                       |(MODULE_NoMsk<<10)               |CLK_APBCLK_PWM01_EN_Pos)    /*!< PWM01 Module */
#define PWM23_MODULE   ((0x0<<31)|(0x1<<29)    |(0x3<<25)         |(30<<20)                       |(MODULE_NoMsk<<10)               |CLK_APBCLK_PWM23_EN_Pos)    /*!< PWM23 Module */
#define PWM45_MODULE   ((0x0<<31)|(0x3<<29)    |(0x3<<25)         |( 4<<20)                       |(MODULE_NoMsk<<10)               |CLK_APBCLK_PWM45_EN_Pos)    /*!< PWM45 Module */
#define PWM67_MODULE   ((0x0<<31)|(0x3<<29)    |(0x3<<25)         |( 6<<20)                       |(MODULE_NoMsk<<10)               |CLK_APBCLK_PWM67_EN_Pos)    /*!< PWM67 Module */
#define ADC_MODULE     ((0x0<<31)|(0x1<<29)    |(0x3<<25)         |( 2<<20)         |(0x0<<18)    |(0xFF<<10)        |(16<<5)       |CLK_APBCLK_ADC_EN_Pos)      /*!< ADC Module */
#define ACMP01_MODULE  ((0x0<<31)              |(MODULE_NoMsk<<25)                                |(MODULE_NoMsk<<10)               |CLK_APBCLK_ACMP01_EN_Pos)   /*!< ACMP01 Module */
#define ACMP23_MODULE  ((0x0<<31)              |(MODULE_NoMsk<<25)                                |(MODULE_NoMsk<<10)               |CLK_APBCLK_ACMP23_EN_Pos)   /*!< ACMP23 Module */
#define WWDT_MODULE    ((MODULE_NoMsk<<31)|(0x3<<29)|(0x3<<25)    |(16<<20)                       |(MODULE_NoMsk<<10)               |MODULE_NoMsk )              /*!< WWDT Module */


/*@}*/ /* end of group M051_CLK_EXPORTED_CONSTANTS */


/** @addtogroup M051_CLK_EXPORTED_FUNCTIONS CLK Exported Functions
  @{
*/


/**
  * @brief  This function get PLL frequency. The frequency unit is Hz.
  * @return PLL frequency
  */
static __INLINE uint32_t CLK_GetPLLClockFreq(void)
{
    uint32_t u32PllFreq = 0, u32PllReg;
    uint32_t u32FIN, u32NF, u32NR, u32NO;
    uint8_t au8NoTbl[4] = {1, 2, 2, 4};

    u32PllReg = CLK->PLLCON;

    if(u32PllReg & (CLK_PLLCON_PD_Msk | CLK_PLLCON_OE_Msk))
        return 0;           /* PLL is in power down mode or fix low */

    if(u32PllReg & CLK_PLLCON_PLL_SRC_HIRC)
        u32FIN = __HIRC;    /* PLL source clock from HIRC */
    else
        u32FIN = __HXT;     /* PLL source clock from HXT */

    if(u32PllReg & CLK_PLLCON_BP_Msk)
        return u32FIN;      /* PLL is in bypass mode */

    /* PLL is output enabled in normal work mode */
    u32NO = au8NoTbl[((u32PllReg & CLK_PLLCON_OUT_DV_Msk) >> CLK_PLLCON_OUT_DV_Pos)];
    u32NF = ((u32PllReg & CLK_PLLCON_FB_DV_Msk) >> CLK_PLLCON_FB_DV_Pos) + 2;
    u32NR = ((u32PllReg & CLK_PLLCON_IN_DV_Msk) >> CLK_PLLCON_IN_DV_Pos) + 2;

    /* u32FIN is shifted 2 bits to avoid overflow */
    u32PllFreq = (((u32FIN >> 2) * u32NF) / (u32NR * u32NO) << 2);

    return u32PllFreq;
}

/**
  * @brief      This function execute delay function.
  * @param      us  Delay time. The Max value is 2^24 / CPU Clock(MHz). Ex:
  *                             50MHz => 335544us, 48MHz => 349525us, 28MHz => 699050us ...
  * @return     None
  * @details    Use the SysTick to generate the delay time and the UNIT is in us.
  *             The SysTick clock source is from HCLK, i.e the same as system core clock.
  */
static __INLINE void CLK_SysTickDelay(uint32_t us)
{
    SysTick->LOAD = us * CyclesPerUs;
    SysTick->VAL  = (0x00);
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

    /* Waiting for down-count to zero */
    while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);
}


void CLK_DisableCKO(void);
void CLK_EnableCKO(uint32_t u32ClkSrc, uint32_t u32ClkDiv, uint32_t u32ClkDivBy1En);
void CLK_PowerDown(void);
void CLK_Idle(void);
uint32_t CLK_GetHXTFreq(void);
uint32_t CLK_GetLXTFreq(void);
uint32_t CLK_GetHCLKFreq(void);
uint32_t CLK_GetPCLKFreq(void);
uint32_t CLK_GetCPUFreq(void);
uint32_t CLK_SetCoreClock(uint32_t u32Hclk);
void CLK_SetHCLK(uint32_t u32ClkSrc, uint32_t u32ClkDiv);
void CLK_SetModuleClock(uint32_t u32ModuleIdx, uint32_t u32ClkSrc, uint32_t u32ClkDiv);
void CLK_SetSysTickClockSrc(uint32_t u32ClkSrc);
void CLK_EnableXtalRC(uint32_t u32ClkMask);
void CLK_DisableXtalRC(uint32_t u32ClkMask);
void CLK_EnableModuleClock(uint32_t u32ModuleIdx);
void CLK_DisableModuleClock(uint32_t u32ModuleIdx);
uint32_t CLK_EnablePLL(uint32_t u32PllClkSrc, uint32_t u32PllFreq);
void CLK_DisablePLL(void);
void CLK_WaitClockReady(uint32_t u32ClkMask);


/*@}*/ /* end of group M051_CLK_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group M051_CLK_Driver */

/*@}*/ /* end of group M051_Device_Driver */



#endif //__CLK_H__



/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
