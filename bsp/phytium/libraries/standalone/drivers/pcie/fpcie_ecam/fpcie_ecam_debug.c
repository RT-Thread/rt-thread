/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
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
 * FilePath: fpcie_debug.c
 * Created Date: 2023-07-11 08:42:27
 * Last Modified: 2023-08-01 13:38:50
 * Description:  This file is for
 *
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 * 1.0     huanghe    2023/08/06        first release
 */
#include "fpcie_ecam.h"
#include "fpcie_ecam_common.h"
#include "string.h"
#include "fdrivers_port.h"

/***************** Macros (Inline Functions) Definitions *********************/

#define FPCIE_DEBUG_DEBUG_TAG "FPCIE_DEBUG"
#define FPCIE_DEBUG_ERROR(format, ...) FT_DEBUG_PRINT_E(FPCIE_DEBUG_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_DEBUG_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FPCIE_DEBUG_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_DEBUG_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FPCIE_DEBUG_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_DEBUG_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FPCIE_DEBUG_DEBUG_TAG, format, ##__VA_ARGS__)



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

const char *FPcieEcamClassStr(u8 class)
{
    switch (class)
    {
        case FPCI_CLASS_NOT_DEFINED:
            return "Build before PCI Rev2.0";
            break;
        case FPCI_BASE_CLASS_STORAGE:
            return "Mass storage controller";
            break;
        case FPCI_BASE_CLASS_NETWORK:
            return "Network controller";
            break;
        case FPCI_BASE_CLASS_DISPLAY:
            return "Display controller";
            break;
        case FPCI_BASE_CLASS_MULTIMEDIA:
            return "Multimedia device";
            break;
        case FPCI_BASE_CLASS_MEMORY:
            return "Memory controller";
            break;
        case FPCI_BASE_CLASS_BRIDGE:
            return "Bridge device";
            break;
        case FPCI_BASE_CLASS_COMMUNICATION:
            return "Simple comm. controller";
            break;
        case FPCI_BASE_CLASS_SYSTEM:
            return "Base system peripheral";
            break;
        case FPCI_BASE_CLASS_INPUT:
            return "Input device";
            break;
        case FPCI_BASE_CLASS_DOCKING:
            return "Docking station";
            break;
        case FPCI_BASE_CLASS_PROCESSOR:
            return "Processor";
            break;
        case FPCI_BASE_CLASS_SERIAL:
            return "Serial bus controller";
            break;
        case FPCI_BASE_CLASS_INTELLIGENT:
            return "Intelligent controller";
            break;
        case FPCI_BASE_CLASS_SATELLITE:
            return "Satellite controller";
            break;
        case FPCI_BASE_CLASS_CRYPT:
            return "Cryptographic device";
            break;
        case FPCI_BASE_CLASS_SIGNAL_PROCESSING:
            return "DSP";
            break;
        case FPCI_CLASS_OTHERS:
            return "Does not fit any class";
            break;
        default:
            return  "???";
            break;
    };
}


void FPcieEcamInfoPrint(FPcieEcam *instance_p)
{
    u32 config_reg ;
    u32 vendor, device;
    u8 bus, dev, function;
    u32 class_code ;
    char buf_bdf_print[20];
    FPCIE_DEBUG_DEBUG_I("\tB:D:F\t\t\tVID:PID\t\t\tclass_code\n");
    for (u32 i = 0; i < instance_p->scans_bdf_count; i++)
    {

        bus =  instance_p->scans_bdf[i].bus;
        dev =  instance_p->scans_bdf[i].device;
        function = instance_p->scans_bdf[i].function;

        if (FPcieEcamReadConfigSpace(instance_p, bus, dev, function, FPCIE_CCR_ID_REG, &config_reg) != FT_SUCCESS)
        {
            FPCIE_DEBUG_DEBUG_E("%s:%d,Failed to read config space", __FUNCTION__, __LINE__) ;
            return ;
        }

        vendor = FPCIE_CCR_VENDOR_ID_MASK(config_reg);
        device = FPCIE_CCR_DEVICE_ID_MASK(config_reg);

        if (FPcieEcamReadConfigSpace(instance_p, bus, dev, function, FPCIE_CCR_REV_CLASSID_REGS, &config_reg) != FT_SUCCESS)
        {
            FPCIE_DEBUG_DEBUG_E("%s:%d,Failed to read config space", __FUNCTION__, __LINE__) ;
            return ;
        }
        class_code = FPCIE_CCR_CLASS_CODE_MASK(config_reg) ;

        /* code */
        sprintf(buf_bdf_print, "pci_%x:%x:%x",
                bus, dev, function);

        FPCIE_DEBUG_DEBUG_I("\t%02x:%02x.%02x\t\t%04lx:%04lx\t\t%s",
                            bus, dev, function, vendor, device,
                            buf_bdf_print);

        FPCIE_DEBUG_DEBUG_I("\t\t\t0x%.2x (%s)\n", (int)class_code, FPcieEcamClassStr(class_code));
    }


}
