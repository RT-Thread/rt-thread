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
#ifndef __SPI_TEST_HDR__
#define __SPI_TEST_HDR__

#include "sdk.h"

#define TEST_BUF_SZ 128
#define TEST_SRC_VAL  0x3569AC00
#define TEST_ERASE_SZ (64 * 1024)

/*!  
 * Channel: SS1
 * Mode: master
 * pre_div, post_div: 2 - clock: 60M/4 = 15MHz
 */
#if defined(BOARD_SMART_DEVICE) || defined(BOARD_EVK)
#define NUMONYX_INIT_PARAM { \
    .channel = 0, \
    .mode = 1, \
    .ss_pol = 0, \
    .sclk_pol = 0, \
    .sclk_pha = 0, \
    .pre_div = 0, \
    .post_div = 2 \
    }
#else
#define NUMONYX_INIT_PARAM { \
    .channel = 1, \
    .mode = 1, \
    .ss_pol = 0, \
    .sclk_pol = 0, \
    .sclk_pha = 0, \
    .pre_div = 0, \
    .post_div = 2 \
    }
#endif
// ((uint32_t)0x00000445)

struct chip_id {
    uint8_t id0;
    uint8_t id1;
    uint8_t id2;
};

typedef struct {
    const char *name;
    int (*test) (void);
} spi_test_t;

int spi_test(void);


#endif // __SPI_TEST_HDR__
