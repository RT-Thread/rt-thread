/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fpcie_common.h
 * Date: 2022-08-10 14:55:11
 * LastEditTime: 2022-08-18 08:57:24
 * Description: This file is for pcie common features definition. 
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe  2022/8/18   init commit
 */

#ifndef FPCIE_ECAM_COMMON_H
#define FPCIE_ECAM_COMMON_H


#include "fkernel.h"
#include "fio.h"
#ifdef __cplusplus
extern "C"
{
#endif

/******************** Macros (Inline Functions) Definitions *******************/

#define FPCIE_ECAM_BUS_SHIFT 20 /**< Bus Number Shift Value */
#define FPCIE_ECAM_DEV_SHIFT 15 /**< Device Number Shift Value */
#define FPCIE_ECAM_FUN_SHIFT 12 /**< Function Number Shift Value */
#define FPCIE_ECAM_REG_SHIFT 2  /**< Register Number Shift Value */
#define FPCIE_ECAM_BYT_SHIFT 0  /**< Byte Offset Shift Value */

/* Pci compatible configuration register space */

#define FPCIE_CCR_ID_REG                    0x0U    /* Vendor ID and Device ID */
#define FPCIE_CCR_CMD_STATUS_REGS           0x1U    /* Command and Status */
#define FPCIE_CCR_REV_CLASSID_REGS          0x2U    /* Revision ID and Class Code */
#define FPCIE_CCR_CLS_LT_HT_REGS            0x3U    /* Cache Line Size, Latency Timer, Header Type */
#define FPCIE_CCR_BAR_ADDR0_REGS            0x4U    /* Base Address Register 0 */
#define FPCIE_CCR_BAR_ADDR1_REGS            0x5U    /* Base Address Register 1 */

/* only for type0 */
#define FPCIE_CCR_BAR_ADDR2_REGS            0x6U    /* Base Address Register 2 (only for Type 0) */
#define FPCIE_CCR_BAR_ADDR3_REGS            0x7U    /* Base Address Register 3 (only for Type 0) */
#define FPCIE_CCR_BAR_ADDR4_REGS            0x8U    /* Base Address Register 4 (only for Type 0) */
#define FPCIE_CCR_BAR_ADDR5_REGS            0x9U    /* Base Address Register 5 (only for Type 0) */
#define FPCIE_CCR_CARDBUS_CIS_REGS          0xaU   /* CardBus CIS Pointer (only for Type 0) */
#define FPCIE_CCR_SUB_ID_REGS               0xbU   /* Subsystem ID (only for Type 0) */
#define FPCIE_CCR_TYPE0_EXPANSION_ROM_REGS  0xcU   /* Expansion ROM Base Address (only for Type 0) */
#define FPCIE_CCR_INTX_LAT_GNT_REGS         0xfU/* INTx Interrupt Line, Latency Timer, and GNT# */

/* only for type1 */
#define FPCIE_CCR_PB_SEC_SUB_SECL_REGS      0x6U    /* Primary/Secondary/Subordinate bus numbers and Secondary Latency Timer */
#define FPCIE_CCR_IOB_IOL_SECS_REGS         0x7U    /* I/O Base and Limit, Secondary Status */
#define FPCIE_CCR_MEMB_MEML_REGS            0x8U    /* Memory Base and Limit */
#define FPCIE_CCR_PMEMB_PMEML_REGS          0x9U    /* Prefetchable Memory Base and Limit */
#define FPCIE_CCR_PREBU32_REGS              0xaU   /* Predefined region 32-bit */
#define FPCIE_CCR_PRELIMITU32_REGS          0xbU   /* Predefined region limit 32-bit */
#define FPCIE_CCR_IOU16_IOL16_REGS          0xcU   /* I/O Base and Limit, Upper 16 bits */
#define FPCIE_CCR_TYPE1_EXPANSION_ROM_REGS  0xeU   /* Expansion ROM Base Address (only for Type 1) */
#define FPCIE_CCR_BRIDGE_CONTROL_REGS       0xfU   /* Bridge Control */

#define FPCIE_CCR_CAPBILITIES_PONINTERS_REGS   0xdU  /* Capabilities Pointers */


#define FPCIE_CCR_INVALID_DATA              0xffffffffU  
#define FPCIE_BAR_ADDR_MASK                 0xffffffffU
#define FPCIE_DEVICE_NOT_PRESENT    0xffff  

/* FPCIE_CCR_ID_REG */
#define FPCIE_CCR_VENDOR_ID_MASK(ccr_id)     (u16)(ccr_id & 0xFFFFU) /* Mask for extracting Vendor ID from CCR ID */
#define FPCIE_CCR_DEVICE_ID_MASK(ccr_id)     (u16)((ccr_id >> 16U) & 0xFFFFU) /* Mask for extracting Device ID from CCR ID */

/* FPCIE_CCR_CLS_LT_HT_REGS */
#define FPCIE_CCR_HEAD_TYPE_MASK(ccr_value)  (u8)((ccr_value >> 16U) & 0x7FU) /* Mask for extracting Header Type from ccr_value */
#define FPCIE_CCR_MULT_FUNTION_MASK(ccr_value)  (u8)((ccr_value >> 16U) & 0x80U) /* Mask for extracting Multi-Function bit from ccr_value */
#define FPCIE_CCR_HEAD_TYPE0                  0 /* Header Type 0 value */
#define FPCIE_CCR_HEAD_TYPE1                  1 /* Header Type 1 value */
#define FPCIE_CCR_HEAD_TYPE2                  2 /* Header Type 2 value */

/* FPCIE_CCR_CMD_STATUS_REGS */
#define FPCIE_CCR_CMD_IO_ACCESS_ENABLED          (1 << 0)      /* Device I/O Access Enable */
#define FPCIE_CCR_CMD_MEMORY_ACCESS_ENABLED      (1 << 1)      /* Device Memory Access Enable */
#define FPCIE_CCR_CMD_BUS_MASTER_ENABLED         (1 << 2)      /* Device Bus Master Enable */
#define FPCIE_CCR_CMD_SPECIAL_CYCLE_ENABLED      (1 << 3)      /* Device Special Cycle Enable */
#define FPCIE_CCR_CMD_WRITE_INVALIDATE_ENABLED   (1 << 4)      /* Device Write and Invalidate Enable */
#define FPCIE_CCR_CMD_VGA_PALETTE_SNOOP_ENABLED  (1 << 5)      /* Device VGA Palette Snoop Enable */
#define FPCIE_CCR_CMD_PARITY_ERROR_RESPONSE_ENABLED  (1 << 6)      /* Device Parity Error Response Enable */
#define FPCIE_CCR_CMD_STEPPING_CONTROL_ENABLED   (1 << 7)      /* Device Stepping Control Enable */
#define FPCIE_CCR_CMD_SERR_ENABLE_ENABLED        (1 << 8)      /* Device SERR Enable */
#define FPCIE_CCR_CMD_FAST_BACK_TO_BACK_ENABLE_ENABLED  (1 << 9)   /* Device Fast Back-to-Back Enable */
#define FPCIE_CCR_CMD_INTX_DISABLED               (1U << 10)
#define FPCIE_CCR_STATUS_INTERRUT                 ((1U << 3) << 16)            


/* FPCIE_CCR_BAR_ADDR0_REGS */
#define FPCIE_CCR_BAR_IO_MEM_TYPE_MASK              (~0x03ULL) /* Mask for extracting IO/Memory Type from BAR data */
#define FPCIE_CCR_BAR_MEM_TYPE_MASK                 (~0x0fULL) /* Mask for extracting Memory Type from BAR data */
#define FPCIE_CCR_BAR_IO_REQ_MASK                   (1 << 0)    /* IO Request bit mask */
#define FPCIE_CCR_BAR_IO_SIZE(bar_data)             (((~(bar_data & FPCIE_CCR_BAR_IO_MEM_TYPE_MASK))& 0xffff) + 1) /* Size of IO space */
#define FPCIE_CCR_BAR_MEM_SIZE(bar_data)            (((~(bar_data & FPCIE_CCR_BAR_MEM_TYPE_MASK))) + 1) /* Size of Memory space */
#define FPCIE_CCR_BAR_MEM_64_MASK                   (1<<2)      /* Memory 64-bit bit mask */
#define FPCIE_CCR_BAR_MEM_PREFETCH_MASK             (1<<3)      /* MemoryPrefetchable bit mask */

/* FPCIE_CCR_CLS_LT_HT_REGS */
#define FPCIE_CCR_CACHELINE_MASK(data)               (data&0xf) /* Mask for extracting Cache Line Size from data */
#define FPCIE_CCR_LATENCY_TIMER_MASK(data)           ((data<<8) &0xF0) /* Mask for extracting Latency Timer from data */

/* FPCIE_CCR_PB_SEC_SUB_SECL_REGS */
#define FPCIE_CCR_PRIMARY_NUM_MASK(data) (u32)(data & 0xff)  /* Mask for extracting Primary Bus Number from data */
#define FPCIE_CCR_SECONDARY_NUM_MASK(data) (u32)(((u32)data<<8) & 0xff00) /* Mask for extracting Secondary Bus Number from data */
#define FPCIE_CCR_SUB_NUM_MASK(data) (u32)(((u32)data<<16) & 0xff0000) /* Mask for extracting Subordinate Bus Number from data */

/* FPCIE_CCR_MEMB_MEML_REGS */
#define FPCIE_CCR_MEM_BASE_MASK(data)   (u32)(data & 0xffff) /* Mask for extracting Memory Base Address from data */
#define FPCIE_CCR_MEM_LIMIT_MASK(data)   (u32)(((u32)data<<16) & 0xffff0000) /* Mask for extracting Memory Limit Address from data */


/* FPCIE_CCR_PMEMB_PMEML_REGS */
#define FPCIE_CCR_PMEMB_64BIT_MASK      (u32)0x1 /* Mask for 64-bit Prefetchable Memory */
#define FPCIE_CCR_PMEM_BASE_MASK(data)   (u32)(data & 0xffff) /* Mask for extracting Prefetchable Memory Base Address from data */
#define FPCIE_CCR_PMEM_LIMIT_MASK(data)   (u32)(((u32)data<<16) & 0xffff0000) /* Mask for extracting Prefetchable Memory Limit Address from data */

/* FPCIE_CCR_IOB_IOL_SECS_REGS */
#define FPCIE_CCR_IO_BASE_MASK(data)      (u32)(data&0xff) /* Mask for extracting I/O Base Address from data */
#define FPCIE_CCR_IO_LIMIT_MASK(data)      (u32)((data<<8)&0xff00) /* Mask for extracting I/O Limit Address from data */

/* FPCIE_CCR_IOU16_IOL16_REGS */
#define FPCIE_CCR_IOB_UP16_MASK(data)      (u32)(data&0xffff) /* Mask for extracting I/O Base Address (Upper 16 bits) from data */
#define FPCIE_CCR_IOB_LIMIT16_MASK(data)   (u32)((data<<16)&0xffff0000) /* Mask for extracting I/O Limit Address (Upper 16 bits) from data */

/* FPCIE_CCR_REV_CLASSID_REGS */
#define FPCIE_CCR_REV_ID_MASK(ccr_value)   (u8)(ccr_value & 0xFF) /* Mask for extracting Revision ID from ccr_value */
#define FPCIE_CCR_CLASS_CODE_MASK(ccr_value) (u8)((ccr_value>>24) & 0xFF)

/* FPCIE_CCR_CAPBILITIES_PONINTERS_REGS */
#define FPCIE_CCR_CAP_PONINTERS_MASK(cap_value) (u8)(cap_value & 0xff) 

/* FPCIE_CCR_INTX_LAT_GNT_REGS */
#define FPCIE_CCR_INTX_PIN_MASK(ccr_value)  (u8)((ccr_value>>8) & 0xff)
#define FPCIE_CCR_INTX_LINE_MASK(ccr_value)  (u8)((ccr_value) & 0xff)

/* capbility */
#define FPCIE_CAP_ADDRESS_GET(cap_value) (u16)((cap_value >> 2U) & 0xFFFFU)
#define FPCIE_CAP_ID_GET(cap_value)     (u8)(cap_value&0xff)
#define FPCIE_CAP_NEXT_POINTER_GET(cap_value) (u32)((cap_value >> 8U) & 0xFFU)

/* Capability lists */

#define FPCI_CAP_LIST_ID        0   /* Capability ID */
#define  FPCI_CAP_ID_PM     0x01    /* Power Management */
#define  FPCI_CAP_ID_AGP        0x02    /* Accelerated Graphics Port */
#define  FPCI_CAP_ID_VPD        0x03    /* Vital Product Data */
#define  FPCI_CAP_ID_SLOTID 0x04    /* Slot Identification */
#define  FPCI_CAP_ID_MSI        0x05    /* Message Signalled Interrupts */
#define  FPCI_CAP_ID_CHSWP  0x06    /* CompactPCI HotSwap */
#define  FPCI_CAP_ID_PCIX   0x07    /* PCI-X */
#define  FPCI_CAP_ID_HT     0x08    /* HyperTransport */
#define  FPCI_CAP_ID_VNDR   0x09    /* Vendor-Specific */
#define  FPCI_CAP_ID_DBG        0x0A    /* Debug port */
#define  FPCI_CAP_ID_CCRC   0x0B    /* CompactPCI Central Resource Control */
#define  FPCI_CAP_ID_SHPC   0x0C    /* PCI Standard Hot-Plug Controller */
#define  FPCI_CAP_ID_SSVID  0x0D    /* Bridge subsystem vendor/device ID */
#define  FPCI_CAP_ID_AGP3   0x0E    /* AGP Target PCI-PCI bridge */
#define  FPCI_CAP_ID_SECDEV 0x0F    /* Secure Device */
#define  FPCI_CAP_ID_EXP        0x10    /* PCI Express */
#define  FPCI_CAP_ID_MSIX   0x11    /* MSI-X */
#define  FPCI_CAP_ID_SATA   0x12    /* SATA Data/Index Conf. */
#define  FPCI_CAP_ID_AF     0x13    /* PCI Advanced Features */
#define  FPCI_CAP_ID_EA     0x14    /* PCI Enhanced Allocation */
#define  FPCI_CAP_ID_MAX        PCI_CAP_ID_EA

/* Extended Configuration Space */
#define FPCI_EXT_REGS   0x40
#define FPCI_EXT_CAP_PONINTERS_MASK(cap_value) (u32)(((cap_value >>20)& 0xfff)  >> 2)
#define FPCIE_EXT_CAP_ID_GET(cap_value)     (u16)(cap_value&0xffff)
#define FPCIE_EXT_CAP_VER_MASK(cap_value)   (u32)(((cap_value >> 16)&0xf)

#define FPCI_EXT_CAP_ID_ERR 0x01    /* Advanced Error Reporting */
#define FPCI_EXT_CAP_ID_VC  0x02    /* Virtual Channel Capability */
#define FPCI_EXT_CAP_ID_DSN 0x03    /* Device Serial Number */
#define FPCI_EXT_CAP_ID_PWR 0x04    /* Power Budgeting */
#define FPCI_EXT_CAP_ID_RCLD    0x05    /* Root Complex Link Declaration */
#define FPCI_EXT_CAP_ID_RCILC   0x06    /* Root Complex Internal Link Control */
#define FPCI_EXT_CAP_ID_RCEC    0x07    /* Root Complex Event Collector */
#define FPCI_EXT_CAP_ID_MFVC    0x08    /* Multi-Function VC Capability */
#define FPCI_EXT_CAP_ID_VC9 0x09    /* same as _VC */
#define FPCI_EXT_CAP_ID_RCRB    0x0A    /* Root Complex RB? */
#define FPCI_EXT_CAP_ID_VNDR    0x0B    /* Vendor-Specific */
#define FPCI_EXT_CAP_ID_CAC 0x0C    /* Config Access - obsolete */
#define FPCI_EXT_CAP_ID_ACS 0x0D    /* Access Control Services */
#define FPCI_EXT_CAP_ID_ARI 0x0E    /* Alternate Routing ID */
#define FPCI_EXT_CAP_ID_ATS 0x0F    /* Address Translation Services */
#define FPCI_EXT_CAP_ID_SRIOV   0x10    /* Single Root I/O Virtualization */
#define FPCI_EXT_CAP_ID_MRIOV   0x11    /* Multi Root I/O Virtualization */
#define FPCI_EXT_CAP_ID_MCAST   0x12    /* Multicast */
#define FPCI_EXT_CAP_ID_PRI 0x13    /* Page Request Interface */
#define FPCI_EXT_CAP_ID_AMD_XXX 0x14    /* Reserved for AMD */
#define FPCI_EXT_CAP_ID_REBAR   0x15    /* Resizable BAR */
#define FPCI_EXT_CAP_ID_DPA 0x16    /* Dynamic Power Allocation */
#define FPCI_EXT_CAP_ID_TPH 0x17    /* TPH Requester */
#define FPCI_EXT_CAP_ID_LTR 0x18    /* Latency Tolerance Reporting */
#define FPCI_EXT_CAP_ID_SECPCI  0x19    /* Secondary PCIe Capability */
#define FPCI_EXT_CAP_ID_PMUX    0x1A    /* Protocol Multiplexing */
#define FPCI_EXT_CAP_ID_PASID   0x1B    /* Process Address Space ID */
#define FPCI_EXT_CAP_ID_DPC 0x1D    /* Downstream Port Containment */
#define FPCI_EXT_CAP_ID_L1SS    0x1E    /* L1 PM Substates */
#define FPCI_EXT_CAP_ID_PTM 0x1F    /* Precision Time Measurement */
#define FPCI_EXT_CAP_ID_MAX PCI_EXT_CAP_ID_PTM

/* ARI capability */
#define FPCIE_CAPABILITY_BASE_OFFSET                                0x100
#define FPCIE_CAPABILITY_ID_SRIOV_CONTROL_ARI_HIERARCHY         0x10
#define FPCIE_CAPABILITY_DEVICE_CAPABILITIES_2_OFFSET           0x24
#define FPCIE_CAPABILITY_DEVICE_CAPABILITIES_2_ARI_FORWARDING   0x20
#define FPCIE_CAPABILITY_DEVICE_CONTROL_2_OFFSET                    0x28
#define FPCIE_CAPABILITY_DEVICE_CONTROL_2_ARI_FORWARDING            0x20


/* Device classes and subclasses */

#define FPCI_CLASS_NOT_DEFINED      0x0000
#define FPCI_CLASS_NOT_DEFINED_VGA  0x0001

#define FPCI_BASE_CLASS_STORAGE     0x01
#define FPCI_CLASS_STORAGE_SCSI     0x0100
#define FPCI_CLASS_STORAGE_IDE      0x0101
#define FPCI_CLASS_STORAGE_FLOPPY   0x0102
#define FPCI_CLASS_STORAGE_IPI      0x0103
#define FPCI_CLASS_STORAGE_RAID     0x0104
#define FPCI_CLASS_STORAGE_SATA     0x0106
#define FPCI_CLASS_STORAGE_SATA_AHCI    0x010601
#define FPCI_CLASS_STORAGE_SAS      0x0107
#define FPCI_CLASS_STORAGE_EXPRESS  0x010802
#define FPCI_CLASS_STORAGE_OTHER        0x0180

#define FPCI_BASE_CLASS_NETWORK     0x02
#define FPCI_CLASS_NETWORK_ETHERNET 0x0200
#define FPCI_CLASS_NETWORK_TOKEN_RING   0x0201
#define FPCI_CLASS_NETWORK_FDDI     0x0202
#define FPCI_CLASS_NETWORK_ATM      0x0203
#define FPCI_CLASS_NETWORK_OTHER        0x0280

#define FPCI_BASE_CLASS_DISPLAY     0x03
#define FPCI_CLASS_DISPLAY_VGA      0x0300
#define FPCI_CLASS_DISPLAY_XGA      0x0301
#define FPCI_CLASS_DISPLAY_3D       0x0302
#define FPCI_CLASS_DISPLAY_OTHER        0x0380

#define FPCI_BASE_CLASS_MULTIMEDIA  0x04
#define FPCI_CLASS_MULTIMEDIA_VIDEO 0x0400
#define FPCI_CLASS_MULTIMEDIA_AUDIO 0x0401
#define FPCI_CLASS_MULTIMEDIA_PHONE 0x0402
#define FPCI_CLASS_MULTIMEDIA_HD_AUDIO  0x0403
#define FPCI_CLASS_MULTIMEDIA_OTHER 0x0480

#define FPCI_BASE_CLASS_MEMORY      0x05
#define FPCI_CLASS_MEMORY_RAM       0x0500
#define FPCI_CLASS_MEMORY_FLASH     0x0501
#define FPCI_CLASS_MEMORY_OTHER     0x0580

#define FPCI_BASE_CLASS_BRIDGE      0x06
#define FPCI_CLASS_BRIDGE_HOST      0x0600
#define FPCI_CLASS_BRIDGE_ISA       0x0601
#define FPCI_CLASS_BRIDGE_EISA      0x0602
#define FPCI_CLASS_BRIDGE_MC        0x0603
#define FPCI_CLASS_BRIDGE_PCI       0x0604
#define FPCI_CLASS_BRIDGE_PCMCIA        0x0605
#define FPCI_CLASS_BRIDGE_NUBUS     0x0606
#define FPCI_CLASS_BRIDGE_CARDBUS   0x0607
#define FPCI_CLASS_BRIDGE_RACEWAY   0x0608
#define FPCI_CLASS_BRIDGE_OTHER     0x0680

#define FPCI_BASE_CLASS_COMMUNICATION   0x07
#define FPCI_CLASS_COMMUNICATION_SERIAL 0x0700
#define FPCI_CLASS_COMMUNICATION_PARALLEL 0x0701
#define FPCI_CLASS_COMMUNICATION_MULTISERIAL 0x0702
#define FPCI_CLASS_COMMUNICATION_MODEM  0x0703
#define FPCI_CLASS_COMMUNICATION_OTHER  0x0780

#define FPCI_BASE_CLASS_SYSTEM      0x08
#define FPCI_CLASS_SYSTEM_PIC       0x0800
#define FPCI_CLASS_SYSTEM_PIC_IOAPIC    0x080010
#define FPCI_CLASS_SYSTEM_PIC_IOXAPIC   0x080020
#define FPCI_CLASS_SYSTEM_DMA       0x0801
#define FPCI_CLASS_SYSTEM_TIMER     0x0802
#define FPCI_CLASS_SYSTEM_RTC       0x0803
#define FPCI_CLASS_SYSTEM_PCI_HOTPLUG   0x0804
#define FPCI_CLASS_SYSTEM_SDHCI     0x0805
#define FPCI_CLASS_SYSTEM_OTHER     0x0880

#define FPCI_BASE_CLASS_INPUT       0x09
#define FPCI_CLASS_INPUT_KEYBOARD   0x0900
#define FPCI_CLASS_INPUT_PEN        0x0901
#define FPCI_CLASS_INPUT_MOUSE      0x0902
#define FPCI_CLASS_INPUT_SCANNER        0x0903
#define FPCI_CLASS_INPUT_GAMEPORT   0x0904
#define FPCI_CLASS_INPUT_OTHER      0x0980

#define FPCI_BASE_CLASS_DOCKING     0x0a
#define FPCI_CLASS_DOCKING_GENERIC  0x0a00
#define FPCI_CLASS_DOCKING_OTHER        0x0a80

#define FPCI_BASE_CLASS_PROCESSOR   0x0b
#define FPCI_CLASS_PROCESSOR_386        0x0b00
#define FPCI_CLASS_PROCESSOR_486        0x0b01
#define FPCI_CLASS_PROCESSOR_PENTIUM    0x0b02
#define FPCI_CLASS_PROCESSOR_ALPHA  0x0b10
#define FPCI_CLASS_PROCESSOR_POWERPC    0x0b20
#define FPCI_CLASS_PROCESSOR_MIPS   0x0b30
#define FPCI_CLASS_PROCESSOR_CO     0x0b40

#define FPCI_BASE_CLASS_SERIAL      0x0c
#define FPCI_CLASS_SERIAL_FIREWIRE  0x0c00
#define FPCI_CLASS_SERIAL_FIREWIRE_OHCI 0x0c0010
#define FPCI_CLASS_SERIAL_ACCESS        0x0c01
#define FPCI_CLASS_SERIAL_SSA       0x0c02
#define FPCI_CLASS_SERIAL_USB       0x0c03
#define FPCI_CLASS_SERIAL_USB_UHCI  0x0c0300
#define FPCI_CLASS_SERIAL_USB_OHCI  0x0c0310
#define FPCI_CLASS_SERIAL_USB_EHCI  0x0c0320
#define FPCI_CLASS_SERIAL_USB_XHCI  0x0c0330
#define FPCI_CLASS_SERIAL_FIBER     0x0c04
#define FPCI_CLASS_SERIAL_SMBUS     0x0c05

#define FPCI_BASE_CLASS_WIRELESS            0x0d
#define FPCI_CLASS_WIRELESS_RF_CONTROLLER   0x0d10
#define FPCI_CLASS_WIRELESS_WHCI            0x0d1010

#define FPCI_BASE_CLASS_INTELLIGENT 0x0e
#define FPCI_CLASS_INTELLIGENT_I2O  0x0e00

#define FPCI_BASE_CLASS_SATELLITE   0x0f
#define FPCI_CLASS_SATELLITE_TV     0x0f00
#define FPCI_CLASS_SATELLITE_AUDIO  0x0f01
#define FPCI_CLASS_SATELLITE_VOICE  0x0f03
#define FPCI_CLASS_SATELLITE_DATA   0x0f04

#define FPCI_BASE_CLASS_CRYPT       0x10
#define FPCI_CLASS_CRYPT_NETWORK        0x1000
#define FPCI_CLASS_CRYPT_ENTERTAINMENT  0x1001
#define FPCI_CLASS_CRYPT_OTHER      0x1080

#define FPCI_BASE_CLASS_SIGNAL_PROCESSING 0x11
#define FPCI_CLASS_SP_DPIO      0x1100
#define FPCI_CLASS_SP_OTHER     0x1180

#define FPCI_CLASS_OTHERS       0xff


#define FPCIE_READECAM_REG(base_addr, reg_offset)\
    FtIn32((base_addr) + (u32)(reg_offset))

#define FPCIE_WRITEECAM_REG(base_addr, reg_offset,data)\
    FtOut32((base_addr) + (u32)(reg_offset),(u32)data)

#define FPCIE_READECAM_BYTE(base_addr, reg_offset)\
    FtIn8((base_addr) + (u32)(reg_offset))

#ifdef __cplusplus
}
#endif

#endif // !
