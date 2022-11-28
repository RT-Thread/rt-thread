/* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.

 * Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
 * the the People's Republic of China and other countries.
 * All Allwinner Technology Co.,Ltd. trademarks are used with permission.

 * DISCLAIMER
 * THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
 * IF YOU NEED TO INTEGRATE THIRD PART'S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
 * IN ALLWINNER'SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
 * ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
 * ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
 * COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
 * YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PART'S TECHNOLOGY.


 * THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
 * PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
 * THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
 * OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __USB_STORAGE_H__
#define __USB_STORAGE_H__

/*
 * linux/usb/storage.h
 *
 * Copyright Matthew Wilcox for Intel Corp, 2010
 *
 * This file contains definitions taken from the
 * USB Mass Storage Class Specification Overview
 *
 * Distributed under the terms of the GNU GPL, version two.
 */

/* Storage subclass codes */

#define USB_SC_RBC  0x01        /* Typically, flash devices */
#define USB_SC_8020 0x02        /* CD-ROM */
#define USB_SC_QIC  0x03        /* QIC-157 Tapes */
#define USB_SC_UFI  0x04        /* Floppy */
#define USB_SC_8070 0x05        /* Removable media */
#define USB_SC_SCSI 0x06        /* Transparent */
#define USB_SC_LOCKABLE 0x07        /* Password-protected */

#define USB_SC_ISD200   0xf0        /* ISD200 ATA */
#define USB_SC_CYP_ATACB    0xf1    /* Cypress ATACB */
#define USB_SC_DEVICE   0xff        /* Use device's value */

/* Storage protocol codes */

#define USB_PR_CBI  0x00        /* Control/Bulk/Interrupt */
#define USB_PR_CB   0x01        /* Control/Bulk w/o interrupt */
#define USB_PR_BULK 0x50        /* bulk only */
#define USB_PR_UAS  0x62        /* USB Attached SCSI */

#define USB_PR_USBAT    0x80        /* SCM-ATAPI bridge */
#define USB_PR_EUSB_SDDR09  0x81    /* SCM-SCSI bridge for SDDR-09 */
#define USB_PR_SDDR55   0x82        /* SDDR-55 (made up) */
#define USB_PR_DPCM_USB 0xf0        /* Combination CB/SDDR09 */
#define USB_PR_FREECOM  0xf1        /* Freecom */
#define USB_PR_DATAFAB  0xf2        /* Datafab chipsets */
#define USB_PR_JUMPSHOT 0xf3        /* Lexar Jumpshot */
#define USB_PR_ALAUDA   0xf4        /* Alauda chipsets */
#define USB_PR_KARMA    0xf5        /* Rio Karma */

#define USB_PR_DEVICE   0xff        /* Use device's value */

/*
 * Bulk only data structures
 */

/* command block wrapper */
struct bulk_cb_wrap {
    uint32_t    Signature;      /* contains 'USBC' */
    uint32_t    Tag;            /* unique per command id */
    uint32_t    DataTransferLength; /* size of data */
    uint8_t     Flags;          /* direction in bit 0 */
    uint8_t     Lun;            /* LUN normally 0 */
    uint8_t     Length;         /* length of the CDB */
    uint8_t     CDB[16];        /* max command */
};

#define US_BULK_CB_WRAP_LEN 31
#define US_BULK_CB_SIGN     0x43425355  /* spells out 'USBC' */
#define US_BULK_FLAG_IN     (1 << 7)
#define US_BULK_FLAG_OUT    0

/* command status wrapper */
struct bulk_cs_wrap {
    uint32_t    Signature;  /* contains 'USBS' */
    uint32_t    Tag;        /* same as original command */
    uint32_t    Residue;    /* amount not transferred */
    uint8_t     Status;     /* see below */
};

#define US_BULK_CS_WRAP_LEN 13
#define US_BULK_CS_SIGN     0x53425355      /* spells out 'USBS' */
#define US_BULK_STAT_OK     0
#define US_BULK_STAT_FAIL   1
#define US_BULK_STAT_PHASE  2

/* bulk-only class specific requests */
#define US_BULK_RESET_REQUEST   0xff
#define US_BULK_GET_MAX_LUN     0xfe

#endif /* __USB_STORAGE_H__ */
