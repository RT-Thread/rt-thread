/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(__IRQ_NUMBERS_H__)
#define __IRQ_NUMBERS_H__

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief i.MX6 interrupt numbers.
//!
//! This enumeration lists the numbers for all of the interrupts available on the i.MX6 series.
//! Use these numbers when specifying an interrupt to the GIC.
//!
//! The first 16 interrupts are special in that they are reserved for software interrupts generated
//! by the SWI instruction.
enum _imx_interrupts
{
    SW_INTERRUPT_0 = 0, //!< Software interrupt 0.
    SW_INTERRUPT_1 = 1, //!< Software interrupt 1.
    SW_INTERRUPT_2 = 2, //!< Software interrupt 2.
    SW_INTERRUPT_3 = 3, //!< Software interrupt 3.
    SW_INTERRUPT_4 = 4, //!< Software interrupt 4.
    SW_INTERRUPT_5 = 5, //!< Software interrupt 5.
    SW_INTERRUPT_6 = 6, //!< Software interrupt 6.
    SW_INTERRUPT_7 = 7, //!< Software interrupt 7.
    SW_INTERRUPT_8 = 8, //!< Software interrupt 8.
    SW_INTERRUPT_9 = 9, //!< Software interrupt 9.
    SW_INTERRUPT_10 = 10,   //!< Software interrupt 10.
    SW_INTERRUPT_11 = 11,   //!< Software interrupt 11.
    SW_INTERRUPT_12 = 12,   //!< Software interrupt 12.
    SW_INTERRUPT_13 = 13,   //!< Software interrupt 13.
    SW_INTERRUPT_14 = 14,   //!< Software interrupt 14.
    SW_INTERRUPT_15 = 15,   //!< Software interrupt 15.
    RSVD_INTERRUPT_16 = 16, //!< Reserved.
    RSVD_INTERRUPT_17 = 17, //!< Reserved.
    RSVD_INTERRUPT_18 = 18, //!< Reserved.
    RSVD_INTERRUPT_19 = 19, //!< Reserved.
    RSVD_INTERRUPT_20 = 20, //!< Reserved.
    RSVD_INTERRUPT_21 = 21, //!< Reserved.
    RSVD_INTERRUPT_22 = 22, //!< Reserved.
    RSVD_INTERRUPT_23 = 23, //!< Reserved.
    RSVD_INTERRUPT_24 = 24, //!< Reserved.
    RSVD_INTERRUPT_25 = 25, //!< Reserved.
    RSVD_INTERRUPT_26 = 26, //!< Reserved.
    RSVD_INTERRUPT_27 = 27, //!< Reserved.
    RSVD_INTERRUPT_28 = 28, //!< Reserved.
    RSVD_INTERRUPT_29 = 29, //!< Reserved.
    RSVD_INTERRUPT_30 = 30, //!< Reserved.
    RSVD_INTERRUPT_31 = 31, //!< Reserved.
    IMX_INT_IOMUXC_GPR = 32,   //!< General Purpose Register 1 from IOMUXC. Used to notify cores on exception condition while boot.
    IMX_INT_CHEETAH_CSYSPWRUPREQ = 33,  //!< @todo Listed as DAP in RM
    IMX_INT_SDMA = 34,  //!< Logical OR of all 48 SDMA interrupt requests/events from all channels.
    IMX_INT_VPU_JPG = 35,   //!< JPEG codec interrupt request.
    IMX_INT_SNVS_LP_SET_PWR_OFF = 36,   //!< PMIC power off request.
    IMX_INT_IPU1_ERR = 37,  //!< IPU1 error interrupt request.
    IMX_INT_IPU1_FUNC = 38, //!< IPU1 sync interrupt request.
    IMX_INT_IPU2_ERR = 39,  //!< IPU2 error interrupt request.
    IMX_INT_IPU2_FUNC = 40, //!< IPU2 sync interrupt request.
    IMX_INT_GPU3D = 41, //!< GPU3D interrupt request.
    IMX_INT_GPU2D = 42, //!< Idle interrupt from GPU2D (for S/W power gating).
    IMX_INT_OPENVG_XAQ2 = 43,   //!< GPU2D general interrupt request.
    IMX_INT_VPU_IPI = 44,   //!< VPU interrupt request.
    IMX_INT_APBHDMA = 45,   //!< Logical OR of 4 signals: dma_chan[0-3]_irq, GPMI operation channel description complete interrupt.
    IMX_INT_EIM = 46,   //!< EIM interrupt request.
    IMX_INT_BCH = 47,   //!< BCH operation complete interrupt.
    IMX_INT_GPMI = 48,  //!< GPMI operation timeout error interrupt.
    IMX_INT_DTCP = 49,  //!< DTCP interrupt request.
    IMX_INT_VDOA = 50,  //!< Logical OR of VDOA interrupt requests.
    IMX_INT_SNVS = 51,  //!< SNVS consolidated interrupt.
    IMX_INT_SNVS_SEC = 52,  //!< SNVS security interrupt.
    IMX_INT_CSU = 53,   //!< CSU interrupt request 1. Indicates to the processor that one or more alarm inputs were asserted.
    IMX_INT_USDHC1 = 54,    //!< uSDHC1 (Enhanced SDHC) interrupt request.
    IMX_INT_USDHC2 = 55,    //!< uSDHC2 (Enhanced SDHC) interrupt request.
    IMX_INT_USDHC3 = 56,    //!< uSDHC3 (Enhanced SDHC) interrupt request.
    IMX_INT_USDHC4 = 57,    //!< uSDHC4 (Enhanced SDHC) interrupt request.
    IMX_INT_UART1 = 58, //!< Logical OR of UART1 interrupt requests.
    IMX_INT_UART2 = 59, //!< Logical OR of UART2 interrupt requests.
    IMX_INT_UART3 = 60, //!< Logical OR of UART3 interrupt requests.
    IMX_INT_UART4 = 61, //!< Logical OR of UART4 interrupt requests.
    IMX_INT_UART5 = 62, //!< Logical OR of UART5 interrupt requests.
    IMX_INT_ECSPI1 = 63,    //!< eCSPI1 interrupt request.
    IMX_INT_ECSPI2 = 64,    //!< eCSPI2 interrupt request.
    IMX_INT_ECSPI3 = 65,    //!< eCSPI3 interrupt request.
    IMX_INT_ECSPI4 = 66,    //!< eCSPI4 interrupt request.
    IMX_INT_ECSPI5 = 67,    //!< eCSPI5 interrupt request.
    IMX_INT_I2C1 = 68,  //!< I2C1 interrupt request.
    IMX_INT_I2C2 = 69,  //!< I2C2 interrupt request.
    IMX_INT_I2C3 = 70,  //!< I2C3 interrupt request.
    IMX_INT_SATA = 71,  //!< SATA interrupt request.
    IMX_INT_USBOH3_UH1 = 72,    //!< USB Host 1 interrupt request.
    IMX_INT_USBOH3_UH2 = 73,    //!< USB Host 2 interrupt request.
    IMX_INT_USBOH3_UH3 = 74,    //!< USB Host 3 interrupt request.
    IMX_INT_USBOH3_UOTG = 75,   //!< USB OTG interrupt request.
    IMX_INT_USB_UTMI0 = 76, //!< UTMI0 interrupt request.
    IMX_INT_USB_UTMI1 = 77, //!< UTMI1 interrupt request.
    IMX_INT_SSI1 = 78,  //!< SSI1 interrupt request.
    IMX_INT_SSI2 = 79,  //!< SSI2 interrupt request.
    IMX_INT_SSI3 = 80,  //!< SSI3 interrupt request.
    IMX_INT_TEMPERATURE = 81,   //!< Temperature Sensor (temp. greater than threshold) interrupt request.
    IMX_INT_ASRC = 82,  //!< ASRC interrupt request.
    IMX_INT_ESAI = 83,  //!< ESAI interrupt request.
    IMX_INT_SPDIF = 84, //!< Logical OR of SPDIF TX and SPDIF RX interrupts.
    IMX_INT_MLB = 85,   //!< MLB error interrupt request.
    IMX_INT_PMU_ANA_BO = 86,    //!< PMU analog regulator brown-out interrupt request.
    IMX_INT_GPT = 87,   //!< Logical OR of GPT rollover interrupt line, input capture 1 & 2 lines, output compare 1, 2 & 3 interrupt lines.
    IMX_INT_EPIT1 = 88, //!< EPIT1 output compare interrupt.
    IMX_INT_EPIT2 = 89, //!< EPIT2 output compare interrupt.
    IMX_INT_GPIO1_INT7 = 90,    //!< INT7 interrupt request.
    IMX_INT_GPIO1_INT6 = 91,    //!< INT6 interrupt request.
    IMX_INT_GPIO1_INT5 = 92,    //!< INT5 interrupt request.
    IMX_INT_GPIO1_INT4 = 93,    //!< INT4 interrupt request.
    IMX_INT_GPIO1_INT3 = 94,    //!< INT3 interrupt request.
    IMX_INT_GPIO1_INT2 = 95,    //!< INT2 interrupt request.
    IMX_INT_GPIO1_INT1 = 96,    //!< INT1 interrupt request.
    IMX_INT_GPIO1_INT0 = 97,    //!< INT0 interrupt request.
    IMX_INT_GPIO1_INT15_0 = 98, //!< Combined interrupt indication for GPIO1 signals 0 - 15.
    IMX_INT_GPIO1_INT31_16 = 99,    //!< Combined interrupt indication for GPIO1 signals 16 - 31.
    IMX_INT_GPIO2_INT15_0 = 100,    //!< Combined interrupt indication for GPIO2 signals 0 - 15.
    IMX_INT_GPIO2_INT31_16 = 101,   //!< Combined interrupt indication for GPIO2 signals 16 - 31.
    IMX_INT_GPIO3_INT15_0 = 102,    //!< Combined interrupt indication for GPIO3 signals 0 - 15.
    IMX_INT_GPIO3_INT31_16 = 103,   //!< Combined interrupt indication for GPIO3 signals 16 - 31.
    IMX_INT_GPIO4_INT15_0 = 104,    //!< Combined interrupt indication for GPIO4 signals 0 - 15.
    IMX_INT_GPIO4_INT31_16 = 105,   //!< Combined interrupt indication for GPIO4 signals 16 - 31.
    IMX_INT_GPIO5_INT15_0 = 106,    //!< Combined interrupt indication for GPIO5 signals 0 - 15.
    IMX_INT_GPIO5_INT31_16 = 107,   //!< Combined interrupt indication for GPIO5 signals 16 - 31.
    IMX_INT_GPIO6_INT15_0 = 108,    //!< Combined interrupt indication for GPIO6 signals 0 - 15.
    IMX_INT_GPIO6_INT31_16 = 109,   //!< Combined interrupt indication for GPIO6 signals 16 - 31.
    IMX_INT_GPIO7_INT15_0 = 110,    //!< Combined interrupt indication for GPIO7 signals 0 - 15.
    IMX_INT_GPIO7_INT31_16 = 111,   //!< Combined interrupt indication for GPIO7 signals 16 - 31.
    IMX_INT_WDOG1 = 112,    //!< WDOG1 timer reset interrupt request.
    IMX_INT_WDOG2 = 113,    //!< WDOG2 timer reset interrupt request.
    IMX_INT_KPP = 114,  //!< Key Pad interrupt request.
    IMX_INT_PWM1 = 115, //!< Cumulative interrupt line for PWM1. Logical OR of rollover, compare, and FIFO waterlevel crossing interrupts.
    IMX_INT_PWM2 = 116, //!< Cumulative interrupt line for PWM2. Logical OR of rollover, compare, and FIFO waterlevel crossing interrupts.
    IMX_INT_PWM3 = 117, //!< Cumulative interrupt line for PWM3. Logical OR of rollover, compare, and FIFO waterlevel crossing interrupts.
    IMX_INT_PWM4 = 118, //!< Cumulative interrupt line for PWM4. Logical OR of rollover, compare, and FIFO waterlevel crossing interrupts.
    IMX_INT_CCM_INT1 = 119, //!< CCM interrupt request 1.
    IMX_INT_CCM_INT2 = 120, //!< CCM interrupt request 2.
    IMX_INT_GPC_INT1 = 121, //!< GPC interrupt request 1.
    IMX_INT_GPC_INT2 = 122, //!< GPC interrupt request 2.
    IMX_INT_SRC = 123,  //!< SRC interrupt request.
    IMX_INT_CHEETAH_L2 = 124,   //!< Logical OR of all L2 interrupt requests.
    IMX_INT_CHEETAH_PARITY = 125,   //!< Parity Check error interrupt request.
    IMX_INT_CHEETAH_PERFORM = 126,  //!< Logical OR of Performance Unit interrupts.
    IMX_INT_CHEETAH_TRIGGER = 127,  //!< Logical OR of CTI trigger outputs.
    IMX_INT_SRC_CPU_WDOG = 128, //!< Combined CPU wdog interrupts (4x) out of SRC.
    IMX_INT_INTERRUPT_129 = 129,    //!< Reserved.
    IMX_INT_INTERRUPT_130 = 130,    //!< Reserved.
    IMX_INT_INTERRUPT_131 = 131,    //!< Reserved.
    IMX_INT_CSI_INTR1 = 132,    //!< MIPI CSI interrupt request 1.
    IMX_INT_CSI_INTR2 = 133,    //!< MIPI CSI interrupt request 2.
    IMX_INT_DSI = 134,  //!< MIPI DSI interrupt request.
    IMX_INT_HSI = 135,  //!< MIPI HSI interrupt request.
    IMX_INT_SJC = 136,  //!< SJC interrupt from General Purpose register.
    IMX_INT_CAAM_INT0 = 137,    //!< CAAM job ring 0 interrupt.
    IMX_INT_CAAM_INT1 = 138,    //!< CAAM job ring 1 interrupt.
    IMX_INT_INTERRUPT_139 = 139,    //!< Reserved.
    IMX_INT_TZASC1 = 140,   //!< ASC1 interrupt request.
    IMX_INT_TZASC2 = 141,   //!< ASC2 interrupt request.
    IMX_INT_FLEXCAN1 = 142, //!< FLEXCAN1 combined interrupt. Logical OR of ini_int_busoff, ini_int_error, ipi_int_mbor, ipi_int_rxwarning, ipi_int_txwarning and ipi_int_wakein.
    IMX_INT_FLEXCAN2 = 143, //!< FLEXCAN2 combined interrupt. Logical OR of ini_int_busoff, ini_int_error, ipi_int_mbor, ipi_int_rxwarning, ipi_int_txwarning and ipi_int_wakein.
    IMX_INT_PERFMON1 = 144,    //!< Reserved.
    IMX_INT_PERFMON2 = 145,    //!< Reserved.
    IMX_INT_PERFMON3 = 146,    //!< Reserved.
    IMX_INT_HDMI_TX = 147,  //!< HDMI master interrupt request.
    IMX_INT_HDMI_TX_WAKEUP = 148,   //!< HDMI CEC engine dedicated interrupt signal raised by a wake-up event.
    IMX_INT_MLB_AHB0 = 149, //!< Channels [31:0] interrupt requests.
    IMX_INT_ENET = 150, //!< MAC 0 IRQ, Logical OR of:
                        //! - MAC 0 Periodic Timer Overflow
                        //! - MAC 0 Time Stamp Available
                        //! - MAC 0 Payload Receive Error
                        //! - MAC 0 Transmit FIFO Underrun
                        //! - MAC 0 Collision Retry Limit
                        //! - MAC 0 Late Collision
                        //! - MAC 0 Ethernet Bus Error
                        //! - MAC 0 MII Data Transfer Done
                        //! - MAC 0 Receive Buffer Done
                        //! - MAC 0 Receive Frame Done
                        //! - MAC 0 Transmit Buffer Done
                        //! - MAC 0 Transmit Frame Done
                        //! - MAC 0 Graceful Stop
                        //! - MAC 0 Babbling Transmit Error
                        //! - MAC 0 Babbling Receive Error
                        //! - MAC 0 Wakeup Request [synchronous]
    IMX_INT_ENET_1588 = 151,    //!< ￼MAC 0 1588 Timer interrupt [synchronous] request.
    IMX_INT_PCIE_1 = 152,   //!< PCIe interrupt request 1.
    IMX_INT_PCIE_2 = 153,   //!< PCIe interrupt request 2.
    IMX_INT_PCIE_3 = 154,   //!< PCIe interrupt request 3.
    IMX_INT_PCIE_4 = 155,   //!< PCIe interrupt request 4.
    IMX_INT_DCIC1 = 156,    //!< Logical OR of DCIC1 interrupt requests.
    IMX_INT_DCIC2 = 157,    //!< Logical OR of DCIC2 interrupt requests.
    IMX_INT_MLB_AHB1 = 158, //!< Logical OR of channel[63:32] interrupt requests.
    IMX_INT_PMU_DIG_BO = 159,    //!< //!< PMU digital regulator brown-out interrupt request.
    IMX_INTERRUPT_COUNT = 160   //!< Total number of interrupts.
};


#endif // __IRQ_NUMBERS_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
