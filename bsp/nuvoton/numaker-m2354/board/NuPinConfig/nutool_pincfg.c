/****************************************************************************
 * @file     nutool_pincfg.c
 * @version  V1.21
 * @Date     2020/11/11-12:06:36
 * @brief    NuMicro generated code file
 *
 * Copyright (C) 2013-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

/********************
MCU:M2354KJFAE(LQFP128)
Pin Configuration:
Pin1:SD0_DAT3
Pin2:SD0_DAT2
Pin3:SD0_DAT1
Pin4:SD0_DAT0
Pin5:EPWM1_CH0
Pin6:EPWM1_CH1
Pin7:EPWM1_CH2
Pin8:EPWM1_CH3
Pin9:SD0_CLK
Pin10:SD0_CMD
Pin15:UART1_TXD
Pin16:UART1_RXD
Pin21:I2C1_SCL
Pin22:I2C1_SDA
Pin25:I2S0_BCLK
Pin26:I2S0_MCLK
Pin27:I2S0_DI
Pin28:I2S0_DO
Pin29:I2S0_LRCK
Pin48:UART4_TXD
Pin49:UART4_RXD
Pin50:UART0_TXD
Pin51:UART0_RXD
Pin57:SPI0_SS
Pin58:SPI0_CLK
Pin59:SPI0_MISO
Pin60:SPI0_MOSI
Pin65:ICE_DAT
Pin66:ICE_CLK
Pin73:EPWM1_CH4
Pin74:EPWM1_CH5
Pin93:USB_VBUS
Pin94:USB_D-
Pin95:USB_D+
Pin96:USB_OTG_ID
Pin97:EPWM0_CH0
Pin98:EPWM0_CH1
Pin105:SPI1_MISO
Pin106:SPI1_MOSI
Pin107:SPI1_CLK
Pin108:SPI1_SS
Pin109:PH.10
Pin116:USB_VBUS_EN
Pin117:USB_VBUS_ST
Pin119:SD0_nCD
Pin123:EADC0_CH11
Pin124:EADC0_CH10
Pin125:EADC0_CH9
Pin126:EADC0_CH8
Pin127:EADC0_CH7
Pin128:EADC0_CH6
********************/

#include "M2354.h"
#include "rtconfig.h"

void nutool_pincfg_init_eadc0(void)
{
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB11MFP_Msk | SYS_GPB_MFPH_PB10MFP_Msk | SYS_GPB_MFPH_PB9MFP_Msk | SYS_GPB_MFPH_PB8MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB11MFP_EADC0_CH11 | SYS_GPB_MFPH_PB10MFP_EADC0_CH10 | SYS_GPB_MFPH_PB9MFP_EADC0_CH9 | SYS_GPB_MFPH_PB8MFP_EADC0_CH8);
    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB7MFP_Msk | SYS_GPB_MFPL_PB6MFP_Msk);
    SYS->GPB_MFPL |= (SYS_GPB_MFPL_PB7MFP_EADC0_CH7 | SYS_GPB_MFPL_PB6MFP_EADC0_CH6);

    /* Disable digital path on these EADC pins */
    GPIO_DISABLE_DIGITAL_PATH(PB, BIT6 | BIT7 | BIT8 | BIT9 | BIT10 | BIT11);

    return;
}

void nutool_pincfg_deinit_eadc0(void)
{
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB11MFP_Msk | SYS_GPB_MFPH_PB10MFP_Msk | SYS_GPB_MFPH_PB9MFP_Msk | SYS_GPB_MFPH_PB8MFP_Msk);
    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB7MFP_Msk | SYS_GPB_MFPL_PB6MFP_Msk);

    /* Enable digital path on these EADC pins */
    GPIO_ENABLE_DIGITAL_PATH(PB, BIT6 | BIT7 | BIT8 | BIT9 | BIT10 | BIT11);

    return;
}

void nutool_pincfg_init_epwm0(void)
{
    SYS->GPE_MFPL &= ~(SYS_GPE_MFPL_PE7MFP_Msk | SYS_GPE_MFPL_PE6MFP_Msk);
    SYS->GPE_MFPL |= (SYS_GPE_MFPL_PE7MFP_EPWM0_CH0 | SYS_GPE_MFPL_PE6MFP_EPWM0_CH1);

    return;
}

void nutool_pincfg_deinit_epwm0(void)
{
    SYS->GPE_MFPL &= ~(SYS_GPE_MFPL_PE7MFP_Msk | SYS_GPE_MFPL_PE6MFP_Msk);

    return;
}

void nutool_pincfg_init_epwm1(void)
{
    SYS->GPC_MFPH &= ~(SYS_GPC_MFPH_PC12MFP_Msk | SYS_GPC_MFPH_PC11MFP_Msk | SYS_GPC_MFPH_PC10MFP_Msk | SYS_GPC_MFPH_PC9MFP_Msk);
#if !defined(BOARD_USING_LCD_ILI9341)
    SYS->GPC_MFPH |= (SYS_GPC_MFPH_PC12MFP_EPWM1_CH0 | SYS_GPC_MFPH_PC11MFP_EPWM1_CH1 | SYS_GPC_MFPH_PC10MFP_EPWM1_CH2 | SYS_GPC_MFPH_PC9MFP_EPWM1_CH3);
#else
    SYS->GPC_MFPH |= (SYS_GPC_MFPH_PC12MFP_EPWM1_CH0 | SYS_GPC_MFPH_PC10MFP_EPWM1_CH2 | SYS_GPC_MFPH_PC9MFP_EPWM1_CH3);
#endif

    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC1MFP_Msk | SYS_GPC_MFPL_PC0MFP_Msk);
    SYS->GPC_MFPL |= (SYS_GPC_MFPL_PC1MFP_EPWM1_CH4 | SYS_GPC_MFPL_PC0MFP_EPWM1_CH5);

    return;
}

void nutool_pincfg_deinit_epwm1(void)
{
    SYS->GPC_MFPH &= ~(SYS_GPC_MFPH_PC12MFP_Msk | SYS_GPC_MFPH_PC11MFP_Msk | SYS_GPC_MFPH_PC10MFP_Msk | SYS_GPC_MFPH_PC9MFP_Msk);
    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC1MFP_Msk | SYS_GPC_MFPL_PC0MFP_Msk);

    return;
}

void nutool_pincfg_init_i2c1(void)
{
    SYS->GPG_MFPL &= ~(SYS_GPG_MFPL_PG3MFP_Msk | SYS_GPG_MFPL_PG2MFP_Msk);
    SYS->GPG_MFPL |= (SYS_GPG_MFPL_PG3MFP_I2C1_SDA | SYS_GPG_MFPL_PG2MFP_I2C1_SCL);

    return;
}

void nutool_pincfg_deinit_i2c1(void)
{
    SYS->GPG_MFPL &= ~(SYS_GPG_MFPL_PG3MFP_Msk | SYS_GPG_MFPL_PG2MFP_Msk);

    return;
}

void nutool_pincfg_init_i2s0(void)
{
    SYS->GPF_MFPH &= ~(SYS_GPF_MFPH_PF10MFP_Msk | SYS_GPF_MFPH_PF9MFP_Msk | SYS_GPF_MFPH_PF8MFP_Msk);
    SYS->GPF_MFPH |= (SYS_GPF_MFPH_PF10MFP_I2S0_BCLK | SYS_GPF_MFPH_PF9MFP_I2S0_MCLK | SYS_GPF_MFPH_PF8MFP_I2S0_DI);
    SYS->GPF_MFPL &= ~(SYS_GPF_MFPL_PF7MFP_Msk | SYS_GPF_MFPL_PF6MFP_Msk);
    SYS->GPF_MFPL |= (SYS_GPF_MFPL_PF7MFP_I2S0_DO | SYS_GPF_MFPL_PF6MFP_I2S0_LRCK);

    return;
}

void nutool_pincfg_deinit_i2s0(void)
{
    SYS->GPF_MFPH &= ~(SYS_GPF_MFPH_PF10MFP_Msk | SYS_GPF_MFPH_PF9MFP_Msk | SYS_GPF_MFPH_PF8MFP_Msk);
    SYS->GPF_MFPL &= ~(SYS_GPF_MFPL_PF7MFP_Msk | SYS_GPF_MFPL_PF6MFP_Msk);

    return;
}

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

void nutool_pincfg_init_ph(void)
{
    SYS->GPH_MFPH &= ~(SYS_GPH_MFPH_PH10MFP_Msk);
    SYS->GPH_MFPH |= (SYS_GPH_MFPH_PH10MFP_GPIO);

    return;
}

void nutool_pincfg_deinit_ph(void)
{
    SYS->GPH_MFPH &= ~(SYS_GPH_MFPH_PH10MFP_Msk);

    return;
}

void nutool_pincfg_init_sd0(void)
{
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_SD0_nCD);
    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB5MFP_Msk | SYS_GPB_MFPL_PB4MFP_Msk | SYS_GPB_MFPL_PB3MFP_Msk | SYS_GPB_MFPL_PB2MFP_Msk | SYS_GPB_MFPL_PB1MFP_Msk | SYS_GPB_MFPL_PB0MFP_Msk);
    SYS->GPB_MFPL |= (SYS_GPB_MFPL_PB5MFP_SD0_DAT3 | SYS_GPB_MFPL_PB4MFP_SD0_DAT2 | SYS_GPB_MFPL_PB3MFP_SD0_DAT1 | SYS_GPB_MFPL_PB2MFP_SD0_DAT0 | SYS_GPB_MFPL_PB1MFP_SD0_CLK | SYS_GPB_MFPL_PB0MFP_SD0_CMD);

    return;
}

void nutool_pincfg_deinit_sd0(void)
{
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk);
    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB5MFP_Msk | SYS_GPB_MFPL_PB4MFP_Msk | SYS_GPB_MFPL_PB3MFP_Msk | SYS_GPB_MFPL_PB2MFP_Msk | SYS_GPB_MFPL_PB1MFP_Msk | SYS_GPB_MFPL_PB0MFP_Msk);

    return;
}

void nutool_pincfg_init_spi0(void)
{
    SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA3MFP_Msk | SYS_GPA_MFPL_PA2MFP_Msk | SYS_GPA_MFPL_PA1MFP_Msk | SYS_GPA_MFPL_PA0MFP_Msk);
    SYS->GPA_MFPL |= (SYS_GPA_MFPL_PA3MFP_SPI0_SS | SYS_GPA_MFPL_PA2MFP_SPI0_CLK | SYS_GPA_MFPL_PA1MFP_SPI0_MISO | SYS_GPA_MFPL_PA0MFP_SPI0_MOSI);

    return;
}

void nutool_pincfg_deinit_spi0(void)
{
    SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA3MFP_Msk | SYS_GPA_MFPL_PA2MFP_Msk | SYS_GPA_MFPL_PA1MFP_Msk | SYS_GPA_MFPL_PA0MFP_Msk);

    return;
}

void nutool_pincfg_init_spi1(void)
{
    SYS->GPE_MFPL &= ~(SYS_GPE_MFPL_PE1MFP_Msk | SYS_GPE_MFPL_PE0MFP_Msk);
    SYS->GPE_MFPL |= (SYS_GPE_MFPL_PE1MFP_SPI1_MISO | SYS_GPE_MFPL_PE0MFP_SPI1_MOSI);
    SYS->GPH_MFPH &= ~(SYS_GPH_MFPH_PH9MFP_Msk | SYS_GPH_MFPH_PH8MFP_Msk);
    SYS->GPH_MFPH |= (SYS_GPH_MFPH_PH9MFP_SPI1_SS | SYS_GPH_MFPH_PH8MFP_SPI1_CLK);

    return;
}

void nutool_pincfg_deinit_spi1(void)
{
    SYS->GPE_MFPL &= ~(SYS_GPE_MFPL_PE1MFP_Msk | SYS_GPE_MFPL_PE0MFP_Msk);
    SYS->GPH_MFPH &= ~(SYS_GPH_MFPH_PH9MFP_Msk | SYS_GPH_MFPH_PH8MFP_Msk);

    return;
}

void nutool_pincfg_init_uart0(void)
{
    SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA7MFP_Msk | SYS_GPA_MFPL_PA6MFP_Msk);
    SYS->GPA_MFPL |= (SYS_GPA_MFPL_PA7MFP_UART0_TXD | SYS_GPA_MFPL_PA6MFP_UART0_RXD);

    return;
}

void nutool_pincfg_deinit_uart0(void)
{
    SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA7MFP_Msk | SYS_GPA_MFPL_PA6MFP_Msk);

    return;
}

void nutool_pincfg_init_uart1(void)
{
    SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA9MFP_Msk | SYS_GPA_MFPH_PA8MFP_Msk);
    SYS->GPA_MFPH |= (SYS_GPA_MFPH_PA9MFP_UART1_TXD | SYS_GPA_MFPH_PA8MFP_UART1_RXD);

    return;
}

void nutool_pincfg_deinit_uart1(void)
{
    SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA9MFP_Msk | SYS_GPA_MFPH_PA8MFP_Msk);

    return;
}

void nutool_pincfg_init_uart4(void)
{
    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC7MFP_Msk | SYS_GPC_MFPL_PC6MFP_Msk);
    SYS->GPC_MFPL |= (SYS_GPC_MFPL_PC7MFP_UART4_TXD | SYS_GPC_MFPL_PC6MFP_UART4_RXD);

    return;
}

void nutool_pincfg_deinit_uart4(void)
{
    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC7MFP_Msk | SYS_GPC_MFPL_PC6MFP_Msk);

    return;
}

void nutool_pincfg_init_usb(void)
{
    SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA15MFP_Msk | SYS_GPA_MFPH_PA14MFP_Msk | SYS_GPA_MFPH_PA13MFP_Msk | SYS_GPA_MFPH_PA12MFP_Msk);
    SYS->GPA_MFPH |= (SYS_GPA_MFPH_PA15MFP_USB_OTG_ID | SYS_GPA_MFPH_PA14MFP_USB_D_P | SYS_GPA_MFPH_PA13MFP_USB_D_N | SYS_GPA_MFPH_PA12MFP_USB_VBUS);
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB15MFP_Msk | SYS_GPB_MFPH_PB14MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB15MFP_USB_VBUS_EN | SYS_GPB_MFPH_PB14MFP_USB_VBUS_ST);

    return;
}

void nutool_pincfg_deinit_usb(void)
{
    SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA15MFP_Msk | SYS_GPA_MFPH_PA14MFP_Msk | SYS_GPA_MFPH_PA13MFP_Msk | SYS_GPA_MFPH_PA12MFP_Msk);
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB15MFP_Msk | SYS_GPB_MFPH_PB14MFP_Msk);

    return;
}


void pincfg_init_slcd(void)
{
    /*
        Summary of LCD pin usage:
            COM 0~5   : PC.0, PC.1, PC.2, PC.3, PC.4, PC.5
            COM 6~7   : PD.8, PD.9
            SEG 0     : PD.14
            SEG 1~4   : PH.11, PH.10, PH.9, PH.8
            SEG 5~12  : PE.0, PE.1, PE.2, PE.3, PE.4, PE.5, PE.6, PE.7
            SEG 13~14 : PD.6, PD.7
            SEG 15~21 : PG.15, PG.14, PG.13, PG.12, PG.11, PG.10, PG.9
            SEG 22~23 : PE.15, PE.14
            SEG 24~29 : PA.0, PA.1, PA.2, PA.3, PA.4, PA.5
            SEG 30~32 : PE.10, PE.9, PE.8
            SEG 33~36 : PH.7, PH.6, PH.5, PH.4
            SEG 37~39 : PG.4, PG.3, PG.2
    */

    /* COM 0~5 */
    SYS->GPC_MFPL = (SYS->GPC_MFPL &
                     ~(SYS_GPC_MFPL_PC0MFP_Msk | SYS_GPC_MFPL_PC1MFP_Msk | SYS_GPC_MFPL_PC2MFP_Msk | SYS_GPC_MFPL_PC3MFP_Msk |
                       SYS_GPC_MFPL_PC4MFP_Msk | SYS_GPC_MFPL_PC5MFP_Msk)) |
                    (LCD_COM0_PC0 | LCD_COM1_PC1 | LCD_COM2_PC2 | LCD_COM3_PC3 | LCD_COM4_PC4 | LCD_COM5_PC5);
    /* COM 6~7 */
    SYS->GPD_MFPH = (SYS->GPD_MFPH & ~(SYS_GPD_MFPH_PD8MFP_Msk | SYS_GPD_MFPH_PD9MFP_Msk)) |
                    (LCD_COM6_PD8 | LCD_COM7_PD9);

    /* SEG 0 */
    SYS->GPD_MFPH = (SYS->GPD_MFPH & ~SYS_GPD_MFPH_PD14MFP_Msk) | LCD_SEG0_PD14;
    /* SEG 1~4 */
    SYS->GPH_MFPH = (SYS->GPH_MFPH & ~(SYS_GPH_MFPH_PH11MFP_Msk | SYS_GPH_MFPH_PH10MFP_Msk | SYS_GPH_MFPH_PH9MFP_Msk | SYS_GPH_MFPH_PH8MFP_Msk)) |
                    (LCD_SEG1_PH11 | LCD_SEG2_PH10 | LCD_SEG3_PH9 | LCD_SEG4_PH8);
    /* SEG 5~12 */
    SYS->GPE_MFPL = (SYS->GPE_MFPL &
                     ~(SYS_GPE_MFPL_PE0MFP_Msk | SYS_GPE_MFPL_PE1MFP_Msk | SYS_GPE_MFPL_PE2MFP_Msk | SYS_GPE_MFPL_PE3MFP_Msk |
                       SYS_GPE_MFPL_PE4MFP_Msk | SYS_GPE_MFPL_PE5MFP_Msk | SYS_GPE_MFPL_PE6MFP_Msk | SYS_GPE_MFPL_PE7MFP_Msk)) |
                    (LCD_SEG5_PE0 | LCD_SEG6_PE1 | LCD_SEG7_PE2 | LCD_SEG8_PE3 |
                     LCD_SEG9_PE4 | LCD_SEG10_PE5 | LCD_SEG11_PE6 | LCD_SEG12_PE7);
    /* SEG 13~14 */
    SYS->GPD_MFPL = (SYS->GPD_MFPL & ~(SYS_GPD_MFPL_PD6MFP_Msk | SYS_GPD_MFPL_PD7MFP_Msk)) | (LCD_SEG13_PD6 | LCD_SEG14_PD7);
    /* SEG 15~21 */
    SYS->GPG_MFPH = (SYS->GPG_MFPH &
                     ~(SYS_GPG_MFPH_PG15MFP_Msk | SYS_GPG_MFPH_PG14MFP_Msk | SYS_GPG_MFPH_PG13MFP_Msk | SYS_GPG_MFPH_PG12MFP_Msk |
                       SYS_GPG_MFPH_PG11MFP_Msk | SYS_GPG_MFPH_PG10MFP_Msk | SYS_GPG_MFPH_PG9MFP_Msk)) |
                    (LCD_SEG15_PG15 | LCD_SEG16_PG14 | LCD_SEG17_PG13 | LCD_SEG18_PG12 |
                     LCD_SEG19_PG11 | LCD_SEG20_PG10 | LCD_SEG21_PG9);
    /* SEG 22~23 */
    SYS->GPE_MFPH = (SYS->GPE_MFPH & ~(SYS_GPE_MFPH_PE15MFP_Msk | SYS_GPE_MFPH_PE14MFP_Msk)) | (LCD_SEG22_PE15 | LCD_SEG23_PE14);
    /* SEG 24~29 */
    SYS->GPA_MFPL = (SYS->GPA_MFPL &
                     ~(SYS_GPA_MFPL_PA0MFP_Msk | SYS_GPA_MFPL_PA1MFP_Msk | SYS_GPA_MFPL_PA2MFP_Msk | SYS_GPA_MFPL_PA3MFP_Msk |
                       SYS_GPA_MFPL_PA4MFP_Msk | SYS_GPA_MFPL_PA5MFP_Msk)) |
                    (LCD_SEG24_PA0 | LCD_SEG25_PA1 | LCD_SEG26_PA2 | LCD_SEG27_PA3 | LCD_SEG28_PA4 | LCD_SEG29_PA5);
    /* SEG 30~32 */
    SYS->GPE_MFPH = (SYS->GPE_MFPH & ~(SYS_GPE_MFPH_PE10MFP_Msk | SYS_GPE_MFPH_PE9MFP_Msk | SYS_GPE_MFPH_PE8MFP_Msk)) |
                    (LCD_SEG30_PE10 | LCD_SEG31_PE9 | LCD_SEG32_PE8);
    /* SEG 33~36 */
    SYS->GPH_MFPL = (SYS->GPH_MFPL & ~(SYS_GPH_MFPL_PH7MFP_Msk | SYS_GPH_MFPL_PH6MFP_Msk | SYS_GPH_MFPL_PH5MFP_Msk | SYS_GPH_MFPL_PH4MFP_Msk)) |
                    (LCD_SEG33_PH7 | LCD_SEG34_PH6 | LCD_SEG35_PH5 | LCD_SEG36_PH4);
    /* SEG 37~39 */
    SYS->GPG_MFPL = (SYS->GPG_MFPL & ~(SYS_GPG_MFPL_PG4MFP_Msk | SYS_GPG_MFPL_PG3MFP_Msk | SYS_GPG_MFPL_PG2MFP_Msk)) |
                    (LCD_SEG37_PG4 | LCD_SEG38_PG3 | LCD_SEG39_PG2);
}


void nutool_pincfg_init(void)
{
    //SYS->GPA_MFPH = 0xEEEE0077;
    //SYS->GPA_MFPL = 0x77004444;
    //SYS->GPB_MFPH = 0xEF091111;
    //SYS->GPB_MFPL = 0x11333333;
    //SYS->GPC_MFPH = 0x000CCCC0;
    //SYS->GPC_MFPL = 0x550000CC;
    //SYS->GPD_MFPH = 0x00000000;
    //SYS->GPD_MFPL = 0x00000000;
    //SYS->GPE_MFPH = 0x00000000;
    //SYS->GPE_MFPL = 0xCC000066;
    //SYS->GPF_MFPH = 0x00000444;
    //SYS->GPF_MFPL = 0x440000EE;
    //SYS->GPG_MFPH = 0x00000000;
    //SYS->GPG_MFPL = 0x00005500;
    //SYS->GPH_MFPH = 0x00000066;
    //SYS->GPH_MFPL = 0x00000000;

    nutool_pincfg_init_eadc0();
    nutool_pincfg_init_epwm0();
    nutool_pincfg_init_epwm1();
    nutool_pincfg_init_i2c1();
    nutool_pincfg_init_i2s0();
    nutool_pincfg_init_ice();
    nutool_pincfg_init_ph();
    nutool_pincfg_init_sd0();
    nutool_pincfg_init_spi0();
    nutool_pincfg_init_spi1();
    nutool_pincfg_init_uart0();
#if !defined(BOARD_USING_LCD_ILI9341)
    nutool_pincfg_init_uart1();
#endif
    nutool_pincfg_init_uart4();
    nutool_pincfg_init_usb();

#if defined(BSP_USING_SLCD)
    pincfg_init_slcd();
#endif
    return;
}

void nutool_pincfg_deinit(void)
{
    nutool_pincfg_deinit_eadc0();
    nutool_pincfg_deinit_epwm0();
    nutool_pincfg_deinit_epwm1();
    nutool_pincfg_deinit_i2c1();
    nutool_pincfg_deinit_i2s0();
    nutool_pincfg_deinit_ice();
    nutool_pincfg_deinit_ph();
    nutool_pincfg_deinit_sd0();
    nutool_pincfg_deinit_spi0();
    nutool_pincfg_deinit_spi1();
    nutool_pincfg_deinit_uart0();
    nutool_pincfg_deinit_uart1();
    nutool_pincfg_deinit_uart4();
    nutool_pincfg_deinit_usb();

    return;
}
/*** (C) COPYRIGHT 2013-2020 Nuvoton Technology Corp. ***/
