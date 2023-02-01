/*!
 * @file       startup_apm32f103_hd.S
 *
 * @brief      CMSIS Cortex-M3 based Core Device Startup File for Device startup_apm32f103_hd
 *
 * @version    V1.0.1
 *
 * @date       2022-12-01
 *
 * @attention
 *
 *  Copyright (C) 2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

  .syntax unified
  .cpu cortex-m3
  .fpu softvfp
  .thumb

.global g_apm32_Vectors
.global Default_Handler

.word _start_address_init_data
.word _start_address_data
.word _end_address_data
.word _start_address_bss
.word _end_address_bss

  .section .text.Reset_Handler
  .weak Reset_Handler
  .type Reset_Handler, %function
// Reset handler routine
Reset_Handler:

  ldr r0, =_start_address_data
  ldr r1, =_end_address_data
  ldr r2, =_start_address_init_data
  movs r3, #0
  b L_loop0_0

L_loop0:
  ldr r4, [r2, r3]
  str r4, [r0, r3]
  adds r3, r3, #4

L_loop0_0:
  adds r4, r0, r3
  cmp r4, r1
  bcc L_loop0
  
  ldr r2, =_start_address_bss
  ldr r4, =_end_address_bss
  movs r3, #0
  b L_loop1

L_loop2:
  str  r3, [r2]
  adds r2, r2, #4

L_loop1:
  cmp r2, r4
  bcc L_loop2

    bl  SystemInit
    bl __libc_init_array
  bl entry
  bx lr
.size Reset_Handler, .-Reset_Handler

// This is the code that gets called when the processor receives an unexpected interrupt.
    .section .text.Default_Handler,"ax",%progbits
Default_Handler:
L_Loop_infinite:
  b L_Loop_infinite
  .size Default_Handler, .-Default_Handler

// The minimal vector table for a Cortex M3.
   .section .isr_vector,"a",%progbits
  .type g_apm32_Vectors, %object
  .size g_apm32_Vectors, .-g_apm32_Vectors

// Vector Table Mapped to Address 0 at Reset
g_apm32_Vectors:

  .word _end_stack                          // Top of Stack
  .word Reset_Handler                       // Reset Handler
  .word NMI_Handler                         // NMI Handler
  .word HardFault_Handler                   // Hard Fault Handler
  .word MemManage_Handler                   // MPU Fault Handler
  .word BusFault_Handler                    // Bus Fault Handler
  .word UsageFault_Handler                  // Usage Fault Handler
  .word 0                                   // Reserved
  .word 0                                   // Reserved
  .word 0                                   // Reserved
  .word 0                                   // Reserved
  .word SVC_Handler                         // SVCall Handler
  .word DebugMon_Handler                    // Debug Monitor Handler
  .word 0                                   // Reserved
  .word PendSV_Handler                      // PendSV Handler
  .word SysTick_Handler                     // SysTick Handler
  .word WWDT_IRQHandler                     // Window Watchdog
  .word PVD_IRQHandler                      // PVD through EINT Line detect
  .word TAMPER_IRQHandler                   // Tamper
  .word RTC_IRQHandler                      // RTC
  .word FLASH_IRQHandler                    // Flash
  .word RCM_IRQHandler                      // RCM
  .word EINT0_IRQHandler                    // EINT Line 0
  .word EINT1_IRQHandler                    // EINT Line 1
  .word EINT2_IRQHandler                    // EINT Line 2
  .word EINT3_IRQHandler                    // EINT Line 3
  .word EINT4_IRQHandler                    // EINT Line 4
  .word DMA1_Channel1_IRQHandler            // DMA1 Channel 1
  .word DMA1_Channel2_IRQHandler            // DMA1 Channel 2
  .word DMA1_Channel3_IRQHandler            // DMA1 Channel 3
  .word DMA1_Channel4_IRQHandler            // DMA1 Channel 4
  .word DMA1_Channel5_IRQHandler            // DMA1 Channel 5
  .word DMA1_Channel6_IRQHandler            // DMA1 Channel 6
  .word DMA1_Channel7_IRQHandler            // DMA1 Channel 7
  .word ADC1_2_IRQHandler                   // ADC1 & ADC2
  .word CAN1_TX_IRQHandler                  // CAN1 TX
  .word CAN1_RX0_IRQHandler                 // CAN1 RX0
  .word CAN1_RX1_IRQHandler                 // CAN1 RX1
  .word CAN1_SCE_IRQHandler                 // CAN1 SCE
  .word EINT9_5_IRQHandler                  // EINT Line 9..5
  .word TMR1_BRK_IRQHandler                 // TMR1 Break
  .word TMR1_UP_IRQHandler                  // TMR1 Update
  .word TMR1_TRG_COM_IRQHandler             // TMR1 Trigger and Commutation
  .word TMR1_CC_IRQHandler                  // TMR1 Capture Compare
  .word TMR2_IRQHandler                     // TMR2
  .word TMR3_IRQHandler                     // TMR3
  .word TMR4_IRQHandler                     // TMR4
  .word I2C1_EV_IRQHandler                  // I2C1 Event
  .word I2C1_ER_IRQHandler                  // I2C1 Error
  .word I2C2_EV_IRQHandler                  // I2C2 Event
  .word I2C2_ER_IRQHandler                  // I2C2 Error
  .word SPI1_IRQHandler                     // SPI1
  .word SPI2_IRQHandler                     // SPI2
  .word USART1_IRQHandler                   // USART1
  .word USART2_IRQHandler                   // USART2
  .word USART3_IRQHandler                   // USART3
  .word EINT15_10_IRQHandler                // EINT Line 15..10
  .word RTCAlarm_IRQHandler                 // RTC Alarm through EINT Line
  .word OTG_FS_WKUP_IRQHandler              // USBD Wakeup from suspend
  .word 0                                   // Reserved
  .word 0                                   // Reserved
  .word 0                                   // Reserved
  .word 0                                   // Reserved
  .word 0                                   // Reserved
  .word 0                                   // Reserved
  .word 0                                   // Reserved
  .word TMR5_IRQHandler                     // TMR5
  .word SPI3_IRQHandler                     // SPI3
  .word UART4_IRQHandler                    // UART4
  .word UART5_IRQHandler                    // UART5
  .word TMR6_IRQHandler                     // TMR6
  .word TMR7_IRQHandler                     // TMR7
  .word DMA2_Channel1_IRQHandler            // DMA2 Channel1
  .word DMA2_Channel2_IRQHandler            // DMA2 Channel2
  .word DMA2_Channel3_IRQHandler            // DMA2 Channel3
  .word DMA2_Channel4_IRQHandler            // DMA2 Channel4
  .word DMA2_Channel5_IRQHandler            // DMA2 Channel5
  .word ETH_IRQHandler                      // ETH
  .word ETH_WKUP_IRQHandler                 // ETH Wake up
  .word CAN2_TX_IRQHandler                  // CAN2 TX
  .word CAN2_RX0_IRQHandler                 // CAN2 RX0
  .word CAN2_RX1_IRQHandler                 // CAN2 RX1
  .word CAN2_SCE_IRQHandler                 // CAN2 SCE
  .word OTG_FS_IRQHandler                   // OTG FS

// Default exception/interrupt handler

  .weak NMI_Handler
  .thumb_set NMI_Handler,Default_Handler

  .weak HardFault_Handler
  .thumb_set HardFault_Handler,Default_Handler

  .weak MemManage_Handler
  .thumb_set MemManage_Handler,Default_Handler

  .weak BusFault_Handler
  .thumb_set BusFault_Handler,Default_Handler

  .weak UsageFault_Handler
  .thumb_set UsageFault_Handler,Default_Handler

  .weak SVC_Handler
  .thumb_set SVC_Handler,Default_Handler

  .weak DebugMon_Handler
  .thumb_set DebugMon_Handler,Default_Handler

  .weak PendSV_Handler
  .thumb_set PendSV_Handler,Default_Handler

  .weak SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler

  .weak WWDT_IRQHandler
  .thumb_set WWDT_IRQHandler,Default_Handler

  .weak PVD_IRQHandler
  .thumb_set PVD_IRQHandler,Default_Handler

  .weak TAMPER_IRQHandler
  .thumb_set TAMPER_IRQHandler,Default_Handler

  .weak RTC_IRQHandler
  .thumb_set RTC_IRQHandler,Default_Handler

  .weak FLASH_IRQHandler
  .thumb_set FLASH_IRQHandler,Default_Handler

  .weak RCM_IRQHandler
  .thumb_set RCM_IRQHandler,Default_Handler

  .weak EINT0_IRQHandler
  .thumb_set EINT0_IRQHandler,Default_Handler

  .weak EINT1_IRQHandler
  .thumb_set EINT1_IRQHandler,Default_Handler

  .weak EINT2_IRQHandler
  .thumb_set EINT2_IRQHandler,Default_Handler

  .weak EINT3_IRQHandler
  .thumb_set EINT3_IRQHandler,Default_Handler

  .weak EINT4_IRQHandler
  .thumb_set EINT4_IRQHandler,Default_Handler

  .weak DMA1_Channel1_IRQHandler
  .thumb_set DMA1_Channel1_IRQHandler,Default_Handler

  .weak DMA1_Channel2_IRQHandler
  .thumb_set DMA1_Channel2_IRQHandler,Default_Handler

  .weak DMA1_Channel3_IRQHandler
  .thumb_set DMA1_Channel3_IRQHandler,Default_Handler

  .weak DMA1_Channel4_IRQHandler
  .thumb_set DMA1_Channel4_IRQHandler,Default_Handler

  .weak DMA1_Channel5_IRQHandler
  .thumb_set DMA1_Channel5_IRQHandler,Default_Handler

  .weak DMA1_Channel6_IRQHandler
  .thumb_set DMA1_Channel6_IRQHandler,Default_Handler

  .weak DMA1_Channel7_IRQHandler
  .thumb_set DMA1_Channel7_IRQHandler,Default_Handler

  .weak ADC1_2_IRQHandler
  .thumb_set ADC1_2_IRQHandler,Default_Handler

  .weak USBD_HP_CAN1_TX_IRQHandler
  .thumb_set USBD_HP_CAN1_TX_IRQHandler,Default_Handler

  .weak USBD_LP_CAN1_RX0_IRQHandler
  .thumb_set USBD_LP_CAN1_RX0_IRQHandler,Default_Handler

  .weak CAN1_TX_IRQHandler
  .thumb_set CAN1_TX_IRQHandler,Default_Handler

  .weak CAN1_RX0_IRQHandler
  .thumb_set CAN1_RX0_IRQHandler,Default_Handler

  .weak CAN1_RX1_IRQHandler
  .thumb_set CAN1_RX1_IRQHandler,Default_Handler

  .weak CAN1_SCE_IRQHandler
  .thumb_set CAN1_SCE_IRQHandler,Default_Handler

  .weak EINT9_5_IRQHandler
  .thumb_set EINT9_5_IRQHandler,Default_Handler

  .weak TMR1_BRK_IRQHandler
  .thumb_set TMR1_BRK_IRQHandler,Default_Handler

  .weak TMR1_UP_IRQHandler
  .thumb_set TMR1_UP_IRQHandler,Default_Handler

  .weak TMR1_TRG_COM_IRQHandler
  .thumb_set TMR1_TRG_COM_IRQHandler,Default_Handler

  .weak TMR1_CC_IRQHandler
  .thumb_set TMR1_CC_IRQHandler,Default_Handler

  .weak TMR2_IRQHandler
  .thumb_set TMR2_IRQHandler,Default_Handler

  .weak TMR3_IRQHandler
  .thumb_set TMR3_IRQHandler,Default_Handler

  .weak TMR4_IRQHandler
  .thumb_set TMR4_IRQHandler,Default_Handler

  .weak I2C1_EV_IRQHandler
  .thumb_set I2C1_EV_IRQHandler,Default_Handler

  .weak I2C1_ER_IRQHandler
  .thumb_set I2C1_ER_IRQHandler,Default_Handler

  .weak I2C2_EV_IRQHandler
  .thumb_set I2C2_EV_IRQHandler,Default_Handler

  .weak I2C2_ER_IRQHandler
  .thumb_set I2C2_ER_IRQHandler,Default_Handler

  .weak SPI1_IRQHandler
  .thumb_set SPI1_IRQHandler,Default_Handler

  .weak SPI2_IRQHandler
  .thumb_set SPI2_IRQHandler,Default_Handler

  .weak USART1_IRQHandler
  .thumb_set USART1_IRQHandler,Default_Handler

  .weak USART2_IRQHandler
  .thumb_set USART2_IRQHandler,Default_Handler

  .weak USART3_IRQHandler
  .thumb_set USART3_IRQHandler,Default_Handler

  .weak EINT15_10_IRQHandler
  .thumb_set EINT15_10_IRQHandler,Default_Handler

  .weak RTCAlarm_IRQHandler
  .thumb_set RTCAlarm_IRQHandler,Default_Handler

  .weak OTG_FS_WKUP_IRQHandler
  .thumb_set OTG_FS_WKUP_IRQHandler,Default_Handler

  .weak TMR5_IRQHandler
  .thumb_set TMR5_IRQHandler,Default_Handler

  .weak SPI3_IRQHandler
  .thumb_set SPI3_IRQHandler,Default_Handler

  .weak UART4_IRQHandler
  .thumb_set UART4_IRQHandler,Default_Handler

  .weak UART5_IRQHandler
  .thumb_set UART5_IRQHandler,Default_Handler

  .weak TMR6_IRQHandler
  .thumb_set TMR6_IRQHandler,Default_Handler

  .weak TMR7_IRQHandler
  .thumb_set TMR7_IRQHandler,Default_Handler

  .weak DMA2_Channel1_IRQHandler
  .thumb_set DMA2_Channel1_IRQHandler,Default_Handler

  .weak DMA2_Channel2_IRQHandler
  .thumb_set DMA2_Channel2_IRQHandler,Default_Handler

  .weak DMA2_Channel3_IRQHandler
  .thumb_set DMA2_Channel3_IRQHandler,Default_Handler

  .weak DMA2_Channel4_IRQHandler
  .thumb_set DMA2_Channel4_IRQHandler,Default_Handler

  .weak DMA2_Channel5_IRQHandler
  .thumb_set DMA2_Channel5_IRQHandler,Default_Handler

  .weak ETH_IRQHandler
  .thumb_set ETH_IRQHandler,Default_Handler

  .weak ETH_WKUP_IRQHandler
  .thumb_set ETH_WKUP_IRQHandler,Default_Handler

  .weak CAN2_TX_IRQHandler
  .thumb_set CAN2_TX_IRQHandler,Default_Handler

  .weak CAN2_RX0_IRQHandler
  .thumb_set CAN2_RX0_IRQHandler,Default_Handler

  .weak CAN2_RX1_IRQHandler
  .thumb_set CAN2_RX1_IRQHandler,Default_Handler

  .weak CAN2_SCE_IRQHandler
  .thumb_set CAN2_SCE_IRQHandler,Default_Handler

  .weak OTG_FS_IRQHandler
  .thumb_set OTG_FS_IRQHandler,Default_Handler
