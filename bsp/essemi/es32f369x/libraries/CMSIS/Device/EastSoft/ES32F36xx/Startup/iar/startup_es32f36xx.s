;*******************************************************************************
; file       : startup_es32f36xx.s
; description: es32f36xx Device Startup File
; author     : AE Team
; data       : 04 Jul 2019
; Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
;*******************************************************************************

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)
        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)				;0,  load top of stack
                DCD     RESET_Handler                   ;1,  reset handler
                DCD     NMI_Handler                     ;2,  nmi handler
                DCD     HardFault_Handler               ;3,  hard fault handler
                DCD     MemManage_Handler               ;4,  MPU Fault Handler
                DCD     BusFault_Handler                ;5,  Bus Fault Handler
                DCD     UsageFault_Handler              ;6,  Usage Fault Handler
                DCD     0                               ;7,  Reserved
                DCD     0                               ;8,  Reserved
                DCD     0                               ;9,  Reserved
                DCD     0                               ;10, Reserved
                DCD     SVC_Handler                     ;11, svcall handler
                DCD     DebugMon_Handler                ;12, Debug Monitor Handler
                DCD     0                               ;13, Reserved
                DCD     PendSV_Handler                  ;14, pendsv handler
                DCD     SysTick_Handler                 ;15, systick handler
                DCD     WWDG_Handler                    ;16, irq0    WWDG handler
                DCD     IWDG_Handler                    ;17, irq1    IWDG handler
                DCD     LVD_Handler                     ;18, irq2    LVD handler
                DCD     RTC_Handler                     ;19, irq3    RTC handler
                DCD     0                               ;20, irq4    Reserved
                DCD     0                               ;21, irq5    Reserved
                DCD     CMU_Handler                     ;22, irq6    CMU handler
                DCD     ADC0_Handler                    ;23, irq7    ADC0 handler
                DCD     CAN0_TX_Handler                 ;24, irq8    CAN0_TX handler
                DCD     CAN0_RX0_Handler                ;25, irq9    CAN0_RX0 handler
                DCD     CAN0_RX1_Handler                ;26, irq10   CAN0_RX1 handler
                DCD     CAN0_EXCEPTION_Handler          ;27, irq11   CAN0_EXCEPTION handler
                DCD     AD16C4T0_BRK_Handler            ;28, irq12   AD16C4T0_BRK handler
                DCD     AD16C4T0_UP_Handler             ;29, irq13   AD16C4T0_UP handler
                DCD     AD16C4T0_TRIG_COM_Handler       ;30, irq14   AD16C4T0_TRIG_COM handler
                DCD     AD16C4T0_CC_Handler             ;31, irq15   AD16C4T0_CC handler
                DCD     AD16C4T1_BRK_Handler            ;32, irq16   AD16C4T1_BRK handler
                DCD     AD16C4T1_UP_Handler             ;33, irq17   AD16C4T1_UP handler
                DCD     AD16C4T1_TRIG_COM_Handler       ;34, irq18   AD16C4T1_TRIG_COM handler
                DCD     AD16C4T1_CC_Handler             ;35, irq19   AD16C4T1_CC handler
                DCD     GP32C4T0_Handler                ;36, irq20   GP32C4T0 handler
                DCD     GP32C4T1_Handler                ;37, irq21   GP32C4T1 handler
                DCD     BS16T0_Handler                  ;38, irq22   BS16T0 handler
                DCD     BS16T1_Handler                  ;39, irq23   BS16T1 handler
                DCD     GP16C4T0_Handler                ;40, irq24   GP16C4T0 handler
                DCD     GP16C4T1_Handler                ;41, irq25   GP16C4T1 handler
                DCD     0                               ;42, irq26   Reserved
                DCD     DAC0_CH0_Handler                ;43, irq27   DAC0_CH0 handler
                DCD     I2C0_EV_Handler                 ;44, irq28   I2C0_EV handler
                DCD     I2C0_ERR_Handler                ;45, irq29   I2C0_ERR handler
                DCD     I2C1_EV_Handler                 ;46, irq30   I2C1_EV handler
                DCD     I2C1_ERR_Handler                ;47, irq31   I2C1_ERR handler
                DCD     SPI0_I2S0_Handler               ;48, irq32   SPI0_I2S0 handler
                DCD     SPI1_I2S1_Handler               ;49, irq33   SPI1_I2S1 handler
                DCD     UART0_Handler                   ;50, irq34   UART0 handler
                DCD     UART1_Handler                   ;51, irq35   UART1 handler
                DCD     UART2_Handler                   ;52, irq36   UART2 handler
                DCD     UART3_Handler                   ;53, irq37   UART3 handler
                DCD     UART4_Handler                   ;54, irq38   UART4 handler
                DCD     UART5_Handler                   ;55, irq39   UART5 handler
                DCD     0                               ;56, irq40   Reserved
                DCD     0                               ;57, irq41   Reserved
                DCD     CRYPT_Handler                   ;58, irq42   CRYPT handler
                DCD     ACMP0_Handler                   ;59, irq43   ACMP0 handler
                DCD     ACMP1_Handler                   ;60, irq44   ACMP1 handler
                DCD     SPI2_I2S2_Handler               ;61, irq45   SPI2_I2S2 handler
                DCD     0                               ;62, irq46   Reserved
                DCD     EBI_Handler                     ;63, irq47   EBI handler
                DCD     TRNG_Handler                    ;64, irq48   TRNG handler
                DCD     TSENSE_Handler                  ;65, irq49   TSENSE handler
                DCD     EXTI0_Handler                   ;66, irq50   EXTI0 handler
                DCD     EXTI1_Handler                   ;67, irq51   EXTI1 handler
                DCD     EXTI2_Handler                   ;68, irq52   EXTI2 handler
                DCD     EXTI3_Handler                   ;69, irq53   EXTI3 handler
                DCD     EXTI4_Handler                   ;70, irq54   EXTI4 handler
                DCD     EXTI5_Handler                   ;71, irq55   EXTI5 handler
                DCD     EXTI6_Handler                   ;72, irq56   EXTI6 handler
                DCD     EXTI7_Handler                   ;73, irq57   EXTI7 handler
                DCD     EXTI8_Handler                   ;74, irq58   EXTI8 handler
                DCD     EXTI9_Handler                   ;75, irq59   EXTI9 handler
                DCD     EXTI10_Handler                  ;76, irq60   EXTI10 handler
                DCD     EXTI11_Handler                  ;77, irq61   EXTI11 handler
                DCD     EXTI12_Handler                  ;78, irq62   EXTI12 handler
                DCD     EXTI13_Handler                  ;79, irq63   EXTI13 handler
                DCD     EXTI14_Handler                  ;80, irq64   EXTI14 handler
                DCD     EXTI15_Handler                  ;81, irq65   EXTI15 handler
                DCD     DMA_Handler                     ;82, irq66   DMA handler
                DCD     ADC1_Handler                    ;83, irq67   ADC1 handler
                DCD     DAC0_CH1_Handler                ;84, irq68   DAC0_CH1 handler
                DCD     QSPI_Handler                    ;85, irq69   QSPI handler
                DCD     USB_INT_Handler                 ;86, irq70   USB_INT handler
                DCD     USB_DMA_Handler                 ;87, irq71   USB_DMA handler
                DCD     ACMP2_Handler                   ;88, irq72   ACMP2 handler
        
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK RESET_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
RESET_Handler
        LDR     R0, =__iar_program_start
        BX      R0
        
        PUBWEAK NMI_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
MemManage_Handler
        B MemManage_Handler	
	
        PUBWEAK BusFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
BusFault_Handler
        B BusFault_Handler	
	
        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
UsageFault_Handler
        B UsageFault_Handler	

        PUBWEAK SVC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
        B SVC_Handler
		
	PUBWEAK DebugMon_Handler
	SECTION .text:CODE:NOROOT:REORDER(1)
DebugMon_Handler
	B DebugMon_Handler

    	PUBWEAK PendSV_Handler
    	SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler
    	B PendSV_Handler

   	PUBWEAK SysTick_Handler
    	SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
    	B SysTick_Handler

        PUBWEAK WWDG_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
WWDG_Handler
        B WWDG_Handler

        PUBWEAK IWDG_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
IWDG_Handler
        B IWDG_Handler

        PUBWEAK LVD_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
LVD_Handler
        B LVD_Handler

        PUBWEAK RTC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_Handler
        B RTC_Handler

        PUBWEAK CMU_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
CMU_Handler
        B CMU_Handler

        PUBWEAK ADC0_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC0_Handler
        B ADC0_Handler

        PUBWEAK CAN0_TX_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_TX_Handler
        B CAN0_TX_Handler

        PUBWEAK CAN0_RX0_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_RX0_Handler
        B CAN0_RX0_Handler

        PUBWEAK CAN0_RX1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_RX1_Handler
        B CAN0_RX1_Handler

        PUBWEAK CAN0_EXCEPTION_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_EXCEPTION_Handler
        B CAN0_EXCEPTION_Handler

        PUBWEAK AD16C4T0_BRK_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
AD16C4T0_BRK_Handler
        B AD16C4T0_BRK_Handler

        PUBWEAK AD16C4T0_UP_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
AD16C4T0_UP_Handler
        B AD16C4T0_UP_Handler

        PUBWEAK AD16C4T0_TRIG_COM_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
AD16C4T0_TRIG_COM_Handler
        B AD16C4T0_TRIG_COM_Handler

        PUBWEAK AD16C4T0_CC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
AD16C4T0_CC_Handler
        B AD16C4T0_CC_Handler

        PUBWEAK AD16C4T1_BRK_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
AD16C4T1_BRK_Handler
        B AD16C4T1_BRK_Handler

        PUBWEAK AD16C4T1_UP_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
AD16C4T1_UP_Handler
        B AD16C4T1_UP_Handler

        PUBWEAK AD16C4T1_TRIG_COM_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
AD16C4T1_TRIG_COM_Handler
        B AD16C4T1_TRIG_COM_Handler

        PUBWEAK AD16C4T1_CC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
AD16C4T1_CC_Handler
        B AD16C4T1_CC_Handler

        PUBWEAK GP32C4T0_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP32C4T0_Handler
        B GP32C4T0_Handler

        PUBWEAK GP32C4T1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP32C4T1_Handler
        B GP32C4T1_Handler

        PUBWEAK BS16T0_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
BS16T0_Handler
        B BS16T0_Handler

        PUBWEAK BS16T1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
BS16T1_Handler
        B BS16T1_Handler

        PUBWEAK GP16C4T0_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP16C4T0_Handler
        B GP16C4T0_Handler

        PUBWEAK GP16C4T1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP16C4T1_Handler
        B GP16C4T1_Handler

        PUBWEAK DAC0_CH0_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DAC0_CH0_Handler
        B DAC0_CH0_Handler

        PUBWEAK I2C0_EV_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C0_EV_Handler
        B I2C0_EV_Handler

        PUBWEAK I2C0_ERR_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C0_ERR_Handler
        B I2C0_ERR_Handler

        PUBWEAK I2C1_EV_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_EV_Handler
        B I2C1_EV_Handler

        PUBWEAK I2C1_ERR_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_ERR_Handler
        B I2C1_ERR_Handler

        PUBWEAK SPI0_I2S0_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI0_I2S0_Handler
        B SPI0_I2S0_Handler

        PUBWEAK SPI1_I2S1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI1_I2S1_Handler
        B SPI1_I2S1_Handler

        PUBWEAK UART0_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART0_Handler
        B UART0_Handler

        PUBWEAK UART1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART1_Handler
        B UART1_Handler

        PUBWEAK UART2_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART2_Handler
        B UART2_Handler

        PUBWEAK UART3_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART3_Handler
        B UART3_Handler

        PUBWEAK UART4_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART4_Handler
        B UART4_Handler

        PUBWEAK UART5_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART5_Handler
        B UART5_Handler

        PUBWEAK CRYPT_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
CRYPT_Handler
        B CRYPT_Handler

        PUBWEAK ACMP0_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
ACMP0_Handler
        B ACMP0_Handler

        PUBWEAK ACMP1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
ACMP1_Handler
        B ACMP1_Handler

        PUBWEAK SPI2_I2S2_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI2_I2S2_Handler
        B SPI2_I2S2_Handler

        PUBWEAK EBI_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EBI_Handler
        B EBI_Handler

        PUBWEAK TRNG_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
TRNG_Handler
        B TRNG_Handler

        PUBWEAK TSENSE_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
TSENSE_Handler
        B TSENSE_Handler

        PUBWEAK EXTI0_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI0_Handler
        B EXTI0_Handler

        PUBWEAK EXTI1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI1_Handler
        B EXTI1_Handler

        PUBWEAK EXTI2_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_Handler
        B EXTI2_Handler

        PUBWEAK EXTI3_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI3_Handler
        B EXTI3_Handler

        PUBWEAK EXTI4_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI4_Handler
        B EXTI4_Handler

        PUBWEAK EXTI5_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI5_Handler
        B EXTI5_Handler

        PUBWEAK EXTI6_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI6_Handler
        B EXTI6_Handler

        PUBWEAK EXTI7_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI7_Handler
        B EXTI7_Handler

        PUBWEAK EXTI8_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI8_Handler
        B EXTI8_Handler

        PUBWEAK EXTI9_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI9_Handler
        B EXTI9_Handler

        PUBWEAK EXTI10_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI10_Handler
        B EXTI10_Handler

        PUBWEAK EXTI11_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI11_Handler
        B EXTI11_Handler

        PUBWEAK EXTI12_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI12_Handler
        B EXTI12_Handler

        PUBWEAK EXTI13_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI13_Handler
        B EXTI13_Handler

        PUBWEAK EXTI14_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI14_Handler
        B EXTI14_Handler

        PUBWEAK EXTI15_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI15_Handler
        B EXTI15_Handler

        PUBWEAK DMA_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA_Handler
        B DMA_Handler

        PUBWEAK ADC1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC1_Handler
        B ADC1_Handler

        PUBWEAK DAC0_CH1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DAC0_CH1_Handler
        B DAC0_CH1_Handler

        PUBWEAK QSPI_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
QSPI_Handler
        B QSPI_Handler

        PUBWEAK USB_INT_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
USB_INT_Handler
        B USB_INT_Handler

        PUBWEAK USB_DMA_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
USB_DMA_Handler
        B USB_DMA_Handler

        PUBWEAK ACMP2_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
ACMP2_Handler
        B ACMP2_Handler

        END
