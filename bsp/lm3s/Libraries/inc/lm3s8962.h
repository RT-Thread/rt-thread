//*****************************************************************************
//
// lm3s8962.h - LM3S8962 Register Definitions
//
// Copyright (c) 2007-2010 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 6459 of the Stellaris Firmware Development Package.
//
//*****************************************************************************

#ifndef __LM3S8962_H__
#define __LM3S8962_H__

//*****************************************************************************
//
// Watchdog Timer registers (WATCHDOG0)
//
//*****************************************************************************
#define WATCHDOG0_LOAD_R        (*((volatile unsigned long *)0x40000000))
#define WATCHDOG0_VALUE_R       (*((volatile unsigned long *)0x40000004))
#define WATCHDOG0_CTL_R         (*((volatile unsigned long *)0x40000008))
#define WATCHDOG0_ICR_R         (*((volatile unsigned long *)0x4000000C))
#define WATCHDOG0_RIS_R         (*((volatile unsigned long *)0x40000010))
#define WATCHDOG0_MIS_R         (*((volatile unsigned long *)0x40000014))
#define WATCHDOG0_TEST_R        (*((volatile unsigned long *)0x40000418))
#define WATCHDOG0_LOCK_R        (*((volatile unsigned long *)0x40000C00))

//*****************************************************************************
//
// GPIO registers (PORTA)
//
//*****************************************************************************
#define GPIO_PORTA_DATA_BITS_R  ((volatile unsigned long *)0x40004000)
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_IS_R         (*((volatile unsigned long *)0x40004404))
#define GPIO_PORTA_IBE_R        (*((volatile unsigned long *)0x40004408))
#define GPIO_PORTA_IEV_R        (*((volatile unsigned long *)0x4000440C))
#define GPIO_PORTA_IM_R         (*((volatile unsigned long *)0x40004410))
#define GPIO_PORTA_RIS_R        (*((volatile unsigned long *)0x40004414))
#define GPIO_PORTA_MIS_R        (*((volatile unsigned long *)0x40004418))
#define GPIO_PORTA_ICR_R        (*((volatile unsigned long *)0x4000441C))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_DR2R_R       (*((volatile unsigned long *)0x40004500))
#define GPIO_PORTA_DR4R_R       (*((volatile unsigned long *)0x40004504))
#define GPIO_PORTA_DR8R_R       (*((volatile unsigned long *)0x40004508))
#define GPIO_PORTA_ODR_R        (*((volatile unsigned long *)0x4000450C))
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *)0x40004510))
#define GPIO_PORTA_PDR_R        (*((volatile unsigned long *)0x40004514))
#define GPIO_PORTA_SLR_R        (*((volatile unsigned long *)0x40004518))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_LOCK_R       (*((volatile unsigned long *)0x40004520))
#define GPIO_PORTA_CR_R         (*((volatile unsigned long *)0x40004524))

//*****************************************************************************
//
// GPIO registers (PORTB)
//
//*****************************************************************************
#define GPIO_PORTB_DATA_BITS_R  ((volatile unsigned long *)0x40005000)
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_IS_R         (*((volatile unsigned long *)0x40005404))
#define GPIO_PORTB_IBE_R        (*((volatile unsigned long *)0x40005408))
#define GPIO_PORTB_IEV_R        (*((volatile unsigned long *)0x4000540C))
#define GPIO_PORTB_IM_R         (*((volatile unsigned long *)0x40005410))
#define GPIO_PORTB_RIS_R        (*((volatile unsigned long *)0x40005414))
#define GPIO_PORTB_MIS_R        (*((volatile unsigned long *)0x40005418))
#define GPIO_PORTB_ICR_R        (*((volatile unsigned long *)0x4000541C))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_DR2R_R       (*((volatile unsigned long *)0x40005500))
#define GPIO_PORTB_DR4R_R       (*((volatile unsigned long *)0x40005504))
#define GPIO_PORTB_DR8R_R       (*((volatile unsigned long *)0x40005508))
#define GPIO_PORTB_ODR_R        (*((volatile unsigned long *)0x4000550C))
#define GPIO_PORTB_PUR_R        (*((volatile unsigned long *)0x40005510))
#define GPIO_PORTB_PDR_R        (*((volatile unsigned long *)0x40005514))
#define GPIO_PORTB_SLR_R        (*((volatile unsigned long *)0x40005518))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_LOCK_R       (*((volatile unsigned long *)0x40005520))
#define GPIO_PORTB_CR_R         (*((volatile unsigned long *)0x40005524))

//*****************************************************************************
//
// GPIO registers (PORTC)
//
//*****************************************************************************
#define GPIO_PORTC_DATA_BITS_R  ((volatile unsigned long *)0x40006000)
#define GPIO_PORTC_DATA_R       (*((volatile unsigned long *)0x400063FC))
#define GPIO_PORTC_DIR_R        (*((volatile unsigned long *)0x40006400))
#define GPIO_PORTC_IS_R         (*((volatile unsigned long *)0x40006404))
#define GPIO_PORTC_IBE_R        (*((volatile unsigned long *)0x40006408))
#define GPIO_PORTC_IEV_R        (*((volatile unsigned long *)0x4000640C))
#define GPIO_PORTC_IM_R         (*((volatile unsigned long *)0x40006410))
#define GPIO_PORTC_RIS_R        (*((volatile unsigned long *)0x40006414))
#define GPIO_PORTC_MIS_R        (*((volatile unsigned long *)0x40006418))
#define GPIO_PORTC_ICR_R        (*((volatile unsigned long *)0x4000641C))
#define GPIO_PORTC_AFSEL_R      (*((volatile unsigned long *)0x40006420))
#define GPIO_PORTC_DR2R_R       (*((volatile unsigned long *)0x40006500))
#define GPIO_PORTC_DR4R_R       (*((volatile unsigned long *)0x40006504))
#define GPIO_PORTC_DR8R_R       (*((volatile unsigned long *)0x40006508))
#define GPIO_PORTC_ODR_R        (*((volatile unsigned long *)0x4000650C))
#define GPIO_PORTC_PUR_R        (*((volatile unsigned long *)0x40006510))
#define GPIO_PORTC_PDR_R        (*((volatile unsigned long *)0x40006514))
#define GPIO_PORTC_SLR_R        (*((volatile unsigned long *)0x40006518))
#define GPIO_PORTC_DEN_R        (*((volatile unsigned long *)0x4000651C))
#define GPIO_PORTC_LOCK_R       (*((volatile unsigned long *)0x40006520))
#define GPIO_PORTC_CR_R         (*((volatile unsigned long *)0x40006524))

//*****************************************************************************
//
// GPIO registers (PORTD)
//
//*****************************************************************************
#define GPIO_PORTD_DATA_BITS_R  ((volatile unsigned long *)0x40007000)
#define GPIO_PORTD_DATA_R       (*((volatile unsigned long *)0x400073FC))
#define GPIO_PORTD_DIR_R        (*((volatile unsigned long *)0x40007400))
#define GPIO_PORTD_IS_R         (*((volatile unsigned long *)0x40007404))
#define GPIO_PORTD_IBE_R        (*((volatile unsigned long *)0x40007408))
#define GPIO_PORTD_IEV_R        (*((volatile unsigned long *)0x4000740C))
#define GPIO_PORTD_IM_R         (*((volatile unsigned long *)0x40007410))
#define GPIO_PORTD_RIS_R        (*((volatile unsigned long *)0x40007414))
#define GPIO_PORTD_MIS_R        (*((volatile unsigned long *)0x40007418))
#define GPIO_PORTD_ICR_R        (*((volatile unsigned long *)0x4000741C))
#define GPIO_PORTD_AFSEL_R      (*((volatile unsigned long *)0x40007420))
#define GPIO_PORTD_DR2R_R       (*((volatile unsigned long *)0x40007500))
#define GPIO_PORTD_DR4R_R       (*((volatile unsigned long *)0x40007504))
#define GPIO_PORTD_DR8R_R       (*((volatile unsigned long *)0x40007508))
#define GPIO_PORTD_ODR_R        (*((volatile unsigned long *)0x4000750C))
#define GPIO_PORTD_PUR_R        (*((volatile unsigned long *)0x40007510))
#define GPIO_PORTD_PDR_R        (*((volatile unsigned long *)0x40007514))
#define GPIO_PORTD_SLR_R        (*((volatile unsigned long *)0x40007518))
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *)0x4000751C))
#define GPIO_PORTD_LOCK_R       (*((volatile unsigned long *)0x40007520))
#define GPIO_PORTD_CR_R         (*((volatile unsigned long *)0x40007524))

//*****************************************************************************
//
// SSI registers (SSI0)
//
//*****************************************************************************
#define SSI0_CR0_R              (*((volatile unsigned long *)0x40008000))
#define SSI0_CR1_R              (*((volatile unsigned long *)0x40008004))
#define SSI0_DR_R               (*((volatile unsigned long *)0x40008008))
#define SSI0_SR_R               (*((volatile unsigned long *)0x4000800C))
#define SSI0_CPSR_R             (*((volatile unsigned long *)0x40008010))
#define SSI0_IM_R               (*((volatile unsigned long *)0x40008014))
#define SSI0_RIS_R              (*((volatile unsigned long *)0x40008018))
#define SSI0_MIS_R              (*((volatile unsigned long *)0x4000801C))
#define SSI0_ICR_R              (*((volatile unsigned long *)0x40008020))

//*****************************************************************************
//
// UART registers (UART0)
//
//*****************************************************************************
#define UART0_DR_R              (*((volatile unsigned long *)0x4000C000))
#define UART0_RSR_R             (*((volatile unsigned long *)0x4000C004))
#define UART0_ECR_R             (*((volatile unsigned long *)0x4000C004))
#define UART0_FR_R              (*((volatile unsigned long *)0x4000C018))
#define UART0_ILPR_R            (*((volatile unsigned long *)0x4000C020))
#define UART0_IBRD_R            (*((volatile unsigned long *)0x4000C024))
#define UART0_FBRD_R            (*((volatile unsigned long *)0x4000C028))
#define UART0_LCRH_R            (*((volatile unsigned long *)0x4000C02C))
#define UART0_CTL_R             (*((volatile unsigned long *)0x4000C030))
#define UART0_IFLS_R            (*((volatile unsigned long *)0x4000C034))
#define UART0_IM_R              (*((volatile unsigned long *)0x4000C038))
#define UART0_RIS_R             (*((volatile unsigned long *)0x4000C03C))
#define UART0_MIS_R             (*((volatile unsigned long *)0x4000C040))
#define UART0_ICR_R             (*((volatile unsigned long *)0x4000C044))

//*****************************************************************************
//
// UART registers (UART1)
//
//*****************************************************************************
#define UART1_DR_R              (*((volatile unsigned long *)0x4000D000))
#define UART1_RSR_R             (*((volatile unsigned long *)0x4000D004))
#define UART1_ECR_R             (*((volatile unsigned long *)0x4000D004))
#define UART1_FR_R              (*((volatile unsigned long *)0x4000D018))
#define UART1_ILPR_R            (*((volatile unsigned long *)0x4000D020))
#define UART1_IBRD_R            (*((volatile unsigned long *)0x4000D024))
#define UART1_FBRD_R            (*((volatile unsigned long *)0x4000D028))
#define UART1_LCRH_R            (*((volatile unsigned long *)0x4000D02C))
#define UART1_CTL_R             (*((volatile unsigned long *)0x4000D030))
#define UART1_IFLS_R            (*((volatile unsigned long *)0x4000D034))
#define UART1_IM_R              (*((volatile unsigned long *)0x4000D038))
#define UART1_RIS_R             (*((volatile unsigned long *)0x4000D03C))
#define UART1_MIS_R             (*((volatile unsigned long *)0x4000D040))
#define UART1_ICR_R             (*((volatile unsigned long *)0x4000D044))

//*****************************************************************************
//
// I2C registers (I2C0 MASTER)
//
//*****************************************************************************
#define I2C0_MASTER_MSA_R       (*((volatile unsigned long *)0x40020000))
#define I2C0_MASTER_SOAR_R      (*((volatile unsigned long *)0x40020000))
#define I2C0_MASTER_SCSR_R      (*((volatile unsigned long *)0x40020004))
#define I2C0_MASTER_MCS_R       (*((volatile unsigned long *)0x40020004))
#define I2C0_MASTER_SDR_R       (*((volatile unsigned long *)0x40020008))
#define I2C0_MASTER_MDR_R       (*((volatile unsigned long *)0x40020008))
#define I2C0_MASTER_MTPR_R      (*((volatile unsigned long *)0x4002000C))
#define I2C0_MASTER_SIMR_R      (*((volatile unsigned long *)0x4002000C))
#define I2C0_MASTER_SRIS_R      (*((volatile unsigned long *)0x40020010))
#define I2C0_MASTER_MIMR_R      (*((volatile unsigned long *)0x40020010))
#define I2C0_MASTER_MRIS_R      (*((volatile unsigned long *)0x40020014))
#define I2C0_MASTER_SMIS_R      (*((volatile unsigned long *)0x40020014))
#define I2C0_MASTER_SICR_R      (*((volatile unsigned long *)0x40020018))
#define I2C0_MASTER_MMIS_R      (*((volatile unsigned long *)0x40020018))
#define I2C0_MASTER_MICR_R      (*((volatile unsigned long *)0x4002001C))
#define I2C0_MASTER_MCR_R       (*((volatile unsigned long *)0x40020020))

//*****************************************************************************
//
// I2C registers (I2C0 SLAVE)
//
//*****************************************************************************
#define I2C0_SLAVE_MSA_R        (*((volatile unsigned long *)0x40020800))
#define I2C0_SLAVE_SOAR_R       (*((volatile unsigned long *)0x40020800))
#define I2C0_SLAVE_SCSR_R       (*((volatile unsigned long *)0x40020804))
#define I2C0_SLAVE_MCS_R        (*((volatile unsigned long *)0x40020804))
#define I2C0_SLAVE_SDR_R        (*((volatile unsigned long *)0x40020808))
#define I2C0_SLAVE_MDR_R        (*((volatile unsigned long *)0x40020808))
#define I2C0_SLAVE_MTPR_R       (*((volatile unsigned long *)0x4002080C))
#define I2C0_SLAVE_SIMR_R       (*((volatile unsigned long *)0x4002080C))
#define I2C0_SLAVE_SRIS_R       (*((volatile unsigned long *)0x40020810))
#define I2C0_SLAVE_MIMR_R       (*((volatile unsigned long *)0x40020810))
#define I2C0_SLAVE_MRIS_R       (*((volatile unsigned long *)0x40020814))
#define I2C0_SLAVE_SMIS_R       (*((volatile unsigned long *)0x40020814))
#define I2C0_SLAVE_SICR_R       (*((volatile unsigned long *)0x40020818))
#define I2C0_SLAVE_MMIS_R       (*((volatile unsigned long *)0x40020818))
#define I2C0_SLAVE_MICR_R       (*((volatile unsigned long *)0x4002081C))
#define I2C0_SLAVE_MCR_R        (*((volatile unsigned long *)0x40020820))

//*****************************************************************************
//
// GPIO registers (PORTE)
//
//*****************************************************************************
#define GPIO_PORTE_DATA_BITS_R  ((volatile unsigned long *)0x40024000)
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_IS_R         (*((volatile unsigned long *)0x40024404))
#define GPIO_PORTE_IBE_R        (*((volatile unsigned long *)0x40024408))
#define GPIO_PORTE_IEV_R        (*((volatile unsigned long *)0x4002440C))
#define GPIO_PORTE_IM_R         (*((volatile unsigned long *)0x40024410))
#define GPIO_PORTE_RIS_R        (*((volatile unsigned long *)0x40024414))
#define GPIO_PORTE_MIS_R        (*((volatile unsigned long *)0x40024418))
#define GPIO_PORTE_ICR_R        (*((volatile unsigned long *)0x4002441C))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DR2R_R       (*((volatile unsigned long *)0x40024500))
#define GPIO_PORTE_DR4R_R       (*((volatile unsigned long *)0x40024504))
#define GPIO_PORTE_DR8R_R       (*((volatile unsigned long *)0x40024508))
#define GPIO_PORTE_ODR_R        (*((volatile unsigned long *)0x4002450C))
#define GPIO_PORTE_PUR_R        (*((volatile unsigned long *)0x40024510))
#define GPIO_PORTE_PDR_R        (*((volatile unsigned long *)0x40024514))
#define GPIO_PORTE_SLR_R        (*((volatile unsigned long *)0x40024518))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_LOCK_R       (*((volatile unsigned long *)0x40024520))
#define GPIO_PORTE_CR_R         (*((volatile unsigned long *)0x40024524))

//*****************************************************************************
//
// GPIO registers (PORTF)
//
//*****************************************************************************
#define GPIO_PORTF_DATA_BITS_R  ((volatile unsigned long *)0x40025000)
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_IS_R         (*((volatile unsigned long *)0x40025404))
#define GPIO_PORTF_IBE_R        (*((volatile unsigned long *)0x40025408))
#define GPIO_PORTF_IEV_R        (*((volatile unsigned long *)0x4002540C))
#define GPIO_PORTF_IM_R         (*((volatile unsigned long *)0x40025410))
#define GPIO_PORTF_RIS_R        (*((volatile unsigned long *)0x40025414))
#define GPIO_PORTF_MIS_R        (*((volatile unsigned long *)0x40025418))
#define GPIO_PORTF_ICR_R        (*((volatile unsigned long *)0x4002541C))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_DR2R_R       (*((volatile unsigned long *)0x40025500))
#define GPIO_PORTF_DR4R_R       (*((volatile unsigned long *)0x40025504))
#define GPIO_PORTF_DR8R_R       (*((volatile unsigned long *)0x40025508))
#define GPIO_PORTF_ODR_R        (*((volatile unsigned long *)0x4002550C))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_PDR_R        (*((volatile unsigned long *)0x40025514))
#define GPIO_PORTF_SLR_R        (*((volatile unsigned long *)0x40025518))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))

//*****************************************************************************
//
// GPIO registers (PORTG)
//
//*****************************************************************************
#define GPIO_PORTG_DATA_BITS_R  ((volatile unsigned long *)0x40026000)
#define GPIO_PORTG_DATA_R       (*((volatile unsigned long *)0x400263FC))
#define GPIO_PORTG_DIR_R        (*((volatile unsigned long *)0x40026400))
#define GPIO_PORTG_IS_R         (*((volatile unsigned long *)0x40026404))
#define GPIO_PORTG_IBE_R        (*((volatile unsigned long *)0x40026408))
#define GPIO_PORTG_IEV_R        (*((volatile unsigned long *)0x4002640C))
#define GPIO_PORTG_IM_R         (*((volatile unsigned long *)0x40026410))
#define GPIO_PORTG_RIS_R        (*((volatile unsigned long *)0x40026414))
#define GPIO_PORTG_MIS_R        (*((volatile unsigned long *)0x40026418))
#define GPIO_PORTG_ICR_R        (*((volatile unsigned long *)0x4002641C))
#define GPIO_PORTG_AFSEL_R      (*((volatile unsigned long *)0x40026420))
#define GPIO_PORTG_DR2R_R       (*((volatile unsigned long *)0x40026500))
#define GPIO_PORTG_DR4R_R       (*((volatile unsigned long *)0x40026504))
#define GPIO_PORTG_DR8R_R       (*((volatile unsigned long *)0x40026508))
#define GPIO_PORTG_ODR_R        (*((volatile unsigned long *)0x4002650C))
#define GPIO_PORTG_PUR_R        (*((volatile unsigned long *)0x40026510))
#define GPIO_PORTG_PDR_R        (*((volatile unsigned long *)0x40026514))
#define GPIO_PORTG_SLR_R        (*((volatile unsigned long *)0x40026518))
#define GPIO_PORTG_DEN_R        (*((volatile unsigned long *)0x4002651C))
#define GPIO_PORTG_LOCK_R       (*((volatile unsigned long *)0x40026520))
#define GPIO_PORTG_CR_R         (*((volatile unsigned long *)0x40026524))

//*****************************************************************************
//
// PWM registers (PWM)
//
//*****************************************************************************
#define PWM_CTL_R               (*((volatile unsigned long *)0x40028000))
#define PWM_SYNC_R              (*((volatile unsigned long *)0x40028004))
#define PWM_ENABLE_R            (*((volatile unsigned long *)0x40028008))
#define PWM_INVERT_R            (*((volatile unsigned long *)0x4002800C))
#define PWM_FAULT_R             (*((volatile unsigned long *)0x40028010))
#define PWM_INTEN_R             (*((volatile unsigned long *)0x40028014))
#define PWM_RIS_R               (*((volatile unsigned long *)0x40028018))
#define PWM_ISC_R               (*((volatile unsigned long *)0x4002801C))
#define PWM_STATUS_R            (*((volatile unsigned long *)0x40028020))
#define PWM_0_CTL_R             (*((volatile unsigned long *)0x40028040))
#define PWM_0_INTEN_R           (*((volatile unsigned long *)0x40028044))
#define PWM_0_RIS_R             (*((volatile unsigned long *)0x40028048))
#define PWM_0_ISC_R             (*((volatile unsigned long *)0x4002804C))
#define PWM_0_LOAD_R            (*((volatile unsigned long *)0x40028050))
#define PWM_0_COUNT_R           (*((volatile unsigned long *)0x40028054))
#define PWM_0_CMPA_R            (*((volatile unsigned long *)0x40028058))
#define PWM_0_CMPB_R            (*((volatile unsigned long *)0x4002805C))
#define PWM_0_GENA_R            (*((volatile unsigned long *)0x40028060))
#define PWM_0_GENB_R            (*((volatile unsigned long *)0x40028064))
#define PWM_0_DBCTL_R           (*((volatile unsigned long *)0x40028068))
#define PWM_0_DBRISE_R          (*((volatile unsigned long *)0x4002806C))
#define PWM_0_DBFALL_R          (*((volatile unsigned long *)0x40028070))
#define PWM_1_CTL_R             (*((volatile unsigned long *)0x40028080))
#define PWM_1_INTEN_R           (*((volatile unsigned long *)0x40028084))
#define PWM_1_RIS_R             (*((volatile unsigned long *)0x40028088))
#define PWM_1_ISC_R             (*((volatile unsigned long *)0x4002808C))
#define PWM_1_LOAD_R            (*((volatile unsigned long *)0x40028090))
#define PWM_1_COUNT_R           (*((volatile unsigned long *)0x40028094))
#define PWM_1_CMPA_R            (*((volatile unsigned long *)0x40028098))
#define PWM_1_CMPB_R            (*((volatile unsigned long *)0x4002809C))
#define PWM_1_GENA_R            (*((volatile unsigned long *)0x400280A0))
#define PWM_1_GENB_R            (*((volatile unsigned long *)0x400280A4))
#define PWM_1_DBCTL_R           (*((volatile unsigned long *)0x400280A8))
#define PWM_1_DBRISE_R          (*((volatile unsigned long *)0x400280AC))
#define PWM_1_DBFALL_R          (*((volatile unsigned long *)0x400280B0))
#define PWM_2_CTL_R             (*((volatile unsigned long *)0x400280C0))
#define PWM_2_INTEN_R           (*((volatile unsigned long *)0x400280C4))
#define PWM_2_RIS_R             (*((volatile unsigned long *)0x400280C8))
#define PWM_2_ISC_R             (*((volatile unsigned long *)0x400280CC))
#define PWM_2_LOAD_R            (*((volatile unsigned long *)0x400280D0))
#define PWM_2_COUNT_R           (*((volatile unsigned long *)0x400280D4))
#define PWM_2_CMPA_R            (*((volatile unsigned long *)0x400280D8))
#define PWM_2_CMPB_R            (*((volatile unsigned long *)0x400280DC))
#define PWM_2_GENA_R            (*((volatile unsigned long *)0x400280E0))
#define PWM_2_GENB_R            (*((volatile unsigned long *)0x400280E4))
#define PWM_2_DBCTL_R           (*((volatile unsigned long *)0x400280E8))
#define PWM_2_DBRISE_R          (*((volatile unsigned long *)0x400280EC))
#define PWM_2_DBFALL_R          (*((volatile unsigned long *)0x400280F0))

//*****************************************************************************
//
// QEI registers (QEI0)
//
//*****************************************************************************
#define QEI0_CTL_R              (*((volatile unsigned long *)0x4002C000))
#define QEI0_STAT_R             (*((volatile unsigned long *)0x4002C004))
#define QEI0_POS_R              (*((volatile unsigned long *)0x4002C008))
#define QEI0_MAXPOS_R           (*((volatile unsigned long *)0x4002C00C))
#define QEI0_LOAD_R             (*((volatile unsigned long *)0x4002C010))
#define QEI0_TIME_R             (*((volatile unsigned long *)0x4002C014))
#define QEI0_COUNT_R            (*((volatile unsigned long *)0x4002C018))
#define QEI0_SPEED_R            (*((volatile unsigned long *)0x4002C01C))
#define QEI0_INTEN_R            (*((volatile unsigned long *)0x4002C020))
#define QEI0_RIS_R              (*((volatile unsigned long *)0x4002C024))
#define QEI0_ISC_R              (*((volatile unsigned long *)0x4002C028))

//*****************************************************************************
//
// QEI registers (QEI1)
//
//*****************************************************************************
#define QEI1_CTL_R              (*((volatile unsigned long *)0x4002D000))
#define QEI1_STAT_R             (*((volatile unsigned long *)0x4002D004))
#define QEI1_POS_R              (*((volatile unsigned long *)0x4002D008))
#define QEI1_MAXPOS_R           (*((volatile unsigned long *)0x4002D00C))
#define QEI1_LOAD_R             (*((volatile unsigned long *)0x4002D010))
#define QEI1_TIME_R             (*((volatile unsigned long *)0x4002D014))
#define QEI1_COUNT_R            (*((volatile unsigned long *)0x4002D018))
#define QEI1_SPEED_R            (*((volatile unsigned long *)0x4002D01C))
#define QEI1_INTEN_R            (*((volatile unsigned long *)0x4002D020))
#define QEI1_RIS_R              (*((volatile unsigned long *)0x4002D024))
#define QEI1_ISC_R              (*((volatile unsigned long *)0x4002D028))

//*****************************************************************************
//
// Timer registers (TIMER0)
//
//*****************************************************************************
#define TIMER0_CFG_R            (*((volatile unsigned long *)0x40030000))
#define TIMER0_TAMR_R           (*((volatile unsigned long *)0x40030004))
#define TIMER0_TBMR_R           (*((volatile unsigned long *)0x40030008))
#define TIMER0_CTL_R            (*((volatile unsigned long *)0x4003000C))
#define TIMER0_IMR_R            (*((volatile unsigned long *)0x40030018))
#define TIMER0_RIS_R            (*((volatile unsigned long *)0x4003001C))
#define TIMER0_MIS_R            (*((volatile unsigned long *)0x40030020))
#define TIMER0_ICR_R            (*((volatile unsigned long *)0x40030024))
#define TIMER0_TAILR_R          (*((volatile unsigned long *)0x40030028))
#define TIMER0_TBILR_R          (*((volatile unsigned long *)0x4003002C))
#define TIMER0_TAMATCHR_R       (*((volatile unsigned long *)0x40030030))
#define TIMER0_TBMATCHR_R       (*((volatile unsigned long *)0x40030034))
#define TIMER0_TAPR_R           (*((volatile unsigned long *)0x40030038))
#define TIMER0_TBPR_R           (*((volatile unsigned long *)0x4003003C))
#define TIMER0_TAPMR_R          (*((volatile unsigned long *)0x40030040))
#define TIMER0_TBPMR_R          (*((volatile unsigned long *)0x40030044))
#define TIMER0_TAR_R            (*((volatile unsigned long *)0x40030048))
#define TIMER0_TBR_R            (*((volatile unsigned long *)0x4003004C))

//*****************************************************************************
//
// Timer registers (TIMER1)
//
//*****************************************************************************
#define TIMER1_CFG_R            (*((volatile unsigned long *)0x40031000))
#define TIMER1_TAMR_R           (*((volatile unsigned long *)0x40031004))
#define TIMER1_TBMR_R           (*((volatile unsigned long *)0x40031008))
#define TIMER1_CTL_R            (*((volatile unsigned long *)0x4003100C))
#define TIMER1_IMR_R            (*((volatile unsigned long *)0x40031018))
#define TIMER1_RIS_R            (*((volatile unsigned long *)0x4003101C))
#define TIMER1_MIS_R            (*((volatile unsigned long *)0x40031020))
#define TIMER1_ICR_R            (*((volatile unsigned long *)0x40031024))
#define TIMER1_TAILR_R          (*((volatile unsigned long *)0x40031028))
#define TIMER1_TBILR_R          (*((volatile unsigned long *)0x4003102C))
#define TIMER1_TAMATCHR_R       (*((volatile unsigned long *)0x40031030))
#define TIMER1_TBMATCHR_R       (*((volatile unsigned long *)0x40031034))
#define TIMER1_TAPR_R           (*((volatile unsigned long *)0x40031038))
#define TIMER1_TBPR_R           (*((volatile unsigned long *)0x4003103C))
#define TIMER1_TAPMR_R          (*((volatile unsigned long *)0x40031040))
#define TIMER1_TBPMR_R          (*((volatile unsigned long *)0x40031044))
#define TIMER1_TAR_R            (*((volatile unsigned long *)0x40031048))
#define TIMER1_TBR_R            (*((volatile unsigned long *)0x4003104C))

//*****************************************************************************
//
// Timer registers (TIMER2)
//
//*****************************************************************************
#define TIMER2_CFG_R            (*((volatile unsigned long *)0x40032000))
#define TIMER2_TAMR_R           (*((volatile unsigned long *)0x40032004))
#define TIMER2_TBMR_R           (*((volatile unsigned long *)0x40032008))
#define TIMER2_CTL_R            (*((volatile unsigned long *)0x4003200C))
#define TIMER2_IMR_R            (*((volatile unsigned long *)0x40032018))
#define TIMER2_RIS_R            (*((volatile unsigned long *)0x4003201C))
#define TIMER2_MIS_R            (*((volatile unsigned long *)0x40032020))
#define TIMER2_ICR_R            (*((volatile unsigned long *)0x40032024))
#define TIMER2_TAILR_R          (*((volatile unsigned long *)0x40032028))
#define TIMER2_TBILR_R          (*((volatile unsigned long *)0x4003202C))
#define TIMER2_TAMATCHR_R       (*((volatile unsigned long *)0x40032030))
#define TIMER2_TBMATCHR_R       (*((volatile unsigned long *)0x40032034))
#define TIMER2_TAPR_R           (*((volatile unsigned long *)0x40032038))
#define TIMER2_TBPR_R           (*((volatile unsigned long *)0x4003203C))
#define TIMER2_TAPMR_R          (*((volatile unsigned long *)0x40032040))
#define TIMER2_TBPMR_R          (*((volatile unsigned long *)0x40032044))
#define TIMER2_TAR_R            (*((volatile unsigned long *)0x40032048))
#define TIMER2_TBR_R            (*((volatile unsigned long *)0x4003204C))

//*****************************************************************************
//
// Timer registers (TIMER3)
//
//*****************************************************************************
#define TIMER3_CFG_R            (*((volatile unsigned long *)0x40033000))
#define TIMER3_TAMR_R           (*((volatile unsigned long *)0x40033004))
#define TIMER3_TBMR_R           (*((volatile unsigned long *)0x40033008))
#define TIMER3_CTL_R            (*((volatile unsigned long *)0x4003300C))
#define TIMER3_IMR_R            (*((volatile unsigned long *)0x40033018))
#define TIMER3_RIS_R            (*((volatile unsigned long *)0x4003301C))
#define TIMER3_MIS_R            (*((volatile unsigned long *)0x40033020))
#define TIMER3_ICR_R            (*((volatile unsigned long *)0x40033024))
#define TIMER3_TAILR_R          (*((volatile unsigned long *)0x40033028))
#define TIMER3_TBILR_R          (*((volatile unsigned long *)0x4003302C))
#define TIMER3_TAMATCHR_R       (*((volatile unsigned long *)0x40033030))
#define TIMER3_TBMATCHR_R       (*((volatile unsigned long *)0x40033034))
#define TIMER3_TAPR_R           (*((volatile unsigned long *)0x40033038))
#define TIMER3_TBPR_R           (*((volatile unsigned long *)0x4003303C))
#define TIMER3_TAPMR_R          (*((volatile unsigned long *)0x40033040))
#define TIMER3_TBPMR_R          (*((volatile unsigned long *)0x40033044))
#define TIMER3_TAR_R            (*((volatile unsigned long *)0x40033048))
#define TIMER3_TBR_R            (*((volatile unsigned long *)0x4003304C))

//*****************************************************************************
//
// ADC registers (ADC0)
//
//*****************************************************************************
#define ADC0_ACTSS_R            (*((volatile unsigned long *)0x40038000))
#define ADC0_RIS_R              (*((volatile unsigned long *)0x40038004))
#define ADC0_IM_R               (*((volatile unsigned long *)0x40038008))
#define ADC0_ISC_R              (*((volatile unsigned long *)0x4003800C))
#define ADC0_OSTAT_R            (*((volatile unsigned long *)0x40038010))
#define ADC0_EMUX_R             (*((volatile unsigned long *)0x40038014))
#define ADC0_USTAT_R            (*((volatile unsigned long *)0x40038018))
#define ADC0_SSPRI_R            (*((volatile unsigned long *)0x40038020))
#define ADC0_PSSI_R             (*((volatile unsigned long *)0x40038028))
#define ADC0_SAC_R              (*((volatile unsigned long *)0x40038030))
#define ADC0_SSMUX0_R           (*((volatile unsigned long *)0x40038040))
#define ADC0_SSCTL0_R           (*((volatile unsigned long *)0x40038044))
#define ADC0_SSFIFO0_R          (*((volatile unsigned long *)0x40038048))
#define ADC0_SSFSTAT0_R         (*((volatile unsigned long *)0x4003804C))
#define ADC0_SSMUX1_R           (*((volatile unsigned long *)0x40038060))
#define ADC0_SSCTL1_R           (*((volatile unsigned long *)0x40038064))
#define ADC0_SSFIFO1_R          (*((volatile unsigned long *)0x40038068))
#define ADC0_SSFSTAT1_R         (*((volatile unsigned long *)0x4003806C))
#define ADC0_SSMUX2_R           (*((volatile unsigned long *)0x40038080))
#define ADC0_SSCTL2_R           (*((volatile unsigned long *)0x40038084))
#define ADC0_SSFIFO2_R          (*((volatile unsigned long *)0x40038088))
#define ADC0_SSFSTAT2_R         (*((volatile unsigned long *)0x4003808C))
#define ADC0_SSMUX3_R           (*((volatile unsigned long *)0x400380A0))
#define ADC0_SSCTL3_R           (*((volatile unsigned long *)0x400380A4))
#define ADC0_SSFIFO3_R          (*((volatile unsigned long *)0x400380A8))
#define ADC0_SSFSTAT3_R         (*((volatile unsigned long *)0x400380AC))
#define ADC0_TMLB_R             (*((volatile unsigned long *)0x40038100))

//*****************************************************************************
//
// Comparator registers (COMP)
//
//*****************************************************************************
#define COMP_ACMIS_R            (*((volatile unsigned long *)0x4003C000))
#define COMP_ACRIS_R            (*((volatile unsigned long *)0x4003C004))
#define COMP_ACINTEN_R          (*((volatile unsigned long *)0x4003C008))
#define COMP_ACREFCTL_R         (*((volatile unsigned long *)0x4003C010))
#define COMP_ACSTAT0_R          (*((volatile unsigned long *)0x4003C020))
#define COMP_ACCTL0_R           (*((volatile unsigned long *)0x4003C024))

//*****************************************************************************
//
// CAN registers (CAN0)
//
//*****************************************************************************
#define CAN0_CTL_R              (*((volatile unsigned long *)0x40040000))
#define CAN0_STS_R              (*((volatile unsigned long *)0x40040004))
#define CAN0_ERR_R              (*((volatile unsigned long *)0x40040008))
#define CAN0_BIT_R              (*((volatile unsigned long *)0x4004000C))
#define CAN0_INT_R              (*((volatile unsigned long *)0x40040010))
#define CAN0_TST_R              (*((volatile unsigned long *)0x40040014))
#define CAN0_BRPE_R             (*((volatile unsigned long *)0x40040018))
#define CAN0_IF1CRQ_R           (*((volatile unsigned long *)0x40040020))
#define CAN0_IF1CMSK_R          (*((volatile unsigned long *)0x40040024))
#define CAN0_IF1MSK1_R          (*((volatile unsigned long *)0x40040028))
#define CAN0_IF1MSK2_R          (*((volatile unsigned long *)0x4004002C))
#define CAN0_IF1ARB1_R          (*((volatile unsigned long *)0x40040030))
#define CAN0_IF1ARB2_R          (*((volatile unsigned long *)0x40040034))
#define CAN0_IF1MCTL_R          (*((volatile unsigned long *)0x40040038))
#define CAN0_IF1DA1_R           (*((volatile unsigned long *)0x4004003C))
#define CAN0_IF1DA2_R           (*((volatile unsigned long *)0x40040040))
#define CAN0_IF1DB1_R           (*((volatile unsigned long *)0x40040044))
#define CAN0_IF1DB2_R           (*((volatile unsigned long *)0x40040048))
#define CAN0_IF2CRQ_R           (*((volatile unsigned long *)0x40040080))
#define CAN0_IF2CMSK_R          (*((volatile unsigned long *)0x40040084))
#define CAN0_IF2MSK1_R          (*((volatile unsigned long *)0x40040088))
#define CAN0_IF2MSK2_R          (*((volatile unsigned long *)0x4004008C))
#define CAN0_IF2ARB1_R          (*((volatile unsigned long *)0x40040090))
#define CAN0_IF2ARB2_R          (*((volatile unsigned long *)0x40040094))
#define CAN0_IF2MCTL_R          (*((volatile unsigned long *)0x40040098))
#define CAN0_IF2DA1_R           (*((volatile unsigned long *)0x4004009C))
#define CAN0_IF2DA2_R           (*((volatile unsigned long *)0x400400A0))
#define CAN0_IF2DB1_R           (*((volatile unsigned long *)0x400400A4))
#define CAN0_IF2DB2_R           (*((volatile unsigned long *)0x400400A8))
#define CAN0_TXRQ1_R            (*((volatile unsigned long *)0x40040100))
#define CAN0_TXRQ2_R            (*((volatile unsigned long *)0x40040104))
#define CAN0_NWDA1_R            (*((volatile unsigned long *)0x40040120))
#define CAN0_NWDA2_R            (*((volatile unsigned long *)0x40040124))
#define CAN0_MSG1INT_R          (*((volatile unsigned long *)0x40040140))
#define CAN0_MSG2INT_R          (*((volatile unsigned long *)0x40040144))
#define CAN0_MSG1VAL_R          (*((volatile unsigned long *)0x40040160))
#define CAN0_MSG2VAL_R          (*((volatile unsigned long *)0x40040164))

//*****************************************************************************
//
// Ethernet MAC registers (MAC)
//
//*****************************************************************************
#define MAC_RIS_R               (*((volatile unsigned long *)0x40048000))
#define MAC_IACK_R              (*((volatile unsigned long *)0x40048000))
#define MAC_IM_R                (*((volatile unsigned long *)0x40048004))
#define MAC_RCTL_R              (*((volatile unsigned long *)0x40048008))
#define MAC_TCTL_R              (*((volatile unsigned long *)0x4004800C))
#define MAC_DATA_R              (*((volatile unsigned long *)0x40048010))
#define MAC_IA0_R               (*((volatile unsigned long *)0x40048014))
#define MAC_IA1_R               (*((volatile unsigned long *)0x40048018))
#define MAC_THR_R               (*((volatile unsigned long *)0x4004801C))
#define MAC_MCTL_R              (*((volatile unsigned long *)0x40048020))
#define MAC_MDV_R               (*((volatile unsigned long *)0x40048024))
#define MAC_MTXD_R              (*((volatile unsigned long *)0x4004802C))
#define MAC_MRXD_R              (*((volatile unsigned long *)0x40048030))
#define MAC_NP_R                (*((volatile unsigned long *)0x40048034))
#define MAC_TR_R                (*((volatile unsigned long *)0x40048038))
#define MAC_TS_R                (*((volatile unsigned long *)0x4004803C))

//*****************************************************************************
//
// Ethernet Controller PHY registers (MAC)
//
//*****************************************************************************
#define PHY_MR0                 0x00000000  // Ethernet PHY Management Register
                                            // 0 - Control
#define PHY_MR1                 0x00000001  // Ethernet PHY Management Register
                                            // 1 - Status
#define PHY_MR2                 0x00000002  // Ethernet PHY Management Register
                                            // 2 - PHY Identifier 1
#define PHY_MR3                 0x00000003  // Ethernet PHY Management Register
                                            // 3 - PHY Identifier 2
#define PHY_MR4                 0x00000004  // Ethernet PHY Management Register
                                            // 4 - Auto-Negotiation
                                            // Advertisement
#define PHY_MR5                 0x00000005  // Ethernet PHY Management Register
                                            // 5 - Auto-Negotiation Link
                                            // Partner Base Page Ability
#define PHY_MR6                 0x00000006  // Ethernet PHY Management Register
                                            // 6 - Auto-Negotiation Expansion
#define PHY_MR16                0x00000010  // Ethernet PHY Management Register
                                            // 16 - Vendor-Specific
#define PHY_MR17                0x00000011  // Ethernet PHY Management Register
                                            // 17 - Mode Control/Status
#define PHY_MR18                0x00000012  // Ethernet PHY Management Register
                                            // 18 - Diagnostic
#define PHY_MR19                0x00000013  // Ethernet PHY Management Register
                                            // 19 - Transceiver Control
#define PHY_MR23                0x00000017  // Ethernet PHY Management Register
                                            // 23 - LED Configuration
#define PHY_MR24                0x00000018  // Ethernet PHY Management Register
                                            // 24 -MDI/MDIX Control

//*****************************************************************************
//
// Hibernation module registers (HIB)
//
//*****************************************************************************
#define HIB_RTCC_R              (*((volatile unsigned long *)0x400FC000))
#define HIB_RTCM0_R             (*((volatile unsigned long *)0x400FC004))
#define HIB_RTCM1_R             (*((volatile unsigned long *)0x400FC008))
#define HIB_RTCLD_R             (*((volatile unsigned long *)0x400FC00C))
#define HIB_CTL_R               (*((volatile unsigned long *)0x400FC010))
#define HIB_IM_R                (*((volatile unsigned long *)0x400FC014))
#define HIB_RIS_R               (*((volatile unsigned long *)0x400FC018))
#define HIB_MIS_R               (*((volatile unsigned long *)0x400FC01C))
#define HIB_IC_R                (*((volatile unsigned long *)0x400FC020))
#define HIB_RTCT_R              (*((volatile unsigned long *)0x400FC024))
#define HIB_DATA_R              (*((volatile unsigned long *)0x400FC030))

//*****************************************************************************
//
// FLASH registers (FLASH CTRL)
//
//*****************************************************************************
#define FLASH_FMA_R             (*((volatile unsigned long *)0x400FD000))
#define FLASH_FMD_R             (*((volatile unsigned long *)0x400FD004))
#define FLASH_FMC_R             (*((volatile unsigned long *)0x400FD008))
#define FLASH_FCRIS_R           (*((volatile unsigned long *)0x400FD00C))
#define FLASH_FCIM_R            (*((volatile unsigned long *)0x400FD010))
#define FLASH_FCMISC_R          (*((volatile unsigned long *)0x400FD014))
#define FLASH_USECRL_R          (*((volatile unsigned long *)0x400FE140))
#define FLASH_USERDBG_R         (*((volatile unsigned long *)0x400FE1D0))
#define FLASH_USERREG0_R        (*((volatile unsigned long *)0x400FE1E0))
#define FLASH_USERREG1_R        (*((volatile unsigned long *)0x400FE1E4))
#define FLASH_FMPRE0_R          (*((volatile unsigned long *)0x400FE200))
#define FLASH_FMPRE1_R          (*((volatile unsigned long *)0x400FE204))
#define FLASH_FMPRE2_R          (*((volatile unsigned long *)0x400FE208))
#define FLASH_FMPRE3_R          (*((volatile unsigned long *)0x400FE20C))
#define FLASH_FMPPE0_R          (*((volatile unsigned long *)0x400FE400))
#define FLASH_FMPPE1_R          (*((volatile unsigned long *)0x400FE404))
#define FLASH_FMPPE2_R          (*((volatile unsigned long *)0x400FE408))
#define FLASH_FMPPE3_R          (*((volatile unsigned long *)0x400FE40C))

//*****************************************************************************
//
// System Control registers (SYSCTL)
//
//*****************************************************************************
#define SYSCTL_DID0_R           (*((volatile unsigned long *)0x400FE000))
#define SYSCTL_DID1_R           (*((volatile unsigned long *)0x400FE004))
#define SYSCTL_DC0_R            (*((volatile unsigned long *)0x400FE008))
#define SYSCTL_DC1_R            (*((volatile unsigned long *)0x400FE010))
#define SYSCTL_DC2_R            (*((volatile unsigned long *)0x400FE014))
#define SYSCTL_DC3_R            (*((volatile unsigned long *)0x400FE018))
#define SYSCTL_DC4_R            (*((volatile unsigned long *)0x400FE01C))
#define SYSCTL_PBORCTL_R        (*((volatile unsigned long *)0x400FE030))
#define SYSCTL_LDOPCTL_R        (*((volatile unsigned long *)0x400FE034))
#define SYSCTL_SRCR0_R          (*((volatile unsigned long *)0x400FE040))
#define SYSCTL_SRCR1_R          (*((volatile unsigned long *)0x400FE044))
#define SYSCTL_SRCR2_R          (*((volatile unsigned long *)0x400FE048))
#define SYSCTL_RIS_R            (*((volatile unsigned long *)0x400FE050))
#define SYSCTL_IMC_R            (*((volatile unsigned long *)0x400FE054))
#define SYSCTL_MISC_R           (*((volatile unsigned long *)0x400FE058))
#define SYSCTL_RESC_R           (*((volatile unsigned long *)0x400FE05C))
#define SYSCTL_RCC_R            (*((volatile unsigned long *)0x400FE060))
#define SYSCTL_PLLCFG_R         (*((volatile unsigned long *)0x400FE064))
#define SYSCTL_RCC2_R           (*((volatile unsigned long *)0x400FE070))
#define SYSCTL_RCGC0_R          (*((volatile unsigned long *)0x400FE100))
#define SYSCTL_RCGC1_R          (*((volatile unsigned long *)0x400FE104))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_SCGC0_R          (*((volatile unsigned long *)0x400FE110))
#define SYSCTL_SCGC1_R          (*((volatile unsigned long *)0x400FE114))
#define SYSCTL_SCGC2_R          (*((volatile unsigned long *)0x400FE118))
#define SYSCTL_DCGC0_R          (*((volatile unsigned long *)0x400FE120))
#define SYSCTL_DCGC1_R          (*((volatile unsigned long *)0x400FE124))
#define SYSCTL_DCGC2_R          (*((volatile unsigned long *)0x400FE128))
#define SYSCTL_DSLPCLKCFG_R     (*((volatile unsigned long *)0x400FE144))

//*****************************************************************************
//
// NVIC registers (NVIC)
//
//*****************************************************************************
#define NVIC_INT_TYPE_R         (*((volatile unsigned long *)0xE000E004))
#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))
#define NVIC_ST_CAL_R           (*((volatile unsigned long *)0xE000E01C))
#define NVIC_EN0_R              (*((volatile unsigned long *)0xE000E100))
#define NVIC_EN1_R              (*((volatile unsigned long *)0xE000E104))
#define NVIC_DIS0_R             (*((volatile unsigned long *)0xE000E180))
#define NVIC_DIS1_R             (*((volatile unsigned long *)0xE000E184))
#define NVIC_PEND0_R            (*((volatile unsigned long *)0xE000E200))
#define NVIC_PEND1_R            (*((volatile unsigned long *)0xE000E204))
#define NVIC_UNPEND0_R          (*((volatile unsigned long *)0xE000E280))
#define NVIC_UNPEND1_R          (*((volatile unsigned long *)0xE000E284))
#define NVIC_ACTIVE0_R          (*((volatile unsigned long *)0xE000E300))
#define NVIC_ACTIVE1_R          (*((volatile unsigned long *)0xE000E304))
#define NVIC_PRI0_R             (*((volatile unsigned long *)0xE000E400))
#define NVIC_PRI1_R             (*((volatile unsigned long *)0xE000E404))
#define NVIC_PRI2_R             (*((volatile unsigned long *)0xE000E408))
#define NVIC_PRI3_R             (*((volatile unsigned long *)0xE000E40C))
#define NVIC_PRI4_R             (*((volatile unsigned long *)0xE000E410))
#define NVIC_PRI5_R             (*((volatile unsigned long *)0xE000E414))
#define NVIC_PRI6_R             (*((volatile unsigned long *)0xE000E418))
#define NVIC_PRI7_R             (*((volatile unsigned long *)0xE000E41C))
#define NVIC_PRI8_R             (*((volatile unsigned long *)0xE000E420))
#define NVIC_PRI9_R             (*((volatile unsigned long *)0xE000E424))
#define NVIC_PRI10_R            (*((volatile unsigned long *)0xE000E428))
#define NVIC_CPUID_R            (*((volatile unsigned long *)0xE000ED00))
#define NVIC_INT_CTRL_R         (*((volatile unsigned long *)0xE000ED04))
#define NVIC_VTABLE_R           (*((volatile unsigned long *)0xE000ED08))
#define NVIC_APINT_R            (*((volatile unsigned long *)0xE000ED0C))
#define NVIC_SYS_CTRL_R         (*((volatile unsigned long *)0xE000ED10))
#define NVIC_CFG_CTRL_R         (*((volatile unsigned long *)0xE000ED14))
#define NVIC_SYS_PRI1_R         (*((volatile unsigned long *)0xE000ED18))
#define NVIC_SYS_PRI2_R         (*((volatile unsigned long *)0xE000ED1C))
#define NVIC_SYS_PRI3_R         (*((volatile unsigned long *)0xE000ED20))
#define NVIC_SYS_HND_CTRL_R     (*((volatile unsigned long *)0xE000ED24))
#define NVIC_FAULT_STAT_R       (*((volatile unsigned long *)0xE000ED28))
#define NVIC_HFAULT_STAT_R      (*((volatile unsigned long *)0xE000ED2C))
#define NVIC_DEBUG_STAT_R       (*((volatile unsigned long *)0xE000ED30))
#define NVIC_MM_ADDR_R          (*((volatile unsigned long *)0xE000ED34))
#define NVIC_FAULT_ADDR_R       (*((volatile unsigned long *)0xE000ED38))
#define NVIC_MPU_TYPE_R         (*((volatile unsigned long *)0xE000ED90))
#define NVIC_MPU_CTRL_R         (*((volatile unsigned long *)0xE000ED94))
#define NVIC_MPU_NUMBER_R       (*((volatile unsigned long *)0xE000ED98))
#define NVIC_MPU_BASE_R         (*((volatile unsigned long *)0xE000ED9C))
#define NVIC_MPU_ATTR_R         (*((volatile unsigned long *)0xE000EDA0))
#define NVIC_DBG_CTRL_R         (*((volatile unsigned long *)0xE000EDF0))
#define NVIC_DBG_XFER_R         (*((volatile unsigned long *)0xE000EDF4))
#define NVIC_DBG_DATA_R         (*((volatile unsigned long *)0xE000EDF8))
#define NVIC_DBG_INT_R          (*((volatile unsigned long *)0xE000EDFC))
#define NVIC_SW_TRIG_R          (*((volatile unsigned long *)0xE000EF00))

//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_LOAD register.
//
//*****************************************************************************
#define WDT_LOAD_M              0xFFFFFFFF  // Watchdog Load Value
#define WDT_LOAD_S              0

//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_VALUE register.
//
//*****************************************************************************
#define WDT_VALUE_M             0xFFFFFFFF  // Watchdog Value
#define WDT_VALUE_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_CTL register.
//
//*****************************************************************************
#define WDT_CTL_RESEN           0x00000002  // Watchdog Reset Enable
#define WDT_CTL_INTEN           0x00000001  // Watchdog Interrupt Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_ICR register.
//
//*****************************************************************************
#define WDT_ICR_M               0xFFFFFFFF  // Watchdog Interrupt Clear
#define WDT_ICR_S               0

//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_RIS register.
//
//*****************************************************************************
#define WDT_RIS_WDTRIS          0x00000001  // Watchdog Raw Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_MIS register.
//
//*****************************************************************************
#define WDT_MIS_WDTMIS          0x00000001  // Watchdog Masked Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_TEST register.
//
//*****************************************************************************
#define WDT_TEST_STALL          0x00000100  // Watchdog Stall Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the WDT_O_LOCK register.
//
//*****************************************************************************
#define WDT_LOCK_M              0xFFFFFFFF  // Watchdog Lock
#define WDT_LOCK_UNLOCKED       0x00000000  // Unlocked
#define WDT_LOCK_LOCKED         0x00000001  // Locked
#define WDT_LOCK_UNLOCK         0x1ACCE551  // Unlocks the watchdog timer

//*****************************************************************************
//
// The following are defines for the bit fields in the GPIO_O_LOCK register.
//
//*****************************************************************************
#define GPIO_LOCK_M             0xFFFFFFFF  // GPIO Lock
#define GPIO_LOCK_UNLOCKED      0x00000000  // The GPIOCR register is unlocked
                                            // and may be modified
#define GPIO_LOCK_LOCKED        0x00000001  // The GPIOCR register is locked
                                            // and may not be modified
#define GPIO_LOCK_KEY           0x1ACCE551  // Unlocks the GPIO_CR register

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_CR0 register.
//
//*****************************************************************************
#define SSI_CR0_SCR_M           0x0000FF00  // SSI Serial Clock Rate
#define SSI_CR0_SPH             0x00000080  // SSI Serial Clock Phase
#define SSI_CR0_SPO             0x00000040  // SSI Serial Clock Polarity
#define SSI_CR0_FRF_M           0x00000030  // SSI Frame Format Select
#define SSI_CR0_FRF_MOTO        0x00000000  // Freescale SPI Frame Format
#define SSI_CR0_FRF_TI          0x00000010  // Texas Instruments Synchronous
                                            // Serial Frame Format
#define SSI_CR0_FRF_NMW         0x00000020  // MICROWIRE Frame Format
#define SSI_CR0_DSS_M           0x0000000F  // SSI Data Size Select
#define SSI_CR0_DSS_4           0x00000003  // 4-bit data
#define SSI_CR0_DSS_5           0x00000004  // 5-bit data
#define SSI_CR0_DSS_6           0x00000005  // 6-bit data
#define SSI_CR0_DSS_7           0x00000006  // 7-bit data
#define SSI_CR0_DSS_8           0x00000007  // 8-bit data
#define SSI_CR0_DSS_9           0x00000008  // 9-bit data
#define SSI_CR0_DSS_10          0x00000009  // 10-bit data
#define SSI_CR0_DSS_11          0x0000000A  // 11-bit data
#define SSI_CR0_DSS_12          0x0000000B  // 12-bit data
#define SSI_CR0_DSS_13          0x0000000C  // 13-bit data
#define SSI_CR0_DSS_14          0x0000000D  // 14-bit data
#define SSI_CR0_DSS_15          0x0000000E  // 15-bit data
#define SSI_CR0_DSS_16          0x0000000F  // 16-bit data
#define SSI_CR0_SCR_S           8

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_CR1 register.
//
//*****************************************************************************
#define SSI_CR1_SOD             0x00000008  // SSI Slave Mode Output Disable
#define SSI_CR1_MS              0x00000004  // SSI Master/Slave Select
#define SSI_CR1_SSE             0x00000002  // SSI Synchronous Serial Port
                                            // Enable
#define SSI_CR1_LBM             0x00000001  // SSI Loopback Mode

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_DR register.
//
//*****************************************************************************
#define SSI_DR_DATA_M           0x0000FFFF  // SSI Receive/Transmit Data
#define SSI_DR_DATA_S           0

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_SR register.
//
//*****************************************************************************
#define SSI_SR_BSY              0x00000010  // SSI Busy Bit
#define SSI_SR_RFF              0x00000008  // SSI Receive FIFO Full
#define SSI_SR_RNE              0x00000004  // SSI Receive FIFO Not Empty
#define SSI_SR_TNF              0x00000002  // SSI Transmit FIFO Not Full
#define SSI_SR_TFE              0x00000001  // SSI Transmit FIFO Empty

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_CPSR register.
//
//*****************************************************************************
#define SSI_CPSR_CPSDVSR_M      0x000000FF  // SSI Clock Prescale Divisor
#define SSI_CPSR_CPSDVSR_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_IM register.
//
//*****************************************************************************
#define SSI_IM_TXIM             0x00000008  // SSI Transmit FIFO Interrupt Mask
#define SSI_IM_RXIM             0x00000004  // SSI Receive FIFO Interrupt Mask
#define SSI_IM_RTIM             0x00000002  // SSI Receive Time-Out Interrupt
                                            // Mask
#define SSI_IM_RORIM            0x00000001  // SSI Receive Overrun Interrupt
                                            // Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_RIS register.
//
//*****************************************************************************
#define SSI_RIS_TXRIS           0x00000008  // SSI Transmit FIFO Raw Interrupt
                                            // Status
#define SSI_RIS_RXRIS           0x00000004  // SSI Receive FIFO Raw Interrupt
                                            // Status
#define SSI_RIS_RTRIS           0x00000002  // SSI Receive Time-Out Raw
                                            // Interrupt Status
#define SSI_RIS_RORRIS          0x00000001  // SSI Receive Overrun Raw
                                            // Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_MIS register.
//
//*****************************************************************************
#define SSI_MIS_TXMIS           0x00000008  // SSI Transmit FIFO Masked
                                            // Interrupt Status
#define SSI_MIS_RXMIS           0x00000004  // SSI Receive FIFO Masked
                                            // Interrupt Status
#define SSI_MIS_RTMIS           0x00000002  // SSI Receive Time-Out Masked
                                            // Interrupt Status
#define SSI_MIS_RORMIS          0x00000001  // SSI Receive Overrun Masked
                                            // Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_ICR register.
//
//*****************************************************************************
#define SSI_ICR_RTIC            0x00000002  // SSI Receive Time-Out Interrupt
                                            // Clear
#define SSI_ICR_RORIC           0x00000001  // SSI Receive Overrun Interrupt
                                            // Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_DR register.
//
//*****************************************************************************
#define UART_DR_OE              0x00000800  // UART Overrun Error
#define UART_DR_BE              0x00000400  // UART Break Error
#define UART_DR_PE              0x00000200  // UART Parity Error
#define UART_DR_FE              0x00000100  // UART Framing Error
#define UART_DR_DATA_M          0x000000FF  // Data Transmitted or Received
#define UART_DR_DATA_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_RSR register.
//
//*****************************************************************************
#define UART_RSR_OE             0x00000008  // UART Overrun Error
#define UART_RSR_BE             0x00000004  // UART Break Error
#define UART_RSR_PE             0x00000002  // UART Parity Error
#define UART_RSR_FE             0x00000001  // UART Framing Error

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_ECR register.
//
//*****************************************************************************
#define UART_ECR_DATA_M         0x000000FF  // Error Clear
#define UART_ECR_DATA_S         0

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_FR register.
//
//*****************************************************************************
#define UART_FR_TXFE            0x00000080  // UART Transmit FIFO Empty
#define UART_FR_RXFF            0x00000040  // UART Receive FIFO Full
#define UART_FR_TXFF            0x00000020  // UART Transmit FIFO Full
#define UART_FR_RXFE            0x00000010  // UART Receive FIFO Empty
#define UART_FR_BUSY            0x00000008  // UART Busy

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_ILPR register.
//
//*****************************************************************************
#define UART_ILPR_ILPDVSR_M     0x000000FF  // IrDA Low-Power Divisor
#define UART_ILPR_ILPDVSR_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_IBRD register.
//
//*****************************************************************************
#define UART_IBRD_DIVINT_M      0x0000FFFF  // Integer Baud-Rate Divisor
#define UART_IBRD_DIVINT_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_FBRD register.
//
//*****************************************************************************
#define UART_FBRD_DIVFRAC_M     0x0000003F  // Fractional Baud-Rate Divisor
#define UART_FBRD_DIVFRAC_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_LCRH register.
//
//*****************************************************************************
#define UART_LCRH_SPS           0x00000080  // UART Stick Parity Select
#define UART_LCRH_WLEN_M        0x00000060  // UART Word Length
#define UART_LCRH_WLEN_5        0x00000000  // 5 bits (default)
#define UART_LCRH_WLEN_6        0x00000020  // 6 bits
#define UART_LCRH_WLEN_7        0x00000040  // 7 bits
#define UART_LCRH_WLEN_8        0x00000060  // 8 bits
#define UART_LCRH_FEN           0x00000010  // UART Enable FIFOs
#define UART_LCRH_STP2          0x00000008  // UART Two Stop Bits Select
#define UART_LCRH_EPS           0x00000004  // UART Even Parity Select
#define UART_LCRH_PEN           0x00000002  // UART Parity Enable
#define UART_LCRH_BRK           0x00000001  // UART Send Break

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_CTL register.
//
//*****************************************************************************
#define UART_CTL_RXE            0x00000200  // UART Receive Enable
#define UART_CTL_TXE            0x00000100  // UART Transmit Enable
#define UART_CTL_LBE            0x00000080  // UART Loop Back Enable
#define UART_CTL_SIRLP          0x00000004  // UART SIR Low-Power Mode
#define UART_CTL_SIREN          0x00000002  // UART SIR Enable
#define UART_CTL_UARTEN         0x00000001  // UART Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_IFLS register.
//
//*****************************************************************************
#define UART_IFLS_RX_M          0x00000038  // UART Receive Interrupt FIFO
                                            // Level Select
#define UART_IFLS_RX1_8         0x00000000  // RX FIFO >= 1/8 full
#define UART_IFLS_RX2_8         0x00000008  // RX FIFO >= 1/4 full
#define UART_IFLS_RX4_8         0x00000010  // RX FIFO >= 1/2 full (default)
#define UART_IFLS_RX6_8         0x00000018  // RX FIFO >= 3/4 full
#define UART_IFLS_RX7_8         0x00000020  // RX FIFO >= 7/8 full
#define UART_IFLS_TX_M          0x00000007  // UART Transmit Interrupt FIFO
                                            // Level Select
#define UART_IFLS_TX1_8         0x00000000  // TX FIFO <= 1/8 full
#define UART_IFLS_TX2_8         0x00000001  // TX FIFO <= 1/4 full
#define UART_IFLS_TX4_8         0x00000002  // TX FIFO <= 1/2 full (default)
#define UART_IFLS_TX6_8         0x00000003  // TX FIFO <= 3/4 full
#define UART_IFLS_TX7_8         0x00000004  // TX FIFO <= 7/8 full

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_IM register.
//
//*****************************************************************************
#define UART_IM_OEIM            0x00000400  // UART Overrun Error Interrupt
                                            // Mask
#define UART_IM_BEIM            0x00000200  // UART Break Error Interrupt Mask
#define UART_IM_PEIM            0x00000100  // UART Parity Error Interrupt Mask
#define UART_IM_FEIM            0x00000080  // UART Framing Error Interrupt
                                            // Mask
#define UART_IM_RTIM            0x00000040  // UART Receive Time-Out Interrupt
                                            // Mask
#define UART_IM_TXIM            0x00000020  // UART Transmit Interrupt Mask
#define UART_IM_RXIM            0x00000010  // UART Receive Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_RIS register.
//
//*****************************************************************************
#define UART_RIS_OERIS          0x00000400  // UART Overrun Error Raw Interrupt
                                            // Status
#define UART_RIS_BERIS          0x00000200  // UART Break Error Raw Interrupt
                                            // Status
#define UART_RIS_PERIS          0x00000100  // UART Parity Error Raw Interrupt
                                            // Status
#define UART_RIS_FERIS          0x00000080  // UART Framing Error Raw Interrupt
                                            // Status
#define UART_RIS_RTRIS          0x00000040  // UART Receive Time-Out Raw
                                            // Interrupt Status
#define UART_RIS_TXRIS          0x00000020  // UART Transmit Raw Interrupt
                                            // Status
#define UART_RIS_RXRIS          0x00000010  // UART Receive Raw Interrupt
                                            // Status

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_MIS register.
//
//*****************************************************************************
#define UART_MIS_OEMIS          0x00000400  // UART Overrun Error Masked
                                            // Interrupt Status
#define UART_MIS_BEMIS          0x00000200  // UART Break Error Masked
                                            // Interrupt Status
#define UART_MIS_PEMIS          0x00000100  // UART Parity Error Masked
                                            // Interrupt Status
#define UART_MIS_FEMIS          0x00000080  // UART Framing Error Masked
                                            // Interrupt Status
#define UART_MIS_RTMIS          0x00000040  // UART Receive Time-Out Masked
                                            // Interrupt Status
#define UART_MIS_TXMIS          0x00000020  // UART Transmit Masked Interrupt
                                            // Status
#define UART_MIS_RXMIS          0x00000010  // UART Receive Masked Interrupt
                                            // Status

//*****************************************************************************
//
// The following are defines for the bit fields in the UART_O_ICR register.
//
//*****************************************************************************
#define UART_ICR_OEIC           0x00000400  // Overrun Error Interrupt Clear
#define UART_ICR_BEIC           0x00000200  // Break Error Interrupt Clear
#define UART_ICR_PEIC           0x00000100  // Parity Error Interrupt Clear
#define UART_ICR_FEIC           0x00000080  // Framing Error Interrupt Clear
#define UART_ICR_RTIC           0x00000040  // Receive Time-Out Interrupt Clear
#define UART_ICR_TXIC           0x00000020  // Transmit Interrupt Clear
#define UART_ICR_RXIC           0x00000010  // Receive Interrupt Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MSA register.
//
//*****************************************************************************
#define I2C_MSA_SA_M            0x000000FE  // I2C Slave Address
#define I2C_MSA_RS              0x00000001  // Receive not send
#define I2C_MSA_SA_S            1

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SOAR register.
//
//*****************************************************************************
#define I2C_SOAR_OAR_M          0x0000007F  // I2C Slave Own Address
#define I2C_SOAR_OAR_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SCSR register.
//
//*****************************************************************************
#define I2C_SCSR_FBR            0x00000004  // First Byte Received
#define I2C_SCSR_TREQ           0x00000002  // Transmit Request
#define I2C_SCSR_DA             0x00000001  // Device Active
#define I2C_SCSR_RREQ           0x00000001  // Receive Request

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MCS register.
//
//*****************************************************************************
#define I2C_MCS_BUSBSY          0x00000040  // Bus Busy
#define I2C_MCS_IDLE            0x00000020  // I2C Idle
#define I2C_MCS_ARBLST          0x00000010  // Arbitration Lost
#define I2C_MCS_ACK             0x00000008  // Data Acknowledge Enable
#define I2C_MCS_DATACK          0x00000008  // Acknowledge Data
#define I2C_MCS_ADRACK          0x00000004  // Acknowledge Address
#define I2C_MCS_STOP            0x00000004  // Generate STOP
#define I2C_MCS_START           0x00000002  // Generate START
#define I2C_MCS_ERROR           0x00000002  // Error
#define I2C_MCS_RUN             0x00000001  // I2C Master Enable
#define I2C_MCS_BUSY            0x00000001  // I2C Busy

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SDR register.
//
//*****************************************************************************
#define I2C_SDR_DATA_M          0x000000FF  // Data for Transfer
#define I2C_SDR_DATA_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MDR register.
//
//*****************************************************************************
#define I2C_MDR_DATA_M          0x000000FF  // Data Transferred
#define I2C_MDR_DATA_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MTPR register.
//
//*****************************************************************************
#define I2C_MTPR_TPR_M          0x0000007F  // SCL Clock Period
#define I2C_MTPR_TPR_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SIMR register.
//
//*****************************************************************************
#define I2C_SIMR_DATAIM         0x00000001  // Data Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SRIS register.
//
//*****************************************************************************
#define I2C_SRIS_DATARIS        0x00000001  // Data Raw Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MIMR register.
//
//*****************************************************************************
#define I2C_MIMR_IM             0x00000001  // Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MRIS register.
//
//*****************************************************************************
#define I2C_MRIS_RIS            0x00000001  // Raw Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SMIS register.
//
//*****************************************************************************
#define I2C_SMIS_DATAMIS        0x00000001  // Data Masked Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SICR register.
//
//*****************************************************************************
#define I2C_SICR_DATAIC         0x00000001  // Data Interrupt Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MMIS register.
//
//*****************************************************************************
#define I2C_MMIS_MIS            0x00000001  // Masked Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MICR register.
//
//*****************************************************************************
#define I2C_MICR_IC             0x00000001  // Interrupt Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MCR register.
//
//*****************************************************************************
#define I2C_MCR_SFE             0x00000020  // I2C Slave Function Enable
#define I2C_MCR_MFE             0x00000010  // I2C Master Function Enable
#define I2C_MCR_LPBK            0x00000001  // I2C Loopback

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_CTL register.
//
//*****************************************************************************
#define PWM_CTL_GLOBALSYNC2     0x00000004  // Update PWM Generator 2
#define PWM_CTL_GLOBALSYNC1     0x00000002  // Update PWM Generator 1
#define PWM_CTL_GLOBALSYNC0     0x00000001  // Update PWM Generator 0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_SYNC register.
//
//*****************************************************************************
#define PWM_SYNC_SYNC2          0x00000004  // Reset Generator 2 Counter
#define PWM_SYNC_SYNC1          0x00000002  // Reset Generator 1 Counter
#define PWM_SYNC_SYNC0          0x00000001  // Reset Generator 0 Counter

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_ENABLE register.
//
//*****************************************************************************
#define PWM_ENABLE_PWM5EN       0x00000020  // PWM5 Output Enable
#define PWM_ENABLE_PWM4EN       0x00000010  // PWM4 Output Enable
#define PWM_ENABLE_PWM3EN       0x00000008  // PWM3 Output Enable
#define PWM_ENABLE_PWM2EN       0x00000004  // PWM2 Output Enable
#define PWM_ENABLE_PWM1EN       0x00000002  // PWM1 Output Enable
#define PWM_ENABLE_PWM0EN       0x00000001  // PWM0 Output Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_INVERT register.
//
//*****************************************************************************
#define PWM_INVERT_PWM5INV      0x00000020  // Invert PWM5 Signal
#define PWM_INVERT_PWM4INV      0x00000010  // Invert PWM4 Signal
#define PWM_INVERT_PWM3INV      0x00000008  // Invert PWM3 Signal
#define PWM_INVERT_PWM2INV      0x00000004  // Invert PWM2 Signal
#define PWM_INVERT_PWM1INV      0x00000002  // Invert PWM1 Signal
#define PWM_INVERT_PWM0INV      0x00000001  // Invert PWM0 Signal

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_FAULT register.
//
//*****************************************************************************
#define PWM_FAULT_FAULT5        0x00000020  // PWM5 Fault
#define PWM_FAULT_FAULT4        0x00000010  // PWM4 Fault
#define PWM_FAULT_FAULT3        0x00000008  // PWM3 Fault
#define PWM_FAULT_FAULT2        0x00000004  // PWM2 Fault
#define PWM_FAULT_FAULT1        0x00000002  // PWM1 Fault
#define PWM_FAULT_FAULT0        0x00000001  // PWM0 Fault

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_INTEN register.
//
//*****************************************************************************
#define PWM_INTEN_INTFAULT      0x00010000  // Fault Interrupt Enable
#define PWM_INTEN_INTPWM2       0x00000004  // PWM2 Interrupt Enable
#define PWM_INTEN_INTPWM1       0x00000002  // PWM1 Interrupt Enable
#define PWM_INTEN_INTPWM0       0x00000001  // PWM0 Interrupt Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_RIS register.
//
//*****************************************************************************
#define PWM_RIS_INTFAULT        0x00010000  // Fault Interrupt Asserted
#define PWM_RIS_INTPWM2         0x00000004  // PWM2 Interrupt Asserted
#define PWM_RIS_INTPWM1         0x00000002  // PWM1 Interrupt Asserted
#define PWM_RIS_INTPWM0         0x00000001  // PWM0 Interrupt Asserted

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_ISC register.
//
//*****************************************************************************
#define PWM_ISC_INTFAULT        0x00010000  // Fault Interrupt Asserted
#define PWM_ISC_INTPWM2         0x00000004  // PWM2 Interrupt Status
#define PWM_ISC_INTPWM1         0x00000002  // PWM1 Interrupt Status
#define PWM_ISC_INTPWM0         0x00000001  // PWM0 Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_STATUS register.
//
//*****************************************************************************
#define PWM_STATUS_FAULT        0x00000001  // Fault Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_X_CTL register.
//
//*****************************************************************************
#define PWM_X_CTL_CMPBUPD       0x00000020  // Comparator B Update Mode
#define PWM_X_CTL_CMPAUPD       0x00000010  // Comparator A Update Mode
#define PWM_X_CTL_LOADUPD       0x00000008  // Load Register Update Mode
#define PWM_X_CTL_DEBUG         0x00000004  // Debug Mode
#define PWM_X_CTL_MODE          0x00000002  // Counter Mode
#define PWM_X_CTL_ENABLE        0x00000001  // PWM Block Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_X_INTEN register.
//
//*****************************************************************************
#define PWM_X_INTEN_TRCMPBD     0x00002000  // Trigger for Counter=PWMnCMPB
                                            // Down
#define PWM_X_INTEN_TRCMPBU     0x00001000  // Trigger for Counter=PWMnCMPB Up
#define PWM_X_INTEN_TRCMPAD     0x00000800  // Trigger for Counter=PWMnCMPA
                                            // Down
#define PWM_X_INTEN_TRCMPAU     0x00000400  // Trigger for Counter=PWMnCMPA Up
#define PWM_X_INTEN_TRCNTLOAD   0x00000200  // Trigger for Counter=PWMnLOAD
#define PWM_X_INTEN_TRCNTZERO   0x00000100  // Trigger for Counter=0
#define PWM_X_INTEN_INTCMPBD    0x00000020  // Interrupt for Counter=PWMnCMPB
                                            // Down
#define PWM_X_INTEN_INTCMPBU    0x00000010  // Interrupt for Counter=PWMnCMPB
                                            // Up
#define PWM_X_INTEN_INTCMPAD    0x00000008  // Interrupt for Counter=PWMnCMPA
                                            // Down
#define PWM_X_INTEN_INTCMPAU    0x00000004  // Interrupt for Counter=PWMnCMPA
                                            // Up
#define PWM_X_INTEN_INTCNTLOAD  0x00000002  // Interrupt for Counter=PWMnLOAD
#define PWM_X_INTEN_INTCNTZERO  0x00000001  // Interrupt for Counter=0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_X_RIS register.
//
//*****************************************************************************
#define PWM_X_RIS_INTCMPBD      0x00000020  // Comparator B Down Interrupt
                                            // Status
#define PWM_X_RIS_INTCMPBU      0x00000010  // Comparator B Up Interrupt Status
#define PWM_X_RIS_INTCMPAD      0x00000008  // Comparator A Down Interrupt
                                            // Status
#define PWM_X_RIS_INTCMPAU      0x00000004  // Comparator A Up Interrupt Status
#define PWM_X_RIS_INTCNTLOAD    0x00000002  // Counter=Load Interrupt Status
#define PWM_X_RIS_INTCNTZERO    0x00000001  // Counter=0 Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_X_ISC register.
//
//*****************************************************************************
#define PWM_X_ISC_INTCMPBD      0x00000020  // Comparator B Down Interrupt
#define PWM_X_ISC_INTCMPBU      0x00000010  // Comparator B Up Interrupt
#define PWM_X_ISC_INTCMPAD      0x00000008  // Comparator A Down Interrupt
#define PWM_X_ISC_INTCMPAU      0x00000004  // Comparator A Up Interrupt
#define PWM_X_ISC_INTCNTLOAD    0x00000002  // Counter=Load Interrupt
#define PWM_X_ISC_INTCNTZERO    0x00000001  // Counter=0 Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_X_LOAD register.
//
//*****************************************************************************
#define PWM_X_LOAD_M            0x0000FFFF  // Counter Load Value
#define PWM_X_LOAD_S            0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_X_COUNT register.
//
//*****************************************************************************
#define PWM_X_COUNT_M           0x0000FFFF  // Counter Value
#define PWM_X_COUNT_S           0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_X_CMPA register.
//
//*****************************************************************************
#define PWM_X_CMPA_M            0x0000FFFF  // Comparator A Value
#define PWM_X_CMPA_S            0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_X_CMPB register.
//
//*****************************************************************************
#define PWM_X_CMPB_M            0x0000FFFF  // Comparator B Value
#define PWM_X_CMPB_S            0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_X_GENA register.
//
//*****************************************************************************
#define PWM_X_GENA_ACTCMPBD_M   0x00000C00  // Action for Comparator B Down
#define PWM_X_GENA_ACTCMPBD_NONE \
                                0x00000000  // Do nothing
#define PWM_X_GENA_ACTCMPBD_INV 0x00000400  // Invert pwmA
#define PWM_X_GENA_ACTCMPBD_ZERO \
                                0x00000800  // Drive pwmA Low
#define PWM_X_GENA_ACTCMPBD_ONE 0x00000C00  // Drive pwmA High
#define PWM_X_GENA_ACTCMPBU_M   0x00000300  // Action for Comparator B Up
#define PWM_X_GENA_ACTCMPBU_NONE \
                                0x00000000  // Do nothing
#define PWM_X_GENA_ACTCMPBU_INV 0x00000100  // Invert pwmA
#define PWM_X_GENA_ACTCMPBU_ZERO \
                                0x00000200  // Drive pwmA Low
#define PWM_X_GENA_ACTCMPBU_ONE 0x00000300  // Drive pwmA High
#define PWM_X_GENA_ACTCMPAD_M   0x000000C0  // Action for Comparator A Down
#define PWM_X_GENA_ACTCMPAD_NONE \
                                0x00000000  // Do nothing
#define PWM_X_GENA_ACTCMPAD_INV 0x00000040  // Invert pwmA
#define PWM_X_GENA_ACTCMPAD_ZERO \
                                0x00000080  // Drive pwmA Low
#define PWM_X_GENA_ACTCMPAD_ONE 0x000000C0  // Drive pwmA High
#define PWM_X_GENA_ACTCMPAU_M   0x00000030  // Action for Comparator A Up
#define PWM_X_GENA_ACTCMPAU_NONE \
                                0x00000000  // Do nothing
#define PWM_X_GENA_ACTCMPAU_INV 0x00000010  // Invert pwmA
#define PWM_X_GENA_ACTCMPAU_ZERO \
                                0x00000020  // Drive pwmA Low
#define PWM_X_GENA_ACTCMPAU_ONE 0x00000030  // Drive pwmA High
#define PWM_X_GENA_ACTLOAD_M    0x0000000C  // Action for Counter=LOAD
#define PWM_X_GENA_ACTLOAD_NONE 0x00000000  // Do nothing
#define PWM_X_GENA_ACTLOAD_INV  0x00000004  // Invert pwmA
#define PWM_X_GENA_ACTLOAD_ZERO 0x00000008  // Drive pwmA Low
#define PWM_X_GENA_ACTLOAD_ONE  0x0000000C  // Drive pwmA High
#define PWM_X_GENA_ACTZERO_M    0x00000003  // Action for Counter=0
#define PWM_X_GENA_ACTZERO_NONE 0x00000000  // Do nothing
#define PWM_X_GENA_ACTZERO_INV  0x00000001  // Invert pwmA
#define PWM_X_GENA_ACTZERO_ZERO 0x00000002  // Drive pwmA Low
#define PWM_X_GENA_ACTZERO_ONE  0x00000003  // Drive pwmA High

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_X_GENB register.
//
//*****************************************************************************
#define PWM_X_GENB_ACTCMPBD_M   0x00000C00  // Action for Comparator B Down
#define PWM_X_GENB_ACTCMPBD_NONE \
                                0x00000000  // Do nothing
#define PWM_X_GENB_ACTCMPBD_INV 0x00000400  // Invert pwmB
#define PWM_X_GENB_ACTCMPBD_ZERO \
                                0x00000800  // Drive pwmB Low
#define PWM_X_GENB_ACTCMPBD_ONE 0x00000C00  // Drive pwmB High
#define PWM_X_GENB_ACTCMPBU_M   0x00000300  // Action for Comparator B Up
#define PWM_X_GENB_ACTCMPBU_NONE \
                                0x00000000  // Do nothing
#define PWM_X_GENB_ACTCMPBU_INV 0x00000100  // Invert pwmB
#define PWM_X_GENB_ACTCMPBU_ZERO \
                                0x00000200  // Drive pwmB Low
#define PWM_X_GENB_ACTCMPBU_ONE 0x00000300  // Drive pwmB High
#define PWM_X_GENB_ACTCMPAD_M   0x000000C0  // Action for Comparator A Down
#define PWM_X_GENB_ACTCMPAD_NONE \
                                0x00000000  // Do nothing
#define PWM_X_GENB_ACTCMPAD_INV 0x00000040  // Invert pwmB
#define PWM_X_GENB_ACTCMPAD_ZERO \
                                0x00000080  // Drive pwmB Low
#define PWM_X_GENB_ACTCMPAD_ONE 0x000000C0  // Drive pwmB High
#define PWM_X_GENB_ACTCMPAU_M   0x00000030  // Action for Comparator A Up
#define PWM_X_GENB_ACTCMPAU_NONE \
                                0x00000000  // Do nothing
#define PWM_X_GENB_ACTCMPAU_INV 0x00000010  // Invert pwmB
#define PWM_X_GENB_ACTCMPAU_ZERO \
                                0x00000020  // Drive pwmB Low
#define PWM_X_GENB_ACTCMPAU_ONE 0x00000030  // Drive pwmB High
#define PWM_X_GENB_ACTLOAD_M    0x0000000C  // Action for Counter=LOAD
#define PWM_X_GENB_ACTLOAD_NONE 0x00000000  // Do nothing
#define PWM_X_GENB_ACTLOAD_INV  0x00000004  // Invert pwmB
#define PWM_X_GENB_ACTLOAD_ZERO 0x00000008  // Drive pwmB Low
#define PWM_X_GENB_ACTLOAD_ONE  0x0000000C  // Drive pwmB High
#define PWM_X_GENB_ACTZERO_M    0x00000003  // Action for Counter=0
#define PWM_X_GENB_ACTZERO_NONE 0x00000000  // Do nothing
#define PWM_X_GENB_ACTZERO_INV  0x00000001  // Invert pwmB
#define PWM_X_GENB_ACTZERO_ZERO 0x00000002  // Drive pwmB Low
#define PWM_X_GENB_ACTZERO_ONE  0x00000003  // Drive pwmB High

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_X_DBCTL register.
//
//*****************************************************************************
#define PWM_X_DBCTL_ENABLE      0x00000001  // Dead-Band Generator Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_X_DBRISE register.
//
//*****************************************************************************
#define PWM_X_DBRISE_DELAY_M    0x00000FFF  // Dead-Band Rise Delay
#define PWM_X_DBRISE_DELAY_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the PWM_O_X_DBFALL register.
//
//*****************************************************************************
#define PWM_X_DBFALL_DELAY_M    0x00000FFF  // Dead-Band Fall Delay
#define PWM_X_DBFALL_DELAY_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_CTL register.
//
//*****************************************************************************
#define QEI_CTL_STALLEN         0x00001000  // Stall QEI
#define QEI_CTL_INVI            0x00000800  // Invert Index Pulse
#define QEI_CTL_INVB            0x00000400  // Invert PhB
#define QEI_CTL_INVA            0x00000200  // Invert PhA
#define QEI_CTL_VELDIV_M        0x000001C0  // Predivide Velocity
#define QEI_CTL_VELDIV_1        0x00000000  // QEI clock /1
#define QEI_CTL_VELDIV_2        0x00000040  // QEI clock /2
#define QEI_CTL_VELDIV_4        0x00000080  // QEI clock /4
#define QEI_CTL_VELDIV_8        0x000000C0  // QEI clock /8
#define QEI_CTL_VELDIV_16       0x00000100  // QEI clock /16
#define QEI_CTL_VELDIV_32       0x00000140  // QEI clock /32
#define QEI_CTL_VELDIV_64       0x00000180  // QEI clock /64
#define QEI_CTL_VELDIV_128      0x000001C0  // QEI clock /128
#define QEI_CTL_VELEN           0x00000020  // Capture Velocity
#define QEI_CTL_RESMODE         0x00000010  // Reset Mode
#define QEI_CTL_CAPMODE         0x00000008  // Capture Mode
#define QEI_CTL_SIGMODE         0x00000004  // Signal Mode
#define QEI_CTL_SWAP            0x00000002  // Swap Signals
#define QEI_CTL_ENABLE          0x00000001  // Enable QEI

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_STAT register.
//
//*****************************************************************************
#define QEI_STAT_DIRECTION      0x00000002  // Direction of Rotation
#define QEI_STAT_ERROR          0x00000001  // Error Detected

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_POS register.
//
//*****************************************************************************
#define QEI_POS_M               0xFFFFFFFF  // Current Position Integrator
                                            // Value
#define QEI_POS_S               0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_MAXPOS register.
//
//*****************************************************************************
#define QEI_MAXPOS_M            0xFFFFFFFF  // Maximum Position Integrator
                                            // Value
#define QEI_MAXPOS_S            0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_LOAD register.
//
//*****************************************************************************
#define QEI_LOAD_M              0xFFFFFFFF  // Velocity Timer Load Value
#define QEI_LOAD_S              0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_TIME register.
//
//*****************************************************************************
#define QEI_TIME_M              0xFFFFFFFF  // Velocity Timer Current Value
#define QEI_TIME_S              0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_COUNT register.
//
//*****************************************************************************
#define QEI_COUNT_M             0xFFFFFFFF  // Velocity Pulse Count
#define QEI_COUNT_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_SPEED register.
//
//*****************************************************************************
#define QEI_SPEED_M             0xFFFFFFFF  // Velocity
#define QEI_SPEED_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_INTEN register.
//
//*****************************************************************************
#define QEI_INTEN_ERROR         0x00000008  // Phase Error Interrupt Enable
#define QEI_INTEN_DIR           0x00000004  // Direction Change Interrupt
                                            // Enable
#define QEI_INTEN_TIMER         0x00000002  // Timer Expires Interrupt Enable
#define QEI_INTEN_INDEX         0x00000001  // Index Pulse Detected Interrupt
                                            // Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_RIS register.
//
//*****************************************************************************
#define QEI_RIS_ERROR           0x00000008  // Phase Error Detected
#define QEI_RIS_DIR             0x00000004  // Direction Change Detected
#define QEI_RIS_TIMER           0x00000002  // Velocity Timer Expired
#define QEI_RIS_INDEX           0x00000001  // Index Pulse Asserted

//*****************************************************************************
//
// The following are defines for the bit fields in the QEI_O_ISC register.
//
//*****************************************************************************
#define QEI_ISC_ERROR           0x00000008  // Phase Error Interrupt
#define QEI_ISC_DIR             0x00000004  // Direction Change Interrupt
#define QEI_ISC_TIMER           0x00000002  // Velocity Timer Expired Interrupt
#define QEI_ISC_INDEX           0x00000001  // Index Pulse Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_CFG register.
//
//*****************************************************************************
#define TIMER_CFG_M             0x00000007  // GPTM Configuration
#define TIMER_CFG_32_BIT_TIMER  0x00000000  // 32-bit timer configuration
#define TIMER_CFG_32_BIT_RTC    0x00000001  // 32-bit real-time clock (RTC)
                                            // counter configuration
#define TIMER_CFG_16_BIT        0x00000004  // 16-bit timer configuration. The
                                            // function is controlled by bits
                                            // 1:0 of GPTMTAMR and GPTMTBMR

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAMR register.
//
//*****************************************************************************
#define TIMER_TAMR_TAAMS        0x00000008  // GPTM Timer A Alternate Mode
                                            // Select
#define TIMER_TAMR_TACMR        0x00000004  // GPTM Timer A Capture Mode
#define TIMER_TAMR_TAMR_M       0x00000003  // GPTM Timer A Mode
#define TIMER_TAMR_TAMR_1_SHOT  0x00000001  // One-Shot Timer mode
#define TIMER_TAMR_TAMR_PERIOD  0x00000002  // Periodic Timer mode
#define TIMER_TAMR_TAMR_CAP     0x00000003  // Capture mode

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBMR register.
//
//*****************************************************************************
#define TIMER_TBMR_TBAMS        0x00000008  // GPTM Timer B Alternate Mode
                                            // Select
#define TIMER_TBMR_TBCMR        0x00000004  // GPTM Timer B Capture Mode
#define TIMER_TBMR_TBMR_M       0x00000003  // GPTM Timer B Mode
#define TIMER_TBMR_TBMR_1_SHOT  0x00000001  // One-Shot Timer mode
#define TIMER_TBMR_TBMR_PERIOD  0x00000002  // Periodic Timer mode
#define TIMER_TBMR_TBMR_CAP     0x00000003  // Capture mode

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_CTL register.
//
//*****************************************************************************
#define TIMER_CTL_TBPWML        0x00004000  // GPTM Timer B PWM Output Level
#define TIMER_CTL_TBOTE         0x00002000  // GPTM Timer B Output Trigger
                                            // Enable
#define TIMER_CTL_TBEVENT_M     0x00000C00  // GPTM Timer B Event Mode
#define TIMER_CTL_TBEVENT_POS   0x00000000  // Positive edge
#define TIMER_CTL_TBEVENT_NEG   0x00000400  // Negative edge
#define TIMER_CTL_TBEVENT_BOTH  0x00000C00  // Both edges
#define TIMER_CTL_TBSTALL       0x00000200  // GPTM Timer B Stall Enable
#define TIMER_CTL_TBEN          0x00000100  // GPTM Timer B Enable
#define TIMER_CTL_TAPWML        0x00000040  // GPTM Timer A PWM Output Level
#define TIMER_CTL_TAOTE         0x00000020  // GPTM Timer A Output Trigger
                                            // Enable
#define TIMER_CTL_RTCEN         0x00000010  // GPTM RTC Enable
#define TIMER_CTL_TAEVENT_M     0x0000000C  // GPTM Timer A Event Mode
#define TIMER_CTL_TAEVENT_POS   0x00000000  // Positive edge
#define TIMER_CTL_TAEVENT_NEG   0x00000004  // Negative edge
#define TIMER_CTL_TAEVENT_BOTH  0x0000000C  // Both edges
#define TIMER_CTL_TASTALL       0x00000002  // GPTM Timer A Stall Enable
#define TIMER_CTL_TAEN          0x00000001  // GPTM Timer A Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_IMR register.
//
//*****************************************************************************
#define TIMER_IMR_CBEIM         0x00000400  // GPTM Capture B Event Interrupt
                                            // Mask
#define TIMER_IMR_CBMIM         0x00000200  // GPTM Capture B Match Interrupt
                                            // Mask
#define TIMER_IMR_TBTOIM        0x00000100  // GPTM Timer B Time-Out Interrupt
                                            // Mask
#define TIMER_IMR_RTCIM         0x00000008  // GPTM RTC Interrupt Mask
#define TIMER_IMR_CAEIM         0x00000004  // GPTM Capture A Event Interrupt
                                            // Mask
#define TIMER_IMR_CAMIM         0x00000002  // GPTM Capture A Match Interrupt
                                            // Mask
#define TIMER_IMR_TATOIM        0x00000001  // GPTM Timer A Time-Out Interrupt
                                            // Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_RIS register.
//
//*****************************************************************************
#define TIMER_RIS_CBERIS        0x00000400  // GPTM Capture B Event Raw
                                            // Interrupt
#define TIMER_RIS_CBMRIS        0x00000200  // GPTM Capture B Match Raw
                                            // Interrupt
#define TIMER_RIS_TBTORIS       0x00000100  // GPTM Timer B Time-Out Raw
                                            // Interrupt
#define TIMER_RIS_RTCRIS        0x00000008  // GPTM RTC Raw Interrupt
#define TIMER_RIS_CAERIS        0x00000004  // GPTM Capture A Event Raw
                                            // Interrupt
#define TIMER_RIS_CAMRIS        0x00000002  // GPTM Capture A Match Raw
                                            // Interrupt
#define TIMER_RIS_TATORIS       0x00000001  // GPTM Timer A Time-Out Raw
                                            // Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_MIS register.
//
//*****************************************************************************
#define TIMER_MIS_CBEMIS        0x00000400  // GPTM Capture B Event Masked
                                            // Interrupt
#define TIMER_MIS_CBMMIS        0x00000200  // GPTM Capture B Match Masked
                                            // Interrupt
#define TIMER_MIS_TBTOMIS       0x00000100  // GPTM Timer B Time-Out Masked
                                            // Interrupt
#define TIMER_MIS_RTCMIS        0x00000008  // GPTM RTC Masked Interrupt
#define TIMER_MIS_CAEMIS        0x00000004  // GPTM Capture A Event Masked
                                            // Interrupt
#define TIMER_MIS_CAMMIS        0x00000002  // GPTM Capture A Match Masked
                                            // Interrupt
#define TIMER_MIS_TATOMIS       0x00000001  // GPTM Timer A Time-Out Masked
                                            // Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_ICR register.
//
//*****************************************************************************
#define TIMER_ICR_CBECINT       0x00000400  // GPTM Capture B Event Interrupt
                                            // Clear
#define TIMER_ICR_CBMCINT       0x00000200  // GPTM Capture B Match Interrupt
                                            // Clear
#define TIMER_ICR_TBTOCINT      0x00000100  // GPTM Timer B Time-Out Interrupt
                                            // Clear
#define TIMER_ICR_RTCCINT       0x00000008  // GPTM RTC Interrupt Clear
#define TIMER_ICR_CAECINT       0x00000004  // GPTM Capture A Event Interrupt
                                            // Clear
#define TIMER_ICR_CAMCINT       0x00000002  // GPTM Capture A Match Interrupt
                                            // Clear
#define TIMER_ICR_TATOCINT      0x00000001  // GPTM Timer A Time-Out Raw
                                            // Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAILR register.
//
//*****************************************************************************
#define TIMER_TAILR_TAILRH_M    0xFFFF0000  // GPTM Timer A Interval Load
                                            // Register High
#define TIMER_TAILR_TAILRL_M    0x0000FFFF  // GPTM Timer A Interval Load
                                            // Register Low
#define TIMER_TAILR_TAILRH_S    16
#define TIMER_TAILR_TAILRL_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBILR register.
//
//*****************************************************************************
#define TIMER_TBILR_TBILRL_M    0x0000FFFF  // GPTM Timer B Interval Load
                                            // Register
#define TIMER_TBILR_TBILRL_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAMATCHR
// register.
//
//*****************************************************************************
#define TIMER_TAMATCHR_TAMRH_M  0xFFFF0000  // GPTM Timer A Match Register High
#define TIMER_TAMATCHR_TAMRL_M  0x0000FFFF  // GPTM Timer A Match Register Low
#define TIMER_TAMATCHR_TAMRH_S  16
#define TIMER_TAMATCHR_TAMRL_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBMATCHR
// register.
//
//*****************************************************************************
#define TIMER_TBMATCHR_TBMRL_M  0x0000FFFF  // GPTM Timer B Match Register Low
#define TIMER_TBMATCHR_TBMRL_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAPR register.
//
//*****************************************************************************
#define TIMER_TAPR_TAPSR_M      0x000000FF  // GPTM Timer A Prescale
#define TIMER_TAPR_TAPSR_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBPR register.
//
//*****************************************************************************
#define TIMER_TBPR_TBPSR_M      0x000000FF  // GPTM Timer B Prescale
#define TIMER_TBPR_TBPSR_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAPMR register.
//
//*****************************************************************************
#define TIMER_TAPMR_TAPSMR_M    0x000000FF  // GPTM TimerA Prescale Match
#define TIMER_TAPMR_TAPSMR_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBPMR register.
//
//*****************************************************************************
#define TIMER_TBPMR_TBPSMR_M    0x000000FF  // GPTM TimerB Prescale Match
#define TIMER_TBPMR_TBPSMR_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TAR register.
//
//*****************************************************************************
#define TIMER_TAR_TARH_M        0xFFFF0000  // GPTM Timer A Register High
#define TIMER_TAR_TARL_M        0x0000FFFF  // GPTM Timer A Register Low
#define TIMER_TAR_TARH_S        16
#define TIMER_TAR_TARL_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the TIMER_O_TBR register.
//
//*****************************************************************************
#define TIMER_TBR_TBRL_M        0x0000FFFF  // GPTM Timer B
#define TIMER_TBR_TBRL_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_ACTSS register.
//
//*****************************************************************************
#define ADC_ACTSS_ASEN3         0x00000008  // ADC SS3 Enable
#define ADC_ACTSS_ASEN2         0x00000004  // ADC SS2 Enable
#define ADC_ACTSS_ASEN1         0x00000002  // ADC SS1 Enable
#define ADC_ACTSS_ASEN0         0x00000001  // ADC SS0 Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_RIS register.
//
//*****************************************************************************
#define ADC_RIS_INR3            0x00000008  // SS3 Raw Interrupt Status
#define ADC_RIS_INR2            0x00000004  // SS2 Raw Interrupt Status
#define ADC_RIS_INR1            0x00000002  // SS1 Raw Interrupt Status
#define ADC_RIS_INR0            0x00000001  // SS0 Raw Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_IM register.
//
//*****************************************************************************
#define ADC_IM_MASK3            0x00000008  // SS3 Interrupt Mask
#define ADC_IM_MASK2            0x00000004  // SS2 Interrupt Mask
#define ADC_IM_MASK1            0x00000002  // SS1 Interrupt Mask
#define ADC_IM_MASK0            0x00000001  // SS0 Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_ISC register.
//
//*****************************************************************************
#define ADC_ISC_IN3             0x00000008  // SS3 Interrupt Status and Clear
#define ADC_ISC_IN2             0x00000004  // SS2 Interrupt Status and Clear
#define ADC_ISC_IN1             0x00000002  // SS1 Interrupt Status and Clear
#define ADC_ISC_IN0             0x00000001  // SS0 Interrupt Status and Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_OSTAT register.
//
//*****************************************************************************
#define ADC_OSTAT_OV3           0x00000008  // SS3 FIFO Overflow
#define ADC_OSTAT_OV2           0x00000004  // SS2 FIFO Overflow
#define ADC_OSTAT_OV1           0x00000002  // SS1 FIFO Overflow
#define ADC_OSTAT_OV0           0x00000001  // SS0 FIFO Overflow

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_EMUX register.
//
//*****************************************************************************
#define ADC_EMUX_EM3_M          0x0000F000  // SS3 Trigger Select
#define ADC_EMUX_EM3_PROCESSOR  0x00000000  // Processor (default)
#define ADC_EMUX_EM3_COMP0      0x00001000  // Analog Comparator 0
#define ADC_EMUX_EM3_EXTERNAL   0x00004000  // External (GPIO PB4)
#define ADC_EMUX_EM3_TIMER      0x00005000  // Timer
#define ADC_EMUX_EM3_PWM0       0x00006000  // PWM0
#define ADC_EMUX_EM3_PWM1       0x00007000  // PWM1
#define ADC_EMUX_EM3_PWM2       0x00008000  // PWM2
#define ADC_EMUX_EM3_ALWAYS     0x0000F000  // Always (continuously sample)
#define ADC_EMUX_EM2_M          0x00000F00  // SS2 Trigger Select
#define ADC_EMUX_EM2_PROCESSOR  0x00000000  // Processor (default)
#define ADC_EMUX_EM2_COMP0      0x00000100  // Analog Comparator 0
#define ADC_EMUX_EM2_EXTERNAL   0x00000400  // External (GPIO PB4)
#define ADC_EMUX_EM2_TIMER      0x00000500  // Timer
#define ADC_EMUX_EM2_PWM0       0x00000600  // PWM0
#define ADC_EMUX_EM2_PWM1       0x00000700  // PWM1
#define ADC_EMUX_EM2_PWM2       0x00000800  // PWM2
#define ADC_EMUX_EM2_ALWAYS     0x00000F00  // Always (continuously sample)
#define ADC_EMUX_EM1_M          0x000000F0  // SS1 Trigger Select
#define ADC_EMUX_EM1_PROCESSOR  0x00000000  // Processor (default)
#define ADC_EMUX_EM1_COMP0      0x00000010  // Analog Comparator 0
#define ADC_EMUX_EM1_EXTERNAL   0x00000040  // External (GPIO PB4)
#define ADC_EMUX_EM1_TIMER      0x00000050  // Timer
#define ADC_EMUX_EM1_PWM0       0x00000060  // PWM0
#define ADC_EMUX_EM1_PWM1       0x00000070  // PWM1
#define ADC_EMUX_EM1_PWM2       0x00000080  // PWM2
#define ADC_EMUX_EM1_ALWAYS     0x000000F0  // Always (continuously sample)
#define ADC_EMUX_EM0_M          0x0000000F  // SS0 Trigger Select
#define ADC_EMUX_EM0_PROCESSOR  0x00000000  // Processor (default)
#define ADC_EMUX_EM0_COMP0      0x00000001  // Analog Comparator 0
#define ADC_EMUX_EM0_EXTERNAL   0x00000004  // External (GPIO PB4)
#define ADC_EMUX_EM0_TIMER      0x00000005  // Timer
#define ADC_EMUX_EM0_PWM0       0x00000006  // PWM0
#define ADC_EMUX_EM0_PWM1       0x00000007  // PWM1
#define ADC_EMUX_EM0_PWM2       0x00000008  // PWM2
#define ADC_EMUX_EM0_ALWAYS     0x0000000F  // Always (continuously sample)

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_USTAT register.
//
//*****************************************************************************
#define ADC_USTAT_UV3           0x00000008  // SS3 FIFO Underflow
#define ADC_USTAT_UV2           0x00000004  // SS2 FIFO Underflow
#define ADC_USTAT_UV1           0x00000002  // SS1 FIFO Underflow
#define ADC_USTAT_UV0           0x00000001  // SS0 FIFO Underflow

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSPRI register.
//
//*****************************************************************************
#define ADC_SSPRI_SS3_M         0x00003000  // SS3 Priority
#define ADC_SSPRI_SS3_1ST       0x00000000  // First priority
#define ADC_SSPRI_SS3_2ND       0x00001000  // Second priority
#define ADC_SSPRI_SS3_3RD       0x00002000  // Third priority
#define ADC_SSPRI_SS3_4TH       0x00003000  // Fourth priority
#define ADC_SSPRI_SS2_M         0x00000300  // SS2 Priority
#define ADC_SSPRI_SS2_1ST       0x00000000  // First priority
#define ADC_SSPRI_SS2_2ND       0x00000100  // Second priority
#define ADC_SSPRI_SS2_3RD       0x00000200  // Third priority
#define ADC_SSPRI_SS2_4TH       0x00000300  // Fourth priority
#define ADC_SSPRI_SS1_M         0x00000030  // SS1 Priority
#define ADC_SSPRI_SS1_1ST       0x00000000  // First priority
#define ADC_SSPRI_SS1_2ND       0x00000010  // Second priority
#define ADC_SSPRI_SS1_3RD       0x00000020  // Third priority
#define ADC_SSPRI_SS1_4TH       0x00000030  // Fourth priority
#define ADC_SSPRI_SS0_M         0x00000003  // SS0 Priority
#define ADC_SSPRI_SS0_1ST       0x00000000  // First priority
#define ADC_SSPRI_SS0_2ND       0x00000001  // Second priority
#define ADC_SSPRI_SS0_3RD       0x00000002  // Third priority
#define ADC_SSPRI_SS0_4TH       0x00000003  // Fourth priority

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_PSSI register.
//
//*****************************************************************************
#define ADC_PSSI_SS3            0x00000008  // SS3 Initiate
#define ADC_PSSI_SS2            0x00000004  // SS2 Initiate
#define ADC_PSSI_SS1            0x00000002  // SS1 Initiate
#define ADC_PSSI_SS0            0x00000001  // SS0 Initiate

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SAC register.
//
//*****************************************************************************
#define ADC_SAC_AVG_M           0x00000007  // Hardware Averaging Control
#define ADC_SAC_AVG_OFF         0x00000000  // No hardware oversampling
#define ADC_SAC_AVG_2X          0x00000001  // 2x hardware oversampling
#define ADC_SAC_AVG_4X          0x00000002  // 4x hardware oversampling
#define ADC_SAC_AVG_8X          0x00000003  // 8x hardware oversampling
#define ADC_SAC_AVG_16X         0x00000004  // 16x hardware oversampling
#define ADC_SAC_AVG_32X         0x00000005  // 32x hardware oversampling
#define ADC_SAC_AVG_64X         0x00000006  // 64x hardware oversampling

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSMUX0 register.
//
//*****************************************************************************
#define ADC_SSMUX0_MUX7_M       0x30000000  // 8th Sample Input Select
#define ADC_SSMUX0_MUX6_M       0x03000000  // 7th Sample Input Select
#define ADC_SSMUX0_MUX5_M       0x00300000  // 6th Sample Input Select
#define ADC_SSMUX0_MUX4_M       0x00030000  // 5th Sample Input Select
#define ADC_SSMUX0_MUX3_M       0x00003000  // 4th Sample Input Select
#define ADC_SSMUX0_MUX2_M       0x00000300  // 3rd Sample Input Select
#define ADC_SSMUX0_MUX1_M       0x00000030  // 2nd Sample Input Select
#define ADC_SSMUX0_MUX0_M       0x00000003  // 1st Sample Input Select
#define ADC_SSMUX0_MUX7_S       28
#define ADC_SSMUX0_MUX6_S       24
#define ADC_SSMUX0_MUX5_S       20
#define ADC_SSMUX0_MUX4_S       16
#define ADC_SSMUX0_MUX3_S       12
#define ADC_SSMUX0_MUX2_S       8
#define ADC_SSMUX0_MUX1_S       4
#define ADC_SSMUX0_MUX0_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSCTL0 register.
//
//*****************************************************************************
#define ADC_SSCTL0_TS7          0x80000000  // 8th Sample Temp Sensor Select
#define ADC_SSCTL0_IE7          0x40000000  // 8th Sample Interrupt Enable
#define ADC_SSCTL0_END7         0x20000000  // 8th Sample is End of Sequence
#define ADC_SSCTL0_D7           0x10000000  // 8th Sample Diff Input Select
#define ADC_SSCTL0_TS6          0x08000000  // 7th Sample Temp Sensor Select
#define ADC_SSCTL0_IE6          0x04000000  // 7th Sample Interrupt Enable
#define ADC_SSCTL0_END6         0x02000000  // 7th Sample is End of Sequence
#define ADC_SSCTL0_D6           0x01000000  // 7th Sample Diff Input Select
#define ADC_SSCTL0_TS5          0x00800000  // 6th Sample Temp Sensor Select
#define ADC_SSCTL0_IE5          0x00400000  // 6th Sample Interrupt Enable
#define ADC_SSCTL0_END5         0x00200000  // 6th Sample is End of Sequence
#define ADC_SSCTL0_D5           0x00100000  // 6th Sample Diff Input Select
#define ADC_SSCTL0_TS4          0x00080000  // 5th Sample Temp Sensor Select
#define ADC_SSCTL0_IE4          0x00040000  // 5th Sample Interrupt Enable
#define ADC_SSCTL0_END4         0x00020000  // 5th Sample is End of Sequence
#define ADC_SSCTL0_D4           0x00010000  // 5th Sample Diff Input Select
#define ADC_SSCTL0_TS3          0x00008000  // 4th Sample Temp Sensor Select
#define ADC_SSCTL0_IE3          0x00004000  // 4th Sample Interrupt Enable
#define ADC_SSCTL0_END3         0x00002000  // 4th Sample is End of Sequence
#define ADC_SSCTL0_D3           0x00001000  // 4th Sample Diff Input Select
#define ADC_SSCTL0_TS2          0x00000800  // 3rd Sample Temp Sensor Select
#define ADC_SSCTL0_IE2          0x00000400  // 3rd Sample Interrupt Enable
#define ADC_SSCTL0_END2         0x00000200  // 3rd Sample is End of Sequence
#define ADC_SSCTL0_D2           0x00000100  // 3rd Sample Diff Input Select
#define ADC_SSCTL0_TS1          0x00000080  // 2nd Sample Temp Sensor Select
#define ADC_SSCTL0_IE1          0x00000040  // 2nd Sample Interrupt Enable
#define ADC_SSCTL0_END1         0x00000020  // 2nd Sample is End of Sequence
#define ADC_SSCTL0_D1           0x00000010  // 2nd Sample Diff Input Select
#define ADC_SSCTL0_TS0          0x00000008  // 1st Sample Temp Sensor Select
#define ADC_SSCTL0_IE0          0x00000004  // 1st Sample Interrupt Enable
#define ADC_SSCTL0_END0         0x00000002  // 1st Sample is End of Sequence
#define ADC_SSCTL0_D0           0x00000001  // 1st Sample Diff Input Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSFIFO0 register.
//
//*****************************************************************************
#define ADC_SSFIFO0_DATA_M      0x000003FF  // Conversion Result Data
#define ADC_SSFIFO0_DATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSFSTAT0 register.
//
//*****************************************************************************
#define ADC_SSFSTAT0_FULL       0x00001000  // FIFO Full
#define ADC_SSFSTAT0_EMPTY      0x00000100  // FIFO Empty
#define ADC_SSFSTAT0_HPTR_M     0x000000F0  // FIFO Head Pointer
#define ADC_SSFSTAT0_TPTR_M     0x0000000F  // FIFO Tail Pointer
#define ADC_SSFSTAT0_HPTR_S     4
#define ADC_SSFSTAT0_TPTR_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSMUX1 register.
//
//*****************************************************************************
#define ADC_SSMUX1_MUX3_M       0x00003000  // 4th Sample Input Select
#define ADC_SSMUX1_MUX2_M       0x00000300  // 3rd Sample Input Select
#define ADC_SSMUX1_MUX1_M       0x00000030  // 2nd Sample Input Select
#define ADC_SSMUX1_MUX0_M       0x00000003  // 1st Sample Input Select
#define ADC_SSMUX1_MUX3_S       12
#define ADC_SSMUX1_MUX2_S       8
#define ADC_SSMUX1_MUX1_S       4
#define ADC_SSMUX1_MUX0_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSCTL1 register.
//
//*****************************************************************************
#define ADC_SSCTL1_TS3          0x00008000  // 4th Sample Temp Sensor Select
#define ADC_SSCTL1_IE3          0x00004000  // 4th Sample Interrupt Enable
#define ADC_SSCTL1_END3         0x00002000  // 4th Sample is End of Sequence
#define ADC_SSCTL1_D3           0x00001000  // 4th Sample Diff Input Select
#define ADC_SSCTL1_TS2          0x00000800  // 3rd Sample Temp Sensor Select
#define ADC_SSCTL1_IE2          0x00000400  // 3rd Sample Interrupt Enable
#define ADC_SSCTL1_END2         0x00000200  // 3rd Sample is End of Sequence
#define ADC_SSCTL1_D2           0x00000100  // 3rd Sample Diff Input Select
#define ADC_SSCTL1_TS1          0x00000080  // 2nd Sample Temp Sensor Select
#define ADC_SSCTL1_IE1          0x00000040  // 2nd Sample Interrupt Enable
#define ADC_SSCTL1_END1         0x00000020  // 2nd Sample is End of Sequence
#define ADC_SSCTL1_D1           0x00000010  // 2nd Sample Diff Input Select
#define ADC_SSCTL1_TS0          0x00000008  // 1st Sample Temp Sensor Select
#define ADC_SSCTL1_IE0          0x00000004  // 1st Sample Interrupt Enable
#define ADC_SSCTL1_END0         0x00000002  // 1st Sample is End of Sequence
#define ADC_SSCTL1_D0           0x00000001  // 1st Sample Diff Input Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSFIFO1 register.
//
//*****************************************************************************
#define ADC_SSFIFO1_DATA_M      0x000003FF  // Conversion Result Data
#define ADC_SSFIFO1_DATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSFSTAT1 register.
//
//*****************************************************************************
#define ADC_SSFSTAT1_FULL       0x00001000  // FIFO Full
#define ADC_SSFSTAT1_EMPTY      0x00000100  // FIFO Empty
#define ADC_SSFSTAT1_HPTR_M     0x000000F0  // FIFO Head Pointer
#define ADC_SSFSTAT1_TPTR_M     0x0000000F  // FIFO Tail Pointer
#define ADC_SSFSTAT1_HPTR_S     4
#define ADC_SSFSTAT1_TPTR_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSMUX2 register.
//
//*****************************************************************************
#define ADC_SSMUX2_MUX3_M       0x00003000  // 4th Sample Input Select
#define ADC_SSMUX2_MUX2_M       0x00000300  // 3rd Sample Input Select
#define ADC_SSMUX2_MUX1_M       0x00000030  // 2nd Sample Input Select
#define ADC_SSMUX2_MUX0_M       0x00000003  // 1st Sample Input Select
#define ADC_SSMUX2_MUX3_S       12
#define ADC_SSMUX2_MUX2_S       8
#define ADC_SSMUX2_MUX1_S       4
#define ADC_SSMUX2_MUX0_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSCTL2 register.
//
//*****************************************************************************
#define ADC_SSCTL2_TS3          0x00008000  // 4th Sample Temp Sensor Select
#define ADC_SSCTL2_IE3          0x00004000  // 4th Sample Interrupt Enable
#define ADC_SSCTL2_END3         0x00002000  // 4th Sample is End of Sequence
#define ADC_SSCTL2_D3           0x00001000  // 4th Sample Diff Input Select
#define ADC_SSCTL2_TS2          0x00000800  // 3rd Sample Temp Sensor Select
#define ADC_SSCTL2_IE2          0x00000400  // 3rd Sample Interrupt Enable
#define ADC_SSCTL2_END2         0x00000200  // 3rd Sample is End of Sequence
#define ADC_SSCTL2_D2           0x00000100  // 3rd Sample Diff Input Select
#define ADC_SSCTL2_TS1          0x00000080  // 2nd Sample Temp Sensor Select
#define ADC_SSCTL2_IE1          0x00000040  // 2nd Sample Interrupt Enable
#define ADC_SSCTL2_END1         0x00000020  // 2nd Sample is End of Sequence
#define ADC_SSCTL2_D1           0x00000010  // 2nd Sample Diff Input Select
#define ADC_SSCTL2_TS0          0x00000008  // 1st Sample Temp Sensor Select
#define ADC_SSCTL2_IE0          0x00000004  // 1st Sample Interrupt Enable
#define ADC_SSCTL2_END0         0x00000002  // 1st Sample is End of Sequence
#define ADC_SSCTL2_D0           0x00000001  // 1st Sample Diff Input Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSFIFO2 register.
//
//*****************************************************************************
#define ADC_SSFIFO2_DATA_M      0x000003FF  // Conversion Result Data
#define ADC_SSFIFO2_DATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSFSTAT2 register.
//
//*****************************************************************************
#define ADC_SSFSTAT2_FULL       0x00001000  // FIFO Full
#define ADC_SSFSTAT2_EMPTY      0x00000100  // FIFO Empty
#define ADC_SSFSTAT2_HPTR_M     0x000000F0  // FIFO Head Pointer
#define ADC_SSFSTAT2_TPTR_M     0x0000000F  // FIFO Tail Pointer
#define ADC_SSFSTAT2_HPTR_S     4
#define ADC_SSFSTAT2_TPTR_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSMUX3 register.
//
//*****************************************************************************
#define ADC_SSMUX3_MUX0_M       0x00000003  // 1st Sample Input Select
#define ADC_SSMUX3_MUX0_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSCTL3 register.
//
//*****************************************************************************
#define ADC_SSCTL3_TS0          0x00000008  // 1st Sample Temp Sensor Select
#define ADC_SSCTL3_IE0          0x00000004  // 1st Sample Interrupt Enable
#define ADC_SSCTL3_END0         0x00000002  // 1st Sample is End of Sequence
#define ADC_SSCTL3_D0           0x00000001  // 1st Sample Diff Input Select

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSFIFO3 register.
//
//*****************************************************************************
#define ADC_SSFIFO3_DATA_M      0x000003FF  // Conversion Result Data
#define ADC_SSFIFO3_DATA_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_SSFSTAT3 register.
//
//*****************************************************************************
#define ADC_SSFSTAT3_FULL       0x00001000  // FIFO Full
#define ADC_SSFSTAT3_EMPTY      0x00000100  // FIFO Empty
#define ADC_SSFSTAT3_HPTR_M     0x000000F0  // FIFO Head Pointer
#define ADC_SSFSTAT3_TPTR_M     0x0000000F  // FIFO Tail Pointer
#define ADC_SSFSTAT3_HPTR_S     4
#define ADC_SSFSTAT3_TPTR_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the ADC_O_TMLB register.
//
//*****************************************************************************
#define ADC_TMLB_LB             0x00000001  // Loopback Mode Enable

//*****************************************************************************
//
// The following are defines for the the interpretation of the data in the
// SSFIFOx when the ADC TMLB is enabled.
//
//*****************************************************************************
#define ADC_SSFIFO_TMLB_CNT_M   0x000003C0  // Continuous Sample Counter
#define ADC_SSFIFO_TMLB_CONT    0x00000020  // Continuation Sample Indicator
#define ADC_SSFIFO_TMLB_DIFF    0x00000010  // Differential Sample Indicator
#define ADC_SSFIFO_TMLB_TS      0x00000008  // Temp Sensor Sample Indicator
#define ADC_SSFIFO_TMLB_MUX_M   0x00000007  // Analog Input Indicator
#define ADC_SSFIFO_TMLB_CNT_S   6           // Sample counter shift
#define ADC_SSFIFO_TMLB_MUX_S   0           // Input channel number shift

//*****************************************************************************
//
// The following are defines for the bit fields in the COMP_O_ACMIS register.
//
//*****************************************************************************
#define COMP_ACMIS_IN0          0x00000001  // Comparator 0 Masked Interrupt
                                            // Status

//*****************************************************************************
//
// The following are defines for the bit fields in the COMP_O_ACRIS register.
//
//*****************************************************************************
#define COMP_ACRIS_IN0          0x00000001  // Comparator 0 Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the COMP_O_ACINTEN register.
//
//*****************************************************************************
#define COMP_ACINTEN_IN0        0x00000001  // Comparator 0 Interrupt Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the COMP_O_ACREFCTL
// register.
//
//*****************************************************************************
#define COMP_ACREFCTL_EN        0x00000200  // Resistor Ladder Enable
#define COMP_ACREFCTL_RNG       0x00000100  // Resistor Ladder Range
#define COMP_ACREFCTL_VREF_M    0x0000000F  // Resistor Ladder Voltage Ref
#define COMP_ACREFCTL_VREF_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the COMP_O_ACSTAT0 register.
//
//*****************************************************************************
#define COMP_ACSTAT0_OVAL       0x00000002  // Comparator Output Value

//*****************************************************************************
//
// The following are defines for the bit fields in the COMP_O_ACCTL0 register.
//
//*****************************************************************************
#define COMP_ACCTL0_TOEN        0x00000800  // Trigger Output Enable
#define COMP_ACCTL0_ASRCP_M     0x00000600  // Analog Source Positive
#define COMP_ACCTL0_ASRCP_PIN   0x00000000  // Pin value of Cn+
#define COMP_ACCTL0_ASRCP_PIN0  0x00000200  // Pin value of C0+
#define COMP_ACCTL0_ASRCP_REF   0x00000400  // Internal voltage reference
                                            // (VIREF)
#define COMP_ACCTL0_TSLVAL      0x00000080  // Trigger Sense Level Value
#define COMP_ACCTL0_TSEN_M      0x00000060  // Trigger Sense
#define COMP_ACCTL0_TSEN_LEVEL  0x00000000  // Level sense, see TSLVAL
#define COMP_ACCTL0_TSEN_FALL   0x00000020  // Falling edge
#define COMP_ACCTL0_TSEN_RISE   0x00000040  // Rising edge
#define COMP_ACCTL0_TSEN_BOTH   0x00000060  // Either edge
#define COMP_ACCTL0_ISLVAL      0x00000010  // Interrupt Sense Level Value
#define COMP_ACCTL0_ISEN_M      0x0000000C  // Interrupt Sense
#define COMP_ACCTL0_ISEN_LEVEL  0x00000000  // Level sense, see ISLVAL
#define COMP_ACCTL0_ISEN_FALL   0x00000004  // Falling edge
#define COMP_ACCTL0_ISEN_RISE   0x00000008  // Rising edge
#define COMP_ACCTL0_ISEN_BOTH   0x0000000C  // Either edge
#define COMP_ACCTL0_CINV        0x00000002  // Comparator Output Invert

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_CTL register.
//
//*****************************************************************************
#define CAN_CTL_TEST            0x00000080  // Test Mode Enable
#define CAN_CTL_CCE             0x00000040  // Configuration Change Enable
#define CAN_CTL_DAR             0x00000020  // Disable Automatic-Retransmission
#define CAN_CTL_EIE             0x00000008  // Error Interrupt Enable
#define CAN_CTL_SIE             0x00000004  // Status Interrupt Enable
#define CAN_CTL_IE              0x00000002  // CAN Interrupt Enable
#define CAN_CTL_INIT            0x00000001  // Initialization

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_STS register.
//
//*****************************************************************************
#define CAN_STS_BOFF            0x00000080  // Bus-Off Status
#define CAN_STS_EWARN           0x00000040  // Warning Status
#define CAN_STS_EPASS           0x00000020  // Error Passive
#define CAN_STS_RXOK            0x00000010  // Received a Message Successfully
#define CAN_STS_TXOK            0x00000008  // Transmitted a Message
                                            // Successfully
#define CAN_STS_LEC_M           0x00000007  // Last Error Code
#define CAN_STS_LEC_NONE        0x00000000  // No Error
#define CAN_STS_LEC_STUFF       0x00000001  // Stuff Error
#define CAN_STS_LEC_FORM        0x00000002  // Format Error
#define CAN_STS_LEC_ACK         0x00000003  // ACK Error
#define CAN_STS_LEC_BIT1        0x00000004  // Bit 1 Error
#define CAN_STS_LEC_BIT0        0x00000005  // Bit 0 Error
#define CAN_STS_LEC_CRC         0x00000006  // CRC Error
#define CAN_STS_LEC_NOEVENT     0x00000007  // No Event

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_ERR register.
//
//*****************************************************************************
#define CAN_ERR_RP              0x00008000  // Received Error Passive
#define CAN_ERR_REC_M           0x00007F00  // Receive Error Counter
#define CAN_ERR_TEC_M           0x000000FF  // Transmit Error Counter
#define CAN_ERR_REC_S           8
#define CAN_ERR_TEC_S           0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_BIT register.
//
//*****************************************************************************
#define CAN_BIT_TSEG2_M         0x00007000  // Time Segment after Sample Point
#define CAN_BIT_TSEG1_M         0x00000F00  // Time Segment Before Sample Point
#define CAN_BIT_SJW_M           0x000000C0  // (Re)Synchronization Jump Width
#define CAN_BIT_BRP_M           0x0000003F  // Baud Rate Prescaler
#define CAN_BIT_TSEG2_S         12
#define CAN_BIT_TSEG1_S         8
#define CAN_BIT_SJW_S           6
#define CAN_BIT_BRP_S           0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_INT register.
//
//*****************************************************************************
#define CAN_INT_INTID_M         0x0000FFFF  // Interrupt Identifier
#define CAN_INT_INTID_NONE      0x00000000  // No interrupt pending
#define CAN_INT_INTID_STATUS    0x00008000  // Status Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_TST register.
//
//*****************************************************************************
#define CAN_TST_RX              0x00000080  // Receive Observation
#define CAN_TST_TX_M            0x00000060  // Transmit Control
#define CAN_TST_TX_CANCTL       0x00000000  // CAN Module Control
#define CAN_TST_TX_SAMPLE       0x00000020  // Sample Point
#define CAN_TST_TX_DOMINANT     0x00000040  // Driven Low
#define CAN_TST_TX_RECESSIVE    0x00000060  // Driven High
#define CAN_TST_LBACK           0x00000010  // Loopback Mode
#define CAN_TST_SILENT          0x00000008  // Silent Mode
#define CAN_TST_BASIC           0x00000004  // Basic Mode

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_BRPE register.
//
//*****************************************************************************
#define CAN_BRPE_BRPE_M         0x0000000F  // Baud Rate Prescaler Extension
#define CAN_BRPE_BRPE_S         0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1CRQ register.
//
//*****************************************************************************
#define CAN_IF1CRQ_BUSY         0x00008000  // Busy Flag
#define CAN_IF1CRQ_MNUM_M       0x0000003F  // Message Number
#define CAN_IF1CRQ_MNUM_RSVD    0x00000000  // 0 is not a valid message number;
                                            // it is interpreted as 0x20, or
                                            // object 32
#define CAN_IF1CRQ_MNUM_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1CMSK register.
//
//*****************************************************************************
#define CAN_IF1CMSK_WRNRD       0x00000080  // Write, Not Read
#define CAN_IF1CMSK_MASK        0x00000040  // Access Mask Bits
#define CAN_IF1CMSK_ARB         0x00000020  // Access Arbitration Bits
#define CAN_IF1CMSK_CONTROL     0x00000010  // Access Control Bits
#define CAN_IF1CMSK_CLRINTPND   0x00000008  // Clear Interrupt Pending Bit
#define CAN_IF1CMSK_NEWDAT      0x00000004  // Access New Data
#define CAN_IF1CMSK_TXRQST      0x00000004  // Access Transmission Request
#define CAN_IF1CMSK_DATAA       0x00000002  // Access Data Byte 0 to 3
#define CAN_IF1CMSK_DATAB       0x00000001  // Access Data Byte 4 to 7

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1MSK1 register.
//
//*****************************************************************************
#define CAN_IF1MSK1_IDMSK_M     0x0000FFFF  // Identifier Mask
#define CAN_IF1MSK1_IDMSK_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1MSK2 register.
//
//*****************************************************************************
#define CAN_IF1MSK2_MXTD        0x00008000  // Mask Extended Identifier
#define CAN_IF1MSK2_MDIR        0x00004000  // Mask Message Direction
#define CAN_IF1MSK2_IDMSK_M     0x00001FFF  // Identifier Mask
#define CAN_IF1MSK2_IDMSK_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1ARB1 register.
//
//*****************************************************************************
#define CAN_IF1ARB1_ID_M        0x0000FFFF  // Message Identifier
#define CAN_IF1ARB1_ID_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1ARB2 register.
//
//*****************************************************************************
#define CAN_IF1ARB2_MSGVAL      0x00008000  // Message Valid
#define CAN_IF1ARB2_XTD         0x00004000  // Extended Identifier
#define CAN_IF1ARB2_DIR         0x00002000  // Message Direction
#define CAN_IF1ARB2_ID_M        0x00001FFF  // Message Identifier
#define CAN_IF1ARB2_ID_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1MCTL register.
//
//*****************************************************************************
#define CAN_IF1MCTL_NEWDAT      0x00008000  // New Data
#define CAN_IF1MCTL_MSGLST      0x00004000  // Message Lost
#define CAN_IF1MCTL_INTPND      0x00002000  // Interrupt Pending
#define CAN_IF1MCTL_UMASK       0x00001000  // Use Acceptance Mask
#define CAN_IF1MCTL_TXIE        0x00000800  // Transmit Interrupt Enable
#define CAN_IF1MCTL_RXIE        0x00000400  // Receive Interrupt Enable
#define CAN_IF1MCTL_RMTEN       0x00000200  // Remote Enable
#define CAN_IF1MCTL_TXRQST      0x00000100  // Transmit Request
#define CAN_IF1MCTL_EOB         0x00000080  // End of Buffer
#define CAN_IF1MCTL_DLC_M       0x0000000F  // Data Length Code
#define CAN_IF1MCTL_DLC_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1DA1 register.
//
//*****************************************************************************
#define CAN_IF1DA1_DATA_M       0x0000FFFF  // Data
#define CAN_IF1DA1_DATA_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1DA2 register.
//
//*****************************************************************************
#define CAN_IF1DA2_DATA_M       0x0000FFFF  // Data
#define CAN_IF1DA2_DATA_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1DB1 register.
//
//*****************************************************************************
#define CAN_IF1DB1_DATA_M       0x0000FFFF  // Data
#define CAN_IF1DB1_DATA_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF1DB2 register.
//
//*****************************************************************************
#define CAN_IF1DB2_DATA_M       0x0000FFFF  // Data
#define CAN_IF1DB2_DATA_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF2CRQ register.
//
//*****************************************************************************
#define CAN_IF2CRQ_BUSY         0x00008000  // Busy Flag
#define CAN_IF2CRQ_MNUM_M       0x0000003F  // Message Number
#define CAN_IF2CRQ_MNUM_RSVD    0x00000000  // 0 is not a valid message number;
                                            // it is interpreted as 0x20, or
                                            // object 32
#define CAN_IF2CRQ_MNUM_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF2CMSK register.
//
//*****************************************************************************
#define CAN_IF2CMSK_WRNRD       0x00000080  // Write, Not Read
#define CAN_IF2CMSK_MASK        0x00000040  // Access Mask Bits
#define CAN_IF2CMSK_ARB         0x00000020  // Access Arbitration Bits
#define CAN_IF2CMSK_CONTROL     0x00000010  // Access Control Bits
#define CAN_IF2CMSK_CLRINTPND   0x00000008  // Clear Interrupt Pending Bit
#define CAN_IF2CMSK_NEWDAT      0x00000004  // Access New Data
#define CAN_IF2CMSK_TXRQST      0x00000004  // Access Transmission Request
#define CAN_IF2CMSK_DATAA       0x00000002  // Access Data Byte 0 to 3
#define CAN_IF2CMSK_DATAB       0x00000001  // Access Data Byte 4 to 7

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF2MSK1 register.
//
//*****************************************************************************
#define CAN_IF2MSK1_IDMSK_M     0x0000FFFF  // Identifier Mask
#define CAN_IF2MSK1_IDMSK_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF2MSK2 register.
//
//*****************************************************************************
#define CAN_IF2MSK2_MXTD        0x00008000  // Mask Extended Identifier
#define CAN_IF2MSK2_MDIR        0x00004000  // Mask Message Direction
#define CAN_IF2MSK2_IDMSK_M     0x00001FFF  // Identifier Mask
#define CAN_IF2MSK2_IDMSK_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF2ARB1 register.
//
//*****************************************************************************
#define CAN_IF2ARB1_ID_M        0x0000FFFF  // Message Identifier
#define CAN_IF2ARB1_ID_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF2ARB2 register.
//
//*****************************************************************************
#define CAN_IF2ARB2_MSGVAL      0x00008000  // Message Valid
#define CAN_IF2ARB2_XTD         0x00004000  // Extended Identifier
#define CAN_IF2ARB2_DIR         0x00002000  // Message Direction
#define CAN_IF2ARB2_ID_M        0x00001FFF  // Message Identifier
#define CAN_IF2ARB2_ID_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF2MCTL register.
//
//*****************************************************************************
#define CAN_IF2MCTL_NEWDAT      0x00008000  // New Data
#define CAN_IF2MCTL_MSGLST      0x00004000  // Message Lost
#define CAN_IF2MCTL_INTPND      0x00002000  // Interrupt Pending
#define CAN_IF2MCTL_UMASK       0x00001000  // Use Acceptance Mask
#define CAN_IF2MCTL_TXIE        0x00000800  // Transmit Interrupt Enable
#define CAN_IF2MCTL_RXIE        0x00000400  // Receive Interrupt Enable
#define CAN_IF2MCTL_RMTEN       0x00000200  // Remote Enable
#define CAN_IF2MCTL_TXRQST      0x00000100  // Transmit Request
#define CAN_IF2MCTL_EOB         0x00000080  // End of Buffer
#define CAN_IF2MCTL_DLC_M       0x0000000F  // Data Length Code
#define CAN_IF2MCTL_DLC_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF2DA1 register.
//
//*****************************************************************************
#define CAN_IF2DA1_DATA_M       0x0000FFFF  // Data
#define CAN_IF2DA1_DATA_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF2DA2 register.
//
//*****************************************************************************
#define CAN_IF2DA2_DATA_M       0x0000FFFF  // Data
#define CAN_IF2DA2_DATA_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF2DB1 register.
//
//*****************************************************************************
#define CAN_IF2DB1_DATA_M       0x0000FFFF  // Data
#define CAN_IF2DB1_DATA_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_IF2DB2 register.
//
//*****************************************************************************
#define CAN_IF2DB2_DATA_M       0x0000FFFF  // Data
#define CAN_IF2DB2_DATA_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_TXRQ1 register.
//
//*****************************************************************************
#define CAN_TXRQ1_TXRQST_M      0x0000FFFF  // Transmission Request Bits
#define CAN_TXRQ1_TXRQST_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_TXRQ2 register.
//
//*****************************************************************************
#define CAN_TXRQ2_TXRQST_M      0x0000FFFF  // Transmission Request Bits
#define CAN_TXRQ2_TXRQST_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_NWDA1 register.
//
//*****************************************************************************
#define CAN_NWDA1_NEWDAT_M      0x0000FFFF  // New Data Bits
#define CAN_NWDA1_NEWDAT_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_NWDA2 register.
//
//*****************************************************************************
#define CAN_NWDA2_NEWDAT_M      0x0000FFFF  // New Data Bits
#define CAN_NWDA2_NEWDAT_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_MSG1INT register.
//
//*****************************************************************************
#define CAN_MSG1INT_INTPND_M    0x0000FFFF  // Interrupt Pending Bits
#define CAN_MSG1INT_INTPND_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_MSG2INT register.
//
//*****************************************************************************
#define CAN_MSG2INT_INTPND_M    0x0000FFFF  // Interrupt Pending Bits
#define CAN_MSG2INT_INTPND_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_MSG1VAL register.
//
//*****************************************************************************
#define CAN_MSG1VAL_MSGVAL_M    0x0000FFFF  // Message Valid Bits
#define CAN_MSG1VAL_MSGVAL_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the CAN_O_MSG2VAL register.
//
//*****************************************************************************
#define CAN_MSG2VAL_MSGVAL_M    0x0000FFFF  // Message Valid Bits
#define CAN_MSG2VAL_MSGVAL_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_O_RIS register.
//
//*****************************************************************************
#define MAC_RIS_PHYINT          0x00000040  // PHY Interrupt
#define MAC_RIS_MDINT           0x00000020  // MII Transaction Complete
#define MAC_RIS_RXER            0x00000010  // Receive Error
#define MAC_RIS_FOV             0x00000008  // FIFO Overrun
#define MAC_RIS_TXEMP           0x00000004  // Transmit FIFO Empty
#define MAC_RIS_TXER            0x00000002  // Transmit Error
#define MAC_RIS_RXINT           0x00000001  // Packet Received

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_O_IACK register.
//
//*****************************************************************************
#define MAC_IACK_PHYINT         0x00000040  // Clear PHY Interrupt
#define MAC_IACK_MDINT          0x00000020  // Clear MII Transaction Complete
#define MAC_IACK_RXER           0x00000010  // Clear Receive Error
#define MAC_IACK_FOV            0x00000008  // Clear FIFO Overrun
#define MAC_IACK_TXEMP          0x00000004  // Clear Transmit FIFO Empty
#define MAC_IACK_TXER           0x00000002  // Clear Transmit Error
#define MAC_IACK_RXINT          0x00000001  // Clear Packet Received

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_O_IM register.
//
//*****************************************************************************
#define MAC_IM_PHYINTM          0x00000040  // Mask PHY Interrupt
#define MAC_IM_MDINTM           0x00000020  // Mask MII Transaction Complete
#define MAC_IM_RXERM            0x00000010  // Mask Receive Error
#define MAC_IM_FOVM             0x00000008  // Mask FIFO Overrun
#define MAC_IM_TXEMPM           0x00000004  // Mask Transmit FIFO Empty
#define MAC_IM_TXERM            0x00000002  // Mask Transmit Error
#define MAC_IM_RXINTM           0x00000001  // Mask Packet Received

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_O_RCTL register.
//
//*****************************************************************************
#define MAC_RCTL_RSTFIFO        0x00000010  // Clear Receive FIFO
#define MAC_RCTL_BADCRC         0x00000008  // Enable Reject Bad CRC
#define MAC_RCTL_PRMS           0x00000004  // Enable Promiscuous Mode
#define MAC_RCTL_AMUL           0x00000002  // Enable Multicast Frames
#define MAC_RCTL_RXEN           0x00000001  // Enable Receiver

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_O_TCTL register.
//
//*****************************************************************************
#define MAC_TCTL_DUPLEX         0x00000010  // Enable Duplex Mode
#define MAC_TCTL_CRC            0x00000004  // Enable CRC Generation
#define MAC_TCTL_PADEN          0x00000002  // Enable Packet Padding
#define MAC_TCTL_TXEN           0x00000001  // Enable Transmitter

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_O_DATA register.
//
//*****************************************************************************
#define MAC_DATA_TXDATA_M       0xFFFFFFFF  // Transmit FIFO Data
#define MAC_DATA_RXDATA_M       0xFFFFFFFF  // Receive FIFO Data
#define MAC_DATA_RXDATA_S       0
#define MAC_DATA_TXDATA_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_O_IA0 register.
//
//*****************************************************************************
#define MAC_IA0_MACOCT4_M       0xFF000000  // MAC Address Octet 4
#define MAC_IA0_MACOCT3_M       0x00FF0000  // MAC Address Octet 3
#define MAC_IA0_MACOCT2_M       0x0000FF00  // MAC Address Octet 2
#define MAC_IA0_MACOCT1_M       0x000000FF  // MAC Address Octet 1
#define MAC_IA0_MACOCT4_S       24
#define MAC_IA0_MACOCT3_S       16
#define MAC_IA0_MACOCT2_S       8
#define MAC_IA0_MACOCT1_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_O_IA1 register.
//
//*****************************************************************************
#define MAC_IA1_MACOCT6_M       0x0000FF00  // MAC Address Octet 6
#define MAC_IA1_MACOCT5_M       0x000000FF  // MAC Address Octet 5
#define MAC_IA1_MACOCT6_S       8
#define MAC_IA1_MACOCT5_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_O_THR register.
//
//*****************************************************************************
#define MAC_THR_THRESH_M        0x0000003F  // Threshold Value
#define MAC_THR_THRESH_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_O_MCTL register.
//
//*****************************************************************************
#define MAC_MCTL_REGADR_M       0x000000F8  // MII Register Address
#define MAC_MCTL_WRITE          0x00000002  // MII Register Transaction Type
#define MAC_MCTL_START          0x00000001  // MII Register Transaction Enable
#define MAC_MCTL_REGADR_S       3

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_O_MDV register.
//
//*****************************************************************************
#define MAC_MDV_DIV_M           0x000000FF  // Clock Divider
#define MAC_MDV_DIV_S           0

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_O_MTXD register.
//
//*****************************************************************************
#define MAC_MTXD_MDTX_M         0x0000FFFF  // MII Register Transmit Data
#define MAC_MTXD_MDTX_S         0

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_O_MRXD register.
//
//*****************************************************************************
#define MAC_MRXD_MDRX_M         0x0000FFFF  // MII Register Receive Data
#define MAC_MRXD_MDRX_S         0

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_O_NP register.
//
//*****************************************************************************
#define MAC_NP_NPR_M            0x0000003F  // Number of Packets in Receive
                                            // FIFO
#define MAC_NP_NPR_S            0

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_O_TR register.
//
//*****************************************************************************
#define MAC_TR_NEWTX            0x00000001  // New Transmission

//*****************************************************************************
//
// The following are defines for the bit fields in the MAC_O_TS register.
//
//*****************************************************************************
#define MAC_TS_TSEN             0x00000001  // Time Stamp Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the PHY_MR0 register.
//
//*****************************************************************************
#define PHY_MR0_RESET           0x00008000  // Reset Registers
#define PHY_MR0_LOOPBK          0x00004000  // Loopback Mode
#define PHY_MR0_SPEEDSL         0x00002000  // Speed Select
#define PHY_MR0_ANEGEN          0x00001000  // Auto-Negotiation Enable
#define PHY_MR0_PWRDN           0x00000800  // Power Down
#define PHY_MR0_ISO             0x00000400  // Isolate
#define PHY_MR0_RANEG           0x00000200  // Restart Auto-Negotiation
#define PHY_MR0_DUPLEX          0x00000100  // Set Duplex Mode
#define PHY_MR0_COLT            0x00000080  // Collision Test

//*****************************************************************************
//
// The following are defines for the bit fields in the PHY_MR1 register.
//
//*****************************************************************************
#define PHY_MR1_100X_F          0x00004000  // 100BASE-TX Full-Duplex Mode
#define PHY_MR1_100X_H          0x00002000  // 100BASE-TX Half-Duplex Mode
#define PHY_MR1_10T_F           0x00001000  // 10BASE-T Full-Duplex Mode
#define PHY_MR1_10T_H           0x00000800  // 10BASE-T Half-Duplex Mode
#define PHY_MR1_MFPS            0x00000040  // Management Frames with Preamble
                                            // Suppressed
#define PHY_MR1_ANEGC           0x00000020  // Auto-Negotiation Complete
#define PHY_MR1_RFAULT          0x00000010  // Remote Fault
#define PHY_MR1_ANEGA           0x00000008  // Auto-Negotiation
#define PHY_MR1_LINK            0x00000004  // Link Made
#define PHY_MR1_JAB             0x00000002  // Jabber Condition
#define PHY_MR1_EXTD            0x00000001  // Extended Capabilities

//*****************************************************************************
//
// The following are defines for the bit fields in the PHY_MR2 register.
//
//*****************************************************************************
#define PHY_MR2_OUI_M           0x0000FFFF  // Organizationally Unique
                                            // Identifier[21:6]
#define PHY_MR2_OUI_S           0

//*****************************************************************************
//
// The following are defines for the bit fields in the PHY_MR3 register.
//
//*****************************************************************************
#define PHY_MR3_OUI_M           0x0000FC00  // Organizationally Unique
                                            // Identifier[5:0]
#define PHY_MR3_MN_M            0x000003F0  // Model Number
#define PHY_MR3_RN_M            0x0000000F  // Revision Number
#define PHY_MR3_OUI_S           10
#define PHY_MR3_MN_S            4
#define PHY_MR3_RN_S            0

//*****************************************************************************
//
// The following are defines for the bit fields in the PHY_MR4 register.
//
//*****************************************************************************
#define PHY_MR4_NP              0x00008000  // Next Page
#define PHY_MR4_RF              0x00002000  // Remote Fault
#define PHY_MR4_A3              0x00000100  // Technology Ability Field [3]
#define PHY_MR4_A2              0x00000080  // Technology Ability Field [2]
#define PHY_MR4_A1              0x00000040  // Technology Ability Field [1]
#define PHY_MR4_A0              0x00000020  // Technology Ability Field [0]
#define PHY_MR4_S_M             0x0000001F  // Selector Field
#define PHY_MR4_S_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the PHY_MR5 register.
//
//*****************************************************************************
#define PHY_MR5_NP              0x00008000  // Next Page
#define PHY_MR5_ACK             0x00004000  // Acknowledge
#define PHY_MR5_RF              0x00002000  // Remote Fault
#define PHY_MR5_A_M             0x00001FE0  // Technology Ability Field
#define PHY_MR5_S_M             0x0000001F  // Selector Field
#define PHY_MR5_S_8023          0x00000001  // IEEE Std 802.3
#define PHY_MR5_S_8029          0x00000002  // IEEE Std 802.9 ISLAN-16T
#define PHY_MR5_S_8025          0x00000003  // IEEE Std 802.5
#define PHY_MR5_S_1394          0x00000004  // IEEE Std 1394
#define PHY_MR5_A_S             5

//*****************************************************************************
//
// The following are defines for the bit fields in the PHY_MR6 register.
//
//*****************************************************************************
#define PHY_MR6_PDF             0x00000010  // Parallel Detection Fault
#define PHY_MR6_LPNPA           0x00000008  // Link Partner is Next Page Able
#define PHY_MR6_PRX             0x00000002  // New Page Received
#define PHY_MR6_LPANEGA         0x00000001  // Link Partner is Auto-Negotiation
                                            // Able

//*****************************************************************************
//
// The following are defines for the bit fields in the PHY_MR16 register.
//
//*****************************************************************************
#define PHY_MR16_RPTR           0x00008000  // Repeater Mode
#define PHY_MR16_INPOL          0x00004000  // Interrupt Polarity
#define PHY_MR16_TXHIM          0x00001000  // Transmit High Impedance Mode
#define PHY_MR16_SQEI           0x00000800  // SQE Inhibit Testing
#define PHY_MR16_NL10           0x00000400  // Natural Loopback Mode
#define PHY_MR16_APOL           0x00000020  // Auto-Polarity Disable
#define PHY_MR16_RVSPOL         0x00000010  // Receive Data Polarity
#define PHY_MR16_PCSBP          0x00000002  // PCS Bypass
#define PHY_MR16_RXCC           0x00000001  // Receive Clock Control

//*****************************************************************************
//
// The following are defines for the bit fields in the PHY_MR17 register.
//
//*****************************************************************************
#define PHY_MR17_JABBER_IE      0x00008000  // Jabber Interrupt Enable
#define PHY_MR17_RXER_IE        0x00004000  // Receive Error Interrupt Enable
#define PHY_MR17_PRX_IE         0x00002000  // Page Received Interrupt Enable
#define PHY_MR17_PDF_IE         0x00001000  // Parallel Detection Fault
                                            // Interrupt Enable
#define PHY_MR17_LPACK_IE       0x00000800  // LP Acknowledge Interrupt Enable
#define PHY_MR17_LSCHG_IE       0x00000400  // Link Status Change Interrupt
                                            // Enable
#define PHY_MR17_RFAULT_IE      0x00000200  // Remote Fault Interrupt Enable
#define PHY_MR17_ANEGCOMP_IE    0x00000100  // Auto-Negotiation Complete
                                            // Interrupt Enable
#define PHY_MR17_JABBER_INT     0x00000080  // Jabber Event Interrupt
#define PHY_MR17_RXER_INT       0x00000040  // Receive Error Interrupt
#define PHY_MR17_PRX_INT        0x00000020  // Page Receive Interrupt
#define PHY_MR17_PDF_INT        0x00000010  // Parallel Detection Fault
                                            // Interrupt
#define PHY_MR17_LPACK_INT      0x00000008  // LP Acknowledge Interrupt
#define PHY_MR17_LSCHG_INT      0x00000004  // Link Status Change Interrupt
#define PHY_MR17_RFAULT_INT     0x00000002  // Remote Fault Interrupt
#define PHY_MR17_ANEGCOMP_INT   0x00000001  // Auto-Negotiation Complete
                                            // Interrupt

//*****************************************************************************
//
// The following are defines for the bit fields in the PHY_MR18 register.
//
//*****************************************************************************
#define PHY_MR18_ANEGF          0x00001000  // Auto-Negotiation Failure
#define PHY_MR18_DPLX           0x00000800  // Duplex Mode
#define PHY_MR18_RATE           0x00000400  // Rate
#define PHY_MR18_RXSD           0x00000200  // Receive Detection
#define PHY_MR18_RX_LOCK        0x00000100  // Receive PLL Lock

//*****************************************************************************
//
// The following are defines for the bit fields in the PHY_MR19 register.
//
//*****************************************************************************
#define PHY_MR19_TXO_M          0x0000C000  // Transmit Amplitude Selection
#define PHY_MR19_TXO_00DB       0x00000000  // Gain set for 0.0dB of insertion
                                            // loss
#define PHY_MR19_TXO_04DB       0x00004000  // Gain set for 0.4dB of insertion
                                            // loss
#define PHY_MR19_TXO_08DB       0x00008000  // Gain set for 0.8dB of insertion
                                            // loss
#define PHY_MR19_TXO_12DB       0x0000C000  // Gain set for 1.2dB of insertion
                                            // loss

//*****************************************************************************
//
// The following are defines for the bit fields in the PHY_MR23 register.
//
//*****************************************************************************
#define PHY_MR23_LED1_M         0x000000F0  // LED1 Source
#define PHY_MR23_LED1_LINK      0x00000000  // Link OK
#define PHY_MR23_LED1_RXTX      0x00000010  // RX or TX Activity (Default LED1)
#define PHY_MR23_LED1_100       0x00000050  // 100BASE-TX mode
#define PHY_MR23_LED1_10        0x00000060  // 10BASE-T mode
#define PHY_MR23_LED1_DUPLEX    0x00000070  // Full-Duplex
#define PHY_MR23_LED1_LINKACT   0x00000080  // Link OK & Blink=RX or TX
                                            // Activity
#define PHY_MR23_LED0_M         0x0000000F  // LED0 Source
#define PHY_MR23_LED0_LINK      0x00000000  // Link OK (Default LED0)
#define PHY_MR23_LED0_RXTX      0x00000001  // RX or TX Activity
#define PHY_MR23_LED0_100       0x00000005  // 100BASE-TX mode
#define PHY_MR23_LED0_10        0x00000006  // 10BASE-T mode
#define PHY_MR23_LED0_DUPLEX    0x00000007  // Full-Duplex
#define PHY_MR23_LED0_LINKACT   0x00000008  // Link OK & Blink=RX or TX
                                            // Activity

//*****************************************************************************
//
// The following are defines for the bit fields in the PHY_MR24 register.
//
//*****************************************************************************
#define PHY_MR24_PD_MODE        0x00000080  // Parallel Detection Mode
#define PHY_MR24_AUTO_SW        0x00000040  // Auto-Switching Enable
#define PHY_MR24_MDIX           0x00000020  // Auto-Switching Configuration
#define PHY_MR24_MDIX_CM        0x00000010  // Auto-Switching Complete
#define PHY_MR24_MDIX_SD_M      0x0000000F  // Auto-Switching Seed
#define PHY_MR24_MDIX_SD_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_RTCC register.
//
//*****************************************************************************
#define HIB_RTCC_M              0xFFFFFFFF  // RTC Counter
#define HIB_RTCC_S              0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_RTCM0 register.
//
//*****************************************************************************
#define HIB_RTCM0_M             0xFFFFFFFF  // RTC Match 0
#define HIB_RTCM0_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_RTCM1 register.
//
//*****************************************************************************
#define HIB_RTCM1_M             0xFFFFFFFF  // RTC Match 1
#define HIB_RTCM1_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_RTCLD register.
//
//*****************************************************************************
#define HIB_RTCLD_M             0xFFFFFFFF  // RTC Load
#define HIB_RTCLD_S             0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_CTL register.
//
//*****************************************************************************
#define HIB_CTL_VABORT          0x00000080  // Power Cut Abort Enable
#define HIB_CTL_CLK32EN         0x00000040  // Clocking Enable
#define HIB_CTL_LOWBATEN        0x00000020  // Low Battery Monitoring Enable
#define HIB_CTL_PINWEN          0x00000010  // External WAKE Pin Enable
#define HIB_CTL_RTCWEN          0x00000008  // RTC Wake-up Enable
#define HIB_CTL_CLKSEL          0x00000004  // Hibernation Module Clock Select
#define HIB_CTL_HIBREQ          0x00000002  // Hibernation Request
#define HIB_CTL_RTCEN           0x00000001  // RTC Timer Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_IM register.
//
//*****************************************************************************
#define HIB_IM_EXTW             0x00000008  // External Wake-Up Interrupt Mask
#define HIB_IM_LOWBAT           0x00000004  // Low Battery Voltage Interrupt
                                            // Mask
#define HIB_IM_RTCALT1          0x00000002  // RTC Alert 1 Interrupt Mask
#define HIB_IM_RTCALT0          0x00000001  // RTC Alert 0 Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_RIS register.
//
//*****************************************************************************
#define HIB_RIS_EXTW            0x00000008  // External Wake-Up Raw Interrupt
                                            // Status
#define HIB_RIS_LOWBAT          0x00000004  // Low Battery Voltage Raw
                                            // Interrupt Status
#define HIB_RIS_RTCALT1         0x00000002  // RTC Alert 1 Raw Interrupt Status
#define HIB_RIS_RTCALT0         0x00000001  // RTC Alert 0 Raw Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_MIS register.
//
//*****************************************************************************
#define HIB_MIS_EXTW            0x00000008  // External Wake-Up Masked
                                            // Interrupt Status
#define HIB_MIS_LOWBAT          0x00000004  // Low Battery Voltage Masked
                                            // Interrupt Status
#define HIB_MIS_RTCALT1         0x00000002  // RTC Alert 1 Masked Interrupt
                                            // Status
#define HIB_MIS_RTCALT0         0x00000001  // RTC Alert 0 Masked Interrupt
                                            // Status

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_IC register.
//
//*****************************************************************************
#define HIB_IC_EXTW             0x00000008  // External Wake-Up Masked
                                            // Interrupt Clear
#define HIB_IC_LOWBAT           0x00000004  // Low Battery Voltage Masked
                                            // Interrupt Clear
#define HIB_IC_RTCALT1          0x00000002  // RTC Alert1 Masked Interrupt
                                            // Clear
#define HIB_IC_RTCALT0          0x00000001  // RTC Alert0 Masked Interrupt
                                            // Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_RTCT register.
//
//*****************************************************************************
#define HIB_RTCT_TRIM_M         0x0000FFFF  // RTC Trim Value
#define HIB_RTCT_TRIM_S         0

//*****************************************************************************
//
// The following are defines for the bit fields in the HIB_DATA register.
//
//*****************************************************************************
#define HIB_DATA_RTD_M          0xFFFFFFFF  // Hibernation Module NV Data
#define HIB_DATA_RTD_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMA register.
//
//*****************************************************************************
#define FLASH_FMA_OFFSET_M      0x0003FFFF  // Address Offset
#define FLASH_FMA_OFFSET_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMD register.
//
//*****************************************************************************
#define FLASH_FMD_DATA_M        0xFFFFFFFF  // Data Value
#define FLASH_FMD_DATA_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FMC register.
//
//*****************************************************************************
#define FLASH_FMC_WRKEY         0xA4420000  // FLASH write key
#define FLASH_FMC_COMT          0x00000008  // Commit Register Value
#define FLASH_FMC_MERASE        0x00000004  // Mass Erase Flash Memory
#define FLASH_FMC_ERASE         0x00000002  // Erase a Page of Flash Memory
#define FLASH_FMC_WRITE         0x00000001  // Write a Word into Flash Memory

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FCRIS register.
//
//*****************************************************************************
#define FLASH_FCRIS_PRIS        0x00000002  // Programming Raw Interrupt Status
#define FLASH_FCRIS_ARIS        0x00000001  // Access Raw Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FCIM register.
//
//*****************************************************************************
#define FLASH_FCIM_PMASK        0x00000002  // Programming Interrupt Mask
#define FLASH_FCIM_AMASK        0x00000001  // Access Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_FCMISC register.
//
//*****************************************************************************
#define FLASH_FCMISC_PMISC      0x00000002  // Programming Masked Interrupt
                                            // Status and Clear
#define FLASH_FCMISC_AMISC      0x00000001  // Access Masked Interrupt Status
                                            // and Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_USECRL register.
//
//*****************************************************************************
#define FLASH_USECRL_M          0x000000FF  // Microsecond Reload Value
#define FLASH_USECRL_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_USERDBG register.
//
//*****************************************************************************
#define FLASH_USERDBG_NW        0x80000000  // User Debug Not Written
#define FLASH_USERDBG_DATA_M    0x7FFFFFFC  // User Data
#define FLASH_USERDBG_DBG1      0x00000002  // Debug Control 1
#define FLASH_USERDBG_DBG0      0x00000001  // Debug Control 0
#define FLASH_USERDBG_DATA_S    2

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_USERREG0 register.
//
//*****************************************************************************
#define FLASH_USERREG0_NW       0x80000000  // Not Written
#define FLASH_USERREG0_DATA_M   0x7FFFFFFF  // User Data
#define FLASH_USERREG0_DATA_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the FLASH_USERREG1 register.
//
//*****************************************************************************
#define FLASH_USERREG1_NW       0x80000000  // Not Written
#define FLASH_USERREG1_DATA_M   0x7FFFFFFF  // User Data
#define FLASH_USERREG1_DATA_S   0

//*****************************************************************************
//
// The following are defines for the erase size of the FLASH block that is
// erased by an erase operation, and the protect size is the size of the FLASH
// block that is protected by each protection register.
//
//*****************************************************************************
#define FLASH_PROTECT_SIZE      0x00000800
#define FLASH_ERASE_SIZE        0x00000400

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DID0 register.
//
//*****************************************************************************
#define SYSCTL_DID0_VER_M       0x70000000  // DID0 Version
#define SYSCTL_DID0_VER_1       0x10000000  // Second version of the DID0
                                            // register format
#define SYSCTL_DID0_CLASS_M     0x00FF0000  // Device Class
#define SYSCTL_DID0_CLASS_FURY  0x00010000  // Stellaris(R) Fury-class devices
#define SYSCTL_DID0_MAJ_M       0x0000FF00  // Major Revision
#define SYSCTL_DID0_MAJ_REVA    0x00000000  // Revision A (initial device)
#define SYSCTL_DID0_MAJ_REVB    0x00000100  // Revision B (first base layer
                                            // revision)
#define SYSCTL_DID0_MAJ_REVC    0x00000200  // Revision C (second base layer
                                            // revision)
#define SYSCTL_DID0_MIN_M       0x000000FF  // Minor Revision
#define SYSCTL_DID0_MIN_0       0x00000000  // Initial device, or a major
                                            // revision update
#define SYSCTL_DID0_MIN_1       0x00000001  // First metal layer change
#define SYSCTL_DID0_MIN_2       0x00000002  // Second metal layer change

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DID1 register.
//
//*****************************************************************************
#define SYSCTL_DID1_VER_M       0xF0000000  // DID1 Version
#define SYSCTL_DID1_VER_1       0x10000000  // Second version of the DID1
                                            // register format
#define SYSCTL_DID1_FAM_M       0x0F000000  // Family
#define SYSCTL_DID1_FAM_STELLARIS \
                                0x00000000  // Stellaris family of
                                            // microcontollers, that is, all
                                            // devices with external part
                                            // numbers starting with LM3S
#define SYSCTL_DID1_PRTNO_M     0x00FF0000  // Part Number
#define SYSCTL_DID1_PRTNO_8962  0x00A60000  // LM3S8962
#define SYSCTL_DID1_PINCNT_M    0x0000E000  // Package Pin Count
#define SYSCTL_DID1_PINCNT_100  0x00004000  // 100-pin package
#define SYSCTL_DID1_TEMP_M      0x000000E0  // Temperature Range
#define SYSCTL_DID1_TEMP_C      0x00000000  // Commercial temperature range (0C
                                            // to 70C)
#define SYSCTL_DID1_TEMP_I      0x00000020  // Industrial temperature range
                                            // (-40C to 85C)
#define SYSCTL_DID1_TEMP_E      0x00000040  // Extended temperature range (-40C
                                            // to 105C)
#define SYSCTL_DID1_PKG_M       0x00000018  // Package Type
#define SYSCTL_DID1_PKG_SOIC    0x00000000  // SOIC package
#define SYSCTL_DID1_PKG_QFP     0x00000008  // LQFP package
#define SYSCTL_DID1_PKG_BGA     0x00000010  // BGA package
#define SYSCTL_DID1_ROHS        0x00000004  // RoHS-Compliance
#define SYSCTL_DID1_QUAL_M      0x00000003  // Qualification Status
#define SYSCTL_DID1_QUAL_ES     0x00000000  // Engineering Sample (unqualified)
#define SYSCTL_DID1_QUAL_PP     0x00000001  // Pilot Production (unqualified)
#define SYSCTL_DID1_QUAL_FQ     0x00000002  // Fully Qualified

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DC0 register.
//
//*****************************************************************************
#define SYSCTL_DC0_SRAMSZ_M     0xFFFF0000  // SRAM Size
#define SYSCTL_DC0_SRAMSZ_64KB  0x00FF0000  // 64 KB of SRAM
#define SYSCTL_DC0_FLASHSZ_M    0x0000FFFF  // Flash Size
#define SYSCTL_DC0_FLASHSZ_256K 0x0000007F  // 256 KB of Flash
#define SYSCTL_DC0_SRAMSZ_S     16          // SRAM size shift
#define SYSCTL_DC0_FLASHSZ_S    0           // Flash size shift

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DC1 register.
//
//*****************************************************************************
#define SYSCTL_DC1_CAN0         0x01000000  // CAN Module 0 Present
#define SYSCTL_DC1_PWM          0x00100000  // PWM Module Present
#define SYSCTL_DC1_ADC          0x00010000  // ADC Module Present
#define SYSCTL_DC1_MINSYSDIV_M  0x0000F000  // System Clock Divider
#define SYSCTL_DC1_MINSYSDIV_50 0x00003000  // Specifies a 50-MHz CPU clock
                                            // with a PLL divider of 4
#define SYSCTL_DC1_ADCSPD_M     0x00000300  // Max ADC Speed
#define SYSCTL_DC1_ADCSPD_500K  0x00000200  // 500K samples/second
#define SYSCTL_DC1_MPU          0x00000080  // MPU Present
#define SYSCTL_DC1_HIB          0x00000040  // Hibernation Module Present
#define SYSCTL_DC1_TEMP         0x00000020  // Temp Sensor Present
#define SYSCTL_DC1_PLL          0x00000010  // PLL Present
#define SYSCTL_DC1_WDT          0x00000008  // Watchdog Timer Present
#define SYSCTL_DC1_SWO          0x00000004  // SWO Trace Port Present
#define SYSCTL_DC1_SWD          0x00000002  // SWD Present
#define SYSCTL_DC1_JTAG         0x00000001  // JTAG Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DC2 register.
//
//*****************************************************************************
#define SYSCTL_DC2_COMP0        0x01000000  // Analog Comparator 0 Present
#define SYSCTL_DC2_TIMER3       0x00080000  // Timer Module 3 Present
#define SYSCTL_DC2_TIMER2       0x00040000  // Timer Module 2 Present
#define SYSCTL_DC2_TIMER1       0x00020000  // Timer Module 1 Present
#define SYSCTL_DC2_TIMER0       0x00010000  // Timer Module 0 Present
#define SYSCTL_DC2_I2C0         0x00001000  // I2C Module 0 Present
#define SYSCTL_DC2_QEI1         0x00000200  // QEI Module 1 Present
#define SYSCTL_DC2_QEI0         0x00000100  // QEI Module 0 Present
#define SYSCTL_DC2_SSI0         0x00000010  // SSI Module 0 Present
#define SYSCTL_DC2_UART1        0x00000002  // UART Module 1 Present
#define SYSCTL_DC2_UART0        0x00000001  // UART Module 0 Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DC3 register.
//
//*****************************************************************************
#define SYSCTL_DC3_32KHZ        0x80000000  // 32KHz Input Clock Available
#define SYSCTL_DC3_CCP1         0x02000000  // CCP1 Pin Present
#define SYSCTL_DC3_CCP0         0x01000000  // CCP0 Pin Present
#define SYSCTL_DC3_ADC3         0x00080000  // ADC3 Pin Present
#define SYSCTL_DC3_ADC2         0x00040000  // ADC2 Pin Present
#define SYSCTL_DC3_ADC1         0x00020000  // ADC1 Pin Present
#define SYSCTL_DC3_ADC0         0x00010000  // ADC0 Pin Present
#define SYSCTL_DC3_PWMFAULT     0x00008000  // PWM Fault Pin Present
#define SYSCTL_DC3_C0O          0x00000100  // C0o Pin Present
#define SYSCTL_DC3_C0PLUS       0x00000080  // C0+ Pin Present
#define SYSCTL_DC3_C0MINUS      0x00000040  // C0- Pin Present
#define SYSCTL_DC3_PWM5         0x00000020  // PWM5 Pin Present
#define SYSCTL_DC3_PWM4         0x00000010  // PWM4 Pin Present
#define SYSCTL_DC3_PWM3         0x00000008  // PWM3 Pin Present
#define SYSCTL_DC3_PWM2         0x00000004  // PWM2 Pin Present
#define SYSCTL_DC3_PWM1         0x00000002  // PWM1 Pin Present
#define SYSCTL_DC3_PWM0         0x00000001  // PWM0 Pin Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DC4 register.
//
//*****************************************************************************
#define SYSCTL_DC4_EPHY0        0x40000000  // Ethernet PHY Layer 0 Present
#define SYSCTL_DC4_EMAC0        0x10000000  // Ethernet MAC Layer 0 Present
#define SYSCTL_DC4_E1588        0x01000000  // 1588 Capable
#define SYSCTL_DC4_GPIOG        0x00000040  // GPIO Port G Present
#define SYSCTL_DC4_GPIOF        0x00000020  // GPIO Port F Present
#define SYSCTL_DC4_GPIOE        0x00000010  // GPIO Port E Present
#define SYSCTL_DC4_GPIOD        0x00000008  // GPIO Port D Present
#define SYSCTL_DC4_GPIOC        0x00000004  // GPIO Port C Present
#define SYSCTL_DC4_GPIOB        0x00000002  // GPIO Port B Present
#define SYSCTL_DC4_GPIOA        0x00000001  // GPIO Port A Present

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PBORCTL register.
//
//*****************************************************************************
#define SYSCTL_PBORCTL_BORIOR   0x00000002  // BOR Interrupt or Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_LDOPCTL register.
//
//*****************************************************************************
#define SYSCTL_LDOPCTL_M        0x0000003F  // LDO Output Voltage
#define SYSCTL_LDOPCTL_2_50V    0x00000000  // 2.50
#define SYSCTL_LDOPCTL_2_45V    0x00000001  // 2.45
#define SYSCTL_LDOPCTL_2_40V    0x00000002  // 2.40
#define SYSCTL_LDOPCTL_2_35V    0x00000003  // 2.35
#define SYSCTL_LDOPCTL_2_30V    0x00000004  // 2.30
#define SYSCTL_LDOPCTL_2_25V    0x00000005  // 2.25
#define SYSCTL_LDOPCTL_2_75V    0x0000001B  // 2.75
#define SYSCTL_LDOPCTL_2_70V    0x0000001C  // 2.70
#define SYSCTL_LDOPCTL_2_65V    0x0000001D  // 2.65
#define SYSCTL_LDOPCTL_2_60V    0x0000001E  // 2.60
#define SYSCTL_LDOPCTL_2_55V    0x0000001F  // 2.55

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRCR0 register.
//
//*****************************************************************************
#define SYSCTL_SRCR0_CAN0       0x01000000  // CAN0 Reset Control
#define SYSCTL_SRCR0_PWM        0x00100000  // PWM Reset Control
#define SYSCTL_SRCR0_ADC        0x00010000  // ADC0 Reset Control
#define SYSCTL_SRCR0_HIB        0x00000040  // HIB Reset Control
#define SYSCTL_SRCR0_WDT        0x00000008  // WDT Reset Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRCR1 register.
//
//*****************************************************************************
#define SYSCTL_SRCR1_COMP0      0x01000000  // Analog Comp 0 Reset Control
#define SYSCTL_SRCR1_TIMER3     0x00080000  // Timer 3 Reset Control
#define SYSCTL_SRCR1_TIMER2     0x00040000  // Timer 2 Reset Control
#define SYSCTL_SRCR1_TIMER1     0x00020000  // Timer 1 Reset Control
#define SYSCTL_SRCR1_TIMER0     0x00010000  // Timer 0 Reset Control
#define SYSCTL_SRCR1_I2C0       0x00001000  // I2C0 Reset Control
#define SYSCTL_SRCR1_QEI1       0x00000200  // QEI1 Reset Control
#define SYSCTL_SRCR1_QEI0       0x00000100  // QEI0 Reset Control
#define SYSCTL_SRCR1_SSI0       0x00000010  // SSI0 Reset Control
#define SYSCTL_SRCR1_UART1      0x00000002  // UART1 Reset Control
#define SYSCTL_SRCR1_UART0      0x00000001  // UART0 Reset Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SRCR2 register.
//
//*****************************************************************************
#define SYSCTL_SRCR2_EPHY0      0x40000000  // PHY0 Reset Control
#define SYSCTL_SRCR2_EMAC0      0x10000000  // MAC0 Reset Control
#define SYSCTL_SRCR2_GPIOG      0x00000040  // Port G Reset Control
#define SYSCTL_SRCR2_GPIOF      0x00000020  // Port F Reset Control
#define SYSCTL_SRCR2_GPIOE      0x00000010  // Port E Reset Control
#define SYSCTL_SRCR2_GPIOD      0x00000008  // Port D Reset Control
#define SYSCTL_SRCR2_GPIOC      0x00000004  // Port C Reset Control
#define SYSCTL_SRCR2_GPIOB      0x00000002  // Port B Reset Control
#define SYSCTL_SRCR2_GPIOA      0x00000001  // Port A Reset Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RIS register.
//
//*****************************************************************************
#define SYSCTL_RIS_PLLLRIS      0x00000040  // PLL Lock Raw Interrupt Status
#define SYSCTL_RIS_BORRIS       0x00000002  // Brown-Out Reset Raw Interrupt
                                            // Status

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_IMC register.
//
//*****************************************************************************
#define SYSCTL_IMC_PLLLIM       0x00000040  // PLL Lock Interrupt Mask
#define SYSCTL_IMC_BORIM        0x00000002  // Brown-Out Reset Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_MISC register.
//
//*****************************************************************************
#define SYSCTL_MISC_PLLLMIS     0x00000040  // PLL Lock Masked Interrupt Status
#define SYSCTL_MISC_BORMIS      0x00000002  // BOR Masked Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RESC register.
//
//*****************************************************************************
#define SYSCTL_RESC_SW          0x00000010  // Software Reset
#define SYSCTL_RESC_WDT         0x00000008  // Watchdog Timer Reset
#define SYSCTL_RESC_BOR         0x00000004  // Brown-Out Reset
#define SYSCTL_RESC_POR         0x00000002  // Power-On Reset
#define SYSCTL_RESC_EXT         0x00000001  // External Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCC register.
//
//*****************************************************************************
#define SYSCTL_RCC_ACG          0x08000000  // Auto Clock Gating
#define SYSCTL_RCC_SYSDIV_M     0x07800000  // System Clock Divisor
#define SYSCTL_RCC_SYSDIV_2     0x00800000  // System clock /2
#define SYSCTL_RCC_SYSDIV_3     0x01000000  // System clock /3
#define SYSCTL_RCC_SYSDIV_4     0x01800000  // System clock /4
#define SYSCTL_RCC_SYSDIV_5     0x02000000  // System clock /5
#define SYSCTL_RCC_SYSDIV_6     0x02800000  // System clock /6
#define SYSCTL_RCC_SYSDIV_7     0x03000000  // System clock /7
#define SYSCTL_RCC_SYSDIV_8     0x03800000  // System clock /8
#define SYSCTL_RCC_SYSDIV_9     0x04000000  // System clock /9
#define SYSCTL_RCC_SYSDIV_10    0x04800000  // System clock /10
#define SYSCTL_RCC_SYSDIV_11    0x05000000  // System clock /11
#define SYSCTL_RCC_SYSDIV_12    0x05800000  // System clock /12
#define SYSCTL_RCC_SYSDIV_13    0x06000000  // System clock /13
#define SYSCTL_RCC_SYSDIV_14    0x06800000  // System clock /14
#define SYSCTL_RCC_SYSDIV_15    0x07000000  // System clock /15
#define SYSCTL_RCC_SYSDIV_16    0x07800000  // System clock /16
#define SYSCTL_RCC_USESYSDIV    0x00400000  // Enable System Clock Divider
#define SYSCTL_RCC_USEPWMDIV    0x00100000  // Enable PWM Clock Divisor
#define SYSCTL_RCC_PWMDIV_M     0x000E0000  // PWM Unit Clock Divisor
#define SYSCTL_RCC_PWMDIV_2     0x00000000  // PWM clock /2
#define SYSCTL_RCC_PWMDIV_4     0x00020000  // PWM clock /4
#define SYSCTL_RCC_PWMDIV_8     0x00040000  // PWM clock /8
#define SYSCTL_RCC_PWMDIV_16    0x00060000  // PWM clock /16
#define SYSCTL_RCC_PWMDIV_32    0x00080000  // PWM clock /32
#define SYSCTL_RCC_PWMDIV_64    0x000A0000  // PWM clock /64
#define SYSCTL_RCC_PWRDN        0x00002000  // PLL Power Down
#define SYSCTL_RCC_BYPASS       0x00000800  // PLL Bypass
#define SYSCTL_RCC_XTAL_M       0x000003C0  // Crystal Value
#define SYSCTL_RCC_XTAL_1MHZ    0x00000000  // 1 MHz
#define SYSCTL_RCC_XTAL_1_84MHZ 0x00000040  // 1.8432 MHz
#define SYSCTL_RCC_XTAL_2MHZ    0x00000080  // 2 MHz
#define SYSCTL_RCC_XTAL_2_45MHZ 0x000000C0  // 2.4576 MHz
#define SYSCTL_RCC_XTAL_3_57MHZ 0x00000100  // 3.579545 MHz
#define SYSCTL_RCC_XTAL_3_68MHZ 0x00000140  // 3.6864 MHz
#define SYSCTL_RCC_XTAL_4MHZ    0x00000180  // 4 MHz
#define SYSCTL_RCC_XTAL_4_09MHZ 0x000001C0  // 4.096 MHz
#define SYSCTL_RCC_XTAL_4_91MHZ 0x00000200  // 4.9152 MHz
#define SYSCTL_RCC_XTAL_5MHZ    0x00000240  // 5 MHz
#define SYSCTL_RCC_XTAL_5_12MHZ 0x00000280  // 5.12 MHz
#define SYSCTL_RCC_XTAL_6MHZ    0x000002C0  // 6 MHz
#define SYSCTL_RCC_XTAL_6_14MHZ 0x00000300  // 6.144 MHz
#define SYSCTL_RCC_XTAL_7_37MHZ 0x00000340  // 7.3728 MHz
#define SYSCTL_RCC_XTAL_8MHZ    0x00000380  // 8 MHz
#define SYSCTL_RCC_XTAL_8_19MHZ 0x000003C0  // 8.192 MHz
#define SYSCTL_RCC_OSCSRC_M     0x00000030  // Oscillator Source
#define SYSCTL_RCC_OSCSRC_MAIN  0x00000000  // MOSC
#define SYSCTL_RCC_OSCSRC_INT   0x00000010  // IOSC
#define SYSCTL_RCC_OSCSRC_INT4  0x00000020  // IOSC/4
#define SYSCTL_RCC_OSCSRC_30    0x00000030  // 30 kHz
#define SYSCTL_RCC_IOSCDIS      0x00000002  // Internal Oscillator Disable
#define SYSCTL_RCC_MOSCDIS      0x00000001  // Main Oscillator Disable
#define SYSCTL_RCC_SYSDIV_S     23

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_PLLCFG register.
//
//*****************************************************************************
#define SYSCTL_PLLCFG_F_M       0x00003FE0  // PLL F Value
#define SYSCTL_PLLCFG_R_M       0x0000001F  // PLL R Value
#define SYSCTL_PLLCFG_F_S       5
#define SYSCTL_PLLCFG_R_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCC2 register.
//
//*****************************************************************************
#define SYSCTL_RCC2_USERCC2     0x80000000  // Use RCC2
#define SYSCTL_RCC2_SYSDIV2_M   0x1F800000  // System Clock Divisor 2
#define SYSCTL_RCC2_SYSDIV2_2   0x00800000  // System clock /2
#define SYSCTL_RCC2_SYSDIV2_3   0x01000000  // System clock /3
#define SYSCTL_RCC2_SYSDIV2_4   0x01800000  // System clock /4
#define SYSCTL_RCC2_SYSDIV2_5   0x02000000  // System clock /5
#define SYSCTL_RCC2_SYSDIV2_6   0x02800000  // System clock /6
#define SYSCTL_RCC2_SYSDIV2_7   0x03000000  // System clock /7
#define SYSCTL_RCC2_SYSDIV2_8   0x03800000  // System clock /8
#define SYSCTL_RCC2_SYSDIV2_9   0x04000000  // System clock /9
#define SYSCTL_RCC2_SYSDIV2_10  0x04800000  // System clock /10
#define SYSCTL_RCC2_SYSDIV2_11  0x05000000  // System clock /11
#define SYSCTL_RCC2_SYSDIV2_12  0x05800000  // System clock /12
#define SYSCTL_RCC2_SYSDIV2_13  0x06000000  // System clock /13
#define SYSCTL_RCC2_SYSDIV2_14  0x06800000  // System clock /14
#define SYSCTL_RCC2_SYSDIV2_15  0x07000000  // System clock /15
#define SYSCTL_RCC2_SYSDIV2_16  0x07800000  // System clock /16
#define SYSCTL_RCC2_SYSDIV2_17  0x08000000  // System clock /17
#define SYSCTL_RCC2_SYSDIV2_18  0x08800000  // System clock /18
#define SYSCTL_RCC2_SYSDIV2_19  0x09000000  // System clock /19
#define SYSCTL_RCC2_SYSDIV2_20  0x09800000  // System clock /20
#define SYSCTL_RCC2_SYSDIV2_21  0x0A000000  // System clock /21
#define SYSCTL_RCC2_SYSDIV2_22  0x0A800000  // System clock /22
#define SYSCTL_RCC2_SYSDIV2_23  0x0B000000  // System clock /23
#define SYSCTL_RCC2_SYSDIV2_24  0x0B800000  // System clock /24
#define SYSCTL_RCC2_SYSDIV2_25  0x0C000000  // System clock /25
#define SYSCTL_RCC2_SYSDIV2_26  0x0C800000  // System clock /26
#define SYSCTL_RCC2_SYSDIV2_27  0x0D000000  // System clock /27
#define SYSCTL_RCC2_SYSDIV2_28  0x0D800000  // System clock /28
#define SYSCTL_RCC2_SYSDIV2_29  0x0E000000  // System clock /29
#define SYSCTL_RCC2_SYSDIV2_30  0x0E800000  // System clock /30
#define SYSCTL_RCC2_SYSDIV2_31  0x0F000000  // System clock /31
#define SYSCTL_RCC2_SYSDIV2_32  0x0F800000  // System clock /32
#define SYSCTL_RCC2_SYSDIV2_33  0x10000000  // System clock /33
#define SYSCTL_RCC2_SYSDIV2_34  0x10800000  // System clock /34
#define SYSCTL_RCC2_SYSDIV2_35  0x11000000  // System clock /35
#define SYSCTL_RCC2_SYSDIV2_36  0x11800000  // System clock /36
#define SYSCTL_RCC2_SYSDIV2_37  0x12000000  // System clock /37
#define SYSCTL_RCC2_SYSDIV2_38  0x12800000  // System clock /38
#define SYSCTL_RCC2_SYSDIV2_39  0x13000000  // System clock /39
#define SYSCTL_RCC2_SYSDIV2_40  0x13800000  // System clock /40
#define SYSCTL_RCC2_SYSDIV2_41  0x14000000  // System clock /41
#define SYSCTL_RCC2_SYSDIV2_42  0x14800000  // System clock /42
#define SYSCTL_RCC2_SYSDIV2_43  0x15000000  // System clock /43
#define SYSCTL_RCC2_SYSDIV2_44  0x15800000  // System clock /44
#define SYSCTL_RCC2_SYSDIV2_45  0x16000000  // System clock /45
#define SYSCTL_RCC2_SYSDIV2_46  0x16800000  // System clock /46
#define SYSCTL_RCC2_SYSDIV2_47  0x17000000  // System clock /47
#define SYSCTL_RCC2_SYSDIV2_48  0x17800000  // System clock /48
#define SYSCTL_RCC2_SYSDIV2_49  0x18000000  // System clock /49
#define SYSCTL_RCC2_SYSDIV2_50  0x18800000  // System clock /50
#define SYSCTL_RCC2_SYSDIV2_51  0x19000000  // System clock /51
#define SYSCTL_RCC2_SYSDIV2_52  0x19800000  // System clock /52
#define SYSCTL_RCC2_SYSDIV2_53  0x1A000000  // System clock /53
#define SYSCTL_RCC2_SYSDIV2_54  0x1A800000  // System clock /54
#define SYSCTL_RCC2_SYSDIV2_55  0x1B000000  // System clock /55
#define SYSCTL_RCC2_SYSDIV2_56  0x1B800000  // System clock /56
#define SYSCTL_RCC2_SYSDIV2_57  0x1C000000  // System clock /57
#define SYSCTL_RCC2_SYSDIV2_58  0x1C800000  // System clock /58
#define SYSCTL_RCC2_SYSDIV2_59  0x1D000000  // System clock /59
#define SYSCTL_RCC2_SYSDIV2_60  0x1D800000  // System clock /60
#define SYSCTL_RCC2_SYSDIV2_61  0x1E000000  // System clock /61
#define SYSCTL_RCC2_SYSDIV2_62  0x1E800000  // System clock /62
#define SYSCTL_RCC2_SYSDIV2_63  0x1F000000  // System clock /63
#define SYSCTL_RCC2_SYSDIV2_64  0x1F800000  // System clock /64
#define SYSCTL_RCC2_PWRDN2      0x00002000  // Power-Down PLL 2
#define SYSCTL_RCC2_BYPASS2     0x00000800  // PLL Bypass 2
#define SYSCTL_RCC2_OSCSRC2_M   0x00000070  // Oscillator Source 2
#define SYSCTL_RCC2_OSCSRC2_MO  0x00000000  // MOSC
#define SYSCTL_RCC2_OSCSRC2_IO  0x00000010  // PIOSC
#define SYSCTL_RCC2_OSCSRC2_IO4 0x00000020  // PIOSC/4
#define SYSCTL_RCC2_OSCSRC2_30  0x00000030  // 30 kHz
#define SYSCTL_RCC2_OSCSRC2_32  0x00000070  // 32.768 kHz
#define SYSCTL_RCC2_SYSDIV2_S   23

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGC0 register.
//
//*****************************************************************************
#define SYSCTL_RCGC0_CAN0       0x01000000  // CAN0 Clock Gating Control
#define SYSCTL_RCGC0_PWM        0x00100000  // PWM Clock Gating Control
#define SYSCTL_RCGC0_ADC        0x00010000  // ADC0 Clock Gating Control
#define SYSCTL_RCGC0_ADCSPD_M   0x00000300  // ADC Sample Speed
#define SYSCTL_RCGC0_ADCSPD125K 0x00000000  // 125K samples/second
#define SYSCTL_RCGC0_ADCSPD250K 0x00000100  // 250K samples/second
#define SYSCTL_RCGC0_ADCSPD500K 0x00000200  // 500K samples/second
#define SYSCTL_RCGC0_HIB        0x00000040  // HIB Clock Gating Control
#define SYSCTL_RCGC0_WDT        0x00000008  // WDT Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGC1 register.
//
//*****************************************************************************
#define SYSCTL_RCGC1_COMP0      0x01000000  // Analog Comparator 0 Clock Gating
#define SYSCTL_RCGC1_TIMER3     0x00080000  // Timer 3 Clock Gating Control
#define SYSCTL_RCGC1_TIMER2     0x00040000  // Timer 2 Clock Gating Control
#define SYSCTL_RCGC1_TIMER1     0x00020000  // Timer 1 Clock Gating Control
#define SYSCTL_RCGC1_TIMER0     0x00010000  // Timer 0 Clock Gating Control
#define SYSCTL_RCGC1_I2C0       0x00001000  // I2C0 Clock Gating Control
#define SYSCTL_RCGC1_QEI1       0x00000200  // QEI1 Clock Gating Control
#define SYSCTL_RCGC1_QEI0       0x00000100  // QEI0 Clock Gating Control
#define SYSCTL_RCGC1_SSI0       0x00000010  // SSI0 Clock Gating Control
#define SYSCTL_RCGC1_UART1      0x00000002  // UART1 Clock Gating Control
#define SYSCTL_RCGC1_UART0      0x00000001  // UART0 Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_RCGC2 register.
//
//*****************************************************************************
#define SYSCTL_RCGC2_EPHY0      0x40000000  // PHY0 Clock Gating Control
#define SYSCTL_RCGC2_EMAC0      0x10000000  // MAC0 Clock Gating Control
#define SYSCTL_RCGC2_GPIOG      0x00000040  // Port G Clock Gating Control
#define SYSCTL_RCGC2_GPIOF      0x00000020  // Port F Clock Gating Control
#define SYSCTL_RCGC2_GPIOE      0x00000010  // Port E Clock Gating Control
#define SYSCTL_RCGC2_GPIOD      0x00000008  // Port D Clock Gating Control
#define SYSCTL_RCGC2_GPIOC      0x00000004  // Port C Clock Gating Control
#define SYSCTL_RCGC2_GPIOB      0x00000002  // Port B Clock Gating Control
#define SYSCTL_RCGC2_GPIOA      0x00000001  // Port A Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGC0 register.
//
//*****************************************************************************
#define SYSCTL_SCGC0_CAN0       0x01000000  // CAN0 Clock Gating Control
#define SYSCTL_SCGC0_PWM        0x00100000  // PWM Clock Gating Control
#define SYSCTL_SCGC0_ADC        0x00010000  // ADC0 Clock Gating Control
#define SYSCTL_SCGC0_ADCSPD_M   0x00000300  // ADC Sample Speed
#define SYSCTL_SCGC0_ADCSPD125K 0x00000000  // 125K samples/second
#define SYSCTL_SCGC0_ADCSPD250K 0x00000100  // 250K samples/second
#define SYSCTL_SCGC0_ADCSPD500K 0x00000200  // 500K samples/second
#define SYSCTL_SCGC0_HIB        0x00000040  // HIB Clock Gating Control
#define SYSCTL_SCGC0_WDT        0x00000008  // WDT Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGC1 register.
//
//*****************************************************************************
#define SYSCTL_SCGC1_COMP0      0x01000000  // Analog Comparator 0 Clock Gating
#define SYSCTL_SCGC1_TIMER3     0x00080000  // Timer 3 Clock Gating Control
#define SYSCTL_SCGC1_TIMER2     0x00040000  // Timer 2 Clock Gating Control
#define SYSCTL_SCGC1_TIMER1     0x00020000  // Timer 1 Clock Gating Control
#define SYSCTL_SCGC1_TIMER0     0x00010000  // Timer 0 Clock Gating Control
#define SYSCTL_SCGC1_I2C0       0x00001000  // I2C0 Clock Gating Control
#define SYSCTL_SCGC1_QEI1       0x00000200  // QEI1 Clock Gating Control
#define SYSCTL_SCGC1_QEI0       0x00000100  // QEI0 Clock Gating Control
#define SYSCTL_SCGC1_SSI0       0x00000010  // SSI0 Clock Gating Control
#define SYSCTL_SCGC1_UART1      0x00000002  // UART1 Clock Gating Control
#define SYSCTL_SCGC1_UART0      0x00000001  // UART0 Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_SCGC2 register.
//
//*****************************************************************************
#define SYSCTL_SCGC2_EPHY0      0x40000000  // PHY0 Clock Gating Control
#define SYSCTL_SCGC2_EMAC0      0x10000000  // MAC0 Clock Gating Control
#define SYSCTL_SCGC2_GPIOG      0x00000040  // Port G Clock Gating Control
#define SYSCTL_SCGC2_GPIOF      0x00000020  // Port F Clock Gating Control
#define SYSCTL_SCGC2_GPIOE      0x00000010  // Port E Clock Gating Control
#define SYSCTL_SCGC2_GPIOD      0x00000008  // Port D Clock Gating Control
#define SYSCTL_SCGC2_GPIOC      0x00000004  // Port C Clock Gating Control
#define SYSCTL_SCGC2_GPIOB      0x00000002  // Port B Clock Gating Control
#define SYSCTL_SCGC2_GPIOA      0x00000001  // Port A Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGC0 register.
//
//*****************************************************************************
#define SYSCTL_DCGC0_CAN0       0x01000000  // CAN0 Clock Gating Control
#define SYSCTL_DCGC0_PWM        0x00100000  // PWM Clock Gating Control
#define SYSCTL_DCGC0_ADC        0x00010000  // ADC0 Clock Gating Control
#define SYSCTL_DCGC0_HIB        0x00000040  // HIB Clock Gating Control
#define SYSCTL_DCGC0_WDT        0x00000008  // WDT Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGC1 register.
//
//*****************************************************************************
#define SYSCTL_DCGC1_COMP0      0x01000000  // Analog Comparator 0 Clock Gating
#define SYSCTL_DCGC1_TIMER3     0x00080000  // Timer 3 Clock Gating Control
#define SYSCTL_DCGC1_TIMER2     0x00040000  // Timer 2 Clock Gating Control
#define SYSCTL_DCGC1_TIMER1     0x00020000  // Timer 1 Clock Gating Control
#define SYSCTL_DCGC1_TIMER0     0x00010000  // Timer 0 Clock Gating Control
#define SYSCTL_DCGC1_I2C0       0x00001000  // I2C0 Clock Gating Control
#define SYSCTL_DCGC1_QEI1       0x00000200  // QEI1 Clock Gating Control
#define SYSCTL_DCGC1_QEI0       0x00000100  // QEI0 Clock Gating Control
#define SYSCTL_DCGC1_SSI0       0x00000010  // SSI0 Clock Gating Control
#define SYSCTL_DCGC1_UART1      0x00000002  // UART1 Clock Gating Control
#define SYSCTL_DCGC1_UART0      0x00000001  // UART0 Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DCGC2 register.
//
//*****************************************************************************
#define SYSCTL_DCGC2_EPHY0      0x40000000  // PHY0 Clock Gating Control
#define SYSCTL_DCGC2_EMAC0      0x10000000  // MAC0 Clock Gating Control
#define SYSCTL_DCGC2_GPIOG      0x00000040  // Port G Clock Gating Control
#define SYSCTL_DCGC2_GPIOF      0x00000020  // Port F Clock Gating Control
#define SYSCTL_DCGC2_GPIOE      0x00000010  // Port E Clock Gating Control
#define SYSCTL_DCGC2_GPIOD      0x00000008  // Port D Clock Gating Control
#define SYSCTL_DCGC2_GPIOC      0x00000004  // Port C Clock Gating Control
#define SYSCTL_DCGC2_GPIOB      0x00000002  // Port B Clock Gating Control
#define SYSCTL_DCGC2_GPIOA      0x00000001  // Port A Clock Gating Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SYSCTL_DSLPCLKCFG
// register.
//
//*****************************************************************************
#define SYSCTL_DSLPCLKCFG_D_M   0x1F800000  // Divider Field Override
#define SYSCTL_DSLPCLKCFG_D_1   0x00000000  // System clock /1
#define SYSCTL_DSLPCLKCFG_D_2   0x00800000  // System clock /2
#define SYSCTL_DSLPCLKCFG_D_3   0x01000000  // System clock /3
#define SYSCTL_DSLPCLKCFG_D_4   0x01800000  // System clock /4
#define SYSCTL_DSLPCLKCFG_D_5   0x02000000  // System clock /5
#define SYSCTL_DSLPCLKCFG_D_6   0x02800000  // System clock /6
#define SYSCTL_DSLPCLKCFG_D_7   0x03000000  // System clock /7
#define SYSCTL_DSLPCLKCFG_D_8   0x03800000  // System clock /8
#define SYSCTL_DSLPCLKCFG_D_9   0x04000000  // System clock /9
#define SYSCTL_DSLPCLKCFG_D_10  0x04800000  // System clock /10
#define SYSCTL_DSLPCLKCFG_D_11  0x05000000  // System clock /11
#define SYSCTL_DSLPCLKCFG_D_12  0x05800000  // System clock /12
#define SYSCTL_DSLPCLKCFG_D_13  0x06000000  // System clock /13
#define SYSCTL_DSLPCLKCFG_D_14  0x06800000  // System clock /14
#define SYSCTL_DSLPCLKCFG_D_15  0x07000000  // System clock /15
#define SYSCTL_DSLPCLKCFG_D_16  0x07800000  // System clock /16
#define SYSCTL_DSLPCLKCFG_D_17  0x08000000  // System clock /17
#define SYSCTL_DSLPCLKCFG_D_18  0x08800000  // System clock /18
#define SYSCTL_DSLPCLKCFG_D_19  0x09000000  // System clock /19
#define SYSCTL_DSLPCLKCFG_D_20  0x09800000  // System clock /20
#define SYSCTL_DSLPCLKCFG_D_21  0x0A000000  // System clock /21
#define SYSCTL_DSLPCLKCFG_D_22  0x0A800000  // System clock /22
#define SYSCTL_DSLPCLKCFG_D_23  0x0B000000  // System clock /23
#define SYSCTL_DSLPCLKCFG_D_24  0x0B800000  // System clock /24
#define SYSCTL_DSLPCLKCFG_D_25  0x0C000000  // System clock /25
#define SYSCTL_DSLPCLKCFG_D_26  0x0C800000  // System clock /26
#define SYSCTL_DSLPCLKCFG_D_27  0x0D000000  // System clock /27
#define SYSCTL_DSLPCLKCFG_D_28  0x0D800000  // System clock /28
#define SYSCTL_DSLPCLKCFG_D_29  0x0E000000  // System clock /29
#define SYSCTL_DSLPCLKCFG_D_30  0x0E800000  // System clock /30
#define SYSCTL_DSLPCLKCFG_D_31  0x0F000000  // System clock /31
#define SYSCTL_DSLPCLKCFG_D_32  0x0F800000  // System clock /32
#define SYSCTL_DSLPCLKCFG_D_33  0x10000000  // System clock /33
#define SYSCTL_DSLPCLKCFG_D_34  0x10800000  // System clock /34
#define SYSCTL_DSLPCLKCFG_D_35  0x11000000  // System clock /35
#define SYSCTL_DSLPCLKCFG_D_36  0x11800000  // System clock /36
#define SYSCTL_DSLPCLKCFG_D_37  0x12000000  // System clock /37
#define SYSCTL_DSLPCLKCFG_D_38  0x12800000  // System clock /38
#define SYSCTL_DSLPCLKCFG_D_39  0x13000000  // System clock /39
#define SYSCTL_DSLPCLKCFG_D_40  0x13800000  // System clock /40
#define SYSCTL_DSLPCLKCFG_D_41  0x14000000  // System clock /41
#define SYSCTL_DSLPCLKCFG_D_42  0x14800000  // System clock /42
#define SYSCTL_DSLPCLKCFG_D_43  0x15000000  // System clock /43
#define SYSCTL_DSLPCLKCFG_D_44  0x15800000  // System clock /44
#define SYSCTL_DSLPCLKCFG_D_45  0x16000000  // System clock /45
#define SYSCTL_DSLPCLKCFG_D_46  0x16800000  // System clock /46
#define SYSCTL_DSLPCLKCFG_D_47  0x17000000  // System clock /47
#define SYSCTL_DSLPCLKCFG_D_48  0x17800000  // System clock /48
#define SYSCTL_DSLPCLKCFG_D_49  0x18000000  // System clock /49
#define SYSCTL_DSLPCLKCFG_D_50  0x18800000  // System clock /50
#define SYSCTL_DSLPCLKCFG_D_51  0x19000000  // System clock /51
#define SYSCTL_DSLPCLKCFG_D_52  0x19800000  // System clock /52
#define SYSCTL_DSLPCLKCFG_D_53  0x1A000000  // System clock /53
#define SYSCTL_DSLPCLKCFG_D_54  0x1A800000  // System clock /54
#define SYSCTL_DSLPCLKCFG_D_55  0x1B000000  // System clock /55
#define SYSCTL_DSLPCLKCFG_D_56  0x1B800000  // System clock /56
#define SYSCTL_DSLPCLKCFG_D_57  0x1C000000  // System clock /57
#define SYSCTL_DSLPCLKCFG_D_58  0x1C800000  // System clock /58
#define SYSCTL_DSLPCLKCFG_D_59  0x1D000000  // System clock /59
#define SYSCTL_DSLPCLKCFG_D_60  0x1D800000  // System clock /60
#define SYSCTL_DSLPCLKCFG_D_61  0x1E000000  // System clock /61
#define SYSCTL_DSLPCLKCFG_D_62  0x1E800000  // System clock /62
#define SYSCTL_DSLPCLKCFG_D_63  0x1F000000  // System clock /63
#define SYSCTL_DSLPCLKCFG_D_64  0x1F800000  // System clock /64
#define SYSCTL_DSLPCLKCFG_O_M   0x00000070  // Clock Source
#define SYSCTL_DSLPCLKCFG_O_IGN 0x00000000  // MOSC
#define SYSCTL_DSLPCLKCFG_O_IO  0x00000010  // PIOSC
#define SYSCTL_DSLPCLKCFG_O_30  0x00000030  // 30 kHz
#define SYSCTL_DSLPCLKCFG_O_32  0x00000070  // 32.768 kHz
#define SYSCTL_DSLPCLKCFG_D_S   23

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_INT_TYPE register.
//
//*****************************************************************************
#define NVIC_INT_TYPE_LINES_M   0x0000001F  // Number of interrupt lines (x32)
#define NVIC_INT_TYPE_LINES_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_ST_CTRL register.
//
//*****************************************************************************
#define NVIC_ST_CTRL_COUNT      0x00010000  // Count flag
#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt enable
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Counter mode

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_ST_RELOAD register.
//
//*****************************************************************************
#define NVIC_ST_RELOAD_M        0x00FFFFFF  // Counter load value
#define NVIC_ST_RELOAD_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_ST_CURRENT
// register.
//
//*****************************************************************************
#define NVIC_ST_CURRENT_M       0x00FFFFFF  // Counter current value
#define NVIC_ST_CURRENT_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_ST_CAL register.
//
//*****************************************************************************
#define NVIC_ST_CAL_NOREF       0x80000000  // No reference clock
#define NVIC_ST_CAL_SKEW        0x40000000  // Clock skew
#define NVIC_ST_CAL_ONEMS_M     0x00FFFFFF  // 1ms reference value
#define NVIC_ST_CAL_ONEMS_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_EN0 register.
//
//*****************************************************************************
#define NVIC_EN0_INT31          0x80000000  // Interrupt 31 enable
#define NVIC_EN0_INT30          0x40000000  // Interrupt 30 enable
#define NVIC_EN0_INT29          0x20000000  // Interrupt 29 enable
#define NVIC_EN0_INT28          0x10000000  // Interrupt 28 enable
#define NVIC_EN0_INT27          0x08000000  // Interrupt 27 enable
#define NVIC_EN0_INT26          0x04000000  // Interrupt 26 enable
#define NVIC_EN0_INT25          0x02000000  // Interrupt 25 enable
#define NVIC_EN0_INT24          0x01000000  // Interrupt 24 enable
#define NVIC_EN0_INT23          0x00800000  // Interrupt 23 enable
#define NVIC_EN0_INT22          0x00400000  // Interrupt 22 enable
#define NVIC_EN0_INT21          0x00200000  // Interrupt 21 enable
#define NVIC_EN0_INT20          0x00100000  // Interrupt 20 enable
#define NVIC_EN0_INT19          0x00080000  // Interrupt 19 enable
#define NVIC_EN0_INT18          0x00040000  // Interrupt 18 enable
#define NVIC_EN0_INT17          0x00020000  // Interrupt 17 enable
#define NVIC_EN0_INT16          0x00010000  // Interrupt 16 enable
#define NVIC_EN0_INT15          0x00008000  // Interrupt 15 enable
#define NVIC_EN0_INT14          0x00004000  // Interrupt 14 enable
#define NVIC_EN0_INT13          0x00002000  // Interrupt 13 enable
#define NVIC_EN0_INT12          0x00001000  // Interrupt 12 enable
#define NVIC_EN0_INT11          0x00000800  // Interrupt 11 enable
#define NVIC_EN0_INT10          0x00000400  // Interrupt 10 enable
#define NVIC_EN0_INT9           0x00000200  // Interrupt 9 enable
#define NVIC_EN0_INT8           0x00000100  // Interrupt 8 enable
#define NVIC_EN0_INT7           0x00000080  // Interrupt 7 enable
#define NVIC_EN0_INT6           0x00000040  // Interrupt 6 enable
#define NVIC_EN0_INT5           0x00000020  // Interrupt 5 enable
#define NVIC_EN0_INT4           0x00000010  // Interrupt 4 enable
#define NVIC_EN0_INT3           0x00000008  // Interrupt 3 enable
#define NVIC_EN0_INT2           0x00000004  // Interrupt 2 enable
#define NVIC_EN0_INT1           0x00000002  // Interrupt 1 enable
#define NVIC_EN0_INT0           0x00000001  // Interrupt 0 enable

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_EN1 register.
//
//*****************************************************************************
#define NVIC_EN1_INT59          0x08000000  // Interrupt 59 enable
#define NVIC_EN1_INT58          0x04000000  // Interrupt 58 enable
#define NVIC_EN1_INT57          0x02000000  // Interrupt 57 enable
#define NVIC_EN1_INT56          0x01000000  // Interrupt 56 enable
#define NVIC_EN1_INT55          0x00800000  // Interrupt 55 enable
#define NVIC_EN1_INT54          0x00400000  // Interrupt 54 enable
#define NVIC_EN1_INT53          0x00200000  // Interrupt 53 enable
#define NVIC_EN1_INT52          0x00100000  // Interrupt 52 enable
#define NVIC_EN1_INT51          0x00080000  // Interrupt 51 enable
#define NVIC_EN1_INT50          0x00040000  // Interrupt 50 enable
#define NVIC_EN1_INT49          0x00020000  // Interrupt 49 enable
#define NVIC_EN1_INT48          0x00010000  // Interrupt 48 enable
#define NVIC_EN1_INT47          0x00008000  // Interrupt 47 enable
#define NVIC_EN1_INT46          0x00004000  // Interrupt 46 enable
#define NVIC_EN1_INT45          0x00002000  // Interrupt 45 enable
#define NVIC_EN1_INT44          0x00001000  // Interrupt 44 enable
#define NVIC_EN1_INT43          0x00000800  // Interrupt 43 enable
#define NVIC_EN1_INT42          0x00000400  // Interrupt 42 enable
#define NVIC_EN1_INT41          0x00000200  // Interrupt 41 enable
#define NVIC_EN1_INT40          0x00000100  // Interrupt 40 enable
#define NVIC_EN1_INT39          0x00000080  // Interrupt 39 enable
#define NVIC_EN1_INT38          0x00000040  // Interrupt 38 enable
#define NVIC_EN1_INT37          0x00000020  // Interrupt 37 enable
#define NVIC_EN1_INT36          0x00000010  // Interrupt 36 enable
#define NVIC_EN1_INT35          0x00000008  // Interrupt 35 enable
#define NVIC_EN1_INT34          0x00000004  // Interrupt 34 enable
#define NVIC_EN1_INT33          0x00000002  // Interrupt 33 enable
#define NVIC_EN1_INT32          0x00000001  // Interrupt 32 enable

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_DIS0 register.
//
//*****************************************************************************
#define NVIC_DIS0_INT31         0x80000000  // Interrupt 31 disable
#define NVIC_DIS0_INT30         0x40000000  // Interrupt 30 disable
#define NVIC_DIS0_INT29         0x20000000  // Interrupt 29 disable
#define NVIC_DIS0_INT28         0x10000000  // Interrupt 28 disable
#define NVIC_DIS0_INT27         0x08000000  // Interrupt 27 disable
#define NVIC_DIS0_INT26         0x04000000  // Interrupt 26 disable
#define NVIC_DIS0_INT25         0x02000000  // Interrupt 25 disable
#define NVIC_DIS0_INT24         0x01000000  // Interrupt 24 disable
#define NVIC_DIS0_INT23         0x00800000  // Interrupt 23 disable
#define NVIC_DIS0_INT22         0x00400000  // Interrupt 22 disable
#define NVIC_DIS0_INT21         0x00200000  // Interrupt 21 disable
#define NVIC_DIS0_INT20         0x00100000  // Interrupt 20 disable
#define NVIC_DIS0_INT19         0x00080000  // Interrupt 19 disable
#define NVIC_DIS0_INT18         0x00040000  // Interrupt 18 disable
#define NVIC_DIS0_INT17         0x00020000  // Interrupt 17 disable
#define NVIC_DIS0_INT16         0x00010000  // Interrupt 16 disable
#define NVIC_DIS0_INT15         0x00008000  // Interrupt 15 disable
#define NVIC_DIS0_INT14         0x00004000  // Interrupt 14 disable
#define NVIC_DIS0_INT13         0x00002000  // Interrupt 13 disable
#define NVIC_DIS0_INT12         0x00001000  // Interrupt 12 disable
#define NVIC_DIS0_INT11         0x00000800  // Interrupt 11 disable
#define NVIC_DIS0_INT10         0x00000400  // Interrupt 10 disable
#define NVIC_DIS0_INT9          0x00000200  // Interrupt 9 disable
#define NVIC_DIS0_INT8          0x00000100  // Interrupt 8 disable
#define NVIC_DIS0_INT7          0x00000080  // Interrupt 7 disable
#define NVIC_DIS0_INT6          0x00000040  // Interrupt 6 disable
#define NVIC_DIS0_INT5          0x00000020  // Interrupt 5 disable
#define NVIC_DIS0_INT4          0x00000010  // Interrupt 4 disable
#define NVIC_DIS0_INT3          0x00000008  // Interrupt 3 disable
#define NVIC_DIS0_INT2          0x00000004  // Interrupt 2 disable
#define NVIC_DIS0_INT1          0x00000002  // Interrupt 1 disable
#define NVIC_DIS0_INT0          0x00000001  // Interrupt 0 disable

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_DIS1 register.
//
//*****************************************************************************
#define NVIC_DIS1_INT59         0x08000000  // Interrupt 59 disable
#define NVIC_DIS1_INT58         0x04000000  // Interrupt 58 disable
#define NVIC_DIS1_INT57         0x02000000  // Interrupt 57 disable
#define NVIC_DIS1_INT56         0x01000000  // Interrupt 56 disable
#define NVIC_DIS1_INT55         0x00800000  // Interrupt 55 disable
#define NVIC_DIS1_INT54         0x00400000  // Interrupt 54 disable
#define NVIC_DIS1_INT53         0x00200000  // Interrupt 53 disable
#define NVIC_DIS1_INT52         0x00100000  // Interrupt 52 disable
#define NVIC_DIS1_INT51         0x00080000  // Interrupt 51 disable
#define NVIC_DIS1_INT50         0x00040000  // Interrupt 50 disable
#define NVIC_DIS1_INT49         0x00020000  // Interrupt 49 disable
#define NVIC_DIS1_INT48         0x00010000  // Interrupt 48 disable
#define NVIC_DIS1_INT47         0x00008000  // Interrupt 47 disable
#define NVIC_DIS1_INT46         0x00004000  // Interrupt 46 disable
#define NVIC_DIS1_INT45         0x00002000  // Interrupt 45 disable
#define NVIC_DIS1_INT44         0x00001000  // Interrupt 44 disable
#define NVIC_DIS1_INT43         0x00000800  // Interrupt 43 disable
#define NVIC_DIS1_INT42         0x00000400  // Interrupt 42 disable
#define NVIC_DIS1_INT41         0x00000200  // Interrupt 41 disable
#define NVIC_DIS1_INT40         0x00000100  // Interrupt 40 disable
#define NVIC_DIS1_INT39         0x00000080  // Interrupt 39 disable
#define NVIC_DIS1_INT38         0x00000040  // Interrupt 38 disable
#define NVIC_DIS1_INT37         0x00000020  // Interrupt 37 disable
#define NVIC_DIS1_INT36         0x00000010  // Interrupt 36 disable
#define NVIC_DIS1_INT35         0x00000008  // Interrupt 35 disable
#define NVIC_DIS1_INT34         0x00000004  // Interrupt 34 disable
#define NVIC_DIS1_INT33         0x00000002  // Interrupt 33 disable
#define NVIC_DIS1_INT32         0x00000001  // Interrupt 32 disable

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PEND0 register.
//
//*****************************************************************************
#define NVIC_PEND0_INT31        0x80000000  // Interrupt 31 pend
#define NVIC_PEND0_INT30        0x40000000  // Interrupt 30 pend
#define NVIC_PEND0_INT29        0x20000000  // Interrupt 29 pend
#define NVIC_PEND0_INT28        0x10000000  // Interrupt 28 pend
#define NVIC_PEND0_INT27        0x08000000  // Interrupt 27 pend
#define NVIC_PEND0_INT26        0x04000000  // Interrupt 26 pend
#define NVIC_PEND0_INT25        0x02000000  // Interrupt 25 pend
#define NVIC_PEND0_INT24        0x01000000  // Interrupt 24 pend
#define NVIC_PEND0_INT23        0x00800000  // Interrupt 23 pend
#define NVIC_PEND0_INT22        0x00400000  // Interrupt 22 pend
#define NVIC_PEND0_INT21        0x00200000  // Interrupt 21 pend
#define NVIC_PEND0_INT20        0x00100000  // Interrupt 20 pend
#define NVIC_PEND0_INT19        0x00080000  // Interrupt 19 pend
#define NVIC_PEND0_INT18        0x00040000  // Interrupt 18 pend
#define NVIC_PEND0_INT17        0x00020000  // Interrupt 17 pend
#define NVIC_PEND0_INT16        0x00010000  // Interrupt 16 pend
#define NVIC_PEND0_INT15        0x00008000  // Interrupt 15 pend
#define NVIC_PEND0_INT14        0x00004000  // Interrupt 14 pend
#define NVIC_PEND0_INT13        0x00002000  // Interrupt 13 pend
#define NVIC_PEND0_INT12        0x00001000  // Interrupt 12 pend
#define NVIC_PEND0_INT11        0x00000800  // Interrupt 11 pend
#define NVIC_PEND0_INT10        0x00000400  // Interrupt 10 pend
#define NVIC_PEND0_INT9         0x00000200  // Interrupt 9 pend
#define NVIC_PEND0_INT8         0x00000100  // Interrupt 8 pend
#define NVIC_PEND0_INT7         0x00000080  // Interrupt 7 pend
#define NVIC_PEND0_INT6         0x00000040  // Interrupt 6 pend
#define NVIC_PEND0_INT5         0x00000020  // Interrupt 5 pend
#define NVIC_PEND0_INT4         0x00000010  // Interrupt 4 pend
#define NVIC_PEND0_INT3         0x00000008  // Interrupt 3 pend
#define NVIC_PEND0_INT2         0x00000004  // Interrupt 2 pend
#define NVIC_PEND0_INT1         0x00000002  // Interrupt 1 pend
#define NVIC_PEND0_INT0         0x00000001  // Interrupt 0 pend

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PEND1 register.
//
//*****************************************************************************
#define NVIC_PEND1_INT59        0x08000000  // Interrupt 59 pend
#define NVIC_PEND1_INT58        0x04000000  // Interrupt 58 pend
#define NVIC_PEND1_INT57        0x02000000  // Interrupt 57 pend
#define NVIC_PEND1_INT56        0x01000000  // Interrupt 56 pend
#define NVIC_PEND1_INT55        0x00800000  // Interrupt 55 pend
#define NVIC_PEND1_INT54        0x00400000  // Interrupt 54 pend
#define NVIC_PEND1_INT53        0x00200000  // Interrupt 53 pend
#define NVIC_PEND1_INT52        0x00100000  // Interrupt 52 pend
#define NVIC_PEND1_INT51        0x00080000  // Interrupt 51 pend
#define NVIC_PEND1_INT50        0x00040000  // Interrupt 50 pend
#define NVIC_PEND1_INT49        0x00020000  // Interrupt 49 pend
#define NVIC_PEND1_INT48        0x00010000  // Interrupt 48 pend
#define NVIC_PEND1_INT47        0x00008000  // Interrupt 47 pend
#define NVIC_PEND1_INT46        0x00004000  // Interrupt 46 pend
#define NVIC_PEND1_INT45        0x00002000  // Interrupt 45 pend
#define NVIC_PEND1_INT44        0x00001000  // Interrupt 44 pend
#define NVIC_PEND1_INT43        0x00000800  // Interrupt 43 pend
#define NVIC_PEND1_INT42        0x00000400  // Interrupt 42 pend
#define NVIC_PEND1_INT41        0x00000200  // Interrupt 41 pend
#define NVIC_PEND1_INT40        0x00000100  // Interrupt 40 pend
#define NVIC_PEND1_INT39        0x00000080  // Interrupt 39 pend
#define NVIC_PEND1_INT38        0x00000040  // Interrupt 38 pend
#define NVIC_PEND1_INT37        0x00000020  // Interrupt 37 pend
#define NVIC_PEND1_INT36        0x00000010  // Interrupt 36 pend
#define NVIC_PEND1_INT35        0x00000008  // Interrupt 35 pend
#define NVIC_PEND1_INT34        0x00000004  // Interrupt 34 pend
#define NVIC_PEND1_INT33        0x00000002  // Interrupt 33 pend
#define NVIC_PEND1_INT32        0x00000001  // Interrupt 32 pend

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_UNPEND0 register.
//
//*****************************************************************************
#define NVIC_UNPEND0_INT31      0x80000000  // Interrupt 31 unpend
#define NVIC_UNPEND0_INT30      0x40000000  // Interrupt 30 unpend
#define NVIC_UNPEND0_INT29      0x20000000  // Interrupt 29 unpend
#define NVIC_UNPEND0_INT28      0x10000000  // Interrupt 28 unpend
#define NVIC_UNPEND0_INT27      0x08000000  // Interrupt 27 unpend
#define NVIC_UNPEND0_INT26      0x04000000  // Interrupt 26 unpend
#define NVIC_UNPEND0_INT25      0x02000000  // Interrupt 25 unpend
#define NVIC_UNPEND0_INT24      0x01000000  // Interrupt 24 unpend
#define NVIC_UNPEND0_INT23      0x00800000  // Interrupt 23 unpend
#define NVIC_UNPEND0_INT22      0x00400000  // Interrupt 22 unpend
#define NVIC_UNPEND0_INT21      0x00200000  // Interrupt 21 unpend
#define NVIC_UNPEND0_INT20      0x00100000  // Interrupt 20 unpend
#define NVIC_UNPEND0_INT19      0x00080000  // Interrupt 19 unpend
#define NVIC_UNPEND0_INT18      0x00040000  // Interrupt 18 unpend
#define NVIC_UNPEND0_INT17      0x00020000  // Interrupt 17 unpend
#define NVIC_UNPEND0_INT16      0x00010000  // Interrupt 16 unpend
#define NVIC_UNPEND0_INT15      0x00008000  // Interrupt 15 unpend
#define NVIC_UNPEND0_INT14      0x00004000  // Interrupt 14 unpend
#define NVIC_UNPEND0_INT13      0x00002000  // Interrupt 13 unpend
#define NVIC_UNPEND0_INT12      0x00001000  // Interrupt 12 unpend
#define NVIC_UNPEND0_INT11      0x00000800  // Interrupt 11 unpend
#define NVIC_UNPEND0_INT10      0x00000400  // Interrupt 10 unpend
#define NVIC_UNPEND0_INT9       0x00000200  // Interrupt 9 unpend
#define NVIC_UNPEND0_INT8       0x00000100  // Interrupt 8 unpend
#define NVIC_UNPEND0_INT7       0x00000080  // Interrupt 7 unpend
#define NVIC_UNPEND0_INT6       0x00000040  // Interrupt 6 unpend
#define NVIC_UNPEND0_INT5       0x00000020  // Interrupt 5 unpend
#define NVIC_UNPEND0_INT4       0x00000010  // Interrupt 4 unpend
#define NVIC_UNPEND0_INT3       0x00000008  // Interrupt 3 unpend
#define NVIC_UNPEND0_INT2       0x00000004  // Interrupt 2 unpend
#define NVIC_UNPEND0_INT1       0x00000002  // Interrupt 1 unpend
#define NVIC_UNPEND0_INT0       0x00000001  // Interrupt 0 unpend

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_UNPEND1 register.
//
//*****************************************************************************
#define NVIC_UNPEND1_INT59      0x08000000  // Interrupt 59 unpend
#define NVIC_UNPEND1_INT58      0x04000000  // Interrupt 58 unpend
#define NVIC_UNPEND1_INT57      0x02000000  // Interrupt 57 unpend
#define NVIC_UNPEND1_INT56      0x01000000  // Interrupt 56 unpend
#define NVIC_UNPEND1_INT55      0x00800000  // Interrupt 55 unpend
#define NVIC_UNPEND1_INT54      0x00400000  // Interrupt 54 unpend
#define NVIC_UNPEND1_INT53      0x00200000  // Interrupt 53 unpend
#define NVIC_UNPEND1_INT52      0x00100000  // Interrupt 52 unpend
#define NVIC_UNPEND1_INT51      0x00080000  // Interrupt 51 unpend
#define NVIC_UNPEND1_INT50      0x00040000  // Interrupt 50 unpend
#define NVIC_UNPEND1_INT49      0x00020000  // Interrupt 49 unpend
#define NVIC_UNPEND1_INT48      0x00010000  // Interrupt 48 unpend
#define NVIC_UNPEND1_INT47      0x00008000  // Interrupt 47 unpend
#define NVIC_UNPEND1_INT46      0x00004000  // Interrupt 46 unpend
#define NVIC_UNPEND1_INT45      0x00002000  // Interrupt 45 unpend
#define NVIC_UNPEND1_INT44      0x00001000  // Interrupt 44 unpend
#define NVIC_UNPEND1_INT43      0x00000800  // Interrupt 43 unpend
#define NVIC_UNPEND1_INT42      0x00000400  // Interrupt 42 unpend
#define NVIC_UNPEND1_INT41      0x00000200  // Interrupt 41 unpend
#define NVIC_UNPEND1_INT40      0x00000100  // Interrupt 40 unpend
#define NVIC_UNPEND1_INT39      0x00000080  // Interrupt 39 unpend
#define NVIC_UNPEND1_INT38      0x00000040  // Interrupt 38 unpend
#define NVIC_UNPEND1_INT37      0x00000020  // Interrupt 37 unpend
#define NVIC_UNPEND1_INT36      0x00000010  // Interrupt 36 unpend
#define NVIC_UNPEND1_INT35      0x00000008  // Interrupt 35 unpend
#define NVIC_UNPEND1_INT34      0x00000004  // Interrupt 34 unpend
#define NVIC_UNPEND1_INT33      0x00000002  // Interrupt 33 unpend
#define NVIC_UNPEND1_INT32      0x00000001  // Interrupt 32 unpend

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_ACTIVE0 register.
//
//*****************************************************************************
#define NVIC_ACTIVE0_INT31      0x80000000  // Interrupt 31 active
#define NVIC_ACTIVE0_INT30      0x40000000  // Interrupt 30 active
#define NVIC_ACTIVE0_INT29      0x20000000  // Interrupt 29 active
#define NVIC_ACTIVE0_INT28      0x10000000  // Interrupt 28 active
#define NVIC_ACTIVE0_INT27      0x08000000  // Interrupt 27 active
#define NVIC_ACTIVE0_INT26      0x04000000  // Interrupt 26 active
#define NVIC_ACTIVE0_INT25      0x02000000  // Interrupt 25 active
#define NVIC_ACTIVE0_INT24      0x01000000  // Interrupt 24 active
#define NVIC_ACTIVE0_INT23      0x00800000  // Interrupt 23 active
#define NVIC_ACTIVE0_INT22      0x00400000  // Interrupt 22 active
#define NVIC_ACTIVE0_INT21      0x00200000  // Interrupt 21 active
#define NVIC_ACTIVE0_INT20      0x00100000  // Interrupt 20 active
#define NVIC_ACTIVE0_INT19      0x00080000  // Interrupt 19 active
#define NVIC_ACTIVE0_INT18      0x00040000  // Interrupt 18 active
#define NVIC_ACTIVE0_INT17      0x00020000  // Interrupt 17 active
#define NVIC_ACTIVE0_INT16      0x00010000  // Interrupt 16 active
#define NVIC_ACTIVE0_INT15      0x00008000  // Interrupt 15 active
#define NVIC_ACTIVE0_INT14      0x00004000  // Interrupt 14 active
#define NVIC_ACTIVE0_INT13      0x00002000  // Interrupt 13 active
#define NVIC_ACTIVE0_INT12      0x00001000  // Interrupt 12 active
#define NVIC_ACTIVE0_INT11      0x00000800  // Interrupt 11 active
#define NVIC_ACTIVE0_INT10      0x00000400  // Interrupt 10 active
#define NVIC_ACTIVE0_INT9       0x00000200  // Interrupt 9 active
#define NVIC_ACTIVE0_INT8       0x00000100  // Interrupt 8 active
#define NVIC_ACTIVE0_INT7       0x00000080  // Interrupt 7 active
#define NVIC_ACTIVE0_INT6       0x00000040  // Interrupt 6 active
#define NVIC_ACTIVE0_INT5       0x00000020  // Interrupt 5 active
#define NVIC_ACTIVE0_INT4       0x00000010  // Interrupt 4 active
#define NVIC_ACTIVE0_INT3       0x00000008  // Interrupt 3 active
#define NVIC_ACTIVE0_INT2       0x00000004  // Interrupt 2 active
#define NVIC_ACTIVE0_INT1       0x00000002  // Interrupt 1 active
#define NVIC_ACTIVE0_INT0       0x00000001  // Interrupt 0 active

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_ACTIVE1 register.
//
//*****************************************************************************
#define NVIC_ACTIVE1_INT59      0x08000000  // Interrupt 59 active
#define NVIC_ACTIVE1_INT58      0x04000000  // Interrupt 58 active
#define NVIC_ACTIVE1_INT57      0x02000000  // Interrupt 57 active
#define NVIC_ACTIVE1_INT56      0x01000000  // Interrupt 56 active
#define NVIC_ACTIVE1_INT55      0x00800000  // Interrupt 55 active
#define NVIC_ACTIVE1_INT54      0x00400000  // Interrupt 54 active
#define NVIC_ACTIVE1_INT53      0x00200000  // Interrupt 53 active
#define NVIC_ACTIVE1_INT52      0x00100000  // Interrupt 52 active
#define NVIC_ACTIVE1_INT51      0x00080000  // Interrupt 51 active
#define NVIC_ACTIVE1_INT50      0x00040000  // Interrupt 50 active
#define NVIC_ACTIVE1_INT49      0x00020000  // Interrupt 49 active
#define NVIC_ACTIVE1_INT48      0x00010000  // Interrupt 48 active
#define NVIC_ACTIVE1_INT47      0x00008000  // Interrupt 47 active
#define NVIC_ACTIVE1_INT46      0x00004000  // Interrupt 46 active
#define NVIC_ACTIVE1_INT45      0x00002000  // Interrupt 45 active
#define NVIC_ACTIVE1_INT44      0x00001000  // Interrupt 44 active
#define NVIC_ACTIVE1_INT43      0x00000800  // Interrupt 43 active
#define NVIC_ACTIVE1_INT42      0x00000400  // Interrupt 42 active
#define NVIC_ACTIVE1_INT41      0x00000200  // Interrupt 41 active
#define NVIC_ACTIVE1_INT40      0x00000100  // Interrupt 40 active
#define NVIC_ACTIVE1_INT39      0x00000080  // Interrupt 39 active
#define NVIC_ACTIVE1_INT38      0x00000040  // Interrupt 38 active
#define NVIC_ACTIVE1_INT37      0x00000020  // Interrupt 37 active
#define NVIC_ACTIVE1_INT36      0x00000010  // Interrupt 36 active
#define NVIC_ACTIVE1_INT35      0x00000008  // Interrupt 35 active
#define NVIC_ACTIVE1_INT34      0x00000004  // Interrupt 34 active
#define NVIC_ACTIVE1_INT33      0x00000002  // Interrupt 33 active
#define NVIC_ACTIVE1_INT32      0x00000001  // Interrupt 32 active

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI0 register.
//
//*****************************************************************************
#define NVIC_PRI0_INT3_M        0xFF000000  // Interrupt 3 priority mask
#define NVIC_PRI0_INT2_M        0x00FF0000  // Interrupt 2 priority mask
#define NVIC_PRI0_INT1_M        0x0000FF00  // Interrupt 1 priority mask
#define NVIC_PRI0_INT0_M        0x000000FF  // Interrupt 0 priority mask
#define NVIC_PRI0_INT3_S        24
#define NVIC_PRI0_INT2_S        16
#define NVIC_PRI0_INT1_S        8
#define NVIC_PRI0_INT0_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI1 register.
//
//*****************************************************************************
#define NVIC_PRI1_INT7_M        0xFF000000  // Interrupt 7 priority mask
#define NVIC_PRI1_INT6_M        0x00FF0000  // Interrupt 6 priority mask
#define NVIC_PRI1_INT5_M        0x0000FF00  // Interrupt 5 priority mask
#define NVIC_PRI1_INT4_M        0x000000FF  // Interrupt 4 priority mask
#define NVIC_PRI1_INT7_S        24
#define NVIC_PRI1_INT6_S        16
#define NVIC_PRI1_INT5_S        8
#define NVIC_PRI1_INT4_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI2 register.
//
//*****************************************************************************
#define NVIC_PRI2_INT11_M       0xFF000000  // Interrupt 11 priority mask
#define NVIC_PRI2_INT10_M       0x00FF0000  // Interrupt 10 priority mask
#define NVIC_PRI2_INT9_M        0x0000FF00  // Interrupt 9 priority mask
#define NVIC_PRI2_INT8_M        0x000000FF  // Interrupt 8 priority mask
#define NVIC_PRI2_INT11_S       24
#define NVIC_PRI2_INT10_S       16
#define NVIC_PRI2_INT9_S        8
#define NVIC_PRI2_INT8_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI3 register.
//
//*****************************************************************************
#define NVIC_PRI3_INT15_M       0xFF000000  // Interrupt 15 priority mask
#define NVIC_PRI3_INT14_M       0x00FF0000  // Interrupt 14 priority mask
#define NVIC_PRI3_INT13_M       0x0000FF00  // Interrupt 13 priority mask
#define NVIC_PRI3_INT12_M       0x000000FF  // Interrupt 12 priority mask
#define NVIC_PRI3_INT15_S       24
#define NVIC_PRI3_INT14_S       16
#define NVIC_PRI3_INT13_S       8
#define NVIC_PRI3_INT12_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI4 register.
//
//*****************************************************************************
#define NVIC_PRI4_INT19_M       0xFF000000  // Interrupt 19 priority mask
#define NVIC_PRI4_INT18_M       0x00FF0000  // Interrupt 18 priority mask
#define NVIC_PRI4_INT17_M       0x0000FF00  // Interrupt 17 priority mask
#define NVIC_PRI4_INT16_M       0x000000FF  // Interrupt 16 priority mask
#define NVIC_PRI4_INT19_S       24
#define NVIC_PRI4_INT18_S       16
#define NVIC_PRI4_INT17_S       8
#define NVIC_PRI4_INT16_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI5 register.
//
//*****************************************************************************
#define NVIC_PRI5_INT23_M       0xFF000000  // Interrupt 23 priority mask
#define NVIC_PRI5_INT22_M       0x00FF0000  // Interrupt 22 priority mask
#define NVIC_PRI5_INT21_M       0x0000FF00  // Interrupt 21 priority mask
#define NVIC_PRI5_INT20_M       0x000000FF  // Interrupt 20 priority mask
#define NVIC_PRI5_INT23_S       24
#define NVIC_PRI5_INT22_S       16
#define NVIC_PRI5_INT21_S       8
#define NVIC_PRI5_INT20_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI6 register.
//
//*****************************************************************************
#define NVIC_PRI6_INT27_M       0xFF000000  // Interrupt 27 priority mask
#define NVIC_PRI6_INT26_M       0x00FF0000  // Interrupt 26 priority mask
#define NVIC_PRI6_INT25_M       0x0000FF00  // Interrupt 25 priority mask
#define NVIC_PRI6_INT24_M       0x000000FF  // Interrupt 24 priority mask
#define NVIC_PRI6_INT27_S       24
#define NVIC_PRI6_INT26_S       16
#define NVIC_PRI6_INT25_S       8
#define NVIC_PRI6_INT24_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI7 register.
//
//*****************************************************************************
#define NVIC_PRI7_INT31_M       0xFF000000  // Interrupt 31 priority mask
#define NVIC_PRI7_INT30_M       0x00FF0000  // Interrupt 30 priority mask
#define NVIC_PRI7_INT29_M       0x0000FF00  // Interrupt 29 priority mask
#define NVIC_PRI7_INT28_M       0x000000FF  // Interrupt 28 priority mask
#define NVIC_PRI7_INT31_S       24
#define NVIC_PRI7_INT30_S       16
#define NVIC_PRI7_INT29_S       8
#define NVIC_PRI7_INT28_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI8 register.
//
//*****************************************************************************
#define NVIC_PRI8_INT35_M       0xFF000000  // Interrupt 35 priority mask
#define NVIC_PRI8_INT34_M       0x00FF0000  // Interrupt 34 priority mask
#define NVIC_PRI8_INT33_M       0x0000FF00  // Interrupt 33 priority mask
#define NVIC_PRI8_INT32_M       0x000000FF  // Interrupt 32 priority mask
#define NVIC_PRI8_INT35_S       24
#define NVIC_PRI8_INT34_S       16
#define NVIC_PRI8_INT33_S       8
#define NVIC_PRI8_INT32_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI9 register.
//
//*****************************************************************************
#define NVIC_PRI9_INT39_M       0xFF000000  // Interrupt 39 priority mask
#define NVIC_PRI9_INT38_M       0x00FF0000  // Interrupt 38 priority mask
#define NVIC_PRI9_INT37_M       0x0000FF00  // Interrupt 37 priority mask
#define NVIC_PRI9_INT36_M       0x000000FF  // Interrupt 36 priority mask
#define NVIC_PRI9_INT39_S       24
#define NVIC_PRI9_INT38_S       16
#define NVIC_PRI9_INT37_S       8
#define NVIC_PRI9_INT36_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_PRI10 register.
//
//*****************************************************************************
#define NVIC_PRI10_INT43_M      0xFF000000  // Interrupt 43 priority mask
#define NVIC_PRI10_INT42_M      0x00FF0000  // Interrupt 42 priority mask
#define NVIC_PRI10_INT41_M      0x0000FF00  // Interrupt 41 priority mask
#define NVIC_PRI10_INT40_M      0x000000FF  // Interrupt 40 priority mask
#define NVIC_PRI10_INT43_S      24
#define NVIC_PRI10_INT42_S      16
#define NVIC_PRI10_INT41_S      8
#define NVIC_PRI10_INT40_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_CPUID register.
//
//*****************************************************************************
#define NVIC_CPUID_IMP_M        0xFF000000  // Implementer
#define NVIC_CPUID_VAR_M        0x00F00000  // Variant
#define NVIC_CPUID_PARTNO_M     0x0000FFF0  // Processor part number
#define NVIC_CPUID_REV_M        0x0000000F  // Revision

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_INT_CTRL register.
//
//*****************************************************************************
#define NVIC_INT_CTRL_NMI_SET   0x80000000  // Pend a NMI
#define NVIC_INT_CTRL_PEND_SV   0x10000000  // Pend a PendSV
#define NVIC_INT_CTRL_UNPEND_SV 0x08000000  // Unpend a PendSV
#define NVIC_INT_CTRL_PENDSTSET 0x04000000  // Set pending SysTick interrupt
#define NVIC_INT_CTRL_PENDSTCLR 0x02000000  // Clear pending SysTick interrupt
#define NVIC_INT_CTRL_ISR_PRE   0x00800000  // Debug interrupt handling
#define NVIC_INT_CTRL_ISR_PEND  0x00400000  // Debug interrupt pending
#define NVIC_INT_CTRL_VEC_PEN_M 0x003FF000  // Highest pending exception
#define NVIC_INT_CTRL_RET_BASE  0x00000800  // Return to base
#define NVIC_INT_CTRL_VEC_ACT_M 0x000003FF  // Current active exception
#define NVIC_INT_CTRL_VEC_PEN_S 12
#define NVIC_INT_CTRL_VEC_ACT_S 0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_VTABLE register.
//
//*****************************************************************************
#define NVIC_VTABLE_BASE        0x20000000  // Vector table base
#define NVIC_VTABLE_OFFSET_M    0x1FFFFF00  // Vector table offset
#define NVIC_VTABLE_OFFSET_S    8

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_APINT register.
//
//*****************************************************************************
#define NVIC_APINT_VECTKEY_M    0xFFFF0000  // Vector key mask
#define NVIC_APINT_VECTKEY      0x05FA0000  // Vector key
#define NVIC_APINT_ENDIANESS    0x00008000  // Data endianess
#define NVIC_APINT_PRIGROUP_M   0x00000700  // Priority group
#define NVIC_APINT_PRIGROUP_7_1 0x00000000  // Priority group 7.1 split
#define NVIC_APINT_PRIGROUP_6_2 0x00000100  // Priority group 6.2 split
#define NVIC_APINT_PRIGROUP_5_3 0x00000200  // Priority group 5.3 split
#define NVIC_APINT_PRIGROUP_4_4 0x00000300  // Priority group 4.4 split
#define NVIC_APINT_PRIGROUP_3_5 0x00000400  // Priority group 3.5 split
#define NVIC_APINT_PRIGROUP_2_6 0x00000500  // Priority group 2.6 split
#define NVIC_APINT_PRIGROUP_1_7 0x00000600  // Priority group 1.7 split
#define NVIC_APINT_PRIGROUP_0_8 0x00000700  // Priority group 0.8 split
#define NVIC_APINT_SYSRESETREQ  0x00000004  // System reset request
#define NVIC_APINT_VECT_CLR_ACT 0x00000002  // Clear active NMI/fault info
#define NVIC_APINT_VECT_RESET   0x00000001  // System reset

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_SYS_CTRL register.
//
//*****************************************************************************
#define NVIC_SYS_CTRL_SEVONPEND 0x00000010  // Wakeup on pend
#define NVIC_SYS_CTRL_SLEEPDEEP 0x00000004  // Deep sleep enable
#define NVIC_SYS_CTRL_SLEEPEXIT 0x00000002  // Sleep on ISR exit

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_CFG_CTRL register.
//
//*****************************************************************************
#define NVIC_CFG_CTRL_BFHFNMIGN 0x00000100  // Ignore bus fault in NMI/fault
#define NVIC_CFG_CTRL_DIV0      0x00000010  // Trap on divide by 0
#define NVIC_CFG_CTRL_UNALIGNED 0x00000008  // Trap on unaligned access
#define NVIC_CFG_CTRL_DEEP_PEND 0x00000004  // Allow deep interrupt trigger
#define NVIC_CFG_CTRL_MAIN_PEND 0x00000002  // Allow main interrupt trigger
#define NVIC_CFG_CTRL_BASE_THR  0x00000001  // Thread state control

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_SYS_PRI1 register.
//
//*****************************************************************************
#define NVIC_SYS_PRI1_RES_M     0xFF000000  // Priority of reserved handler
#define NVIC_SYS_PRI1_USAGE_M   0x00FF0000  // Priority of usage fault handler
#define NVIC_SYS_PRI1_BUS_M     0x0000FF00  // Priority of bus fault handler
#define NVIC_SYS_PRI1_MEM_M     0x000000FF  // Priority of mem manage handler
#define NVIC_SYS_PRI1_USAGE_S   16
#define NVIC_SYS_PRI1_BUS_S     8
#define NVIC_SYS_PRI1_MEM_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_SYS_PRI2 register.
//
//*****************************************************************************
#define NVIC_SYS_PRI2_SVC_M     0xFF000000  // Priority of SVCall handler
#define NVIC_SYS_PRI2_RES_M     0x00FFFFFF  // Priority of reserved handlers
#define NVIC_SYS_PRI2_SVC_S     24

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_SYS_PRI3 register.
//
//*****************************************************************************
#define NVIC_SYS_PRI3_TICK_M    0xFF000000  // Priority of Sys Tick handler
#define NVIC_SYS_PRI3_PENDSV_M  0x00FF0000  // Priority of PendSV handler
#define NVIC_SYS_PRI3_RES_M     0x0000FF00  // Priority of reserved handler
#define NVIC_SYS_PRI3_DEBUG_M   0x000000FF  // Priority of debug handler
#define NVIC_SYS_PRI3_TICK_S    24
#define NVIC_SYS_PRI3_PENDSV_S  16
#define NVIC_SYS_PRI3_DEBUG_S   0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_SYS_HND_CTRL
// register.
//
//*****************************************************************************
#define NVIC_SYS_HND_CTRL_USAGE 0x00040000  // Usage fault enable
#define NVIC_SYS_HND_CTRL_BUS   0x00020000  // Bus fault enable
#define NVIC_SYS_HND_CTRL_MEM   0x00010000  // Mem manage fault enable
#define NVIC_SYS_HND_CTRL_SVC   0x00008000  // SVCall is pended
#define NVIC_SYS_HND_CTRL_BUSP  0x00004000  // Bus fault is pended
#define NVIC_SYS_HND_CTRL_TICK  0x00000800  // Sys tick is active
#define NVIC_SYS_HND_CTRL_PNDSV 0x00000400  // PendSV is active
#define NVIC_SYS_HND_CTRL_MON   0x00000100  // Monitor is active
#define NVIC_SYS_HND_CTRL_SVCA  0x00000080  // SVCall is active
#define NVIC_SYS_HND_CTRL_USGA  0x00000008  // Usage fault is active
#define NVIC_SYS_HND_CTRL_BUSA  0x00000002  // Bus fault is active
#define NVIC_SYS_HND_CTRL_MEMA  0x00000001  // Mem manage is active

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_FAULT_STAT
// register.
//
//*****************************************************************************
#define NVIC_FAULT_STAT_DIV0    0x02000000  // Divide by zero fault
#define NVIC_FAULT_STAT_UNALIGN 0x01000000  // Unaligned access fault
#define NVIC_FAULT_STAT_NOCP    0x00080000  // No coprocessor fault
#define NVIC_FAULT_STAT_INVPC   0x00040000  // Invalid PC fault
#define NVIC_FAULT_STAT_INVSTAT 0x00020000  // Invalid state fault
#define NVIC_FAULT_STAT_UNDEF   0x00010000  // Undefined instruction fault
#define NVIC_FAULT_STAT_BFARV   0x00008000  // BFAR is valid
#define NVIC_FAULT_STAT_BSTKE   0x00001000  // Stack bus fault
#define NVIC_FAULT_STAT_BUSTKE  0x00000800  // Unstack bus fault
#define NVIC_FAULT_STAT_IMPRE   0x00000400  // Imprecise data bus error
#define NVIC_FAULT_STAT_PRECISE 0x00000200  // Precise data bus error
#define NVIC_FAULT_STAT_IBUS    0x00000100  // Instruction bus fault
#define NVIC_FAULT_STAT_MMARV   0x00000080  // MMAR is valid
#define NVIC_FAULT_STAT_MSTKE   0x00000010  // Stack access violation
#define NVIC_FAULT_STAT_MUSTKE  0x00000008  // Unstack access violation
#define NVIC_FAULT_STAT_DERR    0x00000002  // Data access violation
#define NVIC_FAULT_STAT_IERR    0x00000001  // Instruction access violation

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_HFAULT_STAT
// register.
//
//*****************************************************************************
#define NVIC_HFAULT_STAT_DBG    0x80000000  // Debug event
#define NVIC_HFAULT_STAT_FORCED 0x40000000  // Cannot execute fault handler
#define NVIC_HFAULT_STAT_VECT   0x00000002  // Vector table read fault

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_DEBUG_STAT
// register.
//
//*****************************************************************************
#define NVIC_DEBUG_STAT_EXTRNL  0x00000010  // EDBGRQ asserted
#define NVIC_DEBUG_STAT_VCATCH  0x00000008  // Vector catch
#define NVIC_DEBUG_STAT_DWTTRAP 0x00000004  // DWT match
#define NVIC_DEBUG_STAT_BKPT    0x00000002  // Breakpoint instruction
#define NVIC_DEBUG_STAT_HALTED  0x00000001  // Halt request

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_MM_ADDR register.
//
//*****************************************************************************
#define NVIC_MM_ADDR_M          0xFFFFFFFF  // Data fault address
#define NVIC_MM_ADDR_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_FAULT_ADDR
// register.
//
//*****************************************************************************
#define NVIC_FAULT_ADDR_M       0xFFFFFFFF  // Data bus fault address
#define NVIC_FAULT_ADDR_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_MPU_TYPE register.
//
//*****************************************************************************
#define NVIC_MPU_TYPE_IREGION_M 0x00FF0000  // Number of I regions
#define NVIC_MPU_TYPE_DREGION_M 0x0000FF00  // Number of D regions
#define NVIC_MPU_TYPE_SEPARATE  0x00000001  // Separate or unified MPU
#define NVIC_MPU_TYPE_IREGION_S 16
#define NVIC_MPU_TYPE_DREGION_S 8

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_MPU_CTRL register.
//
//*****************************************************************************
#define NVIC_MPU_CTRL_PRIVDEFEN 0x00000004  // MPU default region in priv mode
#define NVIC_MPU_CTRL_HFNMIENA  0x00000002  // MPU enabled during faults
#define NVIC_MPU_CTRL_ENABLE    0x00000001  // MPU enable

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_MPU_NUMBER
// register.
//
//*****************************************************************************
#define NVIC_MPU_NUMBER_M       0x000000FF  // MPU region to access
#define NVIC_MPU_NUMBER_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_MPU_BASE register.
//
//*****************************************************************************
#define NVIC_MPU_BASE_ADDR_M    0xFFFFFFE0  // Base address mask
#define NVIC_MPU_BASE_VALID     0x00000010  // Region number valid
#define NVIC_MPU_BASE_REGION_M  0x0000000F  // Region number
#define NVIC_MPU_BASE_ADDR_S    8
#define NVIC_MPU_BASE_REGION_S  0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_MPU_ATTR register.
//
//*****************************************************************************
#define NVIC_MPU_ATTR_M         0xFFFF0000  // Attributes
#define NVIC_MPU_ATTR_AP_NO_NO  0x00000000  // prv: no access, usr: no access
#define NVIC_MPU_ATTR_BUFFRABLE 0x00010000  // Bufferable
#define NVIC_MPU_ATTR_CACHEABLE 0x00020000  // Cacheable
#define NVIC_MPU_ATTR_SHAREABLE 0x00040000  // Shareable
#define NVIC_MPU_ATTR_TEX_M     0x00380000  // Type extension mask
#define NVIC_MPU_ATTR_AP_RW_NO  0x01000000  // prv: rw, usr: none
#define NVIC_MPU_ATTR_AP_RW_RO  0x02000000  // prv: rw, usr: read-only
#define NVIC_MPU_ATTR_AP_RW_RW  0x03000000  // prv: rw, usr: rw
#define NVIC_MPU_ATTR_AP_RO_NO  0x05000000  // prv: ro, usr: none
#define NVIC_MPU_ATTR_AP_RO_RO  0x06000000  // prv: ro, usr: ro
#define NVIC_MPU_ATTR_AP_M      0x07000000  // Access permissions mask
#define NVIC_MPU_ATTR_XN        0x10000000  // Execute disable
#define NVIC_MPU_ATTR_SRD_M     0x0000FF00  // Sub-region disable mask
#define NVIC_MPU_ATTR_SRD_0     0x00000100  // Sub-region 0 disable
#define NVIC_MPU_ATTR_SRD_1     0x00000200  // Sub-region 1 disable
#define NVIC_MPU_ATTR_SRD_2     0x00000400  // Sub-region 2 disable
#define NVIC_MPU_ATTR_SRD_3     0x00000800  // Sub-region 3 disable
#define NVIC_MPU_ATTR_SRD_4     0x00001000  // Sub-region 4 disable
#define NVIC_MPU_ATTR_SRD_5     0x00002000  // Sub-region 5 disable
#define NVIC_MPU_ATTR_SRD_6     0x00004000  // Sub-region 6 disable
#define NVIC_MPU_ATTR_SRD_7     0x00008000  // Sub-region 7 disable
#define NVIC_MPU_ATTR_SIZE_M    0x0000003E  // Region size mask
#define NVIC_MPU_ATTR_SIZE_32B  0x00000008  // Region size 32 bytes
#define NVIC_MPU_ATTR_SIZE_64B  0x0000000A  // Region size 64 bytes
#define NVIC_MPU_ATTR_SIZE_128B 0x0000000C  // Region size 128 bytes
#define NVIC_MPU_ATTR_SIZE_256B 0x0000000E  // Region size 256 bytes
#define NVIC_MPU_ATTR_SIZE_512B 0x00000010  // Region size 512 bytes
#define NVIC_MPU_ATTR_SIZE_1K   0x00000012  // Region size 1 Kbytes
#define NVIC_MPU_ATTR_SIZE_2K   0x00000014  // Region size 2 Kbytes
#define NVIC_MPU_ATTR_SIZE_4K   0x00000016  // Region size 4 Kbytes
#define NVIC_MPU_ATTR_SIZE_8K   0x00000018  // Region size 8 Kbytes
#define NVIC_MPU_ATTR_SIZE_16K  0x0000001A  // Region size 16 Kbytes
#define NVIC_MPU_ATTR_SIZE_32K  0x0000001C  // Region size 32 Kbytes
#define NVIC_MPU_ATTR_SIZE_64K  0x0000001E  // Region size 64 Kbytes
#define NVIC_MPU_ATTR_SIZE_128K 0x00000020  // Region size 128 Kbytes
#define NVIC_MPU_ATTR_SIZE_256K 0x00000022  // Region size 256 Kbytes
#define NVIC_MPU_ATTR_SIZE_512K 0x00000024  // Region size 512 Kbytes
#define NVIC_MPU_ATTR_SIZE_1M   0x00000026  // Region size 1 Mbytes
#define NVIC_MPU_ATTR_SIZE_2M   0x00000028  // Region size 2 Mbytes
#define NVIC_MPU_ATTR_SIZE_4M   0x0000002A  // Region size 4 Mbytes
#define NVIC_MPU_ATTR_SIZE_8M   0x0000002C  // Region size 8 Mbytes
#define NVIC_MPU_ATTR_SIZE_16M  0x0000002E  // Region size 16 Mbytes
#define NVIC_MPU_ATTR_SIZE_32M  0x00000030  // Region size 32 Mbytes
#define NVIC_MPU_ATTR_SIZE_64M  0x00000032  // Region size 64 Mbytes
#define NVIC_MPU_ATTR_SIZE_128M 0x00000034  // Region size 128 Mbytes
#define NVIC_MPU_ATTR_SIZE_256M 0x00000036  // Region size 256 Mbytes
#define NVIC_MPU_ATTR_SIZE_512M 0x00000038  // Region size 512 Mbytes
#define NVIC_MPU_ATTR_SIZE_1G   0x0000003A  // Region size 1 Gbytes
#define NVIC_MPU_ATTR_SIZE_2G   0x0000003C  // Region size 2 Gbytes
#define NVIC_MPU_ATTR_SIZE_4G   0x0000003E  // Region size 4 Gbytes
#define NVIC_MPU_ATTR_ENABLE    0x00000001  // Region enable

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_DBG_CTRL register.
//
//*****************************************************************************
#define NVIC_DBG_CTRL_DBGKEY_M  0xFFFF0000  // Debug key mask
#define NVIC_DBG_CTRL_DBGKEY    0xA05F0000  // Debug key
#define NVIC_DBG_CTRL_S_RESET_ST \
                                0x02000000  // Core has reset since last read
#define NVIC_DBG_CTRL_S_RETIRE_ST \
                                0x01000000  // Core has executed insruction
                                            // since last read
#define NVIC_DBG_CTRL_S_LOCKUP  0x00080000  // Core is locked up
#define NVIC_DBG_CTRL_S_SLEEP   0x00040000  // Core is sleeping
#define NVIC_DBG_CTRL_S_HALT    0x00020000  // Core status on halt
#define NVIC_DBG_CTRL_S_REGRDY  0x00010000  // Register read/write available
#define NVIC_DBG_CTRL_C_SNAPSTALL \
                                0x00000020  // Breaks a stalled load/store
#define NVIC_DBG_CTRL_C_MASKINT 0x00000008  // Mask interrupts when stepping
#define NVIC_DBG_CTRL_C_STEP    0x00000004  // Step the core
#define NVIC_DBG_CTRL_C_HALT    0x00000002  // Halt the core
#define NVIC_DBG_CTRL_C_DEBUGEN 0x00000001  // Enable debug

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_DBG_XFER register.
//
//*****************************************************************************
#define NVIC_DBG_XFER_REG_WNR   0x00010000  // Write or not read
#define NVIC_DBG_XFER_REG_SEL_M 0x0000001F  // Register
#define NVIC_DBG_XFER_REG_R0    0x00000000  // Register R0
#define NVIC_DBG_XFER_REG_R1    0x00000001  // Register R1
#define NVIC_DBG_XFER_REG_R2    0x00000002  // Register R2
#define NVIC_DBG_XFER_REG_R3    0x00000003  // Register R3
#define NVIC_DBG_XFER_REG_R4    0x00000004  // Register R4
#define NVIC_DBG_XFER_REG_R5    0x00000005  // Register R5
#define NVIC_DBG_XFER_REG_R6    0x00000006  // Register R6
#define NVIC_DBG_XFER_REG_R7    0x00000007  // Register R7
#define NVIC_DBG_XFER_REG_R8    0x00000008  // Register R8
#define NVIC_DBG_XFER_REG_R9    0x00000009  // Register R9
#define NVIC_DBG_XFER_REG_R10   0x0000000A  // Register R10
#define NVIC_DBG_XFER_REG_R11   0x0000000B  // Register R11
#define NVIC_DBG_XFER_REG_R12   0x0000000C  // Register R12
#define NVIC_DBG_XFER_REG_R13   0x0000000D  // Register R13
#define NVIC_DBG_XFER_REG_R14   0x0000000E  // Register R14
#define NVIC_DBG_XFER_REG_R15   0x0000000F  // Register R15
#define NVIC_DBG_XFER_REG_FLAGS 0x00000010  // xPSR/Flags register
#define NVIC_DBG_XFER_REG_MSP   0x00000011  // Main SP
#define NVIC_DBG_XFER_REG_PSP   0x00000012  // Process SP
#define NVIC_DBG_XFER_REG_DSP   0x00000013  // Deep SP
#define NVIC_DBG_XFER_REG_CFBP  0x00000014  // Control/Fault/BasePri/PriMask

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_DBG_DATA register.
//
//*****************************************************************************
#define NVIC_DBG_DATA_M         0xFFFFFFFF  // Data temporary cache
#define NVIC_DBG_DATA_S         0

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_DBG_INT register.
//
//*****************************************************************************
#define NVIC_DBG_INT_HARDERR    0x00000400  // Debug trap on hard fault
#define NVIC_DBG_INT_INTERR     0x00000200  // Debug trap on interrupt errors
#define NVIC_DBG_INT_BUSERR     0x00000100  // Debug trap on bus error
#define NVIC_DBG_INT_STATERR    0x00000080  // Debug trap on usage fault state
#define NVIC_DBG_INT_CHKERR     0x00000040  // Debug trap on usage fault check
#define NVIC_DBG_INT_NOCPERR    0x00000020  // Debug trap on coprocessor error
#define NVIC_DBG_INT_MMERR      0x00000010  // Debug trap on mem manage fault
#define NVIC_DBG_INT_RESET      0x00000008  // Core reset status
#define NVIC_DBG_INT_RSTPENDCLR 0x00000004  // Clear pending core reset
#define NVIC_DBG_INT_RSTPENDING 0x00000002  // Core reset is pending
#define NVIC_DBG_INT_RSTVCATCH  0x00000001  // Reset vector catch

//*****************************************************************************
//
// The following are defines for the bit fields in the NVIC_SW_TRIG register.
//
//*****************************************************************************
#define NVIC_SW_TRIG_INTID_M    0x000003FF  // Interrupt to trigger
#define NVIC_SW_TRIG_INTID_S    0

//*****************************************************************************
//
// The following definitions are deprecated.
//
//*****************************************************************************
#ifndef DEPRECATED

//*****************************************************************************
//
// Deprecated defines for the Watchdog
//
//*****************************************************************************
#define WATCHDOG_LOAD_R         (*((volatile unsigned long *)0x40000000))
#define WATCHDOG_VALUE_R        (*((volatile unsigned long *)0x40000004))
#define WATCHDOG_CTL_R          (*((volatile unsigned long *)0x40000008))
#define WATCHDOG_ICR_R          (*((volatile unsigned long *)0x4000000C))
#define WATCHDOG_RIS_R          (*((volatile unsigned long *)0x40000010))
#define WATCHDOG_MIS_R          (*((volatile unsigned long *)0x40000014))
#define WATCHDOG_TEST_R         (*((volatile unsigned long *)0x40000418))
#define WATCHDOG_LOCK_R         (*((volatile unsigned long *)0x40000C00))

//*****************************************************************************
//
// Deprecated defines for the bit fields in the I2C_O_SICR register.
//
//*****************************************************************************
#define I2C_SICR_IC             0x00000001  // Clear Interrupt

//*****************************************************************************
//
// Deprecated defines for the bit fields in the I2C_O_SMIS register.
//
//*****************************************************************************
#define I2C_SMIS_MIS            0x00000001  // Masked Interrupt Status

//*****************************************************************************
//
// Deprecated defines for the bit fields in the I2C_O_SRIS register.
//
//*****************************************************************************
#define I2C_SRIS_RIS            0x00000001  // Raw Interrupt Status

//*****************************************************************************
//
// Deprecated defines for the bit fields in the I2C_O_SIMR register.
//
//*****************************************************************************
#define I2C_SIMR_IM             0x00000001  // Interrupt Mask

//*****************************************************************************
//
// Deprecated defines for the bit fields in the the interpretation of the data
// in the SSFIFOx when the ADC TMLB is enabled. register.
//
//*****************************************************************************
#define ADC_TMLB_CNT_M          0x000003C0  // Continuous Sample Counter
#define ADC_TMLB_CONT           0x00000020  // Continuation Sample Indicator
#define ADC_TMLB_DIFF           0x00000010  // Differential Sample Indicator
#define ADC_TMLB_TS             0x00000008  // Temp Sensor Sample Indicator
#define ADC_TMLB_MUX_M          0x00000007  // Analog Input Indicator
#define ADC_TMLB_CNT_S          6           // Sample counter shift
#define ADC_TMLB_MUX_S          0           // Input channel number shift

//*****************************************************************************
//
// Deprecated defines for the ADC register offsets.
//
//*****************************************************************************
#define ADC_ACTSS_R             (*((volatile unsigned long *)0x40038000))
#define ADC_RIS_R               (*((volatile unsigned long *)0x40038004))
#define ADC_IM_R                (*((volatile unsigned long *)0x40038008))
#define ADC_ISC_R               (*((volatile unsigned long *)0x4003800C))
#define ADC_OSTAT_R             (*((volatile unsigned long *)0x40038010))
#define ADC_EMUX_R              (*((volatile unsigned long *)0x40038014))
#define ADC_USTAT_R             (*((volatile unsigned long *)0x40038018))
#define ADC_SSPRI_R             (*((volatile unsigned long *)0x40038020))
#define ADC_PSSI_R              (*((volatile unsigned long *)0x40038028))
#define ADC_SAC_R               (*((volatile unsigned long *)0x40038030))
#define ADC_SSMUX0_R            (*((volatile unsigned long *)0x40038040))
#define ADC_SSCTL0_R            (*((volatile unsigned long *)0x40038044))
#define ADC_SSFIFO0_R           (*((volatile unsigned long *)0x40038048))
#define ADC_SSFSTAT0_R          (*((volatile unsigned long *)0x4003804C))
#define ADC_SSMUX1_R            (*((volatile unsigned long *)0x40038060))
#define ADC_SSCTL1_R            (*((volatile unsigned long *)0x40038064))
#define ADC_SSFIFO1_R           (*((volatile unsigned long *)0x40038068))
#define ADC_SSFSTAT1_R          (*((volatile unsigned long *)0x4003806C))
#define ADC_SSMUX2_R            (*((volatile unsigned long *)0x40038080))
#define ADC_SSCTL2_R            (*((volatile unsigned long *)0x40038084))
#define ADC_SSFIFO2_R           (*((volatile unsigned long *)0x40038088))
#define ADC_SSFSTAT2_R          (*((volatile unsigned long *)0x4003808C))
#define ADC_SSMUX3_R            (*((volatile unsigned long *)0x400380A0))
#define ADC_SSCTL3_R            (*((volatile unsigned long *)0x400380A4))
#define ADC_SSFIFO3_R           (*((volatile unsigned long *)0x400380A8))
#define ADC_SSFSTAT3_R          (*((volatile unsigned long *)0x400380AC))
#define ADC_TMLB_R              (*((volatile unsigned long *)0x40038100))

//*****************************************************************************
//
// Deprecated defines for the bit fields in the FLASH_FMC register.
//
//*****************************************************************************
#define FLASH_FMC_WRKEY_M       0xFFFF0000  // Flash Memory Write Key
#define FLASH_FMC_WRKEY_S       16

//*****************************************************************************
//
// Deprecated defines for the bit fields in the SYSCTL_DID1 register.
//
//*****************************************************************************
#define SYSCTL_DID1_PKG_28SOIC  0x00000000  // SOIC package
#define SYSCTL_DID1_PKG_48QFP   0x00000008  // QFP package

//*****************************************************************************
//
// Deprecated defines for the NVIC register addresses.
//
//*****************************************************************************
#define NVIC_MPU_R              (*((volatile unsigned long *)0xE000ED9C))

#endif

#endif // __LM3S8962_H__
