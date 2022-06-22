/*******************************************************************************
 * (c) Copyright 2012-2013 Microsemi SoC Products Group. All rights reserved.
 * 
 *  SmartFusion2 CMSIS system initialization.
 *
 * SVN $Revision: 5280 $
 * SVN $Date: 2013-03-22 20:51:50 +0000 (Fri, 22 Mar 2013) $
 */

#ifndef SYSTEM_M2SXXX_H
#define SYSTEM_M2SXXX_H

#ifdef __cplusplus
extern "C" {
#endif 

/* Standard CMSIS global variables. */
extern uint32_t SystemCoreClock;    /*!< System Clock Frequency (Core Clock) */

/* SmartFusion2 specific clocks. */
extern uint32_t g_FrequencyPCLK0;   /*!< Clock frequency of APB bus 0. */  
extern uint32_t g_FrequencyPCLK1;   /*!< Clock frequency of APB bus 1. */
extern uint32_t g_FrequencyPCLK2;   /*!< Clock frequency of APB bus 2. */
extern uint32_t g_FrequencyFIC0;    /*!< Clock frequecny of FPGA fabric interface controller 1. */
extern uint32_t g_FrequencyFIC1;    /*!< Clock frequecny of FPGA fabric inteface controller 2. */
extern uint32_t g_FrequencyFIC64;   /*!< Clock frequecny of 64-bit FPGA fabric interface controller. */


/***************************************************************************//**
 * The SystemInit() is a standard CMSIS function called during system startup.
 * It is meant to perform low level hardware setup such as configuring DDR and
 * SERDES controllers.
 */
void SystemInit(void);

/***************************************************************************//**
 * The SystemCoreClockUpdate() is a standard CMSIS function which can be called
 * by the application in order to ensure that the SystemCoreClock global
 * variable contains the up to date Cortex-M3 core frequency. Calling this
 * function also updates the global variables containing the frequencies of the
 * APB busses connecting the peripherals.
 */
void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif
