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
 * @file S32K344_FLEXIO.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_FLEXIO
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
#if !defined(S32K344_FLEXIO_H_)  /* Check if memory map has not been already included */
#define S32K344_FLEXIO_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- FLEXIO Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLEXIO_Peripheral_Access_Layer FLEXIO Peripheral Access Layer
 * @{
 */

/** FLEXIO - Size of Registers Arrays */
#define FLEXIO_SHIFTCTL_COUNT                     8u
#define FLEXIO_SHIFTCFG_COUNT                     8u
#define FLEXIO_SHIFTBUF_COUNT                     8u
#define FLEXIO_SHIFTBUFBIS_COUNT                  8u
#define FLEXIO_SHIFTBUFBYS_COUNT                  8u
#define FLEXIO_SHIFTBUFBBS_COUNT                  8u
#define FLEXIO_TIMCTL_COUNT                       8u
#define FLEXIO_TIMCFG_COUNT                       8u
#define FLEXIO_TIMCMP_COUNT                       8u
#define FLEXIO_SHIFTBUFNBS_COUNT                  8u
#define FLEXIO_SHIFTBUFHWS_COUNT                  8u
#define FLEXIO_SHIFTBUFNIS_COUNT                  8u
#define FLEXIO_SHIFTBUFOES_COUNT                  8u
#define FLEXIO_SHIFTBUFEOS_COUNT                  8u
#define FLEXIO_SHIFTBUFHBS_COUNT                  8u

/** FLEXIO - Register Layout Typedef */
typedef struct {
  __I  uint32_t VERID;                             /**< Version ID Register, offset: 0x0 */
  __I  uint32_t PARAM;                             /**< Parameter Register, offset: 0x4 */
  __IO uint32_t CTRL;                              /**< FlexIO Control Register, offset: 0x8 */
  __I  uint32_t PIN;                               /**< Pin State Register, offset: 0xC */
  __IO uint32_t SHIFTSTAT;                         /**< Shifter Status Register, offset: 0x10 */
  __IO uint32_t SHIFTERR;                          /**< Shifter Error Register, offset: 0x14 */
  __IO uint32_t TIMSTAT;                           /**< Timer Status Register, offset: 0x18 */
  uint8_t RESERVED_0[4];
  __IO uint32_t SHIFTSIEN;                         /**< Shifter Status Interrupt Enable, offset: 0x20 */
  __IO uint32_t SHIFTEIEN;                         /**< Shifter Error Interrupt Enable, offset: 0x24 */
  __IO uint32_t TIMIEN;                            /**< Timer Interrupt Enable Register, offset: 0x28 */
  uint8_t RESERVED_1[4];
  __IO uint32_t SHIFTSDEN;                         /**< Shifter Status DMA Enable, offset: 0x30 */
  uint8_t RESERVED_2[4];
  __IO uint32_t TIMERSDEN;                         /**< Timer Status DMA Enable, offset: 0x38 */
  uint8_t RESERVED_3[4];
  __IO uint32_t SHIFTSTATE;                        /**< Shifter State Register, offset: 0x40 */
  uint8_t RESERVED_4[4];
  __IO uint32_t TRGSTAT;                           /**< Trigger Status Register, offset: 0x48 */
  __IO uint32_t TRIGIEN;                           /**< External Trigger Interrupt Enable Register, offset: 0x4C */
  __IO uint32_t PINSTAT;                           /**< Pin Status Register, offset: 0x50 */
  __IO uint32_t PINIEN;                            /**< Pin Interrupt Enable Register, offset: 0x54 */
  __IO uint32_t PINREN;                            /**< Pin Rising Edge Enable Register, offset: 0x58 */
  __IO uint32_t PINFEN;                            /**< Pin Falling Edge Enable Register, offset: 0x5C */
  __IO uint32_t PINOUTD;                           /**< Pin Output Data Register, offset: 0x60 */
  __IO uint32_t PINOUTE;                           /**< Pin Output Enable Register, offset: 0x64 */
  __O  uint32_t PINOUTDIS;                         /**< Pin Output Disable Register, offset: 0x68 */
  __O  uint32_t PINOUTCLR;                         /**< Pin Output Clear Register, offset: 0x6C */
  __O  uint32_t PINOUTSET;                         /**< Pin Output Set Register, offset: 0x70 */
  __O  uint32_t PINOUTTOG;                         /**< Pin Output Toggle Register, offset: 0x74 */
  uint8_t RESERVED_5[8];
  __IO uint32_t SHIFTCTL[FLEXIO_SHIFTCTL_COUNT];   /**< Shifter Control N Register, array offset: 0x80, array step: 0x4 */
  uint8_t RESERVED_6[96];
  __IO uint32_t SHIFTCFG[FLEXIO_SHIFTCFG_COUNT];   /**< Shifter Configuration N Register, array offset: 0x100, array step: 0x4 */
  uint8_t RESERVED_7[224];
  __IO uint32_t SHIFTBUF[FLEXIO_SHIFTBUF_COUNT];   /**< Shifter Buffer N Register, array offset: 0x200, array step: 0x4 */
  uint8_t RESERVED_8[96];
  __IO uint32_t SHIFTBUFBIS[FLEXIO_SHIFTBUFBIS_COUNT]; /**< Shifter Buffer N Bit Swapped Register, array offset: 0x280, array step: 0x4 */
  uint8_t RESERVED_9[96];
  __IO uint32_t SHIFTBUFBYS[FLEXIO_SHIFTBUFBYS_COUNT]; /**< Shifter Buffer N Byte Swapped Register, array offset: 0x300, array step: 0x4 */
  uint8_t RESERVED_10[96];
  __IO uint32_t SHIFTBUFBBS[FLEXIO_SHIFTBUFBBS_COUNT]; /**< Shifter Buffer N Bit Byte Swapped Register, array offset: 0x380, array step: 0x4 */
  uint8_t RESERVED_11[96];
  __IO uint32_t TIMCTL[FLEXIO_TIMCTL_COUNT];       /**< Timer Control N Register, array offset: 0x400, array step: 0x4 */
  uint8_t RESERVED_12[96];
  __IO uint32_t TIMCFG[FLEXIO_TIMCFG_COUNT];       /**< Timer Configuration N Register, array offset: 0x480, array step: 0x4 */
  uint8_t RESERVED_13[96];
  __IO uint32_t TIMCMP[FLEXIO_TIMCMP_COUNT];       /**< Timer Compare N Register, array offset: 0x500, array step: 0x4 */
  uint8_t RESERVED_14[352];
  __IO uint32_t SHIFTBUFNBS[FLEXIO_SHIFTBUFNBS_COUNT]; /**< Shifter Buffer N Nibble Byte Swapped Register, array offset: 0x680, array step: 0x4 */
  uint8_t RESERVED_15[96];
  __IO uint32_t SHIFTBUFHWS[FLEXIO_SHIFTBUFHWS_COUNT]; /**< Shifter Buffer N Half Word Swapped Register, array offset: 0x700, array step: 0x4 */
  uint8_t RESERVED_16[96];
  __IO uint32_t SHIFTBUFNIS[FLEXIO_SHIFTBUFNIS_COUNT]; /**< Shifter Buffer N Nibble Swapped Register, array offset: 0x780, array step: 0x4 */
  uint8_t RESERVED_17[96];
  __IO uint32_t SHIFTBUFOES[FLEXIO_SHIFTBUFOES_COUNT]; /**< Shifter Buffer N Odd Even Swapped Register, array offset: 0x800, array step: 0x4 */
  uint8_t RESERVED_18[96];
  __IO uint32_t SHIFTBUFEOS[FLEXIO_SHIFTBUFEOS_COUNT]; /**< Shifter Buffer N Even Odd Swapped Register, array offset: 0x880, array step: 0x4 */
  uint8_t RESERVED_19[96];
  __IO uint32_t SHIFTBUFHBS[FLEXIO_SHIFTBUFHBS_COUNT]; /**< Shifter Buffer N Halfword Byte Swapped Register, array offset: 0x900, array step: 0x4 */
} FLEXIO_Type, *FLEXIO_MemMapPtr;

/** Number of instances of the FLEXIO module. */
#define FLEXIO_INSTANCE_COUNT                    (1u)

/* FLEXIO - Peripheral instance base addresses */
/** Peripheral FLEXIO base address */
#define IP_FLEXIO_BASE                           (0x40324000u)
/** Peripheral FLEXIO base pointer */
#define IP_FLEXIO                                ((FLEXIO_Type *)IP_FLEXIO_BASE)
/** Array initializer of FLEXIO peripheral base addresses */
#define IP_FLEXIO_BASE_ADDRS                     { IP_FLEXIO_BASE }
/** Array initializer of FLEXIO peripheral base pointers */
#define IP_FLEXIO_BASE_PTRS                      { IP_FLEXIO }

/* ----------------------------------------------------------------------------
   -- FLEXIO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLEXIO_Register_Masks FLEXIO Register Masks
 * @{
 */

/*! @name VERID - Version ID Register */
/*! @{ */

#define FLEXIO_VERID_FEATURE_MASK                (0xFFFFU)
#define FLEXIO_VERID_FEATURE_SHIFT               (0U)
#define FLEXIO_VERID_FEATURE_WIDTH               (16U)
#define FLEXIO_VERID_FEATURE(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_VERID_FEATURE_SHIFT)) & FLEXIO_VERID_FEATURE_MASK)

#define FLEXIO_VERID_MINOR_MASK                  (0xFF0000U)
#define FLEXIO_VERID_MINOR_SHIFT                 (16U)
#define FLEXIO_VERID_MINOR_WIDTH                 (8U)
#define FLEXIO_VERID_MINOR(x)                    (((uint32_t)(((uint32_t)(x)) << FLEXIO_VERID_MINOR_SHIFT)) & FLEXIO_VERID_MINOR_MASK)

#define FLEXIO_VERID_MAJOR_MASK                  (0xFF000000U)
#define FLEXIO_VERID_MAJOR_SHIFT                 (24U)
#define FLEXIO_VERID_MAJOR_WIDTH                 (8U)
#define FLEXIO_VERID_MAJOR(x)                    (((uint32_t)(((uint32_t)(x)) << FLEXIO_VERID_MAJOR_SHIFT)) & FLEXIO_VERID_MAJOR_MASK)
/*! @} */

/*! @name PARAM - Parameter Register */
/*! @{ */

#define FLEXIO_PARAM_SHIFTER_MASK                (0xFFU)
#define FLEXIO_PARAM_SHIFTER_SHIFT               (0U)
#define FLEXIO_PARAM_SHIFTER_WIDTH               (8U)
#define FLEXIO_PARAM_SHIFTER(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_PARAM_SHIFTER_SHIFT)) & FLEXIO_PARAM_SHIFTER_MASK)

#define FLEXIO_PARAM_TIMER_MASK                  (0xFF00U)
#define FLEXIO_PARAM_TIMER_SHIFT                 (8U)
#define FLEXIO_PARAM_TIMER_WIDTH                 (8U)
#define FLEXIO_PARAM_TIMER(x)                    (((uint32_t)(((uint32_t)(x)) << FLEXIO_PARAM_TIMER_SHIFT)) & FLEXIO_PARAM_TIMER_MASK)

#define FLEXIO_PARAM_PIN_MASK                    (0xFF0000U)
#define FLEXIO_PARAM_PIN_SHIFT                   (16U)
#define FLEXIO_PARAM_PIN_WIDTH                   (8U)
#define FLEXIO_PARAM_PIN(x)                      (((uint32_t)(((uint32_t)(x)) << FLEXIO_PARAM_PIN_SHIFT)) & FLEXIO_PARAM_PIN_MASK)

#define FLEXIO_PARAM_TRIGGER_MASK                (0xFF000000U)
#define FLEXIO_PARAM_TRIGGER_SHIFT               (24U)
#define FLEXIO_PARAM_TRIGGER_WIDTH               (8U)
#define FLEXIO_PARAM_TRIGGER(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_PARAM_TRIGGER_SHIFT)) & FLEXIO_PARAM_TRIGGER_MASK)
/*! @} */

/*! @name CTRL - FlexIO Control Register */
/*! @{ */

#define FLEXIO_CTRL_FLEXEN_MASK                  (0x1U)
#define FLEXIO_CTRL_FLEXEN_SHIFT                 (0U)
#define FLEXIO_CTRL_FLEXEN_WIDTH                 (1U)
#define FLEXIO_CTRL_FLEXEN(x)                    (((uint32_t)(((uint32_t)(x)) << FLEXIO_CTRL_FLEXEN_SHIFT)) & FLEXIO_CTRL_FLEXEN_MASK)

#define FLEXIO_CTRL_SWRST_MASK                   (0x2U)
#define FLEXIO_CTRL_SWRST_SHIFT                  (1U)
#define FLEXIO_CTRL_SWRST_WIDTH                  (1U)
#define FLEXIO_CTRL_SWRST(x)                     (((uint32_t)(((uint32_t)(x)) << FLEXIO_CTRL_SWRST_SHIFT)) & FLEXIO_CTRL_SWRST_MASK)

#define FLEXIO_CTRL_FASTACC_MASK                 (0x4U)
#define FLEXIO_CTRL_FASTACC_SHIFT                (2U)
#define FLEXIO_CTRL_FASTACC_WIDTH                (1U)
#define FLEXIO_CTRL_FASTACC(x)                   (((uint32_t)(((uint32_t)(x)) << FLEXIO_CTRL_FASTACC_SHIFT)) & FLEXIO_CTRL_FASTACC_MASK)

#define FLEXIO_CTRL_DBGE_MASK                    (0x40000000U)
#define FLEXIO_CTRL_DBGE_SHIFT                   (30U)
#define FLEXIO_CTRL_DBGE_WIDTH                   (1U)
#define FLEXIO_CTRL_DBGE(x)                      (((uint32_t)(((uint32_t)(x)) << FLEXIO_CTRL_DBGE_SHIFT)) & FLEXIO_CTRL_DBGE_MASK)
/*! @} */

/*! @name PIN - Pin State Register */
/*! @{ */

#define FLEXIO_PIN_PDI_MASK                      (0xFFFFFFFFU)
#define FLEXIO_PIN_PDI_SHIFT                     (0U)
#define FLEXIO_PIN_PDI_WIDTH                     (32U)
#define FLEXIO_PIN_PDI(x)                        (((uint32_t)(((uint32_t)(x)) << FLEXIO_PIN_PDI_SHIFT)) & FLEXIO_PIN_PDI_MASK)
/*! @} */

/*! @name SHIFTSTAT - Shifter Status Register */
/*! @{ */

#define FLEXIO_SHIFTSTAT_SSF_MASK                (0xFFU)
#define FLEXIO_SHIFTSTAT_SSF_SHIFT               (0U)
#define FLEXIO_SHIFTSTAT_SSF_WIDTH               (8U)
#define FLEXIO_SHIFTSTAT_SSF(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTSTAT_SSF_SHIFT)) & FLEXIO_SHIFTSTAT_SSF_MASK)
/*! @} */

/*! @name SHIFTERR - Shifter Error Register */
/*! @{ */

#define FLEXIO_SHIFTERR_SEF_MASK                 (0xFFU)
#define FLEXIO_SHIFTERR_SEF_SHIFT                (0U)
#define FLEXIO_SHIFTERR_SEF_WIDTH                (8U)
#define FLEXIO_SHIFTERR_SEF(x)                   (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTERR_SEF_SHIFT)) & FLEXIO_SHIFTERR_SEF_MASK)
/*! @} */

/*! @name TIMSTAT - Timer Status Register */
/*! @{ */

#define FLEXIO_TIMSTAT_TSF_MASK                  (0xFFU)
#define FLEXIO_TIMSTAT_TSF_SHIFT                 (0U)
#define FLEXIO_TIMSTAT_TSF_WIDTH                 (8U)
#define FLEXIO_TIMSTAT_TSF(x)                    (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMSTAT_TSF_SHIFT)) & FLEXIO_TIMSTAT_TSF_MASK)
/*! @} */

/*! @name SHIFTSIEN - Shifter Status Interrupt Enable */
/*! @{ */

#define FLEXIO_SHIFTSIEN_SSIE_MASK               (0xFFU)
#define FLEXIO_SHIFTSIEN_SSIE_SHIFT              (0U)
#define FLEXIO_SHIFTSIEN_SSIE_WIDTH              (8U)
#define FLEXIO_SHIFTSIEN_SSIE(x)                 (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTSIEN_SSIE_SHIFT)) & FLEXIO_SHIFTSIEN_SSIE_MASK)
/*! @} */

/*! @name SHIFTEIEN - Shifter Error Interrupt Enable */
/*! @{ */

#define FLEXIO_SHIFTEIEN_SEIE_MASK               (0xFFU)
#define FLEXIO_SHIFTEIEN_SEIE_SHIFT              (0U)
#define FLEXIO_SHIFTEIEN_SEIE_WIDTH              (8U)
#define FLEXIO_SHIFTEIEN_SEIE(x)                 (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTEIEN_SEIE_SHIFT)) & FLEXIO_SHIFTEIEN_SEIE_MASK)
/*! @} */

/*! @name TIMIEN - Timer Interrupt Enable Register */
/*! @{ */

#define FLEXIO_TIMIEN_TEIE_MASK                  (0xFFU)
#define FLEXIO_TIMIEN_TEIE_SHIFT                 (0U)
#define FLEXIO_TIMIEN_TEIE_WIDTH                 (8U)
#define FLEXIO_TIMIEN_TEIE(x)                    (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMIEN_TEIE_SHIFT)) & FLEXIO_TIMIEN_TEIE_MASK)
/*! @} */

/*! @name SHIFTSDEN - Shifter Status DMA Enable */
/*! @{ */

#define FLEXIO_SHIFTSDEN_SSDE_MASK               (0xFFU)
#define FLEXIO_SHIFTSDEN_SSDE_SHIFT              (0U)
#define FLEXIO_SHIFTSDEN_SSDE_WIDTH              (8U)
#define FLEXIO_SHIFTSDEN_SSDE(x)                 (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTSDEN_SSDE_SHIFT)) & FLEXIO_SHIFTSDEN_SSDE_MASK)
/*! @} */

/*! @name TIMERSDEN - Timer Status DMA Enable */
/*! @{ */

#define FLEXIO_TIMERSDEN_TSDE_MASK               (0xFFU)
#define FLEXIO_TIMERSDEN_TSDE_SHIFT              (0U)
#define FLEXIO_TIMERSDEN_TSDE_WIDTH              (8U)
#define FLEXIO_TIMERSDEN_TSDE(x)                 (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMERSDEN_TSDE_SHIFT)) & FLEXIO_TIMERSDEN_TSDE_MASK)
/*! @} */

/*! @name SHIFTSTATE - Shifter State Register */
/*! @{ */

#define FLEXIO_SHIFTSTATE_STATE_MASK             (0x7U)
#define FLEXIO_SHIFTSTATE_STATE_SHIFT            (0U)
#define FLEXIO_SHIFTSTATE_STATE_WIDTH            (3U)
#define FLEXIO_SHIFTSTATE_STATE(x)               (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTSTATE_STATE_SHIFT)) & FLEXIO_SHIFTSTATE_STATE_MASK)
/*! @} */

/*! @name TRGSTAT - Trigger Status Register */
/*! @{ */

#define FLEXIO_TRGSTAT_ETSF_MASK                 (0xFU)
#define FLEXIO_TRGSTAT_ETSF_SHIFT                (0U)
#define FLEXIO_TRGSTAT_ETSF_WIDTH                (4U)
#define FLEXIO_TRGSTAT_ETSF(x)                   (((uint32_t)(((uint32_t)(x)) << FLEXIO_TRGSTAT_ETSF_SHIFT)) & FLEXIO_TRGSTAT_ETSF_MASK)
/*! @} */

/*! @name TRIGIEN - External Trigger Interrupt Enable Register */
/*! @{ */

#define FLEXIO_TRIGIEN_TRIE_MASK                 (0xFU)
#define FLEXIO_TRIGIEN_TRIE_SHIFT                (0U)
#define FLEXIO_TRIGIEN_TRIE_WIDTH                (4U)
#define FLEXIO_TRIGIEN_TRIE(x)                   (((uint32_t)(((uint32_t)(x)) << FLEXIO_TRIGIEN_TRIE_SHIFT)) & FLEXIO_TRIGIEN_TRIE_MASK)
/*! @} */

/*! @name PINSTAT - Pin Status Register */
/*! @{ */

#define FLEXIO_PINSTAT_PSF_MASK                  (0xFFFFFFFFU)
#define FLEXIO_PINSTAT_PSF_SHIFT                 (0U)
#define FLEXIO_PINSTAT_PSF_WIDTH                 (32U)
#define FLEXIO_PINSTAT_PSF(x)                    (((uint32_t)(((uint32_t)(x)) << FLEXIO_PINSTAT_PSF_SHIFT)) & FLEXIO_PINSTAT_PSF_MASK)
/*! @} */

/*! @name PINIEN - Pin Interrupt Enable Register */
/*! @{ */

#define FLEXIO_PINIEN_PSIE_MASK                  (0xFFFFFFFFU)
#define FLEXIO_PINIEN_PSIE_SHIFT                 (0U)
#define FLEXIO_PINIEN_PSIE_WIDTH                 (32U)
#define FLEXIO_PINIEN_PSIE(x)                    (((uint32_t)(((uint32_t)(x)) << FLEXIO_PINIEN_PSIE_SHIFT)) & FLEXIO_PINIEN_PSIE_MASK)
/*! @} */

/*! @name PINREN - Pin Rising Edge Enable Register */
/*! @{ */

#define FLEXIO_PINREN_PRE_MASK                   (0xFFFFFFFFU)
#define FLEXIO_PINREN_PRE_SHIFT                  (0U)
#define FLEXIO_PINREN_PRE_WIDTH                  (32U)
#define FLEXIO_PINREN_PRE(x)                     (((uint32_t)(((uint32_t)(x)) << FLEXIO_PINREN_PRE_SHIFT)) & FLEXIO_PINREN_PRE_MASK)
/*! @} */

/*! @name PINFEN - Pin Falling Edge Enable Register */
/*! @{ */

#define FLEXIO_PINFEN_PFE_MASK                   (0xFFFFFFFFU)
#define FLEXIO_PINFEN_PFE_SHIFT                  (0U)
#define FLEXIO_PINFEN_PFE_WIDTH                  (32U)
#define FLEXIO_PINFEN_PFE(x)                     (((uint32_t)(((uint32_t)(x)) << FLEXIO_PINFEN_PFE_SHIFT)) & FLEXIO_PINFEN_PFE_MASK)
/*! @} */

/*! @name PINOUTD - Pin Output Data Register */
/*! @{ */

#define FLEXIO_PINOUTD_OUTD_MASK                 (0xFFFFFFFFU)
#define FLEXIO_PINOUTD_OUTD_SHIFT                (0U)
#define FLEXIO_PINOUTD_OUTD_WIDTH                (32U)
#define FLEXIO_PINOUTD_OUTD(x)                   (((uint32_t)(((uint32_t)(x)) << FLEXIO_PINOUTD_OUTD_SHIFT)) & FLEXIO_PINOUTD_OUTD_MASK)
/*! @} */

/*! @name PINOUTE - Pin Output Enable Register */
/*! @{ */

#define FLEXIO_PINOUTE_OUTE_MASK                 (0xFFFFFFFFU)
#define FLEXIO_PINOUTE_OUTE_SHIFT                (0U)
#define FLEXIO_PINOUTE_OUTE_WIDTH                (32U)
#define FLEXIO_PINOUTE_OUTE(x)                   (((uint32_t)(((uint32_t)(x)) << FLEXIO_PINOUTE_OUTE_SHIFT)) & FLEXIO_PINOUTE_OUTE_MASK)
/*! @} */

/*! @name PINOUTDIS - Pin Output Disable Register */
/*! @{ */

#define FLEXIO_PINOUTDIS_OUTDIS_MASK             (0xFFFFFFFFU)
#define FLEXIO_PINOUTDIS_OUTDIS_SHIFT            (0U)
#define FLEXIO_PINOUTDIS_OUTDIS_WIDTH            (32U)
#define FLEXIO_PINOUTDIS_OUTDIS(x)               (((uint32_t)(((uint32_t)(x)) << FLEXIO_PINOUTDIS_OUTDIS_SHIFT)) & FLEXIO_PINOUTDIS_OUTDIS_MASK)
/*! @} */

/*! @name PINOUTCLR - Pin Output Clear Register */
/*! @{ */

#define FLEXIO_PINOUTCLR_OUTCLR_MASK             (0xFFFFFFFFU)
#define FLEXIO_PINOUTCLR_OUTCLR_SHIFT            (0U)
#define FLEXIO_PINOUTCLR_OUTCLR_WIDTH            (32U)
#define FLEXIO_PINOUTCLR_OUTCLR(x)               (((uint32_t)(((uint32_t)(x)) << FLEXIO_PINOUTCLR_OUTCLR_SHIFT)) & FLEXIO_PINOUTCLR_OUTCLR_MASK)
/*! @} */

/*! @name PINOUTSET - Pin Output Set Register */
/*! @{ */

#define FLEXIO_PINOUTSET_OUTSET_MASK             (0xFFFFFFFFU)
#define FLEXIO_PINOUTSET_OUTSET_SHIFT            (0U)
#define FLEXIO_PINOUTSET_OUTSET_WIDTH            (32U)
#define FLEXIO_PINOUTSET_OUTSET(x)               (((uint32_t)(((uint32_t)(x)) << FLEXIO_PINOUTSET_OUTSET_SHIFT)) & FLEXIO_PINOUTSET_OUTSET_MASK)
/*! @} */

/*! @name PINOUTTOG - Pin Output Toggle Register */
/*! @{ */

#define FLEXIO_PINOUTTOG_OUTTOG_MASK             (0xFFFFFFFFU)
#define FLEXIO_PINOUTTOG_OUTTOG_SHIFT            (0U)
#define FLEXIO_PINOUTTOG_OUTTOG_WIDTH            (32U)
#define FLEXIO_PINOUTTOG_OUTTOG(x)               (((uint32_t)(((uint32_t)(x)) << FLEXIO_PINOUTTOG_OUTTOG_SHIFT)) & FLEXIO_PINOUTTOG_OUTTOG_MASK)
/*! @} */

/*! @name SHIFTCTL - Shifter Control N Register */
/*! @{ */

#define FLEXIO_SHIFTCTL_SMOD_MASK                (0x7U)
#define FLEXIO_SHIFTCTL_SMOD_SHIFT               (0U)
#define FLEXIO_SHIFTCTL_SMOD_WIDTH               (3U)
#define FLEXIO_SHIFTCTL_SMOD(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCTL_SMOD_SHIFT)) & FLEXIO_SHIFTCTL_SMOD_MASK)

#define FLEXIO_SHIFTCTL_PINPOL_MASK              (0x80U)
#define FLEXIO_SHIFTCTL_PINPOL_SHIFT             (7U)
#define FLEXIO_SHIFTCTL_PINPOL_WIDTH             (1U)
#define FLEXIO_SHIFTCTL_PINPOL(x)                (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCTL_PINPOL_SHIFT)) & FLEXIO_SHIFTCTL_PINPOL_MASK)

#define FLEXIO_SHIFTCTL_PINSEL_MASK              (0x1F00U)
#define FLEXIO_SHIFTCTL_PINSEL_SHIFT             (8U)
#define FLEXIO_SHIFTCTL_PINSEL_WIDTH             (5U)
#define FLEXIO_SHIFTCTL_PINSEL(x)                (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCTL_PINSEL_SHIFT)) & FLEXIO_SHIFTCTL_PINSEL_MASK)

#define FLEXIO_SHIFTCTL_PINCFG_MASK              (0x30000U)
#define FLEXIO_SHIFTCTL_PINCFG_SHIFT             (16U)
#define FLEXIO_SHIFTCTL_PINCFG_WIDTH             (2U)
#define FLEXIO_SHIFTCTL_PINCFG(x)                (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCTL_PINCFG_SHIFT)) & FLEXIO_SHIFTCTL_PINCFG_MASK)

#define FLEXIO_SHIFTCTL_TIMPOL_MASK              (0x800000U)
#define FLEXIO_SHIFTCTL_TIMPOL_SHIFT             (23U)
#define FLEXIO_SHIFTCTL_TIMPOL_WIDTH             (1U)
#define FLEXIO_SHIFTCTL_TIMPOL(x)                (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCTL_TIMPOL_SHIFT)) & FLEXIO_SHIFTCTL_TIMPOL_MASK)

#define FLEXIO_SHIFTCTL_TIMSEL_MASK              (0x7000000U)
#define FLEXIO_SHIFTCTL_TIMSEL_SHIFT             (24U)
#define FLEXIO_SHIFTCTL_TIMSEL_WIDTH             (3U)
#define FLEXIO_SHIFTCTL_TIMSEL(x)                (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCTL_TIMSEL_SHIFT)) & FLEXIO_SHIFTCTL_TIMSEL_MASK)
/*! @} */

/*! @name SHIFTCFG - Shifter Configuration N Register */
/*! @{ */

#define FLEXIO_SHIFTCFG_SSTART_MASK              (0x3U)
#define FLEXIO_SHIFTCFG_SSTART_SHIFT             (0U)
#define FLEXIO_SHIFTCFG_SSTART_WIDTH             (2U)
#define FLEXIO_SHIFTCFG_SSTART(x)                (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCFG_SSTART_SHIFT)) & FLEXIO_SHIFTCFG_SSTART_MASK)

#define FLEXIO_SHIFTCFG_SSTOP_MASK               (0x30U)
#define FLEXIO_SHIFTCFG_SSTOP_SHIFT              (4U)
#define FLEXIO_SHIFTCFG_SSTOP_WIDTH              (2U)
#define FLEXIO_SHIFTCFG_SSTOP(x)                 (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCFG_SSTOP_SHIFT)) & FLEXIO_SHIFTCFG_SSTOP_MASK)

#define FLEXIO_SHIFTCFG_INSRC_MASK               (0x100U)
#define FLEXIO_SHIFTCFG_INSRC_SHIFT              (8U)
#define FLEXIO_SHIFTCFG_INSRC_WIDTH              (1U)
#define FLEXIO_SHIFTCFG_INSRC(x)                 (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCFG_INSRC_SHIFT)) & FLEXIO_SHIFTCFG_INSRC_MASK)

#define FLEXIO_SHIFTCFG_LATST_MASK               (0x200U)
#define FLEXIO_SHIFTCFG_LATST_SHIFT              (9U)
#define FLEXIO_SHIFTCFG_LATST_WIDTH              (1U)
#define FLEXIO_SHIFTCFG_LATST(x)                 (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCFG_LATST_SHIFT)) & FLEXIO_SHIFTCFG_LATST_MASK)

#define FLEXIO_SHIFTCFG_SSIZE_MASK               (0x1000U)
#define FLEXIO_SHIFTCFG_SSIZE_SHIFT              (12U)
#define FLEXIO_SHIFTCFG_SSIZE_WIDTH              (1U)
#define FLEXIO_SHIFTCFG_SSIZE(x)                 (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCFG_SSIZE_SHIFT)) & FLEXIO_SHIFTCFG_SSIZE_MASK)

#define FLEXIO_SHIFTCFG_PWIDTH_MASK              (0x1F0000U)
#define FLEXIO_SHIFTCFG_PWIDTH_SHIFT             (16U)
#define FLEXIO_SHIFTCFG_PWIDTH_WIDTH             (5U)
#define FLEXIO_SHIFTCFG_PWIDTH(x)                (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTCFG_PWIDTH_SHIFT)) & FLEXIO_SHIFTCFG_PWIDTH_MASK)
/*! @} */

/*! @name SHIFTBUF - Shifter Buffer N Register */
/*! @{ */

#define FLEXIO_SHIFTBUF_SHIFTBUF_MASK            (0xFFFFFFFFU)
#define FLEXIO_SHIFTBUF_SHIFTBUF_SHIFT           (0U)
#define FLEXIO_SHIFTBUF_SHIFTBUF_WIDTH           (32U)
#define FLEXIO_SHIFTBUF_SHIFTBUF(x)              (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTBUF_SHIFTBUF_SHIFT)) & FLEXIO_SHIFTBUF_SHIFTBUF_MASK)
/*! @} */

/*! @name SHIFTBUFBIS - Shifter Buffer N Bit Swapped Register */
/*! @{ */

#define FLEXIO_SHIFTBUFBIS_SHIFTBUFBIS_MASK      (0xFFFFFFFFU)
#define FLEXIO_SHIFTBUFBIS_SHIFTBUFBIS_SHIFT     (0U)
#define FLEXIO_SHIFTBUFBIS_SHIFTBUFBIS_WIDTH     (32U)
#define FLEXIO_SHIFTBUFBIS_SHIFTBUFBIS(x)        (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTBUFBIS_SHIFTBUFBIS_SHIFT)) & FLEXIO_SHIFTBUFBIS_SHIFTBUFBIS_MASK)
/*! @} */

/*! @name SHIFTBUFBYS - Shifter Buffer N Byte Swapped Register */
/*! @{ */

#define FLEXIO_SHIFTBUFBYS_SHIFTBUFBYS_MASK      (0xFFFFFFFFU)
#define FLEXIO_SHIFTBUFBYS_SHIFTBUFBYS_SHIFT     (0U)
#define FLEXIO_SHIFTBUFBYS_SHIFTBUFBYS_WIDTH     (32U)
#define FLEXIO_SHIFTBUFBYS_SHIFTBUFBYS(x)        (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTBUFBYS_SHIFTBUFBYS_SHIFT)) & FLEXIO_SHIFTBUFBYS_SHIFTBUFBYS_MASK)
/*! @} */

/*! @name SHIFTBUFBBS - Shifter Buffer N Bit Byte Swapped Register */
/*! @{ */

#define FLEXIO_SHIFTBUFBBS_SHIFTBUFBBS_MASK      (0xFFFFFFFFU)
#define FLEXIO_SHIFTBUFBBS_SHIFTBUFBBS_SHIFT     (0U)
#define FLEXIO_SHIFTBUFBBS_SHIFTBUFBBS_WIDTH     (32U)
#define FLEXIO_SHIFTBUFBBS_SHIFTBUFBBS(x)        (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTBUFBBS_SHIFTBUFBBS_SHIFT)) & FLEXIO_SHIFTBUFBBS_SHIFTBUFBBS_MASK)
/*! @} */

/*! @name TIMCTL - Timer Control N Register */
/*! @{ */

#define FLEXIO_TIMCTL_TIMOD_MASK                 (0x7U)
#define FLEXIO_TIMCTL_TIMOD_SHIFT                (0U)
#define FLEXIO_TIMCTL_TIMOD_WIDTH                (3U)
#define FLEXIO_TIMCTL_TIMOD(x)                   (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_TIMOD_SHIFT)) & FLEXIO_TIMCTL_TIMOD_MASK)

#define FLEXIO_TIMCTL_ONETIM_MASK                (0x20U)
#define FLEXIO_TIMCTL_ONETIM_SHIFT               (5U)
#define FLEXIO_TIMCTL_ONETIM_WIDTH               (1U)
#define FLEXIO_TIMCTL_ONETIM(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_ONETIM_SHIFT)) & FLEXIO_TIMCTL_ONETIM_MASK)

#define FLEXIO_TIMCTL_PININS_MASK                (0x40U)
#define FLEXIO_TIMCTL_PININS_SHIFT               (6U)
#define FLEXIO_TIMCTL_PININS_WIDTH               (1U)
#define FLEXIO_TIMCTL_PININS(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_PININS_SHIFT)) & FLEXIO_TIMCTL_PININS_MASK)

#define FLEXIO_TIMCTL_PINPOL_MASK                (0x80U)
#define FLEXIO_TIMCTL_PINPOL_SHIFT               (7U)
#define FLEXIO_TIMCTL_PINPOL_WIDTH               (1U)
#define FLEXIO_TIMCTL_PINPOL(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_PINPOL_SHIFT)) & FLEXIO_TIMCTL_PINPOL_MASK)

#define FLEXIO_TIMCTL_PINSEL_MASK                (0x1F00U)
#define FLEXIO_TIMCTL_PINSEL_SHIFT               (8U)
#define FLEXIO_TIMCTL_PINSEL_WIDTH               (5U)
#define FLEXIO_TIMCTL_PINSEL(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_PINSEL_SHIFT)) & FLEXIO_TIMCTL_PINSEL_MASK)

#define FLEXIO_TIMCTL_PINCFG_MASK                (0x30000U)
#define FLEXIO_TIMCTL_PINCFG_SHIFT               (16U)
#define FLEXIO_TIMCTL_PINCFG_WIDTH               (2U)
#define FLEXIO_TIMCTL_PINCFG(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_PINCFG_SHIFT)) & FLEXIO_TIMCTL_PINCFG_MASK)

#define FLEXIO_TIMCTL_TRGSRC_MASK                (0x400000U)
#define FLEXIO_TIMCTL_TRGSRC_SHIFT               (22U)
#define FLEXIO_TIMCTL_TRGSRC_WIDTH               (1U)
#define FLEXIO_TIMCTL_TRGSRC(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_TRGSRC_SHIFT)) & FLEXIO_TIMCTL_TRGSRC_MASK)

#define FLEXIO_TIMCTL_TRGPOL_MASK                (0x800000U)
#define FLEXIO_TIMCTL_TRGPOL_SHIFT               (23U)
#define FLEXIO_TIMCTL_TRGPOL_WIDTH               (1U)
#define FLEXIO_TIMCTL_TRGPOL(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_TRGPOL_SHIFT)) & FLEXIO_TIMCTL_TRGPOL_MASK)

#define FLEXIO_TIMCTL_TRGSEL_MASK                (0x3F000000U)
#define FLEXIO_TIMCTL_TRGSEL_SHIFT               (24U)
#define FLEXIO_TIMCTL_TRGSEL_WIDTH               (6U)
#define FLEXIO_TIMCTL_TRGSEL(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCTL_TRGSEL_SHIFT)) & FLEXIO_TIMCTL_TRGSEL_MASK)
/*! @} */

/*! @name TIMCFG - Timer Configuration N Register */
/*! @{ */

#define FLEXIO_TIMCFG_TSTART_MASK                (0x2U)
#define FLEXIO_TIMCFG_TSTART_SHIFT               (1U)
#define FLEXIO_TIMCFG_TSTART_WIDTH               (1U)
#define FLEXIO_TIMCFG_TSTART(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCFG_TSTART_SHIFT)) & FLEXIO_TIMCFG_TSTART_MASK)

#define FLEXIO_TIMCFG_TSTOP_MASK                 (0x30U)
#define FLEXIO_TIMCFG_TSTOP_SHIFT                (4U)
#define FLEXIO_TIMCFG_TSTOP_WIDTH                (2U)
#define FLEXIO_TIMCFG_TSTOP(x)                   (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCFG_TSTOP_SHIFT)) & FLEXIO_TIMCFG_TSTOP_MASK)

#define FLEXIO_TIMCFG_TIMENA_MASK                (0x700U)
#define FLEXIO_TIMCFG_TIMENA_SHIFT               (8U)
#define FLEXIO_TIMCFG_TIMENA_WIDTH               (3U)
#define FLEXIO_TIMCFG_TIMENA(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCFG_TIMENA_SHIFT)) & FLEXIO_TIMCFG_TIMENA_MASK)

#define FLEXIO_TIMCFG_TIMDIS_MASK                (0x7000U)
#define FLEXIO_TIMCFG_TIMDIS_SHIFT               (12U)
#define FLEXIO_TIMCFG_TIMDIS_WIDTH               (3U)
#define FLEXIO_TIMCFG_TIMDIS(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCFG_TIMDIS_SHIFT)) & FLEXIO_TIMCFG_TIMDIS_MASK)

#define FLEXIO_TIMCFG_TIMRST_MASK                (0x70000U)
#define FLEXIO_TIMCFG_TIMRST_SHIFT               (16U)
#define FLEXIO_TIMCFG_TIMRST_WIDTH               (3U)
#define FLEXIO_TIMCFG_TIMRST(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCFG_TIMRST_SHIFT)) & FLEXIO_TIMCFG_TIMRST_MASK)

#define FLEXIO_TIMCFG_TIMDEC_MASK                (0x700000U)
#define FLEXIO_TIMCFG_TIMDEC_SHIFT               (20U)
#define FLEXIO_TIMCFG_TIMDEC_WIDTH               (3U)
#define FLEXIO_TIMCFG_TIMDEC(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCFG_TIMDEC_SHIFT)) & FLEXIO_TIMCFG_TIMDEC_MASK)

#define FLEXIO_TIMCFG_TIMOUT_MASK                (0x3000000U)
#define FLEXIO_TIMCFG_TIMOUT_SHIFT               (24U)
#define FLEXIO_TIMCFG_TIMOUT_WIDTH               (2U)
#define FLEXIO_TIMCFG_TIMOUT(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCFG_TIMOUT_SHIFT)) & FLEXIO_TIMCFG_TIMOUT_MASK)
/*! @} */

/*! @name TIMCMP - Timer Compare N Register */
/*! @{ */

#define FLEXIO_TIMCMP_CMP_MASK                   (0xFFFFU)
#define FLEXIO_TIMCMP_CMP_SHIFT                  (0U)
#define FLEXIO_TIMCMP_CMP_WIDTH                  (16U)
#define FLEXIO_TIMCMP_CMP(x)                     (((uint32_t)(((uint32_t)(x)) << FLEXIO_TIMCMP_CMP_SHIFT)) & FLEXIO_TIMCMP_CMP_MASK)
/*! @} */

/*! @name SHIFTBUFNBS - Shifter Buffer N Nibble Byte Swapped Register */
/*! @{ */

#define FLEXIO_SHIFTBUFNBS_SHIFTBUFNBS_MASK      (0xFFFFFFFFU)
#define FLEXIO_SHIFTBUFNBS_SHIFTBUFNBS_SHIFT     (0U)
#define FLEXIO_SHIFTBUFNBS_SHIFTBUFNBS_WIDTH     (32U)
#define FLEXIO_SHIFTBUFNBS_SHIFTBUFNBS(x)        (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTBUFNBS_SHIFTBUFNBS_SHIFT)) & FLEXIO_SHIFTBUFNBS_SHIFTBUFNBS_MASK)
/*! @} */

/*! @name SHIFTBUFHWS - Shifter Buffer N Half Word Swapped Register */
/*! @{ */

#define FLEXIO_SHIFTBUFHWS_SHIFTBUFHWS_MASK      (0xFFFFFFFFU)
#define FLEXIO_SHIFTBUFHWS_SHIFTBUFHWS_SHIFT     (0U)
#define FLEXIO_SHIFTBUFHWS_SHIFTBUFHWS_WIDTH     (32U)
#define FLEXIO_SHIFTBUFHWS_SHIFTBUFHWS(x)        (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTBUFHWS_SHIFTBUFHWS_SHIFT)) & FLEXIO_SHIFTBUFHWS_SHIFTBUFHWS_MASK)
/*! @} */

/*! @name SHIFTBUFNIS - Shifter Buffer N Nibble Swapped Register */
/*! @{ */

#define FLEXIO_SHIFTBUFNIS_SHIFTBUFNIS_MASK      (0xFFFFFFFFU)
#define FLEXIO_SHIFTBUFNIS_SHIFTBUFNIS_SHIFT     (0U)
#define FLEXIO_SHIFTBUFNIS_SHIFTBUFNIS_WIDTH     (32U)
#define FLEXIO_SHIFTBUFNIS_SHIFTBUFNIS(x)        (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTBUFNIS_SHIFTBUFNIS_SHIFT)) & FLEXIO_SHIFTBUFNIS_SHIFTBUFNIS_MASK)
/*! @} */

/*! @name SHIFTBUFOES - Shifter Buffer N Odd Even Swapped Register */
/*! @{ */

#define FLEXIO_SHIFTBUFOES_SHIFTBUFOES_MASK      (0xFFFFFFFFU)
#define FLEXIO_SHIFTBUFOES_SHIFTBUFOES_SHIFT     (0U)
#define FLEXIO_SHIFTBUFOES_SHIFTBUFOES_WIDTH     (32U)
#define FLEXIO_SHIFTBUFOES_SHIFTBUFOES(x)        (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTBUFOES_SHIFTBUFOES_SHIFT)) & FLEXIO_SHIFTBUFOES_SHIFTBUFOES_MASK)
/*! @} */

/*! @name SHIFTBUFEOS - Shifter Buffer N Even Odd Swapped Register */
/*! @{ */

#define FLEXIO_SHIFTBUFEOS_SHIFTBUFEOS_MASK      (0xFFFFFFFFU)
#define FLEXIO_SHIFTBUFEOS_SHIFTBUFEOS_SHIFT     (0U)
#define FLEXIO_SHIFTBUFEOS_SHIFTBUFEOS_WIDTH     (32U)
#define FLEXIO_SHIFTBUFEOS_SHIFTBUFEOS(x)        (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTBUFEOS_SHIFTBUFEOS_SHIFT)) & FLEXIO_SHIFTBUFEOS_SHIFTBUFEOS_MASK)
/*! @} */

/*! @name SHIFTBUFHBS - Shifter Buffer N Halfword Byte Swapped Register */
/*! @{ */

#define FLEXIO_SHIFTBUFHBS_SHIFTBUFHBS_MASK      (0xFFFFFFFFU)
#define FLEXIO_SHIFTBUFHBS_SHIFTBUFHBS_SHIFT     (0U)
#define FLEXIO_SHIFTBUFHBS_SHIFTBUFHBS_WIDTH     (32U)
#define FLEXIO_SHIFTBUFHBS_SHIFTBUFHBS(x)        (((uint32_t)(((uint32_t)(x)) << FLEXIO_SHIFTBUFHBS_SHIFTBUFHBS_SHIFT)) & FLEXIO_SHIFTBUFHBS_SHIFTBUFHBS_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group FLEXIO_Register_Masks */

/*!
 * @}
 */ /* end of group FLEXIO_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_FLEXIO_H_) */
