/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __PCI_REGS_H__
#define __PCI_REGS_H__

#include <rtdef.h>

/*
 *  PCI standard defines
 *  Copyright 1994, Drew Eckhardt
 *  Copyright 1997--1999 Martin Mares <mj@ucw.cz>
 *
 *  For more information, please consult the following manuals (look at
 *  http://www.pcisig.com/ for how to get them):
 *
 *  PCI BIOS Specification
 *  PCI Local Bus Specification
 *  PCI to PCI Bridge Specification
 *  PCI System Design Guide
 *
 *  For HyperTransport information, please consult the following manuals
 *  from http://www.hypertransport.org :
 *
 *  The HyperTransport I/O Link Specification
 *
 *  Mean of prefix:
 *
 *  PCIM_xxx: mask to locate subfield in register
 *  PCIR_xxx: config register offset
 *  PCIC_xxx: device class
 *  PCIS_xxx: device subclass
 *  PCIP_xxx: device programming interface
 *  PCIV_xxx: PCI vendor ID (only required to fixup ancient devices)
 *  PCID_xxx: device ID
 *  PCIY_xxx: capability identification number
 *  PCIZ_xxx: extended capability identification number
 */

/* some PCI bus constants */
#define PCI_DOMAINMAX               65535   /* highest supported domain number */
#define PCI_BUSMAX                  255     /* highest supported bus number */
#define PCI_SLOTMAX                 31      /* highest supported slot number */
#define PCI_FUNCMAX                 7       /* highest supported function number */
#define PCI_REGMAX                  255     /* highest supported config register addr */
#define PCIE_REGMAX                 4095    /* highest supported config register addr */
#define PCI_MAXHDRTYPE              2
#define PCI_STD_HEADER_SIZEOF       64
#define PCI_STD_NUM_BARS            6       /* number of standard BARs */

/* PCI config header registers for all devices */

#define PCIR_DEVVENDOR              0x00
#define PCIR_VENDOR                 0x00
#define PCIR_DEVICE                 0x02
#define PCIR_COMMAND                0x04
#define PCIM_CMD_PORTEN             0x0001
#define PCIM_CMD_MEMEN              0x0002
#define PCIM_CMD_BUSMASTEREN        0x0004
#define PCIM_CMD_SPECIALEN          0x0008
#define PCIM_CMD_MWRICEN            0x0010
#define PCIM_CMD_PERRESPEN          0x0040
#define PCIM_CMD_SERRESPEN          0x0100
#define PCIM_CMD_BACKTOBACK         0x0200
#define PCIM_CMD_INTxDIS            0x0400
#define PCIR_STATUS                 0x06
#define PCIM_STATUS_INTxSTATE       0x0008
#define PCIM_STATUS_CAPPRESENT      0x0010
#define PCIM_STATUS_66CAPABLE       0x0020
#define PCIM_STATUS_BACKTOBACK      0x0080
#define PCIM_STATUS_MDPERR          0x0100
#define PCIM_STATUS_SEL_FAST        0x0000
#define PCIM_STATUS_SEL_MEDIMUM     0x0200
#define PCIM_STATUS_SEL_SLOW        0x0400
#define PCIM_STATUS_SEL_MASK        0x0600
#define PCIM_STATUS_STABORT         0x0800
#define PCIM_STATUS_RTABORT         0x1000
#define PCIM_STATUS_RMABORT         0x2000
#define PCIM_STATUS_SERR            0x4000
#define PCIM_STATUS_PERR            0x8000
#define PCIR_REVID                  0x08
#define PCIR_PROGIF                 0x09
#define PCIR_SUBCLASS               0x0a
#define PCIR_CLASS                  0x0b
#define PCIR_CACHELNSZ              0x0c
#define PCIR_LATTIMER               0x0d
#define PCIR_HDRTYPE                0x0e
#define PCIM_HDRTYPE                0x7f
#define PCIM_HDRTYPE_NORMAL         0x00
#define PCIM_HDRTYPE_BRIDGE         0x01
#define PCIM_HDRTYPE_CARDBUS        0x02
#define PCIM_MFDEV                  0x80
#define PCIR_BIST                   0x0f

/* PCI Spec rev 2.2: 0FFFFh is an invalid value for Vendor ID. */
#define PCIV_INVALID                0xffff

/* Capability Register Offsets */

#define PCICAP_ID                   0x0
#define PCICAP_NEXTPTR              0x1

/* Capability Identification Numbers */

#define PCIY_PMG                    0x01    /* PCI Power Management */
#define PCIY_AGP                    0x02    /* AGP */
#define PCIY_VPD                    0x03    /* Vital Product Data */
#define PCIY_SLOTID                 0x04    /* Slot Identification */
#define PCIY_MSI                    0x05    /* Message Signaled Interrupts */
#define PCIY_CHSWP                  0x06    /* CompactPCI Hot Swap */
#define PCIY_PCIX                   0x07    /* PCI-X */
#define PCIY_HT                     0x08    /* HyperTransport */
#define PCIY_VENDOR                 0x09    /* Vendor Unique */
#define PCIY_DEBUG                  0x0a    /* Debug port */
#define PCIY_CRES                   0x0b    /* CompactPCI central resource control */
#define PCIY_HOTPLUG                0x0c    /* PCI Hot-Plug */
#define PCIY_SUBVENDOR              0x0d    /* PCI-PCI bridge subvendor ID */
#define PCIY_AGP8X                  0x0e    /* AGP 8x */
#define PCIY_SECDEV                 0x0f    /* Secure Device */
#define PCIY_EXPRESS                0x10    /* PCI Express */
#define PCIY_MSIX                   0x11    /* MSI-X */
#define PCIY_SATA                   0x12    /* SATA */
#define PCIY_PCIAF                  0x13    /* PCI Advanced Features */
#define PCIY_EA                     0x14    /* PCI Extended Allocation */
#define PCIY_FPB                    0x15    /* Flattening Portal Bridge */
#define PCIY_MAX                    PCIY_FPB

/* Extended Capability Register Fields */

#define PCIR_EXTCAP                 0x100
#define PCIM_EXTCAP_ID              0x0000ffff
#define PCIM_EXTCAP_VER             0x000f0000
#define PCIM_EXTCAP_NEXTPTR         0xfff00000
#define PCI_EXTCAP_ID(ecap)         ((ecap) & PCIM_EXTCAP_ID)
#define PCI_EXTCAP_VER(ecap)        (((ecap) & PCIM_EXTCAP_VER) >> 16)
#define PCI_EXTCAP_NEXTPTR(ecap)    (((ecap) & PCIM_EXTCAP_NEXTPTR) >> 20)

/* Extended Capability Identification Numbers */

#define PCIZ_AER                    0x0001  /* Advanced Error Reporting */
#define PCIZ_VC                     0x0002  /* Virtual Channel if MFVC Ext Cap not set */
#define PCIZ_SERNUM                 0x0003  /* Device Serial Number */
#define PCIZ_PWRBDGT                0x0004  /* Power Budgeting */
#define PCIZ_RCLINK_DCL             0x0005  /* Root Complex Link Declaration */
#define PCIZ_RCLINK_CTL             0x0006  /* Root Complex Internal Link Control */
#define PCIZ_RCEC_ASSOC             0x0007  /* Root Complex Event Collector Association */
#define PCIZ_MFVC                   0x0008  /* Multi-Function Virtual Channel */
#define PCIZ_VC2                    0x0009  /* Virtual Channel if MFVC Ext Cap set */
#define PCIZ_RCRB                   0x000a  /* RCRB Header */
#define PCIZ_VENDOR                 0x000b  /* Vendor Unique */
#define PCIZ_CAC                    0x000c  /* Configuration Access Correction -- obsolete */
#define PCIZ_ACS                    0x000d  /* Access Control Services */
#define PCIZ_ARI                    0x000e  /* Alternative Routing-ID Interpretation */
#define PCIZ_ATS                    0x000f  /* Address Translation Services */
#define PCIZ_SRIOV                  0x0010  /* Single Root IO Virtualization */
#define PCIZ_MRIOV                  0x0011  /* Multiple Root IO Virtualization */
#define PCIZ_MULTICAST              0x0012  /* Multicast */
#define PCIZ_PAGE_REQ               0x0013  /* Page Request */
#define PCIZ_AMD                    0x0014  /* Reserved for AMD */
#define PCIZ_RESIZE_BAR             0x0015  /* Resizable BAR */
#define PCIZ_DPA                    0x0016  /* Dynamic Power Allocation */
#define PCIZ_TPH_REQ                0x0017  /* TPH Requester */
#define PCIZ_LTR                    0x0018  /* Latency Tolerance Reporting */
#define PCIZ_SEC_PCIE               0x0019  /* Secondary PCI Express */
#define PCIZ_PMUX                   0x001a  /* Protocol Multiplexing */
#define PCIZ_PASID                  0x001b  /* Process Address Space ID */
#define PCIZ_LN_REQ                 0x001c  /* LN Requester */
#define PCIZ_DPC                    0x001d  /* Downstream Port Containment */
#define PCIZ_L1PM                   0x001e  /* L1 PM Substates */
#define PCIZ_PTM                    0x001f  /* Precision Time Measurement */
#define PCIZ_M_PCIE                 0x0020  /* PCIe over M-PHY */
#define PCIZ_FRS                    0x0021  /* FRS Queuing */
#define PCIZ_RTR                    0x0022  /* Readiness Time Reporting */
#define PCIZ_DVSEC                  0x0023  /* Designated Vendor-Specific */
#define PCIZ_VF_REBAR               0x0024  /* VF Resizable BAR */
#define PCIZ_DLNK                   0x0025  /* Data Link Feature */
#define PCIZ_16GT                   0x0026  /* Physical Layer 16.0 GT/s */
#define PCIZ_LMR                    0x0027  /* Lane Margining at Receiver */
#define PCIZ_HIER_ID                0x0028  /* Hierarchy ID */
#define PCIZ_NPEM                   0x0029  /* Native PCIe Enclosure Management */
#define PCIZ_PL32                   0x002a  /* Physical Layer 32.0 GT/s */
#define PCIZ_AP                     0x002b  /* Alternate Protocol */
#define PCIZ_SFI                    0x002c  /* System Firmware Intermediary */

/* Resizable BARs */
#define PCIM_REBAR_CAP              4           /* Capability register */
#define PCIM_REBAR_CAP_SIZES        0x00fffff0  /* Supported BAR sizes */
#define PCIM_REBAR_CTRL             8           /* Control register */
#define PCIM_REBAR_CTRL_BAR_IDX     0x00000007  /* BAR index */
#define PCIM_REBAR_CTRL_NBAR_MASK   0x000000e0
#define PCIM_REBAR_CTRL_NBAR_SHIFT  5           /* Shift for # of BARs */
#define PCIM_REBAR_CTRL_BAR_SIZE    0x00001f00  /* BAR size */
#define PCIM_REBAR_CTRL_BAR_SHIFT   8           /* Shift for BAR size */

/* config registers for header type 0 devices */

#define PCIR_BARS                   0x10
#define PCIR_BAR(x)                 (PCIR_BARS + (x) * 4)
#define PCI_RID2BAR(rid)            (((rid) - PCIR_BARS) / 4)
#define PCI_BAR_IO(x)               (((x) & PCIM_BAR_SPACE) == PCIM_BAR_IO_SPACE)
#define PCI_BAR_MEM(x)              (((x) & PCIM_BAR_SPACE) == PCIM_BAR_MEM_SPACE)
#define PCIM_BAR_SPACE              0x01    /* 0 = memory, 1 = I/O */
#define PCIM_BAR_SPACE_IO           0x01
#define PCIM_BAR_SPACE_MEMORY       0x00
#define PCIM_BAR_MEM_TYPE_MASK      0x06
#define PCIM_BAR_MEM_TYPE_32        0x00    /* 32 bit address */
#define PCIM_BAR_MEM_TYPE_1M        0x02    /* Below 1M [obsolete] */
#define PCIM_BAR_MEM_TYPE_64        0x04    /* 64 bit address */
#define PCIM_BAR_MEM_PREFETCH       0x08    /* prefetchable? */
#define PCIM_BAR_MEM_MASK           (~0x0fUL)
#define PCIM_BAR_IO_MASK            (~0x03UL)
#define PCIR_CIS                    0x28
#define PCIM_CIS_ASI_MASK           0x00000007
#define PCIM_CIS_ASI_CONFIG         0
#define PCIM_CIS_ASI_BAR0           1
#define PCIM_CIS_ASI_BAR1           2
#define PCIM_CIS_ASI_BAR2           3
#define PCIM_CIS_ASI_BAR3           4
#define PCIM_CIS_ASI_BAR4           5
#define PCIM_CIS_ASI_BAR5           6
#define PCIM_CIS_ASI_ROM            7
#define PCIM_CIS_ADDR_MASK          0x0ffffff8
#define PCIM_CIS_ROM_MASK           0xf0000000
#define PCIM_CIS_CONFIG_MASK        0xff
#define PCIR_SUBVEND_0              0x2c
#define PCIR_SUBDEV_0               0x2e
#define PCIR_BIOS                   0x30
#define PCIM_BIOS_ENABLE            0x01
#define PCIM_BIOS_ADDR_MASK         0xfffff800
#define PCIR_CAP_PTR                0x34
#define PCIR_INTLINE                0x3c
#define PCIR_INTPIN                 0x3d
#define PCIR_MINGNT                 0x3e
#define PCIR_MAXLAT                 0x3f

/* config registers for header type 1 (PCI-to-PCI bridge) devices */

#define PCIR_MAX_BAR_1              1
#define PCIR_SECSTAT_1              0x1e

#define PCIR_PRIBUS_1               0x18
#define PCIR_SECBUS_1               0x19
#define PCIR_SUBBUS_1               0x1a
#define PCIR_SECLAT_1               0x1b

#define PCIR_IOBASEL_1              0x1c
#define PCIR_IOLIMITL_1             0x1d
#define PCIR_IOBASEH_1              0x30
#define PCIR_IOLIMITH_1             0x32
#define PCIM_BRIO_16                0x0
#define PCIM_BRIO_32                0x1
#define PCIM_BRIO_MASK              0xf

#define PCIR_MEMBASE_1              0x20
#define PCIR_MEMLIMIT_1             0x22

#define PCIR_PMBASEL_1              0x24
#define PCIR_PMLIMITL_1             0x26
#define PCIR_PMBASEH_1              0x28
#define PCIR_PMLIMITH_1             0x2c
#define PCIM_BRPM_32                0x0
#define PCIM_BRPM_64                0x1
#define PCIM_BRPM_MASK              0xf

#define PCIR_BIOS_1                 0x38
#define PCIR_BRIDGECTL_1            0x3e

#define PCI_PPBMEMBASE(h, l)        ((((rt_uint64_t)(h) << 32) + ((l) << 16)) & ~0xfffff)
#define PCI_PPBMEMLIMIT(h, l)       ((((rt_uint64_t)(h) << 32) + ((l) << 16)) | 0xfffff)
#define PCI_PPBIOBASE(h, l)         ((((h) << 16) + ((l) << 8)) & ~0xfff)
#define PCI_PPBIOLIMIT(h, l)        ((((h) << 16) + ((l) << 8)) | 0xfff)

/* config registers for header t    ype 2 (CardBus) devices */

#define PCIR_MAX_BAR_2              0
#define PCIR_CAP_PTR_2              0x14
#define PCIR_SECSTAT_2              0x16

#define PCIR_PRIBUS_2               0x18
#define PCIR_SECBUS_2               0x19
#define PCIR_SUBBUS_2               0x1a
#define PCIR_SECLAT_2               0x1b

#define PCIR_MEMBASE0_2             0x1c
#define PCIR_MEMLIMIT0_2            0x20
#define PCIR_MEMBASE1_2             0x24
#define PCIR_MEMLIMIT1_2            0x28
#define PCIR_IOBASE0_2              0x2c
#define PCIR_IOLIMIT0_2             0x30
#define PCIR_IOBASE1_2              0x34
#define PCIR_IOLIMIT1_2             0x38
#define PCIM_CBBIO_16               0x0
#define PCIM_CBBIO_32               0x1
#define PCIM_CBBIO_MASK             0x3

#define PCIR_BRIDGECTL_2            0x3e

#define PCIR_SUBVEND_2              0x40
#define PCIR_SUBDEV_2               0x42

#define PCIR_PCCARDIF_2             0x44

#define PCI_CBBMEMBASE(l)           ((l) & ~0xfffff)
#define PCI_CBBMEMLIMIT(l)          ((l) | 0xfffff)
#define PCI_CBBIOBASE(l)            ((l) & ~0x3)
#define PCI_CBBIOLIMIT(l)           ((l) | 0x3)

/* PCI device class, subclass and programming interface definitions */
#define PCIC_NOT_DEFINED                0x0000
#define PCIS_NOT_DEFINED_VGA            0x0001

#define PCIC_STORAGE                    0x01
#define PCIS_STORAGE_SCSI               0x0100
#define PCIS_STORAGE_IDE                0x0101
#define PCIS_STORAGE_FLOPPY             0x0102
#define PCIS_STORAGE_IPI                0x0103
#define PCIS_STORAGE_RAID               0x0104
#define PCIS_STORAGE_SATA               0x0106
#define PCIS_STORAGE_SATA_AHCI          0x010601
#define PCIS_STORAGE_SAS                0x0107
#define PCIS_STORAGE_EXPRESS            0x010802
#define PCIS_STORAGE_OTHER              0x0180

#define PCIC_NETWORK                    0x02
#define PCIS_NETWORK_ETHERNET           0x0200
#define PCIS_NETWORK_TOKEN_RING         0x0201
#define PCIS_NETWORK_FDDI               0x0202
#define PCIS_NETWORK_ATM                0x0203
#define PCIS_NETWORK_OTHER              0x0280

#define PCIC_DISPLAY                    0x03
#define PCIS_DISPLAY_VGA                0x0300
#define PCIS_DISPLAY_XGA                0x0301
#define PCIS_DISPLAY_3D                 0x0302
#define PCIS_DISPLAY_OTHER              0x0380

#define PCIC_MULTIMEDIA                 0x04
#define PCIS_MULTIMEDIA_VIDEO           0x0400
#define PCIS_MULTIMEDIA_AUDIO           0x0401
#define PCIS_MULTIMEDIA_PHONE           0x0402
#define PCIS_MULTIMEDIA_HD_AUDIO        0x0403
#define PCIS_MULTIMEDIA_OTHER           0x0480

#define PCIC_MEMORY                     0x05
#define PCIS_MEMORY_RAM                 0x0500
#define PCIS_MEMORY_FLASH               0x0501
#define PCIS_MEMORY_CXL                 0x0502
#define PCIS_MEMORY_OTHER               0x0580

#define PCIC_BRIDGE                     0x06
#define PCIS_BRIDGE_HOST                0x0600
#define PCIS_BRIDGE_ISA                 0x0601
#define PCIS_BRIDGE_EISA                0x0602
#define PCIS_BRIDGE_MC                  0x0603
#define PCIS_BRIDGE_PCI                 0x0604
#define PCIS_BRIDGE_PCI_NORMAL          0x060400
#define PCIS_BRIDGE_PCI_SUBTRACTIVE     0x060401
#define PCIS_BRIDGE_PCMCIA              0x0605
#define PCIS_BRIDGE_NUBUS               0x0606
#define PCIS_BRIDGE_CARDBUS             0x0607
#define PCIS_BRIDGE_RACEWAY             0x0608
#define PCIS_BRIDGE_OTHER               0x0680

#define PCIC_COMMUNICATION              0x07
#define PCIS_COMMUNICATION_SERIAL       0x0700
#define PCIS_COMMUNICATION_PARALLEL     0x0701
#define PCIS_COMMUNICATION_MULTISERIAL  0x0702
#define PCIS_COMMUNICATION_MODEM        0x0703
#define PCIS_COMMUNICATION_OTHER        0x0780

#define PCIC_SYSTEM                     0x08
#define PCIS_SYSTEM_PIC                 0x0800
#define PCIS_SYSTEM_PIC_IOAPIC          0x080010
#define PCIS_SYSTEM_PIC_IOXAPIC         0x080020
#define PCIS_SYSTEM_DMA                 0x0801
#define PCIS_SYSTEM_TIMER               0x0802
#define PCIS_SYSTEM_RTC                 0x0803
#define PCIS_SYSTEM_PCI_HOTPLUG         0x0804
#define PCIS_SYSTEM_SDHCI               0x0805
#define PCIS_SYSTEM_RCEC                0x0807
#define PCIS_SYSTEM_OTHER               0x0880

#define PCIC_INPUT                      0x09
#define PCIS_INPUT_KEYBOARD             0x0900
#define PCIS_INPUT_PEN                  0x0901
#define PCIS_INPUT_MOUSE                0x0902
#define PCIS_INPUT_SCANNER              0x0903
#define PCIS_INPUT_GAMEPORT             0x0904
#define PCIS_INPUT_OTHER                0x0980

#define PCIC_DOCKING                    0x0a
#define PCIS_DOCKING_GENERIC            0x0a00
#define PCIS_DOCKING_OTHER              0x0a80

#define PCIC_PROCESSOR                  0x0b
#define PCIS_PROCESSOR_386              0x0b00
#define PCIS_PROCESSOR_486              0x0b01
#define PCIS_PROCESSOR_PENTIUM          0x0b02
#define PCIS_PROCESSOR_ALPHA            0x0b10
#define PCIS_PROCESSOR_POWERPC          0x0b20
#define PCIS_PROCESSOR_MIPS             0x0b30
#define PCIS_PROCESSOR_CO               0x0b40

#define PCIC_SERIAL                     0x0c
#define PCIS_SERIAL_FIREWIRE            0x0c00
#define PCIS_SERIAL_FIREWIRE_OHCI       0x0c0010
#define PCIS_SERIAL_ACCESS              0x0c01
#define PCIS_SERIAL_SSA                 0x0c02
#define PCIS_SERIAL_USB                 0x0c03
#define PCIS_SERIAL_USB_UHCI            0x0c0300
#define PCIS_SERIAL_USB_OHCI            0x0c0310
#define PCIS_SERIAL_USB_EHCI            0x0c0320
#define PCIS_SERIAL_USB_XHCI            0x0c0330
#define PCIS_SERIAL_USB_DEVICE          0x0c03fe
#define PCIS_SERIAL_FIBER               0x0c04
#define PCIS_SERIAL_SMBUS               0x0c05
#define PCIS_SERIAL_IPMI                0x0c07
#define PCIS_SERIAL_IPMI_SMIC           0x0c0700
#define PCIS_SERIAL_IPMI_KCS            0x0c0701
#define PCIS_SERIAL_IPMI_BT             0x0c0702

#define PCIC_WIRELESS                   0x0d
#define PCIS_WIRELESS_RF_CONTROLLER     0x0d10
#define PCIS_WIRELESS_WHCI              0x0d1010

#define PCIC_INTELLIGENT                0x0e
#define PCIS_INTELLIGENT_I2O            0x0e00

#define PCIC_SATELLITE                  0x0f
#define PCIS_SATELLITE_TV               0x0f00
#define PCIS_SATELLITE_AUDIO            0x0f01
#define PCIS_SATELLITE_VOICE            0x0f03
#define PCIS_SATELLITE_DATA             0x0f04

#define PCIC_CRYPT                      0x10
#define PCIS_CRYPT_NETWORK              0x1000
#define PCIS_CRYPT_ENTERTAINMENT        0x1001
#define PCIS_CRYPT_OTHER                0x1080

#define PCIC_SIGNAL_PROCESSING          0x11
#define PCIS_SP_DPIO                    0x1100
#define PCIS_SP_OTHER                   0x1180

#define PCIS_OTHERS                     0xff

/* Bridge Control Values. */
#define PCIB_BCR_PERR_ENABLE            0x0001
#define PCIB_BCR_SERR_ENABLE            0x0002
#define PCIB_BCR_ISA_ENABLE             0x0004
#define PCIB_BCR_VGA_ENABLE             0x0008
#define PCIB_BCR_MASTER_ABORT_MODE      0x0020
#define PCIB_BCR_SECBUS_RESET           0x0040
#define PCIB_BCR_SECBUS_BACKTOBACK      0x0080
#define PCIB_BCR_PRI_DISCARD_TIMEOUT    0x0100
#define PCIB_BCR_SEC_DISCARD_TIMEOUT    0x0200
#define PCIB_BCR_DISCARD_TIMER_STATUS   0x0400
#define PCIB_BCR_DISCARD_TIMER_SERREN   0x0800

#define CBB_BCR_PERR_ENABLE             0x0001
#define CBB_BCR_SERR_ENABLE             0x0002
#define CBB_BCR_ISA_ENABLE              0x0004
#define CBB_BCR_VGA_ENABLE              0x0008
#define CBB_BCR_MASTER_ABORT_MODE       0x0020
#define CBB_BCR_CARDBUS_RESET           0x0040
#define CBB_BCR_IREQ_INT_ENABLE         0x0080
#define CBB_BCR_PREFETCH_0_ENABLE       0x0100
#define CBB_BCR_PREFETCH_1_ENABLE       0x0200
#define CBB_BCR_WRITE_POSTING_ENABLE    0x0400

/* PCI power manangement */
#define PCIR_POWER_CAP                  0x2
#define PCIM_PCAP_SPEC                  0x0007
#define PCIM_PCAP_PMEREQCLK             0x0008
#define PCIM_PCAP_DEVSPECINIT           0x0020
#define PCIM_PCAP_AUXPWR_0              0x0000
#define PCIM_PCAP_AUXPWR_55             0x0040
#define PCIM_PCAP_AUXPWR_100            0x0080
#define PCIM_PCAP_AUXPWR_160            0x00c0
#define PCIM_PCAP_AUXPWR_220            0x0100
#define PCIM_PCAP_AUXPWR_270            0x0140
#define PCIM_PCAP_AUXPWR_320            0x0180
#define PCIM_PCAP_AUXPWR_375            0x01c0
#define PCIM_PCAP_AUXPWRMASK            0x01c0
#define PCIM_PCAP_D1SUPP                0x0200
#define PCIM_PCAP_D2SUPP                0x0400
#define PCIM_PCAP_PMEMASK               0xf800
#define PCIM_PCAP_D0PME                 0x0800
#define PCIM_PCAP_D1PME                 0x1000
#define PCIM_PCAP_D2PME                 0x2000
#define PCIM_PCAP_D3PME_HOT             0x4000
#define PCIM_PCAP_D3PME_COLD            0x8000

#define PCIR_POWER_STATUS               0x4
#define PCIM_PSTAT_D0                   0x0000
#define PCIM_PSTAT_D1                   0x0001
#define PCIM_PSTAT_D2                   0x0002
#define PCIM_PSTAT_D3                   0x0003
#define PCIM_PSTAT_DMASK                0x0003
#define PCIM_PSTAT_NOSOFTRESET          0x0008
#define PCIM_PSTAT_PMEENABLE            0x0100
#define PCIM_PSTAT_D0POWER              0x0000
#define PCIM_PSTAT_D1POWER              0x0200
#define PCIM_PSTAT_D2POWER              0x0400
#define PCIM_PSTAT_D3POWER              0x0600
#define PCIM_PSTAT_D0HEAT               0x0800
#define PCIM_PSTAT_D1HEAT               0x0a00
#define PCIM_PSTAT_D2HEAT               0x0c00
#define PCIM_PSTAT_D3HEAT               0x0e00
#define PCIM_PSTAT_DATASELMASK          0x1e00
#define PCIM_PSTAT_DATAUNKN             0x0000
#define PCIM_PSTAT_DATADIV10            0x2000
#define PCIM_PSTAT_DATADIV100           0x4000
#define PCIM_PSTAT_DATADIV1000          0x6000
#define PCIM_PSTAT_DATADIVMASK          0x6000
#define PCIM_PSTAT_PME                  0x8000

#define PCIR_POWER_BSE                  0x6
#define PCIM_PMCSR_BSE_D3B3             0x00
#define PCIM_PMCSR_BSE_D3B2             0x40
#define PCIM_PMCSR_BSE_BPCCE            0x80

#define PCIR_POWER_DATA                 0x7

/* VPD capability registers */
#define PCIR_VPD_ADDR                   0x2
#define PCIR_VPD_DATA                   0x4

/* PCI Message Signalled Interrupts (MSI) */
#define PCIR_MSI_CTRL                   0x2
#define PCIM_MSICTRL_VECTOR             0x0100
#define PCIM_MSICTRL_64BIT              0x0080
#define PCIM_MSICTRL_MME_MASK           0x0070
#define PCIM_MSICTRL_MME_SHIFT          0x4
#define PCIM_MSICTRL_MME_1              0x0000
#define PCIM_MSICTRL_MME_2              0x0010
#define PCIM_MSICTRL_MME_4              0x0020
#define PCIM_MSICTRL_MME_8              0x0030
#define PCIM_MSICTRL_MME_16             0x0040
#define PCIM_MSICTRL_MME_32             0x0050
#define PCIM_MSICTRL_MMC_MASK           0x000e
#define PCIM_MSICTRL_MMC_SHIFT          0x1
#define PCIM_MSICTRL_MMC_1              0x0000
#define PCIM_MSICTRL_MMC_2              0x0002
#define PCIM_MSICTRL_MMC_4              0x0004
#define PCIM_MSICTRL_MMC_8              0x0006
#define PCIM_MSICTRL_MMC_16             0x0008
#define PCIM_MSICTRL_MMC_32             0x000a
#define PCIM_MSICTRL_MSI_ENABLE         0x0001
#define PCIR_MSI_ADDR                   0x4
#define PCIR_MSI_ADDR_HIGH              0x8
#define PCIR_MSI_DATA                   0x8
#define PCIR_MSI_DATA_64BIT             0xc
#define PCIR_MSI_MASK                   0xc
#define PCIR_MSI_MASK_64BIT             0x10
#define PCIR_MSI_PENDING                0x14

/* PCI Enhanced Allocation registers */
#define PCIR_EA_NUM_ENT                 2           /* Number of Capability Entries */
#define PCIM_EA_NUM_ENT_MASK            0x3f        /* Num Entries Mask */
#define PCIR_EA_FIRST_ENT               4           /* First EA Entry in List */
#define PCIR_EA_FIRST_ENT_BRIDGE        8           /* First EA Entry for Bridges */
#define PCIM_EA_ES                      0x00000007  /* Entry Size */
#define PCIM_EA_BEI                     0x000000f0  /* BAR Equivalent Indicator */
#define PCIM_EA_BEI_OFFSET              4
/* 0-5 map to BARs 0-5 respectively */
#define PCIM_EA_BEI_BAR_0               0
#define PCIM_EA_BEI_BAR_5               5
#define PCIM_EA_BEI_BAR(x)              (((x) >> PCIM_EA_BEI_OFFSET) & 0xf)
#define PCIM_EA_BEI_BRIDGE              0x6 /* Resource behind bridge */
#define PCIM_EA_BEI_ENI                 0x7 /* Equivalent Not Indicated */
#define PCIM_EA_BEI_ROM                 0x8 /* Expansion ROM */
/* 9-14 map to VF BARs 0-5 respectively */
#define PCIM_EA_BEI_VF_BAR_0            9
#define PCIM_EA_BEI_VF_BAR_5            14
#define PCIM_EA_BEI_RESERVED            0xf /* Reserved - Treat like ENI */
#define PCIM_EA_PP                      0x0000ff00  /* Primary Properties */
#define PCIM_EA_PP_OFFSET               8
#define PCIM_EA_SP_OFFSET               16
#define PCIM_EA_SP                      0x00ff0000  /* Secondary Properties */
#define PCIM_EA_P_MEM                   0x00    /* Non-Prefetch Memory */
#define PCIM_EA_P_MEM_PREFETCH          0x01    /* Prefetchable Memory */
#define PCIM_EA_P_IO                    0x02    /* I/O Space */
#define PCIM_EA_P_VF_MEM_PREFETCH       0x03    /* VF Prefetchable Memory */
#define PCIM_EA_P_VF_MEM                0x04    /* VF Non-Prefetch Memory */
#define PCIM_EA_P_BRIDGE_MEM            0x05    /* Bridge Non-Prefetch Memory */
#define PCIM_EA_P_BRIDGE_MEM_PREFETCH   0x06    /* Bridge Prefetchable Memory */
#define PCIM_EA_P_BRIDGE_IO             0x07    /* Bridge I/O Space */
/* 0x08-0xfc reserved */
#define PCIM_EA_P_MEM_RESERVED          0xfd    /* Reserved Memory */
#define PCIM_EA_P_IO_RESERVED           0xfe    /* Reserved I/O Space */
#define PCIM_EA_P_UNAVAILABLE           0xff    /* Entry Unavailable */
#define PCIM_EA_WRITABLE                0x40000000  /* Writable: 1 = RW, 0 = HwInit */
#define PCIM_EA_ENABLE                  0x80000000  /* Enable for this entry */
#define PCIM_EA_BASE                    4   /* Base Address Offset */
#define PCIM_EA_MAX_OFFSET              8   /* MaxOffset (resource length) */
/* bit 0 is reserved */
#define PCIM_EA_IS_64                   0x00000002  /* 64-bit field flag */
#define PCIM_EA_FIELD_MASK              0xfffffffc  /* For Base & Max Offset */
/* Bridge config register */
#define PCIM_EA_SEC_NR(reg)             ((reg) & 0xff)
#define PCIM_EA_SUB_NR(reg)             (((reg) >> 8) & 0xff)

/* PCI-X definitions */

/* For header type 0 devices */
#define PCIXR_COMMAND                       0x2
#define PCIXM_COMMAND_DPERR_E               0x0001  /* Data Parity Error Recovery */
#define PCIXM_COMMAND_ERO                   0x0002  /* Enable Relaxed Ordering */
#define PCIXM_COMMAND_MAX_READ              0x000c  /* Maximum Burst Read Count */
#define PCIXM_COMMAND_MAX_READ_512          0x0000
#define PCIXM_COMMAND_MAX_READ_1024         0x0004
#define PCIXM_COMMAND_MAX_READ_2048         0x0008
#define PCIXM_COMMAND_MAX_READ_4096         0x000c
#define PCIXM_COMMAND_MAX_SPLITS            0x0070  /* Maximum Split Transactions */
#define PCIXM_COMMAND_MAX_SPLITS_1          0x0000
#define PCIXM_COMMAND_MAX_SPLITS_2          0x0010
#define PCIXM_COMMAND_MAX_SPLITS_3          0x0020
#define PCIXM_COMMAND_MAX_SPLITS_4          0x0030
#define PCIXM_COMMAND_MAX_SPLITS_8          0x0040
#define PCIXM_COMMAND_MAX_SPLITS_12         0x0050
#define PCIXM_COMMAND_MAX_SPLITS_16         0x0060
#define PCIXM_COMMAND_MAX_SPLITS_32         0x0070
#define PCIXM_COMMAND_VERSION               0x3000
#define PCIXR_STATUS                        0x4
#define PCIXM_STATUS_DEVFN                  0x000000ff
#define PCIXM_STATUS_BUS                    0x0000ff00
#define PCIXM_STATUS_64BIT                  0x00010000
#define PCIXM_STATUS_133CAP                 0x00020000
#define PCIXM_STATUS_SC_DISCARDED           0x00040000
#define PCIXM_STATUS_UNEXP_SC               0x00080000
#define PCIXM_STATUS_COMPLEX_DEV            0x00100000
#define PCIXM_STATUS_MAX_READ               0x00600000
#define PCIXM_STATUS_MAX_READ_512           0x00000000
#define PCIXM_STATUS_MAX_READ_1024          0x00200000
#define PCIXM_STATUS_MAX_READ_2048          0x00400000
#define PCIXM_STATUS_MAX_READ_4096          0x00600000
#define PCIXM_STATUS_MAX_SPLITS             0x03800000
#define PCIXM_STATUS_MAX_SPLITS_1           0x00000000
#define PCIXM_STATUS_MAX_SPLITS_2           0x00800000
#define PCIXM_STATUS_MAX_SPLITS_3           0x01000000
#define PCIXM_STATUS_MAX_SPLITS_4           0x01800000
#define PCIXM_STATUS_MAX_SPLITS_8           0x02000000
#define PCIXM_STATUS_MAX_SPLITS_12          0x02800000
#define PCIXM_STATUS_MAX_SPLITS_16          0x03000000
#define PCIXM_STATUS_MAX_SPLITS_32          0x03800000
#define PCIXM_STATUS_MAX_CUM_READ           0x1c000000
#define PCIXM_STATUS_RCVD_SC_ERR            0x20000000
#define PCIXM_STATUS_266CAP                 0x40000000
#define PCIXM_STATUS_533CAP                 0x80000000

/* For header type 1 devices (PCI-X bridges) */
#define PCIXR_SEC_STATUS                    0x2
#define PCIXM_SEC_STATUS_64BIT              0x0001
#define PCIXM_SEC_STATUS_133CAP             0x0002
#define PCIXM_SEC_STATUS_SC_DISC            0x0004
#define PCIXM_SEC_STATUS_UNEXP_SC           0x0008
#define PCIXM_SEC_STATUS_SC_OVERRUN         0x0010
#define PCIXM_SEC_STATUS_SR_DELAYED         0x0020
#define PCIXM_SEC_STATUS_BUS_MODE           0x03c0
#define PCIXM_SEC_STATUS_VERSION            0x3000
#define PCIXM_SEC_STATUS_266CAP             0x4000
#define PCIXM_SEC_STATUS_533CAP             0x8000
#define PCIXR_BRIDGE_STATUS                 0x4
#define PCIXM_BRIDGE_STATUS_DEVFN           0x000000ff
#define PCIXM_BRIDGE_STATUS_BUS             0x0000ff00
#define PCIXM_BRIDGE_STATUS_64BIT           0x00010000
#define PCIXM_BRIDGE_STATUS_133CAP          0x00020000
#define PCIXM_BRIDGE_STATUS_SC_DISCARDED    0x00040000
#define PCIXM_BRIDGE_STATUS_UNEXP_SC        0x00080000
#define PCIXM_BRIDGE_STATUS_SC_OVERRUN      0x00100000
#define PCIXM_BRIDGE_STATUS_SR_DELAYED      0x00200000
#define PCIXM_BRIDGE_STATUS_DEVID_MSGCAP    0x20000000
#define PCIXM_BRIDGE_STATUS_266CAP          0x40000000
#define PCIXM_BRIDGE_STATUS_533CAP          0x80000000

/* HT (HyperTransport) Capability definitions */
#define PCIR_HT_COMMAND                     0x2
#define PCIM_HTCMD_CAP_MASK                 0xf800  /* Capability type. */
#define PCIM_HTCAP_SLAVE                    0x0000  /* 000xx */
#define PCIM_HTCAP_HOST                     0x2000  /* 001xx */
#define PCIM_HTCAP_SWITCH                   0x4000  /* 01000 */
#define PCIM_HTCAP_INTERRUPT                0x8000  /* 10000 */
#define PCIM_HTCAP_REVISION_ID              0x8800  /* 10001 */
#define PCIM_HTCAP_UNITID_CLUMPING          0x9000  /* 10010 */
#define PCIM_HTCAP_EXT_CONFIG_SPACE         0x9800  /* 10011 */
#define PCIM_HTCAP_ADDRESS_MAPPING          0xa000  /* 10100 */
#define PCIM_HTCAP_MSI_MAPPING              0xa800  /* 10101 */
#define PCIM_HTCAP_DIRECT_ROUTE             0xb000  /* 10110 */
#define PCIM_HTCAP_VCSET                    0xb800  /* 10111 */
#define PCIM_HTCAP_RETRY_MODE               0xc000  /* 11000 */
#define PCIM_HTCAP_X86_ENCODING             0xc800  /* 11001 */
#define PCIM_HTCAP_GEN3                     0xd000  /* 11010 */
#define PCIM_HTCAP_FLE                      0xd800  /* 11011 */
#define PCIM_HTCAP_PM                       0xe000  /* 11100 */
#define PCIM_HTCAP_HIGH_NODE_COUNT          0xe800  /* 11101 */

/* HT MSI Mapping Capability definitions. */
#define PCIM_HTCMD_MSI_ENABLE               0x0001
#define PCIM_HTCMD_MSI_FIXED                0x0002
#define PCIR_HTMSI_ADDRESS_LO               0x4
#define PCIR_HTMSI_ADDRESS_HI               0x8

/* PCI Vendor capability definitions */
#define PCIR_VENDOR_LENGTH                  0x2
#define PCIR_VENDOR_DATA                    0x3

/* PCI Device capability definitions */
#define PCIR_DEVICE_LENGTH                  0x2

/* PCI EHCI Debug Port definitions */
#define PCIR_DEBUG_PORT                     0x2
#define PCIM_DEBUG_PORT_OFFSET              0x1fff
#define PCIM_DEBUG_PORT_BAR                 0xe000

/* PCI-PCI Bridge Subvendor definitions */
#define PCIR_SUBVENDCAP_ID                  0x4
#define PCIR_SUBVENDCAP                     0x4
#define PCIR_SUBDEVCAP                      0x6

/* PCI Express definitions */
#define PCIER_FLAGS                         0x2
#define PCIEM_FLAGS_VERSION                 0x000f
#define PCIEM_FLAGS_TYPE                    0x00f0
#define PCIEM_TYPE_ENDPOINT                 0x0000
#define PCIEM_TYPE_LEGACY_ENDPOINT          0x0010
#define PCIEM_TYPE_ROOT_PORT                0x0040
#define PCIEM_TYPE_UPSTREAM_PORT            0x0050
#define PCIEM_TYPE_DOWNSTREAM_PORT          0x0060
#define PCIEM_TYPE_PCI_BRIDGE               0x0070
#define PCIEM_TYPE_PCIE_BRIDGE              0x0080
#define PCIEM_TYPE_ROOT_INT_EP              0x0090
#define PCIEM_TYPE_ROOT_EC                  0x00a0
#define PCIEM_FLAGS_SLOT                    0x0100
#define PCIEM_FLAGS_IRQ                     0x3e00
#define PCIER_DEVICE_CAP                    0x4
#define PCIEM_CAP_MAX_PAYLOAD               0x00000007
#define PCIEM_CAP_PHANTHOM_FUNCS            0x00000018
#define PCIEM_CAP_EXT_TAG_FIELD             0x00000020
#define PCIEM_CAP_L0S_LATENCY               0x000001c0
#define PCIEM_CAP_L1_LATENCY                0x00000e00
#define PCIEM_CAP_ROLE_ERR_RPT              0x00008000
#define PCIEM_CAP_SLOT_PWR_LIM_VAL          0x03fc0000
#define PCIEM_CAP_SLOT_PWR_LIM_SCALE        0x0c000000
#define PCIEM_CAP_FLR                       0x10000000
#define PCIER_DEVICE_CTL                    0x8
#define PCIEM_CTL_COR_ENABLE                0x0001
#define PCIEM_CTL_NFER_ENABLE               0x0002
#define PCIEM_CTL_FER_ENABLE                0x0004
#define PCIEM_CTL_URR_ENABLE                0x0008
#define PCIEM_CTL_RELAXED_ORD_ENABLE        0x0010
#define PCIEM_CTL_MAX_PAYLOAD               0x00e0
#define PCIEM_CTL_EXT_TAG_FIELD             0x0100
#define PCIEM_CTL_PHANTHOM_FUNCS            0x0200
#define PCIEM_CTL_AUX_POWER_PM              0x0400
#define PCIEM_CTL_NOSNOOP_ENABLE            0x0800
#define PCIEM_CTL_MAX_READ_REQUEST          0x7000
#define PCIEM_CTL_BRDG_CFG_RETRY            0x8000  /* PCI-E - PCI/PCI-X bridges */
#define PCIEM_CTL_INITIATE_FLR              0x8000  /* FLR capable endpoints */
#define PCIER_DEVICE_STA                    0xa
#define PCIEM_STA_CORRECTABLE_ERROR         0x0001
#define PCIEM_STA_NON_FATAL_ERROR           0x0002
#define PCIEM_STA_FATAL_ERROR               0x0004
#define PCIEM_STA_UNSUPPORTED_REQ           0x0008
#define PCIEM_STA_AUX_POWER                 0x0010
#define PCIEM_STA_TRANSACTION_PND           0x0020
#define PCIER_LINK_CAP                      0xc
#define PCIEM_LINK_CAP_MAX_SPEED            0x0000000f
#define PCIEM_LINK_CAP_MAX_WIDTH            0x000003f0
#define PCIEM_LINK_CAP_ASPM                 0x00000c00
#define PCIEM_LINK_CAP_L0S_EXIT             0x00007000
#define PCIEM_LINK_CAP_L1_EXIT              0x00038000
#define PCIEM_LINK_CAP_CLOCK_PM             0x00040000
#define PCIEM_LINK_CAP_SURPRISE_DOWN        0x00080000
#define PCIEM_LINK_CAP_DL_ACTIVE            0x00100000
#define PCIEM_LINK_CAP_LINK_BW_NOTIFY       0x00200000
#define PCIEM_LINK_CAP_ASPM_COMPLIANCE      0x00400000
#define PCIEM_LINK_CAP_PORT                 0xff000000
#define PCIER_LINK_CTL                      0x10
#define PCIEM_LINK_CTL_ASPMC_DIS            0x0000
#define PCIEM_LINK_CTL_ASPMC_L0S            0x0001
#define PCIEM_LINK_CTL_ASPMC_L1             0x0002
#define PCIEM_LINK_CTL_ASPMC                0x0003
#define PCIEM_LINK_CTL_RCB                  0x0008
#define PCIEM_LINK_CTL_LINK_DIS             0x0010
#define PCIEM_LINK_CTL_RETRAIN_LINK         0x0020
#define PCIEM_LINK_CTL_COMMON_CLOCK         0x0040
#define PCIEM_LINK_CTL_EXTENDED_SYNC        0x0080
#define PCIEM_LINK_CTL_ECPM                 0x0100
#define PCIEM_LINK_CTL_HAWD                 0x0200
#define PCIEM_LINK_CTL_LBMIE                0x0400
#define PCIEM_LINK_CTL_LABIE                0x0800
#define PCIER_LINK_STA                      0x12
#define PCIEM_LINK_STA_SPEED                0x000f
#define PCIEM_LINK_STA_WIDTH                0x03f0
#define PCIEM_LINK_STA_TRAINING_ERROR       0x0400
#define PCIEM_LINK_STA_TRAINING             0x0800
#define PCIEM_LINK_STA_SLOT_CLOCK           0x1000
#define PCIEM_LINK_STA_DL_ACTIVE            0x2000
#define PCIEM_LINK_STA_LINK_BW_MGMT         0x4000
#define PCIEM_LINK_STA_LINK_AUTO_BW         0x8000
#define PCIER_SLOT_CAP                      0x14
#define PCIEM_SLOT_CAP_APB                  0x00000001
#define PCIEM_SLOT_CAP_PCP                  0x00000002
#define PCIEM_SLOT_CAP_MRLSP                0x00000004
#define PCIEM_SLOT_CAP_AIP                  0x00000008
#define PCIEM_SLOT_CAP_PIP                  0x00000010
#define PCIEM_SLOT_CAP_HPS                  0x00000020
#define PCIEM_SLOT_CAP_HPC                  0x00000040
#define PCIEM_SLOT_CAP_SPLV                 0x00007f80
#define PCIEM_SLOT_CAP_SPLS                 0x00018000
#define PCIEM_SLOT_CAP_EIP                  0x00020000
#define PCIEM_SLOT_CAP_NCCS                 0x00040000
#define PCIEM_SLOT_CAP_PSN                  0xfff80000
#define PCIER_SLOT_CTL                      0x18
#define PCIEM_SLOT_CTL_ABPE                 0x0001
#define PCIEM_SLOT_CTL_PFDE                 0x0002
#define PCIEM_SLOT_CTL_MRLSCE               0x0004
#define PCIEM_SLOT_CTL_PDCE                 0x0008
#define PCIEM_SLOT_CTL_CCIE                 0x0010
#define PCIEM_SLOT_CTL_HPIE                 0x0020
#define PCIEM_SLOT_CTL_AIC                  0x00c0
#define PCIEM_SLOT_CTL_AI_ON                0x0040
#define PCIEM_SLOT_CTL_AI_BLINK             0x0080
#define PCIEM_SLOT_CTL_AI_OFF               0x00c0
#define PCIEM_SLOT_CTL_PIC                  0x0300
#define PCIEM_SLOT_CTL_PI_ON                0x0100
#define PCIEM_SLOT_CTL_PI_BLINK             0x0200
#define PCIEM_SLOT_CTL_PI_OFF               0x0300
#define PCIEM_SLOT_CTL_PCC                  0x0400
#define PCIEM_SLOT_CTL_PC_ON                0x0000
#define PCIEM_SLOT_CTL_PC_OFF               0x0400
#define PCIEM_SLOT_CTL_EIC                  0x0800
#define PCIEM_SLOT_CTL_DLLSCE               0x1000
#define PCIER_SLOT_STA                      0x1a
#define PCIEM_SLOT_STA_ABP                  0x0001
#define PCIEM_SLOT_STA_PFD                  0x0002
#define PCIEM_SLOT_STA_MRLSC                0x0004
#define PCIEM_SLOT_STA_PDC                  0x0008
#define PCIEM_SLOT_STA_CC                   0x0010
#define PCIEM_SLOT_STA_MRLSS                0x0020
#define PCIEM_SLOT_STA_PDS                  0x0040
#define PCIEM_SLOT_STA_EIS                  0x0080
#define PCIEM_SLOT_STA_DLLSC                0x0100
#define PCIER_ROOT_CTL                      0x1c
#define PCIEM_ROOT_CTL_SERR_CORR            0x0001
#define PCIEM_ROOT_CTL_SERR_NONFATAL        0x0002
#define PCIEM_ROOT_CTL_SERR_FATAL           0x0004
#define PCIEM_ROOT_CTL_PME                  0x0008
#define PCIEM_ROOT_CTL_CRS_VIS              0x0010
#define PCIER_ROOT_CAP                      0x1e
#define PCIEM_ROOT_CAP_CRS_VIS              0x0001
#define PCIER_ROOT_STA                      0x20
#define PCIEM_ROOT_STA_PME_REQID_MASK       0x0000ffff
#define PCIEM_ROOT_STA_PME_STATUS           0x00010000
#define PCIEM_ROOT_STA_PME_PEND             0x00020000
#define PCIER_DEVICE_CAP2                   0x24
#define PCIEM_CAP2_COMP_TIMO_RANGES         0x0000000f
#define PCIEM_CAP2_COMP_TIMO_RANGE_A        0x00000001
#define PCIEM_CAP2_COMP_TIMO_RANGE_B        0x00000002
#define PCIEM_CAP2_COMP_TIMO_RANGE_C        0x00000004
#define PCIEM_CAP2_COMP_TIMO_RANGE_D        0x00000008
#define PCIEM_CAP2_COMP_TIMO_DISABLE        0x00000010
#define PCIEM_CAP2_ARI                      0x00000020
#define PCIER_DEVICE_CTL2                   0x28
#define PCIEM_CTL2_COMP_TIMO_VAL            0x000f
#define PCIEM_CTL2_COMP_TIMO_50MS           0x0000
#define PCIEM_CTL2_COMP_TIMO_100US          0x0001
#define PCIEM_CTL2_COMP_TIMO_10MS           0x0002
#define PCIEM_CTL2_COMP_TIMO_55MS           0x0005
#define PCIEM_CTL2_COMP_TIMO_210MS          0x0006
#define PCIEM_CTL2_COMP_TIMO_900MS          0x0009
#define PCIEM_CTL2_COMP_TIMO_3500MS         0x000a
#define PCIEM_CTL2_COMP_TIMO_13S            0x000d
#define PCIEM_CTL2_COMP_TIMO_64S            0x000e
#define PCIEM_CTL2_COMP_TIMO_DISABLE        0x0010
#define PCIEM_CTL2_ARI                      0x0020
#define PCIEM_CTL2_ATOMIC_REQ_ENABLE        0x0040
#define PCIEM_CTL2_ATOMIC_EGR_BLOCK         0x0080
#define PCIEM_CTL2_ID_ORDERED_REQ_EN        0x0100
#define PCIEM_CTL2_ID_ORDERED_CMP_EN        0x0200
#define PCIEM_CTL2_LTR_ENABLE               0x0400
#define PCIEM_CTL2_OBFF                     0x6000
#define PCIEM_OBFF_DISABLE                  0x0000
#define PCIEM_OBFF_MSGA_ENABLE              0x2000
#define PCIEM_OBFF_MSGB_ENABLE              0x4000
#define PCIEM_OBFF_WAKE_ENABLE              0x6000
#define PCIEM_CTL2_END2END_TLP              0x8000
#define PCIER_DEVICE_STA2                   0x2a
#define PCIER_LINK_CAP2                     0x2c
#define PCIER_LINK_CTL2                     0x30
#define PCIEM_LNKCTL2_TLS                   0x000f
#define PCIEM_LNKCTL2_TLS_2_5GT             0x0001
#define PCIEM_LNKCTL2_TLS_5_0GT             0x0002
#define PCIEM_LNKCTL2_TLS_8_0GT             0x0003
#define PCIEM_LNKCTL2_TLS_16_0GT            0x0004
#define PCIEM_LNKCTL2_TLS_32_0GT            0x0005
#define PCIEM_LNKCTL2_TLS_64_0GT            0x0006
#define PCIEM_LNKCTL2_ENTER_COMP            0x0010
#define PCIEM_LNKCTL2_TX_MARGIN             0x0380
#define PCIEM_LNKCTL2_HASD                  0x0020
#define PCIER_LINK_STA2                     0x32
#define PCIER_SLOT_CAP2                     0x34
#define PCIER_SLOT_CTL2                     0x38
#define PCIER_SLOT_STA2                     0x3a

/* MSI-X definitions */
#define PCIR_MSIX_CTRL                      0x2
#define PCIM_MSIXCTRL_MSIX_ENABLE           0x8000
#define PCIM_MSIXCTRL_FUNCTION_MASK         0x4000
#define PCIM_MSIXCTRL_TABLE_SIZE            0x07ff
#define PCIR_MSIX_TABLE                     0x4
#define PCIR_MSIX_PBA                       0x8
#define PCIM_MSIX_BIR_MASK                  0x7
#define PCIM_MSIX_TABLE_OFFSET              0xfffffff8
#define PCIM_MSIX_BIR_BAR_10                0
#define PCIM_MSIX_BIR_BAR_14                1
#define PCIM_MSIX_BIR_BAR_18                2
#define PCIM_MSIX_BIR_BAR_1C                3
#define PCIM_MSIX_BIR_BAR_20                4
#define PCIM_MSIX_BIR_BAR_24                5
#define PCIM_MSIX_ENTRY_SIZE                16
#define PCIM_MSIX_ENTRY_LOWER_ADDR          0x0  /* Message Address */
#define PCIM_MSIX_ENTRY_UPPER_ADDR          0x4  /* Message Upper Address */
#define PCIM_MSIX_ENTRY_DATA                0x8  /* Message Data */
#define PCIM_MSIX_ENTRY_VECTOR_CTRL         0xc  /* Vector Control */
#define PCIM_MSIX_ENTRYVECTOR_CTRL_MASK     0x1

/* PCI Advanced Features definitions */
#define PCIR_PCIAF_CAP                      0x3
#define PCIM_PCIAFCAP_TP                    0x01
#define PCIM_PCIAFCAP_FLR                   0x02
#define PCIR_PCIAF_CTRL                     0x4
#define PCIR_PCIAFCTRL_FLR                  0x01
#define PCIR_PCIAF_STATUS                   0x5
#define PCIR_PCIAFSTATUS_TP                 0x01

/* Advanced Error Reporting */
#define PCIR_AER_UC_STATUS                  0x04
#define PCIM_AER_UC_TRAINING_ERROR          0x00000001
#define PCIM_AER_UC_DL_PROTOCOL_ERROR       0x00000010
#define PCIM_AER_UC_SURPRISE_LINK_DOWN      0x00000020
#define PCIM_AER_UC_POISONED_TLP            0x00001000
#define PCIM_AER_UC_FC_PROTOCOL_ERROR       0x00002000
#define PCIM_AER_UC_COMPLETION_TIMEOUT      0x00004000
#define PCIM_AER_UC_COMPLETER_ABORT         0x00008000
#define PCIM_AER_UC_UNEXPECTED_COMPLETION   0x00010000
#define PCIM_AER_UC_RECEIVER_OVERFLOW       0x00020000
#define PCIM_AER_UC_MALFORMED_TLP           0x00040000
#define PCIM_AER_UC_ECRC_ERROR              0x00080000
#define PCIM_AER_UC_UNSUPPORTED_REQUEST     0x00100000
#define PCIM_AER_UC_ACS_VIOLATION           0x00200000
#define PCIM_AER_UC_INTERNAL_ERROR          0x00400000
#define PCIM_AER_UC_MC_BLOCKED_TLP          0x00800000
#define PCIM_AER_UC_ATOMIC_EGRESS_BLK       0x01000000
#define PCIM_AER_UC_TLP_PREFIX_BLOCKED      0x02000000
#define PCIR_AER_UC_MASK                    0x08    /* Shares bits with UC_STATUS */
#define PCIR_AER_UC_SEVERITY                0x0c    /* Shares bits with UC_STATUS */
#define PCIR_AER_COR_STATUS                 0x10
#define PCIM_AER_COR_RECEIVER_ERROR         0x00000001
#define PCIM_AER_COR_BAD_TLP                0x00000040
#define PCIM_AER_COR_BAD_DLLP               0x00000080
#define PCIM_AER_COR_REPLAY_ROLLOVER        0x00000100
#define PCIM_AER_COR_REPLAY_TIMEOUT         0x00001000
#define PCIM_AER_COR_ADVISORY_NF_ERROR      0x00002000
#define PCIM_AER_COR_INTERNAL_ERROR         0x00004000
#define PCIM_AER_COR_HEADER_LOG_OVFLOW      0x00008000
#define PCIR_AER_COR_MASK                   0x14    /* Shares bits with COR_STATUS */
#define PCIR_AER_CAP_CONTROL                0x18
#define PCIM_AER_FIRST_ERROR_PTR            0x0000001f
#define PCIM_AER_ECRC_GEN_CAPABLE           0x00000020
#define PCIM_AER_ECRC_GEN_ENABLE            0x00000040
#define PCIM_AER_ECRC_CHECK_CAPABLE         0x00000080
#define PCIM_AER_ECRC_CHECK_ENABLE          0x00000100
#define PCIM_AER_MULT_HDR_CAPABLE           0x00000200
#define PCIM_AER_MULT_HDR_ENABLE            0x00000400
#define PCIM_AER_TLP_PREFIX_LOG_PRESENT     0x00000800
#define PCIR_AER_HEADER_LOG                 0x1c
#define PCIR_AER_ROOTERR_CMD                0x2c    /* Only for root complex ports */
#define PCIM_AER_ROOTERR_COR_ENABLE         0x00000001
#define PCIM_AER_ROOTERR_NF_ENABLE          0x00000002
#define PCIM_AER_ROOTERR_F_ENABLE           0x00000004
#define PCIR_AER_ROOTERR_STATUS             0x30    /* Only for root complex ports */
#define PCIM_AER_ROOTERR_COR_ERR            0x00000001
#define PCIM_AER_ROOTERR_MULTI_COR_ERR      0x00000002
#define PCIM_AER_ROOTERR_UC_ERR             0x00000004
#define PCIM_AER_ROOTERR_MULTI_UC_ERR       0x00000008
#define PCIM_AER_ROOTERR_FIRST_UC_FATAL     0x00000010
#define PCIM_AER_ROOTERR_NF_ERR             0x00000020
#define PCIM_AER_ROOTERR_F_ERR              0x00000040
#define PCIM_AER_ROOTERR_INT_MESSAGE        0xf8000000
#define PCIR_AER_COR_SOURCE_ID              0x34    /* Only for root complex ports */
#define PCIR_AER_ERR_SOURCE_ID              0x36    /* Only for root complex ports */
#define PCIR_AER_TLP_PREFIX_LOG             0x38    /* Only for TLP prefix functions */

/* Virtual Channel definitions */
#define PCIR_VC_CAP1                        0x04
#define PCIM_VC_CAP1_EXT_COUNT              0x00000007
#define PCIM_VC_CAP1_LOWPRI_EXT_COUNT       0x00000070
#define PCIR_VC_CAP2                        0x08
#define PCIR_VC_CONTROL                     0x0c
#define PCIR_VC_STATUS                      0x0e
#define PCIR_VC_RESOURCE_CAP(n)             (0x10 + (n) * 0x0c)
#define PCIR_VC_RESOURCE_CTL(n)             (0x14 + (n) * 0x0c)
#define PCIR_VC_RESOURCE_STA(n)             (0x18 + (n) * 0x0c)

/* Serial Number definitions */
#define PCIR_SERIAL_LOW                     0x04
#define PCIR_SERIAL_HIGH                    0x08

/* SR-IOV definitions */
#define PCIR_SRIOV_CTL                      0x08
#define PCIM_SRIOV_VF_EN                    0x01
#define PCIM_SRIOV_VF_MSE                   0x08    /* Memory space enable. */
#define PCIM_SRIOV_ARI_EN                   0x10
#define PCIR_SRIOV_TOTAL_VFS                0x0e
#define PCIR_SRIOV_NUM_VFS                  0x10
#define PCIR_SRIOV_VF_OFF                   0x14
#define PCIR_SRIOV_VF_STRIDE                0x16
#define PCIR_SRIOV_VF_DID                   0x1a
#define PCIR_SRIOV_PAGE_CAP                 0x1c
#define PCIR_SRIOV_PAGE_SIZE                0x20

#define PCI_SRIOV_BASE_PAGE_SHIFT           12

#define PCIR_SRIOV_BARS                     0x24
#define PCIR_SRIOV_BAR(x)                   (PCIR_SRIOV_BARS + (x) * 4)

/* Extended Capability Vendor-Specific definitions */
#define PCIR_VSEC_HEADER                    0x04
#define PCIR_VSEC_ID(hdr)                   ((hdr) & 0xffff)
#define PCIR_VSEC_REV(hdr)                  (((hdr) & 0xf0000) >> 16)
#define PCIR_VSEC_LENGTH(hdr)               (((hdr) & 0xfff00000) >> 20)
#define PCIR_VSEC_DATA                      0x08

/* ASPM L1 PM Substates */
#define PCIR_L1SS_CAP                       0x04        /* Capabilities Register */
#define PCIM_L1SS_CAP_PCIPM_L1_2            0x00000001  /* PCI-PM L1.2 Supported */
#define PCIM_L1SS_CAP_PCIPM_L1_1            0x00000002  /* PCI-PM L1.1 Supported */
#define PCIM_L1SS_CAP_ASPM_L1_2             0x00000004  /* ASPM L1.2 Supported */
#define PCIM_L1SS_CAP_ASPM_L1_1             0x00000008  /* ASPM L1.1 Supported */
#define PCIM_L1SS_CAP_L1_PM_SS              0x00000010  /* L1 PM Substates Supported */
#define PCIM_L1SS_CAP_CM_RESTORE_TIME       0x0000ff00  /* Port Common_Mode_Restore_Time */
#define PCIM_L1SS_CAP_P_PWR_ON_SCALE        0x00030000  /* Port T_POWER_ON scale */
#define PCIM_L1SS_CAP_P_PWR_ON_VALUE        0x00f80000  /* Port T_POWER_ON value */
#define PCIR_L1SS_CTL1                      0x08        /* Control 1 Register */
#define PCIM_L1SS_CTL1_PCIPM_L1_2           0x00000001  /* PCI-PM L1.2 Enable */
#define PCIM_L1SS_CTL1_PCIPM_L1_1           0x00000002  /* PCI-PM L1.1 Enable */
#define PCIM_L1SS_CTL1_ASPM_L1_2            0x00000004  /* ASPM L1.2 Enable */
#define PCIM_L1SS_CTL1_ASPM_L1_1            0x00000008  /* ASPM L1.1 Enable */
#define PCIM_L1SS_CTL1_L1_2_MASK            0x00000005
#define PCIM_L1SS_CTL1_L1SS_MASK            0x0000000f
#define PCIM_L1SS_CTL1_CM_RESTORE_TIME      0x0000ff00  /* Common_Mode_Restore_Time */
#define PCIM_L1SS_CTL1_LTR_L12_TH_VALUE     0x03ff0000  /* LTR_L1.2_THRESHOLD_Value */
#define PCIM_L1SS_CTL1_LTR_L12_TH_SCALE     0xe0000000  /* LTR_L1.2_THRESHOLD_Scale */
#define PCIR_L1SS_CTL2                      0x0c        /* Control 2 Register */
#define PCIM_L1SS_CTL2_T_PWR_ON_SCALE       0x00000003  /* T_POWER_ON Scale */
#define PCIM_L1SS_CTL2_T_PWR_ON_VALUE       0x000000f8  /* T_POWER_ON Value */

/* Alternative Routing-ID Interpretation */
#define PCIR_ARI_CAP                        0x04                /* Capabilities Register */
#define PCIM_ARI_CAP_MFVC                   0x0001              /* MFVC Function Groups Capability */
#define PCIM_ARI_CAP_ACS                    0x0002              /* ACS Function Groups Capability */
#define PCIM_ARI_CAP_NFN(x)                 (((x) >> 8) & 0xff) /* Next Function Number */
#define PCIR_ARI_CTRL                       0x06                /* ARI Control Register */
#define PCIM_ARI_CTRL_MFVC                  0x0001              /* MFVC Function Groups Enable */
#define PCIM_ARI_CTRL_ACS                   0x0002              /* ACS Function Groups Enable */
#define PCIM_ARI_CTRL_FG(x)                 (((x) >> 4) & 7)    /* Function Group */
#define PCIR_EXT_CAP_ARI_SIZEOF             8

/*
 * PCI Express Firmware Interface definitions
 */
#define PCI_OSC_STATUS                      0
#define PCI_OSC_SUPPORT                     1
#define PCIM_OSC_SUPPORT_EXT_PCI_CONF       0x01    /* Extended PCI Config Space */
#define PCIM_OSC_SUPPORT_ASPM               0x02    /* Active State Power Management */
#define PCIM_OSC_SUPPORT_CPMC               0x04    /* Clock Power Management Cap */
#define PCIM_OSC_SUPPORT_SEG_GROUP          0x08    /* PCI Segment Groups supported */
#define PCIM_OSC_SUPPORT_MSI                0x10    /* MSI signalling supported */
#define PCI_OSC_CTL                         2
#define PCIM_OSC_CTL_PCIE_HP                0x01    /* PCIe Native Hot Plug */
#define PCIM_OSC_CTL_SHPC_HP                0x02    /* SHPC Native Hot Plug */
#define PCIM_OSC_CTL_PCIE_PME               0x04    /* PCIe Native Power Mgt Events */
#define PCIM_OSC_CTL_PCIE_AER               0x08    /* PCIe Advanced Error Reporting */
#define PCIM_OSC_CTL_PCIE_CAP_STRUCT        0x10    /* Various Capability Structures */

#endif /* __PCI_REGS_H__ */
