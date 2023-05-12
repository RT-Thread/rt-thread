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
 * FilePath: fgic_redistributor.h
 * Date: 2022-03-28 14:57:01
 * LastEditTime: 2022-03-28 14:57:01
 * Description:  This file is for gic redistributor implementation.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe  2022/4/16   init commit
 */

#ifndef  FGIC_REDISTRIBUTOR_H
#define  FGIC_REDISTRIBUTOR_H

#include "fgic.h"
#include "fgic_hw.h"
#include "ftypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    GICR_GROUP_G0S = 0,
    GICR_GROUP_G1NS = (1 << 0),
    GICR_GROUP_G1S = (1 << 2),
} GICR_GROUP_SECURE_MODE;

typedef enum
{
    GICR_WAKER_PROCESSOR_SLEEP = (1 << 1),
    GICR_WAKER_CHILDREN_ASLEEP = (1 << 2)
} GICR_WAKER_MODE;

static inline u32 FGicGetGicrAffinity(uintptr redis_base)
{
    return FGIC_GICR_TYPER_H_READ(redis_base);
}


static inline void FGicWakeGicr(uintptr redis_base)
{
    u32 mask ;
    mask = FGIC_GICR_WAKER_READ(redis_base);
    mask &= ~GICR_WAKER_PROCESSOR_SLEEP ;
    FGIC_GICR_WAKER_WRITE(redis_base, mask);

    do
    {
        mask = FGIC_GICR_WAKER_READ(redis_base);

    }
    while ((mask & GICR_WAKER_CHILDREN_ASLEEP) != 0); /* This PE is not in, and is not entering, a low power state.  */
}


static inline void FGicEnablePrivateInt(uintptr redis_base, s32 int_id)
{
    FGIC_GICR_ISENABLER0_WRITE(redis_base + FGIC_GICR_SGI_BASE_OFFSET, (1U << (int_id % 32)));
}

static inline void FGicDisablePrivateInt(uintptr redis_base, s32 int_id)
{
    FGIC_GICR_ICENABLER0_WRITE(redis_base + FGIC_GICR_SGI_BASE_OFFSET, (1U << (int_id % 32)));
}

static inline void FGicSetPrivatePriority(uintptr redis_base, s32 spi_id, u32 priority)
{
    u32 mask;

    /* For SPIs , has one byte-wide entry per interrupt */
    mask = FGIC_GICR_IPRIORITYR_READ(redis_base + FGIC_GICR_SGI_BASE_OFFSET, spi_id);
    mask &= ~FGIC_GICR_IPRIORITYR_VALUE_MASK(spi_id);
    mask |= ((priority & 0xffU) << (spi_id % 4) * 8U);
    FGIC_GICR_IPRIORITYR_WRITE(redis_base + FGIC_GICR_SGI_BASE_OFFSET, spi_id, mask);
}

static inline u32 FGicGetPrivatePriority(uintptr redis_base, s32 spi_id)
{
    u32 mask;
    /* For SPIs , has one byte-wide entry per interrupt */
    mask = FGIC_GICR_IPRIORITYR_READ(redis_base + FGIC_GICR_SGI_BASE_OFFSET, spi_id);

    return (mask >> ((spi_id % 4U) * 8U)) & 0xFFU;
}

static inline void FGicSetSgiLevel(uintptr redis_base, s32 spi_id, GICD_ICFGR_MODE mode)
{
    u32 mask ;
    mask = FGIC_GICR_ICFGR0_READ(redis_base + FGIC_GICR_SGI_BASE_OFFSET);
    mask &= ~FGIC_GICR_ICFGR0_VALUE_OFFSET(spi_id);
    mask |= (mode << FGIC_GICR_ICFGR0_VALUE_OFFSET(spi_id));
    FGIC_GICR_ICFGR0_WRITE(redis_base, mask);
}

static inline u32 FGicGetSgiLevel(uintptr redis_base, s32 spi_id)
{
    u32 mask ;
    mask = FGIC_GICR_ICFGR0_READ(redis_base + FGIC_GICR_SGI_BASE_OFFSET);
    return (mask >> ((spi_id % 16U) >> 1U)) ;
}


static inline void FGicSetPpiLevel(uintptr redis_base, s32 spi_id, GICD_ICFGR_MODE mode)
{
    u32 mask ;
    mask = FGIC_GICR_ICFGR1_READ(redis_base + FGIC_GICR_SGI_BASE_OFFSET);
    mask &= ~FGIC_GICR_ICFGR1_VALUE_OFFSET(spi_id);
    mask |= (mode << FGIC_GICR_ICFGR1_VALUE_OFFSET(spi_id));
    FGIC_GICR_ICFGR1_WRITE(redis_base, mask);
}


static inline u32 FGicGetPpiLevel(uintptr redis_base, s32 spi_id)
{
    u32 mask ;
    mask = FGIC_GICR_ICFGR1_READ(redis_base + FGIC_GICR_SGI_BASE_OFFSET);
    return (mask >> ((spi_id % 16U) >> 1U)) ;
}

static inline void FGicSetPrivateSecurity(uintptr redis_base, s32 spi_id, GICD_GROUP_SECURE_MODE mode)
{
    u32 mask ;
    /* Group status */
    mask = FGIC_GICR_IGROUPR0_READ(redis_base + FGIC_GICR_SGI_BASE_OFFSET);
    mask &= ~FGIC_GICR_IGROUPR0_VALUE_MASK(spi_id);

    mask |= ((mode & 0x1) << (spi_id % 32));
    FGIC_GICR_IGROUPR0_WRITE(redis_base + FGIC_GICR_SGI_BASE_OFFSET, mask);

    /* Group modifier */
    mask = FGIC_GICR_IGRPMODR0_READ(redis_base + FGIC_GICR_SGI_BASE_OFFSET);
    mask &= ~FGIC_GICR_IGRPMODR0_VALUE_MASK(spi_id);

    mask |= (((mode & 0x2) >> 1)  << (spi_id % 32));
    FGIC_GICR_IGRPMODR0_WRITE(redis_base + FGIC_GICR_SGI_BASE_OFFSET, mask);
}


static inline u32 FGicGetPrivateSecurity(uintptr redis_base, s32 spi_id)
{
    u32 mask ;
    u32 group_status, group_modifier;
    /* Group status */
    mask = FGIC_GICR_IGROUPR0_READ(redis_base + FGIC_GICR_SGI_BASE_OFFSET);
    mask &= FGIC_GICR_IGROUPR0_VALUE_MASK(spi_id);
    group_status = (mask >> (spi_id % 32));

    /* Group modifier */
    mask = FGIC_GICR_IGRPMODR0_READ(redis_base + FGIC_GICR_SGI_BASE_OFFSET);
    mask &= FGIC_GICR_IGRPMODR0_VALUE_MASK(spi_id);
    group_modifier = (mask >> (spi_id % 32));

    return ((group_modifier << 1) | group_status);
}


static inline u32 FGicNonSecureAccessRead(uintptr redis_base)
{
    return FGIC_GICR_NSACR_READ(redis_base + FGIC_GICR_SGI_BASE_OFFSET);
}

#ifdef __cplusplus
}
#endif

#endif

