/****************************************************************************
 * @file     nutool_modclkcfg.c
 * @version  V1.05
 * @Date     2020/11/11-11:43:32 
 * @brief    NuMicro generated code file
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright (C) 2013-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

/********************
MCU:M2354KJFAE(LQFP128)
Base Clocks:
HIRC:12MHz
HIRC48:48MHz
MIRC:4MHz
LXT:32.7680kHz
HXT:12MHz
PLL:96MHz
HCLK:96MHz
PCLK0:96MHz
PCLK1:96MHz
Enabled-Module Frequencies:
ACMP01=Bus Clock(PCLK1):96MHz
BPWM0=Bus Clock(PCLK0):96MHz/Engine Clock:96MHz
BPWM1=Bus Clock(PCLK1):96MHz/Engine Clock:96MHz
CAN0=Bus Clock(PCLK0):96MHz
CRC=Bus Clock(HCLK):96MHz
CRPT=Bus Clock(HCLK):96MHz
DAC=Bus Clock(PCLK1):96MHz
EADC=Bus Clock(PCLK0):96MHz/Engine Clock:96MHz
EBI=Bus Clock(HCLK):96MHz
ECAP0=Bus Clock(PCLK0):96MHz
ECAP1=Bus Clock(PCLK1):96MHz
EPWM0=Bus Clock(PCLK0):96MHz/Engine Clock:96MHz
EPWM1=Bus Clock(PCLK1):96MHz/Engine Clock:96MHz
EWDT=Bus Clock(PCLK0):96MHz/Engine Clock:32.7680kHz
EWWDT=Bus Clock(PCLK0):96MHz/Engine Clock:46.8750kHz
FMCIDLE=Bus Clock(HCLK):96MHz/Engine Clock:12MHz
GPA=Bus Clock(HCLK):96MHz
GPB=Bus Clock(HCLK):96MHz
GPC=Bus Clock(HCLK):96MHz
GPD=Bus Clock(HCLK):96MHz
GPE=Bus Clock(HCLK):96MHz
GPF=Bus Clock(HCLK):96MHz
GPG=Bus Clock(HCLK):96MHz
GPH=Bus Clock(HCLK):96MHz
I2C0=Bus Clock(PCLK0):96MHz
I2C1=Bus Clock(PCLK1):96MHz
I2C2=Bus Clock(PCLK0):96MHz
I2S0=Bus Clock(PCLK0):96MHz/Engine Clock:96MHz
ISP=Bus Clock(HCLK):96MHz/Engine Clock:12MHz
KS=Bus Clock(HCLK):96MHz
LCD=Bus Clock(PCLK1):96MHz/Engine Clock:32.7680kHz
OTG=Bus Clock(PCLK1):96MHz/Engine Clock:48MHz
PDMA0=Bus Clock(HCLK):96MHz
PDMA1=Bus Clock(HCLK):96MHz
QEI0=Bus Clock(PCLK0):96MHz
QEI1=Bus Clock(PCLK1):96MHz
QSPI0=Bus Clock(PCLK0):96MHz/Engine Clock:96MHz
RTC=Bus Clock(PCLK0):96MHz/Engine Clock:32.7680kHz
SC0=Bus Clock(PCLK0):96MHz/Engine Clock:12MHz
SC1=Bus Clock(PCLK1):96MHz/Engine Clock:12MHz
SC2=Bus Clock(PCLK0):96MHz/Engine Clock:12MHz
SDH0=Bus Clock(HCLK):96MHz/Engine Clock:96MHz
SPI0=Bus Clock(PCLK1):96MHz/Engine Clock:96MHz
SPI1=Bus Clock(PCLK0):96MHz/Engine Clock:96MHz
SPI2=Bus Clock(PCLK1):96MHz/Engine Clock:96MHz
SPI3=Bus Clock(PCLK0):96MHz/Engine Clock:96MHz
SRAM0=Bus Clock(HCLK):96MHz
SRAM1=Bus Clock(HCLK):96MHz
SRAM2=Bus Clock(HCLK):96MHz
SYSTICK=Bus Clock(HCLK):96MHz/Engine Clock:96MHz
TAMPER=Bus Clock(PCLK0):96MHz
TMR0=Bus Clock(PCLK0):96MHz/Engine Clock:12MHz
TMR1=Bus Clock(PCLK0):96MHz/Engine Clock:12MHz
TMR2=Bus Clock(PCLK1):96MHz/Engine Clock:12MHz
TMR3=Bus Clock(PCLK1):96MHz/Engine Clock:12MHz
TMR4=Bus Clock(PCLK0):96MHz/Engine Clock:12MHz
TMR5=Bus Clock(PCLK0):96MHz/Engine Clock:12MHz
TRNG=Bus Clock(PCLK0):96MHz/Engine Clock:32.7680kHz
UART0=Bus Clock(PCLK0):96MHz/Engine Clock:12MHz
UART1=Bus Clock(PCLK1):96MHz/Engine Clock:12MHz
UART2=Bus Clock(PCLK0):96MHz/Engine Clock:12MHz
UART3=Bus Clock(PCLK1):96MHz/Engine Clock:12MHz
UART4=Bus Clock(PCLK0):96MHz/Engine Clock:12MHz
UART5=Bus Clock(PCLK1):96MHz/Engine Clock:12MHz
USBD=Bus Clock(PCLK0):96MHz/Engine Clock:48MHz
USBH=Bus Clock(HCLK):96MHz/Engine Clock:48MHz
USCI0=Bus Clock(PCLK0):96MHz
USCI1=Bus Clock(PCLK1):96MHz
WDT=Bus Clock(PCLK0):96MHz/Engine Clock:32.7680kHz
WWDT=Bus Clock(PCLK0):96MHz/Engine Clock:46.8750kHz
********************/

#include "M2354.h"
#include "rtconfig.h"

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

void nutool_modclkcfg_init_bpwm0(void)
{
    CLK_EnableModuleClock(BPWM0_MODULE);
    CLK_SetModuleClock(BPWM0_MODULE, CLK_CLKSEL2_BPWM0SEL_PCLK0, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_bpwm0(void)
{
    CLK_DisableModuleClock(BPWM0_MODULE);

    return;
}

void nutool_modclkcfg_init_bpwm1(void)
{
    CLK_EnableModuleClock(BPWM1_MODULE);
    CLK_SetModuleClock(BPWM1_MODULE, CLK_CLKSEL2_BPWM1SEL_PCLK1, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_bpwm1(void)
{
    CLK_DisableModuleClock(BPWM1_MODULE);

    return;
}

void nutool_modclkcfg_init_can0(void)
{
    CLK_EnableModuleClock(CAN0_MODULE);

    return;
}

void nutool_modclkcfg_deinit_can0(void)
{
    CLK_DisableModuleClock(CAN0_MODULE);

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

void nutool_modclkcfg_init_crpt(void)
{
    CLK_EnableModuleClock(CRPT_MODULE);

    return;
}

void nutool_modclkcfg_deinit_crpt(void)
{
    CLK_DisableModuleClock(CRPT_MODULE);

    return;
}

void nutool_modclkcfg_init_dac(void)
{
    CLK_EnableModuleClock(DAC_MODULE);

    return;
}

void nutool_modclkcfg_deinit_dac(void)
{
    CLK_DisableModuleClock(DAC_MODULE);

    return;
}

void nutool_modclkcfg_init_eadc(void)
{
    CLK_EnableModuleClock(EADC_MODULE);
    CLK_SetModuleClock(EADC_MODULE, MODULE_NoMsk, CLK_CLKDIV0_EADC(8));

    return;
}

void nutool_modclkcfg_deinit_eadc(void)
{
    CLK_DisableModuleClock(EADC_MODULE);

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

void nutool_modclkcfg_init_ecap0(void)
{
    CLK_EnableModuleClock(ECAP0_MODULE);

    return;
}

void nutool_modclkcfg_deinit_ecap0(void)
{
    CLK_DisableModuleClock(ECAP0_MODULE);

    return;
}

void nutool_modclkcfg_init_ecap1(void)
{
    CLK_EnableModuleClock(ECAP1_MODULE);

    return;
}

void nutool_modclkcfg_deinit_ecap1(void)
{
    CLK_DisableModuleClock(ECAP1_MODULE);

    return;
}

void nutool_modclkcfg_init_epwm0(void)
{
    CLK_EnableModuleClock(EPWM0_MODULE);
    CLK_SetModuleClock(EPWM0_MODULE, CLK_CLKSEL2_EPWM0SEL_PCLK0, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_epwm0(void)
{
    CLK_DisableModuleClock(EPWM0_MODULE);

    return;
}

void nutool_modclkcfg_init_epwm1(void)
{
    CLK_EnableModuleClock(EPWM1_MODULE);
    CLK_SetModuleClock(EPWM1_MODULE, CLK_CLKSEL2_EPWM1SEL_PCLK1, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_epwm1(void)
{
    CLK_DisableModuleClock(EPWM1_MODULE);

    return;
}

void nutool_modclkcfg_init_ewdt(void)
{
    CLK_EnableModuleClock(EWDT_MODULE);
    CLK_SetModuleClock(EWDT_MODULE, CLK_CLKSEL1_EWDTSEL_LXT, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_ewdt(void)
{
    CLK_DisableModuleClock(EWDT_MODULE);

    return;
}

void nutool_modclkcfg_init_ewwdt(void)
{
    CLK_EnableModuleClock(EWWDT_MODULE);
    CLK_SetModuleClock(EWWDT_MODULE, CLK_CLKSEL1_EWWDTSEL_HCLK_DIV2048, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_ewwdt(void)
{
    CLK_DisableModuleClock(EWWDT_MODULE);

    return;
}

void nutool_modclkcfg_init_exst(void)
{
    CLK_EnableModuleClock(EXST_MODULE);

    return;
}

void nutool_modclkcfg_deinit_exst(void)
{
    CLK_DisableModuleClock(EXST_MODULE);

    return;
}

void nutool_modclkcfg_init_fmcidle(void)
{
    CLK_EnableModuleClock(FMCIDLE_MODULE);

    return;
}

void nutool_modclkcfg_deinit_fmcidle(void)
{
    CLK_DisableModuleClock(FMCIDLE_MODULE);

    return;
}

void nutool_modclkcfg_init_gpa(void)
{
    CLK_EnableModuleClock(GPA_MODULE);

    return;
}

void nutool_modclkcfg_deinit_gpa(void)
{
    CLK_DisableModuleClock(GPA_MODULE);

    return;
}

void nutool_modclkcfg_init_gpb(void)
{
    CLK_EnableModuleClock(GPB_MODULE);

    return;
}

void nutool_modclkcfg_deinit_gpb(void)
{
    CLK_DisableModuleClock(GPB_MODULE);

    return;
}

void nutool_modclkcfg_init_gpc(void)
{
    CLK_EnableModuleClock(GPC_MODULE);

    return;
}

void nutool_modclkcfg_deinit_gpc(void)
{
    CLK_DisableModuleClock(GPC_MODULE);

    return;
}

void nutool_modclkcfg_init_gpd(void)
{
    CLK_EnableModuleClock(GPD_MODULE);

    return;
}

void nutool_modclkcfg_deinit_gpd(void)
{
    CLK_DisableModuleClock(GPD_MODULE);

    return;
}

void nutool_modclkcfg_init_gpe(void)
{
    CLK_EnableModuleClock(GPE_MODULE);

    return;
}

void nutool_modclkcfg_deinit_gpe(void)
{
    CLK_DisableModuleClock(GPE_MODULE);

    return;
}

void nutool_modclkcfg_init_gpf(void)
{
    CLK_EnableModuleClock(GPF_MODULE);

    return;
}

void nutool_modclkcfg_deinit_gpf(void)
{
    CLK_DisableModuleClock(GPF_MODULE);

    return;
}

void nutool_modclkcfg_init_gpg(void)
{
    CLK_EnableModuleClock(GPG_MODULE);

    return;
}

void nutool_modclkcfg_deinit_gpg(void)
{
    CLK_DisableModuleClock(GPG_MODULE);

    return;
}

void nutool_modclkcfg_init_gph(void)
{
    CLK_EnableModuleClock(GPH_MODULE);

    return;
}

void nutool_modclkcfg_deinit_gph(void)
{
    CLK_DisableModuleClock(GPH_MODULE);

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

void nutool_modclkcfg_init_i2c2(void)
{
    CLK_EnableModuleClock(I2C2_MODULE);

    return;
}

void nutool_modclkcfg_deinit_i2c2(void)
{
    CLK_DisableModuleClock(I2C2_MODULE);

    return;
}

void nutool_modclkcfg_init_i2s0(void)
{
    CLK_EnableModuleClock(I2S0_MODULE);
    CLK_SetModuleClock(I2S0_MODULE, CLK_CLKSEL3_I2S0SEL_PCLK0, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_i2s0(void)
{
    CLK_DisableModuleClock(I2S0_MODULE);

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

void nutool_modclkcfg_init_ks(void)
{
    CLK_EnableModuleClock(KS_MODULE);

    return;
}

void nutool_modclkcfg_deinit_ks(void)
{
    CLK_DisableModuleClock(KS_MODULE);

    return;
}

void nutool_modclkcfg_init_lcd(void)
{
    CLK_EnableModuleClock(LCD_MODULE);
    CLK_SetModuleClock(LCD_MODULE, CLK_CLKSEL1_LCDSEL_LXT, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_lcd(void)
{
    CLK_DisableModuleClock(LCD_MODULE);

    return;
}

void nutool_modclkcfg_init_lcdcp(void)
{
    CLK_EnableModuleClock(LCDCP_MODULE);
    CLK_SetModuleClock(LCDCP_MODULE, CLK_CLKSEL1_LCDCPSEL_MIRC, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_lcdcp(void)
{
    CLK_DisableModuleClock(LCDCP_MODULE);

    return;
}

void nutool_modclkcfg_init_otg(void)
{
    CLK_EnableModuleClock(OTG_MODULE);
    CLK_SetModuleClock(OTG_MODULE, CLK_CLKSEL0_USBSEL_PLL, CLK_CLKDIV0_USB(2));

    return;
}

void nutool_modclkcfg_deinit_otg(void)
{
    CLK_DisableModuleClock(OTG_MODULE);

    return;
}

void nutool_modclkcfg_init_pdma0(void)
{
    CLK_EnableModuleClock(PDMA0_MODULE);

    return;
}

void nutool_modclkcfg_deinit_pdma0(void)
{
    CLK_DisableModuleClock(PDMA0_MODULE);

    return;
}

void nutool_modclkcfg_init_pdma1(void)
{
    CLK_EnableModuleClock(PDMA1_MODULE);

    return;
}

void nutool_modclkcfg_deinit_pdma1(void)
{
    CLK_DisableModuleClock(PDMA1_MODULE);

    return;
}

void nutool_modclkcfg_init_qei0(void)
{
    CLK_EnableModuleClock(QEI0_MODULE);

    return;
}

void nutool_modclkcfg_deinit_qei0(void)
{
    CLK_DisableModuleClock(QEI0_MODULE);

    return;
}

void nutool_modclkcfg_init_qei1(void)
{
    CLK_EnableModuleClock(QEI1_MODULE);

    return;
}

void nutool_modclkcfg_deinit_qei1(void)
{
    CLK_DisableModuleClock(QEI1_MODULE);

    return;
}

void nutool_modclkcfg_init_qspi0(void)
{
    CLK_EnableModuleClock(QSPI0_MODULE);
    CLK_SetModuleClock(QSPI0_MODULE, CLK_CLKSEL2_QSPI0SEL_PCLK0, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_qspi0(void)
{
    CLK_DisableModuleClock(QSPI0_MODULE);

    return;
}

void nutool_modclkcfg_init_rtc(void)
{
    CLK_EnableModuleClock(RTC_MODULE);
    RTC->LXTCTL = RTC->LXTCTL & ~RTC_LXTCTL_RTCCKSEL_Msk;

    return;
}

void nutool_modclkcfg_deinit_rtc(void)
{
    CLK_DisableModuleClock(RTC_MODULE);

    return;
}

void nutool_modclkcfg_init_sc0(void)
{
    CLK_EnableModuleClock(SC0_MODULE);
    CLK_SetModuleClock(SC0_MODULE, CLK_CLKSEL3_SC0SEL_HXT, CLK_CLKDIV1_SC0(1));

    return;
}

void nutool_modclkcfg_deinit_sc0(void)
{
    CLK_DisableModuleClock(SC0_MODULE);

    return;
}

void nutool_modclkcfg_init_sc1(void)
{
    CLK_EnableModuleClock(SC1_MODULE);
    CLK_SetModuleClock(SC1_MODULE, CLK_CLKSEL3_SC1SEL_HXT, CLK_CLKDIV1_SC1(1));

    return;
}

void nutool_modclkcfg_deinit_sc1(void)
{
    CLK_DisableModuleClock(SC1_MODULE);

    return;
}

void nutool_modclkcfg_init_sc2(void)
{
    CLK_EnableModuleClock(SC2_MODULE);
    CLK_SetModuleClock(SC2_MODULE, CLK_CLKSEL3_SC2SEL_HXT, CLK_CLKDIV1_SC2(1));

    return;
}

void nutool_modclkcfg_deinit_sc2(void)
{
    CLK_DisableModuleClock(SC2_MODULE);

    return;
}

void nutool_modclkcfg_init_sdh0(void)
{
    CLK_EnableModuleClock(SDH0_MODULE);
    CLK_SetModuleClock(SDH0_MODULE, CLK_CLKSEL0_SDH0SEL_HCLK, CLK_CLKDIV0_SDH0(1));

    return;
}

void nutool_modclkcfg_deinit_sdh0(void)
{
    CLK_DisableModuleClock(SDH0_MODULE);

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

void nutool_modclkcfg_init_spi1(void)
{
    CLK_EnableModuleClock(SPI1_MODULE);
    CLK_SetModuleClock(SPI1_MODULE, CLK_CLKSEL2_SPI1SEL_PCLK0, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_spi1(void)
{
    CLK_DisableModuleClock(SPI1_MODULE);

    return;
}

void nutool_modclkcfg_init_spi2(void)
{
    CLK_EnableModuleClock(SPI2_MODULE);
    CLK_SetModuleClock(SPI2_MODULE, CLK_CLKSEL2_SPI2SEL_PCLK1, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_spi2(void)
{
    CLK_DisableModuleClock(SPI2_MODULE);

    return;
}

void nutool_modclkcfg_init_spi3(void)
{
    CLK_EnableModuleClock(SPI3_MODULE);
    CLK_SetModuleClock(SPI3_MODULE, CLK_CLKSEL2_SPI3SEL_PCLK0, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_spi3(void)
{
    CLK_DisableModuleClock(SPI3_MODULE);

    return;
}

void nutool_modclkcfg_init_sram0(void)
{
    CLK_EnableModuleClock(SRAM0_MODULE);

    return;
}

void nutool_modclkcfg_deinit_sram0(void)
{
    CLK_DisableModuleClock(SRAM0_MODULE);

    return;
}

void nutool_modclkcfg_init_sram1(void)
{
    CLK_EnableModuleClock(SRAM1_MODULE);

    return;
}

void nutool_modclkcfg_deinit_sram1(void)
{
    CLK_DisableModuleClock(SRAM1_MODULE);

    return;
}

void nutool_modclkcfg_init_sram2(void)
{
    CLK_EnableModuleClock(SRAM2_MODULE);

    return;
}

void nutool_modclkcfg_deinit_sram2(void)
{
    CLK_DisableModuleClock(SRAM2_MODULE);

    return;
}

void nutool_modclkcfg_init_systick(void)
{
    CLK_EnableSysTick(CLK_CLKSEL0_STCLKSEL_HCLK, 0);

    return;
}

void nutool_modclkcfg_deinit_systick(void)
{
    CLK_DisableSysTick();

    return;
}

void nutool_modclkcfg_init_tamper(void)
{
    CLK_EnableModuleClock(TAMPER_MODULE);

    return;
}

void nutool_modclkcfg_deinit_tamper(void)
{
    CLK_DisableModuleClock(TAMPER_MODULE);

    return;
}

void nutool_modclkcfg_init_tmr0(void)
{
    CLK_EnableModuleClock(TMR0_MODULE);
    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_HXT, MODULE_NoMsk);

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
    CLK_SetModuleClock(TMR1_MODULE, CLK_CLKSEL1_TMR1SEL_HXT, MODULE_NoMsk);

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
    CLK_SetModuleClock(TMR2_MODULE, CLK_CLKSEL1_TMR2SEL_HXT, MODULE_NoMsk);

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
    CLK_SetModuleClock(TMR3_MODULE, CLK_CLKSEL1_TMR3SEL_HXT, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_tmr3(void)
{
    CLK_DisableModuleClock(TMR3_MODULE);

    return;
}

void nutool_modclkcfg_init_tmr4(void)
{
    CLK_EnableModuleClock(TMR4_MODULE);
    CLK_SetModuleClock(TMR4_MODULE, CLK_CLKSEL3_TMR4SEL_HXT, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_tmr4(void)
{
    CLK_DisableModuleClock(TMR4_MODULE);

    return;
}

void nutool_modclkcfg_init_tmr5(void)
{
    CLK_EnableModuleClock(TMR5_MODULE);
    CLK_SetModuleClock(TMR5_MODULE, CLK_CLKSEL3_TMR5SEL_HXT, MODULE_NoMsk);

    return;
}

void nutool_modclkcfg_deinit_tmr5(void)
{
    CLK_DisableModuleClock(TMR5_MODULE);

    return;
}

void nutool_modclkcfg_init_trace(void)
{
    CLK_EnableModuleClock(TRACE_MODULE);

    return;
}

void nutool_modclkcfg_deinit_trace(void)
{
    CLK_DisableModuleClock(TRACE_MODULE);

    return;
}

void nutool_modclkcfg_init_trng(void)
{
    CLK_EnableModuleClock(TRNG_MODULE);

    return;
}

void nutool_modclkcfg_deinit_trng(void)
{
    CLK_DisableModuleClock(TRNG_MODULE);

    return;
}

void nutool_modclkcfg_init_uart0(void)
{
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL2_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

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
    CLK_SetModuleClock(UART1_MODULE, CLK_CLKSEL2_UART1SEL_HXT, CLK_CLKDIV0_UART1(1));

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
    CLK_SetModuleClock(UART2_MODULE, CLK_CLKSEL2_UART2SEL_HXT, CLK_CLKDIV4_UART2(1));

    return;
}

void nutool_modclkcfg_deinit_uart2(void)
{
    CLK_DisableModuleClock(UART2_MODULE);

    return;
}

void nutool_modclkcfg_init_uart3(void)
{
    CLK_EnableModuleClock(UART3_MODULE);
    CLK_SetModuleClock(UART3_MODULE, CLK_CLKSEL2_UART3SEL_HXT, CLK_CLKDIV4_UART3(1));

    return;
}

void nutool_modclkcfg_deinit_uart3(void)
{
    CLK_DisableModuleClock(UART3_MODULE);

    return;
}

void nutool_modclkcfg_init_uart4(void)
{
    CLK_EnableModuleClock(UART4_MODULE);
    CLK_SetModuleClock(UART4_MODULE, CLK_CLKSEL3_UART4SEL_HXT, CLK_CLKDIV4_UART4(1));

    return;
}

void nutool_modclkcfg_deinit_uart4(void)
{
    CLK_DisableModuleClock(UART4_MODULE);

    return;
}

void nutool_modclkcfg_init_uart5(void)
{
    CLK_EnableModuleClock(UART5_MODULE);
    CLK_SetModuleClock(UART5_MODULE, CLK_CLKSEL3_UART5SEL_HXT, CLK_CLKDIV4_UART5(1));

    return;
}

void nutool_modclkcfg_deinit_uart5(void)
{
    CLK_DisableModuleClock(UART5_MODULE);

    return;
}

void nutool_modclkcfg_init_usbd(void)
{
    CLK_EnableModuleClock(USBD_MODULE);
    CLK_SetModuleClock(USBD_MODULE, CLK_CLKSEL0_USBSEL_HIRC48, CLK_CLKDIV0_USB(1));

    return;
}

void nutool_modclkcfg_deinit_usbd(void)
{
    CLK_DisableModuleClock(USBD_MODULE);

    return;
}

void nutool_modclkcfg_init_usbh(void)
{
    CLK_EnableModuleClock(USBH_MODULE);
    CLK_SetModuleClock(USBH_MODULE, CLK_CLKSEL0_USBSEL_HIRC48, CLK_CLKDIV0_USB(1));

    return;
}

void nutool_modclkcfg_deinit_usbh(void)
{
    CLK_DisableModuleClock(USBH_MODULE);

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

void nutool_modclkcfg_init_usci1(void)
{
    CLK_EnableModuleClock(USCI1_MODULE);

    return;
}

void nutool_modclkcfg_deinit_usci1(void)
{
    CLK_DisableModuleClock(USCI1_MODULE);

    return;
}

void nutool_modclkcfg_init_wdt(void)
{
    CLK_EnableModuleClock(WDT_MODULE);
    CLK_SetModuleClock(WDT_MODULE, CLK_CLKSEL1_WDTSEL_LXT, MODULE_NoMsk);

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

void nutool_modclkcfg_init_base(void)
{
    /* LXT source from external LXT */
    CLK_EnableModuleClock(RTC_MODULE);
    RTC->LXTCTL &= ~(RTC_LXTCTL_LIRC32KEN_Msk|RTC_LXTCTL_C32KSEL_Msk);
    CLK_DisableModuleClock(RTC_MODULE);

    /* Enable clock source */
    CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk|CLK_PWRCTL_LXTEN_Msk|CLK_PWRCTL_HXTEN_Msk|CLK_PWRCTL_HIRC48EN_Msk|CLK_PWRCTL_MIRCEN_Msk);

    /* Waiting for clock source ready */
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk|CLK_STATUS_LXTSTB_Msk|CLK_STATUS_HXTSTB_Msk|CLK_STATUS_HIRC48STB_Msk|CLK_STATUS_MIRCSTB_Msk);

    /* Disable PLL first to avoid unstable when setting PLL */
    CLK_DisablePLL();

    /* Set PLL frequency */
    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_96MHZ);

    /* Waiting for PLL ready */
    CLK_WaitClockReady(CLK_STATUS_PLLSTB_Msk);

    /* If the defines do not exist in your project, please refer to the related clk.h in the Header folder appended to the tool package. */
    /* Set HCLK clock */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_PLL, CLK_CLKDIV0_HCLK(1));

    return;
}

void nutool_modclkcfg_init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/
    //RTC->LXTCTL = (RTC->LXTCTL & ~(0x000000C1UL)) | 0x0000000EUL;
    //CLK->PWRCTL = (CLK->PWRCTL & ~(0x0034000FUL)) | 0x00240007UL;
    //CLK->PLLCTL = (CLK->PLLCTL & ~(0x000BFFFFUL)) | 0x00000206UL;
    //CLK->CLKDIV0 = (CLK->CLKDIV0 & ~(0xFFFFFFFFUL)) | 0x00000010UL;
    //CLK->CLKDIV1 = (CLK->CLKDIV1 & ~(0x00FFFFFFUL)) | 0x00000000UL;
    //CLK->CLKDIV4 = (CLK->CLKDIV4 & ~(0x0000FFFFUL)) | 0x00000000UL;
    //CLK->PCLKDIV = (CLK->PCLKDIV & ~(0x00000077UL)) | 0x00000000UL;
    //CLK->CLKSEL0 = (CLK->CLKSEL0 & ~(0x0030013FUL)) | 0x0020011AUL;
    //CLK->CLKSEL1 = (CLK->CLKSEL1 & ~(0xF07777FFUL)) | 0xB000009DUL;
    //CLK->CLKSEL2 = (CLK->CLKSEL2 & ~(0x77773FFFUL)) | 0x00002BABUL;
    //CLK->CLKSEL3 = (CLK->CLKSEL3 & ~(0x7703773FUL)) | 0x00020000UL;
    //CLK->AHBCLK = (CLK->AHBCLK & ~(0xFF71F0DFUL)) | 0xFFFFFFFFUL;
    //CLK->APBCLK0 = (CLK->APBCLK0 & ~(0xBD7FF7FFUL)) | 0xFFFFFFFFUL;
    //CLK->APBCLK1 = (CLK->APBCLK1 & ~(0x1FCF1377UL)) | 0xFFFFFFFFUL;
    //CLK->CLKOCTL = (CLK->CLKOCTL & ~(0x0000007FUL)) | 0x00000000UL;
    //SysTick->CTRL = (SysTick->CTRL & ~(0x00000005UL)) | 0x00000005UL;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable base clock */
    nutool_modclkcfg_init_base();

    /* Enable module clock and set clock source */
    nutool_modclkcfg_init_sram0();
    nutool_modclkcfg_init_sram1();
    nutool_modclkcfg_init_sram2();
    nutool_modclkcfg_init_systick();

#if defined(BSP_USING_ACMP01)
    nutool_modclkcfg_init_acmp01();
#endif
#if defined(BSP_USING_BPWM0)
    nutool_modclkcfg_init_bpwm0();
#endif
#if defined(BSP_USING_BPWM1)
    nutool_modclkcfg_init_bpwm1();
#endif
#if defined(BSP_USING_CAN0)
    nutool_modclkcfg_init_can0();
#endif
#if defined(BSP_USING_CRC)
    nutool_modclkcfg_init_crc();
#endif
#if defined(BSP_USING_CRYPTO)
    nutool_modclkcfg_init_crpt();
#endif
#if defined(BSP_USING_DAC)
    nutool_modclkcfg_init_dac();
#endif
#if defined(BSP_USING_EADC)
    nutool_modclkcfg_init_eadc();
#endif
#if defined(BSP_USING_EBI)
    nutool_modclkcfg_init_ebi();
#endif
#if defined(BSP_USING_ECAP0)
    nutool_modclkcfg_init_ecap0();
#endif
#if defined(BSP_USING_ECAP1)
    nutool_modclkcfg_init_ecap1();
#endif
#if defined(BSP_USING_EPWM0)
    nutool_modclkcfg_init_epwm0();
#endif
#if defined(BSP_USING_EPWM1)
    nutool_modclkcfg_init_epwm1();
#endif
    /*nutool_modclkcfg_init_ewdt();*/
    /*nutool_modclkcfg_init_ewwdt();*/
    /*nutool_modclkcfg_init_exst();*/
#if defined(BSP_USING_FMC)
    nutool_modclkcfg_init_fmcidle();
    nutool_modclkcfg_init_isp();
#endif
#if defined(BSP_USING_GPIO)
    nutool_modclkcfg_init_gpa();
    nutool_modclkcfg_init_gpb();
    nutool_modclkcfg_init_gpc();
    nutool_modclkcfg_init_gpd();
    nutool_modclkcfg_init_gpe();
    nutool_modclkcfg_init_gpf();
    nutool_modclkcfg_init_gpg();
    nutool_modclkcfg_init_gph();
#endif
#if defined(BSP_USING_I2C0)
    nutool_modclkcfg_init_i2c0();
#endif
#if defined(BSP_USING_I2C1)
    nutool_modclkcfg_init_i2c1();
#endif
#if defined(BSP_USING_I2C2)
    nutool_modclkcfg_init_i2c2();
#endif
#if defined(BSP_USING_I2S)
    nutool_modclkcfg_init_i2s0();
#endif
    /*nutool_modclkcfg_init_ks();*/
#if defined(BSP_USING_SLCD)
    nutool_modclkcfg_init_lcd();
    nutool_modclkcfg_init_lcdcp();
#endif
#if defined(BSP_USING_OTG) || defined(BSP_USING_USBH)
    nutool_modclkcfg_init_otg();
#endif
#if defined(BSP_USING_PDMA)
    nutool_modclkcfg_init_pdma0();
    nutool_modclkcfg_init_pdma1();
#endif
#if defined(BSP_USING_QEI0)
    nutool_modclkcfg_init_qei0();
#endif
#if defined(BSP_USING_QEI1)
    nutool_modclkcfg_init_qei1();
#endif
#if defined(BSP_USING_QSPI0)
    nutool_modclkcfg_init_qspi0();
#endif
#if defined(BSP_USING_RTC)
    nutool_modclkcfg_init_rtc();
#endif
#if defined(BSP_USING_SCUART0)
    nutool_modclkcfg_init_sc0();
#endif
#if defined(BSP_USING_SCUART1)
    nutool_modclkcfg_init_sc1();
#endif
#if defined(BSP_USING_SCUART2)
    nutool_modclkcfg_init_sc2();
#endif
#if defined(BSP_USING_SDH0)
    nutool_modclkcfg_init_sdh0();
#endif
#if defined(BSP_USING_SPI0) || defined(BSP_USING_SPII2S0)
    nutool_modclkcfg_init_spi0();
#endif
#if defined(BSP_USING_SPI1) || defined(BSP_USING_SPII2S1)
    nutool_modclkcfg_init_spi1();
#endif
#if defined(BSP_USING_SPI2) || defined(BSP_USING_SPII2S2)
    nutool_modclkcfg_init_spi2();
#endif
#if defined(BSP_USING_SPI3) || defined(BSP_USING_SPII2S3)
    nutool_modclkcfg_init_spi3();
#endif

    /*nutool_modclkcfg_init_tamper();*/
#if defined(BSP_USING_TMR0)
    nutool_modclkcfg_init_tmr0();
#endif
#if defined(BSP_USING_TMR1)
    nutool_modclkcfg_init_tmr1();
#endif
#if defined(BSP_USING_TMR2)
    nutool_modclkcfg_init_tmr2();
#endif
#if defined(BSP_USING_TMR3)
    nutool_modclkcfg_init_tmr3();
#endif
#if defined(BSP_USING_TMR4)
    nutool_modclkcfg_init_tmr4();
#endif
#if defined(BSP_USING_TMR5)
    nutool_modclkcfg_init_tmr5();
#endif
#if defined(BSP_USING_TRNG)
    nutool_modclkcfg_init_trng();
#endif
#if defined(BSP_USING_UART0)
    nutool_modclkcfg_init_uart0();
#endif
#if defined(BSP_USING_UART1)
    nutool_modclkcfg_init_uart1();
#endif
#if defined(BSP_USING_UART2)
    nutool_modclkcfg_init_uart2();
#endif
#if defined(BSP_USING_UART3)
    nutool_modclkcfg_init_uart3();
#endif
#if defined(BSP_USING_UART4)
    nutool_modclkcfg_init_uart4();
#endif
#if defined(BSP_USING_UART5)
    nutool_modclkcfg_init_uart5();
#endif
#if defined(BSP_USING_USBD) || defined(BSP_USING_USBH)
    nutool_modclkcfg_init_usbd();
#endif
#if defined(BSP_USING_USBH)
    nutool_modclkcfg_init_usbh();
#endif
#if defined(BSP_USING_USCI0)
    nutool_modclkcfg_init_usci0();
#endif
#if defined(BSP_USING_USCI1)
    nutool_modclkcfg_init_usci1();
#endif
#if defined(BSP_USING_WDT)
    nutool_modclkcfg_init_wdt();
#endif
#if defined(BSP_USING_WWDT)
    nutool_modclkcfg_init_wwdt();
#endif

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

    /* Lock protected registers */
    SYS_LockReg();

    return;
}

/*** (C) COPYRIGHT 2013-2020 Nuvoton Technology Corp. ***/
