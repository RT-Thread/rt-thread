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

#include <string.h>
#include <stdio.h>

#include "ecspi.h"
#include "sdma/sdma.h"
#include "sdma_event.h"
#include "sdma_test.h"
#include "sdk.h"

#define SPI_LOOPBACK_TEST_BUF_SZ 	1024

/* Uncacheable & unbufferable area start */
static uint32_t src_buf[SPI_LOOPBACK_TEST_BUF_SZ];
static uint32_t dst_buf[SPI_LOOPBACK_TEST_BUF_SZ];

static char env_buffer[SDMA_ENV_BUF_SIZE];
static sdma_bd_t bd[2];
/* Uncacheable & unbufferable area end */

static void ecspi_access_config(void)
{
/*    *(volatile int *)(AIPS2_BASE_ADDR + 0x40) = 0;
    *(volatile int *)(AIPS2_BASE_ADDR + 0x44) = 0;
    *(volatile int *)(AIPS2_BASE_ADDR + 0x48) = 0;
    *(volatile int *)(AIPS2_BASE_ADDR + 0x4C) = 0;
    *(volatile int *)(AIPS2_BASE_ADDR + 0x50) = 0;
*/
    /* Set all MPROTx to be non-bufferable, trusted for R/W, not forced to user-mode. */
    *(volatile int *)(AIPS1_BASE_ADDR) = 0x77777777;
    *(volatile int *)(AIPS1_BASE_ADDR + 0x04) = 0x77777777;

    *(volatile int *)(AIPS2_BASE_ADDR) = 0x77777777;
    *(volatile int *)(AIPS2_BASE_ADDR + 0x04) = 0x77777777;

    /*Set all OPACRx to be non-buuferable, writable, accessible for non-trusted master */
    *(volatile int *)(AIPS1_BASE_ADDR + 0x40) = 0;
    *(volatile int *)(AIPS1_BASE_ADDR + 0x44) = 0;
    *(volatile int *)(AIPS1_BASE_ADDR + 0x48) = 0;
    *(volatile int *)(AIPS1_BASE_ADDR + 0x4C) = 0;
    *(volatile int *)(AIPS1_BASE_ADDR + 0x50) = 0;

    *(volatile int *)(AIPS2_BASE_ADDR + 0x40) = 0;
    *(volatile int *)(AIPS2_BASE_ADDR + 0x44) = 0;
    *(volatile int *)(AIPS2_BASE_ADDR + 0x48) = 0;
    *(volatile int *)(AIPS2_BASE_ADDR + 0x4C) = 0;
    *(volatile int *)(AIPS2_BASE_ADDR + 0x50) = 0;
}

int ecspi_app_test(void)
{
    int idx, channel[2];
    sdma_chan_desc_t cd[2];
    ecspi_reg_p cspi2_reg_base;

    printf("eCSPI2 loopback test starts...\n");

    cspi2_reg_base = (ecspi_reg_p) ECSPI2_BASE_ADDR;

    MEM_VIRTUAL_2_PHYSICAL(src_buf, sizeof(src_buf), MEM_PRO_UNCACHEABLE | MEM_PRO_UNBUFFERABEL);
    MEM_VIRTUAL_2_PHYSICAL(dst_buf, sizeof(dst_buf), MEM_PRO_UNCACHEABLE | MEM_PRO_UNBUFFERABEL);
    MEM_VIRTUAL_2_PHYSICAL(env_buf, sizeof(env_buffer), MEM_PRO_UNCACHEABLE | MEM_PRO_UNBUFFERABEL);
    MEM_VIRTUAL_2_PHYSICAL(bd, sizeof(bd), MEM_PRO_UNCACHEABLE | MEM_PRO_UNBUFFERABEL);

    /* Initialize buffer for testing */
    memset(src_buf, 0x5A, sizeof(src_buf));
    memset(dst_buf, 0x00, sizeof(dst_buf));

    /* Enable SDMA access to eCSPI2 */
    ecspi_access_config();

    /* Initialize SDMA */
    printf("Initialize SDMA environment.\n");
    if (SDMA_RETV_SUCCESS != sdma_init((uint32_t *)env_buffer, SDMA_IPS_HOST_BASE_ADDR)) {
        printf("SDMA initialization failed.\n");
        return FALSE;
    }

    /* CSPI Tx DMA setup */
    uint32_t script_addr;
    if (SDMA_RETV_SUCCESS != sdma_lookup_script(SDMA_MCU_2_APP, &script_addr)) {
        printf("Invalid script.\n");
        return FALSE;
    }
    /* channel descriptor */
    cd[0].script_addr = script_addr;
    cd[0].dma_mask[0] = 1 << SDMA_EVENT_ECSPI2_TX;
    cd[0].dma_mask[1] = 0;
    cd[0].priority = SDMA_CHANNEL_PRIORITY_LOW;
    cd[0].gpr[0] = cd[0].dma_mask[1];
    cd[0].gpr[1] = cd[0].dma_mask[0];
    cd[0].gpr[6] = (uint32_t)&cspi2_reg_base->txdata;
    cd[0].gpr[7] = 16;

    /* buffer descriptor */
    bd[0].mode = SDMA_FLAGS_BUSY | SDMA_FLAGS_WRAP | (SPI_LOOPBACK_TEST_BUF_SZ << 2);
    bd[0].buf_addr = (uint32_t)src_buf;
    bd[0].ext_buf_addr = 0;

    /* CSPI Rx DMA setup */
    if (SDMA_RETV_SUCCESS != sdma_lookup_script(SDMA_APP_2_MCU, &script_addr)) {
        printf("Invalid script.\n");
        return FALSE;
    }
    /* channel descriptor */
    cd[1].script_addr = script_addr;
    cd[1].dma_mask[0] = 1 << SDMA_EVENT_ECSPI2_RX;
    cd[1].dma_mask[1] = 0;
    cd[1].priority = SDMA_CHANNEL_PRIORITY_LOW;
    cd[1].gpr[0] = cd[1].dma_mask[1];
    cd[1].gpr[1] = cd[1].dma_mask[0];
    cd[1].gpr[6] = (uint32_t)&cspi2_reg_base->rxdata;
    cd[1].gpr[7] = 16;

    /* buffer descriptor */
    bd[1].mode = SDMA_FLAGS_BUSY | SDMA_FLAGS_WRAP | (SPI_LOOPBACK_TEST_BUF_SZ << 2);
    bd[1].buf_addr = (uint32_t)dst_buf;
    bd[1].ext_buf_addr = 0;

    /* Open Tx & Rx channels */
    for (idx = 0; idx < 2; idx++) {
        channel[idx] = sdma_channel_request(&cd[idx], &bd[idx]);
        if (channel[idx] < 0) {
            printf("Channel open failed.\n");
            return FALSE;
        } else {
            printf("Channel %d opened for transfer.\n", channel[idx]);
        }
    }

    printf("Start channels for transfer...\n");

    /* CSPI peripheral configuration */
    cspi2_reg_base->conreg = 0; //Reset module
    *(volatile uint32_t *)(CCM_BASE_ADDR + 0x78) |= 0x0C000000; //Turn on clock gate
    cspi2_reg_base->conreg = ECSPI_CONREG_EN;

    cspi2_reg_base->testreg = ECSPI_TESTREG_LBC;
    cspi2_reg_base->conreg |= ESCPI_CONREG_BL_ONEWORD | ECSPI_CONREG_CHNL0SEL |
        ECSPI_CONREG_CHNL0MD_MASTER | ECSPI_CONREG_SMC | ECSPI_CONREG_PREDIV | ECSPI_CONREG_POSTDIV;
    cspi2_reg_base->configreg = ECSPI_CONFIG_CHNL0SSCTL;
    cspi2_reg_base->dmareg = (ECSPI_DMA_RXDEN | (3 << ECSPI_DMA_RXTHR_SHIFT)) |
        (ECSPI_DMA_TXDEN | (32 << ECSPI_DMA_TXTHR_SHIFT));

    /* Start Tx & Rx channels */
    sdma_channel_start(channel[0]);
    sdma_channel_start(channel[1]);

    /* Wait for channels complete */
    uint32_t status;
    do {
        sdma_channel_status(channel[0], &status);
    } while (!(status & SDMA_CHANNEL_STATUS_DONE));

    do {
        sdma_channel_status(channel[1], &status);
    } while (!(status & SDMA_CHANNEL_STATUS_DONE));

    /* Stop channels */
    sdma_channel_stop(channel[0]);
    sdma_channel_stop(channel[1]);

    sdma_channel_release(channel[0]);
    sdma_channel_release(channel[1]);

    sdma_deinit();

    printf("Transfer completed. Verify data...\n");

    for (idx = 0; idx < SPI_LOOPBACK_TEST_BUF_SZ; idx++) {
        if (src_buf[idx] != dst_buf[idx]) {
            printf("Word %d mismatch: 0x%x, 0x%x\n", idx + 1, src_buf[idx], dst_buf[idx]);
            return FALSE;
        }
    }

    return TRUE;
}

int ecspi_shp_test(void)
{
    int idx, channel[2];
    sdma_chan_desc_t cd[2];
    ecspi_reg_p cspi1_reg_base;

    printf("eCSPI1 loopback test starts...\n");

    cspi1_reg_base = (ecspi_reg_p) (ECSPI1_BASE_ADDR);

    MEM_VIRTUAL_2_PHYSICAL(src_buf, sizeof(src_buf), MEM_PRO_UNCACHEABLE | MEM_PRO_UNBUFFERABEL);
    MEM_VIRTUAL_2_PHYSICAL(dst_buf, sizeof(dst_buf), MEM_PRO_UNCACHEABLE | MEM_PRO_UNBUFFERABEL);
    MEM_VIRTUAL_2_PHYSICAL(env_buf, sizeof(env_buffer), MEM_PRO_UNCACHEABLE | MEM_PRO_UNBUFFERABEL);
    MEM_VIRTUAL_2_PHYSICAL(bd, sizeof(bd), MEM_PRO_UNCACHEABLE | MEM_PRO_UNBUFFERABEL);

    /* Initialize buffers for testing */
    memset(src_buf, 0x5A, sizeof(src_buf));
    memset(dst_buf, 0x00, sizeof(dst_buf));

    /* Initialize SDMA */
    printf("Initialize SDMA environment.\n");
    if (SDMA_RETV_SUCCESS != sdma_init((uint32_t *)env_buffer, SDMA_IPS_HOST_BASE_ADDR)) {
        printf("SDMA initialization failed.\n");
        return FALSE;
    }

    /* CSPI Tx DMA setup */
    uint32_t script_addr;
    if (SDMA_RETV_SUCCESS != sdma_lookup_script(SDMA_MCU_2_SHP, &script_addr)) {
        printf("Invalid script.\n");
        return FALSE;
    }
    /* channel descriptor */
    cd[0].script_addr = script_addr;
    cd[0].dma_mask[0] = 1 << SDMA_EVENT_ECSPI1_TX;
    cd[0].dma_mask[1] = 0;
    cd[0].priority = SDMA_CHANNEL_PRIORITY_LOW;
    cd[0].gpr[0] = cd[0].dma_mask[1];
    cd[0].gpr[1] = cd[0].dma_mask[0];
    cd[0].gpr[6] = (uint32_t)&cspi1_reg_base->txdata;
    cd[0].gpr[7] = 16;

    /* buffer descriptor */
    bd[0].mode = SDMA_FLAGS_BUSY | SDMA_FLAGS_WRAP | (SPI_LOOPBACK_TEST_BUF_SZ << 2);
    bd[0].buf_addr = (uint32_t)src_buf;
    bd[0].ext_buf_addr = 0;

    /* CSPI Rx DMA setup */
    if (SDMA_RETV_SUCCESS != sdma_lookup_script(SDMA_SHP_2_MCU, &script_addr)) {
        printf("Invalid script.\n");
        return FALSE;
    }
    /* channel descriptor */
    cd[1].script_addr = script_addr;
    cd[1].dma_mask[0] = 1 << SDMA_EVENT_ECSPI1_RX;
    cd[1].dma_mask[1] = 0;
    cd[1].priority = SDMA_CHANNEL_PRIORITY_LOW;
    cd[1].gpr[0] = cd[1].dma_mask[1];
    cd[1].gpr[1] = cd[1].dma_mask[0];
    cd[1].gpr[6] = (uint32_t)&cspi1_reg_base->rxdata;
    cd[1].gpr[7] = 16;

    /* buffer descriptor */
    bd[1].mode = SDMA_FLAGS_BUSY | SDMA_FLAGS_WRAP | (SPI_LOOPBACK_TEST_BUF_SZ << 2);
    bd[1].buf_addr = (uint32_t)dst_buf;
    bd[1].ext_buf_addr = 0;

    /* Open Tx & Rx channels */
    for (idx = 0; idx < 2; idx++) {
        channel[idx] = sdma_channel_request(&cd[idx], &bd[idx]);
        if (channel[idx] < 0) {
            printf("Channel open failed.\n");
            return FALSE;
        } else {
            printf("Channel %d opened for transfer.\n", channel[idx]);
        }
    }

    printf("Start channel for transfer...\n");

    /* CSPI peripheral configuration */
    *(volatile uint32_t *)(CCM_BASE_ADDR + 0x78) |= 0x0C000000; //Turn on clock gate
    cspi1_reg_base->conreg = 0; //Reset module
    cspi1_reg_base->conreg = ECSPI_CONREG_EN;

    cspi1_reg_base->testreg = ECSPI_TESTREG_LBC;
    cspi1_reg_base->conreg |= ESCPI_CONREG_BL_ONEWORD | ECSPI_CONREG_CHNL0SEL |
        ECSPI_CONREG_CHNL0MD_MASTER | ECSPI_CONREG_SMC | ECSPI_CONREG_PREDIV | ECSPI_CONREG_POSTDIV;
    cspi1_reg_base->configreg = ECSPI_CONFIG_CHNL0SSCTL;
    cspi1_reg_base->dmareg = (ECSPI_DMA_RXDEN | (3 << ECSPI_DMA_RXTHR_SHIFT)) |
        (ECSPI_DMA_TXDEN | (32 << ECSPI_DMA_TXTHR_SHIFT));

    /* Start Tx & Rx channels */
    sdma_channel_start(channel[0]);
    sdma_channel_start(channel[1]);

    uint32_t status;
    do {
        sdma_channel_status(channel[0], &status);
    } while (!(status & SDMA_CHANNEL_STATUS_DONE));

    do {
        sdma_channel_status(channel[1], &status);
    } while (!(status & SDMA_CHANNEL_STATUS_DONE));

    /* Stop channels */
    sdma_channel_stop(channel[0]);
    sdma_channel_stop(channel[1]);

    sdma_channel_release(channel[0]);
    sdma_channel_release(channel[1]);

    sdma_deinit();

    printf("Transfer completed. Verify data...\n");

    for (idx = 0; idx < SPI_LOOPBACK_TEST_BUF_SZ; idx++) {
        if (src_buf[idx] != dst_buf[idx]) {
            printf("Word %d mismatch: 0x%x, 0x%x\n", idx + 1, src_buf[idx], dst_buf[idx]);
            return FALSE;
        }
    }

    return TRUE;
}
