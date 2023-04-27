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
 * FilePath: fxmac_bdring.c
 * Date: 2022-04-06 14:46:52
 * LastEditTime: 2022-04-06 14:46:58
 * Description:  This file implements buffer descriptor ring related functions.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/06/16    first release
 */

#include "fxmac_hw.h"
#include "fxmac.h"
#include "fxmac_bdring.h"
#include "fxmac_bd.h"
#include "ftypes.h"
#include "fxmac.h"
#include "string.h"
#include "fprintk.h"
#include "fdebug.h"

static void FXmacBdSetRxWrap(uintptr bdptr);
static void FXmacBdSetTxWrap(uintptr bdptr);

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/**
 * @name: FXMAC_RING_SEEKAHEAD
 * @msg:  Move the bdptr argument ahead an arbitrary number of BDs wrapping around
 * to the beginning of the ring if needed.
 * @param ring_ptr is the ring bdptr appears in
 * @param bdptr on input is the starting BD position and on output is the final BD position
 * @param num_bd is the number of BD spaces to increment
 */
#define FXMAC_RING_SEEKAHEAD(ring_ptr, bdptr, num_bd)                               \
    {                                                                               \
        uintptr addr = (uintptr)(void *)(bdptr);                                    \
        \
        addr += ((ring_ptr)->separation * (num_bd));                                \
        if ((addr > (ring_ptr)->high_bd_addr) || ((uintptr)(void *)(bdptr) > addr)) \
        {                                                                           \
            addr -= (ring_ptr)->length;                                             \
        }                                                                           \
        \
        (bdptr) = (FXmacBd *)(void *)addr;                                          \
    }

/**
 * @name: FXMAC_RING_SEEKBACK
 * @msg:  Move the bdptr argument backwards an arbitrary number of BDs wrapping
 * around to the end of the ring if needed.
 * @param ring_ptr is the ring bdptr appears in
 * @param bdptr on input is the starting BD position and on output is the
 *        final BD position
 * @param num_bd is the number of BD spaces to increment
 * @return {*}
 */
#define FXMAC_RING_SEEKBACK(ring_ptr, bdptr, num_bd)                                \
    {                                                                               \
        uintptr addr = (uintptr)(void *)(bdptr);                                    \
        \
        addr -= ((ring_ptr)->separation * (num_bd));                                \
        if ((addr < (ring_ptr)->base_bd_addr) || ((uintptr)(void *)(bdptr) < addr)) \
        {                                                                           \
            addr += (ring_ptr)->length;                                             \
        }                                                                           \
        \
        (bdptr) = (FXmacBd *)(void *)addr;                                          \
    }



/**
 * @name: FXmacBdRingCreate
 * @msg:  Using a memory segment allocated by the caller, create and setup the BD list
 * for the given DMA channel.
 * @param ring_ptr is the instance to be worked on.
 * @param Physaddr is the physical base address of user memory region.
 * @param Virtaddr is the virtual base address of the user memory region. If
 *        address translation is not being utilized, then Virtaddr should be
 *        equivalent to Physaddr.
 * @param Alignment governs the byte alignment of individual BDs. This function
 *        will enforce a minimum alignment of 4 bytes with no maximum as long
 *        as it is specified as a power of 2.
 * @param bd_count is the number of BDs to setup in the user memory region. It
 *        is assumed the region is large enough to contain the BDs.
 * @return
 *        FT_SUCCESS if initialization was successful
 *        FXMAC_ERR_INVALID_PARAM under any of the following conditions:
 *          1) Physaddr and/or Virtaddr are not aligned to the given Alignment
 *              parameter.
 *          2) Alignment parameter does not meet minimum requirements or is not a
 *              power of 2 value.
 *          3) bd_count is 0.
 */
FError FXmacBdRingCreate(FXmacBdRing *ring_ptr, uintptr phys_addr,
                         uintptr virt_addr, u32 alignment, u32 bd_count)
{
    u32 i;
    uintptr bd_virt_addr;
    uintptr bd_phy_addr;
    uintptr virt_addr_loc = virt_addr;

    /* In case there is a failure prior to creating list, make sure the
     * following attributes are 0 to prevent calls to other functions
     * from doing anything.
     */
    ring_ptr->all_cnt = 0U;
    ring_ptr->free_cnt = 0U;
    ring_ptr->hw_cnt = 0U;
    ring_ptr->pre_cnt = 0U;
    ring_ptr->post_cnt = 0U;

    /* Make sure alignment parameter meets minimum requirements */
    if (alignment < (u32)FXMAC_DMABD_MINIMUM_ALIGNMENT)
    {
        return (FError)(FXMAC_ERR_INVALID_PARAM);
    }

    /* Make sure alignment is a power of 2 */
    if (((alignment - 0x00000001U) & alignment) != 0x00000000U)
    {
        return (FError)(FXMAC_ERR_INVALID_PARAM);
    }

    /* Make sure phys_addr and virt_addr are on same alignment */
    if (((phys_addr % alignment) != (u32)0) || ((virt_addr_loc % alignment) != (u32)0))
    {
        return (FError)(FXMAC_ERR_INVALID_PARAM);
    }

    /* Is bd_count reasonable? */
    if (bd_count == 0x00000000U)
    {
        return (FError)(FXMAC_ERR_INVALID_PARAM);
    }

    /* Figure out how many bytes will be between the start of adjacent BDs */
    ring_ptr->separation = ((u32)sizeof(FXmacBd));

    /* Must make sure the ring doesn't span address 0x00000000. If it does,
     * then the next/prev BD traversal macros will fail.
     */
    if (virt_addr_loc > ((virt_addr_loc + (ring_ptr->separation * bd_count)) - (u32)1))
    {
        return (FError)(FXMAC_ERR_SG_LIST);
    }

    /* Initial ring setup:
     *  - Clear the entire space
     *  - Setup each BD's BDA field with the physical address of the next BD
     */
    (void)memset((void *)virt_addr_loc, 0, (ring_ptr->separation * bd_count));

    bd_virt_addr = virt_addr_loc;
    bd_phy_addr = phys_addr + ring_ptr->separation;
    for (i = 1U; i < bd_count; i++)
    {
        bd_virt_addr += ring_ptr->separation;
        bd_phy_addr += ring_ptr->separation;
    }

    /* Setup and initialize pointers and counters */
    ring_ptr->run_state = (u32)(FXMAC_DMA_SG_IS_STOPED);
    ring_ptr->base_bd_addr = virt_addr_loc;
    ring_ptr->phys_base_addr = phys_addr;
    ring_ptr->high_bd_addr = bd_virt_addr;
    ring_ptr->length =
        ((ring_ptr->high_bd_addr - ring_ptr->base_bd_addr) + ring_ptr->separation);
    ring_ptr->all_cnt = (u32)bd_count;
    ring_ptr->free_cnt = (u32)bd_count;
    ring_ptr->free_head = (FXmacBd *)(void *)virt_addr_loc;
    ring_ptr->pre_head = (FXmacBd *)virt_addr_loc;
    ring_ptr->hw_head = (FXmacBd *)virt_addr_loc;
    ring_ptr->hw_tail = (FXmacBd *)virt_addr_loc;
    ring_ptr->post_head = (FXmacBd *)virt_addr_loc;
    ring_ptr->bda_restart = (FXmacBd *)(void *)phys_addr;

    return (FError)(FT_SUCCESS);
}

/**
 * @name: FXmacBdRingClone
 * @msg:  Clone the given BD into every BD in the list.
 * every field of the source BD is replicated in every BD of the list.
 * @param ring_ptr is the instance to be worked on.
 * @param src_bd_ptr is the source BD template to be cloned into the list. This
 *        BD will be modified.
 * @param direction is either FXMAC_SEND or FXMAC_RECV that indicates
 *        which direction.
 * @return {*}
 */
FError FXmacBdRingClone(FXmacBdRing *ring_ptr, FXmacBd *src_bd_ptr,
                        u8 direction)
{
    u32 i;
    uintptr cur_bd;

    /* Can't do this function if there isn't a ring */
    if (ring_ptr->all_cnt == 0x00000000U)
    {
        return (FError)(FXMAC_ERR_SG_NO_LIST);
    }

    /* Can't do this function with the channel running */
    if (ring_ptr->run_state == (u32)FXMAC_DMA_SG_IS_STARTED)
    {
        return (FError)(FT_COMPONENT_IS_STARTED);
    }

    /* Can't do this function with some of the BDs in use */
    if (ring_ptr->free_cnt != ring_ptr->all_cnt)
    {
        return (FError)(FXMAC_ERR_SG_LIST);
    }

    if ((direction != (u8)FXMAC_SEND) && (direction != (u8)FXMAC_RECV))
    {
        return (FError)(FXMAC_ERR_INVALID_PARAM);
    }

    /* Starting from the top of the ring, save bd.next, overwrite the entire
     * BD with the template, then restore bd.next
     */
    cur_bd = ring_ptr->base_bd_addr;
    for (i = 0U; i < ring_ptr->all_cnt; i++)
    {
        memcpy((void *)cur_bd, src_bd_ptr, sizeof(FXmacBd));
        cur_bd += ring_ptr->separation;
    }

    cur_bd -= ring_ptr->separation;

    if (direction == FXMAC_RECV)
    {
        FXmacBdSetRxWrap(cur_bd);
    }
    else
    {
        FXmacBdSetTxWrap(cur_bd);
    }

    return (FError)(FT_SUCCESS);
}


/**
 * @name: FXmacBdRingAlloc
 * @msg:  Reserve locations in the BD list. The set of returned BDs may be modified
 * in preparation for future DMA transaction(s). Once the BDs are ready to be
 * submitted to hardware, the user must call FXmacBdRingToHw() in the same
 * order which they were allocated here.
 * @param ring_ptr is a pointer to the BD ring instance to be worked on.
 * @param num_bd is the number of BDs to allocate
 * @param bd_set_ptr is an output parameter, it points to the first BD available
 *        for modification.
 * @return  FT_SUCCESS if the requested number of BDs was returned in the bd_set_ptr
 *     parameter.
 *   - FXMAC_ERR_GENERAL if there were not enough free BDs to satisfy the request.
 */
FError FXmacBdRingAlloc(FXmacBdRing *ring_ptr, u32 num_bd,
                        FXmacBd **bd_set_ptr)
{
    FError status;
    /* Enough free BDs available for the request? */
    if (ring_ptr->free_cnt < num_bd)
    {
        status = (FError)(FXMAC_ERR_GENERAL);
    }
    else
    {
        /* Set the return argument and move free_head forward */
        *bd_set_ptr = ring_ptr->free_head;
        FXMAC_RING_SEEKAHEAD(ring_ptr, ring_ptr->free_head, num_bd);
        ring_ptr->free_cnt -= num_bd;
        ring_ptr->pre_cnt += num_bd;
        status = (FError)(FT_SUCCESS);
    }
    return status;
}


/**
 * @name: FXmacBdRingUnAlloc
 * @msg:  * Fully or partially undo an FXmacBdRingAlloc() operation. Use this
 * function if all the BDs allocated by FXmacBdRingAlloc() could not be
 * transferred to hardware with FXmacBdRingToHw().
 *
 * This function helps out in situations when an unrelated error occurs after
 * BDs have been allocated but before they have been given to hardware.
 * An example of this type of error would be an OS running out of resources.
 *
 * This function is not the same as FXmacBdRingFree(). The Free function
 * returns BDs to the free list after they have been processed by hardware,
 * while UnAlloc returns them before being processed by hardware.
 *
 * There are two scenarios where this function can be used. Full UnAlloc or
 * Partial UnAlloc. A Full UnAlloc means all the BDs Alloc'd will be returned:
 *
 * <pre>
 *    status = FXmacBdRingAlloc(Myring_ptr, 10, &bdptr),
 *        ...
 *    if (Error)
 *    {
 *        status = FXmacBdRingUnAlloc(Myring_ptr, 10, &bdptr),
 *    }
 * </pre>
 *
 * A partial UnAlloc means some of the BDs Alloc'd will be returned:
 *
 * <pre>
 *    status = FXmacBdRingAlloc(Myring_ptr, 10, &bdptr),
 *    BdsLeft = 10,
 *    cur_bd_ptr = bdptr,
 *
 *    while (BdsLeft)
 *    {
 *       if (Error)
 *       {
 *          status = FXmacBdRingUnAlloc(Myring_ptr, BdsLeft, cur_bd_ptr),
 *       }
 *
 *       cur_bd_ptr = FXMAC_BD_RING_NEXT(Myring_ptr, cur_bd_ptr),
 *       BdsLeft--,
 *    }
 * </pre>
 *
 * A partial UnAlloc must include the last BD in the list that was Alloc'd.
 *
 * @param ring_ptr is a pointer to the instance to be worked on.
 * @param num_bd is the number of BDs to allocate
 * @param bd_set_ptr is an output parameter, it points to the first BD available
 *        for modification.
 *
 * @return
 *   - FT_SUCCESS if the BDs were unallocated.
 *   - FXMAC_ERR_GENERAL if num_bd parameter was greater that the number of BDs in
 *     the preprocessing state.
 *
 * @return {*}
 */
FError FXmacBdRingUnAlloc(FXmacBdRing *ring_ptr, u32 num_bd,
                          FXmacBd *bd_set_ptr)
{
    FError status;
    (void)bd_set_ptr;
    FASSERT(ring_ptr != NULL);
    FASSERT(bd_set_ptr != NULL);

    /* Enough BDs in the free state for the request? */
    if (ring_ptr->pre_cnt < num_bd)
    {
        status = (FError)(FXMAC_ERR_GENERAL);
    }
    else
    {
        /* Set the return argument and move free_head backward */
        FXMAC_RING_SEEKBACK(ring_ptr, (ring_ptr->free_head), num_bd);
        ring_ptr->free_cnt += num_bd;
        ring_ptr->pre_cnt -= num_bd;
        status = (FError)(FT_SUCCESS);
    }
    return status;
}


/**
 * @name: FXmacBdRingToHw
 * @msg:  Enqueue a set of BDs to hardware that were previously allocated by
 * FXmacBdRingAlloc(). Once this function returns, the argument BD set goes
 * under hardware control. Any changes made to these BDs after this point will
 * corrupt the BD list leading to data corruption and system instability.
 *
 * @param ring_ptr is a pointer to the instance to be worked on.
 * @param num_bd is the number of BDs in the set.
 * @param bd_set_ptr is the first BD of the set to commit to hardware.
 * @return  FT_SUCCESS if the set of BDs was accepted and enqueued to hardware.
 *   XST_FAILURE if the set of BDs was rejected because the last BD of the set
 *     did not have its "last" bit set.
 *   FXMAC_ERR_SG_LIST if this function was called out of sequence with
 *     FXmacBdRingAlloc().
 */
FError FXmacBdRingToHw(FXmacBdRing *ring_ptr, u32 num_bd,
                       FXmacBd *bd_set_ptr)
{
    FXmacBd *cur_bd_ptr;
    u32 i;
    FError status;
    /* if no bds to process, simply return. */
    if (0U == num_bd)
    {
        status = (FError)(FT_SUCCESS);
    }
    else
    {
        /* Make sure we are in sync with FXmacBdRingAlloc() */
        if ((ring_ptr->pre_cnt < num_bd) || (ring_ptr->pre_head != bd_set_ptr))
        {
            status = (FError)(FXMAC_ERR_SG_LIST);
        }
        else
        {
            cur_bd_ptr = bd_set_ptr;
            for (i = 0U; i < num_bd; i++)
            {
                cur_bd_ptr = (FXmacBd *)((void *)FXMAC_BD_RING_NEXT(ring_ptr, cur_bd_ptr));
            }
            /* Adjust ring pointers & counters */
            FXMAC_RING_SEEKAHEAD(ring_ptr, ring_ptr->pre_head, num_bd);
            ring_ptr->pre_cnt -= num_bd;
            ring_ptr->hw_tail = cur_bd_ptr;
            ring_ptr->hw_cnt += num_bd;

            status = (FError)(FT_SUCCESS);
        }
    }
    return status;
}


/**
 * @name: FXmacBdRingFromHwTx
 * @msg:  Returns a set of BD(s) that have been processed by hardware. The returned
 * BDs may be examined to determine the outcome of the DMA transaction(s).
 * Once the BDs have been examined, the user must call FXmacBdRingFree()
 * in the same order which they were retrieved here. Example:
 *
 * <pre>
 *        num_bd = FXmacBdRingFromHwTx(Myring_ptr, MaxBd, &MyBdSet),
 *        if (num_bd == 0)
 *        {
 *           * hardware has nothing ready for us yet*
 *        }
 *
 *        cur_bd = MyBdSet,
 *        for (i=0; i<num_bd; i++)
 *        {
 *           * Examine cur_bd for post processing *.....
 *
 *           * Onto next BD *
 *           cur_bd = FXMAC_BD_RING_NEXT(Myring_ptr, cur_bd),
 *           }
 *
 *           FXmacBdRingFree(Myring_ptr, num_bd, MyBdSet),  *Return list*
 *        }
 * </pre>
 *
 * A more advanced use of this function may allocate multiple sets of BDs.
 * They must be retrieved from hardware and freed in the correct sequence:
 * <pre>
 *        * Legal *
 *        FXmacBdRingFromHwTx(Myring_ptr, num_bd1, &MySet1),
 *        FXmacBdRingFree(Myring_ptr, num_bd1, MySet1),
 *
 *        * Legal *
 *        FXmacBdRingFromHwTx(Myring_ptr, num_bd1, &MySet1),
 *        FXmacBdRingFromHwTx(Myring_ptr, num_bd2, &MySet2),
 *        FXmacBdRingFree(Myring_ptr, num_bd1, MySet1),
 *        FXmacBdRingFree(Myring_ptr, num_bd2, MySet2),
 *
 *        * Not legal *
 *        FXmacBdRingFromHwTx(Myring_ptr, num_bd1, &MySet1),
 *        FXmacBdRingFromHwTx(Myring_ptr, num_bd2, &MySet2),
 *        FXmacBdRingFree(Myring_ptr, num_bd2, MySet2),
 *        FXmacBdRingFree(Myring_ptr, num_bd1, MySet1),
 * </pre>
 *
 * If hardware has only partially completed a packet spanning multiple BDs,
 * then none of the BDs for that packet will be included in the results.
 *
 * @param ring_ptr is a pointer to the instance to be worked on.
 * @param bd_limit is the maximum number of BDs to return in the set.
 * @param bd_set_ptr is an output parameter, it points to the first BD available
 *        for examination.
 *
* @return
 *   The number of BDs processed by hardware. A value of 0 indicates that no
 *   data is available. No more than bd_limit BDs will be returned.
 *
 * @return
 *   The number of BDs processed by hardware. A value of 0 indicates that no
 *   data is available. No more than bd_limit BDs will be returned.
 */
u32 FXmacBdRingFromHwTx(FXmacBdRing *ring_ptr, u32 bd_limit,
                        FXmacBd **bd_set_ptr)
{
    FXmacBd *cur_bd_ptr;
    u32 bd_str = 0U;
    u32 bd_count;
    u32 bd_partial_count;
    u32 Sop = 0U;
    u32 status;
    u32 bd_limitLoc = bd_limit;
    cur_bd_ptr = ring_ptr->hw_head;
    bd_count = 0U;
    bd_partial_count = 0U;

    /* If no BDs in work group, then there's nothing to search */
    if (ring_ptr->hw_cnt == 0x00000000U)
    {
        *bd_set_ptr = NULL;
        status = 0U;
    }
    else
    {

        if (bd_limitLoc > ring_ptr->hw_cnt)
        {
            bd_limitLoc = ring_ptr->hw_cnt;
        }
        /* Starting at hw_head, keep moving forward in the list until:
         *  - A BD is encountered with its new/used bit set which means
         *    hardware has not completed processing of that BD.
         *  - ring_ptr->hw_tail is reached and ring_ptr->hw_cnt is reached.
         *  - The number of requested BDs has been processed
         */
        while (bd_count < bd_limitLoc)
        {
            /* Read the status */
            if (cur_bd_ptr != NULL)
            {
                bd_str = FXMAC_BD_READ(cur_bd_ptr, FXMAC_BD_STAT_OFFSET);
            }

            if ((Sop == 0x00000000U) && ((bd_str & FXMAC_TXBUF_USED_MASK) != 0x00000000U))
            {
                Sop = 1U;
            }
            if (Sop == 0x00000001U)
            {
                bd_count++;
                bd_partial_count++;
            }

            /* hardware has processed this BD so check the "last" bit.
             * If it is clear, then there are more BDs for the current
             * packet. Keep a count of these partial packet BDs.
             */
            if ((Sop == 0x00000001U) && ((bd_str & FXMAC_TXBUF_LAST_MASK) != 0x00000000U))
            {
                Sop = 0U;
                bd_partial_count = 0U;
            }

            /* Move on to next BD in work group */
            cur_bd_ptr = FXMAC_BD_RING_NEXT(ring_ptr, cur_bd_ptr);
        }

        /* Subtract off any partial packet BDs found */
        bd_count -= bd_partial_count;

        /* If bd_count is non-zero then BDs were found to return. Set return
         * parameters, update pointers and counters, return success
         */
        if (bd_count > 0x00000000U)
        {
            *bd_set_ptr = ring_ptr->hw_head;
            ring_ptr->hw_cnt -= bd_count;
            ring_ptr->post_cnt += bd_count;
            FXMAC_RING_SEEKAHEAD(ring_ptr, ring_ptr->hw_head, bd_count);
            status = (bd_count);
        }
        else
        {
            *bd_set_ptr = NULL;
            status = 0U;
        }
    }
    return status;
}

/**
 * @name: FXmacBdRingFromHwRx
 * @msg:  Returns a set of BD(s) that have been processed by hardware. The returned
 * BDs may be examined to determine the outcome of the DMA transaction(s).
 * Once the BDs have been examined, the user must call FXmacBdRingFree()
 * in the same order which they were retrieved here. Example:
 *
 * <pre>
 *        num_bd = FXmacBdRingFromHwRx(Myring_ptr, MaxBd, &MyBdSet),
 *
 *        if (num_bd == 0)
 *        {
 *           *hardware has nothing ready for us yet*
 *        }
 *
 *        cur_bd = MyBdSet,
 *        for (i=0; i<num_bd; i++)
 *        {
 *           * Examine cur_bd for post processing *.....
 *
 *           * Onto next BD *
 *           cur_bd = FXMAC_BD_RING_NEXT(Myring_ptr, cur_bd),
 *           }
 *
 *           FXmacBdRingFree(Myring_ptr, num_bd, MyBdSet),  * Return list *
 *        }
 * </pre>
 *
 * A more advanced use of this function may allocate multiple sets of BDs.
 * They must be retrieved from hardware and freed in the correct sequence:
 * <pre>
 *        * Legal *
 *        FXmacBdRingFromHwRx(Myring_ptr, num_bd1, &MySet1),
 *        FXmacBdRingFree(Myring_ptr, num_bd1, MySet1),
 *
 *        * Legal *
 *        FXmacBdRingFromHwRx(Myring_ptr, num_bd1, &MySet1),
 *        FXmacBdRingFromHwRx(Myring_ptr, num_bd2, &MySet2),
 *        FXmacBdRingFree(Myring_ptr, num_bd1, MySet1),
 *        FXmacBdRingFree(Myring_ptr, num_bd2, MySet2),
 *
 *        * Not legal *
 *        FXmacBdRingFromHwRx(Myring_ptr, num_bd1, &MySet1),
 *        FXmacBdRingFromHwRx(Myring_ptr, num_bd2, &MySet2),
 *        FXmacBdRingFree(Myring_ptr, num_bd2, MySet2),
 *        FXmacBdRingFree(Myring_ptr, num_bd1, MySet1),
 * </pre>
 *
 * If hardware has only partially completed a packet spanning multiple BDs,
 * then none of the BDs for that packet will be included in the results.
 *
 * @param ring_ptr is a pointer to the instance to be worked on.
 * @param bd_limit is the maximum number of BDs to return in the set.
 * @param bd_set_ptr is an output parameter, it points to the first BD available
 *        for examination.
 *
 * @return
 *   The number of BDs processed by hardware. A value of 0 indicates that no
 *   data is available. No more than bd_limit BDs will be returned.
 */
u32 FXmacBdRingFromHwRx(FXmacBdRing *ring_ptr, u32 bd_limit,
                        FXmacBd **bd_set_ptr)
{
    FXmacBd *cur_bd_ptr;
    u32 bd_str = 0U;
    u32 bd_count;
    u32 bd_partial_count;
    u32 status;

    cur_bd_ptr = ring_ptr->hw_head;
    bd_count = 0U;
    bd_partial_count = 0U;

    /* If no BDs in work group, then there's nothing to search */
    if (ring_ptr->hw_cnt == 0x00000000U)
    {
        *bd_set_ptr = NULL;
        status = 0U;
    }
    else
    {
        /* Starting at hw_head, keep moving forward in the list until:
         *  - A BD is encountered with its new/used bit set which means
         *    hardware has completed processing of that BD.
         *  - ring_ptr->hw_tail is reached and ring_ptr->hw_cnt is reached.
         *  - The number of requested BDs has been processed
         */
        while (bd_count < bd_limit)
        {

            /* Read the status */
            if (cur_bd_ptr != NULL)
            {
                bd_str = FXMAC_BD_READ(cur_bd_ptr, FXMAC_BD_STAT_OFFSET);
            }
            if ((!(FXMAC_BD_IS_RX_NEW(cur_bd_ptr))) == TRUE)
            {
                break;
            }

            bd_count++;

            /* hardware has processed this BD so check the "last" bit. If
             * it is clear, then there are more BDs for the current packet.
             * Keep a count of these partial packet BDs.
             */
            if ((bd_str & FXMAC_RXBUF_EOF_MASK) != 0x00000000U)
            {
                bd_partial_count = 0U;
            }
            else
            {
                bd_partial_count++;
            }

            /* Move on to next BD in work group */
            cur_bd_ptr = FXMAC_BD_RING_NEXT(ring_ptr, cur_bd_ptr);

        }

        /* Subtract off any partial packet BDs found */
        bd_count -= bd_partial_count;

        /* If bd_count is non-zero then BDs were found to return. Set return
         * parameters, update pointers and counters, return success
         */
        if (bd_count > 0x00000000U)
        {
            *bd_set_ptr = ring_ptr->hw_head;
            ring_ptr->hw_cnt -= bd_count;
            ring_ptr->post_cnt += bd_count;
            FXMAC_RING_SEEKAHEAD(ring_ptr, ring_ptr->hw_head, bd_count);
            status = (bd_count);
        }
        else
        {
            *bd_set_ptr = NULL;
            status = 0U;
        }
    }
    return status;
}

/**
 * @name: FXmacBdRingFree
 * @msg:  Frees a set of BDs that had been previously retrieved with
 * FXmacBdRingFromHw().
 *
 * @param ring_ptr is a pointer to the instance to be worked on.
 * @param num_bd is the number of BDs to free.
 * @param bd_set_ptr is the head of a list of BDs returned by
 * FXmacBdRingFromHw().
 *
 * @return
 *     FT_SUCCESS if the set of BDs was freed.
 *     FXMAC_ERR_SG_LIST if this function was called out of sequence with
 *     FXmacBdRingFromHw().
 */
FError FXmacBdRingFree(FXmacBdRing *ring_ptr, u32 num_bd,
                       FXmacBd *bd_set_ptr)
{
    FError status;
    /* if no bds to process, simply return. */
    if (0x00000000U == num_bd)
    {
        status = (FError)(FT_SUCCESS);
    }
    else
    {
        /* Make sure we are in sync with FXmacBdRingFromHw() */
        if ((ring_ptr->post_cnt < num_bd) || (ring_ptr->post_head != bd_set_ptr))
        {
            status = (FError)(FXMAC_ERR_SG_LIST);
        }
        else
        {
            /* Update pointers and counters */
            ring_ptr->free_cnt += num_bd;
            ring_ptr->post_cnt -= num_bd;
            FXMAC_RING_SEEKAHEAD(ring_ptr, ring_ptr->post_head, num_bd);
            status = (FError)(FT_SUCCESS);
        }
    }
    return status;
}

/**
 * @name: FXmacBdRingCheck
 * @msg:  Check the internal data structures of the BD ring for the provided channel.
 * The following checks are made:
 *
 *   - Is the BD ring linked correctly in physical address space.
 *   - Do the internal pointers point to BDs in the ring.
 *   - Do the internal counters add up.
 *
 * The channel should be stopped prior to calling this function.
 *
 * @param {FXmacBdRing} ring_ptr is a pointer to the instance to be worked on.
 * @param {u8} direction is either FXMAC_SEND or FXMAC_RECV that indicates
 *        which direction.
 * @return {*}
 *     FT_SUCCESS if the set of BDs was freed.
 *     XST_DMA_SG_NO_LIST if the list has not been created.
 *     FT_COMPONENT_IS_STARTED if the channel is not stopped.
 *     FXMAC_ERR_SG_LIST if a problem is found with the internal data
 *     structures. If this value is returned, the channel should be reset to
 *     avoid data corruption or system instability.
 */
FError FXmacBdRingCheck(FXmacBdRing *ring_ptr, u8 direction)
{
    uintptr addr_v, addr_p;
    u32 i;

    if ((direction != (u8)FXMAC_SEND) && (direction != (u8)FXMAC_RECV))
    {
        return (FError)(FXMAC_ERR_INVALID_PARAM);
    }

    /* Is the list created */
    if (ring_ptr->all_cnt == 0x00000000U)
    {
        return (FError)(FXMAC_ERR_SG_NO_LIST);
    }

    /* Can't check if channel is running */
    if (ring_ptr->run_state == (u32)FXMAC_DMA_SG_IS_STARTED)
    {
        return (FError)(FT_COMPONENT_IS_STARTED);
    }

    /* run_state doesn't make sense */
    if (ring_ptr->run_state != (u32)FXMAC_DMA_SG_IS_STOPED)
    {
        return (FError)(FXMAC_ERR_SG_LIST);
    }

    /* Verify internal pointers point to correct memory space */
    addr_v = (uintptr)ring_ptr->free_head;
    if ((addr_v < ring_ptr->base_bd_addr) || (addr_v > ring_ptr->high_bd_addr))
    {
        return (FError)(FXMAC_ERR_SG_LIST);
    }

    addr_v = (uintptr)ring_ptr->pre_head;
    if ((addr_v < ring_ptr->base_bd_addr) || (addr_v > ring_ptr->high_bd_addr))
    {
        return (FError)(FXMAC_ERR_SG_LIST);
    }

    addr_v = (uintptr)ring_ptr->hw_head;
    if ((addr_v < ring_ptr->base_bd_addr) || (addr_v > ring_ptr->high_bd_addr))
    {
        return (FError)(FXMAC_ERR_SG_LIST);
    }

    addr_v = (uintptr)ring_ptr->hw_tail;
    if ((addr_v < ring_ptr->base_bd_addr) || (addr_v > ring_ptr->high_bd_addr))
    {
        return (FError)(FXMAC_ERR_SG_LIST);
    }

    addr_v = (uintptr)ring_ptr->post_head;
    if ((addr_v < ring_ptr->base_bd_addr) || (addr_v > ring_ptr->high_bd_addr))
    {
        return (FError)(FXMAC_ERR_SG_LIST);
    }

    /* Verify internal counters add up */
    if ((ring_ptr->hw_cnt + ring_ptr->pre_cnt + ring_ptr->free_cnt +
         ring_ptr->post_cnt) != ring_ptr->all_cnt)
    {
        return (FError)(FXMAC_ERR_SG_LIST);
    }

    /* Verify BDs are linked correctly */
    addr_v = ring_ptr->base_bd_addr;
    addr_p = ring_ptr->phys_base_addr + ring_ptr->separation;

    for (i = 1U; i < ring_ptr->all_cnt; i++)
    {
        /* Check BDA for this BD. It should point to next physical addr */
        if (FXMAC_BD_READ(addr_v, FXMAC_BD_ADDR_OFFSET) != addr_p)
        {
            return (FError)(FXMAC_ERR_SG_LIST);
        }

        /* Move on to next BD */
        addr_v += ring_ptr->separation;
        addr_p += ring_ptr->separation;
    }

    /* Last BD should have wrap bit set */
    if (FXMAC_SEND == direction)
    {
        if ((!FXMAC_BD_IS_TX_WRAP(addr_v)) == TRUE)
        {
            return (FError)(FXMAC_ERR_SG_LIST);
        }
    }
    else
    {
        /* FXMAC_RECV */
        if ((!FXMAC_BD_IS_RX_WRAP(addr_v)) == TRUE)
        {
            return (FError)(FXMAC_ERR_SG_LIST);
        }
    }

    /* No problems found */
    return (FError)(FT_SUCCESS);
}


/**
 * @name: FXmacBdSetRxWrap
 * @msg:  Set this bit to mark the last descriptor in the receive buffer descriptor
 * list.
 * @param {uintptr} bdptr is the BD pointer to operate on
 */
static void FXmacBdSetRxWrap(uintptr bdptr)
{
    u32 data_value_rx;
    u32 *temp_ptr;

    bdptr += (u32)(FXMAC_BD_ADDR_OFFSET);
    temp_ptr = (u32 *)bdptr;
    if (temp_ptr != NULL)
    {
        data_value_rx = *temp_ptr;
        data_value_rx |= FXMAC_RXBUF_WRAP_MASK;
        *temp_ptr = data_value_rx;
    }
}

/**
 * @name: FXmacBdSetTxWrap
 * @msg:  Sets this bit to mark the last descriptor in the transmit buffer
 * descriptor list.
 * @param {uintptr} bdptr is the BD pointer to operate on
 */
static void FXmacBdSetTxWrap(uintptr bdptr)
{
    u32 data_value_tx;
    u32 *temp_ptr;

    bdptr += (u32)(FXMAC_BD_STAT_OFFSET);
    temp_ptr = (u32 *)bdptr;
    if (temp_ptr != NULL)
    {
        data_value_tx = *temp_ptr;
        data_value_tx |= FXMAC_TXBUF_WRAP_MASK;
        *temp_ptr = data_value_tx;
    }
}


/**
 * @name: FXmacBdringPtrReset
 * @msg:  Reset BD ring head and tail pointers.
 * @return {*}
 * @param {FXmacBdRing} *ring_ptr is the instance to be worked on.
 * @param {void} *virtaddrloc is the virtual base address of the user memory region.
 */
void FXmacBdringPtrReset(FXmacBdRing *ring_ptr, void *virtaddrloc)
{
    ring_ptr->free_head = virtaddrloc;
    ring_ptr->pre_head = virtaddrloc;
    ring_ptr->hw_head = virtaddrloc;
    ring_ptr->hw_tail = virtaddrloc;
    ring_ptr->post_head = virtaddrloc;
}
