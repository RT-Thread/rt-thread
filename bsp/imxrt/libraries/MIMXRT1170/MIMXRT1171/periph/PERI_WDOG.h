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
**         CMSIS Peripheral Access Layer for WDOG
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
 * @file PERI_WDOG.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for WDOG
 *
 * CMSIS Peripheral Access Layer for WDOG
 */

#if !defined(PERI_WDOG_H_)
#define PERI_WDOG_H_                             /**< Symbol preventing repeated inclusion */

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
   -- WDOG Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Peripheral_Access_Layer WDOG Peripheral Access Layer
 * @{
 */

/** WDOG - Register Layout Typedef */
typedef struct {
  __IO uint16_t WCR;                               /**< Watchdog Control Register, offset: 0x0 */
  __IO uint16_t WSR;                               /**< Watchdog Service Register, offset: 0x2 */
  __I  uint16_t WRSR;                              /**< Watchdog Reset Status Register, offset: 0x4 */
  __IO uint16_t WICR;                              /**< Watchdog Interrupt Control Register, offset: 0x6 */
  __IO uint16_t WMCR;                              /**< Watchdog Miscellaneous Control Register, offset: 0x8 */
} WDOG_Type;

/* ----------------------------------------------------------------------------
   -- WDOG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Register_Masks WDOG Register Masks
 * @{
 */

/*! @name WCR - Watchdog Control Register */
/*! @{ */

#define WDOG_WCR_WDZST_MASK                      (0x1U)
#define WDOG_WCR_WDZST_SHIFT                     (0U)
/*! WDZST - WDZST
 *  0b0..Continue timer operation (Default).
 *  0b1..Suspend the watchdog timer.
 */
#define WDOG_WCR_WDZST(x)                        (((uint16_t)(((uint16_t)(x)) << WDOG_WCR_WDZST_SHIFT)) & WDOG_WCR_WDZST_MASK)

#define WDOG_WCR_WDBG_MASK                       (0x2U)
#define WDOG_WCR_WDBG_SHIFT                      (1U)
/*! WDBG - WDBG
 *  0b0..Continue WDOG timer operation (Default).
 *  0b1..Suspend the watchdog timer.
 */
#define WDOG_WCR_WDBG(x)                         (((uint16_t)(((uint16_t)(x)) << WDOG_WCR_WDBG_SHIFT)) & WDOG_WCR_WDBG_MASK)

#define WDOG_WCR_WDE_MASK                        (0x4U)
#define WDOG_WCR_WDE_SHIFT                       (2U)
/*! WDE - WDE
 *  0b0..Disable the Watchdog (Default).
 *  0b1..Enable the Watchdog.
 */
#define WDOG_WCR_WDE(x)                          (((uint16_t)(((uint16_t)(x)) << WDOG_WCR_WDE_SHIFT)) & WDOG_WCR_WDE_MASK)

#define WDOG_WCR_WDT_MASK                        (0x8U)
#define WDOG_WCR_WDT_SHIFT                       (3U)
/*! WDT - WDT
 *  0b0..No effect on WDOG_B (Default).
 *  0b1..Assert WDOG_B upon a Watchdog Time-out event.
 */
#define WDOG_WCR_WDT(x)                          (((uint16_t)(((uint16_t)(x)) << WDOG_WCR_WDT_SHIFT)) & WDOG_WCR_WDT_MASK)

#define WDOG_WCR_SRS_MASK                        (0x10U)
#define WDOG_WCR_SRS_SHIFT                       (4U)
/*! SRS - SRS
 *  0b0..Assert system reset signal.
 *  0b1..No effect on the system (Default).
 */
#define WDOG_WCR_SRS(x)                          (((uint16_t)(((uint16_t)(x)) << WDOG_WCR_SRS_SHIFT)) & WDOG_WCR_SRS_MASK)

#define WDOG_WCR_WDA_MASK                        (0x20U)
#define WDOG_WCR_WDA_SHIFT                       (5U)
/*! WDA - WDA
 *  0b0..Assert WDOG_B output.
 *  0b1..No effect on system (Default).
 */
#define WDOG_WCR_WDA(x)                          (((uint16_t)(((uint16_t)(x)) << WDOG_WCR_WDA_SHIFT)) & WDOG_WCR_WDA_MASK)

#define WDOG_WCR_SRE_MASK                        (0x40U)
#define WDOG_WCR_SRE_SHIFT                       (6U)
/*! SRE - Software Reset Extension, an optional way to generate software reset
 *  0b0..using original way to generate software reset (default)
 *  0b1..using new way to generate software reset.
 */
#define WDOG_WCR_SRE(x)                          (((uint16_t)(((uint16_t)(x)) << WDOG_WCR_SRE_SHIFT)) & WDOG_WCR_SRE_MASK)

#define WDOG_WCR_WDW_MASK                        (0x80U)
#define WDOG_WCR_WDW_SHIFT                       (7U)
/*! WDW - WDW
 *  0b0..Continue WDOG timer operation (Default).
 *  0b1..Suspend WDOG timer operation.
 */
#define WDOG_WCR_WDW(x)                          (((uint16_t)(((uint16_t)(x)) << WDOG_WCR_WDW_SHIFT)) & WDOG_WCR_WDW_MASK)

#define WDOG_WCR_WT_MASK                         (0xFF00U)
#define WDOG_WCR_WT_SHIFT                        (8U)
/*! WT - WT
 *  0b00000000..- 0.5 Seconds (Default).
 *  0b00000001..- 1.0 Seconds.
 *  0b00000010..- 1.5 Seconds.
 *  0b00000011..- 2.0 Seconds.
 *  0b11111111..- 128 Seconds.
 */
#define WDOG_WCR_WT(x)                           (((uint16_t)(((uint16_t)(x)) << WDOG_WCR_WT_SHIFT)) & WDOG_WCR_WT_MASK)
/*! @} */

/*! @name WSR - Watchdog Service Register */
/*! @{ */

#define WDOG_WSR_WSR_MASK                        (0xFFFFU)
#define WDOG_WSR_WSR_SHIFT                       (0U)
/*! WSR - WSR
 *  0b0101010101010101..Write to the Watchdog Service Register (WDOG_WSR).
 *  0b1010101010101010..Write to the Watchdog Service Register (WDOG_WSR).
 */
#define WDOG_WSR_WSR(x)                          (((uint16_t)(((uint16_t)(x)) << WDOG_WSR_WSR_SHIFT)) & WDOG_WSR_WSR_MASK)
/*! @} */

/*! @name WRSR - Watchdog Reset Status Register */
/*! @{ */

#define WDOG_WRSR_SFTW_MASK                      (0x1U)
#define WDOG_WRSR_SFTW_SHIFT                     (0U)
/*! SFTW - SFTW
 *  0b0..Reset is not the result of a software reset.
 *  0b1..Reset is the result of a software reset.
 */
#define WDOG_WRSR_SFTW(x)                        (((uint16_t)(((uint16_t)(x)) << WDOG_WRSR_SFTW_SHIFT)) & WDOG_WRSR_SFTW_MASK)

#define WDOG_WRSR_TOUT_MASK                      (0x2U)
#define WDOG_WRSR_TOUT_SHIFT                     (1U)
/*! TOUT - TOUT
 *  0b0..Reset is not the result of a WDOG timeout.
 *  0b1..Reset is the result of a WDOG timeout.
 */
#define WDOG_WRSR_TOUT(x)                        (((uint16_t)(((uint16_t)(x)) << WDOG_WRSR_TOUT_SHIFT)) & WDOG_WRSR_TOUT_MASK)

#define WDOG_WRSR_POR_MASK                       (0x10U)
#define WDOG_WRSR_POR_SHIFT                      (4U)
/*! POR - POR
 *  0b0..Reset is not the result of a power on reset.
 *  0b1..Reset is the result of a power on reset.
 */
#define WDOG_WRSR_POR(x)                         (((uint16_t)(((uint16_t)(x)) << WDOG_WRSR_POR_SHIFT)) & WDOG_WRSR_POR_MASK)
/*! @} */

/*! @name WICR - Watchdog Interrupt Control Register */
/*! @{ */

#define WDOG_WICR_WICT_MASK                      (0xFFU)
#define WDOG_WICR_WICT_SHIFT                     (0U)
/*! WICT - WICT
 *  0b00000000..WICT[7:0] = Time duration between interrupt and time-out is 0 seconds.
 *  0b00000001..WICT[7:0] = Time duration between interrupt and time-out is 0.5 seconds.
 *  0b00000100..WICT[7:0] = Time duration between interrupt and time-out is 2 seconds (Default).
 *  0b11111111..WICT[7:0] = Time duration between interrupt and time-out is 127.5 seconds.
 */
#define WDOG_WICR_WICT(x)                        (((uint16_t)(((uint16_t)(x)) << WDOG_WICR_WICT_SHIFT)) & WDOG_WICR_WICT_MASK)

#define WDOG_WICR_WTIS_MASK                      (0x4000U)
#define WDOG_WICR_WTIS_SHIFT                     (14U)
/*! WTIS - WTIS
 *  0b0..No interrupt has occurred (Default).
 *  0b1..Interrupt has occurred
 */
#define WDOG_WICR_WTIS(x)                        (((uint16_t)(((uint16_t)(x)) << WDOG_WICR_WTIS_SHIFT)) & WDOG_WICR_WTIS_MASK)

#define WDOG_WICR_WIE_MASK                       (0x8000U)
#define WDOG_WICR_WIE_SHIFT                      (15U)
/*! WIE - WIE
 *  0b0..Disable Interrupt (Default).
 *  0b1..Enable Interrupt.
 */
#define WDOG_WICR_WIE(x)                         (((uint16_t)(((uint16_t)(x)) << WDOG_WICR_WIE_SHIFT)) & WDOG_WICR_WIE_MASK)
/*! @} */

/*! @name WMCR - Watchdog Miscellaneous Control Register */
/*! @{ */

#define WDOG_WMCR_PDE_MASK                       (0x1U)
#define WDOG_WMCR_PDE_SHIFT                      (0U)
/*! PDE - PDE
 *  0b0..Power Down Counter of WDOG is disabled.
 *  0b1..Power Down Counter of WDOG is enabled (Default).
 */
#define WDOG_WMCR_PDE(x)                         (((uint16_t)(((uint16_t)(x)) << WDOG_WMCR_PDE_SHIFT)) & WDOG_WMCR_PDE_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group WDOG_Register_Masks */


/*!
 * @}
 */ /* end of group WDOG_Peripheral_Access_Layer */


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


#endif  /* PERI_WDOG_H_ */

