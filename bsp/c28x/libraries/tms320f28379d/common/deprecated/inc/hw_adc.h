//###########################################################################
//
// FILE:    hw_adc.h
//
// TITLE:   Definitions for the C28x ADC registers.
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

#ifndef __HW_ADC_H__
#define __HW_ADC_H__

//*****************************************************************************
//
// The following are defines for the ADC register offsets
//
//*****************************************************************************
#define ADC_O_CTL1                0x0         // ADC Control 1 Register
#define ADC_O_CTL2                0x1         // ADC Control 2 Register
#define ADC_O_BURSTCTL            0x2         // ADC Burst Control Register
#define ADC_O_INTFLG              0x3         // ADC Interrupt Flag Register
#define ADC_O_INTFLGCLR           0x4         // ADC Interrupt Flag Clear
                                              // Register
#define ADC_O_INTOVF              0x5         // ADC Interrupt Overflow Register
#define ADC_O_INTOVFCLR           0x6         // ADC Interrupt Overflow Clear
                                              // Register
#define ADC_O_INTSEL1N2           0x7         // ADC Interrupt 1 and 2 Selection
                                              // Register
#define ADC_O_INTSEL3N4           0x8         // ADC Interrupt 3 and 4 Selection
                                              // Register
#define ADC_O_SOCPRICTL           0x9         // ADC SOC Priority Control
                                              // Register
#define ADC_O_INTSOCSEL1          0xA         // ADC Interrupt SOC Selection 1
                                              // Register
#define ADC_O_INTSOCSEL2          0xB         // ADC Interrupt SOC Selection 2
                                              // Register
#define ADC_O_SOCFLG1             0xC         // ADC SOC Flag 1 Register
#define ADC_O_SOCFRC1             0xD         // ADC SOC Force 1 Register
#define ADC_O_SOCOVF1             0xE         // ADC SOC Overflow 1 Register
#define ADC_O_SOCOVFCLR1          0xF         // ADC SOC Overflow Clear 1
                                              // Register
#define ADC_O_SOC0CTL             0x10        // ADC SOC0 Control Register
#define ADC_O_SOC1CTL             0x12        // ADC SOC1 Control Register
#define ADC_O_SOC2CTL             0x14        // ADC SOC2 Control Register
#define ADC_O_SOC3CTL             0x16        // ADC SOC3 Control Register
#define ADC_O_SOC4CTL             0x18        // ADC SOC4 Control Register
#define ADC_O_SOC5CTL             0x1A        // ADC SOC5 Control Register
#define ADC_O_SOC6CTL             0x1C        // ADC SOC6 Control Register
#define ADC_O_SOC7CTL             0x1E        // ADC SOC7 Control Register
#define ADC_O_SOC8CTL             0x20        // ADC SOC8 Control Register
#define ADC_O_SOC9CTL             0x22        // ADC SOC9 Control Register
#define ADC_O_SOC10CTL            0x24        // ADC SOC10 Control Register
#define ADC_O_SOC11CTL            0x26        // ADC SOC11 Control Register
#define ADC_O_SOC12CTL            0x28        // ADC SOC12 Control Register
#define ADC_O_SOC13CTL            0x2A        // ADC SOC13 Control Register
#define ADC_O_SOC14CTL            0x2C        // ADC SOC14 Control Register
#define ADC_O_SOC15CTL            0x2E        // ADC SOC15 Control Register
#define ADC_O_EVTSTAT             0x30        // ADC Event Status Register
#define ADC_O_EVTCLR              0x32        // ADC Event Clear Register
#define ADC_O_EVTSEL              0x34        // ADC Event Selection Register
#define ADC_O_EVTINTSEL           0x36        // ADC Event Interrupt Selection
                                              // Register
#define ADC_O_COUNTER             0x39        // ADC Counter Register
#define ADC_O_REV                 0x3A        // ADC Revision Register
#define ADC_O_OFFTRIM             0x3B        // ADC Offset Trim Register
#define ADC_O_PPB1CONFIG          0x40        // ADC PPB1 Config Register
#define ADC_O_PPB1STAMP           0x41        // ADC PPB1 Sample Delay Time
                                              // Stamp Register
#define ADC_O_PPB1OFFCAL          0x42        // ADC PPB1 Offset Calibration
                                              // Register
#define ADC_O_PPB1OFFREF          0x43        // ADC PPB1 Offset Reference
                                              // Register
#define ADC_O_PPB1TRIPHI          0x44        // ADC PPB1 Trip High Register
#define ADC_O_PPB1TRIPLO          0x46        // ADC PPB1 Trip Low/Trigger Time
                                              // Stamp Register
#define ADC_O_PPB2CONFIG          0x48        // ADC PPB2 Config Register
#define ADC_O_PPB2STAMP           0x49        // ADC PPB2 Sample Delay Time
                                              // Stamp Register
#define ADC_O_PPB2OFFCAL          0x4A        // ADC PPB2 Offset Calibration
                                              // Register
#define ADC_O_PPB2OFFREF          0x4B        // ADC PPB2 Offset Reference
                                              // Register
#define ADC_O_PPB2TRIPHI          0x4C        // ADC PPB2 Trip High Register
#define ADC_O_PPB2TRIPLO          0x4E        // ADC PPB2 Trip Low/Trigger Time
                                              // Stamp Register
#define ADC_O_PPB3CONFIG          0x50        // ADC PPB3 Config Register
#define ADC_O_PPB3STAMP           0x51        // ADC PPB3 Sample Delay Time
                                              // Stamp Register
#define ADC_O_PPB3OFFCAL          0x52        // ADC PPB3 Offset Calibration
                                              // Register
#define ADC_O_PPB3OFFREF          0x53        // ADC PPB3 Offset Reference
                                              // Register
#define ADC_O_PPB3TRIPHI          0x54        // ADC PPB3 Trip High Register
#define ADC_O_PPB3TRIPLO          0x56        // ADC PPB3 Trip Low/Trigger Time
                                              // Stamp Register
#define ADC_O_PPB4CONFIG          0x58        // ADC PPB4 Config Register
#define ADC_O_PPB4STAMP           0x59        // ADC PPB4 Sample Delay Time
                                              // Stamp Register
#define ADC_O_PPB4OFFCAL          0x5A        // ADC PPB4 Offset Calibration
                                              // Register
#define ADC_O_PPB4OFFREF          0x5B        // ADC PPB4 Offset Reference
                                              // Register
#define ADC_O_PPB4TRIPHI          0x5C        // ADC PPB4 Trip High Register
#define ADC_O_PPB4TRIPLO          0x5E        // ADC PPB4 Trip Low/Trigger Time
                                              // Stamp Register
#define ADC_O_RESULT0             0x0         // ADC Result 0 Register
#define ADC_O_RESULT1             0x1         // ADC Result 1 Register
#define ADC_O_RESULT2             0x2         // ADC Result 2 Register
#define ADC_O_RESULT3             0x3         // ADC Result 3 Register
#define ADC_O_RESULT4             0x4         // ADC Result 4 Register
#define ADC_O_RESULT5             0x5         // ADC Result 5 Register
#define ADC_O_RESULT6             0x6         // ADC Result 6 Register
#define ADC_O_RESULT7             0x7         // ADC Result 7 Register
#define ADC_O_RESULT8             0x8         // ADC Result 8 Register
#define ADC_O_RESULT9             0x9         // ADC Result 9 Register
#define ADC_O_RESULT10            0xA         // ADC Result 10 Register
#define ADC_O_RESULT11            0xB         // ADC Result 11 Register
#define ADC_O_RESULT12            0xC         // ADC Result 12 Register
#define ADC_O_RESULT13            0xD         // ADC Result 13 Register
#define ADC_O_RESULT14            0xE         // ADC Result 14 Register
#define ADC_O_RESULT15            0xF         // ADC Result 15 Register
#define ADC_O_PPB1RESULT          0x10        // ADC Post Processing Block 1
                                              // Result Register
#define ADC_O_PPB2RESULT          0x12        // ADC Post Processing Block 2
                                              // Result Register
#define ADC_O_PPB3RESULT          0x14        // ADC Post Processing Block 3
                                              // Result Register
#define ADC_O_PPB4RESULT          0x16        // ADC Post Processing Block 4
                                              // Result Register

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCCTL1 register
//
//*****************************************************************************
#define ADC_CTL1_INTPULSEPOS      0x4         // ADC Interrupt Pulse Position
#define ADC_CTL1_ADCPWDNZ         0x80        // ADC Power Down
#define ADC_CTL1_ADCBSYCHN_S      8
#define ADC_CTL1_ADCBSYCHN_M      0xF00       // ADC Busy Channel
#define ADC_CTL1_ADCBSY           0x2000      // ADC Busy

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCCTL2 register
//
//*****************************************************************************
#define ADC_CTL2_PRESCALE_S       0
#define ADC_CTL2_PRESCALE_M       0xF         // ADC Clock Prescaler
#define ADC_CTL2_RESOLUTION       0x40        // SOC Conversion Resolution
#define ADC_CTL2_SIGNALMODE       0x80        // SOC Signaling Mode

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCBURSTCTL register
//
//*****************************************************************************
#define ADC_BURSTCTL_BURSTTRIGSEL_S  0
#define ADC_BURSTCTL_BURSTTRIGSEL_M  0x3F        // SOC Burst Trigger Source Select
#define ADC_BURSTCTL_BURSTSIZE_S  8
#define ADC_BURSTCTL_BURSTSIZE_M  0xF00       // SOC Burst Size Select
#define ADC_BURSTCTL_BURSTEN      0x8000      // SOC Burst Mode Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCINTFLG register
//
//*****************************************************************************
#define ADC_INTFLG_ADCINT1        0x1         // ADC Interrupt 1 Flag
#define ADC_INTFLG_ADCINT2        0x2         // ADC Interrupt 2 Flag
#define ADC_INTFLG_ADCINT3        0x4         // ADC Interrupt 3 Flag
#define ADC_INTFLG_ADCINT4        0x8         // ADC Interrupt 4 Flag

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCINTFLGCLR register
//
//*****************************************************************************
#define ADC_INTFLGCLR_ADCINT1     0x1         // ADC Interrupt 1 Flag Clear
#define ADC_INTFLGCLR_ADCINT2     0x2         // ADC Interrupt 2 Flag Clear
#define ADC_INTFLGCLR_ADCINT3     0x4         // ADC Interrupt 3 Flag Clear
#define ADC_INTFLGCLR_ADCINT4     0x8         // ADC Interrupt 4 Flag Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCINTOVF register
//
//*****************************************************************************
#define ADC_INTOVF_ADCINT1        0x1         // ADC Interrupt 1 Overflow Flags
#define ADC_INTOVF_ADCINT2        0x2         // ADC Interrupt 2 Overflow Flags
#define ADC_INTOVF_ADCINT3        0x4         // ADC Interrupt 3 Overflow Flags
#define ADC_INTOVF_ADCINT4        0x8         // ADC Interrupt 4 Overflow Flags

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCINTOVFCLR register
//
//*****************************************************************************
#define ADC_INTOVFCLR_ADCINT1     0x1         // ADC Interrupt 1 Overflow Clear
                                              // Bits
#define ADC_INTOVFCLR_ADCINT2     0x2         // ADC Interrupt 2 Overflow Clear
                                              // Bits
#define ADC_INTOVFCLR_ADCINT3     0x4         // ADC Interrupt 3 Overflow Clear
                                              // Bits
#define ADC_INTOVFCLR_ADCINT4     0x8         // ADC Interrupt 4 Overflow Clear
                                              // Bits

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCINTSEL1N2 register
//
//*****************************************************************************
#define ADC_INTSEL1N2_INT1SEL_S   0
#define ADC_INTSEL1N2_INT1SEL_M   0xF         // ADCINT1 EOC Source Select
#define ADC_INTSEL1N2_INT1E       0x20        // ADCINT1 Interrupt Enable
#define ADC_INTSEL1N2_INT1CONT    0x40        // ADCINT1 Continuous Mode Enable
#define ADC_INTSEL1N2_INT2SEL_S   8
#define ADC_INTSEL1N2_INT2SEL_M   0xF00       // ADCINT2 EOC Source Select
#define ADC_INTSEL1N2_INT2E       0x2000      // ADCINT2 Interrupt Enable
#define ADC_INTSEL1N2_INT2CONT    0x4000      // ADCINT2 Continuous Mode Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCINTSEL3N4 register
//
//*****************************************************************************
#define ADC_INTSEL3N4_INT3SEL_S   0
#define ADC_INTSEL3N4_INT3SEL_M   0xF         // ADCINT3 EOC Source Select
#define ADC_INTSEL3N4_INT3E       0x20        // ADCINT3 Interrupt Enable
#define ADC_INTSEL3N4_INT3CONT    0x40        // ADCINT3 Continuous Mode Enable
#define ADC_INTSEL3N4_INT4SEL_S   8
#define ADC_INTSEL3N4_INT4SEL_M   0xF00       // ADCINT4 EOC Source Select
#define ADC_INTSEL3N4_INT4E       0x2000      // ADCINT4 Interrupt Enable
#define ADC_INTSEL3N4_INT4CONT    0x4000      // ADCINT4 Continuous Mode Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCSOCPRICTL register
//
//*****************************************************************************
#define ADC_SOCPRICTL_SOCPRIORITY_S  0
#define ADC_SOCPRICTL_SOCPRIORITY_M  0x1F        // SOC Priority
#define ADC_SOCPRICTL_RRPOINTER_S  5
#define ADC_SOCPRICTL_RRPOINTER_M  0x3E0       // Round Robin Pointer

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCINTSOCSEL1 register
//
//*****************************************************************************
#define ADC_INTSOCSEL1_SOC0_S     0
#define ADC_INTSOCSEL1_SOC0_M     0x3         // SOC0 ADC Interrupt Trigger
                                              // Select
#define ADC_INTSOCSEL1_SOC1_S     2
#define ADC_INTSOCSEL1_SOC1_M     0xC         // SOC1 ADC Interrupt Trigger
                                              // Select
#define ADC_INTSOCSEL1_SOC2_S     4
#define ADC_INTSOCSEL1_SOC2_M     0x30        // SOC2 ADC Interrupt Trigger
                                              // Select
#define ADC_INTSOCSEL1_SOC3_S     6
#define ADC_INTSOCSEL1_SOC3_M     0xC0        // SOC3 ADC Interrupt Trigger
                                              // Select
#define ADC_INTSOCSEL1_SOC4_S     8
#define ADC_INTSOCSEL1_SOC4_M     0x300       // SOC4 ADC Interrupt Trigger
                                              // Select
#define ADC_INTSOCSEL1_SOC5_S     10
#define ADC_INTSOCSEL1_SOC5_M     0xC00       // SOC5 ADC Interrupt Trigger
                                              // Select
#define ADC_INTSOCSEL1_SOC6_S     12
#define ADC_INTSOCSEL1_SOC6_M     0x3000      // SOC6 ADC Interrupt Trigger
                                              // Select
#define ADC_INTSOCSEL1_SOC7_S     14
#define ADC_INTSOCSEL1_SOC7_M     0xC000      // SOC7 ADC Interrupt Trigger
                                              // Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCINTSOCSEL2 register
//
//*****************************************************************************
#define ADC_INTSOCSEL2_SOC8_S     0
#define ADC_INTSOCSEL2_SOC8_M     0x3         // SOC8 ADC Interrupt Trigger
                                              // Select
#define ADC_INTSOCSEL2_SOC9_S     2
#define ADC_INTSOCSEL2_SOC9_M     0xC         // SOC9 ADC Interrupt Trigger
                                              // Select
#define ADC_INTSOCSEL2_SOC10_S    4
#define ADC_INTSOCSEL2_SOC10_M    0x30        // SOC10 ADC Interrupt Trigger
                                              // Select
#define ADC_INTSOCSEL2_SOC11_S    6
#define ADC_INTSOCSEL2_SOC11_M    0xC0        // SOC11 ADC Interrupt Trigger
                                              // Select
#define ADC_INTSOCSEL2_SOC12_S    8
#define ADC_INTSOCSEL2_SOC12_M    0x300       // SOC12 ADC Interrupt Trigger
                                              // Select
#define ADC_INTSOCSEL2_SOC13_S    10
#define ADC_INTSOCSEL2_SOC13_M    0xC00       // SOC13 ADC Interrupt Trigger
                                              // Select
#define ADC_INTSOCSEL2_SOC14_S    12
#define ADC_INTSOCSEL2_SOC14_M    0x3000      // SOC14 ADC Interrupt Trigger
                                              // Select
#define ADC_INTSOCSEL2_SOC15_S    14
#define ADC_INTSOCSEL2_SOC15_M    0xC000      // SOC15 ADC Interrupt Trigger
                                              // Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCSOCFLG1 register
//
//*****************************************************************************
#define ADC_SOCFLG1_SOC0          0x1         // SOC0 Start of Conversion Flag
#define ADC_SOCFLG1_SOC1          0x2         // SOC1 Start of Conversion Flag
#define ADC_SOCFLG1_SOC2          0x4         // SOC2 Start of Conversion Flag
#define ADC_SOCFLG1_SOC3          0x8         // SOC3 Start of Conversion Flag
#define ADC_SOCFLG1_SOC4          0x10        // SOC4 Start of Conversion Flag
#define ADC_SOCFLG1_SOC5          0x20        // SOC5 Start of Conversion Flag
#define ADC_SOCFLG1_SOC6          0x40        // SOC6 Start of Conversion Flag
#define ADC_SOCFLG1_SOC7          0x80        // SOC7 Start of Conversion Flag
#define ADC_SOCFLG1_SOC8          0x100       // SOC8 Start of Conversion Flag
#define ADC_SOCFLG1_SOC9          0x200       // SOC9 Start of Conversion Flag
#define ADC_SOCFLG1_SOC10         0x400       // SOC10 Start of Conversion Flag
#define ADC_SOCFLG1_SOC11         0x800       // SOC11 Start of Conversion Flag
#define ADC_SOCFLG1_SOC12         0x1000      // SOC12 Start of Conversion Flag
#define ADC_SOCFLG1_SOC13         0x2000      // SOC13 Start of Conversion Flag
#define ADC_SOCFLG1_SOC14         0x4000      // SOC14 Start of Conversion Flag
#define ADC_SOCFLG1_SOC15         0x8000      // SOC15 Start of Conversion Flag

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCSOCFRC1 register
//
//*****************************************************************************
#define ADC_SOCFRC1_SOC0          0x1         // SOC0 Force Start of Conversion
                                              // Bit
#define ADC_SOCFRC1_SOC1          0x2         // SOC1 Force Start of Conversion
                                              // Bit
#define ADC_SOCFRC1_SOC2          0x4         // SOC2 Force Start of Conversion
                                              // Bit
#define ADC_SOCFRC1_SOC3          0x8         // SOC3 Force Start of Conversion
                                              // Bit
#define ADC_SOCFRC1_SOC4          0x10        // SOC4 Force Start of Conversion
                                              // Bit
#define ADC_SOCFRC1_SOC5          0x20        // SOC5 Force Start of Conversion
                                              // Bit
#define ADC_SOCFRC1_SOC6          0x40        // SOC6 Force Start of Conversion
                                              // Bit
#define ADC_SOCFRC1_SOC7          0x80        // SOC7 Force Start of Conversion
                                              // Bit
#define ADC_SOCFRC1_SOC8          0x100       // SOC8 Force Start of Conversion
                                              // Bit
#define ADC_SOCFRC1_SOC9          0x200       // SOC9 Force Start of Conversion
                                              // Bit
#define ADC_SOCFRC1_SOC10         0x400       // SOC10 Force Start of Conversion
                                              // Bit
#define ADC_SOCFRC1_SOC11         0x800       // SOC11 Force Start of Conversion
                                              // Bit
#define ADC_SOCFRC1_SOC12         0x1000      // SOC12 Force Start of Conversion
                                              // Bit
#define ADC_SOCFRC1_SOC13         0x2000      // SOC13 Force Start of Conversion
                                              // Bit
#define ADC_SOCFRC1_SOC14         0x4000      // SOC14 Force Start of Conversion
                                              // Bit
#define ADC_SOCFRC1_SOC15         0x8000      // SOC15 Force Start of Conversion
                                              // Bit

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCSOCOVF1 register
//
//*****************************************************************************
#define ADC_SOCOVF1_SOC0          0x1         // SOC0 Start of Conversion
                                              // Overflow Flag
#define ADC_SOCOVF1_SOC1          0x2         // SOC1 Start of Conversion
                                              // Overflow Flag
#define ADC_SOCOVF1_SOC2          0x4         // SOC2 Start of Conversion
                                              // Overflow Flag
#define ADC_SOCOVF1_SOC3          0x8         // SOC3 Start of Conversion
                                              // Overflow Flag
#define ADC_SOCOVF1_SOC4          0x10        // SOC4 Start of Conversion
                                              // Overflow Flag
#define ADC_SOCOVF1_SOC5          0x20        // SOC5 Start of Conversion
                                              // Overflow Flag
#define ADC_SOCOVF1_SOC6          0x40        // SOC6 Start of Conversion
                                              // Overflow Flag
#define ADC_SOCOVF1_SOC7          0x80        // SOC7 Start of Conversion
                                              // Overflow Flag
#define ADC_SOCOVF1_SOC8          0x100       // SOC8 Start of Conversion
                                              // Overflow Flag
#define ADC_SOCOVF1_SOC9          0x200       // SOC9 Start of Conversion
                                              // Overflow Flag
#define ADC_SOCOVF1_SOC10         0x400       // SOC10 Start of Conversion
                                              // Overflow Flag
#define ADC_SOCOVF1_SOC11         0x800       // SOC11 Start of Conversion
                                              // Overflow Flag
#define ADC_SOCOVF1_SOC12         0x1000      // SOC12 Start of Conversion
                                              // Overflow Flag
#define ADC_SOCOVF1_SOC13         0x2000      // SOC13 Start of Conversion
                                              // Overflow Flag
#define ADC_SOCOVF1_SOC14         0x4000      // SOC14 Start of Conversion
                                              // Overflow Flag
#define ADC_SOCOVF1_SOC15         0x8000      // SOC15 Start of Conversion
                                              // Overflow Flag

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCSOCOVFCLR1 register
//
//*****************************************************************************
#define ADC_SOCOVFCLR1_SOC0       0x1         // SOC0 Clear Start of Conversion
                                              // Overflow Bit
#define ADC_SOCOVFCLR1_SOC1       0x2         // SOC1 Clear Start of Conversion
                                              // Overflow Bit
#define ADC_SOCOVFCLR1_SOC2       0x4         // SOC2 Clear Start of Conversion
                                              // Overflow Bit
#define ADC_SOCOVFCLR1_SOC3       0x8         // SOC3 Clear Start of Conversion
                                              // Overflow Bit
#define ADC_SOCOVFCLR1_SOC4       0x10        // SOC4 Clear Start of Conversion
                                              // Overflow Bit
#define ADC_SOCOVFCLR1_SOC5       0x20        // SOC5 Clear Start of Conversion
                                              // Overflow Bit
#define ADC_SOCOVFCLR1_SOC6       0x40        // SOC6 Clear Start of Conversion
                                              // Overflow Bit
#define ADC_SOCOVFCLR1_SOC7       0x80        // SOC7 Clear Start of Conversion
                                              // Overflow Bit
#define ADC_SOCOVFCLR1_SOC8       0x100       // SOC8 Clear Start of Conversion
                                              // Overflow Bit
#define ADC_SOCOVFCLR1_SOC9       0x200       // SOC9 Clear Start of Conversion
                                              // Overflow Bit
#define ADC_SOCOVFCLR1_SOC10      0x400       // SOC10 Clear Start of Conversion
                                              // Overflow Bit
#define ADC_SOCOVFCLR1_SOC11      0x800       // SOC11 Clear Start of Conversion
                                              // Overflow Bit
#define ADC_SOCOVFCLR1_SOC12      0x1000      // SOC12 Clear Start of Conversion
                                              // Overflow Bit
#define ADC_SOCOVFCLR1_SOC13      0x2000      // SOC13 Clear Start of Conversion
                                              // Overflow Bit
#define ADC_SOCOVFCLR1_SOC14      0x4000      // SOC14 Clear Start of Conversion
                                              // Overflow Bit
#define ADC_SOCOVFCLR1_SOC15      0x8000      // SOC15 Clear Start of Conversion
                                              // Overflow Bit

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCSOC0CTL register
//
//*****************************************************************************
#define ADC_SOC0CTL_ACQPS_S       0
#define ADC_SOC0CTL_ACQPS_M       0x1FF       // SOC Acquisition Prescale
#define ADC_SOC0CTL_CHSEL_S       15
#define ADC_SOC0CTL_CHSEL_M       0x78000     // SOC Channel Select
#define ADC_SOC0CTL_TRIGSEL_S     20
#define ADC_SOC0CTL_TRIGSEL_M     0x1F00000   // SOC Trigger Source Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCSOC1CTL register
//
//*****************************************************************************
#define ADC_SOC1CTL_ACQPS_S       0
#define ADC_SOC1CTL_ACQPS_M       0x1FF       // SOC Acquisition Prescale
#define ADC_SOC1CTL_CHSEL_S       15
#define ADC_SOC1CTL_CHSEL_M       0x78000     // SOC Channel Select
#define ADC_SOC1CTL_TRIGSEL_S     20
#define ADC_SOC1CTL_TRIGSEL_M     0x1F00000   // SOC Trigger Source Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCSOC2CTL register
//
//*****************************************************************************
#define ADC_SOC2CTL_ACQPS_S       0
#define ADC_SOC2CTL_ACQPS_M       0x1FF       // SOC Acquisition Prescale
#define ADC_SOC2CTL_CHSEL_S       15
#define ADC_SOC2CTL_CHSEL_M       0x78000     // SOC Channel Select
#define ADC_SOC2CTL_TRIGSEL_S     20
#define ADC_SOC2CTL_TRIGSEL_M     0x1F00000   // SOC Trigger Source Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCSOC3CTL register
//
//*****************************************************************************
#define ADC_SOC3CTL_ACQPS_S       0
#define ADC_SOC3CTL_ACQPS_M       0x1FF       // SOC Acquisition Prescale
#define ADC_SOC3CTL_CHSEL_S       15
#define ADC_SOC3CTL_CHSEL_M       0x78000     // SOC Channel Select
#define ADC_SOC3CTL_TRIGSEL_S     20
#define ADC_SOC3CTL_TRIGSEL_M     0x1F00000   // SOC Trigger Source Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCSOC4CTL register
//
//*****************************************************************************
#define ADC_SOC4CTL_ACQPS_S       0
#define ADC_SOC4CTL_ACQPS_M       0x1FF       // SOC Acquisition Prescale
#define ADC_SOC4CTL_CHSEL_S       15
#define ADC_SOC4CTL_CHSEL_M       0x78000     // SOC Channel Select
#define ADC_SOC4CTL_TRIGSEL_S     20
#define ADC_SOC4CTL_TRIGSEL_M     0x1F00000   // SOC Trigger Source Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCSOC5CTL register
//
//*****************************************************************************
#define ADC_SOC5CTL_ACQPS_S       0
#define ADC_SOC5CTL_ACQPS_M       0x1FF       // SOC Acquisition Prescale
#define ADC_SOC5CTL_CHSEL_S       15
#define ADC_SOC5CTL_CHSEL_M       0x78000     // SOC Channel Select
#define ADC_SOC5CTL_TRIGSEL_S     20
#define ADC_SOC5CTL_TRIGSEL_M     0x1F00000   // SOC Trigger Source Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCSOC6CTL register
//
//*****************************************************************************
#define ADC_SOC6CTL_ACQPS_S       0
#define ADC_SOC6CTL_ACQPS_M       0x1FF       // SOC Acquisition Prescale
#define ADC_SOC6CTL_CHSEL_S       15
#define ADC_SOC6CTL_CHSEL_M       0x78000     // SOC Channel Select
#define ADC_SOC6CTL_TRIGSEL_S     20
#define ADC_SOC6CTL_TRIGSEL_M     0x1F00000   // SOC Trigger Source Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCSOC7CTL register
//
//*****************************************************************************
#define ADC_SOC7CTL_ACQPS_S       0
#define ADC_SOC7CTL_ACQPS_M       0x1FF       // SOC Acquisition Prescale
#define ADC_SOC7CTL_CHSEL_S       15
#define ADC_SOC7CTL_CHSEL_M       0x78000     // SOC Channel Select
#define ADC_SOC7CTL_TRIGSEL_S     20
#define ADC_SOC7CTL_TRIGSEL_M     0x1F00000   // SOC Trigger Source Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCSOC8CTL register
//
//*****************************************************************************
#define ADC_SOC8CTL_ACQPS_S       0
#define ADC_SOC8CTL_ACQPS_M       0x1FF       // SOC Acquisition Prescale
#define ADC_SOC8CTL_CHSEL_S       15
#define ADC_SOC8CTL_CHSEL_M       0x78000     // SOC Channel Select
#define ADC_SOC8CTL_TRIGSEL_S     20
#define ADC_SOC8CTL_TRIGSEL_M     0x1F00000   // SOC Trigger Source Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCSOC9CTL register
//
//*****************************************************************************
#define ADC_SOC9CTL_ACQPS_S       0
#define ADC_SOC9CTL_ACQPS_M       0x1FF       // SOC Acquisition Prescale
#define ADC_SOC9CTL_CHSEL_S       15
#define ADC_SOC9CTL_CHSEL_M       0x78000     // SOC Channel Select
#define ADC_SOC9CTL_TRIGSEL_S     20
#define ADC_SOC9CTL_TRIGSEL_M     0x1F00000   // SOC Trigger Source Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCSOC10CTL register
//
//*****************************************************************************
#define ADC_SOC10CTL_ACQPS_S      0
#define ADC_SOC10CTL_ACQPS_M      0x1FF       // SOC Acquisition Prescale
#define ADC_SOC10CTL_CHSEL_S      15
#define ADC_SOC10CTL_CHSEL_M      0x78000     // SOC Channel Select
#define ADC_SOC10CTL_TRIGSEL_S    20
#define ADC_SOC10CTL_TRIGSEL_M    0x1F00000   // SOC Trigger Source Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCSOC11CTL register
//
//*****************************************************************************
#define ADC_SOC11CTL_ACQPS_S      0
#define ADC_SOC11CTL_ACQPS_M      0x1FF       // SOC Acquisition Prescale
#define ADC_SOC11CTL_CHSEL_S      15
#define ADC_SOC11CTL_CHSEL_M      0x78000     // SOC Channel Select
#define ADC_SOC11CTL_TRIGSEL_S    20
#define ADC_SOC11CTL_TRIGSEL_M    0x1F00000   // SOC Trigger Source Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCSOC12CTL register
//
//*****************************************************************************
#define ADC_SOC12CTL_ACQPS_S      0
#define ADC_SOC12CTL_ACQPS_M      0x1FF       // SOC Acquisition Prescale
#define ADC_SOC12CTL_CHSEL_S      15
#define ADC_SOC12CTL_CHSEL_M      0x78000     // SOC Channel Select
#define ADC_SOC12CTL_TRIGSEL_S    20
#define ADC_SOC12CTL_TRIGSEL_M    0x1F00000   // SOC Trigger Source Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCSOC13CTL register
//
//*****************************************************************************
#define ADC_SOC13CTL_ACQPS_S      0
#define ADC_SOC13CTL_ACQPS_M      0x1FF       // SOC Acquisition Prescale
#define ADC_SOC13CTL_CHSEL_S      15
#define ADC_SOC13CTL_CHSEL_M      0x78000     // SOC Channel Select
#define ADC_SOC13CTL_TRIGSEL_S    20
#define ADC_SOC13CTL_TRIGSEL_M    0x1F00000   // SOC Trigger Source Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCSOC14CTL register
//
//*****************************************************************************
#define ADC_SOC14CTL_ACQPS_S      0
#define ADC_SOC14CTL_ACQPS_M      0x1FF       // SOC Acquisition Prescale
#define ADC_SOC14CTL_CHSEL_S      15
#define ADC_SOC14CTL_CHSEL_M      0x78000     // SOC Channel Select
#define ADC_SOC14CTL_TRIGSEL_S    20
#define ADC_SOC14CTL_TRIGSEL_M    0x1F00000   // SOC Trigger Source Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCSOC15CTL register
//
//*****************************************************************************
#define ADC_SOC15CTL_ACQPS_S      0
#define ADC_SOC15CTL_ACQPS_M      0x1FF       // SOC Acquisition Prescale
#define ADC_SOC15CTL_CHSEL_S      15
#define ADC_SOC15CTL_CHSEL_M      0x78000     // SOC Channel Select
#define ADC_SOC15CTL_TRIGSEL_S    20
#define ADC_SOC15CTL_TRIGSEL_M    0x1F00000   // SOC Trigger Source Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCEVTSTAT register
//
//*****************************************************************************
#define ADC_EVTSTAT_PPB1TRIPHI    0x1         // Post Processing Block 1 Trip
                                              // High Flag
#define ADC_EVTSTAT_PPB1TRIPLO    0x2         // Post Processing Block 1 Trip
                                              // Low Flag
#define ADC_EVTSTAT_PPB1ZERO      0x4         // Post Processing Block 1 Zero
                                              // Crossing Flag
#define ADC_EVTSTAT_PPB2TRIPHI    0x10        // Post Processing Block 2 Trip
                                              // High Flag
#define ADC_EVTSTAT_PPB2TRIPLO    0x20        // Post Processing Block 2 Trip
                                              // Low Flag
#define ADC_EVTSTAT_PPB2ZERO      0x40        // Post Processing Block 2 Zero
                                              // Crossing Flag
#define ADC_EVTSTAT_PPB3TRIPHI    0x100       // Post Processing Block 3 Trip
                                              // High Flag
#define ADC_EVTSTAT_PPB3TRIPLO    0x200       // Post Processing Block 3 Trip
                                              // Low Flag
#define ADC_EVTSTAT_PPB3ZERO      0x400       // Post Processing Block 3 Zero
                                              // Crossing Flag
#define ADC_EVTSTAT_PPB4TRIPHI    0x1000      // Post Processing Block 4 Trip
                                              // High Flag
#define ADC_EVTSTAT_PPB4TRIPLO    0x2000      // Post Processing Block 4 Trip
                                              // Low Flag
#define ADC_EVTSTAT_PPB4ZERO      0x4000      // Post Processing Block 4 Zero
                                              // Crossing Flag

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCEVTCLR register
//
//*****************************************************************************
#define ADC_EVTCLR_PPB1TRIPHI     0x1         // Post Processing Block 1 Trip
                                              // High Clear
#define ADC_EVTCLR_PPB1TRIPLO     0x2         // Post Processing Block 1 Trip
                                              // Low Clear
#define ADC_EVTCLR_PPB1ZERO       0x4         // Post Processing Block 1 Zero
                                              // Crossing Clear
#define ADC_EVTCLR_PPB2TRIPHI     0x10        // Post Processing Block 2 Trip
                                              // High Clear
#define ADC_EVTCLR_PPB2TRIPLO     0x20        // Post Processing Block 2 Trip
                                              // Low Clear
#define ADC_EVTCLR_PPB2ZERO       0x40        // Post Processing Block 2 Zero
                                              // Crossing Clear
#define ADC_EVTCLR_PPB3TRIPHI     0x100       // Post Processing Block 3 Trip
                                              // High Clear
#define ADC_EVTCLR_PPB3TRIPLO     0x200       // Post Processing Block 3 Trip
                                              // Low Clear
#define ADC_EVTCLR_PPB3ZERO       0x400       // Post Processing Block 3 Zero
                                              // Crossing Clear
#define ADC_EVTCLR_PPB4TRIPHI     0x1000      // Post Processing Block 4 Trip
                                              // High Clear
#define ADC_EVTCLR_PPB4TRIPLO     0x2000      // Post Processing Block 4 Trip
                                              // Low Clear
#define ADC_EVTCLR_PPB4ZERO       0x4000      // Post Processing Block 4 Zero
                                              // Crossing Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCEVTSEL register
//
//*****************************************************************************
#define ADC_EVTSEL_PPB1TRIPHI     0x1         // Post Processing Block 1 Trip
                                              // High Event Enable
#define ADC_EVTSEL_PPB1TRIPLO     0x2         // Post Processing Block 1 Trip
                                              // Low Event Enable
#define ADC_EVTSEL_PPB1ZERO       0x4         // Post Processing Block 1 Zero
                                              // Crossing Event Enable
#define ADC_EVTSEL_PPB2TRIPHI     0x10        // Post Processing Block 2 Trip
                                              // High Event Enable
#define ADC_EVTSEL_PPB2TRIPLO     0x20        // Post Processing Block 2 Trip
                                              // Low Event Enable
#define ADC_EVTSEL_PPB2ZERO       0x40        // Post Processing Block 2 Zero
                                              // Crossing Event Enable
#define ADC_EVTSEL_PPB3TRIPHI     0x100       // Post Processing Block 3 Trip
                                              // High Event Enable
#define ADC_EVTSEL_PPB3TRIPLO     0x200       // Post Processing Block 3 Trip
                                              // Low Event Enable
#define ADC_EVTSEL_PPB3ZERO       0x400       // Post Processing Block 3 Zero
                                              // Crossing Event Enable
#define ADC_EVTSEL_PPB4TRIPHI     0x1000      // Post Processing Block 4 Trip
                                              // High Event Enable
#define ADC_EVTSEL_PPB4TRIPLO     0x2000      // Post Processing Block 4 Trip
                                              // Low Event Enable
#define ADC_EVTSEL_PPB4ZERO       0x4000      // Post Processing Block 4 Zero
                                              // Crossing Event Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCEVTINTSEL register
//
//*****************************************************************************
#define ADC_EVTINTSEL_PPB1TRIPHI  0x1         // Post Processing Block 1 Trip
                                              // High Interrupt Enable
#define ADC_EVTINTSEL_PPB1TRIPLO  0x2         // Post Processing Block 1 Trip
                                              // Low Interrupt Enable
#define ADC_EVTINTSEL_PPB1ZERO    0x4         // Post Processing Block 1 Zero
                                              // Crossing Interrupt Enable
#define ADC_EVTINTSEL_PPB2TRIPHI  0x10        // Post Processing Block 2 Trip
                                              // High Interrupt Enable
#define ADC_EVTINTSEL_PPB2TRIPLO  0x20        // Post Processing Block 2 Trip
                                              // Low Interrupt Enable
#define ADC_EVTINTSEL_PPB2ZERO    0x40        // Post Processing Block 2 Zero
                                              // Crossing Interrupt Enable
#define ADC_EVTINTSEL_PPB3TRIPHI  0x100       // Post Processing Block 3 Trip
                                              // High Interrupt Enable
#define ADC_EVTINTSEL_PPB3TRIPLO  0x200       // Post Processing Block 3 Trip
                                              // Low Interrupt Enable
#define ADC_EVTINTSEL_PPB3ZERO    0x400       // Post Processing Block 3 Zero
                                              // Crossing Interrupt Enable
#define ADC_EVTINTSEL_PPB4TRIPHI  0x1000      // Post Processing Block 4 Trip
                                              // High Interrupt Enable
#define ADC_EVTINTSEL_PPB4TRIPLO  0x2000      // Post Processing Block 4 Trip
                                              // Low Interrupt Enable
#define ADC_EVTINTSEL_PPB4ZERO    0x4000      // Post Processing Block 4 Zero
                                              // Crossing Interrupt Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCCOUNTER register
//
//*****************************************************************************
#define ADC_COUNTER_FREECOUNT_S   0
#define ADC_COUNTER_FREECOUNT_M   0xFFF       // ADC Free Running Counter Value

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCREV register
//
//*****************************************************************************
#define ADC_REV_TYPE_S            0
#define ADC_REV_TYPE_M            0xFF        // ADC Type
#define ADC_REV_REV_S             8
#define ADC_REV_REV_M             0xFF00      // ADC Revision

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCOFFTRIM register
//
//*****************************************************************************
#define ADC_OFFTRIM_OFFTRIM_S     0
#define ADC_OFFTRIM_OFFTRIM_M     0xFF        // ADC Offset Trim

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1CONFIG register
//
//*****************************************************************************
#define ADC_PPB1CONFIG_CONFIG_S   0
#define ADC_PPB1CONFIG_CONFIG_M   0xF         // ADC Post Processing Block
                                              // Configuration
#define ADC_PPB1CONFIG_TWOSCOMPEN  0x10        // ADC Post Processing Block Two's
                                              // Complement Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1STAMP register
//
//*****************************************************************************
#define ADC_PPB1STAMP_DLYSTAMP_S  0
#define ADC_PPB1STAMP_DLYSTAMP_M  0xFFF       // ADC Post Processing Block Delay
                                              // Time Stamp

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1OFFCAL register
//
//*****************************************************************************
#define ADC_PPB1OFFCAL_OFFCAL_S   0
#define ADC_PPB1OFFCAL_OFFCAL_M   0x3FF       // ADC Post Processing Block
                                              // Offset Correction

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1OFFREF register
//
//*****************************************************************************
#define ADC_PPB1OFFREF_OFFREF_S   0
#define ADC_PPB1OFFREF_OFFREF_M   0xFFFF      // ADC Post Processing Block
                                              // Offset Reference

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1TRIPHI register
//
//*****************************************************************************
#define ADC_PPB1TRIPHI_LIMITHI_S  0
#define ADC_PPB1TRIPHI_LIMITHI_M  0xFFFF      // ADC Post Processing Block Trip
                                              // High Limit
#define ADC_PPB1TRIPHI_HSIGN      0x10000     // High Limit Sign Bit

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1TRIPLO register
//
//*****************************************************************************
#define ADC_PPB1TRIPLO_LIMITLO_S  0
#define ADC_PPB1TRIPLO_LIMITLO_M  0xFFFF      // ADC Post Processing Block Trip
                                              // Low Limit
#define ADC_PPB1TRIPLO_LSIGN      0x10000     // Low Limit Sign Bit
#define ADC_PPB1TRIPLO_REQSTAMP_S  20
#define ADC_PPB1TRIPLO_REQSTAMP_M  0xFFF00000  // ADC Post Processing Block
                                              // Request Time Stamp

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2CONFIG register
//
//*****************************************************************************
#define ADC_PPB2CONFIG_CONFIG_S   0
#define ADC_PPB2CONFIG_CONFIG_M   0xF         // ADC Post Processing Block
                                              // Configuration
#define ADC_PPB2CONFIG_TWOSCOMPEN  0x10        // ADC Post Processing Block Two's
                                              // Complement Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2STAMP register
//
//*****************************************************************************
#define ADC_PPB2STAMP_DLYSTAMP_S  0
#define ADC_PPB2STAMP_DLYSTAMP_M  0xFFF       // ADC Post Processing Block Delay
                                              // Time Stamp

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2OFFCAL register
//
//*****************************************************************************
#define ADC_PPB2OFFCAL_OFFCAL_S   0
#define ADC_PPB2OFFCAL_OFFCAL_M   0x3FF       // ADC Post Processing Block
                                              // Offset Correction

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2OFFREF register
//
//*****************************************************************************
#define ADC_PPB2OFFREF_OFFREF_S   0
#define ADC_PPB2OFFREF_OFFREF_M   0xFFFF      // ADC Post Processing Block
                                              // Offset Reference

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2TRIPHI register
//
//*****************************************************************************
#define ADC_PPB2TRIPHI_LIMITHI_S  0
#define ADC_PPB2TRIPHI_LIMITHI_M  0xFFFF      // ADC Post Processing Block Trip
                                              // High Limit
#define ADC_PPB2TRIPHI_HSIGN      0x10000     // High Limit Sign Bit

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2TRIPLO register
//
//*****************************************************************************
#define ADC_PPB2TRIPLO_LIMITLO_S  0
#define ADC_PPB2TRIPLO_LIMITLO_M  0xFFFF      // ADC Post Processing Block Trip
                                              // Low Limit
#define ADC_PPB2TRIPLO_LSIGN      0x10000     // Low Limit Sign Bit
#define ADC_PPB2TRIPLO_REQSTAMP_S  20
#define ADC_PPB2TRIPLO_REQSTAMP_M  0xFFF00000  // ADC Post Processing Block
                                              // Request Time Stamp

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3CONFIG register
//
//*****************************************************************************
#define ADC_PPB3CONFIG_CONFIG_S   0
#define ADC_PPB3CONFIG_CONFIG_M   0xF         // ADC Post Processing Block
                                              // Configuration
#define ADC_PPB3CONFIG_TWOSCOMPEN  0x10        // ADC Post Processing Block Two's
                                              // Complement Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3STAMP register
//
//*****************************************************************************
#define ADC_PPB3STAMP_DLYSTAMP_S  0
#define ADC_PPB3STAMP_DLYSTAMP_M  0xFFF       // ADC Post Processing Block Delay
                                              // Time Stamp

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3OFFCAL register
//
//*****************************************************************************
#define ADC_PPB3OFFCAL_OFFCAL_S   0
#define ADC_PPB3OFFCAL_OFFCAL_M   0x3FF       // ADC Post Processing Block
                                              // Offset Correction

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3OFFREF register
//
//*****************************************************************************
#define ADC_PPB3OFFREF_OFFREF_S   0
#define ADC_PPB3OFFREF_OFFREF_M   0xFFFF      // ADC Post Processing Block
                                              // Offset Reference

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3TRIPHI register
//
//*****************************************************************************
#define ADC_PPB3TRIPHI_LIMITHI_S  0
#define ADC_PPB3TRIPHI_LIMITHI_M  0xFFFF      // ADC Post Processing Block Trip
                                              // High Limit
#define ADC_PPB3TRIPHI_HSIGN      0x10000     // High Limit Sign Bit

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3TRIPLO register
//
//*****************************************************************************
#define ADC_PPB3TRIPLO_LIMITLO_S  0
#define ADC_PPB3TRIPLO_LIMITLO_M  0xFFFF      // ADC Post Processing Block Trip
                                              // Low Limit
#define ADC_PPB3TRIPLO_LSIGN      0x10000     // Low Limit Sign Bit
#define ADC_PPB3TRIPLO_REQSTAMP_S  20
#define ADC_PPB3TRIPLO_REQSTAMP_M  0xFFF00000  // ADC Post Processing Block
                                              // Request Time Stamp

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4CONFIG register
//
//*****************************************************************************
#define ADC_PPB4CONFIG_CONFIG_S   0
#define ADC_PPB4CONFIG_CONFIG_M   0xF         // ADC Post Processing Block
                                              // Configuration
#define ADC_PPB4CONFIG_TWOSCOMPEN  0x10        // ADC Post Processing Block Two's
                                              // Complement Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4STAMP register
//
//*****************************************************************************
#define ADC_PPB4STAMP_DLYSTAMP_S  0
#define ADC_PPB4STAMP_DLYSTAMP_M  0xFFF       // ADC Post Processing Block Delay
                                              // Time Stamp

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4OFFCAL register
//
//*****************************************************************************
#define ADC_PPB4OFFCAL_OFFCAL_S   0
#define ADC_PPB4OFFCAL_OFFCAL_M   0x3FF       // ADC Post Processing Block
                                              // Offset Correction

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4OFFREF register
//
//*****************************************************************************
#define ADC_PPB4OFFREF_OFFREF_S   0
#define ADC_PPB4OFFREF_OFFREF_M   0xFFFF      // ADC Post Processing Block
                                              // Offset Reference

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4TRIPHI register
//
//*****************************************************************************
#define ADC_PPB4TRIPHI_LIMITHI_S  0
#define ADC_PPB4TRIPHI_LIMITHI_M  0xFFFF      // ADC Post Processing Block Trip
                                              // High Limit
#define ADC_PPB4TRIPHI_HSIGN      0x10000     // High Limit Sign Bit

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4TRIPLO register
//
//*****************************************************************************
#define ADC_PPB4TRIPLO_LIMITLO_S  0
#define ADC_PPB4TRIPLO_LIMITLO_M  0xFFFF      // ADC Post Processing Block Trip
                                              // Low Limit
#define ADC_PPB4TRIPLO_LSIGN      0x10000     // Low Limit Sign Bit
#define ADC_PPB4TRIPLO_REQSTAMP_S  20
#define ADC_PPB4TRIPLO_REQSTAMP_M  0xFFF00000  // ADC Post Processing Block
                                              // Request Time Stamp

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT0 register
//
//*****************************************************************************
#define ADC_RESULT0_RESULT_S      0
#define ADC_RESULT0_RESULT_M      0xFFFF      // ADC Result

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT1 register
//
//*****************************************************************************
#define ADC_RESULT1_RESULT_S      0
#define ADC_RESULT1_RESULT_M      0xFFFF      // ADC Result

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT2 register
//
//*****************************************************************************
#define ADC_RESULT2_RESULT_S      0
#define ADC_RESULT2_RESULT_M      0xFFFF      // ADC Result

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT3 register
//
//*****************************************************************************
#define ADC_RESULT3_RESULT_S      0
#define ADC_RESULT3_RESULT_M      0xFFFF      // ADC Result

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT4 register
//
//*****************************************************************************
#define ADC_RESULT4_RESULT_S      0
#define ADC_RESULT4_RESULT_M      0xFFFF      // ADC Result

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT5 register
//
//*****************************************************************************
#define ADC_RESULT5_RESULT_S      0
#define ADC_RESULT5_RESULT_M      0xFFFF      // ADC Result

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT6 register
//
//*****************************************************************************
#define ADC_RESULT6_RESULT_S      0
#define ADC_RESULT6_RESULT_M      0xFFFF      // ADC Result

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT7 register
//
//*****************************************************************************
#define ADC_RESULT7_RESULT_S      0
#define ADC_RESULT7_RESULT_M      0xFFFF      // ADC Result

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT8 register
//
//*****************************************************************************
#define ADC_RESULT8_RESULT_S      0
#define ADC_RESULT8_RESULT_M      0xFFFF      // ADC Result

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT9 register
//
//*****************************************************************************
#define ADC_RESULT9_RESULT_S      0
#define ADC_RESULT9_RESULT_M      0xFFFF      // ADC Result

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT10 register
//
//*****************************************************************************
#define ADC_RESULT10_RESULT_S     0
#define ADC_RESULT10_RESULT_M     0xFFFF      // ADC Result

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT11 register
//
//*****************************************************************************
#define ADC_RESULT11_RESULT_S     0
#define ADC_RESULT11_RESULT_M     0xFFFF      // ADC Result

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT12 register
//
//*****************************************************************************
#define ADC_RESULT12_RESULT_S     0
#define ADC_RESULT12_RESULT_M     0xFFFF      // ADC Result

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT13 register
//
//*****************************************************************************
#define ADC_RESULT13_RESULT_S     0
#define ADC_RESULT13_RESULT_M     0xFFFF      // ADC Result

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT14 register
//
//*****************************************************************************
#define ADC_RESULT14_RESULT_S     0
#define ADC_RESULT14_RESULT_M     0xFFFF      // ADC Result

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCRESULT15 register
//
//*****************************************************************************
#define ADC_RESULT15_RESULT_S     0
#define ADC_RESULT15_RESULT_M     0xFFFF      // ADC Result

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB1RESULT register
//
//*****************************************************************************
#define ADC_PPB1RESULT_PPBRESULT_S  0
#define ADC_PPB1RESULT_PPBRESULT_M  0xFFFF      // ADC Post Processing Block
                                              // Result
#define ADC_PPB1RESULT_SIGN_S     16
#define ADC_PPB1RESULT_SIGN_M     0xFFFF0000  // Sign Extended Bits

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB2RESULT register
//
//*****************************************************************************
#define ADC_PPB2RESULT_PPBRESULT_S  0
#define ADC_PPB2RESULT_PPBRESULT_M  0xFFFF      // ADC Post Processing Block
                                              // Result
#define ADC_PPB2RESULT_SIGN_S     16
#define ADC_PPB2RESULT_SIGN_M     0xFFFF0000  // Sign Extended Bits

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB3RESULT register
//
//*****************************************************************************
#define ADC_PPB3RESULT_PPBRESULT_S  0
#define ADC_PPB3RESULT_PPBRESULT_M  0xFFFF      // ADC Post Processing Block
                                              // Result
#define ADC_PPB3RESULT_SIGN_S     16
#define ADC_PPB3RESULT_SIGN_M     0xFFFF0000  // Sign Extended Bits

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCPPB4RESULT register
//
//*****************************************************************************
#define ADC_PPB4RESULT_PPBRESULT_S  0
#define ADC_PPB4RESULT_PPBRESULT_M  0xFFFF      // ADC Post Processing Block
                                              // Result
#define ADC_PPB4RESULT_SIGN_S     16
#define ADC_PPB4RESULT_SIGN_M     0xFFFF0000  // Sign Extended Bits
#endif
