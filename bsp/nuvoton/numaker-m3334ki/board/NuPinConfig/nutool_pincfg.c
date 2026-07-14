/****************************************************************************
 * @file     nutool_pincfg.c
 * @version  v1.35.3
 * @Date     Mon Oct 27 2025 19:42:48 GMT+0800 (Taipei Standard Time)
 * @brief    NuMicro generated code file
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright (C) 2013-2025 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

/********************
MCU:M3334KIGAE(LQFP128)
********************/

#include "rtconfig.h"
#include "NuMicro.h"

#if defined(BOARD_USING_NUFUN)
void nutool_pincfg_init_bpwm0(void)
{
    SYS->GPG_MFP3 &= ~(SYS_GPG_MFP3_PG14MFP_Msk | SYS_GPG_MFP3_PG13MFP_Msk | SYS_GPG_MFP3_PG12MFP_Msk);
    SYS->GPG_MFP3 |= (SYS_GPG_MFP3_PG14MFP_BPWM0_CH0 | SYS_GPG_MFP3_PG13MFP_BPWM0_CH1 | SYS_GPG_MFP3_PG12MFP_BPWM0_CH2);

    return;
}

void nutool_pincfg_deinit_bpwm0(void)
{
    SYS->GPG_MFP3 &= ~(SYS_GPG_MFP3_PG14MFP_Msk | SYS_GPG_MFP3_PG13MFP_Msk | SYS_GPG_MFP3_PG12MFP_Msk);

    return;
}

void nutool_pincfg_init_canfd0(void)
{
    SYS->GPE_MFP3 &= ~(SYS_GPE_MFP3_PE15MFP_Msk | SYS_GPE_MFP3_PE14MFP_Msk);
    SYS->GPE_MFP3 |= (SYS_GPE_MFP3_PE15MFP_CANFD0_RXD | SYS_GPE_MFP3_PE14MFP_CANFD0_TXD);

    return;
}

void nutool_pincfg_deinit_canfd0(void)
{
    SYS->GPE_MFP3 &= ~(SYS_GPE_MFP3_PE15MFP_Msk | SYS_GPE_MFP3_PE14MFP_Msk);

    return;
}

void nutool_pincfg_init_epwm1(void)
{
    SYS->GPC_MFP3 &= ~(SYS_GPC_MFP3_PC12MFP_Msk);
    SYS->GPC_MFP3 |= (SYS_GPC_MFP3_PC12MFP_EPWM1_CH0);

    return;
}

void nutool_pincfg_deinit_epwm1(void)
{
    SYS->GPC_MFP3 &= ~(SYS_GPC_MFP3_PC12MFP_Msk);

    return;
}

void nutool_pincfg_init_eqei0(void)
{
    SYS->GPA_MFP0 &= ~(SYS_GPA_MFP0_PA3MFP_Msk);
    SYS->GPA_MFP0 |= (SYS_GPA_MFP0_PA3MFP_EQEI0_B);
    SYS->GPA_MFP1 &= ~(SYS_GPA_MFP1_PA4MFP_Msk);
    SYS->GPA_MFP1 |= (SYS_GPA_MFP1_PA4MFP_EQEI0_A);

    return;
}

void nutool_pincfg_deinit_eqei0(void)
{
    SYS->GPA_MFP0 &= ~(SYS_GPA_MFP0_PA3MFP_Msk);
    SYS->GPA_MFP1 &= ~(SYS_GPA_MFP1_PA4MFP_Msk);

    return;
}

void nutool_pincfg_init_i2c0(void)
{
    SYS->GPC_MFP2 &= ~(SYS_GPC_MFP2_PC8MFP_Msk);
    SYS->GPC_MFP2 |= (SYS_GPC_MFP2_PC8MFP_I2C0_SDA);
    SYS->GPE_MFP3 &= ~(SYS_GPE_MFP3_PE13MFP_Msk);
    SYS->GPE_MFP3 |= (SYS_GPE_MFP3_PE13MFP_I2C0_SCL);

    return;
}

void nutool_pincfg_deinit_i2c0(void)
{
    SYS->GPC_MFP2 &= ~(SYS_GPC_MFP2_PC8MFP_Msk);
    SYS->GPE_MFP3 &= ~(SYS_GPE_MFP3_PE13MFP_Msk);

    return;
}

void nutool_pincfg_init_i2c1(void)
{
    SYS->GPG_MFP0 &= ~(SYS_GPG_MFP0_PG2MFP_Msk | SYS_GPG_MFP0_PG3MFP_Msk);
    SYS->GPG_MFP0 |= (SYS_GPG_MFP0_PG2MFP_I2C1_SCL | SYS_GPG_MFP0_PG3MFP_I2C1_SDA);

    return;
}

void nutool_pincfg_deinit_i2c1(void)
{
    SYS->GPG_MFP0 &= ~(SYS_GPG_MFP0_PG2MFP_Msk | SYS_GPG_MFP0_PG3MFP_Msk);

    return;
}


void nutool_pincfg_init_i2c2(void)
{
    SYS->GPA_MFP2 &= ~(SYS_GPA_MFP2_PA11MFP_Msk | SYS_GPA_MFP2_PA10MFP_Msk);
    SYS->GPA_MFP2 |= (SYS_GPA_MFP2_PA11MFP_I2C2_SCL | SYS_GPA_MFP2_PA10MFP_I2C2_SDA);

    return;
}

void nutool_pincfg_deinit_i2c2(void)
{
    SYS->GPA_MFP2 &= ~(SYS_GPA_MFP2_PA11MFP_Msk | SYS_GPA_MFP2_PA10MFP_Msk);

    return;
}

void nutool_pincfg_init_i2s0(void)
{
    SYS->GPF_MFP1 &= ~(SYS_GPF_MFP1_PF7MFP_Msk | SYS_GPF_MFP1_PF6MFP_Msk);
    SYS->GPF_MFP1 |= (SYS_GPF_MFP1_PF7MFP_I2S0_DO | SYS_GPF_MFP1_PF6MFP_I2S0_LRCK);
    SYS->GPF_MFP2 &= ~(SYS_GPF_MFP2_PF10MFP_Msk | SYS_GPF_MFP2_PF9MFP_Msk | SYS_GPF_MFP2_PF8MFP_Msk);
    SYS->GPF_MFP2 |= (SYS_GPF_MFP2_PF10MFP_I2S0_BCLK | SYS_GPF_MFP2_PF9MFP_I2S0_MCLK | SYS_GPF_MFP2_PF8MFP_I2S0_DI);

    return;
}

void nutool_pincfg_deinit_i2s0(void)
{
    SYS->GPF_MFP1 &= ~(SYS_GPF_MFP1_PF7MFP_Msk | SYS_GPF_MFP1_PF6MFP_Msk);
    SYS->GPF_MFP2 &= ~(SYS_GPF_MFP2_PF10MFP_Msk | SYS_GPF_MFP2_PF9MFP_Msk | SYS_GPF_MFP2_PF8MFP_Msk);

    return;
}

void nutool_pincfg_init_i3c0(void)
{
    /* Set multi-function pins for I3C pin */
    GPIO_ENABLE_SCHMITT_TRIGGER(PB, (BIT0 | BIT1));
    SET_I3C0_SDA_PB0();
    SET_I3C0_SCL_PB1();

    /* Use TYPE-A Resistance Connection */
    PB->PUSEL = ((GPIO_PUSEL_PULL_UP << (0 << 1)) | (GPIO_PUSEL_PULL_UP << (1 << 1)));
    SET_I3C0_PUPEN_PC9();

    return;
}

void nutool_pincfg_deinit_i3c0(void)
{
    SYS->GPB_MFP0 &= ~(SYS_GPB_MFP0_PB1MFP_Msk | SYS_GPB_MFP0_PB0MFP_Msk);
    SYS->GPC_MFP2 &= ~(SYS_GPC_MFP2_PC9MFP_Msk);

    return;
}

void nutool_pincfg_init_ice(void)
{
    SYS->GPF_MFP0 &= ~(SYS_GPF_MFP0_PF1MFP_Msk | SYS_GPF_MFP0_PF0MFP_Msk);
    SYS->GPF_MFP0 |= (SYS_GPF_MFP0_PF1MFP_ICE_CLK | SYS_GPF_MFP0_PF0MFP_ICE_DAT);

    return;
}

void nutool_pincfg_deinit_ice(void)
{
    SYS->GPF_MFP0 &= ~(SYS_GPF_MFP0_PF1MFP_Msk | SYS_GPF_MFP0_PF0MFP_Msk);

    return;
}

void nutool_pincfg_init_llsi0(void)
{
    SYS->GPB_MFP3 &= ~(SYS_GPB_MFP3_PB15MFP_Msk);
    SYS->GPB_MFP3 |= (SYS_GPB_MFP3_PB15MFP_LLSI0_OUT);

    return;
}

void nutool_pincfg_deinit_llsi0(void)
{
    SYS->GPB_MFP3 &= ~(SYS_GPB_MFP3_PB15MFP_Msk);

    return;
}

void nutool_pincfg_init_pa(void)
{
    SYS->GPA_MFP2 &= ~(SYS_GPA_MFP2_PA9MFP_Msk | SYS_GPA_MFP2_PA8MFP_Msk);
    SYS->GPA_MFP2 |= (SYS_GPA_MFP2_PA9MFP_GPIO | SYS_GPA_MFP2_PA8MFP_GPIO);

    return;
}

void nutool_pincfg_deinit_pa(void)
{
    SYS->GPA_MFP2 &= ~(SYS_GPA_MFP2_PA9MFP_Msk | SYS_GPA_MFP2_PA8MFP_Msk);

    return;
}

void nutool_pincfg_init_pb(void)
{
    SYS->GPB_MFP1 &= ~(SYS_GPB_MFP1_PB7MFP_Msk | SYS_GPB_MFP1_PB6MFP_Msk);
    SYS->GPB_MFP1 |= (SYS_GPB_MFP1_PB7MFP_GPIO | SYS_GPB_MFP1_PB6MFP_GPIO);
    SYS->GPB_MFP2 &= ~(SYS_GPB_MFP2_PB9MFP_Msk | SYS_GPB_MFP2_PB8MFP_Msk

#if defined(BOARD_USING_NUFUN_LED)
                       | SYS_GPB_MFP2_PB10MFP_Msk | SYS_GPB_MFP2_PB11MFP_Msk
#endif
                      );

    SYS->GPB_MFP2 |= (SYS_GPB_MFP2_PB9MFP_GPIO | SYS_GPB_MFP2_PB8MFP_GPIO
#if defined(BOARD_USING_NUFUN_LED)
                      | SYS_GPB_MFP2_PB10MFP_GPIO | SYS_GPB_MFP2_PB11MFP_GPIO
#endif
                     );

    SYS->GPB_MFP3 &= ~(SYS_GPB_MFP3_PB14MFP_Msk);
    SYS->GPB_MFP3 |= (SYS_GPB_MFP3_PB14MFP_GPIO);

    return;
}

void nutool_pincfg_deinit_pb(void)
{
    SYS->GPB_MFP1 &= ~(SYS_GPB_MFP1_PB7MFP_Msk | SYS_GPB_MFP1_PB6MFP_Msk);
    SYS->GPB_MFP2 &= ~(SYS_GPB_MFP2_PB9MFP_Msk | SYS_GPB_MFP2_PB8MFP_Msk
#if defined(BOARD_USING_NUFUN_LED)
                       | SYS_GPB_MFP2_PB10MFP_Msk | SYS_GPB_MFP2_PB11MFP_Msk
#endif
                      );

    SYS->GPB_MFP3 &= ~(SYS_GPB_MFP3_PB14MFP_Msk);

    return;
}

void nutool_pincfg_init_pc(void)
{
    SYS->GPC_MFP3 &= ~(SYS_GPC_MFP3_PC13MFP_Msk);
    SYS->GPC_MFP3 |= (SYS_GPC_MFP3_PC13MFP_GPIO);

    return;
}

void nutool_pincfg_deinit_pc(void)
{
    SYS->GPC_MFP3 &= ~(SYS_GPC_MFP3_PC13MFP_Msk);

    return;
}

void nutool_pincfg_init_pd(void)
{
    SYS->GPD_MFP2 &= ~(SYS_GPD_MFP2_PD11MFP_Msk | SYS_GPD_MFP2_PD10MFP_Msk);
    SYS->GPD_MFP2 |= (SYS_GPD_MFP2_PD11MFP_GPIO | SYS_GPD_MFP2_PD10MFP_GPIO);
    SYS->GPD_MFP3 &= ~(SYS_GPD_MFP3_PD14MFP_Msk | SYS_GPD_MFP3_PD12MFP_Msk);
    SYS->GPD_MFP3 |= (SYS_GPD_MFP3_PD14MFP_GPIO | SYS_GPD_MFP3_PD12MFP_GPIO);

    return;
}

void nutool_pincfg_deinit_pd(void)
{
    SYS->GPD_MFP2 &= ~(SYS_GPD_MFP2_PD11MFP_Msk | SYS_GPD_MFP2_PD10MFP_Msk);
    SYS->GPD_MFP3 &= ~(SYS_GPD_MFP3_PD14MFP_Msk | SYS_GPD_MFP3_PD12MFP_Msk);

    return;
}

void nutool_pincfg_init_ph(void)
{
    SYS->GPH_MFP2 &= ~(SYS_GPH_MFP2_PH11MFP_Msk | SYS_GPH_MFP2_PH10MFP_Msk);
    SYS->GPH_MFP2 |= (SYS_GPH_MFP2_PH11MFP_GPIO | SYS_GPH_MFP2_PH10MFP_GPIO);

    return;
}

void nutool_pincfg_deinit_ph(void)
{
    SYS->GPH_MFP2 &= ~(SYS_GPH_MFP2_PH11MFP_Msk | SYS_GPH_MFP2_PH10MFP_Msk);

    return;
}

void nutool_pincfg_init_qspi0(void)
{
    SYS->GPC_MFP0 &= ~(SYS_GPC_MFP0_PC3MFP_Msk | SYS_GPC_MFP0_PC2MFP_Msk | SYS_GPC_MFP0_PC1MFP_Msk | SYS_GPC_MFP0_PC0MFP_Msk);
    SYS->GPC_MFP0 |= (SYS_GPC_MFP0_PC3MFP_QSPI0_SS | SYS_GPC_MFP0_PC2MFP_QSPI0_CLK | SYS_GPC_MFP0_PC1MFP_QSPI0_MISO0 | SYS_GPC_MFP0_PC0MFP_QSPI0_MOSI0);
    SYS->GPC_MFP1 &= ~(SYS_GPC_MFP1_PC5MFP_Msk | SYS_GPC_MFP1_PC4MFP_Msk);
    SYS->GPC_MFP1 |= (SYS_GPC_MFP1_PC5MFP_QSPI0_MISO1 | SYS_GPC_MFP1_PC4MFP_QSPI0_MOSI1);

    return;
}

void nutool_pincfg_deinit_qspi0(void)
{
    SYS->GPC_MFP0 &= ~(SYS_GPC_MFP0_PC3MFP_Msk | SYS_GPC_MFP0_PC2MFP_Msk | SYS_GPC_MFP0_PC1MFP_Msk | SYS_GPC_MFP0_PC0MFP_Msk);
    SYS->GPC_MFP1 &= ~(SYS_GPC_MFP1_PC5MFP_Msk | SYS_GPC_MFP1_PC4MFP_Msk);

    return;
}

void nutool_pincfg_init_sd0(void)
{
    SYS->GPD_MFP3 &= ~(SYS_GPD_MFP3_PD13MFP_Msk);
    SYS->GPD_MFP3 |= (SYS_GPD_MFP3_PD13MFP_SD0_nCD);
    SYS->GPE_MFP0 &= ~(SYS_GPE_MFP0_PE3MFP_Msk | SYS_GPE_MFP0_PE2MFP_Msk);
    SYS->GPE_MFP0 |= (SYS_GPE_MFP0_PE3MFP_SD0_DAT1 | SYS_GPE_MFP0_PE2MFP_SD0_DAT0);
    SYS->GPE_MFP1 &= ~(SYS_GPE_MFP1_PE7MFP_Msk | SYS_GPE_MFP1_PE6MFP_Msk | SYS_GPE_MFP1_PE5MFP_Msk | SYS_GPE_MFP1_PE4MFP_Msk);
    SYS->GPE_MFP1 |= (SYS_GPE_MFP1_PE7MFP_SD0_CMD | SYS_GPE_MFP1_PE6MFP_SD0_CLK | SYS_GPE_MFP1_PE5MFP_SD0_DAT3 | SYS_GPE_MFP1_PE4MFP_SD0_DAT2);

    return;
}

void nutool_pincfg_deinit_sd0(void)
{
    SYS->GPD_MFP3 &= ~(SYS_GPD_MFP3_PD13MFP_Msk);
    SYS->GPE_MFP0 &= ~(SYS_GPE_MFP0_PE3MFP_Msk | SYS_GPE_MFP0_PE2MFP_Msk);
    SYS->GPE_MFP1 &= ~(SYS_GPE_MFP1_PE7MFP_Msk | SYS_GPE_MFP1_PE6MFP_Msk | SYS_GPE_MFP1_PE5MFP_Msk | SYS_GPE_MFP1_PE4MFP_Msk);

    return;
}

void nutool_pincfg_init_spi1(void)
{
    SYS->GPE_MFP0 &= ~(SYS_GPE_MFP0_PE1MFP_Msk | SYS_GPE_MFP0_PE0MFP_Msk);
    SYS->GPE_MFP0 |= (SYS_GPE_MFP0_PE1MFP_SPI1_MISO | SYS_GPE_MFP0_PE0MFP_SPI1_MOSI);
    SYS->GPH_MFP2 &= ~(SYS_GPH_MFP2_PH9MFP_Msk | SYS_GPH_MFP2_PH8MFP_Msk);
    SYS->GPH_MFP2 |= (SYS_GPH_MFP2_PH9MFP_SPI1_SS | SYS_GPH_MFP2_PH8MFP_SPI1_CLK);

    return;
}

void nutool_pincfg_deinit_spi1(void)
{
    SYS->GPE_MFP0 &= ~(SYS_GPE_MFP0_PE1MFP_Msk | SYS_GPE_MFP0_PE0MFP_Msk);
    SYS->GPH_MFP2 &= ~(SYS_GPH_MFP2_PH9MFP_Msk | SYS_GPH_MFP2_PH8MFP_Msk);

    return;
}

void nutool_pincfg_init_uart2_rs485(void)
{
    SET_UART2_RXD_PE9();
    SET_UART2_TXD_PE8();
    SET_UART2_nRTS_PD8();

    return;
}

void nutool_pincfg_deinit_uart2_rs485(void)
{
    SYS->GPE_MFP2 &= ~(SYS_GPE_MFP2_PE8MFP_Msk | SYS_GPE_MFP2_PE9MFP_Msk);
    SYS->GPD_MFP2 &= ~(SYS_GPD_MFP2_PD8MFP_Msk);

    return;
}
#elif defined(BOARD_USING_NUTFT)
void expansion_nutft_pin_init(void)
{
#if defined(BOARD_USING_LCD_ILI9341)
    SET_SPI2_SS_PA11();
    SET_SPI2_CLK_PA10();
    SET_SPI2_MISO_PA9();
    SET_SPI2_MOSI_PA8();


    SET_GPIO_PB2();
    SET_GPIO_PB3();
    SET_GPIO_PB5();
#endif

#if defined(BOARD_USING_NUTFT_ADC_TOUCH)
    GPIO_SetMode(PB, BIT4 | BIT5 | BIT6 | BIT7, GPIO_MODE_INPUT);

    /* EADC Analog Pin: UNO_A0, UNO_A1, UNO_A2, UNO_A3 */
    SYS->GPB_MFP1 &= ~(SYS_GPB_MFP3_PB14MFP_Msk | SYS_GPB_MFP3_PB15MFP_Msk);
    SYS->GPB_MFP1 |= (SYS_GPB_MFP3_PB14MFP_EADC0_CH14 | SYS_GPB_MFP3_PB15MFP_EADC0_CH15);
    SYS->GPB_MFP2 &= ~(SYS_GPB_MFP2_PB9MFP_Msk | SYS_GPB_MFP2_PB8MFP_Msk);
    SYS->GPB_MFP2 |= (SYS_GPB_MFP2_PB9MFP_EADC0_CH9 | SYS_GPB_MFP2_PB8MFP_EADC0_CH8);

    /* Disable digital path on these EADC pins */
    GPIO_DISABLE_DIGITAL_PATH(PB, BIT8 | BIT9 | BIT14 | BIT15);
#endif

#if defined(BOARD_USING_QSPI_FLASH)
    SET_QSPI0_MOSI0_PA0();
    SET_QSPI0_MISO0_PA1();
    SET_QSPI0_CLK_PA2();
    SET_QSPI0_SS_PA3();
    SET_QSPI0_MOSI1_PA4();
    SET_QSPI0_MISO1_PA5();
#endif

#if defined(BOARD_USING_NUTFT_BUTTON)
    SYS->GPB_MFP0 &= ~(SYS_GPB_MFP0_PB0MFP_Msk | SYS_GPB_MFP0_PB1MFP_Msk);

    /* Disable digital path on these ADC pins */
    GPIO_ENABLE_DIGITAL_PATH(PB, BIT0 | BIT1);
#endif

}
#endif

void nutool_pincfg_init_uart0(void)
{
    SET_UART0_RXD_PB12();
    SET_UART0_TXD_PB13();

    return;
}

void nutool_pincfg_deinit_uart0(void)
{
    SET_GPIO_PB12();
    SET_GPIO_PB13();

    return;
}

void nutool_pincfg_init_hsusb(void)
{
    /* HSUSB_VBUS_EN (USB 2.0 VBUS power enable pin) multi-function pin - PB.10   */
    SET_HSUSB_VBUS_EN_PB10();

    /* HSUSB_VBUS_ST (USB 2.0 over-current detect pin) multi-function pin - PB.11 */
    SET_HSUSB_VBUS_ST_PB11();
}

void nutool_pincfg_deinit_hsusb(void)
{
    SET_GPIO_PB10();
    SET_GPIO_PB11();
}

void nutool_pincfg_init_eadc(void)
{
#if defined(BOARD_USING_NUFUN_ADC_TOUCH)
    GPIO_SetMode(PB, BIT2 | BIT3 | BIT4 | BIT5, GPIO_MODE_INPUT);

    SYS->GPB_MFP0 &= ~(SYS_GPB_MFP0_PB2MFP_Msk | SYS_GPB_MFP0_PB2MFP_Msk);
    SYS->GPB_MFP0 |= (SYS_GPB_MFP0_PB2MFP_EADC0_CH2 | SYS_GPB_MFP0_PB3MFP_EADC0_CH3);

    SYS->GPB_MFP1 &= ~(SYS_GPB_MFP1_PB4MFP_Msk | SYS_GPB_MFP1_PB5MFP_Msk);
    SYS->GPB_MFP1 |= (SYS_GPB_MFP1_PB4MFP_EADC0_CH4 | SYS_GPB_MFP1_PB5MFP_EADC0_CH5);

    GPIO_DISABLE_DIGITAL_PATH(PB,  BIT2 | BIT3 | BIT4 | BIT5);
#endif

    GPIO_SetMode(PB, BIT6 | BIT7, GPIO_MODE_INPUT);

    SYS->GPB_MFP1 &= ~(SYS_GPB_MFP1_PB6MFP_Msk | SYS_GPB_MFP1_PB7MFP_Msk);
    SYS->GPB_MFP1 |= (SYS_GPB_MFP1_PB6MFP_EADC0_CH6 | SYS_GPB_MFP1_PB7MFP_EADC0_CH7);

    /* Disable digital path on these EADC pins */
    GPIO_DISABLE_DIGITAL_PATH(PB,  BIT6 | BIT7);
}

void nutool_pincfg_deinit_eadc(void)
{
    /* Disable digital path on these EADC pins */
    GPIO_ENABLE_DIGITAL_PATH(PB, BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7);

    SYS->GPB_MFP0 &= ~(SYS_GPB_MFP0_PB2MFP_Msk | SYS_GPB_MFP0_PB2MFP_Msk);
    SYS->GPB_MFP1 &= ~(SYS_GPB_MFP1_PB4MFP_Msk | SYS_GPB_MFP1_PB5MFP_Msk | SYS_GPB_MFP1_PB6MFP_Msk | SYS_GPB_MFP1_PB7MFP_Msk);
}

void nutool_pincfg_init(void)
{
    /* Vref connect to internal */
    SYS_SetVRef(SYS_VREFCTL_VREF_PIN);

    nutool_pincfg_init_uart0();
    nutool_pincfg_init_hsusb();
    nutool_pincfg_init_eadc();

#if defined(BOARD_USING_NUFUN)
    nutool_pincfg_init_bpwm0();
    nutool_pincfg_init_canfd0();
    nutool_pincfg_init_epwm1();
    nutool_pincfg_init_eqei0();
    nutool_pincfg_init_i2c0();
    nutool_pincfg_init_i2c1();
    nutool_pincfg_init_i2c2();
    nutool_pincfg_init_i2s0();
    nutool_pincfg_init_i3c0();
    nutool_pincfg_init_ice();
    nutool_pincfg_init_llsi0();
    nutool_pincfg_init_pa();
    nutool_pincfg_init_pb();
    nutool_pincfg_init_pc();
    nutool_pincfg_init_pd();
    nutool_pincfg_init_ph();
    nutool_pincfg_init_qspi0();
    nutool_pincfg_init_sd0();
    nutool_pincfg_init_spi1();
    nutool_pincfg_init_uart2_rs485();
#elif defined(BOARD_USING_NUTFT)
    expansion_nutft_pin_init();
#endif

    return;
}

void nutool_pincfg_deinit(void)
{
    nutool_pincfg_deinit_uart0();
    nutool_pincfg_deinit_hsusb();
    nutool_pincfg_deinit_eadc();

#if defined(BOARD_USING_NUFUN)
    nutool_pincfg_deinit_bpwm0();
    nutool_pincfg_deinit_canfd0();
    nutool_pincfg_deinit_epwm1();
    nutool_pincfg_deinit_eqei0();
    nutool_pincfg_deinit_i2c0();
    nutool_pincfg_deinit_i2c1();
    nutool_pincfg_deinit_i2c2();
    nutool_pincfg_deinit_i2s0();
    nutool_pincfg_deinit_i3c0();
    nutool_pincfg_deinit_ice();
    nutool_pincfg_deinit_llsi0();
    nutool_pincfg_deinit_pa();
    nutool_pincfg_deinit_pb();
    nutool_pincfg_deinit_pc();
    nutool_pincfg_deinit_pd();
    nutool_pincfg_deinit_ph();
    nutool_pincfg_deinit_qspi0();
    nutool_pincfg_deinit_sd0();
    nutool_pincfg_deinit_spi1();
    nutool_pincfg_deinit_uart2_rs485();
#elif defined(BOARD_USING_NUTFT)
    /* No de-initialization code is required for NuTFT pins */
#endif

    return;
}

/*** (C) COPYRIGHT 2013-2025 Nuvoton Technology Corp. ***/
