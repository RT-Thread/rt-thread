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

#ifndef FPCIE_COMMON_H
#define FPCIE_COMMON_H

#include "fpcie_hw.h"
#include "fkernel.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************** Macros (Inline Functions) Definitions *******************/

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


/* Command register offsets */

/* PCIe Configuration registers offsets */

/* Vendor ID/Device ID offset */
#define FPCIE_CFG_ID_REG 0x0000

/*  Independent element register */

#define FPCIE_VENDOR_REG            0x0
#define FPCIE_DEVICE_ID_REG         0x02
#define FPCIE_STATUS_REG            0x06
#define FPCI_CLASS_DEVICE_REG       0x0a    /* Device class */
#define FPCIE_CACHE_LINE_SIZE_REG   0x0c    /* 8 bits */
#define FPCIE_LATENCY_TIMER_REG     0x0d    /* 8 bits */
#define FPCIE_HEADER_TYPE_REG       0x0e    /* Header Type */
#define FPCIE_BIST_REG      0x0f    /* 8 bits */

#define  FPCIE_HEADER_TYPE_NORMAL   0
#define  FPCIE_HEADER_TYPE_BRIDGE   1
#define  FPCIE_HEADER_TYPE_CARDBUS  2
#define FPCIE_SECONDARY_BUS_REG     0x19    /* Secondary bus number */
#define FPCIE_SUBORDINATE_BUS_REG   0x1a    /* Highest bus number behind the bridge */
#define FPCIE_SEC_LATENCY_TIMER_REG     0x1b    /* Latency timer for secondary interface */
#define FPCIE_IO_BASE_REG       0x1c    /* I/O range behind the bridge */
#define FPCIE_IO_LIMIT_REG      0x1d
#define FPCIE_SEC_STATUS_REG        0x1e    /* Secondary status register, only bit 14 used */

#define FPCIE_IO_LIMIT_UPPER16_REG  0x32

#define FPCIE_MEMORY_BASE_REG       0x20    /* Memory range behind */
#define FPCIE_MEMORY_LIMIT_REG  0x22
#define FPCIE_PREF_BASE_UPPER32_REG 0x28    /* Upper half of prefetchable memory range */
#define FPCIE_PREF_LIMIT_UPPER32_REG    0x2c

#define FPCIE_IO_BASE_UPPER16_REG   0x30    /* Upper half of I/O addresses */
#define FPCI_CLASS_REVISION 0x08    /* High 24 bits are class, low 8 */

#define FPCIE_CLASS_REVISION    0x0a    /* High 24 bits are class, low 8 revision */

#define FPCIE_INTERRUPT_PIN_REG         0x3d
#define FPCIE_INTERRUPT_LINE_REG        0x3c
#define FPCIE_MIN_GNT_REG       0x3e    /* 8 bits */
#define FPCIE_MAX_LAT_REG       0x3f    /* 8 bits */


#define  FPCIE_COMMAND_REG          0x04    /* 16 bits */
#define  FPCIE_COMMAND_IO           0x1 /* Enable response in I/O space */
#define  FPCIE_COMMAND_MEMORY       0x2 /* Enable response in Memory space */
#define  FPCIE_COMMAND_MASTER       0x4 /* Enable bus mastering */
#define  FPCIE_COMMAND_SPECIAL      0x8 /* Enable response to special cycles */
#define  FPCIE_COMMAND_INVALIDATE   0x10    /* Use memory write and invalidate */
#define  FPCIE_COMMAND_VGA_PALETTE  0x20    /* Enable palette snooping */
#define  FPCIE_COMMAND_PARITY       0x40    /* Enable parity checking */
#define  FPCIE_COMMAND_WAIT         0x80    /* Enable address/data stepping */
#define  FPCIE_COMMAND_SERR         0x100   /* Enable SERR */
#define  FPCIE_COMMAND_FAST_BACK    0x200   /* Enable back-to-back writes */

#define FPCIE_HEADER_TYPE_REG       0x0e    /* 8 bits */

#define FPCIE_REVISION_ID_REG       0x08    /* Revision ID */
#define FPCIE_CLASS_PROG_REG        0x09    /* Reg. Level Programming Interface */
#define FPCIE_CLASS_DEVICE_REG      0x0a    /* Device class */
#define FPCIE_CLASS_CODE_REG        0x0b    /* Device class code */

#define FPCIE_PREF_MEMORY_BASE_REG  0x24    /* Prefetchable memory range behind */
#define FPCIE_PREF_MEMORY_LIMIT_REG     0x26
#define FPCIE_PREF_LIMIT_UPPER32_REG        0x2c
#define FPCIE_PREF_RANGE_TYPE_MASK  0x0f
#define FPCIE_PREF_RANGE_TYPE_32    0x00
#define FPCIE_PREF_RANGE_TYPE_64    0x01
#define FPCIE_PREF_RANGE_MASK       ~0x0f

#define FPCI_CLASS_BRIDGE_PCI       0x0604
#define FPCI_CLASS_BRIDGE_CARDBUS   0x0607
#define FPCI_CLASS_PROCESSOR_POWERPC    0x0b20
#define FPCI_CLASS_DISPLAY_VGA      0x0300

#define FPCIE_CFG_FUN_NOT_IMP_MASK 0xFFFF
#define FPCIE_CFG_HEADER_TYPE_MASK 0x007F0000

/*
 * Base addresses specify locations in memory or I/O space.
 * Decoded size can be determined by writing a value of
 * 0xffffffff to the register, and reading it back.  Only
 * 1 bits are decoded.
 */
#define FPCIE_BASE_ADDRESS_0    0x10    /* 32 bits */
#define FPCIE_BASE_ADDRESS_1    0x14    /* 32 bits [htype 0,1 only] */
#define FPCIE_BASE_ADDRESS_2    0x18    /* 32 bits [htype 0 only] */
#define FPCIE_BASE_ADDRESS_3    0x1c    /* 32 bits */
#define FPCIE_BASE_ADDRESS_4    0x20    /* 32 bits */
#define FPCIE_BASE_ADDRESS_5    0x24    /* 32 bits */
#define  FPCIE_BASE_ADDRESS_SPACE 0x01  /* 0 = memory, 1 = I/O */
#define  FPCIE_BASE_ADDRESS_SPACE_IO 0x01
#define  FPCIE_BASE_ADDRESS_SPACE_MEMORY 0x00
#define  FPCIE_BASE_ADDRESS_MEM_TYPE_MASK 0x06
#define  FPCIE_BASE_ADDRESS_MEM_TYPE_32 0x00    /* 32 bit address */
#define  FPCIE_BASE_ADDRESS_MEM_TYPE_1M 0x02    /* Below 1M [obsolete] */
#define  FPCIE_BASE_ADDRESS_MEM_TYPE_64 0x04    /* 64 bit address */
#define  FPCIE_BASE_ADDRESS_MEM_PREFETCH    0x08    /* prefetchable? */
#define  FPCIE_BASE_ADDRESS_MEM_MASK    (~0x0fULL)
#define  FPCIE_BASE_ADDRESS_IO_MASK (~0x03ULL)
#define FPCIE_EP_MIN_APERTURE 128

/* BAR control values applicable to both Endpoint Function and Root Complex */
#define FPCIE_LM_BAR_CFG_CTRL_DISABLED 0x0
#define FPCIE_LM_BAR_CFG_CTRL_IO_32BITS 0x1
#define FPCIE_LM_BAR_CFG_CTRL_MEM_32BITS 0x4
#define FPCIE_LM_BAR_CFG_CTRL_PREFETCH_MEM_32BITS 0x5
#define FPCIE_LM_BAR_CFG_CTRL_MEM_64BITS 0x6
#define FPCIE_LM_BAR_CFG_CTRL_PREFETCH_MEM_64BITS 0x7


/* Header type 0 (normal devices) */
#define FPCIE_CARDBUS_CIS       0x28
#define FPCIE_SUBSYSTEM_VENDOR_ID 0x2c
#define FPCIE_SUBSYSTEM_ID  0x2e
#define FPCIE_ROM_ADDRESS       0x30    /* Bits 31..11 are address, 10..1 reserved */
#define FPCIE_ROM_ADDRESS_ENABLE 0x01
#define FPCIE_ROM_ADDRESS_MASK  (~0x7ffULL)


#define FPCIE_BASE_CLASS_DISPLAY        0x03
#define FPCIE_CLASS_DISPLAY_VGA     0x0300
#define FPCIE_CLASS_DISPLAY_XGA     0x0301
#define FPCIE_CLASS_DISPLAY_3D      0x0302
#define FPCIE_CLASS_DISPLAY_OTHER       0x0380

/* 0x34 same as for htype 0 */
#define FPCIE_CAPABILITY_LIST   0x34    /* Offset of first capability list entry */
#define FPCIE_ECAP_START  0x100         /* offset of first extend capability list entry */

/* 0x35-0x3b is reserved */
#define FPCIE_ROM_ADDRESS1  0x38    /* Same as PCI_ROM_ADDRESS, but for htype 1 */
#define FPCIE_BRIDGE_CONTROL_REG    0x3e


#define FPCI_CLASS_SUB_CODE 0x0a    /* Device sub-class code */
#define  FPCI_CLASS_SUB_CODE_TOO_OLD_NOTVGA 0x00
#define  FPCI_CLASS_SUB_CODE_TOO_OLD_VGA        0x01
#define  FPCI_CLASS_SUB_CODE_STORAGE_SCSI   0x00
#define  FPCI_CLASS_SUB_CODE_STORAGE_IDE        0x01
#define  FPCI_CLASS_SUB_CODE_STORAGE_FLOPPY 0x02
#define  FPCI_CLASS_SUB_CODE_STORAGE_IPIBUS 0x03
#define  FPCI_CLASS_SUB_CODE_STORAGE_RAID   0x04
#define  FPCI_CLASS_SUB_CODE_STORAGE_ATA        0x05
#define  FPCI_CLASS_SUB_CODE_STORAGE_SATA   0x06
#define  FPCI_CLASS_SUB_CODE_STORAGE_SAS        0x07
#define  FPCI_CLASS_SUB_CODE_STORAGE_OTHER  0x80
#define  FPCI_CLASS_SUB_CODE_NETWORK_ETHERNET   0x00
#define  FPCI_CLASS_SUB_CODE_NETWORK_TOKENRING  0x01
#define  FPCI_CLASS_SUB_CODE_NETWORK_FDDI   0x02
#define  FPCI_CLASS_SUB_CODE_NETWORK_ATM        0x03
#define  FPCI_CLASS_SUB_CODE_NETWORK_ISDN   0x04
#define  FPCI_CLASS_SUB_CODE_NETWORK_WORLDFIP   0x05
#define  FPCI_CLASS_SUB_CODE_NETWORK_PICMG  0x06
#define  FPCI_CLASS_SUB_CODE_NETWORK_OTHER  0x80
#define  FPCI_CLASS_SUB_CODE_DISPLAY_VGA        0x00
#define  FPCI_CLASS_SUB_CODE_DISPLAY_XGA        0x01
#define  FPCI_CLASS_SUB_CODE_DISPLAY_3D     0x02
#define  FPCI_CLASS_SUB_CODE_DISPLAY_OTHER  0x80
#define  FPCI_CLASS_SUB_CODE_MULTIMEDIA_VIDEO   0x00
#define  FPCI_CLASS_SUB_CODE_MULTIMEDIA_AUDIO   0x01
#define  FPCI_CLASS_SUB_CODE_MULTIMEDIA_PHONE   0x02
#define  FPCI_CLASS_SUB_CODE_MULTIMEDIA_OTHER   0x80
#define  FPCI_CLASS_SUB_CODE_MEMORY_RAM     0x00
#define  FPCI_CLASS_SUB_CODE_MEMORY_FLASH   0x01
#define  FPCI_CLASS_SUB_CODE_MEMORY_OTHER   0x80
#define  FPCI_CLASS_SUB_CODE_BRIDGE_HOST        0x00
#define  FPCI_CLASS_SUB_CODE_BRIDGE_ISA     0x01
#define  FPCI_CLASS_SUB_CODE_BRIDGE_EISA        0x02
#define  FPCI_CLASS_SUB_CODE_BRIDGE_MCA     0x03
#define  FPCI_CLASS_SUB_CODE_BRIDGE_PCI     0x04
#define  FPCI_CLASS_SUB_CODE_BRIDGE_PCMCIA  0x05
#define  FPCI_CLASS_SUB_CODE_BRIDGE_NUBUS   0x06
#define  FPCI_CLASS_SUB_CODE_BRIDGE_CARDBUS 0x07
#define  FPCI_CLASS_SUB_CODE_BRIDGE_RACEWAY 0x08
#define  FPCI_CLASS_SUB_CODE_BRIDGE_SEMI_PCI    0x09
#define  FPCI_CLASS_SUB_CODE_BRIDGE_INFINIBAND  0x0A
#define  FPCI_CLASS_SUB_CODE_BRIDGE_OTHER   0x80
#define  FPCI_CLASS_SUB_CODE_COMM_SERIAL        0x00
#define  FPCI_CLASS_SUB_CODE_COMM_PARALLEL  0x01
#define  FPCI_CLASS_SUB_CODE_COMM_MULTIPORT 0x02
#define  FPCI_CLASS_SUB_CODE_COMM_MODEM     0x03
#define  FPCI_CLASS_SUB_CODE_COMM_GPIB      0x04
#define  FPCI_CLASS_SUB_CODE_COMM_SMARTCARD 0x05
#define  FPCI_CLASS_SUB_CODE_COMM_OTHER     0x80
#define  FPCI_CLASS_SUB_CODE_PERIPHERAL_PIC 0x00
#define  FPCI_CLASS_SUB_CODE_PERIPHERAL_DMA 0x01
#define  FPCI_CLASS_SUB_CODE_PERIPHERAL_TIMER   0x02
#define  FPCI_CLASS_SUB_CODE_PERIPHERAL_RTC 0x03
#define  FPCI_CLASS_SUB_CODE_PERIPHERAL_HOTPLUG 0x04
#define  FPCI_CLASS_SUB_CODE_PERIPHERAL_SD  0x05
#define  FPCI_CLASS_SUB_CODE_PERIPHERAL_OTHER   0x80
#define  FPCI_CLASS_SUB_CODE_INPUT_KEYBOARD 0x00
#define  FPCI_CLASS_SUB_CODE_INPUT_DIGITIZER    0x01
#define  FPCI_CLASS_SUB_CODE_INPUT_MOUSE        0x02
#define  FPCI_CLASS_SUB_CODE_INPUT_SCANNER  0x03
#define  FPCI_CLASS_SUB_CODE_INPUT_GAMEPORT 0x04
#define  FPCI_CLASS_SUB_CODE_INPUT_OTHER        0x80
#define  FPCI_CLASS_SUB_CODE_DOCKING_GENERIC    0x00
#define  FPCI_CLASS_SUB_CODE_DOCKING_OTHER  0x80
#define  FPCI_CLASS_SUB_CODE_PROCESSOR_386  0x00
#define  FPCI_CLASS_SUB_CODE_PROCESSOR_486  0x01
#define  FPCI_CLASS_SUB_CODE_PROCESSOR_PENTIUM  0x02
#define  FPCI_CLASS_SUB_CODE_PROCESSOR_ALPHA    0x10
#define  FPCI_CLASS_SUB_CODE_PROCESSOR_POWERPC  0x20
#define  FPCI_CLASS_SUB_CODE_PROCESSOR_MIPS 0x30
#define  FPCI_CLASS_SUB_CODE_PROCESSOR_COPROC   0x40
#define  FPCI_CLASS_SUB_CODE_SERIAL_1394        0x00
#define  FPCI_CLASS_SUB_CODE_SERIAL_ACCESSBUS   0x01
#define  FPCI_CLASS_SUB_CODE_SERIAL_SSA     0x02
#define  FPCI_CLASS_SUB_CODE_SERIAL_USB     0x03
#define  FPCI_CLASS_SUB_CODE_SERIAL_FIBRECHAN   0x04
#define  FPCI_CLASS_SUB_CODE_SERIAL_SMBUS   0x05
#define  FPCI_CLASS_SUB_CODE_SERIAL_INFINIBAND  0x06
#define  FPCI_CLASS_SUB_CODE_SERIAL_IPMI        0x07
#define  FPCI_CLASS_SUB_CODE_SERIAL_SERCOS  0x08
#define  FPCI_CLASS_SUB_CODE_SERIAL_CANBUS  0x09
#define  FPCI_CLASS_SUB_CODE_WIRELESS_IRDA  0x00
#define  FPCI_CLASS_SUB_CODE_WIRELESS_IR        0x01
#define  FPCI_CLASS_SUB_CODE_WIRELESS_RF        0x10
#define  FPCI_CLASS_SUB_CODE_WIRELESS_BLUETOOTH 0x11
#define  FPCI_CLASS_SUB_CODE_WIRELESS_BROADBAND 0x12
#define  FPCI_CLASS_SUB_CODE_WIRELESS_80211A    0x20
#define  FPCI_CLASS_SUB_CODE_WIRELESS_80211B    0x21
#define  FPCI_CLASS_SUB_CODE_WIRELESS_OTHER 0x80
#define  FPCI_CLASS_SUB_CODE_I2O_V1_0       0x00
#define  FPCI_CLASS_SUB_CODE_SATELLITE_TV   0x01
#define  FPCI_CLASS_SUB_CODE_SATELLITE_AUDIO    0x02
#define  FPCI_CLASS_SUB_CODE_SATELLITE_VOICE    0x03
#define  FPCI_CLASS_SUB_CODE_SATELLITE_DATA 0x04
#define  FPCI_CLASS_SUB_CODE_CRYPTO_NETWORK 0x00
#define  FPCI_CLASS_SUB_CODE_CRYPTO_ENTERTAINMENT 0x10
#define  FPCI_CLASS_SUB_CODE_CRYPTO_OTHER   0x80
#define  FPCI_CLASS_SUB_CODE_DATA_DPIO      0x00
#define  FPCI_CLASS_SUB_CODE_DATA_PERFCNTR  0x01
#define  FPCI_CLASS_SUB_CODE_DATA_COMMSYNC  0x10
#define  FPCI_CLASS_SUB_CODE_DATA_MGMT      0x20
#define  FPCI_CLASS_SUB_CODE_DATA_OTHER     0x80


/* Header type 2 (CardBus bridges) */
#define FPCI_CB_CAPABILITY_LIST 0x14
/* 0x15 reserved */
#define FPCI_CB_SEC_STATUS  0x16    /* Secondary status */
#define FPCI_CB_PRIMARY_BUS 0x18    /* PCI bus number */
#define FPCI_CB_CARD_BUS        0x19    /* CardBus bus number */
#define FPCI_CB_SUBORDINATE_BUS 0x1a    /* Subordinate bus number */
#define FPCI_CB_LATENCY_TIMER   0x1b    /* CardBus latency timer */
#define FPCI_CB_MEMORY_BASE_0   0x1c
#define FPCI_CB_MEMORY_LIMIT_0  0x20
#define FPCI_CB_MEMORY_BASE_1   0x24
#define FPCI_CB_MEMORY_LIMIT_1  0x28
#define FPCI_CB_IO_BASE_0   0x2c
#define FPCI_CB_IO_BASE_0_HI    0x2e
#define FPCI_CB_IO_LIMIT_0  0x30
#define FPCI_CB_IO_LIMIT_0_HI   0x32
#define FPCI_CB_IO_BASE_1   0x34
#define FPCI_CB_IO_BASE_1_HI    0x36
#define FPCI_CB_IO_LIMIT_1  0x38
#define FPCI_CB_IO_LIMIT_1_HI   0x3a
#define  FPCI_CB_IO_RANGE_MASK  ~0x03
/* 0x3c-0x3d are same as for htype 0 */
#define FPCI_CB_BRIDGE_CONTROL  0x3e
#define  FPCI_CB_BRIDGE_CTL_PARITY  0x01    /* Similar to standard bridge control register */
#define  FPCI_CB_BRIDGE_CTL_SERR        0x02
#define  FPCI_CB_BRIDGE_CTL_ISA     0x04
#define  FPCI_CB_BRIDGE_CTL_VGA     0x08
#define  FPCI_CB_BRIDGE_CTL_MASTER_ABORT 0x20
#define  FPCI_CB_BRIDGE_CTL_CB_RESET    0x40    /* CardBus reset */
#define  FPCI_CB_BRIDGE_CTL_16BIT_INT   0x80    /* Enable interrupt for 16-bit cards */
#define  FPCI_CB_BRIDGE_CTL_PREFETCH_MEM0 0x100 /* Prefetch enable for both memory regions */
#define  FPCI_CB_BRIDGE_CTL_PREFETCH_MEM1 0x200
#define  FPCI_CB_BRIDGE_CTL_POST_WRITES 0x400
#define FPCI_CB_SUBSYSTEM_VENDOR_ID 0x40
#define FPCI_CB_SUBSYSTEM_ID    0x42
#define FPCI_CB_LEGACY_MODE_BASE 0x44   /* 16-bit PC Card legacy mode base address (ExCa) */
/* 0x48-0x7f reserved */


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

/*
 * Address Translation Registers
 */
#define FPCIE_AT_BASE FPCIE_REG_OUTBOUND_R0_PATR0_OFFSET
/*
 * Local Management Registers
 */
#define FPCIE_LM_BASE 0x2000

#define FPCIE_CFG_HEADER_O_TYPE 0x0000

/* Endpoint Function BAR Inbound PCIe to AXI Address Translation Register */
#define FPCIE_AT_IB_EP_FUNC_BAR_ADDR0(fn, bar) \
    (FPCIE_AT_BASE + 0x0840 + (fn)*0x0040 + (bar)*0x0008)
#define FPCIE_AT_IB_EP_FUNC_BAR_ADDR1(fn, bar) \
    (FPCIE_AT_BASE + 0x0844 + (fn)*0x0040 + (bar)*0x0008)

/* Endpoint Function f BAR b Configuration Registers */
#define FPCIE_LM_EP_FUNC_BAR_CFG0(fn) \
    (FPCIE_LM_BASE + 0x0240 + (fn)*0x0008)
#define FPCIE_LM_EP_FUNC_BAR_CFG1(fn) \
    (FPCIE_LM_BASE + 0x0244 + (fn)*0x0008)

#define FPCIE_LM_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK(b) \
    (GENMASK(4, 0) << ((b)*8))
#define FPCIE_LM_EP_FUNC_BAR_CFG_BAR_APERTURE(b, a) \
    (((a) << ((b)*8)) & FPCIE_LM_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK(b))
#define FPCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL_MASK(b) \
    (GENMASK(7, 5) << ((b)*8))
#define FPCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL(b, c) \
    (((c) << ((b)*8 + 5)) & FPCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL_MASK(b))

#define FPCIE_REG_EP_C0_PREF_BASE_LIMIT_OFFSET_GET(config_addr, peu_num) \
    (u32)(config_addr + FPCIE_REG_EP_C0_PREF_BASE_LIMIT_OFFSET + ((peu_num + 3) % 3) * 16)

#define FPCIE_REG_EP_C0_MEM_BASE_LIMIT_OFFSET_GET(config_addr, peu_num) \
    (u32)(config_addr + FPCIE_REG_EP_C0_MEM_BASE_LIMIT_OFFSET + ((peu_num + 3) % 3) * 16)

#define FPCIE_BAR_MEM_TYPE_64 1
#define FPCIE_BAR_MEM_TYPE_32 0
#define FPCIE_PRIMARY_BUS_REG 0x18

#ifdef __cplusplus
}
#endif

#endif // !
