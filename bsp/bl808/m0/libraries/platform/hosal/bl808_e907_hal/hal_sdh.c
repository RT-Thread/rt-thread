/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdio.h>
#include <hal/soc/sd.h>
#include "bl_sdh.h"
#include "hal_sdh.h"

static sd_card_t gSDCardInfo;
static uint32_t sdio_bus_width = SDH_DATA_BUS_WIDTH_1BIT;

int32_t hal_sd_init(sd_dev_t *sd)
{
    static uint8_t inited = 0;

    if (inited == 0) {
        if (SDH_Init(sdio_bus_width, &gSDCardInfo) == SD_OK) {
            inited = 1;
            return 0;
        } else {
            return -1;
        }
    }

    return 0;
}

void hal_sd_bus_4bits_enable()
{
    sdio_bus_width = SDH_DATA_BUS_WIDTH_4BITS;
}

int32_t hal_sd_stat_get(sd_dev_t *sd, hal_sd_stat *stat)
{
    *stat = SD_STAT_TRANSFER;
    return 0;
}

int32_t hal_sd_blks_read(sd_dev_t *sd, uint8_t *data, uint32_t blk_addr, uint32_t blks, uint32_t timeout)
{
    if (SD_OK == SDH_ReadMultiBlocks(data, blk_addr, gSDCardInfo.blockSize, blks)) {
        return 0;
    } else {
        return -1;
    }
}

int32_t hal_sd_blks_write(sd_dev_t *sd, uint8_t *data, uint32_t blk_addr, uint32_t blks, uint32_t timeout)
{
    if (SD_OK == SDH_WriteMultiBlocks(data, blk_addr, gSDCardInfo.blockSize, blks)) {
        return 0;
    } else {
        return -1;
    }
}

int32_t hal_sd_info_get(sd_dev_t *sd, hal_sd_info_t *info)
{

    info->blk_nums = gSDCardInfo.blockCount;
    info->blk_size = gSDCardInfo.blockSize;

    return 0;
}

