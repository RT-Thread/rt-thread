/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USB_MSC_H
#define USB_MSC_H

/* MSC Subclass Codes */
#define MSC_SUBCLASS_RBC           0x01 /* Reduced block commands (e.g., flash devices) */
#define MSC_SUBCLASS_SFF8020I_MMC2 0x02 /* SFF-8020i/MMC-2 (ATAPI) (e.g., C/DVD) */
#define MSC_SUBCLASS_QIC157        0x03 /* QIC-157 (e.g., tape device) */
#define MSC_SUBCLASS_UFI           0x04 /* e.g. floppy device */
#define MSC_SUBCLASS_SFF8070I      0x05 /* SFF-8070i (e.g. floppy disk) */
#define MSC_SUBCLASS_SCSI          0x06 /* SCSI transparent */

/* MSC Protocol Codes */
#define MSC_PROTOCOL_CBI_INT   0x00 /* CBI transport with command completion interrupt */
#define MSC_PROTOCOL_CBI_NOINT 0x01 /* CBI transport without command completion interrupt */
#define MSC_PROTOCOL_BULK_ONLY 0x50 /* Bulk only transport */

/* MSC Request Codes */
#define MSC_REQUEST_RESET       0xFF
#define MSC_REQUEST_GET_MAX_LUN 0xFE

/** MSC Command Block Wrapper (CBW) Signature */
#define MSC_CBW_Signature 0x43425355
/** Bulk-only Command Status Wrapper (CSW) Signature */
#define MSC_CSW_Signature 0x53425355

/** MSC Command Block Status Values */
#define CSW_STATUS_CMD_PASSED  0x00
#define CSW_STATUS_CMD_FAILED  0x01
#define CSW_STATUS_PHASE_ERROR 0x02

#define MSC_MAX_CDB_LEN (16) /* Max length of SCSI Command Data Block */

/** MSC Bulk-Only Command Block Wrapper (CBW) */
struct CBW {
    uint32_t dSignature;         /* 'USBC' = 0x43425355 */
    uint32_t dTag;               /* Depends on command id */
    uint32_t dDataLength;        /* Number of bytes that host expects to transfer */
    uint8_t bmFlags;             /* Bit 7: Direction=IN (other obsolete or reserved) */
    uint8_t bLUN;                /* LUN (normally 0) */
    uint8_t bCBLength;           /* len of cdb[] */
    uint8_t CB[MSC_MAX_CDB_LEN]; /* Command Data Block */
} __PACKED;

#define USB_SIZEOF_MSC_CBW 31

/** MSC Bulk-Only Command Status Wrapper (CSW) */
struct CSW {
    uint32_t dSignature;   /* 'USBS' = 0x53425355 */
    uint32_t dTag;         /* Same tag as original command */
    uint32_t dDataResidue; /* Amount not transferred */
    uint8_t bStatus;       /* Status of transfer */
} __PACKED;

#define USB_SIZEOF_MSC_CSW 13

/*Length of template descriptor: 23 bytes*/
#define MSC_DESCRIPTOR_LEN (9 + 7 + 7)
// clang-format off
#define MSC_DESCRIPTOR_INIT(bFirstInterface, out_ep, in_ep, wMaxPacketSize, str_idx) \
    /* Interface */                                              \
    0x09,                          /* bLength */                 \
    USB_DESCRIPTOR_TYPE_INTERFACE, /* bDescriptorType */         \
    bFirstInterface,               /* bInterfaceNumber */        \
    0x00,                          /* bAlternateSetting */       \
    0x02,                          /* bNumEndpoints */           \
    USB_DEVICE_CLASS_MASS_STORAGE, /* bInterfaceClass */         \
    MSC_SUBCLASS_SCSI,             /* bInterfaceSubClass */      \
    MSC_PROTOCOL_BULK_ONLY,        /* bInterfaceProtocol */      \
    str_idx,                       /* iInterface */              \
    0x07,                          /* bLength */                 \
    USB_DESCRIPTOR_TYPE_ENDPOINT,  /* bDescriptorType */         \
    out_ep,                        /* bEndpointAddress */        \
    0x02,                          /* bmAttributes */            \
    WBVAL(wMaxPacketSize),         /* wMaxPacketSize */          \
    0x00,                          /* bInterval */               \
    0x07,                          /* bLength */                 \
    USB_DESCRIPTOR_TYPE_ENDPOINT,  /* bDescriptorType */         \
    in_ep,                         /* bEndpointAddress */        \
    0x02,                          /* bmAttributes */            \
    WBVAL(wMaxPacketSize),         /* wMaxPacketSize */          \
    0x00                           /* bInterval */
// clang-format on

#endif /* USB_MSC_H */
