/**************************************************************************//**
 * @file     clk.c
 * @version  V3.00
 * $Revision: 15 $
 * $Date: 14/01/28 10:49a $
 * @brief    M051 series CLK driver source file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "M051Series.h"
/** @addtogroup M051_Device_Driver M051 Device Driver
  @{
*/

/** @addtogroup M051_CLK_Driver CLK Driver
  @{
*/


/** @addtogroup M051_CLK_EXPORTED_FUNCTIONS CLK Exported Functions
  @{
*/

/**
  * @brief  This function disable frequency output function.
  * @return None
  */
void CLK_DisableCKO(void)
{
    /* Disable CKO clock source */
    CLK_DisableModuleClock(FDIV_MODULE);
}

/**
  * @brief  This function enable frequency divider module clock,
  *         enable frequency divider clock function and configure frequency divider.
  * @param  u32ClkSrc is frequency divider function clock source. Including :
  *           - \ref CLK_CLKSEL2_FRQDIV_S_HXT
  *           - \ref CLK_CLKSEL2_FRQDIV_S_LIRC
  *           - \ref CLK_CLKSEL2_FRQDIV_S_HCLK
  *           - \ref CLK_CLKSEL2_FRQDIV_S_HIRC
  * @param  u32ClkDiv is divider output frequency selection.
  * @param  u32ClkDivBy1En is frequency divided by one enable.
  * @return None
  *
  * @details    Output selected clock to CKO. The output clock frequency is divided by u32ClkDiv.
  *             The formula is:
  *                 CKO frequency = (Clock source frequency) / 2^(u32ClkDiv + 1)
  *             This function is just used to set CKO clock.
  *             User must enable I/O for CKO clock output pin by themselves.
  */
void CLK_EnableCKO(uint32_t u32ClkSrc, uint32_t u32ClkDiv, uint32_t u32ClkDivBy1En)
{
    /* CKO = clock source / 2^(u32ClkDiv + 1) */
    CLK->FRQDIV = CLK_FRQDIV_DIVIDER_EN_Msk | u32ClkDiv | u32ClkDivBy1En << CLK_FRQDIV_DIVIDER1_Pos;

    /* Enable CKO clock source */
    CLK_EnableModuleClock(FDIV_MODULE);

    /* Select CKO clock source */
    CLK_SetModuleClock(FDIV_MODULE, u32ClkSrc, 0);
}

/**
  * @brief  This function let system enter to Power-down mode.
  * @return None
  */
void CLK_PowerDown(void)
{
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    CLK->PWRCON |= (CLK_PWRCON_PWR_DOWN_EN_Msk | CLK_PWRCON_PD_WAIT_CPU_Msk);
    __WFI();
}

/**
  * @brief  This function let system enter to Idle mode.
  * @return None
  */
void CLK_Idle(void)
{
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    CLK->PWRCON &= ~CLK_PWRCON_PWR_DOWN_EN_Msk;
    __WFI();
}

/**
  * @brief  This function get external high frequency crystal frequency. The frequency unit is Hz.
  * @return External high frequency crystal frequency
  */
uint32_t CLK_GetHXTFreq(void)
{
    if(CLK->PWRCON & CLK_PWRCON_XTL12M_EN_Msk)
        return __HXT;
    else
        return 0;
}


/**
  * @brief  This function get HCLK frequency. The frequency unit is Hz.
  * @return HCLK frequency
  */
uint32_t CLK_GetHCLKFreq(void)
{
    SystemCoreClockUpdate();
    return SystemCoreClock;
}


/**
  * @brief  This function get CPU frequency. The frequency unit is Hz.
  * @return CPU frequency
  */
uint32_t CLK_GetCPUFreq(void)
{
    SystemCoreClockUpdate();
    return SystemCoreClock;
}


/**
  * @brief  This function set HCLK frequency. The frequency unit is Hz. The range of u32Hclk is 16 ~ 32 MHz
  * @param  u32Hclk is HCLK frequency
  * @return HCLK frequency
  */
uint32_t CLK_SetCoreClock(uint32_t u32Hclk)
{
    if(u32Hclk > FREQ_50MHZ)
        u32Hclk = FREQ_50MHZ;
    else if(u32Hclk < FREQ_25MHZ)
        u32Hclk = FREQ_25MHZ;

    if(CLK->PWRCON & CLK_PWRCON_XTL12M_EN_Msk)
        u32Hclk = CLK_EnablePLL(CLK_PLLCON_PLL_SRC_HXT, u32Hclk);
    else
        u32Hclk = CLK_EnablePLL(CLK_PLLCON_PLL_SRC_HIRC, u32Hclk);

    CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_PLL, CLK_CLKDIV_HCLK(1));

    return u32Hclk;
}

/**
  * @brief  This function set HCLK clock source and HCLK clock divider
  * @param  u32ClkSrc is HCLK clock source. Including :
  *         - \ref CLK_CLKSEL0_HCLK_S_HXT
  *         - \ref CLK_CLKSEL0_HCLK_S_PLL
  *         - \ref CLK_CLKSEL0_HCLK_S_LIRC
  *         - \ref CLK_CLKSEL0_HCLK_S_HIRC
  * @param  u32ClkDiv is HCLK clock divider. Including :
  *         - \ref CLK_CLKDIV_HCLK(x)
  * @return None
  */
void CLK_SetHCLK(uint32_t u32ClkSrc, uint32_t u32ClkDiv)
{
    CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_HCLK_S_Msk) | u32ClkSrc;
    CLK->CLKDIV = (CLK->CLKDIV & ~CLK_CLKDIV_HCLK_N_Msk) | u32ClkDiv;
    SystemCoreClockUpdate();
}

/**
  * @brief  This function set selected module clock source and module clock divider
  * @param  u32ModuleIdx is module index.
  * @param  u32ClkSrc is module clock source.
  * @param  u32ClkDiv is module clock divider.
  * @return None
  * @details Valid parameter combinations listed in following table:
  *
  * |Module index        |Clock source                          |Divider                 |
  * | :----------------  | :----------------------------------- | :--------------------- |
  * |\ref WDT_MODULE     |\ref CLK_CLKSEL1_WDT_S_HCLK_DIV2048   | x                      |
  * |\ref WDT_MODULE     |\ref CLK_CLKSEL1_WDT_S_LIRC           | x                      |
  * |\ref ADC_MODULE     |\ref CLK_CLKSEL1_ADC_S_HXT            |\ref CLK_CLKDIV_ADC(x)  |
  * |\ref ADC_MODULE     |\ref CLK_CLKSEL1_ADC_S_PLL            |\ref CLK_CLKDIV_ADC(x)  |
  * |\ref ADC_MODULE     |\ref CLK_CLKSEL1_ADC_S_HCLK           |\ref CLK_CLKDIV_ADC(x)  |
  * |\ref ADC_MODULE     |\ref CLK_CLKSEL1_ADC_S_HIRC           |\ref CLK_CLKDIV_ADC(x)  |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL1_SPI0_S_HCLK          | x                      |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL1_SPI0_S_PLL           | x                      |
  * |\ref SPI1_MODULE    |\ref CLK_CLKSEL1_SPI1_S_HCLK          | x                      |
  * |\ref SPI1_MODULE    |\ref CLK_CLKSEL1_SPI1_S_PLL           | x                      |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0_S_HXT           | x                      |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0_S_HCLK          | x                      |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0_S_T0            | x                      |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0_S_LIRC          | x                      |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0_S_HIRC          | x                      |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR0_S_HXT           | x                      |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR0_S_HCLK          | x                      |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR0_S_T1            | x                      |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR0_S_LIRC          | x                      |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR0_S_HIRC          | x                      |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2_S_HXT           | x                      |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2_S_HCLK          | x                      |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2_S_T2            | x                      |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2_S_LIRC          | x                      |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2_S_HIRC          | x                      |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3_S_HXT           | x                      |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3_S_HCLK          | x                      |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3_S_T3            | x                      |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3_S_LIRC          | x                      |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3_S_HIRC          | x                      |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL1_UART_S_HXT           |\ref CLK_CLKDIV_UART(x) |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL1_UART_S_PLL           |\ref CLK_CLKDIV_UART(x) |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL1_UART_S_HIRC          |\ref CLK_CLKDIV_UART(x) |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL1_UART_S_HXT           |\ref CLK_CLKDIV_UART(x) |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL1_UART_S_PLL           |\ref CLK_CLKDIV_UART(x) |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL1_UART_S_HIRC          |\ref CLK_CLKDIV_UART(x) |
  * |\ref PWM01_MODULE   |\ref CLK_CLKSEL1_PWM01_S_HXT          | x                      |
  * |\ref PWM01_MODULE   |\ref CLK_CLKSEL1_PWM01_S_LIRC         | x                      |
  * |\ref PWM01_MODULE   |\ref CLK_CLKSEL1_PWM01_S_HCLK         | x                      |
  * |\ref PWM01_MODULE   |\ref CLK_CLKSEL1_PWM01_S_HIRC         | x                      |
  * |\ref PWM23_MODULE   |\ref CLK_CLKSEL1_PWM23_S_HXT          | x                      |
  * |\ref PWM23_MODULE   |\ref CLK_CLKSEL1_PWM23_S_LIRC         | x                      |
  * |\ref PWM23_MODULE   |\ref CLK_CLKSEL1_PWM23_S_HCLK         | x                      |
  * |\ref PWM23_MODULE   |\ref CLK_CLKSEL1_PWM23_S_HIRC         | x                      |
  * |\ref FDIV_MODULE    |\ref CLK_CLKSEL2_FRQDIV_S_HXT         | x                      |
  * |\ref FDIV_MODULE    |\ref CLK_CLKSEL2_FRQDIV_S_LIRC        | x                      |
  * |\ref FDIV_MODULE    |\ref CLK_CLKSEL2_FRQDIV_S_HCLK        | x                      |
  * |\ref FDIV_MODULE    |\ref CLK_CLKSEL2_FRQDIV_S_HIRC        | x
  * |\ref PWM45_MODULE   |\ref CLK_CLKSEL2_PWM45_S_HXT          | x                      |
  * |\ref PWM45_MODULE   |\ref CLK_CLKSEL2_PWM45_S_LIRC         | x                      |
  * |\ref PWM45_MODULE   |\ref CLK_CLKSEL2_PWM45_S_HCLK         | x                      |
  * |\ref PWM45_MODULE   |\ref CLK_CLKSEL2_PWM45_S_HIRC         | x                      |
  * |\ref PWM67_MODULE   |\ref CLK_CLKSEL2_PWM67_S_HXT          | x                      |
  * |\ref PWM67_MODULE   |\ref CLK_CLKSEL2_PWM67_S_LIRC         | x                      |
  * |\ref PWM67_MODULE   |\ref CLK_CLKSEL2_PWM67_S_HCLK         | x                      |
  * |\ref PWM67_MODULE   |\ref CLK_CLKSEL2_PWM67_S_HIRC         | x                      |
  * |\ref WWDT_MODULE    |\ref CLK_CLKSEL1_WWDT_S_HCLK_DIV2048  | x                      |
  * |\ref WWDT_MODULE    |\ref CLK_CLKSEL1_WWDT_S_LIRC          | x                      |
    */

void CLK_SetModuleClock(uint32_t u32ModuleIdx, uint32_t u32ClkSrc, uint32_t u32ClkDiv)
{
    uint32_t u32tmp = 0, u32sel = 0, u32div = 0;

    if(MODULE_CLKSEL_Msk(u32ModuleIdx) != MODULE_NoMsk)
    {
        u32sel = (uint32_t)&CLK->CLKSEL0 + ((MODULE_CLKSEL(u32ModuleIdx)) * 4);
        u32tmp = *(volatile uint32_t *)(u32sel);
        u32tmp = u32tmp & ~(MODULE_CLKSEL_Msk(u32ModuleIdx) << MODULE_CLKSEL_Pos(u32ModuleIdx)) | u32ClkSrc;
        *(volatile uint32_t *)(u32sel) = u32tmp;
    }

    if(MODULE_CLKDIV_Msk(u32ModuleIdx) != MODULE_NoMsk)
    {
        u32div = (uint32_t)&CLK->CLKDIV + ((MODULE_CLKDIV(u32ModuleIdx)) * 4);
        u32tmp = *(volatile uint32_t *)(u32div);
        u32tmp = (u32tmp & ~MODULE_CLKDIV_Msk(u32ModuleIdx) << MODULE_CLKDIV_Pos(u32ModuleIdx)) | u32ClkDiv;
        *(volatile uint32_t *)(u32div) = u32tmp;
    }
}

/**
  * @brief  This function set systick clock source
  * @param  u32ClkSrc is module clock source. Including
  *           - \ref CLK_CLKSEL0_STCLK_S_HXT
  *           - \ref CLK_CLKSEL0_STCLK_S_HXT_DIV2
  *           - \ref CLK_CLKSEL0_STCLK_S_HCLK_DIV2
  *           - \ref CLK_CLKSEL0_STCLK_S_HIRC_DIV2
  * @return None
  */
void CLK_SetSysTickClockSrc(uint32_t u32ClkSrc)
{
    CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_STCLK_S_Msk) | u32ClkSrc;
}

/**
  * @brief  This function enable clock source
  * @param  u32ClkMask is clock source mask. Including :
  *         - \ref CLK_PWRCON_XTL12M_EN_Msk
  *         - \ref CLK_PWRCON_OSC22M_EN_Msk
  *         - \ref CLK_PWRCON_OSC10K_EN_Msk
  * @return None
  */
void CLK_EnableXtalRC(uint32_t u32ClkMask)
{
    CLK->PWRCON |= u32ClkMask;
}

/**
  * @brief  This function disable clock source
  * @param  u32ClkMask is clock source mask. Including :
  *         - \ref CLK_PWRCON_XTL12M_EN_Msk
  *         - \ref CLK_PWRCON_OSC22M_EN_Msk
  *         - \ref CLK_PWRCON_OSC10K_EN_Msk
  * @return None
  */
void CLK_DisableXtalRC(uint32_t u32ClkMask)
{
    CLK->PWRCON &= ~u32ClkMask;
}

/**
  * @brief  This function enable module clock
  * @param  u32ModuleIdx is module index. Including :
  *   - \ref WDT_MODULE
  *   - \ref TMR0_MODULE
  *   - \ref TMR1_MODULE
  *   - \ref TMR2_MODULE
  *   - \ref TMR3_MODULE
  *   - \ref FDIV_MODULE
  *   - \ref I2C0_MODULE
  *   - \ref I2C1_MODULE
  *   - \ref SPI0_MODULE
  *   - \ref SPI1_MODULE
  *   - \ref UART0_MODULE
  *   - \ref UART1_MODULE
  *   - \ref PWM01_MODULE
  *   - \ref PWM23_MODULE
  *   - \ref PWM45_MODULE
  *   - \ref PWM67_MODULE
  *   - \ref ADC_MODULE
  *   - \ref ACMP01_MODULE
  *   - \ref ACMP23_MODULE
  * @return None
  */
void CLK_EnableModuleClock(uint32_t u32ModuleIdx)
{
    *(volatile uint32_t *)((uint32_t)&CLK->APBCLK + (MODULE_APBCLK(u32ModuleIdx) * 4))  |= 1 << MODULE_IP_EN_Pos(u32ModuleIdx);
}

/**
  * @brief  This function disable module clock
  * @param  u32ModuleIdx is module index
  *   - \ref WDT_MODULE
  *   - \ref TMR0_MODULE
  *   - \ref TMR1_MODULE
  *   - \ref TMR2_MODULE
  *   - \ref TMR3_MODULE
  *   - \ref FDIV_MODULE
  *   - \ref I2C0_MODULE
  *   - \ref I2C1_MODULE
  *   - \ref SPI0_MODULE
  *   - \ref SPI1_MODULE
  *   - \ref UART0_MODULE
  *   - \ref UART1_MODULE
  *   - \ref PWM01_MODULE
  *   - \ref PWM23_MODULE
  *   - \ref PWM45_MODULE
  *   - \ref PWM67_MODULE
  *   - \ref ADC_MODULE
  *   - \ref ACMP01_MODULE
  *   - \ref ACMP23_MODULE
  * @return None
  */
void CLK_DisableModuleClock(uint32_t u32ModuleIdx)
{
    *(volatile uint32_t *)((uint32_t)&CLK->APBCLK + (MODULE_APBCLK(u32ModuleIdx) * 4))  &= ~(1 << MODULE_IP_EN_Pos(u32ModuleIdx));
}


/**
  * @brief  This function set PLL frequency
  * @param  u32PllClkSrc is PLL clock source. Including :
  *         - \ref CLK_PLLCON_PLL_SRC_HXT
  *         - \ref CLK_PLLCON_PLL_SRC_HIRC
  * @param  u32PllFreq is PLL frequency
  * @return PLL frequency
  */
uint32_t CLK_EnablePLL(uint32_t u32PllClkSrc, uint32_t u32PllFreq)
{
    uint32_t u32PllSrcClk, u32PLLReg, u32NR, u32NF, u32NO;

    if(u32PllClkSrc == CLK_PLLCON_PLL_SRC_HXT)
    {
        /* PLL source clock from HXT */
        CLK->PLLCON &= ~CLK_PLLCON_PLL_SRC_Msk;
        u32PllSrcClk = __HXT;
    }
    else
    {
        /* PLL source clock from HIRC */
        CLK->PLLCON |= CLK_PLLCON_PLL_SRC_Msk;
        u32PllSrcClk = __HIRC;
    }

    if((u32PllFreq <= FREQ_200MHZ) && (u32PllFreq > FREQ_100MHZ))
    {
        u32NO = 0;
    }
    else if((u32PllFreq <= FREQ_100MHZ) && (u32PllFreq > FREQ_50MHZ))
    {
        u32NO = 1;
        u32PllFreq = u32PllFreq << 1;
    }
    else if((u32PllFreq <= FREQ_50MHZ) && (u32PllFreq >= FREQ_25MHZ))
    {
        u32NO = 3;
        u32PllFreq = u32PllFreq << 2;
    }
    else
    {
        if(u32PllClkSrc == CLK_PLLCON_PLL_SRC_HXT)
            CLK->PLLCON = 0xC22E;
        else
            CLK->PLLCON = 0xD66F;

        CLK_WaitClockReady(CLK_CLKSTATUS_PLL_STB_Msk);
        return CLK_GetPLLClockFreq();
    }

    u32NF = u32PllFreq / 1000000;
    u32NR = u32PllSrcClk / 1000000;

    while(1)
    {
        if((u32NR & 0x01) || (u32NF & 0x01) || (u32NR == 2) || (u32NF == 2))
        {
            break;
        }
        else
        {
            u32NR >>= 1;
            u32NF >>= 1;
        }
    }

    u32PLLReg = (u32NO << 14) | ((u32NR - 2) << 9) | (u32NF - 2);

    CLK->PLLCON = (CLK->PLLCON & ~(CLK_PLLCON_FB_DV_Msk | CLK_PLLCON_IN_DV_Msk | CLK_PLLCON_OUT_DV_Msk)) | u32PLLReg;

    CLK->PLLCON &= ~(CLK_PLLCON_PD_Msk | CLK_PLLCON_OE_Msk);

    CLK_WaitClockReady(CLK_CLKSTATUS_PLL_STB_Msk);

    return ((u32PllSrcClk * u32NF) / (u32NR * (u32NO + 1)));
}

/**
  * @brief  This function disable PLL
  * @param  None
  * @return None
  */
void CLK_DisablePLL(void)
{
    CLK->PLLCON |= CLK_PLLCON_PD_Msk;
}


/**
  * @brief  This function check selected clock source status
  * @param  u32ClkMask is selected clock source. Including :
  *           - \ref CLK_CLKSTATUS_OSC22M_STB_Msk
  *           - \ref CLK_CLKSTATUS_OSC10K_STB_Msk
  *           - \ref CLK_CLKSTATUS_XTL12M_STB_Msk
  *           - \ref CLK_CLKSTATUS_PLL_STB_Msk
  *
  * @return None
  */
void CLK_WaitClockReady(uint32_t u32ClkMask)
{
    int32_t i32TimeOutCnt;

    i32TimeOutCnt = __HSI / 200; /* About 5ms */

    while((CLK->CLKSTATUS & u32ClkMask) != u32ClkMask)
    {
        if(i32TimeOutCnt-- <= 0)
            break;
    }
}


/*@}*/ /* end of group M051_CLK_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group M051_CLK_Driver */

/*@}*/ /* end of group M051_Device_Driver */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
