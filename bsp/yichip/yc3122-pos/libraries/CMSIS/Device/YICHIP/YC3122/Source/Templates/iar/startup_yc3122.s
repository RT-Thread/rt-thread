;/*
; * Copyright (c) 2006-2020, YICHIP Development Team
; * @file     startup_yc3122.s
; * @brief    source file for setting startup
; *
; * Change Logs:
; * Date           Author             Version        Notes
; * 2022-11-08     kiven              V1.0.0         the first version
; */

        MODULE  ?cstartup                       ; // 定义模块名称

        ;Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)
        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start             ; // IAR 入口函数
        EXTERN  SystemInit                      ; // 系统初始化函数
        PUBLIC  _vector_table                   ; // 中断向量表地址

        ALIGNROM 2
        DATA                                    ; // 定义数据段
_vector_table                                   ;中断向量表
        DCD     sfe(CSTACK)
        DCD     Reset_Handler                   ;//reset    1
        DCD     0x00000000                      ;//NMI      2
        DCD     hard_fault_handler           ;//HARD     3
        DCD     0                               ;
        DCD     0                               ;
        DCD     0                               ;
        DCD     0                               ;
        DCD     0                               ;
        DCD     0                               ;
        DCD     0                               ;
        DCD     svc_handler                  ;//SVC      11
        DCD     0                               ;
        DCD     0                               ;
        DCD     pendsv_handler               ;//PENDSV  14
        DCD     systick_handler              ;//SYSTICK 15
        DCD     USB_IRQHandler                  ;//IQR0
        DCD     I2C0_IRQHandler                 ;//IQR1
        DCD     I2C1_IRQHandler                 ;//IQR2
        DCD     QSPI_IRQHandler                 ;//IQR3
        DCD     SPI0_IRQHandler                 ;//IQR4
        DCD     SPI1_IRQHandler                 ;
        DCD     HSPI_IRQHandler                 ;
        DCD     SEC_IRQHandler                  ;
        DCD     UART0_IRQHandler                ;
        DCD     UART1_IRQHandler                ;
        DCD     UART2_IRQHandler                ;
        DCD     UART3_IRQHandler                ;
        DCD     MEMCP_IRQHandler                ;
        DCD     SCI0_IRQHandler                 ;
        DCD     SCI1_IRQHandler                 ;
        DCD     MSR_IRQHandler                  ;
        DCD     GPIO_IRQHandler                 ;
        DCD     TMRG0_IRQHandler                ;
        DCD     TMRG1_IRQHandler                ;
        DCD     SDIO_IRQHandler                 ;
        DCD     PSARM_IRQHandler                ;
        DCD     RSA_IRQHandler                  ;
        DCD     SM4_IRQHandler                  ;
        DCD     TRNG_IRQHandler                 ;
        DCD     WDT_IRQHandler                  ;
        DCD     DCMI_IRQHandler                 ;
        DCD     ADC_IRQHandler                  ;
        DCD     RTC_IRQHandler                  ;
        DCD     BIN_IRQHandler                  ;
        DCD     POWER_IRQHandler                ;
        DCD     SOFTWARE_IRQHandler             ;
        DCD     RISCV_IRQHandler                ;

        THUMB                                   ;//进入THUMB模式（THUMB-2指令集）
        SECTION .intvec:CODE:REORDER(2)
        CODE
        PUBLIC isr
isr
        LDR     R1,=_vector_table
        LDR     R0,[R0,R1]
        BX      R0
        NOP
        NOP
        NOP

        PUBLIC Reset_Handler
Reset_Handler
        LDR     R0, =sfe(CSTACK)
        mov	sp, R0
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0
		
hard_fault_handler PROC
			EXPORT  hard_fault_handler 
            IMPORT HardFault_Handler
			LDR r0,=HardFault_Handler       
			BX r0
			nop
			ENDP
		
svc_handler PROC
			EXPORT  svc_handler         
			ldr r0,=SVC_IRQHandler
			BX r0
			nop
			ENDP

pendsv_handler PROC
			EXPORT  pendsv_handler
            IMPORT  PendSV_Handler
			LDR r0,=PendSV_Handler
			BX r0
			nop
			ENDP
		
systick_handler 	PROC
			EXPORT systick_handler 
            IMPORT SysTick_Handler
			LDR r0,=SysTick_Handler
			BX r0
			nop
			ENDP

; // 定义默认的中断函数，这里只是弱定义，可以被用户自己定义的中断向量函数覆盖
        PUBWEAK HARD_FAULT_IRQHandler
        PUBWEAK SVC_IRQHandler
        PUBWEAK PENDSV_IRQHandler
        PUBWEAK SYSTICK_IRQHandler
        PUBWEAK EXTI_IRQHandler
        PUBWEAK TIMER0_IRQHandler
        PUBWEAK TIMER1_IRQHandler
        PUBWEAK TIMER2_IRQHandler
        PUBWEAK TIMER3_IRQHandler
        PUBWEAK TIMER4_IRQHandler
        PUBWEAK TIMER5_IRQHandler
        PUBWEAK TIMER6_IRQHandler
        PUBWEAK TIMER7_IRQHandler
        PUBWEAK TIMER8_IRQHandler
        PUBWEAK CHGRIN_IRQHandler
        PUBWEAK VBAT_IRQHandler
        PUBWEAK USB_IRQHandler
        PUBWEAK I2C0_IRQHandler
        PUBWEAK I2C1_IRQHandler
        PUBWEAK QSPI_IRQHandler
        PUBWEAK SPI0_IRQHandler
        PUBWEAK SPI1_IRQHandler
        PUBWEAK HSPI_IRQHandler
        PUBWEAK SEC_IRQHandler
        PUBWEAK UART0_IRQHandler
        PUBWEAK UART1_IRQHandler
        PUBWEAK UART2_IRQHandler
        PUBWEAK UART3_IRQHandler
        PUBWEAK MEMCP_IRQHandler
        PUBWEAK SCI0_IRQHandler
        PUBWEAK SCI1_IRQHandler
        PUBWEAK MSR_IRQHandler
        PUBWEAK GPIO_IRQHandler
        PUBWEAK TMRG0_IRQHandler
        PUBWEAK TMRG1_IRQHandler
        PUBWEAK SDIO_IRQHandler
        PUBWEAK PSARM_IRQHandler
        PUBWEAK RSA_IRQHandler
        PUBWEAK SM4_IRQHandler
        PUBWEAK TRNG_IRQHandler
        PUBWEAK WDT_IRQHandler
        PUBWEAK DCMI_IRQHandler
        PUBWEAK ADC_IRQHandler
        PUBWEAK RTC_IRQHandler
        PUBWEAK BIN_IRQHandler
        PUBWEAK POWER_IRQHandler
        PUBWEAK SOFTWARE_IRQHandler
        PUBWEAK RISCV_IRQHandler

; ToDo:  Add here the names for the device specific external interrupts handler
HARD_FAULT_IRQHandler
SVC_IRQHandler
PENDSV_IRQHandler
SYSTICK_IRQHandler
EXTI_IRQHandler
TIMER0_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
TIMER3_IRQHandler
TIMER4_IRQHandler
TIMER5_IRQHandler
TIMER6_IRQHandler
TIMER7_IRQHandler
TIMER8_IRQHandler
CHGRIN_IRQHandler
VBAT_IRQHandler
USB_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
QSPI_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
HSPI_IRQHandler
SEC_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
MEMCP_IRQHandler
SCI0_IRQHandler
SCI1_IRQHandler
MSR_IRQHandler
GPIO_IRQHandler
TMRG0_IRQHandler
TMRG1_IRQHandler
SDIO_IRQHandler
PSARM_IRQHandler
RSA_IRQHandler
SM4_IRQHandler
TRNG_IRQHandler
WDT_IRQHandler
DCMI_IRQHandler
ADC_IRQHandler
RTC_IRQHandler
BIN_IRQHandler
POWER_IRQHandler
SOFTWARE_IRQHandler
RISCV_IRQHandler
        B       .
        END
