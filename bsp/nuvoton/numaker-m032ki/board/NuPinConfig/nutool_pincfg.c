/****************************************************************************
 * @file     nutool_pincfg.c
 * @version  V1.21
 * @Date     2021/03/03-17:36:00
 * @brief    NuMicro generated code file
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright (C) 2013-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

/********************
MCU:M032KIAAE(LQFP128)
Pin Configuration:
Pin1:ADC0_CH5
Pin2:ADC0_CH4
Pin3:UART1_TXD
Pin4:UART1_RXD
Pin9:ADC0_CH1
Pin10:ADC0_CH0
Pin31:X32_IN
Pin32:X32_OUT
Pin37:XT1_IN
Pin38:XT1_OUT
Pin50:PWM1_CH4
Pin51:PWM1_CH5
Pin55:QSPI0_MISO1
Pin56:QSPI0_MOSI1
Pin57:QSPI0_SS
Pin58:QSPI0_CLK
Pin59:QSPI0_MISO0
Pin60:QSPI0_MOSI0
Pin65:ICE_DAT
Pin66:ICE_CLK
Pin69:PWM1_CH0
Pin70:PWM1_CH1
Pin71:PWM1_CH2
Pin72:PWM1_CH3
Pin73:I2C0_SCL
Pin74:I2C0_SDA
Pin118:UART0_TXD
Pin119:UART0_RXD
Pin127:ADC0_CH7
Pin128:ADC0_CH6
********************/

#include "M031Series.h"
#include "rtconfig.h"

void nutool_pincfg_init_ice(void)
{
    SYS->GPF_MFPL &= ~(SYS_GPF_MFPL_PF1MFP_Msk | SYS_GPF_MFPL_PF0MFP_Msk);
    SYS->GPF_MFPL |= (SYS_GPF_MFPL_PF1MFP_ICE_CLK | SYS_GPF_MFPL_PF0MFP_ICE_DAT);

    return;
}

void nutool_pincfg_deinit_ice(void)
{
    SYS->GPF_MFPL &= ~(SYS_GPF_MFPL_PF1MFP_Msk | SYS_GPF_MFPL_PF0MFP_Msk);

    return;
}

void nutool_pincfg_init_uart0(void)
{
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB13MFP_Msk | SYS_GPB_MFPH_PB12MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB13MFP_UART0_TXD | SYS_GPB_MFPH_PB12MFP_UART0_RXD);

    return;
}

void nutool_pincfg_deinit_uart0(void)
{
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB13MFP_Msk | SYS_GPB_MFPH_PB12MFP_Msk);

    return;
}

void nutool_pincfg_init_x32(void)
{
    SYS->GPF_MFPL &= ~(SYS_GPF_MFPL_PF5MFP_Msk | SYS_GPF_MFPL_PF4MFP_Msk);
    SYS->GPF_MFPL |= (SYS_GPF_MFPL_PF5MFP_X32_IN | SYS_GPF_MFPL_PF4MFP_X32_OUT);

    return;
}

void nutool_pincfg_deinit_x32(void)
{
    SYS->GPF_MFPL &= ~(SYS_GPF_MFPL_PF5MFP_Msk | SYS_GPF_MFPL_PF4MFP_Msk);

    return;
}

void nutool_pincfg_init_xt1(void)
{
    SYS->GPF_MFPL &= ~(SYS_GPF_MFPL_PF3MFP_Msk | SYS_GPF_MFPL_PF2MFP_Msk);
    SYS->GPF_MFPL |= (SYS_GPF_MFPL_PF3MFP_XT1_IN | SYS_GPF_MFPL_PF2MFP_XT1_OUT);

    return;
}

void nutool_pincfg_deinit_xt1(void)
{
    SYS->GPF_MFPL &= ~(SYS_GPF_MFPL_PF3MFP_Msk | SYS_GPF_MFPL_PF2MFP_Msk);

    return;
}

void nutool_pincfg_init_qspi0(void)
{
    SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA0MFP_Msk | SYS_GPA_MFPL_PA1MFP_Msk | SYS_GPA_MFPL_PA2MFP_Msk | SYS_GPA_MFPL_PA3MFP_Msk |
                       SYS_GPA_MFPL_PA4MFP_Msk | SYS_GPA_MFPL_PA5MFP_Msk);

    SYS->GPA_MFPL |= (SYS_GPA_MFPL_PA0MFP_QSPI0_MOSI0 | SYS_GPA_MFPL_PA1MFP_QSPI0_MISO0 |
                      SYS_GPA_MFPL_PA2MFP_QSPI0_CLK | SYS_GPA_MFPL_PA3MFP_QSPI0_SS |
                      SYS_GPA_MFPL_PA4MFP_QSPI0_MOSI1 | SYS_GPA_MFPL_PA5MFP_QSPI0_MISO1);

    /* pull high qspi quad mode pins. */
    GPIO_SetMode(PA, BIT4 | BIT5, GPIO_MODE_QUASI);

}

void nutool_pincfg_init_usci0(void)
{
    SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA8MFP_Msk | SYS_GPA_MFPH_PA9MFP_Msk | SYS_GPA_MFPH_PA10MFP_Msk | SYS_GPA_MFPH_PA11MFP_Msk);

    SYS->GPA_MFPH |= (/*SYS_GPA_MFPH_PA8MFP_USCI0_CTL1 |*/ SYS_GPA_MFPH_PA9MFP_USCI0_DAT1 | SYS_GPA_MFPH_PA10MFP_USCI0_DAT0 | SYS_GPA_MFPH_PA11MFP_USCI0_CLK);
}

void nutool_pincfg_deinit_qspi0(void)
{
    SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA0MFP_Msk | SYS_GPA_MFPL_PA1MFP_Msk | SYS_GPA_MFPL_PA2MFP_Msk | SYS_GPA_MFPL_PA3MFP_Msk |
                       SYS_GPA_MFPL_PA4MFP_Msk | SYS_GPA_MFPL_PA5MFP_Msk);
}

void nutool_pincfg_init_i2c0(void)
{
    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC0MFP_Msk | SYS_GPC_MFPL_PC1MFP_Msk);
    SYS->GPC_MFPL |= (SYS_GPC_MFPL_PC0MFP_I2C0_SDA | SYS_GPC_MFPL_PC1MFP_I2C0_SCL);
}

void nutool_pincfg_deinit_i2c0(void)
{
    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC0MFP_Msk | SYS_GPC_MFPL_PC1MFP_Msk);
}

void nutool_pincfg_init_adc0(void)
{
    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB0MFP_Msk | SYS_GPB_MFPL_PB1MFP_Msk | SYS_GPB_MFPL_PB4MFP_Msk |
                       SYS_GPB_MFPL_PB5MFP_Msk | SYS_GPB_MFPL_PB6MFP_Msk | SYS_GPB_MFPL_PB7MFP_Msk);

    SYS->GPB_MFPL |= (SYS_GPB_MFPL_PB0MFP_ADC_CH0 | SYS_GPB_MFPL_PB1MFP_ADC_CH1 | SYS_GPB_MFPL_PB4MFP_ADC_CH4 |
                      SYS_GPB_MFPL_PB5MFP_ADC_CH5 | SYS_GPB_MFPL_PB6MFP_ADC_CH6 | SYS_GPB_MFPL_PB7MFP_ADC_CH7);

    /* Disable digital path on these ADC pins */
    GPIO_DISABLE_DIGITAL_PATH(PB, BIT0 | BIT1 | BIT4 | BIT5 | BIT6 | BIT7);
}

void nutool_pincfg_deinit_adc0(void)
{
    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB0MFP_Msk | SYS_GPB_MFPL_PB1MFP_Msk | SYS_GPB_MFPL_PB4MFP_Msk |
                       SYS_GPB_MFPL_PB5MFP_Msk | SYS_GPB_MFPL_PB6MFP_Msk | SYS_GPB_MFPL_PB7MFP_Msk);

    /* Enable digital path on these ADC pins */
    GPIO_ENABLE_DIGITAL_PATH(PB, BIT0 | BIT1 | BIT4 | BIT5 | BIT6 | BIT7);
}

void nutool_pincfg_init_pwm0(void)
{
    SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA6MFP_Msk | SYS_GPA_MFPL_PA7MFP_Msk);
    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC2MFP_Msk | SYS_GPC_MFPL_PC3MFP_Msk | SYS_GPC_MFPL_PC4MFP_Msk | SYS_GPC_MFPL_PC5MFP_Msk);

    SYS->GPA_MFPL |= (SYS_GPA_MFPL_PA6MFP_PWM1_CH5 | SYS_GPA_MFPL_PA7MFP_PWM1_CH4);
    SYS->GPC_MFPL |= (SYS_GPC_MFPL_PC2MFP_PWM1_CH3 | SYS_GPC_MFPL_PC3MFP_PWM1_CH2 | SYS_GPC_MFPL_PC4MFP_PWM1_CH1 | SYS_GPC_MFPL_PC5MFP_PWM1_CH0);
}

void nutool_pincfg_deinit_pwm0(void)
{
    SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA6MFP_Msk | SYS_GPA_MFPL_PA7MFP_Msk);
    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC2MFP_Msk | SYS_GPC_MFPL_PC3MFP_Msk | SYS_GPC_MFPL_PC4MFP_Msk | SYS_GPC_MFPL_PC5MFP_Msk);
}

void nutool_pincfg_init_uart1(void)
{
    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB2MFP_Msk | SYS_GPB_MFPL_PB3MFP_Msk);
    SYS->GPB_MFPL |= (SYS_GPB_MFPL_PB2MFP_UART1_RXD | SYS_GPB_MFPL_PB3MFP_UART1_TXD);
}

void nutool_pincfg_deinit_uart1(void)
{
    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB2MFP_Msk | SYS_GPB_MFPL_PB3MFP_Msk);
}

void nutool_pincfg_init(void)
{
    //SYS->GPA_MFPH = 0x00000000UL;
    //SYS->GPA_MFPL = 0xBB333333UL;
    //SYS->GPB_MFPH = 0x00660000UL;
    //SYS->GPB_MFPL = 0x11116611UL;
    //SYS->GPC_MFPH = 0x00000000UL;
    //SYS->GPC_MFPL = 0x00CCCC99UL;
    //SYS->GPD_MFPH = 0x00000000UL;
    //SYS->GPD_MFPL = 0x00000000UL;
    //SYS->GPE_MFPH = 0x00000000UL;
    //SYS->GPE_MFPL = 0x00000000UL;
    //SYS->GPF_MFPH = 0x00000000UL;
    //SYS->GPF_MFPL = 0x00AAAAEEUL;
    //SYS->GPG_MFPH = 0x00000000UL;
    //SYS->GPG_MFPL = 0x00000000UL;
    //SYS->GPH_MFPH = 0x00000000UL;
    //SYS->GPH_MFPL = 0x00000000UL;

    nutool_pincfg_init_ice();
    nutool_pincfg_init_uart0();
    nutool_pincfg_init_x32();
    nutool_pincfg_init_xt1();
    nutool_pincfg_init_qspi0();
#if defined(BOARD_USING_LCD_ILI9341)
    nutool_pincfg_init_usci0();
#endif
    nutool_pincfg_init_i2c0();
    nutool_pincfg_init_adc0();
#if !defined(BOARD_USING_LCD_ILI9341)
    nutool_pincfg_deinit_pwm0();
    nutool_pincfg_deinit_uart1();
#endif

    return;
}

void nutool_pincfg_deinit(void)
{
    nutool_pincfg_deinit_ice();
    nutool_pincfg_deinit_uart0();
    nutool_pincfg_deinit_x32();
    nutool_pincfg_deinit_xt1();
    nutool_pincfg_deinit_qspi0();
    nutool_pincfg_init_usci0();
    nutool_pincfg_deinit_i2c0();
    nutool_pincfg_deinit_adc0();
    nutool_pincfg_deinit_pwm0();
    nutool_pincfg_deinit_uart1();

    return;
}
/*** (C) COPYRIGHT 2013-2020 Nuvoton Technology Corp. ***/
