/*
 * Copyright (c) 2019 Nuclei Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/******************************************************************************
 * \file     startup_gd32vf103.S
 * \brief    NMSIS Nuclei N/NX Class Core based Core Device Startup File for
 *  Device gd32vf103
 * \version  V1.00
 * \date     21 Nov 2019
 *
 *
 ******************************************************************************/

#include "riscv_encoding.h"

.macro DECLARE_INT_HANDLER  INT_HDL_NAME
#if defined(__riscv_xlen) && (__riscv_xlen == 32)
    .word \INT_HDL_NAME
#else
    .dword \INT_HDL_NAME
#endif
.endm

    /*
     * Put the interrupt vectors in this section according to the run mode:
     * FlashXIP: .vtable
     * ILM: .vtable
     * Flash: .vtable_ilm
     */
#if defined(DOWNLOAD_MODE) && (DOWNLOAD_MODE == DOWNLOAD_MODE_FLASH)
    .section .vtable_ilm
#else
    .section .vtable
#endif

    .weak  eclic_msip_handler
    .weak  eclic_mtip_handler
    .weak  eclic_bwei_handler
    .weak  eclic_pmovi_handler
    .weak  WWDGT_IRQHandler
    .weak  LVD_IRQHandler
    .weak  TAMPER_IRQHandler
    .weak  RTC_IRQHandler
    .weak  FMC_IRQHandler
    .weak  RCU_IRQHandler
    .weak  EXTI0_IRQHandler
    .weak  EXTI1_IRQHandler
    .weak  EXTI2_IRQHandler
    .weak  EXTI3_IRQHandler
    .weak  EXTI4_IRQHandler
    .weak  DMA0_Channel0_IRQHandler
    .weak  DMA0_Channel1_IRQHandler
    .weak  DMA0_Channel2_IRQHandler
    .weak  DMA0_Channel3_IRQHandler
    .weak  DMA0_Channel4_IRQHandler
    .weak  DMA0_Channel5_IRQHandler
    .weak  DMA0_Channel6_IRQHandler
    .weak  ADC0_1_IRQHandler
    .weak  CAN0_TX_IRQHandler
    .weak  CAN0_RX0_IRQHandler
    .weak  CAN0_RX1_IRQHandler
    .weak  CAN0_EWMC_IRQHandler
    .weak  EXTI5_9_IRQHandler
    .weak  TIMER0_BRK_IRQHandler
    .weak  TIMER0_UP_IRQHandler
    .weak  TIMER0_TRG_CMT_IRQHandler
    .weak  TIMER0_Channel_IRQHandler
    .weak  TIMER1_IRQHandler
    .weak  TIMER2_IRQHandler
    .weak  TIMER3_IRQHandler
    .weak  I2C0_EV_IRQHandler
    .weak  I2C0_ER_IRQHandler
    .weak  I2C1_EV_IRQHandler
    .weak  I2C1_ER_IRQHandler
    .weak  SPI0_IRQHandler
    .weak  SPI1_IRQHandler
    .weak  USART0_IRQHandler
    .weak  USART1_IRQHandler
    .weak  USART2_IRQHandler
    .weak  EXTI10_15_IRQHandler
    .weak  RTC_Alarm_IRQHandler
    .weak  USBFS_WKUP_IRQHandler
    .weak  EXMC_IRQHandler
    .weak  TIMER4_IRQHandler
    .weak  SPI2_IRQHandler
    .weak  UART3_IRQHandler
    .weak  UART4_IRQHandler
    .weak  TIMER5_IRQHandler
    .weak  TIMER6_IRQHandler
    .weak  DMA1_Channel0_IRQHandler
    .weak  DMA1_Channel1_IRQHandler
    .weak  DMA1_Channel2_IRQHandler
    .weak  DMA1_Channel3_IRQHandler
    .weak  DMA1_Channel4_IRQHandler
    .weak  CAN1_TX_IRQHandler
    .weak  CAN1_RX0_IRQHandler
    .weak  CAN1_RX1_IRQHandler
    .weak  CAN1_EWMC_IRQHandler
    .weak  USBFS_IRQHandler


    .globl vector_base
vector_base:
#if defined(DOWNLOAD_MODE) && (DOWNLOAD_MODE != DOWNLOAD_MODE_FLASH)
    j _start                                                /* 0: Reserved, Jump to _start when reset for ILM/FlashXIP mode.*/
    .align LOG_REGBYTES                                     /*    Need to align 4 byte for RV32, 8 Byte for RV64 */
#else
    DECLARE_INT_HANDLER     default_intexc_handler          /* 0: Reserved, default handler for Flash download mode */
#endif
    DECLARE_INT_HANDLER     default_intexc_handler          /* 1: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 2: Reserved */
    DECLARE_INT_HANDLER     eclic_msip_handler              /* 3: Machine software interrupt */

    DECLARE_INT_HANDLER     default_intexc_handler          /* 4: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 5: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 6: Reserved */
    DECLARE_INT_HANDLER     eclic_mtip_handler              /* 7: Machine timer interrupt */

    DECLARE_INT_HANDLER     default_intexc_handler          /* 8: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 9: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 10: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 11: Reserved */

    DECLARE_INT_HANDLER     default_intexc_handler          /* 12: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 13: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 14: Reserved */
    DECLARE_INT_HANDLER     default_intexc_handler          /* 15: Reserved */

    DECLARE_INT_HANDLER     default_intexc_handler          /* 16: Reserved */
    DECLARE_INT_HANDLER     eclic_bwei_handler              /* 17: Bus Error interrupt */
    DECLARE_INT_HANDLER     eclic_pmovi_handler             /* 18: Performance Monitor */

    DECLARE_INT_HANDLER     WWDGT_IRQHandler
	DECLARE_INT_HANDLER     LVD_IRQHandler
	DECLARE_INT_HANDLER     TAMPER_IRQHandler
	DECLARE_INT_HANDLER     RTC_IRQHandler
	DECLARE_INT_HANDLER     FMC_IRQHandler
	DECLARE_INT_HANDLER     RCU_IRQHandler
	DECLARE_INT_HANDLER     EXTI0_IRQHandler
	DECLARE_INT_HANDLER     EXTI1_IRQHandler
	DECLARE_INT_HANDLER     EXTI2_IRQHandler
	DECLARE_INT_HANDLER     EXTI3_IRQHandler
	DECLARE_INT_HANDLER     EXTI4_IRQHandler
	DECLARE_INT_HANDLER     DMA0_Channel0_IRQHandler
	DECLARE_INT_HANDLER     DMA0_Channel1_IRQHandler
	DECLARE_INT_HANDLER     DMA0_Channel2_IRQHandler
	DECLARE_INT_HANDLER     DMA0_Channel3_IRQHandler
	DECLARE_INT_HANDLER     DMA0_Channel4_IRQHandler
	DECLARE_INT_HANDLER     DMA0_Channel5_IRQHandler
	DECLARE_INT_HANDLER     DMA0_Channel6_IRQHandler
	DECLARE_INT_HANDLER     ADC0_1_IRQHandler
	DECLARE_INT_HANDLER     CAN0_TX_IRQHandler
	DECLARE_INT_HANDLER     CAN0_RX0_IRQHandler
	DECLARE_INT_HANDLER     CAN0_RX1_IRQHandler
	DECLARE_INT_HANDLER     CAN0_EWMC_IRQHandler
	DECLARE_INT_HANDLER     EXTI5_9_IRQHandler
	DECLARE_INT_HANDLER     TIMER0_BRK_IRQHandler
	DECLARE_INT_HANDLER     TIMER0_UP_IRQHandler
	DECLARE_INT_HANDLER     TIMER0_TRG_CMT_IRQHandler
	DECLARE_INT_HANDLER     TIMER0_Channel_IRQHandler
	DECLARE_INT_HANDLER     TIMER1_IRQHandler
	DECLARE_INT_HANDLER     TIMER2_IRQHandler
	DECLARE_INT_HANDLER     TIMER3_IRQHandler
	DECLARE_INT_HANDLER     I2C0_EV_IRQHandler
	DECLARE_INT_HANDLER     I2C0_ER_IRQHandler
	DECLARE_INT_HANDLER     I2C1_EV_IRQHandler
	DECLARE_INT_HANDLER     I2C1_ER_IRQHandler
	DECLARE_INT_HANDLER     SPI0_IRQHandler
	DECLARE_INT_HANDLER     SPI1_IRQHandler
	DECLARE_INT_HANDLER     USART0_IRQHandler
	DECLARE_INT_HANDLER     USART1_IRQHandler
	DECLARE_INT_HANDLER     USART2_IRQHandler
	DECLARE_INT_HANDLER     EXTI10_15_IRQHandler
	DECLARE_INT_HANDLER     RTC_Alarm_IRQHandler
	DECLARE_INT_HANDLER     USBFS_WKUP_IRQHandler
    DECLARE_INT_HANDLER     default_intexc_handler
    DECLARE_INT_HANDLER     default_intexc_handler
    DECLARE_INT_HANDLER     default_intexc_handler
    DECLARE_INT_HANDLER     default_intexc_handler
	DECLARE_INT_HANDLER     default_intexc_handler
	DECLARE_INT_HANDLER     EXMC_IRQHandler
	DECLARE_INT_HANDLER     default_intexc_handler
	DECLARE_INT_HANDLER     TIMER4_IRQHandler
	DECLARE_INT_HANDLER     SPI2_IRQHandler
	DECLARE_INT_HANDLER     UART3_IRQHandler
	DECLARE_INT_HANDLER     UART4_IRQHandler
	DECLARE_INT_HANDLER     TIMER5_IRQHandler
	DECLARE_INT_HANDLER     TIMER6_IRQHandler
	DECLARE_INT_HANDLER     DMA1_Channel0_IRQHandler
	DECLARE_INT_HANDLER     DMA1_Channel1_IRQHandler
	DECLARE_INT_HANDLER     DMA1_Channel2_IRQHandler
	DECLARE_INT_HANDLER     DMA1_Channel3_IRQHandler
	DECLARE_INT_HANDLER     DMA1_Channel4_IRQHandler
    DECLARE_INT_HANDLER     default_intexc_handler
    DECLARE_INT_HANDLER     default_intexc_handler
	DECLARE_INT_HANDLER     CAN1_TX_IRQHandler
	DECLARE_INT_HANDLER     CAN1_RX0_IRQHandler
	DECLARE_INT_HANDLER     CAN1_RX1_IRQHandler
	DECLARE_INT_HANDLER     CAN1_EWMC_IRQHandler
	DECLARE_INT_HANDLER     USBFS_IRQHandler

    .section .init

    .globl _start
    .type _start,@function

/**
 * Reset Handler called on controller reset
 */
_start:
    /* ===== Startup Stage 1 ===== */
    /* Disable Global Interrupt */
    csrc CSR_MSTATUS, MSTATUS_MIE
	/* Jump to logical address first to ensure correct operation of RAM region  */
    la		a0,	_start
    li		a1,	1
	slli	a1,	a1, 29
    bleu	a1, a0, _start0800
    srli	a1,	a1, 2
    bleu	a1, a0, _start0800
    la		a0,	_start0800
    add		a0, a0, a1
	jr      a0

_start0800:
    /* Initialize GP and Stack Pointer SP */
    .option push
    .option norelax
    la gp, __global_pointer$

    .option pop
    la sp, _sp

    /*
     * Set the the NMI base mnvec to share
     * with mtvec by setting CSR_MMISC_CTL
     * bit 9 NMI_CAUSE_FFF to 1
     */
    li t0, MMISC_CTL_NMI_CAUSE_FFF
    csrs CSR_MMISC_CTL, t0

    /*
     * Intialize ECLIC vector interrupt
     * base address mtvt to vector_base
     */
    la t0, vector_base
    csrw CSR_MTVT, t0

    /*
     * Set ECLIC non-vector entry to be controlled
     * by mtvt2 CSR register.
     * Intialize ECLIC non-vector interrupt
     * base address mtvt2 to irq_entry.
     */
    la t0, irq_entry
    csrw CSR_MTVT2, t0
    csrs CSR_MTVT2, 0x1

    /*
     * Set Exception Entry MTVEC to exc_entry
     * Due to settings above, Exception and NMI
     * will share common entry.
     */
    la t0, exc_entry
    csrw CSR_MTVEC, t0

    /* Set the interrupt processing mode to ECLIC mode */
    la t0, 0x3f
    csrc CSR_MTVEC, t0
    csrs CSR_MTVEC, 0x3

    /* ===== Startup Stage 2 ===== */

#ifdef __riscv_flen
    /* Enable FPU */
    li t0, MSTATUS_FS
    csrs mstatus, t0
    csrw fcsr, x0
#endif

    /* Enable mcycle and minstret counter */
    csrci CSR_MCOUNTINHIBIT, 0x5

    /* ===== Startup Stage 3 ===== */
    /*
     * Load code section frm FLASH to ILM
     * when code LMA is different with VMA
     */
    la a0, _ilm_lma
    la a1, _ilm
    /* If the ILM phy-address same as the logic-address, then quit */
    beq a0, a1, 2f
    la a2, _eilm
    bgeu a1, a2, 2f

1:
    /* Load code section if necessary */
    lw t0, (a0)
    sw t0, (a1)
    addi a0, a0, 4
    addi a1, a1, 4
    bltu a1, a2, 1b
2:
    /* Load data section */
    la a0, _data_lma
    la a1, _data
    la a2, _edata
    bgeu a1, a2, 2f
1:
    lw t0, (a0)
    sw t0, (a1)
    addi a0, a0, 4
    addi a1, a1, 4
    bltu a1, a2, 1b
2:
    /* Clear bss section */
    la a0, __bss_start
    la a1, _end
    bgeu a0, a1, 2f
1:
    sw zero, (a0)
    addi a0, a0, 4
    bltu a0, a1, 1b
2:

    /*
     * Call vendor defined SystemInit to
     * initialize the micro-controller system
     */
    call SystemInit

    /* Call global constructors */
    la a0, __libc_fini_array
    call atexit
    /* Call C/C++ constructor start up code */
    call __libc_init_array

    /* ===== Call Main Function  ===== */
    /* argc = argv = 0 */
    li a0, 0
    li a1, 0
#ifdef RTOS_RTTHREAD
    // Call entry function when using RT-Thread
    call entry
#else
    call main
#endif

1:
    j 1b
