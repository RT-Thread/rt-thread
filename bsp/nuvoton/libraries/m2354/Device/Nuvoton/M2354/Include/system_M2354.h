/**************************************************************************//**
 * @file     system_M2354.h
 * @version  V3.00
 * @brief    System Setting Header File
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __SYSTEM_M2354_H__
#define __SYSTEM_M2354_H__

#ifdef __cplusplus
extern "C" {
#endif
/*---------------------------------------------------------------------------------------------------------*/
/* Macro Definition                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
#ifndef DEBUG_PORT
# define DEBUG_PORT      UART0       /*!< Select Debug Port which is used for retarget.c to output debug message to UART */
#endif


/* Init ETM Interface Multi-function Pins */
#define ETM_INIT()  { \
    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC0MFP_ETM_TRACE_Msk | SYS_GPC_MFPL_PC1MFP_ETM_TRACE_Msk | \
    SYS_GPC_MFPL_PC2MFP_ETM_TRACE_Msk | SYS_GPC_MFPL_PC3MFP_ETM_TRACE_Msk | \
                     SYS_GPC_MFPL_PC4MFP_ETM_TRACE_Msk); \
    SYS->GPC_MFPL |= SYS_GPC_MFPL_PC0MFP_ETM_TRACE_CLK | SYS_GPC_MFPL_PC1MFP_ETM_TRACE_DATA0 | \
                     SYS_GPC_MFPL_PC2MFP_ETM_TRACE_DATA1 | SYS_GPC_MFPL_PC3MFP_ETM_TRACE_DATA2 | \
                     SYS_GPC_MFPL_PC4MFP_ETM_TRACE_DATA3;}





/**
 *
 * @details    This is used to enable PLL to speed up booting at startup. Remove it will cause system using
 *             default clock source (External crystal or internal 22.1184MHz IRC).
 *             Enable this option will cause system booting in 72MHz(By XTAL) or 71.8848MHz(By IRC22M) according to
 *             user configuration setting in CONFIG0
 *
 */

/*
#define INIT_SYSCLK_AT_BOOTING
*/

/*----------------------------------------------------------------------------
  Define SYSCLK
 *----------------------------------------------------------------------------*/
#define __HXT       (12000000UL)    /*!< External Crystal Clock Frequency     */
#define __LIRC      (32000UL)       /*!< Internal 32K RC Oscillator Frequency */
#define __HIRC      (12000000UL)    /*!< Internal 12M RC Oscillator Frequency */
#define __LXT       (32768UL)       /*!< External Crystal Clock Frequency 32.768KHz */
#define __HSI       (48000000UL)    /*!< PLL Output Clock Frequency */
#define __HIRC48    (48000000UL)    /*!< Internal 48M RC Oscillator Frequency */
#define __LIRC32    (32000UL)       /*!< Internal 32K RC Oscillator Frequency */
#define __MIRC      (4000000UL)     /*!< Internal 4M RC Oscillator Frequency */


#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3L)
# if defined (__ICCARM__)
#  define __NONSECURE_ENTRY       __cmse_nonsecure_entry
#  define __NONSECURE_ENTRY_WEAK  __cmse_nonsecure_entry //__weak
#  define __NONSECURE_CALL        __cmse_nonsecure_call
# else
#  define __NONSECURE_ENTRY       __attribute__((cmse_nonsecure_entry))
#  define __NONSECURE_ENTRY_WEAK  __attribute__((cmse_nonsecure_entry,weak))
#  define __NONSECURE_CALL        __attribute__((cmse_nonsecure_call))
# endif
#else
# define __NONSECURE_ENTRY
# define __NONSECURE_ENTRY_WEAK
# define __NONSECURE_CALL
#endif



extern uint32_t SystemCoreClock;    /*!< System Clock Frequency (Core Clock)  */
extern uint32_t CyclesPerUs;        /*!< Cycles per micro second              */
extern uint32_t PllClock;           /*!< PLL Output Clock Frequency           */
extern uint32_t __PC(void);         /*!< Return the current program counter value */

#if USE_ASSERT
/**
 * @brief      Assert Function
 *
 * @param[in]  expr  Expression to be evaluated
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
 * @brief    System Initialization
 *
 * @details  The necessary initialization of system.
 */
extern void SystemInit(void);


/**
 * @brief    Update the Variable SystemCoreClock
 *
 * @details  This function is used to update the variable SystemCoreClock
 *           and must be called whenever the core clock is changed.
 */
extern void SystemCoreClockUpdate(void);




#if (defined(__ICCARM__) && (__VER__ >= 7080000) && (__VER__ < 8020000))
uint32_t __TZ_get_PSP_NS(void);
void __TZ_set_PSP_NS(uint32_t topOfProcStack);
int32_t __TZ_get_MSP_NS(void);
void __TZ_set_MSP_NS(uint32_t topOfMainStack);
uint32_t __TZ_get_PRIMASK_NS(void);
void __TZ_set_PRIMASK_NS(uint32_t priMask);
#endif



#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_M2354_H__ */
