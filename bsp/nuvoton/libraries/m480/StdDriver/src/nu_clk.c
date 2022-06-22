/**************************************************************************//**
 * @file     clk.c
 * @version  V3.00
 * @brief    M480 series CLK driver source file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
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
  *             - \ref CLK_CLKSEL1_CLKOSEL_HXT
  *             - \ref CLK_CLKSEL1_CLKOSEL_LXT
  *             - \ref CLK_CLKSEL1_CLKOSEL_HCLK
  *             - \ref CLK_CLKSEL1_CLKOSEL_HIRC
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

/**
  * @brief      Enter to Power-down mode
  * @param      None
  * @return     None
  * @details    This function is used to let system enter to Power-down mode. \n
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_PowerDown(void)
{
    uint32_t u32HIRCTRIMCTL;

    /* Set the processor uses deep sleep as its low power mode */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Set system Power-down enabled */
    CLK->PWRCTL |= (CLK_PWRCTL_PDEN_Msk);

    /* Store HIRC control register */
    u32HIRCTRIMCTL = SYS->IRCTCTL;

    /* Disable HIRC auto trim */
    SYS->IRCTCTL &= (~SYS_IRCTCTL_FREQSEL_Msk);

    /* Chip enter Power-down mode after CPU run WFI instruction */
    __WFI();

    /* Restore HIRC control register */
    SYS->IRCTCTL = u32HIRCTRIMCTL;
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
uint32_t CLK_GetHXTFreq(void)
{
    uint32_t u32Freq;

    if((CLK->PWRCTL & CLK_PWRCTL_HXTEN_Msk) == CLK_PWRCTL_HXTEN_Msk)
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
    if((CLK->PWRCTL & CLK_PWRCTL_LXTEN_Msk) == CLK_PWRCTL_LXTEN_Msk)
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
  * @brief      Get PCLK0 frequency
  * @param      None
  * @return     PCLK0 frequency
  * @details    This function get PCLK0 frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetPCLK0Freq(void)
{
    uint32_t u32Freq;
    SystemCoreClockUpdate();

    if((CLK->PCLKDIV & CLK_PCLKDIV_APB0DIV_Msk) == CLK_PCLKDIV_APB0DIV_DIV1)
    {
        u32Freq = SystemCoreClock;
    }
    else if((CLK->PCLKDIV & CLK_PCLKDIV_APB0DIV_Msk) == CLK_PCLKDIV_APB0DIV_DIV2)
    {
        u32Freq = SystemCoreClock / 2UL;
    }
    else if((CLK->PCLKDIV & CLK_PCLKDIV_APB0DIV_Msk) == CLK_PCLKDIV_APB0DIV_DIV4)
    {
        u32Freq = SystemCoreClock / 4UL;
    }
    else if((CLK->PCLKDIV & CLK_PCLKDIV_APB0DIV_Msk) == CLK_PCLKDIV_APB0DIV_DIV8)
    {
        u32Freq = SystemCoreClock / 8UL;
    }
    else if((CLK->PCLKDIV & CLK_PCLKDIV_APB0DIV_Msk) == CLK_PCLKDIV_APB0DIV_DIV16)
    {
        u32Freq = SystemCoreClock / 16UL;
    }
    else
    {
        u32Freq = SystemCoreClock;
    }

    return u32Freq;
}


/**
  * @brief      Get PCLK1 frequency
  * @param      None
  * @return     PCLK1 frequency
  * @details    This function get PCLK1 frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetPCLK1Freq(void)
{
    uint32_t u32Freq;
    SystemCoreClockUpdate();

    if((CLK->PCLKDIV & CLK_PCLKDIV_APB1DIV_Msk) == CLK_PCLKDIV_APB1DIV_DIV1)
    {
        u32Freq = SystemCoreClock;
    }
    else if((CLK->PCLKDIV & CLK_PCLKDIV_APB1DIV_Msk) == CLK_PCLKDIV_APB1DIV_DIV2)
    {
        u32Freq = SystemCoreClock / 2UL;
    }
    else if((CLK->PCLKDIV & CLK_PCLKDIV_APB1DIV_Msk) == CLK_PCLKDIV_APB1DIV_DIV4)
    {
        u32Freq = SystemCoreClock / 4UL;
    }
    else if((CLK->PCLKDIV & CLK_PCLKDIV_APB1DIV_Msk) == CLK_PCLKDIV_APB1DIV_DIV8)
    {
        u32Freq = SystemCoreClock / 8UL;
    }
    else if((CLK->PCLKDIV & CLK_PCLKDIV_APB1DIV_Msk) == CLK_PCLKDIV_APB1DIV_DIV16)
    {
        u32Freq = SystemCoreClock / 16UL;
    }
    else
    {
        u32Freq = SystemCoreClock;
    }

    return u32Freq;
}


/**
  * @brief      Get HCLK frequency
  * @param      None
  * @return     HCLK frequency
  * @details    This function get HCLK frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetHCLKFreq(void)
{
    SystemCoreClockUpdate();
    return SystemCoreClock;
}


/**
  * @brief      Get CPU frequency
  * @param      None
  * @return     CPU frequency
  * @details    This function get CPU frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetCPUFreq(void)
{
    SystemCoreClockUpdate();
    return SystemCoreClock;
}


/**
  * @brief      Set HCLK frequency
  * @param[in]  u32Hclk is HCLK frequency. The range of u32Hclk is running up to 192MHz.
  * @return     HCLK frequency
  * @details    This function is used to set HCLK frequency. The frequency unit is Hz. \n
  *             The register write-protection function should be disabled before using this function.
  */
uint32_t CLK_SetCoreClock(uint32_t u32Hclk)
{
    uint32_t u32HIRCSTB;

    /* Read HIRC clock source stable flag */
    u32HIRCSTB = CLK->STATUS & CLK_STATUS_HIRCSTB_Msk;

    /* The range of u32Hclk is running up to 192 MHz */
    if(u32Hclk > FREQ_192MHZ)
    {
        u32Hclk = FREQ_192MHZ;
    }

    /* Switch HCLK clock source to HIRC clock for safe */
    CLK->PWRCTL |= CLK_PWRCTL_HIRCEN_Msk;
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);
    CLK->CLKSEL0 |= CLK_CLKSEL0_HCLKSEL_Msk;
    CLK->CLKDIV0 &= (~CLK_CLKDIV0_HCLKDIV_Msk);

    /* Configure PLL setting if HXT clock is enabled */
    if((CLK->PWRCTL & CLK_PWRCTL_HXTEN_Msk) == CLK_PWRCTL_HXTEN_Msk)
    {
        u32Hclk = CLK_EnablePLL(CLK_PLLCTL_PLLSRC_HXT, u32Hclk);
    }
    /* Configure PLL setting if HXT clock is not enabled */
    else
    {
        u32Hclk = CLK_EnablePLL(CLK_PLLCTL_PLLSRC_HIRC, u32Hclk);

        /* Read HIRC clock source stable flag */
        u32HIRCSTB = CLK->STATUS & CLK_STATUS_HIRCSTB_Msk;
    }

    /* Select HCLK clock source to PLL,
       and update system core clock
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
    uint32_t u32HIRCSTB;

    /* Read HIRC clock source stable flag */
    u32HIRCSTB = CLK->STATUS & CLK_STATUS_HIRCSTB_Msk;

    /* Switch to HIRC for Safe. Avoid HCLK too high when applying new divider. */
    CLK->PWRCTL |= CLK_PWRCTL_HIRCEN_Msk;
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);
    CLK->CLKSEL0 = (CLK->CLKSEL0 & (~CLK_CLKSEL0_HCLKSEL_Msk)) | CLK_CLKSEL0_HCLKSEL_HIRC;

    /* Apply new Divider */
    CLK->CLKDIV0 = (CLK->CLKDIV0 & (~CLK_CLKDIV0_HCLKDIV_Msk)) | u32ClkDiv;

    /* Switch HCLK to new HCLK source */
    CLK->CLKSEL0 = (CLK->CLKSEL0 & (~CLK_CLKSEL0_HCLKSEL_Msk)) | u32ClkSrc;

    /* Update System Core Clock */
    SystemCoreClockUpdate();

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
  * |Module index        |Clock source                           |Divider                        |
  * | :----------------  | :-----------------------------------  | :--------------------------   |
  * |\ref CCAP_MODULE    |\ref CLK_CLKSEL0_CCAPSEL_HXT           |\ref CLK_CLKDIV3_CCAP(x)       |
  * |\ref CCAP_MODULE    |\ref CLK_CLKSEL0_CCAPSEL_PLL           |\ref CLK_CLKDIV3_CCAP(x)       |
  * |\ref CCAP_MODULE    |\ref CLK_CLKSEL0_CCAPSEL_HIRC          |\ref CLK_CLKDIV3_CCAP(x)       |
  * |\ref CCAP_MODULE    |\ref CLK_CLKSEL0_CCAPSEL_HCLK          |\ref CLK_CLKDIV3_CCAP(x)       |
  * |\ref SDH0_MODULE    |\ref CLK_CLKSEL0_SDH0SEL_HXT           |\ref CLK_CLKDIV0_SDH0(x)       |
  * |\ref SDH0_MODULE    |\ref CLK_CLKSEL0_SDH0SEL_PLL           |\ref CLK_CLKDIV0_SDH0(x)       |
  * |\ref SDH0_MODULE    |\ref CLK_CLKSEL0_SDH0SEL_HIRC          |\ref CLK_CLKDIV0_SDH0(x)       |
  * |\ref SDH0_MODULE    |\ref CLK_CLKSEL0_SDH0SEL_HCLK          |\ref CLK_CLKDIV0_SDH0(x)       |
  * |\ref SDH1_MODULE    |\ref CLK_CLKSEL0_SDH1SEL_HXT           |\ref CLK_CLKDIV3_SDH1(x)       |
  * |\ref SDH1_MODULE    |\ref CLK_CLKSEL0_SDH1SEL_PLL           |\ref CLK_CLKDIV3_SDH1(x)       |
  * |\ref SDH1_MODULE    |\ref CLK_CLKSEL0_SDH1SEL_HIRC          |\ref CLK_CLKDIV3_SDH1(x)       |
  * |\ref SDH1_MODULE    |\ref CLK_CLKSEL0_SDH1SEL_HCLK          |\ref CLK_CLKDIV3_SDH1(x)       |
  * |\ref WDT_MODULE     |\ref CLK_CLKSEL1_WDTSEL_LXT            | x                             |
  * |\ref WDT_MODULE     |\ref CLK_CLKSEL1_WDTSEL_LIRC           | x                             |
  * |\ref WDT_MODULE     |\ref CLK_CLKSEL1_WDTSEL_HCLK_DIV2048   | x                             |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_HXT           | x                             |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_LXT           | x                             |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_LIRC          | x                             |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_HIRC          | x                             |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_PCLK0         | x                             |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_EXT           | x                             |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_HXT           | x                             |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_LXT           | x                             |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_LIRC          | x                             |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_HIRC          | x                             |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_PCLK0         | x                             |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_EXT           | x                             |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_HXT           | x                             |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_LXT           | x                             |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_LIRC          | x                             |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_HIRC          | x                             |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_PCLK1         | x                             |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_EXT           | x                             |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_HXT           | x                             |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_LXT           | x                             |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_LIRC          | x                             |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_HIRC          | x                             |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_PCLK1         | x                             |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_EXT           | x                             |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL1_UART0SEL_HXT          |\ref CLK_CLKDIV0_UART0(x)      |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL1_UART0SEL_LXT          |\ref CLK_CLKDIV0_UART0(x)      |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL1_UART0SEL_PLL          |\ref CLK_CLKDIV0_UART0(x)      |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL1_UART0SEL_HIRC         |\ref CLK_CLKDIV0_UART0(x)      |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL1_UART1SEL_HXT          |\ref CLK_CLKDIV0_UART1(x)      |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL1_UART1SEL_LXT          |\ref CLK_CLKDIV0_UART1(x)      |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL1_UART1SEL_PLL          |\ref CLK_CLKDIV0_UART1(x)      |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL1_UART1SEL_HIRC         |\ref CLK_CLKDIV0_UART1(x)      |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_HXT           | x                             |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_LXT           | x                             |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_HIRC          | x                             |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_HCLK          | x                             |
  * |\ref WWDT_MODULE    |\ref CLK_CLKSEL1_WWDTSEL_LIRC          | x                             |
  * |\ref WWDT_MODULE    |\ref CLK_CLKSEL1_WWDTSEL_HCLK_DIV2048  | x                             |
  * |\ref EPWM0_MODULE   |\ref CLK_CLKSEL2_EPWM0SEL_PLL          | x                             |
  * |\ref EPWM0_MODULE   |\ref CLK_CLKSEL2_EPWM0SEL_PCLK0        | x                             |
  * |\ref EPWM1_MODULE   |\ref CLK_CLKSEL2_EPWM1SEL_PLL          | x                             |
  * |\ref EPWM1_MODULE   |\ref CLK_CLKSEL2_EPWM1SEL_PCLK1        | x                             |
  * |\ref QSPI0_MODULE   |\ref CLK_CLKSEL2_QSPI0SEL_HXT          | x                             |
  * |\ref QSPI0_MODULE   |\ref CLK_CLKSEL2_QSPI0SEL_PLL          | x                             |
  * |\ref QSPI0_MODULE   |\ref CLK_CLKSEL2_QSPI0SEL_HIRC         | x                             |
  * |\ref QSPI0_MODULE   |\ref CLK_CLKSEL2_QSPI0SEL_PCLK0        | x                             |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL2_SPI0SEL_HXT           | x                             |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL2_SPI0SEL_PLL           | x                             |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL2_SPI0SEL_HIRC          | x                             |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL2_SPI0SEL_PCLK1         | x                             |
  * |\ref BPWM0_MODULE   |\ref CLK_CLKSEL2_BPWM0SEL_PLL          | x                             |
  * |\ref BPWM0_MODULE   |\ref CLK_CLKSEL2_BPWM0SEL_PCLK0        | x                             |
  * |\ref BPWM1_MODULE   |\ref CLK_CLKSEL2_BPWM1SEL_PLL          | x                             |
  * |\ref BPWM1_MODULE   |\ref CLK_CLKSEL2_BPWM1SEL_PCLK1        | x                             |
  * |\ref SPI1_MODULE    |\ref CLK_CLKSEL2_SPI1SEL_HXT           | x                             |
  * |\ref SPI1_MODULE    |\ref CLK_CLKSEL2_SPI1SEL_PLL           | x                             |
  * |\ref SPI1_MODULE    |\ref CLK_CLKSEL2_SPI1SEL_HIRC          | x                             |
  * |\ref SPI1_MODULE    |\ref CLK_CLKSEL2_SPI1SEL_PCLK0         | x                             |
  * |\ref SPI2_MODULE    |\ref CLK_CLKSEL2_SPI2SEL_HXT           | x                             |
  * |\ref SPI2_MODULE    |\ref CLK_CLKSEL2_SPI2SEL_PLL           | x                             |
  * |\ref SPI2_MODULE    |\ref CLK_CLKSEL2_SPI2SEL_HIRC          | x                             |
  * |\ref SPI2_MODULE    |\ref CLK_CLKSEL2_SPI2SEL_PCLK1         | x                             |
  * |\ref SPI3_MODULE    |\ref CLK_CLKSEL2_SPI3SEL_HXT           | x                             |
  * |\ref SPI3_MODULE    |\ref CLK_CLKSEL2_SPI3SEL_PLL           | x                             |
  * |\ref SPI3_MODULE    |\ref CLK_CLKSEL2_SPI3SEL_HIRC          | x                             |
  * |\ref SPI3_MODULE    |\ref CLK_CLKSEL2_SPI3SEL_PCLK0         | x                             |
  * |\ref SC0_MODULE     |\ref CLK_CLKSEL3_SC0SEL_HXT            |\ref CLK_CLKDIV1_SC0(x)        |
  * |\ref SC0_MODULE     |\ref CLK_CLKSEL3_SC0SEL_PLL            |\ref CLK_CLKDIV1_SC0(x)        |
  * |\ref SC0_MODULE     |\ref CLK_CLKSEL3_SC0SEL_HIRC           |\ref CLK_CLKDIV1_SC0(x)        |
  * |\ref SC0_MODULE     |\ref CLK_CLKSEL3_SC0SEL_PCLK0          |\ref CLK_CLKDIV1_SC0(x)        |
  * |\ref SC1_MODULE     |\ref CLK_CLKSEL3_SC1SEL_HXT            |\ref CLK_CLKDIV1_SC1(x)        |
  * |\ref SC1_MODULE     |\ref CLK_CLKSEL3_SC1SEL_PLL            |\ref CLK_CLKDIV1_SC1(x)        |
  * |\ref SC1_MODULE     |\ref CLK_CLKSEL3_SC1SEL_HIRC           |\ref CLK_CLKDIV1_SC1(x)        |
  * |\ref SC1_MODULE     |\ref CLK_CLKSEL3_SC1SEL_PCLK1          |\ref CLK_CLKDIV1_SC1(x)        |
  * |\ref SC2_MODULE     |\ref CLK_CLKSEL3_SC2SEL_HXT            |\ref CLK_CLKDIV1_SC2(x)        |
  * |\ref SC2_MODULE     |\ref CLK_CLKSEL3_SC2SEL_PLL            |\ref CLK_CLKDIV1_SC2(x)        |
  * |\ref SC2_MODULE     |\ref CLK_CLKSEL3_SC2SEL_HIRC           |\ref CLK_CLKDIV1_SC2(x)        |
  * |\ref SC2_MODULE     |\ref CLK_CLKSEL3_SC2SEL_PCLK0          |\ref CLK_CLKDIV1_SC2(x)        |
  * |\ref RTC_MODULE     |\ref CLK_CLKSEL3_RTCSEL_LXT            | x                             |
  * |\ref RTC_MODULE     |\ref CLK_CLKSEL3_RTCSEL_LIRC           | x                             |
  * |\ref QSPI1_MODULE   |\ref CLK_CLKSEL3_QSPI1SEL_HXT          | x                             |
  * |\ref QSPI1_MODULE   |\ref CLK_CLKSEL3_QSPI1SEL_PLL          | x                             |
  * |\ref QSPI1_MODULE   |\ref CLK_CLKSEL3_QSPI1SEL_HIRC         | x                             |
  * |\ref QSPI1_MODULE   |\ref CLK_CLKSEL3_QSPI1SEL_PCLK1        | x                             |
  * |\ref I2S0_MODULE    |\ref CLK_CLKSEL3_I2S0SEL_HXT           |\ref CLK_CLKDIV2_I2S0(x)       |
  * |\ref I2S0_MODULE    |\ref CLK_CLKSEL3_I2S0SEL_PLL           |\ref CLK_CLKDIV2_I2S0(x)       |
  * |\ref I2S0_MODULE    |\ref CLK_CLKSEL3_I2S0SEL_HIRC          |\ref CLK_CLKDIV2_I2S0(x)       |
  * |\ref I2S0_MODULE    |\ref CLK_CLKSEL3_I2S0SEL_PCLK0         |\ref CLK_CLKDIV2_I2S0(x)       |
  * |\ref UART6_MODULE   |\ref CLK_CLKSEL3_UART6SEL_HXT          |\ref CLK_CLKDIV4_UART6(x)      |
  * |\ref UART6_MODULE   |\ref CLK_CLKSEL3_UART6SEL_LXT          |\ref CLK_CLKDIV4_UART6(x)      |
  * |\ref UART6_MODULE   |\ref CLK_CLKSEL3_UART6SEL_PLL          |\ref CLK_CLKDIV4_UART6(x)      |
  * |\ref UART6_MODULE   |\ref CLK_CLKSEL3_UART6SEL_HIRC         |\ref CLK_CLKDIV4_UART6(x)      |
  * |\ref UART7_MODULE   |\ref CLK_CLKSEL3_UART7SEL_HXT          |\ref CLK_CLKDIV4_UART7(x)      |
  * |\ref UART7_MODULE   |\ref CLK_CLKSEL3_UART7SEL_LXT          |\ref CLK_CLKDIV4_UART7(x)      |
  * |\ref UART7_MODULE   |\ref CLK_CLKSEL3_UART7SEL_PLL          |\ref CLK_CLKDIV4_UART7(x)      |
  * |\ref UART7_MODULE   |\ref CLK_CLKSEL3_UART7SEL_HIRC         |\ref CLK_CLKDIV4_UART7(x)      |
  * |\ref UART2_MODULE   |\ref CLK_CLKSEL3_UART2SEL_HXT          |\ref CLK_CLKDIV4_UART2(x)      |
  * |\ref UART2_MODULE   |\ref CLK_CLKSEL3_UART2SEL_LXT          |\ref CLK_CLKDIV4_UART2(x)      |
  * |\ref UART2_MODULE   |\ref CLK_CLKSEL3_UART2SEL_PLL          |\ref CLK_CLKDIV4_UART2(x)      |
  * |\ref UART2_MODULE   |\ref CLK_CLKSEL3_UART2SEL_HIRC         |\ref CLK_CLKDIV4_UART2(x)      |
  * |\ref UART3_MODULE   |\ref CLK_CLKSEL3_UART3SEL_HXT          |\ref CLK_CLKDIV4_UART3(x)      |
  * |\ref UART3_MODULE   |\ref CLK_CLKSEL3_UART3SEL_LXT          |\ref CLK_CLKDIV4_UART3(x)      |
  * |\ref UART3_MODULE   |\ref CLK_CLKSEL3_UART3SEL_PLL          |\ref CLK_CLKDIV4_UART3(x)      |
  * |\ref UART3_MODULE   |\ref CLK_CLKSEL3_UART3SEL_HIRC         |\ref CLK_CLKDIV4_UART3(x)      |
  * |\ref UART4_MODULE   |\ref CLK_CLKSEL3_UART4SEL_HXT          |\ref CLK_CLKDIV4_UART4(x)      |
  * |\ref UART4_MODULE   |\ref CLK_CLKSEL3_UART4SEL_LXT          |\ref CLK_CLKDIV4_UART4(x)      |
  * |\ref UART4_MODULE   |\ref CLK_CLKSEL3_UART4SEL_PLL          |\ref CLK_CLKDIV4_UART4(x)      |
  * |\ref UART4_MODULE   |\ref CLK_CLKSEL3_UART4SEL_HIRC         |\ref CLK_CLKDIV4_UART4(x)      |
  * |\ref UART5_MODULE   |\ref CLK_CLKSEL3_UART5SEL_HXT          |\ref CLK_CLKDIV4_UART5(x)      |
  * |\ref UART5_MODULE   |\ref CLK_CLKSEL3_UART5SEL_LXT          |\ref CLK_CLKDIV4_UART5(x)      |
  * |\ref UART5_MODULE   |\ref CLK_CLKSEL3_UART5SEL_PLL          |\ref CLK_CLKDIV4_UART5(x)      |
  * |\ref UART5_MODULE   |\ref CLK_CLKSEL3_UART5SEL_HIRC         |\ref CLK_CLKDIV4_UART5(x)      |
  * |\ref EADC_MODULE    | x                                     |\ref CLK_CLKDIV0_EADC(x)       |
  * |\ref EADC1_MODULE   | x                                     |\ref CLK_CLKDIV2_EADC1(x)      |
  * |\ref EMAC_MODULE    | x                                     |\ref CLK_CLKDIV3_EMAC(x)       |
  *
  */
void CLK_SetModuleClock(uint32_t u32ModuleIdx, uint32_t u32ClkSrc, uint32_t u32ClkDiv)
{
    uint32_t u32sel = 0U, u32div = 0U;

    if(MODULE_CLKDIV_Msk(u32ModuleIdx) != MODULE_NoMsk)
    {
        /* Get clock divider control register address */
        if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x1) // M480LD
        {
            if(MODULE_CLKDIV(u32ModuleIdx) == 2U && MODULE_IP_EN_Pos_ENC(u32ModuleIdx) == 31U) //EADC1
            {
                u32div = (uint32_t)&CLK->CLKDIV2;
            }
            else if(MODULE_CLKDIV(u32ModuleIdx) == 2U && MODULE_IP_EN_Pos_ENC(u32ModuleIdx) == 29U) //I2S0
            {
                u32div = (uint32_t)&CLK->CLKDIV2;
            }
            else if (MODULE_CLKDIV(u32ModuleIdx) == 2U)
            {
                u32div = (uint32_t)&CLK->CLKDIV3;
            }
            else if (MODULE_CLKDIV(u32ModuleIdx) == 3U)
            {
                u32div = (uint32_t)&CLK->CLKDIV4;
            }
            else
            {
                u32div = (uint32_t)&CLK->CLKDIV0 + ((MODULE_CLKDIV(u32ModuleIdx)) * 4U);
            }
        }
        else
        {
            /* Get clock divider control register address */
            if(MODULE_CLKDIV(u32ModuleIdx) == 2U)
            {
                u32div = (uint32_t)&CLK->CLKDIV3;
            }
            else if (MODULE_CLKDIV(u32ModuleIdx) == 3U)
            {
                u32div = (uint32_t)&CLK->CLKDIV4;
            }
            else
            {
                u32div = (uint32_t)&CLK->CLKDIV0 + ((MODULE_CLKDIV(u32ModuleIdx)) * 4U);
            }
        }

        /* Apply new divider */
        M32(u32div) = (M32(u32div) & (~(MODULE_CLKDIV_Msk(u32ModuleIdx) << MODULE_CLKDIV_Pos(u32ModuleIdx)))) | u32ClkDiv;
    }

    if(MODULE_CLKSEL_Msk(u32ModuleIdx) != MODULE_NoMsk)
    {
        /* Get clock select control register address */
        u32sel = (uint32_t)&CLK->CLKSEL0 + ((MODULE_CLKSEL(u32ModuleIdx)) * 4U);
        /* Set new clock selection setting */
        M32(u32sel) = (M32(u32sel) & (~(MODULE_CLKSEL_Msk(u32ModuleIdx) << MODULE_CLKSEL_Pos(u32ModuleIdx)))) | u32ClkSrc;
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
  *             - \ref PDMA_MODULE
  *             - \ref ISP_MODULE
  *             - \ref EBI_MODULE
  *             - \ref EMAC_MODULE
  *             - \ref SDH0_MODULE
  *             - \ref CRC_MODULE
  *             - \ref CCAP_MODULE
  *             - \ref SEN_MODULE
  *             - \ref HSUSBD_MODULE
  *             - \ref CRPT_MODULE
  *             - \ref SPIM_MODULE
  *             - \ref FMCIDLE_MODULE
  *             - \ref USBH_MODULE
  *             - \ref SDH1_MODULE
  *             - \ref WDT_MODULE
  *             - \ref RTC_MODULE
  *             - \ref TMR0_MODULE
  *             - \ref TMR1_MODULE
  *             - \ref TMR2_MODULE
  *             - \ref TMR3_MODULE
  *             - \ref CLKO_MODULE
  *             - \ref WWDT_MODULE
  *             - \ref ACMP01_MODULE
  *             - \ref I2C0_MODULE
  *             - \ref I2C1_MODULE
  *             - \ref I2C2_MODULE
  *             - \ref QSPI0_MODULE
  *             - \ref SPI0_MODULE
  *             - \ref SPI1_MODULE
  *             - \ref SPI2_MODULE
  *             - \ref UART0_MODULE
  *             - \ref UART1_MODULE
  *             - \ref UART2_MODULE
  *             - \ref UART3_MODULE
  *             - \ref UART4_MODULE
  *             - \ref UART5_MODULE
  *             - \ref UART6_MODULE
  *             - \ref UART7_MODULE
  *             - \ref CAN0_MODULE
  *             - \ref CAN1_MODULE
  *             - \ref OTG_MODULE
  *             - \ref USBD_MODULE
  *             - \ref EADC_MODULE
  *             - \ref I2S0_MODULE
  *             - \ref HSOTG_MODULE
  *             - \ref SC0_MODULE
  *             - \ref SC1_MODULE
  *             - \ref SC2_MODULE
  *             - \ref QSPI1_MODULE
  *             - \ref SPI3_MODULE
  *             - \ref USCI0_MODULE
  *             - \ref USCI1_MODULE
  *             - \ref DAC_MODULE
  *             - \ref CAN2_MODULE
  *             - \ref EPWM0_MODULE
  *             - \ref EPWM1_MODULE
  *             - \ref BPWM0_MODULE
  *             - \ref BPWM1_MODULE
  *             - \ref QEI0_MODULE
  *             - \ref QEI1_MODULE
  *             - \ref TRNG_MODULE
  *             - \ref ECAP0_MODULE
  *             - \ref ECAP1_MODULE
  *             - \ref CAN2_MODULE
  *             - \ref OPA_MODULE
  *             - \ref EADC1_MODULE
  * @return     None
  * @details    This function is used to enable module clock.
  */
void CLK_EnableModuleClock(uint32_t u32ModuleIdx)
{
    uint32_t u32tmpVal = 0UL, u32tmpAddr = 0UL;

    u32tmpVal = (1UL << MODULE_IP_EN_Pos(u32ModuleIdx));
    u32tmpAddr = (uint32_t)&CLK->AHBCLK;
    u32tmpAddr += ((MODULE_APBCLK(u32ModuleIdx) * 4UL));

    *(volatile uint32_t *)u32tmpAddr |= u32tmpVal;
}

/**
  * @brief      Disable module clock
  * @param[in]  u32ModuleIdx is module index. Including :
  *             - \ref PDMA_MODULE
  *             - \ref ISP_MODULE
  *             - \ref EBI_MODULE
  *             - \ref EMAC_MODULE
  *             - \ref SDH0_MODULE
  *             - \ref CRC_MODULE
  *             - \ref CCAP_MODULE
  *             - \ref SEN_MODULE
  *             - \ref HSUSBD_MODULE
  *             - \ref CRPT_MODULE
  *             - \ref SPIM_MODULE
  *             - \ref FMCIDLE_MODULE
  *             - \ref USBH_MODULE
  *             - \ref SDH1_MODULE
  *             - \ref WDT_MODULE
  *             - \ref RTC_MODULE
  *             - \ref TMR0_MODULE
  *             - \ref TMR1_MODULE
  *             - \ref TMR2_MODULE
  *             - \ref TMR3_MODULE
  *             - \ref CLKO_MODULE
  *             - \ref WWDT_MODULE
  *             - \ref ACMP01_MODULE
  *             - \ref I2C0_MODULE
  *             - \ref I2C1_MODULE
  *             - \ref I2C2_MODULE
  *             - \ref QSPI0_MODULE
  *             - \ref SPI0_MODULE
  *             - \ref SPI1_MODULE
  *             - \ref SPI2_MODULE
  *             - \ref UART0_MODULE
  *             - \ref UART1_MODULE
  *             - \ref UART2_MODULE
  *             - \ref UART3_MODULE
  *             - \ref UART4_MODULE
  *             - \ref UART5_MODULE
  *             - \ref UART6_MODULE
  *             - \ref UART7_MODULE
  *             - \ref CAN0_MODULE
  *             - \ref CAN1_MODULE
  *             - \ref OTG_MODULE
  *             - \ref USBD_MODULE
  *             - \ref EADC_MODULE
  *             - \ref I2S0_MODULE
  *             - \ref HSOTG_MODULE
  *             - \ref SC0_MODULE
  *             - \ref SC1_MODULE
  *             - \ref SC2_MODULE
  *             - \ref QSPI1_MODULE
  *             - \ref SPI3_MODULE
  *             - \ref USCI0_MODULE
  *             - \ref USCI1_MODULE
  *             - \ref DAC_MODULE
  *             - \ref CAN2_MODULE
  *             - \ref EPWM0_MODULE
  *             - \ref EPWM1_MODULE
  *             - \ref BPWM0_MODULE
  *             - \ref BPWM1_MODULE
  *             - \ref QEI0_MODULE
  *             - \ref QEI1_MODULE
  *             - \ref TRNG_MODULE
  *             - \ref ECAP0_MODULE
  *             - \ref ECAP1_MODULE
  *             - \ref CAN2_MODULE
  *             - \ref OPA_MODULE
  *             - \ref EADC1_MODULE
  * @return     None
  * @details    This function is used to disable module clock.
  */
void CLK_DisableModuleClock(uint32_t u32ModuleIdx)
{
    uint32_t u32tmpVal = 0UL, u32tmpAddr = 0UL;

    u32tmpVal = ~(1UL << MODULE_IP_EN_Pos(u32ModuleIdx));
    u32tmpAddr = (uint32_t)&CLK->AHBCLK;
    u32tmpAddr += ((MODULE_APBCLK(u32ModuleIdx) * 4UL));

    *(uint32_t *)u32tmpAddr &= u32tmpVal;
}


/**
  * @brief      Set PLL frequency
  * @param[in]  u32PllClkSrc is PLL clock source. Including :
  *             - \ref CLK_PLLCTL_PLLSRC_HXT
  *             - \ref CLK_PLLCTL_PLLSRC_HIRC
  * @param[in]  u32PllFreq is PLL frequency.
  * @return     PLL frequency
  * @details    This function is used to configure PLLCTL register to set specified PLL frequency. \n
  *             The register write-protection function should be disabled before using this function.
  */
uint32_t CLK_EnablePLL(uint32_t u32PllClkSrc, uint32_t u32PllFreq)
{
    uint32_t u32PllSrcClk, u32NR, u32NF, u32NO, u32CLK_SRC, u32PllClk;
    uint32_t u32Tmp, u32Tmp2, u32Tmp3, u32Min, u32MinNF, u32MinNR, u32MinNO, u32basFreq;

    /* Disable PLL first to avoid unstable when setting PLL */
    CLK_DisablePLL();

    /* PLL source clock is from HXT */
    if(u32PllClkSrc == CLK_PLLCTL_PLLSRC_HXT)
    {
        /* Enable HXT clock */
        CLK->PWRCTL |= CLK_PWRCTL_HXTEN_Msk;

        /* Wait for HXT clock ready */
        CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

        /* Select PLL source clock from HXT */
        u32CLK_SRC = CLK_PLLCTL_PLLSRC_HXT;
        u32PllSrcClk = __HXT;

        /* u32NR start from 2 */
        u32NR = 2UL;
    }

    /* PLL source clock is from HIRC */
    else
    {
        /* Enable HIRC clock */
        CLK->PWRCTL |= CLK_PWRCTL_HIRCEN_Msk;

        /* Wait for HIRC clock ready */
        CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

        /* Select PLL source clock from HIRC */
        u32CLK_SRC = CLK_PLLCTL_PLLSRC_HIRC;
        u32PllSrcClk = __HIRC;

        /* u32NR start from 4 when FIN = 22.1184MHz to avoid calculation overflow */
        u32NR = 4UL;
    }

    if((u32PllFreq <= FREQ_500MHZ) && (u32PllFreq >= FREQ_50MHZ))
    {

        /* Find best solution */
        u32Min = (uint32_t) - 1;
        u32MinNR = 0UL;
        u32MinNF = 0UL;
        u32MinNO = 0UL;
        u32basFreq = u32PllFreq;

        for(u32NO = 1UL; u32NO <= 4UL; u32NO++)
        {
            /* Break when get good results */
            if (u32Min == 0UL)
            {
                break;
            }

            if (u32NO != 3UL)
            {

                if(u32NO == 4UL)
                {
                    u32PllFreq = u32basFreq << 2;
                }
                else if(u32NO == 2UL)
                {
                    u32PllFreq = u32basFreq << 1;
                }
                else
                {
                }

                for(u32NR = 2UL; u32NR <= 32UL; u32NR++)
                {
                    /* Break when get good results */
                    if (u32Min == 0UL)
                    {
                        break;
                    }

                    u32Tmp = u32PllSrcClk / u32NR;
                    if((u32Tmp >= 4000000UL) && (u32Tmp <= 8000000UL))
                    {
                        for(u32NF = 2UL; u32NF <= 513UL; u32NF++)
                        {
                            /* u32Tmp2 is shifted 2 bits to avoid overflow */
                            u32Tmp2 = (((u32Tmp * 2UL) >> 2) * u32NF);

                            if((u32Tmp2 >= FREQ_50MHZ) && (u32Tmp2 <= FREQ_125MHZ))
                            {
                                u32Tmp3 = (u32Tmp2 > (u32PllFreq>>2)) ? u32Tmp2 - (u32PllFreq>>2) : (u32PllFreq>>2) - u32Tmp2;
                                if(u32Tmp3 < u32Min)
                                {
                                    u32Min = u32Tmp3;
                                    u32MinNR = u32NR;
                                    u32MinNF = u32NF;
                                    u32MinNO = u32NO;

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
            }
        }

        /* Enable and apply new PLL setting. */
        CLK->PLLCTL = u32CLK_SRC | ((u32MinNO - 1UL) << 14) | ((u32MinNR - 1UL) << 9) | (u32MinNF - 2UL);

        /* Wait for PLL clock stable */
        CLK_WaitClockReady(CLK_STATUS_PLLSTB_Msk);

        /* Actual PLL output clock frequency */
        u32PllClk = u32PllSrcClk / (u32MinNO * (u32MinNR)) * (u32MinNF) * 2UL;
    }
    else
    {
        /* Wrong frequency request. Just return default setting. */
        /* Apply default PLL setting and return */
        if(u32PllClkSrc == CLK_PLLCTL_PLLSRC_HXT)
        {
            CLK->PLLCTL = CLK_PLLCTL_192MHz_HXT;
        }
        else
        {
            CLK->PLLCTL = CLK_PLLCTL_192MHz_HIRC;
        }

        /* Wait for PLL clock stable */
        CLK_WaitClockReady(CLK_STATUS_PLLSTB_Msk);

        /* Actual PLL output clock frequency */
        u32PllClk = CLK_GetPLLClockFreq();
    }

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
  * @retval     0  clock is not stable
  * @retval     1  clock is stable
  * @details    To wait for clock ready by specified clock source stable flag or timeout (~300ms)
  */
uint32_t CLK_WaitClockReady(uint32_t u32ClkMask)
{
    int32_t i32TimeOutCnt = 2160000;
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
    if( u32ClkSrc == CLK_CLKSEL0_STCLKSEL_HCLK )
    {
        SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
    }
    else
    {
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
  *             - \ref CLK_PMUCTL_PDMSEL_SPD0
  *             - \ref CLK_PMUCTL_PDMSEL_SPD1
  *             - \ref CLK_PMUCTL_PDMSEL_DPD
  * @return     None
  * @details    This function is used to set power-down mode.
  * @note       Must enable LIRC clock before entering to Standby Power-down Mode
  */

void CLK_SetPowerDownMode(uint32_t u32PDMode)
{
    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x1) // M480LD
    {
        if(u32PDMode == CLK_PMUCTL_PDMSEL_SPD0)
        {
            u32PDMode = CLK_PMUCTL_PDMSEL_SPD0;
            CLK->PMUCTL = (CLK->PMUCTL & ~(CLK_PMUCTL_SRETSEL_Msk)) | CLK_SPDSRETSEL_16K;
        }
        else if(u32PDMode == CLK_PMUCTL_PDMSEL_SPD1)
        {
            u32PDMode = CLK_PMUCTL_PDMSEL_SPD0;
            CLK->PMUCTL = (CLK->PMUCTL & ~(CLK_PMUCTL_SRETSEL_Msk)) | CLK_SPDSRETSEL_NO;
        }
    }
    else
    {
        /* Enable LIRC clock before entering to Standby Power-down Mode */
        if((u32PDMode == CLK_PMUCTL_PDMSEL_SPD0) || (u32PDMode == CLK_PMUCTL_PDMSEL_SPD1))
        {
            /* Enable LIRC clock */
            CLK->PWRCTL |= CLK_PWRCTL_LIRCEN_Msk;

            /* Wait for LIRC clock stable */
            CLK_WaitClockReady(CLK_STATUS_LIRCSTB_Msk);
        }
    }

    CLK->PMUCTL = (CLK->PMUCTL & ~(CLK_PMUCTL_PDMSEL_Msk)) | u32PDMode;
}


/**
 * @brief       Set Wake-up pin trigger type at Deep Power down mode
 *
 * @param[in]   u32TriggerType
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
 *
 * @details     This function is used to enable Wake-up pin trigger type.
 */

void CLK_EnableDPDWKPin(uint32_t u32TriggerType)
{
    uint32_t u32Pin1, u32Pin2, u32Pin3, u32Pin4;

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x1) // M480LD
    {
        u32Pin1 = (((u32TriggerType) & 0x03UL) >> CLK_PMUCTL_WKPINEN1_Pos);
        u32Pin2 = (((u32TriggerType) & 0x03UL) >> CLK_PMUCTL_WKPINEN2_Pos);
        u32Pin3 = (((u32TriggerType) & 0x03UL) >> CLK_PMUCTL_WKPINEN3_Pos);
        u32Pin4 = (((u32TriggerType) & 0x03UL) >> CLK_PMUCTL_WKPINEN4_Pos);

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
    else
    {
        CLK->PMUCTL = (CLK->PMUCTL & ~(CLK_PMUCTL_WKPINEN_Msk)) | u32TriggerType;
    }
}

/**
 * @brief      Get power manager wake up source
 *
 * @param[in]   None
 * @return      None
 *
 * @details     This function get power manager wake up source.
 */

uint32_t CLK_GetPMUWKSrc(void)
{
    return (CLK->PMUSTS);
}

/**
 * @brief       Set specified GPIO as wake up source at Stand-by Power down mode
 *
 * @param[in]   u32Port GPIO port. It could be 0~3.
 * @param[in]   u32Pin  The pin of specified GPIO port. It could be 0 ~ 15.
 * @param[in]   u32TriggerType
 *              - \ref CLK_SPDWKPIN_RISING
 *              - \ref CLK_SPDWKPIN_FALLING
 * @param[in]   u32DebounceEn
 *              - \ref CLK_SPDWKPIN_DEBOUNCEEN
 *              - \ref CLK_SPDWKPIN_DEBOUNCEDIS
 * @return      None
 *
 * @details     This function is used to set specified GPIO as wake up source
 *              at Stand-by Power down mode.
 */
void CLK_EnableSPDWKPin(uint32_t u32Port, uint32_t u32Pin, uint32_t u32TriggerType, uint32_t u32DebounceEn)
{
    uint32_t u32tmpAddr = 0UL;
    uint32_t u32tmpVal = 0UL;

    /* GPx Stand-by Power-down Wake-up Pin Select */
    u32tmpAddr = (uint32_t)&CLK->PASWKCTL;
    u32tmpAddr += (0x4UL * u32Port);

    u32tmpVal = inpw((uint32_t *)u32tmpAddr);
    u32tmpVal = (u32tmpVal & ~(CLK_PASWKCTL_WKPSEL_Msk | CLK_PASWKCTL_PRWKEN_Msk | CLK_PASWKCTL_PFWKEN_Msk | CLK_PASWKCTL_DBEN_Msk | CLK_PASWKCTL_WKEN_Msk)) |
                (u32Pin << CLK_PASWKCTL_WKPSEL_Pos) | u32TriggerType | u32DebounceEn | CLK_SPDWKPIN_ENABLE;
    outpw((uint32_t *)u32tmpAddr, u32tmpVal);
}

/**
  * @brief      Get PLL clock frequency
  * @param      None
  * @return     PLL frequency
  * @details    This function get PLL frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetPLLClockFreq(void)
{
    uint32_t u32PllFreq = 0UL, u32PllReg;
    uint32_t u32FIN, u32NF, u32NR, u32NO;
    uint8_t au8NoTbl[4] = {1U, 2U, 2U, 4U};

    u32PllReg = CLK->PLLCTL;

    if(u32PllReg & (CLK_PLLCTL_PD_Msk | CLK_PLLCTL_OE_Msk))
    {
        u32PllFreq = 0UL;           /* PLL is in power down mode or fix low */
    }
    else if((u32PllReg & CLK_PLLCTL_BP_Msk) == CLK_PLLCTL_BP_Msk)
    {
        if((u32PllReg & CLK_PLLCTL_PLLSRC_HIRC) == CLK_PLLCTL_PLLSRC_HIRC)
        {
            u32FIN = __HIRC;    /* PLL source clock from HIRC */
        }
        else
        {
            u32FIN = __HXT;     /* PLL source clock from HXT */
        }

        u32PllFreq = u32FIN;
    }
    else
    {
        if((u32PllReg & CLK_PLLCTL_PLLSRC_HIRC) == CLK_PLLCTL_PLLSRC_HIRC)
        {
            u32FIN = __HIRC;    /* PLL source clock from HIRC */
        }
        else
        {
            u32FIN = __HXT;     /* PLL source clock from HXT */
        }
        /* PLL is output enabled in normal work mode */
        u32NO = au8NoTbl[((u32PllReg & CLK_PLLCTL_OUTDIV_Msk) >> CLK_PLLCTL_OUTDIV_Pos)];
        u32NF = ((u32PllReg & CLK_PLLCTL_FBDIV_Msk) >> CLK_PLLCTL_FBDIV_Pos) + 2UL;
        u32NR = ((u32PllReg & CLK_PLLCTL_INDIV_Msk) >> CLK_PLLCTL_INDIV_Pos) + 1UL;

        /* u32FIN is shifted 2 bits to avoid overflow */
        u32PllFreq = (((u32FIN >> 2) * u32NF) / (u32NR * u32NO) << 2) * 2UL;
    }

    return u32PllFreq;
}

/**
  * @brief      Get selected module clock source
  * @param[in]  u32ModuleIdx is module index.
  *             - \ref CCAP_MODULE
  *             - \ref SDH0_MODULE
  *             - \ref SDH1_MODULE
  *             - \ref WDT_MODULE
  *             - \ref UART0_MODULE
  *             - \ref UART1_MODULE
  *             - \ref CLKO_MODULE
  *             - \ref WWDT_MODULE
  *             - \ref TMR0_MODULE
  *             - \ref TMR1_MODULE
  *             - \ref TMR2_MODULE
  *             - \ref TMR3_MODULE
  *             - \ref EPWM0_MODULE
  *             - \ref EPWM1_MODULE
  *             - \ref BPWM0_MODULE
  *             - \ref BPWM1_MODULE
  *             - \ref QSPI0_MODULE
  *             - \ref QSPI1_MODULE
  *             - \ref SPI0_MODULE
  *             - \ref SPI1_MODULE
  *             - \ref SPI2_MODULE
  *             - \ref SPI3_MODULE
  *             - \ref SC0_MODULE
  *             - \ref SC1_MODULE
  *             - \ref SC2_MODULE
  *             - \ref RTC_MODULE
  *             - \ref I2S0_MODULE
  *             - \ref UART2_MODULE
  *             - \ref UART3_MODULE
  *             - \ref UART4_MODULE
  *             - \ref UART5_MODULE
  *             - \ref UART6_MODULE
  *             - \ref UART7_MODULE
  * @return     Selected module clock source setting
  * @details    This function get selected module clock source.
  */
uint32_t CLK_GetModuleClockSource(uint32_t u32ModuleIdx)
{
    uint32_t u32sel = 0;
    uint32_t u32SelTbl[4] = {0x0, 0x4, 0x8, 0xC};

    /* Get clock source selection setting */
    if(u32ModuleIdx == EPWM0_MODULE)
        return ((CLK->CLKSEL2 & CLK_CLKSEL2_EPWM0SEL_Msk) >> CLK_CLKSEL2_EPWM0SEL_Pos);
    else if(u32ModuleIdx == EPWM1_MODULE)
        return ((CLK->CLKSEL2 & CLK_CLKSEL2_EPWM1SEL_Msk) >> CLK_CLKSEL2_EPWM1SEL_Pos);
    else if(u32ModuleIdx == BPWM0_MODULE)
        return ((CLK->CLKSEL2 & CLK_CLKSEL2_BPWM0SEL_Msk) >> CLK_CLKSEL2_BPWM0SEL_Pos);
    else if(u32ModuleIdx == BPWM1_MODULE)
        return ((CLK->CLKSEL2 & CLK_CLKSEL2_BPWM1SEL_Msk) >> CLK_CLKSEL2_BPWM1SEL_Pos);
    else if(MODULE_CLKSEL_Msk(u32ModuleIdx) != MODULE_NoMsk)
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
  *             - \ref CCAP_MODULE
  *             - \ref SDH0_MODULE
  *             - \ref SDH1_MODULE
  *             - \ref UART0_MODULE
  *             - \ref UART1_MODULE
  *             - \ref UART2_MODULE
  *             - \ref UART3_MODULE
  *             - \ref UART4_MODULE
  *             - \ref UART5_MODULE
  *             - \ref UART6_MODULE
  *             - \ref UART7_MODULE
  *             - \ref SC0_MODULE
  *             - \ref SC1_MODULE
  *             - \ref SC2_MODULE
  *             - \ref I2S0_MODULE
  *             - \ref EADC_MODULE
  *             - \ref EADC1_MODULE
  *             - \ref EMAC_MODULE
  * @return     Selected module clock divider number setting
  * @details    This function get selected module clock divider number.
  */
uint32_t CLK_GetModuleClockDivider(uint32_t u32ModuleIdx)
{
    uint32_t u32div = 0;
    uint32_t u32DivTbl[4] = {0x0, 0x4, 0xc, 0x10};

    if(MODULE_CLKDIV_Msk(u32ModuleIdx) != MODULE_NoMsk)
    {
        /* Get clock divider control register address */
        u32div = (uint32_t)&CLK->CLKDIV0 + (u32DivTbl[MODULE_CLKDIV(u32ModuleIdx)]);
        if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x1) // M480LD
        {
            if(MODULE_IP_EN_Pos_ENC(u32ModuleIdx) == 31U) //EADC1
                u32div = (uint32_t)&CLK->CLKDIV2;
            else if(MODULE_IP_EN_Pos_ENC(u32ModuleIdx) == 29U) //I2S0
                u32div = (uint32_t)&CLK->CLKDIV2;
        }
        /* Get clock divider number setting */
        return ((M32(u32div) & (MODULE_CLKDIV_Msk(u32ModuleIdx) << MODULE_CLKDIV_Pos(u32ModuleIdx))) >> MODULE_CLKDIV_Pos(u32ModuleIdx));
    }
    else
        return 0;
}


/*@}*/ /* end of group CLK_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group CLK_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
