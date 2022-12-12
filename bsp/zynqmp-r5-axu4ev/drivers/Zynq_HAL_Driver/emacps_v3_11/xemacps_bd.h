/******************************************************************************
* Copyright (C) 2010 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
 *
 * @file xemacps_bd.h
* @addtogroup emacps_v3_11
* @{
 *
 * This header provides operations to manage buffer descriptors in support
 * of scatter-gather DMA.
 *
 * The API exported by this header defines abstracted macros that allow the
 * user to read/write specific BD fields.
 *
 * <b>Buffer Descriptors</b>
 *
 * A buffer descriptor (BD) defines a DMA transaction. The macros defined by
 * this header file allow access to most fields within a BD to tailor a DMA
 * transaction according to user and hardware requirements.  See the hardware
 * IP DMA spec for more information on BD fields and how they affect transfers.
 *
 * The XEmacPs_Bd structure defines a BD. The organization of this structure
 * is driven mainly by the hardware for use in scatter-gather DMA transfers.
 *
 * <b>Performance</b>
 *
 * Limiting I/O to BDs can improve overall performance of the DMA channel.
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   Who  Date     Changes
 * ----- ---- -------- -------------------------------------------------------
 * 1.00a wsy  01/10/10 First release
 * 2.1   srt  07/15/14 Add support for Zynq Ultrascale MP GEM specification
 *                     and 64-bit changes.
 * 3.0   kvn  02/13/15 Modified code for MISRA-C:2012 compliance.
 * 3.0   hk   02/20/15 Added support for jumbo frames.
 *                     Disable extended mode. Perform all 64 bit changes under
 *                     check for arch64.
 * 3.2   hk   11/18/15 Change BD typedef and number of words.
 * 3.8   hk   08/18/18 Remove duplicate definition of XEmacPs_BdSetLength
 * 3.8   mus  11/05/18 Support 64 bit DMA addresses for Microblaze-X platform.
 *
 * </pre>
 *
 * ***************************************************************************
 */

#ifndef XEMACPS_BD_H        /* prevent circular inclusions */
#define XEMACPS_BD_H        /* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/

#include <string.h>
#include "xil_types.h"
#include "xil_assert.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/
#ifdef __aarch64__
/* Minimum BD alignment */
#define XEMACPS_DMABD_MINIMUM_ALIGNMENT  64U
#define XEMACPS_BD_NUM_WORDS 4U
#else
/* Minimum BD alignment */
#define XEMACPS_DMABD_MINIMUM_ALIGNMENT  4U
#define XEMACPS_BD_NUM_WORDS 2U
#endif

/**
 * The XEmacPs_Bd is the type for buffer descriptors (BDs).
 */
typedef u32 XEmacPs_Bd[XEMACPS_BD_NUM_WORDS];


/***************** Macros (Inline Functions) Definitions *********************/

/*****************************************************************************/
/**
 * Zero out BD fields
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @return Nothing
 *
 * @note
 * C-style signature:
 *    void XEmacPs_BdClear(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdClear(BdPtr)                                  \
    memset((BdPtr), 0, sizeof(XEmacPs_Bd))

/****************************************************************************/
/**
*
* Read the given Buffer Descriptor word.
*
* @param    BaseAddress is the base address of the BD to read
* @param    Offset is the word offset to be read
*
* @return   The 32-bit value of the field
*
* @note
* C-style signature:
*    u32 XEmacPs_BdRead(UINTPTR BaseAddress, UINTPTR Offset)
*
*****************************************************************************/
#define XEmacPs_BdRead(BaseAddress, Offset)             \
    (*(u32 *)((UINTPTR)((void*)(BaseAddress)) + (u32)(Offset)))

/****************************************************************************/
/**
*
* Write the given Buffer Descriptor word.
*
* @param    BaseAddress is the base address of the BD to write
* @param    Offset is the word offset to be written
* @param    Data is the 32-bit value to write to the field
*
* @return   None.
*
* @note
* C-style signature:
*    void XEmacPs_BdWrite(UINTPTR BaseAddress, UINTPTR Offset, UINTPTR Data)
*
*****************************************************************************/
#define XEmacPs_BdWrite(BaseAddress, Offset, Data)              \
    (*(u32 *)((UINTPTR)(void*)(BaseAddress) + (u32)(Offset)) = (u32)(Data))

/*****************************************************************************/
/**
 * Set the BD's Address field (word 0).
 *
 * @param  BdPtr is the BD pointer to operate on
 * @param  Addr  is the value to write to BD's status field.
 *
 * @note :
 *
 * C-style signature:
 *    void XEmacPs_BdSetAddressTx(XEmacPs_Bd* BdPtr, UINTPTR Addr)
 *
 *****************************************************************************/
#if defined(__aarch64__) || defined(__arch64__)
#define XEmacPs_BdSetAddressTx(BdPtr, Addr)                        \
    XEmacPs_BdWrite((BdPtr), XEMACPS_BD_ADDR_OFFSET,        \
            (u32)((Addr) & ULONG64_LO_MASK));        \
    XEmacPs_BdWrite((BdPtr), XEMACPS_BD_ADDR_HI_OFFSET,        \
    (u32)(((Addr) & ULONG64_HI_MASK) >> 32U));
#else
#define XEmacPs_BdSetAddressTx(BdPtr, Addr)                        \
    XEmacPs_BdWrite((BdPtr), XEMACPS_BD_ADDR_OFFSET, (u32)(Addr))
#endif

/*****************************************************************************/
/**
 * Set the BD's Address field (word 0).
 *
 * @param  BdPtr is the BD pointer to operate on
 * @param  Addr  is the value to write to BD's status field.
 *
 * @note : Due to some bits are mixed within receive BD's address field,
 *         read-modify-write is performed.
 *
 * C-style signature:
 *    void XEmacPs_BdSetAddressRx(XEmacPs_Bd* BdPtr, UINTPTR Addr)
 *
 *****************************************************************************/
#ifdef __aarch64__
#define XEmacPs_BdSetAddressRx(BdPtr, Addr)                        \
    XEmacPs_BdWrite((BdPtr), XEMACPS_BD_ADDR_OFFSET,              \
    ((XEmacPs_BdRead((BdPtr), XEMACPS_BD_ADDR_OFFSET) &           \
    ~XEMACPS_RXBUF_ADD_MASK) | ((u32)((Addr) & ULONG64_LO_MASK))));  \
    XEmacPs_BdWrite((BdPtr), XEMACPS_BD_ADDR_HI_OFFSET,     \
    (u32)(((Addr) & ULONG64_HI_MASK) >> 32U));
#else
#define XEmacPs_BdSetAddressRx(BdPtr, Addr)                        \
    XEmacPs_BdWrite((BdPtr), XEMACPS_BD_ADDR_OFFSET,              \
    ((XEmacPs_BdRead((BdPtr), XEMACPS_BD_ADDR_OFFSET) &           \
    ~XEMACPS_RXBUF_ADD_MASK) | (UINTPTR)(Addr)))
#endif

/*****************************************************************************/
/**
 * Set the BD's Status field (word 1).
 *
 * @param  BdPtr is the BD pointer to operate on
 * @param  Data  is the value to write to BD's status field.
 *
 * @note
 * C-style signature:
 *    void XEmacPs_BdSetStatus(XEmacPs_Bd* BdPtr, UINTPTR Data)
 *
 *****************************************************************************/
#define XEmacPs_BdSetStatus(BdPtr, Data)                           \
    XEmacPs_BdWrite((BdPtr), XEMACPS_BD_STAT_OFFSET,              \
    XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) | (Data))


/*****************************************************************************/
/**
 * Retrieve the BD's Packet DMA transfer status word (word 1).
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @return Status word
 *
 * @note
 * C-style signature:
 *    u32 XEmacPs_BdGetStatus(XEmacPs_Bd* BdPtr)
 *
 * Due to the BD bit layout differences in transmit and receive. User's
 * caution is required.
 *****************************************************************************/
#define XEmacPs_BdGetStatus(BdPtr)                                 \
    XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET)


/*****************************************************************************/
/**
 * Get the address (bits 0..31) of the BD's buffer address (word 0)
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    UINTPTR XEmacPs_BdGetBufAddr(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#if defined(__aarch64__) || defined(__arch64__)
#define XEmacPs_BdGetBufAddr(BdPtr)                               \
    (XEmacPs_BdRead((BdPtr), XEMACPS_BD_ADDR_OFFSET) |          \
    (XEmacPs_BdRead((BdPtr), XEMACPS_BD_ADDR_HI_OFFSET)) << 32U)
#else
#define XEmacPs_BdGetBufAddr(BdPtr)                               \
    (XEmacPs_BdRead((BdPtr), XEMACPS_BD_ADDR_OFFSET))
#endif

/*****************************************************************************/
/**
 * Set transfer length in bytes for the given BD. The length must be set each
 * time a BD is submitted to hardware.
 *
 * @param  BdPtr is the BD pointer to operate on
 * @param  LenBytes is the number of bytes to transfer.
 *
 * @note
 * C-style signature:
 *    void XEmacPs_BdSetLength(XEmacPs_Bd* BdPtr, u32 LenBytes)
 *
 *****************************************************************************/
#define XEmacPs_BdSetLength(BdPtr, LenBytes)                       \
    XEmacPs_BdWrite((BdPtr), XEMACPS_BD_STAT_OFFSET,              \
    ((XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) &           \
    ~XEMACPS_TXBUF_LEN_MASK) | (LenBytes)))


/*****************************************************************************/
/**
 * Retrieve the BD length field.
 *
 * For Tx channels, the returned value is the same as that written with
 * XEmacPs_BdSetLength().
 *
 * For Rx channels, the returned value is the size of the received packet.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @return Length field processed by hardware or set by
 *         XEmacPs_BdSetLength().
 *
 * @note
 * C-style signature:
 *    UINTPTR XEmacPs_BdGetLength(XEmacPs_Bd* BdPtr)
 *    XEAMCPS_RXBUF_LEN_MASK is same as XEMACPS_TXBUF_LEN_MASK.
 *
 *****************************************************************************/
#define XEmacPs_BdGetLength(BdPtr)                                 \
    (XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) &            \
    XEMACPS_RXBUF_LEN_MASK)

/*****************************************************************************/
/**
 * Retrieve the RX frame size.
 *
 * The returned value is the size of the received packet.
 * This API supports jumbo frame sizes if enabled.
 *
 * @param  InstancePtr is the pointer to XEmacps instance
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @return Length field processed by hardware or set by
 *         XEmacPs_BdSetLength().
 *
 * @note
 * C-style signature:
 *    UINTPTR XEmacPs_GetRxFrameSize(XEmacPs* InstancePtr, XEmacPs_Bd* BdPtr)
 *    RxBufMask is dependent on whether jumbo is enabled or not.
 *
 *****************************************************************************/
#define XEmacPs_GetRxFrameSize(InstancePtr, BdPtr)                   \
    (XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) &            \
    (InstancePtr)->RxBufMask)

/*****************************************************************************/
/**
 * Test whether the given BD has been marked as the last BD of a packet.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @return TRUE if BD represents the "Last" BD of a packet, FALSE otherwise
 *
 * @note
 * C-style signature:
 *    UINTPTR XEmacPs_BdIsLast(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdIsLast(BdPtr)                                    \
    ((XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) &           \
    XEMACPS_RXBUF_EOF_MASK)!=0U ? TRUE : FALSE)


/*****************************************************************************/
/**
 * Tell the DMA engine that the given transmit BD marks the end of the current
 * packet to be processed.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    void XEmacPs_BdSetLast(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdSetLast(BdPtr)                                   \
    (XEmacPs_BdWrite((BdPtr), XEMACPS_BD_STAT_OFFSET,             \
    XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) |             \
    XEMACPS_TXBUF_LAST_MASK))


/*****************************************************************************/
/**
 * Tell the DMA engine that the current packet does not end with the given
 * BD.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    void XEmacPs_BdClearLast(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdClearLast(BdPtr)                                 \
    (XEmacPs_BdWrite((BdPtr), XEMACPS_BD_STAT_OFFSET,             \
    XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) &             \
    ~XEMACPS_TXBUF_LAST_MASK))


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
/*#define XEmacPs_BdSetRxWrap(BdPtr)                                 \
    (XEmacPs_BdWrite((BdPtr), XEMACPS_BD_ADDR_OFFSET,             \
    XEmacPs_BdRead((BdPtr), XEMACPS_BD_ADDR_OFFSET) |             \
    XEMACPS_RXBUF_WRAP_MASK))
*/

/*****************************************************************************/
/**
 * Determine the wrap bit of the receive BD which indicates end of the
 * BD list.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    u8 XEmacPs_BdIsRxWrap(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdIsRxWrap(BdPtr)                                  \
    ((XEmacPs_BdRead((BdPtr), XEMACPS_BD_ADDR_OFFSET) &           \
    XEMACPS_RXBUF_WRAP_MASK)!=0U ? TRUE : FALSE)


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
/*#define XEmacPs_BdSetTxWrap(BdPtr)                                 \
    (XEmacPs_BdWrite((BdPtr), XEMACPS_BD_STAT_OFFSET,             \
    XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) |             \
    XEMACPS_TXBUF_WRAP_MASK))
*/

/*****************************************************************************/
/**
 * Determine the wrap bit of the transmit BD which indicates end of the
 * BD list.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    u8 XEmacPs_BdGetTxWrap(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdIsTxWrap(BdPtr)                                  \
    ((XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) &           \
    XEMACPS_TXBUF_WRAP_MASK)!=0U ? TRUE : FALSE)


/*****************************************************************************/
/*
 * Must clear this bit to enable the MAC to write data to the receive
 * buffer. Hardware sets this bit once it has successfully written a frame to
 * memory. Once set, software has to clear the bit before the buffer can be
 * used again. This macro clear the new bit of the receive BD.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    void XEmacPs_BdClearRxNew(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdClearRxNew(BdPtr)                                \
    (XEmacPs_BdWrite((BdPtr), XEMACPS_BD_ADDR_OFFSET,             \
    XEmacPs_BdRead((BdPtr), XEMACPS_BD_ADDR_OFFSET) &             \
    ~XEMACPS_RXBUF_NEW_MASK))


/*****************************************************************************/
/**
 * Determine the new bit of the receive BD.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    UINTPTR XEmacPs_BdIsRxNew(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdIsRxNew(BdPtr)                                   \
    ((XEmacPs_BdRead((BdPtr), XEMACPS_BD_ADDR_OFFSET) &           \
    XEMACPS_RXBUF_NEW_MASK)!=0U ? TRUE : FALSE)


/*****************************************************************************/
/**
 * Software sets this bit to disable the buffer to be read by the hardware.
 * Hardware sets this bit for the first buffer of a frame once it has been
 * successfully transmitted. This macro sets this bit of transmit BD to avoid
 * confusion.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    void XEmacPs_BdSetTxUsed(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdSetTxUsed(BdPtr)                                 \
    (XEmacPs_BdWrite((BdPtr), XEMACPS_BD_STAT_OFFSET,             \
    XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) |             \
    XEMACPS_TXBUF_USED_MASK))


/*****************************************************************************/
/**
 * Software clears this bit to enable the buffer to be read by the hardware.
 * Hardware sets this bit for the first buffer of a frame once it has been
 * successfully transmitted. This macro clears this bit of transmit BD.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    void XEmacPs_BdClearTxUsed(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdClearTxUsed(BdPtr)                               \
    (XEmacPs_BdWrite((BdPtr), XEMACPS_BD_STAT_OFFSET,             \
    XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) &             \
    ~XEMACPS_TXBUF_USED_MASK))


/*****************************************************************************/
/**
 * Determine the used bit of the transmit BD.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    UINTPTR XEmacPs_BdIsTxUsed(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdIsTxUsed(BdPtr)                                  \
    ((XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) &           \
    XEMACPS_TXBUF_USED_MASK)!=0U ? TRUE : FALSE)


/*****************************************************************************/
/**
 * Determine if a frame fails to be transmitted due to too many retries.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    UINTPTR XEmacPs_BdIsTxRetry(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdIsTxRetry(BdPtr)                                 \
    ((XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) &           \
    XEMACPS_TXBUF_RETRY_MASK)!=0U ? TRUE : FALSE)


/*****************************************************************************/
/**
 * Determine if a frame fails to be transmitted due to data can not be
 * feteched in time or buffers are exhausted.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    UINTPTR XEmacPs_BdIsTxUrun(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdIsTxUrun(BdPtr)                                  \
    ((XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) &           \
    XEMACPS_TXBUF_URUN_MASK)!=0U ? TRUE : FALSE)


/*****************************************************************************/
/**
 * Determine if a frame fails to be transmitted due to buffer is exhausted
 * mid-frame.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    UINTPTR XEmacPs_BdIsTxExh(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdIsTxExh(BdPtr)                                   \
    ((XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) &           \
    XEMACPS_TXBUF_EXH_MASK)!=0U ? TRUE : FALSE)


/*****************************************************************************/
/**
 * Sets this bit, no CRC will be appended to the current frame. This control
 * bit must be set for the first buffer in a frame and will be ignored for
 * the subsequent buffers of a frame.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * This bit must be clear when using the transmit checksum generation offload,
 * otherwise checksum generation and substitution will not occur.
 *
 * C-style signature:
 *    UINTPTR XEmacPs_BdSetTxNoCRC(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdSetTxNoCRC(BdPtr)                                \
    (XEmacPs_BdWrite((BdPtr), XEMACPS_BD_STAT_OFFSET,             \
    XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) |             \
    XEMACPS_TXBUF_NOCRC_MASK))


/*****************************************************************************/
/**
 * Clear this bit, CRC will be appended to the current frame. This control
 * bit must be set for the first buffer in a frame and will be ignored for
 * the subsequent buffers of a frame.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * This bit must be clear when using the transmit checksum generation offload,
 * otherwise checksum generation and substitution will not occur.
 *
 * C-style signature:
 *    UINTPTR XEmacPs_BdClearTxNoCRC(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdClearTxNoCRC(BdPtr)                              \
    (XEmacPs_BdWrite((BdPtr), XEMACPS_BD_STAT_OFFSET,             \
    XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) &             \
    ~XEMACPS_TXBUF_NOCRC_MASK))


/*****************************************************************************/
/**
 * Determine the broadcast bit of the receive BD.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    UINTPTR XEmacPs_BdIsRxBcast(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdIsRxBcast(BdPtr)                                 \
    ((XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) &           \
    XEMACPS_RXBUF_BCAST_MASK)!=0U ? TRUE : FALSE)


/*****************************************************************************/
/**
 * Determine the multicast hash bit of the receive BD.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    UINTPTR XEmacPs_BdIsRxMultiHash(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdIsRxMultiHash(BdPtr)                             \
    ((XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) &           \
    XEMACPS_RXBUF_MULTIHASH_MASK)!=0U ? TRUE : FALSE)


/*****************************************************************************/
/**
 * Determine the unicast hash bit of the receive BD.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    UINTPTR XEmacPs_BdIsRxUniHash(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdIsRxUniHash(BdPtr)                               \
    ((XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) &           \
    XEMACPS_RXBUF_UNIHASH_MASK)!=0U ? TRUE : FALSE)


/*****************************************************************************/
/**
 * Determine if the received frame is a VLAN Tagged frame.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    UINTPTR XEmacPs_BdIsRxVlan(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdIsRxVlan(BdPtr)                                  \
    ((XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) &           \
    XEMACPS_RXBUF_VLAN_MASK)!=0U ? TRUE : FALSE)


/*****************************************************************************/
/**
 * Determine if the received frame has Type ID of 8100h and null VLAN
 * identifier(Priority tag).
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    UINTPTR XEmacPs_BdIsRxPri(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdIsRxPri(BdPtr)                                   \
    ((XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) &           \
    XEMACPS_RXBUF_PRI_MASK)!=0U ? TRUE : FALSE)


/*****************************************************************************/
/**
 * Determine if the received frame's Concatenation Format Indicator (CFI) of
 * the frames VLANTCI field was set.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    UINTPTR XEmacPs_BdIsRxCFI(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdIsRxCFI(BdPtr)                                   \
    ((XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) &           \
    XEMACPS_RXBUF_CFI_MASK)!=0U ? TRUE : FALSE)


/*****************************************************************************/
/**
 * Determine the End Of Frame (EOF) bit of the receive BD.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    UINTPTR XEmacPs_BdGetRxEOF(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdIsRxEOF(BdPtr)                                   \
    ((XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) &           \
    XEMACPS_RXBUF_EOF_MASK)!=0U ? TRUE : FALSE)


/*****************************************************************************/
/**
 * Determine the Start Of Frame (SOF) bit of the receive BD.
 *
 * @param  BdPtr is the BD pointer to operate on
 *
 * @note
 * C-style signature:
 *    UINTPTR XEmacPs_BdGetRxSOF(XEmacPs_Bd* BdPtr)
 *
 *****************************************************************************/
#define XEmacPs_BdIsRxSOF(BdPtr)                                   \
    ((XEmacPs_BdRead((BdPtr), XEMACPS_BD_STAT_OFFSET) &           \
    XEMACPS_RXBUF_SOF_MASK)!=0U ? TRUE : FALSE)


/************************** Function Prototypes ******************************/

#ifdef __cplusplus
}
#endif

#endif /* end of protection macro */
/** @} */
