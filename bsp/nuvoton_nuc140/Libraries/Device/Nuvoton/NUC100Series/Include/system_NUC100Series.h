/**************************************************************************//**
 * @file     system_NUC100Series.h
 * @version  V3.0
 * $Revision: 1 $
 * $Date: 14/12/08 11:47a $
 * @brief    NUC100 Series CMSIS System Header File
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef __SYSTEM_NUC2xx_H
#define __SYSTEM_NUC2xx_H

#ifdef __cplusplus
extern "C" {
#endif
/*---------------------------------------------------------------------------------------------------------*/
/* Macro Definition                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/

/* Using UART0 or UART1 */
#define DEBUG_PORT   UART0

/*----------------------------------------------------------------------------
  Define SYSCLK
 *----------------------------------------------------------------------------*/
#define __HXT       (12000000UL)    /*!< External Crystal Clock Frequency     */
#define __LXT       (32768UL)       /*!< External Crystal Clock Frequency 32.768KHz */
#define __HIRC      (22118400UL)    /*!< Internal 22M RC Oscillator Frequency */
#define __LIRC      (10000UL)       /*!< Internal 10K RC Oscillator Frequency */
#define __HSI       (50000000UL)    /*!< PLL default output is 50MHz */

extern uint32_t SystemCoreClock;    /*!< System Clock Frequency (Core Clock) */
extern uint32_t CyclesPerUs;        /*!< Cycles per micro second              */
extern uint32_t PllClock;           /*!< PLL Output Clock Frequency           */

/**
 * Initialize the system
 *
 * @param  None
 * @return None
 *
 * @brief  Setup the microcontroller system
 *         Initialize GPIO directions and values
 */
extern void SystemInit(void);


/**
 * Update SystemCoreClock variable
 *
 * @param  None
 * @return None
 *
 * @brief  Updates the SystemCoreClock with current core Clock
 *         retrieved from CPU registers.
 */
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif
