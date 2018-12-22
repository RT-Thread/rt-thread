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
    IMX_INT_INTERRUPT_35 = 35,   //!< Reserved.
    IMX_INT_SNVS_LP_SET_PWR_OFF = 36,   //!< PMIC power off request.
    IMX_INT_RNGB = 37,  //!< Random Number Generator interrupt request.
    IMX_INT_SPDC = 38, //!< SiPix Display Controller interrupt request.
    IMX_INT_CSI = 39,  //!< CMOS Sensor Interface interrupt request.
    IMX_INT_INTERRUPT_40 = 40, //!< Reserved.
    IMX_INT_INTERRUPT_41 = 41, //!< Reserved.
    IMX_INT_GPU2D = 42, //!< GPU2D general interrupt request.
    IMX_INT_OPENVG = 43,   //!< OpenVG general interrupt request.
    IMX_INT_INTERRUPT_44 = 44,   //!< Reserved.
    IMX_INT_INTERRUPT_45 = 45,   //!< Reserved.
    IMX_INT_EIM = 46,   //!< EIM interrupt request.
    IMX_INT_INTERRUPT_47 = 47,   //!< Reserved.
    IMX_INT_INTERRUPT_48 = 48,  //!< Reserved.
    IMX_INT_INTERRUPT_49 = 49,  //!< Reserved.
    IMX_INT_INTERRUPT_50 = 50,  //!< Reserved.
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
    IMX_INT_INTERRUPT_67 = 67,    //!< Reserved.
    IMX_INT_I2C1 = 68,  //!< I2C1 interrupt request.
    IMX_INT_I2C2 = 69,  //!< I2C2 interrupt request.
    IMX_INT_I2C3 = 70,  //!< I2C3 interrupt request.
    IMX_INT_LCDIF = 71,  //!< LCDIF interrupt request.
    IMX_INT_USB_OTG2 = 72,    //!< USB OTG2 interrupt request.
    IMX_INT_INTERRUPT_73 = 73,    //!< Reserved.
    IMX_INT_USB_HOST1 = 74,    //!< USB Host 1 interrupt request.
    IMX_INT_USB_OTG1 = 75,   //!< USB OTG1 interrupt request.
    IMX_INT_USB_UTMI0 = 76, //!< UTMI0 interrupt request.
    IMX_INT_USB_UTMI1 = 77, //!< UTMI1 interrupt request.
    IMX_INT_SSI1 = 78,  //!< SSI1 interrupt request.
    IMX_INT_SSI2 = 79,  //!< SSI2 interrupt request.
    IMX_INT_SSI3 = 80,  //!< SSI3 interrupt request.
    IMX_INT_TEMPERATURE = 81,   //!< Temperature Sensor (temp. greater than threshold) interrupt request.
    IMX_INT_INTERRUPT_82 = 82,  //!< Reserved.
    IMX_INT_INTERRUPT_83 = 83,  //!< Reserved.
    IMX_INT_SPDIF = 84, //!< Logical OR of SPDIF TX and SPDIF RX interrupts.
    IMX_INT_INTERRUPT_85 = 85,   //!< Reserved.
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
    IMX_INT_INTERRUPT_108 = 108,    //!< Reserved.
    IMX_INT_INTERRUPT_109 = 109,   //!< Reserved.
    IMX_INT_INTERRUPT_110 = 110,    //!< Reserved.
    IMX_INT_INTERRUPT_111 = 111,   //!< Reserved.
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
    IMX_INT_INTERRUPT_122 = 122, //!< Reserved.
    IMX_INT_SRC = 123,  //!< SRC interrupt request.
    IMX_INT_CHEETAH_L2 = 124,   //!< Logical OR of all L2 interrupt requests.
    IMX_INT_CHEETAH_PARITY = 125,   //!< Parity Check error interrupt request.
    IMX_INT_CHEETAH_PERFORM = 126,  //!< Logical OR of Performance Unit interrupts.
    IMX_INT_CHEETAH_TRIGGER = 127,  //!< Logical OR of CTI trigger outputs.
    IMX_INT_SRC_CPU_WDOG = 128, //!< Combined CPU wdog interrupts (4x) out of SRC.
    IMX_INT_EPDC = 129,    //!< EPDC interrupt request.
    IMX_INT_PXP = 130,    //!< PXP interrupt request.
    IMX_INT_DCP_GENERAL = 131,    //!< DCP general interrupt request.
    IMX_INT_DCP_CHANNEL_0 = 132,    //!< DCP channel 0 interrupt request.
    IMX_INT_DCP_SECURE = 133,    //!< DCP secure interrupt request.
    IMX_INT_INTERRUPT_134 = 134,  //!< Reserved.
    IMX_INT_INTERRUPT_135 = 135,  //!< Reserved.
    IMX_INT_SJC = 136,  //!< SJC interrupt from General Purpose register.
    IMX_INT_INTERRUPT_137 = 137,    //!< Reserved.
    IMX_INT_INTERRUPT_138 = 138,    //!< Reserved.
    IMX_INT_INTERRUPT_139 = 139,    //!< Reserved.
    IMX_INT_TZASC1 = 140,   //!< ASC1 interrupt request.
    IMX_INT_INTERRUPT_141 = 141,   //!< Reserved.
    IMX_INT_INTERRUPT_142 = 142, //!< Reserved.
    IMX_INT_INTERRUPT_143 = 143, //!< Reserved.
    IMX_INT_INTERRUPT_144 = 144,    //!< Reserved.
    IMX_INT_INTERRUPT_145 = 145,    //!< Reserved.
    IMX_INT_FEC = 146,    //!< Fast Ethernet Controller interrupt request.
    IMX_INT_INTERRUPT_147 = 147,  //!< Reserved.
    IMX_INT_INTERRUPT_148 = 148,   //!< Reserved.
    IMX_INT_INTERRUPT_149 = 149, //!< Reserved.
    IMX_INT_INTERRUPT_150 = 150, //!< Reserved.
    IMX_INT_INTERRUPT_151 = 151,    //!< Reserved.
    IMX_INT_INTERRUPT_152 = 152,   //!< Reserved.
    IMX_INT_INTERRUPT_153 = 153,   //!< Reserved.
    IMX_INT_INTERRUPT_154 = 154,   //!< Reserved.
    IMX_INT_INTERRUPT_155 = 155,   //!< Reserved.
    IMX_INT_INTERRUPT_156 = 156,    //!< Reserved.
    IMX_INT_INTERRUPT_157 = 157,    //!< Reserved.
    IMX_INT_INTERRUPT_158 = 158, //!< Reserved.
    IMX_INT_PMU_DIG_BO = 159,    //!< //!< PMU digital regulator brown-out interrupt request.
    IMX_INTERRUPT_COUNT = 160   //!< Total number of interrupts.
};


#endif // __IRQ_NUMBERS_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
