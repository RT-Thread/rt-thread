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
**         CMSIS Peripheral Access Layer for USB
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
 * @file PERI_USB.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for USB
 *
 * CMSIS Peripheral Access Layer for USB
 */

#if !defined(PERI_USB_H_)
#define PERI_USB_H_                              /**< Symbol preventing repeated inclusion */

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
   -- USB Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USB_Peripheral_Access_Layer USB Peripheral Access Layer
 * @{
 */

/** USB - Size of Registers Arrays */
#define USB_ENDPTCTRL_COUNT                       7u

/** USB - Register Layout Typedef */
typedef struct {
  __I  uint32_t ID;                                /**< Identification register, offset: 0x0 */
  __I  uint32_t HWGENERAL;                         /**< Hardware General, offset: 0x4 */
  __I  uint32_t HWHOST;                            /**< Host Hardware Parameters, offset: 0x8 */
  __I  uint32_t HWDEVICE;                          /**< Device Hardware Parameters, offset: 0xC */
  __I  uint32_t HWTXBUF;                           /**< TX Buffer Hardware Parameters, offset: 0x10 */
  __I  uint32_t HWRXBUF;                           /**< RX Buffer Hardware Parameters, offset: 0x14 */
       uint8_t RESERVED_0[104];
  __IO uint32_t GPTIMER0LD;                        /**< General Purpose Timer #0 Load, offset: 0x80 */
  __IO uint32_t GPTIMER0CTRL;                      /**< General Purpose Timer #0 Controller, offset: 0x84 */
  __IO uint32_t GPTIMER1LD;                        /**< General Purpose Timer #1 Load, offset: 0x88 */
  __IO uint32_t GPTIMER1CTRL;                      /**< General Purpose Timer #1 Controller, offset: 0x8C */
  __IO uint32_t SBUSCFG;                           /**< System Bus Config, offset: 0x90 */
       uint8_t RESERVED_1[108];
  __I  uint8_t CAPLENGTH;                          /**< Capability Registers Length, offset: 0x100 */
       uint8_t RESERVED_2[1];
  __I  uint16_t HCIVERSION;                        /**< Host Controller Interface Version, offset: 0x102 */
  __I  uint32_t HCSPARAMS;                         /**< Host Controller Structural Parameters, offset: 0x104 */
  __I  uint32_t HCCPARAMS;                         /**< Host Controller Capability Parameters, offset: 0x108 */
       uint8_t RESERVED_3[20];
  __I  uint16_t DCIVERSION;                        /**< Device Controller Interface Version, offset: 0x120 */
       uint8_t RESERVED_4[2];
  __I  uint32_t DCCPARAMS;                         /**< Device Controller Capability Parameters, offset: 0x124 */
       uint8_t RESERVED_5[24];
  __IO uint32_t USBCMD;                            /**< USB Command Register, offset: 0x140 */
  __IO uint32_t USBSTS;                            /**< USB Status Register, offset: 0x144 */
  __IO uint32_t USBINTR;                           /**< Interrupt Enable Register, offset: 0x148 */
  __IO uint32_t FRINDEX;                           /**< USB Frame Index, offset: 0x14C */
       uint8_t RESERVED_6[4];
  union {                                          /* offset: 0x154 */
    __IO uint32_t DEVICEADDR;                        /**< Device Address, offset: 0x154 */
    __IO uint32_t PERIODICLISTBASE;                  /**< Frame List Base Address, offset: 0x154 */
  };
  union {                                          /* offset: 0x158 */
    __IO uint32_t ASYNCLISTADDR;                     /**< Next Asynch. Address, offset: 0x158 */
    __IO uint32_t ENDPTLISTADDR;                     /**< Endpoint List Address, offset: 0x158 */
  };
       uint8_t RESERVED_7[4];
  __IO uint32_t BURSTSIZE;                         /**< Programmable Burst Size, offset: 0x160 */
  __IO uint32_t TXFILLTUNING;                      /**< TX FIFO Fill Tuning, offset: 0x164 */
       uint8_t RESERVED_8[16];
  __IO uint32_t ENDPTNAK;                          /**< Endpoint NAK, offset: 0x178 */
  __IO uint32_t ENDPTNAKEN;                        /**< Endpoint NAK Enable, offset: 0x17C */
  __I  uint32_t CONFIGFLAG;                        /**< Configure Flag Register, offset: 0x180 */
  __IO uint32_t PORTSC1;                           /**< Port Status & Control, offset: 0x184 */
       uint8_t RESERVED_9[28];
  __IO uint32_t OTGSC;                             /**< On-The-Go Status & control, offset: 0x1A4 */
  __IO uint32_t USBMODE;                           /**< USB Device Mode, offset: 0x1A8 */
  __IO uint32_t ENDPTSETUPSTAT;                    /**< Endpoint Setup Status, offset: 0x1AC */
  __IO uint32_t ENDPTPRIME;                        /**< Endpoint Prime, offset: 0x1B0 */
  __IO uint32_t ENDPTFLUSH;                        /**< Endpoint Flush, offset: 0x1B4 */
  __I  uint32_t ENDPTSTAT;                         /**< Endpoint Status, offset: 0x1B8 */
  __IO uint32_t ENDPTCOMPLETE;                     /**< Endpoint Complete, offset: 0x1BC */
  __IO uint32_t ENDPTCTRL0;                        /**< Endpoint Control0, offset: 0x1C0 */
  __IO uint32_t ENDPTCTRL[USB_ENDPTCTRL_COUNT];    /**< Endpoint Control 1..Endpoint Control 7, array offset: 0x1C4, array step: 0x4 */
} USB_Type;

/* ----------------------------------------------------------------------------
   -- USB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USB_Register_Masks USB Register Masks
 * @{
 */

/*! @name ID - Identification register */
/*! @{ */

#define USB_ID_ID_MASK                           (0x3FU)
#define USB_ID_ID_SHIFT                          (0U)
/*! ID - ID */
#define USB_ID_ID(x)                             (((uint32_t)(((uint32_t)(x)) << USB_ID_ID_SHIFT)) & USB_ID_ID_MASK)

#define USB_ID_NID_MASK                          (0x3F00U)
#define USB_ID_NID_SHIFT                         (8U)
/*! NID - NID */
#define USB_ID_NID(x)                            (((uint32_t)(((uint32_t)(x)) << USB_ID_NID_SHIFT)) & USB_ID_NID_MASK)

#define USB_ID_REVISION_MASK                     (0xFF0000U)
#define USB_ID_REVISION_SHIFT                    (16U)
/*! REVISION - REVISION */
#define USB_ID_REVISION(x)                       (((uint32_t)(((uint32_t)(x)) << USB_ID_REVISION_SHIFT)) & USB_ID_REVISION_MASK)
/*! @} */

/*! @name HWGENERAL - Hardware General */
/*! @{ */

#define USB_HWGENERAL_PHYW_MASK                  (0x30U)
#define USB_HWGENERAL_PHYW_SHIFT                 (4U)
/*! PHYW - PHYW
 *  0b00..8 bit wide data bus (Software non-programmable)
 *  0b01..16 bit wide data bus (Software non-programmable)
 *  0b10..Reset to 8 bit wide data bus (Software programmable)
 *  0b11..Reset to 16 bit wide data bus (Software programmable)
 */
#define USB_HWGENERAL_PHYW(x)                    (((uint32_t)(((uint32_t)(x)) << USB_HWGENERAL_PHYW_SHIFT)) & USB_HWGENERAL_PHYW_MASK)

#define USB_HWGENERAL_PHYM_MASK                  (0x1C0U)
#define USB_HWGENERAL_PHYM_SHIFT                 (6U)
/*! PHYM - PHYM
 *  0b000..UTMI/UMTI+
 *  0b001..ULPI DDR
 *  0b010..ULPI
 *  0b011..Serial Only
 *  0b100..Software programmable - reset to UTMI/UTMI+
 *  0b101..Software programmable - reset to ULPI DDR
 *  0b110..Software programmable - reset to ULPI
 *  0b111..Software programmable - reset to Serial
 */
#define USB_HWGENERAL_PHYM(x)                    (((uint32_t)(((uint32_t)(x)) << USB_HWGENERAL_PHYM_SHIFT)) & USB_HWGENERAL_PHYM_MASK)

#define USB_HWGENERAL_SM_MASK                    (0x600U)
#define USB_HWGENERAL_SM_SHIFT                   (9U)
/*! SM - SM
 *  0b00..No Serial Engine, always use parallel signalling.
 *  0b01..Serial Engine present, always use serial signalling for FS/LS.
 *  0b10..Software programmable - Reset to use parallel signalling for FS/LS
 *  0b11..Software programmable - Reset to use serial signalling for FS/LS
 */
#define USB_HWGENERAL_SM(x)                      (((uint32_t)(((uint32_t)(x)) << USB_HWGENERAL_SM_SHIFT)) & USB_HWGENERAL_SM_MASK)
/*! @} */

/*! @name HWHOST - Host Hardware Parameters */
/*! @{ */

#define USB_HWHOST_HC_MASK                       (0x1U)
#define USB_HWHOST_HC_SHIFT                      (0U)
/*! HC - HC
 *  0b0..Not supported
 *  0b1..Supported
 */
#define USB_HWHOST_HC(x)                         (((uint32_t)(((uint32_t)(x)) << USB_HWHOST_HC_SHIFT)) & USB_HWHOST_HC_MASK)

#define USB_HWHOST_NPORT_MASK                    (0xEU)
#define USB_HWHOST_NPORT_SHIFT                   (1U)
/*! NPORT - NPORT */
#define USB_HWHOST_NPORT(x)                      (((uint32_t)(((uint32_t)(x)) << USB_HWHOST_NPORT_SHIFT)) & USB_HWHOST_NPORT_MASK)
/*! @} */

/*! @name HWDEVICE - Device Hardware Parameters */
/*! @{ */

#define USB_HWDEVICE_DC_MASK                     (0x1U)
#define USB_HWDEVICE_DC_SHIFT                    (0U)
/*! DC - DC
 *  0b0..Not supported
 *  0b1..Supported
 */
#define USB_HWDEVICE_DC(x)                       (((uint32_t)(((uint32_t)(x)) << USB_HWDEVICE_DC_SHIFT)) & USB_HWDEVICE_DC_MASK)

#define USB_HWDEVICE_DEVEP_MASK                  (0x3EU)
#define USB_HWDEVICE_DEVEP_SHIFT                 (1U)
/*! DEVEP - DEVEP */
#define USB_HWDEVICE_DEVEP(x)                    (((uint32_t)(((uint32_t)(x)) << USB_HWDEVICE_DEVEP_SHIFT)) & USB_HWDEVICE_DEVEP_MASK)
/*! @} */

/*! @name HWTXBUF - TX Buffer Hardware Parameters */
/*! @{ */

#define USB_HWTXBUF_TXBURST_MASK                 (0xFFU)
#define USB_HWTXBUF_TXBURST_SHIFT                (0U)
/*! TXBURST - TXBURST */
#define USB_HWTXBUF_TXBURST(x)                   (((uint32_t)(((uint32_t)(x)) << USB_HWTXBUF_TXBURST_SHIFT)) & USB_HWTXBUF_TXBURST_MASK)

#define USB_HWTXBUF_TXCHANADD_MASK               (0xFF0000U)
#define USB_HWTXBUF_TXCHANADD_SHIFT              (16U)
/*! TXCHANADD - TXCHANADD */
#define USB_HWTXBUF_TXCHANADD(x)                 (((uint32_t)(((uint32_t)(x)) << USB_HWTXBUF_TXCHANADD_SHIFT)) & USB_HWTXBUF_TXCHANADD_MASK)
/*! @} */

/*! @name HWRXBUF - RX Buffer Hardware Parameters */
/*! @{ */

#define USB_HWRXBUF_RXBURST_MASK                 (0xFFU)
#define USB_HWRXBUF_RXBURST_SHIFT                (0U)
/*! RXBURST - RXBURST */
#define USB_HWRXBUF_RXBURST(x)                   (((uint32_t)(((uint32_t)(x)) << USB_HWRXBUF_RXBURST_SHIFT)) & USB_HWRXBUF_RXBURST_MASK)

#define USB_HWRXBUF_RXADD_MASK                   (0xFF00U)
#define USB_HWRXBUF_RXADD_SHIFT                  (8U)
/*! RXADD - RXADD */
#define USB_HWRXBUF_RXADD(x)                     (((uint32_t)(((uint32_t)(x)) << USB_HWRXBUF_RXADD_SHIFT)) & USB_HWRXBUF_RXADD_MASK)
/*! @} */

/*! @name GPTIMER0LD - General Purpose Timer #0 Load */
/*! @{ */

#define USB_GPTIMER0LD_GPTLD_MASK                (0xFFFFFFU)
#define USB_GPTIMER0LD_GPTLD_SHIFT               (0U)
/*! GPTLD - GPTLD */
#define USB_GPTIMER0LD_GPTLD(x)                  (((uint32_t)(((uint32_t)(x)) << USB_GPTIMER0LD_GPTLD_SHIFT)) & USB_GPTIMER0LD_GPTLD_MASK)
/*! @} */

/*! @name GPTIMER0CTRL - General Purpose Timer #0 Controller */
/*! @{ */

#define USB_GPTIMER0CTRL_GPTCNT_MASK             (0xFFFFFFU)
#define USB_GPTIMER0CTRL_GPTCNT_SHIFT            (0U)
/*! GPTCNT - GPTCNT */
#define USB_GPTIMER0CTRL_GPTCNT(x)               (((uint32_t)(((uint32_t)(x)) << USB_GPTIMER0CTRL_GPTCNT_SHIFT)) & USB_GPTIMER0CTRL_GPTCNT_MASK)

#define USB_GPTIMER0CTRL_GPTMODE_MASK            (0x1000000U)
#define USB_GPTIMER0CTRL_GPTMODE_SHIFT           (24U)
/*! GPTMODE - GPTMODE
 *  0b0..One Shot Mode
 *  0b1..Repeat Mode
 */
#define USB_GPTIMER0CTRL_GPTMODE(x)              (((uint32_t)(((uint32_t)(x)) << USB_GPTIMER0CTRL_GPTMODE_SHIFT)) & USB_GPTIMER0CTRL_GPTMODE_MASK)

#define USB_GPTIMER0CTRL_GPTRST_MASK             (0x40000000U)
#define USB_GPTIMER0CTRL_GPTRST_SHIFT            (30U)
/*! GPTRST - GPTRST
 *  0b0..No action
 *  0b1..Load counter value from GPTLD bits in n_GPTIMER0LD
 */
#define USB_GPTIMER0CTRL_GPTRST(x)               (((uint32_t)(((uint32_t)(x)) << USB_GPTIMER0CTRL_GPTRST_SHIFT)) & USB_GPTIMER0CTRL_GPTRST_MASK)

#define USB_GPTIMER0CTRL_GPTRUN_MASK             (0x80000000U)
#define USB_GPTIMER0CTRL_GPTRUN_SHIFT            (31U)
/*! GPTRUN - GPTRUN
 *  0b0..Stop counting
 *  0b1..Run
 */
#define USB_GPTIMER0CTRL_GPTRUN(x)               (((uint32_t)(((uint32_t)(x)) << USB_GPTIMER0CTRL_GPTRUN_SHIFT)) & USB_GPTIMER0CTRL_GPTRUN_MASK)
/*! @} */

/*! @name GPTIMER1LD - General Purpose Timer #1 Load */
/*! @{ */

#define USB_GPTIMER1LD_GPTLD_MASK                (0xFFFFFFU)
#define USB_GPTIMER1LD_GPTLD_SHIFT               (0U)
/*! GPTLD - GPTLD */
#define USB_GPTIMER1LD_GPTLD(x)                  (((uint32_t)(((uint32_t)(x)) << USB_GPTIMER1LD_GPTLD_SHIFT)) & USB_GPTIMER1LD_GPTLD_MASK)
/*! @} */

/*! @name GPTIMER1CTRL - General Purpose Timer #1 Controller */
/*! @{ */

#define USB_GPTIMER1CTRL_GPTCNT_MASK             (0xFFFFFFU)
#define USB_GPTIMER1CTRL_GPTCNT_SHIFT            (0U)
/*! GPTCNT - GPTCNT */
#define USB_GPTIMER1CTRL_GPTCNT(x)               (((uint32_t)(((uint32_t)(x)) << USB_GPTIMER1CTRL_GPTCNT_SHIFT)) & USB_GPTIMER1CTRL_GPTCNT_MASK)

#define USB_GPTIMER1CTRL_GPTMODE_MASK            (0x1000000U)
#define USB_GPTIMER1CTRL_GPTMODE_SHIFT           (24U)
/*! GPTMODE - GPTMODE
 *  0b0..One Shot Mode
 *  0b1..Repeat Mode
 */
#define USB_GPTIMER1CTRL_GPTMODE(x)              (((uint32_t)(((uint32_t)(x)) << USB_GPTIMER1CTRL_GPTMODE_SHIFT)) & USB_GPTIMER1CTRL_GPTMODE_MASK)

#define USB_GPTIMER1CTRL_GPTRST_MASK             (0x40000000U)
#define USB_GPTIMER1CTRL_GPTRST_SHIFT            (30U)
/*! GPTRST - GPTRST
 *  0b0..No action
 *  0b1..Load counter value from GPTLD bits in USB_n_GPTIMER0LD
 */
#define USB_GPTIMER1CTRL_GPTRST(x)               (((uint32_t)(((uint32_t)(x)) << USB_GPTIMER1CTRL_GPTRST_SHIFT)) & USB_GPTIMER1CTRL_GPTRST_MASK)

#define USB_GPTIMER1CTRL_GPTRUN_MASK             (0x80000000U)
#define USB_GPTIMER1CTRL_GPTRUN_SHIFT            (31U)
/*! GPTRUN - GPTRUN
 *  0b0..Stop counting
 *  0b1..Run
 */
#define USB_GPTIMER1CTRL_GPTRUN(x)               (((uint32_t)(((uint32_t)(x)) << USB_GPTIMER1CTRL_GPTRUN_SHIFT)) & USB_GPTIMER1CTRL_GPTRUN_MASK)
/*! @} */

/*! @name SBUSCFG - System Bus Config */
/*! @{ */

#define USB_SBUSCFG_AHBBRST_MASK                 (0x7U)
#define USB_SBUSCFG_AHBBRST_SHIFT                (0U)
/*! AHBBRST - AHBBRST
 *  0b000..Incremental burst of unspecified length only
 *  0b001..INCR4 burst, then single transfer
 *  0b010..INCR8 burst, INCR4 burst, then single transfer
 *  0b011..INCR16 burst, INCR8 burst, INCR4 burst, then single transfer
 *  0b100..Reserved, don't use
 *  0b101..INCR4 burst, then incremental burst of unspecified length
 *  0b110..INCR8 burst, INCR4 burst, then incremental burst of unspecified length
 *  0b111..INCR16 burst, INCR8 burst, INCR4 burst, then incremental burst of unspecified length
 */
#define USB_SBUSCFG_AHBBRST(x)                   (((uint32_t)(((uint32_t)(x)) << USB_SBUSCFG_AHBBRST_SHIFT)) & USB_SBUSCFG_AHBBRST_MASK)
/*! @} */

/*! @name CAPLENGTH - Capability Registers Length */
/*! @{ */

#define USB_CAPLENGTH_CAPLENGTH_MASK             (0xFFU)
#define USB_CAPLENGTH_CAPLENGTH_SHIFT            (0U)
/*! CAPLENGTH - CAPLENGTH */
#define USB_CAPLENGTH_CAPLENGTH(x)               (((uint8_t)(((uint8_t)(x)) << USB_CAPLENGTH_CAPLENGTH_SHIFT)) & USB_CAPLENGTH_CAPLENGTH_MASK)
/*! @} */

/*! @name HCIVERSION - Host Controller Interface Version */
/*! @{ */

#define USB_HCIVERSION_HCIVERSION_MASK           (0xFFFFU)
#define USB_HCIVERSION_HCIVERSION_SHIFT          (0U)
/*! HCIVERSION - HCIVERSION */
#define USB_HCIVERSION_HCIVERSION(x)             (((uint16_t)(((uint16_t)(x)) << USB_HCIVERSION_HCIVERSION_SHIFT)) & USB_HCIVERSION_HCIVERSION_MASK)
/*! @} */

/*! @name HCSPARAMS - Host Controller Structural Parameters */
/*! @{ */

#define USB_HCSPARAMS_N_PORTS_MASK               (0xFU)
#define USB_HCSPARAMS_N_PORTS_SHIFT              (0U)
/*! N_PORTS - N_PORTS */
#define USB_HCSPARAMS_N_PORTS(x)                 (((uint32_t)(((uint32_t)(x)) << USB_HCSPARAMS_N_PORTS_SHIFT)) & USB_HCSPARAMS_N_PORTS_MASK)

#define USB_HCSPARAMS_PPC_MASK                   (0x10U)
#define USB_HCSPARAMS_PPC_SHIFT                  (4U)
/*! PPC - PPC */
#define USB_HCSPARAMS_PPC(x)                     (((uint32_t)(((uint32_t)(x)) << USB_HCSPARAMS_PPC_SHIFT)) & USB_HCSPARAMS_PPC_MASK)

#define USB_HCSPARAMS_N_PCC_MASK                 (0xF00U)
#define USB_HCSPARAMS_N_PCC_SHIFT                (8U)
/*! N_PCC - N_PCC */
#define USB_HCSPARAMS_N_PCC(x)                   (((uint32_t)(((uint32_t)(x)) << USB_HCSPARAMS_N_PCC_SHIFT)) & USB_HCSPARAMS_N_PCC_MASK)

#define USB_HCSPARAMS_N_CC_MASK                  (0xF000U)
#define USB_HCSPARAMS_N_CC_SHIFT                 (12U)
/*! N_CC - N_CC
 *  0b0000..There is no internal Companion Controller and port-ownership hand-off is not supported.
 *  0b0001..There are internal companion controller(s) and port-ownership hand-offs is supported.
 */
#define USB_HCSPARAMS_N_CC(x)                    (((uint32_t)(((uint32_t)(x)) << USB_HCSPARAMS_N_CC_SHIFT)) & USB_HCSPARAMS_N_CC_MASK)

#define USB_HCSPARAMS_PI_MASK                    (0x10000U)
#define USB_HCSPARAMS_PI_SHIFT                   (16U)
/*! PI - PI */
#define USB_HCSPARAMS_PI(x)                      (((uint32_t)(((uint32_t)(x)) << USB_HCSPARAMS_PI_SHIFT)) & USB_HCSPARAMS_PI_MASK)

#define USB_HCSPARAMS_N_PTT_MASK                 (0xF00000U)
#define USB_HCSPARAMS_N_PTT_SHIFT                (20U)
/*! N_PTT - N_PTT */
#define USB_HCSPARAMS_N_PTT(x)                   (((uint32_t)(((uint32_t)(x)) << USB_HCSPARAMS_N_PTT_SHIFT)) & USB_HCSPARAMS_N_PTT_MASK)

#define USB_HCSPARAMS_N_TT_MASK                  (0xF000000U)
#define USB_HCSPARAMS_N_TT_SHIFT                 (24U)
/*! N_TT - N_TT */
#define USB_HCSPARAMS_N_TT(x)                    (((uint32_t)(((uint32_t)(x)) << USB_HCSPARAMS_N_TT_SHIFT)) & USB_HCSPARAMS_N_TT_MASK)
/*! @} */

/*! @name HCCPARAMS - Host Controller Capability Parameters */
/*! @{ */

#define USB_HCCPARAMS_ADC_MASK                   (0x1U)
#define USB_HCCPARAMS_ADC_SHIFT                  (0U)
/*! ADC - ADC */
#define USB_HCCPARAMS_ADC(x)                     (((uint32_t)(((uint32_t)(x)) << USB_HCCPARAMS_ADC_SHIFT)) & USB_HCCPARAMS_ADC_MASK)

#define USB_HCCPARAMS_PFL_MASK                   (0x2U)
#define USB_HCCPARAMS_PFL_SHIFT                  (1U)
/*! PFL - PFL */
#define USB_HCCPARAMS_PFL(x)                     (((uint32_t)(((uint32_t)(x)) << USB_HCCPARAMS_PFL_SHIFT)) & USB_HCCPARAMS_PFL_MASK)

#define USB_HCCPARAMS_ASP_MASK                   (0x4U)
#define USB_HCCPARAMS_ASP_SHIFT                  (2U)
/*! ASP - ASP */
#define USB_HCCPARAMS_ASP(x)                     (((uint32_t)(((uint32_t)(x)) << USB_HCCPARAMS_ASP_SHIFT)) & USB_HCCPARAMS_ASP_MASK)

#define USB_HCCPARAMS_IST_MASK                   (0xF0U)
#define USB_HCCPARAMS_IST_SHIFT                  (4U)
/*! IST - IST */
#define USB_HCCPARAMS_IST(x)                     (((uint32_t)(((uint32_t)(x)) << USB_HCCPARAMS_IST_SHIFT)) & USB_HCCPARAMS_IST_MASK)

#define USB_HCCPARAMS_EECP_MASK                  (0xFF00U)
#define USB_HCCPARAMS_EECP_SHIFT                 (8U)
/*! EECP - EECP */
#define USB_HCCPARAMS_EECP(x)                    (((uint32_t)(((uint32_t)(x)) << USB_HCCPARAMS_EECP_SHIFT)) & USB_HCCPARAMS_EECP_MASK)
/*! @} */

/*! @name DCIVERSION - Device Controller Interface Version */
/*! @{ */

#define USB_DCIVERSION_DCIVERSION_MASK           (0xFFFFU)
#define USB_DCIVERSION_DCIVERSION_SHIFT          (0U)
/*! DCIVERSION - DCIVERSION */
#define USB_DCIVERSION_DCIVERSION(x)             (((uint16_t)(((uint16_t)(x)) << USB_DCIVERSION_DCIVERSION_SHIFT)) & USB_DCIVERSION_DCIVERSION_MASK)
/*! @} */

/*! @name DCCPARAMS - Device Controller Capability Parameters */
/*! @{ */

#define USB_DCCPARAMS_DEN_MASK                   (0x1FU)
#define USB_DCCPARAMS_DEN_SHIFT                  (0U)
/*! DEN - DEN */
#define USB_DCCPARAMS_DEN(x)                     (((uint32_t)(((uint32_t)(x)) << USB_DCCPARAMS_DEN_SHIFT)) & USB_DCCPARAMS_DEN_MASK)

#define USB_DCCPARAMS_DC_MASK                    (0x80U)
#define USB_DCCPARAMS_DC_SHIFT                   (7U)
/*! DC - DC */
#define USB_DCCPARAMS_DC(x)                      (((uint32_t)(((uint32_t)(x)) << USB_DCCPARAMS_DC_SHIFT)) & USB_DCCPARAMS_DC_MASK)

#define USB_DCCPARAMS_HC_MASK                    (0x100U)
#define USB_DCCPARAMS_HC_SHIFT                   (8U)
/*! HC - HC */
#define USB_DCCPARAMS_HC(x)                      (((uint32_t)(((uint32_t)(x)) << USB_DCCPARAMS_HC_SHIFT)) & USB_DCCPARAMS_HC_MASK)
/*! @} */

/*! @name USBCMD - USB Command Register */
/*! @{ */

#define USB_USBCMD_RS_MASK                       (0x1U)
#define USB_USBCMD_RS_SHIFT                      (0U)
/*! RS - RS */
#define USB_USBCMD_RS(x)                         (((uint32_t)(((uint32_t)(x)) << USB_USBCMD_RS_SHIFT)) & USB_USBCMD_RS_MASK)

#define USB_USBCMD_RST_MASK                      (0x2U)
#define USB_USBCMD_RST_SHIFT                     (1U)
/*! RST - RST */
#define USB_USBCMD_RST(x)                        (((uint32_t)(((uint32_t)(x)) << USB_USBCMD_RST_SHIFT)) & USB_USBCMD_RST_MASK)

#define USB_USBCMD_FS_1_MASK                     (0xCU)
#define USB_USBCMD_FS_1_SHIFT                    (2U)
/*! FS_1 - FS_1 */
#define USB_USBCMD_FS_1(x)                       (((uint32_t)(((uint32_t)(x)) << USB_USBCMD_FS_1_SHIFT)) & USB_USBCMD_FS_1_MASK)

#define USB_USBCMD_PSE_MASK                      (0x10U)
#define USB_USBCMD_PSE_SHIFT                     (4U)
/*! PSE - PSE
 *  0b0..Do not process the Periodic Schedule
 *  0b1..Use the PERIODICLISTBASE register to access the Periodic Schedule.
 */
#define USB_USBCMD_PSE(x)                        (((uint32_t)(((uint32_t)(x)) << USB_USBCMD_PSE_SHIFT)) & USB_USBCMD_PSE_MASK)

#define USB_USBCMD_ASE_MASK                      (0x20U)
#define USB_USBCMD_ASE_SHIFT                     (5U)
/*! ASE - ASE
 *  0b0..Do not process the Asynchronous Schedule.
 *  0b1..Use the ASYNCLISTADDR register to access the Asynchronous Schedule.
 */
#define USB_USBCMD_ASE(x)                        (((uint32_t)(((uint32_t)(x)) << USB_USBCMD_ASE_SHIFT)) & USB_USBCMD_ASE_MASK)

#define USB_USBCMD_IAA_MASK                      (0x40U)
#define USB_USBCMD_IAA_SHIFT                     (6U)
/*! IAA - IAA */
#define USB_USBCMD_IAA(x)                        (((uint32_t)(((uint32_t)(x)) << USB_USBCMD_IAA_SHIFT)) & USB_USBCMD_IAA_MASK)

#define USB_USBCMD_ASP_MASK                      (0x300U)
#define USB_USBCMD_ASP_SHIFT                     (8U)
/*! ASP - ASP */
#define USB_USBCMD_ASP(x)                        (((uint32_t)(((uint32_t)(x)) << USB_USBCMD_ASP_SHIFT)) & USB_USBCMD_ASP_MASK)

#define USB_USBCMD_ASPE_MASK                     (0x800U)
#define USB_USBCMD_ASPE_SHIFT                    (11U)
/*! ASPE - ASPE */
#define USB_USBCMD_ASPE(x)                       (((uint32_t)(((uint32_t)(x)) << USB_USBCMD_ASPE_SHIFT)) & USB_USBCMD_ASPE_MASK)

#define USB_USBCMD_SUTW_MASK                     (0x2000U)
#define USB_USBCMD_SUTW_SHIFT                    (13U)
/*! SUTW - SUTW */
#define USB_USBCMD_SUTW(x)                       (((uint32_t)(((uint32_t)(x)) << USB_USBCMD_SUTW_SHIFT)) & USB_USBCMD_SUTW_MASK)

#define USB_USBCMD_ATDTW_MASK                    (0x4000U)
#define USB_USBCMD_ATDTW_SHIFT                   (14U)
/*! ATDTW - ATDTW */
#define USB_USBCMD_ATDTW(x)                      (((uint32_t)(((uint32_t)(x)) << USB_USBCMD_ATDTW_SHIFT)) & USB_USBCMD_ATDTW_MASK)

#define USB_USBCMD_FS_2_MASK                     (0x8000U)
#define USB_USBCMD_FS_2_SHIFT                    (15U)
/*! FS_2 - FS_2 */
#define USB_USBCMD_FS_2(x)                       (((uint32_t)(((uint32_t)(x)) << USB_USBCMD_FS_2_SHIFT)) & USB_USBCMD_FS_2_MASK)

#define USB_USBCMD_ITC_MASK                      (0xFF0000U)
#define USB_USBCMD_ITC_SHIFT                     (16U)
/*! ITC - ITC
 *  0b00000000..Immediate (no threshold)
 *  0b00000001..1 micro-frame
 *  0b00000010..2 micro-frames
 *  0b00000100..4 micro-frames
 *  0b00001000..8 micro-frames
 *  0b00010000..16 micro-frames
 *  0b00100000..32 micro-frames
 *  0b01000000..64 micro-frames
 */
#define USB_USBCMD_ITC(x)                        (((uint32_t)(((uint32_t)(x)) << USB_USBCMD_ITC_SHIFT)) & USB_USBCMD_ITC_MASK)
/*! @} */

/*! @name USBSTS - USB Status Register */
/*! @{ */

#define USB_USBSTS_UI_MASK                       (0x1U)
#define USB_USBSTS_UI_SHIFT                      (0U)
/*! UI - UI */
#define USB_USBSTS_UI(x)                         (((uint32_t)(((uint32_t)(x)) << USB_USBSTS_UI_SHIFT)) & USB_USBSTS_UI_MASK)

#define USB_USBSTS_UEI_MASK                      (0x2U)
#define USB_USBSTS_UEI_SHIFT                     (1U)
/*! UEI - UEI */
#define USB_USBSTS_UEI(x)                        (((uint32_t)(((uint32_t)(x)) << USB_USBSTS_UEI_SHIFT)) & USB_USBSTS_UEI_MASK)

#define USB_USBSTS_PCI_MASK                      (0x4U)
#define USB_USBSTS_PCI_SHIFT                     (2U)
/*! PCI - PCI */
#define USB_USBSTS_PCI(x)                        (((uint32_t)(((uint32_t)(x)) << USB_USBSTS_PCI_SHIFT)) & USB_USBSTS_PCI_MASK)

#define USB_USBSTS_FRI_MASK                      (0x8U)
#define USB_USBSTS_FRI_SHIFT                     (3U)
/*! FRI - FRI */
#define USB_USBSTS_FRI(x)                        (((uint32_t)(((uint32_t)(x)) << USB_USBSTS_FRI_SHIFT)) & USB_USBSTS_FRI_MASK)

#define USB_USBSTS_SEI_MASK                      (0x10U)
#define USB_USBSTS_SEI_SHIFT                     (4U)
/*! SEI - SEI */
#define USB_USBSTS_SEI(x)                        (((uint32_t)(((uint32_t)(x)) << USB_USBSTS_SEI_SHIFT)) & USB_USBSTS_SEI_MASK)

#define USB_USBSTS_AAI_MASK                      (0x20U)
#define USB_USBSTS_AAI_SHIFT                     (5U)
/*! AAI - AAI */
#define USB_USBSTS_AAI(x)                        (((uint32_t)(((uint32_t)(x)) << USB_USBSTS_AAI_SHIFT)) & USB_USBSTS_AAI_MASK)

#define USB_USBSTS_URI_MASK                      (0x40U)
#define USB_USBSTS_URI_SHIFT                     (6U)
/*! URI - URI */
#define USB_USBSTS_URI(x)                        (((uint32_t)(((uint32_t)(x)) << USB_USBSTS_URI_SHIFT)) & USB_USBSTS_URI_MASK)

#define USB_USBSTS_SRI_MASK                      (0x80U)
#define USB_USBSTS_SRI_SHIFT                     (7U)
/*! SRI - SRI */
#define USB_USBSTS_SRI(x)                        (((uint32_t)(((uint32_t)(x)) << USB_USBSTS_SRI_SHIFT)) & USB_USBSTS_SRI_MASK)

#define USB_USBSTS_SLI_MASK                      (0x100U)
#define USB_USBSTS_SLI_SHIFT                     (8U)
/*! SLI - SLI */
#define USB_USBSTS_SLI(x)                        (((uint32_t)(((uint32_t)(x)) << USB_USBSTS_SLI_SHIFT)) & USB_USBSTS_SLI_MASK)

#define USB_USBSTS_ULPII_MASK                    (0x400U)
#define USB_USBSTS_ULPII_SHIFT                   (10U)
/*! ULPII - ULPII */
#define USB_USBSTS_ULPII(x)                      (((uint32_t)(((uint32_t)(x)) << USB_USBSTS_ULPII_SHIFT)) & USB_USBSTS_ULPII_MASK)

#define USB_USBSTS_HCH_MASK                      (0x1000U)
#define USB_USBSTS_HCH_SHIFT                     (12U)
/*! HCH - HCH */
#define USB_USBSTS_HCH(x)                        (((uint32_t)(((uint32_t)(x)) << USB_USBSTS_HCH_SHIFT)) & USB_USBSTS_HCH_MASK)

#define USB_USBSTS_RCL_MASK                      (0x2000U)
#define USB_USBSTS_RCL_SHIFT                     (13U)
/*! RCL - RCL */
#define USB_USBSTS_RCL(x)                        (((uint32_t)(((uint32_t)(x)) << USB_USBSTS_RCL_SHIFT)) & USB_USBSTS_RCL_MASK)

#define USB_USBSTS_PS_MASK                       (0x4000U)
#define USB_USBSTS_PS_SHIFT                      (14U)
/*! PS - PS */
#define USB_USBSTS_PS(x)                         (((uint32_t)(((uint32_t)(x)) << USB_USBSTS_PS_SHIFT)) & USB_USBSTS_PS_MASK)

#define USB_USBSTS_AS_MASK                       (0x8000U)
#define USB_USBSTS_AS_SHIFT                      (15U)
/*! AS - AS */
#define USB_USBSTS_AS(x)                         (((uint32_t)(((uint32_t)(x)) << USB_USBSTS_AS_SHIFT)) & USB_USBSTS_AS_MASK)

#define USB_USBSTS_NAKI_MASK                     (0x10000U)
#define USB_USBSTS_NAKI_SHIFT                    (16U)
/*! NAKI - NAKI */
#define USB_USBSTS_NAKI(x)                       (((uint32_t)(((uint32_t)(x)) << USB_USBSTS_NAKI_SHIFT)) & USB_USBSTS_NAKI_MASK)

#define USB_USBSTS_TI0_MASK                      (0x1000000U)
#define USB_USBSTS_TI0_SHIFT                     (24U)
/*! TI0 - TI0 */
#define USB_USBSTS_TI0(x)                        (((uint32_t)(((uint32_t)(x)) << USB_USBSTS_TI0_SHIFT)) & USB_USBSTS_TI0_MASK)

#define USB_USBSTS_TI1_MASK                      (0x2000000U)
#define USB_USBSTS_TI1_SHIFT                     (25U)
/*! TI1 - TI1 */
#define USB_USBSTS_TI1(x)                        (((uint32_t)(((uint32_t)(x)) << USB_USBSTS_TI1_SHIFT)) & USB_USBSTS_TI1_MASK)
/*! @} */

/*! @name USBINTR - Interrupt Enable Register */
/*! @{ */

#define USB_USBINTR_UE_MASK                      (0x1U)
#define USB_USBINTR_UE_SHIFT                     (0U)
/*! UE - UE */
#define USB_USBINTR_UE(x)                        (((uint32_t)(((uint32_t)(x)) << USB_USBINTR_UE_SHIFT)) & USB_USBINTR_UE_MASK)

#define USB_USBINTR_UEE_MASK                     (0x2U)
#define USB_USBINTR_UEE_SHIFT                    (1U)
/*! UEE - UEE */
#define USB_USBINTR_UEE(x)                       (((uint32_t)(((uint32_t)(x)) << USB_USBINTR_UEE_SHIFT)) & USB_USBINTR_UEE_MASK)

#define USB_USBINTR_PCE_MASK                     (0x4U)
#define USB_USBINTR_PCE_SHIFT                    (2U)
/*! PCE - PCE */
#define USB_USBINTR_PCE(x)                       (((uint32_t)(((uint32_t)(x)) << USB_USBINTR_PCE_SHIFT)) & USB_USBINTR_PCE_MASK)

#define USB_USBINTR_FRE_MASK                     (0x8U)
#define USB_USBINTR_FRE_SHIFT                    (3U)
/*! FRE - FRE */
#define USB_USBINTR_FRE(x)                       (((uint32_t)(((uint32_t)(x)) << USB_USBINTR_FRE_SHIFT)) & USB_USBINTR_FRE_MASK)

#define USB_USBINTR_SEE_MASK                     (0x10U)
#define USB_USBINTR_SEE_SHIFT                    (4U)
/*! SEE - SEE */
#define USB_USBINTR_SEE(x)                       (((uint32_t)(((uint32_t)(x)) << USB_USBINTR_SEE_SHIFT)) & USB_USBINTR_SEE_MASK)

#define USB_USBINTR_AAE_MASK                     (0x20U)
#define USB_USBINTR_AAE_SHIFT                    (5U)
/*! AAE - AAE */
#define USB_USBINTR_AAE(x)                       (((uint32_t)(((uint32_t)(x)) << USB_USBINTR_AAE_SHIFT)) & USB_USBINTR_AAE_MASK)

#define USB_USBINTR_URE_MASK                     (0x40U)
#define USB_USBINTR_URE_SHIFT                    (6U)
/*! URE - URE */
#define USB_USBINTR_URE(x)                       (((uint32_t)(((uint32_t)(x)) << USB_USBINTR_URE_SHIFT)) & USB_USBINTR_URE_MASK)

#define USB_USBINTR_SRE_MASK                     (0x80U)
#define USB_USBINTR_SRE_SHIFT                    (7U)
/*! SRE - SRE */
#define USB_USBINTR_SRE(x)                       (((uint32_t)(((uint32_t)(x)) << USB_USBINTR_SRE_SHIFT)) & USB_USBINTR_SRE_MASK)

#define USB_USBINTR_SLE_MASK                     (0x100U)
#define USB_USBINTR_SLE_SHIFT                    (8U)
/*! SLE - SLE */
#define USB_USBINTR_SLE(x)                       (((uint32_t)(((uint32_t)(x)) << USB_USBINTR_SLE_SHIFT)) & USB_USBINTR_SLE_MASK)

#define USB_USBINTR_ULPIE_MASK                   (0x400U)
#define USB_USBINTR_ULPIE_SHIFT                  (10U)
/*! ULPIE - ULPIE */
#define USB_USBINTR_ULPIE(x)                     (((uint32_t)(((uint32_t)(x)) << USB_USBINTR_ULPIE_SHIFT)) & USB_USBINTR_ULPIE_MASK)

#define USB_USBINTR_NAKE_MASK                    (0x10000U)
#define USB_USBINTR_NAKE_SHIFT                   (16U)
/*! NAKE - NAKE */
#define USB_USBINTR_NAKE(x)                      (((uint32_t)(((uint32_t)(x)) << USB_USBINTR_NAKE_SHIFT)) & USB_USBINTR_NAKE_MASK)

#define USB_USBINTR_UAIE_MASK                    (0x40000U)
#define USB_USBINTR_UAIE_SHIFT                   (18U)
/*! UAIE - UAIE */
#define USB_USBINTR_UAIE(x)                      (((uint32_t)(((uint32_t)(x)) << USB_USBINTR_UAIE_SHIFT)) & USB_USBINTR_UAIE_MASK)

#define USB_USBINTR_UPIE_MASK                    (0x80000U)
#define USB_USBINTR_UPIE_SHIFT                   (19U)
/*! UPIE - UPIE */
#define USB_USBINTR_UPIE(x)                      (((uint32_t)(((uint32_t)(x)) << USB_USBINTR_UPIE_SHIFT)) & USB_USBINTR_UPIE_MASK)

#define USB_USBINTR_TIE0_MASK                    (0x1000000U)
#define USB_USBINTR_TIE0_SHIFT                   (24U)
/*! TIE0 - TIE0 */
#define USB_USBINTR_TIE0(x)                      (((uint32_t)(((uint32_t)(x)) << USB_USBINTR_TIE0_SHIFT)) & USB_USBINTR_TIE0_MASK)

#define USB_USBINTR_TIE1_MASK                    (0x2000000U)
#define USB_USBINTR_TIE1_SHIFT                   (25U)
/*! TIE1 - TIE1 */
#define USB_USBINTR_TIE1(x)                      (((uint32_t)(((uint32_t)(x)) << USB_USBINTR_TIE1_SHIFT)) & USB_USBINTR_TIE1_MASK)
/*! @} */

/*! @name FRINDEX - USB Frame Index */
/*! @{ */

#define USB_FRINDEX_FRINDEX_MASK                 (0x3FFFU)
#define USB_FRINDEX_FRINDEX_SHIFT                (0U)
/*! FRINDEX - FRINDEX
 *  0b00000000000000..(1024) 12
 *  0b00000000000001..(512) 11
 *  0b00000000000010..(256) 10
 *  0b00000000000011..(128) 9
 *  0b00000000000100..(64) 8
 *  0b00000000000101..(32) 7
 *  0b00000000000110..(16) 6
 *  0b00000000000111..(8) 5
 */
#define USB_FRINDEX_FRINDEX(x)                   (((uint32_t)(((uint32_t)(x)) << USB_FRINDEX_FRINDEX_SHIFT)) & USB_FRINDEX_FRINDEX_MASK)
/*! @} */

/*! @name DEVICEADDR - Device Address */
/*! @{ */

#define USB_DEVICEADDR_USBADRA_MASK              (0x1000000U)
#define USB_DEVICEADDR_USBADRA_SHIFT             (24U)
/*! USBADRA - USBADRA */
#define USB_DEVICEADDR_USBADRA(x)                (((uint32_t)(((uint32_t)(x)) << USB_DEVICEADDR_USBADRA_SHIFT)) & USB_DEVICEADDR_USBADRA_MASK)

#define USB_DEVICEADDR_USBADR_MASK               (0xFE000000U)
#define USB_DEVICEADDR_USBADR_SHIFT              (25U)
/*! USBADR - USBADR */
#define USB_DEVICEADDR_USBADR(x)                 (((uint32_t)(((uint32_t)(x)) << USB_DEVICEADDR_USBADR_SHIFT)) & USB_DEVICEADDR_USBADR_MASK)
/*! @} */

/*! @name PERIODICLISTBASE - Frame List Base Address */
/*! @{ */

#define USB_PERIODICLISTBASE_BASEADR_MASK        (0xFFFFF000U)
#define USB_PERIODICLISTBASE_BASEADR_SHIFT       (12U)
/*! BASEADR - BASEADR */
#define USB_PERIODICLISTBASE_BASEADR(x)          (((uint32_t)(((uint32_t)(x)) << USB_PERIODICLISTBASE_BASEADR_SHIFT)) & USB_PERIODICLISTBASE_BASEADR_MASK)
/*! @} */

/*! @name ASYNCLISTADDR - Next Asynch. Address */
/*! @{ */

#define USB_ASYNCLISTADDR_ASYBASE_MASK           (0xFFFFFFE0U)
#define USB_ASYNCLISTADDR_ASYBASE_SHIFT          (5U)
/*! ASYBASE - ASYBASE */
#define USB_ASYNCLISTADDR_ASYBASE(x)             (((uint32_t)(((uint32_t)(x)) << USB_ASYNCLISTADDR_ASYBASE_SHIFT)) & USB_ASYNCLISTADDR_ASYBASE_MASK)
/*! @} */

/*! @name ENDPTLISTADDR - Endpoint List Address */
/*! @{ */

#define USB_ENDPTLISTADDR_EPBASE_MASK            (0xFFFFF800U)
#define USB_ENDPTLISTADDR_EPBASE_SHIFT           (11U)
/*! EPBASE - EPBASE */
#define USB_ENDPTLISTADDR_EPBASE(x)              (((uint32_t)(((uint32_t)(x)) << USB_ENDPTLISTADDR_EPBASE_SHIFT)) & USB_ENDPTLISTADDR_EPBASE_MASK)
/*! @} */

/*! @name BURSTSIZE - Programmable Burst Size */
/*! @{ */

#define USB_BURSTSIZE_RXPBURST_MASK              (0xFFU)
#define USB_BURSTSIZE_RXPBURST_SHIFT             (0U)
/*! RXPBURST - RXPBURST */
#define USB_BURSTSIZE_RXPBURST(x)                (((uint32_t)(((uint32_t)(x)) << USB_BURSTSIZE_RXPBURST_SHIFT)) & USB_BURSTSIZE_RXPBURST_MASK)

#define USB_BURSTSIZE_TXPBURST_MASK              (0x1FF00U)
#define USB_BURSTSIZE_TXPBURST_SHIFT             (8U)
/*! TXPBURST - TXPBURST */
#define USB_BURSTSIZE_TXPBURST(x)                (((uint32_t)(((uint32_t)(x)) << USB_BURSTSIZE_TXPBURST_SHIFT)) & USB_BURSTSIZE_TXPBURST_MASK)
/*! @} */

/*! @name TXFILLTUNING - TX FIFO Fill Tuning */
/*! @{ */

#define USB_TXFILLTUNING_TXSCHOH_MASK            (0xFFU)
#define USB_TXFILLTUNING_TXSCHOH_SHIFT           (0U)
/*! TXSCHOH - TXSCHOH */
#define USB_TXFILLTUNING_TXSCHOH(x)              (((uint32_t)(((uint32_t)(x)) << USB_TXFILLTUNING_TXSCHOH_SHIFT)) & USB_TXFILLTUNING_TXSCHOH_MASK)

#define USB_TXFILLTUNING_TXSCHHEALTH_MASK        (0x1F00U)
#define USB_TXFILLTUNING_TXSCHHEALTH_SHIFT       (8U)
/*! TXSCHHEALTH - TXSCHHEALTH */
#define USB_TXFILLTUNING_TXSCHHEALTH(x)          (((uint32_t)(((uint32_t)(x)) << USB_TXFILLTUNING_TXSCHHEALTH_SHIFT)) & USB_TXFILLTUNING_TXSCHHEALTH_MASK)

#define USB_TXFILLTUNING_TXFIFOTHRES_MASK        (0x3F0000U)
#define USB_TXFILLTUNING_TXFIFOTHRES_SHIFT       (16U)
/*! TXFIFOTHRES - TXFIFOTHRES */
#define USB_TXFILLTUNING_TXFIFOTHRES(x)          (((uint32_t)(((uint32_t)(x)) << USB_TXFILLTUNING_TXFIFOTHRES_SHIFT)) & USB_TXFILLTUNING_TXFIFOTHRES_MASK)
/*! @} */

/*! @name ENDPTNAK - Endpoint NAK */
/*! @{ */

#define USB_ENDPTNAK_EPRN_MASK                   (0xFFU)
#define USB_ENDPTNAK_EPRN_SHIFT                  (0U)
/*! EPRN - EPRN */
#define USB_ENDPTNAK_EPRN(x)                     (((uint32_t)(((uint32_t)(x)) << USB_ENDPTNAK_EPRN_SHIFT)) & USB_ENDPTNAK_EPRN_MASK)

#define USB_ENDPTNAK_EPTN_MASK                   (0xFF0000U)
#define USB_ENDPTNAK_EPTN_SHIFT                  (16U)
/*! EPTN - EPTN */
#define USB_ENDPTNAK_EPTN(x)                     (((uint32_t)(((uint32_t)(x)) << USB_ENDPTNAK_EPTN_SHIFT)) & USB_ENDPTNAK_EPTN_MASK)
/*! @} */

/*! @name ENDPTNAKEN - Endpoint NAK Enable */
/*! @{ */

#define USB_ENDPTNAKEN_EPRNE_MASK                (0xFFU)
#define USB_ENDPTNAKEN_EPRNE_SHIFT               (0U)
/*! EPRNE - EPRNE */
#define USB_ENDPTNAKEN_EPRNE(x)                  (((uint32_t)(((uint32_t)(x)) << USB_ENDPTNAKEN_EPRNE_SHIFT)) & USB_ENDPTNAKEN_EPRNE_MASK)

#define USB_ENDPTNAKEN_EPTNE_MASK                (0xFF0000U)
#define USB_ENDPTNAKEN_EPTNE_SHIFT               (16U)
/*! EPTNE - EPTNE */
#define USB_ENDPTNAKEN_EPTNE(x)                  (((uint32_t)(((uint32_t)(x)) << USB_ENDPTNAKEN_EPTNE_SHIFT)) & USB_ENDPTNAKEN_EPTNE_MASK)
/*! @} */

/*! @name CONFIGFLAG - Configure Flag Register */
/*! @{ */

#define USB_CONFIGFLAG_CF_MASK                   (0x1U)
#define USB_CONFIGFLAG_CF_SHIFT                  (0U)
/*! CF - CF
 *  0b0..Port routing control logic default-routes each port to an implementation dependent classic host controller.
 *  0b1..Port routing control logic default-routes all ports to this host controller.
 */
#define USB_CONFIGFLAG_CF(x)                     (((uint32_t)(((uint32_t)(x)) << USB_CONFIGFLAG_CF_SHIFT)) & USB_CONFIGFLAG_CF_MASK)
/*! @} */

/*! @name PORTSC1 - Port Status & Control */
/*! @{ */

#define USB_PORTSC1_CCS_MASK                     (0x1U)
#define USB_PORTSC1_CCS_SHIFT                    (0U)
/*! CCS - CCS */
#define USB_PORTSC1_CCS(x)                       (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_CCS_SHIFT)) & USB_PORTSC1_CCS_MASK)

#define USB_PORTSC1_CSC_MASK                     (0x2U)
#define USB_PORTSC1_CSC_SHIFT                    (1U)
/*! CSC - CSC */
#define USB_PORTSC1_CSC(x)                       (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_CSC_SHIFT)) & USB_PORTSC1_CSC_MASK)

#define USB_PORTSC1_PE_MASK                      (0x4U)
#define USB_PORTSC1_PE_SHIFT                     (2U)
/*! PE - PE */
#define USB_PORTSC1_PE(x)                        (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_PE_SHIFT)) & USB_PORTSC1_PE_MASK)

#define USB_PORTSC1_PEC_MASK                     (0x8U)
#define USB_PORTSC1_PEC_SHIFT                    (3U)
/*! PEC - PEC */
#define USB_PORTSC1_PEC(x)                       (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_PEC_SHIFT)) & USB_PORTSC1_PEC_MASK)

#define USB_PORTSC1_OCA_MASK                     (0x10U)
#define USB_PORTSC1_OCA_SHIFT                    (4U)
/*! OCA - OCA
 *  0b0..This port does not have an over-current condition.
 *  0b1..This port currently has an over-current condition
 */
#define USB_PORTSC1_OCA(x)                       (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_OCA_SHIFT)) & USB_PORTSC1_OCA_MASK)

#define USB_PORTSC1_OCC_MASK                     (0x20U)
#define USB_PORTSC1_OCC_SHIFT                    (5U)
/*! OCC - OCC */
#define USB_PORTSC1_OCC(x)                       (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_OCC_SHIFT)) & USB_PORTSC1_OCC_MASK)

#define USB_PORTSC1_FPR_MASK                     (0x40U)
#define USB_PORTSC1_FPR_SHIFT                    (6U)
/*! FPR - FPR */
#define USB_PORTSC1_FPR(x)                       (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_FPR_SHIFT)) & USB_PORTSC1_FPR_MASK)

#define USB_PORTSC1_SUSP_MASK                    (0x80U)
#define USB_PORTSC1_SUSP_SHIFT                   (7U)
/*! SUSP - SUSP */
#define USB_PORTSC1_SUSP(x)                      (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_SUSP_SHIFT)) & USB_PORTSC1_SUSP_MASK)

#define USB_PORTSC1_PR_MASK                      (0x100U)
#define USB_PORTSC1_PR_SHIFT                     (8U)
/*! PR - PR */
#define USB_PORTSC1_PR(x)                        (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_PR_SHIFT)) & USB_PORTSC1_PR_MASK)

#define USB_PORTSC1_HSP_MASK                     (0x200U)
#define USB_PORTSC1_HSP_SHIFT                    (9U)
/*! HSP - HSP */
#define USB_PORTSC1_HSP(x)                       (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_HSP_SHIFT)) & USB_PORTSC1_HSP_MASK)

#define USB_PORTSC1_LS_MASK                      (0xC00U)
#define USB_PORTSC1_LS_SHIFT                     (10U)
/*! LS - LS
 *  0b00..SE0
 *  0b01..K-state
 *  0b10..J-state
 *  0b11..Undefined
 */
#define USB_PORTSC1_LS(x)                        (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_LS_SHIFT)) & USB_PORTSC1_LS_MASK)

#define USB_PORTSC1_PP_MASK                      (0x1000U)
#define USB_PORTSC1_PP_SHIFT                     (12U)
/*! PP - PP */
#define USB_PORTSC1_PP(x)                        (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_PP_SHIFT)) & USB_PORTSC1_PP_MASK)

#define USB_PORTSC1_PO_MASK                      (0x2000U)
#define USB_PORTSC1_PO_SHIFT                     (13U)
/*! PO - PO */
#define USB_PORTSC1_PO(x)                        (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_PO_SHIFT)) & USB_PORTSC1_PO_MASK)

#define USB_PORTSC1_PIC_MASK                     (0xC000U)
#define USB_PORTSC1_PIC_SHIFT                    (14U)
/*! PIC - PIC
 *  0b00..Port indicators are off
 *  0b01..Amber
 *  0b10..Green
 *  0b11..Undefined
 */
#define USB_PORTSC1_PIC(x)                       (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_PIC_SHIFT)) & USB_PORTSC1_PIC_MASK)

#define USB_PORTSC1_PTC_MASK                     (0xF0000U)
#define USB_PORTSC1_PTC_SHIFT                    (16U)
/*! PTC - PTC
 *  0b0000..TEST_MODE_DISABLE
 *  0b0001..J_STATE
 *  0b0010..K_STATE
 *  0b0011..SE0 (host) / NAK (device)
 *  0b0100..Packet
 *  0b0101..FORCE_ENABLE_HS
 *  0b0110..FORCE_ENABLE_FS
 *  0b0111..FORCE_ENABLE_LS
 *  0b1000-0b1111..Reserved
 */
#define USB_PORTSC1_PTC(x)                       (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_PTC_SHIFT)) & USB_PORTSC1_PTC_MASK)

#define USB_PORTSC1_WKCN_MASK                    (0x100000U)
#define USB_PORTSC1_WKCN_SHIFT                   (20U)
/*! WKCN - WKCN */
#define USB_PORTSC1_WKCN(x)                      (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_WKCN_SHIFT)) & USB_PORTSC1_WKCN_MASK)

#define USB_PORTSC1_WKDC_MASK                    (0x200000U)
#define USB_PORTSC1_WKDC_SHIFT                   (21U)
/*! WKDC - WKDC */
#define USB_PORTSC1_WKDC(x)                      (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_WKDC_SHIFT)) & USB_PORTSC1_WKDC_MASK)

#define USB_PORTSC1_WKOC_MASK                    (0x400000U)
#define USB_PORTSC1_WKOC_SHIFT                   (22U)
/*! WKOC - WKOC */
#define USB_PORTSC1_WKOC(x)                      (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_WKOC_SHIFT)) & USB_PORTSC1_WKOC_MASK)

#define USB_PORTSC1_PHCD_MASK                    (0x800000U)
#define USB_PORTSC1_PHCD_SHIFT                   (23U)
/*! PHCD - PHCD
 *  0b0..Enable PHY clock
 *  0b1..Disable PHY clock
 */
#define USB_PORTSC1_PHCD(x)                      (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_PHCD_SHIFT)) & USB_PORTSC1_PHCD_MASK)

#define USB_PORTSC1_PFSC_MASK                    (0x1000000U)
#define USB_PORTSC1_PFSC_SHIFT                   (24U)
/*! PFSC - PFSC
 *  0b0..Normal operation
 *  0b1..Forced to full speed
 */
#define USB_PORTSC1_PFSC(x)                      (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_PFSC_SHIFT)) & USB_PORTSC1_PFSC_MASK)

#define USB_PORTSC1_PTS_2_MASK                   (0x2000000U)
#define USB_PORTSC1_PTS_2_SHIFT                  (25U)
/*! PTS_2 - PTS_2 */
#define USB_PORTSC1_PTS_2(x)                     (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_PTS_2_SHIFT)) & USB_PORTSC1_PTS_2_MASK)

#define USB_PORTSC1_PSPD_MASK                    (0xC000000U)
#define USB_PORTSC1_PSPD_SHIFT                   (26U)
/*! PSPD - PSPD
 *  0b00..Full Speed
 *  0b01..Low Speed
 *  0b10..High Speed
 *  0b11..Undefined
 */
#define USB_PORTSC1_PSPD(x)                      (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_PSPD_SHIFT)) & USB_PORTSC1_PSPD_MASK)

#define USB_PORTSC1_PTW_MASK                     (0x10000000U)
#define USB_PORTSC1_PTW_SHIFT                    (28U)
/*! PTW - PTW
 *  0b0..Select the 8-bit UTMI interface [60MHz]
 *  0b1..Select the 16-bit UTMI interface [30MHz]
 */
#define USB_PORTSC1_PTW(x)                       (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_PTW_SHIFT)) & USB_PORTSC1_PTW_MASK)

#define USB_PORTSC1_STS_MASK                     (0x20000000U)
#define USB_PORTSC1_STS_SHIFT                    (29U)
/*! STS - STS */
#define USB_PORTSC1_STS(x)                       (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_STS_SHIFT)) & USB_PORTSC1_STS_MASK)

#define USB_PORTSC1_PTS_1_MASK                   (0xC0000000U)
#define USB_PORTSC1_PTS_1_SHIFT                  (30U)
/*! PTS_1 - PTS_1 */
#define USB_PORTSC1_PTS_1(x)                     (((uint32_t)(((uint32_t)(x)) << USB_PORTSC1_PTS_1_SHIFT)) & USB_PORTSC1_PTS_1_MASK)
/*! @} */

/*! @name OTGSC - On-The-Go Status & control */
/*! @{ */

#define USB_OTGSC_VD_MASK                        (0x1U)
#define USB_OTGSC_VD_SHIFT                       (0U)
/*! VD - VD */
#define USB_OTGSC_VD(x)                          (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_VD_SHIFT)) & USB_OTGSC_VD_MASK)

#define USB_OTGSC_VC_MASK                        (0x2U)
#define USB_OTGSC_VC_SHIFT                       (1U)
/*! VC - VC */
#define USB_OTGSC_VC(x)                          (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_VC_SHIFT)) & USB_OTGSC_VC_MASK)

#define USB_OTGSC_OT_MASK                        (0x8U)
#define USB_OTGSC_OT_SHIFT                       (3U)
/*! OT - OT */
#define USB_OTGSC_OT(x)                          (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_OT_SHIFT)) & USB_OTGSC_OT_MASK)

#define USB_OTGSC_DP_MASK                        (0x10U)
#define USB_OTGSC_DP_SHIFT                       (4U)
/*! DP - DP */
#define USB_OTGSC_DP(x)                          (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_DP_SHIFT)) & USB_OTGSC_DP_MASK)

#define USB_OTGSC_IDPU_MASK                      (0x20U)
#define USB_OTGSC_IDPU_SHIFT                     (5U)
/*! IDPU - IDPU */
#define USB_OTGSC_IDPU(x)                        (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_IDPU_SHIFT)) & USB_OTGSC_IDPU_MASK)

#define USB_OTGSC_ID_MASK                        (0x100U)
#define USB_OTGSC_ID_SHIFT                       (8U)
/*! ID - ID */
#define USB_OTGSC_ID(x)                          (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_ID_SHIFT)) & USB_OTGSC_ID_MASK)

#define USB_OTGSC_AVV_MASK                       (0x200U)
#define USB_OTGSC_AVV_SHIFT                      (9U)
/*! AVV - AVV */
#define USB_OTGSC_AVV(x)                         (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_AVV_SHIFT)) & USB_OTGSC_AVV_MASK)

#define USB_OTGSC_ASV_MASK                       (0x400U)
#define USB_OTGSC_ASV_SHIFT                      (10U)
/*! ASV - ASV */
#define USB_OTGSC_ASV(x)                         (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_ASV_SHIFT)) & USB_OTGSC_ASV_MASK)

#define USB_OTGSC_BSV_MASK                       (0x800U)
#define USB_OTGSC_BSV_SHIFT                      (11U)
/*! BSV - BSV */
#define USB_OTGSC_BSV(x)                         (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_BSV_SHIFT)) & USB_OTGSC_BSV_MASK)

#define USB_OTGSC_BSE_MASK                       (0x1000U)
#define USB_OTGSC_BSE_SHIFT                      (12U)
/*! BSE - BSE */
#define USB_OTGSC_BSE(x)                         (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_BSE_SHIFT)) & USB_OTGSC_BSE_MASK)

#define USB_OTGSC_TOG_1MS_MASK                   (0x2000U)
#define USB_OTGSC_TOG_1MS_SHIFT                  (13U)
/*! TOG_1MS - TOG_1MS */
#define USB_OTGSC_TOG_1MS(x)                     (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_TOG_1MS_SHIFT)) & USB_OTGSC_TOG_1MS_MASK)

#define USB_OTGSC_DPS_MASK                       (0x4000U)
#define USB_OTGSC_DPS_SHIFT                      (14U)
/*! DPS - DPS */
#define USB_OTGSC_DPS(x)                         (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_DPS_SHIFT)) & USB_OTGSC_DPS_MASK)

#define USB_OTGSC_IDIS_MASK                      (0x10000U)
#define USB_OTGSC_IDIS_SHIFT                     (16U)
/*! IDIS - IDIS */
#define USB_OTGSC_IDIS(x)                        (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_IDIS_SHIFT)) & USB_OTGSC_IDIS_MASK)

#define USB_OTGSC_AVVIS_MASK                     (0x20000U)
#define USB_OTGSC_AVVIS_SHIFT                    (17U)
/*! AVVIS - AVVIS */
#define USB_OTGSC_AVVIS(x)                       (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_AVVIS_SHIFT)) & USB_OTGSC_AVVIS_MASK)

#define USB_OTGSC_ASVIS_MASK                     (0x40000U)
#define USB_OTGSC_ASVIS_SHIFT                    (18U)
/*! ASVIS - ASVIS */
#define USB_OTGSC_ASVIS(x)                       (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_ASVIS_SHIFT)) & USB_OTGSC_ASVIS_MASK)

#define USB_OTGSC_BSVIS_MASK                     (0x80000U)
#define USB_OTGSC_BSVIS_SHIFT                    (19U)
/*! BSVIS - BSVIS */
#define USB_OTGSC_BSVIS(x)                       (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_BSVIS_SHIFT)) & USB_OTGSC_BSVIS_MASK)

#define USB_OTGSC_BSEIS_MASK                     (0x100000U)
#define USB_OTGSC_BSEIS_SHIFT                    (20U)
/*! BSEIS - BSEIS */
#define USB_OTGSC_BSEIS(x)                       (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_BSEIS_SHIFT)) & USB_OTGSC_BSEIS_MASK)

#define USB_OTGSC_STATUS_1MS_MASK                (0x200000U)
#define USB_OTGSC_STATUS_1MS_SHIFT               (21U)
/*! STATUS_1MS - STATUS_1MS */
#define USB_OTGSC_STATUS_1MS(x)                  (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_STATUS_1MS_SHIFT)) & USB_OTGSC_STATUS_1MS_MASK)

#define USB_OTGSC_DPIS_MASK                      (0x400000U)
#define USB_OTGSC_DPIS_SHIFT                     (22U)
/*! DPIS - DPIS */
#define USB_OTGSC_DPIS(x)                        (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_DPIS_SHIFT)) & USB_OTGSC_DPIS_MASK)

#define USB_OTGSC_IDIE_MASK                      (0x1000000U)
#define USB_OTGSC_IDIE_SHIFT                     (24U)
/*! IDIE - IDIE */
#define USB_OTGSC_IDIE(x)                        (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_IDIE_SHIFT)) & USB_OTGSC_IDIE_MASK)

#define USB_OTGSC_AVVIE_MASK                     (0x2000000U)
#define USB_OTGSC_AVVIE_SHIFT                    (25U)
/*! AVVIE - AVVIE */
#define USB_OTGSC_AVVIE(x)                       (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_AVVIE_SHIFT)) & USB_OTGSC_AVVIE_MASK)

#define USB_OTGSC_ASVIE_MASK                     (0x4000000U)
#define USB_OTGSC_ASVIE_SHIFT                    (26U)
/*! ASVIE - ASVIE */
#define USB_OTGSC_ASVIE(x)                       (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_ASVIE_SHIFT)) & USB_OTGSC_ASVIE_MASK)

#define USB_OTGSC_BSVIE_MASK                     (0x8000000U)
#define USB_OTGSC_BSVIE_SHIFT                    (27U)
/*! BSVIE - BSVIE */
#define USB_OTGSC_BSVIE(x)                       (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_BSVIE_SHIFT)) & USB_OTGSC_BSVIE_MASK)

#define USB_OTGSC_BSEIE_MASK                     (0x10000000U)
#define USB_OTGSC_BSEIE_SHIFT                    (28U)
/*! BSEIE - BSEIE */
#define USB_OTGSC_BSEIE(x)                       (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_BSEIE_SHIFT)) & USB_OTGSC_BSEIE_MASK)

#define USB_OTGSC_EN_1MS_MASK                    (0x20000000U)
#define USB_OTGSC_EN_1MS_SHIFT                   (29U)
/*! EN_1MS - EN_1MS */
#define USB_OTGSC_EN_1MS(x)                      (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_EN_1MS_SHIFT)) & USB_OTGSC_EN_1MS_MASK)

#define USB_OTGSC_DPIE_MASK                      (0x40000000U)
#define USB_OTGSC_DPIE_SHIFT                     (30U)
/*! DPIE - DPIE */
#define USB_OTGSC_DPIE(x)                        (((uint32_t)(((uint32_t)(x)) << USB_OTGSC_DPIE_SHIFT)) & USB_OTGSC_DPIE_MASK)
/*! @} */

/*! @name USBMODE - USB Device Mode */
/*! @{ */

#define USB_USBMODE_CM_MASK                      (0x3U)
#define USB_USBMODE_CM_SHIFT                     (0U)
/*! CM - CM
 *  0b00..Idle [Default for combination host/device]
 *  0b01..Reserved
 *  0b10..Device Controller [Default for device only controller]
 *  0b11..Host Controller [Default for host only controller]
 */
#define USB_USBMODE_CM(x)                        (((uint32_t)(((uint32_t)(x)) << USB_USBMODE_CM_SHIFT)) & USB_USBMODE_CM_MASK)

#define USB_USBMODE_ES_MASK                      (0x4U)
#define USB_USBMODE_ES_SHIFT                     (2U)
/*! ES - ES
 *  0b0..Little Endian [Default]
 *  0b1..Big Endian
 */
#define USB_USBMODE_ES(x)                        (((uint32_t)(((uint32_t)(x)) << USB_USBMODE_ES_SHIFT)) & USB_USBMODE_ES_MASK)

#define USB_USBMODE_SLOM_MASK                    (0x8U)
#define USB_USBMODE_SLOM_SHIFT                   (3U)
/*! SLOM - SLOM
 *  0b0..Setup Lockouts On (default);
 *  0b1..Setup Lockouts Off
 */
#define USB_USBMODE_SLOM(x)                      (((uint32_t)(((uint32_t)(x)) << USB_USBMODE_SLOM_SHIFT)) & USB_USBMODE_SLOM_MASK)

#define USB_USBMODE_SDIS_MASK                    (0x10U)
#define USB_USBMODE_SDIS_SHIFT                   (4U)
/*! SDIS - SDIS */
#define USB_USBMODE_SDIS(x)                      (((uint32_t)(((uint32_t)(x)) << USB_USBMODE_SDIS_SHIFT)) & USB_USBMODE_SDIS_MASK)
/*! @} */

/*! @name ENDPTSETUPSTAT - Endpoint Setup Status */
/*! @{ */

#define USB_ENDPTSETUPSTAT_ENDPTSETUPSTAT_MASK   (0xFFFFU)
#define USB_ENDPTSETUPSTAT_ENDPTSETUPSTAT_SHIFT  (0U)
/*! ENDPTSETUPSTAT - ENDPTSETUPSTAT */
#define USB_ENDPTSETUPSTAT_ENDPTSETUPSTAT(x)     (((uint32_t)(((uint32_t)(x)) << USB_ENDPTSETUPSTAT_ENDPTSETUPSTAT_SHIFT)) & USB_ENDPTSETUPSTAT_ENDPTSETUPSTAT_MASK)
/*! @} */

/*! @name ENDPTPRIME - Endpoint Prime */
/*! @{ */

#define USB_ENDPTPRIME_PERB_MASK                 (0xFFU)
#define USB_ENDPTPRIME_PERB_SHIFT                (0U)
/*! PERB - PERB */
#define USB_ENDPTPRIME_PERB(x)                   (((uint32_t)(((uint32_t)(x)) << USB_ENDPTPRIME_PERB_SHIFT)) & USB_ENDPTPRIME_PERB_MASK)

#define USB_ENDPTPRIME_PETB_MASK                 (0xFF0000U)
#define USB_ENDPTPRIME_PETB_SHIFT                (16U)
/*! PETB - PETB */
#define USB_ENDPTPRIME_PETB(x)                   (((uint32_t)(((uint32_t)(x)) << USB_ENDPTPRIME_PETB_SHIFT)) & USB_ENDPTPRIME_PETB_MASK)
/*! @} */

/*! @name ENDPTFLUSH - Endpoint Flush */
/*! @{ */

#define USB_ENDPTFLUSH_FERB_MASK                 (0xFFU)
#define USB_ENDPTFLUSH_FERB_SHIFT                (0U)
/*! FERB - FERB */
#define USB_ENDPTFLUSH_FERB(x)                   (((uint32_t)(((uint32_t)(x)) << USB_ENDPTFLUSH_FERB_SHIFT)) & USB_ENDPTFLUSH_FERB_MASK)

#define USB_ENDPTFLUSH_FETB_MASK                 (0xFF0000U)
#define USB_ENDPTFLUSH_FETB_SHIFT                (16U)
/*! FETB - FETB */
#define USB_ENDPTFLUSH_FETB(x)                   (((uint32_t)(((uint32_t)(x)) << USB_ENDPTFLUSH_FETB_SHIFT)) & USB_ENDPTFLUSH_FETB_MASK)
/*! @} */

/*! @name ENDPTSTAT - Endpoint Status */
/*! @{ */

#define USB_ENDPTSTAT_ERBR_MASK                  (0xFFU)
#define USB_ENDPTSTAT_ERBR_SHIFT                 (0U)
/*! ERBR - ERBR */
#define USB_ENDPTSTAT_ERBR(x)                    (((uint32_t)(((uint32_t)(x)) << USB_ENDPTSTAT_ERBR_SHIFT)) & USB_ENDPTSTAT_ERBR_MASK)

#define USB_ENDPTSTAT_ETBR_MASK                  (0xFF0000U)
#define USB_ENDPTSTAT_ETBR_SHIFT                 (16U)
/*! ETBR - ETBR */
#define USB_ENDPTSTAT_ETBR(x)                    (((uint32_t)(((uint32_t)(x)) << USB_ENDPTSTAT_ETBR_SHIFT)) & USB_ENDPTSTAT_ETBR_MASK)
/*! @} */

/*! @name ENDPTCOMPLETE - Endpoint Complete */
/*! @{ */

#define USB_ENDPTCOMPLETE_ERCE_MASK              (0xFFU)
#define USB_ENDPTCOMPLETE_ERCE_SHIFT             (0U)
/*! ERCE - ERCE */
#define USB_ENDPTCOMPLETE_ERCE(x)                (((uint32_t)(((uint32_t)(x)) << USB_ENDPTCOMPLETE_ERCE_SHIFT)) & USB_ENDPTCOMPLETE_ERCE_MASK)

#define USB_ENDPTCOMPLETE_ETCE_MASK              (0xFF0000U)
#define USB_ENDPTCOMPLETE_ETCE_SHIFT             (16U)
/*! ETCE - ETCE */
#define USB_ENDPTCOMPLETE_ETCE(x)                (((uint32_t)(((uint32_t)(x)) << USB_ENDPTCOMPLETE_ETCE_SHIFT)) & USB_ENDPTCOMPLETE_ETCE_MASK)
/*! @} */

/*! @name ENDPTCTRL0 - Endpoint Control0 */
/*! @{ */

#define USB_ENDPTCTRL0_RXS_MASK                  (0x1U)
#define USB_ENDPTCTRL0_RXS_SHIFT                 (0U)
/*! RXS - RXS */
#define USB_ENDPTCTRL0_RXS(x)                    (((uint32_t)(((uint32_t)(x)) << USB_ENDPTCTRL0_RXS_SHIFT)) & USB_ENDPTCTRL0_RXS_MASK)

#define USB_ENDPTCTRL0_RXT_MASK                  (0xCU)
#define USB_ENDPTCTRL0_RXT_SHIFT                 (2U)
/*! RXT - RXT */
#define USB_ENDPTCTRL0_RXT(x)                    (((uint32_t)(((uint32_t)(x)) << USB_ENDPTCTRL0_RXT_SHIFT)) & USB_ENDPTCTRL0_RXT_MASK)

#define USB_ENDPTCTRL0_RXE_MASK                  (0x80U)
#define USB_ENDPTCTRL0_RXE_SHIFT                 (7U)
/*! RXE - RXE */
#define USB_ENDPTCTRL0_RXE(x)                    (((uint32_t)(((uint32_t)(x)) << USB_ENDPTCTRL0_RXE_SHIFT)) & USB_ENDPTCTRL0_RXE_MASK)

#define USB_ENDPTCTRL0_TXS_MASK                  (0x10000U)
#define USB_ENDPTCTRL0_TXS_SHIFT                 (16U)
/*! TXS - TXS */
#define USB_ENDPTCTRL0_TXS(x)                    (((uint32_t)(((uint32_t)(x)) << USB_ENDPTCTRL0_TXS_SHIFT)) & USB_ENDPTCTRL0_TXS_MASK)

#define USB_ENDPTCTRL0_TXT_MASK                  (0xC0000U)
#define USB_ENDPTCTRL0_TXT_SHIFT                 (18U)
/*! TXT - TXT */
#define USB_ENDPTCTRL0_TXT(x)                    (((uint32_t)(((uint32_t)(x)) << USB_ENDPTCTRL0_TXT_SHIFT)) & USB_ENDPTCTRL0_TXT_MASK)

#define USB_ENDPTCTRL0_TXE_MASK                  (0x800000U)
#define USB_ENDPTCTRL0_TXE_SHIFT                 (23U)
/*! TXE - TXE */
#define USB_ENDPTCTRL0_TXE(x)                    (((uint32_t)(((uint32_t)(x)) << USB_ENDPTCTRL0_TXE_SHIFT)) & USB_ENDPTCTRL0_TXE_MASK)
/*! @} */

/*! @name ENDPTCTRL - Endpoint Control 1..Endpoint Control 7 */
/*! @{ */

#define USB_ENDPTCTRL_RXS_MASK                   (0x1U)
#define USB_ENDPTCTRL_RXS_SHIFT                  (0U)
/*! RXS - RXS */
#define USB_ENDPTCTRL_RXS(x)                     (((uint32_t)(((uint32_t)(x)) << USB_ENDPTCTRL_RXS_SHIFT)) & USB_ENDPTCTRL_RXS_MASK)

#define USB_ENDPTCTRL_RXD_MASK                   (0x2U)
#define USB_ENDPTCTRL_RXD_SHIFT                  (1U)
/*! RXD - RXD */
#define USB_ENDPTCTRL_RXD(x)                     (((uint32_t)(((uint32_t)(x)) << USB_ENDPTCTRL_RXD_SHIFT)) & USB_ENDPTCTRL_RXD_MASK)

#define USB_ENDPTCTRL_RXT_MASK                   (0xCU)
#define USB_ENDPTCTRL_RXT_SHIFT                  (2U)
/*! RXT - RXT */
#define USB_ENDPTCTRL_RXT(x)                     (((uint32_t)(((uint32_t)(x)) << USB_ENDPTCTRL_RXT_SHIFT)) & USB_ENDPTCTRL_RXT_MASK)

#define USB_ENDPTCTRL_RXI_MASK                   (0x20U)
#define USB_ENDPTCTRL_RXI_SHIFT                  (5U)
/*! RXI - RXI */
#define USB_ENDPTCTRL_RXI(x)                     (((uint32_t)(((uint32_t)(x)) << USB_ENDPTCTRL_RXI_SHIFT)) & USB_ENDPTCTRL_RXI_MASK)

#define USB_ENDPTCTRL_RXR_MASK                   (0x40U)
#define USB_ENDPTCTRL_RXR_SHIFT                  (6U)
/*! RXR - RXR */
#define USB_ENDPTCTRL_RXR(x)                     (((uint32_t)(((uint32_t)(x)) << USB_ENDPTCTRL_RXR_SHIFT)) & USB_ENDPTCTRL_RXR_MASK)

#define USB_ENDPTCTRL_RXE_MASK                   (0x80U)
#define USB_ENDPTCTRL_RXE_SHIFT                  (7U)
/*! RXE - RXE */
#define USB_ENDPTCTRL_RXE(x)                     (((uint32_t)(((uint32_t)(x)) << USB_ENDPTCTRL_RXE_SHIFT)) & USB_ENDPTCTRL_RXE_MASK)

#define USB_ENDPTCTRL_TXS_MASK                   (0x10000U)
#define USB_ENDPTCTRL_TXS_SHIFT                  (16U)
/*! TXS - TXS */
#define USB_ENDPTCTRL_TXS(x)                     (((uint32_t)(((uint32_t)(x)) << USB_ENDPTCTRL_TXS_SHIFT)) & USB_ENDPTCTRL_TXS_MASK)

#define USB_ENDPTCTRL_TXD_MASK                   (0x20000U)
#define USB_ENDPTCTRL_TXD_SHIFT                  (17U)
/*! TXD - TXD */
#define USB_ENDPTCTRL_TXD(x)                     (((uint32_t)(((uint32_t)(x)) << USB_ENDPTCTRL_TXD_SHIFT)) & USB_ENDPTCTRL_TXD_MASK)

#define USB_ENDPTCTRL_TXT_MASK                   (0xC0000U)
#define USB_ENDPTCTRL_TXT_SHIFT                  (18U)
/*! TXT - TXT */
#define USB_ENDPTCTRL_TXT(x)                     (((uint32_t)(((uint32_t)(x)) << USB_ENDPTCTRL_TXT_SHIFT)) & USB_ENDPTCTRL_TXT_MASK)

#define USB_ENDPTCTRL_TXI_MASK                   (0x200000U)
#define USB_ENDPTCTRL_TXI_SHIFT                  (21U)
/*! TXI - TXI */
#define USB_ENDPTCTRL_TXI(x)                     (((uint32_t)(((uint32_t)(x)) << USB_ENDPTCTRL_TXI_SHIFT)) & USB_ENDPTCTRL_TXI_MASK)

#define USB_ENDPTCTRL_TXR_MASK                   (0x400000U)
#define USB_ENDPTCTRL_TXR_SHIFT                  (22U)
/*! TXR - TXR */
#define USB_ENDPTCTRL_TXR(x)                     (((uint32_t)(((uint32_t)(x)) << USB_ENDPTCTRL_TXR_SHIFT)) & USB_ENDPTCTRL_TXR_MASK)

#define USB_ENDPTCTRL_TXE_MASK                   (0x800000U)
#define USB_ENDPTCTRL_TXE_SHIFT                  (23U)
/*! TXE - TXE */
#define USB_ENDPTCTRL_TXE(x)                     (((uint32_t)(((uint32_t)(x)) << USB_ENDPTCTRL_TXE_SHIFT)) & USB_ENDPTCTRL_TXE_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group USB_Register_Masks */

/* Backward compatibility */
#define GPTIMER0CTL                              GPTIMER0CTRL
#define GPTIMER1CTL                              GPTIMER1CTRL
#define USB_SBUSCFG                              SBUSCFG
#define EPLISTADDR                               ENDPTLISTADDR
#define EPSETUPSR                                ENDPTSETUPSTAT
#define EPPRIME                                  ENDPTPRIME
#define EPFLUSH                                  ENDPTFLUSH
#define EPSR                                     ENDPTSTAT
#define EPCOMPLETE                               ENDPTCOMPLETE
#define EPCR                                     ENDPTCTRL
#define EPCR0                                    ENDPTCTRL0
#define USBHS_ID_ID_MASK                         USB_ID_ID_MASK
#define USBHS_ID_ID_SHIFT                        USB_ID_ID_SHIFT
#define USBHS_ID_ID(x)                           USB_ID_ID(x)
#define USBHS_ID_NID_MASK                        USB_ID_NID_MASK
#define USBHS_ID_NID_SHIFT                       USB_ID_NID_SHIFT
#define USBHS_ID_NID(x)                          USB_ID_NID(x)
#define USBHS_ID_REVISION_MASK                   USB_ID_REVISION_MASK
#define USBHS_ID_REVISION_SHIFT                  USB_ID_REVISION_SHIFT
#define USBHS_ID_REVISION(x)                     USB_ID_REVISION(x)
#define USBHS_HWGENERAL_PHYW_MASK                USB_HWGENERAL_PHYW_MASK
#define USBHS_HWGENERAL_PHYW_SHIFT               USB_HWGENERAL_PHYW_SHIFT
#define USBHS_HWGENERAL_PHYW(x)                  USB_HWGENERAL_PHYW(x)
#define USBHS_HWGENERAL_PHYM_MASK                USB_HWGENERAL_PHYM_MASK
#define USBHS_HWGENERAL_PHYM_SHIFT               USB_HWGENERAL_PHYM_SHIFT
#define USBHS_HWGENERAL_PHYM(x)                  USB_HWGENERAL_PHYM(x)
#define USBHS_HWGENERAL_SM_MASK                  USB_HWGENERAL_SM_MASK
#define USBHS_HWGENERAL_SM_SHIFT                 USB_HWGENERAL_SM_SHIFT
#define USBHS_HWGENERAL_SM(x)                    USB_HWGENERAL_SM(x)
#define USBHS_HWHOST_HC_MASK                     USB_HWHOST_HC_MASK
#define USBHS_HWHOST_HC_SHIFT                    USB_HWHOST_HC_SHIFT
#define USBHS_HWHOST_HC(x)                       USB_HWHOST_HC(x)
#define USBHS_HWHOST_NPORT_MASK                  USB_HWHOST_NPORT_MASK
#define USBHS_HWHOST_NPORT_SHIFT                 USB_HWHOST_NPORT_SHIFT
#define USBHS_HWHOST_NPORT(x)                    USB_HWHOST_NPORT(x)
#define USBHS_HWDEVICE_DC_MASK                   USB_HWDEVICE_DC_MASK
#define USBHS_HWDEVICE_DC_SHIFT                  USB_HWDEVICE_DC_SHIFT
#define USBHS_HWDEVICE_DC(x)                     USB_HWDEVICE_DC(x)
#define USBHS_HWDEVICE_DEVEP_MASK                USB_HWDEVICE_DEVEP_MASK
#define USBHS_HWDEVICE_DEVEP_SHIFT               USB_HWDEVICE_DEVEP_SHIFT
#define USBHS_HWDEVICE_DEVEP(x)                  USB_HWDEVICE_DEVEP(x)
#define USBHS_HWTXBUF_TXBURST_MASK               USB_HWTXBUF_TXBURST_MASK
#define USBHS_HWTXBUF_TXBURST_SHIFT              USB_HWTXBUF_TXBURST_SHIFT
#define USBHS_HWTXBUF_TXBURST(x)                 USB_HWTXBUF_TXBURST(x)
#define USBHS_HWTXBUF_TXCHANADD_MASK             USB_HWTXBUF_TXCHANADD_MASK
#define USBHS_HWTXBUF_TXCHANADD_SHIFT            USB_HWTXBUF_TXCHANADD_SHIFT
#define USBHS_HWTXBUF_TXCHANADD(x)               USB_HWTXBUF_TXCHANADD(x)
#define USBHS_HWRXBUF_RXBURST_MASK               USB_HWRXBUF_RXBURST_MASK
#define USBHS_HWRXBUF_RXBURST_SHIFT              USB_HWRXBUF_RXBURST_SHIFT
#define USBHS_HWRXBUF_RXBURST(x)                 USB_HWRXBUF_RXBURST(x)
#define USBHS_HWRXBUF_RXADD_MASK                 USB_HWRXBUF_RXADD_MASK
#define USBHS_HWRXBUF_RXADD_SHIFT                USB_HWRXBUF_RXADD_SHIFT
#define USBHS_HWRXBUF_RXADD(x)                   USB_HWRXBUF_RXADD(x)
#define USBHS_GPTIMER0LD_GPTLD_MASK              USB_GPTIMER0LD_GPTLD_MASK
#define USBHS_GPTIMER0LD_GPTLD_SHIFT             USB_GPTIMER0LD_GPTLD_SHIFT
#define USBHS_GPTIMER0LD_GPTLD(x)                USB_GPTIMER0LD_GPTLD(x)
#define USBHS_GPTIMER0CTL_GPTCNT_MASK            USB_GPTIMER0CTRL_GPTCNT_MASK
#define USBHS_GPTIMER0CTL_GPTCNT_SHIFT           USB_GPTIMER0CTRL_GPTCNT_SHIFT
#define USBHS_GPTIMER0CTL_GPTCNT(x)              USB_GPTIMER0CTRL_GPTCNT(x)
#define USBHS_GPTIMER0CTL_MODE_MASK              USB_GPTIMER0CTRL_GPTMODE_MASK
#define USBHS_GPTIMER0CTL_MODE_SHIFT             USB_GPTIMER0CTRL_GPTMODE_SHIFT
#define USBHS_GPTIMER0CTL_MODE(x)                USB_GPTIMER0CTRL_GPTMODE(x)
#define USBHS_GPTIMER0CTL_RST_MASK               USB_GPTIMER0CTRL_GPTRST_MASK
#define USBHS_GPTIMER0CTL_RST_SHIFT              USB_GPTIMER0CTRL_GPTRST_SHIFT
#define USBHS_GPTIMER0CTL_RST(x)                 USB_GPTIMER0CTRL_GPTRST(x)
#define USBHS_GPTIMER0CTL_RUN_MASK               USB_GPTIMER0CTRL_GPTRUN_MASK
#define USBHS_GPTIMER0CTL_RUN_SHIFT              USB_GPTIMER0CTRL_GPTRUN_SHIFT
#define USBHS_GPTIMER0CTL_RUN(x)                 USB_GPTIMER0CTRL_GPTRUN(x)
#define USBHS_GPTIMER1LD_GPTLD_MASK              USB_GPTIMER1LD_GPTLD_MASK
#define USBHS_GPTIMER1LD_GPTLD_SHIFT             USB_GPTIMER1LD_GPTLD_SHIFT
#define USBHS_GPTIMER1LD_GPTLD(x)                USB_GPTIMER1LD_GPTLD(x)
#define USBHS_GPTIMER1CTL_GPTCNT_MASK            USB_GPTIMER1CTRL_GPTCNT_MASK
#define USBHS_GPTIMER1CTL_GPTCNT_SHIFT           USB_GPTIMER1CTRL_GPTCNT_SHIFT
#define USBHS_GPTIMER1CTL_GPTCNT(x)              USB_GPTIMER1CTRL_GPTCNT(x)
#define USBHS_GPTIMER1CTL_MODE_MASK              USB_GPTIMER1CTRL_GPTMODE_MASK
#define USBHS_GPTIMER1CTL_MODE_SHIFT             USB_GPTIMER1CTRL_GPTMODE_SHIFT
#define USBHS_GPTIMER1CTL_MODE(x)                USB_GPTIMER1CTRL_GPTMODE(x)
#define USBHS_GPTIMER1CTL_RST_MASK               USB_GPTIMER1CTRL_GPTRST_MASK
#define USBHS_GPTIMER1CTL_RST_SHIFT              USB_GPTIMER1CTRL_GPTRST_SHIFT
#define USBHS_GPTIMER1CTL_RST(x)                 USB_GPTIMER1CTRL_GPTRST(x)
#define USBHS_GPTIMER1CTL_RUN_MASK               USB_GPTIMER1CTRL_GPTRUN_MASK
#define USBHS_GPTIMER1CTL_RUN_SHIFT              USB_GPTIMER1CTRL_GPTRUN_SHIFT
#define USBHS_GPTIMER1CTL_RUN(x)                 USB_GPTIMER1CTRL_GPTRUN(x)
#define USBHS_USB_SBUSCFG_BURSTMODE_MASK         USB_SBUSCFG_AHBBRST_MASK
#define USBHS_USB_SBUSCFG_BURSTMODE_SHIFT        USB_SBUSCFG_AHBBRST_SHIFT
#define USBHS_USB_SBUSCFG_BURSTMODE(x)           USB_SBUSCFG_AHBBRST(x)
#define USBHS_HCIVERSION_CAPLENGTH(x)            USB_HCIVERSION_CAPLENGTH(x)
#define USBHS_HCIVERSION_HCIVERSION_MASK         USB_HCIVERSION_HCIVERSION_MASK
#define USBHS_HCIVERSION_HCIVERSION_SHIFT        USB_HCIVERSION_HCIVERSION_SHIFT
#define USBHS_HCIVERSION_HCIVERSION(x)           USB_HCIVERSION_HCIVERSION(x)
#define USBHS_HCSPARAMS_N_PORTS_MASK             USB_HCSPARAMS_N_PORTS_MASK
#define USBHS_HCSPARAMS_N_PORTS_SHIFT            USB_HCSPARAMS_N_PORTS_SHIFT
#define USBHS_HCSPARAMS_N_PORTS(x)               USB_HCSPARAMS_N_PORTS(x)
#define USBHS_HCSPARAMS_PPC_MASK                 USB_HCSPARAMS_PPC_MASK
#define USBHS_HCSPARAMS_PPC_SHIFT                USB_HCSPARAMS_PPC_SHIFT
#define USBHS_HCSPARAMS_PPC(x)                   USB_HCSPARAMS_PPC(x)
#define USBHS_HCSPARAMS_N_PCC_MASK               USB_HCSPARAMS_N_PCC_MASK
#define USBHS_HCSPARAMS_N_PCC_SHIFT              USB_HCSPARAMS_N_PCC_SHIFT
#define USBHS_HCSPARAMS_N_PCC(x)                 USB_HCSPARAMS_N_PCC(x)
#define USBHS_HCSPARAMS_N_CC_MASK                USB_HCSPARAMS_N_CC_MASK
#define USBHS_HCSPARAMS_N_CC_SHIFT               USB_HCSPARAMS_N_CC_SHIFT
#define USBHS_HCSPARAMS_N_CC(x)                  USB_HCSPARAMS_N_CC(x)
#define USBHS_HCSPARAMS_PI_MASK                  USB_HCSPARAMS_PI_MASK
#define USBHS_HCSPARAMS_PI_SHIFT                 USB_HCSPARAMS_PI_SHIFT
#define USBHS_HCSPARAMS_PI(x)                    USB_HCSPARAMS_PI(x)
#define USBHS_HCSPARAMS_N_PTT_MASK               USB_HCSPARAMS_N_PTT_MASK
#define USBHS_HCSPARAMS_N_PTT_SHIFT              USB_HCSPARAMS_N_PTT_SHIFT
#define USBHS_HCSPARAMS_N_PTT(x)                 USB_HCSPARAMS_N_PTT(x)
#define USBHS_HCSPARAMS_N_TT_MASK                USB_HCSPARAMS_N_TT_MASK
#define USBHS_HCSPARAMS_N_TT_SHIFT               USB_HCSPARAMS_N_TT_SHIFT
#define USBHS_HCSPARAMS_N_TT(x)                  USB_HCSPARAMS_N_TT(x)
#define USBHS_HCCPARAMS_ADC_MASK                 USB_HCCPARAMS_ADC_MASK
#define USBHS_HCCPARAMS_ADC_SHIFT                USB_HCCPARAMS_ADC_SHIFT
#define USBHS_HCCPARAMS_ADC(x)                   USB_HCCPARAMS_ADC(x)
#define USBHS_HCCPARAMS_PFL_MASK                 USB_HCCPARAMS_PFL_MASK
#define USBHS_HCCPARAMS_PFL_SHIFT                USB_HCCPARAMS_PFL_SHIFT
#define USBHS_HCCPARAMS_PFL(x)                   USB_HCCPARAMS_PFL(x)
#define USBHS_HCCPARAMS_ASP_MASK                 USB_HCCPARAMS_ASP_MASK
#define USBHS_HCCPARAMS_ASP_SHIFT                USB_HCCPARAMS_ASP_SHIFT
#define USBHS_HCCPARAMS_ASP(x)                   USB_HCCPARAMS_ASP(x)
#define USBHS_HCCPARAMS_IST_MASK                 USB_HCCPARAMS_IST_MASK
#define USBHS_HCCPARAMS_IST_SHIFT                USB_HCCPARAMS_IST_SHIFT
#define USBHS_HCCPARAMS_IST(x)                   USB_HCCPARAMS_IST(x)
#define USBHS_HCCPARAMS_EECP_MASK                USB_HCCPARAMS_EECP_MASK
#define USBHS_HCCPARAMS_EECP_SHIFT               USB_HCCPARAMS_EECP_SHIFT
#define USBHS_HCCPARAMS_EECP(x)                  USB_HCCPARAMS_EECP(x)
#define USBHS_DCIVERSION_DCIVERSION_MASK         USB_DCIVERSION_DCIVERSION_MASK
#define USBHS_DCIVERSION_DCIVERSION_SHIFT        USB_DCIVERSION_DCIVERSION_SHIFT
#define USBHS_DCIVERSION_DCIVERSION(x)           USB_DCIVERSION_DCIVERSION(x)
#define USBHS_DCCPARAMS_DEN_MASK                 USB_DCCPARAMS_DEN_MASK
#define USBHS_DCCPARAMS_DEN_SHIFT                USB_DCCPARAMS_DEN_SHIFT
#define USBHS_DCCPARAMS_DEN(x)                   USB_DCCPARAMS_DEN(x)
#define USBHS_DCCPARAMS_DC_MASK                  USB_DCCPARAMS_DC_MASK
#define USBHS_DCCPARAMS_DC_SHIFT                 USB_DCCPARAMS_DC_SHIFT
#define USBHS_DCCPARAMS_DC(x)                    USB_DCCPARAMS_DC(x)
#define USBHS_DCCPARAMS_HC_MASK                  USB_DCCPARAMS_HC_MASK
#define USBHS_DCCPARAMS_HC_SHIFT                 USB_DCCPARAMS_HC_SHIFT
#define USBHS_DCCPARAMS_HC(x)                    USB_DCCPARAMS_HC(x)
#define USBHS_USBCMD_RS_MASK                     USB_USBCMD_RS_MASK
#define USBHS_USBCMD_RS_SHIFT                    USB_USBCMD_RS_SHIFT
#define USBHS_USBCMD_RS(x)                       USB_USBCMD_RS(x)
#define USBHS_USBCMD_RST_MASK                    USB_USBCMD_RST_MASK
#define USBHS_USBCMD_RST_SHIFT                   USB_USBCMD_RST_SHIFT
#define USBHS_USBCMD_RST(x)                      USB_USBCMD_RST(x)
#define USBHS_USBCMD_FS_MASK                     USB_USBCMD_FS_1_MASK
#define USBHS_USBCMD_FS_SHIFT                    USB_USBCMD_FS_1_SHIFT
#define USBHS_USBCMD_FS(x)                       USB_USBCMD_FS_1(x)
#define USBHS_USBCMD_PSE_MASK                    USB_USBCMD_PSE_MASK
#define USBHS_USBCMD_PSE_SHIFT                   USB_USBCMD_PSE_SHIFT
#define USBHS_USBCMD_PSE(x)                      USB_USBCMD_PSE(x)
#define USBHS_USBCMD_ASE_MASK                    USB_USBCMD_ASE_MASK
#define USBHS_USBCMD_ASE_SHIFT                   USB_USBCMD_ASE_SHIFT
#define USBHS_USBCMD_ASE(x)                      USB_USBCMD_ASE(x)
#define USBHS_USBCMD_IAA_MASK                    USB_USBCMD_IAA_MASK
#define USBHS_USBCMD_IAA_SHIFT                   USB_USBCMD_IAA_SHIFT
#define USBHS_USBCMD_IAA(x)                      USB_USBCMD_IAA(x)
#define USBHS_USBCMD_ASP_MASK                    USB_USBCMD_ASP_MASK
#define USBHS_USBCMD_ASP_SHIFT                   USB_USBCMD_ASP_SHIFT
#define USBHS_USBCMD_ASP(x)                      USB_USBCMD_ASP(x)
#define USBHS_USBCMD_ASPE_MASK                   USB_USBCMD_ASPE_MASK
#define USBHS_USBCMD_ASPE_SHIFT                  USB_USBCMD_ASPE_SHIFT
#define USBHS_USBCMD_ASPE(x)                     USB_USBCMD_ASPE(x)
#define USBHS_USBCMD_ATDTW_MASK                  USB_USBCMD_ATDTW_MASK
#define USBHS_USBCMD_ATDTW_SHIFT                 USB_USBCMD_ATDTW_SHIFT
#define USBHS_USBCMD_ATDTW(x)                    USB_USBCMD_ATDTW(x)
#define USBHS_USBCMD_SUTW_MASK                   USB_USBCMD_SUTW_MASK
#define USBHS_USBCMD_SUTW_SHIFT                  USB_USBCMD_SUTW_SHIFT
#define USBHS_USBCMD_SUTW(x)                     USB_USBCMD_SUTW(x)
#define USBHS_USBCMD_FS2_MASK                    USB_USBCMD_FS_2_MASK
#define USBHS_USBCMD_FS2_SHIFT                   USB_USBCMD_FS_2_SHIFT
#define USBHS_USBCMD_FS2(x)                      USB_USBCMD_FS_2(x)
#define USBHS_USBCMD_ITC_MASK                    USB_USBCMD_ITC_MASK
#define USBHS_USBCMD_ITC_SHIFT                   USB_USBCMD_ITC_SHIFT
#define USBHS_USBCMD_ITC(x)                      USB_USBCMD_ITC(x)
#define USBHS_USBSTS_UI_MASK                     USB_USBSTS_UI_MASK
#define USBHS_USBSTS_UI_SHIFT                    USB_USBSTS_UI_SHIFT
#define USBHS_USBSTS_UI(x)                       USB_USBSTS_UI(x)
#define USBHS_USBSTS_UEI_MASK                    USB_USBSTS_UEI_MASK
#define USBHS_USBSTS_UEI_SHIFT                   USB_USBSTS_UEI_SHIFT
#define USBHS_USBSTS_UEI(x)                      USB_USBSTS_UEI(x)
#define USBHS_USBSTS_PCI_MASK                    USB_USBSTS_PCI_MASK
#define USBHS_USBSTS_PCI_SHIFT                   USB_USBSTS_PCI_SHIFT
#define USBHS_USBSTS_PCI(x)                      USB_USBSTS_PCI(x)
#define USBHS_USBSTS_FRI_MASK                    USB_USBSTS_FRI_MASK
#define USBHS_USBSTS_FRI_SHIFT                   USB_USBSTS_FRI_SHIFT
#define USBHS_USBSTS_FRI(x)                      USB_USBSTS_FRI(x)
#define USBHS_USBSTS_SEI_MASK                    USB_USBSTS_SEI_MASK
#define USBHS_USBSTS_SEI_SHIFT                   USB_USBSTS_SEI_SHIFT
#define USBHS_USBSTS_SEI(x)                      USB_USBSTS_SEI(x)
#define USBHS_USBSTS_AAI_MASK                    USB_USBSTS_AAI_MASK
#define USBHS_USBSTS_AAI_SHIFT                   USB_USBSTS_AAI_SHIFT
#define USBHS_USBSTS_AAI(x)                      USB_USBSTS_AAI(x)
#define USBHS_USBSTS_URI_MASK                    USB_USBSTS_URI_MASK
#define USBHS_USBSTS_URI_SHIFT                   USB_USBSTS_URI_SHIFT
#define USBHS_USBSTS_URI(x)                      USB_USBSTS_URI(x)
#define USBHS_USBSTS_SRI_MASK                    USB_USBSTS_SRI_MASK
#define USBHS_USBSTS_SRI_SHIFT                   USB_USBSTS_SRI_SHIFT
#define USBHS_USBSTS_SRI(x)                      USB_USBSTS_SRI(x)
#define USBHS_USBSTS_SLI_MASK                    USB_USBSTS_SLI_MASK
#define USBHS_USBSTS_SLI_SHIFT                   USB_USBSTS_SLI_SHIFT
#define USBHS_USBSTS_SLI(x)                      USB_USBSTS_SLI(x)
#define USBHS_USBSTS_ULPII_MASK                  USB_USBSTS_ULPII_MASK
#define USBHS_USBSTS_ULPII_SHIFT                 USB_USBSTS_ULPII_SHIFT
#define USBHS_USBSTS_ULPII(x)                    USB_USBSTS_ULPII(x)
#define USBHS_USBSTS_HCH_MASK                    USB_USBSTS_HCH_MASK
#define USBHS_USBSTS_HCH_SHIFT                   USB_USBSTS_HCH_SHIFT
#define USBHS_USBSTS_HCH(x)                      USB_USBSTS_HCH(x)
#define USBHS_USBSTS_RCL_MASK                    USB_USBSTS_RCL_MASK
#define USBHS_USBSTS_RCL_SHIFT                   USB_USBSTS_RCL_SHIFT
#define USBHS_USBSTS_RCL(x)                      USB_USBSTS_RCL(x)
#define USBHS_USBSTS_PS_MASK                     USB_USBSTS_PS_MASK
#define USBHS_USBSTS_PS_SHIFT                    USB_USBSTS_PS_SHIFT
#define USBHS_USBSTS_PS(x)                       USB_USBSTS_PS(x)
#define USBHS_USBSTS_AS_MASK                     USB_USBSTS_AS_MASK
#define USBHS_USBSTS_AS_SHIFT                    USB_USBSTS_AS_SHIFT
#define USBHS_USBSTS_AS(x)                       USB_USBSTS_AS(x)
#define USBHS_USBSTS_NAKI_MASK                   USB_USBSTS_NAKI_MASK
#define USBHS_USBSTS_NAKI_SHIFT                  USB_USBSTS_NAKI_SHIFT
#define USBHS_USBSTS_NAKI(x)                     USB_USBSTS_NAKI(x)
#define USBHS_USBSTS_TI0_MASK                    USB_USBSTS_TI0_MASK
#define USBHS_USBSTS_TI0_SHIFT                   USB_USBSTS_TI0_SHIFT
#define USBHS_USBSTS_TI0(x)                      USB_USBSTS_TI0(x)
#define USBHS_USBSTS_TI1_MASK                    USB_USBSTS_TI1_MASK
#define USBHS_USBSTS_TI1_SHIFT                   USB_USBSTS_TI1_SHIFT
#define USBHS_USBSTS_TI1(x)                      USB_USBSTS_TI1(x)
#define USBHS_USBINTR_UE_MASK                    USB_USBINTR_UE_MASK
#define USBHS_USBINTR_UE_SHIFT                   USB_USBINTR_UE_SHIFT
#define USBHS_USBINTR_UE(x)                      USB_USBINTR_UE(x)
#define USBHS_USBINTR_UEE_MASK                   USB_USBINTR_UEE_MASK
#define USBHS_USBINTR_UEE_SHIFT                  USB_USBINTR_UEE_SHIFT
#define USBHS_USBINTR_UEE(x)                     USB_USBINTR_UEE(x)
#define USBHS_USBINTR_PCE_MASK                   USB_USBINTR_PCE_MASK
#define USBHS_USBINTR_PCE_SHIFT                  USB_USBINTR_PCE_SHIFT
#define USBHS_USBINTR_PCE(x)                     USB_USBINTR_PCE(x)
#define USBHS_USBINTR_FRE_MASK                   USB_USBINTR_FRE_MASK
#define USBHS_USBINTR_FRE_SHIFT                  USB_USBINTR_FRE_SHIFT
#define USBHS_USBINTR_FRE(x)                     USB_USBINTR_FRE(x)
#define USBHS_USBINTR_SEE_MASK                   USB_USBINTR_SEE_MASK
#define USBHS_USBINTR_SEE_SHIFT                  USB_USBINTR_SEE_SHIFT
#define USBHS_USBINTR_SEE(x)                     USB_USBINTR_SEE(x)
#define USBHS_USBINTR_AAE_MASK                   USB_USBINTR_AAE_MASK
#define USBHS_USBINTR_AAE_SHIFT                  USB_USBINTR_AAE_SHIFT
#define USBHS_USBINTR_AAE(x)                     USB_USBINTR_AAE(x)
#define USBHS_USBINTR_URE_MASK                   USB_USBINTR_URE_MASK
#define USBHS_USBINTR_URE_SHIFT                  USB_USBINTR_URE_SHIFT
#define USBHS_USBINTR_URE(x)                     USB_USBINTR_URE(x)
#define USBHS_USBINTR_SRE_MASK                   USB_USBINTR_SRE_MASK
#define USBHS_USBINTR_SRE_SHIFT                  USB_USBINTR_SRE_SHIFT
#define USBHS_USBINTR_SRE(x)                     USB_USBINTR_SRE(x)
#define USBHS_USBINTR_SLE_MASK                   USB_USBINTR_SLE_MASK
#define USBHS_USBINTR_SLE_SHIFT                  USB_USBINTR_SLE_SHIFT
#define USBHS_USBINTR_SLE(x)                     USB_USBINTR_SLE(x)
#define USBHS_USBINTR_ULPIE_MASK                 USB_USBINTR_ULPIE_MASK
#define USBHS_USBINTR_ULPIE_SHIFT                USB_USBINTR_ULPIE_SHIFT
#define USBHS_USBINTR_ULPIE(x)                   USB_USBINTR_ULPIE(x)
#define USBHS_USBINTR_NAKE_MASK                  USB_USBINTR_NAKE_MASK
#define USBHS_USBINTR_NAKE_SHIFT                 USB_USBINTR_NAKE_SHIFT
#define USBHS_USBINTR_NAKE(x)                    USB_USBINTR_NAKE(x)
#define USBHS_USBINTR_UAIE_MASK                  USB_USBINTR_UAIE_MASK
#define USBHS_USBINTR_UAIE_SHIFT                 USB_USBINTR_UAIE_SHIFT
#define USBHS_USBINTR_UAIE(x)                    USB_USBINTR_UAIE(x)
#define USBHS_USBINTR_UPIE_MASK                  USB_USBINTR_UPIE_MASK
#define USBHS_USBINTR_UPIE_SHIFT                 USB_USBINTR_UPIE_SHIFT
#define USBHS_USBINTR_UPIE(x)                    USB_USBINTR_UPIE(x)
#define USBHS_USBINTR_TIE0_MASK                  USB_USBINTR_TIE0_MASK
#define USBHS_USBINTR_TIE0_SHIFT                 USB_USBINTR_TIE0_SHIFT
#define USBHS_USBINTR_TIE0(x)                    USB_USBINTR_TIE0(x)
#define USBHS_USBINTR_TIE1_MASK                  USB_USBINTR_TIE1_MASK
#define USBHS_USBINTR_TIE1_SHIFT                 USB_USBINTR_TIE1_SHIFT
#define USBHS_USBINTR_TIE1(x)                    USB_USBINTR_TIE1(x)
#define USBHS_FRINDEX_FRINDEX_MASK               USB_FRINDEX_FRINDEX_MASK
#define USBHS_FRINDEX_FRINDEX_SHIFT              USB_FRINDEX_FRINDEX_SHIFT
#define USBHS_FRINDEX_FRINDEX(x)                 USB_FRINDEX_FRINDEX(x)
#define USBHS_DEVICEADDR_USBADRA_MASK            USB_DEVICEADDR_USBADRA_MASK
#define USBHS_DEVICEADDR_USBADRA_SHIFT           USB_DEVICEADDR_USBADRA_SHIFT
#define USBHS_DEVICEADDR_USBADRA(x)              USB_DEVICEADDR_USBADRA(x)
#define USBHS_DEVICEADDR_USBADR_MASK             USB_DEVICEADDR_USBADR_MASK
#define USBHS_DEVICEADDR_USBADR_SHIFT            USB_DEVICEADDR_USBADR_SHIFT
#define USBHS_DEVICEADDR_USBADR(x)               USB_DEVICEADDR_USBADR(x)
#define USBHS_PERIODICLISTBASE_PERBASE_MASK      USB_PERIODICLISTBASE_BASEADR_MASK
#define USBHS_PERIODICLISTBASE_PERBASE_SHIFT     USB_PERIODICLISTBASE_BASEADR_SHIFT
#define USBHS_PERIODICLISTBASE_PERBASE(x)        USB_PERIODICLISTBASE_BASEADR(x)
#define USBHS_ASYNCLISTADDR_ASYBASE_MASK         USB_ASYNCLISTADDR_ASYBASE_MASK
#define USBHS_ASYNCLISTADDR_ASYBASE_SHIFT        USB_ASYNCLISTADDR_ASYBASE_SHIFT
#define USBHS_ASYNCLISTADDR_ASYBASE(x)           USB_ASYNCLISTADDR_ASYBASE(x)
#define USBHS_EPLISTADDR_EPBASE_MASK             USB_ENDPTLISTADDR_EPBASE_MASK
#define USBHS_EPLISTADDR_EPBASE_SHIFT            USB_ENDPTLISTADDR_EPBASE_SHIFT
#define USBHS_EPLISTADDR_EPBASE(x)               USB_ENDPTLISTADDR_EPBASE(x)
#define USBHS_BURSTSIZE_RXPBURST_MASK            USB_BURSTSIZE_RXPBURST_MASK
#define USBHS_BURSTSIZE_RXPBURST_SHIFT           USB_BURSTSIZE_RXPBURST_SHIFT
#define USBHS_BURSTSIZE_RXPBURST(x)              USB_BURSTSIZE_RXPBURST(x)
#define USBHS_BURSTSIZE_TXPBURST_MASK            USB_BURSTSIZE_TXPBURST_MASK
#define USBHS_BURSTSIZE_TXPBURST_SHIFT           USB_BURSTSIZE_TXPBURST_SHIFT
#define USBHS_BURSTSIZE_TXPBURST(x)              USB_BURSTSIZE_TXPBURST(x)
#define USBHS_TXFILLTUNING_TXSCHOH_MASK          USB_TXFILLTUNING_TXSCHOH_MASK
#define USBHS_TXFILLTUNING_TXSCHOH_SHIFT         USB_TXFILLTUNING_TXSCHOH_SHIFT
#define USBHS_TXFILLTUNING_TXSCHOH(x)            USB_TXFILLTUNING_TXSCHOH(x)
#define USBHS_TXFILLTUNING_TXSCHHEALTH_MASK      USB_TXFILLTUNING_TXSCHHEALTH_MASK
#define USBHS_TXFILLTUNING_TXSCHHEALTH_SHIFT     USB_TXFILLTUNING_TXSCHHEALTH_SHIFT
#define USBHS_TXFILLTUNING_TXSCHHEALTH(x)        USB_TXFILLTUNING_TXSCHHEALTH(x)
#define USBHS_TXFILLTUNING_TXFIFOTHRES_MASK      USB_TXFILLTUNING_TXFIFOTHRES_MASK
#define USBHS_TXFILLTUNING_TXFIFOTHRES_SHIFT     USB_TXFILLTUNING_TXFIFOTHRES_SHIFT
#define USBHS_TXFILLTUNING_TXFIFOTHRES(x)        USB_TXFILLTUNING_TXFIFOTHRES(x)
#define USBHS_ENDPTNAK_EPRN_MASK                 USB_ENDPTNAK_EPRN_MASK
#define USBHS_ENDPTNAK_EPRN_SHIFT                USB_ENDPTNAK_EPRN_SHIFT
#define USBHS_ENDPTNAK_EPRN(x)                   USB_ENDPTNAK_EPRN(x)
#define USBHS_ENDPTNAK_EPTN_MASK                 USB_ENDPTNAK_EPTN_MASK
#define USBHS_ENDPTNAK_EPTN_SHIFT                USB_ENDPTNAK_EPTN_SHIFT
#define USBHS_ENDPTNAK_EPTN(x)                   USB_ENDPTNAK_EPTN(x)
#define USBHS_ENDPTNAKEN_EPRNE_MASK              USB_ENDPTNAKEN_EPRNE_MASK
#define USBHS_ENDPTNAKEN_EPRNE_SHIFT             USB_ENDPTNAKEN_EPRNE_SHIFT
#define USBHS_ENDPTNAKEN_EPRNE(x)                USB_ENDPTNAKEN_EPRNE(x)
#define USBHS_ENDPTNAKEN_EPTNE_MASK              USB_ENDPTNAKEN_EPTNE_MASK
#define USBHS_ENDPTNAKEN_EPTNE_SHIFT             USB_ENDPTNAKEN_EPTNE_SHIFT
#define USBHS_ENDPTNAKEN_EPTNE(x)                USB_ENDPTNAKEN_EPTNE(x)
#define USBHS_CONFIGFLAG_CF_MASK                 USB_CONFIGFLAG_CF_MASK
#define USBHS_CONFIGFLAG_CF_SHIFT                USB_CONFIGFLAG_CF_SHIFT
#define USBHS_CONFIGFLAG_CF(x)                   USB_CONFIGFLAG_CF(x)
#define USBHS_PORTSC1_CCS_MASK                   USB_PORTSC1_CCS_MASK
#define USBHS_PORTSC1_CCS_SHIFT                  USB_PORTSC1_CCS_SHIFT
#define USBHS_PORTSC1_CCS(x)                     USB_PORTSC1_CCS(x)
#define USBHS_PORTSC1_CSC_MASK                   USB_PORTSC1_CSC_MASK
#define USBHS_PORTSC1_CSC_SHIFT                  USB_PORTSC1_CSC_SHIFT
#define USBHS_PORTSC1_CSC(x)                     USB_PORTSC1_CSC(x)
#define USBHS_PORTSC1_PE_MASK                    USB_PORTSC1_PE_MASK
#define USBHS_PORTSC1_PE_SHIFT                   USB_PORTSC1_PE_SHIFT
#define USBHS_PORTSC1_PE(x)                      USB_PORTSC1_PE(x)
#define USBHS_PORTSC1_PEC_MASK                   USB_PORTSC1_PEC_MASK
#define USBHS_PORTSC1_PEC_SHIFT                  USB_PORTSC1_PEC_SHIFT
#define USBHS_PORTSC1_PEC(x)                     USB_PORTSC1_PEC(x)
#define USBHS_PORTSC1_OCA_MASK                   USB_PORTSC1_OCA_MASK
#define USBHS_PORTSC1_OCA_SHIFT                  USB_PORTSC1_OCA_SHIFT
#define USBHS_PORTSC1_OCA(x)                     USB_PORTSC1_OCA(x)
#define USBHS_PORTSC1_OCC_MASK                   USB_PORTSC1_OCC_MASK
#define USBHS_PORTSC1_OCC_SHIFT                  USB_PORTSC1_OCC_SHIFT
#define USBHS_PORTSC1_OCC(x)                     USB_PORTSC1_OCC(x)
#define USBHS_PORTSC1_FPR_MASK                   USB_PORTSC1_FPR_MASK
#define USBHS_PORTSC1_FPR_SHIFT                  USB_PORTSC1_FPR_SHIFT
#define USBHS_PORTSC1_FPR(x)                     USB_PORTSC1_FPR(x)
#define USBHS_PORTSC1_SUSP_MASK                  USB_PORTSC1_SUSP_MASK
#define USBHS_PORTSC1_SUSP_SHIFT                 USB_PORTSC1_SUSP_SHIFT
#define USBHS_PORTSC1_SUSP(x)                    USB_PORTSC1_SUSP(x)
#define USBHS_PORTSC1_PR_MASK                    USB_PORTSC1_PR_MASK
#define USBHS_PORTSC1_PR_SHIFT                   USB_PORTSC1_PR_SHIFT
#define USBHS_PORTSC1_PR(x)                      USB_PORTSC1_PR(x)
#define USBHS_PORTSC1_HSP_MASK                   USB_PORTSC1_HSP_MASK
#define USBHS_PORTSC1_HSP_SHIFT                  USB_PORTSC1_HSP_SHIFT
#define USBHS_PORTSC1_HSP(x)                     USB_PORTSC1_HSP(x)
#define USBHS_PORTSC1_LS_MASK                    USB_PORTSC1_LS_MASK
#define USBHS_PORTSC1_LS_SHIFT                   USB_PORTSC1_LS_SHIFT
#define USBHS_PORTSC1_LS(x)                      USB_PORTSC1_LS(x)
#define USBHS_PORTSC1_PP_MASK                    USB_PORTSC1_PP_MASK
#define USBHS_PORTSC1_PP_SHIFT                   USB_PORTSC1_PP_SHIFT
#define USBHS_PORTSC1_PP(x)                      USB_PORTSC1_PP(x)
#define USBHS_PORTSC1_PO_MASK                    USB_PORTSC1_PO_MASK
#define USBHS_PORTSC1_PO_SHIFT                   USB_PORTSC1_PO_SHIFT
#define USBHS_PORTSC1_PO(x)                      USB_PORTSC1_PO(x)
#define USBHS_PORTSC1_PIC_MASK                   USB_PORTSC1_PIC_MASK
#define USBHS_PORTSC1_PIC_SHIFT                  USB_PORTSC1_PIC_SHIFT
#define USBHS_PORTSC1_PIC(x)                     USB_PORTSC1_PIC(x)
#define USBHS_PORTSC1_PTC_MASK                   USB_PORTSC1_PTC_MASK
#define USBHS_PORTSC1_PTC_SHIFT                  USB_PORTSC1_PTC_SHIFT
#define USBHS_PORTSC1_PTC(x)                     USB_PORTSC1_PTC(x)
#define USBHS_PORTSC1_WKCN_MASK                  USB_PORTSC1_WKCN_MASK
#define USBHS_PORTSC1_WKCN_SHIFT                 USB_PORTSC1_WKCN_SHIFT
#define USBHS_PORTSC1_WKCN(x)                    USB_PORTSC1_WKCN(x)
#define USBHS_PORTSC1_WKDS_MASK                  USB_PORTSC1_WKDC_MASK
#define USBHS_PORTSC1_WKDS_SHIFT                 USB_PORTSC1_WKDC_SHIFT
#define USBHS_PORTSC1_WKDS(x)                    USB_PORTSC1_WKDC(x)
#define USBHS_PORTSC1_WKOC_MASK                  USB_PORTSC1_WKOC_MASK
#define USBHS_PORTSC1_WKOC_SHIFT                 USB_PORTSC1_WKOC_SHIFT
#define USBHS_PORTSC1_WKOC(x)                    USB_PORTSC1_WKOC(x)
#define USBHS_PORTSC1_PHCD_MASK                  USB_PORTSC1_PHCD_MASK
#define USBHS_PORTSC1_PHCD_SHIFT                 USB_PORTSC1_PHCD_SHIFT
#define USBHS_PORTSC1_PHCD(x)                    USB_PORTSC1_PHCD(x)
#define USBHS_PORTSC1_PFSC_MASK                  USB_PORTSC1_PFSC_MASK
#define USBHS_PORTSC1_PFSC_SHIFT                 USB_PORTSC1_PFSC_SHIFT
#define USBHS_PORTSC1_PFSC(x)                    USB_PORTSC1_PFSC(x)
#define USBHS_PORTSC1_PTS2_MASK                  USB_PORTSC1_PTS_2_MASK
#define USBHS_PORTSC1_PTS2_SHIFT                 USB_PORTSC1_PTS_2_SHIFT
#define USBHS_PORTSC1_PTS2(x)                    USB_PORTSC1_PTS_2(x)
#define USBHS_PORTSC1_PSPD_MASK                  USB_PORTSC1_PSPD_MASK
#define USBHS_PORTSC1_PSPD_SHIFT                 USB_PORTSC1_PSPD_SHIFT
#define USBHS_PORTSC1_PSPD(x)                    USB_PORTSC1_PSPD(x)
#define USBHS_PORTSC1_PTW_MASK                   USB_PORTSC1_PTW_MASK
#define USBHS_PORTSC1_PTW_SHIFT                  USB_PORTSC1_PTW_SHIFT
#define USBHS_PORTSC1_PTW(x)                     USB_PORTSC1_PTW(x)
#define USBHS_PORTSC1_STS_MASK                   USB_PORTSC1_STS_MASK
#define USBHS_PORTSC1_STS_SHIFT                  USB_PORTSC1_STS_SHIFT
#define USBHS_PORTSC1_STS(x)                     USB_PORTSC1_STS(x)
#define USBHS_PORTSC1_PTS_MASK                   USB_PORTSC1_PTS_1_MASK
#define USBHS_PORTSC1_PTS_SHIFT                  USB_PORTSC1_PTS_1_SHIFT
#define USBHS_PORTSC1_PTS(x)                     USB_PORTSC1_PTS_1(x)
#define USBHS_OTGSC_VD_MASK                      USB_OTGSC_VD_MASK
#define USBHS_OTGSC_VD_SHIFT                     USB_OTGSC_VD_SHIFT
#define USBHS_OTGSC_VD(x)                        USB_OTGSC_VD(x)
#define USBHS_OTGSC_VC_MASK                      USB_OTGSC_VC_MASK
#define USBHS_OTGSC_VC_SHIFT                     USB_OTGSC_VC_SHIFT
#define USBHS_OTGSC_VC(x)                        USB_OTGSC_VC(x)
#define USBHS_OTGSC_OT_MASK                      USB_OTGSC_OT_MASK
#define USBHS_OTGSC_OT_SHIFT                     USB_OTGSC_OT_SHIFT
#define USBHS_OTGSC_OT(x)                        USB_OTGSC_OT(x)
#define USBHS_OTGSC_DP_MASK                      USB_OTGSC_DP_MASK
#define USBHS_OTGSC_DP_SHIFT                     USB_OTGSC_DP_SHIFT
#define USBHS_OTGSC_DP(x)                        USB_OTGSC_DP(x)
#define USBHS_OTGSC_IDPU_MASK                    USB_OTGSC_IDPU_MASK
#define USBHS_OTGSC_IDPU_SHIFT                   USB_OTGSC_IDPU_SHIFT
#define USBHS_OTGSC_IDPU(x)                      USB_OTGSC_IDPU(x)
#define USBHS_OTGSC_ID_MASK                      USB_OTGSC_ID_MASK
#define USBHS_OTGSC_ID_SHIFT                     USB_OTGSC_ID_SHIFT
#define USBHS_OTGSC_ID(x)                        USB_OTGSC_ID(x)
#define USBHS_OTGSC_AVV_MASK                     USB_OTGSC_AVV_MASK
#define USBHS_OTGSC_AVV_SHIFT                    USB_OTGSC_AVV_SHIFT
#define USBHS_OTGSC_AVV(x)                       USB_OTGSC_AVV(x)
#define USBHS_OTGSC_ASV_MASK                     USB_OTGSC_ASV_MASK
#define USBHS_OTGSC_ASV_SHIFT                    USB_OTGSC_ASV_SHIFT
#define USBHS_OTGSC_ASV(x)                       USB_OTGSC_ASV(x)
#define USBHS_OTGSC_BSV_MASK                     USB_OTGSC_BSV_MASK
#define USBHS_OTGSC_BSV_SHIFT                    USB_OTGSC_BSV_SHIFT
#define USBHS_OTGSC_BSV(x)                       USB_OTGSC_BSV(x)
#define USBHS_OTGSC_BSE_MASK                     USB_OTGSC_BSE_MASK
#define USBHS_OTGSC_BSE_SHIFT                    USB_OTGSC_BSE_SHIFT
#define USBHS_OTGSC_BSE(x)                       USB_OTGSC_BSE(x)
#define USBHS_OTGSC_MST_MASK                     USB_OTGSC_TOG_1MS_MASK
#define USBHS_OTGSC_MST_SHIFT                    USB_OTGSC_TOG_1MS_SHIFT
#define USBHS_OTGSC_MST(x)                       USB_OTGSC_TOG_1MS(x)
#define USBHS_OTGSC_DPS_MASK                     USB_OTGSC_DPS_MASK
#define USBHS_OTGSC_DPS_SHIFT                    USB_OTGSC_DPS_SHIFT
#define USBHS_OTGSC_DPS(x)                       USB_OTGSC_DPS(x)
#define USBHS_OTGSC_IDIS_MASK                    USB_OTGSC_IDIS_MASK
#define USBHS_OTGSC_IDIS_SHIFT                   USB_OTGSC_IDIS_SHIFT
#define USBHS_OTGSC_IDIS(x)                      USB_OTGSC_IDIS(x)
#define USBHS_OTGSC_AVVIS_MASK                   USB_OTGSC_AVVIS_MASK
#define USBHS_OTGSC_AVVIS_SHIFT                  USB_OTGSC_AVVIS_SHIFT
#define USBHS_OTGSC_AVVIS(x)                     USB_OTGSC_AVVIS(x)
#define USBHS_OTGSC_ASVIS_MASK                   USB_OTGSC_ASVIS_MASK
#define USBHS_OTGSC_ASVIS_SHIFT                  USB_OTGSC_ASVIS_SHIFT
#define USBHS_OTGSC_ASVIS(x)                     USB_OTGSC_ASVIS(x)
#define USBHS_OTGSC_BSVIS_MASK                   USB_OTGSC_BSVIS_MASK
#define USBHS_OTGSC_BSVIS_SHIFT                  USB_OTGSC_BSVIS_SHIFT
#define USBHS_OTGSC_BSVIS(x)                     USB_OTGSC_BSVIS(x)
#define USBHS_OTGSC_BSEIS_MASK                   USB_OTGSC_BSEIS_MASK
#define USBHS_OTGSC_BSEIS_SHIFT                  USB_OTGSC_BSEIS_SHIFT
#define USBHS_OTGSC_BSEIS(x)                     USB_OTGSC_BSEIS(x)
#define USBHS_OTGSC_MSS_MASK                     USB_OTGSC_STATUS_1MS_MASK
#define USBHS_OTGSC_MSS_SHIFT                    USB_OTGSC_STATUS_1MS_SHIFT
#define USBHS_OTGSC_MSS(x)                       USB_OTGSC_STATUS_1MS(x)
#define USBHS_OTGSC_DPIS_MASK                    USB_OTGSC_DPIS_MASK
#define USBHS_OTGSC_DPIS_SHIFT                   USB_OTGSC_DPIS_SHIFT
#define USBHS_OTGSC_DPIS(x)                      USB_OTGSC_DPIS(x)
#define USBHS_OTGSC_IDIE_MASK                    USB_OTGSC_IDIE_MASK
#define USBHS_OTGSC_IDIE_SHIFT                   USB_OTGSC_IDIE_SHIFT
#define USBHS_OTGSC_IDIE(x)                      USB_OTGSC_IDIE(x)
#define USBHS_OTGSC_AVVIE_MASK                   USB_OTGSC_AVVIE_MASK
#define USBHS_OTGSC_AVVIE_SHIFT                  USB_OTGSC_AVVIE_SHIFT
#define USBHS_OTGSC_AVVIE(x)                     USB_OTGSC_AVVIE(x)
#define USBHS_OTGSC_ASVIE_MASK                   USB_OTGSC_ASVIE_MASK
#define USBHS_OTGSC_ASVIE_SHIFT                  USB_OTGSC_ASVIE_SHIFT
#define USBHS_OTGSC_ASVIE(x)                     USB_OTGSC_ASVIE(x)
#define USBHS_OTGSC_BSVIE_MASK                   USB_OTGSC_BSVIE_MASK
#define USBHS_OTGSC_BSVIE_SHIFT                  USB_OTGSC_BSVIE_SHIFT
#define USBHS_OTGSC_BSVIE(x)                     USB_OTGSC_BSVIE(x)
#define USBHS_OTGSC_BSEIE_MASK                   USB_OTGSC_BSEIE_MASK
#define USBHS_OTGSC_BSEIE_SHIFT                  USB_OTGSC_BSEIE_SHIFT
#define USBHS_OTGSC_BSEIE(x)                     USB_OTGSC_BSEIE(x)
#define USBHS_OTGSC_MSE_MASK                     USB_OTGSC_EN_1MS_MASK
#define USBHS_OTGSC_MSE_SHIFT                    USB_OTGSC_EN_1MS_SHIFT
#define USBHS_OTGSC_MSE(x)                       USB_OTGSC_EN_1MS(x)
#define USBHS_OTGSC_DPIE_MASK                    USB_OTGSC_DPIE_MASK
#define USBHS_OTGSC_DPIE_SHIFT                   USB_OTGSC_DPIE_SHIFT
#define USBHS_OTGSC_DPIE(x)                      USB_OTGSC_DPIE(x)
#define USBHS_USBMODE_CM_MASK                    USB_USBMODE_CM_MASK
#define USBHS_USBMODE_CM_SHIFT                   USB_USBMODE_CM_SHIFT
#define USBHS_USBMODE_CM(x)                      USB_USBMODE_CM(x)
#define USBHS_USBMODE_ES_MASK                    USB_USBMODE_ES_MASK
#define USBHS_USBMODE_ES_SHIFT                   USB_USBMODE_ES_SHIFT
#define USBHS_USBMODE_ES(x)                      USB_USBMODE_ES(x)
#define USBHS_USBMODE_SLOM_MASK                  USB_USBMODE_SLOM_MASK
#define USBHS_USBMODE_SLOM_SHIFT                 USB_USBMODE_SLOM_SHIFT
#define USBHS_USBMODE_SLOM(x)                    USB_USBMODE_SLOM(x)
#define USBHS_USBMODE_SDIS_MASK                  USB_USBMODE_SDIS_MASK
#define USBHS_USBMODE_SDIS_SHIFT                 USB_USBMODE_SDIS_SHIFT
#define USBHS_USBMODE_SDIS(x)                    USB_USBMODE_SDIS(x)
#define USBHS_EPSETUPSR_EPSETUPSTAT_MASK         USB_ENDPTSETUPSTAT_ENDPTSETUPSTAT_MASK
#define USBHS_EPSETUPSR_EPSETUPSTAT_SHIFT        USB_ENDPTSETUPSTAT_ENDPTSETUPSTAT_SHIFT
#define USBHS_EPSETUPSR_EPSETUPSTAT(x)           USB_ENDPTSETUPSTAT_ENDPTSETUPSTAT(x)
#define USBHS_EPPRIME_PERB_MASK                  USB_ENDPTPRIME_PERB_MASK
#define USBHS_EPPRIME_PERB_SHIFT                 USB_ENDPTPRIME_PERB_SHIFT
#define USBHS_EPPRIME_PERB(x)                    USB_ENDPTPRIME_PERB(x)
#define USBHS_EPPRIME_PETB_MASK                  USB_ENDPTPRIME_PETB_MASK
#define USBHS_EPPRIME_PETB_SHIFT                 USB_ENDPTPRIME_PETB_SHIFT
#define USBHS_EPPRIME_PETB(x)                    USB_ENDPTPRIME_PETB(x)
#define USBHS_EPFLUSH_FERB_MASK                  USB_ENDPTFLUSH_FERB_MASK
#define USBHS_EPFLUSH_FERB_SHIFT                 USB_ENDPTFLUSH_FERB_SHIFT
#define USBHS_EPFLUSH_FERB(x)                    USB_ENDPTFLUSH_FERB(x)
#define USBHS_EPFLUSH_FETB_MASK                  USB_ENDPTFLUSH_FETB_MASK
#define USBHS_EPFLUSH_FETB_SHIFT                 USB_ENDPTFLUSH_FETB_SHIFT
#define USBHS_EPFLUSH_FETB(x)                    USB_ENDPTFLUSH_FETB(x)
#define USBHS_EPSR_ERBR_MASK                     USB_ENDPTSTAT_ERBR_MASK
#define USBHS_EPSR_ERBR_SHIFT                    USB_ENDPTSTAT_ERBR_SHIFT
#define USBHS_EPSR_ERBR(x)                       USB_ENDPTSTAT_ERBR(x)
#define USBHS_EPSR_ETBR_MASK                     USB_ENDPTSTAT_ETBR_MASK
#define USBHS_EPSR_ETBR_SHIFT                    USB_ENDPTSTAT_ETBR_SHIFT
#define USBHS_EPSR_ETBR(x)                       USB_ENDPTSTAT_ETBR(x)
#define USBHS_EPCOMPLETE_ERCE_MASK               USB_ENDPTCOMPLETE_ERCE_MASK
#define USBHS_EPCOMPLETE_ERCE_SHIFT              USB_ENDPTCOMPLETE_ERCE_SHIFT
#define USBHS_EPCOMPLETE_ERCE(x)                 USB_ENDPTCOMPLETE_ERCE(x)
#define USBHS_EPCOMPLETE_ETCE_MASK               USB_ENDPTCOMPLETE_ETCE_MASK
#define USBHS_EPCOMPLETE_ETCE_SHIFT              USB_ENDPTCOMPLETE_ETCE_SHIFT
#define USBHS_EPCOMPLETE_ETCE(x)                 USB_ENDPTCOMPLETE_ETCE(x)
#define USBHS_EPCR0_RXS_MASK                     USB_ENDPTCTRL0_RXS_MASK
#define USBHS_EPCR0_RXS_SHIFT                    USB_ENDPTCTRL0_RXS_SHIFT
#define USBHS_EPCR0_RXS(x)                       USB_ENDPTCTRL0_RXS(x)
#define USBHS_EPCR0_RXT_MASK                     USB_ENDPTCTRL0_RXT_MASK
#define USBHS_EPCR0_RXT_SHIFT                    USB_ENDPTCTRL0_RXT_SHIFT
#define USBHS_EPCR0_RXT(x)                       USB_ENDPTCTRL0_RXT(x)
#define USBHS_EPCR0_RXE_MASK                     USB_ENDPTCTRL0_RXE_MASK
#define USBHS_EPCR0_RXE_SHIFT                    USB_ENDPTCTRL0_RXE_SHIFT
#define USBHS_EPCR0_RXE(x)                       USB_ENDPTCTRL0_RXE(x)
#define USBHS_EPCR0_TXS_MASK                     USB_ENDPTCTRL0_TXS_MASK
#define USBHS_EPCR0_TXS_SHIFT                    USB_ENDPTCTRL0_TXS_SHIFT
#define USBHS_EPCR0_TXS(x)                       USB_ENDPTCTRL0_TXS(x)
#define USBHS_EPCR0_TXT_MASK                     USB_ENDPTCTRL0_TXT_MASK
#define USBHS_EPCR0_TXT_SHIFT                    USB_ENDPTCTRL0_TXT_SHIFT
#define USBHS_EPCR0_TXT(x)                       USB_ENDPTCTRL0_TXT(x)
#define USBHS_EPCR0_TXE_MASK                     USB_ENDPTCTRL0_TXE_MASK
#define USBHS_EPCR0_TXE_SHIFT                    USB_ENDPTCTRL0_TXE_SHIFT
#define USBHS_EPCR0_TXE(x)                       USB_ENDPTCTRL0_TXE(x)
#define USBHS_EPCR_RXS_MASK                      USB_ENDPTCTRL_RXS_MASK
#define USBHS_EPCR_RXS_SHIFT                     USB_ENDPTCTRL_RXS_SHIFT
#define USBHS_EPCR_RXS(x)                        USB_ENDPTCTRL_RXS(x)
#define USBHS_EPCR_RXD_MASK                      USB_ENDPTCTRL_RXD_MASK
#define USBHS_EPCR_RXD_SHIFT                     USB_ENDPTCTRL_RXD_SHIFT
#define USBHS_EPCR_RXD(x)                        USB_ENDPTCTRL_RXD(x)
#define USBHS_EPCR_RXT_MASK                      USB_ENDPTCTRL_RXT_MASK
#define USBHS_EPCR_RXT_SHIFT                     USB_ENDPTCTRL_RXT_SHIFT
#define USBHS_EPCR_RXT(x)                        USB_ENDPTCTRL_RXT(x)
#define USBHS_EPCR_RXI_MASK                      USB_ENDPTCTRL_RXI_MASK
#define USBHS_EPCR_RXI_SHIFT                     USB_ENDPTCTRL_RXI_SHIFT
#define USBHS_EPCR_RXI(x)                        USB_ENDPTCTRL_RXI(x)
#define USBHS_EPCR_RXR_MASK                      USB_ENDPTCTRL_RXR_MASK
#define USBHS_EPCR_RXR_SHIFT                     USB_ENDPTCTRL_RXR_SHIFT
#define USBHS_EPCR_RXR(x)                        USB_ENDPTCTRL_RXR(x)
#define USBHS_EPCR_RXE_MASK                      USB_ENDPTCTRL_RXE_MASK
#define USBHS_EPCR_RXE_SHIFT                     USB_ENDPTCTRL_RXE_SHIFT
#define USBHS_EPCR_RXE(x)                        USB_ENDPTCTRL_RXE(x)
#define USBHS_EPCR_TXS_MASK                      USB_ENDPTCTRL_TXS_MASK
#define USBHS_EPCR_TXS_SHIFT                     USB_ENDPTCTRL_TXS_SHIFT
#define USBHS_EPCR_TXS(x)                        USB_ENDPTCTRL_TXS(x)
#define USBHS_EPCR_TXD_MASK                      USB_ENDPTCTRL_TXD_MASK
#define USBHS_EPCR_TXD_SHIFT                     USB_ENDPTCTRL_TXD_SHIFT
#define USBHS_EPCR_TXD(x)                        USB_ENDPTCTRL_TXD(x)
#define USBHS_EPCR_TXT_MASK                      USB_ENDPTCTRL_TXT_MASK
#define USBHS_EPCR_TXT_SHIFT                     USB_ENDPTCTRL_TXT_SHIFT
#define USBHS_EPCR_TXT(x)                        USB_ENDPTCTRL_TXT(x)
#define USBHS_EPCR_TXI_MASK                      USB_ENDPTCTRL_TXI_MASK
#define USBHS_EPCR_TXI_SHIFT                     USB_ENDPTCTRL_TXI_SHIFT
#define USBHS_EPCR_TXI(x)                        USB_ENDPTCTRL_TXI(x)
#define USBHS_EPCR_TXR_MASK                      USB_ENDPTCTRL_TXR_MASK
#define USBHS_EPCR_TXR_SHIFT                     USB_ENDPTCTRL_TXR_SHIFT
#define USBHS_EPCR_TXR(x)                        USB_ENDPTCTRL_TXR(x)
#define USBHS_EPCR_TXE_MASK                      USB_ENDPTCTRL_TXE_MASK
#define USBHS_EPCR_TXE_SHIFT                     USB_ENDPTCTRL_TXE_SHIFT
#define USBHS_EPCR_TXE(x)                        USB_ENDPTCTRL_TXE(x)
#define USBHS_EPCR_COUNT                         USB_ENDPTCTRL_COUNT
#define USBHS_Type                               USB_Type
#define USBHS_BASE_ADDRS                         USB_BASE_ADDRS
#define USBHS_IRQS                               { USB_OTG1_IRQn, USB_OTG2_IRQn }
#define USBHS_IRQHandler                         USB_OTG1_IRQHandler
#define USBHS_STACK_BASE_ADDRS                   { USB_OTG1_BASE, USB_OTG2_BASE }


/*!
 * @}
 */ /* end of group USB_Peripheral_Access_Layer */


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


#endif  /* PERI_USB_H_ */

