;/*
; * Copyright (c) 2006-2024, RT-Thread Development Team
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Change Logs:
; * Date           Author       Notes
; * 2024-04-18     Astrozen     first implementation
; */

.syntax unified
.cpu cortex-m7
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
    .word     AVD_LVD_OVD_IRQHandler            // 17:AVD/LVD/OVD through EXTI Line detect
    .word     TAMPER_STAMP_IRQHandler           // 18:Tamper and TimeStamp through EXTI Line detect
    .word     RTC_WKUP_IRQHandler               // 19:RTC Wakeup through EXTI Line
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
    .word     ADC0_1_IRQHandler                 // 34:ADC0 and ADC1 interrupt
    .word     0                                 // 35:Reserved
    .word     0                                 // 36:Reserved
    .word     0                                 // 37:Reserved
    .word     0                                 // 38:Reserved
    .word     EXTI5_9_IRQHandler                // 39:EXTI5 to EXTI9
    .word     TIMER0_BRK_IRQHandler             // 40:TIMER0 Break
    .word     TIMER0_UP_IRQHandler              // 41:TIMER0 Update
    .word     TIMER0_TRG_CMT_IRQHandler         // 42:TIMER0 Trigger and Commutation
    .word     TIMER0_Channel_IRQHandler         // 43:TIMER0 Capture Compare
    .word     TIMER1_IRQHandler                 // 44:TIMER1
    .word     TIMER2_IRQHandler                 // 45:TIMER2
    .word     TIMER3_IRQHandler                 // 46:TIMER3
    .word     I2C0_EV_IRQHandler                // 47:I2C0 Event
    .word     I2C0_ER_IRQHandler                // 48:I2C0 Error
    .word     I2C1_EV_IRQHandler                // 49:I2C1 Event
    .word     I2C1_ER_IRQHandler                // 50:I2C1 Error
    .word     SPI0_IRQHandler                   // 51:SPI0
    .word     SPI1_IRQHandler                   // 52:SPI1
    .word     USART0_IRQHandler                 // 53:USART0 global and wakeup
    .word     USART1_IRQHandler                 // 54:USART1 global and wakeup
    .word     USART2_IRQHandler                 // 55:USART2 global and wakeup
    .word     EXTI10_15_IRQHandler              // 56:EXTI10 to EXTI15
    .word     RTC_Alarm_IRQHandler              // 57:RTC Alarm
    .word     0                                 // Reserved
    .word     TIMER7_BRK_IRQHandler             // 59:TIMER7 Break
    .word     TIMER7_UP_IRQHandler              // 60:TIMER7 Update
    .word     TIMER7_TRG_CMT_IRQHandler         // 61:TIMER7 Trigger and Commutation
    .word     TIMER7_Channel_IRQHandler         // 62:TIMER7 Channel Capture Compare
    .word     DMA0_Channel7_IRQHandler          // 63:DMA0 Channel 7
    .word     EXMC_IRQHandler                   // 64:EXMC
    .word     SDIO0_IRQHandler                  // 65:SDIO0
    .word     TIMER4_IRQHandler                 // 66:TIMER4
    .word     SPI2_IRQHandler                   // 67:SPI2
    .word     UART3_IRQHandler                  // 68:UART3
    .word     UART4_IRQHandler                  // 69:UART4
    .word     TIMER5_DAC_UDR_IRQHandler         // 70:TIMER5 global interrupt and DAC1/DAC0 underrun error
    .word     TIMER6_IRQHandler                 // 71:TIMER6
    .word     DMA1_Channel0_IRQHandler          // 72:DMA1 Channel0
    .word     DMA1_Channel1_IRQHandler          // 73:DMA1 Channel1
    .word     DMA1_Channel2_IRQHandler          // 74:DMA1 Channel2
    .word     DMA1_Channel3_IRQHandler          // 75:DMA1 Channel3
    .word     DMA1_Channel4_IRQHandler          // 76:DMA1 Channel4
    .word     ENET0_IRQHandler                  // 77:Ethernet0
    .word     ENET0_WKUP_IRQHandler             // 78:Ethernet0 Wakeup through EXTI Line
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     DMA1_Channel5_IRQHandler          // 84:DMA1 Channel5
    .word     DMA1_Channel6_IRQHandler          // 85:DMA1 Channel6
    .word     DMA1_Channel7_IRQHandler          // 86:DMA1 Channel7
    .word     USART5_IRQHandler                 // 87:USART5 global and wakeup
    .word     I2C2_EV_IRQHandler                // 88:I2C2 Event
    .word     I2C2_ER_IRQHandler                // 89:I2C2 Error
    .word     USBHS0_EP1_OUT_IRQHandler         // 90:USBHS0 Endpoint 1 Out 
    .word     USBHS0_EP1_IN_IRQHandler          // 91:USBHS0 Endpoint 1 in
    .word     USBHS0_WKUP_IRQHandler            // 92:USBHS0 Wakeup through EXTI Line
    .word     USBHS0_IRQHandler                 // 93:USBHS0
    .word     DCI_IRQHandler                    // 94:DCI
    .word     CAU_IRQHandler                    // 95:CAU
    .word     HAU_TRNG_IRQHandler               // 96:HAU and TRNG
    .word     FPU_IRQHandler                    // 97:FPU
    .word     UART6_IRQHandler                  // 98:UART6
    .word     UART7_IRQHandler                  // 99:UART7
    .word     SPI3_IRQHandler                   // 100:SPI3
    .word     SPI4_IRQHandler                   // 101:SPI4
    .word     SPI5_IRQHandler                   // 102:SPI5
    .word     SAI0_IRQHandler                   // 103:SAI0
    .word     TLI_IRQHandler                    // 104:TLI
    .word     TLI_ER_IRQHandler                 // 105:TLI Error
    .word     IPA_IRQHandler                    // 106:IPA
    .word     SAI1_IRQHandler                   // 107:SAI1
    .word     OSPI0_IRQHandler                  // 108:OSPI0
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     I2C3_EV_IRQHandler                // 111:I2C3 Event
    .word     I2C3_ER_IRQHandler                // 112:I2C3 Error
    .word     RSPDIF_IRQHandler                 // 113:RSPDIF
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     DMAMUX_OVR_IRQHandler             // 118:DMAMUX Overrun interrupt
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     HPDF_INT0_IRQHandler              // 126:HPDF global interrupt 0
    .word     HPDF_INT1_IRQHandler              // 127:HPDF global interrupt 1
    .word     HPDF_INT2_IRQHandler              // 128:HPDF global interrupt 2
    .word     HPDF_INT3_IRQHandler              // 129:HPDF global interrupt 3
    .word     SAI2_IRQHandler                   // 130:SAI2 global interrupt
    .word     0                                 // Reserved
    .word     TIMER14_IRQHandler                // 132:TIMER14
    .word     TIMER15_IRQHandler                // 133:TIMER15
    .word     TIMER16_IRQHandler                // 134:TIMER16
    .word     0                                 // Reserved
    .word     MDIO_IRQHandler                   // 136:MDIO
    .word     0                                 // Reserved
    .word     MDMA_IRQHandler                   // 138:MDMA
    .word     0                                 // Reserved
    .word     SDIO1_IRQHandler                  // 140:SDIO1
    .word     HWSEM_IRQHandler                  // 141:HWSEM
    .word     0                                 // Reserved
    .word     ADC2_IRQHandler                   // 143:ADC2   
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     CMP0_1_IRQHandler                 // 153:CMP0 and CMP1
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     CTC_IRQHandler                    // 160:Clock Recovery System
    .word     RAMECCMU_IRQHandler               // 161:RAMECCMU
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     OSPI1_IRQHandler                  // 166:OSPI1
    .word     RTDEC0_IRQHandler                 // 167:RTDEC0
    .word     RTDEC1_IRQHandler                 // 168:RTDEC1
    .word     FAC_IRQHandler                    // 169:FAC
    .word     TMU_IRQHandler                    // 170:TMU
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     0                                 // Reserved
    .word     TIMER22_IRQHandler                // 177:TIMER22
    .word     TIMER23_IRQHandler                // 178:TIMER23
    .word     TIMER30_IRQHandler                // 179:TIMER30
    .word     TIMER31_IRQHandler                // 180:TIMER31
    .word     TIMER40_IRQHandler                // 181:TIMER40
    .word     TIMER41_IRQHandler                // 182:TIMER41
    .word     TIMER42_IRQHandler                // 183:TIMER42
    .word     TIMER43_IRQHandler                // 184:TIMER43
    .word     TIMER44_IRQHandler                // 185:TIMER44
    .word     TIMER50_IRQHandler                // 186:TIMER50
    .word     TIMER51_IRQHandler                // 187:TIMER51
    .word     USBHS1_EP1_OUT_IRQHandler         // 188:USBHS1 endpoint 1 out
    .word     USBHS1_EP1_IN_IRQHandler          // 189:USBHS1 endpoint 1 in
    .word     USBHS1_WKUP_IRQHandler            // 190:USBHS1 wakeup
    .word     USBHS1_IRQHandler                 // 191:USBHS1
    .word     ENET1_IRQHandler                  // 192:Ethernet1
    .word     ENET1_WKUP_IRQHandler             // 193:Ethernet1 wakeup
    .word     0                                 // Reserved
    .word     CAN0_WKUP_IRQHandler              // 195:CAN0 wakeup
    .word     CAN0_Message_IRQHandler           // 196:CAN0 interrupt for message buffer
    .word     CAN0_Busoff_IRQHandler            // 197:CAN0 interrupt for Bus off / Bus off done
    .word     CAN0_Error_IRQHandler             // 198:CAN0 interrupt for Error
    .word     CAN0_FastError_IRQHandler         // 199:CAN0 interrupt for Error in fast transmission
    .word     CAN0_TEC_IRQHandler               // 200:CAN0 interrupt for Transmit warning
    .word     CAN0_REC_IRQHandler               // 201:CAN0 interrupt for Receive warning
    .word     CAN1_WKUP_IRQHandler              // 202:CAN1 wakeup
    .word     CAN1_Message_IRQHandler           // 203:CAN1 interrupt for message buffer
    .word     CAN1_Busoff_IRQHandler            // 204:CAN1 interrupt for Bus off / Bus off done
    .word     CAN1_Error_IRQHandler             // 205:CAN1 interrupt for Error
    .word     CAN1_FastError_IRQHandler         // 206:CAN1 interrupt for Error in fast transmission
    .word     CAN1_TEC_IRQHandler               // 207:CAN1 interrupt for Transmit warning
    .word     CAN1_REC_IRQHandler               // 208:CAN1 interrupt for Receive warning
    .word     CAN2_WKUP_IRQHandler              // 209:CAN2 wakeup
    .word     CAN2_Message_IRQHandler           // 210:CAN2 interrupt for message buffer
    .word     CAN2_Busoff_IRQHandler            // 211:CAN2 interrupt for Bus off / Bus off done
    .word     CAN2_Error_IRQHandler             // 212:CAN2 interrupt for Error
    .word     CAN2_FastError_IRQHandler         // 213:CAN2 interrupt for Error in fast transmission
    .word     CAN2_TEC_IRQHandler               // 214:CAN2 interrupt for Transmit warning
    .word     CAN2_REC_IRQHandler               // 215:CAN2 interrupt for Receive warning
    .word     EFUSE_IRQHandler                  // 216:EFUSE
    .word     I2C0_WKUP_IRQHandler              // 217:I2C0 wakeup
    .word     I2C1_WKUP_IRQHandler              // 218:I2C1 wakeup
    .word     I2C2_WKUP_IRQHandler              // 219:I2C2 wakeup
    .word     I2C3_WKUP_IRQHandler              // 220:I2C3 wakeup
    .word     LPDTS_IRQHandler                  // 221:LPDTS
    .word     LPDTS_WKUP_IRQHandler             // 222:LPDTS wakeup
    .word     TIMER0_DEC_IRQHandler             // 223:TIMER0 DEC
    .word     TIMER7_DEC_IRQHandler             // 224:TIMER7 DEC
    .word     TIMER1_DEC_IRQHandler             // 225:TIMER1 DEC
    .word     TIMER2_DEC_IRQHandler             // 226:TIMER2 DEC
    .word     TIMER3_DEC_IRQHandler             // 227:TIMER3 DEC
    .word     TIMER4_DEC_IRQHandler             // 228:TIMER4 DEC
    .word     TIMER22_DEC_IRQHandler            // 229:TIMER22 DEC
    .word     TIMER23_DEC_IRQHandler            // 230:TIMER23 DEC
    .word     TIMER30_DEC_IRQHandler            // 231:TIMER30 DEC
    .word     TIMER31_DEC_IRQHandler            // 232:TIMER31 DEC

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
    IRQ AVD_LVD_OVD_IRQHandler
    IRQ TAMPER_STAMP_IRQHandler
    IRQ RTC_WKUP_IRQHandler
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
    IRQ TIMER7_BRK_IRQHandler
    IRQ TIMER7_UP_IRQHandler
    IRQ TIMER7_TRG_CMT_IRQHandler
    IRQ TIMER7_Channel_IRQHandler
    IRQ DMA0_Channel7_IRQHandler
    IRQ EXMC_IRQHandler
    IRQ SDIO0_IRQHandler
    IRQ TIMER4_IRQHandler
    IRQ SPI2_IRQHandler
    IRQ UART3_IRQHandler
    IRQ UART4_IRQHandler
    IRQ TIMER5_DAC_UDR_IRQHandler
    IRQ TIMER6_IRQHandler
    IRQ DMA1_Channel0_IRQHandler
    IRQ DMA1_Channel1_IRQHandler
    IRQ DMA1_Channel2_IRQHandler
    IRQ DMA1_Channel3_IRQHandler
    IRQ DMA1_Channel4_IRQHandler
    IRQ ENET0_IRQHandler
    IRQ ENET0_WKUP_IRQHandler
    IRQ DMA1_Channel5_IRQHandler
    IRQ DMA1_Channel6_IRQHandler
    IRQ DMA1_Channel7_IRQHandler
    IRQ USART5_IRQHandler
    IRQ I2C2_EV_IRQHandler
    IRQ I2C2_ER_IRQHandler
    IRQ USBHS0_EP1_OUT_IRQHandler
    IRQ USBHS0_EP1_IN_IRQHandler
    IRQ USBHS0_WKUP_IRQHandler
    IRQ USBHS0_IRQHandler
    IRQ DCI_IRQHandler
    IRQ CAU_IRQHandler
    IRQ HAU_TRNG_IRQHandler
    IRQ FPU_IRQHandler
    IRQ UART6_IRQHandler
    IRQ UART7_IRQHandler
    IRQ SPI3_IRQHandler
    IRQ SPI4_IRQHandler
    IRQ SPI5_IRQHandler
    IRQ SAI0_IRQHandler
    IRQ TLI_IRQHandler
    IRQ TLI_ER_IRQHandler
    IRQ IPA_IRQHandler
    IRQ SAI1_IRQHandler
    IRQ OSPI0_IRQHandler
    IRQ I2C3_EV_IRQHandler
    IRQ I2C3_ER_IRQHandler
    IRQ RSPDIF_IRQHandler
    IRQ DMAMUX_OVR_IRQHandler
    IRQ HPDF_INT0_IRQHandler
    IRQ HPDF_INT1_IRQHandler
    IRQ HPDF_INT2_IRQHandler
    IRQ HPDF_INT3_IRQHandler
    IRQ SAI2_IRQHandler
    IRQ TIMER14_IRQHandler
    IRQ TIMER15_IRQHandler
    IRQ TIMER16_IRQHandler
    IRQ MDIO_IRQHandler
    IRQ MDMA_IRQHandler
    IRQ SDIO1_IRQHandler
    IRQ HWSEM_IRQHandler
    IRQ ADC2_IRQHandler
    IRQ CMP0_1_IRQHandler
    IRQ CTC_IRQHandler
    IRQ RAMECCMU_IRQHandler
    IRQ OSPI1_IRQHandler
    IRQ RTDEC0_IRQHandler
    IRQ RTDEC1_IRQHandler
    IRQ FAC_IRQHandler
    IRQ TMU_IRQHandler
    IRQ TIMER22_IRQHandler
    IRQ TIMER23_IRQHandler
    IRQ TIMER30_IRQHandler
    IRQ TIMER31_IRQHandler
    IRQ TIMER40_IRQHandler
    IRQ TIMER41_IRQHandler
    IRQ TIMER42_IRQHandler
    IRQ TIMER43_IRQHandler
    IRQ TIMER44_IRQHandler
    IRQ TIMER50_IRQHandler
    IRQ TIMER51_IRQHandler
    IRQ USBHS1_EP1_OUT_IRQHandler
    IRQ USBHS1_EP1_IN_IRQHandler
    IRQ USBHS1_WKUP_IRQHandler
    IRQ USBHS1_IRQHandler
    IRQ ENET1_IRQHandler
    IRQ ENET1_WKUP_IRQHandler
    IRQ CAN0_WKUP_IRQHandler
    IRQ CAN0_Message_IRQHandler
    IRQ CAN0_Busoff_IRQHandler
    IRQ CAN0_Error_IRQHandler
    IRQ CAN0_FastError_IRQHandler
    IRQ CAN0_TEC_IRQHandler
    IRQ CAN0_REC_IRQHandler
    IRQ CAN1_WKUP_IRQHandler
    IRQ CAN1_Message_IRQHandler
    IRQ CAN1_Busoff_IRQHandler
    IRQ CAN1_Error_IRQHandler
    IRQ CAN1_FastError_IRQHandler
    IRQ CAN1_TEC_IRQHandler
    IRQ CAN1_REC_IRQHandler
    IRQ CAN2_WKUP_IRQHandler
    IRQ CAN2_Message_IRQHandler
    IRQ CAN2_Busoff_IRQHandler
    IRQ CAN2_Error_IRQHandler
    IRQ CAN2_FastError_IRQHandler
    IRQ CAN2_TEC_IRQHandler
    IRQ CAN2_REC_IRQHandler
    IRQ EFUSE_IRQHandler
    IRQ I2C0_WKUP_IRQHandler
    IRQ I2C1_WKUP_IRQHandler
    IRQ I2C2_WKUP_IRQHandler
    IRQ I2C3_WKUP_IRQHandler
    IRQ LPDTS_IRQHandler
    IRQ LPDTS_WKUP_IRQHandler
    IRQ TIMER0_DEC_IRQHandler
    IRQ TIMER7_DEC_IRQHandler
    IRQ TIMER1_DEC_IRQHandler
    IRQ TIMER2_DEC_IRQHandler
    IRQ TIMER3_DEC_IRQHandler
    IRQ TIMER4_DEC_IRQHandler
    IRQ TIMER22_DEC_IRQHandler
    IRQ TIMER23_DEC_IRQHandler
    IRQ TIMER30_DEC_IRQHandler
    IRQ TIMER31_DEC_IRQHandler
