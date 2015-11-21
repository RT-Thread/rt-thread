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
#include "sdk.h"
#include "cfi_flash.h"
#include "eim/eim_ifc.h"

#define EIM_BUFFER_SZ 0x1000
extern flash_info_t flash_info[];
static uint32_t eim_test_buffer[EIM_BUFFER_SZ];

static void eim_hw_prepare(void)
{
    /* Init EIM */
    eim_init(EIM_CS0, DSZ_16_HIGH, FALSE, FALSE);

    /* Nor flash */
    eim_cfg_set(EIM_CS0, GCR1_CREP, TRUE);

    /* Address hold time */
    eim_cfg_set(EIM_CS0, GCR2_ADH, 1);

    /* Bypass grant(only for Muxed 16) */
    eim_cfg_set(EIM_CS0, GCR2_MUX16_BYP_GRANT, FALSE);

    /* ADV navigation */
    eim_cfg_set(EIM_CS0, RCR1_RADVN, 2);

    /* OE assertion */
    eim_cfg_set(EIM_CS0, RCR1_OEA, 0);

    /* Read wait state control */
    eim_cfg_set(EIM_CS0, RCR1_RWSC, 28);

    /* WE negation */
    eim_cfg_set(EIM_CS0, WCR1_WEN, 1);

    /* WE assertion */
    eim_cfg_set(EIM_CS0, WCR1_WEA, 1);

    /* BE negation */
    eim_cfg_set(EIM_CS0, WCR1_WBEN, 2);

    /* BE assertion */
    eim_cfg_set(EIM_CS0, WCR1_WBEA, 1);

    /* ADV Negation */
    eim_cfg_set(EIM_CS0, WCR1_WADVN, 1);

    /* Write wait state control */
    eim_cfg_set(EIM_CS0, WCR1_WWSC, 8);
}

static int eim_nor_test(void)
{
    uint32_t idx, retv, size, start, end, *data;
    int32_t count, first[CFG_MAX_FLASH_BANKS], last[CFG_MAX_FLASH_BANKS];
    flash_info_t *info = flash_info;

    /* Prepare buffer */
    for (idx = 0; idx < EIM_BUFFER_SZ; idx++) {
        eim_test_buffer[idx] = idx + 0x5A5A0000;
    }
#if defined(BOARD_SABRE_AI)
    // for EIM_D18 steering
    gpio_set_level(GPIO_PORT5, 4, GPIO_LOW_LEVEL);
#endif
    /* HW init */
    eim_hw_prepare();

    /* Reset flash to read mode */
    flash_reset(WEIM_CS_BASE_ADDR);

    /* Initialize flash */
    size = flash_init(WEIM_CS_BASE_ADDR);
    if ((size == 0) || (info->flash_id == FLASH_UNKNOWN)) {
        printf("Error: Missing or Unknown FLASH type.\n");
        return ERR;
    } else {
        printf("Flash size: 0x%8x\n", size);
    }

    start = WEIM_CS_BASE_ADDR;
    end = start + size - 1;

    /* Obtain sector info */
    retv = flash_fill_sect_ranges(start, end, first, last, &count);
    if (retv == OK) {
        /* Unprotect */
        retv = flash_sects_protect(0, first, last);
        if (retv == OK) {
            /* Erase sectors */
            printf("Flash erase...\n");
            retv = flash_sects_erase(first, first);
            if (retv == OK) {
                if (*(uint16_t *) start != 0xFFFF) {
                    retv = ERR;
                    printf("Error: erased data not 0xFFFF.");
                } else {
                    /* Program data */
                    printf("\nFlash program...\n");
                    retv = flash_write((uint8_t *) eim_test_buffer,
                                       start, EIM_BUFFER_SZ * sizeof(uint32_t));
                }
            }
        }

        /* Protect */
        if (retv == OK) {
            retv = flash_sects_protect(1, first, last);
        }
    }

    /* Compare data */
    if (retv == OK) {
        printf("Data compare...\n");
        for (idx = 0, data = (uint32_t *) start; idx < EIM_BUFFER_SZ; idx++) {
            if (eim_test_buffer[idx] != data[idx]) {
                printf("[%d] Data mismatch: 0x%8x, 0x%8x\n", idx, eim_test_buffer[idx], data[idx]);
                retv = ERR;
                break;
            }
        }
    }

    return retv;
}

int eim_test(void)
{
    uint8_t sel, retv;

    printf("EIM test start: \n");

    do {
        printf("  s - to start EIM NOR flash test.\n");
        printf("  x - to exit.\n");

        do {
            sel = getchar();
        } while (sel == NONE_CHAR);

        if (sel == 'x') {
            printf("Test exit.\n");
            break;
        }

        if (sel == 's') {
            retv = eim_nor_test();
            if (retv == OK) {
                printf("Test passed.\n");
            } else {
                printf("Test failed.\n");
            }
        }
    } while (1);

    return 0;
}
