/********************************** (C) COPYRIGHT *******************************
* File Name          : startup_ch32v20x_D6.S
* Author             : WCH
* Version            : V1.0.2
* Date               : 2025/10/21
* Description        : CH32V203C8T6 (D6) vector table from WCH EVT.
*                      handle_reset jumps to RT-Thread entry, same as
*                      CH32V20x-SDK-for-RTT D8W rtt-patch (not bare-metal main).
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

	.section	.init,"ax",@progbits
	.global	_start
	.align	1
_start:
	j	handle_reset
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00000013
	.word 0x00100073

	.section	.vector,"ax",@progbits
	.align	1
_vector_base:
	.option norvc;
	.word	_start
	.word	0
	.word	NMI_Handler
	.word	HardFault_Handler
	.word	0
	.word	Ecall_M_Mode_Handler
	.word	0
	.word	0
	.word	Ecall_U_Mode_Handler
	.word	Break_Point_Handler
	.word	0
	.word	0
	.word	SysTick_Handler
	.word	0
	.word	SW_handler	/* libcpu symbol; SW_Handler would be a different infinite loop */
	.word	0
	.word	WWDG_IRQHandler
	.word	PVD_IRQHandler
	.word	TAMPER_IRQHandler
	.word	RTC_IRQHandler
	.word	FLASH_IRQHandler
	.word	RCC_IRQHandler
	.word	EXTI0_IRQHandler
	.word	EXTI1_IRQHandler
	.word	EXTI2_IRQHandler
	.word	EXTI3_IRQHandler
	.word	EXTI4_IRQHandler
	.word	DMA1_Channel1_IRQHandler
	.word	DMA1_Channel2_IRQHandler
	.word	DMA1_Channel3_IRQHandler
	.word	DMA1_Channel4_IRQHandler
	.word	DMA1_Channel5_IRQHandler
	.word	DMA1_Channel6_IRQHandler
	.word	DMA1_Channel7_IRQHandler
	.word	ADC1_2_IRQHandler
	.word	USB_HP_CAN1_TX_IRQHandler
	.word	USB_LP_CAN1_RX0_IRQHandler
	.word	CAN1_RX1_IRQHandler
	.word	CAN1_SCE_IRQHandler
	.word	EXTI9_5_IRQHandler
	.word	TIM1_BRK_IRQHandler
	.word	TIM1_UP_IRQHandler
	.word	TIM1_TRG_COM_IRQHandler
	.word	TIM1_CC_IRQHandler
	.word	TIM2_IRQHandler
	.word	TIM3_IRQHandler
	.word	TIM4_IRQHandler
	.word	I2C1_EV_IRQHandler
	.word	I2C1_ER_IRQHandler
	.word	I2C2_EV_IRQHandler
	.word	I2C2_ER_IRQHandler
	.word	SPI1_IRQHandler
	.word	SPI2_IRQHandler
	.word	USART1_IRQHandler
	.word	USART2_IRQHandler
	.word	USART3_IRQHandler
	.word	EXTI15_10_IRQHandler
	.word	RTCAlarm_IRQHandler
	.word	USBWakeUp_IRQHandler
	.word	USBFS_IRQHandler
	.word	USBFSWakeUp_IRQHandler
	.word	UART4_IRQHandler
	.word	DMA1_Channel8_IRQHandler

	.option rvc;
	.section .text.vector_handler, "ax", @progbits
	.weak	NMI_Handler
	.weak	HardFault_Handler
	.weak	Ecall_M_Mode_Handler
	.weak	Ecall_U_Mode_Handler
	.weak	Break_Point_Handler
	.weak	SysTick_Handler
	.weak	SW_handler
	.weak	WWDG_IRQHandler
	.weak	PVD_IRQHandler
	.weak	TAMPER_IRQHandler
	.weak	RTC_IRQHandler
	.weak	FLASH_IRQHandler
	.weak	RCC_IRQHandler
	.weak	EXTI0_IRQHandler
	.weak	EXTI1_IRQHandler
	.weak	EXTI2_IRQHandler
	.weak	EXTI3_IRQHandler
	.weak	EXTI4_IRQHandler
	.weak	DMA1_Channel1_IRQHandler
	.weak	DMA1_Channel2_IRQHandler
	.weak	DMA1_Channel3_IRQHandler
	.weak	DMA1_Channel4_IRQHandler
	.weak	DMA1_Channel5_IRQHandler
	.weak	DMA1_Channel6_IRQHandler
	.weak	DMA1_Channel7_IRQHandler
	.weak	ADC1_2_IRQHandler
	.weak	USB_HP_CAN1_TX_IRQHandler
	.weak	USB_LP_CAN1_RX0_IRQHandler
	.weak	CAN1_RX1_IRQHandler
	.weak	CAN1_SCE_IRQHandler
	.weak	EXTI9_5_IRQHandler
	.weak	TIM1_BRK_IRQHandler
	.weak	TIM1_UP_IRQHandler
	.weak	TIM1_TRG_COM_IRQHandler
	.weak	TIM1_CC_IRQHandler
	.weak	TIM2_IRQHandler
	.weak	TIM3_IRQHandler
	.weak	TIM4_IRQHandler
	.weak	I2C1_EV_IRQHandler
	.weak	I2C1_ER_IRQHandler
	.weak	I2C2_EV_IRQHandler
	.weak	I2C2_ER_IRQHandler
	.weak	SPI1_IRQHandler
	.weak	SPI2_IRQHandler
	.weak	USART1_IRQHandler
	.weak	USART2_IRQHandler
	.weak	USART3_IRQHandler
	.weak	EXTI15_10_IRQHandler
	.weak	RTCAlarm_IRQHandler
	.weak	USBWakeUp_IRQHandler
	.weak	USBFS_IRQHandler
	.weak	USBFSWakeUp_IRQHandler
	.weak	UART4_IRQHandler
	.weak	DMA1_Channel8_IRQHandler

NMI_Handler:
HardFault_Handler:
Ecall_M_Mode_Handler:
Ecall_U_Mode_Handler:
Break_Point_Handler:
SysTick_Handler:
SW_handler:
WWDG_IRQHandler:
PVD_IRQHandler:
TAMPER_IRQHandler:
RTC_IRQHandler:
FLASH_IRQHandler:
RCC_IRQHandler:
EXTI0_IRQHandler:
EXTI1_IRQHandler:
EXTI2_IRQHandler:
EXTI3_IRQHandler:
EXTI4_IRQHandler:
DMA1_Channel1_IRQHandler:
DMA1_Channel2_IRQHandler:
DMA1_Channel3_IRQHandler:
DMA1_Channel4_IRQHandler:
DMA1_Channel5_IRQHandler:
DMA1_Channel6_IRQHandler:
DMA1_Channel7_IRQHandler:
ADC1_2_IRQHandler:
USB_HP_CAN1_TX_IRQHandler:
USB_LP_CAN1_RX0_IRQHandler:
CAN1_RX1_IRQHandler:
CAN1_SCE_IRQHandler:
EXTI9_5_IRQHandler:
TIM1_BRK_IRQHandler:
TIM1_UP_IRQHandler:
TIM1_TRG_COM_IRQHandler:
TIM1_CC_IRQHandler:
TIM2_IRQHandler:
TIM3_IRQHandler:
TIM4_IRQHandler:
I2C1_EV_IRQHandler:
I2C1_ER_IRQHandler:
I2C2_EV_IRQHandler:
I2C2_ER_IRQHandler:
SPI1_IRQHandler:
SPI2_IRQHandler:
USART1_IRQHandler:
USART2_IRQHandler:
USART3_IRQHandler:
EXTI15_10_IRQHandler:
RTCAlarm_IRQHandler:
USBWakeUp_IRQHandler:
USBFS_IRQHandler:
USBFSWakeUp_IRQHandler:
UART4_IRQHandler:
DMA1_Channel8_IRQHandler:
1:
	j 1b

	.section	.text.handle_reset,"ax",@progbits
	.weak	handle_reset
	.align	1
handle_reset:
.option push
.option norelax
	la gp, __global_pointer$
.option pop
	la sp, _eusrstack

	la a0, _data_lma
	la a1, _data_vma
	la a2, _edata
	bgeu a1, a2, 2f
1:
	lw t0, (a0)
	sw t0, (a1)
	addi a0, a0, 4
	addi a1, a1, 4
	bltu a1, a2, 1b
2:
	la a0, _sbss
	la a1, _ebss
	bgeu a0, a1, 2f
1:
	sw zero, (a0)
	addi a0, a0, 4
	bltu a0, a1, 1b
2:
	li t0, 0x1f
	csrw 0xbc0, t0

	li t0, 0x2
	csrw 0x804, t0

	li t0, 0x1800
	csrw mstatus, t0

	la t0, _vector_base
	ori t0, t0, 3
	csrw mtvec, t0

	jal SystemInit
	la t0, entry
	csrw mepc, t0
	mret
