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
 * @file S32K344_SDA_AP.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_SDA_AP
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
#if !defined(S32K344_SDA_AP_H_)  /* Check if memory map has not been already included */
#define S32K344_SDA_AP_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- SDA_AP Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SDA_AP_Peripheral_Access_Layer SDA_AP Peripheral Access Layer
 * @{
 */

/** SDA_AP - Size of Registers Arrays */
#define SDA_AP_KEYCHAL_COUNT                      8u
#define SDA_AP_KEYRESP_COUNT                      8u

/** SDA_AP - Register Layout Typedef */
typedef struct {
  __I  uint32_t AUTHSTTS;                          /**< Authentication Status, offset: 0x0 */
  __IO uint32_t AUTHCTL;                           /**< Authentication Control, offset: 0x4 */
  uint8_t RESERVED_0[8];
  __I  uint32_t KEYCHAL[SDA_AP_KEYCHAL_COUNT];     /**< Key Challenge, array offset: 0x10, array step: 0x4 */
  uint8_t RESERVED_1[16];
  __IO uint32_t KEYRESP[SDA_AP_KEYRESP_COUNT];     /**< Key Response, array offset: 0x40, array step: 0x4 */
  uint8_t RESERVED_2[16];
  __I  uint32_t UID0;                              /**< User Identification 0, offset: 0x70 */
  __I  uint32_t UID1;                              /**< User Identification 1, offset: 0x74 */
  uint8_t RESERVED_3[8];
  __IO uint32_t DBGENCTRL;                         /**< Debug Enable Control, offset: 0x80 */
  uint8_t RESERVED_4[12];
  __IO uint32_t SDAAPRSTCTRL;                      /**< Reset Control, offset: 0x90 */
  uint8_t RESERVED_5[12];
  __I  uint32_t SDAAPGENSTATUS0;                   /**< SDA_AP Generic Status, offset: 0xA0 */
  __IO uint32_t SDAAPGENCTRL0;                     /**< Generic Control 0, offset: 0xA4 */
  uint8_t RESERVED_6[8];
  __I  uint32_t SDAAPGENSTATUS1;                   /**< SDA_AP Generic Status, offset: 0xB0 */
  uint8_t RESERVED_7[12];
  __I  uint32_t SDAAPGENSTATUS2;                   /**< SDA_AP Generic Status, offset: 0xC0 */
  uint8_t RESERVED_8[12];
  __I  uint32_t SDAAPGENSTATUS3;                   /**< SDA_AP Generic Status, offset: 0xD0 */
  uint8_t RESERVED_9[12];
  __I  uint32_t SDAAPGENSTATUS4;                   /**< SDA_AP Generic Status, offset: 0xE0 */
  uint8_t RESERVED_10[24];
  __I  uint32_t ID;                                /**< Identity, offset: 0xFC */
} SDA_AP_Type, *SDA_AP_MemMapPtr;

/** Number of instances of the SDA_AP module. */
#define SDA_AP_INSTANCE_COUNT                    (1u)

/* SDA_AP - Peripheral instance base addresses */
/** Peripheral SDA_AP base address */
#define IP_SDA_AP_BASE                           (0x40254700u)
/** Peripheral SDA_AP base pointer */
#define IP_SDA_AP                                ((SDA_AP_Type *)IP_SDA_AP_BASE)
/** Array initializer of SDA_AP peripheral base addresses */
#define IP_SDA_AP_BASE_ADDRS                     { IP_SDA_AP_BASE }
/** Array initializer of SDA_AP peripheral base pointers */
#define IP_SDA_AP_BASE_PTRS                      { IP_SDA_AP }

/* ----------------------------------------------------------------------------
   -- SDA_AP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SDA_AP_Register_Masks SDA_AP Register Masks
 * @{
 */

/*! @name AUTHSTTS - Authentication Status */
/*! @{ */

#define SDA_AP_AUTHSTTS_CHALRDY_MASK             (0x1U)
#define SDA_AP_AUTHSTTS_CHALRDY_SHIFT            (0U)
#define SDA_AP_AUTHSTTS_CHALRDY_WIDTH            (1U)
#define SDA_AP_AUTHSTTS_CHALRDY(x)               (((uint32_t)(((uint32_t)(x)) << SDA_AP_AUTHSTTS_CHALRDY_SHIFT)) & SDA_AP_AUTHSTTS_CHALRDY_MASK)

#define SDA_AP_AUTHSTTS_UIDSTATUS_MASK           (0x4U)
#define SDA_AP_AUTHSTTS_UIDSTATUS_SHIFT          (2U)
#define SDA_AP_AUTHSTTS_UIDSTATUS_WIDTH          (1U)
#define SDA_AP_AUTHSTTS_UIDSTATUS(x)             (((uint32_t)(((uint32_t)(x)) << SDA_AP_AUTHSTTS_UIDSTATUS_SHIFT)) & SDA_AP_AUTHSTTS_UIDSTATUS_MASK)

#define SDA_AP_AUTHSTTS_SWAPPDBG_MASK            (0x8U)
#define SDA_AP_AUTHSTTS_SWAPPDBG_SHIFT           (3U)
#define SDA_AP_AUTHSTTS_SWAPPDBG_WIDTH           (1U)
#define SDA_AP_AUTHSTTS_SWAPPDBG(x)              (((uint32_t)(((uint32_t)(x)) << SDA_AP_AUTHSTTS_SWAPPDBG_SHIFT)) & SDA_AP_AUTHSTTS_SWAPPDBG_MASK)

#define SDA_AP_AUTHSTTS_APPDBGEN_MASK            (0x40000000U)
#define SDA_AP_AUTHSTTS_APPDBGEN_SHIFT           (30U)
#define SDA_AP_AUTHSTTS_APPDBGEN_WIDTH           (1U)
#define SDA_AP_AUTHSTTS_APPDBGEN(x)              (((uint32_t)(((uint32_t)(x)) << SDA_AP_AUTHSTTS_APPDBGEN_SHIFT)) & SDA_AP_AUTHSTTS_APPDBGEN_MASK)
/*! @} */

/*! @name AUTHCTL - Authentication Control */
/*! @{ */

#define SDA_AP_AUTHCTL_HSEAUTHREQ_MASK           (0x1U)
#define SDA_AP_AUTHCTL_HSEAUTHREQ_SHIFT          (0U)
#define SDA_AP_AUTHCTL_HSEAUTHREQ_WIDTH          (1U)
#define SDA_AP_AUTHCTL_HSEAUTHREQ(x)             (((uint32_t)(((uint32_t)(x)) << SDA_AP_AUTHCTL_HSEAUTHREQ_SHIFT)) & SDA_AP_AUTHCTL_HSEAUTHREQ_MASK)

#define SDA_AP_AUTHCTL_HSENEWDATACTL_MASK        (0x2U)
#define SDA_AP_AUTHCTL_HSENEWDATACTL_SHIFT       (1U)
#define SDA_AP_AUTHCTL_HSENEWDATACTL_WIDTH       (1U)
#define SDA_AP_AUTHCTL_HSENEWDATACTL(x)          (((uint32_t)(((uint32_t)(x)) << SDA_AP_AUTHCTL_HSENEWDATACTL_SHIFT)) & SDA_AP_AUTHCTL_HSENEWDATACTL_MASK)
/*! @} */

/*! @name KEYCHAL - Key Challenge */
/*! @{ */

#define SDA_AP_KEYCHAL_KEYCHAL_MASK              (0xFFFFFFFFU)
#define SDA_AP_KEYCHAL_KEYCHAL_SHIFT             (0U)
#define SDA_AP_KEYCHAL_KEYCHAL_WIDTH             (32U)
#define SDA_AP_KEYCHAL_KEYCHAL(x)                (((uint32_t)(((uint32_t)(x)) << SDA_AP_KEYCHAL_KEYCHAL_SHIFT)) & SDA_AP_KEYCHAL_KEYCHAL_MASK)
/*! @} */

/*! @name KEYRESP - Key Response */
/*! @{ */

#define SDA_AP_KEYRESP_KEYRESP_MASK              (0xFFFFFFFFU)
#define SDA_AP_KEYRESP_KEYRESP_SHIFT             (0U)
#define SDA_AP_KEYRESP_KEYRESP_WIDTH             (32U)
#define SDA_AP_KEYRESP_KEYRESP(x)                (((uint32_t)(((uint32_t)(x)) << SDA_AP_KEYRESP_KEYRESP_SHIFT)) & SDA_AP_KEYRESP_KEYRESP_MASK)
/*! @} */

/*! @name UID0 - User Identification 0 */
/*! @{ */

#define SDA_AP_UID0_UID0_MASK                    (0xFFFFFFFFU)
#define SDA_AP_UID0_UID0_SHIFT                   (0U)
#define SDA_AP_UID0_UID0_WIDTH                   (32U)
#define SDA_AP_UID0_UID0(x)                      (((uint32_t)(((uint32_t)(x)) << SDA_AP_UID0_UID0_SHIFT)) & SDA_AP_UID0_UID0_MASK)
/*! @} */

/*! @name UID1 - User Identification 1 */
/*! @{ */

#define SDA_AP_UID1_UID1_MASK                    (0xFFFFFFFFU)
#define SDA_AP_UID1_UID1_SHIFT                   (0U)
#define SDA_AP_UID1_UID1_WIDTH                   (32U)
#define SDA_AP_UID1_UID1(x)                      (((uint32_t)(((uint32_t)(x)) << SDA_AP_UID1_UID1_SHIFT)) & SDA_AP_UID1_UID1_MASK)
/*! @} */

/*! @name DBGENCTRL - Debug Enable Control */
/*! @{ */

#define SDA_AP_DBGENCTRL_GDBGEN_MASK             (0x10U)
#define SDA_AP_DBGENCTRL_GDBGEN_SHIFT            (4U)
#define SDA_AP_DBGENCTRL_GDBGEN_WIDTH            (1U)
#define SDA_AP_DBGENCTRL_GDBGEN(x)               (((uint32_t)(((uint32_t)(x)) << SDA_AP_DBGENCTRL_GDBGEN_SHIFT)) & SDA_AP_DBGENCTRL_GDBGEN_MASK)

#define SDA_AP_DBGENCTRL_GNIDEN_MASK             (0x20U)
#define SDA_AP_DBGENCTRL_GNIDEN_SHIFT            (5U)
#define SDA_AP_DBGENCTRL_GNIDEN_WIDTH            (1U)
#define SDA_AP_DBGENCTRL_GNIDEN(x)               (((uint32_t)(((uint32_t)(x)) << SDA_AP_DBGENCTRL_GNIDEN_SHIFT)) & SDA_AP_DBGENCTRL_GNIDEN_MASK)

#define SDA_AP_DBGENCTRL_GSPIDEN_MASK            (0x40U)
#define SDA_AP_DBGENCTRL_GSPIDEN_SHIFT           (6U)
#define SDA_AP_DBGENCTRL_GSPIDEN_WIDTH           (1U)
#define SDA_AP_DBGENCTRL_GSPIDEN(x)              (((uint32_t)(((uint32_t)(x)) << SDA_AP_DBGENCTRL_GSPIDEN_SHIFT)) & SDA_AP_DBGENCTRL_GSPIDEN_MASK)

#define SDA_AP_DBGENCTRL_GSPNIDEN_MASK           (0x80U)
#define SDA_AP_DBGENCTRL_GSPNIDEN_SHIFT          (7U)
#define SDA_AP_DBGENCTRL_GSPNIDEN_WIDTH          (1U)
#define SDA_AP_DBGENCTRL_GSPNIDEN(x)             (((uint32_t)(((uint32_t)(x)) << SDA_AP_DBGENCTRL_GSPNIDEN_SHIFT)) & SDA_AP_DBGENCTRL_GSPNIDEN_MASK)

#define SDA_AP_DBGENCTRL_CDBGEN_MASK             (0x10000000U)
#define SDA_AP_DBGENCTRL_CDBGEN_SHIFT            (28U)
#define SDA_AP_DBGENCTRL_CDBGEN_WIDTH            (1U)
#define SDA_AP_DBGENCTRL_CDBGEN(x)               (((uint32_t)(((uint32_t)(x)) << SDA_AP_DBGENCTRL_CDBGEN_SHIFT)) & SDA_AP_DBGENCTRL_CDBGEN_MASK)

#define SDA_AP_DBGENCTRL_CNIDEN_MASK             (0x20000000U)
#define SDA_AP_DBGENCTRL_CNIDEN_SHIFT            (29U)
#define SDA_AP_DBGENCTRL_CNIDEN_WIDTH            (1U)
#define SDA_AP_DBGENCTRL_CNIDEN(x)               (((uint32_t)(((uint32_t)(x)) << SDA_AP_DBGENCTRL_CNIDEN_SHIFT)) & SDA_AP_DBGENCTRL_CNIDEN_MASK)
/*! @} */

/*! @name SDAAPRSTCTRL - Reset Control */
/*! @{ */

#define SDA_AP_SDAAPRSTCTRL_RSTRELTLCM70_MASK    (0x2000000U)
#define SDA_AP_SDAAPRSTCTRL_RSTRELTLCM70_SHIFT   (25U)
#define SDA_AP_SDAAPRSTCTRL_RSTRELTLCM70_WIDTH   (1U)
#define SDA_AP_SDAAPRSTCTRL_RSTRELTLCM70(x)      (((uint32_t)(((uint32_t)(x)) << SDA_AP_SDAAPRSTCTRL_RSTRELTLCM70_SHIFT)) & SDA_AP_SDAAPRSTCTRL_RSTRELTLCM70_MASK)
/*! @} */

/*! @name SDAAPGENSTATUS0 - SDA_AP Generic Status */
/*! @{ */

#define SDA_AP_SDAAPGENSTATUS0_SDAAPGENSTATUS_MASK (0xFFFFFFFFU)
#define SDA_AP_SDAAPGENSTATUS0_SDAAPGENSTATUS_SHIFT (0U)
#define SDA_AP_SDAAPGENSTATUS0_SDAAPGENSTATUS_WIDTH (32U)
#define SDA_AP_SDAAPGENSTATUS0_SDAAPGENSTATUS(x) (((uint32_t)(((uint32_t)(x)) << SDA_AP_SDAAPGENSTATUS0_SDAAPGENSTATUS_SHIFT)) & SDA_AP_SDAAPGENSTATUS0_SDAAPGENSTATUS_MASK)
/*! @} */

/*! @name SDAAPGENCTRL0 - Generic Control 0 */
/*! @{ */

#define SDA_AP_SDAAPGENCTRL0_JTAG_CR_EN_MASK     (0x1U)
#define SDA_AP_SDAAPGENCTRL0_JTAG_CR_EN_SHIFT    (0U)
#define SDA_AP_SDAAPGENCTRL0_JTAG_CR_EN_WIDTH    (1U)
#define SDA_AP_SDAAPGENCTRL0_JTAG_CR_EN(x)       (((uint32_t)(((uint32_t)(x)) << SDA_AP_SDAAPGENCTRL0_JTAG_CR_EN_SHIFT)) & SDA_AP_SDAAPGENCTRL0_JTAG_CR_EN_MASK)
/*! @} */

/*! @name SDAAPGENSTATUS1 - SDA_AP Generic Status */
/*! @{ */

#define SDA_AP_SDAAPGENSTATUS1_SDAAPGENSTATUS_MASK (0xFFFFFFFFU)
#define SDA_AP_SDAAPGENSTATUS1_SDAAPGENSTATUS_SHIFT (0U)
#define SDA_AP_SDAAPGENSTATUS1_SDAAPGENSTATUS_WIDTH (32U)
#define SDA_AP_SDAAPGENSTATUS1_SDAAPGENSTATUS(x) (((uint32_t)(((uint32_t)(x)) << SDA_AP_SDAAPGENSTATUS1_SDAAPGENSTATUS_SHIFT)) & SDA_AP_SDAAPGENSTATUS1_SDAAPGENSTATUS_MASK)
/*! @} */

/*! @name SDAAPGENSTATUS2 - SDA_AP Generic Status */
/*! @{ */

#define SDA_AP_SDAAPGENSTATUS2_SDAAPGENSTATUS_MASK (0xFFFFFFFFU)
#define SDA_AP_SDAAPGENSTATUS2_SDAAPGENSTATUS_SHIFT (0U)
#define SDA_AP_SDAAPGENSTATUS2_SDAAPGENSTATUS_WIDTH (32U)
#define SDA_AP_SDAAPGENSTATUS2_SDAAPGENSTATUS(x) (((uint32_t)(((uint32_t)(x)) << SDA_AP_SDAAPGENSTATUS2_SDAAPGENSTATUS_SHIFT)) & SDA_AP_SDAAPGENSTATUS2_SDAAPGENSTATUS_MASK)
/*! @} */

/*! @name SDAAPGENSTATUS3 - SDA_AP Generic Status */
/*! @{ */

#define SDA_AP_SDAAPGENSTATUS3_SDAAPGENSTATUS_MASK (0xFFFFFFFFU)
#define SDA_AP_SDAAPGENSTATUS3_SDAAPGENSTATUS_SHIFT (0U)
#define SDA_AP_SDAAPGENSTATUS3_SDAAPGENSTATUS_WIDTH (32U)
#define SDA_AP_SDAAPGENSTATUS3_SDAAPGENSTATUS(x) (((uint32_t)(((uint32_t)(x)) << SDA_AP_SDAAPGENSTATUS3_SDAAPGENSTATUS_SHIFT)) & SDA_AP_SDAAPGENSTATUS3_SDAAPGENSTATUS_MASK)
/*! @} */

/*! @name SDAAPGENSTATUS4 - SDA_AP Generic Status */
/*! @{ */

#define SDA_AP_SDAAPGENSTATUS4_SDAAPGENSTATUS_MASK (0xFFFFFFFFU)
#define SDA_AP_SDAAPGENSTATUS4_SDAAPGENSTATUS_SHIFT (0U)
#define SDA_AP_SDAAPGENSTATUS4_SDAAPGENSTATUS_WIDTH (32U)
#define SDA_AP_SDAAPGENSTATUS4_SDAAPGENSTATUS(x) (((uint32_t)(((uint32_t)(x)) << SDA_AP_SDAAPGENSTATUS4_SDAAPGENSTATUS_SHIFT)) & SDA_AP_SDAAPGENSTATUS4_SDAAPGENSTATUS_MASK)
/*! @} */

/*! @name ID - Identity */
/*! @{ */

#define SDA_AP_ID_ID_MASK                        (0xFFFFFFFFU)
#define SDA_AP_ID_ID_SHIFT                       (0U)
#define SDA_AP_ID_ID_WIDTH                       (32U)
#define SDA_AP_ID_ID(x)                          (((uint32_t)(((uint32_t)(x)) << SDA_AP_ID_ID_SHIFT)) & SDA_AP_ID_ID_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group SDA_AP_Register_Masks */

/*!
 * @}
 */ /* end of group SDA_AP_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_SDA_AP_H_) */
