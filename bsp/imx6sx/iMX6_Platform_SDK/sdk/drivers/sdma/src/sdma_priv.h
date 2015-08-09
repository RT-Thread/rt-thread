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
 * @file sdma_priv.h
 * @brief Private header for SDMA library
 */

#ifndef SDMA_PRIV_H
#define SDMA_PRIV_H

#include "sdk.h"
#include "sdma_script_info.h"
#include "sdma/sdma.h"

/*--------------------------------- macros --------------------------------------*/

#define SDMA_SCRATCH_ENABLE

#define SDMA_NUM_CHANNELS 32
#define SDMA_NUM_REQUESTS 48
#define SDMA_NUM_BUF_DESC 64

#define SDMA_REG_RESET_BIT_RESET	(1<<0)
#define SDMA_REG_RESET_BIT_RESCHED	(1<<1)

#define SDMA_REG_CONFIG_VAL_ACR_TWICE	(0<<4)
#define SDMA_REG_CONFIG_VAL_ACR_ONCE	(1<<4)

#define SDMA_REG_CHN0ADDR_BIT_SMSZ	(1<<14)

#define SDMA_CHANNEL_PRIORITY_FREE	0
#define SDMA_CHANNEL_PRIORITY_LOW	1
#define SDMA_CHANNEL_PRIORITY_HIGH	7

#define SDMA_CMD_C0_SET_DM              0x01
#define SDMA_CMD_C0_SET_PM              0x04
#define SDMA_CMD_C0_GET_DM              0x02
#define SDMA_CMD_C0_GET_PM              0x06
#define SDMA_CMD_C0_SETCTX              0x07
#define SDMA_CMD_C0_GETCTX              0x03

#define SDMA_BD_MODE_CMD_SHIFT		24
#define SDMA_BD_MODE_CNT_MASK		0xFFFF

#define SDMA_RAMSCRIPT_CODE_START	0x1800

#define CHANNEL_STOP_STAT(channel) (sdma_base->stop_stat & (1<<channel))

/*-------------------------------- structures -------------------------------------*/

typedef struct {
    unsigned int pc_rpc;
    unsigned int spc_epc;
    unsigned int gr[8];
    unsigned int mda;
    unsigned int msa;
    unsigned int ms;
    unsigned int md;
    unsigned int pda;
    unsigned int psa;
    unsigned int ps;
    unsigned int pd;
    unsigned int ca;
    unsigned int cs;
    unsigned int dda;
    unsigned int dsa;
    unsigned int ds;
    unsigned int dd;
#ifdef SDMA_SCRATCH_ENABLE
    unsigned int scratch[8];
#endif
} sdma_channel_context_t, *sdma_channel_context_p;

typedef struct {
    unsigned int currentBDptr;
    unsigned int baseBDptr;
    unsigned int chanDesc;
    unsigned int status;
} sdma_ccb_t, *sdma_ccb_p;

typedef struct {
    sdma_ccb_t sdma_ccb[SDMA_NUM_CHANNELS]; //channel control block
    sdma_bd_p sdma_bdp[SDMA_NUM_CHANNELS];
    unsigned int sdma_bd_num[SDMA_NUM_CHANNELS];
    sdma_channel_context_t chan_cnxt;   //as the buf to load channel's context to sdma core
    sdma_bd_t chan0BD;          //channel 0 buffer descriptor reserved buffer
} sdma_env_t, *sdma_env_p;


#endif
