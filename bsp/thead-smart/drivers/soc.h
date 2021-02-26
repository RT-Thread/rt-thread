/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-20     zx.chen      CSI Core Peripheral Access Layer Header File for
 *                             CSKYSOC Device Series
 */

#ifndef _SOC_H_
#define _SOC_H_

#include <stdint.h>
#include <csi_core.h>
#include <sys_freq.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef IHS_VALUE
#define  IHS_VALUE    (20000000)
#endif

#ifndef EHS_VALUE
#define  EHS_VALUE    (20000000)
#endif


/* -------------------------  Interrupt Number Definition  ------------------------ */
typedef enum IRQn {
    NMI_EXPn                        =   -2,      /* NMI Exception */
    /* ----------------------  SmartL Specific Interrupt Numbers  --------------------- */
    Machine_Software_IRQn           =   3,      /* Machine software interrupt */
    User_Timer_IRQn                 =   4,      /* User timer interrupt */
    Supervisor_Timer_IRQn           =   5,      /* Supervisor timer interrupt */
    CORET_IRQn                      =   7,      /* core Timer Interrupt */
    Machine_External_IRQn           =   11,     /* Machine external interrupt */
    UART_IRQn                       =   16,     /* uart Interrupt */
    TIM0_IRQn                       =   18,     /* timer0 Interrupt */
    TIM1_IRQn                       =   19,     /* timer1 Interrupt */
    TIM2_IRQn                       =   20,     /* timer2 Interrupt */
    TIM3_IRQn                       =   21,     /* timer3 Interrupt */
    GPIO0_IRQn                      =   23,     /* gpio0 Interrupt */
    GPIO1_IRQn                      =   24,     /* gpio1 Interrupt */
    GPIO2_IRQn                      =   25,     /* gpio2 Interrupt */
    GPIO3_IRQn                      =   26,     /* gpio3 Interrupt */
    GPIO4_IRQn                      =   27,     /* gpio4 Interrupt */
    GPIO5_IRQn                      =   28,     /* gpio5 Interrupt */
    GPIO6_IRQn                      =   29,     /* gpio6 Interrupt */
    GPIO7_IRQn                      =   30,     /* gpio7 Interrupt */
    STIM0_IRQn                      =   31,     /* stimer0 Interrupt */
    STIM1_IRQn                      =   32,     /* stimer1 Interrupt */
    STIM2_IRQn                      =   33,     /* stimer2 Interrupt */
    STIM3_IRQn                      =   34,     /* stimer3 Interrupt */
    PAD_IRQn                        =   35,     /* pad Interrupt */
    TIM6_IRQn                       =   36,     /* timer6 Interrupt */
    TIM7_IRQn                       =   37,     /* timer7 Interrupt */
    TIM8_IRQn                       =   38,     /* timer8 Interrupt */
    TIM9_IRQn                       =   39,     /* timer9 Interrupt */
    TIM10_IRQn                      =   40,     /* timer10 Interrupt */
    TIM11_IRQn                      =   41,     /* timer11 Interrupt */
}
IRQn_Type;

/* ================================================================================ */
/* ================       Device Specific Peripheral Section       ================ */
/* ================================================================================ */

#define CONFIG_TIMER_NUM    12
#define CONFIG_USART_NUM    1
#define CONFIG_GPIO_NUM     8
#define CONFIG_GPIO_PIN_NUM 8

/* ================================================================================ */
/* ================              Peripheral memory map             ================ */
/* ================================================================================ */
/* --------------------------  CPU FPGA memory map  ------------------------------- */
#define CSKY_SRAM_BASE              (0x20000000UL)

#define CSKY_UART_BASE              (0x40015000UL)
#define CSKY_PMU_BASE               (0x40016000UL)
#define CSKY_TIMER0_BASE            (0x40011000UL)
#define CSKY_TIMER1_BASE            (0x40011014UL)
#define CSKY_TIMER2_BASE            (0x40011028UL)
#define CSKY_TIMER3_BASE            (0x4001103cUL)
#define CSKY_TIMER4_BASE            (0x40021000UL)
#define CSKY_TIMER5_BASE            (0x40021014UL)
#define CSKY_TIMER6_BASE            (0x40021028UL)
#define CSKY_TIMER7_BASE            (0x4002103cUL)
#define CSKY_TIMER8_BASE            (0x40031000UL)
#define CSKY_TIMER9_BASE            (0x40031014UL)
#define CSKY_TIMER10_BASE           (0x40031028UL)
#define CSKY_TIMER11_BASE           (0x4003103cUL)

#define CSKY_TIMER_CONTROL_BASE     (0x400110a0UL)
#define CSKY_CLK_GEN_BASE           (0x40017000UL)
#define CSKY_STIMER0_BASE           (0x40018000UL)
#define CSKY_STIMER1_BASE           (0x40018014UL)
#define CSKY_STIMER2_BASE           (0x40018028UL)
#define CSKY_STIMER3_BASE           (0x4001803cUL)
#define CSKY_STIMER_CONTROL_BASE    (0x400110a0UL)

#define CSKY_GPIOA_BASE             (0x40019000UL)
#define CSKY_GPIOA_CONTROL_BASE     (0x40019030UL)
#define CSKY_SMPU_BASE              (0x4001a000UL)

/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */
#define CSKY_UART                  ((   CSKY_UART_TypeDef *)    CSKY_UART_BASE)

#ifdef __cplusplus
}
#endif

#endif  /* _SOC_H_ */
