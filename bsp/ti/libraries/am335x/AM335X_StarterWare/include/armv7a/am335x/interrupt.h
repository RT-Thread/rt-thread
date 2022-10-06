/**
 *  \file   interrupt.h
 *
 *  \brief  Interrupt related API declarations.
 *
 *   This file contains the API prototypes for configuring INTC for 
 *   ARM Cortex-A8
*/

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "hw_intc.h"
#include "hw_types.h"

#ifdef __cplusplus
extern "C" {
#endif
/****************************************************************************
**                       MACRO DEFINITIONS
****************************************************************************/
/*
** Macros which can be passed to IntPrioritySet API as hostIntRoute.
*/
/* To route an interrupt to IRQ */
#define AINTC_HOSTINT_ROUTE_IRQ                (0)

/* To route an interrupt to FIQ */
#define AINTC_HOSTINT_ROUTE_FIQ                (INTC_ILR_FIQNIRQ)

/*
** Interrupt number list
*/
#define SYS_INT_EMUINT                         (0)
#define SYS_INT_COMMTX                         (1)
#define SYS_INT_COMMRX                         (2)
#define SYS_INT_BENCH                          (3)
#define SYS_INT_ELM_IRQ                        (4)
#define SYS_INT_SSM_WFI_IRQ                    (5)
#define SYS_INT_SSM_IRQ                        (6)
#define SYS_INT_NMI                            (7)
#define SYS_INT_SEC_EVNT                       (8)
#define SYS_INT_L3DEBUG                        (9)
#define SYS_INT_L3APPINT                       (10)
#define SYS_INT_PRCMINT                        (11)
#define SYS_INT_EDMACOMPINT                    (12)
#define SYS_INT_EDMAMPERR                      (13)
#define SYS_INT_EDMAERRINT                     (14)
#define SYS_INT_WDT0INT                        (15)
#define SYS_INT_ADC_TSC_GENINT                 (16)
#define SYS_INT_USBSSINT                       (17)
#define SYS_INT_USB0                           (18)
#define SYS_INT_USB1                           (19)
#define SYS_INT_PRUSS1_EVTOUT0                 (20)
#define SYS_INT_PRUSS1_EVTOUT1                 (21)
#define SYS_INT_PRUSS1_EVTOUT2                 (22)
#define SYS_INT_PRUSS1_EVTOUT3                 (23)
#define SYS_INT_PRUSS1_EVTOUT4                 (24)
#define SYS_INT_PRUSS1_EVTOUT5                 (25)
#define SYS_INT_PRUSS1_EVTOUT6                 (26)
#define SYS_INT_PRUSS1_EVTOUT7                 (27)
#define SYS_INT_MMCSD1INT                      (28)
#define SYS_INT_MMCSD2INT                      (29)
#define SYS_INT_I2C2INT                        (30)
#define SYS_INT_eCAP0INT                       (31)
#define SYS_INT_GPIOINT2A                      (32)
#define SYS_INT_GPIOINT2B                      (33)
#define SYS_INT_USBWAKEUP                      (34)
#define SYS_INT_LCDCINT                        (36)
#define SYS_INT_GFXINT                         (37)
#define SYS_INT_2DHWAINT                       (38)
#define SYS_INT_ePWM2INT                       (39)
#define SYS_INT_3PGSWRXTHR0                    (40)
#define SYS_INT_3PGSWRXINT0                    (41)
#define SYS_INT_3PGSWTXINT0                    (42)
#define SYS_INT_3PGSWMISC0                     (43)
#define SYS_INT_UART3INT                       (44)
#define SYS_INT_UART4INT                       (45)
#define SYS_INT_UART5INT                       (46)
#define SYS_INT_eCAP1INT                       (47)
#define SYS_INT_DCAN0_INT0                     (52)
#define SYS_INT_DCAN0_INT1                     (53)
#define SYS_INT_DCAN0_PARITY                   (54)
#define SYS_INT_DCAN1_INT0                     (55)
#define SYS_INT_DCAN1_INT1                     (56)
#define SYS_INT_DCAN1_PARITY                   (57)
#define SYS_INT_ePWM0_TZINT                    (58)
#define SYS_INT_ePWM1_TZINT                    (59)
#define SYS_INT_ePWM2_TZINT                    (60)
#define SYS_INT_eCAP2INT                       (61)
#define SYS_INT_GPIOINT3A                      (62)
#define SYS_INT_GPIOINT3B                      (63)
#define SYS_INT_MMCSD0INT                      (64)
#define SYS_INT_SPI0INT                        (65)
#define SYS_INT_TINT0                          (66)
#define SYS_INT_TINT1_1MS                      (67)
#define SYS_INT_TINT2                          (68)
#define SYS_INT_TINT3                          (69)
#define SYS_INT_I2C0INT                        (70)
#define SYS_INT_I2C1INT                        (71)
#define SYS_INT_UART0INT                       (72)
#define SYS_INT_UART1INT                       (73)
#define SYS_INT_UART2INT                       (74)
#define SYS_INT_RTCINT                         (75)
#define SYS_INT_RTCALARMINT                    (76)
#define SYS_INT_MBINT0                         (77)
#define SYS_INT_M3_TXEV                        (78)
#define SYS_INT_eQEP0INT                       (79)
#define SYS_INT_MCATXINT0                      (80)
#define SYS_INT_MCARXINT0                      (81)
#define SYS_INT_MCATXINT1                      (82)
#define SYS_INT_MCARXINT1                      (83)
#define SYS_INT_ePWM0INT                       (86)
#define SYS_INT_ePWM1INT                       (87)
#define SYS_INT_eQEP1INT                       (88)
#define SYS_INT_eQEP2INT                       (89)
#define SYS_INT_DMA_INTR_PIN2                  (90)
#define SYS_INT_WDT1INT                        (91)
#define SYS_INT_TINT4                          (92)
#define SYS_INT_TINT5                          (93)
#define SYS_INT_TINT6                          (94)
#define SYS_INT_TINT7                          (95)
#define SYS_INT_GPIOINT0A                      (96)
#define SYS_INT_GPIOINT0B                      (97)
#define SYS_INT_GPIOINT1A                      (98)
#define SYS_INT_GPIOINT1B                      (99)
#define SYS_INT_GPMCINT                        (100)
#define SYS_INT_DDRERR0                        (101)
#define SYS_INT_AES0_IRQ_S                     (102)
#define SYS_INT_AES0_IRQ_P                     (103)
#define SYS_INT_SHA_IRQ_S                      (108)
#define SYS_INT_SHA_IRQ_P                      (109)
#define SYS_INT_FPKA_SINTREQUEST_S             (110)
#define SYS_INT_RNG_IRQ                        (111)
#define SYS_INT_TCERRINT0                      (112)
#define SYS_INT_TCERRINT1                      (113)
#define SYS_INT_TCERRINT2                      (114)
#define SYS_INT_SMRFLX_Sabertooth              (120)
#define SYS_INT_SMRFLX_Core                    (121)
#define SYS_INT_DMA_INTR_PIN0                  (123)
#define SYS_INT_DMA_INTR_PIN1                  (124)
#define SYS_INT_SPI1INT                        (125)

/*****************************************************************************
**                     API FUNCTION PROTOTYPES
*****************************************************************************/
extern void IntAINTCInit (void);
extern void IntIfClkFreeRunSet(void);
extern void IntIfClkAutoGateSet(void);
extern void IntProtectionEnable(void);
extern void IntProtectionDisable(void);
extern void IntSyncClkFreeRunSet(void);
extern void IntSyncClkAutoGateSet(void);
extern void IntFuncClkFreeRunSet(void);
extern void IntFuncClkAutoGateSet(void);
extern void IntPriorityThresholdSet(unsigned int threshold);
extern void IntSoftwareIntSet(unsigned int intrNum);
extern void IntSoftwareIntClear(unsigned int intrNum);
extern void IntMasterIRQEnable(void);
extern void IntMasterIRQDisable(void);
extern void IntMasterFIQEnable(void);
extern void IntMasterFIQDisable(void);
extern void IntSystemEnable(unsigned int intrNum);
extern void IntSystemDisable(unsigned int intrNum);
extern void IntUnRegister(unsigned int intrNum);
extern void IntEnable(unsigned char  status);
extern void IntRegister(unsigned int intrNum, void (*pfnHandler)(void));
extern void IntPrioritySet(unsigned int intrNum, unsigned int priority,
                           unsigned int hostIntRoute);
extern unsigned char IntDisable(void);
extern unsigned int IntMasterStatusGet(void);
extern unsigned int IntActiveIrqNumGet(void);
extern unsigned int IntActiveFiqNumGet(void);
extern unsigned int IntSpurIrqFlagGet(void);
extern unsigned int IntSpurFiqFlagGet(void);
extern unsigned int IntCurrIrqPriorityGet(void);
extern unsigned int IntCurrFiqPriorityGet(void);
extern unsigned int IntPriorityThresholdGet(void);
extern unsigned int IntRawStatusGet(unsigned int intrNum);
extern unsigned int IntPendingIrqMaskedStatusGet(unsigned int intrNum);
extern unsigned int IntPendingFiqMaskedStatusGet(unsigned int intrNum);

#ifdef __cplusplus
}
#endif
#endif

