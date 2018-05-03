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

/*
 * Copyright (c) 2006, Chips & Media.  All rights reserved.
 */

/*!
 * @file vpu_gdi.c
 *
 * @brief VPU GDI control
 *
 * @ingroup diag_vpu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vpu/vpu_gdi.h"
#include "vpu/vpu_util.h"
#include "vpu/vpu_debug.h"

RetCode SetTiledMapTypeInfo(GDI_TILED_MAP_TYPE TiledMapType, GdiTiledMap * pTiledInfo)
{
    int luma_map, chro_map, i;

    if (!cpu_is_mx6())
        return RETCODE_FAILURE;

    memset(pTiledInfo, 0, sizeof(GdiTiledMap));

    luma_map = 64;
    chro_map = 64;
    pTiledInfo->MapType = TiledMapType;
    for (i = 0; i < 16; i++)
        pTiledInfo->xy2ca_map[i] = luma_map << 8 | chro_map;
    for (i = 0; i < 4; i++)
        pTiledInfo->xy2ba_map[i] = luma_map << 8 | chro_map;
    for (i = 0; i < 16; i++)
        pTiledInfo->xy2ra_map[i] = luma_map << 8 | chro_map;

    if (TiledMapType == LINEAR_FRAME_MAP) {
        pTiledInfo->xy2rbc_config = 0;
    } else if (TiledMapType == TILED_FRAME_MB_RASTER_MAP) {
        pTiledInfo->xy2ca_map[0] = XY2(Y_SEL, 0, Y_SEL, 0);
        pTiledInfo->xy2ca_map[1] = XY2(Y_SEL, 1, Y_SEL, 1);
        pTiledInfo->xy2ca_map[2] = XY2(Y_SEL, 2, Y_SEL, 2);
        pTiledInfo->xy2ca_map[3] = XY2(Y_SEL, 3, X_SEL, 3);
        pTiledInfo->xy2ca_map[4] = XY2(X_SEL, 3, 4, 0);

        pTiledInfo->xy2rbc_config = XY2CONFIG(0, 0, 0, 1, 1, 15, 0, 7, 0);

    } else if (TiledMapType == TILED_FIELD_MB_RASTER_MAP) {
        pTiledInfo->xy2ca_map[0] = XY2(Y_SEL, 0, Y_SEL, 0);
        pTiledInfo->xy2ca_map[1] = XY2(Y_SEL, 1, Y_SEL, 1);
        pTiledInfo->xy2ca_map[2] = XY2(Y_SEL, 2, X_SEL, 3);
        pTiledInfo->xy2ca_map[3] = XY2(X_SEL, 3, 4, 0);

        pTiledInfo->xy2rbc_config = XY2CONFIG(0, 1, 1, 1, 1, 7, 7, 3, 3);

    } else {
        err_msg("TiledMapType is %d >-- Error\n", TiledMapType);
        return RETCODE_FAILURE;
    }

    if (TiledMapType == TILED_FRAME_MB_RASTER_MAP) {
        pTiledInfo->rbc2axi_map[0] = RBC(Z_SEL, 0, Z_SEL, 0);
        pTiledInfo->rbc2axi_map[1] = RBC(Z_SEL, 0, Z_SEL, 0);
        pTiledInfo->rbc2axi_map[2] = RBC(Z_SEL, 0, Z_SEL, 0);
        pTiledInfo->rbc2axi_map[3] = RBC(CA_SEL, 0, CA_SEL, 0);
        pTiledInfo->rbc2axi_map[4] = RBC(CA_SEL, 1, CA_SEL, 1);
        pTiledInfo->rbc2axi_map[5] = RBC(CA_SEL, 2, CA_SEL, 2);
        pTiledInfo->rbc2axi_map[6] = RBC(CA_SEL, 3, CA_SEL, 3);
        pTiledInfo->rbc2axi_map[7] = RBC(CA_SEL, 4, CA_SEL, 8);
        pTiledInfo->rbc2axi_map[8] = RBC(CA_SEL, 8, CA_SEL, 9);
        pTiledInfo->rbc2axi_map[9] = RBC(CA_SEL, 9, CA_SEL, 10);
        pTiledInfo->rbc2axi_map[10] = RBC(CA_SEL, 10, CA_SEL, 11);
        pTiledInfo->rbc2axi_map[11] = RBC(CA_SEL, 11, CA_SEL, 12);
        pTiledInfo->rbc2axi_map[12] = RBC(CA_SEL, 12, CA_SEL, 13);
        pTiledInfo->rbc2axi_map[13] = RBC(CA_SEL, 13, CA_SEL, 14);
        pTiledInfo->rbc2axi_map[14] = RBC(CA_SEL, 14, CA_SEL, 15);
        pTiledInfo->rbc2axi_map[15] = RBC(CA_SEL, 15, RA_SEL, 0);
        pTiledInfo->rbc2axi_map[16] = RBC(RA_SEL, 0, RA_SEL, 1);
        pTiledInfo->rbc2axi_map[17] = RBC(RA_SEL, 1, RA_SEL, 2);
        pTiledInfo->rbc2axi_map[18] = RBC(RA_SEL, 2, RA_SEL, 3);
        pTiledInfo->rbc2axi_map[19] = RBC(RA_SEL, 3, RA_SEL, 4);
        pTiledInfo->rbc2axi_map[20] = RBC(RA_SEL, 4, RA_SEL, 5);
        pTiledInfo->rbc2axi_map[21] = RBC(RA_SEL, 5, RA_SEL, 6);
        pTiledInfo->rbc2axi_map[22] = RBC(RA_SEL, 6, RA_SEL, 7);
        pTiledInfo->rbc2axi_map[23] = RBC(RA_SEL, 7, RA_SEL, 8);
        pTiledInfo->rbc2axi_map[24] = RBC(RA_SEL, 8, RA_SEL, 9);
        pTiledInfo->rbc2axi_map[25] = RBC(RA_SEL, 9, RA_SEL, 10);
        pTiledInfo->rbc2axi_map[26] = RBC(RA_SEL, 10, RA_SEL, 11);
        pTiledInfo->rbc2axi_map[27] = RBC(RA_SEL, 11, RA_SEL, 12);
        pTiledInfo->rbc2axi_map[28] = RBC(RA_SEL, 12, RA_SEL, 13);
        pTiledInfo->rbc2axi_map[29] = RBC(RA_SEL, 13, RA_SEL, 14);
        pTiledInfo->rbc2axi_map[30] = RBC(RA_SEL, 14, RA_SEL, 15);
        pTiledInfo->rbc2axi_map[31] = RBC(RA_SEL, 15, Z_SEL, 0);
    } else if (TiledMapType == TILED_FIELD_MB_RASTER_MAP) {
        pTiledInfo->rbc2axi_map[0] = RBC(Z_SEL, 0, Z_SEL, 0);
        pTiledInfo->rbc2axi_map[1] = RBC(Z_SEL, 0, Z_SEL, 0);
        pTiledInfo->rbc2axi_map[2] = RBC(Z_SEL, 0, Z_SEL, 0);
        pTiledInfo->rbc2axi_map[3] = RBC(CA_SEL, 0, CA_SEL, 0);
        pTiledInfo->rbc2axi_map[4] = RBC(CA_SEL, 1, CA_SEL, 1);
        pTiledInfo->rbc2axi_map[5] = RBC(CA_SEL, 2, CA_SEL, 2);
        pTiledInfo->rbc2axi_map[6] = RBC(CA_SEL, 3, CA_SEL, 8);
        pTiledInfo->rbc2axi_map[7] = RBC(CA_SEL, 8, CA_SEL, 9);
        pTiledInfo->rbc2axi_map[8] = RBC(CA_SEL, 9, CA_SEL, 10);
        pTiledInfo->rbc2axi_map[9] = RBC(CA_SEL, 10, CA_SEL, 11);
        pTiledInfo->rbc2axi_map[10] = RBC(CA_SEL, 11, CA_SEL, 12);
        pTiledInfo->rbc2axi_map[11] = RBC(CA_SEL, 12, CA_SEL, 13);
        pTiledInfo->rbc2axi_map[12] = RBC(CA_SEL, 13, CA_SEL, 14);
        pTiledInfo->rbc2axi_map[13] = RBC(CA_SEL, 14, CA_SEL, 15);
        pTiledInfo->rbc2axi_map[14] = RBC(CA_SEL, 15, RA_SEL, 0);
        pTiledInfo->rbc2axi_map[15] = RBC(RA_SEL, 0, RA_SEL, 1);
        pTiledInfo->rbc2axi_map[16] = RBC(RA_SEL, 1, RA_SEL, 2);
        pTiledInfo->rbc2axi_map[17] = RBC(RA_SEL, 2, RA_SEL, 3);
        pTiledInfo->rbc2axi_map[18] = RBC(RA_SEL, 3, RA_SEL, 4);
        pTiledInfo->rbc2axi_map[19] = RBC(RA_SEL, 4, RA_SEL, 5);
        pTiledInfo->rbc2axi_map[20] = RBC(RA_SEL, 5, RA_SEL, 6);
        pTiledInfo->rbc2axi_map[21] = RBC(RA_SEL, 6, RA_SEL, 7);
        pTiledInfo->rbc2axi_map[22] = RBC(RA_SEL, 7, RA_SEL, 8);
        pTiledInfo->rbc2axi_map[23] = RBC(RA_SEL, 8, RA_SEL, 9);
        pTiledInfo->rbc2axi_map[24] = RBC(RA_SEL, 9, RA_SEL, 10);
        pTiledInfo->rbc2axi_map[25] = RBC(RA_SEL, 10, RA_SEL, 11);
        pTiledInfo->rbc2axi_map[26] = RBC(RA_SEL, 11, RA_SEL, 12);
        pTiledInfo->rbc2axi_map[27] = RBC(RA_SEL, 12, RA_SEL, 13);
        pTiledInfo->rbc2axi_map[28] = RBC(RA_SEL, 13, RA_SEL, 14);
        pTiledInfo->rbc2axi_map[29] = RBC(RA_SEL, 14, RA_SEL, 15);
        pTiledInfo->rbc2axi_map[30] = RBC(RA_SEL, 15, Z_SEL, 0);
        pTiledInfo->rbc2axi_map[31] = RBC(Z_SEL, 0, Z_SEL, 0);
    }

    pTiledInfo->tb_separate_map = (pTiledInfo->xy2rbc_config >> 19) & 0x1;
    pTiledInfo->top_bot_split = (pTiledInfo->xy2rbc_config >> 18) & 0x1;
    pTiledInfo->tiledMap = (pTiledInfo->xy2rbc_config >> 17) & 0x1;
    pTiledInfo->ca_inc_hor = (pTiledInfo->xy2rbc_config >> 16) & 0x1;

    return RETCODE_SUCCESS;
}

void SetGDIRegs(GdiTiledMap * pTiledInfo)
{
    int i;

    for (i = 0; i < 16; i++)
        vpu_reg_write(GDI_XY2_CAS_0 + 4 * i, pTiledInfo->xy2ca_map[i]);

    for (i = 0; i < 4; i++)
        vpu_reg_write(GDI_XY2_BA_0 + 4 * i, pTiledInfo->xy2ba_map[i]);

    for (i = 0; i < 16; i++)
        vpu_reg_write(GDI_XY2_RAS_0 + 4 * i, pTiledInfo->xy2ra_map[i]);

    vpu_reg_write(GDI_XY2_RBC_CONFIG, pTiledInfo->xy2rbc_config);

    for (i = 0; i < 32; i++)
        vpu_reg_write(GDI_RBC2_AXI_0 + 4 * i, pTiledInfo->rbc2axi_map[i]);
}
