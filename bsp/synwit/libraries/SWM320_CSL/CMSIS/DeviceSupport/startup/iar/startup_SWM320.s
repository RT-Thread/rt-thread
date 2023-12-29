;******************************************************************************************************************************************
; 文件名称:    startup_SWM2400.s
; 功能说明:    SWM2400单片机的启动文件
; 技术支持:    http://www.synwit.com.cn/e/tool/gbook/?bid=1
; 注意事项:
; 版本日期: V1.0.0        2016年1月30日
; 升级记录:
;
;
;******************************************************************************************************************************************
; @attention
;
; THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION
; REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE
; FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
; OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
; -ECTION WITH THEIR PRODUCTS.
;
; COPYRIGHT 2012 Synwit Technology
;******************************************************************************************************************************************

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler              ; Reset Handler
        DCD     NMI_Handler                ; NMI Handler
        DCD     HardFault_Handler          ; Hard Fault Handler
        DCD     MemManage_Handler          ; MPU Fault Handler
        DCD     BusFault_Handler           ; Bus Fault Handler
        DCD     UsageFault_Handler         ; Usage Fault Handler
        DCD     0                          ; Reserved
        DCD     0                          ; Reserved
        DCD     0                          ; Reserved
        DCD     0                          ; Reserved
        DCD     SVC_Handler                ; SVCall Handler
        DCD     DebugMon_Handler           ; Debug Monitor Handler
        DCD     0                          ; Reserved
        DCD     PendSV_Handler             ; PendSV Handler
        DCD     SysTick_Handler            ; SysTick Handler

        ; External Interrupts
        DCD     GPIOA0_Handler
        DCD     GPIOA1_Handler
        DCD     GPIOA2_Handler
        DCD     GPIOA3_Handler
        DCD     GPIOA4_Handler
        DCD     GPIOA5_Handler
        DCD     GPIOA6_Handler
        DCD     GPIOA7_Handler
        DCD     GPIOB0_Handler
        DCD     GPIOB1_Handler
        DCD     GPIOB2_Handler
        DCD     GPIOB3_Handler
        DCD     GPIOB4_Handler
        DCD     GPIOB5_Handler
        DCD     GPIOB6_Handler
        DCD     GPIOB7_Handler
        DCD     GPIOC0_Handler
        DCD     GPIOC1_Handler
        DCD     GPIOC2_Handler
        DCD     GPIOC3_Handler
        DCD     GPIOC4_Handler
        DCD     GPIOC5_Handler
        DCD     GPIOC6_Handler
        DCD     GPIOC7_Handler
        DCD     GPIOM0_Handler
        DCD     GPIOM1_Handler
        DCD     GPIOM2_Handler
        DCD     GPIOM3_Handler
        DCD     GPIOM4_Handler
        DCD     GPIOM5_Handler
        DCD     GPIOM6_Handler
        DCD     GPIOM7_Handler
        DCD     DMA_Handler
        DCD     LCD_Handler
        DCD     NORFLC_Handler
        DCD	    CAN_Handler
        DCD     PULSE_Handler
        DCD     WDT_Handler
        DCD     PWM_Handler
        DCD     UART0_Handler
        DCD     UART1_Handler
        DCD     UART2_Handler
        DCD     UART3_Handler
        DCD     0
        DCD     I2C0_Handler
        DCD     I2C1_Handler
        DCD     SPI0_Handler
        DCD     ADC0_Handler
        DCD     RTC_Handler
        DCD     BOD_Handler
        DCD     SDIO_Handler
        DCD     GPIOA_Handler
        DCD     GPIOB_Handler
        DCD     GPIOC_Handler
        DCD     GPIOM_Handler
        DCD     GPION_Handler
        DCD     GPIOP_Handler
        DCD     ADC1_Handler
        DCD     FPU_Handler
        DCD     SPI1_Handler
        DCD     TIMR0_Handler
        DCD     TIMR1_Handler
        DCD     TIMR2_Handler
        DCD     TIMR3_Handler
        DCD     TIMR4_Handler
        DCD     TIMR5_Handler
        

        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
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

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B SysTick_Handler


        PUBWEAK GPIOA0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOA0_Handler
        B GPIOA0_Handler

        PUBWEAK GPIOA1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOA1_Handler
        B GPIOA1_Handler

        PUBWEAK GPIOA2_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOA2_Handler
        B GPIOA2_Handler

        PUBWEAK GPIOA3_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOA3_Handler
        B GPIOA3_Handler

        PUBWEAK GPIOA4_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOA4_Handler
        B GPIOA4_Handler

        PUBWEAK GPIOA5_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOA5_Handler
        B GPIOA5_Handler

        PUBWEAK GPIOA6_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOA6_Handler
        B GPIOA6_Handler

        PUBWEAK GPIOA7_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOA7_Handler
        B GPIOA7_Handler

        PUBWEAK GPIOB0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOB0_Handler
        B GPIOB0_Handler

        PUBWEAK GPIOB1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOB1_Handler
        B GPIOB1_Handler

        PUBWEAK GPIOB2_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOB2_Handler
        B GPIOB2_Handler

        PUBWEAK GPIOB3_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOB3_Handler
        B GPIOB3_Handler

        PUBWEAK GPIOB4_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOB4_Handler
        B GPIOB4_Handler

        PUBWEAK GPIOB5_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOB5_Handler
        B GPIOB5_Handler

        PUBWEAK GPIOB6_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOB6_Handler
        B GPIOB6_Handler

        PUBWEAK GPIOB7_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOB7_Handler
        B GPIOB7_Handler

        PUBWEAK GPIOC0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOC0_Handler
        B GPIOC0_Handler

        PUBWEAK GPIOC1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOC1_Handler
        B GPIOC1_Handler

        PUBWEAK GPIOC2_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOC2_Handler
        B GPIOC2_Handler

        PUBWEAK GPIOC3_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOC3_Handler
        B GPIOC3_Handler

        PUBWEAK GPIOC4_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOC4_Handler
        B GPIOC4_Handler

        PUBWEAK GPIOC5_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOC5_Handler
        B GPIOC5_Handler

        PUBWEAK GPIOC6_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOC6_Handler
        B GPIOC6_Handler

        PUBWEAK GPIOC7_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOC7_Handler
        B GPIOC7_Handler

        PUBWEAK GPIOM0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOM0_Handler
        B GPIOM0_Handler

        PUBWEAK GPIOM1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOM1_Handler
        B GPIOM1_Handler

        PUBWEAK GPIOM2_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOM2_Handler
        B GPIOM2_Handler

        PUBWEAK GPIOM3_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOM3_Handler
        B GPIOM3_Handler

        PUBWEAK GPIOM4_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOM4_Handler
        B GPIOM4_Handler

        PUBWEAK GPIOM5_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOM5_Handler
        B GPIOM5_Handler

        PUBWEAK GPIOM6_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOM6_Handler
        B GPIOM6_Handler

        PUBWEAK GPIOM7_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOM7_Handler
        B GPIOM7_Handler

        PUBWEAK DMA_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA_Handler
        B DMA_Handler

        PUBWEAK LCD_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
LCD_Handler
        B LCD_Handler

        PUBWEAK NORFLC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NORFLC_Handler
        B NORFLC_Handler

        PUBWEAK CAN_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN_Handler
        B CAN_Handler

        PUBWEAK PULSE_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PULSE_Handler
        B PULSE_Handler

        PUBWEAK WDT_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
WDT_Handler
        B WDT_Handler

        PUBWEAK PWM_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PWM_Handler
        B PWM_Handler

        PUBWEAK UART0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART0_Handler
        B UART0_Handler

        PUBWEAK UART1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART1_Handler
        B UART1_Handler

        PUBWEAK UART2_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART2_Handler
        B UART2_Handler

        PUBWEAK UART3_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART3_Handler
        B UART3_Handler

        PUBWEAK I2C0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C0_Handler
        B I2C0_Handler

        PUBWEAK I2C1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C1_Handler
        B I2C1_Handler

        PUBWEAK SPI0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI0_Handler
        B SPI0_Handler

        PUBWEAK ADC0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC0_Handler
        B ADC0_Handler

        PUBWEAK RTC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC_Handler
        B RTC_Handler

        PUBWEAK BOD_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BOD_Handler
        B BOD_Handler

        PUBWEAK SDIO_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SDIO_Handler
        B SDIO_Handler

        PUBWEAK GPIOA_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOA_Handler
        B GPIOA_Handler

        PUBWEAK GPIOB_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOB_Handler
        B GPIOB_Handler

        PUBWEAK GPIOC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOC_Handler
        B GPIOC_Handler

        PUBWEAK GPIOM_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOM_Handler
        B GPIOM_Handler

        PUBWEAK GPION_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPION_Handler
        B GPION_Handler

        PUBWEAK GPIOP_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOP_Handler
        B GPIOP_Handler

        PUBWEAK ADC1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC1_Handler
        B ADC1_Handler

        PUBWEAK FPU_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
FPU_Handler
        B FPU_Handler

        PUBWEAK SPI1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI1_Handler
        B SPI1_Handler
        
        PUBWEAK TIMR0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMR0_Handler
        B TIMR0_Handler
        
        PUBWEAK TIMR1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMR1_Handler
        B TIMR1_Handler
        
        PUBWEAK TIMR2_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMR2_Handler
        B TIMR2_Handler
        
        PUBWEAK TIMR3_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMR3_Handler
        B TIMR3_Handler
        
        PUBWEAK TIMR4_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMR4_Handler
        B TIMR4_Handler
        
        PUBWEAK TIMR5_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMR5_Handler
        B TIMR5_Handler


        END
