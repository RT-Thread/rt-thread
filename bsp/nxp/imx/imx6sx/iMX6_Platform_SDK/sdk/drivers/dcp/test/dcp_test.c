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

#include "sdk.h"
#include "../dcp.h"
#include "profile/profile.h"

#define DCP_TEST_BUFFER_SIZE	0x1000000

int dcp_test(void)
{
    uint8_t *dst;
    uint8_t *dst_ptr;
    uint8_t *src;
    uint8_t *src_ptr;
    int i;
    int res = 0;
    uint8_t ch;

    printf("\n---- Running DCP memcopy test. Type 'Y/y' to continue.\n");

    do {
        ch = getchar();
    } while (ch == (uint8_t) 0xFF);

    if ((ch != 'Y') && (ch != 'y')) {
        printf("\nTest exit.\n");
        return -1;
    }

    dst = (uint8_t *) malloc(DCP_TEST_BUFFER_SIZE);
    if (dst == NULL) {
        printf("Malloc dst buffer failed.\n");
        return -1;
    }
    src = (uint8_t *) malloc(DCP_TEST_BUFFER_SIZE);
    if (src == NULL) {
        printf("Malloc src buffer failed.\n");
        free(dst);
        return -2;
    }

    memset(dst, 0x0, DCP_TEST_BUFFER_SIZE);
    memset(src, 0x5a, DCP_TEST_BUFFER_SIZE);

    printf("Moving %d bytes from 0x%08x to 0x%08x\n", DCP_TEST_BUFFER_SIZE, (uint32_t) src, (uint32_t) dst);

    dcp_init();

    uint32_t perf_cnt = 0;

    StartPerfCounter();
    dcp_memcpy(dst, src, DCP_TEST_BUFFER_SIZE);
    perf_cnt = StopPerfCounter();

    float interval = ((float)(perf_cnt)) / ((float)get_main_clock(CPU_CLK));
    float speed = (float)(DCP_TEST_BUFFER_SIZE) / 1024.0f / interval;
    printf("memory copy data rate using dcp_memcpy: %d KB/s\n", (int)speed);

    printf("Verifying....\n");
    for (i = 0, dst_ptr = dst, src_ptr = src; i < DCP_TEST_BUFFER_SIZE; i++, dst_ptr++, src_ptr++) {
        if (*dst_ptr != *src_ptr) {
            res = -3;
            break;
        }
    }

    if (res == 0)
        printf("Verified and data match.\n");
    else
        printf("Data dismatch at 0x%08x, 0x%02x expected but 0x%02x\n", (uint32_t) dst_ptr,
               *src_ptr, *dst_ptr);

    dcp_deinit();

    free(dst);
    free(src);

    return res;
}
