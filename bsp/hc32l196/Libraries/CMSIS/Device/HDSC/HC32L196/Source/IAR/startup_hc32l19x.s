;*******************************************************************************
; Copyright (C) 2019, Huada Semiconductor Co.,Ltd All rights reserved.
;
; This software is owned and published by:
; Huada Semiconductor Co.,Ltd ("HDSC").
;
; BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
; BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
;
; This software contains source code for use with HDSC
; components. This software is licensed by HDSC to be adapted only
; for use in systems utilizing HDSC components. HDSC shall not be
; responsible for misuse or illegal use of this software for devices not
; supported herein. HDSC is providing this software "AS IS" and will
; not be responsible for issues arising from incorrect user implementation
; of the software.
;
; Disclaimer:
; HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
; REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
; ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
; WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
; WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
; WARRANTY OF NONINFRINGEMENT.
; HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
; NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
; LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
; LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
; INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
; INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
; SAVINGS OR PROFITS,
; EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
; YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
; INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
; FROM, THE SOFTWARE.
;
; This software may be replicated in part or whole for the licensed use,
; with the restriction that this Disclaimer and Copyright notice must be
; included with each copy of this software, whether used in part or whole,
; at all times.
;/
;/*****************************************************************************/
;/*  Startup for IAR                                                          */
;/*  Version     V1.0                                                         */
;/*  Date        2019-03-01                                                   */
;/*  Target-mcu  M0+ Device                                                   */
;/*****************************************************************************/


                MODULE  ?cstartup

                ;; Forward declaration of sections.
                SECTION CSTACK:DATA:NOROOT(3)

                EXTERN  __iar_program_start
                EXTERN  SystemInit
                PUBLIC  __vector_table
                
                SECTION .intvec:CODE:ROOT(8)
                DATA
__vector_table  
                DCD     sfe(CSTACK)               ; Top of Stack
                DCD     Reset_Handler             ; Reset
                DCD     NMI_Handler               ; NMI
                DCD     HardFault_Handler         ; Hard Fault
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV
                DCD     SysTick_Handler           ; SysTick

; Numbered IRQ handler vectors

; Note: renaming to device dependent ISR function names are done in

                DCD     PORTA_IRQHandler
                DCD     PORTB_IRQHandler
                DCD     PORTC_E_IRQHandler
                DCD     PORTD_F_IRQHandler
                DCD     DMAC_IRQHandler
                DCD     TIM3_IRQHandler
                DCD     UART0_2_IRQHandler
                DCD     UART1_3_IRQHandler
                DCD     LPUART0_IRQHandler
                DCD     LPUART1_IRQHandler
                DCD     SPI0_IRQHandler
                DCD     SPI1_IRQHandler
                DCD     I2C0_IRQHandler
                DCD     I2C1_IRQHandler
                DCD     TIM0_IRQHandler
                DCD     TIM1_IRQHandler
                DCD     TIM2_IRQHandler
                DCD     LPTIM0_1_IRQHandler
                DCD     TIM4_IRQHandler
                DCD     TIM5_IRQHandler
                DCD     TIM6_IRQHandler
                DCD     PCA_IRQHandler
                DCD     WDT_IRQHandler
                DCD     RTC_IRQHandler
                DCD     ADC_DAC_IRQHandler
                DCD     PCNT_IRQHandler
                DCD     VC0_IRQHandler
                DCD     VC1_2_IRQHandler
                DCD     LVD_IRQHandler
                DCD     LCD_IRQHandler
                DCD     FLASH_RAM_IRQHandler
                DCD     CLKTRIM_IRQHandler


                THUMB

                PUBWEAK Reset_Handler
                SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
                ;reset NVIC if in rom debug
                LDR     R0, =0x20000000
                LDR     R2, =0x0              ; vector offset
                cmp     PC, R0
                bls     ROMCODE
              
              ; ram code base address. 
                ADD     R2, R0,R2
ROMCODE
              ; reset Vector table address.
                LDR     R0, =0xE000ED08
                STR     R2, [R0]
                
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__iar_program_start
                BX      R0

                PUBWEAK NMI_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
NMI_Handler
                B       NMI_Handler

                PUBWEAK HardFault_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_Handler
                B       HardFault_Handler


                PUBWEAK SVC_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
                B       SVC_Handler

                PUBWEAK PendSV_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler
                B       PendSV_Handler

                PUBWEAK SysTick_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
                B       SysTick_Handler

                PUBWEAK PORTA_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
PORTA_IRQHandler
                B       PORTA_IRQHandler


                PUBWEAK PORTB_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
PORTB_IRQHandler
                B       PORTB_IRQHandler


                PUBWEAK PORTC_E_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
PORTC_E_IRQHandler
                B       PORTC_E_IRQHandler


                PUBWEAK PORTD_F_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
PORTD_F_IRQHandler
                B       PORTD_F_IRQHandler


                PUBWEAK DMAC_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
DMAC_IRQHandler
                B       DMAC_IRQHandler


                PUBWEAK TIM3_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
TIM3_IRQHandler
                B       TIM3_IRQHandler


                PUBWEAK UART0_2_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
UART0_2_IRQHandler
                B       UART0_2_IRQHandler


                PUBWEAK UART1_3_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
UART1_3_IRQHandler
                B       UART1_3_IRQHandler


                PUBWEAK LPUART0_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
LPUART0_IRQHandler
                B       LPUART0_IRQHandler


                PUBWEAK LPUART1_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
LPUART1_IRQHandler
                B       LPUART1_IRQHandler


                PUBWEAK SPI0_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
SPI0_IRQHandler
                B       SPI0_IRQHandler


                PUBWEAK SPI1_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
SPI1_IRQHandler
                B       SPI1_IRQHandler


                PUBWEAK I2C0_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
I2C0_IRQHandler
                B       I2C0_IRQHandler


                PUBWEAK I2C1_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_IRQHandler
                B       I2C1_IRQHandler


                PUBWEAK TIM0_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
TIM0_IRQHandler
                B       TIM0_IRQHandler


                PUBWEAK TIM1_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_IRQHandler
                B       TIM1_IRQHandler


                PUBWEAK TIM2_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
TIM2_IRQHandler
                B       TIM2_IRQHandler


                PUBWEAK LPTIM0_1_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
LPTIM0_1_IRQHandler
                B       LPTIM0_1_IRQHandler


                PUBWEAK TIM4_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
TIM4_IRQHandler
                B       TIM4_IRQHandler


                PUBWEAK TIM5_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
TIM5_IRQHandler
                B       TIM5_IRQHandler


                PUBWEAK TIM6_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
TIM6_IRQHandler
                B       TIM6_IRQHandler


                PUBWEAK PCA_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
PCA_IRQHandler
                B       PCA_IRQHandler


                PUBWEAK WDT_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
WDT_IRQHandler
                B       WDT_IRQHandler


                PUBWEAK RTC_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
RTC_IRQHandler
                B       RTC_IRQHandler


                PUBWEAK ADC_DAC_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
ADC_DAC_IRQHandler
                B       ADC_DAC_IRQHandler


                PUBWEAK PCNT_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
PCNT_IRQHandler
                B       PCNT_IRQHandler


                PUBWEAK VC0_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
VC0_IRQHandler
                B       VC0_IRQHandler


                PUBWEAK VC1_2_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
VC1_2_IRQHandler
                B       VC1_2_IRQHandler


                PUBWEAK LVD_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
LVD_IRQHandler
                B       LVD_IRQHandler


                PUBWEAK LCD_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
LCD_IRQHandler
                B       LCD_IRQHandler


                PUBWEAK FLASH_RAM_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
FLASH_RAM_IRQHandler
                B       FLASH_RAM_IRQHandler


                PUBWEAK CLKTRIM_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
CLKTRIM_IRQHandler
                B       CLKTRIM_IRQHandler



                
                
                END
