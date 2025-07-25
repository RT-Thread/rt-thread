 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     dma.h
 * @brief    header file for dma driver
 * @version  V1.0
 * @date     08. Apr 2020
 * @model    dma
 ******************************************************************************/

#ifndef _DRV_DMA_H_
#define _DRV_DMA_H_

#include <stdint.h>
#include <stdio.h>
#include <drv/common.h>
#include <drv/list.h>

#ifdef __cplusplus
extern "C" {
#endif

/****** DMA Event *****/
typedef enum {
    DMA_EVENT_TRANSFER_DONE       = 0,  ///< transfer complete
    DMA_EVENT_TRANSFER_HALF_DONE,       ///< transfer half done
    DMA_EVENT_TRANSFER_ERROR,           ///< transfer error
} csi_dma_event_t;

typedef enum {
    DMA_ADDR_INC    = 0,
    DMA_ADDR_DEC,
    DMA_ADDR_CONSTANT
} csi_dma_addr_inc_t;

typedef enum {
    DMA_DATA_WIDTH_8_BITS  = 0,
    DMA_DATA_WIDTH_16_BITS,
    DMA_DATA_WIDTH_32_BITS,
    DMA_DATA_WIDTH_64_BITS,
    DMA_DATA_WIDTH_128_BITS,
    DMA_DATA_WIDTH_512_BITS
} csi_dma_data_width_t;

typedef enum {
    DMA_MEM2MEM     = 0,
    DMA_MEM2PERH,
    DMA_PERH2MEM,
} csi_dma_trans_dir_t;

typedef struct {
    uint8_t ctrl_idx;
    uint8_t ch_idx;
} csi_dma_ch_desc_t;

typedef struct {
    uint16_t dev_tag;
    uint8_t  ctrl_idx;
    const csi_dma_ch_desc_t *ch_list;
} csi_dma_ch_spt_list_t;

typedef struct {
    csi_dma_addr_inc_t          src_inc;        ///< source address increment
    csi_dma_addr_inc_t          dst_inc;        ///< destination address increment
    csi_dma_data_width_t        src_tw;         ///< source transfer width in byte
    csi_dma_data_width_t        dst_tw;         ///< destination transfer width in byte
    csi_dma_trans_dir_t         trans_dir;      ///< transfer direction
    uint16_t                    handshake;      ///< handshake id
    uint16_t                    group_len;      ///< group transaction length (unit: bytes)
    uint8_t                     src_reload_en;  ///< 1:dma enable src addr auto reload, 0:disable
    uint8_t                     dst_reload_en;  ///< 1:dma enable dst addr auto reload, 0:disable
    uint8_t                     half_int_en;    ///< 1:dma enable half interrupt, 0: disable
    uint8_t                     lli_src_en;     ///< 1:dma enable llp, 0 disable
    uint8_t                     lli_dst_en;     ///< 1:dma enable llp, 0 disable
} csi_dma_ch_config_t;

#ifndef DMA_LLI_SIZE
#define DMA_LLI_SIZE 28
#endif

#define DEFINE_DESC_BUF(buf_name, num) uint8_t buf_name[num * DMA_LLI_SIZE]

typedef struct csi_dma_ch csi_dma_ch_t;

struct csi_dma_ch {
    void                *parent;
    int8_t              ctrl_id;
    int8_t              ch_id;
    void                (*callback)(csi_dma_ch_t *dma_ch, csi_dma_event_t event, void *arg);
    void                *arg;
    uint32_t            lli_num;                    //lli buffer len
    uint32_t            lli_count;                  //lli data count
    int32_t             lli_w_p;                    //write position
    int32_t             lli_r_p;                    //read position
    void                *lli;                       //lli buffer
    uint32_t            lli_loop_buf0;              //lli loop data
    uint32_t            lli_loop_buf1;              //lli loop data
    uint8_t             lli_loop[DMA_LLI_SIZE];     //lli loop handle
    int16_t             etb_ch_id;
    slist_t             next;
};

typedef struct {
    csi_dev_t           dev;
    slist_t             head;
    uint32_t            alloc_status;
    uint32_t            ch_num;
    void                *priv;
} csi_dma_t;

/**
  \brief       Init dma controller
  \param[in]   dma     the dma controller operate handle
  \param[in]   ctrl_id  the dma controller id
  \return      csi error code
*/
csi_error_t csi_dma_init(csi_dma_t *dma, int8_t ctrl_id);

/**
  \brief       Uninit dma controller
  \param[in]   dma     the dma controller operate handle
  \return      none
*/
void csi_dma_uninit(csi_dma_t *dma);

/**
  \brief       Alloc a dma channel
  \param[in]   dma_ch   the dma channel operate handle
  \param[in]   ch_id    the channel id  of dma; when set -1, means auto alloc
  \param[in]   ctrl_id  the dma controller id; when set -1, means auto alloc
  \return      csi error code
*/
csi_error_t csi_dma_ch_alloc(csi_dma_ch_t *dma_ch, int8_t ch_id, int8_t ctrl_id);

/**
  \brief       Free a dma channel
  \param[in]   dma_ch   the dma channel operate handle
  \return      none
*/
void csi_dma_ch_free(csi_dma_ch_t *dma_ch);

/**
  \brief       Config a dma channel
  \param[in]   dma_ch   the dma channel operate handle
  \param[in]   config   the config structure for dma channel
  \return      csi error code
*/
csi_error_t csi_dma_ch_config(csi_dma_ch_t *dma_ch, csi_dma_ch_config_t *config);

/**
  \brief       Start a dma channel
  \param[in]   dma_ch       the dma channel operate handle
  \param[in]   psrcaddr     transfer source address
  \param[in]   pdstaddr     transfer destination address
  \param[in]   length       transfer length (unit: bytes), if set data_width is 16, the length should be the multiple of 2, and
                            if set data_width is 32, the length should be the multiple of 4
  \return      none
*/
void csi_dma_ch_start(csi_dma_ch_t *dma_ch, void *srcaddr, void *dstaddr, uint32_t length);

/**
  \brief       Stop a dma channel
  \param[in]   dma_ch       the dma channel operate handle
  \return      none
*/
void csi_dma_ch_stop(csi_dma_ch_t *dma_ch);

/**
  \brief       Attach the callback handler to DMA channel
  \param[in]   dma_ch     operate handle.
  \param[in]   callback   callback function
  \param[in]   arg        user can define it by himself as callback's param
  \return      error code
*/
csi_error_t csi_dma_ch_attach_callback(csi_dma_ch_t *dma_ch, void *callback, void *arg);

/**
  \brief       detach the callback handler
  \param[in]   uart  operate handle.
*/
void        csi_dma_ch_detach_callback(csi_dma_ch_t *dma_ch);

/**
  \brief       enable dma power manage
  \param[in]   dma  dma handle to operate.
  \return      error code
*/
csi_error_t csi_dma_enable_pm(csi_dma_t *dma);

/**
  \brief       disable dma power manage
  \param[in]   dma  dma handle to operate.
*/
void        csi_dma_disable_pm(csi_dma_t *dma);

#ifdef __cplusplus
}
#endif

#endif /* _CSI_DMA_H_ */
