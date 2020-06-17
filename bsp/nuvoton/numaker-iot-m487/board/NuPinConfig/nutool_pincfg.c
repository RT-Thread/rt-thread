/****************************************************************************
 * @file     nutool_pincfg.c
 * @version  V1.20
 * @Date     2020/04/08-17:46:57
 * @brief    NuMicro generated code file
 *
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2013-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

/********************
MCU:M487JIDAE(LQFP144)
********************/

#include "M480.h"

void nutool_pincfg_init_clko(void)
{
    SYS->GPD_MFPH &= ~(SYS_GPD_MFPH_PD12MFP_Msk);
    SYS->GPD_MFPH |= (SYS_GPD_MFPH_PD12MFP_CLKO);

    return;
}

void nutool_pincfg_deinit_clko(void)
{
    SYS->GPD_MFPH &= ~(SYS_GPD_MFPH_PD12MFP_Msk);

    return;
}

void nutool_pincfg_init_eadc0(void)
{
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB14MFP_Msk | SYS_GPB_MFPH_PB9MFP_Msk | SYS_GPB_MFPH_PB8MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB14MFP_EADC0_CH14 | SYS_GPB_MFPH_PB9MFP_EADC0_CH9 | SYS_GPB_MFPH_PB8MFP_EADC0_CH8);
    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB7MFP_Msk | SYS_GPB_MFPL_PB6MFP_Msk | SYS_GPB_MFPL_PB1MFP_Msk | SYS_GPB_MFPL_PB0MFP_Msk);
    SYS->GPB_MFPL |= (SYS_GPB_MFPL_PB7MFP_EADC0_CH7 | SYS_GPB_MFPL_PB6MFP_EADC0_CH6 | SYS_GPB_MFPL_PB1MFP_EADC0_CH1 | SYS_GPB_MFPL_PB0MFP_EADC0_CH0);

    /* Disable digital path on these EADC pins */
    GPIO_DISABLE_DIGITAL_PATH(PB, BIT0 | BIT1 | BIT6 | BIT7 | BIT8 | BIT9 | BIT14);

    return;
}

void nutool_pincfg_deinit_eadc0(void)
{
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB14MFP_Msk | SYS_GPB_MFPH_PB9MFP_Msk | SYS_GPB_MFPH_PB8MFP_Msk);
    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB7MFP_Msk | SYS_GPB_MFPL_PB6MFP_Msk | SYS_GPB_MFPL_PB1MFP_Msk | SYS_GPB_MFPL_PB0MFP_Msk);

    return;
}

void nutool_pincfg_init_emac(void)
{
    SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA7MFP_Msk | SYS_GPA_MFPL_PA6MFP_Msk);
    SYS->GPA_MFPL |= (SYS_GPA_MFPL_PA7MFP_EMAC_RMII_CRSDV | SYS_GPA_MFPL_PA6MFP_EMAC_RMII_RXERR);
    SYS->GPC_MFPH &= ~(SYS_GPC_MFPH_PC8MFP_Msk);
    SYS->GPC_MFPH |= (SYS_GPC_MFPH_PC8MFP_EMAC_RMII_REFCLK);
    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC7MFP_Msk | SYS_GPC_MFPL_PC6MFP_Msk);
    SYS->GPC_MFPL |= (SYS_GPC_MFPL_PC7MFP_EMAC_RMII_RXD0 | SYS_GPC_MFPL_PC6MFP_EMAC_RMII_RXD1);
    SYS->GPE_MFPH &= ~(SYS_GPE_MFPH_PE12MFP_Msk | SYS_GPE_MFPH_PE11MFP_Msk | SYS_GPE_MFPH_PE10MFP_Msk | SYS_GPE_MFPH_PE9MFP_Msk | SYS_GPE_MFPH_PE8MFP_Msk);
    SYS->GPE_MFPH |= (SYS_GPE_MFPH_PE12MFP_EMAC_RMII_TXEN | SYS_GPE_MFPH_PE11MFP_EMAC_RMII_TXD1 | SYS_GPE_MFPH_PE10MFP_EMAC_RMII_TXD0 | SYS_GPE_MFPH_PE9MFP_EMAC_RMII_MDIO | SYS_GPE_MFPH_PE8MFP_EMAC_RMII_MDC);

    /* Enable high slew rate on all RMII TX output pins */
    GPIO_SetSlewCtl(PE, BIT10 | BIT11 | BIT12, GPIO_SLEWCTL_HIGH);

    return;
}

void nutool_pincfg_deinit_emac(void)
{
    SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA7MFP_Msk | SYS_GPA_MFPL_PA6MFP_Msk);
    SYS->GPC_MFPH &= ~(SYS_GPC_MFPH_PC8MFP_Msk);
    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC7MFP_Msk | SYS_GPC_MFPL_PC6MFP_Msk);
    SYS->GPE_MFPH &= ~(SYS_GPE_MFPH_PE12MFP_Msk | SYS_GPE_MFPH_PE11MFP_Msk | SYS_GPE_MFPH_PE10MFP_Msk | SYS_GPE_MFPH_PE9MFP_Msk | SYS_GPE_MFPH_PE8MFP_Msk);

    return;
}

void nutool_pincfg_init_epwm0(void)
{
    SYS->GPD_MFPH &= ~(SYS_GPD_MFPH_PD14MFP_Msk);
    SYS->GPD_MFPH |= (SYS_GPD_MFPH_PD14MFP_EPWM0_CH4);

    return;
}

void nutool_pincfg_deinit_epwm0(void)
{
    SYS->GPD_MFPH &= ~(SYS_GPD_MFPH_PD14MFP_Msk);

    return;
}

void nutool_pincfg_init_hsusb(void)
{
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB11MFP_Msk | SYS_GPB_MFPH_PB10MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB11MFP_HSUSB_VBUS_ST | SYS_GPB_MFPH_PB10MFP_HSUSB_VBUS_EN);

    return;
}

void nutool_pincfg_deinit_hsusb(void)
{
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB11MFP_Msk | SYS_GPB_MFPH_PB10MFP_Msk);

    return;
}

void nutool_pincfg_init_i2c0(void)
{
    SYS->GPG_MFPL &= ~(SYS_GPG_MFPL_PG1MFP_Msk | SYS_GPG_MFPL_PG0MFP_Msk);
    SYS->GPG_MFPL |= (SYS_GPG_MFPL_PG1MFP_I2C0_SDA | SYS_GPG_MFPL_PG0MFP_I2C0_SCL);

    GPIO_SetPullCtl(PG, BIT0 | BIT1, GPIO_PUSEL_PULL_UP);

    return;
}

void nutool_pincfg_deinit_i2c0(void)
{
    SYS->GPG_MFPL &= ~(SYS_GPG_MFPL_PG1MFP_Msk | SYS_GPG_MFPL_PG0MFP_Msk);

    return;
}

void nutool_pincfg_init_i2c1(void)
{
    SYS->GPG_MFPL &= ~(SYS_GPG_MFPL_PG3MFP_Msk | SYS_GPG_MFPL_PG2MFP_Msk);
    SYS->GPG_MFPL |= (SYS_GPG_MFPL_PG3MFP_I2C1_SDA | SYS_GPG_MFPL_PG2MFP_I2C1_SCL);

    GPIO_SetPullCtl(PG, BIT2 | BIT3, GPIO_PUSEL_PULL_UP);

    return;
}

void nutool_pincfg_deinit_i2c1(void)
{
    SYS->GPG_MFPL &= ~(SYS_GPG_MFPL_PG3MFP_Msk | SYS_GPG_MFPL_PG2MFP_Msk);

    return;
}

void nutool_pincfg_init_i2c2(void)
{
    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD1MFP_Msk | SYS_GPD_MFPL_PD0MFP_Msk);
    SYS->GPD_MFPL |= (SYS_GPD_MFPL_PD1MFP_I2C2_SCL | SYS_GPD_MFPL_PD0MFP_I2C2_SDA);

    GPIO_SetPullCtl(PD, BIT0 | BIT1, GPIO_PUSEL_PULL_UP);

    return;
}

void nutool_pincfg_deinit_i2c2(void)
{
    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD1MFP_Msk | SYS_GPD_MFPL_PD0MFP_Msk);

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

void nutool_pincfg_init_pa(void)
{
    SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA5MFP_Msk | SYS_GPA_MFPL_PA4MFP_Msk | SYS_GPA_MFPL_PA3MFP_Msk | SYS_GPA_MFPL_PA2MFP_Msk | SYS_GPA_MFPL_PA1MFP_Msk | SYS_GPA_MFPL_PA0MFP_Msk);
    SYS->GPA_MFPL |= (SYS_GPA_MFPL_PA5MFP_GPIO | SYS_GPA_MFPL_PA4MFP_GPIO | SYS_GPA_MFPL_PA3MFP_GPIO | SYS_GPA_MFPL_PA2MFP_GPIO | SYS_GPA_MFPL_PA1MFP_GPIO | SYS_GPA_MFPL_PA0MFP_GPIO);

    return;
}

void nutool_pincfg_deinit_pa(void)
{
    SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA5MFP_Msk | SYS_GPA_MFPL_PA4MFP_Msk | SYS_GPA_MFPL_PA3MFP_Msk | SYS_GPA_MFPL_PA2MFP_Msk | SYS_GPA_MFPL_PA1MFP_Msk | SYS_GPA_MFPL_PA0MFP_Msk);

    return;
}

void nutool_pincfg_init_pb(void)
{
    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB3MFP_Msk | SYS_GPB_MFPL_PB2MFP_Msk);
    SYS->GPB_MFPL |= (SYS_GPB_MFPL_PB3MFP_GPIO | SYS_GPB_MFPL_PB2MFP_GPIO);

    return;
}

void nutool_pincfg_deinit_pb(void)
{
    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB3MFP_Msk | SYS_GPB_MFPL_PB2MFP_Msk);

    return;
}

void nutool_pincfg_init_pc(void)
{
    SYS->GPC_MFPH &= ~(SYS_GPC_MFPH_PC13MFP_Msk | SYS_GPC_MFPH_PC12MFP_Msk | SYS_GPC_MFPH_PC11MFP_Msk | SYS_GPC_MFPH_PC10MFP_Msk | SYS_GPC_MFPH_PC9MFP_Msk);
    SYS->GPC_MFPH |= (SYS_GPC_MFPH_PC13MFP_GPIO | SYS_GPC_MFPH_PC12MFP_GPIO | SYS_GPC_MFPH_PC11MFP_GPIO | SYS_GPC_MFPH_PC10MFP_GPIO | SYS_GPC_MFPH_PC9MFP_GPIO);

    return;
}

void nutool_pincfg_deinit_pc(void)
{
    SYS->GPC_MFPH &= ~(SYS_GPC_MFPH_PC13MFP_Msk | SYS_GPC_MFPH_PC12MFP_Msk | SYS_GPC_MFPH_PC11MFP_Msk | SYS_GPC_MFPH_PC10MFP_Msk | SYS_GPC_MFPH_PC9MFP_Msk);

    return;
}

void nutool_pincfg_init_pd(void)
{
    SYS->GPD_MFPH &= ~(SYS_GPD_MFPH_PD11MFP_Msk | SYS_GPD_MFPH_PD10MFP_Msk | SYS_GPD_MFPH_PD9MFP_Msk | SYS_GPD_MFPH_PD8MFP_Msk);
    SYS->GPD_MFPH |= (SYS_GPD_MFPH_PD11MFP_GPIO | SYS_GPD_MFPH_PD10MFP_GPIO | SYS_GPD_MFPH_PD9MFP_GPIO | SYS_GPD_MFPH_PD8MFP_GPIO);
    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD3MFP_Msk | SYS_GPD_MFPL_PD2MFP_Msk);
    SYS->GPD_MFPL |= (SYS_GPD_MFPL_PD3MFP_GPIO | SYS_GPD_MFPL_PD2MFP_GPIO);

    return;
}

void nutool_pincfg_deinit_pd(void)
{
    SYS->GPD_MFPH &= ~(SYS_GPD_MFPH_PD11MFP_Msk | SYS_GPD_MFPH_PD10MFP_Msk | SYS_GPD_MFPH_PD9MFP_Msk | SYS_GPD_MFPH_PD8MFP_Msk);
    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD3MFP_Msk | SYS_GPD_MFPL_PD2MFP_Msk);

    return;
}

void nutool_pincfg_init_pe(void)
{
    SYS->GPE_MFPH &= ~(SYS_GPE_MFPH_PE13MFP_Msk);
    SYS->GPE_MFPH |= (SYS_GPE_MFPH_PE13MFP_GPIO);
    SYS->GPE_MFPL &= ~(SYS_GPE_MFPL_PE5MFP_Msk | SYS_GPE_MFPL_PE4MFP_Msk | SYS_GPE_MFPL_PE1MFP_Msk | SYS_GPE_MFPL_PE0MFP_Msk);
    SYS->GPE_MFPL |= (SYS_GPE_MFPL_PE5MFP_GPIO | SYS_GPE_MFPL_PE4MFP_GPIO | SYS_GPE_MFPL_PE1MFP_GPIO | SYS_GPE_MFPL_PE0MFP_GPIO);

    return;
}

void nutool_pincfg_deinit_pe(void)
{
    SYS->GPE_MFPH &= ~(SYS_GPE_MFPH_PE13MFP_Msk);
    SYS->GPE_MFPL &= ~(SYS_GPE_MFPL_PE5MFP_Msk | SYS_GPE_MFPL_PE4MFP_Msk | SYS_GPE_MFPL_PE1MFP_Msk | SYS_GPE_MFPL_PE0MFP_Msk);

    return;
}

void nutool_pincfg_init_pg(void)
{
    SYS->GPG_MFPH &= ~(SYS_GPG_MFPH_PG15MFP_Msk | SYS_GPG_MFPH_PG14MFP_Msk | SYS_GPG_MFPH_PG13MFP_Msk | SYS_GPG_MFPH_PG12MFP_Msk | SYS_GPG_MFPH_PG11MFP_Msk | SYS_GPG_MFPH_PG10MFP_Msk | SYS_GPG_MFPH_PG9MFP_Msk | SYS_GPG_MFPH_PG8MFP_Msk);
    SYS->GPG_MFPH |= (SYS_GPG_MFPH_PG15MFP_GPIO | SYS_GPG_MFPH_PG14MFP_GPIO | SYS_GPG_MFPH_PG13MFP_GPIO | SYS_GPG_MFPH_PG12MFP_GPIO | SYS_GPG_MFPH_PG11MFP_GPIO | SYS_GPG_MFPH_PG10MFP_GPIO | SYS_GPG_MFPH_PG9MFP_GPIO | SYS_GPG_MFPH_PG8MFP_GPIO);
    SYS->GPG_MFPL &= ~(SYS_GPG_MFPL_PG7MFP_Msk | SYS_GPG_MFPL_PG6MFP_Msk | SYS_GPG_MFPL_PG5MFP_Msk | SYS_GPG_MFPL_PG4MFP_Msk);
    SYS->GPG_MFPL |= (SYS_GPG_MFPL_PG7MFP_GPIO | SYS_GPG_MFPL_PG6MFP_GPIO | SYS_GPG_MFPL_PG5MFP_GPIO | SYS_GPG_MFPL_PG4MFP_GPIO);

    return;
}

void nutool_pincfg_deinit_pg(void)
{
    SYS->GPG_MFPH &= ~(SYS_GPG_MFPH_PG15MFP_Msk | SYS_GPG_MFPH_PG14MFP_Msk | SYS_GPG_MFPH_PG13MFP_Msk | SYS_GPG_MFPH_PG12MFP_Msk | SYS_GPG_MFPH_PG11MFP_Msk | SYS_GPG_MFPH_PG10MFP_Msk | SYS_GPG_MFPH_PG9MFP_Msk | SYS_GPG_MFPH_PG8MFP_Msk);
    SYS->GPG_MFPL &= ~(SYS_GPG_MFPL_PG7MFP_Msk | SYS_GPG_MFPL_PG6MFP_Msk | SYS_GPG_MFPL_PG5MFP_Msk | SYS_GPG_MFPL_PG4MFP_Msk);

    return;
}

void nutool_pincfg_init_ph(void)
{
    SYS->GPH_MFPH &= ~(SYS_GPH_MFPH_PH11MFP_Msk | SYS_GPH_MFPH_PH10MFP_Msk);
    SYS->GPH_MFPH |= (SYS_GPH_MFPH_PH11MFP_GPIO | SYS_GPH_MFPH_PH10MFP_GPIO);
    SYS->GPH_MFPL &= ~(SYS_GPH_MFPL_PH3MFP_Msk | SYS_GPH_MFPL_PH2MFP_Msk | SYS_GPH_MFPL_PH1MFP_Msk | SYS_GPH_MFPL_PH0MFP_Msk);
    SYS->GPH_MFPL |= (SYS_GPH_MFPL_PH3MFP_GPIO | SYS_GPH_MFPL_PH2MFP_GPIO | SYS_GPH_MFPL_PH1MFP_GPIO | SYS_GPH_MFPL_PH0MFP_GPIO);

    return;
}

void nutool_pincfg_deinit_ph(void)
{
    SYS->GPH_MFPH &= ~(SYS_GPH_MFPH_PH11MFP_Msk | SYS_GPH_MFPH_PH10MFP_Msk);
    SYS->GPH_MFPL &= ~(SYS_GPH_MFPL_PH3MFP_Msk | SYS_GPH_MFPL_PH2MFP_Msk | SYS_GPH_MFPL_PH1MFP_Msk | SYS_GPH_MFPL_PH0MFP_Msk);

    return;
}

void nutool_pincfg_init_qspi0(void)
{
    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC5MFP_Msk | SYS_GPC_MFPL_PC4MFP_Msk | SYS_GPC_MFPL_PC3MFP_Msk | SYS_GPC_MFPL_PC2MFP_Msk | SYS_GPC_MFPL_PC1MFP_Msk | SYS_GPC_MFPL_PC0MFP_Msk);
    SYS->GPC_MFPL |= (SYS_GPC_MFPL_PC5MFP_QSPI0_MISO1 | SYS_GPC_MFPL_PC4MFP_QSPI0_MOSI1 | SYS_GPC_MFPL_PC3MFP_QSPI0_SS | SYS_GPC_MFPL_PC2MFP_QSPI0_CLK | SYS_GPC_MFPL_PC1MFP_QSPI0_MISO0 | SYS_GPC_MFPL_PC0MFP_QSPI0_MOSI0);

    return;
}

void nutool_pincfg_deinit_qspi0(void)
{
    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC5MFP_Msk | SYS_GPC_MFPL_PC4MFP_Msk | SYS_GPC_MFPL_PC3MFP_Msk | SYS_GPC_MFPL_PC2MFP_Msk | SYS_GPC_MFPL_PC1MFP_Msk | SYS_GPC_MFPL_PC0MFP_Msk);

    return;
}

void nutool_pincfg_init_sd0(void)
{
    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB5MFP_Msk | SYS_GPB_MFPL_PB4MFP_Msk);
    SYS->GPB_MFPL |= (SYS_GPB_MFPL_PB5MFP_SD0_DAT3 | SYS_GPB_MFPL_PB4MFP_SD0_DAT2);
    SYS->GPD_MFPH &= ~(SYS_GPD_MFPH_PD13MFP_Msk);
    SYS->GPD_MFPH |= (SYS_GPD_MFPH_PD13MFP_SD0_nCD);
    SYS->GPE_MFPL &= ~(SYS_GPE_MFPL_PE7MFP_Msk | SYS_GPE_MFPL_PE6MFP_Msk | SYS_GPE_MFPL_PE3MFP_Msk | SYS_GPE_MFPL_PE2MFP_Msk);
    SYS->GPE_MFPL |= (SYS_GPE_MFPL_PE7MFP_SD0_CMD | SYS_GPE_MFPL_PE6MFP_SD0_CLK | SYS_GPE_MFPL_PE3MFP_SD0_DAT1 | SYS_GPE_MFPL_PE2MFP_SD0_DAT0);

    return;
}

void nutool_pincfg_deinit_sd0(void)
{
    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB5MFP_Msk | SYS_GPB_MFPL_PB4MFP_Msk);
    SYS->GPD_MFPH &= ~(SYS_GPD_MFPH_PD13MFP_Msk);
    SYS->GPE_MFPL &= ~(SYS_GPE_MFPL_PE7MFP_Msk | SYS_GPE_MFPL_PE6MFP_Msk | SYS_GPE_MFPL_PE3MFP_Msk | SYS_GPE_MFPL_PE2MFP_Msk);

    return;
}

void nutool_pincfg_init_spi1(void)
{
    SYS->GPH_MFPL &= ~(SYS_GPH_MFPL_PH7MFP_Msk | SYS_GPH_MFPL_PH6MFP_Msk | SYS_GPH_MFPL_PH5MFP_Msk | SYS_GPH_MFPL_PH4MFP_Msk);
    SYS->GPH_MFPL |= (SYS_GPH_MFPL_PH7MFP_SPI1_SS | SYS_GPH_MFPL_PH6MFP_SPI1_CLK | SYS_GPH_MFPL_PH5MFP_SPI1_MOSI | SYS_GPH_MFPL_PH4MFP_SPI1_MISO);

    return;
}

void nutool_pincfg_deinit_spi1(void)
{
    SYS->GPH_MFPL &= ~(SYS_GPH_MFPL_PH7MFP_Msk | SYS_GPH_MFPL_PH6MFP_Msk | SYS_GPH_MFPL_PH5MFP_Msk | SYS_GPH_MFPL_PH4MFP_Msk);

    return;
}

void nutool_pincfg_init_spi2(void)
{
    SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA11MFP_Msk | SYS_GPA_MFPH_PA10MFP_Msk | SYS_GPA_MFPH_PA9MFP_Msk | SYS_GPA_MFPH_PA8MFP_Msk);
    SYS->GPA_MFPH |= (SYS_GPA_MFPH_PA11MFP_SPI2_SS | SYS_GPA_MFPH_PA10MFP_SPI2_CLK | SYS_GPA_MFPH_PA9MFP_SPI2_MISO | SYS_GPA_MFPH_PA8MFP_SPI2_MOSI);

    return;
}

void nutool_pincfg_deinit_spi2(void)
{
    SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA11MFP_Msk | SYS_GPA_MFPH_PA10MFP_Msk | SYS_GPA_MFPH_PA9MFP_Msk | SYS_GPA_MFPH_PA8MFP_Msk);

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

void nutool_pincfg_init_uart1(void)
{
    SYS->GPH_MFPH &= ~(SYS_GPH_MFPH_PH9MFP_Msk | SYS_GPH_MFPH_PH8MFP_Msk);
    SYS->GPH_MFPH |= (SYS_GPH_MFPH_PH9MFP_UART1_RXD | SYS_GPH_MFPH_PH8MFP_UART1_TXD);

    return;
}

void nutool_pincfg_deinit_uart1(void)
{
    SYS->GPH_MFPH &= ~(SYS_GPH_MFPH_PH9MFP_Msk | SYS_GPH_MFPH_PH8MFP_Msk);

    return;
}

void nutool_pincfg_init_uart2(void)
{
    SYS->GPE_MFPH &= ~(SYS_GPE_MFPH_PE15MFP_Msk | SYS_GPE_MFPH_PE14MFP_Msk);
    SYS->GPE_MFPH |= (SYS_GPE_MFPH_PE15MFP_UART2_RXD | SYS_GPE_MFPH_PE14MFP_UART2_TXD);

    return;
}

void nutool_pincfg_deinit_uart2(void)
{
    SYS->GPE_MFPH &= ~(SYS_GPE_MFPH_PE15MFP_Msk | SYS_GPE_MFPH_PE14MFP_Msk);

    return;
}

void nutool_pincfg_init_usb(void)
{
    SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA15MFP_Msk | SYS_GPA_MFPH_PA14MFP_Msk | SYS_GPA_MFPH_PA13MFP_Msk | SYS_GPA_MFPH_PA12MFP_Msk);
    SYS->GPA_MFPH |= (SYS_GPA_MFPH_PA15MFP_USB_OTG_ID | SYS_GPA_MFPH_PA14MFP_USB_D_P | SYS_GPA_MFPH_PA13MFP_USB_D_N | SYS_GPA_MFPH_PA12MFP_USB_VBUS);
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB15MFP_Msk | SYS_GPB_MFPH_PB11MFP_Msk | SYS_GPB_MFPH_PB10MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB15MFP_USB_VBUS_EN | SYS_GPB_MFPH_PB11MFP_HSUSB_VBUS_ST | SYS_GPB_MFPH_PB10MFP_HSUSB_VBUS_EN);
    SYS->GPC_MFPH &= ~(SYS_GPC_MFPH_PC14MFP_Msk);
    SYS->GPC_MFPH |= (SYS_GPC_MFPH_PC14MFP_USB_VBUS_ST);

    return;
}

void nutool_pincfg_deinit_usb(void)
{
    SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA15MFP_Msk | SYS_GPA_MFPH_PA14MFP_Msk | SYS_GPA_MFPH_PA13MFP_Msk | SYS_GPA_MFPH_PA12MFP_Msk);
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB15MFP_Msk | SYS_GPB_MFPH_PB11MFP_Msk | SYS_GPB_MFPH_PB10MFP_Msk);
    SYS->GPC_MFPH &= ~(SYS_GPC_MFPH_PC14MFP_Msk);

    return;
}

void nutool_pincfg_init(void)
{
    //SYS->GPA_MFPH = 0xEEEE4444;
    //SYS->GPA_MFPL = 0x33000000;
    //SYS->GPB_MFPH = 0xE166EE11;
    //SYS->GPB_MFPL = 0x11330011;
    //SYS->GPC_MFPH = 0x0E000003;
    //SYS->GPC_MFPL = 0x33444444;
    //SYS->GPD_MFPH = 0x0B3D0000;
    //SYS->GPD_MFPL = 0x00000066;
    //SYS->GPE_MFPH = 0x33033333;
    //SYS->GPE_MFPL = 0x33003300;
    //SYS->GPF_MFPH = 0x00000000;
    //SYS->GPF_MFPL = 0x000000EE;
    //SYS->GPG_MFPH = 0x00000000;
    //SYS->GPG_MFPL = 0x00005544;
    //SYS->GPH_MFPH = 0x000000AA;
    //SYS->GPH_MFPL = 0x33330000;

    nutool_pincfg_init_clko();
    nutool_pincfg_init_eadc0();
    nutool_pincfg_init_emac();
    nutool_pincfg_init_epwm0();
    nutool_pincfg_init_hsusb();
    nutool_pincfg_init_i2c0();
    nutool_pincfg_init_i2c1();
    nutool_pincfg_init_i2c2();
    nutool_pincfg_init_i2s0();
    nutool_pincfg_init_ice();
    nutool_pincfg_init_pa();
    nutool_pincfg_init_pb();
    nutool_pincfg_init_pc();
    nutool_pincfg_init_pd();
    nutool_pincfg_init_pe();
    nutool_pincfg_init_pg();
    nutool_pincfg_init_ph();
    nutool_pincfg_init_qspi0();
    nutool_pincfg_init_sd0();
    nutool_pincfg_init_spi1();
    nutool_pincfg_init_spi2();
    nutool_pincfg_init_uart0();
    nutool_pincfg_init_uart1();
    nutool_pincfg_init_uart2();
    nutool_pincfg_init_usb();

    return;
}

void nutool_pincfg_deinit(void)
{
    nutool_pincfg_deinit_clko();
    nutool_pincfg_deinit_eadc0();
    nutool_pincfg_deinit_emac();
    nutool_pincfg_deinit_epwm0();
    nutool_pincfg_deinit_hsusb();
    nutool_pincfg_deinit_i2c0();
    nutool_pincfg_deinit_i2c1();
    nutool_pincfg_deinit_i2c2();
    nutool_pincfg_deinit_i2s0();
    nutool_pincfg_deinit_ice();
    nutool_pincfg_deinit_pa();
    nutool_pincfg_deinit_pb();
    nutool_pincfg_deinit_pc();
    nutool_pincfg_deinit_pd();
    nutool_pincfg_deinit_pe();
    nutool_pincfg_deinit_pg();
    nutool_pincfg_deinit_ph();
    nutool_pincfg_deinit_qspi0();
    nutool_pincfg_deinit_sd0();
    nutool_pincfg_deinit_spi1();
    nutool_pincfg_deinit_spi2();
    nutool_pincfg_deinit_uart0();
    nutool_pincfg_deinit_uart1();
    nutool_pincfg_deinit_uart2();
    nutool_pincfg_deinit_usb();

    return;
}
/*** (C) COPYRIGHT 2013-2020 Nuvoton Technology Corp. ***/
