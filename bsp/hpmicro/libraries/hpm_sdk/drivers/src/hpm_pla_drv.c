/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_soc_feature.h"
#include "hpm_pla_drv.h"

void pla_set_aoi_16to8_one_channel(PLA_Type *pla,
                                    pla_aoi_16to8_chn_cfg_t *cfg)
{
    uint8_t i;
    uint32_t value;

    value = 0;
    for (i = 0; i < PLA_AOI_16TO8_SIGNAL_NUM; i++) {
        value |= ((uint32_t)cfg->input[i].op) << (cfg->input[i].signal << 1);
    }
    pla->CHN[cfg->chn].AOI_16TO8[cfg->aoi_16to8_chn] = value;
}

void pla_get_aoi_16to8_one_channel(PLA_Type *pla,
                                    pla_channel_type_t chn,
                                    pla_aoi_16to8_channel_type_t aoi_16to8_chn,
                                    pla_aoi_16to8_chn_cfg_t *cfg)
{
    uint8_t i;

    for (i = 0; i < PLA_AOI_16TO8_SIGNAL_NUM; i++) {
        cfg->input[i].signal = i;
        cfg->input[i].op = (pla->CHN[chn].AOI_16TO8[aoi_16to8_chn] >> (i << 1)) & 0x03;
    }
}

void pla_set_aoi_8to7_one_channel(PLA_Type *pla,
                                    pla_aoi_8to7_chn_cfg_t *cfg)
{
    uint8_t i;
    uint32_t value;

    value = 0;
    for (i = 0; i < PLA_AOI_8TO7_SIGNAL_NUM; i++) {
        value |= ((uint32_t)cfg->input[i].op) << (cfg->input[i].signal << 1);
    }
    switch (cfg->aoi_8to7_chn) {
    case pla_aoi_8to7_chn_0:
        pla->CHN[cfg->chn].AOI_8TO7_00_01 = (pla->CHN[cfg->chn].AOI_8TO7_00_01 & 0xffff0000) | value;
        break;
    case pla_aoi_8to7_chn_1:
        pla->CHN[cfg->chn].AOI_8TO7_00_01 = (pla->CHN[cfg->chn].AOI_8TO7_00_01 & 0x0000ffff) | (value << 16);
        break;
    case pla_aoi_8to7_chn_2:
        pla->CHN[cfg->chn].AOI_8TO7_02_03 = (pla->CHN[cfg->chn].AOI_8TO7_02_03 & 0xffff0000) | value;
        break;
    case pla_aoi_8to7_chn_3:
        pla->CHN[cfg->chn].AOI_8TO7_02_03 = (pla->CHN[cfg->chn].AOI_8TO7_02_03 & 0x0000ffff) | (value << 16);
        break;
    case pla_aoi_8to7_chn_4:
        pla->CHN[cfg->chn].AOI_8TO7_04_05 = (pla->CHN[cfg->chn].AOI_8TO7_04_05 & 0xffff0000) | value;
        break;
    case pla_aoi_8to7_chn_5:
        pla->CHN[cfg->chn].AOI_8TO7_04_05 = (pla->CHN[cfg->chn].AOI_8TO7_04_05 & 0x0000ffff) | (value << 16);
        break;
    case pla_aoi_8to7_chn_6:
        pla->CHN[cfg->chn].AOI_8TO7_06 = value;
        break;
    default:
        break;
    }
}

void pla_get_aoi_8to7_one_channel(PLA_Type *pla,
                                    pla_aoi_8to7_chn_cfg_t *cfg)
{
    uint8_t i;

    switch (cfg->aoi_8to7_chn) {
    case pla_aoi_8to7_chn_0:
        for (i = 0; i < PLA_AOI_8TO7_SIGNAL_NUM; i++) {
            cfg->input[i].signal = i;
            cfg->input[i].op = (pla->CHN[cfg->chn].AOI_8TO7_00_01 >> (i << 1)) & 0x03;
        }
        break;
    case pla_aoi_8to7_chn_1:
        for (i = 0; i < PLA_AOI_8TO7_SIGNAL_NUM; i++) {
            cfg->input[i].signal = i;
            cfg->input[i].op = (pla->CHN[cfg->chn].AOI_8TO7_00_01 >> (i << 17)) & 0x03;
        }
        break;
    case pla_aoi_8to7_chn_2:
        for (i = 0; i < PLA_AOI_8TO7_SIGNAL_NUM; i++) {
            cfg->input[i].signal = i;
            cfg->input[i].op = (pla->CHN[cfg->chn].AOI_8TO7_02_03 >> (i << 1)) & 0x03;
        }
        break;
    case pla_aoi_8to7_chn_3:
        for (i = 0; i < PLA_AOI_8TO7_SIGNAL_NUM; i++) {
            cfg->input[i].signal = i;
            cfg->input[i].op = (pla->CHN[cfg->chn].AOI_8TO7_02_03 >> (i << 17)) & 0x03;
        }
        break;
    case pla_aoi_8to7_chn_4:
        for (i = 0; i < PLA_AOI_8TO7_SIGNAL_NUM; i++) {
            cfg->input[i].signal = i;
            cfg->input[i].op = (pla->CHN[cfg->chn].AOI_8TO7_04_05 >> (i << 1)) & 0x03;
        }
        break;
    case pla_aoi_8to7_chn_5:
        for (i = 0; i < PLA_AOI_8TO7_SIGNAL_NUM; i++) {
            cfg->input[i].signal = i;
            cfg->input[i].op = (pla->CHN[cfg->chn].AOI_8TO7_04_05 >> (i << 17)) & 0x03;
        }
        break;
    case pla_aoi_8to7_chn_6:
        for (i = 0; i < PLA_AOI_8TO7_SIGNAL_NUM; i++) {
            cfg->input[i].signal = i;
            cfg->input[i].op = (pla->CHN[cfg->chn].AOI_8TO7_06 >> (i << 1)) & 0x03;
        }
        break;
    default:
        break;
    }
}

void pla_set_aoi_8to7_input_signal(PLA_Type *pla,
                                    pla_channel_type_t chn,
                                    pla_aoi_8to7_channel_type_t aoi_8to7_chn,
                                    pla_aoi_8to7_cfg_unit_t *cfg)
{
    uint32_t value;

    value = ((uint32_t)cfg->op) << (cfg->signal << 1);
    switch (aoi_8to7_chn) {
    case pla_aoi_8to7_chn_0:
        pla->CHN[chn].AOI_8TO7_00_01 = (pla->CHN[chn].AOI_8TO7_00_01 & 0xffff0000) | value;
        break;
    case pla_aoi_8to7_chn_1:
        pla->CHN[chn].AOI_8TO7_00_01 = (pla->CHN[chn].AOI_8TO7_00_01 & 0x0000ffff) | (value << 16);
        break;
    case pla_aoi_8to7_chn_2:
        pla->CHN[chn].AOI_8TO7_02_03 = (pla->CHN[chn].AOI_8TO7_02_03 & 0xffff0000) | value;
        break;
    case pla_aoi_8to7_chn_3:
        pla->CHN[chn].AOI_8TO7_02_03 = (pla->CHN[chn].AOI_8TO7_02_03 & 0x0000ffff) | (value << 16);
        break;
    case pla_aoi_8to7_chn_4:
        pla->CHN[chn].AOI_8TO7_04_05 = (pla->CHN[chn].AOI_8TO7_04_05 & 0xffff0000) | value;
        break;
    case pla_aoi_8to7_chn_5:
        pla->CHN[chn].AOI_8TO7_04_05 = (pla->CHN[chn].AOI_8TO7_04_05 & 0x0000ffff) | (value << 16);
        break;
    case pla_aoi_8to7_chn_6:
        pla->CHN[chn].AOI_8TO7_06 = value;
        break;
    default:
        break;
    }
}

void pla_get_aoi_8to7_input_signal(PLA_Type *pla,
                                    pla_channel_type_t chn,
                                    pla_aoi_8to7_channel_type_t aoi_8to7_chn,
                                    pla_aoi_8to7_input_signal_type_t signal,
                                    pla_aoi_8to7_cfg_unit_t *cfg)
{

    switch (aoi_8to7_chn) {
    case pla_aoi_8to7_chn_0:
        cfg->signal = signal;
        cfg->op = (pla->CHN[chn].AOI_8TO7_00_01 >> (signal << 1)) & 0x03;
        break;
    case pla_aoi_8to7_chn_1:
        cfg->signal = signal;
        cfg->op = (pla->CHN[chn].AOI_8TO7_00_01 >> (signal << 17)) & 0x03;
        break;
    case pla_aoi_8to7_chn_2:
        cfg->signal = signal;
        cfg->op = (pla->CHN[chn].AOI_8TO7_02_03 >> (signal << 1)) & 0x03;
        break;
    case pla_aoi_8to7_chn_3:
        cfg->signal = signal;
        cfg->op = (pla->CHN[chn].AOI_8TO7_02_03 >> (signal << 17)) & 0x03;
        break;
    case pla_aoi_8to7_chn_4:
        cfg->signal = signal;
        cfg->op = (pla->CHN[chn].AOI_8TO7_04_05 >> (signal << 1)) & 0x03;
        break;
    case pla_aoi_8to7_chn_5:
        cfg->signal = signal;
        cfg->op = (pla->CHN[chn].AOI_8TO7_04_05 >> (signal << 17)) & 0x03;
        break;
    case pla_aoi_8to7_chn_6:
        cfg->signal = signal;
        cfg->op = (pla->CHN[chn].AOI_8TO7_06 >> (signal << 1)) & 0x03;
        break;
    default:
        break;
    }
}
