/*
** ###################################################################
**     Processors:          MIMXRT1171AVM8A
**                          MIMXRT1171AVM8B
**                          MIMXRT1171CVM8A
**                          MIMXRT1171CVM8B
**                          MIMXRT1171DVMAA
**                          MIMXRT1171DVMAB
**                          MIMXRT1172AVM8A
**                          MIMXRT1172AVM8B
**                          MIMXRT1172CVM8A
**                          MIMXRT1172CVM8B
**                          MIMXRT1172DVMAA
**                          MIMXRT1172DVMAB
**                          MIMXRT1173CVM8A_cm4
**                          MIMXRT1173CVM8A_cm7
**                          MIMXRT1173CVM8B_cm4
**                          MIMXRT1173CVM8B_cm7
**                          MIMXRT1175AVM8A_cm4
**                          MIMXRT1175AVM8A_cm7
**                          MIMXRT1175AVM8B_cm4
**                          MIMXRT1175AVM8B_cm7
**                          MIMXRT1175CVM8A_cm4
**                          MIMXRT1175CVM8A_cm7
**                          MIMXRT1175CVM8B_cm4
**                          MIMXRT1175CVM8B_cm7
**                          MIMXRT1175DVMAA_cm4
**                          MIMXRT1175DVMAA_cm7
**                          MIMXRT1175DVMAB_cm4
**                          MIMXRT1175DVMAB_cm7
**                          MIMXRT1176AVM8A_cm4
**                          MIMXRT1176AVM8A_cm7
**                          MIMXRT1176AVM8B_cm4
**                          MIMXRT1176AVM8B_cm7
**                          MIMXRT1176CVM8A_cm4
**                          MIMXRT1176CVM8A_cm7
**                          MIMXRT1176CVM8B_cm4
**                          MIMXRT1176CVM8B_cm7
**                          MIMXRT1176DVMAA_cm4
**                          MIMXRT1176DVMAA_cm7
**                          MIMXRT1176DVMAB_cm4
**                          MIMXRT1176DVMAB_cm7
**                          MIMXRT117HAVM8A_cm4
**                          MIMXRT117HAVM8A_cm7
**                          MIMXRT117HAVM8B_cm4
**                          MIMXRT117HAVM8B_cm7
**                          MIMXRT117HCVM8A_cm4
**                          MIMXRT117HCVM8A_cm7
**                          MIMXRT117HCVM8B_cm4
**                          MIMXRT117HCVM8B_cm7
**                          MIMXRT117HDVMAA_cm4
**                          MIMXRT117HDVMAA_cm7
**                          MIMXRT117HDVMAB_cm4
**                          MIMXRT117HDVMAB_cm7
**
**     Version:             rev. 2.0, 2024-10-29
**     Build:               b250520
**
**     Abstract:
**         CMSIS Peripheral Access Layer for RTWDOG
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2025 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 0.1 (2018-03-05)
**         Initial version.
**     - rev. 1.0 (2020-12-29)
**         Update header files to align with IMXRT1170RM Rev.0.
**     - rev. 2.0 (2024-10-29)
**         Change the device header file from single flat file to multiple files based on peripherals,
**         each peripheral with dedicated header file located in periphN folder.
**
** ###################################################################
*/

/*!
 * @file PERI_RTWDOG.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for RTWDOG
 *
 * CMSIS Peripheral Access Layer for RTWDOG
 */

#if !defined(PERI_RTWDOG_H_)
#define PERI_RTWDOG_H_                           /**< Symbol preventing repeated inclusion */

#if (defined(CPU_MIMXRT1171AVM8A) || defined(CPU_MIMXRT1171AVM8B) || defined(CPU_MIMXRT1171CVM8A) || defined(CPU_MIMXRT1171CVM8B) || defined(CPU_MIMXRT1171DVMAA) || defined(CPU_MIMXRT1171DVMAB))
#include "MIMXRT1171_COMMON.h"
#elif (defined(CPU_MIMXRT1172AVM8A) || defined(CPU_MIMXRT1172AVM8B) || defined(CPU_MIMXRT1172CVM8A) || defined(CPU_MIMXRT1172CVM8B) || defined(CPU_MIMXRT1172DVMAA) || defined(CPU_MIMXRT1172DVMAB))
#include "MIMXRT1172_COMMON.h"
#elif (defined(CPU_MIMXRT1173CVM8A_cm4) || defined(CPU_MIMXRT1173CVM8B_cm4))
#include "MIMXRT1173_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1173CVM8A_cm7) || defined(CPU_MIMXRT1173CVM8B_cm7))
#include "MIMXRT1173_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT1175AVM8A_cm4) || defined(CPU_MIMXRT1175AVM8B_cm4) || defined(CPU_MIMXRT1175CVM8A_cm4) || defined(CPU_MIMXRT1175CVM8B_cm4) || defined(CPU_MIMXRT1175DVMAA_cm4) || defined(CPU_MIMXRT1175DVMAB_cm4))
#include "MIMXRT1175_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1175AVM8A_cm7) || defined(CPU_MIMXRT1175AVM8B_cm7) || defined(CPU_MIMXRT1175CVM8A_cm7) || defined(CPU_MIMXRT1175CVM8B_cm7) || defined(CPU_MIMXRT1175DVMAA_cm7) || defined(CPU_MIMXRT1175DVMAB_cm7))
#include "MIMXRT1175_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT1176AVM8A_cm4) || defined(CPU_MIMXRT1176AVM8B_cm4) || defined(CPU_MIMXRT1176CVM8A_cm4) || defined(CPU_MIMXRT1176CVM8B_cm4) || defined(CPU_MIMXRT1176DVMAA_cm4) || defined(CPU_MIMXRT1176DVMAB_cm4))
#include "MIMXRT1176_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1176AVM8A_cm7) || defined(CPU_MIMXRT1176AVM8B_cm7) || defined(CPU_MIMXRT1176CVM8A_cm7) || defined(CPU_MIMXRT1176CVM8B_cm7) || defined(CPU_MIMXRT1176DVMAA_cm7) || defined(CPU_MIMXRT1176DVMAB_cm7))
#include "MIMXRT1176_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT117HAVM8A_cm4) || defined(CPU_MIMXRT117HAVM8B_cm4) || defined(CPU_MIMXRT117HCVM8A_cm4) || defined(CPU_MIMXRT117HCVM8B_cm4) || defined(CPU_MIMXRT117HDVMAA_cm4) || defined(CPU_MIMXRT117HDVMAB_cm4))
#include "MIMXRT117H_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT117HAVM8A_cm7) || defined(CPU_MIMXRT117HAVM8B_cm7) || defined(CPU_MIMXRT117HCVM8A_cm7) || defined(CPU_MIMXRT117HCVM8B_cm7) || defined(CPU_MIMXRT117HDVMAA_cm7) || defined(CPU_MIMXRT117HDVMAB_cm7))
#include "MIMXRT117H_cm7_COMMON.h"
#else
  #error "No valid CPU defined!"
#endif

/* ----------------------------------------------------------------------------
   -- Device Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_access_layer Device Peripheral Access Layer
 * @{
 */


/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic push
  #else
    #pragma push
    #pragma anon_unions
  #endif
#elif defined(__CWCC__)
  #pragma push
  #pragma cpp_extensions on
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/* ----------------------------------------------------------------------------
   -- RTWDOG Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTWDOG_Peripheral_Access_Layer RTWDOG Peripheral Access Layer
 * @{
 */

/** RTWDOG - Register Layout Typedef */
typedef struct {
  __IO uint32_t CS;                                /**< Watchdog Control and Status Register, offset: 0x0 */
  __IO uint32_t CNT;                               /**< Watchdog Counter Register, offset: 0x4 */
  __IO uint32_t TOVAL;                             /**< Watchdog Timeout Value Register, offset: 0x8 */
  __IO uint32_t WIN;                               /**< Watchdog Window Register, offset: 0xC */
} RTWDOG_Type;

/* ----------------------------------------------------------------------------
   -- RTWDOG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTWDOG_Register_Masks RTWDOG Register Masks
 * @{
 */

/*! @name CS - Watchdog Control and Status Register */
/*! @{ */

#define RTWDOG_CS_STOP_MASK                      (0x1U)
#define RTWDOG_CS_STOP_SHIFT                     (0U)
/*! STOP - Stop Enable
 *  0b0..Watchdog disabled in chip stop mode.
 *  0b1..Watchdog enabled in chip stop mode.
 */
#define RTWDOG_CS_STOP(x)                        (((uint32_t)(((uint32_t)(x)) << RTWDOG_CS_STOP_SHIFT)) & RTWDOG_CS_STOP_MASK)

#define RTWDOG_CS_WAIT_MASK                      (0x2U)
#define RTWDOG_CS_WAIT_SHIFT                     (1U)
/*! WAIT - Wait Enable
 *  0b0..Watchdog disabled in chip wait mode.
 *  0b1..Watchdog enabled in chip wait mode.
 */
#define RTWDOG_CS_WAIT(x)                        (((uint32_t)(((uint32_t)(x)) << RTWDOG_CS_WAIT_SHIFT)) & RTWDOG_CS_WAIT_MASK)

#define RTWDOG_CS_DBG_MASK                       (0x4U)
#define RTWDOG_CS_DBG_SHIFT                      (2U)
/*! DBG - Debug Enable
 *  0b0..Watchdog disabled in chip debug mode.
 *  0b1..Watchdog enabled in chip debug mode.
 */
#define RTWDOG_CS_DBG(x)                         (((uint32_t)(((uint32_t)(x)) << RTWDOG_CS_DBG_SHIFT)) & RTWDOG_CS_DBG_MASK)

#define RTWDOG_CS_TST_MASK                       (0x18U)
#define RTWDOG_CS_TST_SHIFT                      (3U)
/*! TST - Watchdog Test
 *  0b00..Watchdog test mode disabled.
 *  0b01..Watchdog user mode enabled. (Watchdog test mode disabled.) After testing the watchdog, software should
 *        use this setting to indicate that the watchdog is functioning normally in user mode.
 *  0b10..Watchdog test mode enabled, only the low byte is used. CNT[CNTLOW] is compared with TOVAL[TOVALLOW].
 *  0b11..Watchdog test mode enabled, only the high byte is used. CNT[CNTHIGH] is compared with TOVAL[TOVALHIGH].
 */
#define RTWDOG_CS_TST(x)                         (((uint32_t)(((uint32_t)(x)) << RTWDOG_CS_TST_SHIFT)) & RTWDOG_CS_TST_MASK)

#define RTWDOG_CS_UPDATE_MASK                    (0x20U)
#define RTWDOG_CS_UPDATE_SHIFT                   (5U)
/*! UPDATE - Allow updates
 *  0b0..Updates not allowed. After the initial configuration, the watchdog cannot be later modified without forcing a reset.
 *  0b1..Updates allowed. Software can modify the watchdog configuration registers within 255 bus clocks after performing the unlock write sequence.
 */
#define RTWDOG_CS_UPDATE(x)                      (((uint32_t)(((uint32_t)(x)) << RTWDOG_CS_UPDATE_SHIFT)) & RTWDOG_CS_UPDATE_MASK)

#define RTWDOG_CS_INT_MASK                       (0x40U)
#define RTWDOG_CS_INT_SHIFT                      (6U)
/*! INT - Watchdog Interrupt
 *  0b0..Watchdog interrupts are disabled. Watchdog resets are not delayed.
 *  0b1..Watchdog interrupts are enabled. Watchdog resets are delayed by 255 bus clocks from the interrupt vector fetch.
 */
#define RTWDOG_CS_INT(x)                         (((uint32_t)(((uint32_t)(x)) << RTWDOG_CS_INT_SHIFT)) & RTWDOG_CS_INT_MASK)

#define RTWDOG_CS_EN_MASK                        (0x80U)
#define RTWDOG_CS_EN_SHIFT                       (7U)
/*! EN - Watchdog Enable
 *  0b0..Watchdog disabled.
 *  0b1..Watchdog enabled.
 */
#define RTWDOG_CS_EN(x)                          (((uint32_t)(((uint32_t)(x)) << RTWDOG_CS_EN_SHIFT)) & RTWDOG_CS_EN_MASK)

#define RTWDOG_CS_CLK_MASK                       (0x300U)
#define RTWDOG_CS_CLK_SHIFT                      (8U)
/*! CLK - Watchdog Clock */
#define RTWDOG_CS_CLK(x)                         (((uint32_t)(((uint32_t)(x)) << RTWDOG_CS_CLK_SHIFT)) & RTWDOG_CS_CLK_MASK)

#define RTWDOG_CS_RCS_MASK                       (0x400U)
#define RTWDOG_CS_RCS_SHIFT                      (10U)
/*! RCS - Reconfiguration Success
 *  0b0..Reconfiguring WDOG.
 *  0b1..Reconfiguration is successful.
 */
#define RTWDOG_CS_RCS(x)                         (((uint32_t)(((uint32_t)(x)) << RTWDOG_CS_RCS_SHIFT)) & RTWDOG_CS_RCS_MASK)

#define RTWDOG_CS_ULK_MASK                       (0x800U)
#define RTWDOG_CS_ULK_SHIFT                      (11U)
/*! ULK - Unlock status
 *  0b0..WDOG is locked.
 *  0b1..WDOG is unlocked.
 */
#define RTWDOG_CS_ULK(x)                         (((uint32_t)(((uint32_t)(x)) << RTWDOG_CS_ULK_SHIFT)) & RTWDOG_CS_ULK_MASK)

#define RTWDOG_CS_PRES_MASK                      (0x1000U)
#define RTWDOG_CS_PRES_SHIFT                     (12U)
/*! PRES - Watchdog prescaler
 *  0b0..256 prescaler disabled.
 *  0b1..256 prescaler enabled.
 */
#define RTWDOG_CS_PRES(x)                        (((uint32_t)(((uint32_t)(x)) << RTWDOG_CS_PRES_SHIFT)) & RTWDOG_CS_PRES_MASK)

#define RTWDOG_CS_CMD32EN_MASK                   (0x2000U)
#define RTWDOG_CS_CMD32EN_SHIFT                  (13U)
/*! CMD32EN - Enables or disables WDOG support for 32-bit (otherwise 16-bit or 8-bit) refresh/unlock command write words
 *  0b0..Disables support for 32-bit refresh/unlock command write words. Only 16-bit or 8-bit is supported.
 *  0b1..Enables support for 32-bit refresh/unlock command write words. 16-bit or 8-bit is NOT supported.
 */
#define RTWDOG_CS_CMD32EN(x)                     (((uint32_t)(((uint32_t)(x)) << RTWDOG_CS_CMD32EN_SHIFT)) & RTWDOG_CS_CMD32EN_MASK)

#define RTWDOG_CS_FLG_MASK                       (0x4000U)
#define RTWDOG_CS_FLG_SHIFT                      (14U)
/*! FLG - Watchdog Interrupt Flag
 *  0b0..No interrupt occurred.
 *  0b1..An interrupt occurred.
 */
#define RTWDOG_CS_FLG(x)                         (((uint32_t)(((uint32_t)(x)) << RTWDOG_CS_FLG_SHIFT)) & RTWDOG_CS_FLG_MASK)

#define RTWDOG_CS_WIN_MASK                       (0x8000U)
#define RTWDOG_CS_WIN_SHIFT                      (15U)
/*! WIN - Watchdog Window
 *  0b0..Window mode disabled.
 *  0b1..Window mode enabled.
 */
#define RTWDOG_CS_WIN(x)                         (((uint32_t)(((uint32_t)(x)) << RTWDOG_CS_WIN_SHIFT)) & RTWDOG_CS_WIN_MASK)
/*! @} */

/*! @name CNT - Watchdog Counter Register */
/*! @{ */

#define RTWDOG_CNT_CNTLOW_MASK                   (0xFFU)
#define RTWDOG_CNT_CNTLOW_SHIFT                  (0U)
/*! CNTLOW - Low byte of the Watchdog Counter */
#define RTWDOG_CNT_CNTLOW(x)                     (((uint32_t)(((uint32_t)(x)) << RTWDOG_CNT_CNTLOW_SHIFT)) & RTWDOG_CNT_CNTLOW_MASK)

#define RTWDOG_CNT_CNTHIGH_MASK                  (0xFF00U)
#define RTWDOG_CNT_CNTHIGH_SHIFT                 (8U)
/*! CNTHIGH - High byte of the Watchdog Counter */
#define RTWDOG_CNT_CNTHIGH(x)                    (((uint32_t)(((uint32_t)(x)) << RTWDOG_CNT_CNTHIGH_SHIFT)) & RTWDOG_CNT_CNTHIGH_MASK)
/*! @} */

/*! @name TOVAL - Watchdog Timeout Value Register */
/*! @{ */

#define RTWDOG_TOVAL_TOVALLOW_MASK               (0xFFU)
#define RTWDOG_TOVAL_TOVALLOW_SHIFT              (0U)
/*! TOVALLOW - Low byte of the timeout value */
#define RTWDOG_TOVAL_TOVALLOW(x)                 (((uint32_t)(((uint32_t)(x)) << RTWDOG_TOVAL_TOVALLOW_SHIFT)) & RTWDOG_TOVAL_TOVALLOW_MASK)

#define RTWDOG_TOVAL_TOVALHIGH_MASK              (0xFF00U)
#define RTWDOG_TOVAL_TOVALHIGH_SHIFT             (8U)
/*! TOVALHIGH - High byte of the timeout value */
#define RTWDOG_TOVAL_TOVALHIGH(x)                (((uint32_t)(((uint32_t)(x)) << RTWDOG_TOVAL_TOVALHIGH_SHIFT)) & RTWDOG_TOVAL_TOVALHIGH_MASK)
/*! @} */

/*! @name WIN - Watchdog Window Register */
/*! @{ */

#define RTWDOG_WIN_WINLOW_MASK                   (0xFFU)
#define RTWDOG_WIN_WINLOW_SHIFT                  (0U)
/*! WINLOW - Low byte of Watchdog Window */
#define RTWDOG_WIN_WINLOW(x)                     (((uint32_t)(((uint32_t)(x)) << RTWDOG_WIN_WINLOW_SHIFT)) & RTWDOG_WIN_WINLOW_MASK)

#define RTWDOG_WIN_WINHIGH_MASK                  (0xFF00U)
#define RTWDOG_WIN_WINHIGH_SHIFT                 (8U)
/*! WINHIGH - High byte of Watchdog Window */
#define RTWDOG_WIN_WINHIGH(x)                    (((uint32_t)(((uint32_t)(x)) << RTWDOG_WIN_WINHIGH_SHIFT)) & RTWDOG_WIN_WINHIGH_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group RTWDOG_Register_Masks */

/* Extra definition */
#define RTWDOG_UPDATE_KEY                        (0xD928C520U)
#define RTWDOG_REFRESH_KEY                       (0xB480A602U)


/*!
 * @}
 */ /* end of group RTWDOG_Peripheral_Access_Layer */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic pop
  #else
    #pragma pop
  #endif
#elif defined(__CWCC__)
  #pragma pop
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=default
#else
  #error Not supported compiler type
#endif

/*!
 * @}
 */ /* end of group Peripheral_access_layer */


#endif  /* PERI_RTWDOG_H_ */

