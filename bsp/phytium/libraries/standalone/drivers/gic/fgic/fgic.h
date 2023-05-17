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
 * FilePath: fgic.h
 * Date: 2022-03-28 09:30:29
 * LastEditTime: 2022-03-28 09:30:29
 * Description: This file is for detailed description of the device and driver.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe  2022/4/16   init commit
 */

#ifndef FGIC_H
#define FGIC_H

#include "ftypes.h"
#include "ferror_code.h"
#include "fparameters.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define FGIC_RSGI_AFF1_OFFSET 16
#define FGIC_RSGI_AFF2_OFFSET 32
#define FGIC_RSGI_AFF3_OFFSET 48

#define FGIC_SUCCESS    FT_SUCCESS
#define FGIC_CTLR_ERR_TYPE   FT_MAKE_ERRCODE(ErrModBsp, ErrGic, 1) /* 错误选择CTLR 寄存器 */
#define FGIC_CTLR_ERR_NUM    FT_MAKE_ERRCODE(ErrModBsp, ErrGic, 2) /* 当前控制器不支持此中断id */
#define FGIC_CTLR_ERR_IN_SET    FT_MAKE_ERRCODE(ErrModBsp, ErrGic, 3) /* 在设置过程中出现的异常 */
#define FGIC_CTLR_ERR_IN_GET    FT_MAKE_ERRCODE(ErrModBsp, ErrGic, 4) /* 在获取过程中出现的异常 */
#define FGIC_ERR_IN_TIMEOUT    FT_MAKE_ERRCODE(ErrModBsp, ErrGic, 5)  /* 超时退出 */


typedef enum
{
    TRIGGER_BY_LEVEL_SENSITIVE = 0,  /* Corresponding interrupt is level-sensitive. */
    TRIGGER_BY_LEVEL_EDGE,           /* Corresponding interrupt is edge-triggered. */
} TRIGGER_LEVEL;

typedef enum
{
    TWO_SECURITY_STATE = 0,          /*  */
    ONE_NS_SECURITY_STATE,           /*  */
} SECURITY_STATE;

/*  Interrupt Routing Mode. */
typedef enum
{
    SGI_ROUTING_TO_SPECIFIC = 0,        /* sgi interrupts routed to the PEs specified by affinity level. */
    SGI_ROUTING_TO_ANY = (1ULL << 40)   /* sgi interrupts routed to all PEs in the system, excluding "self". */
} SGI_ROUTING_MODE;

typedef enum
{
    SPI_ROUTING_TO_SPECIFIC = 0,  /* spi interrupts routed to the PE specified by affinity level. */
    SPI_ROUTING_TO_ANY = (1U << 31) /* spi interrupts routed to any PE defined as a participating node. */
} SPI_ROUTING_MODE;

typedef struct
{
    u32 instance_id; /* Id of device*/
    uintptr dis_base; /* Distributor base address      */

} FGicConfig;

typedef struct
{
    FGicConfig config; /* Configuration data structure  */
    u32 is_ready;       /* Device is ininitialized and ready*/
    uintptr redis_base; /* Redistributor base address for each core  */
    SECURITY_STATE security ;
    s32 max_spi_num;    /* Max value of spi priority */
} FGic;

/* Initialization */
FGicConfig *FGicLookupConfig(u32 instance_id);
FError FGicCfgInitialize(FGic *instance_p, const FGicConfig *input_config_p, uintptr redis_base);
void FGicDistrubutiorInit(FGic *instance_p);
FError FGicRedistrubutiorInit(FGic *instance_p);
void FGicCpuInterfaceInit(void);

/* Operation interface */
FError FGicIntEnable(FGic *instance_p, s32 int_id);
FError FGicIntDisable(FGic *instance_p, s32 int_id);
FError FGicSetPriority(FGic *instance_p, s32 int_id, u32 priority);
u32 FGicGetPriority(FGic *instance_p, s32 int_id);
FError FGicSetTriggerLevel(FGic *instance_p, s32 int_id, TRIGGER_LEVEL trigger_way);
u32 FGicGetTriggerLevel(FGic *instance_p, s32 int_id);
FError FGicSetSpiAffinityRouting(FGic *instance_p, s32 int_id, SPI_ROUTING_MODE route_mode, u64 affinity);
FError FGicGetAffinityRouting(FGic *instance_p, s32 int_id, SPI_ROUTING_MODE *route_mode_p, u64 *affinity_p);
FError FGicGenerateSgi(FGic *instance_p, s32 int_id, u32 target_list, SGI_ROUTING_MODE routing_mode, u64 affinity);
void FGicDeactionInterrupt(FGic *instance_p, s32 int_id);
s32 FGicAcknowledgeInt(FGic *instance_p);
void FGicSetPriorityFilter(FGic *instance_p, u32 priority_mask);
void FGicSetPriorityGroup(FGic *instance_p, u32 binary_point);
u32 FGicGetPriorityFilter(FGic *instance_p);
u32 FGicGetPriorityGroup(FGic *instance_p);

#ifdef __cplusplus
}
#endif

#endif
