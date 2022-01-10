;/*
; * Copyright (c) 2006-2021, RT-Thread Development Team
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Change Logs:
; * Date           Author       Notes
; * 2021-12-18     BruceOu        first implementation
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
    .word     WWDGT_IRQHandler                  // 16:Window Watchdog Timer
    .word     LVD_IRQHandler                    // 17:LVD through EXTI Line detect
    .word     TAMPER_IRQHandler                 // 18:Tamper through EXTI Line detect
    .word     RTC_IRQHandler                    // 19:RTC through EXTI Line
    .word     FMC_IRQHandler                    // 20:FMC
    .word     RCU_CTC_IRQHandler                // 21:RCU and CTC
    .word     EXTI0_IRQHandler                  // 22:EXTI Line 0
    .word     EXTI1_IRQHandler                  // 23:EXTI Line 1
    .word     EXTI2_IRQHandler                  // 24:EXTI Line 2
    .word     EXTI3_IRQHandler                  // 25:EXTI Line 3
    .word     EXTI4_IRQHandler                  // 26:EXTI Line 4
    .word     DMA0_Channel0_IRQHandler          // 27:DMA0 Channel0
    .word     DMA0_Channel1_IRQHandler          // 28:DMA0 Channel1
    .word     DMA0_Channel2_IRQHandler          // 29:DMA0 Channel2
    .word     DMA0_Channel3_IRQHandler          // 30:DMA0 Channel3
    .word     DMA0_Channel4_IRQHandler          // 31:DMA0 Channel4
    .word     DMA0_Channel5_IRQHandler          // 32:DMA0 Channel5
    .word     DMA0_Channel6_IRQHandler          // 33:DMA0 Channel6
    .word     ADC0_1_IRQHandler                 // 34:ADC0 and ADC1
    .word     USBD_HP_CAN0_TX_IRQHandler        // 35:USBD HP and CAN0 TX
    .word     USBD_LP_CAN0_RX0_IRQHandler       // 36:USBD LP and CAN0 RX0
    .word     CAN0_RX1_IRQHandler               // 37:CAN0 RX1
    .word     CAN0_EWMC_IRQHandler              // 38:CAN0 EWMC
    .word     EXTI5_9_IRQHandler                // 39:EXTI5 to EXTI9
    .word     TIMER0_BRK_IRQHandler             // 40:TIMER0 Break
    .word     TIMER0_UP_IRQHandler              // 41:TIMER0 Update
    .word     TIMER0_TRG_CMT_IRQHandler         // 42:TIMER0 Trigger and Commutation
    .word     TIMER0_Channel_IRQHandler         // 43:TIMER0 Channel Capture Compare
    .word     TIMER1_IRQHandler                 // 44:TIMER1
    .word     TIMER2_IRQHandler                 // 45:TIMER2
    .word     TIMER3_IRQHandler                 // 46:TIMER3
    .word     I2C0_EV_IRQHandler                // 47:I2C0 Event
    .word     I2C0_ER_IRQHandler                // 48:I2C0 Error
    .word     I2C1_EV_IRQHandler                // 49:I2C1 Event
    .word     I2C1_ER_IRQHandler                // 50:I2C1 Error
    .word     SPI0_IRQHandler                   // 51:SPI0
    .word     SPI1_IRQHandler                   // 52:SPI1
    .word     USART0_IRQHandler                 // 53:USART0
    .word     USART1_IRQHandler                 // 54:USART1
    .word     USART2_IRQHandler                 // 55:USART2
    .word     EXTI10_15_IRQHandler              // 56:EXTI10 to EXTI15
    .word     RTC_Alarm_IRQHandler              // 57:RTC Alarm
    .word     USBD_WKUP_IRQHandler              // 58:USBD Wakeup
    .word     TIMER7_BRK_IRQHandler             // 59:TIMER7 Break
    .word     TIMER7_UP_IRQHandler              // 60:TIMER7 Update
    .word     TIMER7_TRG_CMT_IRQHandler         // 61:TIMER7 Trigger and Commutation
    .word     TIMER7_Channel_IRQHandler         // 62:TIMER7 Channel Capture Compare
    .word     0                                 // 63:Reserved
    .word     EXMC_IRQHandler                   // 64:EXMC
    .word     0                                 // 65:Reserved
    .word     TIMER4_IRQHandler                 // 66:TIMER4
    .word     SPI2_IRQHandler                   // 67:SPI2
    .word     UART3_IRQHandler                  // 68:UART3
    .word     UART4_IRQHandler                  // 69:UART4
    .word     TIMER5_IRQHandler                 // 70:TIMER5
    .word     TIMER6_IRQHandler                 // 71:TIMER6
    .word     DMA1_Channel0_IRQHandler          // 72:DMA1 Channel0
    .word     DMA1_Channel1_IRQHandler          // 73:DMA1 Channel1
    .word     DMA1_Channel2_IRQHandler          // 74:DMA1 Channel2
    .word     DMA1_Channel3_IRQHandler          // 75:DMA1 Channel3
	.word     DMA1_Channel4_IRQHandler          // 76:DMA1 Channel4
    .word     ENET_IRQHandler                   // 77:Ethernet
    .word     ENET_WKUP_IRQHandler              // 78:Ethernet Wakeup through EXTI Line
    .word     CAN1_TX_IRQHandler                // 79:CAN1 TX
    .word     CAN1_RX0_IRQHandler               // 80:CAN1 RX0
    .word     CAN1_RX1_IRQHandler               // 81:CAN1 RX1
    .word     CAN1_EWMC_IRQHandler              // 82:CAN1 EWMC
    .word     USBFS_IRQHandler                  // 83:USBFS

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

    IRQ WWDGT_IRQHandler
    IRQ LVD_IRQHandler
    IRQ TAMPER_IRQHandler
    IRQ RTC_IRQHandler
    IRQ FMC_IRQHandler
    IRQ RCU_CTC_IRQHandler
    IRQ EXTI0_IRQHandler
    IRQ EXTI1_IRQHandler
    IRQ EXTI2_IRQHandler
    IRQ EXTI3_IRQHandler
    IRQ EXTI4_IRQHandler
    IRQ DMA0_Channel0_IRQHandler
    IRQ DMA0_Channel1_IRQHandler
    IRQ DMA0_Channel2_IRQHandler
    IRQ DMA0_Channel3_IRQHandler
    IRQ DMA0_Channel4_IRQHandler
    IRQ DMA0_Channel5_IRQHandler
    IRQ DMA0_Channel6_IRQHandler
    IRQ ADC0_1_IRQHandler
    IRQ USBD_HP_CAN0_TX_IRQHandler
    IRQ USBD_LP_CAN0_RX0_IRQHandler
    IRQ CAN0_RX1_IRQHandler
    IRQ CAN0_EWMC_IRQHandler
    IRQ EXTI5_9_IRQHandler
    IRQ TIMER0_BRK_IRQHandler
    IRQ TIMER0_UP_IRQHandler
    IRQ TIMER0_TRG_CMT_IRQHandler
    IRQ TIMER0_Channel_IRQHandler
    IRQ TIMER1_IRQHandler
    IRQ TIMER2_IRQHandler
    IRQ TIMER3_IRQHandler
    IRQ I2C0_EV_IRQHandler
    IRQ I2C0_ER_IRQHandler
    IRQ I2C1_EV_IRQHandler
    IRQ I2C1_ER_IRQHandler
    IRQ SPI0_IRQHandler
    IRQ SPI1_IRQHandler
    IRQ USART0_IRQHandler
    IRQ USART1_IRQHandler
    IRQ USART2_IRQHandler
    IRQ EXTI10_15_IRQHandler
    IRQ RTC_Alarm_IRQHandler
    IRQ USBD_WKUP_IRQHandler
    IRQ TIMER7_BRK_IRQHandler
    IRQ TIMER7_UP_IRQHandler
    IRQ TIMER7_TRG_CMT_IRQHandler
    IRQ TIMER7_Channel_IRQHandler
    IRQ ADC2_IRQHandler
    IRQ EXMC_IRQHandler
    IRQ SDIO_IRQHandler
    IRQ TIMER4_IRQHandler
    IRQ SPI2_IRQHandler
    IRQ UART3_IRQHandler
    IRQ UART4_IRQHandler
    IRQ TIMER5_IRQHandler
    IRQ TIMER6_IRQHandler
    IRQ DMA1_Channel0_IRQHandler
    IRQ DMA1_Channel1_IRQHandler
    IRQ DMA1_Channel2_IRQHandler
    IRQ DMA1_Channel3_IRQHandler
	IRQ DMA1_Channel4_IRQHandler
	IRQ ENET_IRQHandler
	IRQ ENET_WKUP_IRQHandler
	IRQ CAN1_TX_IRQHandler
    IRQ CAN1_RX0_IRQHandler
    IRQ CAN1_RX1_IRQHandler
    IRQ CAN1_EWMC_IRQHandler
    IRQ USBFS_IRQHandler
