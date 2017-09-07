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
 * @file dcp.h
 * @brief Interface for DCP module
 */

#ifndef _DCP_H_
#define _DCP_H_

#include "sdk.h"
#include "registers/regsdcp.h"

#define HW_DCP_CHnCMDPTR_WR(ch, v)	(((ch) == 0) ? HW_DCP_CH0CMDPTR_WR((v)) : \
					((ch) == 1) ? HW_DCP_CH1CMDPTR_WR((v)): \
					((ch) == 2) ? HW_DCP_CH2CMDPTR_WR((v)): \
					HW_DCP_CH3CMDPTR_WR((v)))

#define HW_DCP_CHnSEMA_WR(ch, v)	(((ch) == 0) ? HW_DCP_CH0SEMA_WR((v)) : \
                                        ((ch) == 1) ? HW_DCP_CH1SEMA_WR((v)): \
                                        ((ch) == 2) ? HW_DCP_CH2SEMA_WR((v)): \
                                        HW_DCP_CH3SEMA_WR((v)))


typedef enum {
    DCP_CHANNEL_1 = 0,
    DCP_CHANNEL_2,
    DCP_CHANNEL_3,
    DCP_CHANNEL_4,
    DCP_CHANNEL_MAX,
} dcp_channel_e;

//! Data struture for DCP's work packet
typedef struct {
    uint32_t* next_pkt;
    hw_dcp_packet1_t ctrl0;
    hw_dcp_packet2_t ctrl1;
    uint8_t *src_buf;
    uint8_t *dst_buf;
    uint32_t buf_size;
    uint8_t *payload;
    uint32_t stat;
} dcp_work_pkt_t, *dcp_work_pkt_p;

int dcp_init(void);
int dcp_deinit(void);
int dcp_config_channel(uint32_t ch, dcp_work_pkt_p pkt_list);
int dcp_start_channel(uint32_t ch, uint32_t pkt_num);
int dcp_wait_channel_cmpl(uint32_t ch);
int dcp_memcpy(void* dst, void* src, uint32_t size);

#endif
