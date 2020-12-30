/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-28     lizhirui     first version
 */

#ifndef __PCI_H__
#define __PCI_H__

    struct pci_header
    {
        rt_uint16_t VendorID;
        rt_uint16_t DeviceID;
        rt_uint16_t Command;
        rt_uint16_t Status;
        rt_uint32_t RevisionID : 8;
        rt_uint32_t ClassCode : 24;
        rt_uint8_t CachelineSize;
        rt_uint8_t LatencyTimer;
        rt_uint8_t HeaderType;
        rt_uint8_t BIST;
        rt_uint32_t BaseAddressRegister[6];
        rt_uint32_t CardbusCISPointer;
        rt_uint16_t SubsystemVendorID;
        rt_uint16_t SubsystemID;
        rt_uint32_t ExpansionROMBaseAddress;
        rt_uint32_t CapabilitiesPointer : 8;
        rt_uint32_t resv1 : 24;
        rt_uint32_t resv2;
        rt_uint8_t InterruptLine;
        rt_uint8_t InterruptPin;
        rt_uint8_t Min_Gnt;
        rt_uint8_t Max_Lat;
    };

    rt_uint64_t pci_get_device_map_addr(rt_uint64_t bus,rt_uint64_t device,rt_uint64_t function,rt_uint32_t index);

#endif
