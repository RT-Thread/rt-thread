/**************************************************************************//**
 * @file     clk.c
 * @version  V1.00
 * $Revision: 35 $
 * $Date: 16/03/04 3:42p $
 * @brief    NUC472/NUC442 CLK driver source file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include  "NUC472_442.h"
/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_CLK_Driver CLK Driver
  @{
*/


/** @addtogroup NUC472_442_CLK_EXPORTED_FUNCTIONS CLK Exported Functions
  @{
*/


/**
  * @brief      Disable frequency output function
  * @return     None
  * @details    This function disable frequency output function.
  */
void CLK_DisableCKO(void)
{
    /* Disable CKO clock source */
    CLK->APBCLK0 &= (~CLK_APBCLK0_CLKOCKEN_Msk);
}

/**
  * @brief  This function enable frequency divider module clock,
  *         enable frequency divider clock function and configure frequency divider.
  * @param[in]  u32ClkSrc is frequency divider function clock source
  *         - \ref CLK_CLKSEL1_CLKOSEL_HXT
  *         - \ref CLK_CLKSEL1_CLKOSEL_LXT
  *         - \ref CLK_CLKSEL1_CLKOSEL_HCLK
  *         - \ref CLK_CLKSEL1_CLKOSEL_HIRC
  * @param[in]  u32ClkDiv is system reset source
  * @param[in]  u32ClkDivBy1En is frequency divided by one enable.
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
    CLK->CLKOCTL = CLK_CLKOCTL_CLKOEN_Msk | u32ClkDiv | u32ClkDivBy1En<<CLK_CLKOCTL_DIV1EN_Pos;

    /* Enable CKO clock source */
    CLK->APBCLK0 |= CLK_APBCLK0_CLKOCKEN_Msk;

    /* Select CKO clock source */
    CLK->CLKSEL1 = (CLK->CLKSEL1 & (~CLK_CLKSEL1_CLKOSEL_Msk)) | u32ClkSrc;
}

/**
  * @brief      Enter to Power-down mode
  * @return     None
  * @details    This function let system enter to Power-down mode.
  */
void CLK_PowerDown(void)
{
    SCB->SCR = SCB_SCR_SLEEPDEEP_Msk;
    CLK->PWRCTL |= (CLK_PWRCTL_PDEN_Msk | CLK_PWRCTL_PDWKDLY_Msk );
    __WFI();
}

/**
  * @brief      Enter to Idle mode.
  * @return     None
  * @details    This function let system enter to Idle mode.
  */
void CLK_Idle(void)
{
    /* Set the processor uses sleep as its low power mode */
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;

    /* Set chip in idle mode because of WFI command */
    CLK->PWRCTL &= ~(CLK_PWRCTL_PDEN_Msk );

    /* Chip enter idle mode after CPU run WFI instruction */
    __WFI();
}


/**
  * @brief  This function get PCLK frequency. The frequency unit is Hz.
  * @return PCLK frequency
  */
uint32_t CLK_GetPCLKFreq(void)
{
    SystemCoreClockUpdate();
    if(CLK->CLKSEL0 & CLK_CLKSEL0_PCLKSEL_Msk)
        return SystemCoreClock/2;
    else
        return SystemCoreClock;
}

/**
  * @brief      Get external high speed crystal clock frequency
  * @return     External high frequency crystal frequency
  * @details    This function get external high frequency crystal frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetHXTFreq(void)
{
    if(CLK->PWRCTL & CLK_PWRCTL_HXTEN_Msk )
        return __HXT;
    else
        return 0;
}

/**
  * @brief      Get external low speed crystal clock frequency
  * @return     External low speed crystal clock frequency
  * @details    This function get external low frequency crystal frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetLXTFreq(void)
{
    if(CLK->PWRCTL & CLK_PWRCTL_LXTEN_Msk )
        return __LXT;
    else
        return 0;
}


/**
  * @brief      Get HCLK frequency
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
  * @return     CPU frequency
  * @details    This function get CPU frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetCPUFreq(void)
{
    SystemCoreClockUpdate();
    return SystemCoreClock;
}

/**
  * @brief  This function get PLL frequency. The frequency unit is Hz.
  * @return PLL frequency
  */
uint32_t CLK_GetPLLClockFreq(void)
{
    uint32_t u32Freq =0, u32PLLSrc;
    uint32_t u32NO,u32NF,u32NR,u32PllReg;

    u32PllReg = CLK->PLLCTL;

    if(u32PllReg & (CLK_PLLCTL_PD_Msk | CLK_PLLCTL_OE_Msk))
        return 0;           /* PLL is in power down mode or fix low */

    if(u32PllReg & CLK_PLLCTL_PLLSRC_Msk)
        u32PLLSrc = __HIRC;
    else
        u32PLLSrc = __HXT;

    u32NO=(u32PllReg & CLK_PLLCTL_OUTDV_Msk)>>CLK_PLLCTL_OUTDV_Pos;
    switch(u32NO) {
    case 0:
        u32NO=1;
        break;
    case 1:
    case 2:
        u32NO=2;
        break;
    case 3:
        u32NO=4;
        break;
    }

    u32NF = (u32PllReg & CLK_PLLCTL_FBDIV_Msk) + 2;
    u32NR = ( (u32PllReg & CLK_PLLCTL_INDIV_Msk)>>CLK_PLLCTL_INDIV_Pos ) + 2;

    /* u32PLLSrc is shifted 2 bits to avoid overflow */
    u32Freq = (((u32PLLSrc >> 2) * u32NF) / (u32NR * u32NO) << 2);
    return u32Freq;
}

/**
  * @brief      Set HCLK frequency
  * @param[in]  u32Hclk is HCLK frequency
  * @return     HCLK frequency
  * @details    This function set HCLK frequency. The frequency unit is Hz. The range of u32Hclk is 24 MHz ~ 96 MHz.
  */
uint32_t CLK_SetCoreClock(uint32_t u32Hclk)
{
    uint32_t u32ClkSrc,u32NR, u32NF,u32Register;
    u32ClkSrc = CLK->CLKSEL0 & CLK_CLKSEL0_HCLKSEL_Msk;

    if(u32Hclk < FREQ_24MHZ)
        u32Hclk =FREQ_24MHZ;

    if(CLK->PWRCTL & CLK_PWRCTL_HXTEN_Msk) {
        u32Register = 0<<CLK_PLLCTL_PLLSRC_Pos;
        u32ClkSrc = __HXT;
    } else {
        u32Register = 1<<CLK_PLLCTL_PLLSRC_Pos;
        u32ClkSrc = __HIRC;
    }

    if(u32Hclk<FREQ_50MHZ)  {
        u32Hclk <<=2;
        u32Register |= (0x3<<CLK_PLLCTL_OUTDV_Pos);
    } else {
        u32Hclk <<=1;
        u32Register |= (0x1<<CLK_PLLCTL_OUTDV_Pos);
    }
    u32NF = u32Hclk / 1000000;
    u32NR = u32ClkSrc / 1000000;
    while( u32NR>(0xF+2) || u32NF>(0xFF+2) ) {
        u32NR = u32NR>>1;
        u32NF = u32NF>>1;
    }
    CLK->PLLCTL = u32Register | ((u32NR - 2)<<9) | (u32NF - 2) ;
    CLK_WaitClockReady(CLK_STATUS_PLLSTB_Msk);

    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_PLL,CLK_CLKDIV0_HCLK(1));

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    return SystemCoreClock;
}

/**
  * @brief  This function set HCLK clock source and HCLK clock divider
  * @param[in]  u32ClkSrc is HCLK clock source. Including :
  *         - \ref CLK_CLKSEL0_HCLKSEL_HXT
  *         - \ref CLK_CLKSEL0_HCLKSEL_LXT
  *         - \ref CLK_CLKSEL0_HCLKSEL_PLL
  *         - \ref CLK_CLKSEL0_HCLKSEL_LIRC
  *         - \ref CLK_CLKSEL0_HCLKSEL_HIRC
  * @param[in]  u32ClkDiv is HCLK clock divider. Including :
  *         - \ref CLK_CLKDIV0_HCLK(x)
  * @return None
  */
void CLK_SetHCLK(uint32_t u32ClkSrc, uint32_t u32ClkDiv)
{
    CLK->CLKDIV0 = (CLK->CLKDIV0 & ~CLK_CLKDIV0_HCLKDIV_Msk) | u32ClkDiv;
    CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_HCLKSEL_Msk) | u32ClkSrc;
    SystemCoreClockUpdate();
}

/**
  * @brief  This function set selected module clock source and module clock divider
  * @param[in]  u32ModuleIdx is module index.
  * @param[in]  u32ClkSrc is module clock source.
  * @param[in]  u32ClkDiv is module clock divider.
  * @return None
  * @details Valid parameter combinations listed in following table:
  *
  * |Module index          |Clock source                          |Divider                       |
  * | :------------------- | :-------------------------------     | :-------------------------   |
  * |\ref PDMA_MODULE      | x                                    | x                            |
  * |\ref ISP_MODULE       | x                                    | x                            |
  * |\ref EBI_MODULE       | x                                    | x                            |
  * |\ref USBH_MODULE      |\ref CLK_CLKSEL0_USBHSEL_PLL          |\ref CLK_CLKDIV0_USB(x)       |
  * |\ref USBH_MODULE      |\ref CLK_CLKSEL0_USBHSEL_PLL2         |\ref CLK_CLKDIV0_USB(x)       |
  * |\ref EMAC_MODULE      | x                                    |\ref CLK_CLKDIV3_EMAC(x)      |
  * |\ref SDH_MODULE       |\ref CLK_CLKSEL0_SDHSEL_HXT           |\ref CLK_CLKDIV0_SDH(x)       |
  * |\ref SDH_MODULE       |\ref CLK_CLKSEL0_SDHSEL_PLL           |\ref CLK_CLKDIV0_SDH(x)       |
  * |\ref SDH_MODULE       |\ref CLK_CLKSEL0_SDHSEL_HCLK          |\ref CLK_CLKDIV0_SDH(x)       |
  * |\ref SDH_MODULE       |\ref CLK_CLKSEL0_SDHSEL_HIRC          |\ref CLK_CLKDIV0_SDH(x)       |
  * |\ref CRC_MODULE       | x                                    | x                            |
  * |\ref CAP_MODULE       |\ref CLK_CLKSEL0_CAPSEL_HXT           |\ref CLK_CLKDIV3_CAP(x)       |
  * |\ref CAP_MODULE       |\ref CLK_CLKSEL0_CAPSEL_PLL2          |\ref CLK_CLKDIV3_CAP(x)       |
  * |\ref CAP_MODULE       |\ref CLK_CLKSEL0_CAPSEL_HCLK          |\ref CLK_CLKDIV3_CAP(x)       |
  * |\ref CAP_MODULE       |\ref CLK_CLKSEL0_CAPSEL_HIRC          |\ref CLK_CLKDIV3_CAP(x)       |
  * |\ref SEN_MODULE       | x                                    | x                            |
  * |\ref USBD_MODULE      | x                                    | x                            |
  * |\ref CRPT_MODULE      | x                                    | x                            |
  * |\ref ECAP1_MODULE     | x                                    | x                            |
  * |\ref ECAP0_MODULE     | x                                    | x                            |
  * |\ref EADC_MODULE      |\ref CLK_CLKSEL1_ADCSEL_HXT           |\ref CLK_CLKDIV0_ADC(x)       |
  * |\ref EADC_MODULE      |\ref CLK_CLKSEL1_ADCSEL_PLL           |\ref CLK_CLKDIV0_ADC(x)       |
  * |\ref EADC_MODULE      |\ref CLK_CLKSEL1_ADCSEL_PCLK          |\ref CLK_CLKDIV0_ADC(x)       |
  * |\ref EADC_MODULE      |\ref CLK_CLKSEL1_ADCSEL_HIRC          |\ref CLK_CLKDIV0_ADC(x)       |
  * |\ref OPA_MODULE       | x                                    | x                            |
  * |\ref QEI1_MODULE      | x                                    | x                            |
  * |\ref QEI0_MODULE      | x                                    | x                            |
  * |\ref PWM1CH45_MODULE  |\ref CLK_CLKSEL2_PWM1CH45SEL_HXT      | x                            |
  * |\ref PWM1CH45_MODULE  |\ref CLK_CLKSEL2_PWM1CH45SEL_LXT      | x                            |
  * |\ref PWM1CH45_MODULE  |\ref CLK_CLKSEL2_PWM1CH45SEL_PCLK     | x                            |
  * |\ref PWM1CH45_MODULE  |\ref CLK_CLKSEL2_PWM1CH45SEL_LIRC     | x                            |
  * |\ref PWM1CH45_MODULE  |\ref CLK_CLKSEL2_PWM1CH45SEL_HIRC     | x                            |
  * |\ref PWM1CH23_MODULE  |\ref CLK_CLKSEL2_PWM1CH23SEL_HXT      | x                            |
  * |\ref PWM1CH23_MODULE  |\ref CLK_CLKSEL2_PWM1CH23SEL_LXT      | x                            |
  * |\ref PWM1CH23_MODULE  |\ref CLK_CLKSEL2_PWM1CH23SEL_PCLK     | x                            |
  * |\ref PWM1CH23_MODULE  |\ref CLK_CLKSEL2_PWM1CH23SEL_LIRC     | x                            |
  * |\ref PWM1CH23_MODULE  |\ref CLK_CLKSEL2_PWM1CH23SEL_HIRC     | x                            |
  * |\ref PWM1CH01_MODULE  |\ref CLK_CLKSEL2_PWM1CH01SEL_HXT      | x                            |
  * |\ref PWM1CH01_MODULE  |\ref CLK_CLKSEL2_PWM1CH01SEL_LXT      | x                            |
  * |\ref PWM1CH01_MODULE  |\ref CLK_CLKSEL2_PWM1CH01SEL_PCLK     | x                            |
  * |\ref PWM1CH01_MODULE  |\ref CLK_CLKSEL2_PWM1CH01SEL_LIRC     | x                            |
  * |\ref PWM1CH01_MODULE  |\ref CLK_CLKSEL2_PWM1CH01SEL_HIRC     | x                            |
  * |\ref PWM0CH45_MODULE  |\ref CLK_CLKSEL2_PWM0CH45SEL_HXT      | x                            |
  * |\ref PWM0CH45_MODULE  |\ref CLK_CLKSEL2_PWM0CH45SEL_LXT      | x                            |
  * |\ref PWM0CH45_MODULE  |\ref CLK_CLKSEL2_PWM0CH45SEL_PCLK     | x                            |
  * |\ref PWM0CH45_MODULE  |\ref CLK_CLKSEL2_PWM0CH45SEL_LIRC     | x                            |
  * |\ref PWM0CH45_MODULE  |\ref CLK_CLKSEL2_PWM0CH45SEL_HIRC     | x                            |
  * |\ref PWM0CH23_MODULE  |\ref CLK_CLKSEL2_PWM0CH23SEL_HXT      | x                            |
  * |\ref PWM0CH23_MODULE  |\ref CLK_CLKSEL2_PWM0CH23SEL_LXT      | x                            |
  * |\ref PWM0CH23_MODULE  |\ref CLK_CLKSEL2_PWM0CH23SEL_PCLK     | x                            |
  * |\ref PWM0CH23_MODULE  |\ref CLK_CLKSEL2_PWM0CH23SEL_LIRC     | x                            |
  * |\ref PWM0CH23_MODULE  |\ref CLK_CLKSEL2_PWM0CH23SEL_HIRC     | x                            |
  * |\ref PWM0CH01_MODULE  |\ref CLK_CLKSEL2_PWM0CH01SEL_HXT      | x                            |
  * |\ref PWM0CH01_MODULE  |\ref CLK_CLKSEL2_PWM0CH01SEL_LXT      | x                            |
  * |\ref PWM0CH01_MODULE  |\ref CLK_CLKSEL2_PWM0CH01SEL_PCLK     | x                            |
  * |\ref PWM0CH01_MODULE  |\ref CLK_CLKSEL2_PWM0CH01SEL_LIRC     | x                            |
  * |\ref PWM0CH01_MODULE  |\ref CLK_CLKSEL2_PWM0CH01SEL_HIRC     | x                            |
  * |\ref I2C4_MODULE      | x                                    | x                            |
  * |\ref SC5_MODULE       | x                                    | x                            |
  * |\ref SC4_MODULE       | x                                    | x                            |
  * |\ref SC3_MODULE       | x                                    | x                            |
  * |\ref SC2_MODULE       | x                                    | x                            |
  * |\ref SC5_MODULE       |\ref CLK_CLKSEL3_SC5SEL_HXT           |\ref CLK_CLKDIV2_SC5(x)       |
  * |\ref SC5_MODULE       |\ref CLK_CLKSEL3_SC5SEL_PLL           |\ref CLK_CLKDIV2_SC5(x)       |
  * |\ref SC5_MODULE       |\ref CLK_CLKSEL3_SC5SEL_PCLK          |\ref CLK_CLKDIV2_SC5(x)       |
  * |\ref SC5_MODULE       |\ref CLK_CLKSEL3_SC5SEL_HIRC          |\ref CLK_CLKDIV2_SC5(x)       |
  * |\ref SC4_MODULE       |\ref CLK_CLKSEL3_SC4SEL_HXT           |\ref CLK_CLKDIV2_SC4(x)       |
  * |\ref SC4_MODULE       |\ref CLK_CLKSEL3_SC4SEL_PLL           |\ref CLK_CLKDIV2_SC4(x)       |
  * |\ref SC4_MODULE       |\ref CLK_CLKSEL3_SC4SEL_PCLK          |\ref CLK_CLKDIV2_SC4(x)       |
  * |\ref SC4_MODULE       |\ref CLK_CLKSEL3_SC4SEL_HIRC          |\ref CLK_CLKDIV2_SC4(x)       |
  * |\ref SC3_MODULE       |\ref CLK_CLKSEL3_SC3SEL_HXT           |\ref CLK_CLKDIV1_SC3(x)       |
  * |\ref SC3_MODULE       |\ref CLK_CLKSEL3_SC3SEL_PLL           |\ref CLK_CLKDIV1_SC3(x)       |
  * |\ref SC3_MODULE       |\ref CLK_CLKSEL3_SC3SEL_PCLK          |\ref CLK_CLKDIV1_SC3(x)       |
  * |\ref SC3_MODULE       |\ref CLK_CLKSEL3_SC3SEL_HIRC          |\ref CLK_CLKDIV1_SC3(x)       |
  * |\ref SC2_MODULE       |\ref CLK_CLKSEL3_SC2SEL_HXT           |\ref CLK_CLKDIV1_SC2(x)       |
  * |\ref SC2_MODULE       |\ref CLK_CLKSEL3_SC2SEL_PLL           |\ref CLK_CLKDIV1_SC2(x)       |
  * |\ref SC2_MODULE       |\ref CLK_CLKSEL3_SC2SEL_PCLK          |\ref CLK_CLKDIV1_SC2(x)       |
  * |\ref SC2_MODULE       |\ref CLK_CLKSEL3_SC2SEL_HIRC          |\ref CLK_CLKDIV1_SC2(x)       |
  * |\ref SC1_MODULE       |\ref CLK_CLKSEL3_SC1SEL_HXT           |\ref CLK_CLKDIV1_SC1(x)       |
  * |\ref SC1_MODULE       |\ref CLK_CLKSEL3_SC1SEL_PLL           |\ref CLK_CLKDIV1_SC1(x)       |
  * |\ref SC1_MODULE       |\ref CLK_CLKSEL3_SC1SEL_PCLK          |\ref CLK_CLKDIV1_SC1(x)       |
  * |\ref SC1_MODULE       |\ref CLK_CLKSEL3_SC1SEL_HIRC          |\ref CLK_CLKDIV1_SC1(x)       |
  * |\ref SC0_MODULE       |\ref CLK_CLKSEL3_SC0SEL_HXT           |\ref CLK_CLKDIV1_SC0(x)       |
  * |\ref SC0_MODULE       |\ref CLK_CLKSEL3_SC0SEL_PLL           |\ref CLK_CLKDIV1_SC0(x)       |
  * |\ref SC0_MODULE       |\ref CLK_CLKSEL3_SC0SEL_PCLK          |\ref CLK_CLKDIV1_SC0(x)       |
  * |\ref SC0_MODULE       |\ref CLK_CLKSEL3_SC0SEL_HIRC          |\ref CLK_CLKDIV1_SC0(x)       |
  * |\ref PS2_MODULE       |\ref CLK_CLKSEL3_I2S1SEL_HXT          | x                            |
  * |\ref I2S1_MODULE      |\ref CLK_CLKSEL3_I2S1SEL_HXT          | x                            |
  * |\ref I2S1_MODULE      |\ref CLK_CLKSEL3_I2S1SEL_PLL          | x                            |
  * |\ref I2S1_MODULE      |\ref CLK_CLKSEL3_I2S1SEL_PCLK         | x                            |
  * |\ref I2S1_MODULE      |\ref CLK_CLKSEL3_I2S1SEL_HIRC         | x                            |
  * |\ref I2S0_MODULE      |\ref CLK_CLKSEL3_I2S0SEL_HXT          | x                            |
  * |\ref I2S0_MODULE      |\ref CLK_CLKSEL3_I2S0SEL_PLL          | x                            |
  * |\ref I2S0_MODULE      |\ref CLK_CLKSEL3_I2S0SEL_PCLK         | x                            |
  * |\ref I2S0_MODULE      |\ref CLK_CLKSEL3_I2S0SEL_HIRC         | x                            |
  * |\ref ADC_MODULE       |\ref CLK_CLKSEL1_ADCSEL_HXT           |\ref CLK_CLKDIV0_ADC(x)       |
  * |\ref ADC_MODULE       |\ref CLK_CLKSEL1_ADCSEL_PLL           |\ref CLK_CLKDIV0_ADC(x)       |
  * |\ref ADC_MODULE       |\ref CLK_CLKSEL1_ADCSEL_PCLK          |\ref CLK_CLKDIV0_ADC(x)       |
  * |\ref ADC_MODULE       |\ref CLK_CLKSEL1_ADCSEL_HIRC          |\ref CLK_CLKDIV0_ADC(x)       |
  * |\ref OTG_MODULE       | x                                    | x                            |
  * |\ref CAN1_MODULE      | x                                    | x                            |
  * |\ref CAN0_MODULE      | x                                    | x                            |
  * |\ref UART5_MODULE     |\ref CLK_CLKSEL1_UARTSEL_HXT          |\ref CLK_CLKDIV0_UART(x)      |
  * |\ref UART5_MODULE     |\ref CLK_CLKSEL1_UARTSEL_PLL          |\ref CLK_CLKDIV0_UART(x)      |
  * |\ref UART5_MODULE     |\ref CLK_CLKSEL1_UARTSEL_HIRC         |\ref CLK_CLKDIV0_UART(x)      |
  * |\ref UART4_MODULE     |\ref CLK_CLKSEL1_UARTSEL_HXT          |\ref CLK_CLKDIV0_UART(x)      |
  * |\ref UART4_MODULE     |\ref CLK_CLKSEL1_UARTSEL_PLL          |\ref CLK_CLKDIV0_UART(x)      |
  * |\ref UART4_MODULE     |\ref CLK_CLKSEL1_UARTSEL_HIRC         |\ref CLK_CLKDIV0_UART(x)      |
  * |\ref UART3_MODULE     |\ref CLK_CLKSEL1_UARTSEL_HXT          |\ref CLK_CLKDIV0_UART(x)      |
  * |\ref UART3_MODULE     |\ref CLK_CLKSEL1_UARTSEL_PLL          |\ref CLK_CLKDIV0_UART(x)      |
  * |\ref UART3_MODULE     |\ref CLK_CLKSEL1_UARTSEL_HIRC         |\ref CLK_CLKDIV0_UART(x)      |
  * |\ref UART2_MODULE     |\ref CLK_CLKSEL1_UARTSEL_HXT          |\ref CLK_CLKDIV0_UART(x)      |
  * |\ref UART2_MODULE     |\ref CLK_CLKSEL1_UARTSEL_PLL          |\ref CLK_CLKDIV0_UART(x)      |
  * |\ref UART2_MODULE     |\ref CLK_CLKSEL1_UARTSEL_HIRC         |\ref CLK_CLKDIV0_UART(x)      |
  * |\ref UART1_MODULE     |\ref CLK_CLKSEL1_UARTSEL_HXT          |\ref CLK_CLKDIV0_UART(x)      |
  * |\ref UART1_MODULE     |\ref CLK_CLKSEL1_UARTSEL_PLL          |\ref CLK_CLKDIV0_UART(x)      |
  * |\ref UART1_MODULE     |\ref CLK_CLKSEL1_UARTSEL_HIRC         |\ref CLK_CLKDIV0_UART(x)      |
  * |\ref UART0_MODULE     |\ref CLK_CLKSEL1_UARTSEL_HXT          |\ref CLK_CLKDIV0_UART(x)      |
  * |\ref UART0_MODULE     |\ref CLK_CLKSEL1_UARTSEL_PLL          |\ref CLK_CLKDIV0_UART(x)      |
  * |\ref UART0_MODULE     |\ref CLK_CLKSEL1_UARTSEL_HIRC         |\ref CLK_CLKDIV0_UART(x)      |
  * |\ref SPI3_MODULE      |\ref CLK_CLKSEL1_SPI3SEL_PLL          | x                            |
  * |\ref SPI3_MODULE      |\ref CLK_CLKSEL1_SPI3SEL_PCLK         | x                            |
  * |\ref SPI2_MODULE      |\ref CLK_CLKSEL1_SPI2SEL_PLL          | x                            |
  * |\ref SPI2_MODULE      |\ref CLK_CLKSEL1_SPI2SEL_PCLK         | x                            |
  * |\ref SPI1_MODULE      |\ref CLK_CLKSEL1_SPI1SEL_PLL          | x                            |
  * |\ref SPI1_MODULE      |\ref CLK_CLKSEL1_SPI1SEL_PCLK         | x                            |
  * |\ref SPI0_MODULE      |\ref CLK_CLKSEL1_SPI0SEL_PLL          | x                            |
  * |\ref SPI0_MODULE      |\ref CLK_CLKSEL1_SPI0SEL_PCLK         | x                            |
  * |\ref I2C3_MODULE      | x                                    | x                            |
  * |\ref I2C2_MODULE      | x                                    | x                            |
  * |\ref I2C1_MODULE      | x                                    | x                            |
  * |\ref I2C0_MODULE      | x                                    | x                            |
  * |\ref ACMP_MODULE      | x                                    | x                            |
  * |\ref CLKO_MODULE      |\ref CLK_CLKSEL1_CLKOSEL_HXT          | x                            |
  * |\ref CLKO_MODULE      |\ref CLK_CLKSEL1_CLKOSEL_LXT          | x                            |
  * |\ref CLKO_MODULE      |\ref CLK_CLKSEL1_CLKOSEL_HCLK         | x                            |
  * |\ref CLKO_MODULE      |\ref CLK_CLKSEL1_CLKOSEL_HIRC         | x                            |
  * |\ref TMR3_MODULE      |\ref CLK_CLKSEL1_TMR3SEL_HXT          | x                            |
  * |\ref TMR3_MODULE      |\ref CLK_CLKSEL1_TMR3SEL_LXT          | x                            |
  * |\ref TMR3_MODULE      |\ref CLK_CLKSEL1_TMR3SEL_PCLK         | x                            |
  * |\ref TMR3_MODULE      |\ref CLK_CLKSEL1_TMR3SEL_LIRC         | x                            |
  * |\ref TMR3_MODULE      |\ref CLK_CLKSEL1_TMR3SEL_EXT          | x                            |
  * |\ref TMR3_MODULE      |\ref CLK_CLKSEL1_TMR3SEL_HIRC         | x                            |
  * |\ref TMR2_MODULE      |\ref CLK_CLKSEL1_TMR2SEL_HXT          | x                            |
  * |\ref TMR2_MODULE      |\ref CLK_CLKSEL1_TMR2SEL_LXT          | x                            |
  * |\ref TMR2_MODULE      |\ref CLK_CLKSEL1_TMR2SEL_PCLK         | x                            |
  * |\ref TMR2_MODULE      |\ref CLK_CLKSEL1_TMR2SEL_LIRC         | x                            |
  * |\ref TMR2_MODULE      |\ref CLK_CLKSEL1_TMR2SEL_EXT          | x                            |
  * |\ref TMR2_MODULE      |\ref CLK_CLKSEL1_TMR2SEL_HIRC         | x                            |
  * |\ref TMR1_MODULE      |\ref CLK_CLKSEL1_TMR1SEL_HXT          | x                            |
  * |\ref TMR1_MODULE      |\ref CLK_CLKSEL1_TMR1SEL_LXT          | x                            |
  * |\ref TMR1_MODULE      |\ref CLK_CLKSEL1_TMR1SEL_PCLK         | x                            |
  * |\ref TMR1_MODULE      |\ref CLK_CLKSEL1_TMR1SEL_LIRC         | x                            |
  * |\ref TMR1_MODULE      |\ref CLK_CLKSEL1_TMR1SEL_EXT          | x                            |
  * |\ref TMR1_MODULE      |\ref CLK_CLKSEL1_TMR1SEL_HIRC         | x                            |
  * |\ref TMR0_MODULE      |\ref CLK_CLKSEL1_TMR0SEL_HXT          | x                            |
  * |\ref TMR0_MODULE      |\ref CLK_CLKSEL1_TMR0SEL_LXT          | x                            |
  * |\ref TMR0_MODULE      |\ref CLK_CLKSEL1_TMR0SEL_PCLK         | x                            |
  * |\ref TMR0_MODULE      |\ref CLK_CLKSEL1_TMR0SEL_LIRC         | x                            |
  * |\ref TMR0_MODULE      |\ref CLK_CLKSEL1_TMR0SEL_EXT          | x                            |
  * |\ref TMR0_MODULE      |\ref CLK_CLKSEL1_TMR0SEL_HIRC         | x                            |
  * |\ref RTC_MODULE       | x                                    | x                            |
  * |\ref WWDT_MODULE      |\ref CLK_CLKSEL1_WWDTSEL_HCLK_DIV2048 | x                            |
  * |\ref WWDT_MODULE      |\ref CLK_CLKSEL1_WWDTSEL_LIRC         | x                            |
  * |\ref WDT_MODULE       |\ref CLK_CLKSEL1_WDTSEL_LXT           | x                            |
  * |\ref WDT_MODULE       |\ref CLK_CLKSEL1_WDTSEL_HCLK_DIV2048  | x                            |
  * |\ref WDT_MODULE       |\ref CLK_CLKSEL1_WDTSEL_LIRC          | x                            |
  *
  */

void CLK_SetModuleClock(uint32_t u32ModuleIdx, uint32_t u32ClkSrc, uint32_t u32ClkDiv)
{
    uint32_t u32tmp=0,u32sel=0,u32div=0;

    if(MODULE_CLKDIV_Msk(u32ModuleIdx)!=MODULE_NoMsk) {
        u32div =(uint32_t)&CLK->CLKDIV0+((MODULE_CLKDIV(u32ModuleIdx))*4);
        u32tmp = *(volatile uint32_t *)(u32div);
        u32tmp = ( u32tmp & ~(MODULE_CLKDIV_Msk(u32ModuleIdx)<<MODULE_CLKDIV_Pos(u32ModuleIdx)) ) | u32ClkDiv;
        *(volatile uint32_t *)(u32div) = u32tmp;
    }

    if(MODULE_CLKSEL_Msk(u32ModuleIdx)!=MODULE_NoMsk) {
        u32sel = (uint32_t)&CLK->CLKSEL0+((MODULE_CLKSEL(u32ModuleIdx))*4);
        u32tmp = *(volatile uint32_t *)(u32sel);
        u32tmp = ( u32tmp & ~(MODULE_CLKSEL_Msk(u32ModuleIdx)<<MODULE_CLKSEL_Pos(u32ModuleIdx)) ) | u32ClkSrc;
        *(volatile uint32_t *)(u32sel) = u32tmp;
    }
}

/**
  * @brief  This function enable clock source
  * @param  u32ClkMask is clock source mask. Including:
  *         - \ref CLK_PWRCTL_HXTEN_Msk
  *         - \ref CLK_PWRCTL_LXTEN_Msk
  *         - \ref CLK_PWRCTL_HIRCEN_Msk
  *         - \ref CLK_PWRCTL_LIRCEN_Msk
  * @return None
  */
void CLK_EnableXtalRC(uint32_t u32ClkMask)
{
    CLK->PWRCTL |= u32ClkMask;
}

/**
  * @brief  This function disable clock source
  * @param  u32ClkMask is clock source mask. Including:
  *         - \ref CLK_PWRCTL_HXTEN_Msk
  *         - \ref CLK_PWRCTL_LXTEN_Msk
  *         - \ref CLK_PWRCTL_HIRCEN_Msk
  *         - \ref CLK_PWRCTL_LIRCEN_Msk
  * @return None
  */
void CLK_DisableXtalRC(uint32_t u32ClkMask)
{
    CLK->PWRCTL &= ~u32ClkMask;
}

/**
  * @brief  This function enable module clock
  * @param[in]  u32ModuleIdx is module index. Including :
  *   - \ref PDMA_MODULE
  *   - \ref ISP_MODULE
  *   - \ref EBI_MODULE
  *   - \ref USBH_MODULE
  *   - \ref EMAC_MODULE
  *   - \ref SDH_MODULE
  *   - \ref CRC_MODULE
  *   - \ref CAP_MODULE
  *   - \ref USBD_MODULE
  *   - \ref CRPT_MODULE
  *   - \ref WDT_MODULE
  *   - \ref WWDT_MODULE
  *   - \ref RTC_MODULE
  *   - \ref TMR0_MODULE
  *   - \ref TMR1_MODULE
  *   - \ref TMR2_MODULE
  *   - \ref TMR3_MODULE
  *   - \ref CLKO_MODULE
  *   - \ref ACMP_MODULE
  *   - \ref I2C0_MODULE
  *   - \ref I2C1_MODULE
  *   - \ref I2C2_MODULE
  *   - \ref I2C3_MODULE
  *   - \ref SPI0_MODULE
  *   - \ref SPI1_MODULE
  *   - \ref SPI2_MODULE
  *   - \ref SPI3_MODULE
  *   - \ref UART0_MODULE
  *   - \ref UART1_MODULE
  *   - \ref UART2_MODULE
  *   - \ref UART3_MODULE
  *   - \ref UART4_MODULE
  *   - \ref UART5_MODULE
  *   - \ref CAN0_MODULE
  *   - \ref CAN1_MODULE
  *   - \ref OTG_MODULE
  *   - \ref ADC_MODULE
  *   - \ref I2S0_MODULE
  *   - \ref I2S1_MODULE
  *   - \ref PS2_MODULE
  *   - \ref SC0_MODULE
  *   - \ref SC1_MODULE
  *   - \ref SC2_MODULE
  *   - \ref SC3_MODULE
  *   - \ref SC4_MODULE
  *   - \ref SC5_MODULE
  *   - \ref I2C4_MODULE
  *   - \ref PWM0CH01_MODULE
  *   - \ref PWM0CH23_MODULE
  *   - \ref PWM0CH45_MODULE
  *   - \ref PWM1CH01_MODULE
  *   - \ref PWM1CH23_MODULE
  *   - \ref PWM1CH45_MODULE
  *   - \ref QEI0_MODULE
  *   - \ref QEI1_MODULE
  *   - \ref ECAP0_MODULE
  *   - \ref ECAP1_MODULE
  *   - \ref EPWM0_MODULE
  *   - \ref EPWM1_MODULE
  *   - \ref OPA_MODULE
  *   - \ref EADC_MODULE
  * @return None
  */
void CLK_EnableModuleClock(uint32_t u32ModuleIdx)
{
    *(volatile uint32_t *)((uint32_t)&CLK->AHBCLK+(MODULE_APBCLK(u32ModuleIdx)*4))  |= 1<<MODULE_IP_EN_Pos(u32ModuleIdx);
}

/**
  * @brief  This function disable module clock
  * @param[in]  u32ModuleIdx is module index. Including :
  *   - \ref PDMA_MODULE
  *   - \ref ISP_MODULE
  *   - \ref EBI_MODULE
  *   - \ref USBH_MODULE
  *   - \ref EMAC_MODULE
  *   - \ref SDH_MODULE
  *   - \ref CRC_MODULE
  *   - \ref CAP_MODULE
  *   - \ref USBD_MODULE
  *   - \ref CRPT_MODULE
  *   - \ref WDT_MODULE
  *   - \ref WWDT_MODULE
  *   - \ref RTC_MODULE
  *   - \ref TMR0_MODULE
  *   - \ref TMR1_MODULE
  *   - \ref TMR2_MODULE
  *   - \ref TMR3_MODULE
  *   - \ref CLKO_MODULE
  *   - \ref ACMP_MODULE
  *   - \ref I2C0_MODULE
  *   - \ref I2C1_MODULE
  *   - \ref I2C2_MODULE
  *   - \ref I2C3_MODULE
  *   - \ref SPI0_MODULE
  *   - \ref SPI1_MODULE
  *   - \ref SPI2_MODULE
  *   - \ref SPI3_MODULE
  *   - \ref UART0_MODULE
  *   - \ref UART1_MODULE
  *   - \ref UART2_MODULE
  *   - \ref UART3_MODULE
  *   - \ref UART4_MODULE
  *   - \ref UART5_MODULE
  *   - \ref CAN0_MODULE
  *   - \ref CAN1_MODULE
  *   - \ref OTG_MODULE
  *   - \ref ADC_MODULE
  *   - \ref I2S0_MODULE
  *   - \ref I2S1_MODULE
  *   - \ref PS2_MODULE
  *   - \ref SC0_MODULE
  *   - \ref SC1_MODULE
  *   - \ref SC2_MODULE
  *   - \ref SC3_MODULE
  *   - \ref SC4_MODULE
  *   - \ref SC5_MODULE
  *   - \ref I2C4_MODULE
  *   - \ref PWM0CH01_MODULE
  *   - \ref PWM0CH23_MODULE
  *   - \ref PWM0CH45_MODULE
  *   - \ref PWM1CH01_MODULE
  *   - \ref PWM1CH23_MODULE
  *   - \ref PWM1CH45_MODULE
  *   - \ref QEI0_MODULE
  *   - \ref QEI1_MODULE
  *   - \ref ECAP0_MODULE
  *   - \ref ECAP1_MODULE
  *   - \ref EPWM0_MODULE
  *   - \ref EPWM1_MODULE
  *   - \ref OPA_MODULE
  *   - \ref EADC_MODULE
  * @return None
  */
void CLK_DisableModuleClock(uint32_t u32ModuleIdx)
{
    *(volatile uint32_t *)((uint32_t)&CLK->AHBCLK+(MODULE_APBCLK(u32ModuleIdx)*4))  &= ~(1<<MODULE_IP_EN_Pos(u32ModuleIdx));
}

/**
  * @brief  This function set PLL frequency
  * @param[in]  u32PllClkSrc is PLL clock source. Including :
  *         - \ref CLK_PLLCTL_PLLSRC_HIRC
  *         - \ref CLK_PLLCTL_PLLSRC_HXT
  * @param[in]  u32PllFreq is PLL frequency
  * @return None
  */
uint32_t CLK_EnablePLL(uint32_t u32PllClkSrc, uint32_t u32PllFreq)
{
    uint32_t u32PllSrcClk, u32NR, u32NF, u32NO, u32CLK_SRC;
    uint32_t u32Tmp, u32Tmp2, u32Tmp3, u32Min, u32MinNF, u32MinNR;

    /* Disable PLL first to avoid unstable when setting PLL */
    CLK_DisablePLL();

    /* PLL source clock is from HXT */
    if(u32PllClkSrc == CLK_PLLCTL_PLLSRC_HXT) {
        /* Enable HXT clock */
        CLK->PWRCTL |= CLK_PWRCTL_HXTEN_Msk;

        /* Wait for HXT clock ready */
        CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

        /* Select PLL source clock from HXT */
        u32CLK_SRC = CLK_PLLCTL_PLLSRC_HXT;
        u32PllSrcClk = __HXT;

        /* u32NR start from 2 */
        u32NR = 2;
    }

    /* PLL source clock is from HIRC */
    else {
        /* Enable HIRC clock */
        CLK->PWRCTL |= CLK_PWRCTL_HIRCEN_Msk;

        /* Wait for HIRC clock ready */
        CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

        /* Select PLL source clock from HIRC */
        u32CLK_SRC = CLK_PLLCTL_PLLSRC_HIRC;
        u32PllSrcClk = __HIRC;

        /* u32NR start from 4 when FIN = 22.1184MHz to avoid calculation overflow */
        u32NR = 4;
    }

    /* Select "NO" according to request frequency */
    if((u32PllFreq <= FREQ_500MHZ) && (u32PllFreq > FREQ_250MHZ)) {
        u32NO = 0;
    } else if((u32PllFreq <= FREQ_250MHZ) && (u32PllFreq > FREQ_125MHZ)) {
        u32NO = 1;
        u32PllFreq = u32PllFreq << 1;
    } else if((u32PllFreq <= FREQ_125MHZ) && (u32PllFreq >= FREQ_50MHZ)) {
        u32NO = 3;
        u32PllFreq = u32PllFreq << 2;
    } else {
        /* Wrong frequency request. Just return default setting. */
        goto lexit;
    }

    /* Find best solution */
    u32Min = (uint32_t) - 1;
    u32MinNR = 0;
    u32MinNF = 0;
    for(; u32NR <= 33; u32NR++) {
        u32Tmp = u32PllSrcClk / u32NR;
        if((u32Tmp > 1600000) && (u32Tmp < 16000000)) {
            for(u32NF = 2; u32NF <= 513; u32NF++) {
                u32Tmp2 = u32Tmp * u32NF;
                if((u32Tmp2 >= 200000000) && (u32Tmp2 <= 500000000)) {
                    u32Tmp3 = (u32Tmp2 > u32PllFreq) ? u32Tmp2 - u32PllFreq : u32PllFreq - u32Tmp2;
                    if(u32Tmp3 < u32Min) {
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
    CLK->PLLCTL = u32CLK_SRC | (u32NO << 14) | ((u32MinNR - 2) << 9) | (u32MinNF - 2);

    /* Wait for PLL clock stable */
    CLK_WaitClockReady(CLK_STATUS_PLLSTB_Msk);

    /* Return actual PLL output clock frequency */
    return u32PllSrcClk / ((u32NO + 1) * u32MinNR) * u32MinNF;

lexit:

    /* Apply default PLL setting and return */
    if(u32PllClkSrc == CLK_PLLCTL_PLLSRC_HXT)
        CLK->PLLCTL = CLK_PLLCTL_84MHz_HXT; /* 84MHz */
    else
        CLK->PLLCTL = CLK_PLLCTL_50MHz_HIRC; /* 50MHz */

    /* Wait for PLL clock stable */
    CLK_WaitClockReady(CLK_STATUS_PLLSTB_Msk);

    return CLK_GetPLLClockFreq();
}

/**
  * @brief  This function disable PLL
  * @return None
  */
void CLK_DisablePLL(void)
{
    CLK->PLLCTL |= CLK_PLLCTL_PD_Msk;
}

/**
  * @brief  This function set SysTick clock source
  * @param[in]  u32ClkSrc is SysTick clock source. Including :
  *  - \ref CLK_CLKSEL0_STCLKSEL_HXT
  *  - \ref CLK_CLKSEL0_STCLKSEL_LXT
  *  - \ref CLK_CLKSEL0_STCLKSEL_HXT_DIV2
  *  - \ref CLK_CLKSEL0_STCLKSEL_HCLK_DIV2
  *  - \ref CLK_CLKSEL0_STCLKSEL_HIRC_DIV2
  * @return None
  */
void CLK_SetSysTickClockSrc(uint32_t u32ClkSrc)
{
    CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_STCLKSEL_Msk) | u32ClkSrc ;
}
/**
  * @brief  This function execute delay function.
  * @param[in]  us  Delay time. The Max value is 2^24 / CPU Clock(MHz). Ex:
  *                             50MHz => 335544us, 48MHz => 349525us, 28MHz => 699050us ...
  * @return None
  * @details    Use the SysTick to generate the delay time and the UNIT is in us.
  *             The SysTick clock source is from HCLK, i.e the same as system core clock.
  */
void CLK_SysTickDelay(uint32_t us)
{
    SysTick->LOAD = us * CyclesPerUs;
    SysTick->VAL  =  (0x00);
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

    /* Waiting for down-count to zero */
    while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);
    SysTick->CTRL = 0 ;
}

/**
  * @brief  This function check selected clock source status
  * @param[in]  u32ClkMask is selected clock source. Including
  *           - \ref CLK_STATUS_CLKSFAIL_Msk
  *           - \ref CLK_STATUS_HIRCSTB_Msk
  *           - \ref CLK_STATUS_LIRCSTB_Msk
  *           - \ref CLK_STATUS_PLLSTB_Msk
  *           - \ref CLK_STATUS_LXTSTB_Msk
  *           - \ref CLK_STATUS_HXTSTB_Msk
  *
  * @return   0  clock is not stable
  *           1  clock is stable
  *
  * @details  To wait for clock ready by specified CLKSTATUS bit or timeout (~300ms)
  */
uint32_t CLK_WaitClockReady(uint32_t u32ClkMask)
{
    int32_t i32TimeOutCnt = 2160000;

    while((CLK->STATUS & u32ClkMask) != u32ClkMask) {
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
    if( u32ClkSrc == CLK_CLKSEL0_STCLKSEL_HCLK )
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

/*@}*/ /* end of group NUC472_442_CLK_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_CLK_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/

