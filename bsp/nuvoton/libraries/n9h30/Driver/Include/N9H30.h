/**************************************************************************//**
 * @file     N9H30.h
 * @version  V1.00
 * @brief    N9H30 peripheral access layer header file.
 *           This file contains all the peripheral register's definitions
 *           and memory mapping for NuMicro N9H30 MCU.
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
/**
   \mainpage NuMicro N9H30 Family Driver Reference Guide
   *
   * <b>Introduction</b>
   *
   * This user manual describes the usage of N9H30 family device driver
   *
   * <b>Disclaimer</b>
   *
   * The Software is furnished "AS IS", without warranty as to performance or results, and
   * the entire risk as to performance or results is assumed by YOU. Nuvoton disclaims all
   * warranties, express, implied or otherwise, with regard to the Software, its use, or
   * operation, including without limitation any and all warranties of merchantability, fitness
   * for a particular purpose, and non-infringement of intellectual property rights.
   *
   * <b>Important Notice</b>
   *
   * Nuvoton Products are neither intended nor warranted for usage in systems or equipment,
   * any malfunction or failure of which may cause loss of human life, bodily injury or severe
   * property damage. Such applications are deemed, "Insecure Usage".
   *
   * Insecure usage includes, but is not limited to: equipment for surgical implementation,
   * atomic energy control instruments, airplane or spaceship instruments, the control or
   * operation of dynamic, brake or safety systems designed for vehicular use, traffic signal
   * instruments, all types of safety devices, and other applications intended to support or
   * sustain life.
   *
   * All Insecure Usage shall be made at customer's risk, and in the event that third parties
   * lay claims to Nuvoton as a result of customer's Insecure Usage, customer shall indemnify
   * the damages and liabilities thus incurred by Nuvoton.
   *
   * Please note that all data and specifications are subject to change without notice. All the
   * trademarks of products and companies mentioned in this document belong to their respective
   * owners.
   *
   * <b>Copyright Notice</b>
   *
   * Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
   */

#ifndef __N9H30_H__
    #define __N9H30_H__

    #include <stdint.h>

    /** @addtogroup N9H30_PERIPHERAL_MEM_MAP N9H30 Peripheral Memory Base
    Memory Mapped Structure for N9H30 Peripheral
    @{
    */

    /*!< AHB peripherals */
    #define    SYS_BA    0xB0000000  /*!< System Global Control */
    #define    CLK_BA    0xB0000200  /*!< Clock Control */
    #define    EBI_BA    0xB0001000  /*!< EBI Control */
    #define    SDIC_BA   0xB0001800  /*!< SDRAM (SDR/DDR/DDR2) Control */
    #define    EMC0_BA   0xB0002000  /*!< Ethernet MAC 0 Control */
    #define    EMC1_BA   0xB0003000  /*!< Ethernet MAC 1 Control */
    #define    GDMA_BA   0xB0004000  /*!< GDMA control */
    #define    USBH_BA   0xB0005000  /*!< USB Host EHCI Control */
    #define    USBD_BA   0xB0006000  /*!< USB Device Control */
    #define    USBO_BA   0xB0007000  /*!< OHCI USB Host Control */
    #define    LCM_BA    0xB0008000  /*!< Display, LCM Interface */
    #define    ACTL_BA   0xB0009000  /*!< Audio Control */
    #define    JPEG_BA   0xB000A000  /*!< JPEG Engine Control */
    #define    GE_BA     0xB000B000  /*!< 2-D Graphic Engine */
    #define    SDH_BA    0xB000C000  /*!< SD/SDIO Host Controller */
    #define    FMI_BA    0xB000D000  /*!< Flash Memory Card Interface */
    #define    CAP_BA    0xB000E000  /*!< Sensor (Capture) Interface Control */
    #define    CRPT_BA   0xB000F000  /*!< Crypto Engine Control */

    /*!< APB peripherals */
    #define    UART0_BA  0xB8000000  /*!< UART0 Control */
    #define    UART1_BA  0xB8000100  /*!< UART1 Control (High-Speed UART) */
    #define    UART2_BA  0xB8000200  /*!< UART2 Control (High-Speed UART) */
    #define    UART3_BA  0xB8000300  /*!< UART3 Control  */
    #define    UART4_BA  0xB8000400  /*!< UART4 Control (High-Speed UART) */
    #define    UART5_BA  0xB8000500  /*!< UART5 Control */
    #define    UART6_BA  0xB8000600  /*!< UART6 Control (High-Speed UART) */
    #define    UART7_BA  0xB8000700  /*!< UART7 Control */
    #define    UART8_BA  0xB8000800  /*!< UART8 Control (High-Speed UART) */
    #define    UART9_BA  0xB8000900  /*!< UART9 Control */
    #define    UARTA_BA  0xB8000A00  /*!< UARTA Control (High-Speed UART) */
    #define    TMR0_BA   0xB8001000  /*!< Timer 0 */
    #define    TMR1_BA   0xB8001010  /*!< Timer 1 */
    #define    TMR2_BA   0xB8001020  /*!< Timer 2 */
    #define    TMR3_BA   0xB8001030  /*!< Timer 3 */
    #define    TMR4_BA   0xB8001040  /*!< Timer 4 */
    #define    ETMR0_BA  0xB8001400  /*!< Enhanced Timer 0 */
    #define    ETMR1_BA  0xB8001500  /*!< Enhanced Timer 1 */
    #define    ETMR2_BA  0xB8001600  /*!< Enhanced Timer 2 */
    #define    ETMR3_BA  0xB8001700  /*!< Enhanced Timer 3 */
    #define    WDT_BA    0xB8001800  /*!< Watch Dog Timer */
    #define    WWDT_BA   0xB8001900  /*!< Window Watch Dog Timer */
    #define    AIC_BA    0xB8002000  /*!< Interrupt Controller */
    #define    GPIO_BA   0xB8003000  /*!< GPIO Control */
    #define    RTC_BA    0xB8004000  /*!< Real Time Clock Control */
    #define    SC0_BA    0xB8005000  /*!< Smart Card 0 Control */
    #define    SC1_BA    0xB8005400  /*!< Smart Card 1 Control */
    #define    I2C0_BA   0xB8006000  /*!< I2C 0 Control */
    #define    I2C1_BA   0xB8006100  /*!< I2C 1 Control */
    #define    SPI0_BA   0xB8006200  /*!< Serial Peripheral Interface 0 */
    #define    SPI1_BA   0xB8006300  /*!< Serial Peripheral Interface 1 */
    #define    PWM_BA    0xB8007000  /*!< Pulse Width Modulation (PWM) Control */
    #define    ADC_BA    0xB800A000  /*!< ADC Control */
    #define    CAN0_BA   0xB800B000  /*!< CAN 0 Control */
    #define    CAN1_BA   0xB800B400  /*!< CAN 1 Control */
    #define    MTP_BA    0xB800C000  /*!< MTP Control */

    /*@}*/ /* end of group N9H30_PERIPHERAL_MEM_MAP */

    /******************************************************************************/
    /*                Device Specific Peripheral registers structures             */
    /******************************************************************************/
    /** @addtogroup N9H30_Peripherals N9H30 Control Register
    N9H30 Device Specific Peripheral registers structures
    @{
    */

    /*---------------------- System Manger Controller -------------------------*/
    /**
    @addtogroup SYS System Manger Controller(SYS)
    Memory Mapped Structure for SYS Controller
    @{ */

    #define    REG_SYS_PDID         (SYS_BA+0x000)  /*!< Product Identifier Register */
    #define    REG_SYS_PWRON        (SYS_BA+0x004)  /*!< Power-On Setting Register */
    #define    REG_SYS_ARBCON       (SYS_BA+0x008)  /*!< Arbitration Control Register */
    #define    REG_SYS_LVRDCR       (SYS_BA+0x020)  /*!< Low Voltage Reset & Detect Control Register */
    #define    REG_SYS_MISCFCR      (SYS_BA+0x030)  /*!< Miscellaneous Function Control Register */
    #define    REG_SYS_MISCIER      (SYS_BA+0x040)  /*!< Miscellaneous Interrupt Enable Register */
    #define    REG_SYS_MISCISR      (SYS_BA+0x044)  /*!< Miscellaneous Interrupt Status Register */
    #define    REG_SYS_WKUPSER      (SYS_BA+0x058)  /*!< System Wakeup Source Enable Register */
    #define    REG_SYS_WKUPSSR      (SYS_BA+0x05C)  /*!< System Wakeup Source Status Register */
    #define    REG_SYS_AHBIPRST     (SYS_BA+0x060)  /*!< AHB IP Reset Control Register */
    #define    REG_SYS_APBIPRST0    (SYS_BA+0x064)  /*!< APB IP Reset Control Register 0 */
    #define    REG_SYS_APBIPRST1    (SYS_BA+0x068)  /*!< APB IP Reset Control Register 1 */
    #define    REG_SYS_RSTSTS       (SYS_BA+0x06C)  /*!< Reset Source Active Status Register */
    #define    REG_SYS_GPA_MFPL     (SYS_BA+0x070)  /*!< GPIOA Low Byte Multiple Function Control Register */
    #define    REG_SYS_GPA_MFPH     (SYS_BA+0x074)  /*!< GPIOA High Byte Multiple Function Control Register */
    #define    REG_SYS_GPB_MFPL     (SYS_BA+0x078)  /*!< GPIOB Low Byte Multiple Function Control Register */
    #define    REG_SYS_GPB_MFPH     (SYS_BA+0x07C)  /*!< GPIOB High Byte Multiple Function Control Register */
    #define    REG_SYS_GPC_MFPL     (SYS_BA+0x080)  /*!< GPIOC Low Byte Multiple Function Control Register */
    #define    REG_SYS_GPC_MFPH     (SYS_BA+0x084)  /*!< GPIOC High Byte Multiple Function Control Register */
    #define    REG_SYS_GPD_MFPL     (SYS_BA+0x088)  /*!< GPIOD Low Byte Multiple Function Control Register */
    #define    REG_SYS_GPD_MFPH     (SYS_BA+0x08C)  /*!< GPIOD High Byte Multiple Function Control Register */
    #define    REG_SYS_GPE_MFPL     (SYS_BA+0x090)  /*!< GPIOE Low Byte Multiple Function Control Register */
    #define    REG_SYS_GPE_MFPH     (SYS_BA+0x094)  /*!< GPIOE High Byte Multiple Function Control Register */
    #define    REG_SYS_GPF_MFPL     (SYS_BA+0x098)  /*!< GPIOF Low Byte Multiple Function Control Register */
    #define    REG_SYS_GPF_MFPH     (SYS_BA+0x09C)  /*!< GPIOF High Byte Multiple Function Control Register */
    #define    REG_SYS_GPG_MFPL     (SYS_BA+0x0A0)  /*!< GPIOG Low Byte Multiple Function Control Register */
    #define    REG_SYS_GPG_MFPH     (SYS_BA+0x0A4)  /*!< GPIOG High Byte Multiple Function Control Register */
    #define    REG_SYS_GPH_MFPL     (SYS_BA+0x0A8)  /*!< GPIOH Low Byte Multiple Function Control Register */
    #define    REG_SYS_GPH_MFPH     (SYS_BA+0x0AC)  /*!< GPIOH High Byte Multiple Function Control Register */
    #define    REG_SYS_GPI_MFPL     (SYS_BA+0x0B0)  /*!< GPIOI Low Byte Multiple Function Control Register */
    #define    REG_SYS_GPI_MFPH     (SYS_BA+0x0B4)  /*!< GPIOI High Byte Multiple Function Control Register */
    #define    REG_SYS_GPJ_MFPL     (SYS_BA+0x0B8)  /*!< GPIOJ Low Byte Multiple Function Control Register */
    #define    REG_SYS_DDR_DSCTL    (SYS_BA+0x0F0)  /*!< DDR I/O Driving Strength Control Register */
    #define    REG_SYS_PORDISCR     (SYS_BA+0x100)  /*!< Power-On-Reset Disable Control Register */
    #define    REG_SYS_ICEDBGCR     (SYS_BA+0x104)  /*!< ICE Debug Interface Control Register */
    #define    REG_SYS_ERRADDCR     (SYS_BA+0x108)  /*!< Error Response Address Control Regsiter */
    #define    REG_SYS_REGWPCTL     (SYS_BA+0x1FC)  /*!< Register Write-Protection Control Register */

    /**@}*/ /* end of SYS register group */

    /*---------------------- System Clock Controller -------------------------*/
    /**
    @addtogroup CLK System Clock Controller(CLK)
    Memory Mapped Structure for CLK Controller
    @{ */

    #define    REG_CLK_PMCON        (CLK_BA+0x00) /*!< Power Management Control Register */
    #define    REG_CLK_HCLKEN       (CLK_BA+0x10) /*!< AHB IP Clock Enable Control Register */
    #define    REG_CLK_PCLKEN0      (CLK_BA+0x18) /*!< APB IP Clock Enable Control Register 0 */
    #define    REG_CLK_PCLKEN1      (CLK_BA+0x1C) /*!< APB IP Clock Enable Control Register 1 */
    #define    REG_CLK_DIVCTL0      (CLK_BA+0x20) /*!< Clock Divider Control Register 0 */
    #define    REG_CLK_DIVCTL1      (CLK_BA+0x24) /*!< Clock Divider Control Register 1 */
    #define    REG_CLK_DIVCTL2      (CLK_BA+0x28) /*!< Clock Divider Control Register 2 */
    #define    REG_CLK_DIVCTL3      (CLK_BA+0x2C) /*!< Clock Divider Control Register 3 */
    #define    REG_CLK_DIVCTL4      (CLK_BA+0x30) /*!< Clock Divider Control Register 4 */
    #define    REG_CLK_DIVCTL5      (CLK_BA+0x34) /*!< Clock Divider Control Register 5 */
    #define    REG_CLK_DIVCTL6      (CLK_BA+0x38) /*!< Clock Divider Control Register 6 */
    #define    REG_CLK_DIVCTL7      (CLK_BA+0x3C) /*!< Clock Divider Control Register 7 */
    #define    REG_CLK_DIVCTL8      (CLK_BA+0x40) /*!< Clock Divider Control Register 8 */
    #define    REG_CLK_DIVCTL9      (CLK_BA+0x44) /*!< Clock Divider Control Register 9 */
    #define    REG_CLK_APLLCON      (CLK_BA+0x60) /*!< APLL Control Register */
    #define    REG_CLK_UPLLCON      (CLK_BA+0x64) /*!< UPLL Control Register */
    #define    REG_CLK_PLLSTBCNTR   (CLK_BA+0x80) /*!< PLL Stable Counter and Test Clock Control Register */

    /**@}*/ /* end of CLK register group */


    /*---------------------- External Bus Interface Controller -------------------------*/
    /**
    @addtogroup EBI External Bus Interface Controller(EBI)
    Memory Mapped Structure for EBI Controller
    @{ */

    #define    REG_EBI_CTL          (EBI_BA+0x000)  /*!< EBI control register */
    #define    REG_EBI_BNKCTL0      (EBI_BA+0x018)  /*!< External I/O 0 control register */
    #define    REG_EBI_BNKCTL1      (EBI_BA+0x01C)  /*!< External I/O 1 control register */
    #define    REG_EBI_BNKCTL2      (EBI_BA+0x020)  /*!< External I/O 2 control register */
    #define    REG_EBI_BNKCTL3      (EBI_BA+0x024)  /*!< External I/O 3 control register */
    #define    REG_EBI_BNKCTL4      (EBI_BA+0x028)  /*!< External I/O 4 control register */

    /**@}*/ /* end of EBI register group */


    /*---------------------- Ethernet MAC Controller -------------------------*/
    /**
    @addtogroup EMAC Ethernet MAC Controller(EMAC)
    Memory Mapped Structure for EMAC Controller
    @{ */

    #define     REG_EMAC0_CAMCMR      (EMC0_BA+0x000) /*!< CAM Command Register */
    #define     REG_EMAC0_CAMEN       (EMC0_BA+0x004) /*!< CAM Enable Register */
    #define     REG_EMAC0_CAM0M       (EMC0_BA+0x008)  /*!< CAM0 Most Significant Word Register */
    #define     REG_EMAC0_CAM0L       (EMC0_BA+0x00c)  /*!< CAM0 Least Significant Word Register */
    #define     REG_EMAC0_CAMxM_Reg(x)(REG_EMAC0_CAM0M+(x)*0x8)  /*!< CAMx Most Significant Word Register */
    #define     REG_EMAC0_CAMxL_Reg(x)(REG_EMAC0_CAM0L+(x)*0x8)  /*!< CAMx Least Significant Word Register */
    #define     REG_EMAC0_TXDLSA      (EMC0_BA+0x088) /*!< Transmit Descriptor Link List Start Address Register */
    #define     REG_EMAC0_RXDLSA      (EMC0_BA+0x08C) /*!< Receive Descriptor Link List Start Address Register */
    #define     REG_EMAC0_MCMDR       (EMC0_BA+0x090) /*!< MAC Command Register */
    #define     REG_EMAC0_MIID        (EMC0_BA+0x094) /*!< MII Management Data Register */
    #define     REG_EMAC0_MIIDA       (EMC0_BA+0x098) /*!< MII Management Control and Address Register */
    #define     REG_EMAC0_FFTCR       (EMC0_BA+0x09C) /*!< FIFO Threshold Control Register */
    #define     REG_EMAC0_TSDR        (EMC0_BA+0x0a0) /*!< Transmit Start Demand Register */
    #define     REG_EMAC0_RSDR        (EMC0_BA+0x0a4) /*!< Receive Start Demand Register */
    #define     REG_EMAC0_DMARFC      (EMC0_BA+0x0a8) /*!< Maximum Receive Frame Control Register */
    #define     REG_EMAC0_MIEN        (EMC0_BA+0x0ac) /*!< MAC Interrupt Enable Register */
    #define     REG_EMAC0_MISTA       (EMC0_BA+0x0b0) /*!< MAC Interrupt Status Register */
    #define     REG_EMAC0_MGSTA       (EMC0_BA+0x0b4) /*!< MAC General Status Register */
    #define     REG_EMAC0_MPCNT       (EMC0_BA+0x0b8) /*!< Missed Packet Count Register */
    #define     REG_EMAC0_MRPC        (EMC0_BA+0x0bc) /*!< MAC Receive Pause Count Register */
    #define     REG_EMAC0_DMARFS      (EMC0_BA+0x0c8) /*!< DMA Receive Frame Status Register */
    #define     REG_EMAC0_CTXDSA      (EMC0_BA+0x0cc) /*!< Current Transmit Descriptor Start Address Register */
    #define     REG_EMAC0_CTXBSA      (EMC0_BA+0x0d0) /*!< Current Transmit Buffer Start Address Register */
    #define     REG_EMAC0_CRXDSA      (EMC0_BA+0x0d4) /*!< Current Receive Descriptor Start Address Register */
    #define     REG_EMAC0_CRXBSA      (EMC0_BA+0x0d8) /*!< Current Receive Buffer Start Address Register */
    #define     REG_EMAC0_TSCTL       (EMC0_BA+0x100) /*!< Time Stamp Control Register */
    #define     REG_EMAC0_TSSEC       (EMC0_BA+0x110) /*!< Time Stamp Counter Second Register */
    #define     REG_EMAC0_TSSUBSEC    (EMC0_BA+0x114) /*!< Time Stamp Counter Sub Second Register */
    #define     REG_EMAC0_TSINC       (EMC0_BA+0x118) /*!< Time Stamp Increment Register  */
    #define     REG_EMAC0_TSADDEN     (EMC0_BA+0x11c) /*!< Time Stamp Addend Register */
    #define     REG_EMAC0_TSUPDSEC    (EMC0_BA+0x120) /*!< Time Stamp Update Second Register */
    #define     REG_EMAC0_TSUPDSUBSEC (EMC0_BA+0x124) /*!< Time Stamp Update Sub Second Register */
    #define     REG_EMAC0_TSALMSEC    (EMC0_BA+0x128) /*!< Time Stamp Alarm Second Register */
    #define     REG_EMAC0_TSALMSUBSEC (EMC0_BA+0x12c) /*!< Time Stamp Alarm Sub Second Register */

    #define     REG_EMAC1_CAMCMR      (EMC1_BA+0x000) /*!< CAM Command Register */
    #define     REG_EMAC1_CAMEN       (EMC1_BA+0x004) /*!< CAM Enable Register */
    #define     REG_EMAC1_CAM0M       (EMC1_BA+0x008)  /*!< CAM0 Most Significant Word Register */
    #define     REG_EMAC1_CAM0L       (EMC1_BA+0x00c)  /*!< CAM0 Least Significant Word Register */
    #define     REG_EMAC1_CAMxM_Reg(x)(REG_EMAC1_CAM0M+(x)*0x8)  /*!< CAMx Most Significant Word Register */
    #define     REG_EMAC1_CAMxL_Reg(x)(REG_EMAC1_CAM0L+(x)*0x8)  /*!< CAMx Least Significant Word Register */
    #define     REG_EMAC1_TXDLSA      (EMC1_BA+0x088) /*!< Transmit Descriptor Link List Start Address Register */
    #define     REG_EMAC1_RXDLSA      (EMC1_BA+0x08C) /*!< Receive Descriptor Link List Start Address Register */
    #define     REG_EMAC1_MCMDR       (EMC1_BA+0x090) /*!< MAC Command Register */
    #define     REG_EMAC1_MIID        (EMC1_BA+0x094) /*!< MII Management Data Register */
    #define     REG_EMAC1_MIIDA       (EMC1_BA+0x098) /*!< MII Management Control and Address Register */
    #define     REG_EMAC1_FFTCR       (EMC1_BA+0x09C) /*!< FIFO Threshold Control Register */
    #define     REG_EMAC1_TSDR        (EMC1_BA+0x0a0) /*!< Transmit Start Demand Register */
    #define     REG_EMAC1_RSDR        (EMC1_BA+0x0a4) /*!< Receive Start Demand Register */
    #define     REG_EMAC1_DMARFC      (EMC1_BA+0x0a8) /*!< Maximum Receive Frame Control Register */
    #define     REG_EMAC1_MIEN        (EMC1_BA+0x0ac) /*!< MAC Interrupt Enable Register */
    #define     REG_EMAC1_MISTA       (EMC1_BA+0x0b0) /*!< MAC Interrupt Status Register */
    #define     REG_EMAC1_MGSTA       (EMC1_BA+0x0b4) /*!< MAC General Status Register */
    #define     REG_EMAC1_MPCNT       (EMC1_BA+0x0b8) /*!< Missed Packet Count Register */
    #define     REG_EMAC1_MRPC        (EMC1_BA+0x0bc) /*!< MAC Receive Pause Count Register */
    #define     REG_EMAC1_DMARFS      (EMC1_BA+0x0c8) /*!< DMA Receive Frame Status Register */
    #define     REG_EMAC1_CTXDSA      (EMC1_BA+0x0cc) /*!< Current Transmit Descriptor Start Address Register */
    #define     REG_EMAC1_CTXBSA      (EMC1_BA+0x0d0) /*!< Current Transmit Buffer Start Address Register */
    #define     REG_EMAC1_CRXDSA      (EMC1_BA+0x0d4) /*!< Current Receive Descriptor Start Address Register */
    #define     REG_EMAC1_CRXBSA      (EMC1_BA+0x0d8) /*!< Current Receive Buffer Start Address Register */
    #define     REG_EMAC1_TSCTL       (EMC1_BA+0x100) /*!< Time Stamp Control Register */
    #define     REG_EMAC1_TSSEC       (EMC1_BA+0x110) /*!< Time Stamp Counter Second Register */
    #define     REG_EMAC1_TSSUBSEC    (EMC1_BA+0x114) /*!< Time Stamp Counter Sub Second Register */
    #define     REG_EMAC1_TSINC       (EMC1_BA+0x118) /*!< Time Stamp Increment Register  */
    #define     REG_EMAC1_TSADDEN     (EMC1_BA+0x11c) /*!< Time Stamp Addend Register */
    #define     REG_EMAC1_TSUPDSEC    (EMC1_BA+0x120) /*!< Time Stamp Update Second Register */
    #define     REG_EMAC1_TSUPDSUBSEC (EMC1_BA+0x124) /*!< Time Stamp Update Sub Second Register */
    #define     REG_EMAC1_TSALMSEC    (EMC1_BA+0x128) /*!< Time Stamp Alarm Second Register */
    #define     REG_EMAC1_TSALMSUBSEC (EMC1_BA+0x12c) /*!< Time Stamp Alarm Sub Second Register */

    /**@}*/ /* end of EMAC register group */

    /*----------------------  General Direct Memory Access Controller -------------------------*/
    /**
    @addtogroup GDMA  General Direct Memory Access Controller(GDMA)
    Memory Mapped Structure for GDMA Controller
    @{ */

    #define     REG_GDMA_CTL0   (GDMA_BA+0x000)  /*!< Channel 0 Control Register */
    #define     REG_GDMA_SRCB0  (GDMA_BA+0x004)  /*!< Channel 0 Source Base Address Register */
    #define     REG_GDMA_DSTB0  (GDMA_BA+0x008)  /*!< Channel 0 Destination Base Address Register */
    #define     REG_GDMA_TCNT0  (GDMA_BA+0x00C)  /*!< Channel 0 Transfer Count Register */
    #define     REG_GDMA_CSRC0  (GDMA_BA+0x010)  /*!< Channel 0 Current Source Address Register */
    #define     REG_GDMA_CDST0  (GDMA_BA+0x014)  /*!< Channel 0 Current Destination Address Register */
    #define     REG_GDMA_CTCNT0 (GDMA_BA+0x018)  /*!< Channel 0 Current Transfer Count Register */
    #define     REG_GDMA_DADR0  (GDMA_BA+0x01C)  /*!< Channel 0 Descriptor Address Register */
    #define     REG_GDMA_CTL1   (GDMA_BA+0x020)  /*!< Channel 1 Control Register */
    #define     REG_GDMA_SRCB1  (GDMA_BA+0x024)  /*!< Channel 1 Source Base Address Register */
    #define     REG_GDMA_DSTB1  (GDMA_BA+0x028)  /*!< Channel 1 Destination Base Address Register */
    #define     REG_GDMA_TCNT1  (GDMA_BA+0x02C)  /*!< Channel 1 Transfer Count Register */
    #define     REG_GDMA_CSRC1  (GDMA_BA+0x030)  /*!< Channel 1 Current Source Address Register */
    #define     REG_GDMA_CDST1  (GDMA_BA+0x034)  /*!< Channel 1 Current Destination Address Register */
    #define     REG_GDMA_CTCNT1 (GDMA_BA+0x038)  /*!< Channel 1 Current Transfer Count Register */
    #define     REG_GDMA_DADR1  (GDMA_BA+0x03C)  /*!< Channel 1 Descriptor Address Register */
    #define     REG_GDMA_INTBUF0    (GDMA_BA+0x080)  /*!< GDMA Internal Buffer Word 0 */
    #define     REG_GDMA_INTBUF1    (GDMA_BA+0x084)  /*!< GDMA Internal Buffer Word 1 */
    #define     REG_GDMA_INTBUF2    (GDMA_BA+0x088)  /*!< GDMA Internal Buffer Word 2 */
    #define     REG_GDMA_INTBUF3    (GDMA_BA+0x08C)  /*!< GDMA Internal Buffer Word 3 */
    #define     REG_GDMA_INTBUF4    (GDMA_BA+0x090)  /*!< GDMA Internal Buffer Word 4 */
    #define     REG_GDMA_INTBUF5    (GDMA_BA+0x094)  /*!< GDMA Internal Buffer Word 5 */
    #define     REG_GDMA_INTBUF6    (GDMA_BA+0x098)  /*!< GDMA Internal Buffer Word 6 */
    #define     REG_GDMA_INTBUF7    (GDMA_BA+0x09C)  /*!< GDMA Internal Buffer Word 7 */
    #define     REG_GDMA_INTCS  (GDMA_BA+0x0A0)  /*!< Interrupt Control and Status Register */

    /**@}*/ /* end of GDMA register group */



    /*---------------------- USB Device Controller -------------------------*/
    /**
    @addtogroup USBD USB Device Controller(USBD)
    Memory Mapped Structure for USBD Controller
    @{ */
    #define     REG_USBD_GINTSTS        (USBD_BA+0x00)  /*!< Interrupt Status Low Register */
    #define     REG_USBD_GINTEN         (USBD_BA+0x08)  /*!< Interrupt Enable Low Register */
    #define     REG_USBD_BUSINTSTS      (USBD_BA+0x10)  /*!< USB Bus Interrupt Status Register */
    #define     REG_USBD_BUSINTEN       (USBD_BA+0x14)  /*!< USB Bus Interrupt Enable Register */
    #define     REG_USBD_OPER           (USBD_BA+0x18)  /*!< USB Operational Register */
    #define     REG_USBD_FRAMECNT       (USBD_BA+0x1C)  /*!< USB Frame Count Register */
    #define     REG_USBD_FADDR          (USBD_BA+0x20)  /*!< USB Function Address Register */
    #define     REG_USBD_TEST           (USBD_BA+0x24)  /*!< USB Test Mode Register */
    #define     REG_USBD_CEPDAT         (USBD_BA+0x28)  /*!< Control-ep data buffer register */
    #define     REG_USBD_CEPCTL         (USBD_BA+0x2C)  /*!< Control-ep control and status register */
    #define     REG_USBD_CEPINTEN       (USBD_BA+0x30)  /*!< Control-ep interrupt enable register */
    #define     REG_USBD_CEPINTSTS      (USBD_BA+0x34)  /*!< Control-ep interrupt status register */
    #define     REG_USBD_CEPTXCNT       (USBD_BA+0x38)  /*!< In-transfer data count register */
    #define     REG_USBD_CEPRXCNT       (USBD_BA+0x3C)  /*!< Out-transfer data count register */
    #define     REG_USBD_CEPDATCNT      (USBD_BA+0x40)  /*!< Control-ep data count register */
    #define     REG_USBD_SETUP1_0       (USBD_BA+0x44)  /*!< Setup byte1 & byte0 register */
    #define     REG_USBD_SETUP3_2       (USBD_BA+0x48)  /*!< Setup byte3 & byte2 register */
    #define     REG_USBD_SETUP5_4       (USBD_BA+0x4C)  /*!< Setup byte5 & byte4 register */
    #define     REG_USBD_SETUP7_6       (USBD_BA+0x50)  /*!< Setup byte7 & byte6 register */
    #define     REG_USBD_CEPBUFSTART    (USBD_BA+0x54)  /*!< Control-ep ram start address register */
    #define     REG_USBD_CEPBUFEND      (USBD_BA+0x58)  /*!< Control-ep ram end address register */
    #define     REG_USBD_DMACTL         (USBD_BA+0x5C)  /*!< Dma control and status register */
    #define     REG_USBD_DMACNT         (USBD_BA+0x60)  /*!< Dma count register */

    #define     REG_USBD_EPADAT         (USBD_BA+0x64)  /*!< Endpoint A data buffer register */
    #define     REG_USBD_EPAINTSTS      (USBD_BA+0x68)  /*!< Endpoint A interrupt status register */
    #define     REG_USBD_EPAINTEN       (USBD_BA+0x6C)  /*!< Endpoint A interrupt enable register */
    #define     REG_USBD_EPADATCNT      (USBD_BA+0x70)  /*!< Data count available in endpoint A buffer */
    #define     REG_USBD_EPARSPCTL      (USBD_BA+0x74)  /*!< Endpoint A response register set/clear */
    #define     REG_USBD_EPAMPS         (USBD_BA+0x78)  /*!< Endpoint A max packet size register */
    #define     REG_USBD_EPATXCNT       (USBD_BA+0x7C)  /*!< Endpoint A transfer count register */
    #define     REG_USBD_EPACFG         (USBD_BA+0x80)  /*!< Endpoint A configuration register */
    #define     REG_USBD_EPABUFSTART    (USBD_BA+0x84)  /*!< Endpoint A ram start address register */
    #define     REG_USBD_EPABUFEND      (USBD_BA+0x88)  /*!< Endpoint A ram end address register */

    #define     REG_USBD_EPBDAT         (USBD_BA+0x8C)  /*!< Endpoint B data buffer register */
    #define     REG_USBD_EPBINTSTS      (USBD_BA+0x90)  /*!< Endpoint B interrupt status register */
    #define     REG_USBD_EPBINTEN       (USBD_BA+0x94)  /*!< Endpoint B interrupt enable register */
    #define     REG_USBD_EPBDATCNT      (USBD_BA+0x98)  /*!< Data count available in endpoint B buffer */
    #define     REG_USBD_EPBRSPCTL      (USBD_BA+0x9C)  /*!< Endpoint B response register set/clear */
    #define     REG_USBD_EPBMPS         (USBD_BA+0xA0)  /*!< Endpoint B max packet size register */
    #define     REG_USBD_EPBTXCNT       (USBD_BA+0xA4)  /*!< Endpoint B transfer count register */
    #define     REG_USBD_EPBCFG         (USBD_BA+0xA8)  /*!< Endpoint B configuration register */
    #define     REG_USBD_EPBBUFSTART    (USBD_BA+0xAC)  /*!< Endpoint B ram start address register */
    #define     REG_USBD_EPBBUFEND      (USBD_BA+0xB0)  /*!< Endpoint B ram end address register */

    #define     REG_USBD_EPCDAT         (USBD_BA+0xB4)  /*!< Endpoint C data buffer register */
    #define     REG_USBD_EPCINTSTS      (USBD_BA+0xB8)  /*!< Endpoint C interrupt status register */
    #define     REG_USBD_EPCINTEN       (USBD_BA+0xBC)  /*!< Endpoint C interrupt enable register */
    #define     REG_USBD_EPCDATCNT      (USBD_BA+0xC0)  /*!< Data count available in endpoint C buffer */
    #define     REG_USBD_EPCRSPCTL      (USBD_BA+0xC4)  /*!< Endpoint C response register set/clear */
    #define     REG_USBD_EPCMPS         (USBD_BA+0xC8)  /*!< Endpoint C max packet size register */
    #define     REG_USBD_EPCTXCNT       (USBD_BA+0xCC)  /*!< Endpoint C transfer count register */
    #define     REG_USBD_EPCCFG         (USBD_BA+0xD0)  /*!< Endpoint C configuration register */
    #define     REG_USBD_EPCBUFSTART    (USBD_BA+0xD4)  /*!< Endpoint C ram start address register */
    #define     REG_USBD_EPCBUFEND      (USBD_BA+0xD8)  /*!< Endpoint C ram end address register */

    #define     REG_USBD_EPDDAT         (USBD_BA+0xDC)  /*!< Endpoint D data buffer register */
    #define     REG_USBD_EPDINTSTS      (USBD_BA+0xE0)  /*!< Endpoint D interrupt status register */
    #define     REG_USBD_EPDINTEN       (USBD_BA+0xE4)  /*!< Endpoint D interrupt enable register */
    #define     REG_USBD_EPDDATCNT      (USBD_BA+0xE8)  /*!< Data count available in endpoint D buffer */
    #define     REG_USBD_EPDRSPCTL      (USBD_BA+0xEC)  /*!< Endpoint D response register set/clear */
    #define     REG_USBD_EPDMPS         (USBD_BA+0xF0)  /*!< Endpoint D max packet size register */
    #define     REG_USBD_EPDTXCNT       (USBD_BA+0xF4)  /*!< Endpoint D transfer count register */
    #define     REG_USBD_EPDCFG         (USBD_BA+0xF8)  /*!< Endpoint D configuration register */
    #define     REG_USBD_EPDBUFSTART    (USBD_BA+0xFC)  /*!< Endpoint D ram start address register */
    #define     REG_USBD_EPDBUFEND      (USBD_BA+0x100) /*!< Endpoint D ram end address register */

    #define     REG_USBD_EPEDAT         (USBD_BA+0x104) /*!< Endpoint E data buffer register */
    #define     REG_USBD_EPEINTSTS      (USBD_BA+0x108) /*!< Endpoint E interrupt status register */
    #define     REG_USBD_EPEINTEN       (USBD_BA+0x10C) /*!< Endpoint E interrupt enable register */
    #define     REG_USBD_EPEDATCNT      (USBD_BA+0x110) /*!< Data count available in endpoint E buffer */
    #define     REG_USBD_EPERSPCTL      (USBD_BA+0x114) /*!< Endpoint E response register set/clear */
    #define     REG_USBD_EPEMPS         (USBD_BA+0x118) /*!< Endpoint E max packet size register */
    #define     REG_USBD_EPETXCNT       (USBD_BA+0x11C) /*!< Endpoint E transfer count register */
    #define     REG_USBD_EPECFG         (USBD_BA+0x120) /*!< Endpoint E configuration register */
    #define     REG_USBD_EPEBUFSTART    (USBD_BA+0x124) /*!< Endpoint E ram start address register */
    #define     REG_USBD_EPEBUFEND      (USBD_BA+0x128) /*!< Endpoint E ram end address register */

    #define     REG_USBD_EPFDAT         (USBD_BA+0x12C) /*!< Endpoint F data buffer register */
    #define     REG_USBD_EPFINTSTS      (USBD_BA+0x130) /*!< Endpoint F interrupt status register */
    #define     REG_USBD_EPFINTEN       (USBD_BA+0x134) /*!< Endpoint F interrupt enable register */
    #define     REG_USBD_EPFDATCNT      (USBD_BA+0x138) /*!< Data count available in endpoint F buffer */
    #define     REG_USBD_EPFRSPCTL      (USBD_BA+0x13C) /*!< Endpoint F response register set/clear */
    #define     REG_USBD_EPFMPS         (USBD_BA+0x140) /*!< Endpoint F max packet size register */
    #define     REG_USBD_EPFTXCNT       (USBD_BA+0x144) /*!< Endpoint F transfer count register */
    #define     REG_USBD_EPFCFG         (USBD_BA+0x148) /*!< Endpoint F configuration register */
    #define     REG_USBD_EPFBUFSTART    (USBD_BA+0x14C) /*!< Endpoint F ram start address register */
    #define     REG_USBD_EPFBUFEND      (USBD_BA+0x150) /*!< Endpoint F ram end address register */

    #define     REG_USBD_EPGDAT         (USBD_BA+0x154) /*!< Endpoint G data buffer register */
    #define     REG_USBD_EPGINTSTS      (USBD_BA+0x158) /*!< Endpoint G interrupt status register */
    #define     REG_USBD_EPGINTEN       (USBD_BA+0x15C) /*!< Endpoint G interrupt enable register */
    #define     REG_USBD_EPGDATCNT      (USBD_BA+0x160) /*!< Data count available in endpoint G buffer */
    #define     REG_USBD_EPGRSPCTL      (USBD_BA+0x164) /*!< Endpoint G response register set/clear */
    #define     REG_USBD_EPGMPS         (USBD_BA+0x168) /*!< Endpoint G max packet size register */
    #define     REG_USBD_EPGTXCNT       (USBD_BA+0x16C) /*!< Endpoint G transfer count register */
    #define     REG_USBD_EPGCFG         (USBD_BA+0x170) /*!< Endpoint G configuration register */
    #define     REG_USBD_EPGBUFSTART    (USBD_BA+0x174) /*!< Endpoint G ram start address register */
    #define     REG_USBD_EPGBUFEND      (USBD_BA+0x178) /*!< Endpoint G ram end address register */

    #define     REG_USBD_EPHDAT         (USBD_BA+0x17C) /*!< Endpoint H data buffer register */
    #define     REG_USBD_EPHINTSTS      (USBD_BA+0x180) /*!< Endpoint H interrupt status register */
    #define     REG_USBD_EPHINTEN       (USBD_BA+0x184) /*!< Endpoint H interrupt enable register */
    #define     REG_USBD_EPHDATCNT      (USBD_BA+0x188) /*!< Data count available in endpoint H buffer */
    #define     REG_USBD_EPHRSPCTL      (USBD_BA+0x18C) /*!< Endpoint H response register set/clear */
    #define     REG_USBD_EPHMPS         (USBD_BA+0x190) /*!< Endpoint H max packet size register */
    #define     REG_USBD_EPHTXCNT       (USBD_BA+0x194) /*!< Endpoint H transfer count register */
    #define     REG_USBD_EPHCFG         (USBD_BA+0x198) /*!< Endpoint H configuration register */
    #define     REG_USBD_EPHBUFSTART    (USBD_BA+0x19C) /*!< Endpoint H ram start address register */
    #define     REG_USBD_EPHBUFEND      (USBD_BA+0x1A0) /*!< Endpoint H ram end address register */

    #define     REG_USBD_EPIDAT         (USBD_BA+0x1A4) /*!< Endpoint I data buffer register */
    #define     REG_USBD_EPIINTSTS      (USBD_BA+0x1A8) /*!< Endpoint I interrupt status register */
    #define     REG_USBD_EPIINTEN       (USBD_BA+0x1AC) /*!< Endpoint I interrupt enable register */
    #define     REG_USBD_EPIDATCNT      (USBD_BA+0x1B0) /*!< Data count available in endpoint I buffer */
    #define     REG_USBD_EPIRSPCTL      (USBD_BA+0x1B4) /*!< Endpoint I response register set/clear */
    #define     REG_USBD_EPIMPS         (USBD_BA+0x1B8) /*!< Endpoint I max packet size register */
    #define     REG_USBD_EPITXCNT       (USBD_BA+0x1BC) /*!< Endpoint I transfer count register */
    #define     REG_USBD_EPICFG         (USBD_BA+0x1C0) /*!< Endpoint I configuration register */
    #define     REG_USBD_EPIBUFSTART    (USBD_BA+0x1C4) /*!< Endpoint I ram start address register */
    #define     REG_USBD_EPIBUFEND      (USBD_BA+0x1C8) /*!< Endpoint I ram end address register */

    #define     REG_USBD_EPJDAT         (USBD_BA+0x1CC) /*!< Endpoint J data buffer register */
    #define     REG_USBD_EPJINTSTS      (USBD_BA+0x1D0) /*!< Endpoint J interrupt status register */
    #define     REG_USBD_EPJINTEN       (USBD_BA+0x1D4) /*!< Endpoint J interrupt enable register */
    #define     REG_USBD_EPJDATCNT      (USBD_BA+0x1D8) /*!< Data count available in endpoint J buffer */
    #define     REG_USBD_EPJRSPCTL      (USBD_BA+0x1DC) /*!< Endpoint J response register set/clear */
    #define     REG_USBD_EPJMPS         (USBD_BA+0x1E0) /*!< Endpoint J max packet size register */
    #define     REG_USBD_EPJTXCNT       (USBD_BA+0x1E4) /*!< Endpoint J transfer count register */
    #define     REG_USBD_EPJCFG         (USBD_BA+0x1E8) /*!< Endpoint J configuration register */
    #define     REG_USBD_EPJBUFSTART    (USBD_BA+0x1EC) /*!< Endpoint J ram start address register */
    #define     REG_USBD_EPJBUFEND      (USBD_BA+0x1F0) /*!< Endpoint J ram end address register */

    #define     REG_USBD_EPKDAT         (USBD_BA+0x1F4) /*!< Endpoint K data buffer register */
    #define     REG_USBD_EPKINTSTS      (USBD_BA+0x1F8) /*!< Endpoint K interrupt status register */
    #define     REG_USBD_EPKINTEN       (USBD_BA+0x1FC) /*!< Endpoint K interrupt enable register */
    #define     REG_USBD_EPKDATCNT      (USBD_BA+0x200) /*!< Data count available in endpoint K buffer */
    #define     REG_USBD_EPKRSPCTL      (USBD_BA+0x204) /*!< Endpoint K response register set/clear */
    #define     REG_USBD_EPKMPS         (USBD_BA+0x208) /*!< Endpoint K max packet size register */
    #define     REG_USBD_EPKTXCNT       (USBD_BA+0x20C) /*!< Endpoint K transfer count register */
    #define     REG_USBD_EPKCFG         (USBD_BA+0x210) /*!< Endpoint K configuration register */
    #define     REG_USBD_EPKBUFSTART    (USBD_BA+0x214) /*!< Endpoint K ram start address register */
    #define     REG_USBD_EPKBUFEND      (USBD_BA+0x218) /*!< Endpoint K ram end address register */

    #define     REG_USBD_EPLDAT         (USBD_BA+0x21C) /*!< Endpoint L data buffer register */
    #define     REG_USBD_EPLINTSTS      (USBD_BA+0x220) /*!< Endpoint L interrupt status register */
    #define     REG_USBD_EPLINTEN       (USBD_BA+0x224) /*!< Endpoint L interrupt enable register */
    #define     REG_USBD_EPLDATCNT      (USBD_BA+0x228) /*!< Data count available in endpoint L buffer */
    #define     REG_USBD_EPLRSPCTL      (USBD_BA+0x22C) /*!< Endpoint L response register set/clear */
    #define     REG_USBD_EPLMPS         (USBD_BA+0x230) /*!< Endpoint L max packet size register */
    #define     REG_USBD_EPLTXCNT       (USBD_BA+0x234) /*!< Endpoint L transfer count register */
    #define     REG_USBD_EPLCFG         (USBD_BA+0x238) /*!< Endpoint L configuration register */
    #define     REG_USBD_EPLBUFSTART    (USBD_BA+0x23C) /*!< Endpoint L ram start address register */
    #define     REG_USBD_EPLBUFEND      (USBD_BA+0x240) /*!< Endpoint L ram end address register */
    #define     REG_USBD_DMAADDR        (USBD_BA+0x700) /*!< AHB_DMA address register */
    #define     REG_USBD_PHYCTL         (USBD_BA+0x704) /*!< USB PHY control register */

    /**@}*/ /* end of USBD register group */


    /*----------------------  LCD Display Interface Controller -------------------------*/
    /**
    @addtogroup LCM  LCD Display Interface Controller(LCM)
    Memory Mapped Structure for LCM Controller
    @{ */

    #define     REG_LCM_DCCS        (LCM_BA+0x00)  /*!< Display Controller Control/Status Register */
    #define     REG_LCM_DEV_CTRL    (LCM_BA+0x04)  /*!< Display Output Device Control Register */
    #define     REG_LCM_MPU_CMD     (LCM_BA+0x08)  /*!< MPU-Interface LCD Write Command */
    #define     REG_LCM_INT_CS      (LCM_BA+0x0c)  /*!< Interrupt Control/Status Register */
    #define     REG_LCM_CRTC_SIZE   (LCM_BA+0x10)  /*!< CRTC Display Size Control Register */
    #define     REG_LCM_CRTC_DEND   (LCM_BA+0x14)  /*!< CRTC Display Enable End */
    #define     REG_LCM_CRTC_HR     (LCM_BA+0x18)  /*!< CRTC Internal Horizontal Retrace Control Register */
    #define     REG_LCM_CRTC_HSYNC  (LCM_BA+0x1C)  /*!< CRTC Horizontal Sync Control Register */
    #define     REG_LCM_CRTC_VR     (LCM_BA+0x20)  /*!< CRTC Internal Vertical Retrace Control Register */
    #define     REG_LCM_VA_BADDR0   (LCM_BA+0x24)  /*!< Video Stream Frame Buffer-0 Starting Address */
    #define     REG_LCM_VA_BADDR1   (LCM_BA+0x28)  /*!< Video Stream Frame Buffer-1 Starting Address */
    #define     REG_LCM_VA_FBCTRL   (LCM_BA+0x2C)  /*!< Video Stream Frame Buffer Control Register */
    #define     REG_LCM_VA_SCALE    (LCM_BA+0x30)  /*!< Video Stream Scaling Control Register */
    #define     REG_LCM_VA_WIN      (LCM_BA+0x38)  /*!< Image Stream Active Window Coordinates */
    #define     REG_LCM_VA_STUFF    (LCM_BA+0x3C)  /*!< Image Stream Stuff Pixel */
    #define     REG_LCM_OSD_WINS    (LCM_BA+0x40)  /*!< OSD Window Starting Coordinates */
    #define     REG_LCM_OSD_WINE    (LCM_BA+0x44)  /*!< OSD Window Ending Coordinates */
    #define     REG_LCM_OSD_BADDR   (LCM_BA+0x48)  /*!< OSD Stream Frame Buffer Starting Address */
    #define     REG_LCM_OSD_FBCTRL  (LCM_BA+0x4c)  /*!< OSD Stream Frame Buffer Control Register */
    #define     REG_LCM_OSD_OVERLAY (LCM_BA+0x50)  /*!< OSD Overlay Control Register */
    #define     REG_LCM_OSD_CKEY    (LCM_BA+0x54)  /*!< OSD Overlay Color-Key Pattern Register */
    #define     REG_LCM_OSD_CMASK   (LCM_BA+0x58)  /*!< OSD Overlay Color-Key Mask Register */
    #define     REG_LCM_OSD_SKIP1   (LCM_BA+0x5C)  /*!< OSD Window Skip1 Register */
    #define     REG_LCM_OSD_SKIP2   (LCM_BA+0x60)  /*!< OSD Window Skip2 Register */
    #define     REG_LCM_OSD_SCALE   (LCM_BA+0x64)  /*!< OSD horizontal up scaling control register */
    #define     REG_LCM_MPU_VSYNC   (LCM_BA+0x68)  /*!< MPU Vsync control register */
    #define     REG_LCM_HC_CTRL     (LCM_BA+0x6C)  /*!< Hardware cursor control Register */
    #define     REG_LCM_HC_POS      (LCM_BA+0x70)  /*!< Hardware cursot tip point potison on va picture */
    #define     REG_LCM_HC_WBCTRL   (LCM_BA+0x74)  /*!< Hardware Cursor Window Buffer Control Register */
    #define     REG_LCM_HC_BADDR    (LCM_BA+0x78)  /*!< Hardware cursor memory base address register */
    #define     REG_LCM_HC_COLOR0   (LCM_BA+0x7C)  /*!< Hardware cursor color ram register mapped to bpp = 0 */
    #define     REG_LCM_HC_COLOR1   (LCM_BA+0x80)  /*!< Hardware cursor color ram register mapped to bpp = 1 */
    #define     REG_LCM_HC_COLOR2   (LCM_BA+0x84)  /*!< Hardware cursor color ram register mapped to bpp = 2 */
    #define     REG_LCM_HC_COLOR3   (LCM_BA+0x88)  /*!< Hardware cursor color ram register mapped to bpp = 3 */

    /**@}*/ /* end of LCM register group */


    /*---------------------- I2S Interface Controller -------------------------*/
    /**
    @addtogroup I2S I2S Interface Controller(I2S)
    Memory Mapped Structure for I2S Controller
    @{ */

    #define     REG_ACTL_CON            (ACTL_BA+0x00)      /*!< Audio controller control register */
    #define     REG_ACTL_RESET          (ACTL_BA+0x04)      /*!< Sub block reset control register */
    #define     REG_ACTL_RDESB          (ACTL_BA+0x08)      /*!< DMA destination base address register for record */
    #define     REG_ACTL_RDES_LENGTH    (ACTL_BA+0x0C)      /*!< DMA destination length register for record */
    #define     REG_ACTL_RDESC          (ACTL_BA+0x10)      /*!< DMA destination current address for record */
    #define     REG_ACTL_PDESB          (ACTL_BA+0x14)      /*!< DMA destination current address for play */
    #define     REG_ACTL_PDES_LENGTH    (ACTL_BA+0x18)      /*!< DMA destination length register for play */
    #define     REG_ACTL_PDESC          (ACTL_BA+0x1C)      /*!< DMA destination current address register for play */
    #define     REG_ACTL_RSR            (ACTL_BA+0x20)      /*!< Record status register */
    #define     REG_ACTL_PSR            (ACTL_BA+0x24)      /*!< Play status register */
    #define     REG_ACTL_I2SCON         (ACTL_BA+0x28)      /*!< I2S control register */
    #define     REG_ACTL_COUNTER        (ACTL_BA+0x2C)      /*!< DMA count down values */
    #define     REG_ACTL_PCMCON         (ACTL_BA+0x30)      /*!< PCM interface control register */
    #define     REG_ACTL_PCMS1ST        (ACTL_BA+0x34)      /*!< PCM interface slot1 start register */
    #define     REG_ACTL_PCMS2ST        (ACTL_BA+0x38)      /*!< PCM interface slot2 start register */
    #define     REG_ACTL_RDESB2         (ACTL_BA+0x40)      /*!< DMA destination base address register for record right channel */
    #define     REG_ACTL_PDESB2         (ACTL_BA+0x44)      /*!< DMA destination base address register for play right channel */

    /**@}*/ /* end of I2S register group */

    /*---------------------- 2D Graphic Engine -------------------------*/
    /**
    @addtogroup GE2D 2D Graphic Engine(GE2D)
    Memory Mapped Structure for GE2D Controller
    @{ */

    #define     REG_GE2D_TRG            (GE_BA+0x00)  /*!< Graphic Engine Trigger Control Register */
    #define     REG_GE2D_XYSORG         (GE_BA+0x04)  /*!< Graphic Engine XY Mode Source Origin Starting Register */
    #define     REG_GE2D_TCNTVHSF       (GE_BA+0x08)  /*!< Graphic Engine Tile Width/Height or V/H Scale Factor N/M */
    #define     REG_GE2D_XYRRP          (GE_BA+0x0C)  /*!< Graphic Engine Rotate Reference Point XY Address */
    #define     REG_GE2D_INTSTS         (GE_BA+0x10)  /*!< Graphic Engine Interrupt Status Register */
    #define     REG_GE2D_PATSA          (GE_BA+0x14)  /*!< Graphic Engine Pattern Location Starting Address Register */
    #define     REG_GE2D_BETSC          (GE_BA+0x18)  /*!< GE Bresenham Error Term Stepping Constant Register */
    #define     REG_GE2D_BIEPC          (GE_BA+0x1C)  /*!< GE Bresenham Initial Error, Pixel Count Major M Register */
    #define     REG_GE2D_CTL            (GE_BA+0x20)  /*!< Graphic Engine Control Register */
    #define     REG_GE2D_BGCOLR         (GE_BA+0x24)  /*!< Graphic Engine Background Color Register */
    #define     REG_GE2D_FGCOLR         (GE_BA+0x28)  /*!< Graphic Engine Foreground Color Register */
    #define     REG_GE2D_TRNSCOLR       (GE_BA+0x2C)  /*!< Graphic Engine Transparency Color Register */
    #define     REG_GE2D_TCMSK          (GE_BA+0x30)  /*!< Graphic Engine Transparency Color Mask Register */
    #define     REG_GE2D_XYDORG         (GE_BA+0x34)  /*!< Graphic Engine XY Mode Display Origin Starting Register */
    #define     REG_GE2D_SDPITCH        (GE_BA+0x38)  /*!< Graphic Engine Source/Destination Pitch Register */
    #define     REG_GE2D_SRCSPA         (GE_BA+0x3C)  /*!< Graphic Engine Source Start XY/Linear Address Register */
    #define     REG_GE2D_DSTSPA         (GE_BA+0x40)  /*!< Graphic Engine Destination Start XY/Linear Register */
    #define     REG_GE2D_RTGLSZ         (GE_BA+0x44)  /*!< Graphic Engine Dimension XY/Linear Register */
    #define     REG_GE2D_CLPBTL         (GE_BA+0x48)  /*!< Graphic Engine Clipping Boundary Top/Left Register */
    #define     REG_GE2D_CLPBBR         (GE_BA+0x4C)  /*!< Graphic Engine Clipping Boundary Bottom/Right Register */
    #define     REG_GE2D_PTNA           (GE_BA+0x50)  /*!< Graphic Engine Pattern A Register */
    #define     REG_GE2D_PTNB           (GE_BA+0x54)  /*!< Graphic Engine Pattern B Register */
    #define     REG_GE2D_WRPLNMSK       (GE_BA+0x58)  /*!< Graphic Engine Write Plane Mask Register */
    #define     REG_GE2D_MISCTL         (GE_BA+0x5C)  /*!< Graphic Engine Miscellaneous Control Register */
    #define     REG_GE2D_GEHBDW0        (GE_BA+0x60)  /*!< Graphic Engine HostBLT data Port 0 Register */
    #define     REG_GE2D_GEHBDW1        (GE_BA+0x64)  /*!< Graphic Engine HostBLT data Port 1 Register */
    #define     REG_GE2D_GEHBDW2        (GE_BA+0x68)  /*!< Graphic Engine HostBLT data Port 2 Register */
    #define     REG_GE2D_GEHBDW3        (GE_BA+0x6C)  /*!< Graphic Engine HostBLT data Port 3 Register */
    #define     REG_GE2D_GEHBDW4        (GE_BA+0x70)  /*!< Graphic Engine HostBLT data Port 4 Register */
    #define     REG_GE2D_GEHBDW5        (GE_BA+0x74)  /*!< Graphic Engine HostBLT data Port 5 Register */
    #define     REG_GE2D_GEHBDW6        (GE_BA+0x78)  /*!< Graphic Engine HostBLT data Port 6 Register */
    #define     REG_GE2D_GEHBDW7        (GE_BA+0x7C)  /*!< Graphic Engine HostBLT data Port 7 Register */

    /**@}*/ /* end of GE2D register group */

    /*---------------------- Flash Memory Interface -------------------------*/
    /**
    @addtogroup FMI Flash Memory Interface(FMI)
    Memory Mapped Structure for FMI Controller
    @{ */

    /* DMAC Control Registers*/
    #define     REG_FMI_BUFFER      (FMI_BA+0x000)   /*!< FMI Embedded Buffer Word */
    #define     REG_FMI_DMACTL      (FMI_BA+0x400)   /*!< FMI DMA Control Register */
    #define     REG_FMI_DMASA       (FMI_BA+0x408)   /*!< FMI DMA Transfer Starting Address Register */
    #define     REG_FMI_DMABCNT     (FMI_BA+0x40C)   /*!< FMI DMA Transfer Byte Count Register */
    #define     REG_FMI_DMAINTEN    (FMI_BA+0x410)   /*!< FMI DMA Interrupt Enable Register */
    #define     REG_FMI_DMAINTSTS   (FMI_BA+0x414)   /*!< FMI DMA Interrupt Status Register */

    #define     REG_FMI_CTL         (FMI_BA+0x800)   /*!< Global Control and Status Register */
    #define     REG_FMI_INTEN       (FMI_BA+0x804)   /*!< Global Interrupt Control Register */
    #define     REG_FMI_INTSTS      (FMI_BA+0x808)   /*!< Global Interrupt Status Register */

    /* eMMC Registers */
    #define     REG_FMI_EMMCCTL     (FMI_BA+0x820)   /*!< eMMC control and status register */
    #define     REG_FMI_EMMCCMD     (FMI_BA+0x824)   /*!< eMMC command argument register */
    #define     REG_FMI_EMMCINTEN   (FMI_BA+0x828)   /*!< eMMC interrupt enable register */
    #define     REG_FMI_EMMCINTSTS  (FMI_BA+0x82C)   /*!< eMMC interrupt status register */
    #define     REG_FMI_EMMCRESP0   (FMI_BA+0x830)   /*!< eMMC receive response token register 0 */
    #define     REG_FMI_EMMCRESP1   (FMI_BA+0x834)   /*!< eMMC receive response token register 1 */
    #define     REG_FMI_EMMCBLEN    (FMI_BA+0x838)   /*!< eMMC block length register */
    #define     REG_FMI_EMMCTOUT    (FMI_BA+0x83C)   /*!< eMMC block length register */

    /* NAND-type Flash Registers */
    #define     REG_NANDCTL         (FMI_BA+0x8A0)   /*!< NAND Flash Control and Status Register */
    #define     REG_NANDTMCTL       (FMI_BA+0x8A4)   /*!< NAND Flash Timing Control Register */
    #define     REG_NANDINTEN       (FMI_BA+0x8A8)   /*!< NAND Flash Interrupt Control Register */
    #define     REG_NANDINTSTS      (FMI_BA+0x8AC)   /*!< NAND Flash Interrupt Status Register */
    #define     REG_NANDCMD         (FMI_BA+0x8B0)   /*!< NAND Flash Command Port Register */
    #define     REG_NANDADDR        (FMI_BA+0x8B4)   /*!< NAND Flash Address Port Register */
    #define     REG_NANDDATA        (FMI_BA+0x8B8)   /*!< NAND Flash Data Port Register */
    #define     REG_NANDRACTL       (FMI_BA+0x8BC)   /*!< NAND Flash Redundant Area Control Register */
    #define     REG_NANDECTL        (FMI_BA+0x8C0)   /*!< NAND Flash Extend Control Regsiter */
    #define     REG_NANDECCES0      (FMI_BA+0x8D0)   /*!< NAND Flash ECC Error Status 0 */
    #define     REG_NANDECCES1      (FMI_BA+0x8D4)   /*!< NAND Flash ECC Error Status 1 */
    #define     REG_NANDECCES2      (FMI_BA+0x8D8)   /*!< NAND Flash ECC Error Status 2 */
    #define     REG_NANDECCES3      (FMI_BA+0x8DC)   /*!< NAND Flash ECC Error Status 3 */
    #define     REG_NANDPROTA0      (FMI_BA+0x8E0)   /*!< NAND Flash Protect Region End Address 0 */
    #define     REG_NANDPROTA1      (FMI_BA+0x8E4)   /*!< NAND Flash Protect Region End Address 1 */

    /* NAND-type Flash BCH Error Address Registers */
    #define     REG_NANDECCEA0      (FMI_BA+0x900)   /*!< NAND Flash ECC Error Byte Address 0 */
    #define     REG_NANDECCEA1      (FMI_BA+0x904)   /*!< NAND Flash ECC Error Byte Address 1 */
    #define     REG_NANDECCEA2      (FMI_BA+0x908)   /*!< NAND Flash ECC Error Byte Address 2 */
    #define     REG_NANDECCEA3      (FMI_BA+0x90C)   /*!< NAND Flash ECC Error Byte Address 3 */
    #define     REG_NANDECCEA4      (FMI_BA+0x910)   /*!< NAND Flash ECC Error Byte Address 4 */
    #define     REG_NANDECCEA5      (FMI_BA+0x914)   /*!< NAND Flash ECC Error Byte Address 5 */
    #define     REG_NANDECCEA6      (FMI_BA+0x918)   /*!< NAND Flash ECC Error Byte Address 6 */
    #define     REG_NANDECCEA7      (FMI_BA+0x91C)   /*!< NAND Flash ECC Error Byte Address 7 */
    #define     REG_NANDECCEA8      (FMI_BA+0x920)   /*!< NAND Flash ECC Error Byte Address 8 */
    #define     REG_NANDECCEA9      (FMI_BA+0x924)   /*!< NAND Flash ECC Error Byte Address 9 */
    #define     REG_NANDECCEA10     (FMI_BA+0x928)   /*!< NAND Flash ECC Error Byte Address 10 */
    #define     REG_NANDECCEA11     (FMI_BA+0x92C)   /*!< NAND Flash ECC Error Byte Address 11 */

    /* NAND-type Flash BCH Error Data Registers */
    #define     REG_NANDECCED0      (FMI_BA+0x960)   /*!< NAND Flash ECC Error Data Register 0 */
    #define     REG_NANDECCED1      (FMI_BA+0x964)   /*!< NAND Flash ECC Error Data Register 1 */
    #define     REG_NANDECCED2      (FMI_BA+0x968)   /*!< NAND Flash ECC Error Data Register 2 */
    #define     REG_NANDECCED3      (FMI_BA+0x96C)   /*!< NAND Flash ECC Error Data Register 3 */
    #define     REG_NANDECCED4      (FMI_BA+0x970)   /*!< NAND Flash ECC Error Data Register 4 */
    #define     REG_NANDECCED5      (FMI_BA+0x974)   /*!< NAND Flash ECC Error Data Register 5 */

    /* NAND-type Flash Redundant Area Registers */
    #define     REG_NANDRA0         (FMI_BA+0xA00)   /*!< NAND Flash Redundant Area Register */
    #define     REG_NANDRA1         (FMI_BA+0xA04)   /*!< NAND Flash Redundant Area Register */

    /**@}*/ /* end of FMI register group */


    /*---------------------- SD/SDIO Host Controller -------------------------*/
    /**
    @addtogroup SDH SD/SDIO Host Controller(SDH)
    Memory Mapped Structure for SDH Controller
    @{ */

    /* DMAC Control Registers*/
    #define     REG_SDH_FB0         (SDH_BA+0x000)   /*!< SD Host Embedded Buffer Word */
    #define     REG_SDH_DMACTL      (SDH_BA+0x400)   /*!< SD Host DMA Control and Status Register */
    #define     REG_SDH_DMASA       (SDH_BA+0x408)   /*!< SD Host DMA Transfer Starting Address Register */
    #define     REG_SDH_DMABCNT     (SDH_BA+0x40C)   /*!< SD Host DMA Transfer Byte Count Register */
    #define     REG_SDH_DMAINTEN    (SDH_BA+0x410)   /*!< SD Host DMA Interrupt Enable Register */
    #define     REG_SDH_DMAINTSTS   (SDH_BA+0x414)   /*!< SD Host DMA Interrupt Status Register */

    #define     REG_SDH_GCTL        (SDH_BA+0x800)   /*!< SD Host Global Control and Status Register */
    #define     REG_SDH_GINTEN      (SDH_BA+0x804)   /*!< SD Host Global Interrupt Control Register */
    #define     REG_SDH_GINTSTS     (SDH_BA+0x808)   /*!< SD Host Global Interrupt Status Register */

    /* Secure Digit Registers */
    #define     REG_SDH_CTL         (SDH_BA+0x820)   /*!< SD Host control and status register */
    #define     REG_SDH_CMD         (SDH_BA+0x824)   /*!< SD Host command argument register */
    #define     REG_SDH_INTEN       (SDH_BA+0x828)   /*!< SD Host interrupt enable register */
    #define     REG_SDH_INTSTS      (SDH_BA+0x82C)   /*!< SD Host interrupt status register */
    #define     REG_SDH_RESP0       (SDH_BA+0x830)   /*!< SD Host receive response token register 0 */
    #define     REG_SDH_RESP1       (SDH_BA+0x834)   /*!< SD Host receive response token register 1 */
    #define     REG_SDH_BLEN        (SDH_BA+0x838)   /*!< SD Host block length register */
    #define     REG_SDH_TMOUT       (SDH_BA+0x83C)   /*!< SD Host Response/Data-in Time-out register */
    #define     REG_SDH_ECTL        (SDH_BA+0x840)   /*!< SD Host Extend Control Register */

    /**@}*/ /* end of SDH register group */


    /*---------------------- Cryptographic Accelerator -------------------------*/
    /**
    @addtogroup CRYPTO Cryptographic Accelerator(CRYPTO)
    Memory Mapped Structure for Cryptographic Accelerator registers
    @{ */

    /* Crypto Control Registers */
    #define     CRPT_INTEN          (CRPT_BA+0x000)  /*!< Crypto Interrupt Enable Control Register      */
    #define     CRPT_INTSTS         (CRPT_BA+0x004)  /*!< Crypto Interrupt Flag                         */

    /* PRNG Registers */
    #define     CRPT_PRNG_CTL       (CRPT_BA+0x008)  /*!< PRNG Control Register                         */
    #define     CRPT_PRNG_SEED      (CRPT_BA+0x00C)  /*!< Seed for PRNG                                 */
    #define     CRPT_PRNG_KEY0      (CRPT_BA+0x010)  /*!< PRNG Generated Key 0                          */
    #define     CRPT_PRNG_KEY1      (CRPT_BA+0x014)  /*!< PRNG Generated Key 1                          */
    #define     CRPT_PRNG_KEY2      (CRPT_BA+0x018)  /*!< PRNG Generated Key 2                          */
    #define     CRPT_PRNG_KEY3      (CRPT_BA+0x01C)  /*!< PRNG Generated Key 3                          */
    #define     CRPT_PRNG_KEY4      (CRPT_BA+0x020)  /*!< PRNG Generated Key 4                          */
    #define     CRPT_PRNG_KEY5      (CRPT_BA+0x024)  /*!< PRNG Generated Key 5                          */
    #define     CRPT_PRNG_KEY6      (CRPT_BA+0x028)  /*!< PRNG Generated Key 6                          */
    #define     CRPT_PRNG_KEY7      (CRPT_BA+0x02C)  /*!< PRNG Generated Key 7                          */

    /* AES/TDES feedback Registers */
    #define     CRPT_AES_FDBCK0     (CRPT_BA+0x050)  /*!< AES Engine Output Feedback Data after Cryptographic Operation   */
    #define     CRPT_AES_FDBCK1     (CRPT_BA+0x054)  /*!< AES Engine Output Feedback Data after Cryptographic Operation   */
    #define     CRPT_AES_FDBCK2     (CRPT_BA+0x058)  /*!< AES Engine Output Feedback Data after Cryptographic Operation   */
    #define     CRPT_AES_FDBCK3     (CRPT_BA+0x05C)  /*!< AES Engine Output Feedback Data after Cryptographic Operation   */
    #define     CRPT_TDES_FDBCKH    (CRPT_BA+0x060)  /*!< TDES/DES Engine Output Feedback High Word Data after Cryptographic Operation  */
    #define     CRPT_TDES_FDBCKL    (CRPT_BA+0x064)  /*!< TDES/DES Engine Output Feedback Low Word Data after Cryptographic Operation   */

    /* AES Control Registers */
    #define     CRPT_AES_CTL        (CRPT_BA+0x100)   /*!< AES Control Register                               */
    #define     CRPT_AES_STS        (CRPT_BA+0x104)   /*!< AES Engine Flag                                    */
    #define     CRPT_AES_DATIN      (CRPT_BA+0x108)   /*!< AES Engine Data Input Port Register                */
    #define     CRPT_AES_DATOUT     (CRPT_BA+0x10C)   /*!< AES Engine Data Output Port Register               */
    #define     CRPT_AES0_KEY0      (CRPT_BA+0x110)   /*!< AES Key Word 0 Register for Channel 0              */
    #define     CRPT_AES0_KEY1      (CRPT_BA+0x114)   /*!< AES Key Word 1 Register for Channel 0              */
    #define     CRPT_AES0_KEY2      (CRPT_BA+0x118)   /*!< AES Key Word 2 Register for Channel 0              */
    #define     CRPT_AES0_KEY3      (CRPT_BA+0x11C)   /*!< AES Key Word 3 Register for Channel 0              */
    #define     CRPT_AES0_KEY4      (CRPT_BA+0x120)   /*!< AES Key Word 4 Register for Channel 0              */
    #define     CRPT_AES0_KEY5      (CRPT_BA+0x124)   /*!< AES Key Word 5 Register for Channel 0              */
    #define     CRPT_AES0_KEY6      (CRPT_BA+0x128)   /*!< AES Key Word 6 Register for Channel 0              */
    #define     CRPT_AES0_KEY7      (CRPT_BA+0x12C)   /*!< AES Key Word 7 Register for Channel 0              */
    #define     CRPT_AES0_IV0       (CRPT_BA+0x130)   /*!< AES Initial Vector Word 0 Register for Channel 0   */
    #define     CRPT_AES0_IV1       (CRPT_BA+0x134)   /*!< AES Initial Vector Word 1 Register for Channel 0   */
    #define     CRPT_AES0_IV2       (CRPT_BA+0x138)   /*!< AES Initial Vector Word 2 Register for Channel 0   */
    #define     CRPT_AES0_IV3       (CRPT_BA+0x13C)   /*!< AES Initial Vector Word 3 Register for Channel 0   */
    #define     CRPT_AES0_SADDR     (CRPT_BA+0x140)   /*!< AES DMA Source Address Register for Channel 0      */
    #define     CRPT_AES0_DADDR     (CRPT_BA+0x144)   /*!< AES DMA Destination Address Register for Channel 0 */
    #define     CRPT_AES0_CNT       (CRPT_BA+0x148)   /*!< AES Byte Count Register for Channel 0              */
    #define     CRPT_AES1_KEY0      (CRPT_BA+0x14C)   /*!< AES Key Word 0 Register for Channel 1              */
    #define     CRPT_AES1_KEY1      (CRPT_BA+0x150)   /*!< AES Key Word 1 Register for Channel 1              */
    #define     CRPT_AES1_KEY2      (CRPT_BA+0x154)   /*!< AES Key Word 2 Register for Channel 1              */
    #define     CRPT_AES1_KEY3      (CRPT_BA+0x158)   /*!< AES Key Word 3 Register for Channel 1              */
    #define     CRPT_AES1_KEY4      (CRPT_BA+0x15C)   /*!< AES Key Word 4 Register for Channel 1              */
    #define     CRPT_AES1_KEY5      (CRPT_BA+0x160)   /*!< AES Key Word 5 Register for Channel 1              */
    #define     CRPT_AES1_KEY6      (CRPT_BA+0x164)   /*!< AES Key Word 6 Register for Channel 1              */
    #define     CRPT_AES1_KEY7      (CRPT_BA+0x168)   /*!< AES Key Word 7 Register for Channel 1              */
    #define     CRPT_AES1_IV0       (CRPT_BA+0x16C)   /*!< AES Initial Vector Word 0 Register for Channel 1   */
    #define     CRPT_AES1_IV1       (CRPT_BA+0x170)   /*!< AES Initial Vector Word 1 Register for Channel 1   */
    #define     CRPT_AES1_IV2       (CRPT_BA+0x174)   /*!< AES Initial Vector Word 2 Register for Channel 1   */
    #define     CRPT_AES1_IV3       (CRPT_BA+0x178)   /*!< AES Initial Vector Word 3 Register for Channel 1   */
    #define     CRPT_AES1_SADDR     (CRPT_BA+0x17C)   /*!< AES DMA Source Address Register for Channel 1      */
    #define     CRPT_AES1_DADDR     (CRPT_BA+0x180)   /*!< AES DMA Destination Address Register for Channel 1 */
    #define     CRPT_AES1_CNT       (CRPT_BA+0x184)   /*!< AES Byte Count Register for Channel 1              */
    #define     CRPT_AES2_KEY0      (CRPT_BA+0x188)   /*!< AES Key Word 0 Register for Channel 2              */
    #define     CRPT_AES2_KEY1      (CRPT_BA+0x18C)   /*!< AES Key Word 1 Register for Channel 2              */
    #define     CRPT_AES2_KEY2      (CRPT_BA+0x190)   /*!< AES Key Word 2 Register for Channel 2              */
    #define     CRPT_AES2_KEY3      (CRPT_BA+0x194)   /*!< AES Key Word 3 Register for Channel 2              */
    #define     CRPT_AES2_KEY4      (CRPT_BA+0x198)   /*!< AES Key Word 4 Register for Channel 2              */
    #define     CRPT_AES2_KEY5      (CRPT_BA+0x19C)   /*!< AES Key Word 5 Register for Channel 2              */
    #define     CRPT_AES2_KEY6      (CRPT_BA+0x1A0)   /*!< AES Key Word 6 Register for Channel 2              */
    #define     CRPT_AES2_KEY7      (CRPT_BA+0x1A4)   /*!< AES Key Word 7 Register for Channel 2              */
    #define     CRPT_AES2_IV0       (CRPT_BA+0x1A8)   /*!< AES Initial Vector Word 0 Register for Channel 2   */
    #define     CRPT_AES2_IV1       (CRPT_BA+0x1AC)   /*!< AES Initial Vector Word 1 Register for Channel 2   */
    #define     CRPT_AES2_IV2       (CRPT_BA+0x1B0)   /*!< AES Initial Vector Word 2 Register for Channel 2   */
    #define     CRPT_AES2_IV3       (CRPT_BA+0x1B4)   /*!< AES Initial Vector Word 3 Register for Channel 2   */
    #define     CRPT_AES2_SADDR     (CRPT_BA+0x1B8)   /*!< AES DMA Source Address Register for Channel 2      */
    #define     CRPT_AES2_DADDR     (CRPT_BA+0x1BC)   /*!< AES DMA Destination Address Register for Channel 2 */
    #define     CRPT_AES2_CNT       (CRPT_BA+0x1C0)   /*!< AES Byte Count Register for Channel 2              */
    #define     CRPT_AES3_KEY0      (CRPT_BA+0x1C4)   /*!< AES Key Word 0 Register for Channel 3              */
    #define     CRPT_AES3_KEY1      (CRPT_BA+0x1C8)   /*!< AES Key Word 1 Register for Channel 3              */
    #define     CRPT_AES3_KEY2      (CRPT_BA+0x1CC)   /*!< AES Key Word 2 Register for Channel 3              */
    #define     CRPT_AES3_KEY3      (CRPT_BA+0x1D0)   /*!< AES Key Word 3 Register for Channel 3              */
    #define     CRPT_AES3_KEY4      (CRPT_BA+0x1D4)   /*!< AES Key Word 4 Register for Channel 3              */
    #define     CRPT_AES3_KEY5      (CRPT_BA+0x1D8)   /*!< AES Key Word 5 Register for Channel 3              */
    #define     CRPT_AES3_KEY6      (CRPT_BA+0x1DC)   /*!< AES Key Word 6 Register for Channel 3              */
    #define     CRPT_AES3_KEY7      (CRPT_BA+0x1E0)   /*!< AES Key Word 7 Register for Channel 3              */
    #define     CRPT_AES3_IV0       (CRPT_BA+0x1E4)   /*!< AES Initial Vector Word 0 Register for Channel 3   */
    #define     CRPT_AES3_IV1       (CRPT_BA+0x1E8)   /*!< AES Initial Vector Word 1 Register for Channel 3   */
    #define     CRPT_AES3_IV2       (CRPT_BA+0x1EC)   /*!< AES Initial Vector Word 2 Register for Channel 3   */
    #define     CRPT_AES3_IV3       (CRPT_BA+0x1F0)   /*!< AES Initial Vector Word 3 Register for Channel 3   */
    #define     CRPT_AES3_SADDR     (CRPT_BA+0x1F4)   /*!< AES DMA Source Address Register for Channel 3      */
    #define     CRPT_AES3_DADDR     (CRPT_BA+0x1F8)   /*!< AES DMA Destination Address Register for Channel 3 */
    #define     CRPT_AES3_CNT       (CRPT_BA+0x1FC)   /*!< AES Byte Count Register for Channel 3              */

    /* DES/TDES Control Registers */
    #define     CRPT_TDES_CTL       (CRPT_BA+0x200)   /*!< TDES/DES Control Register                          */
    #define     CRPT_TDES_STS       (CRPT_BA+0x204)   /*!< TDES/DES Engine Flag                               */
    #define     CRPT_TDES0_KEY1H    (CRPT_BA+0x208)   /*!< TDES/DES Key 1 High Word Register for Channel 0    */
    #define     CRPT_TDES0_KEY1L    (CRPT_BA+0x20C)   /*!< TDES/DES Key 1 Low Word Register for Channel 0     */
    #define     CRPT_TDES0_KEY2H    (CRPT_BA+0x210)   /*!< TDES/DES Key 2 High Word Register for Channel 0    */
    #define     CRPT_TDES0_KEY2L    (CRPT_BA+0x214)   /*!< TDES/DES Key 2 Low Word Register for Channel 0     */
    #define     CRPT_TDES0_KEY3H    (CRPT_BA+0x218)   /*!< TDES/DES Key 3 High Word Register for Channel 0    */
    #define     CRPT_TDES0_KEY3L    (CRPT_BA+0x21C)   /*!< TDES/DES Key 3 Low Word Register for Channel 0     */
    #define     CRPT_TDES0_IVH      (CRPT_BA+0x220)   /*!< TDES/DES Initial Vector High Word Register for Channel 0 */
    #define     CRPT_TDES0_IVL      (CRPT_BA+0x224)   /*!< TDES/DES Initial Vector Low Word Register for Channel 0  */
    #define     CRPT_TDES0_SADDR    (CRPT_BA+0x228)   /*!< TDES/DES DMA Source Address Register for Channel 0       */
    #define     CRPT_TDES0_DADDR    (CRPT_BA+0x22C)   /*!< TDES/DES DMA Destination Address Register for Channel 0  */
    #define     CRPT_TDES0_CNT      (CRPT_BA+0x230)   /*!< TDES/DES Byte Count Register for Channel 0         */
    #define     CRPT_TDES_DATIN     (CRPT_BA+0x234)   /*!< TDES/DES Engine Input data Word Register           */
    #define     CRPT_TDES_DATOUT    (CRPT_BA+0x238)   /*!< TDES/DES Engine Output data Word Register          */
    #define     CRPT_TDES1_KEY1H    (CRPT_BA+0x248)   /*!< TDES/DES Key 1 High Word Register for Channel 1    */
    #define     CRPT_TDES1_KEY1L    (CRPT_BA+0x24C)   /*!< TDES/DES Key 1 Low Word Register for Channel 1     */
    #define     CRPT_TDES1_KEY2H    (CRPT_BA+0x250)   /*!< TDES/DES Key 2 High Word Register for Channel 1    */
    #define     CRPT_TDES1_KEY2L    (CRPT_BA+0x254)   /*!< TDES/DES Key 2 Low Word Register for Channel 1     */
    #define     CRPT_TDES1_KEY3H    (CRPT_BA+0x258)   /*!< TDES/DES Key 3 High Word Register for Channel 1    */
    #define     CRPT_TDES1_KEY3L    (CRPT_BA+0x25C)   /*!< TDES/DES Key 3 Low Word Register for Channel 1     */
    #define     CRPT_TDES1_IVH      (CRPT_BA+0x260)   /*!< TDES/DES Initial Vector High Word Register for Channel 1 */
    #define     CRPT_TDES1_IVL      (CRPT_BA+0x264)   /*!< TDES/DES Initial Vector Low Word Register for Channel 1  */
    #define     CRPT_TDES1_SADDR    (CRPT_BA+0x268)   /*!< TDES/DES DMA Source Address Register for Channel 1       */
    #define     CRPT_TDES1_DADDR    (CRPT_BA+0x26C)   /*!< TDES/DES DMA Destination Address Register for Channel 1  */
    #define     CRPT_TDES1_CNT      (CRPT_BA+0x270)   /*!< TDES/DES Byte Count Register for Channel 1         */
    #define     CRPT_TDES2_KEY1H    (CRPT_BA+0x288)   /*!< TDES/DES Key 1 High Word Register for Channel 2    */
    #define     CRPT_TDES2_KEY1L    (CRPT_BA+0x28C)   /*!< TDES/DES Key 1 Low Word Register for Channel 2     */
    #define     CRPT_TDES2_KEY2H    (CRPT_BA+0x290)   /*!< TDES/DES Key 2 High Word Register for Channel 2    */
    #define     CRPT_TDES2_KEY2L    (CRPT_BA+0x294)   /*!< TDES/DES Key 2 Low Word Register for Channel 2     */
    #define     CRPT_TDES2_KEY3H    (CRPT_BA+0x298)   /*!< TDES/DES Key 3 High Word Register for Channel 2    */
    #define     CRPT_TDES2_KEY3L    (CRPT_BA+0x29C)   /*!< TDES/DES Key 3 Low Word Register for Channel 2     */
    #define     CRPT_TDES2_IVH      (CRPT_BA+0x2A0)   /*!< TDES/DES Initial Vector High Word Register for Channel 2 */
    #define     CRPT_TDES2_IVL      (CRPT_BA+0x2A4)   /*!< TDES/DES Initial Vector Low Word Register for Channel 2  */
    #define     CRPT_TDES2_SADDR    (CRPT_BA+0x2A8)   /*!< TDES/DES DMA Source Address Register for Channel 2       */
    #define     CRPT_TDES2_DADDR    (CRPT_BA+0x2AC)   /*!< TDES/DES DMA Destination Address Register for Channel 2  */
    #define     CRPT_TDES2_CNT      (CRPT_BA+0x2B0)   /*!< TDES/DES Byte Count Register for Channel 3         */
    #define     CRPT_TDES3_KEY1H    (CRPT_BA+0x2C8)   /*!< TDES/DES Key 1 High Word Register for Channel 3    */
    #define     CRPT_TDES3_KEY1L    (CRPT_BA+0x2CC)   /*!< TDES/DES Key 1 Low Word Register for Channel 3     */
    #define     CRPT_TDES3_KEY2H    (CRPT_BA+0x2D0)   /*!< TDES/DES Key 2 High Word Register for Channel 3    */
    #define     CRPT_TDES3_KEY2L    (CRPT_BA+0x2D4)   /*!< TDES/DES Key 2 Low Word Register for Channel 3     */
    #define     CRPT_TDES3_KEY3H    (CRPT_BA+0x2D8)   /*!< TDES/DES Key 3 High Word Register for Channel 3    */
    #define     CRPT_TDES3_KEY3L    (CRPT_BA+0x2DC)   /*!< TDES/DES Key 3 Low Word Register for Channel 3     */
    #define     CRPT_TDES3_IVH      (CRPT_BA+0x2E0)   /*!< TDES/DES Initial Vector High Word Register for Channel 3 */
    #define     CRPT_TDES3_IVL      (CRPT_BA+0x2E4)   /*!< TDES/DES Initial Vector Low Word Register for Channel 3  */
    #define     CRPT_TDES3_SADDR    (CRPT_BA+0x2E8)   /*!< TDES/DES DMA Source Address Register for Channel 3       */
    #define     CRPT_TDES3_DADDR    (CRPT_BA+0x2EC)   /*!< TDES/DES DMA Destination Address Register for Channel 3  */
    #define     CRPT_TDES3_CNT      (CRPT_BA+0x2F0)   /*!< TDES/DES Byte Count Register for Channel 3         */

    /* SHA/HMAC Control Registers */
    #define     CRPT_HMAC_CTL       (CRPT_BA+0x300)   /*!< SHA/HMAC Control Register                          */
    #define     CRPT_HMAC_STS       (CRPT_BA+0x304)   /*!< SHA/HMAC Status Flag                               */
    #define     CRPT_HMAC_DGST0     (CRPT_BA+0x308)   /*!< SHA/HMAC Digest Message 0                          */
    #define     CRPT_HMAC_DGST1     (CRPT_BA+0x30C)   /*!< SHA/HMAC Digest Message 1                          */
    #define     CRPT_HMAC_DGST2     (CRPT_BA+0x310)   /*!< SHA/HMAC Digest Message 2                          */
    #define     CRPT_HMAC_DGST3     (CRPT_BA+0x314)   /*!< SHA/HMAC Digest Message 3                          */
    #define     CRPT_HMAC_DGST4     (CRPT_BA+0x318)   /*!< SHA/HMAC Digest Message 4                          */
    #define     CRPT_HMAC_DGST5     (CRPT_BA+0x31C)   /*!< SHA/HMAC Digest Message 5                          */
    #define     CRPT_HMAC_DGST6     (CRPT_BA+0x320)   /*!< SHA/HMAC Digest Message 6                          */
    #define     CRPT_HMAC_DGST7     (CRPT_BA+0x324)   /*!< SHA/HMAC Digest Message 7                          */
    #define     CRPT_HMAC_DGST8     (CRPT_BA+0x328)   /*!< SHA/HMAC Digest Message 8                          */
    #define     CRPT_HMAC_DGST9     (CRPT_BA+0x32C)   /*!< SHA/HMAC Digest Message 8                          */
    #define     CRPT_HMAC_DGST10    (CRPT_BA+0x330)   /*!< SHA/HMAC Digest Message 10                         */
    #define     CRPT_HMAC_DGST11    (CRPT_BA+0x334)   /*!< SHA/HMAC Digest Message 11                         */
    #define     CRPT_HMAC_DGST12    (CRPT_BA+0x338)   /*!< SHA/HMAC Digest Message 12                         */
    #define     CRPT_HMAC_DGST13    (CRPT_BA+0x33C)   /*!< SHA/HMAC Digest Message 13                         */
    #define     CRPT_HMAC_DGST14    (CRPT_BA+0x340)   /*!< SHA/HMAC Digest Message 14                         */
    #define     CRPT_HMAC_DGST15    (CRPT_BA+0x344)   /*!< SHA/HMAC Digest Message 15                         */
    #define     CRPT_HMAC_KEYCNT    (CRPT_BA+0x348)   /*!< SHA/HMAC Key Byte Count                            */
    #define     CRPT_HMAC_SADDR     (CRPT_BA+0x34C)   /*!< SHA/HMAC Key Byte Count                            */
    #define     CRPT_HMAC_DMACNT    (CRPT_BA+0x350)   /*!< SHA/HMAC Byte Count Register                       */
    #define     CRPT_HMAC_DATIN     (CRPT_BA+0x354)   /*!< SHA/HMAC Engine Non-DMA Mode Data Input Port Register  */

    /**@}*/ /* end of Cryptographic Accelerator register group */




    /*---------------------- Universal Asynchronous Receiver/Transmitter Controller -------------------------*/
    /**
    @addtogroup UART Universal Asynchronous Receiver/Transmitter Controller(UART)
    Memory Mapped Structure for UART Controller
    @{ */

    #define     REG_UART0_RBR    (UART0_BA+0x00)  /*!< Receive Buffer Register */
    #define     REG_UART0_THR    (UART0_BA+0x00)  /*!< Transmit Holding Register */
    #define     REG_UART0_IER    (UART0_BA+0x04)  /*!< Interrupt Enable Register */
    #define     REG_UART0_FCR    (UART0_BA+0x08)  /*!< FIFO Control Register */
    #define     REG_UART0_LCR    (UART0_BA+0x0C)  /*!< Line Control Register */
    #define     REG_UART0_MCR   (UART0_BA+0x10)  /*!< Modem Control Register */
    #define     REG_UART0_MSR    (UART0_BA+0x14)  /*!< MODEM Status Register */
    #define     REG_UART0_FSR    (UART0_BA+0x18)  /*!< FIFO Status Register */
    #define     REG_UART0_ISR   (UART0_BA+0x1C)  /*!< Interrupt Status Control Register */
    #define     REG_UART0_TOR       (UART0_BA+0x20)  /*!< Time-out Register */
    #define     REG_UART0_BAUD      (UART0_BA+0x24)  /*!< Baud Rate Divider Register */
    #define     REG_UART0_IRCR   (UART0_BA+0x28)  /*!< IrDA Control Register */
    #define     REG_UART0_ALT_CSR   (UART0_BA+0x2C)  /*!< Alternate Control Register */
    #define     REG_UART0_FUN_SEL   (UART0_BA+0x30)  /*!< UART Function Select REgister */
    #define     REG_UART0_LIN_CTL   (UART0_BA+0x34)  /*!< UART LIN Control Register */
    #define     REG_UART0_LIN_SR    (UART0_BA+0x38)  /*!< LIN Status Register */




    /*
    UART1 Control Registers
    */
    #define     REG_UART1_RBR   (UART1_BA+0x00)  /*!< Receive Buffer Register */
    #define     REG_UART1_THR   (UART1_BA+0x00)  /*!< Transmit Holding Register */
    #define     REG_UART1_IER   (UART1_BA+0x04)  /*!< Interrupt Enable Register */
    #define     REG_UART1_FCR   (UART1_BA+0x08)  /*!< FIFO Control Register */
    #define     REG_UART1_LCR   (UART1_BA+0x0C)  /*!< Line Control Register */
    #define     REG_UART1_MCR   (UART1_BA+0x10)  /*!< Modem Control Register */
    #define     REG_UART1_MSR   (UART1_BA+0x14)  /*!< MODEM Status Register */
    #define     REG_UART1_FSR       (UART1_BA+0x18)  /*!< FIFO Status Register */
    #define     REG_UART1_ISR   (UART1_BA+0x1C)  /*!< Interrupt Status Control Register */
    #define     REG_UART1_TOR       (UART1_BA+0x20)  /*!< Time-out Register */
    #define     REG_UART1_BAUD      (UART1_BA+0x24)  /*!< Baud Rate Divider Register */
    #define     REG_UART1_IRCR      (UART1_BA+0x28)  /*!< IrDA Control Register */
    #define     REG_UART1_ALT_CSR   (UART1_BA+0x2C)  /*!< Alternate Control Register */
    #define     REG_UART1_FUN_SEL   (UART1_BA+0x30)  /*!< UART Function Select REgister */
    #define     REG_UART1_LIN_CTL   (UART1_BA+0x34)  /*!< UART LIN Control Register */
    #define     REG_UART1_LIN_SR    (UART1_BA+0x38)  /*!< LIN Status Register */

    /*
    UART2 Control Registers
    */
    #define     REG_UART2_RBR   (UART2_BA+0x00)  /*!< Receive Buffer Register */
    #define     REG_UART2_THR   (UART2_BA+0x00)  /*!< Transmit Holding Register */
    #define     REG_UART2_IER   (UART2_BA+0x04)  /*!< Interrupt Enable Register */
    #define     REG_UART2_FCR   (UART2_BA+0x08)  /*!< FIFO Control Register */
    #define     REG_UART2_LCR   (UART2_BA+0x0C)  /*!< Line Control Register */
    #define     REG_UART2_MCR   (UART2_BA+0x10)  /*!< Modem Control Register */
    #define     REG_UART2_MSR   (UART2_BA+0x14)  /*!< MODEM Status Register */
    #define     REG_UART2_FSR   (UART2_BA+0x18)  /*!< FIFO Status Register */
    #define     REG_UART2_ISR   (UART2_BA+0x1C)  /*!< Interrupt Status Control Register */
    #define     REG_UART2_TOR   (UART2_BA+0x20)  /*!< Time-out Register */
    #define     REG_UART2_BAUD  (UART2_BA+0x24)  /*!< Baud Rate Divider Register */
    #define     REG_UART2_IRCR  (UART2_BA+0x28)  /*!< IrDA Control Register */
    #define     REG_UART2_ALT_CSR   (UART2_BA+0x2C)  /*!< Alternate Control Register */
    #define     REG_UART2_FUN_SEL   (UART2_BA+0x30)  /*!< UART Function Select REgister */
    #define     REG_UART2_LIN_CTL   (UART2_BA+0x34)  /*!< UART LIN Control Register */
    #define     REG_UART2_LIN_SR    (UART2_BA+0x38)  /*!< LIN Status Register */

    /*
    UART3 Control Registers
    */
    #define     REG_UART3_RBR   (UART3_BA+0x00)  /*!< Receive Buffer Register */
    #define     REG_UART3_THR   (UART3_BA+0x00)  /*!< Transmit Holding Register */
    #define     REG_UART3_IER   (UART3_BA+0x04)  /*!< Interrupt Enable Register */
    #define     REG_UART3_FCR   (UART3_BA+0x08)  /*!< FIFO Control Register */
    #define     REG_UART3_LCR   (UART3_BA+0x0C)  /*!< Line Control Register */
    #define     REG_UART3_MCR   (UART3_BA+0x10)  /*!< Modem Control Register */
    #define     REG_UART3_MSR   (UART3_BA+0x14)  /*!< MODEM Status Register */
    #define     REG_UART3_FSR   (UART3_BA+0x18)  /*!< FIFO Status Register */
    #define     REG_UART3_ISR   (UART3_BA+0x1C)  /*!< Interrupt Status Control Register */
    #define     REG_UART3_TOR   (UART3_BA+0x20)  /*!< Time-out Register */
    #define     REG_UART3_BAUD  (UART3_BA+0x24)  /*!< Baud Rate Divider Register */
    #define     REG_UART3_IRCR  (UART3_BA+0x28)  /*!< IrDA Control Register */
    #define     REG_UART3_ALT_CSR   (UART3_BA+0x2C)  /*!< Alternate Control Register */
    #define     REG_UART3_FUN_SEL   (UART3_BA+0x30)  /*!< UART Function Select REgister */
    #define     REG_UART3_LIN_CTL   (UART3_BA+0x34)  /*!< UART LIN Control Register */
    #define     REG_UART3_LIN_SR    (UART3_BA+0x38)  /*!< LIN Status Register */


    /*
    UART4 Control Registers
    */
    #define     REG_UART4_RBR   (UART4_BA+0x00)  /*!< Receive Buffer Register */
    #define     REG_UART4_THR   (UART4_BA+0x00)  /*!< Transmit Holding Register */
    #define     REG_UART4_IER   (UART4_BA+0x04)  /*!< Interrupt Enable Register */
    #define     REG_UART4_FCR   (UART4_BA+0x08)  /*!< FIFO Control Register */
    #define     REG_UART4_LCR   (UART4_BA+0x0C)  /*!< Line Control Register */
    #define     REG_UART4_MCR   (UART4_BA+0x10)  /*!< Modem Control Register */
    #define     REG_UART4_MSR   (UART4_BA+0x14)  /*!< MODEM Status Register */
    #define     REG_UART4_FSR   (UART4_BA+0x18)  /*!< FIFO Status Register */
    #define     REG_UART4_ISR   (UART4_BA+0x1C)  /*!< Interrupt Status Control Register */
    #define     REG_UART4_TOR   (UART4_BA+0x20)  /*!< Time-out Register */
    #define     REG_UART4_BAUD  (UART4_BA+0x24)  /*!< Baud Rate Divider Register */
    #define     REG_UART4_IRCR  (UART4_BA+0x28)  /*!< IrDA Control Register */
    #define     REG_UART4_ALT_CSR   (UART4_BA+0x2C)  /*!< Alternate Control Register */
    #define     REG_UART4_FUN_SEL   (UART4_BA+0x30)  /*!< UART Function Select REgister */
    #define     REG_UART4_LIN_CTL   (UART4_BA+0x34)  /*!< UART LIN Control Register */
    #define     REG_UART4_LIN_SR    (UART4_BA+0x38)  /*!< LIN Status Register */

    /*
    UART5 Control Registers
    */
    #define     REG_UART5_RBR   (UART5_BA+0x00)  /*!< Receive Buffer Register */
    #define     REG_UART5_THR   (UART5_BA+0x00)  /*!< Transmit Holding Register */
    #define     REG_UART5_IER   (UART5_BA+0x04)  /*!< Interrupt Enable Register */
    #define     REG_UART5_FCR   (UART5_BA+0x08)  /*!< FIFO Control Register */
    #define     REG_UART5_LCR   (UART5_BA+0x0C)  /*!< Line Control Register */
    #define     REG_UART5_MCR   (UART5_BA+0x10)  /*!< Modem Control Register */
    #define     REG_UART5_MSR   (UART5_BA+0x14)  /*!< MODEM Status Register */
    #define     REG_UART5_FSR   (UART5_BA+0x18)  /*!< FIFO Status Register */
    #define     REG_UART5_ISR   (UART5_BA+0x1C)  /*!< Interrupt Status Control Register */
    #define     REG_UART5_TOR   (UART5_BA+0x20)  /*!< Time-out Register */
    #define     REG_UART5_BAUD  (UART5_BA+0x24)  /*!< Baud Rate Divider Register */
    #define     REG_UART5_IRCR  (UART5_BA+0x28)  /*!< IrDA Control Register */
    #define     REG_UART5_ALT_CSR   (UART5_BA+0x2C)  /*!< Alternate Control Register */
    #define     REG_UART5_FUN_SEL   (UART5_BA+0x30)  /*!< UART Function Select REgister */
    #define     REG_UART5_LIN_CTL   (UART5_BA+0x34)  /*!< UART LIN Control Register */
    #define     REG_UART5_LIN_SR    (UART5_BA+0x38)  /*!< LIN Status Register */

    /*
    UART6 Control Registers
    */
    #define     REG_UART6_RBR   (UART6_BA+0x00)  /*!< Receive Buffer Register */
    #define     REG_UART6_THR   (UART6_BA+0x00)  /*!< Transmit Holding Register */
    #define     REG_UART6_IER   (UART6_BA+0x04)  /*!< Interrupt Enable Register */
    #define     REG_UART6_FCR   (UART6_BA+0x08)  /*!< FIFO Control Register */
    #define     REG_UART6_LCR   (UART6_BA+0x0C)  /*!< Line Control Register */
    #define     REG_UART6_MCR   (UART6_BA+0x10)  /*!< Modem Control Register */
    #define     REG_UART6_MSR   (UART6_BA+0x14)  /*!< MODEM Status Register */
    #define     REG_UART6_FSR   (UART6_BA+0x18)  /*!< FIFO Status Register */
    #define     REG_UART6_ISR   (UART6_BA+0x1C)  /*!< Interrupt Status Control Register */
    #define     REG_UART6_TOR   (UART6_BA+0x20)  /*!< Time-out Register */
    #define     REG_UART6_BAUD  (UART6_BA+0x24)  /*!< Baud Rate Divider Register */
    #define     REG_UART6_IRCR  (UART6_BA+0x28)  /*!< IrDA Control Register */
    #define     REG_UART6_ALT_CSR   (UART6_BA+0x2C)  /*!< Alternate Control Register */
    #define     REG_UART6_FUN_SEL   (UART6_BA+0x30)  /*!< UART Function Select REgister */
    #define     REG_UART6_LIN_CTL   (UART6_BA+0x34)  /*!< UART LIN Control Register */
    #define     REG_UART6_LIN_SR    (UART6_BA+0x38)  /*!< LIN Status Register */

    /*
    UART7 Control Registers
    */
    #define     REG_UART7_RBR   (UART7_BA+0x00)  /*!< Receive Buffer Register */
    #define     REG_UART7_THR   (UART7_BA+0x00)  /*!< Transmit Holding Register */
    #define     REG_UART7_IER   (UART7_BA+0x04)  /*!< Interrupt Enable Register */
    #define     REG_UART7_FCR   (UART7_BA+0x08)  /*!< FIFO Control Register */
    #define     REG_UART7_LCR   (UART7_BA+0x0C)  /*!< Line Control Register */
    #define     REG_UART7_MCR   (UART7_BA+0x10)  /*!< Modem Control Register */
    #define     REG_UART7_MSR   (UART7_BA+0x14)  /*!< MODEM Status Register */
    #define     REG_UART7_FSR   (UART7_BA+0x18)  /*!< FIFO Status Register */
    #define     REG_UART7_ISR   (UART7_BA+0x1C)  /*!< Interrupt Status Control Register */
    #define     REG_UART7_TOR   (UART7_BA+0x20)  /*!< Time-out Register */
    #define     REG_UART7_BAUD  (UART7_BA+0x24)  /*!< Baud Rate Divider Register */
    #define     REG_UART7_IRCR  (UART7_BA+0x28)  /*!< IrDA Control Register */
    #define     REG_UART7_ALT_CSR   (UART7_BA+0x2C)  /*!< Alternate Control Register */
    #define     REG_UART7_FUN_SEL   (UART7_BA+0x30)  /*!< UART Function Select REgister */
    #define     REG_UART7_LIN_CTL   (UART7_BA+0x34)  /*!< UART LIN Control Register */
    #define     REG_UART7_LIN_SR    (UART7_BA+0x38)  /*!< LIN Status Register */

    /*
    UART8 Control Registers
    */
    #define     REG_UART8_RBR   (UART8_BA+0x00)  /*!< Receive Buffer Register */
    #define     REG_UART8_THR   (UART8_BA+0x00)  /*!< Transmit Holding Register */
    #define     REG_UART8_IER   (UART8_BA+0x04)  /*!< Interrupt Enable Register */
    #define     REG_UART8_FCR   (UART8_BA+0x08)  /*!< FIFO Control Register */
    #define     REG_UART8_LCR   (UART8_BA+0x0C)  /*!< Line Control Register */
    #define     REG_UART8_MCR   (UART8_BA+0x10)  /*!< Modem Control Register */
    #define     REG_UART8_MSR   (UART8_BA+0x14)  /*!< MODEM Status Register */
    #define     REG_UART8_FSR   (UART8_BA+0x18)  /*!< FIFO Status Register */
    #define     REG_UART8_ISR   (UART8_BA+0x1C)  /*!< Interrupt Status Control Register */
    #define     REG_UART8_TOR   (UART8_BA+0x20)  /*!< Time-out Register */
    #define     REG_UART8_BAUD  (UART8_BA+0x24)  /*!< Baud Rate Divider Register */
    #define     REG_UART8_IRCR  (UART8_BA+0x28)  /*!< IrDA Control Register */
    #define     REG_UART8_ALT_CSR   (UART8_BA+0x2C)  /*!< Alternate Control Register */
    #define     REG_UART8_FUN_SEL   (UART8_BA+0x30)  /*!< UART Function Select REgister */
    #define     REG_UART8_LIN_CTL   (UART8_BA+0x34)  /*!< UART LIN Control Register */
    #define     REG_UART8_LIN_SR    (UART8_BA+0x38)  /*!< LIN Status Register */

    /*
    UART9 Control Registers
    */
    #define     REG_UART9_RBR   (UART9_BA+0x00)  /*!< Receive Buffer Register */
    #define     REG_UART9_THR   (UART9_BA+0x00)  /*!< Transmit Holding Register */
    #define     REG_UART9_IER   (UART9_BA+0x04)  /*!< Interrupt Enable Register */
    #define     REG_UART9_FCR   (UART9_BA+0x08)  /*!< FIFO Control Register */
    #define     REG_UART9_LCR   (UART9_BA+0x0C)  /*!< Line Control Register */
    #define     REG_UART9_MCR   (UART9_BA+0x10)  /*!< Modem Control Register */
    #define     REG_UART9_MSR   (UART9_BA+0x14)  /*!< MODEM Status Register */
    #define     REG_UART9_FSR   (UART9_BA+0x18)  /*!< FIFO Status Register */
    #define     REG_UART9_ISR   (UART9_BA+0x1C)  /*!< Interrupt Status Control Register */
    #define     REG_UART9_TOR   (UART9_BA+0x20)  /*!< Time-out Register */
    #define     REG_UART9_BAUD  (UART9_BA+0x24)  /*!< Baud Rate Divider Register */
    #define     REG_UART9_IRCR  (UART9_BA+0x28)  /*!< IrDA Control Register */
    #define     REG_UART9_ALT_CSR   (UART9_BA+0x2C)  /*!< Alternate Control Register */
    #define     REG_UART9_FUN_SEL   (UART9_BA+0x30)  /*!< UART Function Select REgister */
    #define     REG_UART9_LIN_CTL   (UART9_BA+0x34)  /*!< UART LIN Control Register */
    #define     REG_UART9_LIN_SR    (UART9_BA+0x38)  /*!< LIN Status Register */

    /*
    UARTA Control Registers
    */
    #define     REG_UARTA_RBR   (UARTA_BA+0x00)  /*!< Receive Buffer Register */
    #define     REG_UARTA_THR   (UARTA_BA+0x00)  /*!< Transmit Holding Register */
    #define     REG_UARTA_IER   (UARTA_BA+0x04)  /*!< Interrupt Enable Register */
    #define     REG_UARTA_FCR   (UARTA_BA+0x08)  /*!< FIFO Control Register */
    #define     REG_UARTA_LCR   (UARTA_BA+0x0C)  /*!< Line Control Register */
    #define     REG_UARTA_MCR   (UARTA_BA+0x10)  /*!< Modem Control Register */
    #define     REG_UARTA_MSR   (UARTA_BA+0x14)  /*!< MODEM Status Register */
    #define     REG_UARTA_FSR   (UARTA_BA+0x18)  /*!< FIFO Status Register */
    #define     REG_UARTA_ISR   (UARTA_BA+0x1C)  /*!< Interrupt Status Control Register */
    #define     REG_UARTA_TOR   (UARTA_BA+0x20)  /*!< Time-out Register */
    #define     REG_UARTA_BAUD  (UARTA_BA+0x24)  /*!< Baud Rate Divider Register */
    #define     REG_UARTA_IRCR  (UARTA_BA+0x28)  /*!< IrDA Control Register */
    #define     REG_UARTA_ALT_CSR   (UARTA_BA+0x2C)  /*!< Alternate Control Register */
    #define     REG_UARTA_FUN_SEL   (UARTA_BA+0x30)  /*!< UART Function Select REgister */
    #define     REG_UARTA_LIN_CTL   (UARTA_BA+0x34)  /*!< UART LIN Control Register */
    #define     REG_UARTA_LIN_SR    (UARTA_BA+0x38)  /*!< LIN Status Register */


    /**@}*/ /* end of UART register group */


    /*---------------------- Timer Controller -------------------------*/
    /**
    @addtogroup TIMER Timer Controller(TIMER)
    Memory Mapped Structure for TIMER Controller
    @{ */

    #define     REG_TMR0_CSR    (TMR0_BA+0x00)  /*!< Timer Control and Status Register 0  */
    #define     REG_TMR0_CMPR   (TMR0_BA+0x04)  /*!< Timer Compare Register 0             */
    #define     REG_TMR0_DR     (TMR0_BA+0x08)  /*!< Timer Data Register 0                */

    #define     REG_TMR1_CSR    (TMR1_BA+0x00)  /*!< Timer Control and Status Register 1  */
    #define     REG_TMR1_CMPR   (TMR1_BA+0x04)  /*!< Timer Compare Register 1             */
    #define     REG_TMR1_TDR    (TMR1_BA+0x08)  /*!< Timer Data Register 1                */

    #define     REG_TMR2_CSR    (TMR2_BA+0x00)  /*!< Timer Control and Status Register 2  */
    #define     REG_TMR2_CMPR   (TMR2_BA+0x04)  /*!< Timer Compare Register 2             */
    #define     REG_TMR2_DR     (TMR2_BA+0x08)  /*!< Timer Data Register 2                */

    #define     REG_TMR3_CSR    (TMR3_BA+0x00)  /*!< Timer Control and Status Register 3  */
    #define     REG_TMR3_CMPR   (TMR3_BA+0x04)  /*!< Timer Compare Register 3             */
    #define     REG_TMR3_DR     (TMR3_BA+0x08)  /*!< Timer Data Register 3                */

    #define     REG_TMR4_CSR    (TMR4_BA+0x00)  /*!< Timer Control and Status Register 4  */
    #define     REG_TMR4_CMPR   (TMR4_BA+0x04)  /*!< Timer Compare Register 4             */
    #define     REG_TMR4_DR     (TMR4_BA+0x08)  /*!< Timer Data Register 4                */

    #define     REG_TMR_ISR     (TMR0_BA+0x60)  /*!< Timer Interrupt Status Register      */

    /**@}*/ /* end of TIMER register group */

    /*---------------------- Enhance Timer Controller -------------------------*/
    /**
    @addtogroup ETIMER Enhance Timer Controller(ETIMER)
    Memory Mapped Structure for TIMER Controller
    @{ */

    #define     REG_ETMR0_CTL       (ETMR0_BA+0x00)  /*!< Enhance Timer 0 Control Register */
    #define     REG_ETMR0_PRECNT    (ETMR0_BA+0x04)  /*!< Enhance Timer 0 Pre-Scale Counter Register */
    #define     REG_ETMR0_CMPR      (ETMR0_BA+0x08)  /*!< Enhance Timer 0 Compare Register */
    #define     REG_ETMR0_IER       (ETMR0_BA+0x0C)  /*!< Enhance Timer 0 Interrupt Enable Register */
    #define     REG_ETMR0_ISR       (ETMR0_BA+0x10)  /*!< Enhance Timer 0 Interrupt Status Register  */
    #define     REG_ETMR0_DR        (ETMR0_BA+0x14)  /*!< Enhance Timer 0 Data Register */
    #define     REG_ETMR0_TCAP      (ETMR0_BA+0x18)  /*!< Enhance Timer 0 Capture Data Register  */

    #define     REG_ETMR1_CTL       (ETMR1_BA+0x00)  /*!< Enhance Timer 1 Control Register */
    #define     REG_ETMR1_PRECNT    (ETMR1_BA+0x04)  /*!< Enhance Timer 1 Pre-Scale Counter Register */
    #define     REG_ETMR1_CMPR      (ETMR1_BA+0x08)  /*!< Enhance Timer 1 Compare Register */
    #define     REG_ETMR1_IER       (ETMR1_BA+0x0C)  /*!< Enhance Timer 1 Interrupt Enable Register */
    #define     REG_ETMR1_ISR       (ETMR1_BA+0x10)  /*!< Enhance Timer 1 Interrupt Status Register  */
    #define     REG_ETMR1_DR        (ETMR1_BA+0x14)  /*!< Enhance Timer 1 Data Register */
    #define     REG_ETMR1_TCAP      (ETMR1_BA+0x18)  /*!< Enhance Timer 1 Capture Data Register  */

    #define     REG_ETMR2_CTL       (ETMR2_BA+0x00)  /*!< Enhance Timer 2 Control Register */
    #define     REG_ETMR2_PRECNT    (ETMR2_BA+0x04)  /*!< Enhance Timer 2 Pre-Scale Counter Register */
    #define     REG_ETMR2_CMPR      (ETMR2_BA+0x08)  /*!< Enhance Timer 2 Compare Register */
    #define     REG_ETMR2_IER       (ETMR2_BA+0x0C)  /*!< Enhance Timer 2 Interrupt Enable Register */
    #define     REG_ETMR2_ISR       (ETMR2_BA+0x10)  /*!< Enhance Timer 2 Interrupt Status Register  */
    #define     REG_ETMR2_DR        (ETMR2_BA+0x14)  /*!< Enhance Timer 2 Data Register */
    #define     REG_ETMR2_TCAP      (ETMR2_BA+0x18)  /*!< Enhance Timer 2 Capture Data Register  */

    #define     REG_ETMR3_CTL       (ETMR3_BA+0x00)  /*!< Enhance Timer 3 Control Register */
    #define     REG_ETMR3_PRECNT    (ETMR3_BA+0x04)  /*!< Enhance Timer 3 Pre-Scale Counter Register */
    #define     REG_ETMR3_CMPR      (ETMR3_BA+0x08)  /*!< Enhance Timer 3 Compare Register */
    #define     REG_ETMR3_IER       (ETMR3_BA+0x0C)  /*!< Enhance Timer 3 Interrupt Enable Register */
    #define     REG_ETMR3_ISR       (ETMR3_BA+0x10)  /*!< Enhance Timer 3 Interrupt Status Register  */
    #define     REG_ETMR3_DR        (ETMR3_BA+0x14)  /*!< Enhance Timer 3 Data Register */
    #define     REG_ETMR3_TCAP      (ETMR3_BA+0x18)  /*!< Enhance Timer 3 Capture Data Register  */
    /**@}*/ /* end of ETIMER register group */

    /*---------------------- WDT Controller -------------------------*/
    /**
    @addtogroup WDT Watch Dog Timer Controller(WDT)
    Memory Mapped Structure for WDT Controller
    @{ */

    #define     REG_WDT_CTL         (WDT_BA+0x00)  /*!< WDT Control Register              */
    #define     REG_WDT_ALTCTL      (WDT_BA+0x04)  /*!< WDT Alternative Control Register  */

    /**@}*/ /* end of WDT register group */

    /*---------------------- WWDT Controller -------------------------*/
    /**
    @addtogroup WWDT Window Watch Dog Timer Controller(WWDT)
    Memory Mapped Structure for WWDT Controller
    @{ */

    #define     REG_WWDT_RLDCNT     (WWDT_BA+0x00)  /*!< WWDT Reload Counter Register             */
    #define     REG_WWDT_CTL        (WWDT_BA+0x04)  /*!< WWDT Control Register                    */
    #define     REG_WWDT_STATUS     (WWDT_BA+0x08)  /*!< WWDT Status Register                     */
    #define     REG_WWDT_CNT        (WWDT_BA+0x0C)  /*!< WWDT Counter Value Register              */

    /**@}*/ /* end of WWDT register group */

    /*---------------------- SC Host Interface -------------------------*/
    /**
    @addtogroup SC Smart Card Host Interface (SC)
    Memory Mapped Structure for Smart Card Host Interface
    @{ */

    #define     REG_SC0_DAT     (SC0_BA+0x00)  /*!< SC0 Receiving/Transmit Holding Buffer Register */
    #define     REG_SC0_CTL     (SC0_BA+0x04)  /*!< SC0 Control Register */
    #define     REG_SC0_ALTCTL  (SC0_BA+0x08)  /*!< SC0 Alternate Control Register  */
    #define     REG_SC0_EGT     (SC0_BA+0x0C)  /*!< SC0 Extend Guard Time Register  */
    #define     REG_SC0_RXTOUT  (SC0_BA+0x10)  /*!< SC0 Receive Buffer Time-out Register */
    #define     REG_SC0_ETUCTL  (SC0_BA+0x14)  /*!< SC0 ETU Control Register */
    #define     REG_SC0_INTEN   (SC0_BA+0x18)  /*!< SC0 Interrupt Enable Control Register */
    #define     REG_SC0_INTSTS  (SC0_BA+0x1C)  /*!< SC0 Interrupt Status Register */
    #define     REG_SC0_STATUS  (SC0_BA+0x20)  /*!< SC0 Status Register */
    #define     REG_SC0_PINCTL  (SC0_BA+0x24)  /*!< SC0 Pin Control State Register */
    #define     REG_SC0_TMRCTL0 (SC0_BA+0x28)  /*!< SC0 Internal Timer Control Register 0 */
    #define     REG_SC0_TMRCTL1 (SC0_BA+0x2C)  /*!< SC0 Internal Timer Control Register 1 */
    #define     REG_SC0_TMRCTL2 (SC0_BA+0x30)  /*!< SC0 Internal Timer Control Register 2 */
    #define     REG_SC0_UARTCTL (SC0_BA+0x34)  /*!< SC0 UART Mode Control Register */
    #define     REG_SC0_TMRDAT0 (SC0_BA+0x38)  /*!< SC0 Timer Current Data Register 0 */
    #define     REG_SC0_TMRDAT1 (SC0_BA+0x3C)  /*!< SC0 Timer Current Data Register 1 */

    #define     REG_SC1_DAT     (SC1_BA+0x00)  /*!< SC1 Receiving/Transmit Holding Buffer Register */
    #define     REG_SC1_CTL     (SC1_BA+0x04)  /*!< SC1 Control Register */
    #define     REG_SC1_ALTCTL  (SC1_BA+0x08)  /*!< SC1 Alternate Control Register  */
    #define     REG_SC1_EGT     (SC1_BA+0x0C)  /*!< SC1 Extend Guard Time Register  */
    #define     REG_SC1_RXTOUT  (SC1_BA+0x10)  /*!< SC1 Receive Buffer Time-out Register */
    #define     REG_SC1_ETUCTL  (SC1_BA+0x14)  /*!< SC1 ETU Control Register */
    #define     REG_SC1_INTEN   (SC1_BA+0x18)  /*!< SC1 Interrupt Enable Control Register */
    #define     REG_SC1_INTSTS  (SC1_BA+0x1C)  /*!< SC1 Interrupt Status Register */
    #define     REG_SC1_STATUS  (SC1_BA+0x20)  /*!< SC1 Status Register */
    #define     REG_SC1_PINCTL  (SC1_BA+0x24)  /*!< SC1 Pin Control State Register */
    #define     REG_SC1_TMRCTL0 (SC1_BA+0x28)  /*!< SC1 Internal Timer Control Register 0 */
    #define     REG_SC1_TMRCTL1 (SC1_BA+0x2C)  /*!< SC1 Internal Timer Control Register 1 */
    #define     REG_SC1_TMRCTL2 (SC1_BA+0x30)  /*!< SC1 Internal Timer Control Register 2 */
    #define     REG_SC1_UARTCTL (SC1_BA+0x34)  /*!< SC1 UART Mode Control Register */
    #define     REG_SC1_TMRDAT0 (SC1_BA+0x38)  /*!< SC1 Timer Current Data Register 0 */
    #define     REG_SC1_TMRDAT1 (SC1_BA+0x3C)  /*!< SC1 Timer Current Data Register 1 */

    /**@}*/ /* end of SC register group */


    /*---------------------- Advance Interrupt Controller -------------------------*/
    /**
    @addtogroup AIC Advance Interrupt Controller(AIC)
    Memory Mapped Structure for AIC Controller
    @{ */

    #define     REG_AIC_SCR1    (AIC_BA+0x00)    /*!< Source control register 1 */
    #define     REG_AIC_SCR2    (AIC_BA+0x04)    /*!< Source control register 2 */
    #define     REG_AIC_SCR3    (AIC_BA+0x08)    /*!< Source control register 3 */
    #define     REG_AIC_SCR4    (AIC_BA+0x0C)    /*!< Source control register 4 */
    #define     REG_AIC_SCR5    (AIC_BA+0x10)    /*!< Source control register 5 */
    #define     REG_AIC_SCR6    (AIC_BA+0x14)    /*!< Source control register 6 */
    #define     REG_AIC_SCR7    (AIC_BA+0x18)    /*!< Source control register 7 */
    #define     REG_AIC_SCR8    (AIC_BA+0x1C)    /*!< Source control register 8 */
    #define     REG_AIC_SCR9    (AIC_BA+0x20)    /*!< Source control register 9 */
    #define     REG_AIC_SCR10   (AIC_BA+0x24)    /*!< Source control register 10 */
    #define     REG_AIC_SCR11   (AIC_BA+0x28)    /*!< Source control register 11 */
    #define     REG_AIC_SCR12   (AIC_BA+0x2C)    /*!< Source control register 12 */
    #define     REG_AIC_SCR13   (AIC_BA+0x30)    /*!< Source control register 13 */
    #define     REG_AIC_SCR14   (AIC_BA+0x34)    /*!< Source control register 14 */
    #define     REG_AIC_SCR15   (AIC_BA+0x38)    /*!< Source control register 15 */
    #define     REG_AIC_SCR16   (AIC_BA+0x3C)    /*!< Source control register 16 */
    #define     REG_AIC_IRSR    (AIC_BA+0x100)   /*!< Interrupt raw status register */
    #define     REG_AIC_IRSRH   (AIC_BA+0x104)   /*!< Interrupt raw status register (Hign) */
    #define     REG_AIC_IASR    (AIC_BA+0x108)   /*!< Interrupt active status register */
    #define     REG_AIC_IASRH   (AIC_BA+0x10C)   /*!< Interrupt active status register (Hign) */
    #define     REG_AIC_ISR     (AIC_BA+0x110)   /*!< Interrupt status register */
    #define     REG_AIC_ISRH    (AIC_BA+0x114)   /*!< Interrupt status register (High) */
    #define     REG_AIC_IPER    (AIC_BA+0x118)   /*!< Interrupt priority encoding register */
    #define     REG_AIC_ISNR    (AIC_BA+0x120)   /*!< Interrupt source number register */
    #define     REG_AIC_OISR    (AIC_BA+0x124)   /*!< Output interrupt status register */
    #define     REG_AIC_IMR     (AIC_BA+0x128)   /*!< Interrupt mask register */
    #define     REG_AIC_IMRH    (AIC_BA+0x12C)   /*!< Interrupt mask register (High) */
    #define     REG_AIC_MECR    (AIC_BA+0x130)   /*!< Mask enable command register */
    #define     REG_AIC_MECRH   (AIC_BA+0x134)   /*!< Mask enable command register (High) */
    #define     REG_AIC_MDCR    (AIC_BA+0x138)   /*!< Mask disable command register */
    #define     REG_AIC_MDCRH   (AIC_BA+0x13C)   /*!< Mask disable command register (High) */
    #define     REG_AIC_SSCR    (AIC_BA+0x140)   /*!< Source Set Command Register */
    #define     REG_AIC_SSCRH   (AIC_BA+0x144)   /*!< Source Set Command Register (High) */
    #define     REG_AIC_SCCR    (AIC_BA+0x148)   /*!< Source Clear Command Register */
    #define     REG_AIC_SCCRH   (AIC_BA+0x14C)   /*!< Source Clear Command Register (High) */
    #define     REG_AIC_EOSCR   (AIC_BA+0x150)   /*!< End of service command register */

    /**@}*/ /* end of AIC register group */


    /*---------------------- General Purpose Input/Output Controller -------------------------*/
    /**
    @addtogroup GPIO General Purpose Input/Output Controller(GPIO)
    Memory Mapped Structure for GPIO Controller
    @{ */

    #define     REG_GPIOA_DIR       (GPIO_BA+0x000)  /*!< GPIO portA direction control register */
    #define     REG_GPIOA_DATAOUT   (GPIO_BA+0x004)  /*!< GPIO portA data output register */
    #define     REG_GPIOA_DATAIN    (GPIO_BA+0x008)  /*!< GPIO portA data input register */
    #define     REG_GPIOA_IMD       (GPIO_BA+0x00C)  /*!< GPIO Port A Interrupt Mode Register */
    #define     REG_GPIOA_IREN      (GPIO_BA+0x010)  /*!< GPIO Port A Interrupt Rising-Edge or Level-High Enable Register */
    #define     REG_GPIOA_IFEN      (GPIO_BA+0x014)  /*!< GPIO Port A Interrupt Falling-Edge or Level-Low Enable Register */
    #define     REG_GPIOA_ISR       (GPIO_BA+0x018)  /*!< GPIO Port A Interrupt Status Register */
    #define     REG_GPIOA_DBEN      (GPIO_BA+0x01C)  /*!< GPIO Port A De-bounce Enable Register */
    #define     REG_GPIOA_PUEN      (GPIO_BA+0x020)  /*!< GPIO Port A Pull-Up Enable Register */
    #define     REG_GPIOA_PDEN      (GPIO_BA+0x024)  /*!< GPIO Port A Pull-Down Enable Register */
    #define     REG_GPIOA_ICEN      (GPIO_BA+0x028)  /*!< GPIO Port A CMOS Input Enable Register */
    #define     REG_GPIOA_ISEN      (GPIO_BA+0x02C)  /*!< GPIO Port A Schmitt-Trigger Input Enable Register */

    #define     REG_GPIOB_DIR       (GPIO_BA+0x040)  /*!< GPIO port B direction control register */
    #define     REG_GPIOB_DATAOUT   (GPIO_BA+0x044)  /*!< GPIO port B data output register */
    #define     REG_GPIOB_DATAIN    (GPIO_BA+0x048)  /*!< GPIO port B data input register */
    #define     REG_GPIOB_IMD       (GPIO_BA+0x04C)  /*!< GPIO Port B Interrupt Mode Register */
    #define     REG_GPIOB_IREN      (GPIO_BA+0x050)  /*!< GPIO Port B Interrupt Rising-Edge or Level-High Enable Register */
    #define     REG_GPIOB_IFEN      (GPIO_BA+0x054)  /*!< GPIO Port B Interrupt Falling-Edge or Level-Low Enable Register */
    #define     REG_GPIOB_ISR       (GPIO_BA+0x058)  /*!< GPIO Port B Interrupt Status Register */
    #define     REG_GPIOB_DBEN      (GPIO_BA+0x05C)  /*!< GPIO Port B De-bounce Enable Register */
    #define     REG_GPIOB_PUEN      (GPIO_BA+0x060)  /*!< GPIO Port B Pull-Up Enable Register */
    #define     REG_GPIOB_PDEN      (GPIO_BA+0x064)  /*!< GPIO Port B Pull-Down Enable Register */
    #define     REG_GPIOB_ICEN      (GPIO_BA+0x068)  /*!< GPIO Port B CMOS Input Enable Register */
    #define     REG_GPIOB_ISEN      (GPIO_BA+0x06C)  /*!< GPIO Port B Schmitt-Trigger Input Enable Register */

    #define     REG_GPIOC_DIR       (GPIO_BA+0x080)  /*!< GPIO port C direction control register */
    #define     REG_GPIOC_DATAOUT   (GPIO_BA+0x084)  /*!< GPIO port C data output register */
    #define     REG_GPIOC_DATAIN    (GPIO_BA+0x088)  /*!< GPIO port C data input register */
    #define     REG_GPIOC_IMD       (GPIO_BA+0x08C)  /*!< GPIO Port C Interrupt Mode Register */
    #define     REG_GPIOC_IREN      (GPIO_BA+0x090)  /*!< GPIO Port C Interrupt Rising-Edge or Level-High Enable Register */
    #define     REG_GPIOC_IFEN      (GPIO_BA+0x094)  /*!< GPIO Port C Interrupt Falling-Edge or Level-Low Enable Register */
    #define     REG_GPIOC_ISR       (GPIO_BA+0x098)  /*!< GPIO Port C Interrupt Status Register */
    #define     REG_GPIOC_DBEN      (GPIO_BA+0x09C)  /*!< GPIO Port C De-bounce Enable Register */
    #define     REG_GPIOC_PUEN      (GPIO_BA+0x0A0)  /*!< GPIO Port C Pull-Up Enable Register */
    #define     REG_GPIOC_PDEN      (GPIO_BA+0x0A4)  /*!< GPIO Port C Pull-Down Enable Register */
    #define     REG_GPIOC_ICEN      (GPIO_BA+0x0A8)  /*!< GPIO Port C CMOS Input Enable Register */
    #define     REG_GPIOC_ISEN      (GPIO_BA+0x0AC)  /*!< GPIO Port C Schmitt-Trigger Input Enable Register */

    #define     REG_GPIOD_DIR       (GPIO_BA+0x0C0)  /*!< GPIO port D direction control register */
    #define     REG_GPIOD_DATAOUT   (GPIO_BA+0x0C4)  /*!< GPIO port D data output register */
    #define     REG_GPIOD_DATAIN    (GPIO_BA+0x0C8)  /*!< GPIO port D data input register */
    #define     REG_GPIOD_IMD       (GPIO_BA+0x0CC)  /*!< GPIO Port D Interrupt Mode Register */
    #define     REG_GPIOD_IREN      (GPIO_BA+0x0D0)  /*!< GPIO Port D Interrupt Rising-Edge or Level-High Enable Register */
    #define     REG_GPIOD_IFEN      (GPIO_BA+0x0D4)  /*!< GPIO Port D Interrupt Falling-Edge or Level-Low Enable Register */
    #define     REG_GPIOD_ISR       (GPIO_BA+0x0D8)  /*!< GPIO Port D Interrupt Status Register */
    #define     REG_GPIOD_DBEN      (GPIO_BA+0x0DC)  /*!< GPIO Port D De-bounce Enable Register */
    #define     REG_GPIOD_PUEN      (GPIO_BA+0x0E0)  /*!< GPIO Port D Pull-Up Enable Register */
    #define     REG_GPIOD_PDEN      (GPIO_BA+0x0E4)  /*!< GPIO Port D Pull-Down Enable Register */
    #define     REG_GPIOD_ICEN      (GPIO_BA+0x0E8)  /*!< GPIO Port D CMOS Input Enable Register */
    #define     REG_GPIOD_ISEN      (GPIO_BA+0x0EC)  /*!< GPIO Port D Schmitt-Trigger Input Enable Register */

    #define     REG_GPIOE_DIR       (GPIO_BA+0x100)  /*!< GPIO port E direction control register */
    #define     REG_GPIOE_DATAOUT   (GPIO_BA+0x104)  /*!< GPIO port E data output register */
    #define     REG_GPIOE_DATAIN    (GPIO_BA+0x108)  /*!< GPIO port E data input register */
    #define     REG_GPIOE_IMD       (GPIO_BA+0x10C)  /*!< GPIO Port E Interrupt Mode Register */
    #define     REG_GPIOE_IREN      (GPIO_BA+0x110)  /*!< GPIO Port E Interrupt Rising-Edge or Level-High Enable Register */
    #define     REG_GPIOE_IFEN      (GPIO_BA+0x114)  /*!< GPIO Port E Interrupt Falling-Edge or Level-Low Enable Register */
    #define     REG_GPIOE_ISR       (GPIO_BA+0x118)  /*!< GPIO Port E Interrupt Status Register */
    #define     REG_GPIOE_DBEN      (GPIO_BA+0x11C)  /*!< GPIO Port E De-bounce Enable Register */
    #define     REG_GPIOE_PUEN      (GPIO_BA+0x120)  /*!< GPIO Port E Pull-Up Enable Register */
    #define     REG_GPIOE_PDEN      (GPIO_BA+0x124)  /*!< GPIO Port E Pull-Down Enable Register */
    #define     REG_GPIOE_ICEN      (GPIO_BA+0x128)  /*!< GPIO Port E CMOS Input Enable Register */
    #define     REG_GPIOE_ISEN      (GPIO_BA+0x12C)  /*!< GPIO Port E Schmitt-Trigger Input Enable Register */

    #define     REG_GPIOF_DIR       (GPIO_BA+0x140)  /*!< GPIO port F direction control register */
    #define     REG_GPIOF_DATAOUT   (GPIO_BA+0x144)  /*!< GPIO port F data output register */
    #define     REG_GPIOF_DATAIN    (GPIO_BA+0x148)  /*!< GPIO port F data input register */
    #define     REG_GPIOF_IMD       (GPIO_BA+0x14C)  /*!< GPIO Port F Interrupt Mode Register */
    #define     REG_GPIOF_IREN      (GPIO_BA+0x150)  /*!< GPIO Port F Interrupt Rising-Edge or Level-High Enable Register */
    #define     REG_GPIOF_IFEN      (GPIO_BA+0x154)  /*!< GPIO Port F Interrupt Falling-Edge or Level-Low Enable Register */
    #define     REG_GPIOF_ISR       (GPIO_BA+0x158)  /*!< GPIO Port F Interrupt Status Register */
    #define     REG_GPIOF_DBEN      (GPIO_BA+0x15C)  /*!< GPIO Port F De-bounce Enable Register */
    #define     REG_GPIOF_PUEN      (GPIO_BA+0x160)  /*!< GPIO Port F Pull-Up Enable Register */
    #define     REG_GPIOF_PDEN      (GPIO_BA+0x164)  /*!< GPIO Port F Pull-Down Enable Register */
    #define     REG_GPIOF_ICEN      (GPIO_BA+0x168)  /*!< GPIO Port F CMOS Input Enable Register */
    #define     REG_GPIOF_ISEN      (GPIO_BA+0x16C)  /*!< GPIO Port F Schmitt-Trigger Input Enable Register */

    #define     REG_GPIOG_DIR       (GPIO_BA+0x180)  /*!< GPIO port G direction control register */
    #define     REG_GPIOG_DATAOUT   (GPIO_BA+0x184)  /*!< GPIO port G data output register */
    #define     REG_GPIOG_DATAIN    (GPIO_BA+0x188)  /*!< GPIO port G data input register */
    #define     REG_GPIOG_IMD       (GPIO_BA+0x18C)  /*!< GPIO Port G Interrupt Mode Register */
    #define     REG_GPIOG_IREN      (GPIO_BA+0x190)  /*!< GPIO Port G Interrupt Rising-Edge or Level-High Enable Register */
    #define     REG_GPIOG_IFEN      (GPIO_BA+0x194)  /*!< GPIO Port G Interrupt Falling-Edge or Level-Low Enable Register */
    #define     REG_GPIOG_ISR       (GPIO_BA+0x198)  /*!< GPIO Port G Interrupt Status Register */
    #define     REG_GPIOG_DBEN      (GPIO_BA+0x19C)  /*!< GPIO Port G De-bounce Enable Register */
    #define     REG_GPIOG_PUEN      (GPIO_BA+0x1A0)  /*!< GPIO Port G Pull-Up Enable Register */
    #define     REG_GPIOG_PDEN      (GPIO_BA+0x1A4)  /*!< GPIO Port G Pull-Down Enable Register */
    #define     REG_GPIOG_ICEN      (GPIO_BA+0x1A8)  /*!< GPIO Port G CMOS Input Enable Register */
    #define     REG_GPIOG_ISEN      (GPIO_BA+0x1AC)  /*!< GPIO Port G Schmitt-Trigger Input Enable Register */

    #define     REG_GPIOH_DIR       (GPIO_BA+0x1C0)  /*!< GPIO port H direction control register */
    #define     REG_GPIOH_DATAOUT   (GPIO_BA+0x1C4)  /*!< GPIO port H data output register */
    #define     REG_GPIOH_DATAIN    (GPIO_BA+0x1C8)  /*!< GPIO port H data input register */
    #define     REG_GPIOH_IMD       (GPIO_BA+0x1CC)  /*!< GPIO Port H Interrupt Mode Register */
    #define     REG_GPIOH_IREN      (GPIO_BA+0x1D0)  /*!< GPIO Port H Interrupt Rising-Edge or Level-High Enable Register */
    #define     REG_GPIOH_IFEN      (GPIO_BA+0x1D4)  /*!< GPIO Port H Interrupt Falling-Edge or Level-Low Enable Register */
    #define     REG_GPIOH_ISR       (GPIO_BA+0x1D8)  /*!< GPIO Port H Interrupt Status Register */
    #define     REG_GPIOH_DBEN      (GPIO_BA+0x1DC)  /*!< GPIO Port H De-bounce Enable Register */
    #define     REG_GPIOH_PUEN      (GPIO_BA+0x1E0)  /*!< GPIO Port H Pull-Up Enable Register */
    #define     REG_GPIOH_PDEN      (GPIO_BA+0x1E4)  /*!< GPIO Port H Pull-Down Enable Register */
    #define     REG_GPIOH_ICEN      (GPIO_BA+0x1E8)  /*!< GPIO Port H CMOS Input Enable Register */
    #define     REG_GPIOH_ISEN      (GPIO_BA+0x1EC)  /*!< GPIO Port H Schmitt-Trigger Input Enable Register */

    #define     REG_GPIOI_DIR       (GPIO_BA+0x200)  /*!< GPIO port I direction control register */
    #define     REG_GPIOI_DATAOUT   (GPIO_BA+0x204)  /*!< GPIO port I data output register */
    #define     REG_GPIOI_DATAIN    (GPIO_BA+0x208)  /*!< GPIO port I data input register */
    #define     REG_GPIOI_IMD       (GPIO_BA+0x20C)  /*!< GPIO Port I Interrupt Mode Register */
    #define     REG_GPIOI_IREN      (GPIO_BA+0x210)  /*!< GPIO Port I Interrupt Rising-Edge or Level-High Enable Register */
    #define     REG_GPIOI_IFEN      (GPIO_BA+0x214)  /*!< GPIO Port I Interrupt Falling-Edge or Level-Low Enable Register */
    #define     REG_GPIOI_ISR       (GPIO_BA+0x218)  /*!< GPIO Port I Interrupt Status Register */
    #define     REG_GPIOI_DBEN      (GPIO_BA+0x21C)  /*!< GPIO Port I De-bounce Enable Register */
    #define     REG_GPIOI_PUEN      (GPIO_BA+0x220)  /*!< GPIO Port I Pull-Up Enable Register */
    #define     REG_GPIOI_PDEN      (GPIO_BA+0x224)  /*!< GPIO Port I Pull-Down Enable Register */
    #define     REG_GPIOI_ICEN      (GPIO_BA+0x228)  /*!< GPIO Port I CMOS Input Enable Register */
    #define     REG_GPIOI_ISEN      (GPIO_BA+0x22C)  /*!< GPIO Port I Schmitt-Trigger Input Enable Register */

    #define     REG_GPIOJ_DIR       (GPIO_BA+0x240)  /*!< GPIO port J direction control register */
    #define     REG_GPIOJ_DATAOUT   (GPIO_BA+0x244)  /*!< GPIO port J data output register */
    #define     REG_GPIOJ_DATAIN    (GPIO_BA+0x248)  /*!< GPIO port J data input register */
    #define     REG_GPIOJ_IMD       (GPIO_BA+0x24C)  /*!< GPIO Port J Interrupt Mode Register */
    #define     REG_GPIOJ_IREN      (GPIO_BA+0x250)  /*!< GPIO Port J Interrupt Rising-Edge or Level-High Enable Register */
    #define     REG_GPIOJ_IFEN      (GPIO_BA+0x254)  /*!< GPIO Port J Interrupt Falling-Edge or Level-Low Enable Register */
    #define     REG_GPIOJ_ISR       (GPIO_BA+0x258)  /*!< GPIO Port J Interrupt Status Register */
    #define     REG_GPIOJ_DBEN      (GPIO_BA+0x25C)  /*!< GPIO Port J De-bounce Enable Register */
    #define     REG_GPIOJ_PUEN      (GPIO_BA+0x260)  /*!< GPIO Port J Pull-Up Enable Register */
    #define     REG_GPIOJ_PDEN      (GPIO_BA+0x264)  /*!< GPIO Port J Pull-Down Enable Register */
    #define     REG_GPIOJ_ICEN      (GPIO_BA+0x268)  /*!< GPIO Port J CMOS Input Enable Register */
    #define     REG_GPIOJ_ISEN      (GPIO_BA+0x26C)  /*!< GPIO Port J Schmitt-Trigger Input Enable Register */

    #define     REG_GPIO_DBNCECON   (GPIO_BA+0x3F0)  /*!< GPIO Debounce Control Register */
    #define     REG_GPIO_ISR        (GPIO_BA+0x3FC)  /*!< GPIO Port Interrupt Status Register */

    /**@}*/ /* end of GPIO register group */


    /*---------------------- Real Time Clock Controller -------------------------*/
    /**
    @addtogroup RTC Real Time Clock Controller(RTC)
    Memory Mapped Structure for RTC Controller
    @{ */

    #define     REG_RTC_INIT    (RTC_BA+0x00)   /*!< RTC Initiation Register */
    #define     REG_RTC_RWEN    (RTC_BA+0x04)   /*!< RTC Access Enable Register */
    #define     REG_RTC_FREQADJ (RTC_BA+0x08)   /*!< RTC Frequency Compensation Register */
    #define     REG_RTC_TIME    (RTC_BA+0x0C)   /*!< Time Loading Register */
    #define     REG_RTC_CAL     (RTC_BA+0x10)   /*!< Calendar Loading Register */
    #define     REG_RTC_TIMEFMT (RTC_BA+0x14)   /*!< Time Format Selection Register */
    #define     REG_RTC_WEEKDAY (RTC_BA+0x18)   /*!< Day of the Week Register */
    #define     REG_RTC_TALM    (RTC_BA+0x1C)   /*!< Time Alarm Register */
    #define     REG_RTC_CALM    (RTC_BA+0x20)   /*!< Calendar Alarm Register */
    #define     REG_RTC_LEAPYEAR    (RTC_BA+0x24)   /*!< Leap year Indicator Register */
    #define     REG_RTC_INTEN   (RTC_BA+0x28)   /*!< RTC Interrupt Enable Register */
    #define     REG_RTC_INTSTS  (RTC_BA+0x2C)   /*!< RTC Interrupt Indicator Register */
    #define     REG_RTC_TICK    (RTC_BA+0x30)   /*!< RTC Time Tick Register */
    #define     REG_RTC_PWRCTL      (RTC_BA+0x34)   /*!< Power Control Register */
    #define     REG_RTC_PWRCNT      (RTC_BA+0x38)   /*!< Power Control Counter Register */
    #define     REG_RTC_SPR0        (RTC_BA+0x40)   /*!< Spare REgistger 0 */
    #define     REG_RTC_SPR1        (RTC_BA+0x44)   /*!< Spare REgistger 1 */
    #define     REG_RTC_SPR2        (RTC_BA+0x48)   /*!< Spare REgistger 2 */
    #define     REG_RTC_SPR3        (RTC_BA+0x4C)   /*!< Spare REgistger 3 */
    #define     REG_RTC_SPR4        (RTC_BA+0x50)   /*!< Spare REgistger 4 */
    #define     REG_RTC_SPR5        (RTC_BA+0x54)   /*!< Spare REgistger 5 */
    #define     REG_RTC_SPR6        (RTC_BA+0x58)   /*!< Spare REgistger 6 */
    #define     REG_RTC_SPR7        (RTC_BA+0x5C)   /*!< Spare REgistger 7 */
    #define     REG_RTC_SPR8        (RTC_BA+0x60)   /*!< Spare REgistger 8 */
    #define     REG_RTC_SPR9        (RTC_BA+0x64)   /*!< Spare REgistger 9 */
    #define     REG_RTC_SPR10       (RTC_BA+0x68)   /*!< Spare REgistger 10 */
    #define     REG_RTC_SPR11       (RTC_BA+0x6C)   /*!< Spare REgistger 11 */
    #define     REG_RTC_SPR12       (RTC_BA+0x70)   /*!< Spare REgistger 12 */
    #define     REG_RTC_SPR13       (RTC_BA+0x74)   /*!< Spare REgistger 13 */
    #define     REG_RTC_SPR14       (RTC_BA+0x78)   /*!< Spare REgistger 14 */
    #define     REG_RTC_SPR15       (RTC_BA+0x7C)   /*!< Spare REgistger 15 */

    /**@}*/ /* end of RTC register group */

    /*---------------------- Inter-IC Bus Controller -------------------------*/
    /**
    @addtogroup I2C Inter-IC Bus Controller(I2C)
    Memory Mapped Structure for I2C Controller
    @{ */

    #define     REG_I2C0_CSR        (I2C0_BA+0x00)  /*!< Control and Status Register */
    #define     REG_I2C0_DIVIDER    (I2C0_BA+0x04)  /*!< Clock Prescale Register */
    #define     REG_I2C0_CMDR       (I2C0_BA+0x08)  /*!< Command Register */
    #define     REG_I2C0_SWR        (I2C0_BA+0x0C)  /*!< Software Mode Control Register */
    #define     REG_I2C0_RXR        (I2C0_BA+0x10)  /*!< Data Receive Register */
    #define     REG_I2C0_TXR        (I2C0_BA+0x14)  /*!< Data Transmit Register */

    #define     REG_I2C1_CSR        (I2C1_BA+0x00)  /*!< Control and Status Register */
    #define     REG_I2C1_DIVIDER    (I2C1_BA+0x04)  /*!< Clock Prescale Register */
    #define     REG_I2C1_CMDR       (I2C1_BA+0x08)  /*!< Command Register */
    #define     REG_I2C1_SWR        (I2C1_BA+0x0C)  /*!< Software Mode Control Register */
    #define     REG_I2C1_RXR        (I2C1_BA+0x10)  /*!< Data Receive Register */
    #define     REG_I2C1_TXR        (I2C1_BA+0x14)  /*!< Data Transmit Register */

    /**@}*/ /* end of I2C register group */


    /*---------------------- Serial Peripheral Interface Controller -------------------------*/
    /**
    @addtogroup SPI Serial Peripheral Interface Controller(SPI)
    Memory Mapped Structure for SPI Controller
    @{ */

    #define     REG_SPI0_CNTRL   (SPI0_BA+0x00)  /*!< Control and Status Register */
    #define     REG_SPI0_DIVIDER (SPI0_BA+0x04)  /*!< Clock Divider Register */
    #define     REG_SPI0_SSR     (SPI0_BA+0x08)  /*!< Slave Select Register */
    #define     REG_SPI0_RX0     (SPI0_BA+0x10)  /*!< Data Receive Register 0 */
    #define     REG_SPI0_RX1     (SPI0_BA+0x14)  /*!< Data Receive Register 1 */
    #define     REG_SPI0_RX2     (SPI0_BA+0x18)  /*!< Data Receive Register 2 */
    #define     REG_SPI0_RX3     (SPI0_BA+0x1C)  /*!< Data Receive Register 3 */
    #define     REG_SPI0_TX0     (SPI0_BA+0x10)  /*!< Data Transmit Register 0 */
    #define     REG_SPI0_TX1     (SPI0_BA+0x14)  /*!< Data Transmit Register 1 */
    #define     REG_SPI0_TX2     (SPI0_BA+0x18)  /*!< Data Transmit Register 2 */
    #define     REG_SPI0_TX3     (SPI0_BA+0x1C)  /*!< Data Transmit Register 3 */

    #define     REG_SPI1_CNTRL   (SPI1_BA+0x00)  /*!< Control and Status Register */
    #define     REG_SPI1_DIVIDER (SPI1_BA+0x04)  /*!< Clock Divider Register */
    #define     REG_SPI1_SSR     (SPI1_BA+0x08)  /*!< Slave Select Register */
    #define     REG_SPI1_RX0     (SPI1_BA+0x10)  /*!< Data Receive Register 0 */
    #define     REG_SPI1_RX1     (SPI1_BA+0x14)  /*!< Data Receive Register 1 */
    #define     REG_SPI1_RX2     (SPI1_BA+0x18)  /*!< Data Receive Register 2 */
    #define     REG_SPI1_RX3     (SPI1_BA+0x1C)  /*!< Data Receive Register 3 */
    #define     REG_SPI1_TX0     (SPI1_BA+0x10)  /*!< Data Transmit Register 0 */
    #define     REG_SPI1_TX1     (SPI1_BA+0x14)  /*!< Data Transmit Register 1 */
    #define     REG_SPI1_TX2     (SPI1_BA+0x18)  /*!< Data Transmit Register 2 */
    #define     REG_SPI1_TX3     (SPI1_BA+0x1C)  /*!< Data Transmit Register 3 */

    /**@}*/ /* end of SPI register group */


    /*---------------------- Pulse Width Modulation Controller -------------------------*/
    /**
    @addtogroup PWM Pulse Width Modulation Controller(PWM)
    Memory Mapped Structure for PWM Controller
    @{ */

    #define     REG_PWM_PPR     (PWM_BA+0x00)  /*!< PWM Pre-scale Register 0 */
    #define     REG_PWM_CSR     (PWM_BA+0x04)  /*!< PWM Clock Select Register */
    #define     REG_PWM_PCR     (PWM_BA+0x08)  /*!< PWM Control Register */
    #define     REG_PWM_CNR0    (PWM_BA+0x0C)  /*!< PWM Counter Register 0 */
    #define     REG_PWM_CMR0    (PWM_BA+0x10)  /*!< PWM Comparator Register 0 */
    #define     REG_PWM_PDR0    (PWM_BA+0x14)  /*!< PWM Data Register 0 */
    #define     REG_PWM_CNR1    (PWM_BA+0x18)  /*!< PWM Counter Register 1 */
    #define     REG_PWM_CMR1    (PWM_BA+0x1C)  /*!< PWM Comparator Register 1 */
    #define     REG_PWM_PDR1    (PWM_BA+0x20)  /*!< PWM Data Register 1 */
    #define     REG_PWM_CNR2    (PWM_BA+0x24)  /*!< PWM Counter Register 2 */
    #define     REG_PWM_CMR2    (PWM_BA+0x28)  /*!< PWM Comparator Register 2 */
    #define     REG_PWM_PDR2    (PWM_BA+0x2C)  /*!< PWM Data Register 2 */
    #define     REG_PWM_CNR3    (PWM_BA+0x30)  /*!< PWM Counter Register 3 */
    #define     REG_PWM_CMR3    (PWM_BA+0x34)  /*!< PWM Comparator Register 3 */
    #define     REG_PWM_PDR3    (PWM_BA+0x38)  /*!< PWM Data Register 3 */
    #define     REG_PWM_PIER    (PWM_BA+0x3C)  /*!< PWM Timer Interrupt Enable Register */
    #define     REG_PWM_PIIR    (PWM_BA+0x40)  /*!< PWM Timer Interrupt Identification Register */

    /**@}*/ /* end of PWM register group */


    /*---------------------- Analog to Digital Converter -------------------------*/
    /**
    @addtogroup ADC Analog to Digital Converter(ADC)
    Memory Mapped Structure for ADC Controller
    @{ */

    #define REG_ADC_CTL       (ADC_BA+0x000) /*!< ADC Contrl */
    #define REG_ADC_CONF      (ADC_BA+0x004) /*!< ADC Configure */
    #define REG_ADC_IER       (ADC_BA+0x008) /*!< ADC Interrupt Enable Register */
    #define REG_ADC_ISR       (ADC_BA+0x00C) /*!< ADC Interrupt Status Register */
    #define REG_ADC_WKISR     (ADC_BA+0x010) /*!< ADC Wake Up Interrupt Status Register */
    #define REG_ADC_XYDATA    (ADC_BA+0x020) /*!< ADC Touch XY Pressure Data */
    #define REG_ADC_ZDATA     (ADC_BA+0x024) /*!< ADC Touch Z Pressure Data */
    #define REG_ADC_DATA      (ADC_BA+0x028) /*!< ADC Normal Conversion Data */
    #define REG_ADC_VBADATA   (ADC_BA+0x02C) /*!< ADC Battery Detection Data */
    #define REG_ADC_KPDATA    (ADC_BA+0x030) /*!< ADC Key Pad Data */
    #define REG_ADC_SELFDATA  (ADC_BA+0x034) /*!< ADC Self-Test Data */
    #define REG_ADC_XYSORT0   (ADC_BA+0x1F4) /*!< ADC Touch XY Position Mean Value Sort 0 */
    #define REG_ADC_XYSORT1   (ADC_BA+0x1F8) /*!< ADC Touch XY Position Mean Value Sort 1 */
    #define REG_ADC_XYSORT2   (ADC_BA+0x1FC) /*!< ADC Touch XY Position Mean Value Sort 2 */
    #define REG_ADC_XYSORT3   (ADC_BA+0x200) /*!< ADC Touch XY Position Mean Value Sort 3 */
    #define REG_ADC_ZSORT0    (ADC_BA+0x204) /*!< ADC Touch Z Pressure Mean Value Sort 0 */
    #define REG_ADC_ZSORT1    (ADC_BA+0x208) /*!< ADC Touch Z Pressure Mean Value Sort 1 */
    #define REG_ADC_ZSORT2    (ADC_BA+0x20C) /*!< ADC Touch Z Pressure Mean Value Sort 2 */
    #define REG_ADC_ZSORT3    (ADC_BA+0x210) /*!< ADC Touch Z Pressure Mean Value Sort 3 */
    #define REG_ADC_MTMULCK   (ADC_BA+0x220) /*!< ADC Manual Test Mode Unlock */
    #define REG_ADC_MTCONF    (ADC_BA+0x224) /*!< ADC Manual Test Mode Configure */
    #define REG_ADC_MTCON     (ADC_BA+0x228) /*!< ADC Manual Test Mode Control */
    #define REG_ADC_ADCAII    (ADC_BA+0x22C) /*!< ADC Analog Interface Information */
    #define REG_ADC_ADCAIIRLT (ADC_BA+0x230) /*!< ADC Analog Interface Information Result */

    /**@}*/ /* end of ADC register group */

    /*------------------ Capture Sensor Interface Controller ---------------------*/
    /**
    @addtogroup CAP Capture Sensor Interface Controller(CAP)
    Memory Mapped Structure for CAP Controller
    @{ */

    #define REG_CAP_CTL            (CAP_BA+0x000)  /*!< Image Capture Interface Control Register */
    #define REG_CAP_PAR            (CAP_BA+0x004)  /*!< Image Capture Interface Parameter Register */
    #define REG_CAP_INT            (CAP_BA+0x008)  /*!< Image Capture Interface Interrupt Registe */
    #define REG_CAP_POSTERIZE      (CAP_BA+0x00C)  /*!< YUV Component Posterizing Factor Register */
    #define REG_CAP_MD             (CAP_BA+0x010)  /*!< Motion Detection Register */
    #define REG_CAP_MDADDR         (CAP_BA+0x014)  /*!< Motion Detection Output Address Register */
    #define REG_CAP_MDYADDR        (CAP_BA+0x018)  /*!< Motion Detection Temp YOutput Address Register */
    #define REG_CAP_SEPIA          (CAP_BA+0x01C)  /*!< Sepia Effect Control Register */
    #define REG_CAP_CWSP           (CAP_BA+0x020)  /*!< Cropping Window Starting Address Register */
    #define REG_CAP_CWS            (CAP_BA+0x024)  /*!< Cropping Window Size Register */
    #define REG_CAP_PKTSL          (CAP_BA+0x028)  /*!< Packet Scaling Vertical/Horizontal Factor Register (LSB) */
    #define REG_CAP_PLNSL          (CAP_BA+0x02C)  /*!< Planar Scaling Vertical/Horizontal Factor Register (LSB) */
    #define REG_CAP_FRCTL          (CAP_BA+0x030)  /*!< Scaling Frame Rate Factor Register */
    #define REG_CAP_STRIDE         (CAP_BA+0x034)  /*!< Frame Output Pixel Stride Register */
    #define REG_CAP_FIFOTH         (CAP_BA+0x03C)  /*!< FIFO threshold Register */
    #define REG_CAP_CMPADDR        (CAP_BA+0x040)  /*!< Compare Packet Memory Base Address Register */
    #define REG_CAP_PKTSM          (CAP_BA+0x048)  /*!< Packet Scaling Vertical/Horizontal Factor Register (MSB) */
    #define REG_CAP_PLNSM          (CAP_BA+0x04C)  /*!< Planar Scaling Vertical/Horizontal Factor Register (MSB) */
    #define REG_CAP_CURADDRP       (CAP_BA+0x050)  /*!< Current Packet System Memory Address Register */
    #define REG_CAP_CURADDRY       (CAP_BA+0x054)  /*!< Current Planar Y System Memory Address Register */
    #define REG_CAP_CURADDRU       (CAP_BA+0x058)  /*!< Current Planar U System Memory Address Register */
    #define REG_CAP_CURADDRV       (CAP_BA+0x05C)  /*!< Current Planar V System Memory Address Register */
    #define REG_CAP_PKTBA0         (CAP_BA+0x060)  /*!< System Memory Packet Base Address Register */
    #define REG_CAP_PKTBA1         (CAP_BA+0x064)  /*!< System Memory Packet Base Address Register */
    #define REG_CAP_YBA            (CAP_BA+0x080)  /*!< System Memory Planar Y Base Address Register */
    #define REG_CAP_UBA            (CAP_BA+0x084)  /*!< System Memory Planar U Base Address Register */
    #define REG_CAP_VBA            (CAP_BA+0x088)  /*!< System Memory Planar V Base Address Register */

    /**@}*/ /* end of CAP register group */

    /*------------------ SDRAM Interface Controller ---------------------*/
    /**
    @addtogroup SDIC SDRAM Interface Controller(SDIC)
    Memory Mapped Structure for SDIC Controller
    @{ */

    #define REG_SDIC_OPMCTL     (SDIC_BA+0x000)    /*!< SDRAM Controller Operation Mode Control Register */
    #define REG_SDIC_CMD        (SDIC_BA+0x004)    /*!< SDRAM Command Register */
    #define REG_SDIC_REFCTL     (SDIC_BA+0x008)    /*!< SDRAM Controller Refresh Control Register */
    #define REG_SDIC_SIZE0      (SDIC_BA+0x010)    /*!< SDRAM 0 Size Register */
    #define REG_SDIC_SIZE1      (SDIC_BA+0x014)    /*!< SDRAM 1 Size Register */
    #define REG_SDIC_MR         (SDIC_BA+0x018)    /*!< SDRAM Mode Register */
    #define REG_SDIC_EMR        (SDIC_BA+0x01C)    /*!< SDRAM Extended Mode Register */
    #define REG_SDIC_EMR2       (SDIC_BA+0x020)    /*!< SDRAM Extended Mode Register 2 */
    #define REG_SDIC_EMR3       (SDIC_BA+0x024)    /*!< SDRAM Extended Mode Register 3 */
    #define REG_SDIC_TIME       (SDIC_BA+0x028)    /*!< SDRAM Timing Control Register */
    #define REG_SDIC_DQSODS     (SDIC_BA+0x030)    /*!< DQS Output Delay Selection Register */
    #define REG_SDIC_CKDQSDS    (SDIC_BA+0x034)    /*!< Clock and DQS Delay Selection Register */
    #define REG_SDIC_DAENSEL    (SDIC_BA+0x038)    /*!< Data Latch Enable Selection Register */

    /**@}*/ /* end of SDIC register group */

    /*---------------------- Controller Area Network -------------------------*/
    /**
    @addtogroup CAN Controller Area Network(CAN)
    Memory Mapped Structure for CAN Controller
    @{ */

    #define REG_CAN0_CON       (CAN0_BA+0x00) /*!< Control Register */
    #define REG_CAN0_STATUS    (CAN0_BA+0x04) /*!< Status Register */
    #define REG_CAN0_ERR       (CAN0_BA+0x08) /*!< Error Counter Register */
    #define REG_CAN0_BTIME     (CAN0_BA+0x0C) /*!< Bit Time Register */
    #define REG_CAN0_IIDR      (CAN0_BA+0x10) /*!< Interrupt Identifier Register */
    #define REG_CAN0_TEST      (CAN0_BA+0x14) /*!< Test Register */
    #define REG_CAN0_BRPE      (CAN0_BA+0x18) /*!< BRP Extension Register */
    #define REG_CAN0_IF1_CREQ  (CAN0_BA+0x20) /*!< IF1 Command Request Register */
    #define REG_CAN0_IF2_CREQ  (CAN0_BA+0x80) /*!< IF2 Command Request Register */
    #define REG_CAN0_IF1_CMASK (CAN0_BA+0x24) /*!< IF1 Command Mask Register */
    #define REG_CAN0_IF2_CMASK (CAN0_BA+0x84) /*!< IF2 Command Mask Register */
    #define REG_CAN0_IF1_MASK1 (CAN0_BA+0x28) /*!< IF1 Msak 1 Register */
    #define REG_CNA0_IF2_MASK1 (CAN0_BA+0x88) /*!< IF2 Mask 1 Register */
    #define REG_CAN0_IF1_MASK2 (CAN0_BA+0x2C) /*!< IF1 Mask 2 Register */
    #define REG_CAN0_IF2_MASK2 (CAN0_BA+0x8C) /*!< IF2 Mask 2 REgister */
    #define REG_CAN0_IF1_ARB1  (CAN0_BA+0x30) /*!< IF1 Arbitration 1 Register */
    #define REG_CAN0_IF2_ARB1  (CAN0_BA+0x90) /*!< IF2 Arbitration 1 Register */
    #define REG_CAN0_IF1_ARB2  (CAN0_BA+0x34) /*!< IF1 Arbitration 2 Register */
    #define REG_CAN0_IF2_ARB2  (CAN0_BA+0x94) /*!< IF2 Arbitration 2 Register */
    #define REG_CAN0_IF1_MCON  (CAN0_BA+0x38) /*!< IF1 Message Control Register */
    #define REG_CAN0_IF2_MCON  (CAN0_BA+0x98) /*!< IF2 Message Control Register */
    #define REG_CAN0_IF1_DAT_A1 (CAN0_BA+0x3C) /*!< IF1 Data A1 Register */
    #define REG_CAN0_IF1_DAT_A2 (CAN0_BA+0x40) /*!< IF1 Data A2 Register */
    #define REG_CAN0_IF1_DAT_B1 (CAN0_BA+0x44) /*!< IF1 Data B1 Register */
    #define REG_CAN0_IF1_DAT_B2 (CAN0_BA+0x48) /*!< IF1 Data B2 Register */
    #define REG_CAN0_IF2_DAT_A1 (CAN0_BA+0x9C) /*!< IF2 Data A1 Register */
    #define REG_CAN0_IF2_DAT_A2 (CAN0_BA+0xA0) /*!< IF2 Data A2 Register */
    #define REG_CAN0_IF2_DAT_B1 (CAN0_BA+0xA4) /*!< IF2 Data B1 Register */
    #define REG_CAN0_IF2_DAT_B2 (CAN0_BA+0xA8) /*!< IF2 Data B2 Register */
    #define REG_CAN0_TXREQ1     (CAN0_BA+0x100) /*!< Transmission Request Register 1 */
    #define REG_CAN0_TXREQ2     (CAN0_BA+0x104) /*!< Transmission Request Register 2 */
    #define REG_CAN0_NDAT1      (CAN0_BA+0x120) /*!< New Data Register 1 */
    #define REG_CAN0_NDAT2      (CAN0_BA+0x124) /*!< New Data Register 2 */
    #define REG_CAN0_IPND1      (CAN0_BA+0x140) /*!< Interrupt Pending Register 1 */
    #define REG_CAN0_IPND2      (CAN0_BA+0x142) /*!< Interrupt Pending Register 2 */
    #define REG_CAN0_MVLD1      (CAN0_BA+0x160) /*!< Message Valid Register 1 */
    #define REG_CAN0_MVLD2      (CAN0_BA+0x164) /*!< Message Valid Register 2 */
    #define REG_CAN0_WU_EN      (CAN0_BA+0x168) /*!< Wake-up Function Enable */
    #define REG_CAN0_WU_STATUS  (CAN0_BA+0x16C) /*!< Wake-up Function Status */

    #define REG_CAN1_CON       (CAN1_BA+0x00) /*!< Control Register */
    #define REG_CAN1_STATUS    (CAN1_BA+0x04) /*!< Status Register */
    #define REG_CAN1_ERR       (CAN1_BA+0x08) /*!< Error Counter Register */
    #define REG_CAN1_BTIME     (CAN1_BA+0x0C) /*!< Bit Time Register */
    #define REG_CAN1_IIDR      (CAN1_BA+0x10) /*!< Interrupt Identifier Register */
    #define REG_CAN1_TEST      (CAN1_BA+0x14) /*!< Test Register */
    #define REG_CAN1_BRPE      (CAN1_BA+0x18) /*!< BRP Extension Register */
    #define REG_CAN1_IF1_CREQ  (CAN1_BA+0x20) /*!< IF1 Command Request Register */
    #define REG_CAN1_IF2_CREQ  (CAN1_BA+0x80) /*!< IF2 Command Request Register */
    #define REG_CAN1_IF1_CMASK (CAN1_BA+0x24) /*!< IF1 Command Mask Register */
    #define REG_CAN1_IF2_CMASK (CAN1_BA+0x84) /*!< IF2 Command Mask Register */
    #define REG_CAN1_IF1_MASK1 (CAN1_BA+0x28) /*!< IF1 Msak 1 Register */
    #define REG_CNA1_IF2_MASK1 (CAN1_BA+0x88) /*!< IF2 Mask 1 Register */
    #define REG_CAN1_IF1_MASK2 (CAN1_BA+0x2C) /*!< IF1 Mask 2 Register */
    #define REG_CAN1_IF2_MASK2 (CAN1_BA+0x8C) /*!< IF2 Mask 2 REgister */
    #define REG_CAN1_IF1_ARB1  (CAN1_BA+0x30) /*!< IF1 Arbitration 1 Register */
    #define REG_CAN1_IF2_ARB1  (CAN1_BA+0x90) /*!< IF2 Arbitration 1 Register */
    #define REG_CAN1_IF1_ARB2  (CAN1_BA+0x34) /*!< IF1 Arbitration 2 Register */
    #define REG_CAN1_IF2_ARB2  (CAN1_BA+0x94) /*!< IF2 Arbitration 2 Register */
    #define REG_CAN1_IF1_MCON  (CAN1_BA+0x38) /*!< IF1 Message Control Register */
    #define REG_CAN1_IF2_MCON  (CAN1_BA+0x98) /*!< IF2 Message Control Register */
    #define REG_CAN1_IF1_DAT_A1 (CAN1_BA+0x3C) /*!< IF1 Data A1 Register */
    #define REG_CAN1_IF1_DAT_A2 (CAN1_BA+0x40) /*!< IF1 Data A2 Register */
    #define REG_CAN1_IF1_DAT_B1 (CAN1_BA+0x44) /*!< IF1 Data B1 Register */
    #define REG_CAN1_IF1_DAT_B2 (CAN1_BA+0x48) /*!< IF1 Data B2 Register */
    #define REG_CAN1_IF2_DAT_A1 (CAN1_BA+0x9C) /*!< IF2 Data A1 Register */
    #define REG_CAN1_IF2_DAT_A2 (CAN1_BA+0xA0) /*!< IF2 Data A2 Register */
    #define REG_CAN1_IF2_DAT_B1 (CAN1_BA+0xA4) /*!< IF2 Data B1 Register */
    #define REG_CAN1_IF2_DAT_B2 (CAN1_BA+0xA8) /*!< IF2 Data B2 Register */
    #define REG_CAN1_TXREQ1     (CAN1_BA+0x100) /*!< Transmission Request Register 1 */
    #define REG_CAN1_TXREQ2     (CAN1_BA+0x104) /*!< Transmission Request Register 2 */
    #define REG_CAN1_NDAT1      (CAN1_BA+0x120) /*!< New Data Register 1 */
    #define REG_CAN1_NDAT2      (CAN1_BA+0x124) /*!< New Data Register 2 */
    #define REG_CAN1_IPND1      (CAN1_BA+0x140) /*!< Interrupt Pending Register 1 */
    #define REG_CAN1_IPND2      (CAN1_BA+0x142) /*!< Interrupt Pending Register 2 */
    #define REG_CAN1_MVLD1      (CAN1_BA+0x160) /*!< Message Valid Register 1 */
    #define REG_CAN1_MVLD2      (CAN1_BA+0x164) /*!< Message Valid Register 2 */
    #define REG_CAN1_WU_EN      (CAN1_BA+0x168) /*!< Wake-up Function Enable */
    #define REG_CAN1_WU_STATUS  (CAN1_BA+0x16C) /*!< Wake-up Function Status */

    /**@}*/ /* end of CAN register group */


    /*------------------- Multi-Time Programmable Controller --------------------*/
    /**
    @addtogroup MTP Multi-Time Programmable Controller (MTP)
    Memory Mapped Structure for MTP Controller
    @{ */

    #define     MTP_KEYEN           (MTP_BA+0x000)   /*!< MTP Key Enable Register                       */
    #define     MTP_USERDATA        (MTP_BA+0x00C)   /*!< MTP User Defined Data Register                */
    #define     MTP_KEY0            (MTP_BA+0x010)   /*!< MTP KEY 0 Register                            */
    #define     MTP_KEY1            (MTP_BA+0x014)   /*!< MTP KEY 1 Register                            */
    #define     MTP_KEY2            (MTP_BA+0x018)   /*!< MTP KEY 2 Register                            */
    #define     MTP_KEY3            (MTP_BA+0x01C)   /*!< MTP KEY 3 Register                            */
    #define     MTP_KEY4            (MTP_BA+0x020)   /*!< MTP KEY 4 Register                            */
    #define     MTP_KEY5            (MTP_BA+0x024)   /*!< MTP KEY 5 Register                            */
    #define     MTP_KEY6            (MTP_BA+0x028)   /*!< MTP KEY 6 Register                            */
    #define     MTP_KEY7            (MTP_BA+0x02C)   /*!< MTP KEY 7 Register                            */
    #define     MTP_PCYCLE          (MTP_BA+0x030)   /*!< MTP Program Cycle Program Count Register      */
    #define     MTP_CTL             (MTP_BA+0x034)   /*!< MTP Control Register                          */
    #define     MTP_PSTART          (MTP_BA+0x038)   /*!< MTP Program Start Registe                     */
    #define     MTP_STATUS          (MTP_BA+0x040)   /*!< MTP Status Registe                            */
    #define     MTP_REGLCTL         (MTP_BA+0x050)   /*!< MTP Register Write-Protection Control Register*/

    /**@}*/ /* end of MTP register group */


    /*------------------- JPEG Controller --------------------*/
    /**
    @addtogroup JPEG JPEG Controller (JPEG)
    Memory Mapped Structure for JPEG Controller
    @{ */
    #define JMCR           (JPEG_BA+0x00)           /*!< JPEG Mode Control Register  */
    #define JHEADER        (JPEG_BA+0x04)           /*!< JPEG Encode Header Control Register  */
    #define JITCR          (JPEG_BA+0x08)           /*!< JPEG Image Type Control Register  */
    #define JPRIQC         (JPEG_BA+0x10)           /*!< JPEG Primary Q-Table Control Register  */
    #define JTHBQC         (JPEG_BA+0x14)           /*!< JPEG Thumbnail Q-Table Control Register  */
    #define JPRIWH         (JPEG_BA+0x18)           /*!< JPEG Encode Primary Width/Height Register  */
    #define JTHBWH         (JPEG_BA+0x1C)           /*!< JPEG Encode Thumbnail Width/Height Register  */
    #define JPRST          (JPEG_BA+0x20)           /*!< JPEG Encode Primary Restart Interval Register  */
    #define JTRST          (JPEG_BA+0x24)           /*!< JPEG Encode Thumbnail Restart Interval  */
    #define JDECWH         (JPEG_BA+0x28)           /*!< JPEG Decode Image Width/Height Register  */
    #define JINTCR         (JPEG_BA+0x2C)           /*!< JPEG Interrupt Control and Status Register  */
    #define JDOWFBS        (JPEG_BA+0x3c)           /*!< JPEG Decoding Output Wait Frame Buffer Size  */
    #define JPEG_BSBAD     (JPEG_BA+0x40)           /*!< JPEG Test Control Register  */
    #define JWINDEC0       (JPEG_BA+0x44)           /*!< JPEG Window Decode Mode Control Register 0  */
    #define JWINDEC1       (JPEG_BA+0x48)           /*!< JPEG Window Decode Mode Control Register 1  */
    #define JWINDEC2       (JPEG_BA+0x4C)           /*!< JPEG Window Decode Mode Control Register 2  */
    #define JMACR          (JPEG_BA+0x50)           /*!< JPEG Memory Address Mode Control Register  */
    #define JPSCALU        (JPEG_BA+0x54)           /*!< JPEG Primary Scaling-Up Control Register  */
    #define JPSCALD        (JPEG_BA+0x58)           /*!< JPEG Primary Scaling-Down Control Register  */
    #define JTSCALD        (JPEG_BA+0x5C)           /*!< JPEG Thumbnail  Scaling-Down Control Register  */
    #define JDBCR          (JPEG_BA+0x60)           /*!< JPEG Dual-Buffer Control Register  */
    #define JRESERVE       (JPEG_BA+0x70)           /*!< JPEG Encode Primary Bit-stream Reserved Size Register  */
    #define JOFFSET        (JPEG_BA+0x74)           /*!< JPEG Offset Between Primary & Thumbnail Register  */
    #define JFSTRIDE       (JPEG_BA+0x78)           /*!< JPEG Encode Bit-stream Frame Stride Register  */
    #define JYADDR0        (JPEG_BA+0x7C)           /*!< JPEG Y Component Frame Buffer-0 Starting Address Register  */
    #define JUADDR0        (JPEG_BA+0x80)           /*!< JPEG U Component Frame Buffer-0 Starting Address Register  */
    #define JVADDR0        (JPEG_BA+0x84)           /*!< JPEG V Component Frame Buffer-0 Starting Address Register  */
    #define JYADDR1        (JPEG_BA+0x88)           /*!< JPEG Y Component Frame Buffer-1 Starting Address Register  */
    #define JUADDR1        (JPEG_BA+0x8C)           /*!< JPEG U Component Frame Buffer-1 Starting Address Register  */
    #define JVADDR1        (JPEG_BA+0x90)           /*!< JPEG V Component Frame Buffer-1 Starting Address Register  */
    #define JYSTRIDE       (JPEG_BA+0x94)           /*!< JPEG Y Component Frame Buffer Stride Register  */
    #define JUSTRIDE       (JPEG_BA+0x98)           /*!< JPEG U Component Frame Buffer Stride Register  */
    #define JVSTRIDE       (JPEG_BA+0x9C)           /*!< JPEG V Component Frame Buffer Stride Register  */
    #define JIOADDR0       (JPEG_BA+0xA0)           /*!< JPEG Bit-stream Frame Buffer-0 Starting Address Register  */
    #define JIOADDR1       (JPEG_BA+0xA4)           /*!< JPEG Bit-stream Frame Buffer-1 Starting Address Register  */
    #define JPRI_SIZE      (JPEG_BA+0xA8)           /*!< JPEG Encode Primary Image Bit-stream Size Register  */
    #define JTHB_SIZE      (JPEG_BA+0xAC)           /*!< JPEG Encode Thumbnail Image Bit-stream Size Register  */
    #define JUPRAT         (JPEG_BA+0xB0)           /*!< JPEG Encode Up-Scale Ratio Register  */
    #define JBSFIFO        (JPEG_BA+0xB4)           /*!< JPEG Bit-stream FIFO Control Register  */
    #define JSRCH          (JPEG_BA+0xB8)           /*!< JPEG Encode Source Image Height  */
    #define JQTAB0         (JPEG_BA+0x100)          /*!< JPEG Quantization-Table 0 Register  */
    #define JQTAB1         (JPEG_BA+0x140)          /*!< JPEG Quantization-Table 1 Register  */
    #define JQTAB2         (JPEG_BA+0x180)          /*!< JPEG Quantization-Table 2 Register  */

    /**@}*/ /* end of JPEG register group */



    /*@}*/ /* end of group N9H30_Peripherals */


    /** @addtogroup N9H30_IO_ROUTINE N9H30 I/O Routines
    The Declaration of N9H30 I/O Routines
    @{
    */

    typedef volatile unsigned char  vu8;        ///< Define 8-bit unsigned volatile data type
    typedef volatile unsigned short vu16;       ///< Define 16-bit unsigned volatile data type
    typedef volatile unsigned long  vu32;       ///< Define 32-bit unsigned volatile data type

    /**
    * @brief Get a 8-bit unsigned value from specified address
    * @param[in] addr Address to get 8-bit data from
    * @return  8-bit unsigned value stored in specified address
    */
    #define M8(addr)  (*((vu8  *) (addr)))

    /**
    * @brief Get a 16-bit unsigned value from specified address
    * @param[in] addr Address to get 16-bit data from
    * @return  16-bit unsigned value stored in specified address
    * @note The input address must be 16-bit aligned
    */
    #define M16(addr) (*((vu16 *) (addr)))

    /**
    * @brief Get a 32-bit unsigned value from specified address
    * @param[in] addr Address to get 32-bit data from
    * @return  32-bit unsigned value stored in specified address
    * @note The input address must be 32-bit aligned
    */
    #define M32(addr) (*((vu32 *) (addr)))

    /**
    * @brief Set a 32-bit unsigned value to specified I/O port
    * @param[in] port Port address to set 32-bit data
    * @param[in] value Value to write to I/O port
    * @return  None
    * @note The output port must be 32-bit aligned
    */
    #define outpw(port,value)     *((volatile unsigned int *)(port)) = value

    /**
    * @brief Get a 32-bit unsigned value from specified I/O port
    * @param[in] port Port address to get 32-bit data from
    * @return  32-bit unsigned value stored in specified I/O port
    * @note The input port must be 32-bit aligned
    */
    #define inpw(port)            (*((volatile unsigned int *)(port)))

    /**
    * @brief Set a 16-bit unsigned value to specified I/O port
    * @param[in] port Port address to set 16-bit data
    * @param[in] value Value to write to I/O port
    * @return  None
    * @note The output port must be 16-bit aligned
    */
    #define outps(port,value)     *((volatile unsigned short *)(port)) = value

    /**
    * @brief Get a 16-bit unsigned value from specified I/O port
    * @param[in] port Port address to get 16-bit data from
    * @return  16-bit unsigned value stored in specified I/O port
    * @note The input port must be 16-bit aligned
    */
    #define inps(port)            (*((volatile unsigned short *)(port)))

    /**
    * @brief Set a 8-bit unsigned value to specified I/O port
    * @param[in] port Port address to set 8-bit data
    * @param[in] value Value to write to I/O port
    * @return  None
    */
    #define outpb(port,value)     *((volatile unsigned char *)(port)) = value

    /**
    * @brief Get a 8-bit unsigned value from specified I/O port
    * @param[in] port Port address to get 8-bit data from
    * @return  8-bit unsigned value stored in specified I/O port
    */
    #define inpb(port)            (*((volatile unsigned char *)(port)))

    /**
    * @brief Set a 32-bit unsigned value to specified I/O port
    * @param[in] port Port address to set 32-bit data
    * @param[in] value Value to write to I/O port
    * @return  None
    * @note The output port must be 32-bit aligned
    */
    #define outp32(port,value)    *((volatile unsigned int *)(port)) = value

    /**
    * @brief Get a 32-bit unsigned value from specified I/O port
    * @param[in] port Port address to get 32-bit data from
    * @return  32-bit unsigned value stored in specified I/O port
    * @note The input port must be 32-bit aligned
    */
    #define inp32(port)           (*((volatile unsigned int *)(port)))

    /**
    * @brief Set a 16-bit unsigned value to specified I/O port
    * @param[in] port Port address to set 16-bit data
    * @param[in] value Value to write to I/O port
    * @return  None
    * @note The output port must be 16-bit aligned
    */
    #define outp16(port,value)    *((volatile unsigned short *)(port)) = value

    /**
    * @brief Get a 16-bit unsigned value from specified I/O port
    * @param[in] port Port address to get 16-bit data from
    * @return  16-bit unsigned value stored in specified I/O port
    * @note The input port must be 16-bit aligned
    */
    #define inp16(port)           (*((volatile unsigned short *)(port)))

    /**
    * @brief Set a 8-bit unsigned value to specified I/O port
    * @param[in] port Port address to set 8-bit data
    * @param[in] value Value to write to I/O port
    * @return  None
    */
    #define outp8(port,value)     *((volatile unsigned char *)(port)) = value

    /**
    * @brief Get a 8-bit unsigned value from specified I/O port
    * @param[in] port Port address to get 8-bit data from
    * @return  8-bit unsigned value stored in specified I/O port
    */
    #define inp8(port)            (*((volatile unsigned char *)(port)))


    /*@}*/ /* end of group N9H30_IO_ROUTINE */

    /******************************************************************************/
    /*                Legacy Constants                                            */
    /******************************************************************************/
    /** @addtogroup N9H30_legacy_Constants N9H30 Legacy Constants
    N9H30 Legacy Constants
    @{
    */
    typedef void             *PVOID;    ///< Define void pointer data type
    typedef void              VOID;     ///< Define void data type
    typedef char              BOOL;     ///< Define bool data type
    typedef char             *PBOOL;    ///< Define bool pointer data type

    typedef char              INT8;     ///< Define 8-bit singed data type
    typedef char              CHAR;     ///< Define char data type
    typedef char             *PINT8;    ///< Define 8-bit singed pointer data type
    typedef char             *PCHAR;    ///< Define char pointer data type
    typedef unsigned char     UINT8;    ///< Define 8-bit unsigned data type
    typedef unsigned char     UCHAR;    ///< Define char unsigned data type
    typedef unsigned char    *PUINT8;   ///< Define 8-bit unsigned pointer data type
    typedef unsigned char    *PUCHAR;   ///< Define char unsigned pointer data type
    typedef char             *PSTR;     ///< Define string pointer data type
    typedef const char       *PCSTR;    ///< Define constant string pointer data type

    typedef short             SHORT;    ///< Define short signed data type
    typedef short            *PSHORT;   ///< Define short signed pointer data type
    typedef unsigned short    USHORT;   ///< Define short unsigned data type
    typedef unsigned short   *PUSHORT;  ///< Define short unsigned pointer data type

    typedef short             INT16;    ///< Define 16-bit signed data type
    typedef short            *PINT16;   ///< Define 16-bit signed pointer data type
    typedef unsigned short    UINT16;   ///< Define 16-bit unsigned data type
    typedef unsigned short   *PUINT16;  ///< Define 16-bit unsigned pointer data type

    typedef int               INT;      ///< Define integer signed data type
    typedef int              *PINT;     ///< Define integer signed pointer data type
    typedef unsigned int      UINT;     ///< Define integer unsigned data type
    typedef unsigned int     *PUINT;    ///< Define integer unsigned pointer data type

    typedef int               INT32;    ///< Define 32-bit signed data type
    typedef int              *PINT32;   ///< Define 32-bit signed pointer data type
    typedef unsigned int      UINT32;   ///< Define 32-bit unsigned data type
    typedef unsigned int     *PUINT32;  ///< Define 32-bit unsigned pointer data type

    #if defined ( __GNUC__ ) && !(__CC_ARM)
        typedef long long           INT64;
        typedef unsigned long long  UINT64;
    #else
        typedef __int64           INT64;    ///< Define 64-bit signed data type
        typedef unsigned __int64  UINT64;   ///< Define 64-bit unsigned data type
    #endif

    typedef float             FLOAT;    ///< Define float data type
    typedef float            *PFLOAT;   ///< Define float pointer data type

    typedef double            DOUBLE;   ///< Define double data type
    typedef double           *PDOUBLE;  ///< Define double pointer data type

    typedef int               SIZE_T;   ///< Define size of data type

    typedef unsigned char     REG8;     ///< Define 8-bit register data type
    typedef unsigned short    REG16;    ///< Define 16-bit register data type
    typedef unsigned int      REG32;    ///< Define 32-bit register data type


    #ifndef NULL
        #define NULL           (0)      ///< NULL pointer
    #endif

    #define TRUE           (1)      ///< Boolean true, define to use in API parameters or return value
    #define FALSE          (0)      ///< Boolean false, define to use in API parameters or return value

    #define ENABLE         (1)      ///< Enable, define to use in API parameters
    #define DISABLE        (0)      ///< Disable, define to use in API parameters


    #define   Successful  0         ///< Function return value success
    #define   Fail        1         ///< Function return value failed

    /* Define one bit mask */
    #define BIT0     (0x00000001)       ///< Bit 0 mask of an 32 bit integer
    #define BIT1     (0x00000002)       ///< Bit 1 mask of an 32 bit integer
    #define BIT2     (0x00000004)       ///< Bit 2 mask of an 32 bit integer
    #define BIT3     (0x00000008)       ///< Bit 3 mask of an 32 bit integer
    #define BIT4     (0x00000010)       ///< Bit 4 mask of an 32 bit integer
    #define BIT5     (0x00000020)       ///< Bit 5 mask of an 32 bit integer
    #define BIT6     (0x00000040)       ///< Bit 6 mask of an 32 bit integer
    #define BIT7     (0x00000080)       ///< Bit 7 mask of an 32 bit integer
    #define BIT8     (0x00000100)       ///< Bit 8 mask of an 32 bit integer
    #define BIT9     (0x00000200)       ///< Bit 9 mask of an 32 bit integer
    #define BIT10    (0x00000400)       ///< Bit 10 mask of an 32 bit integer
    #define BIT11    (0x00000800)       ///< Bit 11 mask of an 32 bit integer
    #define BIT12    (0x00001000)       ///< Bit 12 mask of an 32 bit integer
    #define BIT13    (0x00002000)       ///< Bit 13 mask of an 32 bit integer
    #define BIT14    (0x00004000)       ///< Bit 14 mask of an 32 bit integer
    #define BIT15    (0x00008000)       ///< Bit 15 mask of an 32 bit integer
    #define BIT16    (0x00010000)       ///< Bit 16 mask of an 32 bit integer
    #define BIT17    (0x00020000)       ///< Bit 17 mask of an 32 bit integer
    #define BIT18    (0x00040000)       ///< Bit 18 mask of an 32 bit integer
    #define BIT19    (0x00080000)       ///< Bit 19 mask of an 32 bit integer
    #define BIT20    (0x00100000)       ///< Bit 20 mask of an 32 bit integer
    #define BIT21    (0x00200000)       ///< Bit 21 mask of an 32 bit integer
    #define BIT22    (0x00400000)       ///< Bit 22 mask of an 32 bit integer
    #define BIT23    (0x00800000)       ///< Bit 23 mask of an 32 bit integer
    #define BIT24    (0x01000000)       ///< Bit 24 mask of an 32 bit integer
    #define BIT25    (0x02000000)       ///< Bit 25 mask of an 32 bit integer
    #define BIT26    (0x04000000)       ///< Bit 26 mask of an 32 bit integer
    #define BIT27    (0x08000000)       ///< Bit 27 mask of an 32 bit integer
    #define BIT28    (0x10000000)       ///< Bit 28 mask of an 32 bit integer
    #define BIT29    (0x20000000)       ///< Bit 29 mask of an 32 bit integer
    #define BIT30    (0x40000000)       ///< Bit 30 mask of an 32 bit integer
    #define BIT31    (0x80000000)       ///< Bit 31 mask of an 32 bit integer

    /* Byte Mask Definitions */
    #define BYTE0_Msk              (0x000000FF)         ///< Mask to get bit0~bit7 from a 32 bit integer
    #define BYTE1_Msk              (0x0000FF00)         ///< Mask to get bit8~bit15 from a 32 bit integer
    #define BYTE2_Msk              (0x00FF0000)         ///< Mask to get bit16~bit23 from a 32 bit integer
    #define BYTE3_Msk              (0xFF000000)         ///< Mask to get bit24~bit31 from a 32 bit integer

    #define GET_BYTE0(u32Param)    ((u32Param & BYTE0_Msk)      )  /*!< Extract Byte 0 (Bit  0~ 7) from parameter u32Param */
    #define GET_BYTE1(u32Param)    ((u32Param & BYTE1_Msk) >>  8)  /*!< Extract Byte 1 (Bit  8~15) from parameter u32Param */
    #define GET_BYTE2(u32Param)    ((u32Param & BYTE2_Msk) >> 16)  /*!< Extract Byte 2 (Bit 16~23) from parameter u32Param */
    #define GET_BYTE3(u32Param)    ((u32Param & BYTE3_Msk) >> 24)  /*!< Extract Byte 3 (Bit 24~31) from parameter u32Param */

    #ifdef __cplusplus
        #define   __I     volatile             /*!< Defines 'read only' permissions                 */
    #else
        #define   __I     volatile const       /*!< Defines 'read only' permissions                 */
    #endif
    #define     __O     volatile             /*!< Defines 'write only' permissions                */
    #define     __IO    volatile             /*!< Defines 'read / write' permissions              */

    extern void __nop(void);

#endif /* __N9H30_H__ */

/*@}*/ /* end of group N9H30_legacy_Constants */
