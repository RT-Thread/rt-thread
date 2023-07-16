//*****************************************************************************
//
// interrupt.h - Prototypes for the NVIC Interrupt Controller Driver.
//
// Copyright (c) 2005-2017 Texas Instruments Incorporated.  All rights reserved.
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
//*****************************************************************************

#ifndef __DRIVERLIB_INTERRUPT_H__
#define __DRIVERLIB_INTERRUPT_H__

#include <stdint.h>
#include <stdbool.h>

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

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
// MSP432E4 Interrupts
//
//*****************************************************************************
#define INT_GPIOA       16          // GPIO Port A
#define INT_GPIOB       17          // GPIO Port B
#define INT_GPIOC       18          // GPIO Port C
#define INT_GPIOD       19          // GPIO Port D
#define INT_GPIOE       20          // GPIO Port E
#define INT_UART0       21          // UART0
#define INT_UART1       22          // UART1
#define INT_SSI0        23          // SSI0
#define INT_I2C0        24          // I2C0
#define INT_PWM0_FAULT  25          // PWM Fault
#define INT_PWM0_0      26          // PWM Generator 0
#define INT_PWM0_1      27          // PWM Generator 1
#define INT_PWM0_2      28          // PWM Generator 2
#define INT_QEI0        29          // QEI0
#define INT_ADC0SS0     30          // ADC0 Sequence 0
#define INT_ADC0SS1     31          // ADC0 Sequence 1
#define INT_ADC0SS2     32          // ADC0 Sequence 2
#define INT_ADC0SS3     33          // ADC0 Sequence 3
#define INT_WATCHDOG    34          // Watchdog Timers 0 and 1
#define INT_TIMER0A     35          // 16/32-Bit Timer 0A
#define INT_TIMER0B     36          // 16/32-Bit Timer 0B
#define INT_TIMER1A     37          // 16/32-Bit Timer 1A
#define INT_TIMER1B     38          // 16/32-Bit Timer 1B
#define INT_TIMER2A     39          // 16/32-Bit Timer 2A
#define INT_TIMER2B     40          // 16/32-Bit Timer 2B
#define INT_COMP0       41          // Analog Comparator 0
#define INT_COMP1       42          // Analog Comparator 1
#define INT_COMP2       43          // Analog Comparator 2
#define INT_SYSCTL      44          // System Control
#define INT_FLASH       45          // Flash Memory Control
#define INT_GPIOF       46          // GPIO Port F
#define INT_GPIOG       47          // GPIO Port G
#define INT_GPIOH       48          // GPIO Port H
#define INT_UART2       49          // UART2
#define INT_SSI1        50          // SSI1
#define INT_TIMER3A     51          // 16/32-Bit Timer 3A
#define INT_TIMER3B     52          // 16/32-Bit Timer 3B
#define INT_I2C1        53          // I2C1
#define INT_CAN0        54          // CAN 0
#define INT_CAN1        55          // CAN1
#define INT_EMAC0       56          // Ethernet MAC
#define INT_HIBERNATE   57          // HIB
#define INT_USB0        58          // USB MAC
#define INT_PWM0_3      59          // PWM Generator 3
#define INT_UDMA        60          // uDMA 0 Software
#define INT_UDMAERR     61          // uDMA 0 Error
#define INT_ADC1SS0     62          // ADC1 Sequence 0
#define INT_ADC1SS1     63          // ADC1 Sequence 1
#define INT_ADC1SS2     64          // ADC1 Sequence 2
#define INT_ADC1SS3     65          // ADC1 Sequence 3
#define INT_EPI0        66          // EPI 0
#define INT_GPIOJ       67          // GPIO Port J
#define INT_GPIOK       68          // GPIO Port K
#define INT_GPIOL       69          // GPIO Port L
#define INT_SSI2        70          // SSI 2
#define INT_SSI3        71          // SSI 3
#define INT_UART3       72          // UART 3
#define INT_UART4       73          // UART 4
#define INT_UART5       74          // UART 5
#define INT_UART6       75          // UART 6
#define INT_UART7       76          // UART 7
#define INT_I2C2        77          // I2C 2
#define INT_I2C3        78          // I2C 3
#define INT_TIMER4A     79          // Timer 4A
#define INT_TIMER4B     80          // Timer 4B
#define INT_TIMER5A     81          // Timer 5A
#define INT_TIMER5B     82          // Timer 5B
#define INT_SYSEXC      83          // Floating-Point Exception
                                            // (imprecise)
#define INT_I2C4        86          // I2C 4
#define INT_I2C5        87          // I2C 5
#define INT_GPIOM       88          // GPIO Port M
#define INT_GPION       89          // GPIO Port N
#define INT_TAMPER0     91          // Tamper
#define INT_GPIOP0      92          // GPIO Port P (Summary or P0)
#define INT_GPIOP1      93          // GPIO Port P1
#define INT_GPIOP2      94          // GPIO Port P2
#define INT_GPIOP3      95          // GPIO Port P3
#define INT_GPIOP4      96          // GPIO Port P4
#define INT_GPIOP5      97          // GPIO Port P5
#define INT_GPIOP6      98          // GPIO Port P6
#define INT_GPIOP7      99          // GPIO Port P7
#define INT_GPIOQ0      100         // GPIO Port Q (Summary or Q0)
#define INT_GPIOQ1      101         // GPIO Port Q1
#define INT_GPIOQ2      102         // GPIO Port Q2
#define INT_GPIOQ3      103         // GPIO Port Q3
#define INT_GPIOQ4      104         // GPIO Port Q4
#define INT_GPIOQ5      105         // GPIO Port Q5
#define INT_GPIOQ6      106         // GPIO Port Q6
#define INT_GPIOQ7      107         // GPIO Port Q7
#define INT_GPIOR       108         // GPIO Port R
#define INT_GPIOS       109         // GPIO Port S
#define INT_SHA0        110         // SHA/MD5
#define INT_AES0        111         // AES
#define INT_DES0        112         // DES
#define INT_LCD0        113         // LCD
#define INT_TIMER6A     114         // 16/32-Bit Timer 6A
#define INT_TIMER6B     115         // 16/32-Bit Timer 6B
#define INT_TIMER7A     116         // 16/32-Bit Timer 7A
#define INT_TIMER7B     117         // 16/32-Bit Timer 7B
#define INT_I2C6        118         // I2C 6
#define INT_I2C7        119         // I2C 7
#define INT_ONEWIRE0    121         // 1-Wire
#define INT_I2C8        125         // I2C 8
#define INT_I2C9        126         // I2C 9
#define INT_GPIOT       127         // GPIO T
#define NUM_INTERRUPTS  129

//*****************************************************************************
//
// The following are defines for the total number of priority levels.
//
//*****************************************************************************
#define NUM_PRIORITY            8
#define NUM_PRIORITY_BITS       3

//*****************************************************************************
//
// Macro to generate an interrupt priority mask based on the number of bits
// of priority supported by the hardware.
//
//*****************************************************************************
#define INT_PRIORITY_MASK       ((0xFF << (8 - NUM_PRIORITY_BITS)) & 0xFF)

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
extern bool IntMasterEnable(void);
extern bool IntMasterDisable(void);
extern void IntRegister(uint32_t ui32Interrupt, void (*pfnHandler)(void));
extern void IntUnregister(uint32_t ui32Interrupt);
extern void IntPriorityGroupingSet(uint32_t ui32Bits);
extern uint32_t IntPriorityGroupingGet(void);
extern void IntPrioritySet(uint32_t ui32Interrupt,
                           uint8_t ui8Priority);
extern int32_t IntPriorityGet(uint32_t ui32Interrupt);
extern void IntEnable(uint32_t ui32Interrupt);
extern void IntDisable(uint32_t ui32Interrupt);
extern uint32_t IntIsEnabled(uint32_t ui32Interrupt);
extern void IntPendSet(uint32_t ui32Interrupt);
extern void IntPendClear(uint32_t ui32Interrupt);
extern void IntPriorityMaskSet(uint32_t ui32PriorityMask);
extern uint32_t IntPriorityMaskGet(void);
extern void IntTrigger(uint32_t ui32Interrupt);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_INTERRUPT_H__
