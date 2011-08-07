/*
** ###################################################################
**     Processor:           PK40X256VLQ100
**     Compilers:           ARM Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU ARM C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**     Reference manual:    K40P144M100SF2RM, Rev. 3, 4 Nov 2010
**     Version:             rev. 1.6, 2011-01-14
**
**     Abstract:
**         Provides a system configuration function and a global variable that contains the system frequency.
**         It configures the device and initializes the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright: 2011 Freescale Semiconductor, Inc. All Rights Reserved.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 0.1 (2010-09-29)
**         Initial version
**     - rev. 1.0 (2010-10-15)
**         First public version
**     - rev. 1.1 (2010-10-27)
**         Registers updated according to the new reference manual revision - Rev. 2, 15 Oct 2010
**         ADC - Peripheral register PGA bit definition has been fixed, bits PGALP, PGACHP removed.
**         CAN - Peripheral register MCR bit definition has been fixed, bit WAKSRC removed.
**         CRC - Peripheral register layout structure has been extended with 8/16-bit access to shadow registers.
**         CMP - Peripheral base address macro renamed from HSCMPx_BASE to CMPx_BASE.
**         CMP - Peripheral base pointer macro renamed from HSCMPx to CMPx.
**         DMA - Peripheral base address macro renamed from eDMA_BASE to DMA_BASE.
**         DMA - Peripheral base pointer macro renamed from eDMA to DMA.
**         GPIO - Port Output Enable Register (POER) has been renamed to Port Data Direction Register (PDDR), all POER related macros fixed to PDDR.
**         LCD - Peripheral base address macro renamed from SLCD_BASE to LCD_BASE.
**         LCD - Peripheral base pointer macro renamed from SLCD to LCD.
**         PDB - Peripheral register layout structure has been extended for Channel n and DAC n register array access (#MTWX44115).
**         RFSYS - System regfile registers have been added (#MTWX43999)
**         RFVBAT - VBAT  regfile registers have been added (#MTWX43999)
**         RTC - Peripheral register CR bit definition has been fixed, bit OTE removed.
**         TSI - Peripheral registers STATUS, SCANC bit definition have been fixed, bit groups CAPTRM, DELVOL and AMCLKDIV added.
**         USB - Peripheral base address macro renamed from USBOTG0_BASE to USB0_BASE.
**         USB - Peripheral base pointer macro renamed from USBOTG0 to USB0.
**         VREF - Peripheral register TRM removed.
**     - rev. 1.2 (2010-11-11)
**         Registers updated according to the new reference manual revision - Rev. 3, 4 Nov 2010
**         CAN - Individual Matching Element Update (IMEU) feature has been removed.
**         CAN - Peripheral register layout structure has been fixed, registers IMEUR, LRFR have been removed.
**         CAN - Peripheral register CTRL2 bit definition has been fixed, bits IMEUMASK, LOSTRMMSK, LOSTRLMSK, IMEUEN have been removed.
**         CAN - Peripheral register ESR2 bit definition has been fixed, bits IMEUF, LOSTRMF, LOSTRLF have been removed.
**         NV - Fixed offset address of BACKKEYx, FPROTx registers.
**         TSI - Peripheral register layout structure has been fixed, register WUCNTR has been removed.
**     - rev. 1.3 (2010-11-19)
**         CAN - Support for CAN0_IMEU_IRQn, CAN0_Lost_Rx_IRQn interrupts has been removed.
**         CAN - Support for CAN1_IMEU_IRQn, CAN1_Lost_Rx_IRQn interrupts has been removed.
**     - rev. 1.4 (2010-11-30)
**         EWM - Peripheral base address EWM_BASE definition has been fixed from 0x4005F000u to 0x40061000u (#MTWX44776).
**     - rev. 1.5 (2010-12-17)
**         AIPS0, AIPS1 - Fixed offset of PACRE-PACRP registers (#MTWX45259).
**     - rev. 1.6 (2011-01-14)
**         Added BITBAND_REG() macro to provide access to register bits using bit band region.
**
** ###################################################################
*/

/*! \file PK40X256VLQ100 */
/*! \version 1.6 */
/*! \date 2011-01-14 */
/*! \brief Device specific configuration file for PK40X256VLQ100 (header file) */
/*! \detailed Provides a system configuration function and a global variable that contains the system frequency.
      It configures the device and initializes the oscillator (PLL) that is part of the microcontroller device. */

#ifndef SYSTEM_PK40X256VLQ100_H_
#define SYSTEM_PK40X256VLQ100_H_                  /*!< Symbol preventing repeated inclusion */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*! \brief System clock frequency (core clock)
    \detailed The system clock frequency supplied to the SysTick timer and the processor core clock.
      This variable can be used by the user application to setup the SysTick timer or configure other parameters.
      It may also be used by debugger to query the frequency of the debug timer or configure the trace clock speed.
      SystemCoreClock is initialized with a correct predefined value. */
extern uint32_t SystemCoreClock;

/*! \brief Setup the microcontroller system.
    \detailed Typically this function configures the oscillator (PLL) that is part of the microcontroller device.
      For systems with variable clock speed it also updates the variable SystemCoreClock.
      SystemInit is called from startup_device file. */
void SystemInit (void);

/*! \brief Updates the SystemCoreClock variable.
    \detailed It must be called whenever the core clock is changed during program execution.
      SystemCoreClockUpdate() evaluates the clock register settings and calculates the current core clock. */
void SystemCoreClockUpdate (void);

#ifdef __cplusplus
}
#endif

#endif  /* #if !defined(SYSTEM_PK40X256VLQ100_H_) */
