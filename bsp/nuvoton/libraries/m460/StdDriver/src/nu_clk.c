/**************************************************************************//**
 * @file     clk.c
 * @version  V3.00
 * @brief    M460 series CLK driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup CLK_Driver CLK Driver
  @{
*/

int32_t g_CLK_i32ErrCode = 0;    /*!< CLK global error code */

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
    CLK->APBCLK0 &= (~CLK_APBCLK0_CLKOCKEN_Msk);
}

/**
  * @brief      This function enable clock divider output module clock,
  *             enable clock divider output function and set frequency selection.
  * @param[in]  u32ClkSrc is frequency divider function clock source. Including :
  *             - \ref CLK_CLKSEL1_CLKOSEL_HXT
  *             - \ref CLK_CLKSEL1_CLKOSEL_LXT
  *             - \ref CLK_CLKSEL1_CLKOSEL_HCLK
  *             - \ref CLK_CLKSEL1_CLKOSEL_HIRC
  *             - \ref CLK_CLKSEL1_CLKOSEL_LIRC
  *             - \ref CLK_CLKSEL1_CLKOSEL_PLLFN_DIV2
  *             - \ref CLK_CLKSEL1_CLKOSEL_PLL_DIV2
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
    volatile uint32_t u32SysTickTICKINT = 0, u32HIRCTCTL = 0, u32IRCTCTL = 0;

    /* Set the processor uses deep sleep as its low power mode */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Set system Power-down enabled */
    CLK->PWRCTL |= (CLK_PWRCTL_PDEN_Msk);

    /* Store SysTick interrupt and HIRC auto trim setting */
    u32SysTickTICKINT = SysTick->CTRL & SysTick_CTRL_TICKINT_Msk;
    u32HIRCTCTL = SYS->HIRCTCTL;
    u32IRCTCTL = SYS->IRCTCTL;

    /* Disable SysTick interrupt and HIRC auto trim */
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
    SYS->HIRCTCTL &= (~SYS_HIRCTCTL_FREQSEL_Msk);
    SYS->IRCTCTL &= (~SYS_IRCTCTL_FREQSEL_Msk);

    /* Chip enter Power-down mode after CPU run WFI instruction */
    __WFI();

    /* Restore SysTick interrupt and HIRC auto trim setting */
    if (u32SysTickTICKINT) SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
    SYS->HIRCTCTL = u32HIRCTCTL;
    SYS->IRCTCTL = u32IRCTCTL;
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

    if (CLK->PWRCTL & CLK_PWRCTL_HXTEN_Msk)
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

    if (CLK->PWRCTL & CLK_PWRCTL_LXTEN_Msk)
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

    if ((CLK->PCLKDIV & CLK_PCLKDIV_APB0DIV_Msk) == CLK_PCLKDIV_APB0DIV_DIV1)
    {
        u32Freq = SystemCoreClock;
    }
    else if ((CLK->PCLKDIV & CLK_PCLKDIV_APB0DIV_Msk) == CLK_PCLKDIV_APB0DIV_DIV2)
    {
        u32Freq = SystemCoreClock >> 1;
    }
    else if ((CLK->PCLKDIV & CLK_PCLKDIV_APB0DIV_Msk) == CLK_PCLKDIV_APB0DIV_DIV4)
    {
        u32Freq = SystemCoreClock >> 2;
    }
    else if ((CLK->PCLKDIV & CLK_PCLKDIV_APB0DIV_Msk) == CLK_PCLKDIV_APB0DIV_DIV8)
    {
        u32Freq = SystemCoreClock >> 3;
    }
    else if ((CLK->PCLKDIV & CLK_PCLKDIV_APB0DIV_Msk) == CLK_PCLKDIV_APB0DIV_DIV16)
    {
        u32Freq = SystemCoreClock >> 4;
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

    if ((CLK->PCLKDIV & CLK_PCLKDIV_APB1DIV_Msk) == CLK_PCLKDIV_APB1DIV_DIV1)
    {
        u32Freq = SystemCoreClock;
    }
    else if ((CLK->PCLKDIV & CLK_PCLKDIV_APB1DIV_Msk) == CLK_PCLKDIV_APB1DIV_DIV2)
    {
        u32Freq = SystemCoreClock >> 1;
    }
    else if ((CLK->PCLKDIV & CLK_PCLKDIV_APB1DIV_Msk) == CLK_PCLKDIV_APB1DIV_DIV4)
    {
        u32Freq = SystemCoreClock >> 2;
    }
    else if ((CLK->PCLKDIV & CLK_PCLKDIV_APB1DIV_Msk) == CLK_PCLKDIV_APB1DIV_DIV8)
    {
        u32Freq = SystemCoreClock >> 3;
    }
    else if ((CLK->PCLKDIV & CLK_PCLKDIV_APB1DIV_Msk) == CLK_PCLKDIV_APB1DIV_DIV16)
    {
        u32Freq = SystemCoreClock >> 4;
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
  * @param[in]  u32Hclk is HCLK frequency. The range of u32Hclk is 50MHz ~ 200MHz.
  * @return     HCLK frequency
  * @details    This function is used to set HCLK frequency by using PLL. The frequency unit is Hz. \n
  *             Power level and flash access cycle are also set according to HCLK frequency. \n
  *             The register write-protection function should be disabled before using this function.
  */
uint32_t CLK_SetCoreClock(uint32_t u32Hclk)
{
    uint32_t u32HIRCSTB;

    /* Read HIRC clock source stable flag */
    u32HIRCSTB = CLK->STATUS & CLK_STATUS_HIRCSTB_Msk;

    /* Check HCLK frequency range is 50MHz ~ 200MHz */
    if (u32Hclk > FREQ_200MHZ)
    {
        u32Hclk = FREQ_200MHZ;
    }
    else if (u32Hclk < FREQ_50MHZ)
    {
        u32Hclk = FREQ_50MHZ;
    }

    /* Switch HCLK clock source to HIRC clock for safe */
    CLK->PWRCTL |= CLK_PWRCTL_HIRCEN_Msk;
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);
    CLK->CLKSEL0 |= CLK_CLKSEL0_HCLKSEL_Msk;
    CLK->CLKDIV0 &= (~CLK_CLKDIV0_HCLKDIV_Msk);

    /* Configure PLL setting if HXT clock is stable */
    if (CLK->STATUS & CLK_STATUS_HXTSTB_Msk)
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
       adjust power level, flash access cycle and update system core clock
    */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_PLL, CLK_CLKDIV0_HCLK(1UL));

    /* Disable HIRC if HIRC is disabled before setting core clock */
    if (u32HIRCSTB == 0UL)
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
    uint32_t u32HIRCSTB, u32TimeOutCount;

    /* Read HIRC clock source stable flag */
    u32HIRCSTB = CLK->STATUS & CLK_STATUS_HIRCSTB_Msk;

    /* Switch to HIRC for safe. Avoid HCLK too high when applying new divider. */
    CLK->PWRCTL |= CLK_PWRCTL_HIRCEN_Msk;
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);
    CLK->CLKSEL0 |= CLK_CLKSEL0_HCLKSEL_Msk;

    /* Switch to power level 0 for safe */
    SYS->PLCTL = (SYS->PLCTL & (~SYS_PLCTL_PLSEL_Msk)) | SYS_PLCTL_PLSEL_PL0;
    u32TimeOutCount = SystemCoreClock; /* 1 second time-out */
    while (SYS->PLSTS & SYS_PLSTS_PLCBUSY_Msk)
    {
        if (u32TimeOutCount-- == 0) break;
    }

    /* Set Flash Access Cycle to 8 for safe */
    FMC->CYCCTL = (FMC->CYCCTL & (~FMC_CYCCTL_CYCLE_Msk)) | (8);

    /* Apply new Divider */
    CLK->CLKDIV0 = (CLK->CLKDIV0 & (~CLK_CLKDIV0_HCLKDIV_Msk)) | u32ClkDiv;

    /* Switch HCLK to new HCLK source */
    CLK->CLKSEL0 = (CLK->CLKSEL0 & (~CLK_CLKSEL0_HCLKSEL_Msk)) | u32ClkSrc;

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    /* Set power level according to new HCLK */
    if (SystemCoreClock <= FREQ_180MHZ)
    {
        SYS->PLCTL = (SYS->PLCTL & (~SYS_PLCTL_PLSEL_Msk)) | SYS_PLCTL_PLSEL_PL1;
    }
    u32TimeOutCount = SystemCoreClock; /* 1 second time-out */
    while (SYS->PLSTS & SYS_PLSTS_PLCBUSY_Msk)
    {
        if (u32TimeOutCount-- == 0) break;
    }

    /* Switch flash access cycle to suitable value base on HCLK */
    if (SystemCoreClock >= FREQ_175MHZ)
    {
        FMC->CYCCTL = (FMC->CYCCTL & (~FMC_CYCCTL_CYCLE_Msk)) | (8);
    }
    else if (SystemCoreClock >= FREQ_150MHZ)
    {
        FMC->CYCCTL = (FMC->CYCCTL & (~FMC_CYCCTL_CYCLE_Msk)) | (7);
    }
    else if (SystemCoreClock >= FREQ_125MHZ)
    {
        FMC->CYCCTL = (FMC->CYCCTL & (~FMC_CYCCTL_CYCLE_Msk)) | (6);
    }
    else if (SystemCoreClock >= FREQ_100MHZ)
    {
        FMC->CYCCTL = (FMC->CYCCTL & (~FMC_CYCCTL_CYCLE_Msk)) | (5);
    }
    else if (SystemCoreClock >= FREQ_75MHZ)
    {
        FMC->CYCCTL = (FMC->CYCCTL & (~FMC_CYCCTL_CYCLE_Msk)) | (4);
    }
    else if (SystemCoreClock >= FREQ_50MHZ)
    {
        FMC->CYCCTL = (FMC->CYCCTL & (~FMC_CYCCTL_CYCLE_Msk)) | (3);
    }
    else if (SystemCoreClock >= FREQ_25MHZ)
    {
        FMC->CYCCTL = (FMC->CYCCTL & (~FMC_CYCCTL_CYCLE_Msk)) | (2);
    }
    else /* SystemCoreClock < FREQ_25MHZ */
    {
        FMC->CYCCTL = (FMC->CYCCTL & (~FMC_CYCCTL_CYCLE_Msk)) | (1);
    }

    /* Disable HIRC if HIRC is disabled before switching HCLK source */
    if (u32HIRCSTB == 0UL)
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
  * |\ref USBH_MODULE    |\ref CLK_CLKSEL0_USBSEL_HIRC48M        |\ref CLK_CLKDIV0_USB(x)        |
  * |\ref USBH_MODULE    |\ref CLK_CLKSEL0_USBSEL_PLL_DIV2       |\ref CLK_CLKDIV0_USB(x)        |
  * |\ref OTG_MODULE     |\ref CLK_CLKSEL0_USBSEL_HIRC48M        |\ref CLK_CLKDIV0_USB(x)        |
  * |\ref OTG_MODULE     |\ref CLK_CLKSEL0_USBSEL_PLL_DIV2       |\ref CLK_CLKDIV0_USB(x)        |
  * |\ref USBD_MODULE    |\ref CLK_CLKSEL0_USBSEL_HIRC48M        |\ref CLK_CLKDIV0_USB(x)        |
  * |\ref USBD_MODULE    |\ref CLK_CLKSEL0_USBSEL_PLL_DIV2       |\ref CLK_CLKDIV0_USB(x)        |
  * |\ref EADC0_MODULE   |\ref CLK_CLKSEL0_EADC0SEL_PLLFN_DIV2   |\ref CLK_CLKDIV0_EADC0(x)      |
  * |\ref EADC0_MODULE   |\ref CLK_CLKSEL0_EADC0SEL_PLL_DIV2     |\ref CLK_CLKDIV0_EADC0(x)      |
  * |\ref EADC0_MODULE   |\ref CLK_CLKSEL0_EADC0SEL_HCLK         |\ref CLK_CLKDIV0_EADC0(x)      |
  * |\ref EADC1_MODULE   |\ref CLK_CLKSEL0_EADC1SEL_PLLFN_DIV2   |\ref CLK_CLKDIV2_EADC1(x)      |
  * |\ref EADC1_MODULE   |\ref CLK_CLKSEL0_EADC1SEL_PLL_DIV2     |\ref CLK_CLKDIV2_EADC1(x)      |
  * |\ref EADC1_MODULE   |\ref CLK_CLKSEL0_EADC1SEL_HCLK         |\ref CLK_CLKDIV2_EADC1(x)      |
  * |\ref EADC2_MODULE   |\ref CLK_CLKSEL0_EADC2SEL_PLLFN_DIV2   |\ref CLK_CLKDIV5_EADC2(x)      |
  * |\ref EADC2_MODULE   |\ref CLK_CLKSEL0_EADC2SEL_PLL_DIV2     |\ref CLK_CLKDIV5_EADC2(x)      |
  * |\ref EADC2_MODULE   |\ref CLK_CLKSEL0_EADC2SEL_HCLK         |\ref CLK_CLKDIV5_EADC2(x)      |
  * |\ref CCAP_MODULE    | x                                     | x                             |
  * |\ref CCAP_MODULE    | x                                     | x                             |
  * |\ref CCAP_MODULE    | x                                     | x                             |
  * |\ref CCAP_MODULE    | x                                     | x                             |
  * |\ref SEN_MODULE     |\ref CLK_CLKSEL0_CCAPSEL_HXT           |\ref CLK_CLKDIV3_VSENSE(x)     |
  * |\ref SEN_MODULE     |\ref CLK_CLKSEL0_CCAPSEL_PLL_DIV2      |\ref CLK_CLKDIV3_VSENSE(x)     |
  * |\ref SEN_MODULE     |\ref CLK_CLKSEL0_CCAPSEL_HCLK          |\ref CLK_CLKDIV3_VSENSE(x)     |
  * |\ref SEN_MODULE     |\ref CLK_CLKSEL0_CCAPSEL_HIRC          |\ref CLK_CLKDIV3_VSENSE(x)     |
  * |\ref SDH0_MODULE    |\ref CLK_CLKSEL0_SDH0SEL_HXT           |\ref CLK_CLKDIV0_SDH0(x)       |
  * |\ref SDH0_MODULE    |\ref CLK_CLKSEL0_SDH0SEL_PLL_DIV2      |\ref CLK_CLKDIV0_SDH0(x)       |
  * |\ref SDH0_MODULE    |\ref CLK_CLKSEL0_SDH0SEL_HIRC          |\ref CLK_CLKDIV0_SDH0(x)       |
  * |\ref SDH0_MODULE    |\ref CLK_CLKSEL0_SDH0SEL_HCLK          |\ref CLK_CLKDIV0_SDH0(x)       |
  * |\ref SDH1_MODULE    |\ref CLK_CLKSEL0_SDH1SEL_HXT           |\ref CLK_CLKDIV3_SDH1(x)       |
  * |\ref SDH1_MODULE    |\ref CLK_CLKSEL0_SDH1SEL_PLL_DIV2      |\ref CLK_CLKDIV3_SDH1(x)       |
  * |\ref SDH1_MODULE    |\ref CLK_CLKSEL0_SDH1SEL_HIRC          |\ref CLK_CLKDIV3_SDH1(x)       |
  * |\ref SDH1_MODULE    |\ref CLK_CLKSEL0_SDH1SEL_HCLK          |\ref CLK_CLKDIV3_SDH1(x)       |
  * |\ref CANFD0_MODULE  |\ref CLK_CLKSEL0_CANFD0SEL_HXT         |\ref CLK_CLKDIV5_CANFD0(x)     |
  * |\ref CANFD0_MODULE  |\ref CLK_CLKSEL0_CANFD0SEL_PLL_DIV2    |\ref CLK_CLKDIV5_CANFD0(x)     |
  * |\ref CANFD0_MODULE  |\ref CLK_CLKSEL0_CANFD0SEL_HCLK        |\ref CLK_CLKDIV5_CANFD0(x)     |
  * |\ref CANFD0_MODULE  |\ref CLK_CLKSEL0_CANFD0SEL_HIRC        |\ref CLK_CLKDIV5_CANFD0(x)     |
  * |\ref CANFD1_MODULE  |\ref CLK_CLKSEL0_CANFD1SEL_HXT         |\ref CLK_CLKDIV5_CANFD1(x)     |
  * |\ref CANFD1_MODULE  |\ref CLK_CLKSEL0_CANFD1SEL_PLL_DIV2    |\ref CLK_CLKDIV5_CANFD1(x)     |
  * |\ref CANFD1_MODULE  |\ref CLK_CLKSEL0_CANFD1SEL_HCLK        |\ref CLK_CLKDIV5_CANFD1(x)     |
  * |\ref CANFD1_MODULE  |\ref CLK_CLKSEL0_CANFD1SEL_HIRC        |\ref CLK_CLKDIV5_CANFD1(x)     |
  * |\ref CANFD2_MODULE  |\ref CLK_CLKSEL0_CANFD2SEL_HXT         |\ref CLK_CLKDIV5_CANFD2(x)     |
  * |\ref CANFD2_MODULE  |\ref CLK_CLKSEL0_CANFD2SEL_PLL_DIV2    |\ref CLK_CLKDIV5_CANFD2(x)     |
  * |\ref CANFD2_MODULE  |\ref CLK_CLKSEL0_CANFD2SEL_HCLK        |\ref CLK_CLKDIV5_CANFD2(x)     |
  * |\ref CANFD2_MODULE  |\ref CLK_CLKSEL0_CANFD2SEL_HIRC        |\ref CLK_CLKDIV5_CANFD2(x)     |
  * |\ref CANFD3_MODULE  |\ref CLK_CLKSEL0_CANFD3SEL_HXT         |\ref CLK_CLKDIV5_CANFD3(x)     |
  * |\ref CANFD3_MODULE  |\ref CLK_CLKSEL0_CANFD3SEL_PLL_DIV2    |\ref CLK_CLKDIV5_CANFD3(x)     |
  * |\ref CANFD3_MODULE  |\ref CLK_CLKSEL0_CANFD3SEL_HCLK        |\ref CLK_CLKDIV5_CANFD3(x)     |
  * |\ref CANFD3_MODULE  |\ref CLK_CLKSEL0_CANFD3SEL_HIRC        |\ref CLK_CLKDIV5_CANFD3(x)     |
  * |\ref EMAC0_MODULE   | x                                     |\ref CLK_CLKDIV3_EMAC0(x)      |
  * |\ref WDT_MODULE     |\ref CLK_CLKSEL1_WDTSEL_LXT            | x                             |
  * |\ref WDT_MODULE     |\ref CLK_CLKSEL1_WDTSEL_HCLK_DIV2048   | x                             |
  * |\ref WDT_MODULE     |\ref CLK_CLKSEL1_WDTSEL_LIRC           | x                             |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_HXT           | x                             |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_LXT           | x                             |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_HCLK          | x                             |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_HIRC          | x                             |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_LIRC          | x                             |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_PLLFN_DIV2    | x                             |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_PLL_DIV2      | x                             |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_HXT           | x                             |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_LXT           | x                             |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_PCLK0         | x                             |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_EXT           | x                             |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_LIRC          | x                             |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_HIRC          | x                             |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_HXT           | x                             |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_LXT           | x                             |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_PCLK0         | x                             |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_EXT           | x                             |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_LIRC          | x                             |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_HIRC          | x                             |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_HXT           | x                             |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_LXT           | x                             |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_PCLK1         | x                             |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_EXT           | x                             |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_LIRC          | x                             |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_HIRC          | x                             |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_HXT           | x                             |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_LXT           | x                             |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_PCLK1         | x                             |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_EXT           | x                             |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_LIRC          | x                             |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_HIRC          | x                             |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL1_UART0SEL_HXT          |\ref CLK_CLKDIV0_UART0(x)      |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL1_UART0SEL_PLL_DIV2     |\ref CLK_CLKDIV0_UART0(x)      |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL1_UART0SEL_LXT          |\ref CLK_CLKDIV0_UART0(x)      |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL1_UART0SEL_HIRC         |\ref CLK_CLKDIV0_UART0(x)      |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL1_UART1SEL_HXT          |\ref CLK_CLKDIV0_UART1(x)      |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL1_UART1SEL_PLL_DIV2     |\ref CLK_CLKDIV0_UART1(x)      |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL1_UART1SEL_LXT          |\ref CLK_CLKDIV0_UART1(x)      |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL1_UART1SEL_HIRC         |\ref CLK_CLKDIV0_UART1(x)      |
  * |\ref WWDT_MODULE    |\ref CLK_CLKSEL1_WWDTSEL_HCLK_DIV2048  | x                             |
  * |\ref WWDT_MODULE    |\ref CLK_CLKSEL1_WWDTSEL_LIRC          | x                             |
  * |\ref EPWM0_MODULE   |\ref CLK_CLKSEL2_EPWM0SEL_HCLK         | x                             |
  * |\ref EPWM0_MODULE   |\ref CLK_CLKSEL2_EPWM0SEL_PCLK0        | x                             |
  * |\ref EPWM1_MODULE   |\ref CLK_CLKSEL2_EPWM1SEL_HCLK         | x                             |
  * |\ref EPWM1_MODULE   |\ref CLK_CLKSEL2_EPWM1SEL_PCLK1        | x                             |
  * |\ref QSPI0_MODULE   |\ref CLK_CLKSEL2_QSPI0SEL_HXT          | x                             |
  * |\ref QSPI0_MODULE   |\ref CLK_CLKSEL2_QSPI0SEL_PLL_DIV2     | x                             |
  * |\ref QSPI0_MODULE   |\ref CLK_CLKSEL2_QSPI0SEL_PCLK0        | x                             |
  * |\ref QSPI0_MODULE   |\ref CLK_CLKSEL2_QSPI0SEL_HIRC         | x                             |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL2_SPI0SEL_HXT           | x                             |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL2_SPI0SEL_PLL_DIV2      | x                             |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL2_SPI0SEL_PCLK1         | x                             |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL2_SPI0SEL_HIRC          | x                             |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL2_SPI0SEL_HIRC48M       | x                             |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL2_SPI0SEL_PLLFN_DIV2    | x                             |
  * |\ref BPWM0_MODULE   |\ref CLK_CLKSEL2_BPWM0SEL_HCLK         | x                             |
  * |\ref BPWM0_MODULE   |\ref CLK_CLKSEL2_BPWM0SEL_PCLK0        | x                             |
  * |\ref BPWM1_MODULE   |\ref CLK_CLKSEL2_BPWM1SEL_HCLK         | x                             |
  * |\ref BPWM1_MODULE   |\ref CLK_CLKSEL2_BPWM1SEL_PCLK1        | x                             |
  * |\ref QSPI1_MODULE   |\ref CLK_CLKSEL3_QSPI1SEL_HXT          | x                             |
  * |\ref QSPI1_MODULE   |\ref CLK_CLKSEL3_QSPI1SEL_PLL_DIV2     | x                             |
  * |\ref QSPI1_MODULE   |\ref CLK_CLKSEL3_QSPI1SEL_PCLK1        | x                             |
  * |\ref QSPI1_MODULE   |\ref CLK_CLKSEL3_QSPI1SEL_HIRC         | x                             |
  * |\ref SPI1_MODULE    |\ref CLK_CLKSEL2_SPI1SEL_HXT           | x                             |
  * |\ref SPI1_MODULE    |\ref CLK_CLKSEL2_SPI1SEL_PLL_DIV2      | x                             |
  * |\ref SPI1_MODULE    |\ref CLK_CLKSEL2_SPI1SEL_PCLK0         | x                             |
  * |\ref SPI1_MODULE    |\ref CLK_CLKSEL2_SPI1SEL_HIRC          | x                             |
  * |\ref SPI1_MODULE    |\ref CLK_CLKSEL2_SPI1SEL_HIRC48M       | x                             |
  * |\ref SPI1_MODULE    |\ref CLK_CLKSEL2_SPI1SEL_PLLFN_DIV2    | x                             |
  * |\ref I2S1_MODULE    |\ref CLK_CLKSEL2_I2S1SEL_HXT           |\ref CLK_CLKDIV2_I2S1(x)       |
  * |\ref I2S1_MODULE    |\ref CLK_CLKSEL2_I2S1SEL_PLL_DIV2      |\ref CLK_CLKDIV2_I2S1(x)       |
  * |\ref I2S1_MODULE    |\ref CLK_CLKSEL2_I2S1SEL_PCLK1         |\ref CLK_CLKDIV2_I2S1(x)       |
  * |\ref I2S1_MODULE    |\ref CLK_CLKSEL2_I2S1SEL_HIRC          |\ref CLK_CLKDIV2_I2S1(x)       |
  * |\ref I2S1_MODULE    |\ref CLK_CLKSEL2_I2S1SEL_HIRC48M       |\ref CLK_CLKDIV2_I2S1(x)       |
  * |\ref I2S1_MODULE    |\ref CLK_CLKSEL2_I2S1SEL_PLLFN_DIV2    |\ref CLK_CLKDIV2_I2S1(x)       |
  * |\ref UART8_MODULE   |\ref CLK_CLKSEL2_UART8SEL_HXT          |\ref CLK_CLKDIV5_UART8(x)      |
  * |\ref UART8_MODULE   |\ref CLK_CLKSEL2_UART8SEL_PLL_DIV2     |\ref CLK_CLKDIV5_UART8(x)      |
  * |\ref UART8_MODULE   |\ref CLK_CLKSEL2_UART8SEL_LXT          |\ref CLK_CLKDIV5_UART8(x)      |
  * |\ref UART8_MODULE   |\ref CLK_CLKSEL2_UART8SEL_HIRC         |\ref CLK_CLKDIV5_UART8(x)      |
  * |\ref UART9_MODULE   |\ref CLK_CLKSEL2_UART9SEL_HXT          |\ref CLK_CLKDIV5_UART9(x)      |
  * |\ref UART9_MODULE   |\ref CLK_CLKSEL2_UART9SEL_PLL_DIV2     |\ref CLK_CLKDIV5_UART9(x)      |
  * |\ref UART9_MODULE   |\ref CLK_CLKSEL2_UART9SEL_LXT          |\ref CLK_CLKDIV5_UART9(x)      |
  * |\ref UART9_MODULE   |\ref CLK_CLKSEL2_UART9SEL_HIRC         |\ref CLK_CLKDIV5_UART9(x)      |
  * |\ref TRNG_MODULE    |\ref CLK_CLKSEL2_TRNGSEL_LXT           | x                             |
  * |\ref TRNG_MODULE    |\ref CLK_CLKSEL2_TRNGSEL_LIRC          | x                             |
  * |\ref PSIO_MODULE    |\ref CLK_CLKSEL2_PSIOSEL_HXT           |\ref CLK_CLKDIV1_PSIO(x)       |
  * |\ref PSIO_MODULE    |\ref CLK_CLKSEL2_PSIOSEL_LXT           |\ref CLK_CLKDIV1_PSIO(x)       |
  * |\ref PSIO_MODULE    |\ref CLK_CLKSEL2_PSIOSEL_PCLK1         |\ref CLK_CLKDIV1_PSIO(x)       |
  * |\ref PSIO_MODULE    |\ref CLK_CLKSEL2_PSIOSEL_PLL_DIV2      |\ref CLK_CLKDIV1_PSIO(x)       |
  * |\ref PSIO_MODULE    |\ref CLK_CLKSEL2_PSIOSEL_LIRC          |\ref CLK_CLKDIV1_PSIO(x)       |
  * |\ref PSIO_MODULE    |\ref CLK_CLKSEL2_PSIOSEL_HIRC          |\ref CLK_CLKDIV1_PSIO(x)       |
  * |\ref SC0_MODULE     |\ref CLK_CLKSEL3_SC0SEL_HXT            |\ref CLK_CLKDIV1_SC0(x)        |
  * |\ref SC0_MODULE     |\ref CLK_CLKSEL3_SC0SEL_PLL_DIV2       |\ref CLK_CLKDIV1_SC0(x)        |
  * |\ref SC0_MODULE     |\ref CLK_CLKSEL3_SC0SEL_PCLK0          |\ref CLK_CLKDIV1_SC0(x)        |
  * |\ref SC0_MODULE     |\ref CLK_CLKSEL3_SC0SEL_HIRC           |\ref CLK_CLKDIV1_SC0(x)        |
  * |\ref SC1_MODULE     |\ref CLK_CLKSEL3_SC1SEL_HXT            |\ref CLK_CLKDIV1_SC1(x)        |
  * |\ref SC1_MODULE     |\ref CLK_CLKSEL3_SC1SEL_PLL_DIV2       |\ref CLK_CLKDIV1_SC1(x)        |
  * |\ref SC1_MODULE     |\ref CLK_CLKSEL3_SC1SEL_PCLK1          |\ref CLK_CLKDIV1_SC1(x)        |
  * |\ref SC1_MODULE     |\ref CLK_CLKSEL3_SC1SEL_HIRC           |\ref CLK_CLKDIV1_SC1(x)        |
  * |\ref SC2_MODULE     |\ref CLK_CLKSEL3_SC2SEL_HXT            |\ref CLK_CLKDIV1_SC2(x)        |
  * |\ref SC2_MODULE     |\ref CLK_CLKSEL3_SC2SEL_PLL_DIV2       |\ref CLK_CLKDIV1_SC2(x)        |
  * |\ref SC2_MODULE     |\ref CLK_CLKSEL3_SC2SEL_PCLK0          |\ref CLK_CLKDIV1_SC2(x)        |
  * |\ref SC2_MODULE     |\ref CLK_CLKSEL3_SC2SEL_HIRC           |\ref CLK_CLKDIV1_SC2(x)        |
  * |\ref KPI_MODULE     |\ref CLK_CLKSEL3_KPISEL_HXT            |\ref CLK_CLKDIV2_KPI(x)        |
  * |\ref KPI_MODULE     |\ref CLK_CLKSEL3_KPISEL_LIRC           |\ref CLK_CLKDIV1_KPI(x)        |
  * |\ref KPI_MODULE     |\ref CLK_CLKSEL3_KPISEL_HIRC           |\ref CLK_CLKDIV1_KPI(x)        |
  * |\ref SPI2_MODULE    |\ref CLK_CLKSEL3_SPI2SEL_HXT           | x                             |
  * |\ref SPI2_MODULE    |\ref CLK_CLKSEL3_SPI2SEL_PLL_DIV2      | x                             |
  * |\ref SPI2_MODULE    |\ref CLK_CLKSEL3_SPI2SEL_PCLK1         | x                             |
  * |\ref SPI2_MODULE    |\ref CLK_CLKSEL3_SPI2SEL_HIRC          | x                             |
  * |\ref SPI2_MODULE    |\ref CLK_CLKSEL3_SPI2SEL_HIRC48M       | x                             |
  * |\ref SPI2_MODULE    |\ref CLK_CLKSEL3_SPI2SEL_PLLFN_DIV2    | x                             |
  * |\ref SPI3_MODULE    |\ref CLK_CLKSEL3_SPI3SEL_HXT           | x                             |
  * |\ref SPI3_MODULE    |\ref CLK_CLKSEL3_SPI3SEL_PLL_DIV2      | x                             |
  * |\ref SPI3_MODULE    |\ref CLK_CLKSEL3_SPI3SEL_PCLK0         | x                             |
  * |\ref SPI3_MODULE    |\ref CLK_CLKSEL3_SPI3SEL_HIRC          | x                             |
  * |\ref SPI3_MODULE    |\ref CLK_CLKSEL3_SPI3SEL_HIRC48M       | x                             |
  * |\ref SPI3_MODULE    |\ref CLK_CLKSEL3_SPI3SEL_PLLFN_DIV2    | x                             |
  * |\ref I2S0_MODULE    |\ref CLK_CLKSEL3_I2S0SEL_HXT           |\ref CLK_CLKDIV2_I2S0(x)       |
  * |\ref I2S0_MODULE    |\ref CLK_CLKSEL3_I2S0SEL_PLL_DIV2      |\ref CLK_CLKDIV2_I2S0(x)       |
  * |\ref I2S0_MODULE    |\ref CLK_CLKSEL3_I2S0SEL_PCLK0         |\ref CLK_CLKDIV2_I2S0(x)       |
  * |\ref I2S0_MODULE    |\ref CLK_CLKSEL3_I2S0SEL_HIRC          |\ref CLK_CLKDIV2_I2S0(x)       |
  * |\ref I2S0_MODULE    |\ref CLK_CLKSEL3_I2S0SEL_HIRC48M       |\ref CLK_CLKDIV2_I2S0(x)       |
  * |\ref I2S0_MODULE    |\ref CLK_CLKSEL3_I2S0SEL_PLLFN_DIV2    |\ref CLK_CLKDIV2_I2S0(x)       |
  * |\ref UART6_MODULE   |\ref CLK_CLKSEL3_UART6SEL_HXT          |\ref CLK_CLKDIV4_UART6(x)      |
  * |\ref UART6_MODULE   |\ref CLK_CLKSEL3_UART6SEL_PLL_DIV2     |\ref CLK_CLKDIV4_UART6(x)      |
  * |\ref UART6_MODULE   |\ref CLK_CLKSEL3_UART6SEL_LXT          |\ref CLK_CLKDIV4_UART6(x)      |
  * |\ref UART6_MODULE   |\ref CLK_CLKSEL3_UART6SEL_HIRC         |\ref CLK_CLKDIV4_UART6(x)      |
  * |\ref UART7_MODULE   |\ref CLK_CLKSEL3_UART7SEL_HXT          |\ref CLK_CLKDIV4_UART7(x)      |
  * |\ref UART7_MODULE   |\ref CLK_CLKSEL3_UART7SEL_PLL_DIV2     |\ref CLK_CLKDIV4_UART7(x)      |
  * |\ref UART7_MODULE   |\ref CLK_CLKSEL3_UART7SEL_LXT          |\ref CLK_CLKDIV4_UART7(x)      |
  * |\ref UART7_MODULE   |\ref CLK_CLKSEL3_UART7SEL_HIRC         |\ref CLK_CLKDIV4_UART7(x)      |
  * |\ref UART2_MODULE   |\ref CLK_CLKSEL3_UART2SEL_HXT          |\ref CLK_CLKDIV4_UART2(x)      |
  * |\ref UART2_MODULE   |\ref CLK_CLKSEL3_UART2SEL_PLL_DIV2     |\ref CLK_CLKDIV4_UART2(x)      |
  * |\ref UART2_MODULE   |\ref CLK_CLKSEL3_UART2SEL_LXT          |\ref CLK_CLKDIV4_UART2(x)      |
  * |\ref UART2_MODULE   |\ref CLK_CLKSEL3_UART2SEL_HIRC         |\ref CLK_CLKDIV4_UART2(x)      |
  * |\ref UART3_MODULE   |\ref CLK_CLKSEL3_UART3SEL_HXT          |\ref CLK_CLKDIV4_UART3(x)      |
  * |\ref UART3_MODULE   |\ref CLK_CLKSEL3_UART3SEL_PLL_DIV2     |\ref CLK_CLKDIV4_UART3(x)      |
  * |\ref UART3_MODULE   |\ref CLK_CLKSEL3_UART3SEL_LXT          |\ref CLK_CLKDIV4_UART3(x)      |
  * |\ref UART3_MODULE   |\ref CLK_CLKSEL3_UART3SEL_HIRC         |\ref CLK_CLKDIV4_UART3(x)      |
  * |\ref UART4_MODULE   |\ref CLK_CLKSEL3_UART4SEL_HXT          |\ref CLK_CLKDIV4_UART4(x)      |
  * |\ref UART4_MODULE   |\ref CLK_CLKSEL3_UART4SEL_PLL_DIV2     |\ref CLK_CLKDIV4_UART4(x)      |
  * |\ref UART4_MODULE   |\ref CLK_CLKSEL3_UART4SEL_LXT          |\ref CLK_CLKDIV4_UART4(x)      |
  * |\ref UART4_MODULE   |\ref CLK_CLKSEL3_UART4SEL_HIRC         |\ref CLK_CLKDIV4_UART4(x)      |
  * |\ref UART5_MODULE   |\ref CLK_CLKSEL3_UART5SEL_HXT          |\ref CLK_CLKDIV4_UART5(x)      |
  * |\ref UART5_MODULE   |\ref CLK_CLKSEL3_UART5SEL_PLL_DIV2     |\ref CLK_CLKDIV4_UART5(x)      |
  * |\ref UART5_MODULE   |\ref CLK_CLKSEL3_UART5SEL_LXT          |\ref CLK_CLKDIV4_UART5(x)      |
  * |\ref UART5_MODULE   |\ref CLK_CLKSEL3_UART5SEL_HIRC         |\ref CLK_CLKDIV4_UART5(x)      |
  * |\ref RTC_MODULE     |\ref RTC_LXTCTL_RTCCKSEL_LXT           | x                             |
  * |\ref RTC_MODULE     |\ref RTC_LXTCTL_RTCCKSEL_LIRC          | x                             |
  * |\ref SPI4_MODULE    |\ref CLK_CLKSEL4_SPI4SEL_HXT           | x                             |
  * |\ref SPI4_MODULE    |\ref CLK_CLKSEL4_SPI4SEL_PLL_DIV2      | x                             |
  * |\ref SPI4_MODULE    |\ref CLK_CLKSEL4_SPI4SEL_PCLK1         | x                             |
  * |\ref SPI4_MODULE    |\ref CLK_CLKSEL4_SPI4SEL_HIRC          | x                             |
  * |\ref SPI5_MODULE    |\ref CLK_CLKSEL4_SPI5SEL_HXT           | x                             |
  * |\ref SPI5_MODULE    |\ref CLK_CLKSEL4_SPI5SEL_PLL_DIV2      | x                             |
  * |\ref SPI5_MODULE    |\ref CLK_CLKSEL4_SPI5SEL_PCLK0         | x                             |
  * |\ref SPI5_MODULE    |\ref CLK_CLKSEL4_SPI5SEL_HIRC          | x                             |
  * |\ref SPI6_MODULE    |\ref CLK_CLKSEL4_SPI6SEL_HXT           | x                             |
  * |\ref SPI6_MODULE    |\ref CLK_CLKSEL4_SPI6SEL_PLL_DIV2      | x                             |
  * |\ref SPI6_MODULE    |\ref CLK_CLKSEL4_SPI6SEL_PCLK1         | x                             |
  * |\ref SPI6_MODULE    |\ref CLK_CLKSEL4_SPI6SEL_HIRC          | x                             |
  * |\ref SPI7_MODULE    |\ref CLK_CLKSEL4_SPI7SEL_HXT           | x                             |
  * |\ref SPI7_MODULE    |\ref CLK_CLKSEL4_SPI7SEL_PLL_DIV2      | x                             |
  * |\ref SPI7_MODULE    |\ref CLK_CLKSEL4_SPI7SEL_PCLK0         | x                             |
  * |\ref SPI7_MODULE    |\ref CLK_CLKSEL4_SPI7SEL_HIRC          | x                             |
  * |\ref SPI8_MODULE    |\ref CLK_CLKSEL4_SPI8SEL_HXT           | x                             |
  * |\ref SPI8_MODULE    |\ref CLK_CLKSEL4_SPI8SEL_PLL_DIV2      | x                             |
  * |\ref SPI8_MODULE    |\ref CLK_CLKSEL4_SPI8SEL_PCLK1         | x                             |
  * |\ref SPI8_MODULE    |\ref CLK_CLKSEL4_SPI8SEL_HIRC          | x                             |
  * |\ref SPI9_MODULE    |\ref CLK_CLKSEL4_SPI9SEL_HXT           | x                             |
  * |\ref SPI9_MODULE    |\ref CLK_CLKSEL4_SPI9SEL_PLL_DIV2      | x                             |
  * |\ref SPI9_MODULE    |\ref CLK_CLKSEL4_SPI9SEL_PCLK0         | x                             |
  * |\ref SPI9_MODULE    |\ref CLK_CLKSEL4_SPI9SEL_HIRC          | x                             |
  * |\ref SPI10_MODULE   |\ref CLK_CLKSEL4_SPI10SEL_HXT          | x                             |
  * |\ref SPI10_MODULE   |\ref CLK_CLKSEL4_SPI10SEL_PLL_DIV2     | x                             |
  * |\ref SPI10_MODULE   |\ref CLK_CLKSEL4_SPI10SEL_PCLK1        | x                             |
  * |\ref SPI10_MODULE   |\ref CLK_CLKSEL4_SPI10SEL_HIRC         | x                             |
  *
  */
void CLK_SetModuleClock(uint32_t u32ModuleIdx, uint32_t u32ClkSrc, uint32_t u32ClkDiv)
{
    uint32_t u32Sel = 0UL, u32Div = 0UL;
    uint32_t au32SelTbl[5] = {0x0UL, 0x4UL, 0x8UL, 0xCUL, 0x4CUL};       /* CLK_CLKSEL0~4 */
    uint32_t au32DivTbl[6] = {0x0UL, 0x4UL, 0x8UL, 0xCUL, 0x10UL, 0x1C}; /* CLK_CLKDIV0~5 */
    uint32_t u32RTCCKEN = CLK->APBCLK0 & CLK_APBCLK0_RTCCKEN_Msk;

    if (u32ModuleIdx == RTC_MODULE)     /* RTC clock source configuration */
    {
        if (u32RTCCKEN == 0UL)
        {
            CLK->APBCLK0 |= CLK_APBCLK0_RTCCKEN_Msk; /* Enable RTC clock to get LXT clock source */
        }

        /* Select RTC clock source */
        RTC->LXTCTL = (RTC->LXTCTL & (~RTC_LXTCTL_RTCCKSEL_Msk)) | (u32ClkSrc);

        if (u32RTCCKEN == 0UL)
        {
            CLK->APBCLK0 &= (~CLK_APBCLK0_RTCCKEN_Msk); /* Disable RTC clock if it is disabled before */
        }
    }
    else /* Others clock source configuration */
    {
        /* Configure clock source divider */
        switch (u32ModuleIdx)
        {
        /* For 8 bits divider */
        case EADC0_MODULE:
            CLK->CLKDIV0 = (CLK->CLKDIV0 & (~CLK_CLKDIV0_EADC0DIV_Msk)) | (u32ClkDiv);
            break;
        case SDH0_MODULE:
            CLK->CLKDIV0 = (CLK->CLKDIV0 & (~CLK_CLKDIV0_SDH0DIV_Msk)) | (u32ClkDiv);
            break;
        case SC0_MODULE:
            CLK->CLKDIV1 = (CLK->CLKDIV1 & (~CLK_CLKDIV1_SC0DIV_Msk)) | (u32ClkDiv);
            break;
        case SC1_MODULE:
            CLK->CLKDIV1 = (CLK->CLKDIV1 & (~CLK_CLKDIV1_SC1DIV_Msk)) | (u32ClkDiv);
            break;
        case SC2_MODULE:
            CLK->CLKDIV1 = (CLK->CLKDIV1 & (~CLK_CLKDIV1_SC2DIV_Msk)) | (u32ClkDiv);
            break;
        case PSIO_MODULE:
            CLK->CLKDIV1 = (CLK->CLKDIV1 & (~CLK_CLKDIV1_PSIODIV_Msk)) | (u32ClkDiv);
            break;
        case KPI_MODULE:
            CLK->CLKDIV2 = (CLK->CLKDIV2 & (~CLK_CLKDIV2_KPIDIV_Msk)) | (u32ClkDiv);
            break;
        case EADC1_MODULE:
            CLK->CLKDIV2 = (CLK->CLKDIV2 & (~CLK_CLKDIV2_EADC1DIV_Msk)) | (u32ClkDiv);
            break;
        case SEN_MODULE:
            CLK->CLKDIV3 = (CLK->CLKDIV3 & (~CLK_CLKDIV3_VSENSEDIV_Msk)) | (u32ClkDiv);
            break;
        case EMAC0_MODULE:
            CLK->CLKDIV3 = (CLK->CLKDIV3 & (~CLK_CLKDIV3_EMAC0DIV_Msk)) | (u32ClkDiv);
            break;
        case SDH1_MODULE:
            CLK->CLKDIV3 = (CLK->CLKDIV3 & (~CLK_CLKDIV3_SDH1DIV_Msk)) | (u32ClkDiv);
            break;
        case EADC2_MODULE:
            CLK->CLKDIV5 = (CLK->CLKDIV5 & (~CLK_CLKDIV5_EADC2DIV_Msk)) | (u32ClkDiv);
            break;

        /* Others */
        default:
        {
            if (MODULE_CLKDIV_Msk(u32ModuleIdx) != MODULE_NoMsk)
            {
                /* Get clock divider control register address */
                u32Div = (uint32_t)&CLK->CLKDIV0 + (au32DivTbl[MODULE_CLKDIV(u32ModuleIdx)]);
                /* Apply new divider */
                M32(u32Div) = (M32(u32Div) & (~(MODULE_CLKDIV_Msk(u32ModuleIdx) << MODULE_CLKDIV_Pos(u32ModuleIdx)))) | u32ClkDiv;
            }
        }
        break;
        }

        /* Configure clock source */
        if (MODULE_CLKSEL_Msk(u32ModuleIdx) != MODULE_NoMsk)
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
  *             - \ref CLK_PWRCTL_HIRC48MEN_Msk
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
  *             - \ref CLK_PWRCTL_HIRC48MEN_Msk
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
  *             - \ref ST_MODULE
  *             - \ref EMAC0_MODULE
  *             - \ref SDH0_MODULE
  *             - \ref SDH1_MODULE
  *             - \ref CRC_MODULE
  *             - \ref CCAP_MODULE
  *             - \ref SEN_MODULE
  *             - \ref HSUSBD_MODULE
  *             - \ref HSOTG_MODULE
  *             - \ref HBI_MODULE
  *             - \ref CRPT_MODULE
  *             - \ref KS_MODULE
  *             - \ref SPIM_MODULE
  *             - \ref FMCIDLE_MODULE
  *             - \ref USBH_MODULE
  *             - \ref OTG_MODULE
  *             - \ref USBD_MODULE
  *             - \ref TRACE_MODULE
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
  *             - \ref CANFD0_MODULE
  *             - \ref CANFD1_MODULE
  *             - \ref CANFD2_MODULE
  *             - \ref CANFD3_MODULE
  *             - \ref WDT_MODULE
  *             - \ref WWDT_MODULE
  *             - \ref RTC_MODULE
  *             - \ref TMR0_MODULE
  *             - \ref TMR1_MODULE
  *             - \ref TMR2_MODULE
  *             - \ref TMR3_MODULE
  *             - \ref CLKO_MODULE
  *             - \ref ACMP01_MODULE
  *             - \ref ACMP23_MODULE
  *             - \ref I2C0_MODULE
  *             - \ref I2C1_MODULE
  *             - \ref I2C2_MODULE
  *             - \ref I2C3_MODULE
  *             - \ref I2C4_MODULE
  *             - \ref QSPI0_MODULE
  *             - \ref QSPI1_MODULE
  *             - \ref SPI0_MODULE
  *             - \ref SPI1_MODULE
  *             - \ref SPI2_MODULE
  *             - \ref SPI3_MODULE
  *             - \ref SPI4_MODULE
  *             - \ref SPI5_MODULE
  *             - \ref SPI6_MODULE
  *             - \ref SPI7_MODULE
  *             - \ref SPI8_MODULE
  *             - \ref SPI9_MODULE
  *             - \ref SPI10_MODULE
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
  *             - \ref EADC0_MODULE
  *             - \ref EADC1_MODULE
  *             - \ref EADC2_MODULE
  *             - \ref I2S0_MODULE
  *             - \ref I2S1_MODULE
  *             - \ref SC0_MODULE
  *             - \ref SC1_MODULE
  *             - \ref SC2_MODULE
  *             - \ref USCI0_MODULE
  *             - \ref PSIO_MODULE
  *             - \ref DAC_MODULE
  *             - \ref EPWM0_MODULE
  *             - \ref EPWM1_MODULE
  *             - \ref BPWM0_MODULE
  *             - \ref BPWM1_MODULE
  *             - \ref EQEI0_MODULE
  *             - \ref EQEI1_MODULE
  *             - \ref EQEI2_MODULE
  *             - \ref EQEI3_MODULE
  *             - \ref TRNG_MODULE
  *             - \ref ECAP0_MODULE
  *             - \ref ECAP1_MODULE
  *             - \ref ECAP2_MODULE
  *             - \ref ECAP3_MODULE
  *             - \ref TRNG_MODULE
  *             - \ref KPI_MODULE
  * @return     None
  * @details    This function is used to enable module clock.
  */
void CLK_EnableModuleClock(uint32_t u32ModuleIdx)
{
    uint32_t u32TmpVal = 0UL, u32TmpAddr = 0UL;

    /* Index, 0x0:AHBCLK0, 0x1:APBCLK0, 0x2:APBCLK1, 0x3:APBCLK2, 0x4:AHBCLK1 */
    uint32_t au32ClkEnTbl[5] = {0x0UL, 0x4UL, 0x8UL, 0x34UL, 0x54UL};

    u32TmpVal = (1UL << MODULE_IP_EN_Pos(u32ModuleIdx));
    u32TmpAddr = (uint32_t)&CLK->AHBCLK0 + au32ClkEnTbl[MODULE_APBCLK(u32ModuleIdx)];

    *(volatile uint32_t *)u32TmpAddr |= u32TmpVal;
}

/**
  * @brief      Disable module clock
  * @param[in]  u32ModuleIdx is module index. Including :
  *             - \ref PDMA0_MODULE
  *             - \ref PDMA1_MODULE
  *             - \ref ISP_MODULE
  *             - \ref EBI_MODULE
  *             - \ref ST_MODULE
  *             - \ref EMAC0_MODULE
  *             - \ref SDH0_MODULE
  *             - \ref SDH1_MODULE
  *             - \ref CRC_MODULE
  *             - \ref CCAP_MODULE
  *             - \ref SEN_MODULE
  *             - \ref HSUSBD_MODULE
  *             - \ref HSOTG_MODULE
  *             - \ref HBI_MODULE
  *             - \ref CRPT_MODULE
  *             - \ref KS_MODULE
  *             - \ref SPIM_MODULE
  *             - \ref FMCIDLE_MODULE
  *             - \ref USBH_MODULE
  *             - \ref OTG_MODULE
  *             - \ref USBD_MODULE
  *             - \ref TRACE_MODULE
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
  *             - \ref CANFD0_MODULE
  *             - \ref CANFD1_MODULE
  *             - \ref CANFD2_MODULE
  *             - \ref CANFD3_MODULE
  *             - \ref WDT_MODULE
  *             - \ref WWDT_MODULE
  *             - \ref RTC_MODULE
  *             - \ref TMR0_MODULE
  *             - \ref TMR1_MODULE
  *             - \ref TMR2_MODULE
  *             - \ref TMR3_MODULE
  *             - \ref CLKO_MODULE
  *             - \ref ACMP01_MODULE
  *             - \ref ACMP23_MODULE
  *             - \ref I2C0_MODULE
  *             - \ref I2C1_MODULE
  *             - \ref I2C2_MODULE
  *             - \ref I2C3_MODULE
  *             - \ref I2C4_MODULE
  *             - \ref QSPI0_MODULE
  *             - \ref QSPI1_MODULE
  *             - \ref SPI0_MODULE
  *             - \ref SPI1_MODULE
  *             - \ref SPI2_MODULE
  *             - \ref SPI3_MODULE
  *             - \ref SPI4_MODULE
  *             - \ref SPI5_MODULE
  *             - \ref SPI6_MODULE
  *             - \ref SPI7_MODULE
  *             - \ref SPI8_MODULE
  *             - \ref SPI9_MODULE
  *             - \ref SPI10_MODULE
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
  *             - \ref EADC0_MODULE
  *             - \ref EADC1_MODULE
  *             - \ref EADC2_MODULE
  *             - \ref I2S0_MODULE
  *             - \ref I2S1_MODULE
  *             - \ref SC0_MODULE
  *             - \ref SC1_MODULE
  *             - \ref SC2_MODULE
  *             - \ref USCI0_MODULE
  *             - \ref PSIO_MODULE
  *             - \ref DAC_MODULE
  *             - \ref EPWM0_MODULE
  *             - \ref EPWM1_MODULE
  *             - \ref BPWM0_MODULE
  *             - \ref BPWM1_MODULE
  *             - \ref EQEI0_MODULE
  *             - \ref EQEI1_MODULE
  *             - \ref EQEI2_MODULE
  *             - \ref EQEI3_MODULE
  *             - \ref TRNG_MODULE
  *             - \ref ECAP0_MODULE
  *             - \ref ECAP1_MODULE
  *             - \ref ECAP2_MODULE
  *             - \ref ECAP3_MODULE
  *             - \ref TRNG_MODULE
  *             - \ref KPI_MODULE
  * @return     None
  * @details    This function is used to disable module clock.
  */
void CLK_DisableModuleClock(uint32_t u32ModuleIdx)
{
    uint32_t u32TmpVal = 0UL, u32TmpAddr = 0UL;

    /* Index, 0x0:AHBCLK0, 0x1:APBCLK0, 0x2:APBCLK1, 0x3:APBCLK2, 0x4:AHBCLK1 */
    uint32_t au32ClkEnTbl[5] = {0x0UL, 0x4UL, 0x8UL, 0x34UL, 0x54UL};

    u32TmpVal = ~(1UL << MODULE_IP_EN_Pos(u32ModuleIdx));
    u32TmpAddr = (uint32_t)&CLK->AHBCLK0 + au32ClkEnTbl[MODULE_APBCLK(u32ModuleIdx)];

    *(uint32_t *)u32TmpAddr &= u32TmpVal;
}


/**
  * @brief      Set PLL frequency
  * @param[in]  u32PllClkSrc is PLL clock source. Including :
  *             - \ref CLK_PLLCTL_PLLSRC_HXT
  *             - \ref CLK_PLLCTL_PLLSRC_HIRC
  * @param[in]  u32PllFreq is PLL frequency. The range of u32PllFreq is 50 MHz ~ 500 MHz.
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
    if (u32PllClkSrc == CLK_PLLCTL_PLLSRC_HXT)
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
    /* Constraint 1: 50MHz < FOUT < 500MHz */
    if ((u32PllFreq <= FREQ_500MHZ) && (u32PllFreq >= FREQ_50MHZ))
    {
        /* Select "NO" according to request frequency */
        if ((u32PllFreq < FREQ_100MHZ) && (u32PllFreq >= FREQ_50MHZ))
        {
            u32NO = 3UL;
            u32PllFreq = u32PllFreq << 2;
        }
        else if ((u32PllFreq < FREQ_200MHZ) && (u32PllFreq >= FREQ_100MHZ))
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

        for (; u32NR <= 32UL; u32NR++)  /* max NR = 32 since NR = INDIV+1 and INDIV = 0~31 */
        {
            u32Tmp = u32PllSrcClk / u32NR;                      /* FREF = FIN/NR */
            if ((u32Tmp >= FREQ_4MHZ) && (u32Tmp <= FREQ_8MHZ)) /* Constraint 2: 4MHz < FREF < 8MHz. */
            {
                for (u32NF = 2UL; u32NF <= 513UL; u32NF++)      /* NF = 2~513 since NF = FBDIV+2 and FBDIV = 0~511 */
                {
                    u32Tmp2 = (u32Tmp * u32NF) << 1;                            /* FVCO = FREF*2*NF */
                    if ((u32Tmp2 >= FREQ_200MHZ) && (u32Tmp2 <= FREQ_500MHZ))   /* Constraint 3: 200MHz < FVCO < 500MHz */
                    {
                        u32Tmp3 = (u32Tmp2 > u32PllFreq) ? u32Tmp2 - u32PllFreq : u32PllFreq - u32Tmp2;
                        if (u32Tmp3 < u32Min)
                        {
                            u32Min = u32Tmp3;
                            u32MinNR = u32NR;
                            u32MinNF = u32NF;

                            /* Break when get good results */
                            if (u32Min == 0UL)
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
        CLK->PLLCTL = u32PllClkSrc | CLK_PLLCTL_192MHz_HXT;

        /* Actual PLL output clock frequency */
        u32PllClk = FREQ_192MHZ;
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
  *             - \ref CLK_STATUS_PLLFNSTB_Msk
  *             - \ref CLK_STATUS_HIRC48MSTB_Msk
  * @retval     0  clock is not stable
  * @retval     1  clock is stable
  * @details    To wait for clock ready by specified clock source stable flag or timeout (>500ms)
  * @note       This function sets g_CLK_i32ErrCode to CLK_TIMEOUT_ERR if clock source status is not stable.
  */
uint32_t CLK_WaitClockReady(uint32_t u32ClkMask)
{
    uint32_t u32TimeOutCnt = SystemCoreClock >> 1; /* 500ms time-out */
    uint32_t u32Ret = 1U;

    g_CLK_i32ErrCode = 0;
    while ((CLK->STATUS & u32ClkMask) != u32ClkMask)
    {
        if (--u32TimeOutCnt == 0)
        {
            g_CLK_i32ErrCode = CLK_TIMEOUT_ERR;
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
    if (u32ClkSrc == CLK_CLKSEL0_STCLKSEL_HCLK)
    {
        /* Disable System Tick clock source from external reference clock */
        CLK->AHBCLK0 &= ~CLK_AHBCLK0_STCKEN_Msk;

        /* Select System Tick clock source from core clock */
        SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
    }
    else
    {
        /* Enable System Tick clock source from external reference clock */
        CLK->AHBCLK0 |= CLK_AHBCLK0_STCKEN_Msk;

        /* Select System Tick external reference clock source */
        CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_STCLKSEL_Msk) | u32ClkSrc;

        /* Select System Tick clock source from external reference clock */
        SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;
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
  *             - \ref CLK_PMUCTL_PDMSEL_SPD
  *             - \ref CLK_PMUCTL_PDMSEL_DPD
  * @return     None
  * @details    This function is used to set power-down mode.
  *             The register write-protection function should be disabled before using this function.
  */

void CLK_SetPowerDownMode(uint32_t u32PDMode)
{
    CLK->PMUCTL = (CLK->PMUCTL & ~(CLK_PMUCTL_PDMSEL_Msk)) | u32PDMode;
}


/**
 * @brief       Set Wake-up pin trigger type at Deep Power down mode
 *
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
 *
 * @details     This function is used to enable Wake-up pin trigger type.
 *              The register write-protection function should be disabled before using this function.
 */

void CLK_EnableDPDWKPin(uint32_t u32TriggerType)
{
    uint32_t u32Pin1, u32Pin2, u32Pin3, u32Pin4;

    /* Get DPD wake-up pin configuration */
    u32Pin1 = ((u32TriggerType) & CLK_PMUCTL_WKPINEN1_Msk);
    u32Pin2 = ((u32TriggerType) & CLK_PMUCTL_WKPINEN2_Msk);
    u32Pin3 = ((u32TriggerType) & CLK_PMUCTL_WKPINEN3_Msk);
    u32Pin4 = ((u32TriggerType) & CLK_PMUCTL_WKPINEN4_Msk);

    /* Set DPD wake-up pin configuration */
    if (u32Pin1)
    {
        CLK->PMUCTL = (CLK->PMUCTL & ~(CLK_PMUCTL_WKPINEN1_Msk)) | u32TriggerType;
    }
    else if (u32Pin2)
    {
        CLK->PMUCTL = (CLK->PMUCTL & ~(CLK_PMUCTL_WKPINEN2_Msk)) | u32TriggerType;
    }
    else if (u32Pin3)
    {
        CLK->PMUCTL = (CLK->PMUCTL & ~(CLK_PMUCTL_WKPINEN3_Msk)) | u32TriggerType;
    }
    else if (u32Pin4)
    {
        CLK->PMUCTL = (CLK->PMUCTL & ~(CLK_PMUCTL_WKPINEN4_Msk)) | u32TriggerType;
    }
    else
    {
        CLK->PMUCTL = (CLK->PMUCTL & ~(CLK_PMUCTL_WKPINEN0_Msk)) | u32TriggerType;
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
 * @param[in]   u32TriggerType Wake-up pin trigger type
 *              - \ref CLK_SPDWKPIN_RISING
 *              - \ref CLK_SPDWKPIN_FALLING
 * @param[in]   u32DebounceEn Standby Power-down mode wake-up pin de-bounce function
 *              - \ref CLK_SPDWKPIN_DEBOUNCEEN
 *              - \ref CLK_SPDWKPIN_DEBOUNCEDIS
 * @return      None
 *
 * @details     This function is used to set specified GPIO as wake up source at Stand-by Power down mode.
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

    if (u32PllReg & (CLK_PLLCTL_PD_Msk | CLK_PLLCTL_OE_Msk))
    {
        u32PllFreq = 0UL;       /* PLL is in power down mode or fix low */
    }
    else                        /* PLL is in normal mode */
    {
        /* PLL source clock */
        if (u32PllReg & CLK_PLLCTL_PLLSRC_Msk)
        {
            u32FIN = __HIRC;    /* PLL source clock from HIRC */
        }
        else
        {
            u32FIN = __HXT;     /* PLL source clock from HXT */
        }

        /* Calculate PLL frequency */
        if (u32PllReg & CLK_PLLCTL_BP_Msk)
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
  *             - \ref SDH1_MODULE
  *             - \ref SEN_MODULE
  *             - \ref USBH_MODULE
  *             - \ref OTG_MODULE
  *             - \ref USBD_MODULE
  *             - \ref CANFD0_MODULE
  *             - \ref CANFD1_MODULE
  *             - \ref CANFD2_MODULE
  *             - \ref CANFD3_MODULE
  *             - \ref WDT_MODULE
  *             - \ref WWDT_MODULE
  *             - \ref RTC_MODULE
  *             - \ref TMR0_MODULE
  *             - \ref TMR1_MODULE
  *             - \ref TMR2_MODULE
  *             - \ref TMR3_MODULE
  *             - \ref CLKO_MODULE
  *             - \ref QSPI0_MODULE
  *             - \ref QSPI1_MODULE
  *             - \ref SPI0_MODULE
  *             - \ref SPI1_MODULE
  *             - \ref SPI2_MODULE
  *             - \ref SPI3_MODULE
  *             - \ref SPI4_MODULE
  *             - \ref SPI5_MODULE
  *             - \ref SPI6_MODULE
  *             - \ref SPI7_MODULE
  *             - \ref SPI8_MODULE
  *             - \ref SPI9_MODULE
  *             - \ref SPI10_MODULE
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
  *             - \ref EPWM0_MODULE
  *             - \ref EPWM1_MODULE
  *             - \ref BPWM0_MODULE
  *             - \ref BPWM1_MODULE
  *             - \ref EADC0_MODULE
  *             - \ref EADC1_MODULE
  *             - \ref EADC2_MODULE
  *             - \ref I2S0_MODULE
  *             - \ref I2S1_MODULE
  *             - \ref SC0_MODULE
  *             - \ref SC1_MODULE
  *             - \ref SC2_MODULE
  *             - \ref PSIO_MODULE
  *             - \ref TRNG_MODULE
  *             - \ref KPI_MODULE
  * @return     Selected module clock source setting
  * @details    This function get selected module clock source.
  */
uint32_t CLK_GetModuleClockSource(uint32_t u32ModuleIdx)
{
    uint32_t u32TmpVal = 0UL, u32TmpAddr = 0UL;
    uint32_t au32SelTbl[5] = {0x0UL, 0x4UL, 0x8UL, 0xCUL, 0x4CUL}; /* CLK_CLKSEL0~4 */
    uint32_t u32RTCCKEN = CLK->APBCLK0 & CLK_APBCLK0_RTCCKEN_Msk;

    /* Get clock source selection setting */
    if (u32ModuleIdx == RTC_MODULE)
    {
        if (u32RTCCKEN == 0UL)
        {
            /* Enable RTC clock to get LXT clock source */
            CLK->APBCLK0 |= CLK_APBCLK0_RTCCKEN_Msk;
        }

        u32TmpVal = ((RTC->LXTCTL & RTC_LXTCTL_RTCCKSEL_Msk) >> RTC_LXTCTL_RTCCKSEL_Pos);

        if (u32RTCCKEN == 0UL)
        {
            /* Disable RTC clock if it is disabled before */
            CLK->APBCLK0 &= (~CLK_APBCLK0_RTCCKEN_Msk);
        }

    }
    else if (MODULE_CLKSEL_Msk(u32ModuleIdx) != MODULE_NoMsk)
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
  *             - \ref SDH1_MODULE
  *             - \ref SEN_MODULE
  *             - \ref USBH_MODULE
  *             - \ref OTG_MODULE
  *             - \ref USBD_MODULE
  *             - \ref CANFD0_MODULE
  *             - \ref CANFD1_MODULE
  *             - \ref CANFD2_MODULE
  *             - \ref CANFD3_MODULE
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
  *             - \ref EADC0_MODULE
  *             - \ref EADC1_MODULE
  *             - \ref EADC2_MODULE
  *             - \ref I2S0_MODULE
  *             - \ref I2S1_MODULE
  *             - \ref SC0_MODULE
  *             - \ref SC1_MODULE
  *             - \ref SC2_MODULE
  *             - \ref PSIO_MODULE
  *             - \ref KPI_MODULE
  *             - \ref EMAC0_MODULE
  * @return     Selected module clock divider number setting
  * @details    This function get selected module clock divider number.
  */
uint32_t CLK_GetModuleClockDivider(uint32_t u32ModuleIdx)
{
    uint32_t u32DivVal = 0UL, u32DivAddr = 0UL;
    uint32_t au32DivTbl[6] = {0x0UL, 0x4UL, 0x8UL, 0xCUL, 0x10UL, 0x1C}; /* CLK_CLKDIV0~5 */

    switch (u32ModuleIdx)
    {
    /* For 8 bits divider */
    case EADC0_MODULE:
        u32DivVal = (CLK->CLKDIV0 & CLK_CLKDIV0_EADC0DIV_Msk) >> CLK_CLKDIV0_EADC0DIV_Pos;
        break;
    case SDH0_MODULE:
        u32DivVal = (CLK->CLKDIV0 & CLK_CLKDIV0_SDH0DIV_Msk) >> CLK_CLKDIV0_SDH0DIV_Pos;
        break;
    case SC0_MODULE:
        u32DivVal = (CLK->CLKDIV1 & CLK_CLKDIV1_SC0DIV_Msk) >> CLK_CLKDIV1_SC0DIV_Pos;
        break;
    case SC1_MODULE:
        u32DivVal = (CLK->CLKDIV1 & CLK_CLKDIV1_SC1DIV_Msk) >> CLK_CLKDIV1_SC1DIV_Pos;
        break;
    case SC2_MODULE:
        u32DivVal = (CLK->CLKDIV1 & CLK_CLKDIV1_SC2DIV_Msk) >> CLK_CLKDIV1_SC2DIV_Pos;
        break;
    case PSIO_MODULE:
        u32DivVal = (CLK->CLKDIV1 & CLK_CLKDIV1_PSIODIV_Msk) >> CLK_CLKDIV1_PSIODIV_Pos;
        break;
    case KPI_MODULE:
        u32DivVal = (CLK->CLKDIV2 & CLK_CLKDIV2_KPIDIV_Msk) >> CLK_CLKDIV2_KPIDIV_Pos;
        break;
    case EADC1_MODULE:
        u32DivVal = (CLK->CLKDIV2 & CLK_CLKDIV2_EADC1DIV_Msk) >> CLK_CLKDIV2_EADC1DIV_Pos;
        break;
    case SEN_MODULE:
        u32DivVal = (CLK->CLKDIV3 & CLK_CLKDIV3_VSENSEDIV_Msk) >> CLK_CLKDIV3_VSENSEDIV_Pos;
        break;
    case EMAC0_MODULE:
        u32DivVal = (CLK->CLKDIV3 & CLK_CLKDIV3_EMAC0DIV_Msk) >> CLK_CLKDIV3_EMAC0DIV_Pos;
        break;
    case SDH1_MODULE:
        u32DivVal = (CLK->CLKDIV3 & CLK_CLKDIV3_SDH1DIV_Msk) >> CLK_CLKDIV3_SDH1DIV_Pos;
        break;
    case EADC2_MODULE:
        u32DivVal = (CLK->CLKDIV5 & CLK_CLKDIV5_EADC2DIV_Msk) >> CLK_CLKDIV5_EADC2DIV_Pos;
        break;

    /* Others */
    default:
    {
        /* Get clock divider control register address */
        u32DivAddr = (uint32_t)&CLK->CLKDIV0 + (au32DivTbl[MODULE_CLKDIV(u32ModuleIdx)]);
        /* Get clock divider number setting */
        u32DivVal = ((inpw((uint32_t *)u32DivAddr) & (MODULE_CLKDIV_Msk(u32ModuleIdx) << MODULE_CLKDIV_Pos(u32ModuleIdx))) >> MODULE_CLKDIV_Pos(u32ModuleIdx));
    }
    break;
    }

    return u32DivVal;
}

/**
  * @brief      Disable PLLFN
  * @param      None
  * @return     None
  * @details    This function set PLLFN in Power-down mode. \n
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_DisablePLLFN(void)
{
    CLK->PLLFNCTL1 |= CLK_PLLFNCTL1_PD_Msk;
}

/**
  * @brief      Set PLLFN frequency
  * @param[in]  u32PllClkSrc is PLLFN clock source. Including :
  *             - \ref CLK_PLLFNCTL1_PLLSRC_HXT
  *             - \ref CLK_PLLFNCTL1_PLLSRC_HIRC
  * @param[in]  u32PllFreq is PLLFN frequency. The range of u32PllFreq is 50 MHz ~ 500 MHz.
  * @return     PLL frequency
  * @details    This function is used to configure PLLFNCTL0 and PLLFNCTL1 register to set specified PLLFN frequency. \n
  *             The register write-protection function should be disabled before using this function.
  */
uint32_t CLK_EnablePLLFN(uint32_t u32PllClkSrc, uint32_t u32PllFreq)
{
    uint32_t u32FIN, u32FVCO, u32FREF, u32PllClk;
    uint32_t u32NR = 0UL, u32NF, u32NO, u32X = 0UL;
    float fNX_X = 0.0, fX = 0.0;

    /* Disable PLLFN first to avoid unstable when setting PLLFN */
    CLK->PLLFNCTL1 |= CLK_PLLFNCTL1_PD_Msk;

    /* PLLFN source clock is from HXT */
    if (u32PllClkSrc == CLK_PLLFNCTL1_PLLSRC_HXT)
    {
        /* Enable HXT clock */
        CLK->PWRCTL |= CLK_PWRCTL_HXTEN_Msk;

        /* Wait for HXT clock ready */
        CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

        /* Select PLLFN source clock from HXT */
        u32FIN = __HXT;
    }

    /* PLL source clock is from HIRC */
    else
    {
        /* Enable HIRC clock */
        CLK->PWRCTL |= CLK_PWRCTL_HIRCEN_Msk;

        /* Wait for HIRC clock ready */
        CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

        /* Select PLL source clock from HIRC */
        u32FIN = __HIRC;
    }

    /* Check PLL frequency range */
    /* Constraint 1: 50MHz < FOUT < 500MHz */
    if ((u32PllFreq <= FREQ_500MHZ) && (u32PllFreq >= FREQ_50MHZ))
    {
        /* Select "NO" according to request frequency */
        if ((u32PllFreq < FREQ_100MHZ) && (u32PllFreq >= FREQ_50MHZ))
        {
            u32NO = 3UL;
            u32FVCO = u32PllFreq << 2;
        }
        else if ((u32PllFreq < FREQ_200MHZ) && (u32PllFreq >= FREQ_100MHZ))
        {
            u32NO = 1UL;
            u32FVCO = u32PllFreq << 1;
        }
        else
        {
            u32NO = 0UL;
            u32FVCO = u32PllFreq;
        }

        /* u32NR start from 3 to avoid calculation overflow */
        u32NR = 3UL;

        for (; u32NR <= 32UL; u32NR++)  /* max NR = 32 since NR = INDIV+1 and INDIV = 0~31 */
        {
            u32FREF = u32FIN / u32NR;                               /* FREF = FIN/NR */

            if ((u32FREF >= FREQ_1MHZ) && (u32FREF <= FREQ_8MHZ))   /* Constraint 2: 1MHz <= FREF <= 8MHz. */
            {
                fNX_X = (float)((u32FVCO * u32NR) >> 1) / u32FIN;
                u32NF = (uint32_t)fNX_X;

                if ((u32NF >= 12) && (u32NF <= 255))   /* Constraint 4: 12<= NF <= 255. */
                {
                    fX = fNX_X - u32NF;
                    u32X = (uint32_t)(fX * 4096);
                    break;
                }
            }
        }

        /* Enable and apply new PLL setting. */
        CLK->PLLFNCTL0 = (u32X << CLK_PLLFNCTL0_FRDIV_Pos) |
                         (u32NO << CLK_PLLFNCTL0_OUTDIV_Pos) |
                         ((u32NR - 1UL) << CLK_PLLFNCTL0_INDIV_Pos) |
                         ((u32NF - 2UL) << CLK_PLLFNCTL0_FBDIV_Pos);
        CLK->PLLFNCTL1 = u32PllClkSrc;

        /* Actual PLL output clock frequency. FOUT = (FIN/NR)*2*(NF.X)*(1/NO) */
        u32PllClk = (uint32_t)((float)u32FIN / (((u32NO + 1UL) * u32NR) << 11) * ((u32NF << 12) + u32X));
    }

    if ((u32PllFreq > FREQ_500MHZ) || (u32PllFreq < FREQ_50MHZ) || (u32NR == 33))
    {
        /* Apply default PLL setting and return */
        CLK->PLLCTL = u32PllClkSrc | CLK_PLLCTL_192MHz_HXT;

        /* Actual PLL output clock frequency */
        u32PllClk = FREQ_192MHZ;
    }

    /* Wait for PLL clock stable */
    CLK_WaitClockReady(CLK_STATUS_PLLFNSTB_Msk);

    /* Return actual PLL output clock frequency */
    return u32PllClk;
}


/**
  * @brief      Get PLLFN clock frequency
  * @param      None
  * @return     PLL frequency
  * @details    This function get PLLFN frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetPLLFNClockFreq(void)
{
    uint32_t u32PllFreq = 0UL, u32PllReg0, u32PllReg1;
    uint32_t u32FIN, u32NF, u32NR, u32NO, u32X;
    uint8_t au8NoTbl[4] = {1U, 2U, 2U, 4U};

    /* Get PLLFN configuration */
    u32PllReg0 = CLK->PLLFNCTL0;
    u32PllReg1 = CLK->PLLFNCTL1;

    if (u32PllReg1 & (CLK_PLLFNCTL1_PD_Msk | CLK_PLLFNCTL1_OE_Msk))
    {
        u32PllFreq = 0UL;       /* PLLFN is in power down mode or fix low */
    }
    else                        /* PLLFN is in normal mode */
    {
        /* PLLFN source clock */
        if (u32PllReg1 & CLK_PLLFNCTL1_PLLSRC_Msk)
        {
            u32FIN = __HIRC;    /* PLLFN source clock from HIRC */
        }
        else
        {
            u32FIN = __HXT;     /* PLLFN source clock from HXT */
        }

        /* Calculate PLLFN frequency */
        if (u32PllReg1 & CLK_PLLFNCTL1_BP_Msk)
        {
            u32PllFreq = u32FIN;  /* PLLFN is in bypass mode */
        }
        else
        {
            /* PLLFN is output enabled in normal work mode */
            u32NO = au8NoTbl[((u32PllReg0 & CLK_PLLFNCTL0_OUTDIV_Msk) >> CLK_PLLFNCTL0_OUTDIV_Pos)];
            u32NF = ((u32PllReg0 & CLK_PLLFNCTL0_FBDIV_Msk) >> CLK_PLLFNCTL0_FBDIV_Pos) + 2UL;
            u32NR = ((u32PllReg0 & CLK_PLLFNCTL0_INDIV_Msk) >> CLK_PLLFNCTL0_INDIV_Pos) + 1UL;
            u32X  = ((u32PllReg0 & CLK_PLLFNCTL0_FRDIV_Msk) >> CLK_PLLFNCTL0_FRDIV_Pos);

            u32PllFreq = (uint32_t)((float)u32FIN / ((u32NO * u32NR) << 11) * (((u32NF << 12) + u32X)));
        }
    }

    return u32PllFreq;
}


/*@}*/ /* end of group CLK_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group CLK_Driver */

/*@}*/ /* end of group Standard_Driver */
