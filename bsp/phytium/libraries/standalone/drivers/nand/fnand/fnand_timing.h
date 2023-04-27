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
 * FilePath: fnand_timing.h
 * Date: 2022-04-28 18:53:58
 * LastEditTime: 2022-04-28 18:53:58
 * Description:  This file is for timings configuration
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/05/10    first release
 */

#ifndef FNAND_TIMING_H
#define FNAND_TIMING_H

#include "ftypes.h"


#ifdef __cplusplus
extern "C"
{
#endif


/**
 * struct FNandSdrTimings - SDR NAND chip timings
 *
 * This struct defines the timing requirements of a SDR NAND chip.
 * These information can be found in every NAND datasheets and the timings
 * meaning are described in the ONFI specifications:
 * www.onfi.org/~/media/ONFI/specs/onfi_3_1_spec.pdf (chapter 4.15 Timing
 * Parameters)
 *
 * All these timings are expressed in picoseconds.
 *
 * @tBERS_max: Block erase time
 * @tCCS_min: Change column setup time
 * @tPROG_max: Page program time
 * @tR_max: Page read time
 * @tALH_min: ALE hold time
 * @tADL_min: ALE to data loading time
 * @tALS_min: ALE setup time
 * @tAR_min: ALE to RE# delay
 * @tCEA_max: CE# access time
 * @tCEH_min: CE# high hold time
 * @tCH_min:  CE# hold time
 * @tCHZ_max: CE# high to output hi-Z
 * @tCLH_min: CLE hold time
 * @tCLR_min: CLE to RE# delay
 * @tCLS_min: CLE setup time
 * @tCOH_min: CE# high to output hold
 * @tCS_min: CE# setup time
 * @tDH_min: Data hold time
 * @tDS_min: Data setup time
 * @tFEAT_max: Busy time for Set Features and Get Features
 * @tIR_min: Output hi-Z to RE# low
 * @tITC_max: Interface and Timing Mode Change time
 * @tRC_min: RE# cycle time
 * @tREA_max: RE# access time
 * @tREH_min: RE# high hold time
 * @tRHOH_min: RE# high to output hold
 * @tRHW_min: RE# high to WE# low
 * @tRHZ_max: RE# high to output hi-Z
 * @tRLOH_min: RE# low to output hold
 * @tRP_min: RE# pulse width
 * @tRR_min: Ready to RE# low (data only)
 * @tRST_max: Device reset time, measured from the falling edge of R/B# to the
 *        rising edge of R/B#.
 * @tWB_max: WE# high to SR[6] low
 * @tWC_min: WE# cycle time
 * @tWH_min: WE# high hold time
 * @tWHR_min: WE# high to RE# low
 * @tWP_min: WE# pulse width
 * @tWW_min: WP# transition to WE# low
 */
struct FNandSdrTimings
{
    u64 tBERS_max;
    u32 tCCS_min;
    u64 tPROG_max;
    u64 tR_max;
    u32 tALH_min;
    u32 tADL_min;
    u32 tALS_min;
    u32 tAR_min;
    u32 tCEA_max;
    u32 tCEH_min;
    u32 tCH_min;
    u32 tCHZ_max;
    u32 tCLH_min;
    u32 tCLR_min;
    u32 tCLS_min;
    u32 tCOH_min;
    u32 tCS_min;
    u32 tDH_min;
    u32 tDS_min;
    u32 tFEAT_max;
    u32 tIR_min;
    u32 tITC_max;
    u32 tRC_min;
    u32 tREA_max;
    u32 tREH_min;
    u32 tRHOH_min;
    u32 tRHW_min;
    u32 tRHZ_max;
    u32 tRLOH_min;
    u32 tRP_min;
    u32 tRR_min;
    u64 tRST_max;
    u32 tWB_max;
    u32 tWC_min;
    u32 tWH_min;
    u32 tWHR_min;
    u32 tWP_min;
    u32 tWW_min;
};

#ifdef __cplusplus
}
#endif

#endif

