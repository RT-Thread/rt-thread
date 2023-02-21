; ////////////////////////////////////////////////////////////////////////////////
; /// @file     startup_mm32f327x_keil.s
; /// @author   AE TEAM
; /// @brief    THIS FILE PROVIDES ALL THE Device Startup File of MM32 Cortex-M
; ///           Core Device for ARM KEIL toolchain.
; ////////////////////////////////////////////////////////////////////////////////
; /// @attention
; ///
; /// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
; /// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
; /// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
; /// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
; /// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
; /// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
; ///
; /// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
; //////////////////////////////////////////////////////////////////////////////
;
; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp

; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
Heap_Size       EQU     0x00000200

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

__Vectors       DCD     __initial_sp                                            ;         Top of Stack
                DCD     Reset_Handler                                           ;         Reset Handler
                DCD     NMI_Handler                                             ; -14     NMI Handler
                DCD     HardFault_Handler                                       ; -13     Hard Fault Handler
                DCD     MemManage_Handler                                       ; -12     MPU Fault Handler
                DCD     BusFault_Handler                                        ; -11     Bus Fault Handler
                DCD     UsageFault_Handler                                      ; -10     Usage Fault Handler
__vector_table_0x1c
                DCD     0                                                       ; -9      Reserved
                DCD     0                                                       ; -8      Reserved
                DCD     0                                                       ; -7      Reserved
                DCD     0                                                       ; -6      Reserved
                DCD     SVC_Handler                                             ; -5      SVCall Handler
                DCD     DebugMon_Handler                                        ; -4      Debug Monitor Handler
                DCD     0                                                       ; -3      Reserved
                DCD     PendSV_Handler                                          ; -2      PendSV Handler
                DCD     SysTick_Handler                                         ; -1      SysTick Handler  ; External Interrupts     
                DCD     WWDG_IRQHandler                                         ; 0       Window Watchdog
                DCD     PVD_IRQHandler                                          ; 1       PVD through EXTI Line detect
                DCD     TAMPER_IRQHandler                                       ; 2       Tamper
                DCD     RTC_IRQHandler                                          ; 3       RTC
                DCD     FLASH_IRQHandler                                        ; 4       Flash
                DCD     RCC_CRS_IRQHandler                                      ; 5       RCC
                DCD     EXTI0_IRQHandler                                        ; 6       EXTI Line 0
                DCD     EXTI1_IRQHandler                                        ; 7       EXTI Line 1
                DCD     EXTI2_IRQHandler                                        ; 8       EXTI Line 2
                DCD     EXTI3_IRQHandler                                        ; 9       EXTI Line 3
                DCD     EXTI4_IRQHandler                                        ; 10      EXTI Line 4
                DCD     DMA1_Channel1_IRQHandler                                ; 11      DMA1 Channel 1
                DCD     DMA1_Channel2_IRQHandler                                ; 12      DMA1 Channel 2
                DCD     DMA1_Channel3_IRQHandler                                ; 13      DMA1 Channel 3
                DCD     DMA1_Channel4_IRQHandler                                ; 14      DMA1 Channel 4
                DCD     DMA1_Channel5_IRQHandler                                ; 15      DMA1 Channel 5
                DCD     DMA1_Channel6_IRQHandler                                ; 16      DMA1 Channel 6
                DCD     DMA1_Channel7_IRQHandler                                ; 17      DMA1 Channel 7
                DCD     ADC1_2_IRQHandler                                       ; 18      ADC1 and ADC2
                DCD     FlashCache_IRQHandler                                   ; 19      FlashCache outage
                DCD     0                                                       ; 20      Reserved
                DCD     CAN1_RX_IRQHandler                                      ; 21      CAN1_RX
                DCD     0                                                       ; 22      Reserved
                DCD     EXTI9_5_IRQHandler                                      ; 23      EXTI Line 9..5
                DCD     TIM1_BRK_IRQHandler                                     ; 24      TIM1 Break
                DCD     TIM1_UP_IRQHandler                                      ; 25      TIM1 Update
                DCD     TIM1_TRG_COM_IRQHandler                                 ; 26      TIM1 Trigger and Commutation
                DCD     TIM1_CC_IRQHandler                                      ; 27      TIM1 Capture Compare
                DCD     TIM2_IRQHandler                                         ; 28      TIM2
                DCD     TIM3_IRQHandler                                         ; 29      TIM3
                DCD     TIM4_IRQHandler                                         ; 30      TIM4
                DCD     I2C1_IRQHandler                                         ; 31      I2C1 Event
                DCD     0                                                       ; 32      Reserved
                DCD     I2C2_IRQHandler                                         ; 33      I2C2 Event
                DCD     0                                                       ; 34      Reserved
                DCD     SPI1_IRQHandler                                         ; 35      SPI1
                DCD     SPI2_IRQHandler                                         ; 36      SPI2
                DCD     UART1_IRQHandler                                        ; 37      UART1
                DCD     UART2_IRQHandler                                        ; 38      UART2
                DCD     UART3_IRQHandler                                        ; 39      UART3
                DCD     EXTI15_10_IRQHandler                                    ; 40      EXTI Line 15..10
                DCD     RTCAlarm_IRQHandler                                     ; 41      RTC Alarm through EXTI Line 17
                DCD     OTG_FS_WKUP_IRQHandler                                  ; 42      USB OTG FS Wakeup through EXTI line
                DCD     TIM8_BRK_IRQHandler                                     ; 43      TIM8 Break
                DCD     TIM8_UP_IRQHandler                                      ; 44      TIM8 Update
                DCD     TIM8_TRG_COM_IRQHandler                                 ; 45      TIM8 Trigger and Commutation
                DCD     TIM8_CC_IRQHandler                                      ; 46      TIM8 Capture Compare
                DCD     ADC3_IRQHandler                                         ; 47      ADC3
                DCD     0                                                       ; 48      Reserved
                DCD     SDIO_IRQHandler                                         ; 49      SDIO
                DCD     TIM5_IRQHandler                                         ; 50      TIM5
                DCD     SPI3_IRQHandler                                         ; 51      SPI3
                DCD     UART4_IRQHandler                                        ; 52      UART4
                DCD     UART5_IRQHandler                                        ; 53      UART5
                DCD     TIM6_IRQHandler                                         ; 54      TIM6
                DCD     TIM7_IRQHandler                                         ; 55      TIM7
                DCD     DMA2_Channel1_IRQHandler                                ; 56      DMA2 Channel 1
                DCD     DMA2_Channel2_IRQHandler                                ; 57      DMA2 Channel 2
                DCD     DMA2_Channel3_IRQHandler                                ; 58      DMA2 Channel 3
                DCD     DMA2_Channel4_IRQHandler                                ; 59      DMA2 Channel 4
                DCD     DMA2_Channel5_IRQHandler                                ; 60      DMA2 Channel 5
                DCD     ETH_IRQHandler                                          ; 61      Ethernet
                DCD     0                                                       ; 62      Reserved
                DCD     0                                                       ; 63      Reserved
                DCD     COMP1_2_IRQHandler                                      ; 64      COMP1,COMP2
                DCD     0                                                       ; 65      Reserved
                DCD     0                                                       ; 66      Reserved
                DCD     OTG_FS_IRQHandler                                       ; 67      USB OTG_FullSpeed
                DCD     0                                                       ; 68      Reserved
                DCD     0                                                       ; 69      Reserved
                DCD     0                                                       ; 70      Reserved
                DCD     UART6_IRQHandler                                        ; 71      UART6  
                DCD     0                                                       ; 72      Reserved
                DCD     0                                                       ; 73      Reserved
                DCD     0                                                       ; 74      Reserved
                DCD     0                                                       ; 75      Reserved
                DCD     0                                                       ; 76      Reserved
                DCD     0                                                       ; 77      Reserved
                DCD     0                                                       ; 78      Reserved
                DCD     0                                                       ; 79      Reserved
                DCD     0                                                       ; 80      Reserved
                DCD     0                                                       ; 81      Reserved
                DCD     UART7_IRQHandler                                        ; 82      UART7
                DCD     UART8_IRQHandler                                        ; 83      UART8
                                
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler
Reset_Handler   PROC
                EXPORT  Reset_Handler              [WEAK]
                IMPORT  __main
                IMPORT  SystemInit
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler          [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler          [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler           [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler           [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler             [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler            [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WWDG_IRQHandler            [WEAK]
                EXPORT  PVD_IRQHandler             [WEAK]
                EXPORT  TAMPER_IRQHandler          [WEAK]
                EXPORT  RTC_IRQHandler             [WEAK]
                EXPORT  FLASH_IRQHandler           [WEAK]
                EXPORT  RCC_CRS_IRQHandler         [WEAK]
                EXPORT  EXTI0_IRQHandler           [WEAK]
                EXPORT  EXTI1_IRQHandler           [WEAK]
                EXPORT  EXTI2_IRQHandler           [WEAK]
                EXPORT  EXTI3_IRQHandler           [WEAK]
                EXPORT  EXTI4_IRQHandler           [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler   [WEAK]
                EXPORT  DMA1_Channel2_IRQHandler   [WEAK]
                EXPORT  DMA1_Channel3_IRQHandler   [WEAK]
                EXPORT  DMA1_Channel4_IRQHandler   [WEAK]
                EXPORT  DMA1_Channel5_IRQHandler   [WEAK]
                EXPORT  DMA1_Channel6_IRQHandler   [WEAK]
                EXPORT  DMA1_Channel7_IRQHandler   [WEAK]
                EXPORT  ADC1_2_IRQHandler          [WEAK]
                EXPORT  FlashCache_IRQHandler      [WEAK]
                EXPORT  CAN1_RX_IRQHandler         [WEAK]
                EXPORT  EXTI9_5_IRQHandler         [WEAK]
                EXPORT  TIM1_BRK_IRQHandler        [WEAK]
                EXPORT  TIM1_UP_IRQHandler         [WEAK]
                EXPORT  TIM1_TRG_COM_IRQHandler    [WEAK]
                EXPORT  TIM1_CC_IRQHandler         [WEAK]
                EXPORT  TIM2_IRQHandler            [WEAK]
                EXPORT  TIM3_IRQHandler            [WEAK]
                EXPORT  TIM4_IRQHandler            [WEAK]
                EXPORT  I2C1_IRQHandler            [WEAK]
                EXPORT  I2C2_IRQHandler            [WEAK]
                EXPORT  SPI1_IRQHandler            [WEAK]
                EXPORT  SPI2_IRQHandler            [WEAK]
                EXPORT  UART1_IRQHandler           [WEAK]
                EXPORT  UART2_IRQHandler           [WEAK]
                EXPORT  UART3_IRQHandler           [WEAK]
                EXPORT  EXTI15_10_IRQHandler       [WEAK]
                EXPORT  RTCAlarm_IRQHandler        [WEAK]
                EXPORT  OTG_FS_WKUP_IRQHandler     [WEAK]
                EXPORT  TIM8_BRK_IRQHandler        [WEAK]
                EXPORT  TIM8_UP_IRQHandler         [WEAK]
                EXPORT  TIM8_TRG_COM_IRQHandler    [WEAK]
                EXPORT  TIM8_CC_IRQHandler         [WEAK]
                EXPORT  ADC3_IRQHandler            [WEAK]
                EXPORT  SDIO_IRQHandler            [WEAK]
                EXPORT  TIM5_IRQHandler            [WEAK]
                EXPORT  SPI3_IRQHandler            [WEAK]
                EXPORT  UART4_IRQHandler           [WEAK]
                EXPORT  UART5_IRQHandler           [WEAK]
                EXPORT  TIM6_IRQHandler            [WEAK]
                EXPORT  TIM7_IRQHandler            [WEAK]
                EXPORT  DMA2_Channel1_IRQHandler   [WEAK]
                EXPORT  DMA2_Channel2_IRQHandler   [WEAK]
                EXPORT  DMA2_Channel3_IRQHandler   [WEAK]
                EXPORT  DMA2_Channel4_IRQHandler   [WEAK]
                EXPORT  DMA2_Channel5_IRQHandler   [WEAK]
                EXPORT  ETH_IRQHandler             [WEAK]
                EXPORT  COMP1_2_IRQHandler         [WEAK]
                EXPORT  OTG_FS_IRQHandler          [WEAK]
                EXPORT  UART6_IRQHandler           [WEAK]
                EXPORT  UART7_IRQHandler           [WEAK]
                EXPORT  UART8_IRQHandler           [WEAK]
                
WWDG_IRQHandler           
PVD_IRQHandler            
TAMPER_IRQHandler         
RTC_IRQHandler            
FLASH_IRQHandler          
RCC_CRS_IRQHandler        
EXTI0_IRQHandler          
EXTI1_IRQHandler          
EXTI2_IRQHandler          
EXTI3_IRQHandler          
EXTI4_IRQHandler          
DMA1_Channel1_IRQHandler  
DMA1_Channel2_IRQHandler  
DMA1_Channel3_IRQHandler  
DMA1_Channel4_IRQHandler  
DMA1_Channel5_IRQHandler  
DMA1_Channel6_IRQHandler  
DMA1_Channel7_IRQHandler  
ADC1_2_IRQHandler           
FlashCache_IRQHandler     
CAN1_RX_IRQHandler        
EXTI9_5_IRQHandler        
TIM1_BRK_IRQHandler       
TIM1_UP_IRQHandler        
TIM1_TRG_COM_IRQHandler   
TIM1_CC_IRQHandler        
TIM2_IRQHandler           
TIM3_IRQHandler           
TIM4_IRQHandler           
I2C1_IRQHandler           
I2C2_IRQHandler           
SPI1_IRQHandler           
SPI2_IRQHandler           
UART1_IRQHandler          
UART2_IRQHandler          
UART3_IRQHandler          
EXTI15_10_IRQHandler      
RTCAlarm_IRQHandler       
OTG_FS_WKUP_IRQHandler       
TIM8_BRK_IRQHandler       
TIM8_UP_IRQHandler        
TIM8_TRG_COM_IRQHandler   
TIM8_CC_IRQHandler        
ADC3_IRQHandler           
SDIO_IRQHandler           
TIM5_IRQHandler           
SPI3_IRQHandler           
UART4_IRQHandler          
UART5_IRQHandler          
TIM6_IRQHandler           
TIM7_IRQHandler           
DMA2_Channel1_IRQHandler  
DMA2_Channel2_IRQHandler  
DMA2_Channel3_IRQHandler  
DMA2_Channel4_IRQHandler  
DMA2_Channel5_IRQHandler  
ETH_IRQHandler     
COMP1_2_IRQHandler        
OTG_FS_IRQHandler     
UART6_IRQHandler          
UART7_IRQHandler          
UART8_IRQHandler          

                             
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
                LDR     R1, = (Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, =  Stack_Mem
                BX      LR  
                            
                ALIGN       
                            
                ENDIF       
                            
                END         
                        