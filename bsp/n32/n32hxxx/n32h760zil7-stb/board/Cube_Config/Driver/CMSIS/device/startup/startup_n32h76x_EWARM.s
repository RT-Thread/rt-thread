; *********************************************************************************************************
;     Copyright (c) 2024, Nations Technologies Inc.
; 
;     All rights reserved.
;
;     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
; referred to as NATIONS). This software, and the product of NATIONS described herein 
; (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
; of the People's Republic of China and other applicable jurisdictions worldwide.
;
;     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
; intellectual property rights. Names and brands of third party may be mentioned or referred 
; thereto (if any) for identification purposes only.
;
;     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
; improvements to this software at any time without notice. Please contact NATIONS and obtain 
; the latest version of this software before placing orders.

;     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
; no responsibility for the accuracy and reliability of this software.
; 
;     It is the responsibility of the user of this software to properly design, program, and test 
; the functionality and safety of any application made of this information and any resulting product. 
; In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
; consequential damages arising in any way out of the use of this software or the Product.
;
;     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
; malfunction or failure of which may cause loss of human life, bodily injury or severe property 
; damage. Such applications are deemed, "Insecure Usage".
;
;     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
; harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
; to any customer's Insecure Usage.

;     Any express or implied warranty with regard to this software or the Product, including,but not 
; limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
; are disclaimed to the fullest extent permitted by law.

;     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
; or otherwise distribute this software for any purposes, in whole or in part.
;
;     NATIONS products and technologies shall not be used for or incorporated into any products or systems
; whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
; User shall comply with any applicable export control laws and regulations promulgated and administered by 
; the governments of any countries asserting jurisdiction over the parties or transactions.
; ************************************************************************************************************

; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

    MODULE  ?cstartup
        
        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit        
        PUBLIC  __vector_table

        DATA
        
         __iar_init$$done:               ; The vector table is not needed
                                         ; until after copy initialization is done
       
__vector_table
        DCD     sfe(CSTACK)
		DCD     Reset_Handler                     ; Reset Handler
		DCD     NMI_Handler                       ; NMI Handler
		DCD     HardFault_Handler                 ; Hard Fault Handler
		DCD     MemManage_Handler                 ; MPU Fault Handler
		DCD     BusFault_Handler                  ; Bus Fault Handler
		DCD     UsageFault_Handler                ; Usage Fault Handler
		DCD     0                                 ; Reserved
		DCD     0                                 ; Reserved
		DCD     0                                 ; Reserved
		DCD     0                                 ; Reserved
		DCD     SVC_Handler                       ; SVCall Handler
		DCD     DebugMon_Handler                  ; Debug Monitor Handler
		DCD     0                                 ; Reserved
		DCD     PendSV_Handler                    ; PendSV Handler
		DCD     N32SysTick_Handler                ; N32SysTick Handler



        ; External Interrupts
		DCD     WWDG1_IRQHandler           ; Window1 Watchdog interrupt
		DCD     PVD_IRQHandler             ; PVD through EXTI Line16 detection interrupt
		DCD     RTC_TAMPER_IRQHandler      ; RTC Tamper_Timestamp_Overflow or LSE-CSS through EXTI Line18 interrupt
		DCD     RTC_WKUP_IRQHandler        ; RTC Wakeup timer through EXTI line 19 interrupt
		DCD     RCC_IRQHandler             ; RCC interrupt
		DCD     EXTI0_IRQHandler           ; EXTI Line 0 interrupt
		DCD     EXTI1_IRQHandler           ; EXTI Line 1 interrupt
		DCD     EXTI2_IRQHandler           ; EXTI Line 2 interrupt
		DCD     EXTI3_IRQHandler           ; EXTI Line 3 interrupt
		DCD     EXTI4_IRQHandler           ; EXTI Line 4 interrupt
		DCD     EXTI9_5_IRQHandler         ; EXTI Line[9:5] interrupt
		DCD     EXTI15_10_IRQHandler       ; EXTI Line[15:10] interrupt
		DCD     DMA1_Channel0_IRQHandler   ; DMA1 Channel 0
		DCD     DMA1_Channel1_IRQHandler   ; DMA1 Channel 1
		DCD     DMA1_Channel2_IRQHandler   ; DMA1 Channel 2
		DCD     DMA1_Channel3_IRQHandler   ; DMA1 Channel 3
		DCD     DMA1_Channel4_IRQHandler   ; DMA1 Channel 4
		DCD     DMA1_Channel5_IRQHandler   ; DMA1 Channel 5
		DCD     DMA1_Channel6_IRQHandler   ; DMA1 Channel 6
		DCD     DMA1_Channel7_IRQHandler   ; DMA1 Channel 7
		DCD     DMA2_Channel0_IRQHandler   ; DMA2 Channel 0
		DCD     DMA2_Channel1_IRQHandler   ; DMA2 Channel 1
		DCD     DMA2_Channel2_IRQHandler   ; DMA2 Channel 2
		DCD     DMA2_Channel3_IRQHandler   ; DMA2 Channel 3
		DCD     DMA2_Channel4_IRQHandler   ; DMA2 Channel 4
		DCD     DMA2_Channel5_IRQHandler   ; DMA2 Channel 5
		DCD     DMA2_Channel6_IRQHandler   ; DMA2 Channel 6
		DCD     DMA2_Channel7_IRQHandler   ; DMA2 Channel 7
		DCD     DMA3_Channel0_IRQHandler   ; DMA3 Channel 0
		DCD     DMA3_Channel1_IRQHandler   ; DMA3 Channel 1
		DCD     DMA3_Channel2_IRQHandler   ; DMA3 Channel 2
		DCD     DMA3_Channel3_IRQHandler   ; DMA3 Channel 3
		DCD     DMA3_Channel4_IRQHandler   ; DMA3 Channel 4
		DCD     DMA3_Channel5_IRQHandler   ; DMA3 Channel 5
		DCD     DMA3_Channel6_IRQHandler   ; DMA3 Channel 6
		DCD     DMA3_Channel7_IRQHandler   ; DMA3 Channel 7
		DCD     MDMA_Channel0_IRQHandler   ; MDMA Channel 0
		DCD     MDMA_Channel1_IRQHandler   ; MDMA Channel 1
		DCD     MDMA_Channel2_IRQHandler   ; MDMA Channel 2
		DCD     MDMA_Channel3_IRQHandler   ; MDMA Channel 3
		DCD     MDMA_Channel4_IRQHandler   ; MDMA Channel 4
		DCD     MDMA_Channel5_IRQHandler   ; MDMA Channel 5
		DCD     MDMA_Channel6_IRQHandler   ; MDMA Channel 6
		DCD     MDMA_Channel7_IRQHandler   ; MDMA Channel 7
		DCD     MDMA_Channel8_IRQHandler   ; MDMA Channel 8
		DCD     MDMA_Channel9_IRQHandler   ; MDMA Channel 9
		DCD     MDMA_Channel10_IRQHandler  ; MDMA Channel 10
		DCD     MDMA_Channel11_IRQHandler  ; MDMA Channel 11
		DCD     MDMA_Channel12_IRQHandler  ; MDMA Channel 12
		DCD     MDMA_Channel13_IRQHandler  ; MDMA Channel 13
		DCD     MDMA_Channel14_IRQHandler  ; MDMA Channel 14
		DCD     MDMA_Channel15_IRQHandler  ; MDMA Channel 15
		DCD     SDPU_IRQHandler            ; SDPU global interrupt
		DCD     0                          ; Reserved
		DCD     0                          ; Reserved
		DCD     FPU_CPU1_IRQHandler		   ; FPU_CM7 global interrupt		
		DCD     ECCMON_IRQHandler          ; ECCMON global interrupt
		DCD     RTC_ALARM_IRQHandler       ; RTC Alarm via EXTI17 interrupt
		DCD     I2C1_EV_IRQHandler         ; I2C1 event interrupt
		DCD     I2C1_ER_IRQHandler         ; I2C1 error interrupt
		DCD     I2C2_EV_IRQHandler         ; I2C2 event interrupt
		DCD     I2C2_ER_IRQHandler         ; I2C2 error interrupt
		DCD     I2C3_EV_IRQHandler         ; I2C3 event interrupt
		DCD     I2C3_ER_IRQHandler         ; I2C3 error interrupt
		DCD     I2C4_EV_IRQHandler         ; I2C4 event interrupt
		DCD     I2C4_ER_IRQHandler         ; I2C4 error interrupt
		DCD     I2C5_EV_IRQHandler         ; I2C5 event interrupt
		DCD     I2C5_ER_IRQHandler         ; I2C5 error interrupt
		DCD     I2C6_EV_IRQHandler         ; I2C6 event interrupt
		DCD     I2C6_ER_IRQHandler         ; I2C6 error interrupt
		DCD     I2C7_EV_IRQHandler         ; I2C7 event interrupt
		DCD     I2C7_ER_IRQHandler         ; I2C7 error interrupt
		DCD     I2C8_EV_IRQHandler         ; I2C8 event interrupt
		DCD     I2C8_ER_IRQHandler         ; I2C8 error interrupt
		DCD     I2C9_EV_IRQHandler        ; I2C9 event interrupt
		DCD     I2C9_ER_IRQHandler        ; I2C9 error interrupt
		DCD     I2C10_EV_IRQHandler       ; I2C10 event interrupt
		DCD     I2C10_ER_IRQHandler       ; I2C10 error interrupt
		DCD     I2S1_IRQHandler           ; I2S1 global interrupt
		DCD     I2S2_IRQHandler           ; I2S1 global interrupt
		DCD     I2S3_IRQHandler           ; I2S1 global interrupt
		DCD     I2S4_IRQHandler           ; I2S1 global interrupt
		DCD     0                         ; Reserved
		DCD     xSPI2_IRQHandler          ; xSPI2 global interrupt
		DCD     SPI1_IRQHandler           ; SPI1 global interrupt
		DCD     SPI2_IRQHandler           ; SPI2 global interrupt
		DCD     SPI3_IRQHandler           ; SPI3 global interrupt
		DCD     SPI4_IRQHandler           ; SPI4 global interrupt
		DCD     SPI5_IRQHandler           ; SPI5 global interrupt
		DCD     SPI6_IRQHandler           ; SPI6 global interrupt
		DCD     SPI7_IRQHandler           ; SPI7 global interrupt
		DCD     LCD_EV_IRQHandler         ; TFT LCD Controller event interrupt
		DCD     LCD_ER_IRQHandler         ; TFT LCD Controller error interrupt
		DCD     DVP1_IRQHandler           ; DVP1 global interrupt
		DCD     DVP2_IRQHandler           ; DVP2 global interrupt
		DCD     DMAMUX2_IRQHandler        ; DMAMUX2 (MDMA MUX) global interrupt
		DCD     USB1_HS_EPx_OUT_IRQHandler  ; USB1_HS endpoint out global interrupt
		DCD     USB1_HS_EPx_IN_IRQHandler   ; USB1_HS endpoint in global interrupt
		DCD     USB1_HS_WKUP_IRQHandler     ; USB1_HS WKUP interrupt through EXTI line 62
		DCD     USB1_HS_IRQHandler          ; USB1_HS global interrupt
		DCD     USB2_HS_EPx_OUT_IRQHandler  ; USB2_HS  endpoint out global interrupt
		DCD     USB2_HS_EPx_IN_IRQHandler   ; USB2_HS  endpoint in global interrupt
		DCD     USB2_HS_WKUP_IRQHandler     ; USB2_HS WKUP interrupt through EXTI line 63
		DCD     USB2_HS_IRQHandler          ; USB2_HS global interrupt
		DCD     ETH1_IRQHandler             ; Ethernet 1 global interrupt
		DCD     ETH1_PMT_LPI_IRQHandler     ; Ethernet 1 PMT wakeup interrupt and LPI interrupt through EXTI line 83
                DCD     ETH2_IRQHandler            ; Ethernet 2 global interrupt
                DCD     ETH2_PMT_LPI_IRQHandler    ; Ethernet 2  PMT wakeup interrupt and LPI interrupt through EXTI line 84
                DCD     FDCAN1_INT0_IRQHandler     ; FDCAN1 global interrupt line 0
                DCD     FDCAN2_INT0_IRQHandler     ; FDCAN2 global interrupt line 0
                DCD     FDCAN3_INT0_IRQHandler     ; FDCAN3 global interrupt line 0
                DCD     FDCAN4_INT0_IRQHandler     ; FDCAN4 global interrupt line 0
                DCD     FDCAN1_INT1_IRQHandler     ; FDCAN1 global interrupt line 1
                DCD     FDCAN2_INT1_IRQHandler     ; FDCAN2 global interrupt line 1
                DCD     FDCAN3_INT1_IRQHandler     ; FDCAN3 global interrupt line 1
                DCD     FDCAN4_INT1_IRQHandler     ; FDCAN4 global interrupt line 1
		DCD     USART1_IRQHandler           ; USART1 global interrupt
		DCD     USART2_IRQHandler           ; USART2 global interrupt
		DCD     USART3_IRQHandler           ; USART3 global interrupt
		DCD     USART4_IRQHandler           ; USART4 global interrupt
		DCD     USART5_IRQHandler           ; USART5 global interrupt
		DCD     USART6_IRQHandler           ; USART6 global interrupt
		DCD     USART7_IRQHandler           ; USART7 global interrupt
		DCD     USART8_IRQHandler           ; USART8 global interrupt
		DCD     UART9_IRQHandler            ; UART9 global interrupt
		DCD     UART10_IRQHandler           ; UART10 global interrupt
		DCD     UART11_IRQHandler           ; UART11 global interrupt
		DCD     UART12_IRQHandler           ; UART12 global interrupt
		DCD     UART13_IRQHandler           ; UART13 global interrupt
		DCD     UART14_IRQHandler           ; UART14 global interrupt
		DCD     UART15_IRQHandler           ; UART15 global interrupt
		DCD     LPUART1_IRQHandler          ; LPUART1 global interrupt + wakeup through EXTI line 49
		DCD     LPUART2_IRQHandler          ; LPUART2 global interrupt + wakeup through EXTI line 52
		DCD     GPU_IRQHandler              ; GPU global interrupt
		DCD     0                           ; Reserved
		DCD     SDMMC1_IRQHandler           ; SDMMC1_IRQ + WKUP through EXTI line 24
		DCD     SDMMC2_IRQHandler           ; SDMMC2_IRQ + WKUP  through EXTI line 25
		DCD     ADC1_IRQHandler             ; ADC1 global interrupt
		DCD     ADC2_IRQHandler             ; ADC2 global interrupt
		DCD     ADC3_IRQHandler             ; ADC3 global interrupt
		DCD     COMP1_2_IRQHandler          ; COMP1 and COMP2 through EXTI line 20 and 21
		DCD     COMP3_4_IRQHandler          ; COMP3 and COMP4  through EXTI line 22 and 23
		DCD     SHRTIM1_INT1_IRQHandler     ; High Resolution timer 1 interrupt 1
                DCD     SHRTIM1_INT2_IRQHandler     ; High Resolution timer 1 interrupt 2 
                DCD     SHRTIM1_INT3_IRQHandler     ; High Resolution timer 1 interrupt 3 
                DCD     SHRTIM1_INT4_IRQHandler     ; High Resolution timer 1 interrupt 4 
                DCD     SHRTIM1_INT5_IRQHandler     ; High Resolution timer 1 interrupt 5 
                DCD     SHRTIM1_INT6_IRQHandler     ; High Resolution timer 1 interrupt 6 
                DCD     SHRTIM1_INT7_IRQHandler     ; High Resolution timer 1 interrupt 7 
                DCD     SHRTIM1_INT8_IRQHandler     ; High Resolution timer 1 interrupt 8 
                DCD     SHRTIM2_INT1_IRQHandler     ; High Resolution timer 2 interrupt 1
                DCD     SHRTIM2_INT2_IRQHandler     ; High Resolution timer 2 interrupt 2 
                DCD     SHRTIM2_INT3_IRQHandler     ; High Resolution timer 2 interrupt 3 
                DCD     SHRTIM2_INT4_IRQHandler     ; High Resolution timer 2 interrupt 4 
                DCD     SHRTIM2_INT5_IRQHandler     ; High Resolution timer 2 interrupt 5 
                DCD     SHRTIM2_INT6_IRQHandler     ; High Resolution timer 2 interrupt 6 
                DCD     SHRTIM2_INT7_IRQHandler     ; High Resolution timer 2 interrupt 7 
                DCD     SHRTIM2_INT8_IRQHandler     ; High Resolution timer 2 interrupt 8  
		DCD     FDCAN5_INT0_IRQHandler      ; FDCAN5 global interrupt line 0
		DCD     FDCAN6_INT0_IRQHandler      ; FDCAN6 global interrupt line 0
		DCD     FDCAN7_INT0_IRQHandler      ; FDCAN7 global interrupt line 0
                DCD     FDCAN8_INT0_IRQHandler      ; FDCAN8 global interrupt line 0
		DCD     FDCAN5_INT1_IRQHandler      ; FDCAN5 global interrupt line 1
		DCD     FDCAN6_INT1_IRQHandler      ; FDCAN6 global interrupt line 1
                DCD     FDCAN7_INT1_IRQHandler      ; FDCAN7 global interrupt line 1
                DCD     FDCAN8_INT1_IRQHandler      ; FDCAN8 global interrupt line 1
		DCD     0                           ; Reserved
		DCD     0                           ; Reserved
		DCD     LPTIM5_WKUP_IRQHandler      ; LPTIM5 wakeup  through EXTI 86
		DCD     JPEG_SGDMA_H2P_IRQHandler   ; JPEG SGDMA Host to Peripheral Interrupt
		DCD     JPEG_SGDMA_P2H_IRQHandler   ; JPEG SGDMA Peripheral to Host Interrupt
		DCD     WAKEUP_IO_IRQHandler        ; 6 WAKEUP IOs through EXTI line 70-75
		DCD     SEMA4_INT1_IRQHandler       ; SEMA4 interrupt1
		DCD     0                           ; Reserved
		DCD     WWDG2_RST_IRQHandler        ; WWDG2 reset interrupt through EXTI line 82
		DCD     OTPC_IRQHandler             ; OTPC interrupt
		DCD     FEMC_IRQHandler             ; FEMC interrupt
		DCD     DCMUB_IRQHandler            ; DCMUB interrupt
		DCD     DAC1_IRQHandler             ; DAC1 interrupt
		DCD     DAC2_IRQHandler             ; DAC2 interrupt
		DCD     MDMA_AHBS_ER_IRQHandler     ; MDMA HABS ERROR through EXTI line55-56
		DCD     CM7_CATCH_READ_ER_IRQHandler   ; CM7 Error on Cache Read  through EXTI line 64-65
		DCD     DAC3_IRQHandler             ; DAC3 interrupt
		DCD     DAC4_IRQHandler             ; DAC4 interrupt
		DCD     EMC_IRQHandler              ; EMC event interrupt through EXTI line 88-89
		DCD     DAC5_IRQHandler             ; DAC5 interrupt
        DCD     DAC6_IRQHandler             ; DAC6 interrupt
		DCD     ESC_OPB_IRQHandler          ; ETHERCAT OPB Interrupt
		DCD     ESC_SYNC0_IRQHandler        ; ETHERCAT SYNC0 Interrupt
		DCD     ESC_SYNC1_RQHandler         ; ETHERCAT SYNC1 Interrupt
		DCD     ESC_WRP_IRQHandler          ; ETHERCAT WRAPPER Interrupt
		DCD     0                           ; Reserved  			  
		DCD     ATIM1_BRK_IRQHandler        ; Advanced timer 1 break interrupt
		DCD     ATIM1_TRG_COM_IRQHandler    ; Advanced timer 1 trigger and commutation interrupts
		DCD     ATIM1_CC_IRQHandler         ; Advanced timer 1 capture/compare interrupt
		DCD     ATIM1_UP_IRQHandler         ; Advanced timer 1 update interrupt
		DCD     ATIM2_BRK_IRQHandler        ; Advanced timer 2 break interrupt
		DCD     ATIM2_TRG_COM_IRQHandler    ; advanced timer 2 trigger and commutation interrupts
		DCD     ATIM2_CC_IRQHandler         ; Advanced timer 2 capture/compare interrupt
		DCD     ATIM2_UP_IRQHandler         ; Advanced timer 2 update interrupt
		DCD     ATIM3_BRK_IRQHandler       ; Advanced timer 3 break interrupt
                DCD     ATIM3_TRG_COM_IRQHandler   ; Advanced timer 3 trigger and commutation interrupts
                DCD     ATIM3_CC_IRQHandler        ; Advanced timer 3 capture/compare interrupt
                DCD     ATIM3_UP_IRQHandler        ; Advanced timer 3 update interrupt
                DCD     ATIM4_BRK_IRQHandler       ; Advanced timer 4 break interrupt
                DCD     ATIM4_TRG_COM_IRQHandler   ; Advanced timer 4 trigger and commutation interrupts
                DCD     ATIM4_CC_IRQHandler        ; Advanced timer 4 capture/compare interrupt
                DCD     ATIM4_UP_IRQHandler        ; Advanced timer 4 update interrupt
		DCD     GTIMA1_IRQHandler          ; General timer A1 global interrupt
		DCD     GTIMA2_IRQHandler          ; General timer A2 global interrupt
		DCD     GTIMA3_IRQHandler          ; General timer A3 global interrupt
		DCD     GTIMA4_IRQHandler          ; General timer A4 global interrupt
		DCD     GTIMA5_IRQHandler          ; General timer A5 global interrupt
		DCD     GTIMA6_IRQHandler          ; General timer A6 global interrupt
		DCD     GTIMA7_IRQHandler          ; General timer A7 global interrupt
		DCD     GTIMB1_IRQHandler          ; General timer B1 global interrupt
		DCD     GTIMB2_IRQHandler          ; General timer B2 global interrupt
		DCD     GTIMB3_IRQHandler          ; General timer B3 global interrupt
		DCD     BTIM1_IRQHandler           ; Base timer 1 global interrupt
		DCD     BTIM2_IRQHandler           ; Base timer 2 global interrupt
		DCD     BTIM3_IRQHandler           ; Base timer 3 global interrupt
		DCD     BTIM4_IRQHandler           ; Base timer 4 global interrupt
		DCD     LPTIM1_WKUP_IRQHandler     ; LPTIM1 wakeup interrupt
		DCD     LPTIM2_WKUP_IRQHandler     ; LPTIM2 wakeup interrupt
		DCD     LPTIM3_WKUP_IRQHandler     ; LPTIM3 wakeup interrupt
		DCD     LPTIM4_WKUP_IRQHandler     ; LPTIM4 wakeup interrupt
		DCD     DSMU_FLT0_IRQHandler       ; DSMU Filter interrupt 0
		DCD     DSMU_FLT1_IRQHandler       ; DSMU Filter interrupt 1
		DCD     DSMU_FLT2_IRQHandler       ; DSMU Filter interrupt 2
		DCD     DSMU_FLT3_IRQHandler       ; DSMU Filter interrupt 3
		DCD     FMAC_IRQHandler            ; FMAC global interrupt
		DCD     CORDIC_IRQHandler          ; Cordic global interrupt
		DCD     DMAMUX1_IRQHandler         ; DMAMUX1 interrupt
		DCD     MMU_IRQHandler             ; MMU interrupt
        DCD     SysTick_Handler            ; SysTick Handler
        ;need check to user manual of exti chapter 


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
        B UsageFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
        B DebugMon_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK N32SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
N32SysTick_Handler
        B N32SysTick_Handler

        PUBWEAK WWDG1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
WWDG1_IRQHandler
        B WWDG1_IRQHandler

        PUBWEAK PVD_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PVD_IRQHandler
        B PVD_IRQHandler

        PUBWEAK RTC_TAMPER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC_TAMPER_IRQHandler
        B RTC_TAMPER_IRQHandler

        PUBWEAK RTC_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC_WKUP_IRQHandler
        B RTC_WKUP_IRQHandler

        PUBWEAK RCC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RCC_IRQHandler
        B RCC_IRQHandler

        PUBWEAK EXTI0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI0_IRQHandler
        B EXTI0_IRQHandler

        PUBWEAK EXTI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI1_IRQHandler
        B EXTI1_IRQHandler

        PUBWEAK EXTI2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI2_IRQHandler
        B EXTI2_IRQHandler

        PUBWEAK EXTI3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI3_IRQHandler
        B EXTI3_IRQHandler

        PUBWEAK EXTI4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI4_IRQHandler
        B EXTI4_IRQHandler
		
        PUBWEAK EXTI9_5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI9_5_IRQHandler
        B EXTI9_5_IRQHandler

        PUBWEAK EXTI15_10_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EXTI15_10_IRQHandler
        B EXTI15_10_IRQHandler

        PUBWEAK DMA1_Channel0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel0_IRQHandler
        B DMA1_Channel0_IRQHandler

        PUBWEAK DMA1_Channel1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel1_IRQHandler
        B DMA1_Channel1_IRQHandler

        PUBWEAK DMA1_Channel2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel2_IRQHandler
        B DMA1_Channel2_IRQHandler

        PUBWEAK DMA1_Channel3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel3_IRQHandler
        B DMA1_Channel3_IRQHandler

        PUBWEAK DMA1_Channel4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel4_IRQHandler
        B DMA1_Channel4_IRQHandler

        PUBWEAK DMA1_Channel5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel5_IRQHandler
        B DMA1_Channel5_IRQHandler

        PUBWEAK DMA1_Channel6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel6_IRQHandler
        B DMA1_Channel6_IRQHandler

        PUBWEAK DMA1_Channel7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_Channel7_IRQHandler
        B DMA1_Channel7_IRQHandler
		
        PUBWEAK DMA2_Channel0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel0_IRQHandler
        B DMA2_Channel0_IRQHandler

        PUBWEAK DMA2_Channel1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel1_IRQHandler
        B DMA2_Channel1_IRQHandler

        PUBWEAK DMA2_Channel2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel2_IRQHandler
        B DMA2_Channel2_IRQHandler

        PUBWEAK DMA2_Channel3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel3_IRQHandler
        B DMA2_Channel3_IRQHandler

        PUBWEAK DMA2_Channel4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel4_IRQHandler
        B DMA2_Channel4_IRQHandler

        PUBWEAK DMA2_Channel5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel5_IRQHandler
        B DMA2_Channel5_IRQHandler

        PUBWEAK DMA2_Channel6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel6_IRQHandler
        B DMA2_Channel6_IRQHandler

        PUBWEAK DMA2_Channel7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_Channel7_IRQHandler
        B DMA2_Channel7_IRQHandler
		
        PUBWEAK DMA3_Channel0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA3_Channel0_IRQHandler
        B DMA3_Channel0_IRQHandler

        PUBWEAK DMA3_Channel1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA3_Channel1_IRQHandler
        B DMA3_Channel1_IRQHandler

        PUBWEAK DMA3_Channel2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA3_Channel2_IRQHandler
        B DMA3_Channel2_IRQHandler

        PUBWEAK DMA3_Channel3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA3_Channel3_IRQHandler
        B DMA3_Channel3_IRQHandler

        PUBWEAK DMA3_Channel4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA3_Channel4_IRQHandler
        B DMA3_Channel4_IRQHandler

        PUBWEAK DMA3_Channel5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA3_Channel5_IRQHandler
        B DMA3_Channel5_IRQHandler

        PUBWEAK DMA3_Channel6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA3_Channel6_IRQHandler
        B DMA3_Channel6_IRQHandler

        PUBWEAK DMA3_Channel7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA3_Channel7_IRQHandler
        B DMA3_Channel7_IRQHandler

        PUBWEAK MDMA_Channel0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MDMA_Channel0_IRQHandler
        B MDMA_Channel0_IRQHandler
		
        PUBWEAK MDMA_Channel1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MDMA_Channel1_IRQHandler
        B MDMA_Channel1_IRQHandler
		
        PUBWEAK MDMA_Channel2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MDMA_Channel2_IRQHandler
        B MDMA_Channel2_IRQHandler
		
        PUBWEAK MDMA_Channel3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MDMA_Channel3_IRQHandler
        B MDMA_Channel3_IRQHandler
		
        PUBWEAK MDMA_Channel4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MDMA_Channel4_IRQHandler
        B MDMA_Channel4_IRQHandler

        PUBWEAK MDMA_Channel5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MDMA_Channel5_IRQHandler
        B MDMA_Channel5_IRQHandler

        PUBWEAK MDMA_Channel6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MDMA_Channel6_IRQHandler
        B MDMA_Channel6_IRQHandler

        PUBWEAK MDMA_Channel7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MDMA_Channel7_IRQHandler
        B MDMA_Channel7_IRQHandler
		
        PUBWEAK MDMA_Channel8_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MDMA_Channel8_IRQHandler
        B MDMA_Channel8_IRQHandler
		
        PUBWEAK MDMA_Channel9_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MDMA_Channel9_IRQHandler
        B MDMA_Channel9_IRQHandler

        PUBWEAK MDMA_Channel10_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MDMA_Channel10_IRQHandler
        B MDMA_Channel10_IRQHandler

        PUBWEAK MDMA_Channel11_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MDMA_Channel11_IRQHandler
        B MDMA_Channel11_IRQHandler
		
        PUBWEAK MDMA_Channel12_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MDMA_Channel12_IRQHandler
        B MDMA_Channel12_IRQHandler

        PUBWEAK MDMA_Channel13_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MDMA_Channel13_IRQHandler
        B MDMA_Channel13_IRQHandler
		
        PUBWEAK MDMA_Channel14_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MDMA_Channel14_IRQHandler
        B MDMA_Channel14_IRQHandler

        PUBWEAK MDMA_Channel15_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MDMA_Channel15_IRQHandler
        B MDMA_Channel15_IRQHandler

        PUBWEAK SDPU_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SDPU_IRQHandler
        B SDPU_IRQHandler

        PUBWEAK FPU_CPU1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FPU_CPU1_IRQHandler
        B FPU_CPU1_IRQHandler

        PUBWEAK ECCMON_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ECCMON_IRQHandler
        B ECCMON_IRQHandler

        PUBWEAK RTC_ALARM_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC_ALARM_IRQHandler
        B RTC_ALARM_IRQHandler

        PUBWEAK I2C1_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C1_EV_IRQHandler
        B I2C1_EV_IRQHandler

        PUBWEAK I2C1_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C1_ER_IRQHandler
        B I2C1_ER_IRQHandler
		
        PUBWEAK I2C2_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C2_EV_IRQHandler
        B I2C2_EV_IRQHandler

        PUBWEAK I2C2_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C2_ER_IRQHandler
        B I2C2_ER_IRQHandler
		
        PUBWEAK I2C3_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C3_EV_IRQHandler
        B I2C3_EV_IRQHandler

        PUBWEAK I2C3_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C3_ER_IRQHandler
        B I2C3_ER_IRQHandler
		
        PUBWEAK I2C4_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C4_EV_IRQHandler
        B I2C4_EV_IRQHandler

        PUBWEAK I2C4_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C4_ER_IRQHandler
        B I2C4_ER_IRQHandler
		
        PUBWEAK I2C5_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C5_EV_IRQHandler
        B I2C5_EV_IRQHandler

        PUBWEAK I2C5_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C5_ER_IRQHandler
        B I2C5_ER_IRQHandler
		
        PUBWEAK I2C6_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C6_EV_IRQHandler
        B I2C6_EV_IRQHandler

        PUBWEAK I2C6_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C6_ER_IRQHandler
        B I2C6_ER_IRQHandler
		
        PUBWEAK I2C7_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C7_EV_IRQHandler
        B I2C7_EV_IRQHandler

        PUBWEAK I2C7_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C7_ER_IRQHandler
        B I2C7_ER_IRQHandler
		
        PUBWEAK I2C8_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C8_EV_IRQHandler
        B I2C8_EV_IRQHandler

        PUBWEAK I2C8_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C8_ER_IRQHandler
        B I2C8_ER_IRQHandler

        PUBWEAK I2C9_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C9_EV_IRQHandler
        B I2C9_EV_IRQHandler

        PUBWEAK I2C9_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C9_ER_IRQHandler
        B I2C9_ER_IRQHandler
		
        PUBWEAK I2C10_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C10_EV_IRQHandler
        B I2C10_EV_IRQHandler

        PUBWEAK I2C10_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C10_ER_IRQHandler
        B I2C10_ER_IRQHandler

        PUBWEAK I2S1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2S1_IRQHandler
        B I2S1_IRQHandler

        PUBWEAK I2S2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2S2_IRQHandler
        B I2S2_IRQHandler

        PUBWEAK I2S3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2S3_IRQHandler
        B I2S3_IRQHandler

        PUBWEAK I2S4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2S4_IRQHandler
        B I2S4_IRQHandler

        PUBWEAK xSPI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
xSPI1_IRQHandler
        B xSPI1_IRQHandler

        PUBWEAK xSPI2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
xSPI2_IRQHandler
        B xSPI2_IRQHandler

        PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI1_IRQHandler
        B SPI1_IRQHandler

        PUBWEAK SPI2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI2_IRQHandler
        B SPI2_IRQHandler

        PUBWEAK SPI3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI3_IRQHandler
        B SPI3_IRQHandler

        PUBWEAK SPI4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI4_IRQHandler
        B SPI4_IRQHandler

        PUBWEAK SPI5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI5_IRQHandler
        B SPI5_IRQHandler

        PUBWEAK SPI6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI6_IRQHandler
        B SPI6_IRQHandler
		
        PUBWEAK SPI7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI7_IRQHandler
        B SPI7_IRQHandler

        PUBWEAK LCD_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
LCD_EV_IRQHandler
        B LCD_EV_IRQHandler

        PUBWEAK LCD_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
LCD_ER_IRQHandler
        B LCD_ER_IRQHandler

        PUBWEAK DVP1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DVP1_IRQHandler
        B DVP1_IRQHandler

        PUBWEAK DVP2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DVP2_IRQHandler
        B DVP2_IRQHandler

        PUBWEAK DMAMUX2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMAMUX2_IRQHandler
        B DMAMUX2_IRQHandler

        PUBWEAK USB1_HS_EPx_OUT_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USB1_HS_EPx_OUT_IRQHandler
        B USB1_HS_EPx_OUT_IRQHandler

        PUBWEAK USB1_HS_EPx_IN_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USB1_HS_EPx_IN_IRQHandler
        B USB1_HS_EPx_IN_IRQHandler

        PUBWEAK USB1_HS_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USB1_HS_WKUP_IRQHandler
        B USB1_HS_WKUP_IRQHandler

        PUBWEAK USB1_HS_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USB1_HS_IRQHandler
        B USB1_HS_IRQHandler

        PUBWEAK USB2_HS_EPx_OUT_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USB2_HS_EPx_OUT_IRQHandler
        B USB2_HS_EPx_OUT_IRQHandler

        PUBWEAK USB2_HS_EPx_IN_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USB2_HS_EPx_IN_IRQHandler
        B USB2_HS_EPx_IN_IRQHandler

        PUBWEAK USB2_HS_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USB2_HS_WKUP_IRQHandler
        B USB2_HS_WKUP_IRQHandler

        PUBWEAK USB2_HS_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USB2_HS_IRQHandler
        B USB2_HS_IRQHandler

        PUBWEAK ETH1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ETH1_IRQHandler
        B ETH1_IRQHandler

        PUBWEAK ETH1_PMT_LPI_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ETH1_PMT_LPI_IRQHandler
        B ETH1_PMT_LPI_IRQHandler

        PUBWEAK ETH2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ETH2_IRQHandler
        B ETH2_IRQHandler

        PUBWEAK ETH2_PMT_LPI_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ETH2_PMT_LPI_IRQHandler
        B ETH2_PMT_LPI_IRQHandler

        PUBWEAK FDCAN1_INT0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FDCAN1_INT0_IRQHandler
        B FDCAN1_INT0_IRQHandler

        PUBWEAK FDCAN2_INT0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FDCAN2_INT0_IRQHandler
        B FDCAN2_INT0_IRQHandler

        PUBWEAK FDCAN3_INT0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FDCAN3_INT0_IRQHandler
        B FDCAN3_INT0_IRQHandler

        PUBWEAK FDCAN4_INT0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FDCAN4_INT0_IRQHandler
        B FDCAN4_INT0_IRQHandler

        PUBWEAK FDCAN1_INT1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FDCAN1_INT1_IRQHandler
        B FDCAN1_INT1_IRQHandler

        PUBWEAK FDCAN2_INT1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FDCAN2_INT1_IRQHandler
        B FDCAN2_INT1_IRQHandler

        PUBWEAK FDCAN3_INT1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FDCAN3_INT1_IRQHandler
        B FDCAN3_INT1_IRQHandler

        PUBWEAK FDCAN4_INT1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FDCAN4_INT1_IRQHandler
        B FDCAN4_INT1_IRQHandler

        PUBWEAK USART1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART1_IRQHandler
        B USART1_IRQHandler

        PUBWEAK USART2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART2_IRQHandler
        B USART2_IRQHandler

        PUBWEAK USART3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART3_IRQHandler
        B USART3_IRQHandler

        PUBWEAK USART4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART4_IRQHandler
        B USART4_IRQHandler

        PUBWEAK USART5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART5_IRQHandler
        B USART5_IRQHandler

        PUBWEAK USART6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART6_IRQHandler
        B USART6_IRQHandler

        PUBWEAK USART7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART7_IRQHandler
        B USART7_IRQHandler
		
        PUBWEAK USART8_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART8_IRQHandler
        B USART8_IRQHandler

        PUBWEAK UART9_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART9_IRQHandler
        B UART9_IRQHandler

        PUBWEAK UART10_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART10_IRQHandler
        B UART10_IRQHandler

        PUBWEAK UART11_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART11_IRQHandler
        B UART11_IRQHandler

        PUBWEAK UART12_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART12_IRQHandler
        B UART12_IRQHandler

        PUBWEAK UART13_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART13_IRQHandler
        B UART13_IRQHandler

        PUBWEAK UART14_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART14_IRQHandler
        B UART14_IRQHandler

        PUBWEAK UART15_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART15_IRQHandler
        B UART15_IRQHandler

        PUBWEAK LPUART1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
LPUART1_IRQHandler
        B LPUART1_IRQHandler

        PUBWEAK LPUART2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
LPUART2_IRQHandler
        B LPUART2_IRQHandler

        PUBWEAK GPU_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPU_IRQHandler
        B GPU_IRQHandler

        PUBWEAK SDMMC1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SDMMC1_IRQHandler
        B SDMMC1_IRQHandler

        PUBWEAK SDMMC2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SDMMC2_IRQHandler
        B SDMMC2_IRQHandler

        PUBWEAK ADC1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC1_IRQHandler
        B ADC1_IRQHandler

        PUBWEAK ADC2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC2_IRQHandler
        B ADC2_IRQHandler

        PUBWEAK ADC3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC3_IRQHandler
        B ADC3_IRQHandler

        PUBWEAK COMP1_2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
COMP1_2_IRQHandler
        B COMP1_2_IRQHandler

        PUBWEAK COMP3_4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
COMP3_4_IRQHandler
        B COMP3_4_IRQHandler

        PUBWEAK SHRTIM1_INT1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SHRTIM1_INT1_IRQHandler
        B SHRTIM1_INT1_IRQHandler

        PUBWEAK SHRTIM1_INT2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SHRTIM1_INT2_IRQHandler
        B SHRTIM1_INT2_IRQHandler

        PUBWEAK SHRTIM1_INT3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SHRTIM1_INT3_IRQHandler
        B SHRTIM1_INT3_IRQHandler

        PUBWEAK SHRTIM1_INT4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SHRTIM1_INT4_IRQHandler
        B SHRTIM1_INT4_IRQHandler

        PUBWEAK SHRTIM1_INT5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SHRTIM1_INT5_IRQHandler
        B SHRTIM1_INT5_IRQHandler

        PUBWEAK SHRTIM1_INT6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SHRTIM1_INT6_IRQHandler
        B SHRTIM1_INT6_IRQHandler

        PUBWEAK SHRTIM1_INT7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SHRTIM1_INT7_IRQHandler
        B SHRTIM1_INT7_IRQHandler

        PUBWEAK SHRTIM1_INT8_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SHRTIM1_INT8_IRQHandler
        B SHRTIM1_INT8_IRQHandler

        PUBWEAK SHRTIM2_INT1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SHRTIM2_INT1_IRQHandler
        B SHRTIM2_INT1_IRQHandler

        PUBWEAK SHRTIM2_INT2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SHRTIM2_INT2_IRQHandler
        B SHRTIM2_INT2_IRQHandler

        PUBWEAK SHRTIM2_INT3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SHRTIM2_INT3_IRQHandler
        B SHRTIM2_INT3_IRQHandler

        PUBWEAK SHRTIM2_INT4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SHRTIM2_INT4_IRQHandler
        B SHRTIM2_INT4_IRQHandler

        PUBWEAK SHRTIM2_INT5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SHRTIM2_INT5_IRQHandler
        B SHRTIM2_INT5_IRQHandler

        PUBWEAK SHRTIM2_INT6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SHRTIM2_INT6_IRQHandler
        B SHRTIM2_INT6_IRQHandler

        PUBWEAK SHRTIM2_INT7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SHRTIM2_INT7_IRQHandler
        B SHRTIM2_INT7_IRQHandler

        PUBWEAK SHRTIM2_INT8_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SHRTIM2_INT8_IRQHandler
        B SHRTIM2_INT8_IRQHandler

        PUBWEAK FDCAN5_INT0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FDCAN5_INT0_IRQHandler
        B FDCAN5_INT0_IRQHandler

        PUBWEAK FDCAN6_INT0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FDCAN6_INT0_IRQHandler
        B FDCAN6_INT0_IRQHandler

        PUBWEAK FDCAN7_INT0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FDCAN7_INT0_IRQHandler
        B FDCAN7_INT0_IRQHandler

        PUBWEAK FDCAN8_INT0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FDCAN8_INT0_IRQHandler
        B FDCAN8_INT0_IRQHandler

        PUBWEAK FDCAN5_INT1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FDCAN5_INT1_IRQHandler
        B FDCAN5_INT1_IRQHandler

        PUBWEAK FDCAN6_INT1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FDCAN6_INT1_IRQHandler
        B FDCAN6_INT1_IRQHandler

        PUBWEAK FDCAN7_INT1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FDCAN7_INT1_IRQHandler
        B FDCAN7_INT1_IRQHandler

        PUBWEAK FDCAN8_INT1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FDCAN8_INT1_IRQHandler
        B FDCAN8_INT1_IRQHandler

        PUBWEAK LPTIM5_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
LPTIM5_WKUP_IRQHandler
        B LPTIM5_WKUP_IRQHandler

        PUBWEAK JPEG_SGDMA_H2P_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
JPEG_SGDMA_H2P_IRQHandler
        B JPEG_SGDMA_H2P_IRQHandler

        PUBWEAK JPEG_SGDMA_P2H_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
JPEG_SGDMA_P2H_IRQHandler
        B JPEG_SGDMA_P2H_IRQHandler

        PUBWEAK WAKEUP_IO_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
WAKEUP_IO_IRQHandler
        B WAKEUP_IO_IRQHandler

        PUBWEAK SEMA4_INT1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SEMA4_INT1_IRQHandler
        B SEMA4_INT1_IRQHandler

        PUBWEAK WWDG2_RST_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
WWDG2_RST_IRQHandler
        B WWDG2_RST_IRQHandler

        PUBWEAK OTPC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
OTPC_IRQHandler
        B OTPC_IRQHandler

        PUBWEAK FEMC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FEMC_IRQHandler
        B FEMC_IRQHandler

        PUBWEAK DCMUB_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DCMUB_IRQHandler
        B DCMUB_IRQHandler

        PUBWEAK DAC1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DAC1_IRQHandler
        B DAC1_IRQHandler

        PUBWEAK DAC2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DAC2_IRQHandler
        B DAC2_IRQHandler

        PUBWEAK MDMA_AHBS_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MDMA_AHBS_ER_IRQHandler
        B MDMA_AHBS_ER_IRQHandler

        PUBWEAK CM7_CATCH_READ_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CM7_CATCH_READ_ER_IRQHandler
        B CM7_CATCH_READ_ER_IRQHandler

        PUBWEAK DAC3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DAC3_IRQHandler
        B DAC3_IRQHandler

        PUBWEAK DAC4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DAC4_IRQHandler
        B DAC4_IRQHandler

        PUBWEAK EMC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EMC_IRQHandler
        B EMC_IRQHandler

        PUBWEAK DAC5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DAC5_IRQHandler
        B DAC5_IRQHandler

        PUBWEAK DAC6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DAC6_IRQHandler
        B DAC6_IRQHandler

        PUBWEAK ESC_OPB_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ESC_OPB_IRQHandler
        B ESC_OPB_IRQHandler
		
        PUBWEAK ESC_SYNC0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ESC_SYNC0_IRQHandler
        B ESC_SYNC0_IRQHandler

        PUBWEAK ESC_SYNC1_RQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ESC_SYNC1_RQHandler
        B ESC_SYNC1_RQHandler
		
        PUBWEAK ESC_WRP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ESC_WRP_IRQHandler
        B ESC_WRP_IRQHandler
		
        PUBWEAK ATIM1_BRK_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM1_BRK_IRQHandler
        B ATIM1_BRK_IRQHandler

        PUBWEAK ATIM1_TRG_COM_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM1_TRG_COM_IRQHandler
        B ATIM1_TRG_COM_IRQHandler

        PUBWEAK ATIM1_CC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM1_CC_IRQHandler
        B ATIM1_CC_IRQHandler

        PUBWEAK ATIM1_UP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM1_UP_IRQHandler
        B ATIM1_UP_IRQHandler

        PUBWEAK ATIM2_BRK_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM2_BRK_IRQHandler
        B ATIM2_BRK_IRQHandler

        PUBWEAK ATIM2_TRG_COM_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM2_TRG_COM_IRQHandler
        B ATIM2_TRG_COM_IRQHandler
		
        PUBWEAK ATIM2_CC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM2_CC_IRQHandler
        B ATIM2_CC_IRQHandler		
		
        PUBWEAK ATIM2_UP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM2_UP_IRQHandler
        B ATIM2_UP_IRQHandler

        PUBWEAK ATIM3_BRK_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM3_BRK_IRQHandler
        B ATIM3_BRK_IRQHandler

        PUBWEAK ATIM3_TRG_COM_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM3_TRG_COM_IRQHandler
        B ATIM3_TRG_COM_IRQHandler

        PUBWEAK ATIM3_CC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM3_CC_IRQHandler
        B ATIM3_CC_IRQHandler

        PUBWEAK ATIM3_UP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM3_UP_IRQHandler
        B ATIM3_UP_IRQHandler

        PUBWEAK ATIM4_BRK_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM4_BRK_IRQHandler
        B ATIM4_BRK_IRQHandler

        PUBWEAK ATIM4_TRG_COM_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM4_TRG_COM_IRQHandler
        B ATIM4_TRG_COM_IRQHandler

        PUBWEAK ATIM4_CC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM4_CC_IRQHandler
        B ATIM4_CC_IRQHandler

        PUBWEAK ATIM4_UP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ATIM4_UP_IRQHandler
        B ATIM4_UP_IRQHandler
		
        PUBWEAK GTIMA1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIMA1_IRQHandler
        B GTIMA1_IRQHandler	

        PUBWEAK GTIMA2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIMA2_IRQHandler
        B GTIMA2_IRQHandler
		
        PUBWEAK GTIMA3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIMA3_IRQHandler
        B GTIMA3_IRQHandler	

        PUBWEAK GTIMA4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIMA4_IRQHandler
        B GTIMA4_IRQHandler

        PUBWEAK GTIMA5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIMA5_IRQHandler
        B GTIMA5_IRQHandler
		
        PUBWEAK GTIMA6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIMA6_IRQHandler
        B GTIMA6_IRQHandler		
		
        PUBWEAK GTIMA7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIMA7_IRQHandler
        B GTIMA7_IRQHandler
		
        PUBWEAK GTIMB1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIMB1_IRQHandler
        B GTIMB1_IRQHandler	

        PUBWEAK GTIMB2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIMB2_IRQHandler
        B GTIMB2_IRQHandler
		
        PUBWEAK GTIMB3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GTIMB3_IRQHandler
        B GTIMB3_IRQHandler	

        PUBWEAK BTIM1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
BTIM1_IRQHandler
        B BTIM1_IRQHandler	

        PUBWEAK BTIM2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
BTIM2_IRQHandler
        B BTIM2_IRQHandler	
		
        PUBWEAK BTIM3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
BTIM3_IRQHandler
        B BTIM3_IRQHandler	

        PUBWEAK BTIM4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
BTIM4_IRQHandler
        B BTIM4_IRQHandler	
		
        PUBWEAK LPTIM1_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
LPTIM1_WKUP_IRQHandler
        B LPTIM1_WKUP_IRQHandler	

        PUBWEAK LPTIM2_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
LPTIM2_WKUP_IRQHandler
        B LPTIM2_WKUP_IRQHandler		
		
        PUBWEAK LPTIM3_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
LPTIM3_WKUP_IRQHandler
        B LPTIM3_WKUP_IRQHandler	

        PUBWEAK LPTIM4_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
LPTIM4_WKUP_IRQHandler
        B LPTIM4_WKUP_IRQHandler		
			
        PUBWEAK DSMU_FLT0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DSMU_FLT0_IRQHandler
        B DSMU_FLT0_IRQHandler	

        PUBWEAK DSMU_FLT1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DSMU_FLT1_IRQHandler
        B DSMU_FLT1_IRQHandler		
		
        PUBWEAK DSMU_FLT2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DSMU_FLT2_IRQHandler
        B DSMU_FLT2_IRQHandler	

        PUBWEAK DSMU_FLT3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DSMU_FLT3_IRQHandler
        B DSMU_FLT3_IRQHandler		
		
        PUBWEAK FMAC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FMAC_IRQHandler
        B FMAC_IRQHandler	

        PUBWEAK CORDIC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CORDIC_IRQHandler
        B CORDIC_IRQHandler		
		
        PUBWEAK DMAMUX1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMAMUX1_IRQHandler
        B DMAMUX1_IRQHandler	

        PUBWEAK MMU_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
MMU_IRQHandler
        B MMU_IRQHandler
        
        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B SysTick_Handler
		
        END

