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


Stack_Size      EQU     0x00002000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size

__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size      EQU     0x00002000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp                      ; Top of Stack
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
                DCD     I2C8_ER_IRQHandler        ; I2C8 error interrupt
                DCD     I2C9_EV_IRQHandler         ; I2C9 event interrupt
                DCD     I2C9_ER_IRQHandler         ; I2C9 error interrupt
                DCD     I2C10_EV_IRQHandler        ; I2C10 event interrupt
                DCD     I2C10_ER_IRQHandler        ; I2C10 error interrupt
                DCD     I2S1_IRQHandler            ; I2S1 global interrupt
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
                DCD     SPI6_IRQHandler            ; SPI6 global interrupt
                DCD     SPI7_IRQHandler            ; SPI7 global interrupt
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
                DCD     FDCAN1_INT0_IRQHandler      ; FDCAN1 global interrupt line 0
                DCD     FDCAN2_INT0_IRQHandler      ; FDCAN2 global interrupt line 0
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
                DCD     USART8_IRQHandler          ; USART8 global interrupt
                DCD     UART9_IRQHandler           ; UART9 global interrupt
                DCD     UART10_IRQHandler          ; UART10 global interrupt
                DCD     UART11_IRQHandler          ; UART11 global interrupt
                DCD     UART12_IRQHandler          ; UART12 global interrupt
                DCD     UART13_IRQHandler          ; UART13 global interrupt
                DCD     UART14_IRQHandler          ; UART14 global interrupt
                DCD     UART15_IRQHandler          ; UART15 global interrupt
                DCD     LPUART1_IRQHandler         ; LPUART1 global interrupt + wakeup through EXTI line 49
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
                DCD     SHRTIM1_INT1_IRQHandler    ; High Resolution timer 1 interrupt 1
                DCD     SHRTIM1_INT2_IRQHandler    ; High Resolution timer 1 interrupt 2 
                DCD     SHRTIM1_INT3_IRQHandler    ; High Resolution timer 1 interrupt 3 
                DCD     SHRTIM1_INT4_IRQHandler    ; High Resolution timer 1 interrupt 4 
                DCD     SHRTIM1_INT5_IRQHandler    ; High Resolution timer 1 interrupt 5 
                DCD     SHRTIM1_INT6_IRQHandler    ; High Resolution timer 1 interrupt 6 
                DCD     SHRTIM1_INT7_IRQHandler    ; High Resolution timer 1 interrupt 7 
                DCD     SHRTIM1_INT8_IRQHandler    ; High Resolution timer 1 interrupt 8 
                DCD     SHRTIM2_INT1_IRQHandler    ; High Resolution timer 2 interrupt 1
                DCD     SHRTIM2_INT2_IRQHandler    ; High Resolution timer 2 interrupt 2 
                DCD     SHRTIM2_INT3_IRQHandler    ; High Resolution timer 2 interrupt 3 
                DCD     SHRTIM2_INT4_IRQHandler    ; High Resolution timer 2 interrupt 4 
                DCD     SHRTIM2_INT5_IRQHandler    ; High Resolution timer 2 interrupt 5 
                DCD     SHRTIM2_INT6_IRQHandler    ; High Resolution timer 2 interrupt 6 
                DCD     SHRTIM2_INT7_IRQHandler    ; High Resolution timer 2 interrupt 7 
                DCD     SHRTIM2_INT8_IRQHandler    ; High Resolution timer 2 interrupt 8 
                DCD     FDCAN5_INT0_IRQHandler     ; FDCAN5 global interrupt line 0
                DCD     FDCAN6_INT0_IRQHandler     ; FDCAN6 global interrupt line 0
                DCD     FDCAN7_INT0_IRQHandler     ; FDCAN7 global interrupt line 0
                DCD     FDCAN8_INT0_IRQHandler     ; FDCAN8 global interrupt line 0
                DCD     FDCAN5_INT1_IRQHandler     ; FDCAN5 global interrupt line 1
                DCD     FDCAN6_INT1_IRQHandler     ; FDCAN6 global interrupt line 1
                DCD     FDCAN7_INT1_IRQHandler     ; FDCAN7 global interrupt line 1
                DCD     FDCAN8_INT1_IRQHandler     ; FDCAN8 global interrupt line 1
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
                DCD     DAC5_IRQHandler            ; DAC5 interrupt
                DCD     DAC6_IRQHandler            ; DAC6 interrupt
                DCD     ESC_OPB_IRQHandler         ; ETHERCAT OPB Interrupt
                DCD     ESC_SYNC0_IRQHandler       ; ETHERCAT SYNC0 Interrupt
                DCD     ESC_SYNC1_IRQHandler       ; ETHERCAT SYNC1 Interrupt
                DCD     ESC_WRP_IRQHandler         ; ETHERCAT WRAPPER Interrupt
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

__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler
Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  __main
                IMPORT  SystemInit
                LDR     R0, =SystemInit
                BLX     R0               
                LDR     R0, =__main
                BX      R0
                ENDP
                
; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                      [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler                [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler                [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler                 [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler               [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                      [WEAK]
                B       .
				
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler                  [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                    [WEAK]
                B       .
                ENDP
N32SysTick_Handler PROC
                EXPORT  N32SysTick_Handler                   [WEAK]
                B       .
                ENDP                                     
                                                          
Default_Handler PROC                                      

                EXPORT  WWDG1_IRQHandler                        [WEAK]
                EXPORT  PVD_IRQHandler                          [WEAK]
                EXPORT  RTC_TAMPER_IRQHandler                        [WEAK]
                EXPORT  RTC_WKUP_IRQHandler                     [WEAK]
                EXPORT  RCC_IRQHandler                          [WEAK]
                EXPORT  EXTI0_IRQHandler                        [WEAK]
                EXPORT  EXTI1_IRQHandler                        [WEAK]
                EXPORT  EXTI2_IRQHandler                        [WEAK]
                EXPORT  EXTI3_IRQHandler                        [WEAK]
                EXPORT  EXTI4_IRQHandler                        [WEAK]
                EXPORT  EXTI9_5_IRQHandler                           [WEAK]
                EXPORT  EXTI15_10_IRQHandler                         [WEAK]
                EXPORT  DMA1_Channel0_IRQHandler                [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler                [WEAK]
                EXPORT  DMA1_Channel2_IRQHandler                [WEAK]
                EXPORT  DMA1_Channel3_IRQHandler                [WEAK]
                EXPORT  DMA1_Channel4_IRQHandler                [WEAK]
                EXPORT  DMA1_Channel5_IRQHandler                [WEAK]
                EXPORT  DMA1_Channel6_IRQHandler                [WEAK]
                EXPORT  DMA1_Channel7_IRQHandler                [WEAK]
                EXPORT  DMA2_Channel0_IRQHandler                [WEAK]
                EXPORT  DMA2_Channel1_IRQHandler                [WEAK]
                EXPORT  DMA2_Channel2_IRQHandler                [WEAK]
                EXPORT  DMA2_Channel3_IRQHandler                [WEAK]
                EXPORT  DMA2_Channel4_IRQHandler                [WEAK]
                EXPORT  DMA2_Channel5_IRQHandler                [WEAK]
                EXPORT  DMA2_Channel6_IRQHandler                [WEAK]
                EXPORT  DMA2_Channel7_IRQHandler                [WEAK]
                EXPORT  DMA3_Channel0_IRQHandler                [WEAK]
                EXPORT  DMA3_Channel1_IRQHandler                [WEAK]
                EXPORT  DMA3_Channel2_IRQHandler                [WEAK]
                EXPORT  DMA3_Channel3_IRQHandler                [WEAK]
                EXPORT  DMA3_Channel4_IRQHandler                [WEAK]
                EXPORT  DMA3_Channel5_IRQHandler                [WEAK]
                EXPORT  DMA3_Channel6_IRQHandler                [WEAK]
                EXPORT  DMA3_Channel7_IRQHandler                [WEAK]
                EXPORT  MDMA_Channel0_IRQHandler                [WEAK]
                EXPORT  MDMA_Channel1_IRQHandler                [WEAK]
                EXPORT  MDMA_Channel2_IRQHandler                [WEAK]
                EXPORT  MDMA_Channel3_IRQHandler                [WEAK]
                EXPORT  MDMA_Channel4_IRQHandler                [WEAK]
                EXPORT  MDMA_Channel5_IRQHandler                [WEAK]
                EXPORT  MDMA_Channel6_IRQHandler                [WEAK]
                EXPORT  MDMA_Channel7_IRQHandler                [WEAK]
                EXPORT  MDMA_Channel8_IRQHandler                [WEAK]
                EXPORT  MDMA_Channel9_IRQHandler                [WEAK]
                EXPORT  MDMA_Channel10_IRQHandler               [WEAK]
                EXPORT  MDMA_Channel11_IRQHandler               [WEAK]
                EXPORT  MDMA_Channel12_IRQHandler               [WEAK]
                EXPORT  MDMA_Channel13_IRQHandler               [WEAK]
                EXPORT  MDMA_Channel14_IRQHandler               [WEAK]
                EXPORT  MDMA_Channel15_IRQHandler               [WEAK]
                EXPORT  SDPU_IRQHandler                         [WEAK] 
                EXPORT  FPU_CPU1_IRQHandler		                [WEAK]
                EXPORT  ECCMON_IRQHandler                       [WEAK]
                EXPORT  RTC_ALARM_IRQHandler                    [WEAK]
                EXPORT  I2C1_EV_IRQHandler                           [WEAK]
                EXPORT  I2C1_ER_IRQHandler                      [WEAK]
                EXPORT  I2C2_EV_IRQHandler                           [WEAK]
                EXPORT  I2C2_ER_IRQHandler                      [WEAK]
                EXPORT  I2C3_EV_IRQHandler                           [WEAK]
                EXPORT  I2C3_ER_IRQHandler                      [WEAK]
                EXPORT  I2C4_EV_IRQHandler                           [WEAK]
                EXPORT  I2C4_ER_IRQHandler                      [WEAK]
                EXPORT  I2C5_EV_IRQHandler                           [WEAK]
                EXPORT  I2C5_ER_IRQHandler                      [WEAK]
                EXPORT  I2C6_EV_IRQHandler                           [WEAK]
                EXPORT  I2C6_ER_IRQHandler                      [WEAK]
                EXPORT  I2C7_EV_IRQHandler                           [WEAK]
                EXPORT  I2C7_ER_IRQHandler                      [WEAK]
                EXPORT  I2C8_EV_IRQHandler                           [WEAK]
                EXPORT  I2C8_ER_IRQHandler                      [WEAK]
                EXPORT  I2C9_EV_IRQHandler                           [WEAK]
                EXPORT  I2C9_ER_IRQHandler                           [WEAK]
                EXPORT  I2C10_EV_IRQHandler                          [WEAK]
                EXPORT  I2C10_ER_IRQHandler                          [WEAK]
                EXPORT  I2S1_IRQHandler                              [WEAK]
                EXPORT  I2S2_IRQHandler                              [WEAK]
                EXPORT  I2S3_IRQHandler                              [WEAK]
                EXPORT  I2S4_IRQHandler                              [WEAK]
                EXPORT  xSPI1_IRQHandler                             [WEAK]
                EXPORT  xSPI2_IRQHandler                             [WEAK]
                EXPORT  SPI1_IRQHandler                              [WEAK]
                EXPORT  SPI2_IRQHandler                              [WEAK]
                EXPORT  SPI3_IRQHandler                              [WEAK]
                EXPORT  SPI4_IRQHandler                              [WEAK]
                EXPORT  SPI5_IRQHandler                              [WEAK]
                EXPORT  SPI6_IRQHandler                              [WEAK]
                EXPORT  SPI7_IRQHandler                              [WEAK]
                EXPORT  LCD_EV_IRQHandler                            [WEAK]
                EXPORT  LCD_ER_IRQHandler                            [WEAK]
                EXPORT  DVP1_IRQHandler                         [WEAK] 
                EXPORT  DVP2_IRQHandler                         [WEAK] 
                EXPORT  DMAMUX2_IRQHandler                      [WEAK]
                EXPORT  USB1_HS_EPx_OUT_IRQHandler               [WEAK]
                EXPORT  USB1_HS_EPx_IN_IRQHandler                [WEAK]
                EXPORT  USB1_HS_WKUP_IRQHandler                 [WEAK]
                EXPORT  USB1_HS_IRQHandler                      [WEAK]
                EXPORT  USB2_HS_EPx_OUT_IRQHandler               [WEAK]
                EXPORT  USB2_HS_EPx_IN_IRQHandler                [WEAK]
                EXPORT  USB2_HS_WKUP_IRQHandler                 [WEAK]
                EXPORT  USB2_HS_IRQHandler                      [WEAK]
                EXPORT  ETH1_IRQHandler                         [WEAK]
                EXPORT  ETH1_PMT_LPI_IRQHandler                 [WEAK]
                EXPORT  ETH2_IRQHandler                         [WEAK]
                EXPORT  ETH2_PMT_LPI_IRQHandler                 [WEAK]
                EXPORT  FDCAN1_INT0_IRQHandler                       [WEAK]
                EXPORT  FDCAN2_INT0_IRQHandler                       [WEAK]
                EXPORT  FDCAN3_INT0_IRQHandler                       [WEAK]
                EXPORT  FDCAN4_INT0_IRQHandler                       [WEAK]
                EXPORT  FDCAN1_INT1_IRQHandler                       [WEAK]
                EXPORT  FDCAN2_INT1_IRQHandler                       [WEAK]
                EXPORT  FDCAN3_INT1_IRQHandler                       [WEAK]
                EXPORT  FDCAN4_INT1_IRQHandler                       [WEAK]
                EXPORT  USART1_IRQHandler                       [WEAK]
                EXPORT  USART2_IRQHandler                       [WEAK]
                EXPORT  USART3_IRQHandler                       [WEAK]
                EXPORT  USART4_IRQHandler                       [WEAK]
                EXPORT  USART5_IRQHandler                       [WEAK]
                EXPORT  USART6_IRQHandler                       [WEAK]
                EXPORT  USART7_IRQHandler                            [WEAK]
                EXPORT  USART8_IRQHandler                            [WEAK]
                EXPORT  UART9_IRQHandler                             [WEAK]
                EXPORT  UART10_IRQHandler                            [WEAK]
                EXPORT  UART11_IRQHandler                            [WEAK]
                EXPORT  UART12_IRQHandler                            [WEAK]
                EXPORT  UART13_IRQHandler                            [WEAK]
                EXPORT  UART14_IRQHandler                            [WEAK]
                EXPORT  UART15_IRQHandler                            [WEAK]
                EXPORT  LPUART1_IRQHandler                           [WEAK]
                EXPORT  LPUART2_IRQHandler                      [WEAK]
                EXPORT  GPU_IRQHandler                          [WEAK]
                EXPORT  SDMMC1_IRQHandler                       [WEAK]
                EXPORT  SDMMC2_IRQHandler                       [WEAK]
                EXPORT  ADC1_IRQHandler                         [WEAK]
                EXPORT  ADC2_IRQHandler                         [WEAK]
                EXPORT  ADC3_IRQHandler                         [WEAK]
                EXPORT  COMP1_2_IRQHandler                           [WEAK]
                EXPORT  COMP3_4_IRQHandler                           [WEAK]
                EXPORT  SHRTIM1_INT1_IRQHandler                 [WEAK]
                EXPORT  SHRTIM1_INT2_IRQHandler                 [WEAK]
                EXPORT  SHRTIM1_INT3_IRQHandler                 [WEAK]
                EXPORT  SHRTIM1_INT4_IRQHandler                 [WEAK]
                EXPORT  SHRTIM1_INT5_IRQHandler                 [WEAK]
                EXPORT  SHRTIM1_INT6_IRQHandler                 [WEAK]
                EXPORT  SHRTIM1_INT7_IRQHandler                 [WEAK]
                EXPORT  SHRTIM1_INT8_IRQHandler                 [WEAK]
                EXPORT  SHRTIM2_INT1_IRQHandler                 [WEAK]
                EXPORT  SHRTIM2_INT2_IRQHandler                 [WEAK]
                EXPORT  SHRTIM2_INT3_IRQHandler                 [WEAK]
                EXPORT  SHRTIM2_INT4_IRQHandler                 [WEAK]
                EXPORT  SHRTIM2_INT5_IRQHandler                 [WEAK]
                EXPORT  SHRTIM2_INT6_IRQHandler                 [WEAK]
                EXPORT  SHRTIM2_INT7_IRQHandler                 [WEAK]
                EXPORT  SHRTIM2_INT8_IRQHandler                 [WEAK]
                EXPORT  FDCAN5_INT0_IRQHandler                       [WEAK]
                EXPORT  FDCAN6_INT0_IRQHandler                       [WEAK]
                EXPORT  FDCAN7_INT0_IRQHandler                       [WEAK]
                EXPORT  FDCAN8_INT0_IRQHandler                       [WEAK]
                EXPORT  FDCAN5_INT1_IRQHandler                       [WEAK]
                EXPORT  FDCAN6_INT1_IRQHandler                       [WEAK]
                EXPORT  FDCAN7_INT1_IRQHandler                       [WEAK]
                EXPORT  FDCAN8_INT1_IRQHandler                       [WEAK]
                EXPORT  LPTIM5_WKUP_IRQHandler                  [WEAK]
                EXPORT  JPEG_SGDMA_H2P_IRQHandler               [WEAK]
                EXPORT  JPEG_SGDMA_P2H_IRQHandler               [WEAK]
                EXPORT  WAKEUP_IO_IRQHandler                    [WEAK]
                EXPORT  SEMA4_INT1_IRQHandler                   [WEAK]
                EXPORT  WWDG2_RST_IRQHandler                    [WEAK]
                EXPORT  OTPC_IRQHandler                         [WEAK]
                EXPORT  FEMC_IRQHandler                         [WEAK]
                EXPORT  DCMUB_IRQHandler                        [WEAK]
                EXPORT  DAC1_IRQHandler                         [WEAK]
                EXPORT  DAC2_IRQHandler                         [WEAK]
                EXPORT  MDMA_AHBS_ER_IRQHandler                      [WEAK]
                EXPORT  CM7_CATCH_READ_ER_IRQHandler                 [WEAK]
                EXPORT  DAC3_IRQHandler                         [WEAK]
                EXPORT  DAC4_IRQHandler                         [WEAK]
                EXPORT  EMC_IRQHandler                          [WEAK]
                EXPORT  DAC5_IRQHandler                         [WEAK]
                EXPORT  DAC6_IRQHandler                         [WEAK]
				EXPORT  ESC_OPB_IRQHandler                      [WEAK]
				EXPORT  ESC_SYNC0_IRQHandler                    [WEAK]
				EXPORT  ESC_SYNC1_IRQHandler                    [WEAK]
				EXPORT  ESC_WRP_IRQHandler                      [WEAK]
                EXPORT  ATIM1_BRK_IRQHandler                    [WEAK]
                EXPORT  ATIM1_TRG_COM_IRQHandler                [WEAK]
                EXPORT  ATIM1_CC_IRQHandler                     [WEAK]
                EXPORT  ATIM1_UP_IRQHandler                     [WEAK]
                EXPORT  ATIM2_BRK_IRQHandler                    [WEAK]
                EXPORT  ATIM2_TRG_COM_IRQHandler                [WEAK]
                EXPORT  ATIM2_CC_IRQHandler                     [WEAK]
                EXPORT  ATIM2_UP_IRQHandler                     [WEAK]
                EXPORT  ATIM3_BRK_IRQHandler                    [WEAK]
                EXPORT  ATIM3_TRG_COM_IRQHandler                [WEAK]
                EXPORT  ATIM3_CC_IRQHandler                     [WEAK]
                EXPORT  ATIM3_UP_IRQHandler                     [WEAK]
                EXPORT  ATIM4_BRK_IRQHandler                    [WEAK]
                EXPORT  ATIM4_TRG_COM_IRQHandler                [WEAK]
                EXPORT  ATIM4_CC_IRQHandler                     [WEAK]
                EXPORT  ATIM4_UP_IRQHandler                     [WEAK]
                EXPORT  GTIMA1_IRQHandler                            [WEAK]
                EXPORT  GTIMA2_IRQHandler                            [WEAK]
                EXPORT  GTIMA3_IRQHandler                            [WEAK]
                EXPORT  GTIMA4_IRQHandler                            [WEAK]
                EXPORT  GTIMA5_IRQHandler                            [WEAK]
                EXPORT  GTIMA6_IRQHandler                            [WEAK]
                EXPORT  GTIMA7_IRQHandler                            [WEAK]
                EXPORT  GTIMB1_IRQHandler                            [WEAK]
                EXPORT  GTIMB2_IRQHandler                            [WEAK]
                EXPORT  GTIMB3_IRQHandler                            [WEAK]
                EXPORT  BTIM1_IRQHandler                        [WEAK]
                EXPORT  BTIM2_IRQHandler                        [WEAK]
                EXPORT  BTIM3_IRQHandler                        [WEAK]
                EXPORT  BTIM4_IRQHandler                        [WEAK]
                EXPORT  LPTIM1_WKUP_IRQHandler                  [WEAK]
                EXPORT  LPTIM2_WKUP_IRQHandler                  [WEAK]
                EXPORT  LPTIM3_WKUP_IRQHandler                  [WEAK]
                EXPORT  LPTIM4_WKUP_IRQHandler                  [WEAK]
                EXPORT  DSMU_FLT0_IRQHandler                    [WEAK]
                EXPORT  DSMU_FLT1_IRQHandler                    [WEAK]
                EXPORT  DSMU_FLT2_IRQHandler                    [WEAK]
                EXPORT  DSMU_FLT3_IRQHandler                    [WEAK]
                EXPORT  FMAC_IRQHandler                              [WEAK]
                EXPORT  CORDIC_IRQHandler                            [WEAK]
                EXPORT  DMAMUX1_IRQHandler                           [WEAK]
                EXPORT  MMU_IRQHandler                               [WEAK] 
                EXPORT  SysTick_Handler                              [WEAK] 

WWDG1_IRQHandler                        
PVD_IRQHandler                          
RTC_TAMPER_IRQHandler           
RTC_WKUP_IRQHandler                     
RCC_IRQHandler                          
EXTI0_IRQHandler                        
EXTI1_IRQHandler                        
EXTI2_IRQHandler                        
EXTI3_IRQHandler                        
EXTI4_IRQHandler                        
EXTI9_5_IRQHandler              
EXTI15_10_IRQHandler            
DMA1_Channel0_IRQHandler                
DMA1_Channel1_IRQHandler                
DMA1_Channel2_IRQHandler                
DMA1_Channel3_IRQHandler                
DMA1_Channel4_IRQHandler                
DMA1_Channel5_IRQHandler                
DMA1_Channel6_IRQHandler                
DMA1_Channel7_IRQHandler                
DMA2_Channel0_IRQHandler                
DMA2_Channel1_IRQHandler                
DMA2_Channel2_IRQHandler                
DMA2_Channel3_IRQHandler                
DMA2_Channel4_IRQHandler                
DMA2_Channel5_IRQHandler                
DMA2_Channel6_IRQHandler                
DMA2_Channel7_IRQHandler                
DMA3_Channel0_IRQHandler                
DMA3_Channel1_IRQHandler                
DMA3_Channel2_IRQHandler                
DMA3_Channel3_IRQHandler                
DMA3_Channel4_IRQHandler                
DMA3_Channel5_IRQHandler                
DMA3_Channel6_IRQHandler                
DMA3_Channel7_IRQHandler                
MDMA_Channel0_IRQHandler                
MDMA_Channel1_IRQHandler                
MDMA_Channel2_IRQHandler                
MDMA_Channel3_IRQHandler                
MDMA_Channel4_IRQHandler                
MDMA_Channel5_IRQHandler                
MDMA_Channel6_IRQHandler                
MDMA_Channel7_IRQHandler                
MDMA_Channel8_IRQHandler                
MDMA_Channel9_IRQHandler                
MDMA_Channel10_IRQHandler               
MDMA_Channel11_IRQHandler               
MDMA_Channel12_IRQHandler               
MDMA_Channel13_IRQHandler               
MDMA_Channel14_IRQHandler               
MDMA_Channel15_IRQHandler               
SDPU_IRQHandler                         
FPU_CPU1_IRQHandler		                
ECCMON_IRQHandler                       
RTC_ALARM_IRQHandler                    
I2C1_EV_IRQHandler              
I2C1_ER_IRQHandler                      
I2C2_EV_IRQHandler              
I2C2_ER_IRQHandler                      
I2C3_EV_IRQHandler              
I2C3_ER_IRQHandler                      
I2C4_EV_IRQHandler              
I2C4_ER_IRQHandler                      
I2C5_EV_IRQHandler              
I2C5_ER_IRQHandler                      
I2C6_EV_IRQHandler              
I2C6_ER_IRQHandler                      
I2C7_EV_IRQHandler              
I2C7_ER_IRQHandler                      
I2C8_EV_IRQHandler              
I2C8_ER_IRQHandler                                          
I2C9_EV_IRQHandler              
I2C9_ER_IRQHandler              
I2C10_EV_IRQHandler             
I2C10_ER_IRQHandler             
I2S1_IRQHandler                 
I2S2_IRQHandler                 
I2S3_IRQHandler                 
I2S4_IRQHandler                 
xSPI1_IRQHandler                
xSPI2_IRQHandler                
SPI1_IRQHandler                 
SPI2_IRQHandler                 
SPI3_IRQHandler                 
SPI4_IRQHandler                 
SPI5_IRQHandler                 
SPI6_IRQHandler                 
SPI7_IRQHandler                 
LCD_EV_IRQHandler               
LCD_ER_IRQHandler               
DVP1_IRQHandler                 
DVP2_IRQHandler                         
DMAMUX2_IRQHandler                      
USB1_HS_EPx_OUT_IRQHandler               
USB1_HS_EPx_IN_IRQHandler                
USB1_HS_WKUP_IRQHandler                 
USB1_HS_IRQHandler                      
USB2_HS_EPx_OUT_IRQHandler               
USB2_HS_EPx_IN_IRQHandler                
USB2_HS_WKUP_IRQHandler                 
USB2_HS_IRQHandler                      
ETH1_IRQHandler                         
ETH1_PMT_LPI_IRQHandler                                 
ETH2_IRQHandler                         
ETH2_PMT_LPI_IRQHandler                 
FDCAN1_INT0_IRQHandler          
FDCAN2_INT0_IRQHandler                    
FDCAN3_INT0_IRQHandler          
FDCAN4_INT0_IRQHandler          
FDCAN1_INT1_IRQHandler          
FDCAN2_INT1_IRQHandler          
FDCAN3_INT1_IRQHandler          
FDCAN4_INT1_IRQHandler          
USART1_IRQHandler                       
USART2_IRQHandler                       
USART3_IRQHandler                       
USART4_IRQHandler                       
USART5_IRQHandler                       
USART6_IRQHandler                       
USART7_IRQHandler                                             
USART8_IRQHandler               
UART9_IRQHandler                
UART10_IRQHandler               
UART11_IRQHandler               
UART12_IRQHandler               
UART13_IRQHandler               
UART14_IRQHandler               
UART15_IRQHandler               
LPUART1_IRQHandler              
LPUART2_IRQHandler              
GPU_IRQHandler                          
SDMMC1_IRQHandler                       
SDMMC2_IRQHandler                       
ADC1_IRQHandler                         
ADC2_IRQHandler                         
ADC3_IRQHandler                         
COMP1_2_IRQHandler              
COMP3_4_IRQHandler              
SHRTIM1_INT1_IRQHandler                 
SHRTIM1_INT2_IRQHandler                 
SHRTIM1_INT3_IRQHandler                 
SHRTIM1_INT4_IRQHandler                 
SHRTIM1_INT5_IRQHandler                 
SHRTIM1_INT6_IRQHandler                 
SHRTIM1_INT7_IRQHandler                 
SHRTIM1_INT8_IRQHandler                 
SHRTIM2_INT1_IRQHandler                 
SHRTIM2_INT2_IRQHandler                 
SHRTIM2_INT3_IRQHandler                 
SHRTIM2_INT4_IRQHandler                 
SHRTIM2_INT5_IRQHandler                 
SHRTIM2_INT6_IRQHandler                 
SHRTIM2_INT7_IRQHandler                 
SHRTIM2_INT8_IRQHandler                 
FDCAN5_INT0_IRQHandler          
FDCAN6_INT0_IRQHandler                   
FDCAN7_INT0_IRQHandler          
FDCAN8_INT0_IRQHandler          
FDCAN5_INT1_IRQHandler          
FDCAN6_INT1_IRQHandler          
FDCAN7_INT1_IRQHandler          
FDCAN8_INT1_IRQHandler          
LPTIM5_WKUP_IRQHandler                  
JPEG_SGDMA_H2P_IRQHandler               
JPEG_SGDMA_P2H_IRQHandler               
WAKEUP_IO_IRQHandler                    
SEMA4_INT1_IRQHandler                   
WWDG2_RST_IRQHandler                    
OTPC_IRQHandler                         
FEMC_IRQHandler                         
DCMUB_IRQHandler                        
DAC1_IRQHandler                         
DAC2_IRQHandler                         
MDMA_AHBS_ER_IRQHandler         
CM7_CATCH_READ_ER_IRQHandler   
DAC3_IRQHandler                         
DAC4_IRQHandler                         
EMC_IRQHandler                                                                                         
DAC5_IRQHandler                         
DAC6_IRQHandler
ESC_OPB_IRQHandler             
ESC_SYNC0_IRQHandler           
ESC_SYNC1_IRQHandler            
ESC_WRP_IRQHandler                           
ATIM1_BRK_IRQHandler                    
ATIM1_TRG_COM_IRQHandler                
ATIM1_CC_IRQHandler                     
ATIM1_UP_IRQHandler                     
ATIM2_BRK_IRQHandler                    
ATIM2_TRG_COM_IRQHandler                
ATIM2_CC_IRQHandler                     
ATIM2_UP_IRQHandler                                         
ATIM3_BRK_IRQHandler                    
ATIM3_TRG_COM_IRQHandler                
ATIM3_CC_IRQHandler                     
ATIM3_UP_IRQHandler                     
ATIM4_BRK_IRQHandler                    
ATIM4_TRG_COM_IRQHandler                
ATIM4_CC_IRQHandler                     
ATIM4_UP_IRQHandler                     
GTIMA1_IRQHandler                        
GTIMA2_IRQHandler                        
GTIMA3_IRQHandler                        
GTIMA4_IRQHandler                        
GTIMA5_IRQHandler                        
GTIMA6_IRQHandler                        
GTIMA7_IRQHandler                        
GTIMB1_IRQHandler                        
GTIMB2_IRQHandler                        
GTIMB3_IRQHandler                       
BTIM1_IRQHandler                        
BTIM2_IRQHandler                        
BTIM3_IRQHandler                        
BTIM4_IRQHandler                        
LPTIM1_WKUP_IRQHandler                  
LPTIM2_WKUP_IRQHandler                  
LPTIM3_WKUP_IRQHandler                  
LPTIM4_WKUP_IRQHandler                  
DSMU_FLT0_IRQHandler                    
DSMU_FLT1_IRQHandler                    
DSMU_FLT2_IRQHandler                    
DSMU_FLT3_IRQHandler                    
FMAC_IRQHandler            
CORDIC_IRQHandler              
DMAMUX1_IRQHandler         
MMU_IRQHandler                 
SysTick_Handler
                B       .

                ENDP

                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB
                
                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit
                
                 ELSE
                
                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap
                 
__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END

