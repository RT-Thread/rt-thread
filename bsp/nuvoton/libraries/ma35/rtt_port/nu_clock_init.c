/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2021-6-1        Wayne        First version
*
******************************************************************************/

#include "board.h"

static void nu_clock_uart_init(void)
{
#if defined(BSP_USING_UART0)
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL2_UART0SEL_HXT, CLK_CLKDIV1_UART0(1));
#endif
#if defined(BSP_USING_UART1)
    CLK_EnableModuleClock(UART1_MODULE);
    CLK_SetModuleClock(UART1_MODULE, CLK_CLKSEL2_UART1SEL_HXT, CLK_CLKDIV1_UART1(1));
#endif
#if defined(BSP_USING_UART2)
    CLK_EnableModuleClock(UART2_MODULE);
    CLK_SetModuleClock(UART2_MODULE, CLK_CLKSEL2_UART2SEL_HXT, CLK_CLKDIV1_UART2(1));
#endif
#if defined(BSP_USING_UART3)
    CLK_EnableModuleClock(UART3_MODULE);
    CLK_SetModuleClock(UART3_MODULE, CLK_CLKSEL2_UART3SEL_HXT, CLK_CLKDIV1_UART3(1));
#endif
#if defined(BSP_USING_UART4)
    CLK_EnableModuleClock(UART4_MODULE);
    CLK_SetModuleClock(UART4_MODULE, CLK_CLKSEL2_UART4SEL_HXT, CLK_CLKDIV1_UART4(1));
#endif
#if defined(BSP_USING_UART5)
    CLK_EnableModuleClock(UART5_MODULE);
    CLK_SetModuleClock(UART5_MODULE, CLK_CLKSEL2_UART5SEL_HXT, CLK_CLKDIV1_UART5(1));
#endif
#if defined(BSP_USING_UART6)
    CLK_EnableModuleClock(UART6_MODULE);
    CLK_SetModuleClock(UART6_MODULE, CLK_CLKSEL2_UART6SEL_HXT, CLK_CLKDIV1_UART6(1));
#endif
#if defined(BSP_USING_UART7)
    CLK_EnableModuleClock(UART7_MODULE);
    CLK_SetModuleClock(UART7_MODULE, CLK_CLKSEL2_UART7SEL_HXT, CLK_CLKDIV1_UART7(1));
#endif
#if defined(BSP_USING_UART8)
    CLK_EnableModuleClock(UART8_MODULE);
    CLK_SetModuleClock(UART8_MODULE, CLK_CLKSEL3_UART8SEL_HXT, CLK_CLKDIV1_UART8(1));
#endif
#if defined(BSP_USING_UART9)
    CLK_EnableModuleClock(UART9_MODULE);
    CLK_SetModuleClock(UART9_MODULE, CLK_CLKSEL3_UART9SEL_HXT, CLK_CLKDIV2_UART9(1));
#endif
#if defined(BSP_USING_UART10)
    CLK_EnableModuleClock(UART10_MODULE);
    CLK_SetModuleClock(UART10_MODULE, CLK_CLKSEL3_UART10SEL_HXT, CLK_CLKDIV2_UART10(1));
#endif
#if defined(BSP_USING_UART11)
    CLK_EnableModuleClock(UART11_MODULE);
    CLK_SetModuleClock(UART11_MODULE, CLK_CLKSEL3_UART11SEL_HXT, CLK_CLKDIV2_UART11(1));
#endif
#if defined(BSP_USING_UART12)
    CLK_EnableModuleClock(UART12_MODULE);
    CLK_SetModuleClock(UART12_MODULE, CLK_CLKSEL3_UART12SEL_HXT, CLK_CLKDIV3_UART12(1));
#endif
#if defined(BSP_USING_UART13)
    CLK_EnableModuleClock(UART13_MODULE);
    CLK_SetModuleClock(UART13_MODULE, CLK_CLKSEL3_UART13SEL_HXT, CLK_CLKDIV3_UART13(1));
#endif
#if defined(BSP_USING_UART14)
    CLK_EnableModuleClock(UART14_MODULE);
    CLK_SetModuleClock(UART14_MODULE, CLK_CLKSEL3_UART14SEL_HXT, CLK_CLKDIV3_UART14(1));
#endif
#if defined(BSP_USING_UART15)
    CLK_EnableModuleClock(UART15_MODULE);
    CLK_SetModuleClock(UART15_MODULE, CLK_CLKSEL3_UART15SEL_HXT, CLK_CLKDIV3_UART15(1));
#endif
#if defined(BSP_USING_UART16)
    CLK_EnableModuleClock(UART16_MODULE);
    CLK_SetModuleClock(UART16_MODULE, CLK_CLKSEL3_UART16SEL_HXT, CLK_CLKDIV3_UART16(1));
#endif
}

static void nu_clock_pdma_init(void)
{
#if defined(BSP_USING_PDMA0)
    CLK_EnableModuleClock(PDMA0_MODULE);
#endif
#if defined(BSP_USING_PDMA1)
    CLK_EnableModuleClock(PDMA1_MODULE);
#endif
#if defined(BSP_USING_PDMA2)
    CLK_EnableModuleClock(PDMA2_MODULE);
#endif
#if defined(BSP_USING_PDMA3)
    CLK_EnableModuleClock(PDMA3_MODULE);
#endif
}

static void nu_clock_gpio_init(void)
{
#if defined(BSP_USING_GPIO)
    CLK_EnableModuleClock(GPA_MODULE);
    CLK_EnableModuleClock(GPB_MODULE);
    CLK_EnableModuleClock(GPC_MODULE);
    CLK_EnableModuleClock(GPD_MODULE);
    CLK_EnableModuleClock(GPE_MODULE);
    CLK_EnableModuleClock(GPF_MODULE);
    CLK_EnableModuleClock(GPG_MODULE);
    CLK_EnableModuleClock(GPH_MODULE);
    CLK_EnableModuleClock(GPI_MODULE);
    CLK_EnableModuleClock(GPJ_MODULE);
    CLK_EnableModuleClock(GPK_MODULE);
    CLK_EnableModuleClock(GPL_MODULE);
    CLK_EnableModuleClock(GPM_MODULE);
    CLK_EnableModuleClock(GPN_MODULE);
#endif
}

static void nu_clock_qspi_init(void)
{
#if defined(BSP_USING_QSPI0)
    CLK_EnableModuleClock(QSPI0_MODULE);
    CLK_SetModuleClock(QSPI0_MODULE, CLK_CLKSEL4_QSPI0SEL_PCLK0, MODULE_NoMsk);
#endif
#if defined(BSP_USING_QSPI1)
    CLK_EnableModuleClock(QSPI1_MODULE);
    CLK_SetModuleClock(QSPI1_MODULE, CLK_CLKSEL4_QSPI1SEL_PCLK0, MODULE_NoMsk);
#endif
}

static void nu_clock_spi_init(void)
{
#if defined(BSP_USING_SPI0)
    CLK_EnableModuleClock(SPI0_MODULE);
    CLK_SetModuleClock(SPI0_MODULE, CLK_CLKSEL4_SPI0SEL_PCLK1, MODULE_NoMsk);
#endif
#if defined(BSP_USING_SPI1)
    CLK_EnableModuleClock(SPI1_MODULE);
    CLK_SetModuleClock(SPI1_MODULE, CLK_CLKSEL4_SPI1SEL_PCLK2, MODULE_NoMsk);
#endif
#if defined(BSP_USING_SPI2)
    CLK_EnableModuleClock(SPI2_MODULE);
    CLK_SetModuleClock(SPI2_MODULE, CLK_CLKSEL4_SPI2SEL_PCLK1, MODULE_NoMsk);
#endif
#if defined(BSP_USING_SPI3)
    CLK_EnableModuleClock(SPI3_MODULE);
    CLK_SetModuleClock(SPI3_MODULE, CLK_CLKSEL4_SPI3SEL_PCLK2, MODULE_NoMsk);
#endif
}

static void nu_clock_i2c_init(void)
{
#if defined(BSP_USING_I2C0)
    CLK_EnableModuleClock(I2C0_MODULE);
#endif
#if defined(BSP_USING_I2C1)
    CLK_EnableModuleClock(I2C1_MODULE);
#endif
#if defined(BSP_USING_I2C2)
    CLK_EnableModuleClock(I2C2_MODULE);
#endif
#if defined(BSP_USING_I2C3)
    CLK_EnableModuleClock(I2C3_MODULE);
#endif
#if defined(BSP_USING_I2C4)
    CLK_EnableModuleClock(I2C4_MODULE);
#endif
#if defined(BSP_USING_I2C5)
    CLK_EnableModuleClock(I2C5_MODULE);
#endif
}

static void nu_clock_epwm_init(void)
{
#if defined(BSP_USING_EPWM0)
    CLK_EnableModuleClock(EPWM0_MODULE);
#endif
#if defined(BSP_USING_EPWM1)
    CLK_EnableModuleClock(EPWM1_MODULE);
#endif
#if defined(BSP_USING_EPWM2)
    CLK_EnableModuleClock(EPWM2_MODULE);
#endif
}

static void nu_clock_i2s_init(void)
{
#if defined(BSP_USING_I2S0)
    CLK_EnableModuleClock(I2S0_MODULE);
    CLK_SetModuleClock(I2S0_MODULE, CLK_CLKSEL4_I2S0SEL_APLL, MODULE_NoMsk);
#endif
#if defined(BSP_USING_I2S1)
    CLK_EnableModuleClock(I2S1_MODULE);
    CLK_SetModuleClock(I2S1_MODULE, CLK_CLKSEL4_I2S1SEL_APLL, MODULE_NoMsk);
#endif
}

void nu_clock_timer_init(void)
{
#if defined(BSP_USING_TMR0)
    CLK_EnableModuleClock(TMR0_MODULE);
    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_HXT, MODULE_NoMsk);
#endif
#if defined(BSP_USING_TMR1)
    CLK_EnableModuleClock(TMR1_MODULE);
    CLK_SetModuleClock(TMR1_MODULE, CLK_CLKSEL1_TMR1SEL_HXT, MODULE_NoMsk);
#endif
#if defined(BSP_USING_TMR2)
    CLK_EnableModuleClock(TMR2_MODULE);
    CLK_SetModuleClock(TMR2_MODULE, CLK_CLKSEL1_TMR2SEL_HXT, MODULE_NoMsk);
#endif
#if defined(BSP_USING_TMR3)
    CLK_EnableModuleClock(TMR3_MODULE);
    CLK_SetModuleClock(TMR3_MODULE, CLK_CLKSEL1_TMR3SEL_HXT, MODULE_NoMsk);
#endif
#if defined(BSP_USING_TMR4)
    CLK_EnableModuleClock(TMR4_MODULE);
    CLK_SetModuleClock(TMR4_MODULE, CLK_CLKSEL1_TMR4SEL_HXT, MODULE_NoMsk);
#endif
#if defined(BSP_USING_TMR5)
    CLK_EnableModuleClock(TMR5_MODULE);
    CLK_SetModuleClock(TMR5_MODULE, CLK_CLKSEL1_TMR5SEL_HXT, MODULE_NoMsk);
#endif
#if defined(BSP_USING_TMR6)
    CLK_EnableModuleClock(TMR6_MODULE);
    CLK_SetModuleClock(TMR6_MODULE, CLK_CLKSEL1_TMR6SEL_HXT, MODULE_NoMsk);
#endif
#if defined(BSP_USING_TMR7)
    CLK_EnableModuleClock(TMR7_MODULE);
    CLK_SetModuleClock(TMR7_MODULE, CLK_CLKSEL1_TMR7SEL_HXT, MODULE_NoMsk);
#endif
#if defined(BSP_USING_TMR8)
    CLK_EnableModuleClock(TMR8_MODULE);
    CLK_SetModuleClock(TMR8_MODULE, CLK_CLKSEL2_TMR8SEL_HXT, MODULE_NoMsk);
#endif
#if defined(BSP_USING_TMR9)
    CLK_EnableModuleClock(TMR9_MODULE);
    CLK_SetModuleClock(TMR9_MODULE, CLK_CLKSEL2_TMR9SEL_HXT, MODULE_NoMsk);
#endif
#if defined(BSP_USING_TMR10)
    CLK_EnableModuleClock(TMR10_MODULE);
    CLK_SetModuleClock(TMR10_MODULE, CLK_CLKSEL2_TMR10SEL_HXT, MODULE_NoMsk);
#endif
#if defined(BSP_USING_TMR11)
    CLK_EnableModuleClock(TMR11_MODULE);
    CLK_SetModuleClock(TMR11_MODULE, CLK_CLKSEL2_TMR11SEL_HXT, MODULE_NoMsk);
#endif
}

void nu_clock_wdt_init(void)
{
#if defined(BSP_USING_WDT0)
    CLK_EnableModuleClock(WDT0_MODULE);
    CLK_SetModuleClock(WDT0_MODULE, CLK_CLKSEL3_WDT0SEL_PCLK3_DIV4096, MODULE_NoMsk);
#endif
#if defined(BSP_USING_WDT1)
    CLK_EnableModuleClock(WDT1_MODULE);
    CLK_SetModuleClock(WDT1_MODULE, CLK_CLKSEL3_WDT1SEL_PCLK3_DIV4096, MODULE_NoMsk);
#endif
#if defined(BSP_USING_WDT2)
    CLK_EnableModuleClock(WDT2_MODULE);
    CLK_SetModuleClock(WDT2_MODULE, CLK_CLKSEL3_WDT2SEL_PCLK3_DIV4096, MODULE_NoMsk);
#endif
}

void nu_clock_canfd_init(void)
{
#if defined(BSP_USING_CANFD0)
    CLK_EnableModuleClock(CANFD0_MODULE);
    CLK_SetModuleClock(CANFD0_MODULE, CLK_CLKSEL4_CANFD0SEL_APLL, CLK_CLKDIV0_CANFD0(1));
#endif
#if defined(BSP_USING_CANFD1)
    CLK_EnableModuleClock(CANFD1_MODULE);
    CLK_SetModuleClock(CANFD1_MODULE, CLK_CLKSEL4_CANFD1SEL_APLL, CLK_CLKDIV0_CANFD1(1));
#endif
#if defined(BSP_USING_CANFD2)
    CLK_EnableModuleClock(CANFD2_MODULE);
    CLK_SetModuleClock(CANFD2_MODULE, CLK_CLKSEL4_CANFD2SEL_APLL, CLK_CLKDIV0_CANFD2(1));
#endif
#if defined(BSP_USING_CANFD3)
    CLK_EnableModuleClock(CANFD3_MODULE);
    CLK_SetModuleClock(CANFD3_MODULE, CLK_CLKSEL4_CANFD3SEL_APLL, CLK_CLKDIV0_CANFD3(1));
#endif
}

void nu_clock_sc_init(void)
{
#if defined(BSP_USING_SCUART0)
    CLK_EnableModuleClock(SC0_MODULE);
    CLK_SetModuleClock(SC0_MODULE, CLK_CLKSEL4_SC0SEL_HXT, MODULE_NoMsk);
#endif
#if defined(BSP_USING_SCUART1)
    CLK_EnableModuleClock(SC1_MODULE);
    CLK_SetModuleClock(SC1_MODULE, CLK_CLKSEL4_SC1SEL_HXT, MODULE_NoMsk);
#endif
}

void nu_clock_rtc_init(void)
{
#if defined(BSP_USING_RTC)
    CLK_EnableModuleClock(RTC_MODULE);
#endif
}

#if !defined(USE_MA35D1_SUBM)

static void nu_clock_usbd_init(void)
{
}

static void nu_clock_usbh_init(void)
{
}

static void nu_clock_gmac_init(void)
{
#if defined(BSP_USING_GMAC0)
    CLK_EnableModuleClock(GMAC0_MODULE);
#endif
#if defined(BSP_USING_GMAC1)
    CLK_EnableModuleClock(GMAC1_MODULE);
#endif
}

static void nu_clock_sdh_init(void)
{
#if defined(BSP_USING_SDH0)
    CLK_EnableModuleClock(SDH0_MODULE);
#endif
#if defined(BSP_USING_SDH1)
    CLK_EnableModuleClock(SDH1_MODULE);
#endif
}

static void nu_clock_disp_init(void)
{
#if defined(BSP_USING_DISP)
    CLK_EnableModuleClock(DCU_MODULE);
    CLK_SetModuleClock(DCU_MODULE, CLK_CLKSEL0_DCUSEL_EPLL_DIV2, MODULE_NoMsk);

//    CLK_SetModuleClock(DCUP_MODULE, CLK_CLKSEL0_DCUPSEL_VPLL, MODULE_NoMsk);
#endif
}

void nu_clock_base_init(void)
{
    /* Enable HXT, LXT */
    CLK->PWRCTL |= (CLK_PWRCTL_HXTEN_Msk | CLK_PWRCTL_HIRCEN_Msk | CLK_PWRCTL_LXTEN_Msk | CLK_PWRCTL_LIRCEN_Msk);

    /* Waiting clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Waiting clock ready */
    CLK_WaitClockReady(CLK_STATUS_LXTSTB_Msk);

    /* Waiting clock ready */
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

    /* Waiting clock ready */
    CLK_WaitClockReady(CLK_STATUS_LIRCSTB_Msk);
}
#endif

static void nu_clock_hwsem_init(void)
{
#if defined(BSP_USING_HWSEM0)
    CLK_EnableModuleClock(HWSEM0_MODULE);
#endif
}

static void nu_clock_whc_init(void)
{
#if defined(BSP_USING_WHC0)
    CLK_EnableModuleClock(WHC0_MODULE);
#endif
#if defined(BSP_USING_WHC1)
    CLK_EnableModuleClock(WHC1_MODULE);
#endif
}

void nu_clock_init(void)
{
#if !defined(USE_MA35D1_SUBM)
    nu_clock_base_init();

    nu_clock_gmac_init();
    nu_clock_sdh_init();
    nu_clock_usbd_init();
    nu_clock_usbh_init();
    nu_clock_disp_init();
#endif

    nu_clock_whc_init();
    nu_clock_hwsem_init();
    nu_clock_pdma_init();
    nu_clock_gpio_init();
    nu_clock_uart_init();
    nu_clock_qspi_init();
    nu_clock_spi_init();
    nu_clock_i2c_init();
    nu_clock_epwm_init();
    nu_clock_i2s_init();
    nu_clock_canfd_init();
    nu_clock_sc_init();
    nu_clock_timer_init();
    nu_clock_wdt_init();
    nu_clock_rtc_init();
}

void nu_clock_deinit(void)
{

}
