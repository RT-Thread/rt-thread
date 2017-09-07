/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * @file ipu_dmfc.c
 * @brief IPU common file configuration
 * @ingroup diag_ipu
 */

#include "ipu/ipu_common.h"

void ipu_dmfc_config(uint32_t ipu_index, uint32_t channel)
{
    switch (channel) {          // to support multi-flow, the DMFC is shared between them
    case MEM_TO_DP_BG_CH23:
        ipu_write_field(ipu_index, IPU_DMFC_DP_CHAN__DMFC_FIFO_SIZE_5B, 2); //Table of fifo_size 000-2^9,001-2^8,010-2^7,
        ipu_write_field(ipu_index, IPU_DMFC_DP_CHAN__DMFC_BURST_SIZE_5B, 1);    //Table of dmfc_burst_size codes
        ipu_write_field(ipu_index, IPU_DMFC_DP_CHAN__DMFC_ST_ADDR_5B, 0);   //start address 
        ipu_write_field(ipu_index, IPU_DMFC_DP_CHAN_DEF__DMFC_WM_CLR_5B, 0);
        ipu_write_field(ipu_index, IPU_DMFC_DP_CHAN_DEF__DMFC_WM_SET_5B, 0);
        ipu_write_field(ipu_index, IPU_DMFC_DP_CHAN_DEF__DMFC_WM_EN_5B, 0);
        ipu_write_field(ipu_index, IPU_DMFC_GENERAL1__WAIT4EOT_5B, 0);
        break;
    case MEM_TO_DP_FG_CH27:
        ipu_write_field(ipu_index, IPU_DMFC_DP_CHAN__DMFC_FIFO_SIZE_5F, 2);
        ipu_write_field(ipu_index, IPU_DMFC_DP_CHAN__DMFC_BURST_SIZE_5F, 1);
        ipu_write_field(ipu_index, IPU_DMFC_DP_CHAN__DMFC_ST_ADDR_5F, 2);
        ipu_write_field(ipu_index, IPU_DMFC_DP_CHAN_DEF__DMFC_WM_CLR_5F, 0);
        ipu_write_field(ipu_index, IPU_DMFC_DP_CHAN_DEF__DMFC_WM_SET_5F, 0);
        ipu_write_field(ipu_index, IPU_DMFC_DP_CHAN_DEF__DMFC_WM_EN_5F, 0);
        ipu_write_field(ipu_index, IPU_DMFC_GENERAL1__WAIT4EOT_5F, 0);
        break;
    case MEM_TO_DC_CH28:
        ipu_write_field(ipu_index, IPU_DMFC_WR_CHAN__DMFC_FIFO_SIZE_1, 1);
        ipu_write_field(ipu_index, IPU_DMFC_WR_CHAN__DMFC_BURST_SIZE_1, 1);
        ipu_write_field(ipu_index, IPU_DMFC_WR_CHAN__DMFC_ST_ADDR_1, 4);
        ipu_write_field(ipu_index, IPU_DMFC_WR_CHAN_DEF__DMFC_WM_CLR_1, 7);
        ipu_write_field(ipu_index, IPU_DMFC_WR_CHAN_DEF__DMFC_WM_SET_1, 2);
        ipu_write_field(ipu_index, IPU_DMFC_WR_CHAN_DEF__DMFC_WM_EN_1, 1);
        ipu_write_field(ipu_index, IPU_DMFC_GENERAL1__WAIT4EOT_1, 0);
        break;
    }
}

void ipu_dmfc_alloc(uint32_t ipu_index, uint32_t channel, uint32_t size, uint32_t start_addr,
                    uint32_t burst)
{
    switch (channel) {          // to support multi-flow, the DMFC is shared between them
    case MEM_TO_DP_BG_CH23:
        ipu_write_field(ipu_index, IPU_DMFC_DP_CHAN__DMFC_FIFO_SIZE_5B, size);  //Table of fifo_size 000-2^9,001-2^8,010-2^7,
        ipu_write_field(ipu_index, IPU_DMFC_DP_CHAN__DMFC_BURST_SIZE_5B, burst);    //start address 
        ipu_write_field(ipu_index, IPU_DMFC_DP_CHAN__DMFC_ST_ADDR_5B, start_addr);  //start address 
        break;
    case MEM_TO_DP_FG_CH27:
        ipu_write_field(ipu_index, IPU_DMFC_DP_CHAN__DMFC_FIFO_SIZE_5F, size);
        ipu_write_field(ipu_index, IPU_DMFC_DP_CHAN__DMFC_BURST_SIZE_5F, burst);
        ipu_write_field(ipu_index, IPU_DMFC_DP_CHAN__DMFC_ST_ADDR_5F, start_addr);
        break;
    case MEM_TO_DC_CH28:
        ipu_write_field(ipu_index, IPU_DMFC_WR_CHAN__DMFC_FIFO_SIZE_1, size);
        ipu_write_field(ipu_index, IPU_DMFC_WR_CHAN__DMFC_BURST_SIZE_1, burst);
        ipu_write_field(ipu_index, IPU_DMFC_WR_CHAN__DMFC_ST_ADDR_1, start_addr);
        break;
    }

}
