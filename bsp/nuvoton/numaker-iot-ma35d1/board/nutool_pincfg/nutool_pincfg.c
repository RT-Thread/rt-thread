/****************************************************************************
 * @file     nutool_pincfg.c
 * @version  V1.24
 * @Date     2022/11/01-18:39:48
 * @brief    NuMicro generated code file
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright (C) 2013-2022 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

/********************
MCU:MA35D16F787C(LQFP216)
********************/

#include "ma35d1.h"

void nutool_pincfg_init_adc0(void)
{
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB15MFP_Msk | SYS_GPB_MFPH_PB14MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk | SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB11MFP_Msk | SYS_GPB_MFPH_PB10MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB15MFP_ADC0_CH7 | SYS_GPB_MFPH_PB14MFP_ADC0_CH6 | SYS_GPB_MFPH_PB13MFP_ADC0_CH5 | SYS_GPB_MFPH_PB12MFP_ADC0_CH4 | SYS_GPB_MFPH_PB11MFP_ADC0_CH3 | SYS_GPB_MFPH_PB10MFP_ADC0_CH2);

    PB->MODE &= ~(GPIO_MODE_MODE10_Msk | GPIO_MODE_MODE11_Msk | GPIO_MODE_MODE12_Msk | GPIO_MODE_MODE13_Msk | GPIO_MODE_MODE14_Msk | GPIO_MODE_MODE15_Msk);
    GPIO_DISABLE_DIGITAL_PATH(PB, BIT10 | BIT11 | BIT12 | BIT13 | BIT14 | BIT15);

    return;
}

void nutool_pincfg_deinit_adc0(void)
{
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB15MFP_Msk | SYS_GPB_MFPH_PB14MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk | SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB11MFP_Msk | SYS_GPB_MFPH_PB10MFP_Msk);

    return;
}

void nutool_pincfg_init_can1(void)
{
    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC7MFP_Msk | SYS_GPC_MFPL_PC6MFP_Msk);
    SYS->GPC_MFPL |= (SYS_GPC_MFPL_PC7MFP_CAN1_TXD | SYS_GPC_MFPL_PC6MFP_CAN1_RXD);

    return;
}

void nutool_pincfg_deinit_can1(void)
{
    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC7MFP_Msk | SYS_GPC_MFPL_PC6MFP_Msk);

    return;
}

void nutool_pincfg_init_ccap0(void)
{
    SYS->GPK_MFPH &= ~(SYS_GPK_MFPH_PK11MFP_Msk | SYS_GPK_MFPH_PK10MFP_Msk | SYS_GPK_MFPH_PK9MFP_Msk);
    SYS->GPK_MFPH |= (SYS_GPK_MFPH_PK11MFP_CCAP0_HSYNC | SYS_GPK_MFPH_PK10MFP_CCAP0_PIXCLK | SYS_GPK_MFPH_PK9MFP_CCAP0_SCLK);
    SYS->GPM_MFPH &= ~(SYS_GPM_MFPH_PM11MFP_Msk | SYS_GPM_MFPH_PM10MFP_Msk | SYS_GPM_MFPH_PM9MFP_Msk | SYS_GPM_MFPH_PM8MFP_Msk);
    SYS->GPM_MFPH |= (SYS_GPM_MFPH_PM11MFP_CCAP0_DATA9 | SYS_GPM_MFPH_PM10MFP_CCAP0_DATA8 | SYS_GPM_MFPH_PM9MFP_CCAP0_DATA7 | SYS_GPM_MFPH_PM8MFP_CCAP0_DATA6);
    SYS->GPM_MFPL &= ~(SYS_GPM_MFPL_PM7MFP_Msk | SYS_GPM_MFPL_PM6MFP_Msk | SYS_GPM_MFPL_PM5MFP_Msk | SYS_GPM_MFPL_PM4MFP_Msk | SYS_GPM_MFPL_PM3MFP_Msk | SYS_GPM_MFPL_PM2MFP_Msk | SYS_GPM_MFPL_PM0MFP_Msk);
    SYS->GPM_MFPL |= (SYS_GPM_MFPL_PM7MFP_CCAP0_DATA5 | SYS_GPM_MFPL_PM6MFP_CCAP0_DATA4 | SYS_GPM_MFPL_PM5MFP_CCAP0_DATA3 | SYS_GPM_MFPL_PM4MFP_CCAP0_DATA2 | SYS_GPM_MFPL_PM3MFP_CCAP0_DATA1 | SYS_GPM_MFPL_PM2MFP_CCAP0_DATA0 | SYS_GPM_MFPL_PM0MFP_CCAP0_VSYNC);

    return;
}

void nutool_pincfg_deinit_ccap0(void)
{
    SYS->GPK_MFPH &= ~(SYS_GPK_MFPH_PK11MFP_Msk | SYS_GPK_MFPH_PK10MFP_Msk | SYS_GPK_MFPH_PK9MFP_Msk);
    SYS->GPM_MFPH &= ~(SYS_GPM_MFPH_PM11MFP_Msk | SYS_GPM_MFPH_PM10MFP_Msk | SYS_GPM_MFPH_PM9MFP_Msk | SYS_GPM_MFPH_PM8MFP_Msk);
    SYS->GPM_MFPL &= ~(SYS_GPM_MFPL_PM7MFP_Msk | SYS_GPM_MFPL_PM6MFP_Msk | SYS_GPM_MFPL_PM5MFP_Msk | SYS_GPM_MFPL_PM4MFP_Msk | SYS_GPM_MFPL_PM3MFP_Msk | SYS_GPM_MFPL_PM2MFP_Msk | SYS_GPM_MFPL_PM0MFP_Msk);

    return;
}

void nutool_pincfg_init_hsusb0(void)
{
    SYS->GPF_MFPH &= ~(SYS_GPF_MFPH_PF15MFP_Msk);
    SYS->GPF_MFPH |= (SYS_GPF_MFPH_PF15MFP_HSUSB0_VBUSVLD);

    return;
}

void nutool_pincfg_deinit_hsusb0(void)
{
    SYS->GPF_MFPH &= ~(SYS_GPF_MFPH_PF15MFP_Msk);

    return;
}

void nutool_pincfg_init_hsusbh(void)
{
    SYS->GPL_MFPH &= ~(SYS_GPL_MFPH_PL13MFP_Msk | SYS_GPL_MFPH_PL12MFP_Msk);
    SYS->GPL_MFPH |= (SYS_GPL_MFPH_PL13MFP_HSUSBH_OVC | SYS_GPL_MFPH_PL12MFP_HSUSBH_PWREN);

    return;
}

void nutool_pincfg_deinit_hsusbh(void)
{
    SYS->GPL_MFPH &= ~(SYS_GPL_MFPH_PL13MFP_Msk | SYS_GPL_MFPH_PL12MFP_Msk);

    return;
}

void nutool_pincfg_init_i2c1(void)
{
    SYS->GPN_MFPL &= ~(SYS_GPN_MFPL_PN5MFP_Msk | SYS_GPN_MFPL_PN4MFP_Msk);
    SYS->GPN_MFPL |= (SYS_GPN_MFPL_PN5MFP_I2C1_SCL | SYS_GPN_MFPL_PN4MFP_I2C1_SDA);

    return;
}

void nutool_pincfg_deinit_i2c1(void)
{
    SYS->GPN_MFPL &= ~(SYS_GPN_MFPL_PN5MFP_Msk | SYS_GPN_MFPL_PN4MFP_Msk);

    return;
}

void nutool_pincfg_init_i2c2(void)
{
    SYS->GPN_MFPL &= ~(SYS_GPN_MFPL_PN1MFP_Msk | SYS_GPN_MFPL_PN0MFP_Msk);
    SYS->GPN_MFPL |= (SYS_GPN_MFPL_PN1MFP_I2C2_SCL | SYS_GPN_MFPL_PN0MFP_I2C2_SDA);

    return;
}

void nutool_pincfg_deinit_i2c2(void)
{
    SYS->GPN_MFPL &= ~(SYS_GPN_MFPL_PN1MFP_Msk | SYS_GPN_MFPL_PN0MFP_Msk);

    return;
}

void nutool_pincfg_init_i2c4(void)
{
    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC1MFP_Msk | SYS_GPC_MFPL_PC0MFP_Msk);
    SYS->GPC_MFPL |= (SYS_GPC_MFPL_PC1MFP_I2C4_SCL | SYS_GPC_MFPL_PC0MFP_I2C4_SDA);

    return;
}

void nutool_pincfg_deinit_i2c4(void)
{
    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC1MFP_Msk | SYS_GPC_MFPL_PC0MFP_Msk);

    return;
}

void nutool_pincfg_init_i2c5(void)
{
    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC5MFP_Msk | SYS_GPC_MFPL_PC4MFP_Msk);
    SYS->GPC_MFPL |= (SYS_GPC_MFPL_PC5MFP_I2C5_SCL | SYS_GPC_MFPL_PC4MFP_I2C5_SDA);

    return;
}

void nutool_pincfg_deinit_i2c5(void)
{
    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC5MFP_Msk | SYS_GPC_MFPL_PC4MFP_Msk);

    return;
}

void nutool_pincfg_init_i2s0(void)
{
    SYS->GPG_MFPH &= ~(SYS_GPG_MFPH_PG15MFP_Msk | SYS_GPG_MFPH_PG14MFP_Msk | SYS_GPG_MFPH_PG13MFP_Msk | SYS_GPG_MFPH_PG12MFP_Msk | SYS_GPG_MFPH_PG11MFP_Msk);
    SYS->GPG_MFPH |= (SYS_GPG_MFPH_PG15MFP_I2S0_DO | SYS_GPG_MFPH_PG14MFP_I2S0_DI | SYS_GPG_MFPH_PG13MFP_I2S0_BCLK | SYS_GPG_MFPH_PG12MFP_I2S0_LRCK | SYS_GPG_MFPH_PG11MFP_I2S0_MCLK);

    return;
}

void nutool_pincfg_deinit_i2s0(void)
{
    SYS->GPG_MFPH &= ~(SYS_GPG_MFPH_PG15MFP_Msk | SYS_GPG_MFPH_PG14MFP_Msk | SYS_GPG_MFPH_PG13MFP_Msk | SYS_GPG_MFPH_PG12MFP_Msk | SYS_GPG_MFPH_PG11MFP_Msk);

    return;
}

void nutool_pincfg_init_nand(void)
{
    SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA14MFP_Msk | SYS_GPA_MFPH_PA13MFP_Msk | SYS_GPA_MFPH_PA12MFP_Msk | SYS_GPA_MFPH_PA11MFP_Msk | SYS_GPA_MFPH_PA10MFP_Msk | SYS_GPA_MFPH_PA9MFP_Msk | SYS_GPA_MFPH_PA8MFP_Msk);
    SYS->GPA_MFPH |= (SYS_GPA_MFPH_PA14MFP_NAND_nWP | SYS_GPA_MFPH_PA13MFP_NAND_nCS0 | SYS_GPA_MFPH_PA12MFP_NAND_ALE | SYS_GPA_MFPH_PA11MFP_NAND_CLE | SYS_GPA_MFPH_PA10MFP_NAND_nWE | SYS_GPA_MFPH_PA9MFP_NAND_nRE | SYS_GPA_MFPH_PA8MFP_NAND_RDY0);
    SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA7MFP_Msk | SYS_GPA_MFPL_PA6MFP_Msk | SYS_GPA_MFPL_PA5MFP_Msk | SYS_GPA_MFPL_PA4MFP_Msk | SYS_GPA_MFPL_PA3MFP_Msk | SYS_GPA_MFPL_PA2MFP_Msk | SYS_GPA_MFPL_PA1MFP_Msk | SYS_GPA_MFPL_PA0MFP_Msk);
    SYS->GPA_MFPL |= (SYS_GPA_MFPL_PA7MFP_NAND_DATA7 | SYS_GPA_MFPL_PA6MFP_NAND_DATA6 | SYS_GPA_MFPL_PA5MFP_NAND_DATA5 | SYS_GPA_MFPL_PA4MFP_NAND_DATA4 | SYS_GPA_MFPL_PA3MFP_NAND_DATA3 | SYS_GPA_MFPL_PA2MFP_NAND_DATA2 | SYS_GPA_MFPL_PA1MFP_NAND_DATA1 | SYS_GPA_MFPL_PA0MFP_NAND_DATA0);

    return;
}

void nutool_pincfg_deinit_nand(void)
{
    SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA14MFP_Msk | SYS_GPA_MFPH_PA13MFP_Msk | SYS_GPA_MFPH_PA12MFP_Msk | SYS_GPA_MFPH_PA11MFP_Msk | SYS_GPA_MFPH_PA10MFP_Msk | SYS_GPA_MFPH_PA9MFP_Msk | SYS_GPA_MFPH_PA8MFP_Msk);
    SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA7MFP_Msk | SYS_GPA_MFPL_PA6MFP_Msk | SYS_GPA_MFPL_PA5MFP_Msk | SYS_GPA_MFPL_PA4MFP_Msk | SYS_GPA_MFPL_PA3MFP_Msk | SYS_GPA_MFPL_PA2MFP_Msk | SYS_GPA_MFPL_PA1MFP_Msk | SYS_GPA_MFPL_PA0MFP_Msk);

    return;
}

void nutool_pincfg_init_qspi0(void)
{
    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD5MFP_Msk | SYS_GPD_MFPL_PD4MFP_Msk | SYS_GPD_MFPL_PD3MFP_Msk | SYS_GPD_MFPL_PD2MFP_Msk | SYS_GPD_MFPL_PD1MFP_Msk | SYS_GPD_MFPL_PD0MFP_Msk);
    SYS->GPD_MFPL |= (SYS_GPD_MFPL_PD5MFP_QSPI0_MISO1 | SYS_GPD_MFPL_PD4MFP_QSPI0_MOSI1 | SYS_GPD_MFPL_PD3MFP_QSPI0_MISO0 | SYS_GPD_MFPL_PD2MFP_QSPI0_MOSI0 | SYS_GPD_MFPL_PD1MFP_QSPI0_CLK | SYS_GPD_MFPL_PD0MFP_QSPI0_SS0);

    GPIO_SetDrivingCtl(PD, (BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5), 4);

    return;
}

void nutool_pincfg_deinit_qspi0(void)
{
    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD5MFP_Msk | SYS_GPD_MFPL_PD4MFP_Msk | SYS_GPD_MFPL_PD3MFP_Msk | SYS_GPD_MFPL_PD2MFP_Msk | SYS_GPD_MFPL_PD1MFP_Msk | SYS_GPD_MFPL_PD0MFP_Msk);

    return;
}

void nutool_pincfg_init_rgmii0(void)
{
    SYS->GPE_MFPH &= ~(SYS_GPE_MFPH_PE13MFP_Msk | SYS_GPE_MFPH_PE12MFP_Msk | SYS_GPE_MFPH_PE11MFP_Msk | SYS_GPE_MFPH_PE10MFP_Msk | SYS_GPE_MFPH_PE9MFP_Msk | SYS_GPE_MFPH_PE8MFP_Msk);
    SYS->GPE_MFPH |= (SYS_GPE_MFPH_PE13MFP_RGMII0_TXD3 | SYS_GPE_MFPH_PE12MFP_RGMII0_TXD2 | SYS_GPE_MFPH_PE11MFP_RGMII0_TXCLK | SYS_GPE_MFPH_PE10MFP_RGMII0_RXD3 | SYS_GPE_MFPH_PE9MFP_RGMII0_RXD2 | SYS_GPE_MFPH_PE8MFP_RGMII0_RXD1);
    SYS->GPE_MFPL &= ~(SYS_GPE_MFPL_PE7MFP_Msk | SYS_GPE_MFPL_PE6MFP_Msk | SYS_GPE_MFPL_PE5MFP_Msk | SYS_GPE_MFPL_PE4MFP_Msk | SYS_GPE_MFPL_PE3MFP_Msk | SYS_GPE_MFPL_PE2MFP_Msk | SYS_GPE_MFPL_PE1MFP_Msk | SYS_GPE_MFPL_PE0MFP_Msk);
    SYS->GPE_MFPL |= (SYS_GPE_MFPL_PE7MFP_RGMII0_RXD0 | SYS_GPE_MFPL_PE6MFP_RGMII0_RXCTL | SYS_GPE_MFPL_PE5MFP_RGMII0_RXCLK | SYS_GPE_MFPL_PE4MFP_RGMII0_TXD1 | SYS_GPE_MFPL_PE3MFP_RGMII0_TXD0 | SYS_GPE_MFPL_PE2MFP_RGMII0_TXCTL | SYS_GPE_MFPL_PE1MFP_RGMII0_MDIO | SYS_GPE_MFPL_PE0MFP_RGMII0_MDC);

    /* RGMII Mode */
    SYS->GMAC0MISCR &= ~1;

    /* Set 1.8v */
    GPIO_SetPowerMode(PE, 0x3FFF, 0);

    GPIO_SetPullCtl(PE, 0x3FFF, GPIO_PUSEL_DISABLE);

    GPIO_SetSchmittTriggere(PE, 0x3FDF, 1);   //except clk

    GPIO_SetSlewCtl(PE, 0x3FFF, GPIO_SLEWCTL_NORMAL);

    GPIO_SetDrivingCtl(PE, 0x3FFF, 1);

    return;
}

void nutool_pincfg_deinit_rgmii0(void)
{
    SYS->GPE_MFPH &= ~(SYS_GPE_MFPH_PE13MFP_Msk | SYS_GPE_MFPH_PE12MFP_Msk | SYS_GPE_MFPH_PE11MFP_Msk | SYS_GPE_MFPH_PE10MFP_Msk | SYS_GPE_MFPH_PE9MFP_Msk | SYS_GPE_MFPH_PE8MFP_Msk);
    SYS->GPE_MFPL &= ~(SYS_GPE_MFPL_PE7MFP_Msk | SYS_GPE_MFPL_PE6MFP_Msk | SYS_GPE_MFPL_PE5MFP_Msk | SYS_GPE_MFPL_PE4MFP_Msk | SYS_GPE_MFPL_PE3MFP_Msk | SYS_GPE_MFPL_PE2MFP_Msk | SYS_GPE_MFPL_PE1MFP_Msk | SYS_GPE_MFPL_PE0MFP_Msk);

    return;
}

void nutool_pincfg_init_rmii1(void)
{
    SYS->GPF_MFPH &= ~(SYS_GPF_MFPH_PF9MFP_Msk | SYS_GPF_MFPH_PF8MFP_Msk);
    SYS->GPF_MFPH |= (SYS_GPF_MFPH_PF9MFP_RMII1_RXERR | SYS_GPF_MFPH_PF8MFP_RMII1_RXD1);
    SYS->GPF_MFPL &= ~(SYS_GPF_MFPL_PF7MFP_Msk | SYS_GPF_MFPL_PF6MFP_Msk | SYS_GPF_MFPL_PF5MFP_Msk | SYS_GPF_MFPL_PF4MFP_Msk | SYS_GPF_MFPL_PF3MFP_Msk | SYS_GPF_MFPL_PF2MFP_Msk | SYS_GPF_MFPL_PF1MFP_Msk | SYS_GPF_MFPL_PF0MFP_Msk);
    SYS->GPF_MFPL |= (SYS_GPF_MFPL_PF7MFP_RMII1_RXD0 | SYS_GPF_MFPL_PF6MFP_RMII1_CRSDV | SYS_GPF_MFPL_PF5MFP_RMII1_REFCLK | SYS_GPF_MFPL_PF4MFP_RMII1_TXD1 | SYS_GPF_MFPL_PF3MFP_RMII1_TXD0 | SYS_GPF_MFPL_PF2MFP_RMII1_TXEN | SYS_GPF_MFPL_PF1MFP_RMII1_MDIO | SYS_GPF_MFPL_PF0MFP_RMII1_MDC);

    /* RMII Mode */
    SYS->GMAC1MISCR |= 1;

    return;
}

void nutool_pincfg_deinit_rmii1(void)
{
    SYS->GPF_MFPH &= ~(SYS_GPF_MFPH_PF9MFP_Msk | SYS_GPF_MFPH_PF8MFP_Msk);
    SYS->GPF_MFPL &= ~(SYS_GPF_MFPL_PF7MFP_Msk | SYS_GPF_MFPL_PF6MFP_Msk | SYS_GPF_MFPL_PF5MFP_Msk | SYS_GPF_MFPL_PF4MFP_Msk | SYS_GPF_MFPL_PF3MFP_Msk | SYS_GPF_MFPL_PF2MFP_Msk | SYS_GPF_MFPL_PF1MFP_Msk | SYS_GPF_MFPL_PF0MFP_Msk);

    return;
}

void nutool_pincfg_init_sd1(void)
{
    SYS->GPJ_MFPH &= ~(SYS_GPJ_MFPH_PJ11MFP_Msk | SYS_GPJ_MFPH_PJ10MFP_Msk | SYS_GPJ_MFPH_PJ9MFP_Msk | SYS_GPJ_MFPH_PJ8MFP_Msk);
    SYS->GPJ_MFPH |= (SYS_GPJ_MFPH_PJ11MFP_SD1_DAT3 | SYS_GPJ_MFPH_PJ10MFP_SD1_DAT2 | SYS_GPJ_MFPH_PJ9MFP_SD1_DAT1 | SYS_GPJ_MFPH_PJ8MFP_SD1_DAT0);
    SYS->GPJ_MFPL &= ~(SYS_GPJ_MFPL_PJ7MFP_Msk | SYS_GPJ_MFPL_PJ6MFP_Msk | SYS_GPJ_MFPL_PJ5MFP_Msk);
    SYS->GPJ_MFPL |= (SYS_GPJ_MFPL_PJ7MFP_SD1_CLK | SYS_GPJ_MFPL_PJ6MFP_SD1_CMD | SYS_GPJ_MFPL_PJ5MFP_SD1_nCD);

    return;
}

void nutool_pincfg_deinit_sd1(void)
{
    SYS->GPJ_MFPH &= ~(SYS_GPJ_MFPH_PJ11MFP_Msk | SYS_GPJ_MFPH_PJ10MFP_Msk | SYS_GPJ_MFPH_PJ9MFP_Msk | SYS_GPJ_MFPH_PJ8MFP_Msk);
    SYS->GPJ_MFPL &= ~(SYS_GPJ_MFPL_PJ7MFP_Msk | SYS_GPJ_MFPL_PJ6MFP_Msk | SYS_GPJ_MFPL_PJ5MFP_Msk);

    return;
}

void nutool_pincfg_init_spi0(void)
{
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB9MFP_Msk | SYS_GPB_MFPH_PB8MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB9MFP_SPI0_CLK | SYS_GPB_MFPH_PB8MFP_SPI0_SS1);
    SYS->GPL_MFPH &= ~(SYS_GPL_MFPH_PL15MFP_Msk | SYS_GPL_MFPH_PL14MFP_Msk);
    SYS->GPL_MFPH |= (SYS_GPL_MFPH_PL15MFP_SPI0_MISO | SYS_GPL_MFPH_PL14MFP_SPI0_MOSI);

    return;
}

void nutool_pincfg_deinit_spi0(void)
{
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB9MFP_Msk | SYS_GPB_MFPH_PB8MFP_Msk);
    SYS->GPL_MFPH &= ~(SYS_GPL_MFPH_PL15MFP_Msk | SYS_GPL_MFPH_PL14MFP_Msk);

    return;
}

void nutool_pincfg_init_spi2(void)
{
    SYS->GPG_MFPH &= ~(SYS_GPG_MFPH_PG10MFP_Msk | SYS_GPG_MFPH_PG9MFP_Msk | SYS_GPG_MFPH_PG8MFP_Msk);
    SYS->GPG_MFPH |= (SYS_GPG_MFPH_PG10MFP_SPI2_MOSI | SYS_GPG_MFPH_PG9MFP_SPI2_CLK | SYS_GPG_MFPH_PG8MFP_SPI2_SS0);
    SYS->GPK_MFPL &= ~(SYS_GPK_MFPL_PK4MFP_Msk);
    SYS->GPK_MFPL |= (SYS_GPK_MFPL_PK4MFP_SPI2_MISO);

    return;
}

void nutool_pincfg_deinit_spi2(void)
{
    SYS->GPG_MFPH &= ~(SYS_GPG_MFPH_PG10MFP_Msk | SYS_GPG_MFPH_PG9MFP_Msk | SYS_GPG_MFPH_PG8MFP_Msk);
    SYS->GPK_MFPL &= ~(SYS_GPK_MFPL_PK4MFP_Msk);

    return;
}

void nutool_pincfg_init_uart0(void)
{
    SYS->GPE_MFPH &= ~(SYS_GPE_MFPH_PE15MFP_Msk | SYS_GPE_MFPH_PE14MFP_Msk);
    SYS->GPE_MFPH |= (SYS_GPE_MFPH_PE15MFP_UART0_RXD | SYS_GPE_MFPH_PE14MFP_UART0_TXD);

    return;
}

void nutool_pincfg_deinit_uart0(void)
{
    SYS->GPE_MFPH &= ~(SYS_GPE_MFPH_PE15MFP_Msk | SYS_GPE_MFPH_PE14MFP_Msk);

    return;
}

void nutool_pincfg_init_uart10(void)
{
    SYS->GPH_MFPL &= ~(SYS_GPH_MFPL_PH7MFP_Msk | SYS_GPH_MFPL_PH6MFP_Msk | SYS_GPH_MFPL_PH5MFP_Msk | SYS_GPH_MFPL_PH4MFP_Msk);
    SYS->GPH_MFPL |= (SYS_GPH_MFPL_PH7MFP_UART10_TXD | SYS_GPH_MFPL_PH6MFP_UART10_RXD | SYS_GPH_MFPL_PH5MFP_UART10_nRTS | SYS_GPH_MFPL_PH4MFP_UART10_nCTS);

    return;
}

void nutool_pincfg_deinit_uart10(void)
{
    SYS->GPH_MFPL &= ~(SYS_GPH_MFPL_PH7MFP_Msk | SYS_GPH_MFPL_PH6MFP_Msk | SYS_GPH_MFPL_PH5MFP_Msk | SYS_GPH_MFPL_PH4MFP_Msk);

    return;
}

void nutool_pincfg_init_uart12(void)
{
    SYS->GPC_MFPH &= ~(SYS_GPC_MFPH_PC15MFP_Msk | SYS_GPC_MFPH_PC14MFP_Msk | SYS_GPC_MFPH_PC13MFP_Msk);
    SYS->GPC_MFPH |= (SYS_GPC_MFPH_PC15MFP_UART12_TXD | SYS_GPC_MFPH_PC14MFP_UART12_RXD | SYS_GPC_MFPH_PC13MFP_UART12_nRTS);

    return;
}

void nutool_pincfg_deinit_uart12(void)
{
    SYS->GPC_MFPH &= ~(SYS_GPC_MFPH_PC15MFP_Msk | SYS_GPC_MFPH_PC14MFP_Msk | SYS_GPC_MFPH_PC13MFP_Msk);

    return;
}

void nutool_pincfg_init_uart13(void)
{
    SYS->GPH_MFPH &= ~(SYS_GPH_MFPH_PH13MFP_Msk | SYS_GPH_MFPH_PH12MFP_Msk);
    SYS->GPH_MFPH |= (SYS_GPH_MFPH_PH13MFP_UART13_TXD | SYS_GPH_MFPH_PH12MFP_UART13_RXD);

    return;
}

void nutool_pincfg_deinit_uart13(void)
{
    SYS->GPH_MFPH &= ~(SYS_GPH_MFPH_PH13MFP_Msk | SYS_GPH_MFPH_PH12MFP_Msk);

    return;
}

void nutool_pincfg_init_uart14(void)
{
    SYS->GPH_MFPH &= ~(SYS_GPH_MFPH_PH15MFP_Msk | SYS_GPH_MFPH_PH14MFP_Msk);
    SYS->GPH_MFPH |= (SYS_GPH_MFPH_PH15MFP_UART14_TXD | SYS_GPH_MFPH_PH14MFP_UART14_RXD);

    return;
}

void nutool_pincfg_deinit_uart14(void)
{
    SYS->GPH_MFPH &= ~(SYS_GPH_MFPH_PH15MFP_Msk | SYS_GPH_MFPH_PH14MFP_Msk);

    return;
}

void nutool_pincfg_init(void)
{
    //SYS->GPA_MFPH = 0x06666666UL;
    //SYS->GPA_MFPL = 0x66666666UL;
    //SYS->GPB_MFPH = 0x88888855UL;
    //SYS->GPC_MFPH = 0x22200000UL;
    //SYS->GPC_MFPL = 0x33440044UL;
    //SYS->GPD_MFPH = 0x00000000UL;
    //SYS->GPD_MFPL = 0x00555555UL;
    //SYS->GPE_MFPH = 0x11888888UL;
    //SYS->GPE_MFPL = 0x88888888UL;
    //SYS->GPF_MFPH = 0x10000099UL;
    //SYS->GPF_MFPL = 0x99999999UL;
    //SYS->GPG_MFPH = 0x55555555UL;
    //SYS->GPG_MFPL = 0x00000000UL;
    //SYS->GPH_MFPH = 0x22330000UL;
    //SYS->GPH_MFPL = 0x22220000UL;
    //SYS->GPI_MFPH = 0x00000000UL;
    //SYS->GPJ_MFPH = 0x00006666UL;
    //SYS->GPJ_MFPL = 0x66600000UL;
    //SYS->GPK_MFPH = 0x00006660UL;
    //SYS->GPK_MFPL = 0x00050000UL;
    //SYS->GPL_MFPH = 0x55990000UL;
    //SYS->GPM_MFPH = 0x00006666UL;
    //SYS->GPM_MFPL = 0x66666606UL;
    //SYS->GPN_MFPH = 0x00000000UL;
    //SYS->GPN_MFPL = 0x00440044UL;

    nutool_pincfg_init_adc0();
    nutool_pincfg_init_can1();
    nutool_pincfg_init_ccap0();
    nutool_pincfg_init_hsusb0();
    nutool_pincfg_init_hsusbh();
    nutool_pincfg_init_i2c1();
    nutool_pincfg_init_i2c2();
    nutool_pincfg_init_i2c4();
    nutool_pincfg_init_i2c5();
    nutool_pincfg_init_i2s0();
    nutool_pincfg_init_nand();
    nutool_pincfg_init_qspi0();
    nutool_pincfg_init_rgmii0();
    nutool_pincfg_init_rmii1();
    nutool_pincfg_init_sd1();
    nutool_pincfg_init_spi0();
    nutool_pincfg_init_spi2();
    nutool_pincfg_init_uart0();
    nutool_pincfg_init_uart10();
    nutool_pincfg_init_uart12();
    nutool_pincfg_init_uart13();
    nutool_pincfg_init_uart14();

    return;
}

void nutool_pincfg_deinit(void)
{
    nutool_pincfg_deinit_adc0();
    nutool_pincfg_deinit_can1();
    nutool_pincfg_deinit_ccap0();
    nutool_pincfg_deinit_hsusb0();
    nutool_pincfg_deinit_hsusbh();
    nutool_pincfg_deinit_i2c1();
    nutool_pincfg_deinit_i2c2();
    nutool_pincfg_deinit_i2c4();
    nutool_pincfg_deinit_i2c5();
    nutool_pincfg_deinit_i2s0();
    nutool_pincfg_deinit_nand();
    nutool_pincfg_deinit_qspi0();
    nutool_pincfg_deinit_rgmii0();
    nutool_pincfg_deinit_rmii1();
    nutool_pincfg_deinit_sd1();
    nutool_pincfg_deinit_spi0();
    nutool_pincfg_deinit_spi2();
    nutool_pincfg_deinit_uart0();
    nutool_pincfg_deinit_uart10();
    nutool_pincfg_deinit_uart12();
    nutool_pincfg_deinit_uart13();
    nutool_pincfg_deinit_uart14();

    return;
}

/*** (C) COPYRIGHT 2013-2022 Nuvoton Technology Corp. ***/
