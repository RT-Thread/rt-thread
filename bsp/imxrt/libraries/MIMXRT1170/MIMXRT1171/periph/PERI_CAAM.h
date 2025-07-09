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
**         CMSIS Peripheral Access Layer for CAAM
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
 * @file PERI_CAAM.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for CAAM
 *
 * CMSIS Peripheral Access Layer for CAAM
 */

#if !defined(PERI_CAAM_H_)
#define PERI_CAAM_H_                             /**< Symbol preventing repeated inclusion */

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
   -- CAAM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CAAM_Peripheral_Access_Layer CAAM Peripheral Access Layer
 * @{
 */

/** CAAM - Size of Registers Arrays */
#define CAAM_JRADID_COUNT                         4u
#define CAAM_RTICADID_COUNT                       4u
#define CAAM_DECONDID_COUNT                       1u
#define CAAM_JRNSMVBAR_COUNT                      4u
#define CAAM_AID_CNTS_COUNT                       1u
#define CAAM_MPPKRA_COUNT                         64u
#define CAAM_MPMRA_COUNT                          32u
#define CAAM_MPTESTRA_COUNT                       32u
#define CAAM_JDKEKRA_COUNT                        8u
#define CAAM_TDKEKRA_COUNT                        8u
#define CAAM_TDSKRA_COUNT                         8u
#define CAAM_RTENTA_COUNT                         16u
#define CAAM_PX_PG0_COUNT                         16u
#define CAAM_SMWPJR_ARRAY_COUNT                   4u
#define CAAM_HTA_COUNT                            1u
#define CAAM_JRJDDAA_COUNT                        1u
#define CAAM_JOBRING_JRAAA_COUNT                  4u
#define CAAM_JOBRING_PX_JR_COUNT                  16u
#define CAAM_JOBRING_COUNT                        4u
#define CAAM_RMAAB_COUNT                          4u
#define CAAM_RMAAB_RM_COUNT                       2u
#define CAAM_RAMD_COUNT                           4u
#define CAAM_RAMD_RAMD_COUNT                      2u
#define CAAM_RAMD_RAMD_RAMDE_COUNT                32u
#define CAAM_DC_CDC1CTXR_B_COUNT                  16u
#define CAAM_DC_CDC1KEYR_I_COUNT                  8u
#define CAAM_DC_CDC2CTXR_I_COUNT                  18u
#define CAAM_DC_CDC2KEYR_I_COUNT                  32u
#define CAAM_DC_DDMTHB_COUNT                      4u
#define CAAM_DC_DDGTR_COUNT                       1u
#define CAAM_DC_DDSTR_COUNT                       1u
#define CAAM_DC_DDDESB_COUNT                      64u
#define CAAM_DC_COUNT                             1u

/** CAAM - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[4];
  __IO uint32_t MCFGR;                             /**< Master Configuration Register, offset: 0x4 */
  __IO uint32_t PAGE0_SDID;                        /**< Page 0 SDID Register, offset: 0x8 */
  __IO uint32_t SCFGR;                             /**< Security Configuration Register, offset: 0xC */
  struct {                                         /* offset: 0x10, array step: 0x8 */
    __IO uint32_t JRDID_MS;                          /**< Job Ring 0 DID Register - most significant half..Job Ring 3 DID Register - most significant half, array offset: 0x10, array step: 0x8 */
    __IO uint32_t JRDID_LS;                          /**< Job Ring 0 DID Register - least significant half..Job Ring 3 DID Register - least significant half, array offset: 0x14, array step: 0x8 */
  } JRADID[CAAM_JRADID_COUNT];
       uint8_t RESERVED_1[40];
  __IO uint32_t DEBUGCTL;                          /**< Debug Control Register, offset: 0x58 */
  __IO uint32_t JRSTARTR;                          /**< Job Ring Start Register, offset: 0x5C */
  __IO uint32_t RTIC_OWN;                          /**< RTIC OWN Register, offset: 0x60 */
  struct {                                         /* offset: 0x64, array step: 0x8 */
    __IO uint32_t RTIC_DID;                          /**< RTIC DID Register for Block A..RTIC DID Register for Block D, array offset: 0x64, array step: 0x8 */
         uint8_t RESERVED_0[4];
  } RTICADID[CAAM_RTICADID_COUNT];
       uint8_t RESERVED_2[16];
  __IO uint32_t DECORSR;                           /**< DECO Request Source Register, offset: 0x94 */
       uint8_t RESERVED_3[4];
  __IO uint32_t DECORR;                            /**< DECO Request Register, offset: 0x9C */
  struct {                                         /* offset: 0xA0, array step: 0x8 */
    __IO uint32_t DECODID_MS;                        /**< DECO0 DID Register - most significant half, array offset: 0xA0, array step: 0x8 */
    __IO uint32_t DECODID_LS;                        /**< DECO0 DID Register - least significant half, array offset: 0xA4, array step: 0x8 */
  } DECONDID[CAAM_DECONDID_COUNT];
       uint8_t RESERVED_4[120];
  __IO uint32_t DAR;                               /**< DECO Availability Register, offset: 0x120 */
  __O  uint32_t DRR;                               /**< DECO Reset Register, offset: 0x124 */
       uint8_t RESERVED_5[92];
  struct {                                         /* offset: 0x184, array step: 0x8 */
    __IO uint32_t JRSMVBAR;                          /**< Job Ring 0 Secure Memory Virtual Base Address Register..Job Ring 3 Secure Memory Virtual Base Address Register, array offset: 0x184, array step: 0x8 */
         uint8_t RESERVED_0[4];
  } JRNSMVBAR[CAAM_JRNSMVBAR_COUNT];
       uint8_t RESERVED_6[124];
  __IO uint32_t PBSL;                              /**< Peak Bandwidth Smoothing Limit Register, offset: 0x220 */
       uint8_t RESERVED_7[28];
  struct {                                         /* offset: 0x240, array step: 0x10 */
    __I  uint32_t DMA_AIDL_MAP_MS;                   /**< DMA0_AIDL_MAP_MS, array offset: 0x240, array step: 0x10 */
    __I  uint32_t DMA_AIDL_MAP_LS;                   /**< DMA0_AIDL_MAP_LS, array offset: 0x244, array step: 0x10 */
    __I  uint32_t DMA_AIDM_MAP_MS;                   /**< DMA0_AIDM_MAP_MS, array offset: 0x248, array step: 0x10 */
    __I  uint32_t DMA_AIDM_MAP_LS;                   /**< DMA0_AIDM_MAP_LS, array offset: 0x24C, array step: 0x10 */
  } AID_CNTS[CAAM_AID_CNTS_COUNT];
  __I  uint32_t DMA0_AID_ENB;                      /**< DMA0 AXI ID Enable Register, offset: 0x250 */
       uint8_t RESERVED_8[12];
  __IO uint64_t DMA0_ARD_TC;                       /**< DMA0 AXI Read Timing Check Register, offset: 0x260 */
       uint8_t RESERVED_9[4];
  __IO uint32_t DMA0_ARD_LAT;                      /**< DMA0 Read Timing Check Latency Register, offset: 0x26C */
  __IO uint64_t DMA0_AWR_TC;                       /**< DMA0 AXI Write Timing Check Register, offset: 0x270 */
       uint8_t RESERVED_10[4];
  __IO uint32_t DMA0_AWR_LAT;                      /**< DMA0 Write Timing Check Latency Register, offset: 0x27C */
       uint8_t RESERVED_11[128];
  __IO uint8_t MPPKR[CAAM_MPPKRA_COUNT];           /**< Manufacturing Protection Private Key Register, array offset: 0x300, array step: 0x1 */
       uint8_t RESERVED_12[64];
  __IO uint8_t MPMR[CAAM_MPMRA_COUNT];             /**< Manufacturing Protection Message Register, array offset: 0x380, array step: 0x1 */
       uint8_t RESERVED_13[32];
  __I  uint8_t MPTESTR[CAAM_MPTESTRA_COUNT];       /**< Manufacturing Protection Test Register, array offset: 0x3C0, array step: 0x1 */
       uint8_t RESERVED_14[24];
  __I  uint32_t MPECC;                             /**< Manufacturing Protection ECC Register, offset: 0x3F8 */
       uint8_t RESERVED_15[4];
  __IO uint32_t JDKEKR[CAAM_JDKEKRA_COUNT];        /**< Job Descriptor Key Encryption Key Register, array offset: 0x400, array step: 0x4 */
  __IO uint32_t TDKEKR[CAAM_TDKEKRA_COUNT];        /**< Trusted Descriptor Key Encryption Key Register, array offset: 0x420, array step: 0x4 */
  __IO uint32_t TDSKR[CAAM_TDSKRA_COUNT];          /**< Trusted Descriptor Signing Key Register, array offset: 0x440, array step: 0x4 */
       uint8_t RESERVED_16[128];
  __IO uint64_t SKNR;                              /**< Secure Key Nonce Register, offset: 0x4E0 */
       uint8_t RESERVED_17[36];
  __I  uint32_t DMA_STA;                           /**< DMA Status Register, offset: 0x50C */
  __I  uint32_t DMA_X_AID_7_4_MAP;                 /**< DMA_X_AID_7_4_MAP, offset: 0x510 */
  __I  uint32_t DMA_X_AID_3_0_MAP;                 /**< DMA_X_AID_3_0_MAP, offset: 0x514 */
  __I  uint32_t DMA_X_AID_15_12_MAP;               /**< DMA_X_AID_15_12_MAP, offset: 0x518 */
  __I  uint32_t DMA_X_AID_11_8_MAP;                /**< DMA_X_AID_11_8_MAP, offset: 0x51C */
       uint8_t RESERVED_18[4];
  __I  uint32_t DMA_X_AID_15_0_EN;                 /**< DMA_X AXI ID Map Enable Register, offset: 0x524 */
       uint8_t RESERVED_19[8];
  __IO uint32_t DMA_X_ARTC_CTL;                    /**< DMA_X AXI Read Timing Check Control Register, offset: 0x530 */
  __IO uint32_t DMA_X_ARTC_LC;                     /**< DMA_X AXI Read Timing Check Late Count Register, offset: 0x534 */
  __IO uint32_t DMA_X_ARTC_SC;                     /**< DMA_X AXI Read Timing Check Sample Count Register, offset: 0x538 */
  __IO uint32_t DMA_X_ARTC_LAT;                    /**< DMA_X Read Timing Check Latency Register, offset: 0x53C */
  __IO uint32_t DMA_X_AWTC_CTL;                    /**< DMA_X AXI Write Timing Check Control Register, offset: 0x540 */
  __IO uint32_t DMA_X_AWTC_LC;                     /**< DMA_X AXI Write Timing Check Late Count Register, offset: 0x544 */
  __IO uint32_t DMA_X_AWTC_SC;                     /**< DMA_X AXI Write Timing Check Sample Count Register, offset: 0x548 */
  __IO uint32_t DMA_X_AWTC_LAT;                    /**< DMA_X Write Timing Check Latency Register, offset: 0x54C */
       uint8_t RESERVED_20[176];
  __IO uint32_t RTMCTL;                            /**< RNG TRNG Miscellaneous Control Register, offset: 0x600 */
  __IO uint32_t RTSCMISC;                          /**< RNG TRNG Statistical Check Miscellaneous Register, offset: 0x604 */
  __IO uint32_t RTPKRRNG;                          /**< RNG TRNG Poker Range Register, offset: 0x608 */
  union {                                          /* offset: 0x60C */
    __IO uint32_t RTPKRMAX;                          /**< RNG TRNG Poker Maximum Limit Register, offset: 0x60C */
    __I  uint32_t RTPKRSQ;                           /**< RNG TRNG Poker Square Calculation Result Register, offset: 0x60C */
  };
  __IO uint32_t RTSDCTL;                           /**< RNG TRNG Seed Control Register, offset: 0x610 */
  union {                                          /* offset: 0x614 */
    __IO uint32_t RTSBLIM;                           /**< RNG TRNG Sparse Bit Limit Register, offset: 0x614 */
    __I  uint32_t RTTOTSAM;                          /**< RNG TRNG Total Samples Register, offset: 0x614 */
  };
  __IO uint32_t RTFRQMIN;                          /**< RNG TRNG Frequency Count Minimum Limit Register, offset: 0x618 */
  union {                                          /* offset: 0x61C */
    struct {                                         /* offset: 0x61C */
      __I  uint32_t RTFRQCNT;                          /**< RNG TRNG Frequency Count Register, offset: 0x61C */
      __I  uint32_t RTSCMC;                            /**< RNG TRNG Statistical Check Monobit Count Register, offset: 0x620 */
      __I  uint32_t RTSCR1C;                           /**< RNG TRNG Statistical Check Run Length 1 Count Register, offset: 0x624 */
      __I  uint32_t RTSCR2C;                           /**< RNG TRNG Statistical Check Run Length 2 Count Register, offset: 0x628 */
      __I  uint32_t RTSCR3C;                           /**< RNG TRNG Statistical Check Run Length 3 Count Register, offset: 0x62C */
      __I  uint32_t RTSCR4C;                           /**< RNG TRNG Statistical Check Run Length 4 Count Register, offset: 0x630 */
      __I  uint32_t RTSCR5C;                           /**< RNG TRNG Statistical Check Run Length 5 Count Register, offset: 0x634 */
      __I  uint32_t RTSCR6PC;                          /**< RNG TRNG Statistical Check Run Length 6+ Count Register, offset: 0x638 */
    } COUNT;
    struct {                                         /* offset: 0x61C */
      __IO uint32_t RTFRQMAX;                          /**< RNG TRNG Frequency Count Maximum Limit Register, offset: 0x61C */
      __IO uint32_t RTSCML;                            /**< RNG TRNG Statistical Check Monobit Limit Register, offset: 0x620 */
      __IO uint32_t RTSCR1L;                           /**< RNG TRNG Statistical Check Run Length 1 Limit Register, offset: 0x624 */
      __IO uint32_t RTSCR2L;                           /**< RNG TRNG Statistical Check Run Length 2 Limit Register, offset: 0x628 */
      __IO uint32_t RTSCR3L;                           /**< RNG TRNG Statistical Check Run Length 3 Limit Register, offset: 0x62C */
      __IO uint32_t RTSCR4L;                           /**< RNG TRNG Statistical Check Run Length 4 Limit Register, offset: 0x630 */
      __IO uint32_t RTSCR5L;                           /**< RNG TRNG Statistical Check Run Length 5 Limit Register, offset: 0x634 */
      __IO uint32_t RTSCR6PL;                          /**< RNG TRNG Statistical Check Run Length 6+ Limit Register, offset: 0x638 */
    } LIMIT;
  };
  __I  uint32_t RTSTATUS;                          /**< RNG TRNG Status Register, offset: 0x63C */
  __I  uint32_t RTENT[CAAM_RTENTA_COUNT];          /**< RNG TRNG Entropy Read Register, array offset: 0x640, array step: 0x4 */
  __I  uint32_t RTPKRCNT10;                        /**< RNG TRNG Statistical Check Poker Count 1 and 0 Register, offset: 0x680 */
  __I  uint32_t RTPKRCNT32;                        /**< RNG TRNG Statistical Check Poker Count 3 and 2 Register, offset: 0x684 */
  __I  uint32_t RTPKRCNT54;                        /**< RNG TRNG Statistical Check Poker Count 5 and 4 Register, offset: 0x688 */
  __I  uint32_t RTPKRCNT76;                        /**< RNG TRNG Statistical Check Poker Count 7 and 6 Register, offset: 0x68C */
  __I  uint32_t RTPKRCNT98;                        /**< RNG TRNG Statistical Check Poker Count 9 and 8 Register, offset: 0x690 */
  __I  uint32_t RTPKRCNTBA;                        /**< RNG TRNG Statistical Check Poker Count B and A Register, offset: 0x694 */
  __I  uint32_t RTPKRCNTDC;                        /**< RNG TRNG Statistical Check Poker Count D and C Register, offset: 0x698 */
  __I  uint32_t RTPKRCNTFE;                        /**< RNG TRNG Statistical Check Poker Count F and E Register, offset: 0x69C */
       uint8_t RESERVED_21[32];
  __I  uint32_t RDSTA;                             /**< RNG DRNG Status Register, offset: 0x6C0 */
       uint8_t RESERVED_22[12];
  __I  uint32_t RDINT0;                            /**< RNG DRNG State Handle 0 Reseed Interval Register, offset: 0x6D0 */
  __I  uint32_t RDINT1;                            /**< RNG DRNG State Handle 1 Reseed Interval Register, offset: 0x6D4 */
       uint8_t RESERVED_23[8];
  __IO uint32_t RDHCNTL;                           /**< RNG DRNG Hash Control Register, offset: 0x6E0 */
  __I  uint32_t RDHDIG;                            /**< RNG DRNG Hash Digest Register, offset: 0x6E4 */
  __O  uint32_t RDHBUF;                            /**< RNG DRNG Hash Buffer Register, offset: 0x6E8 */
       uint8_t RESERVED_24[788];
  struct {                                         /* offset: 0xA00, array step: 0x10 */
    __I  uint32_t PX_SDID_PG0;                       /**< Partition 0 SDID register..Partition 15 SDID register, array offset: 0xA00, array step: 0x10 */
    __IO uint32_t PX_SMAPR_PG0;                      /**< Secure Memory Access Permissions register, array offset: 0xA04, array step: 0x10 */
    __IO uint32_t PX_SMAG2_PG0;                      /**< Secure Memory Access Group Registers, array offset: 0xA08, array step: 0x10 */
    __IO uint32_t PX_SMAG1_PG0;                      /**< Secure Memory Access Group Registers, array offset: 0xA0C, array step: 0x10 */
  } PX_PG0[CAAM_PX_PG0_COUNT];
  __IO uint32_t REIS;                              /**< Recoverable Error Interrupt Status, offset: 0xB00 */
  __IO uint32_t REIE;                              /**< Recoverable Error Interrupt Enable, offset: 0xB04 */
  __I  uint32_t REIF;                              /**< Recoverable Error Interrupt Force, offset: 0xB08 */
  __IO uint32_t REIH;                              /**< Recoverable Error Interrupt Halt, offset: 0xB0C */
       uint8_t RESERVED_25[192];
  __IO uint32_t SMWPJRR[CAAM_SMWPJR_ARRAY_COUNT];  /**< Secure Memory Write Protect Job Ring Register, array offset: 0xBD0, array step: 0x4 */
       uint8_t RESERVED_26[4];
  __O  uint32_t SMCR_PG0;                          /**< Secure Memory Command Register, offset: 0xBE4 */
       uint8_t RESERVED_27[4];
  __I  uint32_t SMCSR_PG0;                         /**< Secure Memory Command Status Register, offset: 0xBEC */
       uint8_t RESERVED_28[8];
  __I  uint32_t CAAMVID_MS_TRAD;                   /**< CAAM Version ID Register, most-significant half, offset: 0xBF8 */
  __I  uint32_t CAAMVID_LS_TRAD;                   /**< CAAM Version ID Register, least-significant half, offset: 0xBFC */
  struct {                                         /* offset: 0xC00, array step: 0x20 */
    __I  uint64_t HT_JD_ADDR;                        /**< Holding Tank 0 Job Descriptor Address, array offset: 0xC00, array step: 0x20 */
    __I  uint64_t HT_SD_ADDR;                        /**< Holding Tank 0 Shared Descriptor Address, array offset: 0xC08, array step: 0x20 */
    __I  uint32_t HT_JQ_CTRL_MS;                     /**< Holding Tank 0 Job Queue Control, most-significant half, array offset: 0xC10, array step: 0x20 */
    __I  uint32_t HT_JQ_CTRL_LS;                     /**< Holding Tank 0 Job Queue Control, least-significant half, array offset: 0xC14, array step: 0x20 */
         uint8_t RESERVED_0[4];
    __I  uint32_t HT_STATUS;                         /**< Holding Tank Status, array offset: 0xC1C, array step: 0x20 */
  } HTA[CAAM_HTA_COUNT];
       uint8_t RESERVED_29[4];
  __IO uint32_t JQ_DEBUG_SEL;                      /**< Job Queue Debug Select Register, offset: 0xC24 */
       uint8_t RESERVED_30[404];
  __I  uint32_t JRJIDU_LS;                         /**< Job Ring Job IDs in Use Register, least-significant half, offset: 0xDBC */
  __I  uint32_t JRJDJIFBC;                         /**< Job Ring Job-Done Job ID FIFO BC, offset: 0xDC0 */
  __I  uint32_t JRJDJIF;                           /**< Job Ring Job-Done Job ID FIFO, offset: 0xDC4 */
       uint8_t RESERVED_31[28];
  __I  uint32_t JRJDS1;                            /**< Job Ring Job-Done Source 1, offset: 0xDE4 */
       uint8_t RESERVED_32[24];
  __I  uint64_t JRJDDA[CAAM_JRJDDAA_COUNT];        /**< Job Ring Job-Done Descriptor Address 0 Register, array offset: 0xE00, array step: 0x8 */
       uint8_t RESERVED_33[408];
  __I  uint32_t CRNR_MS;                           /**< CHA Revision Number Register, most-significant half, offset: 0xFA0 */
  __I  uint32_t CRNR_LS;                           /**< CHA Revision Number Register, least-significant half, offset: 0xFA4 */
  __I  uint32_t CTPR_MS;                           /**< Compile Time Parameters Register, most-significant half, offset: 0xFA8 */
  __I  uint32_t CTPR_LS;                           /**< Compile Time Parameters Register, least-significant half, offset: 0xFAC */
       uint8_t RESERVED_34[4];
  __I  uint32_t SMSTA;                             /**< Secure Memory Status Register, offset: 0xFB4 */
       uint8_t RESERVED_35[4];
  __I  uint32_t SMPO;                              /**< Secure Memory Partition Owners Register, offset: 0xFBC */
  __I  uint64_t FAR;                               /**< Fault Address Register, offset: 0xFC0 */
  __I  uint32_t FADID;                             /**< Fault Address DID Register, offset: 0xFC8 */
  __I  uint32_t FADR;                              /**< Fault Address Detail Register, offset: 0xFCC */
       uint8_t RESERVED_36[4];
  __I  uint32_t CSTA;                              /**< CAAM Status Register, offset: 0xFD4 */
  __I  uint32_t SMVID_MS;                          /**< Secure Memory Version ID Register, most-significant half, offset: 0xFD8 */
  __I  uint32_t SMVID_LS;                          /**< Secure Memory Version ID Register, least-significant half, offset: 0xFDC */
  __I  uint32_t RVID;                              /**< RTIC Version ID Register, offset: 0xFE0 */
  __I  uint32_t CCBVID;                            /**< CHA Cluster Block Version ID Register, offset: 0xFE4 */
  __I  uint32_t CHAVID_MS;                         /**< CHA Version ID Register, most-significant half, offset: 0xFE8 */
  __I  uint32_t CHAVID_LS;                         /**< CHA Version ID Register, least-significant half, offset: 0xFEC */
  __I  uint32_t CHANUM_MS;                         /**< CHA Number Register, most-significant half, offset: 0xFF0 */
  __I  uint32_t CHANUM_LS;                         /**< CHA Number Register, least-significant half, offset: 0xFF4 */
  __I  uint32_t CAAMVID_MS;                        /**< CAAM Version ID Register, most-significant half, offset: 0xFF8 */
  __I  uint32_t CAAMVID_LS;                        /**< CAAM Version ID Register, least-significant half, offset: 0xFFC */
       uint8_t RESERVED_37[61440];
  struct {                                         /* offset: 0x10000, array step: 0x10000 */
    __IO uint64_t IRBAR_JR;                          /**< Input Ring Base Address Register for Job Ring 0..Input Ring Base Address Register for Job Ring 3, array offset: 0x10000, array step: 0x10000 */
         uint8_t RESERVED_0[4];
    __IO uint32_t IRSR_JR;                           /**< Input Ring Size Register for Job Ring 0..Input Ring Size Register for Job Ring 3, array offset: 0x1000C, array step: 0x10000 */
         uint8_t RESERVED_1[4];
    __IO uint32_t IRSAR_JR;                          /**< Input Ring Slots Available Register for Job Ring 0..Input Ring Slots Available Register for Job Ring 3, array offset: 0x10014, array step: 0x10000 */
         uint8_t RESERVED_2[4];
    __IO uint32_t IRJAR_JR;                          /**< Input Ring Jobs Added Register for Job Ring0..Input Ring Jobs Added Register for Job Ring3, array offset: 0x1001C, array step: 0x10000 */
    __IO uint64_t ORBAR_JR;                          /**< Output Ring Base Address Register for Job Ring 0..Output Ring Base Address Register for Job Ring 3, array offset: 0x10020, array step: 0x10000 */
         uint8_t RESERVED_3[4];
    __IO uint32_t ORSR_JR;                           /**< Output Ring Size Register for Job Ring 0..Output Ring Size Register for Job Ring 3, array offset: 0x1002C, array step: 0x10000 */
         uint8_t RESERVED_4[4];
    __IO uint32_t ORJRR_JR;                          /**< Output Ring Jobs Removed Register for Job Ring 0..Output Ring Jobs Removed Register for Job Ring 3, array offset: 0x10034, array step: 0x10000 */
         uint8_t RESERVED_5[4];
    __IO uint32_t ORSFR_JR;                          /**< Output Ring Slots Full Register for Job Ring 0..Output Ring Slots Full Register for Job Ring 3, array offset: 0x1003C, array step: 0x10000 */
         uint8_t RESERVED_6[4];
    __I  uint32_t JRSTAR_JR;                         /**< Job Ring Output Status Register for Job Ring 0..Job Ring Output Status Register for Job Ring 3, array offset: 0x10044, array step: 0x10000 */
         uint8_t RESERVED_7[4];
    __IO uint32_t JRINTR_JR;                         /**< Job Ring Interrupt Status Register for Job Ring 0..Job Ring Interrupt Status Register for Job Ring 3, array offset: 0x1004C, array step: 0x10000 */
    __IO uint32_t JRCFGR_JR_MS;                      /**< Job Ring Configuration Register for Job Ring 0, most-significant half..Job Ring Configuration Register for Job Ring 3, most-significant half, array offset: 0x10050, array step: 0x10000 */
    __IO uint32_t JRCFGR_JR_LS;                      /**< Job Ring Configuration Register for Job Ring 0, least-significant half..Job Ring Configuration Register for Job Ring 3, least-significant half, array offset: 0x10054, array step: 0x10000 */
         uint8_t RESERVED_8[4];
    __IO uint32_t IRRIR_JR;                          /**< Input Ring Read Index Register for Job Ring 0..Input Ring Read Index Register for Job Ring 3, array offset: 0x1005C, array step: 0x10000 */
         uint8_t RESERVED_9[4];
    __IO uint32_t ORWIR_JR;                          /**< Output Ring Write Index Register for Job Ring 0..Output Ring Write Index Register for Job Ring 3, array offset: 0x10064, array step: 0x10000 */
         uint8_t RESERVED_10[4];
    __O  uint32_t JRCR_JR;                           /**< Job Ring Command Register for Job Ring 0..Job Ring Command Register for Job Ring 3, array offset: 0x1006C, array step: 0x10000 */
         uint8_t RESERVED_11[1684];
    __I  uint32_t JRAAV;                             /**< Job Ring 0 Address-Array Valid Register..Job Ring 3 Address-Array Valid Register, array offset: 0x10704, array step: 0x10000 */
         uint8_t RESERVED_12[248];
    __I  uint64_t JRAAA[CAAM_JOBRING_JRAAA_COUNT];   /**< Job Ring 0 Address-Array Address 0 Register..Job Ring 3 Address-Array Address 3 Register, array offset: 0x10800, array step: index*0x10000, index2*0x8 */
         uint8_t RESERVED_13[480];
    struct {                                         /* offset: 0x10A00, array step: index*0x10000, index2*0x10 */
      __I  uint32_t PX_SDID_JR;                        /**< Partition 0 SDID register..Partition 15 SDID register, array offset: 0x10A00, array step: index*0x10000, index2*0x10 */
      __IO uint32_t PX_SMAPR_JR;                       /**< Secure Memory Access Permissions register, array offset: 0x10A04, array step: index*0x10000, index2*0x10 */
      __IO uint32_t PX_SMAG2_JR;                       /**< Secure Memory Access Group Registers, array offset: 0x10A08, array step: index*0x10000, index2*0x10 */
      __IO uint32_t PX_SMAG1_JR;                       /**< Secure Memory Access Group Registers, array offset: 0x10A0C, array step: index*0x10000, index2*0x10 */
    } PX_JR[CAAM_JOBRING_PX_JR_COUNT];
         uint8_t RESERVED_14[228];
    __O  uint32_t SMCR_JR;                           /**< Secure Memory Command Register, array offset: 0x10BE4, array step: 0x10000 */
         uint8_t RESERVED_15[4];
    __I  uint32_t SMCSR_JR;                          /**< Secure Memory Command Status Register, array offset: 0x10BEC, array step: 0x10000 */
         uint8_t RESERVED_16[528];
    __I  uint32_t REIR0JR;                           /**< Recoverable Error Interrupt Record 0 for Job Ring 0..Recoverable Error Interrupt Record 0 for Job Ring 3, array offset: 0x10E00, array step: 0x10000 */
         uint8_t RESERVED_17[4];
    __I  uint64_t REIR2JR;                           /**< Recoverable Error Interrupt Record 2 for Job Ring 0..Recoverable Error Interrupt Record 2 for Job Ring 3, array offset: 0x10E08, array step: 0x10000 */
    __I  uint32_t REIR4JR;                           /**< Recoverable Error Interrupt Record 4 for Job Ring 0..Recoverable Error Interrupt Record 4 for Job Ring 3, array offset: 0x10E10, array step: 0x10000 */
    __I  uint32_t REIR5JR;                           /**< Recoverable Error Interrupt Record 5 for Job Ring 0..Recoverable Error Interrupt Record 5 for Job Ring 3, array offset: 0x10E14, array step: 0x10000 */
         uint8_t RESERVED_18[392];
    __I  uint32_t CRNR_MS_JR;                        /**< CHA Revision Number Register, most-significant half, array offset: 0x10FA0, array step: 0x10000 */
    __I  uint32_t CRNR_LS_JR;                        /**< CHA Revision Number Register, least-significant half, array offset: 0x10FA4, array step: 0x10000 */
    __I  uint32_t CTPR_MS_JR;                        /**< Compile Time Parameters Register, most-significant half, array offset: 0x10FA8, array step: 0x10000 */
    __I  uint32_t CTPR_LS_JR;                        /**< Compile Time Parameters Register, least-significant half, array offset: 0x10FAC, array step: 0x10000 */
         uint8_t RESERVED_19[4];
    __I  uint32_t SMSTA_JR;                          /**< Secure Memory Status Register, array offset: 0x10FB4, array step: 0x10000 */
         uint8_t RESERVED_20[4];
    __I  uint32_t SMPO_JR;                           /**< Secure Memory Partition Owners Register, array offset: 0x10FBC, array step: 0x10000 */
    __I  uint64_t FAR_JR;                            /**< Fault Address Register, array offset: 0x10FC0, array step: 0x10000 */
    __I  uint32_t FADID_JR;                          /**< Fault Address DID Register, array offset: 0x10FC8, array step: 0x10000 */
    __I  uint32_t FADR_JR;                           /**< Fault Address Detail Register, array offset: 0x10FCC, array step: 0x10000 */
         uint8_t RESERVED_21[4];
    __I  uint32_t CSTA_JR;                           /**< CAAM Status Register, array offset: 0x10FD4, array step: 0x10000 */
    __I  uint32_t SMVID_MS_JR;                       /**< Secure Memory Version ID Register, most-significant half, array offset: 0x10FD8, array step: 0x10000 */
    __I  uint32_t SMVID_LS_JR;                       /**< Secure Memory Version ID Register, least-significant half, array offset: 0x10FDC, array step: 0x10000 */
    __I  uint32_t RVID_JR;                           /**< RTIC Version ID Register, array offset: 0x10FE0, array step: 0x10000 */
    __I  uint32_t CCBVID_JR;                         /**< CHA Cluster Block Version ID Register, array offset: 0x10FE4, array step: 0x10000 */
    __I  uint32_t CHAVID_MS_JR;                      /**< CHA Version ID Register, most-significant half, array offset: 0x10FE8, array step: 0x10000 */
    __I  uint32_t CHAVID_LS_JR;                      /**< CHA Version ID Register, least-significant half, array offset: 0x10FEC, array step: 0x10000 */
    __I  uint32_t CHANUM_MS_JR;                      /**< CHA Number Register, most-significant half, array offset: 0x10FF0, array step: 0x10000 */
    __I  uint32_t CHANUM_LS_JR;                      /**< CHA Number Register, least-significant half, array offset: 0x10FF4, array step: 0x10000 */
    __I  uint32_t CAAMVID_MS_JR;                     /**< CAAM Version ID Register, most-significant half, array offset: 0x10FF8, array step: 0x10000 */
    __I  uint32_t CAAMVID_LS_JR;                     /**< CAAM Version ID Register, least-significant half, array offset: 0x10FFC, array step: 0x10000 */
         uint8_t RESERVED_22[61440];
  } JOBRING[CAAM_JOBRING_COUNT];
       uint8_t RESERVED_38[65540];
  __I  uint32_t RSTA;                              /**< RTIC Status Register, offset: 0x60004 */
       uint8_t RESERVED_39[4];
  __IO uint32_t RCMD;                              /**< RTIC Command Register, offset: 0x6000C */
       uint8_t RESERVED_40[4];
  __IO uint32_t RCTL;                              /**< RTIC Control Register, offset: 0x60014 */
       uint8_t RESERVED_41[4];
  __IO uint32_t RTHR;                              /**< RTIC Throttle Register, offset: 0x6001C */
       uint8_t RESERVED_42[8];
  __IO uint64_t RWDOG;                             /**< RTIC Watchdog Timer, offset: 0x60028 */
       uint8_t RESERVED_43[4];
  __IO uint32_t REND;                              /**< RTIC Endian Register, offset: 0x60034 */
       uint8_t RESERVED_44[200];
  struct {                                         /* offset: 0x60100, array step: index*0x20, index2*0x10 */
    __IO uint64_t RMA;                               /**< RTIC Memory Block A Address 0 Register..RTIC Memory Block D Address 1 Register, array offset: 0x60100, array step: index*0x20, index2*0x10 */
         uint8_t RESERVED_0[4];
    __IO uint32_t RML;                               /**< RTIC Memory Block A Length 0 Register..RTIC Memory Block D Length 1 Register, array offset: 0x6010C, array step: index*0x20, index2*0x10 */
  } RM[CAAM_RMAAB_COUNT][CAAM_RMAAB_RM_COUNT];
       uint8_t RESERVED_45[128];
  __IO uint32_t RMD[CAAM_RAMD_COUNT][CAAM_RAMD_RAMD_COUNT][CAAM_RAMD_RAMD_RAMDE_COUNT]; /**< RTIC Memory Block A Big Endian Hash Result Word 0..RTIC Memory Block D Little Endian Hash Result Word 31, array offset: 0x60200, array step: index*0x100, index2*0x80, index3*0x4 */
       uint8_t RESERVED_46[2048];
  __I  uint32_t REIR0RTIC;                         /**< Recoverable Error Interrupt Record 0 for RTIC, offset: 0x60E00 */
       uint8_t RESERVED_47[4];
  __I  uint64_t REIR2RTIC;                         /**< Recoverable Error Interrupt Record 2 for RTIC, offset: 0x60E08 */
  __I  uint32_t REIR4RTIC;                         /**< Recoverable Error Interrupt Record 4 for RTIC, offset: 0x60E10 */
  __I  uint32_t REIR5RTIC;                         /**< Recoverable Error Interrupt Record 5 for RTIC, offset: 0x60E14 */
       uint8_t RESERVED_48[392];
  __I  uint32_t CRNR_MS_RTIC;                      /**< CHA Revision Number Register, most-significant half, offset: 0x60FA0 */
  __I  uint32_t CRNR_LS_RTIC;                      /**< CHA Revision Number Register, least-significant half, offset: 0x60FA4 */
  __I  uint32_t CTPR_MS_RTIC;                      /**< Compile Time Parameters Register, most-significant half, offset: 0x60FA8 */
  __I  uint32_t CTPR_LS_RTIC;                      /**< Compile Time Parameters Register, least-significant half, offset: 0x60FAC */
       uint8_t RESERVED_49[4];
  __I  uint32_t SMSTA_RTIC;                        /**< Secure Memory Status Register, offset: 0x60FB4 */
       uint8_t RESERVED_50[8];
  __I  uint64_t FAR_RTIC;                          /**< Fault Address Register, offset: 0x60FC0 */
  __I  uint32_t FADID_RTIC;                        /**< Fault Address DID Register, offset: 0x60FC8 */
  __I  uint32_t FADR_RTIC;                         /**< Fault Address Detail Register, offset: 0x60FCC */
       uint8_t RESERVED_51[4];
  __I  uint32_t CSTA_RTIC;                         /**< CAAM Status Register, offset: 0x60FD4 */
  __I  uint32_t SMVID_MS_RTIC;                     /**< Secure Memory Version ID Register, most-significant half, offset: 0x60FD8 */
  __I  uint32_t SMVID_LS_RTIC;                     /**< Secure Memory Version ID Register, least-significant half, offset: 0x60FDC */
  __I  uint32_t RVID_RTIC;                         /**< RTIC Version ID Register, offset: 0x60FE0 */
  __I  uint32_t CCBVID_RTIC;                       /**< CHA Cluster Block Version ID Register, offset: 0x60FE4 */
  __I  uint32_t CHAVID_MS_RTIC;                    /**< CHA Version ID Register, most-significant half, offset: 0x60FE8 */
  __I  uint32_t CHAVID_LS_RTIC;                    /**< CHA Version ID Register, least-significant half, offset: 0x60FEC */
  __I  uint32_t CHANUM_MS_RTIC;                    /**< CHA Number Register, most-significant half, offset: 0x60FF0 */
  __I  uint32_t CHANUM_LS_RTIC;                    /**< CHA Number Register, least-significant half, offset: 0x60FF4 */
  __I  uint32_t CAAMVID_MS_RTIC;                   /**< CAAM Version ID Register, most-significant half, offset: 0x60FF8 */
  __I  uint32_t CAAMVID_LS_RTIC;                   /**< CAAM Version ID Register, least-significant half, offset: 0x60FFC */
       uint8_t RESERVED_52[126976];
  struct {                                         /* offset: 0x80000, array step: 0xE3C */
         uint8_t RESERVED_0[4];
    union {                                          /* offset: 0x80004, array step: 0xE3C */
      __IO uint32_t CC1MR;                             /**< CCB 0 Class 1 Mode Register Format for Non-Public Key Algorithms, array offset: 0x80004, array step: 0xE3C */
      __IO uint32_t CC1MR_PK;                          /**< CCB 0 Class 1 Mode Register Format for Public Key Algorithms, array offset: 0x80004, array step: 0xE3C */
      __IO uint32_t CC1MR_RNG;                         /**< CCB 0 Class 1 Mode Register Format for RNG4, array offset: 0x80004, array step: 0xE3C */
    };
         uint8_t RESERVED_1[4];
    __IO uint32_t CC1KSR;                            /**< CCB 0 Class 1 Key Size Register, array offset: 0x8000C, array step: 0xE3C */
    __IO uint64_t CC1DSR;                            /**< CCB 0 Class 1 Data Size Register, array offset: 0x80010, array step: 0xE3C */
         uint8_t RESERVED_2[4];
    __IO uint32_t CC1ICVSR;                          /**< CCB 0 Class 1 ICV Size Register, array offset: 0x8001C, array step: 0xE3C */
         uint8_t RESERVED_3[20];
    __O  uint32_t CCCTRL;                            /**< CCB 0 CHA Control Register, array offset: 0x80034, array step: 0xE3C */
         uint8_t RESERVED_4[4];
    __IO uint32_t CICTL;                             /**< CCB 0 Interrupt Control Register, array offset: 0x8003C, array step: 0xE3C */
         uint8_t RESERVED_5[4];
    __O  uint32_t CCWR;                              /**< CCB 0 Clear Written Register, array offset: 0x80044, array step: 0xE3C */
    __I  uint32_t CCSTA_MS;                          /**< CCB 0 Status and Error Register, most-significant half, array offset: 0x80048, array step: 0xE3C */
    __I  uint32_t CCSTA_LS;                          /**< CCB 0 Status and Error Register, least-significant half, array offset: 0x8004C, array step: 0xE3C */
         uint8_t RESERVED_6[12];
    __IO uint32_t CC1AADSZR;                         /**< CCB 0 Class 1 AAD Size Register, array offset: 0x8005C, array step: 0xE3C */
         uint8_t RESERVED_7[4];
    __IO uint32_t CC1IVSZR;                          /**< CCB 0 Class 1 IV Size Register, array offset: 0x80064, array step: 0xE3C */
         uint8_t RESERVED_8[28];
    __IO uint32_t CPKASZR;                           /**< PKHA A Size Register, array offset: 0x80084, array step: 0xE3C */
         uint8_t RESERVED_9[4];
    __IO uint32_t CPKBSZR;                           /**< PKHA B Size Register, array offset: 0x8008C, array step: 0xE3C */
         uint8_t RESERVED_10[4];
    __IO uint32_t CPKNSZR;                           /**< PKHA N Size Register, array offset: 0x80094, array step: 0xE3C */
         uint8_t RESERVED_11[4];
    __IO uint32_t CPKESZR;                           /**< PKHA E Size Register, array offset: 0x8009C, array step: 0xE3C */
         uint8_t RESERVED_12[96];
    __IO uint32_t CC1CTXR[CAAM_DC_CDC1CTXR_B_COUNT];   /**< CCB 0 Class 1 Context Register Word 0..CCB 0 Class 1 Context Register Word 15, array offset: 0x80100, array step: index*0xE3C, index2*0x4 */
         uint8_t RESERVED_13[192];
    __IO uint32_t CC1KR[CAAM_DC_CDC1KEYR_I_COUNT];   /**< CCB 0 Class 1 Key Registers Word 0..CCB 0 Class 1 Key Registers Word 7, array offset: 0x80200, array step: index*0xE3C, index2*0x4 */
         uint8_t RESERVED_14[484];
    __IO uint32_t CC2MR;                             /**< CCB 0 Class 2 Mode Register, array offset: 0x80404, array step: 0xE3C */
         uint8_t RESERVED_15[4];
    __IO uint32_t CC2KSR;                            /**< CCB 0 Class 2 Key Size Register, array offset: 0x8040C, array step: 0xE3C */
    __IO uint64_t CC2DSR;                            /**< CCB 0 Class 2 Data Size Register, array offset: 0x80410, array step: 0xE3C */
         uint8_t RESERVED_16[4];
    __IO uint32_t CC2ICVSZR;                         /**< CCB 0 Class 2 ICV Size Register, array offset: 0x8041C, array step: 0xE3C */
         uint8_t RESERVED_17[224];
    __IO uint32_t CC2CTXR[CAAM_DC_CDC2CTXR_I_COUNT];   /**< CCB 0 Class 2 Context Register Word 0..CCB 0 Class 2 Context Register Word 17, array offset: 0x80500, array step: index*0xE3C, index2*0x4 */
         uint8_t RESERVED_18[184];
    __IO uint32_t CC2KEYR[CAAM_DC_CDC2KEYR_I_COUNT];   /**< CCB 0 Class 2 Key Register Word 0..CCB 0 Class 2 Key Register Word 31, array offset: 0x80600, array step: index*0xE3C, index2*0x4 */
         uint8_t RESERVED_19[320];
    __I  uint32_t CFIFOSTA;                          /**< CCB 0 FIFO Status Register, array offset: 0x807C0, array step: 0xE3C */
         uint8_t RESERVED_20[12];
    union {                                          /* offset: 0x807D0, array step: 0xE3C */
      __O  uint32_t CNFIFO;                            /**< CCB 0 iNformation FIFO When STYPE != 10b, array offset: 0x807D0, array step: 0xE3C */
      __O  uint32_t CNFIFO_2;                          /**< CCB 0 iNformation FIFO When STYPE == 10b, array offset: 0x807D0, array step: 0xE3C */
    };
         uint8_t RESERVED_21[12];
    __O  uint32_t CIFIFO;                            /**< CCB 0 Input Data FIFO, array offset: 0x807E0, array step: 0xE3C */
         uint8_t RESERVED_22[12];
    __I  uint64_t COFIFO;                            /**< CCB 0 Output Data FIFO, array offset: 0x807F0, array step: 0xE3C */
         uint8_t RESERVED_23[8];
    __IO uint32_t DJQCR_MS;                          /**< DECO0 Job Queue Control Register, most-significant half, array offset: 0x80800, array step: 0xE3C */
    __I  uint32_t DJQCR_LS;                          /**< DECO0 Job Queue Control Register, least-significant half, array offset: 0x80804, array step: 0xE3C */
    __I  uint64_t DDAR;                              /**< DECO0 Descriptor Address Register, array offset: 0x80808, array step: 0xE3C */
    __I  uint32_t DOPSTA_MS;                         /**< DECO0 Operation Status Register, most-significant half, array offset: 0x80810, array step: 0xE3C */
    __I  uint32_t DOPSTA_LS;                         /**< DECO0 Operation Status Register, least-significant half, array offset: 0x80814, array step: 0xE3C */
         uint8_t RESERVED_24[8];
    __I  uint32_t DPDIDSR;                           /**< DECO0 Primary DID Status Register, array offset: 0x80820, array step: 0xE3C */
    __I  uint32_t DODIDSR;                           /**< DECO0 Output DID Status Register, array offset: 0x80824, array step: 0xE3C */
         uint8_t RESERVED_25[24];
    struct {                                         /* offset: 0x80840, array step: index*0xE3C, index2*0x8 */
      __IO uint32_t DMTH_MS;                           /**< DECO0 Math Register 0_MS..DECO0 Math Register 3_MS, array offset: 0x80840, array step: index*0xE3C, index2*0x8 */
      __IO uint32_t DMTH_LS;                           /**< DECO0 Math Register 0_LS..DECO0 Math Register 3_LS, array offset: 0x80844, array step: index*0xE3C, index2*0x8 */
    } DDMTHB[CAAM_DC_DDMTHB_COUNT];
         uint8_t RESERVED_26[32];
    struct {                                         /* offset: 0x80880, array step: index*0xE3C, index2*0x10 */
      __IO uint32_t DGTR_0;                            /**< DECO0 Gather Table Register 0 Word 0, array offset: 0x80880, array step: index*0xE3C, index2*0x10 */
      __IO uint32_t DGTR_1;                            /**< DECO0 Gather Table Register 0 Word 1, array offset: 0x80884, array step: index*0xE3C, index2*0x10 */
      __IO uint32_t DGTR_2;                            /**< DECO0 Gather Table Register 0 Word 2, array offset: 0x80888, array step: index*0xE3C, index2*0x10 */
      __IO uint32_t DGTR_3;                            /**< DECO0 Gather Table Register 0 Word 3, array offset: 0x8088C, array step: index*0xE3C, index2*0x10 */
    } DDGTR[CAAM_DC_DDGTR_COUNT];
         uint8_t RESERVED_27[112];
    struct {                                         /* offset: 0x80900, array step: index*0xE3C, index2*0x10 */
      __IO uint32_t DSTR_0;                            /**< DECO0 Scatter Table Register 0 Word 0, array offset: 0x80900, array step: index*0xE3C, index2*0x10 */
      __IO uint32_t DSTR_1;                            /**< DECO0 Scatter Table Register 0 Word 1, array offset: 0x80904, array step: index*0xE3C, index2*0x10 */
      __IO uint32_t DSTR_2;                            /**< DECO0 Scatter Table Register 0 Word 2, array offset: 0x80908, array step: index*0xE3C, index2*0x10 */
      __IO uint32_t DSTR_3;                            /**< DECO0 Scatter Table Register 0 Word 3, array offset: 0x8090C, array step: index*0xE3C, index2*0x10 */
    } DDSTR[CAAM_DC_DDSTR_COUNT];
         uint8_t RESERVED_28[240];
    __IO uint32_t DDESB[CAAM_DC_DDDESB_COUNT];       /**< DECO0 Descriptor Buffer Word 0..DECO0 Descriptor Buffer Word 63, array offset: 0x80A00, array step: index*0xE3C, index2*0x4 */
         uint8_t RESERVED_29[768];
    __I  uint32_t DDJR;                              /**< DECO0 Debug Job Register, array offset: 0x80E00, array step: 0xE3C */
    __I  uint32_t DDDR;                              /**< DECO0 Debug DECO Register, array offset: 0x80E04, array step: 0xE3C */
    __I  uint64_t DDJP;                              /**< DECO0 Debug Job Pointer, array offset: 0x80E08, array step: 0xE3C */
    __I  uint64_t DSDP;                              /**< DECO0 Debug Shared Pointer, array offset: 0x80E10, array step: 0xE3C */
    __I  uint32_t DDDR_MS;                           /**< DECO0 Debug DID, most-significant half, array offset: 0x80E18, array step: 0xE3C */
    __I  uint32_t DDDR_LS;                           /**< DECO0 Debug DID, least-significant half, array offset: 0x80E1C, array step: 0xE3C */
    __IO uint32_t SOL;                               /**< Sequence Output Length Register, array offset: 0x80E20, array step: 0xE3C */
    __IO uint32_t VSOL;                              /**< Variable Sequence Output Length Register, array offset: 0x80E24, array step: 0xE3C */
    __IO uint32_t SIL;                               /**< Sequence Input Length Register, array offset: 0x80E28, array step: 0xE3C */
    __IO uint32_t VSIL;                              /**< Variable Sequence Input Length Register, array offset: 0x80E2C, array step: 0xE3C */
    __IO uint32_t DPOVRD;                            /**< Protocol Override Register, array offset: 0x80E30, array step: 0xE3C */
    __IO uint32_t UVSOL;                             /**< Variable Sequence Output Length Register; Upper 32 bits, array offset: 0x80E34, array step: 0xE3C */
    __IO uint32_t UVSIL;                             /**< Variable Sequence Input Length Register; Upper 32 bits, array offset: 0x80E38, array step: 0xE3C */
  } DC[CAAM_DC_COUNT];
       uint8_t RESERVED_53[356];
  __I  uint32_t CRNR_MS_DC01;                      /**< CHA Revision Number Register, most-significant half, offset: 0x80FA0 */
  __I  uint32_t CRNR_LS_DC01;                      /**< CHA Revision Number Register, least-significant half, offset: 0x80FA4 */
  __I  uint32_t CTPR_MS_DC01;                      /**< Compile Time Parameters Register, most-significant half, offset: 0x80FA8 */
  __I  uint32_t CTPR_LS_DC01;                      /**< Compile Time Parameters Register, least-significant half, offset: 0x80FAC */
       uint8_t RESERVED_54[4];
  __I  uint32_t SMSTA_DC01;                        /**< Secure Memory Status Register, offset: 0x80FB4 */
       uint8_t RESERVED_55[8];
  __I  uint64_t FAR_DC01;                          /**< Fault Address Register, offset: 0x80FC0 */
  __I  uint32_t FADID_DC01;                        /**< Fault Address DID Register, offset: 0x80FC8 */
  __I  uint32_t FADR_DC01;                         /**< Fault Address Detail Register, offset: 0x80FCC */
       uint8_t RESERVED_56[4];
  __I  uint32_t CSTA_DC01;                         /**< CAAM Status Register, offset: 0x80FD4 */
  __I  uint32_t SMVID_MS_DC01;                     /**< Secure Memory Version ID Register, most-significant half, offset: 0x80FD8 */
  __I  uint32_t SMVID_LS_DC01;                     /**< Secure Memory Version ID Register, least-significant half, offset: 0x80FDC */
  __I  uint32_t RVID_DC01;                         /**< RTIC Version ID Register, offset: 0x80FE0 */
  __I  uint32_t CCBVID_DC01;                       /**< CHA Cluster Block Version ID Register, offset: 0x80FE4 */
  __I  uint32_t CHAVID_MS_DC01;                    /**< CHA Version ID Register, most-significant half, offset: 0x80FE8 */
  __I  uint32_t CHAVID_LS_DC01;                    /**< CHA Version ID Register, least-significant half, offset: 0x80FEC */
  __I  uint32_t CHANUM_MS_DC01;                    /**< CHA Number Register, most-significant half, offset: 0x80FF0 */
  __I  uint32_t CHANUM_LS_DC01;                    /**< CHA Number Register, least-significant half, offset: 0x80FF4 */
  __I  uint32_t CAAMVID_MS_DC01;                   /**< CAAM Version ID Register, most-significant half, offset: 0x80FF8 */
  __I  uint32_t CAAMVID_LS_DC01;                   /**< CAAM Version ID Register, least-significant half, offset: 0x80FFC */
} CAAM_Type;

/* ----------------------------------------------------------------------------
   -- CAAM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CAAM_Register_Masks CAAM Register Masks
 * @{
 */

/*! @name MCFGR - Master Configuration Register */
/*! @{ */

#define CAAM_MCFGR_NORMAL_BURST_MASK             (0x1U)
#define CAAM_MCFGR_NORMAL_BURST_SHIFT            (0U)
/*! NORMAL_BURST
 *  0b0..Aligned 32 byte burst size target
 *  0b1..Aligned 64 byte burst size target
 */
#define CAAM_MCFGR_NORMAL_BURST(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_MCFGR_NORMAL_BURST_SHIFT)) & CAAM_MCFGR_NORMAL_BURST_MASK)

#define CAAM_MCFGR_LARGE_BURST_MASK              (0x4U)
#define CAAM_MCFGR_LARGE_BURST_SHIFT             (2U)
#define CAAM_MCFGR_LARGE_BURST(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_MCFGR_LARGE_BURST_SHIFT)) & CAAM_MCFGR_LARGE_BURST_MASK)

#define CAAM_MCFGR_AXIPIPE_MASK                  (0xF0U)
#define CAAM_MCFGR_AXIPIPE_SHIFT                 (4U)
#define CAAM_MCFGR_AXIPIPE(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_MCFGR_AXIPIPE_SHIFT)) & CAAM_MCFGR_AXIPIPE_MASK)

#define CAAM_MCFGR_AWCACHE_MASK                  (0xF00U)
#define CAAM_MCFGR_AWCACHE_SHIFT                 (8U)
#define CAAM_MCFGR_AWCACHE(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_MCFGR_AWCACHE_SHIFT)) & CAAM_MCFGR_AWCACHE_MASK)

#define CAAM_MCFGR_ARCACHE_MASK                  (0xF000U)
#define CAAM_MCFGR_ARCACHE_SHIFT                 (12U)
#define CAAM_MCFGR_ARCACHE(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_MCFGR_ARCACHE_SHIFT)) & CAAM_MCFGR_ARCACHE_MASK)

#define CAAM_MCFGR_PS_MASK                       (0x10000U)
#define CAAM_MCFGR_PS_SHIFT                      (16U)
/*! PS
 *  0b0..Pointers fit in one 32-bit word (pointers are 32-bit addresses).
 *  0b1..Pointers require two 32-bit words (pointers are 36-bit addresses).
 */
#define CAAM_MCFGR_PS(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_MCFGR_PS_SHIFT)) & CAAM_MCFGR_PS_MASK)

#define CAAM_MCFGR_DWT_MASK                      (0x80000U)
#define CAAM_MCFGR_DWT_SHIFT                     (19U)
#define CAAM_MCFGR_DWT(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_MCFGR_DWT_SHIFT)) & CAAM_MCFGR_DWT_MASK)

#define CAAM_MCFGR_WRHD_MASK                     (0x8000000U)
#define CAAM_MCFGR_WRHD_SHIFT                    (27U)
#define CAAM_MCFGR_WRHD(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_MCFGR_WRHD_SHIFT)) & CAAM_MCFGR_WRHD_MASK)

#define CAAM_MCFGR_DMA_RST_MASK                  (0x10000000U)
#define CAAM_MCFGR_DMA_RST_SHIFT                 (28U)
#define CAAM_MCFGR_DMA_RST(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_MCFGR_DMA_RST_SHIFT)) & CAAM_MCFGR_DMA_RST_MASK)

#define CAAM_MCFGR_WDF_MASK                      (0x20000000U)
#define CAAM_MCFGR_WDF_SHIFT                     (29U)
#define CAAM_MCFGR_WDF(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_MCFGR_WDF_SHIFT)) & CAAM_MCFGR_WDF_MASK)

#define CAAM_MCFGR_WDE_MASK                      (0x40000000U)
#define CAAM_MCFGR_WDE_SHIFT                     (30U)
#define CAAM_MCFGR_WDE(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_MCFGR_WDE_SHIFT)) & CAAM_MCFGR_WDE_MASK)

#define CAAM_MCFGR_SWRST_MASK                    (0x80000000U)
#define CAAM_MCFGR_SWRST_SHIFT                   (31U)
#define CAAM_MCFGR_SWRST(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_MCFGR_SWRST_SHIFT)) & CAAM_MCFGR_SWRST_MASK)
/*! @} */

/*! @name PAGE0_SDID - Page 0 SDID Register */
/*! @{ */

#define CAAM_PAGE0_SDID_SDID_MASK                (0x7FFFU)
#define CAAM_PAGE0_SDID_SDID_SHIFT               (0U)
#define CAAM_PAGE0_SDID_SDID(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_PAGE0_SDID_SDID_SHIFT)) & CAAM_PAGE0_SDID_SDID_MASK)
/*! @} */

/*! @name SCFGR - Security Configuration Register */
/*! @{ */

#define CAAM_SCFGR_PRIBLOB_MASK                  (0x3U)
#define CAAM_SCFGR_PRIBLOB_SHIFT                 (0U)
/*! PRIBLOB
 *  0b00..Private secure boot software blobs
 *  0b01..Private provisioning type 1 blobs
 *  0b10..Private provisioning type 2 blobs
 *  0b11..Normal operation blobs
 */
#define CAAM_SCFGR_PRIBLOB(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_SCFGR_PRIBLOB_SHIFT)) & CAAM_SCFGR_PRIBLOB_MASK)

#define CAAM_SCFGR_RNGSH0_MASK                   (0x200U)
#define CAAM_SCFGR_RNGSH0_SHIFT                  (9U)
/*! RNGSH0
 *  0b0..When RNGSH0 is 0, RNG DRNG State Handle 0 can be instantiated in any mode. RNGSH0 is set to 0 only for testing.
 *  0b1..When RNGSH0 is 1, RNG DRNG State Handle 0 cannot be instantiated in deterministic (test) mode. RNGSHO
 *       should be set to 1 before the RNG is instantiated. If it is currently instantiated in a deterministic mode,
 *       it will be un-instantiated. Once this bit has been written to a 1, it cannot be changed to a 0 until the
 *       next power on reset.
 */
#define CAAM_SCFGR_RNGSH0(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_SCFGR_RNGSH0_SHIFT)) & CAAM_SCFGR_RNGSH0_MASK)

#define CAAM_SCFGR_LCK_TRNG_MASK                 (0x800U)
#define CAAM_SCFGR_LCK_TRNG_SHIFT                (11U)
#define CAAM_SCFGR_LCK_TRNG(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_SCFGR_LCK_TRNG_SHIFT)) & CAAM_SCFGR_LCK_TRNG_MASK)

#define CAAM_SCFGR_VIRT_EN_MASK                  (0x8000U)
#define CAAM_SCFGR_VIRT_EN_SHIFT                 (15U)
/*! VIRT_EN
 *  0b0..Disable job ring virtualization
 *  0b1..Enable job ring virtualization
 */
#define CAAM_SCFGR_VIRT_EN(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_SCFGR_VIRT_EN_SHIFT)) & CAAM_SCFGR_VIRT_EN_MASK)

#define CAAM_SCFGR_MPMRL_MASK                    (0x4000000U)
#define CAAM_SCFGR_MPMRL_SHIFT                   (26U)
#define CAAM_SCFGR_MPMRL(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_SCFGR_MPMRL_SHIFT)) & CAAM_SCFGR_MPMRL_MASK)

#define CAAM_SCFGR_MPPKRC_MASK                   (0x8000000U)
#define CAAM_SCFGR_MPPKRC_SHIFT                  (27U)
#define CAAM_SCFGR_MPPKRC(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_SCFGR_MPPKRC_SHIFT)) & CAAM_SCFGR_MPPKRC_MASK)

#define CAAM_SCFGR_MPCURVE_MASK                  (0xF0000000U)
#define CAAM_SCFGR_MPCURVE_SHIFT                 (28U)
#define CAAM_SCFGR_MPCURVE(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_SCFGR_MPCURVE_SHIFT)) & CAAM_SCFGR_MPCURVE_MASK)
/*! @} */

/*! @name JRDID_MS - Job Ring 0 DID Register - most significant half..Job Ring 3 DID Register - most significant half */
/*! @{ */

#define CAAM_JRDID_MS_PRIM_DID_MASK              (0xFU)
#define CAAM_JRDID_MS_PRIM_DID_SHIFT             (0U)
#define CAAM_JRDID_MS_PRIM_DID(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_JRDID_MS_PRIM_DID_SHIFT)) & CAAM_JRDID_MS_PRIM_DID_MASK)

#define CAAM_JRDID_MS_PRIM_TZ_MASK               (0x10U)
#define CAAM_JRDID_MS_PRIM_TZ_SHIFT              (4U)
#define CAAM_JRDID_MS_PRIM_TZ(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_JRDID_MS_PRIM_TZ_SHIFT)) & CAAM_JRDID_MS_PRIM_TZ_MASK)

#define CAAM_JRDID_MS_SDID_MS_MASK               (0x7FE0U)
#define CAAM_JRDID_MS_SDID_MS_SHIFT              (5U)
#define CAAM_JRDID_MS_SDID_MS(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_JRDID_MS_SDID_MS_SHIFT)) & CAAM_JRDID_MS_SDID_MS_MASK)

#define CAAM_JRDID_MS_TZ_OWN_MASK                (0x8000U)
#define CAAM_JRDID_MS_TZ_OWN_SHIFT               (15U)
#define CAAM_JRDID_MS_TZ_OWN(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_JRDID_MS_TZ_OWN_SHIFT)) & CAAM_JRDID_MS_TZ_OWN_MASK)

#define CAAM_JRDID_MS_AMTD_MASK                  (0x10000U)
#define CAAM_JRDID_MS_AMTD_SHIFT                 (16U)
#define CAAM_JRDID_MS_AMTD(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_JRDID_MS_AMTD_SHIFT)) & CAAM_JRDID_MS_AMTD_MASK)

#define CAAM_JRDID_MS_LAMTD_MASK                 (0x20000U)
#define CAAM_JRDID_MS_LAMTD_SHIFT                (17U)
#define CAAM_JRDID_MS_LAMTD(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_JRDID_MS_LAMTD_SHIFT)) & CAAM_JRDID_MS_LAMTD_MASK)

#define CAAM_JRDID_MS_PRIM_ICID_MASK             (0x3FF80000U)
#define CAAM_JRDID_MS_PRIM_ICID_SHIFT            (19U)
#define CAAM_JRDID_MS_PRIM_ICID(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_JRDID_MS_PRIM_ICID_SHIFT)) & CAAM_JRDID_MS_PRIM_ICID_MASK)

#define CAAM_JRDID_MS_USE_OUT_MASK               (0x40000000U)
#define CAAM_JRDID_MS_USE_OUT_SHIFT              (30U)
#define CAAM_JRDID_MS_USE_OUT(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_JRDID_MS_USE_OUT_SHIFT)) & CAAM_JRDID_MS_USE_OUT_MASK)

#define CAAM_JRDID_MS_LDID_MASK                  (0x80000000U)
#define CAAM_JRDID_MS_LDID_SHIFT                 (31U)
#define CAAM_JRDID_MS_LDID(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_JRDID_MS_LDID_SHIFT)) & CAAM_JRDID_MS_LDID_MASK)
/*! @} */

/* The count of CAAM_JRDID_MS */
#define CAAM_JRDID_MS_COUNT                      (4U)

/*! @name JRDID_LS - Job Ring 0 DID Register - least significant half..Job Ring 3 DID Register - least significant half */
/*! @{ */

#define CAAM_JRDID_LS_OUT_DID_MASK               (0xFU)
#define CAAM_JRDID_LS_OUT_DID_SHIFT              (0U)
#define CAAM_JRDID_LS_OUT_DID(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_JRDID_LS_OUT_DID_SHIFT)) & CAAM_JRDID_LS_OUT_DID_MASK)

#define CAAM_JRDID_LS_OUT_ICID_MASK              (0x3FF80000U)
#define CAAM_JRDID_LS_OUT_ICID_SHIFT             (19U)
#define CAAM_JRDID_LS_OUT_ICID(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_JRDID_LS_OUT_ICID_SHIFT)) & CAAM_JRDID_LS_OUT_ICID_MASK)
/*! @} */

/* The count of CAAM_JRDID_LS */
#define CAAM_JRDID_LS_COUNT                      (4U)

/*! @name DEBUGCTL - Debug Control Register */
/*! @{ */

#define CAAM_DEBUGCTL_STOP_MASK                  (0x10000U)
#define CAAM_DEBUGCTL_STOP_SHIFT                 (16U)
#define CAAM_DEBUGCTL_STOP(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_DEBUGCTL_STOP_SHIFT)) & CAAM_DEBUGCTL_STOP_MASK)

#define CAAM_DEBUGCTL_STOP_ACK_MASK              (0x20000U)
#define CAAM_DEBUGCTL_STOP_ACK_SHIFT             (17U)
#define CAAM_DEBUGCTL_STOP_ACK(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_DEBUGCTL_STOP_ACK_SHIFT)) & CAAM_DEBUGCTL_STOP_ACK_MASK)
/*! @} */

/*! @name JRSTARTR - Job Ring Start Register */
/*! @{ */

#define CAAM_JRSTARTR_Start_JR0_MASK             (0x1U)
#define CAAM_JRSTARTR_Start_JR0_SHIFT            (0U)
/*! Start_JR0
 *  0b0..Stop Mode. The JR0DID register and the SMVBA register for Job Ring 0 can be written but the IRBAR, IRSR,
 *       IRSAR, IRJAR, ORBAR, ORSR, ORJRR, ORSFR and JRSTAR for Job Ring 0 are NOT accessible. If Job Ring 0 is
 *       allocated to TrustZone SecureWorld (JR0DID[TZ]=1), the JR0DID and SMVBA register can be written only via a
 *       bus transaction that has ns=0.
 *  0b1..Start Mode. The JR0DID register and the SMVBA register for Job Ring 0 CANNOT be written but the IRBAR,
 *       IRSR, IRSAR, IRJAR, ORBAR, ORSR, ORJRR, ORSFR and JRSTAR for Job Ring 0 ARE accessible. If Job Ring 0 is
 *       allocated to TrustZone SecureWorld (JR0DID[TZ]=1), then the SMVBA, IRBAR, IRSR, IRSAR, IRJAR, ORBAR, ORSR,
 *       ORJRR, ORSFR and JRSTAR registers for Job Ring 0 can be written only via a bus transaction that has ns=0.
 */
#define CAAM_JRSTARTR_Start_JR0(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_JRSTARTR_Start_JR0_SHIFT)) & CAAM_JRSTARTR_Start_JR0_MASK)

#define CAAM_JRSTARTR_Start_JR1_MASK             (0x2U)
#define CAAM_JRSTARTR_Start_JR1_SHIFT            (1U)
/*! Start_JR1
 *  0b0..Stop Mode. The JR1DID register and the SMVBA register for Job Ring 1 can be written but the IRBAR, IRSR,
 *       IRSAR, IRJAR, ORBAR, ORSR, ORJRR, ORSFR and JRSTAR for Job Ring 1 are NOT accessible. If Job Ring 1 is
 *       allocated to TrustZone SecureWorld (JR1DID[TZ]=1), the JR1DID and SMVBA register can be written only via a
 *       bus transaction that has ns=0.
 *  0b1..Start Mode. The JR1DID register and the SMVBA register for Job Ring 1 CANNOT be written but the IRBAR,
 *       IRSR, IRSAR, IRJAR, ORBAR, ORSR, ORJRR, ORSFR and JRSTAR for Job Ring 1 ARE accessible. If Job Ring 1 is
 *       allocated to TrustZone SecureWorld (JR1DID[TZ]=1), then the SMVBA, IRBAR, IRSR, IRSAR, IRJAR, ORBAR, ORSR,
 *       ORJRR, ORSFR and JRSTAR registers for Job Ring 1 can be written only via a bus transaction that has ns=0.
 */
#define CAAM_JRSTARTR_Start_JR1(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_JRSTARTR_Start_JR1_SHIFT)) & CAAM_JRSTARTR_Start_JR1_MASK)

#define CAAM_JRSTARTR_Start_JR2_MASK             (0x4U)
#define CAAM_JRSTARTR_Start_JR2_SHIFT            (2U)
/*! Start_JR2
 *  0b0..Stop Mode. The JR2DID register and the SMVBA register for Job Ring 2 can be written but the IRBAR, IRSR,
 *       IRSAR, IRJAR, ORBAR, ORSR, ORJRR, ORSFR and JRSTAR for Job Ring 2 are NOT accessible. If Job Ring 2 is
 *       allocated to TrustZone SecureWorld (JR2DID[TZ]=1), the JR2DID and SMVBA register can be written only via a
 *       bus transaction that has ns=0.
 *  0b1..Start Mode. The JR2DID register and the SMVBA register for Job Ring 2 CANNOT be written but the IRBAR,
 *       IRSR, IRSAR, IRJAR, ORBAR, ORSR, ORJRR, ORSFR and JRSTAR for Job Ring 2 ARE accessible. If Job Ring 2 is
 *       allocated to TrustZone SecureWorld (JR2DID[TZ]=1), then the SMVBA, IRBAR, IRSR, IRSAR, IRJAR, ORBAR, ORSR,
 *       ORJRR, ORSFR and JRSTAR registers for Job Ring 2 can be written only via a bus transaction that has ns=0.
 */
#define CAAM_JRSTARTR_Start_JR2(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_JRSTARTR_Start_JR2_SHIFT)) & CAAM_JRSTARTR_Start_JR2_MASK)

#define CAAM_JRSTARTR_Start_JR3_MASK             (0x8U)
#define CAAM_JRSTARTR_Start_JR3_SHIFT            (3U)
/*! Start_JR3
 *  0b0..Stop Mode. The JR3DID register and the SMVBA register for Job Ring 3 can be written but the IRBAR, IRSR,
 *       IRSAR, IRJAR, ORBAR, ORSR, ORJRR, ORSFR and JRSTAR for Job Ring 3 are NOT accessible. If Job Ring 3 is
 *       allocated to TrustZone SecureWorld (JR3DID[TZ]=1), the JR3DID and SMVBA register can be written only via a
 *       bus transaction that has ns=0.
 *  0b1..Start Mode. The JR3DID register and the SMVBA register for Job Ring 3 CANNOT be written but the IRBAR,
 *       IRSR, IRSAR, IRJAR, ORBAR, ORSR, ORJRR, ORSFR and JRSTAR for Job Ring 3 ARE accessible. If Job Ring 3 is
 *       allocated to TrustZone SecureWorld (JR3DID[TZ]=1), then the SMVBA, IRBAR, IRSR, IRSAR, IRJAR, ORBAR, ORSR,
 *       ORJRR, ORSFR and JRSTAR registers for Job Ring 3 can be written only via a bus transaction that has ns=0.
 */
#define CAAM_JRSTARTR_Start_JR3(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_JRSTARTR_Start_JR3_SHIFT)) & CAAM_JRSTARTR_Start_JR3_MASK)
/*! @} */

/*! @name RTIC_OWN - RTIC OWN Register */
/*! @{ */

#define CAAM_RTIC_OWN_ROWN_DID_MASK              (0xFU)
#define CAAM_RTIC_OWN_ROWN_DID_SHIFT             (0U)
/*! ROWN_DID - RTIC Owner's DID */
#define CAAM_RTIC_OWN_ROWN_DID(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_RTIC_OWN_ROWN_DID_SHIFT)) & CAAM_RTIC_OWN_ROWN_DID_MASK)

#define CAAM_RTIC_OWN_ROWN_TZ_MASK               (0x10U)
#define CAAM_RTIC_OWN_ROWN_TZ_SHIFT              (4U)
#define CAAM_RTIC_OWN_ROWN_TZ(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTIC_OWN_ROWN_TZ_SHIFT)) & CAAM_RTIC_OWN_ROWN_TZ_MASK)

#define CAAM_RTIC_OWN_LCK_MASK                   (0x80000000U)
#define CAAM_RTIC_OWN_LCK_SHIFT                  (31U)
#define CAAM_RTIC_OWN_LCK(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_RTIC_OWN_LCK_SHIFT)) & CAAM_RTIC_OWN_LCK_MASK)
/*! @} */

/*! @name RTIC_DID - RTIC DID Register for Block A..RTIC DID Register for Block D */
/*! @{ */

#define CAAM_RTIC_DID_RTIC_DID_MASK              (0xFU)
#define CAAM_RTIC_DID_RTIC_DID_SHIFT             (0U)
#define CAAM_RTIC_DID_RTIC_DID(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_RTIC_DID_RTIC_DID_SHIFT)) & CAAM_RTIC_DID_RTIC_DID_MASK)

#define CAAM_RTIC_DID_RTIC_TZ_MASK               (0x10U)
#define CAAM_RTIC_DID_RTIC_TZ_SHIFT              (4U)
#define CAAM_RTIC_DID_RTIC_TZ(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTIC_DID_RTIC_TZ_SHIFT)) & CAAM_RTIC_DID_RTIC_TZ_MASK)

#define CAAM_RTIC_DID_RTIC_ICID_MASK             (0x3FF80000U)
#define CAAM_RTIC_DID_RTIC_ICID_SHIFT            (19U)
#define CAAM_RTIC_DID_RTIC_ICID(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_RTIC_DID_RTIC_ICID_SHIFT)) & CAAM_RTIC_DID_RTIC_ICID_MASK)
/*! @} */

/* The count of CAAM_RTIC_DID */
#define CAAM_RTIC_DID_COUNT                      (4U)

/*! @name DECORSR - DECO Request Source Register */
/*! @{ */

#define CAAM_DECORSR_JR_MASK                     (0x3U)
#define CAAM_DECORSR_JR_SHIFT                    (0U)
#define CAAM_DECORSR_JR(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_DECORSR_JR_SHIFT)) & CAAM_DECORSR_JR_MASK)

#define CAAM_DECORSR_VALID_MASK                  (0x80000000U)
#define CAAM_DECORSR_VALID_SHIFT                 (31U)
#define CAAM_DECORSR_VALID(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_DECORSR_VALID_SHIFT)) & CAAM_DECORSR_VALID_MASK)
/*! @} */

/*! @name DECORR - DECO Request Register */
/*! @{ */

#define CAAM_DECORR_RQD0_MASK                    (0x1U)
#define CAAM_DECORR_RQD0_SHIFT                   (0U)
#define CAAM_DECORR_RQD0(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_DECORR_RQD0_SHIFT)) & CAAM_DECORR_RQD0_MASK)

#define CAAM_DECORR_DEN0_MASK                    (0x10000U)
#define CAAM_DECORR_DEN0_SHIFT                   (16U)
#define CAAM_DECORR_DEN0(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_DECORR_DEN0_SHIFT)) & CAAM_DECORR_DEN0_MASK)
/*! @} */

/*! @name DECODID_MS - DECO0 DID Register - most significant half */
/*! @{ */

#define CAAM_DECODID_MS_DPRIM_DID_MASK           (0xFU)
#define CAAM_DECODID_MS_DPRIM_DID_SHIFT          (0U)
/*! DPRIM_DID - DECO Owner */
#define CAAM_DECODID_MS_DPRIM_DID(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_DECODID_MS_DPRIM_DID_SHIFT)) & CAAM_DECODID_MS_DPRIM_DID_MASK)

#define CAAM_DECODID_MS_D_NS_MASK                (0x10U)
#define CAAM_DECODID_MS_D_NS_SHIFT               (4U)
#define CAAM_DECODID_MS_D_NS(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_DECODID_MS_D_NS_SHIFT)) & CAAM_DECODID_MS_D_NS_MASK)

#define CAAM_DECODID_MS_LCK_MASK                 (0x80000000U)
#define CAAM_DECODID_MS_LCK_SHIFT                (31U)
#define CAAM_DECODID_MS_LCK(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_DECODID_MS_LCK_SHIFT)) & CAAM_DECODID_MS_LCK_MASK)
/*! @} */

/* The count of CAAM_DECODID_MS */
#define CAAM_DECODID_MS_COUNT                    (1U)

/*! @name DECODID_LS - DECO0 DID Register - least significant half */
/*! @{ */

#define CAAM_DECODID_LS_DSEQ_DID_MASK            (0xFU)
#define CAAM_DECODID_LS_DSEQ_DID_SHIFT           (0U)
#define CAAM_DECODID_LS_DSEQ_DID(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_DECODID_LS_DSEQ_DID_SHIFT)) & CAAM_DECODID_LS_DSEQ_DID_MASK)

#define CAAM_DECODID_LS_DSEQ_NS_MASK             (0x10U)
#define CAAM_DECODID_LS_DSEQ_NS_SHIFT            (4U)
#define CAAM_DECODID_LS_DSEQ_NS(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_DECODID_LS_DSEQ_NS_SHIFT)) & CAAM_DECODID_LS_DSEQ_NS_MASK)

#define CAAM_DECODID_LS_DNSEQ_DID_MASK           (0xF0000U)
#define CAAM_DECODID_LS_DNSEQ_DID_SHIFT          (16U)
#define CAAM_DECODID_LS_DNSEQ_DID(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_DECODID_LS_DNSEQ_DID_SHIFT)) & CAAM_DECODID_LS_DNSEQ_DID_MASK)

#define CAAM_DECODID_LS_DNONSEQ_NS_MASK          (0x100000U)
#define CAAM_DECODID_LS_DNONSEQ_NS_SHIFT         (20U)
#define CAAM_DECODID_LS_DNONSEQ_NS(x)            (((uint32_t)(((uint32_t)(x)) << CAAM_DECODID_LS_DNONSEQ_NS_SHIFT)) & CAAM_DECODID_LS_DNONSEQ_NS_MASK)
/*! @} */

/* The count of CAAM_DECODID_LS */
#define CAAM_DECODID_LS_COUNT                    (1U)

/*! @name DAR - DECO Availability Register */
/*! @{ */

#define CAAM_DAR_NYA0_MASK                       (0x1U)
#define CAAM_DAR_NYA0_SHIFT                      (0U)
#define CAAM_DAR_NYA0(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_DAR_NYA0_SHIFT)) & CAAM_DAR_NYA0_MASK)
/*! @} */

/*! @name DRR - DECO Reset Register */
/*! @{ */

#define CAAM_DRR_RST0_MASK                       (0x1U)
#define CAAM_DRR_RST0_SHIFT                      (0U)
#define CAAM_DRR_RST0(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_DRR_RST0_SHIFT)) & CAAM_DRR_RST0_MASK)
/*! @} */

/*! @name JRSMVBAR - Job Ring 0 Secure Memory Virtual Base Address Register..Job Ring 3 Secure Memory Virtual Base Address Register */
/*! @{ */

#define CAAM_JRSMVBAR_SMVBA_MASK                 (0xFFFFFFFFU)
#define CAAM_JRSMVBAR_SMVBA_SHIFT                (0U)
#define CAAM_JRSMVBAR_SMVBA(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_JRSMVBAR_SMVBA_SHIFT)) & CAAM_JRSMVBAR_SMVBA_MASK)
/*! @} */

/* The count of CAAM_JRSMVBAR */
#define CAAM_JRSMVBAR_COUNT                      (4U)

/*! @name PBSL - Peak Bandwidth Smoothing Limit Register */
/*! @{ */

#define CAAM_PBSL_PBSL_MASK                      (0x7FU)
#define CAAM_PBSL_PBSL_SHIFT                     (0U)
#define CAAM_PBSL_PBSL(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_PBSL_PBSL_SHIFT)) & CAAM_PBSL_PBSL_MASK)
/*! @} */

/*! @name DMA_AIDL_MAP_MS - DMA0_AIDL_MAP_MS */
/*! @{ */

#define CAAM_DMA_AIDL_MAP_MS_AID4_BID_MASK       (0xFFU)
#define CAAM_DMA_AIDL_MAP_MS_AID4_BID_SHIFT      (0U)
#define CAAM_DMA_AIDL_MAP_MS_AID4_BID(x)         (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_AIDL_MAP_MS_AID4_BID_SHIFT)) & CAAM_DMA_AIDL_MAP_MS_AID4_BID_MASK)

#define CAAM_DMA_AIDL_MAP_MS_AID5_BID_MASK       (0xFF00U)
#define CAAM_DMA_AIDL_MAP_MS_AID5_BID_SHIFT      (8U)
#define CAAM_DMA_AIDL_MAP_MS_AID5_BID(x)         (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_AIDL_MAP_MS_AID5_BID_SHIFT)) & CAAM_DMA_AIDL_MAP_MS_AID5_BID_MASK)

#define CAAM_DMA_AIDL_MAP_MS_AID6_BID_MASK       (0xFF0000U)
#define CAAM_DMA_AIDL_MAP_MS_AID6_BID_SHIFT      (16U)
#define CAAM_DMA_AIDL_MAP_MS_AID6_BID(x)         (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_AIDL_MAP_MS_AID6_BID_SHIFT)) & CAAM_DMA_AIDL_MAP_MS_AID6_BID_MASK)

#define CAAM_DMA_AIDL_MAP_MS_AID7_BID_MASK       (0xFF000000U)
#define CAAM_DMA_AIDL_MAP_MS_AID7_BID_SHIFT      (24U)
#define CAAM_DMA_AIDL_MAP_MS_AID7_BID(x)         (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_AIDL_MAP_MS_AID7_BID_SHIFT)) & CAAM_DMA_AIDL_MAP_MS_AID7_BID_MASK)
/*! @} */

/* The count of CAAM_DMA_AIDL_MAP_MS */
#define CAAM_DMA_AIDL_MAP_MS_COUNT               (1U)

/*! @name DMA_AIDL_MAP_LS - DMA0_AIDL_MAP_LS */
/*! @{ */

#define CAAM_DMA_AIDL_MAP_LS_AID0_BID_MASK       (0xFFU)
#define CAAM_DMA_AIDL_MAP_LS_AID0_BID_SHIFT      (0U)
#define CAAM_DMA_AIDL_MAP_LS_AID0_BID(x)         (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_AIDL_MAP_LS_AID0_BID_SHIFT)) & CAAM_DMA_AIDL_MAP_LS_AID0_BID_MASK)

#define CAAM_DMA_AIDL_MAP_LS_AID1_BID_MASK       (0xFF00U)
#define CAAM_DMA_AIDL_MAP_LS_AID1_BID_SHIFT      (8U)
#define CAAM_DMA_AIDL_MAP_LS_AID1_BID(x)         (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_AIDL_MAP_LS_AID1_BID_SHIFT)) & CAAM_DMA_AIDL_MAP_LS_AID1_BID_MASK)

#define CAAM_DMA_AIDL_MAP_LS_AID2_BID_MASK       (0xFF0000U)
#define CAAM_DMA_AIDL_MAP_LS_AID2_BID_SHIFT      (16U)
#define CAAM_DMA_AIDL_MAP_LS_AID2_BID(x)         (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_AIDL_MAP_LS_AID2_BID_SHIFT)) & CAAM_DMA_AIDL_MAP_LS_AID2_BID_MASK)

#define CAAM_DMA_AIDL_MAP_LS_AID3_BID_MASK       (0xFF000000U)
#define CAAM_DMA_AIDL_MAP_LS_AID3_BID_SHIFT      (24U)
#define CAAM_DMA_AIDL_MAP_LS_AID3_BID(x)         (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_AIDL_MAP_LS_AID3_BID_SHIFT)) & CAAM_DMA_AIDL_MAP_LS_AID3_BID_MASK)
/*! @} */

/* The count of CAAM_DMA_AIDL_MAP_LS */
#define CAAM_DMA_AIDL_MAP_LS_COUNT               (1U)

/*! @name DMA_AIDM_MAP_MS - DMA0_AIDM_MAP_MS */
/*! @{ */

#define CAAM_DMA_AIDM_MAP_MS_AID12_BID_MASK      (0xFFU)
#define CAAM_DMA_AIDM_MAP_MS_AID12_BID_SHIFT     (0U)
#define CAAM_DMA_AIDM_MAP_MS_AID12_BID(x)        (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_AIDM_MAP_MS_AID12_BID_SHIFT)) & CAAM_DMA_AIDM_MAP_MS_AID12_BID_MASK)

#define CAAM_DMA_AIDM_MAP_MS_AID13_BID_MASK      (0xFF00U)
#define CAAM_DMA_AIDM_MAP_MS_AID13_BID_SHIFT     (8U)
#define CAAM_DMA_AIDM_MAP_MS_AID13_BID(x)        (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_AIDM_MAP_MS_AID13_BID_SHIFT)) & CAAM_DMA_AIDM_MAP_MS_AID13_BID_MASK)

#define CAAM_DMA_AIDM_MAP_MS_AID14_BID_MASK      (0xFF0000U)
#define CAAM_DMA_AIDM_MAP_MS_AID14_BID_SHIFT     (16U)
#define CAAM_DMA_AIDM_MAP_MS_AID14_BID(x)        (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_AIDM_MAP_MS_AID14_BID_SHIFT)) & CAAM_DMA_AIDM_MAP_MS_AID14_BID_MASK)

#define CAAM_DMA_AIDM_MAP_MS_AID15_BID_MASK      (0xFF000000U)
#define CAAM_DMA_AIDM_MAP_MS_AID15_BID_SHIFT     (24U)
#define CAAM_DMA_AIDM_MAP_MS_AID15_BID(x)        (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_AIDM_MAP_MS_AID15_BID_SHIFT)) & CAAM_DMA_AIDM_MAP_MS_AID15_BID_MASK)
/*! @} */

/* The count of CAAM_DMA_AIDM_MAP_MS */
#define CAAM_DMA_AIDM_MAP_MS_COUNT               (1U)

/*! @name DMA_AIDM_MAP_LS - DMA0_AIDM_MAP_LS */
/*! @{ */

#define CAAM_DMA_AIDM_MAP_LS_AID8_BID_MASK       (0xFFU)
#define CAAM_DMA_AIDM_MAP_LS_AID8_BID_SHIFT      (0U)
#define CAAM_DMA_AIDM_MAP_LS_AID8_BID(x)         (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_AIDM_MAP_LS_AID8_BID_SHIFT)) & CAAM_DMA_AIDM_MAP_LS_AID8_BID_MASK)

#define CAAM_DMA_AIDM_MAP_LS_AID9_BID_MASK       (0xFF00U)
#define CAAM_DMA_AIDM_MAP_LS_AID9_BID_SHIFT      (8U)
#define CAAM_DMA_AIDM_MAP_LS_AID9_BID(x)         (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_AIDM_MAP_LS_AID9_BID_SHIFT)) & CAAM_DMA_AIDM_MAP_LS_AID9_BID_MASK)

#define CAAM_DMA_AIDM_MAP_LS_AID10_BID_MASK      (0xFF0000U)
#define CAAM_DMA_AIDM_MAP_LS_AID10_BID_SHIFT     (16U)
#define CAAM_DMA_AIDM_MAP_LS_AID10_BID(x)        (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_AIDM_MAP_LS_AID10_BID_SHIFT)) & CAAM_DMA_AIDM_MAP_LS_AID10_BID_MASK)

#define CAAM_DMA_AIDM_MAP_LS_AID11_BID_MASK      (0xFF000000U)
#define CAAM_DMA_AIDM_MAP_LS_AID11_BID_SHIFT     (24U)
#define CAAM_DMA_AIDM_MAP_LS_AID11_BID(x)        (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_AIDM_MAP_LS_AID11_BID_SHIFT)) & CAAM_DMA_AIDM_MAP_LS_AID11_BID_MASK)
/*! @} */

/* The count of CAAM_DMA_AIDM_MAP_LS */
#define CAAM_DMA_AIDM_MAP_LS_COUNT               (1U)

/*! @name DMA0_AID_ENB - DMA0 AXI ID Enable Register */
/*! @{ */

#define CAAM_DMA0_AID_ENB_AID0E_MASK             (0x1U)
#define CAAM_DMA0_AID_ENB_AID0E_SHIFT            (0U)
#define CAAM_DMA0_AID_ENB_AID0E(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_DMA0_AID_ENB_AID0E_SHIFT)) & CAAM_DMA0_AID_ENB_AID0E_MASK)

#define CAAM_DMA0_AID_ENB_AID1E_MASK             (0x2U)
#define CAAM_DMA0_AID_ENB_AID1E_SHIFT            (1U)
#define CAAM_DMA0_AID_ENB_AID1E(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_DMA0_AID_ENB_AID1E_SHIFT)) & CAAM_DMA0_AID_ENB_AID1E_MASK)

#define CAAM_DMA0_AID_ENB_AID2E_MASK             (0x4U)
#define CAAM_DMA0_AID_ENB_AID2E_SHIFT            (2U)
#define CAAM_DMA0_AID_ENB_AID2E(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_DMA0_AID_ENB_AID2E_SHIFT)) & CAAM_DMA0_AID_ENB_AID2E_MASK)

#define CAAM_DMA0_AID_ENB_AID3E_MASK             (0x8U)
#define CAAM_DMA0_AID_ENB_AID3E_SHIFT            (3U)
#define CAAM_DMA0_AID_ENB_AID3E(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_DMA0_AID_ENB_AID3E_SHIFT)) & CAAM_DMA0_AID_ENB_AID3E_MASK)

#define CAAM_DMA0_AID_ENB_AID4E_MASK             (0x10U)
#define CAAM_DMA0_AID_ENB_AID4E_SHIFT            (4U)
#define CAAM_DMA0_AID_ENB_AID4E(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_DMA0_AID_ENB_AID4E_SHIFT)) & CAAM_DMA0_AID_ENB_AID4E_MASK)

#define CAAM_DMA0_AID_ENB_AID5E_MASK             (0x20U)
#define CAAM_DMA0_AID_ENB_AID5E_SHIFT            (5U)
#define CAAM_DMA0_AID_ENB_AID5E(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_DMA0_AID_ENB_AID5E_SHIFT)) & CAAM_DMA0_AID_ENB_AID5E_MASK)

#define CAAM_DMA0_AID_ENB_AID6E_MASK             (0x40U)
#define CAAM_DMA0_AID_ENB_AID6E_SHIFT            (6U)
#define CAAM_DMA0_AID_ENB_AID6E(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_DMA0_AID_ENB_AID6E_SHIFT)) & CAAM_DMA0_AID_ENB_AID6E_MASK)

#define CAAM_DMA0_AID_ENB_AID7E_MASK             (0x80U)
#define CAAM_DMA0_AID_ENB_AID7E_SHIFT            (7U)
#define CAAM_DMA0_AID_ENB_AID7E(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_DMA0_AID_ENB_AID7E_SHIFT)) & CAAM_DMA0_AID_ENB_AID7E_MASK)

#define CAAM_DMA0_AID_ENB_AID8E_MASK             (0x100U)
#define CAAM_DMA0_AID_ENB_AID8E_SHIFT            (8U)
#define CAAM_DMA0_AID_ENB_AID8E(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_DMA0_AID_ENB_AID8E_SHIFT)) & CAAM_DMA0_AID_ENB_AID8E_MASK)

#define CAAM_DMA0_AID_ENB_AID9E_MASK             (0x200U)
#define CAAM_DMA0_AID_ENB_AID9E_SHIFT            (9U)
#define CAAM_DMA0_AID_ENB_AID9E(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_DMA0_AID_ENB_AID9E_SHIFT)) & CAAM_DMA0_AID_ENB_AID9E_MASK)

#define CAAM_DMA0_AID_ENB_AID10E_MASK            (0x400U)
#define CAAM_DMA0_AID_ENB_AID10E_SHIFT           (10U)
#define CAAM_DMA0_AID_ENB_AID10E(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_DMA0_AID_ENB_AID10E_SHIFT)) & CAAM_DMA0_AID_ENB_AID10E_MASK)

#define CAAM_DMA0_AID_ENB_AID11E_MASK            (0x800U)
#define CAAM_DMA0_AID_ENB_AID11E_SHIFT           (11U)
#define CAAM_DMA0_AID_ENB_AID11E(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_DMA0_AID_ENB_AID11E_SHIFT)) & CAAM_DMA0_AID_ENB_AID11E_MASK)

#define CAAM_DMA0_AID_ENB_AID12E_MASK            (0x1000U)
#define CAAM_DMA0_AID_ENB_AID12E_SHIFT           (12U)
#define CAAM_DMA0_AID_ENB_AID12E(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_DMA0_AID_ENB_AID12E_SHIFT)) & CAAM_DMA0_AID_ENB_AID12E_MASK)

#define CAAM_DMA0_AID_ENB_AID13E_MASK            (0x2000U)
#define CAAM_DMA0_AID_ENB_AID13E_SHIFT           (13U)
#define CAAM_DMA0_AID_ENB_AID13E(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_DMA0_AID_ENB_AID13E_SHIFT)) & CAAM_DMA0_AID_ENB_AID13E_MASK)

#define CAAM_DMA0_AID_ENB_AID14E_MASK            (0x4000U)
#define CAAM_DMA0_AID_ENB_AID14E_SHIFT           (14U)
#define CAAM_DMA0_AID_ENB_AID14E(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_DMA0_AID_ENB_AID14E_SHIFT)) & CAAM_DMA0_AID_ENB_AID14E_MASK)

#define CAAM_DMA0_AID_ENB_AID15E_MASK            (0x8000U)
#define CAAM_DMA0_AID_ENB_AID15E_SHIFT           (15U)
#define CAAM_DMA0_AID_ENB_AID15E(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_DMA0_AID_ENB_AID15E_SHIFT)) & CAAM_DMA0_AID_ENB_AID15E_MASK)
/*! @} */

/*! @name DMA0_ARD_TC - DMA0 AXI Read Timing Check Register */
/*! @{ */

#define CAAM_DMA0_ARD_TC_ARSC_MASK               (0xFFFFFU)
#define CAAM_DMA0_ARD_TC_ARSC_SHIFT              (0U)
#define CAAM_DMA0_ARD_TC_ARSC(x)                 (((uint64_t)(((uint64_t)(x)) << CAAM_DMA0_ARD_TC_ARSC_SHIFT)) & CAAM_DMA0_ARD_TC_ARSC_MASK)

#define CAAM_DMA0_ARD_TC_ARLC_MASK               (0xFFFFF000000U)
#define CAAM_DMA0_ARD_TC_ARLC_SHIFT              (24U)
#define CAAM_DMA0_ARD_TC_ARLC(x)                 (((uint64_t)(((uint64_t)(x)) << CAAM_DMA0_ARD_TC_ARLC_SHIFT)) & CAAM_DMA0_ARD_TC_ARLC_MASK)

#define CAAM_DMA0_ARD_TC_ARL_MASK                (0xFFF000000000000U)
#define CAAM_DMA0_ARD_TC_ARL_SHIFT               (48U)
#define CAAM_DMA0_ARD_TC_ARL(x)                  (((uint64_t)(((uint64_t)(x)) << CAAM_DMA0_ARD_TC_ARL_SHIFT)) & CAAM_DMA0_ARD_TC_ARL_MASK)

#define CAAM_DMA0_ARD_TC_ARTL_MASK               (0x1000000000000000U)
#define CAAM_DMA0_ARD_TC_ARTL_SHIFT              (60U)
#define CAAM_DMA0_ARD_TC_ARTL(x)                 (((uint64_t)(((uint64_t)(x)) << CAAM_DMA0_ARD_TC_ARTL_SHIFT)) & CAAM_DMA0_ARD_TC_ARTL_MASK)

#define CAAM_DMA0_ARD_TC_ARTT_MASK               (0x2000000000000000U)
#define CAAM_DMA0_ARD_TC_ARTT_SHIFT              (61U)
#define CAAM_DMA0_ARD_TC_ARTT(x)                 (((uint64_t)(((uint64_t)(x)) << CAAM_DMA0_ARD_TC_ARTT_SHIFT)) & CAAM_DMA0_ARD_TC_ARTT_MASK)

#define CAAM_DMA0_ARD_TC_ARCT_MASK               (0x4000000000000000U)
#define CAAM_DMA0_ARD_TC_ARCT_SHIFT              (62U)
#define CAAM_DMA0_ARD_TC_ARCT(x)                 (((uint64_t)(((uint64_t)(x)) << CAAM_DMA0_ARD_TC_ARCT_SHIFT)) & CAAM_DMA0_ARD_TC_ARCT_MASK)

#define CAAM_DMA0_ARD_TC_ARTCE_MASK              (0x8000000000000000U)
#define CAAM_DMA0_ARD_TC_ARTCE_SHIFT             (63U)
#define CAAM_DMA0_ARD_TC_ARTCE(x)                (((uint64_t)(((uint64_t)(x)) << CAAM_DMA0_ARD_TC_ARTCE_SHIFT)) & CAAM_DMA0_ARD_TC_ARTCE_MASK)
/*! @} */

/*! @name DMA0_ARD_LAT - DMA0 Read Timing Check Latency Register */
/*! @{ */

#define CAAM_DMA0_ARD_LAT_SARL_MASK              (0xFFFFFFFFU)
#define CAAM_DMA0_ARD_LAT_SARL_SHIFT             (0U)
#define CAAM_DMA0_ARD_LAT_SARL(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_DMA0_ARD_LAT_SARL_SHIFT)) & CAAM_DMA0_ARD_LAT_SARL_MASK)
/*! @} */

/*! @name DMA0_AWR_TC - DMA0 AXI Write Timing Check Register */
/*! @{ */

#define CAAM_DMA0_AWR_TC_AWSC_MASK               (0xFFFFFU)
#define CAAM_DMA0_AWR_TC_AWSC_SHIFT              (0U)
#define CAAM_DMA0_AWR_TC_AWSC(x)                 (((uint64_t)(((uint64_t)(x)) << CAAM_DMA0_AWR_TC_AWSC_SHIFT)) & CAAM_DMA0_AWR_TC_AWSC_MASK)

#define CAAM_DMA0_AWR_TC_AWLC_MASK               (0xFFFFF000000U)
#define CAAM_DMA0_AWR_TC_AWLC_SHIFT              (24U)
#define CAAM_DMA0_AWR_TC_AWLC(x)                 (((uint64_t)(((uint64_t)(x)) << CAAM_DMA0_AWR_TC_AWLC_SHIFT)) & CAAM_DMA0_AWR_TC_AWLC_MASK)

#define CAAM_DMA0_AWR_TC_AWL_MASK                (0xFFF000000000000U)
#define CAAM_DMA0_AWR_TC_AWL_SHIFT               (48U)
#define CAAM_DMA0_AWR_TC_AWL(x)                  (((uint64_t)(((uint64_t)(x)) << CAAM_DMA0_AWR_TC_AWL_SHIFT)) & CAAM_DMA0_AWR_TC_AWL_MASK)

#define CAAM_DMA0_AWR_TC_AWTT_MASK               (0x2000000000000000U)
#define CAAM_DMA0_AWR_TC_AWTT_SHIFT              (61U)
#define CAAM_DMA0_AWR_TC_AWTT(x)                 (((uint64_t)(((uint64_t)(x)) << CAAM_DMA0_AWR_TC_AWTT_SHIFT)) & CAAM_DMA0_AWR_TC_AWTT_MASK)

#define CAAM_DMA0_AWR_TC_AWCT_MASK               (0x4000000000000000U)
#define CAAM_DMA0_AWR_TC_AWCT_SHIFT              (62U)
#define CAAM_DMA0_AWR_TC_AWCT(x)                 (((uint64_t)(((uint64_t)(x)) << CAAM_DMA0_AWR_TC_AWCT_SHIFT)) & CAAM_DMA0_AWR_TC_AWCT_MASK)

#define CAAM_DMA0_AWR_TC_AWTCE_MASK              (0x8000000000000000U)
#define CAAM_DMA0_AWR_TC_AWTCE_SHIFT             (63U)
#define CAAM_DMA0_AWR_TC_AWTCE(x)                (((uint64_t)(((uint64_t)(x)) << CAAM_DMA0_AWR_TC_AWTCE_SHIFT)) & CAAM_DMA0_AWR_TC_AWTCE_MASK)
/*! @} */

/*! @name DMA0_AWR_LAT - DMA0 Write Timing Check Latency Register */
/*! @{ */

#define CAAM_DMA0_AWR_LAT_SAWL_MASK              (0xFFFFFFFFU)
#define CAAM_DMA0_AWR_LAT_SAWL_SHIFT             (0U)
#define CAAM_DMA0_AWR_LAT_SAWL(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_DMA0_AWR_LAT_SAWL_SHIFT)) & CAAM_DMA0_AWR_LAT_SAWL_MASK)
/*! @} */

/*! @name MPPKR - Manufacturing Protection Private Key Register */
/*! @{ */

#define CAAM_MPPKR_MPPrivK_MASK                  (0xFFU)
#define CAAM_MPPKR_MPPrivK_SHIFT                 (0U)
#define CAAM_MPPKR_MPPrivK(x)                    (((uint8_t)(((uint8_t)(x)) << CAAM_MPPKR_MPPrivK_SHIFT)) & CAAM_MPPKR_MPPrivK_MASK)
/*! @} */

/* The count of CAAM_MPPKR */
#define CAAM_MPPKR_COUNT                         (64U)

/*! @name MPMR - Manufacturing Protection Message Register */
/*! @{ */

#define CAAM_MPMR_MPMSG_MASK                     (0xFFU)
#define CAAM_MPMR_MPMSG_SHIFT                    (0U)
#define CAAM_MPMR_MPMSG(x)                       (((uint8_t)(((uint8_t)(x)) << CAAM_MPMR_MPMSG_SHIFT)) & CAAM_MPMR_MPMSG_MASK)
/*! @} */

/* The count of CAAM_MPMR */
#define CAAM_MPMR_COUNT                          (32U)

/*! @name MPTESTR - Manufacturing Protection Test Register */
/*! @{ */

#define CAAM_MPTESTR_TEST_VALUE_MASK             (0xFFU)
#define CAAM_MPTESTR_TEST_VALUE_SHIFT            (0U)
#define CAAM_MPTESTR_TEST_VALUE(x)               (((uint8_t)(((uint8_t)(x)) << CAAM_MPTESTR_TEST_VALUE_SHIFT)) & CAAM_MPTESTR_TEST_VALUE_MASK)
/*! @} */

/* The count of CAAM_MPTESTR */
#define CAAM_MPTESTR_COUNT                       (32U)

/*! @name MPECC - Manufacturing Protection ECC Register */
/*! @{ */

#define CAAM_MPECC_MP_SYNDROME_MASK              (0x1FF0000U)
#define CAAM_MPECC_MP_SYNDROME_SHIFT             (16U)
/*! MP_SYNDROME
 *  0b000000000..The MP Key in the SFP passes the ECC check.
 *  0b000000001-0b111111111..The MP Key in the SFP fails the ECC check, and this is the ECC failure syndrome.
 */
#define CAAM_MPECC_MP_SYNDROME(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_MPECC_MP_SYNDROME_SHIFT)) & CAAM_MPECC_MP_SYNDROME_MASK)

#define CAAM_MPECC_MP_ZERO_MASK                  (0x8000000U)
#define CAAM_MPECC_MP_ZERO_SHIFT                 (27U)
/*! MP_ZERO
 *  0b0..The MP Key in the SFP has a non-zero value.
 *  0b1..The MP Key in the SFP is all zeros (unprogrammed).
 */
#define CAAM_MPECC_MP_ZERO(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_MPECC_MP_ZERO_SHIFT)) & CAAM_MPECC_MP_ZERO_MASK)
/*! @} */

/*! @name JDKEKR - Job Descriptor Key Encryption Key Register */
/*! @{ */

#define CAAM_JDKEKR_JDKEK_MASK                   (0xFFFFFFFFU)
#define CAAM_JDKEKR_JDKEK_SHIFT                  (0U)
#define CAAM_JDKEKR_JDKEK(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_JDKEKR_JDKEK_SHIFT)) & CAAM_JDKEKR_JDKEK_MASK)
/*! @} */

/* The count of CAAM_JDKEKR */
#define CAAM_JDKEKR_COUNT                        (8U)

/*! @name TDKEKR - Trusted Descriptor Key Encryption Key Register */
/*! @{ */

#define CAAM_TDKEKR_TDKEK_MASK                   (0xFFFFFFFFU)
#define CAAM_TDKEKR_TDKEK_SHIFT                  (0U)
#define CAAM_TDKEKR_TDKEK(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_TDKEKR_TDKEK_SHIFT)) & CAAM_TDKEKR_TDKEK_MASK)
/*! @} */

/* The count of CAAM_TDKEKR */
#define CAAM_TDKEKR_COUNT                        (8U)

/*! @name TDSKR - Trusted Descriptor Signing Key Register */
/*! @{ */

#define CAAM_TDSKR_TDSK_MASK                     (0xFFFFFFFFU)
#define CAAM_TDSKR_TDSK_SHIFT                    (0U)
#define CAAM_TDSKR_TDSK(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_TDSKR_TDSK_SHIFT)) & CAAM_TDSKR_TDSK_MASK)
/*! @} */

/* The count of CAAM_TDSKR */
#define CAAM_TDSKR_COUNT                         (8U)

/*! @name SKNR - Secure Key Nonce Register */
/*! @{ */

#define CAAM_SKNR_SK_NONCE_LS_MASK               (0xFFFFFFFFU)
#define CAAM_SKNR_SK_NONCE_LS_SHIFT              (0U)
#define CAAM_SKNR_SK_NONCE_LS(x)                 (((uint64_t)(((uint64_t)(x)) << CAAM_SKNR_SK_NONCE_LS_SHIFT)) & CAAM_SKNR_SK_NONCE_LS_MASK)

#define CAAM_SKNR_SK_NONCE_MS_MASK               (0x7FFF00000000U)
#define CAAM_SKNR_SK_NONCE_MS_SHIFT              (32U)
#define CAAM_SKNR_SK_NONCE_MS(x)                 (((uint64_t)(((uint64_t)(x)) << CAAM_SKNR_SK_NONCE_MS_SHIFT)) & CAAM_SKNR_SK_NONCE_MS_MASK)
/*! @} */

/*! @name DMA_STA - DMA Status Register */
/*! @{ */

#define CAAM_DMA_STA_DMA0_ETIF_MASK              (0x1FU)
#define CAAM_DMA_STA_DMA0_ETIF_SHIFT             (0U)
#define CAAM_DMA_STA_DMA0_ETIF(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_STA_DMA0_ETIF_SHIFT)) & CAAM_DMA_STA_DMA0_ETIF_MASK)

#define CAAM_DMA_STA_DMA0_ITIF_MASK              (0x20U)
#define CAAM_DMA_STA_DMA0_ITIF_SHIFT             (5U)
#define CAAM_DMA_STA_DMA0_ITIF(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_STA_DMA0_ITIF_SHIFT)) & CAAM_DMA_STA_DMA0_ITIF_MASK)

#define CAAM_DMA_STA_DMA0_IDLE_MASK              (0x80U)
#define CAAM_DMA_STA_DMA0_IDLE_SHIFT             (7U)
#define CAAM_DMA_STA_DMA0_IDLE(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_STA_DMA0_IDLE_SHIFT)) & CAAM_DMA_STA_DMA0_IDLE_MASK)
/*! @} */

/*! @name DMA_X_AID_7_4_MAP - DMA_X_AID_7_4_MAP */
/*! @{ */

#define CAAM_DMA_X_AID_7_4_MAP_AID4_BID_MASK     (0xFFU)
#define CAAM_DMA_X_AID_7_4_MAP_AID4_BID_SHIFT    (0U)
#define CAAM_DMA_X_AID_7_4_MAP_AID4_BID(x)       (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_7_4_MAP_AID4_BID_SHIFT)) & CAAM_DMA_X_AID_7_4_MAP_AID4_BID_MASK)

#define CAAM_DMA_X_AID_7_4_MAP_AID5_BID_MASK     (0xFF00U)
#define CAAM_DMA_X_AID_7_4_MAP_AID5_BID_SHIFT    (8U)
#define CAAM_DMA_X_AID_7_4_MAP_AID5_BID(x)       (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_7_4_MAP_AID5_BID_SHIFT)) & CAAM_DMA_X_AID_7_4_MAP_AID5_BID_MASK)

#define CAAM_DMA_X_AID_7_4_MAP_AID6_BID_MASK     (0xFF0000U)
#define CAAM_DMA_X_AID_7_4_MAP_AID6_BID_SHIFT    (16U)
#define CAAM_DMA_X_AID_7_4_MAP_AID6_BID(x)       (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_7_4_MAP_AID6_BID_SHIFT)) & CAAM_DMA_X_AID_7_4_MAP_AID6_BID_MASK)

#define CAAM_DMA_X_AID_7_4_MAP_AID7_BID_MASK     (0xFF000000U)
#define CAAM_DMA_X_AID_7_4_MAP_AID7_BID_SHIFT    (24U)
#define CAAM_DMA_X_AID_7_4_MAP_AID7_BID(x)       (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_7_4_MAP_AID7_BID_SHIFT)) & CAAM_DMA_X_AID_7_4_MAP_AID7_BID_MASK)
/*! @} */

/*! @name DMA_X_AID_3_0_MAP - DMA_X_AID_3_0_MAP */
/*! @{ */

#define CAAM_DMA_X_AID_3_0_MAP_AID0_BID_MASK     (0xFFU)
#define CAAM_DMA_X_AID_3_0_MAP_AID0_BID_SHIFT    (0U)
#define CAAM_DMA_X_AID_3_0_MAP_AID0_BID(x)       (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_3_0_MAP_AID0_BID_SHIFT)) & CAAM_DMA_X_AID_3_0_MAP_AID0_BID_MASK)

#define CAAM_DMA_X_AID_3_0_MAP_AID1_BID_MASK     (0xFF00U)
#define CAAM_DMA_X_AID_3_0_MAP_AID1_BID_SHIFT    (8U)
#define CAAM_DMA_X_AID_3_0_MAP_AID1_BID(x)       (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_3_0_MAP_AID1_BID_SHIFT)) & CAAM_DMA_X_AID_3_0_MAP_AID1_BID_MASK)

#define CAAM_DMA_X_AID_3_0_MAP_AID2_BID_MASK     (0xFF0000U)
#define CAAM_DMA_X_AID_3_0_MAP_AID2_BID_SHIFT    (16U)
#define CAAM_DMA_X_AID_3_0_MAP_AID2_BID(x)       (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_3_0_MAP_AID2_BID_SHIFT)) & CAAM_DMA_X_AID_3_0_MAP_AID2_BID_MASK)

#define CAAM_DMA_X_AID_3_0_MAP_AID3_BID_MASK     (0xFF000000U)
#define CAAM_DMA_X_AID_3_0_MAP_AID3_BID_SHIFT    (24U)
#define CAAM_DMA_X_AID_3_0_MAP_AID3_BID(x)       (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_3_0_MAP_AID3_BID_SHIFT)) & CAAM_DMA_X_AID_3_0_MAP_AID3_BID_MASK)
/*! @} */

/*! @name DMA_X_AID_15_12_MAP - DMA_X_AID_15_12_MAP */
/*! @{ */

#define CAAM_DMA_X_AID_15_12_MAP_AID12_BID_MASK  (0xFFU)
#define CAAM_DMA_X_AID_15_12_MAP_AID12_BID_SHIFT (0U)
#define CAAM_DMA_X_AID_15_12_MAP_AID12_BID(x)    (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_15_12_MAP_AID12_BID_SHIFT)) & CAAM_DMA_X_AID_15_12_MAP_AID12_BID_MASK)

#define CAAM_DMA_X_AID_15_12_MAP_AID13_BID_MASK  (0xFF00U)
#define CAAM_DMA_X_AID_15_12_MAP_AID13_BID_SHIFT (8U)
#define CAAM_DMA_X_AID_15_12_MAP_AID13_BID(x)    (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_15_12_MAP_AID13_BID_SHIFT)) & CAAM_DMA_X_AID_15_12_MAP_AID13_BID_MASK)

#define CAAM_DMA_X_AID_15_12_MAP_AID14_BID_MASK  (0xFF0000U)
#define CAAM_DMA_X_AID_15_12_MAP_AID14_BID_SHIFT (16U)
#define CAAM_DMA_X_AID_15_12_MAP_AID14_BID(x)    (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_15_12_MAP_AID14_BID_SHIFT)) & CAAM_DMA_X_AID_15_12_MAP_AID14_BID_MASK)

#define CAAM_DMA_X_AID_15_12_MAP_AID15_BID_MASK  (0xFF000000U)
#define CAAM_DMA_X_AID_15_12_MAP_AID15_BID_SHIFT (24U)
#define CAAM_DMA_X_AID_15_12_MAP_AID15_BID(x)    (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_15_12_MAP_AID15_BID_SHIFT)) & CAAM_DMA_X_AID_15_12_MAP_AID15_BID_MASK)
/*! @} */

/*! @name DMA_X_AID_11_8_MAP - DMA_X_AID_11_8_MAP */
/*! @{ */

#define CAAM_DMA_X_AID_11_8_MAP_AID8_BID_MASK    (0xFFU)
#define CAAM_DMA_X_AID_11_8_MAP_AID8_BID_SHIFT   (0U)
#define CAAM_DMA_X_AID_11_8_MAP_AID8_BID(x)      (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_11_8_MAP_AID8_BID_SHIFT)) & CAAM_DMA_X_AID_11_8_MAP_AID8_BID_MASK)

#define CAAM_DMA_X_AID_11_8_MAP_AID9_BID_MASK    (0xFF00U)
#define CAAM_DMA_X_AID_11_8_MAP_AID9_BID_SHIFT   (8U)
#define CAAM_DMA_X_AID_11_8_MAP_AID9_BID(x)      (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_11_8_MAP_AID9_BID_SHIFT)) & CAAM_DMA_X_AID_11_8_MAP_AID9_BID_MASK)

#define CAAM_DMA_X_AID_11_8_MAP_AID10_BID_MASK   (0xFF0000U)
#define CAAM_DMA_X_AID_11_8_MAP_AID10_BID_SHIFT  (16U)
#define CAAM_DMA_X_AID_11_8_MAP_AID10_BID(x)     (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_11_8_MAP_AID10_BID_SHIFT)) & CAAM_DMA_X_AID_11_8_MAP_AID10_BID_MASK)

#define CAAM_DMA_X_AID_11_8_MAP_AID11_BID_MASK   (0xFF000000U)
#define CAAM_DMA_X_AID_11_8_MAP_AID11_BID_SHIFT  (24U)
#define CAAM_DMA_X_AID_11_8_MAP_AID11_BID(x)     (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_11_8_MAP_AID11_BID_SHIFT)) & CAAM_DMA_X_AID_11_8_MAP_AID11_BID_MASK)
/*! @} */

/*! @name DMA_X_AID_15_0_EN - DMA_X AXI ID Map Enable Register */
/*! @{ */

#define CAAM_DMA_X_AID_15_0_EN_AID0E_MASK        (0x1U)
#define CAAM_DMA_X_AID_15_0_EN_AID0E_SHIFT       (0U)
#define CAAM_DMA_X_AID_15_0_EN_AID0E(x)          (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_15_0_EN_AID0E_SHIFT)) & CAAM_DMA_X_AID_15_0_EN_AID0E_MASK)

#define CAAM_DMA_X_AID_15_0_EN_AID1E_MASK        (0x2U)
#define CAAM_DMA_X_AID_15_0_EN_AID1E_SHIFT       (1U)
#define CAAM_DMA_X_AID_15_0_EN_AID1E(x)          (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_15_0_EN_AID1E_SHIFT)) & CAAM_DMA_X_AID_15_0_EN_AID1E_MASK)

#define CAAM_DMA_X_AID_15_0_EN_AID2E_MASK        (0x4U)
#define CAAM_DMA_X_AID_15_0_EN_AID2E_SHIFT       (2U)
#define CAAM_DMA_X_AID_15_0_EN_AID2E(x)          (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_15_0_EN_AID2E_SHIFT)) & CAAM_DMA_X_AID_15_0_EN_AID2E_MASK)

#define CAAM_DMA_X_AID_15_0_EN_AID3E_MASK        (0x8U)
#define CAAM_DMA_X_AID_15_0_EN_AID3E_SHIFT       (3U)
#define CAAM_DMA_X_AID_15_0_EN_AID3E(x)          (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_15_0_EN_AID3E_SHIFT)) & CAAM_DMA_X_AID_15_0_EN_AID3E_MASK)

#define CAAM_DMA_X_AID_15_0_EN_AID4E_MASK        (0x10U)
#define CAAM_DMA_X_AID_15_0_EN_AID4E_SHIFT       (4U)
#define CAAM_DMA_X_AID_15_0_EN_AID4E(x)          (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_15_0_EN_AID4E_SHIFT)) & CAAM_DMA_X_AID_15_0_EN_AID4E_MASK)

#define CAAM_DMA_X_AID_15_0_EN_AID5E_MASK        (0x20U)
#define CAAM_DMA_X_AID_15_0_EN_AID5E_SHIFT       (5U)
#define CAAM_DMA_X_AID_15_0_EN_AID5E(x)          (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_15_0_EN_AID5E_SHIFT)) & CAAM_DMA_X_AID_15_0_EN_AID5E_MASK)

#define CAAM_DMA_X_AID_15_0_EN_AID6E_MASK        (0x40U)
#define CAAM_DMA_X_AID_15_0_EN_AID6E_SHIFT       (6U)
#define CAAM_DMA_X_AID_15_0_EN_AID6E(x)          (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_15_0_EN_AID6E_SHIFT)) & CAAM_DMA_X_AID_15_0_EN_AID6E_MASK)

#define CAAM_DMA_X_AID_15_0_EN_AID7E_MASK        (0x80U)
#define CAAM_DMA_X_AID_15_0_EN_AID7E_SHIFT       (7U)
#define CAAM_DMA_X_AID_15_0_EN_AID7E(x)          (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_15_0_EN_AID7E_SHIFT)) & CAAM_DMA_X_AID_15_0_EN_AID7E_MASK)

#define CAAM_DMA_X_AID_15_0_EN_AID8E_MASK        (0x100U)
#define CAAM_DMA_X_AID_15_0_EN_AID8E_SHIFT       (8U)
#define CAAM_DMA_X_AID_15_0_EN_AID8E(x)          (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_15_0_EN_AID8E_SHIFT)) & CAAM_DMA_X_AID_15_0_EN_AID8E_MASK)

#define CAAM_DMA_X_AID_15_0_EN_AID9E_MASK        (0x200U)
#define CAAM_DMA_X_AID_15_0_EN_AID9E_SHIFT       (9U)
#define CAAM_DMA_X_AID_15_0_EN_AID9E(x)          (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_15_0_EN_AID9E_SHIFT)) & CAAM_DMA_X_AID_15_0_EN_AID9E_MASK)

#define CAAM_DMA_X_AID_15_0_EN_AID10E_MASK       (0x400U)
#define CAAM_DMA_X_AID_15_0_EN_AID10E_SHIFT      (10U)
#define CAAM_DMA_X_AID_15_0_EN_AID10E(x)         (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_15_0_EN_AID10E_SHIFT)) & CAAM_DMA_X_AID_15_0_EN_AID10E_MASK)

#define CAAM_DMA_X_AID_15_0_EN_AID11E_MASK       (0x800U)
#define CAAM_DMA_X_AID_15_0_EN_AID11E_SHIFT      (11U)
#define CAAM_DMA_X_AID_15_0_EN_AID11E(x)         (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_15_0_EN_AID11E_SHIFT)) & CAAM_DMA_X_AID_15_0_EN_AID11E_MASK)

#define CAAM_DMA_X_AID_15_0_EN_AID12E_MASK       (0x1000U)
#define CAAM_DMA_X_AID_15_0_EN_AID12E_SHIFT      (12U)
#define CAAM_DMA_X_AID_15_0_EN_AID12E(x)         (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_15_0_EN_AID12E_SHIFT)) & CAAM_DMA_X_AID_15_0_EN_AID12E_MASK)

#define CAAM_DMA_X_AID_15_0_EN_AID13E_MASK       (0x2000U)
#define CAAM_DMA_X_AID_15_0_EN_AID13E_SHIFT      (13U)
#define CAAM_DMA_X_AID_15_0_EN_AID13E(x)         (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_15_0_EN_AID13E_SHIFT)) & CAAM_DMA_X_AID_15_0_EN_AID13E_MASK)

#define CAAM_DMA_X_AID_15_0_EN_AID14E_MASK       (0x4000U)
#define CAAM_DMA_X_AID_15_0_EN_AID14E_SHIFT      (14U)
#define CAAM_DMA_X_AID_15_0_EN_AID14E(x)         (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_15_0_EN_AID14E_SHIFT)) & CAAM_DMA_X_AID_15_0_EN_AID14E_MASK)

#define CAAM_DMA_X_AID_15_0_EN_AID15E_MASK       (0x8000U)
#define CAAM_DMA_X_AID_15_0_EN_AID15E_SHIFT      (15U)
#define CAAM_DMA_X_AID_15_0_EN_AID15E(x)         (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AID_15_0_EN_AID15E_SHIFT)) & CAAM_DMA_X_AID_15_0_EN_AID15E_MASK)
/*! @} */

/*! @name DMA_X_ARTC_CTL - DMA_X AXI Read Timing Check Control Register */
/*! @{ */

#define CAAM_DMA_X_ARTC_CTL_ART_MASK             (0xFFFU)
#define CAAM_DMA_X_ARTC_CTL_ART_SHIFT            (0U)
#define CAAM_DMA_X_ARTC_CTL_ART(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_ARTC_CTL_ART_SHIFT)) & CAAM_DMA_X_ARTC_CTL_ART_MASK)

#define CAAM_DMA_X_ARTC_CTL_ARL_MASK             (0xFFF0000U)
#define CAAM_DMA_X_ARTC_CTL_ARL_SHIFT            (16U)
#define CAAM_DMA_X_ARTC_CTL_ARL(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_ARTC_CTL_ARL_SHIFT)) & CAAM_DMA_X_ARTC_CTL_ARL_MASK)

#define CAAM_DMA_X_ARTC_CTL_ARTL_MASK            (0x10000000U)
#define CAAM_DMA_X_ARTC_CTL_ARTL_SHIFT           (28U)
#define CAAM_DMA_X_ARTC_CTL_ARTL(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_ARTC_CTL_ARTL_SHIFT)) & CAAM_DMA_X_ARTC_CTL_ARTL_MASK)

#define CAAM_DMA_X_ARTC_CTL_ARTT_MASK            (0x20000000U)
#define CAAM_DMA_X_ARTC_CTL_ARTT_SHIFT           (29U)
#define CAAM_DMA_X_ARTC_CTL_ARTT(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_ARTC_CTL_ARTT_SHIFT)) & CAAM_DMA_X_ARTC_CTL_ARTT_MASK)

#define CAAM_DMA_X_ARTC_CTL_ARCT_MASK            (0x40000000U)
#define CAAM_DMA_X_ARTC_CTL_ARCT_SHIFT           (30U)
#define CAAM_DMA_X_ARTC_CTL_ARCT(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_ARTC_CTL_ARCT_SHIFT)) & CAAM_DMA_X_ARTC_CTL_ARCT_MASK)

#define CAAM_DMA_X_ARTC_CTL_ARTCE_MASK           (0x80000000U)
#define CAAM_DMA_X_ARTC_CTL_ARTCE_SHIFT          (31U)
#define CAAM_DMA_X_ARTC_CTL_ARTCE(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_ARTC_CTL_ARTCE_SHIFT)) & CAAM_DMA_X_ARTC_CTL_ARTCE_MASK)
/*! @} */

/*! @name DMA_X_ARTC_LC - DMA_X AXI Read Timing Check Late Count Register */
/*! @{ */

#define CAAM_DMA_X_ARTC_LC_ARLC_MASK             (0xFFFFFU)
#define CAAM_DMA_X_ARTC_LC_ARLC_SHIFT            (0U)
#define CAAM_DMA_X_ARTC_LC_ARLC(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_ARTC_LC_ARLC_SHIFT)) & CAAM_DMA_X_ARTC_LC_ARLC_MASK)
/*! @} */

/*! @name DMA_X_ARTC_SC - DMA_X AXI Read Timing Check Sample Count Register */
/*! @{ */

#define CAAM_DMA_X_ARTC_SC_ARSC_MASK             (0xFFFFFU)
#define CAAM_DMA_X_ARTC_SC_ARSC_SHIFT            (0U)
#define CAAM_DMA_X_ARTC_SC_ARSC(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_ARTC_SC_ARSC_SHIFT)) & CAAM_DMA_X_ARTC_SC_ARSC_MASK)
/*! @} */

/*! @name DMA_X_ARTC_LAT - DMA_X Read Timing Check Latency Register */
/*! @{ */

#define CAAM_DMA_X_ARTC_LAT_SARL_MASK            (0xFFFFFFFFU)
#define CAAM_DMA_X_ARTC_LAT_SARL_SHIFT           (0U)
#define CAAM_DMA_X_ARTC_LAT_SARL(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_ARTC_LAT_SARL_SHIFT)) & CAAM_DMA_X_ARTC_LAT_SARL_MASK)
/*! @} */

/*! @name DMA_X_AWTC_CTL - DMA_X AXI Write Timing Check Control Register */
/*! @{ */

#define CAAM_DMA_X_AWTC_CTL_AWT_MASK             (0xFFFU)
#define CAAM_DMA_X_AWTC_CTL_AWT_SHIFT            (0U)
#define CAAM_DMA_X_AWTC_CTL_AWT(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AWTC_CTL_AWT_SHIFT)) & CAAM_DMA_X_AWTC_CTL_AWT_MASK)

#define CAAM_DMA_X_AWTC_CTL_AWL_MASK             (0xFFF0000U)
#define CAAM_DMA_X_AWTC_CTL_AWL_SHIFT            (16U)
#define CAAM_DMA_X_AWTC_CTL_AWL(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AWTC_CTL_AWL_SHIFT)) & CAAM_DMA_X_AWTC_CTL_AWL_MASK)

#define CAAM_DMA_X_AWTC_CTL_AWTT_MASK            (0x20000000U)
#define CAAM_DMA_X_AWTC_CTL_AWTT_SHIFT           (29U)
#define CAAM_DMA_X_AWTC_CTL_AWTT(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AWTC_CTL_AWTT_SHIFT)) & CAAM_DMA_X_AWTC_CTL_AWTT_MASK)

#define CAAM_DMA_X_AWTC_CTL_AWCT_MASK            (0x40000000U)
#define CAAM_DMA_X_AWTC_CTL_AWCT_SHIFT           (30U)
#define CAAM_DMA_X_AWTC_CTL_AWCT(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AWTC_CTL_AWCT_SHIFT)) & CAAM_DMA_X_AWTC_CTL_AWCT_MASK)

#define CAAM_DMA_X_AWTC_CTL_AWTCE_MASK           (0x80000000U)
#define CAAM_DMA_X_AWTC_CTL_AWTCE_SHIFT          (31U)
#define CAAM_DMA_X_AWTC_CTL_AWTCE(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AWTC_CTL_AWTCE_SHIFT)) & CAAM_DMA_X_AWTC_CTL_AWTCE_MASK)
/*! @} */

/*! @name DMA_X_AWTC_LC - DMA_X AXI Write Timing Check Late Count Register */
/*! @{ */

#define CAAM_DMA_X_AWTC_LC_AWLC_MASK             (0xFFFFFU)
#define CAAM_DMA_X_AWTC_LC_AWLC_SHIFT            (0U)
#define CAAM_DMA_X_AWTC_LC_AWLC(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AWTC_LC_AWLC_SHIFT)) & CAAM_DMA_X_AWTC_LC_AWLC_MASK)
/*! @} */

/*! @name DMA_X_AWTC_SC - DMA_X AXI Write Timing Check Sample Count Register */
/*! @{ */

#define CAAM_DMA_X_AWTC_SC_AWSC_MASK             (0xFFFFFU)
#define CAAM_DMA_X_AWTC_SC_AWSC_SHIFT            (0U)
#define CAAM_DMA_X_AWTC_SC_AWSC(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AWTC_SC_AWSC_SHIFT)) & CAAM_DMA_X_AWTC_SC_AWSC_MASK)
/*! @} */

/*! @name DMA_X_AWTC_LAT - DMA_X Write Timing Check Latency Register */
/*! @{ */

#define CAAM_DMA_X_AWTC_LAT_SAWL_MASK            (0xFFFFFFFFU)
#define CAAM_DMA_X_AWTC_LAT_SAWL_SHIFT           (0U)
#define CAAM_DMA_X_AWTC_LAT_SAWL(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_DMA_X_AWTC_LAT_SAWL_SHIFT)) & CAAM_DMA_X_AWTC_LAT_SAWL_MASK)
/*! @} */

/*! @name RTMCTL - RNG TRNG Miscellaneous Control Register */
/*! @{ */

#define CAAM_RTMCTL_SAMP_MODE_MASK               (0x3U)
#define CAAM_RTMCTL_SAMP_MODE_SHIFT              (0U)
/*! SAMP_MODE
 *  0b00..use Von Neumann data into both Entropy shifter and Statistical Checker
 *  0b01..use raw data into both Entropy shifter and Statistical Checker
 *  0b10..use Von Neumann data into Entropy shifter. Use raw data into Statistical Checker
 *  0b11..undefined/reserved.
 */
#define CAAM_RTMCTL_SAMP_MODE(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTMCTL_SAMP_MODE_SHIFT)) & CAAM_RTMCTL_SAMP_MODE_MASK)

#define CAAM_RTMCTL_OSC_DIV_MASK                 (0xCU)
#define CAAM_RTMCTL_OSC_DIV_SHIFT                (2U)
/*! OSC_DIV
 *  0b00..use ring oscillator with no divide
 *  0b01..use ring oscillator divided-by-2
 *  0b10..use ring oscillator divided-by-4
 *  0b11..use ring oscillator divided-by-8
 */
#define CAAM_RTMCTL_OSC_DIV(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_RTMCTL_OSC_DIV_SHIFT)) & CAAM_RTMCTL_OSC_DIV_MASK)

#define CAAM_RTMCTL_CLK_OUT_EN_MASK              (0x10U)
#define CAAM_RTMCTL_CLK_OUT_EN_SHIFT             (4U)
#define CAAM_RTMCTL_CLK_OUT_EN(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_RTMCTL_CLK_OUT_EN_SHIFT)) & CAAM_RTMCTL_CLK_OUT_EN_MASK)

#define CAAM_RTMCTL_TRNG_ACC_MASK                (0x20U)
#define CAAM_RTMCTL_TRNG_ACC_SHIFT               (5U)
#define CAAM_RTMCTL_TRNG_ACC(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_RTMCTL_TRNG_ACC_SHIFT)) & CAAM_RTMCTL_TRNG_ACC_MASK)

#define CAAM_RTMCTL_RST_DEF_MASK                 (0x40U)
#define CAAM_RTMCTL_RST_DEF_SHIFT                (6U)
#define CAAM_RTMCTL_RST_DEF(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_RTMCTL_RST_DEF_SHIFT)) & CAAM_RTMCTL_RST_DEF_MASK)

#define CAAM_RTMCTL_FORCE_SYSCLK_MASK            (0x80U)
#define CAAM_RTMCTL_FORCE_SYSCLK_SHIFT           (7U)
#define CAAM_RTMCTL_FORCE_SYSCLK(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_RTMCTL_FORCE_SYSCLK_SHIFT)) & CAAM_RTMCTL_FORCE_SYSCLK_MASK)

#define CAAM_RTMCTL_FCT_FAIL_MASK                (0x100U)
#define CAAM_RTMCTL_FCT_FAIL_SHIFT               (8U)
#define CAAM_RTMCTL_FCT_FAIL(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_RTMCTL_FCT_FAIL_SHIFT)) & CAAM_RTMCTL_FCT_FAIL_MASK)

#define CAAM_RTMCTL_FCT_VAL_MASK                 (0x200U)
#define CAAM_RTMCTL_FCT_VAL_SHIFT                (9U)
#define CAAM_RTMCTL_FCT_VAL(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_RTMCTL_FCT_VAL_SHIFT)) & CAAM_RTMCTL_FCT_VAL_MASK)

#define CAAM_RTMCTL_ENT_VAL_MASK                 (0x400U)
#define CAAM_RTMCTL_ENT_VAL_SHIFT                (10U)
#define CAAM_RTMCTL_ENT_VAL(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_RTMCTL_ENT_VAL_SHIFT)) & CAAM_RTMCTL_ENT_VAL_MASK)

#define CAAM_RTMCTL_TST_OUT_MASK                 (0x800U)
#define CAAM_RTMCTL_TST_OUT_SHIFT                (11U)
#define CAAM_RTMCTL_TST_OUT(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_RTMCTL_TST_OUT_SHIFT)) & CAAM_RTMCTL_TST_OUT_MASK)

#define CAAM_RTMCTL_ERR_MASK                     (0x1000U)
#define CAAM_RTMCTL_ERR_SHIFT                    (12U)
#define CAAM_RTMCTL_ERR(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_RTMCTL_ERR_SHIFT)) & CAAM_RTMCTL_ERR_MASK)

#define CAAM_RTMCTL_TSTOP_OK_MASK                (0x2000U)
#define CAAM_RTMCTL_TSTOP_OK_SHIFT               (13U)
#define CAAM_RTMCTL_TSTOP_OK(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_RTMCTL_TSTOP_OK_SHIFT)) & CAAM_RTMCTL_TSTOP_OK_MASK)

#define CAAM_RTMCTL_PRGM_MASK                    (0x10000U)
#define CAAM_RTMCTL_PRGM_SHIFT                   (16U)
#define CAAM_RTMCTL_PRGM(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_RTMCTL_PRGM_SHIFT)) & CAAM_RTMCTL_PRGM_MASK)
/*! @} */

/*! @name RTSCMISC - RNG TRNG Statistical Check Miscellaneous Register */
/*! @{ */

#define CAAM_RTSCMISC_LRUN_MAX_MASK              (0xFFU)
#define CAAM_RTSCMISC_LRUN_MAX_SHIFT             (0U)
#define CAAM_RTSCMISC_LRUN_MAX(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCMISC_LRUN_MAX_SHIFT)) & CAAM_RTSCMISC_LRUN_MAX_MASK)

#define CAAM_RTSCMISC_RTY_CNT_MASK               (0xF0000U)
#define CAAM_RTSCMISC_RTY_CNT_SHIFT              (16U)
#define CAAM_RTSCMISC_RTY_CNT(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCMISC_RTY_CNT_SHIFT)) & CAAM_RTSCMISC_RTY_CNT_MASK)
/*! @} */

/*! @name RTPKRRNG - RNG TRNG Poker Range Register */
/*! @{ */

#define CAAM_RTPKRRNG_PKR_RNG_MASK               (0xFFFFU)
#define CAAM_RTPKRRNG_PKR_RNG_SHIFT              (0U)
#define CAAM_RTPKRRNG_PKR_RNG(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTPKRRNG_PKR_RNG_SHIFT)) & CAAM_RTPKRRNG_PKR_RNG_MASK)
/*! @} */

/*! @name RTPKRMAX - RNG TRNG Poker Maximum Limit Register */
/*! @{ */

#define CAAM_RTPKRMAX_PKR_MAX_MASK               (0xFFFFFFU)
#define CAAM_RTPKRMAX_PKR_MAX_SHIFT              (0U)
#define CAAM_RTPKRMAX_PKR_MAX(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTPKRMAX_PKR_MAX_SHIFT)) & CAAM_RTPKRMAX_PKR_MAX_MASK)
/*! @} */

/*! @name RTPKRSQ - RNG TRNG Poker Square Calculation Result Register */
/*! @{ */

#define CAAM_RTPKRSQ_PKR_SQ_MASK                 (0xFFFFFFU)
#define CAAM_RTPKRSQ_PKR_SQ_SHIFT                (0U)
#define CAAM_RTPKRSQ_PKR_SQ(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_RTPKRSQ_PKR_SQ_SHIFT)) & CAAM_RTPKRSQ_PKR_SQ_MASK)
/*! @} */

/*! @name RTSDCTL - RNG TRNG Seed Control Register */
/*! @{ */

#define CAAM_RTSDCTL_SAMP_SIZE_MASK              (0xFFFFU)
#define CAAM_RTSDCTL_SAMP_SIZE_SHIFT             (0U)
#define CAAM_RTSDCTL_SAMP_SIZE(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_RTSDCTL_SAMP_SIZE_SHIFT)) & CAAM_RTSDCTL_SAMP_SIZE_MASK)

#define CAAM_RTSDCTL_ENT_DLY_MASK                (0xFFFF0000U)
#define CAAM_RTSDCTL_ENT_DLY_SHIFT               (16U)
#define CAAM_RTSDCTL_ENT_DLY(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_RTSDCTL_ENT_DLY_SHIFT)) & CAAM_RTSDCTL_ENT_DLY_MASK)
/*! @} */

/*! @name RTSBLIM - RNG TRNG Sparse Bit Limit Register */
/*! @{ */

#define CAAM_RTSBLIM_SB_LIM_MASK                 (0x3FFU)
#define CAAM_RTSBLIM_SB_LIM_SHIFT                (0U)
#define CAAM_RTSBLIM_SB_LIM(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_RTSBLIM_SB_LIM_SHIFT)) & CAAM_RTSBLIM_SB_LIM_MASK)
/*! @} */

/*! @name RTTOTSAM - RNG TRNG Total Samples Register */
/*! @{ */

#define CAAM_RTTOTSAM_TOT_SAM_MASK               (0xFFFFFU)
#define CAAM_RTTOTSAM_TOT_SAM_SHIFT              (0U)
#define CAAM_RTTOTSAM_TOT_SAM(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTTOTSAM_TOT_SAM_SHIFT)) & CAAM_RTTOTSAM_TOT_SAM_MASK)
/*! @} */

/*! @name RTFRQMIN - RNG TRNG Frequency Count Minimum Limit Register */
/*! @{ */

#define CAAM_RTFRQMIN_FRQ_MIN_MASK               (0x3FFFFFU)
#define CAAM_RTFRQMIN_FRQ_MIN_SHIFT              (0U)
#define CAAM_RTFRQMIN_FRQ_MIN(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTFRQMIN_FRQ_MIN_SHIFT)) & CAAM_RTFRQMIN_FRQ_MIN_MASK)
/*! @} */

/*! @name RTFRQCNT - RNG TRNG Frequency Count Register */
/*! @{ */

#define CAAM_RTFRQCNT_FRQ_CNT_MASK               (0x3FFFFFU)
#define CAAM_RTFRQCNT_FRQ_CNT_SHIFT              (0U)
#define CAAM_RTFRQCNT_FRQ_CNT(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTFRQCNT_FRQ_CNT_SHIFT)) & CAAM_RTFRQCNT_FRQ_CNT_MASK)
/*! @} */

/*! @name RTSCMC - RNG TRNG Statistical Check Monobit Count Register */
/*! @{ */

#define CAAM_RTSCMC_MONO_CNT_MASK                (0xFFFFU)
#define CAAM_RTSCMC_MONO_CNT_SHIFT               (0U)
#define CAAM_RTSCMC_MONO_CNT(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCMC_MONO_CNT_SHIFT)) & CAAM_RTSCMC_MONO_CNT_MASK)
/*! @} */

/*! @name RTSCR1C - RNG TRNG Statistical Check Run Length 1 Count Register */
/*! @{ */

#define CAAM_RTSCR1C_R1_0_COUNT_MASK             (0x7FFFU)
#define CAAM_RTSCR1C_R1_0_COUNT_SHIFT            (0U)
#define CAAM_RTSCR1C_R1_0_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR1C_R1_0_COUNT_SHIFT)) & CAAM_RTSCR1C_R1_0_COUNT_MASK)

#define CAAM_RTSCR1C_R1_1_COUNT_MASK             (0x7FFF0000U)
#define CAAM_RTSCR1C_R1_1_COUNT_SHIFT            (16U)
#define CAAM_RTSCR1C_R1_1_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR1C_R1_1_COUNT_SHIFT)) & CAAM_RTSCR1C_R1_1_COUNT_MASK)
/*! @} */

/*! @name RTSCR2C - RNG TRNG Statistical Check Run Length 2 Count Register */
/*! @{ */

#define CAAM_RTSCR2C_R2_0_COUNT_MASK             (0x3FFFU)
#define CAAM_RTSCR2C_R2_0_COUNT_SHIFT            (0U)
#define CAAM_RTSCR2C_R2_0_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR2C_R2_0_COUNT_SHIFT)) & CAAM_RTSCR2C_R2_0_COUNT_MASK)

#define CAAM_RTSCR2C_R2_1_COUNT_MASK             (0x3FFF0000U)
#define CAAM_RTSCR2C_R2_1_COUNT_SHIFT            (16U)
#define CAAM_RTSCR2C_R2_1_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR2C_R2_1_COUNT_SHIFT)) & CAAM_RTSCR2C_R2_1_COUNT_MASK)
/*! @} */

/*! @name RTSCR3C - RNG TRNG Statistical Check Run Length 3 Count Register */
/*! @{ */

#define CAAM_RTSCR3C_R3_0_COUNT_MASK             (0x1FFFU)
#define CAAM_RTSCR3C_R3_0_COUNT_SHIFT            (0U)
#define CAAM_RTSCR3C_R3_0_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR3C_R3_0_COUNT_SHIFT)) & CAAM_RTSCR3C_R3_0_COUNT_MASK)

#define CAAM_RTSCR3C_R3_1_COUNT_MASK             (0x1FFF0000U)
#define CAAM_RTSCR3C_R3_1_COUNT_SHIFT            (16U)
#define CAAM_RTSCR3C_R3_1_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR3C_R3_1_COUNT_SHIFT)) & CAAM_RTSCR3C_R3_1_COUNT_MASK)
/*! @} */

/*! @name RTSCR4C - RNG TRNG Statistical Check Run Length 4 Count Register */
/*! @{ */

#define CAAM_RTSCR4C_R4_0_COUNT_MASK             (0xFFFU)
#define CAAM_RTSCR4C_R4_0_COUNT_SHIFT            (0U)
#define CAAM_RTSCR4C_R4_0_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR4C_R4_0_COUNT_SHIFT)) & CAAM_RTSCR4C_R4_0_COUNT_MASK)

#define CAAM_RTSCR4C_R4_1_COUNT_MASK             (0xFFF0000U)
#define CAAM_RTSCR4C_R4_1_COUNT_SHIFT            (16U)
#define CAAM_RTSCR4C_R4_1_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR4C_R4_1_COUNT_SHIFT)) & CAAM_RTSCR4C_R4_1_COUNT_MASK)
/*! @} */

/*! @name RTSCR5C - RNG TRNG Statistical Check Run Length 5 Count Register */
/*! @{ */

#define CAAM_RTSCR5C_R5_0_COUNT_MASK             (0x7FFU)
#define CAAM_RTSCR5C_R5_0_COUNT_SHIFT            (0U)
#define CAAM_RTSCR5C_R5_0_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR5C_R5_0_COUNT_SHIFT)) & CAAM_RTSCR5C_R5_0_COUNT_MASK)

#define CAAM_RTSCR5C_R5_1_COUNT_MASK             (0x7FF0000U)
#define CAAM_RTSCR5C_R5_1_COUNT_SHIFT            (16U)
#define CAAM_RTSCR5C_R5_1_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR5C_R5_1_COUNT_SHIFT)) & CAAM_RTSCR5C_R5_1_COUNT_MASK)
/*! @} */

/*! @name RTSCR6PC - RNG TRNG Statistical Check Run Length 6+ Count Register */
/*! @{ */

#define CAAM_RTSCR6PC_R6P_0_COUNT_MASK           (0x7FFU)
#define CAAM_RTSCR6PC_R6P_0_COUNT_SHIFT          (0U)
#define CAAM_RTSCR6PC_R6P_0_COUNT(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR6PC_R6P_0_COUNT_SHIFT)) & CAAM_RTSCR6PC_R6P_0_COUNT_MASK)

#define CAAM_RTSCR6PC_R6P_1_COUNT_MASK           (0x7FF0000U)
#define CAAM_RTSCR6PC_R6P_1_COUNT_SHIFT          (16U)
#define CAAM_RTSCR6PC_R6P_1_COUNT(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR6PC_R6P_1_COUNT_SHIFT)) & CAAM_RTSCR6PC_R6P_1_COUNT_MASK)
/*! @} */

/*! @name RTFRQMAX - RNG TRNG Frequency Count Maximum Limit Register */
/*! @{ */

#define CAAM_RTFRQMAX_FRQ_MAX_MASK               (0x3FFFFFU)
#define CAAM_RTFRQMAX_FRQ_MAX_SHIFT              (0U)
#define CAAM_RTFRQMAX_FRQ_MAX(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTFRQMAX_FRQ_MAX_SHIFT)) & CAAM_RTFRQMAX_FRQ_MAX_MASK)
/*! @} */

/*! @name RTSCML - RNG TRNG Statistical Check Monobit Limit Register */
/*! @{ */

#define CAAM_RTSCML_MONO_MAX_MASK                (0xFFFFU)
#define CAAM_RTSCML_MONO_MAX_SHIFT               (0U)
#define CAAM_RTSCML_MONO_MAX(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCML_MONO_MAX_SHIFT)) & CAAM_RTSCML_MONO_MAX_MASK)

#define CAAM_RTSCML_MONO_RNG_MASK                (0xFFFF0000U)
#define CAAM_RTSCML_MONO_RNG_SHIFT               (16U)
#define CAAM_RTSCML_MONO_RNG(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCML_MONO_RNG_SHIFT)) & CAAM_RTSCML_MONO_RNG_MASK)
/*! @} */

/*! @name RTSCR1L - RNG TRNG Statistical Check Run Length 1 Limit Register */
/*! @{ */

#define CAAM_RTSCR1L_RUN1_MAX_MASK               (0x7FFFU)
#define CAAM_RTSCR1L_RUN1_MAX_SHIFT              (0U)
#define CAAM_RTSCR1L_RUN1_MAX(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR1L_RUN1_MAX_SHIFT)) & CAAM_RTSCR1L_RUN1_MAX_MASK)

#define CAAM_RTSCR1L_RUN1_RNG_MASK               (0x7FFF0000U)
#define CAAM_RTSCR1L_RUN1_RNG_SHIFT              (16U)
#define CAAM_RTSCR1L_RUN1_RNG(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR1L_RUN1_RNG_SHIFT)) & CAAM_RTSCR1L_RUN1_RNG_MASK)
/*! @} */

/*! @name RTSCR2L - RNG TRNG Statistical Check Run Length 2 Limit Register */
/*! @{ */

#define CAAM_RTSCR2L_RUN2_MAX_MASK               (0x3FFFU)
#define CAAM_RTSCR2L_RUN2_MAX_SHIFT              (0U)
#define CAAM_RTSCR2L_RUN2_MAX(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR2L_RUN2_MAX_SHIFT)) & CAAM_RTSCR2L_RUN2_MAX_MASK)

#define CAAM_RTSCR2L_RUN2_RNG_MASK               (0x3FFF0000U)
#define CAAM_RTSCR2L_RUN2_RNG_SHIFT              (16U)
#define CAAM_RTSCR2L_RUN2_RNG(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR2L_RUN2_RNG_SHIFT)) & CAAM_RTSCR2L_RUN2_RNG_MASK)
/*! @} */

/*! @name RTSCR3L - RNG TRNG Statistical Check Run Length 3 Limit Register */
/*! @{ */

#define CAAM_RTSCR3L_RUN3_MAX_MASK               (0x1FFFU)
#define CAAM_RTSCR3L_RUN3_MAX_SHIFT              (0U)
#define CAAM_RTSCR3L_RUN3_MAX(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR3L_RUN3_MAX_SHIFT)) & CAAM_RTSCR3L_RUN3_MAX_MASK)

#define CAAM_RTSCR3L_RUN3_RNG_MASK               (0x1FFF0000U)
#define CAAM_RTSCR3L_RUN3_RNG_SHIFT              (16U)
#define CAAM_RTSCR3L_RUN3_RNG(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR3L_RUN3_RNG_SHIFT)) & CAAM_RTSCR3L_RUN3_RNG_MASK)
/*! @} */

/*! @name RTSCR4L - RNG TRNG Statistical Check Run Length 4 Limit Register */
/*! @{ */

#define CAAM_RTSCR4L_RUN4_MAX_MASK               (0xFFFU)
#define CAAM_RTSCR4L_RUN4_MAX_SHIFT              (0U)
#define CAAM_RTSCR4L_RUN4_MAX(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR4L_RUN4_MAX_SHIFT)) & CAAM_RTSCR4L_RUN4_MAX_MASK)

#define CAAM_RTSCR4L_RUN4_RNG_MASK               (0xFFF0000U)
#define CAAM_RTSCR4L_RUN4_RNG_SHIFT              (16U)
#define CAAM_RTSCR4L_RUN4_RNG(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR4L_RUN4_RNG_SHIFT)) & CAAM_RTSCR4L_RUN4_RNG_MASK)
/*! @} */

/*! @name RTSCR5L - RNG TRNG Statistical Check Run Length 5 Limit Register */
/*! @{ */

#define CAAM_RTSCR5L_RUN5_MAX_MASK               (0x7FFU)
#define CAAM_RTSCR5L_RUN5_MAX_SHIFT              (0U)
#define CAAM_RTSCR5L_RUN5_MAX(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR5L_RUN5_MAX_SHIFT)) & CAAM_RTSCR5L_RUN5_MAX_MASK)

#define CAAM_RTSCR5L_RUN5_RNG_MASK               (0x7FF0000U)
#define CAAM_RTSCR5L_RUN5_RNG_SHIFT              (16U)
#define CAAM_RTSCR5L_RUN5_RNG(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR5L_RUN5_RNG_SHIFT)) & CAAM_RTSCR5L_RUN5_RNG_MASK)
/*! @} */

/*! @name RTSCR6PL - RNG TRNG Statistical Check Run Length 6+ Limit Register */
/*! @{ */

#define CAAM_RTSCR6PL_RUN6P_MAX_MASK             (0x7FFU)
#define CAAM_RTSCR6PL_RUN6P_MAX_SHIFT            (0U)
#define CAAM_RTSCR6PL_RUN6P_MAX(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR6PL_RUN6P_MAX_SHIFT)) & CAAM_RTSCR6PL_RUN6P_MAX_MASK)

#define CAAM_RTSCR6PL_RUN6P_RNG_MASK             (0x7FF0000U)
#define CAAM_RTSCR6PL_RUN6P_RNG_SHIFT            (16U)
#define CAAM_RTSCR6PL_RUN6P_RNG(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_RTSCR6PL_RUN6P_RNG_SHIFT)) & CAAM_RTSCR6PL_RUN6P_RNG_MASK)
/*! @} */

/*! @name RTSTATUS - RNG TRNG Status Register */
/*! @{ */

#define CAAM_RTSTATUS_F1BR0TF_MASK               (0x1U)
#define CAAM_RTSTATUS_F1BR0TF_SHIFT              (0U)
#define CAAM_RTSTATUS_F1BR0TF(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTSTATUS_F1BR0TF_SHIFT)) & CAAM_RTSTATUS_F1BR0TF_MASK)

#define CAAM_RTSTATUS_F1BR1TF_MASK               (0x2U)
#define CAAM_RTSTATUS_F1BR1TF_SHIFT              (1U)
#define CAAM_RTSTATUS_F1BR1TF(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTSTATUS_F1BR1TF_SHIFT)) & CAAM_RTSTATUS_F1BR1TF_MASK)

#define CAAM_RTSTATUS_F2BR0TF_MASK               (0x4U)
#define CAAM_RTSTATUS_F2BR0TF_SHIFT              (2U)
#define CAAM_RTSTATUS_F2BR0TF(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTSTATUS_F2BR0TF_SHIFT)) & CAAM_RTSTATUS_F2BR0TF_MASK)

#define CAAM_RTSTATUS_F2BR1TF_MASK               (0x8U)
#define CAAM_RTSTATUS_F2BR1TF_SHIFT              (3U)
#define CAAM_RTSTATUS_F2BR1TF(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTSTATUS_F2BR1TF_SHIFT)) & CAAM_RTSTATUS_F2BR1TF_MASK)

#define CAAM_RTSTATUS_F3BR01TF_MASK              (0x10U)
#define CAAM_RTSTATUS_F3BR01TF_SHIFT             (4U)
#define CAAM_RTSTATUS_F3BR01TF(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_RTSTATUS_F3BR01TF_SHIFT)) & CAAM_RTSTATUS_F3BR01TF_MASK)

#define CAAM_RTSTATUS_F3BR1TF_MASK               (0x20U)
#define CAAM_RTSTATUS_F3BR1TF_SHIFT              (5U)
#define CAAM_RTSTATUS_F3BR1TF(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTSTATUS_F3BR1TF_SHIFT)) & CAAM_RTSTATUS_F3BR1TF_MASK)

#define CAAM_RTSTATUS_F4BR0TF_MASK               (0x40U)
#define CAAM_RTSTATUS_F4BR0TF_SHIFT              (6U)
#define CAAM_RTSTATUS_F4BR0TF(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTSTATUS_F4BR0TF_SHIFT)) & CAAM_RTSTATUS_F4BR0TF_MASK)

#define CAAM_RTSTATUS_F4BR1TF_MASK               (0x80U)
#define CAAM_RTSTATUS_F4BR1TF_SHIFT              (7U)
#define CAAM_RTSTATUS_F4BR1TF(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTSTATUS_F4BR1TF_SHIFT)) & CAAM_RTSTATUS_F4BR1TF_MASK)

#define CAAM_RTSTATUS_F5BR0TF_MASK               (0x100U)
#define CAAM_RTSTATUS_F5BR0TF_SHIFT              (8U)
#define CAAM_RTSTATUS_F5BR0TF(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTSTATUS_F5BR0TF_SHIFT)) & CAAM_RTSTATUS_F5BR0TF_MASK)

#define CAAM_RTSTATUS_F5BR1TF_MASK               (0x200U)
#define CAAM_RTSTATUS_F5BR1TF_SHIFT              (9U)
#define CAAM_RTSTATUS_F5BR1TF(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_RTSTATUS_F5BR1TF_SHIFT)) & CAAM_RTSTATUS_F5BR1TF_MASK)

#define CAAM_RTSTATUS_F6PBR0TF_MASK              (0x400U)
#define CAAM_RTSTATUS_F6PBR0TF_SHIFT             (10U)
#define CAAM_RTSTATUS_F6PBR0TF(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_RTSTATUS_F6PBR0TF_SHIFT)) & CAAM_RTSTATUS_F6PBR0TF_MASK)

#define CAAM_RTSTATUS_F6PBR1TF_MASK              (0x800U)
#define CAAM_RTSTATUS_F6PBR1TF_SHIFT             (11U)
#define CAAM_RTSTATUS_F6PBR1TF(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_RTSTATUS_F6PBR1TF_SHIFT)) & CAAM_RTSTATUS_F6PBR1TF_MASK)

#define CAAM_RTSTATUS_FSBTF_MASK                 (0x1000U)
#define CAAM_RTSTATUS_FSBTF_SHIFT                (12U)
#define CAAM_RTSTATUS_FSBTF(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_RTSTATUS_FSBTF_SHIFT)) & CAAM_RTSTATUS_FSBTF_MASK)

#define CAAM_RTSTATUS_FLRTF_MASK                 (0x2000U)
#define CAAM_RTSTATUS_FLRTF_SHIFT                (13U)
#define CAAM_RTSTATUS_FLRTF(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_RTSTATUS_FLRTF_SHIFT)) & CAAM_RTSTATUS_FLRTF_MASK)

#define CAAM_RTSTATUS_FPTF_MASK                  (0x4000U)
#define CAAM_RTSTATUS_FPTF_SHIFT                 (14U)
#define CAAM_RTSTATUS_FPTF(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_RTSTATUS_FPTF_SHIFT)) & CAAM_RTSTATUS_FPTF_MASK)

#define CAAM_RTSTATUS_FMBTF_MASK                 (0x8000U)
#define CAAM_RTSTATUS_FMBTF_SHIFT                (15U)
#define CAAM_RTSTATUS_FMBTF(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_RTSTATUS_FMBTF_SHIFT)) & CAAM_RTSTATUS_FMBTF_MASK)

#define CAAM_RTSTATUS_RETRY_COUNT_MASK           (0xF0000U)
#define CAAM_RTSTATUS_RETRY_COUNT_SHIFT          (16U)
#define CAAM_RTSTATUS_RETRY_COUNT(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_RTSTATUS_RETRY_COUNT_SHIFT)) & CAAM_RTSTATUS_RETRY_COUNT_MASK)
/*! @} */

/*! @name RTENT - RNG TRNG Entropy Read Register */
/*! @{ */

#define CAAM_RTENT_ENT_MASK                      (0xFFFFFFFFU)
#define CAAM_RTENT_ENT_SHIFT                     (0U)
#define CAAM_RTENT_ENT(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_RTENT_ENT_SHIFT)) & CAAM_RTENT_ENT_MASK)
/*! @} */

/* The count of CAAM_RTENT */
#define CAAM_RTENT_COUNT                         (16U)

/*! @name RTPKRCNT10 - RNG TRNG Statistical Check Poker Count 1 and 0 Register */
/*! @{ */

#define CAAM_RTPKRCNT10_PKR_0_CNT_MASK           (0xFFFFU)
#define CAAM_RTPKRCNT10_PKR_0_CNT_SHIFT          (0U)
#define CAAM_RTPKRCNT10_PKR_0_CNT(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_RTPKRCNT10_PKR_0_CNT_SHIFT)) & CAAM_RTPKRCNT10_PKR_0_CNT_MASK)

#define CAAM_RTPKRCNT10_PKR_1_CNT_MASK           (0xFFFF0000U)
#define CAAM_RTPKRCNT10_PKR_1_CNT_SHIFT          (16U)
#define CAAM_RTPKRCNT10_PKR_1_CNT(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_RTPKRCNT10_PKR_1_CNT_SHIFT)) & CAAM_RTPKRCNT10_PKR_1_CNT_MASK)
/*! @} */

/*! @name RTPKRCNT32 - RNG TRNG Statistical Check Poker Count 3 and 2 Register */
/*! @{ */

#define CAAM_RTPKRCNT32_PKR_2_CNT_MASK           (0xFFFFU)
#define CAAM_RTPKRCNT32_PKR_2_CNT_SHIFT          (0U)
#define CAAM_RTPKRCNT32_PKR_2_CNT(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_RTPKRCNT32_PKR_2_CNT_SHIFT)) & CAAM_RTPKRCNT32_PKR_2_CNT_MASK)

#define CAAM_RTPKRCNT32_PKR_3_CNT_MASK           (0xFFFF0000U)
#define CAAM_RTPKRCNT32_PKR_3_CNT_SHIFT          (16U)
#define CAAM_RTPKRCNT32_PKR_3_CNT(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_RTPKRCNT32_PKR_3_CNT_SHIFT)) & CAAM_RTPKRCNT32_PKR_3_CNT_MASK)
/*! @} */

/*! @name RTPKRCNT54 - RNG TRNG Statistical Check Poker Count 5 and 4 Register */
/*! @{ */

#define CAAM_RTPKRCNT54_PKR_4_CNT_MASK           (0xFFFFU)
#define CAAM_RTPKRCNT54_PKR_4_CNT_SHIFT          (0U)
#define CAAM_RTPKRCNT54_PKR_4_CNT(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_RTPKRCNT54_PKR_4_CNT_SHIFT)) & CAAM_RTPKRCNT54_PKR_4_CNT_MASK)

#define CAAM_RTPKRCNT54_PKR_5_CNT_MASK           (0xFFFF0000U)
#define CAAM_RTPKRCNT54_PKR_5_CNT_SHIFT          (16U)
#define CAAM_RTPKRCNT54_PKR_5_CNT(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_RTPKRCNT54_PKR_5_CNT_SHIFT)) & CAAM_RTPKRCNT54_PKR_5_CNT_MASK)
/*! @} */

/*! @name RTPKRCNT76 - RNG TRNG Statistical Check Poker Count 7 and 6 Register */
/*! @{ */

#define CAAM_RTPKRCNT76_PKR_6_CNT_MASK           (0xFFFFU)
#define CAAM_RTPKRCNT76_PKR_6_CNT_SHIFT          (0U)
#define CAAM_RTPKRCNT76_PKR_6_CNT(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_RTPKRCNT76_PKR_6_CNT_SHIFT)) & CAAM_RTPKRCNT76_PKR_6_CNT_MASK)

#define CAAM_RTPKRCNT76_PKR_7_CNT_MASK           (0xFFFF0000U)
#define CAAM_RTPKRCNT76_PKR_7_CNT_SHIFT          (16U)
#define CAAM_RTPKRCNT76_PKR_7_CNT(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_RTPKRCNT76_PKR_7_CNT_SHIFT)) & CAAM_RTPKRCNT76_PKR_7_CNT_MASK)
/*! @} */

/*! @name RTPKRCNT98 - RNG TRNG Statistical Check Poker Count 9 and 8 Register */
/*! @{ */

#define CAAM_RTPKRCNT98_PKR_8_CNT_MASK           (0xFFFFU)
#define CAAM_RTPKRCNT98_PKR_8_CNT_SHIFT          (0U)
#define CAAM_RTPKRCNT98_PKR_8_CNT(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_RTPKRCNT98_PKR_8_CNT_SHIFT)) & CAAM_RTPKRCNT98_PKR_8_CNT_MASK)

#define CAAM_RTPKRCNT98_PKR_9_CNT_MASK           (0xFFFF0000U)
#define CAAM_RTPKRCNT98_PKR_9_CNT_SHIFT          (16U)
#define CAAM_RTPKRCNT98_PKR_9_CNT(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_RTPKRCNT98_PKR_9_CNT_SHIFT)) & CAAM_RTPKRCNT98_PKR_9_CNT_MASK)
/*! @} */

/*! @name RTPKRCNTBA - RNG TRNG Statistical Check Poker Count B and A Register */
/*! @{ */

#define CAAM_RTPKRCNTBA_PKR_A_CNT_MASK           (0xFFFFU)
#define CAAM_RTPKRCNTBA_PKR_A_CNT_SHIFT          (0U)
#define CAAM_RTPKRCNTBA_PKR_A_CNT(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_RTPKRCNTBA_PKR_A_CNT_SHIFT)) & CAAM_RTPKRCNTBA_PKR_A_CNT_MASK)

#define CAAM_RTPKRCNTBA_PKR_B_CNT_MASK           (0xFFFF0000U)
#define CAAM_RTPKRCNTBA_PKR_B_CNT_SHIFT          (16U)
#define CAAM_RTPKRCNTBA_PKR_B_CNT(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_RTPKRCNTBA_PKR_B_CNT_SHIFT)) & CAAM_RTPKRCNTBA_PKR_B_CNT_MASK)
/*! @} */

/*! @name RTPKRCNTDC - RNG TRNG Statistical Check Poker Count D and C Register */
/*! @{ */

#define CAAM_RTPKRCNTDC_PKR_C_CNT_MASK           (0xFFFFU)
#define CAAM_RTPKRCNTDC_PKR_C_CNT_SHIFT          (0U)
#define CAAM_RTPKRCNTDC_PKR_C_CNT(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_RTPKRCNTDC_PKR_C_CNT_SHIFT)) & CAAM_RTPKRCNTDC_PKR_C_CNT_MASK)

#define CAAM_RTPKRCNTDC_PKR_D_CNT_MASK           (0xFFFF0000U)
#define CAAM_RTPKRCNTDC_PKR_D_CNT_SHIFT          (16U)
#define CAAM_RTPKRCNTDC_PKR_D_CNT(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_RTPKRCNTDC_PKR_D_CNT_SHIFT)) & CAAM_RTPKRCNTDC_PKR_D_CNT_MASK)
/*! @} */

/*! @name RTPKRCNTFE - RNG TRNG Statistical Check Poker Count F and E Register */
/*! @{ */

#define CAAM_RTPKRCNTFE_PKR_E_CNT_MASK           (0xFFFFU)
#define CAAM_RTPKRCNTFE_PKR_E_CNT_SHIFT          (0U)
#define CAAM_RTPKRCNTFE_PKR_E_CNT(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_RTPKRCNTFE_PKR_E_CNT_SHIFT)) & CAAM_RTPKRCNTFE_PKR_E_CNT_MASK)

#define CAAM_RTPKRCNTFE_PKR_F_CNT_MASK           (0xFFFF0000U)
#define CAAM_RTPKRCNTFE_PKR_F_CNT_SHIFT          (16U)
#define CAAM_RTPKRCNTFE_PKR_F_CNT(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_RTPKRCNTFE_PKR_F_CNT_SHIFT)) & CAAM_RTPKRCNTFE_PKR_F_CNT_MASK)
/*! @} */

/*! @name RDSTA - RNG DRNG Status Register */
/*! @{ */

#define CAAM_RDSTA_IF0_MASK                      (0x1U)
#define CAAM_RDSTA_IF0_SHIFT                     (0U)
#define CAAM_RDSTA_IF0(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_RDSTA_IF0_SHIFT)) & CAAM_RDSTA_IF0_MASK)

#define CAAM_RDSTA_IF1_MASK                      (0x2U)
#define CAAM_RDSTA_IF1_SHIFT                     (1U)
#define CAAM_RDSTA_IF1(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_RDSTA_IF1_SHIFT)) & CAAM_RDSTA_IF1_MASK)

#define CAAM_RDSTA_PR0_MASK                      (0x10U)
#define CAAM_RDSTA_PR0_SHIFT                     (4U)
#define CAAM_RDSTA_PR0(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_RDSTA_PR0_SHIFT)) & CAAM_RDSTA_PR0_MASK)

#define CAAM_RDSTA_PR1_MASK                      (0x20U)
#define CAAM_RDSTA_PR1_SHIFT                     (5U)
#define CAAM_RDSTA_PR1(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_RDSTA_PR1_SHIFT)) & CAAM_RDSTA_PR1_MASK)

#define CAAM_RDSTA_TF0_MASK                      (0x100U)
#define CAAM_RDSTA_TF0_SHIFT                     (8U)
#define CAAM_RDSTA_TF0(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_RDSTA_TF0_SHIFT)) & CAAM_RDSTA_TF0_MASK)

#define CAAM_RDSTA_TF1_MASK                      (0x200U)
#define CAAM_RDSTA_TF1_SHIFT                     (9U)
#define CAAM_RDSTA_TF1(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_RDSTA_TF1_SHIFT)) & CAAM_RDSTA_TF1_MASK)

#define CAAM_RDSTA_ERRCODE_MASK                  (0xF0000U)
#define CAAM_RDSTA_ERRCODE_SHIFT                 (16U)
#define CAAM_RDSTA_ERRCODE(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_RDSTA_ERRCODE_SHIFT)) & CAAM_RDSTA_ERRCODE_MASK)

#define CAAM_RDSTA_CE_MASK                       (0x100000U)
#define CAAM_RDSTA_CE_SHIFT                      (20U)
#define CAAM_RDSTA_CE(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_RDSTA_CE_SHIFT)) & CAAM_RDSTA_CE_MASK)

#define CAAM_RDSTA_SKVN_MASK                     (0x40000000U)
#define CAAM_RDSTA_SKVN_SHIFT                    (30U)
#define CAAM_RDSTA_SKVN(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_RDSTA_SKVN_SHIFT)) & CAAM_RDSTA_SKVN_MASK)

#define CAAM_RDSTA_SKVT_MASK                     (0x80000000U)
#define CAAM_RDSTA_SKVT_SHIFT                    (31U)
#define CAAM_RDSTA_SKVT(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_RDSTA_SKVT_SHIFT)) & CAAM_RDSTA_SKVT_MASK)
/*! @} */

/*! @name RDINT0 - RNG DRNG State Handle 0 Reseed Interval Register */
/*! @{ */

#define CAAM_RDINT0_RESINT0_MASK                 (0xFFFFFFFFU)
#define CAAM_RDINT0_RESINT0_SHIFT                (0U)
#define CAAM_RDINT0_RESINT0(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_RDINT0_RESINT0_SHIFT)) & CAAM_RDINT0_RESINT0_MASK)
/*! @} */

/*! @name RDINT1 - RNG DRNG State Handle 1 Reseed Interval Register */
/*! @{ */

#define CAAM_RDINT1_RESINT1_MASK                 (0xFFFFFFFFU)
#define CAAM_RDINT1_RESINT1_SHIFT                (0U)
#define CAAM_RDINT1_RESINT1(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_RDINT1_RESINT1_SHIFT)) & CAAM_RDINT1_RESINT1_MASK)
/*! @} */

/*! @name RDHCNTL - RNG DRNG Hash Control Register */
/*! @{ */

#define CAAM_RDHCNTL_HD_MASK                     (0x1U)
#define CAAM_RDHCNTL_HD_SHIFT                    (0U)
#define CAAM_RDHCNTL_HD(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_RDHCNTL_HD_SHIFT)) & CAAM_RDHCNTL_HD_MASK)

#define CAAM_RDHCNTL_HB_MASK                     (0x2U)
#define CAAM_RDHCNTL_HB_SHIFT                    (1U)
#define CAAM_RDHCNTL_HB(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_RDHCNTL_HB_SHIFT)) & CAAM_RDHCNTL_HB_MASK)

#define CAAM_RDHCNTL_HI_MASK                     (0x4U)
#define CAAM_RDHCNTL_HI_SHIFT                    (2U)
#define CAAM_RDHCNTL_HI(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_RDHCNTL_HI_SHIFT)) & CAAM_RDHCNTL_HI_MASK)

#define CAAM_RDHCNTL_HTM_MASK                    (0x8U)
#define CAAM_RDHCNTL_HTM_SHIFT                   (3U)
#define CAAM_RDHCNTL_HTM(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_RDHCNTL_HTM_SHIFT)) & CAAM_RDHCNTL_HTM_MASK)

#define CAAM_RDHCNTL_HTC_MASK                    (0x10U)
#define CAAM_RDHCNTL_HTC_SHIFT                   (4U)
#define CAAM_RDHCNTL_HTC(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_RDHCNTL_HTC_SHIFT)) & CAAM_RDHCNTL_HTC_MASK)
/*! @} */

/*! @name RDHDIG - RNG DRNG Hash Digest Register */
/*! @{ */

#define CAAM_RDHDIG_HASHMD_MASK                  (0xFFFFFFFFU)
#define CAAM_RDHDIG_HASHMD_SHIFT                 (0U)
#define CAAM_RDHDIG_HASHMD(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_RDHDIG_HASHMD_SHIFT)) & CAAM_RDHDIG_HASHMD_MASK)
/*! @} */

/*! @name RDHBUF - RNG DRNG Hash Buffer Register */
/*! @{ */

#define CAAM_RDHBUF_HASHBUF_MASK                 (0xFFFFFFFFU)
#define CAAM_RDHBUF_HASHBUF_SHIFT                (0U)
#define CAAM_RDHBUF_HASHBUF(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_RDHBUF_HASHBUF_SHIFT)) & CAAM_RDHBUF_HASHBUF_MASK)
/*! @} */

/*! @name PX_SDID_PG0 - Partition 0 SDID register..Partition 15 SDID register */
/*! @{ */

#define CAAM_PX_SDID_PG0_SDID_MASK               (0xFFFFU)
#define CAAM_PX_SDID_PG0_SDID_SHIFT              (0U)
#define CAAM_PX_SDID_PG0_SDID(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SDID_PG0_SDID_SHIFT)) & CAAM_PX_SDID_PG0_SDID_MASK)
/*! @} */

/* The count of CAAM_PX_SDID_PG0 */
#define CAAM_PX_SDID_PG0_COUNT                   (16U)

/*! @name PX_SMAPR_PG0 - Secure Memory Access Permissions register */
/*! @{ */

#define CAAM_PX_SMAPR_PG0_G1_READ_MASK           (0x1U)
#define CAAM_PX_SMAPR_PG0_G1_READ_SHIFT          (0U)
/*! G1_READ
 *  0b0..Instruction fetches and reads are prohibited (except that Trusted Descriptor reads (if G1_TDO=1) and
 *       key-reads are always allowed, and exporting Secure Memory Blobs is allowed if G1_SMBLOB=1 or if done by a
 *       Trusted Descriptor and G1_TDO=1).
 *  0b1..Instruction fetches and reads are allowed (but exporting a Secure Memory Blob is prohibited if
 *       G1_SMBLOB=0 and the descriptor is not a Trusted Descriptor or if G1_TDO=0).
 */
#define CAAM_PX_SMAPR_PG0_G1_READ(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_PG0_G1_READ_SHIFT)) & CAAM_PX_SMAPR_PG0_G1_READ_MASK)

#define CAAM_PX_SMAPR_PG0_G1_WRITE_MASK          (0x2U)
#define CAAM_PX_SMAPR_PG0_G1_WRITE_SHIFT         (1U)
/*! G1_WRITE
 *  0b0..Writes are prohibited (except that Trusted Descriptor writes are allowed, and importing Secure Memory
 *       Blobs is allowed if G1_SMBLOB=1 or if done by a Trusted Descriptor and G1_TDO=1).
 *  0b1..Writes are allowed (but importing a Secure Memory Blob is prohibited if G1_SMBLOB=0 and the descriptor is
 *       not a Trusted Descriptor or if G1_TDO=0).
 */
#define CAAM_PX_SMAPR_PG0_G1_WRITE(x)            (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_PG0_G1_WRITE_SHIFT)) & CAAM_PX_SMAPR_PG0_G1_WRITE_MASK)

#define CAAM_PX_SMAPR_PG0_G1_TDO_MASK            (0x4U)
#define CAAM_PX_SMAPR_PG0_G1_TDO_SHIFT           (2U)
/*! G1_TDO
 *  0b0..Trusted Descriptors have the same access privileges as Job Descriptors
 *  0b1..Trusted Descriptors are allowed to override the other access permissions, i.e. they can export blobs from
 *       or import blobs to the partition and read from and write to the partition regardless of the G1_SMBLOB,
 *       G1_WRITE and G1_READ settings.
 */
#define CAAM_PX_SMAPR_PG0_G1_TDO(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_PG0_G1_TDO_SHIFT)) & CAAM_PX_SMAPR_PG0_G1_TDO_MASK)

#define CAAM_PX_SMAPR_PG0_G1_SMBLOB_MASK         (0x8U)
#define CAAM_PX_SMAPR_PG0_G1_SMBLOB_SHIFT        (3U)
/*! G1_SMBLOB
 *  0b0..Exporting or importing Secure Memory Blobs is prohibited, unless done via a Trusted Descriptor and G1_TDO=1.
 *  0b1..Exporting or importing Secure Memory Blobs is allowed, regardless of the G1_READ and G1_WRITE settings.
 */
#define CAAM_PX_SMAPR_PG0_G1_SMBLOB(x)           (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_PG0_G1_SMBLOB_SHIFT)) & CAAM_PX_SMAPR_PG0_G1_SMBLOB_MASK)

#define CAAM_PX_SMAPR_PG0_G2_READ_MASK           (0x10U)
#define CAAM_PX_SMAPR_PG0_G2_READ_SHIFT          (4U)
/*! G2_READ
 *  0b0..Instruction fetches and reads are prohibited (except that Trusted Descriptor reads (if G2_TDO=1) and
 *       key-reads are always allowed, and exporting Secure Memory Blobs is allowed if G2_SMBLOB=1 or if done by a
 *       Trusted Descriptor and G2_TDO=1).
 *  0b1..Instruction fetches and reads are allowed (but exporting a Secure Memory Blob is prohibited if
 *       G2_SMBLOB=0 and the descriptor is not a Trusted Descriptor or if G2_TDO=0).
 */
#define CAAM_PX_SMAPR_PG0_G2_READ(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_PG0_G2_READ_SHIFT)) & CAAM_PX_SMAPR_PG0_G2_READ_MASK)

#define CAAM_PX_SMAPR_PG0_G2_WRITE_MASK          (0x20U)
#define CAAM_PX_SMAPR_PG0_G2_WRITE_SHIFT         (5U)
/*! G2_WRITE
 *  0b0..Writes are prohibited (except that Trusted Descriptor writes are allowed, and importing Secure Memory
 *       Blobs is allowed if G2_SMBLOB=1 or if done by a Trusted Descriptor and G2_TDO=1).
 *  0b1..Writes are allowed (but importing a Secure Memory Blob is prohibited if G2_SMBLOB=0 and the descriptor is
 *       not a Trusted Descriptor or if G2_TDO=0).
 */
#define CAAM_PX_SMAPR_PG0_G2_WRITE(x)            (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_PG0_G2_WRITE_SHIFT)) & CAAM_PX_SMAPR_PG0_G2_WRITE_MASK)

#define CAAM_PX_SMAPR_PG0_G2_TDO_MASK            (0x40U)
#define CAAM_PX_SMAPR_PG0_G2_TDO_SHIFT           (6U)
/*! G2_TDO
 *  0b0..Trusted Descriptors have the same access privileges as Job Descriptors
 *  0b1..Trusted Descriptors are allowed to override the other access permissions, i.e. they can export blobs from
 *       or import blobs to the partition and read from and write to the partition regardless of the G2_SMBLOB,
 *       G2_WRITE and G2_READ settings.
 */
#define CAAM_PX_SMAPR_PG0_G2_TDO(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_PG0_G2_TDO_SHIFT)) & CAAM_PX_SMAPR_PG0_G2_TDO_MASK)

#define CAAM_PX_SMAPR_PG0_G2_SMBLOB_MASK         (0x80U)
#define CAAM_PX_SMAPR_PG0_G2_SMBLOB_SHIFT        (7U)
/*! G2_SMBLOB
 *  0b0..Exporting or importing Secure Memory Blobs is prohibited, unless done via a Trusted Descriptor and G2_TDO=1.
 *  0b1..Exporting or importing Secure Memory Blobs is allowed, regardless of the G2_READ and G2_WRITE settings.
 */
#define CAAM_PX_SMAPR_PG0_G2_SMBLOB(x)           (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_PG0_G2_SMBLOB_SHIFT)) & CAAM_PX_SMAPR_PG0_G2_SMBLOB_MASK)

#define CAAM_PX_SMAPR_PG0_SMAG_LCK_MASK          (0x1000U)
#define CAAM_PX_SMAPR_PG0_SMAG_LCK_SHIFT         (12U)
/*! SMAG_LCK
 *  0b0..The SMAG2JR register and SMAG1JR register are unlocked. The partition owner can change any writable bits of these registers.
 *  0b1..The SMAG2JR register and SMAG1JR register are locked. The SMAG2JR and SMAG1JR registers cannot be changed
 *       until the partition is de-allocated or a POR occurs.
 */
#define CAAM_PX_SMAPR_PG0_SMAG_LCK(x)            (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_PG0_SMAG_LCK_SHIFT)) & CAAM_PX_SMAPR_PG0_SMAG_LCK_MASK)

#define CAAM_PX_SMAPR_PG0_SMAP_LCK_MASK          (0x2000U)
#define CAAM_PX_SMAPR_PG0_SMAP_LCK_SHIFT         (13U)
/*! SMAP_LCK
 *  0b0..The SMAP register is unlocked. The partition owner can change any writable bits of the SMAP register.
 *  0b1..The SMAP register is locked. The SMAP_LCK, CSP and PSP bits and G1 and G2 permission bits of the SMAP
 *       register cannot be changed until the partition is de-allocated or a POR occurs. The PARTITION_KMOD value can
 *       still be changed. The SMAG_LCK bit can be changed to a 1, but cannot be changed to a 0.
 */
#define CAAM_PX_SMAPR_PG0_SMAP_LCK(x)            (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_PG0_SMAP_LCK_SHIFT)) & CAAM_PX_SMAPR_PG0_SMAP_LCK_MASK)

#define CAAM_PX_SMAPR_PG0_PSP_MASK               (0x4000U)
#define CAAM_PX_SMAPR_PG0_PSP_SHIFT              (14U)
/*! PSP
 *  0b0..The partition and any of the pages allocated to the partition can be de-allocated.
 *  0b1..The partition cannot be de-allocated and the pages allocated to the partition cannot be de-allocated.
 */
#define CAAM_PX_SMAPR_PG0_PSP(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_PG0_PSP_SHIFT)) & CAAM_PX_SMAPR_PG0_PSP_MASK)

#define CAAM_PX_SMAPR_PG0_CSP_MASK               (0x8000U)
#define CAAM_PX_SMAPR_PG0_CSP_SHIFT              (15U)
/*! CSP
 *  0b0..The pages allocated to the partition will not be zeroized when they are de-allocated or the partition is
 *       released or a security alarm occurs.
 *  0b1..The pages allocated to the partition will be zeroized when they are individually de-allocated or the
 *       partition is released or a security alarm occurs.
 */
#define CAAM_PX_SMAPR_PG0_CSP(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_PG0_CSP_SHIFT)) & CAAM_PX_SMAPR_PG0_CSP_MASK)

#define CAAM_PX_SMAPR_PG0_PARTITION_KMOD_MASK    (0xFFFF0000U)
#define CAAM_PX_SMAPR_PG0_PARTITION_KMOD_SHIFT   (16U)
#define CAAM_PX_SMAPR_PG0_PARTITION_KMOD(x)      (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_PG0_PARTITION_KMOD_SHIFT)) & CAAM_PX_SMAPR_PG0_PARTITION_KMOD_MASK)
/*! @} */

/* The count of CAAM_PX_SMAPR_PG0 */
#define CAAM_PX_SMAPR_PG0_COUNT                  (16U)

/*! @name PX_SMAG2_PG0 - Secure Memory Access Group Registers */
/*! @{ */

#define CAAM_PX_SMAG2_PG0_Gx_ID00_MASK           (0x1U)
#define CAAM_PX_SMAG2_PG0_Gx_ID00_SHIFT          (0U)
#define CAAM_PX_SMAG2_PG0_Gx_ID00(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID00_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID00_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID01_MASK           (0x2U)
#define CAAM_PX_SMAG2_PG0_Gx_ID01_SHIFT          (1U)
#define CAAM_PX_SMAG2_PG0_Gx_ID01(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID01_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID01_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID02_MASK           (0x4U)
#define CAAM_PX_SMAG2_PG0_Gx_ID02_SHIFT          (2U)
#define CAAM_PX_SMAG2_PG0_Gx_ID02(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID02_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID02_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID03_MASK           (0x8U)
#define CAAM_PX_SMAG2_PG0_Gx_ID03_SHIFT          (3U)
#define CAAM_PX_SMAG2_PG0_Gx_ID03(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID03_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID03_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID04_MASK           (0x10U)
#define CAAM_PX_SMAG2_PG0_Gx_ID04_SHIFT          (4U)
#define CAAM_PX_SMAG2_PG0_Gx_ID04(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID04_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID04_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID05_MASK           (0x20U)
#define CAAM_PX_SMAG2_PG0_Gx_ID05_SHIFT          (5U)
#define CAAM_PX_SMAG2_PG0_Gx_ID05(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID05_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID05_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID06_MASK           (0x40U)
#define CAAM_PX_SMAG2_PG0_Gx_ID06_SHIFT          (6U)
#define CAAM_PX_SMAG2_PG0_Gx_ID06(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID06_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID06_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID07_MASK           (0x80U)
#define CAAM_PX_SMAG2_PG0_Gx_ID07_SHIFT          (7U)
#define CAAM_PX_SMAG2_PG0_Gx_ID07(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID07_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID07_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID08_MASK           (0x100U)
#define CAAM_PX_SMAG2_PG0_Gx_ID08_SHIFT          (8U)
#define CAAM_PX_SMAG2_PG0_Gx_ID08(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID08_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID08_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID09_MASK           (0x200U)
#define CAAM_PX_SMAG2_PG0_Gx_ID09_SHIFT          (9U)
#define CAAM_PX_SMAG2_PG0_Gx_ID09(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID09_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID09_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID10_MASK           (0x400U)
#define CAAM_PX_SMAG2_PG0_Gx_ID10_SHIFT          (10U)
#define CAAM_PX_SMAG2_PG0_Gx_ID10(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID10_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID10_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID11_MASK           (0x800U)
#define CAAM_PX_SMAG2_PG0_Gx_ID11_SHIFT          (11U)
#define CAAM_PX_SMAG2_PG0_Gx_ID11(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID11_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID11_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID12_MASK           (0x1000U)
#define CAAM_PX_SMAG2_PG0_Gx_ID12_SHIFT          (12U)
#define CAAM_PX_SMAG2_PG0_Gx_ID12(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID12_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID12_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID13_MASK           (0x2000U)
#define CAAM_PX_SMAG2_PG0_Gx_ID13_SHIFT          (13U)
#define CAAM_PX_SMAG2_PG0_Gx_ID13(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID13_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID13_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID14_MASK           (0x4000U)
#define CAAM_PX_SMAG2_PG0_Gx_ID14_SHIFT          (14U)
#define CAAM_PX_SMAG2_PG0_Gx_ID14(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID14_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID14_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID15_MASK           (0x8000U)
#define CAAM_PX_SMAG2_PG0_Gx_ID15_SHIFT          (15U)
#define CAAM_PX_SMAG2_PG0_Gx_ID15(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID15_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID15_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID16_MASK           (0x10000U)
#define CAAM_PX_SMAG2_PG0_Gx_ID16_SHIFT          (16U)
#define CAAM_PX_SMAG2_PG0_Gx_ID16(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID16_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID16_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID17_MASK           (0x20000U)
#define CAAM_PX_SMAG2_PG0_Gx_ID17_SHIFT          (17U)
#define CAAM_PX_SMAG2_PG0_Gx_ID17(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID17_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID17_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID18_MASK           (0x40000U)
#define CAAM_PX_SMAG2_PG0_Gx_ID18_SHIFT          (18U)
#define CAAM_PX_SMAG2_PG0_Gx_ID18(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID18_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID18_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID19_MASK           (0x80000U)
#define CAAM_PX_SMAG2_PG0_Gx_ID19_SHIFT          (19U)
#define CAAM_PX_SMAG2_PG0_Gx_ID19(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID19_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID19_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID20_MASK           (0x100000U)
#define CAAM_PX_SMAG2_PG0_Gx_ID20_SHIFT          (20U)
#define CAAM_PX_SMAG2_PG0_Gx_ID20(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID20_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID20_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID21_MASK           (0x200000U)
#define CAAM_PX_SMAG2_PG0_Gx_ID21_SHIFT          (21U)
#define CAAM_PX_SMAG2_PG0_Gx_ID21(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID21_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID21_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID22_MASK           (0x400000U)
#define CAAM_PX_SMAG2_PG0_Gx_ID22_SHIFT          (22U)
#define CAAM_PX_SMAG2_PG0_Gx_ID22(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID22_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID22_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID23_MASK           (0x800000U)
#define CAAM_PX_SMAG2_PG0_Gx_ID23_SHIFT          (23U)
#define CAAM_PX_SMAG2_PG0_Gx_ID23(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID23_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID23_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID24_MASK           (0x1000000U)
#define CAAM_PX_SMAG2_PG0_Gx_ID24_SHIFT          (24U)
#define CAAM_PX_SMAG2_PG0_Gx_ID24(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID24_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID24_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID25_MASK           (0x2000000U)
#define CAAM_PX_SMAG2_PG0_Gx_ID25_SHIFT          (25U)
#define CAAM_PX_SMAG2_PG0_Gx_ID25(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID25_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID25_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID26_MASK           (0x4000000U)
#define CAAM_PX_SMAG2_PG0_Gx_ID26_SHIFT          (26U)
#define CAAM_PX_SMAG2_PG0_Gx_ID26(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID26_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID26_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID27_MASK           (0x8000000U)
#define CAAM_PX_SMAG2_PG0_Gx_ID27_SHIFT          (27U)
#define CAAM_PX_SMAG2_PG0_Gx_ID27(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID27_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID27_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID28_MASK           (0x10000000U)
#define CAAM_PX_SMAG2_PG0_Gx_ID28_SHIFT          (28U)
#define CAAM_PX_SMAG2_PG0_Gx_ID28(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID28_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID28_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID29_MASK           (0x20000000U)
#define CAAM_PX_SMAG2_PG0_Gx_ID29_SHIFT          (29U)
#define CAAM_PX_SMAG2_PG0_Gx_ID29(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID29_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID29_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID30_MASK           (0x40000000U)
#define CAAM_PX_SMAG2_PG0_Gx_ID30_SHIFT          (30U)
#define CAAM_PX_SMAG2_PG0_Gx_ID30(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID30_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID30_MASK)

#define CAAM_PX_SMAG2_PG0_Gx_ID31_MASK           (0x80000000U)
#define CAAM_PX_SMAG2_PG0_Gx_ID31_SHIFT          (31U)
#define CAAM_PX_SMAG2_PG0_Gx_ID31(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_PG0_Gx_ID31_SHIFT)) & CAAM_PX_SMAG2_PG0_Gx_ID31_MASK)
/*! @} */

/* The count of CAAM_PX_SMAG2_PG0 */
#define CAAM_PX_SMAG2_PG0_COUNT                  (16U)

/*! @name PX_SMAG1_PG0 - Secure Memory Access Group Registers */
/*! @{ */

#define CAAM_PX_SMAG1_PG0_Gx_ID00_MASK           (0x1U)
#define CAAM_PX_SMAG1_PG0_Gx_ID00_SHIFT          (0U)
#define CAAM_PX_SMAG1_PG0_Gx_ID00(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID00_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID00_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID01_MASK           (0x2U)
#define CAAM_PX_SMAG1_PG0_Gx_ID01_SHIFT          (1U)
#define CAAM_PX_SMAG1_PG0_Gx_ID01(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID01_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID01_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID02_MASK           (0x4U)
#define CAAM_PX_SMAG1_PG0_Gx_ID02_SHIFT          (2U)
#define CAAM_PX_SMAG1_PG0_Gx_ID02(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID02_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID02_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID03_MASK           (0x8U)
#define CAAM_PX_SMAG1_PG0_Gx_ID03_SHIFT          (3U)
#define CAAM_PX_SMAG1_PG0_Gx_ID03(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID03_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID03_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID04_MASK           (0x10U)
#define CAAM_PX_SMAG1_PG0_Gx_ID04_SHIFT          (4U)
#define CAAM_PX_SMAG1_PG0_Gx_ID04(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID04_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID04_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID05_MASK           (0x20U)
#define CAAM_PX_SMAG1_PG0_Gx_ID05_SHIFT          (5U)
#define CAAM_PX_SMAG1_PG0_Gx_ID05(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID05_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID05_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID06_MASK           (0x40U)
#define CAAM_PX_SMAG1_PG0_Gx_ID06_SHIFT          (6U)
#define CAAM_PX_SMAG1_PG0_Gx_ID06(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID06_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID06_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID07_MASK           (0x80U)
#define CAAM_PX_SMAG1_PG0_Gx_ID07_SHIFT          (7U)
#define CAAM_PX_SMAG1_PG0_Gx_ID07(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID07_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID07_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID08_MASK           (0x100U)
#define CAAM_PX_SMAG1_PG0_Gx_ID08_SHIFT          (8U)
#define CAAM_PX_SMAG1_PG0_Gx_ID08(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID08_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID08_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID09_MASK           (0x200U)
#define CAAM_PX_SMAG1_PG0_Gx_ID09_SHIFT          (9U)
#define CAAM_PX_SMAG1_PG0_Gx_ID09(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID09_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID09_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID10_MASK           (0x400U)
#define CAAM_PX_SMAG1_PG0_Gx_ID10_SHIFT          (10U)
#define CAAM_PX_SMAG1_PG0_Gx_ID10(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID10_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID10_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID11_MASK           (0x800U)
#define CAAM_PX_SMAG1_PG0_Gx_ID11_SHIFT          (11U)
#define CAAM_PX_SMAG1_PG0_Gx_ID11(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID11_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID11_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID12_MASK           (0x1000U)
#define CAAM_PX_SMAG1_PG0_Gx_ID12_SHIFT          (12U)
#define CAAM_PX_SMAG1_PG0_Gx_ID12(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID12_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID12_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID13_MASK           (0x2000U)
#define CAAM_PX_SMAG1_PG0_Gx_ID13_SHIFT          (13U)
#define CAAM_PX_SMAG1_PG0_Gx_ID13(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID13_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID13_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID14_MASK           (0x4000U)
#define CAAM_PX_SMAG1_PG0_Gx_ID14_SHIFT          (14U)
#define CAAM_PX_SMAG1_PG0_Gx_ID14(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID14_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID14_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID15_MASK           (0x8000U)
#define CAAM_PX_SMAG1_PG0_Gx_ID15_SHIFT          (15U)
#define CAAM_PX_SMAG1_PG0_Gx_ID15(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID15_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID15_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID16_MASK           (0x10000U)
#define CAAM_PX_SMAG1_PG0_Gx_ID16_SHIFT          (16U)
#define CAAM_PX_SMAG1_PG0_Gx_ID16(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID16_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID16_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID17_MASK           (0x20000U)
#define CAAM_PX_SMAG1_PG0_Gx_ID17_SHIFT          (17U)
#define CAAM_PX_SMAG1_PG0_Gx_ID17(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID17_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID17_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID18_MASK           (0x40000U)
#define CAAM_PX_SMAG1_PG0_Gx_ID18_SHIFT          (18U)
#define CAAM_PX_SMAG1_PG0_Gx_ID18(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID18_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID18_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID19_MASK           (0x80000U)
#define CAAM_PX_SMAG1_PG0_Gx_ID19_SHIFT          (19U)
#define CAAM_PX_SMAG1_PG0_Gx_ID19(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID19_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID19_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID20_MASK           (0x100000U)
#define CAAM_PX_SMAG1_PG0_Gx_ID20_SHIFT          (20U)
#define CAAM_PX_SMAG1_PG0_Gx_ID20(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID20_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID20_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID21_MASK           (0x200000U)
#define CAAM_PX_SMAG1_PG0_Gx_ID21_SHIFT          (21U)
#define CAAM_PX_SMAG1_PG0_Gx_ID21(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID21_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID21_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID22_MASK           (0x400000U)
#define CAAM_PX_SMAG1_PG0_Gx_ID22_SHIFT          (22U)
#define CAAM_PX_SMAG1_PG0_Gx_ID22(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID22_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID22_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID23_MASK           (0x800000U)
#define CAAM_PX_SMAG1_PG0_Gx_ID23_SHIFT          (23U)
#define CAAM_PX_SMAG1_PG0_Gx_ID23(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID23_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID23_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID24_MASK           (0x1000000U)
#define CAAM_PX_SMAG1_PG0_Gx_ID24_SHIFT          (24U)
#define CAAM_PX_SMAG1_PG0_Gx_ID24(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID24_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID24_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID25_MASK           (0x2000000U)
#define CAAM_PX_SMAG1_PG0_Gx_ID25_SHIFT          (25U)
#define CAAM_PX_SMAG1_PG0_Gx_ID25(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID25_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID25_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID26_MASK           (0x4000000U)
#define CAAM_PX_SMAG1_PG0_Gx_ID26_SHIFT          (26U)
#define CAAM_PX_SMAG1_PG0_Gx_ID26(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID26_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID26_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID27_MASK           (0x8000000U)
#define CAAM_PX_SMAG1_PG0_Gx_ID27_SHIFT          (27U)
#define CAAM_PX_SMAG1_PG0_Gx_ID27(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID27_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID27_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID28_MASK           (0x10000000U)
#define CAAM_PX_SMAG1_PG0_Gx_ID28_SHIFT          (28U)
#define CAAM_PX_SMAG1_PG0_Gx_ID28(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID28_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID28_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID29_MASK           (0x20000000U)
#define CAAM_PX_SMAG1_PG0_Gx_ID29_SHIFT          (29U)
#define CAAM_PX_SMAG1_PG0_Gx_ID29(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID29_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID29_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID30_MASK           (0x40000000U)
#define CAAM_PX_SMAG1_PG0_Gx_ID30_SHIFT          (30U)
#define CAAM_PX_SMAG1_PG0_Gx_ID30(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID30_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID30_MASK)

#define CAAM_PX_SMAG1_PG0_Gx_ID31_MASK           (0x80000000U)
#define CAAM_PX_SMAG1_PG0_Gx_ID31_SHIFT          (31U)
#define CAAM_PX_SMAG1_PG0_Gx_ID31(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_PG0_Gx_ID31_SHIFT)) & CAAM_PX_SMAG1_PG0_Gx_ID31_MASK)
/*! @} */

/* The count of CAAM_PX_SMAG1_PG0 */
#define CAAM_PX_SMAG1_PG0_COUNT                  (16U)

/*! @name REIS - Recoverable Error Interrupt Status */
/*! @{ */

#define CAAM_REIS_CWDE_MASK                      (0x1U)
#define CAAM_REIS_CWDE_SHIFT                     (0U)
#define CAAM_REIS_CWDE(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_REIS_CWDE_SHIFT)) & CAAM_REIS_CWDE_MASK)

#define CAAM_REIS_RBAE_MASK                      (0x10000U)
#define CAAM_REIS_RBAE_SHIFT                     (16U)
#define CAAM_REIS_RBAE(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_REIS_RBAE_SHIFT)) & CAAM_REIS_RBAE_MASK)

#define CAAM_REIS_JBAE0_MASK                     (0x1000000U)
#define CAAM_REIS_JBAE0_SHIFT                    (24U)
#define CAAM_REIS_JBAE0(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_REIS_JBAE0_SHIFT)) & CAAM_REIS_JBAE0_MASK)

#define CAAM_REIS_JBAE1_MASK                     (0x2000000U)
#define CAAM_REIS_JBAE1_SHIFT                    (25U)
#define CAAM_REIS_JBAE1(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_REIS_JBAE1_SHIFT)) & CAAM_REIS_JBAE1_MASK)

#define CAAM_REIS_JBAE2_MASK                     (0x4000000U)
#define CAAM_REIS_JBAE2_SHIFT                    (26U)
#define CAAM_REIS_JBAE2(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_REIS_JBAE2_SHIFT)) & CAAM_REIS_JBAE2_MASK)

#define CAAM_REIS_JBAE3_MASK                     (0x8000000U)
#define CAAM_REIS_JBAE3_SHIFT                    (27U)
#define CAAM_REIS_JBAE3(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_REIS_JBAE3_SHIFT)) & CAAM_REIS_JBAE3_MASK)
/*! @} */

/*! @name REIE - Recoverable Error Interrupt Enable */
/*! @{ */

#define CAAM_REIE_CWDE_MASK                      (0x1U)
#define CAAM_REIE_CWDE_SHIFT                     (0U)
#define CAAM_REIE_CWDE(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_REIE_CWDE_SHIFT)) & CAAM_REIE_CWDE_MASK)

#define CAAM_REIE_RBAE_MASK                      (0x10000U)
#define CAAM_REIE_RBAE_SHIFT                     (16U)
#define CAAM_REIE_RBAE(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_REIE_RBAE_SHIFT)) & CAAM_REIE_RBAE_MASK)

#define CAAM_REIE_JBAE0_MASK                     (0x1000000U)
#define CAAM_REIE_JBAE0_SHIFT                    (24U)
#define CAAM_REIE_JBAE0(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_REIE_JBAE0_SHIFT)) & CAAM_REIE_JBAE0_MASK)

#define CAAM_REIE_JBAE1_MASK                     (0x2000000U)
#define CAAM_REIE_JBAE1_SHIFT                    (25U)
#define CAAM_REIE_JBAE1(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_REIE_JBAE1_SHIFT)) & CAAM_REIE_JBAE1_MASK)

#define CAAM_REIE_JBAE2_MASK                     (0x4000000U)
#define CAAM_REIE_JBAE2_SHIFT                    (26U)
#define CAAM_REIE_JBAE2(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_REIE_JBAE2_SHIFT)) & CAAM_REIE_JBAE2_MASK)

#define CAAM_REIE_JBAE3_MASK                     (0x8000000U)
#define CAAM_REIE_JBAE3_SHIFT                    (27U)
#define CAAM_REIE_JBAE3(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_REIE_JBAE3_SHIFT)) & CAAM_REIE_JBAE3_MASK)
/*! @} */

/*! @name REIF - Recoverable Error Interrupt Force */
/*! @{ */

#define CAAM_REIF_CWDE_MASK                      (0x1U)
#define CAAM_REIF_CWDE_SHIFT                     (0U)
#define CAAM_REIF_CWDE(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_REIF_CWDE_SHIFT)) & CAAM_REIF_CWDE_MASK)

#define CAAM_REIF_RBAE_MASK                      (0x10000U)
#define CAAM_REIF_RBAE_SHIFT                     (16U)
#define CAAM_REIF_RBAE(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_REIF_RBAE_SHIFT)) & CAAM_REIF_RBAE_MASK)

#define CAAM_REIF_JBAE0_MASK                     (0x1000000U)
#define CAAM_REIF_JBAE0_SHIFT                    (24U)
#define CAAM_REIF_JBAE0(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_REIF_JBAE0_SHIFT)) & CAAM_REIF_JBAE0_MASK)

#define CAAM_REIF_JBAE1_MASK                     (0x2000000U)
#define CAAM_REIF_JBAE1_SHIFT                    (25U)
#define CAAM_REIF_JBAE1(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_REIF_JBAE1_SHIFT)) & CAAM_REIF_JBAE1_MASK)

#define CAAM_REIF_JBAE2_MASK                     (0x4000000U)
#define CAAM_REIF_JBAE2_SHIFT                    (26U)
#define CAAM_REIF_JBAE2(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_REIF_JBAE2_SHIFT)) & CAAM_REIF_JBAE2_MASK)

#define CAAM_REIF_JBAE3_MASK                     (0x8000000U)
#define CAAM_REIF_JBAE3_SHIFT                    (27U)
#define CAAM_REIF_JBAE3(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_REIF_JBAE3_SHIFT)) & CAAM_REIF_JBAE3_MASK)
/*! @} */

/*! @name REIH - Recoverable Error Interrupt Halt */
/*! @{ */

#define CAAM_REIH_CWDE_MASK                      (0x1U)
#define CAAM_REIH_CWDE_SHIFT                     (0U)
/*! CWDE
 *  0b0..Don't halt CAAM if CAAM watchdog expired.
 *  0b1..Halt CAAM if CAAM watchdog expired..
 */
#define CAAM_REIH_CWDE(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_REIH_CWDE_SHIFT)) & CAAM_REIH_CWDE_MASK)

#define CAAM_REIH_RBAE_MASK                      (0x10000U)
#define CAAM_REIH_RBAE_SHIFT                     (16U)
/*! RBAE
 *  0b0..Don't halt CAAM if RTIC-initiated job execution caused bus access error.
 *  0b1..Halt CAAM if RTIC-initiated job execution caused bus access error.
 */
#define CAAM_REIH_RBAE(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_REIH_RBAE_SHIFT)) & CAAM_REIH_RBAE_MASK)

#define CAAM_REIH_JBAE0_MASK                     (0x1000000U)
#define CAAM_REIH_JBAE0_SHIFT                    (24U)
/*! JBAE0
 *  0b0..Don't halt CAAM if JR0-initiated job execution caused bus access error.
 *  0b1..Halt CAAM if JR0-initiated job execution caused bus access error.
 */
#define CAAM_REIH_JBAE0(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_REIH_JBAE0_SHIFT)) & CAAM_REIH_JBAE0_MASK)

#define CAAM_REIH_JBAE1_MASK                     (0x2000000U)
#define CAAM_REIH_JBAE1_SHIFT                    (25U)
/*! JBAE1
 *  0b0..Don't halt CAAM if JR1-initiated job execution caused bus access error.
 *  0b1..Halt CAAM if JR1-initiated job execution caused bus access error.
 */
#define CAAM_REIH_JBAE1(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_REIH_JBAE1_SHIFT)) & CAAM_REIH_JBAE1_MASK)

#define CAAM_REIH_JBAE2_MASK                     (0x4000000U)
#define CAAM_REIH_JBAE2_SHIFT                    (26U)
/*! JBAE2
 *  0b0..Don't halt CAAM if JR2-initiated job execution caused bus access error.
 *  0b1..Halt CAAM if JR2-initiated job execution caused bus access error.
 */
#define CAAM_REIH_JBAE2(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_REIH_JBAE2_SHIFT)) & CAAM_REIH_JBAE2_MASK)

#define CAAM_REIH_JBAE3_MASK                     (0x8000000U)
#define CAAM_REIH_JBAE3_SHIFT                    (27U)
/*! JBAE3
 *  0b0..Don't halt CAAM if JR3-initiated job execution caused bus access error.
 *  0b1..Halt CAAM if JR3-initiated job execution caused bus access error.
 */
#define CAAM_REIH_JBAE3(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_REIH_JBAE3_SHIFT)) & CAAM_REIH_JBAE3_MASK)
/*! @} */

/*! @name SMWPJRR - Secure Memory Write Protect Job Ring Register */
/*! @{ */

#define CAAM_SMWPJRR_SMR_WP_JRa_MASK             (0x1U)
#define CAAM_SMWPJRR_SMR_WP_JRa_SHIFT            (0U)
#define CAAM_SMWPJRR_SMR_WP_JRa(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_SMWPJRR_SMR_WP_JRa_SHIFT)) & CAAM_SMWPJRR_SMR_WP_JRa_MASK)
/*! @} */

/* The count of CAAM_SMWPJRR */
#define CAAM_SMWPJRR_COUNT                       (4U)

/*! @name SMCR_PG0 - Secure Memory Command Register */
/*! @{ */

#define CAAM_SMCR_PG0_CMD_MASK                   (0xFU)
#define CAAM_SMCR_PG0_CMD_SHIFT                  (0U)
#define CAAM_SMCR_PG0_CMD(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_SMCR_PG0_CMD_SHIFT)) & CAAM_SMCR_PG0_CMD_MASK)

#define CAAM_SMCR_PG0_PRTN_MASK                  (0xF00U)
#define CAAM_SMCR_PG0_PRTN_SHIFT                 (8U)
#define CAAM_SMCR_PG0_PRTN(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_SMCR_PG0_PRTN_SHIFT)) & CAAM_SMCR_PG0_PRTN_MASK)

#define CAAM_SMCR_PG0_PAGE_MASK                  (0xFFFF0000U)
#define CAAM_SMCR_PG0_PAGE_SHIFT                 (16U)
#define CAAM_SMCR_PG0_PAGE(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_SMCR_PG0_PAGE_SHIFT)) & CAAM_SMCR_PG0_PAGE_MASK)
/*! @} */

/*! @name SMCSR_PG0 - Secure Memory Command Status Register */
/*! @{ */

#define CAAM_SMCSR_PG0_PRTN_MASK                 (0xFU)
#define CAAM_SMCSR_PG0_PRTN_SHIFT                (0U)
#define CAAM_SMCSR_PG0_PRTN(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_SMCSR_PG0_PRTN_SHIFT)) & CAAM_SMCSR_PG0_PRTN_MASK)

#define CAAM_SMCSR_PG0_PO_MASK                   (0xC0U)
#define CAAM_SMCSR_PG0_PO_SHIFT                  (6U)
/*! PO
 *  0b00..Available; Unowned: The entity that issued the inquiry may allocate this page to a partition. No
 *        zeroization is needed since it has already been cleared, therefore no interrupt should be expected.
 *  0b01..Page does not exist in this version or is not initialized yet.
 *  0b10..Another entity owns the page. This page is unavailable to the issuer of the inquiry.
 *  0b11..Owned by the entity making the inquiry. The owner may de-allocate this page if its partition is not
 *        marked PSP. If the partition to which the page is allocated is designated as CSP, the page will be zeroized
 *        upon de-allocation.
 */
#define CAAM_SMCSR_PG0_PO(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_SMCSR_PG0_PO_SHIFT)) & CAAM_SMCSR_PG0_PO_MASK)

#define CAAM_SMCSR_PG0_AERR_MASK                 (0x3000U)
#define CAAM_SMCSR_PG0_AERR_SHIFT                (12U)
#define CAAM_SMCSR_PG0_AERR(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_SMCSR_PG0_AERR_SHIFT)) & CAAM_SMCSR_PG0_AERR_MASK)

#define CAAM_SMCSR_PG0_CERR_MASK                 (0xC000U)
#define CAAM_SMCSR_PG0_CERR_SHIFT                (14U)
/*! CERR
 *  0b00..No Error.
 *  0b01..Command has not yet completed.
 *  0b10..A security failure occurred.
 *  0b11..Command Overflow. Another command was issued by the same Job Ring owner before the owner's previous
 *        command completed. The additional command was ignored.
 */
#define CAAM_SMCSR_PG0_CERR(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_SMCSR_PG0_CERR_SHIFT)) & CAAM_SMCSR_PG0_CERR_MASK)

#define CAAM_SMCSR_PG0_PAGE_MASK                 (0xFFF0000U)
#define CAAM_SMCSR_PG0_PAGE_SHIFT                (16U)
#define CAAM_SMCSR_PG0_PAGE(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_SMCSR_PG0_PAGE_SHIFT)) & CAAM_SMCSR_PG0_PAGE_MASK)
/*! @} */

/*! @name CAAMVID_MS_TRAD - CAAM Version ID Register, most-significant half */
/*! @{ */

#define CAAM_CAAMVID_MS_TRAD_MIN_REV_MASK        (0xFFU)
#define CAAM_CAAMVID_MS_TRAD_MIN_REV_SHIFT       (0U)
#define CAAM_CAAMVID_MS_TRAD_MIN_REV(x)          (((uint32_t)(((uint32_t)(x)) << CAAM_CAAMVID_MS_TRAD_MIN_REV_SHIFT)) & CAAM_CAAMVID_MS_TRAD_MIN_REV_MASK)

#define CAAM_CAAMVID_MS_TRAD_MAJ_REV_MASK        (0xFF00U)
#define CAAM_CAAMVID_MS_TRAD_MAJ_REV_SHIFT       (8U)
#define CAAM_CAAMVID_MS_TRAD_MAJ_REV(x)          (((uint32_t)(((uint32_t)(x)) << CAAM_CAAMVID_MS_TRAD_MAJ_REV_SHIFT)) & CAAM_CAAMVID_MS_TRAD_MAJ_REV_MASK)

#define CAAM_CAAMVID_MS_TRAD_IP_ID_MASK          (0xFFFF0000U)
#define CAAM_CAAMVID_MS_TRAD_IP_ID_SHIFT         (16U)
#define CAAM_CAAMVID_MS_TRAD_IP_ID(x)            (((uint32_t)(((uint32_t)(x)) << CAAM_CAAMVID_MS_TRAD_IP_ID_SHIFT)) & CAAM_CAAMVID_MS_TRAD_IP_ID_MASK)
/*! @} */

/*! @name CAAMVID_LS_TRAD - CAAM Version ID Register, least-significant half */
/*! @{ */

#define CAAM_CAAMVID_LS_TRAD_CONFIG_OPT_MASK     (0xFFU)
#define CAAM_CAAMVID_LS_TRAD_CONFIG_OPT_SHIFT    (0U)
#define CAAM_CAAMVID_LS_TRAD_CONFIG_OPT(x)       (((uint32_t)(((uint32_t)(x)) << CAAM_CAAMVID_LS_TRAD_CONFIG_OPT_SHIFT)) & CAAM_CAAMVID_LS_TRAD_CONFIG_OPT_MASK)

#define CAAM_CAAMVID_LS_TRAD_ECO_REV_MASK        (0xFF00U)
#define CAAM_CAAMVID_LS_TRAD_ECO_REV_SHIFT       (8U)
#define CAAM_CAAMVID_LS_TRAD_ECO_REV(x)          (((uint32_t)(((uint32_t)(x)) << CAAM_CAAMVID_LS_TRAD_ECO_REV_SHIFT)) & CAAM_CAAMVID_LS_TRAD_ECO_REV_MASK)

#define CAAM_CAAMVID_LS_TRAD_INTG_OPT_MASK       (0xFF0000U)
#define CAAM_CAAMVID_LS_TRAD_INTG_OPT_SHIFT      (16U)
#define CAAM_CAAMVID_LS_TRAD_INTG_OPT(x)         (((uint32_t)(((uint32_t)(x)) << CAAM_CAAMVID_LS_TRAD_INTG_OPT_SHIFT)) & CAAM_CAAMVID_LS_TRAD_INTG_OPT_MASK)

#define CAAM_CAAMVID_LS_TRAD_COMPILE_OPT_MASK    (0xFF000000U)
#define CAAM_CAAMVID_LS_TRAD_COMPILE_OPT_SHIFT   (24U)
#define CAAM_CAAMVID_LS_TRAD_COMPILE_OPT(x)      (((uint32_t)(((uint32_t)(x)) << CAAM_CAAMVID_LS_TRAD_COMPILE_OPT_SHIFT)) & CAAM_CAAMVID_LS_TRAD_COMPILE_OPT_MASK)
/*! @} */

/*! @name HT_JD_ADDR - Holding Tank 0 Job Descriptor Address */
/*! @{ */

#define CAAM_HT_JD_ADDR_JD_ADDR_MASK             (0xFFFFFFFFFU)
#define CAAM_HT_JD_ADDR_JD_ADDR_SHIFT            (0U)
#define CAAM_HT_JD_ADDR_JD_ADDR(x)               (((uint64_t)(((uint64_t)(x)) << CAAM_HT_JD_ADDR_JD_ADDR_SHIFT)) & CAAM_HT_JD_ADDR_JD_ADDR_MASK)
/*! @} */

/* The count of CAAM_HT_JD_ADDR */
#define CAAM_HT_JD_ADDR_COUNT                    (1U)

/*! @name HT_SD_ADDR - Holding Tank 0 Shared Descriptor Address */
/*! @{ */

#define CAAM_HT_SD_ADDR_SD_ADDR_MASK             (0xFFFFFFFFFU)
#define CAAM_HT_SD_ADDR_SD_ADDR_SHIFT            (0U)
#define CAAM_HT_SD_ADDR_SD_ADDR(x)               (((uint64_t)(((uint64_t)(x)) << CAAM_HT_SD_ADDR_SD_ADDR_SHIFT)) & CAAM_HT_SD_ADDR_SD_ADDR_MASK)
/*! @} */

/* The count of CAAM_HT_SD_ADDR */
#define CAAM_HT_SD_ADDR_COUNT                    (1U)

/*! @name HT_JQ_CTRL_MS - Holding Tank 0 Job Queue Control, most-significant half */
/*! @{ */

#define CAAM_HT_JQ_CTRL_MS_ID_MASK               (0x7U)
#define CAAM_HT_JQ_CTRL_MS_ID_SHIFT              (0U)
#define CAAM_HT_JQ_CTRL_MS_ID(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_HT_JQ_CTRL_MS_ID_SHIFT)) & CAAM_HT_JQ_CTRL_MS_ID_MASK)

#define CAAM_HT_JQ_CTRL_MS_SRC_MASK              (0x700U)
#define CAAM_HT_JQ_CTRL_MS_SRC_SHIFT             (8U)
/*! SRC
 *  0b000..Job Ring 0
 *  0b001..Job Ring 1
 *  0b010..Job Ring 2
 *  0b011..Job Ring 3
 *  0b100..RTIC
 *  0b101..Reserved
 *  0b110..Reserved
 *  0b111..Reserved
 */
#define CAAM_HT_JQ_CTRL_MS_SRC(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_HT_JQ_CTRL_MS_SRC_SHIFT)) & CAAM_HT_JQ_CTRL_MS_SRC_MASK)

#define CAAM_HT_JQ_CTRL_MS_JDDS_MASK             (0x4000U)
#define CAAM_HT_JQ_CTRL_MS_JDDS_SHIFT            (14U)
/*! JDDS
 *  0b0..Non-SEQ DID
 *  0b1..SEQ DID
 */
#define CAAM_HT_JQ_CTRL_MS_JDDS(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_HT_JQ_CTRL_MS_JDDS_SHIFT)) & CAAM_HT_JQ_CTRL_MS_JDDS_MASK)

#define CAAM_HT_JQ_CTRL_MS_AMTD_MASK             (0x8000U)
#define CAAM_HT_JQ_CTRL_MS_AMTD_SHIFT            (15U)
#define CAAM_HT_JQ_CTRL_MS_AMTD(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_HT_JQ_CTRL_MS_AMTD_SHIFT)) & CAAM_HT_JQ_CTRL_MS_AMTD_MASK)

#define CAAM_HT_JQ_CTRL_MS_SOB_MASK              (0x10000U)
#define CAAM_HT_JQ_CTRL_MS_SOB_SHIFT             (16U)
#define CAAM_HT_JQ_CTRL_MS_SOB(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_HT_JQ_CTRL_MS_SOB_SHIFT)) & CAAM_HT_JQ_CTRL_MS_SOB_MASK)

#define CAAM_HT_JQ_CTRL_MS_HT_ERROR_MASK         (0x60000U)
#define CAAM_HT_JQ_CTRL_MS_HT_ERROR_SHIFT        (17U)
/*! HT_ERROR
 *  0b00..No error
 *  0b01..Job Descriptor or Shared Descriptor length error
 *  0b10..AXI_error while reading a Job Ring Shared Descriptor or the remainder of a Job Ring Job Descriptor
 *  0b11..reserved
 */
#define CAAM_HT_JQ_CTRL_MS_HT_ERROR(x)           (((uint32_t)(((uint32_t)(x)) << CAAM_HT_JQ_CTRL_MS_HT_ERROR_SHIFT)) & CAAM_HT_JQ_CTRL_MS_HT_ERROR_MASK)

#define CAAM_HT_JQ_CTRL_MS_DWORD_SWAP_MASK       (0x80000U)
#define CAAM_HT_JQ_CTRL_MS_DWORD_SWAP_SHIFT      (19U)
/*! DWORD_SWAP
 *  0b0..DWords are in the order most-significant word, least-significant word.
 *  0b1..DWords are in the order least-significant word, most-significant word.
 */
#define CAAM_HT_JQ_CTRL_MS_DWORD_SWAP(x)         (((uint32_t)(((uint32_t)(x)) << CAAM_HT_JQ_CTRL_MS_DWORD_SWAP_SHIFT)) & CAAM_HT_JQ_CTRL_MS_DWORD_SWAP_MASK)

#define CAAM_HT_JQ_CTRL_MS_SHR_FROM_MASK         (0x7C00000U)
#define CAAM_HT_JQ_CTRL_MS_SHR_FROM_SHIFT        (22U)
#define CAAM_HT_JQ_CTRL_MS_SHR_FROM(x)           (((uint32_t)(((uint32_t)(x)) << CAAM_HT_JQ_CTRL_MS_SHR_FROM_SHIFT)) & CAAM_HT_JQ_CTRL_MS_SHR_FROM_MASK)

#define CAAM_HT_JQ_CTRL_MS_ILE_MASK              (0x8000000U)
#define CAAM_HT_JQ_CTRL_MS_ILE_SHIFT             (27U)
/*! ILE
 *  0b0..No byte-swapping is performed for immediate data transferred to or from the Descriptor Buffer.
 *  0b1..Byte-swapping is performed for immediate data transferred to or from the Descriptor Buffer.
 */
#define CAAM_HT_JQ_CTRL_MS_ILE(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_HT_JQ_CTRL_MS_ILE_SHIFT)) & CAAM_HT_JQ_CTRL_MS_ILE_MASK)

#define CAAM_HT_JQ_CTRL_MS_FOUR_MASK             (0x10000000U)
#define CAAM_HT_JQ_CTRL_MS_FOUR_SHIFT            (28U)
#define CAAM_HT_JQ_CTRL_MS_FOUR(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_HT_JQ_CTRL_MS_FOUR_SHIFT)) & CAAM_HT_JQ_CTRL_MS_FOUR_MASK)

#define CAAM_HT_JQ_CTRL_MS_WHL_MASK              (0x20000000U)
#define CAAM_HT_JQ_CTRL_MS_WHL_SHIFT             (29U)
#define CAAM_HT_JQ_CTRL_MS_WHL(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_HT_JQ_CTRL_MS_WHL_SHIFT)) & CAAM_HT_JQ_CTRL_MS_WHL_MASK)
/*! @} */

/* The count of CAAM_HT_JQ_CTRL_MS */
#define CAAM_HT_JQ_CTRL_MS_COUNT                 (1U)

/*! @name HT_JQ_CTRL_LS - Holding Tank 0 Job Queue Control, least-significant half */
/*! @{ */

#define CAAM_HT_JQ_CTRL_LS_PRIM_DID_MASK         (0xFU)
#define CAAM_HT_JQ_CTRL_LS_PRIM_DID_SHIFT        (0U)
#define CAAM_HT_JQ_CTRL_LS_PRIM_DID(x)           (((uint32_t)(((uint32_t)(x)) << CAAM_HT_JQ_CTRL_LS_PRIM_DID_SHIFT)) & CAAM_HT_JQ_CTRL_LS_PRIM_DID_MASK)

#define CAAM_HT_JQ_CTRL_LS_PRIM_TZ_MASK          (0x10U)
#define CAAM_HT_JQ_CTRL_LS_PRIM_TZ_SHIFT         (4U)
/*! PRIM_TZ
 *  0b0..TrustZone NonSecureWorld
 *  0b1..TrustZone SecureWorld
 */
#define CAAM_HT_JQ_CTRL_LS_PRIM_TZ(x)            (((uint32_t)(((uint32_t)(x)) << CAAM_HT_JQ_CTRL_LS_PRIM_TZ_SHIFT)) & CAAM_HT_JQ_CTRL_LS_PRIM_TZ_MASK)

#define CAAM_HT_JQ_CTRL_LS_PRIM_ICID_MASK        (0xFFE0U)
#define CAAM_HT_JQ_CTRL_LS_PRIM_ICID_SHIFT       (5U)
#define CAAM_HT_JQ_CTRL_LS_PRIM_ICID(x)          (((uint32_t)(((uint32_t)(x)) << CAAM_HT_JQ_CTRL_LS_PRIM_ICID_SHIFT)) & CAAM_HT_JQ_CTRL_LS_PRIM_ICID_MASK)

#define CAAM_HT_JQ_CTRL_LS_OUT_DID_MASK          (0xF0000U)
#define CAAM_HT_JQ_CTRL_LS_OUT_DID_SHIFT         (16U)
#define CAAM_HT_JQ_CTRL_LS_OUT_DID(x)            (((uint32_t)(((uint32_t)(x)) << CAAM_HT_JQ_CTRL_LS_OUT_DID_SHIFT)) & CAAM_HT_JQ_CTRL_LS_OUT_DID_MASK)

#define CAAM_HT_JQ_CTRL_LS_OUT_ICID_MASK         (0xFFE00000U)
#define CAAM_HT_JQ_CTRL_LS_OUT_ICID_SHIFT        (21U)
#define CAAM_HT_JQ_CTRL_LS_OUT_ICID(x)           (((uint32_t)(((uint32_t)(x)) << CAAM_HT_JQ_CTRL_LS_OUT_ICID_SHIFT)) & CAAM_HT_JQ_CTRL_LS_OUT_ICID_MASK)
/*! @} */

/* The count of CAAM_HT_JQ_CTRL_LS */
#define CAAM_HT_JQ_CTRL_LS_COUNT                 (1U)

/*! @name HT_STATUS - Holding Tank Status */
/*! @{ */

#define CAAM_HT_STATUS_PEND_0_MASK               (0x1U)
#define CAAM_HT_STATUS_PEND_0_SHIFT              (0U)
#define CAAM_HT_STATUS_PEND_0(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_HT_STATUS_PEND_0_SHIFT)) & CAAM_HT_STATUS_PEND_0_MASK)

#define CAAM_HT_STATUS_IN_USE_MASK               (0x40000000U)
#define CAAM_HT_STATUS_IN_USE_SHIFT              (30U)
#define CAAM_HT_STATUS_IN_USE(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_HT_STATUS_IN_USE_SHIFT)) & CAAM_HT_STATUS_IN_USE_MASK)

#define CAAM_HT_STATUS_BC_MASK                   (0x80000000U)
#define CAAM_HT_STATUS_BC_SHIFT                  (31U)
#define CAAM_HT_STATUS_BC(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_HT_STATUS_BC_SHIFT)) & CAAM_HT_STATUS_BC_MASK)
/*! @} */

/* The count of CAAM_HT_STATUS */
#define CAAM_HT_STATUS_COUNT                     (1U)

/*! @name JQ_DEBUG_SEL - Job Queue Debug Select Register */
/*! @{ */

#define CAAM_JQ_DEBUG_SEL_HT_SEL_MASK            (0x1U)
#define CAAM_JQ_DEBUG_SEL_HT_SEL_SHIFT           (0U)
#define CAAM_JQ_DEBUG_SEL_HT_SEL(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_JQ_DEBUG_SEL_HT_SEL_SHIFT)) & CAAM_JQ_DEBUG_SEL_HT_SEL_MASK)

#define CAAM_JQ_DEBUG_SEL_JOB_ID_MASK            (0x70000U)
#define CAAM_JQ_DEBUG_SEL_JOB_ID_SHIFT           (16U)
#define CAAM_JQ_DEBUG_SEL_JOB_ID(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_JQ_DEBUG_SEL_JOB_ID_SHIFT)) & CAAM_JQ_DEBUG_SEL_JOB_ID_MASK)
/*! @} */

/*! @name JRJIDU_LS - Job Ring Job IDs in Use Register, least-significant half */
/*! @{ */

#define CAAM_JRJIDU_LS_JID00_MASK                (0x1U)
#define CAAM_JRJIDU_LS_JID00_SHIFT               (0U)
#define CAAM_JRJIDU_LS_JID00(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_JRJIDU_LS_JID00_SHIFT)) & CAAM_JRJIDU_LS_JID00_MASK)

#define CAAM_JRJIDU_LS_JID01_MASK                (0x2U)
#define CAAM_JRJIDU_LS_JID01_SHIFT               (1U)
#define CAAM_JRJIDU_LS_JID01(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_JRJIDU_LS_JID01_SHIFT)) & CAAM_JRJIDU_LS_JID01_MASK)

#define CAAM_JRJIDU_LS_JID02_MASK                (0x4U)
#define CAAM_JRJIDU_LS_JID02_SHIFT               (2U)
#define CAAM_JRJIDU_LS_JID02(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_JRJIDU_LS_JID02_SHIFT)) & CAAM_JRJIDU_LS_JID02_MASK)

#define CAAM_JRJIDU_LS_JID03_MASK                (0x8U)
#define CAAM_JRJIDU_LS_JID03_SHIFT               (3U)
#define CAAM_JRJIDU_LS_JID03(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_JRJIDU_LS_JID03_SHIFT)) & CAAM_JRJIDU_LS_JID03_MASK)
/*! @} */

/*! @name JRJDJIFBC - Job Ring Job-Done Job ID FIFO BC */
/*! @{ */

#define CAAM_JRJDJIFBC_BC_MASK                   (0x80000000U)
#define CAAM_JRJDJIFBC_BC_SHIFT                  (31U)
#define CAAM_JRJDJIFBC_BC(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_JRJDJIFBC_BC_SHIFT)) & CAAM_JRJDJIFBC_BC_MASK)
/*! @} */

/*! @name JRJDJIF - Job Ring Job-Done Job ID FIFO */
/*! @{ */

#define CAAM_JRJDJIF_JOB_ID_ENTRY_MASK           (0x7U)
#define CAAM_JRJDJIF_JOB_ID_ENTRY_SHIFT          (0U)
#define CAAM_JRJDJIF_JOB_ID_ENTRY(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_JRJDJIF_JOB_ID_ENTRY_SHIFT)) & CAAM_JRJDJIF_JOB_ID_ENTRY_MASK)
/*! @} */

/*! @name JRJDS1 - Job Ring Job-Done Source 1 */
/*! @{ */

#define CAAM_JRJDS1_SRC_MASK                     (0x3U)
#define CAAM_JRJDS1_SRC_SHIFT                    (0U)
#define CAAM_JRJDS1_SRC(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_JRJDS1_SRC_SHIFT)) & CAAM_JRJDS1_SRC_MASK)

#define CAAM_JRJDS1_VALID_MASK                   (0x80000000U)
#define CAAM_JRJDS1_VALID_SHIFT                  (31U)
#define CAAM_JRJDS1_VALID(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_JRJDS1_VALID_SHIFT)) & CAAM_JRJDS1_VALID_MASK)
/*! @} */

/*! @name JRJDDA - Job Ring Job-Done Descriptor Address 0 Register */
/*! @{ */

#define CAAM_JRJDDA_JD_ADDR_MASK                 (0xFFFFFFFFFU)
#define CAAM_JRJDDA_JD_ADDR_SHIFT                (0U)
#define CAAM_JRJDDA_JD_ADDR(x)                   (((uint64_t)(((uint64_t)(x)) << CAAM_JRJDDA_JD_ADDR_SHIFT)) & CAAM_JRJDDA_JD_ADDR_MASK)
/*! @} */

/* The count of CAAM_JRJDDA */
#define CAAM_JRJDDA_COUNT                        (1U)

/*! @name CRNR_MS - CHA Revision Number Register, most-significant half */
/*! @{ */

#define CAAM_CRNR_MS_CRCRN_MASK                  (0xFU)
#define CAAM_CRNR_MS_CRCRN_SHIFT                 (0U)
#define CAAM_CRNR_MS_CRCRN(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_CRNR_MS_CRCRN_SHIFT)) & CAAM_CRNR_MS_CRCRN_MASK)

#define CAAM_CRNR_MS_SNW9RN_MASK                 (0xF0U)
#define CAAM_CRNR_MS_SNW9RN_SHIFT                (4U)
#define CAAM_CRNR_MS_SNW9RN(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_CRNR_MS_SNW9RN_SHIFT)) & CAAM_CRNR_MS_SNW9RN_MASK)

#define CAAM_CRNR_MS_ZERN_MASK                   (0xF00U)
#define CAAM_CRNR_MS_ZERN_SHIFT                  (8U)
#define CAAM_CRNR_MS_ZERN(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CRNR_MS_ZERN_SHIFT)) & CAAM_CRNR_MS_ZERN_MASK)

#define CAAM_CRNR_MS_ZARN_MASK                   (0xF000U)
#define CAAM_CRNR_MS_ZARN_SHIFT                  (12U)
#define CAAM_CRNR_MS_ZARN(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CRNR_MS_ZARN_SHIFT)) & CAAM_CRNR_MS_ZARN_MASK)

#define CAAM_CRNR_MS_DECORN_MASK                 (0xF000000U)
#define CAAM_CRNR_MS_DECORN_SHIFT                (24U)
#define CAAM_CRNR_MS_DECORN(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_CRNR_MS_DECORN_SHIFT)) & CAAM_CRNR_MS_DECORN_MASK)

#define CAAM_CRNR_MS_JRRN_MASK                   (0xF0000000U)
#define CAAM_CRNR_MS_JRRN_SHIFT                  (28U)
#define CAAM_CRNR_MS_JRRN(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CRNR_MS_JRRN_SHIFT)) & CAAM_CRNR_MS_JRRN_MASK)
/*! @} */

/*! @name CRNR_LS - CHA Revision Number Register, least-significant half */
/*! @{ */

#define CAAM_CRNR_LS_AESRN_MASK                  (0xFU)
#define CAAM_CRNR_LS_AESRN_SHIFT                 (0U)
#define CAAM_CRNR_LS_AESRN(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_CRNR_LS_AESRN_SHIFT)) & CAAM_CRNR_LS_AESRN_MASK)

#define CAAM_CRNR_LS_DESRN_MASK                  (0xF0U)
#define CAAM_CRNR_LS_DESRN_SHIFT                 (4U)
#define CAAM_CRNR_LS_DESRN(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_CRNR_LS_DESRN_SHIFT)) & CAAM_CRNR_LS_DESRN_MASK)

#define CAAM_CRNR_LS_MDRN_MASK                   (0xF000U)
#define CAAM_CRNR_LS_MDRN_SHIFT                  (12U)
#define CAAM_CRNR_LS_MDRN(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CRNR_LS_MDRN_SHIFT)) & CAAM_CRNR_LS_MDRN_MASK)

#define CAAM_CRNR_LS_RNGRN_MASK                  (0xF0000U)
#define CAAM_CRNR_LS_RNGRN_SHIFT                 (16U)
#define CAAM_CRNR_LS_RNGRN(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_CRNR_LS_RNGRN_SHIFT)) & CAAM_CRNR_LS_RNGRN_MASK)

#define CAAM_CRNR_LS_SNW8RN_MASK                 (0xF00000U)
#define CAAM_CRNR_LS_SNW8RN_SHIFT                (20U)
#define CAAM_CRNR_LS_SNW8RN(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_CRNR_LS_SNW8RN_SHIFT)) & CAAM_CRNR_LS_SNW8RN_MASK)

#define CAAM_CRNR_LS_KASRN_MASK                  (0xF000000U)
#define CAAM_CRNR_LS_KASRN_SHIFT                 (24U)
#define CAAM_CRNR_LS_KASRN(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_CRNR_LS_KASRN_SHIFT)) & CAAM_CRNR_LS_KASRN_MASK)

#define CAAM_CRNR_LS_PKRN_MASK                   (0xF0000000U)
#define CAAM_CRNR_LS_PKRN_SHIFT                  (28U)
/*! PKRN
 *  0b0000..PKHA-SDv1
 *  0b0001..PKHA-SDv2
 *  0b0010..PKHA-SDv3
 *  0b0011..PKHA-SDv4
 */
#define CAAM_CRNR_LS_PKRN(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CRNR_LS_PKRN_SHIFT)) & CAAM_CRNR_LS_PKRN_MASK)
/*! @} */

/*! @name CTPR_MS - Compile Time Parameters Register, most-significant half */
/*! @{ */

#define CAAM_CTPR_MS_VIRT_EN_INCL_MASK           (0x1U)
#define CAAM_CTPR_MS_VIRT_EN_INCL_SHIFT          (0U)
#define CAAM_CTPR_MS_VIRT_EN_INCL(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_MS_VIRT_EN_INCL_SHIFT)) & CAAM_CTPR_MS_VIRT_EN_INCL_MASK)

#define CAAM_CTPR_MS_VIRT_EN_POR_VALUE_MASK      (0x2U)
#define CAAM_CTPR_MS_VIRT_EN_POR_VALUE_SHIFT     (1U)
#define CAAM_CTPR_MS_VIRT_EN_POR_VALUE(x)        (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_MS_VIRT_EN_POR_VALUE_SHIFT)) & CAAM_CTPR_MS_VIRT_EN_POR_VALUE_MASK)

#define CAAM_CTPR_MS_REG_PG_SIZE_MASK            (0x10U)
#define CAAM_CTPR_MS_REG_PG_SIZE_SHIFT           (4U)
#define CAAM_CTPR_MS_REG_PG_SIZE(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_MS_REG_PG_SIZE_SHIFT)) & CAAM_CTPR_MS_REG_PG_SIZE_MASK)

#define CAAM_CTPR_MS_RNG_I_MASK                  (0x700U)
#define CAAM_CTPR_MS_RNG_I_SHIFT                 (8U)
#define CAAM_CTPR_MS_RNG_I(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_MS_RNG_I_SHIFT)) & CAAM_CTPR_MS_RNG_I_MASK)

#define CAAM_CTPR_MS_AI_INCL_MASK                (0x800U)
#define CAAM_CTPR_MS_AI_INCL_SHIFT               (11U)
#define CAAM_CTPR_MS_AI_INCL(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_MS_AI_INCL_SHIFT)) & CAAM_CTPR_MS_AI_INCL_MASK)

#define CAAM_CTPR_MS_DPAA2_MASK                  (0x2000U)
#define CAAM_CTPR_MS_DPAA2_SHIFT                 (13U)
#define CAAM_CTPR_MS_DPAA2(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_MS_DPAA2_SHIFT)) & CAAM_CTPR_MS_DPAA2_MASK)

#define CAAM_CTPR_MS_IP_CLK_MASK                 (0x4000U)
#define CAAM_CTPR_MS_IP_CLK_SHIFT                (14U)
#define CAAM_CTPR_MS_IP_CLK(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_MS_IP_CLK_SHIFT)) & CAAM_CTPR_MS_IP_CLK_MASK)

#define CAAM_CTPR_MS_MCFG_BURST_MASK             (0x10000U)
#define CAAM_CTPR_MS_MCFG_BURST_SHIFT            (16U)
#define CAAM_CTPR_MS_MCFG_BURST(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_MS_MCFG_BURST_SHIFT)) & CAAM_CTPR_MS_MCFG_BURST_MASK)

#define CAAM_CTPR_MS_MCFG_PS_MASK                (0x20000U)
#define CAAM_CTPR_MS_MCFG_PS_SHIFT               (17U)
#define CAAM_CTPR_MS_MCFG_PS(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_MS_MCFG_PS_SHIFT)) & CAAM_CTPR_MS_MCFG_PS_MASK)

#define CAAM_CTPR_MS_SG8_MASK                    (0x40000U)
#define CAAM_CTPR_MS_SG8_SHIFT                   (18U)
#define CAAM_CTPR_MS_SG8(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_MS_SG8_SHIFT)) & CAAM_CTPR_MS_SG8_MASK)

#define CAAM_CTPR_MS_PM_EVT_BUS_MASK             (0x80000U)
#define CAAM_CTPR_MS_PM_EVT_BUS_SHIFT            (19U)
#define CAAM_CTPR_MS_PM_EVT_BUS(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_MS_PM_EVT_BUS_SHIFT)) & CAAM_CTPR_MS_PM_EVT_BUS_MASK)

#define CAAM_CTPR_MS_DECO_WD_MASK                (0x100000U)
#define CAAM_CTPR_MS_DECO_WD_SHIFT               (20U)
#define CAAM_CTPR_MS_DECO_WD(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_MS_DECO_WD_SHIFT)) & CAAM_CTPR_MS_DECO_WD_MASK)

#define CAAM_CTPR_MS_PC_MASK                     (0x200000U)
#define CAAM_CTPR_MS_PC_SHIFT                    (21U)
#define CAAM_CTPR_MS_PC(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_MS_PC_SHIFT)) & CAAM_CTPR_MS_PC_MASK)

#define CAAM_CTPR_MS_C1C2_MASK                   (0x800000U)
#define CAAM_CTPR_MS_C1C2_SHIFT                  (23U)
#define CAAM_CTPR_MS_C1C2(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_MS_C1C2_SHIFT)) & CAAM_CTPR_MS_C1C2_MASK)

#define CAAM_CTPR_MS_ACC_CTL_MASK                (0x1000000U)
#define CAAM_CTPR_MS_ACC_CTL_SHIFT               (24U)
#define CAAM_CTPR_MS_ACC_CTL(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_MS_ACC_CTL_SHIFT)) & CAAM_CTPR_MS_ACC_CTL_MASK)

#define CAAM_CTPR_MS_QI_MASK                     (0x2000000U)
#define CAAM_CTPR_MS_QI_SHIFT                    (25U)
#define CAAM_CTPR_MS_QI(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_MS_QI_SHIFT)) & CAAM_CTPR_MS_QI_MASK)

#define CAAM_CTPR_MS_AXI_PRI_MASK                (0x4000000U)
#define CAAM_CTPR_MS_AXI_PRI_SHIFT               (26U)
#define CAAM_CTPR_MS_AXI_PRI(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_MS_AXI_PRI_SHIFT)) & CAAM_CTPR_MS_AXI_PRI_MASK)

#define CAAM_CTPR_MS_AXI_LIODN_MASK              (0x8000000U)
#define CAAM_CTPR_MS_AXI_LIODN_SHIFT             (27U)
#define CAAM_CTPR_MS_AXI_LIODN(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_MS_AXI_LIODN_SHIFT)) & CAAM_CTPR_MS_AXI_LIODN_MASK)

#define CAAM_CTPR_MS_AXI_PIPE_DEPTH_MASK         (0xF0000000U)
#define CAAM_CTPR_MS_AXI_PIPE_DEPTH_SHIFT        (28U)
#define CAAM_CTPR_MS_AXI_PIPE_DEPTH(x)           (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_MS_AXI_PIPE_DEPTH_SHIFT)) & CAAM_CTPR_MS_AXI_PIPE_DEPTH_MASK)
/*! @} */

/*! @name CTPR_LS - Compile Time Parameters Register, least-significant half */
/*! @{ */

#define CAAM_CTPR_LS_KG_DS_MASK                  (0x1U)
#define CAAM_CTPR_LS_KG_DS_SHIFT                 (0U)
/*! KG_DS
 *  0b0..CAAM does not implement specialized support for Public Key Generation and Digital Signatures.
 *  0b1..CAAM implements specialized support for Public Key Generation and Digital Signatures.
 */
#define CAAM_CTPR_LS_KG_DS(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_LS_KG_DS_SHIFT)) & CAAM_CTPR_LS_KG_DS_MASK)

#define CAAM_CTPR_LS_BLOB_MASK                   (0x2U)
#define CAAM_CTPR_LS_BLOB_SHIFT                  (1U)
/*! BLOB
 *  0b0..CAAM does not implement specialized support for encapsulating and decapsulating cryptographic blobs.
 *  0b1..CAAM implements specialized support for encapsulating and decapsulating cryptographic blobs.
 */
#define CAAM_CTPR_LS_BLOB(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_LS_BLOB_SHIFT)) & CAAM_CTPR_LS_BLOB_MASK)

#define CAAM_CTPR_LS_WIFI_MASK                   (0x4U)
#define CAAM_CTPR_LS_WIFI_SHIFT                  (2U)
/*! WIFI
 *  0b0..CAAM does not implement specialized support for the WIFI protocol.
 *  0b1..CAAM implements specialized support for the WIFI protocol.
 */
#define CAAM_CTPR_LS_WIFI(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_LS_WIFI_SHIFT)) & CAAM_CTPR_LS_WIFI_MASK)

#define CAAM_CTPR_LS_WIMAX_MASK                  (0x8U)
#define CAAM_CTPR_LS_WIMAX_SHIFT                 (3U)
/*! WIMAX
 *  0b0..CAAM does not implement specialized support for the WIMAX protocol.
 *  0b1..CAAM implements specialized support for the WIMAX protocol.
 */
#define CAAM_CTPR_LS_WIMAX(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_LS_WIMAX_SHIFT)) & CAAM_CTPR_LS_WIMAX_MASK)

#define CAAM_CTPR_LS_SRTP_MASK                   (0x10U)
#define CAAM_CTPR_LS_SRTP_SHIFT                  (4U)
/*! SRTP
 *  0b0..CAAM does not implement specialized support for the SRTP protocol.
 *  0b1..CAAM implements specialized support for the SRTP protocol.
 */
#define CAAM_CTPR_LS_SRTP(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_LS_SRTP_SHIFT)) & CAAM_CTPR_LS_SRTP_MASK)

#define CAAM_CTPR_LS_IPSEC_MASK                  (0x20U)
#define CAAM_CTPR_LS_IPSEC_SHIFT                 (5U)
/*! IPSEC
 *  0b0..CAAM does not implement specialized support for the IPSEC protocol.
 *  0b1..CAAM implements specialized support for the IPSEC protocol.
 */
#define CAAM_CTPR_LS_IPSEC(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_LS_IPSEC_SHIFT)) & CAAM_CTPR_LS_IPSEC_MASK)

#define CAAM_CTPR_LS_IKE_MASK                    (0x40U)
#define CAAM_CTPR_LS_IKE_SHIFT                   (6U)
/*! IKE
 *  0b0..CAAM does not implement specialized support for the IKE protocol.
 *  0b1..CAAM implements specialized support for the IKE protocol.
 */
#define CAAM_CTPR_LS_IKE(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_LS_IKE_SHIFT)) & CAAM_CTPR_LS_IKE_MASK)

#define CAAM_CTPR_LS_SSL_TLS_MASK                (0x80U)
#define CAAM_CTPR_LS_SSL_TLS_SHIFT               (7U)
/*! SSL_TLS
 *  0b0..CAAM does not implement specialized support for the SSL and TLS protocols.
 *  0b1..CAAM implements specialized support for the SSL and TLS protocols.
 */
#define CAAM_CTPR_LS_SSL_TLS(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_LS_SSL_TLS_SHIFT)) & CAAM_CTPR_LS_SSL_TLS_MASK)

#define CAAM_CTPR_LS_TLS_PRF_MASK                (0x100U)
#define CAAM_CTPR_LS_TLS_PRF_SHIFT               (8U)
/*! TLS_PRF
 *  0b0..CAAM does not implement specialized support for the TLS protocol pseudo-random function.
 *  0b1..CAAM implements specialized support for the TLS protocol pseudo-random function.
 */
#define CAAM_CTPR_LS_TLS_PRF(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_LS_TLS_PRF_SHIFT)) & CAAM_CTPR_LS_TLS_PRF_MASK)

#define CAAM_CTPR_LS_MACSEC_MASK                 (0x200U)
#define CAAM_CTPR_LS_MACSEC_SHIFT                (9U)
/*! MACSEC
 *  0b0..CAAM does not implement specialized support for the MACSEC protocol.
 *  0b1..CAAM implements specialized support for the MACSEC protocol.
 */
#define CAAM_CTPR_LS_MACSEC(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_LS_MACSEC_SHIFT)) & CAAM_CTPR_LS_MACSEC_MASK)

#define CAAM_CTPR_LS_RSA_MASK                    (0x400U)
#define CAAM_CTPR_LS_RSA_SHIFT                   (10U)
/*! RSA
 *  0b0..CAAM does not implement specialized support for RSA encrypt and decrypt operations.
 *  0b1..CAAM implements specialized support for RSA encrypt and decrypt operations.
 */
#define CAAM_CTPR_LS_RSA(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_LS_RSA_SHIFT)) & CAAM_CTPR_LS_RSA_MASK)

#define CAAM_CTPR_LS_P3G_LTE_MASK                (0x800U)
#define CAAM_CTPR_LS_P3G_LTE_SHIFT               (11U)
/*! P3G_LTE
 *  0b0..CAAM does not implement specialized support for 3G and LTE protocols.
 *  0b1..CAAM implements specialized support for 3G and LTE protocols.
 */
#define CAAM_CTPR_LS_P3G_LTE(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_LS_P3G_LTE_SHIFT)) & CAAM_CTPR_LS_P3G_LTE_MASK)

#define CAAM_CTPR_LS_DBL_CRC_MASK                (0x1000U)
#define CAAM_CTPR_LS_DBL_CRC_SHIFT               (12U)
/*! DBL_CRC
 *  0b0..CAAM does not implement specialized support for Double CRC.
 *  0b1..CAAM implements specialized support for Double CRC.
 */
#define CAAM_CTPR_LS_DBL_CRC(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_LS_DBL_CRC_SHIFT)) & CAAM_CTPR_LS_DBL_CRC_MASK)

#define CAAM_CTPR_LS_MAN_PROT_MASK               (0x2000U)
#define CAAM_CTPR_LS_MAN_PROT_SHIFT              (13U)
/*! MAN_PROT
 *  0b0..CAAM does not implement Manufacturing Protection functions.
 *  0b1..CAAM implements Manufacturing Protection functions.
 */
#define CAAM_CTPR_LS_MAN_PROT(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_LS_MAN_PROT_SHIFT)) & CAAM_CTPR_LS_MAN_PROT_MASK)

#define CAAM_CTPR_LS_DKP_MASK                    (0x4000U)
#define CAAM_CTPR_LS_DKP_SHIFT                   (14U)
/*! DKP
 *  0b0..CAAM does not implement the Derived Key Protocol.
 *  0b1..CAAM implements the Derived Key Protocol.
 */
#define CAAM_CTPR_LS_DKP(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_CTPR_LS_DKP_SHIFT)) & CAAM_CTPR_LS_DKP_MASK)
/*! @} */

/*! @name SMSTA - Secure Memory Status Register */
/*! @{ */

#define CAAM_SMSTA_STATE_MASK                    (0xFU)
#define CAAM_SMSTA_STATE_SHIFT                   (0U)
/*! STATE
 *  0b0000..Reset State
 *  0b0001..Initialize State
 *  0b0010..Normal State
 *  0b0011..Fail State
 */
#define CAAM_SMSTA_STATE(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_SMSTA_STATE_SHIFT)) & CAAM_SMSTA_STATE_MASK)

#define CAAM_SMSTA_ACCERR_MASK                   (0xF0U)
#define CAAM_SMSTA_ACCERR_SHIFT                  (4U)
/*! ACCERR
 *  0b0000..No error occurred
 *  0b0001..A bus transaction attempted to access a page in Secure Memory, but the page was not allocated to any partition.
 *  0b0010..A bus transaction attempted to access a partition, but the transaction's TrustZone World, DID was not
 *          granted access to the partition in the partition's SMAG2/1JR registers.
 *  0b0011..A bus transaction attempted to read, but reads from this partition are not allowed.
 *  0b0100..A bus transaction attempted to write, but writes to this partition are not allowed.
 *  0b0110..A bus transaction attempted a non-key read, but the only reads permitted from this partition are key reads.
 *  0b1001..Secure Memory Blob import or export was attempted, but Secure Memory Blob access is not allowed for this partition.
 *  0b1010..A Descriptor attempted a Secure Memory Blob import or export, but not all of the pages referenced were from the same partition.
 *  0b1011..A memory access was directed to Secure Memory, but the specified address is not implemented in Secure
 *          Memory. The address was either outside the address range occupied by Secure Memory, or was within an
 *          unimplemented portion of the 4kbyte address block occupied by a 1Kbyte or 2Kbyte Secure Memory page.
 *  0b1100..A bus transaction was attempted, but the burst would have crossed a page boundary.
 *  0b1101..An attempt was made to access a page while it was still being initialized.
 */
#define CAAM_SMSTA_ACCERR(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_SMSTA_ACCERR_SHIFT)) & CAAM_SMSTA_ACCERR_MASK)

#define CAAM_SMSTA_DID_MASK                      (0xF00U)
#define CAAM_SMSTA_DID_SHIFT                     (8U)
#define CAAM_SMSTA_DID(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_SMSTA_DID_SHIFT)) & CAAM_SMSTA_DID_MASK)

#define CAAM_SMSTA_NS_MASK                       (0x1000U)
#define CAAM_SMSTA_NS_SHIFT                      (12U)
#define CAAM_SMSTA_NS(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_SMSTA_NS_SHIFT)) & CAAM_SMSTA_NS_MASK)

#define CAAM_SMSTA_SMR_WP_MASK                   (0x8000U)
#define CAAM_SMSTA_SMR_WP_SHIFT                  (15U)
#define CAAM_SMSTA_SMR_WP(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_SMSTA_SMR_WP_SHIFT)) & CAAM_SMSTA_SMR_WP_MASK)

#define CAAM_SMSTA_PAGE_MASK                     (0x7FF0000U)
#define CAAM_SMSTA_PAGE_SHIFT                    (16U)
#define CAAM_SMSTA_PAGE(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_SMSTA_PAGE_SHIFT)) & CAAM_SMSTA_PAGE_MASK)

#define CAAM_SMSTA_PART_MASK                     (0xF0000000U)
#define CAAM_SMSTA_PART_SHIFT                    (28U)
#define CAAM_SMSTA_PART(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_SMSTA_PART_SHIFT)) & CAAM_SMSTA_PART_MASK)
/*! @} */

/*! @name SMPO - Secure Memory Partition Owners Register */
/*! @{ */

#define CAAM_SMPO_PO0_MASK                       (0x3U)
#define CAAM_SMPO_PO0_SHIFT                      (0U)
/*! PO0
 *  0b00..Available; Unowned. A Job Ring owner may claim partition 0 by writing to the appropriate SMAPJR register
 *        address alias. Note that the entire register will return all 0s if read by a entity that does not own
 *        the Job Ring associated with the SMPO address alias that was read.
 *  0b01..Partition 0 does not exist in this version
 *  0b10..Another entity owns partition 0. Partition 0 is unavailable to the reader. If the reader attempts to
 *        de-allocate partition 0 or write to the SMAPJR register or SMAGJR register for partition 0 or allocate a
 *        page to or de-allocate a page from partition 0 the command will be ignored. (Note that if a CSP partition is
 *        de-allocated, all entities (including the owner that de-allocated the partition) will see a 0b10 value
 *        for that partition until all its pages have been zeroized.)
 *  0b11..The entity that read the SMPO register owns partition 0. Ownership is claimed when the access
 *        permissions register (SMAPJR) of an available partition is first written.
 */
#define CAAM_SMPO_PO0(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_SMPO_PO0_SHIFT)) & CAAM_SMPO_PO0_MASK)

#define CAAM_SMPO_PO1_MASK                       (0xCU)
#define CAAM_SMPO_PO1_SHIFT                      (2U)
#define CAAM_SMPO_PO1(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_SMPO_PO1_SHIFT)) & CAAM_SMPO_PO1_MASK)

#define CAAM_SMPO_PO2_MASK                       (0x30U)
#define CAAM_SMPO_PO2_SHIFT                      (4U)
#define CAAM_SMPO_PO2(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_SMPO_PO2_SHIFT)) & CAAM_SMPO_PO2_MASK)

#define CAAM_SMPO_PO3_MASK                       (0xC0U)
#define CAAM_SMPO_PO3_SHIFT                      (6U)
#define CAAM_SMPO_PO3(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_SMPO_PO3_SHIFT)) & CAAM_SMPO_PO3_MASK)

#define CAAM_SMPO_PO4_MASK                       (0x300U)
#define CAAM_SMPO_PO4_SHIFT                      (8U)
#define CAAM_SMPO_PO4(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_SMPO_PO4_SHIFT)) & CAAM_SMPO_PO4_MASK)

#define CAAM_SMPO_PO5_MASK                       (0xC00U)
#define CAAM_SMPO_PO5_SHIFT                      (10U)
#define CAAM_SMPO_PO5(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_SMPO_PO5_SHIFT)) & CAAM_SMPO_PO5_MASK)

#define CAAM_SMPO_PO6_MASK                       (0x3000U)
#define CAAM_SMPO_PO6_SHIFT                      (12U)
#define CAAM_SMPO_PO6(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_SMPO_PO6_SHIFT)) & CAAM_SMPO_PO6_MASK)

#define CAAM_SMPO_PO7_MASK                       (0xC000U)
#define CAAM_SMPO_PO7_SHIFT                      (14U)
#define CAAM_SMPO_PO7(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_SMPO_PO7_SHIFT)) & CAAM_SMPO_PO7_MASK)

#define CAAM_SMPO_PO8_MASK                       (0x30000U)
#define CAAM_SMPO_PO8_SHIFT                      (16U)
#define CAAM_SMPO_PO8(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_SMPO_PO8_SHIFT)) & CAAM_SMPO_PO8_MASK)

#define CAAM_SMPO_PO9_MASK                       (0xC0000U)
#define CAAM_SMPO_PO9_SHIFT                      (18U)
#define CAAM_SMPO_PO9(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_SMPO_PO9_SHIFT)) & CAAM_SMPO_PO9_MASK)

#define CAAM_SMPO_PO10_MASK                      (0x300000U)
#define CAAM_SMPO_PO10_SHIFT                     (20U)
#define CAAM_SMPO_PO10(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_SMPO_PO10_SHIFT)) & CAAM_SMPO_PO10_MASK)

#define CAAM_SMPO_PO11_MASK                      (0xC00000U)
#define CAAM_SMPO_PO11_SHIFT                     (22U)
#define CAAM_SMPO_PO11(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_SMPO_PO11_SHIFT)) & CAAM_SMPO_PO11_MASK)

#define CAAM_SMPO_PO12_MASK                      (0x3000000U)
#define CAAM_SMPO_PO12_SHIFT                     (24U)
#define CAAM_SMPO_PO12(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_SMPO_PO12_SHIFT)) & CAAM_SMPO_PO12_MASK)

#define CAAM_SMPO_PO13_MASK                      (0xC000000U)
#define CAAM_SMPO_PO13_SHIFT                     (26U)
#define CAAM_SMPO_PO13(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_SMPO_PO13_SHIFT)) & CAAM_SMPO_PO13_MASK)

#define CAAM_SMPO_PO14_MASK                      (0x30000000U)
#define CAAM_SMPO_PO14_SHIFT                     (28U)
#define CAAM_SMPO_PO14(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_SMPO_PO14_SHIFT)) & CAAM_SMPO_PO14_MASK)

#define CAAM_SMPO_PO15_MASK                      (0xC0000000U)
#define CAAM_SMPO_PO15_SHIFT                     (30U)
#define CAAM_SMPO_PO15(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_SMPO_PO15_SHIFT)) & CAAM_SMPO_PO15_MASK)
/*! @} */

/*! @name FAR - Fault Address Register */
/*! @{ */

#define CAAM_FAR_FAR_MASK                        (0xFFFFFFFFFU)
#define CAAM_FAR_FAR_SHIFT                       (0U)
#define CAAM_FAR_FAR(x)                          (((uint64_t)(((uint64_t)(x)) << CAAM_FAR_FAR_SHIFT)) & CAAM_FAR_FAR_MASK)
/*! @} */

/*! @name FADID - Fault Address DID Register */
/*! @{ */

#define CAAM_FADID_FDID_MASK                     (0xFU)
#define CAAM_FADID_FDID_SHIFT                    (0U)
#define CAAM_FADID_FDID(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_FADID_FDID_SHIFT)) & CAAM_FADID_FDID_MASK)

#define CAAM_FADID_FNS_MASK                      (0x10U)
#define CAAM_FADID_FNS_SHIFT                     (4U)
#define CAAM_FADID_FNS(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_FADID_FNS_SHIFT)) & CAAM_FADID_FNS_MASK)

#define CAAM_FADID_FICID_MASK                    (0xFFE0U)
#define CAAM_FADID_FICID_SHIFT                   (5U)
#define CAAM_FADID_FICID(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_FADID_FICID_SHIFT)) & CAAM_FADID_FICID_MASK)
/*! @} */

/*! @name FADR - Fault Address Detail Register */
/*! @{ */

#define CAAM_FADR_FSZ_MASK                       (0x7FU)
#define CAAM_FADR_FSZ_SHIFT                      (0U)
#define CAAM_FADR_FSZ(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_FADR_FSZ_SHIFT)) & CAAM_FADR_FSZ_MASK)

#define CAAM_FADR_TYP_MASK                       (0x80U)
#define CAAM_FADR_TYP_SHIFT                      (7U)
/*! TYP
 *  0b0..Read.
 *  0b1..Write.
 */
#define CAAM_FADR_TYP(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_FADR_TYP_SHIFT)) & CAAM_FADR_TYP_MASK)

#define CAAM_FADR_BLKID_MASK                     (0xF00U)
#define CAAM_FADR_BLKID_SHIFT                    (8U)
/*! BLKID
 *  0b0100..job queue controller Burst Buffer
 *  0b0101..One of the Job Rings (see JSRC field)
 *  0b1000..DECO0
 */
#define CAAM_FADR_BLKID(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_FADR_BLKID_SHIFT)) & CAAM_FADR_BLKID_MASK)

#define CAAM_FADR_JSRC_MASK                      (0x7000U)
#define CAAM_FADR_JSRC_SHIFT                     (12U)
/*! JSRC
 *  0b000..Job Ring 0
 *  0b001..Job Ring 1
 *  0b010..Job Ring 2
 *  0b011..Job Ring 3
 *  0b100..RTIC
 *  0b101..reserved
 *  0b110..reserved
 *  0b111..reserved
 */
#define CAAM_FADR_JSRC(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_FADR_JSRC_SHIFT)) & CAAM_FADR_JSRC_MASK)

#define CAAM_FADR_DTYP_MASK                      (0x8000U)
#define CAAM_FADR_DTYP_SHIFT                     (15U)
/*! DTYP
 *  0b0..message data
 *  0b1..control data
 */
#define CAAM_FADR_DTYP(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_FADR_DTYP_SHIFT)) & CAAM_FADR_DTYP_MASK)

#define CAAM_FADR_FSZ_EXT_MASK                   (0x70000U)
#define CAAM_FADR_FSZ_EXT_SHIFT                  (16U)
#define CAAM_FADR_FSZ_EXT(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_FADR_FSZ_EXT_SHIFT)) & CAAM_FADR_FSZ_EXT_MASK)

#define CAAM_FADR_FKMOD_MASK                     (0x1000000U)
#define CAAM_FADR_FKMOD_SHIFT                    (24U)
/*! FKMOD
 *  0b0..CAAM DMA was not attempting to read the key modifier from Secure Memory at the time that the DMA error occurred.
 *  0b1..CAAM DMA was attempting to read the key modifier from Secure Memory at the time that the DMA error occurred.
 */
#define CAAM_FADR_FKMOD(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_FADR_FKMOD_SHIFT)) & CAAM_FADR_FKMOD_MASK)

#define CAAM_FADR_FKEY_MASK                      (0x2000000U)
#define CAAM_FADR_FKEY_SHIFT                     (25U)
/*! FKEY
 *  0b0..CAAM DMA was not attempting to perform a key read from Secure Memory at the time of the DMA error.
 *  0b1..CAAM DMA was attempting to perform a key read from Secure Memory at the time of the DMA error.
 */
#define CAAM_FADR_FKEY(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_FADR_FKEY_SHIFT)) & CAAM_FADR_FKEY_MASK)

#define CAAM_FADR_FTDSC_MASK                     (0x4000000U)
#define CAAM_FADR_FTDSC_SHIFT                    (26U)
/*! FTDSC
 *  0b0..CAAM DMA was not executing a Trusted Descriptor at the time of the DMA error.
 *  0b1..CAAM DMA was executing a Trusted Descriptor at the time of the DMA error.
 */
#define CAAM_FADR_FTDSC(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_FADR_FTDSC_SHIFT)) & CAAM_FADR_FTDSC_MASK)

#define CAAM_FADR_FBNDG_MASK                     (0x8000000U)
#define CAAM_FADR_FBNDG_SHIFT                    (27U)
/*! FBNDG
 *  0b0..CAAM DMA was not reading access permissions from a Secure Memory partition at the time of the DMA error.
 *  0b1..CAAM DMA was reading access permissions from a Secure Memory partition at the time of the DMA error.
 */
#define CAAM_FADR_FBNDG(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_FADR_FBNDG_SHIFT)) & CAAM_FADR_FBNDG_MASK)

#define CAAM_FADR_FNS_MASK                       (0x10000000U)
#define CAAM_FADR_FNS_SHIFT                      (28U)
/*! FNS
 *  0b0..CAAM DMA was asserting ns=0 at the time of the DMA error.
 *  0b1..CAAM DMA was asserting ns=1 at the time of the DMA error.
 */
#define CAAM_FADR_FNS(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_FADR_FNS_SHIFT)) & CAAM_FADR_FNS_MASK)

#define CAAM_FADR_FERR_MASK                      (0xC0000000U)
#define CAAM_FADR_FERR_SHIFT                     (30U)
/*! FERR
 *  0b00..OKAY - Normal Access
 *  0b01..Reserved
 *  0b10..SLVERR - Slave Error
 *  0b11..DECERR - Decode Error
 */
#define CAAM_FADR_FERR(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_FADR_FERR_SHIFT)) & CAAM_FADR_FERR_MASK)
/*! @} */

/*! @name CSTA - CAAM Status Register */
/*! @{ */

#define CAAM_CSTA_BSY_MASK                       (0x1U)
#define CAAM_CSTA_BSY_SHIFT                      (0U)
#define CAAM_CSTA_BSY(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_CSTA_BSY_SHIFT)) & CAAM_CSTA_BSY_MASK)

#define CAAM_CSTA_IDLE_MASK                      (0x2U)
#define CAAM_CSTA_IDLE_SHIFT                     (1U)
#define CAAM_CSTA_IDLE(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CSTA_IDLE_SHIFT)) & CAAM_CSTA_IDLE_MASK)

#define CAAM_CSTA_TRNG_IDLE_MASK                 (0x4U)
#define CAAM_CSTA_TRNG_IDLE_SHIFT                (2U)
#define CAAM_CSTA_TRNG_IDLE(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_CSTA_TRNG_IDLE_SHIFT)) & CAAM_CSTA_TRNG_IDLE_MASK)

#define CAAM_CSTA_MOO_MASK                       (0x300U)
#define CAAM_CSTA_MOO_SHIFT                      (8U)
/*! MOO
 *  0b00..Non-Secure
 *  0b01..Secure
 *  0b10..Trusted
 *  0b11..Fail
 */
#define CAAM_CSTA_MOO(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_CSTA_MOO_SHIFT)) & CAAM_CSTA_MOO_MASK)

#define CAAM_CSTA_PLEND_MASK                     (0x400U)
#define CAAM_CSTA_PLEND_SHIFT                    (10U)
/*! PLEND
 *  0b0..Platform default is Little Endian
 *  0b1..Platform default is Big Endian
 */
#define CAAM_CSTA_PLEND(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CSTA_PLEND_SHIFT)) & CAAM_CSTA_PLEND_MASK)
/*! @} */

/*! @name SMVID_MS - Secure Memory Version ID Register, most-significant half */
/*! @{ */

#define CAAM_SMVID_MS_NPAG_MASK                  (0x3FFU)
#define CAAM_SMVID_MS_NPAG_SHIFT                 (0U)
#define CAAM_SMVID_MS_NPAG(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_SMVID_MS_NPAG_SHIFT)) & CAAM_SMVID_MS_NPAG_MASK)

#define CAAM_SMVID_MS_NPRT_MASK                  (0xF000U)
#define CAAM_SMVID_MS_NPRT_SHIFT                 (12U)
#define CAAM_SMVID_MS_NPRT(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_SMVID_MS_NPRT_SHIFT)) & CAAM_SMVID_MS_NPRT_MASK)

#define CAAM_SMVID_MS_MAX_NPAG_MASK              (0x3FF0000U)
#define CAAM_SMVID_MS_MAX_NPAG_SHIFT             (16U)
#define CAAM_SMVID_MS_MAX_NPAG(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_SMVID_MS_MAX_NPAG_SHIFT)) & CAAM_SMVID_MS_MAX_NPAG_MASK)
/*! @} */

/*! @name SMVID_LS - Secure Memory Version ID Register, least-significant half */
/*! @{ */

#define CAAM_SMVID_LS_SMNV_MASK                  (0xFFU)
#define CAAM_SMVID_LS_SMNV_SHIFT                 (0U)
#define CAAM_SMVID_LS_SMNV(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_SMVID_LS_SMNV_SHIFT)) & CAAM_SMVID_LS_SMNV_MASK)

#define CAAM_SMVID_LS_SMJV_MASK                  (0xFF00U)
#define CAAM_SMVID_LS_SMJV_SHIFT                 (8U)
#define CAAM_SMVID_LS_SMJV(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_SMVID_LS_SMJV_SHIFT)) & CAAM_SMVID_LS_SMJV_MASK)

#define CAAM_SMVID_LS_PSIZ_MASK                  (0x70000U)
#define CAAM_SMVID_LS_PSIZ_SHIFT                 (16U)
#define CAAM_SMVID_LS_PSIZ(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_SMVID_LS_PSIZ_SHIFT)) & CAAM_SMVID_LS_PSIZ_MASK)
/*! @} */

/*! @name RVID - RTIC Version ID Register */
/*! @{ */

#define CAAM_RVID_RMNV_MASK                      (0xFFU)
#define CAAM_RVID_RMNV_SHIFT                     (0U)
#define CAAM_RVID_RMNV(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_RVID_RMNV_SHIFT)) & CAAM_RVID_RMNV_MASK)

#define CAAM_RVID_RMJV_MASK                      (0xFF00U)
#define CAAM_RVID_RMJV_SHIFT                     (8U)
#define CAAM_RVID_RMJV(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_RVID_RMJV_SHIFT)) & CAAM_RVID_RMJV_MASK)

#define CAAM_RVID_SHA_256_MASK                   (0x20000U)
#define CAAM_RVID_SHA_256_SHIFT                  (17U)
/*! SHA_256
 *  0b0..RTIC cannot use the SHA-256 hashing algorithm.
 *  0b1..RTIC can use the SHA-256 hashing algorithm.
 */
#define CAAM_RVID_SHA_256(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_RVID_SHA_256_SHIFT)) & CAAM_RVID_SHA_256_MASK)

#define CAAM_RVID_SHA_512_MASK                   (0x80000U)
#define CAAM_RVID_SHA_512_SHIFT                  (19U)
/*! SHA_512
 *  0b0..RTIC cannot use the SHA-512 hashing algorithm.
 *  0b1..RTIC can use the SHA-512 hashing algorithm.
 */
#define CAAM_RVID_SHA_512(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_RVID_SHA_512_SHIFT)) & CAAM_RVID_SHA_512_MASK)

#define CAAM_RVID_MA_MASK                        (0x1000000U)
#define CAAM_RVID_MA_SHIFT                       (24U)
#define CAAM_RVID_MA(x)                          (((uint32_t)(((uint32_t)(x)) << CAAM_RVID_MA_SHIFT)) & CAAM_RVID_MA_MASK)

#define CAAM_RVID_MB_MASK                        (0x2000000U)
#define CAAM_RVID_MB_SHIFT                       (25U)
#define CAAM_RVID_MB(x)                          (((uint32_t)(((uint32_t)(x)) << CAAM_RVID_MB_SHIFT)) & CAAM_RVID_MB_MASK)

#define CAAM_RVID_MC_MASK                        (0x4000000U)
#define CAAM_RVID_MC_SHIFT                       (26U)
#define CAAM_RVID_MC(x)                          (((uint32_t)(((uint32_t)(x)) << CAAM_RVID_MC_SHIFT)) & CAAM_RVID_MC_MASK)

#define CAAM_RVID_MD_MASK                        (0x8000000U)
#define CAAM_RVID_MD_SHIFT                       (27U)
#define CAAM_RVID_MD(x)                          (((uint32_t)(((uint32_t)(x)) << CAAM_RVID_MD_SHIFT)) & CAAM_RVID_MD_MASK)
/*! @} */

/*! @name CCBVID - CHA Cluster Block Version ID Register */
/*! @{ */

#define CAAM_CCBVID_AMNV_MASK                    (0xFFU)
#define CAAM_CCBVID_AMNV_SHIFT                   (0U)
#define CAAM_CCBVID_AMNV(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_CCBVID_AMNV_SHIFT)) & CAAM_CCBVID_AMNV_MASK)

#define CAAM_CCBVID_AMJV_MASK                    (0xFF00U)
#define CAAM_CCBVID_AMJV_SHIFT                   (8U)
#define CAAM_CCBVID_AMJV(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_CCBVID_AMJV_SHIFT)) & CAAM_CCBVID_AMJV_MASK)

#define CAAM_CCBVID_CAAM_ERA_MASK                (0xFF000000U)
#define CAAM_CCBVID_CAAM_ERA_SHIFT               (24U)
#define CAAM_CCBVID_CAAM_ERA(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CCBVID_CAAM_ERA_SHIFT)) & CAAM_CCBVID_CAAM_ERA_MASK)
/*! @} */

/*! @name CHAVID_MS - CHA Version ID Register, most-significant half */
/*! @{ */

#define CAAM_CHAVID_MS_CRCVID_MASK               (0xFU)
#define CAAM_CHAVID_MS_CRCVID_SHIFT              (0U)
#define CAAM_CHAVID_MS_CRCVID(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_CHAVID_MS_CRCVID_SHIFT)) & CAAM_CHAVID_MS_CRCVID_MASK)

#define CAAM_CHAVID_MS_SNW9VID_MASK              (0xF0U)
#define CAAM_CHAVID_MS_SNW9VID_SHIFT             (4U)
#define CAAM_CHAVID_MS_SNW9VID(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_CHAVID_MS_SNW9VID_SHIFT)) & CAAM_CHAVID_MS_SNW9VID_MASK)

#define CAAM_CHAVID_MS_ZEVID_MASK                (0xF00U)
#define CAAM_CHAVID_MS_ZEVID_SHIFT               (8U)
#define CAAM_CHAVID_MS_ZEVID(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CHAVID_MS_ZEVID_SHIFT)) & CAAM_CHAVID_MS_ZEVID_MASK)

#define CAAM_CHAVID_MS_ZAVID_MASK                (0xF000U)
#define CAAM_CHAVID_MS_ZAVID_SHIFT               (12U)
#define CAAM_CHAVID_MS_ZAVID(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CHAVID_MS_ZAVID_SHIFT)) & CAAM_CHAVID_MS_ZAVID_MASK)

#define CAAM_CHAVID_MS_DECOVID_MASK              (0xF000000U)
#define CAAM_CHAVID_MS_DECOVID_SHIFT             (24U)
#define CAAM_CHAVID_MS_DECOVID(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_CHAVID_MS_DECOVID_SHIFT)) & CAAM_CHAVID_MS_DECOVID_MASK)

#define CAAM_CHAVID_MS_JRVID_MASK                (0xF0000000U)
#define CAAM_CHAVID_MS_JRVID_SHIFT               (28U)
#define CAAM_CHAVID_MS_JRVID(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CHAVID_MS_JRVID_SHIFT)) & CAAM_CHAVID_MS_JRVID_MASK)
/*! @} */

/*! @name CHAVID_LS - CHA Version ID Register, least-significant half */
/*! @{ */

#define CAAM_CHAVID_LS_AESVID_MASK               (0xFU)
#define CAAM_CHAVID_LS_AESVID_SHIFT              (0U)
/*! AESVID
 *  0b0011..Low-power AESA, implementing ECB, CBC, CBC-CS2, CFB128, OFB, CTR, CCM, CMAC, XCBC-MAC, and GCM modes
 *  0b0100..High-performance AESA, implementing ECB, CBC, CBC-CS2, CFB128, OFB, CTR, CCM, CMAC, XCBC-MAC, CBCXCBC, CTRXCBC, XTS, and GCM modes
 */
#define CAAM_CHAVID_LS_AESVID(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_CHAVID_LS_AESVID_SHIFT)) & CAAM_CHAVID_LS_AESVID_MASK)

#define CAAM_CHAVID_LS_DESVID_MASK               (0xF0U)
#define CAAM_CHAVID_LS_DESVID_SHIFT              (4U)
#define CAAM_CHAVID_LS_DESVID(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_CHAVID_LS_DESVID_SHIFT)) & CAAM_CHAVID_LS_DESVID_MASK)

#define CAAM_CHAVID_LS_MDVID_MASK                (0xF000U)
#define CAAM_CHAVID_LS_MDVID_SHIFT               (12U)
/*! MDVID
 *  0b0000..Low-power MDHA, with SHA-1, SHA-256, SHA 224, MD5 and HMAC
 *  0b0001..Low-power MDHA, with SHA-1, SHA-256, SHA 224, SHA-512, SHA-512/224, SHA-512/256, SHA-384, MD5 and HMAC
 *  0b0010..Medium-performance MDHA, with SHA-1, SHA-256, SHA 224, SHA-512, SHA-512/224, SHA-512/256, SHA-384, MD5, HMAC & SMAC
 *  0b0011..High-performance MDHA, with SHA-1, SHA-256, SHA 224, SHA-512, SHA-512/224, SHA-512/256, SHA-384, MD5, HMAC & SMAC
 */
#define CAAM_CHAVID_LS_MDVID(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CHAVID_LS_MDVID_SHIFT)) & CAAM_CHAVID_LS_MDVID_MASK)

#define CAAM_CHAVID_LS_RNGVID_MASK               (0xF0000U)
#define CAAM_CHAVID_LS_RNGVID_SHIFT              (16U)
/*! RNGVID
 *  0b0010..RNGB
 *  0b0100..RNG4
 */
#define CAAM_CHAVID_LS_RNGVID(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_CHAVID_LS_RNGVID_SHIFT)) & CAAM_CHAVID_LS_RNGVID_MASK)

#define CAAM_CHAVID_LS_SNW8VID_MASK              (0xF00000U)
#define CAAM_CHAVID_LS_SNW8VID_SHIFT             (20U)
#define CAAM_CHAVID_LS_SNW8VID(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_CHAVID_LS_SNW8VID_SHIFT)) & CAAM_CHAVID_LS_SNW8VID_MASK)

#define CAAM_CHAVID_LS_KASVID_MASK               (0xF000000U)
#define CAAM_CHAVID_LS_KASVID_SHIFT              (24U)
#define CAAM_CHAVID_LS_KASVID(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_CHAVID_LS_KASVID_SHIFT)) & CAAM_CHAVID_LS_KASVID_MASK)

#define CAAM_CHAVID_LS_PKVID_MASK                (0xF0000000U)
#define CAAM_CHAVID_LS_PKVID_SHIFT               (28U)
/*! PKVID
 *  0b0000..PKHA-XT (32-bit); minimum modulus five bytes
 *  0b0001..PKHA-SD (32-bit)
 *  0b0010..PKHA-SD (64-bit)
 *  0b0011..PKHA-SD (128-bit)
 */
#define CAAM_CHAVID_LS_PKVID(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CHAVID_LS_PKVID_SHIFT)) & CAAM_CHAVID_LS_PKVID_MASK)
/*! @} */

/*! @name CHANUM_MS - CHA Number Register, most-significant half */
/*! @{ */

#define CAAM_CHANUM_MS_CRCNUM_MASK               (0xFU)
#define CAAM_CHANUM_MS_CRCNUM_SHIFT              (0U)
#define CAAM_CHANUM_MS_CRCNUM(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_CHANUM_MS_CRCNUM_SHIFT)) & CAAM_CHANUM_MS_CRCNUM_MASK)

#define CAAM_CHANUM_MS_SNW9NUM_MASK              (0xF0U)
#define CAAM_CHANUM_MS_SNW9NUM_SHIFT             (4U)
#define CAAM_CHANUM_MS_SNW9NUM(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_CHANUM_MS_SNW9NUM_SHIFT)) & CAAM_CHANUM_MS_SNW9NUM_MASK)

#define CAAM_CHANUM_MS_ZENUM_MASK                (0xF00U)
#define CAAM_CHANUM_MS_ZENUM_SHIFT               (8U)
#define CAAM_CHANUM_MS_ZENUM(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CHANUM_MS_ZENUM_SHIFT)) & CAAM_CHANUM_MS_ZENUM_MASK)

#define CAAM_CHANUM_MS_ZANUM_MASK                (0xF000U)
#define CAAM_CHANUM_MS_ZANUM_SHIFT               (12U)
#define CAAM_CHANUM_MS_ZANUM(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CHANUM_MS_ZANUM_SHIFT)) & CAAM_CHANUM_MS_ZANUM_MASK)

#define CAAM_CHANUM_MS_DECONUM_MASK              (0xF000000U)
#define CAAM_CHANUM_MS_DECONUM_SHIFT             (24U)
#define CAAM_CHANUM_MS_DECONUM(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_CHANUM_MS_DECONUM_SHIFT)) & CAAM_CHANUM_MS_DECONUM_MASK)

#define CAAM_CHANUM_MS_JRNUM_MASK                (0xF0000000U)
#define CAAM_CHANUM_MS_JRNUM_SHIFT               (28U)
#define CAAM_CHANUM_MS_JRNUM(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CHANUM_MS_JRNUM_SHIFT)) & CAAM_CHANUM_MS_JRNUM_MASK)
/*! @} */

/*! @name CHANUM_LS - CHA Number Register, least-significant half */
/*! @{ */

#define CAAM_CHANUM_LS_AESNUM_MASK               (0xFU)
#define CAAM_CHANUM_LS_AESNUM_SHIFT              (0U)
#define CAAM_CHANUM_LS_AESNUM(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_CHANUM_LS_AESNUM_SHIFT)) & CAAM_CHANUM_LS_AESNUM_MASK)

#define CAAM_CHANUM_LS_DESNUM_MASK               (0xF0U)
#define CAAM_CHANUM_LS_DESNUM_SHIFT              (4U)
#define CAAM_CHANUM_LS_DESNUM(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_CHANUM_LS_DESNUM_SHIFT)) & CAAM_CHANUM_LS_DESNUM_MASK)

#define CAAM_CHANUM_LS_ARC4NUM_MASK              (0xF00U)
#define CAAM_CHANUM_LS_ARC4NUM_SHIFT             (8U)
#define CAAM_CHANUM_LS_ARC4NUM(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_CHANUM_LS_ARC4NUM_SHIFT)) & CAAM_CHANUM_LS_ARC4NUM_MASK)

#define CAAM_CHANUM_LS_MDNUM_MASK                (0xF000U)
#define CAAM_CHANUM_LS_MDNUM_SHIFT               (12U)
#define CAAM_CHANUM_LS_MDNUM(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CHANUM_LS_MDNUM_SHIFT)) & CAAM_CHANUM_LS_MDNUM_MASK)

#define CAAM_CHANUM_LS_RNGNUM_MASK               (0xF0000U)
#define CAAM_CHANUM_LS_RNGNUM_SHIFT              (16U)
#define CAAM_CHANUM_LS_RNGNUM(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_CHANUM_LS_RNGNUM_SHIFT)) & CAAM_CHANUM_LS_RNGNUM_MASK)

#define CAAM_CHANUM_LS_SNW8NUM_MASK              (0xF00000U)
#define CAAM_CHANUM_LS_SNW8NUM_SHIFT             (20U)
#define CAAM_CHANUM_LS_SNW8NUM(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_CHANUM_LS_SNW8NUM_SHIFT)) & CAAM_CHANUM_LS_SNW8NUM_MASK)

#define CAAM_CHANUM_LS_KASNUM_MASK               (0xF000000U)
#define CAAM_CHANUM_LS_KASNUM_SHIFT              (24U)
#define CAAM_CHANUM_LS_KASNUM(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_CHANUM_LS_KASNUM_SHIFT)) & CAAM_CHANUM_LS_KASNUM_MASK)

#define CAAM_CHANUM_LS_PKNUM_MASK                (0xF0000000U)
#define CAAM_CHANUM_LS_PKNUM_SHIFT               (28U)
#define CAAM_CHANUM_LS_PKNUM(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CHANUM_LS_PKNUM_SHIFT)) & CAAM_CHANUM_LS_PKNUM_MASK)
/*! @} */

/*! @name IRBAR_JR - Input Ring Base Address Register for Job Ring 0..Input Ring Base Address Register for Job Ring 3 */
/*! @{ */

#define CAAM_IRBAR_JR_IRBA_MASK                  (0xFFFFFFFFFU)
#define CAAM_IRBAR_JR_IRBA_SHIFT                 (0U)
#define CAAM_IRBAR_JR_IRBA(x)                    (((uint64_t)(((uint64_t)(x)) << CAAM_IRBAR_JR_IRBA_SHIFT)) & CAAM_IRBAR_JR_IRBA_MASK)
/*! @} */

/* The count of CAAM_IRBAR_JR */
#define CAAM_IRBAR_JR_COUNT                      (4U)

/*! @name IRSR_JR - Input Ring Size Register for Job Ring 0..Input Ring Size Register for Job Ring 3 */
/*! @{ */

#define CAAM_IRSR_JR_IRS_MASK                    (0x3FFU)
#define CAAM_IRSR_JR_IRS_SHIFT                   (0U)
#define CAAM_IRSR_JR_IRS(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_IRSR_JR_IRS_SHIFT)) & CAAM_IRSR_JR_IRS_MASK)
/*! @} */

/* The count of CAAM_IRSR_JR */
#define CAAM_IRSR_JR_COUNT                       (4U)

/*! @name IRSAR_JR - Input Ring Slots Available Register for Job Ring 0..Input Ring Slots Available Register for Job Ring 3 */
/*! @{ */

#define CAAM_IRSAR_JR_IRSA_MASK                  (0x3FFU)
#define CAAM_IRSAR_JR_IRSA_SHIFT                 (0U)
#define CAAM_IRSAR_JR_IRSA(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_IRSAR_JR_IRSA_SHIFT)) & CAAM_IRSAR_JR_IRSA_MASK)
/*! @} */

/* The count of CAAM_IRSAR_JR */
#define CAAM_IRSAR_JR_COUNT                      (4U)

/*! @name IRJAR_JR - Input Ring Jobs Added Register for Job Ring0..Input Ring Jobs Added Register for Job Ring3 */
/*! @{ */

#define CAAM_IRJAR_JR_IRJA_MASK                  (0x3FFU)
#define CAAM_IRJAR_JR_IRJA_SHIFT                 (0U)
#define CAAM_IRJAR_JR_IRJA(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_IRJAR_JR_IRJA_SHIFT)) & CAAM_IRJAR_JR_IRJA_MASK)
/*! @} */

/* The count of CAAM_IRJAR_JR */
#define CAAM_IRJAR_JR_COUNT                      (4U)

/*! @name ORBAR_JR - Output Ring Base Address Register for Job Ring 0..Output Ring Base Address Register for Job Ring 3 */
/*! @{ */

#define CAAM_ORBAR_JR_ORBA_MASK                  (0xFFFFFFFFFU)
#define CAAM_ORBAR_JR_ORBA_SHIFT                 (0U)
#define CAAM_ORBAR_JR_ORBA(x)                    (((uint64_t)(((uint64_t)(x)) << CAAM_ORBAR_JR_ORBA_SHIFT)) & CAAM_ORBAR_JR_ORBA_MASK)
/*! @} */

/* The count of CAAM_ORBAR_JR */
#define CAAM_ORBAR_JR_COUNT                      (4U)

/*! @name ORSR_JR - Output Ring Size Register for Job Ring 0..Output Ring Size Register for Job Ring 3 */
/*! @{ */

#define CAAM_ORSR_JR_ORS_MASK                    (0x3FFU)
#define CAAM_ORSR_JR_ORS_SHIFT                   (0U)
#define CAAM_ORSR_JR_ORS(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_ORSR_JR_ORS_SHIFT)) & CAAM_ORSR_JR_ORS_MASK)
/*! @} */

/* The count of CAAM_ORSR_JR */
#define CAAM_ORSR_JR_COUNT                       (4U)

/*! @name ORJRR_JR - Output Ring Jobs Removed Register for Job Ring 0..Output Ring Jobs Removed Register for Job Ring 3 */
/*! @{ */

#define CAAM_ORJRR_JR_ORJR_MASK                  (0x3FFU)
#define CAAM_ORJRR_JR_ORJR_SHIFT                 (0U)
#define CAAM_ORJRR_JR_ORJR(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_ORJRR_JR_ORJR_SHIFT)) & CAAM_ORJRR_JR_ORJR_MASK)
/*! @} */

/* The count of CAAM_ORJRR_JR */
#define CAAM_ORJRR_JR_COUNT                      (4U)

/*! @name ORSFR_JR - Output Ring Slots Full Register for Job Ring 0..Output Ring Slots Full Register for Job Ring 3 */
/*! @{ */

#define CAAM_ORSFR_JR_ORSF_MASK                  (0x3FFU)
#define CAAM_ORSFR_JR_ORSF_SHIFT                 (0U)
#define CAAM_ORSFR_JR_ORSF(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_ORSFR_JR_ORSF_SHIFT)) & CAAM_ORSFR_JR_ORSF_MASK)
/*! @} */

/* The count of CAAM_ORSFR_JR */
#define CAAM_ORSFR_JR_COUNT                      (4U)

/*! @name JRSTAR_JR - Job Ring Output Status Register for Job Ring 0..Job Ring Output Status Register for Job Ring 3 */
/*! @{ */

#define CAAM_JRSTAR_JR_SSED_MASK                 (0xFFFFFFFU)
#define CAAM_JRSTAR_JR_SSED_SHIFT                (0U)
#define CAAM_JRSTAR_JR_SSED(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_JRSTAR_JR_SSED_SHIFT)) & CAAM_JRSTAR_JR_SSED_MASK)

#define CAAM_JRSTAR_JR_SSRC_MASK                 (0xF0000000U)
#define CAAM_JRSTAR_JR_SSRC_SHIFT                (28U)
/*! SSRC
 *  0b0000..No Status Source (No Error or Status Reported)
 *  0b0001..Reserved
 *  0b0010..CCB Status Source (CCB Error Reported)
 *  0b0011..Jump Halt User Status Source (User-Provided Status Reported)
 *  0b0100..DECO Status Source (DECO Error Reported)
 *  0b0101..Reserved
 *  0b0110..Job Ring Status Source (Job Ring Error Reported)
 *  0b0111..Jump Halt Condition Codes (Condition Code Status Reported)
 */
#define CAAM_JRSTAR_JR_SSRC(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_JRSTAR_JR_SSRC_SHIFT)) & CAAM_JRSTAR_JR_SSRC_MASK)
/*! @} */

/* The count of CAAM_JRSTAR_JR */
#define CAAM_JRSTAR_JR_COUNT                     (4U)

/*! @name JRINTR_JR - Job Ring Interrupt Status Register for Job Ring 0..Job Ring Interrupt Status Register for Job Ring 3 */
/*! @{ */

#define CAAM_JRINTR_JR_JRI_MASK                  (0x1U)
#define CAAM_JRINTR_JR_JRI_SHIFT                 (0U)
#define CAAM_JRINTR_JR_JRI(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_JRINTR_JR_JRI_SHIFT)) & CAAM_JRINTR_JR_JRI_MASK)

#define CAAM_JRINTR_JR_JRE_MASK                  (0x2U)
#define CAAM_JRINTR_JR_JRE_SHIFT                 (1U)
#define CAAM_JRINTR_JR_JRE(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_JRINTR_JR_JRE_SHIFT)) & CAAM_JRINTR_JR_JRE_MASK)

#define CAAM_JRINTR_JR_HALT_MASK                 (0xCU)
#define CAAM_JRINTR_JR_HALT_SHIFT                (2U)
#define CAAM_JRINTR_JR_HALT(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_JRINTR_JR_HALT_SHIFT)) & CAAM_JRINTR_JR_HALT_MASK)

#define CAAM_JRINTR_JR_ENTER_FAIL_MASK           (0x10U)
#define CAAM_JRINTR_JR_ENTER_FAIL_SHIFT          (4U)
#define CAAM_JRINTR_JR_ENTER_FAIL(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_JRINTR_JR_ENTER_FAIL_SHIFT)) & CAAM_JRINTR_JR_ENTER_FAIL_MASK)

#define CAAM_JRINTR_JR_EXIT_FAIL_MASK            (0x20U)
#define CAAM_JRINTR_JR_EXIT_FAIL_SHIFT           (5U)
#define CAAM_JRINTR_JR_EXIT_FAIL(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_JRINTR_JR_EXIT_FAIL_SHIFT)) & CAAM_JRINTR_JR_EXIT_FAIL_MASK)

#define CAAM_JRINTR_JR_ERR_TYPE_MASK             (0x1F00U)
#define CAAM_JRINTR_JR_ERR_TYPE_SHIFT            (8U)
/*! ERR_TYPE
 *  0b00001..Error writing status to Output Ring
 *  0b00011..Bad input ring base address (not on a 4-byte boundary).
 *  0b00100..Bad output ring base address (not on a 4-byte boundary).
 *  0b00101..Invalid write to Input Ring Base Address Register or Input Ring Size Register. Can be written when
 *           there are no jobs in the input ring or when the Job Ring is halted. These are fatal and will likely
 *           result in not being able to get all jobs out into the output ring for processing by software. Resetting
 *           the job ring will almost certainly be necessary.
 *  0b00110..Invalid write to Output Ring Base Address Register or Output Ring Size Register. Can be written when
 *           there are no jobs in the output ring and no jobs from this queue are already processing in CAAM (in
 *           the holding tanks or DECOs), or when the Job Ring is halted.
 *  0b00111..Job Ring reset released before Job Ring is halted.
 *  0b01000..Removed too many jobs (ORJRR larger than ORSFR).
 *  0b01001..Added too many jobs (IRJAR larger than IRSAR).
 *  0b01010..Writing ORSF > ORS In these error cases the write is ignored, the interrupt is asserted (unless
 *           masked) and the error bit and error_type fields are set in the Job Ring Interrupt Status Register.
 *  0b01011..Writing IRSA > IRS
 *  0b01100..Writing ORWI > ORS in bytes
 *  0b01101..Writing IRRI > IRS in bytes
 *  0b01110..Writing IRSA when ring is active
 *  0b01111..Writing IRRI when ring is active
 *  0b10000..Writing ORSF when ring is active
 *  0b10001..Writing ORWI when ring is active
 */
#define CAAM_JRINTR_JR_ERR_TYPE(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_JRINTR_JR_ERR_TYPE_SHIFT)) & CAAM_JRINTR_JR_ERR_TYPE_MASK)

#define CAAM_JRINTR_JR_ERR_ORWI_MASK             (0x3FFF0000U)
#define CAAM_JRINTR_JR_ERR_ORWI_SHIFT            (16U)
#define CAAM_JRINTR_JR_ERR_ORWI(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_JRINTR_JR_ERR_ORWI_SHIFT)) & CAAM_JRINTR_JR_ERR_ORWI_MASK)
/*! @} */

/* The count of CAAM_JRINTR_JR */
#define CAAM_JRINTR_JR_COUNT                     (4U)

/*! @name JRCFGR_JR_MS - Job Ring Configuration Register for Job Ring 0, most-significant half..Job Ring Configuration Register for Job Ring 3, most-significant half */
/*! @{ */

#define CAAM_JRCFGR_JR_MS_MBSI_MASK              (0x1U)
#define CAAM_JRCFGR_JR_MS_MBSI_SHIFT             (0U)
#define CAAM_JRCFGR_JR_MS_MBSI(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_JRCFGR_JR_MS_MBSI_SHIFT)) & CAAM_JRCFGR_JR_MS_MBSI_MASK)

#define CAAM_JRCFGR_JR_MS_MHWSI_MASK             (0x2U)
#define CAAM_JRCFGR_JR_MS_MHWSI_SHIFT            (1U)
#define CAAM_JRCFGR_JR_MS_MHWSI(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_JRCFGR_JR_MS_MHWSI_SHIFT)) & CAAM_JRCFGR_JR_MS_MHWSI_MASK)

#define CAAM_JRCFGR_JR_MS_MWSI_MASK              (0x4U)
#define CAAM_JRCFGR_JR_MS_MWSI_SHIFT             (2U)
#define CAAM_JRCFGR_JR_MS_MWSI(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_JRCFGR_JR_MS_MWSI_SHIFT)) & CAAM_JRCFGR_JR_MS_MWSI_MASK)

#define CAAM_JRCFGR_JR_MS_CBSI_MASK              (0x10U)
#define CAAM_JRCFGR_JR_MS_CBSI_SHIFT             (4U)
#define CAAM_JRCFGR_JR_MS_CBSI(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_JRCFGR_JR_MS_CBSI_SHIFT)) & CAAM_JRCFGR_JR_MS_CBSI_MASK)

#define CAAM_JRCFGR_JR_MS_CHWSI_MASK             (0x20U)
#define CAAM_JRCFGR_JR_MS_CHWSI_SHIFT            (5U)
#define CAAM_JRCFGR_JR_MS_CHWSI(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_JRCFGR_JR_MS_CHWSI_SHIFT)) & CAAM_JRCFGR_JR_MS_CHWSI_MASK)

#define CAAM_JRCFGR_JR_MS_CWSI_MASK              (0x40U)
#define CAAM_JRCFGR_JR_MS_CWSI_SHIFT             (6U)
#define CAAM_JRCFGR_JR_MS_CWSI(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_JRCFGR_JR_MS_CWSI_SHIFT)) & CAAM_JRCFGR_JR_MS_CWSI_MASK)

#define CAAM_JRCFGR_JR_MS_MBSO_MASK              (0x100U)
#define CAAM_JRCFGR_JR_MS_MBSO_SHIFT             (8U)
#define CAAM_JRCFGR_JR_MS_MBSO(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_JRCFGR_JR_MS_MBSO_SHIFT)) & CAAM_JRCFGR_JR_MS_MBSO_MASK)

#define CAAM_JRCFGR_JR_MS_MHWSO_MASK             (0x200U)
#define CAAM_JRCFGR_JR_MS_MHWSO_SHIFT            (9U)
#define CAAM_JRCFGR_JR_MS_MHWSO(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_JRCFGR_JR_MS_MHWSO_SHIFT)) & CAAM_JRCFGR_JR_MS_MHWSO_MASK)

#define CAAM_JRCFGR_JR_MS_MWSO_MASK              (0x400U)
#define CAAM_JRCFGR_JR_MS_MWSO_SHIFT             (10U)
#define CAAM_JRCFGR_JR_MS_MWSO(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_JRCFGR_JR_MS_MWSO_SHIFT)) & CAAM_JRCFGR_JR_MS_MWSO_MASK)

#define CAAM_JRCFGR_JR_MS_CBSO_MASK              (0x1000U)
#define CAAM_JRCFGR_JR_MS_CBSO_SHIFT             (12U)
#define CAAM_JRCFGR_JR_MS_CBSO(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_JRCFGR_JR_MS_CBSO_SHIFT)) & CAAM_JRCFGR_JR_MS_CBSO_MASK)

#define CAAM_JRCFGR_JR_MS_CHWSO_MASK             (0x2000U)
#define CAAM_JRCFGR_JR_MS_CHWSO_SHIFT            (13U)
#define CAAM_JRCFGR_JR_MS_CHWSO(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_JRCFGR_JR_MS_CHWSO_SHIFT)) & CAAM_JRCFGR_JR_MS_CHWSO_MASK)

#define CAAM_JRCFGR_JR_MS_CWSO_MASK              (0x4000U)
#define CAAM_JRCFGR_JR_MS_CWSO_SHIFT             (14U)
#define CAAM_JRCFGR_JR_MS_CWSO(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_JRCFGR_JR_MS_CWSO_SHIFT)) & CAAM_JRCFGR_JR_MS_CWSO_MASK)

#define CAAM_JRCFGR_JR_MS_DMBS_MASK              (0x10000U)
#define CAAM_JRCFGR_JR_MS_DMBS_SHIFT             (16U)
#define CAAM_JRCFGR_JR_MS_DMBS(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_JRCFGR_JR_MS_DMBS_SHIFT)) & CAAM_JRCFGR_JR_MS_DMBS_MASK)

#define CAAM_JRCFGR_JR_MS_PEO_MASK               (0x20000U)
#define CAAM_JRCFGR_JR_MS_PEO_SHIFT              (17U)
#define CAAM_JRCFGR_JR_MS_PEO(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_JRCFGR_JR_MS_PEO_SHIFT)) & CAAM_JRCFGR_JR_MS_PEO_MASK)

#define CAAM_JRCFGR_JR_MS_DWSO_MASK              (0x40000U)
#define CAAM_JRCFGR_JR_MS_DWSO_SHIFT             (18U)
#define CAAM_JRCFGR_JR_MS_DWSO(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_JRCFGR_JR_MS_DWSO_SHIFT)) & CAAM_JRCFGR_JR_MS_DWSO_MASK)

#define CAAM_JRCFGR_JR_MS_FAIL_MODE_MASK         (0x20000000U)
#define CAAM_JRCFGR_JR_MS_FAIL_MODE_SHIFT        (29U)
#define CAAM_JRCFGR_JR_MS_FAIL_MODE(x)           (((uint32_t)(((uint32_t)(x)) << CAAM_JRCFGR_JR_MS_FAIL_MODE_SHIFT)) & CAAM_JRCFGR_JR_MS_FAIL_MODE_MASK)

#define CAAM_JRCFGR_JR_MS_INCL_SEQ_OUT_MASK      (0x40000000U)
#define CAAM_JRCFGR_JR_MS_INCL_SEQ_OUT_SHIFT     (30U)
#define CAAM_JRCFGR_JR_MS_INCL_SEQ_OUT(x)        (((uint32_t)(((uint32_t)(x)) << CAAM_JRCFGR_JR_MS_INCL_SEQ_OUT_SHIFT)) & CAAM_JRCFGR_JR_MS_INCL_SEQ_OUT_MASK)
/*! @} */

/* The count of CAAM_JRCFGR_JR_MS */
#define CAAM_JRCFGR_JR_MS_COUNT                  (4U)

/*! @name JRCFGR_JR_LS - Job Ring Configuration Register for Job Ring 0, least-significant half..Job Ring Configuration Register for Job Ring 3, least-significant half */
/*! @{ */

#define CAAM_JRCFGR_JR_LS_IMSK_MASK              (0x1U)
#define CAAM_JRCFGR_JR_LS_IMSK_SHIFT             (0U)
/*! IMSK
 *  0b0..Interrupt enabled.
 *  0b1..Interrupt masked.
 */
#define CAAM_JRCFGR_JR_LS_IMSK(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_JRCFGR_JR_LS_IMSK_SHIFT)) & CAAM_JRCFGR_JR_LS_IMSK_MASK)

#define CAAM_JRCFGR_JR_LS_ICEN_MASK              (0x2U)
#define CAAM_JRCFGR_JR_LS_ICEN_SHIFT             (1U)
/*! ICEN
 *  0b0..Interrupt coalescing is disabled. If the IMSK bit is cleared, an interrupt is asserted whenever a job is
 *       written to the output ring. ICDCT is ignored. Note that if software removes one or more jobs and clears
 *       the interrupt but the output rings slots full is still greater than 0 (ORSF > 0), then the interrupt will
 *       clear but reassert on the next clock cycle.
 *  0b1..Interrupt coalescing is enabled. If the IMSK bit is cleared, an interrupt is asserted whenever the
 *       threshold number of frames is reached (ICDCT) or when the threshold timer expires (ICTT). Note that if software
 *       removes one or more jobs and clears the interrupt but the interrupt coalescing threshold is still met
 *       (ORSF >= ICDCT), then the interrupt will clear but reassert on the next clock cycle.
 */
#define CAAM_JRCFGR_JR_LS_ICEN(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_JRCFGR_JR_LS_ICEN_SHIFT)) & CAAM_JRCFGR_JR_LS_ICEN_MASK)

#define CAAM_JRCFGR_JR_LS_ICDCT_MASK             (0xFF00U)
#define CAAM_JRCFGR_JR_LS_ICDCT_SHIFT            (8U)
#define CAAM_JRCFGR_JR_LS_ICDCT(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_JRCFGR_JR_LS_ICDCT_SHIFT)) & CAAM_JRCFGR_JR_LS_ICDCT_MASK)

#define CAAM_JRCFGR_JR_LS_ICTT_MASK              (0xFFFF0000U)
#define CAAM_JRCFGR_JR_LS_ICTT_SHIFT             (16U)
#define CAAM_JRCFGR_JR_LS_ICTT(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_JRCFGR_JR_LS_ICTT_SHIFT)) & CAAM_JRCFGR_JR_LS_ICTT_MASK)
/*! @} */

/* The count of CAAM_JRCFGR_JR_LS */
#define CAAM_JRCFGR_JR_LS_COUNT                  (4U)

/*! @name IRRIR_JR - Input Ring Read Index Register for Job Ring 0..Input Ring Read Index Register for Job Ring 3 */
/*! @{ */

#define CAAM_IRRIR_JR_IRRI_MASK                  (0x1FFFU)
#define CAAM_IRRIR_JR_IRRI_SHIFT                 (0U)
#define CAAM_IRRIR_JR_IRRI(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_IRRIR_JR_IRRI_SHIFT)) & CAAM_IRRIR_JR_IRRI_MASK)
/*! @} */

/* The count of CAAM_IRRIR_JR */
#define CAAM_IRRIR_JR_COUNT                      (4U)

/*! @name ORWIR_JR - Output Ring Write Index Register for Job Ring 0..Output Ring Write Index Register for Job Ring 3 */
/*! @{ */

#define CAAM_ORWIR_JR_ORWI_MASK                  (0x3FFFU)
#define CAAM_ORWIR_JR_ORWI_SHIFT                 (0U)
#define CAAM_ORWIR_JR_ORWI(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_ORWIR_JR_ORWI_SHIFT)) & CAAM_ORWIR_JR_ORWI_MASK)
/*! @} */

/* The count of CAAM_ORWIR_JR */
#define CAAM_ORWIR_JR_COUNT                      (4U)

/*! @name JRCR_JR - Job Ring Command Register for Job Ring 0..Job Ring Command Register for Job Ring 3 */
/*! @{ */

#define CAAM_JRCR_JR_RESET_MASK                  (0x1U)
#define CAAM_JRCR_JR_RESET_SHIFT                 (0U)
#define CAAM_JRCR_JR_RESET(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_JRCR_JR_RESET_SHIFT)) & CAAM_JRCR_JR_RESET_MASK)

#define CAAM_JRCR_JR_PARK_MASK                   (0x2U)
#define CAAM_JRCR_JR_PARK_SHIFT                  (1U)
#define CAAM_JRCR_JR_PARK(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_JRCR_JR_PARK_SHIFT)) & CAAM_JRCR_JR_PARK_MASK)
/*! @} */

/* The count of CAAM_JRCR_JR */
#define CAAM_JRCR_JR_COUNT                       (4U)

/*! @name JRAAV - Job Ring 0 Address-Array Valid Register..Job Ring 3 Address-Array Valid Register */
/*! @{ */

#define CAAM_JRAAV_V0_MASK                       (0x1U)
#define CAAM_JRAAV_V0_SHIFT                      (0U)
#define CAAM_JRAAV_V0(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_JRAAV_V0_SHIFT)) & CAAM_JRAAV_V0_MASK)

#define CAAM_JRAAV_V1_MASK                       (0x2U)
#define CAAM_JRAAV_V1_SHIFT                      (1U)
#define CAAM_JRAAV_V1(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_JRAAV_V1_SHIFT)) & CAAM_JRAAV_V1_MASK)

#define CAAM_JRAAV_V2_MASK                       (0x4U)
#define CAAM_JRAAV_V2_SHIFT                      (2U)
#define CAAM_JRAAV_V2(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_JRAAV_V2_SHIFT)) & CAAM_JRAAV_V2_MASK)

#define CAAM_JRAAV_V3_MASK                       (0x8U)
#define CAAM_JRAAV_V3_SHIFT                      (3U)
#define CAAM_JRAAV_V3(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_JRAAV_V3_SHIFT)) & CAAM_JRAAV_V3_MASK)

#define CAAM_JRAAV_BC_MASK                       (0x80000000U)
#define CAAM_JRAAV_BC_SHIFT                      (31U)
#define CAAM_JRAAV_BC(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_JRAAV_BC_SHIFT)) & CAAM_JRAAV_BC_MASK)
/*! @} */

/* The count of CAAM_JRAAV */
#define CAAM_JRAAV_COUNT                         (4U)

/*! @name JRAAA - Job Ring 0 Address-Array Address 0 Register..Job Ring 3 Address-Array Address 3 Register */
/*! @{ */

#define CAAM_JRAAA_JD_ADDR_MASK                  (0xFFFFFFFFFU)
#define CAAM_JRAAA_JD_ADDR_SHIFT                 (0U)
#define CAAM_JRAAA_JD_ADDR(x)                    (((uint64_t)(((uint64_t)(x)) << CAAM_JRAAA_JD_ADDR_SHIFT)) & CAAM_JRAAA_JD_ADDR_MASK)
/*! @} */

/* The count of CAAM_JRAAA */
#define CAAM_JRAAA_COUNT                         (4U)

/* The count of CAAM_JRAAA */
#define CAAM_JRAAA_COUNT2                        (4U)

/*! @name PX_SDID_JR - Partition 0 SDID register..Partition 15 SDID register */
/*! @{ */

#define CAAM_PX_SDID_JR_SDID_MASK                (0xFFFFU)
#define CAAM_PX_SDID_JR_SDID_SHIFT               (0U)
#define CAAM_PX_SDID_JR_SDID(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SDID_JR_SDID_SHIFT)) & CAAM_PX_SDID_JR_SDID_MASK)
/*! @} */

/* The count of CAAM_PX_SDID_JR */
#define CAAM_PX_SDID_JR_COUNT                    (4U)

/* The count of CAAM_PX_SDID_JR */
#define CAAM_PX_SDID_JR_COUNT2                   (16U)

/*! @name PX_SMAPR_JR - Secure Memory Access Permissions register */
/*! @{ */

#define CAAM_PX_SMAPR_JR_G1_READ_MASK            (0x1U)
#define CAAM_PX_SMAPR_JR_G1_READ_SHIFT           (0U)
/*! G1_READ
 *  0b0..Instruction fetches and reads are prohibited (except that Trusted Descriptor reads (if G1_TDO=1) and
 *       key-reads are always allowed, and exporting Secure Memory Blobs is allowed if G1_SMBLOB=1 or if done by a
 *       Trusted Descriptor and G1_TDO=1).
 *  0b1..Instruction fetches and reads are allowed (but exporting a Secure Memory Blob is prohibited if
 *       G1_SMBLOB=0 and the descriptor is not a Trusted Descriptor or if G1_TDO=0).
 */
#define CAAM_PX_SMAPR_JR_G1_READ(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_JR_G1_READ_SHIFT)) & CAAM_PX_SMAPR_JR_G1_READ_MASK)

#define CAAM_PX_SMAPR_JR_G1_WRITE_MASK           (0x2U)
#define CAAM_PX_SMAPR_JR_G1_WRITE_SHIFT          (1U)
/*! G1_WRITE
 *  0b0..Writes are prohibited (except that Trusted Descriptor writes are allowed, and importing Secure Memory
 *       Blobs is allowed if G1_SMBLOB=1 or if done by a Trusted Descriptor and G1_TDO=1).
 *  0b1..Writes are allowed (but importing a Secure Memory Blob is prohibited if G1_SMBLOB=0 and the descriptor is
 *       not a Trusted Descriptor or if G1_TDO=0).
 */
#define CAAM_PX_SMAPR_JR_G1_WRITE(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_JR_G1_WRITE_SHIFT)) & CAAM_PX_SMAPR_JR_G1_WRITE_MASK)

#define CAAM_PX_SMAPR_JR_G1_TDO_MASK             (0x4U)
#define CAAM_PX_SMAPR_JR_G1_TDO_SHIFT            (2U)
/*! G1_TDO
 *  0b0..Trusted Descriptors have the same access privileges as Job Descriptors
 *  0b1..Trusted Descriptors are allowed to override the other access permissions, i.e. they can export blobs from
 *       or import blobs to the partition and read from and write to the partition regardless of the G1_SMBLOB,
 *       G1_WRITE and G1_READ settings.
 */
#define CAAM_PX_SMAPR_JR_G1_TDO(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_JR_G1_TDO_SHIFT)) & CAAM_PX_SMAPR_JR_G1_TDO_MASK)

#define CAAM_PX_SMAPR_JR_G1_SMBLOB_MASK          (0x8U)
#define CAAM_PX_SMAPR_JR_G1_SMBLOB_SHIFT         (3U)
/*! G1_SMBLOB
 *  0b0..Exporting or importing Secure Memory Blobs is prohibited, unless done via a Trusted Descriptor and G1_TDO=1.
 *  0b1..Exporting or importing Secure Memory Blobs is allowed, regardless of the G1_READ and G1_WRITE settings.
 */
#define CAAM_PX_SMAPR_JR_G1_SMBLOB(x)            (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_JR_G1_SMBLOB_SHIFT)) & CAAM_PX_SMAPR_JR_G1_SMBLOB_MASK)

#define CAAM_PX_SMAPR_JR_G2_READ_MASK            (0x10U)
#define CAAM_PX_SMAPR_JR_G2_READ_SHIFT           (4U)
/*! G2_READ
 *  0b0..Instruction fetches and reads are prohibited (except that Trusted Descriptor reads (if G2_TDO=1) and
 *       key-reads are always allowed, and exporting Secure Memory Blobs is allowed if G2_SMBLOB=1 or if done by a
 *       Trusted Descriptor and G2_TDO=1).
 *  0b1..Instruction fetches and reads are allowed (but exporting a Secure Memory Blob is prohibited if
 *       G2_SMBLOB=0 and the descriptor is not a Trusted Descriptor or if G2_TDO=0).
 */
#define CAAM_PX_SMAPR_JR_G2_READ(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_JR_G2_READ_SHIFT)) & CAAM_PX_SMAPR_JR_G2_READ_MASK)

#define CAAM_PX_SMAPR_JR_G2_WRITE_MASK           (0x20U)
#define CAAM_PX_SMAPR_JR_G2_WRITE_SHIFT          (5U)
/*! G2_WRITE
 *  0b0..Writes are prohibited (except that Trusted Descriptor writes are allowed, and importing Secure Memory
 *       Blobs is allowed if G2_SMBLOB=1 or if done by a Trusted Descriptor and G2_TDO=1).
 *  0b1..Writes are allowed (but importing a Secure Memory Blob is prohibited if G2_SMBLOB=0 and the descriptor is
 *       not a Trusted Descriptor or if G2_TDO=0).
 */
#define CAAM_PX_SMAPR_JR_G2_WRITE(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_JR_G2_WRITE_SHIFT)) & CAAM_PX_SMAPR_JR_G2_WRITE_MASK)

#define CAAM_PX_SMAPR_JR_G2_TDO_MASK             (0x40U)
#define CAAM_PX_SMAPR_JR_G2_TDO_SHIFT            (6U)
/*! G2_TDO
 *  0b0..Trusted Descriptors have the same access privileges as Job Descriptors
 *  0b1..Trusted Descriptors are allowed to override the other access permissions, i.e. they can export blobs from
 *       or import blobs to the partition and read from and write to the partition regardless of the G2_SMBLOB,
 *       G2_WRITE and G2_READ settings.
 */
#define CAAM_PX_SMAPR_JR_G2_TDO(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_JR_G2_TDO_SHIFT)) & CAAM_PX_SMAPR_JR_G2_TDO_MASK)

#define CAAM_PX_SMAPR_JR_G2_SMBLOB_MASK          (0x80U)
#define CAAM_PX_SMAPR_JR_G2_SMBLOB_SHIFT         (7U)
/*! G2_SMBLOB
 *  0b0..Exporting or importing Secure Memory Blobs is prohibited, unless done via a Trusted Descriptor and G2_TDO=1.
 *  0b1..Exporting or importing Secure Memory Blobs is allowed, regardless of the G2_READ and G2_WRITE settings.
 */
#define CAAM_PX_SMAPR_JR_G2_SMBLOB(x)            (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_JR_G2_SMBLOB_SHIFT)) & CAAM_PX_SMAPR_JR_G2_SMBLOB_MASK)

#define CAAM_PX_SMAPR_JR_SMAG_LCK_MASK           (0x1000U)
#define CAAM_PX_SMAPR_JR_SMAG_LCK_SHIFT          (12U)
/*! SMAG_LCK
 *  0b0..The SMAG2JR register and SMAG1JR register are unlocked. The partition owner can change any writable bits of these registers.
 *  0b1..The SMAG2JR register and SMAG1JR register are locked. The SMAG2JR and SMAG1JR registers cannot be changed
 *       until the partition is de-allocated or a POR occurs.
 */
#define CAAM_PX_SMAPR_JR_SMAG_LCK(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_JR_SMAG_LCK_SHIFT)) & CAAM_PX_SMAPR_JR_SMAG_LCK_MASK)

#define CAAM_PX_SMAPR_JR_SMAP_LCK_MASK           (0x2000U)
#define CAAM_PX_SMAPR_JR_SMAP_LCK_SHIFT          (13U)
/*! SMAP_LCK
 *  0b0..The SMAP register is unlocked. The partition owner can change any writable bits of the SMAP register.
 *  0b1..The SMAP register is locked. The SMAP_LCK, CSP and PSP bits and G1 and G2 permission bits of the SMAP
 *       register cannot be changed until the partition is de-allocated or a POR occurs. The PARTITION_KMOD value can
 *       still be changed. The SMAG_LCK bit can be changed to a 1, but cannot be changed to a 0.
 */
#define CAAM_PX_SMAPR_JR_SMAP_LCK(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_JR_SMAP_LCK_SHIFT)) & CAAM_PX_SMAPR_JR_SMAP_LCK_MASK)

#define CAAM_PX_SMAPR_JR_PSP_MASK                (0x4000U)
#define CAAM_PX_SMAPR_JR_PSP_SHIFT               (14U)
/*! PSP
 *  0b0..The partition and any of the pages allocated to the partition can be de-allocated.
 *  0b1..The partition cannot be de-allocated and the pages allocated to the partition cannot be de-allocated.
 */
#define CAAM_PX_SMAPR_JR_PSP(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_JR_PSP_SHIFT)) & CAAM_PX_SMAPR_JR_PSP_MASK)

#define CAAM_PX_SMAPR_JR_CSP_MASK                (0x8000U)
#define CAAM_PX_SMAPR_JR_CSP_SHIFT               (15U)
/*! CSP
 *  0b0..The pages allocated to the partition will not be zeroized when they are de-allocated or the partition is
 *       released or a security alarm occurs.
 *  0b1..The pages allocated to the partition will be zeroized when they are individually de-allocated or the
 *       partition is released or a security alarm occurs.
 */
#define CAAM_PX_SMAPR_JR_CSP(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_JR_CSP_SHIFT)) & CAAM_PX_SMAPR_JR_CSP_MASK)

#define CAAM_PX_SMAPR_JR_PARTITION_KMOD_MASK     (0xFFFF0000U)
#define CAAM_PX_SMAPR_JR_PARTITION_KMOD_SHIFT    (16U)
#define CAAM_PX_SMAPR_JR_PARTITION_KMOD(x)       (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAPR_JR_PARTITION_KMOD_SHIFT)) & CAAM_PX_SMAPR_JR_PARTITION_KMOD_MASK)
/*! @} */

/* The count of CAAM_PX_SMAPR_JR */
#define CAAM_PX_SMAPR_JR_COUNT                   (4U)

/* The count of CAAM_PX_SMAPR_JR */
#define CAAM_PX_SMAPR_JR_COUNT2                  (16U)

/*! @name PX_SMAG2_JR - Secure Memory Access Group Registers */
/*! @{ */

#define CAAM_PX_SMAG2_JR_Gx_ID00_MASK            (0x1U)
#define CAAM_PX_SMAG2_JR_Gx_ID00_SHIFT           (0U)
#define CAAM_PX_SMAG2_JR_Gx_ID00(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID00_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID00_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID01_MASK            (0x2U)
#define CAAM_PX_SMAG2_JR_Gx_ID01_SHIFT           (1U)
#define CAAM_PX_SMAG2_JR_Gx_ID01(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID01_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID01_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID02_MASK            (0x4U)
#define CAAM_PX_SMAG2_JR_Gx_ID02_SHIFT           (2U)
#define CAAM_PX_SMAG2_JR_Gx_ID02(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID02_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID02_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID03_MASK            (0x8U)
#define CAAM_PX_SMAG2_JR_Gx_ID03_SHIFT           (3U)
#define CAAM_PX_SMAG2_JR_Gx_ID03(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID03_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID03_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID04_MASK            (0x10U)
#define CAAM_PX_SMAG2_JR_Gx_ID04_SHIFT           (4U)
#define CAAM_PX_SMAG2_JR_Gx_ID04(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID04_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID04_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID05_MASK            (0x20U)
#define CAAM_PX_SMAG2_JR_Gx_ID05_SHIFT           (5U)
#define CAAM_PX_SMAG2_JR_Gx_ID05(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID05_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID05_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID06_MASK            (0x40U)
#define CAAM_PX_SMAG2_JR_Gx_ID06_SHIFT           (6U)
#define CAAM_PX_SMAG2_JR_Gx_ID06(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID06_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID06_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID07_MASK            (0x80U)
#define CAAM_PX_SMAG2_JR_Gx_ID07_SHIFT           (7U)
#define CAAM_PX_SMAG2_JR_Gx_ID07(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID07_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID07_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID08_MASK            (0x100U)
#define CAAM_PX_SMAG2_JR_Gx_ID08_SHIFT           (8U)
#define CAAM_PX_SMAG2_JR_Gx_ID08(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID08_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID08_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID09_MASK            (0x200U)
#define CAAM_PX_SMAG2_JR_Gx_ID09_SHIFT           (9U)
#define CAAM_PX_SMAG2_JR_Gx_ID09(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID09_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID09_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID10_MASK            (0x400U)
#define CAAM_PX_SMAG2_JR_Gx_ID10_SHIFT           (10U)
#define CAAM_PX_SMAG2_JR_Gx_ID10(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID10_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID10_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID11_MASK            (0x800U)
#define CAAM_PX_SMAG2_JR_Gx_ID11_SHIFT           (11U)
#define CAAM_PX_SMAG2_JR_Gx_ID11(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID11_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID11_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID12_MASK            (0x1000U)
#define CAAM_PX_SMAG2_JR_Gx_ID12_SHIFT           (12U)
#define CAAM_PX_SMAG2_JR_Gx_ID12(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID12_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID12_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID13_MASK            (0x2000U)
#define CAAM_PX_SMAG2_JR_Gx_ID13_SHIFT           (13U)
#define CAAM_PX_SMAG2_JR_Gx_ID13(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID13_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID13_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID14_MASK            (0x4000U)
#define CAAM_PX_SMAG2_JR_Gx_ID14_SHIFT           (14U)
#define CAAM_PX_SMAG2_JR_Gx_ID14(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID14_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID14_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID15_MASK            (0x8000U)
#define CAAM_PX_SMAG2_JR_Gx_ID15_SHIFT           (15U)
#define CAAM_PX_SMAG2_JR_Gx_ID15(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID15_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID15_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID16_MASK            (0x10000U)
#define CAAM_PX_SMAG2_JR_Gx_ID16_SHIFT           (16U)
#define CAAM_PX_SMAG2_JR_Gx_ID16(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID16_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID16_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID17_MASK            (0x20000U)
#define CAAM_PX_SMAG2_JR_Gx_ID17_SHIFT           (17U)
#define CAAM_PX_SMAG2_JR_Gx_ID17(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID17_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID17_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID18_MASK            (0x40000U)
#define CAAM_PX_SMAG2_JR_Gx_ID18_SHIFT           (18U)
#define CAAM_PX_SMAG2_JR_Gx_ID18(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID18_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID18_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID19_MASK            (0x80000U)
#define CAAM_PX_SMAG2_JR_Gx_ID19_SHIFT           (19U)
#define CAAM_PX_SMAG2_JR_Gx_ID19(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID19_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID19_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID20_MASK            (0x100000U)
#define CAAM_PX_SMAG2_JR_Gx_ID20_SHIFT           (20U)
#define CAAM_PX_SMAG2_JR_Gx_ID20(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID20_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID20_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID21_MASK            (0x200000U)
#define CAAM_PX_SMAG2_JR_Gx_ID21_SHIFT           (21U)
#define CAAM_PX_SMAG2_JR_Gx_ID21(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID21_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID21_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID22_MASK            (0x400000U)
#define CAAM_PX_SMAG2_JR_Gx_ID22_SHIFT           (22U)
#define CAAM_PX_SMAG2_JR_Gx_ID22(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID22_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID22_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID23_MASK            (0x800000U)
#define CAAM_PX_SMAG2_JR_Gx_ID23_SHIFT           (23U)
#define CAAM_PX_SMAG2_JR_Gx_ID23(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID23_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID23_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID24_MASK            (0x1000000U)
#define CAAM_PX_SMAG2_JR_Gx_ID24_SHIFT           (24U)
#define CAAM_PX_SMAG2_JR_Gx_ID24(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID24_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID24_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID25_MASK            (0x2000000U)
#define CAAM_PX_SMAG2_JR_Gx_ID25_SHIFT           (25U)
#define CAAM_PX_SMAG2_JR_Gx_ID25(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID25_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID25_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID26_MASK            (0x4000000U)
#define CAAM_PX_SMAG2_JR_Gx_ID26_SHIFT           (26U)
#define CAAM_PX_SMAG2_JR_Gx_ID26(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID26_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID26_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID27_MASK            (0x8000000U)
#define CAAM_PX_SMAG2_JR_Gx_ID27_SHIFT           (27U)
#define CAAM_PX_SMAG2_JR_Gx_ID27(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID27_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID27_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID28_MASK            (0x10000000U)
#define CAAM_PX_SMAG2_JR_Gx_ID28_SHIFT           (28U)
#define CAAM_PX_SMAG2_JR_Gx_ID28(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID28_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID28_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID29_MASK            (0x20000000U)
#define CAAM_PX_SMAG2_JR_Gx_ID29_SHIFT           (29U)
#define CAAM_PX_SMAG2_JR_Gx_ID29(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID29_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID29_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID30_MASK            (0x40000000U)
#define CAAM_PX_SMAG2_JR_Gx_ID30_SHIFT           (30U)
#define CAAM_PX_SMAG2_JR_Gx_ID30(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID30_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID30_MASK)

#define CAAM_PX_SMAG2_JR_Gx_ID31_MASK            (0x80000000U)
#define CAAM_PX_SMAG2_JR_Gx_ID31_SHIFT           (31U)
#define CAAM_PX_SMAG2_JR_Gx_ID31(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG2_JR_Gx_ID31_SHIFT)) & CAAM_PX_SMAG2_JR_Gx_ID31_MASK)
/*! @} */

/* The count of CAAM_PX_SMAG2_JR */
#define CAAM_PX_SMAG2_JR_COUNT                   (4U)

/* The count of CAAM_PX_SMAG2_JR */
#define CAAM_PX_SMAG2_JR_COUNT2                  (16U)

/*! @name PX_SMAG1_JR - Secure Memory Access Group Registers */
/*! @{ */

#define CAAM_PX_SMAG1_JR_Gx_ID00_MASK            (0x1U)
#define CAAM_PX_SMAG1_JR_Gx_ID00_SHIFT           (0U)
#define CAAM_PX_SMAG1_JR_Gx_ID00(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID00_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID00_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID01_MASK            (0x2U)
#define CAAM_PX_SMAG1_JR_Gx_ID01_SHIFT           (1U)
#define CAAM_PX_SMAG1_JR_Gx_ID01(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID01_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID01_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID02_MASK            (0x4U)
#define CAAM_PX_SMAG1_JR_Gx_ID02_SHIFT           (2U)
#define CAAM_PX_SMAG1_JR_Gx_ID02(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID02_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID02_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID03_MASK            (0x8U)
#define CAAM_PX_SMAG1_JR_Gx_ID03_SHIFT           (3U)
#define CAAM_PX_SMAG1_JR_Gx_ID03(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID03_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID03_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID04_MASK            (0x10U)
#define CAAM_PX_SMAG1_JR_Gx_ID04_SHIFT           (4U)
#define CAAM_PX_SMAG1_JR_Gx_ID04(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID04_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID04_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID05_MASK            (0x20U)
#define CAAM_PX_SMAG1_JR_Gx_ID05_SHIFT           (5U)
#define CAAM_PX_SMAG1_JR_Gx_ID05(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID05_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID05_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID06_MASK            (0x40U)
#define CAAM_PX_SMAG1_JR_Gx_ID06_SHIFT           (6U)
#define CAAM_PX_SMAG1_JR_Gx_ID06(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID06_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID06_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID07_MASK            (0x80U)
#define CAAM_PX_SMAG1_JR_Gx_ID07_SHIFT           (7U)
#define CAAM_PX_SMAG1_JR_Gx_ID07(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID07_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID07_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID08_MASK            (0x100U)
#define CAAM_PX_SMAG1_JR_Gx_ID08_SHIFT           (8U)
#define CAAM_PX_SMAG1_JR_Gx_ID08(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID08_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID08_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID09_MASK            (0x200U)
#define CAAM_PX_SMAG1_JR_Gx_ID09_SHIFT           (9U)
#define CAAM_PX_SMAG1_JR_Gx_ID09(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID09_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID09_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID10_MASK            (0x400U)
#define CAAM_PX_SMAG1_JR_Gx_ID10_SHIFT           (10U)
#define CAAM_PX_SMAG1_JR_Gx_ID10(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID10_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID10_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID11_MASK            (0x800U)
#define CAAM_PX_SMAG1_JR_Gx_ID11_SHIFT           (11U)
#define CAAM_PX_SMAG1_JR_Gx_ID11(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID11_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID11_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID12_MASK            (0x1000U)
#define CAAM_PX_SMAG1_JR_Gx_ID12_SHIFT           (12U)
#define CAAM_PX_SMAG1_JR_Gx_ID12(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID12_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID12_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID13_MASK            (0x2000U)
#define CAAM_PX_SMAG1_JR_Gx_ID13_SHIFT           (13U)
#define CAAM_PX_SMAG1_JR_Gx_ID13(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID13_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID13_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID14_MASK            (0x4000U)
#define CAAM_PX_SMAG1_JR_Gx_ID14_SHIFT           (14U)
#define CAAM_PX_SMAG1_JR_Gx_ID14(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID14_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID14_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID15_MASK            (0x8000U)
#define CAAM_PX_SMAG1_JR_Gx_ID15_SHIFT           (15U)
#define CAAM_PX_SMAG1_JR_Gx_ID15(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID15_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID15_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID16_MASK            (0x10000U)
#define CAAM_PX_SMAG1_JR_Gx_ID16_SHIFT           (16U)
#define CAAM_PX_SMAG1_JR_Gx_ID16(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID16_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID16_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID17_MASK            (0x20000U)
#define CAAM_PX_SMAG1_JR_Gx_ID17_SHIFT           (17U)
#define CAAM_PX_SMAG1_JR_Gx_ID17(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID17_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID17_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID18_MASK            (0x40000U)
#define CAAM_PX_SMAG1_JR_Gx_ID18_SHIFT           (18U)
#define CAAM_PX_SMAG1_JR_Gx_ID18(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID18_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID18_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID19_MASK            (0x80000U)
#define CAAM_PX_SMAG1_JR_Gx_ID19_SHIFT           (19U)
#define CAAM_PX_SMAG1_JR_Gx_ID19(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID19_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID19_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID20_MASK            (0x100000U)
#define CAAM_PX_SMAG1_JR_Gx_ID20_SHIFT           (20U)
#define CAAM_PX_SMAG1_JR_Gx_ID20(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID20_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID20_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID21_MASK            (0x200000U)
#define CAAM_PX_SMAG1_JR_Gx_ID21_SHIFT           (21U)
#define CAAM_PX_SMAG1_JR_Gx_ID21(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID21_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID21_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID22_MASK            (0x400000U)
#define CAAM_PX_SMAG1_JR_Gx_ID22_SHIFT           (22U)
#define CAAM_PX_SMAG1_JR_Gx_ID22(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID22_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID22_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID23_MASK            (0x800000U)
#define CAAM_PX_SMAG1_JR_Gx_ID23_SHIFT           (23U)
#define CAAM_PX_SMAG1_JR_Gx_ID23(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID23_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID23_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID24_MASK            (0x1000000U)
#define CAAM_PX_SMAG1_JR_Gx_ID24_SHIFT           (24U)
#define CAAM_PX_SMAG1_JR_Gx_ID24(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID24_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID24_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID25_MASK            (0x2000000U)
#define CAAM_PX_SMAG1_JR_Gx_ID25_SHIFT           (25U)
#define CAAM_PX_SMAG1_JR_Gx_ID25(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID25_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID25_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID26_MASK            (0x4000000U)
#define CAAM_PX_SMAG1_JR_Gx_ID26_SHIFT           (26U)
#define CAAM_PX_SMAG1_JR_Gx_ID26(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID26_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID26_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID27_MASK            (0x8000000U)
#define CAAM_PX_SMAG1_JR_Gx_ID27_SHIFT           (27U)
#define CAAM_PX_SMAG1_JR_Gx_ID27(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID27_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID27_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID28_MASK            (0x10000000U)
#define CAAM_PX_SMAG1_JR_Gx_ID28_SHIFT           (28U)
#define CAAM_PX_SMAG1_JR_Gx_ID28(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID28_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID28_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID29_MASK            (0x20000000U)
#define CAAM_PX_SMAG1_JR_Gx_ID29_SHIFT           (29U)
#define CAAM_PX_SMAG1_JR_Gx_ID29(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID29_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID29_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID30_MASK            (0x40000000U)
#define CAAM_PX_SMAG1_JR_Gx_ID30_SHIFT           (30U)
#define CAAM_PX_SMAG1_JR_Gx_ID30(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID30_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID30_MASK)

#define CAAM_PX_SMAG1_JR_Gx_ID31_MASK            (0x80000000U)
#define CAAM_PX_SMAG1_JR_Gx_ID31_SHIFT           (31U)
#define CAAM_PX_SMAG1_JR_Gx_ID31(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_PX_SMAG1_JR_Gx_ID31_SHIFT)) & CAAM_PX_SMAG1_JR_Gx_ID31_MASK)
/*! @} */

/* The count of CAAM_PX_SMAG1_JR */
#define CAAM_PX_SMAG1_JR_COUNT                   (4U)

/* The count of CAAM_PX_SMAG1_JR */
#define CAAM_PX_SMAG1_JR_COUNT2                  (16U)

/*! @name SMCR_JR - Secure Memory Command Register */
/*! @{ */

#define CAAM_SMCR_JR_CMD_MASK                    (0xFU)
#define CAAM_SMCR_JR_CMD_SHIFT                   (0U)
#define CAAM_SMCR_JR_CMD(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_SMCR_JR_CMD_SHIFT)) & CAAM_SMCR_JR_CMD_MASK)

#define CAAM_SMCR_JR_PRTN_MASK                   (0xF00U)
#define CAAM_SMCR_JR_PRTN_SHIFT                  (8U)
#define CAAM_SMCR_JR_PRTN(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_SMCR_JR_PRTN_SHIFT)) & CAAM_SMCR_JR_PRTN_MASK)

#define CAAM_SMCR_JR_PAGE_MASK                   (0xFFFF0000U)
#define CAAM_SMCR_JR_PAGE_SHIFT                  (16U)
#define CAAM_SMCR_JR_PAGE(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_SMCR_JR_PAGE_SHIFT)) & CAAM_SMCR_JR_PAGE_MASK)
/*! @} */

/* The count of CAAM_SMCR_JR */
#define CAAM_SMCR_JR_COUNT                       (4U)

/*! @name SMCSR_JR - Secure Memory Command Status Register */
/*! @{ */

#define CAAM_SMCSR_JR_PRTN_MASK                  (0xFU)
#define CAAM_SMCSR_JR_PRTN_SHIFT                 (0U)
#define CAAM_SMCSR_JR_PRTN(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_SMCSR_JR_PRTN_SHIFT)) & CAAM_SMCSR_JR_PRTN_MASK)

#define CAAM_SMCSR_JR_PO_MASK                    (0xC0U)
#define CAAM_SMCSR_JR_PO_SHIFT                   (6U)
/*! PO
 *  0b00..Available; Unowned: The entity that issued the inquiry may allocate this page to a partition. No
 *        zeroization is needed since it has already been cleared, therefore no interrupt should be expected.
 *  0b01..Page does not exist in this version or is not initialized yet.
 *  0b10..Another entity owns the page. This page is unavailable to the issuer of the inquiry.
 *  0b11..Owned by the entity making the inquiry. The owner may de-allocate this page if its partition is not
 *        marked PSP. If the partition to which the page is allocated is designated as CSP, the page will be zeroized
 *        upon de-allocation.
 */
#define CAAM_SMCSR_JR_PO(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_SMCSR_JR_PO_SHIFT)) & CAAM_SMCSR_JR_PO_MASK)

#define CAAM_SMCSR_JR_AERR_MASK                  (0x3000U)
#define CAAM_SMCSR_JR_AERR_SHIFT                 (12U)
#define CAAM_SMCSR_JR_AERR(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_SMCSR_JR_AERR_SHIFT)) & CAAM_SMCSR_JR_AERR_MASK)

#define CAAM_SMCSR_JR_CERR_MASK                  (0xC000U)
#define CAAM_SMCSR_JR_CERR_SHIFT                 (14U)
/*! CERR
 *  0b00..No Error.
 *  0b01..Command has not yet completed.
 *  0b10..A security failure occurred.
 *  0b11..Command Overflow. Another command was issued by the same Job Ring owner before the owner's previous
 *        command completed. The additional command was ignored.
 */
#define CAAM_SMCSR_JR_CERR(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_SMCSR_JR_CERR_SHIFT)) & CAAM_SMCSR_JR_CERR_MASK)

#define CAAM_SMCSR_JR_PAGE_MASK                  (0xFFF0000U)
#define CAAM_SMCSR_JR_PAGE_SHIFT                 (16U)
#define CAAM_SMCSR_JR_PAGE(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_SMCSR_JR_PAGE_SHIFT)) & CAAM_SMCSR_JR_PAGE_MASK)
/*! @} */

/* The count of CAAM_SMCSR_JR */
#define CAAM_SMCSR_JR_COUNT                      (4U)

/*! @name REIR0JR - Recoverable Error Interrupt Record 0 for Job Ring 0..Recoverable Error Interrupt Record 0 for Job Ring 3 */
/*! @{ */

#define CAAM_REIR0JR_TYPE_MASK                   (0x3000000U)
#define CAAM_REIR0JR_TYPE_SHIFT                  (24U)
#define CAAM_REIR0JR_TYPE(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_REIR0JR_TYPE_SHIFT)) & CAAM_REIR0JR_TYPE_MASK)

#define CAAM_REIR0JR_MISS_MASK                   (0x80000000U)
#define CAAM_REIR0JR_MISS_SHIFT                  (31U)
#define CAAM_REIR0JR_MISS(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_REIR0JR_MISS_SHIFT)) & CAAM_REIR0JR_MISS_MASK)
/*! @} */

/* The count of CAAM_REIR0JR */
#define CAAM_REIR0JR_COUNT                       (4U)

/*! @name REIR2JR - Recoverable Error Interrupt Record 2 for Job Ring 0..Recoverable Error Interrupt Record 2 for Job Ring 3 */
/*! @{ */

#define CAAM_REIR2JR_ADDR_MASK                   (0xFFFFFFFFFU)
#define CAAM_REIR2JR_ADDR_SHIFT                  (0U)
#define CAAM_REIR2JR_ADDR(x)                     (((uint64_t)(((uint64_t)(x)) << CAAM_REIR2JR_ADDR_SHIFT)) & CAAM_REIR2JR_ADDR_MASK)
/*! @} */

/* The count of CAAM_REIR2JR */
#define CAAM_REIR2JR_COUNT                       (4U)

/*! @name REIR4JR - Recoverable Error Interrupt Record 4 for Job Ring 0..Recoverable Error Interrupt Record 4 for Job Ring 3 */
/*! @{ */

#define CAAM_REIR4JR_ICID_MASK                   (0x7FFU)
#define CAAM_REIR4JR_ICID_SHIFT                  (0U)
#define CAAM_REIR4JR_ICID(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_REIR4JR_ICID_SHIFT)) & CAAM_REIR4JR_ICID_MASK)

#define CAAM_REIR4JR_DID_MASK                    (0x7800U)
#define CAAM_REIR4JR_DID_SHIFT                   (11U)
#define CAAM_REIR4JR_DID(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_REIR4JR_DID_SHIFT)) & CAAM_REIR4JR_DID_MASK)

#define CAAM_REIR4JR_AXCACHE_MASK                (0xF0000U)
#define CAAM_REIR4JR_AXCACHE_SHIFT               (16U)
#define CAAM_REIR4JR_AXCACHE(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_REIR4JR_AXCACHE_SHIFT)) & CAAM_REIR4JR_AXCACHE_MASK)

#define CAAM_REIR4JR_AXPROT_MASK                 (0x700000U)
#define CAAM_REIR4JR_AXPROT_SHIFT                (20U)
#define CAAM_REIR4JR_AXPROT(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_REIR4JR_AXPROT_SHIFT)) & CAAM_REIR4JR_AXPROT_MASK)

#define CAAM_REIR4JR_RWB_MASK                    (0x800000U)
#define CAAM_REIR4JR_RWB_SHIFT                   (23U)
#define CAAM_REIR4JR_RWB(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_REIR4JR_RWB_SHIFT)) & CAAM_REIR4JR_RWB_MASK)

#define CAAM_REIR4JR_ERR_MASK                    (0x30000000U)
#define CAAM_REIR4JR_ERR_SHIFT                   (28U)
#define CAAM_REIR4JR_ERR(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_REIR4JR_ERR_SHIFT)) & CAAM_REIR4JR_ERR_MASK)

#define CAAM_REIR4JR_MIX_MASK                    (0xC0000000U)
#define CAAM_REIR4JR_MIX_SHIFT                   (30U)
#define CAAM_REIR4JR_MIX(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_REIR4JR_MIX_SHIFT)) & CAAM_REIR4JR_MIX_MASK)
/*! @} */

/* The count of CAAM_REIR4JR */
#define CAAM_REIR4JR_COUNT                       (4U)

/*! @name REIR5JR - Recoverable Error Interrupt Record 5 for Job Ring 0..Recoverable Error Interrupt Record 5 for Job Ring 3 */
/*! @{ */

#define CAAM_REIR5JR_BID_MASK                    (0xF0000U)
#define CAAM_REIR5JR_BID_SHIFT                   (16U)
#define CAAM_REIR5JR_BID(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_REIR5JR_BID_SHIFT)) & CAAM_REIR5JR_BID_MASK)

#define CAAM_REIR5JR_BNDG_MASK                   (0x2000000U)
#define CAAM_REIR5JR_BNDG_SHIFT                  (25U)
#define CAAM_REIR5JR_BNDG(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_REIR5JR_BNDG_SHIFT)) & CAAM_REIR5JR_BNDG_MASK)

#define CAAM_REIR5JR_TDSC_MASK                   (0x4000000U)
#define CAAM_REIR5JR_TDSC_SHIFT                  (26U)
#define CAAM_REIR5JR_TDSC(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_REIR5JR_TDSC_SHIFT)) & CAAM_REIR5JR_TDSC_MASK)

#define CAAM_REIR5JR_KMOD_MASK                   (0x8000000U)
#define CAAM_REIR5JR_KMOD_SHIFT                  (27U)
#define CAAM_REIR5JR_KMOD(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_REIR5JR_KMOD_SHIFT)) & CAAM_REIR5JR_KMOD_MASK)

#define CAAM_REIR5JR_KEY_MASK                    (0x10000000U)
#define CAAM_REIR5JR_KEY_SHIFT                   (28U)
#define CAAM_REIR5JR_KEY(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_REIR5JR_KEY_SHIFT)) & CAAM_REIR5JR_KEY_MASK)

#define CAAM_REIR5JR_SMA_MASK                    (0x20000000U)
#define CAAM_REIR5JR_SMA_SHIFT                   (29U)
#define CAAM_REIR5JR_SMA(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_REIR5JR_SMA_SHIFT)) & CAAM_REIR5JR_SMA_MASK)
/*! @} */

/* The count of CAAM_REIR5JR */
#define CAAM_REIR5JR_COUNT                       (4U)

/*! @name RSTA - RTIC Status Register */
/*! @{ */

#define CAAM_RSTA_BSY_MASK                       (0x1U)
#define CAAM_RSTA_BSY_SHIFT                      (0U)
/*! BSY
 *  0b0..RTIC Idle.
 *  0b1..RTIC Busy.
 */
#define CAAM_RSTA_BSY(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_RSTA_BSY_SHIFT)) & CAAM_RSTA_BSY_MASK)

#define CAAM_RSTA_HD_MASK                        (0x2U)
#define CAAM_RSTA_HD_SHIFT                       (1U)
/*! HD
 *  0b0..Boot authentication disabled
 *  0b1..Authenticate code/generate reference hash value. This bit cannot be modified during run-time checking mode.
 */
#define CAAM_RSTA_HD(x)                          (((uint32_t)(((uint32_t)(x)) << CAAM_RSTA_HD_SHIFT)) & CAAM_RSTA_HD_MASK)

#define CAAM_RSTA_SV_MASK                        (0x4U)
#define CAAM_RSTA_SV_SHIFT                       (2U)
/*! SV
 *  0b0..Memory block contents authenticated.
 *  0b1..Memory block hash doesn't match reference value.
 */
#define CAAM_RSTA_SV(x)                          (((uint32_t)(((uint32_t)(x)) << CAAM_RSTA_SV_SHIFT)) & CAAM_RSTA_SV_MASK)

#define CAAM_RSTA_HE_MASK                        (0x8U)
#define CAAM_RSTA_HE_SHIFT                       (3U)
/*! HE
 *  0b0..Memory block contents authenticated.
 *  0b1..Memory block hash doesn't match reference value.
 */
#define CAAM_RSTA_HE(x)                          (((uint32_t)(((uint32_t)(x)) << CAAM_RSTA_HE_SHIFT)) & CAAM_RSTA_HE_MASK)

#define CAAM_RSTA_MIS_MASK                       (0xF0U)
#define CAAM_RSTA_MIS_SHIFT                      (4U)
/*! MIS
 *  0b0000..Memory Block X is valid or state unknown
 *  0b0001..Memory Block X has been corrupted
 */
#define CAAM_RSTA_MIS(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_RSTA_MIS_SHIFT)) & CAAM_RSTA_MIS_MASK)

#define CAAM_RSTA_AE_MASK                        (0xF00U)
#define CAAM_RSTA_AE_SHIFT                       (8U)
/*! AE
 *  0b0000..All reads by RTIC were valid.
 *  0b0001..An illegal address was accessed by the RTIC
 */
#define CAAM_RSTA_AE(x)                          (((uint32_t)(((uint32_t)(x)) << CAAM_RSTA_AE_SHIFT)) & CAAM_RSTA_AE_MASK)

#define CAAM_RSTA_WE_MASK                        (0x10000U)
#define CAAM_RSTA_WE_SHIFT                       (16U)
/*! WE
 *  0b0..No RTIC Watchdog timer error has occurred.
 *  0b1..RTIC Watchdog timer has expired prior to completing a round of hashing.
 */
#define CAAM_RSTA_WE(x)                          (((uint32_t)(((uint32_t)(x)) << CAAM_RSTA_WE_SHIFT)) & CAAM_RSTA_WE_MASK)

#define CAAM_RSTA_ABH_MASK                       (0x20000U)
#define CAAM_RSTA_ABH_SHIFT                      (17U)
#define CAAM_RSTA_ABH(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_RSTA_ABH_SHIFT)) & CAAM_RSTA_ABH_MASK)

#define CAAM_RSTA_HOD_MASK                       (0x40000U)
#define CAAM_RSTA_HOD_SHIFT                      (18U)
#define CAAM_RSTA_HOD(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_RSTA_HOD_SHIFT)) & CAAM_RSTA_HOD_MASK)

#define CAAM_RSTA_RTD_MASK                       (0x80000U)
#define CAAM_RSTA_RTD_SHIFT                      (19U)
#define CAAM_RSTA_RTD(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_RSTA_RTD_SHIFT)) & CAAM_RSTA_RTD_MASK)

#define CAAM_RSTA_CS_MASK                        (0x6000000U)
#define CAAM_RSTA_CS_SHIFT                       (25U)
/*! CS
 *  0b00..Idle State
 *  0b01..Single Hash State
 *  0b10..Run-time State
 *  0b11..Error State
 */
#define CAAM_RSTA_CS(x)                          (((uint32_t)(((uint32_t)(x)) << CAAM_RSTA_CS_SHIFT)) & CAAM_RSTA_CS_MASK)
/*! @} */

/*! @name RCMD - RTIC Command Register */
/*! @{ */

#define CAAM_RCMD_CINT_MASK                      (0x1U)
#define CAAM_RCMD_CINT_SHIFT                     (0U)
/*! CINT
 *  0b0..Do not clear interrupt
 *  0b1..Clear interrupt. This bit cannot be modified during run-time checking mode
 */
#define CAAM_RCMD_CINT(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_RCMD_CINT_SHIFT)) & CAAM_RCMD_CINT_MASK)

#define CAAM_RCMD_HO_MASK                        (0x2U)
#define CAAM_RCMD_HO_SHIFT                       (1U)
/*! HO
 *  0b0..Boot authentication disabled
 *  0b1..Authenticate code/generate reference hash value. This bit cannot be modified during run-time checking mode.
 */
#define CAAM_RCMD_HO(x)                          (((uint32_t)(((uint32_t)(x)) << CAAM_RCMD_HO_SHIFT)) & CAAM_RCMD_HO_MASK)

#define CAAM_RCMD_RTC_MASK                       (0x4U)
#define CAAM_RCMD_RTC_SHIFT                      (2U)
/*! RTC
 *  0b0..Run-time checking disabled
 *  0b1..Verify run-time memory blocks continually
 */
#define CAAM_RCMD_RTC(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_RCMD_RTC_SHIFT)) & CAAM_RCMD_RTC_MASK)

#define CAAM_RCMD_RTD_MASK                       (0x8U)
#define CAAM_RCMD_RTD_SHIFT                      (3U)
/*! RTD
 *  0b0..Allow Run Time Mode
 *  0b1..Prevent Run Time Mode
 */
#define CAAM_RCMD_RTD(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_RCMD_RTD_SHIFT)) & CAAM_RCMD_RTD_MASK)
/*! @} */

/*! @name RCTL - RTIC Control Register */
/*! @{ */

#define CAAM_RCTL_IE_MASK                        (0x1U)
#define CAAM_RCTL_IE_SHIFT                       (0U)
/*! IE
 *  0b0..Interrupts disabled
 *  0b1..Interrupts enabled
 */
#define CAAM_RCTL_IE(x)                          (((uint32_t)(((uint32_t)(x)) << CAAM_RCTL_IE_SHIFT)) & CAAM_RCTL_IE_MASK)

#define CAAM_RCTL_RREQS_MASK                     (0xEU)
#define CAAM_RCTL_RREQS_SHIFT                    (1U)
#define CAAM_RCTL_RREQS(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_RCTL_RREQS_SHIFT)) & CAAM_RCTL_RREQS_MASK)

#define CAAM_RCTL_HOME_MASK                      (0xF0U)
#define CAAM_RCTL_HOME_SHIFT                     (4U)
#define CAAM_RCTL_HOME(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_RCTL_HOME_SHIFT)) & CAAM_RCTL_HOME_MASK)

#define CAAM_RCTL_RTME_MASK                      (0xF00U)
#define CAAM_RCTL_RTME_SHIFT                     (8U)
#define CAAM_RCTL_RTME(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_RCTL_RTME_SHIFT)) & CAAM_RCTL_RTME_MASK)

#define CAAM_RCTL_RTMU_MASK                      (0xF000U)
#define CAAM_RCTL_RTMU_SHIFT                     (12U)
#define CAAM_RCTL_RTMU(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_RCTL_RTMU_SHIFT)) & CAAM_RCTL_RTMU_MASK)

#define CAAM_RCTL_RALG_MASK                      (0xF0000U)
#define CAAM_RCTL_RALG_SHIFT                     (16U)
#define CAAM_RCTL_RALG(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_RCTL_RALG_SHIFT)) & CAAM_RCTL_RALG_MASK)

#define CAAM_RCTL_RIDLE_MASK                     (0x100000U)
#define CAAM_RCTL_RIDLE_SHIFT                    (20U)
#define CAAM_RCTL_RIDLE(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_RCTL_RIDLE_SHIFT)) & CAAM_RCTL_RIDLE_MASK)
/*! @} */

/*! @name RTHR - RTIC Throttle Register */
/*! @{ */

#define CAAM_RTHR_RTHR_MASK                      (0xFFFFU)
#define CAAM_RTHR_RTHR_SHIFT                     (0U)
#define CAAM_RTHR_RTHR(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_RTHR_RTHR_SHIFT)) & CAAM_RTHR_RTHR_MASK)
/*! @} */

/*! @name RWDOG - RTIC Watchdog Timer */
/*! @{ */

#define CAAM_RWDOG_RWDOG_MASK                    (0xFFFFFFFFU)
#define CAAM_RWDOG_RWDOG_SHIFT                   (0U)
#define CAAM_RWDOG_RWDOG(x)                      (((uint64_t)(((uint64_t)(x)) << CAAM_RWDOG_RWDOG_SHIFT)) & CAAM_RWDOG_RWDOG_MASK)
/*! @} */

/*! @name REND - RTIC Endian Register */
/*! @{ */

#define CAAM_REND_REPO_MASK                      (0xFU)
#define CAAM_REND_REPO_SHIFT                     (0U)
/*! REPO
 *  0b1xxx..Byte Swap Memory Block D
 *  0bx1xx..Byte Swap Memory Block C
 *  0bxx1x..Byte Swap Memory Block B
 *  0bxxx1..Byte Swap Memory Block A
 */
#define CAAM_REND_REPO(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_REND_REPO_SHIFT)) & CAAM_REND_REPO_MASK)

#define CAAM_REND_RBS_MASK                       (0xF0U)
#define CAAM_REND_RBS_SHIFT                      (4U)
/*! RBS
 *  0b1xxx..Byte Swap Memory Block D
 *  0bx1xx..Byte Swap Memory Block C
 *  0bxx1x..Byte Swap Memory Block B
 *  0bxxx1..Byte Swap Memory Block A
 */
#define CAAM_REND_RBS(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_REND_RBS_SHIFT)) & CAAM_REND_RBS_MASK)

#define CAAM_REND_RHWS_MASK                      (0xF00U)
#define CAAM_REND_RHWS_SHIFT                     (8U)
/*! RHWS
 *  0b1xxx..Half-Word Swap Memory Block D
 *  0bx1xx..Half-Word Swap Memory Block C
 *  0bxx1x..Half-Word Swap Memory Block B
 *  0bxxx1..Half-Word Swap Memory Block A
 */
#define CAAM_REND_RHWS(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_REND_RHWS_SHIFT)) & CAAM_REND_RHWS_MASK)

#define CAAM_REND_RWS_MASK                       (0xF000U)
#define CAAM_REND_RWS_SHIFT                      (12U)
/*! RWS
 *  0b1xxx..Word Swap Memory Block D
 *  0bx1xx..Word Swap Memory Block C
 *  0bxx1x..Word Swap Memory Block B
 *  0bxxx1..Word Swap Memory Block A
 */
#define CAAM_REND_RWS(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_REND_RWS_SHIFT)) & CAAM_REND_RWS_MASK)
/*! @} */

/*! @name RMA - RTIC Memory Block A Address 0 Register..RTIC Memory Block D Address 1 Register */
/*! @{ */

#define CAAM_RMA_MEMBLKADDR_MASK                 (0xFFFFFFFFFU)
#define CAAM_RMA_MEMBLKADDR_SHIFT                (0U)
#define CAAM_RMA_MEMBLKADDR(x)                   (((uint64_t)(((uint64_t)(x)) << CAAM_RMA_MEMBLKADDR_SHIFT)) & CAAM_RMA_MEMBLKADDR_MASK)
/*! @} */

/* The count of CAAM_RMA */
#define CAAM_RMA_COUNT                           (4U)

/* The count of CAAM_RMA */
#define CAAM_RMA_COUNT2                          (2U)

/*! @name RML - RTIC Memory Block A Length 0 Register..RTIC Memory Block D Length 1 Register */
/*! @{ */

#define CAAM_RML_MEMBLKLEN_MASK                  (0xFFFFFFFFU)
#define CAAM_RML_MEMBLKLEN_SHIFT                 (0U)
#define CAAM_RML_MEMBLKLEN(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_RML_MEMBLKLEN_SHIFT)) & CAAM_RML_MEMBLKLEN_MASK)
/*! @} */

/* The count of CAAM_RML */
#define CAAM_RML_COUNT                           (4U)

/* The count of CAAM_RML */
#define CAAM_RML_COUNT2                          (2U)

/*! @name RMD - RTIC Memory Block A Big Endian Hash Result Word 0..RTIC Memory Block D Little Endian Hash Result Word 31 */
/*! @{ */

#define CAAM_RMD_RTIC_Hash_Result_MASK           (0xFFFFFFFFU)
#define CAAM_RMD_RTIC_Hash_Result_SHIFT          (0U)
#define CAAM_RMD_RTIC_Hash_Result(x)             (((uint32_t)(((uint32_t)(x)) << CAAM_RMD_RTIC_Hash_Result_SHIFT)) & CAAM_RMD_RTIC_Hash_Result_MASK)
/*! @} */

/* The count of CAAM_RMD */
#define CAAM_RMD_COUNT                           (4U)

/* The count of CAAM_RMD */
#define CAAM_RMD_COUNT2                          (2U)

/* The count of CAAM_RMD */
#define CAAM_RMD_COUNT3                          (32U)

/*! @name REIR0RTIC - Recoverable Error Interrupt Record 0 for RTIC */
/*! @{ */

#define CAAM_REIR0RTIC_TYPE_MASK                 (0x3000000U)
#define CAAM_REIR0RTIC_TYPE_SHIFT                (24U)
#define CAAM_REIR0RTIC_TYPE(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_REIR0RTIC_TYPE_SHIFT)) & CAAM_REIR0RTIC_TYPE_MASK)

#define CAAM_REIR0RTIC_MISS_MASK                 (0x80000000U)
#define CAAM_REIR0RTIC_MISS_SHIFT                (31U)
#define CAAM_REIR0RTIC_MISS(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_REIR0RTIC_MISS_SHIFT)) & CAAM_REIR0RTIC_MISS_MASK)
/*! @} */

/*! @name REIR2RTIC - Recoverable Error Interrupt Record 2 for RTIC */
/*! @{ */

#define CAAM_REIR2RTIC_ADDR_MASK                 (0xFFFFFFFFFFFFFFFFU)
#define CAAM_REIR2RTIC_ADDR_SHIFT                (0U)
#define CAAM_REIR2RTIC_ADDR(x)                   (((uint64_t)(((uint64_t)(x)) << CAAM_REIR2RTIC_ADDR_SHIFT)) & CAAM_REIR2RTIC_ADDR_MASK)
/*! @} */

/*! @name REIR4RTIC - Recoverable Error Interrupt Record 4 for RTIC */
/*! @{ */

#define CAAM_REIR4RTIC_ICID_MASK                 (0x7FFU)
#define CAAM_REIR4RTIC_ICID_SHIFT                (0U)
#define CAAM_REIR4RTIC_ICID(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_REIR4RTIC_ICID_SHIFT)) & CAAM_REIR4RTIC_ICID_MASK)

#define CAAM_REIR4RTIC_DID_MASK                  (0x7800U)
#define CAAM_REIR4RTIC_DID_SHIFT                 (11U)
#define CAAM_REIR4RTIC_DID(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_REIR4RTIC_DID_SHIFT)) & CAAM_REIR4RTIC_DID_MASK)

#define CAAM_REIR4RTIC_AXCACHE_MASK              (0xF0000U)
#define CAAM_REIR4RTIC_AXCACHE_SHIFT             (16U)
#define CAAM_REIR4RTIC_AXCACHE(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_REIR4RTIC_AXCACHE_SHIFT)) & CAAM_REIR4RTIC_AXCACHE_MASK)

#define CAAM_REIR4RTIC_AXPROT_MASK               (0x700000U)
#define CAAM_REIR4RTIC_AXPROT_SHIFT              (20U)
#define CAAM_REIR4RTIC_AXPROT(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_REIR4RTIC_AXPROT_SHIFT)) & CAAM_REIR4RTIC_AXPROT_MASK)

#define CAAM_REIR4RTIC_RWB_MASK                  (0x800000U)
#define CAAM_REIR4RTIC_RWB_SHIFT                 (23U)
#define CAAM_REIR4RTIC_RWB(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_REIR4RTIC_RWB_SHIFT)) & CAAM_REIR4RTIC_RWB_MASK)

#define CAAM_REIR4RTIC_ERR_MASK                  (0x30000000U)
#define CAAM_REIR4RTIC_ERR_SHIFT                 (28U)
#define CAAM_REIR4RTIC_ERR(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_REIR4RTIC_ERR_SHIFT)) & CAAM_REIR4RTIC_ERR_MASK)

#define CAAM_REIR4RTIC_MIX_MASK                  (0xC0000000U)
#define CAAM_REIR4RTIC_MIX_SHIFT                 (30U)
#define CAAM_REIR4RTIC_MIX(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_REIR4RTIC_MIX_SHIFT)) & CAAM_REIR4RTIC_MIX_MASK)
/*! @} */

/*! @name REIR5RTIC - Recoverable Error Interrupt Record 5 for RTIC */
/*! @{ */

#define CAAM_REIR5RTIC_BID_MASK                  (0xF0000U)
#define CAAM_REIR5RTIC_BID_SHIFT                 (16U)
#define CAAM_REIR5RTIC_BID(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_REIR5RTIC_BID_SHIFT)) & CAAM_REIR5RTIC_BID_MASK)

#define CAAM_REIR5RTIC_SAFE_MASK                 (0x1000000U)
#define CAAM_REIR5RTIC_SAFE_SHIFT                (24U)
#define CAAM_REIR5RTIC_SAFE(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_REIR5RTIC_SAFE_SHIFT)) & CAAM_REIR5RTIC_SAFE_MASK)

#define CAAM_REIR5RTIC_SMA_MASK                  (0x2000000U)
#define CAAM_REIR5RTIC_SMA_SHIFT                 (25U)
#define CAAM_REIR5RTIC_SMA(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_REIR5RTIC_SMA_SHIFT)) & CAAM_REIR5RTIC_SMA_MASK)
/*! @} */

/*! @name CC1MR - CCB 0 Class 1 Mode Register Format for Non-Public Key Algorithms */
/*! @{ */

#define CAAM_CC1MR_ENC_MASK                      (0x1U)
#define CAAM_CC1MR_ENC_SHIFT                     (0U)
/*! ENC
 *  0b0..Decrypt.
 *  0b1..Encrypt.
 */
#define CAAM_CC1MR_ENC(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CC1MR_ENC_SHIFT)) & CAAM_CC1MR_ENC_MASK)

#define CAAM_CC1MR_ICV_TEST_MASK                 (0x2U)
#define CAAM_CC1MR_ICV_TEST_SHIFT                (1U)
#define CAAM_CC1MR_ICV_TEST(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_CC1MR_ICV_TEST_SHIFT)) & CAAM_CC1MR_ICV_TEST_MASK)

#define CAAM_CC1MR_AS_MASK                       (0xCU)
#define CAAM_CC1MR_AS_SHIFT                      (2U)
/*! AS
 *  0b00..Update
 *  0b01..Initialize
 *  0b10..Finalize
 *  0b11..Initialize/Finalize
 */
#define CAAM_CC1MR_AS(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_CC1MR_AS_SHIFT)) & CAAM_CC1MR_AS_MASK)

#define CAAM_CC1MR_AAI_MASK                      (0x1FF0U)
#define CAAM_CC1MR_AAI_SHIFT                     (4U)
#define CAAM_CC1MR_AAI(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CC1MR_AAI_SHIFT)) & CAAM_CC1MR_AAI_MASK)

#define CAAM_CC1MR_ALG_MASK                      (0xFF0000U)
#define CAAM_CC1MR_ALG_SHIFT                     (16U)
/*! ALG
 *  0b00010000..AES
 *  0b00100000..DES
 *  0b00100001..3DES
 *  0b01010000..RNG
 */
#define CAAM_CC1MR_ALG(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CC1MR_ALG_SHIFT)) & CAAM_CC1MR_ALG_MASK)
/*! @} */

/* The count of CAAM_CC1MR */
#define CAAM_CC1MR_COUNT                         (1U)

/*! @name CC1MR_PK - CCB 0 Class 1 Mode Register Format for Public Key Algorithms */
/*! @{ */

#define CAAM_CC1MR_PK_PKHA_MODE_LS_MASK          (0xFFFU)
#define CAAM_CC1MR_PK_PKHA_MODE_LS_SHIFT         (0U)
#define CAAM_CC1MR_PK_PKHA_MODE_LS(x)            (((uint32_t)(((uint32_t)(x)) << CAAM_CC1MR_PK_PKHA_MODE_LS_SHIFT)) & CAAM_CC1MR_PK_PKHA_MODE_LS_MASK)

#define CAAM_CC1MR_PK_PKHA_MODE_MS_MASK          (0xF0000U)
#define CAAM_CC1MR_PK_PKHA_MODE_MS_SHIFT         (16U)
#define CAAM_CC1MR_PK_PKHA_MODE_MS(x)            (((uint32_t)(((uint32_t)(x)) << CAAM_CC1MR_PK_PKHA_MODE_MS_SHIFT)) & CAAM_CC1MR_PK_PKHA_MODE_MS_MASK)
/*! @} */

/* The count of CAAM_CC1MR_PK */
#define CAAM_CC1MR_PK_COUNT                      (1U)

/*! @name CC1MR_RNG - CCB 0 Class 1 Mode Register Format for RNG4 */
/*! @{ */

#define CAAM_CC1MR_RNG_TST_MASK                  (0x1U)
#define CAAM_CC1MR_RNG_TST_SHIFT                 (0U)
#define CAAM_CC1MR_RNG_TST(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_CC1MR_RNG_TST_SHIFT)) & CAAM_CC1MR_RNG_TST_MASK)

#define CAAM_CC1MR_RNG_PR_MASK                   (0x2U)
#define CAAM_CC1MR_RNG_PR_SHIFT                  (1U)
#define CAAM_CC1MR_RNG_PR(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CC1MR_RNG_PR_SHIFT)) & CAAM_CC1MR_RNG_PR_MASK)

#define CAAM_CC1MR_RNG_AS_MASK                   (0xCU)
#define CAAM_CC1MR_RNG_AS_SHIFT                  (2U)
#define CAAM_CC1MR_RNG_AS(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CC1MR_RNG_AS_SHIFT)) & CAAM_CC1MR_RNG_AS_MASK)

#define CAAM_CC1MR_RNG_SH_MASK                   (0x30U)
#define CAAM_CC1MR_RNG_SH_SHIFT                  (4U)
/*! SH
 *  0b00..State Handle 0
 *  0b01..State Handle 1
 *  0b10..Reserved
 *  0b11..Reserved
 */
#define CAAM_CC1MR_RNG_SH(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CC1MR_RNG_SH_SHIFT)) & CAAM_CC1MR_RNG_SH_MASK)

#define CAAM_CC1MR_RNG_NZB_MASK                  (0x100U)
#define CAAM_CC1MR_RNG_NZB_SHIFT                 (8U)
/*! NZB
 *  0b0..Generate random data with all-zero bytes permitted.
 *  0b1..Generate random data without any all-zero bytes.
 */
#define CAAM_CC1MR_RNG_NZB(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_CC1MR_RNG_NZB_SHIFT)) & CAAM_CC1MR_RNG_NZB_MASK)

#define CAAM_CC1MR_RNG_OBP_MASK                  (0x200U)
#define CAAM_CC1MR_RNG_OBP_SHIFT                 (9U)
/*! OBP
 *  0b0..No odd byte parity.
 *  0b1..Generate random data with odd byte parity.
 */
#define CAAM_CC1MR_RNG_OBP(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_CC1MR_RNG_OBP_SHIFT)) & CAAM_CC1MR_RNG_OBP_MASK)

#define CAAM_CC1MR_RNG_PS_MASK                   (0x400U)
#define CAAM_CC1MR_RNG_PS_SHIFT                  (10U)
/*! PS
 *  0b0..No personalization string is included.
 *  0b1..A personalization string is included.
 */
#define CAAM_CC1MR_RNG_PS(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CC1MR_RNG_PS_SHIFT)) & CAAM_CC1MR_RNG_PS_MASK)

#define CAAM_CC1MR_RNG_AI_MASK                   (0x800U)
#define CAAM_CC1MR_RNG_AI_SHIFT                  (11U)
/*! AI
 *  0b0..No additional entropy input has been provided.
 *  0b1..Additional entropy input has been provided.
 */
#define CAAM_CC1MR_RNG_AI(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CC1MR_RNG_AI_SHIFT)) & CAAM_CC1MR_RNG_AI_MASK)

#define CAAM_CC1MR_RNG_SK_MASK                   (0x1000U)
#define CAAM_CC1MR_RNG_SK_SHIFT                  (12U)
/*! SK
 *  0b0..The destination for the RNG data is specified by the FIFO STORE command.
 *  0b1..The RNG data will go to the JDKEKR, TDKEKR and DSKR.
 */
#define CAAM_CC1MR_RNG_SK(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CC1MR_RNG_SK_SHIFT)) & CAAM_CC1MR_RNG_SK_MASK)

#define CAAM_CC1MR_RNG_ALG_MASK                  (0xFF0000U)
#define CAAM_CC1MR_RNG_ALG_SHIFT                 (16U)
/*! ALG
 *  0b01010000..RNG
 */
#define CAAM_CC1MR_RNG_ALG(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_CC1MR_RNG_ALG_SHIFT)) & CAAM_CC1MR_RNG_ALG_MASK)
/*! @} */

/* The count of CAAM_CC1MR_RNG */
#define CAAM_CC1MR_RNG_COUNT                     (1U)

/*! @name CC1KSR - CCB 0 Class 1 Key Size Register */
/*! @{ */

#define CAAM_CC1KSR_C1KS_MASK                    (0x7FU)
#define CAAM_CC1KSR_C1KS_SHIFT                   (0U)
#define CAAM_CC1KSR_C1KS(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_CC1KSR_C1KS_SHIFT)) & CAAM_CC1KSR_C1KS_MASK)
/*! @} */

/* The count of CAAM_CC1KSR */
#define CAAM_CC1KSR_COUNT                        (1U)

/*! @name CC1DSR - CCB 0 Class 1 Data Size Register */
/*! @{ */

#define CAAM_CC1DSR_C1DS_MASK                    (0xFFFFFFFFU)
#define CAAM_CC1DSR_C1DS_SHIFT                   (0U)
#define CAAM_CC1DSR_C1DS(x)                      (((uint64_t)(((uint64_t)(x)) << CAAM_CC1DSR_C1DS_SHIFT)) & CAAM_CC1DSR_C1DS_MASK)

#define CAAM_CC1DSR_C1CY_MASK                    (0x100000000U)
#define CAAM_CC1DSR_C1CY_SHIFT                   (32U)
/*! C1CY
 *  0b0..No carry out of the C1 Data Size Reg.
 *  0b1..There was a carry out of the C1 Data Size Reg.
 */
#define CAAM_CC1DSR_C1CY(x)                      (((uint64_t)(((uint64_t)(x)) << CAAM_CC1DSR_C1CY_SHIFT)) & CAAM_CC1DSR_C1CY_MASK)

#define CAAM_CC1DSR_NUMBITS_MASK                 (0xE000000000000000U)
#define CAAM_CC1DSR_NUMBITS_SHIFT                (61U)
#define CAAM_CC1DSR_NUMBITS(x)                   (((uint64_t)(((uint64_t)(x)) << CAAM_CC1DSR_NUMBITS_SHIFT)) & CAAM_CC1DSR_NUMBITS_MASK)
/*! @} */

/* The count of CAAM_CC1DSR */
#define CAAM_CC1DSR_COUNT                        (1U)

/*! @name CC1ICVSR - CCB 0 Class 1 ICV Size Register */
/*! @{ */

#define CAAM_CC1ICVSR_C1ICVS_MASK                (0x1FU)
#define CAAM_CC1ICVSR_C1ICVS_SHIFT               (0U)
#define CAAM_CC1ICVSR_C1ICVS(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CC1ICVSR_C1ICVS_SHIFT)) & CAAM_CC1ICVSR_C1ICVS_MASK)
/*! @} */

/* The count of CAAM_CC1ICVSR */
#define CAAM_CC1ICVSR_COUNT                      (1U)

/*! @name CCCTRL - CCB 0 CHA Control Register */
/*! @{ */

#define CAAM_CCCTRL_CCB_MASK                     (0x1U)
#define CAAM_CCCTRL_CCB_SHIFT                    (0U)
/*! CCB
 *  0b0..Do Not Reset
 *  0b1..Reset CCB
 */
#define CAAM_CCCTRL_CCB(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CCCTRL_CCB_SHIFT)) & CAAM_CCCTRL_CCB_MASK)

#define CAAM_CCCTRL_AES_MASK                     (0x2U)
#define CAAM_CCCTRL_AES_SHIFT                    (1U)
/*! AES
 *  0b0..Do Not Reset
 *  0b1..Reset AES Accelerator
 */
#define CAAM_CCCTRL_AES(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CCCTRL_AES_SHIFT)) & CAAM_CCCTRL_AES_MASK)

#define CAAM_CCCTRL_DES_MASK                     (0x4U)
#define CAAM_CCCTRL_DES_SHIFT                    (2U)
/*! DES
 *  0b0..Do Not Reset
 *  0b1..Reset DES Accelerator
 */
#define CAAM_CCCTRL_DES(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CCCTRL_DES_SHIFT)) & CAAM_CCCTRL_DES_MASK)

#define CAAM_CCCTRL_PK_MASK                      (0x40U)
#define CAAM_CCCTRL_PK_SHIFT                     (6U)
/*! PK
 *  0b0..Do Not Reset
 *  0b1..Reset Public Key Hardware Accelerator
 */
#define CAAM_CCCTRL_PK(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CCCTRL_PK_SHIFT)) & CAAM_CCCTRL_PK_MASK)

#define CAAM_CCCTRL_MD_MASK                      (0x80U)
#define CAAM_CCCTRL_MD_SHIFT                     (7U)
/*! MD
 *  0b0..Do Not Reset
 *  0b1..Reset Message Digest Hardware Accelerator
 */
#define CAAM_CCCTRL_MD(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CCCTRL_MD_SHIFT)) & CAAM_CCCTRL_MD_MASK)

#define CAAM_CCCTRL_CRC_MASK                     (0x100U)
#define CAAM_CCCTRL_CRC_SHIFT                    (8U)
/*! CRC
 *  0b0..Do Not Reset
 *  0b1..Reset CRC Accelerator
 */
#define CAAM_CCCTRL_CRC(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CCCTRL_CRC_SHIFT)) & CAAM_CCCTRL_CRC_MASK)

#define CAAM_CCCTRL_RNG_MASK                     (0x200U)
#define CAAM_CCCTRL_RNG_SHIFT                    (9U)
/*! RNG
 *  0b0..Do Not Reset
 *  0b1..Reset Random Number Generator Block.
 */
#define CAAM_CCCTRL_RNG(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CCCTRL_RNG_SHIFT)) & CAAM_CCCTRL_RNG_MASK)

#define CAAM_CCCTRL_UA0_MASK                     (0x10000U)
#define CAAM_CCCTRL_UA0_SHIFT                    (16U)
/*! UA0
 *  0b0..Don't unload the PKHA A0 Memory.
 *  0b1..Unload the PKHA A0 Memory into OFIFO.
 */
#define CAAM_CCCTRL_UA0(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CCCTRL_UA0_SHIFT)) & CAAM_CCCTRL_UA0_MASK)

#define CAAM_CCCTRL_UA1_MASK                     (0x20000U)
#define CAAM_CCCTRL_UA1_SHIFT                    (17U)
/*! UA1
 *  0b0..Don't unload the PKHA A1 Memory.
 *  0b1..Unload the PKHA A1 Memory into OFIFO.
 */
#define CAAM_CCCTRL_UA1(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CCCTRL_UA1_SHIFT)) & CAAM_CCCTRL_UA1_MASK)

#define CAAM_CCCTRL_UA2_MASK                     (0x40000U)
#define CAAM_CCCTRL_UA2_SHIFT                    (18U)
/*! UA2
 *  0b0..Don't unload the PKHA A2 Memory.
 *  0b1..Unload the PKHA A2 Memory into OFIFO.
 */
#define CAAM_CCCTRL_UA2(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CCCTRL_UA2_SHIFT)) & CAAM_CCCTRL_UA2_MASK)

#define CAAM_CCCTRL_UA3_MASK                     (0x80000U)
#define CAAM_CCCTRL_UA3_SHIFT                    (19U)
/*! UA3
 *  0b0..Don't unload the PKHA A3 Memory.
 *  0b1..Unload the PKHA A3 Memory into OFIFO.
 */
#define CAAM_CCCTRL_UA3(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CCCTRL_UA3_SHIFT)) & CAAM_CCCTRL_UA3_MASK)

#define CAAM_CCCTRL_UB0_MASK                     (0x100000U)
#define CAAM_CCCTRL_UB0_SHIFT                    (20U)
/*! UB0
 *  0b0..Don't unload the PKHA B0 Memory.
 *  0b1..Unload the PKHA B0 Memory into OFIFO.
 */
#define CAAM_CCCTRL_UB0(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CCCTRL_UB0_SHIFT)) & CAAM_CCCTRL_UB0_MASK)

#define CAAM_CCCTRL_UB1_MASK                     (0x200000U)
#define CAAM_CCCTRL_UB1_SHIFT                    (21U)
/*! UB1
 *  0b0..Don't unload the PKHA B1 Memory.
 *  0b1..Unload the PKHA B1 Memory into OFIFO.
 */
#define CAAM_CCCTRL_UB1(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CCCTRL_UB1_SHIFT)) & CAAM_CCCTRL_UB1_MASK)

#define CAAM_CCCTRL_UB2_MASK                     (0x400000U)
#define CAAM_CCCTRL_UB2_SHIFT                    (22U)
/*! UB2
 *  0b0..Don't unload the PKHA B2 Memory.
 *  0b1..Unload the PKHA B2 Memory into OFIFO.
 */
#define CAAM_CCCTRL_UB2(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CCCTRL_UB2_SHIFT)) & CAAM_CCCTRL_UB2_MASK)

#define CAAM_CCCTRL_UB3_MASK                     (0x800000U)
#define CAAM_CCCTRL_UB3_SHIFT                    (23U)
/*! UB3
 *  0b0..Don't unload the PKHA B3 Memory.
 *  0b1..Unload the PKHA B3 Memory into OFIFO.
 */
#define CAAM_CCCTRL_UB3(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CCCTRL_UB3_SHIFT)) & CAAM_CCCTRL_UB3_MASK)

#define CAAM_CCCTRL_UN_MASK                      (0x1000000U)
#define CAAM_CCCTRL_UN_SHIFT                     (24U)
/*! UN
 *  0b0..Don't unload the PKHA N Memory.
 *  0b1..Unload the PKHA N Memory into OFIFO.
 */
#define CAAM_CCCTRL_UN(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CCCTRL_UN_SHIFT)) & CAAM_CCCTRL_UN_MASK)

#define CAAM_CCCTRL_UA_MASK                      (0x4000000U)
#define CAAM_CCCTRL_UA_SHIFT                     (26U)
/*! UA
 *  0b0..Don't unload the PKHA A Memory.
 *  0b1..Unload the PKHA A Memory into OFIFO.
 */
#define CAAM_CCCTRL_UA(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CCCTRL_UA_SHIFT)) & CAAM_CCCTRL_UA_MASK)

#define CAAM_CCCTRL_UB_MASK                      (0x8000000U)
#define CAAM_CCCTRL_UB_SHIFT                     (27U)
/*! UB
 *  0b0..Don't unload the PKHA B Memory.
 *  0b1..Unload the PKHA B Memory into OFIFO.
 */
#define CAAM_CCCTRL_UB(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CCCTRL_UB_SHIFT)) & CAAM_CCCTRL_UB_MASK)
/*! @} */

/* The count of CAAM_CCCTRL */
#define CAAM_CCCTRL_COUNT                        (1U)

/*! @name CICTL - CCB 0 Interrupt Control Register */
/*! @{ */

#define CAAM_CICTL_ADI_MASK                      (0x2U)
#define CAAM_CICTL_ADI_SHIFT                     (1U)
#define CAAM_CICTL_ADI(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CICTL_ADI_SHIFT)) & CAAM_CICTL_ADI_MASK)

#define CAAM_CICTL_DDI_MASK                      (0x4U)
#define CAAM_CICTL_DDI_SHIFT                     (2U)
#define CAAM_CICTL_DDI(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CICTL_DDI_SHIFT)) & CAAM_CICTL_DDI_MASK)

#define CAAM_CICTL_PDI_MASK                      (0x40U)
#define CAAM_CICTL_PDI_SHIFT                     (6U)
#define CAAM_CICTL_PDI(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CICTL_PDI_SHIFT)) & CAAM_CICTL_PDI_MASK)

#define CAAM_CICTL_MDI_MASK                      (0x80U)
#define CAAM_CICTL_MDI_SHIFT                     (7U)
#define CAAM_CICTL_MDI(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CICTL_MDI_SHIFT)) & CAAM_CICTL_MDI_MASK)

#define CAAM_CICTL_CDI_MASK                      (0x100U)
#define CAAM_CICTL_CDI_SHIFT                     (8U)
#define CAAM_CICTL_CDI(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CICTL_CDI_SHIFT)) & CAAM_CICTL_CDI_MASK)

#define CAAM_CICTL_RNDI_MASK                     (0x200U)
#define CAAM_CICTL_RNDI_SHIFT                    (9U)
#define CAAM_CICTL_RNDI(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CICTL_RNDI_SHIFT)) & CAAM_CICTL_RNDI_MASK)

#define CAAM_CICTL_AEI_MASK                      (0x20000U)
#define CAAM_CICTL_AEI_SHIFT                     (17U)
/*! AEI
 *  0b0..No AESA error detected
 *  0b1..AESA error detected
 */
#define CAAM_CICTL_AEI(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CICTL_AEI_SHIFT)) & CAAM_CICTL_AEI_MASK)

#define CAAM_CICTL_DEI_MASK                      (0x40000U)
#define CAAM_CICTL_DEI_SHIFT                     (18U)
/*! DEI
 *  0b0..No DESA error detected
 *  0b1..DESA error detected
 */
#define CAAM_CICTL_DEI(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CICTL_DEI_SHIFT)) & CAAM_CICTL_DEI_MASK)

#define CAAM_CICTL_PEI_MASK                      (0x400000U)
#define CAAM_CICTL_PEI_SHIFT                     (22U)
/*! PEI
 *  0b0..No PKHA error detected
 *  0b1..PKHA error detected
 */
#define CAAM_CICTL_PEI(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CICTL_PEI_SHIFT)) & CAAM_CICTL_PEI_MASK)

#define CAAM_CICTL_MEI_MASK                      (0x800000U)
#define CAAM_CICTL_MEI_SHIFT                     (23U)
/*! MEI
 *  0b0..No MDHA error detected
 *  0b1..MDHA error detected
 */
#define CAAM_CICTL_MEI(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CICTL_MEI_SHIFT)) & CAAM_CICTL_MEI_MASK)

#define CAAM_CICTL_CEI_MASK                      (0x1000000U)
#define CAAM_CICTL_CEI_SHIFT                     (24U)
/*! CEI
 *  0b0..No CRCA error detected
 *  0b1..CRCA error detected
 */
#define CAAM_CICTL_CEI(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CICTL_CEI_SHIFT)) & CAAM_CICTL_CEI_MASK)

#define CAAM_CICTL_RNEI_MASK                     (0x2000000U)
#define CAAM_CICTL_RNEI_SHIFT                    (25U)
/*! RNEI
 *  0b0..No RNG error detected
 *  0b1..RNG error detected
 */
#define CAAM_CICTL_RNEI(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CICTL_RNEI_SHIFT)) & CAAM_CICTL_RNEI_MASK)
/*! @} */

/* The count of CAAM_CICTL */
#define CAAM_CICTL_COUNT                         (1U)

/*! @name CCWR - CCB 0 Clear Written Register */
/*! @{ */

#define CAAM_CCWR_C1M_MASK                       (0x1U)
#define CAAM_CCWR_C1M_SHIFT                      (0U)
/*! C1M
 *  0b0..Don't clear the Class 1 Mode Register.
 *  0b1..Clear the Class 1 Mode Register.
 */
#define CAAM_CCWR_C1M(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_CCWR_C1M_SHIFT)) & CAAM_CCWR_C1M_MASK)

#define CAAM_CCWR_C1DS_MASK                      (0x4U)
#define CAAM_CCWR_C1DS_SHIFT                     (2U)
/*! C1DS
 *  0b0..Don't clear the Class 1 Data Size Register.
 *  0b1..Clear the Class 1 Data Size Register.
 */
#define CAAM_CCWR_C1DS(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CCWR_C1DS_SHIFT)) & CAAM_CCWR_C1DS_MASK)

#define CAAM_CCWR_C1ICV_MASK                     (0x8U)
#define CAAM_CCWR_C1ICV_SHIFT                    (3U)
/*! C1ICV
 *  0b0..Don't clear the Class 1 ICV Size Register.
 *  0b1..Clear the Class 1 ICV Size Register.
 */
#define CAAM_CCWR_C1ICV(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CCWR_C1ICV_SHIFT)) & CAAM_CCWR_C1ICV_MASK)

#define CAAM_CCWR_C1C_MASK                       (0x20U)
#define CAAM_CCWR_C1C_SHIFT                      (5U)
/*! C1C
 *  0b0..Don't clear the Class 1 Context Register.
 *  0b1..Clear the Class 1 Context Register.
 */
#define CAAM_CCWR_C1C(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_CCWR_C1C_SHIFT)) & CAAM_CCWR_C1C_MASK)

#define CAAM_CCWR_C1K_MASK                       (0x40U)
#define CAAM_CCWR_C1K_SHIFT                      (6U)
/*! C1K
 *  0b0..Don't clear the Class 1 Key Register.
 *  0b1..Clear the Class 1 Key Register.
 */
#define CAAM_CCWR_C1K(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_CCWR_C1K_SHIFT)) & CAAM_CCWR_C1K_MASK)

#define CAAM_CCWR_CPKA_MASK                      (0x1000U)
#define CAAM_CCWR_CPKA_SHIFT                     (12U)
/*! CPKA
 *  0b0..Don't clear the PKHA A Size Register.
 *  0b1..Clear the PKHA A Size Register.
 */
#define CAAM_CCWR_CPKA(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CCWR_CPKA_SHIFT)) & CAAM_CCWR_CPKA_MASK)

#define CAAM_CCWR_CPKB_MASK                      (0x2000U)
#define CAAM_CCWR_CPKB_SHIFT                     (13U)
/*! CPKB
 *  0b0..Don't clear the PKHA B Size Register.
 *  0b1..Clear the PKHA B Size Register.
 */
#define CAAM_CCWR_CPKB(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CCWR_CPKB_SHIFT)) & CAAM_CCWR_CPKB_MASK)

#define CAAM_CCWR_CPKN_MASK                      (0x4000U)
#define CAAM_CCWR_CPKN_SHIFT                     (14U)
/*! CPKN
 *  0b0..Don't clear the PKHA N Size Register.
 *  0b1..Clear the PKHA N Size Register.
 */
#define CAAM_CCWR_CPKN(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CCWR_CPKN_SHIFT)) & CAAM_CCWR_CPKN_MASK)

#define CAAM_CCWR_CPKE_MASK                      (0x8000U)
#define CAAM_CCWR_CPKE_SHIFT                     (15U)
/*! CPKE
 *  0b0..Don't clear the PKHA E Size Register..
 *  0b1..Clear the PKHA E Size Register.
 */
#define CAAM_CCWR_CPKE(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CCWR_CPKE_SHIFT)) & CAAM_CCWR_CPKE_MASK)

#define CAAM_CCWR_C2M_MASK                       (0x10000U)
#define CAAM_CCWR_C2M_SHIFT                      (16U)
/*! C2M
 *  0b0..Don't clear the Class 2 Mode Register.
 *  0b1..Clear the Class 2 Mode Register.
 */
#define CAAM_CCWR_C2M(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_CCWR_C2M_SHIFT)) & CAAM_CCWR_C2M_MASK)

#define CAAM_CCWR_C2DS_MASK                      (0x40000U)
#define CAAM_CCWR_C2DS_SHIFT                     (18U)
/*! C2DS
 *  0b0..Don't clear the Class 2 Data Size Register.
 *  0b1..Clear the Class 2 Data Size Register.
 */
#define CAAM_CCWR_C2DS(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CCWR_C2DS_SHIFT)) & CAAM_CCWR_C2DS_MASK)

#define CAAM_CCWR_C2C_MASK                       (0x200000U)
#define CAAM_CCWR_C2C_SHIFT                      (21U)
/*! C2C
 *  0b0..Don't clear the Class 2 Context Register.
 *  0b1..Clear the Class 2 Context Register.
 */
#define CAAM_CCWR_C2C(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_CCWR_C2C_SHIFT)) & CAAM_CCWR_C2C_MASK)

#define CAAM_CCWR_C2K_MASK                       (0x400000U)
#define CAAM_CCWR_C2K_SHIFT                      (22U)
/*! C2K
 *  0b0..Don't clear the Class 2 Key Register.
 *  0b1..Clear the Class 2 Key Register.
 */
#define CAAM_CCWR_C2K(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_CCWR_C2K_SHIFT)) & CAAM_CCWR_C2K_MASK)

#define CAAM_CCWR_CDS_MASK                       (0x2000000U)
#define CAAM_CCWR_CDS_SHIFT                      (25U)
/*! CDS
 *  0b0..Don't clear the shared descriptor signal.
 *  0b1..Clear the shared descriptor signal.
 */
#define CAAM_CCWR_CDS(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_CCWR_CDS_SHIFT)) & CAAM_CCWR_CDS_MASK)

#define CAAM_CCWR_C2D_MASK                       (0x4000000U)
#define CAAM_CCWR_C2D_SHIFT                      (26U)
/*! C2D
 *  0b0..Don't clear the Class 2 done interrrupt.
 *  0b1..Clear the Class 2 done interrrupt.
 */
#define CAAM_CCWR_C2D(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_CCWR_C2D_SHIFT)) & CAAM_CCWR_C2D_MASK)

#define CAAM_CCWR_C1D_MASK                       (0x8000000U)
#define CAAM_CCWR_C1D_SHIFT                      (27U)
/*! C1D
 *  0b0..Don't clear the Class 1 done interrrupt.
 *  0b1..Clear the Class 1 done interrrupt.
 */
#define CAAM_CCWR_C1D(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_CCWR_C1D_SHIFT)) & CAAM_CCWR_C1D_MASK)

#define CAAM_CCWR_C2RST_MASK                     (0x10000000U)
#define CAAM_CCWR_C2RST_SHIFT                    (28U)
/*! C2RST
 *  0b0..Don't reset the Class 2 CHA.
 *  0b1..Reset the Class 2 CHA.
 */
#define CAAM_CCWR_C2RST(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CCWR_C2RST_SHIFT)) & CAAM_CCWR_C2RST_MASK)

#define CAAM_CCWR_C1RST_MASK                     (0x20000000U)
#define CAAM_CCWR_C1RST_SHIFT                    (29U)
/*! C1RST
 *  0b0..Don't reset the Class 1 CHA.
 *  0b1..Reset the Class 1 CHA.
 */
#define CAAM_CCWR_C1RST(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CCWR_C1RST_SHIFT)) & CAAM_CCWR_C1RST_MASK)

#define CAAM_CCWR_COF_MASK                       (0x40000000U)
#define CAAM_CCWR_COF_SHIFT                      (30U)
/*! COF
 *  0b0..Don't clear the OFIFO.
 *  0b1..Clear the OFIFO.
 */
#define CAAM_CCWR_COF(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_CCWR_COF_SHIFT)) & CAAM_CCWR_COF_MASK)

#define CAAM_CCWR_CIF_MASK                       (0x80000000U)
#define CAAM_CCWR_CIF_SHIFT                      (31U)
/*! CIF
 *  0b0..Don't clear the IFIFO.
 *  0b1..Clear the IFIFO.
 */
#define CAAM_CCWR_CIF(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_CCWR_CIF_SHIFT)) & CAAM_CCWR_CIF_MASK)
/*! @} */

/* The count of CAAM_CCWR */
#define CAAM_CCWR_COUNT                          (1U)

/*! @name CCSTA_MS - CCB 0 Status and Error Register, most-significant half */
/*! @{ */

#define CAAM_CCSTA_MS_ERRID1_MASK                (0xFU)
#define CAAM_CCSTA_MS_ERRID1_SHIFT               (0U)
/*! ERRID1
 *  0b0001..Mode Error
 *  0b0010..Data Size Error, including PKHA N Memory Size Error
 *  0b0011..Key Size Error, including PKHA E Memory Size Error
 *  0b0100..PKHA A Memory Size Error
 *  0b0101..PKHA B Memory Size Error
 *  0b0110..Data Arrived out of Sequence Error
 *  0b0111..PKHA Divide by Zero Error
 *  0b1000..PKHA Modulus Even Error
 *  0b1001..DES Key Parity Error
 *  0b1010..ICV Check Failed
 *  0b1011..Internal Hardware Failure
 *  0b1100..CCM AAD Size Error (either 1. AAD flag in B0 =1 and no AAD type provided, 2. AAD flag in B0 = 0 and
 *          AAD provided, or 3. AAD flag in B0 =1 and not enough AAD provided - expecting more based on AAD size.)
 *  0b1101..Class 1 CHA is not reset
 *  0b1110..Invalid CHA combination was selected
 *  0b1111..Invalid CHA Selected
 */
#define CAAM_CCSTA_MS_ERRID1(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CCSTA_MS_ERRID1_SHIFT)) & CAAM_CCSTA_MS_ERRID1_MASK)

#define CAAM_CCSTA_MS_CL1_MASK                   (0xF000U)
#define CAAM_CCSTA_MS_CL1_SHIFT                  (12U)
/*! CL1
 *  0b0001..AES
 *  0b0010..DES
 *  0b0101..RNG
 *  0b1000..Public Key
 */
#define CAAM_CCSTA_MS_CL1(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CCSTA_MS_CL1_SHIFT)) & CAAM_CCSTA_MS_CL1_MASK)

#define CAAM_CCSTA_MS_ERRID2_MASK                (0xF0000U)
#define CAAM_CCSTA_MS_ERRID2_SHIFT               (16U)
/*! ERRID2
 *  0b0001..Mode Error
 *  0b0010..Data Size Error
 *  0b0011..Key Size Error
 *  0b0110..Data Arrived out of Sequence Error
 *  0b1010..ICV Check Failed
 *  0b1011..Internal Hardware Failure
 *  0b1110..Invalid CHA combination was selected.
 *  0b1111..Invalid CHA Selected
 */
#define CAAM_CCSTA_MS_ERRID2(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CCSTA_MS_ERRID2_SHIFT)) & CAAM_CCSTA_MS_ERRID2_MASK)

#define CAAM_CCSTA_MS_CL2_MASK                   (0xF0000000U)
#define CAAM_CCSTA_MS_CL2_SHIFT                  (28U)
/*! CL2
 *  0b0100..MD5, SHA-1, SHA-224, SHA-256, SHA-384, SHA-512 and SHA-512/224, SHA-512/256
 *  0b1001..CRC
 */
#define CAAM_CCSTA_MS_CL2(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CCSTA_MS_CL2_SHIFT)) & CAAM_CCSTA_MS_CL2_MASK)
/*! @} */

/* The count of CAAM_CCSTA_MS */
#define CAAM_CCSTA_MS_COUNT                      (1U)

/*! @name CCSTA_LS - CCB 0 Status and Error Register, least-significant half */
/*! @{ */

#define CAAM_CCSTA_LS_AB_MASK                    (0x2U)
#define CAAM_CCSTA_LS_AB_SHIFT                   (1U)
/*! AB
 *  0b0..AESA Idle
 *  0b1..AESA Busy
 */
#define CAAM_CCSTA_LS_AB(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_CCSTA_LS_AB_SHIFT)) & CAAM_CCSTA_LS_AB_MASK)

#define CAAM_CCSTA_LS_DB_MASK                    (0x4U)
#define CAAM_CCSTA_LS_DB_SHIFT                   (2U)
/*! DB
 *  0b0..DESA Idle
 *  0b1..DESA Busy
 */
#define CAAM_CCSTA_LS_DB(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_CCSTA_LS_DB_SHIFT)) & CAAM_CCSTA_LS_DB_MASK)

#define CAAM_CCSTA_LS_PB_MASK                    (0x40U)
#define CAAM_CCSTA_LS_PB_SHIFT                   (6U)
/*! PB
 *  0b0..PKHA Idle
 *  0b1..PKHA Busy
 */
#define CAAM_CCSTA_LS_PB(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_CCSTA_LS_PB_SHIFT)) & CAAM_CCSTA_LS_PB_MASK)

#define CAAM_CCSTA_LS_MB_MASK                    (0x80U)
#define CAAM_CCSTA_LS_MB_SHIFT                   (7U)
/*! MB
 *  0b0..MDHA Idle
 *  0b1..MDHA Busy
 */
#define CAAM_CCSTA_LS_MB(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_CCSTA_LS_MB_SHIFT)) & CAAM_CCSTA_LS_MB_MASK)

#define CAAM_CCSTA_LS_CB_MASK                    (0x100U)
#define CAAM_CCSTA_LS_CB_SHIFT                   (8U)
/*! CB
 *  0b0..CRCA Idle
 *  0b1..CRCA Busy
 */
#define CAAM_CCSTA_LS_CB(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_CCSTA_LS_CB_SHIFT)) & CAAM_CCSTA_LS_CB_MASK)

#define CAAM_CCSTA_LS_RNB_MASK                   (0x200U)
#define CAAM_CCSTA_LS_RNB_SHIFT                  (9U)
/*! RNB
 *  0b0..RNG Idle
 *  0b1..RNG Busy
 */
#define CAAM_CCSTA_LS_RNB(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CCSTA_LS_RNB_SHIFT)) & CAAM_CCSTA_LS_RNB_MASK)

#define CAAM_CCSTA_LS_PDI_MASK                   (0x10000U)
#define CAAM_CCSTA_LS_PDI_SHIFT                  (16U)
/*! PDI
 *  0b0..Not Done
 *  0b1..Done Interrupt
 */
#define CAAM_CCSTA_LS_PDI(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CCSTA_LS_PDI_SHIFT)) & CAAM_CCSTA_LS_PDI_MASK)

#define CAAM_CCSTA_LS_SDI_MASK                   (0x20000U)
#define CAAM_CCSTA_LS_SDI_SHIFT                  (17U)
/*! SDI
 *  0b0..Not Done
 *  0b1..Done Interrupt
 */
#define CAAM_CCSTA_LS_SDI(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CCSTA_LS_SDI_SHIFT)) & CAAM_CCSTA_LS_SDI_MASK)

#define CAAM_CCSTA_LS_PEI_MASK                   (0x100000U)
#define CAAM_CCSTA_LS_PEI_SHIFT                  (20U)
/*! PEI
 *  0b0..No Error
 *  0b1..Error Interrupt
 */
#define CAAM_CCSTA_LS_PEI(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CCSTA_LS_PEI_SHIFT)) & CAAM_CCSTA_LS_PEI_MASK)

#define CAAM_CCSTA_LS_SEI_MASK                   (0x200000U)
#define CAAM_CCSTA_LS_SEI_SHIFT                  (21U)
/*! SEI
 *  0b0..No Error
 *  0b1..Error Interrupt
 */
#define CAAM_CCSTA_LS_SEI(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CCSTA_LS_SEI_SHIFT)) & CAAM_CCSTA_LS_SEI_MASK)

#define CAAM_CCSTA_LS_PRM_MASK                   (0x10000000U)
#define CAAM_CCSTA_LS_PRM_SHIFT                  (28U)
/*! PRM
 *  0b0..The given number is NOT prime.
 *  0b1..The given number is probably prime.
 */
#define CAAM_CCSTA_LS_PRM(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CCSTA_LS_PRM_SHIFT)) & CAAM_CCSTA_LS_PRM_MASK)

#define CAAM_CCSTA_LS_GCD_MASK                   (0x20000000U)
#define CAAM_CCSTA_LS_GCD_SHIFT                  (29U)
/*! GCD
 *  0b0..The greatest common divisor of two numbers is NOT one.
 *  0b1..The greatest common divisor of two numbers is one.
 */
#define CAAM_CCSTA_LS_GCD(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CCSTA_LS_GCD_SHIFT)) & CAAM_CCSTA_LS_GCD_MASK)

#define CAAM_CCSTA_LS_PIZ_MASK                   (0x40000000U)
#define CAAM_CCSTA_LS_PIZ_SHIFT                  (30U)
/*! PIZ
 *  0b0..The result of a Public Key operation is not zero.
 *  0b1..The result of a Public Key operation is zero.
 */
#define CAAM_CCSTA_LS_PIZ(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CCSTA_LS_PIZ_SHIFT)) & CAAM_CCSTA_LS_PIZ_MASK)
/*! @} */

/* The count of CAAM_CCSTA_LS */
#define CAAM_CCSTA_LS_COUNT                      (1U)

/*! @name CC1AADSZR - CCB 0 Class 1 AAD Size Register */
/*! @{ */

#define CAAM_CC1AADSZR_AASZ_MASK                 (0xFU)
#define CAAM_CC1AADSZR_AASZ_SHIFT                (0U)
#define CAAM_CC1AADSZR_AASZ(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_CC1AADSZR_AASZ_SHIFT)) & CAAM_CC1AADSZR_AASZ_MASK)
/*! @} */

/* The count of CAAM_CC1AADSZR */
#define CAAM_CC1AADSZR_COUNT                     (1U)

/*! @name CC1IVSZR - CCB 0 Class 1 IV Size Register */
/*! @{ */

#define CAAM_CC1IVSZR_IVSZ_MASK                  (0xFU)
#define CAAM_CC1IVSZR_IVSZ_SHIFT                 (0U)
#define CAAM_CC1IVSZR_IVSZ(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_CC1IVSZR_IVSZ_SHIFT)) & CAAM_CC1IVSZR_IVSZ_MASK)
/*! @} */

/* The count of CAAM_CC1IVSZR */
#define CAAM_CC1IVSZR_COUNT                      (1U)

/*! @name CPKASZR - PKHA A Size Register */
/*! @{ */

#define CAAM_CPKASZR_PKASZ_MASK                  (0x3FFU)
#define CAAM_CPKASZR_PKASZ_SHIFT                 (0U)
#define CAAM_CPKASZR_PKASZ(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_CPKASZR_PKASZ_SHIFT)) & CAAM_CPKASZR_PKASZ_MASK)
/*! @} */

/* The count of CAAM_CPKASZR */
#define CAAM_CPKASZR_COUNT                       (1U)

/*! @name CPKBSZR - PKHA B Size Register */
/*! @{ */

#define CAAM_CPKBSZR_PKBSZ_MASK                  (0x3FFU)
#define CAAM_CPKBSZR_PKBSZ_SHIFT                 (0U)
#define CAAM_CPKBSZR_PKBSZ(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_CPKBSZR_PKBSZ_SHIFT)) & CAAM_CPKBSZR_PKBSZ_MASK)
/*! @} */

/* The count of CAAM_CPKBSZR */
#define CAAM_CPKBSZR_COUNT                       (1U)

/*! @name CPKNSZR - PKHA N Size Register */
/*! @{ */

#define CAAM_CPKNSZR_PKNSZ_MASK                  (0x3FFU)
#define CAAM_CPKNSZR_PKNSZ_SHIFT                 (0U)
#define CAAM_CPKNSZR_PKNSZ(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_CPKNSZR_PKNSZ_SHIFT)) & CAAM_CPKNSZR_PKNSZ_MASK)
/*! @} */

/* The count of CAAM_CPKNSZR */
#define CAAM_CPKNSZR_COUNT                       (1U)

/*! @name CPKESZR - PKHA E Size Register */
/*! @{ */

#define CAAM_CPKESZR_PKESZ_MASK                  (0x3FFU)
#define CAAM_CPKESZR_PKESZ_SHIFT                 (0U)
#define CAAM_CPKESZR_PKESZ(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_CPKESZR_PKESZ_SHIFT)) & CAAM_CPKESZR_PKESZ_MASK)
/*! @} */

/* The count of CAAM_CPKESZR */
#define CAAM_CPKESZR_COUNT                       (1U)

/*! @name CC1CTXR - CCB 0 Class 1 Context Register Word 0..CCB 0 Class 1 Context Register Word 15 */
/*! @{ */

#define CAAM_CC1CTXR_C1CTX_MASK                  (0xFFFFFFFFU)
#define CAAM_CC1CTXR_C1CTX_SHIFT                 (0U)
#define CAAM_CC1CTXR_C1CTX(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_CC1CTXR_C1CTX_SHIFT)) & CAAM_CC1CTXR_C1CTX_MASK)
/*! @} */

/* The count of CAAM_CC1CTXR */
#define CAAM_CC1CTXR_COUNT                       (1U)

/* The count of CAAM_CC1CTXR */
#define CAAM_CC1CTXR_COUNT2                      (16U)

/*! @name CC1KR - CCB 0 Class 1 Key Registers Word 0..CCB 0 Class 1 Key Registers Word 7 */
/*! @{ */

#define CAAM_CC1KR_C1KEY_MASK                    (0xFFFFFFFFU)
#define CAAM_CC1KR_C1KEY_SHIFT                   (0U)
#define CAAM_CC1KR_C1KEY(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_CC1KR_C1KEY_SHIFT)) & CAAM_CC1KR_C1KEY_MASK)
/*! @} */

/* The count of CAAM_CC1KR */
#define CAAM_CC1KR_COUNT                         (1U)

/* The count of CAAM_CC1KR */
#define CAAM_CC1KR_COUNT2                        (8U)

/*! @name CC2MR - CCB 0 Class 2 Mode Register */
/*! @{ */

#define CAAM_CC2MR_AP_MASK                       (0x1U)
#define CAAM_CC2MR_AP_SHIFT                      (0U)
/*! AP
 *  0b0..Authenticate
 *  0b1..Protect
 */
#define CAAM_CC2MR_AP(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_CC2MR_AP_SHIFT)) & CAAM_CC2MR_AP_MASK)

#define CAAM_CC2MR_ICV_MASK                      (0x2U)
#define CAAM_CC2MR_ICV_SHIFT                     (1U)
/*! ICV
 *  0b0..Don't compare the calculated ICV against a received ICV.
 *  0b1..Compare the calculated ICV against a received ICV.
 */
#define CAAM_CC2MR_ICV(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CC2MR_ICV_SHIFT)) & CAAM_CC2MR_ICV_MASK)

#define CAAM_CC2MR_AS_MASK                       (0xCU)
#define CAAM_CC2MR_AS_SHIFT                      (2U)
/*! AS
 *  0b00..Update.
 *  0b01..Initialize.
 *  0b10..Finalize.
 *  0b11..Initialize/Finalize.
 */
#define CAAM_CC2MR_AS(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_CC2MR_AS_SHIFT)) & CAAM_CC2MR_AS_MASK)

#define CAAM_CC2MR_AAI_MASK                      (0x1FF0U)
#define CAAM_CC2MR_AAI_SHIFT                     (4U)
#define CAAM_CC2MR_AAI(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CC2MR_AAI_SHIFT)) & CAAM_CC2MR_AAI_MASK)

#define CAAM_CC2MR_ALG_MASK                      (0xFF0000U)
#define CAAM_CC2MR_ALG_SHIFT                     (16U)
/*! ALG
 *  0b01000000..MD5
 *  0b01000001..SHA-1
 *  0b01000010..SHA-224
 *  0b01000011..SHA-256
 *  0b01000100..SHA-384
 *  0b01000101..SHA-512
 *  0b01000110..SHA-512/224
 *  0b01000111..SHA-512/256
 *  0b10010000..CRC
 */
#define CAAM_CC2MR_ALG(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CC2MR_ALG_SHIFT)) & CAAM_CC2MR_ALG_MASK)
/*! @} */

/* The count of CAAM_CC2MR */
#define CAAM_CC2MR_COUNT                         (1U)

/*! @name CC2KSR - CCB 0 Class 2 Key Size Register */
/*! @{ */

#define CAAM_CC2KSR_C2KS_MASK                    (0xFFU)
#define CAAM_CC2KSR_C2KS_SHIFT                   (0U)
#define CAAM_CC2KSR_C2KS(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_CC2KSR_C2KS_SHIFT)) & CAAM_CC2KSR_C2KS_MASK)
/*! @} */

/* The count of CAAM_CC2KSR */
#define CAAM_CC2KSR_COUNT                        (1U)

/*! @name CC2DSR - CCB 0 Class 2 Data Size Register */
/*! @{ */

#define CAAM_CC2DSR_C2DS_MASK                    (0xFFFFFFFFU)
#define CAAM_CC2DSR_C2DS_SHIFT                   (0U)
#define CAAM_CC2DSR_C2DS(x)                      (((uint64_t)(((uint64_t)(x)) << CAAM_CC2DSR_C2DS_SHIFT)) & CAAM_CC2DSR_C2DS_MASK)

#define CAAM_CC2DSR_C2CY_MASK                    (0x100000000U)
#define CAAM_CC2DSR_C2CY_SHIFT                   (32U)
/*! C2CY
 *  0b0..A write to the Class 2 Data Size Register did not cause a carry.
 *  0b1..A write to the Class 2 Data Size Register caused a carry.
 */
#define CAAM_CC2DSR_C2CY(x)                      (((uint64_t)(((uint64_t)(x)) << CAAM_CC2DSR_C2CY_SHIFT)) & CAAM_CC2DSR_C2CY_MASK)

#define CAAM_CC2DSR_NUMBITS_MASK                 (0xE000000000000000U)
#define CAAM_CC2DSR_NUMBITS_SHIFT                (61U)
#define CAAM_CC2DSR_NUMBITS(x)                   (((uint64_t)(((uint64_t)(x)) << CAAM_CC2DSR_NUMBITS_SHIFT)) & CAAM_CC2DSR_NUMBITS_MASK)
/*! @} */

/* The count of CAAM_CC2DSR */
#define CAAM_CC2DSR_COUNT                        (1U)

/*! @name CC2ICVSZR - CCB 0 Class 2 ICV Size Register */
/*! @{ */

#define CAAM_CC2ICVSZR_ICVSZ_MASK                (0xFU)
#define CAAM_CC2ICVSZR_ICVSZ_SHIFT               (0U)
#define CAAM_CC2ICVSZR_ICVSZ(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_CC2ICVSZR_ICVSZ_SHIFT)) & CAAM_CC2ICVSZR_ICVSZ_MASK)
/*! @} */

/* The count of CAAM_CC2ICVSZR */
#define CAAM_CC2ICVSZR_COUNT                     (1U)

/*! @name CC2CTXR - CCB 0 Class 2 Context Register Word 0..CCB 0 Class 2 Context Register Word 17 */
/*! @{ */

#define CAAM_CC2CTXR_C2CTXR_MASK                 (0xFFFFFFFFU)
#define CAAM_CC2CTXR_C2CTXR_SHIFT                (0U)
#define CAAM_CC2CTXR_C2CTXR(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_CC2CTXR_C2CTXR_SHIFT)) & CAAM_CC2CTXR_C2CTXR_MASK)
/*! @} */

/* The count of CAAM_CC2CTXR */
#define CAAM_CC2CTXR_COUNT                       (1U)

/* The count of CAAM_CC2CTXR */
#define CAAM_CC2CTXR_COUNT2                      (18U)

/*! @name CC2KEYR - CCB 0 Class 2 Key Register Word 0..CCB 0 Class 2 Key Register Word 31 */
/*! @{ */

#define CAAM_CC2KEYR_C2KEY_MASK                  (0xFFFFFFFFU)
#define CAAM_CC2KEYR_C2KEY_SHIFT                 (0U)
#define CAAM_CC2KEYR_C2KEY(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_CC2KEYR_C2KEY_SHIFT)) & CAAM_CC2KEYR_C2KEY_MASK)
/*! @} */

/* The count of CAAM_CC2KEYR */
#define CAAM_CC2KEYR_COUNT                       (1U)

/* The count of CAAM_CC2KEYR */
#define CAAM_CC2KEYR_COUNT2                      (32U)

/*! @name CFIFOSTA - CCB 0 FIFO Status Register */
/*! @{ */

#define CAAM_CFIFOSTA_DECOOQHEAD_MASK            (0xFFU)
#define CAAM_CFIFOSTA_DECOOQHEAD_SHIFT           (0U)
#define CAAM_CFIFOSTA_DECOOQHEAD(x)              (((uint32_t)(((uint32_t)(x)) << CAAM_CFIFOSTA_DECOOQHEAD_SHIFT)) & CAAM_CFIFOSTA_DECOOQHEAD_MASK)

#define CAAM_CFIFOSTA_DMAOQHEAD_MASK             (0xFF00U)
#define CAAM_CFIFOSTA_DMAOQHEAD_SHIFT            (8U)
#define CAAM_CFIFOSTA_DMAOQHEAD(x)               (((uint32_t)(((uint32_t)(x)) << CAAM_CFIFOSTA_DMAOQHEAD_SHIFT)) & CAAM_CFIFOSTA_DMAOQHEAD_MASK)

#define CAAM_CFIFOSTA_C2IQHEAD_MASK              (0xFF0000U)
#define CAAM_CFIFOSTA_C2IQHEAD_SHIFT             (16U)
#define CAAM_CFIFOSTA_C2IQHEAD(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_CFIFOSTA_C2IQHEAD_SHIFT)) & CAAM_CFIFOSTA_C2IQHEAD_MASK)

#define CAAM_CFIFOSTA_C1IQHEAD_MASK              (0xFF000000U)
#define CAAM_CFIFOSTA_C1IQHEAD_SHIFT             (24U)
#define CAAM_CFIFOSTA_C1IQHEAD(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_CFIFOSTA_C1IQHEAD_SHIFT)) & CAAM_CFIFOSTA_C1IQHEAD_MASK)
/*! @} */

/* The count of CAAM_CFIFOSTA */
#define CAAM_CFIFOSTA_COUNT                      (1U)

/*! @name CNFIFO - CCB 0 iNformation FIFO When STYPE != 10b */
/*! @{ */

#define CAAM_CNFIFO_DL_MASK                      (0xFFFU)
#define CAAM_CNFIFO_DL_SHIFT                     (0U)
#define CAAM_CNFIFO_DL(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_DL_SHIFT)) & CAAM_CNFIFO_DL_MASK)

#define CAAM_CNFIFO_AST_MASK                     (0x4000U)
#define CAAM_CNFIFO_AST_SHIFT                    (14U)
#define CAAM_CNFIFO_AST(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_AST_SHIFT)) & CAAM_CNFIFO_AST_MASK)

#define CAAM_CNFIFO_OC_MASK                      (0x8000U)
#define CAAM_CNFIFO_OC_SHIFT                     (15U)
/*! OC
 *  0b0..Allow the final word to be popped from the Output Data FIFO.
 *  0b1..Don't pop the final word from the Output Data FIFO.
 */
#define CAAM_CNFIFO_OC(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_OC_SHIFT)) & CAAM_CNFIFO_OC_MASK)

#define CAAM_CNFIFO_PTYPE_MASK                   (0x70000U)
#define CAAM_CNFIFO_PTYPE_SHIFT                  (16U)
#define CAAM_CNFIFO_PTYPE(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_PTYPE_SHIFT)) & CAAM_CNFIFO_PTYPE_MASK)

#define CAAM_CNFIFO_BND_MASK                     (0x80000U)
#define CAAM_CNFIFO_BND_SHIFT                    (19U)
/*! BND
 *  0b0..Don't pad.
 *  0b1..Pad to the next 16-byte boundary.
 */
#define CAAM_CNFIFO_BND(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_BND_SHIFT)) & CAAM_CNFIFO_BND_MASK)

#define CAAM_CNFIFO_DTYPE_MASK                   (0xF00000U)
#define CAAM_CNFIFO_DTYPE_SHIFT                  (20U)
#define CAAM_CNFIFO_DTYPE(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_DTYPE_SHIFT)) & CAAM_CNFIFO_DTYPE_MASK)

#define CAAM_CNFIFO_STYPE_MASK                   (0x3000000U)
#define CAAM_CNFIFO_STYPE_SHIFT                  (24U)
#define CAAM_CNFIFO_STYPE(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_STYPE_SHIFT)) & CAAM_CNFIFO_STYPE_MASK)

#define CAAM_CNFIFO_FC1_MASK                     (0x4000000U)
#define CAAM_CNFIFO_FC1_SHIFT                    (26U)
/*! FC1
 *  0b0..Don't flush Class 1 data.
 *  0b1..Flush Class 1 data.
 */
#define CAAM_CNFIFO_FC1(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_FC1_SHIFT)) & CAAM_CNFIFO_FC1_MASK)

#define CAAM_CNFIFO_FC2_MASK                     (0x8000000U)
#define CAAM_CNFIFO_FC2_SHIFT                    (27U)
/*! FC2
 *  0b0..Don't flush Class 2 data.
 *  0b1..Flush Class 2 data.
 */
#define CAAM_CNFIFO_FC2(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_FC2_SHIFT)) & CAAM_CNFIFO_FC2_MASK)

#define CAAM_CNFIFO_LC1_MASK                     (0x10000000U)
#define CAAM_CNFIFO_LC1_SHIFT                    (28U)
/*! LC1
 *  0b0..This is not the last Class 1 data.
 *  0b1..This is the last Class 1 data.
 */
#define CAAM_CNFIFO_LC1(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_LC1_SHIFT)) & CAAM_CNFIFO_LC1_MASK)

#define CAAM_CNFIFO_LC2_MASK                     (0x20000000U)
#define CAAM_CNFIFO_LC2_SHIFT                    (29U)
/*! LC2
 *  0b0..This is not the last Class 2 data.
 *  0b1..This is the last Class 2 data.
 */
#define CAAM_CNFIFO_LC2(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_LC2_SHIFT)) & CAAM_CNFIFO_LC2_MASK)

#define CAAM_CNFIFO_DEST_MASK                    (0xC0000000U)
#define CAAM_CNFIFO_DEST_SHIFT                   (30U)
/*! DEST
 *  0b00..DECO Alignment Block. If DTYPE == Eh, data sent to the DECO Alignment Block is dropped. This is used to
 *        skip over input data. An error is generated if a DTYPE other than Eh (drop) or Fh (message) is used with
 *        the DECO Alignment Block destination.
 *  0b01..Class 1.
 *  0b10..Class 2.
 *  0b11..Both Class 1 and Class 2.
 */
#define CAAM_CNFIFO_DEST(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_DEST_SHIFT)) & CAAM_CNFIFO_DEST_MASK)
/*! @} */

/* The count of CAAM_CNFIFO */
#define CAAM_CNFIFO_COUNT                        (1U)

/*! @name CNFIFO_2 - CCB 0 iNformation FIFO When STYPE == 10b */
/*! @{ */

#define CAAM_CNFIFO_2_PL_MASK                    (0x7FU)
#define CAAM_CNFIFO_2_PL_SHIFT                   (0U)
#define CAAM_CNFIFO_2_PL(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_2_PL_SHIFT)) & CAAM_CNFIFO_2_PL_MASK)

#define CAAM_CNFIFO_2_PS_MASK                    (0x400U)
#define CAAM_CNFIFO_2_PS_SHIFT                   (10U)
/*! PS
 *  0b0..C2 CHA snoops pad data from padding block.
 *  0b1..C2 CHA snoops pad data from OFIFO.
 */
#define CAAM_CNFIFO_2_PS(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_2_PS_SHIFT)) & CAAM_CNFIFO_2_PS_MASK)

#define CAAM_CNFIFO_2_BM_MASK                    (0x800U)
#define CAAM_CNFIFO_2_BM_SHIFT                   (11U)
/*! BM
 *  0b0..When padding, pad to power-of-2 boundary.
 *  0b1..When padding, pad to power-of-2 boundary minus 1 byte.
 */
#define CAAM_CNFIFO_2_BM(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_2_BM_SHIFT)) & CAAM_CNFIFO_2_BM_MASK)

#define CAAM_CNFIFO_2_PR_MASK                    (0x8000U)
#define CAAM_CNFIFO_2_PR_SHIFT                   (15U)
/*! PR
 *  0b0..No prediction resistance.
 *  0b1..Prediction resistance.
 */
#define CAAM_CNFIFO_2_PR(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_2_PR_SHIFT)) & CAAM_CNFIFO_2_PR_MASK)

#define CAAM_CNFIFO_2_PTYPE_MASK                 (0x70000U)
#define CAAM_CNFIFO_2_PTYPE_SHIFT                (16U)
/*! PTYPE
 *  0b000..All Zero.
 *  0b001..Random with nonzero bytes.
 *  0b010..Incremented (starting with 01h), followed by a byte containing the value N-1, i.e., if N==1, a single byte is output with value 0h.
 *  0b011..Random.
 *  0b100..All Zero with last byte containing the number of 0 bytes, i.e., if N==1, a single byte is output with value 0h.
 *  0b101..Random with nonzero bytes with last byte 0.
 *  0b110..N bytes of padding all containing the value N-1.
 *  0b111..Random with nonzero bytes, with the last byte containing the value N-1.
 */
#define CAAM_CNFIFO_2_PTYPE(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_2_PTYPE_SHIFT)) & CAAM_CNFIFO_2_PTYPE_MASK)

#define CAAM_CNFIFO_2_BND_MASK                   (0x80000U)
#define CAAM_CNFIFO_2_BND_SHIFT                  (19U)
/*! BND
 *  0b0..Don't add boundary padding.
 *  0b1..Add boundary padding.
 */
#define CAAM_CNFIFO_2_BND(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_2_BND_SHIFT)) & CAAM_CNFIFO_2_BND_MASK)

#define CAAM_CNFIFO_2_DTYPE_MASK                 (0xF00000U)
#define CAAM_CNFIFO_2_DTYPE_SHIFT                (20U)
#define CAAM_CNFIFO_2_DTYPE(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_2_DTYPE_SHIFT)) & CAAM_CNFIFO_2_DTYPE_MASK)

#define CAAM_CNFIFO_2_STYPE_MASK                 (0x3000000U)
#define CAAM_CNFIFO_2_STYPE_SHIFT                (24U)
#define CAAM_CNFIFO_2_STYPE(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_2_STYPE_SHIFT)) & CAAM_CNFIFO_2_STYPE_MASK)

#define CAAM_CNFIFO_2_FC1_MASK                   (0x4000000U)
#define CAAM_CNFIFO_2_FC1_SHIFT                  (26U)
/*! FC1
 *  0b0..Don't flush the Class 1 data.
 *  0b1..Flush the Class 1 data.
 */
#define CAAM_CNFIFO_2_FC1(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_2_FC1_SHIFT)) & CAAM_CNFIFO_2_FC1_MASK)

#define CAAM_CNFIFO_2_FC2_MASK                   (0x8000000U)
#define CAAM_CNFIFO_2_FC2_SHIFT                  (27U)
/*! FC2
 *  0b0..Don't flush the Class 2 data.
 *  0b1..Flush the Class 2 data.
 */
#define CAAM_CNFIFO_2_FC2(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_2_FC2_SHIFT)) & CAAM_CNFIFO_2_FC2_MASK)

#define CAAM_CNFIFO_2_LC1_MASK                   (0x10000000U)
#define CAAM_CNFIFO_2_LC1_SHIFT                  (28U)
/*! LC1
 *  0b0..This is not the last Class 1 data.
 *  0b1..This is the last Class 1 data.
 */
#define CAAM_CNFIFO_2_LC1(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_2_LC1_SHIFT)) & CAAM_CNFIFO_2_LC1_MASK)

#define CAAM_CNFIFO_2_LC2_MASK                   (0x20000000U)
#define CAAM_CNFIFO_2_LC2_SHIFT                  (29U)
/*! LC2
 *  0b0..This is not the last Class 2 data.
 *  0b1..This is the last Class 2 data.
 */
#define CAAM_CNFIFO_2_LC2(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_2_LC2_SHIFT)) & CAAM_CNFIFO_2_LC2_MASK)

#define CAAM_CNFIFO_2_DEST_MASK                  (0xC0000000U)
#define CAAM_CNFIFO_2_DEST_SHIFT                 (30U)
/*! DEST
 *  0b00..DECO Alignment Block. If DTYPE is Eh, data sent to the DECO Alignment Block is dropped. This is used to
 *        skip over input data. An error is generated if a DTYPE other than Eh (drop) or Fh (message) is used with
 *        the DECO Alignment Block destination.
 *  0b01..Class 1.
 *  0b10..Class 2.
 *  0b11..Both Class 1 and Class 2.
 */
#define CAAM_CNFIFO_2_DEST(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_CNFIFO_2_DEST_SHIFT)) & CAAM_CNFIFO_2_DEST_MASK)
/*! @} */

/* The count of CAAM_CNFIFO_2 */
#define CAAM_CNFIFO_2_COUNT                      (1U)

/*! @name CIFIFO - CCB 0 Input Data FIFO */
/*! @{ */

#define CAAM_CIFIFO_IFIFO_MASK                   (0xFFFFFFFFU)
#define CAAM_CIFIFO_IFIFO_SHIFT                  (0U)
#define CAAM_CIFIFO_IFIFO(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_CIFIFO_IFIFO_SHIFT)) & CAAM_CIFIFO_IFIFO_MASK)
/*! @} */

/* The count of CAAM_CIFIFO */
#define CAAM_CIFIFO_COUNT                        (1U)

/*! @name COFIFO - CCB 0 Output Data FIFO */
/*! @{ */

#define CAAM_COFIFO_OFIFO_MASK                   (0xFFFFFFFFFFFFFFFFU)
#define CAAM_COFIFO_OFIFO_SHIFT                  (0U)
#define CAAM_COFIFO_OFIFO(x)                     (((uint64_t)(((uint64_t)(x)) << CAAM_COFIFO_OFIFO_SHIFT)) & CAAM_COFIFO_OFIFO_MASK)
/*! @} */

/* The count of CAAM_COFIFO */
#define CAAM_COFIFO_COUNT                        (1U)

/*! @name DJQCR_MS - DECO0 Job Queue Control Register, most-significant half */
/*! @{ */

#define CAAM_DJQCR_MS_ID_MASK                    (0x7U)
#define CAAM_DJQCR_MS_ID_SHIFT                   (0U)
#define CAAM_DJQCR_MS_ID(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_DJQCR_MS_ID_SHIFT)) & CAAM_DJQCR_MS_ID_MASK)

#define CAAM_DJQCR_MS_SRC_MASK                   (0x700U)
#define CAAM_DJQCR_MS_SRC_SHIFT                  (8U)
/*! SRC
 *  0b000..Job Ring 0
 *  0b001..Job Ring 1
 *  0b010..Job Ring 2
 *  0b011..Job Ring 3
 *  0b100..RTIC
 *  0b101..Reserved
 *  0b110..Reserved
 *  0b111..Reserved
 */
#define CAAM_DJQCR_MS_SRC(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_DJQCR_MS_SRC_SHIFT)) & CAAM_DJQCR_MS_SRC_MASK)

#define CAAM_DJQCR_MS_AMTD_MASK                  (0x8000U)
#define CAAM_DJQCR_MS_AMTD_SHIFT                 (15U)
/*! AMTD
 *  0b0..The Allowed Make Trusted Descriptor bit was NOT set.
 *  0b1..The Allowed Make Trusted Descriptor bit was set.
 */
#define CAAM_DJQCR_MS_AMTD(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_DJQCR_MS_AMTD_SHIFT)) & CAAM_DJQCR_MS_AMTD_MASK)

#define CAAM_DJQCR_MS_SOB_MASK                   (0x10000U)
#define CAAM_DJQCR_MS_SOB_SHIFT                  (16U)
/*! SOB
 *  0b0..Shared Descriptor has NOT been loaded.
 *  0b1..Shared Descriptor HAS been loaded.
 */
#define CAAM_DJQCR_MS_SOB(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_DJQCR_MS_SOB_SHIFT)) & CAAM_DJQCR_MS_SOB_MASK)

#define CAAM_DJQCR_MS_DWS_MASK                   (0x80000U)
#define CAAM_DJQCR_MS_DWS_SHIFT                  (19U)
/*! DWS
 *  0b0..Double Word Swap is NOT set.
 *  0b1..Double Word Swap is set.
 */
#define CAAM_DJQCR_MS_DWS(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_DJQCR_MS_DWS_SHIFT)) & CAAM_DJQCR_MS_DWS_MASK)

#define CAAM_DJQCR_MS_SHR_FROM_MASK              (0x7000000U)
#define CAAM_DJQCR_MS_SHR_FROM_SHIFT             (24U)
#define CAAM_DJQCR_MS_SHR_FROM(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_DJQCR_MS_SHR_FROM_SHIFT)) & CAAM_DJQCR_MS_SHR_FROM_MASK)

#define CAAM_DJQCR_MS_ILE_MASK                   (0x8000000U)
#define CAAM_DJQCR_MS_ILE_SHIFT                  (27U)
/*! ILE
 *  0b0..No byte-swapping is performed for immediate data transferred to or from the Descriptor Buffer.
 *  0b1..Byte-swapping is performed for immediate data transferred to or from the Descriptor Buffer.
 */
#define CAAM_DJQCR_MS_ILE(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_DJQCR_MS_ILE_SHIFT)) & CAAM_DJQCR_MS_ILE_MASK)

#define CAAM_DJQCR_MS_FOUR_MASK                  (0x10000000U)
#define CAAM_DJQCR_MS_FOUR_SHIFT                 (28U)
/*! FOUR
 *  0b0..DECO has not been given at least four words of the descriptor.
 *  0b1..DECO has been given at least four words of the descriptor.
 */
#define CAAM_DJQCR_MS_FOUR(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_DJQCR_MS_FOUR_SHIFT)) & CAAM_DJQCR_MS_FOUR_MASK)

#define CAAM_DJQCR_MS_WHL_MASK                   (0x20000000U)
#define CAAM_DJQCR_MS_WHL_SHIFT                  (29U)
/*! WHL
 *  0b0..DECO has not been given the whole descriptor.
 *  0b1..DECO has been given the whole descriptor.
 */
#define CAAM_DJQCR_MS_WHL(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_DJQCR_MS_WHL_SHIFT)) & CAAM_DJQCR_MS_WHL_MASK)

#define CAAM_DJQCR_MS_SING_MASK                  (0x40000000U)
#define CAAM_DJQCR_MS_SING_SHIFT                 (30U)
/*! SING
 *  0b0..Do not tell DECO to execute the descriptor in single-step mode.
 *  0b1..Tell DECO to execute the descriptor in single-step mode.
 */
#define CAAM_DJQCR_MS_SING(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_DJQCR_MS_SING_SHIFT)) & CAAM_DJQCR_MS_SING_MASK)

#define CAAM_DJQCR_MS_STEP_MASK                  (0x80000000U)
#define CAAM_DJQCR_MS_STEP_SHIFT                 (31U)
/*! STEP
 *  0b0..DECO has not been told to execute the next command in the descriptor.
 *  0b1..DECO has been told to execute the next command in the descriptor.
 */
#define CAAM_DJQCR_MS_STEP(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_DJQCR_MS_STEP_SHIFT)) & CAAM_DJQCR_MS_STEP_MASK)
/*! @} */

/* The count of CAAM_DJQCR_MS */
#define CAAM_DJQCR_MS_COUNT                      (1U)

/*! @name DJQCR_LS - DECO0 Job Queue Control Register, least-significant half */
/*! @{ */

#define CAAM_DJQCR_LS_CMD_MASK                   (0xFFFFFFFFU)
#define CAAM_DJQCR_LS_CMD_SHIFT                  (0U)
#define CAAM_DJQCR_LS_CMD(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_DJQCR_LS_CMD_SHIFT)) & CAAM_DJQCR_LS_CMD_MASK)
/*! @} */

/* The count of CAAM_DJQCR_LS */
#define CAAM_DJQCR_LS_COUNT                      (1U)

/*! @name DDAR - DECO0 Descriptor Address Register */
/*! @{ */

#define CAAM_DDAR_DPTR_MASK                      (0xFFFFFFFFFU)
#define CAAM_DDAR_DPTR_SHIFT                     (0U)
#define CAAM_DDAR_DPTR(x)                        (((uint64_t)(((uint64_t)(x)) << CAAM_DDAR_DPTR_SHIFT)) & CAAM_DDAR_DPTR_MASK)
/*! @} */

/* The count of CAAM_DDAR */
#define CAAM_DDAR_COUNT                          (1U)

/*! @name DOPSTA_MS - DECO0 Operation Status Register, most-significant half */
/*! @{ */

#define CAAM_DOPSTA_MS_STATUS_MASK               (0xFFU)
#define CAAM_DOPSTA_MS_STATUS_SHIFT              (0U)
#define CAAM_DOPSTA_MS_STATUS(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_DOPSTA_MS_STATUS_SHIFT)) & CAAM_DOPSTA_MS_STATUS_MASK)

#define CAAM_DOPSTA_MS_COMMAND_INDEX_MASK        (0x7F00U)
#define CAAM_DOPSTA_MS_COMMAND_INDEX_SHIFT       (8U)
#define CAAM_DOPSTA_MS_COMMAND_INDEX(x)          (((uint32_t)(((uint32_t)(x)) << CAAM_DOPSTA_MS_COMMAND_INDEX_SHIFT)) & CAAM_DOPSTA_MS_COMMAND_INDEX_MASK)

#define CAAM_DOPSTA_MS_NLJ_MASK                  (0x8000000U)
#define CAAM_DOPSTA_MS_NLJ_SHIFT                 (27U)
/*! NLJ
 *  0b0..The original job descriptor running in this DECO has not caused another job descriptor to be executed.
 *  0b1..The original job descriptor running in this DECO has caused another job descriptor to be executed.
 */
#define CAAM_DOPSTA_MS_NLJ(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_DOPSTA_MS_NLJ_SHIFT)) & CAAM_DOPSTA_MS_NLJ_MASK)

#define CAAM_DOPSTA_MS_STATUS_TYPE_MASK          (0xF0000000U)
#define CAAM_DOPSTA_MS_STATUS_TYPE_SHIFT         (28U)
/*! STATUS_TYPE
 *  0b0000..no error
 *  0b0001..DMA error
 *  0b0010..CCB error
 *  0b0011..Jump Halt User Status
 *  0b0100..DECO error
 *  0b0101, 0b0110..Reserved
 *  0b0111..Jump Halt Condition Code
 */
#define CAAM_DOPSTA_MS_STATUS_TYPE(x)            (((uint32_t)(((uint32_t)(x)) << CAAM_DOPSTA_MS_STATUS_TYPE_SHIFT)) & CAAM_DOPSTA_MS_STATUS_TYPE_MASK)
/*! @} */

/* The count of CAAM_DOPSTA_MS */
#define CAAM_DOPSTA_MS_COUNT                     (1U)

/*! @name DOPSTA_LS - DECO0 Operation Status Register, least-significant half */
/*! @{ */

#define CAAM_DOPSTA_LS_OUT_CT_MASK               (0xFFFFFFFFU)
#define CAAM_DOPSTA_LS_OUT_CT_SHIFT              (0U)
#define CAAM_DOPSTA_LS_OUT_CT(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_DOPSTA_LS_OUT_CT_SHIFT)) & CAAM_DOPSTA_LS_OUT_CT_MASK)
/*! @} */

/* The count of CAAM_DOPSTA_LS */
#define CAAM_DOPSTA_LS_COUNT                     (1U)

/*! @name DPDIDSR - DECO0 Primary DID Status Register */
/*! @{ */

#define CAAM_DPDIDSR_PRIM_DID_MASK               (0xFU)
#define CAAM_DPDIDSR_PRIM_DID_SHIFT              (0U)
#define CAAM_DPDIDSR_PRIM_DID(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_DPDIDSR_PRIM_DID_SHIFT)) & CAAM_DPDIDSR_PRIM_DID_MASK)

#define CAAM_DPDIDSR_PRIM_ICID_MASK              (0x3FF80000U)
#define CAAM_DPDIDSR_PRIM_ICID_SHIFT             (19U)
#define CAAM_DPDIDSR_PRIM_ICID(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_DPDIDSR_PRIM_ICID_SHIFT)) & CAAM_DPDIDSR_PRIM_ICID_MASK)
/*! @} */

/* The count of CAAM_DPDIDSR */
#define CAAM_DPDIDSR_COUNT                       (1U)

/*! @name DODIDSR - DECO0 Output DID Status Register */
/*! @{ */

#define CAAM_DODIDSR_OUT_DID_MASK                (0xFU)
#define CAAM_DODIDSR_OUT_DID_SHIFT               (0U)
#define CAAM_DODIDSR_OUT_DID(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_DODIDSR_OUT_DID_SHIFT)) & CAAM_DODIDSR_OUT_DID_MASK)

#define CAAM_DODIDSR_OUT_ICID_MASK               (0x3FF80000U)
#define CAAM_DODIDSR_OUT_ICID_SHIFT              (19U)
#define CAAM_DODIDSR_OUT_ICID(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_DODIDSR_OUT_ICID_SHIFT)) & CAAM_DODIDSR_OUT_ICID_MASK)
/*! @} */

/* The count of CAAM_DODIDSR */
#define CAAM_DODIDSR_COUNT                       (1U)

/*! @name DMTH_MS - DECO0 Math Register 0_MS..DECO0 Math Register 3_MS */
/*! @{ */

#define CAAM_DMTH_MS_MATH_MS_MASK                (0xFFFFFFFFU)
#define CAAM_DMTH_MS_MATH_MS_SHIFT               (0U)
#define CAAM_DMTH_MS_MATH_MS(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_DMTH_MS_MATH_MS_SHIFT)) & CAAM_DMTH_MS_MATH_MS_MASK)
/*! @} */

/* The count of CAAM_DMTH_MS */
#define CAAM_DMTH_MS_COUNT                       (1U)

/* The count of CAAM_DMTH_MS */
#define CAAM_DMTH_MS_COUNT2                      (4U)

/*! @name DMTH_LS - DECO0 Math Register 0_LS..DECO0 Math Register 3_LS */
/*! @{ */

#define CAAM_DMTH_LS_MATH_LS_MASK                (0xFFFFFFFFU)
#define CAAM_DMTH_LS_MATH_LS_SHIFT               (0U)
#define CAAM_DMTH_LS_MATH_LS(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_DMTH_LS_MATH_LS_SHIFT)) & CAAM_DMTH_LS_MATH_LS_MASK)
/*! @} */

/* The count of CAAM_DMTH_LS */
#define CAAM_DMTH_LS_COUNT                       (1U)

/* The count of CAAM_DMTH_LS */
#define CAAM_DMTH_LS_COUNT2                      (4U)

/*! @name DGTR_0 - DECO0 Gather Table Register 0 Word 0 */
/*! @{ */

#define CAAM_DGTR_0_ADDRESS_POINTER_MASK         (0xFU)
#define CAAM_DGTR_0_ADDRESS_POINTER_SHIFT        (0U)
/*! ADDRESS_POINTER - most-significant bits of memory address pointed to by table entry */
#define CAAM_DGTR_0_ADDRESS_POINTER(x)           (((uint32_t)(((uint32_t)(x)) << CAAM_DGTR_0_ADDRESS_POINTER_SHIFT)) & CAAM_DGTR_0_ADDRESS_POINTER_MASK)
/*! @} */

/* The count of CAAM_DGTR_0 */
#define CAAM_DGTR_0_COUNT                        (1U)

/* The count of CAAM_DGTR_0 */
#define CAAM_DGTR_0_COUNT2                       (1U)

/*! @name DGTR_1 - DECO0 Gather Table Register 0 Word 1 */
/*! @{ */

#define CAAM_DGTR_1_ADDRESS_POINTER_MASK         (0xFFFFFFFFU)
#define CAAM_DGTR_1_ADDRESS_POINTER_SHIFT        (0U)
#define CAAM_DGTR_1_ADDRESS_POINTER(x)           (((uint32_t)(((uint32_t)(x)) << CAAM_DGTR_1_ADDRESS_POINTER_SHIFT)) & CAAM_DGTR_1_ADDRESS_POINTER_MASK)
/*! @} */

/* The count of CAAM_DGTR_1 */
#define CAAM_DGTR_1_COUNT                        (1U)

/* The count of CAAM_DGTR_1 */
#define CAAM_DGTR_1_COUNT2                       (1U)

/*! @name DGTR_2 - DECO0 Gather Table Register 0 Word 2 */
/*! @{ */

#define CAAM_DGTR_2_Length_MASK                  (0x3FFFFFFFU)
#define CAAM_DGTR_2_Length_SHIFT                 (0U)
#define CAAM_DGTR_2_Length(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_DGTR_2_Length_SHIFT)) & CAAM_DGTR_2_Length_MASK)

#define CAAM_DGTR_2_F_MASK                       (0x40000000U)
#define CAAM_DGTR_2_F_SHIFT                      (30U)
/*! F
 *  0b0..This is not the last entry of the SGT.
 *  0b1..This is the last entry of the SGT.
 */
#define CAAM_DGTR_2_F(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_DGTR_2_F_SHIFT)) & CAAM_DGTR_2_F_MASK)

#define CAAM_DGTR_2_E_MASK                       (0x80000000U)
#define CAAM_DGTR_2_E_SHIFT                      (31U)
/*! E
 *  0b0..Address Pointer points to a memory buffer.
 *  0b1..Address Pointer points to a Scatter/Gather Table Entry.
 */
#define CAAM_DGTR_2_E(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_DGTR_2_E_SHIFT)) & CAAM_DGTR_2_E_MASK)
/*! @} */

/* The count of CAAM_DGTR_2 */
#define CAAM_DGTR_2_COUNT                        (1U)

/* The count of CAAM_DGTR_2 */
#define CAAM_DGTR_2_COUNT2                       (1U)

/*! @name DGTR_3 - DECO0 Gather Table Register 0 Word 3 */
/*! @{ */

#define CAAM_DGTR_3_Offset_MASK                  (0x1FFFU)
#define CAAM_DGTR_3_Offset_SHIFT                 (0U)
#define CAAM_DGTR_3_Offset(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_DGTR_3_Offset_SHIFT)) & CAAM_DGTR_3_Offset_MASK)
/*! @} */

/* The count of CAAM_DGTR_3 */
#define CAAM_DGTR_3_COUNT                        (1U)

/* The count of CAAM_DGTR_3 */
#define CAAM_DGTR_3_COUNT2                       (1U)

/*! @name DSTR_0 - DECO0 Scatter Table Register 0 Word 0 */
/*! @{ */

#define CAAM_DSTR_0_ADDRESS_POINTER_MASK         (0xFU)
#define CAAM_DSTR_0_ADDRESS_POINTER_SHIFT        (0U)
/*! ADDRESS_POINTER - most-significant bits of memory address pointed to by table entry */
#define CAAM_DSTR_0_ADDRESS_POINTER(x)           (((uint32_t)(((uint32_t)(x)) << CAAM_DSTR_0_ADDRESS_POINTER_SHIFT)) & CAAM_DSTR_0_ADDRESS_POINTER_MASK)
/*! @} */

/* The count of CAAM_DSTR_0 */
#define CAAM_DSTR_0_COUNT                        (1U)

/* The count of CAAM_DSTR_0 */
#define CAAM_DSTR_0_COUNT2                       (1U)

/*! @name DSTR_1 - DECO0 Scatter Table Register 0 Word 1 */
/*! @{ */

#define CAAM_DSTR_1_ADDRESS_POINTER_MASK         (0xFFFFFFFFU)
#define CAAM_DSTR_1_ADDRESS_POINTER_SHIFT        (0U)
#define CAAM_DSTR_1_ADDRESS_POINTER(x)           (((uint32_t)(((uint32_t)(x)) << CAAM_DSTR_1_ADDRESS_POINTER_SHIFT)) & CAAM_DSTR_1_ADDRESS_POINTER_MASK)
/*! @} */

/* The count of CAAM_DSTR_1 */
#define CAAM_DSTR_1_COUNT                        (1U)

/* The count of CAAM_DSTR_1 */
#define CAAM_DSTR_1_COUNT2                       (1U)

/*! @name DSTR_2 - DECO0 Scatter Table Register 0 Word 2 */
/*! @{ */

#define CAAM_DSTR_2_Length_MASK                  (0x3FFFFFFFU)
#define CAAM_DSTR_2_Length_SHIFT                 (0U)
#define CAAM_DSTR_2_Length(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_DSTR_2_Length_SHIFT)) & CAAM_DSTR_2_Length_MASK)

#define CAAM_DSTR_2_F_MASK                       (0x40000000U)
#define CAAM_DSTR_2_F_SHIFT                      (30U)
/*! F
 *  0b0..This is not the last entry of the SGT.
 *  0b1..This is the last entry of the SGT.
 */
#define CAAM_DSTR_2_F(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_DSTR_2_F_SHIFT)) & CAAM_DSTR_2_F_MASK)

#define CAAM_DSTR_2_E_MASK                       (0x80000000U)
#define CAAM_DSTR_2_E_SHIFT                      (31U)
/*! E
 *  0b0..Address Pointer points to a memory buffer.
 *  0b1..Address Pointer points to a Scatter/Gather Table Entry.
 */
#define CAAM_DSTR_2_E(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_DSTR_2_E_SHIFT)) & CAAM_DSTR_2_E_MASK)
/*! @} */

/* The count of CAAM_DSTR_2 */
#define CAAM_DSTR_2_COUNT                        (1U)

/* The count of CAAM_DSTR_2 */
#define CAAM_DSTR_2_COUNT2                       (1U)

/*! @name DSTR_3 - DECO0 Scatter Table Register 0 Word 3 */
/*! @{ */

#define CAAM_DSTR_3_Offset_MASK                  (0x1FFFU)
#define CAAM_DSTR_3_Offset_SHIFT                 (0U)
#define CAAM_DSTR_3_Offset(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_DSTR_3_Offset_SHIFT)) & CAAM_DSTR_3_Offset_MASK)
/*! @} */

/* The count of CAAM_DSTR_3 */
#define CAAM_DSTR_3_COUNT                        (1U)

/* The count of CAAM_DSTR_3 */
#define CAAM_DSTR_3_COUNT2                       (1U)

/*! @name DDESB - DECO0 Descriptor Buffer Word 0..DECO0 Descriptor Buffer Word 63 */
/*! @{ */

#define CAAM_DDESB_DESBW_MASK                    (0xFFFFFFFFU)
#define CAAM_DDESB_DESBW_SHIFT                   (0U)
#define CAAM_DDESB_DESBW(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_DDESB_DESBW_SHIFT)) & CAAM_DDESB_DESBW_MASK)
/*! @} */

/* The count of CAAM_DDESB */
#define CAAM_DDESB_COUNT                         (1U)

/* The count of CAAM_DDESB */
#define CAAM_DDESB_COUNT2                        (64U)

/*! @name DDJR - DECO0 Debug Job Register */
/*! @{ */

#define CAAM_DDJR_ID_MASK                        (0x7U)
#define CAAM_DDJR_ID_SHIFT                       (0U)
#define CAAM_DDJR_ID(x)                          (((uint32_t)(((uint32_t)(x)) << CAAM_DDJR_ID_SHIFT)) & CAAM_DDJR_ID_MASK)

#define CAAM_DDJR_SRC_MASK                       (0x700U)
#define CAAM_DDJR_SRC_SHIFT                      (8U)
/*! SRC
 *  0b000..Job Ring 0
 *  0b001..Job Ring 1
 *  0b010..Job Ring 2
 *  0b011..Job Ring 3
 *  0b100..RTIC
 *  0b101, 0b110, 0b111..Reserved
 */
#define CAAM_DDJR_SRC(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_DDJR_SRC_SHIFT)) & CAAM_DDJR_SRC_MASK)

#define CAAM_DDJR_JDDS_MASK                      (0x4000U)
#define CAAM_DDJR_JDDS_SHIFT                     (14U)
/*! JDDS
 *  0b0..Non-SEQ DID
 *  0b1..SEQ DID
 */
#define CAAM_DDJR_JDDS(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_DDJR_JDDS_SHIFT)) & CAAM_DDJR_JDDS_MASK)

#define CAAM_DDJR_AMTD_MASK                      (0x8000U)
#define CAAM_DDJR_AMTD_SHIFT                     (15U)
/*! AMTD
 *  0b0..The Allowed Make Trusted Descriptor bit was NOT set.
 *  0b1..The Allowed Make Trusted Descriptor bit was set.
 */
#define CAAM_DDJR_AMTD(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_DDJR_AMTD_SHIFT)) & CAAM_DDJR_AMTD_MASK)

#define CAAM_DDJR_GSD_MASK                       (0x10000U)
#define CAAM_DDJR_GSD_SHIFT                      (16U)
/*! GSD
 *  0b0..Shared Descriptor was NOT obtained from another DECO.
 *  0b1..Shared Descriptor was obtained from another DECO.
 */
#define CAAM_DDJR_GSD(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_DDJR_GSD_SHIFT)) & CAAM_DDJR_GSD_MASK)

#define CAAM_DDJR_DWS_MASK                       (0x80000U)
#define CAAM_DDJR_DWS_SHIFT                      (19U)
/*! DWS
 *  0b0..Double Word Swap is NOT set.
 *  0b1..Double Word Swap is set.
 */
#define CAAM_DDJR_DWS(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_DDJR_DWS_SHIFT)) & CAAM_DDJR_DWS_MASK)

#define CAAM_DDJR_SHR_FROM_MASK                  (0x7000000U)
#define CAAM_DDJR_SHR_FROM_SHIFT                 (24U)
#define CAAM_DDJR_SHR_FROM(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_DDJR_SHR_FROM_SHIFT)) & CAAM_DDJR_SHR_FROM_MASK)

#define CAAM_DDJR_ILE_MASK                       (0x8000000U)
#define CAAM_DDJR_ILE_SHIFT                      (27U)
/*! ILE
 *  0b0..No byte-swapping is performed for immediate data transferred to or from the Descriptor Buffer.
 *  0b1..Byte-swapping is performed for immediate data transferred to or from the Descriptor Buffer.
 */
#define CAAM_DDJR_ILE(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_DDJR_ILE_SHIFT)) & CAAM_DDJR_ILE_MASK)

#define CAAM_DDJR_FOUR_MASK                      (0x10000000U)
#define CAAM_DDJR_FOUR_SHIFT                     (28U)
/*! FOUR
 *  0b0..DECO has not been given at least four words of the descriptor.
 *  0b1..DECO has been given at least four words of the descriptor.
 */
#define CAAM_DDJR_FOUR(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_DDJR_FOUR_SHIFT)) & CAAM_DDJR_FOUR_MASK)

#define CAAM_DDJR_WHL_MASK                       (0x20000000U)
#define CAAM_DDJR_WHL_SHIFT                      (29U)
/*! WHL
 *  0b0..DECO has not been given the whole descriptor.
 *  0b1..DECO has been given the whole descriptor.
 */
#define CAAM_DDJR_WHL(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_DDJR_WHL_SHIFT)) & CAAM_DDJR_WHL_MASK)

#define CAAM_DDJR_SING_MASK                      (0x40000000U)
#define CAAM_DDJR_SING_SHIFT                     (30U)
/*! SING
 *  0b0..DECO has not been told to execute the descriptor in single-step mode.
 *  0b1..DECO has been told to execute the descriptor in single-step mode.
 */
#define CAAM_DDJR_SING(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_DDJR_SING_SHIFT)) & CAAM_DDJR_SING_MASK)

#define CAAM_DDJR_STEP_MASK                      (0x80000000U)
#define CAAM_DDJR_STEP_SHIFT                     (31U)
/*! STEP
 *  0b0..DECO has not been told to execute the next command in the descriptor.
 *  0b1..DECO has been told to execute the next command in the descriptor.
 */
#define CAAM_DDJR_STEP(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_DDJR_STEP_SHIFT)) & CAAM_DDJR_STEP_MASK)
/*! @} */

/* The count of CAAM_DDJR */
#define CAAM_DDJR_COUNT                          (1U)

/*! @name DDDR - DECO0 Debug DECO Register */
/*! @{ */

#define CAAM_DDDR_CT_MASK                        (0x1U)
#define CAAM_DDDR_CT_SHIFT                       (0U)
/*! CT
 *  0b0..This DECO is NOTcurrently generating the signature of a Trusted Descriptor.
 *  0b1..This DECO is currently generating the signature of a Trusted Descriptor.
 */
#define CAAM_DDDR_CT(x)                          (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_CT_SHIFT)) & CAAM_DDDR_CT_MASK)

#define CAAM_DDDR_BRB_MASK                       (0x2U)
#define CAAM_DDDR_BRB_SHIFT                      (1U)
/*! BRB
 *  0b0..The READ machine in the Burster is not busy.
 *  0b1..The READ machine in the Burster is busy.
 */
#define CAAM_DDDR_BRB(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_BRB_SHIFT)) & CAAM_DDDR_BRB_MASK)

#define CAAM_DDDR_BWB_MASK                       (0x4U)
#define CAAM_DDDR_BWB_SHIFT                      (2U)
/*! BWB
 *  0b0..The WRITE machine in the Burster is not busy.
 *  0b1..The WRITE machine in the Burster is busy.
 */
#define CAAM_DDDR_BWB(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_BWB_SHIFT)) & CAAM_DDDR_BWB_MASK)

#define CAAM_DDDR_NC_MASK                        (0x8U)
#define CAAM_DDDR_NC_SHIFT                       (3U)
/*! NC
 *  0b0..This DECO is currently executing a command.
 *  0b1..This DECO is not currently executing a command.
 */
#define CAAM_DDDR_NC(x)                          (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_NC_SHIFT)) & CAAM_DDDR_NC_MASK)

#define CAAM_DDDR_CSA_MASK                       (0x10U)
#define CAAM_DDDR_CSA_SHIFT                      (4U)
#define CAAM_DDDR_CSA(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_CSA_SHIFT)) & CAAM_DDDR_CSA_MASK)

#define CAAM_DDDR_CMD_STAGE_MASK                 (0xE0U)
#define CAAM_DDDR_CMD_STAGE_SHIFT                (5U)
#define CAAM_DDDR_CMD_STAGE(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_CMD_STAGE_SHIFT)) & CAAM_DDDR_CMD_STAGE_MASK)

#define CAAM_DDDR_CMD_INDEX_MASK                 (0x3F00U)
#define CAAM_DDDR_CMD_INDEX_SHIFT                (8U)
#define CAAM_DDDR_CMD_INDEX(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_CMD_INDEX_SHIFT)) & CAAM_DDDR_CMD_INDEX_MASK)

#define CAAM_DDDR_NLJ_MASK                       (0x4000U)
#define CAAM_DDDR_NLJ_SHIFT                      (14U)
/*! NLJ
 *  0b0..The original job descriptor running in this DECO has not caused another job descriptor to be executed.
 *  0b1..The original job descriptor running in this DECO has caused another job descriptor to be executed.
 */
#define CAAM_DDDR_NLJ(x)                         (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_NLJ_SHIFT)) & CAAM_DDDR_NLJ_MASK)

#define CAAM_DDDR_PTCL_RUN_MASK                  (0x8000U)
#define CAAM_DDDR_PTCL_RUN_SHIFT                 (15U)
/*! PTCL_RUN
 *  0b0..No protocol is running in this DECO.
 *  0b1..A protocol is running in this DECO.
 */
#define CAAM_DDDR_PTCL_RUN(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_PTCL_RUN_SHIFT)) & CAAM_DDDR_PTCL_RUN_MASK)

#define CAAM_DDDR_PDB_STALL_MASK                 (0x30000U)
#define CAAM_DDDR_PDB_STALL_SHIFT                (16U)
#define CAAM_DDDR_PDB_STALL(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_PDB_STALL_SHIFT)) & CAAM_DDDR_PDB_STALL_MASK)

#define CAAM_DDDR_PDB_WB_ST_MASK                 (0xC0000U)
#define CAAM_DDDR_PDB_WB_ST_SHIFT                (18U)
#define CAAM_DDDR_PDB_WB_ST(x)                   (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_PDB_WB_ST_SHIFT)) & CAAM_DDDR_PDB_WB_ST_MASK)

#define CAAM_DDDR_DECO_STATE_MASK                (0xF00000U)
#define CAAM_DDDR_DECO_STATE_SHIFT               (20U)
#define CAAM_DDDR_DECO_STATE(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_DECO_STATE_SHIFT)) & CAAM_DDDR_DECO_STATE_MASK)

#define CAAM_DDDR_NSEQLSEL_MASK                  (0x3000000U)
#define CAAM_DDDR_NSEQLSEL_SHIFT                 (24U)
/*! NSEQLSEL
 *  0b01..SEQ DID
 *  0b10..Non-SEQ DID
 *  0b11..Trusted DID
 */
#define CAAM_DDDR_NSEQLSEL(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_NSEQLSEL_SHIFT)) & CAAM_DDDR_NSEQLSEL_MASK)

#define CAAM_DDDR_SEQLSEL_MASK                   (0xC000000U)
#define CAAM_DDDR_SEQLSEL_SHIFT                  (26U)
/*! SEQLSEL
 *  0b01..SEQ DID
 *  0b10..Non-SEQ DID
 *  0b11..Trusted DID
 */
#define CAAM_DDDR_SEQLSEL(x)                     (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_SEQLSEL_SHIFT)) & CAAM_DDDR_SEQLSEL_MASK)

#define CAAM_DDDR_TRCT_MASK                      (0x30000000U)
#define CAAM_DDDR_TRCT_SHIFT                     (28U)
#define CAAM_DDDR_TRCT(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_TRCT_SHIFT)) & CAAM_DDDR_TRCT_MASK)

#define CAAM_DDDR_SD_MASK                        (0x40000000U)
#define CAAM_DDDR_SD_SHIFT                       (30U)
/*! SD
 *  0b0..This DECO has not received a shared descriptor from another DECO.
 *  0b1..This DECO has received a shared descriptor from another DECO.
 */
#define CAAM_DDDR_SD(x)                          (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_SD_SHIFT)) & CAAM_DDDR_SD_MASK)

#define CAAM_DDDR_VALID_MASK                     (0x80000000U)
#define CAAM_DDDR_VALID_SHIFT                    (31U)
/*! VALID
 *  0b0..No descriptor is currently running in this DECO.
 *  0b1..There is currently a descriptor running in this DECO.
 */
#define CAAM_DDDR_VALID(x)                       (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_VALID_SHIFT)) & CAAM_DDDR_VALID_MASK)
/*! @} */

/* The count of CAAM_DDDR */
#define CAAM_DDDR_COUNT                          (1U)

/*! @name DDJP - DECO0 Debug Job Pointer */
/*! @{ */

#define CAAM_DDJP_JDPTR_MASK                     (0xFFFFFFFFFU)
#define CAAM_DDJP_JDPTR_SHIFT                    (0U)
#define CAAM_DDJP_JDPTR(x)                       (((uint64_t)(((uint64_t)(x)) << CAAM_DDJP_JDPTR_SHIFT)) & CAAM_DDJP_JDPTR_MASK)
/*! @} */

/* The count of CAAM_DDJP */
#define CAAM_DDJP_COUNT                          (1U)

/*! @name DSDP - DECO0 Debug Shared Pointer */
/*! @{ */

#define CAAM_DSDP_SDPTR_MASK                     (0xFFFFFFFFFU)
#define CAAM_DSDP_SDPTR_SHIFT                    (0U)
#define CAAM_DSDP_SDPTR(x)                       (((uint64_t)(((uint64_t)(x)) << CAAM_DSDP_SDPTR_SHIFT)) & CAAM_DSDP_SDPTR_MASK)
/*! @} */

/* The count of CAAM_DSDP */
#define CAAM_DSDP_COUNT                          (1U)

/*! @name DDDR_MS - DECO0 Debug DID, most-significant half */
/*! @{ */

#define CAAM_DDDR_MS_PRIM_DID_MASK               (0xFU)
#define CAAM_DDDR_MS_PRIM_DID_SHIFT              (0U)
#define CAAM_DDDR_MS_PRIM_DID(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_MS_PRIM_DID_SHIFT)) & CAAM_DDDR_MS_PRIM_DID_MASK)

#define CAAM_DDDR_MS_PRIM_TZ_MASK                (0x10U)
#define CAAM_DDDR_MS_PRIM_TZ_SHIFT               (4U)
/*! PRIM_TZ
 *  0b0..TrustZone NonSecureWorld
 *  0b1..TrustZone SecureWorld
 */
#define CAAM_DDDR_MS_PRIM_TZ(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_MS_PRIM_TZ_SHIFT)) & CAAM_DDDR_MS_PRIM_TZ_MASK)

#define CAAM_DDDR_MS_PRIM_ICID_MASK              (0xFFE0U)
#define CAAM_DDDR_MS_PRIM_ICID_SHIFT             (5U)
#define CAAM_DDDR_MS_PRIM_ICID(x)                (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_MS_PRIM_ICID_SHIFT)) & CAAM_DDDR_MS_PRIM_ICID_MASK)

#define CAAM_DDDR_MS_OUT_DID_MASK                (0xF0000U)
#define CAAM_DDDR_MS_OUT_DID_SHIFT               (16U)
#define CAAM_DDDR_MS_OUT_DID(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_MS_OUT_DID_SHIFT)) & CAAM_DDDR_MS_OUT_DID_MASK)

#define CAAM_DDDR_MS_OUT_ICID_MASK               (0xFFE00000U)
#define CAAM_DDDR_MS_OUT_ICID_SHIFT              (21U)
#define CAAM_DDDR_MS_OUT_ICID(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_MS_OUT_ICID_SHIFT)) & CAAM_DDDR_MS_OUT_ICID_MASK)
/*! @} */

/* The count of CAAM_DDDR_MS */
#define CAAM_DDDR_MS_COUNT                       (1U)

/*! @name DDDR_LS - DECO0 Debug DID, least-significant half */
/*! @{ */

#define CAAM_DDDR_LS_OUT_DID_MASK                (0xFU)
#define CAAM_DDDR_LS_OUT_DID_SHIFT               (0U)
#define CAAM_DDDR_LS_OUT_DID(x)                  (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_LS_OUT_DID_SHIFT)) & CAAM_DDDR_LS_OUT_DID_MASK)

#define CAAM_DDDR_LS_OUT_ICID_MASK               (0x3FF80000U)
#define CAAM_DDDR_LS_OUT_ICID_SHIFT              (19U)
#define CAAM_DDDR_LS_OUT_ICID(x)                 (((uint32_t)(((uint32_t)(x)) << CAAM_DDDR_LS_OUT_ICID_SHIFT)) & CAAM_DDDR_LS_OUT_ICID_MASK)
/*! @} */

/* The count of CAAM_DDDR_LS */
#define CAAM_DDDR_LS_COUNT                       (1U)

/*! @name SOL - Sequence Output Length Register */
/*! @{ */

#define CAAM_SOL_SOL_MASK                        (0xFFFFFFFFU)
#define CAAM_SOL_SOL_SHIFT                       (0U)
#define CAAM_SOL_SOL(x)                          (((uint32_t)(((uint32_t)(x)) << CAAM_SOL_SOL_SHIFT)) & CAAM_SOL_SOL_MASK)
/*! @} */

/* The count of CAAM_SOL */
#define CAAM_SOL_COUNT                           (1U)

/*! @name VSOL - Variable Sequence Output Length Register */
/*! @{ */

#define CAAM_VSOL_VSOL_MASK                      (0xFFFFFFFFU)
#define CAAM_VSOL_VSOL_SHIFT                     (0U)
#define CAAM_VSOL_VSOL(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_VSOL_VSOL_SHIFT)) & CAAM_VSOL_VSOL_MASK)
/*! @} */

/* The count of CAAM_VSOL */
#define CAAM_VSOL_COUNT                          (1U)

/*! @name SIL - Sequence Input Length Register */
/*! @{ */

#define CAAM_SIL_SIL_MASK                        (0xFFFFFFFFU)
#define CAAM_SIL_SIL_SHIFT                       (0U)
#define CAAM_SIL_SIL(x)                          (((uint32_t)(((uint32_t)(x)) << CAAM_SIL_SIL_SHIFT)) & CAAM_SIL_SIL_MASK)
/*! @} */

/* The count of CAAM_SIL */
#define CAAM_SIL_COUNT                           (1U)

/*! @name VSIL - Variable Sequence Input Length Register */
/*! @{ */

#define CAAM_VSIL_VSIL_MASK                      (0xFFFFFFFFU)
#define CAAM_VSIL_VSIL_SHIFT                     (0U)
#define CAAM_VSIL_VSIL(x)                        (((uint32_t)(((uint32_t)(x)) << CAAM_VSIL_VSIL_SHIFT)) & CAAM_VSIL_VSIL_MASK)
/*! @} */

/* The count of CAAM_VSIL */
#define CAAM_VSIL_COUNT                          (1U)

/*! @name DPOVRD - Protocol Override Register */
/*! @{ */

#define CAAM_DPOVRD_DPOVRD_MASK                  (0xFFFFFFFFU)
#define CAAM_DPOVRD_DPOVRD_SHIFT                 (0U)
#define CAAM_DPOVRD_DPOVRD(x)                    (((uint32_t)(((uint32_t)(x)) << CAAM_DPOVRD_DPOVRD_SHIFT)) & CAAM_DPOVRD_DPOVRD_MASK)
/*! @} */

/* The count of CAAM_DPOVRD */
#define CAAM_DPOVRD_COUNT                        (1U)

/*! @name UVSOL - Variable Sequence Output Length Register; Upper 32 bits */
/*! @{ */

#define CAAM_UVSOL_UVSOL_MASK                    (0xFFFFFFFFU)
#define CAAM_UVSOL_UVSOL_SHIFT                   (0U)
#define CAAM_UVSOL_UVSOL(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_UVSOL_UVSOL_SHIFT)) & CAAM_UVSOL_UVSOL_MASK)
/*! @} */

/* The count of CAAM_UVSOL */
#define CAAM_UVSOL_COUNT                         (1U)

/*! @name UVSIL - Variable Sequence Input Length Register; Upper 32 bits */
/*! @{ */

#define CAAM_UVSIL_UVSIL_MASK                    (0xFFFFFFFFU)
#define CAAM_UVSIL_UVSIL_SHIFT                   (0U)
#define CAAM_UVSIL_UVSIL(x)                      (((uint32_t)(((uint32_t)(x)) << CAAM_UVSIL_UVSIL_SHIFT)) & CAAM_UVSIL_UVSIL_MASK)
/*! @} */

/* The count of CAAM_UVSIL */
#define CAAM_UVSIL_COUNT                         (1U)


/*!
 * @}
 */ /* end of group CAAM_Register_Masks */


/*!
 * @}
 */ /* end of group CAAM_Peripheral_Access_Layer */


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


#endif  /* PERI_CAAM_H_ */

