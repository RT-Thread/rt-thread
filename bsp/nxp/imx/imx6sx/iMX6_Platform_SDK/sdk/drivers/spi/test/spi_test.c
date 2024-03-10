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
#include "spi_test.h"
#include "sdk.h"
#include "spi_nor_numonyx.h"
#include "spi/ecspi_ifc.h"
#include "registers/regsiomuxc.h"

static int numonyx_spi_nor_test(void);

static struct chip_id numonyx_chip_id = {
    .id0 = 0x16,
    .id1 = 0x20,
    .id2 = 0x20
};

static spi_test_t spi_tests[] = {
    {"NUMONYX SPI NOR", numonyx_spi_nor_test},
};

dev_ecspi_e dev_spi_nor;

static uint32_t src_buf[TEST_BUF_SZ];
static uint32_t dst_buf[TEST_BUF_SZ];

static int numonyx_spi_nor_test(void)
{
    uint8_t id[4];
    uint32_t retv, idx, len = TEST_BUF_SZ * sizeof(uint32_t);

#if defined(BOARD_SABRE_AI) && !defined(BOARD_REV_A) 
    printf("Please remove the jumper within J3 on the board.\n");
    if(!is_input_char('y', NULL))
	return FALSE;

    HW_IOMUXC_SW_MUX_CTL_PAD_EIM_ADDR24_WR(
    		BF_IOMUXC_SW_MUX_CTL_PAD_EIM_ADDR24_MUX_MODE_V(ALT5));
    gpio_set_direction(GPIO_PORT5, 4, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT5, 4, GPIO_LOW_LEVEL);
#endif

    // eCSPI device setup 
    dev_spi_nor = DEV_ECSPI1;
    
    param_ecspi_t numonyxParams = NUMONYX_INIT_PARAM;

    // Init eCSPI 
    ecspi_open(dev_spi_nor, &numonyxParams);

    // Query Numonyx chip ID 
    if (spi_nor_query_numonyx((uint8_t *) id) == FAIL) {
        printf("Chip ID query FAIL.\n");
        return FALSE;
    }

    // Verify chip ID 
    if ((id[0] == numonyx_chip_id.id0) &&
        (id[1] == numonyx_chip_id.id1) && (id[2] == numonyx_chip_id.id2)) {
        printf("Chip ID checking PASS.\n");
    } else {
        printf("Chip ID checking FAIL.\n");
        return FALSE;
    }

    // Setup src & dst buffer 
    for (idx = 0; idx < TEST_BUF_SZ; idx++) {
        src_buf[idx] = idx + TEST_SRC_VAL;
    }

    memset((void *)dst_buf, 0x0, len);

    // Erase flash 
    if (spi_nor_erase_numonyx(0, TEST_ERASE_SZ) == FAIL) {
        printf("Flash erase FAIL.\n");
        return FALSE;
    } else {
        printf("Flash erase SUCCESS.\n");
    }

    // Program flash 
    if (spi_nor_write_numonyx(0, (void *)src_buf, len) == FAIL) {
        printf("Flash write FAIL.\n");
        return FALSE;
    } else {
        printf("Flash write SUCCESS.\n");
    }

    // Reset eCSPI controller 
    ecspi_configure(dev_spi_nor, &numonyxParams);

    // Read back flash 
    if (spi_nor_read_numonyx(0, (void *)dst_buf, len) == FAIL) {
        printf("Flash read FAIL.\n");
        return FALSE;
    } else {
        printf("Flash read SUCCESS.\n");
    }

    // Compare src & dst 
    for (retv = TRUE, idx = 0; ((idx < TEST_BUF_SZ) && retv == TRUE); idx++) {
        if (dst_buf[idx] != src_buf[idx]) {
            printf("[%d] mismatch: src - %d, dst - %d\n", idx, src_buf[idx], dst_buf[idx]);
            retv = FALSE;
        }
    }

    if (retv == TRUE) {
        printf("Data comparation PASS.\n");
    } else {
        printf("Data comparation FAIL.\n");
    }

    // Close eCSPI 
    ecspi_close(dev_spi_nor);

    return retv;
}

int spi_test(void)
{
    int retv=SUCCESS, idx;
    char sel;

    printf("\n---- Running eCSPI test, type 'x' to exit.\n");

    do {
        printf("Please select test:\n");
        for (idx = 0; idx < (sizeof(spi_tests) / sizeof(spi_test_t)); idx++) {
            printf("\t%d - %s\n", idx, spi_tests[idx].name);
        }
        printf("\tx - to exit.\n");

        do {
            sel = getchar();
        } while (sel == (char)0xFF);

        if (sel == 'x') {
            printf("\nTest exit.\n");
            break;
        }

        idx = sel - '0';

        if ((idx >= 0) && (idx < (sizeof(spi_tests) / sizeof(spi_test_t)))) {
            printf("\n");
            retv = spi_tests[idx].test();
            if (retv == TRUE) {
                printf("\n%s test PASSED.\n\n", spi_tests[idx].name);
            } else {
                printf("\n%s test FAILED.\n\n", spi_tests[idx].name);
            }
        }
    } while (TRUE);

    return retv;
}
