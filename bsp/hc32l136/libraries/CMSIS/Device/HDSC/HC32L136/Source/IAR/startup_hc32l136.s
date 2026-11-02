;*******************************************************************************
; Copyright (C) 2018, Huada Semiconductor Co.,Ltd All rights reserved.
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
;/*  Date        2018-04-15                                                   */
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
__vector_table  DCD     sfe(CSTACK)                 
                DCD     Reset_Handler
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
                DCD     0                         ; Debug Monitor
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV
                DCD     SysTick_Handler           ; SysTick

; Numbered IRQ handler vectors

; Note: renaming to device dependent ISR function names are done in
                DCD     IRQ000_Handler
                DCD     IRQ001_Handler
                DCD     IRQ002_Handler
                DCD     IRQ003_Handler
                DCD     IRQ004_Handler
                DCD     IRQ005_Handler
                DCD     IRQ006_Handler
                DCD     IRQ007_Handler
                DCD     IRQ008_Handler
                DCD     IRQ009_Handler
                DCD     IRQ010_Handler
                DCD     IRQ011_Handler
                DCD     IRQ012_Handler
                DCD     IRQ013_Handler
                DCD     IRQ014_Handler
                DCD     IRQ015_Handler
                DCD     IRQ016_Handler
                DCD     IRQ017_Handler
                DCD     IRQ018_Handler
                DCD     IRQ019_Handler
                DCD     IRQ020_Handler
                DCD     IRQ021_Handler
                DCD     IRQ022_Handler
                DCD     IRQ023_Handler
                DCD     IRQ024_Handler
                DCD     IRQ025_Handler
                DCD     IRQ026_Handler
                DCD     IRQ027_Handler
                DCD     IRQ028_Handler
                DCD     IRQ029_Handler
                DCD     IRQ030_Handler
                DCD     IRQ031_Handler

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


                PUBWEAK IRQ000_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ000_Handler
                B       IRQ000_Handler


                PUBWEAK IRQ001_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ001_Handler
                B       IRQ001_Handler


                PUBWEAK IRQ002_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ002_Handler
                B       IRQ002_Handler


                PUBWEAK IRQ003_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ003_Handler
                B       IRQ003_Handler


                PUBWEAK IRQ004_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ004_Handler
                B       IRQ004_Handler


                PUBWEAK IRQ005_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ005_Handler
                B       IRQ005_Handler


                PUBWEAK IRQ006_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ006_Handler
                B       IRQ006_Handler


                PUBWEAK IRQ007_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ007_Handler
                B       IRQ007_Handler


                PUBWEAK IRQ008_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ008_Handler
                B       IRQ008_Handler


                PUBWEAK IRQ009_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ009_Handler
                B       IRQ009_Handler


                PUBWEAK IRQ010_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ010_Handler
                B       IRQ010_Handler


                PUBWEAK IRQ011_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ011_Handler
                B       IRQ011_Handler


                PUBWEAK IRQ012_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ012_Handler
                B       IRQ012_Handler


                PUBWEAK IRQ013_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ013_Handler
                B       IRQ013_Handler


                PUBWEAK IRQ014_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ014_Handler
                B       IRQ014_Handler


                PUBWEAK IRQ015_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ015_Handler
                B       IRQ015_Handler


                PUBWEAK IRQ016_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ016_Handler
                B       IRQ016_Handler


                PUBWEAK IRQ017_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ017_Handler
                B       IRQ017_Handler


                PUBWEAK IRQ018_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ018_Handler
                B       IRQ018_Handler


                PUBWEAK IRQ019_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ019_Handler
                B       IRQ019_Handler


                PUBWEAK IRQ020_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ020_Handler
                B       IRQ020_Handler


                PUBWEAK IRQ021_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ021_Handler
                B       IRQ021_Handler


                PUBWEAK IRQ022_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ022_Handler
                B       IRQ022_Handler


                PUBWEAK IRQ023_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ023_Handler
                B       IRQ023_Handler


                PUBWEAK IRQ024_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ024_Handler
                B       IRQ024_Handler


                PUBWEAK IRQ025_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ025_Handler
                B       IRQ025_Handler


                PUBWEAK IRQ026_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ026_Handler
                B       IRQ026_Handler


                PUBWEAK IRQ027_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ027_Handler
                B       IRQ027_Handler


                PUBWEAK IRQ028_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ028_Handler
                B       IRQ028_Handler


                PUBWEAK IRQ029_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ029_Handler
                B       IRQ029_Handler


                PUBWEAK IRQ030_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ030_Handler
                B       IRQ030_Handler


                PUBWEAK IRQ031_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
IRQ031_Handler
                B       IRQ031_Handler

                END
