/**************************************************************************//**
 * @file     clk.c
 * @version  V3.00
 * @brief    M2354 series Clock Controller (CLK) driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NuMicro.h"
/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup CLK_Driver CLK Driver
  @{
*/


/** @addtogroup CLK_EXPORTED_FUNCTIONS CLK Exported Functions
  @{
*/


/**
  * @brief      Disable frequency output function
  * @param      None
  * @return     None
  * @details    This function disable frequency output function.
  */
void CLK_DisableCKO(void)
{
    /* Disable CKO clock source */
    CLK->APBCLK0 &= (~CLK_APBCLK0_CLKOCKEN_Msk);
}


/**
  * @brief      This function enable frequency divider module clock.
  *             enable frequency divider clock function and configure frequency divider.
  * @param[in]  u32ClkSrc is frequency divider function clock source. Including :
  *             - \ref CLK_CLKSEL1_CLKOSEL_HXT
  *             - \ref CLK_CLKSEL1_CLKOSEL_LXT
  *             - \ref CLK_CLKSEL1_CLKOSEL_HCLK
  *             - \ref CLK_CLKSEL1_CLKOSEL_HIRC
  * @param[in]  u32ClkDiv is divider output frequency selection.
  * @param[in]  u32ClkDivBy1En is frequency divided by one enable.
  * @return     None
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
    CLK->CLKOCTL = CLK_CLKOCTL_CLKOEN_Msk | u32ClkDiv | (u32ClkDivBy1En << CLK_CLKOCTL_DIV1EN_Pos);

    /* Enable CKO clock source */
    CLK->APBCLK0 |= CLK_APBCLK0_CLKOCKEN_Msk;

    /* Select CKO clock source */
    CLK->CLKSEL1 = (CLK->CLKSEL1 & (~CLK_CLKSEL1_CLKOSEL_Msk)) | (u32ClkSrc);

}

/**
  * @brief      Enter to Power-down mode
  * @param      None
  * @return     None
  * @details    This function is used to let system enter to Power-down mode. \n
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_PowerDown(void)
{
    volatile uint32_t u32SysTickTICKINT = 0;    /* Backup Systick interrupt enable bit */

    /* Set the processor uses deep sleep as its low power mode */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Set system Power-down enabled */
    CLK->PWRCTL |= CLK_PWRCTL_PDEN_Msk;

    /* Backup systick interrupt setting */
    u32SysTickTICKINT = SysTick->CTRL & SysTick_CTRL_TICKINT_Msk;

    /* Disable systick interrupt */
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;

    /* Chip enter Power-down mode after CPU run WFI instruction */
    __WFI();

    /* Restore systick interrupt setting */
    if(u32SysTickTICKINT) SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
}


/**
  * @brief      Enter to Idle mode
  * @param      None
  * @return     None
  * @details    This function let system enter to Idle mode. \n
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_Idle(void)
{
    /* Set the processor uses sleep as its low power mode */
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;

    /* Set chip in idle mode because of WFI command */
    CLK->PWRCTL &= ~CLK_PWRCTL_PDEN_Msk;

    /* Chip enter idle mode after CPU run WFI instruction */
    __WFI();
}


/**
  * @brief      Get external high speed crystal clock frequency
  * @param      None
  * @return     External high frequency crystal frequency
  * @details    This function get external high frequency crystal frequency. The frequency unit is Hz.
  */
__NONSECURE_ENTRY_WEAK
uint32_t CLK_GetHXTFreq(void)
{
    uint32_t u32Freq = 0UL;
    uint32_t u32HXTEN = CLK->PWRCTL & CLK_PWRCTL_HXTEN_Msk;

    if(u32HXTEN)
    {
        u32Freq = __HXT;
    }
    else
    {
        u32Freq = 0UL;
    }

    return u32Freq;
}

/**
  * @brief      Get external low speed crystal clock frequency
  * @param      None
  * @return     External low speed crystal clock frequency
  * @details    This function get external low frequency crystal frequency. The frequency unit is Hz.
  */

__NONSECURE_ENTRY_WEAK
uint32_t CLK_GetLXTFreq(void)
{
    uint32_t u32Freq = 0UL;
    uint32_t u32LXTEN = CLK->PWRCTL & CLK_PWRCTL_LXTEN_Msk;

    if(u32LXTEN)
    {
        u32Freq = __LXT;
    }
    else
    {
        u32Freq = 0UL;
    }

    return u32Freq;
}

/**
  * @brief      Get HCLK frequency
  * @param      None
  * @return     HCLK frequency
  * @details    This function get HCLK frequency. The frequency unit is Hz.
  */

__NONSECURE_ENTRY_WEAK
uint32_t CLK_GetHCLKFreq(void)
{
    SystemCoreClockUpdate();
    return SystemCoreClock;
}

/**
  * @brief      Get PCLK0 frequency
  * @param      None
  * @return     PCLK0 frequency
  * @details    This function get PCLK0 frequency. The frequency unit is Hz.
  */

__NONSECURE_ENTRY_WEAK
uint32_t CLK_GetPCLK0Freq(void)
{
    SystemCoreClockUpdate();
    return (SystemCoreClock);
}

/**
  * @brief      Get PCLK1 frequency
  * @param      None
  * @return     PCLK1 frequency
  * @details    This function get PCLK1 frequency. The frequency unit is Hz.
  */

__NONSECURE_ENTRY_WEAK
uint32_t CLK_GetPCLK1Freq(void)
{
    SystemCoreClockUpdate();
    return (SystemCoreClock);
}

/**
  * @brief      Get CPU frequency
  * @param      None
  * @return     CPU frequency
  * @details    This function get CPU frequency. The frequency unit is Hz.
  */

__NONSECURE_ENTRY_WEAK
uint32_t CLK_GetCPUFreq(void)
{
    uint32_t u32Freq, u32HclkSrc, u32HclkDiv;
    uint32_t au32ClkTbl[] = {__HXT, __LXT, 0UL, __LIRC, 0UL, __HIRC48, __MIRC, __HIRC};
    uint32_t u32PllReg, u32FIN, u32NF, u32NR, u32NO;
    uint8_t au8NoTbl[4] = {1U, 2U, 2U, 4U};
    uint32_t u32RTCCKEN = CLK->APBCLK0 & CLK_APBCLK0_RTCCKEN_Msk;

    /* Update PLL Clock */
    u32PllReg = CLK->PLLCTL;

    if(u32PllReg & CLK_PLLCTL_PD_Msk)
    {
        PllClock = 0UL;         /* PLL is in power down mode */
    }
    else                        /* PLL is in normal mode */
    {

        /* PLL source clock */
        if(u32PllReg & CLK_PLLCTL_PLLSRC_Msk)
        {
            u32FIN = __HIRC;    /* PLL source clock from HIRC */
        }
        else
        {
            u32FIN = __HXT;     /* PLL source clock from HXT */
        }

        /* Calculate PLL frequency */
        if(u32PllReg & CLK_PLLCTL_BP_Msk)
        {
            PllClock = u32FIN;  /* PLL is in bypass mode */
        }
        else
        {
            /* PLL is output enabled in normal work mode */
            u32NO = au8NoTbl[((u32PllReg & CLK_PLLCTL_OUTDIV_Msk) >> CLK_PLLCTL_OUTDIV_Pos)];
            u32NF = ((u32PllReg & CLK_PLLCTL_FBDIV_Msk) >> CLK_PLLCTL_FBDIV_Pos) + 2UL;
            u32NR = ((u32PllReg & CLK_PLLCTL_INDIV_Msk) >> CLK_PLLCTL_INDIV_Pos) + 1UL;

            /* u32FIN is shifted 2 bits to avoid overflow */
            PllClock = (((u32FIN >> 2) * (u32NF << 1)) / (u32NR * u32NO) << 2);
        }
    }

    /* HCLK clock source */
    u32HclkSrc = CLK->CLKSEL0 & CLK_CLKSEL0_HCLKSEL_Msk;

    if(u32HclkSrc == CLK_CLKSEL0_HCLKSEL_LXT)
    {

        if(u32RTCCKEN == 0UL)
        {
            CLK->APBCLK0 |= CLK_APBCLK0_RTCCKEN_Msk; /* Enable RTC clock to get LXT clock source */
        }

        if(RTC->LXTCTL & RTC_LXTCTL_C32KSEL_Msk)
        {
            u32Freq = __LIRC32; /* LXT clock source is LIRC32 */
        }
        else
        {
            u32Freq = __LXT;    /* LXT clock source is external LXT */
        }

        if(u32RTCCKEN == 0UL)
        {
            CLK->APBCLK0 &= (~CLK_APBCLK0_RTCCKEN_Msk); /* Disable RTC clock if it is disabled before */
        }

    }
    else if(u32HclkSrc == CLK_CLKSEL0_HCLKSEL_PLL)
    {
        u32Freq = PllClock;/* Use PLL clock */
    }
    else
    {
        u32Freq = au32ClkTbl[u32HclkSrc]; /* Use the clock sources directly */
    }

    /* HCLK clock source divider */
    u32HclkDiv = (CLK->CLKDIV0 & CLK_CLKDIV0_HCLKDIV_Msk) + 1UL;

    /* Update System Core Clock */
    SystemCoreClock = u32Freq / u32HclkDiv;

    /* Update Cycles per micro second */
    CyclesPerUs = (SystemCoreClock + 500000UL) / 1000000UL;

    return SystemCoreClock;
}

/**
  * @brief      Set HCLK frequency
  * @param[in]  u32Hclk is HCLK frequency.
  *             The range of u32Hclk is 24 MHz ~ 96 MHz.
  * @return     HCLK frequency
  * @details    This function is used to set HCLK frequency by using PLL. \n
  *             Power level is also set according to HCLK frequency. The frequency unit is Hz. \n
  *             The register write-protection function should be disabled before using this function.
  */
uint32_t CLK_SetCoreClock(uint32_t u32Hclk)
{
    uint32_t u32HIRCSTB;

    /* Read HIRC clock source stable flag */
    u32HIRCSTB = CLK->STATUS & CLK_STATUS_HIRCSTB_Msk;

    /* Check HCLK frequency range */
    if(u32Hclk > FREQ_96MHZ)
    {
        u32Hclk = FREQ_96MHZ;
    }
    else if(u32Hclk < FREQ_24MHZ)
    {
        u32Hclk = FREQ_24MHZ;
    }

    /* Switch HCLK clock source to HIRC clock for safe */
    CLK->PWRCTL |= CLK_PWRCTL_HIRCEN_Msk;
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);
    CLK->CLKSEL0 |= CLK_CLKSEL0_HCLKSEL_Msk;
    CLK->CLKDIV0 &= (~CLK_CLKDIV0_HCLKDIV_Msk);

    /* Configure PLL setting if HXT clock is stable */
    if(CLK->STATUS & CLK_STATUS_HXTSTB_Msk)
    {
        u32Hclk = CLK_EnablePLL(CLK_PLLCTL_PLLSRC_HXT, u32Hclk);
    }
    /* Configure PLL setting if HXT clock is not stable */
    else
    {
        u32Hclk = CLK_EnablePLL(CLK_PLLCTL_PLLSRC_HIRC, u32Hclk);

        /* Read HIRC clock source stable flag */
        u32HIRCSTB = CLK->STATUS & CLK_STATUS_HIRCSTB_Msk;
    }

    /* Select HCLK clock source to PLL,
       select HCLK clock source divider as 1,
       adjust power level and update system core clock
    */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_PLL, CLK_CLKDIV0_HCLK(1UL));

    /* Disable HIRC if HIRC is disabled before setting core clock */
    if(u32HIRCSTB == 0UL)
    {
        CLK->PWRCTL &= ~CLK_PWRCTL_HIRCEN_Msk;
    }

    /* Return actually HCLK frequency is PLL frequency divide 1 */
    return u32Hclk;
}


/**
  * @brief      Set HCLK clock source and HCLK clock divider
  * @param[in]  u32ClkSrc is HCLK clock source. Including :
  *             - \ref CLK_CLKSEL0_HCLKSEL_HXT
  *             - \ref CLK_CLKSEL0_HCLKSEL_LXT
  *             - \ref CLK_CLKSEL0_HCLKSEL_PLL
  *             - \ref CLK_CLKSEL0_HCLKSEL_LIRC
  *             - \ref CLK_CLKSEL0_HCLKSEL_HIRC48
  *             - \ref CLK_CLKSEL0_HCLKSEL_MIRC
  *             - \ref CLK_CLKSEL0_HCLKSEL_HIRC
  * @param[in]  u32ClkDiv is HCLK clock divider. Including :
  *             - \ref CLK_CLKDIV0_HCLK(x)
  * @return     None
  * @details    This function set HCLK clock source and HCLK clock divider. \n
  *             Power level and flash access cycle are also set according to HCLK operation frequency. \n
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_SetHCLK(uint32_t u32ClkSrc, uint32_t u32ClkDiv)
{
    uint32_t u32HIRCSTB;

    /* Read HIRC clock source stable flag */
    u32HIRCSTB = CLK->STATUS & CLK_STATUS_HIRCSTB_Msk;

    /* Switch to HIRC for safe. Avoid HCLK too high when applying new divider. */
    CLK->PWRCTL |= CLK_PWRCTL_HIRCEN_Msk;
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);
    CLK->CLKSEL0 |= CLK_CLKSEL0_HCLKSEL_Msk;

    /* Switch to power level 0 for safe */
    while(SYS->PLCTL & SYS_PLCTL_WRBUSY_Msk);
    SYS->PLCTL = (SYS->PLCTL & (~SYS_PLCTL_PLSEL_Msk)) | SYS_PLCTL_PLSEL_PL0;
    while(SYS->PLSTS & SYS_PLSTS_PLCBUSY_Msk);

    /* Set Flash Access Cycle to 4 for safe */
    FMC->CYCCTL = (FMC->CYCCTL & (~FMC_CYCCTL_CYCLE_Msk)) | (4);

    /* Apply new Divider */
    CLK->CLKDIV0 = (CLK->CLKDIV0 & (~CLK_CLKDIV0_HCLKDIV_Msk)) | u32ClkDiv;

    /* Switch HCLK to new HCLK source */
    CLK->CLKSEL0 = (CLK->CLKSEL0 & (~CLK_CLKSEL0_HCLKSEL_Msk)) | u32ClkSrc;

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    /* Set power level according to new HCLK source */
    while(SYS->PLCTL & SYS_PLCTL_WRBUSY_Msk);
    if((SystemCoreClock > FREQ_48MHZ) && SystemCoreClock <= FREQ_84MHZ)
    {
        SYS->PLCTL = (SYS->PLCTL & (~SYS_PLCTL_PLSEL_Msk)) | SYS_PLCTL_PLSEL_PL1;
    }
    else if((SystemCoreClock > FREQ_4MHZ) && SystemCoreClock <= FREQ_48MHZ)
    {
        SYS->PLCTL = (SYS->PLCTL & (~SYS_PLCTL_PLSEL_Msk)) | SYS_PLCTL_PLSEL_PL2;
    }
    if(SystemCoreClock <= FREQ_4MHZ)
    {
        SYS->PLCTL = (SYS->PLCTL & (~SYS_PLCTL_PLSEL_Msk)) | SYS_PLCTL_PLSEL_PL3;
    }
    while(SYS->PLSTS & SYS_PLSTS_PLCBUSY_Msk);

    /* Set Flash Access Cycle */
    if((SystemCoreClock >= FREQ_50MHZ) && SystemCoreClock < FREQ_75MHZ)
    {
        FMC->CYCCTL = (FMC->CYCCTL & (~FMC_CYCCTL_CYCLE_Msk)) | (3);
    }
    else if((SystemCoreClock >= FREQ_25MHZ) && SystemCoreClock < FREQ_50MHZ)
    {
        FMC->CYCCTL = (FMC->CYCCTL & (~FMC_CYCCTL_CYCLE_Msk)) | (2);
    }
    if(SystemCoreClock < FREQ_25MHZ)
    {
        FMC->CYCCTL = (FMC->CYCCTL & (~FMC_CYCCTL_CYCLE_Msk)) | (1);
    }

    /* Disable HIRC if HIRC is disabled before switching HCLK source */
    if(u32HIRCSTB == 0UL)
    {
        CLK->PWRCTL &= ~CLK_PWRCTL_HIRCEN_Msk;
    }
}
/**
  * @brief      This function set selected module clock source and module clock divider
  * @param[in]  u32ModuleIdx is module index.
  * @param[in]  u32ClkSrc is module clock source.
  * @param[in]  u32ClkDiv is module clock divider.
  * @return     None
  * @details    Valid parameter combinations listed in following table:
  *
  * |Module index        |Clock source                           |Divider                   |
  * | :----------------  | :------------------------------------ | :----------------------- |
  * |\ref SDH0_MODULE    |\ref CLK_CLKSEL0_SDH0SEL_HXT           |\ref CLK_CLKDIV0_SDH0(x)  |
  * |\ref SDH0_MODULE    |\ref CLK_CLKSEL0_SDH0SEL_PLL           |\ref CLK_CLKDIV0_SDH0(x)  |
  * |\ref SDH0_MODULE    |\ref CLK_CLKSEL0_SDH0SEL_HCLK          |\ref CLK_CLKDIV0_SDH0(x)  |
  * |\ref SDH0_MODULE    |\ref CLK_CLKSEL0_SDH0SEL_HIRC          |\ref CLK_CLKDIV0_SDH0(x)  |
  * |\ref WDT_MODULE     |\ref CLK_CLKSEL1_WDTSEL_LXT            | x                        |
  * |\ref WDT_MODULE     |\ref CLK_CLKSEL1_WDTSEL_HCLK_DIV2048   | x                        |
  * |\ref WDT_MODULE     |\ref CLK_CLKSEL1_WDTSEL_LIRC           | x                        |
  * |\ref WWDT_MODULE    |\ref CLK_CLKSEL1_WWDTSEL_HCLK_DIV2048  | x                        |
  * |\ref WWDT_MODULE    |\ref CLK_CLKSEL1_WWDTSEL_LIRC          | x                        |
  * |\ref LCD_MODULE     |\ref CLK_CLKSEL1_LCDSEL_LIRC           | x                        |
  * |\ref LCD_MODULE     |\ref CLK_CLKSEL1_LCDSEL_LXT            | x                        |
  * |\ref LCDCP_MODULE   |\ref CLK_CLKSEL1_LCDCPSEL_MIRC1P2M     | x                        |
  * |\ref LCDCP_MODULE   |\ref CLK_CLKSEL1_LCDCPSEL_MIRC         | x                        |
  * |\ref EWDT_MODULE    |\ref CLK_CLKSEL1_EWDTSEL_LXT           | x                        |
  * |\ref EWDT_MODULE    |\ref CLK_CLKSEL1_EWDTSEL_HCLK_DIV2048  | x                        |
  * |\ref EWDT_MODULE    |\ref CLK_CLKSEL1_EWDTSEL_LIRC          | x                        |
  * |\ref EWWDT_MODULE   |\ref CLK_CLKSEL1_EWWDTSEL_HCLK_DIV2048 | x                        |
  * |\ref EWWDT_MODULE   |\ref CLK_CLKSEL1_EWWDTSEL_LIRC         | x                        |
  * |\ref EADC_MODULE    | x                                     |\ref CLK_CLKDIV0_EADC(x)  |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_HXT           | x                        |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_LXT           | x                        |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_PCLK0         | x                        |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_EXT_TRG       | x                        |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_LIRC          | x                        |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_HIRC          | x                        |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_HXT           | x                        |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_LXT           | x                        |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_PCLK0         | x                        |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_EXT_TRG       | x                        |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_LIRC          | x                        |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_HIRC          | x                        |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_HXT           | x                        |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_LXT           | x                        |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_PCLK1         | x                        |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_EXT_TRG       | x                        |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_LIRC          | x                        |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_HIRC          | x                        |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_HXT           | x                        |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_LXT           | x                        |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_PCLK1         | x                        |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_EXT_TRG       | x                        |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_LIRC          | x                        |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_HIRC          | x                        |
  * |\ref TMR4_MODULE    |\ref CLK_CLKSEL3_TMR4SEL_HXT           | x                        |
  * |\ref TMR4_MODULE    |\ref CLK_CLKSEL3_TMR4SEL_LXT           | x                        |
  * |\ref TMR4_MODULE    |\ref CLK_CLKSEL3_TMR4SEL_PCLK0         | x                        |
  * |\ref TMR4_MODULE    |\ref CLK_CLKSEL3_TMR4SEL_EXT_TRG       | x                        |
  * |\ref TMR4_MODULE    |\ref CLK_CLKSEL3_TMR4SEL_MIRC          | x                        |
  * |\ref TMR4_MODULE    |\ref CLK_CLKSEL3_TMR4SEL_LIRC          | x                        |
  * |\ref TMR4_MODULE    |\ref CLK_CLKSEL3_TMR4SEL_HIRC          | x                        |
  * |\ref TMR5_MODULE    |\ref CLK_CLKSEL3_TMR5SEL_HXT           | x                        |
  * |\ref TMR5_MODULE    |\ref CLK_CLKSEL3_TMR5SEL_LXT           | x                        |
  * |\ref TMR5_MODULE    |\ref CLK_CLKSEL3_TMR5SEL_PCLK0         | x                        |
  * |\ref TMR5_MODULE    |\ref CLK_CLKSEL3_TMR5SEL_EXT_TRG       | x                        |
  * |\ref TMR5_MODULE    |\ref CLK_CLKSEL3_TMR5SEL_MIRC          | x                        |
  * |\ref TMR5_MODULE    |\ref CLK_CLKSEL3_TMR5SEL_LIRC          | x                        |
  * |\ref TMR5_MODULE    |\ref CLK_CLKSEL3_TMR5SEL_HIRC          | x                        |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL2_UART0SEL_HXT          |\ref CLK_CLKDIV0_UART0(x) |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL2_UART0SEL_PLL          |\ref CLK_CLKDIV0_UART0(x) |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL2_UART0SEL_LXT          |\ref CLK_CLKDIV0_UART0(x) |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL2_UART0SEL_HIRC         |\ref CLK_CLKDIV0_UART0(x) |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL2_UART0SEL_PCLK0        |\ref CLK_CLKDIV0_UART0(x) |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL2_UART1SEL_HXT          |\ref CLK_CLKDIV0_UART1(x) |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL2_UART1SEL_PLL          |\ref CLK_CLKDIV0_UART1(x) |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL2_UART1SEL_LXT          |\ref CLK_CLKDIV0_UART1(x) |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL2_UART1SEL_HIRC         |\ref CLK_CLKDIV0_UART1(x) |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL2_UART1SEL_PCLK1        |\ref CLK_CLKDIV0_UART1(x) |
  * |\ref UART2_MODULE   |\ref CLK_CLKSEL2_UART2SEL_HXT          |\ref CLK_CLKDIV4_UART2(x) |
  * |\ref UART2_MODULE   |\ref CLK_CLKSEL2_UART2SEL_PLL          |\ref CLK_CLKDIV4_UART2(x) |
  * |\ref UART2_MODULE   |\ref CLK_CLKSEL2_UART2SEL_LXT          |\ref CLK_CLKDIV4_UART2(x) |
  * |\ref UART2_MODULE   |\ref CLK_CLKSEL2_UART2SEL_HIRC         |\ref CLK_CLKDIV4_UART2(x) |
  * |\ref UART2_MODULE   |\ref CLK_CLKSEL2_UART2SEL_PCLK0        |\ref CLK_CLKDIV4_UART2(x) |
  * |\ref UART3_MODULE   |\ref CLK_CLKSEL2_UART3SEL_HXT          |\ref CLK_CLKDIV4_UART3(x) |
  * |\ref UART3_MODULE   |\ref CLK_CLKSEL2_UART3SEL_PLL          |\ref CLK_CLKDIV4_UART3(x) |
  * |\ref UART3_MODULE   |\ref CLK_CLKSEL2_UART3SEL_LXT          |\ref CLK_CLKDIV4_UART3(x) |
  * |\ref UART3_MODULE   |\ref CLK_CLKSEL2_UART3SEL_HIRC         |\ref CLK_CLKDIV4_UART3(x) |
  * |\ref UART3_MODULE   |\ref CLK_CLKSEL2_UART3SEL_PCLK1        |\ref CLK_CLKDIV4_UART3(x) |
  * |\ref UART4_MODULE   |\ref CLK_CLKSEL3_UART4SEL_HXT          |\ref CLK_CLKDIV4_UART4(x) |
  * |\ref UART4_MODULE   |\ref CLK_CLKSEL3_UART4SEL_PLL          |\ref CLK_CLKDIV4_UART4(x) |
  * |\ref UART4_MODULE   |\ref CLK_CLKSEL3_UART4SEL_LXT          |\ref CLK_CLKDIV4_UART4(x) |
  * |\ref UART4_MODULE   |\ref CLK_CLKSEL3_UART4SEL_HIRC         |\ref CLK_CLKDIV4_UART4(x) |
  * |\ref UART4_MODULE   |\ref CLK_CLKSEL3_UART4SEL_PCLK0        |\ref CLK_CLKDIV4_UART4(x) |
  * |\ref UART5_MODULE   |\ref CLK_CLKSEL3_UART5SEL_HXT          |\ref CLK_CLKDIV4_UART5(x) |
  * |\ref UART5_MODULE   |\ref CLK_CLKSEL3_UART5SEL_PLL          |\ref CLK_CLKDIV4_UART5(x) |
  * |\ref UART5_MODULE   |\ref CLK_CLKSEL3_UART5SEL_LXT          |\ref CLK_CLKDIV4_UART5(x) |
  * |\ref UART5_MODULE   |\ref CLK_CLKSEL3_UART5SEL_HIRC         |\ref CLK_CLKDIV4_UART5(x) |
  * |\ref UART5_MODULE   |\ref CLK_CLKSEL3_UART5SEL_PCLK1        |\ref CLK_CLKDIV4_UART5(x) |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_HXT           | x                        |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_LXT           | x                        |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_HCLK          | x                        |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_HIRC          | x                        |
  * |\ref RTC_MODULE     |\ref RTC_LXTCTL_RTCCKSEL_LXT           | x                        |
  * |\ref RTC_MODULE     |\ref RTC_LXTCTL_RTCCKSEL_LIRC          | x                        |
  * |\ref I2S0_MODULE    |\ref CLK_CLKSEL3_I2S0SEL_HXT           | x                        |
  * |\ref I2S0_MODULE    |\ref CLK_CLKSEL3_I2S0SEL_PLL           | x                        |
  * |\ref I2S0_MODULE    |\ref CLK_CLKSEL3_I2S0SEL_PCLK0         | x                        |
  * |\ref I2S0_MODULE    |\ref CLK_CLKSEL3_I2S0SEL_HIRC          | x                        |
  * |\ref QSPI0_MODULE   |\ref CLK_CLKSEL2_QSPI0SEL_HXT          | x                        |
  * |\ref QSPI0_MODULE   |\ref CLK_CLKSEL2_QSPI0SEL_PLL          | x                        |
  * |\ref QSPI0_MODULE   |\ref CLK_CLKSEL2_QSPI0SEL_PCLK0        | x                        |
  * |\ref QSPI0_MODULE   |\ref CLK_CLKSEL2_QSPI0SEL_HIRC         | x                        |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL2_SPI0SEL_HXT           | x                        |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL2_SPI0SEL_PLL           | x                        |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL2_SPI0SEL_PCLK1         | x                        |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL2_SPI0SEL_HIRC          | x                        |
  * |\ref SPI1_MODULE    |\ref CLK_CLKSEL2_SPI1SEL_HXT           | x                        |
  * |\ref SPI1_MODULE    |\ref CLK_CLKSEL2_SPI1SEL_PLL           | x                        |
  * |\ref SPI1_MODULE    |\ref CLK_CLKSEL2_SPI1SEL_PCLK0         | x                        |
  * |\ref SPI1_MODULE    |\ref CLK_CLKSEL2_SPI1SEL_HIRC          | x                        |
  * |\ref SPI2_MODULE    |\ref CLK_CLKSEL2_SPI2SEL_HXT           | x                        |
  * |\ref SPI2_MODULE    |\ref CLK_CLKSEL2_SPI2SEL_PLL           | x                        |
  * |\ref SPI2_MODULE    |\ref CLK_CLKSEL2_SPI2SEL_PCLK1         | x                        |
  * |\ref SPI2_MODULE    |\ref CLK_CLKSEL2_SPI2SEL_HIRC          | x                        |
  * |\ref SPI3_MODULE    |\ref CLK_CLKSEL2_SPI3SEL_HXT           | x                        |
  * |\ref SPI3_MODULE    |\ref CLK_CLKSEL2_SPI3SEL_PLL           | x                        |
  * |\ref SPI3_MODULE    |\ref CLK_CLKSEL2_SPI3SEL_PCLK0         | x                        |
  * |\ref SPI3_MODULE    |\ref CLK_CLKSEL2_SPI3SEL_HIRC          | x                        |
  * |\ref SC0_MODULE     |\ref CLK_CLKSEL3_SC0SEL_HXT            |\ref CLK_CLKDIV1_SC0(x)   |
  * |\ref SC0_MODULE     |\ref CLK_CLKSEL3_SC0SEL_PLL            |\ref CLK_CLKDIV1_SC0(x)   |
  * |\ref SC0_MODULE     |\ref CLK_CLKSEL3_SC0SEL_PCLK0          |\ref CLK_CLKDIV1_SC0(x)   |
  * |\ref SC0_MODULE     |\ref CLK_CLKSEL3_SC0SEL_HIRC           |\ref CLK_CLKDIV1_SC0(x)   |
  * |\ref SC1_MODULE     |\ref CLK_CLKSEL3_SC1SEL_HXT            |\ref CLK_CLKDIV1_SC1(x)   |
  * |\ref SC1_MODULE     |\ref CLK_CLKSEL3_SC1SEL_PLL            |\ref CLK_CLKDIV1_SC1(x)   |
  * |\ref SC1_MODULE     |\ref CLK_CLKSEL3_SC1SEL_PCLK1          |\ref CLK_CLKDIV1_SC1(x)   |
  * |\ref SC1_MODULE     |\ref CLK_CLKSEL3_SC1SEL_HIRC           |\ref CLK_CLKDIV1_SC1(x)   |
  * |\ref SC2_MODULE     |\ref CLK_CLKSEL3_SC2SEL_HXT            |\ref CLK_CLKDIV1_SC2(x)   |
  * |\ref SC2_MODULE     |\ref CLK_CLKSEL3_SC2SEL_PLL            |\ref CLK_CLKDIV1_SC2(x)   |
  * |\ref SC2_MODULE     |\ref CLK_CLKSEL3_SC2SEL_PCLK0          |\ref CLK_CLKDIV1_SC2(x)   |
  * |\ref SC2_MODULE     |\ref CLK_CLKSEL3_SC2SEL_HIRC           |\ref CLK_CLKDIV1_SC2(x)   |
  * |\ref USBH_MODULE    |\ref CLK_CLKSEL0_USBSEL_HIRC48         |\ref CLK_CLKDIV0_USB(x)   |
  * |\ref USBH_MODULE    |\ref CLK_CLKSEL0_USBSEL_PLL            |\ref CLK_CLKDIV0_USB(x)   |
  * |\ref OTG_MODULE     |\ref CLK_CLKSEL0_USBSEL_HIRC48         |\ref CLK_CLKDIV0_USB(x)   |
  * |\ref OTG_MODULE     |\ref CLK_CLKSEL0_USBSEL_PLL            |\ref CLK_CLKDIV0_USB(x)   |
  * |\ref USBD_MODULE    |\ref CLK_CLKSEL0_USBSEL_HIRC48         |\ref CLK_CLKDIV0_USB(x)   |
  * |\ref USBD_MODULE    |\ref CLK_CLKSEL0_USBSEL_PLL            |\ref CLK_CLKDIV0_USB(x)   |
  */
void CLK_SetModuleClock(uint32_t u32ModuleIdx, uint32_t u32ClkSrc, uint32_t u32ClkDiv)
{
    uint32_t u32Sel = 0UL, u32Div = 0UL;
    uint32_t au32SelTbl[4] = {0x0UL, 0x4UL, 0x8UL, 0xCUL};
    uint32_t au32DivTbl[4] = {0x0UL, 0x4UL, 0x8UL, 0x10UL};
    uint32_t u32RTCCKEN = CLK->APBCLK0 & CLK_APBCLK0_RTCCKEN_Msk;

    if(u32ModuleIdx == RTC_MODULE)      /* RTC clock source configuration */
    {
        if(u32RTCCKEN == 0UL)
        {
            CLK->APBCLK0 |= CLK_APBCLK0_RTCCKEN_Msk; /* Enable RTC clock to get LXT clock source */
        }

        /* Select RTC clock source */
        RTC->LXTCTL = (RTC->LXTCTL & (~RTC_LXTCTL_RTCCKSEL_Msk)) | (u32ClkSrc);

        if(u32RTCCKEN == 0UL)
        {
            CLK->APBCLK0 &= (~CLK_APBCLK0_RTCCKEN_Msk); /* Disable RTC clock if it is disabled before */
        }

    }
    else /* Others clock source configuration */
    {
        if(MODULE_CLKDIV_Msk(u32ModuleIdx) != MODULE_NoMsk)
        {
            /* Get clock divider control register address */
            u32Div = (uint32_t)&CLK->CLKDIV0 + (au32DivTbl[MODULE_CLKDIV(u32ModuleIdx)]);
            /* Apply new divider */
            M32(u32Div) = (M32(u32Div) & (~(MODULE_CLKDIV_Msk(u32ModuleIdx) << MODULE_CLKDIV_Pos(u32ModuleIdx)))) | u32ClkDiv;
        }

        if(MODULE_CLKSEL_Msk(u32ModuleIdx) != MODULE_NoMsk)
        {
            /* Get clock select control register address */
            u32Sel = (uint32_t)&CLK->CLKSEL0 + (au32SelTbl[MODULE_CLKSEL(u32ModuleIdx)]);
            /* Set new clock selection setting */
            M32(u32Sel) = (M32(u32Sel) & (~(MODULE_CLKSEL_Msk(u32ModuleIdx) << MODULE_CLKSEL_Pos(u32ModuleIdx)))) | u32ClkSrc;
        }
    }
}

/**
  * @brief      Set SysTick clock source
  * @param[in]  u32ClkSrc is module clock source. Including:
  *             - \ref CLK_CLKSEL0_STCLKSEL_HXT
  *             - \ref CLK_CLKSEL0_STCLKSEL_LXT
  *             - \ref CLK_CLKSEL0_STCLKSEL_HXT_DIV2
  *             - \ref CLK_CLKSEL0_STCLKSEL_HCLK_DIV2
  *             - \ref CLK_CLKSEL0_STCLKSEL_HIRC_DIV2
  * @return     None
  * @details    This function set SysTick clock source. \n
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_SetSysTickClockSrc(uint32_t u32ClkSrc)
{
    CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_STCLKSEL_Msk) | u32ClkSrc;
}

/**
  * @brief      Enable clock source
  * @param[in]  u32ClkMask is clock source mask. Including :
  *             - \ref CLK_PWRCTL_HXTEN_Msk
  *             - \ref CLK_PWRCTL_LXTEN_Msk
  *             - \ref CLK_PWRCTL_HIRCEN_Msk
  *             - \ref CLK_PWRCTL_LIRCEN_Msk
  *             - \ref CLK_PWRCTL_HIRC48EN_Msk
  *             - \ref CLK_PWRCTL_MIRC1P2MEN_Msk
  *             - \ref CLK_PWRCTL_MIRCEN_Msk
  * @return     None
  * @details    This function enable clock source. \n
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_EnableXtalRC(uint32_t u32ClkMask)
{
    CLK->PWRCTL |= u32ClkMask;
}

/**
  * @brief      Disable clock source
  * @param[in]  u32ClkMask is clock source mask. Including :
  *             - \ref CLK_PWRCTL_HXTEN_Msk
  *             - \ref CLK_PWRCTL_LXTEN_Msk
  *             - \ref CLK_PWRCTL_HIRCEN_Msk
  *             - \ref CLK_PWRCTL_LIRCEN_Msk
  *             - \ref CLK_PWRCTL_HIRC48EN_Msk
  *             - \ref CLK_PWRCTL_MIRC1P2MEN_Msk
  *             - \ref CLK_PWRCTL_MIRCEN_Msk
  * @return     None
  * @details    This function disable clock source. \n
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_DisableXtalRC(uint32_t u32ClkMask)
{
    CLK->PWRCTL &= ~u32ClkMask;
}

/**
  * @brief      Enable module clock
  * @param[in]  u32ModuleIdx is module index. Including :
  *             - \ref PDMA0_MODULE
  *             - \ref PDMA1_MODULE
  *             - \ref ISP_MODULE
  *             - \ref EBI_MODULE
  *             - \ref SDH0_MODULE
  *             - \ref CRC_MODULE
  *             - \ref CRPT_MODULE
  *             - \ref KS_MODULE
  *             - \ref TRACE_MODULE
  *             - \ref USBH_MODULE
  *             - \ref SRAM0_MODULE
  *             - \ref SRAM1_MODULE
  *             - \ref SRAM2_MODULE
  *             - \ref GPA_MODULE
  *             - \ref GPB_MODULE
  *             - \ref GPC_MODULE
  *             - \ref GPD_MODULE
  *             - \ref GPE_MODULE
  *             - \ref GPF_MODULE
  *             - \ref GPG_MODULE
  *             - \ref GPH_MODULE
  *             - \ref WDT_MODULE
  *             - \ref WWDT_MODULE
  *             - \ref EWDT_MODULE
  *             - \ref EWWDT_MODULE
  *             - \ref RTC_MODULE
  *             - \ref TMR0_MODULE
  *             - \ref TMR1_MODULE
  *             - \ref TMR2_MODULE
  *             - \ref TMR3_MODULE
  *             - \ref TMR4_MODULE
  *             - \ref TMR5_MODULE
  *             - \ref CLKO_MODULE
  *             - \ref ACMP01_MODULE
  *             - \ref I2C0_MODULE
  *             - \ref I2C1_MODULE
  *             - \ref I2C2_MODULE
  *             - \ref QSPI0_MODULE
  *             - \ref SPI0_MODULE
  *             - \ref SPI1_MODULE
  *             - \ref SPI2_MODULE
  *             - \ref SPI3_MODULE
  *             - \ref UART0_MODULE
  *             - \ref UART1_MODULE
  *             - \ref UART2_MODULE
  *             - \ref UART3_MODULE
  *             - \ref UART4_MODULE
  *             - \ref UART5_MODULE
  *             - \ref TAMPER_MODULE
  *             - \ref CAN0_MODULE
  *             - \ref OTG_MODULE
  *             - \ref USBD_MODULE
  *             - \ref EADC_MODULE
  *             - \ref I2S0_MODULE
  *             - \ref SC0_MODULE
  *             - \ref SC1_MODULE
  *             - \ref SC2_MODULE
  *             - \ref USCI0_MODULE
  *             - \ref USCI1_MODULE
  *             - \ref DAC_MODULE
  *             - \ref EPWM0_MODULE
  *             - \ref EPWM1_MODULE
  *             - \ref BPWM0_MODULE
  *             - \ref BPWM1_MODULE
  *             - \ref QEI0_MODULE
  *             - \ref QEI1_MODULE
  *             - \ref QEI0_MODULE
  *             - \ref LCD_MODULE
  *             - \ref LCDCP_MODULE
  *             - \ref TRNG_MODULE
  *             - \ref ECAP0_MODULE
  *             - \ref ECAP1_MODULE
  * @return     None
  * @details    This function is used to enable module clock.
  */
void CLK_EnableModuleClock(uint32_t u32ModuleIdx)
{
    uint32_t u32TmpVal = 0UL, u32TmpAddr = 0UL;

    u32TmpVal = (1UL << MODULE_IP_EN_Pos(u32ModuleIdx));
    u32TmpAddr = (uint32_t)&CLK->AHBCLK;
    u32TmpAddr += ((MODULE_APBCLK(u32ModuleIdx) * 4UL));

    *(volatile uint32_t *)u32TmpAddr |= u32TmpVal;
}

/**
  * @brief      Disable module clock
  * @param[in]  u32ModuleIdx is module index
  *             - \ref PDMA0_MODULE
  *             - \ref PDMA1_MODULE
  *             - \ref ISP_MODULE
  *             - \ref EBI_MODULE
  *             - \ref SDH0_MODULE
  *             - \ref CRC_MODULE
  *             - \ref CRPT_MODULE
  *             - \ref KS_MODULE
  *             - \ref TRACE_MODULE
  *             - \ref USBH_MODULE
  *             - \ref SRAM0_MODULE
  *             - \ref SRAM1_MODULE
  *             - \ref SRAM2_MODULE
  *             - \ref GPA_MODULE
  *             - \ref GPB_MODULE
  *             - \ref GPC_MODULE
  *             - \ref GPD_MODULE
  *             - \ref GPE_MODULE
  *             - \ref GPF_MODULE
  *             - \ref GPG_MODULE
  *             - \ref GPH_MODULE
  *             - \ref WDT_MODULE
  *             - \ref WWDT_MODULE
  *             - \ref EWDT_MODULE
  *             - \ref EWWDT_MODULE
  *             - \ref RTC_MODULE
  *             - \ref TMR0_MODULE
  *             - \ref TMR1_MODULE
  *             - \ref TMR2_MODULE
  *             - \ref TMR3_MODULE
  *             - \ref TMR4_MODULE
  *             - \ref TMR5_MODULE
  *             - \ref CLKO_MODULE
  *             - \ref ACMP01_MODULE
  *             - \ref I2C0_MODULE
  *             - \ref I2C1_MODULE
  *             - \ref I2C2_MODULE
  *             - \ref QSPI0_MODULE
  *             - \ref SPI0_MODULE
  *             - \ref SPI1_MODULE
  *             - \ref SPI2_MODULE
  *             - \ref SPI3_MODULE
  *             - \ref UART0_MODULE
  *             - \ref UART1_MODULE
  *             - \ref UART2_MODULE
  *             - \ref UART3_MODULE
  *             - \ref UART4_MODULE
  *             - \ref UART5_MODULE
  *             - \ref TAMPER_MODULE
  *             - \ref CAN0_MODULE
  *             - \ref OTG_MODULE
  *             - \ref USBD_MODULE
  *             - \ref EADC_MODULE
  *             - \ref I2S0_MODULE
  *             - \ref SC0_MODULE
  *             - \ref SC1_MODULE
  *             - \ref SC2_MODULE
  *             - \ref USCI0_MODULE
  *             - \ref USCI1_MODULE
  *             - \ref DAC_MODULE
  *             - \ref EPWM0_MODULE
  *             - \ref EPWM1_MODULE
  *             - \ref BPWM0_MODULE
  *             - \ref BPWM1_MODULE
  *             - \ref QEI0_MODULE
  *             - \ref QEI1_MODULE
  *             - \ref QEI0_MODULE
  *             - \ref LCD_MODULE
  *             - \ref LCDCP_MODULE
  *             - \ref TRNG_MODULE
  *             - \ref ECAP0_MODULE
  *             - \ref ECAP1_MODULE
  * @return     None
  * @details    This function is used to disable module clock.
  */
void CLK_DisableModuleClock(uint32_t u32ModuleIdx)
{
    uint32_t u32TmpVal = 0UL, u32TmpAddr = 0UL;

    u32TmpVal = ~(1UL << MODULE_IP_EN_Pos(u32ModuleIdx));
    u32TmpAddr = (uint32_t)&CLK->AHBCLK;
    u32TmpAddr += ((MODULE_APBCLK(u32ModuleIdx) * 4UL));

    *(uint32_t *)u32TmpAddr &= u32TmpVal;
}


/**
  * @brief      Set PLL frequency
  * @param[in]  u32PllClkSrc is PLL clock source. Including :
  *             - \ref CLK_PLLCTL_PLLSRC_HXT
  *             - \ref CLK_PLLCTL_PLLSRC_HIRC
  * @param[in]  u32PllFreq is PLL frequency. The range of u32PllFreq is 24 MHz ~ 200 MHz.
  * @return     PLL frequency
  * @details    This function is used to configure PLLCTL register to set specified PLL frequency. \n
  *             The register write-protection function should be disabled before using this function.
  */
uint32_t CLK_EnablePLL(uint32_t u32PllClkSrc, uint32_t u32PllFreq)
{
    uint32_t u32PllSrcClk, u32NR, u32NF, u32NO, u32PllClk;
    uint32_t u32Tmp, u32Tmp2, u32Tmp3, u32Min, u32MinNF, u32MinNR;

    /* Disable PLL first to avoid unstable when setting PLL */
    CLK->PLLCTL |= CLK_PLLCTL_PD_Msk;

    /* PLL source clock is from HXT */
    if(u32PllClkSrc == CLK_PLLCTL_PLLSRC_HXT)
    {
        /* Enable HXT clock */
        CLK->PWRCTL |= CLK_PWRCTL_HXTEN_Msk;

        /* Wait for HXT clock ready */
        CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

        /* Select PLL source clock from HXT */
        u32PllSrcClk = __HXT;
    }

    /* PLL source clock is from HIRC */
    else
    {
        /* Enable HIRC clock */
        CLK->PWRCTL |= CLK_PWRCTL_HIRCEN_Msk;

        /* Wait for HIRC clock ready */
        CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

        /* Select PLL source clock from HIRC */
        u32PllSrcClk = __HIRC;
    }

    /* Check PLL frequency range */
    /* Constraint 1: 24MHz < FOUT < 200MHz */
    if((u32PllFreq <= FREQ_200MHZ) && (u32PllFreq >= FREQ_24MHZ))
    {

        /* Select "NO" according to request frequency */
        if((u32PllFreq < FREQ_48MHZ) && (u32PllFreq >= FREQ_24MHZ))
        {
            u32NO = 3UL;
            u32PllFreq = u32PllFreq << 2;
        }
        else if((u32PllFreq < FREQ_96MHZ) && (u32PllFreq >= FREQ_48MHZ))
        {
            u32NO = 1UL;
            u32PllFreq = u32PllFreq << 1;
        }
        else
        {
            u32NO = 0UL;
        }

        /* u32NR start from 3 to avoid calculation overflow */
        u32NR = 3UL;

        /* Find best solution */
        u32Min = (uint32_t) - 1;    /* initial u32Min to max value of uint32_t (0xFFFFFFFF) */
        u32MinNR = 0UL;
        u32MinNF = 0UL;

        for(; u32NR <= 32UL; u32NR++)   /* max NR = 32 since NR = INDIV+1 and INDIV = 0~31 */
        {
            u32Tmp = u32PllSrcClk / u32NR;                      /* FREF = FIN/NR */
            if((u32Tmp >= FREQ_2MHZ) && (u32Tmp <= FREQ_8MHZ))  /* Constraint 2: 2MHz < FREF < 8MHz. */
            {
                for(u32NF = 2UL; u32NF <= 513UL; u32NF++)       /* NF = 2~513 since NF = FBDIV+2 and FBDIV = 0~511 */
                {
                    u32Tmp2 = (u32Tmp * u32NF) << 1;                            /* FVCO = FREF*2*NF */
                    if((u32Tmp2 >= FREQ_96MHZ) && (u32Tmp2 <= FREQ_200MHZ))     /* Constraint 3: 96MHz < FVCO < 200MHz */
                    {
                        u32Tmp3 = (u32Tmp2 > u32PllFreq) ? u32Tmp2 - u32PllFreq : u32PllFreq - u32Tmp2;
                        if(u32Tmp3 < u32Min)
                        {
                            u32Min = u32Tmp3;
                            u32MinNR = u32NR;
                            u32MinNF = u32NF;

                            /* Break when get good results */
                            if(u32Min == 0UL)
                            {
                                break;
                            }
                        }
                    }
                }
            }
        }

        /* Enable and apply new PLL setting. */
        CLK->PLLCTL = u32PllClkSrc |
                      (u32NO << CLK_PLLCTL_OUTDIV_Pos) |
                      ((u32MinNR - 1UL) << CLK_PLLCTL_INDIV_Pos) |
                      ((u32MinNF - 2UL) << CLK_PLLCTL_FBDIV_Pos);

        /* Actual PLL output clock frequency. FOUT = (FIN/NR)*2*NF*(1/NO) */
        u32PllClk = u32PllSrcClk / ((u32NO + 1UL) * u32MinNR) * (u32MinNF << 1);

    }
    else
    {
        /* Apply default PLL setting and return */
        CLK->PLLCTL = u32PllClkSrc | CLK_PLLCTL_48MHz_HXT;

        /* Actual PLL output clock frequency */
        u32PllClk = FREQ_48MHZ;
    }

    /* Wait for PLL clock stable */
    CLK_WaitClockReady(CLK_STATUS_PLLSTB_Msk);

    /* Return actual PLL output clock frequency */
    return u32PllClk;
}

/**
  * @brief      Disable PLL
  * @param      None
  * @return     None
  * @details    This function set PLL in Power-down mode. \n
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_DisablePLL(void)
{
    CLK->PLLCTL |= CLK_PLLCTL_PD_Msk;
}

/**
  * @brief      This function check selected clock source status
  * @param[in]  u32ClkMask is selected clock source. Including :
  *             - \ref CLK_STATUS_HXTSTB_Msk
  *             - \ref CLK_STATUS_LXTSTB_Msk
  *             - \ref CLK_STATUS_HIRCSTB_Msk
  *             - \ref CLK_STATUS_LIRCSTB_Msk
  *             - \ref CLK_STATUS_PLLSTB_Msk
  *             - \ref CLK_STATUS_HIRC48STB_Msk
  *             - \ref CLK_STATUS_EXTLXTSTB_Msk
  *             - \ref CLK_STATUS_LIRC32STB_Msk
  *             - \ref CLK_STATUS_MIRCSTB_Msk
  * @retval     0  clock is not stable
  * @retval     1  clock is stable
  * @details    To wait for clock ready by specified clock source stable flag or timeout (~500ms)
  */
uint32_t CLK_WaitClockReady(uint32_t u32ClkMask)
{
    int32_t i32TimeOutCnt = 2400000;
    uint32_t u32Ret = 1U;

    while((CLK->STATUS & u32ClkMask) != u32ClkMask)
    {
        if(i32TimeOutCnt-- <= 0)
        {
            u32Ret = 0U;
            break;
        }
    }
    return u32Ret;
}

/**
  * @brief      Enable System Tick counter
  * @param[in]  u32ClkSrc is System Tick clock source. Including:
  *             - \ref CLK_CLKSEL0_STCLKSEL_HXT
  *             - \ref CLK_CLKSEL0_STCLKSEL_LXT
  *             - \ref CLK_CLKSEL0_STCLKSEL_HXT_DIV2
  *             - \ref CLK_CLKSEL0_STCLKSEL_HCLK_DIV2
  *             - \ref CLK_CLKSEL0_STCLKSEL_HIRC_DIV2
  *             - \ref CLK_CLKSEL0_STCLKSEL_HCLK
  * @param[in]  u32Count is System Tick reload value. It could be 0~0xFFFFFF.
  * @return     None
  * @details    This function set System Tick clock source, reload value, enable System Tick counter and interrupt. \n
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_EnableSysTick(uint32_t u32ClkSrc, uint32_t u32Count)
{
    /* Set System Tick counter disabled */
    SysTick->CTRL = 0UL;

    /* Set System Tick clock source */
    if(u32ClkSrc == CLK_CLKSEL0_STCLKSEL_HCLK)
    {
        SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
    }
    else
    {
        CLK->AHBCLK |= CLK_AHBCLK_EXSTCKEN_Msk;
        CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_STCLKSEL_Msk) | u32ClkSrc;
    }

    /* Set System Tick reload value */
    SysTick->LOAD = u32Count;

    /* Clear System Tick current value and counter flag */
    SysTick->VAL = 0UL;

    /* Set System Tick interrupt enabled and counter enabled */
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

/**
  * @brief      Disable System Tick counter
  * @param      None
  * @return     None
  * @details    This function disable System Tick counter.
  */
void CLK_DisableSysTick(void)
{
    /* Set System Tick counter disabled */
    SysTick->CTRL = 0UL;
}

/**
  * @brief      Power-down mode selected
  * @param[in]  u32PDMode is power down mode index. Including :
  *             - \ref CLK_PMUCTL_PDMSEL_PD
  *             - \ref CLK_PMUCTL_PDMSEL_LLPD
  *             - \ref CLK_PMUCTL_PDMSEL_FWPD
  *             - \ref CLK_PMUCTL_PDMSEL_ULLPD
  *             - \ref CLK_PMUCTL_PDMSEL_SPD
  *             - \ref CLK_PMUCTL_PDMSEL_DPD
  * @return     None
  * @details    This function is used to set power-down mode.
  */
void CLK_SetPowerDownMode(uint32_t u32PDMode)
{
    while(CLK->PMUCTL & CLK_PMUCTL_WRBUSY_Msk);
    CLK->PMUCTL = (CLK->PMUCTL & (~CLK_PMUCTL_PDMSEL_Msk)) | (u32PDMode);
}

/**
 * @brief       Set Wake-up pin trigger type at Deep Power down mode
 * @param[in]   u32TriggerType Wake-up pin trigger type
 *              - \ref CLK_DPDWKPIN_RISING
 *              - \ref CLK_DPDWKPIN_FALLING
 *              - \ref CLK_DPDWKPIN_BOTHEDGE
 *              - \ref CLK_DPDWKPIN1_RISING
 *              - \ref CLK_DPDWKPIN1_FALLING
 *              - \ref CLK_DPDWKPIN1_BOTHEDGE
 *              - \ref CLK_DPDWKPIN2_RISING
 *              - \ref CLK_DPDWKPIN2_FALLING
 *              - \ref CLK_DPDWKPIN2_BOTHEDGE
 *              - \ref CLK_DPDWKPIN3_RISING
 *              - \ref CLK_DPDWKPIN3_FALLING
 *              - \ref CLK_DPDWKPIN3_BOTHEDGE
 *              - \ref CLK_DPDWKPIN4_RISING
 *              - \ref CLK_DPDWKPIN4_FALLING
 *              - \ref CLK_DPDWKPIN4_BOTHEDGE
 * @return      None
 * @details     This function is used to enable Wake-up pin trigger type.
 */

void CLK_EnableDPDWKPin(uint32_t u32TriggerType)
{
    uint32_t u32Pin1, u32Pin2, u32Pin3, u32Pin4;

    u32Pin1 = (((u32TriggerType) & 0x03UL) >> CLK_PMUCTL_WKPINEN1_Pos);
    u32Pin2 = (((u32TriggerType) & 0x03UL) >> CLK_PMUCTL_WKPINEN2_Pos);
    u32Pin3 = (((u32TriggerType) & 0x03UL) >> CLK_PMUCTL_WKPINEN3_Pos);
    u32Pin4 = (((u32TriggerType) & 0x03UL) >> CLK_PMUCTL_WKPINEN4_Pos);

    while(CLK->PMUCTL & CLK_PMUCTL_WRBUSY_Msk);

    if(u32Pin1)
    {
        CLK->PMUCTL = (CLK->PMUCTL & ~(CLK_PMUCTL_WKPINEN1_Msk)) | u32TriggerType;
    }
    else if(u32Pin2)
    {
        CLK->PMUCTL = (CLK->PMUCTL & ~(CLK_PMUCTL_WKPINEN2_Msk)) | u32TriggerType;
    }
    else if(u32Pin3)
    {
        CLK->PMUCTL = (CLK->PMUCTL & ~(CLK_PMUCTL_WKPINEN3_Msk)) | u32TriggerType;
    }
    else if(u32Pin4)
    {
        CLK->PMUCTL = (CLK->PMUCTL & ~(CLK_PMUCTL_WKPINEN4_Msk)) | u32TriggerType;
    }
    else
    {
        CLK->PMUCTL = (CLK->PMUCTL & ~(CLK_PMUCTL_WKPINEN_Msk)) | u32TriggerType;
    }
}

/**
 * @brief       Get power manager wake up source
 * @param[in]   None
 * @return      None
 * @details     This function get power manager wake up source.
 */

uint32_t CLK_GetPMUWKSrc(void)
{
    return (CLK->PMUSTS);
}

/**
 * @brief       Set specified GPIO as wake up source at Standby Power-down mode
 * @param[in]   u32Port GPIO port. It could be 0~3.
 * @param[in]   u32Pin  The pin of specified GPIO port. It could be 0 ~ 15.
 * @param[in]   u32TriggerType Wake-up pin trigger type
 *              - \ref CLK_SPDWKPIN_RISING
 *              - \ref CLK_SPDWKPIN_FALLING
 * @param[in]   u32DebounceEn Standby Power-down mode wake-up pin de-bounce function
 *              - \ref CLK_SPDWKPIN_DEBOUNCEEN
 *              - \ref CLK_SPDWKPIN_DEBOUNCEDIS
 * @return      None
 * @details     This function is used to set specified GPIO as wake up source at Standby Power-down mode.
 */

void CLK_EnableSPDWKPin(uint32_t u32Port, uint32_t u32Pin, uint32_t u32TriggerType, uint32_t u32DebounceEn)
{
    uint32_t u32TmpAddr = 0UL;
    uint32_t u32TmpVal = 0UL;

    /* GPx Stand-by Power-down Wake-up Pin Select */
    u32TmpAddr = (uint32_t)&CLK->PASWKCTL;
    u32TmpAddr += (0x4UL * u32Port);

    u32TmpVal = inpw((uint32_t *)u32TmpAddr);
    u32TmpVal = (u32TmpVal & ~(CLK_PASWKCTL_WKPSEL_Msk | CLK_PASWKCTL_PRWKEN_Msk | CLK_PASWKCTL_PFWKEN_Msk | CLK_PASWKCTL_DBEN_Msk | CLK_PASWKCTL_WKEN_Msk)) |
                (u32Pin << CLK_PASWKCTL_WKPSEL_Pos) | u32TriggerType | u32DebounceEn | CLK_SPDWKPIN_ENABLE;
    outpw((uint32_t *)u32TmpAddr, u32TmpVal);
}

/**
  * @brief      Get PLL clock frequency
  * @param      None
  * @return     PLL frequency
  * @details    This function get PLL frequency. The frequency unit is Hz.
  */

__NONSECURE_ENTRY_WEAK
uint32_t CLK_GetPLLClockFreq(void)
{
    uint32_t u32PllFreq = 0UL, u32PllReg;
    uint32_t u32FIN, u32NF, u32NR, u32NO;
    uint8_t au8NoTbl[4] = {1U, 2U, 2U, 4U};

    u32PllReg = CLK->PLLCTL;

    if(u32PllReg & CLK_PLLCTL_PD_Msk)
    {
        u32PllFreq = 0UL;       /* PLL is in power down mode or fix low */
    }
    else                        /* PLL is in normal mode */
    {
        /* PLL source clock */
        if(u32PllReg & CLK_PLLCTL_PLLSRC_Msk)
        {
            u32FIN = __HIRC;    /* PLL source clock from HIRC */
        }
        else
        {
            u32FIN = __HXT;     /* PLL source clock from HXT */
        }

        /* Calculate PLL frequency */
        if(u32PllReg & CLK_PLLCTL_BP_Msk)
        {
            u32PllFreq = u32FIN;  /* PLL is in bypass mode */
        }
        else
        {
            /* PLL is output enabled in normal work mode */
            u32NO = au8NoTbl[((u32PllReg & CLK_PLLCTL_OUTDIV_Msk) >> CLK_PLLCTL_OUTDIV_Pos)];
            u32NF = ((u32PllReg & CLK_PLLCTL_FBDIV_Msk) >> CLK_PLLCTL_FBDIV_Pos) + 2UL;
            u32NR = ((u32PllReg & CLK_PLLCTL_INDIV_Msk) >> CLK_PLLCTL_INDIV_Pos) + 1UL;

            /* u32FIN is shifted 2 bits to avoid overflow */
            u32PllFreq = (((u32FIN >> 2) * (u32NF << 1)) / (u32NR * u32NO) << 2);
        }
    }

    return u32PllFreq;
}

/**
  * @brief      Get selected module clock source
  * @param[in]  u32ModuleIdx is module index.
  *             - \ref SDH0_MODULE
  *             - \ref USBH_MODULE
  *             - \ref WDT_MODULE
  *             - \ref WWDT_MODULE
  *             - \ref EWDT_MODULE
  *             - \ref EWWDT_MODULE
  *             - \ref LCD_MODULE
  *             - \ref LCDCP_MODULE
  *             - \ref RTC_MODULE
  *             - \ref TMR0_MODULE
  *             - \ref TMR1_MODULE
  *             - \ref TMR2_MODULE
  *             - \ref TMR3_MODULE
  *             - \ref TMR4_MODULE
  *             - \ref TMR5_MODULE
  *             - \ref CLKO_MODULE
  *             - \ref QSPI0_MODULE
  *             - \ref SPI0_MODULE
  *             - \ref SPI1_MODULE
  *             - \ref SPI2_MODULE
  *             - \ref SPI3_MODULE
  *             - \ref UART0_MODULE
  *             - \ref UART1_MODULE
  *             - \ref UART2_MODULE
  *             - \ref UART3_MODULE
  *             - \ref UART4_MODULE
  *             - \ref UART5_MODULE
  *             - \ref OTG_MODULE
  *             - \ref USBD_MODULE
  *             - \ref I2S0_MODULE
  *             - \ref SC0_MODULE
  *             - \ref SC1_MODULE
  *             - \ref SC2_MODULE
  *             - \ref EPWM0_MODULE
  *             - \ref EPWM1_MODULE
  *             - \ref BPWM0_MODULE
  *             - \ref BPWM1_MODULE
  * @return     Selected module clock source setting
  * @details    This function get selected module clock source.
  */

__NONSECURE_ENTRY_WEAK
uint32_t CLK_GetModuleClockSource(uint32_t u32ModuleIdx)
{
    uint32_t u32TmpVal = 0UL, u32TmpAddr = 0UL;
    uint32_t au32SelTbl[4] = {0x0UL, 0x4UL, 0x8UL, 0xCUL};
    uint32_t u32RTCCKEN = CLK->APBCLK0 & CLK_APBCLK0_RTCCKEN_Msk;

    /* Get clock source selection setting */
    if(u32ModuleIdx == RTC_MODULE)
    {
        if(u32RTCCKEN == 0UL)
        {
            CLK->APBCLK0 |= CLK_APBCLK0_RTCCKEN_Msk; /* Enable RTC clock to get LXT clock source */
        }

        u32TmpVal = ((RTC->LXTCTL & RTC_LXTCTL_RTCCKSEL_Msk) >> RTC_LXTCTL_RTCCKSEL_Pos);

        if(u32RTCCKEN == 0UL)
        {
            CLK->APBCLK0 &= (~CLK_APBCLK0_RTCCKEN_Msk); /* Disable RTC clock if it is disabled before */
        }

    }
    else if(u32ModuleIdx == EPWM0_MODULE)
    {
        u32TmpVal = ((CLK->CLKSEL2 & CLK_CLKSEL2_EPWM0SEL_Msk) >> CLK_CLKSEL2_EPWM0SEL_Pos);
    }
    else if(u32ModuleIdx == EPWM1_MODULE)
    {
        u32TmpVal = ((CLK->CLKSEL2 & CLK_CLKSEL2_EPWM1SEL_Msk) >> CLK_CLKSEL2_EPWM1SEL_Pos);
    }
    else if(u32ModuleIdx == BPWM0_MODULE)
    {
        u32TmpVal = ((CLK->CLKSEL2 & CLK_CLKSEL2_BPWM0SEL_Msk) >> CLK_CLKSEL2_BPWM0SEL_Pos);
    }
    else if(u32ModuleIdx == BPWM1_MODULE)
    {
        u32TmpVal = ((CLK->CLKSEL2 & CLK_CLKSEL2_BPWM1SEL_Msk) >> CLK_CLKSEL2_BPWM1SEL_Pos);
    }
    else if(MODULE_CLKSEL_Msk(u32ModuleIdx) != MODULE_NoMsk)
    {
        /* Get clock select control register address */
        u32TmpAddr = (uint32_t)&CLK->CLKSEL0 + (au32SelTbl[MODULE_CLKSEL(u32ModuleIdx)]);

        /* Get clock source selection setting */
        u32TmpVal = ((inpw((uint32_t *)u32TmpAddr) & (MODULE_CLKSEL_Msk(u32ModuleIdx) << MODULE_CLKSEL_Pos(u32ModuleIdx))) >> MODULE_CLKSEL_Pos(u32ModuleIdx));
    }

    return u32TmpVal;
}

/**
  * @brief      Get selected module clock divider number
  * @param[in]  u32ModuleIdx is module index.
  *             - \ref SDH0_MODULE
  *             - \ref USBH_MODULE
  *             - \ref UART0_MODULE
  *             - \ref UART1_MODULE
  *             - \ref UART2_MODULE
  *             - \ref UART3_MODULE
  *             - \ref UART4_MODULE
  *             - \ref UART5_MODULE
  *             - \ref OTG_MODULE
  *             - \ref USBD_MODULE
  *             - \ref SC0_MODULE
  *             - \ref SC1_MODULE
  *             - \ref SC2_MODULE
  *             - \ref EADC_MODULE
  * @return     Selected module clock divider number setting
  * @details    This function get selected module clock divider number.
  */

__NONSECURE_ENTRY_WEAK
uint32_t CLK_GetModuleClockDivider(uint32_t u32ModuleIdx)
{
    uint32_t u32TmpVal = 0UL, u32TmpAddr = 0UL;
    uint32_t au32DivTbl[4] = {0x0UL, 0x4UL, 0x8UL, 0x10UL};

    if(MODULE_CLKDIV_Msk(u32ModuleIdx) != MODULE_NoMsk)
    {
        /* Get clock divider control register address */
        u32TmpAddr = (uint32_t)&CLK->CLKDIV0 + (au32DivTbl[MODULE_CLKDIV(u32ModuleIdx)]);
        /* Get clock divider number setting */
        u32TmpVal = ((inpw((uint32_t *)u32TmpAddr) & (MODULE_CLKDIV_Msk(u32ModuleIdx) << MODULE_CLKDIV_Pos(u32ModuleIdx))) >> MODULE_CLKDIV_Pos(u32ModuleIdx));
    }

    return u32TmpVal;
}


/**@}*/ /* end of group CLK_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group CLK_Driver */

/**@}*/ /* end of group Standard_Driver */

