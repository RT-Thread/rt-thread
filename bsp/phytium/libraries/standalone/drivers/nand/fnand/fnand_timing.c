/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fnand_timing.c
 * Date: 2022-05-09 14:53:42
 * LastEditTime: 2022-05-09 08:56:27
 * Description:   This file is for timings configuration
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/05/10    first release
 */
#include "ferror_code.h"
#include "fnand.h"
#include "fnand_hw.h"

#include "fdebug.h"
#define FNAND_TIMING_DEBUG_TAG "FNAND_TIMING"
#define FNAND_TIMING_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FNAND_TIMING_DEBUG_TAG, format, ##__VA_ARGS__)
#define FNAND_TIMING_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FNAND_TIMING_DEBUG_TAG, format, ##__VA_ARGS__)
#define FNAND_TIMING_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FNAND_TIMING_DEBUG_TAG, format, ##__VA_ARGS__)

#define FNAND_TIMING_ASY_NUM 12
#define FNAND_TIMING_SYN_NUM 14
#define FNAND_TIMING_TOG_NUM 12

const u16 fnand_timing_asy_mode0[FNAND_TIMING_ASY_NUM] = {0x03, 0x03, 0x28, 0x28, 0x03, 0x03, 0x06, 0x06, 0x28, 0x70, 0x30, 0x50};
const u16 fnand_timing_asy_mode1[FNAND_TIMING_ASY_NUM] = {0x03, 0x03, 0x14, 0x14, 0x03, 0x03, 0x06, 0x06, 0x14, 0x70, 0x20, 0x28};
const u16 fnand_timing_asy_mode2[FNAND_TIMING_ASY_NUM] = {0x03, 0x03, 0x0D, 0x0D, 0x03, 0x03, 0x06, 0x06, 0x0D, 0x70, 0x20, 0x1A};
const u16 fnand_timing_asy_mode3[FNAND_TIMING_ASY_NUM] = {0x03, 0x03, 0x0A, 0x0A, 0x03, 0x03, 0x06, 0x06, 0x0A, 0x70, 0x20, 0x14};
const u16 fnand_timing_asy_mode4[FNAND_TIMING_ASY_NUM] = {0x03, 0x03, 0x08, 0x08, 0x03, 0x03, 0x06, 0x06, 0x08, 0x70, 0x15, 0x10};
const u16 fnand_timing_asy_mode5[FNAND_TIMING_ASY_NUM] = {0x03, 0x03, 0x07, 0x07, 0x03, 0x03, 0x06, 0x06, 0x07, 0x20, 0x15, 0x0E};

const u16 fnand_timing_syn_mode0[FNAND_TIMING_SYN_NUM] = {0x20, 0x41, 0x05, 0x20, 0x10, 0x19, 0x62, 0x40, 0x38, 0x20, 0x00, 0x09, 0x50, 0x20};
const u16 fnand_timing_syn_mode1[FNAND_TIMING_SYN_NUM] = {0x18, 0x32, 0x06, 0x18, 0x0C, 0x10, 0x76, 0x40, 0x2A, 0x18, 0x00, 0x12, 0x24, 0x18};
const u16 fnand_timing_syn_mode2[FNAND_TIMING_SYN_NUM] = {0x10, 0x0A, 0x04, 0x10, 0x08, 0x0A, 0x6E, 0x50, 0x1D, 0x10, 0x00, 0x0C, 0x18, 0x10};
const u16 fnand_timing_syn_mode3[FNAND_TIMING_SYN_NUM] = {0x0C, 0x1A, 0x02, 0x0C, 0x06, 0x08, 0x78, 0x7C, 0x15, 0x0C, 0x00, 0x08, 0x12, 0x0C};
const u16 fnand_timing_syn_mode4[FNAND_TIMING_SYN_NUM] = {0x08, 0x17, 0x05, 0x08, 0x04, 0x01, 0x73, 0x40, 0x0C, 0x08, 0x00, 0x06, 0x0C, 0x10};

const u16 fnand_timing_tog_ddr_mode0[FNAND_TIMING_TOG_NUM] = {0x14, 0x0a, 0x08, 0x08, 0xc8, 0xc8, 0x08, 0x08, 0x14, 0x0a, 0x14, 0x08}; /* 600M clk */


#define ONFI_DYN_TIMING_MAX ((u16)~0U)

static const struct FNandSdrTimings onfi_sdr_timings[] =
{
    {
        .tCCS_min = 500000,
        .tR_max = 200000000,
        .tADL_min = 400000,
        .tALH_min = 20000,
        .tALS_min = 50000,
        .tAR_min = 25000,
        .tCEA_max = 100000,
        .tCEH_min = 20000,
        .tCH_min = 20000,
        .tCHZ_max = 100000,
        .tCLH_min = 20000,
        .tCLR_min = 20000,
        .tCLS_min = 50000,
        .tCOH_min = 0,
        .tCS_min = 70000,
        .tDH_min = 20000,
        .tDS_min = 40000,
        .tFEAT_max = 1000000,
        .tIR_min = 10000,
        .tITC_max = 1000000,
        .tRC_min = 100000,
        .tREA_max = 40000,
        .tREH_min = 30000,
        .tRHOH_min = 0,
        .tRHW_min = 200000,
        .tRHZ_max = 200000,
        .tRLOH_min = 0,
        .tRP_min = 50000,
        .tRR_min = 40000,
        .tRST_max = 250000000000ULL,
        .tWB_max = 200000,
        .tWC_min = 100000,
        .tWH_min = 30000,
        .tWHR_min = 120000,
        .tWP_min = 50000,
        .tWW_min = 100000,
    },

    /* Mode 1 */
    {
        .tCCS_min = 500000,
        .tR_max = 200000000,
        .tADL_min = 400000,
        .tALH_min = 10000,
        .tALS_min = 25000,
        .tAR_min = 10000,
        .tCEA_max = 45000,
        .tCEH_min = 20000,
        .tCH_min = 10000,
        .tCHZ_max = 50000,
        .tCLH_min = 10000,
        .tCLR_min = 10000,
        .tCLS_min = 25000,
        .tCOH_min = 15000,
        .tCS_min = 35000,
        .tDH_min = 10000,
        .tDS_min = 20000,
        .tFEAT_max = 1000000,
        .tIR_min = 0,
        .tITC_max = 1000000,
        .tRC_min = 50000,
        .tREA_max = 30000,
        .tREH_min = 15000,
        .tRHOH_min = 15000,
        .tRHW_min = 100000,
        .tRHZ_max = 100000,
        .tRLOH_min = 0,
        .tRP_min = 25000,
        .tRR_min = 20000,
        .tRST_max = 500000000,
        .tWB_max = 100000,
        .tWC_min = 45000,
        .tWH_min = 15000,
        .tWHR_min = 80000,
        .tWP_min = 25000,
        .tWW_min = 100000,
    },

    /* Mode 2 */
    {
        .tCCS_min = 500000,
        .tR_max = 200000000,
        .tADL_min = 400000,
        .tALH_min = 10000,
        .tALS_min = 15000,
        .tAR_min = 10000,
        .tCEA_max = 30000,
        .tCEH_min = 20000,
        .tCH_min = 10000,
        .tCHZ_max = 50000,
        .tCLH_min = 10000,
        .tCLR_min = 10000,
        .tCLS_min = 15000,
        .tCOH_min = 15000,
        .tCS_min = 25000,
        .tDH_min = 5000,
        .tDS_min = 15000,
        .tFEAT_max = 1000000,
        .tIR_min = 0,
        .tITC_max = 1000000,
        .tRC_min = 35000,
        .tREA_max = 25000,
        .tREH_min = 15000,
        .tRHOH_min = 15000,
        .tRHW_min = 100000,
        .tRHZ_max = 100000,
        .tRLOH_min = 0,
        .tRR_min = 20000,
        .tRST_max = 500000000,
        .tWB_max = 100000,
        .tRP_min = 17000,
        .tWC_min = 35000,
        .tWH_min = 15000,
        .tWHR_min = 80000,
        .tWP_min = 17000,
        .tWW_min = 100000,
    },

    /* Mode 3 */
    {
        .tCCS_min = 500000,
        .tR_max = 200000000,
        .tADL_min = 400000,
        .tALH_min = 5000,
        .tALS_min = 10000,
        .tAR_min = 10000,
        .tCEA_max = 25000,
        .tCEH_min = 20000,
        .tCH_min = 5000,
        .tCHZ_max = 50000,
        .tCLH_min = 5000,
        .tCLR_min = 10000,
        .tCLS_min = 10000,
        .tCOH_min = 15000,
        .tCS_min = 25000,
        .tDH_min = 5000,
        .tDS_min = 10000,
        .tFEAT_max = 1000000,
        .tIR_min = 0,
        .tITC_max = 1000000,
        .tRC_min = 30000,
        .tREA_max = 20000,
        .tREH_min = 10000,
        .tRHOH_min = 15000,
        .tRHW_min = 100000,
        .tRHZ_max = 100000,
        .tRLOH_min = 0,
        .tRP_min = 15000,
        .tRR_min = 20000,
        .tRST_max = 500000000,
        .tWB_max = 100000,
        .tWC_min = 30000,
        .tWH_min = 10000,
        .tWHR_min = 80000,
        .tWP_min = 15000,
        .tWW_min = 100000,
    },
    /* Mode 4 */
    {
        .tCCS_min = 500000,
        .tR_max = 200000000,
        .tADL_min = 400000,
        .tALH_min = 5000,
        .tALS_min = 10000,
        .tAR_min = 10000,
        .tCEA_max = 25000,
        .tCEH_min = 20000,
        .tCH_min = 5000,
        .tCHZ_max = 30000,
        .tCLH_min = 5000,
        .tCLR_min = 10000,
        .tCLS_min = 10000,
        .tCOH_min = 15000,
        .tCS_min = 20000,
        .tDH_min = 5000,
        .tDS_min = 10000,
        .tFEAT_max = 1000000,
        .tIR_min = 0,
        .tITC_max = 1000000,
        .tRC_min = 25000,
        .tREA_max = 20000,
        .tREH_min = 10000,
        .tRHOH_min = 15000,
        .tRHW_min = 100000,
        .tRHZ_max = 100000,
        .tRLOH_min = 5000,
        .tRP_min = 12000,
        .tRR_min = 20000,
        .tRST_max = 500000000,
        .tWB_max = 100000,
        .tWC_min = 25000,
        .tWH_min = 10000,
        .tWHR_min = 80000,
        .tWP_min = 12000,
        .tWW_min = 100000,
    },
    /* Mode 5 */
    {
        .tCCS_min = 500000,
        .tR_max = 200000000,
        .tADL_min = 400000,
        .tALH_min = 5000,
        .tALS_min = 10000,
        .tAR_min = 10000,
        .tCEA_max = 25000,
        .tCEH_min = 20000,
        .tCH_min = 5000,
        .tCHZ_max = 30000,
        .tCLH_min = 5000,
        .tCLR_min = 10000,
        .tCLS_min = 10000,
        .tCOH_min = 15000,
        .tCS_min = 15000,
        .tDH_min = 5000,
        .tDS_min = 7000,
        .tFEAT_max = 1000000,
        .tIR_min = 0,
        .tITC_max = 1000000,
        .tRC_min = 20000,
        .tREA_max = 16000,
        .tREH_min = 7000,
        .tRHOH_min = 15000,
        .tRHW_min = 100000,
        .tRHZ_max = 100000,
        .tRLOH_min = 5000,
        .tRP_min = 10000,
        .tRR_min = 20000,
        .tRST_max = 500000000,
        .tWB_max = 100000,
        .tWC_min = 20000,
        .tWH_min = 7000,
        .tWHR_min = 80000,
        .tWP_min = 10000,
        .tWW_min = 100000,
    },
};

static FError FNandMemcpyToReg16(FNand *instance_p, u32 reg, u32 reg_step, const u16 *buf, u32 len)
{
    u32 i;
    u32 value = 0;

    if (!instance_p || !buf)
    {
        FNAND_TIMING_DEBUG_E("instance_p is %p ,buf is %p", instance_p, buf);
        return FNAND_ERR_INVAILD_PARAMETER;
    }

    for (i = 0; i < len; i++)
    {
        value = (value << 16) + buf[i];
        if (i % 2)
        {
            FNAND_WRITEREG(instance_p->config.base_address, reg, value);
            value = 0;
            reg += reg_step;
        }
    }

    return FT_SUCCESS;
}

/**
 * @name:
 * @msg: 根据inter_mode 与 timing_mode
 * @note:
 * @return {*}
 * @param {FNand} *instance_p
 */
FError FNandTimingInterfaceUpdate(FNand *instance_p, u32 chip_addr)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(chip_addr < FNAND_CONNECT_MAX_NUM);
    const u16 *target_timming_data = NULL;
    FNandConfig *config_p = &instance_p->config ;
    u32 value = 0 ;
    FError ret;

    FNandSetOption(instance_p, FNAND_OPS_INTER_MODE_SELECT, instance_p->inter_mode[chip_addr]);

    FNAND_CLEARBIT(config_p->base_address, FNAND_CTRL1_OFFSET, FNAND_CTRL1_SAMPL_PHASE_MAKE(0xffffUL)); /* clear sampl_phase */
    switch (instance_p->inter_mode[chip_addr])
    {
        case FNAND_ASYN_SDR:
            if (FNAND_TIMING_MODE4 == (instance_p->timing_mode[chip_addr] & 0xf))
            {
                target_timming_data = fnand_timing_asy_mode4;
                value = FNAND_CTRL1_SAMPL_PHASE_MAKE(4UL) ;
            }
            else if (FNAND_TIMING_MODE3 == (instance_p->timing_mode[chip_addr] & 0xf))
            {
                target_timming_data = fnand_timing_asy_mode3;
                value = FNAND_CTRL1_SAMPL_PHASE_MAKE(5UL) ;
            }
            else if (FNAND_TIMING_MODE2 == (instance_p->timing_mode[chip_addr] & 0xf))
            {
                target_timming_data = fnand_timing_asy_mode2;
                value = FNAND_CTRL1_SAMPL_PHASE_MAKE(6UL) ;
            }
            else if (FNAND_TIMING_MODE1 == (instance_p->timing_mode[chip_addr] & 0xf))
            {
                target_timming_data = fnand_timing_asy_mode1;
                value = FNAND_CTRL1_SAMPL_PHASE_MAKE(5UL) ;
            }
            else
            {
                target_timming_data = fnand_timing_asy_mode0;
                value = FNAND_CTRL1_SAMPL_PHASE_MAKE(1UL) ;
            }
            ret = FNandMemcpyToReg16(instance_p, FNAND_ASY_TIMING0_OFFSET, 4, target_timming_data, FNAND_TIMING_ASY_NUM);
            if (ret != FT_SUCCESS)
            {
                return  ret;
            }
            FNAND_SETBIT(config_p->base_address, FNAND_CTRL1_OFFSET, value);
            FNAND_WRITEREG(config_p->base_address, FNAND_INTERVAL_OFFSET, 1);
            break;
        case FNAND_ONFI_DDR:
            if (FNAND_TIMING_MODE4 == (instance_p->timing_mode[chip_addr] & 0xf))
            {
                FNAND_WRITEREG(config_p->base_address, FNAND_INTERVAL_OFFSET, 0x30);
                target_timming_data = fnand_timing_syn_mode4;
                value = FNAND_CTRL1_SAMPL_PHASE_MAKE(0xdUL) ;
            }
            else if (FNAND_TIMING_MODE3 == (instance_p->timing_mode[chip_addr] & 0xf))
            {
                FNAND_WRITEREG(config_p->base_address, FNAND_INTERVAL_OFFSET, 0x18);
                target_timming_data = fnand_timing_syn_mode3;
                value = FNAND_CTRL1_SAMPL_PHASE_MAKE(5UL) ;
            }
            else if (FNAND_TIMING_MODE2 == (instance_p->timing_mode[chip_addr] & 0xf))
            {
                FNAND_WRITEREG(config_p->base_address, FNAND_INTERVAL_OFFSET, 0x20);
                target_timming_data = fnand_timing_syn_mode2;
                value = FNAND_CTRL1_SAMPL_PHASE_MAKE(0x8UL) ;
            }
            else if (FNAND_TIMING_MODE1 == (instance_p->timing_mode[chip_addr] & 0xf))
            {
                FNAND_WRITEREG(config_p->base_address, FNAND_INTERVAL_OFFSET, 0x40);
                target_timming_data = fnand_timing_syn_mode1;
                value = FNAND_CTRL1_SAMPL_PHASE_MAKE(0x12UL) ;
            }
            else
            {
                FNAND_WRITEREG(config_p->base_address, FNAND_INTERVAL_OFFSET, 0x40);
                target_timming_data = fnand_timing_syn_mode0;
                value = FNAND_CTRL1_SAMPL_PHASE_MAKE(0x12UL) ;
            }
            ret =  FNandMemcpyToReg16(instance_p, FNAND_SYN_TIMING6_OFFSET, 4, target_timming_data, FNAND_TIMING_SYN_NUM);
            if (ret != FT_SUCCESS)
            {
                return  ret;
            }
            FNAND_SETBIT(config_p->base_address, FNAND_CTRL1_OFFSET, value);
            break;
        case FNAND_TOG_ASYN_DDR:
            value = FNAND_CTRL1_SAMPL_PHASE_MAKE(8UL);
            target_timming_data = fnand_timing_tog_ddr_mode0;
            ret = FNandMemcpyToReg16(instance_p, FNAND_TOG_TIMING13_OFFSET, 4, target_timming_data, FNAND_TIMING_SYN_NUM);
            if (ret != FT_SUCCESS)
            {
                return  ret;
            }
            FNAND_WRITEREG(config_p->base_address, FNAND_INTERVAL_OFFSET, 0xc8);
            FNAND_SETBIT(config_p->base_address, FNAND_CTRL1_OFFSET, value);
            break;
        default:
            FNAND_TIMING_DEBUG_E("Error inter_mode is %x", instance_p->inter_mode[chip_addr]);
            return  FNAND_ERR_INVAILD_PARAMETER;
    }

    return FT_SUCCESS;
}


const struct FNandSdrTimings *FNandAsyncTimingModeToSdrTimings(FNandAsyncTimint mode)
{
    if (mode >= FNAND_ASYNC_TIM_INT_MODE4)
    {
        FNAND_TIMING_DEBUG_E("FNandAsyncTimingModeToSdrTimings set is over mode range");
        return NULL;
    }

    return &onfi_sdr_timings[mode];
}



/**
 * @name:
 * @msg:
 * @return {*}
 * @param {FNand} *instance_p
 * @param {FNandAsyncTimint} mode
 * @Note 当前只支持onfi 模式
 */
FError FNandFillTimingModeTiming(FNand *instance_p, FNandAsyncTimint mode)
{
    struct FNandSdrTimings *sdr_timing_p = NULL;
    const struct FNandSdrTimings *source_timing_p = NULL;
    FASSERT(instance_p != NULL);
    sdr_timing_p = &instance_p->sdr_timing;
    source_timing_p = FNandAsyncTimingModeToSdrTimings(mode);
    FASSERT(source_timing_p != NULL);
    *sdr_timing_p = *source_timing_p;


    return FT_SUCCESS;
}
