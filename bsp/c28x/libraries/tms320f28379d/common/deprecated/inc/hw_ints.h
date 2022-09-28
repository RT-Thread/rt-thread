//###########################################################################
//
// FILE:   hw_ints.h
//
// TITLE:  Definitions of interrupt numbers for use with interrupt.c.
//
//###########################################################################
// $TI Release: F2837xD Support Library v3.05.00.00 $
// $Release Date: Tue Jun 26 03:15:23 CDT 2018 $
// $Copyright:
// Copyright (C) 2013-2018 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

#ifndef __HW_INTS_H__
#define __HW_INTS_H__

//*****************************************************************************
//
// PIE Interrupt Numbers
//
// 0x00FF = PIE Table Row #
// 0xFF00 = PIE Table Column #
// 0xFFFF0000 = PIE Vector ID
//
//*****************************************************************************

// Lower PIE Group 1
#define INT_ADCA_CH1            0x200101        //ADC-A Interrupt 1
#define INT_ADCB_CH1            0x210102        //ADC-B Interrupt 1
#define INT_ADCC_CH1            0x220103        //ADC-C Interrupt 1
#define INT_XINT1               0x230104        //External Interrupt 1
#define INT_XINT2               0x240105        //External Interrupt 2
#define INT_ADCD_CH1            0x250106        //ADC-D Interrupt 1
#define INT_TINT0               0x260107        //Timer Interrupt 0
#define INT_WAKEINT             0x270108        //Wakeup Interrupt

// Lower PIE Group 2
#define INT_PWM1TZ              0x280201        //PWM TZ Interrupt 1
#define INT_PWM2TZ              0x290202        //PWM TZ Interrupt 2
#define INT_PWM3TZ              0x2A0203        //PWM TZ Interrupt 3
#define INT_PWM4TZ              0x2B0204        //PWM TZ Interrupt 4
#define INT_PWM5TZ              0x2C0205        //PWM TZ Interrupt 5
#define INT_PWM6TZ              0x2D0206        //PWM TZ Interrupt 6
#define INT_PWM7TZ              0x2E0207        //PWM TZ Interrupt 7
#define INT_PWM8TZ              0x2F0208        //PWM TZ Interrupt 8

// Lower PIE Group 3
#define INT_PWM1INT             0x300301        //PWM Interrupt 1
#define INT_PWM2INT             0x310302        //PWM Interrupt 2
#define INT_PWM3INT             0x320303        //PWM Interrupt 3
#define INT_PWM4INT             0x330304        //PWM Interrupt 4
#define INT_PWM5INT             0x340305        //PWM Interrupt 5
#define INT_PWM6INT             0x350306        //PWM Interrupt 6
#define INT_PWM7INT             0x360307        //PWM Interrupt 7
#define INT_PWM8INT             0x370308        //PWM Interrupt 8

// Lower PIE Group 4
#define INT_CAP1INT             0x380401        //Capture Interrupt 1
#define INT_CAP2INT             0x390402        //Capture Interrupt 2
#define INT_CAP3INT             0x3A0403        //Capture Interrupt 3
#define INT_CAP4INT             0x3B0404        //Capture Interrupt 4
#define INT_CAP5INT             0x3C0405        //Capture Interrupt 5
#define INT_CAP6INT             0x3D0406        //Capture Interrupt 6
#define INT_CAP7INT             0x3E0407        //Capture Interrupt 7
#define INT_CAP8INT             0x3F0408        //Capture Interrupt 8

// Lower PIE Group 5
#define INT_EQEP1INT            0x400501        //Quadrature Interrupt 1
#define INT_EQEP2INT            0x410502        //Quadrature Interrupt 2
#define INT_EQEP3INT            0x420503        //Quadrature Interrupt 3
#define INT_EQEP4INT            0x430504        //Quadrature Interrupt 4
#define INT_CLB1INT             0x440505        //CLB Interrupt 1
#define INT_CLB2INT             0x450506        //CLB Interrupt 2
#define INT_CLB3INT             0x460507        //CLB Interrupt 3
#define INT_CLB4INT             0x470508        //CLB Interrupt 4

// Lower PIE Group 6
#define INT_SPIRXINTA           0x480601        //SPI-A Receive Interrupt
#define INT_SPITXINTA           0x490602        //SPI-A Transmit Interrupt
#define INT_SPIRXINTB           0x4A0603        //SPI-B Receive Interrupt
#define INT_SPITXINTB           0x4B0604        //SPI-B Transmit Interrupt
#define INT_MRINTA              0x4C0605        //McBSP-A Receive Interrupt
#define INT_MXINTA              0x4D0606        //McBSP-A Transmit Interrupt
#define INT_MRINTB              0x4E0607        //McBSP-B Receive Interrupt
#define INT_MXINTB              0x4F0608        //McBSP-B Transmit Interrupt

// Lower PIE Group 7
#define INT_DMA1INT             0x500701        //DMA Channel 1 Interrupt
#define INT_DMA2INT             0x510702        //DMA Channel 2 Interrupt
#define INT_DMA3INT             0x520703        //DMA Channel 3 Interrupt
#define INT_DMA4INT             0x530704        //DMA Channel 4 Interrupt
#define INT_DMA5INT             0x540705        //DMA Channel 5 Interrupt
#define INT_DMA6INT             0x550706        //DMA Channel 6 Interrupt

// Lower PIE Group 8
#define INT_I2CINT1A            0x580801        //I2C-A Basic Interrupts
#define INT_I2CINT2A            0x590802        //I2C-A FIFO Interrupts
#define INT_I2CINT1B            0x5A0803        //I2C-B Basic Interrupts
#define INT_I2CINT2B            0x5B0804        //I2C-B FIFO Interrupts
#define INT_SCICRX              0x5C0805        //SCI-C Receive Interrupt
#define INT_SCICTX              0x5D0806        //SCI-C Transmit Interrupt
#define INT_SCIDRX              0x5E0807        //SCI-D Receive Interrupt
#define INT_SCIDTX              0x5F0808        //SCI-D Transmit Interrupt

// Lower PIE Group 9
#define INT_SCIRXINTA           0x600901        //SCI-A RX Interrupt
#define INT_SCITXINTA           0x610902        //SCI-A TX Interrupt
#define INT_SCIRXINTB           0x620903        //SCI-B RX Interrupt
#define INT_SCITXINTB           0x630904        //SCI-B TX Interrupt
#define INT_CANA_0              0x640905        //CANA 0 Interrupt
#define INT_CANA_1              0x650906        //CANA 1 Interrupt
#define INT_CANB_0              0x660907        //CANB 0 Interrupt
#define INT_CANB_1              0x670908        //CANB 1 Interrupt

// Lower PIE Group 10
#define INT_ADCA_EVT            0x680A01        //ADCA_EVT Interrupt
#define INT_ADCA_CH2            0x690A02        //ADCA_CH2 Interrupt 2
#define INT_ADCA_CH3            0x6A0A03        //ADCA_CH3 Interrupt 3
#define INT_ADCA_CH4            0x6B0A04        //ADCA_CH4 Interrupt 4
#define INT_ADCB_EVT            0x6C0A05        //ADCB_EVT Interrupt
#define INT_ADCB_CH2            0x6D0A06        //ADCB_CH2 Interrupt 2
#define INT_ADCB_CH3            0x6E0A07        //ADCB_CH3 Interrupt 3
#define INT_ADCB_CH4            0x6F0A08        //ADCB_CH4 Interrupt 4

// Lower PIE Group 11
#define INT_CLA1INT1            0x700B01        //CLA_1 Interrupt 1
#define INT_CLA1INT2            0x710B02        //CLA_1 Interrupt 2
#define INT_CLA1INT3            0x720B03        //CLA_1 Interrupt 3
#define INT_CLA1INT4            0x730B04        //CLA_1 Interrupt 4
#define INT_CLA1INT5            0x740B05        //CLA_1 Interrupt 5
#define INT_CLA1INT6            0x750B06        //CLA_1 Interrupt 6
#define INT_CLA1INT7            0x760B07        //CLA_1 Interrupt 7
#define INT_CLA1INT8            0x770B08        //CLA_1 Interrupt 8

// Lower PIE Group 12
#define INT_XINT3               0x780C01        //External Interrupt 3
#define INT_XINT4               0x790C02        //External Interrupt 4
#define INT_XINT5               0x7A0C03        //External Interrupt 5
#define INT_FMC                 0x7C0C05        //FMC Interrupt
#define INT_VCU                 0x7D0C06        //VCU Interrupt
#define INT_LVF                 0x7E0C07        //Latched Overflow
#define INT_LUF                 0x7F0C08        //Latched Underflow

// Upper PIE Group 1
#define INT_IPC0INT             0x84010D        //IPC Interrupt 1
#define INT_IPC1INT             0x85010E        //IPC Interrupt 2
#define INT_IPC2INT             0x86010F        //IPC Interrupt 3
#define INT_IPC3INT             0x870110        //IPC Interrupt 4

// Upper PIE Group 2
#define INT_PWM9TZ              0x880209        //PWM TZ Interrupt 9
#define INT_PWM10TZ             0x89020A        //PWM TZ Interrupt 10
#define INT_PWM11TZ             0x8A020B        //PWM TZ Interrupt 11
#define INT_PWM12TZ             0x8B020C        //PWM TZ Interrupt 12

// Upper PIE Group 3
#define INT_PWM9INT             0x900309        //PWM Interrupt 9
#define INT_PWM10INT            0x91030A        //PWN Interrupt 10
#define INT_PWM11INT            0x92030B        //PWM Interrupt 11
#define INT_PWM12INT            0x93030C        //PWM Interrupt 12

// Upper PIE Group 4
#define INT_HRCAP1INT           0x980409        //High-Res Capture Interrupt 1
#define INT_HRCAP2INT           0x99040A        //High-Res Capture Interrupt 2
#define INT_HRCAP3INT           0x9A040B        //High-Res Capture Interrupt 3
#define INT_HRCAP4INT           0x9B040C        //High-Res Capture Interrupt 4
#define INT_HRCAP5INT           0x9C040D        //High-Res Capture Interrupt 1
#define INT_HRCAP6INT           0x9D040E        //High-Res Capture Interrupt 2
#define INT_HRCAP7INT           0x9E040F        //High-Res Capture Interrupt 3
#define INT_HRCAP8INT           0x9F0410        //High-Res Capture Interrupt 4

// Upper PIE Group 5
#define INT_SDFM1INT            0xA00509        //SDFM Interrupt 1
#define INT_SDFM2INT            0xA1050A        //SDFM Interrupt 2
#define INT_SDFM3INT            0xA2050B        //SDFM Interrupt 3
#define INT_SDFM4INT            0xA3050C        //SDFM Interrupt 4
#define INT_SDFM5INT            0xA4050D        //SDFM Interrupt 5
#define INT_SDFM6INT            0xA5050E        //SDFM Interrupt 6
#define INT_SDFM7INT            0xA6050F        //SDFM Interrupt 7
#define INT_SDFM8INT            0xA70510        //SDFM Interrupt 8

// Upper PIE Group 6
#define INT_SPIRXINTC           0xA80609        //SPI-A Receive Interrupt
#define INT_SPITXINTC           0xA9060A        //SPI-A Transmit Interrupt
#define INT_SPIRXINTD           0xAA060B        //SPI-B Receive Interrupt
#define INT_SPITXINTD           0xAB060C        //SPI-B Transmit Interrupt

// Upper PIE Group 8
#define INT_UPPAINT             0xBE080F        //UPP-A Interrupt
#define INT_UPPBINT             0xBF0810        //UPP-B Interrupt

// Upper PIE Group 9
#define INT_CANCINT1            0xC00909        //CANC 1 Interrupt
#define INT_CANCINT2            0xC1090A        //CANC 2 Interrupt
#define INT_CANDINT1            0xC2090B        //CAND 1 Interrupt
#define INT_CANDINT2            0xC3090C        //CAND 2 Interrupt
#define INT_USBAINT             0xC6090F        //USBA Interrupt
#define INT_USBBINT             0xC70910        //USBB Interrupt

// Upper PIE Group 10
#define INT_ADCC_EVT            0xC80A09        //ADCC_EVT Interrupt
#define INT_ADCC_CH2            0xC90A0A        //ADCC_CH2 Interrupt 2
#define INT_ADCC_CH3            0xCA0A0B        //ADCC_CH3 Interrupt 3
#define INT_ADCC_CH4            0xCB0A0C        //ADCC_CH4 Interrupt 4
#define INT_ADCD_EVT            0xCC0A0D        //ADCD_EVT Interrupt
#define INT_ADCD_CH2            0xCD0A0E        //ADCD_CH2 Interrupt 2
#define INT_ADCD_CH3            0xCE0A0F        //ADCD_CH3 Interrupt 3
#define INT_ADCD_CH4            0xCF0A10        //ADCD_CH4 Interrupt 4

// Upper PIE Group 11
#define INT_CLA2INT1            0xD00B09        //CLA_2 Interrupt 1
#define INT_CLA2INT2            0xD10B0A        //CLA_2 Interrupt 2
#define INT_CLA2INT3            0xD20B0B        //CLA_2 Interrupt 3
#define INT_CLA2INT4            0xD30B0C        //CLA_2 Interrupt 4
#define INT_CLA2INT5            0xD40B0D        //CLA_2 Interrupt 1
#define INT_CLA2INT6            0xD50B0E        //CLA_2 Interrupt 2
#define INT_CLA2INT7            0xD60B0F        //CLA_2 Interrupt 3
#define INT_CLA2INT8            0xD70B10        //CLA_2 Interrupt 4

// Upper PIE Group 12
#define INT_EMIF_ERR            0xD80C09        //EMIF Error Interrupt
#define INT_RAM_CORR_ERR        0xD90C0A        //RAM Correctable Error Interrupt
#define INT_FLASH_CORR_ERR      0xDA0C0B        //Flash correctable Error Interrupt
#define INT_RAM_ACC_VIO         0xDB0C0C        //RAM Access Violation Interrupt
#define INT_SYS_PLL_SLIP        0xDC0C0D        //System PLL Slip Interrupt
#define INT_AUX_PLL_SLIP        0xDD0C0E        //Auxillary PLL Slip Interrupt
#define INT_CLA_OF              0xDE0C0F        //CLA Overflow Interrupt
#define INT_CLA_UF              0xDF0C10        //CLA Underflow Interrupt

//Workaround for  Stellaris code
#define INT_USB0                INT_USBAINT     // USB 0 Controller

//Workaround for other interrupts
#define INT_RESET               0x000000        //Reset Interrupt
#define INT_INT1                0x010000        //Not Used
#define INT_INT2                0x020000        //Not Used
#define INT_INT3                0x030000        //Not Used
#define INT_INT4                0x040000        //Not Used
#define INT_INT5                0x050000        //Not Used
#define INT_INT6                0x060000        //Not Used
#define INT_INT7                0x070000        //Not Used
#define INT_INT8                0x080000        //Not Used
#define INT_INT9                0x090000        //Not Used
#define INT_INT10               0x0A0000        //Not Used
#define INT_INT11               0x0B0000        //Not Used
#define INT_INT12               0x0C0000        //Not Used
#define INT_TINT1               0x0D0D00        //Timer Interrupt 1
#define INT_TINT2               0x0E0E00        //Timer Interrupt 2
#define INT_DATALOG             0x0F0F00        //CPU Data Logging Interrupt
#define INT_RTOSINT             0x101000        //CPU Real Time OS Interrupt
#define INT_EMUINT              0x110000        //CPU Emulation Interrupt
#define INT_NMI                 0x120000        //External Non-Maskable Interrupt
#define INT_ILLEGAL             0x130000        //Illegal Operation
#define INT_USER1               0x140000        //User-defined
#define INT_USER2               0x150000        //User-defined
#define INT_USER3               0x160000        //User-defined
#define INT_USER4               0x170000        //User-defined
#define INT_USER5               0x180000        //User-defined
#define INT_USER6               0x190000        //User-defined
#define INT_USER7               0x1A0000        //User-defined
#define INT_USER8               0x1B0000        //User-defined
#define INT_USER9               0x1C0000        //User-defined
#define INT_USER10              0x1D0000        //User-defined
#define INT_USER11              0x1E0000        //User-defined
#define INT_USER12              0x1F0000        //User-defined


#endif // __HW_INTS_H__


