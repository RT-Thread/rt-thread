;******************************************************************************************************************************************
; 文件名称: startup_SWM341.s
; 功能说明: SWM341单片机的启动文件
; 技术支持: http://www.synwit.com.cn/e/tool/gbook/?bid=1
; 注意事项:
; 版本日期: V1.0.0        2019年5月30日
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
        DCD     UART0_Handler
        DCD     UART1_Handler
        DCD     TIMR0_Handler
        DCD     TIMR1_Handler
        DCD     DMA_Handler
        DCD     SPI0_Handler
        DCD     PWM0_Handler
        DCD     WDT_Handler
        DCD     UART2_Handler
        DCD     PWM1_Handler
        DCD     ADC0_Handler
        DCD     BTIMR0_Handler
        DCD     HALL0_Handler
        DCD     PWM2_Handler
        DCD     PWMBRK_Handler
        DCD     I2C0_Handler
        DCD     CAN0_Handler
        DCD     SPI1_Handler
        DCD     RTC_Handler
        DCD     PWM3_Handler
        DCD     TIMR2_Handler
        DCD     UART3_Handler
        DCD     TIMR3_Handler
        DCD     ADC1_Handler
        DCD     BOD_Handler
        DCD     CORDIC_Handler
        DCD     BTIMR1_Handler
        DCD     PWM4_Handler
        DCD     HALL3_Handler
        DCD     BTIMR2_Handler
        DCD     I2C1_Handler
        DCD     BTIMR3_Handler
        DCD     ACMP_Handler
        DCD     XTALSTOP_Handler
        DCD     FSPI_Handler
        DCD     GPIOA_Handler
        DCD     GPIOB_Handler
        DCD     GPIOC_Handler
        DCD     GPIOD_Handler
        DCD     GPIOM_Handler
        DCD     GPION_Handler
        DCD     GPIOA0_Handler
        DCD     GPIOA1_Handler
        DCD     GPIOA5_Handler
        DCD     GPIOA6_Handler
        DCD     GPIOA10_Handler
        DCD     GPIOA11_Handler
        DCD     GPIOA12_Handler
        DCD     GPIOA13_Handler
        DCD     GPIOB0_Handler
        DCD     GPIOB1_Handler
        DCD     GPIOB2_Handler
        DCD     GPIOC0_Handler
        DCD     GPIOC1_Handler
        DCD     GPIOC2_Handler
        DCD     GPIOC3_Handler
        DCD     GPIOC4_Handler
        DCD     GPIOD3_Handler
        DCD     GPIOD4_Handler
        DCD     GPIOD5_Handler
        DCD     GPIOD6_Handler
        DCD     GPIOD7_Handler
        DCD     GPIOD8_Handler
        DCD     GPIOC9_Handler
        DCD     GPIOC10_Handler
        DCD     GPIOC11_Handler
        DCD     GPIOC12_Handler
        DCD     GPIOM0_Handler
        DCD     GPIOM1_Handler
        DCD     GPIOM2_Handler
        DCD     GPIOM3_Handler
        DCD     GPIOM4_Handler
        DCD     DIV_Handler
        DCD     LCD_Handler
        DCD     GPIOE_Handler
        DCD     JPEG_Handler
        DCD     SDIO_Handler
        DCD     USB_Handler
        DCD     CAN1_Handler
        DCD     TIMR4_Handler
        DCD     BTIMR4_Handler
        DCD     BTIMR5_Handler
        DCD     BTIMR6_Handler
        DCD     BTIMR7_Handler
        DCD     BTIMR8_Handler
        DCD     BTIMR9_Handler
        DCD     BTIMR10_Handler
        DCD     BTIMR11_Handler
        DCD     DMA2D_Handler
        DCD     QEI_Handler
        

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


        PUBWEAK UART0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART0_Handler
        B UART0_Handler

        PUBWEAK UART1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART1_Handler
        B UART1_Handler

        PUBWEAK TIMR0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMR0_Handler
        B TIMR0_Handler

        PUBWEAK TIMR1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMR1_Handler
        B TIMR1_Handler

        PUBWEAK DMA_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA_Handler
        B DMA_Handler

        PUBWEAK SPI0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI0_Handler
        B SPI0_Handler

        PUBWEAK PWM0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PWM0_Handler
        B PWM0_Handler

        PUBWEAK WDT_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
WDT_Handler
        B WDT_Handler

        PUBWEAK UART2_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART2_Handler
        B UART2_Handler

        PUBWEAK PWM1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PWM1_Handler
        B PWM1_Handler

        PUBWEAK ADC0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC0_Handler
        B ADC0_Handler

        PUBWEAK BTIMR0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BTIMR0_Handler
        B BTIMR0_Handler

        PUBWEAK HALL0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HALL0_Handler
        B HALL0_Handler

        PUBWEAK PWM2_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PWM2_Handler
        B PWM2_Handler

        PUBWEAK PWMBRK_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PWMBRK_Handler
        B PWMBRK_Handler

        PUBWEAK I2C0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C0_Handler
        B I2C0_Handler

        PUBWEAK CAN0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN0_Handler
        B CAN0_Handler

        PUBWEAK SPI1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI1_Handler
        B SPI1_Handler

        PUBWEAK RTC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC_Handler
        B RTC_Handler

        PUBWEAK PWM3_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PWM3_Handler
        B PWM3_Handler

        PUBWEAK TIMR2_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMR2_Handler
        B TIMR2_Handler

        PUBWEAK UART3_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART3_Handler
        B UART3_Handler

        PUBWEAK TIMR3_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMR3_Handler
        B TIMR3_Handler

        PUBWEAK ADC1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC1_Handler
        B ADC1_Handler

        PUBWEAK BOD_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BOD_Handler
        B BOD_Handler

        PUBWEAK CORDIC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
CORDIC_Handler
        B CORDIC_Handler

        PUBWEAK BTIMR1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BTIMR1_Handler
        B BTIMR1_Handler

        PUBWEAK PWM4_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PWM4_Handler
        B PWM4_Handler

        PUBWEAK HALL3_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HALL3_Handler
        B HALL3_Handler

        PUBWEAK BTIMR2_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BTIMR2_Handler
        B BTIMR2_Handler

        PUBWEAK I2C1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C1_Handler
        B I2C1_Handler

        PUBWEAK BTIMR3_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BTIMR3_Handler
        B BTIMR3_Handler

        PUBWEAK ACMP_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
ACMP_Handler
        B ACMP_Handler

        PUBWEAK XTALSTOP_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
XTALSTOP_Handler
        B XTALSTOP_Handler

        PUBWEAK FSPI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
FSPI_Handler
        B FSPI_Handler

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

        PUBWEAK GPIOD_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOD_Handler
        B GPIOD_Handler

        PUBWEAK GPIOM_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOM_Handler
        B GPIOM_Handler

        PUBWEAK GPION_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPION_Handler
        B GPION_Handler

        PUBWEAK GPIOA0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOA0_Handler
        B GPIOA0_Handler

        PUBWEAK GPIOA1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOA1_Handler
        B GPIOA1_Handler

        PUBWEAK GPIOA5_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOA5_Handler
        B GPIOA5_Handler

        PUBWEAK GPIOA6_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOA6_Handler
        B GPIOA6_Handler

        PUBWEAK GPIOA10_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOA10_Handler
        B GPIOA10_Handler

        PUBWEAK GPIOA11_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOA11_Handler
        B GPIOA11_Handler

        PUBWEAK GPIOA12_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOA12_Handler
        B GPIOA12_Handler

        PUBWEAK GPIOA13_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOA13_Handler
        B GPIOA13_Handler

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

        PUBWEAK GPIOD3_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOD3_Handler
        B GPIOD3_Handler

        PUBWEAK GPIOD4_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOD4_Handler
        B GPIOD4_Handler

        PUBWEAK GPIOD5_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOD5_Handler
        B GPIOD5_Handler

        PUBWEAK GPIOD6_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOD6_Handler
        B GPIOD6_Handler

        PUBWEAK GPIOD7_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOD7_Handler
        B GPIOD7_Handler

        PUBWEAK GPIOD8_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOD8_Handler
        B GPIOD8_Handler

        PUBWEAK GPIOC9_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOC9_Handler
        B GPIOC9_Handler

        PUBWEAK GPIOC10_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOC10_Handler
        B GPIOC10_Handler

        PUBWEAK GPIOC11_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOC11_Handler
        B GPIOC11_Handler

        PUBWEAK GPIOC12_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOC12_Handler
        B GPIOC12_Handler

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

        PUBWEAK DIV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DIV_Handler
        B DIV_Handler

        PUBWEAK LCD_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
LCD_Handler
        B LCD_Handler

        PUBWEAK GPIOE_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOE_Handler
        B GPIOE_Handler

        PUBWEAK JPEG_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
JPEG_Handler
        B JPEG_Handler

        PUBWEAK SDIO_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SDIO_Handler
        B SDIO_Handler

        PUBWEAK USB_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
USB_Handler
        B USB_Handler

        PUBWEAK CAN1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN1_Handler
        B CAN1_Handler

        PUBWEAK TIMR4_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMR4_Handler
        B TIMR4_Handler

        PUBWEAK BTIMR4_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BTIMR4_Handler
        B BTIMR4_Handler

        PUBWEAK BTIMR5_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BTIMR5_Handler
        B BTIMR5_Handler

        PUBWEAK BTIMR6_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BTIMR6_Handler
        B BTIMR6_Handler

        PUBWEAK BTIMR7_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BTIMR7_Handler
        B BTIMR7_Handler

        PUBWEAK BTIMR8_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BTIMR8_Handler
        B BTIMR8_Handler

        PUBWEAK BTIMR9_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BTIMR9_Handler
        B BTIMR9_Handler

        PUBWEAK BTIMR10_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BTIMR10_Handler
        B BTIMR10_Handler

        PUBWEAK BTIMR11_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BTIMR11_Handler
        B BTIMR11_Handler

        PUBWEAK DMA2D_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2D_Handler
        B DMA2D_Handler

        PUBWEAK QEI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
QEI_Handler
        B QEI_Handler

        END
