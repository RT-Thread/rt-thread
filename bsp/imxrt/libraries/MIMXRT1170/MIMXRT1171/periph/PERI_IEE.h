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
**         CMSIS Peripheral Access Layer for IEE
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
 * @file PERI_IEE.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for IEE
 *
 * CMSIS Peripheral Access Layer for IEE
 */

#if !defined(PERI_IEE_H_)
#define PERI_IEE_H_                              /**< Symbol preventing repeated inclusion */

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
   -- IEE Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IEE_Peripheral_Access_Layer IEE Peripheral Access Layer
 * @{
 */

/** IEE - Size of Registers Arrays */
#define IEE_REGX_REGKEY1_I_COUNT                  8u
#define IEE_REGX_REGKEY2_I_COUNT                  8u
#define IEE_REGX_COUNT                            8u
#define IEE_AESTSTBUFX_COUNT                      32u

/** IEE - Register Layout Typedef */
typedef struct {
  __IO uint32_t GCFG;                              /**< IEE Global Configuration, offset: 0x0 */
  __I  uint32_t STA;                               /**< IEE Status, offset: 0x4 */
  __IO uint32_t TSTMD;                             /**< IEE Test Mode Register, offset: 0x8 */
  __O  uint32_t DPAMS;                             /**< AES Mask Generation Seed, offset: 0xC */
       uint8_t RESERVED_0[16];
  __IO uint32_t PC_S_LT;                           /**< Performance Counter, AES Slave Latency Threshold Value, offset: 0x20 */
  __IO uint32_t PC_M_LT;                           /**< Performance Counter, AES Master Latency Threshold, offset: 0x24 */
       uint8_t RESERVED_1[24];
  __IO uint32_t PC_BLK_ENC;                        /**< Performance Counter, Number of AES Block Encryptions, offset: 0x40 */
  __IO uint32_t PC_BLK_DEC;                        /**< Performance Counter, Number of AES Block Decryptions, offset: 0x44 */
       uint8_t RESERVED_2[8];
  __IO uint32_t PC_SR_TRANS;                       /**< Performance Counter, Number of AXI Slave Read Transactions, offset: 0x50 */
  __IO uint32_t PC_SW_TRANS;                       /**< Performance Counter, Number of AXI Slave Write Transactions, offset: 0x54 */
  __IO uint32_t PC_MR_TRANS;                       /**< Performance Counter, Number of AXI Master Read Transactions, offset: 0x58 */
  __IO uint32_t PC_MW_TRANS;                       /**< Performance Counter, Number of AXI Master Write Transactions, offset: 0x5C */
       uint8_t RESERVED_3[4];
  __IO uint32_t PC_M_MBR;                          /**< Performance Counter, Number of AXI Master Merge Buffer Read Transactions, offset: 0x64 */
       uint8_t RESERVED_4[8];
  __IO uint32_t PC_SR_TBC_U;                       /**< Performance Counter, Upper Slave Read Transactions Byte Count, offset: 0x70 */
  __IO uint32_t PC_SR_TBC_L;                       /**< Performance Counter, Lower Slave Read Transactions Byte Count, offset: 0x74 */
  __IO uint32_t PC_SW_TBC_U;                       /**< Performance Counter, Upper Slave Write Transactions Byte Count, offset: 0x78 */
  __IO uint32_t PC_SW_TBC_L;                       /**< Performance Counter, Lower Slave Write Transactions Byte Count, offset: 0x7C */
  __IO uint32_t PC_MR_TBC_U;                       /**< Performance Counter, Upper Master Read Transactions Byte Count, offset: 0x80 */
  __IO uint32_t PC_MR_TBC_L;                       /**< Performance Counter, Lower Master Read Transactions Byte Count, offset: 0x84 */
  __IO uint32_t PC_MW_TBC_U;                       /**< Performance Counter, Upper Master Write Transactions Byte Count, offset: 0x88 */
  __IO uint32_t PC_MW_TBC_L;                       /**< Performance Counter, Lower Master Write Transactions Byte Count, offset: 0x8C */
  __IO uint32_t PC_SR_TLGTT;                       /**< Performance Counter, Number of AXI Slave Read Transactions with Latency Greater than the Threshold, offset: 0x90 */
  __IO uint32_t PC_SW_TLGTT;                       /**< Performance Counter, Number of AXI Slave Write Transactions with Latency Greater than the Threshold, offset: 0x94 */
  __IO uint32_t PC_MR_TLGTT;                       /**< Performance Counter, Number of AXI Master Read Transactions with Latency Greater than the Threshold, offset: 0x98 */
  __IO uint32_t PC_MW_TLGTT;                       /**< Performance Counter, Number of AXI Master Write Transactions with Latency Greater than the Threshold, offset: 0x9C */
  __IO uint32_t PC_SR_TLAT_U;                      /**< Performance Counter, Upper Slave Read Latency Count, offset: 0xA0 */
  __IO uint32_t PC_SR_TLAT_L;                      /**< Performance Counter, Lower Slave Read Latency Count, offset: 0xA4 */
  __IO uint32_t PC_SW_TLAT_U;                      /**< Performance Counter, Upper Slave Write Latency Count, offset: 0xA8 */
  __IO uint32_t PC_SW_TLAT_L;                      /**< Performance Counter, Lower Slave Write Latency Count, offset: 0xAC */
  __IO uint32_t PC_MR_TLAT_U;                      /**< Performance Counter, Upper Master Read Latency Count, offset: 0xB0 */
  __IO uint32_t PC_MR_TLAT_L;                      /**< Performance Counter, Lower Master Read Latency Count, offset: 0xB4 */
  __IO uint32_t PC_MW_TLAT_U;                      /**< Performance Counter, Upper Master Write Latency Count, offset: 0xB8 */
  __IO uint32_t PC_MW_TLAT_L;                      /**< Performance Counter, Lower Master Write Latency Count, offset: 0xBC */
  __IO uint32_t PC_SR_TNRT_U;                      /**< Performance Counter, Upper Slave Read Total Non-Responding Time, offset: 0xC0 */
  __IO uint32_t PC_SR_TNRT_L;                      /**< Performance Counter, Lower Slave Read Total Non-Responding Time, offset: 0xC4 */
  __IO uint32_t PC_SW_TNRT_U;                      /**< Performance Counter, Upper Slave Write Total Non-Responding Time, offset: 0xC8 */
  __IO uint32_t PC_SW_TNRT_L;                      /**< Performance Counter, Lower Slave Write Total Non-Responding Time, offset: 0xCC */
       uint8_t RESERVED_5[32];
  __I  uint32_t VIDR1;                             /**< IEE Version ID Register 1, offset: 0xF0 */
       uint8_t RESERVED_6[4];
  __I  uint32_t AESVID;                            /**< IEE AES Version ID Register, offset: 0xF8 */
       uint8_t RESERVED_7[4];
  struct {                                         /* offset: 0x100, array step: 0x100 */
    __IO uint32_t REGATTR;                           /**< IEE Region 0 Attribute Register...IEE Region 7 Attribute Register., array offset: 0x100, array step: 0x100 */
         uint8_t RESERVED_0[4];
    __IO uint32_t REGPO;                             /**< IEE Region 0 Page Offset Register..IEE Region 7 Page Offset Register, array offset: 0x108, array step: 0x100 */
         uint8_t RESERVED_1[52];
    __O  uint32_t REGKEY1[IEE_REGX_REGKEY1_I_COUNT];   /**< IEE Region 0 Key 1 Register..IEE Region 7 Key 1 Register, array offset: 0x140, array step: index*0x100, index2*0x4 */
         uint8_t RESERVED_2[32];
    __O  uint32_t REGKEY2[IEE_REGX_REGKEY2_I_COUNT];   /**< IEE Region 0 Key 2 Register..IEE Region 7 Key 2 Register, array offset: 0x180, array step: index*0x100, index2*0x4 */
         uint8_t RESERVED_3[96];
  } REGX[IEE_REGX_COUNT];
       uint8_t RESERVED_8[1536];
  __IO uint32_t AES_TST_DB[IEE_AESTSTBUFX_COUNT];  /**< IEE AES Test Mode Data Buffer, array offset: 0xF00, array step: 0x4 */
} IEE_Type;

/* ----------------------------------------------------------------------------
   -- IEE Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IEE_Register_Masks IEE Register Masks
 * @{
 */

/*! @name GCFG - IEE Global Configuration */
/*! @{ */

#define IEE_GCFG_RL0_MASK                        (0x1U)
#define IEE_GCFG_RL0_SHIFT                       (0U)
/*! RL0
 *  0b0..Unlocked.
 *  0b1..Key, Offset and Attribute registers are locked.
 */
#define IEE_GCFG_RL0(x)                          (((uint32_t)(((uint32_t)(x)) << IEE_GCFG_RL0_SHIFT)) & IEE_GCFG_RL0_MASK)

#define IEE_GCFG_RL1_MASK                        (0x2U)
#define IEE_GCFG_RL1_SHIFT                       (1U)
/*! RL1
 *  0b0..Unlocked.
 *  0b1..Key, Offset and Attribute registers are locked.
 */
#define IEE_GCFG_RL1(x)                          (((uint32_t)(((uint32_t)(x)) << IEE_GCFG_RL1_SHIFT)) & IEE_GCFG_RL1_MASK)

#define IEE_GCFG_RL2_MASK                        (0x4U)
#define IEE_GCFG_RL2_SHIFT                       (2U)
/*! RL2
 *  0b0..Unlocked.
 *  0b1..Key, Offset and Attribute registers are locked.
 */
#define IEE_GCFG_RL2(x)                          (((uint32_t)(((uint32_t)(x)) << IEE_GCFG_RL2_SHIFT)) & IEE_GCFG_RL2_MASK)

#define IEE_GCFG_RL3_MASK                        (0x8U)
#define IEE_GCFG_RL3_SHIFT                       (3U)
/*! RL3
 *  0b0..Unlocked.
 *  0b1..Key, Offset and Attribute registers are locked.
 */
#define IEE_GCFG_RL3(x)                          (((uint32_t)(((uint32_t)(x)) << IEE_GCFG_RL3_SHIFT)) & IEE_GCFG_RL3_MASK)

#define IEE_GCFG_RL4_MASK                        (0x10U)
#define IEE_GCFG_RL4_SHIFT                       (4U)
/*! RL4
 *  0b0..Unlocked.
 *  0b1..Key, Offset and Attribute registers are locked.
 */
#define IEE_GCFG_RL4(x)                          (((uint32_t)(((uint32_t)(x)) << IEE_GCFG_RL4_SHIFT)) & IEE_GCFG_RL4_MASK)

#define IEE_GCFG_RL5_MASK                        (0x20U)
#define IEE_GCFG_RL5_SHIFT                       (5U)
/*! RL5
 *  0b0..Unlocked.
 *  0b1..Key, Offset and Attribute registers are locked.
 */
#define IEE_GCFG_RL5(x)                          (((uint32_t)(((uint32_t)(x)) << IEE_GCFG_RL5_SHIFT)) & IEE_GCFG_RL5_MASK)

#define IEE_GCFG_RL6_MASK                        (0x40U)
#define IEE_GCFG_RL6_SHIFT                       (6U)
/*! RL6
 *  0b0..Unlocked.
 *  0b1..Key, Offset and Attribute registers are locked.
 */
#define IEE_GCFG_RL6(x)                          (((uint32_t)(((uint32_t)(x)) << IEE_GCFG_RL6_SHIFT)) & IEE_GCFG_RL6_MASK)

#define IEE_GCFG_RL7_MASK                        (0x80U)
#define IEE_GCFG_RL7_SHIFT                       (7U)
/*! RL7
 *  0b0..Unlocked.
 *  0b1..Key, Offset and Attribute registers are locked.
 */
#define IEE_GCFG_RL7(x)                          (((uint32_t)(((uint32_t)(x)) << IEE_GCFG_RL7_SHIFT)) & IEE_GCFG_RL7_MASK)

#define IEE_GCFG_TME_MASK                        (0x10000U)
#define IEE_GCFG_TME_SHIFT                       (16U)
/*! TME
 *  0b0..Disabled.
 *  0b1..Enabled.
 */
#define IEE_GCFG_TME(x)                          (((uint32_t)(((uint32_t)(x)) << IEE_GCFG_TME_SHIFT)) & IEE_GCFG_TME_MASK)

#define IEE_GCFG_TMD_MASK                        (0x20000U)
#define IEE_GCFG_TMD_SHIFT                       (17U)
/*! TMD
 *  0b0..Test mode is usable.
 *  0b1..Test mode is disabled.
 */
#define IEE_GCFG_TMD(x)                          (((uint32_t)(((uint32_t)(x)) << IEE_GCFG_TMD_SHIFT)) & IEE_GCFG_TMD_MASK)

#define IEE_GCFG_KEY_RD_DIS_MASK                 (0x2000000U)
#define IEE_GCFG_KEY_RD_DIS_SHIFT                (25U)
/*! KEY_RD_DIS
 *  0b0..Key read enabled. Reading the key registers is allowed.
 *  0b1..Key read disabled. Reading the key registers is disabled.
 */
#define IEE_GCFG_KEY_RD_DIS(x)                   (((uint32_t)(((uint32_t)(x)) << IEE_GCFG_KEY_RD_DIS_SHIFT)) & IEE_GCFG_KEY_RD_DIS_MASK)

#define IEE_GCFG_MON_EN_MASK                     (0x10000000U)
#define IEE_GCFG_MON_EN_SHIFT                    (28U)
/*! MON_EN
 *  0b0..Performance monitoring disabled. Writing of the performance counter registers is enabled.
 *  0b1..Performance monitoring enabled. Writing of the performance counter registers is disabled.
 */
#define IEE_GCFG_MON_EN(x)                       (((uint32_t)(((uint32_t)(x)) << IEE_GCFG_MON_EN_SHIFT)) & IEE_GCFG_MON_EN_MASK)

#define IEE_GCFG_CLR_MON_MASK                    (0x20000000U)
#define IEE_GCFG_CLR_MON_SHIFT                   (29U)
/*! CLR_MON
 *  0b0..Do not reset.
 *  0b1..Reset performance counters.
 */
#define IEE_GCFG_CLR_MON(x)                      (((uint32_t)(((uint32_t)(x)) << IEE_GCFG_CLR_MON_SHIFT)) & IEE_GCFG_CLR_MON_MASK)

#define IEE_GCFG_RST_MASK                        (0x80000000U)
#define IEE_GCFG_RST_SHIFT                       (31U)
/*! RST
 *  0b0..Do Not Reset.
 *  0b1..Reset IEE.
 */
#define IEE_GCFG_RST(x)                          (((uint32_t)(((uint32_t)(x)) << IEE_GCFG_RST_SHIFT)) & IEE_GCFG_RST_MASK)
/*! @} */

/*! @name STA - IEE Status */
/*! @{ */

#define IEE_STA_DSR_MASK                         (0x1U)
#define IEE_STA_DSR_SHIFT                        (0U)
/*! DSR
 *  0b0..No seed request present
 *  0b1..Seed request present
 */
#define IEE_STA_DSR(x)                           (((uint32_t)(((uint32_t)(x)) << IEE_STA_DSR_SHIFT)) & IEE_STA_DSR_MASK)

#define IEE_STA_AFD_MASK                         (0x10U)
#define IEE_STA_AFD_SHIFT                        (4U)
/*! AFD
 *  0b0..No fault detected
 *  0b1..Fault detected
 */
#define IEE_STA_AFD(x)                           (((uint32_t)(((uint32_t)(x)) << IEE_STA_AFD_SHIFT)) & IEE_STA_AFD_MASK)
/*! @} */

/*! @name TSTMD - IEE Test Mode Register */
/*! @{ */

#define IEE_TSTMD_TMRDY_MASK                     (0x1U)
#define IEE_TSTMD_TMRDY_SHIFT                    (0U)
/*! TMRDY
 *  0b0..Not Ready.
 *  0b1..Ready.
 */
#define IEE_TSTMD_TMRDY(x)                       (((uint32_t)(((uint32_t)(x)) << IEE_TSTMD_TMRDY_SHIFT)) & IEE_TSTMD_TMRDY_MASK)

#define IEE_TSTMD_TMR_MASK                       (0x2U)
#define IEE_TSTMD_TMR_SHIFT                      (1U)
/*! TMR
 *  0b0..Not running. May be written if IEE_GCFG[TME] = 1
 *  0b1..Run AES Test until TMDONE is indicated.
 */
#define IEE_TSTMD_TMR(x)                         (((uint32_t)(((uint32_t)(x)) << IEE_TSTMD_TMR_SHIFT)) & IEE_TSTMD_TMR_MASK)

#define IEE_TSTMD_TMENCR_MASK                    (0x4U)
#define IEE_TSTMD_TMENCR_SHIFT                   (2U)
/*! TMENCR
 *  0b0..AES Test mode will do decryption.
 *  0b1..AES Test mode will do encryption.
 */
#define IEE_TSTMD_TMENCR(x)                      (((uint32_t)(((uint32_t)(x)) << IEE_TSTMD_TMENCR_SHIFT)) & IEE_TSTMD_TMENCR_MASK)

#define IEE_TSTMD_TMCONT_MASK                    (0x8U)
#define IEE_TSTMD_TMCONT_SHIFT                   (3U)
/*! TMCONT
 *  0b0..Do not continue. This is the last block of data for AES.
 *  0b1..Continue. Do not initialize AES after this block.
 */
#define IEE_TSTMD_TMCONT(x)                      (((uint32_t)(((uint32_t)(x)) << IEE_TSTMD_TMCONT_SHIFT)) & IEE_TSTMD_TMCONT_MASK)

#define IEE_TSTMD_TMDONE_MASK                    (0x10U)
#define IEE_TSTMD_TMDONE_SHIFT                   (4U)
/*! TMDONE
 *  0b0..Not Done.
 *  0b1..Test Done.
 */
#define IEE_TSTMD_TMDONE(x)                      (((uint32_t)(((uint32_t)(x)) << IEE_TSTMD_TMDONE_SHIFT)) & IEE_TSTMD_TMDONE_MASK)

#define IEE_TSTMD_TMLEN_MASK                     (0xF00U)
#define IEE_TSTMD_TMLEN_SHIFT                    (8U)
#define IEE_TSTMD_TMLEN(x)                       (((uint32_t)(((uint32_t)(x)) << IEE_TSTMD_TMLEN_SHIFT)) & IEE_TSTMD_TMLEN_MASK)
/*! @} */

/*! @name DPAMS - AES Mask Generation Seed */
/*! @{ */

#define IEE_DPAMS_DPAMS_MASK                     (0xFFFFFFFFU)
#define IEE_DPAMS_DPAMS_SHIFT                    (0U)
#define IEE_DPAMS_DPAMS(x)                       (((uint32_t)(((uint32_t)(x)) << IEE_DPAMS_DPAMS_SHIFT)) & IEE_DPAMS_DPAMS_MASK)
/*! @} */

/*! @name PC_S_LT - Performance Counter, AES Slave Latency Threshold Value */
/*! @{ */

#define IEE_PC_S_LT_SW_LT_MASK                   (0xFFFFU)
#define IEE_PC_S_LT_SW_LT_SHIFT                  (0U)
#define IEE_PC_S_LT_SW_LT(x)                     (((uint32_t)(((uint32_t)(x)) << IEE_PC_S_LT_SW_LT_SHIFT)) & IEE_PC_S_LT_SW_LT_MASK)

#define IEE_PC_S_LT_SR_LT_MASK                   (0xFFFF0000U)
#define IEE_PC_S_LT_SR_LT_SHIFT                  (16U)
#define IEE_PC_S_LT_SR_LT(x)                     (((uint32_t)(((uint32_t)(x)) << IEE_PC_S_LT_SR_LT_SHIFT)) & IEE_PC_S_LT_SR_LT_MASK)
/*! @} */

/*! @name PC_M_LT - Performance Counter, AES Master Latency Threshold */
/*! @{ */

#define IEE_PC_M_LT_MW_LT_MASK                   (0xFFFU)
#define IEE_PC_M_LT_MW_LT_SHIFT                  (0U)
#define IEE_PC_M_LT_MW_LT(x)                     (((uint32_t)(((uint32_t)(x)) << IEE_PC_M_LT_MW_LT_SHIFT)) & IEE_PC_M_LT_MW_LT_MASK)

#define IEE_PC_M_LT_MR_LT_MASK                   (0xFFF0000U)
#define IEE_PC_M_LT_MR_LT_SHIFT                  (16U)
#define IEE_PC_M_LT_MR_LT(x)                     (((uint32_t)(((uint32_t)(x)) << IEE_PC_M_LT_MR_LT_SHIFT)) & IEE_PC_M_LT_MR_LT_MASK)
/*! @} */

/*! @name PC_BLK_ENC - Performance Counter, Number of AES Block Encryptions */
/*! @{ */

#define IEE_PC_BLK_ENC_BLK_ENC_MASK              (0xFFFFFFFFU)
#define IEE_PC_BLK_ENC_BLK_ENC_SHIFT             (0U)
#define IEE_PC_BLK_ENC_BLK_ENC(x)                (((uint32_t)(((uint32_t)(x)) << IEE_PC_BLK_ENC_BLK_ENC_SHIFT)) & IEE_PC_BLK_ENC_BLK_ENC_MASK)
/*! @} */

/*! @name PC_BLK_DEC - Performance Counter, Number of AES Block Decryptions */
/*! @{ */

#define IEE_PC_BLK_DEC_BLK_DEC_MASK              (0xFFFFFFFFU)
#define IEE_PC_BLK_DEC_BLK_DEC_SHIFT             (0U)
#define IEE_PC_BLK_DEC_BLK_DEC(x)                (((uint32_t)(((uint32_t)(x)) << IEE_PC_BLK_DEC_BLK_DEC_SHIFT)) & IEE_PC_BLK_DEC_BLK_DEC_MASK)
/*! @} */

/*! @name PC_SR_TRANS - Performance Counter, Number of AXI Slave Read Transactions */
/*! @{ */

#define IEE_PC_SR_TRANS_SR_TRANS_MASK            (0xFFFFFFFFU)
#define IEE_PC_SR_TRANS_SR_TRANS_SHIFT           (0U)
#define IEE_PC_SR_TRANS_SR_TRANS(x)              (((uint32_t)(((uint32_t)(x)) << IEE_PC_SR_TRANS_SR_TRANS_SHIFT)) & IEE_PC_SR_TRANS_SR_TRANS_MASK)
/*! @} */

/*! @name PC_SW_TRANS - Performance Counter, Number of AXI Slave Write Transactions */
/*! @{ */

#define IEE_PC_SW_TRANS_SW_TRANS_MASK            (0xFFFFFFFFU)
#define IEE_PC_SW_TRANS_SW_TRANS_SHIFT           (0U)
#define IEE_PC_SW_TRANS_SW_TRANS(x)              (((uint32_t)(((uint32_t)(x)) << IEE_PC_SW_TRANS_SW_TRANS_SHIFT)) & IEE_PC_SW_TRANS_SW_TRANS_MASK)
/*! @} */

/*! @name PC_MR_TRANS - Performance Counter, Number of AXI Master Read Transactions */
/*! @{ */

#define IEE_PC_MR_TRANS_MR_TRANS_MASK            (0xFFFFFFFFU)
#define IEE_PC_MR_TRANS_MR_TRANS_SHIFT           (0U)
#define IEE_PC_MR_TRANS_MR_TRANS(x)              (((uint32_t)(((uint32_t)(x)) << IEE_PC_MR_TRANS_MR_TRANS_SHIFT)) & IEE_PC_MR_TRANS_MR_TRANS_MASK)
/*! @} */

/*! @name PC_MW_TRANS - Performance Counter, Number of AXI Master Write Transactions */
/*! @{ */

#define IEE_PC_MW_TRANS_MW_TRANS_MASK            (0xFFFFFFFFU)
#define IEE_PC_MW_TRANS_MW_TRANS_SHIFT           (0U)
#define IEE_PC_MW_TRANS_MW_TRANS(x)              (((uint32_t)(((uint32_t)(x)) << IEE_PC_MW_TRANS_MW_TRANS_SHIFT)) & IEE_PC_MW_TRANS_MW_TRANS_MASK)
/*! @} */

/*! @name PC_M_MBR - Performance Counter, Number of AXI Master Merge Buffer Read Transactions */
/*! @{ */

#define IEE_PC_M_MBR_M_MBR_MASK                  (0xFFFFFFFFU)
#define IEE_PC_M_MBR_M_MBR_SHIFT                 (0U)
#define IEE_PC_M_MBR_M_MBR(x)                    (((uint32_t)(((uint32_t)(x)) << IEE_PC_M_MBR_M_MBR_SHIFT)) & IEE_PC_M_MBR_M_MBR_MASK)
/*! @} */

/*! @name PC_SR_TBC_U - Performance Counter, Upper Slave Read Transactions Byte Count */
/*! @{ */

#define IEE_PC_SR_TBC_U_SR_TBC_MASK              (0xFFFFU)
#define IEE_PC_SR_TBC_U_SR_TBC_SHIFT             (0U)
#define IEE_PC_SR_TBC_U_SR_TBC(x)                (((uint32_t)(((uint32_t)(x)) << IEE_PC_SR_TBC_U_SR_TBC_SHIFT)) & IEE_PC_SR_TBC_U_SR_TBC_MASK)
/*! @} */

/*! @name PC_SR_TBC_L - Performance Counter, Lower Slave Read Transactions Byte Count */
/*! @{ */

#define IEE_PC_SR_TBC_L_SR_TBC_MASK              (0xFFFFFFFFU)
#define IEE_PC_SR_TBC_L_SR_TBC_SHIFT             (0U)
#define IEE_PC_SR_TBC_L_SR_TBC(x)                (((uint32_t)(((uint32_t)(x)) << IEE_PC_SR_TBC_L_SR_TBC_SHIFT)) & IEE_PC_SR_TBC_L_SR_TBC_MASK)
/*! @} */

/*! @name PC_SW_TBC_U - Performance Counter, Upper Slave Write Transactions Byte Count */
/*! @{ */

#define IEE_PC_SW_TBC_U_SW_TBC_MASK              (0xFFFFU)
#define IEE_PC_SW_TBC_U_SW_TBC_SHIFT             (0U)
#define IEE_PC_SW_TBC_U_SW_TBC(x)                (((uint32_t)(((uint32_t)(x)) << IEE_PC_SW_TBC_U_SW_TBC_SHIFT)) & IEE_PC_SW_TBC_U_SW_TBC_MASK)
/*! @} */

/*! @name PC_SW_TBC_L - Performance Counter, Lower Slave Write Transactions Byte Count */
/*! @{ */

#define IEE_PC_SW_TBC_L_SW_TBC_MASK              (0xFFFFFFFFU)
#define IEE_PC_SW_TBC_L_SW_TBC_SHIFT             (0U)
#define IEE_PC_SW_TBC_L_SW_TBC(x)                (((uint32_t)(((uint32_t)(x)) << IEE_PC_SW_TBC_L_SW_TBC_SHIFT)) & IEE_PC_SW_TBC_L_SW_TBC_MASK)
/*! @} */

/*! @name PC_MR_TBC_U - Performance Counter, Upper Master Read Transactions Byte Count */
/*! @{ */

#define IEE_PC_MR_TBC_U_MR_TBC_MASK              (0xFFFFU)
#define IEE_PC_MR_TBC_U_MR_TBC_SHIFT             (0U)
#define IEE_PC_MR_TBC_U_MR_TBC(x)                (((uint32_t)(((uint32_t)(x)) << IEE_PC_MR_TBC_U_MR_TBC_SHIFT)) & IEE_PC_MR_TBC_U_MR_TBC_MASK)
/*! @} */

/*! @name PC_MR_TBC_L - Performance Counter, Lower Master Read Transactions Byte Count */
/*! @{ */

#define IEE_PC_MR_TBC_L_MR_TBC_LSB_MASK          (0xFU)
#define IEE_PC_MR_TBC_L_MR_TBC_LSB_SHIFT         (0U)
#define IEE_PC_MR_TBC_L_MR_TBC_LSB(x)            (((uint32_t)(((uint32_t)(x)) << IEE_PC_MR_TBC_L_MR_TBC_LSB_SHIFT)) & IEE_PC_MR_TBC_L_MR_TBC_LSB_MASK)

#define IEE_PC_MR_TBC_L_MR_TBC_MASK              (0xFFFFFFF0U)
#define IEE_PC_MR_TBC_L_MR_TBC_SHIFT             (4U)
#define IEE_PC_MR_TBC_L_MR_TBC(x)                (((uint32_t)(((uint32_t)(x)) << IEE_PC_MR_TBC_L_MR_TBC_SHIFT)) & IEE_PC_MR_TBC_L_MR_TBC_MASK)
/*! @} */

/*! @name PC_MW_TBC_U - Performance Counter, Upper Master Write Transactions Byte Count */
/*! @{ */

#define IEE_PC_MW_TBC_U_MW_TBC_MASK              (0xFFFFU)
#define IEE_PC_MW_TBC_U_MW_TBC_SHIFT             (0U)
#define IEE_PC_MW_TBC_U_MW_TBC(x)                (((uint32_t)(((uint32_t)(x)) << IEE_PC_MW_TBC_U_MW_TBC_SHIFT)) & IEE_PC_MW_TBC_U_MW_TBC_MASK)
/*! @} */

/*! @name PC_MW_TBC_L - Performance Counter, Lower Master Write Transactions Byte Count */
/*! @{ */

#define IEE_PC_MW_TBC_L_MW_TBC_LSB_MASK          (0xFU)
#define IEE_PC_MW_TBC_L_MW_TBC_LSB_SHIFT         (0U)
#define IEE_PC_MW_TBC_L_MW_TBC_LSB(x)            (((uint32_t)(((uint32_t)(x)) << IEE_PC_MW_TBC_L_MW_TBC_LSB_SHIFT)) & IEE_PC_MW_TBC_L_MW_TBC_LSB_MASK)

#define IEE_PC_MW_TBC_L_MW_TBC_MASK              (0xFFFFFFF0U)
#define IEE_PC_MW_TBC_L_MW_TBC_SHIFT             (4U)
#define IEE_PC_MW_TBC_L_MW_TBC(x)                (((uint32_t)(((uint32_t)(x)) << IEE_PC_MW_TBC_L_MW_TBC_SHIFT)) & IEE_PC_MW_TBC_L_MW_TBC_MASK)
/*! @} */

/*! @name PC_SR_TLGTT - Performance Counter, Number of AXI Slave Read Transactions with Latency Greater than the Threshold */
/*! @{ */

#define IEE_PC_SR_TLGTT_SR_TLGTT_MASK            (0xFFFFFFFFU)
#define IEE_PC_SR_TLGTT_SR_TLGTT_SHIFT           (0U)
#define IEE_PC_SR_TLGTT_SR_TLGTT(x)              (((uint32_t)(((uint32_t)(x)) << IEE_PC_SR_TLGTT_SR_TLGTT_SHIFT)) & IEE_PC_SR_TLGTT_SR_TLGTT_MASK)
/*! @} */

/*! @name PC_SW_TLGTT - Performance Counter, Number of AXI Slave Write Transactions with Latency Greater than the Threshold */
/*! @{ */

#define IEE_PC_SW_TLGTT_SW_TLGTT_MASK            (0xFFFFFFFFU)
#define IEE_PC_SW_TLGTT_SW_TLGTT_SHIFT           (0U)
#define IEE_PC_SW_TLGTT_SW_TLGTT(x)              (((uint32_t)(((uint32_t)(x)) << IEE_PC_SW_TLGTT_SW_TLGTT_SHIFT)) & IEE_PC_SW_TLGTT_SW_TLGTT_MASK)
/*! @} */

/*! @name PC_MR_TLGTT - Performance Counter, Number of AXI Master Read Transactions with Latency Greater than the Threshold */
/*! @{ */

#define IEE_PC_MR_TLGTT_MR_TLGTT_MASK            (0xFFFFFFFFU)
#define IEE_PC_MR_TLGTT_MR_TLGTT_SHIFT           (0U)
#define IEE_PC_MR_TLGTT_MR_TLGTT(x)              (((uint32_t)(((uint32_t)(x)) << IEE_PC_MR_TLGTT_MR_TLGTT_SHIFT)) & IEE_PC_MR_TLGTT_MR_TLGTT_MASK)
/*! @} */

/*! @name PC_MW_TLGTT - Performance Counter, Number of AXI Master Write Transactions with Latency Greater than the Threshold */
/*! @{ */

#define IEE_PC_MW_TLGTT_MW_TGTT_MASK             (0xFFFFFFFFU)
#define IEE_PC_MW_TLGTT_MW_TGTT_SHIFT            (0U)
#define IEE_PC_MW_TLGTT_MW_TGTT(x)               (((uint32_t)(((uint32_t)(x)) << IEE_PC_MW_TLGTT_MW_TGTT_SHIFT)) & IEE_PC_MW_TLGTT_MW_TGTT_MASK)
/*! @} */

/*! @name PC_SR_TLAT_U - Performance Counter, Upper Slave Read Latency Count */
/*! @{ */

#define IEE_PC_SR_TLAT_U_SR_TLAT_MASK            (0xFFFFU)
#define IEE_PC_SR_TLAT_U_SR_TLAT_SHIFT           (0U)
#define IEE_PC_SR_TLAT_U_SR_TLAT(x)              (((uint32_t)(((uint32_t)(x)) << IEE_PC_SR_TLAT_U_SR_TLAT_SHIFT)) & IEE_PC_SR_TLAT_U_SR_TLAT_MASK)
/*! @} */

/*! @name PC_SR_TLAT_L - Performance Counter, Lower Slave Read Latency Count */
/*! @{ */

#define IEE_PC_SR_TLAT_L_SR_TLAT_MASK            (0xFFFFFFFFU)
#define IEE_PC_SR_TLAT_L_SR_TLAT_SHIFT           (0U)
#define IEE_PC_SR_TLAT_L_SR_TLAT(x)              (((uint32_t)(((uint32_t)(x)) << IEE_PC_SR_TLAT_L_SR_TLAT_SHIFT)) & IEE_PC_SR_TLAT_L_SR_TLAT_MASK)
/*! @} */

/*! @name PC_SW_TLAT_U - Performance Counter, Upper Slave Write Latency Count */
/*! @{ */

#define IEE_PC_SW_TLAT_U_SW_TLAT_MASK            (0xFFFFU)
#define IEE_PC_SW_TLAT_U_SW_TLAT_SHIFT           (0U)
#define IEE_PC_SW_TLAT_U_SW_TLAT(x)              (((uint32_t)(((uint32_t)(x)) << IEE_PC_SW_TLAT_U_SW_TLAT_SHIFT)) & IEE_PC_SW_TLAT_U_SW_TLAT_MASK)
/*! @} */

/*! @name PC_SW_TLAT_L - Performance Counter, Lower Slave Write Latency Count */
/*! @{ */

#define IEE_PC_SW_TLAT_L_SW_TLAT_MASK            (0xFFFFFFFFU)
#define IEE_PC_SW_TLAT_L_SW_TLAT_SHIFT           (0U)
#define IEE_PC_SW_TLAT_L_SW_TLAT(x)              (((uint32_t)(((uint32_t)(x)) << IEE_PC_SW_TLAT_L_SW_TLAT_SHIFT)) & IEE_PC_SW_TLAT_L_SW_TLAT_MASK)
/*! @} */

/*! @name PC_MR_TLAT_U - Performance Counter, Upper Master Read Latency Count */
/*! @{ */

#define IEE_PC_MR_TLAT_U_MR_TLAT_MASK            (0xFFFFU)
#define IEE_PC_MR_TLAT_U_MR_TLAT_SHIFT           (0U)
#define IEE_PC_MR_TLAT_U_MR_TLAT(x)              (((uint32_t)(((uint32_t)(x)) << IEE_PC_MR_TLAT_U_MR_TLAT_SHIFT)) & IEE_PC_MR_TLAT_U_MR_TLAT_MASK)
/*! @} */

/*! @name PC_MR_TLAT_L - Performance Counter, Lower Master Read Latency Count */
/*! @{ */

#define IEE_PC_MR_TLAT_L_MR_TLAT_MASK            (0xFFFFFFFFU)
#define IEE_PC_MR_TLAT_L_MR_TLAT_SHIFT           (0U)
#define IEE_PC_MR_TLAT_L_MR_TLAT(x)              (((uint32_t)(((uint32_t)(x)) << IEE_PC_MR_TLAT_L_MR_TLAT_SHIFT)) & IEE_PC_MR_TLAT_L_MR_TLAT_MASK)
/*! @} */

/*! @name PC_MW_TLAT_U - Performance Counter, Upper Master Write Latency Count */
/*! @{ */

#define IEE_PC_MW_TLAT_U_MW_TLAT_MASK            (0xFFFFU)
#define IEE_PC_MW_TLAT_U_MW_TLAT_SHIFT           (0U)
#define IEE_PC_MW_TLAT_U_MW_TLAT(x)              (((uint32_t)(((uint32_t)(x)) << IEE_PC_MW_TLAT_U_MW_TLAT_SHIFT)) & IEE_PC_MW_TLAT_U_MW_TLAT_MASK)
/*! @} */

/*! @name PC_MW_TLAT_L - Performance Counter, Lower Master Write Latency Count */
/*! @{ */

#define IEE_PC_MW_TLAT_L_MW_TLAT_MASK            (0xFFFFFFFFU)
#define IEE_PC_MW_TLAT_L_MW_TLAT_SHIFT           (0U)
#define IEE_PC_MW_TLAT_L_MW_TLAT(x)              (((uint32_t)(((uint32_t)(x)) << IEE_PC_MW_TLAT_L_MW_TLAT_SHIFT)) & IEE_PC_MW_TLAT_L_MW_TLAT_MASK)
/*! @} */

/*! @name PC_SR_TNRT_U - Performance Counter, Upper Slave Read Total Non-Responding Time */
/*! @{ */

#define IEE_PC_SR_TNRT_U_SR_TNRT_MASK            (0xFFFFU)
#define IEE_PC_SR_TNRT_U_SR_TNRT_SHIFT           (0U)
#define IEE_PC_SR_TNRT_U_SR_TNRT(x)              (((uint32_t)(((uint32_t)(x)) << IEE_PC_SR_TNRT_U_SR_TNRT_SHIFT)) & IEE_PC_SR_TNRT_U_SR_TNRT_MASK)
/*! @} */

/*! @name PC_SR_TNRT_L - Performance Counter, Lower Slave Read Total Non-Responding Time */
/*! @{ */

#define IEE_PC_SR_TNRT_L_SR_TNRT_MASK            (0xFFFFFFFFU)
#define IEE_PC_SR_TNRT_L_SR_TNRT_SHIFT           (0U)
#define IEE_PC_SR_TNRT_L_SR_TNRT(x)              (((uint32_t)(((uint32_t)(x)) << IEE_PC_SR_TNRT_L_SR_TNRT_SHIFT)) & IEE_PC_SR_TNRT_L_SR_TNRT_MASK)
/*! @} */

/*! @name PC_SW_TNRT_U - Performance Counter, Upper Slave Write Total Non-Responding Time */
/*! @{ */

#define IEE_PC_SW_TNRT_U_SW_TNRT_MASK            (0xFFFFU)
#define IEE_PC_SW_TNRT_U_SW_TNRT_SHIFT           (0U)
#define IEE_PC_SW_TNRT_U_SW_TNRT(x)              (((uint32_t)(((uint32_t)(x)) << IEE_PC_SW_TNRT_U_SW_TNRT_SHIFT)) & IEE_PC_SW_TNRT_U_SW_TNRT_MASK)
/*! @} */

/*! @name PC_SW_TNRT_L - Performance Counter, Lower Slave Write Total Non-Responding Time */
/*! @{ */

#define IEE_PC_SW_TNRT_L_SW_TNRT_MASK            (0xFFFFFFFFU)
#define IEE_PC_SW_TNRT_L_SW_TNRT_SHIFT           (0U)
#define IEE_PC_SW_TNRT_L_SW_TNRT(x)              (((uint32_t)(((uint32_t)(x)) << IEE_PC_SW_TNRT_L_SW_TNRT_SHIFT)) & IEE_PC_SW_TNRT_L_SW_TNRT_MASK)
/*! @} */

/*! @name VIDR1 - IEE Version ID Register 1 */
/*! @{ */

#define IEE_VIDR1_MIN_REV_MASK                   (0xFFU)
#define IEE_VIDR1_MIN_REV_SHIFT                  (0U)
#define IEE_VIDR1_MIN_REV(x)                     (((uint32_t)(((uint32_t)(x)) << IEE_VIDR1_MIN_REV_SHIFT)) & IEE_VIDR1_MIN_REV_MASK)

#define IEE_VIDR1_MAJ_REV_MASK                   (0xFF00U)
#define IEE_VIDR1_MAJ_REV_SHIFT                  (8U)
#define IEE_VIDR1_MAJ_REV(x)                     (((uint32_t)(((uint32_t)(x)) << IEE_VIDR1_MAJ_REV_SHIFT)) & IEE_VIDR1_MAJ_REV_MASK)

#define IEE_VIDR1_IP_ID_MASK                     (0xFFFF0000U)
#define IEE_VIDR1_IP_ID_SHIFT                    (16U)
#define IEE_VIDR1_IP_ID(x)                       (((uint32_t)(((uint32_t)(x)) << IEE_VIDR1_IP_ID_SHIFT)) & IEE_VIDR1_IP_ID_MASK)
/*! @} */

/*! @name AESVID - IEE AES Version ID Register */
/*! @{ */

#define IEE_AESVID_AESRN_MASK                    (0xFU)
#define IEE_AESVID_AESRN_SHIFT                   (0U)
#define IEE_AESVID_AESRN(x)                      (((uint32_t)(((uint32_t)(x)) << IEE_AESVID_AESRN_SHIFT)) & IEE_AESVID_AESRN_MASK)

#define IEE_AESVID_AESVID_MASK                   (0xF0U)
#define IEE_AESVID_AESVID_SHIFT                  (4U)
#define IEE_AESVID_AESVID(x)                     (((uint32_t)(((uint32_t)(x)) << IEE_AESVID_AESVID_SHIFT)) & IEE_AESVID_AESVID_MASK)
/*! @} */

/*! @name REGATTR - IEE Region 0 Attribute Register...IEE Region 7 Attribute Register. */
/*! @{ */

#define IEE_REGATTR_KS_MASK                      (0x1U)
#define IEE_REGATTR_KS_SHIFT                     (0U)
/*! KS
 *  0b0..128 bits (CTR), 256 bits (XTS).
 *  0b1..256 bits (CTR), 512 bits (XTS).
 */
#define IEE_REGATTR_KS(x)                        (((uint32_t)(((uint32_t)(x)) << IEE_REGATTR_KS_SHIFT)) & IEE_REGATTR_KS_MASK)

#define IEE_REGATTR_MD_MASK                      (0x70U)
#define IEE_REGATTR_MD_SHIFT                     (4U)
/*! MD
 *  0b000..None (AXI error if accessed)
 *  0b001..XTS
 *  0b010..CTR w/ address binding
 *  0b011..CTR w/o address binding
 *  0b100..CTR keystream only
 *  0b101..Undefined, AXI error if used
 *  0b110..Undefined, AXI error if used
 *  0b111..Undefined, AXI error if used
 */
#define IEE_REGATTR_MD(x)                        (((uint32_t)(((uint32_t)(x)) << IEE_REGATTR_MD_SHIFT)) & IEE_REGATTR_MD_MASK)

#define IEE_REGATTR_BYP_MASK                     (0x80U)
#define IEE_REGATTR_BYP_SHIFT                    (7U)
/*! BYP
 *  0b0..use MD field
 *  0b1..Bypass AES, no encrypt/decrypt
 */
#define IEE_REGATTR_BYP(x)                       (((uint32_t)(((uint32_t)(x)) << IEE_REGATTR_BYP_SHIFT)) & IEE_REGATTR_BYP_MASK)
/*! @} */

/* The count of IEE_REGATTR */
#define IEE_REGATTR_COUNT                        (8U)

/*! @name REGPO - IEE Region 0 Page Offset Register..IEE Region 7 Page Offset Register */
/*! @{ */

#define IEE_REGPO_PGOFF_MASK                     (0xFFFFFFU)
#define IEE_REGPO_PGOFF_SHIFT                    (0U)
#define IEE_REGPO_PGOFF(x)                       (((uint32_t)(((uint32_t)(x)) << IEE_REGPO_PGOFF_SHIFT)) & IEE_REGPO_PGOFF_MASK)
/*! @} */

/* The count of IEE_REGPO */
#define IEE_REGPO_COUNT                          (8U)

/*! @name REGKEY1 - IEE Region 0 Key 1 Register..IEE Region 7 Key 1 Register */
/*! @{ */

#define IEE_REGKEY1_KEY1_MASK                    (0xFFFFFFFFU)
#define IEE_REGKEY1_KEY1_SHIFT                   (0U)
#define IEE_REGKEY1_KEY1(x)                      (((uint32_t)(((uint32_t)(x)) << IEE_REGKEY1_KEY1_SHIFT)) & IEE_REGKEY1_KEY1_MASK)
/*! @} */

/* The count of IEE_REGKEY1 */
#define IEE_REGKEY1_COUNT                        (8U)

/* The count of IEE_REGKEY1 */
#define IEE_REGKEY1_COUNT2                       (8U)

/*! @name REGKEY2 - IEE Region 0 Key 2 Register..IEE Region 7 Key 2 Register */
/*! @{ */

#define IEE_REGKEY2_KEY2_MASK                    (0xFFFFFFFFU)
#define IEE_REGKEY2_KEY2_SHIFT                   (0U)
#define IEE_REGKEY2_KEY2(x)                      (((uint32_t)(((uint32_t)(x)) << IEE_REGKEY2_KEY2_SHIFT)) & IEE_REGKEY2_KEY2_MASK)
/*! @} */

/* The count of IEE_REGKEY2 */
#define IEE_REGKEY2_COUNT                        (8U)

/* The count of IEE_REGKEY2 */
#define IEE_REGKEY2_COUNT2                       (8U)

/*! @name AES_TST_DB - IEE AES Test Mode Data Buffer */
/*! @{ */

#define IEE_AES_TST_DB_AES_TST_DB0_MASK          (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB0_SHIFT         (0U)
#define IEE_AES_TST_DB_AES_TST_DB0(x)            (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB0_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB0_MASK)

#define IEE_AES_TST_DB_AES_TST_DB1_MASK          (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB1_SHIFT         (0U)
#define IEE_AES_TST_DB_AES_TST_DB1(x)            (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB1_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB1_MASK)

#define IEE_AES_TST_DB_AES_TST_DB2_MASK          (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB2_SHIFT         (0U)
#define IEE_AES_TST_DB_AES_TST_DB2(x)            (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB2_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB2_MASK)

#define IEE_AES_TST_DB_AES_TST_DB3_MASK          (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB3_SHIFT         (0U)
#define IEE_AES_TST_DB_AES_TST_DB3(x)            (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB3_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB3_MASK)

#define IEE_AES_TST_DB_AES_TST_DB4_MASK          (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB4_SHIFT         (0U)
#define IEE_AES_TST_DB_AES_TST_DB4(x)            (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB4_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB4_MASK)

#define IEE_AES_TST_DB_AES_TST_DB5_MASK          (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB5_SHIFT         (0U)
#define IEE_AES_TST_DB_AES_TST_DB5(x)            (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB5_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB5_MASK)

#define IEE_AES_TST_DB_AES_TST_DB6_MASK          (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB6_SHIFT         (0U)
#define IEE_AES_TST_DB_AES_TST_DB6(x)            (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB6_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB6_MASK)

#define IEE_AES_TST_DB_AES_TST_DB7_MASK          (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB7_SHIFT         (0U)
#define IEE_AES_TST_DB_AES_TST_DB7(x)            (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB7_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB7_MASK)

#define IEE_AES_TST_DB_AES_TST_DB8_MASK          (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB8_SHIFT         (0U)
#define IEE_AES_TST_DB_AES_TST_DB8(x)            (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB8_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB8_MASK)

#define IEE_AES_TST_DB_AES_TST_DB9_MASK          (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB9_SHIFT         (0U)
#define IEE_AES_TST_DB_AES_TST_DB9(x)            (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB9_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB9_MASK)

#define IEE_AES_TST_DB_AES_TST_DB10_MASK         (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB10_SHIFT        (0U)
#define IEE_AES_TST_DB_AES_TST_DB10(x)           (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB10_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB10_MASK)

#define IEE_AES_TST_DB_AES_TST_DB11_MASK         (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB11_SHIFT        (0U)
#define IEE_AES_TST_DB_AES_TST_DB11(x)           (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB11_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB11_MASK)

#define IEE_AES_TST_DB_AES_TST_DB12_MASK         (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB12_SHIFT        (0U)
#define IEE_AES_TST_DB_AES_TST_DB12(x)           (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB12_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB12_MASK)

#define IEE_AES_TST_DB_AES_TST_DB13_MASK         (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB13_SHIFT        (0U)
#define IEE_AES_TST_DB_AES_TST_DB13(x)           (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB13_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB13_MASK)

#define IEE_AES_TST_DB_AES_TST_DB14_MASK         (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB14_SHIFT        (0U)
#define IEE_AES_TST_DB_AES_TST_DB14(x)           (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB14_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB14_MASK)

#define IEE_AES_TST_DB_AES_TST_DB15_MASK         (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB15_SHIFT        (0U)
#define IEE_AES_TST_DB_AES_TST_DB15(x)           (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB15_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB15_MASK)

#define IEE_AES_TST_DB_AES_TST_DB16_MASK         (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB16_SHIFT        (0U)
#define IEE_AES_TST_DB_AES_TST_DB16(x)           (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB16_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB16_MASK)

#define IEE_AES_TST_DB_AES_TST_DB17_MASK         (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB17_SHIFT        (0U)
#define IEE_AES_TST_DB_AES_TST_DB17(x)           (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB17_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB17_MASK)

#define IEE_AES_TST_DB_AES_TST_DB18_MASK         (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB18_SHIFT        (0U)
#define IEE_AES_TST_DB_AES_TST_DB18(x)           (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB18_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB18_MASK)

#define IEE_AES_TST_DB_AES_TST_DB19_MASK         (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB19_SHIFT        (0U)
#define IEE_AES_TST_DB_AES_TST_DB19(x)           (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB19_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB19_MASK)

#define IEE_AES_TST_DB_AES_TST_DB20_MASK         (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB20_SHIFT        (0U)
#define IEE_AES_TST_DB_AES_TST_DB20(x)           (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB20_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB20_MASK)

#define IEE_AES_TST_DB_AES_TST_DB21_MASK         (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB21_SHIFT        (0U)
#define IEE_AES_TST_DB_AES_TST_DB21(x)           (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB21_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB21_MASK)

#define IEE_AES_TST_DB_AES_TST_DB22_MASK         (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB22_SHIFT        (0U)
#define IEE_AES_TST_DB_AES_TST_DB22(x)           (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB22_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB22_MASK)

#define IEE_AES_TST_DB_AES_TST_DB23_MASK         (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB23_SHIFT        (0U)
#define IEE_AES_TST_DB_AES_TST_DB23(x)           (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB23_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB23_MASK)

#define IEE_AES_TST_DB_AES_TST_DB24_MASK         (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB24_SHIFT        (0U)
#define IEE_AES_TST_DB_AES_TST_DB24(x)           (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB24_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB24_MASK)

#define IEE_AES_TST_DB_AES_TST_DB25_MASK         (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB25_SHIFT        (0U)
#define IEE_AES_TST_DB_AES_TST_DB25(x)           (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB25_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB25_MASK)

#define IEE_AES_TST_DB_AES_TST_DB26_MASK         (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB26_SHIFT        (0U)
#define IEE_AES_TST_DB_AES_TST_DB26(x)           (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB26_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB26_MASK)

#define IEE_AES_TST_DB_AES_TST_DB27_MASK         (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB27_SHIFT        (0U)
#define IEE_AES_TST_DB_AES_TST_DB27(x)           (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB27_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB27_MASK)

#define IEE_AES_TST_DB_AES_TST_DB28_MASK         (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB28_SHIFT        (0U)
#define IEE_AES_TST_DB_AES_TST_DB28(x)           (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB28_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB28_MASK)

#define IEE_AES_TST_DB_AES_TST_DB29_MASK         (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB29_SHIFT        (0U)
#define IEE_AES_TST_DB_AES_TST_DB29(x)           (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB29_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB29_MASK)

#define IEE_AES_TST_DB_AES_TST_DB30_MASK         (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB30_SHIFT        (0U)
#define IEE_AES_TST_DB_AES_TST_DB30(x)           (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB30_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB30_MASK)

#define IEE_AES_TST_DB_AES_TST_DB31_MASK         (0xFFFFFFFFU)
#define IEE_AES_TST_DB_AES_TST_DB31_SHIFT        (0U)
#define IEE_AES_TST_DB_AES_TST_DB31(x)           (((uint32_t)(((uint32_t)(x)) << IEE_AES_TST_DB_AES_TST_DB31_SHIFT)) & IEE_AES_TST_DB_AES_TST_DB31_MASK)
/*! @} */

/* The count of IEE_AES_TST_DB */
#define IEE_AES_TST_DB_COUNT                     (32U)


/*!
 * @}
 */ /* end of group IEE_Register_Masks */


/*!
 * @}
 */ /* end of group IEE_Peripheral_Access_Layer */


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


#endif  /* PERI_IEE_H_ */

