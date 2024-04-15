/*********************************************************************************************************//**
 * @file    ht32_time.h
 * @version $Rev:: 6751         $
 * @date    $Date:: 2023-03-02 #$
 * @brief   The header file of time function.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32_TIME_H
#define __HT32_TIME_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#ifndef HTCFG_TIME_IPSEL
#include "ht32_time_conf.h"
#endif

/* Settings ------------------------------------------------------------------------------------------------*/
#ifdef HTCFG_TIME_IPSEL
#if (HTCFG_TIME_IPSEL == 0)
#define HTCFG_TIME_IPN    BFTM0
#endif
#if (HTCFG_TIME_IPSEL == 1)
#define HTCFG_TIME_IPN    BFTM1
#endif
#if (HTCFG_TIME_IPSEL == 2)
#define HTCFG_TIME_IPN    SCTM0
#endif
#if (HTCFG_TIME_IPSEL == 3)
#define HTCFG_TIME_IPN    SCTM1
#endif
#if (HTCFG_TIME_IPSEL == 4)
#define HTCFG_TIME_IPN    SCTM2
#endif
#if (HTCFG_TIME_IPSEL == 5)
#define HTCFG_TIME_IPN    SCTM3
#endif
#if (HTCFG_TIME_IPSEL == 6)
#define HTCFG_TIME_IPN    PWM0
#endif
#if (HTCFG_TIME_IPSEL == 7)
#define HTCFG_TIME_IPN    PWM1
#endif
#if (HTCFG_TIME_IPSEL == 8)
#define HTCFG_TIME_IPN    PWM2
#endif
#if (HTCFG_TIME_IPSEL == 9)
#define HTCFG_TIME_IPN    GPTM0
#endif
#if (HTCFG_TIME_IPSEL == 10)
#define HTCFG_TIME_IPN    GPTM1
#endif
#if (HTCFG_TIME_IPSEL == 11)
#define HTCFG_TIME_IPN    MCTM0
#endif
#endif

/* Exported constants --------------------------------------------------------------------------------------*/
#ifndef IS_IPN_BFTM
#undef IPN_MCTM0
#undef IPN_MCTM1
#undef IPN_GPTM0
#undef IPN_GPTM1

#define IPN_NULL                        (0)
#define IPN_MCTM0                       (0x4002C000)
#define IPN_MCTM1                       (0x4002D000)
#define IPN_GPTM0                       (0x4006E000)
#define IPN_GPTM1                       (0x4006F000)
#define IPN_SCTM0                       (0x40034000)
#define IPN_SCTM1                       (0x40074000)
#define IPN_SCTM2                       (0x40035000)
#define IPN_SCTM3                       (0x40075000)
#define IPN_PWM0                        (0x40031000)
#define IPN_PWM1                        (0x40071000)
#define IPN_PWM2                        (0x40031000)
#define IPN_BFTM0                       (0x40076000)
#define IPN_BFTM1                       (0x40077000)
#define IPN_CHECK(IP)                   STRCAT2(IPN_, IP)
#define IS_IPN_BFTM(IP)                 (IPN_CHECK(IP) == IPN_BFTM0) || (IPN_CHECK(IP) == IPN_BFTM1)
#define IS_IPN_MCTM(IP)                 (IPN_CHECK(IP) == IPN_MCTM0) || (IPN_CHECK(IP) == IPN_MCTM1)
#define IS_IPN_GPTM(IP)                 (IPN_CHECK(IP) == IPN_GPTM0) || (IPN_CHECK(IP) == IPN_GPTM1)
#define IS_IPN_SCTM(IP)                 (IPN_CHECK(IP) == IPN_SCTM0) || (IPN_CHECK(IP) == IPN_SCTM1) || (IPN_CHECK(IP) == IPN_SCTM2) || (IPN_CHECK(IP) == IPN_SCTM3)
#define IS_IPN_PWM(IP)                  (IPN_CHECK(IP) == IPN_PWM0) || (IPN_CHECK(IP) == IPN_PWM1) || (IPN_CHECK(IP) == IPN_PWM2)
#define IS_IPN_TM(IP)                   (IS_IPN_MCTM(IP) || IS_IPN_GPTM(IP) || IS_IPN_SCTM(IP) || IS_IPN_PWM(IP))
#endif

#define _HTCFG_TIME_PORT                          STRCAT2(HT_, HTCFG_TIME_IPN)

#if (HTCFG_TIME_CLKSEL == 0)
#define _HTCFG_TIME_CORECLK                       (LIBCFG_MAX_SPEED)
#else
#define _HTCFG_TIME_CORECLK                       (HTCFG_TIME_CLK_MANUAL)
#endif

#if (LIBCFG_CKCU_NO_APB_PRESCALER == 1)
#undef HTCFG_TIME_PCLK_DIV
#define HTCFG_TIME_PCLK_DIV                       (0)
#endif

#define HTCFG_TIME_CLKSRC                         (_HTCFG_TIME_CORECLK >> HTCFG_TIME_PCLK_DIV)

#if (IS_IPN_BFTM(HTCFG_TIME_IPN))
#undef HTCFG_TIME_TICKHZ
#define HTCFG_TIME_TICKHZ                         HTCFG_TIME_CLKSRC
#endif

/* Exported macro ------------------------------------------------------------------------------------------*/
#define TIME_TICKDIFF(start, current)             ((current >= start) ? (u32)(current - start) : (u32)(0xFFFFFFFF - start + 1 + current))

#if (HTCFG_TIME_TICKHZ < 1000000)
#define TIME_US2TICK(us)                          (us / (1000000UL / HTCFG_TIME_TICKHZ))
#define TIME_TICK2US(t)                           (t * (1000000UL / HTCFG_TIME_TICKHZ))
#else
#define TIME_US2TICK(us)                          (us * (HTCFG_TIME_TICKHZ / 1000000UL))
#define TIME_TICK2US(t)                           (t / (HTCFG_TIME_TICKHZ / 1000000UL))
#endif

#if (HTCFG_TIME_TICKHZ < 1000)
#define TIME_MS2TICK(ms)                          (ms / (1000UL / HTCFG_TIME_TICKHZ))
#define TIME_TICK2MS(t)                           (t * (1000UL / HTCFG_TIME_TICKHZ))
#else
#define TIME_MS2TICK(ms)                          (ms * (HTCFG_TIME_TICKHZ / 1000UL))
#define TIME_TICK2MS(t)                           (t / (HTCFG_TIME_TICKHZ / 1000UL))
#endif

#define TIME_S2TICK(s)                            (s * (u32)(HTCFG_TIME_TICKHZ))
#define TIME_TICK2S(t)                            (t / (HTCFG_TIME_TICKHZ))


#define GET_CNT()                                 (_HTCFG_TIME_PORT->CNTR)

/* Exported functions --------------------------------------------------------------------------------------*/
void Time_Init(void);
void Time_Delay(u32 delay);
u32 Time_GetTick(void);

#if (IS_IPN_BFTM(HTCFG_TIME_IPN))
// BFTM
#define Time_GetTick    GET_CNT
#endif

#ifdef __cplusplus
}
#endif

#endif
