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
**         CMSIS Peripheral Access Layer for RDC_SEMAPHORE
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
 * @file PERI_RDC_SEMAPHORE.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for RDC_SEMAPHORE
 *
 * CMSIS Peripheral Access Layer for RDC_SEMAPHORE
 */

#if !defined(PERI_RDC_SEMAPHORE_H_)
#define PERI_RDC_SEMAPHORE_H_                    /**< Symbol preventing repeated inclusion */

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
   -- RDC_SEMAPHORE Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RDC_SEMAPHORE_Peripheral_Access_Layer RDC_SEMAPHORE Peripheral Access Layer
 * @{
 */

/** RDC_SEMAPHORE - Size of Registers Arrays */
#define RDC_SEMAPHORE_GATE_COUNT                  64u

/** RDC_SEMAPHORE - Register Layout Typedef */
typedef struct {
  __IO uint8_t GATE[RDC_SEMAPHORE_GATE_COUNT];     /**< Gate Register, array offset: 0x0, array step: 0x1 */
       uint8_t RESERVED_0[2];
  union {                                          /* offset: 0x42 */
    __IO uint16_t RSTGT_R;                           /**< Reset Gate Read, offset: 0x42 */
    __IO uint16_t RSTGT_W;                           /**< Reset Gate Write, offset: 0x42 */
  };
} RDC_SEMAPHORE_Type;

/* ----------------------------------------------------------------------------
   -- RDC_SEMAPHORE Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RDC_SEMAPHORE_Register_Masks RDC_SEMAPHORE Register Masks
 * @{
 */

/*! @name GATE - Gate Register */
/*! @{ */

#define RDC_SEMAPHORE_GATE_GTFSM_MASK            (0xFU)
#define RDC_SEMAPHORE_GATE_GTFSM_SHIFT           (0U)
/*! GTFSM - Gate Finite State Machine.
 *  0b0000..The gate is unlocked (free).
 *  0b0001..The gate has been locked by processor with master_index = 0.
 *  0b0010..The gate has been locked by processor with master_index = 1.
 *  0b0011..The gate has been locked by processor with master_index = 2.
 *  0b0100..The gate has been locked by processor with master_index = 3.
 *  0b0101..The gate has been locked by processor with master_index = 4.
 *  0b0110..The gate has been locked by processor with master_index = 5.
 *  0b0111..The gate has been locked by processor with master_index = 6.
 *  0b1000..The gate has been locked by processor with master_index = 7.
 *  0b1001..The gate has been locked by processor with master_index = 8.
 *  0b1010..The gate has been locked by processor with master_index = 9.
 *  0b1011..The gate has been locked by processor with master_index = 10.
 *  0b1100..The gate has been locked by processor with master_index = 11.
 *  0b1101..The gate has been locked by processor with master_index = 12.
 *  0b1110..The gate has been locked by processor with master_index = 13.
 *  0b1111..The gate has been locked by processor with master_index = 14.
 */
#define RDC_SEMAPHORE_GATE_GTFSM(x)              (((uint8_t)(((uint8_t)(x)) << RDC_SEMAPHORE_GATE_GTFSM_SHIFT)) & RDC_SEMAPHORE_GATE_GTFSM_MASK)

#define RDC_SEMAPHORE_GATE_LDOM_MASK             (0x30U)
#define RDC_SEMAPHORE_GATE_LDOM_SHIFT            (4U)
/*! LDOM
 *  0b00..The gate is locked by domain 0. (True if the field GTFSM does not equal to 0000.)
 *  0b01..The gate has been locked by domain 1.
 *  0b10..Reserved
 *  0b11..Reserved
 */
#define RDC_SEMAPHORE_GATE_LDOM(x)               (((uint8_t)(((uint8_t)(x)) << RDC_SEMAPHORE_GATE_LDOM_SHIFT)) & RDC_SEMAPHORE_GATE_LDOM_MASK)
/*! @} */

/*! @name RSTGT_R - Reset Gate Read */
/*! @{ */

#define RDC_SEMAPHORE_RSTGT_R_RSTGMS_MASK        (0xFU)
#define RDC_SEMAPHORE_RSTGT_R_RSTGMS_SHIFT       (0U)
#define RDC_SEMAPHORE_RSTGT_R_RSTGMS(x)          (((uint16_t)(((uint16_t)(x)) << RDC_SEMAPHORE_RSTGT_R_RSTGMS_SHIFT)) & RDC_SEMAPHORE_RSTGT_R_RSTGMS_MASK)

#define RDC_SEMAPHORE_RSTGT_R_RSTGSM_MASK        (0x30U)
#define RDC_SEMAPHORE_RSTGT_R_RSTGSM_SHIFT       (4U)
/*! RSTGSM
 *  0b00..Idle, waiting for the first data pattern write.
 *  0b01..Waiting for the second data pattern write.
 *  0b10..The 2-write sequence has completed. Generate the specified gate reset(s). After the reset is performed,
 *        this machine returns to the idle (waiting for first data pattern write) state. The "01" state persists
 *        for only one clock cycle. Software will never be able to observe this state.
 *  0b11..This state encoding is never used and therefore reserved.
 */
#define RDC_SEMAPHORE_RSTGT_R_RSTGSM(x)          (((uint16_t)(((uint16_t)(x)) << RDC_SEMAPHORE_RSTGT_R_RSTGSM_SHIFT)) & RDC_SEMAPHORE_RSTGT_R_RSTGSM_MASK)

#define RDC_SEMAPHORE_RSTGT_R_RSTGTN_MASK        (0xFF00U)
#define RDC_SEMAPHORE_RSTGT_R_RSTGTN_SHIFT       (8U)
#define RDC_SEMAPHORE_RSTGT_R_RSTGTN(x)          (((uint16_t)(((uint16_t)(x)) << RDC_SEMAPHORE_RSTGT_R_RSTGTN_SHIFT)) & RDC_SEMAPHORE_RSTGT_R_RSTGTN_MASK)
/*! @} */

/*! @name RSTGT_W - Reset Gate Write */
/*! @{ */

#define RDC_SEMAPHORE_RSTGT_W_RSTGDP_MASK        (0xFFU)
#define RDC_SEMAPHORE_RSTGT_W_RSTGDP_SHIFT       (0U)
#define RDC_SEMAPHORE_RSTGT_W_RSTGDP(x)          (((uint16_t)(((uint16_t)(x)) << RDC_SEMAPHORE_RSTGT_W_RSTGDP_SHIFT)) & RDC_SEMAPHORE_RSTGT_W_RSTGDP_MASK)

#define RDC_SEMAPHORE_RSTGT_W_RSTGTN_MASK        (0xFF00U)
#define RDC_SEMAPHORE_RSTGT_W_RSTGTN_SHIFT       (8U)
#define RDC_SEMAPHORE_RSTGT_W_RSTGTN(x)          (((uint16_t)(((uint16_t)(x)) << RDC_SEMAPHORE_RSTGT_W_RSTGTN_SHIFT)) & RDC_SEMAPHORE_RSTGT_W_RSTGTN_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group RDC_SEMAPHORE_Register_Masks */


/*!
 * @}
 */ /* end of group RDC_SEMAPHORE_Peripheral_Access_Layer */


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


#endif  /* PERI_RDC_SEMAPHORE_H_ */

