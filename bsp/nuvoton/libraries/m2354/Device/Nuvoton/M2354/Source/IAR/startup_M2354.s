/****************************************************************************//**
 * @file     startup_M2354.s
 * @version  V1.00
 * @brief    CMSIS Device Startup File
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2016-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    MODULE  ?cstartup

    ;; Forward declaration of sections.
    SECTION CSTACK:DATA:NOROOT(3) ;; 8 bytes alignment

    SECTION .intvec:CODE:NOROOT(2);; 4 bytes alignment

    EXTERN  SystemInit	
    EXTERN  __iar_program_start
    PUBLIC  __vector_table
    PUBLIC  g_pfnVectors

    DATA
g_pfnVectors    
__vector_table
    DCD     sfe(CSTACK)
    DCD     Reset_Handler

    DCD     NMI_Handler
    DCD     HardFault_Handler
    DCD     0
    DCD     0
    DCD     0
    DCD     0
    DCD     0
    DCD     0
    DCD     0
    DCD     SVC_Handler
    DCD     0
    DCD     0
    DCD     PendSV_Handler
    DCD     SysTick_Handler

    ; External Interrupts
                                                   ; maximum of 32 External Interrupts are possible
                DCD     BOD_IRQHandler		       ; 0  
                DCD     IRC_IRQHandler             ; 1  
                DCD     PWRWU_IRQHandler           ; 2  
                DCD     SRAM_IRQHandler            ; 3  
                DCD     CLKFAIL_IRQHandler         ; 4  
                DCD     DEFAULT_IRQHandler         ; 5  
                DCD     RTC_IRQHandler             ; 6  
                DCD     RTC_TAMPER_IRQHandler      ; 7  
                DCD     WDT_IRQHandler             ; 8  
                DCD     WWDT_IRQHandler            ; 9  
                DCD     EINT0_IRQHandler           ; 10 
                DCD     EINT1_IRQHandler           ; 11 
                DCD     EINT2_IRQHandler           ; 12 
                DCD     EINT3_IRQHandler           ; 13 
                DCD     EINT4_IRQHandler           ; 14 
                DCD     EINT5_IRQHandler           ; 15 
                DCD     GPA_IRQHandler             ; 16 
                DCD     GPB_IRQHandler             ; 17 
                DCD     GPC_IRQHandler             ; 18 
                DCD     GPD_IRQHandler             ; 19 
                DCD     GPE_IRQHandler             ; 20 
                DCD     GPF_IRQHandler             ; 21 
                DCD     QSPI0_IRQHandler           ; 22 
                DCD     SPI0_IRQHandler            ; 23 
                DCD     BRAKE0_IRQHandler          ; 24 
                DCD     EPWM0_P0_IRQHandler        ; 25 
                DCD     EPWM0_P1_IRQHandler        ; 26 
                DCD     EPWM0_P2_IRQHandler        ; 27 
                DCD     BRAKE1_IRQHandler          ; 28 
                DCD     EPWM1_P0_IRQHandler        ; 29 
                DCD     EPWM1_P1_IRQHandler        ; 30 
                DCD     EPWM1_P2_IRQHandler        ; 31 
                DCD     TMR0_IRQHandler            ; 32 
                DCD     TMR1_IRQHandler            ; 33 
                DCD     TMR2_IRQHandler            ; 34 
                DCD     TMR3_IRQHandler            ; 35 
                DCD     UART0_IRQHandler           ; 36 
                DCD     UART1_IRQHandler           ; 37 
                DCD     I2C0_IRQHandler            ; 38 
                DCD     I2C1_IRQHandler            ; 39 
                DCD     PDMA0_IRQHandler           ; 40 
                DCD     DAC_IRQHandler             ; 41 
                DCD     EADC0_IRQHandler           ; 42 
                DCD     EADC1_IRQHandler           ; 43 
                DCD     ACMP01_IRQHandler          ; 44 
                DCD     DEFAULT_IRQHandler         ; 45 
                DCD     EADC2_IRQHandler           ; 46 
                DCD     EADC3_IRQHandler           ; 47 
                DCD     UART2_IRQHandler           ; 48 
                DCD     UART3_IRQHandler           ; 49 
                DCD     DEFAULT_IRQHandler         ; 50 
                DCD     SPI1_IRQHandler            ; 51 
                DCD     SPI2_IRQHandler            ; 52 
                DCD     USBD_IRQHandler            ; 53 
                DCD     USBH_IRQHandler            ; 54 
                DCD     USBOTG_IRQHandler          ; 55 
                DCD     CAN0_IRQHandler            ; 56 
                DCD     DEFAULT_IRQHandler         ; 57 
                DCD     SC0_IRQHandler             ; 58 
                DCD     SC1_IRQHandler             ; 59 
                DCD     SC2_IRQHandler             ; 60 
                DCD     DEFAULT_IRQHandler         ; 61 
                DCD     SPI3_IRQHandler            ; 62 
                DCD     DEFAULT_IRQHandler         ; 63 
                DCD     SDH0_IRQHandler            ; 64 
                DCD     DEFAULT_IRQHandler         ; 65 
                DCD     DEFAULT_IRQHandler         ; 66 
                DCD     DEFAULT_IRQHandler         ; 67 
                DCD     I2S0_IRQHandler            ; 68 
                DCD     DEFAULT_IRQHandler         ; 69 
                DCD     OPA0_IRQHandler            ; 70 
                DCD     CRPT_IRQHandler            ; 71 
                DCD     GPG_IRQHandler             ; 72 
                DCD     EINT6_IRQHandler           ; 73 
                DCD     UART4_IRQHandler           ; 74 
                DCD     UART5_IRQHandler           ; 75 
                DCD     USCI0_IRQHandler           ; 76 
                DCD     USCI1_IRQHandler           ; 77 
                DCD     BPWM0_IRQHandler           ; 78 
                DCD     BPWM1_IRQHandler           ; 79 
                DCD     DEFAULT_IRQHandler         ; 80 
                DCD     DEFAULT_IRQHandler         ; 81 
                DCD     I2C2_IRQHandler            ; 82 
                DCD     DEFAULT_IRQHandler         ; 83 
                DCD     QEI0_IRQHandler            ; 84 
                DCD     QEI1_IRQHandler            ; 85 
                DCD     ECAP0_IRQHandler           ; 86 
                DCD     ECAP1_IRQHandler           ; 87 
                DCD     GPH_IRQHandler             ; 88 
                DCD     EINT7_IRQHandler           ; 89 
                DCD     SDH1_IRQHandler            ; 90 
                DCD     DEFAULT_IRQHandler         ; 91 
                DCD     DEFAULT_IRQHandler         ; 92 
                DCD     DEFAULT_IRQHandler         ; 93 
                DCD     DEFAULT_IRQHandler         ; 94 
                DCD     DEFAULT_IRQHandler         ; 95 
                DCD     DEFAULT_IRQHandler         ; 96 
                DCD     DEFAULT_IRQHandler         ; 97 
                DCD     PDMA1_IRQHandler           ; 98 
                DCD     SCU_IRQHandler             ; 99 
                DCD     LCD_IRQHandler             ; 100
                DCD     TRNG_IRQHandler            ; 101
                DCD     DEFAULT_IRQHandler         ; 102 
                DCD     DEFAULT_IRQHandler         ; 103 
                DCD     DEFAULT_IRQHandler         ; 104 
                DCD     DEFAULT_IRQHandler         ; 105 
                DCD     DEFAULT_IRQHandler         ; 106 
                DCD     DEFAULT_IRQHandler         ; 107 
                DCD     DEFAULT_IRQHandler         ; 108     
                DCD     KS_IRQHandler              ; 109     
                DCD     TAMPER_IRQHandler          ; 110     
                DCD     EWDT_IRQHandler            ; 111     
                DCD     EWWDT_IRQHandler           ; 112     
                DCD     NS_ISP_IRQHandler          ; 113
                DCD     TMR4_IRQHandler            ; 114 
                DCD     TMR5_IRQHandler            ; 115 
                 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
    THUMB
    PUBWEAK Reset_Handler   
    SECTION .text:CODE:NOROOT:REORDER(2)       ; 4 bytes alignment
Reset_Handler

      ; Check SecureWorld
      MOV     R0, R15
      LSLS    R0, R0, #3
      BMI.N   GotoSystemInit

      ; Unlock Register
      LDR     R0, =0x40000100
      LDR     R1, =0x59
      STR     R1, [R0]
      LDR     R1, =0x16
      STR     R1, [R0]
      LDR     R1, =0x88
      STR     R1, [R0]

      ; power gating
      ; M32(0x400001f4) = 0xfffffffful;
      LDR     R0, =0x400001f4
      LDR     R1, =0xffffffff
      STR     R1, [R0]

      ; M32(0x400000dC) = 0ul;
      LDR     R0, =0x400000dC
      LDR     R1, =0x0
      STR     R1, [R0]

      ; Enable GPIO clks, SRAM clks, Trace clk
      ; CLK->AHBCLK |= (0xffful << 20) | (1ul << 14);

      LDR     R0, =0x40000200   ; R0 = Clock Controller Register Base Address
      LDR     R1, [R0,#0x4]     ; R1 = 0x40000204  (AHBCLK)
    
      LDR     R2, =0xfff02000

      ORRS    R1, R1, R2        ; (0xffful << 20) | (1ul << 14); 
      STR     R1, [R0,#0x4]     ; CLK->AHBCLK |= (0xffful << 20) | (1ul << 14); ;

GotoSystemInit:
      LDR      R0, =SystemInit
      BLX      R0

      ; Lock register
      LDR     R0, =0x40000100
      MOVS    R1, #0
      STR     R1, [R0]

      LDR      R0, =__iar_program_start
      BX       R0

          PUBWEAK HardFault_Handler
          PUBWEAK NMI_Handler       
          PUBWEAK SVC_Handler       
          PUBWEAK PendSV_Handler    
          PUBWEAK SysTick_Handler   

          PUBWEAK  BOD_IRQHandler	      ; 0  
          PUBWEAK  IRC_IRQHandler             ; 1  
          PUBWEAK  PWRWU_IRQHandler           ; 2  
          PUBWEAK  SRAM_IRQHandler            ; 3  
          PUBWEAK  CLKFAIL_IRQHandler         ; 4  
         ;PUBWEAK  0                          ; 5  
          PUBWEAK  RTC_IRQHandler             ; 6  
          PUBWEAK  RTC_TAMPER_IRQHandler      ; 7  
          PUBWEAK  WDT_IRQHandler             ; 8  
          PUBWEAK  WWDT_IRQHandler            ; 9  
          PUBWEAK  EINT0_IRQHandler           ; 10 
          PUBWEAK  EINT1_IRQHandler           ; 11 
          PUBWEAK  EINT2_IRQHandler           ; 12 
          PUBWEAK  EINT3_IRQHandler           ; 13 
          PUBWEAK  EINT4_IRQHandler           ; 14 
          PUBWEAK  EINT5_IRQHandler           ; 15 
          PUBWEAK  GPA_IRQHandler             ; 16 
          PUBWEAK  GPB_IRQHandler             ; 17 
          PUBWEAK  GPC_IRQHandler             ; 18 
          PUBWEAK  GPD_IRQHandler             ; 19 
          PUBWEAK  GPE_IRQHandler             ; 20 
          PUBWEAK  GPF_IRQHandler             ; 21 
          PUBWEAK  QSPI0_IRQHandler           ; 22 
          PUBWEAK  SPI0_IRQHandler            ; 23 
          PUBWEAK  BRAKE0_IRQHandler          ; 24 
          PUBWEAK  EPWM0_P0_IRQHandler        ; 25 
          PUBWEAK  EPWM0_P1_IRQHandler        ; 26 
          PUBWEAK  EPWM0_P2_IRQHandler        ; 27 
          PUBWEAK  BRAKE1_IRQHandler          ; 28 
          PUBWEAK  EPWM1_P0_IRQHandler        ; 29 
          PUBWEAK  EPWM1_P1_IRQHandler        ; 30 
          PUBWEAK  EPWM1_P2_IRQHandler        ; 31 
          PUBWEAK  TMR0_IRQHandler            ; 32 
          PUBWEAK  TMR1_IRQHandler            ; 33 
          PUBWEAK  TMR2_IRQHandler            ; 34 
          PUBWEAK  TMR3_IRQHandler            ; 35 
          PUBWEAK  UART0_IRQHandler           ; 36 
          PUBWEAK  UART1_IRQHandler           ; 37 
          PUBWEAK  I2C0_IRQHandler            ; 38 
          PUBWEAK  I2C1_IRQHandler            ; 39 
          PUBWEAK  PDMA0_IRQHandler           ; 40 
          PUBWEAK  DAC_IRQHandler             ; 41 
          PUBWEAK  EADC0_IRQHandler           ; 42 
          PUBWEAK  EADC1_IRQHandler           ; 43 
          PUBWEAK  ACMP01_IRQHandler          ; 44 
         ;PUBWEAK  0                          ; 45 
          PUBWEAK  EADC2_IRQHandler           ; 46 
          PUBWEAK  EADC3_IRQHandler           ; 47 
          PUBWEAK  UART2_IRQHandler           ; 48 
          PUBWEAK  UART3_IRQHandler           ; 49 
         ;PUBWEAK  0                          ; 50 
          PUBWEAK  SPI1_IRQHandler            ; 51 
          PUBWEAK  SPI2_IRQHandler            ; 52 
          PUBWEAK  USBD_IRQHandler            ; 53 
          PUBWEAK  USBH_IRQHandler            ; 54 
          PUBWEAK  USBOTG_IRQHandler          ; 55 
          PUBWEAK  CAN0_IRQHandler            ; 56 
          PUBWEAK  CAN1_IRQHandler            ; 57 
          PUBWEAK  SC0_IRQHandler             ; 58 
          PUBWEAK  SC1_IRQHandler             ; 59 
          PUBWEAK  SC2_IRQHandler             ; 60 
          PUBWEAK  SC3_IRQHandler             ; 61 
          PUBWEAK  SPI3_IRQHandler            ; 62 
         ;PUBWEAK  0                          ; 63 
          PUBWEAK  SDH0_IRQHandler            ; 64 
         ;PUBWEAK  0                          ; 65 
         ;PUBWEAK  0                          ; 66 
         ;PUBWEAK  0                          ; 67 
          PUBWEAK  I2S0_IRQHandler            ; 68 
         ;PUBWEAK  0                          ; 69 
          PUBWEAK  OPA0_IRQHandler            ; 70 
          PUBWEAK  CRPT_IRQHandler            ; 71 
          PUBWEAK  GPG_IRQHandler             ; 72 
          PUBWEAK  EINT6_IRQHandler           ; 73 
          PUBWEAK  UART4_IRQHandler           ; 74 
          PUBWEAK  UART5_IRQHandler           ; 75 
          PUBWEAK  USCI0_IRQHandler           ; 76 
          PUBWEAK  USCI1_IRQHandler           ; 77 
          PUBWEAK  BPWM0_IRQHandler           ; 78 
          PUBWEAK  BPWM1_IRQHandler           ; 79 
         ;PUBWEAK  0                          ; 80 
         ;PUBWEAK  0                          ; 81 
          PUBWEAK  I2C2_IRQHandler            ; 82 
         ;PUBWEAK  0                          ; 83 
          PUBWEAK  QEI0_IRQHandler            ; 84 
          PUBWEAK  QEI1_IRQHandler            ; 85 
          PUBWEAK  ECAP0_IRQHandler           ; 86 
          PUBWEAK  ECAP1_IRQHandler           ; 87 
          PUBWEAK  GPH_IRQHandler             ; 88 
          PUBWEAK  EINT7_IRQHandler           ; 89 
          PUBWEAK  SDH1_IRQHandler            ; 90 
         ;PUBWEAK  0                          ; 91 
         ;PUBWEAK  USBH_IRQHandler            ; 92 
         ;PUBWEAK  0                          ; 93 
         ;PUBWEAK  0                          ; 94 
         ;PUBWEAK  0                          ; 95 
         ;PUBWEAK  0                          ; 96 
         ;PUBWEAK  0                          ; 97 
          PUBWEAK  PDMA1_IRQHandler           ; 98 
          PUBWEAK  SCU_IRQHandler             ; 99 
          PUBWEAK  LCD_IRQHandler             ; 100
          PUBWEAK  TRNG_IRQHandler            ; 101
          ;PUBWEAK  0         ; 102 
          ;PUBWEAK  0         ; 103 
          ;PUBWEAK  0         ; 104 
          ;PUBWEAK  0         ; 105 
          ;PUBWEAK  0         ; 106 
          ;PUBWEAK  0         ; 107 
          ;PUBWEAK  0         ; 108     
          PUBWEAK  KS_IRQHandler              ; 109     
          PUBWEAK  TAMPER_IRQHandler          ; 110     
          PUBWEAK  EWDT_IRQHandler            ; 111     
          PUBWEAK  EWWDT_IRQHandler           ; 112     
          PUBWEAK  NS_ISP_IRQHandler          ; 113                         
          PUBWEAK  TMR4_IRQHandler            ; 114 
          PUBWEAK  TMR5_IRQHandler            ; 115 
		
          PUBWEAK	DEFAULT_IRQHandler		                                                

    SECTION .text:CODE:NOROOT:REORDER(2)

HardFault_Handler
NMI_Handler       
SVC_Handler       
PendSV_Handler    
SysTick_Handler   

BOD_IRQHandler		       ; 0  
IRC_IRQHandler             ; 1  
PWRWU_IRQHandler           ; 2  
SRAM_IRQHandler            ; 3  
CLKFAIL_IRQHandler         ; 4  
;0                          ; 5  
RTC_IRQHandler             ; 6  
RTC_TAMPER_IRQHandler      ; 7  
WDT_IRQHandler             ; 8  
WWDT_IRQHandler            ; 9  
EINT0_IRQHandler           ; 10 
EINT1_IRQHandler           ; 11 
EINT2_IRQHandler           ; 12 
EINT3_IRQHandler           ; 13 
EINT4_IRQHandler           ; 14 
EINT5_IRQHandler           ; 15 
GPA_IRQHandler             ; 16 
GPB_IRQHandler             ; 17 
GPC_IRQHandler             ; 18 
GPD_IRQHandler             ; 19 
GPE_IRQHandler             ; 20 
GPF_IRQHandler             ; 21 
QSPI0_IRQHandler           ; 22 
SPI0_IRQHandler            ; 23 
BRAKE0_IRQHandler          ; 24 
EPWM0_P0_IRQHandler        ; 25 
EPWM0_P1_IRQHandler        ; 26 
EPWM0_P2_IRQHandler        ; 27 
BRAKE1_IRQHandler          ; 28 
EPWM1_P0_IRQHandler        ; 29 
EPWM1_P1_IRQHandler        ; 30 
EPWM1_P2_IRQHandler        ; 31 
TMR0_IRQHandler            ; 32 
TMR1_IRQHandler            ; 33 
TMR2_IRQHandler            ; 34 
TMR3_IRQHandler            ; 35 
UART0_IRQHandler           ; 36 
UART1_IRQHandler           ; 37 
I2C0_IRQHandler            ; 38 
I2C1_IRQHandler            ; 39 
PDMA0_IRQHandler           ; 40 
DAC_IRQHandler             ; 41 
EADC0_IRQHandler           ; 42 
EADC1_IRQHandler           ; 43 
ACMP01_IRQHandler          ; 44 
;0                          ; 45 
EADC2_IRQHandler           ; 46 
EADC3_IRQHandler           ; 47 
UART2_IRQHandler           ; 48 
UART3_IRQHandler           ; 49 
;0                          ; 50 
SPI1_IRQHandler            ; 51 
SPI2_IRQHandler            ; 52 
USBD_IRQHandler            ; 53 
USBH_IRQHandler            ; 54 
USBOTG_IRQHandler          ; 55 
CAN0_IRQHandler            ; 56 
CAN1_IRQHandler            ; 57 
SC0_IRQHandler             ; 58 
SC1_IRQHandler             ; 59 
SC2_IRQHandler             ; 60 
SC3_IRQHandler             ; 61 
SPI3_IRQHandler            ; 62 
;0                          ; 63 
SDH0_IRQHandler            ; 64 
;0                          ; 65 
;0                          ; 66 
;0                          ; 67 
I2S0_IRQHandler            ; 68 
;0                          ; 69 
OPA0_IRQHandler            ; 70 
CRPT_IRQHandler            ; 71 
GPG_IRQHandler             ; 72 
EINT6_IRQHandler           ; 73 
UART4_IRQHandler           ; 74 
UART5_IRQHandler           ; 75 
USCI0_IRQHandler           ; 76 
USCI1_IRQHandler           ; 77 
BPWM0_IRQHandler           ; 78 
BPWM1_IRQHandler           ; 79 
;0                          ; 80 
;0                          ; 81 
I2C2_IRQHandler            ; 82 
;0                          ; 83 
QEI0_IRQHandler            ; 84 
QEI1_IRQHandler            ; 85 
ECAP0_IRQHandler           ; 86 
ECAP1_IRQHandler           ; 87 
GPH_IRQHandler             ; 88 
EINT7_IRQHandler           ; 89 
SDH1_IRQHandler            ; 90 
;0                          ; 91 
;USBH_IRQHandler            ; 92 
;0                          ; 93 
;0                          ; 94 
;0                          ; 95 
;0                          ; 96 
;0                          ; 97 
PDMA1_IRQHandler           ; 98 
SCU_IRQHandler             ; 99 
LCD_IRQHandler             ; 100
TRNG_IRQHandler            ; 101
;0                          ; 102 
;0                          ; 103 
;0                          ; 104 
;0                          ; 105 
;0                          ; 106
;0                          ; 107 
;0                          ; 108 
KS_IRQHandler               ; 109     
TAMPER_IRQHandler           ; 110     
EWDT_IRQHandler             ; 111     
EWWDT_IRQHandler            ; 112     
NS_ISP_IRQHandler           ; 113    
TMR4_IRQHandler             ; 114 
TMR5_IRQHandler             ; 115 
DEFAULT_IRQHandler
    B DEFAULT_IRQHandler         


;void SH_ICE(void)
    PUBLIC    SH_ICE
SH_ICE    
    CMP   R2,#0
    BEQ   SH_End
    STR   R0,[R2]   ; Save the return value to *pn32Out_R0

;void SH_End(void)
    PUBLIC    SH_End
SH_End
    MOVS   R0,#1    ; Set return value to 1
    BX     lr       ; Return


;int32_t SH_DoCommand(int32_t n32In_R0, int32_t n32In_R1, int32_t *pn32Out_R0)
    PUBLIC    SH_DoCommand
SH_DoCommand
    BKPT   0xAB             ; This instruction will cause ICE trap or system HardFault
    B      SH_ICE
SH_HardFault                ; Captured by HardFault
    MOVS   R0,#0            ; Set return value to 0
    BX     lr               ; Return
    
    
    PUBLIC    __PC
__PC          
        MOV     r0, lr
        BLX     lr
            
    END

