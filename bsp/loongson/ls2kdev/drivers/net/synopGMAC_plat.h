/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-24     chinesebear  first version
 * 2020-08-10     lizhirui     porting to ls2k
 */

#ifndef SYNOP_GMAC_PLAT_H
#define SYNOP_GMAC_PLAT_H 1

/*    sw
#include <linux/kernel.h>
#include <asm/io.h>
#include <linux/gfp.h>
#include <linux/slab.h>
#include <linux/pci.h>
*/
#include "synopGMAC_types.h"
#include "synopGMAC_debug.h"
//#include "mii.h"
//#include "GMAC_Pmon.h"
//#include "synopGMAC_Host.h"
#include <rtthread.h>
#include <stdint.h>
#include "mips_addrspace.h"
//sw:    copy the type define into here
#define IOCTL_READ_REGISTER  SIOCDEVPRIVATE+1
#define IOCTL_WRITE_REGISTER SIOCDEVPRIVATE+2
#define IOCTL_READ_IPSTRUCT  SIOCDEVPRIVATE+3
#define IOCTL_READ_RXDESC    SIOCDEVPRIVATE+4
#define IOCTL_READ_TXDESC    SIOCDEVPRIVATE+5
#define IOCTL_POWER_DOWN     SIOCDEVPRIVATE+6

#define SYNOP_GMAC0 1

typedef int bool;
//typedef unsigned long dma_addr_t;

#define KUSEG_ADDR              0x0
#define CACHED_MEMORY_ADDR      KSEG0BASE
#define UNCACHED_MEMORY_ADDR    KSEG0BASE
#define KSEG2_ADDR              KSEG2BASE
#define MAX_MEM_ADDR            KSEG3BASE
#define RESERVED_ADDR           KSEG3BASE

#define CACHED_TO_PHYS(x)       ((uint64_t)(x) - CACHED_MEMORY_ADDR)
#define PHYS_TO_CACHED(x)       ((uint64_t)(x) + CACHED_MEMORY_ADDR)
#define UNCACHED_TO_PHYS(x)     ((uint64_t)(x) - UNCACHED_MEMORY_ADDR)
#define PHYS_TO_UNCACHED(x)     ((uint64_t)(x) + UNCACHED_MEMORY_ADDR)
#define VA_TO_CINDEX(x)         (PHYS_TO_CACHED(UNCACHED_TO_PHYS(x)))
#define CACHED_TO_UNCACHED(x)   (PHYS_TO_UNCACHED(CACHED_TO_PHYS(x)))

#define VA_TO_PA(x)     CACHED_TO_PHYS(x)

/*    sw
#define TR0(fmt, args...) printk(KERN_CRIT "SynopGMAC: " fmt, ##args)

#ifdef DEBUG
#undef TR
#  define TR(fmt, args...) printk(KERN_CRIT "SynopGMAC: " fmt, ##args)
#else
# define TR(fmt, args...) // not debugging: nothing
#endif
*/
/*
#define TR0(fmt, args...) printf("SynopGMAC: " fmt, ##args)
*/

/*
#ifdef DEBUG
#undef TR
#  define TR(fmt, args...) printf("SynopGMAC: " fmt, ##args)
#else
//# define TR(fmt, args...) // not debugging: nothing
#define TR(fmt, args...) printf("SynopGMAC: " fmt, ##args)
#endif
*/

//sw: nothing to display
#define TR0(fmt, args...) //rt_kprintf(fmt, ##args)
#define TR(fmt, args...)  //rt_kprintf(fmt, ##args)

//typedef int bool;
enum synopGMAC_boolean
 {
    false = 0,
    true = 1
 };

#define DEFAULT_DELAY_VARIABLE  10
#define DEFAULT_LOOP_VARIABLE   10000

/* There are platform related endian conversions
 *
 */
#define LE32_TO_CPU    __le32_to_cpu
#define BE32_TO_CPU    __be32_to_cpu
#define CPU_TO_LE32    __cpu_to_le32

/* Error Codes */
#define ESYNOPGMACNOERR   0
#define ESYNOPGMACNOMEM   1
#define ESYNOPGMACPHYERR  2
#define ESYNOPGMACBUSY    3

struct Network_interface_data
{
    u32 unit;
    u64 addr;
    u32 data;
};


/**
  * These are the wrapper function prototypes for OS/platform related routines
  */
void * plat_alloc_memory(u32 );
void   plat_free_memory(void *);

//void * plat_alloc_consistent_dmaable_memory(struct pci_dev *, u32, u32 *);
//void   plat_free_consistent_dmaable_memory (struct pci_dev *, u32, void *, u32);
void   plat_delay(u32);


/**
 * The Low level function to read register contents from Hardware.
 *
 * @param[in] pointer to the base of register map
 * @param[in] Offset from the base
 * \return  Returns the register contents
 */
static u32  synopGMACReadReg(u64 RegBase, u32 RegOffset)
{
    u64 addr;
    u32 data;

    addr = RegBase + (u32)RegOffset;
    data = *(volatile u32 *)addr;

#if SYNOP_REG_DEBUG
    TR("%s RegBase = 0x%08x RegOffset = 0x%08x RegData = 0x%08x\n", __FUNCTION__, (u32)RegBase, RegOffset, data );
#endif
    //  rt_kprintf("%s RegBase = 0x%08x RegOffset = 0x%08x RegData = 0x%08x\n", __FUNCTION__, (u32)RegBase, RegOffset, data );
    return data;

}

/**
 * The Low level function to write to a register in Hardware.
 *
 * @param[in] pointer to the base of register map
 * @param[in] Offset from the base
 * @param[in] Data to be written
 * \return  void
 */
static void synopGMACWriteReg(u64 RegBase, u32 RegOffset, u32 RegData )
{
    u64 addr;
    addr = RegBase + (u32)RegOffset;
//  rt_kprintf("%s RegBase = 0x%08x RegOffset = 0x%08x RegData = 0x%08x\n", __FUNCTION__,(u32) RegBase, RegOffset, RegData );
#if SYNOP_REG_DEBUG
    TR("%s RegBase = 0x%p RegOffset = 0x%08x RegData = 0x%08x\n", __FUNCTION__,(u32) RegBase, RegOffset, RegData );
#endif
    *(volatile u32 *)addr = RegData;
    /*if(addr == 0xbfe1100c)
        DEBUG_MES("regdata = %08x\n", RegData);*/
    return;
}

/**
 * The Low level function to set bits of a register in Hardware.
 *
 * @param[in] pointer to the base of register map
 * @param[in] Offset from the base
 * @param[in] Bit mask to set bits to logical 1
 * \return  void
 */
static void synopGMACSetBits(u64 RegBase, u32 RegOffset, u32 BitPos)
{
  //u64 addr = (u64)RegBase + (u64)RegOffset;
    u32 data;
    data = synopGMACReadReg(RegBase, RegOffset);
    data |= BitPos;
    synopGMACWriteReg(RegBase, RegOffset, data);
    // writel(data,(void *)addr);
    #if SYNOP_REG_DEBUG
    TR("%s !!!!!!!!!!!!! RegOffset = 0x%08x RegData = 0x%08x\n", __FUNCTION__, RegOffset, data );
    #endif
    return;
}


/**
 * The Low level function to clear bits of a register in Hardware.
 *
 * @param[in] pointer to the base of register map
 * @param[in] Offset from the base
 * @param[in] Bit mask to clear bits to logical 0
 * \return  void
 */
static void  synopGMACClearBits(u64 RegBase, u32 RegOffset, u32 BitPos)
{
    u32 data;
    data = synopGMACReadReg(RegBase, RegOffset);
    data &= (~BitPos);
    synopGMACWriteReg(RegBase, RegOffset, data);
    #if SYNOP_REG_DEBUG
    TR("%s !!!!!!!!!!!!! RegOffset = 0x%08x RegData = 0x%08x\n", __FUNCTION__, RegOffset, data );
    #endif
    return;
}

/**
 * The Low level function to Check the setting of the bits.
 *
 * @param[in] pointer to the base of register map
 * @param[in] Offset from the base
 * @param[in] Bit mask to set bits to logical 1
 * \return  returns TRUE if set to '1' returns FALSE if set to '0'. Result undefined there are no bit set in the BitPos argument.
 *
 */
static bool  synopGMACCheckBits(u64 RegBase, u32 RegOffset, u32 BitPos)
{
    u32 data;
    data = synopGMACReadReg(RegBase, RegOffset);
    data &= BitPos;

    if(data)
    {
        return true;
    }
    else
    {
        return false;
    }
}

#endif
