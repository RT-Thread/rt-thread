/****************************************************************************
 * @file     nutool_pincfg.c
 * @version  V1.24
 * @Date     2022/03/31-16:32:03
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
Pin20:PD.10
Pin23:I2C3_SCL
Pin24:I2C3_SDA
Pin25:CCAP_DATA7
Pin26:CCAP_DATA6
Pin27:CCAP_DATA5
Pin28:I2S0_BCLK
Pin29:I2S0_MCLK
Pin30:I2S0_DI
Pin31:I2S0_DO
Pin32:I2S0_LRCK
Pin34:CCAP_DATA4
Pin35:CCAP_DATA3
Pin36:CCAP_DATA2
Pin37:CCAP_DATA1
Pin38:CCAP_DATA0
Pin41:X32_IN
Pin42:X32_OUT
Pin45:I2C0_SCL
Pin46:I2C0_SDA
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
Pin66:QSPI0_MISO1
Pin67:QSPI0_MOSI1
Pin68:QSPI0_SS
Pin69:QSPI0_CLK
Pin70:QSPI0_MISO0
Pin71:QSPI0_MOSI0
Pin82:EBI_AD8
Pin83:EBI_AD9
Pin85:ICE_DAT
Pin86:ICE_CLK
Pin87:EBI_AD7
Pin88:EBI_AD6
Pin89:EBI_AD5
Pin90:EBI_AD4
Pin91:EBI_AD3
Pin92:EBI_AD2
Pin93:EBI_AD1
Pin94:EBI_AD0
Pin97:CCAP_PIXCLK
Pin98:CCAP_SCLK
Pin100:CCAP_VSYNC
Pin101:CCAP_HSYNC
Pin104:HBI_nRESET
Pin105:HBI_D3
Pin106:HBI_D2
Pin107:HBI_D1
Pin108:HBI_D0
Pin109:HBI_nCS
Pin110:HBI_nCK
Pin111:HBI_CK
Pin112:HBI_RWDS
Pin113:HBI_D4
Pin114:HBI_D5
Pin115:HBI_D6
Pin116:HBI_D7
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
Pin143:EBI_AD10
Pin144:EBI_AD11
Pin145:EBI_AD12
Pin146:EBI_AD13
Pin147:EBI_AD14
Pin148:EBI_AD15
Pin149:EBI_nCS0
Pin150:EBI_nRD
Pin151:EBI_nWR
Pin152:CAN0_TXD
Pin153:CAN0_RXD
Pin154:HSUSB_VBUS_ST
Pin155:HSUSB_VBUS_EN
Pin163:USB_VBUS_ST
Pin164:USB_VBUS_EN
Pin166:UART0_TXD
Pin167:UART0_RXD
Pin171:I2C1_SCL
Pin172:I2C1_SDA
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

void nutool_pincfg_init_ccap(void)
{
    SYS->GPF_MFP1 &= ~(SYS_GPF_MFP1_PF7MFP_Msk);
    SYS->GPF_MFP1 |= (SYS_GPF_MFP1_PF7MFP_CCAP_DATA0);
    SYS->GPF_MFP2 &= ~(SYS_GPF_MFP2_PF11MFP_Msk | SYS_GPF_MFP2_PF10MFP_Msk | SYS_GPF_MFP2_PF9MFP_Msk | SYS_GPF_MFP2_PF8MFP_Msk);
    SYS->GPF_MFP2 |= (SYS_GPF_MFP2_PF11MFP_CCAP_DATA4 | SYS_GPF_MFP2_PF10MFP_CCAP_DATA3 | SYS_GPF_MFP2_PF9MFP_CCAP_DATA2 | SYS_GPF_MFP2_PF8MFP_CCAP_DATA1);
    SYS->GPG_MFP0 &= ~(SYS_GPG_MFP0_PG3MFP_Msk | SYS_GPG_MFP0_PG2MFP_Msk);
    SYS->GPG_MFP0 |= (SYS_GPG_MFP0_PG3MFP_CCAP_DATA6 | SYS_GPG_MFP0_PG2MFP_CCAP_DATA7);
    SYS->GPG_MFP1 &= ~(SYS_GPG_MFP1_PG4MFP_Msk);
    SYS->GPG_MFP1 |= (SYS_GPG_MFP1_PG4MFP_CCAP_DATA5);
    SYS->GPG_MFP2 &= ~(SYS_GPG_MFP2_PG10MFP_Msk | SYS_GPG_MFP2_PG9MFP_Msk);
    SYS->GPG_MFP2 |= (SYS_GPG_MFP2_PG10MFP_CCAP_SCLK | SYS_GPG_MFP2_PG9MFP_CCAP_PIXCLK);
    SYS->GPG_MFP3 &= ~(SYS_GPG_MFP3_PG13MFP_Msk | SYS_GPG_MFP3_PG12MFP_Msk);
    SYS->GPG_MFP3 |= (SYS_GPG_MFP3_PG13MFP_CCAP_HSYNC | SYS_GPG_MFP3_PG12MFP_CCAP_VSYNC);

    return;
}

void nutool_pincfg_deinit_ccap(void)
{
    SYS->GPF_MFP1 &= ~(SYS_GPF_MFP1_PF7MFP_Msk);
    SYS->GPF_MFP2 &= ~(SYS_GPF_MFP2_PF11MFP_Msk | SYS_GPF_MFP2_PF10MFP_Msk | SYS_GPF_MFP2_PF9MFP_Msk | SYS_GPF_MFP2_PF8MFP_Msk);
    SYS->GPG_MFP0 &= ~(SYS_GPG_MFP0_PG3MFP_Msk | SYS_GPG_MFP0_PG2MFP_Msk);
    SYS->GPG_MFP1 &= ~(SYS_GPG_MFP1_PG4MFP_Msk);
    SYS->GPG_MFP2 &= ~(SYS_GPG_MFP2_PG10MFP_Msk | SYS_GPG_MFP2_PG9MFP_Msk);
    SYS->GPG_MFP3 &= ~(SYS_GPG_MFP3_PG13MFP_Msk | SYS_GPG_MFP3_PG12MFP_Msk);

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
    SYS->GPD_MFP2 &= ~(SYS_GPD_MFP2_PD11MFP_Msk);
    SYS->GPD_MFP2 |= (SYS_GPD_MFP2_PD11MFP_EADC1_CH1);

    /* Disable digital path on these EADC pins */
    GPIO_DISABLE_DIGITAL_PATH(PD, BIT11);

    return;
}

void nutool_pincfg_deinit_eadc1(void)
{
    SYS->GPD_MFP2 &= ~(SYS_GPD_MFP2_PD11MFP_Msk);

    /* Enable digital path on these EADC pins */
    GPIO_ENABLE_DIGITAL_PATH(PD, BIT11);

    return;
}

void nutool_pincfg_init_ebi(void)
{
    SYS->GPC_MFP0 &= ~(SYS_GPC_MFP0_PC3MFP_Msk | SYS_GPC_MFP0_PC2MFP_Msk | SYS_GPC_MFP0_PC1MFP_Msk | SYS_GPC_MFP0_PC0MFP_Msk);
    SYS->GPC_MFP0 |= (SYS_GPC_MFP0_PC3MFP_EBI_AD3 | SYS_GPC_MFP0_PC2MFP_EBI_AD2 | SYS_GPC_MFP0_PC1MFP_EBI_AD1 | SYS_GPC_MFP0_PC0MFP_EBI_AD0);
    SYS->GPC_MFP1 &= ~(SYS_GPC_MFP1_PC5MFP_Msk | SYS_GPC_MFP1_PC4MFP_Msk);
    SYS->GPC_MFP1 |= (SYS_GPC_MFP1_PC5MFP_EBI_AD5 | SYS_GPC_MFP1_PC4MFP_EBI_AD4);
    SYS->GPD_MFP2 &= ~(SYS_GPD_MFP2_PD9MFP_Msk | SYS_GPD_MFP2_PD8MFP_Msk);
    SYS->GPD_MFP2 |= (SYS_GPD_MFP2_PD9MFP_EBI_AD7 | SYS_GPD_MFP2_PD8MFP_EBI_AD6);
    SYS->GPD_MFP3 &= ~(SYS_GPD_MFP3_PD14MFP_Msk);
    SYS->GPD_MFP3 |= (SYS_GPD_MFP3_PD14MFP_EBI_nCS0);
    SYS->GPE_MFP0 &= ~(SYS_GPE_MFP0_PE1MFP_Msk | SYS_GPE_MFP0_PE0MFP_Msk);
    SYS->GPE_MFP0 |= (SYS_GPE_MFP0_PE1MFP_EBI_AD10 | SYS_GPE_MFP0_PE0MFP_EBI_AD11);
    SYS->GPE_MFP3 &= ~(SYS_GPE_MFP3_PE15MFP_Msk | SYS_GPE_MFP3_PE14MFP_Msk);
    SYS->GPE_MFP3 |= (SYS_GPE_MFP3_PE15MFP_EBI_AD9 | SYS_GPE_MFP3_PE14MFP_EBI_AD8);
    SYS->GPH_MFP2 &= ~(SYS_GPH_MFP2_PH11MFP_Msk | SYS_GPH_MFP2_PH10MFP_Msk | SYS_GPH_MFP2_PH9MFP_Msk | SYS_GPH_MFP2_PH8MFP_Msk);
    SYS->GPH_MFP2 |= (SYS_GPH_MFP2_PH11MFP_EBI_AD15 | SYS_GPH_MFP2_PH10MFP_EBI_AD14 | SYS_GPH_MFP2_PH9MFP_EBI_AD13 | SYS_GPH_MFP2_PH8MFP_EBI_AD12);
    SYS->GPJ_MFP2 &= ~(SYS_GPJ_MFP2_PJ9MFP_Msk | SYS_GPJ_MFP2_PJ8MFP_Msk);
    SYS->GPJ_MFP2 |= (SYS_GPJ_MFP2_PJ9MFP_EBI_nWR | SYS_GPJ_MFP2_PJ8MFP_EBI_nRD);

    GPIO_SetSlewCtl(PC, (BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5), GPIO_SLEWCTL_FAST);
    GPIO_SetSlewCtl(PD, (BIT8 | BIT9), GPIO_SLEWCTL_FAST);
    GPIO_SetSlewCtl(PE, (BIT14 | BIT15), GPIO_SLEWCTL_FAST);
    GPIO_SetSlewCtl(PE, (BIT0 | BIT1), GPIO_SLEWCTL_FAST);
    GPIO_SetSlewCtl(PH, (BIT8 | BIT9 | BIT10 | BIT11), GPIO_SLEWCTL_FAST);
    GPIO_SetSlewCtl(PJ, (BIT8 | BIT9), GPIO_SLEWCTL_FAST);
    GPIO_SetSlewCtl(PD, BIT14, GPIO_SLEWCTL_FAST);

    return;
}

void nutool_pincfg_deinit_ebi(void)
{
    SYS->GPC_MFP0 &= ~(SYS_GPC_MFP0_PC3MFP_Msk | SYS_GPC_MFP0_PC2MFP_Msk | SYS_GPC_MFP0_PC1MFP_Msk | SYS_GPC_MFP0_PC0MFP_Msk);
    SYS->GPC_MFP1 &= ~(SYS_GPC_MFP1_PC5MFP_Msk | SYS_GPC_MFP1_PC4MFP_Msk);
    SYS->GPD_MFP2 &= ~(SYS_GPD_MFP2_PD9MFP_Msk | SYS_GPD_MFP2_PD8MFP_Msk);
    SYS->GPD_MFP3 &= ~(SYS_GPD_MFP3_PD14MFP_Msk);
    SYS->GPE_MFP0 &= ~(SYS_GPE_MFP0_PE1MFP_Msk | SYS_GPE_MFP0_PE0MFP_Msk);
    SYS->GPE_MFP3 &= ~(SYS_GPE_MFP3_PE15MFP_Msk | SYS_GPE_MFP3_PE14MFP_Msk);
    SYS->GPH_MFP2 &= ~(SYS_GPH_MFP2_PH11MFP_Msk | SYS_GPH_MFP2_PH10MFP_Msk | SYS_GPH_MFP2_PH9MFP_Msk | SYS_GPH_MFP2_PH8MFP_Msk);
    SYS->GPJ_MFP2 &= ~(SYS_GPJ_MFP2_PJ9MFP_Msk | SYS_GPJ_MFP2_PJ8MFP_Msk);

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
    SYS->GPB_MFP1 &= ~(SYS_GPB_MFP1_PB5MFP_Msk | SYS_GPB_MFP1_PB4MFP_Msk);
    SYS->GPB_MFP1 |= (SYS_GPB_MFP1_PB5MFP_EPWM0_CH0 | SYS_GPB_MFP1_PB4MFP_EPWM0_CH1);

    return;
}

void nutool_pincfg_deinit_epwm0(void)
{
    SYS->GPB_MFP1 &= ~(SYS_GPB_MFP1_PB5MFP_Msk | SYS_GPB_MFP1_PB4MFP_Msk);

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

void nutool_pincfg_init_hbi(void)
{
    SYS->GPD_MFP1 &= ~(SYS_GPD_MFP1_PD7MFP_Msk | SYS_GPD_MFP1_PD6MFP_Msk | SYS_GPD_MFP1_PD5MFP_Msk);
    SYS->GPD_MFP1 |= (SYS_GPD_MFP1_PD7MFP_HBI_D5 | SYS_GPD_MFP1_PD6MFP_HBI_D6 | SYS_GPD_MFP1_PD5MFP_HBI_D7);
    SYS->GPH_MFP3 &= ~(SYS_GPH_MFP3_PH15MFP_Msk | SYS_GPH_MFP3_PH14MFP_Msk | SYS_GPH_MFP3_PH13MFP_Msk | SYS_GPH_MFP3_PH12MFP_Msk);
    SYS->GPH_MFP3 |= (SYS_GPH_MFP3_PH15MFP_HBI_D4 | SYS_GPH_MFP3_PH14MFP_HBI_RWDS | SYS_GPH_MFP3_PH13MFP_HBI_CK | SYS_GPH_MFP3_PH12MFP_HBI_nCK);
    SYS->GPJ_MFP0 &= ~(SYS_GPJ_MFP0_PJ3MFP_Msk | SYS_GPJ_MFP0_PJ2MFP_Msk);
    SYS->GPJ_MFP0 |= (SYS_GPJ_MFP0_PJ3MFP_HBI_D3 | SYS_GPJ_MFP0_PJ2MFP_HBI_nRESET);
    SYS->GPJ_MFP1 &= ~(SYS_GPJ_MFP1_PJ7MFP_Msk | SYS_GPJ_MFP1_PJ6MFP_Msk | SYS_GPJ_MFP1_PJ5MFP_Msk | SYS_GPJ_MFP1_PJ4MFP_Msk);
    SYS->GPJ_MFP1 |= (SYS_GPJ_MFP1_PJ7MFP_HBI_nCS | SYS_GPJ_MFP1_PJ6MFP_HBI_D0 | SYS_GPJ_MFP1_PJ5MFP_HBI_D1 | SYS_GPJ_MFP1_PJ4MFP_HBI_D2);

    return;
}

void nutool_pincfg_deinit_hbi(void)
{
    SYS->GPD_MFP1 &= ~(SYS_GPD_MFP1_PD7MFP_Msk | SYS_GPD_MFP1_PD6MFP_Msk | SYS_GPD_MFP1_PD5MFP_Msk);
    SYS->GPH_MFP3 &= ~(SYS_GPH_MFP3_PH15MFP_Msk | SYS_GPH_MFP3_PH14MFP_Msk | SYS_GPH_MFP3_PH13MFP_Msk | SYS_GPH_MFP3_PH12MFP_Msk);
    SYS->GPJ_MFP0 &= ~(SYS_GPJ_MFP0_PJ3MFP_Msk | SYS_GPJ_MFP0_PJ2MFP_Msk);
    SYS->GPJ_MFP1 &= ~(SYS_GPJ_MFP1_PJ7MFP_Msk | SYS_GPJ_MFP1_PJ6MFP_Msk | SYS_GPJ_MFP1_PJ5MFP_Msk | SYS_GPJ_MFP1_PJ4MFP_Msk);

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

void nutool_pincfg_init_i2c0(void)
{
    SYS->GPH_MFP0 &= ~(SYS_GPH_MFP0_PH3MFP_Msk | SYS_GPH_MFP0_PH2MFP_Msk);
    SYS->GPH_MFP0 |= (SYS_GPH_MFP0_PH3MFP_I2C0_SDA | SYS_GPH_MFP0_PH2MFP_I2C0_SCL);

    GPIO_SetPullCtl(PH, BIT2 | BIT3, GPIO_PUSEL_PULL_UP);

    return;
}

void nutool_pincfg_deinit_i2c0(void)
{
    SYS->GPH_MFP0 &= ~(SYS_GPH_MFP0_PH3MFP_Msk | SYS_GPH_MFP0_PH2MFP_Msk);

    return;
}

void nutool_pincfg_init_i2c1(void)
{
    SYS->GPB_MFP2 &= ~(SYS_GPB_MFP2_PB11MFP_Msk | SYS_GPB_MFP2_PB10MFP_Msk);
    SYS->GPB_MFP2 |= (SYS_GPB_MFP2_PB11MFP_I2C1_SCL | SYS_GPB_MFP2_PB10MFP_I2C1_SDA);

    GPIO_SetPullCtl(PB, BIT11 | BIT10, GPIO_PUSEL_PULL_UP);

    return;
}

void nutool_pincfg_deinit_i2c1(void)
{
    SYS->GPB_MFP2 &= ~(SYS_GPB_MFP2_PB11MFP_Msk | SYS_GPB_MFP2_PB10MFP_Msk);

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

void nutool_pincfg_init_i2s0(void)
{
    SYS->GPI_MFP1 &= ~(SYS_GPI_MFP1_PI7MFP_Msk | SYS_GPI_MFP1_PI6MFP_Msk);
    SYS->GPI_MFP1 |= (SYS_GPI_MFP1_PI7MFP_I2S0_MCLK | SYS_GPI_MFP1_PI6MFP_I2S0_BCLK);
    SYS->GPI_MFP2 &= ~(SYS_GPI_MFP2_PI10MFP_Msk | SYS_GPI_MFP2_PI9MFP_Msk | SYS_GPI_MFP2_PI8MFP_Msk);
    SYS->GPI_MFP2 |= (SYS_GPI_MFP2_PI10MFP_I2S0_LRCK | SYS_GPI_MFP2_PI9MFP_I2S0_DO | SYS_GPI_MFP2_PI8MFP_I2S0_DI);

    return;
}

void nutool_pincfg_deinit_i2s0(void)
{
    SYS->GPI_MFP1 &= ~(SYS_GPI_MFP1_PI7MFP_Msk | SYS_GPI_MFP1_PI6MFP_Msk);
    SYS->GPI_MFP2 &= ~(SYS_GPI_MFP2_PI10MFP_Msk | SYS_GPI_MFP2_PI9MFP_Msk | SYS_GPI_MFP2_PI8MFP_Msk);

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

void nutool_pincfg_init_pd(void)
{
    SYS->GPD_MFP2 &= ~(SYS_GPD_MFP2_PD10MFP_Msk);
    SYS->GPD_MFP2 |= (SYS_GPD_MFP2_PD10MFP_GPIO);

    return;
}

void nutool_pincfg_deinit_pd(void)
{
    SYS->GPD_MFP2 &= ~(SYS_GPD_MFP2_PD10MFP_Msk);

    return;
}

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
    //SYS->GPA_MFP0 = 0x00000000UL;
    //SYS->GPA_MFP1 = 0x03030000UL;
    //SYS->GPA_MFP2 = 0x04040404UL;
    //SYS->GPA_MFP3 = 0x0E0E0E0EUL;
    //SYS->GPB_MFP0 = 0x06060101UL;
    //SYS->GPB_MFP1 = 0x01010B0BUL;
    //SYS->GPB_MFP2 = 0x07070101UL;
    //SYS->GPB_MFP3 = 0x0E000606UL;
    //SYS->GPC_MFP0 = 0x02020202UL;
    //SYS->GPC_MFP1 = 0x03030202UL;
    //SYS->GPC_MFP2 = 0x0C0C0C03UL;
    //SYS->GPC_MFP3 = 0x000E000CUL;
    //SYS->GPD_MFP0 = 0x00000606UL;
    //SYS->GPD_MFP1 = 0x10101000UL;
    //SYS->GPD_MFP2 = 0x01000202UL;
    //SYS->GPD_MFP3 = 0x00020300UL;
    //SYS->GPE_MFP0 = 0x03030202UL;
    //SYS->GPE_MFP1 = 0x03030303UL;
    //SYS->GPE_MFP2 = 0x03030303UL;
    //SYS->GPE_MFP3 = 0x02020003UL;
    //SYS->GPF_MFP0 = 0x0A0A0E0EUL;
    //SYS->GPF_MFP1 = 0x07000A0AUL;
    //SYS->GPF_MFP2 = 0x07070707UL;
    //SYS->GPG_MFP0 = 0x07070909UL;
    //SYS->GPG_MFP1 = 0x00000007UL;
    //SYS->GPG_MFP2 = 0x00070700UL;
    //SYS->GPG_MFP3 = 0x00000707UL;
    //SYS->GPH_MFP0 = 0x06060000UL;
    //SYS->GPH_MFP1 = 0x00000000UL;
    //SYS->GPH_MFP2 = 0x02020202UL;
    //SYS->GPH_MFP3 = 0x10101010UL;
    //SYS->GPI_MFP1 = 0x06060000UL;
    //SYS->GPI_MFP2 = 0x00060606UL;
    //SYS->GPI_MFP3 = 0x04040404UL;
    //SYS->GPJ_MFP0 = 0x10100404UL;
    //SYS->GPJ_MFP1 = 0x10101010UL;
    //SYS->GPJ_MFP2 = 0x0B0B0202UL;
    //SYS->GPJ_MFP3 = 0x00000F0FUL;

    nutool_pincfg_init_can0();
    nutool_pincfg_init_ccap();
    nutool_pincfg_init_eadc0();
    nutool_pincfg_init_eadc1();
    nutool_pincfg_init_ebi();
    nutool_pincfg_init_emac0();
    nutool_pincfg_init_epwm0();
    nutool_pincfg_init_epwm1();
    nutool_pincfg_init_hbi();
    nutool_pincfg_init_hsusb();
    nutool_pincfg_init_i2c0();
    nutool_pincfg_init_i2c1();
    nutool_pincfg_init_i2c2();
    nutool_pincfg_init_i2c3();
    nutool_pincfg_init_i2s0();
    nutool_pincfg_init_ice();
    nutool_pincfg_init_pd();
    nutool_pincfg_init_qspi0();
    nutool_pincfg_init_sd0();
    nutool_pincfg_init_spi2();
    nutool_pincfg_init_uart0();
    nutool_pincfg_init_uart1();
    nutool_pincfg_init_usb();
    nutool_pincfg_init_x32();
    nutool_pincfg_init_xt1();

    return;
}

void nutool_pincfg_deinit(void)
{
    nutool_pincfg_deinit_can0();
    nutool_pincfg_deinit_ccap();
    nutool_pincfg_deinit_eadc0();
    nutool_pincfg_deinit_eadc1();
    nutool_pincfg_deinit_ebi();
    nutool_pincfg_deinit_emac0();
    nutool_pincfg_deinit_epwm0();
    nutool_pincfg_deinit_epwm1();
    nutool_pincfg_deinit_hbi();
    nutool_pincfg_deinit_hsusb();
    nutool_pincfg_deinit_i2c0();
    nutool_pincfg_deinit_i2c1();
    nutool_pincfg_deinit_i2c2();
    nutool_pincfg_deinit_i2c3();
    nutool_pincfg_deinit_i2s0();
    nutool_pincfg_deinit_ice();
    nutool_pincfg_deinit_pd();
    nutool_pincfg_deinit_qspi0();
    nutool_pincfg_deinit_sd0();
    nutool_pincfg_deinit_spi2();
    nutool_pincfg_deinit_uart0();
    nutool_pincfg_deinit_uart1();
    nutool_pincfg_deinit_usb();
    nutool_pincfg_deinit_x32();
    nutool_pincfg_deinit_xt1();

    return;
}

/*** (C) COPYRIGHT 2013-2022 Nuvoton Technology Corp. ***/
