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
 * FilePath: fpcie.c
 * Date: 2022-08-10 14:55:11
 * LastEditTime: 2022-08-18 08:59:28
 * Description: This file is for the minimum required function implementations for this driver.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe  2022/8/18   init commit
 */

/***************************** Include Files *********************************/
#include "fpcie.h"
#include "fpcie_hw.h"
#include "fpcie_common.h"
#include "fparameters.h"
#include "fkernel.h"
#include <stdio.h>
#include <string.h>
#include "fdebug.h"


#define CONFIG_SYS_PCI_CACHE_LINE_SIZE  8
#define upper_32_bits(n) ((u32)(((n) >> 16) >> 16))


/***************** Macros (Inline Functions) Definitions *********************/

#define FPCIE_DEBUG_TAG "FPCIE"
#define FPCIE_ERROR(format, ...) FT_DEBUG_PRINT_E(FPCIE_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FPCIE_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FPCIE_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FPCIE_DEBUG_TAG, format, ##__VA_ARGS__)


/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

extern int FPcieEpCleanBar(FPcie *instance_p, u32 peu_num, u32 bar_num) ;

static void FPcieShowRegion(const char *name, struct FPcieRegion *region)
{
    FPCIE_DEBUG_I("Pci auto config: bus %s region: [0x%llx-0x%llx],\n"
                  "\t\tphysical memory [0x%llx-0x%llx]", name,
                  (unsigned long long)region->bus_start,
                  (unsigned long long)(region->bus_start + region->size - 1),
                  (unsigned long long)region->phys_start,
                  (unsigned long long)(region->phys_start + region->size - 1));
    FPCIE_DEBUG_I("Bus lower is 0x%llx", (unsigned long long)region->bus_lower) ;
}

/**
 * @name: FPcieRegionConfigInit
 * @msg:  初始化PEU 用于分配的地址空间
 * @param {FPcie} *instance_p is a pointer to the FPcie instance.
 * @param {FPcieRegion} *regs 地址空间对应的指针
 * @param {u32} regs_num 传入regs 结构体的数量
 */
//用于资源初始化到instance_p中
static void FPcieRegionConfigInit(FPcie *instance_p, struct FPcieRegion *regs, u32 regs_num)
{
    u32 i ;

    for (i = 0; i < regs_num; i++)
    {
        switch (regs[i].flags)
        {
            case FPCIE_REGION_IO:
                memset(&instance_p->mem_io, 0, sizeof(struct FPcieRegion)) ;
                memcpy(&instance_p->mem_io, regs, sizeof(struct FPcieRegion)) ;
                instance_p->mem_io.exist_flg = FPCIE_REGION_EXIST_FLG ;
                instance_p->mem_io.bus_lower = instance_p->mem_io.phys_start;
                FPcieShowRegion("I/O", &instance_p->mem_io);
                break;
            case FPCIE_REGION_MEM:
                memset(&instance_p->mem, 0, sizeof(struct FPcieRegion)) ;
                memcpy(&instance_p->mem, regs, sizeof(struct FPcieRegion)) ;
                instance_p->mem.exist_flg = FPCIE_REGION_EXIST_FLG ;
                instance_p->mem.bus_lower = instance_p->mem.phys_start;
                FPcieShowRegion("Memory", &instance_p->mem);
                break;
            case (PCI_REGION_PREFETCH|FPCIE_REGION_MEM):
                memset(&instance_p->mem_prefetch, 0, sizeof(struct FPcieRegion)) ;
                memcpy(&instance_p->mem_prefetch, regs, sizeof(struct FPcieRegion)) ;
                instance_p->mem_prefetch.exist_flg = FPCIE_REGION_EXIST_FLG ;
                instance_p->mem_prefetch.bus_lower = instance_p->mem_prefetch.phys_start;
                FPcieShowRegion("Prefetchable Mem", &instance_p->mem_prefetch);
                break;
            default:
                break;
        }
    }
}

/**
 * @name: FPcieCfgInitialize
 * @msg: This function initializes the config space and PCIe bridge.
 * @param {FPcie} *instance_p is a pointer to the FPcie instance.
 * @param {FPcieConfig} *config_p pointer to FPcieConfig instrance Pointer.
 * @return FError
 */
FError FPcieCfgInitialize(FPcie *instance_p, FPcieConfig *config_p) //用于从全局配置数据中获取数据，初始化instance_p
{
    fsize_t i;
    struct FPcieRegion mem_region = {0} ;
    struct FPcieRegion prefetch_region = {0} ;
    struct FPcieRegion io_region = {0} ;

    /* Assert arguments */
    FASSERT(instance_p != NULL);
    FASSERT(config_p != NULL);

    /* Clear instance memory and make copy of configuration */
    memset(instance_p, 0, sizeof(FPcie));
    memcpy(&instance_p->config, config_p, sizeof(FPcieConfig));

    /* 为枚举过程中，涉及的配置空间提供地址划分 */
    /* mem32 地址 */          //使用获取到的硬件信息，来初始化mem32
    mem_region.phys_start = instance_p->config.npmem_base_addr ;
    mem_region.bus_start = instance_p->config.npmem_base_addr ;
    mem_region.size = instance_p->config.npmem_size ;
    mem_region.flags = FPCIE_REGION_MEM ;

    /* mem64 地址 */          //使用获取到的硬件信息，来初始化mem64
    prefetch_region.phys_start = instance_p->config.pmem_base_addr ;
    prefetch_region.bus_start = instance_p->config.pmem_base_addr ;
    prefetch_region.size  = instance_p->config.pmem_size ;
    prefetch_region.flags = (PCI_REGION_PREFETCH | FPCIE_REGION_MEM);

    /* memio 地址 */          //使用获取到的硬件信息，来初始化io
    io_region.phys_start = instance_p->config.io_base_addr ;
    io_region.bus_start = instance_p->config.io_base_addr ;
    io_region.size  = instance_p->config.io_size ;
    io_region.flags = FPCIE_REGION_IO;

    /* scaned bdf array clean */
    instance_p->scaned_bdf_count = 0;

    FPcieRegionConfigInit(instance_p, &mem_region, 1) ;
#if defined(__aarch64__)
    FPcieRegionConfigInit(instance_p, &prefetch_region, 1) ;
#endif
    FPcieRegionConfigInit(instance_p, &io_region, 1) ;

    instance_p->is_ready = FT_COMPONENT_IS_READY;

    return (FT_SUCCESS);
}

u32 FPcieFindCapability(FPcie *instance_p, u32 bdf, u32 cid_type, u32 cid, u32 *cid_offset)
{

    u32 reg_value;
    u32 next_cap_offset;

    if (cid_type == PCIE_CAP)
    {

        /* Serach in PCIe configuration space */
        FPcieEcamReadConfig32bit(instance_p->config.ecam, bdf, FPCIE_CAPABILITY_LIST, &reg_value);
        if (reg_value == 0xffffffff)
        {
            return -1;
        }

        next_cap_offset = (reg_value & 0xff);
        while (next_cap_offset)
        {
            FPcieEcamReadConfig32bit(instance_p->config.ecam, bdf, next_cap_offset, &reg_value);
            if ((reg_value & 0xff) == cid)
            {
                *cid_offset = next_cap_offset;
                return 0;
            }
            next_cap_offset = ((reg_value >> 8) & 0xff);
        }
    }
    else if (cid_type == PCIE_ECAP)
    {

        /* Serach in PCIe extended configuration space */
        next_cap_offset = FPCIE_ECAP_START;
        while (next_cap_offset)
        {
            FPcieEcamReadConfig32bit(instance_p->config.ecam, bdf, next_cap_offset, &reg_value);
            if ((reg_value & 0xffff) == cid)
            {
                *cid_offset = next_cap_offset;
                return 0;
            }
            next_cap_offset = ((reg_value >> 20) & 0xfff);
        }
    }

    /* The capability was not found */
    return -1;
}

const char *FPcieClassStr(u8 class)
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


void FPcieAutoRegionAlign(struct FPcieRegion *res, pci_size_t size)
{
    res->bus_lower = ((res->bus_lower - 1) | (size - 1)) + 1;
}

int FPcieAutoRegionAllocate(struct FPcieRegion *res, pci_size_t size,
                            pci_addr_t *bar, bool supports_64bit)
{
    pci_addr_t addr;

    if (!res)
    {
        FPCIE_DEBUG_E("No resource.");
        goto error;
    }

    addr = ((res->bus_lower - 1) | (size - 1)) + 1;

    if (addr - res->bus_start + size > res->size)
    {
        FPCIE_DEBUG_E("No room in resource.");
        goto error;
    }

    if (upper_32_bits(addr) && !supports_64bit)
    {
        FPCIE_DEBUG_E("Cannot assign 64-bit address to 32-bit-only resource.");
        goto error;
    }

    res->bus_lower = addr + size;

    *bar = addr;
    return 0;

error:
    *bar = (pci_addr_t) -1;
    return -1;
}



/* This function uses BAR to request IO or MMIO space and configure the expansion ROM address */
void FPcieAutoSetupDevice(FPcie *instance_p, u32 bdf, int bars_num,
                          struct FPcieRegion *mem,
                          struct FPcieRegion *prefetch, struct FPcieRegion *io,
                          bool enum_only)
{
    u32 bar_response;
    pci_size_t bar_size;
    u16 cmdstat = 0;
    int bar, bar_nr = 0;
    u8 header_type;
    int rom_addr;
    pci_addr_t bar_value;
    struct FPcieRegion *bar_res = NULL;
    int found_mem64 = 0;
    u16 class;

    /* Command register: enable or disable the access to I/O and memory */
    FPcieEcamReadConfig16bit(instance_p->config.ecam, bdf, FPCIE_COMMAND_REG, &cmdstat);
    cmdstat = (cmdstat & ~(FPCIE_COMMAND_IO | FPCIE_COMMAND_MEMORY)) |
              FPCIE_COMMAND_MASTER;

    for (bar = FPCIE_BASE_ADDRESS_0;
         bar < FPCIE_BASE_ADDRESS_0 + (bars_num * 4); bar += 4)
    {
        /* Tickle the BAR and get the response */
        if (!enum_only)
        {
            FPcieEcamWriteConfig32bit(instance_p->config.ecam, bdf, bar, 0xffffffff);
        }

        FPcieEcamReadConfig32bit(instance_p->config.ecam, bdf, bar, &bar_response);

        /* If BAR is not implemented go to the next BAR */
        if (!bar_response)
        {
            continue;
        }

        found_mem64 = 0;

        /* Check the BAR type and set our address mask */
        if (bar_response & FPCIE_BASE_ADDRESS_SPACE)
        {
            /* formula to get addr space of BAR */
            bar_size = ((~(bar_response & FPCIE_BASE_ADDRESS_IO_MASK))
                        & 0xffff) + 1;
            if (!enum_only)
            {
                bar_res = io;
            }

        }
        else
        {
            if ((bar_response & FPCIE_BASE_ADDRESS_MEM_TYPE_MASK) ==
                FPCIE_BASE_ADDRESS_MEM_TYPE_64)
            {
                u32 bar_response_upper;
                u64 bar64;

                if (!enum_only)
                {
                    FPcieEcamWriteConfig32bit(instance_p->config.ecam, bdf, bar + 4, 0xffffffff);
                }
                FPcieEcamReadConfig32bit(instance_p->config.ecam, bdf, bar + 4, &bar_response_upper);

                bar64 = ((u64)bar_response_upper << 32) |
                        bar_response;

                bar_size = ~(bar64 & FPCIE_BASE_ADDRESS_MEM_MASK)
                           + 1;
                if (!enum_only)
                {
                    found_mem64 = 1;
                }
            }
            else
            {
                bar_size = (u32)(~(bar_response &
                                   FPCIE_BASE_ADDRESS_MEM_MASK) + 1);
            }
            if (!enum_only)
            {
                if ((prefetch->exist_flg & FPCIE_REGION_EXIST_FLG)   & (bar_response &
                        FPCIE_BASE_ADDRESS_MEM_PREFETCH))
                {
                    bar_res = prefetch;
                }
                else
                {
                    bar_res = mem;
                }
            }
        }

        if (!enum_only && FPcieAutoRegionAllocate(bar_res, bar_size,
                &bar_value,
                found_mem64) == 0)
        {
            /* Write it out and update our limit */
            FPcieEcamWriteConfig32bit(instance_p->config.ecam, bdf, bar, (u32)bar_value);

            if (found_mem64)
            {
                bar += 4;

#ifdef CONFIG_SYS_PCI_64BIT
                FPcieEcamWriteConfig32bit(instance_p->config.ecam, bdf, bar, (u32)(bar_value >> 32));
#else
                /*
                 * If we are a 64-bit decoder then increment to
                 * the upper 32 bits of the bar and force it to
                 * locate in the lower 4GB of memory.
                 */
                FPcieEcamWriteConfig32bit(instance_p->config.ecam, bdf, bar, 0x00000000);
#endif
            }
        }

        cmdstat |= (bar_response & FPCIE_BASE_ADDRESS_SPACE) ?
                   FPCIE_COMMAND_IO : FPCIE_COMMAND_MEMORY;

        bar_nr++;
    }

    if (!enum_only)
    {
        /* Configure the expansion ROM address */
        FPcieEcamReadConfig8bit(instance_p->config.ecam, bdf, FPCIE_HEADER_TYPE_REG, &header_type);
        header_type &= 0x7f;
        if (header_type != FPCIE_HEADER_TYPE_CARDBUS)
        {
            rom_addr = (header_type == FPCIE_HEADER_TYPE_NORMAL) ?
                       FPCIE_ROM_ADDRESS : FPCIE_ROM_ADDRESS1;
            FPcieEcamWriteConfig32bit(instance_p->config.ecam, bdf, rom_addr, 0xfffffffe);
            FPcieEcamReadConfig32bit(instance_p->config.ecam, bdf, rom_addr, &bar_response);
            if (bar_response)
            {
                bar_size = -(bar_response & ~1);
                
                if (FPcieAutoRegionAllocate(mem, bar_size,
                                            &bar_value,
                                            false) == 0)
                {
                    FPcieEcamWriteConfig32bit(instance_p->config.ecam, bdf, rom_addr, bar_value);

                }
                cmdstat |= FPCIE_COMMAND_MEMORY;
            }
        }
    }

    /* PCI_COMMAND_IO must be set for VGA device */
    FPcieEcamReadConfig16bit(instance_p->config.ecam, bdf, FPCI_CLASS_DEVICE_REG, &class);
    if (class == FPCI_CLASS_DISPLAY_VGA)
    {
        cmdstat |= FPCIE_COMMAND_IO;
    }

    FPcieEcamWriteConfig16bit(instance_p->config.ecam, bdf, FPCIE_COMMAND_REG, cmdstat);
    FPcieEcamWriteConfig8bit(instance_p->config.ecam, bdf, FPCIE_CACHE_LINE_SIZE_REG,
                             CONFIG_SYS_PCI_CACHE_LINE_SIZE);
    FPcieEcamWriteConfig8bit(instance_p->config.ecam, bdf, FPCIE_LATENCY_TIMER_REG, 0x80);
}

void FPcieAutoPrescanSetupBridge(FPcie *instance_p, u32 bdf, int sub_bus)
{
    struct FPcieRegion *pci_mem;
    struct FPcieRegion *pci_prefetch;
    struct FPcieRegion *pci_io;
    u16 cmdstat, prefechable_64;

    pci_mem = &(instance_p->mem);
    pci_prefetch = &(instance_p->mem_prefetch);
    pci_io = &(instance_p->mem_io);

    FPcieEcamReadConfig16bit(instance_p->config.ecam, bdf, FPCIE_COMMAND_REG, &cmdstat) ;
    FPcieEcamReadConfig16bit(instance_p->config.ecam, bdf, FPCIE_PREF_MEMORY_BASE_REG, &prefechable_64) ;
    prefechable_64 &= FPCIE_PREF_RANGE_TYPE_MASK;

    /* Configure bus number registers *///暂时只有一个pcie配置空间的做法，如果多个pci配置空间，则需当前bus减去该配置空间对应设备的起始bus号
    FPcieEcamWriteConfig8bit(instance_p->config.ecam, bdf, FPCIE_PRIMARY_BUS_REG, FPCIE_BUS(bdf));
    FPcieEcamWriteConfig8bit(instance_p->config.ecam, bdf, FPCIE_SECONDARY_BUS_REG, sub_bus);
    FPcieEcamWriteConfig8bit(instance_p->config.ecam, bdf, FPCIE_SUBORDINATE_BUS_REG, 0xff);

    if (pci_mem->exist_flg & FPCIE_REGION_EXIST_FLG)
    {
        /* Round memory allocator to 1MB boundary */
        FPcieAutoRegionAlign(pci_mem, 0x100000);

        /*
         * Set up memory and I/O filter limits, assume 32-bit
         * I/O space
         */
        FPcieEcamWriteConfig16bit(instance_p->config.ecam, bdf, FPCIE_MEMORY_BASE_REG,
                                  (pci_mem->bus_lower & 0xfff00000) >> 16);

        cmdstat |= FPCIE_COMMAND_MEMORY;
    }

    if (pci_prefetch->exist_flg & FPCIE_REGION_EXIST_FLG)
    {
        /* Round memory allocator to 1MB boundary */
        FPcieAutoRegionAlign(pci_prefetch, 0x100000);

        /*
         * Set up memory and I/O filter limits, assume 32-bit
         * I/O space
         */
        FPcieEcamWriteConfig16bit(instance_p->config.ecam, bdf, FPCIE_PREF_MEMORY_BASE_REG,
                                  (pci_prefetch->bus_lower & 0xfff00000) >> 16);

        if (prefechable_64 == FPCIE_PREF_RANGE_TYPE_64)
#ifdef CONFIG_SYS_PCI_64BIT
            FPcieEcamWriteConfig32bit(instance_p->config.ecam, bdf, FPCIE_PREF_BASE_UPPER32_REG,
                                      pci_prefetch->bus_lower >> 32);
#else
            FPcieEcamWriteConfig32bit(instance_p->config.ecam, bdf, FPCIE_PREF_BASE_UPPER32_REG,
                                      0x0);
#endif

        cmdstat |= FPCIE_COMMAND_MEMORY;
    }
    else
    {
        /* We don't support prefetchable memory for now, so disable */
        FPcieEcamWriteConfig16bit(instance_p->config.ecam, bdf, FPCIE_PREF_MEMORY_BASE_REG, 0x1000);
        FPcieEcamWriteConfig16bit(instance_p->config.ecam, bdf, FPCIE_PREF_MEMORY_LIMIT_REG, 0x0);
        if (prefechable_64 == FPCIE_PREF_RANGE_TYPE_64)
        {
            FPcieEcamWriteConfig16bit(instance_p->config.ecam, bdf, FPCIE_PREF_BASE_UPPER32_REG, 0x0);
            FPcieEcamWriteConfig16bit(instance_p->config.ecam, bdf, FPCIE_PREF_LIMIT_UPPER32_REG, 0x0);
        }
    }

    if (pci_io->exist_flg & FPCIE_REGION_EXIST_FLG)
    {
        /* Round I/O allocator to 4KB boundary */
        FPcieAutoRegionAlign(pci_io, 0x1000);

        FPcieEcamWriteConfig8bit(instance_p->config.ecam, bdf, FPCIE_IO_BASE_REG,
                                 (pci_io->bus_lower & 0x0000f000) >> 8);
        FPcieEcamWriteConfig16bit(instance_p->config.ecam, bdf, FPCIE_IO_BASE_UPPER16_REG,
                                  (pci_io->bus_lower & 0xffff0000) >> 16);

        cmdstat |= FPCIE_COMMAND_IO;
    }

    /* Enable memory and I/O accesses, enable bus master */
    FPcieEcamWriteConfig16bit(instance_p->config.ecam, bdf, FPCIE_COMMAND_REG, cmdstat | FPCIE_COMMAND_MASTER);
}


void FPcieAutoPostscanSetupBridge(FPcie *instance_p, u32 bdf, int sub_bus)
{
    struct FPcieRegion *pci_mem;
    struct FPcieRegion *pci_prefetch;
    struct FPcieRegion *pci_io;

    pci_mem = &(instance_p->mem);
    pci_prefetch = &(instance_p->mem_prefetch);
    pci_io = &(instance_p->mem_io);

    /* Configure bus number registers */
    FPcieEcamWriteConfig8bit(instance_p->config.ecam, bdf, FPCIE_SUBORDINATE_BUS_REG, sub_bus);//配置一下subordinate-bus，可能在固件下不一定必须用

    if (pci_mem->exist_flg & FPCIE_REGION_EXIST_FLG)
    {
        /* Round memory allocator to 1MB boundary */
        FPcieAutoRegionAlign(pci_mem, 0x100000);

        FPcieEcamWriteConfig16bit(instance_p->config.ecam, bdf, FPCIE_MEMORY_LIMIT_REG, (pci_mem->bus_lower - 1) >> 16);
    }

    if (pci_prefetch->exist_flg & FPCIE_REGION_EXIST_FLG)
    {
        u16 prefechable_64;

        FPcieEcamReadConfig16bit(instance_p->config.ecam, bdf, FPCIE_PREF_MEMORY_LIMIT_REG, &prefechable_64);
        prefechable_64 &= FPCIE_PREF_RANGE_TYPE_MASK;

        /* Round memory allocator to 1MB boundary */
        FPcieAutoRegionAlign(pci_prefetch, 0x100000);

        FPcieEcamWriteConfig16bit(instance_p->config.ecam, bdf, FPCIE_PREF_MEMORY_LIMIT_REG, (pci_prefetch->bus_lower - 1) >> 16);
        if (prefechable_64 == FPCIE_PREF_RANGE_TYPE_64)
#ifdef CONFIG_SYS_PCI_64BIT

            FPcieEcamWriteConfig32bit(instance_p->config.ecam, bdf, FPCIE_PREF_LIMIT_UPPER32_REG,
                                      (pci_prefetch->bus_lower - 1) >> 32);
#else
            FPcieEcamWriteConfig32bit(instance_p->config.ecam, bdf, FPCIE_PREF_LIMIT_UPPER32_REG, 0x0);
#endif
    }

    if (pci_io->exist_flg & FPCIE_REGION_EXIST_FLG)
    {
        /* Round I/O allocator to 4KB boundary */
        FPcieAutoRegionAlign(pci_io, 0x1000);

        FPcieEcamWriteConfig8bit(instance_p->config.ecam, bdf, FPCIE_IO_LIMIT_REG,
                                 ((pci_io->bus_lower - 1) & 0x0000f000) >> 8);
        FPcieEcamWriteConfig16bit(instance_p->config.ecam, bdf, FPCIE_IO_LIMIT_UPPER16_REG,
                                  ((pci_io->bus_lower - 1) & 0xffff0000) >> 16);
    }
}


int FPcieHoseProbeBus(FPcie *instance_p, u32 bdf)
{
    int sub_bus;
    int ret;

    instance_p->bus_max = instance_p->bus_max + 1;

    sub_bus = instance_p->bus_max;

    FPcieAutoPrescanSetupBridge(instance_p, bdf, sub_bus);

    FPcieScanBus(instance_p, sub_bus, bdf);

    sub_bus = instance_p->bus_max;
    FPcieAutoPostscanSetupBridge(instance_p, bdf, sub_bus);

    return sub_bus;
}

/*
 * HJF: Changed this to return int. I think this is required
 * to get the correct result when scanning bridges
 */
int FPcieAutoConfigDevice(FPcie *instance_p, u32 bdf)
{
    u16 class = 0;

    struct FPcieRegion *pci_mem;
    struct FPcieRegion *pci_prefetch;
    struct FPcieRegion *pci_io;

    bool enum_only = false;

    int n;

#ifdef CONFIG_PCI_ENUM_ONLY
    enum_only = true;
#endif

    pci_mem = &(instance_p->mem);
    pci_prefetch = &(instance_p->mem_prefetch);
    pci_io = &(instance_p->mem_io);

    FPcieEcamReadConfig16bit(instance_p->config.ecam, bdf, FPCIE_CLASS_DEVICE_REG, &class) ;//读取classcode编号

    switch (class)
    {
        case FPCI_CLASS_BRIDGE_PCI:
            FPcieAutoSetupDevice(instance_p, bdf, 2, pci_mem, pci_prefetch, pci_io,
                                 enum_only);

            n = FPcieHoseProbeBus(instance_p, bdf);
            if (n < 0)
            {
                return n;
            }
            break;

        case FPCI_CLASS_BRIDGE_CARDBUS:
            /*
             * just do a minimal setup of the bridge,
             * let the OS take care of the rest
             */
            FPcieAutoSetupDevice(instance_p, bdf, 0, pci_mem, pci_prefetch, pci_io,
                                 enum_only);

            FPCIE_DEBUG_I("PCI auto config: Found P2CardBus bridge, device %d.", FPCIE_DEV(bdf));

            break;

        case FPCI_CLASS_PROCESSOR_POWERPC: /* an agent or end-point */
            FPCIE_DEBUG_I("PCI auto config: Found PowerPC device.");

        default:
            FPcieAutoSetupDevice(instance_p, bdf, 6, pci_mem, pci_prefetch, pci_io,
                                 enum_only);
            break;
    }

    return FT_SUCCESS;
}


FError FPcieBindBusDevices(FPcie *instance_p, u32 bus_num, u32 parent_bdf, struct FPcieBus *bus)
{
    int dev_count = 0;
    u16 vendor, device;
    u8 header_type;
    s32 bdf, end;
    bool found_multi;
    FError ret;
    u8 class_show;
    u32 dev_exp_cap, bus_exp_cap, dev_ext_ari_cap;
    u32 data;
    char buf_bdf_print[20];
    found_multi = false;
    end = FPCIE_BDF(bus_num, FPCIE_CFG_MAX_NUM_OF_DEV - 1,
                    FPCIE_CFG_MAX_NUM_OF_FUN - 1);

    /* 使用bus的seq成员来进行扫描，其实相当于secondory_bus号 */
    for (bdf = FPCIE_BDF(bus_num, 0, 0); bdf <= end;    
         bdf += FPCIE_BDF(0, 0, 1))
    {
        u32 class;

        /* phytium old pci ip version, need skip in some bus */
        if (instance_p->config.need_skip)
        {
            if (FPcieSkipDevice(instance_p->config.ecam, parent_bdf) == FPCIE_NEED_SKIP)
            {
                continue;
            }
        }

        if (!FPCIE_FUNC(bdf))
        {
            found_multi = false;
        }
        if (FPCIE_FUNC(bdf) && !found_multi)
        {
            continue;
        }

        /* Check only the first access, we don't expect problems */
        FPcieEcamReadConfig16bit(instance_p->config.ecam, bdf, FPCIE_VENDOR_REG, &vendor) ;

        if (vendor == 0xffff || vendor == 0x0000)
        {
            continue;
        }

        FPcieEcamReadConfig8bit(instance_p->config.ecam, bdf, FPCIE_HEADER_TYPE_REG, &header_type) ;

        if (!FPCIE_FUNC(bdf))
        {
            found_multi = header_type & 0x80;
        }
        
        /* 读取deviceid, classcode */
        FPcieEcamReadConfig16bit(instance_p->config.ecam, bdf, FPCIE_DEVICE_ID_REG, &device) ;  
        FPcieEcamReadConfig32bit(instance_p->config.ecam, bdf, FPCI_CLASS_REVISION, &class) ; 
        class >>= 8;

        FPcieEcamReadConfig8bit(instance_p->config.ecam, bdf, FPCIE_CLASS_CODE_REG, &class_show) ;

        if (parent_bdf == 0xffffffff)
        {
            strcpy(buf_bdf_print, "root-controller");
        }
        else
        {
            sprintf(buf_bdf_print, "pci_%x:%x:%x",
                    FPCIE_BUS(parent_bdf), FPCIE_DEV(parent_bdf), FPCIE_FUNC(parent_bdf));
        }
        printf("\t%02x:%02x.%02x\t\t%04lx:%04lx\t\t%s",
               FPCIE_BUS(bdf), FPCIE_DEV(bdf), FPCIE_FUNC(bdf), vendor, device,
               buf_bdf_print);
        printf("\t\t\t0x%.2x (%s)\n", (int)class_show, FPcieClassStr(class_show));

        /* ARI function handle  */
        /* step 1: detect if PCI Express Device */
        ret = FPcieFindCapability(instance_p, bdf, PCIE_CAP, FPCI_CAP_ID_EXP, &dev_exp_cap);
        if (ret == 0 && dev_exp_cap > 0)
        {
            /* step2: check if the device is an ARI device */
            ret = FPcieFindCapability(instance_p, bdf, PCIE_ECAP, FPCI_EXT_CAP_ID_ARI, &dev_ext_ari_cap);
            if (ret == 0 && dev_ext_ari_cap > 0)
            {
                /* step3: check if its parent supports ARI forwarding */
                ret = FPcieFindCapability(instance_p, parent_bdf, PCIE_CAP, FPCI_CAP_ID_EXP, &bus_exp_cap);
                /* config bus ARI forwarding */
                if (ret == 0 && bus_exp_cap > 0)
                {
                    FPcieEcamReadConfig32bit(instance_p->config.ecam, parent_bdf,
                                             bus_exp_cap + FPCIE_CAPABILITY_DEVICE_CAPABILITIES_2_OFFSET, &data);
                    if ((data & FPCIE_CAPABILITY_DEVICE_CAPABILITIES_2_ARI_FORWARDING) != 0)
                    {
                        /* step4: ARI forwarding support in bridge, so enable it */
                        FPcieEcamReadConfig32bit(instance_p->config.ecam, parent_bdf,
                                                 bus_exp_cap + FPCIE_CAPABILITY_DEVICE_CONTROL_2_OFFSET, &data);
                        if (data & FPCIE_CAPABILITY_DEVICE_CONTROL_2_ARI_FORWARDING == 0)
                        {
                            data |= FPCIE_CAPABILITY_DEVICE_CONTROL_2_ARI_FORWARDING;
                            FPcieEcamWriteConfig32bit(instance_p->config.ecam, parent_bdf,
                                                      bus_exp_cap + FPCIE_CAPABILITY_DEVICE_CONTROL_2_OFFSET, data);
                        }
                    }
                }
            }
        }

        bus->ChildN[dev_count] = bdf;
        dev_count++;

        //这里可以将当前的device，保存到全局变量中，供别的驱动来查询。
        instance_p->scaned_bdf_array[instance_p->scaned_bdf_count] = bdf;
        (instance_p->scaned_bdf_count)++;

    }
    bus->ChildCount = dev_count;

    return FT_SUCCESS;

}

FError FPcieScanBus(FPcie *instance_p, u32 bus_num, u32 parent_bdf)
{
    int i = 0;
    s32 bdf;
    struct FPcieBus bus;
    bus.ChildCount = 0;

    /* scan bus 0 device */
    FPcieBindBusDevices(instance_p, bus_num, parent_bdf, &bus);

    if (bus.ChildCount > 0)
    {
        for (i = 0; i < bus.ChildCount; i++)
        {
            bdf = bus.ChildN[i];
            FPcieAutoConfigDevice(instance_p, bdf);
        }
    }
    instance_p->is_scaned = 1;  //表示已经扫描完成

    return FT_SUCCESS;
}

