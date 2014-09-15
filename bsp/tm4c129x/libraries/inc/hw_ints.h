//*****************************************************************************
//
// hw_ints.h - Macros that define the interrupt assignment on Tiva C Series
// MCUs.
//
// Copyright (c) 2005-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions
//   are met:
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
// 
// This is part of revision 2.1.0.12573 of the Tiva Firmware Development Package.
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
// TM4C123 Class Interrupts
//
//*****************************************************************************
#define INT_GPIOA_TM4C123       16          // GPIO Port A
#define INT_GPIOB_TM4C123       17          // GPIO Port B
#define INT_GPIOC_TM4C123       18          // GPIO Port C
#define INT_GPIOD_TM4C123       19          // GPIO Port D
#define INT_GPIOE_TM4C123       20          // GPIO Port E
#define INT_UART0_TM4C123       21          // UART0
#define INT_UART1_TM4C123       22          // UART1
#define INT_SSI0_TM4C123        23          // SSI0
#define INT_I2C0_TM4C123        24          // I2C0
#define INT_PWM0_FAULT_TM4C123  25          // PWM0 Fault
#define INT_PWM0_0_TM4C123      26          // PWM0 Generator 0
#define INT_PWM0_1_TM4C123      27          // PWM0 Generator 1
#define INT_PWM0_2_TM4C123      28          // PWM0 Generator 2
#define INT_QEI0_TM4C123        29          // QEI0
#define INT_ADC0SS0_TM4C123     30          // ADC0 Sequence 0
#define INT_ADC0SS1_TM4C123     31          // ADC0 Sequence 1
#define INT_ADC0SS2_TM4C123     32          // ADC0 Sequence 2
#define INT_ADC0SS3_TM4C123     33          // ADC0 Sequence 3
#define INT_WATCHDOG_TM4C123    34          // Watchdog Timers 0 and 1
#define INT_TIMER0A_TM4C123     35          // 16/32-Bit Timer 0A
#define INT_TIMER0B_TM4C123     36          // 16/32-Bit Timer 0B
#define INT_TIMER1A_TM4C123     37          // 16/32-Bit Timer 1A
#define INT_TIMER1B_TM4C123     38          // 16/32-Bit Timer 1B
#define INT_TIMER2A_TM4C123     39          // 16/32-Bit Timer 2A
#define INT_TIMER2B_TM4C123     40          // 16/32-Bit Timer 2B
#define INT_COMP0_TM4C123       41          // Analog Comparator 0
#define INT_COMP1_TM4C123       42          // Analog Comparator 1
#define INT_COMP2_TM4C123       43          // Analog Comparator 2
#define INT_SYSCTL_TM4C123      44          // System Control
#define INT_FLASH_TM4C123       45          // Flash Memory Control and EEPROM
                                            // Control
#define INT_GPIOF_TM4C123       46          // GPIO Port F
#define INT_GPIOG_TM4C123       47          // GPIO Port G
#define INT_GPIOH_TM4C123       48          // GPIO Port H
#define INT_UART2_TM4C123       49          // UART2
#define INT_SSI1_TM4C123        50          // SSI1
#define INT_TIMER3A_TM4C123     51          // 16/32-Bit Timer 3A
#define INT_TIMER3B_TM4C123     52          // Timer 3B
#define INT_I2C1_TM4C123        53          // I2C1
#define INT_QEI1_TM4C123        54          // QEI1
#define INT_CAN0_TM4C123        55          // CAN0
#define INT_CAN1_TM4C123        56          // CAN1
#define INT_HIBERNATE_TM4C123   59          // Hibernation Module
#define INT_USB0_TM4C123        60          // USB
#define INT_PWM0_3_TM4C123      61          // PWM Generator 3
#define INT_UDMA_TM4C123        62          // uDMA Software
#define INT_UDMAERR_TM4C123     63          // uDMA Error
#define INT_ADC1SS0_TM4C123     64          // ADC1 Sequence 0
#define INT_ADC1SS1_TM4C123     65          // ADC1 Sequence 1
#define INT_ADC1SS2_TM4C123     66          // ADC1 Sequence 2
#define INT_ADC1SS3_TM4C123     67          // ADC1 Sequence 3
#define INT_GPIOJ_TM4C123       70          // GPIO Port J
#define INT_GPIOK_TM4C123       71          // GPIO Port K
#define INT_GPIOL_TM4C123       72          // GPIO Port L
#define INT_SSI2_TM4C123        73          // SSI2
#define INT_SSI3_TM4C123        74          // SSI3
#define INT_UART3_TM4C123       75          // UART3
#define INT_UART4_TM4C123       76          // UART4
#define INT_UART5_TM4C123       77          // UART5
#define INT_UART6_TM4C123       78          // UART6
#define INT_UART7_TM4C123       79          // UART7
#define INT_I2C2_TM4C123        84          // I2C2
#define INT_I2C3_TM4C123        85          // I2C3
#define INT_TIMER4A_TM4C123     86          // 16/32-Bit Timer 4A
#define INT_TIMER4B_TM4C123     87          // 16/32-Bit Timer 4B
#define INT_TIMER5A_TM4C123     108         // 16/32-Bit Timer 5A
#define INT_TIMER5B_TM4C123     109         // 16/32-Bit Timer 5B
#define INT_WTIMER0A_TM4C123    110         // 32/64-Bit Timer 0A
#define INT_WTIMER0B_TM4C123    111         // 32/64-Bit Timer 0B
#define INT_WTIMER1A_TM4C123    112         // 32/64-Bit Timer 1A
#define INT_WTIMER1B_TM4C123    113         // 32/64-Bit Timer 1B
#define INT_WTIMER2A_TM4C123    114         // 32/64-Bit Timer 2A
#define INT_WTIMER2B_TM4C123    115         // 32/64-Bit Timer 2B
#define INT_WTIMER3A_TM4C123    116         // 32/64-Bit Timer 3A
#define INT_WTIMER3B_TM4C123    117         // 32/64-Bit Timer 3B
#define INT_WTIMER4A_TM4C123    118         // 32/64-Bit Timer 4A
#define INT_WTIMER4B_TM4C123    119         // 32/64-Bit Timer 4B
#define INT_WTIMER5A_TM4C123    120         // 32/64-Bit Timer 5A
#define INT_WTIMER5B_TM4C123    121         // 32/64-Bit Timer 5B
#define INT_SYSEXC_TM4C123      122         // System Exception (imprecise)
#define INT_I2C4_TM4C123        125         // I2C4
#define INT_I2C5_TM4C123        126         // I2C5
#define INT_GPIOM_TM4C123       127         // GPIO Port M
#define INT_GPION_TM4C123       128         // GPIO Port N
#define INT_GPIOP0_TM4C123      132         // GPIO Port P (Summary or P0)
#define INT_GPIOP1_TM4C123      133         // GPIO Port P1
#define INT_GPIOP2_TM4C123      134         // GPIO Port P2
#define INT_GPIOP3_TM4C123      135         // GPIO Port P3
#define INT_GPIOP4_TM4C123      136         // GPIO Port P4
#define INT_GPIOP5_TM4C123      137         // GPIO Port P5
#define INT_GPIOP6_TM4C123      138         // GPIO Port P6
#define INT_GPIOP7_TM4C123      139         // GPIO Port P7
#define INT_GPIOQ0_TM4C123      140         // GPIO Port Q (Summary or Q0)
#define INT_GPIOQ1_TM4C123      141         // GPIO Port Q1
#define INT_GPIOQ2_TM4C123      142         // GPIO Port Q2
#define INT_GPIOQ3_TM4C123      143         // GPIO Port Q3
#define INT_GPIOQ4_TM4C123      144         // GPIO Port Q4
#define INT_GPIOQ5_TM4C123      145         // GPIO Port Q5
#define INT_GPIOQ6_TM4C123      146         // GPIO Port Q6
#define INT_GPIOQ7_TM4C123      147         // GPIO Port Q7
#define INT_PWM1_0_TM4C123      150         // PWM1 Generator 0
#define INT_PWM1_1_TM4C123      151         // PWM1 Generator 1
#define INT_PWM1_2_TM4C123      152         // PWM1 Generator 2
#define INT_PWM1_3_TM4C123      153         // PWM1 Generator 3
#define INT_PWM1_FAULT_TM4C123  154         // PWM1 Fault
#define NUM_INTERRUPTS_TM4C123  155

//*****************************************************************************
//
// TM4C129 Class Interrupts
//
//*****************************************************************************
#define INT_GPIOA_TM4C129       16          // GPIO Port A
#define INT_GPIOB_TM4C129       17          // GPIO Port B
#define INT_GPIOC_TM4C129       18          // GPIO Port C
#define INT_GPIOD_TM4C129       19          // GPIO Port D
#define INT_GPIOE_TM4C129       20          // GPIO Port E
#define INT_UART0_TM4C129       21          // UART0
#define INT_UART1_TM4C129       22          // UART1
#define INT_SSI0_TM4C129        23          // SSI0
#define INT_I2C0_TM4C129        24          // I2C0
#define INT_PWM0_FAULT_TM4C129  25          // PWM Fault
#define INT_PWM0_0_TM4C129      26          // PWM Generator 0
#define INT_PWM0_1_TM4C129      27          // PWM Generator 1
#define INT_PWM0_2_TM4C129      28          // PWM Generator 2
#define INT_QEI0_TM4C129        29          // QEI0
#define INT_ADC0SS0_TM4C129     30          // ADC0 Sequence 0
#define INT_ADC0SS1_TM4C129     31          // ADC0 Sequence 1
#define INT_ADC0SS2_TM4C129     32          // ADC0 Sequence 2
#define INT_ADC0SS3_TM4C129     33          // ADC0 Sequence 3
#define INT_WATCHDOG_TM4C129    34          // Watchdog Timers 0 and 1
#define INT_TIMER0A_TM4C129     35          // 16/32-Bit Timer 0A
#define INT_TIMER0B_TM4C129     36          // 16/32-Bit Timer 0B
#define INT_TIMER1A_TM4C129     37          // 16/32-Bit Timer 1A
#define INT_TIMER1B_TM4C129     38          // 16/32-Bit Timer 1B
#define INT_TIMER2A_TM4C129     39          // 16/32-Bit Timer 2A
#define INT_TIMER2B_TM4C129     40          // 16/32-Bit Timer 2B
#define INT_COMP0_TM4C129       41          // Analog Comparator 0
#define INT_COMP1_TM4C129       42          // Analog Comparator 1
#define INT_COMP2_TM4C129       43          // Analog Comparator 2
#define INT_SYSCTL_TM4C129      44          // System Control
#define INT_FLASH_TM4C129       45          // Flash Memory Control
#define INT_GPIOF_TM4C129       46          // GPIO Port F
#define INT_GPIOG_TM4C129       47          // GPIO Port G
#define INT_GPIOH_TM4C129       48          // GPIO Port H
#define INT_UART2_TM4C129       49          // UART2
#define INT_SSI1_TM4C129        50          // SSI1
#define INT_TIMER3A_TM4C129     51          // 16/32-Bit Timer 3A
#define INT_TIMER3B_TM4C129     52          // 16/32-Bit Timer 3B
#define INT_I2C1_TM4C129        53          // I2C1
#define INT_CAN0_TM4C129        54          // CAN 0
#define INT_CAN1_TM4C129        55          // CAN1
#define INT_EMAC0_TM4C129       56          // Ethernet MAC
#define INT_HIBERNATE_TM4C129   57          // HIB
#define INT_USB0_TM4C129        58          // USB MAC
#define INT_PWM0_3_TM4C129      59          // PWM Generator 3
#define INT_UDMA_TM4C129        60          // uDMA 0 Software
#define INT_UDMAERR_TM4C129     61          // uDMA 0 Error
#define INT_ADC1SS0_TM4C129     62          // ADC1 Sequence 0
#define INT_ADC1SS1_TM4C129     63          // ADC1 Sequence 1
#define INT_ADC1SS2_TM4C129     64          // ADC1 Sequence 2
#define INT_ADC1SS3_TM4C129     65          // ADC1 Sequence 3
#define INT_EPI0_TM4C129        66          // EPI 0
#define INT_GPIOJ_TM4C129       67          // GPIO Port J
#define INT_GPIOK_TM4C129       68          // GPIO Port K
#define INT_GPIOL_TM4C129       69          // GPIO Port L
#define INT_SSI2_TM4C129        70          // SSI 2
#define INT_SSI3_TM4C129        71          // SSI 3
#define INT_UART3_TM4C129       72          // UART 3
#define INT_UART4_TM4C129       73          // UART 4
#define INT_UART5_TM4C129       74          // UART 5
#define INT_UART6_TM4C129       75          // UART 6
#define INT_UART7_TM4C129       76          // UART 7
#define INT_I2C2_TM4C129        77          // I2C 2
#define INT_I2C3_TM4C129        78          // I2C 3
#define INT_TIMER4A_TM4C129     79          // Timer 4A
#define INT_TIMER4B_TM4C129     80          // Timer 4B
#define INT_TIMER5A_TM4C129     81          // Timer 5A
#define INT_TIMER5B_TM4C129     82          // Timer 5B
#define INT_SYSEXC_TM4C129      83          // Floating-Point Exception
                                            // (imprecise)
#define INT_I2C4_TM4C129        86          // I2C 4
#define INT_I2C5_TM4C129        87          // I2C 5
#define INT_GPIOM_TM4C129       88          // GPIO Port M
#define INT_GPION_TM4C129       89          // GPIO Port N
#define INT_TAMPER0_TM4C129     91          // Tamper
#define INT_GPIOP0_TM4C129      92          // GPIO Port P (Summary or P0)
#define INT_GPIOP1_TM4C129      93          // GPIO Port P1
#define INT_GPIOP2_TM4C129      94          // GPIO Port P2
#define INT_GPIOP3_TM4C129      95          // GPIO Port P3
#define INT_GPIOP4_TM4C129      96          // GPIO Port P4
#define INT_GPIOP5_TM4C129      97          // GPIO Port P5
#define INT_GPIOP6_TM4C129      98          // GPIO Port P6
#define INT_GPIOP7_TM4C129      99          // GPIO Port P7
#define INT_GPIOQ0_TM4C129      100         // GPIO Port Q (Summary or Q0)
#define INT_GPIOQ1_TM4C129      101         // GPIO Port Q1
#define INT_GPIOQ2_TM4C129      102         // GPIO Port Q2
#define INT_GPIOQ3_TM4C129      103         // GPIO Port Q3
#define INT_GPIOQ4_TM4C129      104         // GPIO Port Q4
#define INT_GPIOQ5_TM4C129      105         // GPIO Port Q5
#define INT_GPIOQ6_TM4C129      106         // GPIO Port Q6
#define INT_GPIOQ7_TM4C129      107         // GPIO Port Q7
#define INT_GPIOR_TM4C129       108         // GPIO Port R
#define INT_GPIOS_TM4C129       109         // GPIO Port S
#define INT_SHA0_TM4C129        110         // SHA/MD5
#define INT_AES0_TM4C129        111         // AES
#define INT_DES0_TM4C129        112         // DES
#define INT_LCD0_TM4C129        113         // LCD
#define INT_TIMER6A_TM4C129     114         // 16/32-Bit Timer 6A
#define INT_TIMER6B_TM4C129     115         // 16/32-Bit Timer 6B
#define INT_TIMER7A_TM4C129     116         // 16/32-Bit Timer 7A
#define INT_TIMER7B_TM4C129     117         // 16/32-Bit Timer 7B
#define INT_I2C6_TM4C129        118         // I2C 6
#define INT_I2C7_TM4C129        119         // I2C 7
#define INT_ONEWIRE0_TM4C129    121         // 1-Wire
#define INT_I2C8_TM4C129        125         // I2C 8
#define INT_I2C9_TM4C129        126         // I2C 9
#define INT_GPIOT_TM4C129       127         // GPIO T
#define NUM_INTERRUPTS_TM4C129  129

//*****************************************************************************
//
// TM4C123 Interrupt Class Definition
//
//*****************************************************************************
#if defined(TARGET_IS_TM4C123_RA1) || defined(TARGET_IS_TM4C123_RA2) || \
    defined(TARGET_IS_TM4C123_RA3) || defined(TARGET_IS_TM4C123_RB0) || \
    defined(TARGET_IS_TM4C123_RB1) || defined(PART_TM4C1230C3PM) || \
    defined(PART_TM4C1230D5PM) || defined(PART_TM4C1230E6PM) || \
    defined(PART_TM4C1230H6PM) || defined(PART_TM4C1231C3PM) || \
    defined(PART_TM4C1231D5PM) || defined(PART_TM4C1231D5PZ) || \
    defined(PART_TM4C1231E6PM) || defined(PART_TM4C1231E6PZ) || \
    defined(PART_TM4C1231H6PM) || defined(PART_TM4C1231H6PZ) || \
    defined(PART_TM4C1232C3PM) || defined(PART_TM4C1232D5PM) || \
    defined(PART_TM4C1232E6PM) || defined(PART_TM4C1232H6PM) || \
    defined(PART_TM4C1233C3PM) || defined(PART_TM4C1233D5PM) || \
    defined(PART_TM4C1233D5PZ) || defined(PART_TM4C1233E6PM) || \
    defined(PART_TM4C1233E6PZ) || defined(PART_TM4C1233H6PM) || \
    defined(PART_TM4C1233H6PZ) || defined(PART_TM4C1236D5PM) || \
    defined(PART_TM4C1236E6PM) || defined(PART_TM4C1236H6PM) || \
    defined(PART_TM4C1237D5PM) || defined(PART_TM4C1237D5PZ) || \
    defined(PART_TM4C1237E6PM) || defined(PART_TM4C1237E6PZ) || \
    defined(PART_TM4C1237H6PM) || defined(PART_TM4C1237H6PZ) || \
    defined(PART_TM4C123AE6PM) || defined(PART_TM4C123AH6PM) || \
    defined(PART_TM4C123BE6PM) || defined(PART_TM4C123BE6PZ) || \
    defined(PART_TM4C123BH6PM) || defined(PART_TM4C123BH6PZ) || \
    defined(PART_TM4C123FE6PM) || defined(PART_TM4C123FH6PM) || \
    defined(PART_TM4C123GE6PM) || defined(PART_TM4C123GE6PZ) || \
    defined(PART_TM4C123GH6PM) || defined(PART_TM4C123GH6PZ) || \
    defined(PART_TM4C1231H6PGE) || defined(PART_TM4C1233H6PGE) || \
    defined(PART_TM4C1237H6PGE) || defined(PART_TM4C123BH6PGE) || \
    defined(PART_TM4C123BH6ZRB) || defined(PART_TM4C123GH6PGE) || \
    defined(PART_TM4C123GH6ZRB)
#define INT_RESOLVE(intname, class) intname##TM4C123

//*****************************************************************************
//
// TM4C129 Interrupt Class Definition
//
//*****************************************************************************
#elif defined(TARGET_IS_TM4C129_RA0) || defined(PART_TM4C1290NCPDT) || \
    defined(PART_TM4C1290NCZAD) || defined(PART_TM4C1292NCPDT) || \
    defined(PART_TM4C1292NCZAD) || defined(PART_TM4C1294KCPDT) || \
    defined(PART_TM4C1294NCPDT) || defined(PART_TM4C1294NCZAD) || \
    defined(PART_TM4C1297NCZAD) || defined(PART_TM4C1299KCZAD) || \
    defined(PART_TM4C1299NCZAD) || defined(PART_TM4C129CNCPDT) || \
    defined(PART_TM4C129CNCZAD) || defined(PART_TM4C129DNCPDT) || \
    defined(PART_TM4C129DNCZAD) || defined(PART_TM4C129EKCPDT) || \
    defined(PART_TM4C129ENCPDT) || defined(PART_TM4C129ENCZAD) || \
    defined(PART_TM4C129LNCZAD) || defined(PART_TM4C129XKCZAD) || \
    defined(PART_TM4C129XNCZAD)
#define INT_RESOLVE(intname, class) intname##TM4C129
#else
#define INT_DEVICE_CLASS        "UNKNOWN"
#endif

//*****************************************************************************
//
// Macros to resolve the INT_PERIPH_CLASS name to a common INT_PERIPH name.
//
//*****************************************************************************
#define INT_CONCAT(intname, class)  INT_RESOLVE(intname, class)

//*****************************************************************************
//
// The following are defines for the interrupt assignments.
//
//*****************************************************************************
#define INT_ADC0SS0             INT_CONCAT(INT_ADC0SS0_, INT_DEVICE_CLASS)
#define INT_ADC0SS1             INT_CONCAT(INT_ADC0SS1_, INT_DEVICE_CLASS)
#define INT_ADC0SS2             INT_CONCAT(INT_ADC0SS2_, INT_DEVICE_CLASS)
#define INT_ADC0SS3             INT_CONCAT(INT_ADC0SS3_, INT_DEVICE_CLASS)
#define INT_ADC1SS0             INT_CONCAT(INT_ADC1SS0_, INT_DEVICE_CLASS)
#define INT_ADC1SS1             INT_CONCAT(INT_ADC1SS1_, INT_DEVICE_CLASS)
#define INT_ADC1SS2             INT_CONCAT(INT_ADC1SS2_, INT_DEVICE_CLASS)
#define INT_ADC1SS3             INT_CONCAT(INT_ADC1SS3_, INT_DEVICE_CLASS)
#define INT_AES0                INT_CONCAT(INT_AES0_, INT_DEVICE_CLASS)
#define INT_CAN0                INT_CONCAT(INT_CAN0_, INT_DEVICE_CLASS)
#define INT_CAN1                INT_CONCAT(INT_CAN1_, INT_DEVICE_CLASS)
#define INT_COMP0               INT_CONCAT(INT_COMP0_, INT_DEVICE_CLASS)
#define INT_COMP1               INT_CONCAT(INT_COMP1_, INT_DEVICE_CLASS)
#define INT_COMP2               INT_CONCAT(INT_COMP2_, INT_DEVICE_CLASS)
#define INT_DES0                INT_CONCAT(INT_DES0_, INT_DEVICE_CLASS)
#define INT_EMAC0               INT_CONCAT(INT_EMAC0_, INT_DEVICE_CLASS)
#define INT_EPI0                INT_CONCAT(INT_EPI0_, INT_DEVICE_CLASS)
#define INT_FLASH               INT_CONCAT(INT_FLASH_, INT_DEVICE_CLASS)
#define INT_GPIOA               INT_CONCAT(INT_GPIOA_, INT_DEVICE_CLASS)
#define INT_GPIOB               INT_CONCAT(INT_GPIOB_, INT_DEVICE_CLASS)
#define INT_GPIOC               INT_CONCAT(INT_GPIOC_, INT_DEVICE_CLASS)
#define INT_GPIOD               INT_CONCAT(INT_GPIOD_, INT_DEVICE_CLASS)
#define INT_GPIOE               INT_CONCAT(INT_GPIOE_, INT_DEVICE_CLASS)
#define INT_GPIOF               INT_CONCAT(INT_GPIOF_, INT_DEVICE_CLASS)
#define INT_GPIOG               INT_CONCAT(INT_GPIOG_, INT_DEVICE_CLASS)
#define INT_GPIOH               INT_CONCAT(INT_GPIOH_, INT_DEVICE_CLASS)
#define INT_GPIOJ               INT_CONCAT(INT_GPIOJ_, INT_DEVICE_CLASS)
#define INT_GPIOK               INT_CONCAT(INT_GPIOK_, INT_DEVICE_CLASS)
#define INT_GPIOL               INT_CONCAT(INT_GPIOL_, INT_DEVICE_CLASS)
#define INT_GPIOM               INT_CONCAT(INT_GPIOM_, INT_DEVICE_CLASS)
#define INT_GPION               INT_CONCAT(INT_GPION_, INT_DEVICE_CLASS)
#define INT_GPIOP0              INT_CONCAT(INT_GPIOP0_, INT_DEVICE_CLASS)
#define INT_GPIOP1              INT_CONCAT(INT_GPIOP1_, INT_DEVICE_CLASS)
#define INT_GPIOP2              INT_CONCAT(INT_GPIOP2_, INT_DEVICE_CLASS)
#define INT_GPIOP3              INT_CONCAT(INT_GPIOP3_, INT_DEVICE_CLASS)
#define INT_GPIOP4              INT_CONCAT(INT_GPIOP4_, INT_DEVICE_CLASS)
#define INT_GPIOP5              INT_CONCAT(INT_GPIOP5_, INT_DEVICE_CLASS)
#define INT_GPIOP6              INT_CONCAT(INT_GPIOP6_, INT_DEVICE_CLASS)
#define INT_GPIOP7              INT_CONCAT(INT_GPIOP7_, INT_DEVICE_CLASS)
#define INT_GPIOQ0              INT_CONCAT(INT_GPIOQ0_, INT_DEVICE_CLASS)
#define INT_GPIOQ1              INT_CONCAT(INT_GPIOQ1_, INT_DEVICE_CLASS)
#define INT_GPIOQ2              INT_CONCAT(INT_GPIOQ2_, INT_DEVICE_CLASS)
#define INT_GPIOQ3              INT_CONCAT(INT_GPIOQ3_, INT_DEVICE_CLASS)
#define INT_GPIOQ4              INT_CONCAT(INT_GPIOQ4_, INT_DEVICE_CLASS)
#define INT_GPIOQ5              INT_CONCAT(INT_GPIOQ5_, INT_DEVICE_CLASS)
#define INT_GPIOQ6              INT_CONCAT(INT_GPIOQ6_, INT_DEVICE_CLASS)
#define INT_GPIOQ7              INT_CONCAT(INT_GPIOQ7_, INT_DEVICE_CLASS)
#define INT_GPIOR               INT_CONCAT(INT_GPIOR_, INT_DEVICE_CLASS)
#define INT_GPIOS               INT_CONCAT(INT_GPIOS_, INT_DEVICE_CLASS)
#define INT_GPIOT               INT_CONCAT(INT_GPIOT_, INT_DEVICE_CLASS)
#define INT_HIBERNATE           INT_CONCAT(INT_HIBERNATE_, INT_DEVICE_CLASS)
#define INT_I2C0                INT_CONCAT(INT_I2C0_, INT_DEVICE_CLASS)
#define INT_I2C1                INT_CONCAT(INT_I2C1_, INT_DEVICE_CLASS)
#define INT_I2C2                INT_CONCAT(INT_I2C2_, INT_DEVICE_CLASS)
#define INT_I2C3                INT_CONCAT(INT_I2C3_, INT_DEVICE_CLASS)
#define INT_I2C4                INT_CONCAT(INT_I2C4_, INT_DEVICE_CLASS)
#define INT_I2C5                INT_CONCAT(INT_I2C5_, INT_DEVICE_CLASS)
#define INT_I2C6                INT_CONCAT(INT_I2C6_, INT_DEVICE_CLASS)
#define INT_I2C7                INT_CONCAT(INT_I2C7_, INT_DEVICE_CLASS)
#define INT_I2C8                INT_CONCAT(INT_I2C8_, INT_DEVICE_CLASS)
#define INT_I2C9                INT_CONCAT(INT_I2C9_, INT_DEVICE_CLASS)
#define INT_LCD0                INT_CONCAT(INT_LCD0_, INT_DEVICE_CLASS)
#define INT_ONEWIRE0            INT_CONCAT(INT_ONEWIRE0_, INT_DEVICE_CLASS)
#define INT_PWM0_0              INT_CONCAT(INT_PWM0_0_, INT_DEVICE_CLASS)
#define INT_PWM0_1              INT_CONCAT(INT_PWM0_1_, INT_DEVICE_CLASS)
#define INT_PWM0_2              INT_CONCAT(INT_PWM0_2_, INT_DEVICE_CLASS)
#define INT_PWM0_3              INT_CONCAT(INT_PWM0_3_, INT_DEVICE_CLASS)
#define INT_PWM0_FAULT          INT_CONCAT(INT_PWM0_FAULT_, INT_DEVICE_CLASS)
#define INT_PWM1_0              INT_CONCAT(INT_PWM1_0_, INT_DEVICE_CLASS)
#define INT_PWM1_1              INT_CONCAT(INT_PWM1_1_, INT_DEVICE_CLASS)
#define INT_PWM1_2              INT_CONCAT(INT_PWM1_2_, INT_DEVICE_CLASS)
#define INT_PWM1_3              INT_CONCAT(INT_PWM1_3_, INT_DEVICE_CLASS)
#define INT_PWM1_FAULT          INT_CONCAT(INT_PWM1_FAULT_, INT_DEVICE_CLASS)
#define INT_QEI0                INT_CONCAT(INT_QEI0_, INT_DEVICE_CLASS)
#define INT_QEI1                INT_CONCAT(INT_QEI1_, INT_DEVICE_CLASS)
#define INT_SHA0                INT_CONCAT(INT_SHA0_, INT_DEVICE_CLASS)
#define INT_SSI0                INT_CONCAT(INT_SSI0_, INT_DEVICE_CLASS)
#define INT_SSI1                INT_CONCAT(INT_SSI1_, INT_DEVICE_CLASS)
#define INT_SSI2                INT_CONCAT(INT_SSI2_, INT_DEVICE_CLASS)
#define INT_SSI3                INT_CONCAT(INT_SSI3_, INT_DEVICE_CLASS)
#define INT_SYSCTL              INT_CONCAT(INT_SYSCTL_, INT_DEVICE_CLASS)
#define INT_SYSEXC              INT_CONCAT(INT_SYSEXC_, INT_DEVICE_CLASS)
#define INT_TAMPER0             INT_CONCAT(INT_TAMPER0_, INT_DEVICE_CLASS)
#define INT_TIMER0A             INT_CONCAT(INT_TIMER0A_, INT_DEVICE_CLASS)
#define INT_TIMER0B             INT_CONCAT(INT_TIMER0B_, INT_DEVICE_CLASS)
#define INT_TIMER1A             INT_CONCAT(INT_TIMER1A_, INT_DEVICE_CLASS)
#define INT_TIMER1B             INT_CONCAT(INT_TIMER1B_, INT_DEVICE_CLASS)
#define INT_TIMER2A             INT_CONCAT(INT_TIMER2A_, INT_DEVICE_CLASS)
#define INT_TIMER2B             INT_CONCAT(INT_TIMER2B_, INT_DEVICE_CLASS)
#define INT_TIMER3A             INT_CONCAT(INT_TIMER3A_, INT_DEVICE_CLASS)
#define INT_TIMER3B             INT_CONCAT(INT_TIMER3B_, INT_DEVICE_CLASS)
#define INT_TIMER4A             INT_CONCAT(INT_TIMER4A_, INT_DEVICE_CLASS)
#define INT_TIMER4B             INT_CONCAT(INT_TIMER4B_, INT_DEVICE_CLASS)
#define INT_TIMER5A             INT_CONCAT(INT_TIMER5A_, INT_DEVICE_CLASS)
#define INT_TIMER5B             INT_CONCAT(INT_TIMER5B_, INT_DEVICE_CLASS)
#define INT_TIMER6A             INT_CONCAT(INT_TIMER6A_, INT_DEVICE_CLASS)
#define INT_TIMER6B             INT_CONCAT(INT_TIMER6B_, INT_DEVICE_CLASS)
#define INT_TIMER7A             INT_CONCAT(INT_TIMER7A_, INT_DEVICE_CLASS)
#define INT_TIMER7B             INT_CONCAT(INT_TIMER7B_, INT_DEVICE_CLASS)
#define INT_UART0               INT_CONCAT(INT_UART0_, INT_DEVICE_CLASS)
#define INT_UART1               INT_CONCAT(INT_UART1_, INT_DEVICE_CLASS)
#define INT_UART2               INT_CONCAT(INT_UART2_, INT_DEVICE_CLASS)
#define INT_UART3               INT_CONCAT(INT_UART3_, INT_DEVICE_CLASS)
#define INT_UART4               INT_CONCAT(INT_UART4_, INT_DEVICE_CLASS)
#define INT_UART5               INT_CONCAT(INT_UART5_, INT_DEVICE_CLASS)
#define INT_UART6               INT_CONCAT(INT_UART6_, INT_DEVICE_CLASS)
#define INT_UART7               INT_CONCAT(INT_UART7_, INT_DEVICE_CLASS)
#define INT_UDMA                INT_CONCAT(INT_UDMA_, INT_DEVICE_CLASS)
#define INT_UDMAERR             INT_CONCAT(INT_UDMAERR_, INT_DEVICE_CLASS)
#define INT_USB0                INT_CONCAT(INT_USB0_, INT_DEVICE_CLASS)
#define INT_WATCHDOG            INT_CONCAT(INT_WATCHDOG_, INT_DEVICE_CLASS)
#define INT_WTIMER0A            INT_CONCAT(INT_WTIMER0A_, INT_DEVICE_CLASS)
#define INT_WTIMER0B            INT_CONCAT(INT_WTIMER0B_, INT_DEVICE_CLASS)
#define INT_WTIMER1A            INT_CONCAT(INT_WTIMER1A_, INT_DEVICE_CLASS)
#define INT_WTIMER1B            INT_CONCAT(INT_WTIMER1B_, INT_DEVICE_CLASS)
#define INT_WTIMER2A            INT_CONCAT(INT_WTIMER2A_, INT_DEVICE_CLASS)
#define INT_WTIMER2B            INT_CONCAT(INT_WTIMER2B_, INT_DEVICE_CLASS)
#define INT_WTIMER3A            INT_CONCAT(INT_WTIMER3A_, INT_DEVICE_CLASS)
#define INT_WTIMER3B            INT_CONCAT(INT_WTIMER3B_, INT_DEVICE_CLASS)
#define INT_WTIMER4A            INT_CONCAT(INT_WTIMER4A_, INT_DEVICE_CLASS)
#define INT_WTIMER4B            INT_CONCAT(INT_WTIMER4B_, INT_DEVICE_CLASS)
#define INT_WTIMER5A            INT_CONCAT(INT_WTIMER5A_, INT_DEVICE_CLASS)
#define INT_WTIMER5B            INT_CONCAT(INT_WTIMER5B_, INT_DEVICE_CLASS)

//*****************************************************************************
//
// The following are defines for the total number of interrupts.
//
//*****************************************************************************
#define NUM_INTERRUPTS          INT_CONCAT(NUM_INTERRUPTS_, INT_DEVICE_CLASS)

//*****************************************************************************
//
// The following are defines for the total number of priority levels.
//
//*****************************************************************************
#define NUM_PRIORITY            8
#define NUM_PRIORITY_BITS       3

#endif // __HW_INTS_H__
