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
 * FilePath: fgic.c
 * Date: 2022-03-28 09:30:23
 * LastEditTime: 2022-03-28 09:30:24
 * Description: This file is for the minimum required function implementations for this driver.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe  2022/4/16   init commit
 */

#include "fgic.h"
#include "fgic_distributor.h"
#include "fgic_cpu_interface.h"
#include "fgic_redistributor.h"
#include "fgic_hw.h"
#include "ftypes.h"
#include "fkernel.h"
#include "fassert.h"
#include "fdebug.h"


#define FGIC_DEBUG_TAG "FGIC"
#define FGIC_ERROR(format, ...) FT_DEBUG_PRINT_E(FGIC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGIC_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FGIC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGIC_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FGIC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGIC_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FGIC_DEBUG_TAG, format, ##__VA_ARGS__)


#define FGIC_SPI_START_ID       32
#define FGIC_PPI_END_ID         31
#define FGIC_SGI_END_ID         15

#define FGIC_GICD_32_PER_REG    32
#define FGIC_GICD_16_PER_REG    16
#define FGIC_GICD_4_PER_REG     4

#define FGIC_INT_DEFAULT_PRI_X4     0xa0a0a0a0 /* 考虑到当前一般程序工作于EL1，对于NS 或 S 安全状态 ，0x80 - 0xff 的优先级都有存在的可能性 */
#define FGIC_CPU_INTERFACE_DEFAULT_FILTER 0xFF

typedef enum
{
    GICD_CTLR_RWP_WAIT = 0, /* Use GICD_CTLR for test */
    GICR_CTLR_RWP_WAIT,     /* Use GICR_CTLR for test */
} WAIT_RWP_MODE;

/**
 * @name: FGicWaitRwp
 * @msg:    Wait for register write pending
 * @param {uintptr} ctrl_base is a GICD_CTLR address
 * @param {WAIT_RWP_MODE} wait_mode
 * @return {*}
 */
static FError FGicWaitRwp(uintptr ctrl_base, WAIT_RWP_MODE wait_mode)
{
    u32 rwp_mask;
    u32 timeout_cnt = 0;
    if (GICD_CTLR_RWP_WAIT == wait_mode)
    {
        rwp_mask = FGIC_GICD_CTLR_RWP_MASK;
    }
    else if (GICR_CTLR_RWP_WAIT == wait_mode)
    {
        rwp_mask = FGIC_GICR_CTLR_RWP_MASK;
    }
    else
    {
        FGIC_DEBUG_E(" wait_mode not in WAIT_RWP_MODE.");
        return FGIC_CTLR_ERR_TYPE;
    }

    while (FGIC_READREG32(ctrl_base, 0) & rwp_mask)
    {
        if (timeout_cnt ++ >= 0xffffff)
        {
            FGIC_DEBUG_E(" Wait rwp timeout.");
            return FGIC_CTLR_ERR_IN_GET;
        }
    }

    return FGIC_SUCCESS;
}

/**
 * @name: void FGicDistrubutiorInit(FGic *instance_p)
 * @msg:  Initialize Distrubutior
 * @param {FGic} *instance_p is a pointer to the FGic instance.
 */
void FGicDistrubutiorInit(FGic *instance_p)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    u32 max_ints_mun, int_id, int_index;
    uintptr dis_base = instance_p->config.dis_base;
    max_ints_mun = instance_p->max_spi_num;
    /* Disable the distributor */
    FGIC_WRITEREG32(dis_base, FGIC_GICD_CTLR_OFFSET, 0);
    FASSERT(FGicWaitRwp(dis_base + FGIC_GICD_CTLR_OFFSET, GICD_CTLR_RWP_WAIT) == FGIC_SUCCESS);

    if (instance_p->security == ONE_NS_SECURITY_STATE)
    {
        /* Make  GICD_CTLR.DS = 1 ,Non-secure accesses are permitted to access and modify registers that control Group 0 interrupts */
        FGIC_SETBIT(dis_base, FGIC_GICD_CTLR_OFFSET, FGIC_GICD_CTLR_DS_MASK);
        FASSERT(FGIC_READREG32(dis_base, FGIC_GICD_CTLR_OFFSET) & FGIC_GICD_CTLR_DS_MASK);
    }

    /* 关闭所有中断，并将中断分组默认为group 1 */
    for (int_id = FGIC_SPI_START_ID; int_id < max_ints_mun; int_id += FGIC_GICD_32_PER_REG)
    {
        int_index = int_id / FGIC_GICD_32_PER_REG;
        /* Disables forwarding of the corresponding interrupt. */
        FGIC_GICD_ICENABLER_WRITE_N_MASK(dis_base, int_id, FGIC_GICD_ICENABLER_DEFAULT_MASK);
        /*  Changes the state of the corresponding interrupt from pending to inactive, or from active and pending to active. */
        FGIC_GICD_ICPENDR_WRITE_N_MASK(dis_base, int_id, FGIC_GICD_ICPENDR_DEFAULT_MASK);

        if (instance_p->security == ONE_NS_SECURITY_STATE)
        {
            FGIC_GICD_IGROUPR_WRITE_N_MASK(dis_base, int_id, FGIC_GICD_ICPENDR_DEFAULT_MASK);
        }
        else
        {
            FGIC_GICD_IGROUPR_WRITE_N_MASK(dis_base, int_id, FGIC_GICD_ICPENDR_DEFAULT_MASK);
        }
        FGIC_GICD_IGRPMODR_WRITE_N_MASK(dis_base, int_id, FGIC_GICD_IGRPMODR_DEFAULT_MASK);
    }

    FASSERT(FGicWaitRwp(dis_base + FGIC_GICD_CTLR_OFFSET, GICD_CTLR_RWP_WAIT) == FGIC_SUCCESS);

    for (int_id = FGIC_SPI_START_ID; int_id < max_ints_mun; int_id += FGIC_GICD_4_PER_REG)
    {
        FGIC_GICD_IPRIORITYR_WRITE_N_MASK(dis_base, int_id, FGIC_INT_DEFAULT_PRI_X4);
    }

    for (int_id = FGIC_SPI_START_ID; int_id < max_ints_mun; int_id += FGIC_GICD_16_PER_REG)
    {
        FGIC_GICD_ICFGR_WRITE_N_MASK(dis_base, int_id, 0); /* level-sensitive */
    }

    if (instance_p->security == ONE_NS_SECURITY_STATE)
    {
        FGIC_GICD_CTLR_WRITE(dis_base, GICD_CTLR_BIT_ARE_S | GICD_CTLR_ENABLE_GRP1_NS);
    }
    else
    {
        FGIC_GICD_CTLR_WRITE(dis_base, GICD_CTLR_BIT_ARE_NS | GICD_CTLR_ENABLE_GRP1_NS);
    }



}

/**
 * @name: FError FGicRedistrubutiorInit(FGic *instance_p)
 * @msg:  Initialize Redistrubutior
 * @param {FGic} *instance_p is a pointer to the FGic instance.
 * @return {FError} FGIC_SUCCESS is success ,FGIC_ERR_IN_TIMEOUT is timeout
 */
FError FGicRedistrubutiorInit(FGic *instance_p)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    s32 int_id ;
    u32 timeout = 0;
    uintptr redis_base = instance_p->redis_base;
    uintptr sgi_base = instance_p->redis_base + FGIC_GICR_SGI_BASE_OFFSET;

    /* Clear processor sleep and wait till childasleep is cleard */

    FGIC_GICR_WAKER_CLEAR_BIT(redis_base, FGIC_GICR_WAKER_PROCESSOR_SLEEP_MASK);
    while (FGIC_GICR_WAKER_READ(redis_base) & FGIC_GICR_WAKER_CHILDREN_ASLEEP_MASK)
    {
        timeout++;
        if (timeout >= 0xfffffff)
        {
            return FGIC_ERR_IN_TIMEOUT;
        }
    }

    FASSERT(FGicWaitRwp(redis_base, GICR_CTLR_RWP_WAIT) == FGIC_SUCCESS);
    FGIC_GICR_ICENABLER0_WRITE(sgi_base, FGIC_GICR_ICENABLER0_DEFAULT_MASK); /* Disable all sgi ppi */

    /* Clear pending */
    FGIC_GICR_ICPENDR0_WRITE(sgi_base, FGIC_GICR_ICPENDR0_DEFAULT_MASK);

    /* Set sgi ppi route to different security group */

    if (instance_p->security == ONE_NS_SECURITY_STATE)
    {
        FGIC_GICR_IGROUPR0_WRITE(sgi_base, FGIC_GICR_IGROUPR0_DEFAULT_MASK);
    }
    else
    {
        FGIC_GICR_IGROUPR0_WRITE(sgi_base, FGIC_GICR_IGROUPR0_DEFAULT_MASK);
    }
    FGIC_GICR_IGRPMODR0_WRITE(sgi_base, FGIC_GICR_IGRPMODR0_DEFAULT_MASK);

    /* 默认所有优先级为0xa0 */
    for (int_id = 0; int_id < FGIC_SPI_START_ID; int_id += FGIC_GICD_4_PER_REG)
    {
        FGIC_GICR_IPRIORITYR_WRITE(sgi_base, int_id, FGIC_INT_DEFAULT_PRI_X4);
    }

    FGIC_GICR_ICFGR0_WRITE(sgi_base, 0); /* set level-sensitive */
    FGIC_GICR_ICFGR1_WRITE(sgi_base, 0);

    return FGIC_SUCCESS;
}

/**
 * @name: void FGicCpuInterfaceInit(void)
 * @msg:  Initialize Cpu interface  of current core
 */
void FGicCpuInterfaceInit(void)
{
    u32 reg;
    reg = FGicGetICC_SRE_EL1();

    if (!(reg & GICC_SRE_SRE))
    {
        reg |= (GICC_SRE_SRE | GICC_SRE_DFB | GICC_SRE_DIB);
        FGicSetICC_SRE_EL1(reg);
        reg = FGicGetICC_SRE_EL1();
        FASSERT(reg & GICC_SRE_SRE);
    }

    FGicSetICC_PMR(FGIC_CPU_INTERFACE_DEFAULT_FILTER);

    FGicEnableGroup1_EL1();

    FGicSetICC_CTLR_EL1(GICC_CTLR_CBPR); /* ICC_BPR0_EL1 determines the preemption group for both Group 0 and Group 1 interrupts. */
}

/**
 * @name: FError FGicCfgInitialize(FGic *instance_p, const FGicConfig *input_config_p , uintptr redis_base)
 * @msg:  Initialize the GIC driver instance based on the incoming configuration
 * @param {FGic} *instance_p is a pointer to the FGic instance.
 * @param {FGicConfig} *input_config_p Configuration items that need to be applied in the instance
 * @param {uintptr} redis_base is the redistributor adress of current core
 * @return {*}
 */
FError FGicCfgInitialize(FGic *instance_p, const FGicConfig *input_config_p, uintptr redis_base)
{
    u32 max_ints_mun;
    uintptr dis_base;

    FASSERT(instance_p && input_config_p);

    instance_p->config = *input_config_p;
    instance_p->redis_base = redis_base ;
    instance_p->is_ready = FT_COMPONENT_IS_READY;

    dis_base = instance_p->config.dis_base;

    max_ints_mun = FGIC_READREG32(dis_base, FGIC_GICD_TYPER_OFFSET);
    max_ints_mun &= FGIC_GICD_TYPER_ITLINESNUMBER_MASK  ;
    max_ints_mun = ((max_ints_mun + 1) << 5) - 1; /* If the value of this field is N, the maximum SPI INTID is 32(N+1) minus 1. */
    instance_p->max_spi_num = max_ints_mun;

    return FGIC_SUCCESS;
}

/**
 * @name: FError FGicIntEnable(FGic *instance_p,s32 int_id)
 * @msg:  Enables the interrupt function based on the interrupt number
 * @param {FGic} *instance_p is a pointer to the FGic instance.
 * @param {s32} int_id is interrupt id
 * @return {*}
 */
FError FGicIntEnable(FGic *instance_p, s32 int_id)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);

    if (int_id > instance_p->max_spi_num)
    {
        FGIC_DEBUG_E("int_id is over max spi num for FGicIntEnable.");
        return FGIC_CTLR_ERR_NUM;
    }

    if (int_id <= FGIC_PPI_END_ID)
    {
        uintptr redis_base = instance_p->redis_base;
        FGicEnablePrivateInt(redis_base, int_id);
    }
    else
    {
        uintptr dis_base = instance_p->config.dis_base;
        FGicEnableSPI(dis_base, int_id);
    }

    return FGIC_SUCCESS ;
}


/**
 * @name: FError FGicIntEnable(FGic *instance_p,s32 int_id)
 * @msg:  Disable the interrupt function based on the interrupt number
 * @param {FGic} *instance_p is a pointer to the FGic instance.
 * @param {s32} int_id is interrupt id
 */
FError FGicIntDisable(FGic *instance_p, s32 int_id)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);


    if (int_id > instance_p->max_spi_num)
    {
        FGIC_DEBUG_E("int_id is over max spi num for FGicIntDisable.");
        return FGIC_CTLR_ERR_NUM;
    }

    if (int_id <= FGIC_PPI_END_ID)
    {
        uintptr redis_base = instance_p->redis_base;
        FGicDisablePrivateInt(redis_base, int_id);
    }
    else
    {
        uintptr dis_base = instance_p->config.dis_base;
        FGicDisableSPI(dis_base, int_id);
    }

    return FGIC_SUCCESS ;
}


/**
 * @name:   FError FGicSetPriority(FGic *instance_p,s32 int_id,u32 priority)
 * @msg:    Sets the current interrupt priority value based on the interrupt number
 * @param {FGic} *instance_p is a pointer to the FGic instance.
 * @param {s32} int_id  is interrupt id
 * @param {u32} priority is priority value ,valid bit is bit[0:7]
 * @return {*}
 */
FError FGicSetPriority(FGic *instance_p, s32 int_id, u32 priority)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);


    if (int_id > instance_p->max_spi_num)
    {
        FGIC_DEBUG_E("int_id is over max spi num for FGicSetPriority.");
        return FGIC_CTLR_ERR_IN_GET;
    }

    if (int_id <= FGIC_PPI_END_ID)
    {
        uintptr redis_base = instance_p->redis_base;
        FGicSetPrivatePriority(redis_base, int_id, priority);
    }
    else
    {
        uintptr dis_base = instance_p->config.dis_base;
        FGicSetSpiPriority(dis_base, int_id, priority);
    }

    return FGIC_SUCCESS ;
}

/**
 * @name:  u32 FGicGetPriority(FGic *instance_p,s32 int_id)
 * @msg:   Gets the current interrupt priority value based on the interrupt number
 * @param {FGic} *instance_p is a pointer to the FGic instance
 * @param {s32} int_id is interrupt id
 * @return {u32} priority value ,valid bit is bit[0:7]
 */
u32 FGicGetPriority(FGic *instance_p, s32 int_id)
{
    u32 priority;
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);


    if (int_id > instance_p->max_spi_num)
    {
        FGIC_DEBUG_E("int_id is over max spi num for FGicGetPriority.");
        return (u32)FGIC_CTLR_ERR_IN_GET;
    }

    if (int_id <= FGIC_PPI_END_ID)
    {
        uintptr redis_base = instance_p->redis_base;
        priority = FGicGetPrivatePriority(redis_base, int_id);
    }
    else
    {
        uintptr dis_base = instance_p->config.dis_base;
        priority = FGicGetSpiPriority(dis_base, int_id);
    }

    return priority ;
}

/**
 * @name: FError FGicSetTriggerLevel(FGic *instance_p,s32 int_id,TRIGGER_LEVEL trigger_way)
 * @msg:  Sets the interrupt triggering mode based on the current interrupt number
 * @param {FGic} *instance_p is a pointer to the FGic instance
 * @param {s32} int_id is interrupt id
 * @param {TRIGGER_LEVEL} trigger_way is trigger mode
 * @return {*}
 */
FError FGicSetTriggerLevel(FGic *instance_p, s32 int_id, TRIGGER_LEVEL trigger_way)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);

    if (int_id > instance_p->max_spi_num)
    {
        FGIC_DEBUG_E("int_id is over max spi num for FGicSetTriggerLevel.");
        return FGIC_CTLR_ERR_IN_SET;
    }

    if (int_id <= FGIC_SGI_END_ID)
    {
        uintptr redis_base = instance_p->redis_base;
        FGicSetSgiLevel(redis_base, int_id, trigger_way);
    }
    else if (int_id <= FGIC_PPI_END_ID)
    {
        uintptr redis_base = instance_p->redis_base;
        FGicSetPpiLevel(redis_base, int_id, trigger_way);
    }
    else
    {
        uintptr dis_base = instance_p->config.dis_base;
        FGicSetSpiLevel(dis_base, int_id, trigger_way);
    }

    return FGIC_SUCCESS ;
}

/**
 * @name: u32 FGicGetTriggerLevel(FGic *instance_p,s32 int_id)
 * @msg:  Gets the interrupt triggering mode based on the current interrupt number
 * @param {FGic} *instance_p is a pointer to the FGic instance
 * @param {s32} int_id is interrupt id
 * @return {u32} triggering mode
 */
u32 FGicGetTriggerLevel(FGic *instance_p, s32 int_id)
{
    u32 trigger_way;
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);


    if (int_id > instance_p->max_spi_num)
    {
        FGIC_DEBUG_E("int_id is over max spi num for FGicGetTriggerLevel.");
        return (u32)FGIC_CTLR_ERR_IN_GET;
    }

    if (int_id <= FGIC_SGI_END_ID)
    {
        uintptr redis_base = instance_p->redis_base;
        trigger_way = FGicGetSgiLevel(redis_base, int_id);
    }
    else if (int_id <= FGIC_PPI_END_ID)
    {
        uintptr redis_base = instance_p->redis_base;
        trigger_way = FGicGetPpiLevel(redis_base, int_id);
    }
    else
    {
        uintptr dis_base = instance_p->config.dis_base;
        trigger_way = FGicGetSpiLevel(dis_base, int_id);
    }

    return trigger_way ;
}

/**
 * @name: FGicSetSpiAffinityRouting
 * @msg:  Set intermediate routing information for a specific SPI interrupt
 * @param {FGic} *instance_p is a pointer to the FGic instance.
 * @param {u32} int_id is interrupt vector for spi
 * @param {SPI_ROUTING_MODE} route_mode is the interrupt routing mode.
 * @param {u64} affinity  is the affinity level ，format is
 * |--------[bit39-32]-------[bit23-16]-------------[bit15-8]--------[bit7-0]
 * |--------Affinity level3-----Affinity level2-----Affinity level1---Affinity level0
 * @return {*}
 */
FError FGicSetSpiAffinityRouting(FGic *instance_p, s32 int_id, SPI_ROUTING_MODE route_mode, u64 affinity)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    uintptr dis_base = instance_p->config.dis_base;

    if ((int_id > instance_p->max_spi_num)  || (int_id <= FGIC_PPI_END_ID))
    {
        FGIC_DEBUG_E("int_id %d is out of range.", int_id);
        return FGIC_CTLR_ERR_IN_SET;
    }

    FGicSetSpiRoute(dis_base, int_id, route_mode, affinity);
    return FGIC_SUCCESS;
}


/**
 * @name: FGicGetAffinityRouting
 * @msg:  Get intermediate routing information for a specific SPI interrupt
 * @param {FGic} *instance_p is a pointer to the FGic instance.
 * @param {u32} int_id  is interrupt vector for spi
 * @param {SPI_ROUTING_MODE} *route_mode_p is a pointer to get interrupt routing mode.
 * @param {u64} *affinity_p is pointer to get affinity level ,format is
 * |--------[bit39-32]-------[bit23-16]-------------[bit15-8]--------[bit7-0]
 * |--------Affinity level3-----Affinity level2-----Affinity level1---Affinity level0
 * @return {FError}
 */
FError FGicGetAffinityRouting(FGic *instance_p, s32 int_id, SPI_ROUTING_MODE *route_mode_p, u64 *affinity_p)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(route_mode_p != NULL);
    FASSERT(affinity_p != NULL);
    uintptr dis_base = instance_p->config.dis_base;
    u64 reg;

    if ((int_id > instance_p->max_spi_num)  || (int_id <= FGIC_PPI_END_ID))
    {
        FGIC_DEBUG_E("int_id %d is out of range.", int_id);
        return (u32)FGIC_CTLR_ERR_IN_GET;
    }

    reg = FGicGetSpiRoute(dis_base, int_id);
    *route_mode_p = reg & SPI_ROUTING_TO_ANY;
    *affinity_p = reg & FGIC_GICD_IROUTER_AFFINITY_MASK;
    return FGIC_SUCCESS;
}


/**
 * @name: FGicGenerateSgi
 * @msg:  This interface is used for software generated interrupts
 * @param {FGic} *instance_p is a pointer to the FGic instance.
 * @param {u32} int_id  is interrupt vector for spi
 * @param {u32} target_list is the set of PEs for which SGI interrupts will be generated. Each bit corresponds to the PE within a cluster with an Affinity 0 value equal to the bit number.
 * @param {SGI_ROUTING_MODE} routing_mode is Interrupt Routing Mode.
 * @param {u64} affinity is the affinity level ,format is
 * |--------[bit55-48]-------[bit39-32]-------------[bit23-16]
 * |--------Affinity level3-----Affinity level2-----Affinity level1
 * @return {*}
 */
FError FGicGenerateSgi(FGic *instance_p, s32 int_id, u32 target_list, SGI_ROUTING_MODE routing_mode, u64 affinity)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);

    if (int_id > FGIC_SGI_END_ID)
    {
        FGIC_DEBUG_E("int_id %d is out of range.", int_id);
        return FGIC_CTLR_ERR_IN_SET;
    }

    FGicSetICC_SGI1R((int_id & FGIC_ICC_SGI1R_INTID_MASK) << 24, target_list, routing_mode, affinity);
    return FGIC_SUCCESS;
}

/**
 * @name: FGicDeactionInterrupt
 * @msg:  Deactive Interruption of the current active state
 * @param {FGic} *instance_p is a pointer to the FGic instance.
 * @param {s32} int_id is interrupt id
 */
void FGicDeactionInterrupt(FGic *instance_p, s32 int_id)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FGicSetICC_EOIR1(int_id);
}

/**
 * @name: FGicAcknowledgeInt
 * @msg:  Acknowledge pending interrupt
 * @param {FGic} *instance_p is a pointer to the FGic instance.
 * @return {s32}  interrupt id
 */
s32 FGicAcknowledgeInt(FGic *instance_p)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    return FGicGetICC_APR1();
}


/**
 * @name: FGicSetPriorityFilter
 * @msg:  By setting the parameter of ICC_PMR, the interrupt range that the interrupt controller can respond to is determined
 * @param {FGic} *instance_p is a pointer to the FGic instance.
 * @param {u32} priority_mask . If the priority of an interrupt is lower than the value indicated by this field, the interface signals the interrupt to the PE.
 * The reference values  of priority_mask  are as follows
 * |priority_mask---------------256-------254--------252------248-------240
 * |Implemented priority bits---[7:0]----[7:1]------[7:2]-----[7:3]-----[7:4]
 * |priority the growing steps--any-----even value----4---------8--------16
 */
void FGicSetPriorityFilter(FGic *instance_p, u32 priority_mask)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);

    FGicSetICC_PMR(priority_mask);
}


/**
 * @name: FGicGetPriorityFilter
 * @msg:  Gets the current priority filtering value
 * @param {FGic} *instance_p is a pointer to the FGic instance.
 * @return {u32} Priority Mask for the CPU interface . If the priority of an interrupt is lower than the value
 * indicated by this field, the interface signals the interrupt to the PE.
 * The reference values  of priority_mask  are as follows
 * |return value----------------256-------254--------252------248-------240
 * |Implemented priority bits---[7:0]----[7:1]------[7:2]-----[7:3]-----[7:4]
 * |priority the growing steps--any-----even value----4---------8--------16
 */
u32 FGicGetPriorityFilter(FGic *instance_p)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);

    return FGicGetICC_PMR();
}


/**
 * @name: FGicGetPriorityGroup
 * @msg:  Get Binary point value
 * @param {FGic} *instance_p is a pointer to the FGic instance.
 * @return {u32} The relationship between Binary point value and grouping is as follows
 * |return value----------------0-------1--------2------3-------4------5------6-------7
 * |Group priority field------[---]----[7:1]---[7:2]--[7:3]---[7:4]---[7:5]---[7:6]---[7]
 * |Subpriority field---------[---]-----[0]----[1:0]--[2:0]---[3:0]---[4:0]---[5:0]---[6:0]
 */
u32 FGicGetPriorityGroup(FGic *instance_p)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);

    return FGicGetICC_BPR1();
}

/**
 * @name: FGicSetPriorityGroup
 * @msg:  Sets the value of the current group priority
 * @param {FGic} *instance_p is a pointer to the FGic instance.
 * @param {u32} binary_point : The value of this field controls how the 8-bit interrupt priority field is split into a group priority field
 *  The relationship between binary_point value and grouping is as follows
 * |binary_point----------------0-------1--------2------3-------4------5------6-------7
 * |Group priority field------[---]----[7:1]---[7:2]--[7:3]---[7:4]---[7:5]---[7:6]---[7]
 * |Subpriority field---------[---]-----[0]----[1:0]--[2:0]---[3:0]---[4:0]---[5:0]---[6:0]
 */
void FGicSetPriorityGroup(FGic *instance_p, u32 binary_point)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);

    FGicSetICC_BPR1(binary_point);
}


