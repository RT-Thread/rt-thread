/*
 * Copyright (c) 2010-2012, Freescale Semiconductor, Inc.
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
#include <string.h>
#include "sdk.h"
#include "ldb/ldb_def.h"
#include "ipu/ipu_common.h"
#include "registers/regsldb.h"
#include "registers/regsiomuxc.h"

/////////////////////////////////////////////////////////////////////////////
// CODE
/////////////////////////////////////////////////////////////////////////////

//! @brief select the LDB port and data source
static void ldb_set_channel_route(int ipu_port, int lvds_port)
{
    if (ipu_port == IPU1_DI0 || ipu_port == IPU2_DI0) {
        if (lvds_port == LVDS_PORT0)
            HW_LDB_CTRL.B.CH0_MODE = 1;
        else if (lvds_port == LVDS_PORT1)
            HW_LDB_CTRL.B.CH1_MODE = 1;
        else {
            HW_LDB_CTRL.B.CH0_MODE = 1;
            HW_LDB_CTRL.B.CH1_MODE = 1;
        }
    } else if (ipu_port == IPU1_DI1 || ipu_port == IPU2_DI1) {
        if (lvds_port == LVDS_PORT0)
            HW_LDB_CTRL.B.CH0_MODE = 3;
        else if (lvds_port == LVDS_PORT1)
            HW_LDB_CTRL.B.CH1_MODE = 3;
        else {
            HW_LDB_CTRL.B.CH0_MODE = 3;
            HW_LDB_CTRL.B.CH1_MODE = 3;
        }
    } else {
        printf("Wrong IPU display port %d input!!\n", ipu_port);
        return;
    }

    if (ipu_port == IPU1_DI0 || ipu_port == IPU1_DI1) {
        HW_IOMUXC_GPR3.B.LVDS0_MUX_CTL = 0;
        HW_IOMUXC_GPR3.B.LVDS1_MUX_CTL = 0;
    } else {
        HW_IOMUXC_GPR3.B.LVDS0_MUX_CTL = 2;
        HW_IOMUXC_GPR3.B.LVDS1_MUX_CTL = 2;
    }
}

void ldb_config(int ipu_port, int lvds_port, int data_width, int bit_map)
{
    switch (lvds_port) {
    case LVDS_PORT0:
        HW_LDB_CTRL.B.BIT_MAPPING_CH0 = bit_map;
        HW_LDB_CTRL.B.DATA_WIDTH_CH0 = data_width;
#if defined(CHIP_MX6DQ) || defined(CHIP_MX6SDL)
        HW_IOMUXC_GPR3.B.LVDS0_MUX_CTL = ipu_port;
#endif
        break;
    case LVDS_PORT1:
        HW_LDB_CTRL.B.BIT_MAPPING_CH1 = bit_map;
        HW_LDB_CTRL.B.DATA_WIDTH_CH1 = data_width;
#if defined(CHIP_MX6DQ) || defined(CHIP_MX6SDL)
        HW_IOMUXC_GPR3.B.LVDS1_MUX_CTL = ipu_port;
#endif
        break;
    case LVDS_SPLIT_PORT:
        HW_LDB_CTRL.B.SPLIT_MODE_EN = 1;
        break;
    case LVDS_DUAL_PORT:
        HW_LDB_CTRL.B.BIT_MAPPING_CH0 = bit_map;
        HW_LDB_CTRL.B.DATA_WIDTH_CH0 = data_width;
        HW_LDB_CTRL.B.BIT_MAPPING_CH1 = bit_map;
        HW_LDB_CTRL.B.DATA_WIDTH_CH1 = data_width;
#if defined(CHIP_MX6DQ) || defined(CHIP_MX6SDL)
        HW_IOMUXC_GPR3.B.LVDS0_MUX_CTL = ipu_port;
        HW_IOMUXC_GPR3.B.LVDS1_MUX_CTL = ipu_port;
#endif
        break;
    default:
        printf("Wrong LVDS port input!!\n");
        return;
    }
    ldb_set_channel_route(ipu_port, lvds_port);
}

void ldb_set_vs_polarity(int ipu_port, int vs_pol)
{
    switch (ipu_port) {
    case IPU1_DI0:
    case IPU2_DI0:
        HW_LDB_CTRL.B.DI0_VS_POLARITY = vs_pol;
        break;
    case IPU1_DI1:
    case IPU2_DI1:
        HW_LDB_CTRL.B.DI1_VS_POLARITY = vs_pol;
        break;
    default:
        printf("Unkown display port %d!! please check.\n", ipu_port);
        break;
    }
}

/////////////////////////////////////////////////////////////////////////////
// CODE
/////////////////////////////////////////////////////////////////////////////
