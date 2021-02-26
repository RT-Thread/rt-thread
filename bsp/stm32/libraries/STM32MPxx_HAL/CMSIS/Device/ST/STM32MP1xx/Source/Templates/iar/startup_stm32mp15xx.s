;******************************************************************************
;* File Name          : startup_stm32mp15xx.s
;* Author             : MCD Application Team
;* Description        : STM32MP15xx devices vector table for EWARM toolchain.
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == __iar_program_start,
;*                      - Set the vector table entries with the exceptions ISR 
;*                        address
;*                      - Branches to main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the CortexM4 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;******************************************************************************
;* @attention
;*
;* <h2><center>&copy; Copyright (c) 2019 STMicroelectronics. 
;* All rights reserved.</center></h2>
;*
;* This software component is licensed by ST under BSD 3-Clause license,
;* the "License"; You may not use this file except in compliance with the 
;* License. You may obtain a copy of the License at:
;*                        opensource.org/licenses/BSD-3-Clause
;*
;*******************************************************************************

//#define __DATA_IN_ExtSRAM 		 /* When External SRAM is used */ 
#ifdef __DATA_IN_ExtSRAM 
__initial_spTop EQU    0x20000400 		  ; stack used for SystemInit & SystemInit_ExtMemCtl 
#endif /*__DATA_IN_ExtSRAM*/  
	   MODULE  ?cstartup 

	  ;; Forward declaration of sections. 
	  SECTION CSTACK:DATA:NOROOT(3) 

	  SECTION .intvec:CODE:NOROOT(2)


	  EXTERN  __iar_program_start 
	  EXTERN  SystemInit 
	  PUBLIC  __vector_table 

	  DATA 

__vector_table 
#ifdef __DATA_IN_ExtSRAM 
 	  DCD     __initial_spTop 				   ; Use internal RAM for stack for calling SystemInit 
 #else 
 	  DCD     sfe(CSTACK) 
#endif /*__DATA_IN_ExtSRAM*/ 
 	  DCD     Reset_Handler      				                   ; Reset Handler  
 	  DCD     NMI_Handler        				                   ; NMI Handler 
 	  DCD     HardFault_Handler   				                   ; Hard Fault Handler 
 	  DCD     MemManage_Handler      				           ; MPU Fault Handler 
 	  DCD     BusFault_Handler       				           ; Bus Fault Handler 
 	  DCD     UsageFault_Handler    				           ; Usage Fault Handler 
 	  DCD     0         				                           ; Reserved 
 	  DCD     0                  				                   ; Reserved  
 	  DCD     0                  				                   ; Reserved 
 	  DCD     0                  				                   ; Reserved 
 	  DCD     SVC_Handler       				                   ; SVCall Handler 
 	  DCD     DebugMon_Handler  				                   ; Debug Monitor Handler 
 	  DCD     0                  				                   ; Reserved 
 	  DCD     PendSV_Handler    				                   ; PendSV Handler 
 	  DCD     SysTick_Handler    				                   ; SysTick Handler 

	 ; External Interrupts 
 	  DCD 				WWDG1_IRQHandler 			;
 	  DCD 				PVD_AVD_IRQHandler		        ;
 	  DCD 				TAMP_IRQHandler 			;
 	  DCD 				RTC_WKUP_ALARM_IRQHandler 	        ;
 	  DCD 				0 				        ;
 	  DCD 				RCC_IRQHandler 				;
 	  DCD 				EXTI0_IRQHandler 			;
 	  DCD 				EXTI1_IRQHandler 			;
 	  DCD 				EXTI2_IRQHandler 			;
 	  DCD 				EXTI3_IRQHandler 			;
 	  DCD 				EXTI4_IRQHandler 			;
 	  DCD 				DMA1_Stream0_IRQHandler 		;
 	  DCD 				DMA1_Stream1_IRQHandler 		;
 	  DCD 				DMA1_Stream2_IRQHandler 		;
 	  DCD 				DMA1_Stream3_IRQHandler 		;
 	  DCD 				DMA1_Stream4_IRQHandler 		;
 	  DCD 				DMA1_Stream5_IRQHandler 		;
 	  DCD 				DMA1_Stream6_IRQHandler 		;
 	  DCD 				ADC1_IRQHandler 			;
 	  DCD 				FDCAN1_IT0_IRQHandler 			;
 	  DCD 				FDCAN2_IT0_IRQHandler 			;
 	  DCD 				FDCAN1_IT1_IRQHandler 			;
 	  DCD 				FDCAN2_IT1_IRQHandler 			;
 	  DCD 				EXTI5_IRQHandler 			;
 	  DCD 				TIM1_BRK_IRQHandler 			;
 	  DCD 				TIM1_UP_IRQHandler 			;
 	  DCD 				TIM1_TRG_COM_IRQHandler 		;
 	  DCD 				TIM1_CC_IRQHandler 			;
 	  DCD 				TIM2_IRQHandler 			;
 	  DCD 				TIM3_IRQHandler 			;
 	  DCD 				TIM4_IRQHandler 			;
 	  DCD 				I2C1_EV_IRQHandler 			;
 	  DCD 				I2C1_ER_IRQHandler 			;
 	  DCD 				I2C2_EV_IRQHandler 			;
 	  DCD 				I2C2_ER_IRQHandler 			;
 	  DCD 				SPI1_IRQHandler 			;
 	  DCD 				SPI2_IRQHandler 			;
 	  DCD 				USART1_IRQHandler 			;
 	  DCD 				USART2_IRQHandler 			;
 	  DCD 				USART3_IRQHandler 			;
 	  DCD 				EXTI10_IRQHandler 			;
 	  DCD 				RTC_TIMESTAMP_IRQHandler 		;
 	  DCD 				EXTI11_IRQHandler 			;
 	  DCD 				TIM8_BRK_IRQHandler 		        ;
 	  DCD 				TIM8_UP_IRQHandler 		        ;
 	  DCD 				TIM8_TRG_COM_IRQHandler 		;
 	  DCD 				TIM8_CC_IRQHandler 			;
 	  DCD 				DMA1_Stream7_IRQHandler 		;
 	  DCD 				FMC_IRQHandler 				;
 	  DCD 				SDMMC1_IRQHandler 		        ;
 	  DCD 				TIM5_IRQHandler 		        ;
 	  DCD 				SPI3_IRQHandler 		        ;
 	  DCD 				UART4_IRQHandler 		        ;
 	  DCD 				UART5_IRQHandler 		        ;
 	  DCD 				TIM6_IRQHandler 		        ;
 	  DCD 				TIM7_IRQHandler 		        ;
 	  DCD 				DMA2_Stream0_IRQHandler 	        ;
 	  DCD 				DMA2_Stream1_IRQHandler 	        ;
 	  DCD 				DMA2_Stream2_IRQHandler 	        ;
 	  DCD 				DMA2_Stream3_IRQHandler 	        ;
 	  DCD 				DMA2_Stream4_IRQHandler 	        ;
 	  DCD 				ETH1_IRQHandler 			;
 	  DCD 				ETH1_WKUP_IRQHandler 			;
 	  DCD 				FDCAN_CAL_IRQHandler 			;
 	  DCD 				EXTI6_IRQHandler 			;
 	  DCD 				EXTI7_IRQHandler 			;
 	  DCD 				EXTI8_IRQHandler 			;
 	  DCD 				EXTI9_IRQHandler 			;
 	  DCD 				DMA2_Stream5_IRQHandler 		;
 	  DCD 				DMA2_Stream6_IRQHandler 		;
 	  DCD 				DMA2_Stream7_IRQHandler 		;
 	  DCD 				USART6_IRQHandler 			;
 	  DCD 				I2C3_EV_IRQHandler 			;
 	  DCD 				I2C3_ER_IRQHandler 			;
 	  DCD 				USBH_OHCI_IRQHandler 			;
 	  DCD 				USBH_EHCI_IRQHandler 			;
 	  DCD 				EXTI12_IRQHandler 			;
 	  DCD 				EXTI13_IRQHandler 			;
 	  DCD 				DCMI_IRQHandler 			;
 	  DCD 				CRYP1_IRQHandler 			;
 	  DCD 				HASH1_IRQHandler 			;
 	  DCD 				FPU_IRQHandler 				;
 	  DCD 				UART7_IRQHandler 			;
 	  DCD 				UART8_IRQHandler 			;
 	  DCD 				SPI4_IRQHandler 			;
 	  DCD 				SPI5_IRQHandler 			;
 	  DCD 				SPI6_IRQHandler 			;
 	  DCD 				SAI1_IRQHandler 			;
 	  DCD 				LTDC_IRQHandler 			;
 	  DCD 				LTDC_ER_IRQHandler 			;
 	  DCD 				ADC2_IRQHandler				;
 	  DCD 				SAI2_IRQHandler 			;
 	  DCD 				QUADSPI_IRQHandler 			;
 	  DCD 				LPTIM1_IRQHandler 			;
 	  DCD 				CEC_IRQHandler 				;
 	  DCD 				I2C4_EV_IRQHandler 			;
 	  DCD 				I2C4_ER_IRQHandler 			;
 	  DCD 				SPDIF_RX_IRQHandler 			;
 	  DCD 				OTG_IRQHandler	 		        ;
 	  DCD 				0 				        ;
 	  DCD 				IPCC_RX0_IRQHandler 			;
 	  DCD 				IPCC_TX0_IRQHandler 			;
 	  DCD 				DMAMUX1_OVR_IRQHandler		        ;
 	  DCD 				IPCC_RX1_IRQHandler 			;
 	  DCD 				IPCC_TX1_IRQHandler 			;
 	  DCD 				CRYP2_IRQHandler 			;
 	  DCD 				HASH2_IRQHandler 			;
 	  DCD 				I2C5_EV_IRQHandler 			;
 	  DCD 				I2C5_ER_IRQHandler 			;
 	  DCD 				GPU_IRQHandler	 			;
 	  DCD 				DFSDM1_FLT0_IRQHandler 			;
 	  DCD 				DFSDM1_FLT1_IRQHandler 			;
 	  DCD 				DFSDM1_FLT2_IRQHandler 			;
 	  DCD 				DFSDM1_FLT3_IRQHandler 			;
 	  DCD 				SAI3_IRQHandler 			;
 	  DCD 				DFSDM1_FLT4_IRQHandler 			;
 	  DCD 				TIM15_IRQHandler 			;
 	  DCD 				TIM16_IRQHandler 			;
 	  DCD 				TIM17_IRQHandler 			;
      DCD 				TIM12_IRQHandler 			;
 	  DCD 				MDIOS_IRQHandler 			;
 	  DCD 				EXTI14_IRQHandler 			;
 	  DCD 				MDMA_IRQHandler 			;
 	  DCD 				DSI_IRQHandler 				;
 	  DCD 				SDMMC2_IRQHandler 			;
 	  DCD 				HSEM_IT2_IRQHandler			;
 	  DCD 				DFSDM1_FLT5_IRQHandler 			;
 	  DCD 				EXTI15_IRQHandler	 			;
 	  DCD 				nCTIIRQ1_IRQHandler 			;
 	  DCD 				nCTIIRQ2_IRQHandler 			;
  	  DCD 				TIM13_IRQHandler 			    ;
  	  DCD 				TIM14_IRQHandler 	            ;
  	  DCD 				DAC_IRQHandler 		            ;
  	  DCD 				RNG1_IRQHandler 	            ;
  	  DCD 				RNG2_IRQHandler 	            ;
 	  DCD 				I2C6_EV_IRQHandler 				;
 	  DCD 				I2C6_ER_IRQHandler 				;
 	  DCD 				SDMMC3_IRQHandler 				;
 	  DCD 				LPTIM2_IRQHandler 				;
 	  DCD 				LPTIM3_IRQHandler 				;
 	  DCD 				LPTIM4_IRQHandler 				;
 	  DCD 				LPTIM5_IRQHandler 				;
 	  DCD 				ETH1_LPI_IRQHandler 			;
 	  DCD 				0 				                ;
 	  DCD 				MPU_SEV_IRQHandler 				;
 	  DCD 				RCC_WAKEUP_IRQHandler           ;
 	  DCD 				SAI4_IRQHandler 				;
 	  DCD 				DTS_IRQHandler	 				;
 	  DCD 				0					 			;
 	  DCD 				WAKEUP_PIN_IRQHandler 		    ;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; 
;;
;; Default interrupt handlers. 
;; 
	 THUMB 
	 PUBWEAK Reset_Handler 
	 SECTION .text:CODE:NOROOT:REORDER(2) 
Reset_Handler 

          LDR     R0, =SystemInit 
          BLX     R0 
          LDR     R0, =__iar_program_start 
          BLX     R0 

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

	  PUBWEAK WWDG1_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
WWDG1_IRQHandler  
 	  B  WWDG1_IRQHandler 

	  PUBWEAK PVD_AVD_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
PVD_AVD_IRQHandler  
 	  B  PVD_AVD_IRQHandler 

	  PUBWEAK TAMP_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
TAMP_IRQHandler  
 	  B  TAMP_IRQHandler 

	  PUBWEAK RTC_WKUP_ALARM_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
RTC_WKUP_ALARM_IRQHandler  
 	  B  RTC_WKUP_ALARM_IRQHandler 

	  PUBWEAK RCC_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
RCC_IRQHandler  
 	  B  RCC_IRQHandler 

	  PUBWEAK EXTI0_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
EXTI0_IRQHandler  
 	  B  EXTI0_IRQHandler 

	  PUBWEAK EXTI1_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
EXTI1_IRQHandler  
 	  B  EXTI1_IRQHandler 

	  PUBWEAK EXTI2_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
EXTI2_IRQHandler  
 	  B  EXTI2_IRQHandler 

	  PUBWEAK EXTI3_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
EXTI3_IRQHandler  
 	  B  EXTI3_IRQHandler 

	  PUBWEAK EXTI4_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
EXTI4_IRQHandler  
 	  B  EXTI4_IRQHandler 

	  PUBWEAK DMA1_Stream0_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DMA1_Stream0_IRQHandler  
 	  B  DMA1_Stream0_IRQHandler 

	  PUBWEAK DMA1_Stream1_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DMA1_Stream1_IRQHandler  
 	  B  DMA1_Stream1_IRQHandler 

	  PUBWEAK DMA1_Stream2_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DMA1_Stream2_IRQHandler  
 	  B  DMA1_Stream2_IRQHandler 

	  PUBWEAK DMA1_Stream3_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DMA1_Stream3_IRQHandler  
 	  B  DMA1_Stream3_IRQHandler 

	  PUBWEAK DMA1_Stream4_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DMA1_Stream4_IRQHandler  
 	  B  DMA1_Stream4_IRQHandler 

	  PUBWEAK DMA1_Stream5_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DMA1_Stream5_IRQHandler  
 	  B  DMA1_Stream5_IRQHandler 

	  PUBWEAK DMA1_Stream6_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DMA1_Stream6_IRQHandler  
 	  B  DMA1_Stream6_IRQHandler 

	  PUBWEAK ADC1_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
ADC1_IRQHandler  
 	  B  ADC1_IRQHandler 

	  PUBWEAK FDCAN1_IT0_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
FDCAN1_IT0_IRQHandler  
 	  B  FDCAN1_IT0_IRQHandler 

	  PUBWEAK FDCAN2_IT0_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
FDCAN2_IT0_IRQHandler  
 	  B  FDCAN2_IT0_IRQHandler 

	  PUBWEAK FDCAN1_IT1_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
FDCAN1_IT1_IRQHandler  
 	  B  FDCAN1_IT1_IRQHandler 

	  PUBWEAK FDCAN2_IT1_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
FDCAN2_IT1_IRQHandler  
 	  B  FDCAN2_IT1_IRQHandler 

	  PUBWEAK EXTI5_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
EXTI5_IRQHandler  
 	  B  EXTI5_IRQHandler 

	  PUBWEAK TIM1_BRK_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
TIM1_BRK_IRQHandler  
 	  B  TIM1_BRK_IRQHandler 

	  PUBWEAK TIM1_UP_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
TIM1_UP_IRQHandler  
 	  B  TIM1_UP_IRQHandler 

	  PUBWEAK TIM1_TRG_COM_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
TIM1_TRG_COM_IRQHandler  
 	  B  TIM1_TRG_COM_IRQHandler 

	  PUBWEAK TIM1_CC_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
TIM1_CC_IRQHandler  
 	  B  TIM1_CC_IRQHandler 

	  PUBWEAK TIM2_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
TIM2_IRQHandler  
 	  B  TIM2_IRQHandler 

	  PUBWEAK TIM3_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
TIM3_IRQHandler  
 	  B  TIM3_IRQHandler 

	  PUBWEAK TIM4_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
TIM4_IRQHandler  
 	  B  TIM4_IRQHandler 

	  PUBWEAK I2C1_EV_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
I2C1_EV_IRQHandler  
 	  B  I2C1_EV_IRQHandler 

	  PUBWEAK I2C1_ER_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
I2C1_ER_IRQHandler  
 	  B  I2C1_ER_IRQHandler 

	  PUBWEAK I2C2_EV_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
I2C2_EV_IRQHandler  
 	  B  I2C2_EV_IRQHandler 

	  PUBWEAK I2C2_ER_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
I2C2_ER_IRQHandler  
 	  B  I2C2_ER_IRQHandler 

	  PUBWEAK SPI1_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
SPI1_IRQHandler  
 	  B  SPI1_IRQHandler 

	  PUBWEAK SPI2_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
SPI2_IRQHandler  
 	  B  SPI2_IRQHandler 

	  PUBWEAK USART1_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
USART1_IRQHandler  
 	  B  USART1_IRQHandler 

	  PUBWEAK USART2_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
USART2_IRQHandler  
 	  B  USART2_IRQHandler 

	  PUBWEAK USART3_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
USART3_IRQHandler  
 	  B  USART3_IRQHandler 

	  PUBWEAK EXTI10_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
EXTI10_IRQHandler  
 	  B  EXTI10_IRQHandler 

	  PUBWEAK RTC_TIMESTAMP_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
RTC_TIMESTAMP_IRQHandler  
 	  B  RTC_TIMESTAMP_IRQHandler 

	  PUBWEAK EXTI11_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
EXTI11_IRQHandler  
 	  B  EXTI11_IRQHandler 

	  PUBWEAK TIM8_BRK_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
TIM8_BRK_IRQHandler  
 	  B  TIM8_BRK_IRQHandler 

	  PUBWEAK TIM8_UP_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
TIM8_UP_IRQHandler  
 	  B  TIM8_UP_IRQHandler 

	  PUBWEAK TIM8_TRG_COM_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
TIM8_TRG_COM_IRQHandler  
 	  B  TIM8_TRG_COM_IRQHandler 

	  PUBWEAK TIM8_CC_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
TIM8_CC_IRQHandler  
 	  B  TIM8_CC_IRQHandler 

	  PUBWEAK DMA1_Stream7_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DMA1_Stream7_IRQHandler  
 	  B  DMA1_Stream7_IRQHandler 

	  PUBWEAK FMC_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
FMC_IRQHandler  
 	  B  FMC_IRQHandler 

	  PUBWEAK SDMMC1_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
SDMMC1_IRQHandler  
 	  B  SDMMC1_IRQHandler 

	  PUBWEAK TIM5_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
TIM5_IRQHandler  
 	  B  TIM5_IRQHandler 

	  PUBWEAK SPI3_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
SPI3_IRQHandler  
 	  B  SPI3_IRQHandler 

	  PUBWEAK UART4_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
UART4_IRQHandler  
 	  B  UART4_IRQHandler 

	  PUBWEAK UART5_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
UART5_IRQHandler  
 	  B  UART5_IRQHandler 

	  PUBWEAK TIM6_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
TIM6_IRQHandler  
 	  B  TIM6_IRQHandler 

	  PUBWEAK TIM7_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
TIM7_IRQHandler  
 	  B  TIM7_IRQHandler 

	  PUBWEAK DMA2_Stream0_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DMA2_Stream0_IRQHandler  
 	  B  DMA2_Stream0_IRQHandler 

	  PUBWEAK DMA2_Stream1_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DMA2_Stream1_IRQHandler  
 	  B  DMA2_Stream1_IRQHandler 

	  PUBWEAK DMA2_Stream2_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DMA2_Stream2_IRQHandler  
 	  B  DMA2_Stream2_IRQHandler 

	  PUBWEAK DMA2_Stream3_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DMA2_Stream3_IRQHandler  
 	  B  DMA2_Stream3_IRQHandler 

	  PUBWEAK DMA2_Stream4_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DMA2_Stream4_IRQHandler  
 	  B  DMA2_Stream4_IRQHandler 

	  PUBWEAK ETH1_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
ETH1_IRQHandler  
 	  B  ETH1_IRQHandler 

	  PUBWEAK ETH1_WKUP_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
ETH1_WKUP_IRQHandler  
 	  B  ETH1_WKUP_IRQHandler 

	  PUBWEAK ETH1_LPI_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
ETH1_LPI_IRQHandler  
 	  B  ETH1_LPI_IRQHandler 
	  
	  PUBWEAK FDCAN_CAL_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
FDCAN_CAL_IRQHandler  
 	  B  FDCAN_CAL_IRQHandler 

	  PUBWEAK EXTI6_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
EXTI6_IRQHandler  
 	  B  EXTI6_IRQHandler 

	  PUBWEAK EXTI7_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
EXTI7_IRQHandler  
 	  B  EXTI7_IRQHandler 

	  PUBWEAK EXTI8_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
EXTI8_IRQHandler  
 	  B  EXTI8_IRQHandler 

	  PUBWEAK EXTI9_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
EXTI9_IRQHandler  
 	  B  EXTI9_IRQHandler 

	  PUBWEAK DMA2_Stream5_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DMA2_Stream5_IRQHandler  
 	  B  DMA2_Stream5_IRQHandler 

	  PUBWEAK DMA2_Stream6_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DMA2_Stream6_IRQHandler  
 	  B  DMA2_Stream6_IRQHandler 

	  PUBWEAK DMA2_Stream7_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DMA2_Stream7_IRQHandler  
 	  B  DMA2_Stream7_IRQHandler 

	  PUBWEAK USART6_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
USART6_IRQHandler  
 	  B  USART6_IRQHandler 

	  PUBWEAK I2C3_EV_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
I2C3_EV_IRQHandler  
 	  B  I2C3_EV_IRQHandler 

	  PUBWEAK I2C3_ER_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
I2C3_ER_IRQHandler  
 	  B  I2C3_ER_IRQHandler 

	  PUBWEAK USBH_OHCI_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
USBH_OHCI_IRQHandler  
 	  B  USBH_OHCI_IRQHandler 

	  PUBWEAK USBH_EHCI_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
USBH_EHCI_IRQHandler  
 	  B  USBH_EHCI_IRQHandler 

	  PUBWEAK EXTI12_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
EXTI12_IRQHandler  
 	  B  EXTI12_IRQHandler 

	  PUBWEAK EXTI13_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
EXTI13_IRQHandler  
 	  B  EXTI13_IRQHandler 

	  PUBWEAK DCMI_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DCMI_IRQHandler  
 	  B  DCMI_IRQHandler 

	  PUBWEAK CRYP1_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
CRYP1_IRQHandler  
 	  B  CRYP1_IRQHandler 

	  PUBWEAK HASH1_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
HASH1_IRQHandler  
 	  B  HASH1_IRQHandler 

	  PUBWEAK FPU_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
FPU_IRQHandler  
 	  B  FPU_IRQHandler 

	  PUBWEAK UART7_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
UART7_IRQHandler  
 	  B  UART7_IRQHandler 

	  PUBWEAK UART8_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
UART8_IRQHandler  
 	  B  UART8_IRQHandler 

	  PUBWEAK SPI4_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
SPI4_IRQHandler  
 	  B  SPI4_IRQHandler 

	  PUBWEAK SPI5_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
SPI5_IRQHandler  
 	  B  SPI5_IRQHandler 

	  PUBWEAK SPI6_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
SPI6_IRQHandler  
 	  B  SPI6_IRQHandler 

	  PUBWEAK SAI1_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
SAI1_IRQHandler  
 	  B  SAI1_IRQHandler 

	  PUBWEAK LTDC_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
LTDC_IRQHandler  
 	  B  LTDC_IRQHandler 

	  PUBWEAK LTDC_ER_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
LTDC_ER_IRQHandler  
 	  B  LTDC_ER_IRQHandler 

	  PUBWEAK ADC2_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
ADC2_IRQHandler  
 	  B  ADC2_IRQHandler 

	  PUBWEAK SAI2_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
SAI2_IRQHandler  
 	  B  SAI2_IRQHandler 

	  PUBWEAK QUADSPI_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
QUADSPI_IRQHandler  
 	  B  QUADSPI_IRQHandler 

	  PUBWEAK LPTIM1_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
LPTIM1_IRQHandler  
 	  B  LPTIM1_IRQHandler 

	  PUBWEAK CEC_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
CEC_IRQHandler  
 	  B  CEC_IRQHandler 

	  PUBWEAK I2C4_EV_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
I2C4_EV_IRQHandler  
 	  B  I2C4_EV_IRQHandler 

	  PUBWEAK I2C4_ER_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
I2C4_ER_IRQHandler  
 	  B  I2C4_ER_IRQHandler 

	  PUBWEAK SPDIF_RX_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
SPDIF_RX_IRQHandler  
 	  B  SPDIF_RX_IRQHandler 

	  PUBWEAK OTG_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
OTG_IRQHandler  
 	  B  OTG_IRQHandler 

	  PUBWEAK IPCC_RX0_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
IPCC_RX0_IRQHandler  
 	  B  IPCC_RX0_IRQHandler 

	  PUBWEAK IPCC_TX0_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
IPCC_TX0_IRQHandler  
 	  B  IPCC_TX0_IRQHandler 

	  PUBWEAK DMAMUX1_OVR_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DMAMUX1_OVR_IRQHandler  
 	  B  DMAMUX1_OVR_IRQHandler 

	  PUBWEAK IPCC_RX1_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
IPCC_RX1_IRQHandler  
 	  B  IPCC_RX1_IRQHandler 

	  PUBWEAK IPCC_TX1_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
IPCC_TX1_IRQHandler  
 	  B  IPCC_TX1_IRQHandler 

	  PUBWEAK CRYP2_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
CRYP2_IRQHandler  
 	  B  CRYP2_IRQHandler 

	  PUBWEAK HASH2_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
HASH2_IRQHandler  
 	  B  HASH2_IRQHandler 

	  PUBWEAK I2C5_EV_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
I2C5_EV_IRQHandler  
 	  B  I2C5_EV_IRQHandler 

	  PUBWEAK I2C5_ER_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
I2C5_ER_IRQHandler  
 	  B  I2C5_ER_IRQHandler 

	  PUBWEAK GPU_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
GPU_IRQHandler  
 	  B  GPU_IRQHandler 

	  PUBWEAK DFSDM1_FLT0_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DFSDM1_FLT0_IRQHandler  
 	  B  DFSDM1_FLT0_IRQHandler 

	  PUBWEAK DFSDM1_FLT1_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DFSDM1_FLT1_IRQHandler  
 	  B  DFSDM1_FLT1_IRQHandler 

	  PUBWEAK DFSDM1_FLT2_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DFSDM1_FLT2_IRQHandler  
 	  B  DFSDM1_FLT2_IRQHandler 

	  PUBWEAK DFSDM1_FLT3_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DFSDM1_FLT3_IRQHandler  
 	  B  DFSDM1_FLT3_IRQHandler 

	  PUBWEAK SAI3_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
SAI3_IRQHandler  
 	  B  SAI3_IRQHandler 

	  PUBWEAK DFSDM1_FLT4_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DFSDM1_FLT4_IRQHandler  
 	  B  DFSDM1_FLT4_IRQHandler 

	  PUBWEAK TIM15_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
TIM15_IRQHandler  
 	  B  TIM15_IRQHandler 

	  PUBWEAK TIM16_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
TIM16_IRQHandler  
 	  B  TIM16_IRQHandler 

	  PUBWEAK TIM17_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
TIM17_IRQHandler  
 	  B  TIM17_IRQHandler 
          
          	  PUBWEAK TIM12_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
TIM12_IRQHandler  
 	  B  TIM12_IRQHandler 

	  PUBWEAK MDIOS_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
MDIOS_IRQHandler  
 	  B  MDIOS_IRQHandler 

	  PUBWEAK EXTI14_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
EXTI14_IRQHandler  
 	  B  EXTI14_IRQHandler 

	  PUBWEAK MDMA_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
MDMA_IRQHandler  
 	  B  MDMA_IRQHandler 

	  PUBWEAK DSI_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DSI_IRQHandler  
 	  B  DSI_IRQHandler 

	  PUBWEAK SDMMC2_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
SDMMC2_IRQHandler  
 	  B  SDMMC2_IRQHandler 

	  PUBWEAK HSEM_IT2_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
HSEM_IT2_IRQHandler  
 	  B  HSEM_IT2_IRQHandler
      
      PUBWEAK DFSDM1_FLT5_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DFSDM1_FLT5_IRQHandler  
 	  B  DFSDM1_FLT5_IRQHandler 
      
      PUBWEAK nCTIIRQ1_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
nCTIIRQ1_IRQHandler  
 	  B  nCTIIRQ1_IRQHandler 
      
      PUBWEAK nCTIIRQ2_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
nCTIIRQ2_IRQHandler  
 	  B  nCTIIRQ2_IRQHandler 
            
	  PUBWEAK EXTI15_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
EXTI15_IRQHandler  
 	  B  EXTI15_IRQHandler 

   	  PUBWEAK TIM13_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
TIM13_IRQHandler  
 	  B  TIM13_IRQHandler
          
   	  PUBWEAK TIM14_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
TIM14_IRQHandler  
 	  B  TIM14_IRQHandler  

       	  PUBWEAK DAC_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DAC_IRQHandler  
 	  B  DAC_IRQHandler        
          
       	  PUBWEAK RNG1_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
RNG1_IRQHandler  
 	  B  RNG1_IRQHandler        

       	  PUBWEAK RNG2_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
RNG2_IRQHandler  
 	  B  RNG2_IRQHandler        

          PUBWEAK I2C6_EV_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
I2C6_EV_IRQHandler  
 	  B  I2C6_EV_IRQHandler 

	  PUBWEAK I2C6_ER_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
I2C6_ER_IRQHandler  
 	  B  I2C6_ER_IRQHandler

	  PUBWEAK SDMMC3_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
SDMMC3_IRQHandler  
 	  B  SDMMC3_IRQHandler 

	  PUBWEAK LPTIM2_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
LPTIM2_IRQHandler  
 	  B  LPTIM2_IRQHandler 

	  PUBWEAK LPTIM3_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
LPTIM3_IRQHandler  
 	  B  LPTIM3_IRQHandler 

	  PUBWEAK LPTIM4_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
LPTIM4_IRQHandler  
 	  B  LPTIM4_IRQHandler 

	  PUBWEAK LPTIM5_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
LPTIM5_IRQHandler  
 	  B  LPTIM5_IRQHandler 

	  PUBWEAK MPU_SEV_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
MPU_SEV_IRQHandler  
 	  B  MPU_SEV_IRQHandler 

	  PUBWEAK RCC_WAKEUP_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
RCC_WAKEUP_IRQHandler  
 	  B  RCC_WAKEUP_IRQHandler 
      
	  PUBWEAK SAI4_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
SAI4_IRQHandler  
 	  B  SAI4_IRQHandler 

	  PUBWEAK DTS_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
DTS_IRQHandler  
 	  B  DTS_IRQHandler 

	  PUBWEAK WAKEUP_PIN_IRQHandler 
	  SECTION .text:CODE:NOROOT:REORDER(1) 
WAKEUP_PIN_IRQHandler  
 	  B  WAKEUP_PIN_IRQHandler 

	 END 
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/