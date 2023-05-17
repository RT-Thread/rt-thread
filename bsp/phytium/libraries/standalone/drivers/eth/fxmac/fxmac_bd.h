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
 * FilePath: fxmac_bd.h
 * Date: 2022-04-06 14:46:52
 * LastEditTime: 2022-04-06 14:46:58
 * Description:  This file is for buffer descriptor (BD) management API.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/06/16    first release
 */

#ifndef FXMAC_BD_H
#define FXMAC_BD_H

#include "ftypes.h"
#include "string.h"

#ifdef __cplusplus
extern "C"
{
#endif


/**
 * @name: FXMAC_BD_READ
 * @msg: Read the given Buffer Descriptor word.
 * @param  bd_ptr is the base address of the BD to read
 * @param  offset is the word offset to be read
 * @return The 32-bit value of the field
 */
#define FXMAC_BD_READ(bd_ptr, offset) \
    (*(u32 *)((uintptr)((void *)(bd_ptr)) + (u32)(offset)))


/**
 * @name: FXMAC_BD_WRITE
 * @msg:  Write the given Buffer Descriptor word.
 * @param    bd_ptr is the base address of the BD to write
 * @param    Offset is the word offset to be written
 * @param    data is the 32-bit value to write to the field
 * @return {*}
 */
#define FXMAC_BD_WRITE(bd_ptr, Offset, data) \
    (*(u32 *)((uintptr)(void *)(bd_ptr) + (u32)(Offset)) = (u32)(data))


/**
 * @name: FXMAC_BD_SET_STATUS
 * @msg:  Set the BD's Status field (word 1).
 * @param  bd_ptr is the BD pointer to operate on
 * @param  data  is the value to write to BD's status field.
 */
#define FXMAC_BD_SET_STATUS(bd_ptr, data)           \
    FXMAC_BD_WRITE((bd_ptr), FXMAC_BD_STAT_OFFSET, \
                   FXMAC_BD_READ((bd_ptr), FXMAC_BD_STAT_OFFSET) | (data))


/**
 * @name: FXMAC_BD_IS_RX_NEW
 * @msg: Determine the new bit of the receive BD.
 * @param  bd_ptr is the BD pointer to operate on
 */
#define FXMAC_BD_IS_RX_NEW(bd_ptr)                      \
    ((FXMAC_BD_READ((bd_ptr), FXMAC_BD_ADDR_OFFSET) & \
      FXMAC_RXBUF_NEW_MASK) != 0U                   \
     ? TRUE                                     \
     : FALSE)


/**
 * @name: FXMAC_BD_IS_TX_WRAP
 * @msg:  Determine the wrap bit of the transmit BD which indicates end of the
 * BD list.
 * @param  bd_ptr is the BD pointer to operate on
 */
#define FXMAC_BD_IS_TX_WRAP(bd_ptr)                     \
    ((FXMAC_BD_READ((bd_ptr), FXMAC_BD_STAT_OFFSET) & \
      FXMAC_TXBUF_WRAP_MASK) != 0U                        \
     ? TRUE                                           \
     : FALSE)


/**
 * @name: FXMAC_BD_IS_RX_WRAP
 * @msg:  Determine the wrap bit of the receive BD which indicates end of the
 * BD list.
 * @param:  bd_ptr is the BD pointer to operate on
 */
#define FXMAC_BD_IS_RX_WRAP(bd_ptr)                     \
    ((FXMAC_BD_READ((bd_ptr), FXMAC_BD_ADDR_OFFSET) & \
      FXMAC_RXBUF_WRAP_MASK) != 0U                        \
     ? TRUE                                           \
     : FALSE)



/**
 * @name: FXMAC_BD_SET_ADDRESS_TX
 * @msg:  Set the BD's address field (word 0).
 * @param:  bd_ptr is the BD pointer to operate on
 * @param:  addr  is the value to write to BD's status field.
 */
#if defined(__aarch64__) || defined(__arch64__)
#define FXMAC_BD_SET_ADDRESS_TX(bd_ptr, addr)           \
    FXMAC_BD_WRITE((bd_ptr), FXMAC_BD_ADDR_OFFSET,    \
                   (u32)((addr)&ULONG64_LO_MASK));          \
    FXMAC_BD_WRITE((bd_ptr), FXMAC_BD_ADDR_HI_OFFSET, \
                   (u32)(((addr)&ULONG64_HI_MASK) >> 32U));
#else
#define FXMAC_BD_SET_ADDRESS_TX(bd_ptr, addr) \
    FXMAC_BD_WRITE((bd_ptr), FXMAC_BD_ADDR_OFFSET, (u32)(addr))
#endif


/**
 * @name: FXMAC_BD_SET_ADDRESS_RX
 * @msg: Set the BD's address field (word 0).
 * @param:  bd_ptr is the BD pointer to operate on
 * @param:  addr  is the value to write to BD's status field.
 * @return {*}
 */
#ifdef __aarch64__
#define FXMAC_BD_SET_ADDRESS_RX(bd_ptr, addr)                        \
    FXMAC_BD_WRITE((bd_ptr), FXMAC_BD_ADDR_OFFSET,                 \
                   ((FXMAC_BD_READ((bd_ptr), FXMAC_BD_ADDR_OFFSET) & \
                     ~FXMAC_RXBUF_ADD_MASK) |                            \
                    ((u32)((addr)&ULONG64_LO_MASK))));                   \
    FXMAC_BD_WRITE((bd_ptr), FXMAC_BD_ADDR_HI_OFFSET,              \
                   (u32)(((addr)&ULONG64_HI_MASK) >> 32U));
#else
#define FXMAC_BD_SET_ADDRESS_RX(bd_ptr, addr)                        \
    FXMAC_BD_WRITE((bd_ptr), FXMAC_BD_ADDR_OFFSET,                 \
                   ((FXMAC_BD_READ((bd_ptr), FXMAC_BD_ADDR_OFFSET) & \
                     ~FXMAC_RXBUF_ADD_MASK) |                            \
                    (u32)(addr)))
#endif


/**
 * @name: FXMAC_BD_SET_LENGTH
 * @msg:   Set transfer length in bytes for the given BD. The length must be set each
 * time a BD is submitted to hardware.
 * @param: bd_ptr is the BD pointer to operate on
 * @param: len_bytes is the number of bytes to transfer.
 * @return {*}
 */
#define FXMAC_BD_SET_LENGTH(bd_ptr, len_bytes)                      \
    FXMAC_BD_WRITE((bd_ptr), FXMAC_BD_STAT_OFFSET,                 \
                   ((FXMAC_BD_READ((bd_ptr), FXMAC_BD_STAT_OFFSET) & \
                     ~FXMAC_TXBUF_LEN_MASK) |                            \
                    (len_bytes)))


/**
 * @name: FXMAC_BD_GET_LENGTH
 * @msg:  For Tx channels, the returned value is the same as that written with
 * FXMAC_BD_SET_LENGTH(). For Rx channels, the returned value is the size of the received packet.
 * @param: bd_ptr is the BD pointer to operate on
 * @return {*}
 */
#define FXMAC_BD_GET_LENGTH(bd_ptr)                   \
    (FXMAC_BD_READ((bd_ptr), FXMAC_BD_STAT_OFFSET) & \
     FXMAC_RXBUF_LEN_MASK)

#define FXMAC_BD_GET_TX_LENGTH(bd_ptr)                   \
    (FXMAC_BD_READ((bd_ptr), FXMAC_BD_STAT_OFFSET) & \
     FXMAC_TXBUF_LEN_MASK)


/**
 * @name: FXMAC_GET_RX_FRAME_SIZE
 * @msg:  The returned value is the size of the received packet.
 * This API supports jumbo frame sizes if enabled.
 * @param  instance_p is the pointer to xmac instance
 * @param  bd_ptr is the BD pointer to operate on
 *
 * @return Length field processed by hardware or set by
 *         FXMAC_BD_SET_LENGTH().
 */

#define FXMAC_BD_JUMBO_LENGTH_MASK

#define FXMAC_GET_RX_FRAME_SIZE(instance_p, bd_ptr)                   \
    (FXMAC_BD_READ((bd_ptr), FXMAC_BD_STAT_OFFSET) &            \
     0x00003FFFU)



/**
 * @name: FXMAC_BD_CLEAR_TX_USED
 * @msg:  Software clears this bit to enable the buffer to be read by the hardware.
 * Hardware sets this bit for the first buffer of a frame once it has been
 * successfully transmitted. This macro clears this bit of transmit BD.
 * @param:  bd_ptr is the BD pointer to operate on
 * @return {*}
 */
#define FXMAC_BD_CLEAR_TX_USED(bd_ptr)                              \
    (FXMAC_BD_WRITE((bd_ptr), FXMAC_BD_STAT_OFFSET,               \
                    FXMAC_BD_READ((bd_ptr), FXMAC_BD_STAT_OFFSET) & \
                    (~FXMAC_TXBUF_USED_MASK)))

#define FXMAC_BD_SET_CRC(bd_ptr)                                   \
    (FXMAC_BD_WRITE((bd_ptr), FXMAC_BD_STAT_OFFSET,               \
                    FXMAC_BD_READ((bd_ptr), FXMAC_BD_STAT_OFFSET) & \
                    (~FXMAC_TXBUF_NOCRC_MASK)))


/**
 * @name: FXMAC_BD_SET_LAST
 * @msg:  Tell the DMA engine that the given transmit BD marks the end of the current
 * packet to be processed.
 * @param  bd_ptr is the BD pointer to operate on
 * @return {*}
 */
#define FXMAC_BD_SET_LAST(bd_ptr)                                  \
    (FXMAC_BD_WRITE((bd_ptr), FXMAC_BD_STAT_OFFSET,               \
                    FXMAC_BD_READ((bd_ptr), FXMAC_BD_STAT_OFFSET) | \
                    FXMAC_TXBUF_LAST_MASK))


/**
 * @name: FXMAC_BD_CLEAR_LAST
 * @msg:  Tell the DMA engine that the current packet does not end with the given
 * BD.
 * @param  bd_ptr is the BD pointer to operate on
 * @return {*}
 */
#define FXMAC_BD_CLEAR_LAST(bd_ptr)                                 \
    (FXMAC_BD_WRITE((bd_ptr), FXMAC_BD_STAT_OFFSET,             \
                    FXMAC_BD_READ((bd_ptr), FXMAC_BD_STAT_OFFSET) &             \
                    ~FXMAC_TXBUF_LAST_MASK))

/**
 * @name: FXMAC_BD_CLEAR
 * @msg:  Zero out BD fields
 * @param  bd_ptr is the BD pointer to operate on
 * @return {*}
 */
#define FXMAC_BD_CLEAR(bd_ptr)                                  \
    memset((bd_ptr), 0, sizeof(FXmacBd))

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/
#ifdef __aarch64__
/* Minimum BD alignment */
#define FXMAC_DMABD_MINIMUM_ALIGNMENT 64U
#define FXMAC_BD_NUM_WORDS 4U
#else
/* Minimum BD alignment */
#define FXMAC_DMABD_MINIMUM_ALIGNMENT 4U
#define FXMAC_BD_NUM_WORDS 2U
#endif

/**
 * The FXMAC_Bd is the type for buffer descriptors (BDs).
 */
typedef u32 FXmacBd[FXMAC_BD_NUM_WORDS];

#ifdef __cplusplus
}
#endif

#endif // !
