/**************************************************************************//**
 * @file     clk.c
 * @brief    series CLK driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
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
#define SYSPLLFREQCLK    FREQ_180MHZ

/**
  * @brief      Disable clock divider output function
  * @param      None
  * @return     None
  * @details    This function disable clock divider output function.
  */
void CLK_DisableCKO(void)
{
    /* Disable CKO clock source */
    CLK_DisableModuleClock(CLKO_MODULE);
}

/**
  * @brief      This function enable clock divider output module clock,
  *             enable clock divider output function and set frequency selection.
  * @param[in]  u32ClkSrc is frequency divider function clock source. Including :
  *             - \ref CLK_CLKSEL4_CKOSEL_HXT
  *             - \ref CLK_CLKSEL4_CKOSEL_LXT
  *             - \ref CLK_CLKSEL4_CKOSEL_LIRC
  *             - \ref CLK_CLKSEL4_CKOSEL_HIRC
  *             - \ref CLK_CLKSEL4_CKOSEL_CAPLL
  *             - \ref CLK_CLKSEL4_CKOSEL_SYSPLL
  *             - \ref CLK_CLKSEL4_CKOSEL_APLL
  *             - \ref CLK_CLKSEL4_CKOSEL_EPLL
  *             - \ref CLK_CLKSEL4_CKOSEL_VPLL
  * @param[in]  u32ClkDiv is divider output frequency selection. It could be 0~15.
  * @param[in]  u32ClkDivBy1En is clock divided by one enabled.
  * @return     None
  * @details    Output selected clock to CKO. The output clock frequency is divided by u32ClkDiv. \n
  *             The formula is: \n
  *                 CKO frequency = (Clock source frequency) / 2^(u32ClkDiv + 1) \n
  *             This function is just used to set CKO clock.
  *             User must enable I/O for CKO clock output pin by themselves. \n
  */
void CLK_EnableCKO(uint32_t u32ClkSrc, uint32_t u32ClkDiv, uint32_t u32ClkDivBy1En)
{
    /* CKO = clock source / 2^(u32ClkDiv + 1) */
    CLK->CLKOCTL = CLK_CLKOCTL_CLKOEN_Msk | (u32ClkDiv) | (u32ClkDivBy1En << CLK_CLKOCTL_DIV1EN_Pos);

    /* Enable CKO clock source */
    CLK_EnableModuleClock(CLKO_MODULE);

    /* Select CKO clock source */
    CLK_SetModuleClock(CLKO_MODULE, u32ClkSrc, 0UL);
}

#if defined(USE_MA35D1_SUBM)
/**
  * @brief      Enter to Power-down mode
  * @param      None
  * @return     None
  * @details    This function is used to let system enter to Power-down mode. \n
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_PowerDown(void)
{
    /* Set the processor uses deep sleep as its low power mode */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Set system Power-down enabled */
    SYS->PMUCR |= (SYS_PMUCR_RTPPDEN_Msk);

    /* Chip enter Power-down mode after CPU run WFI instruction */
    __WFI();

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
    SYS->PMUCR &= ~(SYS_PMUCR_RTPPDEN_Msk);

    /* Chip enter idle mode after CPU run WFI instruction */
    __WFI();
}
#else
void SystemCoreClockUpdate(void)
{

}
#endif

/**
  * @brief      Get external high speed crystal clock frequency
  * @param      None
  * @return     External high frequency crystal frequency
  * @details    This function get external high frequency crystal frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetHXTFreq(void)
{
    uint32_t u32Freq;

    if ((CLK->PWRCTL & CLK_PWRCTL_HXTEN_Msk) == CLK_PWRCTL_HXTEN_Msk)
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
uint32_t CLK_GetLXTFreq(void)
{
    uint32_t u32Freq;

    if ((CLK->PWRCTL & CLK_PWRCTL_LXTEN_Msk) == CLK_PWRCTL_LXTEN_Msk)
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
  * @brief      Get SYSCLK0 frequency
  * @param      None
  * @return     SYSCLK0 frequency
  * @details    This function get SYSCLK0 frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetSYSCLK0Freq(void)
{
    uint32_t u32Freq;

    if ((CLK->CLKSEL0 & CLK_CLKSEL0_SYSCK0SEL_Msk) == CLK_CLKSEL0_SYSCK0SEL_EPLL_DIV2)
    {
        u32Freq = CLK_GetPLLClockFreq(EPLL) / 2;
    }
    else
    {
        u32Freq = SYSPLLFREQCLK;
    }

    return u32Freq;
}

/**
  * @brief      Get SYSCLK1 frequency
  * @param      None
  * @return     SYSCLK1 frequency
  * @details    This function get SYSCLK1 frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetSYSCLK1Freq(void)
{
    uint32_t u32Freq;

    if ((CLK->CLKSEL0 & CLK_CLKSEL0_SYSCK1SEL_Msk) == CLK_CLKSEL0_SYSCK1SEL_HXT)
    {
        u32Freq = __HXT;
    }
    else
    {
        u32Freq = SYSPLLFREQCLK;
    }

    return u32Freq;
}

/**
  * @brief      Get CPU frequency
  * @param      None
  * @return     CPU frequency
  * @details    This function get CPU frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetCPUFreq(void)
{
    return CLK_GetSYSCLK1Freq();
}

/**
  * @brief      Set HCLK frequency
  * @param[in]  u32Hclk is HCLK frequency. The range of u32Hclk is running up to 180MHz.
  * @return     HCLK frequency
  * @details    This function is used to set HCLK frequency. The frequency unit is Hz. \n
  *             The register write-protection function should be disabled before using this function.
  */
uint32_t CLK_SetCoreClock(uint32_t u32Hclk)
{
    /* The range of u32Hclk is running up to SYSPLLFREQCLK MHz */
    if (u32Hclk > SYSPLLFREQCLK)
    {
        u32Hclk = SYSPLLFREQCLK;
    }

    /* Return actually HCLK frequency is PLL frequency divide 1 */
    return u32Hclk;
}

/**
  * @brief      This function set HCLK clock source and HCLK clock divider
  * @param[in]  u32ClkSrc is HCLK clock source. Including :
  *             - \ref CLK_CLKSEL0_HCLKSEL_HXT
  *             - \ref CLK_CLKSEL0_HCLKSEL_LXT
  *             - \ref CLK_CLKSEL0_HCLKSEL_PLL
  *             - \ref CLK_CLKSEL0_HCLKSEL_LIRC
  *             - \ref CLK_CLKSEL0_HCLKSEL_HIRC
  * @param[in]  u32ClkDiv is HCLK clock divider. Including :
  *             - \ref CLK_CLKDIV0_HCLK(x)
  * @return     None
  * @details    This function set HCLK clock source and HCLK clock divider. \n
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_SetHCLK(uint32_t u32ClkSrc, uint32_t u32ClkDiv)
{
}

/**
  * @brief      This function set selected module clock source and module clock divider
  * @param[in]  u32ModuleIdx is module index.
  * @param[in]  u32ClkSrc is module clock source.
  * @param[in]  u32ClkDiv is module clock divider.
  * @return     None
  * @details    Valid parameter combinations listed in following table:
  *
  * |Module index          |Clock source                           |Divider                       |
  * | :----------------    | :-----------------------------------  | :------------------------    |
  * |\ref CA35CK_MODULE    |\ref CLK_CLKSEL0_CA35CKSEL_HXT         | x                            |
  * |\ref CA35CK_MODULE    |\ref CLK_CLKSEL0_CA35CKSEL_CAPLL       | x                            |
  * |\ref SYSCK0_MODULE    |\ref CLK_CLKSEL0_SYSCK0SEL_SYSPLL      | x                            |
  * |\ref SYSCK0_MODULE    |\ref CLK_CLKSEL0_SYSCK0SEL_EPLL        | x                            |
  * |\ref LVRDB_MODULE     |\ref CLK_CLKSEL0_LVRDBSEL_LIRC         | x                            |
  * |\ref LVRDB_MODULE     |\ref CLK_CLKSEL0_LVRDBSEL_HIRC         | x                            |
  * |\ref SYSCK1_MODULE    |\ref CLK_CLKSEL0_SYSCK1SEL_HXT         | x                            |
  * |\ref SYSCK1_MODULE    |\ref CLK_CLKSEL0_SYSCK1SEL_SYSPLL      | x                            |
  * |\ref RTPST_MODULE     |\ref CLK_CLKSEL0_RTPSTSEL_HXT          | x                            |
  * |\ref RTPST_MODULE     |\ref CLK_CLKSEL0_RTPSTSEL_LXT          | x                            |
  * |\ref RTPST_MODULE     |\ref CLK_CLKSEL0_RTPSTSEL_HXT_DIV2     | x                            |
  * |\ref RTPST_MODULE     |\ref CLK_CLKSEL0_RTPSTSEL_SYSCLK1_DIV2 | x                            |
  * |\ref RTPST_MODULE     |\ref CLK_CLKSEL0_RTPSTSEL_HIRC         | x                            |
  * |\ref CCAP0_MODULE     |\ref CLK_CLKSEL0_CCAP0SEL_HXT          |\ref CLK_CLKDIV1_CCAP0(x)     |
  * |\ref CCAP0_MODULE     |\ref CLK_CLKSEL0_CCAP0SEL_SYSPLL       |\ref CLK_CLKDIV1_CCAP0(x)     |
  * |\ref CCAP0_MODULE     |\ref CLK_CLKSEL0_CCAP0SEL_APLL         |\ref CLK_CLKDIV1_CCAP0(x)     |
  * |\ref CCAP0_MODULE     |\ref CLK_CLKSEL0_CCAP0SEL_VPLL         |\ref CLK_CLKDIV1_CCAP0(x)     |
  * |\ref CCAP1_MODULE     |\ref CLK_CLKSEL0_CCAP1SEL_HXT          |\ref CLK_CLKDIV1_CCAP1(x)     |
  * |\ref CCAP1_MODULE     |\ref CLK_CLKSEL0_CCAP1SEL_SYSPLL       |\ref CLK_CLKDIV1_CCAP1(x)     |
  * |\ref CCAP1_MODULE     |\ref CLK_CLKSEL0_CCAP1SEL_APLL         |\ref CLK_CLKDIV1_CCAP1(x)     |
  * |\ref CCAP1_MODULE     |\ref CLK_CLKSEL0_CCAP1SEL_VPLL         |\ref CLK_CLKDIV1_CCAP1(x)     |
  * |\ref SD0_MODULE       |\ref CLK_CLKSEL0_SD0SEL_SYSPLL         | x                            |
  * |\ref SD0_MODULE       |\ref CLK_CLKSEL0_SD0SEL_APLL           | x                            |
  * |\ref SD1_MODULE       |\ref CLK_CLKSEL0_SD1SEL_SYSPLL         | x                            |
  * |\ref SD1_MODULE       |\ref CLK_CLKSEL0_SD1SEL_APLL           | x                            |
  * |\ref DCU_MODULE       |\ref CLK_CLKSEL0_DCUSEL_SYSPLL         | x                            |
  * |\ref DCU_MODULE       |\ref CLK_CLKSEL0_DCUSEL_EPLL           | x                            |
  * |\ref GFX_MODULE       |\ref CLK_CLKSEL0_GFXSEL_SYSPLL         | x                            |
  * |\ref GFX_MODULE       |\ref CLK_CLKSEL0_GFXSEL_EPLL           | x                            |
  * |\ref DBG_MODULE       |\ref CLK_CLKSEL0_DBGSEL_HIRC           |\ref CLK_CLKDIV3_DBG(x)       |
  * |\ref DBG_MODULE       |\ref CLK_CLKSEL0_DBGSEL_SYSPLL         |\ref CLK_CLKDIV3_DBG(x)       |
  * |\ref TMR0_MODULE      |\ref CLK_CLKSEL1_TMR0SEL_HXT           | x                            |
  * |\ref TMR0_MODULE      |\ref CLK_CLKSEL1_TMR0SEL_LXT           | x                            |
  * |\ref TMR0_MODULE      |\ref CLK_CLKSEL1_TMR0SEL_LIRC          | x                            |
  * |\ref TMR0_MODULE      |\ref CLK_CLKSEL1_TMR0SEL_HIRC          | x                            |
  * |\ref TMR0_MODULE      |\ref CLK_CLKSEL1_TMR0SEL_PCLK0         | x                            |
  * |\ref TMR0_MODULE      |\ref CLK_CLKSEL1_TMR0SEL_EXT           | x                            |
  * |\ref TMR1_MODULE      |\ref CLK_CLKSEL1_TMR1SEL_HXT           | x                            |
  * |\ref TMR1_MODULE      |\ref CLK_CLKSEL1_TMR1SEL_LXT           | x                            |
  * |\ref TMR1_MODULE      |\ref CLK_CLKSEL1_TMR1SEL_LIRC          | x                            |
  * |\ref TMR1_MODULE      |\ref CLK_CLKSEL1_TMR1SEL_HIRC          | x                            |
  * |\ref TMR1_MODULE      |\ref CLK_CLKSEL1_TMR1SEL_PCLK0         | x                            |
  * |\ref TMR1_MODULE      |\ref CLK_CLKSEL1_TMR1SEL_EXT           | x                            |
  * |\ref TMR2_MODULE      |\ref CLK_CLKSEL1_TMR2SEL_HXT           | x                            |
  * |\ref TMR2_MODULE      |\ref CLK_CLKSEL1_TMR2SEL_LXT           | x                            |
  * |\ref TMR2_MODULE      |\ref CLK_CLKSEL1_TMR2SEL_LIRC          | x                            |
  * |\ref TMR2_MODULE      |\ref CLK_CLKSEL1_TMR2SEL_HIRC          | x                            |
  * |\ref TMR2_MODULE      |\ref CLK_CLKSEL1_TMR2SEL_PCLK1         | x                            |
  * |\ref TMR2_MODULE      |\ref CLK_CLKSEL1_TMR2SEL_EXT           | x                            |
  * |\ref TMR3_MODULE      |\ref CLK_CLKSEL1_TMR3SEL_HXT           | x                            |
  * |\ref TMR3_MODULE      |\ref CLK_CLKSEL1_TMR3SEL_LXT           | x                            |
  * |\ref TMR3_MODULE      |\ref CLK_CLKSEL1_TMR3SEL_LIRC          | x                            |
  * |\ref TMR3_MODULE      |\ref CLK_CLKSEL1_TMR3SEL_HIRC          | x                            |
  * |\ref TMR3_MODULE      |\ref CLK_CLKSEL1_TMR3SEL_PCLK1         | x                            |
  * |\ref TMR3_MODULE      |\ref CLK_CLKSEL1_TMR3SEL_EXT           | x                            |
  * |\ref TMR4_MODULE      |\ref CLK_CLKSEL1_TMR4SEL_HXT           | x                            |
  * |\ref TMR4_MODULE      |\ref CLK_CLKSEL1_TMR4SEL_LXT           | x                            |
  * |\ref TMR4_MODULE      |\ref CLK_CLKSEL1_TMR4SEL_LIRC          | x                            |
  * |\ref TMR4_MODULE      |\ref CLK_CLKSEL1_TMR4SEL_HIRC          | x                            |
  * |\ref TMR4_MODULE      |\ref CLK_CLKSEL1_TMR4SEL_EXT           | x                            |
  * |\ref TMR4_MODULE      |\ref CLK_CLKSEL1_TMR4SEL_PCLK2         | x                            |
  * |\ref TMR5_MODULE      |\ref CLK_CLKSEL1_TMR5SEL_HXT           | x                            |
  * |\ref TMR5_MODULE      |\ref CLK_CLKSEL1_TMR5SEL_LXT           | x                            |
  * |\ref TMR5_MODULE      |\ref CLK_CLKSEL1_TMR5SEL_LIRC          | x                            |
  * |\ref TMR5_MODULE      |\ref CLK_CLKSEL1_TMR5SEL_HIRC          | x                            |
  * |\ref TMR5_MODULE      |\ref CLK_CLKSEL1_TMR5SEL_EXT           | x                            |
  * |\ref TMR5_MODULE      |\ref CLK_CLKSEL1_TMR5SEL_PCLK2         | x                            |
  * |\ref TMR6_MODULE      |\ref CLK_CLKSEL1_TMR6SEL_HXT           | x                            |
  * |\ref TMR6_MODULE      |\ref CLK_CLKSEL1_TMR6SEL_LXT           | x                            |
  * |\ref TMR6_MODULE      |\ref CLK_CLKSEL1_TMR6SEL_LIRC          | x                            |
  * |\ref TMR6_MODULE      |\ref CLK_CLKSEL1_TMR6SEL_HIRC          | x                            |
  * |\ref TMR6_MODULE      |\ref CLK_CLKSEL1_TMR6SEL_PCLK0         | x                            |
  * |\ref TMR6_MODULE      |\ref CLK_CLKSEL1_TMR6SEL_EXT           | x                            |
  * |\ref TMR7_MODULE      |\ref CLK_CLKSEL1_TMR7SEL_HXT           | x                            |
  * |\ref TMR7_MODULE      |\ref CLK_CLKSEL1_TMR7SEL_LXT           | x                            |
  * |\ref TMR7_MODULE      |\ref CLK_CLKSEL1_TMR7SEL_LIRC          | x                            |
  * |\ref TMR7_MODULE      |\ref CLK_CLKSEL1_TMR7SEL_HIRC          | x                            |
  * |\ref TMR7_MODULE      |\ref CLK_CLKSEL1_TMR7SEL_PCLK0         | x                            |
  * |\ref TMR7_MODULE      |\ref CLK_CLKSEL1_TMR7SEL_EXT           | x                            |
  * |\ref TMR8_MODULE      |\ref CLK_CLKSEL2_TMR8SEL_HXT           | x                            |
  * |\ref TMR8_MODULE      |\ref CLK_CLKSEL2_TMR8SEL_LXT           | x                            |
  * |\ref TMR8_MODULE      |\ref CLK_CLKSEL2_TMR8SEL_LIRC          | x                            |
  * |\ref TMR8_MODULE      |\ref CLK_CLKSEL2_TMR8SEL_HIRC          | x                            |
  * |\ref TMR8_MODULE      |\ref CLK_CLKSEL2_TMR8SEL_PCLK1         | x                            |
  * |\ref TMR8_MODULE      |\ref CLK_CLKSEL2_TMR8SEL_EXT           | x                            |
  * |\ref TMR9_MODULE      |\ref CLK_CLKSEL2_TMR9SEL_HXT           | x                            |
  * |\ref TMR9_MODULE      |\ref CLK_CLKSEL2_TMR9SEL_LXT           | x                            |
  * |\ref TMR9_MODULE      |\ref CLK_CLKSEL2_TMR9SEL_LIRC          | x                            |
  * |\ref TMR9_MODULE      |\ref CLK_CLKSEL2_TMR9SEL_HIRC          | x                            |
  * |\ref TMR9_MODULE      |\ref CLK_CLKSEL2_TMR9SEL_PCLK1         | x                            |
  * |\ref TMR9_MODULE      |\ref CLK_CLKSEL2_TMR9SEL_EXT           | x                            |
  * |\ref TMR10_MODULE     |\ref CLK_CLKSEL2_TMR10SEL_HXT          | x                            |
  * |\ref TMR10_MODULE     |\ref CLK_CLKSEL2_TMR10SEL_LXT          | x                            |
  * |\ref TMR10_MODULE     |\ref CLK_CLKSEL2_TMR10SEL_LIRC         | x                            |
  * |\ref TMR10_MODULE     |\ref CLK_CLKSEL2_TMR10SEL_HIRC         | x                            |
  * |\ref TMR10_MODULE     |\ref CLK_CLKSEL2_TMR10SEL_EXT          | x                            |
  * |\ref TMR10_MODULE     |\ref CLK_CLKSEL2_TMR10SEL_PCLK2        | x                            |
  * |\ref TMR11_MODULE     |\ref CLK_CLKSEL2_TMR11SEL_HXT          | x                            |
  * |\ref TMR11_MODULE     |\ref CLK_CLKSEL2_TMR11SEL_LXT          | x                            |
  * |\ref TMR11_MODULE     |\ref CLK_CLKSEL2_TMR11SEL_LIRC         | x                            |
  * |\ref TMR11_MODULE     |\ref CLK_CLKSEL2_TMR11SEL_HIRC         | x                            |
  * |\ref TMR11_MODULE     |\ref CLK_CLKSEL2_TMR11SEL_EXT          | x                            |
  * |\ref TMR11_MODULE     |\ref CLK_CLKSEL2_TMR11SEL_PCLK2        | x                            |
  * |\ref UART0_MODULE     |\ref CLK_CLKSEL2_UART0SEL_HXT          |\ref CLK_CLKDIV1_UART0(x)     |
  * |\ref UART0_MODULE     |\ref CLK_CLKSEL2_UART0SEL_SYSCLK1      |\ref CLK_CLKDIV1_UART0(x)     |
  * |\ref UART1_MODULE     |\ref CLK_CLKSEL2_UART1SEL_HXT          |\ref CLK_CLKDIV1_UART1(x)     |
  * |\ref UART1_MODULE     |\ref CLK_CLKSEL2_UART1SEL_SYSCLK1      |\ref CLK_CLKDIV1_UART1(x)     |
  * |\ref UART2_MODULE     |\ref CLK_CLKSEL2_UART2SEL_HXT          |\ref CLK_CLKDIV1_UART2(x)     |
  * |\ref UART2_MODULE     |\ref CLK_CLKSEL2_UART2SEL_SYSCLK1      |\ref CLK_CLKDIV1_UART2(x)     |
  * |\ref UART3_MODULE     |\ref CLK_CLKSEL2_UART3SEL_HXT          |\ref CLK_CLKDIV1_UART3(x)     |
  * |\ref UART3_MODULE     |\ref CLK_CLKSEL2_UART3SEL_SYSCLK1      |\ref CLK_CLKDIV1_UART3(x)     |
  * |\ref UART4_MODULE     |\ref CLK_CLKSEL2_UART4SEL_HXT          |\ref CLK_CLKDIV2_UART4(x)     |
  * |\ref UART4_MODULE     |\ref CLK_CLKSEL2_UART4SEL_SYSCLK1      |\ref CLK_CLKDIV2_UART4(x)     |
  * |\ref UART5_MODULE     |\ref CLK_CLKSEL2_UART5SEL_HXT          |\ref CLK_CLKDIV2_UART5(x)     |
  * |\ref UART5_MODULE     |\ref CLK_CLKSEL2_UART5SEL_SYSCLK1      |\ref CLK_CLKDIV2_UART5(x)     |
  * |\ref UART6_MODULE     |\ref CLK_CLKSEL2_UART6SEL_HXT          |\ref CLK_CLKDIV2_UART6(x)     |
  * |\ref UART6_MODULE     |\ref CLK_CLKSEL2_UART6SEL_SYSCLK1      |\ref CLK_CLKDIV2_UART6(x)     |
  * |\ref UART7_MODULE     |\ref CLK_CLKSEL2_UART7SEL_HXT          |\ref CLK_CLKDIV2_UART7(x)     |
  * |\ref UART7_MODULE     |\ref CLK_CLKSEL2_UART7SEL_SYSCLK1      |\ref CLK_CLKDIV2_UART7(x)     |
  * |\ref UART8_MODULE     |\ref CLK_CLKSEL3_UART8SEL_HXT          |\ref CLK_CLKDIV2_UART8(x)     |
  * |\ref UART8_MODULE     |\ref CLK_CLKSEL3_UART8SEL_SYSCLK1      |\ref CLK_CLKDIV2_UART8(x)     |
  * |\ref UART9_MODULE     |\ref CLK_CLKSEL3_UART9SEL_HXT          |\ref CLK_CLKDIV2_UART9(x)     |
  * |\ref UART9_MODULE     |\ref CLK_CLKSEL3_UART9SEL_SYSCLK1      |\ref CLK_CLKDIV2_UART9(x)     |
  * |\ref UART10_MODULE    |\ref CLK_CLKSEL3_UART10SEL_HXT         |\ref CLK_CLKDIV1_UART1(x)     |
  * |\ref UART10_MODULE    |\ref CLK_CLKSEL3_UART10SEL_SYSCLK1     |\ref CLK_CLKDIV1_UART1(x)     |
  * |\ref UART11_MODULE    |\ref CLK_CLKSEL3_UART11SEL_HXT         |\ref CLK_CLKDIV1_UART1(x)     |
  * |\ref UART11_MODULE    |\ref CLK_CLKSEL3_UART11SEL_SYSCLK1     |\ref CLK_CLKDIV1_UART1(x)     |
  * |\ref UART12_MODULE    |\ref CLK_CLKSEL3_UART12SEL_HXT         |\ref CLK_CLKDIV1_UART1(x)     |
  * |\ref UART12_MODULE    |\ref CLK_CLKSEL3_UART12SEL_SYSCLK1     |\ref CLK_CLKDIV1_UART1(x)     |
  * |\ref UART13_MODULE    |\ref CLK_CLKSEL3_UART13SEL_HXT         |\ref CLK_CLKDIV1_UART1(x)     |
  * |\ref UART13_MODULE    |\ref CLK_CLKSEL3_UART13SEL_SYSCLK1     |\ref CLK_CLKDIV1_UART1(x)     |
  * |\ref UART14_MODULE    |\ref CLK_CLKSEL3_UART14SEL_HXT         |\ref CLK_CLKDIV1_UART1(x)     |
  * |\ref UART14_MODULE    |\ref CLK_CLKSEL3_UART14SEL_SYSCLK1     |\ref CLK_CLKDIV1_UART1(x)     |
  * |\ref UART15_MODULE    |\ref CLK_CLKSEL3_UART15SEL_HXT         |\ref CLK_CLKDIV1_UART1(x)     |
  * |\ref UART15_MODULE    |\ref CLK_CLKSEL3_UART15SEL_SYSCLK1     |\ref CLK_CLKDIV1_UART1(x)     |
  * |\ref UART16_MODULE    |\ref CLK_CLKSEL3_UART16SEL_HXT         |\ref CLK_CLKDIV1_UART1(x)     |
  * |\ref UART16_MODULE    |\ref CLK_CLKSEL3_UART16SEL_SYSCLK1     |\ref CLK_CLKDIV1_UART1(x)     |
  * |\ref WDT0_MODULE      |\ref CLK_CLKSEL3_WDT0SEL_HXT           | x                            |
  * |\ref WDT0_MODULE      |\ref CLK_CLKSEL3_WDT0SEL_LXT           | x                            |
  * |\ref WDT0_MODULE      |\ref CLK_CLKSEL3_WDT0SEL_LIRC          | x                            |
  * |\ref WDT0_MODULE      |\ref CLK_CLKSEL3_WDT0SEL_PCLK3         | x                            |
  * |\ref WWDT0_MODULE     |\ref CLK_CLKSEL3_WWDT0SEL_HXT          | x                            |
  * |\ref WWDT0_MODULE     |\ref CLK_CLKSEL3_WWDT0SEL_LXT          | x                            |
  * |\ref WWDT0_MODULE     |\ref CLK_CLKSEL3_WWDT0SEL_LIRC         | x                            |
  * |\ref WWDT0_MODULE     |\ref CLK_CLKSEL3_WWDT0SEL_PCLK3        | x                            |
  * |\ref WDT1_MODULE      |\ref CLK_CLKSEL3_WDT1SEL_HXT           | x                            |
  * |\ref WDT1_MODULE      |\ref CLK_CLKSEL3_WDT1SEL_LXT           | x                            |
  * |\ref WDT1_MODULE      |\ref CLK_CLKSEL3_WDT1SEL_LIRC          | x                            |
  * |\ref WDT1_MODULE      |\ref CLK_CLKSEL3_WDT1SEL_PCLK3         | x                            |
  * |\ref WWDT1_MODULE     |\ref CLK_CLKSEL3_WWDT1SEL_HXT          | x                            |
  * |\ref WWDT1_MODULE     |\ref CLK_CLKSEL3_WWDT1SEL_LXT          | x                            |
  * |\ref WWDT1_MODULE     |\ref CLK_CLKSEL3_WWDT1SEL_LIRC         | x                            |
  * |\ref WWDT1_MODULE     |\ref CLK_CLKSEL3_WWDT1SEL_PCLK3        | x                            |
  * |\ref WDT2_MODULE      |\ref CLK_CLKSEL3_WDT2SEL_HXT           | x                            |
  * |\ref WDT2_MODULE      |\ref CLK_CLKSEL3_WDT2SEL_LXT           | x                            |
  * |\ref WDT2_MODULE      |\ref CLK_CLKSEL3_WDT2SEL_LIRC          | x                            |
  * |\ref WDT2_MODULE      |\ref CLK_CLKSEL3_WDT2SEL_PCLK4         | x                            |
  * |\ref WWDT2_MODULE     |\ref CLK_CLKSEL3_WWDT2SEL_HXT          | x                            |
  * |\ref WWDT2_MODULE     |\ref CLK_CLKSEL3_WWDT2SEL_LXT          | x                            |
  * |\ref WWDT2_MODULE     |\ref CLK_CLKSEL3_WWDT2SEL_LIRC         | x                            |
  * |\ref WWDT2_MODULE     |\ref CLK_CLKSEL3_WWDT2SEL_PCLK4        | x                            |
  * |\ref SPI0_MODULE      |\ref CLK_CLKSEL4_SPI0SEL_PCLK1         | x                            |
  * |\ref SPI0_MODULE      |\ref CLK_CLKSEL4_SPI0SEL_APLL          | x                            |
  * |\ref SPI1_MODULE      |\ref CLK_CLKSEL4_SPI1SEL_APLL          | x                            |
  * |\ref SPI1_MODULE      |\ref CLK_CLKSEL4_SPI1SEL_PCLK2         | x                            |
  * |\ref SPI2_MODULE      |\ref CLK_CLKSEL4_SPI2SEL_PCLK1         | x                            |
  * |\ref SPI2_MODULE      |\ref CLK_CLKSEL4_SPI2SEL_APLL          | x                            |
  * |\ref SPI3_MODULE      |\ref CLK_CLKSEL4_SPI3SEL_APLL          | x                            |
  * |\ref SPI3_MODULE      |\ref CLK_CLKSEL4_SPI3SEL_PCLK2         | x                            |
  * |\ref QSPI0_MODULE     |\ref CLK_CLKSEL4_QSPI0SEL_PCLK0        | x                            |
  * |\ref QSPI0_MODULE     |\ref CLK_CLKSEL4_QSPI0SEL_APLL         | x                            |
  * |\ref QSPI1_MODULE     |\ref CLK_CLKSEL4_QSPI1SEL_PCLK0        | x                            |
  * |\ref QSPI1_MODULE     |\ref CLK_CLKSEL4_QSPI1SEL_APLL         | x                            |
  * |\ref I2S0_MODULE      |\ref CLK_CLKSEL4_I2S0SEL_APLL          | x                            |
  * |\ref I2S0_MODULE      |\ref CLK_CLKSEL4_I2S0SEL_SYSCLK1       | x                            |
  * |\ref I2S1_MODULE      |\ref CLK_CLKSEL4_I2S1SEL_APLL          | x                            |
  * |\ref I2S1_MODULE      |\ref CLK_CLKSEL4_I2S1SEL_SYSCLK1       | x                            |
  * |\ref CANFD0_MODULE    |\ref CLK_CLKSEL4_CANFD0SEL_APLL        |\ref CLK_CLKDIV0_CANFD0(x)    |
  * |\ref CANFD0_MODULE    |\ref CLK_CLKSEL4_CANFD0SEL_VPLL        |\ref CLK_CLKDIV0_CANFD0(x)    |
  * |\ref CANFD1_MODULE    |\ref CLK_CLKSEL4_CANFD1SEL_APLL        |\ref CLK_CLKDIV0_CANFD1(x)    |
  * |\ref CANFD1_MODULE    |\ref CLK_CLKSEL4_CANFD1SEL_VPLL        |\ref CLK_CLKDIV0_CANFD1(x)    |
  * |\ref CANFD2_MODULE    |\ref CLK_CLKSEL4_CANFD2SEL_APLL        |\ref CLK_CLKDIV0_CANFD2(x)    |
  * |\ref CANFD2_MODULE    |\ref CLK_CLKSEL4_CANFD2SEL_VPLL        |\ref CLK_CLKDIV0_CANFD2(x)    |
  * |\ref CANFD3_MODULE    |\ref CLK_CLKSEL4_CANFD3SEL_APLL        |\ref CLK_CLKDIV0_CANFD3(x)    |
  * |\ref CANFD3_MODULE    |\ref CLK_CLKSEL4_CANFD3SEL_VPLL        |\ref CLK_CLKDIV0_CANFD3(x)    |
  * |\ref CLKO_MODULE      |\ref CLK_CLKSEL4_CKOSEL_HXT            | x                            |
  * |\ref CLKO_MODULE      |\ref CLK_CLKSEL4_CKOSEL_LXT            | x                            |
  * |\ref CLKO_MODULE      |\ref CLK_CLKSEL4_CKOSEL_LIRC           | x                            |
  * |\ref CLKO_MODULE      |\ref CLK_CLKSEL4_CKOSEL_HIRC           | x                            |
  * |\ref CLKO_MODULE      |\ref CLK_CLKSEL4_CKOSEL_CAPLL          | x                            |
  * |\ref CLKO_MODULE      |\ref CLK_CLKSEL4_CKOSEL_SYSPLL         | x                            |
  * |\ref CLKO_MODULE      |\ref CLK_CLKSEL4_CKOSEL_APLL           | x                            |
  * |\ref CLKO_MODULE      |\ref CLK_CLKSEL4_CKOSEL_EPLL           | x                            |
  * |\ref CLKO_MODULE      |\ref CLK_CLKSEL4_CKOSEL_VPLL           | x                            |
  * |\ref SC0_MODULE       |\ref CLK_CLKSEL4_SC0SEL_HXT            |\ref CLK_CLKDIV1_SC0(x)       |
  * |\ref SC0_MODULE       |\ref CLK_CLKSEL4_SC0SEL_PCLK4          |\ref CLK_CLKDIV1_SC0(x)       |
  * |\ref SC1_MODULE       |\ref CLK_CLKSEL4_SC1SEL_HXT            |\ref CLK_CLKDIV1_SC1(x)       |
  * |\ref SC1_MODULE       |\ref CLK_CLKSEL4_SC1SEL_PCLK4          |\ref CLK_CLKDIV1_SC1(x)       |
  * |\ref KPI_MODULE       |\ref CLK_CLKSEL4_KPISEL_HXT            |\ref CLK_CLKDIV4_KPI(x)       |
  * |\ref KPI_MODULE       |\ref CLK_CLKSEL4_KPISEL_LXT            |\ref CLK_CLKDIV4_KPI(x)       |
  * |\ref CA35CK_MODULE    |\ref CLK_CLKSEL0_CA35CKSEL_HXT         | x                            |
  * |\ref CA35CK_MODULE    |\ref CLK_CLKSEL0_CA35CKSEL_CAPLL       | x                            |

  *
  */
void CLK_SetModuleClock(uint32_t u32ModuleIdx, uint32_t u32ClkSrc, uint32_t u32ClkDiv)
{
    uint32_t u32sel = 0U, u32div = 0U;

    if (u32ModuleIdx == KPI_MODULE)
    {
        CLK->CLKDIV4 = (CLK->CLKDIV4 & ~(CLK_CLKDIV4_KPIDIV_Msk)) | u32ClkDiv;
        CLK->CLKSEL4 = (CLK->CLKSEL4 & ~(CLK_CLKSEL4_KPISEL_Msk)) | u32ClkSrc;
        CLK->APBCLK0 = (CLK->APBCLK0 & ~(CLK_APBCLK0_KPICKEN_Msk)) | CLK_APBCLK0_KPICKEN_Msk;
    }
    else if (u32ModuleIdx == ADC_MODULE)
    {
        CLK->CLKDIV4 = (CLK->CLKDIV4 & ~(CLK_CLKDIV4_ADCDIV_Msk)) | u32ClkDiv;
        CLK->APBCLK2 = (CLK->APBCLK2 & ~(CLK_APBCLK2_ADCCKEN_Msk)) | CLK_APBCLK2_ADCCKEN_Msk;
    }
    else
    {
        if (MODULE_CLKDIV_Msk(u32ModuleIdx) != MODULE_NoMsk)
        {
            /* Get clock divider control register address */
            u32div = (uint32_t)&CLK->CLKDIV0 + ((MODULE_CLKDIV(u32ModuleIdx)) * 4U);
            /* Apply new divider */
            M32(u32div) = (M32(u32div) & (~(MODULE_CLKDIV_Msk(u32ModuleIdx) << MODULE_CLKDIV_Pos(u32ModuleIdx)))) | u32ClkDiv;
        }

        if (MODULE_CLKSEL_Msk(u32ModuleIdx) != MODULE_NoMsk)
        {
            /* Get clock select control register address */
            u32sel = (uint32_t)&CLK->CLKSEL0 + ((MODULE_CLKSEL(u32ModuleIdx)) * 4U);
            /* Set new clock selection setting */
            M32(u32sel) = (M32(u32sel) & (~(MODULE_CLKSEL_Msk(u32ModuleIdx) << MODULE_CLKSEL_Pos(u32ModuleIdx)))) | u32ClkSrc;
        }
    }
}

/**
  * @brief      Set SysTick clock source
  * @param[in]  u32ClkSrc is module clock source. Including:
  *             - \ref CLK_CLKSEL0_RTPSTSEL_HXT
  *             - \ref CLK_CLKSEL0_RTPSTSEL_LXT
  *             - \ref CLK_CLKSEL0_RTPSTSEL_HXT_DIV2
  *             - \ref CLK_CLKSEL0_RTPSTSEL_SYSCLK1_DIV2
  *             - \ref CLK_CLKSEL0_RTPSTSEL_HIRC
  * @return     None
  * @details    This function set SysTick clock source. \n
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_SetSysTickClockSrc(uint32_t u32ClkSrc)
{
    CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_RTPSTSEL_Msk) | u32ClkSrc;
}

/**
  * @brief      Enable clock source
  * @param[in]  u32ClkMask is clock source mask. Including :
  *             - \ref CLK_PWRCTL_HXTEN_Msk
  *             - \ref CLK_PWRCTL_LXTEN_Msk
  *             - \ref CLK_PWRCTL_HIRCEN_Msk
  *             - \ref CLK_PWRCTL_LIRCEN_Msk
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
  *             - \ref PDMA2_MODULE
  *             - \ref PDMA3_MODULE
  *             - \ref WH0_MODULE
  *             - \ref WH1_MODULE
  *             - \ref HWSEM0_MODULE
  *             - \ref EBI_MODULE
  *             - \ref SRAM0_MODULE
  *             - \ref SRAM1_MODULE
  *             - \ref ROM_MODULE
  *             - \ref TRA_MODULE
  *             - \ref DBG_MODULE
  *             - \ref CLKO_MODULE
  *             - \ref GTMR_MODULE
  *             - \ref GPA_MODULE
  *             - \ref GPB_MODULE
  *             - \ref GPC_MODULE
  *             - \ref GPD_MODULE
  *             - \ref GPE_MODULE
  *             - \ref GPF_MODULE
  *             - \ref GPG_MODULE
  *             - \ref GPH_MODULE
  *             - \ref GPI_MODULE
  *             - \ref GPJ_MODULE
  *             - \ref GPK_MODULE
  *             - \ref GPL_MODULE
  *             - \ref GPM_MODULE
  *             - \ref GPN_MODULE
  *             - \ref CA35_MODULE
  *             - \ref RTP_MODULE
  *             - \ref TAHB_MODULE
  *             - \ref LVRDB_MODULE
  *             - \ref DDR0_MODULE
  *             - \ref DDR6_MODULE
  *             - \ref CANFD0_MODULE
  *             - \ref CANFD1_MODULE
  *             - \ref CANFD2_MODULE
  *             - \ref CANFD3_MODULE
  *             - \ref SDH0_MODULE
  *             - \ref SDH1_MODULE
  *             - \ref NAND_MODULE
  *             - \ref USBD_MODULE
  *             - \ref USBH_MODULE
  *             - \ref HUSBH0_MODULE
  *             - \ref HUSBH1_MODULE
  *             - \ref GFX_MODULE
  *             - \ref VDEC_MODULE
  *             - \ref DCU_MODULE
  *             - \ref GMAC0_MODULE
  *             - \ref GMAC1_MODULE
  *             - \ref CCAP0_MODULE
  *             - \ref CCAP1_MODULE
  *             - \ref TMR0_MODULE
  *             - \ref TMR1_MODULE
  *             - \ref TMR2_MODULE
  *             - \ref TMR3_MODULE
  *             - \ref TMR4_MODULE
  *             - \ref TMR5_MODULE
  *             - \ref TMR6_MODULE
  *             - \ref TMR7_MODULE
  *             - \ref TMR8_MODULE
  *             - \ref TMR9_MODULE
  *             - \ref TMR10_MODULE
  *             - \ref TMR11_MODULE
  *             - \ref UART0_MODULE
  *             - \ref UART1_MODULE
  *             - \ref UART2_MODULE
  *             - \ref UART3_MODULE
  *             - \ref UART4_MODULE
  *             - \ref UART5_MODULE
  *             - \ref UART6_MODULE
  *             - \ref UART7_MODULE
  *             - \ref UART8_MODULE
  *             - \ref UART9_MODULE
  *             - \ref UART10_MODULE
  *             - \ref UART11_MODULE
  *             - \ref UART12_MODULE
  *             - \ref UART13_MODULE
  *             - \ref UART14_MODULE
  *             - \ref UART15_MODULE
  *             - \ref UART16_MODULE
  *             - \ref RTC_MODULE
  *             - \ref DDRP_MODULE
  *             - \ref KPI_MODULE
  *             - \ref I2C0_MODULE
  *             - \ref I2C1_MODULE
  *             - \ref I2C2_MODULE
  *             - \ref I2C3_MODULE
  *             - \ref I2C4_MODULE
  *             - \ref I2C5_MODULE
  *             - \ref QSPI0_MODULE
  *             - \ref QSPI1_MODULE
  *             - \ref SC0_MODULE
  *             - \ref SC1_MODULE
  *             - \ref WDT0_MODULE
  *             - \ref WDT1_MODULE
  *             - \ref WDT2_MODULE
  *             - \ref EPWM0_MODULE
  *             - \ref EPWM1_MODULE
  *             - \ref EPWM2_MODULE
  *             - \ref I2S0_MODULE
  *             - \ref I2S1_MODULE
  *             - \ref SSMCC_MODULE
  *             - \ref SSPCC_MODULE
  *             - \ref SPI0_MODULE
  *             - \ref SPI1_MODULE
  *             - \ref SPI2_MODULE
  *             - \ref SPI3_MODULE
  *             - \ref ECAP0_MODULE
  *             - \ref ECAP1_MODULE
  *             - \ref ECAP2_MODULE
  *             - \ref QEI0_MODULE
  *             - \ref QEI1_MODULE
  *             - \ref QEI2_MODULE
  *             - \ref ADC_MODULE
  *             - \ref EADC_MODULE
  * @return     None
  * @details    This function is used to enable module clock.
  */
void CLK_EnableModuleClock(uint32_t u32ModuleIdx)
{
    vu32 u32tmpVal = 0UL, u32tmpAddr = 0UL;

    u32tmpVal = (1UL << MODULE_IP_EN_Pos(u32ModuleIdx));
    u32tmpAddr = (uint32_t)&CLK->SYSCLK0;
    u32tmpAddr += ((MODULE_APBCLK(u32ModuleIdx) * 4UL));

    *(vu32 *)u32tmpAddr |= u32tmpVal;
}

/**
  * @brief      Disable module clock
  * @param[in]  u32ModuleIdx is module index. Including :
  *             - \ref PDMA0_MODULE
  *             - \ref PDMA1_MODULE
  *             - \ref PDMA2_MODULE
  *             - \ref PDMA3_MODULE
  *             - \ref WH0_MODULE
  *             - \ref WH1_MODULE
  *             - \ref HWSEM0_MODULE
  *             - \ref EBI_MODULE
  *             - \ref SRAM0_MODULE
  *             - \ref SRAM1_MODULE
  *             - \ref ROM_MODULE
  *             - \ref TRA_MODULE
  *             - \ref DBG_MODULE
  *             - \ref CLKO_MODULE
  *             - \ref GTMR_MODULE
  *             - \ref GPA_MODULE
  *             - \ref GPB_MODULE
  *             - \ref GPC_MODULE
  *             - \ref GPD_MODULE
  *             - \ref GPE_MODULE
  *             - \ref GPF_MODULE
  *             - \ref GPG_MODULE
  *             - \ref GPH_MODULE
  *             - \ref GPI_MODULE
  *             - \ref GPJ_MODULE
  *             - \ref GPK_MODULE
  *             - \ref GPL_MODULE
  *             - \ref GPM_MODULE
  *             - \ref GPN_MODULE
  *             - \ref CA35_MODULE
  *             - \ref RTP_MODULE
  *             - \ref TAHB_MODULE
  *             - \ref LVRDB_MODULE
  *             - \ref DDR0_MODULE
  *             - \ref DDR6_MODULE
  *             - \ref CANFD0_MODULE
  *             - \ref CANFD1_MODULE
  *             - \ref CANFD2_MODULE
  *             - \ref CANFD3_MODULE
  *             - \ref SDH0_MODULE
  *             - \ref SDH1_MODULE
  *             - \ref NAND_MODULE
  *             - \ref USBD_MODULE
  *             - \ref USBH_MODULE
  *             - \ref HUSBH0_MODULE
  *             - \ref HUSBH1_MODULE
  *             - \ref GFX_MODULE
  *             - \ref VDEC_MODULE
  *             - \ref DCU_MODULE
  *             - \ref GMAC0_MODULE
  *             - \ref GMAC1_MODULE
  *             - \ref CCAP0_MODULE
  *             - \ref CCAP1_MODULE
  *             - \ref TMR0_MODULE
  *             - \ref TMR1_MODULE
  *             - \ref TMR2_MODULE
  *             - \ref TMR3_MODULE
  *             - \ref TMR4_MODULE
  *             - \ref TMR5_MODULE
  *             - \ref TMR6_MODULE
  *             - \ref TMR7_MODULE
  *             - \ref TMR8_MODULE
  *             - \ref TMR9_MODULE
  *             - \ref TMR10_MODULE
  *             - \ref TMR11_MODULE
  *             - \ref UART0_MODULE
  *             - \ref UART1_MODULE
  *             - \ref UART2_MODULE
  *             - \ref UART3_MODULE
  *             - \ref UART4_MODULE
  *             - \ref UART5_MODULE
  *             - \ref UART6_MODULE
  *             - \ref UART7_MODULE
  *             - \ref UART8_MODULE
  *             - \ref UART9_MODULE
  *             - \ref UART10_MODULE
  *             - \ref UART11_MODULE
  *             - \ref UART12_MODULE
  *             - \ref UART13_MODULE
  *             - \ref UART14_MODULE
  *             - \ref UART15_MODULE
  *             - \ref UART16_MODULE
  *             - \ref RTC_MODULE
  *             - \ref DDRP_MODULE
  *             - \ref KPI_MODULE
  *             - \ref I2C0_MODULE
  *             - \ref I2C1_MODULE
  *             - \ref I2C2_MODULE
  *             - \ref I2C3_MODULE
  *             - \ref I2C4_MODULE
  *             - \ref I2C5_MODULE
  *             - \ref QSPI0_MODULE
  *             - \ref QSPI1_MODULE
  *             - \ref SC0_MODULE
  *             - \ref SC1_MODULE
  *             - \ref WDT0_MODULE
  *             - \ref WDT1_MODULE
  *             - \ref WDT2_MODULE
  *             - \ref EPWM0_MODULE
  *             - \ref EPWM1_MODULE
  *             - \ref EPWM2_MODULE
  *             - \ref I2S0_MODULE
  *             - \ref I2S1_MODULE
  *             - \ref SSMCC_MODULE
  *             - \ref SSPCC_MODULE
  *             - \ref SPI0_MODULE
  *             - \ref SPI1_MODULE
  *             - \ref SPI2_MODULE
  *             - \ref SPI3_MODULE
  *             - \ref ECAP0_MODULE
  *             - \ref ECAP1_MODULE
  *             - \ref ECAP2_MODULE
  *             - \ref QEI0_MODULE
  *             - \ref QEI1_MODULE
  *             - \ref QEI2_MODULE
  *             - \ref ADC_MODULE
  *             - \ref EADC_MODULE
  * @return     None
  * @details    This function is used to disable module clock.
  */
void CLK_DisableModuleClock(uint32_t u32ModuleIdx)
{
    vu32 u32tmpVal = 0UL, u32tmpAddr = 0UL;

    u32tmpVal = ~(1UL << MODULE_IP_EN_Pos(u32ModuleIdx));
    u32tmpAddr = (uint32_t)&CLK->SYSCLK0;
    u32tmpAddr += ((MODULE_APBCLK(u32ModuleIdx) * 4UL));

    *((vu32 *)u32tmpAddr) &= u32tmpVal;
}

/**
  * @brief      Get VSI PLL Operation Mode
  * @param[in]  u32PllIdx is PLL clock index. Including :
  *             - \ref DDRPLL
  *             - \ref APLL
  *             - \ref EPLL
  *             - \ref VPLL
  * @return     VSI PLL Operation Mode
  * @details    This function get VSI PLL Operation Mode.
  */
uint32_t CLK_GetPLLOpMode(uint32_t u32PllIdx)
{
    return (CLK->PLL[u32PllIdx].CTL0 & CLK_PLLnCTL0_MODE_Msk) >> CLK_PLLnCTL0_MODE_Pos;
}

/**
  * @brief      This function check selected clock source status
  * @param[in]  u32ClkMask is selected clock source. Including :
  *             - \ref CLK_STATUS_HXTSTB_Msk
  *             - \ref CLK_STATUS_LXTSTB_Msk
  *             - \ref CLK_STATUS_HIRCSTB_Msk
  *             - \ref CLK_STATUS_LIRCSTB_Msk
  *             - \ref CLK_STATUS_CAPLLSTB_Msk
  *             - \ref CLK_STATUS_DDRPLLSTB_Msk
  *             - \ref CLK_STATUS_EPLLSTB_Msk
  *             - \ref CLK_STATUS_APLLSTB_Msk
  *             - \ref CLK_STATUS_VPLLSTB_Msk
  * @retval     0  clock is not stable
  * @retval     1  clock is stable
  * @details    To wait for clock ready by specified clock source stable flag or timeout (~300ms)
  */
uint32_t CLK_WaitClockReady(uint32_t u32ClkMask)
{
    int32_t i32TimeOutCnt = 2160000;
    uint32_t u32Ret = 1U;

    while ((CLK->STATUS & u32ClkMask) != u32ClkMask)
    {
        if (i32TimeOutCnt-- <= 0)
        {
            u32Ret = 0U;
            break;
        }
    }

    return u32Ret;
}

#if defined(USE_MA35D1_SUBM)
/**
  * @brief      Enable System Tick counter
  * @param[in]  u32ClkSrc is System Tick clock source. Including:
  *             - \ref CLK_CLKSEL0_RTPSTSEL_HXT
  *             - \ref CLK_CLKSEL0_RTPSTSEL_LXT
  *             - \ref CLK_CLKSEL0_RTPSTSEL_HXT_DIV2
  *             - \ref CLK_CLKSEL0_RTPSTSEL_SYSCLK1_DIV2
  *             - \ref CLK_CLKSEL0_RTPSTSEL_HIRC
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
    if (u32ClkSrc == CLK_CLKSEL0_RTPSTSEL_HIRC)
    {
        SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
    }
    else
    {
        CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_RTPSTSEL_Msk) | u32ClkSrc;
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
#endif

/**
  * @brief      Get CAPLL clock frequency
  * @param      None
  * @return     PLL frequency
  * @details    This function get PLL frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetCAPLLClockFreq(void)
{
    uint32_t u32M, u32N, u32P;
    uint32_t u32PllClk, u32RefClk;
    uint32_t val;

    val = CLK->PLL0CTL0;

    u32N = (val & CLK_PLL0CTL0_FBDIV_Msk);
    u32M = (val & CLK_PLL0CTL0_INDIV_Msk) >> (CLK_PLL0CTL0_INDIV_Pos);
    u32P = (val & CLK_PLL0CTL0_OUTDIV_Msk) >> (CLK_PLL0CTL0_OUTDIV_Pos);

    if (val & CLK_PLL0CTL0_BP_Msk)
    {
        u32PllClk = __HXT;
    }
    else
    {
        /* u32RefClk is shifted to avoid overflow */
        u32RefClk = __HXT / 100;

        /* Actual PLL output clock frequency */
        u32PllClk = ((u32RefClk * u32N) / ((0x1 << u32P) * u32M)) * 100;
    }

    return u32PllClk;
}

/**
  * @brief      Get Advanced PLL clock frequency
  * @param[in]  u32PllIdx is Advanced PLL clock index. Including :
  *             - \ref DDRPLL
  *             - \ref APLL
  *             - \ref EPLL
  *             - \ref VPLL
  * @return     Advanced PLL frequency
  * @details    This function get Advanced PLL frequency. The frequency unit is Hz.
  */
static uint32_t CLK_GetVSIPLLClockFreq(uint32_t u32PllIdx)
{
    uint32_t u32M, u32N, u32P, u32X, u32Mode;
    uint32_t u32CTLVal0, u32CTLVal1, u32PllClk = 0ul;

    /* Set PLL Operation mode. */
    u32CTLVal0 = CLK->PLL[u32PllIdx].CTL0;
    u32CTLVal1 = CLK->PLL[u32PllIdx].CTL1;

    /* If is power down state, it will return 0 directly. */
    if (u32CTLVal1 & CLK_PLLnCTL1_PD_Msk)
        return 0U;

    u32Mode = (u32CTLVal0 & CLK_PLLnCTL0_MODE_Msk) >> CLK_PLLnCTL0_MODE_Pos;

    u32N = (u32CTLVal0 & CLK_PLLnCTL0_FBDIV_Msk);
    u32M = (u32CTLVal0 & CLK_PLLnCTL0_INDIV_Msk)  >> CLK_PLLnCTL0_INDIV_Pos;
    u32P = (u32CTLVal1 & CLK_PLLnCTL1_OUTDIV_Msk) >> CLK_PLLnCTL1_OUTDIV_Pos;
    u32X = (u32CTLVal1 & CLK_PLLnCTL1_FRAC_Msk)  >> CLK_PLLnCTL1_FRAC_Pos;

    if (u32Mode == 0)
    {
        /* Actual PLL output clock frequency */
        u32PllClk = (__HXT / (u32P * u32M)) * u32N;
    }
    else if (u32Mode == 1)
    {
        /* Actual PLL output clock frequency */
        u32X = (((u32X * 1000) + 500) >> 24);
        u32PllClk = (__HXT / 1000) * ((u32N * 1000) + u32X) / (u32P * u32M);
    }
    else if (u32Mode == 2)
    {
        //uint32_t u32SR, u32FMOD, u32CTLVal2;

        //u32CTLVal2 = CLK->PLLCTL[u32PllIdx].REG2;
        //u32SR = (u32CTLVal0 & (CLK_PLLnCTL0_SSRATE_Msk)) >> CLK_PLLnCTL0_SSRATE_Pos;
        //u32FMOD = u32CTLVal2 & CLK_PLLnCTL2_SLOPE_Msk;

        /* Actual PLL output clock frequency */
        u32X = ((u32X * 1000) >> 24);
        u32PllClk = (__HXT / 1000) * ((u32N * 1000) + u32X) / (u32P * u32M);
    }

    return u32PllClk;
}

/* VSI-PLL Specification limits */
#define VSIPLL_FREF_MAX_FREQ        200000000U
#define VSIPLL_FREF_MIN_FREQ        1000000U

#define VSIPLL_FREFDIVM_MAX_FREQ    40000000U
#define VSIPLL_FREFDIVM_MIN_FREQ0   1000000U
#define VSIPLL_FREFDIVM_MIN_FREQ1   10000000U

#define VSIPLL_FCLK_MAX_FREQ        2400000000U
#define VSIPLL_FCLK_MIN_FREQ        600000000U

#define VSIPLL_FCLKO_MAX_FREQ       2400000000U
#define VSIPLL_FCLKO_MIN_FREQ       85700000U

#define VSIPLL_SPREAD_RANGE         194
#define VSIPLL_MODULATION_FREQ      50000

struct S_PLL_FREQ_MAP
{
    uint64_t freq;
    uint32_t mode;
    uint32_t ctl0_reg;
    uint32_t ctl1_reg;
    uint32_t ctl2_reg;
} ;

static const struct S_PLL_FREQ_MAP s_sVsiPllFreqTbl[] =
{
    { 1000000000, PLL_OPMODE_INTEGER, 0x307d, 0x10, 0 },            /* Mode0 */
    { 884736000,  PLL_OPMODE_FRACTIONAL, 0x41024, 0xdd2f1b11, 0 },   /* Mode1 */
    { 533000000,  PLL_OPMODE_SPREAD_SPECTRUM, 0x12b8102c, 0x6aaaab20, 0x12317 },  /* Mode2 */
    { }
};

static uint64_t CLK_CalPLLFreq_Mode0(uint64_t u64PllSrcClk, uint64_t u64PllFreq, uint32_t *u32Reg)
{
    uint32_t u32Tmp, u32Min, u32MinN, u32MinM, u32MinP;

    uint64_t u64PllClk;
    uint64_t u64Con1, u64Con2, u64Con3;

    /* Find best solution */
    u32Min = (uint32_t) - 1;
    u32MinM = 0UL;
    u32MinN = 0UL;
    u32MinP = 0UL;

    if ((u64PllFreq < VSIPLL_FCLKO_MIN_FREQ) || (u64PllFreq > VSIPLL_FCLKO_MAX_FREQ))
    {
        u32Reg[0] = s_sVsiPllFreqTbl[0].ctl0_reg;
        u32Reg[1] = s_sVsiPllFreqTbl[0].ctl1_reg;
        u64PllClk = s_sVsiPllFreqTbl[0].freq;
    }
    else
    {
        uint32_t u32TmpM, u32TmpN, u32TmpP;
        uint32_t u32RngMinN, u32RngMinM, u32RngMinP;
        uint32_t u32RngMaxN, u32RngMaxM, u32RngMaxP;

        /* Find best solution */
        u32RngMinM = 1UL;
        u32RngMaxM = 63UL;

        u32RngMinM = ((u64PllSrcClk / VSIPLL_FREFDIVM_MAX_FREQ) > 1) ?
                     (u64PllSrcClk / VSIPLL_FREFDIVM_MAX_FREQ) : 1;
        u32RngMaxM = ((u64PllSrcClk / VSIPLL_FREFDIVM_MIN_FREQ0) < u32RngMaxM) ?
                     (u64PllSrcClk / VSIPLL_FREFDIVM_MIN_FREQ0) : u32RngMaxM;

        for (u32TmpM = u32RngMinM; u32TmpM < (u32RngMaxM + 1); u32TmpM++)
        {
            u64Con1 = u64PllSrcClk / u32TmpM;

            u32RngMinN = 16UL;
            u32RngMaxN = 2047UL;

            u32RngMinN = ((VSIPLL_FCLK_MIN_FREQ / u64Con1) > u32RngMinN) ?
                         (VSIPLL_FCLK_MIN_FREQ / u64Con1) : u32RngMinN;
            u32RngMaxN = ((VSIPLL_FCLK_MAX_FREQ / u64Con1) < u32RngMaxN) ?
                         (VSIPLL_FCLK_MAX_FREQ / u64Con1) : u32RngMaxN;

            for (u32TmpN = u32RngMinN; u32TmpN < (u32RngMaxN + 1); u32TmpN++)
            {
                u64Con2 = u64Con1 * u32TmpN;

                u32RngMinP = 1UL;
                u32RngMaxP = 7UL;

                u32RngMinP = ((u64Con2 / VSIPLL_FCLKO_MAX_FREQ) > 1) ? (u64Con2 /
                             VSIPLL_FCLKO_MAX_FREQ) : 1;
                u32RngMaxP = ((u64Con2 / VSIPLL_FCLKO_MIN_FREQ) < u32RngMaxP) ?
                             (u64Con2 / VSIPLL_FCLKO_MIN_FREQ) : u32RngMaxP;

                for (u32TmpP = u32RngMinP; u32TmpP < (u32RngMaxP + 1); u32TmpP++)
                {
                    u64Con3 = u64Con2 / u32TmpP;
                    if (u64Con3 > u64PllFreq)
                        u32Tmp = u64Con3 - u64PllFreq;
                    else
                        u32Tmp = u64PllFreq - u64Con3;

                    if (u32Tmp < u32Min)
                    {
                        u32Min = u32Tmp;
                        u32MinM = u32TmpM;
                        u32MinN = u32TmpN;
                        u32MinP = u32TmpP;

                        /* Break when get good results */
                        if (u32Min == 0UL)
                        {
                            u32Reg[0] = (u32MinM << 12) | (u32MinN);
                            u32Reg[1] = (u32MinP << 4);

                            return ((u64PllSrcClk * u32MinN) / (u32MinP * u32MinM));
                        }
                    }
                }
            }

        }

        /* Enable and apply new PLL setting. */
        u32Reg[0] = (u32MinM << 12) | (u32MinN);
        u32Reg[1] = (u32MinP << 4);

        /* Actual PLL output clock frequency */
        u64PllClk = (u64PllSrcClk * u32MinN) / (u32MinP * u32MinM);
    }

    return u64PllClk;
}


static uint64_t CLK_CalPLLFreq_Mode1(uint64_t u64PllSrcClk, uint64_t u64PllFreq, uint32_t *u32Reg)
{
    uint64_t u64X, u64N, u64M, u64P, u64tmp, u64tmpP, u64tmpM;
    uint64_t u64PllClk, u64FCLKO;
    uint32_t u32FRAC, i;

    // check condition 1
    if ((u64PllSrcClk > VSIPLL_FREF_MAX_FREQ) || (u64PllSrcClk < VSIPLL_FREF_MIN_FREQ))
    {
        // Fref is incorrect, return fail
        return 0;
    }

    // check condition 4
    if (u64PllFreq < VSIPLL_FCLKO_MIN_FREQ)
    {
        // Adjust u64FCLKO
        u64FCLKO = 0;

        for (i = 2; i < 100; i++)
        {
            u64tmp = (i * u64PllFreq);
            if (u64tmp > VSIPLL_FCLKO_MIN_FREQ)
            {
                u64FCLKO = u64tmp;
                break;
            }
        }

        if (u64FCLKO == 0) return 0;
    }
    else if (u64PllFreq >= VSIPLL_FCLKO_MAX_FREQ)
    {
        u32Reg[0] = 0x30FA;
        u32Reg[1] = (0x2 << 4);
        u64PllClk = 1000000000;
        return u64PllClk;
    }
    else
        u64FCLKO = u64PllFreq;

    // Find P
    u64P = 0;
    for (i = 1; i < 8; i++)
    {
        u64tmpP =  i * u64FCLKO;
        // it should be condition 3
        if ((u64tmpP <= VSIPLL_FCLKO_MAX_FREQ) && (u64tmpP >= 600000000))
        {
            u64P = i;
            break;
        }
    }

    // No reasonable P is found, return fail.
    if (u64P == 0)  return 0;

    // Find M
    u64M = 0; // Initialize it, and use it to judge reasonable M is found or not
    for (i = 1; i < 64; i++)
    {
        u64tmpM = u64PllSrcClk / i;
        if ((u64tmpM <= 40000000) && (u64tmpM >= 10000000)) // condition 2
        {
            u64M = i;
            break;
        }
    }

    if (u64M == 0)
    {
        // No reasonable M is found
        return 0;
    }

    u64tmp = (u64FCLKO * u64P * u64M * 1000) / u64PllSrcClk;
    u64N = u64tmp / 1000;
    u64X = u64tmp % 1000;
    u32FRAC = ((u64X << 24) + 500) / 1000;

    u32Reg[0] = (u64M << 12) | (u64N);
    u32Reg[1] = (u64P << 4) | (u32FRAC << 8);

    /* Actual PLL output clock frequency */
    u64PllClk = (u64PllSrcClk * u64tmp) / u64P / u64M / 1000;

    return u64PllClk;
}

static uint64_t CLK_CalPLLFreq_Mode2(uint64_t PllSrcClk, uint64_t u64PllFreq, uint32_t u32SR, uint32_t u32Fmod, uint32_t *u32Reg)
{
    uint64_t u64PllClk;
    uint64_t u64X, u64N, u64M, u64P, u64tmp, u64tmpP, u64tmpM;
    uint64_t u64FCLKO, u64SSRATE, u64SLOPE;
    uint32_t u32FRAC, i;

    // check condition 1
    if ((PllSrcClk > 200000000) || (PllSrcClk < 1000000))
    {
        // Fref is incorrect, return fail case
        return 0;
    }

    // check condition 4
    if (u64PllFreq < 85700000)
    {
        u64FCLKO = 0;
        for (i = 2; i < 8; i++)
        {
            u64tmp = (i * u64PllFreq);
            if (u64tmp > 85700000)
            {
                u64FCLKO = u64tmp;
            }
        }

        if (u64FCLKO == 0) return 0;
    }
    else if (u64PllFreq >= 2400000000)
    {
        u32Reg[0] = 0x30FA;
        u32Reg[1] = (0x2 << 4);
        u64PllClk = 1000000000;
        return u64PllClk;
    }
    else
        u64FCLKO = u64PllFreq;

    // Find P
    u64P = 0;
    for (i = 1; i < 8; i++)
    {
        u64tmpP =  i * u64FCLKO;
        if ((u64tmpP <= 2400000000) && (u64tmpP >= 600000000))
        {
            u64P = i;
            break;
        }
    }

    // No reasonable P is found, return fail.
    if (u64P == 0)  return 0;

    // Find M
    u64M = 0; // Initialize it, and use it to judge reasonable M is found or not
    for (i = 1; i < 64; i++)
    {
        u64tmpM = PllSrcClk / i;
        if ((u64tmpM <= 40000000) && (u64tmpM >= 10000000))  // condition 2
        {
            u64M = i;
            break;
        }
    }

    if (u64M == 0)   // No reasonable M is found
    {
        return 0;
    }

    u64tmp = (u64FCLKO * u64P * u64M * 1000) / PllSrcClk;
    u64N = u64tmp / 1000;
    u64X = u64tmp % 1000;
    u32FRAC = ((u64X << 24) + 500) / 1000;

    u64SSRATE = ((PllSrcClk >> 1) / (u32Fmod * 2)) - 1;
    u64SLOPE = ((u64tmp * u32SR / u64SSRATE) << 24) / 100 / 1000;

    u32Reg[0] = (u64SSRATE << 20) | (u64M << 12) | (u64N);
    u32Reg[1] = (u64P << 4) | (u32FRAC << 8);
    u32Reg[2] = u64SLOPE;

    /* Actual PLL output clock frequency */
    u64PllClk = (PllSrcClk * u64tmp) / u64P / u64M / 1000;

    return u64PllClk;
}

/**
  * @brief      Get Advanced PLL clock frequency
  * @param[in]  u32PllIdx is Advanced PLL clock index. Including :
  *             - \ref CAPLL
  *             - \ref
  *             - \ref DDRPLL
  *             - \ref APLL
  *             - \ref EPLL
  *             - \ref VPLL
  * @return     Advanced PLL frequency
  * @details    This function get Advanced PLL frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetPLLClockFreq(uint32_t u32PllIdx)
{
    uint32_t u32Pllout = 0;

    switch (u32PllIdx)
    {
    /* SMIC */
    case CAPLL:
        u32Pllout = CLK_GetCAPLLClockFreq();
        break;

    case SYSPLL:
        u32Pllout = SYSPLLFREQCLK;
        break;

    /* VSI */
    case DDRPLL:
    case EPLL:
    case APLL:
    case VPLL:
        u32Pllout = CLK_GetVSIPLLClockFreq(u32PllIdx);
        break;

    default:
        break;
    }

    return u32Pllout;
}

/* CPU-PLL: 1000MHz 800MHz 700MHz */
static const struct S_PLL_FREQ_MAP s_au32CAPLLMap[] =
{
    { 1000000000u, PLL_OPMODE_INTEGER, 0x000006FA, 0, 0 },  /* 1000 MHz */
    {  800000000u, PLL_OPMODE_INTEGER, 0x00000364, 0, 0 },  /*  800 MHz */
    {  700000000u, PLL_OPMODE_INTEGER, 0x000006AF, 0, 0 },  /*  700 MHz */
};
#define ARRARSIZE_CAPLLPLLMAP  (sizeof(s_au32CAPLLMap)/sizeof(struct S_PLL_FREQ_MAP))

static uint64_t CLK_SetCAPLLClockFreq(uint32_t u32PllIdx, uint32_t u32OpMode, uint64_t PllSrcClk, uint64_t u64PllFreq)
{
    // TODO
    uint32_t i;

    for (i = 0; i < ARRARSIZE_CAPLLPLLMAP; i++)
    {
        if ((u32OpMode == PLL_OPMODE_INTEGER) && (u64PllFreq == s_au32CAPLLMap[i].freq))
        {
            CLK->PLL0CTL0 = s_au32CAPLLMap[i].ctl0_reg;
            return s_au32CAPLLMap[i].freq;
        }
    }

    return 0;
}

static uint64_t CLK_SetVSIPLLFreq(uint32_t u32PllIdx, uint32_t u32OpMode, uint64_t PllSrcClk, uint64_t u64PllFreq)
{
    uint32_t u32CTLVal0, u32CTLVal1, u32CTLVal2;
    uint32_t u32Reg[3] = {0};
    uint64_t u64PllClk = 0;

    /* Set PLL Operation mode. */
    u32CTLVal0 = CLK->PLL[u32PllIdx].CTL0;
    u32CTLVal1 = CLK->PLL[u32PllIdx].CTL1;
    u32CTLVal2 = CLK->PLL[u32PllIdx].CTL2;

    /* Set PLL Operation mode. */
    u32CTLVal0 = (u32CTLVal0 & ~CLK_PLLnCTL0_MODE_Msk) | (u32OpMode << CLK_PLLnCTL0_MODE_Pos);

    if (u32OpMode == PLL_OPMODE_INTEGER)
    {
        u64PllClk  = CLK_CalPLLFreq_Mode0(PllSrcClk, u64PllFreq, &u32Reg[0]);
        u32CTLVal0 = (u32CTLVal0 & ~(CLK_PLLnCTL0_INDIV_Msk | CLK_PLLnCTL0_FBDIV_Msk)) | u32Reg[0];
        u32CTLVal1 = (u32CTLVal1 & ~CLK_PLLnCTL1_OUTDIV_Msk) | u32Reg[1];
    }
    else if (u32OpMode == PLL_OPMODE_FRACTIONAL)
    {
        u64PllClk = CLK_CalPLLFreq_Mode1(PllSrcClk, u64PllFreq, &u32Reg[0]);
        u32CTLVal0 = (u32CTLVal0 & ~(CLK_PLLnCTL0_INDIV_Msk | CLK_PLLnCTL0_FBDIV_Msk)) | u32Reg[0];
        u32CTLVal1 = (u32CTLVal1 & ~(CLK_PLLnCTL1_OUTDIV_Msk | CLK_PLLnCTL1_FRAC_Msk)) | u32Reg[1];
    }
    else if (u32OpMode == PLL_OPMODE_SPREAD_SPECTRUM)
    {
        u64PllClk = CLK_CalPLLFreq_Mode2(PllSrcClk, u64PllFreq, 50000, 194, &u32Reg[0]); /* 50 khz, 1.94% */
        u32CTLVal0 = (u32CTLVal0 & ~(CLK_PLLnCTL0_SSRATE_Msk | CLK_PLLnCTL0_INDIV_Msk | CLK_PLLnCTL0_FBDIV_Msk)) | u32Reg[0];
        u32CTLVal1 = (u32CTLVal1 & ~(CLK_PLLnCTL1_OUTDIV_Msk | CLK_PLLnCTL1_FRAC_Msk)) | u32Reg[1];
        u32CTLVal2 = u32Reg[2];
    }
    else
    {
        return 0;
    }

    CLK->PLL[u32PllIdx].CTL0 = u32CTLVal0;
    CLK->PLL[u32PllIdx].CTL1 = u32CTLVal1 & (~CLK_PLLnCTL1_PD_Msk);
    CLK->PLL[u32PllIdx].CTL2 = u32CTLVal2;

    return u64PllClk;
}

uint64_t CLK_SetPLLFreq(uint32_t u32PllIdx, uint32_t u32OpMode, uint64_t PllSrcClk, uint64_t u64PllFreq)
{
    uint64_t u64Pllout = 0;

    switch (u32PllIdx)
    {
    /* SMIC */
    case CAPLL:
        u64Pllout = CLK_SetCAPLLClockFreq(u32PllIdx, u32OpMode, PllSrcClk, u64PllFreq);
        break;

    case SYSPLL:
        u64Pllout = SYSPLLFREQCLK;
        break;

    /* VSI */
    case DDRPLL:
    case EPLL:
    case APLL:
    case VPLL:
        u64Pllout = CLK_SetVSIPLLFreq(u32PllIdx, u32OpMode, PllSrcClk, u64PllFreq);
        break;

    default:
        break;
    }

    return u64Pllout;
}

/**
  * @brief      Get selected module clock source
  * @param[in]  u32ModuleIdx is module index.
  *             - \ref PDMA0_MODULE
  *             - \ref PDMA1_MODULE
  *             - \ref PDMA2_MODULE
  *             - \ref PDMA3_MODULE
  *             - \ref WH0_MODULE
  *             - \ref WH1_MODULE
  *             - \ref HWSEM0_MODULE
  *             - \ref EBI_MODULE
  *             - \ref SRAM0_MODULE
  *             - \ref SRAM1_MODULE
  *             - \ref ROM_MODULE
  *             - \ref TRA_MODULE
  *             - \ref DBG_MODULE
  *             - \ref CLKO_MODULE
  *             - \ref GTMR_MODULE
  *             - \ref GPA_MODULE
  *             - \ref GPB_MODULE
  *             - \ref GPC_MODULE
  *             - \ref GPD_MODULE
  *             - \ref GPE_MODULE
  *             - \ref GPF_MODULE
  *             - \ref GPG_MODULE
  *             - \ref GPH_MODULE
  *             - \ref GPI_MODULE
  *             - \ref GPJ_MODULE
  *             - \ref GPK_MODULE
  *             - \ref GPL_MODULE
  *             - \ref GPM_MODULE
  *             - \ref GPN_MODULE
  *             - \ref CA35_MODULE
  *             - \ref RTP_MODULE
  *             - \ref TAHB_MODULE
  *             - \ref LVRDB_MODULE
  *             - \ref DDR0_MODULE
  *             - \ref DDR6_MODULE
  *             - \ref CANFD0_MODULE
  *             - \ref CANFD1_MODULE
  *             - \ref CANFD2_MODULE
  *             - \ref CANFD3_MODULE
  *             - \ref SDH0_MODULE
  *             - \ref SDH1_MODULE
  *             - \ref NAND_MODULE
  *             - \ref USBD_MODULE
  *             - \ref USBH_MODULE
  *             - \ref HUSBH0_MODULE
  *             - \ref HUSBH1_MODULE
  *             - \ref GFX_MODULE
  *             - \ref VDEC_MODULE
  *             - \ref DCU_MODULE
  *             - \ref GMAC0_MODULE
  *             - \ref GMAC1_MODULE
  *             - \ref CCAP0_MODULE
  *             - \ref CCAP1_MODULE
  *             - \ref TMR0_MODULE
  *             - \ref TMR1_MODULE
  *             - \ref TMR2_MODULE
  *             - \ref TMR3_MODULE
  *             - \ref TMR4_MODULE
  *             - \ref TMR5_MODULE
  *             - \ref TMR6_MODULE
  *             - \ref TMR7_MODULE
  *             - \ref TMR8_MODULE
  *             - \ref TMR9_MODULE
  *             - \ref TMR10_MODULE
  *             - \ref TMR11_MODULE
  *             - \ref UART0_MODULE
  *             - \ref UART1_MODULE
  *             - \ref UART2_MODULE
  *             - \ref UART3_MODULE
  *             - \ref UART4_MODULE
  *             - \ref UART5_MODULE
  *             - \ref UART6_MODULE
  *             - \ref UART7_MODULE
  *             - \ref UART8_MODULE
  *             - \ref UART9_MODULE
  *             - \ref UART10_MODULE
  *             - \ref UART11_MODULE
  *             - \ref UART12_MODULE
  *             - \ref UART13_MODULE
  *             - \ref UART14_MODULE
  *             - \ref UART15_MODULE
  *             - \ref UART16_MODULE
  *             - \ref RTC_MODULE
  *             - \ref DDRP_MODULE
  *             - \ref KPI_MODULE
  *             - \ref I2C0_MODULE
  *             - \ref I2C1_MODULE
  *             - \ref I2C2_MODULE
  *             - \ref I2C3_MODULE
  *             - \ref I2C4_MODULE
  *             - \ref I2C5_MODULE
  *             - \ref QSPI0_MODULE
  *             - \ref QSPI1_MODULE
  *             - \ref SC0_MODULE
  *             - \ref SC1_MODULE
  *             - \ref WDT0_MODULE
  *             - \ref WDT1_MODULE
  *             - \ref WDT2_MODULE
  *             - \ref EPWM0_MODULE
  *             - \ref EPWM1_MODULE
  *             - \ref EPWM2_MODULE
  *             - \ref I2S0_MODULE
  *             - \ref I2S1_MODULE
  *             - \ref SSMCC_MODULE
  *             - \ref SSPCC_MODULE
  *             - \ref SPI0_MODULE
  *             - \ref SPI1_MODULE
  *             - \ref SPI2_MODULE
  *             - \ref SPI3_MODULE
  *             - \ref ECAP0_MODULE
  *             - \ref ECAP1_MODULE
  *             - \ref ECAP2_MODULE
  *             - \ref QEI0_MODULE
  *             - \ref QEI1_MODULE
  *             - \ref QEI2_MODULE
  *             - \ref ADC_MODULE
  *             - \ref EADC_MODULE
  * @return     Selected module clock source setting
  * @details    This function get selected module clock source.
  */
uint32_t CLK_GetModuleClockSource(uint32_t u32ModuleIdx)
{
    uint32_t u32sel = 0;
    uint32_t u32SelTbl[5] = {0x0, 0x4, 0x8, 0xC, 0x10};

    /* Get clock source selection setting */
    if (MODULE_CLKSEL_Msk(u32ModuleIdx) != MODULE_NoMsk)
    {
        /* Get clock select control register address */
        u32sel = (uint32_t)&CLK->CLKSEL0 + (u32SelTbl[MODULE_CLKSEL(u32ModuleIdx)]);
        /* Get clock source selection setting */
        return ((M32(u32sel) & (MODULE_CLKSEL_Msk(u32ModuleIdx) << MODULE_CLKSEL_Pos(u32ModuleIdx))) >> MODULE_CLKSEL_Pos(u32ModuleIdx));
    }
    else
        return 0;
}

/**
  * @brief      Get selected module clock divider number
  * @param[in]  u32ModuleIdx is module index.
  *             - \ref PDMA0_MODULE
  *             - \ref PDMA1_MODULE
  *             - \ref PDMA2_MODULE
  *             - \ref PDMA3_MODULE
  *             - \ref WH0_MODULE
  *             - \ref WH1_MODULE
  *             - \ref HWSEM0_MODULE
  *             - \ref EBI_MODULE
  *             - \ref SRAM0_MODULE
  *             - \ref SRAM1_MODULE
  *             - \ref ROM_MODULE
  *             - \ref TRA_MODULE
  *             - \ref DBG_MODULE
  *             - \ref CLKO_MODULE
  *             - \ref GTMR_MODULE
  *             - \ref GPA_MODULE
  *             - \ref GPB_MODULE
  *             - \ref GPC_MODULE
  *             - \ref GPD_MODULE
  *             - \ref GPE_MODULE
  *             - \ref GPF_MODULE
  *             - \ref GPG_MODULE
  *             - \ref GPH_MODULE
  *             - \ref GPI_MODULE
  *             - \ref GPJ_MODULE
  *             - \ref GPK_MODULE
  *             - \ref GPL_MODULE
  *             - \ref GPM_MODULE
  *             - \ref GPN_MODULE
  *             - \ref CA35_MODULE
  *             - \ref RTP_MODULE
  *             - \ref TAHB_MODULE
  *             - \ref LVRDB_MODULE
  *             - \ref DDR0_MODULE
  *             - \ref DDR6_MODULE
  *             - \ref CANFD0_MODULE
  *             - \ref CANFD1_MODULE
  *             - \ref CANFD2_MODULE
  *             - \ref CANFD3_MODULE
  *             - \ref SDH0_MODULE
  *             - \ref SDH1_MODULE
  *             - \ref NAND_MODULE
  *             - \ref USBD_MODULE
  *             - \ref USBH_MODULE
  *             - \ref HUSBH0_MODULE
  *             - \ref HUSBH1_MODULE
  *             - \ref GFX_MODULE
  *             - \ref VDEC_MODULE
  *             - \ref DCU_MODULE
  *             - \ref GMAC0_MODULE
  *             - \ref GMAC1_MODULE
  *             - \ref CCAP0_MODULE
  *             - \ref CCAP1_MODULE
  *             - \ref TMR0_MODULE
  *             - \ref TMR1_MODULE
  *             - \ref TMR2_MODULE
  *             - \ref TMR3_MODULE
  *             - \ref TMR4_MODULE
  *             - \ref TMR5_MODULE
  *             - \ref TMR6_MODULE
  *             - \ref TMR7_MODULE
  *             - \ref TMR8_MODULE
  *             - \ref TMR9_MODULE
  *             - \ref TMR10_MODULE
  *             - \ref TMR11_MODULE
  *             - \ref UART0_MODULE
  *             - \ref UART1_MODULE
  *             - \ref UART2_MODULE
  *             - \ref UART3_MODULE
  *             - \ref UART4_MODULE
  *             - \ref UART5_MODULE
  *             - \ref UART6_MODULE
  *             - \ref UART7_MODULE
  *             - \ref UART8_MODULE
  *             - \ref UART9_MODULE
  *             - \ref UART10_MODULE
  *             - \ref UART11_MODULE
  *             - \ref UART12_MODULE
  *             - \ref UART13_MODULE
  *             - \ref UART14_MODULE
  *             - \ref UART15_MODULE
  *             - \ref UART16_MODULE
  *             - \ref RTC_MODULE
  *             - \ref DDRP_MODULE
  *             - \ref KPI_MODULE
  *             - \ref I2C0_MODULE
  *             - \ref I2C1_MODULE
  *             - \ref I2C2_MODULE
  *             - \ref I2C3_MODULE
  *             - \ref I2C4_MODULE
  *             - \ref I2C5_MODULE
  *             - \ref QSPI0_MODULE
  *             - \ref QSPI1_MODULE
  *             - \ref SC0_MODULE
  *             - \ref SC1_MODULE
  *             - \ref WDT0_MODULE
  *             - \ref WDT1_MODULE
  *             - \ref WDT2_MODULE
  *             - \ref EPWM0_MODULE
  *             - \ref EPWM1_MODULE
  *             - \ref EPWM2_MODULE
  *             - \ref I2S0_MODULE
  *             - \ref I2S1_MODULE
  *             - \ref SSMCC_MODULE
  *             - \ref SSPCC_MODULE
  *             - \ref SPI0_MODULE
  *             - \ref SPI1_MODULE
  *             - \ref SPI2_MODULE
  *             - \ref SPI3_MODULE
  *             - \ref ECAP0_MODULE
  *             - \ref ECAP1_MODULE
  *             - \ref ECAP2_MODULE
  *             - \ref QEI0_MODULE
  *             - \ref QEI1_MODULE
  *             - \ref QEI2_MODULE
  *             - \ref ADC_MODULE
  *             - \ref EADC_MODULE
  * @return     Selected module clock divider number setting
  * @details    This function get selected module clock divider number.
  */
uint32_t CLK_GetModuleClockDivider(uint32_t u32ModuleIdx)
{
    vu32 u32div = 0;
    uint32_t u32DivTbl[5] = {0x0, 0x4, 0xc, 0xc, 0x10};

    if (MODULE_CLKDIV_Msk(u32ModuleIdx) != MODULE_NoMsk)
    {
        if (u32ModuleIdx == KPI_MODULE)
        {
            u32div = (CLK->CLKDIV4 & CLK_CLKDIV4_KPIDIV_Msk) >> CLK_CLKDIV4_KPIDIV_Pos;
            return u32div;
        }
        else if (u32ModuleIdx == ADC_MODULE)
        {
            u32div = (CLK->CLKDIV4 & CLK_CLKDIV4_ADCDIV_Msk) >> CLK_CLKDIV4_ADCDIV_Pos;
            return u32div;
        }
        else
        {
            /* Get clock divider control register address */
            u32div = (vu32)&CLK->CLKDIV0 + (u32DivTbl[MODULE_CLKDIV(u32ModuleIdx)]);
            /* Get clock divider number setting */
            return ((M32(u32div) & (MODULE_CLKDIV_Msk(u32ModuleIdx) << MODULE_CLKDIV_Pos(u32ModuleIdx))) >> MODULE_CLKDIV_Pos(u32ModuleIdx));
        }
    }
    else
        return 0;
}


/*@}*/ /* end of group CLK_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group CLK_Driver */

/*@}*/ /* end of group Standard_Driver */

