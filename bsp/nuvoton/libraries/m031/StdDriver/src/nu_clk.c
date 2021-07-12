/**************************************************************************//**
 * @file     clk.c
 * @version  V3.00
 * $Revision: 6 $
 * $Date: 18/07/05 4:42p $
 * @brief    M031 Series Clock Controller (CLK) Driver Source File
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "M031Series.h"

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
  * @brief      This function enable frequency output function and
  *             configure frequency clock source and divider.
  * @param[in]  u32ClkSrc is frequency output function clock source. Including :
  *             - \ref CLK_CLKSEL1_CLKOSEL_HXT
  *             - \ref CLK_CLKSEL1_CLKOSEL_LXT
  *             - \ref CLK_CLKSEL1_CLKOSEL_HCLK
  *             - \ref CLK_CLKSEL1_CLKOSEL_HIRC
  *             - \ref CLK_CLKSEL1_CLKOSEL_LIRC
  *             - \ref CLK_CLKSEL1_CLKOSEL_PLL
  *             - \ref CLK_CLKSEL1_CLKOSEL_SOF
  * @param[in]  u32ClkDiv is divider selection for output frequency.
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
  * @note       Must be care of HIRC/MIRC auto trim is disabled when using this function.
  */
void CLK_PowerDown(void)
{
    volatile uint32_t u32SysTickTICKINT = 0;    /* Backup Systick interrupt enable bit */

    /* Check HIRC/MIRC auto trim function disable */
    if(SYS->HIRCTRIMCTL & SYS_HIRCTRIMCTL_FREQSEL_Msk)
    {
        return;
    }

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
uint32_t CLK_GetHXTFreq(void)
{
    if(CLK->PWRCTL & CLK_PWRCTL_HXTEN_Msk)
        return __HXT;
    else
        return 0;
}

/**
  * @brief      Get external low speed crystal clock frequency
  * @param      None
  * @return     External low speed crystal clock frequency
  * @details    This function get external low frequency crystal frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetLXTFreq(void)
{
    if(CLK->PWRCTL & CLK_PWRCTL_LXTEN_Msk)
        return __LXT;
    else
        return 0;
}

/**
  * @brief      Get PCLK0 frequency
  * @param      None
  * @return     PCLK0 frequency
  * @details    This function get PCLK0 frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetPCLK0Freq(void)
{
    uint32_t PCLK0Div;

    SystemCoreClockUpdate();
    PCLK0Div = (CLK->PCLKDIV & CLK_PCLKDIV_APB0DIV_Msk) >> CLK_PCLKDIV_APB0DIV_Pos;
    return (SystemCoreClock >> PCLK0Div);
}

/**
  * @brief      Get PCLK1 frequency
  * @param      None
  * @return     PCLK1 frequency
  * @details    This function get PCLK1 frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetPCLK1Freq(void)
{
    uint32_t PCLK1Div;

    SystemCoreClockUpdate();
    PCLK1Div = (CLK->PCLKDIV & CLK_PCLKDIV_APB1DIV_Msk) >> CLK_PCLKDIV_APB1DIV_Pos;
    return (SystemCoreClock >> PCLK1Div);
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
  * @param[in]  u32Hclk is HCLK frequency. The range of u32Hclk is 25.5MHz ~ 48MHz.
*               NOTE: For M031_G/I, the HCLK frequency up to 72MHz.
  * @return     HCLK frequency
  * @details    This function is used to set HCLK frequency. The frequency unit is Hz. \n
  *             It would configure PLL frequency to 51MHz ~ 96MHz,
  *             set HCLK clock divider as 2 and switch HCLK clock source to PLL. \n
  *             The register write-protection function should be disabled before using this function.
  *             NOTE: For M031_G/I, the PLL frequency up to 144MHz.
  */
uint32_t CLK_SetCoreClock(uint32_t u32Hclk)
{
    uint32_t u32HIRCSTB;
    uint32_t u32HCLK_UpperLimit;

    /* Read HIRC clock source stable flag */
    u32HIRCSTB = CLK->STATUS & CLK_STATUS_HIRCSTB_Msk;

    /* The range of u32Hclk is 25.5 MHz ~ 48 MHz or 72 MHz */
    if ((GET_CHIP_SERIES_NUM == CHIP_SERIES_NUM_G) || (GET_CHIP_SERIES_NUM == CHIP_SERIES_NUM_I))
        u32HCLK_UpperLimit = FREQ_72MHZ;
    else
        u32HCLK_UpperLimit = FREQ_48MHZ;

    if(u32Hclk > u32HCLK_UpperLimit)
        u32Hclk = u32HCLK_UpperLimit;
    if(u32Hclk < (FREQ_51MHZ >> 1))
        u32Hclk = (FREQ_51MHZ >> 1);

    /* Switch HCLK clock source to HIRC clock for safe */
    CLK->PWRCTL |= CLK_PWRCTL_HIRCEN_Msk;
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);
    CLK->CLKSEL0 |= CLK_CLKSEL0_HCLKSEL_Msk;
    CLK->CLKDIV0 &= (~CLK_CLKDIV0_HCLKDIV_Msk);

    /* Configure PLL setting if HXT clock is stable */
    if(CLK->STATUS & CLK_STATUS_HXTSTB_Msk)
        u32Hclk = CLK_EnablePLL(CLK_PLLCTL_PLLSRC_HXT, (u32Hclk << 1));

    /* Configure PLL setting if HXT clock is not stable */
    else
    {
        u32Hclk = CLK_EnablePLL(CLK_PLLCTL_PLLSRC_HIRC_DIV4, (u32Hclk << 1));

        /* Read HIRC clock source stable flag */
        u32HIRCSTB = CLK->STATUS & CLK_STATUS_HIRCSTB_Msk;
    }

    /* Select HCLK clock source to PLL,
       Select HCLK clock source divider as 2
       and update system core clock
    */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_PLL, CLK_CLKDIV0_HCLK(2));

    /* Disable HIRC if HIRC is disabled before setting core clock */
    if(u32HIRCSTB == 0)
        CLK->PWRCTL &= ~CLK_PWRCTL_HIRCEN_Msk;

    /* Return actually HCLK frequency is PLL frequency divide 2 */
    return u32Hclk >> 1;
}

/**
  * @brief      Set HCLK clock source and HCLK clock divider
  * @param[in]  u32ClkSrc is HCLK clock source. Including :
  *             - \ref CLK_CLKSEL0_HCLKSEL_HXT
  *             - \ref CLK_CLKSEL0_HCLKSEL_LXT
  *             - \ref CLK_CLKSEL0_HCLKSEL_PLL
  *             - \ref CLK_CLKSEL0_HCLKSEL_LIRC
  *             - \ref CLK_CLKSEL0_HCLKSEL_HIRC
  * @param[in]  u32ClkDiv is HCLK clock divider. Including :
  *             - \ref CLK_CLKDIV0_HCLK(x)
  * @return     None
  * @details    This function set HCLK clock source and HCLK clock divider. The HCLK clock divider is set by CLK_CLKDIV0_HCLK(x) where x = 1~16.
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
    if(u32HIRCSTB == 0)
        CLK->PWRCTL &= ~CLK_PWRCTL_HIRCEN_Msk;
}

/**
  * @brief      This function set selected module clock source and module clock divider
  * @param[in]  u32ModuleIdx is module index.
  * @param[in]  u32ClkSrc is module clock source.
  * @param[in]  u32ClkDiv is module clock divider.
  * @return     None
  * @details    Valid parameter combinations listed in following table:
  *
  * |Module index        |Clock source                          |Divider                   |
  * | :----------------  | :----------------------------------- | :----------------------- |
  * |\ref USBD_MODULE    |\ref CLK_CLKSEL0_USBDSEL_HIRC         |\ref CLK_CLKDIV0_USB(x)   |
  * |\ref USBD_MODULE    |\ref CLK_CLKSEL0_USBDSEL_PLL          |\ref CLK_CLKDIV0_USB(x)   |
  * |\ref WDT_MODULE     |\ref CLK_CLKSEL1_WDTSEL_LXT           | x                        |
  * |\ref WDT_MODULE     |\ref CLK_CLKSEL1_WDTSEL_HCLK_DIV2048  | x                        |
  * |\ref WDT_MODULE     |\ref CLK_CLKSEL1_WDTSEL_LIRC          | x                        |
  * |\ref WWDT_MODULE    |\ref CLK_CLKSEL1_WWDTSEL_HCLK_DIV2048 | x                        |
  * |\ref WWDT_MODULE    |\ref CLK_CLKSEL1_WWDTSEL_LIRC         | x                        |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_HXT          | x                        |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_LXT          | x                        |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_HCLK         | x                        |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_HIRC         | x                        |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_LIRC         | x                        |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_PLL          | x                        |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_SOF          | x                        |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_HXT          | x                        |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_LXT          | x                        |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_PCLK0        | x                        |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_EXT_TRG      | x                        |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_LIRC         | x                        |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_HIRC         | x                        |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_HXT          | x                        |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_LXT          | x                        |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_PCLK0        | x                        |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_EXT_TRG      | x                        |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_LIRC         | x                        |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_HIRC         | x                        |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_HXT          | x                        |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_LXT          | x                        |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_PCLK1        | x                        |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_EXT_TRG      | x                        |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_LIRC         | x                        |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_HIRC         | x                        |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_HXT          | x                        |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_LXT          | x                        |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_PCLK1        | x                        |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_EXT_TRG      | x                        |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_LIRC         | x                        |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_HIRC         | x                        |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL1_UART0SEL_HXT         |\ref CLK_CLKDIV0_UART0(x) |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL1_UART0SEL_PLL         |\ref CLK_CLKDIV0_UART0(x) |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL1_UART0SEL_LXT         |\ref CLK_CLKDIV0_UART0(x) |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL1_UART0SEL_HIRC        |\ref CLK_CLKDIV0_UART0(x) |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL1_UART0SEL_PCLK0       |\ref CLK_CLKDIV0_UART0(x) |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL1_UART0SEL_LIRC        |\ref CLK_CLKDIV0_UART0(x) |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL1_UART1SEL_HXT         |\ref CLK_CLKDIV0_UART1(x) |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL1_UART1SEL_PLL         |\ref CLK_CLKDIV0_UART1(x) |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL1_UART1SEL_LXT         |\ref CLK_CLKDIV0_UART1(x) |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL1_UART1SEL_HIRC        |\ref CLK_CLKDIV0_UART1(x) |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL1_UART1SEL_PCLK1       |\ref CLK_CLKDIV0_UART1(x) |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL1_UART1SEL_LIRC        |\ref CLK_CLKDIV0_UART1(x) |
  * |\ref UART2_MODULE   |\ref CLK_CLKSEL3_UART2SEL_HXT         |\ref CLK_CLKDIV4_UART2(x) |
  * |\ref UART2_MODULE   |\ref CLK_CLKSEL3_UART2SEL_PLL         |\ref CLK_CLKDIV4_UART2(x) |
  * |\ref UART2_MODULE   |\ref CLK_CLKSEL3_UART2SEL_LXT         |\ref CLK_CLKDIV4_UART2(x) |
  * |\ref UART2_MODULE   |\ref CLK_CLKSEL3_UART2SEL_HIRC        |\ref CLK_CLKDIV4_UART2(x) |
  * |\ref UART2_MODULE   |\ref CLK_CLKSEL3_UART2SEL_PCLK0       |\ref CLK_CLKDIV4_UART2(x) |
  * |\ref UART2_MODULE   |\ref CLK_CLKSEL3_UART2SEL_LIRC        |\ref CLK_CLKDIV4_UART2(x) |
  * |\ref UART3_MODULE   |\ref CLK_CLKSEL3_UART3SEL_HXT         |\ref CLK_CLKDIV4_UART3(x) |
  * |\ref UART3_MODULE   |\ref CLK_CLKSEL3_UART3SEL_PLL         |\ref CLK_CLKDIV4_UART3(x) |
  * |\ref UART3_MODULE   |\ref CLK_CLKSEL3_UART3SEL_LXT         |\ref CLK_CLKDIV4_UART3(x) |
  * |\ref UART3_MODULE   |\ref CLK_CLKSEL3_UART3SEL_HIRC        |\ref CLK_CLKDIV4_UART3(x) |
  * |\ref UART3_MODULE   |\ref CLK_CLKSEL3_UART3SEL_PCLK1       |\ref CLK_CLKDIV4_UART3(x) |
  * |\ref UART3_MODULE   |\ref CLK_CLKSEL3_UART3SEL_LIRC        |\ref CLK_CLKDIV4_UART3(x) |
  * |\ref UART4_MODULE   |\ref CLK_CLKSEL3_UART4SEL_HXT         |\ref CLK_CLKDIV4_UART4(x) |
  * |\ref UART4_MODULE   |\ref CLK_CLKSEL3_UART4SEL_PLL         |\ref CLK_CLKDIV4_UART4(x) |
  * |\ref UART4_MODULE   |\ref CLK_CLKSEL3_UART4SEL_LXT         |\ref CLK_CLKDIV4_UART4(x) |
  * |\ref UART4_MODULE   |\ref CLK_CLKSEL3_UART4SEL_HIRC        |\ref CLK_CLKDIV4_UART4(x) |
  * |\ref UART4_MODULE   |\ref CLK_CLKSEL3_UART4SEL_PCLK0       |\ref CLK_CLKDIV4_UART4(x) |
  * |\ref UART4_MODULE   |\ref CLK_CLKSEL3_UART4SEL_LIRC        |\ref CLK_CLKDIV4_UART4(x) |
  * |\ref UART5_MODULE   |\ref CLK_CLKSEL3_UART5SEL_HXT         |\ref CLK_CLKDIV4_UART5(x) |
  * |\ref UART5_MODULE   |\ref CLK_CLKSEL3_UART5SEL_PLL         |\ref CLK_CLKDIV4_UART5(x) |
  * |\ref UART5_MODULE   |\ref CLK_CLKSEL3_UART5SEL_LXT         |\ref CLK_CLKDIV4_UART5(x) |
  * |\ref UART5_MODULE   |\ref CLK_CLKSEL3_UART5SEL_HIRC        |\ref CLK_CLKDIV4_UART5(x) |
  * |\ref UART5_MODULE   |\ref CLK_CLKSEL3_UART5SEL_PCLK1       |\ref CLK_CLKDIV4_UART5(x) |
  * |\ref UART5_MODULE   |\ref CLK_CLKSEL3_UART5SEL_LIRC        |\ref CLK_CLKDIV4_UART5(x) |
  * |\ref UART6_MODULE   |\ref CLK_CLKSEL3_UART6SEL_HXT         |\ref CLK_CLKDIV4_UART6(x) |
  * |\ref UART6_MODULE   |\ref CLK_CLKSEL3_UART6SEL_PLL         |\ref CLK_CLKDIV4_UART6(x) |
  * |\ref UART6_MODULE   |\ref CLK_CLKSEL3_UART6SEL_LXT         |\ref CLK_CLKDIV4_UART6(x) |
  * |\ref UART6_MODULE   |\ref CLK_CLKSEL3_UART6SEL_HIRC        |\ref CLK_CLKDIV4_UART6(x) |
  * |\ref UART6_MODULE   |\ref CLK_CLKSEL3_UART6SEL_PCLK0       |\ref CLK_CLKDIV4_UART6(x) |
  * |\ref UART6_MODULE   |\ref CLK_CLKSEL3_UART6SEL_LIRC        |\ref CLK_CLKDIV4_UART6(x) |
  * |\ref UART7_MODULE   |\ref CLK_CLKSEL3_UART7SEL_HXT         |\ref CLK_CLKDIV4_UART7(x) |
  * |\ref UART7_MODULE   |\ref CLK_CLKSEL3_UART7SEL_PLL         |\ref CLK_CLKDIV4_UART7(x) |
  * |\ref UART7_MODULE   |\ref CLK_CLKSEL3_UART7SEL_LXT         |\ref CLK_CLKDIV4_UART7(x) |
  * |\ref UART7_MODULE   |\ref CLK_CLKSEL3_UART7SEL_HIRC        |\ref CLK_CLKDIV4_UART7(x) |
  * |\ref UART7_MODULE   |\ref CLK_CLKSEL3_UART7SEL_PCLK1       |\ref CLK_CLKDIV4_UART7(x) |
  * |\ref UART7_MODULE   |\ref CLK_CLKSEL3_UART7SEL_LIRC        |\ref CLK_CLKDIV4_UART7(x) |
  * |\ref PWM0_MODULE    |\ref CLK_CLKSEL2_PWM0SEL_PLL          | x                        |
  * |\ref PWM0_MODULE    |\ref CLK_CLKSEL2_PWM0SEL_PCLK0        | x                        |
  * |\ref PWM1_MODULE    |\ref CLK_CLKSEL2_PWM1SEL_PLL          | x                        |
  * |\ref PWM1_MODULE    |\ref CLK_CLKSEL2_PWM1SEL_PCLK1        | x                        |
  * |\ref QSPI0_MODULE   |\ref CLK_CLKSEL2_QSPI0SEL_HXT         | x                        |
  * |\ref QSPI0_MODULE   |\ref CLK_CLKSEL2_QSPI0SEL_PLL         | x                        |
  * |\ref QSPI0_MODULE   |\ref CLK_CLKSEL2_QSPI0SEL_PCLK0       | x                        |
  * |\ref QSPI0_MODULE   |\ref CLK_CLKSEL2_QSPI0SEL_HIRC        | x                        |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL2_SPI0SEL_HXT          | x                        |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL2_SPI0SEL_PLL          | x                        |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL2_SPI0SEL_PCLK1        | x                        |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL2_SPI0SEL_HIRC         | x                        |
  * |\ref BPWM0_MODULE   |\ref CLK_CLKSEL2_BPWM0SEL_PLL         | x                        |
  * |\ref BPWM0_MODULE   |\ref CLK_CLKSEL2_BPWM0SEL_PCLK0       | x                        |
  * |\ref BPWM1_MODULE   |\ref CLK_CLKSEL2_BPWM1SEL_PLL         | x                        |
  * |\ref BPWM1_MODULE   |\ref CLK_CLKSEL2_BPWM1SEL_PCLK1       | x                        |
  * |\ref ADC_MODULE     |\ref CLK_CLKSEL2_ADCSEL_HXT           |\ref CLK_CLKDIV0_ADC(x)   |
  * |\ref ADC_MODULE     |\ref CLK_CLKSEL2_ADCSEL_PLL           |\ref CLK_CLKDIV0_ADC(x)   |
  * |\ref ADC_MODULE     |\ref CLK_CLKSEL2_ADCSEL_PCLK1         |\ref CLK_CLKDIV0_ADC(x)   |
  * |\ref ADC_MODULE     |\ref CLK_CLKSEL2_ADCSEL_HIRC          |\ref CLK_CLKDIV0_ADC(x)   |
  */
void CLK_SetModuleClock(uint32_t u32ModuleIdx, uint32_t u32ClkSrc, uint32_t u32ClkDiv)
{
    uint32_t u32sel = 0, u32div = 0;
    uint32_t u32SelTbl[4] = {0x0, 0x4, 0x8, 0xC};   /* CLKSEL offset on MODULE index, 0x0:CLKSEL0, 0x1:CLKSEL1, 0x2:CLKSEL2, 0x3:CLKSEL3 */
    uint32_t u32DivTbl[4] = {0x0, 0x0, 0x0, 0x10};  /* CLKDIV offset on MODULE index, 0x0:CLKDIV0, 0x1:CLKDIV1, 0x2:CLKDIV3, 0x3:CLKDIV4 */

    if(MODULE_CLKDIV_Msk(u32ModuleIdx) != MODULE_NoMsk)
    {
        /* Get clock divider control register address */
        u32div = (uint32_t)&CLK->CLKDIV0 + (u32DivTbl[MODULE_CLKDIV(u32ModuleIdx)]);
        /* Apply new divider */
        M32(u32div) = (M32(u32div) & (~(MODULE_CLKDIV_Msk(u32ModuleIdx) << MODULE_CLKDIV_Pos(u32ModuleIdx)))) | u32ClkDiv;
    }

    if(MODULE_CLKSEL_Msk(u32ModuleIdx) != MODULE_NoMsk)
    {
        /* Get clock select control register address */
        u32sel = (uint32_t)&CLK->CLKSEL0 + (u32SelTbl[MODULE_CLKSEL(u32ModuleIdx)]);
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
  * @brief      This function enable module clock
  * @param[in]  u32ModuleIdx is module index. Including :
  *             - \ref PDMA_MODULE
  *             - \ref ISP_MODULE
  *             - \ref EBI_MODULE
  *             - \ref HDIV_MODULE
  *             - \ref CRC_MODULE
  *             - \ref WDT_MODULE
  *             - \ref WWDT_MODULE
  *             - \ref RTC_MODULE
  *             - \ref TMR0_MODULE
  *             - \ref TMR1_MODULE
  *             - \ref TMR2_MODULE
  *             - \ref TMR3_MODULE
  *             - \ref CLKO_MODULE
  *             - \ref UART0_MODULE
  *             - \ref UART1_MODULE
  *             - \ref UART2_MODULE
  *             - \ref UART3_MODULE
  *             - \ref UART4_MODULE
  *             - \ref UART5_MODULE
  *             - \ref UART6_MODULE
  *             - \ref UART7_MODULE
  *             - \ref I2C0_MODULE
  *             - \ref I2C1_MODULE
  *             - \ref QSPI0_MODULE
  *             - \ref SPI0_MODULE
  *             - \ref ADC_MODULE
  *             - \ref ACMP01_MODULE
  *             - \ref USBD_MODULE
  *             - \ref PWM0_MODULE
  *             - \ref PWM1_MODULE
  *             - \ref BPWM0_MODULE
  *             - \ref BPWM1_MODULE
  *             - \ref USCI0_MODULE
  *             - \ref USCI1_MODULE
  * @return     None
  * @details    This function enable module clock.
  */
void CLK_EnableModuleClock(uint32_t u32ModuleIdx)
{
    uint32_t u32ClkTbl[3] = {0x0, 0x4, 0x8};    /* AHBCLK/APBCLK offset on MODULE index, 0x0:AHBCLK, 0x1:APBCLK0, 0x2:APBCLK1 */

    *(volatile uint32_t *)((uint32_t)&CLK->AHBCLK + (u32ClkTbl[MODULE_APBCLK(u32ModuleIdx)]))  |= 1 << MODULE_IP_EN_Pos(u32ModuleIdx);
}

/**
  * @brief      This function disable module clock
  * @param[in]  u32ModuleIdx is module index
  *             - \ref PDMA_MODULE
  *             - \ref ISP_MODULE
  *             - \ref EBI_MODULE
  *             - \ref HDIV_MODULE
  *             - \ref CRC_MODULE
  *             - \ref WDT_MODULE
  *             - \ref WWDT_MODULE
  *             - \ref RTC_MODULE
  *             - \ref TMR0_MODULE
  *             - \ref TMR1_MODULE
  *             - \ref TMR2_MODULE
  *             - \ref TMR3_MODULE
  *             - \ref CLKO_MODULE
  *             - \ref UART0_MODULE
  *             - \ref UART1_MODULE
  *             - \ref UART2_MODULE
  *             - \ref UART3_MODULE
  *             - \ref UART4_MODULE
  *             - \ref UART5_MODULE
  *             - \ref UART6_MODULE
  *             - \ref UART7_MODULE
  *             - \ref I2C0_MODULE
  *             - \ref I2C1_MODULE
  *             - \ref QSPI0_MODULE
  *             - \ref SPI0_MODULE
  *             - \ref ADC_MODULE
  *             - \ref ACMP01_MODULE
  *             - \ref USBD_MODULE
  *             - \ref PWM0_MODULE
  *             - \ref PWM1_MODULE
  *             - \ref BPWM0_MODULE
  *             - \ref BPWM1_MODULE
  *             - \ref USCI0_MODULE
  *             - \ref USCI1_MODULE
  * @return     None
  * @details    This function disable module clock.
  */
void CLK_DisableModuleClock(uint32_t u32ModuleIdx)
{
    uint32_t u32ClkTbl[3] = {0x0, 0x4, 0x8};    /* AHBCLK/APBCLK offset on MODULE index, 0x0:AHBCLK, 0x1:APBCLK0, 0x2:APBCLK1 */

    *(volatile uint32_t *)((uint32_t)&CLK->AHBCLK + (u32ClkTbl[MODULE_APBCLK(u32ModuleIdx)]))  &= ~(1 << MODULE_IP_EN_Pos(u32ModuleIdx));
}

/**
  * @brief      Set PLL frequency
  * @param[in]  u32PllClkSrc is PLL clock source. Including :
  *             - \ref CLK_PLLCTL_PLLSRC_HXT
  *             - \ref CLK_PLLCTL_PLLSRC_HIRC_DIV4
  * @param[in]  u32PllFreq is PLL frequency. The frequency unit is Hz.
  * @return     Actual PLL frequency
  * @details    This function is used to configure PLLCTL register to set specified PLL frequency. \n
  *             The register write-protection function should be disabled before using this function.
  */
uint32_t CLK_EnablePLL(uint32_t u32PllClkSrc, uint32_t u32PllFreq)
{
    uint32_t u32PllSrcClk, u32NR, u32NF, u32NO, u32CLK_SRC, u32Outdiv;
    uint32_t u32Tmp, u32Tmp2, u32Tmp3, u32Min, u32MinNF, u32MinNR;
    uint32_t u32PLL_UpperLimit;

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

        /* u32NR start from 2 since NR = INDIV + 2 */
        u32NR = 2;
    }

    /* PLL source clock is from HIRC/4 */
    else
    {
        /* Enable HIRC clock */
        CLK->PWRCTL |= CLK_PWRCTL_HIRCEN_Msk;

        /* Wait for HIRC clock ready */
        CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

        /* Select PLL source clock from HIRC */
        u32CLK_SRC = CLK_PLLCTL_PLLSRC_HIRC_DIV4;
        u32PllSrcClk = __HIRC >> 2;

        /* u32NR start from 2 since NR = INDIV + 2 */
        u32NR = 2;
    }

    /* Select "NO" according to request frequency */
    /* Constraint: PLL output frequency must <= 96MHz */
    /*             PLL output frequency must > 50.14MHz to meet all constraints */
    if ((GET_CHIP_SERIES_NUM == CHIP_SERIES_NUM_G) || (GET_CHIP_SERIES_NUM == CHIP_SERIES_NUM_I))
        u32PLL_UpperLimit = FREQ_144MHZ;
    else
        u32PLL_UpperLimit = FREQ_96MHZ;

    if((u32PllFreq <= u32PLL_UpperLimit) && (u32PllFreq >= FREQ_51MHZ))
    {
        if (u32PllFreq <= FREQ_96MHZ)
        {
            u32NO = 4;
            u32Outdiv = 3;
            u32PllFreq = u32PllFreq << 2;   /* u32PllFreq = (FIN * NF / NR) now */
        }
        else
        {
            u32NO = 2;
            u32Outdiv = 2;
            u32PllFreq = u32PllFreq << 1;   /* u32PllFreq = (FIN * NF / NR) now */
        }
    }
    else
    {
        /* Wrong frequency request. Just return default setting. */
        goto lexit;
    }

    /* Find best solution */
    u32Min = (uint32_t) 0xFFFFFFFF; /* initial u32Min to max value of uint32_t */
    u32MinNR = 0;
    u32MinNF = 0;
    for(; u32NR <= 33; u32NR++) /* max NR = 33 since NR = INDIV + 2 and INDIV = 0 ~ 31 */
    {
        u32Tmp = u32PllSrcClk / u32NR;
        /* Constraint 2: 800KHz < (FIN / (2*NR)) < 8MHz */
        if((u32Tmp > 1600000) && (u32Tmp < 16000000))
        {
            for(u32NF = 2; u32NF <= 513; u32NF++) /* NF = 2~513 since NF = FBDIV + 2 and FBDIV = 0 ~ 511 */
            {
                u32Tmp2 = u32Tmp * u32NF;
                /* Constraint 3: 200MHz < (FIN * NF / NR) < 500MHz */
                if((u32Tmp2 >= 200000000) && (u32Tmp2 < 500000000))
                {
                    u32Tmp3 = (u32Tmp2 > u32PllFreq) ? u32Tmp2 - u32PllFreq : u32PllFreq - u32Tmp2;
                    if(u32Tmp3 < u32Min)
                    {
                        u32Min = u32Tmp3;
                        u32MinNR = u32NR;
                        u32MinNF = u32NF;

                        /* Break when get good results */
                        if(u32Min == 0)
                            break;
                    }
                }
            }
        }
    }

    /* Enable and apply new PLL setting. */
    CLK->PLLCTL = u32CLK_SRC |
                  (u32Outdiv << CLK_PLLCTL_OUTDIV_Pos) |
                  ((u32MinNR - 2) << CLK_PLLCTL_INDIV_Pos) |
                  ((u32MinNF - 2) << CLK_PLLCTL_FBDIV_Pos);

    /* Wait for PLL clock stable */
    CLK_WaitClockReady(CLK_STATUS_PLLSTB_Msk);

    /* Return actual PLL output clock frequency */
    return (u32PllSrcClk / (u32NO * u32MinNR) * u32MinNF);

lexit:

    /* Apply default PLL setting and return */
    if(u32PllClkSrc == CLK_PLLCTL_PLLSRC_HXT)
        CLK->PLLCTL = CLK_PLLCTL_96MHz_HXT;
    else
        CLK->PLLCTL = CLK_PLLCTL_96MHz_HIRC_DIV4;

    /* Wait for PLL clock stable */
    CLK_WaitClockReady(CLK_STATUS_PLLSTB_Msk);

    return CLK_GetPLLClockFreq();
}

/**
  * @brief      Disable PLL
  * @param      None
  * @return     None
  * @details    This function set PLL in Power-down mode. \n
  *             If the current HCLK is PLL, this function will switch HCLK to HIRC before disable PLL. \n
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_DisablePLL(void)
{
    /* Switch HCLK to HIRC before disable PLL if current HCLK is PLL */
    if ((CLK->CLKSEL0 & CLK_CLKSEL0_HCLKSEL_Msk) == CLK_CLKSEL0_HCLKSEL_PLL)
    {
        CLK->PWRCTL |= CLK_PWRCTL_HIRCEN_Msk;
        CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);
        CLK->CLKSEL0 = (CLK->CLKSEL0 & (~CLK_CLKSEL0_HCLKSEL_Msk)) | CLK_CLKSEL0_HCLKSEL_HIRC;
    }

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

    while((CLK->STATUS & u32ClkMask) != u32ClkMask)
    {
        if(i32TimeOutCnt-- <= 0)
            return 0;
    }

    return 1;
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
    SysTick->CTRL = 0;

    /* Set System Tick clock source */
    if(u32ClkSrc == CLK_CLKSEL0_STCLKSEL_HCLK)
        SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
    else
        CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_STCLKSEL_Msk) | u32ClkSrc;

    /* Set System Tick reload value */
    SysTick->LOAD = u32Count;

    /* Clear System Tick current value and counter flag */
    SysTick->VAL = 0;

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
    SysTick->CTRL = 0;
}



/*@}*/ /* end of group CLK_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group CLK_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
