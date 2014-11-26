/**************************************************************************//**
 * @file     system_M051Series.h
 * @version  V3.00
 * $Revision: 9 $
 * $Date: 14/01/28 10:49a $
 * @brief    M051 Series System Setting Header File
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef __SYSTEM_M051Series_H__
#define __SYSTEM_M051Series_H__

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------------------------------------*/
/* Macro Definition                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
#ifndef DEBUG_PORT
# define DEBUG_PORT      UART0       /*!< Select Debug Port which is used for retarget.c to output debug message to UART */
#endif

/**
 *
 * @details    This is used to enable PLL to speed up booting at startup. Remove it will cause system using
 *             default clock source (External crystal or internal 22.1184MHz IRC).
 *             Enable this option will casue system booting in 50MHz(By XTAL) or 50.1918MHz(By IRC22M) according to
 *             user configuration setting in CONFIG0
 *
 */
//#define INIT_SYSCLK_AT_BOOTING

/*----------------------------------------------------------------------------
  Define SYSCLK
 *----------------------------------------------------------------------------*/
#define __HXT       (12000000UL)    /*!< External Crystal Clock Frequency     */
#define __LIRC      (10000UL)       /*!< Internal 10K RC Oscillator Frequency */
#define __HIRC      (22118400UL)    /*!< Internal 22M RC Oscillator Frequency */
#define __HSI       (50000000UL)    /*!< PLL default output is 48MHz@12M X'tal */

extern uint32_t SystemCoreClock;    /*!< System Clock Frequency (Core Clock)  */
extern uint32_t CyclesPerUs;        /*!< Cycles per micro second              */
extern uint32_t PllClock;           /*!< PLL Output Clock Frequency           */

#if USE_ASSERT
/**
 * @brief      Assert Function
 *
 * @param[in]  expr  Expression to be evaluated
 *
 * @return     None
 *
 * @details    If the expression is false, an error message will be printed out
 *             from debug port (UART0 or UART1).
 */
#define ASSERT_PARAM(expr)  { if (!(expr)) { AssertError((uint8_t*)__FILE__, __LINE__); } }

void AssertError(uint8_t* file, uint32_t line);
#else
#define ASSERT_PARAM(expr)
#endif

#define assert_param(expr)  ASSERT_PARAM(expr)


/**
 * @brief    System Initializaiton
 *
 * @param    None
 *
 * @return   None
 *
 * @details  The necessary initializaiton of system.
 */
extern void SystemInit(void);


/**
 * @brief    Update the Variable SystemCoreClock
 *
 * @param    None
 *
 * @return   None
 *
 * @details  This function is used to update the variable SystemCoreClock
 *           and must be called whenever the core clock is changed.
 */
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif

/* Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved. */
