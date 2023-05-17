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
 * FilePath: fgic_distributor.h
 * Date: 2022-03-28 15:18:56
 * LastEditTime: 2022-03-28 15:18:56
 * Description: This file is for gic distributor implementation.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe  2022/4/16   init commit
 */

#ifndef  FGIC_DISTRIBUTOR_H
#define  FGIC_DISTRIBUTOR_H

#include "fgic.h"
#include "fgic_hw.h"
#include "ftypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define GICD_ICFGR_MODE TRIGGER_LEVEL
#define GICD_IRPITER_MODE SPI_ROUTING_MODE

typedef enum
{
    GICD_CTLR_ENABLE_GRP0 = (1 << 0),
    GICD_CTLR_ENABLE_GRP1_NS = (1 << 1),
    GICD_CTLR_ENABLE_GRP1A = (1 << 1),
    GICD_CTLR_ENABLE_GRP1S = (1 << 2),
    GICD_CTLR_ENABLE_ALL = (1 << 2) | (1 << 1) | (1 << 0),
    GICD_CTLR_BIT_ARE_S = (1 << 4), /* Enable Secure state affinity routing ， for single Security state ，this bit is  */
    GICD_CTLR_BIT_ARE_NS = (1 << 5),    /* Enable Non-Secure state affinity routing */
    GICD_CTLR_BIT_DS = (1 << 6),    /* Disable Security support */
    GICD_CTLR_BIT_E1NWF = (1 << 7)  /* Enable "1-of-N" wakeup model */
} GICD_CTLR_VALUE;

typedef enum
{
    GICD_GROUP_G0S = 0,
    GICD_GROUP_G1NS = (1 << 0),
    GICD_GROUP_G1S = (1 << 2),
} GICD_GROUP_SECURE_MODE;

static inline void FGicSetGicd(uintptr dist_base, GICD_CTLR_VALUE ctrl_value)
{
    FGIC_GICD_CTLR_WRITE(dist_base, ctrl_value);
}

/**
 * @name: FGicEnableSPI
 * @msg:  configure the priority for a shared peripheral interrupt
 * @param {FGic} *gic_p is a pointer to the FGic instance.
 * @param {u32} spi_id spi interrupt identifier ,value range 32-1019
 */
static inline void FGicEnableSPI(uintptr dist_base, u32 spi_id)
{
    FGIC_GICD_ISENABLER_WRITE_N_MASK(dist_base, spi_id, (1U << (spi_id % 32)));
}

static inline void FGicDisableSPI(uintptr dist_base, u32 spi_id)
{
    FGIC_GICD_ICENABLER_WRITE_N_MASK(dist_base, spi_id, (1U << (spi_id % 32)));
}

static inline void FGicSetSpiPriority(uintptr dist_base, u32 spi_id, u32 priority)
{
    u32 mask;

    /* For SPIs , has one byte-wide entry per interrupt */
    mask = FGIC_GICD_IPRIORITYR_READ_N_MASK(dist_base, spi_id);
    mask &= ~FGIC_GICD_IPRIORITYR_VALUE_MASK(spi_id);
    mask |= ((priority & 0xffU) << (spi_id % 4) * 8U);
    FGIC_GICD_IPRIORITYR_WRITE_N_MASK(dist_base, spi_id, mask);
}

static inline u32 FGicGetSpiPriority(uintptr dist_base, u32 spi_id)
{
    u32 mask;

    /* For SPIs , has one byte-wide entry per interrupt */
    mask = FGIC_GICD_IPRIORITYR_READ_N_MASK(dist_base, spi_id);

    return (mask >> ((spi_id % 4U) * 8U)) & 0xFFU ;
}

static inline void FGicSetSpiRoute(uintptr dist_base, u32 spi_id, GICD_IRPITER_MODE route_mode, u64 affinity)
{
    u32 bank;

    /* For SPIs ,has one doubleword-wide entry per interrupt */
    bank = spi_id & FGIC_GICD_IROUTER_RANGE_LIMIT;
    __asm__ volatile("dsb 0xF" ::: "memory");
    FGIC_GICD_IROUTER_WRITE(dist_base, bank, affinity | route_mode);
    __asm__ volatile("isb 0xF" ::: "memory");
}

static inline u64 FGicGetSpiRoute(uintptr dist_base, u32 spi_id)
{
    u32 bank;
    /* For SPIs ,has one doubleword-wide entry per interrupt */
    bank = spi_id & FGIC_GICD_IROUTER_RANGE_LIMIT;
    return FGIC_GICD_IROUTER_READ(dist_base, bank);
}

static inline void FGicSetSpiLevel(uintptr dist_base, u32 spi_id, GICD_ICFGR_MODE mode)
{
    u32 mask ;
    mask = FGIC_GICD_ICFGR_READ_N_MASK(dist_base, spi_id);
    mask &= ~FGIC_GICD_ICFGR_VALUE_MASK(spi_id);
    mask |= (mode << FGIC_GICD_ICFGR_VALUE_OFFSET(spi_id));
    FGIC_GICD_ICFGR_WRITE_N_MASK(dist_base, spi_id, mask);
}

static inline u32 FGicGetSpiLevel(uintptr dist_base, u32 spi_id)
{
    u32 mask ;
    mask = FGIC_GICD_ICFGR_READ_N_MASK(dist_base, spi_id);
    return (mask >> ((spi_id % 16U) >> 1U)) ;
}

static inline void FGicSetSpiSecurity(uintptr dist_base, u32 spi_id, GICD_GROUP_SECURE_MODE mode)
{
    u32 mask ;
    /* Group status */
    mask = FGIC_GICD_IGROUPR_READ_N_MASK(dist_base, spi_id);
    mask &= ~FGIC_GICD_IGROUPR_VALUE_MASK(spi_id);

    mask |= ((mode & 0x1) << (spi_id % 32));
    FGIC_GICD_IGROUPR_WRITE_N_MASK(dist_base, spi_id, mask);

    /* Group modifier */
    mask = FGIC_GICD_IGRPMODR_READ_N_MASK(dist_base, spi_id);
    mask &= ~FGIC_GICD_IGRPMODR_VALUE_MASK(spi_id);

    mask |= (((mode & 0x2) >> 1)  << (spi_id % 32));
    FGIC_GICD_IGRPMODR_WRITE_N_MASK(dist_base, spi_id, mask);
}

static inline u32 FGicGetSpiSecurity(uintptr dist_base, u32 spi_id)
{
    u32 mask ;
    u32 group_status, group_modifier;
    /* Group status */
    mask = FGIC_GICD_IGROUPR_READ_N_MASK(dist_base, spi_id);
    mask &= FGIC_GICD_IGROUPR_VALUE_MASK(spi_id);
    group_status = (mask >> (spi_id % 32));

    /* Group modifier */
    mask = FGIC_GICD_IGRPMODR_READ_N_MASK(dist_base, spi_id);
    mask &= FGIC_GICD_IGRPMODR_VALUE_MASK(spi_id);
    group_modifier = (mask >> (spi_id % 32));

    return ((group_modifier << 1) | group_status);
}

#ifdef __cplusplus
}
#endif

#endif // !
