//*****************************************************************************
//
// hw_gpio.h - Defines and Macros for GPIO hardware.
//
// Copyright (c) 2005-2010 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 6459 of the Stellaris Firmware Development Package.
//
//*****************************************************************************

#ifndef __HW_GPIO_H__
#define __HW_GPIO_H__

//*****************************************************************************
//
// The following are defines for the GPIO register offsets.
//
//*****************************************************************************
#define GPIO_O_DATA             0x00000000  // GPIO Data
#define GPIO_O_DIR              0x00000400  // GPIO Direction
#define GPIO_O_IS               0x00000404  // GPIO Interrupt Sense
#define GPIO_O_IBE              0x00000408  // GPIO Interrupt Both Edges
#define GPIO_O_IEV              0x0000040C  // GPIO Interrupt Event
#define GPIO_O_IM               0x00000410  // GPIO Interrupt Mask
#define GPIO_O_RIS              0x00000414  // GPIO Raw Interrupt Status
#define GPIO_O_MIS              0x00000418  // GPIO Masked Interrupt Status
#define GPIO_O_ICR              0x0000041C  // GPIO Interrupt Clear
#define GPIO_O_AFSEL            0x00000420  // GPIO Alternate Function Select
#define GPIO_O_DR2R             0x00000500  // GPIO 2-mA Drive Select
#define GPIO_O_DR4R             0x00000504  // GPIO 4-mA Drive Select
#define GPIO_O_DR8R             0x00000508  // GPIO 8-mA Drive Select
#define GPIO_O_ODR              0x0000050C  // GPIO Open Drain Select
#define GPIO_O_PUR              0x00000510  // GPIO Pull-Up Select
#define GPIO_O_PDR              0x00000514  // GPIO Pull-Down Select
#define GPIO_O_SLR              0x00000518  // GPIO Slew Rate Control Select
#define GPIO_O_DEN              0x0000051C  // GPIO Digital Enable
#define GPIO_O_LOCK             0x00000520  // GPIO Lock
#define GPIO_O_CR               0x00000524  // GPIO Commit
#define GPIO_O_AMSEL            0x00000528  // GPIO Analog Mode Select
#define GPIO_O_PCTL             0x0000052C  // GPIO Port Control

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_O_LOCK register.
//
//*****************************************************************************
#define GPIO_LOCK_M             0xFFFFFFFF  // GPIO Lock
#define GPIO_LOCK_UNLOCKED      0x00000000  // The GPIOCR register is unlocked
                                            // and may be modified
#define GPIO_LOCK_LOCKED        0x00000001  // The GPIOCR register is locked
                                            // and may not be modified
#define GPIO_LOCK_KEY           0x1ACCE551  // Unlocks the GPIO_CR register
#define GPIO_LOCK_KEY_DD        0x4C4F434B  // Unlocks the GPIO_CR register on
                                            // DustDevil-class devices and
                                            // later

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_PCTL register for
// port A.
//
//*****************************************************************************
#define GPIO_PCTL_PA0_M         0x0000000F  // PA0 mask
#define GPIO_PCTL_PA0_U0RX      0x00000001  // U0RX on PA0
#define GPIO_PCTL_PA0_I2C1SCL   0x00000008  // I2C1SCL on PA0
#define GPIO_PCTL_PA0_U1RX      0x00000009  // U1RX on PA0
#define GPIO_PCTL_PA1_M         0x000000F0  // PA1 mask
#define GPIO_PCTL_PA1_U0TX      0x00000010  // U0TX on PA1
#define GPIO_PCTL_PA1_I2C1SDA   0x00000080  // I2C1SDA on PA1
#define GPIO_PCTL_PA1_U1TX      0x00000090  // U1TX on PA1
#define GPIO_PCTL_PA2_M         0x00000F00  // PA2 mask
#define GPIO_PCTL_PA2_SSI0CLK   0x00000100  // SSI0CLK on PA2
#define GPIO_PCTL_PA2_PWM4      0x00000400  // PWM4 on PA2
#define GPIO_PCTL_PA2_I2S0RXSD  0x00000900  // I2S0RXSD on PA2
#define GPIO_PCTL_PA3_M         0x0000F000  // PA3 mask
#define GPIO_PCTL_PA3_SSI0FSS   0x00001000  // SSI0FSS on PA3
#define GPIO_PCTL_PA3_PWM5      0x00004000  // PWM5 on PA3
#define GPIO_PCTL_PA3_I2S0RXMCLK \
                                0x00009000  // I2S0RXMCLK on PA3
#define GPIO_PCTL_PA4_M         0x000F0000  // PA4 mask
#define GPIO_PCTL_PA4_SSI0RX    0x00010000  // SSI0RX on PA4
#define GPIO_PCTL_PA4_PWM6      0x00040000  // PWM6 on PA4
#define GPIO_PCTL_PA4_CAN0RX    0x00050000  // CAN0RX on PA4
#define GPIO_PCTL_PA4_I2S0TXSCK 0x00090000  // I2S0TXSCK on PA4
#define GPIO_PCTL_PA5_M         0x00F00000  // PA5 mask
#define GPIO_PCTL_PA5_SSI0TX    0x00100000  // SSI0TX on PA5
#define GPIO_PCTL_PA5_PWM7      0x00400000  // PWM7 on PA5
#define GPIO_PCTL_PA5_CAN0TX    0x00500000  // CAN0TX on PA5
#define GPIO_PCTL_PA5_I2S0TXWS  0x00900000  // I2S0TXWS on PA5
#define GPIO_PCTL_PA6_M         0x0F000000  // PA6 mask
#define GPIO_PCTL_PA6_I2C1SCL   0x01000000  // I2C1SCL on PA6
#define GPIO_PCTL_PA6_CCP1      0x02000000  // CCP1 on PA6
#define GPIO_PCTL_PA6_PWM0      0x04000000  // PWM0 on PA6
#define GPIO_PCTL_PA6_PWM4      0x05000000  // PWM4 on PA6
#define GPIO_PCTL_PA6_CAN0RX    0x06000000  // CAN0RX on PA6
#define GPIO_PCTL_PA6_USB0EPEN  0x08000000  // USB0EPEN on PA6
#define GPIO_PCTL_PA6_U1CTS     0x09000000  // U1CTS on PA6
#define GPIO_PCTL_PA7_M         0xF0000000  // PA7 mask
#define GPIO_PCTL_PA7_I2C1SDA   0x10000000  // I2C1SDA on PA7
#define GPIO_PCTL_PA7_CCP4      0x20000000  // CCP4 on PA7
#define GPIO_PCTL_PA7_PWM1      0x40000000  // PWM1 on PA7
#define GPIO_PCTL_PA7_PWM5      0x50000000  // PWM5 on PA7
#define GPIO_PCTL_PA7_CAN0TX    0x60000000  // CAN0TX on PA7
#define GPIO_PCTL_PA7_CCP3      0x70000000  // CCP3 on PA7
#define GPIO_PCTL_PA7_USB0PFLT  0x80000000  // USB0PFLT on PA7
#define GPIO_PCTL_PA7_U1DCD     0x90000000  // U1DCD on PA7

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_PCTL register for
// port B.
//
//*****************************************************************************
#define GPIO_PCTL_PB0_M         0x0000000F  // PB0 mask
#define GPIO_PCTL_PB0_CCP0      0x00000001  // CCP0 on PB0
#define GPIO_PCTL_PB0_PWM2      0x00000002  // PWM2 on PB0
#define GPIO_PCTL_PB0_U1RX      0x00000005  // U1RX on PB0
#define GPIO_PCTL_PB1_M         0x000000F0  // PB1 mask
#define GPIO_PCTL_PB1_CCP2      0x00000010  // CCP2 on PB1
#define GPIO_PCTL_PB1_PWM3      0x00000020  // PWM3 on PB1
#define GPIO_PCTL_PB1_CCP1      0x00000040  // CCP1 on PB1
#define GPIO_PCTL_PB1_U1TX      0x00000050  // U1TX on PB1
#define GPIO_PCTL_PB2_M         0x00000F00  // PB2 mask
#define GPIO_PCTL_PB2_I2C0SCL   0x00000100  // I2C0SCL on PB2
#define GPIO_PCTL_PB2_IDX0      0x00000200  // IDX0 on PB2
#define GPIO_PCTL_PB2_CCP3      0x00000400  // CCP3 on PB2
#define GPIO_PCTL_PB2_CCP0      0x00000500  // CCP0 on PB2
#define GPIO_PCTL_PB2_USB0EPEN  0x00000800  // USB0EPEN on PB2
#define GPIO_PCTL_PB3_M         0x0000F000  // PB3 mask
#define GPIO_PCTL_PB3_I2C0SDA   0x00001000  // I2C0SDA on PB3
#define GPIO_PCTL_PB3_FAULT0    0x00002000  // FAULT0 on PB3
#define GPIO_PCTL_PB3_FAULT3    0x00004000  // FAULT3 on PB3
#define GPIO_PCTL_PB3_USB0PFLT  0x00008000  // USB0PFLT on PB3
#define GPIO_PCTL_PB4_M         0x000F0000  // PB4 mask
#define GPIO_PCTL_PB4_U2RX      0x00040000  // U2RX on PB4
#define GPIO_PCTL_PB4_CAN0RX    0x00050000  // CAN0RX on PB4
#define GPIO_PCTL_PB4_IDX0      0x00060000  // IDX0 on PB4
#define GPIO_PCTL_PB4_U1RX      0x00070000  // U1RX on PB4
#define GPIO_PCTL_PB4_EPI0S23   0x00080000  // EPI0S23 on PB4
#define GPIO_PCTL_PB5_M         0x00F00000  // PB5 mask
#define GPIO_PCTL_PB5_C0O       0x00100000  // C0O on PB5
#define GPIO_PCTL_PB5_CCP5      0x00200000  // CCP5 on PB5
#define GPIO_PCTL_PB5_CCP6      0x00300000  // CCP6 on PB5
#define GPIO_PCTL_PB5_CCP0      0x00400000  // CCP0 on PB5
#define GPIO_PCTL_PB5_CAN0TX    0x00500000  // CAN0TX on PB5
#define GPIO_PCTL_PB5_CCP2      0x00600000  // CCP2 on PB5
#define GPIO_PCTL_PB5_U1TX      0x00700000  // U1TX on PB5
#define GPIO_PCTL_PB5_EPI0S22   0x00800000  // EPI0S22 on PB5
#define GPIO_PCTL_PB6_M         0x0F000000  // PB6 mask
#define GPIO_PCTL_PB6_CCP1      0x01000000  // CCP1 on PB6
#define GPIO_PCTL_PB6_CCP7      0x02000000  // CCP7 on PB6
#define GPIO_PCTL_PB6_C0O       0x03000000  // C0O on PB6
#define GPIO_PCTL_PB6_FAULT1    0x04000000  // FAULT1 on PB6
#define GPIO_PCTL_PB6_IDX0      0x05000000  // IDX0 on PB6
#define GPIO_PCTL_PB6_CCP5      0x06000000  // CCP5 on PB6
#define GPIO_PCTL_PB6_I2S0TXSCK 0x09000000  // I2S0TXSCK on PB6
#define GPIO_PCTL_PB7_M         0xF0000000  // PB7 mask
#define GPIO_PCTL_PB7_NMI       0x40000000  // NMI on PB7

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_PCTL register for
// port C.
//
//*****************************************************************************
#define GPIO_PCTL_PC0_M         0x0000000F  // PC0 mask
#define GPIO_PCTL_PC0_TCK       0x00000003  // TCK on PC0
#define GPIO_PCTL_PC1_M         0x000000F0  // PC1 mask
#define GPIO_PCTL_PC1_TMS       0x00000030  // TMS on PC1
#define GPIO_PCTL_PC2_M         0x00000F00  // PC2 mask
#define GPIO_PCTL_PC2_TDI       0x00000300  // TDI on PC2
#define GPIO_PCTL_PC3_M         0x0000F000  // PC3 mask
#define GPIO_PCTL_PC3_TDO       0x00003000  // TDO on PC3
#define GPIO_PCTL_PC4_M         0x000F0000  // PC4 mask
#define GPIO_PCTL_PC4_CCP5      0x00010000  // CCP5 on PC4
#define GPIO_PCTL_PC4_PHA0      0x00020000  // PHA0 on PC4
#define GPIO_PCTL_PC4_PWM6      0x00040000  // PWM6 on PC4
#define GPIO_PCTL_PC4_CCP2      0x00050000  // CCP2 on PC4
#define GPIO_PCTL_PC4_CCP4      0x00060000  // CCP4 on PC4
#define GPIO_PCTL_PC4_EPI0S2    0x00080000  // EPI0S2 on PC4
#define GPIO_PCTL_PC4_CCP1      0x00090000  // CCP1 on PC4
#define GPIO_PCTL_PC5_M         0x00F00000  // PC5 mask
#define GPIO_PCTL_PC5_CCP1      0x00100000  // CCP1 on PC5
#define GPIO_PCTL_PC5_C1O       0x00200000  // C1O on PC5
#define GPIO_PCTL_PC5_C0O       0x00300000  // C0O on PC5
#define GPIO_PCTL_PC5_FAULT2    0x00400000  // FAULT2 on PC5
#define GPIO_PCTL_PC5_CCP3      0x00500000  // CCP3 on PC5
#define GPIO_PCTL_PC5_USB0EPEN  0x00600000  // USB0EPEN on PC5
#define GPIO_PCTL_PC5_EPI0S3    0x00800000  // EPI0S3 on PC5
#define GPIO_PCTL_PC6_M         0x0F000000  // PC6 mask
#define GPIO_PCTL_PC6_CCP3      0x01000000  // CCP3 on PC6
#define GPIO_PCTL_PC6_PHB0      0x02000000  // PHB0 on PC6
#define GPIO_PCTL_PC6_C2O       0x03000000  // C2O on PC6
#define GPIO_PCTL_PC6_PWM7      0x04000000  // PWM7 on PC6
#define GPIO_PCTL_PC6_U1RX      0x05000000  // U1RX on PC6
#define GPIO_PCTL_PC6_CCP0      0x06000000  // CCP0 on PC6
#define GPIO_PCTL_PC6_USB0PFLT  0x07000000  // USB0PFLT on PC6
#define GPIO_PCTL_PC6_EPI0S4    0x08000000  // EPI0S4 on PC6
#define GPIO_PCTL_PC7_M         0xF0000000  // PC7 mask
#define GPIO_PCTL_PC7_CCP4      0x10000000  // CCP4 on PC7
#define GPIO_PCTL_PC7_PHB0      0x20000000  // PHB0 on PC7
#define GPIO_PCTL_PC7_CCP0      0x40000000  // CCP0 on PC7
#define GPIO_PCTL_PC7_U1TX      0x50000000  // U1TX on PC7
#define GPIO_PCTL_PC7_USB0PFLT  0x60000000  // USB0PFLT on PC7
#define GPIO_PCTL_PC7_C1O       0x70000000  // C1O on PC7
#define GPIO_PCTL_PC7_EPI0S5    0x80000000  // EPI0S5 on PC7

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_PCTL register for
// port D.
//
//*****************************************************************************
#define GPIO_PCTL_PD0_M         0x0000000F  // PD0 mask
#define GPIO_PCTL_PD0_PWM0      0x00000001  // PWM0 on PD0
#define GPIO_PCTL_PD0_CAN0RX    0x00000002  // CAN0RX on PD0
#define GPIO_PCTL_PD0_IDX0      0x00000003  // IDX0 on PD0
#define GPIO_PCTL_PD0_U2RX      0x00000004  // U2RX on PD0
#define GPIO_PCTL_PD0_U1RX      0x00000005  // U1RX on PD0
#define GPIO_PCTL_PD0_CCP6      0x00000006  // CCP6 on PD0
#define GPIO_PCTL_PD0_I2S0RXSCK 0x00000008  // I2S0RXSCK on PD0
#define GPIO_PCTL_PD0_U1CTS     0x00000009  // U1CTS on PD0
#define GPIO_PCTL_PD1_M         0x000000F0  // PD1 mask
#define GPIO_PCTL_PD1_PWM1      0x00000010  // PWM1 on PD1
#define GPIO_PCTL_PD1_CAN0TX    0x00000020  // CAN0TX on PD1
#define GPIO_PCTL_PD1_PHA0      0x00000030  // PHA0 on PD1
#define GPIO_PCTL_PD1_U2TX      0x00000040  // U2TX on PD1
#define GPIO_PCTL_PD1_U1TX      0x00000050  // U1TX on PD1
#define GPIO_PCTL_PD1_CCP7      0x00000060  // CCP7 on PD1
#define GPIO_PCTL_PD1_I2S0RXWS  0x00000080  // I2S0RXWS on PD1
#define GPIO_PCTL_PD1_U1DCD     0x00000090  // U1DCD on PD1
#define GPIO_PCTL_PD1_CCP2      0x000000A0  // CCP2 on PD1
#define GPIO_PCTL_PD1_PHB1      0x000000B0  // PHB1 on PD1
#define GPIO_PCTL_PD2_M         0x00000F00  // PD2 mask
#define GPIO_PCTL_PD2_U1RX      0x00000100  // U1RX on PD2
#define GPIO_PCTL_PD2_CCP6      0x00000200  // CCP6 on PD2
#define GPIO_PCTL_PD2_PWM2      0x00000300  // PWM2 on PD2
#define GPIO_PCTL_PD2_CCP5      0x00000400  // CCP5 on PD2
#define GPIO_PCTL_PD2_EPI0S20   0x00000800  // EPI0S20 on PD2
#define GPIO_PCTL_PD3_M         0x0000F000  // PD3 mask
#define GPIO_PCTL_PD3_U1TX      0x00001000  // U1TX on PD3
#define GPIO_PCTL_PD3_CCP7      0x00002000  // CCP7 on PD3
#define GPIO_PCTL_PD3_PWM3      0x00003000  // PWM3 on PD3
#define GPIO_PCTL_PD3_CCP0      0x00004000  // CCP0 on PD3
#define GPIO_PCTL_PD3_EPI0S21   0x00008000  // EPI0S21 on PD3
#define GPIO_PCTL_PD4_M         0x000F0000  // PD4 mask
#define GPIO_PCTL_PD4_CCP0      0x00010000  // CCP0 on PD4
#define GPIO_PCTL_PD4_CCP3      0x00020000  // CCP3 on PD4
#define GPIO_PCTL_PD4_I2S0RXSD  0x00080000  // I2S0RXSD on PD4
#define GPIO_PCTL_PD4_U1RI      0x00090000  // U1RI on PD4
#define GPIO_PCTL_PD4_EPI0S19   0x000A0000  // EPI0S19 on PD4
#define GPIO_PCTL_PD5_M         0x00F00000  // PD5 mask
#define GPIO_PCTL_PD5_CCP2      0x00100000  // CCP2 on PD5
#define GPIO_PCTL_PD5_CCP4      0x00200000  // CCP4 on PD5
#define GPIO_PCTL_PD5_I2S0RXMCLK \
                                0x00800000  // I2S0RXMCLK on PD5
#define GPIO_PCTL_PD5_U2RX      0x00900000  // U2RX on PD5
#define GPIO_PCTL_PD5_EPI0S28   0x00A00000  // EPI0S28 on PD5
#define GPIO_PCTL_PD6_M         0x0F000000  // PD6 mask
#define GPIO_PCTL_PD6_FAULT0    0x01000000  // FAULT0 on PD6
#define GPIO_PCTL_PD6_I2S0TXSCK 0x08000000  // I2S0TXSCK on PD6
#define GPIO_PCTL_PD6_U2TX      0x09000000  // U2TX on PD6
#define GPIO_PCTL_PD6_EPI0S29   0x0A000000  // EPI0S29 on PD6
#define GPIO_PCTL_PD7_M         0xF0000000  // PD7 mask
#define GPIO_PCTL_PD7_IDX0      0x10000000  // IDX0 on PD7
#define GPIO_PCTL_PD7_C0O       0x20000000  // C0O on PD7
#define GPIO_PCTL_PD7_CCP1      0x30000000  // CCP1 on PD7
#define GPIO_PCTL_PD7_I2S0TXWS  0x80000000  // I2S0TXWS on PD7
#define GPIO_PCTL_PD7_U1DTR     0x90000000  // U1DTR on PD7
#define GPIO_PCTL_PD7_EPI0S30   0xA0000000  // EPI0S30 on PD7

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_PCTL register for
// port E.
//
//*****************************************************************************
#define GPIO_PCTL_PE0_M         0x0000000F  // PE0 mask
#define GPIO_PCTL_PE0_PWM4      0x00000001  // PWM4 on PE0
#define GPIO_PCTL_PE0_SSI1CLK   0x00000002  // SSI1CLK on PE0
#define GPIO_PCTL_PE0_CCP3      0x00000003  // CCP3 on PE0
#define GPIO_PCTL_PE0_EPI0S8    0x00000008  // EPI0S8 on PE0
#define GPIO_PCTL_PE0_USB0PFLT  0x00000009  // USB0PFLT on PE0
#define GPIO_PCTL_PE1_M         0x000000F0  // PE1 mask
#define GPIO_PCTL_PE1_PWM5      0x00000010  // PWM5 on PE1
#define GPIO_PCTL_PE1_SSI1FSS   0x00000020  // SSI1FSS on PE1
#define GPIO_PCTL_PE1_FAULT0    0x00000030  // FAULT0 on PE1
#define GPIO_PCTL_PE1_CCP2      0x00000040  // CCP2 on PE1
#define GPIO_PCTL_PE1_CCP6      0x00000050  // CCP6 on PE1
#define GPIO_PCTL_PE1_EPI0S9    0x00000080  // EPI0S9 on PE1
#define GPIO_PCTL_PE2_M         0x00000F00  // PE2 mask
#define GPIO_PCTL_PE2_CCP4      0x00000100  // CCP4 on PE2
#define GPIO_PCTL_PE2_SSI1RX    0x00000200  // SSI1RX on PE2
#define GPIO_PCTL_PE2_PHB1      0x00000300  // PHB1 on PE2
#define GPIO_PCTL_PE2_PHA0      0x00000400  // PHA0 on PE2
#define GPIO_PCTL_PE2_CCP2      0x00000500  // CCP2 on PE2
#define GPIO_PCTL_PE2_EPI0S24   0x00000800  // EPI0S24 on PE2
#define GPIO_PCTL_PE3_M         0x0000F000  // PE3 mask
#define GPIO_PCTL_PE3_CCP1      0x00001000  // CCP1 on PE3
#define GPIO_PCTL_PE3_SSI1TX    0x00002000  // SSI1TX on PE3
#define GPIO_PCTL_PE3_PHA1      0x00003000  // PHA1 on PE3
#define GPIO_PCTL_PE3_PHB0      0x00004000  // PHB0 on PE3
#define GPIO_PCTL_PE3_CCP7      0x00005000  // CCP7 on PE3
#define GPIO_PCTL_PE3_EPI0S25   0x00008000  // EPI0S25 on PE3
#define GPIO_PCTL_PE4_M         0x000F0000  // PE4 mask
#define GPIO_PCTL_PE4_CCP3      0x00010000  // CCP3 on PE4
#define GPIO_PCTL_PE4_FAULT0    0x00040000  // FAULT0 on PE4
#define GPIO_PCTL_PE4_U2TX      0x00050000  // U2TX on PE4
#define GPIO_PCTL_PE4_CCP2      0x00060000  // CCP2 on PE4
#define GPIO_PCTL_PE4_I2S0TXWS  0x00090000  // I2S0TXWS on PE4
#define GPIO_PCTL_PE5_M         0x00F00000  // PE5 mask
#define GPIO_PCTL_PE5_CCP5      0x00100000  // CCP5 on PE5
#define GPIO_PCTL_PE5_I2S0TXSD  0x00900000  // I2S0TXSD on PE5
#define GPIO_PCTL_PE6_M         0x0F000000  // PE6 mask
#define GPIO_PCTL_PE6_PWM4      0x01000000  // PWM4 on PE6
#define GPIO_PCTL_PE6_C1O       0x02000000  // C1O on PE6
#define GPIO_PCTL_PE6_U1CTS     0x09000000  // U1CTS on PE6
#define GPIO_PCTL_PE7_M         0xF0000000  // PE7 mask
#define GPIO_PCTL_PE7_PWM5      0x10000000  // PWM5 on PE7
#define GPIO_PCTL_PE7_C2O       0x20000000  // C2O on PE7
#define GPIO_PCTL_PE7_U1DCD     0x90000000  // U1DCD on PE7

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_PCTL register for
// port F.
//
//*****************************************************************************
#define GPIO_PCTL_PF0_M         0x0000000F  // PF0 mask
#define GPIO_PCTL_PF0_CAN1RX    0x00000001  // CAN1RX on PF0
#define GPIO_PCTL_PF0_PHB0      0x00000002  // PHB0 on PF0
#define GPIO_PCTL_PF0_PWM0      0x00000003  // PWM0 on PF0
#define GPIO_PCTL_PF0_I2S0TXSD  0x00000008  // I2S0TXSD on PF0
#define GPIO_PCTL_PF0_U1DSR     0x00000009  // U1DSR on PF0
#define GPIO_PCTL_PF1_M         0x000000F0  // PF1 mask
#define GPIO_PCTL_PF1_CAN1TX    0x00000010  // CAN1TX on PF1
#define GPIO_PCTL_PF1_IDX1      0x00000020  // IDX1 on PF1
#define GPIO_PCTL_PF1_PWM1      0x00000030  // PWM1 on PF1
#define GPIO_PCTL_PF1_I2S0TXMCLK \
                                0x00000080  // I2S0TXMCLK on PF1
#define GPIO_PCTL_PF1_U1RTS     0x00000090  // U1RTS on PF1
#define GPIO_PCTL_PF1_CCP3      0x000000A0  // CCP3 on PF1
#define GPIO_PCTL_PF2_M         0x00000F00  // PF2 mask
#define GPIO_PCTL_PF2_LED1      0x00000100  // LED1 on PF2
#define GPIO_PCTL_PF2_PWM4      0x00000200  // PWM4 on PF2
#define GPIO_PCTL_PF2_PWM2      0x00000400  // PWM2 on PF2
#define GPIO_PCTL_PF2_SSI1CLK   0x00000900  // SSI1CLK on PF2
#define GPIO_PCTL_PF3_M         0x0000F000  // PF3 mask
#define GPIO_PCTL_PF3_LED0      0x00001000  // LED0 on PF3
#define GPIO_PCTL_PF3_PWM5      0x00002000  // PWM5 on PF3
#define GPIO_PCTL_PF3_PWM3      0x00004000  // PWM3 on PF3
#define GPIO_PCTL_PF3_SSI1FSS   0x00009000  // SSI1FSS on PF3
#define GPIO_PCTL_PF4_M         0x000F0000  // PF4 mask
#define GPIO_PCTL_PF4_CCP0      0x00010000  // CCP0 on PF4
#define GPIO_PCTL_PF4_C0O       0x00020000  // C0O on PF4
#define GPIO_PCTL_PF4_FAULT0    0x00040000  // FAULT0 on PF4
#define GPIO_PCTL_PF4_EPI0S12   0x00080000  // EPI0S12 on PF4
#define GPIO_PCTL_PF4_SSI1RX    0x00090000  // SSI1RX on PF4
#define GPIO_PCTL_PF5_M         0x00F00000  // PF5 mask
#define GPIO_PCTL_PF5_CCP2      0x00100000  // CCP2 on PF5
#define GPIO_PCTL_PF5_C1O       0x00200000  // C1O on PF5
#define GPIO_PCTL_PF5_EPI0S15   0x00800000  // EPI0S15 on PF5
#define GPIO_PCTL_PF5_SSI1TX    0x00900000  // SSI1TX on PF5
#define GPIO_PCTL_PF6_M         0x0F000000  // PF6 mask
#define GPIO_PCTL_PF6_CCP1      0x01000000  // CCP1 on PF6
#define GPIO_PCTL_PF6_C2O       0x02000000  // C2O on PF6
#define GPIO_PCTL_PF6_PHA0      0x04000000  // PHA0 on PF6
#define GPIO_PCTL_PF6_I2S0TXMCLK \
                                0x09000000  // I2S0TXMCLK on PF6
#define GPIO_PCTL_PF6_U1RTS     0x0A000000  // U1RTS on PF6
#define GPIO_PCTL_PF7_M         0xF0000000  // PF7 mask
#define GPIO_PCTL_PF7_CCP4      0x10000000  // CCP4 on PF7
#define GPIO_PCTL_PF7_PHB0      0x40000000  // PHB0 on PF7
#define GPIO_PCTL_PF7_EPI0S12   0x80000000  // EPI0S12 on PF7
#define GPIO_PCTL_PF7_FAULT1    0x90000000  // FAULT1 on PF7

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_PCTL register for
// port G.
//
//*****************************************************************************
#define GPIO_PCTL_PG0_M         0x0000000F  // PG0 mask
#define GPIO_PCTL_PG0_U2RX      0x00000001  // U2RX on PG0
#define GPIO_PCTL_PG0_PWM0      0x00000002  // PWM0 on PG0
#define GPIO_PCTL_PG0_I2C1SCL   0x00000003  // I2C1SCL on PG0
#define GPIO_PCTL_PG0_PWM4      0x00000004  // PWM4 on PG0
#define GPIO_PCTL_PG0_USB0EPEN  0x00000007  // USB0EPEN on PG0
#define GPIO_PCTL_PG0_EPI0S13   0x00000008  // EPI0S13 on PG0
#define GPIO_PCTL_PG1_M         0x000000F0  // PG1 mask
#define GPIO_PCTL_PG1_U2TX      0x00000010  // U2TX on PG1
#define GPIO_PCTL_PG1_PWM1      0x00000020  // PWM1 on PG1
#define GPIO_PCTL_PG1_I2C1SDA   0x00000030  // I2C1SDA on PG1
#define GPIO_PCTL_PG1_PWM5      0x00000040  // PWM5 on PG1
#define GPIO_PCTL_PG1_EPI0S14   0x00000080  // EPI0S14 on PG1
#define GPIO_PCTL_PG2_M         0x00000F00  // PG2 mask
#define GPIO_PCTL_PG2_PWM0      0x00000100  // PWM0 on PG2
#define GPIO_PCTL_PG2_FAULT0    0x00000400  // FAULT0 on PG2
#define GPIO_PCTL_PG2_IDX1      0x00000800  // IDX1 on PG2
#define GPIO_PCTL_PG2_I2S0RXSD  0x00000900  // I2S0RXSD on PG2
#define GPIO_PCTL_PG3_M         0x0000F000  // PG3 mask
#define GPIO_PCTL_PG3_PWM1      0x00001000  // PWM1 on PG3
#define GPIO_PCTL_PG3_FAULT2    0x00004000  // FAULT2 on PG3
#define GPIO_PCTL_PG3_FAULT0    0x00008000  // FAULT0 on PG3
#define GPIO_PCTL_PG3_I2S0RXMCLK \
                                0x00009000  // I2S0RXMCLK on PG3
#define GPIO_PCTL_PG4_M         0x000F0000  // PG4 mask
#define GPIO_PCTL_PG4_CCP3      0x00010000  // CCP3 on PG4
#define GPIO_PCTL_PG4_FAULT1    0x00040000  // FAULT1 on PG4
#define GPIO_PCTL_PG4_EPI0S15   0x00080000  // EPI0S15 on PG4
#define GPIO_PCTL_PG4_PWM6      0x00090000  // PWM6 on PG4
#define GPIO_PCTL_PG4_U1RI      0x000A0000  // U1RI on PG4
#define GPIO_PCTL_PG5_M         0x00F00000  // PG5 mask
#define GPIO_PCTL_PG5_CCP5      0x00100000  // CCP5 on PG5
#define GPIO_PCTL_PG5_IDX0      0x00400000  // IDX0 on PG5
#define GPIO_PCTL_PG5_FAULT1    0x00500000  // FAULT1 on PG5
#define GPIO_PCTL_PG5_PWM7      0x00800000  // PWM7 on PG5
#define GPIO_PCTL_PG5_I2S0RXSCK 0x00900000  // I2S0RXSCK on PG5
#define GPIO_PCTL_PG5_U1DTR     0x00A00000  // U1DTR on PG5
#define GPIO_PCTL_PG6_M         0x0F000000  // PG6 mask
#define GPIO_PCTL_PG6_PHA1      0x01000000  // PHA1 on PG6
#define GPIO_PCTL_PG6_PWM6      0x04000000  // PWM6 on PG6
#define GPIO_PCTL_PG6_FAULT1    0x08000000  // FAULT1 on PG6
#define GPIO_PCTL_PG6_I2S0RXWS  0x09000000  // I2S0RXWS on PG6
#define GPIO_PCTL_PG6_U1RI      0x0A000000  // U1RI on PG6
#define GPIO_PCTL_PG7_M         0xF0000000  // PG7 mask
#define GPIO_PCTL_PG7_PHB1      0x10000000  // PHB1 on PG7
#define GPIO_PCTL_PG7_PWM7      0x40000000  // PWM7 on PG7
#define GPIO_PCTL_PG7_CCP5      0x80000000  // CCP5 on PG7
#define GPIO_PCTL_PG7_EPI0S31   0x90000000  // EPI0S31 on PG7

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_PCTL register for
// port H.
//
//*****************************************************************************
#define GPIO_PCTL_PH0_M         0x0000000F  // PH0 mask
#define GPIO_PCTL_PH0_CCP6      0x00000001  // CCP6 on PH0
#define GPIO_PCTL_PH0_PWM2      0x00000002  // PWM2 on PH0
#define GPIO_PCTL_PH0_EPI0S6    0x00000008  // EPI0S6 on PH0
#define GPIO_PCTL_PH0_PWM4      0x00000009  // PWM4 on PH0
#define GPIO_PCTL_PH1_M         0x000000F0  // PH1 mask
#define GPIO_PCTL_PH1_CCP7      0x00000010  // CCP7 on PH1
#define GPIO_PCTL_PH1_PWM3      0x00000020  // PWM3 on PH1
#define GPIO_PCTL_PH1_EPI0S7    0x00000080  // EPI0S7 on PH1
#define GPIO_PCTL_PH1_PWM5      0x00000090  // PWM5 on PH1
#define GPIO_PCTL_PH2_M         0x00000F00  // PH2 mask
#define GPIO_PCTL_PH2_IDX1      0x00000100  // IDX1 on PH2
#define GPIO_PCTL_PH2_C1O       0x00000200  // C1O on PH2
#define GPIO_PCTL_PH2_FAULT3    0x00000400  // FAULT3 on PH2
#define GPIO_PCTL_PH2_EPI0S1    0x00000800  // EPI0S1 on PH2
#define GPIO_PCTL_PH3_M         0x0000F000  // PH3 mask
#define GPIO_PCTL_PH3_PHB0      0x00001000  // PHB0 on PH3
#define GPIO_PCTL_PH3_FAULT0    0x00002000  // FAULT0 on PH3
#define GPIO_PCTL_PH3_USB0EPEN  0x00004000  // USB0EPEN on PH3
#define GPIO_PCTL_PH3_EPI0S0    0x00008000  // EPI0S0 on PH3
#define GPIO_PCTL_PH4_M         0x000F0000  // PH4 mask
#define GPIO_PCTL_PH4_USB0PFLT  0x00040000  // USB0PFLT on PH4
#define GPIO_PCTL_PH4_EPI0S10   0x00080000  // EPI0S10 on PH4
#define GPIO_PCTL_PH4_SSI1CLK   0x000B0000  // SSI1CLK on PH4
#define GPIO_PCTL_PH5_M         0x00F00000  // PH5 mask
#define GPIO_PCTL_PH5_EPI0S11   0x00800000  // EPI0S11 on PH5
#define GPIO_PCTL_PH5_FAULT2    0x00A00000  // FAULT2 on PH5
#define GPIO_PCTL_PH5_SSI1FSS   0x00B00000  // SSI1FSS on PH5
#define GPIO_PCTL_PH6_M         0x0F000000  // PH6 mask
#define GPIO_PCTL_PH6_EPI0S26   0x08000000  // EPI0S26 on PH6
#define GPIO_PCTL_PH6_PWM4      0x0A000000  // PWM4 on PH6
#define GPIO_PCTL_PH6_SSI1RX    0x0B000000  // SSI1RX on PH6
#define GPIO_PCTL_PH7_M         0xF0000000  // PH7 mask
#define GPIO_PCTL_PH7_EPI0S27   0x80000000  // EPI0S27 on PH7
#define GPIO_PCTL_PH7_PWM5      0xA0000000  // PWM5 on PH7
#define GPIO_PCTL_PH7_SSI1TX    0xB0000000  // SSI1TX on PH7

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_PCTL register for
// port J.
//
//*****************************************************************************
#define GPIO_PCTL_PJ0_M         0x0000000F  // PJ0 mask
#define GPIO_PCTL_PJ0_EPI0S16   0x00000008  // EPI0S16 on PJ0
#define GPIO_PCTL_PJ0_PWM0      0x0000000A  // PWM0 on PJ0
#define GPIO_PCTL_PJ0_I2C1SCL   0x0000000B  // I2C1SCL on PJ0
#define GPIO_PCTL_PJ1_M         0x000000F0  // PJ1 mask
#define GPIO_PCTL_PJ1_EPI0S17   0x00000080  // EPI0S17 on PJ1
#define GPIO_PCTL_PJ1_USB0PFLT  0x00000090  // USB0PFLT on PJ1
#define GPIO_PCTL_PJ1_PWM1      0x000000A0  // PWM1 on PJ1
#define GPIO_PCTL_PJ1_I2C1SDA   0x000000B0  // I2C1SDA on PJ1
#define GPIO_PCTL_PJ2_M         0x00000F00  // PJ2 mask
#define GPIO_PCTL_PJ2_EPI0S18   0x00000800  // EPI0S18 on PJ2
#define GPIO_PCTL_PJ2_CCP0      0x00000900  // CCP0 on PJ2
#define GPIO_PCTL_PJ2_FAULT0    0x00000A00  // FAULT0 on PJ2
#define GPIO_PCTL_PJ3_M         0x0000F000  // PJ3 mask
#define GPIO_PCTL_PJ3_EPI0S19   0x00008000  // EPI0S19 on PJ3
#define GPIO_PCTL_PJ3_U1CTS     0x00009000  // U1CTS on PJ3
#define GPIO_PCTL_PJ3_CCP6      0x0000A000  // CCP6 on PJ3
#define GPIO_PCTL_PJ4_M         0x000F0000  // PJ4 mask
#define GPIO_PCTL_PJ4_EPI0S28   0x00080000  // EPI0S28 on PJ4
#define GPIO_PCTL_PJ4_U1DCD     0x00090000  // U1DCD on PJ4
#define GPIO_PCTL_PJ4_CCP4      0x000A0000  // CCP4 on PJ4
#define GPIO_PCTL_PJ5_M         0x00F00000  // PJ5 mask
#define GPIO_PCTL_PJ5_EPI0S29   0x00800000  // EPI0S29 on PJ5
#define GPIO_PCTL_PJ5_U1DSR     0x00900000  // U1DSR on PJ5
#define GPIO_PCTL_PJ5_CCP2      0x00A00000  // CCP2 on PJ5
#define GPIO_PCTL_PJ6_M         0x0F000000  // PJ6 mask
#define GPIO_PCTL_PJ6_EPI0S30   0x08000000  // EPI0S30 on PJ6
#define GPIO_PCTL_PJ6_U1RTS     0x09000000  // U1RTS on PJ6
#define GPIO_PCTL_PJ6_CCP1      0x0A000000  // CCP1 on PJ6
#define GPIO_PCTL_PJ7_M         0xF0000000  // PJ7 mask
#define GPIO_PCTL_PJ7_U1DTR     0x90000000  // U1DTR on PJ7
#define GPIO_PCTL_PJ7_CCP0      0xA0000000  // CCP0 on PJ7

//*****************************************************************************
//
// The following definitions are deprecated.
//
//*****************************************************************************
#ifndef DEPRECATED

//*****************************************************************************
//
// The following are deprecated defines for the GPIO register offsets.
//
//*****************************************************************************
#define GPIO_O_PeriphID4        0x00000FD0
#define GPIO_O_PeriphID5        0x00000FD4
#define GPIO_O_PeriphID6        0x00000FD8
#define GPIO_O_PeriphID7        0x00000FDC
#define GPIO_O_PeriphID0        0x00000FE0
#define GPIO_O_PeriphID1        0x00000FE4
#define GPIO_O_PeriphID2        0x00000FE8
#define GPIO_O_PeriphID3        0x00000FEC
#define GPIO_O_PCellID0         0x00000FF0
#define GPIO_O_PCellID1         0x00000FF4
#define GPIO_O_PCellID2         0x00000FF8
#define GPIO_O_PCellID3         0x00000FFC

//*****************************************************************************
//
// The following are deprecated defines for the GPIO Register reset values.
//
//*****************************************************************************
#define GPIO_RV_DEN             0x000000FF  // Digital input enable reg RV
#define GPIO_RV_PUR             0x000000FF  // Pull up select reg RV
#define GPIO_RV_DR2R            0x000000FF  // 2ma drive select reg RV
#define GPIO_RV_PCellID1        0x000000F0
#define GPIO_RV_PCellID3        0x000000B1
#define GPIO_RV_PeriphID0       0x00000061
#define GPIO_RV_PeriphID1       0x00000010
#define GPIO_RV_PCellID0        0x0000000D
#define GPIO_RV_PCellID2        0x00000005
#define GPIO_RV_PeriphID2       0x00000004
#define GPIO_RV_LOCK            0x00000001  // Lock register RV
#define GPIO_RV_PeriphID7       0x00000000
#define GPIO_RV_PDR             0x00000000  // Pull down select reg RV
#define GPIO_RV_IC              0x00000000  // Interrupt clear reg RV
#define GPIO_RV_SLR             0x00000000  // Slew rate control enable reg RV
#define GPIO_RV_ODR             0x00000000  // Open drain select reg RV
#define GPIO_RV_IBE             0x00000000  // Interrupt both edges reg RV
#define GPIO_RV_AFSEL           0x00000000  // Mode control select reg RV
#define GPIO_RV_IS              0x00000000  // Interrupt sense reg RV
#define GPIO_RV_IM              0x00000000  // Interrupt mask reg RV
#define GPIO_RV_PeriphID4       0x00000000
#define GPIO_RV_PeriphID5       0x00000000
#define GPIO_RV_DR8R            0x00000000  // 8ma drive select reg RV
#define GPIO_RV_RIS             0x00000000  // Raw interrupt status reg RV
#define GPIO_RV_DR4R            0x00000000  // 4ma drive select reg RV
#define GPIO_RV_IEV             0x00000000  // Intterupt event reg RV
#define GPIO_RV_DIR             0x00000000  // Data direction reg RV
#define GPIO_RV_PeriphID6       0x00000000
#define GPIO_RV_PeriphID3       0x00000000
#define GPIO_RV_DATA            0x00000000  // Data register reset value
#define GPIO_RV_MIS             0x00000000  // Masked interrupt status reg RV

#endif

#endif // __HW_GPIO_H__
