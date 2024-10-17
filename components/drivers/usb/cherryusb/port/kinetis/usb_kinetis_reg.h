/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __USB_KINETIS_REG_H__
#define __USB_KINETIS_REG_H__

#define __I  volatile const /* Define "read-only" permission */
#define __IO volatile       /* Define "read-write" permission */

/* ----------------------------------------------------------------------------
   -- USB Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USB_Peripheral_Access_Layer USB Peripheral Access Layer
 * @{
 */

/** USB - Register Layout Typedef */
typedef struct {
    __I uint8_t PERID; /**< Peripheral ID, offset: 0x0 */
    uint8_t RESERVED_0[3];
    __I uint8_t IDCOMP; /**< Peripheral ID Complement, offset: 0x4 */
    uint8_t RESERVED_1[3];
    __I uint8_t REV; /**< Peripheral Revision, offset: 0x8 */
    uint8_t RESERVED_2[3];
    __I uint8_t ADDINFO; /**< Peripheral Additional Information, offset: 0xC */
    uint8_t RESERVED_3[3];
    __IO uint8_t OTGISTAT; /**< OTG Interrupt Status, offset: 0x10 */
    uint8_t RESERVED_4[3];
    __IO uint8_t OTGICR; /**< OTG Interrupt Control, offset: 0x14 */
    uint8_t RESERVED_5[3];
    __I uint8_t OTGSTAT; /**< OTG Status, offset: 0x18 */
    uint8_t RESERVED_6[3];
    __IO uint8_t OTGCTL; /**< OTG Control, offset: 0x1C */
    uint8_t RESERVED_7[99];
    __IO uint8_t ISTAT; /**< Interrupt Status, offset: 0x80 */
    uint8_t RESERVED_8[3];
    __IO uint8_t INTEN; /**< Interrupt Enable, offset: 0x84 */
    uint8_t RESERVED_9[3];
    __IO uint8_t ERRSTAT; /**< Error Interrupt Status, offset: 0x88 */
    uint8_t RESERVED_10[3];
    __IO uint8_t ERREN; /**< Error Interrupt Enable, offset: 0x8C */
    uint8_t RESERVED_11[3];
    __I uint8_t STAT; /**< Status, offset: 0x90 */
    uint8_t RESERVED_12[3];
    __IO uint8_t CTL; /**< Control, offset: 0x94 */
    uint8_t RESERVED_13[3];
    __IO uint8_t ADDR; /**< Address, offset: 0x98 */
    uint8_t RESERVED_14[3];
    __IO uint8_t BDTPAGE1; /**< BDT Page 1, offset: 0x9C */
    uint8_t RESERVED_15[3];
    __I uint8_t FRMNUML; /**< Frame Number Register Low, offset: 0xA0 */
    uint8_t RESERVED_16[3];
    __I uint8_t FRMNUMH; /**< Frame Number Register High, offset: 0xA4 */
    uint8_t RESERVED_17[3];
    __IO uint8_t TOKEN; /**< Token, offset: 0xA8 */
    uint8_t RESERVED_18[3];
    __IO uint8_t SOFTHLD; /**< SOF Threshold, offset: 0xAC */
    uint8_t RESERVED_19[3];
    __IO uint8_t BDTPAGE2; /**< BDT Page 2, offset: 0xB0 */
    uint8_t RESERVED_20[3];
    __IO uint8_t BDTPAGE3; /**< BDT Page 3, offset: 0xB4 */
    uint8_t RESERVED_21[11];
    struct {                /* offset: 0xC0, array step: 0x4 */
        __IO uint8_t ENDPT; /**< Endpoint Control, array offset: 0xC0, array step: 0x4 */
        uint8_t RESERVED_0[3];
    } ENDPOINT[16];
} KINETIS_TypeDef;

/* ----------------------------------------------------------------------------
   -- USB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USB_Register_Masks USB Register Masks
 * @{
 */

/*! @name PERID - Peripheral ID */
/*! @{ */

#define USB_PERID_ID_MASK  (0x3FU)
#define USB_PERID_ID_SHIFT (0U)
/*! ID - Peripheral Identification */
#define USB_PERID_ID(x) (((uint8_t)(((uint8_t)(x)) << USB_PERID_ID_SHIFT)) & USB_PERID_ID_MASK)
/*! @} */

/*! @name IDCOMP - Peripheral ID Complement */
/*! @{ */

#define USB_IDCOMP_NID_MASK  (0x3FU)
#define USB_IDCOMP_NID_SHIFT (0U)
/*! NID - Negative Peripheral ID */
#define USB_IDCOMP_NID(x) (((uint8_t)(((uint8_t)(x)) << USB_IDCOMP_NID_SHIFT)) & USB_IDCOMP_NID_MASK)
/*! @} */

/*! @name REV - Peripheral Revision */
/*! @{ */

#define USB_REV_REV_MASK  (0xFFU)
#define USB_REV_REV_SHIFT (0U)
/*! REV - Revision */
#define USB_REV_REV(x) (((uint8_t)(((uint8_t)(x)) << USB_REV_REV_SHIFT)) & USB_REV_REV_MASK)
/*! @} */

/*! @name ADDINFO - Peripheral Additional Information */
/*! @{ */

#define USB_ADDINFO_IEHOST_MASK  (0x1U)
#define USB_ADDINFO_IEHOST_SHIFT (0U)
/*! IEHOST - Host Mode Enable
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define USB_ADDINFO_IEHOST(x) (((uint8_t)(((uint8_t)(x)) << USB_ADDINFO_IEHOST_SHIFT)) & USB_ADDINFO_IEHOST_MASK)
/*! @} */

/*! @name OTGISTAT - OTG Interrupt Status */
/*! @{ */

#define USB_OTGISTAT_LINE_STATE_CHG_MASK  (0x20U)
#define USB_OTGISTAT_LINE_STATE_CHG_SHIFT (5U)
/*! LINE_STATE_CHG - Line State Change Interrupt Flag
 *  0b0..Interrupt did not occur
 *  0b1..Interrupt occurred
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define USB_OTGISTAT_LINE_STATE_CHG(x) (((uint8_t)(((uint8_t)(x)) << USB_OTGISTAT_LINE_STATE_CHG_SHIFT)) & USB_OTGISTAT_LINE_STATE_CHG_MASK)

#define USB_OTGISTAT_ONEMSEC_MASK  (0x40U)
#define USB_OTGISTAT_ONEMSEC_SHIFT (6U)
/*! ONEMSEC - One Millisecond Timer Timeout Flag
 *  0b0..Not timed out
 *  0b1..Timed out
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define USB_OTGISTAT_ONEMSEC(x) (((uint8_t)(((uint8_t)(x)) << USB_OTGISTAT_ONEMSEC_SHIFT)) & USB_OTGISTAT_ONEMSEC_MASK)
/*! @} */

/*! @name OTGICR - OTG Interrupt Control */
/*! @{ */

#define USB_OTGICR_LINESTATEEN_MASK  (0x20U)
#define USB_OTGICR_LINESTATEEN_SHIFT (5U)
/*! LINESTATEEN - Line State Change Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_OTGICR_LINESTATEEN(x) (((uint8_t)(((uint8_t)(x)) << USB_OTGICR_LINESTATEEN_SHIFT)) & USB_OTGICR_LINESTATEEN_MASK)

#define USB_OTGICR_ONEMSECEN_MASK  (0x40U)
#define USB_OTGICR_ONEMSECEN_SHIFT (6U)
/*! ONEMSECEN - 1-Millisecond Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_OTGICR_ONEMSECEN(x) (((uint8_t)(((uint8_t)(x)) << USB_OTGICR_ONEMSECEN_SHIFT)) & USB_OTGICR_ONEMSECEN_MASK)
/*! @} */

/*! @name OTGSTAT - OTG Status */
/*! @{ */

#define USB_OTGSTAT_LINESTATESTABLE_MASK  (0x20U)
#define USB_OTGSTAT_LINESTATESTABLE_SHIFT (5U)
/*! LINESTATESTABLE - Line State Stable
 *  0b0..Unstable
 *  0b1..Stable
 */
#define USB_OTGSTAT_LINESTATESTABLE(x) (((uint8_t)(((uint8_t)(x)) << USB_OTGSTAT_LINESTATESTABLE_SHIFT)) & USB_OTGSTAT_LINESTATESTABLE_MASK)

#define USB_OTGSTAT_ONEMSEC_MASK  (0x40U)
#define USB_OTGSTAT_ONEMSEC_SHIFT (6U)
/*! ONEMSEC - Reserved for 1 ms count */
#define USB_OTGSTAT_ONEMSEC(x) (((uint8_t)(((uint8_t)(x)) << USB_OTGSTAT_ONEMSEC_SHIFT)) & USB_OTGSTAT_ONEMSEC_MASK)
/*! @} */

/*! @name OTGCTL - OTG Control */
/*! @{ */

#define USB_OTGCTL_OTGEN_MASK  (0x4U)
#define USB_OTGCTL_OTGEN_SHIFT (2U)
/*! OTGEN - On-The-Go Pullup and Pulldown Resistor Enable
 *  0b0..If USBENSOFEN is 1 and HOSTMODEEN is 0 in the Control Register (CTL), then the D+ Data line pullup
 *       resistors are enabled. If HOSTMODEEN is 1, then the D+ and D- Data line pulldown resistors are engaged.
 *  0b1..Uses the pullup and pulldown controls in this register.
 */
#define USB_OTGCTL_OTGEN(x) (((uint8_t)(((uint8_t)(x)) << USB_OTGCTL_OTGEN_SHIFT)) & USB_OTGCTL_OTGEN_MASK)

#define USB_OTGCTL_DMLOW_MASK  (0x10U)
#define USB_OTGCTL_DMLOW_SHIFT (4U)
/*! DMLOW - D- Data Line Pulldown Resistor Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_OTGCTL_DMLOW(x) (((uint8_t)(((uint8_t)(x)) << USB_OTGCTL_DMLOW_SHIFT)) & USB_OTGCTL_DMLOW_MASK)

#define USB_OTGCTL_DPLOW_MASK  (0x20U)
#define USB_OTGCTL_DPLOW_SHIFT (5U)
/*! DPLOW - D+ Data Line pulldown Resistor Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_OTGCTL_DPLOW(x) (((uint8_t)(((uint8_t)(x)) << USB_OTGCTL_DPLOW_SHIFT)) & USB_OTGCTL_DPLOW_MASK)

#define USB_OTGCTL_DPHIGH_MASK  (0x80U)
#define USB_OTGCTL_DPHIGH_SHIFT (7U)
/*! DPHIGH - D+ Data Line Pullup Resistor Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_OTGCTL_DPHIGH(x) (((uint8_t)(((uint8_t)(x)) << USB_OTGCTL_DPHIGH_SHIFT)) & USB_OTGCTL_DPHIGH_MASK)
/*! @} */

/*! @name ISTAT - Interrupt Status */
/*! @{ */

#define USB_ISTAT_USBRST_MASK  (0x1U)
#define USB_ISTAT_USBRST_SHIFT (0U)
/*! USBRST - USB Reset Flag
 *  0b0..Not detected
 *  0b1..Detected
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define USB_ISTAT_USBRST(x) (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_USBRST_SHIFT)) & USB_ISTAT_USBRST_MASK)

#define USB_ISTAT_ERROR_MASK  (0x2U)
#define USB_ISTAT_ERROR_SHIFT (1U)
/*! ERROR - Error Flag
 *  0b0..Error did not occur
 *  0b1..Error occurred
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define USB_ISTAT_ERROR(x) (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_ERROR_SHIFT)) & USB_ISTAT_ERROR_MASK)

#define USB_ISTAT_SOFTOK_MASK  (0x4U)
#define USB_ISTAT_SOFTOK_SHIFT (2U)
/*! SOFTOK - Start Of Frame (SOF) Token Flag
 *  0b0..Did not receive
 *  0b1..Received
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define USB_ISTAT_SOFTOK(x) (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_SOFTOK_SHIFT)) & USB_ISTAT_SOFTOK_MASK)

#define USB_ISTAT_TOKDNE_MASK  (0x8U)
#define USB_ISTAT_TOKDNE_SHIFT (3U)
/*! TOKDNE - Current Token Processing Flag
 *  0b0..Not processed
 *  0b1..Processed
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define USB_ISTAT_TOKDNE(x) (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_TOKDNE_SHIFT)) & USB_ISTAT_TOKDNE_MASK)

#define USB_ISTAT_SLEEP_MASK  (0x10U)
#define USB_ISTAT_SLEEP_SHIFT (4U)
/*! SLEEP - Sleep Flag
 *  0b0..Interrupt did not occur
 *  0b1..Interrupt occurred
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define USB_ISTAT_SLEEP(x) (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_SLEEP_SHIFT)) & USB_ISTAT_SLEEP_MASK)

#define USB_ISTAT_RESUME_MASK  (0x20U)
#define USB_ISTAT_RESUME_SHIFT (5U)
/*! RESUME - Resume Flag
 *  0b0..Interrupt did not occur
 *  0b1..Interrupt occurred
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define USB_ISTAT_RESUME(x) (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_RESUME_SHIFT)) & USB_ISTAT_RESUME_MASK)

#define USB_ISTAT_ATTACH_MASK  (0x40U)
#define USB_ISTAT_ATTACH_SHIFT (6U)
/*! ATTACH - Attach Interrupt Flag
 *  0b0..Not detected
 *  0b1..Detected
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define USB_ISTAT_ATTACH(x) (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_ATTACH_SHIFT)) & USB_ISTAT_ATTACH_MASK)

#define USB_ISTAT_STALL_MASK  (0x80U)
#define USB_ISTAT_STALL_SHIFT (7U)
/*! STALL - Stall Interrupt Flag
 *  0b0..Interrupt did not occur
 *  0b1..Interrupt occurred
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define USB_ISTAT_STALL(x) (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_STALL_SHIFT)) & USB_ISTAT_STALL_MASK)
/*! @} */

/*! @name INTEN - Interrupt Enable */
/*! @{ */

#define USB_INTEN_USBRSTEN_MASK  (0x1U)
#define USB_INTEN_USBRSTEN_SHIFT (0U)
/*! USBRSTEN - USBRST Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_INTEN_USBRSTEN(x) (((uint8_t)(((uint8_t)(x)) << USB_INTEN_USBRSTEN_SHIFT)) & USB_INTEN_USBRSTEN_MASK)

#define USB_INTEN_ERROREN_MASK  (0x2U)
#define USB_INTEN_ERROREN_SHIFT (1U)
/*! ERROREN - ERROR Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_INTEN_ERROREN(x) (((uint8_t)(((uint8_t)(x)) << USB_INTEN_ERROREN_SHIFT)) & USB_INTEN_ERROREN_MASK)

#define USB_INTEN_SOFTOKEN_MASK  (0x4U)
#define USB_INTEN_SOFTOKEN_SHIFT (2U)
/*! SOFTOKEN - SOFTOK Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_INTEN_SOFTOKEN(x) (((uint8_t)(((uint8_t)(x)) << USB_INTEN_SOFTOKEN_SHIFT)) & USB_INTEN_SOFTOKEN_MASK)

#define USB_INTEN_TOKDNEEN_MASK  (0x8U)
#define USB_INTEN_TOKDNEEN_SHIFT (3U)
/*! TOKDNEEN - TOKDNE Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_INTEN_TOKDNEEN(x) (((uint8_t)(((uint8_t)(x)) << USB_INTEN_TOKDNEEN_SHIFT)) & USB_INTEN_TOKDNEEN_MASK)

#define USB_INTEN_SLEEPEN_MASK  (0x10U)
#define USB_INTEN_SLEEPEN_SHIFT (4U)
/*! SLEEPEN - SLEEP Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_INTEN_SLEEPEN(x) (((uint8_t)(((uint8_t)(x)) << USB_INTEN_SLEEPEN_SHIFT)) & USB_INTEN_SLEEPEN_MASK)

#define USB_INTEN_RESUMEEN_MASK  (0x20U)
#define USB_INTEN_RESUMEEN_SHIFT (5U)
/*! RESUMEEN - RESUME Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_INTEN_RESUMEEN(x) (((uint8_t)(((uint8_t)(x)) << USB_INTEN_RESUMEEN_SHIFT)) & USB_INTEN_RESUMEEN_MASK)

#define USB_INTEN_ATTACHEN_MASK  (0x40U)
#define USB_INTEN_ATTACHEN_SHIFT (6U)
/*! ATTACHEN - ATTACH Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_INTEN_ATTACHEN(x) (((uint8_t)(((uint8_t)(x)) << USB_INTEN_ATTACHEN_SHIFT)) & USB_INTEN_ATTACHEN_MASK)

#define USB_INTEN_STALLEN_MASK  (0x80U)
#define USB_INTEN_STALLEN_SHIFT (7U)
/*! STALLEN - STALL Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_INTEN_STALLEN(x) (((uint8_t)(((uint8_t)(x)) << USB_INTEN_STALLEN_SHIFT)) & USB_INTEN_STALLEN_MASK)
/*! @} */

/*! @name ERRSTAT - Error Interrupt Status */
/*! @{ */

#define USB_ERRSTAT_PIDERR_MASK  (0x1U)
#define USB_ERRSTAT_PIDERR_SHIFT (0U)
/*! PIDERR - PID Error Flag
 *  0b0..Did not fail
 *  0b1..Failed
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define USB_ERRSTAT_PIDERR(x) (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_PIDERR_SHIFT)) & USB_ERRSTAT_PIDERR_MASK)

#define USB_ERRSTAT_CRC5EOF_MASK  (0x2U)
#define USB_ERRSTAT_CRC5EOF_SHIFT (1U)
/*! CRC5EOF - CRC5 Error or End of Frame Error Flag
 *  0b0..Interrupt did not occur
 *  0b1..Interrupt occurred
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define USB_ERRSTAT_CRC5EOF(x) (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_CRC5EOF_SHIFT)) & USB_ERRSTAT_CRC5EOF_MASK)

#define USB_ERRSTAT_CRC16_MASK  (0x4U)
#define USB_ERRSTAT_CRC16_SHIFT (2U)
/*! CRC16 - CRC16 Error Flag
 *  0b0..Not rejected
 *  0b1..Rejected
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define USB_ERRSTAT_CRC16(x) (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_CRC16_SHIFT)) & USB_ERRSTAT_CRC16_MASK)

#define USB_ERRSTAT_DFN8_MASK  (0x8U)
#define USB_ERRSTAT_DFN8_SHIFT (3U)
/*! DFN8 - Data Field Not 8 Bits Flag
 *  0b0..Integer number of bytes
 *  0b1..Not an integer number of bytes
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define USB_ERRSTAT_DFN8(x) (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_DFN8_SHIFT)) & USB_ERRSTAT_DFN8_MASK)

#define USB_ERRSTAT_BTOERR_MASK  (0x10U)
#define USB_ERRSTAT_BTOERR_SHIFT (4U)
/*! BTOERR - Bus Turnaround Timeout Error Flag
 *  0b0..Not timed out
 *  0b1..Timed out
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define USB_ERRSTAT_BTOERR(x) (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_BTOERR_SHIFT)) & USB_ERRSTAT_BTOERR_MASK)

#define USB_ERRSTAT_DMAERR_MASK  (0x20U)
#define USB_ERRSTAT_DMAERR_SHIFT (5U)
/*! DMAERR - DMA Access Error Flag
 *  0b0..Interrupt did not occur
 *  0b1..Interrupt occurred
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define USB_ERRSTAT_DMAERR(x) (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_DMAERR_SHIFT)) & USB_ERRSTAT_DMAERR_MASK)

#define USB_ERRSTAT_OWNERR_MASK  (0x40U)
#define USB_ERRSTAT_OWNERR_SHIFT (6U)
/*! OWNERR - BD Unavailable Error Flag
 *  0b0..Interrupt did not occur
 *  0b1..Interrupt occurred
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define USB_ERRSTAT_OWNERR(x) (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_OWNERR_SHIFT)) & USB_ERRSTAT_OWNERR_MASK)

#define USB_ERRSTAT_BTSERR_MASK  (0x80U)
#define USB_ERRSTAT_BTSERR_SHIFT (7U)
/*! BTSERR - Bit Stuff Error Flag
 *  0b0..Packet not rejected due to the error
 *  0b1..Packet rejected due to the error
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define USB_ERRSTAT_BTSERR(x) (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_BTSERR_SHIFT)) & USB_ERRSTAT_BTSERR_MASK)
/*! @} */

/*! @name ERREN - Error Interrupt Enable */
/*! @{ */

#define USB_ERREN_PIDERREN_MASK  (0x1U)
#define USB_ERREN_PIDERREN_SHIFT (0U)
/*! PIDERREN - PIDERR Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_ERREN_PIDERREN(x) (((uint8_t)(((uint8_t)(x)) << USB_ERREN_PIDERREN_SHIFT)) & USB_ERREN_PIDERREN_MASK)

#define USB_ERREN_CRC5EOFEN_MASK  (0x2U)
#define USB_ERREN_CRC5EOFEN_SHIFT (1U)
/*! CRC5EOFEN - CRC5/EOF Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_ERREN_CRC5EOFEN(x) (((uint8_t)(((uint8_t)(x)) << USB_ERREN_CRC5EOFEN_SHIFT)) & USB_ERREN_CRC5EOFEN_MASK)

#define USB_ERREN_CRC16EN_MASK  (0x4U)
#define USB_ERREN_CRC16EN_SHIFT (2U)
/*! CRC16EN - CRC16 Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_ERREN_CRC16EN(x) (((uint8_t)(((uint8_t)(x)) << USB_ERREN_CRC16EN_SHIFT)) & USB_ERREN_CRC16EN_MASK)

#define USB_ERREN_DFN8EN_MASK  (0x8U)
#define USB_ERREN_DFN8EN_SHIFT (3U)
/*! DFN8EN - DFN8 (Data Field Not Integer Number of Bytes) Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_ERREN_DFN8EN(x) (((uint8_t)(((uint8_t)(x)) << USB_ERREN_DFN8EN_SHIFT)) & USB_ERREN_DFN8EN_MASK)

#define USB_ERREN_BTOERREN_MASK  (0x10U)
#define USB_ERREN_BTOERREN_SHIFT (4U)
/*! BTOERREN - BTOERR (Bus Timeout Error) Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_ERREN_BTOERREN(x) (((uint8_t)(((uint8_t)(x)) << USB_ERREN_BTOERREN_SHIFT)) & USB_ERREN_BTOERREN_MASK)

#define USB_ERREN_DMAERREN_MASK  (0x20U)
#define USB_ERREN_DMAERREN_SHIFT (5U)
/*! DMAERREN - DMAERR Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_ERREN_DMAERREN(x) (((uint8_t)(((uint8_t)(x)) << USB_ERREN_DMAERREN_SHIFT)) & USB_ERREN_DMAERREN_MASK)

#define USB_ERREN_OWNERREN_MASK  (0x40U)
#define USB_ERREN_OWNERREN_SHIFT (6U)
/*! OWNERREN - OWNERR Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_ERREN_OWNERREN(x) (((uint8_t)(((uint8_t)(x)) << USB_ERREN_OWNERREN_SHIFT)) & USB_ERREN_OWNERREN_MASK)

#define USB_ERREN_BTSERREN_MASK  (0x80U)
#define USB_ERREN_BTSERREN_SHIFT (7U)
/*! BTSERREN - BTSERR (Bit Stuff Error) Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_ERREN_BTSERREN(x) (((uint8_t)(((uint8_t)(x)) << USB_ERREN_BTSERREN_SHIFT)) & USB_ERREN_BTSERREN_MASK)
/*! @} */

/*! @name STAT - Status */
/*! @{ */

#define USB_STAT_ODD_MASK  (0x4U)
#define USB_STAT_ODD_SHIFT (2U)
/*! ODD - Odd Bank
 *  0b0..Not in the odd bank
 *  0b1..In the odd bank
 */
#define USB_STAT_ODD(x) (((uint8_t)(((uint8_t)(x)) << USB_STAT_ODD_SHIFT)) & USB_STAT_ODD_MASK)

#define USB_STAT_TX_MASK  (0x8U)
#define USB_STAT_TX_SHIFT (3U)
/*! TX - Transmit Indicator
 *  0b0..Receive
 *  0b1..Transmit
 */
#define USB_STAT_TX(x) (((uint8_t)(((uint8_t)(x)) << USB_STAT_TX_SHIFT)) & USB_STAT_TX_MASK)

#define USB_STAT_ENDP_MASK  (0xF0U)
#define USB_STAT_ENDP_SHIFT (4U)
/*! ENDP - Endpoint address */
#define USB_STAT_ENDP(x) (((uint8_t)(((uint8_t)(x)) << USB_STAT_ENDP_SHIFT)) & USB_STAT_ENDP_MASK)
/*! @} */

/*! @name CTL - Control */
/*! @{ */

#define USB_CTL_USBENSOFEN_MASK  (0x1U)
#define USB_CTL_USBENSOFEN_SHIFT (0U)
/*! USBENSOFEN - USB Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_CTL_USBENSOFEN(x) (((uint8_t)(((uint8_t)(x)) << USB_CTL_USBENSOFEN_SHIFT)) & USB_CTL_USBENSOFEN_MASK)

#define USB_CTL_ODDRST_MASK  (0x2U)
#define USB_CTL_ODDRST_SHIFT (1U)
/*! ODDRST - Odd Reset */
#define USB_CTL_ODDRST(x) (((uint8_t)(((uint8_t)(x)) << USB_CTL_ODDRST_SHIFT)) & USB_CTL_ODDRST_MASK)

#define USB_CTL_RESUME_MASK  (0x4U)
#define USB_CTL_RESUME_SHIFT (2U)
/*! RESUME - Resume */
#define USB_CTL_RESUME(x) (((uint8_t)(((uint8_t)(x)) << USB_CTL_RESUME_SHIFT)) & USB_CTL_RESUME_MASK)

#define USB_CTL_HOSTMODEEN_MASK  (0x8U)
#define USB_CTL_HOSTMODEEN_SHIFT (3U)
/*! HOSTMODEEN - Host Mode Enable
 *  0b0..USBFS operates in Device mode.
 *  0b1..USBFS operates in Host mode. In Host mode, USBFS performs USB transactions under the programmed control of the host processor.
 */
#define USB_CTL_HOSTMODEEN(x) (((uint8_t)(((uint8_t)(x)) << USB_CTL_HOSTMODEEN_SHIFT)) & USB_CTL_HOSTMODEEN_MASK)

#define USB_CTL_RESET_MASK  (0x10U)
#define USB_CTL_RESET_SHIFT (4U)
/*! RESET - Reset Signaling Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_CTL_RESET(x) (((uint8_t)(((uint8_t)(x)) << USB_CTL_RESET_SHIFT)) & USB_CTL_RESET_MASK)

#define USB_CTL_TXSUSPENDTOKENBUSY_MASK  (0x20U)
#define USB_CTL_TXSUSPENDTOKENBUSY_SHIFT (5U)
/*! TXSUSPENDTOKENBUSY - TXD Suspend And Token Busy */
#define USB_CTL_TXSUSPENDTOKENBUSY(x) (((uint8_t)(((uint8_t)(x)) << USB_CTL_TXSUSPENDTOKENBUSY_SHIFT)) & USB_CTL_TXSUSPENDTOKENBUSY_MASK)

#define USB_CTL_SE0_MASK  (0x40U)
#define USB_CTL_SE0_SHIFT (6U)
/*! SE0 - Live USB Single-Ended Zero signal */
#define USB_CTL_SE0(x) (((uint8_t)(((uint8_t)(x)) << USB_CTL_SE0_SHIFT)) & USB_CTL_SE0_MASK)

#define USB_CTL_JSTATE_MASK  (0x80U)
#define USB_CTL_JSTATE_SHIFT (7U)
/*! JSTATE - Live USB Differential Receiver JSTATE Signal */
#define USB_CTL_JSTATE(x) (((uint8_t)(((uint8_t)(x)) << USB_CTL_JSTATE_SHIFT)) & USB_CTL_JSTATE_MASK)
/*! @} */

/*! @name ADDR - Address */
/*! @{ */

#define USB_ADDR_ADDR_MASK  (0x7FU)
#define USB_ADDR_ADDR_SHIFT (0U)
/*! ADDR - USB Address */
#define USB_ADDR_ADDR(x) (((uint8_t)(((uint8_t)(x)) << USB_ADDR_ADDR_SHIFT)) & USB_ADDR_ADDR_MASK)

#define USB_ADDR_LSEN_MASK  (0x80U)
#define USB_ADDR_LSEN_SHIFT (7U)
/*! LSEN - Low Speed Enable */
#define USB_ADDR_LSEN(x) (((uint8_t)(((uint8_t)(x)) << USB_ADDR_LSEN_SHIFT)) & USB_ADDR_LSEN_MASK)
/*! @} */

/*! @name BDTPAGE1 - BDT Page 1 */
/*! @{ */

#define USB_BDTPAGE1_BDTBA_MASK  (0xFEU)
#define USB_BDTPAGE1_BDTBA_SHIFT (1U)
/*! BDTBA - BDT Base Address */
#define USB_BDTPAGE1_BDTBA(x) (((uint8_t)(((uint8_t)(x)) << USB_BDTPAGE1_BDTBA_SHIFT)) & USB_BDTPAGE1_BDTBA_MASK)
/*! @} */

/*! @name FRMNUML - Frame Number Register Low */
/*! @{ */

#define USB_FRMNUML_FRM_MASK  (0xFFU)
#define USB_FRMNUML_FRM_SHIFT (0U)
/*! FRM - Frame Number, Bits 0-7 */
#define USB_FRMNUML_FRM(x) (((uint8_t)(((uint8_t)(x)) << USB_FRMNUML_FRM_SHIFT)) & USB_FRMNUML_FRM_MASK)
/*! @} */

/*! @name FRMNUMH - Frame Number Register High */
/*! @{ */

#define USB_FRMNUMH_FRM_MASK  (0x7U)
#define USB_FRMNUMH_FRM_SHIFT (0U)
/*! FRM - Frame Number, Bits 8-10 */
#define USB_FRMNUMH_FRM(x) (((uint8_t)(((uint8_t)(x)) << USB_FRMNUMH_FRM_SHIFT)) & USB_FRMNUMH_FRM_MASK)
/*! @} */

/*! @name TOKEN - Token */
/*! @{ */

#define USB_TOKEN_TOKENENDPT_MASK  (0xFU)
#define USB_TOKEN_TOKENENDPT_SHIFT (0U)
/*! TOKENENDPT - Token Endpoint Address */
#define USB_TOKEN_TOKENENDPT(x) (((uint8_t)(((uint8_t)(x)) << USB_TOKEN_TOKENENDPT_SHIFT)) & USB_TOKEN_TOKENENDPT_MASK)

#define USB_TOKEN_TOKENPID_MASK  (0xF0U)
#define USB_TOKEN_TOKENPID_SHIFT (4U)
/*! TOKENPID - Token Type
 *  0b0001..OUT token. USBFS performs an OUT (TX) transaction.
 *  0b1001..IN token. USBFS performs an IN (RX) transaction.
 *  0b1101..SETUP token. USBFS performs a SETUP (TX) transaction
 */
#define USB_TOKEN_TOKENPID(x) (((uint8_t)(((uint8_t)(x)) << USB_TOKEN_TOKENPID_SHIFT)) & USB_TOKEN_TOKENPID_MASK)
/*! @} */

/*! @name SOFTHLD - SOF Threshold */
/*! @{ */

#define USB_SOFTHLD_CNT_MASK  (0xFFU)
#define USB_SOFTHLD_CNT_SHIFT (0U)
/*! CNT - SOF Count Threshold */
#define USB_SOFTHLD_CNT(x) (((uint8_t)(((uint8_t)(x)) << USB_SOFTHLD_CNT_SHIFT)) & USB_SOFTHLD_CNT_MASK)
/*! @} */

/*! @name BDTPAGE2 - BDT Page 2 */
/*! @{ */

#define USB_BDTPAGE2_BDTBA_MASK  (0xFFU)
#define USB_BDTPAGE2_BDTBA_SHIFT (0U)
/*! BDTBA - BDT Base Address */
#define USB_BDTPAGE2_BDTBA(x) (((uint8_t)(((uint8_t)(x)) << USB_BDTPAGE2_BDTBA_SHIFT)) & USB_BDTPAGE2_BDTBA_MASK)
/*! @} */

/*! @name BDTPAGE3 - BDT Page 3 */
/*! @{ */

#define USB_BDTPAGE3_BDTBA_MASK  (0xFFU)
#define USB_BDTPAGE3_BDTBA_SHIFT (0U)
/*! BDTBA - BDT Base Address */
#define USB_BDTPAGE3_BDTBA(x) (((uint8_t)(((uint8_t)(x)) << USB_BDTPAGE3_BDTBA_SHIFT)) & USB_BDTPAGE3_BDTBA_MASK)
/*! @} */

/*! @name ENDPT - Endpoint Control */
/*! @{ */

#define USB_ENDPT_EPHSHK_MASK  (0x1U)
#define USB_ENDPT_EPHSHK_SHIFT (0U)
/*! EPHSHK - Endpoint Handshaking Enable */
#define USB_ENDPT_EPHSHK(x) (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_EPHSHK_SHIFT)) & USB_ENDPT_EPHSHK_MASK)

#define USB_ENDPT_EPSTALL_MASK  (0x2U)
#define USB_ENDPT_EPSTALL_SHIFT (1U)
/*! EPSTALL - Endpoint Stalled */
#define USB_ENDPT_EPSTALL(x) (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_EPSTALL_SHIFT)) & USB_ENDPT_EPSTALL_MASK)

#define USB_ENDPT_EPTXEN_MASK  (0x4U)
#define USB_ENDPT_EPTXEN_SHIFT (2U)
/*! EPTXEN - Endpoint for TX transfers enable */
#define USB_ENDPT_EPTXEN(x) (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_EPTXEN_SHIFT)) & USB_ENDPT_EPTXEN_MASK)

#define USB_ENDPT_EPRXEN_MASK  (0x8U)
#define USB_ENDPT_EPRXEN_SHIFT (3U)
/*! EPRXEN - Endpoint for RX transfers enable */
#define USB_ENDPT_EPRXEN(x) (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_EPRXEN_SHIFT)) & USB_ENDPT_EPRXEN_MASK)

#define USB_ENDPT_EPCTLDIS_MASK  (0x10U)
#define USB_ENDPT_EPCTLDIS_SHIFT (4U)
/*! EPCTLDIS - Control Transfer Disable
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_ENDPT_EPCTLDIS(x) (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_EPCTLDIS_SHIFT)) & USB_ENDPT_EPCTLDIS_MASK)

#define USB_ENDPT_RETRYDIS_MASK  (0x40U)
#define USB_ENDPT_RETRYDIS_SHIFT (6U)
/*! RETRYDIS - Retry Disable
 *  0b0..Retried NAK'ed transactions in hardware.
 *  0b1..Do not retry NAK'ed transactions. When a transaction is NAK'ed, the BDT PID field is updated with the NAK
 *       PID, and the TOKEN_DNE interrupt becomes 1.
 */
#define USB_ENDPT_RETRYDIS(x) (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_RETRYDIS_SHIFT)) & USB_ENDPT_RETRYDIS_MASK)

#define USB_ENDPT_HOSTWOHUB_MASK  (0x80U)
#define USB_ENDPT_HOSTWOHUB_SHIFT (7U)
/*! HOSTWOHUB - Host Without A Hub
 *  0b0..Connected using a hub (USBFS generates PRE_PID as required)
 *  0b1..Connected directly to host without a hub, or was used to attach
 */
#define USB_ENDPT_HOSTWOHUB(x) (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_HOSTWOHUB_SHIFT)) & USB_ENDPT_HOSTWOHUB_MASK)
/*! @} */

/* The count of USB_ENDPT */
#define USB_ENDPT_COUNT (16U)

/*! @name USBCTRL - USB Control */
/*! @{ */

#define USB_USBCTRL_DPDM_LANE_REVERSE_MASK  (0x4U)
#define USB_USBCTRL_DPDM_LANE_REVERSE_SHIFT (2U)
/*! DPDM_LANE_REVERSE - DP and DM Lane Reversal Control
 *  0b0..Standard USB DP and DM package pin assignment
 *  0b1..Reverse roles of USB DP and DM package pins
 */
#define USB_USBCTRL_DPDM_LANE_REVERSE(x) (((uint8_t)(((uint8_t)(x)) << USB_USBCTRL_DPDM_LANE_REVERSE_SHIFT)) & USB_USBCTRL_DPDM_LANE_REVERSE_MASK)

#define USB_USBCTRL_HOST_LS_EOP_MASK  (0x8U)
#define USB_USBCTRL_HOST_LS_EOP_SHIFT (3U)
/*! HOST_LS_EOP - Host-Mode-Only Low-Speed Device EOP Signaling
 *  0b0..Full-speed device or a low-speed device through a hub
 *  0b1..Directly-connected low-speed device
 */
#define USB_USBCTRL_HOST_LS_EOP(x) (((uint8_t)(((uint8_t)(x)) << USB_USBCTRL_HOST_LS_EOP_SHIFT)) & USB_USBCTRL_HOST_LS_EOP_MASK)

#define USB_USBCTRL_UARTSEL_MASK  (0x10U)
#define USB_USBCTRL_UARTSEL_SHIFT (4U)
/*! UARTSEL - UART Select
 *  0b0..USB DP and DM external package pins are used for USB signaling.
 *  0b1..USB DP and DM external package pins are used for UART signaling.
 */
#define USB_USBCTRL_UARTSEL(x) (((uint8_t)(((uint8_t)(x)) << USB_USBCTRL_UARTSEL_SHIFT)) & USB_USBCTRL_UARTSEL_MASK)

#define USB_USBCTRL_UARTCHLS_MASK  (0x20U)
#define USB_USBCTRL_UARTCHLS_SHIFT (5U)
/*! UARTCHLS - UART Signal Channel Select
 *  0b0..USB DP and DM signals are used as UART TX/RX.
 *  0b1..USB DP and DM signals are used as UART RX/TX.
 */
#define USB_USBCTRL_UARTCHLS(x) (((uint8_t)(((uint8_t)(x)) << USB_USBCTRL_UARTCHLS_SHIFT)) & USB_USBCTRL_UARTCHLS_MASK)

#define USB_USBCTRL_PDE_MASK  (0x40U)
#define USB_USBCTRL_PDE_SHIFT (6U)
/*! PDE - Pulldown Enable
 *  0b0..Disable on D+ and D-
 *  0b1..Enable on D+ and D-
 */
#define USB_USBCTRL_PDE(x) (((uint8_t)(((uint8_t)(x)) << USB_USBCTRL_PDE_SHIFT)) & USB_USBCTRL_PDE_MASK)

#define USB_USBCTRL_SUSP_MASK  (0x80U)
#define USB_USBCTRL_SUSP_SHIFT (7U)
/*! SUSP - Suspend
 *  0b0..Not in Suspend state
 *  0b1..In Suspend state
 */
#define USB_USBCTRL_SUSP(x) (((uint8_t)(((uint8_t)(x)) << USB_USBCTRL_SUSP_SHIFT)) & USB_USBCTRL_SUSP_MASK)
/*! @} */

/*! @name OBSERVE - USB OTG Observe */
/*! @{ */

#define USB_OBSERVE_DMPD_MASK  (0x10U)
#define USB_OBSERVE_DMPD_SHIFT (4U)
/*! DMPD - D- Pulldown
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define USB_OBSERVE_DMPD(x) (((uint8_t)(((uint8_t)(x)) << USB_OBSERVE_DMPD_SHIFT)) & USB_OBSERVE_DMPD_MASK)

#define USB_OBSERVE_DPPD_MASK  (0x40U)
#define USB_OBSERVE_DPPD_SHIFT (6U)
/*! DPPD - D+ Pulldown
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define USB_OBSERVE_DPPD(x) (((uint8_t)(((uint8_t)(x)) << USB_OBSERVE_DPPD_SHIFT)) & USB_OBSERVE_DPPD_MASK)

#define USB_OBSERVE_DPPU_MASK  (0x80U)
#define USB_OBSERVE_DPPU_SHIFT (7U)
/*! DPPU - D+ Pullup
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define USB_OBSERVE_DPPU(x) (((uint8_t)(((uint8_t)(x)) << USB_OBSERVE_DPPU_SHIFT)) & USB_OBSERVE_DPPU_MASK)
/*! @} */

/*! @name CONTROL - USB OTG Control */
/*! @{ */

#define USB_CONTROL_VBUS_SOURCE_SEL_MASK  (0x1U)
#define USB_CONTROL_VBUS_SOURCE_SEL_SHIFT (0U)
/*! VBUS_SOURCE_SEL - VBUS Monitoring Source Select
 *  0b0..Reserved
 *  0b1..Resistive divider attached to a GPIO pin
 */
#define USB_CONTROL_VBUS_SOURCE_SEL(x) (((uint8_t)(((uint8_t)(x)) << USB_CONTROL_VBUS_SOURCE_SEL_SHIFT)) & USB_CONTROL_VBUS_SOURCE_SEL_MASK)

#define USB_CONTROL_SESS_VLD_MASK  (0x2U)
#define USB_CONTROL_SESS_VLD_SHIFT (1U)
/*! SESS_VLD - VBUS Session Valid status
 *  0b1..Above
 *  0b0..Below
 */
#define USB_CONTROL_SESS_VLD(x) (((uint8_t)(((uint8_t)(x)) << USB_CONTROL_SESS_VLD_SHIFT)) & USB_CONTROL_SESS_VLD_MASK)

#define USB_CONTROL_DPPULLUPNONOTG_MASK  (0x10U)
#define USB_CONTROL_DPPULLUPNONOTG_SHIFT (4U)
/*! DPPULLUPNONOTG - DP Pullup in Non-OTG Device Mode
 *  0b0..Disable
 *  0b1..Enabled
 */
#define USB_CONTROL_DPPULLUPNONOTG(x) (((uint8_t)(((uint8_t)(x)) << USB_CONTROL_DPPULLUPNONOTG_SHIFT)) & USB_CONTROL_DPPULLUPNONOTG_MASK)
/*! @} */

/*! @name USBTRC0 - USB Transceiver Control 0 */
/*! @{ */

#define USB_USBTRC0_USB_RESUME_INT_MASK  (0x1U)
#define USB_USBTRC0_USB_RESUME_INT_SHIFT (0U)
/*! USB_RESUME_INT - USB Asynchronous Interrupt
 *  0b0..Not generated
 *  0b1..Generated because of the USB asynchronous interrupt
 */
#define USB_USBTRC0_USB_RESUME_INT(x) (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_USB_RESUME_INT_SHIFT)) & USB_USBTRC0_USB_RESUME_INT_MASK)

#define USB_USBTRC0_SYNC_DET_MASK  (0x2U)
#define USB_USBTRC0_SYNC_DET_SHIFT (1U)
/*! SYNC_DET - Synchronous USB Interrupt Detect
 *  0b0..Not detected
 *  0b1..Detected
 */
#define USB_USBTRC0_SYNC_DET(x) (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_SYNC_DET_SHIFT)) & USB_USBTRC0_SYNC_DET_MASK)

#define USB_USBTRC0_USB_CLK_RECOVERY_INT_MASK  (0x4U)
#define USB_USBTRC0_USB_CLK_RECOVERY_INT_SHIFT (2U)
/*! USB_CLK_RECOVERY_INT - Combined USB Clock Recovery interrupt status */
#define USB_USBTRC0_USB_CLK_RECOVERY_INT(x) (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_USB_CLK_RECOVERY_INT_SHIFT)) & USB_USBTRC0_USB_CLK_RECOVERY_INT_MASK)

#define USB_USBTRC0_VREDG_DET_MASK  (0x8U)
#define USB_USBTRC0_VREDG_DET_SHIFT (3U)
/*! VREDG_DET - VREGIN Rising Edge Interrupt Detect
 *  0b0..Not detected
 *  0b1..Detected
 */
#define USB_USBTRC0_VREDG_DET(x) (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_VREDG_DET_SHIFT)) & USB_USBTRC0_VREDG_DET_MASK)

#define USB_USBTRC0_VFEDG_DET_MASK  (0x10U)
#define USB_USBTRC0_VFEDG_DET_SHIFT (4U)
/*! VFEDG_DET - VREGIN Falling Edge Interrupt Detect
 *  0b0..Not detected
 *  0b1..Detected
 */
#define USB_USBTRC0_VFEDG_DET(x) (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_VFEDG_DET_SHIFT)) & USB_USBTRC0_VFEDG_DET_MASK)

#define USB_USBTRC0_USBRESMEN_MASK  (0x20U)
#define USB_USBTRC0_USBRESMEN_SHIFT (5U)
/*! USBRESMEN - Asynchronous Resume Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_USBTRC0_USBRESMEN(x) (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_USBRESMEN_SHIFT)) & USB_USBTRC0_USBRESMEN_MASK)

#define USB_USBTRC0_VREGIN_STS_MASK  (0x40U)
#define USB_USBTRC0_VREGIN_STS_SHIFT (6U)
/*! VREGIN_STS - VREGIN Status */
#define USB_USBTRC0_VREGIN_STS(x) (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_VREGIN_STS_SHIFT)) & USB_USBTRC0_VREGIN_STS_MASK)

#define USB_USBTRC0_USBRESET_MASK  (0x80U)
#define USB_USBTRC0_USBRESET_SHIFT (7U)
/*! USBRESET - USB Reset
 *  0b0..Normal USBFS operation
 *  0b1..Returns USBFS to its reset state
 */
#define USB_USBTRC0_USBRESET(x) (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_USBRESET_SHIFT)) & USB_USBTRC0_USBRESET_MASK)
/*! @} */

/*! @name USBFRMADJUST - Frame Adjust */
/*! @{ */

#define USB_USBFRMADJUST_ADJ_MASK  (0xFFU)
#define USB_USBFRMADJUST_ADJ_SHIFT (0U)
/*! ADJ - Frame Adjustment */
#define USB_USBFRMADJUST_ADJ(x) (((uint8_t)(((uint8_t)(x)) << USB_USBFRMADJUST_ADJ_SHIFT)) & USB_USBFRMADJUST_ADJ_MASK)
/*! @} */

/*! @name KEEP_ALIVE_CTRL - Keep Alive Mode Control */
/*! @{ */

#define USB_KEEP_ALIVE_CTRL_KEEP_ALIVE_EN_MASK  (0x1U)
#define USB_KEEP_ALIVE_CTRL_KEEP_ALIVE_EN_SHIFT (0U)
/*! KEEP_ALIVE_EN - Keep Alive Mode Enable
 *  0b0..Everything remains same as before.
 *  0b1..USB shall enter USB_KEEP_ALIVE mode after asserting ipg_stop.
 */
#define USB_KEEP_ALIVE_CTRL_KEEP_ALIVE_EN(x) (((uint8_t)(((uint8_t)(x)) << USB_KEEP_ALIVE_CTRL_KEEP_ALIVE_EN_SHIFT)) & USB_KEEP_ALIVE_CTRL_KEEP_ALIVE_EN_MASK)

#define USB_KEEP_ALIVE_CTRL_OWN_OVERRD_EN_MASK  (0x2U)
#define USB_KEEP_ALIVE_CTRL_OWN_OVERRD_EN_SHIFT (1U)
/*! OWN_OVERRD_EN - OWN Bit Override Enable */
#define USB_KEEP_ALIVE_CTRL_OWN_OVERRD_EN(x) (((uint8_t)(((uint8_t)(x)) << USB_KEEP_ALIVE_CTRL_OWN_OVERRD_EN_SHIFT)) & USB_KEEP_ALIVE_CTRL_OWN_OVERRD_EN_MASK)

#define USB_KEEP_ALIVE_CTRL_STOP_ACK_DLY_EN_MASK  (0x4U)
#define USB_KEEP_ALIVE_CTRL_STOP_ACK_DLY_EN_SHIFT (2U)
/*! STOP_ACK_DLY_EN - Stop Acknowledge Delay Enable
 *  0b0..Enter KEEP_ALIVE mode immediately when there is no USB AHB transfer.
 *  0b1..Enter KEEP_ALIVE mode until the USB core is idle and there is no USB AHB transfer.
 */
#define USB_KEEP_ALIVE_CTRL_STOP_ACK_DLY_EN(x) (((uint8_t)(((uint8_t)(x)) << USB_KEEP_ALIVE_CTRL_STOP_ACK_DLY_EN_SHIFT)) & USB_KEEP_ALIVE_CTRL_STOP_ACK_DLY_EN_MASK)

#define USB_KEEP_ALIVE_CTRL_WAKE_REQ_EN_MASK  (0x8U)
#define USB_KEEP_ALIVE_CTRL_WAKE_REQ_EN_SHIFT (3U)
/*! WAKE_REQ_EN - Wakeup Request Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_KEEP_ALIVE_CTRL_WAKE_REQ_EN(x) (((uint8_t)(((uint8_t)(x)) << USB_KEEP_ALIVE_CTRL_WAKE_REQ_EN_SHIFT)) & USB_KEEP_ALIVE_CTRL_WAKE_REQ_EN_MASK)

#define USB_KEEP_ALIVE_CTRL_WAKE_INT_EN_MASK  (0x10U)
#define USB_KEEP_ALIVE_CTRL_WAKE_INT_EN_SHIFT (4U)
/*! WAKE_INT_EN - Wakeup Interrupt Enable */
#define USB_KEEP_ALIVE_CTRL_WAKE_INT_EN(x) (((uint8_t)(((uint8_t)(x)) << USB_KEEP_ALIVE_CTRL_WAKE_INT_EN_SHIFT)) & USB_KEEP_ALIVE_CTRL_WAKE_INT_EN_MASK)

#define USB_KEEP_ALIVE_CTRL_KEEP_ALIVE_STS_MASK  (0x40U)
#define USB_KEEP_ALIVE_CTRL_KEEP_ALIVE_STS_SHIFT (6U)
/*! KEEP_ALIVE_STS - Keep Alive Status
 *  0b0..Not in Keep Alive mode
 *  0b1..In Keep Alive mode
 */
#define USB_KEEP_ALIVE_CTRL_KEEP_ALIVE_STS(x) (((uint8_t)(((uint8_t)(x)) << USB_KEEP_ALIVE_CTRL_KEEP_ALIVE_STS_SHIFT)) & USB_KEEP_ALIVE_CTRL_KEEP_ALIVE_STS_MASK)

#define USB_KEEP_ALIVE_CTRL_WAKE_INT_STS_MASK  (0x80U)
#define USB_KEEP_ALIVE_CTRL_WAKE_INT_STS_SHIFT (7U)
/*! WAKE_INT_STS - Wakeup Interrupt Status Flag
 *  0b0..Interrupt did not occur
 *  0b1..Interrupt occurred
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define USB_KEEP_ALIVE_CTRL_WAKE_INT_STS(x) (((uint8_t)(((uint8_t)(x)) << USB_KEEP_ALIVE_CTRL_WAKE_INT_STS_SHIFT)) & USB_KEEP_ALIVE_CTRL_WAKE_INT_STS_MASK)
/*! @} */

/*! @name KEEP_ALIVE_WKCTRL - Keep Alive Mode Wakeup Control */
/*! @{ */

#define USB_KEEP_ALIVE_WKCTRL_WAKE_ON_THIS_MASK  (0xFU)
#define USB_KEEP_ALIVE_WKCTRL_WAKE_ON_THIS_SHIFT (0U)
/*! WAKE_ON_THIS - Token PID for the wakeup request
 *  0b0001..Wake up after receiving OUT or SETUP token packet.
 *  0b1101..Wake up after receiving SETUP token packet. All other values are reserved.
 */
#define USB_KEEP_ALIVE_WKCTRL_WAKE_ON_THIS(x) (((uint8_t)(((uint8_t)(x)) << USB_KEEP_ALIVE_WKCTRL_WAKE_ON_THIS_SHIFT)) & USB_KEEP_ALIVE_WKCTRL_WAKE_ON_THIS_MASK)

#define USB_KEEP_ALIVE_WKCTRL_WAKE_ENDPT_MASK  (0xF0U)
#define USB_KEEP_ALIVE_WKCTRL_WAKE_ENDPT_SHIFT (4U)
/*! WAKE_ENDPT - Endpoint address for the wakeup request */
#define USB_KEEP_ALIVE_WKCTRL_WAKE_ENDPT(x) (((uint8_t)(((uint8_t)(x)) << USB_KEEP_ALIVE_WKCTRL_WAKE_ENDPT_SHIFT)) & USB_KEEP_ALIVE_WKCTRL_WAKE_ENDPT_MASK)
/*! @} */

/*! @name MISCCTRL - Miscellaneous Control */
/*! @{ */

#define USB_MISCCTRL_SOFDYNTHLD_MASK  (0x1U)
#define USB_MISCCTRL_SOFDYNTHLD_SHIFT (0U)
/*! SOFDYNTHLD - Dynamic SOF Threshold Compare mode
 *  0b0..When the byte-times SOF threshold is reached
 *  0b1..When 8 byte-times SOF threshold is reached or overstepped
 */
#define USB_MISCCTRL_SOFDYNTHLD(x) (((uint8_t)(((uint8_t)(x)) << USB_MISCCTRL_SOFDYNTHLD_SHIFT)) & USB_MISCCTRL_SOFDYNTHLD_MASK)

#define USB_MISCCTRL_SOFBUSSET_MASK  (0x2U)
#define USB_MISCCTRL_SOFBUSSET_SHIFT (1U)
/*! SOFBUSSET - SOF_TOK Interrupt Generation Mode Select
 *  0b0..According to the SOF threshold value
 *  0b1..When the SOF counter reaches 0
 */
#define USB_MISCCTRL_SOFBUSSET(x) (((uint8_t)(((uint8_t)(x)) << USB_MISCCTRL_SOFBUSSET_SHIFT)) & USB_MISCCTRL_SOFBUSSET_MASK)

#define USB_MISCCTRL_OWNERRISODIS_MASK  (0x4U)
#define USB_MISCCTRL_OWNERRISODIS_SHIFT (2U)
/*! OWNERRISODIS - OWN Error Detect for ISO IN and ISO OUT Disable
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_MISCCTRL_OWNERRISODIS(x) (((uint8_t)(((uint8_t)(x)) << USB_MISCCTRL_OWNERRISODIS_SHIFT)) & USB_MISCCTRL_OWNERRISODIS_MASK)

#define USB_MISCCTRL_VREDG_EN_MASK  (0x8U)
#define USB_MISCCTRL_VREDG_EN_SHIFT (3U)
/*! VREDG_EN - VREGIN Rising Edge Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_MISCCTRL_VREDG_EN(x) (((uint8_t)(((uint8_t)(x)) << USB_MISCCTRL_VREDG_EN_SHIFT)) & USB_MISCCTRL_VREDG_EN_MASK)

#define USB_MISCCTRL_VFEDG_EN_MASK  (0x10U)
#define USB_MISCCTRL_VFEDG_EN_SHIFT (4U)
/*! VFEDG_EN - VREGIN Falling Edge Interrupt Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_MISCCTRL_VFEDG_EN(x) (((uint8_t)(((uint8_t)(x)) << USB_MISCCTRL_VFEDG_EN_SHIFT)) & USB_MISCCTRL_VFEDG_EN_MASK)

#define USB_MISCCTRL_STL_ADJ_EN_MASK  (0x80U)
#define USB_MISCCTRL_STL_ADJ_EN_SHIFT (7U)
/*! STL_ADJ_EN - USB Peripheral Mode Stall Adjust Enable
 *  0b0..If ENDPTn[END_STALL] = 1, both IN and OUT directions for the associated endpoint stalls.
 *  0b1..If ENDPTn[END_STALL] = 1, the STALL_xx_DIS registers control which directions for the associated endpoint stalls.
 */
#define USB_MISCCTRL_STL_ADJ_EN(x) (((uint8_t)(((uint8_t)(x)) << USB_MISCCTRL_STL_ADJ_EN_SHIFT)) & USB_MISCCTRL_STL_ADJ_EN_MASK)
/*! @} */

/*! @name STALL_IL_DIS - Peripheral Mode Stall Disable for Endpoints 7 to 0 in IN Direction */
/*! @{ */

#define USB_STALL_IL_DIS_STALL_I_DIS0_MASK  (0x1U)
#define USB_STALL_IL_DIS_STALL_I_DIS0_SHIFT (0U)
/*! STALL_I_DIS0 - Disable Endpoint 0 IN Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_IL_DIS_STALL_I_DIS0(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_IL_DIS_STALL_I_DIS0_SHIFT)) & USB_STALL_IL_DIS_STALL_I_DIS0_MASK)

#define USB_STALL_IL_DIS_STALL_I_DIS1_MASK  (0x2U)
#define USB_STALL_IL_DIS_STALL_I_DIS1_SHIFT (1U)
/*! STALL_I_DIS1 - Disable Endpoint 1 IN Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_IL_DIS_STALL_I_DIS1(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_IL_DIS_STALL_I_DIS1_SHIFT)) & USB_STALL_IL_DIS_STALL_I_DIS1_MASK)

#define USB_STALL_IL_DIS_STALL_I_DIS2_MASK  (0x4U)
#define USB_STALL_IL_DIS_STALL_I_DIS2_SHIFT (2U)
/*! STALL_I_DIS2 - Disable Endpoint 2 IN Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_IL_DIS_STALL_I_DIS2(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_IL_DIS_STALL_I_DIS2_SHIFT)) & USB_STALL_IL_DIS_STALL_I_DIS2_MASK)

#define USB_STALL_IL_DIS_STALL_I_DIS3_MASK  (0x8U)
#define USB_STALL_IL_DIS_STALL_I_DIS3_SHIFT (3U)
/*! STALL_I_DIS3 - Disable Endpoint 3 IN Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_IL_DIS_STALL_I_DIS3(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_IL_DIS_STALL_I_DIS3_SHIFT)) & USB_STALL_IL_DIS_STALL_I_DIS3_MASK)

#define USB_STALL_IL_DIS_STALL_I_DIS4_MASK  (0x10U)
#define USB_STALL_IL_DIS_STALL_I_DIS4_SHIFT (4U)
/*! STALL_I_DIS4 - Disable Endpoint 4 IN Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_IL_DIS_STALL_I_DIS4(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_IL_DIS_STALL_I_DIS4_SHIFT)) & USB_STALL_IL_DIS_STALL_I_DIS4_MASK)

#define USB_STALL_IL_DIS_STALL_I_DIS5_MASK  (0x20U)
#define USB_STALL_IL_DIS_STALL_I_DIS5_SHIFT (5U)
/*! STALL_I_DIS5 - Disable Endpoint 5 IN Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_IL_DIS_STALL_I_DIS5(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_IL_DIS_STALL_I_DIS5_SHIFT)) & USB_STALL_IL_DIS_STALL_I_DIS5_MASK)

#define USB_STALL_IL_DIS_STALL_I_DIS6_MASK  (0x40U)
#define USB_STALL_IL_DIS_STALL_I_DIS6_SHIFT (6U)
/*! STALL_I_DIS6 - Disable Endpoint 6 IN Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_IL_DIS_STALL_I_DIS6(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_IL_DIS_STALL_I_DIS6_SHIFT)) & USB_STALL_IL_DIS_STALL_I_DIS6_MASK)

#define USB_STALL_IL_DIS_STALL_I_DIS7_MASK  (0x80U)
#define USB_STALL_IL_DIS_STALL_I_DIS7_SHIFT (7U)
/*! STALL_I_DIS7 - Disable Endpoint 7 IN Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_IL_DIS_STALL_I_DIS7(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_IL_DIS_STALL_I_DIS7_SHIFT)) & USB_STALL_IL_DIS_STALL_I_DIS7_MASK)
/*! @} */

/*! @name STALL_IH_DIS - Peripheral Mode Stall Disable for Endpoints 15 to 8 in IN Direction */
/*! @{ */

#define USB_STALL_IH_DIS_STALL_I_DIS8_MASK  (0x1U)
#define USB_STALL_IH_DIS_STALL_I_DIS8_SHIFT (0U)
/*! STALL_I_DIS8 - Disable Endpoint 8 IN Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_IH_DIS_STALL_I_DIS8(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_IH_DIS_STALL_I_DIS8_SHIFT)) & USB_STALL_IH_DIS_STALL_I_DIS8_MASK)

#define USB_STALL_IH_DIS_STALL_I_DIS9_MASK  (0x2U)
#define USB_STALL_IH_DIS_STALL_I_DIS9_SHIFT (1U)
/*! STALL_I_DIS9 - Disable Endpoint 9 IN Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_IH_DIS_STALL_I_DIS9(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_IH_DIS_STALL_I_DIS9_SHIFT)) & USB_STALL_IH_DIS_STALL_I_DIS9_MASK)

#define USB_STALL_IH_DIS_STALL_I_DIS10_MASK  (0x4U)
#define USB_STALL_IH_DIS_STALL_I_DIS10_SHIFT (2U)
/*! STALL_I_DIS10 - Disable Endpoint 10 IN Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_IH_DIS_STALL_I_DIS10(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_IH_DIS_STALL_I_DIS10_SHIFT)) & USB_STALL_IH_DIS_STALL_I_DIS10_MASK)

#define USB_STALL_IH_DIS_STALL_I_DIS11_MASK  (0x8U)
#define USB_STALL_IH_DIS_STALL_I_DIS11_SHIFT (3U)
/*! STALL_I_DIS11 - Disable Endpoint 11 IN Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_IH_DIS_STALL_I_DIS11(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_IH_DIS_STALL_I_DIS11_SHIFT)) & USB_STALL_IH_DIS_STALL_I_DIS11_MASK)

#define USB_STALL_IH_DIS_STALL_I_DIS12_MASK  (0x10U)
#define USB_STALL_IH_DIS_STALL_I_DIS12_SHIFT (4U)
/*! STALL_I_DIS12 - Disable Endpoint 12 IN Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_IH_DIS_STALL_I_DIS12(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_IH_DIS_STALL_I_DIS12_SHIFT)) & USB_STALL_IH_DIS_STALL_I_DIS12_MASK)

#define USB_STALL_IH_DIS_STALL_I_DIS13_MASK  (0x20U)
#define USB_STALL_IH_DIS_STALL_I_DIS13_SHIFT (5U)
/*! STALL_I_DIS13 - Disable Endpoint 13 IN Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_IH_DIS_STALL_I_DIS13(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_IH_DIS_STALL_I_DIS13_SHIFT)) & USB_STALL_IH_DIS_STALL_I_DIS13_MASK)

#define USB_STALL_IH_DIS_STALL_I_DIS14_MASK  (0x40U)
#define USB_STALL_IH_DIS_STALL_I_DIS14_SHIFT (6U)
/*! STALL_I_DIS14 - Disable Endpoint 14 IN Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_IH_DIS_STALL_I_DIS14(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_IH_DIS_STALL_I_DIS14_SHIFT)) & USB_STALL_IH_DIS_STALL_I_DIS14_MASK)

#define USB_STALL_IH_DIS_STALL_I_DIS15_MASK  (0x80U)
#define USB_STALL_IH_DIS_STALL_I_DIS15_SHIFT (7U)
/*! STALL_I_DIS15 - Disable Endpoint 15 IN Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_IH_DIS_STALL_I_DIS15(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_IH_DIS_STALL_I_DIS15_SHIFT)) & USB_STALL_IH_DIS_STALL_I_DIS15_MASK)
/*! @} */

/*! @name STALL_OL_DIS - Peripheral Mode Stall Disable for Endpoints 7 to 0 in OUT Direction */
/*! @{ */

#define USB_STALL_OL_DIS_STALL_O_DIS0_MASK  (0x1U)
#define USB_STALL_OL_DIS_STALL_O_DIS0_SHIFT (0U)
/*! STALL_O_DIS0 - Disable Endpoint 0 OUT Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_OL_DIS_STALL_O_DIS0(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_OL_DIS_STALL_O_DIS0_SHIFT)) & USB_STALL_OL_DIS_STALL_O_DIS0_MASK)

#define USB_STALL_OL_DIS_STALL_O_DIS1_MASK  (0x2U)
#define USB_STALL_OL_DIS_STALL_O_DIS1_SHIFT (1U)
/*! STALL_O_DIS1 - Disable Endpoint 1 OUT Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_OL_DIS_STALL_O_DIS1(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_OL_DIS_STALL_O_DIS1_SHIFT)) & USB_STALL_OL_DIS_STALL_O_DIS1_MASK)

#define USB_STALL_OL_DIS_STALL_O_DIS2_MASK  (0x4U)
#define USB_STALL_OL_DIS_STALL_O_DIS2_SHIFT (2U)
/*! STALL_O_DIS2 - Disable Endpoint 2 OUT Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_OL_DIS_STALL_O_DIS2(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_OL_DIS_STALL_O_DIS2_SHIFT)) & USB_STALL_OL_DIS_STALL_O_DIS2_MASK)

#define USB_STALL_OL_DIS_STALL_O_DIS3_MASK  (0x8U)
#define USB_STALL_OL_DIS_STALL_O_DIS3_SHIFT (3U)
/*! STALL_O_DIS3 - Disable Endpoint 3 OUT Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_OL_DIS_STALL_O_DIS3(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_OL_DIS_STALL_O_DIS3_SHIFT)) & USB_STALL_OL_DIS_STALL_O_DIS3_MASK)

#define USB_STALL_OL_DIS_STALL_O_DIS4_MASK  (0x10U)
#define USB_STALL_OL_DIS_STALL_O_DIS4_SHIFT (4U)
/*! STALL_O_DIS4 - Disable Endpoint 4 OUT Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_OL_DIS_STALL_O_DIS4(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_OL_DIS_STALL_O_DIS4_SHIFT)) & USB_STALL_OL_DIS_STALL_O_DIS4_MASK)

#define USB_STALL_OL_DIS_STALL_O_DIS5_MASK  (0x20U)
#define USB_STALL_OL_DIS_STALL_O_DIS5_SHIFT (5U)
/*! STALL_O_DIS5 - Disable Endpoint 5 OUT Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_OL_DIS_STALL_O_DIS5(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_OL_DIS_STALL_O_DIS5_SHIFT)) & USB_STALL_OL_DIS_STALL_O_DIS5_MASK)

#define USB_STALL_OL_DIS_STALL_O_DIS6_MASK  (0x40U)
#define USB_STALL_OL_DIS_STALL_O_DIS6_SHIFT (6U)
/*! STALL_O_DIS6 - Disable Endpoint 6 OUT Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_OL_DIS_STALL_O_DIS6(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_OL_DIS_STALL_O_DIS6_SHIFT)) & USB_STALL_OL_DIS_STALL_O_DIS6_MASK)

#define USB_STALL_OL_DIS_STALL_O_DIS7_MASK  (0x80U)
#define USB_STALL_OL_DIS_STALL_O_DIS7_SHIFT (7U)
/*! STALL_O_DIS7 - Disable Endpoint 7 OUT Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_OL_DIS_STALL_O_DIS7(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_OL_DIS_STALL_O_DIS7_SHIFT)) & USB_STALL_OL_DIS_STALL_O_DIS7_MASK)
/*! @} */

/*! @name STALL_OH_DIS - Peripheral Mode Stall Disable for Endpoints 15 to 8 in OUT Direction */
/*! @{ */

#define USB_STALL_OH_DIS_STALL_O_DIS8_MASK  (0x1U)
#define USB_STALL_OH_DIS_STALL_O_DIS8_SHIFT (0U)
/*! STALL_O_DIS8 - Disable Endpoint 8 OUT Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_OH_DIS_STALL_O_DIS8(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_OH_DIS_STALL_O_DIS8_SHIFT)) & USB_STALL_OH_DIS_STALL_O_DIS8_MASK)

#define USB_STALL_OH_DIS_STALL_O_DIS9_MASK  (0x2U)
#define USB_STALL_OH_DIS_STALL_O_DIS9_SHIFT (1U)
/*! STALL_O_DIS9 - Disable Endpoint 9 OUT Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_OH_DIS_STALL_O_DIS9(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_OH_DIS_STALL_O_DIS9_SHIFT)) & USB_STALL_OH_DIS_STALL_O_DIS9_MASK)

#define USB_STALL_OH_DIS_STALL_O_DIS10_MASK  (0x4U)
#define USB_STALL_OH_DIS_STALL_O_DIS10_SHIFT (2U)
/*! STALL_O_DIS10 - Disable Endpoint 10 OUT Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_OH_DIS_STALL_O_DIS10(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_OH_DIS_STALL_O_DIS10_SHIFT)) & USB_STALL_OH_DIS_STALL_O_DIS10_MASK)

#define USB_STALL_OH_DIS_STALL_O_DIS11_MASK  (0x8U)
#define USB_STALL_OH_DIS_STALL_O_DIS11_SHIFT (3U)
/*! STALL_O_DIS11 - Disable Endpoint 11 OUT Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_OH_DIS_STALL_O_DIS11(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_OH_DIS_STALL_O_DIS11_SHIFT)) & USB_STALL_OH_DIS_STALL_O_DIS11_MASK)

#define USB_STALL_OH_DIS_STALL_O_DIS12_MASK  (0x10U)
#define USB_STALL_OH_DIS_STALL_O_DIS12_SHIFT (4U)
/*! STALL_O_DIS12 - Disable endpoint 12 OUT direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_OH_DIS_STALL_O_DIS12(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_OH_DIS_STALL_O_DIS12_SHIFT)) & USB_STALL_OH_DIS_STALL_O_DIS12_MASK)

#define USB_STALL_OH_DIS_STALL_O_DIS13_MASK  (0x20U)
#define USB_STALL_OH_DIS_STALL_O_DIS13_SHIFT (5U)
/*! STALL_O_DIS13 - Disable Endpoint 13 OUT Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_OH_DIS_STALL_O_DIS13(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_OH_DIS_STALL_O_DIS13_SHIFT)) & USB_STALL_OH_DIS_STALL_O_DIS13_MASK)

#define USB_STALL_OH_DIS_STALL_O_DIS14_MASK  (0x40U)
#define USB_STALL_OH_DIS_STALL_O_DIS14_SHIFT (6U)
/*! STALL_O_DIS14 - Disable Endpoint 14 OUT Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_OH_DIS_STALL_O_DIS14(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_OH_DIS_STALL_O_DIS14_SHIFT)) & USB_STALL_OH_DIS_STALL_O_DIS14_MASK)

#define USB_STALL_OH_DIS_STALL_O_DIS15_MASK  (0x80U)
#define USB_STALL_OH_DIS_STALL_O_DIS15_SHIFT (7U)
/*! STALL_O_DIS15 - Disable Endpoint 15 OUT Direction
 *  0b0..Enable
 *  0b1..Disable
 */
#define USB_STALL_OH_DIS_STALL_O_DIS15(x) (((uint8_t)(((uint8_t)(x)) << USB_STALL_OH_DIS_STALL_O_DIS15_SHIFT)) & USB_STALL_OH_DIS_STALL_O_DIS15_MASK)
/*! @} */

/*! @name CLK_RECOVER_CTRL - USB Clock Recovery Control */
/*! @{ */

#define USB_CLK_RECOVER_CTRL_TRIM_INIT_VAL_SEL_MASK  (0x8U)
#define USB_CLK_RECOVER_CTRL_TRIM_INIT_VAL_SEL_SHIFT (3U)
/*! TRIM_INIT_VAL_SEL - Selects the source for the initial FIRC trim fine value used after a reset.
 *  0b0..Mid-scale
 *  0b1..IFR
 */
#define USB_CLK_RECOVER_CTRL_TRIM_INIT_VAL_SEL(x) (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_CTRL_TRIM_INIT_VAL_SEL_SHIFT)) & USB_CLK_RECOVER_CTRL_TRIM_INIT_VAL_SEL_MASK)

#define USB_CLK_RECOVER_CTRL_RESTART_IFRTRIM_EN_MASK  (0x20U)
#define USB_CLK_RECOVER_CTRL_RESTART_IFRTRIM_EN_SHIFT (5U)
/*! RESTART_IFRTRIM_EN - Restart from IFR Trim Value
 *  0b0..Trim fine adjustment always works based on the previous updated trim fine value.
 *  0b1..Trim fine restarts from the IFR trim value whenever you detect bus_reset or bus_resume or deassert module enable.
 */
#define USB_CLK_RECOVER_CTRL_RESTART_IFRTRIM_EN(x) (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_CTRL_RESTART_IFRTRIM_EN_SHIFT)) & USB_CLK_RECOVER_CTRL_RESTART_IFRTRIM_EN_MASK)

#define USB_CLK_RECOVER_CTRL_RESET_RESUME_ROUGH_EN_MASK  (0x40U)
#define USB_CLK_RECOVER_CTRL_RESET_RESUME_ROUGH_EN_SHIFT (6U)
/*! RESET_RESUME_ROUGH_EN - Reset or Resume to Rough Phase Enable
 *  0b0..Always works in tracking phase after the first time rough phase, to track transition.
 *  0b1..Go back to rough stage whenever a bus reset or bus resume occurs.
 */
#define USB_CLK_RECOVER_CTRL_RESET_RESUME_ROUGH_EN(x) (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_CTRL_RESET_RESUME_ROUGH_EN_SHIFT)) & USB_CLK_RECOVER_CTRL_RESET_RESUME_ROUGH_EN_MASK)

#define USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_MASK  (0x80U)
#define USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_SHIFT (7U)
/*! CLOCK_RECOVER_EN - Crystal-Less USB Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN(x) (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_SHIFT)) & USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_MASK)
/*! @} */

/*! @name CLK_RECOVER_IRC_EN - FIRC Oscillator Enable */
/*! @{ */

#define USB_CLK_RECOVER_IRC_EN_IRC_EN_MASK  (0x2U)
#define USB_CLK_RECOVER_IRC_EN_IRC_EN_SHIFT (1U)
/*! IRC_EN - Fast IRC enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define USB_CLK_RECOVER_IRC_EN_IRC_EN(x) (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_IRC_EN_IRC_EN_SHIFT)) & USB_CLK_RECOVER_IRC_EN_IRC_EN_MASK)
/*! @} */

/*! @name CLK_RECOVER_INT_EN - Clock Recovery Combined Interrupt Enable */
/*! @{ */

#define USB_CLK_RECOVER_INT_EN_OVF_ERROR_EN_MASK  (0x10U)
#define USB_CLK_RECOVER_INT_EN_OVF_ERROR_EN_SHIFT (4U)
/*! OVF_ERROR_EN - Overflow error interrupt enable
 *  0b0..The interrupt is masked
 *  0b1..The interrupt is enabled
 */
#define USB_CLK_RECOVER_INT_EN_OVF_ERROR_EN(x) (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_INT_EN_OVF_ERROR_EN_SHIFT)) & USB_CLK_RECOVER_INT_EN_OVF_ERROR_EN_MASK)
/*! @} */

/*! @name CLK_RECOVER_INT_STATUS - Clock Recovery Separated Interrupt Status */
/*! @{ */

#define USB_CLK_RECOVER_INT_STATUS_OVF_ERROR_MASK  (0x10U)
#define USB_CLK_RECOVER_INT_STATUS_OVF_ERROR_SHIFT (4U)
/*! OVF_ERROR - Overflow Error Interrupt Status Flag
 *  0b0..Interrupt did not occur
 *  0b1..Unmasked interrupt occurred
 *  0b0..No effect
 *  0b1..Clear the flag
 */
#define USB_CLK_RECOVER_INT_STATUS_OVF_ERROR(x) (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_INT_STATUS_OVF_ERROR_SHIFT)) & USB_CLK_RECOVER_INT_STATUS_OVF_ERROR_MASK)
/*! @} */

/*!
 * @}
 */
/* end of group USB_Register_Masks */

/*!
 * @brief This type of structure instance is used to implement the buffer descriptor for USB.
 */
typedef struct
{
    union {
        uint32_t head; /*!< Head. */
        struct
        {
            uint32_t reserved0 : 2;  /*!< RESEVED. */
            uint32_t bdt_stall : 1;  /*!< Stall. */
            uint32_t dts       : 1;  /*!< Data shift sync. */
            uint32_t ninc      : 1;  /*!< DMA addr cannot increasing. */
            uint32_t keep      : 1;  /*!< Keep BD held by USB. */
            uint32_t data      : 1;  /*!< DATA0 or DATA1. */
            uint32_t own       : 1;  /*!< Owner, 0 is CPU, 1 is USB. */
            uint32_t reserved1 : 8;  /*!< RESEVED. */
            uint32_t bc        : 10; /*!< Packet size. */
            uint32_t reserved2 : 6;  /*!< RESEVED. */
        };
        struct
        {
            uint32_t reserved3 : 2;  /*!< RESEVED. */
            uint32_t tok_pid   : 4;  /*!< Token pid. */
            uint32_t reserved4 : 26; /*!< RESEVED. */
        };
    };
    uint32_t addr; /*!< Buffer addr. */
} kinetis_bd_t;

/*!
 * @brief This type of structure instance is used to implement the buffer descriptor table for USB.
 */
typedef union {
    kinetis_bd_t table[16][2][2]; /*!< [EndPoint] [Direction] [Odd_Even]. */
    uint8_t buffer[512];              /*!< buffer. */
} kinetis_bd_table_t;

/**
  * @brief USBFS TokenPid type.
  */
typedef enum {
    USB_TOKEN_PID_OUT = 0x1u,        /*!< USB Token Pid: OUT.   */
    USB_TOKEN_PID_IN = 0x9u,         /*!< USB Token Pid: IN.    */
    USB_TOKEN_PID_SETUP = 0xDu,      /*!< USB Token Pid: SETUP. */
    USB_TOKEN_PID_DATA0 = 0x03,      /*!< USB Token Pid: DATA0. */
    USB_TOKEN_PID_DATA1 = 0x0B,      /*!< USB Token Pid: DATA1. */
    USB_TOKEN_PID_ACK = 0x02,        /*!< USB Token Pid: ACK.   */
    USB_TOKEN_PID_STALL = 0x0E,      /*!< USB Token Pid: STALL. */
    USB_TOKEN_PID_NAK = 0x0A,        /*!< USB Token Pid: NAK.   */
    USB_TOKEN_PID_BUSTIMEOUT = 0x00, /*!< USB Token Pid: BUSTO. */
    USB_TOKEN_PID_ERR = 0x0f,        /*!< USB Token Pid: ERR.   */
} USB_TOKEN_PID_Type;

typedef struct {
    KINETIS_TypeDef base;
    __IO uint8_t USBCTRL; /**< USB Control, offset: 0x100 */
    uint8_t RESERVED_22[3];
    __I uint8_t OBSERVE; /**< USB OTG Observe, offset: 0x104 */
    uint8_t RESERVED_23[3];
    __IO uint8_t CONTROL; /**< USB OTG Control, offset: 0x108 */
    uint8_t RESERVED_24[3];
    __IO uint8_t USBTRC0; /**< USB Transceiver Control 0, offset: 0x10C */
    uint8_t RESERVED_25[7];
    __IO uint8_t USBFRMADJUST; /**< Frame Adjust, offset: 0x114 */
    uint8_t RESERVED_26[15];
    __IO uint8_t KEEP_ALIVE_CTRL; /**< Keep Alive Mode Control, offset: 0x124 */
    uint8_t RESERVED_27[3];
    __IO uint8_t KEEP_ALIVE_WKCTRL; /**< Keep Alive Mode Wakeup Control, offset: 0x128 */
    uint8_t RESERVED_28[3];
    __IO uint8_t MISCCTRL; /**< Miscellaneous Control, offset: 0x12C */
    uint8_t RESERVED_29[3];
    __IO uint8_t STALL_IL_DIS; /**< Peripheral Mode Stall Disable for Endpoints 7 to 0 in IN Direction, offset: 0x130 */
    uint8_t RESERVED_30[3];
    __IO uint8_t STALL_IH_DIS; /**< Peripheral Mode Stall Disable for Endpoints 15 to 8 in IN Direction, offset: 0x134 */
    uint8_t RESERVED_31[3];
    __IO uint8_t STALL_OL_DIS; /**< Peripheral Mode Stall Disable for Endpoints 7 to 0 in OUT Direction, offset: 0x138 */
    uint8_t RESERVED_32[3];
    __IO uint8_t STALL_OH_DIS; /**< Peripheral Mode Stall Disable for Endpoints 15 to 8 in OUT Direction, offset: 0x13C */
    uint8_t RESERVED_33[3];
    __IO uint8_t CLK_RECOVER_CTRL; /**< USB Clock Recovery Control, offset: 0x140 */
    uint8_t RESERVED_34[3];
    __IO uint8_t CLK_RECOVER_IRC_EN; /**< FIRC Oscillator Enable, offset: 0x144 */
    uint8_t RESERVED_35[15];
    __IO uint8_t CLK_RECOVER_INT_EN; /**< Clock Recovery Combined Interrupt Enable, offset: 0x154 */
    uint8_t RESERVED_36[7];
    __IO uint8_t CLK_RECOVER_INT_STATUS; /**< Clock Recovery Separated Interrupt Status, offset: 0x15C */
} KINETIS_MCX_TypeDef;

void usb_dc_low_level_init(uint8_t busid);
void usb_dc_low_level_deinit(uint8_t busid);

void usbd_kinetis_delay_ms(uint8_t ms);
#endif