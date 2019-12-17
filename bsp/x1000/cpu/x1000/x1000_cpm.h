/*
 * File      : x1000_cpm.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-02-03     Urey         the first version
 */

#ifndef _X1000_CPM_H_
#define _X1000_CPM_H_

#define CPM_CPCCR       (0x00)
#define CPM_CPCSR       (0xd4)

#define CPM_DDRCDR      (0x2c)
#define CPM_I2SCDR      (0x60)
#define CPM_I2SCDR1     (0x70)
#define CPM_LPCDR       (0x64)
#define CPM_MSC0CDR     (0x68)
#define CPM_MSC1CDR     (0xa4)
#define CPM_USBCDR      (0x50)
#define CPM_MACCDR      (0x54)
#define CPM_UHCCDR      (0x6c)
#define CPM_SFCCDR      (0x74)
#define CPM_CIMCDR      (0x7c)
#define CPM_PCMCDR      (0x84)
#define CPM_PCMCDR1     (0xe0)
#define CPM_MPHYC       (0xe8)

#define CPM_INTR        (0xb0)
#define CPM_INTRE       (0xb4)
#define CPM_DRCG        (0xd0)
#define CPM_CPSPPR      (0x38)
#define CPM_CPPSR       (0x34)

#define CPM_USBPCR      (0x3c)
#define CPM_USBRDT      (0x40)
#define CPM_USBVBFIL    (0x44)
#define CPM_USBPCR1     (0x48)

#define CPM_CPAPCR      (0x10)
#define CPM_CPMPCR      (0x14)

#define CPM_LCR         (0x04)
#define CPM_PSWC0ST     (0x90)
#define CPM_PSWC1ST     (0x94)
#define CPM_PSWC2ST     (0x98)
#define CPM_PSWC3ST     (0x9c)
#define CPM_CLKGR       (0x20)
#define CPM_CLKGR0       (0x20)
#define CPM_MESTSEL     (0xec)
#define CPM_SRBC        (0xc4)
#define CPM_ERNG        (0xd8)
#define CPM_RNG         (0xdc)
#define CPM_SLBC        (0xc8)
#define CPM_SLPC        (0xcc)
#define CPM_OPCR        (0x24)
#define CPM_RSR         (0x08)




/*
 * CPM registers common define
 */

/* Clock control register(CPCCR) */
#define CPCCR_SEL_SRC_LSB       30
#define CPCCR_SEL_SRC_MASK      BITS_H2L(31, CPCCR_SEL_SRC_LSB)

#define CPCCR_SEL_CPLL_LSB      28
#define CPCCR_SEL_CPLL_MASK     BITS_H2L(29, CPCCR_SEL_CPLL_LSB)

#define CPCCR_SEL_H0PLL_LSB     26
#define CPCCR_SEL_H0PLL_MASK    BITS_H2L(27, CPCCR_SEL_H0PLL_LSB)

#define CPCCR_SEL_H2PLL_LSB     24
#define CPCCR_SEL_H2PLL_MASK    BITS_H2L(25, CPCCR_SEL_H2PLL_LSB)

#define CPCCR_CE_CPU            BIT22
#define CPCCR_CE_AHB0           BIT21
#define CPCCR_CE_AHB2           BIT20
#define CPCCR_CE                (CPCCR_CE_CPU | CPCCR_CE_AHB0 | CPCCR_CE_AHB2)

#define CPCCR_PDIV_LSB          16
#define CPCCR_PDIV_MASK         BITS_H2L(19, CPCCR_PDIV_LSB)

#define CPCCR_H2DIV_LSB         12
#define CPCCR_H2DIV_MASK        BITS_H2L(15, CPCCR_H2DIV_LSB)

#define CPCCR_H0DIV_LSB         8
#define CPCCR_H0DIV_MASK        BITS_H2L(11, CPCCR_H0DIV_LSB)

#define CPCCR_L2DIV_LSB         4
#define CPCCR_L2DIV_MASK        BITS_H2L(7,  CPCCR_L2DIV_LSB)

#define CPCCR_CDIV_LSB          0
#define CPCCR_CDIV_MASK         BITS_H2L(3,  CPCCR_CDIV_LSB)

#define CPM_SRC_SEL_APLL        1
#define CPM_PLL_SEL_SRC         1
#define CPM_PLL_SEL_MPLL        2

/* Clock Status register(CPCSR) */
#define CPCSR_SRC_MUX           BIT31
#define CPCSR_CPU_MUX           BIT30
#define CPCSR_AHB0_MUX          BIT29
#define CPCSR_AHB2_MUX          BIT28
#define CPCSR_DDR_MUX           BIT27
#define CPCSR_H2DIV_BUSY        BIT2
#define CPCSR_H0DIV_BUSY        BIT1
#define CPCSR_CDIV_BUSY         BIT0
#define CPCSR_DIV_BUSY          (CPCSR_H2DIV_BUSY | CPCSR_H0DIV_BUSY | CPCSR_CDIV_BUSY)

/* DDR clock divider register(DDCDR) */
#define DDCDR_DCS_LSB           30
#define DDCDR_DCS_MASK          BITS_H2L(31, DDCDR_DCS_LSB)
#define DDCDR_DCS_STOP          (0 << DDCDR_DCS_LSB)
#define DDCDR_DCS_APLL          (1 << DDCDR_DCS_LSB)
#define DDCDR_DCS_MPLL          (2 << DDCDR_DCS_LSB)
#define DDCDR_CE_DDR            BIT29
#define DDCDR_DDR_BUSY          BIT28
#define DDCDR_DDR_STOP          BIT27
#define DDCDR_GATE_EN           BIT26
#define DDCDR_DDR_CHANGE_EN     BIT25
#define DDCDR_DDR               BIT24
#define DDCDR_DDRDIV_LSB        0
#define DDCDR_DDRDIV_MASK       BITS_H2L(3, DDCDR_DDRDIV_LSB)

/*MACPHY clock divider Register (MACCDR)*/
#define MACCDR_MACPCS           BIT31
#define MACCDR_CE_MAC           BIT29
#define MACCDR_MAC_BUSY         BIT28
#define MACCDR_MAC_STOP         BIT27
#define MACCDR_MACCDR_LSB       BIT0
#define MACCDR_MACCDR_MASK      BITS_H2L(7,MACCDR_MACCDR_LSB)

/* I2S device clock divider register(I2SCDR) */
#define I2SCDR_I2PCS            BIT31
#define I2SCDR_I2CS             BIT30

#define I2SCDR_I2SDIV_M_LSB     13
#define I2SCDR_I2SDIV_M_MASK    BITS_H2L(21,I2SCDR_I2SDIV_M_LSB)
#define I2SCDR_I2SDIV_N_LSB     0       /* I2SCDR bit */
#define I2SCDR_I2SDIV_N_MASK    BITS_H2L(7, I2SCDR_I2SDIV_N_LSB)


/* I2S device clock divider register(I2SCDR1) */
#define I2SCDR1_NEN             BIT31
#define I2SCDR1_DEN             BIT30
#define I2SCDR1_I2SDIV_D_LSB    0
#define I2SCDR1_I2SDIV_D_MASK   BITS_H2L(12,I2SCDR1_I2SDIV_D_LSB)

/* LCD pix clock divider register(LPCDR) */
#define LPCDR_LPCS_LSB          31
#define LPCDR_LPCS_APLL         (0 << LPCDR_LPCS_LSB)
#define LPCDR_LPCS_MPLL         (1 << LPCDR_LPCS_LSB)
#define LPCDR_CE_LCD            BIT28
#define LPCDR_LCD_BUSY          BIT27
#define LPCDR_LCD_STOP          BIT26

#define LPCDR_PIXDIV_LSB        0       /* LPCDR bit */
#define LPCDR_PIXDIV_MASK       BITS_H2L(7, LPCDR_PIXDIV_LSB)

/* MSC clock divider register(MSCCDR) */
#define MSCCDR_MPCS_LSB         31       /* MPCS bit */
#define MSCCDR_MPCS_APLL        (0 << MSCCDR_MPCS_LSB)
#define MSCCDR_MPCS_MPLL        (1 << MSCCDR_MPCS_LSB)

#define MSCCDR_CE_MSC           BIT29
#define MSCCDR_MSC_BUSY         BIT28
#define MSCCDR_MSC_STOP         BIT27
#define MSCCDR_S_CLK0_SEL       BIT15

#define MSCCDR_MSCDIV_LSB       0       /* MSCCDR bit */
#define MSCCDR_MSCDIV_MASK      BITS_H2L(7, MSCCDR_MSCDIV_LSB)


/* OTG PHY clock divider register(USBCDR) */
#define USBCDR_UCS              BIT31
#define USBCDR_UPCS             BIT30
#define USBCDR_CE_USB           BIT29
#define USBCDR_USB_BUSY         BIT28
#define USBCDR_USB_STOP         BIT27

#define USBCDR_OTGDIV_LSB       0       /* USBCDR bit */
#define USBCDR_OTGDIV_MASK      BITS_H2L(7, USBCDR_OTGDIV_LSB)

/* SSI clock divider register(SSICDR) */
#define SSICDR_SPCS             BIT31
#define SSICDR_SCS              BIT30
#define SSICDR_CE_SSI           BIT29
#define SSICDR_SSI_BUSY         BIT28
#define SSICDR_SSI_STOP         BIT27
#define SSICDR_SSIDIV_LSB       0       /* SSICDR bit */
#define SSICDR_SSIDIV_MASK      BITS_H2L(7, SSICDR_SSIDIV_LSB)

/* CIM mclk clock divider register(CIMCDR) */
#define CIMCDR_CIMPCS_APLL      (0 << 31)
#define CIMCDR_CIMPCS_MPLL      BIT31
#define CIMCDR_CE_CIM           BIT29
#define CIMCDR_CIM_BUSY         BIT28
#define CIMCDR_CIM_STOP         BIT27

#define CIMCDR_CIMDIV_LSB       0       /* CIMCDR bit */
#define CIMCDR_CIMDIV_MASK      BITS_H2L(7, CIMCDR_CIMDIV_LSB)


/* PCM device clock divider register(PCMCDR) */
#define PCMCDR_PCMPCS_LSB       30
#define PCMCDR_PCMPCS_MASK      BITS_H2L(31,PCMCDR_PCMPCS_LSB)
#define PCMCDR_PCMPCS_SCLK_A    0 << PCMCDR_PCMPCS_LSB
#define PCMCDR_PCMPCS_EXTCLK    1 << PCMCDR_PCMPCS_LSB
#define PCMCDR_PCMPCS_MPLL      2 << PCMCDR_PCMPCS_LSB
#define PCMCDR_CE_PCM           BIT29
#define PCMCDR_PCMDIV_M_LSB     13
#define PCMCDR_PCMDIV_M_MASK    BITS_H2L(21,PCMCDR_PCMDIV_M_LSB)
#define PCMCDR_PCMDIV_N_LSB     0
#define PCMCDR_PCMDIV_N_MASK    BITS_H2L(12,PCMCDR_PCMDIV_N_LSB)

/* PCM device clock divider register(PCMCDR1) */

#define PCMCDR1_PCM_NEN         BIT31
#define PCMCDR1_PCM_DEN         BIT30
#define PCMCDR1_PCMDIV_D_LSB    0
#define PCMCDR1_PCMDIV_D_MASK   BITS_H2L(12,PCMCDR1_PCMDIV_D_LSB)

/* MAC PHY Control Register (MPHYC) */
#define MPHYC_MODE_SEL          BIT31  //useless now
#define MPHYC_MAC_SPEED_LSB     29
#define MPHYC_MAC_SPEED_MASK    BITS_H2L(30,MPHYC_MAC_SPEED_LSB)
#define MPHYC_SOFT_RST          BIT3
#define MPHYC_PHY_INTF_LSB      0
#define MPHYC_PHY_INTF_MASK     BITS_H2L(2,MPHYC_PHY_INTF_MASK) //useless now

/* CPM Interrupt Register (CPM_INTR)*/
#define CPM_INTR_VBUS_INTR      BIT1
#define CPM_INTR_ADEV_INTR      BIT0

/* CPM Interrupt Enable Register (CPM_INTRE)*/
#define CPM_INTRE_VBUS_INTRE    BIT1
#define CPM_INTRE_ADEV_INTRE    BIT0

/* CPM scratch pad protected register(CPSPPR) */
#define CPSPPR_CPSPR_WRITABLE   (0x00005a5a)

/* OTG parameter control register(USBPCR) */
#define USBPCR_USB_MODE         BIT31
#define USBPCR_AVLD_REG         BIT30
#define USBPCR_INCRM            BIT27   /* INCR_MASK bit */
#define USBPCR_TXRISE_TUNE      BIT26
#define USBPCR_COMMONONN        BIT25
#define USBPCR_VBUSVLDEXT       BIT24
#define USBPCR_VBUSVLDEXTSEL    BIT23
#define USBPCR_POR              BIT22
#define USBPCR_SIDDQ            BIT21
#define USBPCR_OTG_DISABLE      BIT20
#define USBPCR_TXPREEMPHTUNE    BIT6

#define USBPCR_IDPULLUP_LSB     28   /* IDPULLUP_MASK bit */
#define USBPCR_IDPULLUP_MASK    BITS_H2L(29, USBPCR_IDPULLUP_LSB)

#define USBPCR_COMPDISTUNE_LSB  17
#define USBPCR_COMPDISTUNE_MASK BITS_H2L(19, USBPCR_COMPDISTUNE_LSB)

#define USBPCR_OTGTUNE_LSB      14
#define USBPCR_OTGTUNE_MASK     BITS_H2L(16, USBPCR_OTGTUNE_LSB)

#define USBPCR_SQRXTUNE_LSB     11
#define USBPCR_SQRXTUNE_MASK    BITS_H2L(13, USBPCR_SQRXTUNE_LSB)

#define USBPCR_TXFSLSTUNE_LSB   7
#define USBPCR_TXFSLSTUNE_MASK  BITS_H2L(10, USBPCR_TXFSLSTUNE_LSB)

#define USBPCR_TXRISETUNE_LSB   4
#define USBPCR_TXRISETUNE_MASK  BITS_H2L(5, USBPCR_TXRISETUNE_LSB)

#define USBPCR_TXVREFTUNE_LSB   0
#define USBPCR_TXVREFTUNE_MASK  BITS_H2L(3, USBPCR_TXVREFTUNE_LSB)

/* OTG reset detect timer register(USBRDT) */
#define USBRDT_HB_MASK          BIT26
#define USBRDT_VBFIL_LD_EN      BIT25
#define USBRDT_IDDIG_EN         BIT24
#define USBRDT_IDDIG_REG        BIT23

#define USBRDT_USBRDT_LSB       0
#define USBRDT_USBRDT_MASK      BITS_H2L(22, USBRDT_USBRDT_LSB)

/* OTG parameter control register(USBPCR1) */
#define USBPCR1_REG             BIT31
#define USBPCR1_USB_SEL         BIT28
#define USBPCR1_REFCLKSEL_LSB   26
#define USBPCR1_REFCLKSEL_MASK  BITS_H2L(27, USBPCR1_REFCLKSEL_LSB)

#define USBPCR1_REFCLKDIV_LSB   24
#define USBPCR1_REFCLKDIV_MASK  BITS_H2L(25, USBPCR1_REFCLKDIV_LSB)

#define USBPCR1_PORT_RST        BIT21

#define USBPCR1_WORD_IF0        BIT19
#define USBPCR1_WORD_IF1        BIT18


/* APLL control register (CPXPCR) */
#define CPAPCR_BS               BIT31
#define CPAPCR_M_LSB            24
#define CPAPCR_M_MASK           BITS_H2L(30, CPAPCR_M_LSB)

#define CPAPCR_N_LSB            18
#define CPAPCR_N_MASK           BITS_H2L(22, CPAPCR_N_LSB)

#define CPAPCR_OD_LSB           16
#define CPAPCR_OD_MASK          BITS_H2L(17, CPAPCR_OD_LSB)

#define CPAPCR_LOCK             BIT15   /* LOCK bit */
#define CPAPCR_ON               BIT10
#define CPAPCR_BP               BIT9
#define CPAPCR_EN               BIT8
#define CPAPCR_PLLST_LSB        0
#define CPAPCR_PLLST_MASK       BITS_H2L(7,CPAPCR_PLLST_LSB)

#define CPM_CPAPCR_EN           CPAPCR_EN
#define CPM_CPAPCR_ON           CPAPCR_ON

/* MPLL control register (CPXPCR) */
#define CPMPCR_BS               BIT31
#define CPMPCR_M_LSB            24
#define CPMPCR_M_MASK           BITS_H2L(30, CPAPCR_M_LSB)

#define CPMPCR_N_LSB            18
#define CPMPCR_N_MASK           BITS_H2L(22, CPAPCR_N_LSB)

#define CPMPCR_OD_LSB           16
#define CPMPCR_OD_MASK          BITS_H2L(17, CPAPCR_OD_LSB)

#define CPMPCR_EN               BIT7
#define CPMPCR_BP               BIT6
#define CPMPCR_LOCK             BIT1    /* LOCK bit */
#define CPMPCR_ON               BIT0

#define CPM_CPMPCR_EN           CPMPCR_EN
#define CPM_CPMPCR_ON           CPMPCR_ON



/* Low power control register(LCR) */
#define LCR_PST_LSB             8
#define LCD_PST_MASK            BITS_H2L(19,LCR_PST_LSB)
#define LCR_LPM_LSB             0
#define LCR_LPM_MASK            BITS_H2L(1,LCR_LPM_LSB)

/* Clock gate register 0(CGR0) */
#define CLKGR0_DDR              BIT31
#define CLKGR0_CPU              BIT30
#define CLKGR0_AHB0             BIT29
#define CLKGR0_APB0             BIT28
#define CLKGR0_RTC              BIT27
#define CLKGR0_PCM              BIT26
#define CLKGR0_MAC              BIT25
#define CLKGR0_AES              BIT24
#define CLKGR0_LCD              BIT23
#define CLKGR0_CIM              BIT22
#define CLKGR0_PDMA             BIT21
#define CLKGR0_OST              BIT20
#define CLKGR0_SSI              BIT19
#define CLKGR0_TCU              BIT18
#define CLKGR0_DMIC             BIT17
#define CLKGR0_UART2            BIT16
#define CLKGR0_UART1            BIT15
#define CLKGR0_UART0            BIT14
#define CLKGR0_SADC             BIT13
#define CLKGR0_JPEG             BIT12
#define CLKGR0_AIC              BIT11
#define CLKGR0_I2C3             BIT10
#define CLKGR0_I2C2             BIT9
#define CLKGR0_I2C1             BIT8
#define CLKGR0_I2C0             BIT7
#define CLKGR0_SCC              BIT6
#define CLKGR0_MSC1             BIT5
#define CLKGR0_MSC0             BIT4
#define CLKGR0_OTG              BIT3
#define CLKGR0_SFC              BIT2
#define CLKGR0_EFUSE            BIT1
#define CLKGR0_NEMC             BIT0

/* CPM MEST SEL Register */

#define MEST_SEL_TST8           BIT8
#define MEST_SEL_TST7           BIT7
#define MEST_SEL_TST4           BIT4
#define MEST_SEL_TST3           BIT3
#define MEST_SEL_TST1           BIT1
#define MEST_SEL_TST0           BIT0

/*Soft Reset and Bus Control Register (SRBC)*/

#define SRBC_JPEG_SR            BIT31
#define SRBC_JPEG_STP           BIT30
#define SRBC_JPEG_ACK           BIT29
#define SRBC_LCD_SR             BIT25
#define SRBC_LCD_STP            BIT24
#define SRBC_LCD_ACK            BIT23
#define SRBC_CIM_STP            BIT21
#define SRBC_CIM_ACK            BIT20
#define SRBC_CPU_STP            BIT15
#define SRBC_CPU_ACK            BIT14
#define SRBC_OTG_SR             BIT12
#define SRBC_AHB2_STP           BIT8
#define SRBC_AHB2_ACK           BIT7
#define SRBC_DDR_STP            BIT6
#define SRBC_DDR_ACK            BIT5


/* Oscillator and power control register(OPCR) */
#define OPCR_IDLE_DIS           BIT31
#define OPCR_MASK_INT           BIT30
#define OPCR_MASK_VPU           BIT29  //ONLY FOR DEBUG
#define OPCR_GATE_SCLK_ABUS     BIT28
#define OPCR_L2C_PD             BIT25
#define OPCR_REQ_MODE           BIT24
#define OPCR_GATE_USBPHY_CLK    BIT23
#define OPCR_DIS_STOP_MUX       BIT22
#define OPCR_O1ST_LSB           8
#define OPCR_O1ST_MASK          BITS_H2L(19, OPCR_O1ST_LSB)
#define OPCR_OTGPHY0_ENABLE     BIT7    /* otg */
#define OPCR_OTGPHY1_ENABLE     BIT6    /* uhc */
#define OPCR_USBPHY_ENABLE      (OPCR_OTGPHY0_ENABLE | OPCR_OTGPHY1_ENABLE)
#define OPCR_O1SE               BIT4
#define OPCR_PD                 BIT3
#define OPCR_ERCS               BIT2
#define OPCR_BUSMODE            BIT1



/* Reset status register(RSR) */
#define RSR_HR                  BIT3
#define RSR_P0R                 BIT2
#define RSR_WR                  BIT1
#define RSR_PR                  BIT0


#ifndef __ASSEMBLY__

#define REG_CPM_CPCCR           REG32(CPM_BASE + CPM_CPCCR)
#define REG_CPM_CPCSR           REG32(CPM_BASE + CPM_CPCSR)
#define REG_CPM_DDCDR           REG32(CPM_BASE + CPM_DDCDR)
#define REG_CPM_MACCDR          REG32(CPM_BASE + CPM_MACCDR)
#define REG_CPM_I2SCDR          REG32(CPM_BASE + CPM_I2SCDR)
#define REG_CPM_I2SCDR1         REG32(CPM_BASE + CPM_I2SCDR1)
#define REG_CPM_LPCDR           REG32(CPM_BASE + CPM_LPCDR)
#define REG_CPM_MSC0CDR         REG32(CPM_BASE + CPM_MSC0CDR)
#define REG_CPM_MSC1CDR         REG32(CPM_BASE + CPM_MSC1CDR)
#define REG_CPM_USBCDR          REG32(CPM_BASE + CPM_USBCDR)
#define REG_CPM_SSICDR          REG32(CPM_BASE + CPM_SSICDR)
#define REG_CPM_CIMCDR          REG32(CPM_BASE + CPM_CIMCDR)
#define REG_CPM_PCMCDR          REG32(CPM_BASE + CPM_PCMCDR)
#define REG_CPM_PCMCDR1         REG32(CPM_BASE + CPM_PCMCDR1)
#define REG_CPM_MPHYC           REG32(CPM_BASE + CPM_MPHYC)
#define REG_CPM_INTRCDR         REG32(CPM_BASE + CPM_INTRCDR)
#define REG_CPM_INTRECDR        REG32(CPM_BASE + CPM_INTRECDR)
#define REG_CPM_CPSPR           REG32(CPM_BASE + CPM_CPSPR)
#define REG_CPM_CPSPPR          REG32(CPM_BASE + CPM_CPSPPR)
#define REG_CPM_USBPCR          REG32(CPM_BASE + CPM_USBPCR)
#define REG_CPM_USBRDT          REG32(CPM_BASE + CPM_USBRDT)
#define REG_CPM_USBVBFIL        REG32(CPM_BASE + CPM_USBVBFIL)
#define REG_CPM_USBPCR1         REG32(CPM_BASE + CPM_USBPCR1)
#define REG_CPM_CPAPCR          REG32(CPM_BASE + CPM_CPAPCR)
#define REG_CPM_CPMPCR          REG32(CPM_BASE + CPM_CPMPCR)

#define REG_CPM_LCR             REG32(CPM_BASE + CPM_LCR)
#define REG_CPM_PSWC0ST         REG32(CPM_BASE + CPM_PSWC0ST)
#define REG_CPM_PSWC1ST         REG32(CPM_BASE + CPM_PSWC1ST)
#define REG_CPM_PSWC2ST         REG32(CPM_BASE + CPM_PSWC2ST)
#define REG_CPM_PSWC3ST         REG32(CPM_BASE + CPM_PSWC3ST)
#define REG_CPM_CLKGR0          REG32(CPM_BASE + CPM_CLKGR0)
#define REG_CPM_SRBC            REG32(CPM_BASE + CPM_SRBC)
#define REG_CPM_SLBC            REG32(CPM_BASE + CPM_SLBC)
#define REG_CPM_SLPC            REG32(CPM_BASE + CPM_SLPC)
#define REG_CPM_OPCR            REG32(CPM_BASE + CPM_OPCR)
#define REG_CPM_RSR             REG32(CPM_BASE + CPM_RSR)

#define _REG_CPM_MSCCDR(n)      REG_CPM_MSC##n##CDR
#define REG_CPM_MSCCDR(n)       _REG_CPM_MSCCDR(n)

/* CPM read write */
#define cpm_inl(off)            readl(CPM_BASE + off)
#define cpm_outl(val,off)       writel(val, CPM_BASE + off)
#define cpm_test_bit(bit,off)   (cpm_inl(off) & 0x1<<(bit))
#define cpm_set_bit(bit,off)    (cpm_outl((cpm_inl(off) | 0x1<<(bit)),off))
#define cpm_clear_bit(bit,off)  (cpm_outl(cpm_inl(off) & ~(0x1 << bit), off))

#endif /* __ASSEMBLY__ */

#endif /* _X1000_CPM_H_ */
