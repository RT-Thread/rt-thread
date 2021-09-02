
        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        PUBLIC  __vector_table

        DATA
        
__vector_table
        DCD     sfe(CSTACK)
		DCD     Reset_Handler             ; Reset Handler
		DCD     NMI_Handler               ; NMI Handler
		DCD     HardFault_Handler         ; Hard Fault Handler
		DCD     0                         ; Reserved
		DCD     0                         ; Reserved
		DCD     0                         ; Reserved
		DCD     0                         ; Reserved
		DCD     0                         ; Reserved
		DCD     0                         ; Reserved
		DCD     0                         ; Reserved
		DCD     SVC_Handler               ; SVCall Handler
		DCD     0                         ; Reserved
		DCD     0                         ; Reserved
		DCD     PendSV_Handler            ; PendSV Handler
		DCD     SysTick_Handler           ; SysTick Handler

		; External Interrupts
		DCD     WDT_IRQHandler            ; 0:  WWDT 
		DCD     SVD_IRQHandler            ; 1:  SVD     
		DCD     RTC_IRQHandler            ; 2:  RTC     
		DCD     FLASH_IRQHandler          ; 3:  FLASH    
		DCD     FDET_IRQHandler           ; 4:  LFDET    
		DCD     ADC_IRQHandler            ; 5:  ADC    
		DCD     DAC_IRQHandler            ; 6:  DAC
		DCD     SPI0_IRQHandler           ; 7:  SPI0     
		DCD     SPI1_IRQHandler           ; 8:  SPI1
		DCD     SPI2_IRQHandler           ; 9:  SPI2    
		DCD     UART0_IRQHandler          ; 10:  UART0    
		DCD     UART1_IRQHandler          ; 11:  UART1        
		DCD     UART3_IRQHandler          ; 12:  UART3    
		DCD     UART4_IRQHandler          ; 13:  UART4    
		DCD     UART5_IRQHandler          ; 14:  UART5        
		DCD     U7816_IRQHandler          ; 15:  U7816    
		DCD     LPUARTx_IRQHandler        ; 16:  LPUART   
		DCD     I2C_IRQHandler            ; 17:  I2C    
		DCD     CCL_IRQHandler            ; 18:  CCL  
		DCD     AES_IRQHandler            ; 19:  AES    
		DCD     LPTIM_IRQHandler          ; 20:  LPTIM    
		DCD     DMA_IRQHandler            ; 21:  DMA    
		DCD     WKUPx_IRQHandler          ; 22:  WKUP    
		DCD     LUT_IRQHandler            ; 23:  LUT   
		DCD     BSTIM_IRQHandler          ; 24:  BSTIM
		DCD     COMPx_IRQHandler          ; 25:  COMPx
		DCD     GPTIM0_1_IRQHandler       ; 26:  GPTIM0_1    
		DCD     GPTIM2_IRQHandler         ; 27:  GPTIM2    
		DCD     ATIM_IRQHandler           ; 28:  ATIM    
		DCD     VREF_IRQHandler           ; 29:  VREF    
		DCD     GPIO_IRQHandler           ; 30:  GPIO
		DCD     CAN_IRQHandler      	  ; 31:  CAN
__Vectors_End
                
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
        IMPORT  SystemInit
        LDR     R0, =SystemInit
        BLX     R0		
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
       
        
        PUBWEAK SVC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
        B SVC_Handler
        
        
        PUBWEAK PendSV_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler  
        B PendSV_Handler
        
        
        PUBWEAK SysTick_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
        B SysTick_Handler
        
        
        PUBWEAK WDT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WDT_IRQHandler
        B WDT_IRQHandler
        
                
        PUBWEAK SVD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SVD_IRQHandler
        B SVD_IRQHandler
        
                
        PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_IRQHandler
        B RTC_IRQHandler
        
                
        PUBWEAK FLASH_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FLASH_IRQHandler
        B FLASH_IRQHandler
        
                
        PUBWEAK FDET_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FDET_IRQHandler
        B FDET_IRQHandler
        
                
        PUBWEAK ADC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC_IRQHandler
        B ADC_IRQHandler
  
        PUBWEAK DAC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DAC_IRQHandler
        B DAC_IRQHandler
       
       
        PUBWEAK SPI0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI0_IRQHandler
        B SPI0_IRQHandler
        

        PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI1_IRQHandler
        B SPI1_IRQHandler
        
                                
        PUBWEAK SPI2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI2_IRQHandler
        B SPI2_IRQHandler
        
                
        PUBWEAK UART0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART0_IRQHandler
        B UART0_IRQHandler
        
                
        PUBWEAK UART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART1_IRQHandler
        B UART1_IRQHandler
        
                
        PUBWEAK UART3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART3_IRQHandler
        B UART3_IRQHandler
        
                
        PUBWEAK UART4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART4_IRQHandler
        B UART4_IRQHandler
        
                
        PUBWEAK UART5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART5_IRQHandler
        B UART5_IRQHandler
        
                 
        PUBWEAK U7816_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
U7816_IRQHandler
        B U7816_IRQHandler
        
                 
        PUBWEAK LPUARTx_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPUARTx_IRQHandler
        B LPUARTx_IRQHandler
        
                
        PUBWEAK I2C_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C_IRQHandler
        B I2C_IRQHandler
        
        PUBWEAK CCL_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CCL_IRQHandler
        B CCL_IRQHandler
        
                
        PUBWEAK AES_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
AES_IRQHandler
        B AES_IRQHandler
                  
                  
        PUBWEAK LPTIM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPTIM_IRQHandler
        B LPTIM_IRQHandler
                
                
        PUBWEAK DMA_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA_IRQHandler
        B DMA_IRQHandler
        
        
        PUBWEAK WKUPx_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WKUPx_IRQHandler
        B WKUPx_IRQHandler
        
        PUBWEAK LUT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LUT_IRQHandler
        B LUT_IRQHandler


        PUBWEAK BSTIM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
BSTIM_IRQHandler
        B BSTIM_IRQHandler 
      
      
        PUBWEAK COMPx_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
COMPx_IRQHandler
        B COMPx_IRQHandler


        PUBWEAK GPTIM0_1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GPTIM0_1_IRQHandler
        B GPTIM0_1_IRQHandler
        
                
        PUBWEAK GPTIM2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GPTIM2_IRQHandler
        B GPTIM2_IRQHandler
               
        
        PUBWEAK ATIM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ATIM_IRQHandler
        B ATIM_IRQHandler
         
         
        PUBWEAK VREF_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
VREF_IRQHandler
        B VREF_IRQHandler
        
        
         PUBWEAK GPIO_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GPIO_IRQHandler
        B GPIO_IRQHandler
        
        
         PUBWEAK CAN_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN_IRQHandler
        B CAN_IRQHandler
        END