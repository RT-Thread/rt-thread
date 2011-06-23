//*****************************************************************************
//
// hw_ints.h - Macros that define the interrupt assignment on Stellaris.
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

#ifndef __HW_INTS_H__
#define __HW_INTS_H__

//*****************************************************************************
//
// The following are defines for the fault assignments.
//
//*****************************************************************************
#define FAULT_NMI               2           // NMI fault
#define FAULT_HARD              3           // Hard fault
#define FAULT_MPU               4           // MPU fault
#define FAULT_BUS               5           // Bus fault
#define FAULT_USAGE             6           // Usage fault
#define FAULT_SVCALL            11          // SVCall
#define FAULT_DEBUG             12          // Debug monitor
#define FAULT_PENDSV            14          // PendSV
#define FAULT_SYSTICK           15          // System Tick

//*****************************************************************************
//
// The following are defines for the interrupt assignments.
//
//*****************************************************************************
#define INT_GPIOA               16          // GPIO Port A
#define INT_GPIOB               17          // GPIO Port B
#define INT_GPIOC               18          // GPIO Port C
#define INT_GPIOD               19          // GPIO Port D
#define INT_GPIOE               20          // GPIO Port E
#define INT_UART0               21          // UART0 Rx and Tx
#define INT_UART1               22          // UART1 Rx and Tx
#define INT_SSI0                23          // SSI0 Rx and Tx
#define INT_I2C0                24          // I2C0 Master and Slave
#define INT_PWM_FAULT           25          // PWM Fault
#define INT_PWM0                26          // PWM Generator 0
#define INT_PWM1                27          // PWM Generator 1
#define INT_PWM2                28          // PWM Generator 2
#define INT_QEI0                29          // Quadrature Encoder 0
#define INT_ADC0SS0             30          // ADC0 Sequence 0
#define INT_ADC0SS1             31          // ADC0 Sequence 1
#define INT_ADC0SS2             32          // ADC0 Sequence 2
#define INT_ADC0SS3             33          // ADC0 Sequence 3
#define INT_WATCHDOG            34          // Watchdog timer
#define INT_TIMER0A             35          // Timer 0 subtimer A
#define INT_TIMER0B             36          // Timer 0 subtimer B
#define INT_TIMER1A             37          // Timer 1 subtimer A
#define INT_TIMER1B             38          // Timer 1 subtimer B
#define INT_TIMER2A             39          // Timer 2 subtimer A
#define INT_TIMER2B             40          // Timer 2 subtimer B
#define INT_COMP0               41          // Analog Comparator 0
#define INT_COMP1               42          // Analog Comparator 1
#define INT_COMP2               43          // Analog Comparator 2
#define INT_SYSCTL              44          // System Control (PLL, OSC, BO)
#define INT_FLASH               45          // FLASH Control
#define INT_GPIOF               46          // GPIO Port F
#define INT_GPIOG               47          // GPIO Port G
#define INT_GPIOH               48          // GPIO Port H
#define INT_UART2               49          // UART2 Rx and Tx
#define INT_SSI1                50          // SSI1 Rx and Tx
#define INT_TIMER3A             51          // Timer 3 subtimer A
#define INT_TIMER3B             52          // Timer 3 subtimer B
#define INT_I2C1                53          // I2C1 Master and Slave
#define INT_QEI1                54          // Quadrature Encoder 1
#define INT_CAN0                55          // CAN0
#define INT_CAN1                56          // CAN1
#define INT_CAN2                57          // CAN2
#define INT_ETH                 58          // Ethernet
#define INT_HIBERNATE           59          // Hibernation module
#define INT_USB0                60          // USB 0 Controller
#define INT_PWM3                61          // PWM Generator 3
#define INT_UDMA                62          // uDMA controller
#define INT_UDMAERR             63          // uDMA Error
#define INT_ADC1SS0             64          // ADC1 Sequence 0
#define INT_ADC1SS1             65          // ADC1 Sequence 1
#define INT_ADC1SS2             66          // ADC1 Sequence 2
#define INT_ADC1SS3             67          // ADC1 Sequence 3
#define INT_I2S0                68          // I2S0
#define INT_EPI0                69          // EPI0
#define INT_GPIOJ               70          // GPIO Port J

//*****************************************************************************
//
// The following are defines for the total number of interrupts.
//
//*****************************************************************************
#define NUM_INTERRUPTS          71

//*****************************************************************************
//
// The following are defines for the total number of priority levels.
//
//*****************************************************************************
#define NUM_PRIORITY            8
#define NUM_PRIORITY_BITS       3

//*****************************************************************************
//
// The following definitions are deprecated.
//
//*****************************************************************************
#ifndef DEPRECATED

//*****************************************************************************
//
// The following are deprecated defines for the interrupt assignments.
//
//*****************************************************************************
#define INT_SSI                 23          // SSI Rx and Tx
#define INT_I2C                 24          // I2C Master and Slave
#define INT_QEI                 29          // Quadrature Encoder
#define INT_ADC0                30          // ADC Sequence 0
#define INT_ADC1                31          // ADC Sequence 1
#define INT_ADC2                32          // ADC Sequence 2
#define INT_ADC3                33          // ADC Sequence 3

#endif

#endif // __HW_INTS_H__
