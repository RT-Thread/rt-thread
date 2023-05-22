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
 * FilePath: fgmac_dma.c
 * Date: 2022-04-06 14:46:52
 * LastEditTime: 2022-04-06 14:46:58
 * Description:  This file implements dma descriptor ring related functions.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2021/06/04    first release
 */

/***************************** Include Files *********************************/

#include <string.h>
#include "fassert.h"
#include "fkernel.h"
#include "fcache.h"
#include "fdebug.h"
#include "fgmac.h"
#include "fgmac_hw.h"

/************************** Constant Definitions *****************************/
#if defined(__aarch64__)
    #define  FGMAC_DMA_IS_64_BIT_MEMORY(addr)  (GENMASK_ULL(63, 32) & (uintptr)(addr))
#else
    #define  FGMAC_DMA_IS_64_BIT_MEMORY(addr)  (FALSE)
#endif

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FGMAC_DEBUG_TAG "FGMAC-DMA"
#define FGMAC_ERROR(format, ...)   FT_DEBUG_PRINT_E(FGMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGMAC_WARN(format, ...)    FT_DEBUG_PRINT_W(FGMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGMAC_INFO(format, ...)    FT_DEBUG_PRINT_I(FGMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGMAC_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FGMAC_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Variable Definitions *****************************/

/************************** Function Prototypes ******************************/

/**
 * @name: FGmacSetupTxDescRing
 * @msg: 配置FGMAC的接收DMA描述符和缓冲区
 * @param {FGmac *}instance_p 驱动控制数据
 *        {volatile FGmacDmaDesc *} rx_desc_tbl 接收DMA描述符表(数组)
 *        {u8} *rx_buf 接收DMA缓冲区(数组，每一个描述符对应一个缓冲区)
 *        {const fsize_t} rx_pre_buf_len 单个DMA缓冲区的字节数
 *        {const fsize_t} rx_buf_num DMA描述符或者DMA缓存区的数目
 * @return  {FError} RX DMA初始化的错误码信息，FGMAC_SUCCESS 表示RX DMA初始化成功，其它返回值表示RX DMA初始化失败
 * @note 传入的rx_desc_tbl和rx_buf必须为32位空间地址
 */
FError FGmacSetupRxDescRing(FGmac *instance_p, volatile FGmacDmaDesc *rx_desc_tbl,
                            u8 *rx_buf, const fsize_t rx_pre_buf_len, const fsize_t rx_buf_num)
{
    FASSERT(instance_p && rx_desc_tbl && rx_buf);
    u32 i;
    volatile FGmacDmaDesc *cur_rx_desc;
    FGmacRingDescData *rx_ring_p = &instance_p->rx_ring;
    uintptr base_addr = instance_p->config.base_addr;
    void *desc_end = (void *)(rx_desc_tbl + rx_buf_num * sizeof(FGmacDmaDesc));
    void *buf_end = (void *)(rx_buf + rx_buf_num * rx_pre_buf_len);

    /* check if end address of descriptor or buffer is in 64 bit memory,
        if TRUE, return error because DMA register can only hold 32 bit memory address */
    if ((FGMAC_DMA_IS_64_BIT_MEMORY(desc_end)) || (FGMAC_DMA_IS_64_BIT_MEMORY(buf_end)))
    {
        FGMAC_ERROR("Invalid rx descriptor memory %p or rx dma buf memory %p",
                    desc_end, buf_end);
        return FGMAC_ERR_INVALID_DMA_MEM;
    }

    /* init rx dma ring data */
    memset(rx_ring_p, 0, sizeof(*rx_ring_p));
    rx_ring_p->desc_max_num = rx_buf_num; /* total num of rx desc and rx buf */
    rx_ring_p->desc_idx = 0; /* idx of rx desc */
    rx_ring_p->desc_buf_idx = 0; /* idx of rx buf */
    rx_ring_p->desc_buf_base = rx_buf; /* base addr of rx buf */

    /* init rx dma descriptor table */
    memset((void *)rx_desc_tbl, 0, sizeof(FGmacDmaDesc) * rx_buf_num);

    for (i = 0; i < rx_buf_num; i++)
    {
        cur_rx_desc = rx_desc_tbl + i;
        cur_rx_desc->status = FGMAC_DMA_RDES0_OWN;
        cur_rx_desc->ctrl   = (FGMAC_DMA_RDES1_BUFFER1_SIZE_MASK & rx_pre_buf_len);
        FCacheDCacheInvalidateRange((uintptr)&rx_buf[i * rx_pre_buf_len], rx_pre_buf_len);
        cur_rx_desc->buf_addr = (u32)((uintptr)&rx_buf[i * rx_pre_buf_len]);

        if ((rx_buf_num - 1) == i)
        {
            cur_rx_desc->ctrl |= FGMAC_DMA_RDES1_END_RING;
        }
    }

    /* flush descriptor */
    instance_p->rx_desc = rx_desc_tbl;
    FCacheDCacheInvalidateRange((uintptr)instance_p->rx_desc, sizeof(FGmacDmaDesc) * rx_buf_num);

    FGMAC_WRITE_REG32(base_addr, FGMAC_DMA_RX_LIST_BASE_OFFSET, (u32)(uintptr)rx_desc_tbl);
    return FGMAC_SUCCESS;
}

/**
 * @name: FGmacSetupTxDescRing
 * @msg: 配置FGMAC的发送DMA描述符和缓冲区
 * @param {FGmac *}instance_p 驱动控制数据
 *        {volatile FGmacDmaDesc *} tx_desc_tbl 发送DMA描述符表(数组)
 *        {u8} *tx_buf 发送DMA缓冲区(数组，每一个描述符对应一个缓冲区)
 *        {const fsize_t} tx_pre_buf_len 单个DMA缓冲区的字节数
 *        {const fsize_t} tx_buf_num DMA描述符或者DMA缓存区的数目
 * @return  {FError} TX DMA初始化的错误码信息，FGMAC_SUCCESS 表示TX DMA初始化成功，其它返回值表示TX DMA初始化失败
 * @note 传入的tx_desc_tbl和tx_buf必须为32位空间地址
 */
FError FGmacSetupTxDescRing(FGmac *instance_p, volatile FGmacDmaDesc *tx_desc_tbl,
                            u8 *tx_buf, const fsize_t tx_pre_buf_len, const fsize_t tx_buf_num)
{
    FASSERT(instance_p && tx_desc_tbl && tx_buf);
    u32 i;
    volatile FGmacDmaDesc *cur_tx_desc;
    FGmacRingDescData *tx_ring_p = &instance_p->tx_ring;
    uintptr base_addr = instance_p->config.base_addr;
    void *desc_end = (void *)(tx_desc_tbl + tx_buf_num * sizeof(FGmacDmaDesc));
    void *buf_end = (void *)(tx_buf + tx_buf_num * tx_pre_buf_len);

    /* check if end address of descriptor or buffer is in 64 bit memory,
        if TRUE, return error because DMA register can only hold 32 bit memory address */
    if ((FGMAC_DMA_IS_64_BIT_MEMORY(desc_end)) || (FGMAC_DMA_IS_64_BIT_MEMORY(buf_end)))
    {
        FGMAC_ERROR("Invalid rx descriptor memory %p or rx dma buf memory %p",
                    desc_end, buf_end);
        return FGMAC_ERR_INVALID_DMA_MEM;
    }

    /* setup DMA descriptor ring data */
    memset(tx_ring_p, 0, sizeof(*tx_ring_p));
    tx_ring_p->desc_max_num = tx_buf_num;
    tx_ring_p->desc_idx = 0;
    tx_ring_p->desc_buf_idx = 0;
    tx_ring_p->desc_buf_base = tx_buf;

    /* setup DMA descriptor */
    memset((void *)tx_desc_tbl, 0, tx_buf_num * sizeof(FGmacDmaDesc));
    tx_desc_tbl[tx_buf_num - 1].ctrl |= FGMAC_DMA_TDES1_END_RING;
    for (i = 0; i < tx_buf_num; i++)
    {
        cur_tx_desc = tx_desc_tbl + i;
        FCacheDCacheInvalidateRange((uintptr)&tx_buf[i * tx_pre_buf_len], tx_pre_buf_len);
        cur_tx_desc->buf_addr = (u32)((uintptr)&tx_buf[i * tx_pre_buf_len]);
        cur_tx_desc->status  = 0;
    }

    /* flush descriptor */
    instance_p->tx_desc = tx_desc_tbl;
    FCacheDCacheInvalidateRange((uintptr)instance_p->tx_desc, tx_buf_num * sizeof(FGmacDmaDesc));

    FGMAC_WRITE_REG32(base_addr, FGMAC_DMA_TX_LIST_BASE_OFFSET, (u32)(uintptr)tx_desc_tbl);
    return FGMAC_SUCCESS;
}

/**
 * @name: FGmacStartTrans
 * @msg: 使能FGMAC DMA，使之可以接收/发送数据
 * @return {FError} FGMAC_SUCCESS 表示启动成功，其它返回值表示启动失败
 * @param {FGmac} *instance_p 驱动控制数据
 * @note 调用函数前需要确保FGMAC驱动初始化成功
 */
FError FGmacStartTrans(FGmac *instance_p)
{
    FASSERT(instance_p);
    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FGMAC_ERROR("Device is already initialized!!!");
        return FGMAC_ERR_NOT_READY;
    }

    FGmacStartDmaTrans(instance_p->config.base_addr);
    return FGMAC_SUCCESS;
}

/**
 * @name: FGmacStopTrans
 * @msg: 去使能FGMAC DMA, 使之不再能接收/发送数据
 * @return {FError} FGMAC_SUCCESS 表示去启动成功，其它返回值表示去启动失败
 * @param {FGmac} *instance_p 驱动控制数据
 * @note 调用函数前需要确保FGMAC驱动初始化成功
 */
FError FGmacStopTrans(FGmac *instance_p)
{
    FASSERT(instance_p);
    if (FT_COMPONENT_IS_READY != instance_p->is_ready)
    {
        FGMAC_ERROR("Device is already initialized!!!");
        return FGMAC_ERR_NOT_READY;
    }

    FGmacStopDmaTrans(instance_p->config.base_addr);
    return FGMAC_SUCCESS;
}

/**
 * @name: FGmacRecvFrame
 * @msg: 通过FGMAC接收数据帧
 * @return  {FError} FGMAC_SUCCESS 表示接收数据帧成功，其它返回值表示接收数据帧失败
 * @param {FGmac} *instance_p 驱动控制数据
 * @note 调用函数前需要确保FGMAC驱动初始化成功
 */
FError FGmacRecvFrame(FGmac *instance_p)
{
    FASSERT(instance_p);
    FGmacRingDescData *rx_ring = &instance_p->rx_ring;
    volatile FGmacDmaDesc *cur_rx_desc = &instance_p->rx_desc[rx_ring->desc_idx];
    u32 desc_cnt = 0;
    u32 flag = (FGMAC_DMA_RDES0_FIRST_DESCRIPTOR | FGMAC_DMA_RDES0_LAST_DESCRIPTOR);

    while ((0 == (FGMAC_DMA_RDES0_OWN & cur_rx_desc->status)) &&
           (desc_cnt < rx_ring->desc_max_num))
    {
        desc_cnt++;

        if (FGMAC_DMA_RDES0_FIRST_DESCRIPTOR == (flag & cur_rx_desc->status))
        {
            rx_ring->desc_buf_idx = rx_ring->desc_idx;
            FGMAC_DMA_INC_DESC(rx_ring->desc_idx, rx_ring->desc_max_num);
            cur_rx_desc = &instance_p->rx_desc[rx_ring->desc_idx];
        }
        else if (0 == (flag & cur_rx_desc->status))
        {
            FGMAC_DMA_INC_DESC(rx_ring->desc_idx, rx_ring->desc_max_num);
            cur_rx_desc = &instance_p->rx_desc[rx_ring->desc_idx];
        }
        else
        {
            rx_ring->desc_buf_idx = rx_ring->desc_idx;
            FGMAC_DMA_INC_DESC(rx_ring->desc_idx, rx_ring->desc_max_num);
            return FGMAC_SUCCESS;
        }
    }

    return FGMAC_ERR_TRANS_FAILED;
}

/**
 * @name: FGmacSendFrame
 * @msg: 通过FGMAC发送数据帧
 * @return {FError} FGMAC_SUCCESS 表示发送数据帧成功，其它返回值表示发送数据帧失败
 * @param {FGmac} *instance_p 驱动控制数据
 * @param {u32} frame_len 数据帧长度
 * @note 调用函数前需要确保FGMAC驱动初始化成功
 */
FError FGmacSendFrame(FGmac *instance_p, u32 frame_len)
{
    FASSERT(instance_p);
    u32 size = 0U;
    u32 i = 0U;
    u32 buf_cnt = 0U;
    FError ret = FGMAC_SUCCESS;
    volatile FGmacDmaDesc *tx_desc;
    FGmacRingDescData *tx_ring = &instance_p->tx_ring;
    const u32 max_packet_size = instance_p->config.max_packet_size;

    if (0U == frame_len)
    {
        return FGMAC_SUCCESS;
    }

    if (max_packet_size < frame_len)
    {
        buf_cnt = frame_len / max_packet_size;
        if (frame_len % max_packet_size)
        {
            buf_cnt++;
        }
    }
    else
    {
        buf_cnt = 1U;
    }

    if (1U == buf_cnt)
    {
        tx_desc = &instance_p->tx_desc[tx_ring->desc_idx];

        /* Set LAST and FIRST segment */
        tx_desc->ctrl |= (FGMAC_DMA_TDES1_FIRST_SEGMENT | FGMAC_DMA_TDES1_LAST_SEGMENT);

        /* Set frame size */
        tx_desc->ctrl &= ~(FGMAC_DMA_TDES1_BUFFER1_SIZE_MASK);
        tx_desc->ctrl |= (frame_len & FGMAC_DMA_TDES1_BUFFER1_SIZE_MASK);

        /* Set Own bit of the Tx descriptor Status: gives the buffer back to ETHERNET DMA */
        tx_desc->status |= FGMAC_DMA_TDES0_OWN;
        FGMAC_DMA_INC_DESC(tx_ring->desc_idx, tx_ring->desc_max_num);

    }
    else
    {
        for (i = 0U; i < buf_cnt; i++)
        {
            tx_desc = &instance_p->tx_desc[tx_ring->desc_idx];

            /* Clear FIRST and LAST segment bits */
            tx_desc->ctrl &= ~(FGMAC_DMA_TDES1_FIRST_SEGMENT | FGMAC_DMA_TDES1_LAST_SEGMENT);

            if (0U == i)
            {
                tx_desc->ctrl |= FGMAC_DMA_TDES1_FIRST_SEGMENT; /* Setting the first segment bit */
            }

            /* Program size */
            tx_desc->ctrl &= ~(FGMAC_DMA_TDES1_BUFFER1_SIZE_MASK);
            tx_desc->ctrl |= (max_packet_size & FGMAC_DMA_TDES1_BUFFER1_SIZE_MASK);

            if ((buf_cnt - 1) == i)
            {
                /* Setting the last segment bit */
                tx_desc->ctrl |= FGMAC_DMA_TDES1_LAST_SEGMENT;
                size = frame_len - (buf_cnt - 1U) * max_packet_size;
                tx_desc->ctrl &= ~(FGMAC_DMA_TDES1_BUFFER1_SIZE_MASK);
                tx_desc->ctrl |= (size & FGMAC_DMA_TDES1_BUFFER1_SIZE_MASK);
            }

            /* Set Own bit of the Tx descriptor Status: gives the buffer back to ETHERNET DMA */
            tx_desc->status |= FGMAC_DMA_TDES0_OWN;
            FGMAC_DMA_INC_DESC(tx_ring->desc_idx, tx_ring->desc_max_num);
        }
    }

    FGmacResumeDmaSend(instance_p->config.base_addr);
    return ret;
}