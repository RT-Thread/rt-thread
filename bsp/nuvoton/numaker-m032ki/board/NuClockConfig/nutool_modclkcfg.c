/****************************************************************************
 * @file     nutool_modclkcfg.c
 * @version  V1.05
 * @Date     2020/09/30-13:56:58
 * @brief    NuMicro generated code file
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright (C) 2013-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

/********************
MCU:M032SE3AE(ULQFP64)
Base Clocks:
LIRC:38.4000kHz
HIRC:48MHz
LXT:32.7680kHz
HXT:12MHz
PLL:72MHz
HCLK:48MHz
PCLK0:48MHz
PCLK1:48MHz
Enabled-Module Frequencies:
ACMP01=Bus Clock(PCLK1):48MHz
ADC=Bus Clock(PCLK1):48MHz/Engine Clock:48MHz
CRC=Bus Clock(HCLK):48MHz
EBI=Bus Clock(HCLK):48MHz
HDIV=Bus Clock(HCLK):48MHz
I2C0=Bus Clock(PCLK0):48MHz
I2C1=Bus Clock(PCLK1):48MHz
ISP=Bus Clock(HCLK):48MHz/Engine Clock:48MHz
PDMA=Bus Clock(HCLK):48MHz
PWM0=Bus Clock(PCLK0):48MHz/Engine Clock:48MHz
PWM1=Bus Clock(PCLK1):48MHz/Engine Clock:48MHz
SPI0=Bus Clock(PCLK1):48MHz/Engine Clock:48MHz
SYSTICK=Bus Clock(HCLK):48MHz/Engine Clock:24MHz
TMR0=Bus Clock(PCLK0):48MHz/Engine Clock:48MHz
TMR1=Bus Clock(PCLK0):48MHz/Engine Clock:48MHz
TMR2=Bus Clock(PCLK1):48MHz/Engine Clock:48MHz
TMR3=Bus Clock(PCLK1):48MHz/Engine Clock:48MHz
UART0=Bus Clock(PCLK0):48MHz/Engine Clock:48MHz
UART1=Bus Clock(PCLK1):48MHz/Engine Clock:48MHz
UART2=Bus Clock(PCLK0):48MHz/Engine Clock:48MHz
USBD=Bus Clock(PCLK0):48MHz/Engine Clock:48MHz
USCI0=Bus Clock(PCLK0):48MHz
WDT=Bus Clock(PCLK0):48MHz/Engine Clock:38.4000kHz
WWDT=Bus Clock(PCLK0):48MHz/Engine Clock:23.4375kHz
********************/

#include "M031Series.h"

void nutool_modclkcfg_init_acmp01(void)
{
    CLK_EnableModuleClock(ACMP01_MODULE);

    return;
}

void nutool_modclkcfg_deinit_acmp01(void)
{
    CLK_DisableModuleClock(ACMP01_MODULE);

    return;
}

void nutool_modclkcfg_init_adc(void)
{
    CLK_EnableModuleClock(ADC_MODULE);
    CLK_SetModuleClock(ADC_MODULE, CLK_CLKSEL2_ADCSEL_PCLK1, CLK_CLKDIV0_ADC(1));

    return;
}

void nutool_modclkcfg_deinit_adc(void)
{
    CLK_DisableModuleClock(ADC_MODULE);

    return;
}

void nutool_modclkcfg_init_crc(void)
{
    CLK_EnableModuleClock(CRC_MODULE);

    return;
}

void nutool_modclkcfg_deinit_crc(void)
{
    CLK_DisableModuleClock(CRC_MODULE);

    return;
}

void nutool_modclkcfg_init_ebi(void)
{
    CLK_EnableModuleClock(EBI_MODULE);

    return;
}

void nutool_modclkcfg_deinit_ebi(void)
{
    CLK_DisableModuleClock(EBI_MODULE);

    return;
}

void nutool_modclkcfg_init_hdiv(void)
{
    CLK_EnableModuleClock(HDIV_MODULE);

    return;
}

void nutool_modclkcfg_deinit_hdiv(void)
{
    CLK_DisableModuleClock(HDIV_MODULE);

    return;
}

void nutool_modclkcfg_init_i2c0(void)
{
    CLK_EnableModuleClock(I2C0_MODULE);

    return;
}

void nutool_modclkcfg_deinit_i2c0(void)
{
    CLK_DisableModuleClock(I2C0_MODULE);

    return;
}

void nutool_modclkcfg_init_i2c1(void)
{
    CLK_EnableModuleClock(I2C1_MODULE);

    return;
}

void nutool_modclkcfg_deinit_i2c1(void)
{
    CLK_DisableModuleClock(I2C1_MODULE);

    return;
}

void nutool_modclkcfg_init_isp(void)
{
    CLK_EnableModuleClock(ISP_MODULE);

    return;
}

void nutool_modclkcfg_deinit_isp(void)
{
    CLK_DisableModuleClock(ISP_MODULE);

    return;
}

void nutool_modclkcfg_init_pdma(void)
{
    CLK_EnableModuleClock(PDMA_MODULE);

    return;
}

void nutool_modclkcfg_deinit_pdma(void)
{
    CLK_DisableModuleClock(PDMA_MODULE);

    return;
}

void nutool_modclkcfg_init_pwm0(void)
{
    CLK_EnableModuleClock(PWM0_MODULE);
    CLK_SetModuleClock(PWM0_MODULE, CLK_CLKSEL2_PWM0SEL_PCLK0, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_pwm0(void)
{
    CLK_DisableModuleClock(PWM0_MODULE);

    return;
}

void nutool_modclkcfg_init_pwm1(void)
{
    CLK_EnableModuleClock(PWM1_MODULE);
    CLK_SetModuleClock(PWM1_MODULE, CLK_CLKSEL2_PWM1SEL_PCLK1, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_pwm1(void)
{
    CLK_DisableModuleClock(PWM1_MODULE);

    return;
}

void nutool_modclkcfg_init_spi0(void)
{
    CLK_EnableModuleClock(SPI0_MODULE);
    CLK_SetModuleClock(SPI0_MODULE, CLK_CLKSEL2_SPI0SEL_PCLK1, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_spi0(void)
{
    CLK_DisableModuleClock(SPI0_MODULE);

    return;
}

void nutool_modclkcfg_init_systick(void)
{
    CLK_EnableSysTick(CLK_CLKSEL0_STCLKSEL_HIRC_DIV2, 0);

    return;
}

void nutool_modclkcfg_deinit_systick(void)
{
    CLK_DisableSysTick();

    return;
}

void nutool_modclkcfg_init_tmr0(void)
{
    CLK_EnableModuleClock(TMR0_MODULE);
    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_HIRC, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_tmr0(void)
{
    CLK_DisableModuleClock(TMR0_MODULE);

    return;
}

void nutool_modclkcfg_init_tmr1(void)
{
    CLK_EnableModuleClock(TMR1_MODULE);
    CLK_SetModuleClock(TMR1_MODULE, CLK_CLKSEL1_TMR1SEL_HIRC, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_tmr1(void)
{
    CLK_DisableModuleClock(TMR1_MODULE);

    return;
}

void nutool_modclkcfg_init_tmr2(void)
{
    CLK_EnableModuleClock(TMR2_MODULE);
    CLK_SetModuleClock(TMR2_MODULE, CLK_CLKSEL1_TMR2SEL_HIRC, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_tmr2(void)
{
    CLK_DisableModuleClock(TMR2_MODULE);

    return;
}

void nutool_modclkcfg_init_tmr3(void)
{
    CLK_EnableModuleClock(TMR3_MODULE);
    CLK_SetModuleClock(TMR3_MODULE, CLK_CLKSEL1_TMR3SEL_HIRC, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_tmr3(void)
{
    CLK_DisableModuleClock(TMR3_MODULE);

    return;
}

void nutool_modclkcfg_init_uart0(void)
{
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    return;
}

void nutool_modclkcfg_deinit_uart0(void)
{
    CLK_DisableModuleClock(UART0_MODULE);

    return;
}

void nutool_modclkcfg_init_uart1(void)
{
    CLK_EnableModuleClock(UART1_MODULE);
    CLK_SetModuleClock(UART1_MODULE, CLK_CLKSEL1_UART1SEL_PCLK1, CLK_CLKDIV0_UART1(1));

    return;
}

void nutool_modclkcfg_deinit_uart1(void)
{
    CLK_DisableModuleClock(UART1_MODULE);

    return;
}

void nutool_modclkcfg_init_uart2(void)
{
    CLK_EnableModuleClock(UART2_MODULE);
    CLK_SetModuleClock(UART2_MODULE, CLK_CLKSEL3_UART2SEL_PCLK0, CLK_CLKDIV4_UART2(1));

    return;
}

void nutool_modclkcfg_deinit_uart2(void)
{
    CLK_DisableModuleClock(UART2_MODULE);

    return;
}

void nutool_modclkcfg_init_usbd(void)
{
    CLK_EnableModuleClock(USBD_MODULE);
    CLK_SetModuleClock(USBD_MODULE, CLK_CLKSEL0_USBDSEL_HIRC, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_usbd(void)
{
    CLK_DisableModuleClock(USBD_MODULE);

    return;
}

void nutool_modclkcfg_init_usci0(void)
{
    CLK_EnableModuleClock(USCI0_MODULE);

    return;
}

void nutool_modclkcfg_deinit_usci0(void)
{
    CLK_DisableModuleClock(USCI0_MODULE);

    return;
}

void nutool_modclkcfg_init_wdt(void)
{
    CLK_EnableModuleClock(WDT_MODULE);
    CLK_SetModuleClock(WDT_MODULE, CLK_CLKSEL1_WDTSEL_LIRC, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_wdt(void)
{
    CLK_DisableModuleClock(WDT_MODULE);

    return;
}

void nutool_modclkcfg_init_wwdt(void)
{
    CLK_EnableModuleClock(WWDT_MODULE);
    CLK_SetModuleClock(WWDT_MODULE, CLK_CLKSEL1_WWDTSEL_HCLK_DIV2048, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_wwdt(void)
{
    CLK_DisableModuleClock(WWDT_MODULE);

    return;
}

void nutool_modclkcfg_init_rtc(void)
{
    CLK_EnableModuleClock(RTC_MODULE);

    return;
}

void nutool_modclkcfg_deinit_rtc(void)
{
    CLK_DisableModuleClock(RTC_MODULE);

    return;
}

void nutool_modclkcfg_init_base(void)
{
    /* Enable clock source */
    CLK_EnableXtalRC(CLK_PWRCTL_LIRCEN_Msk | CLK_PWRCTL_HIRCEN_Msk | CLK_PWRCTL_LXTEN_Msk | CLK_PWRCTL_HXTEN_Msk);

    /* Waiting for clock source ready */
    CLK_WaitClockReady(CLK_STATUS_LIRCSTB_Msk | CLK_STATUS_HIRCSTB_Msk | CLK_STATUS_LXTSTB_Msk | CLK_STATUS_HXTSTB_Msk);

    /* Disable PLL first to avoid unstable when setting PLL */
    CLK_DisablePLL();

    /* Set PLL frequency */
    CLK->PLLCTL = (CLK->PLLCTL & ~(0x000FFFFFul)) | 0x0008C02Eul;

    /* Waiting for PLL ready */
    CLK_WaitClockReady(CLK_STATUS_PLLSTB_Msk);

    /* If the defines do not exist in your project, please refer to the related clk.h in the Header folder appended to the tool package. */
    /* Set HCLK clock */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV0_HCLK(1));

    /* Set PCLK-related clock */
    CLK->PCLKDIV = (CLK_PCLKDIV_APB0DIV_DIV1 | CLK_PCLKDIV_APB1DIV_DIV1);

    return;
}

void nutool_modclkcfg_init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/
    //CLK->PWRCTL = (CLK->PWRCTL & ~(0x0000000Ful)) | 0x0231001Ful;
    //CLK->PLLCTL = (CLK->PLLCTL & ~(0x000FFFFFul)) | 0x0008C02Eul;
    //CLK->CLKDIV0 = (CLK->CLKDIV0 & ~(0x00FFFFFFul)) | 0x00000000ul;
    //CLK->CLKDIV4 = (CLK->CLKDIV4 & ~(0x0000000Ful)) | 0x00000000ul;
    //CLK->PCLKDIV = (CLK->PCLKDIV & ~(0x00000077ul)) | 0x00000000ul;
    //CLK->CLKSEL0 = (CLK->CLKSEL0 & ~(0x0000013Ful)) | 0x0000003Ful;
    //CLK->CLKSEL1 = (CLK->CLKSEL1 & ~(0x7777777Ful)) | 0x4477773Bul;
    //CLK->CLKSEL2 = (CLK->CLKSEL2 & ~(0x00300033ul)) | 0x00200023ul;
    //CLK->CLKSEL3 = (CLK->CLKSEL3 & ~(0x07000000ul)) | 0x04000000ul;
    //CLK->AHBCLK = (CLK->AHBCLK & ~(0x0000009Eul)) | 0x0000009Eul;
    //CLK->APBCLK0 = (CLK->APBCLK0 & ~(0x180723FDul)) | 0x180723BDul;
    //CLK->APBCLK1 = (CLK->APBCLK1 & ~(0x00030100ul)) | 0x00030100ul;
    //CLK->CLKOCTL = (CLK->CLKOCTL & ~(0x0000003Ful)) | 0x00000000ul;
    //SysTick->CTRL = (SysTick->CTRL & ~(0x00000005ul)) | 0x00000001ul;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable base clock */
    nutool_modclkcfg_init_base();

    /* Enable module clock and set clock source */
    nutool_modclkcfg_init_acmp01();
    nutool_modclkcfg_init_adc();
    nutool_modclkcfg_init_crc();
    nutool_modclkcfg_init_ebi();
    nutool_modclkcfg_init_hdiv();
    nutool_modclkcfg_init_i2c0();
    nutool_modclkcfg_init_i2c1();
    nutool_modclkcfg_init_isp();
    nutool_modclkcfg_init_pdma();
    nutool_modclkcfg_init_pwm0();
    nutool_modclkcfg_init_pwm1();
    nutool_modclkcfg_init_spi0();
    nutool_modclkcfg_init_systick();
    nutool_modclkcfg_init_tmr0();
    nutool_modclkcfg_init_tmr1();
    nutool_modclkcfg_init_tmr2();
    nutool_modclkcfg_init_tmr3();
    nutool_modclkcfg_init_uart0();
    nutool_modclkcfg_init_uart1();
    nutool_modclkcfg_init_uart2();
    nutool_modclkcfg_init_usbd();
    nutool_modclkcfg_init_usci0();
    nutool_modclkcfg_init_wdt();
    nutool_modclkcfg_init_wwdt();
    nutool_modclkcfg_init_rtc();

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

    /* Lock protected registers */
    SYS_LockReg();

    return;
}

/*** (C) COPYRIGHT 2013-2020 Nuvoton Technology Corp. ***/
