/****************************************************************************
 * @file     nutool_pincfg.c
 * @version  V1.24
 * @Date     2022/09/15-10:20:52
 * @brief    NuMicro generated code file
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright (C) 2013-2022 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

/********************
MCU:M467HJHAE(LQFP176)
Pin Configuration:
Pin1:EPWM0_CH0
Pin2:EPWM0_CH1
Pin3:UART1_TXD
Pin4:UART1_RXD
Pin5:EPWM1_CH0
Pin6:EPWM1_CH1
Pin7:EPWM1_CH2
Pin8:EPWM1_CH3
Pin9:EADC0_CH1
Pin10:EADC0_CH0
Pin13:SPI2_SS
Pin14:SPI2_CLK
Pin15:SPI2_MISO
Pin16:SPI2_MOSI
Pin19:EADC1_CH1
Pin20:EADC1_CH0
Pin23:I2C3_SCL
Pin24:I2C3_SDA
Pin25:I2C1_SCL
Pin26:I2C1_SDA
Pin27:PG.4
Pin28:PI.6
Pin29:SPI1_MISO
Pin30:SPI1_MOSI
Pin31:SPI1_CLK
Pin32:SPI1_SS
Pin34:UART5_TXD
Pin35:UART5_RXD
Pin36:PF.9
Pin37:PF.8
Pin38:UART4_TXD
Pin39:UART4_RXD
Pin41:X32_IN
Pin42:X32_OUT
Pin45:PH.2
Pin46:PH.3
Pin47:PH.4
Pin48:PH.5
Pin49:PH.6
Pin50:PH.7
Pin51:XT1_IN
Pin52:XT1_OUT
Pin55:EMAC0_RMII_MDC
Pin56:EMAC0_RMII_MDIO
Pin57:EMAC0_RMII_TXD0
Pin58:EMAC0_RMII_TXD1
Pin59:EMAC0_RMII_TXEN
Pin61:EMAC0_RMII_REFCLK
Pin62:EMAC0_RMII_RXD0
Pin63:EMAC0_RMII_RXD1
Pin64:EMAC0_RMII_CRSDV
Pin65:EMAC0_RMII_RXERR
Pin66:SPIM_SS
Pin67:SPIM_MISO
Pin68:SPIM_D2
Pin69:SPIM_D3
Pin70:SPIM_CLK
Pin71:SPIM_MOSI
Pin75:QSPI0_MISO1
Pin76:QSPI0_MOSI1
Pin77:QSPI0_SS
Pin78:QSPI0_CLK
Pin79:QSPI0_MISO0
Pin80:QSPI0_MOSI0
Pin82:PE.14
Pin83:PE.15
Pin85:ICE_DAT
Pin86:ICE_CLK
Pin87:PD.9
Pin88:PD.8
Pin89:PC.5
Pin90:PC.4
Pin91:UART2_nRTS
Pin92:UART2_nCTS
Pin93:UART2_TXD
Pin94:UART2_RXD
Pin97:I2C4_SCL
Pin98:I2C4_SDA
Pin99:PG.11
Pin100:PG.12
Pin101:PG.13
Pin102:PG.14
Pin103:PG.15
Pin104:PJ.2
Pin105:PJ.3
Pin106:PJ.4
Pin107:PJ.5
Pin108:PJ.6
Pin109:PJ.7
Pin110:PH.12
Pin111:PH.13
Pin112:PH.14
Pin113:PH.15
Pin114:PD.7
Pin115:PD.6
Pin116:PD.5
Pin117:PD.4
Pin118:PD.3
Pin119:PD.2
Pin120:I2C2_SCL
Pin121:I2C2_SDA
Pin122:SD0_nCD
Pin123:USB_VBUS
Pin124:USB_D-
Pin125:USB_D+
Pin126:USB_OTG_ID
Pin135:SD0_CMD
Pin136:SD0_CLK
Pin137:SD0_DAT3
Pin138:SD0_DAT2
Pin139:SD0_DAT1
Pin140:SD0_DAT0
Pin143:PE.1
Pin144:PE.0
Pin145:PH.8
Pin146:PH.9
Pin147:PH.10
Pin148:EPWM0_CH5
Pin149:EPWM0_CH4
Pin150:PJ.8
Pin151:PJ.9
Pin152:CAN0_TXD
Pin153:CAN0_RXD
Pin154:HSUSB_VBUS_ST
Pin155:HSUSB_VBUS_EN
Pin156:SPI3_SS
Pin157:SPI3_CLK
Pin158:SPI3_MISO
Pin159:SPI3_MOSI
Pin163:USB_VBUS_ST
Pin164:USB_VBUS_EN
Pin166:UART0_TXD
Pin167:UART0_RXD
Pin173:EADC0_CH9
Pin174:EADC0_CH8
Pin175:EADC0_CH7
Pin176:EADC0_CH6
********************/

#include "NuMicro.h"
#include "rtconfig.h"

void nutool_pincfg_init_can0(void)
{
    SYS->GPJ_MFP2 &= ~(SYS_GPJ_MFP2_PJ11MFP_Msk | SYS_GPJ_MFP2_PJ10MFP_Msk);
    SYS->GPJ_MFP2 |= (SYS_GPJ_MFP2_PJ11MFP_CAN0_RXD | SYS_GPJ_MFP2_PJ10MFP_CAN0_TXD);

    return;
}

void nutool_pincfg_deinit_can0(void)
{
    SYS->GPJ_MFP2 &= ~(SYS_GPJ_MFP2_PJ11MFP_Msk | SYS_GPJ_MFP2_PJ10MFP_Msk);

    return;
}

void nutool_pincfg_init_eadc0(void)
{
    SYS->GPB_MFP0 &= ~(SYS_GPB_MFP0_PB1MFP_Msk | SYS_GPB_MFP0_PB0MFP_Msk);
    SYS->GPB_MFP0 |= (SYS_GPB_MFP0_PB1MFP_EADC0_CH1 | SYS_GPB_MFP0_PB0MFP_EADC0_CH0);
    SYS->GPB_MFP1 &= ~(SYS_GPB_MFP1_PB7MFP_Msk | SYS_GPB_MFP1_PB6MFP_Msk);
    SYS->GPB_MFP1 |= (SYS_GPB_MFP1_PB7MFP_EADC0_CH7 | SYS_GPB_MFP1_PB6MFP_EADC0_CH6);
    SYS->GPB_MFP2 &= ~(SYS_GPB_MFP2_PB9MFP_Msk | SYS_GPB_MFP2_PB8MFP_Msk);
    SYS->GPB_MFP2 |= (SYS_GPB_MFP2_PB9MFP_EADC0_CH9 | SYS_GPB_MFP2_PB8MFP_EADC0_CH8);

    /* Disable digital path on these EADC pins */
    GPIO_DISABLE_DIGITAL_PATH(PB, BIT0 | BIT1 | BIT6 | BIT7 | BIT8 | BIT9);

    return;
}

void nutool_pincfg_deinit_eadc0(void)
{
    SYS->GPB_MFP0 &= ~(SYS_GPB_MFP0_PB1MFP_Msk | SYS_GPB_MFP0_PB0MFP_Msk);
    SYS->GPB_MFP1 &= ~(SYS_GPB_MFP1_PB7MFP_Msk | SYS_GPB_MFP1_PB6MFP_Msk);
    SYS->GPB_MFP2 &= ~(SYS_GPB_MFP2_PB9MFP_Msk | SYS_GPB_MFP2_PB8MFP_Msk);

    /* Enable digital path on these EADC pins */
    GPIO_ENABLE_DIGITAL_PATH(PB, BIT0 | BIT1 | BIT6 | BIT7 | BIT8 | BIT9);

    return;
}

void nutool_pincfg_init_eadc1(void)
{
    SYS->GPD_MFP2 &= ~(SYS_GPD_MFP2_PD11MFP_Msk | SYS_GPD_MFP2_PD10MFP_Msk);
    SYS->GPD_MFP2 |= (SYS_GPD_MFP2_PD11MFP_EADC1_CH1 | SYS_GPD_MFP2_PD10MFP_EADC1_CH0);

    /* Disable digital path on these EADC pins */
    GPIO_DISABLE_DIGITAL_PATH(PD, BIT10 | BIT11);

    return;
}

void nutool_pincfg_deinit_eadc1(void)
{
    SYS->GPD_MFP2 &= ~(SYS_GPD_MFP2_PD11MFP_Msk | SYS_GPD_MFP2_PD10MFP_Msk);
    /* Enable digital path on these EADC pins */
    GPIO_ENABLE_DIGITAL_PATH(PD, BIT10 | BIT11);

    return;
}

void nutool_pincfg_init_emac0(void)
{
    SYS->GPA_MFP1 &= ~(SYS_GPA_MFP1_PA7MFP_Msk | SYS_GPA_MFP1_PA6MFP_Msk);
    SYS->GPA_MFP1 |= (SYS_GPA_MFP1_PA7MFP_EMAC0_RMII_CRSDV | SYS_GPA_MFP1_PA6MFP_EMAC0_RMII_RXERR);
    SYS->GPC_MFP1 &= ~(SYS_GPC_MFP1_PC7MFP_Msk | SYS_GPC_MFP1_PC6MFP_Msk);
    SYS->GPC_MFP1 |= (SYS_GPC_MFP1_PC7MFP_EMAC0_RMII_RXD0 | SYS_GPC_MFP1_PC6MFP_EMAC0_RMII_RXD1);
    SYS->GPC_MFP2 &= ~(SYS_GPC_MFP2_PC8MFP_Msk);
    SYS->GPC_MFP2 |= (SYS_GPC_MFP2_PC8MFP_EMAC0_RMII_REFCLK);
    SYS->GPE_MFP2 &= ~(SYS_GPE_MFP2_PE11MFP_Msk | SYS_GPE_MFP2_PE10MFP_Msk | SYS_GPE_MFP2_PE9MFP_Msk | SYS_GPE_MFP2_PE8MFP_Msk);
    SYS->GPE_MFP2 |= (SYS_GPE_MFP2_PE11MFP_EMAC0_RMII_TXD1 | SYS_GPE_MFP2_PE10MFP_EMAC0_RMII_TXD0 | SYS_GPE_MFP2_PE9MFP_EMAC0_RMII_MDIO | SYS_GPE_MFP2_PE8MFP_EMAC0_RMII_MDC);
    SYS->GPE_MFP3 &= ~(SYS_GPE_MFP3_PE12MFP_Msk);
    SYS->GPE_MFP3 |= (SYS_GPE_MFP3_PE12MFP_EMAC0_RMII_TXEN);

    return;
}

void nutool_pincfg_deinit_emac0(void)
{
    SYS->GPA_MFP1 &= ~(SYS_GPA_MFP1_PA7MFP_Msk | SYS_GPA_MFP1_PA6MFP_Msk);
    SYS->GPC_MFP1 &= ~(SYS_GPC_MFP1_PC7MFP_Msk | SYS_GPC_MFP1_PC6MFP_Msk);
    SYS->GPC_MFP2 &= ~(SYS_GPC_MFP2_PC8MFP_Msk);
    SYS->GPE_MFP2 &= ~(SYS_GPE_MFP2_PE11MFP_Msk | SYS_GPE_MFP2_PE10MFP_Msk | SYS_GPE_MFP2_PE9MFP_Msk | SYS_GPE_MFP2_PE8MFP_Msk);
    SYS->GPE_MFP3 &= ~(SYS_GPE_MFP3_PE12MFP_Msk);

    return;
}

void nutool_pincfg_init_epwm0(void)
{
#if defined(BOARD_USING_LCD_ILI9341) && defined(NU_PKG_USING_ILI9341_SPI)
    /* NuTFT LED Pin is PB.5 */
    SYS->GPB_MFP1 &= ~(SYS_GPB_MFP1_PB5MFP_Msk | SYS_GPB_MFP1_PB4MFP_Msk);
    SYS->GPB_MFP1 |= (SYS_GPB_MFP1_PB4MFP_EPWM0_CH1);
#else
    SYS->GPB_MFP1 &= ~(SYS_GPB_MFP1_PB5MFP_Msk | SYS_GPB_MFP1_PB4MFP_Msk);
    SYS->GPB_MFP1 |= (SYS_GPB_MFP1_PB5MFP_EPWM0_CH0 | SYS_GPB_MFP1_PB4MFP_EPWM0_CH1);
#endif
    SYS->GPD_MFP3 &= ~(SYS_GPD_MFP3_PD14MFP_Msk);
    SYS->GPD_MFP3 |= (SYS_GPD_MFP3_PD14MFP_EPWM0_CH4);
    SYS->GPH_MFP2 &= ~(SYS_GPH_MFP2_PH11MFP_Msk);
    SYS->GPH_MFP2 |= (SYS_GPH_MFP2_PH11MFP_EPWM0_CH5);

    return;
}

void nutool_pincfg_deinit_epwm0(void)
{
#if defined(BOARD_USING_LCD_ILI9341) && defined(NU_PKG_USING_ILI9341_SPI)
    SYS->GPB_MFP1 &= ~(SYS_GPB_MFP1_PB4MFP_Msk);
#else
    SYS->GPB_MFP1 &= ~(SYS_GPB_MFP1_PB5MFP_Msk | SYS_GPB_MFP1_PB4MFP_Msk);
#endif
    SYS->GPD_MFP3 &= ~(SYS_GPD_MFP3_PD14MFP_Msk);
    SYS->GPH_MFP2 &= ~(SYS_GPH_MFP2_PH11MFP_Msk);

    return;
}

void nutool_pincfg_init_epwm1(void)
{
    SYS->GPC_MFP2 &= ~(SYS_GPC_MFP2_PC11MFP_Msk | SYS_GPC_MFP2_PC10MFP_Msk | SYS_GPC_MFP2_PC9MFP_Msk);
    SYS->GPC_MFP2 |= (SYS_GPC_MFP2_PC11MFP_EPWM1_CH1 | SYS_GPC_MFP2_PC10MFP_EPWM1_CH2 | SYS_GPC_MFP2_PC9MFP_EPWM1_CH3);
    SYS->GPC_MFP3 &= ~(SYS_GPC_MFP3_PC12MFP_Msk);
    SYS->GPC_MFP3 |= (SYS_GPC_MFP3_PC12MFP_EPWM1_CH0);

    return;
}

void nutool_pincfg_deinit_epwm1(void)
{
    SYS->GPC_MFP2 &= ~(SYS_GPC_MFP2_PC11MFP_Msk | SYS_GPC_MFP2_PC10MFP_Msk | SYS_GPC_MFP2_PC9MFP_Msk);
    SYS->GPC_MFP3 &= ~(SYS_GPC_MFP3_PC12MFP_Msk);

    return;
}

void nutool_pincfg_init_hsusb(void)
{
    SYS->GPJ_MFP3 &= ~(SYS_GPJ_MFP3_PJ13MFP_Msk | SYS_GPJ_MFP3_PJ12MFP_Msk);
    SYS->GPJ_MFP3 |= (SYS_GPJ_MFP3_PJ13MFP_HSUSB_VBUS_EN | SYS_GPJ_MFP3_PJ12MFP_HSUSB_VBUS_ST);

    return;
}

void nutool_pincfg_deinit_hsusb(void)
{
    SYS->GPJ_MFP3 &= ~(SYS_GPJ_MFP3_PJ13MFP_Msk | SYS_GPJ_MFP3_PJ12MFP_Msk);

    return;
}

void nutool_pincfg_init_i2c1(void)
{
    SYS->GPG_MFP0 &= ~(SYS_GPG_MFP0_PG3MFP_Msk | SYS_GPG_MFP0_PG2MFP_Msk);
    SYS->GPG_MFP0 |= (SYS_GPG_MFP0_PG3MFP_I2C1_SDA | SYS_GPG_MFP0_PG2MFP_I2C1_SCL);

    //GPIO_SetPullCtl(PG, BIT2 | BIT3, GPIO_PUSEL_PULL_UP);

    return;
}

void nutool_pincfg_deinit_i2c1(void)
{
    SYS->GPG_MFP0 &= ~(SYS_GPG_MFP0_PG3MFP_Msk | SYS_GPG_MFP0_PG2MFP_Msk);

    return;
}

void nutool_pincfg_init_i2c2(void)
{
    SYS->GPD_MFP0 &= ~(SYS_GPD_MFP0_PD1MFP_Msk | SYS_GPD_MFP0_PD0MFP_Msk);
    SYS->GPD_MFP0 |= (SYS_GPD_MFP0_PD1MFP_I2C2_SCL | SYS_GPD_MFP0_PD0MFP_I2C2_SDA);

    return;
}

void nutool_pincfg_deinit_i2c2(void)
{
    SYS->GPD_MFP0 &= ~(SYS_GPD_MFP0_PD1MFP_Msk | SYS_GPD_MFP0_PD0MFP_Msk);

    return;
}

void nutool_pincfg_init_i2c3(void)
{
    SYS->GPG_MFP0 &= ~(SYS_GPG_MFP0_PG1MFP_Msk | SYS_GPG_MFP0_PG0MFP_Msk);
    SYS->GPG_MFP0 |= (SYS_GPG_MFP0_PG1MFP_I2C3_SDA | SYS_GPG_MFP0_PG0MFP_I2C3_SCL);

    return;
}

void nutool_pincfg_deinit_i2c3(void)
{
    SYS->GPG_MFP0 &= ~(SYS_GPG_MFP0_PG1MFP_Msk | SYS_GPG_MFP0_PG0MFP_Msk);

    return;
}

void nutool_pincfg_init_i2c4(void)
{
    SYS->GPG_MFP2 &= ~(SYS_GPG_MFP2_PG10MFP_Msk | SYS_GPG_MFP2_PG9MFP_Msk);
    SYS->GPG_MFP2 |= (SYS_GPG_MFP2_PG10MFP_I2C4_SDA | SYS_GPG_MFP2_PG9MFP_I2C4_SCL);
    //GPIO_SetPullCtl(PG, BIT9 | BIT10, GPIO_PUSEL_PULL_UP);

    return;
}

void nutool_pincfg_deinit_i2c4(void)
{
    SYS->GPG_MFP2 &= ~(SYS_GPG_MFP2_PG10MFP_Msk | SYS_GPG_MFP2_PG9MFP_Msk);

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

void nutool_pincfg_init_pc(void)
{
    SYS->GPC_MFP1 &= ~(SYS_GPC_MFP1_PC5MFP_Msk | SYS_GPC_MFP1_PC4MFP_Msk);
    SYS->GPC_MFP1 |= (SYS_GPC_MFP1_PC5MFP_GPIO | SYS_GPC_MFP1_PC4MFP_GPIO);

    return;
}

void nutool_pincfg_deinit_pc(void)
{
    SYS->GPC_MFP1 &= ~(SYS_GPC_MFP1_PC5MFP_Msk | SYS_GPC_MFP1_PC4MFP_Msk);

    return;
}

void nutool_pincfg_init_pd(void)
{
    SYS->GPD_MFP0 &= ~(SYS_GPD_MFP0_PD3MFP_Msk | SYS_GPD_MFP0_PD2MFP_Msk);
    SYS->GPD_MFP0 |= (SYS_GPD_MFP0_PD3MFP_GPIO | SYS_GPD_MFP0_PD2MFP_GPIO);
    SYS->GPD_MFP1 &= ~(SYS_GPD_MFP1_PD7MFP_Msk | SYS_GPD_MFP1_PD6MFP_Msk | SYS_GPD_MFP1_PD5MFP_Msk | SYS_GPD_MFP1_PD4MFP_Msk);
    SYS->GPD_MFP1 |= (SYS_GPD_MFP1_PD7MFP_GPIO | SYS_GPD_MFP1_PD6MFP_GPIO | SYS_GPD_MFP1_PD5MFP_GPIO | SYS_GPD_MFP1_PD4MFP_GPIO);
    SYS->GPD_MFP2 &= ~(SYS_GPD_MFP2_PD9MFP_Msk | SYS_GPD_MFP2_PD8MFP_Msk);
    SYS->GPD_MFP2 |= (SYS_GPD_MFP2_PD9MFP_GPIO | SYS_GPD_MFP2_PD8MFP_GPIO);

    return;
}

void nutool_pincfg_deinit_pd(void)
{
    SYS->GPD_MFP0 &= ~(SYS_GPD_MFP0_PD3MFP_Msk | SYS_GPD_MFP0_PD2MFP_Msk);
    SYS->GPD_MFP1 &= ~(SYS_GPD_MFP1_PD7MFP_Msk | SYS_GPD_MFP1_PD6MFP_Msk | SYS_GPD_MFP1_PD5MFP_Msk | SYS_GPD_MFP1_PD4MFP_Msk);
    SYS->GPD_MFP2 &= ~(SYS_GPD_MFP2_PD9MFP_Msk | SYS_GPD_MFP2_PD8MFP_Msk);

    return;
}

void nutool_pincfg_init_pe(void)
{
    SYS->GPE_MFP0 &= ~(SYS_GPE_MFP0_PE1MFP_Msk | SYS_GPE_MFP0_PE0MFP_Msk);
    SYS->GPE_MFP0 |= (SYS_GPE_MFP0_PE1MFP_GPIO | SYS_GPE_MFP0_PE0MFP_GPIO);
    SYS->GPE_MFP3 &= ~(SYS_GPE_MFP3_PE15MFP_Msk | SYS_GPE_MFP3_PE14MFP_Msk);
    SYS->GPE_MFP3 |= (SYS_GPE_MFP3_PE15MFP_GPIO | SYS_GPE_MFP3_PE14MFP_GPIO);

    return;
}

void nutool_pincfg_deinit_pe(void)
{
    SYS->GPE_MFP0 &= ~(SYS_GPE_MFP0_PE1MFP_Msk | SYS_GPE_MFP0_PE0MFP_Msk);
    SYS->GPE_MFP3 &= ~(SYS_GPE_MFP3_PE15MFP_Msk | SYS_GPE_MFP3_PE14MFP_Msk);

    return;
}

void nutool_pincfg_init_pf(void)
{
    SYS->GPF_MFP2 &= ~(SYS_GPF_MFP2_PF9MFP_Msk | SYS_GPF_MFP2_PF8MFP_Msk);
    SYS->GPF_MFP2 |= (SYS_GPF_MFP2_PF9MFP_GPIO | SYS_GPF_MFP2_PF8MFP_GPIO);

    return;
}

void nutool_pincfg_deinit_pf(void)
{
    SYS->GPF_MFP2 &= ~(SYS_GPF_MFP2_PF9MFP_Msk | SYS_GPF_MFP2_PF8MFP_Msk);

    return;
}

void nutool_pincfg_init_pg(void)
{
    SYS->GPG_MFP1 &= ~(SYS_GPG_MFP1_PG4MFP_Msk);
    SYS->GPG_MFP1 |= (SYS_GPG_MFP1_PG4MFP_GPIO);
    SYS->GPG_MFP2 &= ~(SYS_GPG_MFP2_PG11MFP_Msk);
    SYS->GPG_MFP2 |= (SYS_GPG_MFP2_PG11MFP_GPIO);
    SYS->GPG_MFP3 &= ~(SYS_GPG_MFP3_PG15MFP_Msk | SYS_GPG_MFP3_PG14MFP_Msk | SYS_GPG_MFP3_PG13MFP_Msk | SYS_GPG_MFP3_PG12MFP_Msk);
    SYS->GPG_MFP3 |= (SYS_GPG_MFP3_PG15MFP_GPIO | SYS_GPG_MFP3_PG14MFP_GPIO | SYS_GPG_MFP3_PG13MFP_GPIO | SYS_GPG_MFP3_PG12MFP_GPIO);

    return;
}

void nutool_pincfg_deinit_pg(void)
{
    SYS->GPG_MFP1 &= ~(SYS_GPG_MFP1_PG4MFP_Msk);
    SYS->GPG_MFP2 &= ~(SYS_GPG_MFP2_PG11MFP_Msk);
    SYS->GPG_MFP3 &= ~(SYS_GPG_MFP3_PG15MFP_Msk | SYS_GPG_MFP3_PG14MFP_Msk | SYS_GPG_MFP3_PG13MFP_Msk | SYS_GPG_MFP3_PG12MFP_Msk);

    return;
}

void nutool_pincfg_init_ph(void)
{
    SYS->GPH_MFP0 &= ~(SYS_GPH_MFP0_PH3MFP_Msk | SYS_GPH_MFP0_PH2MFP_Msk);
    SYS->GPH_MFP0 |= (SYS_GPH_MFP0_PH3MFP_GPIO | SYS_GPH_MFP0_PH2MFP_GPIO);
    SYS->GPH_MFP1 &= ~(SYS_GPH_MFP1_PH7MFP_Msk | SYS_GPH_MFP1_PH6MFP_Msk | SYS_GPH_MFP1_PH5MFP_Msk | SYS_GPH_MFP1_PH4MFP_Msk);
    SYS->GPH_MFP1 |= (SYS_GPH_MFP1_PH7MFP_GPIO | SYS_GPH_MFP1_PH6MFP_GPIO | SYS_GPH_MFP1_PH5MFP_GPIO | SYS_GPH_MFP1_PH4MFP_GPIO);
    SYS->GPH_MFP2 &= ~(SYS_GPH_MFP2_PH10MFP_Msk | SYS_GPH_MFP2_PH9MFP_Msk | SYS_GPH_MFP2_PH8MFP_Msk);
    SYS->GPH_MFP2 |= (SYS_GPH_MFP2_PH10MFP_GPIO | SYS_GPH_MFP2_PH9MFP_GPIO | SYS_GPH_MFP2_PH8MFP_GPIO);
    SYS->GPH_MFP3 &= ~(SYS_GPH_MFP3_PH15MFP_Msk | SYS_GPH_MFP3_PH14MFP_Msk | SYS_GPH_MFP3_PH13MFP_Msk | SYS_GPH_MFP3_PH12MFP_Msk);
    SYS->GPH_MFP3 |= (SYS_GPH_MFP3_PH15MFP_GPIO | SYS_GPH_MFP3_PH14MFP_GPIO | SYS_GPH_MFP3_PH13MFP_GPIO | SYS_GPH_MFP3_PH12MFP_GPIO);

    return;
}

void nutool_pincfg_deinit_ph(void)
{
    SYS->GPH_MFP0 &= ~(SYS_GPH_MFP0_PH3MFP_Msk | SYS_GPH_MFP0_PH2MFP_Msk);
    SYS->GPH_MFP1 &= ~(SYS_GPH_MFP1_PH7MFP_Msk | SYS_GPH_MFP1_PH6MFP_Msk | SYS_GPH_MFP1_PH5MFP_Msk | SYS_GPH_MFP1_PH4MFP_Msk);
    SYS->GPH_MFP2 &= ~(SYS_GPH_MFP2_PH10MFP_Msk | SYS_GPH_MFP2_PH9MFP_Msk | SYS_GPH_MFP2_PH8MFP_Msk);
    SYS->GPH_MFP3 &= ~(SYS_GPH_MFP3_PH15MFP_Msk | SYS_GPH_MFP3_PH14MFP_Msk | SYS_GPH_MFP3_PH13MFP_Msk | SYS_GPH_MFP3_PH12MFP_Msk);

    return;
}

void nutool_pincfg_init_pi(void)
{
    SYS->GPI_MFP1 &= ~(SYS_GPI_MFP1_PI6MFP_Msk);
    SYS->GPI_MFP1 |= (SYS_GPI_MFP1_PI6MFP_GPIO);

    return;
}

void nutool_pincfg_deinit_pi(void)
{
    SYS->GPI_MFP1 &= ~(SYS_GPI_MFP1_PI6MFP_Msk);

    return;
}

void nutool_pincfg_init_pj(void)
{
    SYS->GPJ_MFP0 &= ~(SYS_GPJ_MFP0_PJ3MFP_Msk | SYS_GPJ_MFP0_PJ2MFP_Msk);
    SYS->GPJ_MFP0 |= (SYS_GPJ_MFP0_PJ3MFP_GPIO | SYS_GPJ_MFP0_PJ2MFP_GPIO);
    SYS->GPJ_MFP1 &= ~(SYS_GPJ_MFP1_PJ7MFP_Msk | SYS_GPJ_MFP1_PJ6MFP_Msk | SYS_GPJ_MFP1_PJ5MFP_Msk | SYS_GPJ_MFP1_PJ4MFP_Msk);
    SYS->GPJ_MFP1 |= (SYS_GPJ_MFP1_PJ7MFP_GPIO | SYS_GPJ_MFP1_PJ6MFP_GPIO | SYS_GPJ_MFP1_PJ5MFP_GPIO | SYS_GPJ_MFP1_PJ4MFP_GPIO);
    SYS->GPJ_MFP2 &= ~(SYS_GPJ_MFP2_PJ9MFP_Msk | SYS_GPJ_MFP2_PJ8MFP_Msk);
    SYS->GPJ_MFP2 |= (SYS_GPJ_MFP2_PJ9MFP_GPIO | SYS_GPJ_MFP2_PJ8MFP_GPIO);

    return;
}

void nutool_pincfg_deinit_pj(void)
{
    SYS->GPJ_MFP0 &= ~(SYS_GPJ_MFP0_PJ3MFP_Msk | SYS_GPJ_MFP0_PJ2MFP_Msk);
    SYS->GPJ_MFP1 &= ~(SYS_GPJ_MFP1_PJ7MFP_Msk | SYS_GPJ_MFP1_PJ6MFP_Msk | SYS_GPJ_MFP1_PJ5MFP_Msk | SYS_GPJ_MFP1_PJ4MFP_Msk);
    SYS->GPJ_MFP2 &= ~(SYS_GPJ_MFP2_PJ9MFP_Msk | SYS_GPJ_MFP2_PJ8MFP_Msk);

    return;
}

#if 1
// Use on-board SPI NOR flash
void nutool_pincfg_init_qspi0(void)
{
    SYS->GPI_MFP3 &= ~(SYS_GPI_MFP3_PI15MFP_Msk | SYS_GPI_MFP3_PI14MFP_Msk | SYS_GPI_MFP3_PI13MFP_Msk | SYS_GPI_MFP3_PI12MFP_Msk);
    SYS->GPI_MFP3 |= (SYS_GPI_MFP3_PI15MFP_QSPI0_CLK | SYS_GPI_MFP3_PI14MFP_QSPI0_SS | SYS_GPI_MFP3_PI13MFP_QSPI0_MOSI1 | SYS_GPI_MFP3_PI12MFP_QSPI0_MISO1);
    SYS->GPJ_MFP0 &= ~(SYS_GPJ_MFP0_PJ1MFP_Msk | SYS_GPJ_MFP0_PJ0MFP_Msk);
    SYS->GPJ_MFP0 |= (SYS_GPJ_MFP0_PJ1MFP_QSPI0_MOSI0 | SYS_GPJ_MFP0_PJ0MFP_QSPI0_MISO0);

    return;
}

void nutool_pincfg_deinit_qspi0(void)
{
    SYS->GPI_MFP3 &= ~(SYS_GPI_MFP3_PI15MFP_Msk | SYS_GPI_MFP3_PI14MFP_Msk | SYS_GPI_MFP3_PI13MFP_Msk | SYS_GPI_MFP3_PI12MFP_Msk);
    SYS->GPJ_MFP0 &= ~(SYS_GPJ_MFP0_PJ1MFP_Msk | SYS_GPJ_MFP0_PJ0MFP_Msk);

    return;
}
#else
//UNO interface pins
void nutool_pincfg_init_qspi0(void)
{
    SYS->GPA_MFP0 &= ~(SYS_GPA_MFP0_PA3MFP_Msk | SYS_GPA_MFP0_PA2MFP_Msk | SYS_GPA_MFP0_PA1MFP_Msk | SYS_GPA_MFP0_PA0MFP_Msk);
    SYS->GPA_MFP0 |= (SYS_GPA_MFP0_PA3MFP_QSPI0_SS | SYS_GPA_MFP0_PA2MFP_QSPI0_CLK | SYS_GPA_MFP0_PA1MFP_QSPI0_MISO0 | SYS_GPA_MFP0_PA0MFP_QSPI0_MOSI0);
    SYS->GPA_MFP1 &= ~(SYS_GPA_MFP1_PA5MFP_Msk | SYS_GPA_MFP1_PA4MFP_Msk);
    SYS->GPA_MFP1 |= (SYS_GPA_MFP1_PA5MFP_QSPI0_MISO1 | SYS_GPA_MFP1_PA4MFP_QSPI0_MOSI1);

    return;
}

void nutool_pincfg_deinit_qspi0(void)
{
    SYS->GPA_MFP0 &= ~(SYS_GPA_MFP0_PA3MFP_Msk | SYS_GPA_MFP0_PA2MFP_Msk | SYS_GPA_MFP0_PA1MFP_Msk | SYS_GPA_MFP0_PA0MFP_Msk);
    SYS->GPA_MFP1 &= ~(SYS_GPA_MFP1_PA5MFP_Msk | SYS_GPA_MFP1_PA4MFP_Msk);

    return;
}
#endif

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
    SYS->GPI_MFP1 &= ~(SYS_GPI_MFP1_PI7MFP_Msk);
    SYS->GPI_MFP1 |= (SYS_GPI_MFP1_PI7MFP_SPI1_MISO);
    SYS->GPI_MFP2 &= ~(SYS_GPI_MFP2_PI10MFP_Msk | SYS_GPI_MFP2_PI9MFP_Msk | SYS_GPI_MFP2_PI8MFP_Msk);
    SYS->GPI_MFP2 |= (SYS_GPI_MFP2_PI10MFP_SPI1_SS | SYS_GPI_MFP2_PI9MFP_SPI1_CLK | SYS_GPI_MFP2_PI8MFP_SPI1_MOSI);

    return;
}

void nutool_pincfg_deinit_spi1(void)
{
    SYS->GPI_MFP1 &= ~(SYS_GPI_MFP1_PI7MFP_Msk);
    SYS->GPI_MFP2 &= ~(SYS_GPI_MFP2_PI10MFP_Msk | SYS_GPI_MFP2_PI9MFP_Msk | SYS_GPI_MFP2_PI8MFP_Msk);

    return;
}

void nutool_pincfg_init_spi2(void)
{
    SYS->GPA_MFP2 &= ~(SYS_GPA_MFP2_PA11MFP_Msk | SYS_GPA_MFP2_PA10MFP_Msk | SYS_GPA_MFP2_PA9MFP_Msk | SYS_GPA_MFP2_PA8MFP_Msk);
    SYS->GPA_MFP2 |= (SYS_GPA_MFP2_PA11MFP_SPI2_SS | SYS_GPA_MFP2_PA10MFP_SPI2_CLK | SYS_GPA_MFP2_PA9MFP_SPI2_MISO | SYS_GPA_MFP2_PA8MFP_SPI2_MOSI);

    return;
}

void nutool_pincfg_deinit_spi2(void)
{
    SYS->GPA_MFP2 &= ~(SYS_GPA_MFP2_PA11MFP_Msk | SYS_GPA_MFP2_PA10MFP_Msk | SYS_GPA_MFP2_PA9MFP_Msk | SYS_GPA_MFP2_PA8MFP_Msk);

    return;
}

void nutool_pincfg_init_spi3(void)
{
    SYS->GPG_MFP1 &= ~(SYS_GPG_MFP1_PG7MFP_Msk | SYS_GPG_MFP1_PG6MFP_Msk | SYS_GPG_MFP1_PG5MFP_Msk);
    SYS->GPG_MFP1 |= (SYS_GPG_MFP1_PG7MFP_SPI3_MISO | SYS_GPG_MFP1_PG6MFP_SPI3_CLK | SYS_GPG_MFP1_PG5MFP_SPI3_SS);
    SYS->GPG_MFP2 &= ~(SYS_GPG_MFP2_PG8MFP_Msk);
    SYS->GPG_MFP2 |= (SYS_GPG_MFP2_PG8MFP_SPI3_MOSI);

    return;
}

void nutool_pincfg_deinit_spi3(void)
{
    SYS->GPG_MFP1 &= ~(SYS_GPG_MFP1_PG7MFP_Msk | SYS_GPG_MFP1_PG6MFP_Msk | SYS_GPG_MFP1_PG5MFP_Msk);
    SYS->GPG_MFP2 &= ~(SYS_GPG_MFP2_PG8MFP_Msk);

    return;
}

#if 0
void nutool_pincfg_init_spim(void)
{
    SYS->GPI_MFP3 &= ~(SYS_GPI_MFP3_PI15MFP_Msk | SYS_GPI_MFP3_PI14MFP_Msk | SYS_GPI_MFP3_PI13MFP_Msk | SYS_GPI_MFP3_PI12MFP_Msk);
    SYS->GPI_MFP3 |= (SYS_GPI_MFP3_PI15MFP_SPIM_D3 | SYS_GPI_MFP3_PI14MFP_SPIM_D2 | SYS_GPI_MFP3_PI13MFP_SPIM_MISO | SYS_GPI_MFP3_PI12MFP_SPIM_SS);
    SYS->GPJ_MFP0 &= ~(SYS_GPJ_MFP0_PJ1MFP_Msk | SYS_GPJ_MFP0_PJ0MFP_Msk);
    SYS->GPJ_MFP0 |= (SYS_GPJ_MFP0_PJ1MFP_SPIM_MOSI | SYS_GPJ_MFP0_PJ0MFP_SPIM_CLK);

    return;
}

void nutool_pincfg_deinit_spim(void)
{
    SYS->GPI_MFP3 &= ~(SYS_GPI_MFP3_PI15MFP_Msk | SYS_GPI_MFP3_PI14MFP_Msk | SYS_GPI_MFP3_PI13MFP_Msk | SYS_GPI_MFP3_PI12MFP_Msk);
    SYS->GPJ_MFP0 &= ~(SYS_GPJ_MFP0_PJ1MFP_Msk | SYS_GPJ_MFP0_PJ0MFP_Msk);

    return;
}
#endif

void nutool_pincfg_init_uart0(void)
{
    SYS->GPB_MFP3 &= ~(SYS_GPB_MFP3_PB13MFP_Msk | SYS_GPB_MFP3_PB12MFP_Msk);
    SYS->GPB_MFP3 |= (SYS_GPB_MFP3_PB13MFP_UART0_TXD | SYS_GPB_MFP3_PB12MFP_UART0_RXD);

    return;
}

void nutool_pincfg_deinit_uart0(void)
{
    SYS->GPB_MFP3 &= ~(SYS_GPB_MFP3_PB13MFP_Msk | SYS_GPB_MFP3_PB12MFP_Msk);

    return;
}

void nutool_pincfg_init_uart1(void)
{
    SYS->GPB_MFP0 &= ~(SYS_GPB_MFP0_PB3MFP_Msk | SYS_GPB_MFP0_PB2MFP_Msk);
    SYS->GPB_MFP0 |= (SYS_GPB_MFP0_PB3MFP_UART1_TXD | SYS_GPB_MFP0_PB2MFP_UART1_RXD);

    return;
}

void nutool_pincfg_deinit_uart1(void)
{
    SYS->GPB_MFP0 &= ~(SYS_GPB_MFP0_PB3MFP_Msk | SYS_GPB_MFP0_PB2MFP_Msk);

    return;
}

void nutool_pincfg_init_uart2(void)
{
    SYS->GPC_MFP0 &= ~(SYS_GPC_MFP0_PC3MFP_Msk | SYS_GPC_MFP0_PC2MFP_Msk | SYS_GPC_MFP0_PC1MFP_Msk | SYS_GPC_MFP0_PC0MFP_Msk);
    SYS->GPC_MFP0 |= (SYS_GPC_MFP0_PC3MFP_UART2_nRTS | SYS_GPC_MFP0_PC2MFP_UART2_nCTS | SYS_GPC_MFP0_PC1MFP_UART2_TXD | SYS_GPC_MFP0_PC0MFP_UART2_RXD);

    return;
}

void nutool_pincfg_deinit_uart2(void)
{
    SYS->GPC_MFP0 &= ~(SYS_GPC_MFP0_PC3MFP_Msk | SYS_GPC_MFP0_PC2MFP_Msk | SYS_GPC_MFP0_PC1MFP_Msk | SYS_GPC_MFP0_PC0MFP_Msk);

    return;
}

void nutool_pincfg_init_uart4(void)
{
    SYS->GPF_MFP1 &= ~(SYS_GPF_MFP1_PF7MFP_Msk | SYS_GPF_MFP1_PF6MFP_Msk);
    SYS->GPF_MFP1 |= (SYS_GPF_MFP1_PF7MFP_UART4_TXD | SYS_GPF_MFP1_PF6MFP_UART4_RXD);

    return;
}

void nutool_pincfg_deinit_uart4(void)
{
    SYS->GPF_MFP1 &= ~(SYS_GPF_MFP1_PF7MFP_Msk | SYS_GPF_MFP1_PF6MFP_Msk);

    return;
}

void nutool_pincfg_init_uart5(void)
{
    SYS->GPF_MFP2 &= ~(SYS_GPF_MFP2_PF11MFP_Msk | SYS_GPF_MFP2_PF10MFP_Msk);
    SYS->GPF_MFP2 |= (SYS_GPF_MFP2_PF11MFP_UART5_TXD | SYS_GPF_MFP2_PF10MFP_UART5_RXD);

    return;
}

void nutool_pincfg_deinit_uart5(void)
{
    SYS->GPF_MFP2 &= ~(SYS_GPF_MFP2_PF11MFP_Msk | SYS_GPF_MFP2_PF10MFP_Msk);

    return;
}

void nutool_pincfg_init_usb(void)
{
    SYS->GPA_MFP3 &= ~(SYS_GPA_MFP3_PA15MFP_Msk | SYS_GPA_MFP3_PA14MFP_Msk | SYS_GPA_MFP3_PA13MFP_Msk | SYS_GPA_MFP3_PA12MFP_Msk);
    SYS->GPA_MFP3 |= (SYS_GPA_MFP3_PA15MFP_USB_OTG_ID | SYS_GPA_MFP3_PA14MFP_USB_D_P | SYS_GPA_MFP3_PA13MFP_USB_D_N | SYS_GPA_MFP3_PA12MFP_USB_VBUS);
    SYS->GPB_MFP3 &= ~(SYS_GPB_MFP3_PB15MFP_Msk);
    SYS->GPB_MFP3 |= (SYS_GPB_MFP3_PB15MFP_USB_VBUS_EN);
    SYS->GPC_MFP3 &= ~(SYS_GPC_MFP3_PC14MFP_Msk);
    SYS->GPC_MFP3 |= (SYS_GPC_MFP3_PC14MFP_USB_VBUS_ST);

    return;
}

void nutool_pincfg_deinit_usb(void)
{
    SYS->GPA_MFP3 &= ~(SYS_GPA_MFP3_PA15MFP_Msk | SYS_GPA_MFP3_PA14MFP_Msk | SYS_GPA_MFP3_PA13MFP_Msk | SYS_GPA_MFP3_PA12MFP_Msk);
    SYS->GPB_MFP3 &= ~(SYS_GPB_MFP3_PB15MFP_Msk);
    SYS->GPC_MFP3 &= ~(SYS_GPC_MFP3_PC14MFP_Msk);

    return;
}

void nutool_pincfg_init_x32(void)
{
    SYS->GPF_MFP1 &= ~(SYS_GPF_MFP1_PF5MFP_Msk | SYS_GPF_MFP1_PF4MFP_Msk);
    SYS->GPF_MFP1 |= (SYS_GPF_MFP1_PF5MFP_X32_IN | SYS_GPF_MFP1_PF4MFP_X32_OUT);

    return;
}

void nutool_pincfg_deinit_x32(void)
{
    SYS->GPF_MFP1 &= ~(SYS_GPF_MFP1_PF5MFP_Msk | SYS_GPF_MFP1_PF4MFP_Msk);

    return;
}

void nutool_pincfg_init_xt1(void)
{
    SYS->GPF_MFP0 &= ~(SYS_GPF_MFP0_PF3MFP_Msk | SYS_GPF_MFP0_PF2MFP_Msk);
    SYS->GPF_MFP0 |= (SYS_GPF_MFP0_PF3MFP_XT1_IN | SYS_GPF_MFP0_PF2MFP_XT1_OUT);

    return;
}

void nutool_pincfg_deinit_xt1(void)
{
    SYS->GPF_MFP0 &= ~(SYS_GPF_MFP0_PF3MFP_Msk | SYS_GPF_MFP0_PF2MFP_Msk);

    return;
}

void nutool_pincfg_init(void)
{
    //SYS->GPA_MFP0 = 0x03030303UL;
    //SYS->GPA_MFP1 = 0x03030303UL;
    //SYS->GPA_MFP2 = 0x04040404UL;
    //SYS->GPA_MFP3 = 0x0E0E0E0EUL;
    //SYS->GPB_MFP0 = 0x06060101UL;
    //SYS->GPB_MFP1 = 0x01010B0BUL;
    //SYS->GPB_MFP2 = 0x00000101UL;
    //SYS->GPB_MFP3 = 0x0E000606UL;
    //SYS->GPC_MFP0 = 0x08080808UL;
    //SYS->GPC_MFP1 = 0x03030000UL;
    //SYS->GPC_MFP2 = 0x0C0C0C03UL;
    //SYS->GPC_MFP3 = 0x000E000CUL;
    //SYS->GPD_MFP0 = 0x00000606UL;
    //SYS->GPD_MFP1 = 0x00000000UL;
    //SYS->GPD_MFP2 = 0x01010000UL;
    //SYS->GPD_MFP3 = 0x000B0300UL;
    //SYS->GPE_MFP0 = 0x03030000UL;
    //SYS->GPE_MFP1 = 0x03030303UL;
    //SYS->GPE_MFP2 = 0x03030303UL;
    //SYS->GPE_MFP3 = 0x00000003UL;
    //SYS->GPF_MFP0 = 0x0A0A0E0EUL;
    //SYS->GPF_MFP1 = 0x06060A0AUL;
    //SYS->GPF_MFP2 = 0x06060000UL;
    //SYS->GPG_MFP0 = 0x05050909UL;
    //SYS->GPG_MFP1 = 0x03030300UL;
    //SYS->GPG_MFP2 = 0x00080803UL;
    //SYS->GPG_MFP3 = 0x00000000UL;
    //SYS->GPH_MFP0 = 0x00000000UL;
    //SYS->GPH_MFP1 = 0x00000000UL;
    //SYS->GPH_MFP2 = 0x0B000000UL;
    //SYS->GPH_MFP3 = 0x00000000UL;
    //SYS->GPI_MFP1 = 0x07000000UL;
    //SYS->GPI_MFP2 = 0x00070707UL;
    //SYS->GPI_MFP3 = 0x03030303UL;
    //SYS->GPJ_MFP0 = 0x00000303UL;
    //SYS->GPJ_MFP1 = 0x00000000UL;
    //SYS->GPJ_MFP2 = 0x0B0B0000UL;
    //SYS->GPJ_MFP3 = 0x00000F0FUL;

    nutool_pincfg_init_can0();
    nutool_pincfg_init_eadc0();
    nutool_pincfg_init_eadc1();
    nutool_pincfg_init_emac0();
    nutool_pincfg_init_epwm0();
    nutool_pincfg_init_epwm1();
    nutool_pincfg_init_hsusb();
    nutool_pincfg_init_i2c1();
    nutool_pincfg_init_i2c2();
    nutool_pincfg_init_i2c3();
    nutool_pincfg_init_i2c4();
    nutool_pincfg_init_ice();
    nutool_pincfg_init_pc();
    nutool_pincfg_init_pd();
    nutool_pincfg_init_pe();
    nutool_pincfg_init_pf();
    nutool_pincfg_init_pg();
    nutool_pincfg_init_ph();
    nutool_pincfg_init_pi();
    nutool_pincfg_init_pj();
    nutool_pincfg_init_qspi0();
    nutool_pincfg_init_sd0();
    nutool_pincfg_init_spi1();
    nutool_pincfg_init_spi2();
    nutool_pincfg_init_spi3();
    //nutool_pincfg_init_spim();
    nutool_pincfg_init_uart0();
#if !(defined(BOARD_USING_LCD_ILI9341) && defined(NU_PKG_USING_ILI9341_SPI))
    nutool_pincfg_init_uart1();
#endif
    nutool_pincfg_init_uart2();
    nutool_pincfg_init_uart4();
    nutool_pincfg_init_uart5();
    nutool_pincfg_init_usb();
    nutool_pincfg_init_x32();
    nutool_pincfg_init_xt1();

    return;
}

void nutool_pincfg_deinit(void)
{
    nutool_pincfg_deinit_can0();
    nutool_pincfg_deinit_eadc0();
    nutool_pincfg_deinit_eadc1();
    nutool_pincfg_deinit_emac0();
    nutool_pincfg_deinit_epwm0();
    nutool_pincfg_deinit_epwm1();
    nutool_pincfg_deinit_hsusb();
    nutool_pincfg_deinit_i2c1();
    nutool_pincfg_deinit_i2c2();
    nutool_pincfg_deinit_i2c3();
    nutool_pincfg_deinit_i2c4();
    nutool_pincfg_deinit_ice();
    nutool_pincfg_deinit_pc();
    nutool_pincfg_deinit_pd();
    nutool_pincfg_deinit_pe();
    nutool_pincfg_deinit_pf();
    nutool_pincfg_deinit_pg();
    nutool_pincfg_deinit_ph();
    nutool_pincfg_deinit_pi();
    nutool_pincfg_deinit_pj();
    nutool_pincfg_deinit_qspi0();
    nutool_pincfg_deinit_sd0();
    nutool_pincfg_deinit_spi1();
    nutool_pincfg_deinit_spi2();
    nutool_pincfg_deinit_spi3();
    //nutool_pincfg_deinit_spim();
    nutool_pincfg_deinit_uart0();
#if !(defined(BOARD_USING_LCD_ILI9341) && defined(NU_PKG_USING_ILI9341_SPI))
    nutool_pincfg_deinit_uart1();
#endif
    nutool_pincfg_deinit_uart2();
    nutool_pincfg_deinit_uart4();
    nutool_pincfg_deinit_uart5();
    nutool_pincfg_deinit_usb();
    nutool_pincfg_deinit_x32();
    nutool_pincfg_deinit_xt1();

    return;
}

/*** (C) COPYRIGHT 2013-2022 Nuvoton Technology Corp. ***/
