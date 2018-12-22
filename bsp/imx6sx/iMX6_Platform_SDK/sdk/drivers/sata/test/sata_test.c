/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
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

#include <stdio.h>
#include <stdlib.h>

#include "sata/imx_sata.h"

const char g_sata_test_name[] = "SATA Test";

//extern sata_ahci_regs_t *imx_sata_host;
//extern sata_port_regs_t *imx_sata_port0;
extern void sata_clock_disable(void);
extern void sata_power_off(void);

static void fill_buffer(u32 buff, u32 size_in_byte);

void fill_buffer(u32 buff, u32 size_in_byte)
{
    u32 *ptr = (u32 *) buff;
    int i;

    ptr[0] = 0x80108010;
    ptr[1] = 0x91219121;

    for (i = 2; i < (size_in_byte / 4); i++) {
        ptr[i] = ptr[i - 1] + ptr[i - 2];
    }
}

test_return_t sata_test(void)
{
    sata_return_t ret;
    uint8_t sel;

    ret = sata_init();

    if (ret == SATA_FAIL) {
        goto error_handler;
    }

    ret = sata_identify(PORT0);

    if (ret == SATA_FAIL) {
        goto error_handler;
    }
    printf("SATA identify test passed\n");

    printf("Do you want to perform a write/read access to a disk?");
    printf("  y or Y - yes\n");
    printf("  any other key to exit.\n\n");

    do {
        sel = getchar();
    } while (sel == NONE_CHAR);

    if((sel == 'Y') || (sel == 'y'))
    {
        u32 i = 0;
        static u8 wr_buf[SATA_HDD_SECTOR_SIZE];
        static u8 rd_buf[SATA_HDD_SECTOR_SIZE];

        fill_buffer((u32) wr_buf, SATA_HDD_SECTOR_SIZE);
        printf("SATA fill buffer\n");
        ret = sata_disk_write_sector(0, wr_buf, SATA_HDD_SECTOR_SIZE, PORT0);
        printf("SATA write disk,result is %d\n", ret);
        if (ret == SATA_FAIL) {
            goto error_handler;
        }

        memset(rd_buf, 0x00, SATA_HDD_SECTOR_SIZE);
        ret = sata_disk_read_sector(0, rd_buf, SATA_HDD_SECTOR_SIZE, PORT0);
        printf("SATA read disk,result is %d\n", ret);
        if (ret == SATA_FAIL) {
            goto error_handler;
        }

        while (i < SATA_HDD_SECTOR_SIZE) {
            if (rd_buf[i] != wr_buf[i]) {
                goto error_handler;
            }
            i++;
        }
    }

    sata_clock_disable();
    sata_power_off();
    printf("SATA test passed\n");
    return TEST_PASSED;

  error_handler:
    printf("SATA test failed\n");
    return TEST_FAILED;

}

#if 0
test_return_t sata_test(void)
{
    sata_return_t ret;
    uint8_t sel;

    ret = sata_init(imx_sata_host);

    if (ret == SATA_FAIL) {
        goto error_handler;
    }

    ret = sata_identify(imx_sata_host, (u32) imx_sata_port0);

    if (ret == SATA_FAIL) {
        goto error_handler;
    }
    printf("SATA identify test passed\n");

    printf("Do you want to perform a write/read access to a disk?");
    printf("  y or Y - yes\n");
    printf("  any other key to exit.\n\n");

    do {
        sel = getchar();
    } while (sel == NONE_CHAR);

    if((sel == 'Y') || (sel == 'y'))
    {
        u32 i = 0;
        static u8 wr_buf[SATA_HDD_SECTOR_SIZE];
        static u8 rd_buf[SATA_HDD_SECTOR_SIZE];

        fill_buffer((u32) wr_buf, SATA_HDD_SECTOR_SIZE);
        printf("SATA fill buffer\n");
        ret = sata_disk_write_sector(0, wr_buf, SATA_HDD_SECTOR_SIZE);
        printf("SATA write disk,result is %d\n", ret);
        if (ret == SATA_FAIL) {
            goto error_handler;
        }

        memset(rd_buf, 0x00, SATA_HDD_SECTOR_SIZE);
        ret = sata_disk_read_sector(0, rd_buf, SATA_HDD_SECTOR_SIZE);
        printf("SATA read disk,result is %d\n", ret);
        if (ret == SATA_FAIL) {
            goto error_handler;
        }

        while (i < SATA_HDD_SECTOR_SIZE) {
            if (rd_buf[i] != wr_buf[i]) {
                goto error_handler;
            }
            i++;
        }
    }

    sata_clock_disable();
    sata_power_off();
    printf("SATA test passed\n");
    return TEST_PASSED;

  error_handler:
    printf("SATA test failed\n");
    return TEST_FAILED;

}
#endif 
