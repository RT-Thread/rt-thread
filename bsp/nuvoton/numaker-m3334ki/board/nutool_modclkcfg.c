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

#include "NuMicro.h"
#include "rtconfig.h"

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

void nutool_modclkcfg_init_st(void)
{
    CLK_EnableModuleClock(ST_MODULE);
    return;
}
void nutool_modclkcfg_deinit_st(void)
{
    CLK_DisableModuleClock(ST_MODULE);
    return;
}

void nutool_modclkcfg_init_sdh0(void)
{
    /* Select IP clock source */
    CLK_SetModuleClock(SDH0_MODULE, CLK_CLKSEL0_SDH0SEL_PLL_DIV2, CLK_CLKDIV0_SDH0(5));

    CLK_EnableModuleClock(SDH0_MODULE);
    return;
}
void nutool_modclkcfg_deinit_sdh0(void)
{
    CLK_DisableModuleClock(SDH0_MODULE);
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

void nutool_modclkcfg_init_canfd0(void)
{
    CLK_EnableModuleClock(CANFD0_MODULE);
    return;
}
void nutool_modclkcfg_deinit_canfd0(void)
{
    CLK_DisableModuleClock(CANFD0_MODULE);
    return;
}

void nutool_modclkcfg_init_canfd1(void)
{
    CLK_EnableModuleClock(CANFD1_MODULE);
    return;
}
void nutool_modclkcfg_deinit_canfd1(void)
{
    CLK_DisableModuleClock(CANFD1_MODULE);
    return;
}

void nutool_modclkcfg_init_hsusbd(void)
{
    CLK_EnableModuleClock(HSUSBD_MODULE);
    return;
}
void nutool_modclkcfg_deinit_hsusbd(void)
{
    CLK_DisableModuleClock(HSUSBD_MODULE);
    return;
}

void nutool_modclkcfg_init_pdci(void)
{
    CLK_EnableModuleClock(PDCI_MODULE);
    return;
}
void nutool_modclkcfg_deinit_pdci(void)
{
    CLK_DisableModuleClock(PDCI_MODULE);
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

void nutool_modclkcfg_init_usbh(void)
{
    CLK_EnableModuleClock(USBH_MODULE);

    return;
}
void nutool_modclkcfg_deinit_usbh(void)
{
    CLK_DisableModuleClock(USBH_MODULE);

    return;
}

void nutool_modclkcfg_init_canram0(void)
{
    CLK_EnableModuleClock(CANRAM0_MODULE);
    return;
}
void nutool_modclkcfg_deinit_canram0(void)
{
    CLK_DisableModuleClock(CANRAM0_MODULE);
    return;
}

void nutool_modclkcfg_init_canram1(void)
{
    CLK_EnableModuleClock(CANRAM1_MODULE);
    return;
}
void nutool_modclkcfg_deinit_canram1(void)
{
    CLK_DisableModuleClock(CANRAM1_MODULE);
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

void nutool_modclkcfg_init_wdt0(void)
{
    CLK_EnableModuleClock(WDT0_MODULE);
    CLK_SetModuleClock(WDT0_MODULE, CLK_CLKSEL1_WDT0SEL_HCLK_DIV2048, MODULE_NoMsk);
    return;
}
void nutool_modclkcfg_deinit_wdt0(void)
{
    CLK_DisableModuleClock(WDT0_MODULE);
    return;
}

void nutool_modclkcfg_init_wdt1(void)
{
    CLK_EnableModuleClock(WDT1_MODULE);
    CLK_SetModuleClock(WDT1_MODULE, CLK_CLKSEL1_WDT1SEL_HCLK_DIV2048, MODULE_NoMsk);
    return;
}
void nutool_modclkcfg_deinit_wdt1(void)
{
    CLK_DisableModuleClock(WDT1_MODULE);
    return;
}

void nutool_modclkcfg_init_wwdt0(void)
{
    CLK_EnableModuleClock(WWDT0_MODULE);
    return;
}
void nutool_modclkcfg_deinit_wwdt0(void)
{
    CLK_DisableModuleClock(WWDT0_MODULE);
    return;
}

void nutool_modclkcfg_init_wwdt1(void)
{
    CLK_EnableModuleClock(WWDT1_MODULE);
    return;
}
void nutool_modclkcfg_deinit_wwdt1(void)
{
    CLK_DisableModuleClock(WWDT1_MODULE);
    return;
}

void nutool_modclkcfg_init_rtc(void)
{
    CLK_EnableModuleClock(RTC_MODULE);

    /* RTC clock source select LXT */
    CLK_SetModuleClock(RTC_MODULE, RTC_LXTCTL_RTCCKSEL_LXT, 0);

    /* Set LXT as RTC clock source */
    RTC_SetClockSource(RTC_CLOCK_SOURCE_LXT);

    return;
}
void nutool_modclkcfg_deinit_rtc(void)
{
    CLK_DisableModuleClock(RTC_MODULE);
    return;
}

void nutool_modclkcfg_init_tmr0(void)
{
    CLK_EnableModuleClock(TMR0_MODULE);

#if defined(BSP_USING_TPWM0)
    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_PCLK0, MODULE_NoMsk);
#else
    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_HIRC, MODULE_NoMsk);
#endif

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

#if defined(BSP_USING_TPWM1)
    CLK_SetModuleClock(TMR1_MODULE, CLK_CLKSEL1_TMR1SEL_PCLK0, MODULE_NoMsk);
#else
    CLK_SetModuleClock(TMR1_MODULE, CLK_CLKSEL1_TMR1SEL_HIRC, MODULE_NoMsk);
#endif

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

#if defined(BSP_USING_TPWM2)
    CLK_SetModuleClock(TMR2_MODULE, CLK_CLKSEL1_TMR2SEL_PCLK1, MODULE_NoMsk);
#else
    CLK_SetModuleClock(TMR2_MODULE, CLK_CLKSEL1_TMR2SEL_HIRC, MODULE_NoMsk);
#endif

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

#if defined(BSP_USING_TPWM3)
    CLK_SetModuleClock(TMR3_MODULE, CLK_CLKSEL1_TMR3SEL_PCLK1, MODULE_NoMsk);
#else
    CLK_SetModuleClock(TMR3_MODULE, CLK_CLKSEL1_TMR3SEL_HIRC, MODULE_NoMsk);
#endif

    return;
}

void nutool_modclkcfg_deinit_tmr3(void)
{
    CLK_DisableModuleClock(TMR3_MODULE);

    return;
}

void nutool_modclkcfg_init_clko(void)
{
    CLK_EnableModuleClock(CLKO_MODULE);
    return;
}
void nutool_modclkcfg_deinit_clko(void)
{
    CLK_DisableModuleClock(CLKO_MODULE);
    return;
}

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

void nutool_modclkcfg_init_i3c0(void)
{
    CLK_EnableModuleClock(I3C0_MODULE);
    return;
}
void nutool_modclkcfg_deinit_i3c0(void)
{
    CLK_DisableModuleClock(I3C0_MODULE);
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


void nutool_modclkcfg_init_uart0(void)
{
    CLK_EnableModuleClock(UART0_MODULE);

    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HIRC, CLK_CLKDIV0_UART0(1));

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
    CLK_SetModuleClock(UART1_MODULE, CLK_CLKSEL1_UART1SEL_HIRC, CLK_CLKDIV0_UART1(1));

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
    CLK_SetModuleClock(UART2_MODULE, CLK_CLKSEL3_UART2SEL_HIRC, CLK_CLKDIV1_UART2(1));

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
    CLK_SetModuleClock(UART3_MODULE, CLK_CLKSEL3_UART3SEL_HIRC, CLK_CLKDIV1_UART3(1));

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
    CLK_SetModuleClock(UART4_MODULE, CLK_CLKSEL3_UART4SEL_HIRC, CLK_CLKDIV1_UART4(1));

    return;
}

void nutool_modclkcfg_deinit_uart4(void)
{
    CLK_DisableModuleClock(UART4_MODULE);

    return;
}

void nutool_modclkcfg_init_eadc0(void)
{
    CLK_EnableModuleClock(EADC0_MODULE);
    CLK_SetModuleClock(EADC0_MODULE, CLK_CLKSEL0_EADC0SEL_PLL_DIV2, CLK_CLKDIV0_EADC0(8));

    return;
}
void nutool_modclkcfg_deinit_eadc0(void)
{
    CLK_DisableModuleClock(EADC0_MODULE);
    return;
}

void nutool_modclkcfg_init_i2s0(void)
{
    CLK_EnableModuleClock(I2S0_MODULE);
    CLK_SetModuleClock(I2S0_MODULE, CLK_CLKSEL3_I2S0SEL_HIRC, 0);

    return;
}
void nutool_modclkcfg_deinit_i2s0(void)
{
    CLK_DisableModuleClock(I2S0_MODULE);
    return;
}

void nutool_modclkcfg_init_hsotg(void)
{
    CLK_EnableModuleClock(HSOTG_MODULE);
    return;
}
void nutool_modclkcfg_deinit_hsotg(void)
{
    CLK_DisableModuleClock(HSOTG_MODULE);
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

void nutool_modclkcfg_init_bpwm2(void)
{
    CLK_EnableModuleClock(BPWM2_MODULE);
    CLK_SetModuleClock(BPWM2_MODULE, CLK_CLKSEL2_BPWM2SEL_PCLK0, MODULE_NoMsk);

    return;
}
void nutool_modclkcfg_deinit_bpwm2(void)
{
    CLK_DisableModuleClock(BPWM2_MODULE);
    return;
}

void nutool_modclkcfg_init_bpwm3(void)
{
    CLK_EnableModuleClock(BPWM3_MODULE);
    CLK_SetModuleClock(BPWM3_MODULE, CLK_CLKSEL2_BPWM3SEL_PCLK1, MODULE_NoMsk);

    return;
}
void nutool_modclkcfg_deinit_bpwm3(void)
{
    CLK_DisableModuleClock(BPWM3_MODULE);
    return;
}

void nutool_modclkcfg_init_bpwm4(void)
{
    CLK_EnableModuleClock(BPWM4_MODULE);
    CLK_SetModuleClock(BPWM4_MODULE, CLK_CLKSEL2_BPWM4SEL_PCLK0, MODULE_NoMsk);

    return;
}
void nutool_modclkcfg_deinit_bpwm4(void)
{
    CLK_DisableModuleClock(BPWM4_MODULE);
    return;
}

void nutool_modclkcfg_init_bpwm5(void)
{
    CLK_EnableModuleClock(BPWM5_MODULE);
    CLK_SetModuleClock(BPWM5_MODULE, CLK_CLKSEL2_BPWM5SEL_PCLK1, MODULE_NoMsk);

    return;
}
void nutool_modclkcfg_deinit_bpwm5(void)
{
    CLK_DisableModuleClock(BPWM5_MODULE);
    return;
}

void nutool_modclkcfg_init_eqei0(void)
{
    CLK_EnableModuleClock(EQEI0_MODULE);
    return;
}
void nutool_modclkcfg_deinit_eqei0(void)
{
    CLK_DisableModuleClock(EQEI0_MODULE);
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

void nutool_modclkcfg_init_llsi0(void)
{
    CLK_EnableModuleClock(LLSI0_MODULE);
    return;
}
void nutool_modclkcfg_deinit_llsi0(void)
{
    CLK_DisableModuleClock(LLSI0_MODULE);
    return;
}

void nutool_modclkcfg_init_llsi1(void)
{
    CLK_EnableModuleClock(LLSI1_MODULE);
    return;
}
void nutool_modclkcfg_deinit_llsi1(void)
{
    CLK_DisableModuleClock(LLSI1_MODULE);
    return;
}

void nutool_modclkcfg_init_llsi2(void)
{
    CLK_EnableModuleClock(LLSI2_MODULE);
    return;
}
void nutool_modclkcfg_deinit_llsi2(void)
{
    CLK_DisableModuleClock(LLSI2_MODULE);
    return;
}

void nutool_modclkcfg_init_llsi3(void)
{
    CLK_EnableModuleClock(LLSI3_MODULE);
    return;
}
void nutool_modclkcfg_deinit_llsi3(void)
{
    CLK_DisableModuleClock(LLSI3_MODULE);
    return;
}

void nutool_modclkcfg_init_llsi4(void)
{
    CLK_EnableModuleClock(LLSI4_MODULE);
    return;
}
void nutool_modclkcfg_deinit_llsi4(void)
{
    CLK_DisableModuleClock(LLSI4_MODULE);
    return;
}

void nutool_modclkcfg_init_llsi5(void)
{
    CLK_EnableModuleClock(LLSI5_MODULE);
    return;
}
void nutool_modclkcfg_deinit_llsi5(void)
{
    CLK_DisableModuleClock(LLSI5_MODULE);
    return;
}

void nutool_modclkcfg_init_llsi6(void)
{
    CLK_EnableModuleClock(LLSI6_MODULE);
    return;
}
void nutool_modclkcfg_deinit_llsi6(void)
{
    CLK_DisableModuleClock(LLSI6_MODULE);
    return;
}

void nutool_modclkcfg_init_llsi7(void)
{
    CLK_EnableModuleClock(LLSI7_MODULE);
    return;
}
void nutool_modclkcfg_deinit_llsi7(void)
{
    CLK_DisableModuleClock(LLSI7_MODULE);
    return;
}

void nutool_modclkcfg_init_llsi8(void)
{
    CLK_EnableModuleClock(LLSI8_MODULE);
    return;
}
void nutool_modclkcfg_deinit_llsi8(void)
{
    CLK_DisableModuleClock(LLSI8_MODULE);
    return;
}

void nutool_modclkcfg_init_llsi9(void)
{
    CLK_EnableModuleClock(LLSI9_MODULE);
    return;
}
void nutool_modclkcfg_deinit_llsi9(void)
{
    CLK_DisableModuleClock(LLSI9_MODULE);
    return;
}

void nutool_modclkcfg_init_ellsi0(void)
{
    CLK_EnableModuleClock(ELLSI0_MODULE);
    return;
}
void nutool_modclkcfg_deinit_ellsi0(void)
{
    CLK_DisableModuleClock(ELLSI0_MODULE);
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

void nutool_modclkcfg_init_base(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* HXT filter select */
    outpw(0x400002D4, 0x00FF8800);

#if defined(RT_USING_PM) && defined(BSP_USING_CLK)
    /* Release I/O hold status to resume normal I/O operation. */
    /* Note: This option must be set; otherwise, the HXT may not stabilize properly. */
    CLK->IOPDCTL = 1;
#endif

    /* Enable HIRC/HXT/LXT/LIRC clocks */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk | CLK_PWRCTL_LXTEN_Msk | CLK_PWRCTL_LIRCEN_Msk | CLK_PWRCTL_HIRCEN_Msk);

    /* Wait for HIRC/HXT/LXT/LIRC clocks ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk | CLK_STATUS_LXTSTB_Msk | CLK_STATUS_LIRCSTB_Msk | CLK_STATUS_HIRCSTB_Msk);

    /* Set PLL to 180MHz */
    CLK_SetCoreClock(__HSI);

    /* Set PCLK-related clock */
    CLK->PCLKDIV = (CLK_PCLKDIV_PCLK0DIV2 | CLK_PCLKDIV_PCLK1DIV2);

    /* Enable all GPIO clock */
    CLK->AHBCLK0 |= CLK_AHBCLK0_GPACKEN_Msk | CLK_AHBCLK0_GPBCKEN_Msk | CLK_AHBCLK0_GPCCKEN_Msk | CLK_AHBCLK0_GPDCKEN_Msk |
                    CLK_AHBCLK0_GPECKEN_Msk | CLK_AHBCLK0_GPFCKEN_Msk | CLK_AHBCLK0_GPGCKEN_Msk | CLK_AHBCLK0_GPHCKEN_Msk;

    SystemCoreClockUpdate();

    return;
}

void Reset_Handler_PreInit(void)
{
    /* Enable base clock */
    nutool_modclkcfg_init_base();
}

void nutool_modclkcfg_init(void)
{
#if defined(BSP_USING_PDMA0)
    nutool_modclkcfg_init_pdma0();
#endif

#if defined(BSP_USING_ISP)
    nutool_modclkcfg_init_isp();
#endif

#if defined(BSP_USING_EBI)
    nutool_modclkcfg_init_ebi();
#endif

#if defined(BSP_USING_ST)
    nutool_modclkcfg_init_st();
#endif

#if defined(BSP_USING_SDH0)
    nutool_modclkcfg_init_sdh0();
#endif

#if defined(BSP_USING_CRC)
    nutool_modclkcfg_init_crc();
#endif

#if defined(BSP_USING_CANFD0)
    nutool_modclkcfg_init_canfd0();
#endif

#if defined(BSP_USING_CANFD1)
    nutool_modclkcfg_init_canfd1();
#endif

#if defined(BSP_USING_HSUSBD)
    nutool_modclkcfg_init_hsusbd();
#endif

#if defined(BSP_USING_SPB)
    nutool_modclkcfg_init_spb();
#endif

#if defined(BSP_USING_FMCIDLE)
    nutool_modclkcfg_init_fmcidle();
#endif

#if defined(BSP_USING_USBH) || defined(BSP_USING_HSUSBH)
    nutool_modclkcfg_init_usbh();
#endif

#if defined(BSP_USING_CANRAM0)
    nutool_modclkcfg_init_canram0();
#endif

#if defined(BSP_USING_CANRAM1)
    nutool_modclkcfg_init_canram1();
#endif

#if defined(BSP_USING_TRACE)
    nutool_modclkcfg_init_trace();
#endif

#if defined(BSP_USING_WDT0)
    nutool_modclkcfg_init_wdt0();
#endif

#if defined(BSP_USING_WDT1)
    nutool_modclkcfg_init_wdt1();
#endif

#if defined(BSP_USING_WWDT0)
    nutool_modclkcfg_init_wwdt0();
#endif

#if defined(BSP_USING_WWDT1)
    nutool_modclkcfg_init_wwdt1();
#endif

#if defined(BSP_USING_RTC)
    nutool_modclkcfg_init_rtc();
#endif

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

#if defined(BSP_USING_CLKO)
    nutool_modclkcfg_init_clko();
#endif

#if defined(BSP_USING_ACMP01)
    nutool_modclkcfg_init_acmp01();
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

#if defined(BSP_USING_I3C0)
    nutool_modclkcfg_init_i3c0();
#endif

#if defined(BSP_USING_QSPI0)
    nutool_modclkcfg_init_qspi0();
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

#if defined(BSP_USING_EADC0)
    nutool_modclkcfg_init_eadc0();
#endif

#if defined(BSP_USING_I2S0)
    nutool_modclkcfg_init_i2s0();
#endif

#if defined(BSP_USING_HSOTG)
    nutool_modclkcfg_init_hsotg();
#endif

#if defined(BSP_USING_USCI0)
    nutool_modclkcfg_init_usci0();
#endif

#if defined(BSP_USING_USCI1)
    nutool_modclkcfg_init_usci1();
#endif

#if defined(BSP_USING_EPWM0)
    nutool_modclkcfg_init_epwm0();
#endif

#if defined(BSP_USING_EPWM1)
    nutool_modclkcfg_init_epwm1();
#endif

#if defined(BSP_USING_BPWM0)
    nutool_modclkcfg_init_bpwm0();
#endif

#if defined(BSP_USING_BPWM1)
    nutool_modclkcfg_init_bpwm1();
#endif

#if defined(BSP_USING_EQEI0)
    nutool_modclkcfg_init_eqei0();
#endif

#if defined(BSP_USING_ECAP0)
    nutool_modclkcfg_init_ecap0();
#endif

#if defined(BSP_USING_BPWM2)
    nutool_modclkcfg_init_bpwm2();
#endif

#if defined(BSP_USING_BPWM3)
    nutool_modclkcfg_init_bpwm3();
#endif

#if defined(BSP_USING_BPWM4)
    nutool_modclkcfg_init_bpwm4();
#endif

#if defined(BSP_USING_BPWM5)
    nutool_modclkcfg_init_bpwm5();
#endif

#if defined(BSP_USING_LLSI0)
    nutool_modclkcfg_init_llsi0();
#endif

#if defined(BSP_USING_LLSI1)
    nutool_modclkcfg_init_llsi1();
#endif

#if defined(BSP_USING_LLSI2)
    nutool_modclkcfg_init_llsi2();
#endif

#if defined(BSP_USING_LLSI3)
    nutool_modclkcfg_init_llsi3();
#endif

#if defined(BSP_USING_LLSI4)
    nutool_modclkcfg_init_llsi4();
#endif

#if defined(BSP_USING_LLSI5)
    nutool_modclkcfg_init_llsi5();
#endif

#if defined(BSP_USING_LLSI6)
    nutool_modclkcfg_init_llsi6();
#endif

#if defined(BSP_USING_LLSI7)
    nutool_modclkcfg_init_llsi7();
#endif

#if defined(BSP_USING_LLSI8)
    nutool_modclkcfg_init_llsi8();
#endif

#if defined(BSP_USING_LLSI9)
    nutool_modclkcfg_init_llsi9();
#endif

#if defined(BSP_USING_ELLSI0)
    nutool_modclkcfg_init_ellsi0();
#endif

    /* Update System Core Clock */
    SystemCoreClockUpdate();
}

void nutool_modclkcfg_deinit(void)
{
#if defined(BSP_USING_PDMA0)
    nutool_modclkcfg_deinit_pdma0();
#endif

#if defined(BSP_USING_ISP)
    nutool_modclkcfg_deinit_isp();
#endif

#if defined(BSP_USING_EBI)
    nutool_modclkcfg_deinit_ebi();
#endif

#if defined(BSP_USING_ST)
    nutool_modclkcfg_deinit_st();
#endif

#if defined(BSP_USING_SDH0)
    nutool_modclkcfg_deinit_sdh0();
#endif

#if defined(BSP_USING_CRC)
    nutool_modclkcfg_deinit_crc();
#endif

#if defined(BSP_USING_CANFD0)
    nutool_modclkcfg_deinit_canfd0();
#endif

#if defined(BSP_USING_CANFD1)
    nutool_modclkcfg_deinit_canfd1();
#endif

#if defined(BSP_USING_HSOTG)
    nutool_modclkcfg_init_hsotg();
#endif
#if defined(BSP_USING_HSUSBD)
    nutool_modclkcfg_init_hsusbd();
#endif

#if defined(BSP_USING_SPB)
    nutool_modclkcfg_deinit_spb();
#endif

#if defined(BSP_USING_FMCIDLE)
    nutool_modclkcfg_deinit_fmcidle();
#endif

#if defined(BSP_USING_USBH) || defined(BSP_USING_HSUSBH)
    nutool_modclkcfg_deinit_usbh();
#endif

#if defined(BSP_USING_CANRAM0)
    nutool_modclkcfg_deinit_canram0();
#endif

#if defined(BSP_USING_CANRAM1)
    nutool_modclkcfg_deinit_canram1();
#endif

#if defined(BSP_USING_TRACE)
    nutool_modclkcfg_deinit_trace();
#endif

#if defined(BSP_USING_GPIO)
    nutool_modclkcfg_deinit_gpa();
    nutool_modclkcfg_deinit_gpb();
    nutool_modclkcfg_deinit_gpc();
    nutool_modclkcfg_deinit_gpd();
    nutool_modclkcfg_deinit_gpe();
    nutool_modclkcfg_deinit_gpf();
    nutool_modclkcfg_deinit_gpg();
    nutool_modclkcfg_deinit_gph();
#endif

#if defined(BSP_USING_WDT0)
    nutool_modclkcfg_deinit_wdt0();
#endif

#if defined(BSP_USING_WDT1)
    nutool_modclkcfg_deinit_wdt1();
#endif

#if defined(BSP_USING_WWDT0)
    nutool_modclkcfg_deinit_wwdt0();
#endif

#if defined(BSP_USING_WWDT1)
    nutool_modclkcfg_deinit_wwdt1();
#endif

#if defined(BSP_USING_RTC)
    nutool_modclkcfg_deinit_rtc();
#endif

#if defined(BSP_USING_TMR0)
    nutool_modclkcfg_deinit_tmr0();
#endif

#if defined(BSP_USING_TMR1)
    nutool_modclkcfg_deinit_tmr1();
#endif

#if defined(BSP_USING_TMR2)
    nutool_modclkcfg_deinit_tmr2();
#endif

#if defined(BSP_USING_TMR3)
    nutool_modclkcfg_deinit_tmr3();
#endif

#if defined(BSP_USING_CLKO)
    nutool_modclkcfg_deinit_clko();
#endif

#if defined(BSP_USING_ACMP01)
    nutool_modclkcfg_deinit_acmp01();
#endif

#if defined(BSP_USING_I2C0)
    nutool_modclkcfg_deinit_i2c0();
#endif

#if defined(BSP_USING_I2C1)
    nutool_modclkcfg_deinit_i2c1();
#endif

#if defined(BSP_USING_I2C2)
    nutool_modclkcfg_deinit_i2c2();
#endif

#if defined(BSP_USING_I3C0)
    nutool_modclkcfg_deinit_i3c0();
#endif

#if defined(BSP_USING_QSPI0)
    nutool_modclkcfg_deinit_qspi0();
#endif

#if defined(BSP_USING_SPI0) || defined(BSP_USING_SPII2S0)
    nutool_modclkcfg_deinit_spi0();
#endif

#if defined(BSP_USING_SPI1) || defined(BSP_USING_SPII2S1)
    nutool_modclkcfg_deinit_spi1();
#endif

#if defined(BSP_USING_SPI2) || defined(BSP_USING_SPII2S2)
    nutool_modclkcfg_deinit_spi2();
#endif

#if defined(BSP_USING_UART0)
    nutool_modclkcfg_deinit_uart0();
#endif

#if defined(BSP_USING_UART1)
    nutool_modclkcfg_deinit_uart1();
#endif

#if defined(BSP_USING_UART2)
    nutool_modclkcfg_deinit_uart2();
#endif

#if defined(BSP_USING_UART3)
    nutool_modclkcfg_deinit_uart3();
#endif

#if defined(BSP_USING_UART4)
    nutool_modclkcfg_deinit_uart4();
#endif

#if defined(BSP_USING_EADC0)
    nutool_modclkcfg_deinit_eadc0();
#endif

#if defined(BSP_USING_I2S0)
    nutool_modclkcfg_deinit_i2s0();
#endif

#if defined(BSP_USING_HSOTG)
    nutool_modclkcfg_deinit_hsotg();
#endif

#if defined(BSP_USING_USCI0)
    nutool_modclkcfg_deinit_usci0();
#endif

#if defined(BSP_USING_USCI1)
    nutool_modclkcfg_deinit_usci1();
#endif

#if defined(BSP_USING_EPWM0)
    nutool_modclkcfg_deinit_epwm0();
#endif

#if defined(BSP_USING_EPWM1)
    nutool_modclkcfg_deinit_epwm1();
#endif

#if defined(BSP_USING_BPWM0)
    nutool_modclkcfg_deinit_bpwm0();
#endif

#if defined(BSP_USING_BPWM1)
    nutool_modclkcfg_deinit_bpwm1();
#endif

#if defined(BSP_USING_BPWM2)
    nutool_modclkcfg_deinit_bpwm2();
#endif

#if defined(BSP_USING_BPWM3)
    nutool_modclkcfg_deinit_bpwm3();
#endif

#if defined(BSP_USING_BPWM4)
    nutool_modclkcfg_deinit_bpwm4();
#endif

#if defined(BSP_USING_BPWM5)
    nutool_modclkcfg_deinit_bpwm5();
#endif

#if defined(BSP_USING_EQEI0)
    nutool_modclkcfg_deinit_eqei0();
#endif

#if defined(BSP_USING_ECAP0)
    nutool_modclkcfg_deinit_ecap0();
#endif

#if defined(BSP_USING_LLSI0)
    nutool_modclkcfg_deinit_llsi0();
#endif

#if defined(BSP_USING_LLSI1)
    nutool_modclkcfg_deinit_llsi1();
#endif

#if defined(BSP_USING_LLSI2)
    nutool_modclkcfg_deinit_llsi2();
#endif

#if defined(BSP_USING_LLSI3)
    nutool_modclkcfg_deinit_llsi3();
#endif

#if defined(BSP_USING_LLSI4)
    nutool_modclkcfg_deinit_llsi4();
#endif

#if defined(BSP_USING_LLSI5)
    nutool_modclkcfg_deinit_llsi5();
#endif

#if defined(BSP_USING_LLSI6)
    nutool_modclkcfg_deinit_llsi6();
#endif

#if defined(BSP_USING_LLSI7)
    nutool_modclkcfg_deinit_llsi7();
#endif

#if defined(BSP_USING_LLSI8)
    nutool_modclkcfg_deinit_llsi8();
#endif

#if defined(BSP_USING_LLSI9)
    nutool_modclkcfg_deinit_llsi9();
#endif

#if defined(BSP_USING_ELLSI0)
    nutool_modclkcfg_deinit_ellsi0();
#endif

    /* Update System Core Clock */
    SystemCoreClockUpdate();
}

/*** (C) COPYRIGHT 2013-2020 Nuvoton Technology Corp. ***/
