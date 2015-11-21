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
 * @file sdma.h
 * @brief SDMA library macros, structures and functions 
 */
#ifndef SDMA_H
#define SDMA_H
#include "sdk.h"
/*--------------------------------- macros --------------------------------------*/
#define SDMA_ENV_BUF_SIZE		0x800
#define SDMA_CHANNEL_PRIORITY_FREE	0
#define SDMA_CHANNEL_PRIORITY_LOW	1
#define SDMA_CHANNEL_PRIORITY_HIGH	7

//! @brief List of scripts' names.
typedef enum {
    SDMA_AP_2_AP = 0,
    SDMA_APP_2_MCU,
    SDMA_MCU_2_APP,
    SDMA_UART_2_MCU,
    SDMA_SHP_2_MCU,
    SDMA_MCU_2_SHP,
    SDMA_SPDIF_2_MCU,
    SDMA_MCU_2_SPDIF,
    SDMA_FIRI_2_MCU,
    SDMA_MCU_2_FIRI,
    SDMA_MCU_2_SSIAPP,
    SDMA_MCU_2_SSISH,
    SDMA_P_2_P,
    SDMA_SSIAPP_2_MCU,
    SDMA_SSISH_2_MCU,
    SDMA_NUM_SCRIPTS
} script_name_e;

//! @brief SDMA buffer descriptor modes.
typedef enum {
    SDMA_FLAGS_BUSY = (1 << 16),
    SDMA_FLAGS_WRAP = (1 << 17),
    SDMA_FLAGS_CONT = (1 << 18),
    SDMA_FLAGS_INTR = (1 << 19),
    SDMA_FLAGS_ERROR = (1 << 20),
    SDMA_FLAGS_NFC_RD = (1 << 28),
    SDMA_FLAGS_BW8 = (1 << 24),
    SDMA_FLAGS_BW16 = (2 << 24),
    SDMA_FLAGS_BW24 = (3 << 24),
    SDMA_FLAGS_BW32 = (0 << 24)
} sdma_flag_e;

//! @brief SDMA transfer information in buffer descriptor.
typedef enum {
    SDMA_CHANNEL_STATUS_ERROR,
    SDMA_CHANNEL_STATUS_BUSY,
    SDMA_CHANNEL_STATUS_DONE
} sdma_channel_status_e;

//! @brief The return value of function.
typedef enum {
    SDMA_RETV_SUCCESS = 0,
    SDMA_RETV_FAIL = -1,
    SDMA_RETV_NULLP = -2,
    SDMA_RETV_PRIORITY = -3,
    SDMA_RETV_NO_FREE_CHANNEL = -4,
    SDMA_RETV_SET_CONTEXT = -5,
    SDMA_RETV_BD_VALIDATE = -6,
    SDMA_RETV_NOT_INITED = -7
} sdma_error_e;

//! @brief SDMA buffer descriptor structure.
typedef struct {
    uint32_t mode;          //mode word, including count, command, flag...
    uint32_t buf_addr;      //buffer address, while peripheral address in channel context
    uint32_t ext_buf_addr;  //extended buffer address, not mandatory for scripts
} sdma_bd_t, *sdma_bd_p;

//! @brief SDMA channel descriptor.
typedef struct {
    uint32_t script_addr;   //script to use
    uint32_t gpr[8];        //r0-r7, including DMA mask, watermark...
    uint32_t dma_mask[2];   //dma_mask[0]: DMA request 0-31, 1: 32-47
    uint32_t priority;     //priority of channel(0-7)
    uint32_t nbd;           //number of buffer descriptors
} sdma_chan_desc_t, *sdma_chan_desc_p;
typedef void (*sdma_channel_isr) (uint32_t);
/*--------------------------------- functions -------------------------------------*/
int32_t sdma_init(uint32_t *, uint32_t);
void sdma_deinit(void);
int32_t sdma_channel_start(uint32_t);
int32_t sdma_channel_stop(uint32_t);
int32_t sdma_channel_request(sdma_chan_desc_p, sdma_bd_p);
int32_t sdma_channel_release(uint32_t);
uint32_t sdma_channel_status(uint32_t, uint32_t *);
int32_t sdma_lookup_script(script_name_e, uint32_t *);
void sdma_setup_interrupt(void);
int32_t sdma_channel_isr_attach(uint32_t, sdma_channel_isr isr);
#endif

