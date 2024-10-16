/*
** ###################################################################
**     Processor:           S32K344
**     Reference manual:    S32K3xx RM Rev.3
**     Version:             rev. 1.9, 2021-10-27
**     Build:               b211026
**
**     Abstract:
**         Peripheral Access Layer for S32K344
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2021 NXP
**
**     NXP Confidential. This software is owned or controlled by NXP and may only be
**     used strictly in accordance with the applicable license terms. By expressly
**     accepting such terms or by downloading, installing, activating and/or otherwise
**     using the software, you are agreeing that you have read, and that you agree to
**     comply with and are bound by, such license terms. If you do not agree to be
**     bound by the applicable license terms, then you may not retain, install,
**     activate or otherwise use the software. The production use license in
**     Section 2.3 is expressly granted for this software.
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
** ###################################################################
*/

/*!
 * @file S32K344_DMA_TCD.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_DMA_TCD
 *
 * This file contains register definitions and macros for easy access to their
 * bit fields.
 *
 * This file assumes LITTLE endian system.
 */

/**
* @page misra_violations MISRA-C:2012 violations
*
* @section [global]
* Violates MISRA 2012 Advisory Rule 2.3, local typedef not referenced
* The SoC header defines typedef for all modules.
*
* @section [global]
* Violates MISRA 2012 Advisory Rule 2.5, local macro not referenced
* The SoC header defines macros for all modules and registers.
*
* @section [global]
* Violates MISRA 2012 Advisory Directive 4.9, Function-like macro
* These are generated macros used for accessing the bit-fields from registers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.1, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.2, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.4, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.5, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 21.1, defined macro '__I' is reserved to the compiler
* This type qualifier is needed to ensure correct I/O access and addressing.
*/

/* Prevention from multiple including the same memory map */
#if !defined(S32K344_DMA_TCD_H_)  /* Check if memory map has not been already included */
#define S32K344_DMA_TCD_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- DMA_TCD Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_TCD_Peripheral_Access_Layer DMA_TCD Peripheral Access Layer
 * @{
 */

/** DMA_TCD - Register Layout Typedef */
typedef struct {
  __IO uint32_t CH0_CSR;                           /**< Channel Control and Status, offset: 0x0 */
  __IO uint32_t CH0_ES;                            /**< Channel Error Status, offset: 0x4 */
  __IO uint32_t CH0_INT;                           /**< Channel Interrupt Status, offset: 0x8 */
  __IO uint32_t CH0_SBR;                           /**< Channel System Bus, offset: 0xC */
  __IO uint32_t CH0_PRI;                           /**< Channel Priority, offset: 0x10 */
  uint8_t RESERVED_0[12];
  __IO uint32_t TCD0_SADDR;                        /**< TCD Source Address, offset: 0x20 */
  __IO uint16_t TCD0_SOFF;                         /**< TCD Signed Source Address Offset, offset: 0x24 */
  __IO uint16_t TCD0_ATTR;                         /**< TCD Transfer Attributes, offset: 0x26 */
  union {                                          /* offset: 0x28 */
    __IO uint32_t TCD0_NBYTES_MLOFFNO;               /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x28 */
    __IO uint32_t TCD0_NBYTES_MLOFFYES;              /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x28 */
  } NBYTES0;
  __IO uint32_t TCD0_SLAST_SDA;                    /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x2C */
  __IO uint32_t TCD0_DADDR;                        /**< TCD Destination Address, offset: 0x30 */
  __IO uint16_t TCD0_DOFF;                         /**< TCD Signed Destination Address Offset, offset: 0x34 */
  union {                                          /* offset: 0x36 */
    __IO uint16_t TCD0_CITER_ELINKNO;                /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x36 */
    __IO uint16_t TCD0_CITER_ELINKYES;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x36 */
  } CITER0;
  __IO uint32_t TCD0_DLAST_SGA;                    /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x38 */
  __IO uint16_t TCD0_CSR;                          /**< TCD Control and Status, offset: 0x3C */
  union {                                          /* offset: 0x3E */
    __IO uint16_t TCD0_BITER_ELINKNO;                /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x3E */
    __IO uint16_t TCD0_BITER_ELINKYES;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x3E */
  } BITER0;
  uint8_t RESERVED_1[16320];
  __IO uint32_t CH1_CSR;                           /**< Channel Control and Status, offset: 0x4000 */
  __IO uint32_t CH1_ES;                            /**< Channel Error Status, offset: 0x4004 */
  __IO uint32_t CH1_INT;                           /**< Channel Interrupt Status, offset: 0x4008 */
  __IO uint32_t CH1_SBR;                           /**< Channel System Bus, offset: 0x400C */
  __IO uint32_t CH1_PRI;                           /**< Channel Priority, offset: 0x4010 */
  uint8_t RESERVED_2[12];
  __IO uint32_t TCD1_SADDR;                        /**< TCD Source Address, offset: 0x4020 */
  __IO uint16_t TCD1_SOFF;                         /**< TCD Signed Source Address Offset, offset: 0x4024 */
  __IO uint16_t TCD1_ATTR;                         /**< TCD Transfer Attributes, offset: 0x4026 */
  union {                                          /* offset: 0x4028 */
    __IO uint32_t TCD1_NBYTES_MLOFFNO;               /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x4028 */
    __IO uint32_t TCD1_NBYTES_MLOFFYES;              /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x4028 */
  } NBYTES1;
  __IO uint32_t TCD1_SLAST_SDA;                    /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x402C */
  __IO uint32_t TCD1_DADDR;                        /**< TCD Destination Address, offset: 0x4030 */
  __IO uint16_t TCD1_DOFF;                         /**< TCD Signed Destination Address Offset, offset: 0x4034 */
  union {                                          /* offset: 0x4036 */
    __IO uint16_t TCD1_CITER_ELINKNO;                /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x4036 */
    __IO uint16_t TCD1_CITER_ELINKYES;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x4036 */
  } CITER1;
  __IO uint32_t TCD1_DLAST_SGA;                    /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x4038 */
  __IO uint16_t TCD1_CSR;                          /**< TCD Control and Status, offset: 0x403C */
  union {                                          /* offset: 0x403E */
    __IO uint16_t TCD1_BITER_ELINKNO;                /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x403E */
    __IO uint16_t TCD1_BITER_ELINKYES;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x403E */
  } BITER1;
  uint8_t RESERVED_3[16320];
  __IO uint32_t CH2_CSR;                           /**< Channel Control and Status, offset: 0x8000 */
  __IO uint32_t CH2_ES;                            /**< Channel Error Status, offset: 0x8004 */
  __IO uint32_t CH2_INT;                           /**< Channel Interrupt Status, offset: 0x8008 */
  __IO uint32_t CH2_SBR;                           /**< Channel System Bus, offset: 0x800C */
  __IO uint32_t CH2_PRI;                           /**< Channel Priority, offset: 0x8010 */
  uint8_t RESERVED_4[12];
  __IO uint32_t TCD2_SADDR;                        /**< TCD Source Address, offset: 0x8020 */
  __IO uint16_t TCD2_SOFF;                         /**< TCD Signed Source Address Offset, offset: 0x8024 */
  __IO uint16_t TCD2_ATTR;                         /**< TCD Transfer Attributes, offset: 0x8026 */
  union {                                          /* offset: 0x8028 */
    __IO uint32_t TCD2_NBYTES_MLOFFNO;               /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x8028 */
    __IO uint32_t TCD2_NBYTES_MLOFFYES;              /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x8028 */
  } NBYTES2;
  __IO uint32_t TCD2_SLAST_SDA;                    /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x802C */
  __IO uint32_t TCD2_DADDR;                        /**< TCD Destination Address, offset: 0x8030 */
  __IO uint16_t TCD2_DOFF;                         /**< TCD Signed Destination Address Offset, offset: 0x8034 */
  union {                                          /* offset: 0x8036 */
    __IO uint16_t TCD2_CITER_ELINKNO;                /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x8036 */
    __IO uint16_t TCD2_CITER_ELINKYES;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x8036 */
  } CITER2;
  __IO uint32_t TCD2_DLAST_SGA;                    /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x8038 */
  __IO uint16_t TCD2_CSR;                          /**< TCD Control and Status, offset: 0x803C */
  union {                                          /* offset: 0x803E */
    __IO uint16_t TCD2_BITER_ELINKNO;                /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x803E */
    __IO uint16_t TCD2_BITER_ELINKYES;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x803E */
  } BITER2;
  uint8_t RESERVED_5[16320];
  __IO uint32_t CH3_CSR;                           /**< Channel Control and Status, offset: 0xC000 */
  __IO uint32_t CH3_ES;                            /**< Channel Error Status, offset: 0xC004 */
  __IO uint32_t CH3_INT;                           /**< Channel Interrupt Status, offset: 0xC008 */
  __IO uint32_t CH3_SBR;                           /**< Channel System Bus, offset: 0xC00C */
  __IO uint32_t CH3_PRI;                           /**< Channel Priority, offset: 0xC010 */
  uint8_t RESERVED_6[12];
  __IO uint32_t TCD3_SADDR;                        /**< TCD Source Address, offset: 0xC020 */
  __IO uint16_t TCD3_SOFF;                         /**< TCD Signed Source Address Offset, offset: 0xC024 */
  __IO uint16_t TCD3_ATTR;                         /**< TCD Transfer Attributes, offset: 0xC026 */
  union {                                          /* offset: 0xC028 */
    __IO uint32_t TCD3_NBYTES_MLOFFNO;               /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0xC028 */
    __IO uint32_t TCD3_NBYTES_MLOFFYES;              /**< TCD Transfer Size with Minor Loop Offsets, offset: 0xC028 */
  } NBYTES3;
  __IO uint32_t TCD3_SLAST_SDA;                    /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0xC02C */
  __IO uint32_t TCD3_DADDR;                        /**< TCD Destination Address, offset: 0xC030 */
  __IO uint16_t TCD3_DOFF;                         /**< TCD Signed Destination Address Offset, offset: 0xC034 */
  union {                                          /* offset: 0xC036 */
    __IO uint16_t TCD3_CITER_ELINKNO;                /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0xC036 */
    __IO uint16_t TCD3_CITER_ELINKYES;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0xC036 */
  } CITER3;
  __IO uint32_t TCD3_DLAST_SGA;                    /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0xC038 */
  __IO uint16_t TCD3_CSR;                          /**< TCD Control and Status, offset: 0xC03C */
  union {                                          /* offset: 0xC03E */
    __IO uint16_t TCD3_BITER_ELINKNO;                /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0xC03E */
    __IO uint16_t TCD3_BITER_ELINKYES;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0xC03E */
  } BITER3;
  uint8_t RESERVED_7[16320];
  __IO uint32_t CH4_CSR;                           /**< Channel Control and Status, offset: 0x10000 */
  __IO uint32_t CH4_ES;                            /**< Channel Error Status, offset: 0x10004 */
  __IO uint32_t CH4_INT;                           /**< Channel Interrupt Status, offset: 0x10008 */
  __IO uint32_t CH4_SBR;                           /**< Channel System Bus, offset: 0x1000C */
  __IO uint32_t CH4_PRI;                           /**< Channel Priority, offset: 0x10010 */
  uint8_t RESERVED_8[12];
  __IO uint32_t TCD4_SADDR;                        /**< TCD Source Address, offset: 0x10020 */
  __IO uint16_t TCD4_SOFF;                         /**< TCD Signed Source Address Offset, offset: 0x10024 */
  __IO uint16_t TCD4_ATTR;                         /**< TCD Transfer Attributes, offset: 0x10026 */
  union {                                          /* offset: 0x10028 */
    __IO uint32_t TCD4_NBYTES_MLOFFNO;               /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x10028 */
    __IO uint32_t TCD4_NBYTES_MLOFFYES;              /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x10028 */
  } NBYTES4;
  __IO uint32_t TCD4_SLAST_SDA;                    /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x1002C */
  __IO uint32_t TCD4_DADDR;                        /**< TCD Destination Address, offset: 0x10030 */
  __IO uint16_t TCD4_DOFF;                         /**< TCD Signed Destination Address Offset, offset: 0x10034 */
  union {                                          /* offset: 0x10036 */
    __IO uint16_t TCD4_CITER_ELINKNO;                /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x10036 */
    __IO uint16_t TCD4_CITER_ELINKYES;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x10036 */
  } CITER4;
  __IO uint32_t TCD4_DLAST_SGA;                    /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x10038 */
  __IO uint16_t TCD4_CSR;                          /**< TCD Control and Status, offset: 0x1003C */
  union {                                          /* offset: 0x1003E */
    __IO uint16_t TCD4_BITER_ELINKNO;                /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x1003E */
    __IO uint16_t TCD4_BITER_ELINKYES;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x1003E */
  } BITER4;
  uint8_t RESERVED_9[16320];
  __IO uint32_t CH5_CSR;                           /**< Channel Control and Status, offset: 0x14000 */
  __IO uint32_t CH5_ES;                            /**< Channel Error Status, offset: 0x14004 */
  __IO uint32_t CH5_INT;                           /**< Channel Interrupt Status, offset: 0x14008 */
  __IO uint32_t CH5_SBR;                           /**< Channel System Bus, offset: 0x1400C */
  __IO uint32_t CH5_PRI;                           /**< Channel Priority, offset: 0x14010 */
  uint8_t RESERVED_10[12];
  __IO uint32_t TCD5_SADDR;                        /**< TCD Source Address, offset: 0x14020 */
  __IO uint16_t TCD5_SOFF;                         /**< TCD Signed Source Address Offset, offset: 0x14024 */
  __IO uint16_t TCD5_ATTR;                         /**< TCD Transfer Attributes, offset: 0x14026 */
  union {                                          /* offset: 0x14028 */
    __IO uint32_t TCD5_NBYTES_MLOFFNO;               /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x14028 */
    __IO uint32_t TCD5_NBYTES_MLOFFYES;              /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x14028 */
  } NBYTES5;
  __IO uint32_t TCD5_SLAST_SDA;                    /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x1402C */
  __IO uint32_t TCD5_DADDR;                        /**< TCD Destination Address, offset: 0x14030 */
  __IO uint16_t TCD5_DOFF;                         /**< TCD Signed Destination Address Offset, offset: 0x14034 */
  union {                                          /* offset: 0x14036 */
    __IO uint16_t TCD5_CITER_ELINKNO;                /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x14036 */
    __IO uint16_t TCD5_CITER_ELINKYES;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x14036 */
  } CITER5;
  __IO uint32_t TCD5_DLAST_SGA;                    /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x14038 */
  __IO uint16_t TCD5_CSR;                          /**< TCD Control and Status, offset: 0x1403C */
  union {                                          /* offset: 0x1403E */
    __IO uint16_t TCD5_BITER_ELINKNO;                /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x1403E */
    __IO uint16_t TCD5_BITER_ELINKYES;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x1403E */
  } BITER5;
  uint8_t RESERVED_11[16320];
  __IO uint32_t CH6_CSR;                           /**< Channel Control and Status, offset: 0x18000 */
  __IO uint32_t CH6_ES;                            /**< Channel Error Status, offset: 0x18004 */
  __IO uint32_t CH6_INT;                           /**< Channel Interrupt Status, offset: 0x18008 */
  __IO uint32_t CH6_SBR;                           /**< Channel System Bus, offset: 0x1800C */
  __IO uint32_t CH6_PRI;                           /**< Channel Priority, offset: 0x18010 */
  uint8_t RESERVED_12[12];
  __IO uint32_t TCD6_SADDR;                        /**< TCD Source Address, offset: 0x18020 */
  __IO uint16_t TCD6_SOFF;                         /**< TCD Signed Source Address Offset, offset: 0x18024 */
  __IO uint16_t TCD6_ATTR;                         /**< TCD Transfer Attributes, offset: 0x18026 */
  union {                                          /* offset: 0x18028 */
    __IO uint32_t TCD6_NBYTES_MLOFFNO;               /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x18028 */
    __IO uint32_t TCD6_NBYTES_MLOFFYES;              /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x18028 */
  } NBYTES6;
  __IO uint32_t TCD6_SLAST_SDA;                    /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x1802C */
  __IO uint32_t TCD6_DADDR;                        /**< TCD Destination Address, offset: 0x18030 */
  __IO uint16_t TCD6_DOFF;                         /**< TCD Signed Destination Address Offset, offset: 0x18034 */
  union {                                          /* offset: 0x18036 */
    __IO uint16_t TCD6_CITER_ELINKNO;                /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x18036 */
    __IO uint16_t TCD6_CITER_ELINKYES;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x18036 */
  } CITER6;
  __IO uint32_t TCD6_DLAST_SGA;                    /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x18038 */
  __IO uint16_t TCD6_CSR;                          /**< TCD Control and Status, offset: 0x1803C */
  union {                                          /* offset: 0x1803E */
    __IO uint16_t TCD6_BITER_ELINKNO;                /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x1803E */
    __IO uint16_t TCD6_BITER_ELINKYES;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x1803E */
  } BITER6;
  uint8_t RESERVED_13[16320];
  __IO uint32_t CH7_CSR;                           /**< Channel Control and Status, offset: 0x1C000 */
  __IO uint32_t CH7_ES;                            /**< Channel Error Status, offset: 0x1C004 */
  __IO uint32_t CH7_INT;                           /**< Channel Interrupt Status, offset: 0x1C008 */
  __IO uint32_t CH7_SBR;                           /**< Channel System Bus, offset: 0x1C00C */
  __IO uint32_t CH7_PRI;                           /**< Channel Priority, offset: 0x1C010 */
  uint8_t RESERVED_14[12];
  __IO uint32_t TCD7_SADDR;                        /**< TCD Source Address, offset: 0x1C020 */
  __IO uint16_t TCD7_SOFF;                         /**< TCD Signed Source Address Offset, offset: 0x1C024 */
  __IO uint16_t TCD7_ATTR;                         /**< TCD Transfer Attributes, offset: 0x1C026 */
  union {                                          /* offset: 0x1C028 */
    __IO uint32_t TCD7_NBYTES_MLOFFNO;               /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x1C028 */
    __IO uint32_t TCD7_NBYTES_MLOFFYES;              /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x1C028 */
  } NBYTES7;
  __IO uint32_t TCD7_SLAST_SDA;                    /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x1C02C */
  __IO uint32_t TCD7_DADDR;                        /**< TCD Destination Address, offset: 0x1C030 */
  __IO uint16_t TCD7_DOFF;                         /**< TCD Signed Destination Address Offset, offset: 0x1C034 */
  union {                                          /* offset: 0x1C036 */
    __IO uint16_t TCD7_CITER_ELINKNO;                /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x1C036 */
    __IO uint16_t TCD7_CITER_ELINKYES;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x1C036 */
  } CITER7;
  __IO uint32_t TCD7_DLAST_SGA;                    /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x1C038 */
  __IO uint16_t TCD7_CSR;                          /**< TCD Control and Status, offset: 0x1C03C */
  union {                                          /* offset: 0x1C03E */
    __IO uint16_t TCD7_BITER_ELINKNO;                /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x1C03E */
    __IO uint16_t TCD7_BITER_ELINKYES;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x1C03E */
  } BITER7;
  uint8_t RESERVED_15[16320];
  __IO uint32_t CH8_CSR;                           /**< Channel Control and Status, offset: 0x20000 */
  __IO uint32_t CH8_ES;                            /**< Channel Error Status, offset: 0x20004 */
  __IO uint32_t CH8_INT;                           /**< Channel Interrupt Status, offset: 0x20008 */
  __IO uint32_t CH8_SBR;                           /**< Channel System Bus, offset: 0x2000C */
  __IO uint32_t CH8_PRI;                           /**< Channel Priority, offset: 0x20010 */
  uint8_t RESERVED_16[12];
  __IO uint32_t TCD8_SADDR;                        /**< TCD Source Address, offset: 0x20020 */
  __IO uint16_t TCD8_SOFF;                         /**< TCD Signed Source Address Offset, offset: 0x20024 */
  __IO uint16_t TCD8_ATTR;                         /**< TCD Transfer Attributes, offset: 0x20026 */
  union {                                          /* offset: 0x20028 */
    __IO uint32_t TCD8_NBYTES_MLOFFNO;               /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x20028 */
    __IO uint32_t TCD8_NBYTES_MLOFFYES;              /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x20028 */
  } NBYTES8;
  __IO uint32_t TCD8_SLAST_SDA;                    /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x2002C */
  __IO uint32_t TCD8_DADDR;                        /**< TCD Destination Address, offset: 0x20030 */
  __IO uint16_t TCD8_DOFF;                         /**< TCD Signed Destination Address Offset, offset: 0x20034 */
  union {                                          /* offset: 0x20036 */
    __IO uint16_t TCD8_CITER_ELINKNO;                /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x20036 */
    __IO uint16_t TCD8_CITER_ELINKYES;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x20036 */
  } CITER8;
  __IO uint32_t TCD8_DLAST_SGA;                    /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x20038 */
  __IO uint16_t TCD8_CSR;                          /**< TCD Control and Status, offset: 0x2003C */
  union {                                          /* offset: 0x2003E */
    __IO uint16_t TCD8_BITER_ELINKNO;                /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x2003E */
    __IO uint16_t TCD8_BITER_ELINKYES;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x2003E */
  } BITER8;
  uint8_t RESERVED_17[16320];
  __IO uint32_t CH9_CSR;                           /**< Channel Control and Status, offset: 0x24000 */
  __IO uint32_t CH9_ES;                            /**< Channel Error Status, offset: 0x24004 */
  __IO uint32_t CH9_INT;                           /**< Channel Interrupt Status, offset: 0x24008 */
  __IO uint32_t CH9_SBR;                           /**< Channel System Bus, offset: 0x2400C */
  __IO uint32_t CH9_PRI;                           /**< Channel Priority, offset: 0x24010 */
  uint8_t RESERVED_18[12];
  __IO uint32_t TCD9_SADDR;                        /**< TCD Source Address, offset: 0x24020 */
  __IO uint16_t TCD9_SOFF;                         /**< TCD Signed Source Address Offset, offset: 0x24024 */
  __IO uint16_t TCD9_ATTR;                         /**< TCD Transfer Attributes, offset: 0x24026 */
  union {                                          /* offset: 0x24028 */
    __IO uint32_t TCD9_NBYTES_MLOFFNO;               /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x24028 */
    __IO uint32_t TCD9_NBYTES_MLOFFYES;              /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x24028 */
  } NBYTES9;
  __IO uint32_t TCD9_SLAST_SDA;                    /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x2402C */
  __IO uint32_t TCD9_DADDR;                        /**< TCD Destination Address, offset: 0x24030 */
  __IO uint16_t TCD9_DOFF;                         /**< TCD Signed Destination Address Offset, offset: 0x24034 */
  union {                                          /* offset: 0x24036 */
    __IO uint16_t TCD9_CITER_ELINKNO;                /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x24036 */
    __IO uint16_t TCD9_CITER_ELINKYES;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x24036 */
  } CITER9;
  __IO uint32_t TCD9_DLAST_SGA;                    /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x24038 */
  __IO uint16_t TCD9_CSR;                          /**< TCD Control and Status, offset: 0x2403C */
  union {                                          /* offset: 0x2403E */
    __IO uint16_t TCD9_BITER_ELINKNO;                /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x2403E */
    __IO uint16_t TCD9_BITER_ELINKYES;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x2403E */
  } BITER9;
  uint8_t RESERVED_19[16320];
  __IO uint32_t CH10_CSR;                          /**< Channel Control and Status, offset: 0x28000 */
  __IO uint32_t CH10_ES;                           /**< Channel Error Status, offset: 0x28004 */
  __IO uint32_t CH10_INT;                          /**< Channel Interrupt Status, offset: 0x28008 */
  __IO uint32_t CH10_SBR;                          /**< Channel System Bus, offset: 0x2800C */
  __IO uint32_t CH10_PRI;                          /**< Channel Priority, offset: 0x28010 */
  uint8_t RESERVED_20[12];
  __IO uint32_t TCD10_SADDR;                       /**< TCD Source Address, offset: 0x28020 */
  __IO uint16_t TCD10_SOFF;                        /**< TCD Signed Source Address Offset, offset: 0x28024 */
  __IO uint16_t TCD10_ATTR;                        /**< TCD Transfer Attributes, offset: 0x28026 */
  union {                                          /* offset: 0x28028 */
    __IO uint32_t TCD10_NBYTES_MLOFFNO;              /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x28028 */
    __IO uint32_t TCD10_NBYTES_MLOFFYES;             /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x28028 */
  } NBYTES10;
  __IO uint32_t TCD10_SLAST_SDA;                   /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x2802C */
  __IO uint32_t TCD10_DADDR;                       /**< TCD Destination Address, offset: 0x28030 */
  __IO uint16_t TCD10_DOFF;                        /**< TCD Signed Destination Address Offset, offset: 0x28034 */
  union {                                          /* offset: 0x28036 */
    __IO uint16_t TCD10_CITER_ELINKNO;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x28036 */
    __IO uint16_t TCD10_CITER_ELINKYES;              /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x28036 */
  } CITER10;
  __IO uint32_t TCD10_DLAST_SGA;                   /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x28038 */
  __IO uint16_t TCD10_CSR;                         /**< TCD Control and Status, offset: 0x2803C */
  union {                                          /* offset: 0x2803E */
    __IO uint16_t TCD10_BITER_ELINKNO;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x2803E */
    __IO uint16_t TCD10_BITER_ELINKYES;              /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x2803E */
  } BITER10;
  uint8_t RESERVED_21[16320];
  __IO uint32_t CH11_CSR;                          /**< Channel Control and Status, offset: 0x2C000 */
  __IO uint32_t CH11_ES;                           /**< Channel Error Status, offset: 0x2C004 */
  __IO uint32_t CH11_INT;                          /**< Channel Interrupt Status, offset: 0x2C008 */
  __IO uint32_t CH11_SBR;                          /**< Channel System Bus, offset: 0x2C00C */
  __IO uint32_t CH11_PRI;                          /**< Channel Priority, offset: 0x2C010 */
  uint8_t RESERVED_22[12];
  __IO uint32_t TCD11_SADDR;                       /**< TCD Source Address, offset: 0x2C020 */
  __IO uint16_t TCD11_SOFF;                        /**< TCD Signed Source Address Offset, offset: 0x2C024 */
  __IO uint16_t TCD11_ATTR;                        /**< TCD Transfer Attributes, offset: 0x2C026 */
  union {                                          /* offset: 0x2C028 */
    __IO uint32_t TCD11_NBYTES_MLOFFNO;              /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x2C028 */
    __IO uint32_t TCD11_NBYTES_MLOFFYES;             /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x2C028 */
  } NBYTES11;
  __IO uint32_t TCD11_SLAST_SDA;                   /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x2C02C */
  __IO uint32_t TCD11_DADDR;                       /**< TCD Destination Address, offset: 0x2C030 */
  __IO uint16_t TCD11_DOFF;                        /**< TCD Signed Destination Address Offset, offset: 0x2C034 */
  union {                                          /* offset: 0x2C036 */
    __IO uint16_t TCD11_CITER_ELINKNO;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x2C036 */
    __IO uint16_t TCD11_CITER_ELINKYES;              /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x2C036 */
  } CITER11;
  __IO uint32_t TCD11_DLAST_SGA;                   /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x2C038 */
  __IO uint16_t TCD11_CSR;                         /**< TCD Control and Status, offset: 0x2C03C */
  union {                                          /* offset: 0x2C03E */
    __IO uint16_t TCD11_BITER_ELINKNO;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x2C03E */
    __IO uint16_t TCD11_BITER_ELINKYES;              /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x2C03E */
  } BITER11;
  uint8_t RESERVED_23[1916864];
  __IO uint32_t CH12_CSR;                          /**< Channel Control and Status, offset: 0x200000 */
  __IO uint32_t CH12_ES;                           /**< Channel Error Status, offset: 0x200004 */
  __IO uint32_t CH12_INT;                          /**< Channel Interrupt Status, offset: 0x200008 */
  __IO uint32_t CH12_SBR;                          /**< Channel System Bus, offset: 0x20000C */
  __IO uint32_t CH12_PRI;                          /**< Channel Priority, offset: 0x200010 */
  uint8_t RESERVED_24[12];
  __IO uint32_t TCD12_SADDR;                       /**< TCD Source Address, offset: 0x200020 */
  __IO uint16_t TCD12_SOFF;                        /**< TCD Signed Source Address Offset, offset: 0x200024 */
  __IO uint16_t TCD12_ATTR;                        /**< TCD Transfer Attributes, offset: 0x200026 */
  union {                                          /* offset: 0x200028 */
    __IO uint32_t TCD12_NBYTES_MLOFFNO;              /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x200028 */
    __IO uint32_t TCD12_NBYTES_MLOFFYES;             /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x200028 */
  } NBYTES12;
  __IO uint32_t TCD12_SLAST_SDA;                   /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x20002C */
  __IO uint32_t TCD12_DADDR;                       /**< TCD Destination Address, offset: 0x200030 */
  __IO uint16_t TCD12_DOFF;                        /**< TCD Signed Destination Address Offset, offset: 0x200034 */
  union {                                          /* offset: 0x200036 */
    __IO uint16_t TCD12_CITER_ELINKNO;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x200036 */
    __IO uint16_t TCD12_CITER_ELINKYES;              /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x200036 */
  } CITER12;
  __IO uint32_t TCD12_DLAST_SGA;                   /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x200038 */
  __IO uint16_t TCD12_CSR;                         /**< TCD Control and Status, offset: 0x20003C */
  union {                                          /* offset: 0x20003E */
    __IO uint16_t TCD12_BITER_ELINKNO;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x20003E */
    __IO uint16_t TCD12_BITER_ELINKYES;              /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x20003E */
  } BITER12;
  uint8_t RESERVED_25[16320];
  __IO uint32_t CH13_CSR;                          /**< Channel Control and Status, offset: 0x204000 */
  __IO uint32_t CH13_ES;                           /**< Channel Error Status, offset: 0x204004 */
  __IO uint32_t CH13_INT;                          /**< Channel Interrupt Status, offset: 0x204008 */
  __IO uint32_t CH13_SBR;                          /**< Channel System Bus, offset: 0x20400C */
  __IO uint32_t CH13_PRI;                          /**< Channel Priority, offset: 0x204010 */
  uint8_t RESERVED_26[12];
  __IO uint32_t TCD13_SADDR;                       /**< TCD Source Address, offset: 0x204020 */
  __IO uint16_t TCD13_SOFF;                        /**< TCD Signed Source Address Offset, offset: 0x204024 */
  __IO uint16_t TCD13_ATTR;                        /**< TCD Transfer Attributes, offset: 0x204026 */
  union {                                          /* offset: 0x204028 */
    __IO uint32_t TCD13_NBYTES_MLOFFNO;              /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x204028 */
    __IO uint32_t TCD13_NBYTES_MLOFFYES;             /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x204028 */
  } NBYTES13;
  __IO uint32_t TCD13_SLAST_SDA;                   /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x20402C */
  __IO uint32_t TCD13_DADDR;                       /**< TCD Destination Address, offset: 0x204030 */
  __IO uint16_t TCD13_DOFF;                        /**< TCD Signed Destination Address Offset, offset: 0x204034 */
  union {                                          /* offset: 0x204036 */
    __IO uint16_t TCD13_CITER_ELINKNO;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x204036 */
    __IO uint16_t TCD13_CITER_ELINKYES;              /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x204036 */
  } CITER13;
  __IO uint32_t TCD13_DLAST_SGA;                   /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x204038 */
  __IO uint16_t TCD13_CSR;                         /**< TCD Control and Status, offset: 0x20403C */
  union {                                          /* offset: 0x20403E */
    __IO uint16_t TCD13_BITER_ELINKNO;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x20403E */
    __IO uint16_t TCD13_BITER_ELINKYES;              /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x20403E */
  } BITER13;
  uint8_t RESERVED_27[16320];
  __IO uint32_t CH14_CSR;                          /**< Channel Control and Status, offset: 0x208000 */
  __IO uint32_t CH14_ES;                           /**< Channel Error Status, offset: 0x208004 */
  __IO uint32_t CH14_INT;                          /**< Channel Interrupt Status, offset: 0x208008 */
  __IO uint32_t CH14_SBR;                          /**< Channel System Bus, offset: 0x20800C */
  __IO uint32_t CH14_PRI;                          /**< Channel Priority, offset: 0x208010 */
  uint8_t RESERVED_28[12];
  __IO uint32_t TCD14_SADDR;                       /**< TCD Source Address, offset: 0x208020 */
  __IO uint16_t TCD14_SOFF;                        /**< TCD Signed Source Address Offset, offset: 0x208024 */
  __IO uint16_t TCD14_ATTR;                        /**< TCD Transfer Attributes, offset: 0x208026 */
  union {                                          /* offset: 0x208028 */
    __IO uint32_t TCD14_NBYTES_MLOFFNO;              /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x208028 */
    __IO uint32_t TCD14_NBYTES_MLOFFYES;             /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x208028 */
  } NBYTES14;
  __IO uint32_t TCD14_SLAST_SDA;                   /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x20802C */
  __IO uint32_t TCD14_DADDR;                       /**< TCD Destination Address, offset: 0x208030 */
  __IO uint16_t TCD14_DOFF;                        /**< TCD Signed Destination Address Offset, offset: 0x208034 */
  union {                                          /* offset: 0x208036 */
    __IO uint16_t TCD14_CITER_ELINKNO;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x208036 */
    __IO uint16_t TCD14_CITER_ELINKYES;              /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x208036 */
  } CITER14;
  __IO uint32_t TCD14_DLAST_SGA;                   /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x208038 */
  __IO uint16_t TCD14_CSR;                         /**< TCD Control and Status, offset: 0x20803C */
  union {                                          /* offset: 0x20803E */
    __IO uint16_t TCD14_BITER_ELINKNO;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x20803E */
    __IO uint16_t TCD14_BITER_ELINKYES;              /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x20803E */
  } BITER14;
  uint8_t RESERVED_29[16320];
  __IO uint32_t CH15_CSR;                          /**< Channel Control and Status, offset: 0x20C000 */
  __IO uint32_t CH15_ES;                           /**< Channel Error Status, offset: 0x20C004 */
  __IO uint32_t CH15_INT;                          /**< Channel Interrupt Status, offset: 0x20C008 */
  __IO uint32_t CH15_SBR;                          /**< Channel System Bus, offset: 0x20C00C */
  __IO uint32_t CH15_PRI;                          /**< Channel Priority, offset: 0x20C010 */
  uint8_t RESERVED_30[12];
  __IO uint32_t TCD15_SADDR;                       /**< TCD Source Address, offset: 0x20C020 */
  __IO uint16_t TCD15_SOFF;                        /**< TCD Signed Source Address Offset, offset: 0x20C024 */
  __IO uint16_t TCD15_ATTR;                        /**< TCD Transfer Attributes, offset: 0x20C026 */
  union {                                          /* offset: 0x20C028 */
    __IO uint32_t TCD15_NBYTES_MLOFFNO;              /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x20C028 */
    __IO uint32_t TCD15_NBYTES_MLOFFYES;             /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x20C028 */
  } NBYTES15;
  __IO uint32_t TCD15_SLAST_SDA;                   /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x20C02C */
  __IO uint32_t TCD15_DADDR;                       /**< TCD Destination Address, offset: 0x20C030 */
  __IO uint16_t TCD15_DOFF;                        /**< TCD Signed Destination Address Offset, offset: 0x20C034 */
  union {                                          /* offset: 0x20C036 */
    __IO uint16_t TCD15_CITER_ELINKNO;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x20C036 */
    __IO uint16_t TCD15_CITER_ELINKYES;              /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x20C036 */
  } CITER15;
  __IO uint32_t TCD15_DLAST_SGA;                   /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x20C038 */
  __IO uint16_t TCD15_CSR;                         /**< TCD Control and Status, offset: 0x20C03C */
  union {                                          /* offset: 0x20C03E */
    __IO uint16_t TCD15_BITER_ELINKNO;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x20C03E */
    __IO uint16_t TCD15_BITER_ELINKYES;              /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x20C03E */
  } BITER15;
  uint8_t RESERVED_31[16320];
  __IO uint32_t CH16_CSR;                          /**< Channel Control and Status, offset: 0x210000 */
  __IO uint32_t CH16_ES;                           /**< Channel Error Status, offset: 0x210004 */
  __IO uint32_t CH16_INT;                          /**< Channel Interrupt Status, offset: 0x210008 */
  __IO uint32_t CH16_SBR;                          /**< Channel System Bus, offset: 0x21000C */
  __IO uint32_t CH16_PRI;                          /**< Channel Priority, offset: 0x210010 */
  uint8_t RESERVED_32[12];
  __IO uint32_t TCD16_SADDR;                       /**< TCD Source Address, offset: 0x210020 */
  __IO uint16_t TCD16_SOFF;                        /**< TCD Signed Source Address Offset, offset: 0x210024 */
  __IO uint16_t TCD16_ATTR;                        /**< TCD Transfer Attributes, offset: 0x210026 */
  union {                                          /* offset: 0x210028 */
    __IO uint32_t TCD16_NBYTES_MLOFFNO;              /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x210028 */
    __IO uint32_t TCD16_NBYTES_MLOFFYES;             /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x210028 */
  } NBYTES16;
  __IO uint32_t TCD16_SLAST_SDA;                   /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x21002C */
  __IO uint32_t TCD16_DADDR;                       /**< TCD Destination Address, offset: 0x210030 */
  __IO uint16_t TCD16_DOFF;                        /**< TCD Signed Destination Address Offset, offset: 0x210034 */
  union {                                          /* offset: 0x210036 */
    __IO uint16_t TCD16_CITER_ELINKNO;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x210036 */
    __IO uint16_t TCD16_CITER_ELINKYES;              /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x210036 */
  } CITER16;
  __IO uint32_t TCD16_DLAST_SGA;                   /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x210038 */
  __IO uint16_t TCD16_CSR;                         /**< TCD Control and Status, offset: 0x21003C */
  union {                                          /* offset: 0x21003E */
    __IO uint16_t TCD16_BITER_ELINKNO;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x21003E */
    __IO uint16_t TCD16_BITER_ELINKYES;              /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x21003E */
  } BITER16;
  uint8_t RESERVED_33[16320];
  __IO uint32_t CH17_CSR;                          /**< Channel Control and Status, offset: 0x214000 */
  __IO uint32_t CH17_ES;                           /**< Channel Error Status, offset: 0x214004 */
  __IO uint32_t CH17_INT;                          /**< Channel Interrupt Status, offset: 0x214008 */
  __IO uint32_t CH17_SBR;                          /**< Channel System Bus, offset: 0x21400C */
  __IO uint32_t CH17_PRI;                          /**< Channel Priority, offset: 0x214010 */
  uint8_t RESERVED_34[12];
  __IO uint32_t TCD17_SADDR;                       /**< TCD Source Address, offset: 0x214020 */
  __IO uint16_t TCD17_SOFF;                        /**< TCD Signed Source Address Offset, offset: 0x214024 */
  __IO uint16_t TCD17_ATTR;                        /**< TCD Transfer Attributes, offset: 0x214026 */
  union {                                          /* offset: 0x214028 */
    __IO uint32_t TCD17_NBYTES_MLOFFNO;              /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x214028 */
    __IO uint32_t TCD17_NBYTES_MLOFFYES;             /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x214028 */
  } NBYTES17;
  __IO uint32_t TCD17_SLAST_SDA;                   /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x21402C */
  __IO uint32_t TCD17_DADDR;                       /**< TCD Destination Address, offset: 0x214030 */
  __IO uint16_t TCD17_DOFF;                        /**< TCD Signed Destination Address Offset, offset: 0x214034 */
  union {                                          /* offset: 0x214036 */
    __IO uint16_t TCD17_CITER_ELINKNO;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x214036 */
    __IO uint16_t TCD17_CITER_ELINKYES;              /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x214036 */
  } CITER17;
  __IO uint32_t TCD17_DLAST_SGA;                   /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x214038 */
  __IO uint16_t TCD17_CSR;                         /**< TCD Control and Status, offset: 0x21403C */
  union {                                          /* offset: 0x21403E */
    __IO uint16_t TCD17_BITER_ELINKNO;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x21403E */
    __IO uint16_t TCD17_BITER_ELINKYES;              /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x21403E */
  } BITER17;
  uint8_t RESERVED_35[16320];
  __IO uint32_t CH18_CSR;                          /**< Channel Control and Status, offset: 0x218000 */
  __IO uint32_t CH18_ES;                           /**< Channel Error Status, offset: 0x218004 */
  __IO uint32_t CH18_INT;                          /**< Channel Interrupt Status, offset: 0x218008 */
  __IO uint32_t CH18_SBR;                          /**< Channel System Bus, offset: 0x21800C */
  __IO uint32_t CH18_PRI;                          /**< Channel Priority, offset: 0x218010 */
  uint8_t RESERVED_36[12];
  __IO uint32_t TCD18_SADDR;                       /**< TCD Source Address, offset: 0x218020 */
  __IO uint16_t TCD18_SOFF;                        /**< TCD Signed Source Address Offset, offset: 0x218024 */
  __IO uint16_t TCD18_ATTR;                        /**< TCD Transfer Attributes, offset: 0x218026 */
  union {                                          /* offset: 0x218028 */
    __IO uint32_t TCD18_NBYTES_MLOFFNO;              /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x218028 */
    __IO uint32_t TCD18_NBYTES_MLOFFYES;             /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x218028 */
  } NBYTES18;
  __IO uint32_t TCD18_SLAST_SDA;                   /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x21802C */
  __IO uint32_t TCD18_DADDR;                       /**< TCD Destination Address, offset: 0x218030 */
  __IO uint16_t TCD18_DOFF;                        /**< TCD Signed Destination Address Offset, offset: 0x218034 */
  union {                                          /* offset: 0x218036 */
    __IO uint16_t TCD18_CITER_ELINKNO;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x218036 */
    __IO uint16_t TCD18_CITER_ELINKYES;              /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x218036 */
  } CITER18;
  __IO uint32_t TCD18_DLAST_SGA;                   /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x218038 */
  __IO uint16_t TCD18_CSR;                         /**< TCD Control and Status, offset: 0x21803C */
  union {                                          /* offset: 0x21803E */
    __IO uint16_t TCD18_BITER_ELINKNO;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x21803E */
    __IO uint16_t TCD18_BITER_ELINKYES;              /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x21803E */
  } BITER18;
  uint8_t RESERVED_37[16320];
  __IO uint32_t CH19_CSR;                          /**< Channel Control and Status, offset: 0x21C000 */
  __IO uint32_t CH19_ES;                           /**< Channel Error Status, offset: 0x21C004 */
  __IO uint32_t CH19_INT;                          /**< Channel Interrupt Status, offset: 0x21C008 */
  __IO uint32_t CH19_SBR;                          /**< Channel System Bus, offset: 0x21C00C */
  __IO uint32_t CH19_PRI;                          /**< Channel Priority, offset: 0x21C010 */
  uint8_t RESERVED_38[12];
  __IO uint32_t TCD19_SADDR;                       /**< TCD Source Address, offset: 0x21C020 */
  __IO uint16_t TCD19_SOFF;                        /**< TCD Signed Source Address Offset, offset: 0x21C024 */
  __IO uint16_t TCD19_ATTR;                        /**< TCD Transfer Attributes, offset: 0x21C026 */
  union {                                          /* offset: 0x21C028 */
    __IO uint32_t TCD19_NBYTES_MLOFFNO;              /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x21C028 */
    __IO uint32_t TCD19_NBYTES_MLOFFYES;             /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x21C028 */
  } NBYTES19;
  __IO uint32_t TCD19_SLAST_SDA;                   /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x21C02C */
  __IO uint32_t TCD19_DADDR;                       /**< TCD Destination Address, offset: 0x21C030 */
  __IO uint16_t TCD19_DOFF;                        /**< TCD Signed Destination Address Offset, offset: 0x21C034 */
  union {                                          /* offset: 0x21C036 */
    __IO uint16_t TCD19_CITER_ELINKNO;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x21C036 */
    __IO uint16_t TCD19_CITER_ELINKYES;              /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x21C036 */
  } CITER19;
  __IO uint32_t TCD19_DLAST_SGA;                   /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x21C038 */
  __IO uint16_t TCD19_CSR;                         /**< TCD Control and Status, offset: 0x21C03C */
  union {                                          /* offset: 0x21C03E */
    __IO uint16_t TCD19_BITER_ELINKNO;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x21C03E */
    __IO uint16_t TCD19_BITER_ELINKYES;              /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x21C03E */
  } BITER19;
  uint8_t RESERVED_39[16320];
  __IO uint32_t CH20_CSR;                          /**< Channel Control and Status, offset: 0x220000 */
  __IO uint32_t CH20_ES;                           /**< Channel Error Status, offset: 0x220004 */
  __IO uint32_t CH20_INT;                          /**< Channel Interrupt Status, offset: 0x220008 */
  __IO uint32_t CH20_SBR;                          /**< Channel System Bus, offset: 0x22000C */
  __IO uint32_t CH20_PRI;                          /**< Channel Priority, offset: 0x220010 */
  uint8_t RESERVED_40[12];
  __IO uint32_t TCD20_SADDR;                       /**< TCD Source Address, offset: 0x220020 */
  __IO uint16_t TCD20_SOFF;                        /**< TCD Signed Source Address Offset, offset: 0x220024 */
  __IO uint16_t TCD20_ATTR;                        /**< TCD Transfer Attributes, offset: 0x220026 */
  union {                                          /* offset: 0x220028 */
    __IO uint32_t TCD20_NBYTES_MLOFFNO;              /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x220028 */
    __IO uint32_t TCD20_NBYTES_MLOFFYES;             /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x220028 */
  } NBYTES20;
  __IO uint32_t TCD20_SLAST_SDA;                   /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x22002C */
  __IO uint32_t TCD20_DADDR;                       /**< TCD Destination Address, offset: 0x220030 */
  __IO uint16_t TCD20_DOFF;                        /**< TCD Signed Destination Address Offset, offset: 0x220034 */
  union {                                          /* offset: 0x220036 */
    __IO uint16_t TCD20_CITER_ELINKNO;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x220036 */
    __IO uint16_t TCD20_CITER_ELINKYES;              /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x220036 */
  } CITER20;
  __IO uint32_t TCD20_DLAST_SGA;                   /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x220038 */
  __IO uint16_t TCD20_CSR;                         /**< TCD Control and Status, offset: 0x22003C */
  union {                                          /* offset: 0x22003E */
    __IO uint16_t TCD20_BITER_ELINKNO;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x22003E */
    __IO uint16_t TCD20_BITER_ELINKYES;              /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x22003E */
  } BITER20;
  uint8_t RESERVED_41[16320];
  __IO uint32_t CH21_CSR;                          /**< Channel Control and Status, offset: 0x224000 */
  __IO uint32_t CH21_ES;                           /**< Channel Error Status, offset: 0x224004 */
  __IO uint32_t CH21_INT;                          /**< Channel Interrupt Status, offset: 0x224008 */
  __IO uint32_t CH21_SBR;                          /**< Channel System Bus, offset: 0x22400C */
  __IO uint32_t CH21_PRI;                          /**< Channel Priority, offset: 0x224010 */
  uint8_t RESERVED_42[12];
  __IO uint32_t TCD21_SADDR;                       /**< TCD Source Address, offset: 0x224020 */
  __IO uint16_t TCD21_SOFF;                        /**< TCD Signed Source Address Offset, offset: 0x224024 */
  __IO uint16_t TCD21_ATTR;                        /**< TCD Transfer Attributes, offset: 0x224026 */
  union {                                          /* offset: 0x224028 */
    __IO uint32_t TCD21_NBYTES_MLOFFNO;              /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x224028 */
    __IO uint32_t TCD21_NBYTES_MLOFFYES;             /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x224028 */
  } NBYTES21;
  __IO uint32_t TCD21_SLAST_SDA;                   /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x22402C */
  __IO uint32_t TCD21_DADDR;                       /**< TCD Destination Address, offset: 0x224030 */
  __IO uint16_t TCD21_DOFF;                        /**< TCD Signed Destination Address Offset, offset: 0x224034 */
  union {                                          /* offset: 0x224036 */
    __IO uint16_t TCD21_CITER_ELINKNO;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x224036 */
    __IO uint16_t TCD21_CITER_ELINKYES;              /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x224036 */
  } CITER21;
  __IO uint32_t TCD21_DLAST_SGA;                   /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x224038 */
  __IO uint16_t TCD21_CSR;                         /**< TCD Control and Status, offset: 0x22403C */
  union {                                          /* offset: 0x22403E */
    __IO uint16_t TCD21_BITER_ELINKNO;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x22403E */
    __IO uint16_t TCD21_BITER_ELINKYES;              /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x22403E */
  } BITER21;
  uint8_t RESERVED_43[16320];
  __IO uint32_t CH22_CSR;                          /**< Channel Control and Status, offset: 0x228000 */
  __IO uint32_t CH22_ES;                           /**< Channel Error Status, offset: 0x228004 */
  __IO uint32_t CH22_INT;                          /**< Channel Interrupt Status, offset: 0x228008 */
  __IO uint32_t CH22_SBR;                          /**< Channel System Bus, offset: 0x22800C */
  __IO uint32_t CH22_PRI;                          /**< Channel Priority, offset: 0x228010 */
  uint8_t RESERVED_44[12];
  __IO uint32_t TCD22_SADDR;                       /**< TCD Source Address, offset: 0x228020 */
  __IO uint16_t TCD22_SOFF;                        /**< TCD Signed Source Address Offset, offset: 0x228024 */
  __IO uint16_t TCD22_ATTR;                        /**< TCD Transfer Attributes, offset: 0x228026 */
  union {                                          /* offset: 0x228028 */
    __IO uint32_t TCD22_NBYTES_MLOFFNO;              /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x228028 */
    __IO uint32_t TCD22_NBYTES_MLOFFYES;             /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x228028 */
  } NBYTES22;
  __IO uint32_t TCD22_SLAST_SDA;                   /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x22802C */
  __IO uint32_t TCD22_DADDR;                       /**< TCD Destination Address, offset: 0x228030 */
  __IO uint16_t TCD22_DOFF;                        /**< TCD Signed Destination Address Offset, offset: 0x228034 */
  union {                                          /* offset: 0x228036 */
    __IO uint16_t TCD22_CITER_ELINKNO;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x228036 */
    __IO uint16_t TCD22_CITER_ELINKYES;              /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x228036 */
  } CITER22;
  __IO uint32_t TCD22_DLAST_SGA;                   /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x228038 */
  __IO uint16_t TCD22_CSR;                         /**< TCD Control and Status, offset: 0x22803C */
  union {                                          /* offset: 0x22803E */
    __IO uint16_t TCD22_BITER_ELINKNO;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x22803E */
    __IO uint16_t TCD22_BITER_ELINKYES;              /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x22803E */
  } BITER22;
  uint8_t RESERVED_45[16320];
  __IO uint32_t CH23_CSR;                          /**< Channel Control and Status, offset: 0x22C000 */
  __IO uint32_t CH23_ES;                           /**< Channel Error Status, offset: 0x22C004 */
  __IO uint32_t CH23_INT;                          /**< Channel Interrupt Status, offset: 0x22C008 */
  __IO uint32_t CH23_SBR;                          /**< Channel System Bus, offset: 0x22C00C */
  __IO uint32_t CH23_PRI;                          /**< Channel Priority, offset: 0x22C010 */
  uint8_t RESERVED_46[12];
  __IO uint32_t TCD23_SADDR;                       /**< TCD Source Address, offset: 0x22C020 */
  __IO uint16_t TCD23_SOFF;                        /**< TCD Signed Source Address Offset, offset: 0x22C024 */
  __IO uint16_t TCD23_ATTR;                        /**< TCD Transfer Attributes, offset: 0x22C026 */
  union {                                          /* offset: 0x22C028 */
    __IO uint32_t TCD23_NBYTES_MLOFFNO;              /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x22C028 */
    __IO uint32_t TCD23_NBYTES_MLOFFYES;             /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x22C028 */
  } NBYTES23;
  __IO uint32_t TCD23_SLAST_SDA;                   /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x22C02C */
  __IO uint32_t TCD23_DADDR;                       /**< TCD Destination Address, offset: 0x22C030 */
  __IO uint16_t TCD23_DOFF;                        /**< TCD Signed Destination Address Offset, offset: 0x22C034 */
  union {                                          /* offset: 0x22C036 */
    __IO uint16_t TCD23_CITER_ELINKNO;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x22C036 */
    __IO uint16_t TCD23_CITER_ELINKYES;              /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x22C036 */
  } CITER23;
  __IO uint32_t TCD23_DLAST_SGA;                   /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x22C038 */
  __IO uint16_t TCD23_CSR;                         /**< TCD Control and Status, offset: 0x22C03C */
  union {                                          /* offset: 0x22C03E */
    __IO uint16_t TCD23_BITER_ELINKNO;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x22C03E */
    __IO uint16_t TCD23_BITER_ELINKYES;              /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x22C03E */
  } BITER23;
  uint8_t RESERVED_47[16320];
  __IO uint32_t CH24_CSR;                          /**< Channel Control and Status, offset: 0x230000 */
  __IO uint32_t CH24_ES;                           /**< Channel Error Status, offset: 0x230004 */
  __IO uint32_t CH24_INT;                          /**< Channel Interrupt Status, offset: 0x230008 */
  __IO uint32_t CH24_SBR;                          /**< Channel System Bus, offset: 0x23000C */
  __IO uint32_t CH24_PRI;                          /**< Channel Priority, offset: 0x230010 */
  uint8_t RESERVED_48[12];
  __IO uint32_t TCD24_SADDR;                       /**< TCD Source Address, offset: 0x230020 */
  __IO uint16_t TCD24_SOFF;                        /**< TCD Signed Source Address Offset, offset: 0x230024 */
  __IO uint16_t TCD24_ATTR;                        /**< TCD Transfer Attributes, offset: 0x230026 */
  union {                                          /* offset: 0x230028 */
    __IO uint32_t TCD24_NBYTES_MLOFFNO;              /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x230028 */
    __IO uint32_t TCD24_NBYTES_MLOFFYES;             /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x230028 */
  } NBYTES24;
  __IO uint32_t TCD24_SLAST_SDA;                   /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x23002C */
  __IO uint32_t TCD24_DADDR;                       /**< TCD Destination Address, offset: 0x230030 */
  __IO uint16_t TCD24_DOFF;                        /**< TCD Signed Destination Address Offset, offset: 0x230034 */
  union {                                          /* offset: 0x230036 */
    __IO uint16_t TCD24_CITER_ELINKNO;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x230036 */
    __IO uint16_t TCD24_CITER_ELINKYES;              /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x230036 */
  } CITER24;
  __IO uint32_t TCD24_DLAST_SGA;                   /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x230038 */
  __IO uint16_t TCD24_CSR;                         /**< TCD Control and Status, offset: 0x23003C */
  union {                                          /* offset: 0x23003E */
    __IO uint16_t TCD24_BITER_ELINKNO;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x23003E */
    __IO uint16_t TCD24_BITER_ELINKYES;              /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x23003E */
  } BITER24;
  uint8_t RESERVED_49[16320];
  __IO uint32_t CH25_CSR;                          /**< Channel Control and Status, offset: 0x234000 */
  __IO uint32_t CH25_ES;                           /**< Channel Error Status, offset: 0x234004 */
  __IO uint32_t CH25_INT;                          /**< Channel Interrupt Status, offset: 0x234008 */
  __IO uint32_t CH25_SBR;                          /**< Channel System Bus, offset: 0x23400C */
  __IO uint32_t CH25_PRI;                          /**< Channel Priority, offset: 0x234010 */
  uint8_t RESERVED_50[12];
  __IO uint32_t TCD25_SADDR;                       /**< TCD Source Address, offset: 0x234020 */
  __IO uint16_t TCD25_SOFF;                        /**< TCD Signed Source Address Offset, offset: 0x234024 */
  __IO uint16_t TCD25_ATTR;                        /**< TCD Transfer Attributes, offset: 0x234026 */
  union {                                          /* offset: 0x234028 */
    __IO uint32_t TCD25_NBYTES_MLOFFNO;              /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x234028 */
    __IO uint32_t TCD25_NBYTES_MLOFFYES;             /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x234028 */
  } NBYTES25;
  __IO uint32_t TCD25_SLAST_SDA;                   /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x23402C */
  __IO uint32_t TCD25_DADDR;                       /**< TCD Destination Address, offset: 0x234030 */
  __IO uint16_t TCD25_DOFF;                        /**< TCD Signed Destination Address Offset, offset: 0x234034 */
  union {                                          /* offset: 0x234036 */
    __IO uint16_t TCD25_CITER_ELINKNO;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x234036 */
    __IO uint16_t TCD25_CITER_ELINKYES;              /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x234036 */
  } CITER25;
  __IO uint32_t TCD25_DLAST_SGA;                   /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x234038 */
  __IO uint16_t TCD25_CSR;                         /**< TCD Control and Status, offset: 0x23403C */
  union {                                          /* offset: 0x23403E */
    __IO uint16_t TCD25_BITER_ELINKNO;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x23403E */
    __IO uint16_t TCD25_BITER_ELINKYES;              /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x23403E */
  } BITER25;
  uint8_t RESERVED_51[16320];
  __IO uint32_t CH26_CSR;                          /**< Channel Control and Status, offset: 0x238000 */
  __IO uint32_t CH26_ES;                           /**< Channel Error Status, offset: 0x238004 */
  __IO uint32_t CH26_INT;                          /**< Channel Interrupt Status, offset: 0x238008 */
  __IO uint32_t CH26_SBR;                          /**< Channel System Bus, offset: 0x23800C */
  __IO uint32_t CH26_PRI;                          /**< Channel Priority, offset: 0x238010 */
  uint8_t RESERVED_52[12];
  __IO uint32_t TCD26_SADDR;                       /**< TCD Source Address, offset: 0x238020 */
  __IO uint16_t TCD26_SOFF;                        /**< TCD Signed Source Address Offset, offset: 0x238024 */
  __IO uint16_t TCD26_ATTR;                        /**< TCD Transfer Attributes, offset: 0x238026 */
  union {                                          /* offset: 0x238028 */
    __IO uint32_t TCD26_NBYTES_MLOFFNO;              /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x238028 */
    __IO uint32_t TCD26_NBYTES_MLOFFYES;             /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x238028 */
  } NBYTES26;
  __IO uint32_t TCD26_SLAST_SDA;                   /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x23802C */
  __IO uint32_t TCD26_DADDR;                       /**< TCD Destination Address, offset: 0x238030 */
  __IO uint16_t TCD26_DOFF;                        /**< TCD Signed Destination Address Offset, offset: 0x238034 */
  union {                                          /* offset: 0x238036 */
    __IO uint16_t TCD26_CITER_ELINKNO;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x238036 */
    __IO uint16_t TCD26_CITER_ELINKYES;              /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x238036 */
  } CITER26;
  __IO uint32_t TCD26_DLAST_SGA;                   /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x238038 */
  __IO uint16_t TCD26_CSR;                         /**< TCD Control and Status, offset: 0x23803C */
  union {                                          /* offset: 0x23803E */
    __IO uint16_t TCD26_BITER_ELINKNO;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x23803E */
    __IO uint16_t TCD26_BITER_ELINKYES;              /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x23803E */
  } BITER26;
  uint8_t RESERVED_53[16320];
  __IO uint32_t CH27_CSR;                          /**< Channel Control and Status, offset: 0x23C000 */
  __IO uint32_t CH27_ES;                           /**< Channel Error Status, offset: 0x23C004 */
  __IO uint32_t CH27_INT;                          /**< Channel Interrupt Status, offset: 0x23C008 */
  __IO uint32_t CH27_SBR;                          /**< Channel System Bus, offset: 0x23C00C */
  __IO uint32_t CH27_PRI;                          /**< Channel Priority, offset: 0x23C010 */
  uint8_t RESERVED_54[12];
  __IO uint32_t TCD27_SADDR;                       /**< TCD Source Address, offset: 0x23C020 */
  __IO uint16_t TCD27_SOFF;                        /**< TCD Signed Source Address Offset, offset: 0x23C024 */
  __IO uint16_t TCD27_ATTR;                        /**< TCD Transfer Attributes, offset: 0x23C026 */
  union {                                          /* offset: 0x23C028 */
    __IO uint32_t TCD27_NBYTES_MLOFFNO;              /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x23C028 */
    __IO uint32_t TCD27_NBYTES_MLOFFYES;             /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x23C028 */
  } NBYTES27;
  __IO uint32_t TCD27_SLAST_SDA;                   /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x23C02C */
  __IO uint32_t TCD27_DADDR;                       /**< TCD Destination Address, offset: 0x23C030 */
  __IO uint16_t TCD27_DOFF;                        /**< TCD Signed Destination Address Offset, offset: 0x23C034 */
  union {                                          /* offset: 0x23C036 */
    __IO uint16_t TCD27_CITER_ELINKNO;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x23C036 */
    __IO uint16_t TCD27_CITER_ELINKYES;              /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x23C036 */
  } CITER27;
  __IO uint32_t TCD27_DLAST_SGA;                   /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x23C038 */
  __IO uint16_t TCD27_CSR;                         /**< TCD Control and Status, offset: 0x23C03C */
  union {                                          /* offset: 0x23C03E */
    __IO uint16_t TCD27_BITER_ELINKNO;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x23C03E */
    __IO uint16_t TCD27_BITER_ELINKYES;              /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x23C03E */
  } BITER27;
  uint8_t RESERVED_55[16320];
  __IO uint32_t CH28_CSR;                          /**< Channel Control and Status, offset: 0x240000 */
  __IO uint32_t CH28_ES;                           /**< Channel Error Status, offset: 0x240004 */
  __IO uint32_t CH28_INT;                          /**< Channel Interrupt Status, offset: 0x240008 */
  __IO uint32_t CH28_SBR;                          /**< Channel System Bus, offset: 0x24000C */
  __IO uint32_t CH28_PRI;                          /**< Channel Priority, offset: 0x240010 */
  uint8_t RESERVED_56[12];
  __IO uint32_t TCD28_SADDR;                       /**< TCD Source Address, offset: 0x240020 */
  __IO uint16_t TCD28_SOFF;                        /**< TCD Signed Source Address Offset, offset: 0x240024 */
  __IO uint16_t TCD28_ATTR;                        /**< TCD Transfer Attributes, offset: 0x240026 */
  union {                                          /* offset: 0x240028 */
    __IO uint32_t TCD28_NBYTES_MLOFFNO;              /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x240028 */
    __IO uint32_t TCD28_NBYTES_MLOFFYES;             /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x240028 */
  } NBYTES28;
  __IO uint32_t TCD28_SLAST_SDA;                   /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x24002C */
  __IO uint32_t TCD28_DADDR;                       /**< TCD Destination Address, offset: 0x240030 */
  __IO uint16_t TCD28_DOFF;                        /**< TCD Signed Destination Address Offset, offset: 0x240034 */
  union {                                          /* offset: 0x240036 */
    __IO uint16_t TCD28_CITER_ELINKNO;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x240036 */
    __IO uint16_t TCD28_CITER_ELINKYES;              /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x240036 */
  } CITER28;
  __IO uint32_t TCD28_DLAST_SGA;                   /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x240038 */
  __IO uint16_t TCD28_CSR;                         /**< TCD Control and Status, offset: 0x24003C */
  union {                                          /* offset: 0x24003E */
    __IO uint16_t TCD28_BITER_ELINKNO;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x24003E */
    __IO uint16_t TCD28_BITER_ELINKYES;              /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x24003E */
  } BITER28;
  uint8_t RESERVED_57[16320];
  __IO uint32_t CH29_CSR;                          /**< Channel Control and Status, offset: 0x244000 */
  __IO uint32_t CH29_ES;                           /**< Channel Error Status, offset: 0x244004 */
  __IO uint32_t CH29_INT;                          /**< Channel Interrupt Status, offset: 0x244008 */
  __IO uint32_t CH29_SBR;                          /**< Channel System Bus, offset: 0x24400C */
  __IO uint32_t CH29_PRI;                          /**< Channel Priority, offset: 0x244010 */
  uint8_t RESERVED_58[12];
  __IO uint32_t TCD29_SADDR;                       /**< TCD Source Address, offset: 0x244020 */
  __IO uint16_t TCD29_SOFF;                        /**< TCD Signed Source Address Offset, offset: 0x244024 */
  __IO uint16_t TCD29_ATTR;                        /**< TCD Transfer Attributes, offset: 0x244026 */
  union {                                          /* offset: 0x244028 */
    __IO uint32_t TCD29_NBYTES_MLOFFNO;              /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x244028 */
    __IO uint32_t TCD29_NBYTES_MLOFFYES;             /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x244028 */
  } NBYTES29;
  __IO uint32_t TCD29_SLAST_SDA;                   /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x24402C */
  __IO uint32_t TCD29_DADDR;                       /**< TCD Destination Address, offset: 0x244030 */
  __IO uint16_t TCD29_DOFF;                        /**< TCD Signed Destination Address Offset, offset: 0x244034 */
  union {                                          /* offset: 0x244036 */
    __IO uint16_t TCD29_CITER_ELINKNO;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x244036 */
    __IO uint16_t TCD29_CITER_ELINKYES;              /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x244036 */
  } CITER29;
  __IO uint32_t TCD29_DLAST_SGA;                   /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x244038 */
  __IO uint16_t TCD29_CSR;                         /**< TCD Control and Status, offset: 0x24403C */
  union {                                          /* offset: 0x24403E */
    __IO uint16_t TCD29_BITER_ELINKNO;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x24403E */
    __IO uint16_t TCD29_BITER_ELINKYES;              /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x24403E */
  } BITER29;
  uint8_t RESERVED_59[16320];
  __IO uint32_t CH30_CSR;                          /**< Channel Control and Status, offset: 0x248000 */
  __IO uint32_t CH30_ES;                           /**< Channel Error Status, offset: 0x248004 */
  __IO uint32_t CH30_INT;                          /**< Channel Interrupt Status, offset: 0x248008 */
  __IO uint32_t CH30_SBR;                          /**< Channel System Bus, offset: 0x24800C */
  __IO uint32_t CH30_PRI;                          /**< Channel Priority, offset: 0x248010 */
  uint8_t RESERVED_60[12];
  __IO uint32_t TCD30_SADDR;                       /**< TCD Source Address, offset: 0x248020 */
  __IO uint16_t TCD30_SOFF;                        /**< TCD Signed Source Address Offset, offset: 0x248024 */
  __IO uint16_t TCD30_ATTR;                        /**< TCD Transfer Attributes, offset: 0x248026 */
  union {                                          /* offset: 0x248028 */
    __IO uint32_t TCD30_NBYTES_MLOFFNO;              /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x248028 */
    __IO uint32_t TCD30_NBYTES_MLOFFYES;             /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x248028 */
  } NBYTES30;
  __IO uint32_t TCD30_SLAST_SDA;                   /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x24802C */
  __IO uint32_t TCD30_DADDR;                       /**< TCD Destination Address, offset: 0x248030 */
  __IO uint16_t TCD30_DOFF;                        /**< TCD Signed Destination Address Offset, offset: 0x248034 */
  union {                                          /* offset: 0x248036 */
    __IO uint16_t TCD30_CITER_ELINKNO;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x248036 */
    __IO uint16_t TCD30_CITER_ELINKYES;              /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x248036 */
  } CITER30;
  __IO uint32_t TCD30_DLAST_SGA;                   /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x248038 */
  __IO uint16_t TCD30_CSR;                         /**< TCD Control and Status, offset: 0x24803C */
  union {                                          /* offset: 0x24803E */
    __IO uint16_t TCD30_BITER_ELINKNO;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x24803E */
    __IO uint16_t TCD30_BITER_ELINKYES;              /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x24803E */
  } BITER30;
  uint8_t RESERVED_61[16320];
  __IO uint32_t CH31_CSR;                          /**< Channel Control and Status, offset: 0x24C000 */
  __IO uint32_t CH31_ES;                           /**< Channel Error Status, offset: 0x24C004 */
  __IO uint32_t CH31_INT;                          /**< Channel Interrupt Status, offset: 0x24C008 */
  __IO uint32_t CH31_SBR;                          /**< Channel System Bus, offset: 0x24C00C */
  __IO uint32_t CH31_PRI;                          /**< Channel Priority, offset: 0x24C010 */
  uint8_t RESERVED_62[12];
  __IO uint32_t TCD31_SADDR;                       /**< TCD Source Address, offset: 0x24C020 */
  __IO uint16_t TCD31_SOFF;                        /**< TCD Signed Source Address Offset, offset: 0x24C024 */
  __IO uint16_t TCD31_ATTR;                        /**< TCD Transfer Attributes, offset: 0x24C026 */
  union {                                          /* offset: 0x24C028 */
    __IO uint32_t TCD31_NBYTES_MLOFFNO;              /**< TCD Transfer Size Without Minor Loop Offsets, offset: 0x24C028 */
    __IO uint32_t TCD31_NBYTES_MLOFFYES;             /**< TCD Transfer Size with Minor Loop Offsets, offset: 0x24C028 */
  } NBYTES31;
  __IO uint32_t TCD31_SLAST_SDA;                   /**< TCD Last Source Address Adjustment / Store DADDR Address, offset: 0x24C02C */
  __IO uint32_t TCD31_DADDR;                       /**< TCD Destination Address, offset: 0x24C030 */
  __IO uint16_t TCD31_DOFF;                        /**< TCD Signed Destination Address Offset, offset: 0x24C034 */
  union {                                          /* offset: 0x24C036 */
    __IO uint16_t TCD31_CITER_ELINKNO;               /**< TCD Current Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x24C036 */
    __IO uint16_t TCD31_CITER_ELINKYES;              /**< TCD Current Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x24C036 */
  } CITER31;
  __IO uint32_t TCD31_DLAST_SGA;                   /**< TCD Last Destination Address Adjustment / Scatter Gather Address, offset: 0x24C038 */
  __IO uint16_t TCD31_CSR;                         /**< TCD Control and Status, offset: 0x24C03C */
  union {                                          /* offset: 0x24C03E */
    __IO uint16_t TCD31_BITER_ELINKNO;               /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled), offset: 0x24C03E */
    __IO uint16_t TCD31_BITER_ELINKYES;              /**< TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled), offset: 0x24C03E */
  } BITER31;
} DMA_TCD_Type, *DMA_TCD_MemMapPtr;

/** Number of instances of the DMA_TCD module. */
#define DMA_TCD_INSTANCE_COUNT                   (1u)

/* DMA_TCD - Peripheral instance base addresses */
/** Peripheral TCD base address */
#define IP_TCD_BASE                              (0x40210000u)
/** Peripheral TCD base pointer */
#define IP_TCD                                   ((DMA_TCD_Type *)IP_TCD_BASE)
/** Array initializer of DMA_TCD peripheral base addresses */
#define IP_DMA_TCD_BASE_ADDRS                    { IP_TCD_BASE }
/** Array initializer of DMA_TCD peripheral base pointers */
#define IP_DMA_TCD_BASE_PTRS                     { IP_TCD }

/* ----------------------------------------------------------------------------
   -- DMA_TCD Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_TCD_Register_Masks DMA_TCD Register Masks
 * @{
 */

/*! @name CH0_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH0_CSR_ERQ_MASK                 (0x1U)
#define DMA_TCD_CH0_CSR_ERQ_SHIFT                (0U)
#define DMA_TCD_CH0_CSR_ERQ_WIDTH                (1U)
#define DMA_TCD_CH0_CSR_ERQ(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_CSR_ERQ_SHIFT)) & DMA_TCD_CH0_CSR_ERQ_MASK)

#define DMA_TCD_CH0_CSR_EARQ_MASK                (0x2U)
#define DMA_TCD_CH0_CSR_EARQ_SHIFT               (1U)
#define DMA_TCD_CH0_CSR_EARQ_WIDTH               (1U)
#define DMA_TCD_CH0_CSR_EARQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_CSR_EARQ_SHIFT)) & DMA_TCD_CH0_CSR_EARQ_MASK)

#define DMA_TCD_CH0_CSR_EEI_MASK                 (0x4U)
#define DMA_TCD_CH0_CSR_EEI_SHIFT                (2U)
#define DMA_TCD_CH0_CSR_EEI_WIDTH                (1U)
#define DMA_TCD_CH0_CSR_EEI(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_CSR_EEI_SHIFT)) & DMA_TCD_CH0_CSR_EEI_MASK)

#define DMA_TCD_CH0_CSR_EBW_MASK                 (0x8U)
#define DMA_TCD_CH0_CSR_EBW_SHIFT                (3U)
#define DMA_TCD_CH0_CSR_EBW_WIDTH                (1U)
#define DMA_TCD_CH0_CSR_EBW(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_CSR_EBW_SHIFT)) & DMA_TCD_CH0_CSR_EBW_MASK)

#define DMA_TCD_CH0_CSR_DONE_MASK                (0x40000000U)
#define DMA_TCD_CH0_CSR_DONE_SHIFT               (30U)
#define DMA_TCD_CH0_CSR_DONE_WIDTH               (1U)
#define DMA_TCD_CH0_CSR_DONE(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_CSR_DONE_SHIFT)) & DMA_TCD_CH0_CSR_DONE_MASK)

#define DMA_TCD_CH0_CSR_ACTIVE_MASK              (0x80000000U)
#define DMA_TCD_CH0_CSR_ACTIVE_SHIFT             (31U)
#define DMA_TCD_CH0_CSR_ACTIVE_WIDTH             (1U)
#define DMA_TCD_CH0_CSR_ACTIVE(x)                (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH0_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH0_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH0_ES_DBE_MASK                  (0x1U)
#define DMA_TCD_CH0_ES_DBE_SHIFT                 (0U)
#define DMA_TCD_CH0_ES_DBE_WIDTH                 (1U)
#define DMA_TCD_CH0_ES_DBE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_ES_DBE_SHIFT)) & DMA_TCD_CH0_ES_DBE_MASK)

#define DMA_TCD_CH0_ES_SBE_MASK                  (0x2U)
#define DMA_TCD_CH0_ES_SBE_SHIFT                 (1U)
#define DMA_TCD_CH0_ES_SBE_WIDTH                 (1U)
#define DMA_TCD_CH0_ES_SBE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_ES_SBE_SHIFT)) & DMA_TCD_CH0_ES_SBE_MASK)

#define DMA_TCD_CH0_ES_SGE_MASK                  (0x4U)
#define DMA_TCD_CH0_ES_SGE_SHIFT                 (2U)
#define DMA_TCD_CH0_ES_SGE_WIDTH                 (1U)
#define DMA_TCD_CH0_ES_SGE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_ES_SGE_SHIFT)) & DMA_TCD_CH0_ES_SGE_MASK)

#define DMA_TCD_CH0_ES_NCE_MASK                  (0x8U)
#define DMA_TCD_CH0_ES_NCE_SHIFT                 (3U)
#define DMA_TCD_CH0_ES_NCE_WIDTH                 (1U)
#define DMA_TCD_CH0_ES_NCE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_ES_NCE_SHIFT)) & DMA_TCD_CH0_ES_NCE_MASK)

#define DMA_TCD_CH0_ES_DOE_MASK                  (0x10U)
#define DMA_TCD_CH0_ES_DOE_SHIFT                 (4U)
#define DMA_TCD_CH0_ES_DOE_WIDTH                 (1U)
#define DMA_TCD_CH0_ES_DOE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_ES_DOE_SHIFT)) & DMA_TCD_CH0_ES_DOE_MASK)

#define DMA_TCD_CH0_ES_DAE_MASK                  (0x20U)
#define DMA_TCD_CH0_ES_DAE_SHIFT                 (5U)
#define DMA_TCD_CH0_ES_DAE_WIDTH                 (1U)
#define DMA_TCD_CH0_ES_DAE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_ES_DAE_SHIFT)) & DMA_TCD_CH0_ES_DAE_MASK)

#define DMA_TCD_CH0_ES_SOE_MASK                  (0x40U)
#define DMA_TCD_CH0_ES_SOE_SHIFT                 (6U)
#define DMA_TCD_CH0_ES_SOE_WIDTH                 (1U)
#define DMA_TCD_CH0_ES_SOE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_ES_SOE_SHIFT)) & DMA_TCD_CH0_ES_SOE_MASK)

#define DMA_TCD_CH0_ES_SAE_MASK                  (0x80U)
#define DMA_TCD_CH0_ES_SAE_SHIFT                 (7U)
#define DMA_TCD_CH0_ES_SAE_WIDTH                 (1U)
#define DMA_TCD_CH0_ES_SAE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_ES_SAE_SHIFT)) & DMA_TCD_CH0_ES_SAE_MASK)

#define DMA_TCD_CH0_ES_ERR_MASK                  (0x80000000U)
#define DMA_TCD_CH0_ES_ERR_SHIFT                 (31U)
#define DMA_TCD_CH0_ES_ERR_WIDTH                 (1U)
#define DMA_TCD_CH0_ES_ERR(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_ES_ERR_SHIFT)) & DMA_TCD_CH0_ES_ERR_MASK)
/*! @} */

/*! @name CH0_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH0_INT_INT_MASK                 (0x1U)
#define DMA_TCD_CH0_INT_INT_SHIFT                (0U)
#define DMA_TCD_CH0_INT_INT_WIDTH                (1U)
#define DMA_TCD_CH0_INT_INT(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_INT_INT_SHIFT)) & DMA_TCD_CH0_INT_INT_MASK)
/*! @} */

/*! @name CH0_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH0_SBR_MID_MASK                 (0xFU)
#define DMA_TCD_CH0_SBR_MID_SHIFT                (0U)
#define DMA_TCD_CH0_SBR_MID_WIDTH                (4U)
#define DMA_TCD_CH0_SBR_MID(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_SBR_MID_SHIFT)) & DMA_TCD_CH0_SBR_MID_MASK)

#define DMA_TCD_CH0_SBR_PAL_MASK                 (0x8000U)
#define DMA_TCD_CH0_SBR_PAL_SHIFT                (15U)
#define DMA_TCD_CH0_SBR_PAL_WIDTH                (1U)
#define DMA_TCD_CH0_SBR_PAL(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_SBR_PAL_SHIFT)) & DMA_TCD_CH0_SBR_PAL_MASK)

#define DMA_TCD_CH0_SBR_EMI_MASK                 (0x10000U)
#define DMA_TCD_CH0_SBR_EMI_SHIFT                (16U)
#define DMA_TCD_CH0_SBR_EMI_WIDTH                (1U)
#define DMA_TCD_CH0_SBR_EMI(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_SBR_EMI_SHIFT)) & DMA_TCD_CH0_SBR_EMI_MASK)

#define DMA_TCD_CH0_SBR_ATTR_MASK                (0xE0000U)
#define DMA_TCD_CH0_SBR_ATTR_SHIFT               (17U)
#define DMA_TCD_CH0_SBR_ATTR_WIDTH               (3U)
#define DMA_TCD_CH0_SBR_ATTR(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_SBR_ATTR_SHIFT)) & DMA_TCD_CH0_SBR_ATTR_MASK)
/*! @} */

/*! @name CH0_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH0_PRI_APL_MASK                 (0x7U)
#define DMA_TCD_CH0_PRI_APL_SHIFT                (0U)
#define DMA_TCD_CH0_PRI_APL_WIDTH                (3U)
#define DMA_TCD_CH0_PRI_APL(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_PRI_APL_SHIFT)) & DMA_TCD_CH0_PRI_APL_MASK)

#define DMA_TCD_CH0_PRI_DPA_MASK                 (0x40000000U)
#define DMA_TCD_CH0_PRI_DPA_SHIFT                (30U)
#define DMA_TCD_CH0_PRI_DPA_WIDTH                (1U)
#define DMA_TCD_CH0_PRI_DPA(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_PRI_DPA_SHIFT)) & DMA_TCD_CH0_PRI_DPA_MASK)

#define DMA_TCD_CH0_PRI_ECP_MASK                 (0x80000000U)
#define DMA_TCD_CH0_PRI_ECP_SHIFT                (31U)
#define DMA_TCD_CH0_PRI_ECP_WIDTH                (1U)
#define DMA_TCD_CH0_PRI_ECP(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH0_PRI_ECP_SHIFT)) & DMA_TCD_CH0_PRI_ECP_MASK)
/*! @} */

/*! @name TCD0_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD0_SADDR_SADDR_MASK            (0xFFFFFFFFU)
#define DMA_TCD_TCD0_SADDR_SADDR_SHIFT           (0U)
#define DMA_TCD_TCD0_SADDR_SADDR_WIDTH           (32U)
#define DMA_TCD_TCD0_SADDR_SADDR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD0_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD0_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD0_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD0_SOFF_SOFF_MASK              (0xFFFFU)
#define DMA_TCD_TCD0_SOFF_SOFF_SHIFT             (0U)
#define DMA_TCD_TCD0_SOFF_SOFF_WIDTH             (16U)
#define DMA_TCD_TCD0_SOFF_SOFF(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD0_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD0_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD0_ATTR_DSIZE_MASK             (0x7U)
#define DMA_TCD_TCD0_ATTR_DSIZE_SHIFT            (0U)
#define DMA_TCD_TCD0_ATTR_DSIZE_WIDTH            (3U)
#define DMA_TCD_TCD0_ATTR_DSIZE(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD0_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD0_ATTR_DMOD_MASK              (0xF8U)
#define DMA_TCD_TCD0_ATTR_DMOD_SHIFT             (3U)
#define DMA_TCD_TCD0_ATTR_DMOD_WIDTH             (5U)
#define DMA_TCD_TCD0_ATTR_DMOD(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD0_ATTR_DMOD_MASK)

#define DMA_TCD_TCD0_ATTR_SSIZE_MASK             (0x700U)
#define DMA_TCD_TCD0_ATTR_SSIZE_SHIFT            (8U)
#define DMA_TCD_TCD0_ATTR_SSIZE_WIDTH            (3U)
#define DMA_TCD_TCD0_ATTR_SSIZE(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD0_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD0_ATTR_SMOD_MASK              (0xF800U)
#define DMA_TCD_TCD0_ATTR_SMOD_SHIFT             (11U)
#define DMA_TCD_TCD0_ATTR_SMOD_WIDTH             (5U)
#define DMA_TCD_TCD0_ATTR_SMOD(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD0_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD0_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD0_NBYTES_MLOFFNO_NBYTES_MASK  (0x3FFFFFFFU)
#define DMA_TCD_TCD0_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD0_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD0_NBYTES_MLOFFNO_NBYTES(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD0_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD0_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD0_NBYTES_MLOFFNO_DMLOE_MASK   (0x40000000U)
#define DMA_TCD_TCD0_NBYTES_MLOFFNO_DMLOE_SHIFT  (30U)
#define DMA_TCD_TCD0_NBYTES_MLOFFNO_DMLOE_WIDTH  (1U)
#define DMA_TCD_TCD0_NBYTES_MLOFFNO_DMLOE(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD0_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD0_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD0_NBYTES_MLOFFNO_SMLOE_MASK   (0x80000000U)
#define DMA_TCD_TCD0_NBYTES_MLOFFNO_SMLOE_SHIFT  (31U)
#define DMA_TCD_TCD0_NBYTES_MLOFFNO_SMLOE_WIDTH  (1U)
#define DMA_TCD_TCD0_NBYTES_MLOFFNO_SMLOE(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD0_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD0_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD0_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD0_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD0_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD0_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD0_NBYTES_MLOFFYES_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD0_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD0_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD0_NBYTES_MLOFFYES_MLOFF_MASK  (0x3FFFFC00U)
#define DMA_TCD_TCD0_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD0_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD0_NBYTES_MLOFFYES_MLOFF(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD0_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD0_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD0_NBYTES_MLOFFYES_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD0_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD0_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD0_NBYTES_MLOFFYES_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD0_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD0_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD0_NBYTES_MLOFFYES_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD0_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD0_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD0_NBYTES_MLOFFYES_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD0_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD0_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD0_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD0_SLAST_SDA_SLAST_SDA_MASK    (0xFFFFFFFFU)
#define DMA_TCD_TCD0_SLAST_SDA_SLAST_SDA_SHIFT   (0U)
#define DMA_TCD_TCD0_SLAST_SDA_SLAST_SDA_WIDTH   (32U)
#define DMA_TCD_TCD0_SLAST_SDA_SLAST_SDA(x)      (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD0_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD0_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD0_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD0_DADDR_DADDR_MASK            (0xFFFFFFFFU)
#define DMA_TCD_TCD0_DADDR_DADDR_SHIFT           (0U)
#define DMA_TCD_TCD0_DADDR_DADDR_WIDTH           (32U)
#define DMA_TCD_TCD0_DADDR_DADDR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD0_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD0_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD0_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD0_DOFF_DOFF_MASK              (0xFFFFU)
#define DMA_TCD_TCD0_DOFF_DOFF_SHIFT             (0U)
#define DMA_TCD_TCD0_DOFF_DOFF_WIDTH             (16U)
#define DMA_TCD_TCD0_DOFF_DOFF(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD0_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD0_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD0_CITER_ELINKNO_CITER_MASK    (0x7FFFU)
#define DMA_TCD_TCD0_CITER_ELINKNO_CITER_SHIFT   (0U)
#define DMA_TCD_TCD0_CITER_ELINKNO_CITER_WIDTH   (15U)
#define DMA_TCD_TCD0_CITER_ELINKNO_CITER(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD0_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD0_CITER_ELINKNO_ELINK_MASK    (0x8000U)
#define DMA_TCD_TCD0_CITER_ELINKNO_ELINK_SHIFT   (15U)
#define DMA_TCD_TCD0_CITER_ELINKNO_ELINK_WIDTH   (1U)
#define DMA_TCD_TCD0_CITER_ELINKNO_ELINK(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD0_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD0_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD0_CITER_ELINKYES_CITER_MASK   (0x1FFU)
#define DMA_TCD_TCD0_CITER_ELINKYES_CITER_SHIFT  (0U)
#define DMA_TCD_TCD0_CITER_ELINKYES_CITER_WIDTH  (9U)
#define DMA_TCD_TCD0_CITER_ELINKYES_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD0_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD0_CITER_ELINKYES_LINKCH_MASK  (0x3E00U)
#define DMA_TCD_TCD0_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD0_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD0_CITER_ELINKYES_LINKCH(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD0_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD0_CITER_ELINKYES_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD0_CITER_ELINKYES_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD0_CITER_ELINKYES_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD0_CITER_ELINKYES_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD0_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD0_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD0_DLAST_SGA_DLAST_SGA_MASK    (0xFFFFFFFFU)
#define DMA_TCD_TCD0_DLAST_SGA_DLAST_SGA_SHIFT   (0U)
#define DMA_TCD_TCD0_DLAST_SGA_DLAST_SGA_WIDTH   (32U)
#define DMA_TCD_TCD0_DLAST_SGA_DLAST_SGA(x)      (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD0_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD0_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD0_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD0_CSR_START_MASK              (0x1U)
#define DMA_TCD_TCD0_CSR_START_SHIFT             (0U)
#define DMA_TCD_TCD0_CSR_START_WIDTH             (1U)
#define DMA_TCD_TCD0_CSR_START(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_CSR_START_SHIFT)) & DMA_TCD_TCD0_CSR_START_MASK)

#define DMA_TCD_TCD0_CSR_INTMAJOR_MASK           (0x2U)
#define DMA_TCD_TCD0_CSR_INTMAJOR_SHIFT          (1U)
#define DMA_TCD_TCD0_CSR_INTMAJOR_WIDTH          (1U)
#define DMA_TCD_TCD0_CSR_INTMAJOR(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD0_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD0_CSR_INTHALF_MASK            (0x4U)
#define DMA_TCD_TCD0_CSR_INTHALF_SHIFT           (2U)
#define DMA_TCD_TCD0_CSR_INTHALF_WIDTH           (1U)
#define DMA_TCD_TCD0_CSR_INTHALF(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD0_CSR_INTHALF_MASK)

#define DMA_TCD_TCD0_CSR_DREQ_MASK               (0x8U)
#define DMA_TCD_TCD0_CSR_DREQ_SHIFT              (3U)
#define DMA_TCD_TCD0_CSR_DREQ_WIDTH              (1U)
#define DMA_TCD_TCD0_CSR_DREQ(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_CSR_DREQ_SHIFT)) & DMA_TCD_TCD0_CSR_DREQ_MASK)

#define DMA_TCD_TCD0_CSR_ESG_MASK                (0x10U)
#define DMA_TCD_TCD0_CSR_ESG_SHIFT               (4U)
#define DMA_TCD_TCD0_CSR_ESG_WIDTH               (1U)
#define DMA_TCD_TCD0_CSR_ESG(x)                  (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_CSR_ESG_SHIFT)) & DMA_TCD_TCD0_CSR_ESG_MASK)

#define DMA_TCD_TCD0_CSR_MAJORELINK_MASK         (0x20U)
#define DMA_TCD_TCD0_CSR_MAJORELINK_SHIFT        (5U)
#define DMA_TCD_TCD0_CSR_MAJORELINK_WIDTH        (1U)
#define DMA_TCD_TCD0_CSR_MAJORELINK(x)           (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD0_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD0_CSR_EEOP_MASK               (0x40U)
#define DMA_TCD_TCD0_CSR_EEOP_SHIFT              (6U)
#define DMA_TCD_TCD0_CSR_EEOP_WIDTH              (1U)
#define DMA_TCD_TCD0_CSR_EEOP(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_CSR_EEOP_SHIFT)) & DMA_TCD_TCD0_CSR_EEOP_MASK)

#define DMA_TCD_TCD0_CSR_ESDA_MASK               (0x80U)
#define DMA_TCD_TCD0_CSR_ESDA_SHIFT              (7U)
#define DMA_TCD_TCD0_CSR_ESDA_WIDTH              (1U)
#define DMA_TCD_TCD0_CSR_ESDA(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_CSR_ESDA_SHIFT)) & DMA_TCD_TCD0_CSR_ESDA_MASK)

#define DMA_TCD_TCD0_CSR_MAJORLINKCH_MASK        (0x1F00U)
#define DMA_TCD_TCD0_CSR_MAJORLINKCH_SHIFT       (8U)
#define DMA_TCD_TCD0_CSR_MAJORLINKCH_WIDTH       (5U)
#define DMA_TCD_TCD0_CSR_MAJORLINKCH(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD0_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD0_CSR_BWC_MASK                (0xC000U)
#define DMA_TCD_TCD0_CSR_BWC_SHIFT               (14U)
#define DMA_TCD_TCD0_CSR_BWC_WIDTH               (2U)
#define DMA_TCD_TCD0_CSR_BWC(x)                  (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_CSR_BWC_SHIFT)) & DMA_TCD_TCD0_CSR_BWC_MASK)
/*! @} */

/*! @name TCD0_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD0_BITER_ELINKNO_BITER_MASK    (0x7FFFU)
#define DMA_TCD_TCD0_BITER_ELINKNO_BITER_SHIFT   (0U)
#define DMA_TCD_TCD0_BITER_ELINKNO_BITER_WIDTH   (15U)
#define DMA_TCD_TCD0_BITER_ELINKNO_BITER(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD0_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD0_BITER_ELINKNO_ELINK_MASK    (0x8000U)
#define DMA_TCD_TCD0_BITER_ELINKNO_ELINK_SHIFT   (15U)
#define DMA_TCD_TCD0_BITER_ELINKNO_ELINK_WIDTH   (1U)
#define DMA_TCD_TCD0_BITER_ELINKNO_ELINK(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD0_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD0_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD0_BITER_ELINKYES_BITER_MASK   (0x1FFU)
#define DMA_TCD_TCD0_BITER_ELINKYES_BITER_SHIFT  (0U)
#define DMA_TCD_TCD0_BITER_ELINKYES_BITER_WIDTH  (9U)
#define DMA_TCD_TCD0_BITER_ELINKYES_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD0_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD0_BITER_ELINKYES_LINKCH_MASK  (0x3E00U)
#define DMA_TCD_TCD0_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD0_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD0_BITER_ELINKYES_LINKCH(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD0_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD0_BITER_ELINKYES_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD0_BITER_ELINKYES_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD0_BITER_ELINKYES_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD0_BITER_ELINKYES_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD0_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD0_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH1_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH1_CSR_ERQ_MASK                 (0x1U)
#define DMA_TCD_CH1_CSR_ERQ_SHIFT                (0U)
#define DMA_TCD_CH1_CSR_ERQ_WIDTH                (1U)
#define DMA_TCD_CH1_CSR_ERQ(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_CSR_ERQ_SHIFT)) & DMA_TCD_CH1_CSR_ERQ_MASK)

#define DMA_TCD_CH1_CSR_EARQ_MASK                (0x2U)
#define DMA_TCD_CH1_CSR_EARQ_SHIFT               (1U)
#define DMA_TCD_CH1_CSR_EARQ_WIDTH               (1U)
#define DMA_TCD_CH1_CSR_EARQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_CSR_EARQ_SHIFT)) & DMA_TCD_CH1_CSR_EARQ_MASK)

#define DMA_TCD_CH1_CSR_EEI_MASK                 (0x4U)
#define DMA_TCD_CH1_CSR_EEI_SHIFT                (2U)
#define DMA_TCD_CH1_CSR_EEI_WIDTH                (1U)
#define DMA_TCD_CH1_CSR_EEI(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_CSR_EEI_SHIFT)) & DMA_TCD_CH1_CSR_EEI_MASK)

#define DMA_TCD_CH1_CSR_EBW_MASK                 (0x8U)
#define DMA_TCD_CH1_CSR_EBW_SHIFT                (3U)
#define DMA_TCD_CH1_CSR_EBW_WIDTH                (1U)
#define DMA_TCD_CH1_CSR_EBW(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_CSR_EBW_SHIFT)) & DMA_TCD_CH1_CSR_EBW_MASK)

#define DMA_TCD_CH1_CSR_DONE_MASK                (0x40000000U)
#define DMA_TCD_CH1_CSR_DONE_SHIFT               (30U)
#define DMA_TCD_CH1_CSR_DONE_WIDTH               (1U)
#define DMA_TCD_CH1_CSR_DONE(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_CSR_DONE_SHIFT)) & DMA_TCD_CH1_CSR_DONE_MASK)

#define DMA_TCD_CH1_CSR_ACTIVE_MASK              (0x80000000U)
#define DMA_TCD_CH1_CSR_ACTIVE_SHIFT             (31U)
#define DMA_TCD_CH1_CSR_ACTIVE_WIDTH             (1U)
#define DMA_TCD_CH1_CSR_ACTIVE(x)                (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH1_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH1_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH1_ES_DBE_MASK                  (0x1U)
#define DMA_TCD_CH1_ES_DBE_SHIFT                 (0U)
#define DMA_TCD_CH1_ES_DBE_WIDTH                 (1U)
#define DMA_TCD_CH1_ES_DBE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_ES_DBE_SHIFT)) & DMA_TCD_CH1_ES_DBE_MASK)

#define DMA_TCD_CH1_ES_SBE_MASK                  (0x2U)
#define DMA_TCD_CH1_ES_SBE_SHIFT                 (1U)
#define DMA_TCD_CH1_ES_SBE_WIDTH                 (1U)
#define DMA_TCD_CH1_ES_SBE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_ES_SBE_SHIFT)) & DMA_TCD_CH1_ES_SBE_MASK)

#define DMA_TCD_CH1_ES_SGE_MASK                  (0x4U)
#define DMA_TCD_CH1_ES_SGE_SHIFT                 (2U)
#define DMA_TCD_CH1_ES_SGE_WIDTH                 (1U)
#define DMA_TCD_CH1_ES_SGE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_ES_SGE_SHIFT)) & DMA_TCD_CH1_ES_SGE_MASK)

#define DMA_TCD_CH1_ES_NCE_MASK                  (0x8U)
#define DMA_TCD_CH1_ES_NCE_SHIFT                 (3U)
#define DMA_TCD_CH1_ES_NCE_WIDTH                 (1U)
#define DMA_TCD_CH1_ES_NCE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_ES_NCE_SHIFT)) & DMA_TCD_CH1_ES_NCE_MASK)

#define DMA_TCD_CH1_ES_DOE_MASK                  (0x10U)
#define DMA_TCD_CH1_ES_DOE_SHIFT                 (4U)
#define DMA_TCD_CH1_ES_DOE_WIDTH                 (1U)
#define DMA_TCD_CH1_ES_DOE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_ES_DOE_SHIFT)) & DMA_TCD_CH1_ES_DOE_MASK)

#define DMA_TCD_CH1_ES_DAE_MASK                  (0x20U)
#define DMA_TCD_CH1_ES_DAE_SHIFT                 (5U)
#define DMA_TCD_CH1_ES_DAE_WIDTH                 (1U)
#define DMA_TCD_CH1_ES_DAE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_ES_DAE_SHIFT)) & DMA_TCD_CH1_ES_DAE_MASK)

#define DMA_TCD_CH1_ES_SOE_MASK                  (0x40U)
#define DMA_TCD_CH1_ES_SOE_SHIFT                 (6U)
#define DMA_TCD_CH1_ES_SOE_WIDTH                 (1U)
#define DMA_TCD_CH1_ES_SOE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_ES_SOE_SHIFT)) & DMA_TCD_CH1_ES_SOE_MASK)

#define DMA_TCD_CH1_ES_SAE_MASK                  (0x80U)
#define DMA_TCD_CH1_ES_SAE_SHIFT                 (7U)
#define DMA_TCD_CH1_ES_SAE_WIDTH                 (1U)
#define DMA_TCD_CH1_ES_SAE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_ES_SAE_SHIFT)) & DMA_TCD_CH1_ES_SAE_MASK)

#define DMA_TCD_CH1_ES_ERR_MASK                  (0x80000000U)
#define DMA_TCD_CH1_ES_ERR_SHIFT                 (31U)
#define DMA_TCD_CH1_ES_ERR_WIDTH                 (1U)
#define DMA_TCD_CH1_ES_ERR(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_ES_ERR_SHIFT)) & DMA_TCD_CH1_ES_ERR_MASK)
/*! @} */

/*! @name CH1_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH1_INT_INT_MASK                 (0x1U)
#define DMA_TCD_CH1_INT_INT_SHIFT                (0U)
#define DMA_TCD_CH1_INT_INT_WIDTH                (1U)
#define DMA_TCD_CH1_INT_INT(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_INT_INT_SHIFT)) & DMA_TCD_CH1_INT_INT_MASK)
/*! @} */

/*! @name CH1_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH1_SBR_MID_MASK                 (0xFU)
#define DMA_TCD_CH1_SBR_MID_SHIFT                (0U)
#define DMA_TCD_CH1_SBR_MID_WIDTH                (4U)
#define DMA_TCD_CH1_SBR_MID(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_SBR_MID_SHIFT)) & DMA_TCD_CH1_SBR_MID_MASK)

#define DMA_TCD_CH1_SBR_PAL_MASK                 (0x8000U)
#define DMA_TCD_CH1_SBR_PAL_SHIFT                (15U)
#define DMA_TCD_CH1_SBR_PAL_WIDTH                (1U)
#define DMA_TCD_CH1_SBR_PAL(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_SBR_PAL_SHIFT)) & DMA_TCD_CH1_SBR_PAL_MASK)

#define DMA_TCD_CH1_SBR_EMI_MASK                 (0x10000U)
#define DMA_TCD_CH1_SBR_EMI_SHIFT                (16U)
#define DMA_TCD_CH1_SBR_EMI_WIDTH                (1U)
#define DMA_TCD_CH1_SBR_EMI(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_SBR_EMI_SHIFT)) & DMA_TCD_CH1_SBR_EMI_MASK)

#define DMA_TCD_CH1_SBR_ATTR_MASK                (0xE0000U)
#define DMA_TCD_CH1_SBR_ATTR_SHIFT               (17U)
#define DMA_TCD_CH1_SBR_ATTR_WIDTH               (3U)
#define DMA_TCD_CH1_SBR_ATTR(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_SBR_ATTR_SHIFT)) & DMA_TCD_CH1_SBR_ATTR_MASK)
/*! @} */

/*! @name CH1_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH1_PRI_APL_MASK                 (0x7U)
#define DMA_TCD_CH1_PRI_APL_SHIFT                (0U)
#define DMA_TCD_CH1_PRI_APL_WIDTH                (3U)
#define DMA_TCD_CH1_PRI_APL(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_PRI_APL_SHIFT)) & DMA_TCD_CH1_PRI_APL_MASK)

#define DMA_TCD_CH1_PRI_DPA_MASK                 (0x40000000U)
#define DMA_TCD_CH1_PRI_DPA_SHIFT                (30U)
#define DMA_TCD_CH1_PRI_DPA_WIDTH                (1U)
#define DMA_TCD_CH1_PRI_DPA(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_PRI_DPA_SHIFT)) & DMA_TCD_CH1_PRI_DPA_MASK)

#define DMA_TCD_CH1_PRI_ECP_MASK                 (0x80000000U)
#define DMA_TCD_CH1_PRI_ECP_SHIFT                (31U)
#define DMA_TCD_CH1_PRI_ECP_WIDTH                (1U)
#define DMA_TCD_CH1_PRI_ECP(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH1_PRI_ECP_SHIFT)) & DMA_TCD_CH1_PRI_ECP_MASK)
/*! @} */

/*! @name TCD1_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD1_SADDR_SADDR_MASK            (0xFFFFFFFFU)
#define DMA_TCD_TCD1_SADDR_SADDR_SHIFT           (0U)
#define DMA_TCD_TCD1_SADDR_SADDR_WIDTH           (32U)
#define DMA_TCD_TCD1_SADDR_SADDR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD1_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD1_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD1_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD1_SOFF_SOFF_MASK              (0xFFFFU)
#define DMA_TCD_TCD1_SOFF_SOFF_SHIFT             (0U)
#define DMA_TCD_TCD1_SOFF_SOFF_WIDTH             (16U)
#define DMA_TCD_TCD1_SOFF_SOFF(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD1_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD1_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD1_ATTR_DSIZE_MASK             (0x7U)
#define DMA_TCD_TCD1_ATTR_DSIZE_SHIFT            (0U)
#define DMA_TCD_TCD1_ATTR_DSIZE_WIDTH            (3U)
#define DMA_TCD_TCD1_ATTR_DSIZE(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD1_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD1_ATTR_DMOD_MASK              (0xF8U)
#define DMA_TCD_TCD1_ATTR_DMOD_SHIFT             (3U)
#define DMA_TCD_TCD1_ATTR_DMOD_WIDTH             (5U)
#define DMA_TCD_TCD1_ATTR_DMOD(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD1_ATTR_DMOD_MASK)

#define DMA_TCD_TCD1_ATTR_SSIZE_MASK             (0x700U)
#define DMA_TCD_TCD1_ATTR_SSIZE_SHIFT            (8U)
#define DMA_TCD_TCD1_ATTR_SSIZE_WIDTH            (3U)
#define DMA_TCD_TCD1_ATTR_SSIZE(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD1_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD1_ATTR_SMOD_MASK              (0xF800U)
#define DMA_TCD_TCD1_ATTR_SMOD_SHIFT             (11U)
#define DMA_TCD_TCD1_ATTR_SMOD_WIDTH             (5U)
#define DMA_TCD_TCD1_ATTR_SMOD(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD1_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD1_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD1_NBYTES_MLOFFNO_NBYTES_MASK  (0x3FFFFFFFU)
#define DMA_TCD_TCD1_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD1_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD1_NBYTES_MLOFFNO_NBYTES(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD1_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD1_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD1_NBYTES_MLOFFNO_DMLOE_MASK   (0x40000000U)
#define DMA_TCD_TCD1_NBYTES_MLOFFNO_DMLOE_SHIFT  (30U)
#define DMA_TCD_TCD1_NBYTES_MLOFFNO_DMLOE_WIDTH  (1U)
#define DMA_TCD_TCD1_NBYTES_MLOFFNO_DMLOE(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD1_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD1_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD1_NBYTES_MLOFFNO_SMLOE_MASK   (0x80000000U)
#define DMA_TCD_TCD1_NBYTES_MLOFFNO_SMLOE_SHIFT  (31U)
#define DMA_TCD_TCD1_NBYTES_MLOFFNO_SMLOE_WIDTH  (1U)
#define DMA_TCD_TCD1_NBYTES_MLOFFNO_SMLOE(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD1_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD1_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD1_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD1_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD1_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD1_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD1_NBYTES_MLOFFYES_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD1_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD1_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD1_NBYTES_MLOFFYES_MLOFF_MASK  (0x3FFFFC00U)
#define DMA_TCD_TCD1_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD1_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD1_NBYTES_MLOFFYES_MLOFF(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD1_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD1_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD1_NBYTES_MLOFFYES_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD1_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD1_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD1_NBYTES_MLOFFYES_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD1_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD1_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD1_NBYTES_MLOFFYES_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD1_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD1_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD1_NBYTES_MLOFFYES_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD1_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD1_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD1_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD1_SLAST_SDA_SLAST_SDA_MASK    (0xFFFFFFFFU)
#define DMA_TCD_TCD1_SLAST_SDA_SLAST_SDA_SHIFT   (0U)
#define DMA_TCD_TCD1_SLAST_SDA_SLAST_SDA_WIDTH   (32U)
#define DMA_TCD_TCD1_SLAST_SDA_SLAST_SDA(x)      (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD1_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD1_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD1_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD1_DADDR_DADDR_MASK            (0xFFFFFFFFU)
#define DMA_TCD_TCD1_DADDR_DADDR_SHIFT           (0U)
#define DMA_TCD_TCD1_DADDR_DADDR_WIDTH           (32U)
#define DMA_TCD_TCD1_DADDR_DADDR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD1_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD1_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD1_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD1_DOFF_DOFF_MASK              (0xFFFFU)
#define DMA_TCD_TCD1_DOFF_DOFF_SHIFT             (0U)
#define DMA_TCD_TCD1_DOFF_DOFF_WIDTH             (16U)
#define DMA_TCD_TCD1_DOFF_DOFF(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD1_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD1_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD1_CITER_ELINKNO_CITER_MASK    (0x7FFFU)
#define DMA_TCD_TCD1_CITER_ELINKNO_CITER_SHIFT   (0U)
#define DMA_TCD_TCD1_CITER_ELINKNO_CITER_WIDTH   (15U)
#define DMA_TCD_TCD1_CITER_ELINKNO_CITER(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD1_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD1_CITER_ELINKNO_ELINK_MASK    (0x8000U)
#define DMA_TCD_TCD1_CITER_ELINKNO_ELINK_SHIFT   (15U)
#define DMA_TCD_TCD1_CITER_ELINKNO_ELINK_WIDTH   (1U)
#define DMA_TCD_TCD1_CITER_ELINKNO_ELINK(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD1_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD1_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD1_CITER_ELINKYES_CITER_MASK   (0x1FFU)
#define DMA_TCD_TCD1_CITER_ELINKYES_CITER_SHIFT  (0U)
#define DMA_TCD_TCD1_CITER_ELINKYES_CITER_WIDTH  (9U)
#define DMA_TCD_TCD1_CITER_ELINKYES_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD1_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD1_CITER_ELINKYES_LINKCH_MASK  (0x3E00U)
#define DMA_TCD_TCD1_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD1_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD1_CITER_ELINKYES_LINKCH(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD1_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD1_CITER_ELINKYES_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD1_CITER_ELINKYES_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD1_CITER_ELINKYES_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD1_CITER_ELINKYES_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD1_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD1_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD1_DLAST_SGA_DLAST_SGA_MASK    (0xFFFFFFFFU)
#define DMA_TCD_TCD1_DLAST_SGA_DLAST_SGA_SHIFT   (0U)
#define DMA_TCD_TCD1_DLAST_SGA_DLAST_SGA_WIDTH   (32U)
#define DMA_TCD_TCD1_DLAST_SGA_DLAST_SGA(x)      (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD1_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD1_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD1_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD1_CSR_START_MASK              (0x1U)
#define DMA_TCD_TCD1_CSR_START_SHIFT             (0U)
#define DMA_TCD_TCD1_CSR_START_WIDTH             (1U)
#define DMA_TCD_TCD1_CSR_START(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_CSR_START_SHIFT)) & DMA_TCD_TCD1_CSR_START_MASK)

#define DMA_TCD_TCD1_CSR_INTMAJOR_MASK           (0x2U)
#define DMA_TCD_TCD1_CSR_INTMAJOR_SHIFT          (1U)
#define DMA_TCD_TCD1_CSR_INTMAJOR_WIDTH          (1U)
#define DMA_TCD_TCD1_CSR_INTMAJOR(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD1_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD1_CSR_INTHALF_MASK            (0x4U)
#define DMA_TCD_TCD1_CSR_INTHALF_SHIFT           (2U)
#define DMA_TCD_TCD1_CSR_INTHALF_WIDTH           (1U)
#define DMA_TCD_TCD1_CSR_INTHALF(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD1_CSR_INTHALF_MASK)

#define DMA_TCD_TCD1_CSR_DREQ_MASK               (0x8U)
#define DMA_TCD_TCD1_CSR_DREQ_SHIFT              (3U)
#define DMA_TCD_TCD1_CSR_DREQ_WIDTH              (1U)
#define DMA_TCD_TCD1_CSR_DREQ(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_CSR_DREQ_SHIFT)) & DMA_TCD_TCD1_CSR_DREQ_MASK)

#define DMA_TCD_TCD1_CSR_ESG_MASK                (0x10U)
#define DMA_TCD_TCD1_CSR_ESG_SHIFT               (4U)
#define DMA_TCD_TCD1_CSR_ESG_WIDTH               (1U)
#define DMA_TCD_TCD1_CSR_ESG(x)                  (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_CSR_ESG_SHIFT)) & DMA_TCD_TCD1_CSR_ESG_MASK)

#define DMA_TCD_TCD1_CSR_MAJORELINK_MASK         (0x20U)
#define DMA_TCD_TCD1_CSR_MAJORELINK_SHIFT        (5U)
#define DMA_TCD_TCD1_CSR_MAJORELINK_WIDTH        (1U)
#define DMA_TCD_TCD1_CSR_MAJORELINK(x)           (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD1_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD1_CSR_EEOP_MASK               (0x40U)
#define DMA_TCD_TCD1_CSR_EEOP_SHIFT              (6U)
#define DMA_TCD_TCD1_CSR_EEOP_WIDTH              (1U)
#define DMA_TCD_TCD1_CSR_EEOP(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_CSR_EEOP_SHIFT)) & DMA_TCD_TCD1_CSR_EEOP_MASK)

#define DMA_TCD_TCD1_CSR_ESDA_MASK               (0x80U)
#define DMA_TCD_TCD1_CSR_ESDA_SHIFT              (7U)
#define DMA_TCD_TCD1_CSR_ESDA_WIDTH              (1U)
#define DMA_TCD_TCD1_CSR_ESDA(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_CSR_ESDA_SHIFT)) & DMA_TCD_TCD1_CSR_ESDA_MASK)

#define DMA_TCD_TCD1_CSR_MAJORLINKCH_MASK        (0x1F00U)
#define DMA_TCD_TCD1_CSR_MAJORLINKCH_SHIFT       (8U)
#define DMA_TCD_TCD1_CSR_MAJORLINKCH_WIDTH       (5U)
#define DMA_TCD_TCD1_CSR_MAJORLINKCH(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD1_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD1_CSR_BWC_MASK                (0xC000U)
#define DMA_TCD_TCD1_CSR_BWC_SHIFT               (14U)
#define DMA_TCD_TCD1_CSR_BWC_WIDTH               (2U)
#define DMA_TCD_TCD1_CSR_BWC(x)                  (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_CSR_BWC_SHIFT)) & DMA_TCD_TCD1_CSR_BWC_MASK)
/*! @} */

/*! @name TCD1_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD1_BITER_ELINKNO_BITER_MASK    (0x7FFFU)
#define DMA_TCD_TCD1_BITER_ELINKNO_BITER_SHIFT   (0U)
#define DMA_TCD_TCD1_BITER_ELINKNO_BITER_WIDTH   (15U)
#define DMA_TCD_TCD1_BITER_ELINKNO_BITER(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD1_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD1_BITER_ELINKNO_ELINK_MASK    (0x8000U)
#define DMA_TCD_TCD1_BITER_ELINKNO_ELINK_SHIFT   (15U)
#define DMA_TCD_TCD1_BITER_ELINKNO_ELINK_WIDTH   (1U)
#define DMA_TCD_TCD1_BITER_ELINKNO_ELINK(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD1_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD1_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD1_BITER_ELINKYES_BITER_MASK   (0x1FFU)
#define DMA_TCD_TCD1_BITER_ELINKYES_BITER_SHIFT  (0U)
#define DMA_TCD_TCD1_BITER_ELINKYES_BITER_WIDTH  (9U)
#define DMA_TCD_TCD1_BITER_ELINKYES_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD1_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD1_BITER_ELINKYES_LINKCH_MASK  (0x3E00U)
#define DMA_TCD_TCD1_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD1_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD1_BITER_ELINKYES_LINKCH(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD1_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD1_BITER_ELINKYES_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD1_BITER_ELINKYES_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD1_BITER_ELINKYES_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD1_BITER_ELINKYES_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD1_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD1_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH2_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH2_CSR_ERQ_MASK                 (0x1U)
#define DMA_TCD_CH2_CSR_ERQ_SHIFT                (0U)
#define DMA_TCD_CH2_CSR_ERQ_WIDTH                (1U)
#define DMA_TCD_CH2_CSR_ERQ(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_CSR_ERQ_SHIFT)) & DMA_TCD_CH2_CSR_ERQ_MASK)

#define DMA_TCD_CH2_CSR_EARQ_MASK                (0x2U)
#define DMA_TCD_CH2_CSR_EARQ_SHIFT               (1U)
#define DMA_TCD_CH2_CSR_EARQ_WIDTH               (1U)
#define DMA_TCD_CH2_CSR_EARQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_CSR_EARQ_SHIFT)) & DMA_TCD_CH2_CSR_EARQ_MASK)

#define DMA_TCD_CH2_CSR_EEI_MASK                 (0x4U)
#define DMA_TCD_CH2_CSR_EEI_SHIFT                (2U)
#define DMA_TCD_CH2_CSR_EEI_WIDTH                (1U)
#define DMA_TCD_CH2_CSR_EEI(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_CSR_EEI_SHIFT)) & DMA_TCD_CH2_CSR_EEI_MASK)

#define DMA_TCD_CH2_CSR_EBW_MASK                 (0x8U)
#define DMA_TCD_CH2_CSR_EBW_SHIFT                (3U)
#define DMA_TCD_CH2_CSR_EBW_WIDTH                (1U)
#define DMA_TCD_CH2_CSR_EBW(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_CSR_EBW_SHIFT)) & DMA_TCD_CH2_CSR_EBW_MASK)

#define DMA_TCD_CH2_CSR_DONE_MASK                (0x40000000U)
#define DMA_TCD_CH2_CSR_DONE_SHIFT               (30U)
#define DMA_TCD_CH2_CSR_DONE_WIDTH               (1U)
#define DMA_TCD_CH2_CSR_DONE(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_CSR_DONE_SHIFT)) & DMA_TCD_CH2_CSR_DONE_MASK)

#define DMA_TCD_CH2_CSR_ACTIVE_MASK              (0x80000000U)
#define DMA_TCD_CH2_CSR_ACTIVE_SHIFT             (31U)
#define DMA_TCD_CH2_CSR_ACTIVE_WIDTH             (1U)
#define DMA_TCD_CH2_CSR_ACTIVE(x)                (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH2_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH2_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH2_ES_DBE_MASK                  (0x1U)
#define DMA_TCD_CH2_ES_DBE_SHIFT                 (0U)
#define DMA_TCD_CH2_ES_DBE_WIDTH                 (1U)
#define DMA_TCD_CH2_ES_DBE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_ES_DBE_SHIFT)) & DMA_TCD_CH2_ES_DBE_MASK)

#define DMA_TCD_CH2_ES_SBE_MASK                  (0x2U)
#define DMA_TCD_CH2_ES_SBE_SHIFT                 (1U)
#define DMA_TCD_CH2_ES_SBE_WIDTH                 (1U)
#define DMA_TCD_CH2_ES_SBE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_ES_SBE_SHIFT)) & DMA_TCD_CH2_ES_SBE_MASK)

#define DMA_TCD_CH2_ES_SGE_MASK                  (0x4U)
#define DMA_TCD_CH2_ES_SGE_SHIFT                 (2U)
#define DMA_TCD_CH2_ES_SGE_WIDTH                 (1U)
#define DMA_TCD_CH2_ES_SGE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_ES_SGE_SHIFT)) & DMA_TCD_CH2_ES_SGE_MASK)

#define DMA_TCD_CH2_ES_NCE_MASK                  (0x8U)
#define DMA_TCD_CH2_ES_NCE_SHIFT                 (3U)
#define DMA_TCD_CH2_ES_NCE_WIDTH                 (1U)
#define DMA_TCD_CH2_ES_NCE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_ES_NCE_SHIFT)) & DMA_TCD_CH2_ES_NCE_MASK)

#define DMA_TCD_CH2_ES_DOE_MASK                  (0x10U)
#define DMA_TCD_CH2_ES_DOE_SHIFT                 (4U)
#define DMA_TCD_CH2_ES_DOE_WIDTH                 (1U)
#define DMA_TCD_CH2_ES_DOE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_ES_DOE_SHIFT)) & DMA_TCD_CH2_ES_DOE_MASK)

#define DMA_TCD_CH2_ES_DAE_MASK                  (0x20U)
#define DMA_TCD_CH2_ES_DAE_SHIFT                 (5U)
#define DMA_TCD_CH2_ES_DAE_WIDTH                 (1U)
#define DMA_TCD_CH2_ES_DAE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_ES_DAE_SHIFT)) & DMA_TCD_CH2_ES_DAE_MASK)

#define DMA_TCD_CH2_ES_SOE_MASK                  (0x40U)
#define DMA_TCD_CH2_ES_SOE_SHIFT                 (6U)
#define DMA_TCD_CH2_ES_SOE_WIDTH                 (1U)
#define DMA_TCD_CH2_ES_SOE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_ES_SOE_SHIFT)) & DMA_TCD_CH2_ES_SOE_MASK)

#define DMA_TCD_CH2_ES_SAE_MASK                  (0x80U)
#define DMA_TCD_CH2_ES_SAE_SHIFT                 (7U)
#define DMA_TCD_CH2_ES_SAE_WIDTH                 (1U)
#define DMA_TCD_CH2_ES_SAE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_ES_SAE_SHIFT)) & DMA_TCD_CH2_ES_SAE_MASK)

#define DMA_TCD_CH2_ES_ERR_MASK                  (0x80000000U)
#define DMA_TCD_CH2_ES_ERR_SHIFT                 (31U)
#define DMA_TCD_CH2_ES_ERR_WIDTH                 (1U)
#define DMA_TCD_CH2_ES_ERR(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_ES_ERR_SHIFT)) & DMA_TCD_CH2_ES_ERR_MASK)
/*! @} */

/*! @name CH2_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH2_INT_INT_MASK                 (0x1U)
#define DMA_TCD_CH2_INT_INT_SHIFT                (0U)
#define DMA_TCD_CH2_INT_INT_WIDTH                (1U)
#define DMA_TCD_CH2_INT_INT(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_INT_INT_SHIFT)) & DMA_TCD_CH2_INT_INT_MASK)
/*! @} */

/*! @name CH2_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH2_SBR_MID_MASK                 (0xFU)
#define DMA_TCD_CH2_SBR_MID_SHIFT                (0U)
#define DMA_TCD_CH2_SBR_MID_WIDTH                (4U)
#define DMA_TCD_CH2_SBR_MID(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_SBR_MID_SHIFT)) & DMA_TCD_CH2_SBR_MID_MASK)

#define DMA_TCD_CH2_SBR_PAL_MASK                 (0x8000U)
#define DMA_TCD_CH2_SBR_PAL_SHIFT                (15U)
#define DMA_TCD_CH2_SBR_PAL_WIDTH                (1U)
#define DMA_TCD_CH2_SBR_PAL(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_SBR_PAL_SHIFT)) & DMA_TCD_CH2_SBR_PAL_MASK)

#define DMA_TCD_CH2_SBR_EMI_MASK                 (0x10000U)
#define DMA_TCD_CH2_SBR_EMI_SHIFT                (16U)
#define DMA_TCD_CH2_SBR_EMI_WIDTH                (1U)
#define DMA_TCD_CH2_SBR_EMI(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_SBR_EMI_SHIFT)) & DMA_TCD_CH2_SBR_EMI_MASK)

#define DMA_TCD_CH2_SBR_ATTR_MASK                (0xE0000U)
#define DMA_TCD_CH2_SBR_ATTR_SHIFT               (17U)
#define DMA_TCD_CH2_SBR_ATTR_WIDTH               (3U)
#define DMA_TCD_CH2_SBR_ATTR(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_SBR_ATTR_SHIFT)) & DMA_TCD_CH2_SBR_ATTR_MASK)
/*! @} */

/*! @name CH2_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH2_PRI_APL_MASK                 (0x7U)
#define DMA_TCD_CH2_PRI_APL_SHIFT                (0U)
#define DMA_TCD_CH2_PRI_APL_WIDTH                (3U)
#define DMA_TCD_CH2_PRI_APL(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_PRI_APL_SHIFT)) & DMA_TCD_CH2_PRI_APL_MASK)

#define DMA_TCD_CH2_PRI_DPA_MASK                 (0x40000000U)
#define DMA_TCD_CH2_PRI_DPA_SHIFT                (30U)
#define DMA_TCD_CH2_PRI_DPA_WIDTH                (1U)
#define DMA_TCD_CH2_PRI_DPA(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_PRI_DPA_SHIFT)) & DMA_TCD_CH2_PRI_DPA_MASK)

#define DMA_TCD_CH2_PRI_ECP_MASK                 (0x80000000U)
#define DMA_TCD_CH2_PRI_ECP_SHIFT                (31U)
#define DMA_TCD_CH2_PRI_ECP_WIDTH                (1U)
#define DMA_TCD_CH2_PRI_ECP(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH2_PRI_ECP_SHIFT)) & DMA_TCD_CH2_PRI_ECP_MASK)
/*! @} */

/*! @name TCD2_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD2_SADDR_SADDR_MASK            (0xFFFFFFFFU)
#define DMA_TCD_TCD2_SADDR_SADDR_SHIFT           (0U)
#define DMA_TCD_TCD2_SADDR_SADDR_WIDTH           (32U)
#define DMA_TCD_TCD2_SADDR_SADDR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD2_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD2_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD2_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD2_SOFF_SOFF_MASK              (0xFFFFU)
#define DMA_TCD_TCD2_SOFF_SOFF_SHIFT             (0U)
#define DMA_TCD_TCD2_SOFF_SOFF_WIDTH             (16U)
#define DMA_TCD_TCD2_SOFF_SOFF(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD2_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD2_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD2_ATTR_DSIZE_MASK             (0x7U)
#define DMA_TCD_TCD2_ATTR_DSIZE_SHIFT            (0U)
#define DMA_TCD_TCD2_ATTR_DSIZE_WIDTH            (3U)
#define DMA_TCD_TCD2_ATTR_DSIZE(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD2_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD2_ATTR_DMOD_MASK              (0xF8U)
#define DMA_TCD_TCD2_ATTR_DMOD_SHIFT             (3U)
#define DMA_TCD_TCD2_ATTR_DMOD_WIDTH             (5U)
#define DMA_TCD_TCD2_ATTR_DMOD(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD2_ATTR_DMOD_MASK)

#define DMA_TCD_TCD2_ATTR_SSIZE_MASK             (0x700U)
#define DMA_TCD_TCD2_ATTR_SSIZE_SHIFT            (8U)
#define DMA_TCD_TCD2_ATTR_SSIZE_WIDTH            (3U)
#define DMA_TCD_TCD2_ATTR_SSIZE(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD2_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD2_ATTR_SMOD_MASK              (0xF800U)
#define DMA_TCD_TCD2_ATTR_SMOD_SHIFT             (11U)
#define DMA_TCD_TCD2_ATTR_SMOD_WIDTH             (5U)
#define DMA_TCD_TCD2_ATTR_SMOD(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD2_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD2_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD2_NBYTES_MLOFFNO_NBYTES_MASK  (0x3FFFFFFFU)
#define DMA_TCD_TCD2_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD2_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD2_NBYTES_MLOFFNO_NBYTES(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD2_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD2_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD2_NBYTES_MLOFFNO_DMLOE_MASK   (0x40000000U)
#define DMA_TCD_TCD2_NBYTES_MLOFFNO_DMLOE_SHIFT  (30U)
#define DMA_TCD_TCD2_NBYTES_MLOFFNO_DMLOE_WIDTH  (1U)
#define DMA_TCD_TCD2_NBYTES_MLOFFNO_DMLOE(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD2_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD2_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD2_NBYTES_MLOFFNO_SMLOE_MASK   (0x80000000U)
#define DMA_TCD_TCD2_NBYTES_MLOFFNO_SMLOE_SHIFT  (31U)
#define DMA_TCD_TCD2_NBYTES_MLOFFNO_SMLOE_WIDTH  (1U)
#define DMA_TCD_TCD2_NBYTES_MLOFFNO_SMLOE(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD2_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD2_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD2_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD2_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD2_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD2_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD2_NBYTES_MLOFFYES_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD2_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD2_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD2_NBYTES_MLOFFYES_MLOFF_MASK  (0x3FFFFC00U)
#define DMA_TCD_TCD2_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD2_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD2_NBYTES_MLOFFYES_MLOFF(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD2_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD2_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD2_NBYTES_MLOFFYES_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD2_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD2_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD2_NBYTES_MLOFFYES_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD2_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD2_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD2_NBYTES_MLOFFYES_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD2_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD2_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD2_NBYTES_MLOFFYES_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD2_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD2_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD2_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD2_SLAST_SDA_SLAST_SDA_MASK    (0xFFFFFFFFU)
#define DMA_TCD_TCD2_SLAST_SDA_SLAST_SDA_SHIFT   (0U)
#define DMA_TCD_TCD2_SLAST_SDA_SLAST_SDA_WIDTH   (32U)
#define DMA_TCD_TCD2_SLAST_SDA_SLAST_SDA(x)      (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD2_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD2_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD2_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD2_DADDR_DADDR_MASK            (0xFFFFFFFFU)
#define DMA_TCD_TCD2_DADDR_DADDR_SHIFT           (0U)
#define DMA_TCD_TCD2_DADDR_DADDR_WIDTH           (32U)
#define DMA_TCD_TCD2_DADDR_DADDR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD2_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD2_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD2_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD2_DOFF_DOFF_MASK              (0xFFFFU)
#define DMA_TCD_TCD2_DOFF_DOFF_SHIFT             (0U)
#define DMA_TCD_TCD2_DOFF_DOFF_WIDTH             (16U)
#define DMA_TCD_TCD2_DOFF_DOFF(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD2_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD2_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD2_CITER_ELINKNO_CITER_MASK    (0x7FFFU)
#define DMA_TCD_TCD2_CITER_ELINKNO_CITER_SHIFT   (0U)
#define DMA_TCD_TCD2_CITER_ELINKNO_CITER_WIDTH   (15U)
#define DMA_TCD_TCD2_CITER_ELINKNO_CITER(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD2_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD2_CITER_ELINKNO_ELINK_MASK    (0x8000U)
#define DMA_TCD_TCD2_CITER_ELINKNO_ELINK_SHIFT   (15U)
#define DMA_TCD_TCD2_CITER_ELINKNO_ELINK_WIDTH   (1U)
#define DMA_TCD_TCD2_CITER_ELINKNO_ELINK(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD2_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD2_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD2_CITER_ELINKYES_CITER_MASK   (0x1FFU)
#define DMA_TCD_TCD2_CITER_ELINKYES_CITER_SHIFT  (0U)
#define DMA_TCD_TCD2_CITER_ELINKYES_CITER_WIDTH  (9U)
#define DMA_TCD_TCD2_CITER_ELINKYES_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD2_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD2_CITER_ELINKYES_LINKCH_MASK  (0x3E00U)
#define DMA_TCD_TCD2_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD2_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD2_CITER_ELINKYES_LINKCH(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD2_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD2_CITER_ELINKYES_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD2_CITER_ELINKYES_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD2_CITER_ELINKYES_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD2_CITER_ELINKYES_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD2_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD2_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD2_DLAST_SGA_DLAST_SGA_MASK    (0xFFFFFFFFU)
#define DMA_TCD_TCD2_DLAST_SGA_DLAST_SGA_SHIFT   (0U)
#define DMA_TCD_TCD2_DLAST_SGA_DLAST_SGA_WIDTH   (32U)
#define DMA_TCD_TCD2_DLAST_SGA_DLAST_SGA(x)      (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD2_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD2_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD2_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD2_CSR_START_MASK              (0x1U)
#define DMA_TCD_TCD2_CSR_START_SHIFT             (0U)
#define DMA_TCD_TCD2_CSR_START_WIDTH             (1U)
#define DMA_TCD_TCD2_CSR_START(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_CSR_START_SHIFT)) & DMA_TCD_TCD2_CSR_START_MASK)

#define DMA_TCD_TCD2_CSR_INTMAJOR_MASK           (0x2U)
#define DMA_TCD_TCD2_CSR_INTMAJOR_SHIFT          (1U)
#define DMA_TCD_TCD2_CSR_INTMAJOR_WIDTH          (1U)
#define DMA_TCD_TCD2_CSR_INTMAJOR(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD2_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD2_CSR_INTHALF_MASK            (0x4U)
#define DMA_TCD_TCD2_CSR_INTHALF_SHIFT           (2U)
#define DMA_TCD_TCD2_CSR_INTHALF_WIDTH           (1U)
#define DMA_TCD_TCD2_CSR_INTHALF(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD2_CSR_INTHALF_MASK)

#define DMA_TCD_TCD2_CSR_DREQ_MASK               (0x8U)
#define DMA_TCD_TCD2_CSR_DREQ_SHIFT              (3U)
#define DMA_TCD_TCD2_CSR_DREQ_WIDTH              (1U)
#define DMA_TCD_TCD2_CSR_DREQ(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_CSR_DREQ_SHIFT)) & DMA_TCD_TCD2_CSR_DREQ_MASK)

#define DMA_TCD_TCD2_CSR_ESG_MASK                (0x10U)
#define DMA_TCD_TCD2_CSR_ESG_SHIFT               (4U)
#define DMA_TCD_TCD2_CSR_ESG_WIDTH               (1U)
#define DMA_TCD_TCD2_CSR_ESG(x)                  (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_CSR_ESG_SHIFT)) & DMA_TCD_TCD2_CSR_ESG_MASK)

#define DMA_TCD_TCD2_CSR_MAJORELINK_MASK         (0x20U)
#define DMA_TCD_TCD2_CSR_MAJORELINK_SHIFT        (5U)
#define DMA_TCD_TCD2_CSR_MAJORELINK_WIDTH        (1U)
#define DMA_TCD_TCD2_CSR_MAJORELINK(x)           (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD2_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD2_CSR_EEOP_MASK               (0x40U)
#define DMA_TCD_TCD2_CSR_EEOP_SHIFT              (6U)
#define DMA_TCD_TCD2_CSR_EEOP_WIDTH              (1U)
#define DMA_TCD_TCD2_CSR_EEOP(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_CSR_EEOP_SHIFT)) & DMA_TCD_TCD2_CSR_EEOP_MASK)

#define DMA_TCD_TCD2_CSR_ESDA_MASK               (0x80U)
#define DMA_TCD_TCD2_CSR_ESDA_SHIFT              (7U)
#define DMA_TCD_TCD2_CSR_ESDA_WIDTH              (1U)
#define DMA_TCD_TCD2_CSR_ESDA(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_CSR_ESDA_SHIFT)) & DMA_TCD_TCD2_CSR_ESDA_MASK)

#define DMA_TCD_TCD2_CSR_MAJORLINKCH_MASK        (0x1F00U)
#define DMA_TCD_TCD2_CSR_MAJORLINKCH_SHIFT       (8U)
#define DMA_TCD_TCD2_CSR_MAJORLINKCH_WIDTH       (5U)
#define DMA_TCD_TCD2_CSR_MAJORLINKCH(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD2_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD2_CSR_BWC_MASK                (0xC000U)
#define DMA_TCD_TCD2_CSR_BWC_SHIFT               (14U)
#define DMA_TCD_TCD2_CSR_BWC_WIDTH               (2U)
#define DMA_TCD_TCD2_CSR_BWC(x)                  (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_CSR_BWC_SHIFT)) & DMA_TCD_TCD2_CSR_BWC_MASK)
/*! @} */

/*! @name TCD2_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD2_BITER_ELINKNO_BITER_MASK    (0x7FFFU)
#define DMA_TCD_TCD2_BITER_ELINKNO_BITER_SHIFT   (0U)
#define DMA_TCD_TCD2_BITER_ELINKNO_BITER_WIDTH   (15U)
#define DMA_TCD_TCD2_BITER_ELINKNO_BITER(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD2_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD2_BITER_ELINKNO_ELINK_MASK    (0x8000U)
#define DMA_TCD_TCD2_BITER_ELINKNO_ELINK_SHIFT   (15U)
#define DMA_TCD_TCD2_BITER_ELINKNO_ELINK_WIDTH   (1U)
#define DMA_TCD_TCD2_BITER_ELINKNO_ELINK(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD2_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD2_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD2_BITER_ELINKYES_BITER_MASK   (0x1FFU)
#define DMA_TCD_TCD2_BITER_ELINKYES_BITER_SHIFT  (0U)
#define DMA_TCD_TCD2_BITER_ELINKYES_BITER_WIDTH  (9U)
#define DMA_TCD_TCD2_BITER_ELINKYES_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD2_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD2_BITER_ELINKYES_LINKCH_MASK  (0x3E00U)
#define DMA_TCD_TCD2_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD2_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD2_BITER_ELINKYES_LINKCH(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD2_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD2_BITER_ELINKYES_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD2_BITER_ELINKYES_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD2_BITER_ELINKYES_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD2_BITER_ELINKYES_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD2_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD2_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH3_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH3_CSR_ERQ_MASK                 (0x1U)
#define DMA_TCD_CH3_CSR_ERQ_SHIFT                (0U)
#define DMA_TCD_CH3_CSR_ERQ_WIDTH                (1U)
#define DMA_TCD_CH3_CSR_ERQ(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_CSR_ERQ_SHIFT)) & DMA_TCD_CH3_CSR_ERQ_MASK)

#define DMA_TCD_CH3_CSR_EARQ_MASK                (0x2U)
#define DMA_TCD_CH3_CSR_EARQ_SHIFT               (1U)
#define DMA_TCD_CH3_CSR_EARQ_WIDTH               (1U)
#define DMA_TCD_CH3_CSR_EARQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_CSR_EARQ_SHIFT)) & DMA_TCD_CH3_CSR_EARQ_MASK)

#define DMA_TCD_CH3_CSR_EEI_MASK                 (0x4U)
#define DMA_TCD_CH3_CSR_EEI_SHIFT                (2U)
#define DMA_TCD_CH3_CSR_EEI_WIDTH                (1U)
#define DMA_TCD_CH3_CSR_EEI(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_CSR_EEI_SHIFT)) & DMA_TCD_CH3_CSR_EEI_MASK)

#define DMA_TCD_CH3_CSR_EBW_MASK                 (0x8U)
#define DMA_TCD_CH3_CSR_EBW_SHIFT                (3U)
#define DMA_TCD_CH3_CSR_EBW_WIDTH                (1U)
#define DMA_TCD_CH3_CSR_EBW(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_CSR_EBW_SHIFT)) & DMA_TCD_CH3_CSR_EBW_MASK)

#define DMA_TCD_CH3_CSR_DONE_MASK                (0x40000000U)
#define DMA_TCD_CH3_CSR_DONE_SHIFT               (30U)
#define DMA_TCD_CH3_CSR_DONE_WIDTH               (1U)
#define DMA_TCD_CH3_CSR_DONE(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_CSR_DONE_SHIFT)) & DMA_TCD_CH3_CSR_DONE_MASK)

#define DMA_TCD_CH3_CSR_ACTIVE_MASK              (0x80000000U)
#define DMA_TCD_CH3_CSR_ACTIVE_SHIFT             (31U)
#define DMA_TCD_CH3_CSR_ACTIVE_WIDTH             (1U)
#define DMA_TCD_CH3_CSR_ACTIVE(x)                (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH3_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH3_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH3_ES_DBE_MASK                  (0x1U)
#define DMA_TCD_CH3_ES_DBE_SHIFT                 (0U)
#define DMA_TCD_CH3_ES_DBE_WIDTH                 (1U)
#define DMA_TCD_CH3_ES_DBE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_ES_DBE_SHIFT)) & DMA_TCD_CH3_ES_DBE_MASK)

#define DMA_TCD_CH3_ES_SBE_MASK                  (0x2U)
#define DMA_TCD_CH3_ES_SBE_SHIFT                 (1U)
#define DMA_TCD_CH3_ES_SBE_WIDTH                 (1U)
#define DMA_TCD_CH3_ES_SBE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_ES_SBE_SHIFT)) & DMA_TCD_CH3_ES_SBE_MASK)

#define DMA_TCD_CH3_ES_SGE_MASK                  (0x4U)
#define DMA_TCD_CH3_ES_SGE_SHIFT                 (2U)
#define DMA_TCD_CH3_ES_SGE_WIDTH                 (1U)
#define DMA_TCD_CH3_ES_SGE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_ES_SGE_SHIFT)) & DMA_TCD_CH3_ES_SGE_MASK)

#define DMA_TCD_CH3_ES_NCE_MASK                  (0x8U)
#define DMA_TCD_CH3_ES_NCE_SHIFT                 (3U)
#define DMA_TCD_CH3_ES_NCE_WIDTH                 (1U)
#define DMA_TCD_CH3_ES_NCE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_ES_NCE_SHIFT)) & DMA_TCD_CH3_ES_NCE_MASK)

#define DMA_TCD_CH3_ES_DOE_MASK                  (0x10U)
#define DMA_TCD_CH3_ES_DOE_SHIFT                 (4U)
#define DMA_TCD_CH3_ES_DOE_WIDTH                 (1U)
#define DMA_TCD_CH3_ES_DOE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_ES_DOE_SHIFT)) & DMA_TCD_CH3_ES_DOE_MASK)

#define DMA_TCD_CH3_ES_DAE_MASK                  (0x20U)
#define DMA_TCD_CH3_ES_DAE_SHIFT                 (5U)
#define DMA_TCD_CH3_ES_DAE_WIDTH                 (1U)
#define DMA_TCD_CH3_ES_DAE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_ES_DAE_SHIFT)) & DMA_TCD_CH3_ES_DAE_MASK)

#define DMA_TCD_CH3_ES_SOE_MASK                  (0x40U)
#define DMA_TCD_CH3_ES_SOE_SHIFT                 (6U)
#define DMA_TCD_CH3_ES_SOE_WIDTH                 (1U)
#define DMA_TCD_CH3_ES_SOE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_ES_SOE_SHIFT)) & DMA_TCD_CH3_ES_SOE_MASK)

#define DMA_TCD_CH3_ES_SAE_MASK                  (0x80U)
#define DMA_TCD_CH3_ES_SAE_SHIFT                 (7U)
#define DMA_TCD_CH3_ES_SAE_WIDTH                 (1U)
#define DMA_TCD_CH3_ES_SAE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_ES_SAE_SHIFT)) & DMA_TCD_CH3_ES_SAE_MASK)

#define DMA_TCD_CH3_ES_ERR_MASK                  (0x80000000U)
#define DMA_TCD_CH3_ES_ERR_SHIFT                 (31U)
#define DMA_TCD_CH3_ES_ERR_WIDTH                 (1U)
#define DMA_TCD_CH3_ES_ERR(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_ES_ERR_SHIFT)) & DMA_TCD_CH3_ES_ERR_MASK)
/*! @} */

/*! @name CH3_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH3_INT_INT_MASK                 (0x1U)
#define DMA_TCD_CH3_INT_INT_SHIFT                (0U)
#define DMA_TCD_CH3_INT_INT_WIDTH                (1U)
#define DMA_TCD_CH3_INT_INT(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_INT_INT_SHIFT)) & DMA_TCD_CH3_INT_INT_MASK)
/*! @} */

/*! @name CH3_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH3_SBR_MID_MASK                 (0xFU)
#define DMA_TCD_CH3_SBR_MID_SHIFT                (0U)
#define DMA_TCD_CH3_SBR_MID_WIDTH                (4U)
#define DMA_TCD_CH3_SBR_MID(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_SBR_MID_SHIFT)) & DMA_TCD_CH3_SBR_MID_MASK)

#define DMA_TCD_CH3_SBR_PAL_MASK                 (0x8000U)
#define DMA_TCD_CH3_SBR_PAL_SHIFT                (15U)
#define DMA_TCD_CH3_SBR_PAL_WIDTH                (1U)
#define DMA_TCD_CH3_SBR_PAL(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_SBR_PAL_SHIFT)) & DMA_TCD_CH3_SBR_PAL_MASK)

#define DMA_TCD_CH3_SBR_EMI_MASK                 (0x10000U)
#define DMA_TCD_CH3_SBR_EMI_SHIFT                (16U)
#define DMA_TCD_CH3_SBR_EMI_WIDTH                (1U)
#define DMA_TCD_CH3_SBR_EMI(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_SBR_EMI_SHIFT)) & DMA_TCD_CH3_SBR_EMI_MASK)

#define DMA_TCD_CH3_SBR_ATTR_MASK                (0xE0000U)
#define DMA_TCD_CH3_SBR_ATTR_SHIFT               (17U)
#define DMA_TCD_CH3_SBR_ATTR_WIDTH               (3U)
#define DMA_TCD_CH3_SBR_ATTR(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_SBR_ATTR_SHIFT)) & DMA_TCD_CH3_SBR_ATTR_MASK)
/*! @} */

/*! @name CH3_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH3_PRI_APL_MASK                 (0x7U)
#define DMA_TCD_CH3_PRI_APL_SHIFT                (0U)
#define DMA_TCD_CH3_PRI_APL_WIDTH                (3U)
#define DMA_TCD_CH3_PRI_APL(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_PRI_APL_SHIFT)) & DMA_TCD_CH3_PRI_APL_MASK)

#define DMA_TCD_CH3_PRI_DPA_MASK                 (0x40000000U)
#define DMA_TCD_CH3_PRI_DPA_SHIFT                (30U)
#define DMA_TCD_CH3_PRI_DPA_WIDTH                (1U)
#define DMA_TCD_CH3_PRI_DPA(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_PRI_DPA_SHIFT)) & DMA_TCD_CH3_PRI_DPA_MASK)

#define DMA_TCD_CH3_PRI_ECP_MASK                 (0x80000000U)
#define DMA_TCD_CH3_PRI_ECP_SHIFT                (31U)
#define DMA_TCD_CH3_PRI_ECP_WIDTH                (1U)
#define DMA_TCD_CH3_PRI_ECP(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH3_PRI_ECP_SHIFT)) & DMA_TCD_CH3_PRI_ECP_MASK)
/*! @} */

/*! @name TCD3_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD3_SADDR_SADDR_MASK            (0xFFFFFFFFU)
#define DMA_TCD_TCD3_SADDR_SADDR_SHIFT           (0U)
#define DMA_TCD_TCD3_SADDR_SADDR_WIDTH           (32U)
#define DMA_TCD_TCD3_SADDR_SADDR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD3_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD3_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD3_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD3_SOFF_SOFF_MASK              (0xFFFFU)
#define DMA_TCD_TCD3_SOFF_SOFF_SHIFT             (0U)
#define DMA_TCD_TCD3_SOFF_SOFF_WIDTH             (16U)
#define DMA_TCD_TCD3_SOFF_SOFF(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD3_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD3_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD3_ATTR_DSIZE_MASK             (0x7U)
#define DMA_TCD_TCD3_ATTR_DSIZE_SHIFT            (0U)
#define DMA_TCD_TCD3_ATTR_DSIZE_WIDTH            (3U)
#define DMA_TCD_TCD3_ATTR_DSIZE(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD3_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD3_ATTR_DMOD_MASK              (0xF8U)
#define DMA_TCD_TCD3_ATTR_DMOD_SHIFT             (3U)
#define DMA_TCD_TCD3_ATTR_DMOD_WIDTH             (5U)
#define DMA_TCD_TCD3_ATTR_DMOD(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD3_ATTR_DMOD_MASK)

#define DMA_TCD_TCD3_ATTR_SSIZE_MASK             (0x700U)
#define DMA_TCD_TCD3_ATTR_SSIZE_SHIFT            (8U)
#define DMA_TCD_TCD3_ATTR_SSIZE_WIDTH            (3U)
#define DMA_TCD_TCD3_ATTR_SSIZE(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD3_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD3_ATTR_SMOD_MASK              (0xF800U)
#define DMA_TCD_TCD3_ATTR_SMOD_SHIFT             (11U)
#define DMA_TCD_TCD3_ATTR_SMOD_WIDTH             (5U)
#define DMA_TCD_TCD3_ATTR_SMOD(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD3_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD3_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD3_NBYTES_MLOFFNO_NBYTES_MASK  (0x3FFFFFFFU)
#define DMA_TCD_TCD3_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD3_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD3_NBYTES_MLOFFNO_NBYTES(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD3_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD3_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD3_NBYTES_MLOFFNO_DMLOE_MASK   (0x40000000U)
#define DMA_TCD_TCD3_NBYTES_MLOFFNO_DMLOE_SHIFT  (30U)
#define DMA_TCD_TCD3_NBYTES_MLOFFNO_DMLOE_WIDTH  (1U)
#define DMA_TCD_TCD3_NBYTES_MLOFFNO_DMLOE(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD3_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD3_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD3_NBYTES_MLOFFNO_SMLOE_MASK   (0x80000000U)
#define DMA_TCD_TCD3_NBYTES_MLOFFNO_SMLOE_SHIFT  (31U)
#define DMA_TCD_TCD3_NBYTES_MLOFFNO_SMLOE_WIDTH  (1U)
#define DMA_TCD_TCD3_NBYTES_MLOFFNO_SMLOE(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD3_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD3_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD3_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD3_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD3_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD3_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD3_NBYTES_MLOFFYES_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD3_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD3_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD3_NBYTES_MLOFFYES_MLOFF_MASK  (0x3FFFFC00U)
#define DMA_TCD_TCD3_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD3_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD3_NBYTES_MLOFFYES_MLOFF(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD3_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD3_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD3_NBYTES_MLOFFYES_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD3_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD3_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD3_NBYTES_MLOFFYES_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD3_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD3_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD3_NBYTES_MLOFFYES_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD3_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD3_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD3_NBYTES_MLOFFYES_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD3_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD3_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD3_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD3_SLAST_SDA_SLAST_SDA_MASK    (0xFFFFFFFFU)
#define DMA_TCD_TCD3_SLAST_SDA_SLAST_SDA_SHIFT   (0U)
#define DMA_TCD_TCD3_SLAST_SDA_SLAST_SDA_WIDTH   (32U)
#define DMA_TCD_TCD3_SLAST_SDA_SLAST_SDA(x)      (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD3_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD3_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD3_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD3_DADDR_DADDR_MASK            (0xFFFFFFFFU)
#define DMA_TCD_TCD3_DADDR_DADDR_SHIFT           (0U)
#define DMA_TCD_TCD3_DADDR_DADDR_WIDTH           (32U)
#define DMA_TCD_TCD3_DADDR_DADDR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD3_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD3_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD3_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD3_DOFF_DOFF_MASK              (0xFFFFU)
#define DMA_TCD_TCD3_DOFF_DOFF_SHIFT             (0U)
#define DMA_TCD_TCD3_DOFF_DOFF_WIDTH             (16U)
#define DMA_TCD_TCD3_DOFF_DOFF(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD3_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD3_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD3_CITER_ELINKNO_CITER_MASK    (0x7FFFU)
#define DMA_TCD_TCD3_CITER_ELINKNO_CITER_SHIFT   (0U)
#define DMA_TCD_TCD3_CITER_ELINKNO_CITER_WIDTH   (15U)
#define DMA_TCD_TCD3_CITER_ELINKNO_CITER(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD3_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD3_CITER_ELINKNO_ELINK_MASK    (0x8000U)
#define DMA_TCD_TCD3_CITER_ELINKNO_ELINK_SHIFT   (15U)
#define DMA_TCD_TCD3_CITER_ELINKNO_ELINK_WIDTH   (1U)
#define DMA_TCD_TCD3_CITER_ELINKNO_ELINK(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD3_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD3_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD3_CITER_ELINKYES_CITER_MASK   (0x1FFU)
#define DMA_TCD_TCD3_CITER_ELINKYES_CITER_SHIFT  (0U)
#define DMA_TCD_TCD3_CITER_ELINKYES_CITER_WIDTH  (9U)
#define DMA_TCD_TCD3_CITER_ELINKYES_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD3_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD3_CITER_ELINKYES_LINKCH_MASK  (0x3E00U)
#define DMA_TCD_TCD3_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD3_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD3_CITER_ELINKYES_LINKCH(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD3_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD3_CITER_ELINKYES_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD3_CITER_ELINKYES_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD3_CITER_ELINKYES_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD3_CITER_ELINKYES_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD3_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD3_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD3_DLAST_SGA_DLAST_SGA_MASK    (0xFFFFFFFFU)
#define DMA_TCD_TCD3_DLAST_SGA_DLAST_SGA_SHIFT   (0U)
#define DMA_TCD_TCD3_DLAST_SGA_DLAST_SGA_WIDTH   (32U)
#define DMA_TCD_TCD3_DLAST_SGA_DLAST_SGA(x)      (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD3_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD3_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD3_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD3_CSR_START_MASK              (0x1U)
#define DMA_TCD_TCD3_CSR_START_SHIFT             (0U)
#define DMA_TCD_TCD3_CSR_START_WIDTH             (1U)
#define DMA_TCD_TCD3_CSR_START(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_CSR_START_SHIFT)) & DMA_TCD_TCD3_CSR_START_MASK)

#define DMA_TCD_TCD3_CSR_INTMAJOR_MASK           (0x2U)
#define DMA_TCD_TCD3_CSR_INTMAJOR_SHIFT          (1U)
#define DMA_TCD_TCD3_CSR_INTMAJOR_WIDTH          (1U)
#define DMA_TCD_TCD3_CSR_INTMAJOR(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD3_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD3_CSR_INTHALF_MASK            (0x4U)
#define DMA_TCD_TCD3_CSR_INTHALF_SHIFT           (2U)
#define DMA_TCD_TCD3_CSR_INTHALF_WIDTH           (1U)
#define DMA_TCD_TCD3_CSR_INTHALF(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD3_CSR_INTHALF_MASK)

#define DMA_TCD_TCD3_CSR_DREQ_MASK               (0x8U)
#define DMA_TCD_TCD3_CSR_DREQ_SHIFT              (3U)
#define DMA_TCD_TCD3_CSR_DREQ_WIDTH              (1U)
#define DMA_TCD_TCD3_CSR_DREQ(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_CSR_DREQ_SHIFT)) & DMA_TCD_TCD3_CSR_DREQ_MASK)

#define DMA_TCD_TCD3_CSR_ESG_MASK                (0x10U)
#define DMA_TCD_TCD3_CSR_ESG_SHIFT               (4U)
#define DMA_TCD_TCD3_CSR_ESG_WIDTH               (1U)
#define DMA_TCD_TCD3_CSR_ESG(x)                  (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_CSR_ESG_SHIFT)) & DMA_TCD_TCD3_CSR_ESG_MASK)

#define DMA_TCD_TCD3_CSR_MAJORELINK_MASK         (0x20U)
#define DMA_TCD_TCD3_CSR_MAJORELINK_SHIFT        (5U)
#define DMA_TCD_TCD3_CSR_MAJORELINK_WIDTH        (1U)
#define DMA_TCD_TCD3_CSR_MAJORELINK(x)           (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD3_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD3_CSR_EEOP_MASK               (0x40U)
#define DMA_TCD_TCD3_CSR_EEOP_SHIFT              (6U)
#define DMA_TCD_TCD3_CSR_EEOP_WIDTH              (1U)
#define DMA_TCD_TCD3_CSR_EEOP(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_CSR_EEOP_SHIFT)) & DMA_TCD_TCD3_CSR_EEOP_MASK)

#define DMA_TCD_TCD3_CSR_ESDA_MASK               (0x80U)
#define DMA_TCD_TCD3_CSR_ESDA_SHIFT              (7U)
#define DMA_TCD_TCD3_CSR_ESDA_WIDTH              (1U)
#define DMA_TCD_TCD3_CSR_ESDA(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_CSR_ESDA_SHIFT)) & DMA_TCD_TCD3_CSR_ESDA_MASK)

#define DMA_TCD_TCD3_CSR_MAJORLINKCH_MASK        (0x1F00U)
#define DMA_TCD_TCD3_CSR_MAJORLINKCH_SHIFT       (8U)
#define DMA_TCD_TCD3_CSR_MAJORLINKCH_WIDTH       (5U)
#define DMA_TCD_TCD3_CSR_MAJORLINKCH(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD3_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD3_CSR_BWC_MASK                (0xC000U)
#define DMA_TCD_TCD3_CSR_BWC_SHIFT               (14U)
#define DMA_TCD_TCD3_CSR_BWC_WIDTH               (2U)
#define DMA_TCD_TCD3_CSR_BWC(x)                  (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_CSR_BWC_SHIFT)) & DMA_TCD_TCD3_CSR_BWC_MASK)
/*! @} */

/*! @name TCD3_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD3_BITER_ELINKNO_BITER_MASK    (0x7FFFU)
#define DMA_TCD_TCD3_BITER_ELINKNO_BITER_SHIFT   (0U)
#define DMA_TCD_TCD3_BITER_ELINKNO_BITER_WIDTH   (15U)
#define DMA_TCD_TCD3_BITER_ELINKNO_BITER(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD3_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD3_BITER_ELINKNO_ELINK_MASK    (0x8000U)
#define DMA_TCD_TCD3_BITER_ELINKNO_ELINK_SHIFT   (15U)
#define DMA_TCD_TCD3_BITER_ELINKNO_ELINK_WIDTH   (1U)
#define DMA_TCD_TCD3_BITER_ELINKNO_ELINK(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD3_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD3_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD3_BITER_ELINKYES_BITER_MASK   (0x1FFU)
#define DMA_TCD_TCD3_BITER_ELINKYES_BITER_SHIFT  (0U)
#define DMA_TCD_TCD3_BITER_ELINKYES_BITER_WIDTH  (9U)
#define DMA_TCD_TCD3_BITER_ELINKYES_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD3_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD3_BITER_ELINKYES_LINKCH_MASK  (0x3E00U)
#define DMA_TCD_TCD3_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD3_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD3_BITER_ELINKYES_LINKCH(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD3_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD3_BITER_ELINKYES_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD3_BITER_ELINKYES_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD3_BITER_ELINKYES_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD3_BITER_ELINKYES_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD3_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD3_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH4_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH4_CSR_ERQ_MASK                 (0x1U)
#define DMA_TCD_CH4_CSR_ERQ_SHIFT                (0U)
#define DMA_TCD_CH4_CSR_ERQ_WIDTH                (1U)
#define DMA_TCD_CH4_CSR_ERQ(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_CSR_ERQ_SHIFT)) & DMA_TCD_CH4_CSR_ERQ_MASK)

#define DMA_TCD_CH4_CSR_EARQ_MASK                (0x2U)
#define DMA_TCD_CH4_CSR_EARQ_SHIFT               (1U)
#define DMA_TCD_CH4_CSR_EARQ_WIDTH               (1U)
#define DMA_TCD_CH4_CSR_EARQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_CSR_EARQ_SHIFT)) & DMA_TCD_CH4_CSR_EARQ_MASK)

#define DMA_TCD_CH4_CSR_EEI_MASK                 (0x4U)
#define DMA_TCD_CH4_CSR_EEI_SHIFT                (2U)
#define DMA_TCD_CH4_CSR_EEI_WIDTH                (1U)
#define DMA_TCD_CH4_CSR_EEI(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_CSR_EEI_SHIFT)) & DMA_TCD_CH4_CSR_EEI_MASK)

#define DMA_TCD_CH4_CSR_EBW_MASK                 (0x8U)
#define DMA_TCD_CH4_CSR_EBW_SHIFT                (3U)
#define DMA_TCD_CH4_CSR_EBW_WIDTH                (1U)
#define DMA_TCD_CH4_CSR_EBW(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_CSR_EBW_SHIFT)) & DMA_TCD_CH4_CSR_EBW_MASK)

#define DMA_TCD_CH4_CSR_DONE_MASK                (0x40000000U)
#define DMA_TCD_CH4_CSR_DONE_SHIFT               (30U)
#define DMA_TCD_CH4_CSR_DONE_WIDTH               (1U)
#define DMA_TCD_CH4_CSR_DONE(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_CSR_DONE_SHIFT)) & DMA_TCD_CH4_CSR_DONE_MASK)

#define DMA_TCD_CH4_CSR_ACTIVE_MASK              (0x80000000U)
#define DMA_TCD_CH4_CSR_ACTIVE_SHIFT             (31U)
#define DMA_TCD_CH4_CSR_ACTIVE_WIDTH             (1U)
#define DMA_TCD_CH4_CSR_ACTIVE(x)                (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH4_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH4_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH4_ES_DBE_MASK                  (0x1U)
#define DMA_TCD_CH4_ES_DBE_SHIFT                 (0U)
#define DMA_TCD_CH4_ES_DBE_WIDTH                 (1U)
#define DMA_TCD_CH4_ES_DBE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_ES_DBE_SHIFT)) & DMA_TCD_CH4_ES_DBE_MASK)

#define DMA_TCD_CH4_ES_SBE_MASK                  (0x2U)
#define DMA_TCD_CH4_ES_SBE_SHIFT                 (1U)
#define DMA_TCD_CH4_ES_SBE_WIDTH                 (1U)
#define DMA_TCD_CH4_ES_SBE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_ES_SBE_SHIFT)) & DMA_TCD_CH4_ES_SBE_MASK)

#define DMA_TCD_CH4_ES_SGE_MASK                  (0x4U)
#define DMA_TCD_CH4_ES_SGE_SHIFT                 (2U)
#define DMA_TCD_CH4_ES_SGE_WIDTH                 (1U)
#define DMA_TCD_CH4_ES_SGE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_ES_SGE_SHIFT)) & DMA_TCD_CH4_ES_SGE_MASK)

#define DMA_TCD_CH4_ES_NCE_MASK                  (0x8U)
#define DMA_TCD_CH4_ES_NCE_SHIFT                 (3U)
#define DMA_TCD_CH4_ES_NCE_WIDTH                 (1U)
#define DMA_TCD_CH4_ES_NCE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_ES_NCE_SHIFT)) & DMA_TCD_CH4_ES_NCE_MASK)

#define DMA_TCD_CH4_ES_DOE_MASK                  (0x10U)
#define DMA_TCD_CH4_ES_DOE_SHIFT                 (4U)
#define DMA_TCD_CH4_ES_DOE_WIDTH                 (1U)
#define DMA_TCD_CH4_ES_DOE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_ES_DOE_SHIFT)) & DMA_TCD_CH4_ES_DOE_MASK)

#define DMA_TCD_CH4_ES_DAE_MASK                  (0x20U)
#define DMA_TCD_CH4_ES_DAE_SHIFT                 (5U)
#define DMA_TCD_CH4_ES_DAE_WIDTH                 (1U)
#define DMA_TCD_CH4_ES_DAE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_ES_DAE_SHIFT)) & DMA_TCD_CH4_ES_DAE_MASK)

#define DMA_TCD_CH4_ES_SOE_MASK                  (0x40U)
#define DMA_TCD_CH4_ES_SOE_SHIFT                 (6U)
#define DMA_TCD_CH4_ES_SOE_WIDTH                 (1U)
#define DMA_TCD_CH4_ES_SOE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_ES_SOE_SHIFT)) & DMA_TCD_CH4_ES_SOE_MASK)

#define DMA_TCD_CH4_ES_SAE_MASK                  (0x80U)
#define DMA_TCD_CH4_ES_SAE_SHIFT                 (7U)
#define DMA_TCD_CH4_ES_SAE_WIDTH                 (1U)
#define DMA_TCD_CH4_ES_SAE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_ES_SAE_SHIFT)) & DMA_TCD_CH4_ES_SAE_MASK)

#define DMA_TCD_CH4_ES_ERR_MASK                  (0x80000000U)
#define DMA_TCD_CH4_ES_ERR_SHIFT                 (31U)
#define DMA_TCD_CH4_ES_ERR_WIDTH                 (1U)
#define DMA_TCD_CH4_ES_ERR(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_ES_ERR_SHIFT)) & DMA_TCD_CH4_ES_ERR_MASK)
/*! @} */

/*! @name CH4_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH4_INT_INT_MASK                 (0x1U)
#define DMA_TCD_CH4_INT_INT_SHIFT                (0U)
#define DMA_TCD_CH4_INT_INT_WIDTH                (1U)
#define DMA_TCD_CH4_INT_INT(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_INT_INT_SHIFT)) & DMA_TCD_CH4_INT_INT_MASK)
/*! @} */

/*! @name CH4_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH4_SBR_MID_MASK                 (0xFU)
#define DMA_TCD_CH4_SBR_MID_SHIFT                (0U)
#define DMA_TCD_CH4_SBR_MID_WIDTH                (4U)
#define DMA_TCD_CH4_SBR_MID(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_SBR_MID_SHIFT)) & DMA_TCD_CH4_SBR_MID_MASK)

#define DMA_TCD_CH4_SBR_PAL_MASK                 (0x8000U)
#define DMA_TCD_CH4_SBR_PAL_SHIFT                (15U)
#define DMA_TCD_CH4_SBR_PAL_WIDTH                (1U)
#define DMA_TCD_CH4_SBR_PAL(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_SBR_PAL_SHIFT)) & DMA_TCD_CH4_SBR_PAL_MASK)

#define DMA_TCD_CH4_SBR_EMI_MASK                 (0x10000U)
#define DMA_TCD_CH4_SBR_EMI_SHIFT                (16U)
#define DMA_TCD_CH4_SBR_EMI_WIDTH                (1U)
#define DMA_TCD_CH4_SBR_EMI(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_SBR_EMI_SHIFT)) & DMA_TCD_CH4_SBR_EMI_MASK)

#define DMA_TCD_CH4_SBR_ATTR_MASK                (0xE0000U)
#define DMA_TCD_CH4_SBR_ATTR_SHIFT               (17U)
#define DMA_TCD_CH4_SBR_ATTR_WIDTH               (3U)
#define DMA_TCD_CH4_SBR_ATTR(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_SBR_ATTR_SHIFT)) & DMA_TCD_CH4_SBR_ATTR_MASK)
/*! @} */

/*! @name CH4_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH4_PRI_APL_MASK                 (0x7U)
#define DMA_TCD_CH4_PRI_APL_SHIFT                (0U)
#define DMA_TCD_CH4_PRI_APL_WIDTH                (3U)
#define DMA_TCD_CH4_PRI_APL(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_PRI_APL_SHIFT)) & DMA_TCD_CH4_PRI_APL_MASK)

#define DMA_TCD_CH4_PRI_DPA_MASK                 (0x40000000U)
#define DMA_TCD_CH4_PRI_DPA_SHIFT                (30U)
#define DMA_TCD_CH4_PRI_DPA_WIDTH                (1U)
#define DMA_TCD_CH4_PRI_DPA(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_PRI_DPA_SHIFT)) & DMA_TCD_CH4_PRI_DPA_MASK)

#define DMA_TCD_CH4_PRI_ECP_MASK                 (0x80000000U)
#define DMA_TCD_CH4_PRI_ECP_SHIFT                (31U)
#define DMA_TCD_CH4_PRI_ECP_WIDTH                (1U)
#define DMA_TCD_CH4_PRI_ECP(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH4_PRI_ECP_SHIFT)) & DMA_TCD_CH4_PRI_ECP_MASK)
/*! @} */

/*! @name TCD4_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD4_SADDR_SADDR_MASK            (0xFFFFFFFFU)
#define DMA_TCD_TCD4_SADDR_SADDR_SHIFT           (0U)
#define DMA_TCD_TCD4_SADDR_SADDR_WIDTH           (32U)
#define DMA_TCD_TCD4_SADDR_SADDR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD4_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD4_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD4_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD4_SOFF_SOFF_MASK              (0xFFFFU)
#define DMA_TCD_TCD4_SOFF_SOFF_SHIFT             (0U)
#define DMA_TCD_TCD4_SOFF_SOFF_WIDTH             (16U)
#define DMA_TCD_TCD4_SOFF_SOFF(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD4_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD4_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD4_ATTR_DSIZE_MASK             (0x7U)
#define DMA_TCD_TCD4_ATTR_DSIZE_SHIFT            (0U)
#define DMA_TCD_TCD4_ATTR_DSIZE_WIDTH            (3U)
#define DMA_TCD_TCD4_ATTR_DSIZE(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD4_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD4_ATTR_DMOD_MASK              (0xF8U)
#define DMA_TCD_TCD4_ATTR_DMOD_SHIFT             (3U)
#define DMA_TCD_TCD4_ATTR_DMOD_WIDTH             (5U)
#define DMA_TCD_TCD4_ATTR_DMOD(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD4_ATTR_DMOD_MASK)

#define DMA_TCD_TCD4_ATTR_SSIZE_MASK             (0x700U)
#define DMA_TCD_TCD4_ATTR_SSIZE_SHIFT            (8U)
#define DMA_TCD_TCD4_ATTR_SSIZE_WIDTH            (3U)
#define DMA_TCD_TCD4_ATTR_SSIZE(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD4_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD4_ATTR_SMOD_MASK              (0xF800U)
#define DMA_TCD_TCD4_ATTR_SMOD_SHIFT             (11U)
#define DMA_TCD_TCD4_ATTR_SMOD_WIDTH             (5U)
#define DMA_TCD_TCD4_ATTR_SMOD(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD4_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD4_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD4_NBYTES_MLOFFNO_NBYTES_MASK  (0x3FFFFFFFU)
#define DMA_TCD_TCD4_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD4_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD4_NBYTES_MLOFFNO_NBYTES(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD4_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD4_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD4_NBYTES_MLOFFNO_DMLOE_MASK   (0x40000000U)
#define DMA_TCD_TCD4_NBYTES_MLOFFNO_DMLOE_SHIFT  (30U)
#define DMA_TCD_TCD4_NBYTES_MLOFFNO_DMLOE_WIDTH  (1U)
#define DMA_TCD_TCD4_NBYTES_MLOFFNO_DMLOE(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD4_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD4_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD4_NBYTES_MLOFFNO_SMLOE_MASK   (0x80000000U)
#define DMA_TCD_TCD4_NBYTES_MLOFFNO_SMLOE_SHIFT  (31U)
#define DMA_TCD_TCD4_NBYTES_MLOFFNO_SMLOE_WIDTH  (1U)
#define DMA_TCD_TCD4_NBYTES_MLOFFNO_SMLOE(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD4_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD4_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD4_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD4_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD4_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD4_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD4_NBYTES_MLOFFYES_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD4_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD4_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD4_NBYTES_MLOFFYES_MLOFF_MASK  (0x3FFFFC00U)
#define DMA_TCD_TCD4_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD4_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD4_NBYTES_MLOFFYES_MLOFF(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD4_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD4_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD4_NBYTES_MLOFFYES_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD4_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD4_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD4_NBYTES_MLOFFYES_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD4_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD4_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD4_NBYTES_MLOFFYES_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD4_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD4_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD4_NBYTES_MLOFFYES_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD4_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD4_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD4_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD4_SLAST_SDA_SLAST_SDA_MASK    (0xFFFFFFFFU)
#define DMA_TCD_TCD4_SLAST_SDA_SLAST_SDA_SHIFT   (0U)
#define DMA_TCD_TCD4_SLAST_SDA_SLAST_SDA_WIDTH   (32U)
#define DMA_TCD_TCD4_SLAST_SDA_SLAST_SDA(x)      (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD4_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD4_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD4_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD4_DADDR_DADDR_MASK            (0xFFFFFFFFU)
#define DMA_TCD_TCD4_DADDR_DADDR_SHIFT           (0U)
#define DMA_TCD_TCD4_DADDR_DADDR_WIDTH           (32U)
#define DMA_TCD_TCD4_DADDR_DADDR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD4_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD4_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD4_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD4_DOFF_DOFF_MASK              (0xFFFFU)
#define DMA_TCD_TCD4_DOFF_DOFF_SHIFT             (0U)
#define DMA_TCD_TCD4_DOFF_DOFF_WIDTH             (16U)
#define DMA_TCD_TCD4_DOFF_DOFF(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD4_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD4_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD4_CITER_ELINKNO_CITER_MASK    (0x7FFFU)
#define DMA_TCD_TCD4_CITER_ELINKNO_CITER_SHIFT   (0U)
#define DMA_TCD_TCD4_CITER_ELINKNO_CITER_WIDTH   (15U)
#define DMA_TCD_TCD4_CITER_ELINKNO_CITER(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD4_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD4_CITER_ELINKNO_ELINK_MASK    (0x8000U)
#define DMA_TCD_TCD4_CITER_ELINKNO_ELINK_SHIFT   (15U)
#define DMA_TCD_TCD4_CITER_ELINKNO_ELINK_WIDTH   (1U)
#define DMA_TCD_TCD4_CITER_ELINKNO_ELINK(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD4_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD4_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD4_CITER_ELINKYES_CITER_MASK   (0x1FFU)
#define DMA_TCD_TCD4_CITER_ELINKYES_CITER_SHIFT  (0U)
#define DMA_TCD_TCD4_CITER_ELINKYES_CITER_WIDTH  (9U)
#define DMA_TCD_TCD4_CITER_ELINKYES_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD4_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD4_CITER_ELINKYES_LINKCH_MASK  (0x3E00U)
#define DMA_TCD_TCD4_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD4_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD4_CITER_ELINKYES_LINKCH(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD4_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD4_CITER_ELINKYES_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD4_CITER_ELINKYES_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD4_CITER_ELINKYES_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD4_CITER_ELINKYES_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD4_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD4_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD4_DLAST_SGA_DLAST_SGA_MASK    (0xFFFFFFFFU)
#define DMA_TCD_TCD4_DLAST_SGA_DLAST_SGA_SHIFT   (0U)
#define DMA_TCD_TCD4_DLAST_SGA_DLAST_SGA_WIDTH   (32U)
#define DMA_TCD_TCD4_DLAST_SGA_DLAST_SGA(x)      (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD4_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD4_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD4_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD4_CSR_START_MASK              (0x1U)
#define DMA_TCD_TCD4_CSR_START_SHIFT             (0U)
#define DMA_TCD_TCD4_CSR_START_WIDTH             (1U)
#define DMA_TCD_TCD4_CSR_START(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_CSR_START_SHIFT)) & DMA_TCD_TCD4_CSR_START_MASK)

#define DMA_TCD_TCD4_CSR_INTMAJOR_MASK           (0x2U)
#define DMA_TCD_TCD4_CSR_INTMAJOR_SHIFT          (1U)
#define DMA_TCD_TCD4_CSR_INTMAJOR_WIDTH          (1U)
#define DMA_TCD_TCD4_CSR_INTMAJOR(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD4_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD4_CSR_INTHALF_MASK            (0x4U)
#define DMA_TCD_TCD4_CSR_INTHALF_SHIFT           (2U)
#define DMA_TCD_TCD4_CSR_INTHALF_WIDTH           (1U)
#define DMA_TCD_TCD4_CSR_INTHALF(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD4_CSR_INTHALF_MASK)

#define DMA_TCD_TCD4_CSR_DREQ_MASK               (0x8U)
#define DMA_TCD_TCD4_CSR_DREQ_SHIFT              (3U)
#define DMA_TCD_TCD4_CSR_DREQ_WIDTH              (1U)
#define DMA_TCD_TCD4_CSR_DREQ(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_CSR_DREQ_SHIFT)) & DMA_TCD_TCD4_CSR_DREQ_MASK)

#define DMA_TCD_TCD4_CSR_ESG_MASK                (0x10U)
#define DMA_TCD_TCD4_CSR_ESG_SHIFT               (4U)
#define DMA_TCD_TCD4_CSR_ESG_WIDTH               (1U)
#define DMA_TCD_TCD4_CSR_ESG(x)                  (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_CSR_ESG_SHIFT)) & DMA_TCD_TCD4_CSR_ESG_MASK)

#define DMA_TCD_TCD4_CSR_MAJORELINK_MASK         (0x20U)
#define DMA_TCD_TCD4_CSR_MAJORELINK_SHIFT        (5U)
#define DMA_TCD_TCD4_CSR_MAJORELINK_WIDTH        (1U)
#define DMA_TCD_TCD4_CSR_MAJORELINK(x)           (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD4_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD4_CSR_EEOP_MASK               (0x40U)
#define DMA_TCD_TCD4_CSR_EEOP_SHIFT              (6U)
#define DMA_TCD_TCD4_CSR_EEOP_WIDTH              (1U)
#define DMA_TCD_TCD4_CSR_EEOP(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_CSR_EEOP_SHIFT)) & DMA_TCD_TCD4_CSR_EEOP_MASK)

#define DMA_TCD_TCD4_CSR_ESDA_MASK               (0x80U)
#define DMA_TCD_TCD4_CSR_ESDA_SHIFT              (7U)
#define DMA_TCD_TCD4_CSR_ESDA_WIDTH              (1U)
#define DMA_TCD_TCD4_CSR_ESDA(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_CSR_ESDA_SHIFT)) & DMA_TCD_TCD4_CSR_ESDA_MASK)

#define DMA_TCD_TCD4_CSR_MAJORLINKCH_MASK        (0x1F00U)
#define DMA_TCD_TCD4_CSR_MAJORLINKCH_SHIFT       (8U)
#define DMA_TCD_TCD4_CSR_MAJORLINKCH_WIDTH       (5U)
#define DMA_TCD_TCD4_CSR_MAJORLINKCH(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD4_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD4_CSR_BWC_MASK                (0xC000U)
#define DMA_TCD_TCD4_CSR_BWC_SHIFT               (14U)
#define DMA_TCD_TCD4_CSR_BWC_WIDTH               (2U)
#define DMA_TCD_TCD4_CSR_BWC(x)                  (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_CSR_BWC_SHIFT)) & DMA_TCD_TCD4_CSR_BWC_MASK)
/*! @} */

/*! @name TCD4_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD4_BITER_ELINKNO_BITER_MASK    (0x7FFFU)
#define DMA_TCD_TCD4_BITER_ELINKNO_BITER_SHIFT   (0U)
#define DMA_TCD_TCD4_BITER_ELINKNO_BITER_WIDTH   (15U)
#define DMA_TCD_TCD4_BITER_ELINKNO_BITER(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD4_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD4_BITER_ELINKNO_ELINK_MASK    (0x8000U)
#define DMA_TCD_TCD4_BITER_ELINKNO_ELINK_SHIFT   (15U)
#define DMA_TCD_TCD4_BITER_ELINKNO_ELINK_WIDTH   (1U)
#define DMA_TCD_TCD4_BITER_ELINKNO_ELINK(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD4_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD4_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD4_BITER_ELINKYES_BITER_MASK   (0x1FFU)
#define DMA_TCD_TCD4_BITER_ELINKYES_BITER_SHIFT  (0U)
#define DMA_TCD_TCD4_BITER_ELINKYES_BITER_WIDTH  (9U)
#define DMA_TCD_TCD4_BITER_ELINKYES_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD4_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD4_BITER_ELINKYES_LINKCH_MASK  (0x3E00U)
#define DMA_TCD_TCD4_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD4_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD4_BITER_ELINKYES_LINKCH(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD4_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD4_BITER_ELINKYES_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD4_BITER_ELINKYES_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD4_BITER_ELINKYES_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD4_BITER_ELINKYES_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD4_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD4_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH5_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH5_CSR_ERQ_MASK                 (0x1U)
#define DMA_TCD_CH5_CSR_ERQ_SHIFT                (0U)
#define DMA_TCD_CH5_CSR_ERQ_WIDTH                (1U)
#define DMA_TCD_CH5_CSR_ERQ(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_CSR_ERQ_SHIFT)) & DMA_TCD_CH5_CSR_ERQ_MASK)

#define DMA_TCD_CH5_CSR_EARQ_MASK                (0x2U)
#define DMA_TCD_CH5_CSR_EARQ_SHIFT               (1U)
#define DMA_TCD_CH5_CSR_EARQ_WIDTH               (1U)
#define DMA_TCD_CH5_CSR_EARQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_CSR_EARQ_SHIFT)) & DMA_TCD_CH5_CSR_EARQ_MASK)

#define DMA_TCD_CH5_CSR_EEI_MASK                 (0x4U)
#define DMA_TCD_CH5_CSR_EEI_SHIFT                (2U)
#define DMA_TCD_CH5_CSR_EEI_WIDTH                (1U)
#define DMA_TCD_CH5_CSR_EEI(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_CSR_EEI_SHIFT)) & DMA_TCD_CH5_CSR_EEI_MASK)

#define DMA_TCD_CH5_CSR_EBW_MASK                 (0x8U)
#define DMA_TCD_CH5_CSR_EBW_SHIFT                (3U)
#define DMA_TCD_CH5_CSR_EBW_WIDTH                (1U)
#define DMA_TCD_CH5_CSR_EBW(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_CSR_EBW_SHIFT)) & DMA_TCD_CH5_CSR_EBW_MASK)

#define DMA_TCD_CH5_CSR_DONE_MASK                (0x40000000U)
#define DMA_TCD_CH5_CSR_DONE_SHIFT               (30U)
#define DMA_TCD_CH5_CSR_DONE_WIDTH               (1U)
#define DMA_TCD_CH5_CSR_DONE(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_CSR_DONE_SHIFT)) & DMA_TCD_CH5_CSR_DONE_MASK)

#define DMA_TCD_CH5_CSR_ACTIVE_MASK              (0x80000000U)
#define DMA_TCD_CH5_CSR_ACTIVE_SHIFT             (31U)
#define DMA_TCD_CH5_CSR_ACTIVE_WIDTH             (1U)
#define DMA_TCD_CH5_CSR_ACTIVE(x)                (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH5_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH5_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH5_ES_DBE_MASK                  (0x1U)
#define DMA_TCD_CH5_ES_DBE_SHIFT                 (0U)
#define DMA_TCD_CH5_ES_DBE_WIDTH                 (1U)
#define DMA_TCD_CH5_ES_DBE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_ES_DBE_SHIFT)) & DMA_TCD_CH5_ES_DBE_MASK)

#define DMA_TCD_CH5_ES_SBE_MASK                  (0x2U)
#define DMA_TCD_CH5_ES_SBE_SHIFT                 (1U)
#define DMA_TCD_CH5_ES_SBE_WIDTH                 (1U)
#define DMA_TCD_CH5_ES_SBE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_ES_SBE_SHIFT)) & DMA_TCD_CH5_ES_SBE_MASK)

#define DMA_TCD_CH5_ES_SGE_MASK                  (0x4U)
#define DMA_TCD_CH5_ES_SGE_SHIFT                 (2U)
#define DMA_TCD_CH5_ES_SGE_WIDTH                 (1U)
#define DMA_TCD_CH5_ES_SGE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_ES_SGE_SHIFT)) & DMA_TCD_CH5_ES_SGE_MASK)

#define DMA_TCD_CH5_ES_NCE_MASK                  (0x8U)
#define DMA_TCD_CH5_ES_NCE_SHIFT                 (3U)
#define DMA_TCD_CH5_ES_NCE_WIDTH                 (1U)
#define DMA_TCD_CH5_ES_NCE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_ES_NCE_SHIFT)) & DMA_TCD_CH5_ES_NCE_MASK)

#define DMA_TCD_CH5_ES_DOE_MASK                  (0x10U)
#define DMA_TCD_CH5_ES_DOE_SHIFT                 (4U)
#define DMA_TCD_CH5_ES_DOE_WIDTH                 (1U)
#define DMA_TCD_CH5_ES_DOE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_ES_DOE_SHIFT)) & DMA_TCD_CH5_ES_DOE_MASK)

#define DMA_TCD_CH5_ES_DAE_MASK                  (0x20U)
#define DMA_TCD_CH5_ES_DAE_SHIFT                 (5U)
#define DMA_TCD_CH5_ES_DAE_WIDTH                 (1U)
#define DMA_TCD_CH5_ES_DAE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_ES_DAE_SHIFT)) & DMA_TCD_CH5_ES_DAE_MASK)

#define DMA_TCD_CH5_ES_SOE_MASK                  (0x40U)
#define DMA_TCD_CH5_ES_SOE_SHIFT                 (6U)
#define DMA_TCD_CH5_ES_SOE_WIDTH                 (1U)
#define DMA_TCD_CH5_ES_SOE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_ES_SOE_SHIFT)) & DMA_TCD_CH5_ES_SOE_MASK)

#define DMA_TCD_CH5_ES_SAE_MASK                  (0x80U)
#define DMA_TCD_CH5_ES_SAE_SHIFT                 (7U)
#define DMA_TCD_CH5_ES_SAE_WIDTH                 (1U)
#define DMA_TCD_CH5_ES_SAE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_ES_SAE_SHIFT)) & DMA_TCD_CH5_ES_SAE_MASK)

#define DMA_TCD_CH5_ES_ERR_MASK                  (0x80000000U)
#define DMA_TCD_CH5_ES_ERR_SHIFT                 (31U)
#define DMA_TCD_CH5_ES_ERR_WIDTH                 (1U)
#define DMA_TCD_CH5_ES_ERR(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_ES_ERR_SHIFT)) & DMA_TCD_CH5_ES_ERR_MASK)
/*! @} */

/*! @name CH5_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH5_INT_INT_MASK                 (0x1U)
#define DMA_TCD_CH5_INT_INT_SHIFT                (0U)
#define DMA_TCD_CH5_INT_INT_WIDTH                (1U)
#define DMA_TCD_CH5_INT_INT(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_INT_INT_SHIFT)) & DMA_TCD_CH5_INT_INT_MASK)
/*! @} */

/*! @name CH5_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH5_SBR_MID_MASK                 (0xFU)
#define DMA_TCD_CH5_SBR_MID_SHIFT                (0U)
#define DMA_TCD_CH5_SBR_MID_WIDTH                (4U)
#define DMA_TCD_CH5_SBR_MID(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_SBR_MID_SHIFT)) & DMA_TCD_CH5_SBR_MID_MASK)

#define DMA_TCD_CH5_SBR_PAL_MASK                 (0x8000U)
#define DMA_TCD_CH5_SBR_PAL_SHIFT                (15U)
#define DMA_TCD_CH5_SBR_PAL_WIDTH                (1U)
#define DMA_TCD_CH5_SBR_PAL(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_SBR_PAL_SHIFT)) & DMA_TCD_CH5_SBR_PAL_MASK)

#define DMA_TCD_CH5_SBR_EMI_MASK                 (0x10000U)
#define DMA_TCD_CH5_SBR_EMI_SHIFT                (16U)
#define DMA_TCD_CH5_SBR_EMI_WIDTH                (1U)
#define DMA_TCD_CH5_SBR_EMI(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_SBR_EMI_SHIFT)) & DMA_TCD_CH5_SBR_EMI_MASK)

#define DMA_TCD_CH5_SBR_ATTR_MASK                (0xE0000U)
#define DMA_TCD_CH5_SBR_ATTR_SHIFT               (17U)
#define DMA_TCD_CH5_SBR_ATTR_WIDTH               (3U)
#define DMA_TCD_CH5_SBR_ATTR(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_SBR_ATTR_SHIFT)) & DMA_TCD_CH5_SBR_ATTR_MASK)
/*! @} */

/*! @name CH5_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH5_PRI_APL_MASK                 (0x7U)
#define DMA_TCD_CH5_PRI_APL_SHIFT                (0U)
#define DMA_TCD_CH5_PRI_APL_WIDTH                (3U)
#define DMA_TCD_CH5_PRI_APL(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_PRI_APL_SHIFT)) & DMA_TCD_CH5_PRI_APL_MASK)

#define DMA_TCD_CH5_PRI_DPA_MASK                 (0x40000000U)
#define DMA_TCD_CH5_PRI_DPA_SHIFT                (30U)
#define DMA_TCD_CH5_PRI_DPA_WIDTH                (1U)
#define DMA_TCD_CH5_PRI_DPA(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_PRI_DPA_SHIFT)) & DMA_TCD_CH5_PRI_DPA_MASK)

#define DMA_TCD_CH5_PRI_ECP_MASK                 (0x80000000U)
#define DMA_TCD_CH5_PRI_ECP_SHIFT                (31U)
#define DMA_TCD_CH5_PRI_ECP_WIDTH                (1U)
#define DMA_TCD_CH5_PRI_ECP(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH5_PRI_ECP_SHIFT)) & DMA_TCD_CH5_PRI_ECP_MASK)
/*! @} */

/*! @name TCD5_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD5_SADDR_SADDR_MASK            (0xFFFFFFFFU)
#define DMA_TCD_TCD5_SADDR_SADDR_SHIFT           (0U)
#define DMA_TCD_TCD5_SADDR_SADDR_WIDTH           (32U)
#define DMA_TCD_TCD5_SADDR_SADDR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD5_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD5_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD5_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD5_SOFF_SOFF_MASK              (0xFFFFU)
#define DMA_TCD_TCD5_SOFF_SOFF_SHIFT             (0U)
#define DMA_TCD_TCD5_SOFF_SOFF_WIDTH             (16U)
#define DMA_TCD_TCD5_SOFF_SOFF(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD5_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD5_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD5_ATTR_DSIZE_MASK             (0x7U)
#define DMA_TCD_TCD5_ATTR_DSIZE_SHIFT            (0U)
#define DMA_TCD_TCD5_ATTR_DSIZE_WIDTH            (3U)
#define DMA_TCD_TCD5_ATTR_DSIZE(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD5_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD5_ATTR_DMOD_MASK              (0xF8U)
#define DMA_TCD_TCD5_ATTR_DMOD_SHIFT             (3U)
#define DMA_TCD_TCD5_ATTR_DMOD_WIDTH             (5U)
#define DMA_TCD_TCD5_ATTR_DMOD(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD5_ATTR_DMOD_MASK)

#define DMA_TCD_TCD5_ATTR_SSIZE_MASK             (0x700U)
#define DMA_TCD_TCD5_ATTR_SSIZE_SHIFT            (8U)
#define DMA_TCD_TCD5_ATTR_SSIZE_WIDTH            (3U)
#define DMA_TCD_TCD5_ATTR_SSIZE(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD5_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD5_ATTR_SMOD_MASK              (0xF800U)
#define DMA_TCD_TCD5_ATTR_SMOD_SHIFT             (11U)
#define DMA_TCD_TCD5_ATTR_SMOD_WIDTH             (5U)
#define DMA_TCD_TCD5_ATTR_SMOD(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD5_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD5_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD5_NBYTES_MLOFFNO_NBYTES_MASK  (0x3FFFFFFFU)
#define DMA_TCD_TCD5_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD5_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD5_NBYTES_MLOFFNO_NBYTES(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD5_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD5_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD5_NBYTES_MLOFFNO_DMLOE_MASK   (0x40000000U)
#define DMA_TCD_TCD5_NBYTES_MLOFFNO_DMLOE_SHIFT  (30U)
#define DMA_TCD_TCD5_NBYTES_MLOFFNO_DMLOE_WIDTH  (1U)
#define DMA_TCD_TCD5_NBYTES_MLOFFNO_DMLOE(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD5_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD5_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD5_NBYTES_MLOFFNO_SMLOE_MASK   (0x80000000U)
#define DMA_TCD_TCD5_NBYTES_MLOFFNO_SMLOE_SHIFT  (31U)
#define DMA_TCD_TCD5_NBYTES_MLOFFNO_SMLOE_WIDTH  (1U)
#define DMA_TCD_TCD5_NBYTES_MLOFFNO_SMLOE(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD5_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD5_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD5_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD5_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD5_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD5_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD5_NBYTES_MLOFFYES_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD5_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD5_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD5_NBYTES_MLOFFYES_MLOFF_MASK  (0x3FFFFC00U)
#define DMA_TCD_TCD5_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD5_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD5_NBYTES_MLOFFYES_MLOFF(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD5_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD5_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD5_NBYTES_MLOFFYES_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD5_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD5_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD5_NBYTES_MLOFFYES_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD5_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD5_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD5_NBYTES_MLOFFYES_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD5_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD5_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD5_NBYTES_MLOFFYES_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD5_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD5_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD5_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD5_SLAST_SDA_SLAST_SDA_MASK    (0xFFFFFFFFU)
#define DMA_TCD_TCD5_SLAST_SDA_SLAST_SDA_SHIFT   (0U)
#define DMA_TCD_TCD5_SLAST_SDA_SLAST_SDA_WIDTH   (32U)
#define DMA_TCD_TCD5_SLAST_SDA_SLAST_SDA(x)      (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD5_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD5_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD5_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD5_DADDR_DADDR_MASK            (0xFFFFFFFFU)
#define DMA_TCD_TCD5_DADDR_DADDR_SHIFT           (0U)
#define DMA_TCD_TCD5_DADDR_DADDR_WIDTH           (32U)
#define DMA_TCD_TCD5_DADDR_DADDR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD5_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD5_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD5_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD5_DOFF_DOFF_MASK              (0xFFFFU)
#define DMA_TCD_TCD5_DOFF_DOFF_SHIFT             (0U)
#define DMA_TCD_TCD5_DOFF_DOFF_WIDTH             (16U)
#define DMA_TCD_TCD5_DOFF_DOFF(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD5_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD5_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD5_CITER_ELINKNO_CITER_MASK    (0x7FFFU)
#define DMA_TCD_TCD5_CITER_ELINKNO_CITER_SHIFT   (0U)
#define DMA_TCD_TCD5_CITER_ELINKNO_CITER_WIDTH   (15U)
#define DMA_TCD_TCD5_CITER_ELINKNO_CITER(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD5_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD5_CITER_ELINKNO_ELINK_MASK    (0x8000U)
#define DMA_TCD_TCD5_CITER_ELINKNO_ELINK_SHIFT   (15U)
#define DMA_TCD_TCD5_CITER_ELINKNO_ELINK_WIDTH   (1U)
#define DMA_TCD_TCD5_CITER_ELINKNO_ELINK(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD5_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD5_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD5_CITER_ELINKYES_CITER_MASK   (0x1FFU)
#define DMA_TCD_TCD5_CITER_ELINKYES_CITER_SHIFT  (0U)
#define DMA_TCD_TCD5_CITER_ELINKYES_CITER_WIDTH  (9U)
#define DMA_TCD_TCD5_CITER_ELINKYES_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD5_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD5_CITER_ELINKYES_LINKCH_MASK  (0x3E00U)
#define DMA_TCD_TCD5_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD5_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD5_CITER_ELINKYES_LINKCH(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD5_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD5_CITER_ELINKYES_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD5_CITER_ELINKYES_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD5_CITER_ELINKYES_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD5_CITER_ELINKYES_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD5_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD5_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD5_DLAST_SGA_DLAST_SGA_MASK    (0xFFFFFFFFU)
#define DMA_TCD_TCD5_DLAST_SGA_DLAST_SGA_SHIFT   (0U)
#define DMA_TCD_TCD5_DLAST_SGA_DLAST_SGA_WIDTH   (32U)
#define DMA_TCD_TCD5_DLAST_SGA_DLAST_SGA(x)      (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD5_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD5_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD5_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD5_CSR_START_MASK              (0x1U)
#define DMA_TCD_TCD5_CSR_START_SHIFT             (0U)
#define DMA_TCD_TCD5_CSR_START_WIDTH             (1U)
#define DMA_TCD_TCD5_CSR_START(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_CSR_START_SHIFT)) & DMA_TCD_TCD5_CSR_START_MASK)

#define DMA_TCD_TCD5_CSR_INTMAJOR_MASK           (0x2U)
#define DMA_TCD_TCD5_CSR_INTMAJOR_SHIFT          (1U)
#define DMA_TCD_TCD5_CSR_INTMAJOR_WIDTH          (1U)
#define DMA_TCD_TCD5_CSR_INTMAJOR(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD5_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD5_CSR_INTHALF_MASK            (0x4U)
#define DMA_TCD_TCD5_CSR_INTHALF_SHIFT           (2U)
#define DMA_TCD_TCD5_CSR_INTHALF_WIDTH           (1U)
#define DMA_TCD_TCD5_CSR_INTHALF(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD5_CSR_INTHALF_MASK)

#define DMA_TCD_TCD5_CSR_DREQ_MASK               (0x8U)
#define DMA_TCD_TCD5_CSR_DREQ_SHIFT              (3U)
#define DMA_TCD_TCD5_CSR_DREQ_WIDTH              (1U)
#define DMA_TCD_TCD5_CSR_DREQ(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_CSR_DREQ_SHIFT)) & DMA_TCD_TCD5_CSR_DREQ_MASK)

#define DMA_TCD_TCD5_CSR_ESG_MASK                (0x10U)
#define DMA_TCD_TCD5_CSR_ESG_SHIFT               (4U)
#define DMA_TCD_TCD5_CSR_ESG_WIDTH               (1U)
#define DMA_TCD_TCD5_CSR_ESG(x)                  (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_CSR_ESG_SHIFT)) & DMA_TCD_TCD5_CSR_ESG_MASK)

#define DMA_TCD_TCD5_CSR_MAJORELINK_MASK         (0x20U)
#define DMA_TCD_TCD5_CSR_MAJORELINK_SHIFT        (5U)
#define DMA_TCD_TCD5_CSR_MAJORELINK_WIDTH        (1U)
#define DMA_TCD_TCD5_CSR_MAJORELINK(x)           (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD5_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD5_CSR_EEOP_MASK               (0x40U)
#define DMA_TCD_TCD5_CSR_EEOP_SHIFT              (6U)
#define DMA_TCD_TCD5_CSR_EEOP_WIDTH              (1U)
#define DMA_TCD_TCD5_CSR_EEOP(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_CSR_EEOP_SHIFT)) & DMA_TCD_TCD5_CSR_EEOP_MASK)

#define DMA_TCD_TCD5_CSR_ESDA_MASK               (0x80U)
#define DMA_TCD_TCD5_CSR_ESDA_SHIFT              (7U)
#define DMA_TCD_TCD5_CSR_ESDA_WIDTH              (1U)
#define DMA_TCD_TCD5_CSR_ESDA(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_CSR_ESDA_SHIFT)) & DMA_TCD_TCD5_CSR_ESDA_MASK)

#define DMA_TCD_TCD5_CSR_MAJORLINKCH_MASK        (0x1F00U)
#define DMA_TCD_TCD5_CSR_MAJORLINKCH_SHIFT       (8U)
#define DMA_TCD_TCD5_CSR_MAJORLINKCH_WIDTH       (5U)
#define DMA_TCD_TCD5_CSR_MAJORLINKCH(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD5_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD5_CSR_BWC_MASK                (0xC000U)
#define DMA_TCD_TCD5_CSR_BWC_SHIFT               (14U)
#define DMA_TCD_TCD5_CSR_BWC_WIDTH               (2U)
#define DMA_TCD_TCD5_CSR_BWC(x)                  (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_CSR_BWC_SHIFT)) & DMA_TCD_TCD5_CSR_BWC_MASK)
/*! @} */

/*! @name TCD5_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD5_BITER_ELINKNO_BITER_MASK    (0x7FFFU)
#define DMA_TCD_TCD5_BITER_ELINKNO_BITER_SHIFT   (0U)
#define DMA_TCD_TCD5_BITER_ELINKNO_BITER_WIDTH   (15U)
#define DMA_TCD_TCD5_BITER_ELINKNO_BITER(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD5_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD5_BITER_ELINKNO_ELINK_MASK    (0x8000U)
#define DMA_TCD_TCD5_BITER_ELINKNO_ELINK_SHIFT   (15U)
#define DMA_TCD_TCD5_BITER_ELINKNO_ELINK_WIDTH   (1U)
#define DMA_TCD_TCD5_BITER_ELINKNO_ELINK(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD5_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD5_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD5_BITER_ELINKYES_BITER_MASK   (0x1FFU)
#define DMA_TCD_TCD5_BITER_ELINKYES_BITER_SHIFT  (0U)
#define DMA_TCD_TCD5_BITER_ELINKYES_BITER_WIDTH  (9U)
#define DMA_TCD_TCD5_BITER_ELINKYES_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD5_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD5_BITER_ELINKYES_LINKCH_MASK  (0x3E00U)
#define DMA_TCD_TCD5_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD5_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD5_BITER_ELINKYES_LINKCH(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD5_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD5_BITER_ELINKYES_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD5_BITER_ELINKYES_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD5_BITER_ELINKYES_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD5_BITER_ELINKYES_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD5_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD5_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH6_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH6_CSR_ERQ_MASK                 (0x1U)
#define DMA_TCD_CH6_CSR_ERQ_SHIFT                (0U)
#define DMA_TCD_CH6_CSR_ERQ_WIDTH                (1U)
#define DMA_TCD_CH6_CSR_ERQ(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_CSR_ERQ_SHIFT)) & DMA_TCD_CH6_CSR_ERQ_MASK)

#define DMA_TCD_CH6_CSR_EARQ_MASK                (0x2U)
#define DMA_TCD_CH6_CSR_EARQ_SHIFT               (1U)
#define DMA_TCD_CH6_CSR_EARQ_WIDTH               (1U)
#define DMA_TCD_CH6_CSR_EARQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_CSR_EARQ_SHIFT)) & DMA_TCD_CH6_CSR_EARQ_MASK)

#define DMA_TCD_CH6_CSR_EEI_MASK                 (0x4U)
#define DMA_TCD_CH6_CSR_EEI_SHIFT                (2U)
#define DMA_TCD_CH6_CSR_EEI_WIDTH                (1U)
#define DMA_TCD_CH6_CSR_EEI(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_CSR_EEI_SHIFT)) & DMA_TCD_CH6_CSR_EEI_MASK)

#define DMA_TCD_CH6_CSR_EBW_MASK                 (0x8U)
#define DMA_TCD_CH6_CSR_EBW_SHIFT                (3U)
#define DMA_TCD_CH6_CSR_EBW_WIDTH                (1U)
#define DMA_TCD_CH6_CSR_EBW(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_CSR_EBW_SHIFT)) & DMA_TCD_CH6_CSR_EBW_MASK)

#define DMA_TCD_CH6_CSR_DONE_MASK                (0x40000000U)
#define DMA_TCD_CH6_CSR_DONE_SHIFT               (30U)
#define DMA_TCD_CH6_CSR_DONE_WIDTH               (1U)
#define DMA_TCD_CH6_CSR_DONE(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_CSR_DONE_SHIFT)) & DMA_TCD_CH6_CSR_DONE_MASK)

#define DMA_TCD_CH6_CSR_ACTIVE_MASK              (0x80000000U)
#define DMA_TCD_CH6_CSR_ACTIVE_SHIFT             (31U)
#define DMA_TCD_CH6_CSR_ACTIVE_WIDTH             (1U)
#define DMA_TCD_CH6_CSR_ACTIVE(x)                (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH6_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH6_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH6_ES_DBE_MASK                  (0x1U)
#define DMA_TCD_CH6_ES_DBE_SHIFT                 (0U)
#define DMA_TCD_CH6_ES_DBE_WIDTH                 (1U)
#define DMA_TCD_CH6_ES_DBE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_ES_DBE_SHIFT)) & DMA_TCD_CH6_ES_DBE_MASK)

#define DMA_TCD_CH6_ES_SBE_MASK                  (0x2U)
#define DMA_TCD_CH6_ES_SBE_SHIFT                 (1U)
#define DMA_TCD_CH6_ES_SBE_WIDTH                 (1U)
#define DMA_TCD_CH6_ES_SBE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_ES_SBE_SHIFT)) & DMA_TCD_CH6_ES_SBE_MASK)

#define DMA_TCD_CH6_ES_SGE_MASK                  (0x4U)
#define DMA_TCD_CH6_ES_SGE_SHIFT                 (2U)
#define DMA_TCD_CH6_ES_SGE_WIDTH                 (1U)
#define DMA_TCD_CH6_ES_SGE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_ES_SGE_SHIFT)) & DMA_TCD_CH6_ES_SGE_MASK)

#define DMA_TCD_CH6_ES_NCE_MASK                  (0x8U)
#define DMA_TCD_CH6_ES_NCE_SHIFT                 (3U)
#define DMA_TCD_CH6_ES_NCE_WIDTH                 (1U)
#define DMA_TCD_CH6_ES_NCE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_ES_NCE_SHIFT)) & DMA_TCD_CH6_ES_NCE_MASK)

#define DMA_TCD_CH6_ES_DOE_MASK                  (0x10U)
#define DMA_TCD_CH6_ES_DOE_SHIFT                 (4U)
#define DMA_TCD_CH6_ES_DOE_WIDTH                 (1U)
#define DMA_TCD_CH6_ES_DOE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_ES_DOE_SHIFT)) & DMA_TCD_CH6_ES_DOE_MASK)

#define DMA_TCD_CH6_ES_DAE_MASK                  (0x20U)
#define DMA_TCD_CH6_ES_DAE_SHIFT                 (5U)
#define DMA_TCD_CH6_ES_DAE_WIDTH                 (1U)
#define DMA_TCD_CH6_ES_DAE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_ES_DAE_SHIFT)) & DMA_TCD_CH6_ES_DAE_MASK)

#define DMA_TCD_CH6_ES_SOE_MASK                  (0x40U)
#define DMA_TCD_CH6_ES_SOE_SHIFT                 (6U)
#define DMA_TCD_CH6_ES_SOE_WIDTH                 (1U)
#define DMA_TCD_CH6_ES_SOE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_ES_SOE_SHIFT)) & DMA_TCD_CH6_ES_SOE_MASK)

#define DMA_TCD_CH6_ES_SAE_MASK                  (0x80U)
#define DMA_TCD_CH6_ES_SAE_SHIFT                 (7U)
#define DMA_TCD_CH6_ES_SAE_WIDTH                 (1U)
#define DMA_TCD_CH6_ES_SAE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_ES_SAE_SHIFT)) & DMA_TCD_CH6_ES_SAE_MASK)

#define DMA_TCD_CH6_ES_ERR_MASK                  (0x80000000U)
#define DMA_TCD_CH6_ES_ERR_SHIFT                 (31U)
#define DMA_TCD_CH6_ES_ERR_WIDTH                 (1U)
#define DMA_TCD_CH6_ES_ERR(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_ES_ERR_SHIFT)) & DMA_TCD_CH6_ES_ERR_MASK)
/*! @} */

/*! @name CH6_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH6_INT_INT_MASK                 (0x1U)
#define DMA_TCD_CH6_INT_INT_SHIFT                (0U)
#define DMA_TCD_CH6_INT_INT_WIDTH                (1U)
#define DMA_TCD_CH6_INT_INT(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_INT_INT_SHIFT)) & DMA_TCD_CH6_INT_INT_MASK)
/*! @} */

/*! @name CH6_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH6_SBR_MID_MASK                 (0xFU)
#define DMA_TCD_CH6_SBR_MID_SHIFT                (0U)
#define DMA_TCD_CH6_SBR_MID_WIDTH                (4U)
#define DMA_TCD_CH6_SBR_MID(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_SBR_MID_SHIFT)) & DMA_TCD_CH6_SBR_MID_MASK)

#define DMA_TCD_CH6_SBR_PAL_MASK                 (0x8000U)
#define DMA_TCD_CH6_SBR_PAL_SHIFT                (15U)
#define DMA_TCD_CH6_SBR_PAL_WIDTH                (1U)
#define DMA_TCD_CH6_SBR_PAL(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_SBR_PAL_SHIFT)) & DMA_TCD_CH6_SBR_PAL_MASK)

#define DMA_TCD_CH6_SBR_EMI_MASK                 (0x10000U)
#define DMA_TCD_CH6_SBR_EMI_SHIFT                (16U)
#define DMA_TCD_CH6_SBR_EMI_WIDTH                (1U)
#define DMA_TCD_CH6_SBR_EMI(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_SBR_EMI_SHIFT)) & DMA_TCD_CH6_SBR_EMI_MASK)

#define DMA_TCD_CH6_SBR_ATTR_MASK                (0xE0000U)
#define DMA_TCD_CH6_SBR_ATTR_SHIFT               (17U)
#define DMA_TCD_CH6_SBR_ATTR_WIDTH               (3U)
#define DMA_TCD_CH6_SBR_ATTR(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_SBR_ATTR_SHIFT)) & DMA_TCD_CH6_SBR_ATTR_MASK)
/*! @} */

/*! @name CH6_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH6_PRI_APL_MASK                 (0x7U)
#define DMA_TCD_CH6_PRI_APL_SHIFT                (0U)
#define DMA_TCD_CH6_PRI_APL_WIDTH                (3U)
#define DMA_TCD_CH6_PRI_APL(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_PRI_APL_SHIFT)) & DMA_TCD_CH6_PRI_APL_MASK)

#define DMA_TCD_CH6_PRI_DPA_MASK                 (0x40000000U)
#define DMA_TCD_CH6_PRI_DPA_SHIFT                (30U)
#define DMA_TCD_CH6_PRI_DPA_WIDTH                (1U)
#define DMA_TCD_CH6_PRI_DPA(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_PRI_DPA_SHIFT)) & DMA_TCD_CH6_PRI_DPA_MASK)

#define DMA_TCD_CH6_PRI_ECP_MASK                 (0x80000000U)
#define DMA_TCD_CH6_PRI_ECP_SHIFT                (31U)
#define DMA_TCD_CH6_PRI_ECP_WIDTH                (1U)
#define DMA_TCD_CH6_PRI_ECP(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH6_PRI_ECP_SHIFT)) & DMA_TCD_CH6_PRI_ECP_MASK)
/*! @} */

/*! @name TCD6_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD6_SADDR_SADDR_MASK            (0xFFFFFFFFU)
#define DMA_TCD_TCD6_SADDR_SADDR_SHIFT           (0U)
#define DMA_TCD_TCD6_SADDR_SADDR_WIDTH           (32U)
#define DMA_TCD_TCD6_SADDR_SADDR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD6_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD6_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD6_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD6_SOFF_SOFF_MASK              (0xFFFFU)
#define DMA_TCD_TCD6_SOFF_SOFF_SHIFT             (0U)
#define DMA_TCD_TCD6_SOFF_SOFF_WIDTH             (16U)
#define DMA_TCD_TCD6_SOFF_SOFF(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD6_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD6_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD6_ATTR_DSIZE_MASK             (0x7U)
#define DMA_TCD_TCD6_ATTR_DSIZE_SHIFT            (0U)
#define DMA_TCD_TCD6_ATTR_DSIZE_WIDTH            (3U)
#define DMA_TCD_TCD6_ATTR_DSIZE(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD6_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD6_ATTR_DMOD_MASK              (0xF8U)
#define DMA_TCD_TCD6_ATTR_DMOD_SHIFT             (3U)
#define DMA_TCD_TCD6_ATTR_DMOD_WIDTH             (5U)
#define DMA_TCD_TCD6_ATTR_DMOD(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD6_ATTR_DMOD_MASK)

#define DMA_TCD_TCD6_ATTR_SSIZE_MASK             (0x700U)
#define DMA_TCD_TCD6_ATTR_SSIZE_SHIFT            (8U)
#define DMA_TCD_TCD6_ATTR_SSIZE_WIDTH            (3U)
#define DMA_TCD_TCD6_ATTR_SSIZE(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD6_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD6_ATTR_SMOD_MASK              (0xF800U)
#define DMA_TCD_TCD6_ATTR_SMOD_SHIFT             (11U)
#define DMA_TCD_TCD6_ATTR_SMOD_WIDTH             (5U)
#define DMA_TCD_TCD6_ATTR_SMOD(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD6_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD6_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD6_NBYTES_MLOFFNO_NBYTES_MASK  (0x3FFFFFFFU)
#define DMA_TCD_TCD6_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD6_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD6_NBYTES_MLOFFNO_NBYTES(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD6_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD6_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD6_NBYTES_MLOFFNO_DMLOE_MASK   (0x40000000U)
#define DMA_TCD_TCD6_NBYTES_MLOFFNO_DMLOE_SHIFT  (30U)
#define DMA_TCD_TCD6_NBYTES_MLOFFNO_DMLOE_WIDTH  (1U)
#define DMA_TCD_TCD6_NBYTES_MLOFFNO_DMLOE(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD6_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD6_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD6_NBYTES_MLOFFNO_SMLOE_MASK   (0x80000000U)
#define DMA_TCD_TCD6_NBYTES_MLOFFNO_SMLOE_SHIFT  (31U)
#define DMA_TCD_TCD6_NBYTES_MLOFFNO_SMLOE_WIDTH  (1U)
#define DMA_TCD_TCD6_NBYTES_MLOFFNO_SMLOE(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD6_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD6_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD6_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD6_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD6_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD6_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD6_NBYTES_MLOFFYES_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD6_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD6_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD6_NBYTES_MLOFFYES_MLOFF_MASK  (0x3FFFFC00U)
#define DMA_TCD_TCD6_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD6_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD6_NBYTES_MLOFFYES_MLOFF(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD6_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD6_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD6_NBYTES_MLOFFYES_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD6_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD6_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD6_NBYTES_MLOFFYES_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD6_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD6_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD6_NBYTES_MLOFFYES_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD6_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD6_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD6_NBYTES_MLOFFYES_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD6_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD6_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD6_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD6_SLAST_SDA_SLAST_SDA_MASK    (0xFFFFFFFFU)
#define DMA_TCD_TCD6_SLAST_SDA_SLAST_SDA_SHIFT   (0U)
#define DMA_TCD_TCD6_SLAST_SDA_SLAST_SDA_WIDTH   (32U)
#define DMA_TCD_TCD6_SLAST_SDA_SLAST_SDA(x)      (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD6_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD6_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD6_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD6_DADDR_DADDR_MASK            (0xFFFFFFFFU)
#define DMA_TCD_TCD6_DADDR_DADDR_SHIFT           (0U)
#define DMA_TCD_TCD6_DADDR_DADDR_WIDTH           (32U)
#define DMA_TCD_TCD6_DADDR_DADDR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD6_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD6_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD6_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD6_DOFF_DOFF_MASK              (0xFFFFU)
#define DMA_TCD_TCD6_DOFF_DOFF_SHIFT             (0U)
#define DMA_TCD_TCD6_DOFF_DOFF_WIDTH             (16U)
#define DMA_TCD_TCD6_DOFF_DOFF(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD6_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD6_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD6_CITER_ELINKNO_CITER_MASK    (0x7FFFU)
#define DMA_TCD_TCD6_CITER_ELINKNO_CITER_SHIFT   (0U)
#define DMA_TCD_TCD6_CITER_ELINKNO_CITER_WIDTH   (15U)
#define DMA_TCD_TCD6_CITER_ELINKNO_CITER(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD6_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD6_CITER_ELINKNO_ELINK_MASK    (0x8000U)
#define DMA_TCD_TCD6_CITER_ELINKNO_ELINK_SHIFT   (15U)
#define DMA_TCD_TCD6_CITER_ELINKNO_ELINK_WIDTH   (1U)
#define DMA_TCD_TCD6_CITER_ELINKNO_ELINK(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD6_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD6_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD6_CITER_ELINKYES_CITER_MASK   (0x1FFU)
#define DMA_TCD_TCD6_CITER_ELINKYES_CITER_SHIFT  (0U)
#define DMA_TCD_TCD6_CITER_ELINKYES_CITER_WIDTH  (9U)
#define DMA_TCD_TCD6_CITER_ELINKYES_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD6_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD6_CITER_ELINKYES_LINKCH_MASK  (0x3E00U)
#define DMA_TCD_TCD6_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD6_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD6_CITER_ELINKYES_LINKCH(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD6_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD6_CITER_ELINKYES_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD6_CITER_ELINKYES_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD6_CITER_ELINKYES_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD6_CITER_ELINKYES_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD6_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD6_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD6_DLAST_SGA_DLAST_SGA_MASK    (0xFFFFFFFFU)
#define DMA_TCD_TCD6_DLAST_SGA_DLAST_SGA_SHIFT   (0U)
#define DMA_TCD_TCD6_DLAST_SGA_DLAST_SGA_WIDTH   (32U)
#define DMA_TCD_TCD6_DLAST_SGA_DLAST_SGA(x)      (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD6_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD6_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD6_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD6_CSR_START_MASK              (0x1U)
#define DMA_TCD_TCD6_CSR_START_SHIFT             (0U)
#define DMA_TCD_TCD6_CSR_START_WIDTH             (1U)
#define DMA_TCD_TCD6_CSR_START(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_CSR_START_SHIFT)) & DMA_TCD_TCD6_CSR_START_MASK)

#define DMA_TCD_TCD6_CSR_INTMAJOR_MASK           (0x2U)
#define DMA_TCD_TCD6_CSR_INTMAJOR_SHIFT          (1U)
#define DMA_TCD_TCD6_CSR_INTMAJOR_WIDTH          (1U)
#define DMA_TCD_TCD6_CSR_INTMAJOR(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD6_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD6_CSR_INTHALF_MASK            (0x4U)
#define DMA_TCD_TCD6_CSR_INTHALF_SHIFT           (2U)
#define DMA_TCD_TCD6_CSR_INTHALF_WIDTH           (1U)
#define DMA_TCD_TCD6_CSR_INTHALF(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD6_CSR_INTHALF_MASK)

#define DMA_TCD_TCD6_CSR_DREQ_MASK               (0x8U)
#define DMA_TCD_TCD6_CSR_DREQ_SHIFT              (3U)
#define DMA_TCD_TCD6_CSR_DREQ_WIDTH              (1U)
#define DMA_TCD_TCD6_CSR_DREQ(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_CSR_DREQ_SHIFT)) & DMA_TCD_TCD6_CSR_DREQ_MASK)

#define DMA_TCD_TCD6_CSR_ESG_MASK                (0x10U)
#define DMA_TCD_TCD6_CSR_ESG_SHIFT               (4U)
#define DMA_TCD_TCD6_CSR_ESG_WIDTH               (1U)
#define DMA_TCD_TCD6_CSR_ESG(x)                  (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_CSR_ESG_SHIFT)) & DMA_TCD_TCD6_CSR_ESG_MASK)

#define DMA_TCD_TCD6_CSR_MAJORELINK_MASK         (0x20U)
#define DMA_TCD_TCD6_CSR_MAJORELINK_SHIFT        (5U)
#define DMA_TCD_TCD6_CSR_MAJORELINK_WIDTH        (1U)
#define DMA_TCD_TCD6_CSR_MAJORELINK(x)           (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD6_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD6_CSR_EEOP_MASK               (0x40U)
#define DMA_TCD_TCD6_CSR_EEOP_SHIFT              (6U)
#define DMA_TCD_TCD6_CSR_EEOP_WIDTH              (1U)
#define DMA_TCD_TCD6_CSR_EEOP(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_CSR_EEOP_SHIFT)) & DMA_TCD_TCD6_CSR_EEOP_MASK)

#define DMA_TCD_TCD6_CSR_ESDA_MASK               (0x80U)
#define DMA_TCD_TCD6_CSR_ESDA_SHIFT              (7U)
#define DMA_TCD_TCD6_CSR_ESDA_WIDTH              (1U)
#define DMA_TCD_TCD6_CSR_ESDA(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_CSR_ESDA_SHIFT)) & DMA_TCD_TCD6_CSR_ESDA_MASK)

#define DMA_TCD_TCD6_CSR_MAJORLINKCH_MASK        (0x1F00U)
#define DMA_TCD_TCD6_CSR_MAJORLINKCH_SHIFT       (8U)
#define DMA_TCD_TCD6_CSR_MAJORLINKCH_WIDTH       (5U)
#define DMA_TCD_TCD6_CSR_MAJORLINKCH(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD6_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD6_CSR_BWC_MASK                (0xC000U)
#define DMA_TCD_TCD6_CSR_BWC_SHIFT               (14U)
#define DMA_TCD_TCD6_CSR_BWC_WIDTH               (2U)
#define DMA_TCD_TCD6_CSR_BWC(x)                  (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_CSR_BWC_SHIFT)) & DMA_TCD_TCD6_CSR_BWC_MASK)
/*! @} */

/*! @name TCD6_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD6_BITER_ELINKNO_BITER_MASK    (0x7FFFU)
#define DMA_TCD_TCD6_BITER_ELINKNO_BITER_SHIFT   (0U)
#define DMA_TCD_TCD6_BITER_ELINKNO_BITER_WIDTH   (15U)
#define DMA_TCD_TCD6_BITER_ELINKNO_BITER(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD6_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD6_BITER_ELINKNO_ELINK_MASK    (0x8000U)
#define DMA_TCD_TCD6_BITER_ELINKNO_ELINK_SHIFT   (15U)
#define DMA_TCD_TCD6_BITER_ELINKNO_ELINK_WIDTH   (1U)
#define DMA_TCD_TCD6_BITER_ELINKNO_ELINK(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD6_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD6_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD6_BITER_ELINKYES_BITER_MASK   (0x1FFU)
#define DMA_TCD_TCD6_BITER_ELINKYES_BITER_SHIFT  (0U)
#define DMA_TCD_TCD6_BITER_ELINKYES_BITER_WIDTH  (9U)
#define DMA_TCD_TCD6_BITER_ELINKYES_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD6_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD6_BITER_ELINKYES_LINKCH_MASK  (0x3E00U)
#define DMA_TCD_TCD6_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD6_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD6_BITER_ELINKYES_LINKCH(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD6_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD6_BITER_ELINKYES_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD6_BITER_ELINKYES_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD6_BITER_ELINKYES_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD6_BITER_ELINKYES_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD6_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD6_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH7_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH7_CSR_ERQ_MASK                 (0x1U)
#define DMA_TCD_CH7_CSR_ERQ_SHIFT                (0U)
#define DMA_TCD_CH7_CSR_ERQ_WIDTH                (1U)
#define DMA_TCD_CH7_CSR_ERQ(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_CSR_ERQ_SHIFT)) & DMA_TCD_CH7_CSR_ERQ_MASK)

#define DMA_TCD_CH7_CSR_EARQ_MASK                (0x2U)
#define DMA_TCD_CH7_CSR_EARQ_SHIFT               (1U)
#define DMA_TCD_CH7_CSR_EARQ_WIDTH               (1U)
#define DMA_TCD_CH7_CSR_EARQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_CSR_EARQ_SHIFT)) & DMA_TCD_CH7_CSR_EARQ_MASK)

#define DMA_TCD_CH7_CSR_EEI_MASK                 (0x4U)
#define DMA_TCD_CH7_CSR_EEI_SHIFT                (2U)
#define DMA_TCD_CH7_CSR_EEI_WIDTH                (1U)
#define DMA_TCD_CH7_CSR_EEI(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_CSR_EEI_SHIFT)) & DMA_TCD_CH7_CSR_EEI_MASK)

#define DMA_TCD_CH7_CSR_EBW_MASK                 (0x8U)
#define DMA_TCD_CH7_CSR_EBW_SHIFT                (3U)
#define DMA_TCD_CH7_CSR_EBW_WIDTH                (1U)
#define DMA_TCD_CH7_CSR_EBW(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_CSR_EBW_SHIFT)) & DMA_TCD_CH7_CSR_EBW_MASK)

#define DMA_TCD_CH7_CSR_DONE_MASK                (0x40000000U)
#define DMA_TCD_CH7_CSR_DONE_SHIFT               (30U)
#define DMA_TCD_CH7_CSR_DONE_WIDTH               (1U)
#define DMA_TCD_CH7_CSR_DONE(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_CSR_DONE_SHIFT)) & DMA_TCD_CH7_CSR_DONE_MASK)

#define DMA_TCD_CH7_CSR_ACTIVE_MASK              (0x80000000U)
#define DMA_TCD_CH7_CSR_ACTIVE_SHIFT             (31U)
#define DMA_TCD_CH7_CSR_ACTIVE_WIDTH             (1U)
#define DMA_TCD_CH7_CSR_ACTIVE(x)                (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH7_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH7_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH7_ES_DBE_MASK                  (0x1U)
#define DMA_TCD_CH7_ES_DBE_SHIFT                 (0U)
#define DMA_TCD_CH7_ES_DBE_WIDTH                 (1U)
#define DMA_TCD_CH7_ES_DBE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_ES_DBE_SHIFT)) & DMA_TCD_CH7_ES_DBE_MASK)

#define DMA_TCD_CH7_ES_SBE_MASK                  (0x2U)
#define DMA_TCD_CH7_ES_SBE_SHIFT                 (1U)
#define DMA_TCD_CH7_ES_SBE_WIDTH                 (1U)
#define DMA_TCD_CH7_ES_SBE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_ES_SBE_SHIFT)) & DMA_TCD_CH7_ES_SBE_MASK)

#define DMA_TCD_CH7_ES_SGE_MASK                  (0x4U)
#define DMA_TCD_CH7_ES_SGE_SHIFT                 (2U)
#define DMA_TCD_CH7_ES_SGE_WIDTH                 (1U)
#define DMA_TCD_CH7_ES_SGE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_ES_SGE_SHIFT)) & DMA_TCD_CH7_ES_SGE_MASK)

#define DMA_TCD_CH7_ES_NCE_MASK                  (0x8U)
#define DMA_TCD_CH7_ES_NCE_SHIFT                 (3U)
#define DMA_TCD_CH7_ES_NCE_WIDTH                 (1U)
#define DMA_TCD_CH7_ES_NCE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_ES_NCE_SHIFT)) & DMA_TCD_CH7_ES_NCE_MASK)

#define DMA_TCD_CH7_ES_DOE_MASK                  (0x10U)
#define DMA_TCD_CH7_ES_DOE_SHIFT                 (4U)
#define DMA_TCD_CH7_ES_DOE_WIDTH                 (1U)
#define DMA_TCD_CH7_ES_DOE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_ES_DOE_SHIFT)) & DMA_TCD_CH7_ES_DOE_MASK)

#define DMA_TCD_CH7_ES_DAE_MASK                  (0x20U)
#define DMA_TCD_CH7_ES_DAE_SHIFT                 (5U)
#define DMA_TCD_CH7_ES_DAE_WIDTH                 (1U)
#define DMA_TCD_CH7_ES_DAE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_ES_DAE_SHIFT)) & DMA_TCD_CH7_ES_DAE_MASK)

#define DMA_TCD_CH7_ES_SOE_MASK                  (0x40U)
#define DMA_TCD_CH7_ES_SOE_SHIFT                 (6U)
#define DMA_TCD_CH7_ES_SOE_WIDTH                 (1U)
#define DMA_TCD_CH7_ES_SOE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_ES_SOE_SHIFT)) & DMA_TCD_CH7_ES_SOE_MASK)

#define DMA_TCD_CH7_ES_SAE_MASK                  (0x80U)
#define DMA_TCD_CH7_ES_SAE_SHIFT                 (7U)
#define DMA_TCD_CH7_ES_SAE_WIDTH                 (1U)
#define DMA_TCD_CH7_ES_SAE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_ES_SAE_SHIFT)) & DMA_TCD_CH7_ES_SAE_MASK)

#define DMA_TCD_CH7_ES_ERR_MASK                  (0x80000000U)
#define DMA_TCD_CH7_ES_ERR_SHIFT                 (31U)
#define DMA_TCD_CH7_ES_ERR_WIDTH                 (1U)
#define DMA_TCD_CH7_ES_ERR(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_ES_ERR_SHIFT)) & DMA_TCD_CH7_ES_ERR_MASK)
/*! @} */

/*! @name CH7_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH7_INT_INT_MASK                 (0x1U)
#define DMA_TCD_CH7_INT_INT_SHIFT                (0U)
#define DMA_TCD_CH7_INT_INT_WIDTH                (1U)
#define DMA_TCD_CH7_INT_INT(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_INT_INT_SHIFT)) & DMA_TCD_CH7_INT_INT_MASK)
/*! @} */

/*! @name CH7_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH7_SBR_MID_MASK                 (0xFU)
#define DMA_TCD_CH7_SBR_MID_SHIFT                (0U)
#define DMA_TCD_CH7_SBR_MID_WIDTH                (4U)
#define DMA_TCD_CH7_SBR_MID(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_SBR_MID_SHIFT)) & DMA_TCD_CH7_SBR_MID_MASK)

#define DMA_TCD_CH7_SBR_PAL_MASK                 (0x8000U)
#define DMA_TCD_CH7_SBR_PAL_SHIFT                (15U)
#define DMA_TCD_CH7_SBR_PAL_WIDTH                (1U)
#define DMA_TCD_CH7_SBR_PAL(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_SBR_PAL_SHIFT)) & DMA_TCD_CH7_SBR_PAL_MASK)

#define DMA_TCD_CH7_SBR_EMI_MASK                 (0x10000U)
#define DMA_TCD_CH7_SBR_EMI_SHIFT                (16U)
#define DMA_TCD_CH7_SBR_EMI_WIDTH                (1U)
#define DMA_TCD_CH7_SBR_EMI(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_SBR_EMI_SHIFT)) & DMA_TCD_CH7_SBR_EMI_MASK)

#define DMA_TCD_CH7_SBR_ATTR_MASK                (0xE0000U)
#define DMA_TCD_CH7_SBR_ATTR_SHIFT               (17U)
#define DMA_TCD_CH7_SBR_ATTR_WIDTH               (3U)
#define DMA_TCD_CH7_SBR_ATTR(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_SBR_ATTR_SHIFT)) & DMA_TCD_CH7_SBR_ATTR_MASK)
/*! @} */

/*! @name CH7_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH7_PRI_APL_MASK                 (0x7U)
#define DMA_TCD_CH7_PRI_APL_SHIFT                (0U)
#define DMA_TCD_CH7_PRI_APL_WIDTH                (3U)
#define DMA_TCD_CH7_PRI_APL(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_PRI_APL_SHIFT)) & DMA_TCD_CH7_PRI_APL_MASK)

#define DMA_TCD_CH7_PRI_DPA_MASK                 (0x40000000U)
#define DMA_TCD_CH7_PRI_DPA_SHIFT                (30U)
#define DMA_TCD_CH7_PRI_DPA_WIDTH                (1U)
#define DMA_TCD_CH7_PRI_DPA(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_PRI_DPA_SHIFT)) & DMA_TCD_CH7_PRI_DPA_MASK)

#define DMA_TCD_CH7_PRI_ECP_MASK                 (0x80000000U)
#define DMA_TCD_CH7_PRI_ECP_SHIFT                (31U)
#define DMA_TCD_CH7_PRI_ECP_WIDTH                (1U)
#define DMA_TCD_CH7_PRI_ECP(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH7_PRI_ECP_SHIFT)) & DMA_TCD_CH7_PRI_ECP_MASK)
/*! @} */

/*! @name TCD7_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD7_SADDR_SADDR_MASK            (0xFFFFFFFFU)
#define DMA_TCD_TCD7_SADDR_SADDR_SHIFT           (0U)
#define DMA_TCD_TCD7_SADDR_SADDR_WIDTH           (32U)
#define DMA_TCD_TCD7_SADDR_SADDR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD7_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD7_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD7_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD7_SOFF_SOFF_MASK              (0xFFFFU)
#define DMA_TCD_TCD7_SOFF_SOFF_SHIFT             (0U)
#define DMA_TCD_TCD7_SOFF_SOFF_WIDTH             (16U)
#define DMA_TCD_TCD7_SOFF_SOFF(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD7_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD7_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD7_ATTR_DSIZE_MASK             (0x7U)
#define DMA_TCD_TCD7_ATTR_DSIZE_SHIFT            (0U)
#define DMA_TCD_TCD7_ATTR_DSIZE_WIDTH            (3U)
#define DMA_TCD_TCD7_ATTR_DSIZE(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD7_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD7_ATTR_DMOD_MASK              (0xF8U)
#define DMA_TCD_TCD7_ATTR_DMOD_SHIFT             (3U)
#define DMA_TCD_TCD7_ATTR_DMOD_WIDTH             (5U)
#define DMA_TCD_TCD7_ATTR_DMOD(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD7_ATTR_DMOD_MASK)

#define DMA_TCD_TCD7_ATTR_SSIZE_MASK             (0x700U)
#define DMA_TCD_TCD7_ATTR_SSIZE_SHIFT            (8U)
#define DMA_TCD_TCD7_ATTR_SSIZE_WIDTH            (3U)
#define DMA_TCD_TCD7_ATTR_SSIZE(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD7_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD7_ATTR_SMOD_MASK              (0xF800U)
#define DMA_TCD_TCD7_ATTR_SMOD_SHIFT             (11U)
#define DMA_TCD_TCD7_ATTR_SMOD_WIDTH             (5U)
#define DMA_TCD_TCD7_ATTR_SMOD(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD7_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD7_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD7_NBYTES_MLOFFNO_NBYTES_MASK  (0x3FFFFFFFU)
#define DMA_TCD_TCD7_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD7_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD7_NBYTES_MLOFFNO_NBYTES(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD7_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD7_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD7_NBYTES_MLOFFNO_DMLOE_MASK   (0x40000000U)
#define DMA_TCD_TCD7_NBYTES_MLOFFNO_DMLOE_SHIFT  (30U)
#define DMA_TCD_TCD7_NBYTES_MLOFFNO_DMLOE_WIDTH  (1U)
#define DMA_TCD_TCD7_NBYTES_MLOFFNO_DMLOE(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD7_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD7_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD7_NBYTES_MLOFFNO_SMLOE_MASK   (0x80000000U)
#define DMA_TCD_TCD7_NBYTES_MLOFFNO_SMLOE_SHIFT  (31U)
#define DMA_TCD_TCD7_NBYTES_MLOFFNO_SMLOE_WIDTH  (1U)
#define DMA_TCD_TCD7_NBYTES_MLOFFNO_SMLOE(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD7_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD7_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD7_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD7_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD7_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD7_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD7_NBYTES_MLOFFYES_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD7_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD7_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD7_NBYTES_MLOFFYES_MLOFF_MASK  (0x3FFFFC00U)
#define DMA_TCD_TCD7_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD7_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD7_NBYTES_MLOFFYES_MLOFF(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD7_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD7_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD7_NBYTES_MLOFFYES_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD7_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD7_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD7_NBYTES_MLOFFYES_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD7_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD7_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD7_NBYTES_MLOFFYES_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD7_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD7_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD7_NBYTES_MLOFFYES_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD7_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD7_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD7_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD7_SLAST_SDA_SLAST_SDA_MASK    (0xFFFFFFFFU)
#define DMA_TCD_TCD7_SLAST_SDA_SLAST_SDA_SHIFT   (0U)
#define DMA_TCD_TCD7_SLAST_SDA_SLAST_SDA_WIDTH   (32U)
#define DMA_TCD_TCD7_SLAST_SDA_SLAST_SDA(x)      (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD7_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD7_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD7_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD7_DADDR_DADDR_MASK            (0xFFFFFFFFU)
#define DMA_TCD_TCD7_DADDR_DADDR_SHIFT           (0U)
#define DMA_TCD_TCD7_DADDR_DADDR_WIDTH           (32U)
#define DMA_TCD_TCD7_DADDR_DADDR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD7_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD7_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD7_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD7_DOFF_DOFF_MASK              (0xFFFFU)
#define DMA_TCD_TCD7_DOFF_DOFF_SHIFT             (0U)
#define DMA_TCD_TCD7_DOFF_DOFF_WIDTH             (16U)
#define DMA_TCD_TCD7_DOFF_DOFF(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD7_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD7_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD7_CITER_ELINKNO_CITER_MASK    (0x7FFFU)
#define DMA_TCD_TCD7_CITER_ELINKNO_CITER_SHIFT   (0U)
#define DMA_TCD_TCD7_CITER_ELINKNO_CITER_WIDTH   (15U)
#define DMA_TCD_TCD7_CITER_ELINKNO_CITER(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD7_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD7_CITER_ELINKNO_ELINK_MASK    (0x8000U)
#define DMA_TCD_TCD7_CITER_ELINKNO_ELINK_SHIFT   (15U)
#define DMA_TCD_TCD7_CITER_ELINKNO_ELINK_WIDTH   (1U)
#define DMA_TCD_TCD7_CITER_ELINKNO_ELINK(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD7_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD7_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD7_CITER_ELINKYES_CITER_MASK   (0x1FFU)
#define DMA_TCD_TCD7_CITER_ELINKYES_CITER_SHIFT  (0U)
#define DMA_TCD_TCD7_CITER_ELINKYES_CITER_WIDTH  (9U)
#define DMA_TCD_TCD7_CITER_ELINKYES_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD7_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD7_CITER_ELINKYES_LINKCH_MASK  (0x3E00U)
#define DMA_TCD_TCD7_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD7_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD7_CITER_ELINKYES_LINKCH(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD7_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD7_CITER_ELINKYES_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD7_CITER_ELINKYES_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD7_CITER_ELINKYES_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD7_CITER_ELINKYES_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD7_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD7_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD7_DLAST_SGA_DLAST_SGA_MASK    (0xFFFFFFFFU)
#define DMA_TCD_TCD7_DLAST_SGA_DLAST_SGA_SHIFT   (0U)
#define DMA_TCD_TCD7_DLAST_SGA_DLAST_SGA_WIDTH   (32U)
#define DMA_TCD_TCD7_DLAST_SGA_DLAST_SGA(x)      (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD7_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD7_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD7_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD7_CSR_START_MASK              (0x1U)
#define DMA_TCD_TCD7_CSR_START_SHIFT             (0U)
#define DMA_TCD_TCD7_CSR_START_WIDTH             (1U)
#define DMA_TCD_TCD7_CSR_START(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_CSR_START_SHIFT)) & DMA_TCD_TCD7_CSR_START_MASK)

#define DMA_TCD_TCD7_CSR_INTMAJOR_MASK           (0x2U)
#define DMA_TCD_TCD7_CSR_INTMAJOR_SHIFT          (1U)
#define DMA_TCD_TCD7_CSR_INTMAJOR_WIDTH          (1U)
#define DMA_TCD_TCD7_CSR_INTMAJOR(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD7_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD7_CSR_INTHALF_MASK            (0x4U)
#define DMA_TCD_TCD7_CSR_INTHALF_SHIFT           (2U)
#define DMA_TCD_TCD7_CSR_INTHALF_WIDTH           (1U)
#define DMA_TCD_TCD7_CSR_INTHALF(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD7_CSR_INTHALF_MASK)

#define DMA_TCD_TCD7_CSR_DREQ_MASK               (0x8U)
#define DMA_TCD_TCD7_CSR_DREQ_SHIFT              (3U)
#define DMA_TCD_TCD7_CSR_DREQ_WIDTH              (1U)
#define DMA_TCD_TCD7_CSR_DREQ(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_CSR_DREQ_SHIFT)) & DMA_TCD_TCD7_CSR_DREQ_MASK)

#define DMA_TCD_TCD7_CSR_ESG_MASK                (0x10U)
#define DMA_TCD_TCD7_CSR_ESG_SHIFT               (4U)
#define DMA_TCD_TCD7_CSR_ESG_WIDTH               (1U)
#define DMA_TCD_TCD7_CSR_ESG(x)                  (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_CSR_ESG_SHIFT)) & DMA_TCD_TCD7_CSR_ESG_MASK)

#define DMA_TCD_TCD7_CSR_MAJORELINK_MASK         (0x20U)
#define DMA_TCD_TCD7_CSR_MAJORELINK_SHIFT        (5U)
#define DMA_TCD_TCD7_CSR_MAJORELINK_WIDTH        (1U)
#define DMA_TCD_TCD7_CSR_MAJORELINK(x)           (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD7_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD7_CSR_EEOP_MASK               (0x40U)
#define DMA_TCD_TCD7_CSR_EEOP_SHIFT              (6U)
#define DMA_TCD_TCD7_CSR_EEOP_WIDTH              (1U)
#define DMA_TCD_TCD7_CSR_EEOP(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_CSR_EEOP_SHIFT)) & DMA_TCD_TCD7_CSR_EEOP_MASK)

#define DMA_TCD_TCD7_CSR_ESDA_MASK               (0x80U)
#define DMA_TCD_TCD7_CSR_ESDA_SHIFT              (7U)
#define DMA_TCD_TCD7_CSR_ESDA_WIDTH              (1U)
#define DMA_TCD_TCD7_CSR_ESDA(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_CSR_ESDA_SHIFT)) & DMA_TCD_TCD7_CSR_ESDA_MASK)

#define DMA_TCD_TCD7_CSR_MAJORLINKCH_MASK        (0x1F00U)
#define DMA_TCD_TCD7_CSR_MAJORLINKCH_SHIFT       (8U)
#define DMA_TCD_TCD7_CSR_MAJORLINKCH_WIDTH       (5U)
#define DMA_TCD_TCD7_CSR_MAJORLINKCH(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD7_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD7_CSR_BWC_MASK                (0xC000U)
#define DMA_TCD_TCD7_CSR_BWC_SHIFT               (14U)
#define DMA_TCD_TCD7_CSR_BWC_WIDTH               (2U)
#define DMA_TCD_TCD7_CSR_BWC(x)                  (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_CSR_BWC_SHIFT)) & DMA_TCD_TCD7_CSR_BWC_MASK)
/*! @} */

/*! @name TCD7_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD7_BITER_ELINKNO_BITER_MASK    (0x7FFFU)
#define DMA_TCD_TCD7_BITER_ELINKNO_BITER_SHIFT   (0U)
#define DMA_TCD_TCD7_BITER_ELINKNO_BITER_WIDTH   (15U)
#define DMA_TCD_TCD7_BITER_ELINKNO_BITER(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD7_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD7_BITER_ELINKNO_ELINK_MASK    (0x8000U)
#define DMA_TCD_TCD7_BITER_ELINKNO_ELINK_SHIFT   (15U)
#define DMA_TCD_TCD7_BITER_ELINKNO_ELINK_WIDTH   (1U)
#define DMA_TCD_TCD7_BITER_ELINKNO_ELINK(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD7_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD7_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD7_BITER_ELINKYES_BITER_MASK   (0x1FFU)
#define DMA_TCD_TCD7_BITER_ELINKYES_BITER_SHIFT  (0U)
#define DMA_TCD_TCD7_BITER_ELINKYES_BITER_WIDTH  (9U)
#define DMA_TCD_TCD7_BITER_ELINKYES_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD7_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD7_BITER_ELINKYES_LINKCH_MASK  (0x3E00U)
#define DMA_TCD_TCD7_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD7_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD7_BITER_ELINKYES_LINKCH(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD7_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD7_BITER_ELINKYES_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD7_BITER_ELINKYES_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD7_BITER_ELINKYES_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD7_BITER_ELINKYES_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD7_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD7_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH8_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH8_CSR_ERQ_MASK                 (0x1U)
#define DMA_TCD_CH8_CSR_ERQ_SHIFT                (0U)
#define DMA_TCD_CH8_CSR_ERQ_WIDTH                (1U)
#define DMA_TCD_CH8_CSR_ERQ(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_CSR_ERQ_SHIFT)) & DMA_TCD_CH8_CSR_ERQ_MASK)

#define DMA_TCD_CH8_CSR_EARQ_MASK                (0x2U)
#define DMA_TCD_CH8_CSR_EARQ_SHIFT               (1U)
#define DMA_TCD_CH8_CSR_EARQ_WIDTH               (1U)
#define DMA_TCD_CH8_CSR_EARQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_CSR_EARQ_SHIFT)) & DMA_TCD_CH8_CSR_EARQ_MASK)

#define DMA_TCD_CH8_CSR_EEI_MASK                 (0x4U)
#define DMA_TCD_CH8_CSR_EEI_SHIFT                (2U)
#define DMA_TCD_CH8_CSR_EEI_WIDTH                (1U)
#define DMA_TCD_CH8_CSR_EEI(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_CSR_EEI_SHIFT)) & DMA_TCD_CH8_CSR_EEI_MASK)

#define DMA_TCD_CH8_CSR_EBW_MASK                 (0x8U)
#define DMA_TCD_CH8_CSR_EBW_SHIFT                (3U)
#define DMA_TCD_CH8_CSR_EBW_WIDTH                (1U)
#define DMA_TCD_CH8_CSR_EBW(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_CSR_EBW_SHIFT)) & DMA_TCD_CH8_CSR_EBW_MASK)

#define DMA_TCD_CH8_CSR_DONE_MASK                (0x40000000U)
#define DMA_TCD_CH8_CSR_DONE_SHIFT               (30U)
#define DMA_TCD_CH8_CSR_DONE_WIDTH               (1U)
#define DMA_TCD_CH8_CSR_DONE(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_CSR_DONE_SHIFT)) & DMA_TCD_CH8_CSR_DONE_MASK)

#define DMA_TCD_CH8_CSR_ACTIVE_MASK              (0x80000000U)
#define DMA_TCD_CH8_CSR_ACTIVE_SHIFT             (31U)
#define DMA_TCD_CH8_CSR_ACTIVE_WIDTH             (1U)
#define DMA_TCD_CH8_CSR_ACTIVE(x)                (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH8_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH8_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH8_ES_DBE_MASK                  (0x1U)
#define DMA_TCD_CH8_ES_DBE_SHIFT                 (0U)
#define DMA_TCD_CH8_ES_DBE_WIDTH                 (1U)
#define DMA_TCD_CH8_ES_DBE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_ES_DBE_SHIFT)) & DMA_TCD_CH8_ES_DBE_MASK)

#define DMA_TCD_CH8_ES_SBE_MASK                  (0x2U)
#define DMA_TCD_CH8_ES_SBE_SHIFT                 (1U)
#define DMA_TCD_CH8_ES_SBE_WIDTH                 (1U)
#define DMA_TCD_CH8_ES_SBE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_ES_SBE_SHIFT)) & DMA_TCD_CH8_ES_SBE_MASK)

#define DMA_TCD_CH8_ES_SGE_MASK                  (0x4U)
#define DMA_TCD_CH8_ES_SGE_SHIFT                 (2U)
#define DMA_TCD_CH8_ES_SGE_WIDTH                 (1U)
#define DMA_TCD_CH8_ES_SGE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_ES_SGE_SHIFT)) & DMA_TCD_CH8_ES_SGE_MASK)

#define DMA_TCD_CH8_ES_NCE_MASK                  (0x8U)
#define DMA_TCD_CH8_ES_NCE_SHIFT                 (3U)
#define DMA_TCD_CH8_ES_NCE_WIDTH                 (1U)
#define DMA_TCD_CH8_ES_NCE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_ES_NCE_SHIFT)) & DMA_TCD_CH8_ES_NCE_MASK)

#define DMA_TCD_CH8_ES_DOE_MASK                  (0x10U)
#define DMA_TCD_CH8_ES_DOE_SHIFT                 (4U)
#define DMA_TCD_CH8_ES_DOE_WIDTH                 (1U)
#define DMA_TCD_CH8_ES_DOE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_ES_DOE_SHIFT)) & DMA_TCD_CH8_ES_DOE_MASK)

#define DMA_TCD_CH8_ES_DAE_MASK                  (0x20U)
#define DMA_TCD_CH8_ES_DAE_SHIFT                 (5U)
#define DMA_TCD_CH8_ES_DAE_WIDTH                 (1U)
#define DMA_TCD_CH8_ES_DAE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_ES_DAE_SHIFT)) & DMA_TCD_CH8_ES_DAE_MASK)

#define DMA_TCD_CH8_ES_SOE_MASK                  (0x40U)
#define DMA_TCD_CH8_ES_SOE_SHIFT                 (6U)
#define DMA_TCD_CH8_ES_SOE_WIDTH                 (1U)
#define DMA_TCD_CH8_ES_SOE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_ES_SOE_SHIFT)) & DMA_TCD_CH8_ES_SOE_MASK)

#define DMA_TCD_CH8_ES_SAE_MASK                  (0x80U)
#define DMA_TCD_CH8_ES_SAE_SHIFT                 (7U)
#define DMA_TCD_CH8_ES_SAE_WIDTH                 (1U)
#define DMA_TCD_CH8_ES_SAE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_ES_SAE_SHIFT)) & DMA_TCD_CH8_ES_SAE_MASK)

#define DMA_TCD_CH8_ES_ERR_MASK                  (0x80000000U)
#define DMA_TCD_CH8_ES_ERR_SHIFT                 (31U)
#define DMA_TCD_CH8_ES_ERR_WIDTH                 (1U)
#define DMA_TCD_CH8_ES_ERR(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_ES_ERR_SHIFT)) & DMA_TCD_CH8_ES_ERR_MASK)
/*! @} */

/*! @name CH8_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH8_INT_INT_MASK                 (0x1U)
#define DMA_TCD_CH8_INT_INT_SHIFT                (0U)
#define DMA_TCD_CH8_INT_INT_WIDTH                (1U)
#define DMA_TCD_CH8_INT_INT(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_INT_INT_SHIFT)) & DMA_TCD_CH8_INT_INT_MASK)
/*! @} */

/*! @name CH8_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH8_SBR_MID_MASK                 (0xFU)
#define DMA_TCD_CH8_SBR_MID_SHIFT                (0U)
#define DMA_TCD_CH8_SBR_MID_WIDTH                (4U)
#define DMA_TCD_CH8_SBR_MID(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_SBR_MID_SHIFT)) & DMA_TCD_CH8_SBR_MID_MASK)

#define DMA_TCD_CH8_SBR_PAL_MASK                 (0x8000U)
#define DMA_TCD_CH8_SBR_PAL_SHIFT                (15U)
#define DMA_TCD_CH8_SBR_PAL_WIDTH                (1U)
#define DMA_TCD_CH8_SBR_PAL(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_SBR_PAL_SHIFT)) & DMA_TCD_CH8_SBR_PAL_MASK)

#define DMA_TCD_CH8_SBR_EMI_MASK                 (0x10000U)
#define DMA_TCD_CH8_SBR_EMI_SHIFT                (16U)
#define DMA_TCD_CH8_SBR_EMI_WIDTH                (1U)
#define DMA_TCD_CH8_SBR_EMI(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_SBR_EMI_SHIFT)) & DMA_TCD_CH8_SBR_EMI_MASK)

#define DMA_TCD_CH8_SBR_ATTR_MASK                (0xE0000U)
#define DMA_TCD_CH8_SBR_ATTR_SHIFT               (17U)
#define DMA_TCD_CH8_SBR_ATTR_WIDTH               (3U)
#define DMA_TCD_CH8_SBR_ATTR(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_SBR_ATTR_SHIFT)) & DMA_TCD_CH8_SBR_ATTR_MASK)
/*! @} */

/*! @name CH8_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH8_PRI_APL_MASK                 (0x7U)
#define DMA_TCD_CH8_PRI_APL_SHIFT                (0U)
#define DMA_TCD_CH8_PRI_APL_WIDTH                (3U)
#define DMA_TCD_CH8_PRI_APL(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_PRI_APL_SHIFT)) & DMA_TCD_CH8_PRI_APL_MASK)

#define DMA_TCD_CH8_PRI_DPA_MASK                 (0x40000000U)
#define DMA_TCD_CH8_PRI_DPA_SHIFT                (30U)
#define DMA_TCD_CH8_PRI_DPA_WIDTH                (1U)
#define DMA_TCD_CH8_PRI_DPA(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_PRI_DPA_SHIFT)) & DMA_TCD_CH8_PRI_DPA_MASK)

#define DMA_TCD_CH8_PRI_ECP_MASK                 (0x80000000U)
#define DMA_TCD_CH8_PRI_ECP_SHIFT                (31U)
#define DMA_TCD_CH8_PRI_ECP_WIDTH                (1U)
#define DMA_TCD_CH8_PRI_ECP(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH8_PRI_ECP_SHIFT)) & DMA_TCD_CH8_PRI_ECP_MASK)
/*! @} */

/*! @name TCD8_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD8_SADDR_SADDR_MASK            (0xFFFFFFFFU)
#define DMA_TCD_TCD8_SADDR_SADDR_SHIFT           (0U)
#define DMA_TCD_TCD8_SADDR_SADDR_WIDTH           (32U)
#define DMA_TCD_TCD8_SADDR_SADDR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD8_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD8_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD8_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD8_SOFF_SOFF_MASK              (0xFFFFU)
#define DMA_TCD_TCD8_SOFF_SOFF_SHIFT             (0U)
#define DMA_TCD_TCD8_SOFF_SOFF_WIDTH             (16U)
#define DMA_TCD_TCD8_SOFF_SOFF(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD8_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD8_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD8_ATTR_DSIZE_MASK             (0x7U)
#define DMA_TCD_TCD8_ATTR_DSIZE_SHIFT            (0U)
#define DMA_TCD_TCD8_ATTR_DSIZE_WIDTH            (3U)
#define DMA_TCD_TCD8_ATTR_DSIZE(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD8_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD8_ATTR_DMOD_MASK              (0xF8U)
#define DMA_TCD_TCD8_ATTR_DMOD_SHIFT             (3U)
#define DMA_TCD_TCD8_ATTR_DMOD_WIDTH             (5U)
#define DMA_TCD_TCD8_ATTR_DMOD(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD8_ATTR_DMOD_MASK)

#define DMA_TCD_TCD8_ATTR_SSIZE_MASK             (0x700U)
#define DMA_TCD_TCD8_ATTR_SSIZE_SHIFT            (8U)
#define DMA_TCD_TCD8_ATTR_SSIZE_WIDTH            (3U)
#define DMA_TCD_TCD8_ATTR_SSIZE(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD8_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD8_ATTR_SMOD_MASK              (0xF800U)
#define DMA_TCD_TCD8_ATTR_SMOD_SHIFT             (11U)
#define DMA_TCD_TCD8_ATTR_SMOD_WIDTH             (5U)
#define DMA_TCD_TCD8_ATTR_SMOD(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD8_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD8_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD8_NBYTES_MLOFFNO_NBYTES_MASK  (0x3FFFFFFFU)
#define DMA_TCD_TCD8_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD8_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD8_NBYTES_MLOFFNO_NBYTES(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD8_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD8_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD8_NBYTES_MLOFFNO_DMLOE_MASK   (0x40000000U)
#define DMA_TCD_TCD8_NBYTES_MLOFFNO_DMLOE_SHIFT  (30U)
#define DMA_TCD_TCD8_NBYTES_MLOFFNO_DMLOE_WIDTH  (1U)
#define DMA_TCD_TCD8_NBYTES_MLOFFNO_DMLOE(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD8_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD8_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD8_NBYTES_MLOFFNO_SMLOE_MASK   (0x80000000U)
#define DMA_TCD_TCD8_NBYTES_MLOFFNO_SMLOE_SHIFT  (31U)
#define DMA_TCD_TCD8_NBYTES_MLOFFNO_SMLOE_WIDTH  (1U)
#define DMA_TCD_TCD8_NBYTES_MLOFFNO_SMLOE(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD8_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD8_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD8_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD8_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD8_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD8_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD8_NBYTES_MLOFFYES_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD8_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD8_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD8_NBYTES_MLOFFYES_MLOFF_MASK  (0x3FFFFC00U)
#define DMA_TCD_TCD8_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD8_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD8_NBYTES_MLOFFYES_MLOFF(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD8_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD8_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD8_NBYTES_MLOFFYES_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD8_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD8_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD8_NBYTES_MLOFFYES_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD8_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD8_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD8_NBYTES_MLOFFYES_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD8_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD8_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD8_NBYTES_MLOFFYES_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD8_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD8_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD8_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD8_SLAST_SDA_SLAST_SDA_MASK    (0xFFFFFFFFU)
#define DMA_TCD_TCD8_SLAST_SDA_SLAST_SDA_SHIFT   (0U)
#define DMA_TCD_TCD8_SLAST_SDA_SLAST_SDA_WIDTH   (32U)
#define DMA_TCD_TCD8_SLAST_SDA_SLAST_SDA(x)      (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD8_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD8_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD8_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD8_DADDR_DADDR_MASK            (0xFFFFFFFFU)
#define DMA_TCD_TCD8_DADDR_DADDR_SHIFT           (0U)
#define DMA_TCD_TCD8_DADDR_DADDR_WIDTH           (32U)
#define DMA_TCD_TCD8_DADDR_DADDR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD8_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD8_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD8_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD8_DOFF_DOFF_MASK              (0xFFFFU)
#define DMA_TCD_TCD8_DOFF_DOFF_SHIFT             (0U)
#define DMA_TCD_TCD8_DOFF_DOFF_WIDTH             (16U)
#define DMA_TCD_TCD8_DOFF_DOFF(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD8_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD8_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD8_CITER_ELINKNO_CITER_MASK    (0x7FFFU)
#define DMA_TCD_TCD8_CITER_ELINKNO_CITER_SHIFT   (0U)
#define DMA_TCD_TCD8_CITER_ELINKNO_CITER_WIDTH   (15U)
#define DMA_TCD_TCD8_CITER_ELINKNO_CITER(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD8_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD8_CITER_ELINKNO_ELINK_MASK    (0x8000U)
#define DMA_TCD_TCD8_CITER_ELINKNO_ELINK_SHIFT   (15U)
#define DMA_TCD_TCD8_CITER_ELINKNO_ELINK_WIDTH   (1U)
#define DMA_TCD_TCD8_CITER_ELINKNO_ELINK(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD8_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD8_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD8_CITER_ELINKYES_CITER_MASK   (0x1FFU)
#define DMA_TCD_TCD8_CITER_ELINKYES_CITER_SHIFT  (0U)
#define DMA_TCD_TCD8_CITER_ELINKYES_CITER_WIDTH  (9U)
#define DMA_TCD_TCD8_CITER_ELINKYES_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD8_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD8_CITER_ELINKYES_LINKCH_MASK  (0x3E00U)
#define DMA_TCD_TCD8_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD8_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD8_CITER_ELINKYES_LINKCH(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD8_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD8_CITER_ELINKYES_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD8_CITER_ELINKYES_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD8_CITER_ELINKYES_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD8_CITER_ELINKYES_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD8_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD8_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD8_DLAST_SGA_DLAST_SGA_MASK    (0xFFFFFFFFU)
#define DMA_TCD_TCD8_DLAST_SGA_DLAST_SGA_SHIFT   (0U)
#define DMA_TCD_TCD8_DLAST_SGA_DLAST_SGA_WIDTH   (32U)
#define DMA_TCD_TCD8_DLAST_SGA_DLAST_SGA(x)      (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD8_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD8_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD8_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD8_CSR_START_MASK              (0x1U)
#define DMA_TCD_TCD8_CSR_START_SHIFT             (0U)
#define DMA_TCD_TCD8_CSR_START_WIDTH             (1U)
#define DMA_TCD_TCD8_CSR_START(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_CSR_START_SHIFT)) & DMA_TCD_TCD8_CSR_START_MASK)

#define DMA_TCD_TCD8_CSR_INTMAJOR_MASK           (0x2U)
#define DMA_TCD_TCD8_CSR_INTMAJOR_SHIFT          (1U)
#define DMA_TCD_TCD8_CSR_INTMAJOR_WIDTH          (1U)
#define DMA_TCD_TCD8_CSR_INTMAJOR(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD8_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD8_CSR_INTHALF_MASK            (0x4U)
#define DMA_TCD_TCD8_CSR_INTHALF_SHIFT           (2U)
#define DMA_TCD_TCD8_CSR_INTHALF_WIDTH           (1U)
#define DMA_TCD_TCD8_CSR_INTHALF(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD8_CSR_INTHALF_MASK)

#define DMA_TCD_TCD8_CSR_DREQ_MASK               (0x8U)
#define DMA_TCD_TCD8_CSR_DREQ_SHIFT              (3U)
#define DMA_TCD_TCD8_CSR_DREQ_WIDTH              (1U)
#define DMA_TCD_TCD8_CSR_DREQ(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_CSR_DREQ_SHIFT)) & DMA_TCD_TCD8_CSR_DREQ_MASK)

#define DMA_TCD_TCD8_CSR_ESG_MASK                (0x10U)
#define DMA_TCD_TCD8_CSR_ESG_SHIFT               (4U)
#define DMA_TCD_TCD8_CSR_ESG_WIDTH               (1U)
#define DMA_TCD_TCD8_CSR_ESG(x)                  (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_CSR_ESG_SHIFT)) & DMA_TCD_TCD8_CSR_ESG_MASK)

#define DMA_TCD_TCD8_CSR_MAJORELINK_MASK         (0x20U)
#define DMA_TCD_TCD8_CSR_MAJORELINK_SHIFT        (5U)
#define DMA_TCD_TCD8_CSR_MAJORELINK_WIDTH        (1U)
#define DMA_TCD_TCD8_CSR_MAJORELINK(x)           (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD8_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD8_CSR_EEOP_MASK               (0x40U)
#define DMA_TCD_TCD8_CSR_EEOP_SHIFT              (6U)
#define DMA_TCD_TCD8_CSR_EEOP_WIDTH              (1U)
#define DMA_TCD_TCD8_CSR_EEOP(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_CSR_EEOP_SHIFT)) & DMA_TCD_TCD8_CSR_EEOP_MASK)

#define DMA_TCD_TCD8_CSR_ESDA_MASK               (0x80U)
#define DMA_TCD_TCD8_CSR_ESDA_SHIFT              (7U)
#define DMA_TCD_TCD8_CSR_ESDA_WIDTH              (1U)
#define DMA_TCD_TCD8_CSR_ESDA(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_CSR_ESDA_SHIFT)) & DMA_TCD_TCD8_CSR_ESDA_MASK)

#define DMA_TCD_TCD8_CSR_MAJORLINKCH_MASK        (0x1F00U)
#define DMA_TCD_TCD8_CSR_MAJORLINKCH_SHIFT       (8U)
#define DMA_TCD_TCD8_CSR_MAJORLINKCH_WIDTH       (5U)
#define DMA_TCD_TCD8_CSR_MAJORLINKCH(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD8_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD8_CSR_BWC_MASK                (0xC000U)
#define DMA_TCD_TCD8_CSR_BWC_SHIFT               (14U)
#define DMA_TCD_TCD8_CSR_BWC_WIDTH               (2U)
#define DMA_TCD_TCD8_CSR_BWC(x)                  (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_CSR_BWC_SHIFT)) & DMA_TCD_TCD8_CSR_BWC_MASK)
/*! @} */

/*! @name TCD8_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD8_BITER_ELINKNO_BITER_MASK    (0x7FFFU)
#define DMA_TCD_TCD8_BITER_ELINKNO_BITER_SHIFT   (0U)
#define DMA_TCD_TCD8_BITER_ELINKNO_BITER_WIDTH   (15U)
#define DMA_TCD_TCD8_BITER_ELINKNO_BITER(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD8_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD8_BITER_ELINKNO_ELINK_MASK    (0x8000U)
#define DMA_TCD_TCD8_BITER_ELINKNO_ELINK_SHIFT   (15U)
#define DMA_TCD_TCD8_BITER_ELINKNO_ELINK_WIDTH   (1U)
#define DMA_TCD_TCD8_BITER_ELINKNO_ELINK(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD8_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD8_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD8_BITER_ELINKYES_BITER_MASK   (0x1FFU)
#define DMA_TCD_TCD8_BITER_ELINKYES_BITER_SHIFT  (0U)
#define DMA_TCD_TCD8_BITER_ELINKYES_BITER_WIDTH  (9U)
#define DMA_TCD_TCD8_BITER_ELINKYES_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD8_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD8_BITER_ELINKYES_LINKCH_MASK  (0x3E00U)
#define DMA_TCD_TCD8_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD8_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD8_BITER_ELINKYES_LINKCH(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD8_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD8_BITER_ELINKYES_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD8_BITER_ELINKYES_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD8_BITER_ELINKYES_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD8_BITER_ELINKYES_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD8_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD8_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH9_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH9_CSR_ERQ_MASK                 (0x1U)
#define DMA_TCD_CH9_CSR_ERQ_SHIFT                (0U)
#define DMA_TCD_CH9_CSR_ERQ_WIDTH                (1U)
#define DMA_TCD_CH9_CSR_ERQ(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_CSR_ERQ_SHIFT)) & DMA_TCD_CH9_CSR_ERQ_MASK)

#define DMA_TCD_CH9_CSR_EARQ_MASK                (0x2U)
#define DMA_TCD_CH9_CSR_EARQ_SHIFT               (1U)
#define DMA_TCD_CH9_CSR_EARQ_WIDTH               (1U)
#define DMA_TCD_CH9_CSR_EARQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_CSR_EARQ_SHIFT)) & DMA_TCD_CH9_CSR_EARQ_MASK)

#define DMA_TCD_CH9_CSR_EEI_MASK                 (0x4U)
#define DMA_TCD_CH9_CSR_EEI_SHIFT                (2U)
#define DMA_TCD_CH9_CSR_EEI_WIDTH                (1U)
#define DMA_TCD_CH9_CSR_EEI(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_CSR_EEI_SHIFT)) & DMA_TCD_CH9_CSR_EEI_MASK)

#define DMA_TCD_CH9_CSR_EBW_MASK                 (0x8U)
#define DMA_TCD_CH9_CSR_EBW_SHIFT                (3U)
#define DMA_TCD_CH9_CSR_EBW_WIDTH                (1U)
#define DMA_TCD_CH9_CSR_EBW(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_CSR_EBW_SHIFT)) & DMA_TCD_CH9_CSR_EBW_MASK)

#define DMA_TCD_CH9_CSR_DONE_MASK                (0x40000000U)
#define DMA_TCD_CH9_CSR_DONE_SHIFT               (30U)
#define DMA_TCD_CH9_CSR_DONE_WIDTH               (1U)
#define DMA_TCD_CH9_CSR_DONE(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_CSR_DONE_SHIFT)) & DMA_TCD_CH9_CSR_DONE_MASK)

#define DMA_TCD_CH9_CSR_ACTIVE_MASK              (0x80000000U)
#define DMA_TCD_CH9_CSR_ACTIVE_SHIFT             (31U)
#define DMA_TCD_CH9_CSR_ACTIVE_WIDTH             (1U)
#define DMA_TCD_CH9_CSR_ACTIVE(x)                (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH9_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH9_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH9_ES_DBE_MASK                  (0x1U)
#define DMA_TCD_CH9_ES_DBE_SHIFT                 (0U)
#define DMA_TCD_CH9_ES_DBE_WIDTH                 (1U)
#define DMA_TCD_CH9_ES_DBE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_ES_DBE_SHIFT)) & DMA_TCD_CH9_ES_DBE_MASK)

#define DMA_TCD_CH9_ES_SBE_MASK                  (0x2U)
#define DMA_TCD_CH9_ES_SBE_SHIFT                 (1U)
#define DMA_TCD_CH9_ES_SBE_WIDTH                 (1U)
#define DMA_TCD_CH9_ES_SBE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_ES_SBE_SHIFT)) & DMA_TCD_CH9_ES_SBE_MASK)

#define DMA_TCD_CH9_ES_SGE_MASK                  (0x4U)
#define DMA_TCD_CH9_ES_SGE_SHIFT                 (2U)
#define DMA_TCD_CH9_ES_SGE_WIDTH                 (1U)
#define DMA_TCD_CH9_ES_SGE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_ES_SGE_SHIFT)) & DMA_TCD_CH9_ES_SGE_MASK)

#define DMA_TCD_CH9_ES_NCE_MASK                  (0x8U)
#define DMA_TCD_CH9_ES_NCE_SHIFT                 (3U)
#define DMA_TCD_CH9_ES_NCE_WIDTH                 (1U)
#define DMA_TCD_CH9_ES_NCE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_ES_NCE_SHIFT)) & DMA_TCD_CH9_ES_NCE_MASK)

#define DMA_TCD_CH9_ES_DOE_MASK                  (0x10U)
#define DMA_TCD_CH9_ES_DOE_SHIFT                 (4U)
#define DMA_TCD_CH9_ES_DOE_WIDTH                 (1U)
#define DMA_TCD_CH9_ES_DOE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_ES_DOE_SHIFT)) & DMA_TCD_CH9_ES_DOE_MASK)

#define DMA_TCD_CH9_ES_DAE_MASK                  (0x20U)
#define DMA_TCD_CH9_ES_DAE_SHIFT                 (5U)
#define DMA_TCD_CH9_ES_DAE_WIDTH                 (1U)
#define DMA_TCD_CH9_ES_DAE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_ES_DAE_SHIFT)) & DMA_TCD_CH9_ES_DAE_MASK)

#define DMA_TCD_CH9_ES_SOE_MASK                  (0x40U)
#define DMA_TCD_CH9_ES_SOE_SHIFT                 (6U)
#define DMA_TCD_CH9_ES_SOE_WIDTH                 (1U)
#define DMA_TCD_CH9_ES_SOE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_ES_SOE_SHIFT)) & DMA_TCD_CH9_ES_SOE_MASK)

#define DMA_TCD_CH9_ES_SAE_MASK                  (0x80U)
#define DMA_TCD_CH9_ES_SAE_SHIFT                 (7U)
#define DMA_TCD_CH9_ES_SAE_WIDTH                 (1U)
#define DMA_TCD_CH9_ES_SAE(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_ES_SAE_SHIFT)) & DMA_TCD_CH9_ES_SAE_MASK)

#define DMA_TCD_CH9_ES_ERR_MASK                  (0x80000000U)
#define DMA_TCD_CH9_ES_ERR_SHIFT                 (31U)
#define DMA_TCD_CH9_ES_ERR_WIDTH                 (1U)
#define DMA_TCD_CH9_ES_ERR(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_ES_ERR_SHIFT)) & DMA_TCD_CH9_ES_ERR_MASK)
/*! @} */

/*! @name CH9_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH9_INT_INT_MASK                 (0x1U)
#define DMA_TCD_CH9_INT_INT_SHIFT                (0U)
#define DMA_TCD_CH9_INT_INT_WIDTH                (1U)
#define DMA_TCD_CH9_INT_INT(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_INT_INT_SHIFT)) & DMA_TCD_CH9_INT_INT_MASK)
/*! @} */

/*! @name CH9_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH9_SBR_MID_MASK                 (0xFU)
#define DMA_TCD_CH9_SBR_MID_SHIFT                (0U)
#define DMA_TCD_CH9_SBR_MID_WIDTH                (4U)
#define DMA_TCD_CH9_SBR_MID(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_SBR_MID_SHIFT)) & DMA_TCD_CH9_SBR_MID_MASK)

#define DMA_TCD_CH9_SBR_PAL_MASK                 (0x8000U)
#define DMA_TCD_CH9_SBR_PAL_SHIFT                (15U)
#define DMA_TCD_CH9_SBR_PAL_WIDTH                (1U)
#define DMA_TCD_CH9_SBR_PAL(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_SBR_PAL_SHIFT)) & DMA_TCD_CH9_SBR_PAL_MASK)

#define DMA_TCD_CH9_SBR_EMI_MASK                 (0x10000U)
#define DMA_TCD_CH9_SBR_EMI_SHIFT                (16U)
#define DMA_TCD_CH9_SBR_EMI_WIDTH                (1U)
#define DMA_TCD_CH9_SBR_EMI(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_SBR_EMI_SHIFT)) & DMA_TCD_CH9_SBR_EMI_MASK)

#define DMA_TCD_CH9_SBR_ATTR_MASK                (0xE0000U)
#define DMA_TCD_CH9_SBR_ATTR_SHIFT               (17U)
#define DMA_TCD_CH9_SBR_ATTR_WIDTH               (3U)
#define DMA_TCD_CH9_SBR_ATTR(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_SBR_ATTR_SHIFT)) & DMA_TCD_CH9_SBR_ATTR_MASK)
/*! @} */

/*! @name CH9_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH9_PRI_APL_MASK                 (0x7U)
#define DMA_TCD_CH9_PRI_APL_SHIFT                (0U)
#define DMA_TCD_CH9_PRI_APL_WIDTH                (3U)
#define DMA_TCD_CH9_PRI_APL(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_PRI_APL_SHIFT)) & DMA_TCD_CH9_PRI_APL_MASK)

#define DMA_TCD_CH9_PRI_DPA_MASK                 (0x40000000U)
#define DMA_TCD_CH9_PRI_DPA_SHIFT                (30U)
#define DMA_TCD_CH9_PRI_DPA_WIDTH                (1U)
#define DMA_TCD_CH9_PRI_DPA(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_PRI_DPA_SHIFT)) & DMA_TCD_CH9_PRI_DPA_MASK)

#define DMA_TCD_CH9_PRI_ECP_MASK                 (0x80000000U)
#define DMA_TCD_CH9_PRI_ECP_SHIFT                (31U)
#define DMA_TCD_CH9_PRI_ECP_WIDTH                (1U)
#define DMA_TCD_CH9_PRI_ECP(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH9_PRI_ECP_SHIFT)) & DMA_TCD_CH9_PRI_ECP_MASK)
/*! @} */

/*! @name TCD9_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD9_SADDR_SADDR_MASK            (0xFFFFFFFFU)
#define DMA_TCD_TCD9_SADDR_SADDR_SHIFT           (0U)
#define DMA_TCD_TCD9_SADDR_SADDR_WIDTH           (32U)
#define DMA_TCD_TCD9_SADDR_SADDR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD9_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD9_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD9_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD9_SOFF_SOFF_MASK              (0xFFFFU)
#define DMA_TCD_TCD9_SOFF_SOFF_SHIFT             (0U)
#define DMA_TCD_TCD9_SOFF_SOFF_WIDTH             (16U)
#define DMA_TCD_TCD9_SOFF_SOFF(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD9_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD9_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD9_ATTR_DSIZE_MASK             (0x7U)
#define DMA_TCD_TCD9_ATTR_DSIZE_SHIFT            (0U)
#define DMA_TCD_TCD9_ATTR_DSIZE_WIDTH            (3U)
#define DMA_TCD_TCD9_ATTR_DSIZE(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD9_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD9_ATTR_DMOD_MASK              (0xF8U)
#define DMA_TCD_TCD9_ATTR_DMOD_SHIFT             (3U)
#define DMA_TCD_TCD9_ATTR_DMOD_WIDTH             (5U)
#define DMA_TCD_TCD9_ATTR_DMOD(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD9_ATTR_DMOD_MASK)

#define DMA_TCD_TCD9_ATTR_SSIZE_MASK             (0x700U)
#define DMA_TCD_TCD9_ATTR_SSIZE_SHIFT            (8U)
#define DMA_TCD_TCD9_ATTR_SSIZE_WIDTH            (3U)
#define DMA_TCD_TCD9_ATTR_SSIZE(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD9_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD9_ATTR_SMOD_MASK              (0xF800U)
#define DMA_TCD_TCD9_ATTR_SMOD_SHIFT             (11U)
#define DMA_TCD_TCD9_ATTR_SMOD_WIDTH             (5U)
#define DMA_TCD_TCD9_ATTR_SMOD(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD9_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD9_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD9_NBYTES_MLOFFNO_NBYTES_MASK  (0x3FFFFFFFU)
#define DMA_TCD_TCD9_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD9_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD9_NBYTES_MLOFFNO_NBYTES(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD9_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD9_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD9_NBYTES_MLOFFNO_DMLOE_MASK   (0x40000000U)
#define DMA_TCD_TCD9_NBYTES_MLOFFNO_DMLOE_SHIFT  (30U)
#define DMA_TCD_TCD9_NBYTES_MLOFFNO_DMLOE_WIDTH  (1U)
#define DMA_TCD_TCD9_NBYTES_MLOFFNO_DMLOE(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD9_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD9_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD9_NBYTES_MLOFFNO_SMLOE_MASK   (0x80000000U)
#define DMA_TCD_TCD9_NBYTES_MLOFFNO_SMLOE_SHIFT  (31U)
#define DMA_TCD_TCD9_NBYTES_MLOFFNO_SMLOE_WIDTH  (1U)
#define DMA_TCD_TCD9_NBYTES_MLOFFNO_SMLOE(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD9_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD9_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD9_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD9_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD9_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD9_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD9_NBYTES_MLOFFYES_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD9_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD9_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD9_NBYTES_MLOFFYES_MLOFF_MASK  (0x3FFFFC00U)
#define DMA_TCD_TCD9_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD9_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD9_NBYTES_MLOFFYES_MLOFF(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD9_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD9_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD9_NBYTES_MLOFFYES_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD9_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD9_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD9_NBYTES_MLOFFYES_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD9_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD9_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD9_NBYTES_MLOFFYES_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD9_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD9_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD9_NBYTES_MLOFFYES_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD9_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD9_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD9_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD9_SLAST_SDA_SLAST_SDA_MASK    (0xFFFFFFFFU)
#define DMA_TCD_TCD9_SLAST_SDA_SLAST_SDA_SHIFT   (0U)
#define DMA_TCD_TCD9_SLAST_SDA_SLAST_SDA_WIDTH   (32U)
#define DMA_TCD_TCD9_SLAST_SDA_SLAST_SDA(x)      (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD9_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD9_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD9_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD9_DADDR_DADDR_MASK            (0xFFFFFFFFU)
#define DMA_TCD_TCD9_DADDR_DADDR_SHIFT           (0U)
#define DMA_TCD_TCD9_DADDR_DADDR_WIDTH           (32U)
#define DMA_TCD_TCD9_DADDR_DADDR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD9_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD9_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD9_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD9_DOFF_DOFF_MASK              (0xFFFFU)
#define DMA_TCD_TCD9_DOFF_DOFF_SHIFT             (0U)
#define DMA_TCD_TCD9_DOFF_DOFF_WIDTH             (16U)
#define DMA_TCD_TCD9_DOFF_DOFF(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD9_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD9_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD9_CITER_ELINKNO_CITER_MASK    (0x7FFFU)
#define DMA_TCD_TCD9_CITER_ELINKNO_CITER_SHIFT   (0U)
#define DMA_TCD_TCD9_CITER_ELINKNO_CITER_WIDTH   (15U)
#define DMA_TCD_TCD9_CITER_ELINKNO_CITER(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD9_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD9_CITER_ELINKNO_ELINK_MASK    (0x8000U)
#define DMA_TCD_TCD9_CITER_ELINKNO_ELINK_SHIFT   (15U)
#define DMA_TCD_TCD9_CITER_ELINKNO_ELINK_WIDTH   (1U)
#define DMA_TCD_TCD9_CITER_ELINKNO_ELINK(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD9_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD9_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD9_CITER_ELINKYES_CITER_MASK   (0x1FFU)
#define DMA_TCD_TCD9_CITER_ELINKYES_CITER_SHIFT  (0U)
#define DMA_TCD_TCD9_CITER_ELINKYES_CITER_WIDTH  (9U)
#define DMA_TCD_TCD9_CITER_ELINKYES_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD9_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD9_CITER_ELINKYES_LINKCH_MASK  (0x3E00U)
#define DMA_TCD_TCD9_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD9_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD9_CITER_ELINKYES_LINKCH(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD9_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD9_CITER_ELINKYES_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD9_CITER_ELINKYES_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD9_CITER_ELINKYES_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD9_CITER_ELINKYES_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD9_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD9_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD9_DLAST_SGA_DLAST_SGA_MASK    (0xFFFFFFFFU)
#define DMA_TCD_TCD9_DLAST_SGA_DLAST_SGA_SHIFT   (0U)
#define DMA_TCD_TCD9_DLAST_SGA_DLAST_SGA_WIDTH   (32U)
#define DMA_TCD_TCD9_DLAST_SGA_DLAST_SGA(x)      (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD9_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD9_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD9_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD9_CSR_START_MASK              (0x1U)
#define DMA_TCD_TCD9_CSR_START_SHIFT             (0U)
#define DMA_TCD_TCD9_CSR_START_WIDTH             (1U)
#define DMA_TCD_TCD9_CSR_START(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_CSR_START_SHIFT)) & DMA_TCD_TCD9_CSR_START_MASK)

#define DMA_TCD_TCD9_CSR_INTMAJOR_MASK           (0x2U)
#define DMA_TCD_TCD9_CSR_INTMAJOR_SHIFT          (1U)
#define DMA_TCD_TCD9_CSR_INTMAJOR_WIDTH          (1U)
#define DMA_TCD_TCD9_CSR_INTMAJOR(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD9_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD9_CSR_INTHALF_MASK            (0x4U)
#define DMA_TCD_TCD9_CSR_INTHALF_SHIFT           (2U)
#define DMA_TCD_TCD9_CSR_INTHALF_WIDTH           (1U)
#define DMA_TCD_TCD9_CSR_INTHALF(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD9_CSR_INTHALF_MASK)

#define DMA_TCD_TCD9_CSR_DREQ_MASK               (0x8U)
#define DMA_TCD_TCD9_CSR_DREQ_SHIFT              (3U)
#define DMA_TCD_TCD9_CSR_DREQ_WIDTH              (1U)
#define DMA_TCD_TCD9_CSR_DREQ(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_CSR_DREQ_SHIFT)) & DMA_TCD_TCD9_CSR_DREQ_MASK)

#define DMA_TCD_TCD9_CSR_ESG_MASK                (0x10U)
#define DMA_TCD_TCD9_CSR_ESG_SHIFT               (4U)
#define DMA_TCD_TCD9_CSR_ESG_WIDTH               (1U)
#define DMA_TCD_TCD9_CSR_ESG(x)                  (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_CSR_ESG_SHIFT)) & DMA_TCD_TCD9_CSR_ESG_MASK)

#define DMA_TCD_TCD9_CSR_MAJORELINK_MASK         (0x20U)
#define DMA_TCD_TCD9_CSR_MAJORELINK_SHIFT        (5U)
#define DMA_TCD_TCD9_CSR_MAJORELINK_WIDTH        (1U)
#define DMA_TCD_TCD9_CSR_MAJORELINK(x)           (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD9_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD9_CSR_EEOP_MASK               (0x40U)
#define DMA_TCD_TCD9_CSR_EEOP_SHIFT              (6U)
#define DMA_TCD_TCD9_CSR_EEOP_WIDTH              (1U)
#define DMA_TCD_TCD9_CSR_EEOP(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_CSR_EEOP_SHIFT)) & DMA_TCD_TCD9_CSR_EEOP_MASK)

#define DMA_TCD_TCD9_CSR_ESDA_MASK               (0x80U)
#define DMA_TCD_TCD9_CSR_ESDA_SHIFT              (7U)
#define DMA_TCD_TCD9_CSR_ESDA_WIDTH              (1U)
#define DMA_TCD_TCD9_CSR_ESDA(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_CSR_ESDA_SHIFT)) & DMA_TCD_TCD9_CSR_ESDA_MASK)

#define DMA_TCD_TCD9_CSR_MAJORLINKCH_MASK        (0x1F00U)
#define DMA_TCD_TCD9_CSR_MAJORLINKCH_SHIFT       (8U)
#define DMA_TCD_TCD9_CSR_MAJORLINKCH_WIDTH       (5U)
#define DMA_TCD_TCD9_CSR_MAJORLINKCH(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD9_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD9_CSR_BWC_MASK                (0xC000U)
#define DMA_TCD_TCD9_CSR_BWC_SHIFT               (14U)
#define DMA_TCD_TCD9_CSR_BWC_WIDTH               (2U)
#define DMA_TCD_TCD9_CSR_BWC(x)                  (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_CSR_BWC_SHIFT)) & DMA_TCD_TCD9_CSR_BWC_MASK)
/*! @} */

/*! @name TCD9_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD9_BITER_ELINKNO_BITER_MASK    (0x7FFFU)
#define DMA_TCD_TCD9_BITER_ELINKNO_BITER_SHIFT   (0U)
#define DMA_TCD_TCD9_BITER_ELINKNO_BITER_WIDTH   (15U)
#define DMA_TCD_TCD9_BITER_ELINKNO_BITER(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD9_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD9_BITER_ELINKNO_ELINK_MASK    (0x8000U)
#define DMA_TCD_TCD9_BITER_ELINKNO_ELINK_SHIFT   (15U)
#define DMA_TCD_TCD9_BITER_ELINKNO_ELINK_WIDTH   (1U)
#define DMA_TCD_TCD9_BITER_ELINKNO_ELINK(x)      (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD9_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD9_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD9_BITER_ELINKYES_BITER_MASK   (0x1FFU)
#define DMA_TCD_TCD9_BITER_ELINKYES_BITER_SHIFT  (0U)
#define DMA_TCD_TCD9_BITER_ELINKYES_BITER_WIDTH  (9U)
#define DMA_TCD_TCD9_BITER_ELINKYES_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD9_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD9_BITER_ELINKYES_LINKCH_MASK  (0x3E00U)
#define DMA_TCD_TCD9_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD9_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD9_BITER_ELINKYES_LINKCH(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD9_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD9_BITER_ELINKYES_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD9_BITER_ELINKYES_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD9_BITER_ELINKYES_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD9_BITER_ELINKYES_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD9_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD9_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH10_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH10_CSR_ERQ_MASK                (0x1U)
#define DMA_TCD_CH10_CSR_ERQ_SHIFT               (0U)
#define DMA_TCD_CH10_CSR_ERQ_WIDTH               (1U)
#define DMA_TCD_CH10_CSR_ERQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_CSR_ERQ_SHIFT)) & DMA_TCD_CH10_CSR_ERQ_MASK)

#define DMA_TCD_CH10_CSR_EARQ_MASK               (0x2U)
#define DMA_TCD_CH10_CSR_EARQ_SHIFT              (1U)
#define DMA_TCD_CH10_CSR_EARQ_WIDTH              (1U)
#define DMA_TCD_CH10_CSR_EARQ(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_CSR_EARQ_SHIFT)) & DMA_TCD_CH10_CSR_EARQ_MASK)

#define DMA_TCD_CH10_CSR_EEI_MASK                (0x4U)
#define DMA_TCD_CH10_CSR_EEI_SHIFT               (2U)
#define DMA_TCD_CH10_CSR_EEI_WIDTH               (1U)
#define DMA_TCD_CH10_CSR_EEI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_CSR_EEI_SHIFT)) & DMA_TCD_CH10_CSR_EEI_MASK)

#define DMA_TCD_CH10_CSR_EBW_MASK                (0x8U)
#define DMA_TCD_CH10_CSR_EBW_SHIFT               (3U)
#define DMA_TCD_CH10_CSR_EBW_WIDTH               (1U)
#define DMA_TCD_CH10_CSR_EBW(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_CSR_EBW_SHIFT)) & DMA_TCD_CH10_CSR_EBW_MASK)

#define DMA_TCD_CH10_CSR_DONE_MASK               (0x40000000U)
#define DMA_TCD_CH10_CSR_DONE_SHIFT              (30U)
#define DMA_TCD_CH10_CSR_DONE_WIDTH              (1U)
#define DMA_TCD_CH10_CSR_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_CSR_DONE_SHIFT)) & DMA_TCD_CH10_CSR_DONE_MASK)

#define DMA_TCD_CH10_CSR_ACTIVE_MASK             (0x80000000U)
#define DMA_TCD_CH10_CSR_ACTIVE_SHIFT            (31U)
#define DMA_TCD_CH10_CSR_ACTIVE_WIDTH            (1U)
#define DMA_TCD_CH10_CSR_ACTIVE(x)               (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH10_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH10_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH10_ES_DBE_MASK                 (0x1U)
#define DMA_TCD_CH10_ES_DBE_SHIFT                (0U)
#define DMA_TCD_CH10_ES_DBE_WIDTH                (1U)
#define DMA_TCD_CH10_ES_DBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_ES_DBE_SHIFT)) & DMA_TCD_CH10_ES_DBE_MASK)

#define DMA_TCD_CH10_ES_SBE_MASK                 (0x2U)
#define DMA_TCD_CH10_ES_SBE_SHIFT                (1U)
#define DMA_TCD_CH10_ES_SBE_WIDTH                (1U)
#define DMA_TCD_CH10_ES_SBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_ES_SBE_SHIFT)) & DMA_TCD_CH10_ES_SBE_MASK)

#define DMA_TCD_CH10_ES_SGE_MASK                 (0x4U)
#define DMA_TCD_CH10_ES_SGE_SHIFT                (2U)
#define DMA_TCD_CH10_ES_SGE_WIDTH                (1U)
#define DMA_TCD_CH10_ES_SGE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_ES_SGE_SHIFT)) & DMA_TCD_CH10_ES_SGE_MASK)

#define DMA_TCD_CH10_ES_NCE_MASK                 (0x8U)
#define DMA_TCD_CH10_ES_NCE_SHIFT                (3U)
#define DMA_TCD_CH10_ES_NCE_WIDTH                (1U)
#define DMA_TCD_CH10_ES_NCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_ES_NCE_SHIFT)) & DMA_TCD_CH10_ES_NCE_MASK)

#define DMA_TCD_CH10_ES_DOE_MASK                 (0x10U)
#define DMA_TCD_CH10_ES_DOE_SHIFT                (4U)
#define DMA_TCD_CH10_ES_DOE_WIDTH                (1U)
#define DMA_TCD_CH10_ES_DOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_ES_DOE_SHIFT)) & DMA_TCD_CH10_ES_DOE_MASK)

#define DMA_TCD_CH10_ES_DAE_MASK                 (0x20U)
#define DMA_TCD_CH10_ES_DAE_SHIFT                (5U)
#define DMA_TCD_CH10_ES_DAE_WIDTH                (1U)
#define DMA_TCD_CH10_ES_DAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_ES_DAE_SHIFT)) & DMA_TCD_CH10_ES_DAE_MASK)

#define DMA_TCD_CH10_ES_SOE_MASK                 (0x40U)
#define DMA_TCD_CH10_ES_SOE_SHIFT                (6U)
#define DMA_TCD_CH10_ES_SOE_WIDTH                (1U)
#define DMA_TCD_CH10_ES_SOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_ES_SOE_SHIFT)) & DMA_TCD_CH10_ES_SOE_MASK)

#define DMA_TCD_CH10_ES_SAE_MASK                 (0x80U)
#define DMA_TCD_CH10_ES_SAE_SHIFT                (7U)
#define DMA_TCD_CH10_ES_SAE_WIDTH                (1U)
#define DMA_TCD_CH10_ES_SAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_ES_SAE_SHIFT)) & DMA_TCD_CH10_ES_SAE_MASK)

#define DMA_TCD_CH10_ES_ERR_MASK                 (0x80000000U)
#define DMA_TCD_CH10_ES_ERR_SHIFT                (31U)
#define DMA_TCD_CH10_ES_ERR_WIDTH                (1U)
#define DMA_TCD_CH10_ES_ERR(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_ES_ERR_SHIFT)) & DMA_TCD_CH10_ES_ERR_MASK)
/*! @} */

/*! @name CH10_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH10_INT_INT_MASK                (0x1U)
#define DMA_TCD_CH10_INT_INT_SHIFT               (0U)
#define DMA_TCD_CH10_INT_INT_WIDTH               (1U)
#define DMA_TCD_CH10_INT_INT(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_INT_INT_SHIFT)) & DMA_TCD_CH10_INT_INT_MASK)
/*! @} */

/*! @name CH10_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH10_SBR_MID_MASK                (0xFU)
#define DMA_TCD_CH10_SBR_MID_SHIFT               (0U)
#define DMA_TCD_CH10_SBR_MID_WIDTH               (4U)
#define DMA_TCD_CH10_SBR_MID(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_SBR_MID_SHIFT)) & DMA_TCD_CH10_SBR_MID_MASK)

#define DMA_TCD_CH10_SBR_PAL_MASK                (0x8000U)
#define DMA_TCD_CH10_SBR_PAL_SHIFT               (15U)
#define DMA_TCD_CH10_SBR_PAL_WIDTH               (1U)
#define DMA_TCD_CH10_SBR_PAL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_SBR_PAL_SHIFT)) & DMA_TCD_CH10_SBR_PAL_MASK)

#define DMA_TCD_CH10_SBR_EMI_MASK                (0x10000U)
#define DMA_TCD_CH10_SBR_EMI_SHIFT               (16U)
#define DMA_TCD_CH10_SBR_EMI_WIDTH               (1U)
#define DMA_TCD_CH10_SBR_EMI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_SBR_EMI_SHIFT)) & DMA_TCD_CH10_SBR_EMI_MASK)

#define DMA_TCD_CH10_SBR_ATTR_MASK               (0xE0000U)
#define DMA_TCD_CH10_SBR_ATTR_SHIFT              (17U)
#define DMA_TCD_CH10_SBR_ATTR_WIDTH              (3U)
#define DMA_TCD_CH10_SBR_ATTR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_SBR_ATTR_SHIFT)) & DMA_TCD_CH10_SBR_ATTR_MASK)
/*! @} */

/*! @name CH10_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH10_PRI_APL_MASK                (0x7U)
#define DMA_TCD_CH10_PRI_APL_SHIFT               (0U)
#define DMA_TCD_CH10_PRI_APL_WIDTH               (3U)
#define DMA_TCD_CH10_PRI_APL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_PRI_APL_SHIFT)) & DMA_TCD_CH10_PRI_APL_MASK)

#define DMA_TCD_CH10_PRI_DPA_MASK                (0x40000000U)
#define DMA_TCD_CH10_PRI_DPA_SHIFT               (30U)
#define DMA_TCD_CH10_PRI_DPA_WIDTH               (1U)
#define DMA_TCD_CH10_PRI_DPA(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_PRI_DPA_SHIFT)) & DMA_TCD_CH10_PRI_DPA_MASK)

#define DMA_TCD_CH10_PRI_ECP_MASK                (0x80000000U)
#define DMA_TCD_CH10_PRI_ECP_SHIFT               (31U)
#define DMA_TCD_CH10_PRI_ECP_WIDTH               (1U)
#define DMA_TCD_CH10_PRI_ECP(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH10_PRI_ECP_SHIFT)) & DMA_TCD_CH10_PRI_ECP_MASK)
/*! @} */

/*! @name TCD10_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD10_SADDR_SADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD10_SADDR_SADDR_SHIFT          (0U)
#define DMA_TCD_TCD10_SADDR_SADDR_WIDTH          (32U)
#define DMA_TCD_TCD10_SADDR_SADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD10_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD10_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD10_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD10_SOFF_SOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD10_SOFF_SOFF_SHIFT            (0U)
#define DMA_TCD_TCD10_SOFF_SOFF_WIDTH            (16U)
#define DMA_TCD_TCD10_SOFF_SOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD10_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD10_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD10_ATTR_DSIZE_MASK            (0x7U)
#define DMA_TCD_TCD10_ATTR_DSIZE_SHIFT           (0U)
#define DMA_TCD_TCD10_ATTR_DSIZE_WIDTH           (3U)
#define DMA_TCD_TCD10_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD10_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD10_ATTR_DMOD_MASK             (0xF8U)
#define DMA_TCD_TCD10_ATTR_DMOD_SHIFT            (3U)
#define DMA_TCD_TCD10_ATTR_DMOD_WIDTH            (5U)
#define DMA_TCD_TCD10_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD10_ATTR_DMOD_MASK)

#define DMA_TCD_TCD10_ATTR_SSIZE_MASK            (0x700U)
#define DMA_TCD_TCD10_ATTR_SSIZE_SHIFT           (8U)
#define DMA_TCD_TCD10_ATTR_SSIZE_WIDTH           (3U)
#define DMA_TCD_TCD10_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD10_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD10_ATTR_SMOD_MASK             (0xF800U)
#define DMA_TCD_TCD10_ATTR_SMOD_SHIFT            (11U)
#define DMA_TCD_TCD10_ATTR_SMOD_WIDTH            (5U)
#define DMA_TCD_TCD10_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD10_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD10_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD10_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_TCD_TCD10_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD10_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD10_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD10_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD10_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD10_NBYTES_MLOFFNO_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD10_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD10_NBYTES_MLOFFNO_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD10_NBYTES_MLOFFNO_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD10_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD10_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD10_NBYTES_MLOFFNO_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD10_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD10_NBYTES_MLOFFNO_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD10_NBYTES_MLOFFNO_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD10_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD10_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD10_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD10_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD10_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD10_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD10_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD10_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD10_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD10_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_TCD_TCD10_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD10_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD10_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD10_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD10_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD10_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_TCD_TCD10_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD10_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD10_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD10_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD10_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD10_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_TCD_TCD10_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD10_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD10_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD10_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD10_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD10_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD10_SLAST_SDA_SLAST_SDA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD10_SLAST_SDA_SLAST_SDA_SHIFT  (0U)
#define DMA_TCD_TCD10_SLAST_SDA_SLAST_SDA_WIDTH  (32U)
#define DMA_TCD_TCD10_SLAST_SDA_SLAST_SDA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD10_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD10_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD10_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD10_DADDR_DADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD10_DADDR_DADDR_SHIFT          (0U)
#define DMA_TCD_TCD10_DADDR_DADDR_WIDTH          (32U)
#define DMA_TCD_TCD10_DADDR_DADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD10_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD10_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD10_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD10_DOFF_DOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD10_DOFF_DOFF_SHIFT            (0U)
#define DMA_TCD_TCD10_DOFF_DOFF_WIDTH            (16U)
#define DMA_TCD_TCD10_DOFF_DOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD10_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD10_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD10_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD10_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_TCD_TCD10_CITER_ELINKNO_CITER_WIDTH  (15U)
#define DMA_TCD_TCD10_CITER_ELINKNO_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD10_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD10_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD10_CITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD10_CITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD10_CITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD10_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD10_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD10_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_TCD_TCD10_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_TCD_TCD10_CITER_ELINKYES_CITER_WIDTH (9U)
#define DMA_TCD_TCD10_CITER_ELINKYES_CITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD10_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD10_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD10_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD10_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD10_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD10_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD10_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD10_CITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD10_CITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD10_CITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD10_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD10_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD10_DLAST_SGA_DLAST_SGA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD10_DLAST_SGA_DLAST_SGA_SHIFT  (0U)
#define DMA_TCD_TCD10_DLAST_SGA_DLAST_SGA_WIDTH  (32U)
#define DMA_TCD_TCD10_DLAST_SGA_DLAST_SGA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD10_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD10_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD10_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD10_CSR_START_MASK             (0x1U)
#define DMA_TCD_TCD10_CSR_START_SHIFT            (0U)
#define DMA_TCD_TCD10_CSR_START_WIDTH            (1U)
#define DMA_TCD_TCD10_CSR_START(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_CSR_START_SHIFT)) & DMA_TCD_TCD10_CSR_START_MASK)

#define DMA_TCD_TCD10_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_TCD_TCD10_CSR_INTMAJOR_SHIFT         (1U)
#define DMA_TCD_TCD10_CSR_INTMAJOR_WIDTH         (1U)
#define DMA_TCD_TCD10_CSR_INTMAJOR(x)            (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD10_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD10_CSR_INTHALF_MASK           (0x4U)
#define DMA_TCD_TCD10_CSR_INTHALF_SHIFT          (2U)
#define DMA_TCD_TCD10_CSR_INTHALF_WIDTH          (1U)
#define DMA_TCD_TCD10_CSR_INTHALF(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD10_CSR_INTHALF_MASK)

#define DMA_TCD_TCD10_CSR_DREQ_MASK              (0x8U)
#define DMA_TCD_TCD10_CSR_DREQ_SHIFT             (3U)
#define DMA_TCD_TCD10_CSR_DREQ_WIDTH             (1U)
#define DMA_TCD_TCD10_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_CSR_DREQ_SHIFT)) & DMA_TCD_TCD10_CSR_DREQ_MASK)

#define DMA_TCD_TCD10_CSR_ESG_MASK               (0x10U)
#define DMA_TCD_TCD10_CSR_ESG_SHIFT              (4U)
#define DMA_TCD_TCD10_CSR_ESG_WIDTH              (1U)
#define DMA_TCD_TCD10_CSR_ESG(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_CSR_ESG_SHIFT)) & DMA_TCD_TCD10_CSR_ESG_MASK)

#define DMA_TCD_TCD10_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_TCD_TCD10_CSR_MAJORELINK_SHIFT       (5U)
#define DMA_TCD_TCD10_CSR_MAJORELINK_WIDTH       (1U)
#define DMA_TCD_TCD10_CSR_MAJORELINK(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD10_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD10_CSR_EEOP_MASK              (0x40U)
#define DMA_TCD_TCD10_CSR_EEOP_SHIFT             (6U)
#define DMA_TCD_TCD10_CSR_EEOP_WIDTH             (1U)
#define DMA_TCD_TCD10_CSR_EEOP(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_CSR_EEOP_SHIFT)) & DMA_TCD_TCD10_CSR_EEOP_MASK)

#define DMA_TCD_TCD10_CSR_ESDA_MASK              (0x80U)
#define DMA_TCD_TCD10_CSR_ESDA_SHIFT             (7U)
#define DMA_TCD_TCD10_CSR_ESDA_WIDTH             (1U)
#define DMA_TCD_TCD10_CSR_ESDA(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_CSR_ESDA_SHIFT)) & DMA_TCD_TCD10_CSR_ESDA_MASK)

#define DMA_TCD_TCD10_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_TCD_TCD10_CSR_MAJORLINKCH_SHIFT      (8U)
#define DMA_TCD_TCD10_CSR_MAJORLINKCH_WIDTH      (5U)
#define DMA_TCD_TCD10_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD10_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD10_CSR_BWC_MASK               (0xC000U)
#define DMA_TCD_TCD10_CSR_BWC_SHIFT              (14U)
#define DMA_TCD_TCD10_CSR_BWC_WIDTH              (2U)
#define DMA_TCD_TCD10_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_CSR_BWC_SHIFT)) & DMA_TCD_TCD10_CSR_BWC_MASK)
/*! @} */

/*! @name TCD10_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD10_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD10_BITER_ELINKNO_BITER_SHIFT  (0U)
#define DMA_TCD_TCD10_BITER_ELINKNO_BITER_WIDTH  (15U)
#define DMA_TCD_TCD10_BITER_ELINKNO_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD10_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD10_BITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD10_BITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD10_BITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD10_BITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD10_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD10_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD10_BITER_ELINKYES_BITER_MASK  (0x1FFU)
#define DMA_TCD_TCD10_BITER_ELINKYES_BITER_SHIFT (0U)
#define DMA_TCD_TCD10_BITER_ELINKYES_BITER_WIDTH (9U)
#define DMA_TCD_TCD10_BITER_ELINKYES_BITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD10_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD10_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD10_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD10_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD10_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD10_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD10_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD10_BITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD10_BITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD10_BITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD10_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD10_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH11_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH11_CSR_ERQ_MASK                (0x1U)
#define DMA_TCD_CH11_CSR_ERQ_SHIFT               (0U)
#define DMA_TCD_CH11_CSR_ERQ_WIDTH               (1U)
#define DMA_TCD_CH11_CSR_ERQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_CSR_ERQ_SHIFT)) & DMA_TCD_CH11_CSR_ERQ_MASK)

#define DMA_TCD_CH11_CSR_EARQ_MASK               (0x2U)
#define DMA_TCD_CH11_CSR_EARQ_SHIFT              (1U)
#define DMA_TCD_CH11_CSR_EARQ_WIDTH              (1U)
#define DMA_TCD_CH11_CSR_EARQ(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_CSR_EARQ_SHIFT)) & DMA_TCD_CH11_CSR_EARQ_MASK)

#define DMA_TCD_CH11_CSR_EEI_MASK                (0x4U)
#define DMA_TCD_CH11_CSR_EEI_SHIFT               (2U)
#define DMA_TCD_CH11_CSR_EEI_WIDTH               (1U)
#define DMA_TCD_CH11_CSR_EEI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_CSR_EEI_SHIFT)) & DMA_TCD_CH11_CSR_EEI_MASK)

#define DMA_TCD_CH11_CSR_EBW_MASK                (0x8U)
#define DMA_TCD_CH11_CSR_EBW_SHIFT               (3U)
#define DMA_TCD_CH11_CSR_EBW_WIDTH               (1U)
#define DMA_TCD_CH11_CSR_EBW(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_CSR_EBW_SHIFT)) & DMA_TCD_CH11_CSR_EBW_MASK)

#define DMA_TCD_CH11_CSR_DONE_MASK               (0x40000000U)
#define DMA_TCD_CH11_CSR_DONE_SHIFT              (30U)
#define DMA_TCD_CH11_CSR_DONE_WIDTH              (1U)
#define DMA_TCD_CH11_CSR_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_CSR_DONE_SHIFT)) & DMA_TCD_CH11_CSR_DONE_MASK)

#define DMA_TCD_CH11_CSR_ACTIVE_MASK             (0x80000000U)
#define DMA_TCD_CH11_CSR_ACTIVE_SHIFT            (31U)
#define DMA_TCD_CH11_CSR_ACTIVE_WIDTH            (1U)
#define DMA_TCD_CH11_CSR_ACTIVE(x)               (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH11_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH11_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH11_ES_DBE_MASK                 (0x1U)
#define DMA_TCD_CH11_ES_DBE_SHIFT                (0U)
#define DMA_TCD_CH11_ES_DBE_WIDTH                (1U)
#define DMA_TCD_CH11_ES_DBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_ES_DBE_SHIFT)) & DMA_TCD_CH11_ES_DBE_MASK)

#define DMA_TCD_CH11_ES_SBE_MASK                 (0x2U)
#define DMA_TCD_CH11_ES_SBE_SHIFT                (1U)
#define DMA_TCD_CH11_ES_SBE_WIDTH                (1U)
#define DMA_TCD_CH11_ES_SBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_ES_SBE_SHIFT)) & DMA_TCD_CH11_ES_SBE_MASK)

#define DMA_TCD_CH11_ES_SGE_MASK                 (0x4U)
#define DMA_TCD_CH11_ES_SGE_SHIFT                (2U)
#define DMA_TCD_CH11_ES_SGE_WIDTH                (1U)
#define DMA_TCD_CH11_ES_SGE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_ES_SGE_SHIFT)) & DMA_TCD_CH11_ES_SGE_MASK)

#define DMA_TCD_CH11_ES_NCE_MASK                 (0x8U)
#define DMA_TCD_CH11_ES_NCE_SHIFT                (3U)
#define DMA_TCD_CH11_ES_NCE_WIDTH                (1U)
#define DMA_TCD_CH11_ES_NCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_ES_NCE_SHIFT)) & DMA_TCD_CH11_ES_NCE_MASK)

#define DMA_TCD_CH11_ES_DOE_MASK                 (0x10U)
#define DMA_TCD_CH11_ES_DOE_SHIFT                (4U)
#define DMA_TCD_CH11_ES_DOE_WIDTH                (1U)
#define DMA_TCD_CH11_ES_DOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_ES_DOE_SHIFT)) & DMA_TCD_CH11_ES_DOE_MASK)

#define DMA_TCD_CH11_ES_DAE_MASK                 (0x20U)
#define DMA_TCD_CH11_ES_DAE_SHIFT                (5U)
#define DMA_TCD_CH11_ES_DAE_WIDTH                (1U)
#define DMA_TCD_CH11_ES_DAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_ES_DAE_SHIFT)) & DMA_TCD_CH11_ES_DAE_MASK)

#define DMA_TCD_CH11_ES_SOE_MASK                 (0x40U)
#define DMA_TCD_CH11_ES_SOE_SHIFT                (6U)
#define DMA_TCD_CH11_ES_SOE_WIDTH                (1U)
#define DMA_TCD_CH11_ES_SOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_ES_SOE_SHIFT)) & DMA_TCD_CH11_ES_SOE_MASK)

#define DMA_TCD_CH11_ES_SAE_MASK                 (0x80U)
#define DMA_TCD_CH11_ES_SAE_SHIFT                (7U)
#define DMA_TCD_CH11_ES_SAE_WIDTH                (1U)
#define DMA_TCD_CH11_ES_SAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_ES_SAE_SHIFT)) & DMA_TCD_CH11_ES_SAE_MASK)

#define DMA_TCD_CH11_ES_ERR_MASK                 (0x80000000U)
#define DMA_TCD_CH11_ES_ERR_SHIFT                (31U)
#define DMA_TCD_CH11_ES_ERR_WIDTH                (1U)
#define DMA_TCD_CH11_ES_ERR(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_ES_ERR_SHIFT)) & DMA_TCD_CH11_ES_ERR_MASK)
/*! @} */

/*! @name CH11_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH11_INT_INT_MASK                (0x1U)
#define DMA_TCD_CH11_INT_INT_SHIFT               (0U)
#define DMA_TCD_CH11_INT_INT_WIDTH               (1U)
#define DMA_TCD_CH11_INT_INT(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_INT_INT_SHIFT)) & DMA_TCD_CH11_INT_INT_MASK)
/*! @} */

/*! @name CH11_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH11_SBR_MID_MASK                (0xFU)
#define DMA_TCD_CH11_SBR_MID_SHIFT               (0U)
#define DMA_TCD_CH11_SBR_MID_WIDTH               (4U)
#define DMA_TCD_CH11_SBR_MID(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_SBR_MID_SHIFT)) & DMA_TCD_CH11_SBR_MID_MASK)

#define DMA_TCD_CH11_SBR_PAL_MASK                (0x8000U)
#define DMA_TCD_CH11_SBR_PAL_SHIFT               (15U)
#define DMA_TCD_CH11_SBR_PAL_WIDTH               (1U)
#define DMA_TCD_CH11_SBR_PAL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_SBR_PAL_SHIFT)) & DMA_TCD_CH11_SBR_PAL_MASK)

#define DMA_TCD_CH11_SBR_EMI_MASK                (0x10000U)
#define DMA_TCD_CH11_SBR_EMI_SHIFT               (16U)
#define DMA_TCD_CH11_SBR_EMI_WIDTH               (1U)
#define DMA_TCD_CH11_SBR_EMI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_SBR_EMI_SHIFT)) & DMA_TCD_CH11_SBR_EMI_MASK)

#define DMA_TCD_CH11_SBR_ATTR_MASK               (0xE0000U)
#define DMA_TCD_CH11_SBR_ATTR_SHIFT              (17U)
#define DMA_TCD_CH11_SBR_ATTR_WIDTH              (3U)
#define DMA_TCD_CH11_SBR_ATTR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_SBR_ATTR_SHIFT)) & DMA_TCD_CH11_SBR_ATTR_MASK)
/*! @} */

/*! @name CH11_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH11_PRI_APL_MASK                (0x7U)
#define DMA_TCD_CH11_PRI_APL_SHIFT               (0U)
#define DMA_TCD_CH11_PRI_APL_WIDTH               (3U)
#define DMA_TCD_CH11_PRI_APL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_PRI_APL_SHIFT)) & DMA_TCD_CH11_PRI_APL_MASK)

#define DMA_TCD_CH11_PRI_DPA_MASK                (0x40000000U)
#define DMA_TCD_CH11_PRI_DPA_SHIFT               (30U)
#define DMA_TCD_CH11_PRI_DPA_WIDTH               (1U)
#define DMA_TCD_CH11_PRI_DPA(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_PRI_DPA_SHIFT)) & DMA_TCD_CH11_PRI_DPA_MASK)

#define DMA_TCD_CH11_PRI_ECP_MASK                (0x80000000U)
#define DMA_TCD_CH11_PRI_ECP_SHIFT               (31U)
#define DMA_TCD_CH11_PRI_ECP_WIDTH               (1U)
#define DMA_TCD_CH11_PRI_ECP(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH11_PRI_ECP_SHIFT)) & DMA_TCD_CH11_PRI_ECP_MASK)
/*! @} */

/*! @name TCD11_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD11_SADDR_SADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD11_SADDR_SADDR_SHIFT          (0U)
#define DMA_TCD_TCD11_SADDR_SADDR_WIDTH          (32U)
#define DMA_TCD_TCD11_SADDR_SADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD11_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD11_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD11_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD11_SOFF_SOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD11_SOFF_SOFF_SHIFT            (0U)
#define DMA_TCD_TCD11_SOFF_SOFF_WIDTH            (16U)
#define DMA_TCD_TCD11_SOFF_SOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD11_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD11_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD11_ATTR_DSIZE_MASK            (0x7U)
#define DMA_TCD_TCD11_ATTR_DSIZE_SHIFT           (0U)
#define DMA_TCD_TCD11_ATTR_DSIZE_WIDTH           (3U)
#define DMA_TCD_TCD11_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD11_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD11_ATTR_DMOD_MASK             (0xF8U)
#define DMA_TCD_TCD11_ATTR_DMOD_SHIFT            (3U)
#define DMA_TCD_TCD11_ATTR_DMOD_WIDTH            (5U)
#define DMA_TCD_TCD11_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD11_ATTR_DMOD_MASK)

#define DMA_TCD_TCD11_ATTR_SSIZE_MASK            (0x700U)
#define DMA_TCD_TCD11_ATTR_SSIZE_SHIFT           (8U)
#define DMA_TCD_TCD11_ATTR_SSIZE_WIDTH           (3U)
#define DMA_TCD_TCD11_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD11_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD11_ATTR_SMOD_MASK             (0xF800U)
#define DMA_TCD_TCD11_ATTR_SMOD_SHIFT            (11U)
#define DMA_TCD_TCD11_ATTR_SMOD_WIDTH            (5U)
#define DMA_TCD_TCD11_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD11_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD11_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD11_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_TCD_TCD11_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD11_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD11_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD11_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD11_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD11_NBYTES_MLOFFNO_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD11_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD11_NBYTES_MLOFFNO_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD11_NBYTES_MLOFFNO_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD11_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD11_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD11_NBYTES_MLOFFNO_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD11_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD11_NBYTES_MLOFFNO_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD11_NBYTES_MLOFFNO_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD11_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD11_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD11_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD11_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD11_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD11_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD11_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD11_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD11_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD11_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_TCD_TCD11_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD11_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD11_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD11_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD11_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD11_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_TCD_TCD11_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD11_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD11_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD11_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD11_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD11_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_TCD_TCD11_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD11_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD11_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD11_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD11_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD11_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD11_SLAST_SDA_SLAST_SDA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD11_SLAST_SDA_SLAST_SDA_SHIFT  (0U)
#define DMA_TCD_TCD11_SLAST_SDA_SLAST_SDA_WIDTH  (32U)
#define DMA_TCD_TCD11_SLAST_SDA_SLAST_SDA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD11_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD11_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD11_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD11_DADDR_DADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD11_DADDR_DADDR_SHIFT          (0U)
#define DMA_TCD_TCD11_DADDR_DADDR_WIDTH          (32U)
#define DMA_TCD_TCD11_DADDR_DADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD11_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD11_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD11_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD11_DOFF_DOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD11_DOFF_DOFF_SHIFT            (0U)
#define DMA_TCD_TCD11_DOFF_DOFF_WIDTH            (16U)
#define DMA_TCD_TCD11_DOFF_DOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD11_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD11_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD11_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD11_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_TCD_TCD11_CITER_ELINKNO_CITER_WIDTH  (15U)
#define DMA_TCD_TCD11_CITER_ELINKNO_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD11_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD11_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD11_CITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD11_CITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD11_CITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD11_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD11_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD11_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_TCD_TCD11_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_TCD_TCD11_CITER_ELINKYES_CITER_WIDTH (9U)
#define DMA_TCD_TCD11_CITER_ELINKYES_CITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD11_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD11_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD11_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD11_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD11_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD11_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD11_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD11_CITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD11_CITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD11_CITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD11_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD11_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD11_DLAST_SGA_DLAST_SGA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD11_DLAST_SGA_DLAST_SGA_SHIFT  (0U)
#define DMA_TCD_TCD11_DLAST_SGA_DLAST_SGA_WIDTH  (32U)
#define DMA_TCD_TCD11_DLAST_SGA_DLAST_SGA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD11_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD11_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD11_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD11_CSR_START_MASK             (0x1U)
#define DMA_TCD_TCD11_CSR_START_SHIFT            (0U)
#define DMA_TCD_TCD11_CSR_START_WIDTH            (1U)
#define DMA_TCD_TCD11_CSR_START(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_CSR_START_SHIFT)) & DMA_TCD_TCD11_CSR_START_MASK)

#define DMA_TCD_TCD11_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_TCD_TCD11_CSR_INTMAJOR_SHIFT         (1U)
#define DMA_TCD_TCD11_CSR_INTMAJOR_WIDTH         (1U)
#define DMA_TCD_TCD11_CSR_INTMAJOR(x)            (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD11_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD11_CSR_INTHALF_MASK           (0x4U)
#define DMA_TCD_TCD11_CSR_INTHALF_SHIFT          (2U)
#define DMA_TCD_TCD11_CSR_INTHALF_WIDTH          (1U)
#define DMA_TCD_TCD11_CSR_INTHALF(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD11_CSR_INTHALF_MASK)

#define DMA_TCD_TCD11_CSR_DREQ_MASK              (0x8U)
#define DMA_TCD_TCD11_CSR_DREQ_SHIFT             (3U)
#define DMA_TCD_TCD11_CSR_DREQ_WIDTH             (1U)
#define DMA_TCD_TCD11_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_CSR_DREQ_SHIFT)) & DMA_TCD_TCD11_CSR_DREQ_MASK)

#define DMA_TCD_TCD11_CSR_ESG_MASK               (0x10U)
#define DMA_TCD_TCD11_CSR_ESG_SHIFT              (4U)
#define DMA_TCD_TCD11_CSR_ESG_WIDTH              (1U)
#define DMA_TCD_TCD11_CSR_ESG(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_CSR_ESG_SHIFT)) & DMA_TCD_TCD11_CSR_ESG_MASK)

#define DMA_TCD_TCD11_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_TCD_TCD11_CSR_MAJORELINK_SHIFT       (5U)
#define DMA_TCD_TCD11_CSR_MAJORELINK_WIDTH       (1U)
#define DMA_TCD_TCD11_CSR_MAJORELINK(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD11_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD11_CSR_EEOP_MASK              (0x40U)
#define DMA_TCD_TCD11_CSR_EEOP_SHIFT             (6U)
#define DMA_TCD_TCD11_CSR_EEOP_WIDTH             (1U)
#define DMA_TCD_TCD11_CSR_EEOP(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_CSR_EEOP_SHIFT)) & DMA_TCD_TCD11_CSR_EEOP_MASK)

#define DMA_TCD_TCD11_CSR_ESDA_MASK              (0x80U)
#define DMA_TCD_TCD11_CSR_ESDA_SHIFT             (7U)
#define DMA_TCD_TCD11_CSR_ESDA_WIDTH             (1U)
#define DMA_TCD_TCD11_CSR_ESDA(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_CSR_ESDA_SHIFT)) & DMA_TCD_TCD11_CSR_ESDA_MASK)

#define DMA_TCD_TCD11_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_TCD_TCD11_CSR_MAJORLINKCH_SHIFT      (8U)
#define DMA_TCD_TCD11_CSR_MAJORLINKCH_WIDTH      (5U)
#define DMA_TCD_TCD11_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD11_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD11_CSR_BWC_MASK               (0xC000U)
#define DMA_TCD_TCD11_CSR_BWC_SHIFT              (14U)
#define DMA_TCD_TCD11_CSR_BWC_WIDTH              (2U)
#define DMA_TCD_TCD11_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_CSR_BWC_SHIFT)) & DMA_TCD_TCD11_CSR_BWC_MASK)
/*! @} */

/*! @name TCD11_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD11_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD11_BITER_ELINKNO_BITER_SHIFT  (0U)
#define DMA_TCD_TCD11_BITER_ELINKNO_BITER_WIDTH  (15U)
#define DMA_TCD_TCD11_BITER_ELINKNO_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD11_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD11_BITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD11_BITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD11_BITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD11_BITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD11_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD11_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD11_BITER_ELINKYES_BITER_MASK  (0x1FFU)
#define DMA_TCD_TCD11_BITER_ELINKYES_BITER_SHIFT (0U)
#define DMA_TCD_TCD11_BITER_ELINKYES_BITER_WIDTH (9U)
#define DMA_TCD_TCD11_BITER_ELINKYES_BITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD11_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD11_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD11_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD11_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD11_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD11_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD11_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD11_BITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD11_BITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD11_BITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD11_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD11_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH12_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH12_CSR_ERQ_MASK                (0x1U)
#define DMA_TCD_CH12_CSR_ERQ_SHIFT               (0U)
#define DMA_TCD_CH12_CSR_ERQ_WIDTH               (1U)
#define DMA_TCD_CH12_CSR_ERQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_CSR_ERQ_SHIFT)) & DMA_TCD_CH12_CSR_ERQ_MASK)

#define DMA_TCD_CH12_CSR_EARQ_MASK               (0x2U)
#define DMA_TCD_CH12_CSR_EARQ_SHIFT              (1U)
#define DMA_TCD_CH12_CSR_EARQ_WIDTH              (1U)
#define DMA_TCD_CH12_CSR_EARQ(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_CSR_EARQ_SHIFT)) & DMA_TCD_CH12_CSR_EARQ_MASK)

#define DMA_TCD_CH12_CSR_EEI_MASK                (0x4U)
#define DMA_TCD_CH12_CSR_EEI_SHIFT               (2U)
#define DMA_TCD_CH12_CSR_EEI_WIDTH               (1U)
#define DMA_TCD_CH12_CSR_EEI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_CSR_EEI_SHIFT)) & DMA_TCD_CH12_CSR_EEI_MASK)

#define DMA_TCD_CH12_CSR_EBW_MASK                (0x8U)
#define DMA_TCD_CH12_CSR_EBW_SHIFT               (3U)
#define DMA_TCD_CH12_CSR_EBW_WIDTH               (1U)
#define DMA_TCD_CH12_CSR_EBW(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_CSR_EBW_SHIFT)) & DMA_TCD_CH12_CSR_EBW_MASK)

#define DMA_TCD_CH12_CSR_DONE_MASK               (0x40000000U)
#define DMA_TCD_CH12_CSR_DONE_SHIFT              (30U)
#define DMA_TCD_CH12_CSR_DONE_WIDTH              (1U)
#define DMA_TCD_CH12_CSR_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_CSR_DONE_SHIFT)) & DMA_TCD_CH12_CSR_DONE_MASK)

#define DMA_TCD_CH12_CSR_ACTIVE_MASK             (0x80000000U)
#define DMA_TCD_CH12_CSR_ACTIVE_SHIFT            (31U)
#define DMA_TCD_CH12_CSR_ACTIVE_WIDTH            (1U)
#define DMA_TCD_CH12_CSR_ACTIVE(x)               (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH12_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH12_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH12_ES_DBE_MASK                 (0x1U)
#define DMA_TCD_CH12_ES_DBE_SHIFT                (0U)
#define DMA_TCD_CH12_ES_DBE_WIDTH                (1U)
#define DMA_TCD_CH12_ES_DBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_ES_DBE_SHIFT)) & DMA_TCD_CH12_ES_DBE_MASK)

#define DMA_TCD_CH12_ES_SBE_MASK                 (0x2U)
#define DMA_TCD_CH12_ES_SBE_SHIFT                (1U)
#define DMA_TCD_CH12_ES_SBE_WIDTH                (1U)
#define DMA_TCD_CH12_ES_SBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_ES_SBE_SHIFT)) & DMA_TCD_CH12_ES_SBE_MASK)

#define DMA_TCD_CH12_ES_SGE_MASK                 (0x4U)
#define DMA_TCD_CH12_ES_SGE_SHIFT                (2U)
#define DMA_TCD_CH12_ES_SGE_WIDTH                (1U)
#define DMA_TCD_CH12_ES_SGE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_ES_SGE_SHIFT)) & DMA_TCD_CH12_ES_SGE_MASK)

#define DMA_TCD_CH12_ES_NCE_MASK                 (0x8U)
#define DMA_TCD_CH12_ES_NCE_SHIFT                (3U)
#define DMA_TCD_CH12_ES_NCE_WIDTH                (1U)
#define DMA_TCD_CH12_ES_NCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_ES_NCE_SHIFT)) & DMA_TCD_CH12_ES_NCE_MASK)

#define DMA_TCD_CH12_ES_DOE_MASK                 (0x10U)
#define DMA_TCD_CH12_ES_DOE_SHIFT                (4U)
#define DMA_TCD_CH12_ES_DOE_WIDTH                (1U)
#define DMA_TCD_CH12_ES_DOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_ES_DOE_SHIFT)) & DMA_TCD_CH12_ES_DOE_MASK)

#define DMA_TCD_CH12_ES_DAE_MASK                 (0x20U)
#define DMA_TCD_CH12_ES_DAE_SHIFT                (5U)
#define DMA_TCD_CH12_ES_DAE_WIDTH                (1U)
#define DMA_TCD_CH12_ES_DAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_ES_DAE_SHIFT)) & DMA_TCD_CH12_ES_DAE_MASK)

#define DMA_TCD_CH12_ES_SOE_MASK                 (0x40U)
#define DMA_TCD_CH12_ES_SOE_SHIFT                (6U)
#define DMA_TCD_CH12_ES_SOE_WIDTH                (1U)
#define DMA_TCD_CH12_ES_SOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_ES_SOE_SHIFT)) & DMA_TCD_CH12_ES_SOE_MASK)

#define DMA_TCD_CH12_ES_SAE_MASK                 (0x80U)
#define DMA_TCD_CH12_ES_SAE_SHIFT                (7U)
#define DMA_TCD_CH12_ES_SAE_WIDTH                (1U)
#define DMA_TCD_CH12_ES_SAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_ES_SAE_SHIFT)) & DMA_TCD_CH12_ES_SAE_MASK)

#define DMA_TCD_CH12_ES_ERR_MASK                 (0x80000000U)
#define DMA_TCD_CH12_ES_ERR_SHIFT                (31U)
#define DMA_TCD_CH12_ES_ERR_WIDTH                (1U)
#define DMA_TCD_CH12_ES_ERR(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_ES_ERR_SHIFT)) & DMA_TCD_CH12_ES_ERR_MASK)
/*! @} */

/*! @name CH12_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH12_INT_INT_MASK                (0x1U)
#define DMA_TCD_CH12_INT_INT_SHIFT               (0U)
#define DMA_TCD_CH12_INT_INT_WIDTH               (1U)
#define DMA_TCD_CH12_INT_INT(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_INT_INT_SHIFT)) & DMA_TCD_CH12_INT_INT_MASK)
/*! @} */

/*! @name CH12_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH12_SBR_MID_MASK                (0xFU)
#define DMA_TCD_CH12_SBR_MID_SHIFT               (0U)
#define DMA_TCD_CH12_SBR_MID_WIDTH               (4U)
#define DMA_TCD_CH12_SBR_MID(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_SBR_MID_SHIFT)) & DMA_TCD_CH12_SBR_MID_MASK)

#define DMA_TCD_CH12_SBR_PAL_MASK                (0x8000U)
#define DMA_TCD_CH12_SBR_PAL_SHIFT               (15U)
#define DMA_TCD_CH12_SBR_PAL_WIDTH               (1U)
#define DMA_TCD_CH12_SBR_PAL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_SBR_PAL_SHIFT)) & DMA_TCD_CH12_SBR_PAL_MASK)

#define DMA_TCD_CH12_SBR_EMI_MASK                (0x10000U)
#define DMA_TCD_CH12_SBR_EMI_SHIFT               (16U)
#define DMA_TCD_CH12_SBR_EMI_WIDTH               (1U)
#define DMA_TCD_CH12_SBR_EMI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_SBR_EMI_SHIFT)) & DMA_TCD_CH12_SBR_EMI_MASK)

#define DMA_TCD_CH12_SBR_ATTR_MASK               (0xE0000U)
#define DMA_TCD_CH12_SBR_ATTR_SHIFT              (17U)
#define DMA_TCD_CH12_SBR_ATTR_WIDTH              (3U)
#define DMA_TCD_CH12_SBR_ATTR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_SBR_ATTR_SHIFT)) & DMA_TCD_CH12_SBR_ATTR_MASK)
/*! @} */

/*! @name CH12_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH12_PRI_APL_MASK                (0x7U)
#define DMA_TCD_CH12_PRI_APL_SHIFT               (0U)
#define DMA_TCD_CH12_PRI_APL_WIDTH               (3U)
#define DMA_TCD_CH12_PRI_APL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_PRI_APL_SHIFT)) & DMA_TCD_CH12_PRI_APL_MASK)

#define DMA_TCD_CH12_PRI_DPA_MASK                (0x40000000U)
#define DMA_TCD_CH12_PRI_DPA_SHIFT               (30U)
#define DMA_TCD_CH12_PRI_DPA_WIDTH               (1U)
#define DMA_TCD_CH12_PRI_DPA(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_PRI_DPA_SHIFT)) & DMA_TCD_CH12_PRI_DPA_MASK)

#define DMA_TCD_CH12_PRI_ECP_MASK                (0x80000000U)
#define DMA_TCD_CH12_PRI_ECP_SHIFT               (31U)
#define DMA_TCD_CH12_PRI_ECP_WIDTH               (1U)
#define DMA_TCD_CH12_PRI_ECP(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH12_PRI_ECP_SHIFT)) & DMA_TCD_CH12_PRI_ECP_MASK)
/*! @} */

/*! @name TCD12_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD12_SADDR_SADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD12_SADDR_SADDR_SHIFT          (0U)
#define DMA_TCD_TCD12_SADDR_SADDR_WIDTH          (32U)
#define DMA_TCD_TCD12_SADDR_SADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD12_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD12_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD12_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD12_SOFF_SOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD12_SOFF_SOFF_SHIFT            (0U)
#define DMA_TCD_TCD12_SOFF_SOFF_WIDTH            (16U)
#define DMA_TCD_TCD12_SOFF_SOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD12_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD12_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD12_ATTR_DSIZE_MASK            (0x7U)
#define DMA_TCD_TCD12_ATTR_DSIZE_SHIFT           (0U)
#define DMA_TCD_TCD12_ATTR_DSIZE_WIDTH           (3U)
#define DMA_TCD_TCD12_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD12_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD12_ATTR_DMOD_MASK             (0xF8U)
#define DMA_TCD_TCD12_ATTR_DMOD_SHIFT            (3U)
#define DMA_TCD_TCD12_ATTR_DMOD_WIDTH            (5U)
#define DMA_TCD_TCD12_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD12_ATTR_DMOD_MASK)

#define DMA_TCD_TCD12_ATTR_SSIZE_MASK            (0x700U)
#define DMA_TCD_TCD12_ATTR_SSIZE_SHIFT           (8U)
#define DMA_TCD_TCD12_ATTR_SSIZE_WIDTH           (3U)
#define DMA_TCD_TCD12_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD12_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD12_ATTR_SMOD_MASK             (0xF800U)
#define DMA_TCD_TCD12_ATTR_SMOD_SHIFT            (11U)
#define DMA_TCD_TCD12_ATTR_SMOD_WIDTH            (5U)
#define DMA_TCD_TCD12_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD12_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD12_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD12_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_TCD_TCD12_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD12_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD12_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD12_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD12_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD12_NBYTES_MLOFFNO_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD12_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD12_NBYTES_MLOFFNO_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD12_NBYTES_MLOFFNO_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD12_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD12_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD12_NBYTES_MLOFFNO_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD12_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD12_NBYTES_MLOFFNO_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD12_NBYTES_MLOFFNO_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD12_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD12_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD12_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD12_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD12_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD12_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD12_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD12_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD12_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD12_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_TCD_TCD12_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD12_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD12_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD12_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD12_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD12_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_TCD_TCD12_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD12_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD12_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD12_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD12_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD12_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_TCD_TCD12_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD12_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD12_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD12_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD12_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD12_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD12_SLAST_SDA_SLAST_SDA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD12_SLAST_SDA_SLAST_SDA_SHIFT  (0U)
#define DMA_TCD_TCD12_SLAST_SDA_SLAST_SDA_WIDTH  (32U)
#define DMA_TCD_TCD12_SLAST_SDA_SLAST_SDA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD12_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD12_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD12_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD12_DADDR_DADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD12_DADDR_DADDR_SHIFT          (0U)
#define DMA_TCD_TCD12_DADDR_DADDR_WIDTH          (32U)
#define DMA_TCD_TCD12_DADDR_DADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD12_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD12_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD12_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD12_DOFF_DOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD12_DOFF_DOFF_SHIFT            (0U)
#define DMA_TCD_TCD12_DOFF_DOFF_WIDTH            (16U)
#define DMA_TCD_TCD12_DOFF_DOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD12_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD12_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD12_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD12_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_TCD_TCD12_CITER_ELINKNO_CITER_WIDTH  (15U)
#define DMA_TCD_TCD12_CITER_ELINKNO_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD12_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD12_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD12_CITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD12_CITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD12_CITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD12_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD12_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD12_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_TCD_TCD12_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_TCD_TCD12_CITER_ELINKYES_CITER_WIDTH (9U)
#define DMA_TCD_TCD12_CITER_ELINKYES_CITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD12_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD12_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD12_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD12_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD12_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD12_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD12_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD12_CITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD12_CITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD12_CITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD12_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD12_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD12_DLAST_SGA_DLAST_SGA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD12_DLAST_SGA_DLAST_SGA_SHIFT  (0U)
#define DMA_TCD_TCD12_DLAST_SGA_DLAST_SGA_WIDTH  (32U)
#define DMA_TCD_TCD12_DLAST_SGA_DLAST_SGA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD12_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD12_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD12_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD12_CSR_START_MASK             (0x1U)
#define DMA_TCD_TCD12_CSR_START_SHIFT            (0U)
#define DMA_TCD_TCD12_CSR_START_WIDTH            (1U)
#define DMA_TCD_TCD12_CSR_START(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_CSR_START_SHIFT)) & DMA_TCD_TCD12_CSR_START_MASK)

#define DMA_TCD_TCD12_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_TCD_TCD12_CSR_INTMAJOR_SHIFT         (1U)
#define DMA_TCD_TCD12_CSR_INTMAJOR_WIDTH         (1U)
#define DMA_TCD_TCD12_CSR_INTMAJOR(x)            (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD12_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD12_CSR_INTHALF_MASK           (0x4U)
#define DMA_TCD_TCD12_CSR_INTHALF_SHIFT          (2U)
#define DMA_TCD_TCD12_CSR_INTHALF_WIDTH          (1U)
#define DMA_TCD_TCD12_CSR_INTHALF(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD12_CSR_INTHALF_MASK)

#define DMA_TCD_TCD12_CSR_DREQ_MASK              (0x8U)
#define DMA_TCD_TCD12_CSR_DREQ_SHIFT             (3U)
#define DMA_TCD_TCD12_CSR_DREQ_WIDTH             (1U)
#define DMA_TCD_TCD12_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_CSR_DREQ_SHIFT)) & DMA_TCD_TCD12_CSR_DREQ_MASK)

#define DMA_TCD_TCD12_CSR_ESG_MASK               (0x10U)
#define DMA_TCD_TCD12_CSR_ESG_SHIFT              (4U)
#define DMA_TCD_TCD12_CSR_ESG_WIDTH              (1U)
#define DMA_TCD_TCD12_CSR_ESG(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_CSR_ESG_SHIFT)) & DMA_TCD_TCD12_CSR_ESG_MASK)

#define DMA_TCD_TCD12_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_TCD_TCD12_CSR_MAJORELINK_SHIFT       (5U)
#define DMA_TCD_TCD12_CSR_MAJORELINK_WIDTH       (1U)
#define DMA_TCD_TCD12_CSR_MAJORELINK(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD12_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD12_CSR_EEOP_MASK              (0x40U)
#define DMA_TCD_TCD12_CSR_EEOP_SHIFT             (6U)
#define DMA_TCD_TCD12_CSR_EEOP_WIDTH             (1U)
#define DMA_TCD_TCD12_CSR_EEOP(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_CSR_EEOP_SHIFT)) & DMA_TCD_TCD12_CSR_EEOP_MASK)

#define DMA_TCD_TCD12_CSR_ESDA_MASK              (0x80U)
#define DMA_TCD_TCD12_CSR_ESDA_SHIFT             (7U)
#define DMA_TCD_TCD12_CSR_ESDA_WIDTH             (1U)
#define DMA_TCD_TCD12_CSR_ESDA(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_CSR_ESDA_SHIFT)) & DMA_TCD_TCD12_CSR_ESDA_MASK)

#define DMA_TCD_TCD12_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_TCD_TCD12_CSR_MAJORLINKCH_SHIFT      (8U)
#define DMA_TCD_TCD12_CSR_MAJORLINKCH_WIDTH      (5U)
#define DMA_TCD_TCD12_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD12_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD12_CSR_BWC_MASK               (0xC000U)
#define DMA_TCD_TCD12_CSR_BWC_SHIFT              (14U)
#define DMA_TCD_TCD12_CSR_BWC_WIDTH              (2U)
#define DMA_TCD_TCD12_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_CSR_BWC_SHIFT)) & DMA_TCD_TCD12_CSR_BWC_MASK)
/*! @} */

/*! @name TCD12_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD12_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD12_BITER_ELINKNO_BITER_SHIFT  (0U)
#define DMA_TCD_TCD12_BITER_ELINKNO_BITER_WIDTH  (15U)
#define DMA_TCD_TCD12_BITER_ELINKNO_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD12_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD12_BITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD12_BITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD12_BITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD12_BITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD12_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD12_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD12_BITER_ELINKYES_BITER_MASK  (0x1FFU)
#define DMA_TCD_TCD12_BITER_ELINKYES_BITER_SHIFT (0U)
#define DMA_TCD_TCD12_BITER_ELINKYES_BITER_WIDTH (9U)
#define DMA_TCD_TCD12_BITER_ELINKYES_BITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD12_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD12_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD12_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD12_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD12_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD12_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD12_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD12_BITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD12_BITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD12_BITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD12_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD12_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH13_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH13_CSR_ERQ_MASK                (0x1U)
#define DMA_TCD_CH13_CSR_ERQ_SHIFT               (0U)
#define DMA_TCD_CH13_CSR_ERQ_WIDTH               (1U)
#define DMA_TCD_CH13_CSR_ERQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_CSR_ERQ_SHIFT)) & DMA_TCD_CH13_CSR_ERQ_MASK)

#define DMA_TCD_CH13_CSR_EARQ_MASK               (0x2U)
#define DMA_TCD_CH13_CSR_EARQ_SHIFT              (1U)
#define DMA_TCD_CH13_CSR_EARQ_WIDTH              (1U)
#define DMA_TCD_CH13_CSR_EARQ(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_CSR_EARQ_SHIFT)) & DMA_TCD_CH13_CSR_EARQ_MASK)

#define DMA_TCD_CH13_CSR_EEI_MASK                (0x4U)
#define DMA_TCD_CH13_CSR_EEI_SHIFT               (2U)
#define DMA_TCD_CH13_CSR_EEI_WIDTH               (1U)
#define DMA_TCD_CH13_CSR_EEI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_CSR_EEI_SHIFT)) & DMA_TCD_CH13_CSR_EEI_MASK)

#define DMA_TCD_CH13_CSR_EBW_MASK                (0x8U)
#define DMA_TCD_CH13_CSR_EBW_SHIFT               (3U)
#define DMA_TCD_CH13_CSR_EBW_WIDTH               (1U)
#define DMA_TCD_CH13_CSR_EBW(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_CSR_EBW_SHIFT)) & DMA_TCD_CH13_CSR_EBW_MASK)

#define DMA_TCD_CH13_CSR_DONE_MASK               (0x40000000U)
#define DMA_TCD_CH13_CSR_DONE_SHIFT              (30U)
#define DMA_TCD_CH13_CSR_DONE_WIDTH              (1U)
#define DMA_TCD_CH13_CSR_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_CSR_DONE_SHIFT)) & DMA_TCD_CH13_CSR_DONE_MASK)

#define DMA_TCD_CH13_CSR_ACTIVE_MASK             (0x80000000U)
#define DMA_TCD_CH13_CSR_ACTIVE_SHIFT            (31U)
#define DMA_TCD_CH13_CSR_ACTIVE_WIDTH            (1U)
#define DMA_TCD_CH13_CSR_ACTIVE(x)               (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH13_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH13_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH13_ES_DBE_MASK                 (0x1U)
#define DMA_TCD_CH13_ES_DBE_SHIFT                (0U)
#define DMA_TCD_CH13_ES_DBE_WIDTH                (1U)
#define DMA_TCD_CH13_ES_DBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_ES_DBE_SHIFT)) & DMA_TCD_CH13_ES_DBE_MASK)

#define DMA_TCD_CH13_ES_SBE_MASK                 (0x2U)
#define DMA_TCD_CH13_ES_SBE_SHIFT                (1U)
#define DMA_TCD_CH13_ES_SBE_WIDTH                (1U)
#define DMA_TCD_CH13_ES_SBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_ES_SBE_SHIFT)) & DMA_TCD_CH13_ES_SBE_MASK)

#define DMA_TCD_CH13_ES_SGE_MASK                 (0x4U)
#define DMA_TCD_CH13_ES_SGE_SHIFT                (2U)
#define DMA_TCD_CH13_ES_SGE_WIDTH                (1U)
#define DMA_TCD_CH13_ES_SGE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_ES_SGE_SHIFT)) & DMA_TCD_CH13_ES_SGE_MASK)

#define DMA_TCD_CH13_ES_NCE_MASK                 (0x8U)
#define DMA_TCD_CH13_ES_NCE_SHIFT                (3U)
#define DMA_TCD_CH13_ES_NCE_WIDTH                (1U)
#define DMA_TCD_CH13_ES_NCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_ES_NCE_SHIFT)) & DMA_TCD_CH13_ES_NCE_MASK)

#define DMA_TCD_CH13_ES_DOE_MASK                 (0x10U)
#define DMA_TCD_CH13_ES_DOE_SHIFT                (4U)
#define DMA_TCD_CH13_ES_DOE_WIDTH                (1U)
#define DMA_TCD_CH13_ES_DOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_ES_DOE_SHIFT)) & DMA_TCD_CH13_ES_DOE_MASK)

#define DMA_TCD_CH13_ES_DAE_MASK                 (0x20U)
#define DMA_TCD_CH13_ES_DAE_SHIFT                (5U)
#define DMA_TCD_CH13_ES_DAE_WIDTH                (1U)
#define DMA_TCD_CH13_ES_DAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_ES_DAE_SHIFT)) & DMA_TCD_CH13_ES_DAE_MASK)

#define DMA_TCD_CH13_ES_SOE_MASK                 (0x40U)
#define DMA_TCD_CH13_ES_SOE_SHIFT                (6U)
#define DMA_TCD_CH13_ES_SOE_WIDTH                (1U)
#define DMA_TCD_CH13_ES_SOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_ES_SOE_SHIFT)) & DMA_TCD_CH13_ES_SOE_MASK)

#define DMA_TCD_CH13_ES_SAE_MASK                 (0x80U)
#define DMA_TCD_CH13_ES_SAE_SHIFT                (7U)
#define DMA_TCD_CH13_ES_SAE_WIDTH                (1U)
#define DMA_TCD_CH13_ES_SAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_ES_SAE_SHIFT)) & DMA_TCD_CH13_ES_SAE_MASK)

#define DMA_TCD_CH13_ES_ERR_MASK                 (0x80000000U)
#define DMA_TCD_CH13_ES_ERR_SHIFT                (31U)
#define DMA_TCD_CH13_ES_ERR_WIDTH                (1U)
#define DMA_TCD_CH13_ES_ERR(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_ES_ERR_SHIFT)) & DMA_TCD_CH13_ES_ERR_MASK)
/*! @} */

/*! @name CH13_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH13_INT_INT_MASK                (0x1U)
#define DMA_TCD_CH13_INT_INT_SHIFT               (0U)
#define DMA_TCD_CH13_INT_INT_WIDTH               (1U)
#define DMA_TCD_CH13_INT_INT(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_INT_INT_SHIFT)) & DMA_TCD_CH13_INT_INT_MASK)
/*! @} */

/*! @name CH13_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH13_SBR_MID_MASK                (0xFU)
#define DMA_TCD_CH13_SBR_MID_SHIFT               (0U)
#define DMA_TCD_CH13_SBR_MID_WIDTH               (4U)
#define DMA_TCD_CH13_SBR_MID(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_SBR_MID_SHIFT)) & DMA_TCD_CH13_SBR_MID_MASK)

#define DMA_TCD_CH13_SBR_PAL_MASK                (0x8000U)
#define DMA_TCD_CH13_SBR_PAL_SHIFT               (15U)
#define DMA_TCD_CH13_SBR_PAL_WIDTH               (1U)
#define DMA_TCD_CH13_SBR_PAL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_SBR_PAL_SHIFT)) & DMA_TCD_CH13_SBR_PAL_MASK)

#define DMA_TCD_CH13_SBR_EMI_MASK                (0x10000U)
#define DMA_TCD_CH13_SBR_EMI_SHIFT               (16U)
#define DMA_TCD_CH13_SBR_EMI_WIDTH               (1U)
#define DMA_TCD_CH13_SBR_EMI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_SBR_EMI_SHIFT)) & DMA_TCD_CH13_SBR_EMI_MASK)

#define DMA_TCD_CH13_SBR_ATTR_MASK               (0xE0000U)
#define DMA_TCD_CH13_SBR_ATTR_SHIFT              (17U)
#define DMA_TCD_CH13_SBR_ATTR_WIDTH              (3U)
#define DMA_TCD_CH13_SBR_ATTR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_SBR_ATTR_SHIFT)) & DMA_TCD_CH13_SBR_ATTR_MASK)
/*! @} */

/*! @name CH13_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH13_PRI_APL_MASK                (0x7U)
#define DMA_TCD_CH13_PRI_APL_SHIFT               (0U)
#define DMA_TCD_CH13_PRI_APL_WIDTH               (3U)
#define DMA_TCD_CH13_PRI_APL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_PRI_APL_SHIFT)) & DMA_TCD_CH13_PRI_APL_MASK)

#define DMA_TCD_CH13_PRI_DPA_MASK                (0x40000000U)
#define DMA_TCD_CH13_PRI_DPA_SHIFT               (30U)
#define DMA_TCD_CH13_PRI_DPA_WIDTH               (1U)
#define DMA_TCD_CH13_PRI_DPA(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_PRI_DPA_SHIFT)) & DMA_TCD_CH13_PRI_DPA_MASK)

#define DMA_TCD_CH13_PRI_ECP_MASK                (0x80000000U)
#define DMA_TCD_CH13_PRI_ECP_SHIFT               (31U)
#define DMA_TCD_CH13_PRI_ECP_WIDTH               (1U)
#define DMA_TCD_CH13_PRI_ECP(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH13_PRI_ECP_SHIFT)) & DMA_TCD_CH13_PRI_ECP_MASK)
/*! @} */

/*! @name TCD13_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD13_SADDR_SADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD13_SADDR_SADDR_SHIFT          (0U)
#define DMA_TCD_TCD13_SADDR_SADDR_WIDTH          (32U)
#define DMA_TCD_TCD13_SADDR_SADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD13_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD13_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD13_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD13_SOFF_SOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD13_SOFF_SOFF_SHIFT            (0U)
#define DMA_TCD_TCD13_SOFF_SOFF_WIDTH            (16U)
#define DMA_TCD_TCD13_SOFF_SOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD13_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD13_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD13_ATTR_DSIZE_MASK            (0x7U)
#define DMA_TCD_TCD13_ATTR_DSIZE_SHIFT           (0U)
#define DMA_TCD_TCD13_ATTR_DSIZE_WIDTH           (3U)
#define DMA_TCD_TCD13_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD13_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD13_ATTR_DMOD_MASK             (0xF8U)
#define DMA_TCD_TCD13_ATTR_DMOD_SHIFT            (3U)
#define DMA_TCD_TCD13_ATTR_DMOD_WIDTH            (5U)
#define DMA_TCD_TCD13_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD13_ATTR_DMOD_MASK)

#define DMA_TCD_TCD13_ATTR_SSIZE_MASK            (0x700U)
#define DMA_TCD_TCD13_ATTR_SSIZE_SHIFT           (8U)
#define DMA_TCD_TCD13_ATTR_SSIZE_WIDTH           (3U)
#define DMA_TCD_TCD13_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD13_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD13_ATTR_SMOD_MASK             (0xF800U)
#define DMA_TCD_TCD13_ATTR_SMOD_SHIFT            (11U)
#define DMA_TCD_TCD13_ATTR_SMOD_WIDTH            (5U)
#define DMA_TCD_TCD13_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD13_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD13_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD13_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_TCD_TCD13_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD13_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD13_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD13_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD13_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD13_NBYTES_MLOFFNO_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD13_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD13_NBYTES_MLOFFNO_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD13_NBYTES_MLOFFNO_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD13_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD13_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD13_NBYTES_MLOFFNO_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD13_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD13_NBYTES_MLOFFNO_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD13_NBYTES_MLOFFNO_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD13_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD13_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD13_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD13_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD13_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD13_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD13_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD13_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD13_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD13_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_TCD_TCD13_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD13_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD13_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD13_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD13_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD13_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_TCD_TCD13_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD13_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD13_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD13_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD13_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD13_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_TCD_TCD13_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD13_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD13_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD13_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD13_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD13_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD13_SLAST_SDA_SLAST_SDA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD13_SLAST_SDA_SLAST_SDA_SHIFT  (0U)
#define DMA_TCD_TCD13_SLAST_SDA_SLAST_SDA_WIDTH  (32U)
#define DMA_TCD_TCD13_SLAST_SDA_SLAST_SDA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD13_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD13_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD13_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD13_DADDR_DADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD13_DADDR_DADDR_SHIFT          (0U)
#define DMA_TCD_TCD13_DADDR_DADDR_WIDTH          (32U)
#define DMA_TCD_TCD13_DADDR_DADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD13_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD13_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD13_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD13_DOFF_DOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD13_DOFF_DOFF_SHIFT            (0U)
#define DMA_TCD_TCD13_DOFF_DOFF_WIDTH            (16U)
#define DMA_TCD_TCD13_DOFF_DOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD13_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD13_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD13_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD13_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_TCD_TCD13_CITER_ELINKNO_CITER_WIDTH  (15U)
#define DMA_TCD_TCD13_CITER_ELINKNO_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD13_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD13_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD13_CITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD13_CITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD13_CITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD13_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD13_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD13_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_TCD_TCD13_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_TCD_TCD13_CITER_ELINKYES_CITER_WIDTH (9U)
#define DMA_TCD_TCD13_CITER_ELINKYES_CITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD13_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD13_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD13_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD13_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD13_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD13_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD13_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD13_CITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD13_CITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD13_CITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD13_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD13_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD13_DLAST_SGA_DLAST_SGA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD13_DLAST_SGA_DLAST_SGA_SHIFT  (0U)
#define DMA_TCD_TCD13_DLAST_SGA_DLAST_SGA_WIDTH  (32U)
#define DMA_TCD_TCD13_DLAST_SGA_DLAST_SGA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD13_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD13_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD13_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD13_CSR_START_MASK             (0x1U)
#define DMA_TCD_TCD13_CSR_START_SHIFT            (0U)
#define DMA_TCD_TCD13_CSR_START_WIDTH            (1U)
#define DMA_TCD_TCD13_CSR_START(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_CSR_START_SHIFT)) & DMA_TCD_TCD13_CSR_START_MASK)

#define DMA_TCD_TCD13_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_TCD_TCD13_CSR_INTMAJOR_SHIFT         (1U)
#define DMA_TCD_TCD13_CSR_INTMAJOR_WIDTH         (1U)
#define DMA_TCD_TCD13_CSR_INTMAJOR(x)            (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD13_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD13_CSR_INTHALF_MASK           (0x4U)
#define DMA_TCD_TCD13_CSR_INTHALF_SHIFT          (2U)
#define DMA_TCD_TCD13_CSR_INTHALF_WIDTH          (1U)
#define DMA_TCD_TCD13_CSR_INTHALF(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD13_CSR_INTHALF_MASK)

#define DMA_TCD_TCD13_CSR_DREQ_MASK              (0x8U)
#define DMA_TCD_TCD13_CSR_DREQ_SHIFT             (3U)
#define DMA_TCD_TCD13_CSR_DREQ_WIDTH             (1U)
#define DMA_TCD_TCD13_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_CSR_DREQ_SHIFT)) & DMA_TCD_TCD13_CSR_DREQ_MASK)

#define DMA_TCD_TCD13_CSR_ESG_MASK               (0x10U)
#define DMA_TCD_TCD13_CSR_ESG_SHIFT              (4U)
#define DMA_TCD_TCD13_CSR_ESG_WIDTH              (1U)
#define DMA_TCD_TCD13_CSR_ESG(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_CSR_ESG_SHIFT)) & DMA_TCD_TCD13_CSR_ESG_MASK)

#define DMA_TCD_TCD13_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_TCD_TCD13_CSR_MAJORELINK_SHIFT       (5U)
#define DMA_TCD_TCD13_CSR_MAJORELINK_WIDTH       (1U)
#define DMA_TCD_TCD13_CSR_MAJORELINK(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD13_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD13_CSR_EEOP_MASK              (0x40U)
#define DMA_TCD_TCD13_CSR_EEOP_SHIFT             (6U)
#define DMA_TCD_TCD13_CSR_EEOP_WIDTH             (1U)
#define DMA_TCD_TCD13_CSR_EEOP(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_CSR_EEOP_SHIFT)) & DMA_TCD_TCD13_CSR_EEOP_MASK)

#define DMA_TCD_TCD13_CSR_ESDA_MASK              (0x80U)
#define DMA_TCD_TCD13_CSR_ESDA_SHIFT             (7U)
#define DMA_TCD_TCD13_CSR_ESDA_WIDTH             (1U)
#define DMA_TCD_TCD13_CSR_ESDA(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_CSR_ESDA_SHIFT)) & DMA_TCD_TCD13_CSR_ESDA_MASK)

#define DMA_TCD_TCD13_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_TCD_TCD13_CSR_MAJORLINKCH_SHIFT      (8U)
#define DMA_TCD_TCD13_CSR_MAJORLINKCH_WIDTH      (5U)
#define DMA_TCD_TCD13_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD13_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD13_CSR_BWC_MASK               (0xC000U)
#define DMA_TCD_TCD13_CSR_BWC_SHIFT              (14U)
#define DMA_TCD_TCD13_CSR_BWC_WIDTH              (2U)
#define DMA_TCD_TCD13_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_CSR_BWC_SHIFT)) & DMA_TCD_TCD13_CSR_BWC_MASK)
/*! @} */

/*! @name TCD13_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD13_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD13_BITER_ELINKNO_BITER_SHIFT  (0U)
#define DMA_TCD_TCD13_BITER_ELINKNO_BITER_WIDTH  (15U)
#define DMA_TCD_TCD13_BITER_ELINKNO_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD13_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD13_BITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD13_BITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD13_BITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD13_BITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD13_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD13_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD13_BITER_ELINKYES_BITER_MASK  (0x1FFU)
#define DMA_TCD_TCD13_BITER_ELINKYES_BITER_SHIFT (0U)
#define DMA_TCD_TCD13_BITER_ELINKYES_BITER_WIDTH (9U)
#define DMA_TCD_TCD13_BITER_ELINKYES_BITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD13_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD13_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD13_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD13_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD13_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD13_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD13_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD13_BITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD13_BITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD13_BITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD13_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD13_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH14_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH14_CSR_ERQ_MASK                (0x1U)
#define DMA_TCD_CH14_CSR_ERQ_SHIFT               (0U)
#define DMA_TCD_CH14_CSR_ERQ_WIDTH               (1U)
#define DMA_TCD_CH14_CSR_ERQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_CSR_ERQ_SHIFT)) & DMA_TCD_CH14_CSR_ERQ_MASK)

#define DMA_TCD_CH14_CSR_EARQ_MASK               (0x2U)
#define DMA_TCD_CH14_CSR_EARQ_SHIFT              (1U)
#define DMA_TCD_CH14_CSR_EARQ_WIDTH              (1U)
#define DMA_TCD_CH14_CSR_EARQ(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_CSR_EARQ_SHIFT)) & DMA_TCD_CH14_CSR_EARQ_MASK)

#define DMA_TCD_CH14_CSR_EEI_MASK                (0x4U)
#define DMA_TCD_CH14_CSR_EEI_SHIFT               (2U)
#define DMA_TCD_CH14_CSR_EEI_WIDTH               (1U)
#define DMA_TCD_CH14_CSR_EEI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_CSR_EEI_SHIFT)) & DMA_TCD_CH14_CSR_EEI_MASK)

#define DMA_TCD_CH14_CSR_EBW_MASK                (0x8U)
#define DMA_TCD_CH14_CSR_EBW_SHIFT               (3U)
#define DMA_TCD_CH14_CSR_EBW_WIDTH               (1U)
#define DMA_TCD_CH14_CSR_EBW(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_CSR_EBW_SHIFT)) & DMA_TCD_CH14_CSR_EBW_MASK)

#define DMA_TCD_CH14_CSR_DONE_MASK               (0x40000000U)
#define DMA_TCD_CH14_CSR_DONE_SHIFT              (30U)
#define DMA_TCD_CH14_CSR_DONE_WIDTH              (1U)
#define DMA_TCD_CH14_CSR_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_CSR_DONE_SHIFT)) & DMA_TCD_CH14_CSR_DONE_MASK)

#define DMA_TCD_CH14_CSR_ACTIVE_MASK             (0x80000000U)
#define DMA_TCD_CH14_CSR_ACTIVE_SHIFT            (31U)
#define DMA_TCD_CH14_CSR_ACTIVE_WIDTH            (1U)
#define DMA_TCD_CH14_CSR_ACTIVE(x)               (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH14_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH14_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH14_ES_DBE_MASK                 (0x1U)
#define DMA_TCD_CH14_ES_DBE_SHIFT                (0U)
#define DMA_TCD_CH14_ES_DBE_WIDTH                (1U)
#define DMA_TCD_CH14_ES_DBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_ES_DBE_SHIFT)) & DMA_TCD_CH14_ES_DBE_MASK)

#define DMA_TCD_CH14_ES_SBE_MASK                 (0x2U)
#define DMA_TCD_CH14_ES_SBE_SHIFT                (1U)
#define DMA_TCD_CH14_ES_SBE_WIDTH                (1U)
#define DMA_TCD_CH14_ES_SBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_ES_SBE_SHIFT)) & DMA_TCD_CH14_ES_SBE_MASK)

#define DMA_TCD_CH14_ES_SGE_MASK                 (0x4U)
#define DMA_TCD_CH14_ES_SGE_SHIFT                (2U)
#define DMA_TCD_CH14_ES_SGE_WIDTH                (1U)
#define DMA_TCD_CH14_ES_SGE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_ES_SGE_SHIFT)) & DMA_TCD_CH14_ES_SGE_MASK)

#define DMA_TCD_CH14_ES_NCE_MASK                 (0x8U)
#define DMA_TCD_CH14_ES_NCE_SHIFT                (3U)
#define DMA_TCD_CH14_ES_NCE_WIDTH                (1U)
#define DMA_TCD_CH14_ES_NCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_ES_NCE_SHIFT)) & DMA_TCD_CH14_ES_NCE_MASK)

#define DMA_TCD_CH14_ES_DOE_MASK                 (0x10U)
#define DMA_TCD_CH14_ES_DOE_SHIFT                (4U)
#define DMA_TCD_CH14_ES_DOE_WIDTH                (1U)
#define DMA_TCD_CH14_ES_DOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_ES_DOE_SHIFT)) & DMA_TCD_CH14_ES_DOE_MASK)

#define DMA_TCD_CH14_ES_DAE_MASK                 (0x20U)
#define DMA_TCD_CH14_ES_DAE_SHIFT                (5U)
#define DMA_TCD_CH14_ES_DAE_WIDTH                (1U)
#define DMA_TCD_CH14_ES_DAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_ES_DAE_SHIFT)) & DMA_TCD_CH14_ES_DAE_MASK)

#define DMA_TCD_CH14_ES_SOE_MASK                 (0x40U)
#define DMA_TCD_CH14_ES_SOE_SHIFT                (6U)
#define DMA_TCD_CH14_ES_SOE_WIDTH                (1U)
#define DMA_TCD_CH14_ES_SOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_ES_SOE_SHIFT)) & DMA_TCD_CH14_ES_SOE_MASK)

#define DMA_TCD_CH14_ES_SAE_MASK                 (0x80U)
#define DMA_TCD_CH14_ES_SAE_SHIFT                (7U)
#define DMA_TCD_CH14_ES_SAE_WIDTH                (1U)
#define DMA_TCD_CH14_ES_SAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_ES_SAE_SHIFT)) & DMA_TCD_CH14_ES_SAE_MASK)

#define DMA_TCD_CH14_ES_ERR_MASK                 (0x80000000U)
#define DMA_TCD_CH14_ES_ERR_SHIFT                (31U)
#define DMA_TCD_CH14_ES_ERR_WIDTH                (1U)
#define DMA_TCD_CH14_ES_ERR(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_ES_ERR_SHIFT)) & DMA_TCD_CH14_ES_ERR_MASK)
/*! @} */

/*! @name CH14_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH14_INT_INT_MASK                (0x1U)
#define DMA_TCD_CH14_INT_INT_SHIFT               (0U)
#define DMA_TCD_CH14_INT_INT_WIDTH               (1U)
#define DMA_TCD_CH14_INT_INT(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_INT_INT_SHIFT)) & DMA_TCD_CH14_INT_INT_MASK)
/*! @} */

/*! @name CH14_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH14_SBR_MID_MASK                (0xFU)
#define DMA_TCD_CH14_SBR_MID_SHIFT               (0U)
#define DMA_TCD_CH14_SBR_MID_WIDTH               (4U)
#define DMA_TCD_CH14_SBR_MID(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_SBR_MID_SHIFT)) & DMA_TCD_CH14_SBR_MID_MASK)

#define DMA_TCD_CH14_SBR_PAL_MASK                (0x8000U)
#define DMA_TCD_CH14_SBR_PAL_SHIFT               (15U)
#define DMA_TCD_CH14_SBR_PAL_WIDTH               (1U)
#define DMA_TCD_CH14_SBR_PAL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_SBR_PAL_SHIFT)) & DMA_TCD_CH14_SBR_PAL_MASK)

#define DMA_TCD_CH14_SBR_EMI_MASK                (0x10000U)
#define DMA_TCD_CH14_SBR_EMI_SHIFT               (16U)
#define DMA_TCD_CH14_SBR_EMI_WIDTH               (1U)
#define DMA_TCD_CH14_SBR_EMI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_SBR_EMI_SHIFT)) & DMA_TCD_CH14_SBR_EMI_MASK)

#define DMA_TCD_CH14_SBR_ATTR_MASK               (0xE0000U)
#define DMA_TCD_CH14_SBR_ATTR_SHIFT              (17U)
#define DMA_TCD_CH14_SBR_ATTR_WIDTH              (3U)
#define DMA_TCD_CH14_SBR_ATTR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_SBR_ATTR_SHIFT)) & DMA_TCD_CH14_SBR_ATTR_MASK)
/*! @} */

/*! @name CH14_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH14_PRI_APL_MASK                (0x7U)
#define DMA_TCD_CH14_PRI_APL_SHIFT               (0U)
#define DMA_TCD_CH14_PRI_APL_WIDTH               (3U)
#define DMA_TCD_CH14_PRI_APL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_PRI_APL_SHIFT)) & DMA_TCD_CH14_PRI_APL_MASK)

#define DMA_TCD_CH14_PRI_DPA_MASK                (0x40000000U)
#define DMA_TCD_CH14_PRI_DPA_SHIFT               (30U)
#define DMA_TCD_CH14_PRI_DPA_WIDTH               (1U)
#define DMA_TCD_CH14_PRI_DPA(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_PRI_DPA_SHIFT)) & DMA_TCD_CH14_PRI_DPA_MASK)

#define DMA_TCD_CH14_PRI_ECP_MASK                (0x80000000U)
#define DMA_TCD_CH14_PRI_ECP_SHIFT               (31U)
#define DMA_TCD_CH14_PRI_ECP_WIDTH               (1U)
#define DMA_TCD_CH14_PRI_ECP(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH14_PRI_ECP_SHIFT)) & DMA_TCD_CH14_PRI_ECP_MASK)
/*! @} */

/*! @name TCD14_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD14_SADDR_SADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD14_SADDR_SADDR_SHIFT          (0U)
#define DMA_TCD_TCD14_SADDR_SADDR_WIDTH          (32U)
#define DMA_TCD_TCD14_SADDR_SADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD14_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD14_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD14_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD14_SOFF_SOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD14_SOFF_SOFF_SHIFT            (0U)
#define DMA_TCD_TCD14_SOFF_SOFF_WIDTH            (16U)
#define DMA_TCD_TCD14_SOFF_SOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD14_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD14_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD14_ATTR_DSIZE_MASK            (0x7U)
#define DMA_TCD_TCD14_ATTR_DSIZE_SHIFT           (0U)
#define DMA_TCD_TCD14_ATTR_DSIZE_WIDTH           (3U)
#define DMA_TCD_TCD14_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD14_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD14_ATTR_DMOD_MASK             (0xF8U)
#define DMA_TCD_TCD14_ATTR_DMOD_SHIFT            (3U)
#define DMA_TCD_TCD14_ATTR_DMOD_WIDTH            (5U)
#define DMA_TCD_TCD14_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD14_ATTR_DMOD_MASK)

#define DMA_TCD_TCD14_ATTR_SSIZE_MASK            (0x700U)
#define DMA_TCD_TCD14_ATTR_SSIZE_SHIFT           (8U)
#define DMA_TCD_TCD14_ATTR_SSIZE_WIDTH           (3U)
#define DMA_TCD_TCD14_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD14_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD14_ATTR_SMOD_MASK             (0xF800U)
#define DMA_TCD_TCD14_ATTR_SMOD_SHIFT            (11U)
#define DMA_TCD_TCD14_ATTR_SMOD_WIDTH            (5U)
#define DMA_TCD_TCD14_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD14_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD14_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD14_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_TCD_TCD14_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD14_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD14_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD14_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD14_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD14_NBYTES_MLOFFNO_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD14_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD14_NBYTES_MLOFFNO_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD14_NBYTES_MLOFFNO_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD14_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD14_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD14_NBYTES_MLOFFNO_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD14_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD14_NBYTES_MLOFFNO_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD14_NBYTES_MLOFFNO_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD14_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD14_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD14_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD14_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD14_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD14_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD14_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD14_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD14_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD14_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_TCD_TCD14_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD14_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD14_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD14_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD14_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD14_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_TCD_TCD14_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD14_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD14_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD14_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD14_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD14_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_TCD_TCD14_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD14_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD14_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD14_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD14_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD14_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD14_SLAST_SDA_SLAST_SDA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD14_SLAST_SDA_SLAST_SDA_SHIFT  (0U)
#define DMA_TCD_TCD14_SLAST_SDA_SLAST_SDA_WIDTH  (32U)
#define DMA_TCD_TCD14_SLAST_SDA_SLAST_SDA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD14_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD14_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD14_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD14_DADDR_DADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD14_DADDR_DADDR_SHIFT          (0U)
#define DMA_TCD_TCD14_DADDR_DADDR_WIDTH          (32U)
#define DMA_TCD_TCD14_DADDR_DADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD14_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD14_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD14_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD14_DOFF_DOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD14_DOFF_DOFF_SHIFT            (0U)
#define DMA_TCD_TCD14_DOFF_DOFF_WIDTH            (16U)
#define DMA_TCD_TCD14_DOFF_DOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD14_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD14_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD14_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD14_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_TCD_TCD14_CITER_ELINKNO_CITER_WIDTH  (15U)
#define DMA_TCD_TCD14_CITER_ELINKNO_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD14_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD14_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD14_CITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD14_CITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD14_CITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD14_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD14_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD14_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_TCD_TCD14_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_TCD_TCD14_CITER_ELINKYES_CITER_WIDTH (9U)
#define DMA_TCD_TCD14_CITER_ELINKYES_CITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD14_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD14_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD14_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD14_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD14_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD14_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD14_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD14_CITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD14_CITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD14_CITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD14_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD14_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD14_DLAST_SGA_DLAST_SGA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD14_DLAST_SGA_DLAST_SGA_SHIFT  (0U)
#define DMA_TCD_TCD14_DLAST_SGA_DLAST_SGA_WIDTH  (32U)
#define DMA_TCD_TCD14_DLAST_SGA_DLAST_SGA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD14_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD14_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD14_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD14_CSR_START_MASK             (0x1U)
#define DMA_TCD_TCD14_CSR_START_SHIFT            (0U)
#define DMA_TCD_TCD14_CSR_START_WIDTH            (1U)
#define DMA_TCD_TCD14_CSR_START(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_CSR_START_SHIFT)) & DMA_TCD_TCD14_CSR_START_MASK)

#define DMA_TCD_TCD14_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_TCD_TCD14_CSR_INTMAJOR_SHIFT         (1U)
#define DMA_TCD_TCD14_CSR_INTMAJOR_WIDTH         (1U)
#define DMA_TCD_TCD14_CSR_INTMAJOR(x)            (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD14_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD14_CSR_INTHALF_MASK           (0x4U)
#define DMA_TCD_TCD14_CSR_INTHALF_SHIFT          (2U)
#define DMA_TCD_TCD14_CSR_INTHALF_WIDTH          (1U)
#define DMA_TCD_TCD14_CSR_INTHALF(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD14_CSR_INTHALF_MASK)

#define DMA_TCD_TCD14_CSR_DREQ_MASK              (0x8U)
#define DMA_TCD_TCD14_CSR_DREQ_SHIFT             (3U)
#define DMA_TCD_TCD14_CSR_DREQ_WIDTH             (1U)
#define DMA_TCD_TCD14_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_CSR_DREQ_SHIFT)) & DMA_TCD_TCD14_CSR_DREQ_MASK)

#define DMA_TCD_TCD14_CSR_ESG_MASK               (0x10U)
#define DMA_TCD_TCD14_CSR_ESG_SHIFT              (4U)
#define DMA_TCD_TCD14_CSR_ESG_WIDTH              (1U)
#define DMA_TCD_TCD14_CSR_ESG(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_CSR_ESG_SHIFT)) & DMA_TCD_TCD14_CSR_ESG_MASK)

#define DMA_TCD_TCD14_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_TCD_TCD14_CSR_MAJORELINK_SHIFT       (5U)
#define DMA_TCD_TCD14_CSR_MAJORELINK_WIDTH       (1U)
#define DMA_TCD_TCD14_CSR_MAJORELINK(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD14_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD14_CSR_EEOP_MASK              (0x40U)
#define DMA_TCD_TCD14_CSR_EEOP_SHIFT             (6U)
#define DMA_TCD_TCD14_CSR_EEOP_WIDTH             (1U)
#define DMA_TCD_TCD14_CSR_EEOP(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_CSR_EEOP_SHIFT)) & DMA_TCD_TCD14_CSR_EEOP_MASK)

#define DMA_TCD_TCD14_CSR_ESDA_MASK              (0x80U)
#define DMA_TCD_TCD14_CSR_ESDA_SHIFT             (7U)
#define DMA_TCD_TCD14_CSR_ESDA_WIDTH             (1U)
#define DMA_TCD_TCD14_CSR_ESDA(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_CSR_ESDA_SHIFT)) & DMA_TCD_TCD14_CSR_ESDA_MASK)

#define DMA_TCD_TCD14_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_TCD_TCD14_CSR_MAJORLINKCH_SHIFT      (8U)
#define DMA_TCD_TCD14_CSR_MAJORLINKCH_WIDTH      (5U)
#define DMA_TCD_TCD14_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD14_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD14_CSR_BWC_MASK               (0xC000U)
#define DMA_TCD_TCD14_CSR_BWC_SHIFT              (14U)
#define DMA_TCD_TCD14_CSR_BWC_WIDTH              (2U)
#define DMA_TCD_TCD14_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_CSR_BWC_SHIFT)) & DMA_TCD_TCD14_CSR_BWC_MASK)
/*! @} */

/*! @name TCD14_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD14_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD14_BITER_ELINKNO_BITER_SHIFT  (0U)
#define DMA_TCD_TCD14_BITER_ELINKNO_BITER_WIDTH  (15U)
#define DMA_TCD_TCD14_BITER_ELINKNO_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD14_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD14_BITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD14_BITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD14_BITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD14_BITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD14_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD14_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD14_BITER_ELINKYES_BITER_MASK  (0x1FFU)
#define DMA_TCD_TCD14_BITER_ELINKYES_BITER_SHIFT (0U)
#define DMA_TCD_TCD14_BITER_ELINKYES_BITER_WIDTH (9U)
#define DMA_TCD_TCD14_BITER_ELINKYES_BITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD14_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD14_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD14_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD14_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD14_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD14_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD14_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD14_BITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD14_BITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD14_BITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD14_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD14_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH15_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH15_CSR_ERQ_MASK                (0x1U)
#define DMA_TCD_CH15_CSR_ERQ_SHIFT               (0U)
#define DMA_TCD_CH15_CSR_ERQ_WIDTH               (1U)
#define DMA_TCD_CH15_CSR_ERQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_CSR_ERQ_SHIFT)) & DMA_TCD_CH15_CSR_ERQ_MASK)

#define DMA_TCD_CH15_CSR_EARQ_MASK               (0x2U)
#define DMA_TCD_CH15_CSR_EARQ_SHIFT              (1U)
#define DMA_TCD_CH15_CSR_EARQ_WIDTH              (1U)
#define DMA_TCD_CH15_CSR_EARQ(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_CSR_EARQ_SHIFT)) & DMA_TCD_CH15_CSR_EARQ_MASK)

#define DMA_TCD_CH15_CSR_EEI_MASK                (0x4U)
#define DMA_TCD_CH15_CSR_EEI_SHIFT               (2U)
#define DMA_TCD_CH15_CSR_EEI_WIDTH               (1U)
#define DMA_TCD_CH15_CSR_EEI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_CSR_EEI_SHIFT)) & DMA_TCD_CH15_CSR_EEI_MASK)

#define DMA_TCD_CH15_CSR_EBW_MASK                (0x8U)
#define DMA_TCD_CH15_CSR_EBW_SHIFT               (3U)
#define DMA_TCD_CH15_CSR_EBW_WIDTH               (1U)
#define DMA_TCD_CH15_CSR_EBW(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_CSR_EBW_SHIFT)) & DMA_TCD_CH15_CSR_EBW_MASK)

#define DMA_TCD_CH15_CSR_DONE_MASK               (0x40000000U)
#define DMA_TCD_CH15_CSR_DONE_SHIFT              (30U)
#define DMA_TCD_CH15_CSR_DONE_WIDTH              (1U)
#define DMA_TCD_CH15_CSR_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_CSR_DONE_SHIFT)) & DMA_TCD_CH15_CSR_DONE_MASK)

#define DMA_TCD_CH15_CSR_ACTIVE_MASK             (0x80000000U)
#define DMA_TCD_CH15_CSR_ACTIVE_SHIFT            (31U)
#define DMA_TCD_CH15_CSR_ACTIVE_WIDTH            (1U)
#define DMA_TCD_CH15_CSR_ACTIVE(x)               (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH15_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH15_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH15_ES_DBE_MASK                 (0x1U)
#define DMA_TCD_CH15_ES_DBE_SHIFT                (0U)
#define DMA_TCD_CH15_ES_DBE_WIDTH                (1U)
#define DMA_TCD_CH15_ES_DBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_ES_DBE_SHIFT)) & DMA_TCD_CH15_ES_DBE_MASK)

#define DMA_TCD_CH15_ES_SBE_MASK                 (0x2U)
#define DMA_TCD_CH15_ES_SBE_SHIFT                (1U)
#define DMA_TCD_CH15_ES_SBE_WIDTH                (1U)
#define DMA_TCD_CH15_ES_SBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_ES_SBE_SHIFT)) & DMA_TCD_CH15_ES_SBE_MASK)

#define DMA_TCD_CH15_ES_SGE_MASK                 (0x4U)
#define DMA_TCD_CH15_ES_SGE_SHIFT                (2U)
#define DMA_TCD_CH15_ES_SGE_WIDTH                (1U)
#define DMA_TCD_CH15_ES_SGE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_ES_SGE_SHIFT)) & DMA_TCD_CH15_ES_SGE_MASK)

#define DMA_TCD_CH15_ES_NCE_MASK                 (0x8U)
#define DMA_TCD_CH15_ES_NCE_SHIFT                (3U)
#define DMA_TCD_CH15_ES_NCE_WIDTH                (1U)
#define DMA_TCD_CH15_ES_NCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_ES_NCE_SHIFT)) & DMA_TCD_CH15_ES_NCE_MASK)

#define DMA_TCD_CH15_ES_DOE_MASK                 (0x10U)
#define DMA_TCD_CH15_ES_DOE_SHIFT                (4U)
#define DMA_TCD_CH15_ES_DOE_WIDTH                (1U)
#define DMA_TCD_CH15_ES_DOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_ES_DOE_SHIFT)) & DMA_TCD_CH15_ES_DOE_MASK)

#define DMA_TCD_CH15_ES_DAE_MASK                 (0x20U)
#define DMA_TCD_CH15_ES_DAE_SHIFT                (5U)
#define DMA_TCD_CH15_ES_DAE_WIDTH                (1U)
#define DMA_TCD_CH15_ES_DAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_ES_DAE_SHIFT)) & DMA_TCD_CH15_ES_DAE_MASK)

#define DMA_TCD_CH15_ES_SOE_MASK                 (0x40U)
#define DMA_TCD_CH15_ES_SOE_SHIFT                (6U)
#define DMA_TCD_CH15_ES_SOE_WIDTH                (1U)
#define DMA_TCD_CH15_ES_SOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_ES_SOE_SHIFT)) & DMA_TCD_CH15_ES_SOE_MASK)

#define DMA_TCD_CH15_ES_SAE_MASK                 (0x80U)
#define DMA_TCD_CH15_ES_SAE_SHIFT                (7U)
#define DMA_TCD_CH15_ES_SAE_WIDTH                (1U)
#define DMA_TCD_CH15_ES_SAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_ES_SAE_SHIFT)) & DMA_TCD_CH15_ES_SAE_MASK)

#define DMA_TCD_CH15_ES_ERR_MASK                 (0x80000000U)
#define DMA_TCD_CH15_ES_ERR_SHIFT                (31U)
#define DMA_TCD_CH15_ES_ERR_WIDTH                (1U)
#define DMA_TCD_CH15_ES_ERR(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_ES_ERR_SHIFT)) & DMA_TCD_CH15_ES_ERR_MASK)
/*! @} */

/*! @name CH15_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH15_INT_INT_MASK                (0x1U)
#define DMA_TCD_CH15_INT_INT_SHIFT               (0U)
#define DMA_TCD_CH15_INT_INT_WIDTH               (1U)
#define DMA_TCD_CH15_INT_INT(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_INT_INT_SHIFT)) & DMA_TCD_CH15_INT_INT_MASK)
/*! @} */

/*! @name CH15_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH15_SBR_MID_MASK                (0xFU)
#define DMA_TCD_CH15_SBR_MID_SHIFT               (0U)
#define DMA_TCD_CH15_SBR_MID_WIDTH               (4U)
#define DMA_TCD_CH15_SBR_MID(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_SBR_MID_SHIFT)) & DMA_TCD_CH15_SBR_MID_MASK)

#define DMA_TCD_CH15_SBR_PAL_MASK                (0x8000U)
#define DMA_TCD_CH15_SBR_PAL_SHIFT               (15U)
#define DMA_TCD_CH15_SBR_PAL_WIDTH               (1U)
#define DMA_TCD_CH15_SBR_PAL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_SBR_PAL_SHIFT)) & DMA_TCD_CH15_SBR_PAL_MASK)

#define DMA_TCD_CH15_SBR_EMI_MASK                (0x10000U)
#define DMA_TCD_CH15_SBR_EMI_SHIFT               (16U)
#define DMA_TCD_CH15_SBR_EMI_WIDTH               (1U)
#define DMA_TCD_CH15_SBR_EMI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_SBR_EMI_SHIFT)) & DMA_TCD_CH15_SBR_EMI_MASK)

#define DMA_TCD_CH15_SBR_ATTR_MASK               (0xE0000U)
#define DMA_TCD_CH15_SBR_ATTR_SHIFT              (17U)
#define DMA_TCD_CH15_SBR_ATTR_WIDTH              (3U)
#define DMA_TCD_CH15_SBR_ATTR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_SBR_ATTR_SHIFT)) & DMA_TCD_CH15_SBR_ATTR_MASK)
/*! @} */

/*! @name CH15_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH15_PRI_APL_MASK                (0x7U)
#define DMA_TCD_CH15_PRI_APL_SHIFT               (0U)
#define DMA_TCD_CH15_PRI_APL_WIDTH               (3U)
#define DMA_TCD_CH15_PRI_APL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_PRI_APL_SHIFT)) & DMA_TCD_CH15_PRI_APL_MASK)

#define DMA_TCD_CH15_PRI_DPA_MASK                (0x40000000U)
#define DMA_TCD_CH15_PRI_DPA_SHIFT               (30U)
#define DMA_TCD_CH15_PRI_DPA_WIDTH               (1U)
#define DMA_TCD_CH15_PRI_DPA(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_PRI_DPA_SHIFT)) & DMA_TCD_CH15_PRI_DPA_MASK)

#define DMA_TCD_CH15_PRI_ECP_MASK                (0x80000000U)
#define DMA_TCD_CH15_PRI_ECP_SHIFT               (31U)
#define DMA_TCD_CH15_PRI_ECP_WIDTH               (1U)
#define DMA_TCD_CH15_PRI_ECP(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH15_PRI_ECP_SHIFT)) & DMA_TCD_CH15_PRI_ECP_MASK)
/*! @} */

/*! @name TCD15_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD15_SADDR_SADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD15_SADDR_SADDR_SHIFT          (0U)
#define DMA_TCD_TCD15_SADDR_SADDR_WIDTH          (32U)
#define DMA_TCD_TCD15_SADDR_SADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD15_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD15_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD15_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD15_SOFF_SOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD15_SOFF_SOFF_SHIFT            (0U)
#define DMA_TCD_TCD15_SOFF_SOFF_WIDTH            (16U)
#define DMA_TCD_TCD15_SOFF_SOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD15_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD15_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD15_ATTR_DSIZE_MASK            (0x7U)
#define DMA_TCD_TCD15_ATTR_DSIZE_SHIFT           (0U)
#define DMA_TCD_TCD15_ATTR_DSIZE_WIDTH           (3U)
#define DMA_TCD_TCD15_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD15_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD15_ATTR_DMOD_MASK             (0xF8U)
#define DMA_TCD_TCD15_ATTR_DMOD_SHIFT            (3U)
#define DMA_TCD_TCD15_ATTR_DMOD_WIDTH            (5U)
#define DMA_TCD_TCD15_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD15_ATTR_DMOD_MASK)

#define DMA_TCD_TCD15_ATTR_SSIZE_MASK            (0x700U)
#define DMA_TCD_TCD15_ATTR_SSIZE_SHIFT           (8U)
#define DMA_TCD_TCD15_ATTR_SSIZE_WIDTH           (3U)
#define DMA_TCD_TCD15_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD15_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD15_ATTR_SMOD_MASK             (0xF800U)
#define DMA_TCD_TCD15_ATTR_SMOD_SHIFT            (11U)
#define DMA_TCD_TCD15_ATTR_SMOD_WIDTH            (5U)
#define DMA_TCD_TCD15_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD15_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD15_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD15_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_TCD_TCD15_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD15_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD15_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD15_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD15_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD15_NBYTES_MLOFFNO_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD15_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD15_NBYTES_MLOFFNO_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD15_NBYTES_MLOFFNO_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD15_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD15_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD15_NBYTES_MLOFFNO_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD15_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD15_NBYTES_MLOFFNO_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD15_NBYTES_MLOFFNO_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD15_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD15_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD15_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD15_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD15_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD15_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD15_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD15_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD15_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD15_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_TCD_TCD15_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD15_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD15_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD15_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD15_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD15_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_TCD_TCD15_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD15_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD15_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD15_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD15_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD15_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_TCD_TCD15_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD15_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD15_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD15_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD15_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD15_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD15_SLAST_SDA_SLAST_SDA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD15_SLAST_SDA_SLAST_SDA_SHIFT  (0U)
#define DMA_TCD_TCD15_SLAST_SDA_SLAST_SDA_WIDTH  (32U)
#define DMA_TCD_TCD15_SLAST_SDA_SLAST_SDA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD15_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD15_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD15_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD15_DADDR_DADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD15_DADDR_DADDR_SHIFT          (0U)
#define DMA_TCD_TCD15_DADDR_DADDR_WIDTH          (32U)
#define DMA_TCD_TCD15_DADDR_DADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD15_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD15_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD15_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD15_DOFF_DOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD15_DOFF_DOFF_SHIFT            (0U)
#define DMA_TCD_TCD15_DOFF_DOFF_WIDTH            (16U)
#define DMA_TCD_TCD15_DOFF_DOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD15_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD15_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD15_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD15_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_TCD_TCD15_CITER_ELINKNO_CITER_WIDTH  (15U)
#define DMA_TCD_TCD15_CITER_ELINKNO_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD15_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD15_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD15_CITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD15_CITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD15_CITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD15_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD15_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD15_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_TCD_TCD15_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_TCD_TCD15_CITER_ELINKYES_CITER_WIDTH (9U)
#define DMA_TCD_TCD15_CITER_ELINKYES_CITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD15_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD15_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD15_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD15_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD15_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD15_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD15_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD15_CITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD15_CITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD15_CITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD15_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD15_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD15_DLAST_SGA_DLAST_SGA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD15_DLAST_SGA_DLAST_SGA_SHIFT  (0U)
#define DMA_TCD_TCD15_DLAST_SGA_DLAST_SGA_WIDTH  (32U)
#define DMA_TCD_TCD15_DLAST_SGA_DLAST_SGA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD15_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD15_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD15_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD15_CSR_START_MASK             (0x1U)
#define DMA_TCD_TCD15_CSR_START_SHIFT            (0U)
#define DMA_TCD_TCD15_CSR_START_WIDTH            (1U)
#define DMA_TCD_TCD15_CSR_START(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_CSR_START_SHIFT)) & DMA_TCD_TCD15_CSR_START_MASK)

#define DMA_TCD_TCD15_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_TCD_TCD15_CSR_INTMAJOR_SHIFT         (1U)
#define DMA_TCD_TCD15_CSR_INTMAJOR_WIDTH         (1U)
#define DMA_TCD_TCD15_CSR_INTMAJOR(x)            (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD15_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD15_CSR_INTHALF_MASK           (0x4U)
#define DMA_TCD_TCD15_CSR_INTHALF_SHIFT          (2U)
#define DMA_TCD_TCD15_CSR_INTHALF_WIDTH          (1U)
#define DMA_TCD_TCD15_CSR_INTHALF(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD15_CSR_INTHALF_MASK)

#define DMA_TCD_TCD15_CSR_DREQ_MASK              (0x8U)
#define DMA_TCD_TCD15_CSR_DREQ_SHIFT             (3U)
#define DMA_TCD_TCD15_CSR_DREQ_WIDTH             (1U)
#define DMA_TCD_TCD15_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_CSR_DREQ_SHIFT)) & DMA_TCD_TCD15_CSR_DREQ_MASK)

#define DMA_TCD_TCD15_CSR_ESG_MASK               (0x10U)
#define DMA_TCD_TCD15_CSR_ESG_SHIFT              (4U)
#define DMA_TCD_TCD15_CSR_ESG_WIDTH              (1U)
#define DMA_TCD_TCD15_CSR_ESG(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_CSR_ESG_SHIFT)) & DMA_TCD_TCD15_CSR_ESG_MASK)

#define DMA_TCD_TCD15_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_TCD_TCD15_CSR_MAJORELINK_SHIFT       (5U)
#define DMA_TCD_TCD15_CSR_MAJORELINK_WIDTH       (1U)
#define DMA_TCD_TCD15_CSR_MAJORELINK(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD15_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD15_CSR_EEOP_MASK              (0x40U)
#define DMA_TCD_TCD15_CSR_EEOP_SHIFT             (6U)
#define DMA_TCD_TCD15_CSR_EEOP_WIDTH             (1U)
#define DMA_TCD_TCD15_CSR_EEOP(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_CSR_EEOP_SHIFT)) & DMA_TCD_TCD15_CSR_EEOP_MASK)

#define DMA_TCD_TCD15_CSR_ESDA_MASK              (0x80U)
#define DMA_TCD_TCD15_CSR_ESDA_SHIFT             (7U)
#define DMA_TCD_TCD15_CSR_ESDA_WIDTH             (1U)
#define DMA_TCD_TCD15_CSR_ESDA(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_CSR_ESDA_SHIFT)) & DMA_TCD_TCD15_CSR_ESDA_MASK)

#define DMA_TCD_TCD15_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_TCD_TCD15_CSR_MAJORLINKCH_SHIFT      (8U)
#define DMA_TCD_TCD15_CSR_MAJORLINKCH_WIDTH      (5U)
#define DMA_TCD_TCD15_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD15_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD15_CSR_BWC_MASK               (0xC000U)
#define DMA_TCD_TCD15_CSR_BWC_SHIFT              (14U)
#define DMA_TCD_TCD15_CSR_BWC_WIDTH              (2U)
#define DMA_TCD_TCD15_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_CSR_BWC_SHIFT)) & DMA_TCD_TCD15_CSR_BWC_MASK)
/*! @} */

/*! @name TCD15_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD15_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD15_BITER_ELINKNO_BITER_SHIFT  (0U)
#define DMA_TCD_TCD15_BITER_ELINKNO_BITER_WIDTH  (15U)
#define DMA_TCD_TCD15_BITER_ELINKNO_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD15_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD15_BITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD15_BITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD15_BITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD15_BITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD15_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD15_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD15_BITER_ELINKYES_BITER_MASK  (0x1FFU)
#define DMA_TCD_TCD15_BITER_ELINKYES_BITER_SHIFT (0U)
#define DMA_TCD_TCD15_BITER_ELINKYES_BITER_WIDTH (9U)
#define DMA_TCD_TCD15_BITER_ELINKYES_BITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD15_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD15_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD15_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD15_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD15_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD15_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD15_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD15_BITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD15_BITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD15_BITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD15_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD15_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH16_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH16_CSR_ERQ_MASK                (0x1U)
#define DMA_TCD_CH16_CSR_ERQ_SHIFT               (0U)
#define DMA_TCD_CH16_CSR_ERQ_WIDTH               (1U)
#define DMA_TCD_CH16_CSR_ERQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_CSR_ERQ_SHIFT)) & DMA_TCD_CH16_CSR_ERQ_MASK)

#define DMA_TCD_CH16_CSR_EARQ_MASK               (0x2U)
#define DMA_TCD_CH16_CSR_EARQ_SHIFT              (1U)
#define DMA_TCD_CH16_CSR_EARQ_WIDTH              (1U)
#define DMA_TCD_CH16_CSR_EARQ(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_CSR_EARQ_SHIFT)) & DMA_TCD_CH16_CSR_EARQ_MASK)

#define DMA_TCD_CH16_CSR_EEI_MASK                (0x4U)
#define DMA_TCD_CH16_CSR_EEI_SHIFT               (2U)
#define DMA_TCD_CH16_CSR_EEI_WIDTH               (1U)
#define DMA_TCD_CH16_CSR_EEI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_CSR_EEI_SHIFT)) & DMA_TCD_CH16_CSR_EEI_MASK)

#define DMA_TCD_CH16_CSR_EBW_MASK                (0x8U)
#define DMA_TCD_CH16_CSR_EBW_SHIFT               (3U)
#define DMA_TCD_CH16_CSR_EBW_WIDTH               (1U)
#define DMA_TCD_CH16_CSR_EBW(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_CSR_EBW_SHIFT)) & DMA_TCD_CH16_CSR_EBW_MASK)

#define DMA_TCD_CH16_CSR_DONE_MASK               (0x40000000U)
#define DMA_TCD_CH16_CSR_DONE_SHIFT              (30U)
#define DMA_TCD_CH16_CSR_DONE_WIDTH              (1U)
#define DMA_TCD_CH16_CSR_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_CSR_DONE_SHIFT)) & DMA_TCD_CH16_CSR_DONE_MASK)

#define DMA_TCD_CH16_CSR_ACTIVE_MASK             (0x80000000U)
#define DMA_TCD_CH16_CSR_ACTIVE_SHIFT            (31U)
#define DMA_TCD_CH16_CSR_ACTIVE_WIDTH            (1U)
#define DMA_TCD_CH16_CSR_ACTIVE(x)               (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH16_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH16_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH16_ES_DBE_MASK                 (0x1U)
#define DMA_TCD_CH16_ES_DBE_SHIFT                (0U)
#define DMA_TCD_CH16_ES_DBE_WIDTH                (1U)
#define DMA_TCD_CH16_ES_DBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_ES_DBE_SHIFT)) & DMA_TCD_CH16_ES_DBE_MASK)

#define DMA_TCD_CH16_ES_SBE_MASK                 (0x2U)
#define DMA_TCD_CH16_ES_SBE_SHIFT                (1U)
#define DMA_TCD_CH16_ES_SBE_WIDTH                (1U)
#define DMA_TCD_CH16_ES_SBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_ES_SBE_SHIFT)) & DMA_TCD_CH16_ES_SBE_MASK)

#define DMA_TCD_CH16_ES_SGE_MASK                 (0x4U)
#define DMA_TCD_CH16_ES_SGE_SHIFT                (2U)
#define DMA_TCD_CH16_ES_SGE_WIDTH                (1U)
#define DMA_TCD_CH16_ES_SGE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_ES_SGE_SHIFT)) & DMA_TCD_CH16_ES_SGE_MASK)

#define DMA_TCD_CH16_ES_NCE_MASK                 (0x8U)
#define DMA_TCD_CH16_ES_NCE_SHIFT                (3U)
#define DMA_TCD_CH16_ES_NCE_WIDTH                (1U)
#define DMA_TCD_CH16_ES_NCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_ES_NCE_SHIFT)) & DMA_TCD_CH16_ES_NCE_MASK)

#define DMA_TCD_CH16_ES_DOE_MASK                 (0x10U)
#define DMA_TCD_CH16_ES_DOE_SHIFT                (4U)
#define DMA_TCD_CH16_ES_DOE_WIDTH                (1U)
#define DMA_TCD_CH16_ES_DOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_ES_DOE_SHIFT)) & DMA_TCD_CH16_ES_DOE_MASK)

#define DMA_TCD_CH16_ES_DAE_MASK                 (0x20U)
#define DMA_TCD_CH16_ES_DAE_SHIFT                (5U)
#define DMA_TCD_CH16_ES_DAE_WIDTH                (1U)
#define DMA_TCD_CH16_ES_DAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_ES_DAE_SHIFT)) & DMA_TCD_CH16_ES_DAE_MASK)

#define DMA_TCD_CH16_ES_SOE_MASK                 (0x40U)
#define DMA_TCD_CH16_ES_SOE_SHIFT                (6U)
#define DMA_TCD_CH16_ES_SOE_WIDTH                (1U)
#define DMA_TCD_CH16_ES_SOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_ES_SOE_SHIFT)) & DMA_TCD_CH16_ES_SOE_MASK)

#define DMA_TCD_CH16_ES_SAE_MASK                 (0x80U)
#define DMA_TCD_CH16_ES_SAE_SHIFT                (7U)
#define DMA_TCD_CH16_ES_SAE_WIDTH                (1U)
#define DMA_TCD_CH16_ES_SAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_ES_SAE_SHIFT)) & DMA_TCD_CH16_ES_SAE_MASK)

#define DMA_TCD_CH16_ES_ERR_MASK                 (0x80000000U)
#define DMA_TCD_CH16_ES_ERR_SHIFT                (31U)
#define DMA_TCD_CH16_ES_ERR_WIDTH                (1U)
#define DMA_TCD_CH16_ES_ERR(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_ES_ERR_SHIFT)) & DMA_TCD_CH16_ES_ERR_MASK)
/*! @} */

/*! @name CH16_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH16_INT_INT_MASK                (0x1U)
#define DMA_TCD_CH16_INT_INT_SHIFT               (0U)
#define DMA_TCD_CH16_INT_INT_WIDTH               (1U)
#define DMA_TCD_CH16_INT_INT(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_INT_INT_SHIFT)) & DMA_TCD_CH16_INT_INT_MASK)
/*! @} */

/*! @name CH16_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH16_SBR_MID_MASK                (0xFU)
#define DMA_TCD_CH16_SBR_MID_SHIFT               (0U)
#define DMA_TCD_CH16_SBR_MID_WIDTH               (4U)
#define DMA_TCD_CH16_SBR_MID(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_SBR_MID_SHIFT)) & DMA_TCD_CH16_SBR_MID_MASK)

#define DMA_TCD_CH16_SBR_PAL_MASK                (0x8000U)
#define DMA_TCD_CH16_SBR_PAL_SHIFT               (15U)
#define DMA_TCD_CH16_SBR_PAL_WIDTH               (1U)
#define DMA_TCD_CH16_SBR_PAL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_SBR_PAL_SHIFT)) & DMA_TCD_CH16_SBR_PAL_MASK)

#define DMA_TCD_CH16_SBR_EMI_MASK                (0x10000U)
#define DMA_TCD_CH16_SBR_EMI_SHIFT               (16U)
#define DMA_TCD_CH16_SBR_EMI_WIDTH               (1U)
#define DMA_TCD_CH16_SBR_EMI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_SBR_EMI_SHIFT)) & DMA_TCD_CH16_SBR_EMI_MASK)

#define DMA_TCD_CH16_SBR_ATTR_MASK               (0xE0000U)
#define DMA_TCD_CH16_SBR_ATTR_SHIFT              (17U)
#define DMA_TCD_CH16_SBR_ATTR_WIDTH              (3U)
#define DMA_TCD_CH16_SBR_ATTR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_SBR_ATTR_SHIFT)) & DMA_TCD_CH16_SBR_ATTR_MASK)
/*! @} */

/*! @name CH16_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH16_PRI_APL_MASK                (0x7U)
#define DMA_TCD_CH16_PRI_APL_SHIFT               (0U)
#define DMA_TCD_CH16_PRI_APL_WIDTH               (3U)
#define DMA_TCD_CH16_PRI_APL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_PRI_APL_SHIFT)) & DMA_TCD_CH16_PRI_APL_MASK)

#define DMA_TCD_CH16_PRI_DPA_MASK                (0x40000000U)
#define DMA_TCD_CH16_PRI_DPA_SHIFT               (30U)
#define DMA_TCD_CH16_PRI_DPA_WIDTH               (1U)
#define DMA_TCD_CH16_PRI_DPA(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_PRI_DPA_SHIFT)) & DMA_TCD_CH16_PRI_DPA_MASK)

#define DMA_TCD_CH16_PRI_ECP_MASK                (0x80000000U)
#define DMA_TCD_CH16_PRI_ECP_SHIFT               (31U)
#define DMA_TCD_CH16_PRI_ECP_WIDTH               (1U)
#define DMA_TCD_CH16_PRI_ECP(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH16_PRI_ECP_SHIFT)) & DMA_TCD_CH16_PRI_ECP_MASK)
/*! @} */

/*! @name TCD16_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD16_SADDR_SADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD16_SADDR_SADDR_SHIFT          (0U)
#define DMA_TCD_TCD16_SADDR_SADDR_WIDTH          (32U)
#define DMA_TCD_TCD16_SADDR_SADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD16_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD16_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD16_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD16_SOFF_SOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD16_SOFF_SOFF_SHIFT            (0U)
#define DMA_TCD_TCD16_SOFF_SOFF_WIDTH            (16U)
#define DMA_TCD_TCD16_SOFF_SOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD16_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD16_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD16_ATTR_DSIZE_MASK            (0x7U)
#define DMA_TCD_TCD16_ATTR_DSIZE_SHIFT           (0U)
#define DMA_TCD_TCD16_ATTR_DSIZE_WIDTH           (3U)
#define DMA_TCD_TCD16_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD16_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD16_ATTR_DMOD_MASK             (0xF8U)
#define DMA_TCD_TCD16_ATTR_DMOD_SHIFT            (3U)
#define DMA_TCD_TCD16_ATTR_DMOD_WIDTH            (5U)
#define DMA_TCD_TCD16_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD16_ATTR_DMOD_MASK)

#define DMA_TCD_TCD16_ATTR_SSIZE_MASK            (0x700U)
#define DMA_TCD_TCD16_ATTR_SSIZE_SHIFT           (8U)
#define DMA_TCD_TCD16_ATTR_SSIZE_WIDTH           (3U)
#define DMA_TCD_TCD16_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD16_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD16_ATTR_SMOD_MASK             (0xF800U)
#define DMA_TCD_TCD16_ATTR_SMOD_SHIFT            (11U)
#define DMA_TCD_TCD16_ATTR_SMOD_WIDTH            (5U)
#define DMA_TCD_TCD16_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD16_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD16_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD16_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_TCD_TCD16_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD16_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD16_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD16_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD16_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD16_NBYTES_MLOFFNO_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD16_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD16_NBYTES_MLOFFNO_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD16_NBYTES_MLOFFNO_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD16_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD16_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD16_NBYTES_MLOFFNO_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD16_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD16_NBYTES_MLOFFNO_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD16_NBYTES_MLOFFNO_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD16_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD16_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD16_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD16_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD16_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD16_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD16_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD16_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD16_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD16_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_TCD_TCD16_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD16_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD16_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD16_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD16_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD16_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_TCD_TCD16_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD16_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD16_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD16_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD16_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD16_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_TCD_TCD16_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD16_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD16_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD16_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD16_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD16_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD16_SLAST_SDA_SLAST_SDA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD16_SLAST_SDA_SLAST_SDA_SHIFT  (0U)
#define DMA_TCD_TCD16_SLAST_SDA_SLAST_SDA_WIDTH  (32U)
#define DMA_TCD_TCD16_SLAST_SDA_SLAST_SDA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD16_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD16_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD16_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD16_DADDR_DADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD16_DADDR_DADDR_SHIFT          (0U)
#define DMA_TCD_TCD16_DADDR_DADDR_WIDTH          (32U)
#define DMA_TCD_TCD16_DADDR_DADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD16_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD16_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD16_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD16_DOFF_DOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD16_DOFF_DOFF_SHIFT            (0U)
#define DMA_TCD_TCD16_DOFF_DOFF_WIDTH            (16U)
#define DMA_TCD_TCD16_DOFF_DOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD16_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD16_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD16_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD16_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_TCD_TCD16_CITER_ELINKNO_CITER_WIDTH  (15U)
#define DMA_TCD_TCD16_CITER_ELINKNO_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD16_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD16_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD16_CITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD16_CITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD16_CITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD16_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD16_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD16_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_TCD_TCD16_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_TCD_TCD16_CITER_ELINKYES_CITER_WIDTH (9U)
#define DMA_TCD_TCD16_CITER_ELINKYES_CITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD16_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD16_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD16_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD16_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD16_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD16_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD16_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD16_CITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD16_CITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD16_CITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD16_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD16_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD16_DLAST_SGA_DLAST_SGA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD16_DLAST_SGA_DLAST_SGA_SHIFT  (0U)
#define DMA_TCD_TCD16_DLAST_SGA_DLAST_SGA_WIDTH  (32U)
#define DMA_TCD_TCD16_DLAST_SGA_DLAST_SGA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD16_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD16_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD16_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD16_CSR_START_MASK             (0x1U)
#define DMA_TCD_TCD16_CSR_START_SHIFT            (0U)
#define DMA_TCD_TCD16_CSR_START_WIDTH            (1U)
#define DMA_TCD_TCD16_CSR_START(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_CSR_START_SHIFT)) & DMA_TCD_TCD16_CSR_START_MASK)

#define DMA_TCD_TCD16_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_TCD_TCD16_CSR_INTMAJOR_SHIFT         (1U)
#define DMA_TCD_TCD16_CSR_INTMAJOR_WIDTH         (1U)
#define DMA_TCD_TCD16_CSR_INTMAJOR(x)            (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD16_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD16_CSR_INTHALF_MASK           (0x4U)
#define DMA_TCD_TCD16_CSR_INTHALF_SHIFT          (2U)
#define DMA_TCD_TCD16_CSR_INTHALF_WIDTH          (1U)
#define DMA_TCD_TCD16_CSR_INTHALF(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD16_CSR_INTHALF_MASK)

#define DMA_TCD_TCD16_CSR_DREQ_MASK              (0x8U)
#define DMA_TCD_TCD16_CSR_DREQ_SHIFT             (3U)
#define DMA_TCD_TCD16_CSR_DREQ_WIDTH             (1U)
#define DMA_TCD_TCD16_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_CSR_DREQ_SHIFT)) & DMA_TCD_TCD16_CSR_DREQ_MASK)

#define DMA_TCD_TCD16_CSR_ESG_MASK               (0x10U)
#define DMA_TCD_TCD16_CSR_ESG_SHIFT              (4U)
#define DMA_TCD_TCD16_CSR_ESG_WIDTH              (1U)
#define DMA_TCD_TCD16_CSR_ESG(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_CSR_ESG_SHIFT)) & DMA_TCD_TCD16_CSR_ESG_MASK)

#define DMA_TCD_TCD16_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_TCD_TCD16_CSR_MAJORELINK_SHIFT       (5U)
#define DMA_TCD_TCD16_CSR_MAJORELINK_WIDTH       (1U)
#define DMA_TCD_TCD16_CSR_MAJORELINK(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD16_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD16_CSR_EEOP_MASK              (0x40U)
#define DMA_TCD_TCD16_CSR_EEOP_SHIFT             (6U)
#define DMA_TCD_TCD16_CSR_EEOP_WIDTH             (1U)
#define DMA_TCD_TCD16_CSR_EEOP(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_CSR_EEOP_SHIFT)) & DMA_TCD_TCD16_CSR_EEOP_MASK)

#define DMA_TCD_TCD16_CSR_ESDA_MASK              (0x80U)
#define DMA_TCD_TCD16_CSR_ESDA_SHIFT             (7U)
#define DMA_TCD_TCD16_CSR_ESDA_WIDTH             (1U)
#define DMA_TCD_TCD16_CSR_ESDA(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_CSR_ESDA_SHIFT)) & DMA_TCD_TCD16_CSR_ESDA_MASK)

#define DMA_TCD_TCD16_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_TCD_TCD16_CSR_MAJORLINKCH_SHIFT      (8U)
#define DMA_TCD_TCD16_CSR_MAJORLINKCH_WIDTH      (5U)
#define DMA_TCD_TCD16_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD16_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD16_CSR_BWC_MASK               (0xC000U)
#define DMA_TCD_TCD16_CSR_BWC_SHIFT              (14U)
#define DMA_TCD_TCD16_CSR_BWC_WIDTH              (2U)
#define DMA_TCD_TCD16_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_CSR_BWC_SHIFT)) & DMA_TCD_TCD16_CSR_BWC_MASK)
/*! @} */

/*! @name TCD16_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD16_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD16_BITER_ELINKNO_BITER_SHIFT  (0U)
#define DMA_TCD_TCD16_BITER_ELINKNO_BITER_WIDTH  (15U)
#define DMA_TCD_TCD16_BITER_ELINKNO_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD16_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD16_BITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD16_BITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD16_BITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD16_BITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD16_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD16_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD16_BITER_ELINKYES_BITER_MASK  (0x1FFU)
#define DMA_TCD_TCD16_BITER_ELINKYES_BITER_SHIFT (0U)
#define DMA_TCD_TCD16_BITER_ELINKYES_BITER_WIDTH (9U)
#define DMA_TCD_TCD16_BITER_ELINKYES_BITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD16_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD16_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD16_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD16_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD16_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD16_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD16_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD16_BITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD16_BITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD16_BITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD16_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD16_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH17_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH17_CSR_ERQ_MASK                (0x1U)
#define DMA_TCD_CH17_CSR_ERQ_SHIFT               (0U)
#define DMA_TCD_CH17_CSR_ERQ_WIDTH               (1U)
#define DMA_TCD_CH17_CSR_ERQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_CSR_ERQ_SHIFT)) & DMA_TCD_CH17_CSR_ERQ_MASK)

#define DMA_TCD_CH17_CSR_EARQ_MASK               (0x2U)
#define DMA_TCD_CH17_CSR_EARQ_SHIFT              (1U)
#define DMA_TCD_CH17_CSR_EARQ_WIDTH              (1U)
#define DMA_TCD_CH17_CSR_EARQ(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_CSR_EARQ_SHIFT)) & DMA_TCD_CH17_CSR_EARQ_MASK)

#define DMA_TCD_CH17_CSR_EEI_MASK                (0x4U)
#define DMA_TCD_CH17_CSR_EEI_SHIFT               (2U)
#define DMA_TCD_CH17_CSR_EEI_WIDTH               (1U)
#define DMA_TCD_CH17_CSR_EEI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_CSR_EEI_SHIFT)) & DMA_TCD_CH17_CSR_EEI_MASK)

#define DMA_TCD_CH17_CSR_EBW_MASK                (0x8U)
#define DMA_TCD_CH17_CSR_EBW_SHIFT               (3U)
#define DMA_TCD_CH17_CSR_EBW_WIDTH               (1U)
#define DMA_TCD_CH17_CSR_EBW(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_CSR_EBW_SHIFT)) & DMA_TCD_CH17_CSR_EBW_MASK)

#define DMA_TCD_CH17_CSR_DONE_MASK               (0x40000000U)
#define DMA_TCD_CH17_CSR_DONE_SHIFT              (30U)
#define DMA_TCD_CH17_CSR_DONE_WIDTH              (1U)
#define DMA_TCD_CH17_CSR_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_CSR_DONE_SHIFT)) & DMA_TCD_CH17_CSR_DONE_MASK)

#define DMA_TCD_CH17_CSR_ACTIVE_MASK             (0x80000000U)
#define DMA_TCD_CH17_CSR_ACTIVE_SHIFT            (31U)
#define DMA_TCD_CH17_CSR_ACTIVE_WIDTH            (1U)
#define DMA_TCD_CH17_CSR_ACTIVE(x)               (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH17_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH17_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH17_ES_DBE_MASK                 (0x1U)
#define DMA_TCD_CH17_ES_DBE_SHIFT                (0U)
#define DMA_TCD_CH17_ES_DBE_WIDTH                (1U)
#define DMA_TCD_CH17_ES_DBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_ES_DBE_SHIFT)) & DMA_TCD_CH17_ES_DBE_MASK)

#define DMA_TCD_CH17_ES_SBE_MASK                 (0x2U)
#define DMA_TCD_CH17_ES_SBE_SHIFT                (1U)
#define DMA_TCD_CH17_ES_SBE_WIDTH                (1U)
#define DMA_TCD_CH17_ES_SBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_ES_SBE_SHIFT)) & DMA_TCD_CH17_ES_SBE_MASK)

#define DMA_TCD_CH17_ES_SGE_MASK                 (0x4U)
#define DMA_TCD_CH17_ES_SGE_SHIFT                (2U)
#define DMA_TCD_CH17_ES_SGE_WIDTH                (1U)
#define DMA_TCD_CH17_ES_SGE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_ES_SGE_SHIFT)) & DMA_TCD_CH17_ES_SGE_MASK)

#define DMA_TCD_CH17_ES_NCE_MASK                 (0x8U)
#define DMA_TCD_CH17_ES_NCE_SHIFT                (3U)
#define DMA_TCD_CH17_ES_NCE_WIDTH                (1U)
#define DMA_TCD_CH17_ES_NCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_ES_NCE_SHIFT)) & DMA_TCD_CH17_ES_NCE_MASK)

#define DMA_TCD_CH17_ES_DOE_MASK                 (0x10U)
#define DMA_TCD_CH17_ES_DOE_SHIFT                (4U)
#define DMA_TCD_CH17_ES_DOE_WIDTH                (1U)
#define DMA_TCD_CH17_ES_DOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_ES_DOE_SHIFT)) & DMA_TCD_CH17_ES_DOE_MASK)

#define DMA_TCD_CH17_ES_DAE_MASK                 (0x20U)
#define DMA_TCD_CH17_ES_DAE_SHIFT                (5U)
#define DMA_TCD_CH17_ES_DAE_WIDTH                (1U)
#define DMA_TCD_CH17_ES_DAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_ES_DAE_SHIFT)) & DMA_TCD_CH17_ES_DAE_MASK)

#define DMA_TCD_CH17_ES_SOE_MASK                 (0x40U)
#define DMA_TCD_CH17_ES_SOE_SHIFT                (6U)
#define DMA_TCD_CH17_ES_SOE_WIDTH                (1U)
#define DMA_TCD_CH17_ES_SOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_ES_SOE_SHIFT)) & DMA_TCD_CH17_ES_SOE_MASK)

#define DMA_TCD_CH17_ES_SAE_MASK                 (0x80U)
#define DMA_TCD_CH17_ES_SAE_SHIFT                (7U)
#define DMA_TCD_CH17_ES_SAE_WIDTH                (1U)
#define DMA_TCD_CH17_ES_SAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_ES_SAE_SHIFT)) & DMA_TCD_CH17_ES_SAE_MASK)

#define DMA_TCD_CH17_ES_ERR_MASK                 (0x80000000U)
#define DMA_TCD_CH17_ES_ERR_SHIFT                (31U)
#define DMA_TCD_CH17_ES_ERR_WIDTH                (1U)
#define DMA_TCD_CH17_ES_ERR(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_ES_ERR_SHIFT)) & DMA_TCD_CH17_ES_ERR_MASK)
/*! @} */

/*! @name CH17_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH17_INT_INT_MASK                (0x1U)
#define DMA_TCD_CH17_INT_INT_SHIFT               (0U)
#define DMA_TCD_CH17_INT_INT_WIDTH               (1U)
#define DMA_TCD_CH17_INT_INT(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_INT_INT_SHIFT)) & DMA_TCD_CH17_INT_INT_MASK)
/*! @} */

/*! @name CH17_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH17_SBR_MID_MASK                (0xFU)
#define DMA_TCD_CH17_SBR_MID_SHIFT               (0U)
#define DMA_TCD_CH17_SBR_MID_WIDTH               (4U)
#define DMA_TCD_CH17_SBR_MID(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_SBR_MID_SHIFT)) & DMA_TCD_CH17_SBR_MID_MASK)

#define DMA_TCD_CH17_SBR_PAL_MASK                (0x8000U)
#define DMA_TCD_CH17_SBR_PAL_SHIFT               (15U)
#define DMA_TCD_CH17_SBR_PAL_WIDTH               (1U)
#define DMA_TCD_CH17_SBR_PAL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_SBR_PAL_SHIFT)) & DMA_TCD_CH17_SBR_PAL_MASK)

#define DMA_TCD_CH17_SBR_EMI_MASK                (0x10000U)
#define DMA_TCD_CH17_SBR_EMI_SHIFT               (16U)
#define DMA_TCD_CH17_SBR_EMI_WIDTH               (1U)
#define DMA_TCD_CH17_SBR_EMI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_SBR_EMI_SHIFT)) & DMA_TCD_CH17_SBR_EMI_MASK)

#define DMA_TCD_CH17_SBR_ATTR_MASK               (0xE0000U)
#define DMA_TCD_CH17_SBR_ATTR_SHIFT              (17U)
#define DMA_TCD_CH17_SBR_ATTR_WIDTH              (3U)
#define DMA_TCD_CH17_SBR_ATTR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_SBR_ATTR_SHIFT)) & DMA_TCD_CH17_SBR_ATTR_MASK)
/*! @} */

/*! @name CH17_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH17_PRI_APL_MASK                (0x7U)
#define DMA_TCD_CH17_PRI_APL_SHIFT               (0U)
#define DMA_TCD_CH17_PRI_APL_WIDTH               (3U)
#define DMA_TCD_CH17_PRI_APL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_PRI_APL_SHIFT)) & DMA_TCD_CH17_PRI_APL_MASK)

#define DMA_TCD_CH17_PRI_DPA_MASK                (0x40000000U)
#define DMA_TCD_CH17_PRI_DPA_SHIFT               (30U)
#define DMA_TCD_CH17_PRI_DPA_WIDTH               (1U)
#define DMA_TCD_CH17_PRI_DPA(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_PRI_DPA_SHIFT)) & DMA_TCD_CH17_PRI_DPA_MASK)

#define DMA_TCD_CH17_PRI_ECP_MASK                (0x80000000U)
#define DMA_TCD_CH17_PRI_ECP_SHIFT               (31U)
#define DMA_TCD_CH17_PRI_ECP_WIDTH               (1U)
#define DMA_TCD_CH17_PRI_ECP(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH17_PRI_ECP_SHIFT)) & DMA_TCD_CH17_PRI_ECP_MASK)
/*! @} */

/*! @name TCD17_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD17_SADDR_SADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD17_SADDR_SADDR_SHIFT          (0U)
#define DMA_TCD_TCD17_SADDR_SADDR_WIDTH          (32U)
#define DMA_TCD_TCD17_SADDR_SADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD17_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD17_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD17_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD17_SOFF_SOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD17_SOFF_SOFF_SHIFT            (0U)
#define DMA_TCD_TCD17_SOFF_SOFF_WIDTH            (16U)
#define DMA_TCD_TCD17_SOFF_SOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD17_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD17_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD17_ATTR_DSIZE_MASK            (0x7U)
#define DMA_TCD_TCD17_ATTR_DSIZE_SHIFT           (0U)
#define DMA_TCD_TCD17_ATTR_DSIZE_WIDTH           (3U)
#define DMA_TCD_TCD17_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD17_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD17_ATTR_DMOD_MASK             (0xF8U)
#define DMA_TCD_TCD17_ATTR_DMOD_SHIFT            (3U)
#define DMA_TCD_TCD17_ATTR_DMOD_WIDTH            (5U)
#define DMA_TCD_TCD17_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD17_ATTR_DMOD_MASK)

#define DMA_TCD_TCD17_ATTR_SSIZE_MASK            (0x700U)
#define DMA_TCD_TCD17_ATTR_SSIZE_SHIFT           (8U)
#define DMA_TCD_TCD17_ATTR_SSIZE_WIDTH           (3U)
#define DMA_TCD_TCD17_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD17_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD17_ATTR_SMOD_MASK             (0xF800U)
#define DMA_TCD_TCD17_ATTR_SMOD_SHIFT            (11U)
#define DMA_TCD_TCD17_ATTR_SMOD_WIDTH            (5U)
#define DMA_TCD_TCD17_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD17_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD17_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD17_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_TCD_TCD17_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD17_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD17_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD17_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD17_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD17_NBYTES_MLOFFNO_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD17_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD17_NBYTES_MLOFFNO_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD17_NBYTES_MLOFFNO_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD17_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD17_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD17_NBYTES_MLOFFNO_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD17_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD17_NBYTES_MLOFFNO_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD17_NBYTES_MLOFFNO_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD17_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD17_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD17_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD17_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD17_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD17_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD17_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD17_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD17_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD17_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_TCD_TCD17_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD17_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD17_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD17_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD17_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD17_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_TCD_TCD17_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD17_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD17_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD17_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD17_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD17_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_TCD_TCD17_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD17_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD17_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD17_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD17_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD17_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD17_SLAST_SDA_SLAST_SDA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD17_SLAST_SDA_SLAST_SDA_SHIFT  (0U)
#define DMA_TCD_TCD17_SLAST_SDA_SLAST_SDA_WIDTH  (32U)
#define DMA_TCD_TCD17_SLAST_SDA_SLAST_SDA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD17_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD17_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD17_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD17_DADDR_DADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD17_DADDR_DADDR_SHIFT          (0U)
#define DMA_TCD_TCD17_DADDR_DADDR_WIDTH          (32U)
#define DMA_TCD_TCD17_DADDR_DADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD17_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD17_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD17_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD17_DOFF_DOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD17_DOFF_DOFF_SHIFT            (0U)
#define DMA_TCD_TCD17_DOFF_DOFF_WIDTH            (16U)
#define DMA_TCD_TCD17_DOFF_DOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD17_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD17_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD17_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD17_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_TCD_TCD17_CITER_ELINKNO_CITER_WIDTH  (15U)
#define DMA_TCD_TCD17_CITER_ELINKNO_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD17_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD17_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD17_CITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD17_CITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD17_CITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD17_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD17_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD17_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_TCD_TCD17_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_TCD_TCD17_CITER_ELINKYES_CITER_WIDTH (9U)
#define DMA_TCD_TCD17_CITER_ELINKYES_CITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD17_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD17_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD17_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD17_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD17_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD17_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD17_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD17_CITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD17_CITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD17_CITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD17_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD17_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD17_DLAST_SGA_DLAST_SGA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD17_DLAST_SGA_DLAST_SGA_SHIFT  (0U)
#define DMA_TCD_TCD17_DLAST_SGA_DLAST_SGA_WIDTH  (32U)
#define DMA_TCD_TCD17_DLAST_SGA_DLAST_SGA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD17_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD17_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD17_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD17_CSR_START_MASK             (0x1U)
#define DMA_TCD_TCD17_CSR_START_SHIFT            (0U)
#define DMA_TCD_TCD17_CSR_START_WIDTH            (1U)
#define DMA_TCD_TCD17_CSR_START(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_CSR_START_SHIFT)) & DMA_TCD_TCD17_CSR_START_MASK)

#define DMA_TCD_TCD17_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_TCD_TCD17_CSR_INTMAJOR_SHIFT         (1U)
#define DMA_TCD_TCD17_CSR_INTMAJOR_WIDTH         (1U)
#define DMA_TCD_TCD17_CSR_INTMAJOR(x)            (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD17_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD17_CSR_INTHALF_MASK           (0x4U)
#define DMA_TCD_TCD17_CSR_INTHALF_SHIFT          (2U)
#define DMA_TCD_TCD17_CSR_INTHALF_WIDTH          (1U)
#define DMA_TCD_TCD17_CSR_INTHALF(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD17_CSR_INTHALF_MASK)

#define DMA_TCD_TCD17_CSR_DREQ_MASK              (0x8U)
#define DMA_TCD_TCD17_CSR_DREQ_SHIFT             (3U)
#define DMA_TCD_TCD17_CSR_DREQ_WIDTH             (1U)
#define DMA_TCD_TCD17_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_CSR_DREQ_SHIFT)) & DMA_TCD_TCD17_CSR_DREQ_MASK)

#define DMA_TCD_TCD17_CSR_ESG_MASK               (0x10U)
#define DMA_TCD_TCD17_CSR_ESG_SHIFT              (4U)
#define DMA_TCD_TCD17_CSR_ESG_WIDTH              (1U)
#define DMA_TCD_TCD17_CSR_ESG(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_CSR_ESG_SHIFT)) & DMA_TCD_TCD17_CSR_ESG_MASK)

#define DMA_TCD_TCD17_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_TCD_TCD17_CSR_MAJORELINK_SHIFT       (5U)
#define DMA_TCD_TCD17_CSR_MAJORELINK_WIDTH       (1U)
#define DMA_TCD_TCD17_CSR_MAJORELINK(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD17_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD17_CSR_EEOP_MASK              (0x40U)
#define DMA_TCD_TCD17_CSR_EEOP_SHIFT             (6U)
#define DMA_TCD_TCD17_CSR_EEOP_WIDTH             (1U)
#define DMA_TCD_TCD17_CSR_EEOP(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_CSR_EEOP_SHIFT)) & DMA_TCD_TCD17_CSR_EEOP_MASK)

#define DMA_TCD_TCD17_CSR_ESDA_MASK              (0x80U)
#define DMA_TCD_TCD17_CSR_ESDA_SHIFT             (7U)
#define DMA_TCD_TCD17_CSR_ESDA_WIDTH             (1U)
#define DMA_TCD_TCD17_CSR_ESDA(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_CSR_ESDA_SHIFT)) & DMA_TCD_TCD17_CSR_ESDA_MASK)

#define DMA_TCD_TCD17_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_TCD_TCD17_CSR_MAJORLINKCH_SHIFT      (8U)
#define DMA_TCD_TCD17_CSR_MAJORLINKCH_WIDTH      (5U)
#define DMA_TCD_TCD17_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD17_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD17_CSR_BWC_MASK               (0xC000U)
#define DMA_TCD_TCD17_CSR_BWC_SHIFT              (14U)
#define DMA_TCD_TCD17_CSR_BWC_WIDTH              (2U)
#define DMA_TCD_TCD17_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_CSR_BWC_SHIFT)) & DMA_TCD_TCD17_CSR_BWC_MASK)
/*! @} */

/*! @name TCD17_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD17_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD17_BITER_ELINKNO_BITER_SHIFT  (0U)
#define DMA_TCD_TCD17_BITER_ELINKNO_BITER_WIDTH  (15U)
#define DMA_TCD_TCD17_BITER_ELINKNO_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD17_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD17_BITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD17_BITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD17_BITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD17_BITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD17_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD17_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD17_BITER_ELINKYES_BITER_MASK  (0x1FFU)
#define DMA_TCD_TCD17_BITER_ELINKYES_BITER_SHIFT (0U)
#define DMA_TCD_TCD17_BITER_ELINKYES_BITER_WIDTH (9U)
#define DMA_TCD_TCD17_BITER_ELINKYES_BITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD17_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD17_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD17_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD17_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD17_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD17_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD17_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD17_BITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD17_BITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD17_BITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD17_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD17_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH18_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH18_CSR_ERQ_MASK                (0x1U)
#define DMA_TCD_CH18_CSR_ERQ_SHIFT               (0U)
#define DMA_TCD_CH18_CSR_ERQ_WIDTH               (1U)
#define DMA_TCD_CH18_CSR_ERQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_CSR_ERQ_SHIFT)) & DMA_TCD_CH18_CSR_ERQ_MASK)

#define DMA_TCD_CH18_CSR_EARQ_MASK               (0x2U)
#define DMA_TCD_CH18_CSR_EARQ_SHIFT              (1U)
#define DMA_TCD_CH18_CSR_EARQ_WIDTH              (1U)
#define DMA_TCD_CH18_CSR_EARQ(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_CSR_EARQ_SHIFT)) & DMA_TCD_CH18_CSR_EARQ_MASK)

#define DMA_TCD_CH18_CSR_EEI_MASK                (0x4U)
#define DMA_TCD_CH18_CSR_EEI_SHIFT               (2U)
#define DMA_TCD_CH18_CSR_EEI_WIDTH               (1U)
#define DMA_TCD_CH18_CSR_EEI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_CSR_EEI_SHIFT)) & DMA_TCD_CH18_CSR_EEI_MASK)

#define DMA_TCD_CH18_CSR_EBW_MASK                (0x8U)
#define DMA_TCD_CH18_CSR_EBW_SHIFT               (3U)
#define DMA_TCD_CH18_CSR_EBW_WIDTH               (1U)
#define DMA_TCD_CH18_CSR_EBW(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_CSR_EBW_SHIFT)) & DMA_TCD_CH18_CSR_EBW_MASK)

#define DMA_TCD_CH18_CSR_DONE_MASK               (0x40000000U)
#define DMA_TCD_CH18_CSR_DONE_SHIFT              (30U)
#define DMA_TCD_CH18_CSR_DONE_WIDTH              (1U)
#define DMA_TCD_CH18_CSR_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_CSR_DONE_SHIFT)) & DMA_TCD_CH18_CSR_DONE_MASK)

#define DMA_TCD_CH18_CSR_ACTIVE_MASK             (0x80000000U)
#define DMA_TCD_CH18_CSR_ACTIVE_SHIFT            (31U)
#define DMA_TCD_CH18_CSR_ACTIVE_WIDTH            (1U)
#define DMA_TCD_CH18_CSR_ACTIVE(x)               (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH18_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH18_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH18_ES_DBE_MASK                 (0x1U)
#define DMA_TCD_CH18_ES_DBE_SHIFT                (0U)
#define DMA_TCD_CH18_ES_DBE_WIDTH                (1U)
#define DMA_TCD_CH18_ES_DBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_ES_DBE_SHIFT)) & DMA_TCD_CH18_ES_DBE_MASK)

#define DMA_TCD_CH18_ES_SBE_MASK                 (0x2U)
#define DMA_TCD_CH18_ES_SBE_SHIFT                (1U)
#define DMA_TCD_CH18_ES_SBE_WIDTH                (1U)
#define DMA_TCD_CH18_ES_SBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_ES_SBE_SHIFT)) & DMA_TCD_CH18_ES_SBE_MASK)

#define DMA_TCD_CH18_ES_SGE_MASK                 (0x4U)
#define DMA_TCD_CH18_ES_SGE_SHIFT                (2U)
#define DMA_TCD_CH18_ES_SGE_WIDTH                (1U)
#define DMA_TCD_CH18_ES_SGE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_ES_SGE_SHIFT)) & DMA_TCD_CH18_ES_SGE_MASK)

#define DMA_TCD_CH18_ES_NCE_MASK                 (0x8U)
#define DMA_TCD_CH18_ES_NCE_SHIFT                (3U)
#define DMA_TCD_CH18_ES_NCE_WIDTH                (1U)
#define DMA_TCD_CH18_ES_NCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_ES_NCE_SHIFT)) & DMA_TCD_CH18_ES_NCE_MASK)

#define DMA_TCD_CH18_ES_DOE_MASK                 (0x10U)
#define DMA_TCD_CH18_ES_DOE_SHIFT                (4U)
#define DMA_TCD_CH18_ES_DOE_WIDTH                (1U)
#define DMA_TCD_CH18_ES_DOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_ES_DOE_SHIFT)) & DMA_TCD_CH18_ES_DOE_MASK)

#define DMA_TCD_CH18_ES_DAE_MASK                 (0x20U)
#define DMA_TCD_CH18_ES_DAE_SHIFT                (5U)
#define DMA_TCD_CH18_ES_DAE_WIDTH                (1U)
#define DMA_TCD_CH18_ES_DAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_ES_DAE_SHIFT)) & DMA_TCD_CH18_ES_DAE_MASK)

#define DMA_TCD_CH18_ES_SOE_MASK                 (0x40U)
#define DMA_TCD_CH18_ES_SOE_SHIFT                (6U)
#define DMA_TCD_CH18_ES_SOE_WIDTH                (1U)
#define DMA_TCD_CH18_ES_SOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_ES_SOE_SHIFT)) & DMA_TCD_CH18_ES_SOE_MASK)

#define DMA_TCD_CH18_ES_SAE_MASK                 (0x80U)
#define DMA_TCD_CH18_ES_SAE_SHIFT                (7U)
#define DMA_TCD_CH18_ES_SAE_WIDTH                (1U)
#define DMA_TCD_CH18_ES_SAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_ES_SAE_SHIFT)) & DMA_TCD_CH18_ES_SAE_MASK)

#define DMA_TCD_CH18_ES_ERR_MASK                 (0x80000000U)
#define DMA_TCD_CH18_ES_ERR_SHIFT                (31U)
#define DMA_TCD_CH18_ES_ERR_WIDTH                (1U)
#define DMA_TCD_CH18_ES_ERR(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_ES_ERR_SHIFT)) & DMA_TCD_CH18_ES_ERR_MASK)
/*! @} */

/*! @name CH18_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH18_INT_INT_MASK                (0x1U)
#define DMA_TCD_CH18_INT_INT_SHIFT               (0U)
#define DMA_TCD_CH18_INT_INT_WIDTH               (1U)
#define DMA_TCD_CH18_INT_INT(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_INT_INT_SHIFT)) & DMA_TCD_CH18_INT_INT_MASK)
/*! @} */

/*! @name CH18_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH18_SBR_MID_MASK                (0xFU)
#define DMA_TCD_CH18_SBR_MID_SHIFT               (0U)
#define DMA_TCD_CH18_SBR_MID_WIDTH               (4U)
#define DMA_TCD_CH18_SBR_MID(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_SBR_MID_SHIFT)) & DMA_TCD_CH18_SBR_MID_MASK)

#define DMA_TCD_CH18_SBR_PAL_MASK                (0x8000U)
#define DMA_TCD_CH18_SBR_PAL_SHIFT               (15U)
#define DMA_TCD_CH18_SBR_PAL_WIDTH               (1U)
#define DMA_TCD_CH18_SBR_PAL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_SBR_PAL_SHIFT)) & DMA_TCD_CH18_SBR_PAL_MASK)

#define DMA_TCD_CH18_SBR_EMI_MASK                (0x10000U)
#define DMA_TCD_CH18_SBR_EMI_SHIFT               (16U)
#define DMA_TCD_CH18_SBR_EMI_WIDTH               (1U)
#define DMA_TCD_CH18_SBR_EMI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_SBR_EMI_SHIFT)) & DMA_TCD_CH18_SBR_EMI_MASK)

#define DMA_TCD_CH18_SBR_ATTR_MASK               (0xE0000U)
#define DMA_TCD_CH18_SBR_ATTR_SHIFT              (17U)
#define DMA_TCD_CH18_SBR_ATTR_WIDTH              (3U)
#define DMA_TCD_CH18_SBR_ATTR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_SBR_ATTR_SHIFT)) & DMA_TCD_CH18_SBR_ATTR_MASK)
/*! @} */

/*! @name CH18_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH18_PRI_APL_MASK                (0x7U)
#define DMA_TCD_CH18_PRI_APL_SHIFT               (0U)
#define DMA_TCD_CH18_PRI_APL_WIDTH               (3U)
#define DMA_TCD_CH18_PRI_APL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_PRI_APL_SHIFT)) & DMA_TCD_CH18_PRI_APL_MASK)

#define DMA_TCD_CH18_PRI_DPA_MASK                (0x40000000U)
#define DMA_TCD_CH18_PRI_DPA_SHIFT               (30U)
#define DMA_TCD_CH18_PRI_DPA_WIDTH               (1U)
#define DMA_TCD_CH18_PRI_DPA(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_PRI_DPA_SHIFT)) & DMA_TCD_CH18_PRI_DPA_MASK)

#define DMA_TCD_CH18_PRI_ECP_MASK                (0x80000000U)
#define DMA_TCD_CH18_PRI_ECP_SHIFT               (31U)
#define DMA_TCD_CH18_PRI_ECP_WIDTH               (1U)
#define DMA_TCD_CH18_PRI_ECP(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH18_PRI_ECP_SHIFT)) & DMA_TCD_CH18_PRI_ECP_MASK)
/*! @} */

/*! @name TCD18_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD18_SADDR_SADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD18_SADDR_SADDR_SHIFT          (0U)
#define DMA_TCD_TCD18_SADDR_SADDR_WIDTH          (32U)
#define DMA_TCD_TCD18_SADDR_SADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD18_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD18_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD18_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD18_SOFF_SOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD18_SOFF_SOFF_SHIFT            (0U)
#define DMA_TCD_TCD18_SOFF_SOFF_WIDTH            (16U)
#define DMA_TCD_TCD18_SOFF_SOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD18_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD18_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD18_ATTR_DSIZE_MASK            (0x7U)
#define DMA_TCD_TCD18_ATTR_DSIZE_SHIFT           (0U)
#define DMA_TCD_TCD18_ATTR_DSIZE_WIDTH           (3U)
#define DMA_TCD_TCD18_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD18_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD18_ATTR_DMOD_MASK             (0xF8U)
#define DMA_TCD_TCD18_ATTR_DMOD_SHIFT            (3U)
#define DMA_TCD_TCD18_ATTR_DMOD_WIDTH            (5U)
#define DMA_TCD_TCD18_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD18_ATTR_DMOD_MASK)

#define DMA_TCD_TCD18_ATTR_SSIZE_MASK            (0x700U)
#define DMA_TCD_TCD18_ATTR_SSIZE_SHIFT           (8U)
#define DMA_TCD_TCD18_ATTR_SSIZE_WIDTH           (3U)
#define DMA_TCD_TCD18_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD18_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD18_ATTR_SMOD_MASK             (0xF800U)
#define DMA_TCD_TCD18_ATTR_SMOD_SHIFT            (11U)
#define DMA_TCD_TCD18_ATTR_SMOD_WIDTH            (5U)
#define DMA_TCD_TCD18_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD18_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD18_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD18_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_TCD_TCD18_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD18_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD18_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD18_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD18_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD18_NBYTES_MLOFFNO_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD18_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD18_NBYTES_MLOFFNO_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD18_NBYTES_MLOFFNO_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD18_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD18_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD18_NBYTES_MLOFFNO_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD18_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD18_NBYTES_MLOFFNO_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD18_NBYTES_MLOFFNO_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD18_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD18_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD18_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD18_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD18_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD18_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD18_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD18_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD18_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD18_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_TCD_TCD18_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD18_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD18_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD18_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD18_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD18_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_TCD_TCD18_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD18_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD18_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD18_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD18_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD18_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_TCD_TCD18_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD18_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD18_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD18_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD18_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD18_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD18_SLAST_SDA_SLAST_SDA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD18_SLAST_SDA_SLAST_SDA_SHIFT  (0U)
#define DMA_TCD_TCD18_SLAST_SDA_SLAST_SDA_WIDTH  (32U)
#define DMA_TCD_TCD18_SLAST_SDA_SLAST_SDA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD18_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD18_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD18_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD18_DADDR_DADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD18_DADDR_DADDR_SHIFT          (0U)
#define DMA_TCD_TCD18_DADDR_DADDR_WIDTH          (32U)
#define DMA_TCD_TCD18_DADDR_DADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD18_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD18_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD18_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD18_DOFF_DOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD18_DOFF_DOFF_SHIFT            (0U)
#define DMA_TCD_TCD18_DOFF_DOFF_WIDTH            (16U)
#define DMA_TCD_TCD18_DOFF_DOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD18_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD18_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD18_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD18_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_TCD_TCD18_CITER_ELINKNO_CITER_WIDTH  (15U)
#define DMA_TCD_TCD18_CITER_ELINKNO_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD18_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD18_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD18_CITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD18_CITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD18_CITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD18_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD18_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD18_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_TCD_TCD18_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_TCD_TCD18_CITER_ELINKYES_CITER_WIDTH (9U)
#define DMA_TCD_TCD18_CITER_ELINKYES_CITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD18_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD18_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD18_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD18_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD18_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD18_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD18_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD18_CITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD18_CITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD18_CITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD18_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD18_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD18_DLAST_SGA_DLAST_SGA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD18_DLAST_SGA_DLAST_SGA_SHIFT  (0U)
#define DMA_TCD_TCD18_DLAST_SGA_DLAST_SGA_WIDTH  (32U)
#define DMA_TCD_TCD18_DLAST_SGA_DLAST_SGA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD18_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD18_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD18_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD18_CSR_START_MASK             (0x1U)
#define DMA_TCD_TCD18_CSR_START_SHIFT            (0U)
#define DMA_TCD_TCD18_CSR_START_WIDTH            (1U)
#define DMA_TCD_TCD18_CSR_START(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_CSR_START_SHIFT)) & DMA_TCD_TCD18_CSR_START_MASK)

#define DMA_TCD_TCD18_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_TCD_TCD18_CSR_INTMAJOR_SHIFT         (1U)
#define DMA_TCD_TCD18_CSR_INTMAJOR_WIDTH         (1U)
#define DMA_TCD_TCD18_CSR_INTMAJOR(x)            (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD18_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD18_CSR_INTHALF_MASK           (0x4U)
#define DMA_TCD_TCD18_CSR_INTHALF_SHIFT          (2U)
#define DMA_TCD_TCD18_CSR_INTHALF_WIDTH          (1U)
#define DMA_TCD_TCD18_CSR_INTHALF(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD18_CSR_INTHALF_MASK)

#define DMA_TCD_TCD18_CSR_DREQ_MASK              (0x8U)
#define DMA_TCD_TCD18_CSR_DREQ_SHIFT             (3U)
#define DMA_TCD_TCD18_CSR_DREQ_WIDTH             (1U)
#define DMA_TCD_TCD18_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_CSR_DREQ_SHIFT)) & DMA_TCD_TCD18_CSR_DREQ_MASK)

#define DMA_TCD_TCD18_CSR_ESG_MASK               (0x10U)
#define DMA_TCD_TCD18_CSR_ESG_SHIFT              (4U)
#define DMA_TCD_TCD18_CSR_ESG_WIDTH              (1U)
#define DMA_TCD_TCD18_CSR_ESG(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_CSR_ESG_SHIFT)) & DMA_TCD_TCD18_CSR_ESG_MASK)

#define DMA_TCD_TCD18_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_TCD_TCD18_CSR_MAJORELINK_SHIFT       (5U)
#define DMA_TCD_TCD18_CSR_MAJORELINK_WIDTH       (1U)
#define DMA_TCD_TCD18_CSR_MAJORELINK(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD18_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD18_CSR_EEOP_MASK              (0x40U)
#define DMA_TCD_TCD18_CSR_EEOP_SHIFT             (6U)
#define DMA_TCD_TCD18_CSR_EEOP_WIDTH             (1U)
#define DMA_TCD_TCD18_CSR_EEOP(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_CSR_EEOP_SHIFT)) & DMA_TCD_TCD18_CSR_EEOP_MASK)

#define DMA_TCD_TCD18_CSR_ESDA_MASK              (0x80U)
#define DMA_TCD_TCD18_CSR_ESDA_SHIFT             (7U)
#define DMA_TCD_TCD18_CSR_ESDA_WIDTH             (1U)
#define DMA_TCD_TCD18_CSR_ESDA(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_CSR_ESDA_SHIFT)) & DMA_TCD_TCD18_CSR_ESDA_MASK)

#define DMA_TCD_TCD18_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_TCD_TCD18_CSR_MAJORLINKCH_SHIFT      (8U)
#define DMA_TCD_TCD18_CSR_MAJORLINKCH_WIDTH      (5U)
#define DMA_TCD_TCD18_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD18_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD18_CSR_BWC_MASK               (0xC000U)
#define DMA_TCD_TCD18_CSR_BWC_SHIFT              (14U)
#define DMA_TCD_TCD18_CSR_BWC_WIDTH              (2U)
#define DMA_TCD_TCD18_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_CSR_BWC_SHIFT)) & DMA_TCD_TCD18_CSR_BWC_MASK)
/*! @} */

/*! @name TCD18_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD18_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD18_BITER_ELINKNO_BITER_SHIFT  (0U)
#define DMA_TCD_TCD18_BITER_ELINKNO_BITER_WIDTH  (15U)
#define DMA_TCD_TCD18_BITER_ELINKNO_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD18_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD18_BITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD18_BITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD18_BITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD18_BITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD18_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD18_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD18_BITER_ELINKYES_BITER_MASK  (0x1FFU)
#define DMA_TCD_TCD18_BITER_ELINKYES_BITER_SHIFT (0U)
#define DMA_TCD_TCD18_BITER_ELINKYES_BITER_WIDTH (9U)
#define DMA_TCD_TCD18_BITER_ELINKYES_BITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD18_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD18_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD18_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD18_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD18_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD18_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD18_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD18_BITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD18_BITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD18_BITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD18_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD18_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH19_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH19_CSR_ERQ_MASK                (0x1U)
#define DMA_TCD_CH19_CSR_ERQ_SHIFT               (0U)
#define DMA_TCD_CH19_CSR_ERQ_WIDTH               (1U)
#define DMA_TCD_CH19_CSR_ERQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_CSR_ERQ_SHIFT)) & DMA_TCD_CH19_CSR_ERQ_MASK)

#define DMA_TCD_CH19_CSR_EARQ_MASK               (0x2U)
#define DMA_TCD_CH19_CSR_EARQ_SHIFT              (1U)
#define DMA_TCD_CH19_CSR_EARQ_WIDTH              (1U)
#define DMA_TCD_CH19_CSR_EARQ(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_CSR_EARQ_SHIFT)) & DMA_TCD_CH19_CSR_EARQ_MASK)

#define DMA_TCD_CH19_CSR_EEI_MASK                (0x4U)
#define DMA_TCD_CH19_CSR_EEI_SHIFT               (2U)
#define DMA_TCD_CH19_CSR_EEI_WIDTH               (1U)
#define DMA_TCD_CH19_CSR_EEI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_CSR_EEI_SHIFT)) & DMA_TCD_CH19_CSR_EEI_MASK)

#define DMA_TCD_CH19_CSR_EBW_MASK                (0x8U)
#define DMA_TCD_CH19_CSR_EBW_SHIFT               (3U)
#define DMA_TCD_CH19_CSR_EBW_WIDTH               (1U)
#define DMA_TCD_CH19_CSR_EBW(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_CSR_EBW_SHIFT)) & DMA_TCD_CH19_CSR_EBW_MASK)

#define DMA_TCD_CH19_CSR_DONE_MASK               (0x40000000U)
#define DMA_TCD_CH19_CSR_DONE_SHIFT              (30U)
#define DMA_TCD_CH19_CSR_DONE_WIDTH              (1U)
#define DMA_TCD_CH19_CSR_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_CSR_DONE_SHIFT)) & DMA_TCD_CH19_CSR_DONE_MASK)

#define DMA_TCD_CH19_CSR_ACTIVE_MASK             (0x80000000U)
#define DMA_TCD_CH19_CSR_ACTIVE_SHIFT            (31U)
#define DMA_TCD_CH19_CSR_ACTIVE_WIDTH            (1U)
#define DMA_TCD_CH19_CSR_ACTIVE(x)               (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH19_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH19_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH19_ES_DBE_MASK                 (0x1U)
#define DMA_TCD_CH19_ES_DBE_SHIFT                (0U)
#define DMA_TCD_CH19_ES_DBE_WIDTH                (1U)
#define DMA_TCD_CH19_ES_DBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_ES_DBE_SHIFT)) & DMA_TCD_CH19_ES_DBE_MASK)

#define DMA_TCD_CH19_ES_SBE_MASK                 (0x2U)
#define DMA_TCD_CH19_ES_SBE_SHIFT                (1U)
#define DMA_TCD_CH19_ES_SBE_WIDTH                (1U)
#define DMA_TCD_CH19_ES_SBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_ES_SBE_SHIFT)) & DMA_TCD_CH19_ES_SBE_MASK)

#define DMA_TCD_CH19_ES_SGE_MASK                 (0x4U)
#define DMA_TCD_CH19_ES_SGE_SHIFT                (2U)
#define DMA_TCD_CH19_ES_SGE_WIDTH                (1U)
#define DMA_TCD_CH19_ES_SGE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_ES_SGE_SHIFT)) & DMA_TCD_CH19_ES_SGE_MASK)

#define DMA_TCD_CH19_ES_NCE_MASK                 (0x8U)
#define DMA_TCD_CH19_ES_NCE_SHIFT                (3U)
#define DMA_TCD_CH19_ES_NCE_WIDTH                (1U)
#define DMA_TCD_CH19_ES_NCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_ES_NCE_SHIFT)) & DMA_TCD_CH19_ES_NCE_MASK)

#define DMA_TCD_CH19_ES_DOE_MASK                 (0x10U)
#define DMA_TCD_CH19_ES_DOE_SHIFT                (4U)
#define DMA_TCD_CH19_ES_DOE_WIDTH                (1U)
#define DMA_TCD_CH19_ES_DOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_ES_DOE_SHIFT)) & DMA_TCD_CH19_ES_DOE_MASK)

#define DMA_TCD_CH19_ES_DAE_MASK                 (0x20U)
#define DMA_TCD_CH19_ES_DAE_SHIFT                (5U)
#define DMA_TCD_CH19_ES_DAE_WIDTH                (1U)
#define DMA_TCD_CH19_ES_DAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_ES_DAE_SHIFT)) & DMA_TCD_CH19_ES_DAE_MASK)

#define DMA_TCD_CH19_ES_SOE_MASK                 (0x40U)
#define DMA_TCD_CH19_ES_SOE_SHIFT                (6U)
#define DMA_TCD_CH19_ES_SOE_WIDTH                (1U)
#define DMA_TCD_CH19_ES_SOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_ES_SOE_SHIFT)) & DMA_TCD_CH19_ES_SOE_MASK)

#define DMA_TCD_CH19_ES_SAE_MASK                 (0x80U)
#define DMA_TCD_CH19_ES_SAE_SHIFT                (7U)
#define DMA_TCD_CH19_ES_SAE_WIDTH                (1U)
#define DMA_TCD_CH19_ES_SAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_ES_SAE_SHIFT)) & DMA_TCD_CH19_ES_SAE_MASK)

#define DMA_TCD_CH19_ES_ERR_MASK                 (0x80000000U)
#define DMA_TCD_CH19_ES_ERR_SHIFT                (31U)
#define DMA_TCD_CH19_ES_ERR_WIDTH                (1U)
#define DMA_TCD_CH19_ES_ERR(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_ES_ERR_SHIFT)) & DMA_TCD_CH19_ES_ERR_MASK)
/*! @} */

/*! @name CH19_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH19_INT_INT_MASK                (0x1U)
#define DMA_TCD_CH19_INT_INT_SHIFT               (0U)
#define DMA_TCD_CH19_INT_INT_WIDTH               (1U)
#define DMA_TCD_CH19_INT_INT(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_INT_INT_SHIFT)) & DMA_TCD_CH19_INT_INT_MASK)
/*! @} */

/*! @name CH19_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH19_SBR_MID_MASK                (0xFU)
#define DMA_TCD_CH19_SBR_MID_SHIFT               (0U)
#define DMA_TCD_CH19_SBR_MID_WIDTH               (4U)
#define DMA_TCD_CH19_SBR_MID(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_SBR_MID_SHIFT)) & DMA_TCD_CH19_SBR_MID_MASK)

#define DMA_TCD_CH19_SBR_PAL_MASK                (0x8000U)
#define DMA_TCD_CH19_SBR_PAL_SHIFT               (15U)
#define DMA_TCD_CH19_SBR_PAL_WIDTH               (1U)
#define DMA_TCD_CH19_SBR_PAL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_SBR_PAL_SHIFT)) & DMA_TCD_CH19_SBR_PAL_MASK)

#define DMA_TCD_CH19_SBR_EMI_MASK                (0x10000U)
#define DMA_TCD_CH19_SBR_EMI_SHIFT               (16U)
#define DMA_TCD_CH19_SBR_EMI_WIDTH               (1U)
#define DMA_TCD_CH19_SBR_EMI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_SBR_EMI_SHIFT)) & DMA_TCD_CH19_SBR_EMI_MASK)

#define DMA_TCD_CH19_SBR_ATTR_MASK               (0xE0000U)
#define DMA_TCD_CH19_SBR_ATTR_SHIFT              (17U)
#define DMA_TCD_CH19_SBR_ATTR_WIDTH              (3U)
#define DMA_TCD_CH19_SBR_ATTR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_SBR_ATTR_SHIFT)) & DMA_TCD_CH19_SBR_ATTR_MASK)
/*! @} */

/*! @name CH19_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH19_PRI_APL_MASK                (0x7U)
#define DMA_TCD_CH19_PRI_APL_SHIFT               (0U)
#define DMA_TCD_CH19_PRI_APL_WIDTH               (3U)
#define DMA_TCD_CH19_PRI_APL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_PRI_APL_SHIFT)) & DMA_TCD_CH19_PRI_APL_MASK)

#define DMA_TCD_CH19_PRI_DPA_MASK                (0x40000000U)
#define DMA_TCD_CH19_PRI_DPA_SHIFT               (30U)
#define DMA_TCD_CH19_PRI_DPA_WIDTH               (1U)
#define DMA_TCD_CH19_PRI_DPA(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_PRI_DPA_SHIFT)) & DMA_TCD_CH19_PRI_DPA_MASK)

#define DMA_TCD_CH19_PRI_ECP_MASK                (0x80000000U)
#define DMA_TCD_CH19_PRI_ECP_SHIFT               (31U)
#define DMA_TCD_CH19_PRI_ECP_WIDTH               (1U)
#define DMA_TCD_CH19_PRI_ECP(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH19_PRI_ECP_SHIFT)) & DMA_TCD_CH19_PRI_ECP_MASK)
/*! @} */

/*! @name TCD19_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD19_SADDR_SADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD19_SADDR_SADDR_SHIFT          (0U)
#define DMA_TCD_TCD19_SADDR_SADDR_WIDTH          (32U)
#define DMA_TCD_TCD19_SADDR_SADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD19_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD19_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD19_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD19_SOFF_SOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD19_SOFF_SOFF_SHIFT            (0U)
#define DMA_TCD_TCD19_SOFF_SOFF_WIDTH            (16U)
#define DMA_TCD_TCD19_SOFF_SOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD19_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD19_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD19_ATTR_DSIZE_MASK            (0x7U)
#define DMA_TCD_TCD19_ATTR_DSIZE_SHIFT           (0U)
#define DMA_TCD_TCD19_ATTR_DSIZE_WIDTH           (3U)
#define DMA_TCD_TCD19_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD19_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD19_ATTR_DMOD_MASK             (0xF8U)
#define DMA_TCD_TCD19_ATTR_DMOD_SHIFT            (3U)
#define DMA_TCD_TCD19_ATTR_DMOD_WIDTH            (5U)
#define DMA_TCD_TCD19_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD19_ATTR_DMOD_MASK)

#define DMA_TCD_TCD19_ATTR_SSIZE_MASK            (0x700U)
#define DMA_TCD_TCD19_ATTR_SSIZE_SHIFT           (8U)
#define DMA_TCD_TCD19_ATTR_SSIZE_WIDTH           (3U)
#define DMA_TCD_TCD19_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD19_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD19_ATTR_SMOD_MASK             (0xF800U)
#define DMA_TCD_TCD19_ATTR_SMOD_SHIFT            (11U)
#define DMA_TCD_TCD19_ATTR_SMOD_WIDTH            (5U)
#define DMA_TCD_TCD19_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD19_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD19_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD19_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_TCD_TCD19_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD19_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD19_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD19_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD19_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD19_NBYTES_MLOFFNO_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD19_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD19_NBYTES_MLOFFNO_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD19_NBYTES_MLOFFNO_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD19_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD19_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD19_NBYTES_MLOFFNO_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD19_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD19_NBYTES_MLOFFNO_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD19_NBYTES_MLOFFNO_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD19_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD19_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD19_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD19_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD19_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD19_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD19_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD19_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD19_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD19_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_TCD_TCD19_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD19_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD19_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD19_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD19_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD19_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_TCD_TCD19_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD19_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD19_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD19_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD19_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD19_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_TCD_TCD19_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD19_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD19_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD19_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD19_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD19_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD19_SLAST_SDA_SLAST_SDA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD19_SLAST_SDA_SLAST_SDA_SHIFT  (0U)
#define DMA_TCD_TCD19_SLAST_SDA_SLAST_SDA_WIDTH  (32U)
#define DMA_TCD_TCD19_SLAST_SDA_SLAST_SDA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD19_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD19_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD19_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD19_DADDR_DADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD19_DADDR_DADDR_SHIFT          (0U)
#define DMA_TCD_TCD19_DADDR_DADDR_WIDTH          (32U)
#define DMA_TCD_TCD19_DADDR_DADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD19_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD19_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD19_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD19_DOFF_DOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD19_DOFF_DOFF_SHIFT            (0U)
#define DMA_TCD_TCD19_DOFF_DOFF_WIDTH            (16U)
#define DMA_TCD_TCD19_DOFF_DOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD19_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD19_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD19_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD19_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_TCD_TCD19_CITER_ELINKNO_CITER_WIDTH  (15U)
#define DMA_TCD_TCD19_CITER_ELINKNO_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD19_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD19_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD19_CITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD19_CITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD19_CITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD19_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD19_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD19_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_TCD_TCD19_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_TCD_TCD19_CITER_ELINKYES_CITER_WIDTH (9U)
#define DMA_TCD_TCD19_CITER_ELINKYES_CITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD19_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD19_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD19_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD19_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD19_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD19_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD19_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD19_CITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD19_CITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD19_CITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD19_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD19_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD19_DLAST_SGA_DLAST_SGA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD19_DLAST_SGA_DLAST_SGA_SHIFT  (0U)
#define DMA_TCD_TCD19_DLAST_SGA_DLAST_SGA_WIDTH  (32U)
#define DMA_TCD_TCD19_DLAST_SGA_DLAST_SGA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD19_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD19_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD19_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD19_CSR_START_MASK             (0x1U)
#define DMA_TCD_TCD19_CSR_START_SHIFT            (0U)
#define DMA_TCD_TCD19_CSR_START_WIDTH            (1U)
#define DMA_TCD_TCD19_CSR_START(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_CSR_START_SHIFT)) & DMA_TCD_TCD19_CSR_START_MASK)

#define DMA_TCD_TCD19_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_TCD_TCD19_CSR_INTMAJOR_SHIFT         (1U)
#define DMA_TCD_TCD19_CSR_INTMAJOR_WIDTH         (1U)
#define DMA_TCD_TCD19_CSR_INTMAJOR(x)            (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD19_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD19_CSR_INTHALF_MASK           (0x4U)
#define DMA_TCD_TCD19_CSR_INTHALF_SHIFT          (2U)
#define DMA_TCD_TCD19_CSR_INTHALF_WIDTH          (1U)
#define DMA_TCD_TCD19_CSR_INTHALF(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD19_CSR_INTHALF_MASK)

#define DMA_TCD_TCD19_CSR_DREQ_MASK              (0x8U)
#define DMA_TCD_TCD19_CSR_DREQ_SHIFT             (3U)
#define DMA_TCD_TCD19_CSR_DREQ_WIDTH             (1U)
#define DMA_TCD_TCD19_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_CSR_DREQ_SHIFT)) & DMA_TCD_TCD19_CSR_DREQ_MASK)

#define DMA_TCD_TCD19_CSR_ESG_MASK               (0x10U)
#define DMA_TCD_TCD19_CSR_ESG_SHIFT              (4U)
#define DMA_TCD_TCD19_CSR_ESG_WIDTH              (1U)
#define DMA_TCD_TCD19_CSR_ESG(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_CSR_ESG_SHIFT)) & DMA_TCD_TCD19_CSR_ESG_MASK)

#define DMA_TCD_TCD19_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_TCD_TCD19_CSR_MAJORELINK_SHIFT       (5U)
#define DMA_TCD_TCD19_CSR_MAJORELINK_WIDTH       (1U)
#define DMA_TCD_TCD19_CSR_MAJORELINK(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD19_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD19_CSR_EEOP_MASK              (0x40U)
#define DMA_TCD_TCD19_CSR_EEOP_SHIFT             (6U)
#define DMA_TCD_TCD19_CSR_EEOP_WIDTH             (1U)
#define DMA_TCD_TCD19_CSR_EEOP(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_CSR_EEOP_SHIFT)) & DMA_TCD_TCD19_CSR_EEOP_MASK)

#define DMA_TCD_TCD19_CSR_ESDA_MASK              (0x80U)
#define DMA_TCD_TCD19_CSR_ESDA_SHIFT             (7U)
#define DMA_TCD_TCD19_CSR_ESDA_WIDTH             (1U)
#define DMA_TCD_TCD19_CSR_ESDA(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_CSR_ESDA_SHIFT)) & DMA_TCD_TCD19_CSR_ESDA_MASK)

#define DMA_TCD_TCD19_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_TCD_TCD19_CSR_MAJORLINKCH_SHIFT      (8U)
#define DMA_TCD_TCD19_CSR_MAJORLINKCH_WIDTH      (5U)
#define DMA_TCD_TCD19_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD19_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD19_CSR_BWC_MASK               (0xC000U)
#define DMA_TCD_TCD19_CSR_BWC_SHIFT              (14U)
#define DMA_TCD_TCD19_CSR_BWC_WIDTH              (2U)
#define DMA_TCD_TCD19_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_CSR_BWC_SHIFT)) & DMA_TCD_TCD19_CSR_BWC_MASK)
/*! @} */

/*! @name TCD19_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD19_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD19_BITER_ELINKNO_BITER_SHIFT  (0U)
#define DMA_TCD_TCD19_BITER_ELINKNO_BITER_WIDTH  (15U)
#define DMA_TCD_TCD19_BITER_ELINKNO_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD19_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD19_BITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD19_BITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD19_BITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD19_BITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD19_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD19_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD19_BITER_ELINKYES_BITER_MASK  (0x1FFU)
#define DMA_TCD_TCD19_BITER_ELINKYES_BITER_SHIFT (0U)
#define DMA_TCD_TCD19_BITER_ELINKYES_BITER_WIDTH (9U)
#define DMA_TCD_TCD19_BITER_ELINKYES_BITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD19_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD19_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD19_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD19_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD19_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD19_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD19_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD19_BITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD19_BITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD19_BITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD19_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD19_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH20_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH20_CSR_ERQ_MASK                (0x1U)
#define DMA_TCD_CH20_CSR_ERQ_SHIFT               (0U)
#define DMA_TCD_CH20_CSR_ERQ_WIDTH               (1U)
#define DMA_TCD_CH20_CSR_ERQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_CSR_ERQ_SHIFT)) & DMA_TCD_CH20_CSR_ERQ_MASK)

#define DMA_TCD_CH20_CSR_EARQ_MASK               (0x2U)
#define DMA_TCD_CH20_CSR_EARQ_SHIFT              (1U)
#define DMA_TCD_CH20_CSR_EARQ_WIDTH              (1U)
#define DMA_TCD_CH20_CSR_EARQ(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_CSR_EARQ_SHIFT)) & DMA_TCD_CH20_CSR_EARQ_MASK)

#define DMA_TCD_CH20_CSR_EEI_MASK                (0x4U)
#define DMA_TCD_CH20_CSR_EEI_SHIFT               (2U)
#define DMA_TCD_CH20_CSR_EEI_WIDTH               (1U)
#define DMA_TCD_CH20_CSR_EEI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_CSR_EEI_SHIFT)) & DMA_TCD_CH20_CSR_EEI_MASK)

#define DMA_TCD_CH20_CSR_EBW_MASK                (0x8U)
#define DMA_TCD_CH20_CSR_EBW_SHIFT               (3U)
#define DMA_TCD_CH20_CSR_EBW_WIDTH               (1U)
#define DMA_TCD_CH20_CSR_EBW(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_CSR_EBW_SHIFT)) & DMA_TCD_CH20_CSR_EBW_MASK)

#define DMA_TCD_CH20_CSR_DONE_MASK               (0x40000000U)
#define DMA_TCD_CH20_CSR_DONE_SHIFT              (30U)
#define DMA_TCD_CH20_CSR_DONE_WIDTH              (1U)
#define DMA_TCD_CH20_CSR_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_CSR_DONE_SHIFT)) & DMA_TCD_CH20_CSR_DONE_MASK)

#define DMA_TCD_CH20_CSR_ACTIVE_MASK             (0x80000000U)
#define DMA_TCD_CH20_CSR_ACTIVE_SHIFT            (31U)
#define DMA_TCD_CH20_CSR_ACTIVE_WIDTH            (1U)
#define DMA_TCD_CH20_CSR_ACTIVE(x)               (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH20_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH20_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH20_ES_DBE_MASK                 (0x1U)
#define DMA_TCD_CH20_ES_DBE_SHIFT                (0U)
#define DMA_TCD_CH20_ES_DBE_WIDTH                (1U)
#define DMA_TCD_CH20_ES_DBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_ES_DBE_SHIFT)) & DMA_TCD_CH20_ES_DBE_MASK)

#define DMA_TCD_CH20_ES_SBE_MASK                 (0x2U)
#define DMA_TCD_CH20_ES_SBE_SHIFT                (1U)
#define DMA_TCD_CH20_ES_SBE_WIDTH                (1U)
#define DMA_TCD_CH20_ES_SBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_ES_SBE_SHIFT)) & DMA_TCD_CH20_ES_SBE_MASK)

#define DMA_TCD_CH20_ES_SGE_MASK                 (0x4U)
#define DMA_TCD_CH20_ES_SGE_SHIFT                (2U)
#define DMA_TCD_CH20_ES_SGE_WIDTH                (1U)
#define DMA_TCD_CH20_ES_SGE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_ES_SGE_SHIFT)) & DMA_TCD_CH20_ES_SGE_MASK)

#define DMA_TCD_CH20_ES_NCE_MASK                 (0x8U)
#define DMA_TCD_CH20_ES_NCE_SHIFT                (3U)
#define DMA_TCD_CH20_ES_NCE_WIDTH                (1U)
#define DMA_TCD_CH20_ES_NCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_ES_NCE_SHIFT)) & DMA_TCD_CH20_ES_NCE_MASK)

#define DMA_TCD_CH20_ES_DOE_MASK                 (0x10U)
#define DMA_TCD_CH20_ES_DOE_SHIFT                (4U)
#define DMA_TCD_CH20_ES_DOE_WIDTH                (1U)
#define DMA_TCD_CH20_ES_DOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_ES_DOE_SHIFT)) & DMA_TCD_CH20_ES_DOE_MASK)

#define DMA_TCD_CH20_ES_DAE_MASK                 (0x20U)
#define DMA_TCD_CH20_ES_DAE_SHIFT                (5U)
#define DMA_TCD_CH20_ES_DAE_WIDTH                (1U)
#define DMA_TCD_CH20_ES_DAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_ES_DAE_SHIFT)) & DMA_TCD_CH20_ES_DAE_MASK)

#define DMA_TCD_CH20_ES_SOE_MASK                 (0x40U)
#define DMA_TCD_CH20_ES_SOE_SHIFT                (6U)
#define DMA_TCD_CH20_ES_SOE_WIDTH                (1U)
#define DMA_TCD_CH20_ES_SOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_ES_SOE_SHIFT)) & DMA_TCD_CH20_ES_SOE_MASK)

#define DMA_TCD_CH20_ES_SAE_MASK                 (0x80U)
#define DMA_TCD_CH20_ES_SAE_SHIFT                (7U)
#define DMA_TCD_CH20_ES_SAE_WIDTH                (1U)
#define DMA_TCD_CH20_ES_SAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_ES_SAE_SHIFT)) & DMA_TCD_CH20_ES_SAE_MASK)

#define DMA_TCD_CH20_ES_ERR_MASK                 (0x80000000U)
#define DMA_TCD_CH20_ES_ERR_SHIFT                (31U)
#define DMA_TCD_CH20_ES_ERR_WIDTH                (1U)
#define DMA_TCD_CH20_ES_ERR(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_ES_ERR_SHIFT)) & DMA_TCD_CH20_ES_ERR_MASK)
/*! @} */

/*! @name CH20_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH20_INT_INT_MASK                (0x1U)
#define DMA_TCD_CH20_INT_INT_SHIFT               (0U)
#define DMA_TCD_CH20_INT_INT_WIDTH               (1U)
#define DMA_TCD_CH20_INT_INT(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_INT_INT_SHIFT)) & DMA_TCD_CH20_INT_INT_MASK)
/*! @} */

/*! @name CH20_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH20_SBR_MID_MASK                (0xFU)
#define DMA_TCD_CH20_SBR_MID_SHIFT               (0U)
#define DMA_TCD_CH20_SBR_MID_WIDTH               (4U)
#define DMA_TCD_CH20_SBR_MID(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_SBR_MID_SHIFT)) & DMA_TCD_CH20_SBR_MID_MASK)

#define DMA_TCD_CH20_SBR_PAL_MASK                (0x8000U)
#define DMA_TCD_CH20_SBR_PAL_SHIFT               (15U)
#define DMA_TCD_CH20_SBR_PAL_WIDTH               (1U)
#define DMA_TCD_CH20_SBR_PAL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_SBR_PAL_SHIFT)) & DMA_TCD_CH20_SBR_PAL_MASK)

#define DMA_TCD_CH20_SBR_EMI_MASK                (0x10000U)
#define DMA_TCD_CH20_SBR_EMI_SHIFT               (16U)
#define DMA_TCD_CH20_SBR_EMI_WIDTH               (1U)
#define DMA_TCD_CH20_SBR_EMI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_SBR_EMI_SHIFT)) & DMA_TCD_CH20_SBR_EMI_MASK)

#define DMA_TCD_CH20_SBR_ATTR_MASK               (0xE0000U)
#define DMA_TCD_CH20_SBR_ATTR_SHIFT              (17U)
#define DMA_TCD_CH20_SBR_ATTR_WIDTH              (3U)
#define DMA_TCD_CH20_SBR_ATTR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_SBR_ATTR_SHIFT)) & DMA_TCD_CH20_SBR_ATTR_MASK)
/*! @} */

/*! @name CH20_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH20_PRI_APL_MASK                (0x7U)
#define DMA_TCD_CH20_PRI_APL_SHIFT               (0U)
#define DMA_TCD_CH20_PRI_APL_WIDTH               (3U)
#define DMA_TCD_CH20_PRI_APL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_PRI_APL_SHIFT)) & DMA_TCD_CH20_PRI_APL_MASK)

#define DMA_TCD_CH20_PRI_DPA_MASK                (0x40000000U)
#define DMA_TCD_CH20_PRI_DPA_SHIFT               (30U)
#define DMA_TCD_CH20_PRI_DPA_WIDTH               (1U)
#define DMA_TCD_CH20_PRI_DPA(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_PRI_DPA_SHIFT)) & DMA_TCD_CH20_PRI_DPA_MASK)

#define DMA_TCD_CH20_PRI_ECP_MASK                (0x80000000U)
#define DMA_TCD_CH20_PRI_ECP_SHIFT               (31U)
#define DMA_TCD_CH20_PRI_ECP_WIDTH               (1U)
#define DMA_TCD_CH20_PRI_ECP(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH20_PRI_ECP_SHIFT)) & DMA_TCD_CH20_PRI_ECP_MASK)
/*! @} */

/*! @name TCD20_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD20_SADDR_SADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD20_SADDR_SADDR_SHIFT          (0U)
#define DMA_TCD_TCD20_SADDR_SADDR_WIDTH          (32U)
#define DMA_TCD_TCD20_SADDR_SADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD20_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD20_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD20_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD20_SOFF_SOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD20_SOFF_SOFF_SHIFT            (0U)
#define DMA_TCD_TCD20_SOFF_SOFF_WIDTH            (16U)
#define DMA_TCD_TCD20_SOFF_SOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD20_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD20_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD20_ATTR_DSIZE_MASK            (0x7U)
#define DMA_TCD_TCD20_ATTR_DSIZE_SHIFT           (0U)
#define DMA_TCD_TCD20_ATTR_DSIZE_WIDTH           (3U)
#define DMA_TCD_TCD20_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD20_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD20_ATTR_DMOD_MASK             (0xF8U)
#define DMA_TCD_TCD20_ATTR_DMOD_SHIFT            (3U)
#define DMA_TCD_TCD20_ATTR_DMOD_WIDTH            (5U)
#define DMA_TCD_TCD20_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD20_ATTR_DMOD_MASK)

#define DMA_TCD_TCD20_ATTR_SSIZE_MASK            (0x700U)
#define DMA_TCD_TCD20_ATTR_SSIZE_SHIFT           (8U)
#define DMA_TCD_TCD20_ATTR_SSIZE_WIDTH           (3U)
#define DMA_TCD_TCD20_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD20_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD20_ATTR_SMOD_MASK             (0xF800U)
#define DMA_TCD_TCD20_ATTR_SMOD_SHIFT            (11U)
#define DMA_TCD_TCD20_ATTR_SMOD_WIDTH            (5U)
#define DMA_TCD_TCD20_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD20_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD20_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD20_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_TCD_TCD20_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD20_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD20_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD20_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD20_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD20_NBYTES_MLOFFNO_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD20_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD20_NBYTES_MLOFFNO_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD20_NBYTES_MLOFFNO_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD20_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD20_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD20_NBYTES_MLOFFNO_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD20_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD20_NBYTES_MLOFFNO_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD20_NBYTES_MLOFFNO_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD20_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD20_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD20_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD20_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD20_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD20_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD20_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD20_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD20_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD20_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_TCD_TCD20_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD20_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD20_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD20_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD20_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD20_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_TCD_TCD20_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD20_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD20_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD20_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD20_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD20_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_TCD_TCD20_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD20_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD20_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD20_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD20_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD20_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD20_SLAST_SDA_SLAST_SDA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD20_SLAST_SDA_SLAST_SDA_SHIFT  (0U)
#define DMA_TCD_TCD20_SLAST_SDA_SLAST_SDA_WIDTH  (32U)
#define DMA_TCD_TCD20_SLAST_SDA_SLAST_SDA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD20_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD20_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD20_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD20_DADDR_DADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD20_DADDR_DADDR_SHIFT          (0U)
#define DMA_TCD_TCD20_DADDR_DADDR_WIDTH          (32U)
#define DMA_TCD_TCD20_DADDR_DADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD20_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD20_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD20_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD20_DOFF_DOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD20_DOFF_DOFF_SHIFT            (0U)
#define DMA_TCD_TCD20_DOFF_DOFF_WIDTH            (16U)
#define DMA_TCD_TCD20_DOFF_DOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD20_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD20_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD20_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD20_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_TCD_TCD20_CITER_ELINKNO_CITER_WIDTH  (15U)
#define DMA_TCD_TCD20_CITER_ELINKNO_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD20_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD20_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD20_CITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD20_CITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD20_CITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD20_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD20_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD20_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_TCD_TCD20_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_TCD_TCD20_CITER_ELINKYES_CITER_WIDTH (9U)
#define DMA_TCD_TCD20_CITER_ELINKYES_CITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD20_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD20_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD20_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD20_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD20_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD20_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD20_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD20_CITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD20_CITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD20_CITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD20_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD20_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD20_DLAST_SGA_DLAST_SGA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD20_DLAST_SGA_DLAST_SGA_SHIFT  (0U)
#define DMA_TCD_TCD20_DLAST_SGA_DLAST_SGA_WIDTH  (32U)
#define DMA_TCD_TCD20_DLAST_SGA_DLAST_SGA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD20_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD20_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD20_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD20_CSR_START_MASK             (0x1U)
#define DMA_TCD_TCD20_CSR_START_SHIFT            (0U)
#define DMA_TCD_TCD20_CSR_START_WIDTH            (1U)
#define DMA_TCD_TCD20_CSR_START(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_CSR_START_SHIFT)) & DMA_TCD_TCD20_CSR_START_MASK)

#define DMA_TCD_TCD20_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_TCD_TCD20_CSR_INTMAJOR_SHIFT         (1U)
#define DMA_TCD_TCD20_CSR_INTMAJOR_WIDTH         (1U)
#define DMA_TCD_TCD20_CSR_INTMAJOR(x)            (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD20_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD20_CSR_INTHALF_MASK           (0x4U)
#define DMA_TCD_TCD20_CSR_INTHALF_SHIFT          (2U)
#define DMA_TCD_TCD20_CSR_INTHALF_WIDTH          (1U)
#define DMA_TCD_TCD20_CSR_INTHALF(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD20_CSR_INTHALF_MASK)

#define DMA_TCD_TCD20_CSR_DREQ_MASK              (0x8U)
#define DMA_TCD_TCD20_CSR_DREQ_SHIFT             (3U)
#define DMA_TCD_TCD20_CSR_DREQ_WIDTH             (1U)
#define DMA_TCD_TCD20_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_CSR_DREQ_SHIFT)) & DMA_TCD_TCD20_CSR_DREQ_MASK)

#define DMA_TCD_TCD20_CSR_ESG_MASK               (0x10U)
#define DMA_TCD_TCD20_CSR_ESG_SHIFT              (4U)
#define DMA_TCD_TCD20_CSR_ESG_WIDTH              (1U)
#define DMA_TCD_TCD20_CSR_ESG(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_CSR_ESG_SHIFT)) & DMA_TCD_TCD20_CSR_ESG_MASK)

#define DMA_TCD_TCD20_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_TCD_TCD20_CSR_MAJORELINK_SHIFT       (5U)
#define DMA_TCD_TCD20_CSR_MAJORELINK_WIDTH       (1U)
#define DMA_TCD_TCD20_CSR_MAJORELINK(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD20_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD20_CSR_EEOP_MASK              (0x40U)
#define DMA_TCD_TCD20_CSR_EEOP_SHIFT             (6U)
#define DMA_TCD_TCD20_CSR_EEOP_WIDTH             (1U)
#define DMA_TCD_TCD20_CSR_EEOP(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_CSR_EEOP_SHIFT)) & DMA_TCD_TCD20_CSR_EEOP_MASK)

#define DMA_TCD_TCD20_CSR_ESDA_MASK              (0x80U)
#define DMA_TCD_TCD20_CSR_ESDA_SHIFT             (7U)
#define DMA_TCD_TCD20_CSR_ESDA_WIDTH             (1U)
#define DMA_TCD_TCD20_CSR_ESDA(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_CSR_ESDA_SHIFT)) & DMA_TCD_TCD20_CSR_ESDA_MASK)

#define DMA_TCD_TCD20_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_TCD_TCD20_CSR_MAJORLINKCH_SHIFT      (8U)
#define DMA_TCD_TCD20_CSR_MAJORLINKCH_WIDTH      (5U)
#define DMA_TCD_TCD20_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD20_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD20_CSR_BWC_MASK               (0xC000U)
#define DMA_TCD_TCD20_CSR_BWC_SHIFT              (14U)
#define DMA_TCD_TCD20_CSR_BWC_WIDTH              (2U)
#define DMA_TCD_TCD20_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_CSR_BWC_SHIFT)) & DMA_TCD_TCD20_CSR_BWC_MASK)
/*! @} */

/*! @name TCD20_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD20_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD20_BITER_ELINKNO_BITER_SHIFT  (0U)
#define DMA_TCD_TCD20_BITER_ELINKNO_BITER_WIDTH  (15U)
#define DMA_TCD_TCD20_BITER_ELINKNO_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD20_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD20_BITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD20_BITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD20_BITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD20_BITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD20_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD20_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD20_BITER_ELINKYES_BITER_MASK  (0x1FFU)
#define DMA_TCD_TCD20_BITER_ELINKYES_BITER_SHIFT (0U)
#define DMA_TCD_TCD20_BITER_ELINKYES_BITER_WIDTH (9U)
#define DMA_TCD_TCD20_BITER_ELINKYES_BITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD20_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD20_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD20_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD20_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD20_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD20_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD20_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD20_BITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD20_BITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD20_BITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD20_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD20_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH21_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH21_CSR_ERQ_MASK                (0x1U)
#define DMA_TCD_CH21_CSR_ERQ_SHIFT               (0U)
#define DMA_TCD_CH21_CSR_ERQ_WIDTH               (1U)
#define DMA_TCD_CH21_CSR_ERQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_CSR_ERQ_SHIFT)) & DMA_TCD_CH21_CSR_ERQ_MASK)

#define DMA_TCD_CH21_CSR_EARQ_MASK               (0x2U)
#define DMA_TCD_CH21_CSR_EARQ_SHIFT              (1U)
#define DMA_TCD_CH21_CSR_EARQ_WIDTH              (1U)
#define DMA_TCD_CH21_CSR_EARQ(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_CSR_EARQ_SHIFT)) & DMA_TCD_CH21_CSR_EARQ_MASK)

#define DMA_TCD_CH21_CSR_EEI_MASK                (0x4U)
#define DMA_TCD_CH21_CSR_EEI_SHIFT               (2U)
#define DMA_TCD_CH21_CSR_EEI_WIDTH               (1U)
#define DMA_TCD_CH21_CSR_EEI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_CSR_EEI_SHIFT)) & DMA_TCD_CH21_CSR_EEI_MASK)

#define DMA_TCD_CH21_CSR_EBW_MASK                (0x8U)
#define DMA_TCD_CH21_CSR_EBW_SHIFT               (3U)
#define DMA_TCD_CH21_CSR_EBW_WIDTH               (1U)
#define DMA_TCD_CH21_CSR_EBW(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_CSR_EBW_SHIFT)) & DMA_TCD_CH21_CSR_EBW_MASK)

#define DMA_TCD_CH21_CSR_DONE_MASK               (0x40000000U)
#define DMA_TCD_CH21_CSR_DONE_SHIFT              (30U)
#define DMA_TCD_CH21_CSR_DONE_WIDTH              (1U)
#define DMA_TCD_CH21_CSR_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_CSR_DONE_SHIFT)) & DMA_TCD_CH21_CSR_DONE_MASK)

#define DMA_TCD_CH21_CSR_ACTIVE_MASK             (0x80000000U)
#define DMA_TCD_CH21_CSR_ACTIVE_SHIFT            (31U)
#define DMA_TCD_CH21_CSR_ACTIVE_WIDTH            (1U)
#define DMA_TCD_CH21_CSR_ACTIVE(x)               (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH21_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH21_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH21_ES_DBE_MASK                 (0x1U)
#define DMA_TCD_CH21_ES_DBE_SHIFT                (0U)
#define DMA_TCD_CH21_ES_DBE_WIDTH                (1U)
#define DMA_TCD_CH21_ES_DBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_ES_DBE_SHIFT)) & DMA_TCD_CH21_ES_DBE_MASK)

#define DMA_TCD_CH21_ES_SBE_MASK                 (0x2U)
#define DMA_TCD_CH21_ES_SBE_SHIFT                (1U)
#define DMA_TCD_CH21_ES_SBE_WIDTH                (1U)
#define DMA_TCD_CH21_ES_SBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_ES_SBE_SHIFT)) & DMA_TCD_CH21_ES_SBE_MASK)

#define DMA_TCD_CH21_ES_SGE_MASK                 (0x4U)
#define DMA_TCD_CH21_ES_SGE_SHIFT                (2U)
#define DMA_TCD_CH21_ES_SGE_WIDTH                (1U)
#define DMA_TCD_CH21_ES_SGE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_ES_SGE_SHIFT)) & DMA_TCD_CH21_ES_SGE_MASK)

#define DMA_TCD_CH21_ES_NCE_MASK                 (0x8U)
#define DMA_TCD_CH21_ES_NCE_SHIFT                (3U)
#define DMA_TCD_CH21_ES_NCE_WIDTH                (1U)
#define DMA_TCD_CH21_ES_NCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_ES_NCE_SHIFT)) & DMA_TCD_CH21_ES_NCE_MASK)

#define DMA_TCD_CH21_ES_DOE_MASK                 (0x10U)
#define DMA_TCD_CH21_ES_DOE_SHIFT                (4U)
#define DMA_TCD_CH21_ES_DOE_WIDTH                (1U)
#define DMA_TCD_CH21_ES_DOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_ES_DOE_SHIFT)) & DMA_TCD_CH21_ES_DOE_MASK)

#define DMA_TCD_CH21_ES_DAE_MASK                 (0x20U)
#define DMA_TCD_CH21_ES_DAE_SHIFT                (5U)
#define DMA_TCD_CH21_ES_DAE_WIDTH                (1U)
#define DMA_TCD_CH21_ES_DAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_ES_DAE_SHIFT)) & DMA_TCD_CH21_ES_DAE_MASK)

#define DMA_TCD_CH21_ES_SOE_MASK                 (0x40U)
#define DMA_TCD_CH21_ES_SOE_SHIFT                (6U)
#define DMA_TCD_CH21_ES_SOE_WIDTH                (1U)
#define DMA_TCD_CH21_ES_SOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_ES_SOE_SHIFT)) & DMA_TCD_CH21_ES_SOE_MASK)

#define DMA_TCD_CH21_ES_SAE_MASK                 (0x80U)
#define DMA_TCD_CH21_ES_SAE_SHIFT                (7U)
#define DMA_TCD_CH21_ES_SAE_WIDTH                (1U)
#define DMA_TCD_CH21_ES_SAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_ES_SAE_SHIFT)) & DMA_TCD_CH21_ES_SAE_MASK)

#define DMA_TCD_CH21_ES_ERR_MASK                 (0x80000000U)
#define DMA_TCD_CH21_ES_ERR_SHIFT                (31U)
#define DMA_TCD_CH21_ES_ERR_WIDTH                (1U)
#define DMA_TCD_CH21_ES_ERR(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_ES_ERR_SHIFT)) & DMA_TCD_CH21_ES_ERR_MASK)
/*! @} */

/*! @name CH21_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH21_INT_INT_MASK                (0x1U)
#define DMA_TCD_CH21_INT_INT_SHIFT               (0U)
#define DMA_TCD_CH21_INT_INT_WIDTH               (1U)
#define DMA_TCD_CH21_INT_INT(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_INT_INT_SHIFT)) & DMA_TCD_CH21_INT_INT_MASK)
/*! @} */

/*! @name CH21_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH21_SBR_MID_MASK                (0xFU)
#define DMA_TCD_CH21_SBR_MID_SHIFT               (0U)
#define DMA_TCD_CH21_SBR_MID_WIDTH               (4U)
#define DMA_TCD_CH21_SBR_MID(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_SBR_MID_SHIFT)) & DMA_TCD_CH21_SBR_MID_MASK)

#define DMA_TCD_CH21_SBR_PAL_MASK                (0x8000U)
#define DMA_TCD_CH21_SBR_PAL_SHIFT               (15U)
#define DMA_TCD_CH21_SBR_PAL_WIDTH               (1U)
#define DMA_TCD_CH21_SBR_PAL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_SBR_PAL_SHIFT)) & DMA_TCD_CH21_SBR_PAL_MASK)

#define DMA_TCD_CH21_SBR_EMI_MASK                (0x10000U)
#define DMA_TCD_CH21_SBR_EMI_SHIFT               (16U)
#define DMA_TCD_CH21_SBR_EMI_WIDTH               (1U)
#define DMA_TCD_CH21_SBR_EMI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_SBR_EMI_SHIFT)) & DMA_TCD_CH21_SBR_EMI_MASK)

#define DMA_TCD_CH21_SBR_ATTR_MASK               (0xE0000U)
#define DMA_TCD_CH21_SBR_ATTR_SHIFT              (17U)
#define DMA_TCD_CH21_SBR_ATTR_WIDTH              (3U)
#define DMA_TCD_CH21_SBR_ATTR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_SBR_ATTR_SHIFT)) & DMA_TCD_CH21_SBR_ATTR_MASK)
/*! @} */

/*! @name CH21_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH21_PRI_APL_MASK                (0x7U)
#define DMA_TCD_CH21_PRI_APL_SHIFT               (0U)
#define DMA_TCD_CH21_PRI_APL_WIDTH               (3U)
#define DMA_TCD_CH21_PRI_APL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_PRI_APL_SHIFT)) & DMA_TCD_CH21_PRI_APL_MASK)

#define DMA_TCD_CH21_PRI_DPA_MASK                (0x40000000U)
#define DMA_TCD_CH21_PRI_DPA_SHIFT               (30U)
#define DMA_TCD_CH21_PRI_DPA_WIDTH               (1U)
#define DMA_TCD_CH21_PRI_DPA(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_PRI_DPA_SHIFT)) & DMA_TCD_CH21_PRI_DPA_MASK)

#define DMA_TCD_CH21_PRI_ECP_MASK                (0x80000000U)
#define DMA_TCD_CH21_PRI_ECP_SHIFT               (31U)
#define DMA_TCD_CH21_PRI_ECP_WIDTH               (1U)
#define DMA_TCD_CH21_PRI_ECP(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH21_PRI_ECP_SHIFT)) & DMA_TCD_CH21_PRI_ECP_MASK)
/*! @} */

/*! @name TCD21_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD21_SADDR_SADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD21_SADDR_SADDR_SHIFT          (0U)
#define DMA_TCD_TCD21_SADDR_SADDR_WIDTH          (32U)
#define DMA_TCD_TCD21_SADDR_SADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD21_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD21_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD21_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD21_SOFF_SOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD21_SOFF_SOFF_SHIFT            (0U)
#define DMA_TCD_TCD21_SOFF_SOFF_WIDTH            (16U)
#define DMA_TCD_TCD21_SOFF_SOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD21_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD21_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD21_ATTR_DSIZE_MASK            (0x7U)
#define DMA_TCD_TCD21_ATTR_DSIZE_SHIFT           (0U)
#define DMA_TCD_TCD21_ATTR_DSIZE_WIDTH           (3U)
#define DMA_TCD_TCD21_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD21_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD21_ATTR_DMOD_MASK             (0xF8U)
#define DMA_TCD_TCD21_ATTR_DMOD_SHIFT            (3U)
#define DMA_TCD_TCD21_ATTR_DMOD_WIDTH            (5U)
#define DMA_TCD_TCD21_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD21_ATTR_DMOD_MASK)

#define DMA_TCD_TCD21_ATTR_SSIZE_MASK            (0x700U)
#define DMA_TCD_TCD21_ATTR_SSIZE_SHIFT           (8U)
#define DMA_TCD_TCD21_ATTR_SSIZE_WIDTH           (3U)
#define DMA_TCD_TCD21_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD21_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD21_ATTR_SMOD_MASK             (0xF800U)
#define DMA_TCD_TCD21_ATTR_SMOD_SHIFT            (11U)
#define DMA_TCD_TCD21_ATTR_SMOD_WIDTH            (5U)
#define DMA_TCD_TCD21_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD21_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD21_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD21_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_TCD_TCD21_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD21_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD21_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD21_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD21_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD21_NBYTES_MLOFFNO_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD21_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD21_NBYTES_MLOFFNO_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD21_NBYTES_MLOFFNO_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD21_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD21_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD21_NBYTES_MLOFFNO_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD21_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD21_NBYTES_MLOFFNO_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD21_NBYTES_MLOFFNO_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD21_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD21_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD21_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD21_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD21_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD21_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD21_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD21_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD21_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD21_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_TCD_TCD21_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD21_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD21_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD21_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD21_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD21_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_TCD_TCD21_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD21_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD21_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD21_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD21_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD21_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_TCD_TCD21_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD21_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD21_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD21_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD21_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD21_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD21_SLAST_SDA_SLAST_SDA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD21_SLAST_SDA_SLAST_SDA_SHIFT  (0U)
#define DMA_TCD_TCD21_SLAST_SDA_SLAST_SDA_WIDTH  (32U)
#define DMA_TCD_TCD21_SLAST_SDA_SLAST_SDA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD21_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD21_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD21_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD21_DADDR_DADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD21_DADDR_DADDR_SHIFT          (0U)
#define DMA_TCD_TCD21_DADDR_DADDR_WIDTH          (32U)
#define DMA_TCD_TCD21_DADDR_DADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD21_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD21_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD21_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD21_DOFF_DOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD21_DOFF_DOFF_SHIFT            (0U)
#define DMA_TCD_TCD21_DOFF_DOFF_WIDTH            (16U)
#define DMA_TCD_TCD21_DOFF_DOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD21_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD21_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD21_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD21_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_TCD_TCD21_CITER_ELINKNO_CITER_WIDTH  (15U)
#define DMA_TCD_TCD21_CITER_ELINKNO_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD21_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD21_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD21_CITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD21_CITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD21_CITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD21_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD21_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD21_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_TCD_TCD21_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_TCD_TCD21_CITER_ELINKYES_CITER_WIDTH (9U)
#define DMA_TCD_TCD21_CITER_ELINKYES_CITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD21_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD21_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD21_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD21_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD21_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD21_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD21_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD21_CITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD21_CITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD21_CITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD21_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD21_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD21_DLAST_SGA_DLAST_SGA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD21_DLAST_SGA_DLAST_SGA_SHIFT  (0U)
#define DMA_TCD_TCD21_DLAST_SGA_DLAST_SGA_WIDTH  (32U)
#define DMA_TCD_TCD21_DLAST_SGA_DLAST_SGA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD21_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD21_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD21_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD21_CSR_START_MASK             (0x1U)
#define DMA_TCD_TCD21_CSR_START_SHIFT            (0U)
#define DMA_TCD_TCD21_CSR_START_WIDTH            (1U)
#define DMA_TCD_TCD21_CSR_START(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_CSR_START_SHIFT)) & DMA_TCD_TCD21_CSR_START_MASK)

#define DMA_TCD_TCD21_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_TCD_TCD21_CSR_INTMAJOR_SHIFT         (1U)
#define DMA_TCD_TCD21_CSR_INTMAJOR_WIDTH         (1U)
#define DMA_TCD_TCD21_CSR_INTMAJOR(x)            (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD21_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD21_CSR_INTHALF_MASK           (0x4U)
#define DMA_TCD_TCD21_CSR_INTHALF_SHIFT          (2U)
#define DMA_TCD_TCD21_CSR_INTHALF_WIDTH          (1U)
#define DMA_TCD_TCD21_CSR_INTHALF(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD21_CSR_INTHALF_MASK)

#define DMA_TCD_TCD21_CSR_DREQ_MASK              (0x8U)
#define DMA_TCD_TCD21_CSR_DREQ_SHIFT             (3U)
#define DMA_TCD_TCD21_CSR_DREQ_WIDTH             (1U)
#define DMA_TCD_TCD21_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_CSR_DREQ_SHIFT)) & DMA_TCD_TCD21_CSR_DREQ_MASK)

#define DMA_TCD_TCD21_CSR_ESG_MASK               (0x10U)
#define DMA_TCD_TCD21_CSR_ESG_SHIFT              (4U)
#define DMA_TCD_TCD21_CSR_ESG_WIDTH              (1U)
#define DMA_TCD_TCD21_CSR_ESG(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_CSR_ESG_SHIFT)) & DMA_TCD_TCD21_CSR_ESG_MASK)

#define DMA_TCD_TCD21_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_TCD_TCD21_CSR_MAJORELINK_SHIFT       (5U)
#define DMA_TCD_TCD21_CSR_MAJORELINK_WIDTH       (1U)
#define DMA_TCD_TCD21_CSR_MAJORELINK(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD21_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD21_CSR_EEOP_MASK              (0x40U)
#define DMA_TCD_TCD21_CSR_EEOP_SHIFT             (6U)
#define DMA_TCD_TCD21_CSR_EEOP_WIDTH             (1U)
#define DMA_TCD_TCD21_CSR_EEOP(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_CSR_EEOP_SHIFT)) & DMA_TCD_TCD21_CSR_EEOP_MASK)

#define DMA_TCD_TCD21_CSR_ESDA_MASK              (0x80U)
#define DMA_TCD_TCD21_CSR_ESDA_SHIFT             (7U)
#define DMA_TCD_TCD21_CSR_ESDA_WIDTH             (1U)
#define DMA_TCD_TCD21_CSR_ESDA(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_CSR_ESDA_SHIFT)) & DMA_TCD_TCD21_CSR_ESDA_MASK)

#define DMA_TCD_TCD21_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_TCD_TCD21_CSR_MAJORLINKCH_SHIFT      (8U)
#define DMA_TCD_TCD21_CSR_MAJORLINKCH_WIDTH      (5U)
#define DMA_TCD_TCD21_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD21_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD21_CSR_BWC_MASK               (0xC000U)
#define DMA_TCD_TCD21_CSR_BWC_SHIFT              (14U)
#define DMA_TCD_TCD21_CSR_BWC_WIDTH              (2U)
#define DMA_TCD_TCD21_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_CSR_BWC_SHIFT)) & DMA_TCD_TCD21_CSR_BWC_MASK)
/*! @} */

/*! @name TCD21_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD21_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD21_BITER_ELINKNO_BITER_SHIFT  (0U)
#define DMA_TCD_TCD21_BITER_ELINKNO_BITER_WIDTH  (15U)
#define DMA_TCD_TCD21_BITER_ELINKNO_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD21_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD21_BITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD21_BITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD21_BITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD21_BITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD21_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD21_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD21_BITER_ELINKYES_BITER_MASK  (0x1FFU)
#define DMA_TCD_TCD21_BITER_ELINKYES_BITER_SHIFT (0U)
#define DMA_TCD_TCD21_BITER_ELINKYES_BITER_WIDTH (9U)
#define DMA_TCD_TCD21_BITER_ELINKYES_BITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD21_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD21_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD21_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD21_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD21_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD21_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD21_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD21_BITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD21_BITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD21_BITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD21_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD21_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH22_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH22_CSR_ERQ_MASK                (0x1U)
#define DMA_TCD_CH22_CSR_ERQ_SHIFT               (0U)
#define DMA_TCD_CH22_CSR_ERQ_WIDTH               (1U)
#define DMA_TCD_CH22_CSR_ERQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_CSR_ERQ_SHIFT)) & DMA_TCD_CH22_CSR_ERQ_MASK)

#define DMA_TCD_CH22_CSR_EARQ_MASK               (0x2U)
#define DMA_TCD_CH22_CSR_EARQ_SHIFT              (1U)
#define DMA_TCD_CH22_CSR_EARQ_WIDTH              (1U)
#define DMA_TCD_CH22_CSR_EARQ(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_CSR_EARQ_SHIFT)) & DMA_TCD_CH22_CSR_EARQ_MASK)

#define DMA_TCD_CH22_CSR_EEI_MASK                (0x4U)
#define DMA_TCD_CH22_CSR_EEI_SHIFT               (2U)
#define DMA_TCD_CH22_CSR_EEI_WIDTH               (1U)
#define DMA_TCD_CH22_CSR_EEI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_CSR_EEI_SHIFT)) & DMA_TCD_CH22_CSR_EEI_MASK)

#define DMA_TCD_CH22_CSR_EBW_MASK                (0x8U)
#define DMA_TCD_CH22_CSR_EBW_SHIFT               (3U)
#define DMA_TCD_CH22_CSR_EBW_WIDTH               (1U)
#define DMA_TCD_CH22_CSR_EBW(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_CSR_EBW_SHIFT)) & DMA_TCD_CH22_CSR_EBW_MASK)

#define DMA_TCD_CH22_CSR_DONE_MASK               (0x40000000U)
#define DMA_TCD_CH22_CSR_DONE_SHIFT              (30U)
#define DMA_TCD_CH22_CSR_DONE_WIDTH              (1U)
#define DMA_TCD_CH22_CSR_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_CSR_DONE_SHIFT)) & DMA_TCD_CH22_CSR_DONE_MASK)

#define DMA_TCD_CH22_CSR_ACTIVE_MASK             (0x80000000U)
#define DMA_TCD_CH22_CSR_ACTIVE_SHIFT            (31U)
#define DMA_TCD_CH22_CSR_ACTIVE_WIDTH            (1U)
#define DMA_TCD_CH22_CSR_ACTIVE(x)               (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH22_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH22_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH22_ES_DBE_MASK                 (0x1U)
#define DMA_TCD_CH22_ES_DBE_SHIFT                (0U)
#define DMA_TCD_CH22_ES_DBE_WIDTH                (1U)
#define DMA_TCD_CH22_ES_DBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_ES_DBE_SHIFT)) & DMA_TCD_CH22_ES_DBE_MASK)

#define DMA_TCD_CH22_ES_SBE_MASK                 (0x2U)
#define DMA_TCD_CH22_ES_SBE_SHIFT                (1U)
#define DMA_TCD_CH22_ES_SBE_WIDTH                (1U)
#define DMA_TCD_CH22_ES_SBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_ES_SBE_SHIFT)) & DMA_TCD_CH22_ES_SBE_MASK)

#define DMA_TCD_CH22_ES_SGE_MASK                 (0x4U)
#define DMA_TCD_CH22_ES_SGE_SHIFT                (2U)
#define DMA_TCD_CH22_ES_SGE_WIDTH                (1U)
#define DMA_TCD_CH22_ES_SGE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_ES_SGE_SHIFT)) & DMA_TCD_CH22_ES_SGE_MASK)

#define DMA_TCD_CH22_ES_NCE_MASK                 (0x8U)
#define DMA_TCD_CH22_ES_NCE_SHIFT                (3U)
#define DMA_TCD_CH22_ES_NCE_WIDTH                (1U)
#define DMA_TCD_CH22_ES_NCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_ES_NCE_SHIFT)) & DMA_TCD_CH22_ES_NCE_MASK)

#define DMA_TCD_CH22_ES_DOE_MASK                 (0x10U)
#define DMA_TCD_CH22_ES_DOE_SHIFT                (4U)
#define DMA_TCD_CH22_ES_DOE_WIDTH                (1U)
#define DMA_TCD_CH22_ES_DOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_ES_DOE_SHIFT)) & DMA_TCD_CH22_ES_DOE_MASK)

#define DMA_TCD_CH22_ES_DAE_MASK                 (0x20U)
#define DMA_TCD_CH22_ES_DAE_SHIFT                (5U)
#define DMA_TCD_CH22_ES_DAE_WIDTH                (1U)
#define DMA_TCD_CH22_ES_DAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_ES_DAE_SHIFT)) & DMA_TCD_CH22_ES_DAE_MASK)

#define DMA_TCD_CH22_ES_SOE_MASK                 (0x40U)
#define DMA_TCD_CH22_ES_SOE_SHIFT                (6U)
#define DMA_TCD_CH22_ES_SOE_WIDTH                (1U)
#define DMA_TCD_CH22_ES_SOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_ES_SOE_SHIFT)) & DMA_TCD_CH22_ES_SOE_MASK)

#define DMA_TCD_CH22_ES_SAE_MASK                 (0x80U)
#define DMA_TCD_CH22_ES_SAE_SHIFT                (7U)
#define DMA_TCD_CH22_ES_SAE_WIDTH                (1U)
#define DMA_TCD_CH22_ES_SAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_ES_SAE_SHIFT)) & DMA_TCD_CH22_ES_SAE_MASK)

#define DMA_TCD_CH22_ES_ERR_MASK                 (0x80000000U)
#define DMA_TCD_CH22_ES_ERR_SHIFT                (31U)
#define DMA_TCD_CH22_ES_ERR_WIDTH                (1U)
#define DMA_TCD_CH22_ES_ERR(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_ES_ERR_SHIFT)) & DMA_TCD_CH22_ES_ERR_MASK)
/*! @} */

/*! @name CH22_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH22_INT_INT_MASK                (0x1U)
#define DMA_TCD_CH22_INT_INT_SHIFT               (0U)
#define DMA_TCD_CH22_INT_INT_WIDTH               (1U)
#define DMA_TCD_CH22_INT_INT(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_INT_INT_SHIFT)) & DMA_TCD_CH22_INT_INT_MASK)
/*! @} */

/*! @name CH22_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH22_SBR_MID_MASK                (0xFU)
#define DMA_TCD_CH22_SBR_MID_SHIFT               (0U)
#define DMA_TCD_CH22_SBR_MID_WIDTH               (4U)
#define DMA_TCD_CH22_SBR_MID(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_SBR_MID_SHIFT)) & DMA_TCD_CH22_SBR_MID_MASK)

#define DMA_TCD_CH22_SBR_PAL_MASK                (0x8000U)
#define DMA_TCD_CH22_SBR_PAL_SHIFT               (15U)
#define DMA_TCD_CH22_SBR_PAL_WIDTH               (1U)
#define DMA_TCD_CH22_SBR_PAL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_SBR_PAL_SHIFT)) & DMA_TCD_CH22_SBR_PAL_MASK)

#define DMA_TCD_CH22_SBR_EMI_MASK                (0x10000U)
#define DMA_TCD_CH22_SBR_EMI_SHIFT               (16U)
#define DMA_TCD_CH22_SBR_EMI_WIDTH               (1U)
#define DMA_TCD_CH22_SBR_EMI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_SBR_EMI_SHIFT)) & DMA_TCD_CH22_SBR_EMI_MASK)

#define DMA_TCD_CH22_SBR_ATTR_MASK               (0xE0000U)
#define DMA_TCD_CH22_SBR_ATTR_SHIFT              (17U)
#define DMA_TCD_CH22_SBR_ATTR_WIDTH              (3U)
#define DMA_TCD_CH22_SBR_ATTR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_SBR_ATTR_SHIFT)) & DMA_TCD_CH22_SBR_ATTR_MASK)
/*! @} */

/*! @name CH22_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH22_PRI_APL_MASK                (0x7U)
#define DMA_TCD_CH22_PRI_APL_SHIFT               (0U)
#define DMA_TCD_CH22_PRI_APL_WIDTH               (3U)
#define DMA_TCD_CH22_PRI_APL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_PRI_APL_SHIFT)) & DMA_TCD_CH22_PRI_APL_MASK)

#define DMA_TCD_CH22_PRI_DPA_MASK                (0x40000000U)
#define DMA_TCD_CH22_PRI_DPA_SHIFT               (30U)
#define DMA_TCD_CH22_PRI_DPA_WIDTH               (1U)
#define DMA_TCD_CH22_PRI_DPA(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_PRI_DPA_SHIFT)) & DMA_TCD_CH22_PRI_DPA_MASK)

#define DMA_TCD_CH22_PRI_ECP_MASK                (0x80000000U)
#define DMA_TCD_CH22_PRI_ECP_SHIFT               (31U)
#define DMA_TCD_CH22_PRI_ECP_WIDTH               (1U)
#define DMA_TCD_CH22_PRI_ECP(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH22_PRI_ECP_SHIFT)) & DMA_TCD_CH22_PRI_ECP_MASK)
/*! @} */

/*! @name TCD22_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD22_SADDR_SADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD22_SADDR_SADDR_SHIFT          (0U)
#define DMA_TCD_TCD22_SADDR_SADDR_WIDTH          (32U)
#define DMA_TCD_TCD22_SADDR_SADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD22_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD22_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD22_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD22_SOFF_SOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD22_SOFF_SOFF_SHIFT            (0U)
#define DMA_TCD_TCD22_SOFF_SOFF_WIDTH            (16U)
#define DMA_TCD_TCD22_SOFF_SOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD22_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD22_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD22_ATTR_DSIZE_MASK            (0x7U)
#define DMA_TCD_TCD22_ATTR_DSIZE_SHIFT           (0U)
#define DMA_TCD_TCD22_ATTR_DSIZE_WIDTH           (3U)
#define DMA_TCD_TCD22_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD22_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD22_ATTR_DMOD_MASK             (0xF8U)
#define DMA_TCD_TCD22_ATTR_DMOD_SHIFT            (3U)
#define DMA_TCD_TCD22_ATTR_DMOD_WIDTH            (5U)
#define DMA_TCD_TCD22_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD22_ATTR_DMOD_MASK)

#define DMA_TCD_TCD22_ATTR_SSIZE_MASK            (0x700U)
#define DMA_TCD_TCD22_ATTR_SSIZE_SHIFT           (8U)
#define DMA_TCD_TCD22_ATTR_SSIZE_WIDTH           (3U)
#define DMA_TCD_TCD22_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD22_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD22_ATTR_SMOD_MASK             (0xF800U)
#define DMA_TCD_TCD22_ATTR_SMOD_SHIFT            (11U)
#define DMA_TCD_TCD22_ATTR_SMOD_WIDTH            (5U)
#define DMA_TCD_TCD22_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD22_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD22_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD22_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_TCD_TCD22_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD22_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD22_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD22_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD22_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD22_NBYTES_MLOFFNO_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD22_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD22_NBYTES_MLOFFNO_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD22_NBYTES_MLOFFNO_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD22_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD22_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD22_NBYTES_MLOFFNO_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD22_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD22_NBYTES_MLOFFNO_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD22_NBYTES_MLOFFNO_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD22_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD22_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD22_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD22_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD22_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD22_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD22_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD22_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD22_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD22_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_TCD_TCD22_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD22_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD22_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD22_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD22_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD22_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_TCD_TCD22_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD22_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD22_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD22_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD22_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD22_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_TCD_TCD22_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD22_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD22_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD22_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD22_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD22_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD22_SLAST_SDA_SLAST_SDA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD22_SLAST_SDA_SLAST_SDA_SHIFT  (0U)
#define DMA_TCD_TCD22_SLAST_SDA_SLAST_SDA_WIDTH  (32U)
#define DMA_TCD_TCD22_SLAST_SDA_SLAST_SDA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD22_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD22_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD22_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD22_DADDR_DADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD22_DADDR_DADDR_SHIFT          (0U)
#define DMA_TCD_TCD22_DADDR_DADDR_WIDTH          (32U)
#define DMA_TCD_TCD22_DADDR_DADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD22_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD22_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD22_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD22_DOFF_DOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD22_DOFF_DOFF_SHIFT            (0U)
#define DMA_TCD_TCD22_DOFF_DOFF_WIDTH            (16U)
#define DMA_TCD_TCD22_DOFF_DOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD22_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD22_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD22_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD22_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_TCD_TCD22_CITER_ELINKNO_CITER_WIDTH  (15U)
#define DMA_TCD_TCD22_CITER_ELINKNO_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD22_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD22_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD22_CITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD22_CITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD22_CITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD22_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD22_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD22_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_TCD_TCD22_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_TCD_TCD22_CITER_ELINKYES_CITER_WIDTH (9U)
#define DMA_TCD_TCD22_CITER_ELINKYES_CITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD22_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD22_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD22_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD22_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD22_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD22_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD22_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD22_CITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD22_CITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD22_CITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD22_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD22_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD22_DLAST_SGA_DLAST_SGA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD22_DLAST_SGA_DLAST_SGA_SHIFT  (0U)
#define DMA_TCD_TCD22_DLAST_SGA_DLAST_SGA_WIDTH  (32U)
#define DMA_TCD_TCD22_DLAST_SGA_DLAST_SGA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD22_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD22_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD22_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD22_CSR_START_MASK             (0x1U)
#define DMA_TCD_TCD22_CSR_START_SHIFT            (0U)
#define DMA_TCD_TCD22_CSR_START_WIDTH            (1U)
#define DMA_TCD_TCD22_CSR_START(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_CSR_START_SHIFT)) & DMA_TCD_TCD22_CSR_START_MASK)

#define DMA_TCD_TCD22_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_TCD_TCD22_CSR_INTMAJOR_SHIFT         (1U)
#define DMA_TCD_TCD22_CSR_INTMAJOR_WIDTH         (1U)
#define DMA_TCD_TCD22_CSR_INTMAJOR(x)            (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD22_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD22_CSR_INTHALF_MASK           (0x4U)
#define DMA_TCD_TCD22_CSR_INTHALF_SHIFT          (2U)
#define DMA_TCD_TCD22_CSR_INTHALF_WIDTH          (1U)
#define DMA_TCD_TCD22_CSR_INTHALF(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD22_CSR_INTHALF_MASK)

#define DMA_TCD_TCD22_CSR_DREQ_MASK              (0x8U)
#define DMA_TCD_TCD22_CSR_DREQ_SHIFT             (3U)
#define DMA_TCD_TCD22_CSR_DREQ_WIDTH             (1U)
#define DMA_TCD_TCD22_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_CSR_DREQ_SHIFT)) & DMA_TCD_TCD22_CSR_DREQ_MASK)

#define DMA_TCD_TCD22_CSR_ESG_MASK               (0x10U)
#define DMA_TCD_TCD22_CSR_ESG_SHIFT              (4U)
#define DMA_TCD_TCD22_CSR_ESG_WIDTH              (1U)
#define DMA_TCD_TCD22_CSR_ESG(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_CSR_ESG_SHIFT)) & DMA_TCD_TCD22_CSR_ESG_MASK)

#define DMA_TCD_TCD22_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_TCD_TCD22_CSR_MAJORELINK_SHIFT       (5U)
#define DMA_TCD_TCD22_CSR_MAJORELINK_WIDTH       (1U)
#define DMA_TCD_TCD22_CSR_MAJORELINK(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD22_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD22_CSR_EEOP_MASK              (0x40U)
#define DMA_TCD_TCD22_CSR_EEOP_SHIFT             (6U)
#define DMA_TCD_TCD22_CSR_EEOP_WIDTH             (1U)
#define DMA_TCD_TCD22_CSR_EEOP(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_CSR_EEOP_SHIFT)) & DMA_TCD_TCD22_CSR_EEOP_MASK)

#define DMA_TCD_TCD22_CSR_ESDA_MASK              (0x80U)
#define DMA_TCD_TCD22_CSR_ESDA_SHIFT             (7U)
#define DMA_TCD_TCD22_CSR_ESDA_WIDTH             (1U)
#define DMA_TCD_TCD22_CSR_ESDA(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_CSR_ESDA_SHIFT)) & DMA_TCD_TCD22_CSR_ESDA_MASK)

#define DMA_TCD_TCD22_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_TCD_TCD22_CSR_MAJORLINKCH_SHIFT      (8U)
#define DMA_TCD_TCD22_CSR_MAJORLINKCH_WIDTH      (5U)
#define DMA_TCD_TCD22_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD22_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD22_CSR_BWC_MASK               (0xC000U)
#define DMA_TCD_TCD22_CSR_BWC_SHIFT              (14U)
#define DMA_TCD_TCD22_CSR_BWC_WIDTH              (2U)
#define DMA_TCD_TCD22_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_CSR_BWC_SHIFT)) & DMA_TCD_TCD22_CSR_BWC_MASK)
/*! @} */

/*! @name TCD22_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD22_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD22_BITER_ELINKNO_BITER_SHIFT  (0U)
#define DMA_TCD_TCD22_BITER_ELINKNO_BITER_WIDTH  (15U)
#define DMA_TCD_TCD22_BITER_ELINKNO_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD22_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD22_BITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD22_BITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD22_BITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD22_BITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD22_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD22_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD22_BITER_ELINKYES_BITER_MASK  (0x1FFU)
#define DMA_TCD_TCD22_BITER_ELINKYES_BITER_SHIFT (0U)
#define DMA_TCD_TCD22_BITER_ELINKYES_BITER_WIDTH (9U)
#define DMA_TCD_TCD22_BITER_ELINKYES_BITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD22_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD22_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD22_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD22_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD22_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD22_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD22_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD22_BITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD22_BITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD22_BITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD22_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD22_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH23_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH23_CSR_ERQ_MASK                (0x1U)
#define DMA_TCD_CH23_CSR_ERQ_SHIFT               (0U)
#define DMA_TCD_CH23_CSR_ERQ_WIDTH               (1U)
#define DMA_TCD_CH23_CSR_ERQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_CSR_ERQ_SHIFT)) & DMA_TCD_CH23_CSR_ERQ_MASK)

#define DMA_TCD_CH23_CSR_EARQ_MASK               (0x2U)
#define DMA_TCD_CH23_CSR_EARQ_SHIFT              (1U)
#define DMA_TCD_CH23_CSR_EARQ_WIDTH              (1U)
#define DMA_TCD_CH23_CSR_EARQ(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_CSR_EARQ_SHIFT)) & DMA_TCD_CH23_CSR_EARQ_MASK)

#define DMA_TCD_CH23_CSR_EEI_MASK                (0x4U)
#define DMA_TCD_CH23_CSR_EEI_SHIFT               (2U)
#define DMA_TCD_CH23_CSR_EEI_WIDTH               (1U)
#define DMA_TCD_CH23_CSR_EEI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_CSR_EEI_SHIFT)) & DMA_TCD_CH23_CSR_EEI_MASK)

#define DMA_TCD_CH23_CSR_EBW_MASK                (0x8U)
#define DMA_TCD_CH23_CSR_EBW_SHIFT               (3U)
#define DMA_TCD_CH23_CSR_EBW_WIDTH               (1U)
#define DMA_TCD_CH23_CSR_EBW(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_CSR_EBW_SHIFT)) & DMA_TCD_CH23_CSR_EBW_MASK)

#define DMA_TCD_CH23_CSR_DONE_MASK               (0x40000000U)
#define DMA_TCD_CH23_CSR_DONE_SHIFT              (30U)
#define DMA_TCD_CH23_CSR_DONE_WIDTH              (1U)
#define DMA_TCD_CH23_CSR_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_CSR_DONE_SHIFT)) & DMA_TCD_CH23_CSR_DONE_MASK)

#define DMA_TCD_CH23_CSR_ACTIVE_MASK             (0x80000000U)
#define DMA_TCD_CH23_CSR_ACTIVE_SHIFT            (31U)
#define DMA_TCD_CH23_CSR_ACTIVE_WIDTH            (1U)
#define DMA_TCD_CH23_CSR_ACTIVE(x)               (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH23_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH23_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH23_ES_DBE_MASK                 (0x1U)
#define DMA_TCD_CH23_ES_DBE_SHIFT                (0U)
#define DMA_TCD_CH23_ES_DBE_WIDTH                (1U)
#define DMA_TCD_CH23_ES_DBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_ES_DBE_SHIFT)) & DMA_TCD_CH23_ES_DBE_MASK)

#define DMA_TCD_CH23_ES_SBE_MASK                 (0x2U)
#define DMA_TCD_CH23_ES_SBE_SHIFT                (1U)
#define DMA_TCD_CH23_ES_SBE_WIDTH                (1U)
#define DMA_TCD_CH23_ES_SBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_ES_SBE_SHIFT)) & DMA_TCD_CH23_ES_SBE_MASK)

#define DMA_TCD_CH23_ES_SGE_MASK                 (0x4U)
#define DMA_TCD_CH23_ES_SGE_SHIFT                (2U)
#define DMA_TCD_CH23_ES_SGE_WIDTH                (1U)
#define DMA_TCD_CH23_ES_SGE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_ES_SGE_SHIFT)) & DMA_TCD_CH23_ES_SGE_MASK)

#define DMA_TCD_CH23_ES_NCE_MASK                 (0x8U)
#define DMA_TCD_CH23_ES_NCE_SHIFT                (3U)
#define DMA_TCD_CH23_ES_NCE_WIDTH                (1U)
#define DMA_TCD_CH23_ES_NCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_ES_NCE_SHIFT)) & DMA_TCD_CH23_ES_NCE_MASK)

#define DMA_TCD_CH23_ES_DOE_MASK                 (0x10U)
#define DMA_TCD_CH23_ES_DOE_SHIFT                (4U)
#define DMA_TCD_CH23_ES_DOE_WIDTH                (1U)
#define DMA_TCD_CH23_ES_DOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_ES_DOE_SHIFT)) & DMA_TCD_CH23_ES_DOE_MASK)

#define DMA_TCD_CH23_ES_DAE_MASK                 (0x20U)
#define DMA_TCD_CH23_ES_DAE_SHIFT                (5U)
#define DMA_TCD_CH23_ES_DAE_WIDTH                (1U)
#define DMA_TCD_CH23_ES_DAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_ES_DAE_SHIFT)) & DMA_TCD_CH23_ES_DAE_MASK)

#define DMA_TCD_CH23_ES_SOE_MASK                 (0x40U)
#define DMA_TCD_CH23_ES_SOE_SHIFT                (6U)
#define DMA_TCD_CH23_ES_SOE_WIDTH                (1U)
#define DMA_TCD_CH23_ES_SOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_ES_SOE_SHIFT)) & DMA_TCD_CH23_ES_SOE_MASK)

#define DMA_TCD_CH23_ES_SAE_MASK                 (0x80U)
#define DMA_TCD_CH23_ES_SAE_SHIFT                (7U)
#define DMA_TCD_CH23_ES_SAE_WIDTH                (1U)
#define DMA_TCD_CH23_ES_SAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_ES_SAE_SHIFT)) & DMA_TCD_CH23_ES_SAE_MASK)

#define DMA_TCD_CH23_ES_ERR_MASK                 (0x80000000U)
#define DMA_TCD_CH23_ES_ERR_SHIFT                (31U)
#define DMA_TCD_CH23_ES_ERR_WIDTH                (1U)
#define DMA_TCD_CH23_ES_ERR(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_ES_ERR_SHIFT)) & DMA_TCD_CH23_ES_ERR_MASK)
/*! @} */

/*! @name CH23_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH23_INT_INT_MASK                (0x1U)
#define DMA_TCD_CH23_INT_INT_SHIFT               (0U)
#define DMA_TCD_CH23_INT_INT_WIDTH               (1U)
#define DMA_TCD_CH23_INT_INT(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_INT_INT_SHIFT)) & DMA_TCD_CH23_INT_INT_MASK)
/*! @} */

/*! @name CH23_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH23_SBR_MID_MASK                (0xFU)
#define DMA_TCD_CH23_SBR_MID_SHIFT               (0U)
#define DMA_TCD_CH23_SBR_MID_WIDTH               (4U)
#define DMA_TCD_CH23_SBR_MID(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_SBR_MID_SHIFT)) & DMA_TCD_CH23_SBR_MID_MASK)

#define DMA_TCD_CH23_SBR_PAL_MASK                (0x8000U)
#define DMA_TCD_CH23_SBR_PAL_SHIFT               (15U)
#define DMA_TCD_CH23_SBR_PAL_WIDTH               (1U)
#define DMA_TCD_CH23_SBR_PAL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_SBR_PAL_SHIFT)) & DMA_TCD_CH23_SBR_PAL_MASK)

#define DMA_TCD_CH23_SBR_EMI_MASK                (0x10000U)
#define DMA_TCD_CH23_SBR_EMI_SHIFT               (16U)
#define DMA_TCD_CH23_SBR_EMI_WIDTH               (1U)
#define DMA_TCD_CH23_SBR_EMI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_SBR_EMI_SHIFT)) & DMA_TCD_CH23_SBR_EMI_MASK)

#define DMA_TCD_CH23_SBR_ATTR_MASK               (0xE0000U)
#define DMA_TCD_CH23_SBR_ATTR_SHIFT              (17U)
#define DMA_TCD_CH23_SBR_ATTR_WIDTH              (3U)
#define DMA_TCD_CH23_SBR_ATTR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_SBR_ATTR_SHIFT)) & DMA_TCD_CH23_SBR_ATTR_MASK)
/*! @} */

/*! @name CH23_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH23_PRI_APL_MASK                (0x7U)
#define DMA_TCD_CH23_PRI_APL_SHIFT               (0U)
#define DMA_TCD_CH23_PRI_APL_WIDTH               (3U)
#define DMA_TCD_CH23_PRI_APL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_PRI_APL_SHIFT)) & DMA_TCD_CH23_PRI_APL_MASK)

#define DMA_TCD_CH23_PRI_DPA_MASK                (0x40000000U)
#define DMA_TCD_CH23_PRI_DPA_SHIFT               (30U)
#define DMA_TCD_CH23_PRI_DPA_WIDTH               (1U)
#define DMA_TCD_CH23_PRI_DPA(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_PRI_DPA_SHIFT)) & DMA_TCD_CH23_PRI_DPA_MASK)

#define DMA_TCD_CH23_PRI_ECP_MASK                (0x80000000U)
#define DMA_TCD_CH23_PRI_ECP_SHIFT               (31U)
#define DMA_TCD_CH23_PRI_ECP_WIDTH               (1U)
#define DMA_TCD_CH23_PRI_ECP(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH23_PRI_ECP_SHIFT)) & DMA_TCD_CH23_PRI_ECP_MASK)
/*! @} */

/*! @name TCD23_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD23_SADDR_SADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD23_SADDR_SADDR_SHIFT          (0U)
#define DMA_TCD_TCD23_SADDR_SADDR_WIDTH          (32U)
#define DMA_TCD_TCD23_SADDR_SADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD23_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD23_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD23_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD23_SOFF_SOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD23_SOFF_SOFF_SHIFT            (0U)
#define DMA_TCD_TCD23_SOFF_SOFF_WIDTH            (16U)
#define DMA_TCD_TCD23_SOFF_SOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD23_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD23_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD23_ATTR_DSIZE_MASK            (0x7U)
#define DMA_TCD_TCD23_ATTR_DSIZE_SHIFT           (0U)
#define DMA_TCD_TCD23_ATTR_DSIZE_WIDTH           (3U)
#define DMA_TCD_TCD23_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD23_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD23_ATTR_DMOD_MASK             (0xF8U)
#define DMA_TCD_TCD23_ATTR_DMOD_SHIFT            (3U)
#define DMA_TCD_TCD23_ATTR_DMOD_WIDTH            (5U)
#define DMA_TCD_TCD23_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD23_ATTR_DMOD_MASK)

#define DMA_TCD_TCD23_ATTR_SSIZE_MASK            (0x700U)
#define DMA_TCD_TCD23_ATTR_SSIZE_SHIFT           (8U)
#define DMA_TCD_TCD23_ATTR_SSIZE_WIDTH           (3U)
#define DMA_TCD_TCD23_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD23_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD23_ATTR_SMOD_MASK             (0xF800U)
#define DMA_TCD_TCD23_ATTR_SMOD_SHIFT            (11U)
#define DMA_TCD_TCD23_ATTR_SMOD_WIDTH            (5U)
#define DMA_TCD_TCD23_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD23_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD23_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD23_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_TCD_TCD23_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD23_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD23_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD23_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD23_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD23_NBYTES_MLOFFNO_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD23_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD23_NBYTES_MLOFFNO_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD23_NBYTES_MLOFFNO_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD23_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD23_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD23_NBYTES_MLOFFNO_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD23_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD23_NBYTES_MLOFFNO_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD23_NBYTES_MLOFFNO_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD23_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD23_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD23_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD23_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD23_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD23_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD23_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD23_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD23_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD23_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_TCD_TCD23_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD23_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD23_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD23_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD23_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD23_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_TCD_TCD23_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD23_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD23_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD23_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD23_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD23_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_TCD_TCD23_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD23_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD23_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD23_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD23_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD23_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD23_SLAST_SDA_SLAST_SDA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD23_SLAST_SDA_SLAST_SDA_SHIFT  (0U)
#define DMA_TCD_TCD23_SLAST_SDA_SLAST_SDA_WIDTH  (32U)
#define DMA_TCD_TCD23_SLAST_SDA_SLAST_SDA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD23_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD23_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD23_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD23_DADDR_DADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD23_DADDR_DADDR_SHIFT          (0U)
#define DMA_TCD_TCD23_DADDR_DADDR_WIDTH          (32U)
#define DMA_TCD_TCD23_DADDR_DADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD23_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD23_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD23_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD23_DOFF_DOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD23_DOFF_DOFF_SHIFT            (0U)
#define DMA_TCD_TCD23_DOFF_DOFF_WIDTH            (16U)
#define DMA_TCD_TCD23_DOFF_DOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD23_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD23_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD23_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD23_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_TCD_TCD23_CITER_ELINKNO_CITER_WIDTH  (15U)
#define DMA_TCD_TCD23_CITER_ELINKNO_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD23_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD23_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD23_CITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD23_CITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD23_CITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD23_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD23_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD23_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_TCD_TCD23_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_TCD_TCD23_CITER_ELINKYES_CITER_WIDTH (9U)
#define DMA_TCD_TCD23_CITER_ELINKYES_CITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD23_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD23_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD23_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD23_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD23_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD23_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD23_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD23_CITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD23_CITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD23_CITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD23_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD23_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD23_DLAST_SGA_DLAST_SGA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD23_DLAST_SGA_DLAST_SGA_SHIFT  (0U)
#define DMA_TCD_TCD23_DLAST_SGA_DLAST_SGA_WIDTH  (32U)
#define DMA_TCD_TCD23_DLAST_SGA_DLAST_SGA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD23_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD23_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD23_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD23_CSR_START_MASK             (0x1U)
#define DMA_TCD_TCD23_CSR_START_SHIFT            (0U)
#define DMA_TCD_TCD23_CSR_START_WIDTH            (1U)
#define DMA_TCD_TCD23_CSR_START(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_CSR_START_SHIFT)) & DMA_TCD_TCD23_CSR_START_MASK)

#define DMA_TCD_TCD23_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_TCD_TCD23_CSR_INTMAJOR_SHIFT         (1U)
#define DMA_TCD_TCD23_CSR_INTMAJOR_WIDTH         (1U)
#define DMA_TCD_TCD23_CSR_INTMAJOR(x)            (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD23_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD23_CSR_INTHALF_MASK           (0x4U)
#define DMA_TCD_TCD23_CSR_INTHALF_SHIFT          (2U)
#define DMA_TCD_TCD23_CSR_INTHALF_WIDTH          (1U)
#define DMA_TCD_TCD23_CSR_INTHALF(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD23_CSR_INTHALF_MASK)

#define DMA_TCD_TCD23_CSR_DREQ_MASK              (0x8U)
#define DMA_TCD_TCD23_CSR_DREQ_SHIFT             (3U)
#define DMA_TCD_TCD23_CSR_DREQ_WIDTH             (1U)
#define DMA_TCD_TCD23_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_CSR_DREQ_SHIFT)) & DMA_TCD_TCD23_CSR_DREQ_MASK)

#define DMA_TCD_TCD23_CSR_ESG_MASK               (0x10U)
#define DMA_TCD_TCD23_CSR_ESG_SHIFT              (4U)
#define DMA_TCD_TCD23_CSR_ESG_WIDTH              (1U)
#define DMA_TCD_TCD23_CSR_ESG(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_CSR_ESG_SHIFT)) & DMA_TCD_TCD23_CSR_ESG_MASK)

#define DMA_TCD_TCD23_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_TCD_TCD23_CSR_MAJORELINK_SHIFT       (5U)
#define DMA_TCD_TCD23_CSR_MAJORELINK_WIDTH       (1U)
#define DMA_TCD_TCD23_CSR_MAJORELINK(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD23_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD23_CSR_EEOP_MASK              (0x40U)
#define DMA_TCD_TCD23_CSR_EEOP_SHIFT             (6U)
#define DMA_TCD_TCD23_CSR_EEOP_WIDTH             (1U)
#define DMA_TCD_TCD23_CSR_EEOP(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_CSR_EEOP_SHIFT)) & DMA_TCD_TCD23_CSR_EEOP_MASK)

#define DMA_TCD_TCD23_CSR_ESDA_MASK              (0x80U)
#define DMA_TCD_TCD23_CSR_ESDA_SHIFT             (7U)
#define DMA_TCD_TCD23_CSR_ESDA_WIDTH             (1U)
#define DMA_TCD_TCD23_CSR_ESDA(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_CSR_ESDA_SHIFT)) & DMA_TCD_TCD23_CSR_ESDA_MASK)

#define DMA_TCD_TCD23_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_TCD_TCD23_CSR_MAJORLINKCH_SHIFT      (8U)
#define DMA_TCD_TCD23_CSR_MAJORLINKCH_WIDTH      (5U)
#define DMA_TCD_TCD23_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD23_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD23_CSR_BWC_MASK               (0xC000U)
#define DMA_TCD_TCD23_CSR_BWC_SHIFT              (14U)
#define DMA_TCD_TCD23_CSR_BWC_WIDTH              (2U)
#define DMA_TCD_TCD23_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_CSR_BWC_SHIFT)) & DMA_TCD_TCD23_CSR_BWC_MASK)
/*! @} */

/*! @name TCD23_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD23_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD23_BITER_ELINKNO_BITER_SHIFT  (0U)
#define DMA_TCD_TCD23_BITER_ELINKNO_BITER_WIDTH  (15U)
#define DMA_TCD_TCD23_BITER_ELINKNO_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD23_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD23_BITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD23_BITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD23_BITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD23_BITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD23_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD23_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD23_BITER_ELINKYES_BITER_MASK  (0x1FFU)
#define DMA_TCD_TCD23_BITER_ELINKYES_BITER_SHIFT (0U)
#define DMA_TCD_TCD23_BITER_ELINKYES_BITER_WIDTH (9U)
#define DMA_TCD_TCD23_BITER_ELINKYES_BITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD23_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD23_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD23_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD23_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD23_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD23_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD23_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD23_BITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD23_BITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD23_BITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD23_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD23_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH24_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH24_CSR_ERQ_MASK                (0x1U)
#define DMA_TCD_CH24_CSR_ERQ_SHIFT               (0U)
#define DMA_TCD_CH24_CSR_ERQ_WIDTH               (1U)
#define DMA_TCD_CH24_CSR_ERQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_CSR_ERQ_SHIFT)) & DMA_TCD_CH24_CSR_ERQ_MASK)

#define DMA_TCD_CH24_CSR_EARQ_MASK               (0x2U)
#define DMA_TCD_CH24_CSR_EARQ_SHIFT              (1U)
#define DMA_TCD_CH24_CSR_EARQ_WIDTH              (1U)
#define DMA_TCD_CH24_CSR_EARQ(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_CSR_EARQ_SHIFT)) & DMA_TCD_CH24_CSR_EARQ_MASK)

#define DMA_TCD_CH24_CSR_EEI_MASK                (0x4U)
#define DMA_TCD_CH24_CSR_EEI_SHIFT               (2U)
#define DMA_TCD_CH24_CSR_EEI_WIDTH               (1U)
#define DMA_TCD_CH24_CSR_EEI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_CSR_EEI_SHIFT)) & DMA_TCD_CH24_CSR_EEI_MASK)

#define DMA_TCD_CH24_CSR_EBW_MASK                (0x8U)
#define DMA_TCD_CH24_CSR_EBW_SHIFT               (3U)
#define DMA_TCD_CH24_CSR_EBW_WIDTH               (1U)
#define DMA_TCD_CH24_CSR_EBW(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_CSR_EBW_SHIFT)) & DMA_TCD_CH24_CSR_EBW_MASK)

#define DMA_TCD_CH24_CSR_DONE_MASK               (0x40000000U)
#define DMA_TCD_CH24_CSR_DONE_SHIFT              (30U)
#define DMA_TCD_CH24_CSR_DONE_WIDTH              (1U)
#define DMA_TCD_CH24_CSR_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_CSR_DONE_SHIFT)) & DMA_TCD_CH24_CSR_DONE_MASK)

#define DMA_TCD_CH24_CSR_ACTIVE_MASK             (0x80000000U)
#define DMA_TCD_CH24_CSR_ACTIVE_SHIFT            (31U)
#define DMA_TCD_CH24_CSR_ACTIVE_WIDTH            (1U)
#define DMA_TCD_CH24_CSR_ACTIVE(x)               (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH24_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH24_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH24_ES_DBE_MASK                 (0x1U)
#define DMA_TCD_CH24_ES_DBE_SHIFT                (0U)
#define DMA_TCD_CH24_ES_DBE_WIDTH                (1U)
#define DMA_TCD_CH24_ES_DBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_ES_DBE_SHIFT)) & DMA_TCD_CH24_ES_DBE_MASK)

#define DMA_TCD_CH24_ES_SBE_MASK                 (0x2U)
#define DMA_TCD_CH24_ES_SBE_SHIFT                (1U)
#define DMA_TCD_CH24_ES_SBE_WIDTH                (1U)
#define DMA_TCD_CH24_ES_SBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_ES_SBE_SHIFT)) & DMA_TCD_CH24_ES_SBE_MASK)

#define DMA_TCD_CH24_ES_SGE_MASK                 (0x4U)
#define DMA_TCD_CH24_ES_SGE_SHIFT                (2U)
#define DMA_TCD_CH24_ES_SGE_WIDTH                (1U)
#define DMA_TCD_CH24_ES_SGE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_ES_SGE_SHIFT)) & DMA_TCD_CH24_ES_SGE_MASK)

#define DMA_TCD_CH24_ES_NCE_MASK                 (0x8U)
#define DMA_TCD_CH24_ES_NCE_SHIFT                (3U)
#define DMA_TCD_CH24_ES_NCE_WIDTH                (1U)
#define DMA_TCD_CH24_ES_NCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_ES_NCE_SHIFT)) & DMA_TCD_CH24_ES_NCE_MASK)

#define DMA_TCD_CH24_ES_DOE_MASK                 (0x10U)
#define DMA_TCD_CH24_ES_DOE_SHIFT                (4U)
#define DMA_TCD_CH24_ES_DOE_WIDTH                (1U)
#define DMA_TCD_CH24_ES_DOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_ES_DOE_SHIFT)) & DMA_TCD_CH24_ES_DOE_MASK)

#define DMA_TCD_CH24_ES_DAE_MASK                 (0x20U)
#define DMA_TCD_CH24_ES_DAE_SHIFT                (5U)
#define DMA_TCD_CH24_ES_DAE_WIDTH                (1U)
#define DMA_TCD_CH24_ES_DAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_ES_DAE_SHIFT)) & DMA_TCD_CH24_ES_DAE_MASK)

#define DMA_TCD_CH24_ES_SOE_MASK                 (0x40U)
#define DMA_TCD_CH24_ES_SOE_SHIFT                (6U)
#define DMA_TCD_CH24_ES_SOE_WIDTH                (1U)
#define DMA_TCD_CH24_ES_SOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_ES_SOE_SHIFT)) & DMA_TCD_CH24_ES_SOE_MASK)

#define DMA_TCD_CH24_ES_SAE_MASK                 (0x80U)
#define DMA_TCD_CH24_ES_SAE_SHIFT                (7U)
#define DMA_TCD_CH24_ES_SAE_WIDTH                (1U)
#define DMA_TCD_CH24_ES_SAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_ES_SAE_SHIFT)) & DMA_TCD_CH24_ES_SAE_MASK)

#define DMA_TCD_CH24_ES_ERR_MASK                 (0x80000000U)
#define DMA_TCD_CH24_ES_ERR_SHIFT                (31U)
#define DMA_TCD_CH24_ES_ERR_WIDTH                (1U)
#define DMA_TCD_CH24_ES_ERR(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_ES_ERR_SHIFT)) & DMA_TCD_CH24_ES_ERR_MASK)
/*! @} */

/*! @name CH24_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH24_INT_INT_MASK                (0x1U)
#define DMA_TCD_CH24_INT_INT_SHIFT               (0U)
#define DMA_TCD_CH24_INT_INT_WIDTH               (1U)
#define DMA_TCD_CH24_INT_INT(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_INT_INT_SHIFT)) & DMA_TCD_CH24_INT_INT_MASK)
/*! @} */

/*! @name CH24_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH24_SBR_MID_MASK                (0xFU)
#define DMA_TCD_CH24_SBR_MID_SHIFT               (0U)
#define DMA_TCD_CH24_SBR_MID_WIDTH               (4U)
#define DMA_TCD_CH24_SBR_MID(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_SBR_MID_SHIFT)) & DMA_TCD_CH24_SBR_MID_MASK)

#define DMA_TCD_CH24_SBR_PAL_MASK                (0x8000U)
#define DMA_TCD_CH24_SBR_PAL_SHIFT               (15U)
#define DMA_TCD_CH24_SBR_PAL_WIDTH               (1U)
#define DMA_TCD_CH24_SBR_PAL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_SBR_PAL_SHIFT)) & DMA_TCD_CH24_SBR_PAL_MASK)

#define DMA_TCD_CH24_SBR_EMI_MASK                (0x10000U)
#define DMA_TCD_CH24_SBR_EMI_SHIFT               (16U)
#define DMA_TCD_CH24_SBR_EMI_WIDTH               (1U)
#define DMA_TCD_CH24_SBR_EMI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_SBR_EMI_SHIFT)) & DMA_TCD_CH24_SBR_EMI_MASK)

#define DMA_TCD_CH24_SBR_ATTR_MASK               (0xE0000U)
#define DMA_TCD_CH24_SBR_ATTR_SHIFT              (17U)
#define DMA_TCD_CH24_SBR_ATTR_WIDTH              (3U)
#define DMA_TCD_CH24_SBR_ATTR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_SBR_ATTR_SHIFT)) & DMA_TCD_CH24_SBR_ATTR_MASK)
/*! @} */

/*! @name CH24_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH24_PRI_APL_MASK                (0x7U)
#define DMA_TCD_CH24_PRI_APL_SHIFT               (0U)
#define DMA_TCD_CH24_PRI_APL_WIDTH               (3U)
#define DMA_TCD_CH24_PRI_APL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_PRI_APL_SHIFT)) & DMA_TCD_CH24_PRI_APL_MASK)

#define DMA_TCD_CH24_PRI_DPA_MASK                (0x40000000U)
#define DMA_TCD_CH24_PRI_DPA_SHIFT               (30U)
#define DMA_TCD_CH24_PRI_DPA_WIDTH               (1U)
#define DMA_TCD_CH24_PRI_DPA(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_PRI_DPA_SHIFT)) & DMA_TCD_CH24_PRI_DPA_MASK)

#define DMA_TCD_CH24_PRI_ECP_MASK                (0x80000000U)
#define DMA_TCD_CH24_PRI_ECP_SHIFT               (31U)
#define DMA_TCD_CH24_PRI_ECP_WIDTH               (1U)
#define DMA_TCD_CH24_PRI_ECP(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH24_PRI_ECP_SHIFT)) & DMA_TCD_CH24_PRI_ECP_MASK)
/*! @} */

/*! @name TCD24_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD24_SADDR_SADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD24_SADDR_SADDR_SHIFT          (0U)
#define DMA_TCD_TCD24_SADDR_SADDR_WIDTH          (32U)
#define DMA_TCD_TCD24_SADDR_SADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD24_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD24_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD24_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD24_SOFF_SOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD24_SOFF_SOFF_SHIFT            (0U)
#define DMA_TCD_TCD24_SOFF_SOFF_WIDTH            (16U)
#define DMA_TCD_TCD24_SOFF_SOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD24_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD24_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD24_ATTR_DSIZE_MASK            (0x7U)
#define DMA_TCD_TCD24_ATTR_DSIZE_SHIFT           (0U)
#define DMA_TCD_TCD24_ATTR_DSIZE_WIDTH           (3U)
#define DMA_TCD_TCD24_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD24_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD24_ATTR_DMOD_MASK             (0xF8U)
#define DMA_TCD_TCD24_ATTR_DMOD_SHIFT            (3U)
#define DMA_TCD_TCD24_ATTR_DMOD_WIDTH            (5U)
#define DMA_TCD_TCD24_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD24_ATTR_DMOD_MASK)

#define DMA_TCD_TCD24_ATTR_SSIZE_MASK            (0x700U)
#define DMA_TCD_TCD24_ATTR_SSIZE_SHIFT           (8U)
#define DMA_TCD_TCD24_ATTR_SSIZE_WIDTH           (3U)
#define DMA_TCD_TCD24_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD24_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD24_ATTR_SMOD_MASK             (0xF800U)
#define DMA_TCD_TCD24_ATTR_SMOD_SHIFT            (11U)
#define DMA_TCD_TCD24_ATTR_SMOD_WIDTH            (5U)
#define DMA_TCD_TCD24_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD24_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD24_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD24_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_TCD_TCD24_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD24_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD24_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD24_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD24_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD24_NBYTES_MLOFFNO_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD24_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD24_NBYTES_MLOFFNO_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD24_NBYTES_MLOFFNO_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD24_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD24_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD24_NBYTES_MLOFFNO_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD24_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD24_NBYTES_MLOFFNO_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD24_NBYTES_MLOFFNO_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD24_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD24_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD24_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD24_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD24_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD24_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD24_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD24_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD24_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD24_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_TCD_TCD24_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD24_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD24_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD24_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD24_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD24_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_TCD_TCD24_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD24_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD24_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD24_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD24_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD24_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_TCD_TCD24_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD24_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD24_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD24_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD24_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD24_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD24_SLAST_SDA_SLAST_SDA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD24_SLAST_SDA_SLAST_SDA_SHIFT  (0U)
#define DMA_TCD_TCD24_SLAST_SDA_SLAST_SDA_WIDTH  (32U)
#define DMA_TCD_TCD24_SLAST_SDA_SLAST_SDA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD24_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD24_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD24_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD24_DADDR_DADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD24_DADDR_DADDR_SHIFT          (0U)
#define DMA_TCD_TCD24_DADDR_DADDR_WIDTH          (32U)
#define DMA_TCD_TCD24_DADDR_DADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD24_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD24_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD24_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD24_DOFF_DOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD24_DOFF_DOFF_SHIFT            (0U)
#define DMA_TCD_TCD24_DOFF_DOFF_WIDTH            (16U)
#define DMA_TCD_TCD24_DOFF_DOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD24_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD24_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD24_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD24_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_TCD_TCD24_CITER_ELINKNO_CITER_WIDTH  (15U)
#define DMA_TCD_TCD24_CITER_ELINKNO_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD24_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD24_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD24_CITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD24_CITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD24_CITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD24_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD24_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD24_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_TCD_TCD24_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_TCD_TCD24_CITER_ELINKYES_CITER_WIDTH (9U)
#define DMA_TCD_TCD24_CITER_ELINKYES_CITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD24_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD24_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD24_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD24_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD24_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD24_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD24_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD24_CITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD24_CITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD24_CITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD24_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD24_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD24_DLAST_SGA_DLAST_SGA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD24_DLAST_SGA_DLAST_SGA_SHIFT  (0U)
#define DMA_TCD_TCD24_DLAST_SGA_DLAST_SGA_WIDTH  (32U)
#define DMA_TCD_TCD24_DLAST_SGA_DLAST_SGA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD24_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD24_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD24_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD24_CSR_START_MASK             (0x1U)
#define DMA_TCD_TCD24_CSR_START_SHIFT            (0U)
#define DMA_TCD_TCD24_CSR_START_WIDTH            (1U)
#define DMA_TCD_TCD24_CSR_START(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_CSR_START_SHIFT)) & DMA_TCD_TCD24_CSR_START_MASK)

#define DMA_TCD_TCD24_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_TCD_TCD24_CSR_INTMAJOR_SHIFT         (1U)
#define DMA_TCD_TCD24_CSR_INTMAJOR_WIDTH         (1U)
#define DMA_TCD_TCD24_CSR_INTMAJOR(x)            (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD24_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD24_CSR_INTHALF_MASK           (0x4U)
#define DMA_TCD_TCD24_CSR_INTHALF_SHIFT          (2U)
#define DMA_TCD_TCD24_CSR_INTHALF_WIDTH          (1U)
#define DMA_TCD_TCD24_CSR_INTHALF(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD24_CSR_INTHALF_MASK)

#define DMA_TCD_TCD24_CSR_DREQ_MASK              (0x8U)
#define DMA_TCD_TCD24_CSR_DREQ_SHIFT             (3U)
#define DMA_TCD_TCD24_CSR_DREQ_WIDTH             (1U)
#define DMA_TCD_TCD24_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_CSR_DREQ_SHIFT)) & DMA_TCD_TCD24_CSR_DREQ_MASK)

#define DMA_TCD_TCD24_CSR_ESG_MASK               (0x10U)
#define DMA_TCD_TCD24_CSR_ESG_SHIFT              (4U)
#define DMA_TCD_TCD24_CSR_ESG_WIDTH              (1U)
#define DMA_TCD_TCD24_CSR_ESG(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_CSR_ESG_SHIFT)) & DMA_TCD_TCD24_CSR_ESG_MASK)

#define DMA_TCD_TCD24_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_TCD_TCD24_CSR_MAJORELINK_SHIFT       (5U)
#define DMA_TCD_TCD24_CSR_MAJORELINK_WIDTH       (1U)
#define DMA_TCD_TCD24_CSR_MAJORELINK(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD24_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD24_CSR_EEOP_MASK              (0x40U)
#define DMA_TCD_TCD24_CSR_EEOP_SHIFT             (6U)
#define DMA_TCD_TCD24_CSR_EEOP_WIDTH             (1U)
#define DMA_TCD_TCD24_CSR_EEOP(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_CSR_EEOP_SHIFT)) & DMA_TCD_TCD24_CSR_EEOP_MASK)

#define DMA_TCD_TCD24_CSR_ESDA_MASK              (0x80U)
#define DMA_TCD_TCD24_CSR_ESDA_SHIFT             (7U)
#define DMA_TCD_TCD24_CSR_ESDA_WIDTH             (1U)
#define DMA_TCD_TCD24_CSR_ESDA(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_CSR_ESDA_SHIFT)) & DMA_TCD_TCD24_CSR_ESDA_MASK)

#define DMA_TCD_TCD24_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_TCD_TCD24_CSR_MAJORLINKCH_SHIFT      (8U)
#define DMA_TCD_TCD24_CSR_MAJORLINKCH_WIDTH      (5U)
#define DMA_TCD_TCD24_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD24_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD24_CSR_BWC_MASK               (0xC000U)
#define DMA_TCD_TCD24_CSR_BWC_SHIFT              (14U)
#define DMA_TCD_TCD24_CSR_BWC_WIDTH              (2U)
#define DMA_TCD_TCD24_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_CSR_BWC_SHIFT)) & DMA_TCD_TCD24_CSR_BWC_MASK)
/*! @} */

/*! @name TCD24_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD24_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD24_BITER_ELINKNO_BITER_SHIFT  (0U)
#define DMA_TCD_TCD24_BITER_ELINKNO_BITER_WIDTH  (15U)
#define DMA_TCD_TCD24_BITER_ELINKNO_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD24_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD24_BITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD24_BITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD24_BITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD24_BITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD24_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD24_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD24_BITER_ELINKYES_BITER_MASK  (0x1FFU)
#define DMA_TCD_TCD24_BITER_ELINKYES_BITER_SHIFT (0U)
#define DMA_TCD_TCD24_BITER_ELINKYES_BITER_WIDTH (9U)
#define DMA_TCD_TCD24_BITER_ELINKYES_BITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD24_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD24_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD24_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD24_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD24_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD24_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD24_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD24_BITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD24_BITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD24_BITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD24_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD24_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH25_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH25_CSR_ERQ_MASK                (0x1U)
#define DMA_TCD_CH25_CSR_ERQ_SHIFT               (0U)
#define DMA_TCD_CH25_CSR_ERQ_WIDTH               (1U)
#define DMA_TCD_CH25_CSR_ERQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_CSR_ERQ_SHIFT)) & DMA_TCD_CH25_CSR_ERQ_MASK)

#define DMA_TCD_CH25_CSR_EARQ_MASK               (0x2U)
#define DMA_TCD_CH25_CSR_EARQ_SHIFT              (1U)
#define DMA_TCD_CH25_CSR_EARQ_WIDTH              (1U)
#define DMA_TCD_CH25_CSR_EARQ(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_CSR_EARQ_SHIFT)) & DMA_TCD_CH25_CSR_EARQ_MASK)

#define DMA_TCD_CH25_CSR_EEI_MASK                (0x4U)
#define DMA_TCD_CH25_CSR_EEI_SHIFT               (2U)
#define DMA_TCD_CH25_CSR_EEI_WIDTH               (1U)
#define DMA_TCD_CH25_CSR_EEI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_CSR_EEI_SHIFT)) & DMA_TCD_CH25_CSR_EEI_MASK)

#define DMA_TCD_CH25_CSR_EBW_MASK                (0x8U)
#define DMA_TCD_CH25_CSR_EBW_SHIFT               (3U)
#define DMA_TCD_CH25_CSR_EBW_WIDTH               (1U)
#define DMA_TCD_CH25_CSR_EBW(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_CSR_EBW_SHIFT)) & DMA_TCD_CH25_CSR_EBW_MASK)

#define DMA_TCD_CH25_CSR_DONE_MASK               (0x40000000U)
#define DMA_TCD_CH25_CSR_DONE_SHIFT              (30U)
#define DMA_TCD_CH25_CSR_DONE_WIDTH              (1U)
#define DMA_TCD_CH25_CSR_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_CSR_DONE_SHIFT)) & DMA_TCD_CH25_CSR_DONE_MASK)

#define DMA_TCD_CH25_CSR_ACTIVE_MASK             (0x80000000U)
#define DMA_TCD_CH25_CSR_ACTIVE_SHIFT            (31U)
#define DMA_TCD_CH25_CSR_ACTIVE_WIDTH            (1U)
#define DMA_TCD_CH25_CSR_ACTIVE(x)               (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH25_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH25_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH25_ES_DBE_MASK                 (0x1U)
#define DMA_TCD_CH25_ES_DBE_SHIFT                (0U)
#define DMA_TCD_CH25_ES_DBE_WIDTH                (1U)
#define DMA_TCD_CH25_ES_DBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_ES_DBE_SHIFT)) & DMA_TCD_CH25_ES_DBE_MASK)

#define DMA_TCD_CH25_ES_SBE_MASK                 (0x2U)
#define DMA_TCD_CH25_ES_SBE_SHIFT                (1U)
#define DMA_TCD_CH25_ES_SBE_WIDTH                (1U)
#define DMA_TCD_CH25_ES_SBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_ES_SBE_SHIFT)) & DMA_TCD_CH25_ES_SBE_MASK)

#define DMA_TCD_CH25_ES_SGE_MASK                 (0x4U)
#define DMA_TCD_CH25_ES_SGE_SHIFT                (2U)
#define DMA_TCD_CH25_ES_SGE_WIDTH                (1U)
#define DMA_TCD_CH25_ES_SGE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_ES_SGE_SHIFT)) & DMA_TCD_CH25_ES_SGE_MASK)

#define DMA_TCD_CH25_ES_NCE_MASK                 (0x8U)
#define DMA_TCD_CH25_ES_NCE_SHIFT                (3U)
#define DMA_TCD_CH25_ES_NCE_WIDTH                (1U)
#define DMA_TCD_CH25_ES_NCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_ES_NCE_SHIFT)) & DMA_TCD_CH25_ES_NCE_MASK)

#define DMA_TCD_CH25_ES_DOE_MASK                 (0x10U)
#define DMA_TCD_CH25_ES_DOE_SHIFT                (4U)
#define DMA_TCD_CH25_ES_DOE_WIDTH                (1U)
#define DMA_TCD_CH25_ES_DOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_ES_DOE_SHIFT)) & DMA_TCD_CH25_ES_DOE_MASK)

#define DMA_TCD_CH25_ES_DAE_MASK                 (0x20U)
#define DMA_TCD_CH25_ES_DAE_SHIFT                (5U)
#define DMA_TCD_CH25_ES_DAE_WIDTH                (1U)
#define DMA_TCD_CH25_ES_DAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_ES_DAE_SHIFT)) & DMA_TCD_CH25_ES_DAE_MASK)

#define DMA_TCD_CH25_ES_SOE_MASK                 (0x40U)
#define DMA_TCD_CH25_ES_SOE_SHIFT                (6U)
#define DMA_TCD_CH25_ES_SOE_WIDTH                (1U)
#define DMA_TCD_CH25_ES_SOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_ES_SOE_SHIFT)) & DMA_TCD_CH25_ES_SOE_MASK)

#define DMA_TCD_CH25_ES_SAE_MASK                 (0x80U)
#define DMA_TCD_CH25_ES_SAE_SHIFT                (7U)
#define DMA_TCD_CH25_ES_SAE_WIDTH                (1U)
#define DMA_TCD_CH25_ES_SAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_ES_SAE_SHIFT)) & DMA_TCD_CH25_ES_SAE_MASK)

#define DMA_TCD_CH25_ES_ERR_MASK                 (0x80000000U)
#define DMA_TCD_CH25_ES_ERR_SHIFT                (31U)
#define DMA_TCD_CH25_ES_ERR_WIDTH                (1U)
#define DMA_TCD_CH25_ES_ERR(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_ES_ERR_SHIFT)) & DMA_TCD_CH25_ES_ERR_MASK)
/*! @} */

/*! @name CH25_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH25_INT_INT_MASK                (0x1U)
#define DMA_TCD_CH25_INT_INT_SHIFT               (0U)
#define DMA_TCD_CH25_INT_INT_WIDTH               (1U)
#define DMA_TCD_CH25_INT_INT(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_INT_INT_SHIFT)) & DMA_TCD_CH25_INT_INT_MASK)
/*! @} */

/*! @name CH25_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH25_SBR_MID_MASK                (0xFU)
#define DMA_TCD_CH25_SBR_MID_SHIFT               (0U)
#define DMA_TCD_CH25_SBR_MID_WIDTH               (4U)
#define DMA_TCD_CH25_SBR_MID(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_SBR_MID_SHIFT)) & DMA_TCD_CH25_SBR_MID_MASK)

#define DMA_TCD_CH25_SBR_PAL_MASK                (0x8000U)
#define DMA_TCD_CH25_SBR_PAL_SHIFT               (15U)
#define DMA_TCD_CH25_SBR_PAL_WIDTH               (1U)
#define DMA_TCD_CH25_SBR_PAL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_SBR_PAL_SHIFT)) & DMA_TCD_CH25_SBR_PAL_MASK)

#define DMA_TCD_CH25_SBR_EMI_MASK                (0x10000U)
#define DMA_TCD_CH25_SBR_EMI_SHIFT               (16U)
#define DMA_TCD_CH25_SBR_EMI_WIDTH               (1U)
#define DMA_TCD_CH25_SBR_EMI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_SBR_EMI_SHIFT)) & DMA_TCD_CH25_SBR_EMI_MASK)

#define DMA_TCD_CH25_SBR_ATTR_MASK               (0xE0000U)
#define DMA_TCD_CH25_SBR_ATTR_SHIFT              (17U)
#define DMA_TCD_CH25_SBR_ATTR_WIDTH              (3U)
#define DMA_TCD_CH25_SBR_ATTR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_SBR_ATTR_SHIFT)) & DMA_TCD_CH25_SBR_ATTR_MASK)
/*! @} */

/*! @name CH25_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH25_PRI_APL_MASK                (0x7U)
#define DMA_TCD_CH25_PRI_APL_SHIFT               (0U)
#define DMA_TCD_CH25_PRI_APL_WIDTH               (3U)
#define DMA_TCD_CH25_PRI_APL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_PRI_APL_SHIFT)) & DMA_TCD_CH25_PRI_APL_MASK)

#define DMA_TCD_CH25_PRI_DPA_MASK                (0x40000000U)
#define DMA_TCD_CH25_PRI_DPA_SHIFT               (30U)
#define DMA_TCD_CH25_PRI_DPA_WIDTH               (1U)
#define DMA_TCD_CH25_PRI_DPA(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_PRI_DPA_SHIFT)) & DMA_TCD_CH25_PRI_DPA_MASK)

#define DMA_TCD_CH25_PRI_ECP_MASK                (0x80000000U)
#define DMA_TCD_CH25_PRI_ECP_SHIFT               (31U)
#define DMA_TCD_CH25_PRI_ECP_WIDTH               (1U)
#define DMA_TCD_CH25_PRI_ECP(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH25_PRI_ECP_SHIFT)) & DMA_TCD_CH25_PRI_ECP_MASK)
/*! @} */

/*! @name TCD25_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD25_SADDR_SADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD25_SADDR_SADDR_SHIFT          (0U)
#define DMA_TCD_TCD25_SADDR_SADDR_WIDTH          (32U)
#define DMA_TCD_TCD25_SADDR_SADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD25_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD25_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD25_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD25_SOFF_SOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD25_SOFF_SOFF_SHIFT            (0U)
#define DMA_TCD_TCD25_SOFF_SOFF_WIDTH            (16U)
#define DMA_TCD_TCD25_SOFF_SOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD25_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD25_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD25_ATTR_DSIZE_MASK            (0x7U)
#define DMA_TCD_TCD25_ATTR_DSIZE_SHIFT           (0U)
#define DMA_TCD_TCD25_ATTR_DSIZE_WIDTH           (3U)
#define DMA_TCD_TCD25_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD25_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD25_ATTR_DMOD_MASK             (0xF8U)
#define DMA_TCD_TCD25_ATTR_DMOD_SHIFT            (3U)
#define DMA_TCD_TCD25_ATTR_DMOD_WIDTH            (5U)
#define DMA_TCD_TCD25_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD25_ATTR_DMOD_MASK)

#define DMA_TCD_TCD25_ATTR_SSIZE_MASK            (0x700U)
#define DMA_TCD_TCD25_ATTR_SSIZE_SHIFT           (8U)
#define DMA_TCD_TCD25_ATTR_SSIZE_WIDTH           (3U)
#define DMA_TCD_TCD25_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD25_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD25_ATTR_SMOD_MASK             (0xF800U)
#define DMA_TCD_TCD25_ATTR_SMOD_SHIFT            (11U)
#define DMA_TCD_TCD25_ATTR_SMOD_WIDTH            (5U)
#define DMA_TCD_TCD25_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD25_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD25_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD25_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_TCD_TCD25_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD25_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD25_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD25_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD25_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD25_NBYTES_MLOFFNO_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD25_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD25_NBYTES_MLOFFNO_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD25_NBYTES_MLOFFNO_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD25_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD25_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD25_NBYTES_MLOFFNO_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD25_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD25_NBYTES_MLOFFNO_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD25_NBYTES_MLOFFNO_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD25_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD25_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD25_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD25_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD25_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD25_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD25_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD25_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD25_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD25_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_TCD_TCD25_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD25_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD25_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD25_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD25_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD25_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_TCD_TCD25_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD25_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD25_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD25_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD25_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD25_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_TCD_TCD25_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD25_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD25_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD25_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD25_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD25_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD25_SLAST_SDA_SLAST_SDA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD25_SLAST_SDA_SLAST_SDA_SHIFT  (0U)
#define DMA_TCD_TCD25_SLAST_SDA_SLAST_SDA_WIDTH  (32U)
#define DMA_TCD_TCD25_SLAST_SDA_SLAST_SDA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD25_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD25_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD25_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD25_DADDR_DADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD25_DADDR_DADDR_SHIFT          (0U)
#define DMA_TCD_TCD25_DADDR_DADDR_WIDTH          (32U)
#define DMA_TCD_TCD25_DADDR_DADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD25_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD25_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD25_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD25_DOFF_DOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD25_DOFF_DOFF_SHIFT            (0U)
#define DMA_TCD_TCD25_DOFF_DOFF_WIDTH            (16U)
#define DMA_TCD_TCD25_DOFF_DOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD25_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD25_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD25_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD25_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_TCD_TCD25_CITER_ELINKNO_CITER_WIDTH  (15U)
#define DMA_TCD_TCD25_CITER_ELINKNO_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD25_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD25_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD25_CITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD25_CITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD25_CITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD25_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD25_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD25_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_TCD_TCD25_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_TCD_TCD25_CITER_ELINKYES_CITER_WIDTH (9U)
#define DMA_TCD_TCD25_CITER_ELINKYES_CITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD25_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD25_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD25_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD25_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD25_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD25_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD25_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD25_CITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD25_CITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD25_CITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD25_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD25_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD25_DLAST_SGA_DLAST_SGA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD25_DLAST_SGA_DLAST_SGA_SHIFT  (0U)
#define DMA_TCD_TCD25_DLAST_SGA_DLAST_SGA_WIDTH  (32U)
#define DMA_TCD_TCD25_DLAST_SGA_DLAST_SGA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD25_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD25_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD25_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD25_CSR_START_MASK             (0x1U)
#define DMA_TCD_TCD25_CSR_START_SHIFT            (0U)
#define DMA_TCD_TCD25_CSR_START_WIDTH            (1U)
#define DMA_TCD_TCD25_CSR_START(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_CSR_START_SHIFT)) & DMA_TCD_TCD25_CSR_START_MASK)

#define DMA_TCD_TCD25_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_TCD_TCD25_CSR_INTMAJOR_SHIFT         (1U)
#define DMA_TCD_TCD25_CSR_INTMAJOR_WIDTH         (1U)
#define DMA_TCD_TCD25_CSR_INTMAJOR(x)            (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD25_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD25_CSR_INTHALF_MASK           (0x4U)
#define DMA_TCD_TCD25_CSR_INTHALF_SHIFT          (2U)
#define DMA_TCD_TCD25_CSR_INTHALF_WIDTH          (1U)
#define DMA_TCD_TCD25_CSR_INTHALF(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD25_CSR_INTHALF_MASK)

#define DMA_TCD_TCD25_CSR_DREQ_MASK              (0x8U)
#define DMA_TCD_TCD25_CSR_DREQ_SHIFT             (3U)
#define DMA_TCD_TCD25_CSR_DREQ_WIDTH             (1U)
#define DMA_TCD_TCD25_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_CSR_DREQ_SHIFT)) & DMA_TCD_TCD25_CSR_DREQ_MASK)

#define DMA_TCD_TCD25_CSR_ESG_MASK               (0x10U)
#define DMA_TCD_TCD25_CSR_ESG_SHIFT              (4U)
#define DMA_TCD_TCD25_CSR_ESG_WIDTH              (1U)
#define DMA_TCD_TCD25_CSR_ESG(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_CSR_ESG_SHIFT)) & DMA_TCD_TCD25_CSR_ESG_MASK)

#define DMA_TCD_TCD25_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_TCD_TCD25_CSR_MAJORELINK_SHIFT       (5U)
#define DMA_TCD_TCD25_CSR_MAJORELINK_WIDTH       (1U)
#define DMA_TCD_TCD25_CSR_MAJORELINK(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD25_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD25_CSR_EEOP_MASK              (0x40U)
#define DMA_TCD_TCD25_CSR_EEOP_SHIFT             (6U)
#define DMA_TCD_TCD25_CSR_EEOP_WIDTH             (1U)
#define DMA_TCD_TCD25_CSR_EEOP(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_CSR_EEOP_SHIFT)) & DMA_TCD_TCD25_CSR_EEOP_MASK)

#define DMA_TCD_TCD25_CSR_ESDA_MASK              (0x80U)
#define DMA_TCD_TCD25_CSR_ESDA_SHIFT             (7U)
#define DMA_TCD_TCD25_CSR_ESDA_WIDTH             (1U)
#define DMA_TCD_TCD25_CSR_ESDA(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_CSR_ESDA_SHIFT)) & DMA_TCD_TCD25_CSR_ESDA_MASK)

#define DMA_TCD_TCD25_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_TCD_TCD25_CSR_MAJORLINKCH_SHIFT      (8U)
#define DMA_TCD_TCD25_CSR_MAJORLINKCH_WIDTH      (5U)
#define DMA_TCD_TCD25_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD25_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD25_CSR_BWC_MASK               (0xC000U)
#define DMA_TCD_TCD25_CSR_BWC_SHIFT              (14U)
#define DMA_TCD_TCD25_CSR_BWC_WIDTH              (2U)
#define DMA_TCD_TCD25_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_CSR_BWC_SHIFT)) & DMA_TCD_TCD25_CSR_BWC_MASK)
/*! @} */

/*! @name TCD25_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD25_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD25_BITER_ELINKNO_BITER_SHIFT  (0U)
#define DMA_TCD_TCD25_BITER_ELINKNO_BITER_WIDTH  (15U)
#define DMA_TCD_TCD25_BITER_ELINKNO_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD25_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD25_BITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD25_BITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD25_BITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD25_BITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD25_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD25_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD25_BITER_ELINKYES_BITER_MASK  (0x1FFU)
#define DMA_TCD_TCD25_BITER_ELINKYES_BITER_SHIFT (0U)
#define DMA_TCD_TCD25_BITER_ELINKYES_BITER_WIDTH (9U)
#define DMA_TCD_TCD25_BITER_ELINKYES_BITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD25_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD25_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD25_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD25_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD25_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD25_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD25_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD25_BITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD25_BITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD25_BITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD25_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD25_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH26_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH26_CSR_ERQ_MASK                (0x1U)
#define DMA_TCD_CH26_CSR_ERQ_SHIFT               (0U)
#define DMA_TCD_CH26_CSR_ERQ_WIDTH               (1U)
#define DMA_TCD_CH26_CSR_ERQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_CSR_ERQ_SHIFT)) & DMA_TCD_CH26_CSR_ERQ_MASK)

#define DMA_TCD_CH26_CSR_EARQ_MASK               (0x2U)
#define DMA_TCD_CH26_CSR_EARQ_SHIFT              (1U)
#define DMA_TCD_CH26_CSR_EARQ_WIDTH              (1U)
#define DMA_TCD_CH26_CSR_EARQ(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_CSR_EARQ_SHIFT)) & DMA_TCD_CH26_CSR_EARQ_MASK)

#define DMA_TCD_CH26_CSR_EEI_MASK                (0x4U)
#define DMA_TCD_CH26_CSR_EEI_SHIFT               (2U)
#define DMA_TCD_CH26_CSR_EEI_WIDTH               (1U)
#define DMA_TCD_CH26_CSR_EEI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_CSR_EEI_SHIFT)) & DMA_TCD_CH26_CSR_EEI_MASK)

#define DMA_TCD_CH26_CSR_EBW_MASK                (0x8U)
#define DMA_TCD_CH26_CSR_EBW_SHIFT               (3U)
#define DMA_TCD_CH26_CSR_EBW_WIDTH               (1U)
#define DMA_TCD_CH26_CSR_EBW(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_CSR_EBW_SHIFT)) & DMA_TCD_CH26_CSR_EBW_MASK)

#define DMA_TCD_CH26_CSR_DONE_MASK               (0x40000000U)
#define DMA_TCD_CH26_CSR_DONE_SHIFT              (30U)
#define DMA_TCD_CH26_CSR_DONE_WIDTH              (1U)
#define DMA_TCD_CH26_CSR_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_CSR_DONE_SHIFT)) & DMA_TCD_CH26_CSR_DONE_MASK)

#define DMA_TCD_CH26_CSR_ACTIVE_MASK             (0x80000000U)
#define DMA_TCD_CH26_CSR_ACTIVE_SHIFT            (31U)
#define DMA_TCD_CH26_CSR_ACTIVE_WIDTH            (1U)
#define DMA_TCD_CH26_CSR_ACTIVE(x)               (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH26_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH26_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH26_ES_DBE_MASK                 (0x1U)
#define DMA_TCD_CH26_ES_DBE_SHIFT                (0U)
#define DMA_TCD_CH26_ES_DBE_WIDTH                (1U)
#define DMA_TCD_CH26_ES_DBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_ES_DBE_SHIFT)) & DMA_TCD_CH26_ES_DBE_MASK)

#define DMA_TCD_CH26_ES_SBE_MASK                 (0x2U)
#define DMA_TCD_CH26_ES_SBE_SHIFT                (1U)
#define DMA_TCD_CH26_ES_SBE_WIDTH                (1U)
#define DMA_TCD_CH26_ES_SBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_ES_SBE_SHIFT)) & DMA_TCD_CH26_ES_SBE_MASK)

#define DMA_TCD_CH26_ES_SGE_MASK                 (0x4U)
#define DMA_TCD_CH26_ES_SGE_SHIFT                (2U)
#define DMA_TCD_CH26_ES_SGE_WIDTH                (1U)
#define DMA_TCD_CH26_ES_SGE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_ES_SGE_SHIFT)) & DMA_TCD_CH26_ES_SGE_MASK)

#define DMA_TCD_CH26_ES_NCE_MASK                 (0x8U)
#define DMA_TCD_CH26_ES_NCE_SHIFT                (3U)
#define DMA_TCD_CH26_ES_NCE_WIDTH                (1U)
#define DMA_TCD_CH26_ES_NCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_ES_NCE_SHIFT)) & DMA_TCD_CH26_ES_NCE_MASK)

#define DMA_TCD_CH26_ES_DOE_MASK                 (0x10U)
#define DMA_TCD_CH26_ES_DOE_SHIFT                (4U)
#define DMA_TCD_CH26_ES_DOE_WIDTH                (1U)
#define DMA_TCD_CH26_ES_DOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_ES_DOE_SHIFT)) & DMA_TCD_CH26_ES_DOE_MASK)

#define DMA_TCD_CH26_ES_DAE_MASK                 (0x20U)
#define DMA_TCD_CH26_ES_DAE_SHIFT                (5U)
#define DMA_TCD_CH26_ES_DAE_WIDTH                (1U)
#define DMA_TCD_CH26_ES_DAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_ES_DAE_SHIFT)) & DMA_TCD_CH26_ES_DAE_MASK)

#define DMA_TCD_CH26_ES_SOE_MASK                 (0x40U)
#define DMA_TCD_CH26_ES_SOE_SHIFT                (6U)
#define DMA_TCD_CH26_ES_SOE_WIDTH                (1U)
#define DMA_TCD_CH26_ES_SOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_ES_SOE_SHIFT)) & DMA_TCD_CH26_ES_SOE_MASK)

#define DMA_TCD_CH26_ES_SAE_MASK                 (0x80U)
#define DMA_TCD_CH26_ES_SAE_SHIFT                (7U)
#define DMA_TCD_CH26_ES_SAE_WIDTH                (1U)
#define DMA_TCD_CH26_ES_SAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_ES_SAE_SHIFT)) & DMA_TCD_CH26_ES_SAE_MASK)

#define DMA_TCD_CH26_ES_ERR_MASK                 (0x80000000U)
#define DMA_TCD_CH26_ES_ERR_SHIFT                (31U)
#define DMA_TCD_CH26_ES_ERR_WIDTH                (1U)
#define DMA_TCD_CH26_ES_ERR(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_ES_ERR_SHIFT)) & DMA_TCD_CH26_ES_ERR_MASK)
/*! @} */

/*! @name CH26_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH26_INT_INT_MASK                (0x1U)
#define DMA_TCD_CH26_INT_INT_SHIFT               (0U)
#define DMA_TCD_CH26_INT_INT_WIDTH               (1U)
#define DMA_TCD_CH26_INT_INT(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_INT_INT_SHIFT)) & DMA_TCD_CH26_INT_INT_MASK)
/*! @} */

/*! @name CH26_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH26_SBR_MID_MASK                (0xFU)
#define DMA_TCD_CH26_SBR_MID_SHIFT               (0U)
#define DMA_TCD_CH26_SBR_MID_WIDTH               (4U)
#define DMA_TCD_CH26_SBR_MID(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_SBR_MID_SHIFT)) & DMA_TCD_CH26_SBR_MID_MASK)

#define DMA_TCD_CH26_SBR_PAL_MASK                (0x8000U)
#define DMA_TCD_CH26_SBR_PAL_SHIFT               (15U)
#define DMA_TCD_CH26_SBR_PAL_WIDTH               (1U)
#define DMA_TCD_CH26_SBR_PAL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_SBR_PAL_SHIFT)) & DMA_TCD_CH26_SBR_PAL_MASK)

#define DMA_TCD_CH26_SBR_EMI_MASK                (0x10000U)
#define DMA_TCD_CH26_SBR_EMI_SHIFT               (16U)
#define DMA_TCD_CH26_SBR_EMI_WIDTH               (1U)
#define DMA_TCD_CH26_SBR_EMI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_SBR_EMI_SHIFT)) & DMA_TCD_CH26_SBR_EMI_MASK)

#define DMA_TCD_CH26_SBR_ATTR_MASK               (0xE0000U)
#define DMA_TCD_CH26_SBR_ATTR_SHIFT              (17U)
#define DMA_TCD_CH26_SBR_ATTR_WIDTH              (3U)
#define DMA_TCD_CH26_SBR_ATTR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_SBR_ATTR_SHIFT)) & DMA_TCD_CH26_SBR_ATTR_MASK)
/*! @} */

/*! @name CH26_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH26_PRI_APL_MASK                (0x7U)
#define DMA_TCD_CH26_PRI_APL_SHIFT               (0U)
#define DMA_TCD_CH26_PRI_APL_WIDTH               (3U)
#define DMA_TCD_CH26_PRI_APL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_PRI_APL_SHIFT)) & DMA_TCD_CH26_PRI_APL_MASK)

#define DMA_TCD_CH26_PRI_DPA_MASK                (0x40000000U)
#define DMA_TCD_CH26_PRI_DPA_SHIFT               (30U)
#define DMA_TCD_CH26_PRI_DPA_WIDTH               (1U)
#define DMA_TCD_CH26_PRI_DPA(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_PRI_DPA_SHIFT)) & DMA_TCD_CH26_PRI_DPA_MASK)

#define DMA_TCD_CH26_PRI_ECP_MASK                (0x80000000U)
#define DMA_TCD_CH26_PRI_ECP_SHIFT               (31U)
#define DMA_TCD_CH26_PRI_ECP_WIDTH               (1U)
#define DMA_TCD_CH26_PRI_ECP(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH26_PRI_ECP_SHIFT)) & DMA_TCD_CH26_PRI_ECP_MASK)
/*! @} */

/*! @name TCD26_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD26_SADDR_SADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD26_SADDR_SADDR_SHIFT          (0U)
#define DMA_TCD_TCD26_SADDR_SADDR_WIDTH          (32U)
#define DMA_TCD_TCD26_SADDR_SADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD26_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD26_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD26_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD26_SOFF_SOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD26_SOFF_SOFF_SHIFT            (0U)
#define DMA_TCD_TCD26_SOFF_SOFF_WIDTH            (16U)
#define DMA_TCD_TCD26_SOFF_SOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD26_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD26_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD26_ATTR_DSIZE_MASK            (0x7U)
#define DMA_TCD_TCD26_ATTR_DSIZE_SHIFT           (0U)
#define DMA_TCD_TCD26_ATTR_DSIZE_WIDTH           (3U)
#define DMA_TCD_TCD26_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD26_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD26_ATTR_DMOD_MASK             (0xF8U)
#define DMA_TCD_TCD26_ATTR_DMOD_SHIFT            (3U)
#define DMA_TCD_TCD26_ATTR_DMOD_WIDTH            (5U)
#define DMA_TCD_TCD26_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD26_ATTR_DMOD_MASK)

#define DMA_TCD_TCD26_ATTR_SSIZE_MASK            (0x700U)
#define DMA_TCD_TCD26_ATTR_SSIZE_SHIFT           (8U)
#define DMA_TCD_TCD26_ATTR_SSIZE_WIDTH           (3U)
#define DMA_TCD_TCD26_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD26_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD26_ATTR_SMOD_MASK             (0xF800U)
#define DMA_TCD_TCD26_ATTR_SMOD_SHIFT            (11U)
#define DMA_TCD_TCD26_ATTR_SMOD_WIDTH            (5U)
#define DMA_TCD_TCD26_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD26_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD26_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD26_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_TCD_TCD26_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD26_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD26_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD26_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD26_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD26_NBYTES_MLOFFNO_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD26_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD26_NBYTES_MLOFFNO_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD26_NBYTES_MLOFFNO_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD26_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD26_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD26_NBYTES_MLOFFNO_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD26_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD26_NBYTES_MLOFFNO_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD26_NBYTES_MLOFFNO_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD26_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD26_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD26_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD26_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD26_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD26_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD26_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD26_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD26_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD26_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_TCD_TCD26_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD26_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD26_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD26_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD26_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD26_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_TCD_TCD26_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD26_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD26_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD26_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD26_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD26_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_TCD_TCD26_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD26_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD26_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD26_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD26_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD26_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD26_SLAST_SDA_SLAST_SDA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD26_SLAST_SDA_SLAST_SDA_SHIFT  (0U)
#define DMA_TCD_TCD26_SLAST_SDA_SLAST_SDA_WIDTH  (32U)
#define DMA_TCD_TCD26_SLAST_SDA_SLAST_SDA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD26_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD26_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD26_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD26_DADDR_DADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD26_DADDR_DADDR_SHIFT          (0U)
#define DMA_TCD_TCD26_DADDR_DADDR_WIDTH          (32U)
#define DMA_TCD_TCD26_DADDR_DADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD26_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD26_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD26_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD26_DOFF_DOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD26_DOFF_DOFF_SHIFT            (0U)
#define DMA_TCD_TCD26_DOFF_DOFF_WIDTH            (16U)
#define DMA_TCD_TCD26_DOFF_DOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD26_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD26_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD26_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD26_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_TCD_TCD26_CITER_ELINKNO_CITER_WIDTH  (15U)
#define DMA_TCD_TCD26_CITER_ELINKNO_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD26_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD26_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD26_CITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD26_CITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD26_CITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD26_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD26_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD26_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_TCD_TCD26_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_TCD_TCD26_CITER_ELINKYES_CITER_WIDTH (9U)
#define DMA_TCD_TCD26_CITER_ELINKYES_CITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD26_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD26_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD26_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD26_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD26_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD26_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD26_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD26_CITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD26_CITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD26_CITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD26_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD26_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD26_DLAST_SGA_DLAST_SGA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD26_DLAST_SGA_DLAST_SGA_SHIFT  (0U)
#define DMA_TCD_TCD26_DLAST_SGA_DLAST_SGA_WIDTH  (32U)
#define DMA_TCD_TCD26_DLAST_SGA_DLAST_SGA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD26_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD26_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD26_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD26_CSR_START_MASK             (0x1U)
#define DMA_TCD_TCD26_CSR_START_SHIFT            (0U)
#define DMA_TCD_TCD26_CSR_START_WIDTH            (1U)
#define DMA_TCD_TCD26_CSR_START(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_CSR_START_SHIFT)) & DMA_TCD_TCD26_CSR_START_MASK)

#define DMA_TCD_TCD26_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_TCD_TCD26_CSR_INTMAJOR_SHIFT         (1U)
#define DMA_TCD_TCD26_CSR_INTMAJOR_WIDTH         (1U)
#define DMA_TCD_TCD26_CSR_INTMAJOR(x)            (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD26_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD26_CSR_INTHALF_MASK           (0x4U)
#define DMA_TCD_TCD26_CSR_INTHALF_SHIFT          (2U)
#define DMA_TCD_TCD26_CSR_INTHALF_WIDTH          (1U)
#define DMA_TCD_TCD26_CSR_INTHALF(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD26_CSR_INTHALF_MASK)

#define DMA_TCD_TCD26_CSR_DREQ_MASK              (0x8U)
#define DMA_TCD_TCD26_CSR_DREQ_SHIFT             (3U)
#define DMA_TCD_TCD26_CSR_DREQ_WIDTH             (1U)
#define DMA_TCD_TCD26_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_CSR_DREQ_SHIFT)) & DMA_TCD_TCD26_CSR_DREQ_MASK)

#define DMA_TCD_TCD26_CSR_ESG_MASK               (0x10U)
#define DMA_TCD_TCD26_CSR_ESG_SHIFT              (4U)
#define DMA_TCD_TCD26_CSR_ESG_WIDTH              (1U)
#define DMA_TCD_TCD26_CSR_ESG(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_CSR_ESG_SHIFT)) & DMA_TCD_TCD26_CSR_ESG_MASK)

#define DMA_TCD_TCD26_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_TCD_TCD26_CSR_MAJORELINK_SHIFT       (5U)
#define DMA_TCD_TCD26_CSR_MAJORELINK_WIDTH       (1U)
#define DMA_TCD_TCD26_CSR_MAJORELINK(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD26_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD26_CSR_EEOP_MASK              (0x40U)
#define DMA_TCD_TCD26_CSR_EEOP_SHIFT             (6U)
#define DMA_TCD_TCD26_CSR_EEOP_WIDTH             (1U)
#define DMA_TCD_TCD26_CSR_EEOP(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_CSR_EEOP_SHIFT)) & DMA_TCD_TCD26_CSR_EEOP_MASK)

#define DMA_TCD_TCD26_CSR_ESDA_MASK              (0x80U)
#define DMA_TCD_TCD26_CSR_ESDA_SHIFT             (7U)
#define DMA_TCD_TCD26_CSR_ESDA_WIDTH             (1U)
#define DMA_TCD_TCD26_CSR_ESDA(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_CSR_ESDA_SHIFT)) & DMA_TCD_TCD26_CSR_ESDA_MASK)

#define DMA_TCD_TCD26_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_TCD_TCD26_CSR_MAJORLINKCH_SHIFT      (8U)
#define DMA_TCD_TCD26_CSR_MAJORLINKCH_WIDTH      (5U)
#define DMA_TCD_TCD26_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD26_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD26_CSR_BWC_MASK               (0xC000U)
#define DMA_TCD_TCD26_CSR_BWC_SHIFT              (14U)
#define DMA_TCD_TCD26_CSR_BWC_WIDTH              (2U)
#define DMA_TCD_TCD26_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_CSR_BWC_SHIFT)) & DMA_TCD_TCD26_CSR_BWC_MASK)
/*! @} */

/*! @name TCD26_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD26_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD26_BITER_ELINKNO_BITER_SHIFT  (0U)
#define DMA_TCD_TCD26_BITER_ELINKNO_BITER_WIDTH  (15U)
#define DMA_TCD_TCD26_BITER_ELINKNO_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD26_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD26_BITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD26_BITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD26_BITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD26_BITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD26_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD26_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD26_BITER_ELINKYES_BITER_MASK  (0x1FFU)
#define DMA_TCD_TCD26_BITER_ELINKYES_BITER_SHIFT (0U)
#define DMA_TCD_TCD26_BITER_ELINKYES_BITER_WIDTH (9U)
#define DMA_TCD_TCD26_BITER_ELINKYES_BITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD26_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD26_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD26_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD26_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD26_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD26_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD26_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD26_BITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD26_BITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD26_BITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD26_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD26_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH27_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH27_CSR_ERQ_MASK                (0x1U)
#define DMA_TCD_CH27_CSR_ERQ_SHIFT               (0U)
#define DMA_TCD_CH27_CSR_ERQ_WIDTH               (1U)
#define DMA_TCD_CH27_CSR_ERQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_CSR_ERQ_SHIFT)) & DMA_TCD_CH27_CSR_ERQ_MASK)

#define DMA_TCD_CH27_CSR_EARQ_MASK               (0x2U)
#define DMA_TCD_CH27_CSR_EARQ_SHIFT              (1U)
#define DMA_TCD_CH27_CSR_EARQ_WIDTH              (1U)
#define DMA_TCD_CH27_CSR_EARQ(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_CSR_EARQ_SHIFT)) & DMA_TCD_CH27_CSR_EARQ_MASK)

#define DMA_TCD_CH27_CSR_EEI_MASK                (0x4U)
#define DMA_TCD_CH27_CSR_EEI_SHIFT               (2U)
#define DMA_TCD_CH27_CSR_EEI_WIDTH               (1U)
#define DMA_TCD_CH27_CSR_EEI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_CSR_EEI_SHIFT)) & DMA_TCD_CH27_CSR_EEI_MASK)

#define DMA_TCD_CH27_CSR_EBW_MASK                (0x8U)
#define DMA_TCD_CH27_CSR_EBW_SHIFT               (3U)
#define DMA_TCD_CH27_CSR_EBW_WIDTH               (1U)
#define DMA_TCD_CH27_CSR_EBW(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_CSR_EBW_SHIFT)) & DMA_TCD_CH27_CSR_EBW_MASK)

#define DMA_TCD_CH27_CSR_DONE_MASK               (0x40000000U)
#define DMA_TCD_CH27_CSR_DONE_SHIFT              (30U)
#define DMA_TCD_CH27_CSR_DONE_WIDTH              (1U)
#define DMA_TCD_CH27_CSR_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_CSR_DONE_SHIFT)) & DMA_TCD_CH27_CSR_DONE_MASK)

#define DMA_TCD_CH27_CSR_ACTIVE_MASK             (0x80000000U)
#define DMA_TCD_CH27_CSR_ACTIVE_SHIFT            (31U)
#define DMA_TCD_CH27_CSR_ACTIVE_WIDTH            (1U)
#define DMA_TCD_CH27_CSR_ACTIVE(x)               (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH27_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH27_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH27_ES_DBE_MASK                 (0x1U)
#define DMA_TCD_CH27_ES_DBE_SHIFT                (0U)
#define DMA_TCD_CH27_ES_DBE_WIDTH                (1U)
#define DMA_TCD_CH27_ES_DBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_ES_DBE_SHIFT)) & DMA_TCD_CH27_ES_DBE_MASK)

#define DMA_TCD_CH27_ES_SBE_MASK                 (0x2U)
#define DMA_TCD_CH27_ES_SBE_SHIFT                (1U)
#define DMA_TCD_CH27_ES_SBE_WIDTH                (1U)
#define DMA_TCD_CH27_ES_SBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_ES_SBE_SHIFT)) & DMA_TCD_CH27_ES_SBE_MASK)

#define DMA_TCD_CH27_ES_SGE_MASK                 (0x4U)
#define DMA_TCD_CH27_ES_SGE_SHIFT                (2U)
#define DMA_TCD_CH27_ES_SGE_WIDTH                (1U)
#define DMA_TCD_CH27_ES_SGE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_ES_SGE_SHIFT)) & DMA_TCD_CH27_ES_SGE_MASK)

#define DMA_TCD_CH27_ES_NCE_MASK                 (0x8U)
#define DMA_TCD_CH27_ES_NCE_SHIFT                (3U)
#define DMA_TCD_CH27_ES_NCE_WIDTH                (1U)
#define DMA_TCD_CH27_ES_NCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_ES_NCE_SHIFT)) & DMA_TCD_CH27_ES_NCE_MASK)

#define DMA_TCD_CH27_ES_DOE_MASK                 (0x10U)
#define DMA_TCD_CH27_ES_DOE_SHIFT                (4U)
#define DMA_TCD_CH27_ES_DOE_WIDTH                (1U)
#define DMA_TCD_CH27_ES_DOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_ES_DOE_SHIFT)) & DMA_TCD_CH27_ES_DOE_MASK)

#define DMA_TCD_CH27_ES_DAE_MASK                 (0x20U)
#define DMA_TCD_CH27_ES_DAE_SHIFT                (5U)
#define DMA_TCD_CH27_ES_DAE_WIDTH                (1U)
#define DMA_TCD_CH27_ES_DAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_ES_DAE_SHIFT)) & DMA_TCD_CH27_ES_DAE_MASK)

#define DMA_TCD_CH27_ES_SOE_MASK                 (0x40U)
#define DMA_TCD_CH27_ES_SOE_SHIFT                (6U)
#define DMA_TCD_CH27_ES_SOE_WIDTH                (1U)
#define DMA_TCD_CH27_ES_SOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_ES_SOE_SHIFT)) & DMA_TCD_CH27_ES_SOE_MASK)

#define DMA_TCD_CH27_ES_SAE_MASK                 (0x80U)
#define DMA_TCD_CH27_ES_SAE_SHIFT                (7U)
#define DMA_TCD_CH27_ES_SAE_WIDTH                (1U)
#define DMA_TCD_CH27_ES_SAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_ES_SAE_SHIFT)) & DMA_TCD_CH27_ES_SAE_MASK)

#define DMA_TCD_CH27_ES_ERR_MASK                 (0x80000000U)
#define DMA_TCD_CH27_ES_ERR_SHIFT                (31U)
#define DMA_TCD_CH27_ES_ERR_WIDTH                (1U)
#define DMA_TCD_CH27_ES_ERR(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_ES_ERR_SHIFT)) & DMA_TCD_CH27_ES_ERR_MASK)
/*! @} */

/*! @name CH27_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH27_INT_INT_MASK                (0x1U)
#define DMA_TCD_CH27_INT_INT_SHIFT               (0U)
#define DMA_TCD_CH27_INT_INT_WIDTH               (1U)
#define DMA_TCD_CH27_INT_INT(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_INT_INT_SHIFT)) & DMA_TCD_CH27_INT_INT_MASK)
/*! @} */

/*! @name CH27_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH27_SBR_MID_MASK                (0xFU)
#define DMA_TCD_CH27_SBR_MID_SHIFT               (0U)
#define DMA_TCD_CH27_SBR_MID_WIDTH               (4U)
#define DMA_TCD_CH27_SBR_MID(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_SBR_MID_SHIFT)) & DMA_TCD_CH27_SBR_MID_MASK)

#define DMA_TCD_CH27_SBR_PAL_MASK                (0x8000U)
#define DMA_TCD_CH27_SBR_PAL_SHIFT               (15U)
#define DMA_TCD_CH27_SBR_PAL_WIDTH               (1U)
#define DMA_TCD_CH27_SBR_PAL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_SBR_PAL_SHIFT)) & DMA_TCD_CH27_SBR_PAL_MASK)

#define DMA_TCD_CH27_SBR_EMI_MASK                (0x10000U)
#define DMA_TCD_CH27_SBR_EMI_SHIFT               (16U)
#define DMA_TCD_CH27_SBR_EMI_WIDTH               (1U)
#define DMA_TCD_CH27_SBR_EMI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_SBR_EMI_SHIFT)) & DMA_TCD_CH27_SBR_EMI_MASK)

#define DMA_TCD_CH27_SBR_ATTR_MASK               (0xE0000U)
#define DMA_TCD_CH27_SBR_ATTR_SHIFT              (17U)
#define DMA_TCD_CH27_SBR_ATTR_WIDTH              (3U)
#define DMA_TCD_CH27_SBR_ATTR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_SBR_ATTR_SHIFT)) & DMA_TCD_CH27_SBR_ATTR_MASK)
/*! @} */

/*! @name CH27_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH27_PRI_APL_MASK                (0x7U)
#define DMA_TCD_CH27_PRI_APL_SHIFT               (0U)
#define DMA_TCD_CH27_PRI_APL_WIDTH               (3U)
#define DMA_TCD_CH27_PRI_APL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_PRI_APL_SHIFT)) & DMA_TCD_CH27_PRI_APL_MASK)

#define DMA_TCD_CH27_PRI_DPA_MASK                (0x40000000U)
#define DMA_TCD_CH27_PRI_DPA_SHIFT               (30U)
#define DMA_TCD_CH27_PRI_DPA_WIDTH               (1U)
#define DMA_TCD_CH27_PRI_DPA(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_PRI_DPA_SHIFT)) & DMA_TCD_CH27_PRI_DPA_MASK)

#define DMA_TCD_CH27_PRI_ECP_MASK                (0x80000000U)
#define DMA_TCD_CH27_PRI_ECP_SHIFT               (31U)
#define DMA_TCD_CH27_PRI_ECP_WIDTH               (1U)
#define DMA_TCD_CH27_PRI_ECP(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH27_PRI_ECP_SHIFT)) & DMA_TCD_CH27_PRI_ECP_MASK)
/*! @} */

/*! @name TCD27_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD27_SADDR_SADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD27_SADDR_SADDR_SHIFT          (0U)
#define DMA_TCD_TCD27_SADDR_SADDR_WIDTH          (32U)
#define DMA_TCD_TCD27_SADDR_SADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD27_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD27_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD27_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD27_SOFF_SOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD27_SOFF_SOFF_SHIFT            (0U)
#define DMA_TCD_TCD27_SOFF_SOFF_WIDTH            (16U)
#define DMA_TCD_TCD27_SOFF_SOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD27_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD27_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD27_ATTR_DSIZE_MASK            (0x7U)
#define DMA_TCD_TCD27_ATTR_DSIZE_SHIFT           (0U)
#define DMA_TCD_TCD27_ATTR_DSIZE_WIDTH           (3U)
#define DMA_TCD_TCD27_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD27_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD27_ATTR_DMOD_MASK             (0xF8U)
#define DMA_TCD_TCD27_ATTR_DMOD_SHIFT            (3U)
#define DMA_TCD_TCD27_ATTR_DMOD_WIDTH            (5U)
#define DMA_TCD_TCD27_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD27_ATTR_DMOD_MASK)

#define DMA_TCD_TCD27_ATTR_SSIZE_MASK            (0x700U)
#define DMA_TCD_TCD27_ATTR_SSIZE_SHIFT           (8U)
#define DMA_TCD_TCD27_ATTR_SSIZE_WIDTH           (3U)
#define DMA_TCD_TCD27_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD27_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD27_ATTR_SMOD_MASK             (0xF800U)
#define DMA_TCD_TCD27_ATTR_SMOD_SHIFT            (11U)
#define DMA_TCD_TCD27_ATTR_SMOD_WIDTH            (5U)
#define DMA_TCD_TCD27_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD27_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD27_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD27_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_TCD_TCD27_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD27_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD27_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD27_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD27_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD27_NBYTES_MLOFFNO_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD27_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD27_NBYTES_MLOFFNO_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD27_NBYTES_MLOFFNO_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD27_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD27_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD27_NBYTES_MLOFFNO_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD27_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD27_NBYTES_MLOFFNO_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD27_NBYTES_MLOFFNO_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD27_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD27_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD27_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD27_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD27_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD27_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD27_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD27_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD27_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD27_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_TCD_TCD27_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD27_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD27_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD27_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD27_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD27_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_TCD_TCD27_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD27_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD27_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD27_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD27_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD27_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_TCD_TCD27_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD27_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD27_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD27_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD27_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD27_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD27_SLAST_SDA_SLAST_SDA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD27_SLAST_SDA_SLAST_SDA_SHIFT  (0U)
#define DMA_TCD_TCD27_SLAST_SDA_SLAST_SDA_WIDTH  (32U)
#define DMA_TCD_TCD27_SLAST_SDA_SLAST_SDA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD27_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD27_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD27_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD27_DADDR_DADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD27_DADDR_DADDR_SHIFT          (0U)
#define DMA_TCD_TCD27_DADDR_DADDR_WIDTH          (32U)
#define DMA_TCD_TCD27_DADDR_DADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD27_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD27_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD27_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD27_DOFF_DOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD27_DOFF_DOFF_SHIFT            (0U)
#define DMA_TCD_TCD27_DOFF_DOFF_WIDTH            (16U)
#define DMA_TCD_TCD27_DOFF_DOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD27_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD27_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD27_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD27_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_TCD_TCD27_CITER_ELINKNO_CITER_WIDTH  (15U)
#define DMA_TCD_TCD27_CITER_ELINKNO_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD27_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD27_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD27_CITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD27_CITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD27_CITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD27_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD27_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD27_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_TCD_TCD27_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_TCD_TCD27_CITER_ELINKYES_CITER_WIDTH (9U)
#define DMA_TCD_TCD27_CITER_ELINKYES_CITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD27_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD27_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD27_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD27_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD27_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD27_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD27_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD27_CITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD27_CITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD27_CITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD27_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD27_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD27_DLAST_SGA_DLAST_SGA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD27_DLAST_SGA_DLAST_SGA_SHIFT  (0U)
#define DMA_TCD_TCD27_DLAST_SGA_DLAST_SGA_WIDTH  (32U)
#define DMA_TCD_TCD27_DLAST_SGA_DLAST_SGA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD27_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD27_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD27_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD27_CSR_START_MASK             (0x1U)
#define DMA_TCD_TCD27_CSR_START_SHIFT            (0U)
#define DMA_TCD_TCD27_CSR_START_WIDTH            (1U)
#define DMA_TCD_TCD27_CSR_START(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_CSR_START_SHIFT)) & DMA_TCD_TCD27_CSR_START_MASK)

#define DMA_TCD_TCD27_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_TCD_TCD27_CSR_INTMAJOR_SHIFT         (1U)
#define DMA_TCD_TCD27_CSR_INTMAJOR_WIDTH         (1U)
#define DMA_TCD_TCD27_CSR_INTMAJOR(x)            (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD27_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD27_CSR_INTHALF_MASK           (0x4U)
#define DMA_TCD_TCD27_CSR_INTHALF_SHIFT          (2U)
#define DMA_TCD_TCD27_CSR_INTHALF_WIDTH          (1U)
#define DMA_TCD_TCD27_CSR_INTHALF(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD27_CSR_INTHALF_MASK)

#define DMA_TCD_TCD27_CSR_DREQ_MASK              (0x8U)
#define DMA_TCD_TCD27_CSR_DREQ_SHIFT             (3U)
#define DMA_TCD_TCD27_CSR_DREQ_WIDTH             (1U)
#define DMA_TCD_TCD27_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_CSR_DREQ_SHIFT)) & DMA_TCD_TCD27_CSR_DREQ_MASK)

#define DMA_TCD_TCD27_CSR_ESG_MASK               (0x10U)
#define DMA_TCD_TCD27_CSR_ESG_SHIFT              (4U)
#define DMA_TCD_TCD27_CSR_ESG_WIDTH              (1U)
#define DMA_TCD_TCD27_CSR_ESG(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_CSR_ESG_SHIFT)) & DMA_TCD_TCD27_CSR_ESG_MASK)

#define DMA_TCD_TCD27_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_TCD_TCD27_CSR_MAJORELINK_SHIFT       (5U)
#define DMA_TCD_TCD27_CSR_MAJORELINK_WIDTH       (1U)
#define DMA_TCD_TCD27_CSR_MAJORELINK(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD27_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD27_CSR_EEOP_MASK              (0x40U)
#define DMA_TCD_TCD27_CSR_EEOP_SHIFT             (6U)
#define DMA_TCD_TCD27_CSR_EEOP_WIDTH             (1U)
#define DMA_TCD_TCD27_CSR_EEOP(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_CSR_EEOP_SHIFT)) & DMA_TCD_TCD27_CSR_EEOP_MASK)

#define DMA_TCD_TCD27_CSR_ESDA_MASK              (0x80U)
#define DMA_TCD_TCD27_CSR_ESDA_SHIFT             (7U)
#define DMA_TCD_TCD27_CSR_ESDA_WIDTH             (1U)
#define DMA_TCD_TCD27_CSR_ESDA(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_CSR_ESDA_SHIFT)) & DMA_TCD_TCD27_CSR_ESDA_MASK)

#define DMA_TCD_TCD27_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_TCD_TCD27_CSR_MAJORLINKCH_SHIFT      (8U)
#define DMA_TCD_TCD27_CSR_MAJORLINKCH_WIDTH      (5U)
#define DMA_TCD_TCD27_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD27_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD27_CSR_BWC_MASK               (0xC000U)
#define DMA_TCD_TCD27_CSR_BWC_SHIFT              (14U)
#define DMA_TCD_TCD27_CSR_BWC_WIDTH              (2U)
#define DMA_TCD_TCD27_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_CSR_BWC_SHIFT)) & DMA_TCD_TCD27_CSR_BWC_MASK)
/*! @} */

/*! @name TCD27_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD27_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD27_BITER_ELINKNO_BITER_SHIFT  (0U)
#define DMA_TCD_TCD27_BITER_ELINKNO_BITER_WIDTH  (15U)
#define DMA_TCD_TCD27_BITER_ELINKNO_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD27_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD27_BITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD27_BITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD27_BITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD27_BITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD27_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD27_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD27_BITER_ELINKYES_BITER_MASK  (0x1FFU)
#define DMA_TCD_TCD27_BITER_ELINKYES_BITER_SHIFT (0U)
#define DMA_TCD_TCD27_BITER_ELINKYES_BITER_WIDTH (9U)
#define DMA_TCD_TCD27_BITER_ELINKYES_BITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD27_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD27_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD27_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD27_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD27_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD27_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD27_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD27_BITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD27_BITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD27_BITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD27_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD27_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH28_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH28_CSR_ERQ_MASK                (0x1U)
#define DMA_TCD_CH28_CSR_ERQ_SHIFT               (0U)
#define DMA_TCD_CH28_CSR_ERQ_WIDTH               (1U)
#define DMA_TCD_CH28_CSR_ERQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_CSR_ERQ_SHIFT)) & DMA_TCD_CH28_CSR_ERQ_MASK)

#define DMA_TCD_CH28_CSR_EARQ_MASK               (0x2U)
#define DMA_TCD_CH28_CSR_EARQ_SHIFT              (1U)
#define DMA_TCD_CH28_CSR_EARQ_WIDTH              (1U)
#define DMA_TCD_CH28_CSR_EARQ(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_CSR_EARQ_SHIFT)) & DMA_TCD_CH28_CSR_EARQ_MASK)

#define DMA_TCD_CH28_CSR_EEI_MASK                (0x4U)
#define DMA_TCD_CH28_CSR_EEI_SHIFT               (2U)
#define DMA_TCD_CH28_CSR_EEI_WIDTH               (1U)
#define DMA_TCD_CH28_CSR_EEI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_CSR_EEI_SHIFT)) & DMA_TCD_CH28_CSR_EEI_MASK)

#define DMA_TCD_CH28_CSR_EBW_MASK                (0x8U)
#define DMA_TCD_CH28_CSR_EBW_SHIFT               (3U)
#define DMA_TCD_CH28_CSR_EBW_WIDTH               (1U)
#define DMA_TCD_CH28_CSR_EBW(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_CSR_EBW_SHIFT)) & DMA_TCD_CH28_CSR_EBW_MASK)

#define DMA_TCD_CH28_CSR_DONE_MASK               (0x40000000U)
#define DMA_TCD_CH28_CSR_DONE_SHIFT              (30U)
#define DMA_TCD_CH28_CSR_DONE_WIDTH              (1U)
#define DMA_TCD_CH28_CSR_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_CSR_DONE_SHIFT)) & DMA_TCD_CH28_CSR_DONE_MASK)

#define DMA_TCD_CH28_CSR_ACTIVE_MASK             (0x80000000U)
#define DMA_TCD_CH28_CSR_ACTIVE_SHIFT            (31U)
#define DMA_TCD_CH28_CSR_ACTIVE_WIDTH            (1U)
#define DMA_TCD_CH28_CSR_ACTIVE(x)               (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH28_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH28_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH28_ES_DBE_MASK                 (0x1U)
#define DMA_TCD_CH28_ES_DBE_SHIFT                (0U)
#define DMA_TCD_CH28_ES_DBE_WIDTH                (1U)
#define DMA_TCD_CH28_ES_DBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_ES_DBE_SHIFT)) & DMA_TCD_CH28_ES_DBE_MASK)

#define DMA_TCD_CH28_ES_SBE_MASK                 (0x2U)
#define DMA_TCD_CH28_ES_SBE_SHIFT                (1U)
#define DMA_TCD_CH28_ES_SBE_WIDTH                (1U)
#define DMA_TCD_CH28_ES_SBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_ES_SBE_SHIFT)) & DMA_TCD_CH28_ES_SBE_MASK)

#define DMA_TCD_CH28_ES_SGE_MASK                 (0x4U)
#define DMA_TCD_CH28_ES_SGE_SHIFT                (2U)
#define DMA_TCD_CH28_ES_SGE_WIDTH                (1U)
#define DMA_TCD_CH28_ES_SGE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_ES_SGE_SHIFT)) & DMA_TCD_CH28_ES_SGE_MASK)

#define DMA_TCD_CH28_ES_NCE_MASK                 (0x8U)
#define DMA_TCD_CH28_ES_NCE_SHIFT                (3U)
#define DMA_TCD_CH28_ES_NCE_WIDTH                (1U)
#define DMA_TCD_CH28_ES_NCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_ES_NCE_SHIFT)) & DMA_TCD_CH28_ES_NCE_MASK)

#define DMA_TCD_CH28_ES_DOE_MASK                 (0x10U)
#define DMA_TCD_CH28_ES_DOE_SHIFT                (4U)
#define DMA_TCD_CH28_ES_DOE_WIDTH                (1U)
#define DMA_TCD_CH28_ES_DOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_ES_DOE_SHIFT)) & DMA_TCD_CH28_ES_DOE_MASK)

#define DMA_TCD_CH28_ES_DAE_MASK                 (0x20U)
#define DMA_TCD_CH28_ES_DAE_SHIFT                (5U)
#define DMA_TCD_CH28_ES_DAE_WIDTH                (1U)
#define DMA_TCD_CH28_ES_DAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_ES_DAE_SHIFT)) & DMA_TCD_CH28_ES_DAE_MASK)

#define DMA_TCD_CH28_ES_SOE_MASK                 (0x40U)
#define DMA_TCD_CH28_ES_SOE_SHIFT                (6U)
#define DMA_TCD_CH28_ES_SOE_WIDTH                (1U)
#define DMA_TCD_CH28_ES_SOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_ES_SOE_SHIFT)) & DMA_TCD_CH28_ES_SOE_MASK)

#define DMA_TCD_CH28_ES_SAE_MASK                 (0x80U)
#define DMA_TCD_CH28_ES_SAE_SHIFT                (7U)
#define DMA_TCD_CH28_ES_SAE_WIDTH                (1U)
#define DMA_TCD_CH28_ES_SAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_ES_SAE_SHIFT)) & DMA_TCD_CH28_ES_SAE_MASK)

#define DMA_TCD_CH28_ES_ERR_MASK                 (0x80000000U)
#define DMA_TCD_CH28_ES_ERR_SHIFT                (31U)
#define DMA_TCD_CH28_ES_ERR_WIDTH                (1U)
#define DMA_TCD_CH28_ES_ERR(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_ES_ERR_SHIFT)) & DMA_TCD_CH28_ES_ERR_MASK)
/*! @} */

/*! @name CH28_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH28_INT_INT_MASK                (0x1U)
#define DMA_TCD_CH28_INT_INT_SHIFT               (0U)
#define DMA_TCD_CH28_INT_INT_WIDTH               (1U)
#define DMA_TCD_CH28_INT_INT(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_INT_INT_SHIFT)) & DMA_TCD_CH28_INT_INT_MASK)
/*! @} */

/*! @name CH28_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH28_SBR_MID_MASK                (0xFU)
#define DMA_TCD_CH28_SBR_MID_SHIFT               (0U)
#define DMA_TCD_CH28_SBR_MID_WIDTH               (4U)
#define DMA_TCD_CH28_SBR_MID(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_SBR_MID_SHIFT)) & DMA_TCD_CH28_SBR_MID_MASK)

#define DMA_TCD_CH28_SBR_PAL_MASK                (0x8000U)
#define DMA_TCD_CH28_SBR_PAL_SHIFT               (15U)
#define DMA_TCD_CH28_SBR_PAL_WIDTH               (1U)
#define DMA_TCD_CH28_SBR_PAL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_SBR_PAL_SHIFT)) & DMA_TCD_CH28_SBR_PAL_MASK)

#define DMA_TCD_CH28_SBR_EMI_MASK                (0x10000U)
#define DMA_TCD_CH28_SBR_EMI_SHIFT               (16U)
#define DMA_TCD_CH28_SBR_EMI_WIDTH               (1U)
#define DMA_TCD_CH28_SBR_EMI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_SBR_EMI_SHIFT)) & DMA_TCD_CH28_SBR_EMI_MASK)

#define DMA_TCD_CH28_SBR_ATTR_MASK               (0xE0000U)
#define DMA_TCD_CH28_SBR_ATTR_SHIFT              (17U)
#define DMA_TCD_CH28_SBR_ATTR_WIDTH              (3U)
#define DMA_TCD_CH28_SBR_ATTR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_SBR_ATTR_SHIFT)) & DMA_TCD_CH28_SBR_ATTR_MASK)
/*! @} */

/*! @name CH28_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH28_PRI_APL_MASK                (0x7U)
#define DMA_TCD_CH28_PRI_APL_SHIFT               (0U)
#define DMA_TCD_CH28_PRI_APL_WIDTH               (3U)
#define DMA_TCD_CH28_PRI_APL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_PRI_APL_SHIFT)) & DMA_TCD_CH28_PRI_APL_MASK)

#define DMA_TCD_CH28_PRI_DPA_MASK                (0x40000000U)
#define DMA_TCD_CH28_PRI_DPA_SHIFT               (30U)
#define DMA_TCD_CH28_PRI_DPA_WIDTH               (1U)
#define DMA_TCD_CH28_PRI_DPA(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_PRI_DPA_SHIFT)) & DMA_TCD_CH28_PRI_DPA_MASK)

#define DMA_TCD_CH28_PRI_ECP_MASK                (0x80000000U)
#define DMA_TCD_CH28_PRI_ECP_SHIFT               (31U)
#define DMA_TCD_CH28_PRI_ECP_WIDTH               (1U)
#define DMA_TCD_CH28_PRI_ECP(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH28_PRI_ECP_SHIFT)) & DMA_TCD_CH28_PRI_ECP_MASK)
/*! @} */

/*! @name TCD28_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD28_SADDR_SADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD28_SADDR_SADDR_SHIFT          (0U)
#define DMA_TCD_TCD28_SADDR_SADDR_WIDTH          (32U)
#define DMA_TCD_TCD28_SADDR_SADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD28_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD28_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD28_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD28_SOFF_SOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD28_SOFF_SOFF_SHIFT            (0U)
#define DMA_TCD_TCD28_SOFF_SOFF_WIDTH            (16U)
#define DMA_TCD_TCD28_SOFF_SOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD28_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD28_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD28_ATTR_DSIZE_MASK            (0x7U)
#define DMA_TCD_TCD28_ATTR_DSIZE_SHIFT           (0U)
#define DMA_TCD_TCD28_ATTR_DSIZE_WIDTH           (3U)
#define DMA_TCD_TCD28_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD28_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD28_ATTR_DMOD_MASK             (0xF8U)
#define DMA_TCD_TCD28_ATTR_DMOD_SHIFT            (3U)
#define DMA_TCD_TCD28_ATTR_DMOD_WIDTH            (5U)
#define DMA_TCD_TCD28_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD28_ATTR_DMOD_MASK)

#define DMA_TCD_TCD28_ATTR_SSIZE_MASK            (0x700U)
#define DMA_TCD_TCD28_ATTR_SSIZE_SHIFT           (8U)
#define DMA_TCD_TCD28_ATTR_SSIZE_WIDTH           (3U)
#define DMA_TCD_TCD28_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD28_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD28_ATTR_SMOD_MASK             (0xF800U)
#define DMA_TCD_TCD28_ATTR_SMOD_SHIFT            (11U)
#define DMA_TCD_TCD28_ATTR_SMOD_WIDTH            (5U)
#define DMA_TCD_TCD28_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD28_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD28_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD28_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_TCD_TCD28_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD28_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD28_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD28_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD28_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD28_NBYTES_MLOFFNO_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD28_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD28_NBYTES_MLOFFNO_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD28_NBYTES_MLOFFNO_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD28_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD28_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD28_NBYTES_MLOFFNO_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD28_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD28_NBYTES_MLOFFNO_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD28_NBYTES_MLOFFNO_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD28_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD28_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD28_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD28_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD28_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD28_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD28_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD28_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD28_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD28_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_TCD_TCD28_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD28_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD28_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD28_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD28_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD28_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_TCD_TCD28_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD28_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD28_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD28_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD28_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD28_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_TCD_TCD28_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD28_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD28_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD28_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD28_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD28_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD28_SLAST_SDA_SLAST_SDA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD28_SLAST_SDA_SLAST_SDA_SHIFT  (0U)
#define DMA_TCD_TCD28_SLAST_SDA_SLAST_SDA_WIDTH  (32U)
#define DMA_TCD_TCD28_SLAST_SDA_SLAST_SDA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD28_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD28_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD28_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD28_DADDR_DADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD28_DADDR_DADDR_SHIFT          (0U)
#define DMA_TCD_TCD28_DADDR_DADDR_WIDTH          (32U)
#define DMA_TCD_TCD28_DADDR_DADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD28_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD28_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD28_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD28_DOFF_DOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD28_DOFF_DOFF_SHIFT            (0U)
#define DMA_TCD_TCD28_DOFF_DOFF_WIDTH            (16U)
#define DMA_TCD_TCD28_DOFF_DOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD28_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD28_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD28_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD28_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_TCD_TCD28_CITER_ELINKNO_CITER_WIDTH  (15U)
#define DMA_TCD_TCD28_CITER_ELINKNO_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD28_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD28_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD28_CITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD28_CITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD28_CITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD28_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD28_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD28_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_TCD_TCD28_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_TCD_TCD28_CITER_ELINKYES_CITER_WIDTH (9U)
#define DMA_TCD_TCD28_CITER_ELINKYES_CITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD28_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD28_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD28_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD28_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD28_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD28_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD28_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD28_CITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD28_CITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD28_CITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD28_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD28_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD28_DLAST_SGA_DLAST_SGA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD28_DLAST_SGA_DLAST_SGA_SHIFT  (0U)
#define DMA_TCD_TCD28_DLAST_SGA_DLAST_SGA_WIDTH  (32U)
#define DMA_TCD_TCD28_DLAST_SGA_DLAST_SGA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD28_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD28_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD28_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD28_CSR_START_MASK             (0x1U)
#define DMA_TCD_TCD28_CSR_START_SHIFT            (0U)
#define DMA_TCD_TCD28_CSR_START_WIDTH            (1U)
#define DMA_TCD_TCD28_CSR_START(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_CSR_START_SHIFT)) & DMA_TCD_TCD28_CSR_START_MASK)

#define DMA_TCD_TCD28_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_TCD_TCD28_CSR_INTMAJOR_SHIFT         (1U)
#define DMA_TCD_TCD28_CSR_INTMAJOR_WIDTH         (1U)
#define DMA_TCD_TCD28_CSR_INTMAJOR(x)            (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD28_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD28_CSR_INTHALF_MASK           (0x4U)
#define DMA_TCD_TCD28_CSR_INTHALF_SHIFT          (2U)
#define DMA_TCD_TCD28_CSR_INTHALF_WIDTH          (1U)
#define DMA_TCD_TCD28_CSR_INTHALF(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD28_CSR_INTHALF_MASK)

#define DMA_TCD_TCD28_CSR_DREQ_MASK              (0x8U)
#define DMA_TCD_TCD28_CSR_DREQ_SHIFT             (3U)
#define DMA_TCD_TCD28_CSR_DREQ_WIDTH             (1U)
#define DMA_TCD_TCD28_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_CSR_DREQ_SHIFT)) & DMA_TCD_TCD28_CSR_DREQ_MASK)

#define DMA_TCD_TCD28_CSR_ESG_MASK               (0x10U)
#define DMA_TCD_TCD28_CSR_ESG_SHIFT              (4U)
#define DMA_TCD_TCD28_CSR_ESG_WIDTH              (1U)
#define DMA_TCD_TCD28_CSR_ESG(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_CSR_ESG_SHIFT)) & DMA_TCD_TCD28_CSR_ESG_MASK)

#define DMA_TCD_TCD28_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_TCD_TCD28_CSR_MAJORELINK_SHIFT       (5U)
#define DMA_TCD_TCD28_CSR_MAJORELINK_WIDTH       (1U)
#define DMA_TCD_TCD28_CSR_MAJORELINK(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD28_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD28_CSR_EEOP_MASK              (0x40U)
#define DMA_TCD_TCD28_CSR_EEOP_SHIFT             (6U)
#define DMA_TCD_TCD28_CSR_EEOP_WIDTH             (1U)
#define DMA_TCD_TCD28_CSR_EEOP(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_CSR_EEOP_SHIFT)) & DMA_TCD_TCD28_CSR_EEOP_MASK)

#define DMA_TCD_TCD28_CSR_ESDA_MASK              (0x80U)
#define DMA_TCD_TCD28_CSR_ESDA_SHIFT             (7U)
#define DMA_TCD_TCD28_CSR_ESDA_WIDTH             (1U)
#define DMA_TCD_TCD28_CSR_ESDA(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_CSR_ESDA_SHIFT)) & DMA_TCD_TCD28_CSR_ESDA_MASK)

#define DMA_TCD_TCD28_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_TCD_TCD28_CSR_MAJORLINKCH_SHIFT      (8U)
#define DMA_TCD_TCD28_CSR_MAJORLINKCH_WIDTH      (5U)
#define DMA_TCD_TCD28_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD28_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD28_CSR_BWC_MASK               (0xC000U)
#define DMA_TCD_TCD28_CSR_BWC_SHIFT              (14U)
#define DMA_TCD_TCD28_CSR_BWC_WIDTH              (2U)
#define DMA_TCD_TCD28_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_CSR_BWC_SHIFT)) & DMA_TCD_TCD28_CSR_BWC_MASK)
/*! @} */

/*! @name TCD28_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD28_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD28_BITER_ELINKNO_BITER_SHIFT  (0U)
#define DMA_TCD_TCD28_BITER_ELINKNO_BITER_WIDTH  (15U)
#define DMA_TCD_TCD28_BITER_ELINKNO_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD28_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD28_BITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD28_BITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD28_BITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD28_BITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD28_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD28_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD28_BITER_ELINKYES_BITER_MASK  (0x1FFU)
#define DMA_TCD_TCD28_BITER_ELINKYES_BITER_SHIFT (0U)
#define DMA_TCD_TCD28_BITER_ELINKYES_BITER_WIDTH (9U)
#define DMA_TCD_TCD28_BITER_ELINKYES_BITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD28_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD28_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD28_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD28_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD28_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD28_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD28_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD28_BITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD28_BITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD28_BITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD28_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD28_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH29_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH29_CSR_ERQ_MASK                (0x1U)
#define DMA_TCD_CH29_CSR_ERQ_SHIFT               (0U)
#define DMA_TCD_CH29_CSR_ERQ_WIDTH               (1U)
#define DMA_TCD_CH29_CSR_ERQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_CSR_ERQ_SHIFT)) & DMA_TCD_CH29_CSR_ERQ_MASK)

#define DMA_TCD_CH29_CSR_EARQ_MASK               (0x2U)
#define DMA_TCD_CH29_CSR_EARQ_SHIFT              (1U)
#define DMA_TCD_CH29_CSR_EARQ_WIDTH              (1U)
#define DMA_TCD_CH29_CSR_EARQ(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_CSR_EARQ_SHIFT)) & DMA_TCD_CH29_CSR_EARQ_MASK)

#define DMA_TCD_CH29_CSR_EEI_MASK                (0x4U)
#define DMA_TCD_CH29_CSR_EEI_SHIFT               (2U)
#define DMA_TCD_CH29_CSR_EEI_WIDTH               (1U)
#define DMA_TCD_CH29_CSR_EEI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_CSR_EEI_SHIFT)) & DMA_TCD_CH29_CSR_EEI_MASK)

#define DMA_TCD_CH29_CSR_EBW_MASK                (0x8U)
#define DMA_TCD_CH29_CSR_EBW_SHIFT               (3U)
#define DMA_TCD_CH29_CSR_EBW_WIDTH               (1U)
#define DMA_TCD_CH29_CSR_EBW(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_CSR_EBW_SHIFT)) & DMA_TCD_CH29_CSR_EBW_MASK)

#define DMA_TCD_CH29_CSR_DONE_MASK               (0x40000000U)
#define DMA_TCD_CH29_CSR_DONE_SHIFT              (30U)
#define DMA_TCD_CH29_CSR_DONE_WIDTH              (1U)
#define DMA_TCD_CH29_CSR_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_CSR_DONE_SHIFT)) & DMA_TCD_CH29_CSR_DONE_MASK)

#define DMA_TCD_CH29_CSR_ACTIVE_MASK             (0x80000000U)
#define DMA_TCD_CH29_CSR_ACTIVE_SHIFT            (31U)
#define DMA_TCD_CH29_CSR_ACTIVE_WIDTH            (1U)
#define DMA_TCD_CH29_CSR_ACTIVE(x)               (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH29_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH29_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH29_ES_DBE_MASK                 (0x1U)
#define DMA_TCD_CH29_ES_DBE_SHIFT                (0U)
#define DMA_TCD_CH29_ES_DBE_WIDTH                (1U)
#define DMA_TCD_CH29_ES_DBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_ES_DBE_SHIFT)) & DMA_TCD_CH29_ES_DBE_MASK)

#define DMA_TCD_CH29_ES_SBE_MASK                 (0x2U)
#define DMA_TCD_CH29_ES_SBE_SHIFT                (1U)
#define DMA_TCD_CH29_ES_SBE_WIDTH                (1U)
#define DMA_TCD_CH29_ES_SBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_ES_SBE_SHIFT)) & DMA_TCD_CH29_ES_SBE_MASK)

#define DMA_TCD_CH29_ES_SGE_MASK                 (0x4U)
#define DMA_TCD_CH29_ES_SGE_SHIFT                (2U)
#define DMA_TCD_CH29_ES_SGE_WIDTH                (1U)
#define DMA_TCD_CH29_ES_SGE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_ES_SGE_SHIFT)) & DMA_TCD_CH29_ES_SGE_MASK)

#define DMA_TCD_CH29_ES_NCE_MASK                 (0x8U)
#define DMA_TCD_CH29_ES_NCE_SHIFT                (3U)
#define DMA_TCD_CH29_ES_NCE_WIDTH                (1U)
#define DMA_TCD_CH29_ES_NCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_ES_NCE_SHIFT)) & DMA_TCD_CH29_ES_NCE_MASK)

#define DMA_TCD_CH29_ES_DOE_MASK                 (0x10U)
#define DMA_TCD_CH29_ES_DOE_SHIFT                (4U)
#define DMA_TCD_CH29_ES_DOE_WIDTH                (1U)
#define DMA_TCD_CH29_ES_DOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_ES_DOE_SHIFT)) & DMA_TCD_CH29_ES_DOE_MASK)

#define DMA_TCD_CH29_ES_DAE_MASK                 (0x20U)
#define DMA_TCD_CH29_ES_DAE_SHIFT                (5U)
#define DMA_TCD_CH29_ES_DAE_WIDTH                (1U)
#define DMA_TCD_CH29_ES_DAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_ES_DAE_SHIFT)) & DMA_TCD_CH29_ES_DAE_MASK)

#define DMA_TCD_CH29_ES_SOE_MASK                 (0x40U)
#define DMA_TCD_CH29_ES_SOE_SHIFT                (6U)
#define DMA_TCD_CH29_ES_SOE_WIDTH                (1U)
#define DMA_TCD_CH29_ES_SOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_ES_SOE_SHIFT)) & DMA_TCD_CH29_ES_SOE_MASK)

#define DMA_TCD_CH29_ES_SAE_MASK                 (0x80U)
#define DMA_TCD_CH29_ES_SAE_SHIFT                (7U)
#define DMA_TCD_CH29_ES_SAE_WIDTH                (1U)
#define DMA_TCD_CH29_ES_SAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_ES_SAE_SHIFT)) & DMA_TCD_CH29_ES_SAE_MASK)

#define DMA_TCD_CH29_ES_ERR_MASK                 (0x80000000U)
#define DMA_TCD_CH29_ES_ERR_SHIFT                (31U)
#define DMA_TCD_CH29_ES_ERR_WIDTH                (1U)
#define DMA_TCD_CH29_ES_ERR(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_ES_ERR_SHIFT)) & DMA_TCD_CH29_ES_ERR_MASK)
/*! @} */

/*! @name CH29_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH29_INT_INT_MASK                (0x1U)
#define DMA_TCD_CH29_INT_INT_SHIFT               (0U)
#define DMA_TCD_CH29_INT_INT_WIDTH               (1U)
#define DMA_TCD_CH29_INT_INT(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_INT_INT_SHIFT)) & DMA_TCD_CH29_INT_INT_MASK)
/*! @} */

/*! @name CH29_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH29_SBR_MID_MASK                (0xFU)
#define DMA_TCD_CH29_SBR_MID_SHIFT               (0U)
#define DMA_TCD_CH29_SBR_MID_WIDTH               (4U)
#define DMA_TCD_CH29_SBR_MID(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_SBR_MID_SHIFT)) & DMA_TCD_CH29_SBR_MID_MASK)

#define DMA_TCD_CH29_SBR_PAL_MASK                (0x8000U)
#define DMA_TCD_CH29_SBR_PAL_SHIFT               (15U)
#define DMA_TCD_CH29_SBR_PAL_WIDTH               (1U)
#define DMA_TCD_CH29_SBR_PAL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_SBR_PAL_SHIFT)) & DMA_TCD_CH29_SBR_PAL_MASK)

#define DMA_TCD_CH29_SBR_EMI_MASK                (0x10000U)
#define DMA_TCD_CH29_SBR_EMI_SHIFT               (16U)
#define DMA_TCD_CH29_SBR_EMI_WIDTH               (1U)
#define DMA_TCD_CH29_SBR_EMI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_SBR_EMI_SHIFT)) & DMA_TCD_CH29_SBR_EMI_MASK)

#define DMA_TCD_CH29_SBR_ATTR_MASK               (0xE0000U)
#define DMA_TCD_CH29_SBR_ATTR_SHIFT              (17U)
#define DMA_TCD_CH29_SBR_ATTR_WIDTH              (3U)
#define DMA_TCD_CH29_SBR_ATTR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_SBR_ATTR_SHIFT)) & DMA_TCD_CH29_SBR_ATTR_MASK)
/*! @} */

/*! @name CH29_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH29_PRI_APL_MASK                (0x7U)
#define DMA_TCD_CH29_PRI_APL_SHIFT               (0U)
#define DMA_TCD_CH29_PRI_APL_WIDTH               (3U)
#define DMA_TCD_CH29_PRI_APL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_PRI_APL_SHIFT)) & DMA_TCD_CH29_PRI_APL_MASK)

#define DMA_TCD_CH29_PRI_DPA_MASK                (0x40000000U)
#define DMA_TCD_CH29_PRI_DPA_SHIFT               (30U)
#define DMA_TCD_CH29_PRI_DPA_WIDTH               (1U)
#define DMA_TCD_CH29_PRI_DPA(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_PRI_DPA_SHIFT)) & DMA_TCD_CH29_PRI_DPA_MASK)

#define DMA_TCD_CH29_PRI_ECP_MASK                (0x80000000U)
#define DMA_TCD_CH29_PRI_ECP_SHIFT               (31U)
#define DMA_TCD_CH29_PRI_ECP_WIDTH               (1U)
#define DMA_TCD_CH29_PRI_ECP(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH29_PRI_ECP_SHIFT)) & DMA_TCD_CH29_PRI_ECP_MASK)
/*! @} */

/*! @name TCD29_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD29_SADDR_SADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD29_SADDR_SADDR_SHIFT          (0U)
#define DMA_TCD_TCD29_SADDR_SADDR_WIDTH          (32U)
#define DMA_TCD_TCD29_SADDR_SADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD29_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD29_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD29_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD29_SOFF_SOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD29_SOFF_SOFF_SHIFT            (0U)
#define DMA_TCD_TCD29_SOFF_SOFF_WIDTH            (16U)
#define DMA_TCD_TCD29_SOFF_SOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD29_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD29_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD29_ATTR_DSIZE_MASK            (0x7U)
#define DMA_TCD_TCD29_ATTR_DSIZE_SHIFT           (0U)
#define DMA_TCD_TCD29_ATTR_DSIZE_WIDTH           (3U)
#define DMA_TCD_TCD29_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD29_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD29_ATTR_DMOD_MASK             (0xF8U)
#define DMA_TCD_TCD29_ATTR_DMOD_SHIFT            (3U)
#define DMA_TCD_TCD29_ATTR_DMOD_WIDTH            (5U)
#define DMA_TCD_TCD29_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD29_ATTR_DMOD_MASK)

#define DMA_TCD_TCD29_ATTR_SSIZE_MASK            (0x700U)
#define DMA_TCD_TCD29_ATTR_SSIZE_SHIFT           (8U)
#define DMA_TCD_TCD29_ATTR_SSIZE_WIDTH           (3U)
#define DMA_TCD_TCD29_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD29_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD29_ATTR_SMOD_MASK             (0xF800U)
#define DMA_TCD_TCD29_ATTR_SMOD_SHIFT            (11U)
#define DMA_TCD_TCD29_ATTR_SMOD_WIDTH            (5U)
#define DMA_TCD_TCD29_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD29_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD29_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD29_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_TCD_TCD29_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD29_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD29_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD29_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD29_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD29_NBYTES_MLOFFNO_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD29_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD29_NBYTES_MLOFFNO_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD29_NBYTES_MLOFFNO_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD29_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD29_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD29_NBYTES_MLOFFNO_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD29_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD29_NBYTES_MLOFFNO_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD29_NBYTES_MLOFFNO_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD29_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD29_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD29_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD29_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD29_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD29_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD29_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD29_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD29_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD29_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_TCD_TCD29_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD29_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD29_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD29_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD29_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD29_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_TCD_TCD29_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD29_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD29_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD29_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD29_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD29_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_TCD_TCD29_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD29_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD29_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD29_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD29_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD29_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD29_SLAST_SDA_SLAST_SDA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD29_SLAST_SDA_SLAST_SDA_SHIFT  (0U)
#define DMA_TCD_TCD29_SLAST_SDA_SLAST_SDA_WIDTH  (32U)
#define DMA_TCD_TCD29_SLAST_SDA_SLAST_SDA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD29_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD29_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD29_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD29_DADDR_DADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD29_DADDR_DADDR_SHIFT          (0U)
#define DMA_TCD_TCD29_DADDR_DADDR_WIDTH          (32U)
#define DMA_TCD_TCD29_DADDR_DADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD29_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD29_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD29_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD29_DOFF_DOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD29_DOFF_DOFF_SHIFT            (0U)
#define DMA_TCD_TCD29_DOFF_DOFF_WIDTH            (16U)
#define DMA_TCD_TCD29_DOFF_DOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD29_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD29_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD29_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD29_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_TCD_TCD29_CITER_ELINKNO_CITER_WIDTH  (15U)
#define DMA_TCD_TCD29_CITER_ELINKNO_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD29_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD29_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD29_CITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD29_CITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD29_CITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD29_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD29_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD29_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_TCD_TCD29_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_TCD_TCD29_CITER_ELINKYES_CITER_WIDTH (9U)
#define DMA_TCD_TCD29_CITER_ELINKYES_CITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD29_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD29_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD29_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD29_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD29_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD29_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD29_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD29_CITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD29_CITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD29_CITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD29_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD29_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD29_DLAST_SGA_DLAST_SGA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD29_DLAST_SGA_DLAST_SGA_SHIFT  (0U)
#define DMA_TCD_TCD29_DLAST_SGA_DLAST_SGA_WIDTH  (32U)
#define DMA_TCD_TCD29_DLAST_SGA_DLAST_SGA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD29_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD29_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD29_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD29_CSR_START_MASK             (0x1U)
#define DMA_TCD_TCD29_CSR_START_SHIFT            (0U)
#define DMA_TCD_TCD29_CSR_START_WIDTH            (1U)
#define DMA_TCD_TCD29_CSR_START(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_CSR_START_SHIFT)) & DMA_TCD_TCD29_CSR_START_MASK)

#define DMA_TCD_TCD29_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_TCD_TCD29_CSR_INTMAJOR_SHIFT         (1U)
#define DMA_TCD_TCD29_CSR_INTMAJOR_WIDTH         (1U)
#define DMA_TCD_TCD29_CSR_INTMAJOR(x)            (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD29_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD29_CSR_INTHALF_MASK           (0x4U)
#define DMA_TCD_TCD29_CSR_INTHALF_SHIFT          (2U)
#define DMA_TCD_TCD29_CSR_INTHALF_WIDTH          (1U)
#define DMA_TCD_TCD29_CSR_INTHALF(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD29_CSR_INTHALF_MASK)

#define DMA_TCD_TCD29_CSR_DREQ_MASK              (0x8U)
#define DMA_TCD_TCD29_CSR_DREQ_SHIFT             (3U)
#define DMA_TCD_TCD29_CSR_DREQ_WIDTH             (1U)
#define DMA_TCD_TCD29_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_CSR_DREQ_SHIFT)) & DMA_TCD_TCD29_CSR_DREQ_MASK)

#define DMA_TCD_TCD29_CSR_ESG_MASK               (0x10U)
#define DMA_TCD_TCD29_CSR_ESG_SHIFT              (4U)
#define DMA_TCD_TCD29_CSR_ESG_WIDTH              (1U)
#define DMA_TCD_TCD29_CSR_ESG(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_CSR_ESG_SHIFT)) & DMA_TCD_TCD29_CSR_ESG_MASK)

#define DMA_TCD_TCD29_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_TCD_TCD29_CSR_MAJORELINK_SHIFT       (5U)
#define DMA_TCD_TCD29_CSR_MAJORELINK_WIDTH       (1U)
#define DMA_TCD_TCD29_CSR_MAJORELINK(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD29_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD29_CSR_EEOP_MASK              (0x40U)
#define DMA_TCD_TCD29_CSR_EEOP_SHIFT             (6U)
#define DMA_TCD_TCD29_CSR_EEOP_WIDTH             (1U)
#define DMA_TCD_TCD29_CSR_EEOP(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_CSR_EEOP_SHIFT)) & DMA_TCD_TCD29_CSR_EEOP_MASK)

#define DMA_TCD_TCD29_CSR_ESDA_MASK              (0x80U)
#define DMA_TCD_TCD29_CSR_ESDA_SHIFT             (7U)
#define DMA_TCD_TCD29_CSR_ESDA_WIDTH             (1U)
#define DMA_TCD_TCD29_CSR_ESDA(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_CSR_ESDA_SHIFT)) & DMA_TCD_TCD29_CSR_ESDA_MASK)

#define DMA_TCD_TCD29_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_TCD_TCD29_CSR_MAJORLINKCH_SHIFT      (8U)
#define DMA_TCD_TCD29_CSR_MAJORLINKCH_WIDTH      (5U)
#define DMA_TCD_TCD29_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD29_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD29_CSR_BWC_MASK               (0xC000U)
#define DMA_TCD_TCD29_CSR_BWC_SHIFT              (14U)
#define DMA_TCD_TCD29_CSR_BWC_WIDTH              (2U)
#define DMA_TCD_TCD29_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_CSR_BWC_SHIFT)) & DMA_TCD_TCD29_CSR_BWC_MASK)
/*! @} */

/*! @name TCD29_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD29_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD29_BITER_ELINKNO_BITER_SHIFT  (0U)
#define DMA_TCD_TCD29_BITER_ELINKNO_BITER_WIDTH  (15U)
#define DMA_TCD_TCD29_BITER_ELINKNO_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD29_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD29_BITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD29_BITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD29_BITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD29_BITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD29_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD29_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD29_BITER_ELINKYES_BITER_MASK  (0x1FFU)
#define DMA_TCD_TCD29_BITER_ELINKYES_BITER_SHIFT (0U)
#define DMA_TCD_TCD29_BITER_ELINKYES_BITER_WIDTH (9U)
#define DMA_TCD_TCD29_BITER_ELINKYES_BITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD29_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD29_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD29_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD29_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD29_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD29_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD29_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD29_BITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD29_BITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD29_BITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD29_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD29_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH30_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH30_CSR_ERQ_MASK                (0x1U)
#define DMA_TCD_CH30_CSR_ERQ_SHIFT               (0U)
#define DMA_TCD_CH30_CSR_ERQ_WIDTH               (1U)
#define DMA_TCD_CH30_CSR_ERQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_CSR_ERQ_SHIFT)) & DMA_TCD_CH30_CSR_ERQ_MASK)

#define DMA_TCD_CH30_CSR_EARQ_MASK               (0x2U)
#define DMA_TCD_CH30_CSR_EARQ_SHIFT              (1U)
#define DMA_TCD_CH30_CSR_EARQ_WIDTH              (1U)
#define DMA_TCD_CH30_CSR_EARQ(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_CSR_EARQ_SHIFT)) & DMA_TCD_CH30_CSR_EARQ_MASK)

#define DMA_TCD_CH30_CSR_EEI_MASK                (0x4U)
#define DMA_TCD_CH30_CSR_EEI_SHIFT               (2U)
#define DMA_TCD_CH30_CSR_EEI_WIDTH               (1U)
#define DMA_TCD_CH30_CSR_EEI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_CSR_EEI_SHIFT)) & DMA_TCD_CH30_CSR_EEI_MASK)

#define DMA_TCD_CH30_CSR_EBW_MASK                (0x8U)
#define DMA_TCD_CH30_CSR_EBW_SHIFT               (3U)
#define DMA_TCD_CH30_CSR_EBW_WIDTH               (1U)
#define DMA_TCD_CH30_CSR_EBW(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_CSR_EBW_SHIFT)) & DMA_TCD_CH30_CSR_EBW_MASK)

#define DMA_TCD_CH30_CSR_DONE_MASK               (0x40000000U)
#define DMA_TCD_CH30_CSR_DONE_SHIFT              (30U)
#define DMA_TCD_CH30_CSR_DONE_WIDTH              (1U)
#define DMA_TCD_CH30_CSR_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_CSR_DONE_SHIFT)) & DMA_TCD_CH30_CSR_DONE_MASK)

#define DMA_TCD_CH30_CSR_ACTIVE_MASK             (0x80000000U)
#define DMA_TCD_CH30_CSR_ACTIVE_SHIFT            (31U)
#define DMA_TCD_CH30_CSR_ACTIVE_WIDTH            (1U)
#define DMA_TCD_CH30_CSR_ACTIVE(x)               (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH30_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH30_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH30_ES_DBE_MASK                 (0x1U)
#define DMA_TCD_CH30_ES_DBE_SHIFT                (0U)
#define DMA_TCD_CH30_ES_DBE_WIDTH                (1U)
#define DMA_TCD_CH30_ES_DBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_ES_DBE_SHIFT)) & DMA_TCD_CH30_ES_DBE_MASK)

#define DMA_TCD_CH30_ES_SBE_MASK                 (0x2U)
#define DMA_TCD_CH30_ES_SBE_SHIFT                (1U)
#define DMA_TCD_CH30_ES_SBE_WIDTH                (1U)
#define DMA_TCD_CH30_ES_SBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_ES_SBE_SHIFT)) & DMA_TCD_CH30_ES_SBE_MASK)

#define DMA_TCD_CH30_ES_SGE_MASK                 (0x4U)
#define DMA_TCD_CH30_ES_SGE_SHIFT                (2U)
#define DMA_TCD_CH30_ES_SGE_WIDTH                (1U)
#define DMA_TCD_CH30_ES_SGE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_ES_SGE_SHIFT)) & DMA_TCD_CH30_ES_SGE_MASK)

#define DMA_TCD_CH30_ES_NCE_MASK                 (0x8U)
#define DMA_TCD_CH30_ES_NCE_SHIFT                (3U)
#define DMA_TCD_CH30_ES_NCE_WIDTH                (1U)
#define DMA_TCD_CH30_ES_NCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_ES_NCE_SHIFT)) & DMA_TCD_CH30_ES_NCE_MASK)

#define DMA_TCD_CH30_ES_DOE_MASK                 (0x10U)
#define DMA_TCD_CH30_ES_DOE_SHIFT                (4U)
#define DMA_TCD_CH30_ES_DOE_WIDTH                (1U)
#define DMA_TCD_CH30_ES_DOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_ES_DOE_SHIFT)) & DMA_TCD_CH30_ES_DOE_MASK)

#define DMA_TCD_CH30_ES_DAE_MASK                 (0x20U)
#define DMA_TCD_CH30_ES_DAE_SHIFT                (5U)
#define DMA_TCD_CH30_ES_DAE_WIDTH                (1U)
#define DMA_TCD_CH30_ES_DAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_ES_DAE_SHIFT)) & DMA_TCD_CH30_ES_DAE_MASK)

#define DMA_TCD_CH30_ES_SOE_MASK                 (0x40U)
#define DMA_TCD_CH30_ES_SOE_SHIFT                (6U)
#define DMA_TCD_CH30_ES_SOE_WIDTH                (1U)
#define DMA_TCD_CH30_ES_SOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_ES_SOE_SHIFT)) & DMA_TCD_CH30_ES_SOE_MASK)

#define DMA_TCD_CH30_ES_SAE_MASK                 (0x80U)
#define DMA_TCD_CH30_ES_SAE_SHIFT                (7U)
#define DMA_TCD_CH30_ES_SAE_WIDTH                (1U)
#define DMA_TCD_CH30_ES_SAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_ES_SAE_SHIFT)) & DMA_TCD_CH30_ES_SAE_MASK)

#define DMA_TCD_CH30_ES_ERR_MASK                 (0x80000000U)
#define DMA_TCD_CH30_ES_ERR_SHIFT                (31U)
#define DMA_TCD_CH30_ES_ERR_WIDTH                (1U)
#define DMA_TCD_CH30_ES_ERR(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_ES_ERR_SHIFT)) & DMA_TCD_CH30_ES_ERR_MASK)
/*! @} */

/*! @name CH30_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH30_INT_INT_MASK                (0x1U)
#define DMA_TCD_CH30_INT_INT_SHIFT               (0U)
#define DMA_TCD_CH30_INT_INT_WIDTH               (1U)
#define DMA_TCD_CH30_INT_INT(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_INT_INT_SHIFT)) & DMA_TCD_CH30_INT_INT_MASK)
/*! @} */

/*! @name CH30_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH30_SBR_MID_MASK                (0xFU)
#define DMA_TCD_CH30_SBR_MID_SHIFT               (0U)
#define DMA_TCD_CH30_SBR_MID_WIDTH               (4U)
#define DMA_TCD_CH30_SBR_MID(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_SBR_MID_SHIFT)) & DMA_TCD_CH30_SBR_MID_MASK)

#define DMA_TCD_CH30_SBR_PAL_MASK                (0x8000U)
#define DMA_TCD_CH30_SBR_PAL_SHIFT               (15U)
#define DMA_TCD_CH30_SBR_PAL_WIDTH               (1U)
#define DMA_TCD_CH30_SBR_PAL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_SBR_PAL_SHIFT)) & DMA_TCD_CH30_SBR_PAL_MASK)

#define DMA_TCD_CH30_SBR_EMI_MASK                (0x10000U)
#define DMA_TCD_CH30_SBR_EMI_SHIFT               (16U)
#define DMA_TCD_CH30_SBR_EMI_WIDTH               (1U)
#define DMA_TCD_CH30_SBR_EMI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_SBR_EMI_SHIFT)) & DMA_TCD_CH30_SBR_EMI_MASK)

#define DMA_TCD_CH30_SBR_ATTR_MASK               (0xE0000U)
#define DMA_TCD_CH30_SBR_ATTR_SHIFT              (17U)
#define DMA_TCD_CH30_SBR_ATTR_WIDTH              (3U)
#define DMA_TCD_CH30_SBR_ATTR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_SBR_ATTR_SHIFT)) & DMA_TCD_CH30_SBR_ATTR_MASK)
/*! @} */

/*! @name CH30_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH30_PRI_APL_MASK                (0x7U)
#define DMA_TCD_CH30_PRI_APL_SHIFT               (0U)
#define DMA_TCD_CH30_PRI_APL_WIDTH               (3U)
#define DMA_TCD_CH30_PRI_APL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_PRI_APL_SHIFT)) & DMA_TCD_CH30_PRI_APL_MASK)

#define DMA_TCD_CH30_PRI_DPA_MASK                (0x40000000U)
#define DMA_TCD_CH30_PRI_DPA_SHIFT               (30U)
#define DMA_TCD_CH30_PRI_DPA_WIDTH               (1U)
#define DMA_TCD_CH30_PRI_DPA(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_PRI_DPA_SHIFT)) & DMA_TCD_CH30_PRI_DPA_MASK)

#define DMA_TCD_CH30_PRI_ECP_MASK                (0x80000000U)
#define DMA_TCD_CH30_PRI_ECP_SHIFT               (31U)
#define DMA_TCD_CH30_PRI_ECP_WIDTH               (1U)
#define DMA_TCD_CH30_PRI_ECP(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH30_PRI_ECP_SHIFT)) & DMA_TCD_CH30_PRI_ECP_MASK)
/*! @} */

/*! @name TCD30_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD30_SADDR_SADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD30_SADDR_SADDR_SHIFT          (0U)
#define DMA_TCD_TCD30_SADDR_SADDR_WIDTH          (32U)
#define DMA_TCD_TCD30_SADDR_SADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD30_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD30_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD30_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD30_SOFF_SOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD30_SOFF_SOFF_SHIFT            (0U)
#define DMA_TCD_TCD30_SOFF_SOFF_WIDTH            (16U)
#define DMA_TCD_TCD30_SOFF_SOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD30_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD30_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD30_ATTR_DSIZE_MASK            (0x7U)
#define DMA_TCD_TCD30_ATTR_DSIZE_SHIFT           (0U)
#define DMA_TCD_TCD30_ATTR_DSIZE_WIDTH           (3U)
#define DMA_TCD_TCD30_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD30_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD30_ATTR_DMOD_MASK             (0xF8U)
#define DMA_TCD_TCD30_ATTR_DMOD_SHIFT            (3U)
#define DMA_TCD_TCD30_ATTR_DMOD_WIDTH            (5U)
#define DMA_TCD_TCD30_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD30_ATTR_DMOD_MASK)

#define DMA_TCD_TCD30_ATTR_SSIZE_MASK            (0x700U)
#define DMA_TCD_TCD30_ATTR_SSIZE_SHIFT           (8U)
#define DMA_TCD_TCD30_ATTR_SSIZE_WIDTH           (3U)
#define DMA_TCD_TCD30_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD30_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD30_ATTR_SMOD_MASK             (0xF800U)
#define DMA_TCD_TCD30_ATTR_SMOD_SHIFT            (11U)
#define DMA_TCD_TCD30_ATTR_SMOD_WIDTH            (5U)
#define DMA_TCD_TCD30_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD30_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD30_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD30_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_TCD_TCD30_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD30_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD30_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD30_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD30_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD30_NBYTES_MLOFFNO_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD30_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD30_NBYTES_MLOFFNO_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD30_NBYTES_MLOFFNO_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD30_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD30_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD30_NBYTES_MLOFFNO_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD30_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD30_NBYTES_MLOFFNO_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD30_NBYTES_MLOFFNO_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD30_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD30_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD30_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD30_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD30_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD30_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD30_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD30_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD30_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD30_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_TCD_TCD30_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD30_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD30_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD30_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD30_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD30_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_TCD_TCD30_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD30_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD30_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD30_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD30_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD30_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_TCD_TCD30_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD30_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD30_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD30_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD30_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD30_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD30_SLAST_SDA_SLAST_SDA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD30_SLAST_SDA_SLAST_SDA_SHIFT  (0U)
#define DMA_TCD_TCD30_SLAST_SDA_SLAST_SDA_WIDTH  (32U)
#define DMA_TCD_TCD30_SLAST_SDA_SLAST_SDA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD30_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD30_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD30_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD30_DADDR_DADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD30_DADDR_DADDR_SHIFT          (0U)
#define DMA_TCD_TCD30_DADDR_DADDR_WIDTH          (32U)
#define DMA_TCD_TCD30_DADDR_DADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD30_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD30_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD30_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD30_DOFF_DOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD30_DOFF_DOFF_SHIFT            (0U)
#define DMA_TCD_TCD30_DOFF_DOFF_WIDTH            (16U)
#define DMA_TCD_TCD30_DOFF_DOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD30_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD30_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD30_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD30_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_TCD_TCD30_CITER_ELINKNO_CITER_WIDTH  (15U)
#define DMA_TCD_TCD30_CITER_ELINKNO_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD30_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD30_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD30_CITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD30_CITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD30_CITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD30_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD30_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD30_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_TCD_TCD30_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_TCD_TCD30_CITER_ELINKYES_CITER_WIDTH (9U)
#define DMA_TCD_TCD30_CITER_ELINKYES_CITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD30_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD30_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD30_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD30_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD30_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD30_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD30_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD30_CITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD30_CITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD30_CITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD30_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD30_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD30_DLAST_SGA_DLAST_SGA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD30_DLAST_SGA_DLAST_SGA_SHIFT  (0U)
#define DMA_TCD_TCD30_DLAST_SGA_DLAST_SGA_WIDTH  (32U)
#define DMA_TCD_TCD30_DLAST_SGA_DLAST_SGA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD30_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD30_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD30_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD30_CSR_START_MASK             (0x1U)
#define DMA_TCD_TCD30_CSR_START_SHIFT            (0U)
#define DMA_TCD_TCD30_CSR_START_WIDTH            (1U)
#define DMA_TCD_TCD30_CSR_START(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_CSR_START_SHIFT)) & DMA_TCD_TCD30_CSR_START_MASK)

#define DMA_TCD_TCD30_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_TCD_TCD30_CSR_INTMAJOR_SHIFT         (1U)
#define DMA_TCD_TCD30_CSR_INTMAJOR_WIDTH         (1U)
#define DMA_TCD_TCD30_CSR_INTMAJOR(x)            (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD30_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD30_CSR_INTHALF_MASK           (0x4U)
#define DMA_TCD_TCD30_CSR_INTHALF_SHIFT          (2U)
#define DMA_TCD_TCD30_CSR_INTHALF_WIDTH          (1U)
#define DMA_TCD_TCD30_CSR_INTHALF(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD30_CSR_INTHALF_MASK)

#define DMA_TCD_TCD30_CSR_DREQ_MASK              (0x8U)
#define DMA_TCD_TCD30_CSR_DREQ_SHIFT             (3U)
#define DMA_TCD_TCD30_CSR_DREQ_WIDTH             (1U)
#define DMA_TCD_TCD30_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_CSR_DREQ_SHIFT)) & DMA_TCD_TCD30_CSR_DREQ_MASK)

#define DMA_TCD_TCD30_CSR_ESG_MASK               (0x10U)
#define DMA_TCD_TCD30_CSR_ESG_SHIFT              (4U)
#define DMA_TCD_TCD30_CSR_ESG_WIDTH              (1U)
#define DMA_TCD_TCD30_CSR_ESG(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_CSR_ESG_SHIFT)) & DMA_TCD_TCD30_CSR_ESG_MASK)

#define DMA_TCD_TCD30_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_TCD_TCD30_CSR_MAJORELINK_SHIFT       (5U)
#define DMA_TCD_TCD30_CSR_MAJORELINK_WIDTH       (1U)
#define DMA_TCD_TCD30_CSR_MAJORELINK(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD30_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD30_CSR_EEOP_MASK              (0x40U)
#define DMA_TCD_TCD30_CSR_EEOP_SHIFT             (6U)
#define DMA_TCD_TCD30_CSR_EEOP_WIDTH             (1U)
#define DMA_TCD_TCD30_CSR_EEOP(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_CSR_EEOP_SHIFT)) & DMA_TCD_TCD30_CSR_EEOP_MASK)

#define DMA_TCD_TCD30_CSR_ESDA_MASK              (0x80U)
#define DMA_TCD_TCD30_CSR_ESDA_SHIFT             (7U)
#define DMA_TCD_TCD30_CSR_ESDA_WIDTH             (1U)
#define DMA_TCD_TCD30_CSR_ESDA(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_CSR_ESDA_SHIFT)) & DMA_TCD_TCD30_CSR_ESDA_MASK)

#define DMA_TCD_TCD30_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_TCD_TCD30_CSR_MAJORLINKCH_SHIFT      (8U)
#define DMA_TCD_TCD30_CSR_MAJORLINKCH_WIDTH      (5U)
#define DMA_TCD_TCD30_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD30_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD30_CSR_BWC_MASK               (0xC000U)
#define DMA_TCD_TCD30_CSR_BWC_SHIFT              (14U)
#define DMA_TCD_TCD30_CSR_BWC_WIDTH              (2U)
#define DMA_TCD_TCD30_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_CSR_BWC_SHIFT)) & DMA_TCD_TCD30_CSR_BWC_MASK)
/*! @} */

/*! @name TCD30_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD30_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD30_BITER_ELINKNO_BITER_SHIFT  (0U)
#define DMA_TCD_TCD30_BITER_ELINKNO_BITER_WIDTH  (15U)
#define DMA_TCD_TCD30_BITER_ELINKNO_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD30_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD30_BITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD30_BITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD30_BITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD30_BITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD30_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD30_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD30_BITER_ELINKYES_BITER_MASK  (0x1FFU)
#define DMA_TCD_TCD30_BITER_ELINKYES_BITER_SHIFT (0U)
#define DMA_TCD_TCD30_BITER_ELINKYES_BITER_WIDTH (9U)
#define DMA_TCD_TCD30_BITER_ELINKYES_BITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD30_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD30_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD30_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD30_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD30_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD30_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD30_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD30_BITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD30_BITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD30_BITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD30_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD30_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name CH31_CSR - Channel Control and Status */
/*! @{ */

#define DMA_TCD_CH31_CSR_ERQ_MASK                (0x1U)
#define DMA_TCD_CH31_CSR_ERQ_SHIFT               (0U)
#define DMA_TCD_CH31_CSR_ERQ_WIDTH               (1U)
#define DMA_TCD_CH31_CSR_ERQ(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_CSR_ERQ_SHIFT)) & DMA_TCD_CH31_CSR_ERQ_MASK)

#define DMA_TCD_CH31_CSR_EARQ_MASK               (0x2U)
#define DMA_TCD_CH31_CSR_EARQ_SHIFT              (1U)
#define DMA_TCD_CH31_CSR_EARQ_WIDTH              (1U)
#define DMA_TCD_CH31_CSR_EARQ(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_CSR_EARQ_SHIFT)) & DMA_TCD_CH31_CSR_EARQ_MASK)

#define DMA_TCD_CH31_CSR_EEI_MASK                (0x4U)
#define DMA_TCD_CH31_CSR_EEI_SHIFT               (2U)
#define DMA_TCD_CH31_CSR_EEI_WIDTH               (1U)
#define DMA_TCD_CH31_CSR_EEI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_CSR_EEI_SHIFT)) & DMA_TCD_CH31_CSR_EEI_MASK)

#define DMA_TCD_CH31_CSR_EBW_MASK                (0x8U)
#define DMA_TCD_CH31_CSR_EBW_SHIFT               (3U)
#define DMA_TCD_CH31_CSR_EBW_WIDTH               (1U)
#define DMA_TCD_CH31_CSR_EBW(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_CSR_EBW_SHIFT)) & DMA_TCD_CH31_CSR_EBW_MASK)

#define DMA_TCD_CH31_CSR_DONE_MASK               (0x40000000U)
#define DMA_TCD_CH31_CSR_DONE_SHIFT              (30U)
#define DMA_TCD_CH31_CSR_DONE_WIDTH              (1U)
#define DMA_TCD_CH31_CSR_DONE(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_CSR_DONE_SHIFT)) & DMA_TCD_CH31_CSR_DONE_MASK)

#define DMA_TCD_CH31_CSR_ACTIVE_MASK             (0x80000000U)
#define DMA_TCD_CH31_CSR_ACTIVE_SHIFT            (31U)
#define DMA_TCD_CH31_CSR_ACTIVE_WIDTH            (1U)
#define DMA_TCD_CH31_CSR_ACTIVE(x)               (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_CSR_ACTIVE_SHIFT)) & DMA_TCD_CH31_CSR_ACTIVE_MASK)
/*! @} */

/*! @name CH31_ES - Channel Error Status */
/*! @{ */

#define DMA_TCD_CH31_ES_DBE_MASK                 (0x1U)
#define DMA_TCD_CH31_ES_DBE_SHIFT                (0U)
#define DMA_TCD_CH31_ES_DBE_WIDTH                (1U)
#define DMA_TCD_CH31_ES_DBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_ES_DBE_SHIFT)) & DMA_TCD_CH31_ES_DBE_MASK)

#define DMA_TCD_CH31_ES_SBE_MASK                 (0x2U)
#define DMA_TCD_CH31_ES_SBE_SHIFT                (1U)
#define DMA_TCD_CH31_ES_SBE_WIDTH                (1U)
#define DMA_TCD_CH31_ES_SBE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_ES_SBE_SHIFT)) & DMA_TCD_CH31_ES_SBE_MASK)

#define DMA_TCD_CH31_ES_SGE_MASK                 (0x4U)
#define DMA_TCD_CH31_ES_SGE_SHIFT                (2U)
#define DMA_TCD_CH31_ES_SGE_WIDTH                (1U)
#define DMA_TCD_CH31_ES_SGE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_ES_SGE_SHIFT)) & DMA_TCD_CH31_ES_SGE_MASK)

#define DMA_TCD_CH31_ES_NCE_MASK                 (0x8U)
#define DMA_TCD_CH31_ES_NCE_SHIFT                (3U)
#define DMA_TCD_CH31_ES_NCE_WIDTH                (1U)
#define DMA_TCD_CH31_ES_NCE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_ES_NCE_SHIFT)) & DMA_TCD_CH31_ES_NCE_MASK)

#define DMA_TCD_CH31_ES_DOE_MASK                 (0x10U)
#define DMA_TCD_CH31_ES_DOE_SHIFT                (4U)
#define DMA_TCD_CH31_ES_DOE_WIDTH                (1U)
#define DMA_TCD_CH31_ES_DOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_ES_DOE_SHIFT)) & DMA_TCD_CH31_ES_DOE_MASK)

#define DMA_TCD_CH31_ES_DAE_MASK                 (0x20U)
#define DMA_TCD_CH31_ES_DAE_SHIFT                (5U)
#define DMA_TCD_CH31_ES_DAE_WIDTH                (1U)
#define DMA_TCD_CH31_ES_DAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_ES_DAE_SHIFT)) & DMA_TCD_CH31_ES_DAE_MASK)

#define DMA_TCD_CH31_ES_SOE_MASK                 (0x40U)
#define DMA_TCD_CH31_ES_SOE_SHIFT                (6U)
#define DMA_TCD_CH31_ES_SOE_WIDTH                (1U)
#define DMA_TCD_CH31_ES_SOE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_ES_SOE_SHIFT)) & DMA_TCD_CH31_ES_SOE_MASK)

#define DMA_TCD_CH31_ES_SAE_MASK                 (0x80U)
#define DMA_TCD_CH31_ES_SAE_SHIFT                (7U)
#define DMA_TCD_CH31_ES_SAE_WIDTH                (1U)
#define DMA_TCD_CH31_ES_SAE(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_ES_SAE_SHIFT)) & DMA_TCD_CH31_ES_SAE_MASK)

#define DMA_TCD_CH31_ES_ERR_MASK                 (0x80000000U)
#define DMA_TCD_CH31_ES_ERR_SHIFT                (31U)
#define DMA_TCD_CH31_ES_ERR_WIDTH                (1U)
#define DMA_TCD_CH31_ES_ERR(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_ES_ERR_SHIFT)) & DMA_TCD_CH31_ES_ERR_MASK)
/*! @} */

/*! @name CH31_INT - Channel Interrupt Status */
/*! @{ */

#define DMA_TCD_CH31_INT_INT_MASK                (0x1U)
#define DMA_TCD_CH31_INT_INT_SHIFT               (0U)
#define DMA_TCD_CH31_INT_INT_WIDTH               (1U)
#define DMA_TCD_CH31_INT_INT(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_INT_INT_SHIFT)) & DMA_TCD_CH31_INT_INT_MASK)
/*! @} */

/*! @name CH31_SBR - Channel System Bus */
/*! @{ */

#define DMA_TCD_CH31_SBR_MID_MASK                (0xFU)
#define DMA_TCD_CH31_SBR_MID_SHIFT               (0U)
#define DMA_TCD_CH31_SBR_MID_WIDTH               (4U)
#define DMA_TCD_CH31_SBR_MID(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_SBR_MID_SHIFT)) & DMA_TCD_CH31_SBR_MID_MASK)

#define DMA_TCD_CH31_SBR_PAL_MASK                (0x8000U)
#define DMA_TCD_CH31_SBR_PAL_SHIFT               (15U)
#define DMA_TCD_CH31_SBR_PAL_WIDTH               (1U)
#define DMA_TCD_CH31_SBR_PAL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_SBR_PAL_SHIFT)) & DMA_TCD_CH31_SBR_PAL_MASK)

#define DMA_TCD_CH31_SBR_EMI_MASK                (0x10000U)
#define DMA_TCD_CH31_SBR_EMI_SHIFT               (16U)
#define DMA_TCD_CH31_SBR_EMI_WIDTH               (1U)
#define DMA_TCD_CH31_SBR_EMI(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_SBR_EMI_SHIFT)) & DMA_TCD_CH31_SBR_EMI_MASK)

#define DMA_TCD_CH31_SBR_ATTR_MASK               (0xE0000U)
#define DMA_TCD_CH31_SBR_ATTR_SHIFT              (17U)
#define DMA_TCD_CH31_SBR_ATTR_WIDTH              (3U)
#define DMA_TCD_CH31_SBR_ATTR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_SBR_ATTR_SHIFT)) & DMA_TCD_CH31_SBR_ATTR_MASK)
/*! @} */

/*! @name CH31_PRI - Channel Priority */
/*! @{ */

#define DMA_TCD_CH31_PRI_APL_MASK                (0x7U)
#define DMA_TCD_CH31_PRI_APL_SHIFT               (0U)
#define DMA_TCD_CH31_PRI_APL_WIDTH               (3U)
#define DMA_TCD_CH31_PRI_APL(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_PRI_APL_SHIFT)) & DMA_TCD_CH31_PRI_APL_MASK)

#define DMA_TCD_CH31_PRI_DPA_MASK                (0x40000000U)
#define DMA_TCD_CH31_PRI_DPA_SHIFT               (30U)
#define DMA_TCD_CH31_PRI_DPA_WIDTH               (1U)
#define DMA_TCD_CH31_PRI_DPA(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_PRI_DPA_SHIFT)) & DMA_TCD_CH31_PRI_DPA_MASK)

#define DMA_TCD_CH31_PRI_ECP_MASK                (0x80000000U)
#define DMA_TCD_CH31_PRI_ECP_SHIFT               (31U)
#define DMA_TCD_CH31_PRI_ECP_WIDTH               (1U)
#define DMA_TCD_CH31_PRI_ECP(x)                  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_CH31_PRI_ECP_SHIFT)) & DMA_TCD_CH31_PRI_ECP_MASK)
/*! @} */

/*! @name TCD31_SADDR - TCD Source Address */
/*! @{ */

#define DMA_TCD_TCD31_SADDR_SADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD31_SADDR_SADDR_SHIFT          (0U)
#define DMA_TCD_TCD31_SADDR_SADDR_WIDTH          (32U)
#define DMA_TCD_TCD31_SADDR_SADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD31_SADDR_SADDR_SHIFT)) & DMA_TCD_TCD31_SADDR_SADDR_MASK)
/*! @} */

/*! @name TCD31_SOFF - TCD Signed Source Address Offset */
/*! @{ */

#define DMA_TCD_TCD31_SOFF_SOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD31_SOFF_SOFF_SHIFT            (0U)
#define DMA_TCD_TCD31_SOFF_SOFF_WIDTH            (16U)
#define DMA_TCD_TCD31_SOFF_SOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_SOFF_SOFF_SHIFT)) & DMA_TCD_TCD31_SOFF_SOFF_MASK)
/*! @} */

/*! @name TCD31_ATTR - TCD Transfer Attributes */
/*! @{ */

#define DMA_TCD_TCD31_ATTR_DSIZE_MASK            (0x7U)
#define DMA_TCD_TCD31_ATTR_DSIZE_SHIFT           (0U)
#define DMA_TCD_TCD31_ATTR_DSIZE_WIDTH           (3U)
#define DMA_TCD_TCD31_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_ATTR_DSIZE_SHIFT)) & DMA_TCD_TCD31_ATTR_DSIZE_MASK)

#define DMA_TCD_TCD31_ATTR_DMOD_MASK             (0xF8U)
#define DMA_TCD_TCD31_ATTR_DMOD_SHIFT            (3U)
#define DMA_TCD_TCD31_ATTR_DMOD_WIDTH            (5U)
#define DMA_TCD_TCD31_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_ATTR_DMOD_SHIFT)) & DMA_TCD_TCD31_ATTR_DMOD_MASK)

#define DMA_TCD_TCD31_ATTR_SSIZE_MASK            (0x700U)
#define DMA_TCD_TCD31_ATTR_SSIZE_SHIFT           (8U)
#define DMA_TCD_TCD31_ATTR_SSIZE_WIDTH           (3U)
#define DMA_TCD_TCD31_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_ATTR_SSIZE_SHIFT)) & DMA_TCD_TCD31_ATTR_SSIZE_MASK)

#define DMA_TCD_TCD31_ATTR_SMOD_MASK             (0xF800U)
#define DMA_TCD_TCD31_ATTR_SMOD_SHIFT            (11U)
#define DMA_TCD_TCD31_ATTR_SMOD_WIDTH            (5U)
#define DMA_TCD_TCD31_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_ATTR_SMOD_SHIFT)) & DMA_TCD_TCD31_ATTR_SMOD_MASK)
/*! @} */

/*! @name TCD31_NBYTES_MLOFFNO - TCD Transfer Size Without Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD31_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_TCD_TCD31_NBYTES_MLOFFNO_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD31_NBYTES_MLOFFNO_NBYTES_WIDTH (30U)
#define DMA_TCD_TCD31_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD31_NBYTES_MLOFFNO_NBYTES_SHIFT)) & DMA_TCD_TCD31_NBYTES_MLOFFNO_NBYTES_MASK)

#define DMA_TCD_TCD31_NBYTES_MLOFFNO_DMLOE_MASK  (0x40000000U)
#define DMA_TCD_TCD31_NBYTES_MLOFFNO_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD31_NBYTES_MLOFFNO_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD31_NBYTES_MLOFFNO_DMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD31_NBYTES_MLOFFNO_DMLOE_SHIFT)) & DMA_TCD_TCD31_NBYTES_MLOFFNO_DMLOE_MASK)

#define DMA_TCD_TCD31_NBYTES_MLOFFNO_SMLOE_MASK  (0x80000000U)
#define DMA_TCD_TCD31_NBYTES_MLOFFNO_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD31_NBYTES_MLOFFNO_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD31_NBYTES_MLOFFNO_SMLOE(x)    (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD31_NBYTES_MLOFFNO_SMLOE_SHIFT)) & DMA_TCD_TCD31_NBYTES_MLOFFNO_SMLOE_MASK)
/*! @} */

/*! @name TCD31_NBYTES_MLOFFYES - TCD Transfer Size with Minor Loop Offsets */
/*! @{ */

#define DMA_TCD_TCD31_NBYTES_MLOFFYES_NBYTES_MASK (0x3FFU)
#define DMA_TCD_TCD31_NBYTES_MLOFFYES_NBYTES_SHIFT (0U)
#define DMA_TCD_TCD31_NBYTES_MLOFFYES_NBYTES_WIDTH (10U)
#define DMA_TCD_TCD31_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD31_NBYTES_MLOFFYES_NBYTES_SHIFT)) & DMA_TCD_TCD31_NBYTES_MLOFFYES_NBYTES_MASK)

#define DMA_TCD_TCD31_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_TCD_TCD31_NBYTES_MLOFFYES_MLOFF_SHIFT (10U)
#define DMA_TCD_TCD31_NBYTES_MLOFFYES_MLOFF_WIDTH (20U)
#define DMA_TCD_TCD31_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD31_NBYTES_MLOFFYES_MLOFF_SHIFT)) & DMA_TCD_TCD31_NBYTES_MLOFFYES_MLOFF_MASK)

#define DMA_TCD_TCD31_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_TCD_TCD31_NBYTES_MLOFFYES_DMLOE_SHIFT (30U)
#define DMA_TCD_TCD31_NBYTES_MLOFFYES_DMLOE_WIDTH (1U)
#define DMA_TCD_TCD31_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD31_NBYTES_MLOFFYES_DMLOE_SHIFT)) & DMA_TCD_TCD31_NBYTES_MLOFFYES_DMLOE_MASK)

#define DMA_TCD_TCD31_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_TCD_TCD31_NBYTES_MLOFFYES_SMLOE_SHIFT (31U)
#define DMA_TCD_TCD31_NBYTES_MLOFFYES_SMLOE_WIDTH (1U)
#define DMA_TCD_TCD31_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD31_NBYTES_MLOFFYES_SMLOE_SHIFT)) & DMA_TCD_TCD31_NBYTES_MLOFFYES_SMLOE_MASK)
/*! @} */

/*! @name TCD31_SLAST_SDA - TCD Last Source Address Adjustment / Store DADDR Address */
/*! @{ */

#define DMA_TCD_TCD31_SLAST_SDA_SLAST_SDA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD31_SLAST_SDA_SLAST_SDA_SHIFT  (0U)
#define DMA_TCD_TCD31_SLAST_SDA_SLAST_SDA_WIDTH  (32U)
#define DMA_TCD_TCD31_SLAST_SDA_SLAST_SDA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD31_SLAST_SDA_SLAST_SDA_SHIFT)) & DMA_TCD_TCD31_SLAST_SDA_SLAST_SDA_MASK)
/*! @} */

/*! @name TCD31_DADDR - TCD Destination Address */
/*! @{ */

#define DMA_TCD_TCD31_DADDR_DADDR_MASK           (0xFFFFFFFFU)
#define DMA_TCD_TCD31_DADDR_DADDR_SHIFT          (0U)
#define DMA_TCD_TCD31_DADDR_DADDR_WIDTH          (32U)
#define DMA_TCD_TCD31_DADDR_DADDR(x)             (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD31_DADDR_DADDR_SHIFT)) & DMA_TCD_TCD31_DADDR_DADDR_MASK)
/*! @} */

/*! @name TCD31_DOFF - TCD Signed Destination Address Offset */
/*! @{ */

#define DMA_TCD_TCD31_DOFF_DOFF_MASK             (0xFFFFU)
#define DMA_TCD_TCD31_DOFF_DOFF_SHIFT            (0U)
#define DMA_TCD_TCD31_DOFF_DOFF_WIDTH            (16U)
#define DMA_TCD_TCD31_DOFF_DOFF(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_DOFF_DOFF_SHIFT)) & DMA_TCD_TCD31_DOFF_DOFF_MASK)
/*! @} */

/*! @name TCD31_CITER_ELINKNO - TCD Current Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD31_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD31_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_TCD_TCD31_CITER_ELINKNO_CITER_WIDTH  (15U)
#define DMA_TCD_TCD31_CITER_ELINKNO_CITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_CITER_ELINKNO_CITER_SHIFT)) & DMA_TCD_TCD31_CITER_ELINKNO_CITER_MASK)

#define DMA_TCD_TCD31_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD31_CITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD31_CITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD31_CITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_CITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD31_CITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD31_CITER_ELINKYES - TCD Current Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD31_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_TCD_TCD31_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_TCD_TCD31_CITER_ELINKYES_CITER_WIDTH (9U)
#define DMA_TCD_TCD31_CITER_ELINKYES_CITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_CITER_ELINKYES_CITER_SHIFT)) & DMA_TCD_TCD31_CITER_ELINKYES_CITER_MASK)

#define DMA_TCD_TCD31_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD31_CITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD31_CITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD31_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_CITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD31_CITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD31_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD31_CITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD31_CITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD31_CITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_CITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD31_CITER_ELINKYES_ELINK_MASK)
/*! @} */

/*! @name TCD31_DLAST_SGA - TCD Last Destination Address Adjustment / Scatter Gather Address */
/*! @{ */

#define DMA_TCD_TCD31_DLAST_SGA_DLAST_SGA_MASK   (0xFFFFFFFFU)
#define DMA_TCD_TCD31_DLAST_SGA_DLAST_SGA_SHIFT  (0U)
#define DMA_TCD_TCD31_DLAST_SGA_DLAST_SGA_WIDTH  (32U)
#define DMA_TCD_TCD31_DLAST_SGA_DLAST_SGA(x)     (((uint32_t)(((uint32_t)(x)) << DMA_TCD_TCD31_DLAST_SGA_DLAST_SGA_SHIFT)) & DMA_TCD_TCD31_DLAST_SGA_DLAST_SGA_MASK)
/*! @} */

/*! @name TCD31_CSR - TCD Control and Status */
/*! @{ */

#define DMA_TCD_TCD31_CSR_START_MASK             (0x1U)
#define DMA_TCD_TCD31_CSR_START_SHIFT            (0U)
#define DMA_TCD_TCD31_CSR_START_WIDTH            (1U)
#define DMA_TCD_TCD31_CSR_START(x)               (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_CSR_START_SHIFT)) & DMA_TCD_TCD31_CSR_START_MASK)

#define DMA_TCD_TCD31_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_TCD_TCD31_CSR_INTMAJOR_SHIFT         (1U)
#define DMA_TCD_TCD31_CSR_INTMAJOR_WIDTH         (1U)
#define DMA_TCD_TCD31_CSR_INTMAJOR(x)            (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_CSR_INTMAJOR_SHIFT)) & DMA_TCD_TCD31_CSR_INTMAJOR_MASK)

#define DMA_TCD_TCD31_CSR_INTHALF_MASK           (0x4U)
#define DMA_TCD_TCD31_CSR_INTHALF_SHIFT          (2U)
#define DMA_TCD_TCD31_CSR_INTHALF_WIDTH          (1U)
#define DMA_TCD_TCD31_CSR_INTHALF(x)             (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_CSR_INTHALF_SHIFT)) & DMA_TCD_TCD31_CSR_INTHALF_MASK)

#define DMA_TCD_TCD31_CSR_DREQ_MASK              (0x8U)
#define DMA_TCD_TCD31_CSR_DREQ_SHIFT             (3U)
#define DMA_TCD_TCD31_CSR_DREQ_WIDTH             (1U)
#define DMA_TCD_TCD31_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_CSR_DREQ_SHIFT)) & DMA_TCD_TCD31_CSR_DREQ_MASK)

#define DMA_TCD_TCD31_CSR_ESG_MASK               (0x10U)
#define DMA_TCD_TCD31_CSR_ESG_SHIFT              (4U)
#define DMA_TCD_TCD31_CSR_ESG_WIDTH              (1U)
#define DMA_TCD_TCD31_CSR_ESG(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_CSR_ESG_SHIFT)) & DMA_TCD_TCD31_CSR_ESG_MASK)

#define DMA_TCD_TCD31_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_TCD_TCD31_CSR_MAJORELINK_SHIFT       (5U)
#define DMA_TCD_TCD31_CSR_MAJORELINK_WIDTH       (1U)
#define DMA_TCD_TCD31_CSR_MAJORELINK(x)          (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_CSR_MAJORELINK_SHIFT)) & DMA_TCD_TCD31_CSR_MAJORELINK_MASK)

#define DMA_TCD_TCD31_CSR_EEOP_MASK              (0x40U)
#define DMA_TCD_TCD31_CSR_EEOP_SHIFT             (6U)
#define DMA_TCD_TCD31_CSR_EEOP_WIDTH             (1U)
#define DMA_TCD_TCD31_CSR_EEOP(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_CSR_EEOP_SHIFT)) & DMA_TCD_TCD31_CSR_EEOP_MASK)

#define DMA_TCD_TCD31_CSR_ESDA_MASK              (0x80U)
#define DMA_TCD_TCD31_CSR_ESDA_SHIFT             (7U)
#define DMA_TCD_TCD31_CSR_ESDA_WIDTH             (1U)
#define DMA_TCD_TCD31_CSR_ESDA(x)                (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_CSR_ESDA_SHIFT)) & DMA_TCD_TCD31_CSR_ESDA_MASK)

#define DMA_TCD_TCD31_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_TCD_TCD31_CSR_MAJORLINKCH_SHIFT      (8U)
#define DMA_TCD_TCD31_CSR_MAJORLINKCH_WIDTH      (5U)
#define DMA_TCD_TCD31_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_CSR_MAJORLINKCH_SHIFT)) & DMA_TCD_TCD31_CSR_MAJORLINKCH_MASK)

#define DMA_TCD_TCD31_CSR_BWC_MASK               (0xC000U)
#define DMA_TCD_TCD31_CSR_BWC_SHIFT              (14U)
#define DMA_TCD_TCD31_CSR_BWC_WIDTH              (2U)
#define DMA_TCD_TCD31_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_CSR_BWC_SHIFT)) & DMA_TCD_TCD31_CSR_BWC_MASK)
/*! @} */

/*! @name TCD31_BITER_ELINKNO - TCD Beginning Major Loop Count (Minor Loop Channel Linking Disabled) */
/*! @{ */

#define DMA_TCD_TCD31_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_TCD_TCD31_BITER_ELINKNO_BITER_SHIFT  (0U)
#define DMA_TCD_TCD31_BITER_ELINKNO_BITER_WIDTH  (15U)
#define DMA_TCD_TCD31_BITER_ELINKNO_BITER(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_BITER_ELINKNO_BITER_SHIFT)) & DMA_TCD_TCD31_BITER_ELINKNO_BITER_MASK)

#define DMA_TCD_TCD31_BITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_TCD_TCD31_BITER_ELINKNO_ELINK_SHIFT  (15U)
#define DMA_TCD_TCD31_BITER_ELINKNO_ELINK_WIDTH  (1U)
#define DMA_TCD_TCD31_BITER_ELINKNO_ELINK(x)     (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_BITER_ELINKNO_ELINK_SHIFT)) & DMA_TCD_TCD31_BITER_ELINKNO_ELINK_MASK)
/*! @} */

/*! @name TCD31_BITER_ELINKYES - TCD Beginning Major Loop Count (Minor Loop Channel Linking Enabled) */
/*! @{ */

#define DMA_TCD_TCD31_BITER_ELINKYES_BITER_MASK  (0x1FFU)
#define DMA_TCD_TCD31_BITER_ELINKYES_BITER_SHIFT (0U)
#define DMA_TCD_TCD31_BITER_ELINKYES_BITER_WIDTH (9U)
#define DMA_TCD_TCD31_BITER_ELINKYES_BITER(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_BITER_ELINKYES_BITER_SHIFT)) & DMA_TCD_TCD31_BITER_ELINKYES_BITER_MASK)

#define DMA_TCD_TCD31_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_TCD_TCD31_BITER_ELINKYES_LINKCH_SHIFT (9U)
#define DMA_TCD_TCD31_BITER_ELINKYES_LINKCH_WIDTH (5U)
#define DMA_TCD_TCD31_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_BITER_ELINKYES_LINKCH_SHIFT)) & DMA_TCD_TCD31_BITER_ELINKYES_LINKCH_MASK)

#define DMA_TCD_TCD31_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_TCD_TCD31_BITER_ELINKYES_ELINK_SHIFT (15U)
#define DMA_TCD_TCD31_BITER_ELINKYES_ELINK_WIDTH (1U)
#define DMA_TCD_TCD31_BITER_ELINKYES_ELINK(x)    (((uint16_t)(((uint16_t)(x)) << DMA_TCD_TCD31_BITER_ELINKYES_ELINK_SHIFT)) & DMA_TCD_TCD31_BITER_ELINKYES_ELINK_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group DMA_TCD_Register_Masks */

/*!
 * @}
 */ /* end of group DMA_TCD_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_DMA_TCD_H_) */
