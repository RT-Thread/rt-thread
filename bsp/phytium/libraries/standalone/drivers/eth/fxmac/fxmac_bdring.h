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
 * FilePath: fxmac_bdring.h
 * Date: 2022-04-06 14:46:52
 * LastEditTime: 2022-04-06 14:46:58
 * Description:  This file ontains DMA channel related structure and constant definition
 * as well as function prototypes.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/06/16    first release
 */

#ifndef FXMAC_BDRING_H
#define FXMAC_BDRING_H

#include "fxmac_bd.h"
#include "ftypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**************************** Type Definitions *******************************/

/** This is an internal structure used to maintain the DMA list */
typedef struct
{
    uintptr phys_base_addr; /* Physical address of 1st BD in list */
    uintptr base_bd_addr;   /* Virtual address of 1st BD in list */
    uintptr high_bd_addr;   /* Virtual address of last BD in the list */
    u32 length;             /* Total size of ring in bytes */
    u32 run_state;          /* Flag to indicate DMA is started */
    u32 separation;         /* Number of bytes between the starting address
                                  of adjacent BDs */
    FXmacBd *free_head;
    /* First BD in the free group */
    FXmacBd *pre_head; /* First BD in the pre-work group */
    FXmacBd *hw_head;  /* First BD in the work group */
    FXmacBd *hw_tail;  /* Last BD in the work group */
    FXmacBd *post_head;
    /* First BD in the post-work group */
    FXmacBd *bda_restart;
    /* BDA to load when channel is started */

    volatile u32 hw_cnt; /* Number of BDs in work group */
    u32 pre_cnt;         /* Number of BDs in pre-work group */
    u32 free_cnt;        /* Number of allocatable BDs in the free group */
    u32 post_cnt;        /* Number of BDs in post-work group */
    u32 all_cnt;         /* Total Number of BDs for channel */
} FXmacBdRing;

/**
 * @name: FXMAC_BD_RING_NEXT
 * @msg:  Return the next BD from bd_ptr in a list.
 *
 * @param  ring_ptr is the DMA channel to operate on.
 * @param  bd_ptr is the BD to operate on.
 * @return The next BD in the list relative to the bd_ptr parameter.
 */
#define FXMAC_BD_RING_NEXT(ring_ptr, bd_ptr) \
    (((uintptr)((void *)(bd_ptr)) >= (ring_ptr)->high_bd_addr) ? (FXmacBd *)((void *)(ring_ptr)->base_bd_addr) : (FXmacBd *)((uintptr)((void *)(bd_ptr)) + (ring_ptr)->separation))

/**
 * @name: FXMAC_BD_RING_CNT_CALC
 * @msg:  Use this macro at initialization time to determine how many BDs will fit
 * in a BD list within the given memory constraints.
 *
 * @param alignment specifies what byte alignment the BDs must fall on and
 *        must be a power of 2 to get an accurate calculation (32, 64, 128,...)
 * @param Bytes is the number of bytes to be used to store BDs.
 * @return Number of BDs that can fit in the given memory area
 */
#define FXMAC_BD_RING_CNT_CALC(alignment, Bytes) \
    (u32)((Bytes) / (sizeof(FXmacBd)))

/**
 * @name: FXMAC_BD_RING_MEM_CALC
 * @msg:  Use this macro at initialization time to determine how many bytes of memory
 * is required to contain a given number of BDs at a given alignment.
 * @param alignment specifies what byte alignment the BDs must fall on. This
 *        parameter must be a power of 2 to get an accurate calculation (32, 64,
 *        128,...)
 * @param num_bd is the number of BDs to calculate memory size requirements for
 * @return The number of bytes of memory required to create a BD list with the
 *         given memory constraints.
 */
#define FXMAC_BD_RING_MEM_CALC(alignment, num_bd) \
    (u32)(sizeof(FXmacBd) * (num_bd))

/**
 * @name: FXMAC_BD_RING_GET_CNT
 * @msg:  Return the total number of BDs allocated by this channel with
 * FXmacBdRingCreate().
 * @param  ring_ptr is the DMA channel to operate on.
 * @return The total number of BDs allocated for this channel.
 */
#define FXMAC_BD_RING_GET_CNT(ring_ptr) ((ring_ptr)->all_cnt)

/**
 * @name: FXMAC_BD_RING_GET_FREE_CNT
 * @msg:  Return the number of BDs allocatable with FXmacBdRingAlloc() for pre-
 * processing.
 *
 * @param  ring_ptr is the DMA channel to operate on.
 * @return The number of BDs currently allocatable.
 */
#define FXMAC_BD_RING_GET_FREE_CNT(ring_ptr) ((ring_ptr)->free_cnt)

/**
 * @name: FXMAC_BD_RING_PREV
 * @msg:  Return the previous BD from bd_ptr in the list.
 * @param  ring_ptr is the DMA channel to operate on.
 * @param  bd_ptr is the BD to operate on
 * @return The previous BD in the list relative to the bd_ptr parameter.
 */
#define FXMAC_BD_RING_PREV(ring_ptr, bd_ptr) \
    (((uintptr)(bd_ptr) <= (ring_ptr)->base_bd_addr) ? (FXmacBd *)(ring_ptr)->high_bd_addr : (FXmacBd *)((uintptr)(bd_ptr) - (ring_ptr)->separation))

/************************** Function Prototypes ******************************/

/*
 * Scatter gather DMA related functions in FXmacbdring.c
 */
FError FXmacBdRingCreate(FXmacBdRing *ring_ptr, uintptr phys_addr,
                         uintptr virt_addr, u32 alignment, u32 bd_count);
FError FXmacBdRingClone(FXmacBdRing *ring_ptr, FXmacBd *src_bd_ptr,
                        u8 direction);
FError FXmacBdRingAlloc(FXmacBdRing *ring_ptr, u32 num_bd,
                        FXmacBd **bd_set_ptr);
FError FXmacBdRingUnAlloc(FXmacBdRing *ring_ptr, u32 num_bd,
                          FXmacBd *bd_set_ptr);
FError FXmacBdRingToHw(FXmacBdRing *ring_ptr, u32 num_bd,
                       FXmacBd *bd_set_ptr);
FError FXmacBdRingFree(FXmacBdRing *ring_ptr, u32 num_bd,
                       FXmacBd *bd_set_ptr);
u32 FXmacBdRingFromHwTx(FXmacBdRing *ring_ptr, u32 bd_limit,
                        FXmacBd **bd_set_ptr);
u32 FXmacBdRingFromHwRx(FXmacBdRing *ring_ptr, u32 bd_limit,
                        FXmacBd **bd_set_ptr);
FError FXmacBdRingCheck(FXmacBdRing *ring_ptr, u8 direction);

void FXmacBdringPtrReset(FXmacBdRing *ring_ptr, void *virt_addrloc);

#ifdef __cplusplus
}
#endif

#endif