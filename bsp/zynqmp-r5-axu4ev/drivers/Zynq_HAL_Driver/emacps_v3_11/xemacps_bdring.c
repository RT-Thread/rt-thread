/******************************************************************************
* Copyright (C) 2010 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xemacps_bdring.c
* @addtogroup emacps_v3_11
* @{
*
* This file implements buffer descriptor ring related functions.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a wsy  01/10/10 First release
* 1.00a asa  11/21/11 The function XEmacPs_BdRingFromHwTx is modified.
*		      Earlier it used to search in "BdLimit" number of BDs to
*		      know which BDs are processed. Now one more check is
*		      added. It looks for BDs till the current BD pointer
*		      reaches HwTail. By doing this processing time is saved.
* 1.00a asa  01/24/12 The function XEmacPs_BdRingFromHwTx in file
*		      xemacps_bdring.c is modified. Now start of packet is
*		      searched for returning the number of BDs processed.
* 1.05a asa  09/23/13 Cache operations on BDs are not required and hence
*		      removed. It is expected that all BDs are allocated in
*		      from uncached area. Fix for CR #663885.
* 2.1   srt  07/15/14 Add support for Zynq Ultrascale Mp architecture.
* 3.0   kvn  02/13/15 Modified code for MISRA-C:2012 compliance.
* 3.6   rb   09/08/17 Add XEmacPs_BdRingPtrReset() API to reset BD ring
* 		      pointers
*
* </pre>
******************************************************************************/

/***************************** Include Files *********************************/

#include "xstatus.h"
#include "xil_cache.h"
#include "xemacps_hw.h"
#include "xemacps_bd.h"
#include "xemacps_bdring.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/

/****************************************************************************
 * Compute the virtual address of a descriptor from its physical address
 *
 * @param BdPtr is the physical address of the BD
 *
 * @returns Virtual address of BdPtr
 *
 * @note Assume BdPtr is always a valid BD in the ring
 ****************************************************************************/
#define XEMACPS_PHYS_TO_VIRT(BdPtr) \
    ((UINTPTR)(BdPtr) + (RingPtr->BaseBdAddr - RingPtr->PhysBaseAddr))

/****************************************************************************
 * Compute the physical address of a descriptor from its virtual address
 *
 * @param BdPtr is the physical address of the BD
 *
 * @returns Physical address of BdPtr
 *
 * @note Assume BdPtr is always a valid BD in the ring
 ****************************************************************************/
#define XEMACPS_VIRT_TO_PHYS(BdPtr) \
    ((UINTPTR)(BdPtr) - (RingPtr->BaseBdAddr - RingPtr->PhysBaseAddr))

/****************************************************************************
 * Move the BdPtr argument ahead an arbitrary number of BDs wrapping around
 * to the beginning of the ring if needed.
 *
 * We know if a wrapaound should occur if the new BdPtr is greater than
 * the high address in the ring OR if the new BdPtr crosses over the
 * 0xFFFFFFFF to 0 boundary. The latter test is a valid one since we do not
 * allow a BD space to span this boundary.
 *
 * @param RingPtr is the ring BdPtr appears in
 * @param BdPtr on input is the starting BD position and on output is the
 *        final BD position
 * @param NumBd is the number of BD spaces to increment
 *
 ****************************************************************************/
#define XEMACPS_RING_SEEKAHEAD(RingPtr, BdPtr, NumBd)                  \
    {                                                                   \
        UINTPTR Addr = (UINTPTR)(void *)(BdPtr);                        \
                                                                        \
        Addr += ((RingPtr)->Separation * (NumBd));                        \
        if ((Addr > (RingPtr)->HighBdAddr) || ((UINTPTR)(void *)(BdPtr) > Addr))  \
        {                                                               \
            Addr -= (RingPtr)->Length;                                  \
        }                                                               \
                                                                        \
        (BdPtr) = (XEmacPs_Bd*)(void *)Addr;                                     \
    }

/****************************************************************************
 * Move the BdPtr argument backwards an arbitrary number of BDs wrapping
 * around to the end of the ring if needed.
 *
 * We know if a wrapaound should occur if the new BdPtr is less than
 * the base address in the ring OR if the new BdPtr crosses over the
 * 0xFFFFFFFF to 0 boundary. The latter test is a valid one since we do not
 * allow a BD space to span this boundary.
 *
 * @param RingPtr is the ring BdPtr appears in
 * @param BdPtr on input is the starting BD position and on output is the
 *        final BD position
 * @param NumBd is the number of BD spaces to increment
 *
 ****************************************************************************/
#define XEMACPS_RING_SEEKBACK(RingPtr, BdPtr, NumBd)                   \
    {                                                                   \
        UINTPTR Addr = (UINTPTR)(void *)(BdPtr);                                  \
                                                                        \
        Addr -= ((RingPtr)->Separation * (NumBd));                        \
        if ((Addr < (RingPtr)->BaseBdAddr) || ((UINTPTR)(void*)(BdPtr) < Addr))  \
        {                                                               \
            Addr += (RingPtr)->Length;                                  \
        }                                                               \
                                                                        \
        (BdPtr) = (XEmacPs_Bd*)(void*)Addr;                                     \
    }


/************************** Function Prototypes ******************************/

static void XEmacPs_BdSetRxWrap(UINTPTR BdPtr);
static void XEmacPs_BdSetTxWrap(UINTPTR BdPtr);

/************************** Variable Definitions *****************************/

/*****************************************************************************/
/**
 * Using a memory segment allocated by the caller, create and setup the BD list
 * for the given DMA channel.
 *
 * @param RingPtr is the instance to be worked on.
 * @param PhysAddr is the physical base address of user memory region.
 * @param VirtAddr is the virtual base address of the user memory region. If
 *        address translation is not being utilized, then VirtAddr should be
 *        equivalent to PhysAddr.
 * @param Alignment governs the byte alignment of individual BDs. This function
 *        will enforce a minimum alignment of 4 bytes with no maximum as long
 *        as it is specified as a power of 2.
 * @param BdCount is the number of BDs to setup in the user memory region. It
 *        is assumed the region is large enough to contain the BDs.
 *
 * @return
 *
 * - XST_SUCCESS if initialization was successful
 * - XST_NO_FEATURE if the provided instance is a non DMA type
 *   channel.
 * - XST_INVALID_PARAM under any of the following conditions:
 *   1) PhysAddr and/or VirtAddr are not aligned to the given Alignment
 *      parameter.
 *   2) Alignment parameter does not meet minimum requirements or is not a
 *      power of 2 value.
 *   3) BdCount is 0.
 * - XST_DMA_SG_LIST_ERROR if the memory segment containing the list spans
 *   over address 0x00000000 in virtual address space.
 *
 * @note
 * Make sure to pass in the right alignment value.
 *****************************************************************************/
LONG XEmacPs_BdRingCreate(XEmacPs_BdRing * RingPtr, UINTPTR PhysAddr,
			  UINTPTR VirtAddr, u32 Alignment, u32 BdCount)
{
	u32 i;
	UINTPTR BdVirtAddr;
	UINTPTR BdPhyAddr;
	UINTPTR VirtAddrLoc = VirtAddr;

	/* In case there is a failure prior to creating list, make sure the
	 * following attributes are 0 to prevent calls to other functions
	 * from doing anything.
	 */
	RingPtr->AllCnt = 0U;
	RingPtr->FreeCnt = 0U;
	RingPtr->HwCnt = 0U;
	RingPtr->PreCnt = 0U;
	RingPtr->PostCnt = 0U;

	/* Make sure Alignment parameter meets minimum requirements */
	if (Alignment < (u32)XEMACPS_DMABD_MINIMUM_ALIGNMENT) {
		return (LONG)(XST_INVALID_PARAM);
	}

	/* Make sure Alignment is a power of 2 */
	if (((Alignment - 0x00000001U) & Alignment)!=0x00000000U) {
		return (LONG)(XST_INVALID_PARAM);
	}

	/* Make sure PhysAddr and VirtAddr are on same Alignment */
	if (((PhysAddr % Alignment)!=(u32)0) || ((VirtAddrLoc % Alignment)!=(u32)0)) {
		return (LONG)(XST_INVALID_PARAM);
	}

	/* Is BdCount reasonable? */
	if (BdCount == 0x00000000U) {
		return (LONG)(XST_INVALID_PARAM);
	}

	/* Figure out how many bytes will be between the start of adjacent BDs */
	RingPtr->Separation = ((u32)sizeof(XEmacPs_Bd));

	/* Must make sure the ring doesn't span address 0x00000000. If it does,
	 * then the next/prev BD traversal macros will fail.
	 */
	if (VirtAddrLoc > ((VirtAddrLoc + (RingPtr->Separation * BdCount)) - (u32)1)) {
		return (LONG)(XST_DMA_SG_LIST_ERROR);
	}

	/* Initial ring setup:
	 *  - Clear the entire space
	 *  - Setup each BD's BDA field with the physical address of the next BD
	 */
	(void)memset((void *) VirtAddrLoc, 0, (RingPtr->Separation * BdCount));

	BdVirtAddr = VirtAddrLoc;
	BdPhyAddr = PhysAddr + RingPtr->Separation;
	for (i = 1U; i < BdCount; i++) {
		BdVirtAddr += RingPtr->Separation;
		BdPhyAddr += RingPtr->Separation;
	}

	/* Setup and initialize pointers and counters */
	RingPtr->RunState = (u32)(XST_DMA_SG_IS_STOPPED);
	RingPtr->BaseBdAddr = VirtAddrLoc;
	RingPtr->PhysBaseAddr = PhysAddr;
	RingPtr->HighBdAddr = BdVirtAddr;
	RingPtr->Length =
		((RingPtr->HighBdAddr - RingPtr->BaseBdAddr) + RingPtr->Separation);
	RingPtr->AllCnt = (u32)BdCount;
	RingPtr->FreeCnt = (u32)BdCount;
	RingPtr->FreeHead = (XEmacPs_Bd *)(void *)VirtAddrLoc;
	RingPtr->PreHead = (XEmacPs_Bd *)VirtAddrLoc;
	RingPtr->HwHead = (XEmacPs_Bd *)VirtAddrLoc;
	RingPtr->HwTail = (XEmacPs_Bd *)VirtAddrLoc;
	RingPtr->PostHead = (XEmacPs_Bd *)VirtAddrLoc;
	RingPtr->BdaRestart = (XEmacPs_Bd *)(void *)PhysAddr;

	return (LONG)(XST_SUCCESS);
}


/*****************************************************************************/
/**
 * Clone the given BD into every BD in the list.
 * every field of the source BD is replicated in every BD of the list.
 *
 * This function can be called only when all BDs are in the free group such as
 * they are immediately after initialization with XEmacPs_BdRingCreate().
 * This prevents modification of BDs while they are in use by hardware or the
 * user.
 *
 * @param RingPtr is the pointer of BD ring instance to be worked on.
 * @param SrcBdPtr is the source BD template to be cloned into the list. This
 *        BD will be modified.
 * @param Direction is either XEMACPS_SEND or XEMACPS_RECV that indicates
 *        which direction.
 *
 * @return
 *   - XST_SUCCESS if the list was modified.
 *   - XST_DMA_SG_NO_LIST if a list has not been created.
 *   - XST_DMA_SG_LIST_ERROR if some of the BDs in this channel are under
 *     hardware or user control.
 *   - XST_DEVICE_IS_STARTED if the DMA channel has not been stopped.
 *
 *****************************************************************************/
LONG XEmacPs_BdRingClone(XEmacPs_BdRing * RingPtr, XEmacPs_Bd * SrcBdPtr,
			 u8 Direction)
{
	u32 i;
	UINTPTR CurBd;

	/* Can't do this function if there isn't a ring */
	if (RingPtr->AllCnt == 0x00000000U) {
		return (LONG)(XST_DMA_SG_NO_LIST);
	}

	/* Can't do this function with the channel running */
	if (RingPtr->RunState == (u32)XST_DMA_SG_IS_STARTED) {
		return (LONG)(XST_DEVICE_IS_STARTED);
	}

	/* Can't do this function with some of the BDs in use */
	if (RingPtr->FreeCnt != RingPtr->AllCnt) {
		return (LONG)(XST_DMA_SG_LIST_ERROR);
	}

	if ((Direction != (u8)XEMACPS_SEND) && (Direction != (u8)XEMACPS_RECV)) {
		return (LONG)(XST_INVALID_PARAM);
	}

	/* Starting from the top of the ring, save BD.Next, overwrite the entire
	 * BD with the template, then restore BD.Next
	 */
	CurBd = RingPtr->BaseBdAddr;
	for (i = 0U; i < RingPtr->AllCnt; i++) {
		memcpy((void *)CurBd, SrcBdPtr, sizeof(XEmacPs_Bd));
	CurBd += RingPtr->Separation;
	}

	CurBd -= RingPtr->Separation;

	if (Direction == XEMACPS_RECV) {
		XEmacPs_BdSetRxWrap(CurBd);
	}
	else {
		XEmacPs_BdSetTxWrap(CurBd);
	}

	return (LONG)(XST_SUCCESS);
}


/*****************************************************************************/
/**
 * Reserve locations in the BD list. The set of returned BDs may be modified
 * in preparation for future DMA transaction(s). Once the BDs are ready to be
 * submitted to hardware, the user must call XEmacPs_BdRingToHw() in the same
 * order which they were allocated here. Example:
 *
 * <pre>
 *        NumBd = 2,
 *        Status = XEmacPs_BdRingAlloc(MyRingPtr, NumBd, &MyBdSet),
 *
 *        if (Status != XST_SUCCESS)
 *        {
 *            *Not enough BDs available for the request*
 *        }
 *
 *        CurBd = MyBdSet,
 *        for (i=0; i<NumBd; i++)
 *        {
 *            * Prepare CurBd *.....
 *
 *            * Onto next BD *
 *            CurBd = XEmacPs_BdRingNext(MyRingPtr, CurBd),
 *        }
 *
 *        * Give list to hardware *
 *        Status = XEmacPs_BdRingToHw(MyRingPtr, NumBd, MyBdSet),
 * </pre>
 *
 * A more advanced use of this function may allocate multiple sets of BDs.
 * They must be allocated and given to hardware in the correct sequence:
 * <pre>
 *        * Legal *
 *        XEmacPs_BdRingAlloc(MyRingPtr, NumBd1, &MySet1),
 *        XEmacPs_BdRingToHw(MyRingPtr, NumBd1, MySet1),
 *
 *        * Legal *
 *        XEmacPs_BdRingAlloc(MyRingPtr, NumBd1, &MySet1),
 *        XEmacPs_BdRingAlloc(MyRingPtr, NumBd2, &MySet2),
 *        XEmacPs_BdRingToHw(MyRingPtr, NumBd1, MySet1),
 *        XEmacPs_BdRingToHw(MyRingPtr, NumBd2, MySet2),
 *
 *        * Not legal *
 *        XEmacPs_BdRingAlloc(MyRingPtr, NumBd1, &MySet1),
 *        XEmacPs_BdRingAlloc(MyRingPtr, NumBd2, &MySet2),
 *        XEmacPs_BdRingToHw(MyRingPtr, NumBd2, MySet2),
 *        XEmacPs_BdRingToHw(MyRingPtr, NumBd1, MySet1),
 * </pre>
 *
 * Use the API defined in xemacps_bd.h to modify individual BDs. Traversal
 * of the BD set can be done using XEmacPs_BdRingNext() and
 * XEmacPs_BdRingPrev().
 *
 * @param RingPtr is a pointer to the BD ring instance to be worked on.
 * @param NumBd is the number of BDs to allocate
 * @param BdSetPtr is an output parameter, it points to the first BD available
 *        for modification.
 *
 * @return
 *   - XST_SUCCESS if the requested number of BDs was returned in the BdSetPtr
 *     parameter.
 *   - XST_FAILURE if there were not enough free BDs to satisfy the request.
 *
 * @note This function should not be preempted by another XEmacPs_Bd function
 *       call that modifies the BD space. It is the caller's responsibility to
 *       provide a mutual exclusion mechanism.
 *
 * @note Do not modify more BDs than the number requested with the NumBd
 *       parameter. Doing so will lead to data corruption and system
 *       instability.
 *
 *****************************************************************************/
LONG XEmacPs_BdRingAlloc(XEmacPs_BdRing * RingPtr, u32 NumBd,
			 XEmacPs_Bd ** BdSetPtr)
{
	LONG Status;
	/* Enough free BDs available for the request? */
	if (RingPtr->FreeCnt < NumBd) {
		Status = (LONG)(XST_FAILURE);
	} else {
	/* Set the return argument and move FreeHead forward */
	*BdSetPtr = RingPtr->FreeHead;
	XEMACPS_RING_SEEKAHEAD(RingPtr, RingPtr->FreeHead, NumBd);
	RingPtr->FreeCnt -= NumBd;
	RingPtr->PreCnt += NumBd;
		Status = (LONG)(XST_SUCCESS);
	}
	return Status;
}

/*****************************************************************************/
/**
 * Fully or partially undo an XEmacPs_BdRingAlloc() operation. Use this
 * function if all the BDs allocated by XEmacPs_BdRingAlloc() could not be
 * transferred to hardware with XEmacPs_BdRingToHw().
 *
 * This function helps out in situations when an unrelated error occurs after
 * BDs have been allocated but before they have been given to hardware.
 * An example of this type of error would be an OS running out of resources.
 *
 * This function is not the same as XEmacPs_BdRingFree(). The Free function
 * returns BDs to the free list after they have been processed by hardware,
 * while UnAlloc returns them before being processed by hardware.
 *
 * There are two scenarios where this function can be used. Full UnAlloc or
 * Partial UnAlloc. A Full UnAlloc means all the BDs Alloc'd will be returned:
 *
 * <pre>
 *    Status = XEmacPs_BdRingAlloc(MyRingPtr, 10, &BdPtr),
 *        ...
 *    if (Error)
 *    {
 *        Status = XEmacPs_BdRingUnAlloc(MyRingPtr, 10, &BdPtr),
 *    }
 * </pre>
 *
 * A partial UnAlloc means some of the BDs Alloc'd will be returned:
 *
 * <pre>
 *    Status = XEmacPs_BdRingAlloc(MyRingPtr, 10, &BdPtr),
 *    BdsLeft = 10,
 *    CurBdPtr = BdPtr,
 *
 *    while (BdsLeft)
 *    {
 *       if (Error)
 *       {
 *          Status = XEmacPs_BdRingUnAlloc(MyRingPtr, BdsLeft, CurBdPtr),
 *       }
 *
 *       CurBdPtr = XEmacPs_BdRingNext(MyRingPtr, CurBdPtr),
 *       BdsLeft--,
 *    }
 * </pre>
 *
 * A partial UnAlloc must include the last BD in the list that was Alloc'd.
 *
 * @param RingPtr is a pointer to the instance to be worked on.
 * @param NumBd is the number of BDs to allocate
 * @param BdSetPtr is an output parameter, it points to the first BD available
 *        for modification.
 *
 * @return
 *   - XST_SUCCESS if the BDs were unallocated.
 *   - XST_FAILURE if NumBd parameter was greater that the number of BDs in
 *     the preprocessing state.
 *
 * @note This function should not be preempted by another XEmacPs_Bd function
 *       call that modifies the BD space. It is the caller's responsibility to
 *       provide a mutual exclusion mechanism.
 *
 *****************************************************************************/
LONG XEmacPs_BdRingUnAlloc(XEmacPs_BdRing * RingPtr, u32 NumBd,
			   XEmacPs_Bd * BdSetPtr)
{
	LONG Status;
	(void) BdSetPtr;
	Xil_AssertNonvoid(RingPtr != NULL);
	Xil_AssertNonvoid(BdSetPtr != NULL);

	/* Enough BDs in the free state for the request? */
	if (RingPtr->PreCnt < NumBd) {
		Status = (LONG)(XST_FAILURE);
	} else {
	/* Set the return argument and move FreeHead backward */
		XEMACPS_RING_SEEKBACK(RingPtr, (RingPtr->FreeHead), NumBd);
	RingPtr->FreeCnt += NumBd;
	RingPtr->PreCnt -= NumBd;
		Status = (LONG)(XST_SUCCESS);
	}
	return Status;
}


/*****************************************************************************/
/**
 * Enqueue a set of BDs to hardware that were previously allocated by
 * XEmacPs_BdRingAlloc(). Once this function returns, the argument BD set goes
 * under hardware control. Any changes made to these BDs after this point will
 * corrupt the BD list leading to data corruption and system instability.
 *
 * The set will be rejected if the last BD of the set does not mark the end of
 * a packet (see XEmacPs_BdSetLast()).
 *
 * @param RingPtr is a pointer to the instance to be worked on.
 * @param NumBd is the number of BDs in the set.
 * @param BdSetPtr is the first BD of the set to commit to hardware.
 *
 * @return
 *   - XST_SUCCESS if the set of BDs was accepted and enqueued to hardware.
 *   - XST_FAILURE if the set of BDs was rejected because the last BD of the set
 *     did not have its "last" bit set.
 *   - XST_DMA_SG_LIST_ERROR if this function was called out of sequence with
 *     XEmacPs_BdRingAlloc().
 *
 * @note This function should not be preempted by another XEmacPs_Bd function
 *       call that modifies the BD space. It is the caller's responsibility to
 *       provide a mutual exclusion mechanism.
 *
 *****************************************************************************/
LONG XEmacPs_BdRingToHw(XEmacPs_BdRing * RingPtr, u32 NumBd,
			XEmacPs_Bd * BdSetPtr)
{
	XEmacPs_Bd *CurBdPtr;
	u32 i;
	LONG Status;
	/* if no bds to process, simply return. */
	if (0U == NumBd){
		Status = (LONG)(XST_SUCCESS);
	} else {
	/* Make sure we are in sync with XEmacPs_BdRingAlloc() */
	if ((RingPtr->PreCnt < NumBd) || (RingPtr->PreHead != BdSetPtr)) {
			Status = (LONG)(XST_DMA_SG_LIST_ERROR);
		} else {
	CurBdPtr = BdSetPtr;
			for (i = 0U; i < NumBd; i++) {
				CurBdPtr = (XEmacPs_Bd *)((void *)XEmacPs_BdRingNext(RingPtr, CurBdPtr));
	}
	/* Adjust ring pointers & counters */
	XEMACPS_RING_SEEKAHEAD(RingPtr, RingPtr->PreHead, NumBd);
	RingPtr->PreCnt -= NumBd;
	RingPtr->HwTail = CurBdPtr;
	RingPtr->HwCnt += NumBd;

			Status = (LONG)(XST_SUCCESS);
		}
	}
	return Status;
}


/*****************************************************************************/
/**
 * Returns a set of BD(s) that have been processed by hardware. The returned
 * BDs may be examined to determine the outcome of the DMA transaction(s).
 * Once the BDs have been examined, the user must call XEmacPs_BdRingFree()
 * in the same order which they were retrieved here. Example:
 *
 * <pre>
 *        NumBd = XEmacPs_BdRingFromHwTx(MyRingPtr, MaxBd, &MyBdSet),
 *        if (NumBd == 0)
 *        {
 *           * hardware has nothing ready for us yet*
 *        }
 *
 *        CurBd = MyBdSet,
 *        for (i=0; i<NumBd; i++)
 *        {
 *           * Examine CurBd for post processing *.....
 *
 *           * Onto next BD *
 *           CurBd = XEmacPs_BdRingNext(MyRingPtr, CurBd),
 *           }
 *
 *           XEmacPs_BdRingFree(MyRingPtr, NumBd, MyBdSet),  *Return list*
 *        }
 * </pre>
 *
 * A more advanced use of this function may allocate multiple sets of BDs.
 * They must be retrieved from hardware and freed in the correct sequence:
 * <pre>
 *        * Legal *
 *        XEmacPs_BdRingFromHwTx(MyRingPtr, NumBd1, &MySet1),
 *        XEmacPs_BdRingFree(MyRingPtr, NumBd1, MySet1),
 *
 *        * Legal *
 *        XEmacPs_BdRingFromHwTx(MyRingPtr, NumBd1, &MySet1),
 *        XEmacPs_BdRingFromHwTx(MyRingPtr, NumBd2, &MySet2),
 *        XEmacPs_BdRingFree(MyRingPtr, NumBd1, MySet1),
 *        XEmacPs_BdRingFree(MyRingPtr, NumBd2, MySet2),
 *
 *        * Not legal *
 *        XEmacPs_BdRingFromHwTx(MyRingPtr, NumBd1, &MySet1),
 *        XEmacPs_BdRingFromHwTx(MyRingPtr, NumBd2, &MySet2),
 *        XEmacPs_BdRingFree(MyRingPtr, NumBd2, MySet2),
 *        XEmacPs_BdRingFree(MyRingPtr, NumBd1, MySet1),
 * </pre>
 *
 * If hardware has only partially completed a packet spanning multiple BDs,
 * then none of the BDs for that packet will be included in the results.
 *
 * @param RingPtr is a pointer to the instance to be worked on.
 * @param BdLimit is the maximum number of BDs to return in the set.
 * @param BdSetPtr is an output parameter, it points to the first BD available
 *        for examination.
 *
 * @return
 *   The number of BDs processed by hardware. A value of 0 indicates that no
 *   data is available. No more than BdLimit BDs will be returned.
 *
 * @note Treat BDs returned by this function as read-only.
 *
 * @note This function should not be preempted by another XEmacPs_Bd function
 *       call that modifies the BD space. It is the caller's responsibility to
 *       provide a mutual exclusion mechanism.
 *
 *****************************************************************************/
u32 XEmacPs_BdRingFromHwTx(XEmacPs_BdRing * RingPtr, u32 BdLimit,
				 XEmacPs_Bd ** BdSetPtr)
{
	XEmacPs_Bd *CurBdPtr;
	u32 BdStr = 0U;
	u32 BdCount;
	u32 BdPartialCount;
	u32 Sop = 0U;
	u32 Status;
	u32 BdLimitLoc = BdLimit;
	CurBdPtr = RingPtr->HwHead;
	BdCount = 0U;
	BdPartialCount = 0U;

	/* If no BDs in work group, then there's nothing to search */
	if (RingPtr->HwCnt == 0x00000000U) {
		*BdSetPtr = NULL;
		Status = 0U;
	} else {

		if (BdLimitLoc > RingPtr->HwCnt){
			BdLimitLoc = RingPtr->HwCnt;
	}
	/* Starting at HwHead, keep moving forward in the list until:
	 *  - A BD is encountered with its new/used bit set which means
	 *    hardware has not completed processing of that BD.
	 *  - RingPtr->HwTail is reached and RingPtr->HwCnt is reached.
	 *  - The number of requested BDs has been processed
	 */
		while (BdCount < BdLimitLoc) {
		/* Read the status */
			if(CurBdPtr != NULL){
		BdStr = XEmacPs_BdRead(CurBdPtr, XEMACPS_BD_STAT_OFFSET);
			}

			if ((Sop == 0x00000000U) && ((BdStr & XEMACPS_TXBUF_USED_MASK)!=0x00000000U)){
				Sop = 1U;
			}
			if (Sop == 0x00000001U) {
			BdCount++;
			BdPartialCount++;
		}

		/* hardware has processed this BD so check the "last" bit.
		 * If it is clear, then there are more BDs for the current
		 * packet. Keep a count of these partial packet BDs.
		 */
			if ((Sop == 0x00000001U) && ((BdStr & XEMACPS_TXBUF_LAST_MASK)!=0x00000000U)) {
				Sop = 0U;
				BdPartialCount = 0U;
		}

		/* Move on to next BD in work group */
		CurBdPtr = XEmacPs_BdRingNext(RingPtr, CurBdPtr);
	}

	/* Subtract off any partial packet BDs found */
        BdCount -= BdPartialCount;

	/* If BdCount is non-zero then BDs were found to return. Set return
	 * parameters, update pointers and counters, return success
	 */
		if (BdCount > 0x00000000U) {
		*BdSetPtr = RingPtr->HwHead;
		RingPtr->HwCnt -= BdCount;
		RingPtr->PostCnt += BdCount;
		XEMACPS_RING_SEEKAHEAD(RingPtr, RingPtr->HwHead, BdCount);
			Status = (BdCount);
		} else {
			*BdSetPtr = NULL;
			Status = 0U;
	}
	}
	return Status;
}


/*****************************************************************************/
/**
 * Returns a set of BD(s) that have been processed by hardware. The returned
 * BDs may be examined to determine the outcome of the DMA transaction(s).
 * Once the BDs have been examined, the user must call XEmacPs_BdRingFree()
 * in the same order which they were retrieved here. Example:
 *
 * <pre>
 *        NumBd = XEmacPs_BdRingFromHwRx(MyRingPtr, MaxBd, &MyBdSet),
 *
 *        if (NumBd == 0)
 *        {
 *           *hardware has nothing ready for us yet*
 *        }
 *
 *        CurBd = MyBdSet,
 *        for (i=0; i<NumBd; i++)
 *        {
 *           * Examine CurBd for post processing *.....
 *
 *           * Onto next BD *
 *           CurBd = XEmacPs_BdRingNext(MyRingPtr, CurBd),
 *           }
 *
 *           XEmacPs_BdRingFree(MyRingPtr, NumBd, MyBdSet),  * Return list *
 *        }
 * </pre>
 *
 * A more advanced use of this function may allocate multiple sets of BDs.
 * They must be retrieved from hardware and freed in the correct sequence:
 * <pre>
 *        * Legal *
 *        XEmacPs_BdRingFromHwRx(MyRingPtr, NumBd1, &MySet1),
 *        XEmacPs_BdRingFree(MyRingPtr, NumBd1, MySet1),
 *
 *        * Legal *
 *        XEmacPs_BdRingFromHwRx(MyRingPtr, NumBd1, &MySet1),
 *        XEmacPs_BdRingFromHwRx(MyRingPtr, NumBd2, &MySet2),
 *        XEmacPs_BdRingFree(MyRingPtr, NumBd1, MySet1),
 *        XEmacPs_BdRingFree(MyRingPtr, NumBd2, MySet2),
 *
 *        * Not legal *
 *        XEmacPs_BdRingFromHwRx(MyRingPtr, NumBd1, &MySet1),
 *        XEmacPs_BdRingFromHwRx(MyRingPtr, NumBd2, &MySet2),
 *        XEmacPs_BdRingFree(MyRingPtr, NumBd2, MySet2),
 *        XEmacPs_BdRingFree(MyRingPtr, NumBd1, MySet1),
 * </pre>
 *
 * If hardware has only partially completed a packet spanning multiple BDs,
 * then none of the BDs for that packet will be included in the results.
 *
 * @param RingPtr is a pointer to the instance to be worked on.
 * @param BdLimit is the maximum number of BDs to return in the set.
 * @param BdSetPtr is an output parameter, it points to the first BD available
 *        for examination.
 *
 * @return
 *   The number of BDs processed by hardware. A value of 0 indicates that no
 *   data is available. No more than BdLimit BDs will be returned.
 *
 * @note Treat BDs returned by this function as read-only.
 *
 * @note This function should not be preempted by another XEmacPs_Bd function
 *       call that modifies the BD space. It is the caller's responsibility to
 *       provide a mutual exclusion mechanism.
 *
 *****************************************************************************/
u32 XEmacPs_BdRingFromHwRx(XEmacPs_BdRing * RingPtr, u32 BdLimit,
				 XEmacPs_Bd ** BdSetPtr)
{
	XEmacPs_Bd *CurBdPtr;
	u32 BdStr = 0U;
	u32 BdCount;
	u32 BdPartialCount;
	u32 Status;

	CurBdPtr = RingPtr->HwHead;
	BdCount = 0U;
	BdPartialCount = 0U;

	/* If no BDs in work group, then there's nothing to search */
	if (RingPtr->HwCnt == 0x00000000U) {
		*BdSetPtr = NULL;
		Status = 0U;
	} else {

	/* Starting at HwHead, keep moving forward in the list until:
	 *  - A BD is encountered with its new/used bit set which means
	 *    hardware has completed processing of that BD.
	 *  - RingPtr->HwTail is reached and RingPtr->HwCnt is reached.
	 *  - The number of requested BDs has been processed
	 */
	while (BdCount < BdLimit) {

		/* Read the status */
			if(CurBdPtr!=NULL){
		BdStr = XEmacPs_BdRead(CurBdPtr, XEMACPS_BD_STAT_OFFSET);
			}
			if ((!(XEmacPs_BdIsRxNew(CurBdPtr)))==TRUE) {
			break;
		}

		BdCount++;

		/* hardware has processed this BD so check the "last" bit. If
                 * it is clear, then there are more BDs for the current packet.
                 * Keep a count of these partial packet BDs.
		 */
			if ((BdStr & XEMACPS_RXBUF_EOF_MASK)!=0x00000000U) {
				BdPartialCount = 0U;
			} else {
			BdPartialCount++;
		}

		/* Move on to next BD in work group */
		CurBdPtr = XEmacPs_BdRingNext(RingPtr, CurBdPtr);
	}

	/* Subtract off any partial packet BDs found */
	BdCount -= BdPartialCount;

	/* If BdCount is non-zero then BDs were found to return. Set return
	 * parameters, update pointers and counters, return success
	 */
		if (BdCount > 0x00000000U) {
		*BdSetPtr = RingPtr->HwHead;
		RingPtr->HwCnt -= BdCount;
		RingPtr->PostCnt += BdCount;
		XEMACPS_RING_SEEKAHEAD(RingPtr, RingPtr->HwHead, BdCount);
			Status = (BdCount);
	}
	else {
		*BdSetPtr = NULL;
			Status = 0U;
	}
}
	return Status;
}


/*****************************************************************************/
/**
 * Frees a set of BDs that had been previously retrieved with
 * XEmacPs_BdRingFromHw().
 *
 * @param RingPtr is a pointer to the instance to be worked on.
 * @param NumBd is the number of BDs to free.
 * @param BdSetPtr is the head of a list of BDs returned by
 * XEmacPs_BdRingFromHw().
 *
 * @return
 *   - XST_SUCCESS if the set of BDs was freed.
 *   - XST_DMA_SG_LIST_ERROR if this function was called out of sequence with
 *     XEmacPs_BdRingFromHw().
 *
 * @note This function should not be preempted by another XEmacPs_Bd function
 *       call that modifies the BD space. It is the caller's responsibility to
 *       provide a mutual exclusion mechanism.
 *
 *****************************************************************************/
LONG XEmacPs_BdRingFree(XEmacPs_BdRing * RingPtr, u32 NumBd,
			XEmacPs_Bd * BdSetPtr)
{
	LONG Status;
	/* if no bds to process, simply return. */
	if (0x00000000U == NumBd){
		Status = (LONG)(XST_SUCCESS);
	} else {
	/* Make sure we are in sync with XEmacPs_BdRingFromHw() */
	if ((RingPtr->PostCnt < NumBd) || (RingPtr->PostHead != BdSetPtr)) {
			Status = (LONG)(XST_DMA_SG_LIST_ERROR);
		} else {
	/* Update pointers and counters */
	RingPtr->FreeCnt += NumBd;
	RingPtr->PostCnt -= NumBd;
	XEMACPS_RING_SEEKAHEAD(RingPtr, RingPtr->PostHead, NumBd);
			Status = (LONG)(XST_SUCCESS);
		}
	}
	return Status;
}


/*****************************************************************************/
/**
 * Check the internal data structures of the BD ring for the provided channel.
 * The following checks are made:
 *
 *   - Is the BD ring linked correctly in physical address space.
 *   - Do the internal pointers point to BDs in the ring.
 *   - Do the internal counters add up.
 *
 * The channel should be stopped prior to calling this function.
 *
 * @param RingPtr is a pointer to the instance to be worked on.
 * @param Direction is either XEMACPS_SEND or XEMACPS_RECV that indicates
 *        which direction.
 *
 * @return
 *   - XST_SUCCESS if the set of BDs was freed.
 *   - XST_DMA_SG_NO_LIST if the list has not been created.
 *   - XST_IS_STARTED if the channel is not stopped.
 *   - XST_DMA_SG_LIST_ERROR if a problem is found with the internal data
 *     structures. If this value is returned, the channel should be reset to
 *     avoid data corruption or system instability.
 *
 * @note This function should not be preempted by another XEmacPs_Bd function
 *       call that modifies the BD space. It is the caller's responsibility to
 *       provide a mutual exclusion mechanism.
 *
 *****************************************************************************/
LONG XEmacPs_BdRingCheck(XEmacPs_BdRing * RingPtr, u8 Direction)
{
	UINTPTR AddrV, AddrP;
	u32 i;

	if ((Direction != (u8)XEMACPS_SEND) && (Direction != (u8)XEMACPS_RECV)) {
		return (LONG)(XST_INVALID_PARAM);
	}

	/* Is the list created */
	if (RingPtr->AllCnt == 0x00000000U) {
		return (LONG)(XST_DMA_SG_NO_LIST);
	}

	/* Can't check if channel is running */
	if (RingPtr->RunState == (u32)XST_DMA_SG_IS_STARTED) {
		return (LONG)(XST_IS_STARTED);
	}

	/* RunState doesn't make sense */
	if (RingPtr->RunState != (u32)XST_DMA_SG_IS_STOPPED) {
		return (LONG)(XST_DMA_SG_LIST_ERROR);
	}

	/* Verify internal pointers point to correct memory space */
	AddrV = (UINTPTR) RingPtr->FreeHead;
	if ((AddrV < RingPtr->BaseBdAddr) || (AddrV > RingPtr->HighBdAddr)) {
		return (LONG)(XST_DMA_SG_LIST_ERROR);
	}

	AddrV = (UINTPTR) RingPtr->PreHead;
	if ((AddrV < RingPtr->BaseBdAddr) || (AddrV > RingPtr->HighBdAddr)) {
		return (LONG)(XST_DMA_SG_LIST_ERROR);
	}

	AddrV = (UINTPTR) RingPtr->HwHead;
	if ((AddrV < RingPtr->BaseBdAddr) || (AddrV > RingPtr->HighBdAddr)) {
		return (LONG)(XST_DMA_SG_LIST_ERROR);
	}

	AddrV = (UINTPTR) RingPtr->HwTail;
	if ((AddrV < RingPtr->BaseBdAddr) || (AddrV > RingPtr->HighBdAddr)) {
		return (LONG)(XST_DMA_SG_LIST_ERROR);
	}

	AddrV = (UINTPTR) RingPtr->PostHead;
	if ((AddrV < RingPtr->BaseBdAddr) || (AddrV > RingPtr->HighBdAddr)) {
		return (LONG)(XST_DMA_SG_LIST_ERROR);
	}

	/* Verify internal counters add up */
	if ((RingPtr->HwCnt + RingPtr->PreCnt + RingPtr->FreeCnt +
	     RingPtr->PostCnt) != RingPtr->AllCnt) {
		return (LONG)(XST_DMA_SG_LIST_ERROR);
	}

	/* Verify BDs are linked correctly */
	AddrV = RingPtr->BaseBdAddr;
	AddrP = RingPtr->PhysBaseAddr + RingPtr->Separation;

	for (i = 1U; i < RingPtr->AllCnt; i++) {
		/* Check BDA for this BD. It should point to next physical addr */
		if (XEmacPs_BdRead(AddrV, XEMACPS_BD_ADDR_OFFSET) != AddrP) {
			return (LONG)(XST_DMA_SG_LIST_ERROR);
		}

		/* Move on to next BD */
		AddrV += RingPtr->Separation;
		AddrP += RingPtr->Separation;
	}

	/* Last BD should have wrap bit set */
	if (XEMACPS_SEND == Direction) {
		if ((!XEmacPs_BdIsTxWrap(AddrV))==TRUE) {
			return (LONG)(XST_DMA_SG_LIST_ERROR);
		}
	}
	else {			/* XEMACPS_RECV */
		if ((!XEmacPs_BdIsRxWrap(AddrV))==TRUE) {
			return (LONG)(XST_DMA_SG_LIST_ERROR);
		}
	}

	/* No problems found */
	return (LONG)(XST_SUCCESS);
}

/*****************************************************************************/
/**
 * Set this bit to mark the last descriptor in the receive buffer descriptor
 * list.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    void XEmacPs_BdSetRxWrap(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
static void XEmacPs_BdSetRxWrap(UINTPTR BdPtr)
{
    u32 DataValueRx;
	u32 *TempPtr;

	BdPtr += (u32)(XEMACPS_BD_ADDR_OFFSET);
	TempPtr = (u32 *)BdPtr;
	if(TempPtr != NULL) {
		DataValueRx = *TempPtr;
		DataValueRx |= XEMACPS_RXBUF_WRAP_MASK;
		*TempPtr = DataValueRx;
	}
}

/*****************************************************************************/
/**
 * Sets this bit to mark the last descriptor in the transmit buffer
 * descriptor list.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    void XEmacPs_BdSetTxWrap(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
static void XEmacPs_BdSetTxWrap(UINTPTR BdPtr)
{
    u32 DataValueTx;
	u32 *TempPtr;

	BdPtr += (u32)(XEMACPS_BD_STAT_OFFSET);
	TempPtr = (u32 *)BdPtr;
	if(TempPtr != NULL) {
		DataValueTx = *TempPtr;
		DataValueTx |= XEMACPS_TXBUF_WRAP_MASK;
		*TempPtr = DataValueTx;
	}
}

/*****************************************************************************/
/**
 * Reset BD ring head and tail pointers.
 *
 * @param RingPtr is the instance to be worked on.
 * @param virtaddrloc is the virtual base address of the user memory region.
 *
 * @note
 * Should be called after XEmacPs_Stop()
 *
 * @note
 * C-style signature:
 *    void XEmacPs_BdRingPtrReset(XEmacPs_BdRing * RingPtr, void *virtaddrloc)
 *
 *****************************************************************************/
void XEmacPs_BdRingPtrReset(XEmacPs_BdRing * RingPtr, void *virtaddrloc)
{
	RingPtr->FreeHead = virtaddrloc;
	RingPtr->PreHead = virtaddrloc;
	RingPtr->HwHead = virtaddrloc;
	RingPtr->HwTail = virtaddrloc;
	RingPtr->PostHead = virtaddrloc;
}

/** @} */
