;/*!
; * @file        startup_apm32f10x_hd.s
; *
; * @brief       CMSIS Cortex-M3 based Core Device Startup File for Device startup_apm32f10x_hd
; *
; * @version     V1.0.0
; *
; * @date        2022-01-05
; *
; * @attention
; *
; *  Copyright (C) 2020-2022 Geehy Semiconductor
; *
; *  You may not use this file except in compliance with the
; *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
; *
; *  The program is only for reference, which is distributed in the hope
; *  that it will be usefull and instructional for customers to develop
; *  their software. Unless required by applicable law or agreed to in
; *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
; *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
; *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
; *  and limitations under the License.
; */

.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.global  g_pfnVectors
.global  Default_Handler

    .section  .isr_vector,"a",%progbits
    .type  g_pfnVectors, %object

g_pfnVectors:
    .word     _estack                           // Top of Stack
    .word     Reset_Handler                     // Reset Handler
    .word     NMI_Handler                       // NMI Handler
    .word     HardFault_Handler                 // Hard Fault Handler
    .word     MemManage_Handler                 // MPU Fault Handler
    .word     BusFault_Handler                  // Bus Fault Handler
    .word     UsageFault_Handler                // Usage Fault Handler
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     SVC_Handler                       // SVCall Handler
    .word     DebugMon_Handler                  // Debug Monitor Handler
    .word     0                                 // Reserved
    .word     PendSV_Handler                    // PendSV Handler
    .word     SysTick_Handler                   // SysTick Handler

    // external interrupts handler
    .word     WWDT_IRQHandler              // Window Watchdog
    .word     PVD_IRQHandler               // PVD through EINT Line detect
    .word     TAMPER_IRQHandler            // Tamper
    .word     RTC_IRQHandler               // RTC
    .word     FLASH_IRQHandler             // Flash
    .word     RCM_IRQHandler               // RCM
    .word     EINT0_IRQHandler             // EINT Line 0
    .word     EINT1_IRQHandler             // EINT Line 1
    .word     EINT2_IRQHandler             // EINT Line 2
    .word     EINT3_IRQHandler             // EINT Line 3
    .word     EINT4_IRQHandler             // EINT Line 4
    .word     DMA1_Channel1_IRQHandler     // DMA1 Channel 1
    .word     DMA1_Channel2_IRQHandler     // DMA1 Channel 2
    .word     DMA1_Channel3_IRQHandler     // DMA1 Channel 3
    .word     DMA1_Channel4_IRQHandler     // DMA1 Channel 4
    .word     DMA1_Channel5_IRQHandler     // DMA1 Channel 5
    .word     DMA1_Channel6_IRQHandler     // DMA1 Channel 6
    .word     DMA1_Channel7_IRQHandler     // DMA1 Channel 7
    .word     ADC1_2_IRQHandler            // ADC1_2
    .word     USBD1_HP_CAN1_TX_IRQHandler  // USBD1 High Priority or CAN1 TX
    .word     USBD1_LP_CAN1_RX0_IRQHandler // USBD1 Low  Priority or CAN1 RX0
    .word     CAN1_RX1_IRQHandler          // CAN1 RX1
    .word     CAN1_SCE_IRQHandler          // CAN1 SCE
    .word     EINT9_5_IRQHandler           // EINT Line 9..5
    .word     TMR1_BRK_IRQHandler          // TMR1 Break
    .word     TMR1_UP_IRQHandler           // TMR1 Update
    .word     TMR1_TRG_COM_IRQHandler      // TMR1 Trigger and Commutation
    .word     TMR1_CC_IRQHandler           // TMR1 Capture Compare
    .word     TMR2_IRQHandler              // TMR2
    .word     TMR3_IRQHandler              // TMR3
    .word     TMR4_IRQHandler              // TMR4
    .word     I2C1_EV_IRQHandler           // I2C1 Event
    .word     I2C1_ER_IRQHandler           // I2C1 Error
    .word     I2C2_EV_IRQHandler           // I2C2 Event
    .word     I2C2_ER_IRQHandler           // I2C2 Error
    .word     SPI1_IRQHandler              // SPI1
    .word     SPI2_IRQHandler              // SPI2
    .word     USART1_IRQHandler            // USART1
    .word     USART2_IRQHandler            // USART2
    .word     USART3_IRQHandler            // USART3
    .word     EINT15_10_IRQHandler         // EINT Line 15..10
    .word     RTCAlarm_IRQHandler          // RTC Alarm through EINT Line
    .word     USBDWakeUp_IRQHandler        // USBD Wakeup from suspend
    .word     FPU_IRQHandler               // FPU
    .word     QSPI_IRQHandler              // QSPI
    .word     USBD2_HP_IRQHandler          // USBD2 High Priority
    .word     USBD2_LP_IRQHandler          // USBD2 Low Priority

    .size  g_pfnVectors, .-g_pfnVectors

    .section  .text.Reset_Handler
    .weak  Reset_Handler
    .type  Reset_Handler, %function
Reset_Handler:
    ldr r1, =_sidata
    ldr r2, =_sdata
    ldr r3, =_edata

    subs r3, r2
    ble fill_bss_start

loop_copy_data:
    subs r3, #4
    ldr r0, [r1,r3]
    str r0, [r2,r3]
    bgt loop_copy_data

fill_bss_start:
    ldr r1, =__bss_start
    ldr r2, =__bss_end
    movs r0, 0
    subs r2, r1
    ble startup_enter

loop_fill_bss:
    subs r2, #4
    str r0, [r1, r2]
    bgt loop_fill_bss

startup_enter:
    bl SystemInit
    bl entry

    /* Exception Handlers */
    .weak   NMI_Handler
    .type   NMI_Handler, %function
NMI_Handler:
    b       .
    .size   NMI_Handler, . - NMI_Handler

    .weak   MemManage_Handler
    .type   MemManage_Handler, %function
MemManage_Handler:
    b       .
    .size   MemManage_Handler, . - MemManage_Handler

    .weak   BusFault_Handler
    .type   BusFault_Handler, %function
BusFault_Handler:
    b       .
    .size   BusFault_Handler, . - BusFault_Handler

    .weak   UsageFault_Handler
    .type   UsageFault_Handler, %function
UsageFault_Handler:
    b       .
    .size   UsageFault_Handler, . - UsageFault_Handler

    .weak   SVC_Handler
    .type   SVC_Handler, %function
SVC_Handler:
    b       .
    .size   SVC_Handler, . - SVC_Handler

    .weak   DebugMon_Handler
    .type   DebugMon_Handler, %function
DebugMon_Handler:
    b       .
    .size   DebugMon_Handler, . - DebugMon_Handler

    .weak   PendSV_Handler
    .type   PendSV_Handler, %function
PendSV_Handler:
    b       .
    .size   PendSV_Handler, . - PendSV_Handler

    .weak   SysTick_Handler
    .type   SysTick_Handler, %function
SysTick_Handler:
    b       .
    .size   SysTick_Handler, . - SysTick_Handler

    /* IQR Handler */
    .section  .text.Default_Handler,"ax",%progbits
    .type  Default_Handler, %function
Default_Handler:
    b  .
    .size  Default_Handler, . - Default_Handler

    .macro  IRQ handler
    .weak   \handler
    .set    \handler, Default_Handler
    .endm

    IRQ WWDT_IRQHandler
    IRQ PVD_IRQHandler
    IRQ TAMPER_IRQHandler
    IRQ RTC_IRQHandler
    IRQ FLASH_IRQHandler
    IRQ RCM_IRQHandler
    IRQ EINT0_IRQHandler
    IRQ EINT1_IRQHandler
    IRQ EINT2_IRQHandler
    IRQ EINT3_IRQHandler
    IRQ EINT4_IRQHandler
    IRQ DMA1_Channel1_IRQHandler
    IRQ DMA1_Channel2_IRQHandler
    IRQ DMA1_Channel3_IRQHandler
    IRQ DMA1_Channel4_IRQHandler
    IRQ DMA1_Channel5_IRQHandler
    IRQ DMA1_Channel6_IRQHandler
    IRQ DMA1_Channel7_IRQHandler
    IRQ ADC1_2_IRQHandler
    IRQ USBD1_HP_CAN1_TX_IRQHandler
    IRQ USBD1_LP_CAN1_RX0_IRQHandler
    IRQ CAN1_RX1_IRQHandler
    IRQ CAN1_SCE_IRQHandler
    IRQ EINT9_5_IRQHandler
    IRQ TMR1_BRK_IRQHandler
    IRQ TMR1_UP_IRQHandler
    IRQ TMR1_TRG_COM_IRQHandler
    IRQ TMR1_CC_IRQHandler
    IRQ TMR2_IRQHandler
    IRQ TMR3_IRQHandler
    IRQ TMR4_IRQHandler
    IRQ I2C1_EV_IRQHandler
    IRQ I2C1_ER_IRQHandler
    IRQ I2C2_EV_IRQHandler
    IRQ I2C2_ER_IRQHandler
    IRQ SPI1_IRQHandler
    IRQ SPI2_IRQHandler
    IRQ USART1_IRQHandler
    IRQ USART2_IRQHandler
    IRQ USART3_IRQHandler
    IRQ EINT15_10_IRQHandler
    IRQ RTCAlarm_IRQHandler
    IRQ USBDWakeUp_IRQHandler
    IRQ FPU_IRQHandler
    IRQ QSPI_IRQHandler
    IRQ USBD2_HP_IRQHandler
    IRQ USBD2_LP_IRQHandler
